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
int /*usercall*/ sub_51BA00@<eax>(int nArg1@<edx>, int nArg2@<ecx>, int nArg3@<ebx>, int nArg4, int nArg5)  // 实现：size=25733
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v6; // esp
  char nArg12; // si
  int v9; // eax
  int pObj; // esi
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
  void *pMem; // eax
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
  int pObj2; // edi
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
  uint32_t pBuf[4]; // [esp+27CCh] [ebp-34h] BYREF
  int v412; // [esp+27DCh] [ebp-24h]
  int v413; // [esp+27E0h] [ebp-20h]
  int v414; // [esp+27E4h] [ebp-1Ch]
  int v415; // [esp+27E8h] [ebp-18h]
  void *pMem2; // [esp+27ECh] [ebp-14h]
  void *Block[3]; // [esp+27F0h] [ebp-10h] BYREF
  int v418; // [esp+27FCh] [ebp-4h]

  // ── [段 1] 入口：SEH 展开框架装配（ExceptionList/loc_6B10B3）+ alloca(10228) 大栈帧 + 五个轨迹标志清零 ──
  //   ★ 本函数 = ★★ 装备 PO 工厂（0x51 区）：nArg1=物品 ID → new + 专属 CNEquipment 构造器 ──
  //   调用点：sub_522300（pvp_ui.cpp PO 总工厂）先试 sub_510F30(护符) → 再试本函数 → 再试 0x442DA0 装备判定
  //   参数传递：nArg1@edx=物品ID、nArg2@ecx、nArg3@ebx、nArg4/nArg5=附参；返回值=新对象（0 表示不支持该 ID）
  //   手法定案：ID 不连续 → 编译器生成 二分阈值 if 树 + 叶子处 switch(ID)，case 标签即物品 ID
  //   v18=结果对象、Block[0]=operator new 的内存、v413/v414/v415=异常展开时需销毁的成员位掩码、v418=展开状态号
  v418 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;  // ExceptionList = 取线程环境块(SEH 链)
  Block[2] = &loc_6B10B3;  // SEH 展开 Block[2] = &loc_6B10B3(异常处理器/链指针)
  Block[1] = ExceptionList;
  v6 = alloca(10228);  // 栈上分配 10228 字节(alloca 大栈帧)
  v413 = 0;  // 标记待释放成员位 = 0(0x0)
  v412 = 0;
  v414 = 0;  // 标记待释放成员位 = 0(0x0)
  v415 = 0;  // 标记待释放成员位 = 0(0x0)
  pMem2 = nullptr;
  Block[0] = nullptr;
  nArg12 = nArg1;
  memset(&pBuf[1], 0, 12);  // 清零 pBuf 局部缓冲 12 字节
  v418 = 0;  // SEH 展开状态号 = 0
  // ── [段 2] 顶层二分之北：nArg1 > 27662（ID 3 万段：后期装备/时装） ──
  //   骨架（全函数同构）：Block[0]=operator new(0x5B0 等) → sub_4E9B10 建参数结构 → 构造器 → 置标志位 → LABEL_269 收尾
  //   v413/v414/v415 位标志在异常时决定是否 sub_445150（释放参数结构）——IDE 展开语义，非业务逻辑
  if ( nArg1 > 27662 )  // 物品 ID > 27662(二分阈值,北支)
  {
    if ( nArg1 <= 30253 )  // nArg1 <= 30253 判定
    {
      // ── [段 3] 30253 → LABEL_915：CNEventEquipment(0x5B0) 通用事件装备 ──
      if ( nArg1 == 30253 )  // nArg1 == 30253 判定
      {
LABEL_915:
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        v418 = 349;  // SEH 展开状态号 = 349
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v173 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v173 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = 94;  // 把 94 低字节存入 v418(短串内联指针)
          v415 = 0x4000;  // 标记待释放成员位 = 0x4000
          v18 = sub_5144A0(nArg12, v173);  // v18 = sub_5144A0 · CNEventEquipment 构造器
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (v415 & 0x4000) != 0 )  // 展开位 v415&0x4000 判定(需释放对应成员)
          sub_445150(v326);  // sub_445150 · 装备同步资源清理
        sub_6048E0(4, 300, 1, 100);  // sub_6048E0 · 概率组写入
        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
      }
      // ── [段 4] 29332 → LABEL_1250：CNEventEquipment 通用 ──
      if ( nArg1 <= 29332 )  // nArg1 <= 29332 判定
      {
        if ( nArg1 == 29332 )  // nArg1 == 29332 判定
        {
LABEL_1250:
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 279;  // SEH 展开状态号 = 279
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v220 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v220 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 24;  // 把 24 低字节存入 v418(短串内联指针)
            v414 = 0x1000000;  // 标记待释放成员位 = 0x1000000
            v18 = sub_5144A0(nArg12, v220);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v414 & 0x1000000) == 0 )  // 展开位 v414&0x1000000 为 0(无需释放)
            goto LABEL_1256;  // 跳转 LABEL_1256(收尾/共用分支)
          v79 = &v236;
          goto LABEL_1255;  // 跳转 LABEL_1255(收尾/共用分支)
        }
        // ── [段 5] 28255 → CNEventEquipment 通用（0x5B0；周边 27913/27923 等亦多为通用底座） ──
        //   [推断] 大阈值直判分支多落在「同族多 ID 共用一个构造器」的通用件上
        if ( nArg1 <= 28255 )  // nArg1 <= 28255 判定
        {
          if ( nArg1 == 28255 )  // nArg1 == 28255 判定
          {
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 464;  // SEH 展开状态号 = 464
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v139 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v139 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -47;  // SEH 展开状态号(低字节) = -47
              pMem2 = (void *)0x10000;  // 标记待释放成员位 = 0x10000(第 2 组掩码)
              v18 = sub_5144A0(95, v139);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( ((unsigned int)pMem2 & 0x10000) != 0 )  // 展开位 pMem2&0x10000 判定
              sub_445150(v374);  // sub_445150 · 装备同步资源清理
            v408 = 18;
            v409 = 0;
            v410 = 1097859072;  // 置 v410 = 1097859072（float 15.0f）
            Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
            v418 = 467;  // SEH 展开状态号 = 467
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
            else
              v87 = 0;
            v418 = 0;  // SEH 展开状态号 = 0
            goto LABEL_607;  // 跳转 LABEL_607(收尾/共用分支)
          }
          // ── [段 6] (27662, 27958] 段：27926 进入 switch，其余 27928/27939/27957/27961/27965 逐一判定 ──
          //   【已对表】27674/27675/27913/27923 四个 ID 在此 switch 内
          if ( nArg1 <= 27958 )  // nArg1 <= 27958 判定
          {
            if ( nArg1 == 27958 )  // nArg1 == 27958 判定
              goto LABEL_664;  // 跳转 LABEL_664(收尾/共用分支)
            if ( nArg1 <= 27926 )  // nArg1 <= 27926 判定
            {
              if ( nArg1 != 27926 )  // nArg1 != 27926 判定
              {
                //   27674 = CNEventEquipment（0x5B0）→ sub_6048E0(0,100,4,100) 装概率组
                switch ( nArg1 )  // 按 nArg1 分派
                {
                  case 27674:  // case 27674 → 装备参数结构构造
                    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                    v418 = 323;  // SEH 展开状态号 = 323
                    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                    {
                      v129 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v129 = sub_4E9B10 · 装备参数结构构造
                      LOBYTE(v418) = 68;  // 把 68 低字节存入 v418(短串内联指针)
                      v415 = 64;  // 标记待释放成员位 = 64(0x40)
                      v18 = sub_5144A0(nArg12, v129);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;  // SEH 展开状态号 = 0
                    if ( (v415 & 0x40) != 0 )  // 展开位 v415&0x40 判定(需释放对应成员)
                      sub_445150(v392);  // sub_445150 · 装备同步资源清理
                    sub_6048E0(0, 100, 4, 100);  // sub_6048E0 · 概率组写入
                    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                  //   27675 = CNEquipmentShootingStarDrop（流星坠落）
                  case 27675:  // case 27675 → 装备参数结构构造
                    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                    v418 = 326;  // SEH 展开状态号 = 326
                    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                    {
                      v130 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v130 = sub_4E9B10 · 装备参数结构构造
                      LOBYTE(v418) = 71;  // 把 71 低字节存入 v418(短串内联指针)
                      v415 = 128;  // 标记待释放成员位 = 128(0x80)
                      v18 = sub_5177B0(nArg12, v130);
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;  // SEH 展开状态号 = 0
                    if ( (v415 & 0x80u) != 0 )  // 展开位 v415&0x80 判定(需释放对应成员)
                      sub_445150(v390);  // sub_445150 · 装备同步资源清理
                    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                  //   27913 = CNEventEquipment + 若 Block 空走 LABEL_605 清理
                  case 27913:  // case 27913 → 装备参数结构构造
                    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                    LOBYTE(v418) = 12;  // 把 12 低字节存入 v418(短串内联指针)
                    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                    {
                      v128 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v128 = sub_4E9B10 · 装备参数结构构造
                      LOBYTE(v418) = 13;  // 把 13 低字节存入 v418(短串内联指针)
                      v413 = 8;  // 标记待释放成员位 = 8(0x8)
                      v18 = sub_5144A0(nArg12, v128);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;  // SEH 展开状态号 = 0
                    if ( (v413 & 8) != 0 )  // 展开位 v413&8 判定(需释放对应成员)
                      sub_445150(v394);  // sub_445150 · 装备同步资源清理
                    v408 = 5;
                    v409 = 0;
                    v410 = 1127481344;  // 置 v410 = 1127481344（float 180.0f）
                    Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
                    LOBYTE(v418) = 15;  // 把 15 低字节存入 v418(短串内联指针)
                    if ( Block[0] == nullptr )  // Block[0] 分配失败(走释放路径)
                      goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
                    v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
                    break;  // 跳出本 switch(单 case 处理完)
                  //   27923 → LABEL_658 与 27957 共用一支（0x5B0 装备）
                  case 27923:  // case 27923：LABEL_658 与 27957 共用一支（0x5B0 装备）
                    goto LABEL_658;  // 跳转 LABEL_658(收尾/共用分支)
                  default:
                    goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                }
                goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
              }
LABEL_664:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 43;  // 把 43 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v132 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v132 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 44;  // 把 44 低字节存入 v418(短串内联指针)
                v413 = 4096;  // 标记待释放成员位 = 4096(0x1000)
                v18 = sub_51AF20(nArg12, v132);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v413 & 0x1000) != 0 )  // 展开位 v413&0x1000 判定(需释放对应成员)
                sub_445150(v386);  // sub_445150 · 装备同步资源清理
              sub_605650(0, 5, 100, 12, 0, 12, 0);  // sub_605650 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
            //   (27926, 28220] 段：27928 → LABEL_683 / 27939 → LABEL_677 / 27957 → LABEL_658 ──
            //   三条支路各自带 sub_605650/sub_6055A0 概率组参数装载
            if ( nArg1 != 27928 )  // nArg1 != 27928 判定
            {
              if ( nArg1 != 27939 )  // nArg1 != 27939 判定
              {
                if ( nArg1 == 27957 )  // nArg1 == 27957 判定
                {
LABEL_658:
                  Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                  LOBYTE(v418) = 40;  // 把 40 低字节存入 v418(短串内联指针)
                  if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                  {
                    v131 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v131 = sub_4E9B10 · 装备参数结构构造
                    LOBYTE(v418) = 41;  // 把 41 低字节存入 v418(短串内联指针)
                    v413 = 2048;  // 标记待释放成员位 = 2048(0x800)
                    v18 = sub_5144A0(nArg12, v131);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;  // SEH 展开状态号 = 0
                  if ( (v413 & 0x800) != 0 )  // 展开位 v413&0x800 判定(需释放对应成员)
                    sub_445150(v388);  // sub_445150 · 装备同步资源清理
                  sub_605650(0, 3, 100, 5, 0, -1, 1);  // sub_605650 · 6 字段记录追加
                  goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                }
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
              }
LABEL_677:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 46;  // 把 46 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v134 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v134 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 47;  // 把 47 低字节存入 v418(短串内联指针)
                v413 = 0x2000;  // 标记待释放成员位 = 0x2000
                v18 = sub_5144A0(nArg12, v134);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v413 & 0x2000) != 0 )  // 展开位 v413&0x2000 判定(需释放对应成员)
                sub_445150(v384);  // sub_445150 · 装备同步资源清理
              sub_6055A0(0, 3, 100, 50, 0, 40002);  // sub_6055A0 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
LABEL_683:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = 62;  // 把 62 低字节存入 v418(短串内联指针)
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v135 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v135 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 63;  // 把 63 低字节存入 v418(短串内联指针)
              v413 = 0x40000;  // 标记待释放成员位 = 0x40000
              v18 = sub_5144A0(nArg12, v135);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v413 & 0x40000) != 0 )  // 展开位 v413&0x40000 判定(需释放对应成员)
              sub_445150(v382);  // sub_445150 · 装备同步资源清理
            v229 = 48003;
            v228 = 0;
            v227 = 8;
            v226 = 100;
            v224 = 10;
            goto LABEL_268;  // 跳转 LABEL_268(收尾/共用分支)
          }
          //   28220 附近：27961 → LABEL_683 / 27965 → LABEL_677 / 28203 → LABEL_675 ──
          //   LABEL_675 支带 v399/v400/v401 三个参数（含 1092616192=10.0f）
          if ( nArg1 <= 28220 )  // nArg1 <= 28220 判定
          {
            if ( nArg1 != 28220 )  // nArg1 != 28220 判定
            {
              if ( nArg1 == 27961 )  // nArg1 == 27961 判定
                goto LABEL_683;  // 跳转 LABEL_683(收尾/共用分支)
              if ( nArg1 == 27965 )  // nArg1 == 27965 判定
                goto LABEL_677;  // 跳转 LABEL_677(收尾/共用分支)
              if ( nArg1 != 28203 )  // nArg1 != 28203 判定
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_675:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 20;  // 把 20 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v133 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v133 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 21;  // 把 21 低字节存入 v418(短串内联指针)
                v413 = 32;  // 标记待释放成员位 = 32(0x20)
                v18 = sub_5144A0(nArg12, v133);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v413 & 0x20) != 0 )  // 展开位 v413&0x20 判定(需释放对应成员)
                sub_445150(v376);  // sub_445150 · 装备同步资源清理
              v399 = 16;
              v400 = 0;
              v401 = 1092616192;  // 置 v401 = 1092616192（float 10.0f）
              v402 = 17;
              v403 = 0;
              v404 = 1092616192;  // 置 v404 = 1092616192（float 10.0f）
              v405 = 18;
              v406 = 0;
              v407 = 1092616192;  // 置 v407 = 1092616192（float 10.0f）
              v408 = 19;
              v409 = 0;
              v410 = 1092616192;  // 置 v410 = 1092616192（float 10.0f）
              Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 23;  // 把 23 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v87 = sub_5101B0(&v399, 4, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
                goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
              }
              goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
            }
            goto LABEL_700;  // 跳转 LABEL_700(收尾/共用分支)
          }
          //   28227 / 28240 两支（各自 0x5B0 装备构造）
          if ( nArg1 == 28227 )  // nArg1 == 28227 判定
            goto LABEL_675;  // 跳转 LABEL_675(收尾/共用分支)
          if ( nArg1 == 28240 )  // nArg1 == 28240 判定
          {
LABEL_700:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = 24;  // 把 24 低字节存入 v418(短串内联指针)
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v138 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v138 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 25;  // 把 25 低字节存入 v418(短串内联指针)
              v413 = 64;  // 标记待释放成员位 = 64(0x40)
              v18 = sub_5144A0(nArg12, v138);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v413 & 0x40) != 0 )  // 展开位 v413&0x40 判定(需释放对应成员)
              sub_445150(v378);  // sub_445150 · 装备同步资源清理
            sub_605650(1, 5, 100, 7, 0, 13, 0);  // sub_605650 · 6 字段记录追加
            v408 = 5;
            v410 = 1112014848;  // 置 v410 = 1112014848（float 50.0f）
            v409 = 0;
            Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = 27;  // 把 27 低字节存入 v418(短串内联指针)
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
              goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
            }
            goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
          }
          //   28251 → 0x5B0 装备构造
          if ( nArg1 != 28251 )  // nArg1 != 28251 判定
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 513;  // SEH 展开状态号 = 513
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v136 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v136 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 2;  // 把 2 低字节存入 v418(短串内联指针)
            pMem2 = (void *)0x80000000;  // 标记待释放成员位 = 0x80000000(第 2 组掩码)
            v30 = sub_5144A0(91, v136);  // v30 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v30 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (int)pMem2 < 0 )  // < 范围判定
            sub_445150(v380);  // sub_445150 · 装备同步资源清理
          v405 = 11;
          v406 = 0;
          v407 = 1107558400;  // 浮点常量 33f
          v408 = 23;
          v409 = 0;
          v410 = 1107558400;  // 浮点常量 33f
          Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
          v418 = 516;  // SEH 展开状态号 = 516
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v137 = sub_5101B0(&v405, 2, 0, 1);  // v137 = sub_5101B0 · CNChangeStatus 构造器
            v418 = 0;  // SEH 展开状态号 = 0
            sub_6055F0(2, 100, 100, 0, v137, 0);  // sub_6055F0 · 6 字段记录追加
          }
          else
          {
            v418 = 0;  // SEH 展开状态号 = 0
            sub_6055F0(2, 100, 100, 0, 0, 0);  // sub_6055F0 · 6 字段记录追加
          }
