// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_51BA00_sub_51BA00.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x51BA00）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 4866 行；字符串证据 0 条；外调 6 个
//   调: sub_51BA00 sub_4E9B10 sub_5144A0 sub_445150 sub_6048E0 sub_5101B0
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x51BA00 sub_51BA00  size=25733
// ------------------------------------------------------------
// bad sp value at call has been detected, the output may be wrong!
int /*usercall*/ sub_51BA00@<eax>(int a1@<edx>, int a2@<ecx>, int a3@<ebx>, int a4, int a5)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v6; // esp
  char v8; // si
  int v9; // eax
  int v10; // esi
  int v11; // eax
  double v12; // st7
  int result; // eax
  int v14; // eax
  int v15; // esi
  int v16; // eax
  int v17; // eax
  int v18; // esi
  int v19; // eax
  int v20; // eax
  int v21; // esi
  int v22; // eax
  int v23; // esi
  int v24; // eax
  int v25; // eax
  char *v26; // ecx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // esi
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int v44; // eax
  int v45; // esi
  int v46; // eax
  int v47; // esi
  int v48; // eax
  int v49; // eax
  int v50; // esi
  int v51; // eax
  int v52; // esi
  int v53; // eax
  int v54; // esi
  int v55; // eax
  int v56; // esi
  int v57; // eax
  int v58; // esi
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int v62; // esi
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // eax
  int v67; // esi
  int v68; // eax
  int v69; // eax
  int v70; // eax
  int v71; // eax
  int v72; // eax
  int v73; // eax
  int v74; // eax
  int v75; // edi
  int v76; // eax
  int v77; // eax
  int v78; // eax
  char *v79; // ecx
  int v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  int v85; // eax
  int v86; // eax
  int v87; // eax
  int v88; // eax
  int v89; // eax
  int v90; // eax
  int v91; // eax
  int v92; // eax
  int v93; // eax
  int v94; // eax
  int v95; // eax
  int v96; // eax
  int v97; // eax
  int v98; // eax
  int v99; // eax
  int v100; // eax
  char *v101; // ecx
  int v102; // eax
  int v103; // esi
  int v104; // eax
  int v105; // eax
  int v106; // eax
  int v107; // esi
  void *v108; // eax
  int v109; // eax
  int v110; // eax
  int v111; // eax
  int v112; // eax
  int v113; // eax
  int v114; // eax
  int v115; // eax
  char *v116; // ecx
  int v117; // eax
  int v118; // eax
  int v119; // eax
  int v120; // eax
  int v121; // eax
  int v122; // eax
  int v123; // eax
  int v124; // eax
  int v125; // eax
  int v126; // eax
  int v127; // eax
  int v128; // eax
  int v129; // eax
  int v130; // eax
  int v131; // eax
  int v132; // eax
  int v133; // eax
  int v134; // eax
  int v135; // eax
  int v136; // eax
  int v137; // eax
  int v138; // eax
  int v139; // eax
  int v140; // eax
  int v141; // eax
  int v142; // eax
  int v143; // eax
  void *v144; // eax
  int v145; // eax
  int v146; // eax
  int v147; // eax
  int v148; // eax
  int v149; // eax
  int v150; // eax
  int v151; // eax
  int v152; // eax
  int v153; // eax
  int v154; // eax
  int v155; // eax
  int v156; // eax
  int v157; // eax
  int v158; // eax
  int v159; // eax
  int v160; // eax
  int v161; // eax
  int v162; // eax
  int v163; // eax
  int v164; // eax
  int v165; // eax
  int v166; // edi
  int v167; // eax
  double v168; // st7
  int v169; // eax
  int v170; // eax
  int v171; // eax
  int v172; // eax
  int v173; // eax
  int v174; // eax
  int v175; // eax
  int v176; // eax
  int v177; // eax
  int v178; // eax
  char *v179; // ecx
  int v180; // eax
  int v181; // eax
  int v182; // eax
  int v183; // eax
  int v184; // eax
  int v185; // eax
  int v186; // eax
  int v187; // eax
  int v188; // eax
  int v189; // eax
  int v190; // eax
  int v191; // eax
  int v192; // eax
  int v193; // eax
  int v194; // eax
  int v195; // eax
  int v196; // eax
  int v197; // eax
  int v198; // eax
  int v199; // eax
  int v200; // eax
  void *v201; // eax
  int v202; // eax
  int v203; // eax
  int v204; // eax
  int v205; // eax
  int v206; // eax
  int v207; // eax
  int v208; // eax
  int v209; // eax
  void *v210; // eax
  int v211; // eax
  void *v212; // eax
  int v213; // eax
  int v214; // eax
  int v215; // eax
  int v216; // eax
  int v217; // eax
  int v218; // eax
  int v219; // eax
  int v220; // eax
  int v221; // eax
  int v222; // eax
  int v223; // eax
  int v224; // [esp-1Ch] [ebp-281Ch]
  int v225; // [esp-1Ch] [ebp-281Ch]
  int v226; // [esp-18h] [ebp-2818h] BYREF
  int v227; // [esp-14h] [ebp-2814h]
  int v228; // [esp-10h] [ebp-2810h]
  int v229; // [esp-Ch] [ebp-280Ch]
  char v230; // [esp+0h] [ebp-2800h] BYREF
  uint8_t v231[60]; // [esp+3Ch] [ebp-27C4h] BYREF
  uint8_t v232[60]; // [esp+78h] [ebp-2788h] BYREF
  uint8_t v233[60]; // [esp+B4h] [ebp-274Ch] BYREF
  uint8_t v234[60]; // [esp+F0h] [ebp-2710h] BYREF
  uint8_t v235[60]; // [esp+12Ch] [ebp-26D4h] BYREF
  char v236; // [esp+168h] [ebp-2698h] BYREF
  uint8_t v237[60]; // [esp+1A4h] [ebp-265Ch] BYREF
  uint8_t v238[60]; // [esp+1E0h] [ebp-2620h] BYREF
  uint8_t v239[60]; // [esp+21Ch] [ebp-25E4h] BYREF
  uint8_t v240[60]; // [esp+258h] [ebp-25A8h] BYREF
  uint8_t v241[60]; // [esp+294h] [ebp-256Ch] BYREF
  uint8_t v242[60]; // [esp+2D0h] [ebp-2530h] BYREF
  uint8_t v243[60]; // [esp+30Ch] [ebp-24F4h] BYREF
  uint8_t v244[60]; // [esp+348h] [ebp-24B8h] BYREF
  uint8_t v245[60]; // [esp+384h] [ebp-247Ch] BYREF
  uint8_t v246[60]; // [esp+3C0h] [ebp-2440h] BYREF
  uint8_t v247[60]; // [esp+3FCh] [ebp-2404h] BYREF
  uint8_t v248[60]; // [esp+438h] [ebp-23C8h] BYREF
  uint8_t v249[60]; // [esp+474h] [ebp-238Ch] BYREF
  uint8_t v250[60]; // [esp+4B0h] [ebp-2350h] BYREF
  uint8_t v251[60]; // [esp+4ECh] [ebp-2314h] BYREF
  uint8_t v252[60]; // [esp+528h] [ebp-22D8h] BYREF
  char v253; // [esp+564h] [ebp-229Ch] BYREF
  uint8_t v254[60]; // [esp+5A0h] [ebp-2260h] BYREF
  uint8_t v255[60]; // [esp+5DCh] [ebp-2224h] BYREF
  uint8_t v256[60]; // [esp+618h] [ebp-21E8h] BYREF
  uint8_t v257[60]; // [esp+654h] [ebp-21ACh] BYREF
  uint8_t v258[60]; // [esp+690h] [ebp-2170h] BYREF
  uint8_t v259[60]; // [esp+6CCh] [ebp-2134h] BYREF
  uint8_t v260[60]; // [esp+708h] [ebp-20F8h] BYREF
  uint8_t v261[60]; // [esp+744h] [ebp-20BCh] BYREF
  uint8_t v262[60]; // [esp+780h] [ebp-2080h] BYREF
  uint8_t v263[60]; // [esp+7BCh] [ebp-2044h] BYREF
  uint8_t v264[60]; // [esp+7F8h] [ebp-2008h] BYREF
  uint8_t v265[60]; // [esp+834h] [ebp-1FCCh] BYREF
  uint8_t v266[60]; // [esp+870h] [ebp-1F90h] BYREF
  uint8_t v267[60]; // [esp+8ACh] [ebp-1F54h] BYREF
  uint8_t v268[60]; // [esp+8E8h] [ebp-1F18h] BYREF
  uint8_t v269[60]; // [esp+924h] [ebp-1EDCh] BYREF
  uint8_t v270[60]; // [esp+960h] [ebp-1EA0h] BYREF
  uint8_t v271[60]; // [esp+99Ch] [ebp-1E64h] BYREF
  uint8_t v272[60]; // [esp+9D8h] [ebp-1E28h] BYREF
  uint8_t v273[60]; // [esp+A14h] [ebp-1DECh] BYREF
  uint8_t v274[60]; // [esp+A50h] [ebp-1DB0h] BYREF
  uint8_t v275[60]; // [esp+A8Ch] [ebp-1D74h] BYREF
  uint8_t v276[60]; // [esp+AC8h] [ebp-1D38h] BYREF
  uint8_t v277[60]; // [esp+B04h] [ebp-1CFCh] BYREF
  uint8_t v278[60]; // [esp+B40h] [ebp-1CC0h] BYREF
  uint8_t v279[60]; // [esp+B7Ch] [ebp-1C84h] BYREF
  uint8_t v280[60]; // [esp+BB8h] [ebp-1C48h] BYREF
  char v281; // [esp+BF4h] [ebp-1C0Ch] BYREF
  uint8_t v282[60]; // [esp+C30h] [ebp-1BD0h] BYREF
  uint8_t v283[60]; // [esp+C6Ch] [ebp-1B94h] BYREF
  uint8_t v284[60]; // [esp+CA8h] [ebp-1B58h] BYREF
  char v285; // [esp+CE4h] [ebp-1B1Ch] BYREF
  uint8_t v286[60]; // [esp+D20h] [ebp-1AE0h] BYREF
  uint8_t v287[60]; // [esp+D5Ch] [ebp-1AA4h] BYREF
  uint8_t v288[60]; // [esp+D98h] [ebp-1A68h] BYREF
  uint8_t v289[60]; // [esp+DD4h] [ebp-1A2Ch] BYREF
  uint8_t v290[60]; // [esp+E10h] [ebp-19F0h] BYREF
  uint8_t v291[60]; // [esp+E4Ch] [ebp-19B4h] BYREF
  uint8_t v292[60]; // [esp+E88h] [ebp-1978h] BYREF
  uint8_t v293[60]; // [esp+EC4h] [ebp-193Ch] BYREF
  uint8_t v294[60]; // [esp+F00h] [ebp-1900h] BYREF
  uint8_t v295[60]; // [esp+F3Ch] [ebp-18C4h] BYREF
  uint8_t v296[60]; // [esp+F78h] [ebp-1888h] BYREF
  uint8_t v297[60]; // [esp+FB4h] [ebp-184Ch] BYREF
  uint8_t v298[60]; // [esp+FF0h] [ebp-1810h] BYREF
  uint8_t v299[60]; // [esp+102Ch] [ebp-17D4h] BYREF
  uint8_t v300[60]; // [esp+1068h] [ebp-1798h] BYREF
  uint8_t v301[60]; // [esp+10A4h] [ebp-175Ch] BYREF
  uint8_t v302[60]; // [esp+10E0h] [ebp-1720h] BYREF
  uint8_t v303[60]; // [esp+111Ch] [ebp-16E4h] BYREF
  uint8_t v304[60]; // [esp+1158h] [ebp-16A8h] BYREF
  uint8_t v305[60]; // [esp+1194h] [ebp-166Ch] BYREF
  uint8_t v306[60]; // [esp+11D0h] [ebp-1630h] BYREF
  uint8_t v307[60]; // [esp+120Ch] [ebp-15F4h] BYREF
  uint8_t v308[60]; // [esp+1248h] [ebp-15B8h] BYREF
  uint8_t v309[60]; // [esp+1284h] [ebp-157Ch] BYREF
  char v310; // [esp+12C0h] [ebp-1540h] BYREF
  uint8_t v311[60]; // [esp+12FCh] [ebp-1504h] BYREF
  uint8_t v312[60]; // [esp+1338h] [ebp-14C8h] BYREF
  uint8_t v313[60]; // [esp+1374h] [ebp-148Ch] BYREF
  uint8_t v314[60]; // [esp+13B0h] [ebp-1450h] BYREF
  uint8_t v315[60]; // [esp+13ECh] [ebp-1414h] BYREF
  uint8_t v316[60]; // [esp+1428h] [ebp-13D8h] BYREF
  uint8_t v317[60]; // [esp+1464h] [ebp-139Ch] BYREF
  char v318; // [esp+14A0h] [ebp-1360h] BYREF
  uint8_t v319[60]; // [esp+14DCh] [ebp-1324h] BYREF
  uint8_t v320[60]; // [esp+1518h] [ebp-12E8h] BYREF
  uint8_t v321[60]; // [esp+1554h] [ebp-12ACh] BYREF
  uint8_t v322[60]; // [esp+1590h] [ebp-1270h] BYREF
  uint8_t v323[60]; // [esp+15CCh] [ebp-1234h] BYREF
  uint8_t v324[60]; // [esp+1608h] [ebp-11F8h] BYREF
  uint8_t v325[60]; // [esp+1644h] [ebp-11BCh] BYREF
  uint8_t v326[60]; // [esp+1680h] [ebp-1180h] BYREF
  uint8_t v327[60]; // [esp+16BCh] [ebp-1144h] BYREF
  uint8_t v328[60]; // [esp+16F8h] [ebp-1108h] BYREF
  uint8_t v329[60]; // [esp+1734h] [ebp-10CCh] BYREF
  uint8_t v330[60]; // [esp+1770h] [ebp-1090h] BYREF
  uint8_t v331[60]; // [esp+17ACh] [ebp-1054h] BYREF
  uint8_t v332[60]; // [esp+17E8h] [ebp-1018h] BYREF
  uint8_t v333[60]; // [esp+1824h] [ebp-FDCh] BYREF
  uint8_t v334[60]; // [esp+1860h] [ebp-FA0h] BYREF
  uint8_t v335[60]; // [esp+189Ch] [ebp-F64h] BYREF
  char v336; // [esp+18D8h] [ebp-F28h] BYREF
  uint8_t v337[60]; // [esp+1914h] [ebp-EECh] BYREF
  uint8_t v338[60]; // [esp+1950h] [ebp-EB0h] BYREF
  uint8_t v339[60]; // [esp+198Ch] [ebp-E74h] BYREF
  uint8_t v340[60]; // [esp+19C8h] [ebp-E38h] BYREF
  uint8_t v341[60]; // [esp+1A04h] [ebp-DFCh] BYREF
  uint8_t v342[60]; // [esp+1A40h] [ebp-DC0h] BYREF
  uint8_t v343[60]; // [esp+1A7Ch] [ebp-D84h] BYREF
  uint8_t v344[60]; // [esp+1AB8h] [ebp-D48h] BYREF
  uint8_t v345[60]; // [esp+1AF4h] [ebp-D0Ch] BYREF
  uint8_t v346[60]; // [esp+1B30h] [ebp-CD0h] BYREF
  uint8_t v347[60]; // [esp+1B6Ch] [ebp-C94h] BYREF
  uint8_t v348[60]; // [esp+1BA8h] [ebp-C58h] BYREF
  uint8_t v349[60]; // [esp+1BE4h] [ebp-C1Ch] BYREF
  uint8_t v350[60]; // [esp+1C20h] [ebp-BE0h] BYREF
  uint8_t v351[60]; // [esp+1C5Ch] [ebp-BA4h] BYREF
  uint8_t v352[60]; // [esp+1C98h] [ebp-B68h] BYREF
  char v353; // [esp+1CD4h] [ebp-B2Ch] BYREF
  uint8_t v354[60]; // [esp+1D10h] [ebp-AF0h] BYREF
  uint8_t v355[60]; // [esp+1D4Ch] [ebp-AB4h] BYREF
  uint8_t v356[60]; // [esp+1D88h] [ebp-A78h] BYREF
  uint8_t v357[60]; // [esp+1DC4h] [ebp-A3Ch] BYREF
  uint8_t v358[60]; // [esp+1E00h] [ebp-A00h] BYREF
  uint8_t v359[60]; // [esp+1E3Ch] [ebp-9C4h] BYREF
  uint8_t v360[60]; // [esp+1E78h] [ebp-988h] BYREF
  uint8_t v361[60]; // [esp+1EB4h] [ebp-94Ch] BYREF
  uint8_t v362[60]; // [esp+1EF0h] [ebp-910h] BYREF
  uint8_t v363[60]; // [esp+1F2Ch] [ebp-8D4h] BYREF
  uint8_t v364[60]; // [esp+1F68h] [ebp-898h] BYREF
  uint8_t v365[60]; // [esp+1FA4h] [ebp-85Ch] BYREF
  uint8_t v366[60]; // [esp+1FE0h] [ebp-820h] BYREF
  uint8_t v367[60]; // [esp+201Ch] [ebp-7E4h] BYREF
  uint8_t v368[60]; // [esp+2058h] [ebp-7A8h] BYREF
  uint8_t v369[60]; // [esp+2094h] [ebp-76Ch] BYREF
  uint8_t v370[60]; // [esp+20D0h] [ebp-730h] BYREF
  uint8_t v371[60]; // [esp+210Ch] [ebp-6F4h] BYREF
  uint8_t v372[60]; // [esp+2148h] [ebp-6B8h] BYREF
  uint8_t v373[60]; // [esp+2184h] [ebp-67Ch] BYREF
  uint8_t v374[60]; // [esp+21C0h] [ebp-640h] BYREF
  uint8_t v375[60]; // [esp+21FCh] [ebp-604h] BYREF
  uint8_t v376[60]; // [esp+2238h] [ebp-5C8h] BYREF
  uint8_t v377[60]; // [esp+2274h] [ebp-58Ch] BYREF
  uint8_t v378[60]; // [esp+22B0h] [ebp-550h] BYREF
  uint8_t v379[60]; // [esp+22ECh] [ebp-514h] BYREF
  uint8_t v380[60]; // [esp+2328h] [ebp-4D8h] BYREF
  uint8_t v381[60]; // [esp+2364h] [ebp-49Ch] BYREF
  uint8_t v382[60]; // [esp+23A0h] [ebp-460h] BYREF
  uint8_t v383[60]; // [esp+23DCh] [ebp-424h] BYREF
  uint8_t v384[60]; // [esp+2418h] [ebp-3E8h] BYREF
  uint8_t v385[60]; // [esp+2454h] [ebp-3ACh] BYREF
  uint8_t v386[60]; // [esp+2490h] [ebp-370h] BYREF
  uint8_t v387[60]; // [esp+24CCh] [ebp-334h] BYREF
  uint8_t v388[60]; // [esp+2508h] [ebp-2F8h] BYREF
  char v389; // [esp+2544h] [ebp-2BCh] BYREF
  uint8_t v390[60]; // [esp+2580h] [ebp-280h] BYREF
  uint8_t v391[60]; // [esp+25BCh] [ebp-244h] BYREF
  uint8_t v392[60]; // [esp+25F8h] [ebp-208h] BYREF
  uint8_t v393[60]; // [esp+2634h] [ebp-1CCh] BYREF
  uint8_t v394[60]; // [esp+2670h] [ebp-190h] BYREF
  uint8_t v395[60]; // [esp+26ACh] [ebp-154h] BYREF
  uint8_t v396[60]; // [esp+26E8h] [ebp-118h] BYREF
  uint8_t v397[60]; // [esp+2724h] [ebp-DCh] BYREF
  uint8_t v398[60]; // [esp+2760h] [ebp-A0h] BYREF
  int v399; // [esp+279Ch] [ebp-64h] BYREF
  char v400; // [esp+27A0h] [ebp-60h]
  int v401; // [esp+27A4h] [ebp-5Ch]
  int v402; // [esp+27A8h] [ebp-58h]
  char v403; // [esp+27ACh] [ebp-54h]
  int v404; // [esp+27B0h] [ebp-50h]
  int v405; // [esp+27B4h] [ebp-4Ch] BYREF
  char v406; // [esp+27B8h] [ebp-48h]
  int v407; // [esp+27BCh] [ebp-44h]
  int v408; // [esp+27C0h] [ebp-40h] BYREF
  char v409; // [esp+27C4h] [ebp-3Ch]
  int v410; // [esp+27C8h] [ebp-38h]
  uint32_t v411[4]; // [esp+27CCh] [ebp-34h] BYREF
  int v412; // [esp+27DCh] [ebp-24h]
  int v413; // [esp+27E0h] [ebp-20h]
  int v414; // [esp+27E4h] [ebp-1Ch]
  int v415; // [esp+27E8h] [ebp-18h]
  void *v416; // [esp+27ECh] [ebp-14h]
  void *Block[3]; // [esp+27F0h] [ebp-10h] BYREF
  int v418; // [esp+27FCh] [ebp-4h]

  v418 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  Block[2] = &loc_6B10B3;
  Block[1] = ExceptionList;
  v6 = alloca(10228);
  v413 = 0;
  v412 = 0;
  v414 = 0;
  v415 = 0;
  v416 = nullptr;
  Block[0] = nullptr;
  v8 = a1;
  memset(&v411[1], 0, 12);
  v418 = 0;
  if ( a1 > 27662 )
  {
    if ( a1 <= 30253 )
    {
      if ( a1 == 30253 )
      {
LABEL_915:
        Block[0] = operator new(0x5B0u);
        v418 = 349;
        if ( Block[0] != nullptr )
        {
          v173 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = 94;
          v415 = 0x4000;
          v18 = sub_5144A0(v8, v173);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;
        if ( (v415 & 0x4000) != 0 )
          sub_445150(v326);
        sub_6048E0(4, 300, 1, 100);
        goto LABEL_269;
      }
      if ( a1 <= 29332 )
      {
        if ( a1 == 29332 )
        {
LABEL_1250:
          Block[0] = operator new(0x5B0u);
          v418 = 279;
          if ( Block[0] != nullptr )
          {
            v220 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 24;
            v414 = 0x1000000;
            v18 = sub_5144A0(v8, v220);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v414 & 0x1000000) == 0 )
            goto LABEL_1256;
          v79 = &v236;
          goto LABEL_1255;
        }
        if ( a1 <= 28255 )
        {
          if ( a1 == 28255 )
          {
            Block[0] = operator new(0x5B0u);
            v418 = 464;
            if ( Block[0] != nullptr )
            {
              v139 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -47;
              v416 = (void *)0x10000;
              v18 = sub_5144A0(95, v139);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( ((unsigned int)v416 & 0x10000) != 0 )
              sub_445150(v374);
            v408 = 18;
            v409 = 0;
            v410 = 1097859072;
            Block[0] = operator new(0x7Cu);
            v418 = 467;
            if ( Block[0] != nullptr )
              v87 = sub_5101B0(&v408, 1, 0, 1);
            else
              v87 = 0;
            v418 = 0;
            goto LABEL_607;
          }
          if ( a1 <= 27958 )
          {
            if ( a1 == 27958 )
              goto LABEL_664;
            if ( a1 <= 27926 )
            {
              if ( a1 != 27926 )
              {
                switch ( a1 )
                {
                  case 27674:
                    Block[0] = operator new(0x5B0u);
                    v418 = 323;
                    if ( Block[0] != nullptr )
                    {
                      v129 = sub_4E9B10(a4, a5, a3, a2);
                      LOBYTE(v418) = 68;
                      v415 = 64;
                      v18 = sub_5144A0(v8, v129);
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;
                    if ( (v415 & 0x40) != 0 )
                      sub_445150(v392);
                    sub_6048E0(0, 100, 4, 100);
                    goto LABEL_269;
                  case 27675:
                    Block[0] = operator new(0x5B0u);
                    v418 = 326;
                    if ( Block[0] != nullptr )
                    {
                      v130 = sub_4E9B10(a4, a5, a3, a2);
                      LOBYTE(v418) = 71;
                      v415 = 128;
                      v18 = sub_5177B0(v8, v130);
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;
                    if ( (v415 & 0x80u) != 0 )
                      sub_445150(v390);
                    goto LABEL_269;
                  case 27913:
                    Block[0] = operator new(0x5B0u);
                    LOBYTE(v418) = 12;
                    if ( Block[0] != nullptr )
                    {
                      v128 = sub_4E9B10(a4, a5, a3, a2);
                      LOBYTE(v418) = 13;
                      v413 = 8;
                      v18 = sub_5144A0(v8, v128);
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;
                    if ( (v413 & 8) != 0 )
                      sub_445150(v394);
                    v408 = 5;
                    v409 = 0;
                    v410 = 1127481344;
                    Block[0] = operator new(0x7Cu);
                    LOBYTE(v418) = 15;
                    if ( Block[0] == nullptr )
                      goto LABEL_605;
                    v87 = sub_5101B0(&v408, 1, 0, 1);
                    break;
                  case 27923:
                    goto LABEL_658;
                  default:
                    goto LABEL_155;
                }
                goto LABEL_606;
              }
LABEL_664:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = 43;
              if ( Block[0] != nullptr )
              {
                v132 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 44;
                v413 = 4096;
                v18 = sub_51AF20(v8, v132);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v413 & 0x1000) != 0 )
                sub_445150(v386);
              sub_605650(0, 5, 100, 12, 0, 12, 0);
              goto LABEL_269;
            }
            if ( a1 != 27928 )
            {
              if ( a1 != 27939 )
              {
                if ( a1 == 27957 )
                {
LABEL_658:
                  Block[0] = operator new(0x5B0u);
                  LOBYTE(v418) = 40;
                  if ( Block[0] != nullptr )
                  {
                    v131 = sub_4E9B10(a4, a5, a3, a2);
                    LOBYTE(v418) = 41;
                    v413 = 2048;
                    v18 = sub_5144A0(v8, v131);
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;
                  if ( (v413 & 0x800) != 0 )
                    sub_445150(v388);
                  sub_605650(0, 3, 100, 5, 0, -1, 1);
                  goto LABEL_269;
                }
                goto LABEL_155;
              }
LABEL_677:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = 46;
              if ( Block[0] != nullptr )
              {
                v134 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 47;
                v413 = 0x2000;
                v18 = sub_5144A0(v8, v134);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v413 & 0x2000) != 0 )
                sub_445150(v384);
              sub_6055A0(0, 3, 100, 50, 0, 40002);
              goto LABEL_269;
            }
LABEL_683:
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = 62;
            if ( Block[0] != nullptr )
            {
              v135 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 63;
              v413 = 0x40000;
              v18 = sub_5144A0(v8, v135);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v413 & 0x40000) != 0 )
              sub_445150(v382);
            v229 = 48003;
            v228 = 0;
            v227 = 8;
            v226 = 100;
            v224 = 10;
            goto LABEL_268;
          }
          if ( a1 <= 28220 )
          {
            if ( a1 != 28220 )
            {
              if ( a1 == 27961 )
                goto LABEL_683;
              if ( a1 == 27965 )
                goto LABEL_677;
              if ( a1 != 28203 )
                goto LABEL_155;
LABEL_675:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = 20;
              if ( Block[0] != nullptr )
              {
                v133 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 21;
                v413 = 32;
                v18 = sub_5144A0(v8, v133);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v413 & 0x20) != 0 )
                sub_445150(v376);
              v399 = 16;
              v400 = 0;
              v401 = 1092616192;
              v402 = 17;
              v403 = 0;
              v404 = 1092616192;
              v405 = 18;
              v406 = 0;
              v407 = 1092616192;
              v408 = 19;
              v409 = 0;
              v410 = 1092616192;
              Block[0] = operator new(0x7Cu);
              LOBYTE(v418) = 23;
              if ( Block[0] != nullptr )
              {
                v87 = sub_5101B0(&v399, 4, 0, 1);
                goto LABEL_606;
              }
              goto LABEL_605;
            }
            goto LABEL_700;
          }
          if ( a1 == 28227 )
            goto LABEL_675;
          if ( a1 == 28240 )
          {
LABEL_700:
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = 24;
            if ( Block[0] != nullptr )
            {
              v138 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 25;
              v413 = 64;
              v18 = sub_5144A0(v8, v138);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v413 & 0x40) != 0 )
              sub_445150(v378);
            sub_605650(1, 5, 100, 7, 0, 13, 0);
            v408 = 5;
            v410 = 1112014848;
            v409 = 0;
            Block[0] = operator new(0x7Cu);
            LOBYTE(v418) = 27;
            if ( Block[0] != nullptr )
            {
              v87 = sub_5101B0(&v408, 1, 0, 1);
              goto LABEL_606;
            }
            goto LABEL_605;
          }
          if ( a1 != 28251 )
            goto LABEL_155;
          Block[0] = operator new(0x5B0u);
          v418 = 513;
          if ( Block[0] != nullptr )
          {
            v136 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 2;
            v416 = (void *)0x80000000;
            v30 = sub_5144A0(91, v136);
          }
          else
          {
            v30 = 0;
          }
          v418 = 0;
          if ( (int)v416 < 0 )
            sub_445150(v380);
          v405 = 11;
          v406 = 0;
          v407 = 1107558400;
          v408 = 23;
          v409 = 0;
          v410 = 1107558400;
          Block[0] = operator new(0x7Cu);
          v418 = 516;
          if ( Block[0] != nullptr )
          {
            v137 = sub_5101B0(&v405, 2, 0, 1);
            v418 = 0;
            sub_6055F0(2, 100, 100, 0, v137, 0);
          }
          else
          {
            v418 = 0;
            sub_6055F0(2, 100, 100, 0, 0, 0);
          }
LABEL_219:
          sub_5E5260(v411);
          return v30;
        }
        if ( a1 <= 29061 )
        {
          if ( a1 != 29061 )
          {
            switch ( a1 )
            {
              case 29018:
              case 29053:
                Block[0] = operator new(0x5B0u);
                LOBYTE(v418) = 65;
                if ( Block[0] != nullptr )
                {
                  v141 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 66;
                  v413 = 0x80000;
                  v18 = sub_5151B0(v8, v141);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( (v413 & 0x80000) != 0 )
                  sub_445150(v370);
                goto LABEL_269;
              case 29020:
              case 29057:
                Block[0] = operator new(0x5B0u);
                LOBYTE(v418) = 59;
                if ( Block[0] != nullptr )
                {
                  v140 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 60;
                  v413 = 0x20000;
                  v18 = sub_5144A0(v8, v140);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( (v413 & 0x20000) != 0 )
                  sub_445150(v372);
                v229 = 48003;
                v228 = 0;
                v227 = 6;
                v226 = 100;
                v224 = 10;
                goto LABEL_268;
              case 29025:
              case 29060:
                Block[0] = operator new(0x5B0u);
                LOBYTE(v418) = -4;
                if ( Block[0] != nullptr )
                {
                  v142 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = -3;
                  v414 = 0x10000;
                  v18 = sub_5144A0(v8, v142);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( (v414 & 0x10000) != 0 )
                  sub_445150(v368);
                sub_6048E0(4, 30, 3, 100);
                goto LABEL_269;
              case 29030:
                break;
              case 29035:
                goto LABEL_767;
              default:
                goto LABEL_155;
            }
          }
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -1;
          if ( Block[0] != nullptr )
          {
            v143 = sub_4E9B10(a4, a5, a3, a2);
            v418 = 256;
            v414 = 0x20000;
            v18 = sub_5144A0(v8, v143);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v414 & 0x20000) != 0 )
            sub_445150(v366);
          v408 = 5;
          v409 = 0;
          v410 = 1132068864;
          v144 = operator new(0x7Cu);
          Block[0] = v144;
          v418 = 258;
          goto LABEL_874;
        }
        if ( a1 <= 29315 )
        {
          if ( a1 != 29315 )
          {
            if ( a1 == 29070 )
            {
LABEL_767:
              Block[0] = operator new(0x5B0u);
              v418 = 259;
              if ( Block[0] != nullptr )
              {
                v148 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 4;
                v414 = 0x40000;
                v18 = sub_5144A0(v8, v148);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v414 & 0x40000) != 0 )
                sub_445150(v360);
              v408 = 4;
              v409 = 1;
              v410 = 1106247680;
              Block[0] = operator new(0x7Cu);
              v418 = 262;
              if ( Block[0] != nullptr )
                v149 = sub_5101B0(&v408, 1, 30000, 1);
              else
                v149 = 0;
              v418 = 0;
              sub_6055F0(0, 2, 100, 0, v149, 0);
              sub_605650(1, 5, 100, 10, 0, 15, 0);
              goto LABEL_269;
            }
            if ( a1 != 29076 )
            {
              if ( a1 == 29081 )
              {
                Block[0] = operator new(0x5B0u);
                v418 = 468;
                if ( Block[0] != nullptr )
                {
                  v146 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = -43;
                  v416 = (void *)0x20000;
                  v18 = sub_5144A0(153, v146);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( ((unsigned int)v416 & 0x20000) != 0 )
                  sub_445150(v364);
                sub_6048E0(4, 100, 3, 100);
                goto LABEL_269;
              }
              goto LABEL_155;
            }
            v405 = 0;
            v406 = 0;
            v407 = 1101004800;
            v408 = 3;
            v409 = 0;
            v410 = 1101004800;
            Block[0] = operator new(0x5B0u);
            v418 = 345;
            if ( Block[0] != nullptr )
            {
              v147 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 90;
              v415 = 0x2000;
              v75 = sub_5144A0(148, v147);
            }
            else
            {
              v75 = 0;
            }
            v418 = 0;
            if ( (v415 & 0x2000) != 0 )
              sub_445150(v362);
            Block[0] = operator new(0x7Cu);
            v418 = 348;
            if ( Block[0] != nullptr )
            {
              v76 = sub_5101B0(&v405, 2, 0, 1);
              goto LABEL_309;
            }
            goto LABEL_308;
          }
LABEL_1216:
          Block[0] = operator new(0xCD0u);
          v418 = 263;
          if ( Block[0] != nullptr )
          {
            v215 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 8;
            v414 = 0x80000;
            v18 = sub_51B460(v8, v215);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v414 & 0x80000) != 0 )
            sub_445150(v250);
          goto LABEL_269;
        }
        if ( a1 != 29319 )
        {
          if ( a1 == 29327 )
          {
LABEL_1241:
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = -17;
            if ( Block[0] != nullptr )
            {
              v219 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -16;
              v414 = 4096;
              v18 = sub_516DE0(v8, v219);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v414 & 0x1000) != 0 )
              sub_445150(v240);
            goto LABEL_269;
          }
          if ( a1 == 29329 )
          {
LABEL_779:
            Block[0] = operator new(0x5B0u);
            v418 = 276;
            if ( Block[0] != nullptr )
            {
              v150 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 21;
              v414 = (int)&unk_800000;
              v18 = sub_5144A0(v8, v150);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( ((unsigned int)&unk_800000 & v414) != 0 )
              sub_445150(v238);
            sub_6048E0(0, 20, 3, 100);
            sub_6048E0(1, 30, 2, 100);
            goto LABEL_269;
          }
          goto LABEL_155;
        }
        goto LABEL_1231;
      }
      if ( a1 > 29921 )
      {
        if ( a1 > 30207 )
        {
          switch ( a1 )
          {
            case 30209:
            case 30230:
              Block[0] = operator new(0x5B0u);
              v418 = 314;
              if ( Block[0] != nullptr )
              {
                v171 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 59;
                v415 = 8;
                v18 = sub_5144A0(v8, v171);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v415 & 8) != 0 )
                sub_445150(v330);
              sub_6048E0(4, 44, 2, 100);
              sub_605650(0, 2, 100, 6, 0, 4, 1);
              goto LABEL_269;
            case 30220:
            case 30241:
              Block[0] = operator new(0xCD0u);
              v418 = 317;
              if ( Block[0] != nullptr )
              {
                v172 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 62;
                v415 = 16;
                v18 = sub_51B740(v8, v172);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v415 & 0x10) != 0 )
                sub_445150(v328);
              goto LABEL_269;
            case 30226:
              goto LABEL_879;
            case 30227:
              goto LABEL_899;
            case 30246:
              goto LABEL_915;
            default:
              goto LABEL_155;
          }
        }
        if ( a1 == 30207 )
        {
LABEL_899:
          Block[0] = operator new(0xCD0u);
          v418 = 311;
          if ( Block[0] != nullptr )
          {
            v170 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 56;
            v415 = 4;
            v18 = sub_515520(v8, v170);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v415 & 4) != 0 )
            sub_445150(v332);
          goto LABEL_269;
        }
        if ( a1 > 29962 )
        {
          if ( a1 == 29974 )
          {
            Block[0] = operator new(0x5B0u);
            v418 = 339;
            if ( Block[0] != nullptr )
            {
              v169 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 84;
              v415 = 2048;
              v18 = sub_5144A0(22, v169);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v415 & 0x800) == 0 )
              goto LABEL_893;
            v101 = &v336;
            goto LABEL_892;
          }
          if ( a1 == 29976 )
          {
            Block[0] = operator new(0x90Cu);
            v418 = 342;
            if ( Block[0] != nullptr )
            {
              v165 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 87;
              v415 = 4096;
              v166 = sub_514350(24, v165, 6, 0);
            }
            else
            {
              v166 = 0;
            }
            v418 = 0;
            if ( (v415 & 0x1000) != 0 )
              sub_445150(v338);
            v167 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v166 + 176))(v166);
            v168 = (double)sub_41A5E0(v167 + 112) * 0.25;
            sub_41C150((uint64_t)v168);
            sub_5E5260(v411);
            return v166;
          }
          if ( a1 != 30204 )
            goto LABEL_155;
LABEL_879:
          Block[0] = operator new(0x5B0u);
          v418 = 272;
          if ( Block[0] != nullptr )
          {
            v164 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 17;
            v414 = 0x400000;
            v18 = sub_5144A0(v8, v164);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v414 & 0x400000) != 0 )
            sub_445150(v334);
          v408 = 7;
          v409 = 0;
          v410 = 1106247680;
          v144 = operator new(0x7Cu);
          Block[0] = v144;
          v418 = 275;
LABEL_874:
          if ( v144 != nullptr )
            v145 = sub_5101B0(&v408, 1, 0, 1);
          else
            v145 = 0;
          v418 = 0;
          sub_6055F0(2, 100, 100, 0, v145, 0);
          goto LABEL_269;
        }
        if ( a1 == 29962 || a1 == 29928 )
        {
          Block[0] = operator new(0x5B0u);
          v418 = 307;
          if ( Block[0] != nullptr )
          {
            v163 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 52;
            v415 = 2;
            v18 = sub_5144A0(v8, v163);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v415 & 2) != 0 )
            sub_445150(v340);
          v408 = 10;
          v409 = 0;
          v410 = 1125515264;
          v144 = operator new(0x7Cu);
          Block[0] = v144;
          v418 = 310;
          goto LABEL_874;
        }
        if ( a1 == 29952 )
          goto LABEL_836;
        if ( a1 != 29955 )
          goto LABEL_155;
      }
      else if ( a1 != 29921 )
      {
        if ( a1 <= 29642 )
        {
          if ( a1 != 29642 )
          {
            if ( a1 <= 29627 )
            {
              if ( a1 != 29627 )
              {
                if ( a1 <= 29346 )
                {
                  switch ( a1 )
                  {
                    case 29346:
                      Block[0] = operator new(0xCD0u);
                      LOBYTE(v418) = -100;
                      if ( Block[0] != nullptr )
                      {
                        v152 = sub_4E9B10(a4, a5, a3, a2);
                        LOBYTE(v418) = -99;
                        v412 = 0x20000;
                        v18 = sub_517200(162, v152);
                      }
                      else
                      {
                        v18 = 0;
                      }
                      v418 = 0;
                      if ( (v412 & 0x20000) != 0 )
                        sub_445150(v358);
                      goto LABEL_269;
                    case 29335:
LABEL_1257:
                      Block[0] = operator new(0x5B0u);
                      v418 = 282;
                      if ( Block[0] != nullptr )
                      {
                        v221 = sub_4E9B10(a4, a5, a3, a2);
                        LOBYTE(v418) = 27;
                        v414 = 0x2000000;
                        v18 = sub_5144A0(v8, v221);
                      }
                      else
                      {
                        v18 = 0;
                      }
                      v418 = 0;
                      if ( (v414 & 0x2000000) != 0 )
                        sub_445150(v234);
                      sub_6048E0(3, 50, 2, 100);
                      v229 = 1;
                      v228 = 3;
                      break;
                    case 29344:
LABEL_791:
                      Block[0] = operator new(0x5B0u);
                      LOBYTE(v418) = -103;
                      if ( Block[0] != nullptr )
                      {
                        v151 = sub_4E9B10(a4, a5, a3, a2);
                        LOBYTE(v418) = -102;
                        v412 = 0x10000;
                        v18 = sub_5144A0(v8, v151);
                      }
                      else
                      {
                        v18 = 0;
                      }
                      v418 = 0;
                      if ( (v412 & 0x10000) != 0 )
                        sub_445150(v242);
                      sub_6048E0(2, 100, 2, 100);
                      v229 = 0;
                      v228 = 4;
                      break;
                    default:
                      goto LABEL_155;
                  }
                  goto LABEL_571;
                }
                if ( a1 != 29618 )
                  goto LABEL_155;
LABEL_799:
                Block[0] = operator new(0x5B0u);
                v418 = 285;
                if ( Block[0] != nullptr )
                {
                  v153 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 30;
                  v414 = 0x4000000;
                  v18 = sub_5144A0(v8, v153);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( (v414 & 0x4000000) != 0 )
                  sub_445150(v352);
                sub_605650(1, 20, 100, 3, 0, 11, 2);
                goto LABEL_269;
              }
              goto LABEL_817;
            }
            if ( a1 != 29628 )
            {
              if ( a1 != 29632 )
              {
                if ( a1 != 29633 )
                  goto LABEL_155;
LABEL_804:
                Block[0] = operator new(0x5B0u);
                v418 = 294;
                if ( Block[0] != nullptr )
                {
                  v154 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 39;
                  v414 = 0x20000000;
                  v18 = sub_5144A0(v8, v154);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( (v414 & 0x20000000) != 0 )
                  sub_445150(v346);
                sub_6048E0(4, 100, 1, 100);
                goto LABEL_269;
              }
LABEL_827:
              Block[0] = operator new(0x5B0u);
              v418 = 291;
              if ( Block[0] != nullptr )
              {
                v157 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 36;
                v414 = 0x10000000;
                v18 = sub_5144A0(v8, v157);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v414 & 0x10000000) != 0 )
                sub_445150(v350);
              v229 = 1;
              v228 = -1;
              goto LABEL_531;
            }
LABEL_811:
            Block[0] = operator new(0x5B0u);
            v418 = 288;
            if ( Block[0] != nullptr )
            {
              v155 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 33;
              v414 = 0x8000000;
              v18 = sub_5144A0(v8, v155);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v414 & 0x8000000) != 0 )
              sub_445150(v356);
            sub_6048E0(2, 40, 3, 100);
            sub_605650(0, 3, 100, 5, 0, 4, 1);
            goto LABEL_269;
          }
          goto LABEL_838;
        }
        if ( a1 <= 29662 )
        {
          switch ( a1 )
          {
            case 29662:
              goto LABEL_827;
            case 29654:
              goto LABEL_799;
            case 29658:
LABEL_817:
              Block[0] = operator new(0x5B0u);
              v418 = 269;
              if ( Block[0] != nullptr )
              {
                v156 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 14;
                v414 = 0x200000;
                v18 = sub_5144A0(v8, v156);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v414 & 0x200000) != 0 )
                sub_445150(v354);
              sub_6048E0(2, 40, 3, 100);
              goto LABEL_269;
            default:
              break;
          }
          if ( a1 != 29661 )
            goto LABEL_155;
          goto LABEL_811;
        }
        if ( a1 == 29667 )
          goto LABEL_804;
        if ( a1 == 29668 )
        {
LABEL_838:
          Block[0] = operator new(0x5B0u);
          v418 = 297;
          if ( Block[0] != nullptr )
          {
            v159 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 42;
            v414 = 0x40000000;
            v18 = sub_5144A0(v8, v159);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v414 & 0x40000000) != 0 )
            sub_445150(v348);
          sub_6048E0(0, 30, 5, 100);
          sub_6048E0(1, 30, 5, 100);
          goto LABEL_269;
        }
        if ( a1 != 29918 )
          goto LABEL_155;