LABEL_219:
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v30;  // 返回结果对象 v30(0=不支持该 ID)
        }
        // ── [段 7] (28251, 29061] 段：29018/29020/29025/29030/29035/29053/29057/29060 八 ID ──
        //   典型：29053 → CNEquipmentKnuckleofChiefSign（首领之证拳套）；其余多为 CNEventEquipment 底座
        if ( nArg1 <= 29061 )  // nArg1 <= 29061 判定
        {
          if ( nArg1 != 29061 )  // nArg1 != 29061 判定
          {
            switch ( nArg1 )  // 按 nArg1 分派
            {
              case 29018:  // case 29018 → 装备参数结构构造
              case 29053:  // case 29053 → 装备参数结构构造
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                LOBYTE(v418) = 65;  // 把 65 低字节存入 v418(短串内联指针)
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v141 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v141 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 66;  // 把 66 低字节存入 v418(短串内联指针)
                  v413 = 0x80000;  // 标记待释放成员位 = 0x80000
                  v18 = sub_5151B0(nArg12, v141);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v413 & 0x80000) != 0 )  // 展开位 v413&0x80000 判定(需释放对应成员)
                  sub_445150(v370);  // sub_445150 · 装备同步资源清理
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              case 29020:  // case 29020 → 装备参数结构构造
              case 29057:  // case 29057 → 装备参数结构构造
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                LOBYTE(v418) = 59;  // 把 59 低字节存入 v418(短串内联指针)
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v140 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v140 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 60;  // 把 60 低字节存入 v418(短串内联指针)
                  v413 = 0x20000;  // 标记待释放成员位 = 0x20000
                  v18 = sub_5144A0(nArg12, v140);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v413 & 0x20000) != 0 )  // 展开位 v413&0x20000 判定(需释放对应成员)
                  sub_445150(v372);  // sub_445150 · 装备同步资源清理
                v229 = 48003;
                v228 = 0;
                v227 = 6;
                v226 = 100;
                v224 = 10;
                goto LABEL_268;  // 跳转 LABEL_268(收尾/共用分支)
              case 29025:  // case 29025 → 装备参数结构构造
              case 29060:  // case 29060 → 装备参数结构构造
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                LOBYTE(v418) = -4;  // SEH 展开状态号(低字节) = -4
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v142 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v142 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = -3;  // SEH 展开状态号(低字节) = -3
                  v414 = 0x10000;  // 标记待释放成员位 = 0x10000
                  v18 = sub_5144A0(nArg12, v142);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v414 & 0x10000) != 0 )  // 展开位 v414&0x10000 判定(需释放对应成员)
                  sub_445150(v368);  // sub_445150 · 装备同步资源清理
                sub_6048E0(4, 30, 3, 100);  // sub_6048E0 · 概率组写入
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              case 29030:
                break;  // 跳出本 switch(单 case 处理完)
              case 29035:
                goto LABEL_767;  // 跳转 LABEL_767(收尾/共用分支)
              default:
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
            }
          }
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -1;  // SEH 展开状态号(低字节) = -1
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v143 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v143 = sub_4E9B10 · 装备参数结构构造
            v418 = 256;  // SEH 展开状态号 = 256
            v414 = 0x20000;  // 标记待释放成员位 = 0x20000
            v18 = sub_5144A0(nArg12, v143);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v414 & 0x20000) != 0 )  // 展开位 v414&0x20000 判定(需释放对应成员)
            sub_445150(v366);  // sub_445150 · 装备同步资源清理
          v408 = 5;
          v409 = 0;
          v410 = 1132068864;  // 浮点常量 250f
          pMem = operator new(0x7Cu);  // 分配堆内存
          Block[0] = pMem;
          v418 = 258;  // SEH 展开状态号 = 258
          goto LABEL_874;  // 跳转 LABEL_874(收尾/共用分支)
        }
        // ── [段 8] (29061, 29315] 段：29070/29076/29081 + 29315 边界 ──
        //   该段出现 CNEquipmentVermote（维尔莫特，防篡读 ×0.2 写 this+373）
        if ( nArg1 <= 29315 )  // nArg1 <= 29315 判定
        {
          if ( nArg1 != 29315 )  // nArg1 != 29315 判定
          {
            if ( nArg1 == 29070 )  // nArg1 == 29070 判定
            {
LABEL_767:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 259;  // SEH 展开状态号 = 259
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v148 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v148 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 4;  // 把 4 低字节存入 v418(短串内联指针)
                v414 = 0x40000;  // 标记待释放成员位 = 0x40000
                v18 = sub_5144A0(nArg12, v148);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v414 & 0x40000) != 0 )  // 展开位 v414&0x40000 判定(需释放对应成员)
                sub_445150(v360);  // sub_445150 · 装备同步资源清理
              v408 = 4;
              v409 = 1;
              v410 = 1106247680;  // 置 v410 = 1106247680（float 30.0f）
              Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
              v418 = 262;  // SEH 展开状态号 = 262
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                v149 = sub_5101B0(&v408, 1, 30000, 1);  // v149 = sub_5101B0 · CNChangeStatus 构造器
              else
                v149 = 0;
              v418 = 0;  // SEH 展开状态号 = 0
              sub_6055F0(0, 2, 100, 0, v149, 0);  // sub_6055F0 · 6 字段记录追加
              sub_605650(1, 5, 100, 10, 0, 15, 0);  // sub_605650 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
            if ( nArg1 != 29076 )  // nArg1 != 29076 判定
            {
              if ( nArg1 == 29081 )  // nArg1 == 29081 判定
              {
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                v418 = 468;  // SEH 展开状态号 = 468
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v146 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v146 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = -43;  // SEH 展开状态号(低字节) = -43
                  pMem2 = (void *)0x20000;  // 标记待释放成员位 = 0x20000(第 2 组掩码)
                  v18 = sub_5144A0(153, v146);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( ((unsigned int)pMem2 & 0x20000) != 0 )  // 展开位 pMem2&0x20000 判定
                  sub_445150(v364);  // sub_445150 · 装备同步资源清理
                sub_6048E0(4, 100, 3, 100);  // sub_6048E0 · 概率组写入
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              }
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
            }
            v405 = 0;
            v406 = 0;
            v407 = 1101004800;  // 置 v407 = 1101004800（float 20.0f）
            v408 = 3;
            v409 = 0;
            v410 = 1101004800;  // 置 v410 = 1101004800（float 20.0f）
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 345;  // SEH 展开状态号 = 345
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v147 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v147 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 90;  // 把 90 低字节存入 v418(短串内联指针)
              v415 = 0x2000;  // 标记待释放成员位 = 0x2000
              v75 = sub_5144A0(148, v147);  // v75 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v75 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v415 & 0x2000) != 0 )  // 展开位 v415&0x2000 判定(需释放对应成员)
              sub_445150(v362);  // sub_445150 · 装备同步资源清理
            Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
            v418 = 348;  // SEH 展开状态号 = 348
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v76 = sub_5101B0(&v405, 2, 0, 1);  // v76 = sub_5101B0 · CNChangeStatus 构造器
              goto LABEL_309;  // 跳转 LABEL_309(收尾/共用分支)
            }
            goto LABEL_308;  // 跳转 LABEL_308(收尾/共用分支)
          }
LABEL_1216:
          Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
          v418 = 263;  // SEH 展开状态号 = 263
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v215 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v215 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 8;  // 把 8 低字节存入 v418(短串内联指针)
            v414 = 0x80000;  // 标记待释放成员位 = 0x80000
            v18 = sub_51B460(nArg12, v215);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v414 & 0x80000) != 0 )  // 展开位 v414&0x80000 判定(需释放对应成员)
            sub_445150(v250);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        // ── [段 9] 29319/29327/29329 三 ID：29327 附近为 CNEquipmentMadeInHeaven（天堂制造） ──
        if ( nArg1 != 29319 )  // nArg1 != 29319 判定
        {
          if ( nArg1 == 29327 )  // nArg1 == 29327 判定
          {
LABEL_1241:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = -17;  // SEH 展开状态号(低字节) = -17
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v219 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v219 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -16;  // SEH 展开状态号(低字节) = -16
              v414 = 4096;  // 标记待释放成员位 = 4096(0x1000)
              v18 = sub_516DE0(nArg12, v219);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v414 & 0x1000) != 0 )  // 展开位 v414&0x1000 判定(需释放对应成员)
              sub_445150(v240);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          // ── [段 10] (29329, 29921] 段：CNEventEquipment 通用 + 若干专属 ──
          if ( nArg1 == 29329 )  // nArg1 == 29329 判定
          {
LABEL_779:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 276;  // SEH 展开状态号 = 276
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v150 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v150 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 21;  // 把 21 低字节存入 v418(短串内联指针)
              v414 = (int)&unk_800000;
              v18 = sub_5144A0(nArg12, v150);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( ((unsigned int)&unk_800000 & v414) != 0 )  // 展开位掩码判定(v414)
              sub_445150(v238);  // sub_445150 · 装备同步资源清理
            sub_6048E0(0, 20, 3, 100);  // sub_6048E0 · 概率组写入
            sub_6048E0(1, 30, 2, 100);  // sub_6048E0 · 概率组写入
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        }
        goto LABEL_1231;  // 跳转 LABEL_1231(收尾/共用分支)
      }
      // ── [段 11] 北支收尾：>29921 → 二分 30207 再细分 ──
      if ( nArg1 > 29921 )  // 物品 ID > 29921(二分阈值,北支)
      {
        if ( nArg1 > 30207 )  // 物品 ID > 30207(二分阈值,北支)
        {
          switch ( nArg1 )  // 按 nArg1 分派
          {
            case 30209:  // case 30209 → 装备参数结构构造
            case 30230:  // case 30230 → 装备参数结构构造
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 314;  // SEH 展开状态号 = 314
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v171 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v171 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 59;  // 把 59 低字节存入 v418(短串内联指针)
                v415 = 8;  // 标记待释放成员位 = 8(0x8)
                v18 = sub_5144A0(nArg12, v171);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v415 & 8) != 0 )  // 展开位 v415&8 判定(需释放对应成员)
                sub_445150(v330);  // sub_445150 · 装备同步资源清理
              sub_6048E0(4, 44, 2, 100);  // sub_6048E0 · 概率组写入
              sub_605650(0, 2, 100, 6, 0, 4, 1);  // sub_605650 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            case 30220:  // case 30220 → 装备参数结构构造
            case 30241:  // case 30241 → 装备参数结构构造
              Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
              v418 = 317;  // SEH 展开状态号 = 317
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v172 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v172 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 62;  // 把 62 低字节存入 v418(短串内联指针)
                v415 = 16;  // 标记待释放成员位 = 16(0x10)
                v18 = sub_51B740(nArg12, v172);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v415 & 0x10) != 0 )  // 展开位 v415&0x10 判定(需释放对应成员)
                sub_445150(v328);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            case 30226:
              goto LABEL_879;  // 跳转 LABEL_879(收尾/共用分支)
            case 30227:
              goto LABEL_899;  // 跳转 LABEL_899(收尾/共用分支)
            case 30246:
              goto LABEL_915;  // 跳转 LABEL_915(收尾/共用分支)
            default:
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
          }
        }
        //   30207 单点（0x3CC 装备）
        if ( nArg1 == 30207 )  // nArg1 == 30207 判定
        {
LABEL_899:
          Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
          v418 = 311;  // SEH 展开状态号 = 311
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v170 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v170 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 56;  // 把 56 低字节存入 v418(短串内联指针)
            v415 = 4;  // 标记待释放成员位 = 4(0x4)
            v18 = sub_515520(nArg12, v170);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v415 & 4) != 0 )  // 展开位 v415&4 判定(需释放对应成员)
            sub_445150(v332);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        //   (29962, 30207) 段：29974/29976 两支
        if ( nArg1 > 29962 )  // 物品 ID > 29962(二分阈值,北支)
        {
          if ( nArg1 == 29974 )  // nArg1 == 29974 判定
          {
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 339;  // SEH 展开状态号 = 339
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v169 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v169 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 84;  // 把 84 低字节存入 v418(短串内联指针)
              v415 = 2048;  // 标记待释放成员位 = 2048(0x800)
              v18 = sub_5144A0(22, v169);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v415 & 0x800) == 0 )  // 展开位 v415&0x800 为 0(无需释放)
              goto LABEL_893;  // 跳转 LABEL_893(收尾/共用分支)
            v101 = &v336;
            goto LABEL_892;  // 跳转 LABEL_892(收尾/共用分支)
          }
          //   29976 支（第二路）
          if ( nArg1 == 29976 )  // nArg1 == 29976 判定
          {
            Block[0] = operator new(0x90Cu);  // 分配 2316 字节对象(operator new, Block[0] 承接)
            v418 = 342;  // SEH 展开状态号 = 342
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v165 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v165 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 87;  // 把 87 低字节存入 v418(短串内联指针)
              v415 = 4096;  // 标记待释放成员位 = 4096(0x1000)
              pObj2 = sub_514350(24, v165, 6, 0);
            }
            else
            {
              pObj2 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v415 & 0x1000) != 0 )  // 展开位 v415&0x1000 判定(需释放对应成员)
              sub_445150(v338);  // sub_445150 · 装备同步资源清理
            v167 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 176))(pObj2);  // 虚槽+176
            v168 = (double)sub_41A5E0(v167 + 112) * 0.25;  // v168 = sub_41A5E0 · crypt4byte 解密校验
            sub_41C150((uint64_t)v168);  // sub_41C150 · crypt4byte 初始化转发
            sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
            return pObj2;  // 返回对象 pObj2
          }
          //   (29976, 30204]：30204 附近单点
          if ( nArg1 != 30204 )  // nArg1 != 30204 判定
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_879:
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 272;  // SEH 展开状态号 = 272
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v164 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v164 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 17;  // 把 17 低字节存入 v418(短串内联指针)
            v414 = 0x400000;  // 标记待释放成员位 = 0x400000
            v18 = sub_5144A0(nArg12, v164);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v414 & 0x400000) != 0 )  // 展开位 v414&0x400000 判定(需释放对应成员)
            sub_445150(v334);  // sub_445150 · 装备同步资源清理
          v408 = 7;
          v409 = 0;
          v410 = 1106247680;  // 置 v410 = 1106247680（float 30.0f）
          pMem = operator new(0x7Cu);  // 分配堆内存
          Block[0] = pMem;
          v418 = 275;  // SEH 展开状态号 = 275
LABEL_874:
          if ( pMem != nullptr )  // pMem != nullptr 判定
            v145 = sub_5101B0(&v408, 1, 0, 1);  // v145 = sub_5101B0 · CNChangeStatus 构造器
          else
            v145 = 0;
          v418 = 0;  // SEH 展开状态号 = 0
          sub_6055F0(2, 100, 100, 0, v145, 0);  // sub_6055F0 · 6 字段记录追加
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        //   29962 / 29928 双 ID 同支 → 29952 / 29955
        if ( nArg1 == 29962 || nArg1 == 29928 )  // ID ∈ {29962,29928} 两 ID 共用一支
        {
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 307;  // SEH 展开状态号 = 307
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v163 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v163 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 52;  // 把 52 低字节存入 v418(短串内联指针)
            v415 = 2;  // 标记待释放成员位 = 2(0x2)
            v18 = sub_5144A0(nArg12, v163);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v415 & 2) != 0 )  // 展开位 v415&2 判定(需释放对应成员)
            sub_445150(v340);  // sub_445150 · 装备同步资源清理
          v408 = 10;
          v409 = 0;
          v410 = 1125515264;  // 浮点常量 150f
          pMem = operator new(0x7Cu);  // 分配堆内存
          Block[0] = pMem;
          v418 = 310;  // SEH 展开状态号 = 310
          goto LABEL_874;  // 跳转 LABEL_874(收尾/共用分支)
        }
        if ( nArg1 == 29952 )  // nArg1 == 29952 判定
          goto LABEL_836;  // 跳转 LABEL_836(收尾/共用分支)
        if ( nArg1 != 29955 )  // nArg1 != 29955 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
      }
      else if ( nArg1 != 29921 )  // ID 非 29921 分支
      {
        // ── [段 12] (29315, 29642] 段：29332 / 29335 / 29344 / 29346 → 四个装备 ID ──
        //   29346 = CNEquipmentAntiGravityLifter（反重力升降装置，CNSpecificEnemyEquipment(1,0) 系）
        if ( nArg1 <= 29642 )  // nArg1 <= 29642 判定
        {
          if ( nArg1 != 29642 )  // nArg1 != 29642 判定
          {
            if ( nArg1 <= 29627 )  // nArg1 <= 29627 判定
            {
              if ( nArg1 != 29627 )  // nArg1 != 29627 判定
              {
                if ( nArg1 <= 29346 )  // nArg1 <= 29346 判定
                {
                  switch ( nArg1 )  // 按 nArg1 分派
                  {
                    case 29346:  // case 29346 → 装备参数结构构造
                      Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
                      LOBYTE(v418) = -100;  // SEH 展开状态号(低字节) = -100
                      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                      {
                        v152 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v152 = sub_4E9B10 · 装备参数结构构造
                        LOBYTE(v418) = -99;  // SEH 展开状态号(低字节) = -99
                        v412 = 0x20000;
                        v18 = sub_517200(162, v152);
                      }
                      else
                      {
                        v18 = 0;
                      }
                      v418 = 0;  // SEH 展开状态号 = 0
                      if ( (v412 & 0x20000) != 0 )  // 展开位 v412&0x20000 判定(需释放对应成员)
                        sub_445150(v358);  // sub_445150 · 装备同步资源清理
                      goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                    case 29335:  // case 29335 → 装备参数结构构造
LABEL_1257:
                      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                      v418 = 282;  // SEH 展开状态号 = 282
                      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                      {
                        v221 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v221 = sub_4E9B10 · 装备参数结构构造
                        LOBYTE(v418) = 27;  // 把 27 低字节存入 v418(短串内联指针)
                        v414 = 0x2000000;  // 标记待释放成员位 = 0x2000000
                        v18 = sub_5144A0(nArg12, v221);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                      }
                      else
                      {
                        v18 = 0;
                      }
                      v418 = 0;  // SEH 展开状态号 = 0
                      if ( (v414 & 0x2000000) != 0 )  // 展开位 v414&0x2000000 判定(需释放对应成员)
                        sub_445150(v234);  // sub_445150 · 装备同步资源清理
                      sub_6048E0(3, 50, 2, 100);  // sub_6048E0 · 概率组写入
                      v229 = 1;
                      v228 = 3;
                      break;  // 跳出本 switch(单 case 处理完)
                    case 29344:  // case 29344 → 装备参数结构构造
LABEL_791:
                      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                      LOBYTE(v418) = -103;  // SEH 展开状态号(低字节) = -103
                      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                      {
                        v151 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v151 = sub_4E9B10 · 装备参数结构构造
                        LOBYTE(v418) = -102;  // SEH 展开状态号(低字节) = -102
                        v412 = 0x10000;
                        v18 = sub_5144A0(nArg12, v151);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                      }
                      else
                      {
                        v18 = 0;
                      }
                      v418 = 0;  // SEH 展开状态号 = 0
                      if ( (v412 & 0x10000) != 0 )  // 展开位 v412&0x10000 判定(需释放对应成员)
                        sub_445150(v242);  // sub_445150 · 装备同步资源清理
                      sub_6048E0(2, 100, 2, 100);  // sub_6048E0 · 概率组写入
                      v229 = 0;
                      v228 = 4;
                      break;  // 跳出本 switch(单 case 处理完)
                    default:
                      goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                  }
                  goto LABEL_571;  // 跳转 LABEL_571(收尾/共用分支)
                }
                //   29618 附近单点
                if ( nArg1 != 29618 )  // nArg1 != 29618 判定
                  goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_799:
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                v418 = 285;  // SEH 展开状态号 = 285
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v153 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v153 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 30;  // 把 30 低字节存入 v418(短串内联指针)
                  v414 = 0x4000000;  // 标记待释放成员位 = 0x4000000
                  v18 = sub_5144A0(nArg12, v153);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v414 & 0x4000000) != 0 )  // 展开位 v414&0x4000000 判定(需释放对应成员)
                  sub_445150(v352);  // sub_445150 · 装备同步资源清理
                sub_605650(1, 20, 100, 3, 0, 11, 2);  // sub_605650 · 6 字段记录追加
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              }
              goto LABEL_817;  // 跳转 LABEL_817(收尾/共用分支)
            }
            //   29627 / 29628 / 29632 / 29633 四连（每支 0x5B0 装备构造 + 概率组装载）
            if ( nArg1 != 29628 )  // nArg1 != 29628 判定
            {
              if ( nArg1 != 29632 )  // nArg1 != 29632 判定
              {
                if ( nArg1 != 29633 )  // nArg1 != 29633 判定
                  goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_804:
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                v418 = 294;  // SEH 展开状态号 = 294
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v154 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v154 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 39;  // 把 39 低字节存入 v418(短串内联指针)
                  v414 = 0x20000000;  // 标记待释放成员位 = 0x20000000
                  v18 = sub_5144A0(nArg12, v154);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v414 & 0x20000000) != 0 )  // 展开位 v414&0x20000000 判定(需释放对应成员)
                  sub_445150(v346);  // sub_445150 · 装备同步资源清理
                sub_6048E0(4, 100, 1, 100);  // sub_6048E0 · 概率组写入
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              }
LABEL_827:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 291;  // SEH 展开状态号 = 291
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v157 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v157 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 36;  // 把 36 低字节存入 v418(短串内联指针)
                v414 = 0x10000000;  // 标记待释放成员位 = 0x10000000
                v18 = sub_5144A0(nArg12, v157);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v414 & 0x10000000) != 0 )  // 展开位 v414&0x10000000 判定(需释放对应成员)
                sub_445150(v350);  // sub_445150 · 装备同步资源清理
              v229 = 1;
              v228 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
              goto LABEL_531;  // 跳转 LABEL_531(收尾/共用分支)
            }
LABEL_811:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 288;  // SEH 展开状态号 = 288
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v155 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v155 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 33;  // 把 33 低字节存入 v418(短串内联指针)
              v414 = 0x8000000;  // 标记待释放成员位 = 0x8000000
              v18 = sub_5144A0(nArg12, v155);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v414 & 0x8000000) != 0 )  // 展开位 v414&0x8000000 判定(需释放对应成员)
              sub_445150(v356);  // sub_445150 · 装备同步资源清理
            sub_6048E0(2, 40, 3, 100);  // sub_6048E0 · 概率组写入
            sub_605650(0, 3, 100, 5, 0, 4, 1);  // sub_605650 · 6 字段记录追加
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          goto LABEL_838;  // 跳转 LABEL_838(收尾/共用分支)
        }
        // ── [段 13] (29642, 29662] 段：29654 / 29658 ──
        if ( nArg1 <= 29662 )  // nArg1 <= 29662 判定
        {
          switch ( nArg1 )  // 按 nArg1 分派
          {
            case 29662:
              goto LABEL_827;  // 跳转 LABEL_827(收尾/共用分支)
            case 29654:  // case 29654 → 装备参数结构构造
              goto LABEL_799;  // 跳转 LABEL_799(收尾/共用分支)
            case 29658:  // case 29658 → 装备参数结构构造
LABEL_817:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 269;  // SEH 展开状态号 = 269
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v156 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v156 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 14;  // 把 14 低字节存入 v418(短串内联指针)
                v414 = 0x200000;  // 标记待释放成员位 = 0x200000
                v18 = sub_5144A0(nArg12, v156);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v414 & 0x200000) != 0 )  // 展开位 v414&0x200000 判定(需释放对应成员)
                sub_445150(v354);  // sub_445150 · 装备同步资源清理
              sub_6048E0(2, 40, 3, 100);  // sub_6048E0 · 概率组写入
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            default:
              break;  // 跳出本 switch(单 case 处理完)
          }
          if ( nArg1 != 29661 )  // nArg1 != 29661 判定
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
          goto LABEL_811;  // 跳转 LABEL_811(收尾/共用分支)
        }
        //   29667 / 29668 双 ID
        if ( nArg1 == 29667 )  // nArg1 == 29667 判定
          goto LABEL_804;  // 跳转 LABEL_804(收尾/共用分支)
        if ( nArg1 == 29668 )  // nArg1 == 29668 判定
        {
LABEL_838:
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 297;  // SEH 展开状态号 = 297
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v159 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v159 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 42;  // 把 42 低字节存入 v418(短串内联指针)
            v414 = 0x40000000;  // 标记待释放成员位 = 0x40000000
            v18 = sub_5144A0(nArg12, v159);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v414 & 0x40000000) != 0 )  // 展开位 v414&0x40000000 判定(需释放对应成员)
            sub_445150(v348);  // sub_445150 · 装备同步资源清理
          sub_6048E0(0, 30, 5, 100);  // sub_6048E0 · 概率组写入
          sub_6048E0(1, 30, 5, 100);  // sub_6048E0 · 概率组写入
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        //   29918 单点
        if ( nArg1 != 29918 )  // nArg1 != 29918 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_836:
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        v418 = 300;  // SEH 展开状态号 = 300
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v158 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v158 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = 45;  // 把 45 低字节存入 v418(短串内联指针)
          v414 = 0x80000000;  // 标记待释放成员位 = 0x80000000
          v18 = sub_5144A0(nArg12, v158);  // v18 = sub_5144A0 · CNEventEquipment 构造器
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( v414 < 0 )  // v414 < 0 判定(无效值)
          sub_445150(v342);  // sub_445150 · 装备同步资源清理
        Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
        v418 = 303;  // SEH 展开状态号 = 303
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          v162 = sub_4B3DF0(12, 0, 1176256512, 3000, 1);  // v162 = sub_4B3DF0 · CNChangeStatus 构造
        else
          v162 = 0;
        v418 = 0;  // SEH 展开状态号 = 0
        sub_6055F0(0, 1, 100, 0, v162, 0);  // sub_6055F0 · 6 字段记录追加
        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
      }
      Block[0] = operator new(0x90Cu);  // 分配 2316 字节对象(operator new, Block[0] 承接)
      v418 = 304;  // SEH 展开状态号 = 304
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v160 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v160 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = 49;  // 把 49 低字节存入 v418(短串内联指针)
        v415 = 1;  // 标记待释放成员位 = 1(0x1)
        pObj = sub_514350(nArg12, v160, 12, 0);
      }
      else
      {
        pObj = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( (v415 & 1) != 0 )  // 展开位 v415&1 判定(需释放对应成员)
        sub_445150(v344);  // sub_445150 · 装备同步资源清理
      v161 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);  // 虚槽+176
      Block[0] = (void *)sub_41A5E0(v161 + 112);  // sub_41A5E0 · crypt4byte 解密校验
      v12 = (double)(int)Block[0] * 0.1;
      goto LABEL_16;  // 跳转 LABEL_16(收尾/共用分支)
    }
    // ── [段 14] ★ 北支最大段 (30207, 32236]（共 306 行）—— 3 万段装备主区 ──
    //   骨架（本段极密）：Block[0]=new(0x5B0/0x5D4/0x3CC/0x3CD0) → 构造器 → 置 0x1000 位标志
    if ( nArg1 <= 32236 )  // nArg1 <= 32236 判定
    {
      if ( nArg1 != 32236 )  // nArg1 != 32236 判定
      {
        if ( nArg1 <= 31657 )  // nArg1 <= 31657 判定
        {
          if ( nArg1 != 31657 )  // nArg1 != 31657 判定
          {
            //   31354/31333/31340/31365/31374/31630 等 ID 逐点判定
            if ( nArg1 <= 31354 )  // nArg1 <= 31354 判定
            {
              if ( nArg1 != 31354 )  // nArg1 != 31354 判定
              {
                if ( nArg1 <= 31060 )  // nArg1 <= 31060 判定
                {
                  if ( nArg1 != 31060 )  // nArg1 != 31060 判定
                  {
                    switch ( nArg1 )  // 按 nArg1 分派
                    {
                      case 31033:  // case 31033 → 装备参数结构构造
                      case 31052:  // case 31052 → 装备参数结构构造
                        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                        LOBYTE(v418) = 77;  // 把 77 低字节存入 v418(短串内联指针)
                        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                        {
                          v174 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v174 = sub_4E9B10 · 装备参数结构构造
                          LOBYTE(v418) = 78;  // 把 78 低字节存入 v418(短串内联指针)
                          v413 = (int)&unk_800000;
                          v18 = sub_5144A0(nArg12, v174);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                        }
                        else
                        {
                          v18 = 0;
                        }
                        v418 = 0;  // SEH 展开状态号 = 0
                        if ( ((unsigned int)&unk_800000 & v413) != 0 )  // 展开位掩码判定(v413)
                          sub_445150(v324);  // sub_445150 · 装备同步资源清理
                        sub_6048E0(0, 20, 2, 100);  // sub_6048E0 · 概率组写入
                        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                      case 31037:
                        break;  // 跳出本 switch(单 case 处理完)
                      case 31041:
                        goto LABEL_947;  // 跳转 LABEL_947(收尾/共用分支)
                      default:
                        goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                    }
                  }
                  Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                  LOBYTE(v418) = 80;  // 把 80 低字节存入 v418(短串内联指针)
                  if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                  {
                    v175 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v175 = sub_4E9B10 · 装备参数结构构造
                    LOBYTE(v418) = 81;  // 把 81 低字节存入 v418(短串内联指针)
                    v413 = 0x1000000;  // 标记待释放成员位 = 0x1000000
                    v18 = sub_5144A0(nArg12, v175);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;  // SEH 展开状态号 = 0
                  if ( (v413 & 0x1000000) != 0 )  // 展开位 v413&0x1000000 判定(需释放对应成员)
                    sub_445150(v322);  // sub_445150 · 装备同步资源清理
                  sub_6048E0(2, 50, 5, 100);  // sub_6048E0 · 概率组写入
                  goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                }
                //   31068 单点
                if ( nArg1 == 31068 )  // nArg1 == 31068 判定
                {
LABEL_947:
                  Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                  LOBYTE(v418) = 113;  // 把 113 低字节存入 v418(短串内联指针)
                  if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                  {
                    v177 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v177 = sub_4E9B10 · 装备参数结构构造
                    LOBYTE(v418) = 114;  // 把 114 低字节存入 v418(短串内联指针)
                    v412 = 8;
                    v18 = sub_5144A0(nArg12, v177);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;  // SEH 展开状态号 = 0
                  if ( (v412 & 8) != 0 )  // 展开位 v412&8 判定(需释放对应成员)
                    sub_445150(v320);  // sub_445150 · 装备同步资源清理
                  v408 = 5;
                  v409 = 0;
                  v410 = 1137180672;  // 浮点常量 400f
                  Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
                  LOBYTE(v418) = 116;  // 把 116 低字节存入 v418(短串内联指针)
                  if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                  {
                    v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
                    goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
                  }
                  goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
                }
                if ( nArg1 != 31333 )  // nArg1 != 31333 判定
                {
                  if ( nArg1 != 31340 )  // nArg1 != 31340 判定
                    goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                  goto LABEL_945;  // 跳转 LABEL_945(收尾/共用分支)
                }
              }
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 83;  // 把 83 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v178 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v178 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 84;  // 把 84 低字节存入 v418(短串内联指针)
                v413 = 0x2000000;  // 标记待释放成员位 = 0x2000000
                v18 = sub_5144A0(nArg12, v178);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v413 & 0x2000000) == 0 )  // 展开位 v413&0x2000000 为 0(无需释放)
              {
LABEL_988:
                sub_605650(0, 1, 100, 5, 0, 13, 0);  // sub_605650 · 6 字段记录追加
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              }
              v179 = &v318;
LABEL_987:
              sub_445150(v179);  // sub_445150 · 装备同步资源清理
              goto LABEL_988;  // 跳转 LABEL_988(收尾/共用分支)
            }
            //   (31365, 31632] 段：31632 边界 + 31374 / 31630（0x5B0）
            if ( nArg1 <= 31632 )  // nArg1 <= 31632 判定
            {
              if ( nArg1 != 31632 )  // nArg1 != 31632 判定
              {
                if ( nArg1 != 31365 )  // nArg1 != 31365 判定
                {
                  if ( nArg1 == 31374 )  // nArg1 == 31374 判定
                  {
                    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                    v418 = 355;  // SEH 展开状态号 = 355
                    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                    {
                      v181 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v181 = sub_4E9B10 · 装备参数结构构造
                      LOBYTE(v418) = 100;  // 把 100 低字节存入 v418(短串内联指针)
                      v415 = 0x10000;  // 标记待释放成员位 = 0x10000
                      v18 = sub_5144A0(142, v181);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;  // SEH 展开状态号 = 0
                    if ( (v415 & 0x10000) != 0 )  // 展开位 v415&0x10000 判定(需释放对应成员)
                      sub_445150(v314);  // sub_445150 · 装备同步资源清理
                    sub_6055A0(0, 2, 100, 80, 0, 40002);  // sub_6055A0 · 6 字段记录追加
                    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                  }
                  if ( nArg1 == 31630 )  // nArg1 == 31630 判定
                  {
                    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                    LOBYTE(v418) = 104;  // 把 104 低字节存入 v418(短串内联指针)
                    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                    {
                      v180 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v180 = sub_4E9B10 · 装备参数结构构造
                      LOBYTE(v418) = 105;  // 把 105 低字节存入 v418(短串内联指针)
                      v412 = 1;
                      v18 = sub_514EF0(142, v180);
                    }
                    else
                    {
                      v18 = 0;
                    }
                    v418 = 0;  // SEH 展开状态号 = 0
                    if ( (v412 & 1) != 0 )  // 展开位 v412&1 判定(需释放对应成员)
                      sub_445150(v316);  // sub_445150 · 装备同步资源清理
                    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                  }
                  goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                }
LABEL_945:
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                LOBYTE(v418) = 101;  // 把 101 低字节存入 v418(短串内联指针)
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v176 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v176 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 102;  // 把 102 低字节存入 v418(短串内联指针)
                  v413 = 0x80000000;  // 标记待释放成员位 = 0x80000000
                  v18 = sub_5144A0(nArg12, v176);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( v413 < 0 )  // v413 < 0 判定(无效值)
                  sub_445150(v312);  // sub_445150 · 装备同步资源清理
                sub_6055A0(0, 2, 100, 20, 0, 40002);  // sub_6055A0 · 6 字段记录追加
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              }
              goto LABEL_982;  // 跳转 LABEL_982(收尾/共用分支)
            }
            //   31636 / 31637 / 31653 三点
            if ( nArg1 != 31636 )  // nArg1 != 31636 判定
            {
              if ( nArg1 != 31637 )  // nArg1 != 31637 判定
              {
                if ( nArg1 != 31653 )  // nArg1 != 31653 判定
                  goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_982:
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                LOBYTE(v418) = 86;  // 把 86 低字节存入 v418(短串内联指针)
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v182 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v182 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 87;  // 把 87 低字节存入 v418(短串内联指针)
                  v413 = 0x4000000;  // 标记待释放成员位 = 0x4000000
                  v18 = sub_5144A0(nArg12, v182);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v413 & 0x4000000) == 0 )  // 展开位 v413&0x4000000 为 0(无需释放)
                  goto LABEL_988;  // 跳转 LABEL_988(收尾/共用分支)
                v179 = &v310;
                goto LABEL_987;  // 跳转 LABEL_987(收尾/共用分支)
              }
LABEL_1004:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 89;  // 把 89 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v184 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v184 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 90;  // 把 90 低字节存入 v418(短串内联指针)
                v413 = 0x8000000;  // 标记待释放成员位 = 0x8000000
                v18 = sub_5144A0(nArg12, v184);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v413 & 0x8000000) != 0 )  // 展开位 v413&0x8000000 判定(需释放对应成员)
                sub_445150(v306);  // sub_445150 · 装备同步资源清理
              sub_605650(1, 10, 100, 1, 0, 4, 0);  // sub_605650 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
          }
          Block[0] = operator new(0x90Cu);  // 分配 2316 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 107;  // 把 107 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v183 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v183 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 108;  // 把 108 低字节存入 v418(短串内联指针)
            v412 = 2;
            v18 = sub_514350(nArg12, v183, 12, 0);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 2) != 0 )  // 展开位 v412&2 判定(需释放对应成员)
            sub_445150(v308);  // sub_445150 · 装备同步资源清理
          sub_41C150(100);  // sub_41C150 · crypt4byte 初始化转发
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        //   (31653, 31957] 段：31935/31938/31939/31940/31941/31951 六点 ──
        //   31661 亦在此段内
        if ( nArg1 <= 31957 )  // nArg1 <= 31957 判定
        {
          if ( nArg1 == 31957 )  // nArg1 == 31957 判定
            goto LABEL_1022;  // 跳转 LABEL_1022(收尾/共用分支)
          if ( nArg1 <= 31939 )  // nArg1 <= 31939 判定
          {
            if ( nArg1 != 31939 )  // nArg1 != 31939 判定
            {
              if ( nArg1 <= 31935 )  // nArg1 <= 31935 判定
              {
                if ( nArg1 != 31935 )  // nArg1 != 31935 判定
                {
                  if ( nArg1 == 31661 )  // nArg1 == 31661 判定
                    goto LABEL_1004;  // 跳转 LABEL_1004(收尾/共用分支)
                  if ( nArg1 != 31934 )  // nArg1 != 31934 判定
                    goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_1016:
                  Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                  LOBYTE(v418) = 92;  // 把 92 低字节存入 v418(短串内联指针)
                  if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                  {
                    v186 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v186 = sub_4E9B10 · 装备参数结构构造
                    LOBYTE(v418) = 93;  // 把 93 低字节存入 v418(短串内联指针)
                    v413 = 0x10000000;  // 标记待释放成员位 = 0x10000000
                    v18 = sub_5144A0(nArg12, v186);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;  // SEH 展开状态号 = 0
                  if ( (v413 & 0x10000000) != 0 )  // 展开位 v413&0x10000000 判定(需释放对应成员)
                    sub_445150(v304);  // sub_445150 · 装备同步资源清理
                  sub_6048E0(4, 30, 2, 100);  // sub_6048E0 · 概率组写入
                  goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                }
LABEL_1022:
                Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                LOBYTE(v418) = 95;  // 把 95 低字节存入 v418(短串内联指针)
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v187 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v187 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 96;  // 把 96 低字节存入 v418(短串内联指针)
                  v413 = 0x20000000;  // 标记待释放成员位 = 0x20000000
                  v18 = sub_5144A0(nArg12, v187);  // v18 = sub_5144A0 · CNEventEquipment 构造器
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v413 & 0x20000000) != 0 )  // 展开位 v413&0x20000000 判定(需释放对应成员)
                  sub_445150(v302);  // sub_445150 · 装备同步资源清理
                sub_6048E0(0, 20, 2, 100);  // sub_6048E0 · 概率组写入
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              }
              if ( nArg1 != 31938 )  // nArg1 != 31938 判定
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_1011:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 110;  // 把 110 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v185 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v185 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 111;  // 把 111 低字节存入 v418(短串内联指针)
                v412 = 4;
                v18 = sub_5144A0(nArg12, v185);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v412 & 4) != 0 )  // 展开位 v412&4 判定(需释放对应成员)
                sub_445150(v296);  // sub_445150 · 装备同步资源清理
              v229 = 48001;
              v228 = 0;
              v227 = 10;
              goto LABEL_267;  // 跳转 LABEL_267(收尾/共用分支)
            }
LABEL_1033:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = 98;  // 把 98 低字节存入 v418(短串内联指针)
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v188 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v188 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 99;  // 把 99 低字节存入 v418(短串内联指针)
              v413 = 0x40000000;  // 标记待释放成员位 = 0x40000000
              v18 = sub_5144A0(nArg12, v188);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v413 & 0x40000000) != 0 )  // 展开位 v413&0x40000000 判定(需释放对应成员)
              sub_445150(v300);  // sub_445150 · 装备同步资源清理
            sub_605650(1, 4, 100, 4, 0, 3, 2);  // sub_605650 · 6 字段记录追加
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          if ( nArg1 != 31940 )  // nArg1 != 31940 判定
          {
            if ( nArg1 != 31941 )  // nArg1 != 31941 判定
            {
              if ( nArg1 != 31951 )  // nArg1 != 31951 判定
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
              goto LABEL_1016;  // 跳转 LABEL_1016(收尾/共用分支)
            }
LABEL_1054:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = 117;  // 把 117 低字节存入 v418(短串内联指针)
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v191 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v191 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 118;  // 把 118 低字节存入 v418(短串内联指针)
              v412 = 16;
              v18 = sub_5150B0(nArg12, v191);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v412 & 0x10) != 0 )  // 展开位 v412&0x10 判定(需释放对应成员)
              sub_445150(v294);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
LABEL_1039:
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -14;  // SEH 展开状态号(低字节) = -14
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v189 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v189 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -13;  // SEH 展开状态号(低字节) = -13
            v414 = 0x2000;  // 标记待释放成员位 = 0x2000
            v18 = sub_5144A0(nArg12, v189);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v414 & 0x2000) != 0 )  // 展开位 v414&0x2000 判定(需释放对应成员)
            sub_445150(v298);  // sub_445150 · 装备同步资源清理
          sub_6055A0(0, 2, 100, 30, 0, 40002);  // sub_6055A0 · 6 字段记录追加
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        //   (31957, 31967] 段：31962/31965/31966
        if ( nArg1 <= 31967 )  // nArg1 <= 31967 判定
        {
          if ( nArg1 == 31967 )  // nArg1 == 31967 判定
            goto LABEL_1054;  // 跳转 LABEL_1054(收尾/共用分支)
          if ( nArg1 == 31962 )  // nArg1 == 31962 判定
            goto LABEL_1011;  // 跳转 LABEL_1011(收尾/共用分支)
          if ( nArg1 != 31965 )  // nArg1 != 31965 判定
          {
            if ( nArg1 != 31966 )  // nArg1 != 31966 判定
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
            goto LABEL_1033;  // 跳转 LABEL_1033(收尾/共用分支)
          }
          goto LABEL_1039;  // 跳转 LABEL_1039(收尾/共用分支)
        }
        //   31977 单点
        if ( nArg1 == 31977 )  // nArg1 == 31977 判定
        {
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 474;  // SEH 展开状态号 = 474
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v192 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v192 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -37;  // SEH 展开状态号(低字节) = -37
            pMem2 = (void *)0x80000;  // 标记待释放成员位 = 0x80000(第 2 组掩码)
            v30 = sub_5144A0(233, v192);  // v30 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v30 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( ((unsigned int)pMem2 & 0x80000) != 0 )  // 展开位 pMem2&0x80000 判定
            sub_445150(v292);  // sub_445150 · 装备同步资源清理
          v408 = 18;
          v409 = 0;
          v410 = 1092616192;  // 置 v410 = 1092616192（float 10.0f）
          Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
          v418 = 477;  // SEH 展开状态号 = 477
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            v193 = sub_5101B0(&v408, 1, 0, 1);  // v193 = sub_5101B0 · CNChangeStatus 构造器
          else
            v193 = 0;
          v418 = 0;  // SEH 展开状态号 = 0
          sub_6055F0(2, 100, 100, 0, v193, 0);  // sub_6055F0 · 6 字段记录追加
          goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
        }
        //   31978 单点
        if ( nArg1 == 31978 )  // nArg1 == 31978 判定
          goto LABEL_1054;  // 跳转 LABEL_1054(收尾/共用分支)
        //   32231 边界
        if ( nArg1 != 32231 )  // nArg1 != 32231 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_1052:
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        LOBYTE(v418) = -11;  // SEH 展开状态号(低字节) = -11
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v190 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v190 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = -10;  // SEH 展开状态号(低字节) = -10
          v414 = 0x4000;  // 标记待释放成员位 = 0x4000
          v18 = sub_5144A0(nArg12, v190);  // v18 = sub_5144A0 · CNEventEquipment 构造器
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (v414 & 0x4000) != 0 )  // 展开位 v414&0x4000 判定(需释放对应成员)
          sub_445150(v288);  // sub_445150 · 装备同步资源清理
        v408 = 18;
        v409 = 0;
        v410 = 1092616192;  // 置 v410 = 1092616192（float 10.0f）
        Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
        LOBYTE(v418) = -8;  // SEH 展开状态号(低字节) = -8
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
          goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
        }
        goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
      }