LABEL_836:
        Block[0] = operator new(0x5B0u);
        v418 = 300;
        if ( Block[0] != nullptr )
        {
          v158 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = 45;
          v414 = 0x80000000;
          v18 = sub_5144A0(v8, v158);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;
        if ( v414 < 0 )
          sub_445150(v342);
        Block[0] = operator new(0x7Cu);
        v418 = 303;
        if ( Block[0] != nullptr )
          v162 = sub_4B3DF0(12, 0, 1176256512, 3000, 1);
        else
          v162 = 0;
        v418 = 0;
        sub_6055F0(0, 1, 100, 0, v162, 0);
        goto LABEL_269;
      }
      Block[0] = operator new(0x90Cu);
      v418 = 304;
      if ( Block[0] != nullptr )
      {
        v160 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = 49;
        v415 = 1;
        v10 = sub_514350(v8, v160, 12, 0);
      }
      else
      {
        v10 = 0;
      }
      v418 = 0;
      if ( (v415 & 1) != 0 )
        sub_445150(v344);
      v161 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 176))(v10);
      Block[0] = (void *)sub_41A5E0(v161 + 112);
      v12 = (double)(int)Block[0] * 0.1;
      goto LABEL_16;
    }
    if ( a1 <= 32236 )
    {
      if ( a1 != 32236 )
      {
        if ( a1 <= 31657 )
        {
          if ( a1 != 31657 )
          {
            if ( a1 <= 31354 )
            {
              if ( a1 != 31354 )
              {
                if ( a1 <= 31060 )
                {
                  if ( a1 != 31060 )
                  {
                    switch ( a1 )
                    {
                      case 31033:
                      case 31052:
                        Block[0] = operator new(0x5B0u);
                        LOBYTE(v418) = 77;
                        if ( Block[0] != nullptr )
                        {
                          v174 = sub_4E9B10(a4, a5, a3, a2);
                          LOBYTE(v418) = 78;
                          v413 = (int)&unk_800000;
                          v18 = sub_5144A0(v8, v174);
                        }
                        else
                        {
                          v18 = 0;
                        }
                        v418 = 0;
                        if ( ((unsigned int)&unk_800000 & v413) != 0 )
                          sub_445150(v324);
                        sub_6048E0(0, 20, 2, 100);
                        goto LABEL_269;
                      case 31037:
                        break;
                      case 31041:
                        goto LABEL_947;
                      default:
                        goto LABEL_155;
                    }
                  }
                  Block[0] = operator new(0x5B0u);
                  LOBYTE(v418) = 80;
                  if ( Block[0] != nullptr )
                  {
                    v175 = sub_4E9B10(a4, a5, a3, a2);
                    LOBYTE(v418) = 81;
                    v413 = 0x1000000;
                    v18 = sub_5144A0(v8, v175);
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;
                  if ( (v413 & 0x1000000) != 0 )
                    sub_445150(v322);
                  sub_6048E0(2, 50, 5, 100);
                  goto LABEL_269;
                }
                if ( a1 == 31068 )
                {
LABEL_947:
                  Block[0] = operator new(0x5B0u);
                  LOBYTE(v418) = 113;
                  if ( Block[0] != nullptr )
                  {
                    v177 = sub_4E9B10(a4, a5, a3, a2);
                    LOBYTE(v418) = 114;
                    v412 = 8;
                    v18 = sub_5144A0(v8, v177);
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;
                  if ( (v412 & 8) != 0 )
                    sub_445150(v320);
                  v408 = 5;
                  v409 = 0;
                  v410 = 1137180672;
                  Block[0] = operator new(0x7Cu);
                  LOBYTE(v418) = 116;
                  if ( Block[0] != nullptr )
                  {
                    v87 = sub_5101B0(&v408, 1, 0, 1);
                    goto LABEL_606;
                  }
                  goto LABEL_605;
                }
                if ( a1 != 31333 )
                {
                  if ( a1 != 31340 )
                    goto LABEL_155;
                  goto LABEL_945;
                }
              }
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = 83;
              if ( Block[0] != nullptr )
              {
                v178 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 84;
                v413 = 0x2000000;
                v18 = sub_5144A0(v8, v178);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v413 & 0x2000000) == 0 )
              {
LABEL_988:
                sub_605650(0, 1, 100, 5, 0, 13, 0);
                goto LABEL_269;
              }
              v179 = &v318;
LABEL_987:
              sub_445150(v179);
              goto LABEL_988;
            }
            if ( a1 <= 31632 )
            {
              if ( a1 != 31632 )
              {
                if ( a1 != 31365 )
                {
                  if ( a1 == 31374 )
                  {
                    Block[0] = operator new(0x5B0u);
                    v418 = 355;
                    if ( Block[0] != nullptr )
                    {
                      v181 = sub_4E9B10(a4, a5, a3, a2);
                      LOBYTE(v418) = 100;
                      v415 = 0x10000;
                      v18 = sub_5144A0(142, v181);
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;
                    if ( (v415 & 0x10000) != 0 )
                      sub_445150(v314);
                    sub_6055A0(0, 2, 100, 80, 0, 40002);
                    goto LABEL_269;
                  }
                  if ( a1 == 31630 )
                  {
                    Block[0] = operator new(0x5B0u);
                    LOBYTE(v418) = 104;
                    if ( Block[0] != nullptr )
                    {
                      v180 = sub_4E9B10(a4, a5, a3, a2);
                      LOBYTE(v418) = 105;
                      v412 = 1;
                      v18 = sub_514EF0(142, v180);
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;
                    if ( (v412 & 1) != 0 )
                      sub_445150(v316);
                    goto LABEL_269;
                  }
                  goto LABEL_155;
                }
LABEL_945:
                Block[0] = operator new(0x5B0u);
                LOBYTE(v418) = 101;
                if ( Block[0] != nullptr )
                {
                  v176 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 102;
                  v413 = 0x80000000;
                  v18 = sub_5144A0(v8, v176);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( v413 < 0 )
                  sub_445150(v312);
                sub_6055A0(0, 2, 100, 20, 0, 40002);
                goto LABEL_269;
              }
              goto LABEL_982;
            }
            if ( a1 != 31636 )
            {
              if ( a1 != 31637 )
              {
                if ( a1 != 31653 )
                  goto LABEL_155;
LABEL_982:
                Block[0] = operator new(0x5B0u);
                LOBYTE(v418) = 86;
                if ( Block[0] != nullptr )
                {
                  v182 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 87;
                  v413 = 0x4000000;
                  v18 = sub_5144A0(v8, v182);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( (v413 & 0x4000000) == 0 )
                  goto LABEL_988;
                v179 = &v310;
                goto LABEL_987;
              }
LABEL_1004:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = 89;
              if ( Block[0] != nullptr )
              {
                v184 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 90;
                v413 = 0x8000000;
                v18 = sub_5144A0(v8, v184);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v413 & 0x8000000) != 0 )
                sub_445150(v306);
              sub_605650(1, 10, 100, 1, 0, 4, 0);
              goto LABEL_269;
            }
          }
          Block[0] = operator new(0x90Cu);
          LOBYTE(v418) = 107;
          if ( Block[0] != nullptr )
          {
            v183 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 108;
            v412 = 2;
            v18 = sub_514350(v8, v183, 12, 0);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v412 & 2) != 0 )
            sub_445150(v308);
          sub_41C150(100);
          goto LABEL_269;
        }
        if ( a1 <= 31957 )
        {
          if ( a1 == 31957 )
            goto LABEL_1022;
          if ( a1 <= 31939 )
          {
            if ( a1 != 31939 )
            {
              if ( a1 <= 31935 )
              {
                if ( a1 != 31935 )
                {
                  if ( a1 == 31661 )
                    goto LABEL_1004;
                  if ( a1 != 31934 )
                    goto LABEL_155;
LABEL_1016:
                  Block[0] = operator new(0x5B0u);
                  LOBYTE(v418) = 92;
                  if ( Block[0] != nullptr )
                  {
                    v186 = sub_4E9B10(a4, a5, a3, a2);
                    LOBYTE(v418) = 93;
                    v413 = 0x10000000;
                    v18 = sub_5144A0(v8, v186);
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;
                  if ( (v413 & 0x10000000) != 0 )
                    sub_445150(v304);
                  sub_6048E0(4, 30, 2, 100);
                  goto LABEL_269;
                }
LABEL_1022:
                Block[0] = operator new(0x5B0u);
                LOBYTE(v418) = 95;
                if ( Block[0] != nullptr )
                {
                  v187 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 96;
                  v413 = 0x20000000;
                  v18 = sub_5144A0(v8, v187);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( (v413 & 0x20000000) != 0 )
                  sub_445150(v302);
                sub_6048E0(0, 20, 2, 100);
                goto LABEL_269;
              }
              if ( a1 != 31938 )
                goto LABEL_155;
LABEL_1011:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = 110;
              if ( Block[0] != nullptr )
              {
                v185 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 111;
                v412 = 4;
                v18 = sub_5144A0(v8, v185);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v412 & 4) != 0 )
                sub_445150(v296);
              v229 = 48001;
              v228 = 0;
              v227 = 10;
              goto LABEL_267;
            }
LABEL_1033:
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = 98;
            if ( Block[0] != nullptr )
            {
              v188 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 99;
              v413 = 0x40000000;
              v18 = sub_5144A0(v8, v188);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v413 & 0x40000000) != 0 )
              sub_445150(v300);
            sub_605650(1, 4, 100, 4, 0, 3, 2);
            goto LABEL_269;
          }
          if ( a1 != 31940 )
          {
            if ( a1 != 31941 )
            {
              if ( a1 != 31951 )
                goto LABEL_155;
              goto LABEL_1016;
            }
LABEL_1054:
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = 117;
            if ( Block[0] != nullptr )
            {
              v191 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 118;
              v412 = 16;
              v18 = sub_5150B0(v8, v191);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v412 & 0x10) != 0 )
              sub_445150(v294);
            goto LABEL_269;
          }
LABEL_1039:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -14;
          if ( Block[0] != nullptr )
          {
            v189 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -13;
            v414 = 0x2000;
            v18 = sub_5144A0(v8, v189);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v414 & 0x2000) != 0 )
            sub_445150(v298);
          sub_6055A0(0, 2, 100, 30, 0, 40002);
          goto LABEL_269;
        }
        if ( a1 <= 31967 )
        {
          if ( a1 == 31967 )
            goto LABEL_1054;
          if ( a1 == 31962 )
            goto LABEL_1011;
          if ( a1 != 31965 )
          {
            if ( a1 != 31966 )
              goto LABEL_155;
            goto LABEL_1033;
          }
          goto LABEL_1039;
        }
        if ( a1 == 31977 )
        {
          Block[0] = operator new(0x5B0u);
          v418 = 474;
          if ( Block[0] != nullptr )
          {
            v192 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -37;
            v416 = (void *)0x80000;
            v30 = sub_5144A0(233, v192);
          }
          else
          {
            v30 = 0;
          }
          v418 = 0;
          if ( ((unsigned int)v416 & 0x80000) != 0 )
            sub_445150(v292);
          v408 = 18;
          v409 = 0;
          v410 = 1092616192;
          Block[0] = operator new(0x7Cu);
          v418 = 477;
          if ( Block[0] != nullptr )
            v193 = sub_5101B0(&v408, 1, 0, 1);
          else
            v193 = 0;
          v418 = 0;
          sub_6055F0(2, 100, 100, 0, v193, 0);
          goto LABEL_219;
        }
        if ( a1 == 31978 )
          goto LABEL_1054;
        if ( a1 != 32231 )
          goto LABEL_155;
LABEL_1052:
        Block[0] = operator new(0x5B0u);
        LOBYTE(v418) = -11;
        if ( Block[0] != nullptr )
        {
          v190 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = -10;
          v414 = 0x4000;
          v18 = sub_5144A0(v8, v190);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;
        if ( (v414 & 0x4000) != 0 )
          sub_445150(v288);
        v408 = 18;
        v409 = 0;
        v410 = 1092616192;
        Block[0] = operator new(0x7Cu);
        LOBYTE(v418) = -8;
        if ( Block[0] != nullptr )
        {
          v87 = sub_5101B0(&v408, 1, 0, 1);
          goto LABEL_606;
        }
        goto LABEL_605;
      }
LABEL_1078:
      Block[0] = operator new(0x5B0u);
      LOBYTE(v418) = -7;
      if ( Block[0] != nullptr )
      {
        v194 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -6;
        v414 = 0x8000;
        v18 = sub_5144A0(v8, v194);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;
      if ( (v414 & 0x8000) != 0 )
        sub_445150(v290);
      sub_6055A0(0, 3, 100, 50, 0, 40002);
      goto LABEL_269;
    }
    if ( a1 > 33643 )
    {
      if ( a1 > 39356 )
      {
        switch ( a1 )
        {
          case 39357:
            goto LABEL_791;
          case 39361:
            goto LABEL_1241;
          case 39364:
            goto LABEL_779;
          case 39365:
            goto LABEL_1250;
          case 39368:
            goto LABEL_1257;
          case 39378:
            Block[0] = operator new(0x5B0u);
            v418 = 352;
            if ( Block[0] != nullptr )
            {
              v222 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 97;
              v415 = 0x8000;
              v18 = sub_517A60(v8, v222);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v415 & 0x8000) != 0 )
              sub_445150(v232);
            goto LABEL_269;
          case 39381:
            Block[0] = operator new(0x5B0u);
            v418 = 471;
            if ( Block[0] != nullptr )
            {
              v223 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -40;
              v416 = (void *)0x40000;
              v18 = sub_5144A0(v8, v223);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( ((unsigned int)v416 & 0x40000) == 0 )
              goto LABEL_1274;
            v116 = &v230;
            break;
          default:
            goto LABEL_155;
        }
        goto LABEL_1273;
      }
      if ( a1 != 39356 )
      {
        if ( a1 <= 33933 )
        {
          switch ( a1 )
          {
            case 33933:
              Block[0] = operator new(0x5B0u);
              v418 = 420;
              if ( Block[0] != nullptr )
              {
                v214 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -91;
                v416 = (void *)4;
                v18 = sub_5144A0(141, v214);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( ((uint8_t)v416 & 4) != 0 )
                sub_445150(v252);
              sub_605650(1, 3, 100, 12, 0, 16, 2);
              goto LABEL_269;
            case 33926:
              Block[0] = (void *)3;
              sub_431230(Block);
              Block[0] = operator new(0x5B0u);
              v418 = 386;
              if ( Block[0] != nullptr )
              {
                v416 = &v226;
                sub_435020(v411);
                LOBYTE(v418) = -125;
                v213 = sub_4E9B10(a4, a5, a3, a2);
                v415 = 0x4000000;
                v418 = 389;
                v18 = sub_517D90(134, v213, v226, (void *)v227, v228, v229);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v415 & 0x4000000) != 0 )
                sub_445150(v254);
              goto LABEL_269;
            case 33931:
              Block[0] = (void *)37;
              sub_431230(Block);
              Block[0] = operator new(0x5D4u);
              v418 = 410;
              if ( Block[0] != nullptr )
              {
                v416 = &v226;
                sub_435020(v411);
                LOBYTE(v418) = -101;
                v212 = (void *)sub_4E9B10(a4, a5, a3, a2);
                v416 = (void *)1;
                v418 = 413;
                v18 = sub_518360(139, v212, v226, (void *)v227, v228, v229);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( ((uint8_t)v416 & 1) != 0 )
                sub_445150(v256);
              goto LABEL_269;
            case 33932:
              Block[0] = (void *)26;
              sub_431230(Block);
              Block[0] = operator new(0x5B0u);
              v418 = 415;
              if ( Block[0] != nullptr )
              {
                v416 = &v226;
                sub_435020(v411);
                LOBYTE(v418) = -96;
                v211 = sub_4E9B10(a4, a5, a3, a2);
                v416 = (void *)2;
                v418 = 418;
                v18 = sub_518100(140, v211, v226, (void *)v227, v228, v229);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( ((uint8_t)v416 & 2) != 0 )
                sub_445150(v258);
              goto LABEL_269;
            default:
              break;
          }
          goto LABEL_155;
        }
        if ( a1 == 33936 )
        {
          Block[0] = operator new(0x5B0u);
          v418 = 423;
          if ( Block[0] != nullptr )
          {
            v217 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -88;
            v416 = (void *)8;
            v18 = sub_518DE0(144, v217);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( ((uint8_t)v416 & 8) != 0 )
            sub_445150(v246);
          goto LABEL_269;
        }
        if ( a1 == 33943 )
        {
          Block[0] = operator new(0x5B4u);
          v418 = 481;
          if ( Block[0] != nullptr )
          {
            v216 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -30;
            v416 = (void *)0x200000;
            v30 = sub_519560(151, v216);
          }
          else
          {
            v30 = 0;
          }
          v418 = 0;
          if ( ((unsigned int)v416 & 0x200000) != 0 )
            sub_445150(v248);
          goto LABEL_219;
        }
        if ( a1 != 39352 )
          goto LABEL_155;
        goto LABEL_1216;
      }
LABEL_1231:
      Block[0] = operator new(0x5B0u);
      v418 = 266;
      if ( Block[0] != nullptr )
      {
        v218 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = 11;
        v414 = 0x100000;
        v18 = sub_51B540(v8, v218);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;
      if ( (v414 & 0x100000) != 0 )
        sub_445150(v244);
      goto LABEL_269;
    }
    if ( a1 != 33643 )
    {
      if ( a1 <= 33333 )
      {
        if ( a1 == 33333 )
        {
          Block[0] = operator new(0x5B0u);
          v418 = 429;
          if ( Block[0] != nullptr )
          {
            v202 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -82;
            v416 = (void *)32;
            v18 = sub_5144A0(53, v202);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( ((uint8_t)v416 & 0x20) != 0 )
            sub_445150(v274);
          sub_605650(0, 3, 100, 12, 0, 12, 0);
          goto LABEL_269;
        }
        if ( a1 > 33033 )
        {
          if ( a1 == 33035 )
          {
            Block[0] = (void *)13;
            sub_431230(Block);
            Block[0] = operator new(0x5D4u);
            v418 = 438;
            if ( Block[0] != nullptr )
            {
              v416 = &v226;
              sub_435020(v411);
              LOBYTE(v418) = -73;
              v201 = (void *)sub_4E9B10(a4, a5, a3, a2);
              v416 = (void *)256;
              v418 = 441;
              v18 = sub_518B20(11, v201, v226, (void *)v227, v228, v229);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (BYTE1(v416) & 1) != 0 )
              sub_445150(v276);
            goto LABEL_269;
          }
          if ( a1 == 33327 )
          {
            Block[0] = operator new(0x5B0u);
            v418 = 391;
            if ( Block[0] != nullptr )
            {
              v200 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -120;
              v415 = 0x8000000;
              v18 = sub_5144A0(47, v200);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v415 & 0x8000000) != 0 )
              sub_445150(v278);
            sub_6055A0(0, 1, 100, 5, 0, 46001);
            goto LABEL_269;
          }
          if ( a1 != 33331 )
            goto LABEL_155;
          Block[0] = operator new(0x90Cu);
          v418 = 426;
          if ( Block[0] != nullptr )
          {
            v198 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -85;
            v416 = (void *)16;
            v10 = sub_514350(51, v198, 7, 0);
          }
          else
          {
            v10 = 0;
          }
          v418 = 0;
          if ( ((uint8_t)v416 & 0x10) != 0 )
            sub_445150(v280);
          v199 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 176))(v10);
          Block[0] = (void *)sub_41A5E0(v199 + 112);
          v12 = (double)(int)Block[0] * 0.5;
          goto LABEL_16;
        }
        if ( a1 == 33033 )
        {
          Block[0] = operator new(0x5B0u);
          v418 = 435;
          if ( Block[0] != nullptr )
          {
            v197 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -76;
            v416 = (void *)128;
            v18 = sub_5144A0(9, v197);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (char)v416 < 0 )
            sub_445150(v282);
          sub_605650(0, 3, 100, 12, 0, 13, 0);
          goto LABEL_269;
        }
        if ( a1 > 32274 )
        {
          if ( a1 == 33027 )
          {
            Block[0] = operator new(0x5B0u);
            v418 = 394;
            if ( Block[0] != nullptr )
            {
              v196 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -117;
              v415 = 0x10000000;
              v18 = sub_5144A0(3, v196);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v415 & 0x10000000) != 0 )
              sub_445150(v284);
            sub_6048E0(4, 60, 4, 100);
            goto LABEL_269;
          }
          goto LABEL_155;
        }
        if ( a1 == 32274 )
        {
          Block[0] = operator new(0x5B0u);
          v418 = 358;
          if ( Block[0] != nullptr )
          {
            v195 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 103;
            v415 = 0x20000;
            v18 = sub_5144A0(18, v195);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v415 & 0x20000) != 0 )
            sub_445150(v286);
          sub_6055A0(0, 3, 100, 200, 0, 40002);
          goto LABEL_269;
        }
        if ( a1 == 32249 )
          goto LABEL_1052;
        if ( a1 != 32257 )
          goto LABEL_155;
        goto LABEL_1078;
      }
      if ( a1 <= 33630 )
      {
        switch ( a1 )
        {
          case 33630:
            Block[0] = (void *)17;
            sub_431230(Block);
            Block[0] = (void *)31;
            sub_431230(Block);
            Block[0] = operator new(0x5B0u);
            v418 = 383;
            if ( Block[0] != nullptr )
            {
              v207 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 0x80;
              v415 = 0x2000000;
              v18 = sub_517C10(94, v207, (int)v411);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v415 & 0x2000000) != 0 )
              sub_445150(v266);
            goto LABEL_269;
          case 33335:
            Block[0] = (void *)4;
            sub_431230(Block);
            Block[0] = operator new(0x5B0u);
            v418 = 432;
            if ( Block[0] != nullptr )
            {
              v206 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -79;
              v416 = (void *)64;
              v18 = sub_514520(55, v206, (int)v411);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( ((uint8_t)v416 & 0x40) != 0 )
              sub_445150(v268);
            sub_605650(0, 5, 100, 12, 0, 3, 1);
            goto LABEL_269;
          case 33627:
            Block[0] = (void *)31;
            sub_431230(Block);
            Block[0] = operator new(0x5B0u);
            v418 = 379;
            if ( Block[0] != nullptr )
            {
              v204 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 124;
              v415 = 0x1000000;
              v18 = sub_514520(91, v204, (int)v411);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v415 & 0x1000000) != 0 )
              sub_445150(v270);
            Block[0] = operator new(0x7Cu);
            v418 = 382;
            if ( Block[0] != nullptr )
              v205 = sub_4B3DF0(1, 0, 1112014848, 30000, 1);
            else
              v205 = 0;
            v418 = 0;
            sub_6055F0(4, 3, 100, 0, v205, 0);
            goto LABEL_269;
          default:
            break;
        }
        if ( a1 != 33628 )
          goto LABEL_155;
        Block[0] = operator new(0x5B0u);
        LOBYTE(v418) = 16;
        if ( Block[0] != nullptr )
        {
          v203 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = 17;
          v413 = 16;
          v18 = sub_5144A0(92, v203);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;
        if ( (v413 & 0x10) != 0 )
          sub_445150(v272);
        v408 = 18;
        v409 = 0;
        v410 = 1092616192;
        Block[0] = operator new(0x7Cu);
        LOBYTE(v418) = 19;
        if ( Block[0] != nullptr )
        {
          v87 = sub_5101B0(&v408, 1, 0, 1);
          goto LABEL_606;
        }
        goto LABEL_605;
      }
      if ( a1 != 33635 )
      {
        if ( a1 == 33636 )
        {
          Block[0] = operator new(0x5B0u);
          v418 = 407;
          if ( Block[0] != nullptr )
          {
            v209 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -104;
            v415 = 0x80000000;
            v18 = sub_518FB0(100, v209);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( v415 < 0 )
            sub_445150(v262);
          goto LABEL_269;
        }
        if ( a1 != 33641 )
          goto LABEL_155;
        Block[0] = (void *)26;
        sub_431230(Block);
        Block[0] = operator new(0x5B0u);
        v418 = 478;
        if ( Block[0] != nullptr )
        {
          v208 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = -33;
          v416 = (void *)0x100000;
          v30 = sub_514520(105, v208, (int)v411);
        }
        else
        {
          v30 = 0;
        }
        v418 = 0;
        if ( ((unsigned int)v416 & 0x100000) != 0 )
          sub_445150(v264);
        sub_605650(0, 3, 100, 12, 0, 4, 1);
        goto LABEL_219;
      }
    }
    Block[0] = (void *)26;
    sub_431230(Block);
    Block[0] = operator new(0x5D8u);
    v418 = 402;
    if ( Block[0] != nullptr )
    {
      v416 = &v226;
      sub_435020(v411);
      LOBYTE(v418) = -109;
      v210 = (void *)sub_4E9B10(a4, a5, a3, a2);
      v415 = 0x40000000;
      v418 = 405;
      v18 = sub_5186C0(v8, v210, v226, (void *)v227, v228, v229);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;
    if ( (v415 & 0x40000000) != 0 )
      sub_445150(v260);
    goto LABEL_269;
  }
  if ( a1 == 27662 )
  {
LABEL_620:
    Block[0] = operator new(0x5B0u);
    LOBYTE(v418) = 56;
    if ( Block[0] != nullptr )
    {
      v127 = sub_4E9B10(a4, a5, a3, a2);
      LOBYTE(v418) = 57;
      v413 = 0x10000;
      v18 = sub_5144A0(v8, v127);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;
    if ( (v413 & 0x10000) != 0 )
      sub_445150(v396);
    v229 = 0;
    v228 = 12;
LABEL_619:
    sub_605650(1, 10, 100, 7, 0, v228, v229);
    goto LABEL_269;
  }
  if ( a1 > 14064 )
  {
    if ( a1 <= 26027 )
    {
      if ( a1 != 26027 )
      {
        if ( a1 <= 22053 )
        {
          if ( a1 == 22053 )
          {
            Block[0] = operator new(0x544u);
            LOBYTE(v418) = 1;
            if ( Block[0] != nullptr )
            {
              v89 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 2;
              v413 = 1;
              v18 = sub_51AD20(37, v89);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v413 & 1) != 0 )
              sub_445150(v345);
            goto LABEL_269;
          }
          if ( a1 <= 20060 )
          {
            if ( a1 != 20060 )
            {
              if ( a1 <= 14457 )
              {
                if ( a1 != 14457 )
                {
                  if ( a1 <= 14079 )
                  {
                    if ( a1 == 14079 )
                      goto LABEL_343;
                    if ( a1 == 14069 )
                      goto LABEL_299;
                    if ( a1 != 14074 )
                      goto LABEL_155;
                    goto LABEL_335;
                  }
                  if ( a1 != 14435 )
                    goto LABEL_155;
                }
                Block[0] = operator new(0xCD0u);
                LOBYTE(v418) = -127;
                if ( Block[0] != nullptr )
                {
                  v82 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = -126;
                  v412 = 256;
                  v18 = sub_5141B0(v8, v82, 0, 1);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;
                if ( (v412 & 0x100) != 0 )
                  sub_445150(v349);
                sub_513B10(2, 1);
                sub_41C150(50);
                goto LABEL_269;
              }
              if ( a1 == 14468 )
              {
                Block[0] = operator new(0xCD0u);
                v418 = 370;
                if ( Block[0] != nullptr )
                {
                  v84 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 115;
                  v415 = 0x200000;
                  v10 = sub_5141B0(132, v84, 0, 1);
                }
                else
                {
                  v10 = 0;
                }
                v418 = 0;
                if ( (v415 & 0x200000) != 0 )
                  sub_445150(v289);
                sub_513B10(2, 1);
                v229 = 150;
                goto LABEL_17;
              }
              if ( a1 != 20016 )
              {
                if ( a1 != 20027 )
                  goto LABEL_155;
                goto LABEL_359;
              }
            }
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = -52;
            if ( Block[0] != nullptr )
            {
              v85 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -51;
              v414 = 2;
              v18 = sub_515A50(v8, v85);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v414 & 2) != 0 )
              sub_445150(v347);
            goto LABEL_269;
          }
          if ( a1 <= 22031 )
          {
            if ( a1 == 22031 )
            {
LABEL_409:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = -38;
              if ( Block[0] != nullptr )
              {
                v91 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -37;
                v414 = 32;
                v18 = sub_516980(v8, v91);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v414 & 0x20) != 0 )
                sub_445150(v237);
              goto LABEL_269;
            }
            if ( a1 != 20064 )
            {
              if ( a1 != 22017 )
              {
                if ( a1 == 22030 )
                {
LABEL_377:
                  Block[0] = operator new(0x5B0u);
                  LOBYTE(v418) = -41;
                  if ( Block[0] != nullptr )
                  {
                    v86 = sub_4E9B10(a4, a5, a3, a2);
                    LOBYTE(v418) = -40;
                    v414 = 16;
                    v18 = sub_515CA0(v8, v86);
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;
                  if ( (v414 & 0x10) != 0 )
                    sub_445150(v343);
                  goto LABEL_269;
                }
                goto LABEL_155;
              }
LABEL_399:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = -45;
              if ( Block[0] != nullptr )
              {
                v90 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -44;
                v414 = 8;
                v18 = sub_5144A0(v8, v90);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v414 & 8) != 0 )
                sub_445150(v287);
              v408 = 1;
              v409 = 0;
              v410 = 1092616192;
              Block[0] = operator new(0x7Cu);
              LOBYTE(v418) = -42;
              if ( Block[0] != nullptr )
              {
                v87 = sub_5101B0(&v408, 1, 0, 1);
                goto LABEL_606;
              }
LABEL_605:
              v87 = 0;
              goto LABEL_606;
            }
LABEL_359:
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = -49;
            if ( Block[0] != nullptr )
            {
              v83 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -48;
              v414 = 4;
              v18 = sub_5144A0(v8, v83);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v414 & 4) != 0 )
              sub_445150(v259);
            v408 = 23;
            v409 = 0;
            v410 = 1092616192;
            Block[0] = operator new(0x7Cu);
            LOBYTE(v418) = -46;
            if ( Block[0] != nullptr )
            {
              v87 = sub_5101B0(&v408, 1, 0, 1);
LABEL_606:
              LOBYTE(v418) = 0;
LABEL_607:
              sub_6055F0(2, 100, 100, 0, v87, 0);
              goto LABEL_269;
            }
            goto LABEL_605;
          }
          if ( a1 != 22038 )
          {
            if ( a1 == 22040 )
            {
LABEL_414:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = -32;
              if ( Block[0] != nullptr )
              {
                v92 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -31;
                v414 = 128;
                v18 = sub_516610(v8, v92);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v414 & 0x80u) != 0 )
                sub_445150(v341);
              goto LABEL_269;
            }
            if ( a1 != 22047 )
              goto LABEL_155;
LABEL_387:
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = -29;
            if ( Block[0] != nullptr )
            {
              v88 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -28;
              v414 = 256;
              v18 = sub_5144A0(v8, v88);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v414 & 0x100) != 0 )
              sub_445150(v339);
            sub_6055A0(1, 10, 100, 100, 0, 40002);
            sub_605650(1, 10, 100, 5, 0, 4, 0);
            goto LABEL_269;
          }
LABEL_419:
          Block[0] = operator new(0xCD0u);
          LOBYTE(v418) = -35;
          if ( Block[0] != nullptr )
          {
            v93 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -34;
            v414 = 64;
            v10 = sub_515E80(v8, v93, 0, 1);
          }
          else
          {
            v10 = 0;
          }
          v418 = 0;
          if ( (v414 & 0x40) != 0 )
          {
            v26 = &v285;
LABEL_62:
            sub_445150(v26);
          }
LABEL_63:
          sub_513B10(2, 1);
          v229 = 300;
          goto LABEL_17;
        }
        if ( a1 <= 24027 )
        {
          if ( a1 != 24027 )
          {
            if ( a1 <= 22078 )
            {
              if ( a1 != 22078 )
              {
                switch ( a1 )
                {
                  case 22061:
                    goto LABEL_399;
                  case 22069:
                    goto LABEL_409;
                  case 22072:
                    goto LABEL_377;
                  case 22076:
                    goto LABEL_414;
                  default:
                    goto LABEL_155;
                }
              }
              goto LABEL_419;
            }
            if ( a1 == 22079 )
              goto LABEL_387;
            if ( a1 != 24014 )
            {
              if ( a1 != 24023 )
                goto LABEL_155;
              goto LABEL_437;
            }
            goto LABEL_442;
          }
LABEL_448:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -23;
          if ( Block[0] != nullptr )
          {
            v96 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -22;
            v414 = 1024;
            v18 = sub_5144A0(v8, v96);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v414 & 0x400) != 0 )
            sub_445150(v283);
          v229 = 20011;
          v228 = 0;
          v227 = 3;
          v226 = 100;
          v224 = 5;
          goto LABEL_268;
        }
        if ( a1 > 24070 )
        {
          if ( a1 != 24081 )
          {
            if ( a1 == 26024 )
            {
              Block[0] = operator new(0x5B0u);
              v418 = 452;
              if ( Block[0] != nullptr )
              {
                v98 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -59;
                v416 = (void *)4096;
                v18 = sub_519310(168, v98);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (BYTE1(v416) & 0x10) != 0 )
                sub_445150(v243);
              goto LABEL_269;
            }
            if ( a1 == 26026 )
            {
              Block[0] = operator new(0x5B0u);
              v418 = 455;
              if ( Block[0] != nullptr )
              {
                v97 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -56;
                v416 = (void *)0x2000;
                v18 = sub_519440(170, v97);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (BYTE1(v416) & 0x20) != 0 )
                sub_445150(v335);
              goto LABEL_269;
            }
            goto LABEL_155;
          }
        }
        else
        {
          if ( a1 == 24070 )
            goto LABEL_448;
          if ( a1 != 24046 )
          {
            if ( a1 != 24060 )
            {
              if ( a1 != 24064 )
                goto LABEL_155;
LABEL_437:
              Block[0] = operator new(0x5D4u);
              LOBYTE(v418) = -26;
              if ( Block[0] != nullptr )
              {
                v94 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -25;
                v414 = 512;
                v18 = sub_516F30(v8, v94);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v414 & 0x200) != 0 )
                sub_445150(v257);
              goto LABEL_269;
            }
LABEL_442:
            Block[0] = operator new(0x5B0u);
            v418 = 449;
            if ( Block[0] != nullptr )
            {
              v95 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -62;
              v416 = (void *)2048;
              v18 = sub_5144A0(v8, v95);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (BYTE1(v416) & 8) != 0 )
              sub_445150(v337);
            sub_605650(0, 2, 100, 3, 0, 11, 1);
            goto LABEL_269;
          }
        }
        Block[0] = operator new(0xCD0u);
        LOBYTE(v418) = -20;
        if ( Block[0] != nullptr )
        {
          v99 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = -19;
          v414 = 2048;
          v18 = sub_515F20(v8, v99);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;
        if ( (v414 & 0x800) != 0 )
          sub_445150(v333);
        goto LABEL_269;
      }
      Block[0] = operator new(0x5B0u);
      v418 = 458;
      if ( Block[0] != nullptr )
      {
        v100 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -53;
        v416 = (void *)0x4000;
        v18 = sub_5144A0(171, v100);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;
      if ( (BYTE1(v416) & 0x40) == 0 )
      {
LABEL_893:
        sub_6055A0(0, 2, 100, 150, 0, 40002);
        goto LABEL_269;
      }
      v101 = &v281;
LABEL_892:
      sub_445150(v101);
      goto LABEL_893;
    }
    if ( a1 > 27320 )
    {
      if ( a1 <= 27531 )
      {
        if ( a1 != 27531 )
        {
          switch ( a1 )
          {
            case 27327:
            case 27514:
              Block[0] = operator new(0xCD0u);
              LOBYTE(v418) = 68;
              if ( Block[0] != nullptr )
              {
                v119 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 69;
                v413 = 0x100000;
                v18 = sub_51B380(v8, v119);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v413 & 0x100000) != 0 )
                sub_445150(v319);
              goto LABEL_269;
            case 27332:
            case 27518:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = 31;
              if ( Block[0] != nullptr )
              {
                v117 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 32;
                v413 = 256;
                v18 = sub_5144A0(v8, v117);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v413 & 0x100) != 0 )
                sub_445150(v321);
              sub_6048E0(0, 100, 2, 100);
              goto LABEL_269;
            case 27500:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = -88;
              if ( Block[0] != nullptr )
              {
                v120 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -87;
                v412 = 0x200000;
                v18 = sub_5144A0(v8, v120);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v412 & 0x200000) != 0 )
                sub_445150(v241);
              sub_6048E0(0, 40, 5, 100);
              goto LABEL_269;
            case 27509:
              goto LABEL_565;
            case 27530:
              v405 = 0;
              v406 = 0;
              v407 = 1103626240;
              v408 = 3;
              v409 = 0;
              v410 = 1103626240;
              Block[0] = operator new(0x5B0u);
              v418 = 332;
              if ( Block[0] != nullptr )
              {
                v121 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 77;
                v415 = 512;
                v18 = sub_5144A0(v8, v121);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v415 & 0x200) != 0 )
                sub_445150(v398);
              Block[0] = operator new(0x7Cu);
              v418 = 335;
              if ( Block[0] != nullptr )
                v122 = sub_5101B0(&v405, 2, 30000, 1);
              else
                v122 = 0;
              v418 = 0;
              sub_6055F0(0, 2, 100, 0, v122, 0);
              goto LABEL_269;
            default:
              goto LABEL_155;
          }
        }
        Block[0] = operator new(0x5B0u);
        v418 = 336;
        if ( Block[0] != nullptr )
        {
          v123 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = 81;
          v415 = 1024;
          v18 = sub_517570(139, v123);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;
        if ( (v415 & 0x400) != 0 )
          sub_445150(v273);
        goto LABEL_269;
      }
      switch ( a1 )
      {
        case 27622:
        case 27651:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = 28;
          if ( Block[0] != nullptr )
          {
            v125 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 29;
            v413 = 128;
            v18 = sub_51ADF0(v8, v125);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v413 & 0x80u) != 0 )
            sub_445150(v251);
          goto LABEL_269;
        case 27623:
        case 27657:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = 4;
          if ( Block[0] != nullptr )
          {
            v124 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 5;
            v413 = 2;
            v18 = sub_5144A0(v8, v124);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v413 & 2) != 0 )
            sub_445150(v315);
          v408 = 18;
          v409 = 0;
          v410 = 1101004800;
          Block[0] = operator new(0x7Cu);
          LOBYTE(v418) = 7;
          if ( Block[0] == nullptr )
            goto LABEL_605;
          v87 = sub_5101B0(&v408, 1, 0, 1);
          break;
        case 27628:
        case 27661:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = 53;
          if ( Block[0] != nullptr )
          {
            v126 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 54;
            v413 = 0x8000;
            v18 = sub_5144A0(v8, v126);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v413 & 0x8000) != 0 )
            sub_445150(v397);
          v229 = 0;
          v228 = 13;
          goto LABEL_619;
        case 27632:
          goto LABEL_620;
        default:
          goto LABEL_155;
      }
      goto LABEL_606;
    }
    if ( a1 != 27320 )
    {
      if ( a1 <= 27055 )
      {
        if ( a1 == 27055 )
          goto LABEL_509;
        if ( a1 <= 27032 )
        {
          if ( a1 == 27032 )
          {
LABEL_541:
            Block[0] = operator new(0xCD0u);
            LOBYTE(v418) = 71;
            if ( Block[0] != nullptr )
            {
              v113 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 72;
              v413 = 0x200000;
              v18 = sub_51B2A0(v8, v113);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v413 & 0x200000) != 0 )
              sub_445150(v277);
            goto LABEL_269;
          }
          if ( a1 <= 26031 )
          {
            if ( a1 == 26031 )
            {
              v416 = operator new(0x5B0u);
              v418 = 520;
              if ( v416 != nullptr )
              {
                v106 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 9;
                Block[0] = (void *)2;
                v107 = sub_51A520(175, v106);
              }
              else
              {
                v107 = 0;
              }
              v418 = 0;
              if ( ((int)Block[0] & 2) != 0 )
                sub_445150(v329);
              sub_5E5260(v411);
              return v107;
            }
            if ( a1 != 26029 )
            {
              if ( a1 == 26030 )
              {
                v416 = operator new(0x5B0u);
                v418 = 517;
                if ( v416 != nullptr )
                {
                  v102 = sub_4E9B10(a4, a5, a3, a2);
                  LOBYTE(v418) = 6;
                  Block[0] = (void *)1;
                  v103 = sub_51A670(174, v102);
                }
                else
                {
                  v103 = 0;
                }
                v418 = 0;
                if ( ((int)Block[0] & 1) != 0 )
                  sub_445150(v331);
                sub_5E5260(v411);
                return v103;
              }
              goto LABEL_155;
            }
            Block[0] = operator new(0x5B0u);
            v418 = 509;
            if ( Block[0] != nullptr )
            {
              v104 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -2;
              v416 = (void *)0x40000000;
              v30 = sub_5144A0(173, v104);
            }
            else
            {
              v30 = 0;
            }
            v418 = 0;
            if ( ((unsigned int)v416 & 0x40000000) != 0 )
              sub_445150(v255);
            v408 = 6;
            v409 = 0;
            v410 = 1120403456;
            Block[0] = operator new(0x7Cu);
            v418 = 512;
            if ( Block[0] != nullptr )
            {
              v105 = sub_5101B0(&v408, 1, 30000, 1);
              v229 = 0;
              v228 = v105;
            }
            else
            {
              v229 = 0;
              v228 = 0;
            }
            v227 = 0;
            v226 = 100;
            v418 = 0;
            v225 = 5;
            goto LABEL_218;
          }
          if ( a1 != 27020 )
            goto LABEL_155;
LABEL_509:
          Block[0] = operator new(0x548u);
          LOBYTE(v418) = 74;
          if ( Block[0] != nullptr )
          {
            v108 = (void *)sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 75;
            v413 = 0x400000;
            v18 = sub_51B050(v8, v108);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v413 & 0x400000) != 0 )
            sub_445150(v279);
          goto LABEL_269;
        }
        if ( a1 == 27033 )
        {
LABEL_532:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = 49;
          if ( Block[0] != nullptr )
          {
            v111 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 50;
            v413 = 0x4000;
            v18 = sub_5144A0(v8, v111);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v413 & 0x4000) != 0 )
            sub_445150(v325);
          Block[0] = operator new(0x7Cu);
          LOBYTE(v418) = 52;
          if ( Block[0] != nullptr )
            v112 = sub_4B3DF0(0, 0, 1106247680, 60000, 1);
          else
            v112 = 0;
          LOBYTE(v418) = 0;
          sub_6055F0(0, 2, 100, 0, v112, 0);
          goto LABEL_269;
        }
        if ( a1 == 27037 )
        {
LABEL_520:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = 8;
          if ( Block[0] != nullptr )
          {
            v110 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 9;
            v413 = 4;
            v18 = sub_5144A0(v8, v110);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v413 & 4) != 0 )
            sub_445150(v327);
          v408 = 5;
          v409 = 0;
          v410 = 1112014848;
          Block[0] = operator new(0x7Cu);
          LOBYTE(v418) = 11;
          if ( Block[0] != nullptr )
          {
            v87 = sub_5101B0(&v408, 1, 0, 1);
            goto LABEL_606;
          }
          goto LABEL_605;
        }
        if ( a1 != 27038 )
          goto LABEL_155;