LABEL_1078:
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      LOBYTE(v418) = -7;  // SEH 展开状态号(低字节) = -7
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v194 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v194 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -6;  // SEH 展开状态号(低字节) = -6
        v414 = 0x8000;  // 标记待释放成员位 = 0x8000
        v18 = sub_5144A0(nArg12, v194);  // v18 = sub_5144A0 · CNEventEquipment 构造器
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( (v414 & 0x8000) != 0 )  // 展开位 v414&0x8000 判定(需释放对应成员)
        sub_445150(v290);  // sub_445150 · 装备同步资源清理
      sub_6055A0(0, 3, 100, 50, 0, 40002);  // sub_6055A0 · 6 字段记录追加
      goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
    }
    // ── [段 15] ★ (32236, 39356] 段（192 行）—— 3.3 万段（时装/高级装备） ──
    //   33643 为分界：>33643 与 <=33643 两大子树
    if ( nArg1 > 33643 )  // 物品 ID > 33643(二分阈值,北支)
    {
      if ( nArg1 > 39356 )  // 物品 ID > 39356(二分阈值,北支)
      {
        switch ( nArg1 )  // 按 nArg1 分派
        {
          case 39357:
            goto LABEL_791;  // 跳转 LABEL_791(收尾/共用分支)
          case 39361:
            goto LABEL_1241;  // 跳转 LABEL_1241(收尾/共用分支)
          case 39364:
            goto LABEL_779;  // 跳转 LABEL_779(收尾/共用分支)
          case 39365:
            goto LABEL_1250;  // 跳转 LABEL_1250(收尾/共用分支)
          case 39368:  // case 39368 → 装备参数结构构造
            goto LABEL_1257;  // 跳转 LABEL_1257(收尾/共用分支)
          case 39378:  // case 39378 → 装备参数结构构造
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 352;  // SEH 展开状态号 = 352
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v222 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v222 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 97;  // 把 97 低字节存入 v418(短串内联指针)
              v415 = 0x8000;  // 标记待释放成员位 = 0x8000
              v18 = sub_517A60(nArg12, v222);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v415 & 0x8000) != 0 )  // 展开位 v415&0x8000 判定(需释放对应成员)
              sub_445150(v232);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          case 39381:  // case 39381 → 装备参数结构构造
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 471;  // SEH 展开状态号 = 471
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v223 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v223 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -40;  // SEH 展开状态号(低字节) = -40
              pMem2 = (void *)0x40000;  // 标记待释放成员位 = 0x40000(第 2 组掩码)
              v18 = sub_5144A0(nArg12, v223);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( ((unsigned int)pMem2 & 0x40000) == 0 )  // 字节位掩码 pMem2&0x40000 为 0(无需释放)
              goto LABEL_1274;  // 跳转 LABEL_1274(收尾/共用分支)
            v116 = &v230;
            break;  // 跳出本 switch(单 case 处理完)
          default:
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        }
        goto LABEL_1273;  // 跳转 LABEL_1273(收尾/共用分支)
      }
      //   (39356, ∞) 段：39357/39361/39364/39365/39368/39378/39381 七个 ID（时装 ID 段） ──
      //   39378 = CNEquipmentBloodsoul（血魂）
      if ( nArg1 != 39356 )  // nArg1 != 39356 判定
      {
        if ( nArg1 <= 33933 )  // nArg1 <= 33933 判定
        {
          //   (33933, 39352] 段：33936 / 33943 两点
          //   39352 单点
          switch ( nArg1 )  // 按 nArg1 分派
          {
            case 33933:  // case 33933 → 装备参数结构构造
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 420;  // SEH 展开状态号 = 420
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v214 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v214 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -91;  // SEH 展开状态号(低字节) = -91
                pMem2 = (void *)4;  // pMem2 = 取 4(转指针/类型)
                v18 = sub_5144A0(141, v214);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( ((uint8_t)pMem2 & 4) != 0 )  // 字节位掩码 pMem2&4 判定(需释放)
                sub_445150(v252);  // sub_445150 · 装备同步资源清理
              sub_605650(1, 3, 100, 12, 0, 16, 2);  // sub_605650 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            case 33926:
              Block[0] = (void *)3;  // Block[0] = 常量 3
              sub_431230(Block);  // sub_431230 · uint32 vector push_back
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 386;  // SEH 展开状态号 = 386
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                pMem2 = &v226;
                sub_435020(pBuf);  // sub_435020 · uint32 向量整体赋值
                LOBYTE(v418) = -125;  // SEH 展开状态号(低字节) = -125
                v213 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v213 = sub_4E9B10 · 装备参数结构构造
                v415 = 0x4000000;  // 标记待释放成员位 = 0x4000000
                v418 = 389;  // SEH 展开状态号 = 389
                v18 = sub_517D90(134, v213, v226, (void *)v227, v228, v229);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v415 & 0x4000000) != 0 )  // 展开位 v415&0x4000000 判定(需释放对应成员)
                sub_445150(v254);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            case 33931:
              Block[0] = (void *)37;  // Block[0] = 常量 37
              sub_431230(Block);  // sub_431230 · uint32 vector push_back
              Block[0] = operator new(0x5D4u);  // 分配 1492 字节对象(operator new, Block[0] 承接)
              v418 = 410;  // SEH 展开状态号 = 410
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                pMem2 = &v226;
                sub_435020(pBuf);  // sub_435020 · uint32 向量整体赋值
                LOBYTE(v418) = -101;  // SEH 展开状态号(低字节) = -101
                v212 = (void *)sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v212 = sub_4E9B10 · 装备参数结构构造
                pMem2 = (void *)1;  // pMem2 = 取 1(转指针/类型)
                v418 = 413;  // SEH 展开状态号 = 413
                v18 = sub_518360(139, v212, v226, (void *)v227, v228, v229);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( ((uint8_t)pMem2 & 1) != 0 )  // 字节位掩码 pMem2&1 判定(需释放)
                sub_445150(v256);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            case 33932:
              Block[0] = (void *)26;  // Block[0] = 常量 26
              sub_431230(Block);  // sub_431230 · uint32 vector push_back
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 415;  // SEH 展开状态号 = 415
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                pMem2 = &v226;
                sub_435020(pBuf);  // sub_435020 · uint32 向量整体赋值
                LOBYTE(v418) = -96;  // SEH 展开状态号(低字节) = -96
                v211 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v211 = sub_4E9B10 · 装备参数结构构造
                pMem2 = (void *)2;  // pMem2 = 取 2(转指针/类型)
                v418 = 418;  // SEH 展开状态号 = 418
                v18 = sub_518100(140, v211, v226, (void *)v227, v228, v229);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( ((uint8_t)pMem2 & 2) != 0 )  // 字节位掩码 pMem2&2 判定(需释放)
                sub_445150(v258);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            default:
              break;  // 跳出本 switch(单 case 处理完)
          }
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        }
        if ( nArg1 == 33936 )  // nArg1 == 33936 判定
        {
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 423;  // SEH 展开状态号 = 423
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v217 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v217 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -88;  // SEH 展开状态号(低字节) = -88
            pMem2 = (void *)8;  // pMem2 = 取 8(转指针/类型)
            v18 = sub_518DE0(144, v217);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( ((uint8_t)pMem2 & 8) != 0 )  // 字节位掩码 pMem2&8 判定(需释放)
            sub_445150(v246);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        if ( nArg1 == 33943 )  // nArg1 == 33943 判定
        {
          Block[0] = operator new(0x5B4u);  // 分配 1460 字节对象(operator new, Block[0] 承接)
          v418 = 481;  // SEH 展开状态号 = 481
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v216 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v216 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -30;  // SEH 展开状态号(低字节) = -30
            pMem2 = (void *)0x200000;  // 标记待释放成员位 = 0x200000(第 2 组掩码)
            v30 = sub_519560(151, v216);
          }
          else
          {
            v30 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( ((unsigned int)pMem2 & 0x200000) != 0 )  // 展开位 pMem2&0x200000 判定
            sub_445150(v248);  // sub_445150 · 装备同步资源清理
          goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
        }
        if ( nArg1 != 39352 )  // nArg1 != 39352 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        goto LABEL_1216;  // 跳转 LABEL_1216(收尾/共用分支)
      }
LABEL_1231:
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      v418 = 266;  // SEH 展开状态号 = 266
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v218 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v218 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = 11;  // 把 11 低字节存入 v418(短串内联指针)
        v414 = 0x100000;  // 标记待释放成员位 = 0x100000
        v18 = sub_51B540(nArg12, v218);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( (v414 & 0x100000) != 0 )  // 展开位 v414&0x100000 判定(需释放对应成员)
        sub_445150(v244);  // sub_445150 · 装备同步资源清理
      goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
    }
    if ( nArg1 != 33643 )  // nArg1 != 33643 判定
    {
      //   (33643, 33933] 段：33926 / 33931 / 33932 / 33933 四点 ──
      //   33926 = CNEquipmentSpiritCall（精灵召唤，Block 非空则 sub_4ED3F0 装数组）
      //   33931 = CNEquipmentPureGuardian（纯粹守护者，0x5D4 大构造 62 行）/ 33932 = CNEquipmentQuattroMephist（四重梅菲斯特）
      if ( nArg1 <= 33333 )  // nArg1 <= 33333 判定
      {
        if ( nArg1 == 33333 )  // nArg1 == 33333 判定
        {
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 429;  // SEH 展开状态号 = 429
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v202 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v202 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -82;  // SEH 展开状态号(低字节) = -82
            pMem2 = (void *)32;  // pMem2 = 取 32(转指针/类型)
            v18 = sub_5144A0(53, v202);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( ((uint8_t)pMem2 & 0x20) != 0 )  // 展开位 pMem2&0x20 判定
            sub_445150(v274);  // sub_445150 · 装备同步资源清理
          sub_605650(0, 3, 100, 12, 0, 12, 0);  // sub_605650 · 6 字段记录追加
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        if ( nArg1 > 33033 )  // 物品 ID > 33033(二分阈值,北支)
        {
          if ( nArg1 == 33035 )  // nArg1 == 33035 判定
          {
            Block[0] = (void *)13;  // Block[0] = 常量 13
            sub_431230(Block);  // sub_431230 · uint32 vector push_back
            Block[0] = operator new(0x5D4u);  // 分配 1492 字节对象(operator new, Block[0] 承接)
            v418 = 438;  // SEH 展开状态号 = 438
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              pMem2 = &v226;
              sub_435020(pBuf);  // sub_435020 · uint32 向量整体赋值
              LOBYTE(v418) = -73;  // SEH 展开状态号(低字节) = -73
              v201 = (void *)sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v201 = sub_4E9B10 · 装备参数结构构造
              pMem2 = (void *)256;  // pMem2 = 取 256(转指针/类型)
              v418 = 441;  // SEH 展开状态号 = 441
              v18 = sub_518B20(11, v201, v226, (void *)v227, v228, v229);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (BYTE1(pMem2) & 1) != 0 )  // 字节位 pMem2 位 1 判定
              sub_445150(v276);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          if ( nArg1 == 33327 )  // nArg1 == 33327 判定
          {
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 391;  // SEH 展开状态号 = 391
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v200 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v200 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -120;  // SEH 展开状态号(低字节) = -120
              v415 = 0x8000000;  // 标记待释放成员位 = 0x8000000
              v18 = sub_5144A0(47, v200);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v415 & 0x8000000) != 0 )  // 展开位 v415&0x8000000 判定(需释放对应成员)
              sub_445150(v278);  // sub_445150 · 装备同步资源清理
            sub_6055A0(0, 1, 100, 5, 0, 46001);  // sub_6055A0 · 6 字段记录追加
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          if ( nArg1 != 33331 )  // nArg1 != 33331 判定
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
          Block[0] = operator new(0x90Cu);  // 分配 2316 字节对象(operator new, Block[0] 承接)
          v418 = 426;  // SEH 展开状态号 = 426
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v198 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v198 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -85;  // SEH 展开状态号(低字节) = -85
            pMem2 = (void *)16;  // pMem2 = 取 16(转指针/类型)
            pObj = sub_514350(51, v198, 7, 0);
          }
          else
          {
            pObj = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( ((uint8_t)pMem2 & 0x10) != 0 )  // 展开位 pMem2&0x10 判定
            sub_445150(v280);  // sub_445150 · 装备同步资源清理
          v199 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);  // 虚槽+176
          Block[0] = (void *)sub_41A5E0(v199 + 112);  // sub_41A5E0 · crypt4byte 解密校验
          v12 = (double)(int)Block[0] * 0.5;
          goto LABEL_16;  // 跳转 LABEL_16(收尾/共用分支)
        }
        if ( nArg1 == 33033 )  // nArg1 == 33033 判定
        {
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 435;  // SEH 展开状态号 = 435
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v197 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v197 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -76;  // SEH 展开状态号(低字节) = -76
            pMem2 = (void *)128;  // pMem2 = 取 128(转指针/类型)
            v18 = sub_5144A0(9, v197);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (char)pMem2 < 0 )  // < 范围判定
            sub_445150(v282);  // sub_445150 · 装备同步资源清理
          sub_605650(0, 3, 100, 12, 0, 13, 0);  // sub_605650 · 6 字段记录追加
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        if ( nArg1 > 32274 )  // 物品 ID > 32274(二分阈值,北支)
        {
          if ( nArg1 == 33027 )  // nArg1 == 33027 判定
          {
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 394;  // SEH 展开状态号 = 394
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v196 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v196 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -117;  // SEH 展开状态号(低字节) = -117
              v415 = 0x10000000;  // 标记待释放成员位 = 0x10000000
              v18 = sub_5144A0(3, v196);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v415 & 0x10000000) != 0 )  // 展开位 v415&0x10000000 判定(需释放对应成员)
              sub_445150(v284);  // sub_445150 · 装备同步资源清理
            sub_6048E0(4, 60, 4, 100);  // sub_6048E0 · 概率组写入
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        }
        if ( nArg1 == 32274 )  // nArg1 == 32274 判定
        {
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 358;  // SEH 展开状态号 = 358
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v195 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v195 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 103;  // 把 103 低字节存入 v418(短串内联指针)
            v415 = 0x20000;  // 标记待释放成员位 = 0x20000
            v18 = sub_5144A0(18, v195);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v415 & 0x20000) != 0 )  // 展开位 v415&0x20000 判定(需释放对应成员)
            sub_445150(v286);  // sub_445150 · 装备同步资源清理
          sub_6055A0(0, 3, 100, 200, 0, 40002);  // sub_6055A0 · 6 字段记录追加
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        if ( nArg1 == 32249 )  // nArg1 == 32249 判定
          goto LABEL_1052;  // 跳转 LABEL_1052(收尾/共用分支)
        if ( nArg1 != 32257 )  // nArg1 != 32257 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        goto LABEL_1078;  // 跳转 LABEL_1078(收尾/共用分支)
      }
      if ( nArg1 <= 33630 )  // nArg1 <= 33630 判定
      {
        //   (33333, 33630] 段：33627 / 33630 — CNEquipmentNovaCraft（新星工艺，CNEventEquipment 重载系） ──
        //   33335 = CNEventEquipment 重载（+1440 额外数组 sub_4ED3F0）
        switch ( nArg1 )  // 按 nArg1 分派
        {
          case 33630:
            Block[0] = (void *)17;  // Block[0] = 常量 17
            sub_431230(Block);  // sub_431230 · uint32 vector push_back
            Block[0] = (void *)31;  // Block[0] = 常量 31
            sub_431230(Block);  // sub_431230 · uint32 vector push_back
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 383;  // SEH 展开状态号 = 383
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v207 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v207 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 0x80;  // 把 0x80 低字节存入 v418(短串内联指针)
              v415 = 0x2000000;  // 标记待释放成员位 = 0x2000000
              v18 = sub_517C10(94, v207, (int)pBuf);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v415 & 0x2000000) != 0 )  // 展开位 v415&0x2000000 判定(需释放对应成员)
              sub_445150(v266);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          case 33335:
            Block[0] = (void *)4;  // Block[0] = 常量 4
            sub_431230(Block);  // sub_431230 · uint32 vector push_back
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 432;  // SEH 展开状态号 = 432
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v206 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v206 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -79;  // SEH 展开状态号(低字节) = -79
              pMem2 = (void *)64;  // pMem2 = 取 64(转指针/类型)
              v18 = sub_514520(55, v206, (int)pBuf);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( ((uint8_t)pMem2 & 0x40) != 0 )  // 展开位 pMem2&0x40 判定
              sub_445150(v268);  // sub_445150 · 装备同步资源清理
            sub_605650(0, 5, 100, 12, 0, 3, 1);  // sub_605650 · 6 字段记录追加
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          case 33627:
            Block[0] = (void *)31;  // Block[0] = 常量 31
            sub_431230(Block);  // sub_431230 · uint32 vector push_back
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 379;  // SEH 展开状态号 = 379
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v204 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v204 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 124;  // 把 124 低字节存入 v418(短串内联指针)
              v415 = 0x1000000;  // 标记待释放成员位 = 0x1000000
              v18 = sub_514520(91, v204, (int)pBuf);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v415 & 0x1000000) != 0 )  // 展开位 v415&0x1000000 判定(需释放对应成员)
              sub_445150(v270);  // sub_445150 · 装备同步资源清理
            Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
            v418 = 382;  // SEH 展开状态号 = 382
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              v205 = sub_4B3DF0(1, 0, 1112014848, 30000, 1);  // v205 = sub_4B3DF0 · CNChangeStatus 构造
            else
              v205 = 0;
            v418 = 0;  // SEH 展开状态号 = 0
            sub_6055F0(4, 3, 100, 0, v205, 0);  // sub_6055F0 · 6 字段记录追加
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          default:
            break;  // 跳出本 switch(单 case 处理完)
        }
        if ( nArg1 != 33628 )  // nArg1 != 33628 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        LOBYTE(v418) = 16;  // 把 16 低字节存入 v418(短串内联指针)
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v203 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v203 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = 17;  // 把 17 低字节存入 v418(短串内联指针)
          v413 = 16;  // 标记待释放成员位 = 16(0x10)
          v18 = sub_5144A0(92, v203);  // v18 = sub_5144A0 · CNEventEquipment 构造器
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (v413 & 0x10) != 0 )  // 展开位 v413&0x10 判定(需释放对应成员)
          sub_445150(v272);  // sub_445150 · 装备同步资源清理
        v408 = 18;
        v409 = 0;
        v410 = 1092616192;  // 置 v410 = 1092616192（float 10.0f）
        Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
        LOBYTE(v418) = 19;  // 把 19 低字节存入 v418(短串内联指针)
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
          goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
        }
        goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
      }
      //   33635 / 33636 / 33641 三点
      if ( nArg1 != 33635 )  // nArg1 != 33635 判定
      {
        if ( nArg1 == 33636 )  // nArg1 == 33636 判定
        {
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 407;  // SEH 展开状态号 = 407
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v209 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v209 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -104;  // SEH 展开状态号(低字节) = -104
            v415 = 0x80000000;  // 标记待释放成员位 = 0x80000000
            v18 = sub_518FB0(100, v209);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( v415 < 0 )  // v415 < 0 判定(无效值)
            sub_445150(v262);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        if ( nArg1 != 33641 )  // nArg1 != 33641 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        Block[0] = (void *)26;  // Block[0] = 常量 26
        sub_431230(Block);  // sub_431230 · uint32 vector push_back
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        v418 = 478;  // SEH 展开状态号 = 478
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v208 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v208 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = -33;  // SEH 展开状态号(低字节) = -33
          pMem2 = (void *)0x100000;  // 标记待释放成员位 = 0x100000(第 2 组掩码)
          v30 = sub_514520(105, v208, (int)pBuf);
        }
        else
        {
          v30 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( ((unsigned int)pMem2 & 0x100000) != 0 )  // 展开位 pMem2&0x100000 判定
          sub_445150(v264);  // sub_445150 · 装备同步资源清理
        sub_605650(0, 3, 100, 12, 0, 4, 1);  // sub_605650 · 6 字段记录追加
        goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
      }
    }
    Block[0] = (void *)26;  // Block[0] = 常量 26
    sub_431230(Block);  // sub_431230 · uint32 vector push_back
    Block[0] = operator new(0x5D8u);  // 分配 1496 字节对象(operator new, Block[0] 承接)
    v418 = 402;  // SEH 展开状态号 = 402
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      pMem2 = &v226;
      sub_435020(pBuf);  // sub_435020 · uint32 向量整体赋值
      LOBYTE(v418) = -109;  // SEH 展开状态号(低字节) = -109
      v210 = (void *)sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v210 = sub_4E9B10 · 装备参数结构构造
      v415 = 0x40000000;  // 标记待释放成员位 = 0x40000000
      v418 = 405;  // SEH 展开状态号 = 405
      v18 = sub_5186C0(nArg12, v210, v226, (void *)v227, v228, v229);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( (v415 & 0x40000000) != 0 )  // 展开位 v415&0x40000000 判定(需释放对应成员)
      sub_445150(v260);  // sub_445150 · 装备同步资源清理
    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
  }
  // ── [段 16] 北支收口：nArg1 == 27662 与 (32236, 33643) 之间的 3.2/3.3 万零散段 ──
  if ( nArg1 == 27662 )  // nArg1 == 27662 判定
  {
LABEL_620:
    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
    LOBYTE(v418) = 56;  // 把 56 低字节存入 v418(短串内联指针)
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v127 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v127 = sub_4E9B10 · 装备参数结构构造
      LOBYTE(v418) = 57;  // 把 57 低字节存入 v418(短串内联指针)
      v413 = 0x10000;  // 标记待释放成员位 = 0x10000
      v18 = sub_5144A0(nArg12, v127);  // v18 = sub_5144A0 · CNEventEquipment 构造器
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( (v413 & 0x10000) != 0 )  // 展开位 v413&0x10000 判定(需释放对应成员)
      sub_445150(v396);  // sub_445150 · 装备同步资源清理
    v229 = 0;
    v228 = 12;
LABEL_619:
    sub_605650(1, 10, 100, 7, 0, v228, v229);  // sub_605650 · 6 字段记录追加
    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
  }
  // ── [段 17] ★ 中北支 (14064, 26027] 段（~400 行）—— 2.2-2.7 万段（中阶装备主区） ──
  //   14064/14069/14079 三点 → 14435/14457/14468 → 20016/20027/20060/20064/22017/22030/22031
  if ( nArg1 > 14064 )  // 物品 ID > 14064(二分阈值,北支)
  {
    if ( nArg1 <= 26027 )  // nArg1 <= 26027 判定
    {
      if ( nArg1 != 26027 )  // nArg1 != 26027 判定
      {
        if ( nArg1 <= 22053 )  // nArg1 <= 22053 判定
        {
          if ( nArg1 == 22053 )  // nArg1 == 22053 判定
          {
            Block[0] = operator new(0x544u);  // 分配 1348 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = 1;  // 把 1 低字节存入 v418(短串内联指针)
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v89 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v89 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 2;  // 把 2 低字节存入 v418(短串内联指针)
              v413 = 1;  // 标记待释放成员位 = 1(0x1)
              v18 = sub_51AD20(37, v89);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v413 & 1) != 0 )  // 展开位 v413&1 判定(需释放对应成员)
              sub_445150(v345);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          if ( nArg1 <= 20060 )  // nArg1 <= 20060 判定
          {
            if ( nArg1 != 20060 )  // nArg1 != 20060 判定
            {
              if ( nArg1 <= 14457 )  // nArg1 <= 14457 判定
              {
                if ( nArg1 != 14457 )  // nArg1 != 14457 判定
                {
                  if ( nArg1 <= 14079 )  // nArg1 <= 14079 判定
                  {
                    //   14079 / 14069 / 14074 三连（14064 段入口）
                    if ( nArg1 == 14079 )  // nArg1 == 14079 判定
                      goto LABEL_343;  // 跳转 LABEL_343(收尾/共用分支)
                    if ( nArg1 == 14069 )  // nArg1 == 14069 判定
                      goto LABEL_299;  // 跳转 LABEL_299(收尾/共用分支)
                    if ( nArg1 != 14074 )  // nArg1 != 14074 判定
                      goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                    goto LABEL_335;  // 跳转 LABEL_335(收尾/共用分支)
                  }
                  if ( nArg1 != 14435 )  // nArg1 != 14435 判定
                    goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                }
                Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
                LOBYTE(v418) = -127;  // SEH 展开状态号(低字节) = -127
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v82 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v82 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = -126;  // SEH 展开状态号(低字节) = -126
                  v412 = 256;
                  v18 = sub_5141B0(nArg12, v82, 0, 1);
                }
                else
                {
                  v18 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v412 & 0x100) != 0 )  // 展开位 v412&0x100 判定(需释放对应成员)
                  sub_445150(v349);  // sub_445150 · 装备同步资源清理
                sub_513B10(2, 1);
                sub_41C150(50);  // sub_41C150 · crypt4byte 初始化转发
                goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
              }
              //   14468 单点
              if ( nArg1 == 14468 )  // nArg1 == 14468 判定
              {
                Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
                v418 = 370;  // SEH 展开状态号 = 370
                if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                {
                  v84 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v84 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 115;  // 把 115 低字节存入 v418(短串内联指针)
                  v415 = 0x200000;  // 标记待释放成员位 = 0x200000
                  pObj = sub_5141B0(132, v84, 0, 1);
                }
                else
                {
                  pObj = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( (v415 & 0x200000) != 0 )  // 展开位 v415&0x200000 判定(需释放对应成员)
                  sub_445150(v289);  // sub_445150 · 装备同步资源清理
                sub_513B10(2, 1);
                v229 = 150;
                goto LABEL_17;  // 跳转 LABEL_17(收尾/共用分支)
              }
              if ( nArg1 != 20016 )  // nArg1 != 20016 判定
              {
                if ( nArg1 != 20027 )  // nArg1 != 20027 判定
                  goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                goto LABEL_359;  // 跳转 LABEL_359(收尾/共用分支)
              }
            }
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = -52;  // SEH 展开状态号(低字节) = -52
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v85 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v85 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -51;  // SEH 展开状态号(低字节) = -51
              v414 = 2;  // 标记待释放成员位 = 2(0x2)
              v18 = sub_515A50(nArg12, v85);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v414 & 2) != 0 )  // 展开位 v414&2 判定(需释放对应成员)
              sub_445150(v347);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          //   22031 / 22017 / 22030 三点（22031 段）
          if ( nArg1 <= 22031 )  // nArg1 <= 22031 判定
          {
            if ( nArg1 == 22031 )  // nArg1 == 22031 判定
            {
LABEL_409:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = -38;  // SEH 展开状态号(低字节) = -38
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v91 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v91 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -37;  // SEH 展开状态号(低字节) = -37
                v414 = 32;  // 标记待释放成员位 = 32(0x20)
                v18 = sub_516980(nArg12, v91);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v414 & 0x20) != 0 )  // 展开位 v414&0x20 判定(需释放对应成员)
                sub_445150(v237);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
            if ( nArg1 != 20064 )  // nArg1 != 20064 判定
            {
              if ( nArg1 != 22017 )  // nArg1 != 22017 判定
              {
                if ( nArg1 == 22030 )  // nArg1 == 22030 判定
                {
LABEL_377:
                  Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
                  LOBYTE(v418) = -41;  // SEH 展开状态号(低字节) = -41
                  if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                  {
                    v86 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v86 = sub_4E9B10 · 装备参数结构构造
                    LOBYTE(v418) = -40;  // SEH 展开状态号(低字节) = -40
                    v414 = 16;  // 标记待释放成员位 = 16(0x10)
                    v18 = sub_515CA0(nArg12, v86);
                  }
                  else
                  {
                    v18 = 0;
                  }
                  v418 = 0;  // SEH 展开状态号 = 0
                  if ( (v414 & 0x10) != 0 )  // 展开位 v414&0x10 判定(需释放对应成员)
                    sub_445150(v343);  // sub_445150 · 装备同步资源清理
                  goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
                }
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
              }
LABEL_399:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = -45;  // SEH 展开状态号(低字节) = -45
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v90 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v90 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -44;  // SEH 展开状态号(低字节) = -44
                v414 = 8;  // 标记待释放成员位 = 8(0x8)
                v18 = sub_5144A0(nArg12, v90);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v414 & 8) != 0 )  // 展开位 v414&8 判定(需释放对应成员)
                sub_445150(v287);  // sub_445150 · 装备同步资源清理
              v408 = 1;
              v409 = 0;
              v410 = 1092616192;  // 置 v410 = 1092616192（float 10.0f）
              Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = -42;  // SEH 展开状态号(低字节) = -42
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
                goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
              }