LABEL_514:
        Block[0] = operator new(0x5B0u);
        LOBYTE(v418) = 34;
        if ( Block[0] != nullptr )
        {
          v109 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = 35;
          v413 = 512;
          v18 = sub_5144A0(v8, v109);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;
        if ( (v413 & 0x200) != 0 )
          sub_445150(v233);
        v229 = 0;
        v228 = 12;
LABEL_531:
        sub_605650(0, 3, 100, 7, 0, v228, v229);
        goto LABEL_269;
      }
      switch ( a1 )
      {
        case 27063:
          goto LABEL_541;
        case 27067:
          goto LABEL_520;
        case 27068:
        case 27081:
          goto LABEL_532;
        case 27069:
          goto LABEL_514;
        case 27074:
          Block[0] = operator new(0x5B0u);
          v418 = 329;
          if ( Block[0] != nullptr )
          {
            v114 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 74;
            v415 = 256;
            v18 = sub_517940(v8, v114);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v415 & 0x100) != 0 )
            sub_445150(v323);
          goto LABEL_269;
        case 27080:
          Block[0] = operator new(0x5B0u);
          v418 = 461;
          if ( Block[0] != nullptr )
          {
            v115 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -50;
            v416 = (void *)0x8000;
            v18 = sub_5144A0(v8, v115);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( SBYTE1(v416) >= 0 )
            goto LABEL_1274;
          v116 = &v253;
          break;
        default:
          goto LABEL_155;
      }