LABEL_605:
              v87 = 0;
              goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
            }
LABEL_359:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = -49;  // SEH 展开状态号(低字节) = -49
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v83 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v83 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -48;  // SEH 展开状态号(低字节) = -48
              v414 = 4;  // 标记待释放成员位 = 4(0x4)
              v18 = sub_5144A0(nArg12, v83);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v414 & 4) != 0 )  // 展开位 v414&4 判定(需释放对应成员)
              sub_445150(v259);  // sub_445150 · 装备同步资源清理
            v408 = 23;
            v409 = 0;
            v410 = 1092616192;  // 置 v410 = 1092616192（float 10.0f）
            Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = -46;  // SEH 展开状态号(低字节) = -46
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
LABEL_606:
              LOBYTE(v418) = 0;  // 把 0 低字节存入 v418(短串内联指针)
LABEL_607:
              sub_6055F0(2, 100, 100, 0, v87, 0);  // sub_6055F0 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
            goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
          }
          //   22038 / 22040 / 22047 三点
          if ( nArg1 != 22038 )  // nArg1 != 22038 判定
          {
            if ( nArg1 == 22040 )  // nArg1 == 22040 判定
            {
LABEL_414:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = -32;  // SEH 展开状态号(低字节) = -32
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v92 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v92 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -31;  // SEH 展开状态号(低字节) = -31
                v414 = 128;  // 标记待释放成员位 = 128(0x80)
                v18 = sub_516610(nArg12, v92);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v414 & 0x80u) != 0 )  // 展开位 v414&0x80 判定(需释放对应成员)
                sub_445150(v341);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
            if ( nArg1 != 22047 )  // nArg1 != 22047 判定
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_387:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = -29;  // SEH 展开状态号(低字节) = -29
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v88 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v88 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -28;  // SEH 展开状态号(低字节) = -28
              v414 = 256;  // 标记待释放成员位 = 256(0x100)
              v18 = sub_5144A0(nArg12, v88);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v414 & 0x100) != 0 )  // 展开位 v414&0x100 判定(需释放对应成员)
              sub_445150(v339);  // sub_445150 · 装备同步资源清理
            sub_6055A0(1, 10, 100, 100, 0, 40002);  // sub_6055A0 · 6 字段记录追加
            sub_605650(1, 10, 100, 5, 0, 4, 0);  // sub_605650 · 6 字段记录追加
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
LABEL_419:
          Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -35;  // SEH 展开状态号(低字节) = -35
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v93 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v93 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -34;  // SEH 展开状态号(低字节) = -34
            v414 = 64;  // 标记待释放成员位 = 64(0x40)
            pObj = sub_515E80(nArg12, v93, 0, 1);
          }
          else
          {
            pObj = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v414 & 0x40) != 0 )  // 展开位 v414&0x40 判定(需释放对应成员)
          {
            v26 = &v285;
LABEL_62:
            sub_445150(v26);  // sub_445150 · 装备同步资源清理
          }
LABEL_63:
          sub_513B10(2, 1);
          v229 = 300;
          goto LABEL_17;  // 跳转 LABEL_17(收尾/共用分支)
        }
        //   (24023, 24027] 段：24027 边界
        if ( nArg1 <= 24027 )  // nArg1 <= 24027 判定
        {
          if ( nArg1 != 24027 )  // nArg1 != 24027 判定
          {
            if ( nArg1 <= 22078 )  // nArg1 <= 22078 判定
            {
              if ( nArg1 != 22078 )  // nArg1 != 22078 判定
              {
                switch ( nArg1 )  // 按 nArg1 分派
                {
                  case 22061:
                    goto LABEL_399;  // 跳转 LABEL_399(收尾/共用分支)
                  case 22069:
                    goto LABEL_409;  // 跳转 LABEL_409(收尾/共用分支)
                  case 22072:
                    goto LABEL_377;  // 跳转 LABEL_377(收尾/共用分支)
                  case 22076:
                    goto LABEL_414;  // 跳转 LABEL_414(收尾/共用分支)
                  default:
                    goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
                }
              }
              goto LABEL_419;  // 跳转 LABEL_419(收尾/共用分支)
            }
            //   22079 单点
            if ( nArg1 == 22079 )  // nArg1 == 22079 判定
              goto LABEL_387;  // 跳转 LABEL_387(收尾/共用分支)
            if ( nArg1 != 24014 )  // nArg1 != 24014 判定
            {
              if ( nArg1 != 24023 )  // nArg1 != 24023 判定
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
              goto LABEL_437;  // 跳转 LABEL_437(收尾/共用分支)
            }
            goto LABEL_442;  // 跳转 LABEL_442(收尾/共用分支)
          }
LABEL_448:
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -23;  // SEH 展开状态号(低字节) = -23
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v96 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v96 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -22;  // SEH 展开状态号(低字节) = -22
            v414 = 1024;  // 标记待释放成员位 = 1024(0x400)
            v18 = sub_5144A0(nArg12, v96);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v414 & 0x400) != 0 )  // 展开位 v414&0x400 判定(需释放对应成员)
            sub_445150(v283);  // sub_445150 · 装备同步资源清理
          v229 = 20011;
          v228 = 0;
          v227 = 3;
          v226 = 100;
          v224 = 5;
          goto LABEL_268;  // 跳转 LABEL_268(收尾/共用分支)
        }
        //   (24070, 26024] 段：24081 边界 → 26024 / 26026 两点
        if ( nArg1 > 24070 )  // 物品 ID > 24070(二分阈值,北支)
        {
          if ( nArg1 != 24081 )  // nArg1 != 24081 判定
          {
            if ( nArg1 == 26024 )  // nArg1 == 26024 判定
            {
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 452;  // SEH 展开状态号 = 452
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v98 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v98 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -59;  // SEH 展开状态号(低字节) = -59
                pMem2 = (void *)4096;  // pMem2 = 取 4096(转指针/类型)
                v18 = sub_519310(168, v98);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (BYTE1(pMem2) & 0x10) != 0 )  // 字节位掩码(pMem2 特定字节)&0x10 判定
                sub_445150(v243);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
            if ( nArg1 == 26026 )  // nArg1 == 26026 判定
            {
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 455;  // SEH 展开状态号 = 455
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v97 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v97 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -56;  // SEH 展开状态号(低字节) = -56
                pMem2 = (void *)0x2000;  // 标记待释放成员位 = 0x2000(第 2 组掩码)
                v18 = sub_519440(170, v97);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (BYTE1(pMem2) & 0x20) != 0 )  // 字节位掩码(pMem2 特定字节)&0x20 判定
                sub_445150(v335);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
          }
        }
        else
        {
          //   24070 / 24046 / 24060 / 24064 四点
          if ( nArg1 == 24070 )  // nArg1 == 24070 判定
            goto LABEL_448;  // 跳转 LABEL_448(收尾/共用分支)
          if ( nArg1 != 24046 )  // nArg1 != 24046 判定
          {
            if ( nArg1 != 24060 )  // nArg1 != 24060 判定
            {
              if ( nArg1 != 24064 )  // nArg1 != 24064 判定
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_437:
              Block[0] = operator new(0x5D4u);  // 分配 1492 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = -26;  // SEH 展开状态号(低字节) = -26
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v94 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v94 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -25;  // SEH 展开状态号(低字节) = -25
                v414 = 512;  // 标记待释放成员位 = 512(0x200)
                v18 = sub_516F30(nArg12, v94);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v414 & 0x200) != 0 )  // 展开位 v414&0x200 判定(需释放对应成员)
                sub_445150(v257);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
LABEL_442:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 449;  // SEH 展开状态号 = 449
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v95 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v95 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -62;  // SEH 展开状态号(低字节) = -62
              pMem2 = (void *)2048;  // pMem2 = 取 2048(转指针/类型)
              v18 = sub_5144A0(nArg12, v95);  // v18 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (BYTE1(pMem2) & 8) != 0 )  // 字节位 pMem2 位 8 判定
              sub_445150(v337);  // sub_445150 · 装备同步资源清理
            sub_605650(0, 2, 100, 3, 0, 11, 1);  // sub_605650 · 6 字段记录追加
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
        }
        Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
        LOBYTE(v418) = -20;  // SEH 展开状态号(低字节) = -20
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v99 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v99 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = -19;  // SEH 展开状态号(低字节) = -19
          v414 = 2048;  // 标记待释放成员位 = 2048(0x800)
          v18 = sub_515F20(nArg12, v99);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (v414 & 0x800) != 0 )  // 展开位 v414&0x800 判定(需释放对应成员)
          sub_445150(v333);  // sub_445150 · 装备同步资源清理
        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
      }
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      v418 = 458;  // SEH 展开状态号 = 458
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v100 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v100 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -53;  // SEH 展开状态号(低字节) = -53
        pMem2 = (void *)0x4000;  // 标记待释放成员位 = 0x4000(第 2 组掩码)
        v18 = sub_5144A0(171, v100);  // v18 = sub_5144A0 · CNEventEquipment 构造器
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( (BYTE1(pMem2) & 0x40) == 0 )  // 字节位掩码(pMem2 特定字节)&0x40 判定
      {
LABEL_893:
        sub_6055A0(0, 2, 100, 150, 0, 40002);  // sub_6055A0 · 6 字段记录追加
        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
      }
      v101 = &v281;