LABEL_1273:
      sub_445150(v116);
LABEL_1274:
      sub_6055A0(0, 3, 100, 100, 0, 40002);
      goto LABEL_269;
    }
LABEL_565:
    Block[0] = operator new(0x5B0u);
    LOBYTE(v418) = 37;
    if ( Block[0] != nullptr )
    {
      v118 = sub_4E9B10(a4, a5, a3, a2);
      LOBYTE(v418) = 38;
      v413 = 1024;
      v18 = sub_5144A0(v8, v118);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;
    if ( (v413 & 0x400) != 0 )
      sub_445150(v275);
    v229 = 0;
    v228 = 13;
LABEL_571:
    sub_605650(0, 2, 100, 5, 0, v228, v229);
    goto LABEL_269;
  }
  if ( a1 == 14064 )
  {
LABEL_318:
    Block[0] = operator new(0x5B0u);
    LOBYTE(v418) = -61;
    if ( Block[0] != nullptr )
    {
      v78 = sub_4E9B10(a4, a5, a3, a2);
      LOBYTE(v418) = -60;
      v412 = 0x40000000;
      v18 = sub_5144A0(v8, v78);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;
    if ( (v412 & 0x40000000) != 0 )
    {
      v79 = &v353;
LABEL_1255:
      sub_445150(v79);
    }
LABEL_1256:
    sub_605650(1, 10, 100, 7, 0, 13, 0);
    goto LABEL_269;
  }
  if ( a1 > 10830 )
  {
    if ( a1 <= 11256 )
    {
      if ( a1 == 11256 )
        goto LABEL_246;
      if ( a1 <= 10875 )
      {
        if ( a1 != 10875 )
        {
          switch ( a1 )
          {
            case 10843:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = -124;
              if ( Block[0] != nullptr )
              {
                v44 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -123;
                v412 = 512;
                v45 = sub_5144A0(v8, v44);
              }
              else
              {
                v45 = 0;
              }
              v418 = 0;
              if ( (v412 & 0x200) != 0 )
                sub_445150(v373);
              sub_605650(1, 5, 100, 7, 0, 13, 0);
              sub_5E5260(v411);
              result = v45;
              break;
            case 10850:
              goto LABEL_167;
            case 10856:
              goto LABEL_173;
            case 10868:
              Block[0] = operator new(0x5B0u);
              v418 = 373;
              if ( Block[0] != nullptr )
              {
                v49 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 118;
                v415 = 0x400000;
                v50 = sub_5144A0(v8, v49);
              }
              else
              {
                v50 = 0;
              }
              v418 = 0;
              if ( (v415 & 0x400000) != 0 )
                sub_445150(v265);
              sub_605650(0, 2, 100, 8, 0, 13, 0);
              sub_5E5260(v411);
              result = v50;
              break;
            case 10870:
              Block[0] = operator new(0x5B0u);
              v418 = 376;
              if ( Block[0] != nullptr )
              {
                v51 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 121;
                v415 = (int)&unk_800000;
                v52 = sub_5144A0(v8, v51);
              }
              else
              {
                v52 = 0;
              }
              v418 = 0;
              if ( ((unsigned int)&unk_800000 & v415) != 0 )
                sub_445150(v369);
              sub_605650(0, 4, 100, 8, 0, 15, 2);
              sub_5E5260(v411);
              result = v52;
              break;
            case 10871:
              v416 = operator new(0x90Cu);
              v418 = 523;
              if ( v416 != nullptr )
              {
                v53 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 12;
                Block[0] = (void *)4;
                v54 = sub_51A920(v8, v53, 7, 0);
              }
              else
              {
                v54 = 0;
              }
              v418 = 0;
              if ( ((int)Block[0] & 4) != 0 )
                sub_445150(v299);
              sub_5E5260(v411);
              result = v54;
              break;
            case 10872:
              v416 = operator new(0x90Cu);
              v418 = 526;
              if ( v416 != nullptr )
              {
                v55 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 15;
                Block[0] = (void *)8;
                v56 = sub_51AA20(v8, v55, 12, 0);
              }
              else
              {
                v56 = 0;
              }
              v418 = 0;
              if ( ((int)Block[0] & 8) != 0 )
                sub_445150(v367);
              sub_5E5260(v411);
              result = v56;
              break;
            case 10874:
              v416 = operator new(0x5B0u);
              v418 = 529;
              if ( v416 != nullptr )
              {
                v57 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = 18;
                Block[0] = (void *)16;
                v58 = sub_5144A0(v8, v57);
              }
              else
              {
                v58 = 0;
              }
              v418 = 0;
              if ( ((int)Block[0] & 0x10) != 0 )
                sub_445150(v247);
              sub_605650(1, 3, 100, 15, 0, 2, 1);
              sub_5E5260(v411);
              result = v58;
              break;
            default:
              goto LABEL_155;
          }
          return result;
        }
        v416 = operator new(0x5B0u);
        v418 = 532;
        if ( v416 != nullptr )
        {
          v59 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = 21;
          Block[0] = (void *)32;
          v30 = sub_5144A0(123, v59);
        }
        else
        {
          v30 = 0;
        }
        v418 = 0;
        if ( ((int)Block[0] & 0x20) != 0 )
          sub_445150(v365);
        Block[0] = operator new(0x7Cu);
        v418 = 535;
        if ( Block[0] != nullptr )
          v60 = sub_4B3DF0(0, 0, 1109393408, 30000, 1);
        else
          v60 = 0;
        v229 = 0;
        v228 = v60;
        v418 = 0;
        v227 = 0;
LABEL_217:
        v226 = 100;
        v225 = 2;
LABEL_218:
        sub_6055F0(1, v225, v226, v227, v228, v229);
        goto LABEL_219;
      }
      if ( a1 <= 11230 )
      {
        if ( a1 != 11230 )
        {
          if ( a1 == 10876 )
          {
            v416 = operator new(0x5B4u);
            v418 = 536;
            if ( v416 != nullptr )
            {
              v61 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 25;
              Block[0] = (void *)64;
              v62 = sub_51A330(124, v61);
            }
            else
            {
              v62 = 0;
            }
            v418 = 0;
            if ( ((int)Block[0] & 0x40) != 0 )
              sub_445150(v297);
            sub_5E5260(v411);
            return v62;
          }
          if ( a1 != 11216 )
          {
            if ( a1 != 11220 )
              goto LABEL_155;
            goto LABEL_235;
          }
LABEL_240:
          Block[0] = operator new(0x90Cu);
          LOBYTE(v418) = -115;
          if ( Block[0] != nullptr )
          {
            v64 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -114;
            v412 = 4096;
            v10 = sub_514B80(v8, v64, 16, 0);
          }
          else
          {
            v10 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x1000) != 0 )
            sub_445150(v263);
          v65 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 176))(v10);
LABEL_293:
          Block[0] = (void *)sub_41A5E0(v65 + 112);
          v12 = (double)(int)Block[0] * 0.25;
LABEL_16:
          v229 = (uint64_t)v12;
LABEL_17:
          sub_41C150(v229);
          sub_5E5260(v411);
          return v10;
        }
LABEL_246:
        Block[0] = operator new(0x5B0u);
        LOBYTE(v418) = -109;
        if ( Block[0] != nullptr )
        {
          v66 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = -108;
          v412 = 0x4000;
          v67 = sub_5144A0(v8, v66);
        }
        else
        {
          v67 = 0;
        }
        v418 = 0;
        if ( (v412 & 0x4000) != 0 )
          sub_445150(v361);
        sub_605650(1, 3, 100, 7, 0, 6, 2);
        sub_5E5260(v411);
        return v67;
      }
      if ( a1 != 11237 )
      {
        if ( a1 != 11250 )
        {
          if ( a1 != 11253 )
            goto LABEL_155;
LABEL_235:
          Block[0] = operator new(0xCD0u);
          LOBYTE(v418) = -112;
          if ( Block[0] != nullptr )
          {
            v63 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -111;
            v412 = 0x2000;
            v18 = sub_5156B0(v8, v63);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x2000) != 0 )
          {
            sub_445150(v363);
            sub_5E5260(v411);
            return v18;
          }
          goto LABEL_269;
        }
        goto LABEL_240;
      }