LABEL_892:
      sub_445150(v101);  // sub_445150 · 装备同步资源清理
      goto LABEL_893;  // 跳转 LABEL_893(收尾/共用分支)
    }
    // ── [段 18] ★ (27320, 27531] 段（~200 行）—— 2.7 万段（高级装备：诅咒/毁灭/黑月系） ──
    //   27514 = CNEquipmentCurseOfKhazan（哈赞诅咒）等
    if ( nArg1 > 27320 )  // 物品 ID > 27320(二分阈值,北支)
    {
      if ( nArg1 <= 27531 )  // nArg1 <= 27531 判定
      {
        if ( nArg1 != 27531 )  // nArg1 != 27531 判定
        {
          switch ( nArg1 )  // 按 nArg1 分派
          {
            case 27327:  // case 27327 → 装备参数结构构造
            case 27514:  // case 27514 → 装备参数结构构造
              Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 68;  // 把 68 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v119 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v119 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 69;  // 把 69 低字节存入 v418(短串内联指针)
                v413 = 0x100000;  // 标记待释放成员位 = 0x100000
                v18 = sub_51B380(nArg12, v119);
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v413 & 0x100000) != 0 )  // 展开位 v413&0x100000 判定(需释放对应成员)
                sub_445150(v319);  // sub_445150 · 装备同步资源清理
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            case 27332:  // case 27332 → 装备参数结构构造
            case 27518:  // case 27518 → 装备参数结构构造
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = 31;  // 把 31 低字节存入 v418(短串内联指针)
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v117 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v117 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 32;  // 把 32 低字节存入 v418(短串内联指针)
                v413 = 256;  // 标记待释放成员位 = 256(0x100)
                v18 = sub_5144A0(nArg12, v117);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v413 & 0x100) != 0 )  // 展开位 v413&0x100 判定(需释放对应成员)
                sub_445150(v321);  // sub_445150 · 装备同步资源清理
              sub_6048E0(0, 100, 2, 100);  // sub_6048E0 · 概率组写入
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            case 27500:  // case 27500 → 装备参数结构构造
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = -88;  // SEH 展开状态号(低字节) = -88
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v120 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v120 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -87;  // SEH 展开状态号(低字节) = -87
                v412 = 0x200000;
                v18 = sub_5144A0(nArg12, v120);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v412 & 0x200000) != 0 )  // 展开位 v412&0x200000 判定(需释放对应成员)
                sub_445150(v241);  // sub_445150 · 装备同步资源清理
              sub_6048E0(0, 40, 5, 100);  // sub_6048E0 · 概率组写入
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            case 27509:
              goto LABEL_565;  // 跳转 LABEL_565(收尾/共用分支)
            case 27530:
              v405 = 0;
              v406 = 0;
              v407 = 1103626240;  // 置 v407 = 1103626240（float 25.0f）
              v408 = 3;
              v409 = 0;
              v410 = 1103626240;  // 置 v410 = 1103626240（float 25.0f）
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 332;  // SEH 展开状态号 = 332
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v121 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v121 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 77;  // 把 77 低字节存入 v418(短串内联指针)
                v415 = 512;  // 标记待释放成员位 = 512(0x200)
                v18 = sub_5144A0(nArg12, v121);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v415 & 0x200) != 0 )  // 展开位 v415&0x200 判定(需释放对应成员)
                sub_445150(v398);  // sub_445150 · 装备同步资源清理
              Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
              v418 = 335;  // SEH 展开状态号 = 335
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
                v122 = sub_5101B0(&v405, 2, 30000, 1);  // v122 = sub_5101B0 · CNChangeStatus 构造器
              else
                v122 = 0;
              v418 = 0;  // SEH 展开状态号 = 0
              sub_6055F0(0, 2, 100, 0, v122, 0);  // sub_6055F0 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            default:
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
          }
        }
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        v418 = 336;  // SEH 展开状态号 = 336
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v123 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v123 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = 81;  // 把 81 低字节存入 v418(短串内联指针)
          v415 = 1024;  // 标记待释放成员位 = 1024(0x400)
          v18 = sub_517570(139, v123);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (v415 & 0x400) != 0 )  // 展开位 v415&0x400 判定(需释放对应成员)
          sub_445150(v273);  // sub_445150 · 装备同步资源清理
        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
      }
      //   27327 / 27332 / 27500 / 27509 / 27518 / 27530 六点 ──
      //   27332 = CNEquipmentDestroyHeart（毁灭之心）周边
      switch ( nArg1 )  // 按 nArg1 分派
      {
        case 27622:  // case 27622 → 装备参数结构构造
        case 27651:  // case 27651 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 28;  // 把 28 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v125 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v125 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 29;  // 把 29 低字节存入 v418(短串内联指针)
            v413 = 128;  // 标记待释放成员位 = 128(0x80)
            v18 = sub_51ADF0(nArg12, v125);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v413 & 0x80u) != 0 )  // 展开位 v413&0x80 判定(需释放对应成员)
            sub_445150(v251);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        case 27623:  // case 27623 → 装备参数结构构造
        case 27657:  // case 27657 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 4;  // 把 4 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v124 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v124 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 5;  // 把 5 低字节存入 v418(短串内联指针)
            v413 = 2;  // 标记待释放成员位 = 2(0x2)
            v18 = sub_5144A0(nArg12, v124);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v413 & 2) != 0 )  // 展开位 v413&2 判定(需释放对应成员)
            sub_445150(v315);  // sub_445150 · 装备同步资源清理
          v408 = 18;
          v409 = 0;
          v410 = 1101004800;  // 置 v410 = 1101004800（float 20.0f）
          Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 7;  // 把 7 低字节存入 v418(短串内联指针)
          if ( Block[0] == nullptr )  // Block[0] 分配失败(走释放路径)
            goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
          v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
          break;  // 跳出本 switch(单 case 处理完)
        case 27628:  // case 27628 → 装备参数结构构造
        case 27661:  // case 27661 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 53;  // 把 53 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v126 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v126 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 54;  // 把 54 低字节存入 v418(短串内联指针)
            v413 = 0x8000;  // 标记待释放成员位 = 0x8000
            v18 = sub_5144A0(nArg12, v126);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v413 & 0x8000) != 0 )  // 展开位 v413&0x8000 判定(需释放对应成员)
            sub_445150(v397);  // sub_445150 · 装备同步资源清理
          v229 = 0;
          v228 = 13;
          goto LABEL_619;  // 跳转 LABEL_619(收尾/共用分支)
        case 27632:
          goto LABEL_620;  // 跳转 LABEL_620(收尾/共用分支)
        default:
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
      }
      goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
    }
    // ── [段 19] (27055, 27320] 段（~200 行）──
    //   27063/27067/27068/27069/27074/27080/27081 七点；27074 = CNEquipmentFrostbringer（冰霜使者）
    if ( nArg1 != 27320 )  // nArg1 != 27320 判定
    {
      if ( nArg1 <= 27055 )  // nArg1 <= 27055 判定
      {
        if ( nArg1 == 27055 )  // nArg1 == 27055 判定
          goto LABEL_509;  // 跳转 LABEL_509(收尾/共用分支)
        if ( nArg1 <= 27032 )  // nArg1 <= 27032 判定
        {
          if ( nArg1 == 27032 )  // nArg1 == 27032 判定
          {
LABEL_541:
            Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = 71;  // 把 71 低字节存入 v418(短串内联指针)
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v113 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v113 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 72;  // 把 72 低字节存入 v418(短串内联指针)
              v413 = 0x200000;  // 标记待释放成员位 = 0x200000
              v18 = sub_51B2A0(nArg12, v113);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v413 & 0x200000) != 0 )  // 展开位 v413&0x200000 判定(需释放对应成员)
              sub_445150(v277);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
          if ( nArg1 <= 26031 )  // nArg1 <= 26031 判定
          {
            if ( nArg1 == 26031 )  // nArg1 == 26031 判定
            {
              pMem2 = operator new(0x5B0u);  // 分配堆内存
              v418 = 520;  // SEH 展开状态号 = 520
              if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
              {
                v106 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v106 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 9;  // 把 9 低字节存入 v418(短串内联指针)
                Block[0] = (void *)2;  // Block[0] = 常量 2
                v107 = sub_51A520(175, v106);
              }
              else
              {
                v107 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( ((int)Block[0] & 2) != 0 )  // 字节位掩码 Block[0]&2 判定(需释放)
                sub_445150(v329);  // sub_445150 · 装备同步资源清理
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
              return v107;  // 返回结果对象 v107(0=不支持该 ID)
            }
            if ( nArg1 != 26029 )  // nArg1 != 26029 判定
            {
              if ( nArg1 == 26030 )  // nArg1 == 26030 判定
              {
                pMem2 = operator new(0x5B0u);  // 分配堆内存
                v418 = 517;  // SEH 展开状态号 = 517
                if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
                {
                  v102 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v102 = sub_4E9B10 · 装备参数结构构造
                  LOBYTE(v418) = 6;  // 把 6 低字节存入 v418(短串内联指针)
                  Block[0] = (void *)1;  // Block[0] = 常量 1
                  v103 = sub_51A670(174, v102);
                }
                else
                {
                  v103 = 0;
                }
                v418 = 0;  // SEH 展开状态号 = 0
                if ( ((int)Block[0] & 1) != 0 )  // 字节位掩码 Block[0]&1 判定(需释放)
                  sub_445150(v331);  // sub_445150 · 装备同步资源清理
                sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
                return v103;  // 返回结果对象 v103(0=不支持该 ID)
              }
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
            }
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            v418 = 509;  // SEH 展开状态号 = 509
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v104 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v104 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -2;  // SEH 展开状态号(低字节) = -2
              pMem2 = (void *)0x40000000;  // 标记待释放成员位 = 0x40000000(第 2 组掩码)
              v30 = sub_5144A0(173, v104);  // v30 = sub_5144A0 · CNEventEquipment 构造器
            }
            else
            {
              v30 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( ((unsigned int)pMem2 & 0x40000000) != 0 )  // 展开位 pMem2&0x40000000 判定
              sub_445150(v255);  // sub_445150 · 装备同步资源清理
            v408 = 6;
            v409 = 0;
            v410 = 1120403456;  // 置 v410 = 1120403456（float 100.0f）
            Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
            v418 = 512;  // SEH 展开状态号 = 512
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v105 = sub_5101B0(&v408, 1, 30000, 1);  // v105 = sub_5101B0 · CNChangeStatus 构造器
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
            v418 = 0;  // SEH 展开状态号 = 0
            v225 = 5;
            goto LABEL_218;  // 跳转 LABEL_218(收尾/共用分支)
          }
          if ( nArg1 != 27020 )  // nArg1 != 27020 判定
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_509:
          Block[0] = operator new(0x548u);  // 分配 1352 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 74;  // 把 74 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v108 = (void *)sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v108 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 75;  // 把 75 低字节存入 v418(短串内联指针)
            v413 = 0x400000;  // 标记待释放成员位 = 0x400000
            v18 = sub_51B050(nArg12, v108);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v413 & 0x400000) != 0 )  // 展开位 v413&0x400000 判定(需释放对应成员)
            sub_445150(v279);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        //   27032 / 27033 两点
        if ( nArg1 == 27033 )  // nArg1 == 27033 判定
        {
LABEL_532:
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 49;  // 把 49 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v111 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v111 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 50;  // 把 50 低字节存入 v418(短串内联指针)
            v413 = 0x4000;  // 标记待释放成员位 = 0x4000
            v18 = sub_5144A0(nArg12, v111);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v413 & 0x4000) != 0 )  // 展开位 v413&0x4000 判定(需释放对应成员)
            sub_445150(v325);  // sub_445150 · 装备同步资源清理
          Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 52;  // 把 52 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            v112 = sub_4B3DF0(0, 0, 1106247680, 60000, 1);  // v112 = sub_4B3DF0 · CNChangeStatus 构造
          else
            v112 = 0;
          LOBYTE(v418) = 0;  // 把 0 低字节存入 v418(短串内联指针)
          sub_6055F0(0, 2, 100, 0, v112, 0);  // sub_6055F0 · 6 字段记录追加
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        //   27037 / 27038 两点
        if ( nArg1 == 27037 )  // nArg1 == 27037 判定
        {
LABEL_520:
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 8;  // 把 8 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v110 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v110 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 9;  // 把 9 低字节存入 v418(短串内联指针)
            v413 = 4;  // 标记待释放成员位 = 4(0x4)
            v18 = sub_5144A0(nArg12, v110);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v413 & 4) != 0 )  // 展开位 v413&4 判定(需释放对应成员)
            sub_445150(v327);  // sub_445150 · 装备同步资源清理
          v408 = 5;
          v409 = 0;
          v410 = 1112014848;  // 置 v410 = 1112014848（float 50.0f）
          Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 11;  // 把 11 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v87 = sub_5101B0(&v408, 1, 0, 1);  // v87 = sub_5101B0 · CNChangeStatus 构造器
            goto LABEL_606;  // 跳转 LABEL_606(收尾/共用分支)
          }
          goto LABEL_605;  // 跳转 LABEL_605(收尾/共用分支)
        }
        //   26029 / 26030 / 26031 三点（2.6 万段入口）
        if ( nArg1 != 27038 )  // nArg1 != 27038 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_514:
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        LOBYTE(v418) = 34;  // 把 34 低字节存入 v418(短串内联指针)
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v109 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v109 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = 35;  // 把 35 低字节存入 v418(短串内联指针)
          v413 = 512;  // 标记待释放成员位 = 512(0x200)
          v18 = sub_5144A0(nArg12, v109);  // v18 = sub_5144A0 · CNEventEquipment 构造器
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (v413 & 0x200) != 0 )  // 展开位 v413&0x200 判定(需释放对应成员)
          sub_445150(v233);  // sub_445150 · 装备同步资源清理
        v229 = 0;
        v228 = 12;
LABEL_531:
        sub_605650(0, 3, 100, 7, 0, v228, v229);  // sub_605650 · 6 字段记录追加
        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
      }
      switch ( nArg1 )  // 按 nArg1 分派
      {
        case 27063:
          goto LABEL_541;  // 跳转 LABEL_541(收尾/共用分支)
        case 27067:
          goto LABEL_520;  // 跳转 LABEL_520(收尾/共用分支)
        case 27068:
        case 27081:
          goto LABEL_532;  // 跳转 LABEL_532(收尾/共用分支)
        case 27069:  // case 27069 → 装备参数结构构造
          goto LABEL_514;  // 跳转 LABEL_514(收尾/共用分支)
        case 27074:  // case 27074 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 329;  // SEH 展开状态号 = 329
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v114 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v114 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 74;  // 把 74 低字节存入 v418(短串内联指针)
            v415 = 256;  // 标记待释放成员位 = 256(0x100)
            v18 = sub_517940(nArg12, v114);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v415 & 0x100) != 0 )  // 展开位 v415&0x100 判定(需释放对应成员)
            sub_445150(v323);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        case 27080:  // case 27080 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 461;  // SEH 展开状态号 = 461
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v115 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v115 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -50;  // SEH 展开状态号(低字节) = -50
            pMem2 = (void *)0x8000;  // 标记待释放成员位 = 0x8000(第 2 组掩码)
            v18 = sub_5144A0(nArg12, v115);  // v18 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( SBYTE1(pMem2) >= 0 )  // 符号字节 SBYTE1(pMem2) 正负判定
            goto LABEL_1274;  // 跳转 LABEL_1274(收尾/共用分支)
          v116 = &v253;
          break;  // 跳出本 switch(单 case 处理完)
        default:
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
      }
LABEL_1273:
      sub_445150(v116);  // sub_445150 · 装备同步资源清理
LABEL_1274:
      sub_6055A0(0, 3, 100, 100, 0, 40002);  // sub_6055A0 · 6 字段记录追加
      goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
    }
LABEL_565:
    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
    LOBYTE(v418) = 37;  // 把 37 低字节存入 v418(短串内联指针)
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v118 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v118 = sub_4E9B10 · 装备参数结构构造
      LOBYTE(v418) = 38;  // 把 38 低字节存入 v418(短串内联指针)
      v413 = 1024;  // 标记待释放成员位 = 1024(0x400)
      v18 = sub_5144A0(nArg12, v118);  // v18 = sub_5144A0 · CNEventEquipment 构造器
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( (v413 & 0x400) != 0 )  // 展开位 v413&0x400 判定(需释放对应成员)
      sub_445150(v275);  // sub_445150 · 装备同步资源清理
    v229 = 0;
    v228 = 13;
LABEL_571:
    sub_605650(0, 2, 100, 5, 0, v228, v229);  // sub_605650 · 6 字段记录追加
    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
  }
  // ── [段 20] 中段收口：nArg1 == 14064 直判 ──
  if ( nArg1 == 14064 )  // nArg1 == 14064 判定
  {
LABEL_318:
    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
    LOBYTE(v418) = -61;  // SEH 展开状态号(低字节) = -61
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v78 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v78 = sub_4E9B10 · 装备参数结构构造
      LOBYTE(v418) = -60;  // SEH 展开状态号(低字节) = -60
      v412 = 0x40000000;
      v18 = sub_5144A0(nArg12, v78);  // v18 = sub_5144A0 · CNEventEquipment 构造器
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( (v412 & 0x40000000) != 0 )  // 展开位 v412&0x40000000 判定(需释放对应成员)
    {
      v79 = &v353;
LABEL_1255:
      sub_445150(v79);  // sub_445150 · 装备同步资源清理
    }
LABEL_1256:
    sub_605650(1, 10, 100, 7, 0, 13, 0);  // sub_605650 · 6 字段记录追加
    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
  }
  // ── [段 21] ★ (10830, 11256] 段（~180 行）—— 1.1 万段（低阶装备/套装件） ──
  //   11256 / 11230 / 11237 / 11250 / 11253 等
  if ( nArg1 > 10830 )  // 物品 ID > 10830(二分阈值,北支)
  {
    if ( nArg1 <= 11256 )  // nArg1 <= 11256 判定
    {
      if ( nArg1 == 11256 )  // nArg1 == 11256 判定
        goto LABEL_246;  // 跳转 LABEL_246(收尾/共用分支)
      if ( nArg1 <= 10875 )  // nArg1 <= 10875 判定
      {
        if ( nArg1 != 10875 )  // nArg1 != 10875 判定
        {
          switch ( nArg1 )  // 按 nArg1 分派
          {
            case 10843:  // case 10843 → 装备参数结构构造
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = -124;  // SEH 展开状态号(低字节) = -124
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v44 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v44 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -123;  // SEH 展开状态号(低字节) = -123
                v412 = 512;
                v45 = sub_5144A0(nArg12, v44);  // v45 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v45 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v412 & 0x200) != 0 )  // 展开位 v412&0x200 判定(需释放对应成员)
                sub_445150(v373);  // sub_445150 · 装备同步资源清理
              sub_605650(1, 5, 100, 7, 0, 13, 0);  // sub_605650 · 6 字段记录追加
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
              result = v45;
              break;  // 跳出本 switch(单 case 处理完)
            case 10850:
              goto LABEL_167;  // 跳转 LABEL_167(收尾/共用分支)
            case 10856:  // case 10856 → 装备参数结构构造
              goto LABEL_173;  // 跳转 LABEL_173(收尾/共用分支)
            case 10868:  // case 10868 → 装备参数结构构造
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              //   10843 单点（0x5B0）
              v418 = 373;  // SEH 展开状态号 = 373
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v49 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v49 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 118;  // 把 118 低字节存入 v418(短串内联指针)
                v415 = 0x400000;  // 标记待释放成员位 = 0x400000
                v50 = sub_5144A0(nArg12, v49);  // v50 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v50 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v415 & 0x400000) != 0 )  // 展开位 v415&0x400000 判定(需释放对应成员)
                sub_445150(v265);  // sub_445150 · 装备同步资源清理
              sub_605650(0, 2, 100, 8, 0, 13, 0);  // sub_605650 · 6 字段记录追加
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
              result = v50;
              break;  // 跳出本 switch(单 case 处理完)
            case 10870:  // case 10870 → 装备参数结构构造
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              v418 = 376;  // SEH 展开状态号 = 376
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v51 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v51 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 121;  // 把 121 低字节存入 v418(短串内联指针)
                v415 = (int)&unk_800000;
                v52 = sub_5144A0(nArg12, v51);  // v52 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v52 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( ((unsigned int)&unk_800000 & v415) != 0 )  // 展开位掩码判定(v415)
                sub_445150(v369);  // sub_445150 · 装备同步资源清理
              sub_605650(0, 4, 100, 8, 0, 15, 2);  // sub_605650 · 6 字段记录追加
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
              result = v52;
              break;  // 跳出本 switch(单 case 处理完)
            case 10871:  // case 10871 → 装备参数结构构造
              pMem2 = operator new(0x90Cu);  // 分配堆内存
              v418 = 523;  // SEH 展开状态号 = 523
              if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
              {
                v53 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v53 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 12;  // 把 12 低字节存入 v418(短串内联指针)
                Block[0] = (void *)4;  // Block[0] = 常量 4
                v54 = sub_51A920(nArg12, v53, 7, 0);
              }
              else
              {
                v54 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( ((int)Block[0] & 4) != 0 )  // 字节位掩码 Block[0]&4 判定(需释放)
                sub_445150(v299);  // sub_445150 · 装备同步资源清理
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
              result = v54;
              break;  // 跳出本 switch(单 case 处理完)
            case 10872:  // case 10872 → 装备参数结构构造
              pMem2 = operator new(0x90Cu);  // 分配堆内存
              v418 = 526;  // SEH 展开状态号 = 526
              if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
              {
                v55 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v55 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 15;  // 把 15 低字节存入 v418(短串内联指针)
                Block[0] = (void *)8;  // Block[0] = 常量 8
                v56 = sub_51AA20(nArg12, v55, 12, 0);
              }
              else
              {
                v56 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( ((int)Block[0] & 8) != 0 )  // 字节位掩码 Block[0]&8 判定(需释放)
                sub_445150(v367);  // sub_445150 · 装备同步资源清理
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
              result = v56;
              break;  // 跳出本 switch(单 case 处理完)
            case 10874:  // case 10874 → 装备参数结构构造
              pMem2 = operator new(0x5B0u);  // 分配堆内存
              v418 = 529;  // SEH 展开状态号 = 529
              if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
              {
                v57 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v57 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = 18;  // 把 18 低字节存入 v418(短串内联指针)
                Block[0] = (void *)16;  // Block[0] = 常量 16
                v58 = sub_5144A0(nArg12, v57);  // v58 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v58 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( ((int)Block[0] & 0x10) != 0 )  // 字节位掩码 Block[0]&0x10 判定(需释放)
                sub_445150(v247);  // sub_445150 · 装备同步资源清理
              sub_605650(1, 3, 100, 15, 0, 2, 1);  // sub_605650 · 6 字段记录追加
              sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
              result = v58;
              break;  // 跳出本 switch(单 case 处理完)
            default:
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
          }
          return result;
        }
        pMem2 = operator new(0x5B0u);  // 分配堆内存
        v418 = 532;  // SEH 展开状态号 = 532
        if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
        {
          v59 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v59 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = 21;  // 把 21 低字节存入 v418(短串内联指针)
          Block[0] = (void *)32;  // Block[0] = 常量 32
          v30 = sub_5144A0(123, v59);  // v30 = sub_5144A0 · CNEventEquipment 构造器
        }
        else
        {
          v30 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( ((int)Block[0] & 0x20) != 0 )  // 字节位掩码 Block[0]&0x20 判定(需释放)
          sub_445150(v365);  // sub_445150 · 装备同步资源清理
        Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
        v418 = 535;  // SEH 展开状态号 = 535
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          v60 = sub_4B3DF0(0, 0, 1109393408, 30000, 1);  // v60 = sub_4B3DF0 · CNChangeStatus 构造
        else
          v60 = 0;
        v229 = 0;
        v228 = v60;
        v418 = 0;  // SEH 展开状态号 = 0
        v227 = 0;
LABEL_217:
        v226 = 100;
        v225 = 2;
LABEL_218:
        sub_6055F0(1, v225, v226, v227, v228, v229);  // sub_6055F0 · 6 字段记录追加
        goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
      }
      //   (11230, 11237] 段：11230 边界 → 11216 / 11220
      if ( nArg1 <= 11230 )  // nArg1 <= 11230 判定
      {
        if ( nArg1 != 11230 )  // nArg1 != 11230 判定
        {
          if ( nArg1 == 10876 )  // nArg1 == 10876 判定
          {
            pMem2 = operator new(0x5B4u);  // 分配堆内存
            v418 = 536;  // SEH 展开状态号 = 536
            if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
            {
              v61 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v61 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 25;  // 把 25 低字节存入 v418(短串内联指针)
              Block[0] = (void *)64;  // Block[0] = 常量 64
              v62 = sub_51A330(124, v61);
            }
            else
            {
              v62 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( ((int)Block[0] & 0x40) != 0 )  // 字节位掩码 Block[0]&0x40 判定(需释放)
              sub_445150(v297);  // sub_445150 · 装备同步资源清理
            sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
            return v62;  // 返回结果对象 v62(0=不支持该 ID)
          }
          if ( nArg1 != 11216 )  // nArg1 != 11216 判定
          {
            if ( nArg1 != 11220 )  // nArg1 != 11220 判定
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
            goto LABEL_235;  // 跳转 LABEL_235(收尾/共用分支)
          }
LABEL_240:
          Block[0] = operator new(0x90Cu);  // 分配 2316 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -115;  // SEH 展开状态号(低字节) = -115
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v64 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v64 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -114;  // SEH 展开状态号(低字节) = -114
            v412 = 4096;
            pObj = sub_514B80(nArg12, v64, 16, 0);
          }
          else
          {
            pObj = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x1000) != 0 )  // 展开位 v412&0x1000 判定(需释放对应成员)
            sub_445150(v263);  // sub_445150 · 装备同步资源清理
          v65 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);  // 虚槽+176
LABEL_293:
          Block[0] = (void *)sub_41A5E0(v65 + 112);  // sub_41A5E0 · crypt4byte 解密校验
          v12 = (double)(int)Block[0] * 0.25;
LABEL_16:
          v229 = (uint64_t)v12;  // v229 = 取 v12(转指针/类型)
LABEL_17:
          sub_41C150(v229);  // sub_41C150 · crypt4byte 初始化转发
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return pObj;  // 返回对象 pObj
        }
LABEL_246:
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        LOBYTE(v418) = -109;  // SEH 展开状态号(低字节) = -109
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v66 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v66 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = -108;  // SEH 展开状态号(低字节) = -108
          v412 = 0x4000;
          v67 = sub_5144A0(nArg12, v66);  // v67 = sub_5144A0 · CNEventEquipment 构造器
        }
        else
        {
          v67 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (v412 & 0x4000) != 0 )  // 展开位 v412&0x4000 判定(需释放对应成员)
          sub_445150(v361);  // sub_445150 · 装备同步资源清理
        sub_605650(1, 3, 100, 7, 0, 6, 2);  // sub_605650 · 6 字段记录追加
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
        return v67;  // 返回结果对象 v67(0=不支持该 ID)
      }
      //   11237 / 11250 / 11253 三点
      if ( nArg1 != 11237 )  // nArg1 != 11237 判定
      {
        if ( nArg1 != 11250 )  // nArg1 != 11250 判定
        {
          if ( nArg1 != 11253 )  // nArg1 != 11253 判定
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_235:
          Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -112;  // SEH 展开状态号(低字节) = -112
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v63 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v63 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -111;  // SEH 展开状态号(低字节) = -111
            v412 = 0x2000;
            v18 = sub_5156B0(nArg12, v63);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x2000) != 0 )  // 展开位 v412&0x2000 判定(需释放对应成员)
          {
            sub_445150(v363);  // sub_445150 · 装备同步资源清理
            sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
            return v18;  // 返回结果对象 v18(0=不支持该 ID)
          }
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        goto LABEL_240;  // 跳转 LABEL_240(收尾/共用分支)
      }
LABEL_270:
      Block[0] = operator new(0x548u);  // 分配 1352 字节对象(operator new, Block[0] 承接)
      LOBYTE(v418) = -106;  // SEH 展开状态号(低字节) = -106
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v70 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v70 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -105;  // SEH 展开状态号(低字节) = -105
        v412 = 0x8000;
        v18 = sub_514940(nArg12, v70);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( (v412 & 0x8000) != 0 )  // 展开位 v412&0x8000 判定(需释放对应成员)
        sub_445150(v359);  // sub_445150 · 装备同步资源清理
      goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
    }
    // ── [段 22] (11256, 11637] 段：11259 / 11274 / 11605 / 11612 / 11619 / 11631 / 11634 ──
    if ( nArg1 <= 11637 )  // nArg1 <= 11637 判定
    {
      if ( nArg1 != 11637 )  // nArg1 != 11637 判定
      {
        if ( nArg1 <= 11612 )  // nArg1 <= 11612 判定
        {
          if ( nArg1 != 11612 )  // nArg1 != 11612 判定
          {
            if ( nArg1 == 11259 )  // nArg1 == 11259 判定
              goto LABEL_270;  // 跳转 LABEL_270(收尾/共用分支)
            if ( nArg1 != 11274 )  // nArg1 != 11274 判定
            {
              if ( nArg1 != 11605 )  // nArg1 != 11605 判定
                goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_259:
              Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
              LOBYTE(v418) = -97;  // SEH 展开状态号(低字节) = -97
              if ( Block[0] != nullptr )  // Block[0] 分配成功判定
              {
                v68 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v68 = sub_4E9B10 · 装备参数结构构造
                LOBYTE(v418) = -96;  // SEH 展开状态号(低字节) = -96
                v412 = 0x40000;
                v18 = sub_5144A0(nArg12, v68);  // v18 = sub_5144A0 · CNEventEquipment 构造器
              }
              else
              {
                v18 = 0;
              }
              v418 = 0;  // SEH 展开状态号 = 0
              if ( (v412 & 0x40000) != 0 )  // 展开位 v412&0x40000 判定(需释放对应成员)
                sub_445150(v357);  // sub_445150 · 装备同步资源清理
              sub_605650(1, 3, 100, 7, 0, 1, 2);  // sub_605650 · 6 字段记录追加
              goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
            }
            pMem2 = operator new(0x5B4u);  // 分配堆内存
            v418 = 539;  // SEH 展开状态号 = 539
            if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
            {
              v69 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v69 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = 28;  // 把 28 低字节存入 v418(短串内联指针)
              Block[0] = (void *)128;  // Block[0] = 常量 128
              v18 = sub_51AB20(10, v69);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( SLOBYTE(Block[0]) < 0 )  // 符号字节 SLOBYTE(Block[0]) 正负判定
              sub_445150(v295);  // sub_445150 · 装备同步资源清理
            v229 = 20011;
            v228 = 0;
            v227 = 5;
LABEL_267:
            v226 = 100;
            v224 = 2;
LABEL_268:
            sub_6055A0(1, v224, v226, v227, v228, v229);  // sub_6055A0 · 6 字段记录追加
LABEL_269:
            sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
            return v18;  // 返回结果对象 v18(0=不支持该 ID)
          }
LABEL_278:
          Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -94;  // SEH 展开状态号(低字节) = -94
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v71 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v71 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -93;  // SEH 展开状态号(低字节) = -93
            v412 = 0x80000;
            v18 = sub_515870(nArg12, v71);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x80000) != 0 )  // 展开位 v412&0x80000 判定(需释放对应成员)
            sub_445150(v231);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        //   11619 / 11631 / 11634 三点
        if ( nArg1 != 11619 )  // nArg1 != 11619 判定
        {
          if ( nArg1 == 11631 )  // nArg1 == 11631 判定
            goto LABEL_259;  // 跳转 LABEL_259(收尾/共用分支)
          if ( nArg1 != 11634 )  // nArg1 != 11634 判定
            goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
          goto LABEL_278;  // 跳转 LABEL_278(收尾/共用分支)
        }
      }
      Block[0] = operator new(0x90Cu);  // 分配 2316 字节对象(operator new, Block[0] 承接)
      LOBYTE(v418) = -91;  // SEH 展开状态号(低字节) = -91
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v72 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v72 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -90;  // SEH 展开状态号(低字节) = -90
        v412 = 0x100000;
        pObj = sub_514C60(nArg12, v72, 24, 0);
      }
      else
      {
        pObj = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( (v412 & 0x100000) != 0 )  // 展开位 v412&0x100000 判定(需释放对应成员)
        sub_445150(v293);  // sub_445150 · 装备同步资源清理
      v65 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);  // 虚槽+176
      goto LABEL_293;  // 跳转 LABEL_293(收尾/共用分支)
    }
    // ── [段 23] (11637, 14032] 段：11648 / 14022 / 14030 / 14032 四点 ──
    if ( nArg1 <= 14032 )  // nArg1 <= 14032 判定
    {
      if ( nArg1 != 14032 )  // nArg1 != 14032 判定
      {
        if ( nArg1 != 11648 )  // nArg1 != 11648 判定
        {
          if ( nArg1 != 14022 )  // nArg1 != 14022 判定
          {
            if ( nArg1 != 14030 )  // nArg1 != 14030 判定
              goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
LABEL_299:
            Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
            LOBYTE(v418) = -64;  // SEH 展开状态号(低字节) = -64
            if ( Block[0] != nullptr )  // Block[0] 分配成功判定
            {
              v73 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v73 = sub_4E9B10 · 装备参数结构构造
              LOBYTE(v418) = -63;  // SEH 展开状态号(低字节) = -63
              v412 = 0x20000000;
              v18 = sub_5167E0(nArg12, v73);
            }
            else
            {
              v18 = 0;
            }
            v418 = 0;  // SEH 展开状态号 = 0
            if ( (v412 & 0x20000000) != 0 )  // 展开位 v412&0x20000000 判定(需释放对应成员)
              sub_445150(v351);  // sub_445150 · 装备同步资源清理
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          }
LABEL_313:
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -67;  // SEH 展开状态号(低字节) = -67
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v77 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v77 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -66;  // SEH 展开状态号(低字节) = -66
            v412 = 0x10000000;
            v18 = sub_516300(nArg12, v77);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x10000000) != 0 )  // 展开位 v412&0x10000000 判定(需释放对应成员)
            sub_445150(v261);  // sub_445150 · 装备同步资源清理
          goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
        }
        pMem2 = operator new(0x5B0u);  // 分配堆内存
        v418 = 542;  // SEH 展开状态号 = 542
        if ( pMem2 != nullptr )  // pMem2 != nullptr 判定
        {
          v74 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v74 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = 31;  // 把 31 低字节存入 v418(短串内联指针)
          Block[0] = (void *)256;  // Block[0] = 常量 256
          v75 = sub_5144A0(128, v74);  // v75 = sub_5144A0 · CNEventEquipment 构造器
        }
        else
        {
          v75 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (BYTE1(Block[0]) & 1) != 0 )  // 字节位掩码(Block[0] 特定字节)&1 判定
          sub_445150(v355);  // sub_445150 · 装备同步资源清理
        v405 = 0;
        v406 = 0;
        v407 = 1101004800;  // 置 v407 = 1101004800（float 20.0f）
        v408 = 3;
        v409 = 0;
        v410 = 1101004800;  // 置 v410 = 1101004800（float 20.0f）
        Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
        v418 = 545;  // SEH 展开状态号 = 545
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v76 = sub_5101B0(&v405, 2, 0, 1);  // v76 = sub_5101B0 · CNChangeStatus 构造器
LABEL_309:
          v418 = 0;  // SEH 展开状态号 = 0
          sub_6055F0(2, 100, 100, 0, v76, 0);  // sub_6055F0 · 6 字段记录追加
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v75;  // 返回结果对象 v75(0=不支持该 ID)
        }
LABEL_308:
        v76 = 0;
        goto LABEL_309;  // 跳转 LABEL_309(收尾/共用分支)
      }
      goto LABEL_318;  // 跳转 LABEL_318(收尾/共用分支)
    }
    //   14039 / 14046 / 14059 三点
    if ( nArg1 != 14039 )  // nArg1 != 14039 判定
    {
      if ( nArg1 != 14046 )  // nArg1 != 14046 判定
      {
        if ( nArg1 != 14059 )  // nArg1 != 14059 判定
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
        goto LABEL_313;  // 跳转 LABEL_313(收尾/共用分支)
      }
LABEL_343:
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      LOBYTE(v418) = -55;  // SEH 展开状态号(低字节) = -55
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v81 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v81 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -54;  // SEH 展开状态号(低字节) = -54
        v414 = 1;  // 标记待释放成员位 = 1(0x1)
        v18 = sub_5144A0(nArg12, v81);  // v18 = sub_5144A0 · CNEventEquipment 构造器
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( (v414 & 1) != 0 )  // 展开位 v414&1 判定(需释放对应成员)
        sub_445150(v245);  // sub_445150 · 装备同步资源清理
      sub_605650(1, 10, 100, 9, 0, 4, 2);  // sub_605650 · 6 字段记录追加
      goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
    }