LABEL_270:
      Block[0] = operator new(0x548u);
      LOBYTE(v418) = -106;
      if ( Block[0] != nullptr )
      {
        v70 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -105;
        v412 = 0x8000;
        v18 = sub_514940(v8, v70);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;
      if ( (v412 & 0x8000) != 0 )
        sub_445150(v359);
      goto LABEL_269;
    }
    if ( a1 <= 11637 )
    {
      if ( a1 != 11637 )
      {
        if ( a1 <= 11612 )
        {
          if ( a1 != 11612 )
          {
            if ( a1 == 11259 )
              goto LABEL_270;
            if ( a1 != 11274 )
            {
              if ( a1 != 11605 )
                goto LABEL_155;
LABEL_259:
              Block[0] = operator new(0x5B0u);
              LOBYTE(v418) = -97;
              if ( Block[0] != nullptr )
              {
                v68 = sub_4E9B10(a4, a5, a3, a2);
                LOBYTE(v418) = -96;
                v412 = 0x40000;
                v18 = sub_5144A0(v8, v68);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;
              if ( (v412 & 0x40000) != 0 )
                sub_445150(v357);
              sub_605650(1, 3, 100, 7, 0, 1, 2);
              goto LABEL_269;
            }
            v416 = operator new(0x5B4u);
            v418 = 539;
            if ( v416 != nullptr )
            {
              v69 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = 28;
              Block[0] = (void *)128;
              v18 = sub_51AB20(10, v69);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( SLOBYTE(Block[0]) < 0 )
              sub_445150(v295);
            v229 = 20011;
            v228 = 0;
            v227 = 5;
LABEL_267:
            v226 = 100;
            v224 = 2;
LABEL_268:
            sub_6055A0(1, v224, v226, v227, v228, v229);
LABEL_269:
            sub_5E5260(v411);
            return v18;
          }
LABEL_278:
          Block[0] = operator new(0xCD0u);
          LOBYTE(v418) = -94;
          if ( Block[0] != nullptr )
          {
            v71 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -93;
            v412 = 0x80000;
            v18 = sub_515870(v8, v71);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x80000) != 0 )
            sub_445150(v231);
          goto LABEL_269;
        }
        if ( a1 != 11619 )
        {
          if ( a1 == 11631 )
            goto LABEL_259;
          if ( a1 != 11634 )
            goto LABEL_155;
          goto LABEL_278;
        }
      }
      Block[0] = operator new(0x90Cu);
      LOBYTE(v418) = -91;
      if ( Block[0] != nullptr )
      {
        v72 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -90;
        v412 = 0x100000;
        v10 = sub_514C60(v8, v72, 24, 0);
      }
      else
      {
        v10 = 0;
      }
      v418 = 0;
      if ( (v412 & 0x100000) != 0 )
        sub_445150(v293);
      v65 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 176))(v10);
      goto LABEL_293;
    }
    if ( a1 <= 14032 )
    {
      if ( a1 != 14032 )
      {
        if ( a1 != 11648 )
        {
          if ( a1 != 14022 )
          {
            if ( a1 != 14030 )
              goto LABEL_155;
LABEL_299:
            Block[0] = operator new(0x5B0u);
            LOBYTE(v418) = -64;
            if ( Block[0] != nullptr )
            {
              v73 = sub_4E9B10(a4, a5, a3, a2);
              LOBYTE(v418) = -63;
              v412 = 0x20000000;
              v18 = sub_5167E0(v8, v73);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;
            if ( (v412 & 0x20000000) != 0 )
              sub_445150(v351);
            goto LABEL_269;
          }
LABEL_313:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -67;
          if ( Block[0] != nullptr )
          {
            v77 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -66;
            v412 = 0x10000000;
            v18 = sub_516300(v8, v77);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x10000000) != 0 )
            sub_445150(v261);
          goto LABEL_269;
        }
        v416 = operator new(0x5B0u);
        v418 = 542;
        if ( v416 != nullptr )
        {
          v74 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = 31;
          Block[0] = (void *)256;
          v75 = sub_5144A0(128, v74);
        }
        else
        {
          v75 = 0;
        }
        v418 = 0;
        if ( (BYTE1(Block[0]) & 1) != 0 )
          sub_445150(v355);
        v405 = 0;
        v406 = 0;
        v407 = 1101004800;
        v408 = 3;
        v409 = 0;
        v410 = 1101004800;
        Block[0] = operator new(0x7Cu);
        v418 = 545;
        if ( Block[0] != nullptr )
        {
          v76 = sub_5101B0(&v405, 2, 0, 1);
LABEL_309:
          v418 = 0;
          sub_6055F0(2, 100, 100, 0, v76, 0);
          sub_5E5260(v411);
          return v75;
        }
LABEL_308:
        v76 = 0;
        goto LABEL_309;
      }
      goto LABEL_318;
    }
    if ( a1 != 14039 )
    {
      if ( a1 != 14046 )
      {
        if ( a1 != 14059 )
          goto LABEL_155;
        goto LABEL_313;
      }
LABEL_343:
      Block[0] = operator new(0x5B0u);
      LOBYTE(v418) = -55;
      if ( Block[0] != nullptr )
      {
        v81 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -54;
        v414 = 1;
        v18 = sub_5144A0(v8, v81);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;
      if ( (v414 & 1) != 0 )
        sub_445150(v245);
      sub_605650(1, 10, 100, 9, 0, 4, 2);
      goto LABEL_269;
    }
LABEL_335:
    Block[0] = operator new(0x5B4u);
    LOBYTE(v418) = -58;
    if ( Block[0] != nullptr )
    {
      v80 = sub_4E9B10(a4, a5, a3, a2);
      LOBYTE(v418) = -57;
      v412 = 0x80000000;
      v18 = sub_5163B0(v8, v80);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;
    if ( v412 < 0 )
      sub_445150(v291);
    goto LABEL_269;
  }
  if ( a1 == 10830 )
  {
LABEL_173:
    Block[0] = operator new(0x5B0u);
    LOBYTE(v418) = -118;
    if ( Block[0] != nullptr )
    {
      v48 = sub_4E9B10(a4, a5, a3, a2);
      LOBYTE(v418) = -117;
      v412 = 2048;
      v18 = sub_514DE0(v8, v48);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;
    if ( (v412 & 0x800) != 0 )
    {
      sub_445150(v371);
      sub_5E5260(v411);
      return v18;
    }
    goto LABEL_269;
  }
  if ( a1 <= 10087 )
  {
    if ( a1 != 10087 )
    {
      switch ( a1 )
      {
        case 10024:
        case 10065:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -82;
          if ( Block[0] != nullptr )
          {
            v17 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -81;
            v412 = (int)&unk_800000;
            v18 = sub_515410(v8, v17);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( ((unsigned int)&unk_800000 & v412) == 0 )
            goto LABEL_269;
          sub_445150(v271);
          sub_5E5260(v411);
          return v18;
        case 10030:
        case 10070:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -79;
          if ( Block[0] != nullptr )
          {
            v19 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -78;
            v412 = 0x1000000;
            v18 = sub_5166D0(v8, v19);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x1000000) == 0 )
            goto LABEL_269;
          sub_445150(v393);
          sub_5E5260(v411);
          return v18;
        case 10034:
        case 10069:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -76;
          if ( Block[0] != nullptr )
          {
            v20 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -75;
            v412 = 0x2000000;
            v21 = sub_5144A0(v8, v20);
          }
          else
          {
            v21 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x2000000) != 0 )
            sub_445150(v311);
          sub_605650(1, 5, 100, 4, 0, 1, 2);
          sub_5E5260(v411);
          return v21;
        case 10038:
        case 10077:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -73;
          if ( Block[0] != nullptr )
          {
            v22 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -72;
            v412 = 0x4000000;
            v23 = sub_5144A0(v8, v22);
          }
          else
          {
            v23 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x4000000) != 0 )
            sub_445150(v391);
          sub_605650(1, 10, 100, 5, 0, 15, 2);
          sub_5E5260(v411);
          return v23;
        case 10039:
        case 10074:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = -70;
          if ( Block[0] != nullptr )
          {
            v24 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -69;
            v412 = 0x8000000;
            v18 = sub_5160B0(v8, v24);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x8000000) == 0 )
            goto LABEL_269;
          sub_445150(v235);
          sub_5E5260(v411);
          return v18;
        case 10043:
        case 10068:
          Block[0] = operator new(0x90Cu);
          LOBYTE(v418) = 120;
          if ( Block[0] != nullptr )
          {
            v9 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 121;
            v412 = 32;
            v10 = sub_514350(v8, v9, 16, 0);
          }
          else
          {
            v10 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x20) != 0 )
            sub_445150(v317);
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 176))(v10);
          Block[0] = (void *)sub_41A5E0(v11 + 112);
          v12 = (double)(int)Block[0] * 0.15000001;
          goto LABEL_16;
        case 10049:
        case 10073:
          Block[0] = operator new(0x5B0u);
          LOBYTE(v418) = 123;
          if ( Block[0] != nullptr )
          {
            v14 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 124;
            v412 = 64;
            v15 = sub_5144A0(v8, v14);
          }
          else
          {
            v15 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x40) != 0 )
            sub_445150(v313);
          sub_605650(0, 2, 100, 7, 0, 13, 0);
          sub_5E5260(v411);
          return v15;
        case 10054:
          Block[0] = operator new(0xCD0u);
          LOBYTE(v418) = -85;
          if ( Block[0] != nullptr )
          {
            v16 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = -84;
            v412 = 0x400000;
            v10 = sub_5141B0(v8, v16, 0, 1);
          }
          else
          {
            v10 = 0;
          }
          v418 = 0;
          if ( (v412 & 0x400000) != 0 )
            sub_445150(v395);
          sub_513B10(2, 1);
          v229 = 30;
          goto LABEL_17;
        case 10086:
          Block[0] = operator new(0xCD0u);
          v418 = 361;
          if ( Block[0] != nullptr )
          {
            v25 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 106;
            v415 = 0x40000;
            v10 = sub_5141B0(v8, v25, 0, 1);
          }
          else
          {
            v10 = 0;
          }
          v418 = 0;
          if ( (v415 & 0x40000) == 0 )
            goto LABEL_63;
          v26 = &v389;
          goto LABEL_62;
        default:
          goto LABEL_155;
      }
    }
    Block[0] = operator new(0x5B0u);
    v418 = 364;
    if ( Block[0] != nullptr )
    {
      v27 = sub_4E9B10(a4, a5, a3, a2);
      LOBYTE(v418) = 109;
      v415 = 0x80000;
      v18 = sub_5144A0(103, v27);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;
    if ( (v415 & 0x80000) != 0 )
      sub_445150(v309);
    v229 = 20011;
    v228 = 0;
    v227 = 6;
    v226 = 100;
    v224 = 5;
    goto LABEL_268;
  }
  if ( a1 > 10430 )
  {
    if ( a1 <= 10473 )
    {
      if ( a1 == 10473 )
      {
        Block[0] = operator new(0x5B0u);
        v418 = 446;
        if ( Block[0] != nullptr )
        {
          v39 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = -65;
          v416 = (void *)1024;
          v18 = sub_519190(233, v39);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;
        if ( (BYTE1(v416) & 4) != 0 )
        {
          sub_445150(v377);
          sub_5E5260(v411);
          return v18;
        }
        goto LABEL_269;
      }
      switch ( a1 )
      {
        case 10442:
          Block[0] = operator new(0x544u);
          v418 = 320;
          if ( Block[0] != nullptr )
          {
            v36 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 65;
            v415 = 32;
            v18 = sub_514680(v8, v36);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v415 & 0x20) == 0 )
            goto LABEL_269;
          sub_445150(v305);
          sub_5E5260(v411);
          result = v18;
          break;
        case 10457:
          goto LABEL_106;
        case 10469:
          Block[0] = operator new(0x5B0u);
          v418 = 367;
          if ( Block[0] != nullptr )
          {
            v37 = sub_4E9B10(a4, a5, a3, a2);
            LOBYTE(v418) = 112;
            v415 = 0x100000;
            v18 = sub_517360(v8, v37);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v415 & 0x100000) == 0 )
            goto LABEL_269;
          sub_445150(v379);
          sub_5E5260(v411);
          result = v18;
          break;
        case 10472:
          Block[0] = (void *)5;
          sub_431230(Block);
          Block[0] = (void *)6;
          sub_431230(Block);
          Block[0] = (void *)7;
          sub_431230(Block);
          Block[0] = (void *)8;
          sub_431230(Block);
          Block[0] = (void *)9;
          sub_431230(Block);
          Block[0] = (void *)10;
          sub_431230(Block);
          Block[0] = operator new(0x5B0u);
          v418 = 397;
          if ( Block[0] != nullptr )
          {
            v416 = &v226;
            sub_435020(v411);
            LOBYTE(v418) = -114;
            v38 = sub_4E9B10(a4, a5, a3, a2);
            v415 = 0x20000000;
            v418 = 400;
            v18 = sub_518010(v8, v38, v226, (void *)v227, v228, v229);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;
          if ( (v415 & 0x20000000) == 0 )
            goto LABEL_269;
          sub_445150(v267);
          sub_5E5260(v411);
          result = v18;
          break;
        default:
          goto LABEL_155;
      }
      return result;
    }
    if ( a1 > 10479 )
    {
      if ( a1 == 10816 )
      {
LABEL_167:
        Block[0] = operator new(0x5B0u);
        LOBYTE(v418) = -121;
        if ( Block[0] != nullptr )
        {
          v46 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = -120;
          v412 = 1024;
          v47 = sub_515950(v8, v46);
        }
        else
        {
          v47 = 0;
        }
        v418 = 0;
        if ( (v412 & 0x400) != 0 )
          sub_445150(v301);
        sub_605650(1, 5, 100, 7, 0, 4, 2);
        sub_5E5260(v411);
        return v47;
      }
      goto LABEL_155;
    }
    if ( a1 == 10479 )
    {
      Block[0] = operator new(0x5B4u);
      v418 = 506;
      if ( Block[0] != nullptr )
      {
        v43 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -5;
        v416 = (void *)0x20000000;
        v30 = sub_51A0C0(239, v43);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;
      if ( ((unsigned int)v416 & 0x20000000) != 0 )
      {
        sub_445150(v239);
        sub_5E5260(v411);
        return v30;
      }
      goto LABEL_219;
    }
    if ( a1 != 10476 )
    {
      if ( a1 == 10477 )
      {
        Block[0] = operator new(0xCD0u);
        v418 = 503;
        if ( Block[0] != nullptr )
        {
          v40 = sub_4E9B10(a4, a5, a3, a2);
          LOBYTE(v418) = -8;
          v416 = (void *)0x10000000;
          v30 = sub_51B900(237, v40);
        }
        else
        {
          v30 = 0;
        }
        v418 = 0;
        if ( ((unsigned int)v416 & 0x10000000) != 0 )
        {
          sub_445150(v303);
          sub_5E5260(v411);
          return v30;
        }
        goto LABEL_219;
      }
LABEL_155:
      sub_5E5260(v411);
      return 0;
    }
    Block[0] = operator new(0x5B0u);
    v418 = 499;
    if ( Block[0] != nullptr )
    {
      v41 = sub_4E9B10(a4, a5, a3, a2);
      LOBYTE(v418) = -12;
      v416 = (void *)0x8000000;
      v30 = sub_5144A0(236, v41);
    }
    else
    {
      v30 = 0;
    }
    v418 = 0;
    if ( ((unsigned int)v416 & 0x8000000) != 0 )
      sub_445150(v375);
    v405 = 0;
    v406 = 0;
    v407 = 1106247680;
    v408 = 1;
    v409 = 0;
    v410 = 1101004800;
    Block[0] = operator new(0x7Cu);
    v418 = 502;
    if ( Block[0] != nullptr )
    {
      v42 = sub_5101B0(&v405, 2, 30000, 1);
      v229 = 0;
      v228 = v42;
    }
    else
    {
      v229 = 0;
      v228 = 0;
    }
    v418 = 0;
    v227 = 0;
    goto LABEL_217;
  }
  if ( a1 == 10430 )
  {
LABEL_106:
    Block[0] = operator new(0x5D4u);
    LOBYTE(v418) = 126;
    if ( Block[0] != nullptr )
    {
      v35 = sub_4E9B10(a4, a5, a3, a2);
      LOBYTE(v418) = 127;
      v412 = 128;
      v18 = sub_516A90(v8, v35);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;
    if ( (v412 & 0x80u) != 0 )
    {
      sub_445150(v381);
      sub_5E5260(v411);
      return v18;
    }
    goto LABEL_269;
  }
  switch ( a1 )
  {
    case 10092:
      Block[0] = operator new(0x5B0u);
      v418 = 443;
      if ( Block[0] != nullptr )
      {
        v28 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -68;
        v416 = (void *)512;
        v18 = sub_519080(v8, v28);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;
      if ( (BYTE1(v416) & 2) == 0 )
        goto LABEL_269;
      sub_445150(v387);
      sub_5E5260(v411);
      result = v18;
      break;
    case 10094:
      Block[0] = operator new(0x5B0u);
      v418 = 484;
      if ( Block[0] != nullptr )
      {
        v29 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -27;
        v416 = (void *)0x400000;
        v30 = sub_519770(v8, v29);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;
      if ( ((unsigned int)v416 & 0x400000) == 0 )
        goto LABEL_219;
      sub_445150(v269);
      sub_5E5260(v411);
      result = v30;
      break;
    case 10097:
      Block[0] = operator new(0x5B4u);
      v418 = 487;
      if ( Block[0] != nullptr )
      {
        v31 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -24;
        v416 = &unk_800000;
        v30 = sub_519910(v8, v31);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;
      if ( ((unsigned int)&unk_800000 & (unsigned int)v416) == 0 )
        goto LABEL_219;
      sub_445150(v385);
      sub_5E5260(v411);
      result = v30;
      break;
    case 10098:
      Block[0] = operator new(0x5B0u);
      v418 = 490;
      if ( Block[0] != nullptr )
      {
        v32 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -21;
        v416 = (void *)0x1000000;
        v30 = sub_519BF0(v8, v32);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;
      if ( ((unsigned int)v416 & 0x1000000) == 0 )
        goto LABEL_219;
      sub_445150(v307);
      sub_5E5260(v411);
      result = v30;
      break;
    case 10099:
      Block[0] = operator new(0x5B0u);
      v418 = 493;
      if ( Block[0] != nullptr )
      {
        v33 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -18;
        v416 = (void *)0x2000000;
        v30 = sub_519D30(v8, v33);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;
      if ( ((unsigned int)v416 & 0x2000000) == 0 )
        goto LABEL_219;
      sub_445150(v383);
      sub_5E5260(v411);
      result = v30;
      break;
    case 10100:
      Block[0] = operator new(0x5B0u);
      v418 = 496;
      if ( Block[0] != nullptr )
      {
        v34 = sub_4E9B10(a4, a5, a3, a2);
        LOBYTE(v418) = -15;
        v416 = (void *)0x4000000;
        v30 = sub_519EF0(v8, v34);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;
      if ( ((unsigned int)v416 & 0x4000000) == 0 )
        goto LABEL_219;
      sub_445150(v249);
      sub_5E5260(v411);
      result = v30;
      break;
    default:
      goto LABEL_155;
  }
  return result;
}