LABEL_335:
    Block[0] = operator new(0x5B4u);  // 分配 1460 字节对象(operator new, Block[0] 承接)
    LOBYTE(v418) = -58;  // SEH 展开状态号(低字节) = -58
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v80 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v80 = sub_4E9B10 · 装备参数结构构造
      LOBYTE(v418) = -57;  // SEH 展开状态号(低字节) = -57
      v412 = 0x80000000;
      v18 = sub_5163B0(nArg12, v80);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( v412 < 0 )  // v412 < 0 判定(无效值)
      sub_445150(v291);  // sub_445150 · 装备同步资源清理
    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
  }
  // ── [段 24] nArg1 == 10830 直判 ──
  if ( nArg1 == 10830 )  // nArg1 == 10830 判定
  {
LABEL_173:
    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
    LOBYTE(v418) = -118;  // SEH 展开状态号(低字节) = -118
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v48 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v48 = sub_4E9B10 · 装备参数结构构造
      LOBYTE(v418) = -117;  // SEH 展开状态号(低字节) = -117
      v412 = 2048;
      v18 = sub_514DE0(nArg12, v48);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( (v412 & 0x800) != 0 )  // 展开位 v412&0x800 判定(需释放对应成员)
    {
      sub_445150(v371);  // sub_445150 · 装备同步资源清理
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      return v18;  // 返回结果对象 v18(0=不支持该 ID)
    }
    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
  }
  // ── [段 25] ★ 南支 (≤10087) 段（~250 行）—— 1.0 万段（基础装备/称号族） ──
  //   10024/10030/10034/10038/10039/10043/10049/10054/10065/10068/10069/10070/10073/10074/10077/10086 十六点
  //   10065 = CNEquipmentVestofScreamGlass（惊叫玻璃衣）；10070 = CNEquipmentDressofEternalFlame（永恒之焰长裙）
  //   10074 = CNEquipmentVestofTauMane（牛头王鬃毛衣）；10086 = CNEventEquipment 通用收口
  if ( nArg1 <= 10087 )  // nArg1 <= 10087 判定
  {
    if ( nArg1 != 10087 )  // nArg1 != 10087 判定
    {
      switch ( nArg1 )  // 按 nArg1 分派
      {
        case 10024:  // case 10024 → 装备参数结构构造
        case 10065:  // case 10065 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -82;  // SEH 展开状态号(低字节) = -82
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v17 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v17 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -81;  // SEH 展开状态号(低字节) = -81
            v412 = (int)&unk_800000;
            v18 = sub_515410(nArg12, v17);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( ((unsigned int)&unk_800000 & v412) == 0 )  // 高位掩码判定(v412)
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          sub_445150(v271);  // sub_445150 · 装备同步资源清理
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v18;  // 返回结果对象 v18(0=不支持该 ID)
        case 10030:  // case 10030 → 装备参数结构构造
        case 10070:  // case 10070 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -79;  // SEH 展开状态号(低字节) = -79
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v19 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v19 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -78;  // SEH 展开状态号(低字节) = -78
            v412 = 0x1000000;
            v18 = sub_5166D0(nArg12, v19);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x1000000) == 0 )  // 展开位 v412&0x1000000 为 0(无需释放)
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          sub_445150(v393);  // sub_445150 · 装备同步资源清理
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v18;  // 返回结果对象 v18(0=不支持该 ID)
        case 10034:  // case 10034 → 装备参数结构构造
        case 10069:  // case 10069 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -76;  // SEH 展开状态号(低字节) = -76
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v20 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v20 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -75;  // SEH 展开状态号(低字节) = -75
            v412 = 0x2000000;
            v21 = sub_5144A0(nArg12, v20);  // v21 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v21 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x2000000) != 0 )  // 展开位 v412&0x2000000 判定(需释放对应成员)
            sub_445150(v311);  // sub_445150 · 装备同步资源清理
          sub_605650(1, 5, 100, 4, 0, 1, 2);  // sub_605650 · 6 字段记录追加
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v21;  // 返回结果对象 v21(0=不支持该 ID)
        case 10038:  // case 10038 → 装备参数结构构造
        case 10077:  // case 10077 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -73;  // SEH 展开状态号(低字节) = -73
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v22 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v22 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -72;  // SEH 展开状态号(低字节) = -72
            v412 = 0x4000000;
            v23 = sub_5144A0(nArg12, v22);  // v23 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v23 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x4000000) != 0 )  // 展开位 v412&0x4000000 判定(需释放对应成员)
            sub_445150(v391);  // sub_445150 · 装备同步资源清理
          sub_605650(1, 10, 100, 5, 0, 15, 2);  // sub_605650 · 6 字段记录追加
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v23;  // 返回结果对象 v23(0=不支持该 ID)
        case 10039:  // case 10039 → 装备参数结构构造
        case 10074:  // case 10074 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -70;  // SEH 展开状态号(低字节) = -70
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v24 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v24 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -69;  // SEH 展开状态号(低字节) = -69
            v412 = 0x8000000;
            v18 = sub_5160B0(nArg12, v24);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x8000000) == 0 )  // 展开位 v412&0x8000000 为 0(无需释放)
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          sub_445150(v235);  // sub_445150 · 装备同步资源清理
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v18;  // 返回结果对象 v18(0=不支持该 ID)
        case 10043:  // case 10043 → 装备参数结构构造
        case 10068:  // case 10068 → 装备参数结构构造
          Block[0] = operator new(0x90Cu);  // 分配 2316 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 120;  // 把 120 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v9 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v9 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 121;  // 把 121 低字节存入 v418(短串内联指针)
            v412 = 32;
            pObj = sub_514350(nArg12, v9, 16, 0);
          }
          else
          {
            pObj = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x20) != 0 )  // 展开位 v412&0x20 判定(需释放对应成员)
            sub_445150(v317);  // sub_445150 · 装备同步资源清理
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);  // 虚槽+176
          Block[0] = (void *)sub_41A5E0(v11 + 112);  // sub_41A5E0 · crypt4byte 解密校验
          v12 = (double)(int)Block[0] * 0.15000001;
          goto LABEL_16;  // 跳转 LABEL_16(收尾/共用分支)
        case 10049:  // case 10049 → 装备参数结构构造
        case 10073:  // case 10073 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = 123;  // 把 123 低字节存入 v418(短串内联指针)
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v14 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v14 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 124;  // 把 124 低字节存入 v418(短串内联指针)
            v412 = 64;
            v15 = sub_5144A0(nArg12, v14);  // v15 = sub_5144A0 · CNEventEquipment 构造器
          }
          else
          {
            v15 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x40) != 0 )  // 展开位 v412&0x40 判定(需释放对应成员)
            sub_445150(v313);  // sub_445150 · 装备同步资源清理
          sub_605650(0, 2, 100, 7, 0, 13, 0);  // sub_605650 · 6 字段记录追加
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v15;  // 返回结果对象 v15(0=不支持该 ID)
        case 10054:  // case 10054 → 装备参数结构构造
          Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
          LOBYTE(v418) = -85;  // SEH 展开状态号(低字节) = -85
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v16 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v16 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = -84;  // SEH 展开状态号(低字节) = -84
            v412 = 0x400000;
            pObj = sub_5141B0(nArg12, v16, 0, 1);
          }
          else
          {
            pObj = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v412 & 0x400000) != 0 )  // 展开位 v412&0x400000 判定(需释放对应成员)
            sub_445150(v395);  // sub_445150 · 装备同步资源清理
          sub_513B10(2, 1);
          v229 = 30;
          goto LABEL_17;  // 跳转 LABEL_17(收尾/共用分支)
        case 10086:  // case 10086 → 装备参数结构构造
          Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
          v418 = 361;  // SEH 展开状态号 = 361
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v25 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v25 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 106;  // 把 106 低字节存入 v418(短串内联指针)
            v415 = 0x40000;  // 标记待释放成员位 = 0x40000
            pObj = sub_5141B0(nArg12, v25, 0, 1);
          }
          else
          {
            pObj = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v415 & 0x40000) == 0 )  // 展开位 v415&0x40000 为 0(无需释放)
            goto LABEL_63;  // 跳转 LABEL_63(收尾/共用分支)
          v26 = &v389;
          goto LABEL_62;  // 跳转 LABEL_62(收尾/共用分支)
        default:
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
      }
    }
    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
    v418 = 364;  // SEH 展开状态号 = 364
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v27 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v27 = sub_4E9B10 · 装备参数结构构造
      LOBYTE(v418) = 109;  // 把 109 低字节存入 v418(短串内联指针)
      v415 = 0x80000;  // 标记待释放成员位 = 0x80000
      v18 = sub_5144A0(103, v27);  // v18 = sub_5144A0 · CNEventEquipment 构造器
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( (v415 & 0x80000) != 0 )  // 展开位 v415&0x80000 判定(需释放对应成员)
      sub_445150(v309);  // sub_445150 · 装备同步资源清理
    v229 = 20011;
    v228 = 0;
    v227 = 6;
    v226 = 100;
    v224 = 5;
    goto LABEL_268;  // 跳转 LABEL_268(收尾/共用分支)
  }
  // ── [段 26] ★ (10430, 10473] 段：10430 / 10442 / 10457 / 10469 / 10472 / 10473 ──
  //   10442 = CNEquipmentSummonOnDamage（受击召唤装备，0x544 大对象）
  if ( nArg1 > 10430 )  // 物品 ID > 10430(二分阈值,北支)
  {
    if ( nArg1 <= 10473 )  // nArg1 <= 10473 判定
    {
      if ( nArg1 == 10473 )  // nArg1 == 10473 判定
      {
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        v418 = 446;  // SEH 展开状态号 = 446
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v39 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v39 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = -65;  // SEH 展开状态号(低字节) = -65
          pMem2 = (void *)1024;  // pMem2 = 取 1024(转指针/类型)
          v18 = sub_519190(233, v39);
        }
        else
        {
          v18 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (BYTE1(pMem2) & 4) != 0 )  // 字节位 pMem2 位 4 判定
        {
          sub_445150(v377);  // sub_445150 · 装备同步资源清理
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v18;  // 返回结果对象 v18(0=不支持该 ID)
        }
        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
      }
      //   10469 = CNEquipmentAssaultAttackerCoat（突击攻击者外套）/ 10472 = CNEquipmentCoatofStarRocker（星辰摇滚衣）
      switch ( nArg1 )  // 按 nArg1 分派
      {
        case 10442:  // case 10442 → 装备参数结构构造
          Block[0] = operator new(0x544u);  // 分配 1348 字节对象(operator new, Block[0] 承接)
          v418 = 320;  // SEH 展开状态号 = 320
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v36 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v36 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 65;  // 把 65 低字节存入 v418(短串内联指针)
            v415 = 32;  // 标记待释放成员位 = 32(0x20)
            v18 = sub_514680(nArg12, v36);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v415 & 0x20) == 0 )  // 展开位 v415&0x20 为 0(无需释放)
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          sub_445150(v305);  // sub_445150 · 装备同步资源清理
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          result = v18;
          break;  // 跳出本 switch(单 case 处理完)
        case 10457:  // case 10457 → 装备参数结构构造
          goto LABEL_106;  // 跳转 LABEL_106(收尾/共用分支)
        case 10469:  // case 10469 → 装备参数结构构造
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 367;  // SEH 展开状态号 = 367
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            v37 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v37 = sub_4E9B10 · 装备参数结构构造
            LOBYTE(v418) = 112;  // 把 112 低字节存入 v418(短串内联指针)
            v415 = 0x100000;  // 标记待释放成员位 = 0x100000
            v18 = sub_517360(nArg12, v37);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v415 & 0x100000) == 0 )  // 展开位 v415&0x100000 为 0(无需释放)
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          sub_445150(v379);  // sub_445150 · 装备同步资源清理
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          result = v18;
          break;  // 跳出本 switch(单 case 处理完)
        case 10472:
          Block[0] = (void *)5;  // Block[0] = 常量 5
          sub_431230(Block);  // sub_431230 · uint32 vector push_back
          Block[0] = (void *)6;  // Block[0] = 常量 6
          sub_431230(Block);  // sub_431230 · uint32 vector push_back
          Block[0] = (void *)7;  // Block[0] = 常量 7
          sub_431230(Block);  // sub_431230 · uint32 vector push_back
          Block[0] = (void *)8;  // Block[0] = 常量 8
          sub_431230(Block);  // sub_431230 · uint32 vector push_back
          Block[0] = (void *)9;  // Block[0] = 常量 9
          sub_431230(Block);  // sub_431230 · uint32 vector push_back
          Block[0] = (void *)10;  // Block[0] = 常量 10
          sub_431230(Block);  // sub_431230 · uint32 vector push_back
          Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
          v418 = 397;  // SEH 展开状态号 = 397
          if ( Block[0] != nullptr )  // Block[0] 分配成功判定
          {
            pMem2 = &v226;
            sub_435020(pBuf);  // sub_435020 · uint32 向量整体赋值
            LOBYTE(v418) = -114;  // SEH 展开状态号(低字节) = -114
            v38 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v38 = sub_4E9B10 · 装备参数结构构造
            v415 = 0x20000000;  // 标记待释放成员位 = 0x20000000
            v418 = 400;  // SEH 展开状态号 = 400
            v18 = sub_518010(nArg12, v38, v226, (void *)v227, v228, v229);
          }
          else
          {
            v18 = 0;
          }
          v418 = 0;  // SEH 展开状态号 = 0
          if ( (v415 & 0x20000000) == 0 )  // 展开位 v415&0x20000000 为 0(无需释放)
            goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
          sub_445150(v267);  // sub_445150 · 装备同步资源清理
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          result = v18;
          break;  // 跳出本 switch(单 case 处理完)
        default:
          goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
      }
      return result;
    }
    //   10479 / 10816 两点
    if ( nArg1 > 10479 )  // 物品 ID > 10479(二分阈值,北支)
    {
      if ( nArg1 == 10816 )  // nArg1 == 10816 判定
      {
LABEL_167:
        Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
        LOBYTE(v418) = -121;  // SEH 展开状态号(低字节) = -121
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v46 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v46 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = -120;  // SEH 展开状态号(低字节) = -120
          v412 = 1024;
          v47 = sub_515950(nArg12, v46);
        }
        else
        {
          v47 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( (v412 & 0x400) != 0 )  // 展开位 v412&0x400 判定(需释放对应成员)
          sub_445150(v301);  // sub_445150 · 装备同步资源清理
        sub_605650(1, 5, 100, 7, 0, 4, 2);  // sub_605650 · 6 字段记录追加
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
        return v47;  // 返回结果对象 v47(0=不支持该 ID)
      }
      goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
    }
    //   10479 支第二路
    if ( nArg1 == 10479 )  // nArg1 == 10479 判定
    {
      Block[0] = operator new(0x5B4u);  // 分配 1460 字节对象(operator new, Block[0] 承接)
      v418 = 506;  // SEH 展开状态号 = 506
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v43 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v43 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -5;  // SEH 展开状态号(低字节) = -5
        pMem2 = (void *)0x20000000;  // 标记待释放成员位 = 0x20000000(第 2 组掩码)
        v30 = sub_51A0C0(239, v43);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( ((unsigned int)pMem2 & 0x20000000) != 0 )  // 展开位 pMem2&0x20000000 判定
      {
        sub_445150(v239);  // sub_445150 · 装备同步资源清理
        sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
        return v30;  // 返回结果对象 v30(0=不支持该 ID)
      }
      goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
    }
    //   10476 / 10477 两个相邻 ID（同族双型）
    if ( nArg1 != 10476 )  // nArg1 != 10476 判定
    {
      if ( nArg1 == 10477 )  // nArg1 == 10477 判定
      {
        Block[0] = operator new(0xCD0u);  // 分配 3280 字节对象(operator new, Block[0] 承接)
        v418 = 503;  // SEH 展开状态号 = 503
        if ( Block[0] != nullptr )  // Block[0] 分配成功判定
        {
          v40 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v40 = sub_4E9B10 · 装备参数结构构造
          LOBYTE(v418) = -8;  // SEH 展开状态号(低字节) = -8
          pMem2 = (void *)0x10000000;  // 标记待释放成员位 = 0x10000000(第 2 组掩码)
          v30 = sub_51B900(237, v40);
        }
        else
        {
          v30 = 0;
        }
        v418 = 0;  // SEH 展开状态号 = 0
        if ( ((unsigned int)pMem2 & 0x10000000) != 0 )  // 展开位 pMem2&0x10000000 判定
        {
          sub_445150(v303);  // sub_445150 · 装备同步资源清理
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
          return v30;  // 返回结果对象 v30(0=不支持该 ID)
        }
        goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
      }
LABEL_155:
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      return 0;  // 返回 0(不支持该物品 ID)
    }
    Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
    v418 = 499;  // SEH 展开状态号 = 499
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v41 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v41 = sub_4E9B10 · 装备参数结构构造
      LOBYTE(v418) = -12;  // SEH 展开状态号(低字节) = -12
      pMem2 = (void *)0x8000000;  // 标记待释放成员位 = 0x8000000(第 2 组掩码)
      v30 = sub_5144A0(236, v41);  // v30 = sub_5144A0 · CNEventEquipment 构造器
    }
    else
    {
      v30 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( ((unsigned int)pMem2 & 0x8000000) != 0 )  // 展开位 pMem2&0x8000000 判定
      sub_445150(v375);  // sub_445150 · 装备同步资源清理
    v405 = 0;
    v406 = 0;
    v407 = 1106247680;  // 置 v407 = 1106247680（float 30.0f）
    v408 = 1;
    v409 = 0;
    v410 = 1101004800;  // 置 v410 = 1101004800（float 20.0f）
    Block[0] = operator new(0x7Cu);  // 分配 124 字节对象(operator new, Block[0] 承接)
    v418 = 502;  // SEH 展开状态号 = 502
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v42 = sub_5101B0(&v405, 2, 30000, 1);  // v42 = sub_5101B0 · CNChangeStatus 构造器
      v229 = 0;
      v228 = v42;
    }
    else
    {
      v229 = 0;
      v228 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    v227 = 0;
    goto LABEL_217;  // 跳转 LABEL_217(收尾/共用分支)
  }
  // ── [段 27] nArg1 == 10430 直判 → case 10430 ──
  if ( nArg1 == 10430 )  // nArg1 == 10430 判定
  {
LABEL_106:
    Block[0] = operator new(0x5D4u);  // 分配 1492 字节对象(operator new, Block[0] 承接)
    LOBYTE(v418) = 126;  // 把 126 低字节存入 v418(短串内联指针)
    if ( Block[0] != nullptr )  // Block[0] 分配成功判定
    {
      v35 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v35 = sub_4E9B10 · 装备参数结构构造
      LOBYTE(v418) = 127;  // 把 127 低字节存入 v418(短串内联指针)
      v412 = 128;
      v18 = sub_516A90(nArg12, v35);
    }
    else
    {
      v18 = 0;
    }
    v418 = 0;  // SEH 展开状态号 = 0
    if ( (v412 & 0x80u) != 0 )  // 展开位 v412&0x80 判定(需释放对应成员)
    {
      sub_445150(v381);  // sub_445150 · 装备同步资源清理
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      return v18;  // 返回结果对象 v18(0=不支持该 ID)
    }
    goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
  }
  // ── [段 28] ★ 最南端 switch（10092-10100 九 ID）—— 1.0 万段收尾（外套族） ──
  //   10092 = CNEquipmentManaholickerCoat（玛那嗜者外套）/ 10094 = CNEquipmentMusingRegaliaRob（沉思法衣）
  //   10097 = CNEquipmentZiegGarbCoat（赛格哈特外套，0x5B4）/ 10098 = CNEquipmentSilentFreyjaRobe（寂静弗雷娅法袍）
  //   10099 = CNEquipmentAirVintageCoat（复古空气外套）/ 10100 = CNEquipmentManaLamellaRobe（玛那薄片法袍）
  switch ( nArg1 )  // 按 nArg1 分派
  {
    case 10092:  // case 10092 → 装备参数结构构造
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      v418 = 443;  // SEH 展开状态号 = 443
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v28 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v28 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -68;  // SEH 展开状态号(低字节) = -68
        pMem2 = (void *)512;  // pMem2 = 取 512(转指针/类型)
        v18 = sub_519080(nArg12, v28);
      }
      else
      {
        v18 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( (BYTE1(pMem2) & 2) == 0 )  // 字节位掩码(pMem2 特定字节)&2 判定
        goto LABEL_269;  // 跳转 LABEL_269(收尾/共用分支)
      sub_445150(v387);  // sub_445150 · 装备同步资源清理
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      result = v18;
      break;  // 跳出本 switch(单 case 处理完)
    case 10094:  // case 10094 → 装备参数结构构造
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      v418 = 484;  // SEH 展开状态号 = 484
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v29 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v29 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -27;  // SEH 展开状态号(低字节) = -27
        pMem2 = (void *)0x400000;  // 标记待释放成员位 = 0x400000(第 2 组掩码)
        v30 = sub_519770(nArg12, v29);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( ((unsigned int)pMem2 & 0x400000) == 0 )  // 字节位掩码 pMem2&0x400000 为 0(无需释放)
        goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
      sub_445150(v269);  // sub_445150 · 装备同步资源清理
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      result = v30;
      break;  // 跳出本 switch(单 case 处理完)
    case 10097:  // case 10097 → 装备参数结构构造
      Block[0] = operator new(0x5B4u);  // 分配 1460 字节对象(operator new, Block[0] 承接)
      v418 = 487;  // SEH 展开状态号 = 487
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v31 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v31 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -24;  // SEH 展开状态号(低字节) = -24
        pMem2 = &unk_800000;
        v30 = sub_519910(nArg12, v31);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( ((unsigned int)&unk_800000 & (unsigned int)pMem2) == 0 )  // 高位掩码(pMem2 与 0x800000)判定
        goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
      sub_445150(v385);  // sub_445150 · 装备同步资源清理
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      result = v30;
      break;  // 跳出本 switch(单 case 处理完)
    case 10098:  // case 10098 → 装备参数结构构造
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      v418 = 490;  // SEH 展开状态号 = 490
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v32 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v32 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -21;  // SEH 展开状态号(低字节) = -21
        pMem2 = (void *)0x1000000;  // 标记待释放成员位 = 0x1000000(第 2 组掩码)
        v30 = sub_519BF0(nArg12, v32);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( ((unsigned int)pMem2 & 0x1000000) == 0 )  // 字节位掩码 pMem2&0x1000000 为 0(无需释放)
        goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
      sub_445150(v307);  // sub_445150 · 装备同步资源清理
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      result = v30;
      break;  // 跳出本 switch(单 case 处理完)
    case 10099:  // case 10099 → 装备参数结构构造
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      v418 = 493;  // SEH 展开状态号 = 493
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v33 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v33 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -18;  // SEH 展开状态号(低字节) = -18
        pMem2 = (void *)0x2000000;  // 标记待释放成员位 = 0x2000000(第 2 组掩码)
        v30 = sub_519D30(nArg12, v33);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( ((unsigned int)pMem2 & 0x2000000) == 0 )  // 字节位掩码 pMem2&0x2000000 为 0(无需释放)
        goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
      sub_445150(v383);  // sub_445150 · 装备同步资源清理
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      result = v30;
      break;  // 跳出本 switch(单 case 处理完)
    case 10100:  // case 10100 → 装备参数结构构造
      Block[0] = operator new(0x5B0u);  // 分配 1456 字节对象(operator new, Block[0] 承接)
      v418 = 496;  // SEH 展开状态号 = 496
      if ( Block[0] != nullptr )  // Block[0] 分配成功判定
      {
        v34 = sub_4E9B10(nArg4, nArg5, nArg3, nArg2);  // v34 = sub_4E9B10 · 装备参数结构构造
        LOBYTE(v418) = -15;  // SEH 展开状态号(低字节) = -15
        pMem2 = (void *)0x4000000;  // 标记待释放成员位 = 0x4000000(第 2 组掩码)
        v30 = sub_519EF0(nArg12, v34);
      }
      else
      {
        v30 = 0;
      }
      v418 = 0;  // SEH 展开状态号 = 0
      if ( ((unsigned int)pMem2 & 0x4000000) == 0 )  // 字节位掩码 pMem2&0x4000000 为 0(无需释放)
        goto LABEL_219;  // 跳转 LABEL_219(收尾/共用分支)
      sub_445150(v249);  // sub_445150 · 装备同步资源清理
      sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
      result = v30;
      break;  // 跳出本 switch(单 case 处理完)
    // ── [段 29] default：该 ID 不受本函数支持，返回 0（交由 sub_522300 后续装备判定路径处理） ──
    default:
      goto LABEL_155;  // 跳转 LABEL_155(收尾/共用分支)
  }
  return result;
}

