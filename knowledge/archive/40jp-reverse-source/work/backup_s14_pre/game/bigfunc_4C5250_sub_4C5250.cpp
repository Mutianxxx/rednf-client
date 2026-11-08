// ============================================================
// 【40JP逆向源代码工程】src/game/bigfunc_4C5250_sub_4C5250.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x4C5250）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 3003 行；字符串证据 5 条；外调 6 个
//   串: "GUN_DRAW1"
//   串: "BOWGUN_DRAW1"
//   串: "Effect/Animation/NapalmBombShoot.ani"
//   串: "Particle/NapalmBomb.ptl"
//   串: "NAPALM_SHOT"
//   调: sub_4C5250 sub_4B7430 sub_4C23A0 sub_4C2530 sub_699000 sub_4AECE0
//   case 分支地图（共 9 处）:
//     L1145  case 0xC:
//     L1214  case 0xF:
//     L1278  case 0x10:
//     L1305  case 0x12:
//     L1352  case 0x14:
//     L1460  case 0x16:
//     L2553  case 0x17:
//     L2828  case 0x1A:
//     L2833  case 0x1B:
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x4C5250 sub_4C5250  size=18096
// ------------------------------------------------------------
int /*usercall*/ sub_4C5250@<eax>(int pArg1@<ecx>, double fArg2@<st0>)
{
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int pObj11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // edi
  bool v15; // cc
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  int pObj15; // edi
  int v23; // edx
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // ecx
  int v28; // edi
  int pObj20; // edi
  int v30; // ecx
  int v31; // ebx
  int v32; // eax
  int v33; // ebx
  int nRand23; // eax
  int nRand43; // edx
  int nRand232; // edi
  int v37; // eax
  char *v38; // eax
  uint32_t *v39; // ecx
  int v40; // eax
  int pObj2; // edi
  int v42; // ecx
  int v43; // ebx
  int v44; // edi
  int pObj21; // edi
  int v46; // ecx
  int v47; // ebx
  int v48; // eax
  int v49; // eax
  int v50; // edi
  int v51; // eax
  int v52; // eax
  int v53; // ecx
  int v54; // eax
  int v55; // eax
  char *v56; // eax
  uint32_t *v57; // ecx
  int v58; // edi
  int pObj33; // edi
  int v60; // ecx
  int v61; // ebx
  int v62; // eax
  char *v63; // ecx
  int pObj4; // edi
  bool v65; // bl
  int v66; // eax
  int nRand44; // ecx
  void *v68; // ecx
  char *v69; // eax
  uint32_t *v70; // ecx
  int v71; // eax
  int pObj17; // edi
  int v73; // ecx
  int v74; // ebx
  int v75; // eax
  uint32_t *v76; // ecx
  int v77; // eax
  int pObj8; // edi
  int v79; // ecx
  int v80; // ebx
  int v81; // eax
  int v82; // eax
  int v83; // eax
  int v84; // eax
  uint64_t v85; // rax
  int v86; // eax
  int v87; // eax
  int v88; // eax
  double v89; // st7
  int v90; // ebx
  int pObj10; // edi
  int v92; // edx
  int v93; // eax
  int pObj26; // edi
  int v95; // ecx
  int v96; // ebx
  int v97; // edx
  int v98; // ecx
  int v99; // eax
  int pObj29; // ecx
  int v101; // eax
  int v102; // eax
  int v103; // eax
  int v104; // edi
  int v105; // eax
  int v106; // eax
  int v107; // edi
  int pObj32; // edi
  int v109; // ecx
  int v110; // ebx
  int pObj34; // edi
  bool v112; // bl
  int v113; // eax
  int nRand42; // ecx
  void *v115; // ecx
  uint32_t *v116; // ecx
  int v117; // eax
  int pObj24; // edi
  int v119; // ecx
  int v120; // ebx
  int v121; // eax
  uint32_t *v122; // ecx
  int v123; // eax
  int pObj14; // edi
  int v125; // ecx
  int v126; // ebx
  int v127; // eax
  int v128; // edi
  int v129; // edi
  int v130; // eax
  int v131; // edi
  int *v132; // edi
  int v133; // ecx
  int v134; // ebx
  int v135; // eax
  int v136; // ebx
  int v137; // eax
  int v138; // eax
  int v139; // eax
  int v140; // edi
  int pObj23; // edi
  int v142; // ecx
  int v143; // ebx
  int v144; // ebx
  int v145; // eax
  int v146; // eax
  int v147; // eax
  int v148; // ecx
  int v149; // eax
  int v150; // edx
  int v151; // eax
  uint32_t *v152; // edi
  int j; // ebx
  int v154; // edx
  int v155; // edi
  int pObj3; // edi
  int v157; // ecx
  int v158; // ebx
  int v159; // ebx
  int v160; // eax
  int v161; // eax
  int v162; // eax
  uint32_t *v163; // edi
  int i; // ebx
  int v165; // edx
  int v166; // eax
  int pObj16; // ecx
  int pObj6; // ecx
  int pObj35; // ecx
  int v170; // eax
  int v171; // ecx
  int v172; // edi
  int nRand; // ebx
  int v174; // edi
  int nRand3; // edi
  int v176; // eax
  int v177; // edx
  uint32_t *v178; // ecx
  int v179; // eax
  int pObj; // edi
  int v181; // ecx
  uint32_t *v182; // ecx
  int v183; // eax
  int pObj9; // edi
  int v185; // ecx
  int v186; // edi
  int v187; // eax
  int v188; // ecx
  int v189; // ebx
  uint32_t *v190; // edi
  int v191; // edx
  uint32_t *v192; // edi
  int k; // ebx
  int v194; // edi
  int v195; // ebx
  int v196; // eax
  int v197; // eax
  int v198; // eax
  int v199; // edx
  int v200; // eax
  int nRand5; // eax
  int v202; // edx
  int v203; // edi
  int v204; // edi
  bool v205; // zf
  signed int nRand6; // eax
  char *v207; // eax
  bool v208; // zf
  signed int nRand7; // eax
  int *v210; // edi
  int v211; // ecx
  int v212; // ebx
  int v213; // eax
  int v214; // ebx
  int v215; // eax
  int v216; // eax
  int v217; // eax
  int v218; // ebx
  int v219; // edi
  int v220; // eax
  int v221; // eax
  int v222; // edi
  int v223; // eax
  int v224; // edx
  int v225; // ebx
  int v226; // edi
  int v227; // ebx
  int v228; // eax
  int v229; // edi
  int v230; // ebx
  int v231; // eax
  int v232; // eax
  int v233; // ebx
  int v234; // ecx
  int v235; // edx
  int v236; // edi
  int v237; // edi
  int v238; // ecx
  int v239; // ebx
  int v240; // eax
  int v241; // edx
  int pObj5; // ecx
  int v243; // ebx
  int pObj22; // edi
  int v245; // edx
  int v246; // eax
  int pObj27; // edi
  int v248; // ecx
  int v249; // ebx
  int v250; // eax
  int v251; // eax
  int v252; // eax
  int v253; // edi
  int v254; // eax
  int v255; // eax
  int v256; // edi
  int pObj30; // edi
  int v258; // ecx
  int v259; // ebx
  int pObj12; // edi
  bool v261; // bl
  int v262; // eax
  int nRand45; // ecx
  void *v264; // ecx
  uint32_t *v265; // ecx
  int v266; // eax
  int pObj31; // edi
  int v268; // ecx
  int v269; // ebx
  int v270; // eax
  uint32_t *v271; // ecx
  int v272; // eax
  int pObj25; // edi
  int v274; // ecx
  int v275; // ebx
  int v276; // eax
  int v277; // edi
  int nRand25; // ebx
  int v279; // edi
  int v280; // eax
  int v281; // edi
  double v282; // st7
  int v283; // eax
  int v284; // edi
  int v285; // ebx
  int *v286; // ecx
  int v287; // ebx
  double v288; // st7
  double v289; // st7
  int *v290; // ebx
  double v291; // st7
  int v292; // edx
  int v293; // eax
  int pObj13; // ebx
  double v295; // st7
  int v296; // edi
  int *v297; // edi
  uint64_t v298; // rax
  int *v299; // edi
  int v300; // ebx
  int v301; // ecx
  int v302; // edi
  int *v303; // edi
  int v304; // ecx
  int v305; // ebx
  int v306; // eax
  int v307; // ebx
  int v308; // eax
  int v309; // eax
  int v310; // eax
  int v311; // ecx
  int v312; // edi
  int *v313; // edi
  int v314; // ecx
  int v315; // ebx
  int v316; // eax
  int v317; // ebx
  int v318; // eax
  int v319; // eax
  int v320; // eax
  int v321; // edi
  int result; // eax
  int pObj28; // ecx
  int pObj7; // ecx
  int pObj18; // ecx
  uint32_t *v326; // eax
  int v327; // edx
  int v328; // eax
  int v329; // edi
  int v330; // eax
  int *v331; // edx
  int v332; // eax
  int v333; // ecx
  int v334; // edi
  int v335; // edi
  int v336; // eax
  int v337; // eax
  int v338; // eax
  int v339; // eax
  int v340; // eax
  int pObj19; // ecx
  int v342; // eax
  int v343; // eax
  int v344; // eax
  int v345; // eax
  int v346; // eax
  int v347; // eax
  int v348; // edx
  int v349; // edi
  int v350; // eax
  int *v351; // edi
  int v352; // eax
  int v353; // eax
  int v354; // eax
  int v355; // eax
  int v356; // eax
  int v357; // eax
  int v358; // eax
  int v359; // eax
  int v360; // ecx
  int v361; // eax
  int v362; // eax
  int v363; // edi
  int v364; // eax
  bool v365; // zf
  int v366; // eax
  int v367; // eax
  int v368; // ecx
  int v369; // eax
  double v370; // st7
  char v372; // c0
  int v373; // edx
  int v374; // eax
  int v375; // edi
  int v376; // eax
  int v377; // eax
  int v378; // edi
  int v379; // eax
  uint32_t *v380; // edi
  int v381; // eax
  int v382; // eax
  int v383; // eax
  int v384; // edi
  int v385; // eax
  int v386; // eax
  int v387; // eax
  int v388; // edi
  int v389; // eax
  int v390; // eax
  int v391; // edi
  int v392; // eax
  int v393; // eax
  int v394; // edi
  int v395; // eax
  unsigned int v396; // [esp+38h] [ebp-FCh]
  int v397; // [esp+44h] [ebp-F0h]
  int v398; // [esp+44h] [ebp-F0h]
  int nRand22; // [esp+44h] [ebp-F0h]
  int v400; // [esp+44h] [ebp-F0h]
  int nRand24; // [esp+44h] [ebp-F0h]
  int v402; // [esp+48h] [ebp-ECh]
  int v403; // [esp+48h] [ebp-ECh]
  int v404; // [esp+48h] [ebp-ECh]
  int v405; // [esp+48h] [ebp-ECh]
  float v406; // [esp+48h] [ebp-ECh]
  int v407; // [esp+48h] [ebp-ECh]
  int v408; // [esp+48h] [ebp-ECh]
  int v409; // [esp+48h] [ebp-ECh]
  int v410; // [esp+48h] [ebp-ECh]
  int v411; // [esp+48h] [ebp-ECh]
  int v412; // [esp+48h] [ebp-ECh]
  int v413; // [esp+48h] [ebp-ECh]
  int v414; // [esp+48h] [ebp-ECh]
  int v415; // [esp+48h] [ebp-ECh]
  int v416; // [esp+48h] [ebp-ECh]
  int v417; // [esp+48h] [ebp-ECh]
  float v418; // [esp+4Ch] [ebp-E8h]
  int v419; // [esp+50h] [ebp-E4h]
  int v420; // [esp+54h] [ebp-E0h]
  int v421[4]; // [esp+58h] [ebp-DCh] BYREF
  uint8_t v422[16]; // [esp+68h] [ebp-CCh] BYREF
  uint8_t v423[16]; // [esp+78h] [ebp-BCh] BYREF
  uint8_t v424[16]; // [esp+88h] [ebp-ACh] BYREF
  uint8_t v425[16]; // [esp+98h] [ebp-9Ch] BYREF
  int v426; // [esp+A8h] [ebp-8Ch]
  uint32_t v427[4]; // [esp+ACh] [ebp-88h] BYREF
  int v428; // [esp+BCh] [ebp-78h] BYREF
  char v429[4]; // [esp+C0h] [ebp-74h] BYREF
  void *v430; // [esp+C4h] [ebp-70h]
  int v431; // [esp+C8h] [ebp-6Ch]
  int v432; // [esp+CCh] [ebp-68h]
  char v433; // [esp+D3h] [ebp-61h]
  int v434; // [esp+D4h] [ebp-60h] BYREF
  int m; // [esp+D8h] [ebp-5Ch] BYREF
  int nRand4; // [esp+DCh] [ebp-58h] BYREF
  int nRand2; // [esp+E0h] [ebp-54h] BYREF
  int v438; // [esp+E4h] [ebp-50h] BYREF
  int nRand8; // [esp+E8h] [ebp-4Ch] BYREF
  char v440[4]; // [esp+ECh] [ebp-48h] BYREF
  uint32_t v441[5]; // [esp+F0h] [ebp-44h] BYREF
  unsigned int v442; // [esp+104h] [ebp-30h]
  char v443[4]; // [esp+108h] [ebp-2Ch] BYREF
  uint32_t v444[2]; // [esp+10Ch] [ebp-28h] BYREF
  char v445[4]; // [esp+114h] [ebp-20h] BYREF
  void *Block; // [esp+118h] [ebp-1Ch]
  int v447; // [esp+11Ch] [ebp-18h]
  unsigned int v448; // [esp+120h] [ebp-14h]
  int dword_796E502; // [esp+124h] [ebp-10h]
  int v450; // [esp+130h] [ebp-4h]

  // ── [段 1] 入口序：dword_796E502 快照 → sub_4B7430 通用逐帧前置 → 进大状态 switch(pArg1+6556) ──
  //   pArg1 = CNGunner 对象（本函数 = CNGunner::vt+332，class_method_slots.txt 直证）；
  //   +6556=大状态机状态号；+8516=技能号(表号)；+120=动画对象；+7212/+6160=两枚参照对象槽；
  //   case 表 0/7/8/0xC/0xF/0x10/0x12/0x14/0x16/0x17/0x1A/0x1B；LABEL_463 为公共尾（全 case 汇合）
  dword_796E502 = dword_796E50;  // dword_796E502＝dword_796E50
  sub_4B7430((int *)pArg1, fArg2);  // sub_4B7430 · 升级演出装配
  switch ( *(uint32_t *)(pArg1 + 6556) )
  {
    // ── [段 2] 大状态 0：待机态 —— 双参照对象的动画帧对齐（+8536/+8540 游标自纠）──
    //   与 +7212 比帧：落后或超前时按 (end-begin)/88 算帧数逐格追平（sub_4C23A0 逐帧施）；
    //   与 +6160 比帧：用 sub_4C2530 单向递增；两处都对齐不了就置游标 -1（本状态不参与）
    case 0:
      v3 = *(uint32_t *)(pArg1 + 120);  // 字段 pAnimObj(pArg1+120) 读写
      if ( v3 == *(uint32_t *)(pArg1 + 7212) )  // 字段 +7212(pArg1+7212) 条件判定
      {
        v4 = *(uint32_t *)(v3 + 148);  // 字段 +148(v3+148) 读写
        if ( v4 < *(uint32_t *)(pArg1 + 8536) )  // 字段 +8536(pArg1+8536) 条件判定
        {
          while ( 1 )
          {
            v5 = *(uint32_t *)(pArg1 + 120);  // 字段 pAnimObj(pArg1+120) 读写
            v6 = *(uint32_t *)(v5 + 44);  // 字段 +44(v5+44) 读写
            v7 = v5 + 40;
            v8 = v6 != 0 ? (*(uint32_t *)(v7 + 8) - v6) / 88 : 0;  // 字段 +8(v7+8) 读写
            v9 = *(uint32_t *)(pArg1 + 8536);  // 字段 +8536(pArg1+8536) 读写
            if ( v9 >= v8 )  // v9 >= v8 判定
              break;  // 跳出本 switch(单 case 处理完)
            *(uint32_t *)(pArg1 + 8536) = v9 + 1;  // 字段 +8536(pArg1+8536) 读写
            v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 6500) + 16))(*(uint32_t *)(pArg1 + 6500));  // 字段 nWeaponItemId(pArg1+6500) 读写
            sub_4C23A0(pArg1, *(uint32_t *)(pArg1 + 8536), *(uint32_t *)(v10 + 4));
          }
          *(uint32_t *)(pArg1 + 8536) = -1;  // 字段 +8536(pArg1+8536) 读写
        }
        while ( *(uint32_t *)(pArg1 + 8536) < v4 )
        {
          pObj11 = *(uint32_t *)(pArg1 + 6500);  // 字段 nWeaponItemId(pArg1+6500) 读写
          ++*(uint32_t *)(pArg1 + 8536);  // 字段 +8536(pArg1+8536) 自增/更新
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 16))(pObj11);  // 虚槽+16
          sub_4C23A0(pArg1, *(uint32_t *)(pArg1 + 8536), *(uint32_t *)(v12 + 4));
        }
      }
      else
      {
        *(uint32_t *)(pArg1 + 8536) = -1;  // 字段 +8536(pArg1+8536) 读写
      }
      v13 = *(uint32_t *)(pArg1 + 120);  // 字段 pAnimObj(pArg1+120) 读写
      if ( v13 == *(uint32_t *)(pArg1 + 6160) )  // 字段 +6160(pArg1+6160) 条件判定
      {
        v14 = *(uint32_t *)(v13 + 148);  // 字段 +148(v13+148) 读写
        v15 = *(uint32_t *)(pArg1 + 8540) < v14;  // 字段 nPhaseStamp(pArg1+8540) 读写
        if ( *(uint32_t *)(pArg1 + 8540) > v14 )  // 字段 nPhaseStamp(pArg1+8540) 条件判定
        {
          while ( 1 )
          {
            v16 = *(uint32_t *)(pArg1 + 120);  // 字段 pAnimObj(pArg1+120) 读写
            v17 = *(uint32_t *)(v16 + 44);  // 字段 +44(v16+44) 读写
            v18 = v16 + 40;
            v19 = v17 != 0 ? (*(uint32_t *)(v18 + 8) - v17) / 88 : 0;  // 字段 +8(v18+8) 读写
            v20 = *(uint32_t *)(pArg1 + 8540);  // 字段 nPhaseStamp(pArg1+8540) 读写
            if ( v20 >= v19 )  // v20 >= v19 判定
              break;  // 跳出本 switch(单 case 处理完)
            *(uint32_t *)(pArg1 + 8540) = v20 + 1;  // 字段 nPhaseStamp(pArg1+8540) 读写
            sub_4C2530(v20 + 1);
          }
          *(uint32_t *)(pArg1 + 8540) = -1;  // 字段 nPhaseStamp(pArg1+8540) 读写
          v15 = v14 > -1;
        }
        if ( v15 )  // v15 为真则进入
        {
          do
          {
            v402 = *(uint32_t *)(pArg1 + 8540) + 1;  // 字段 nPhaseStamp(pArg1+8540) 读写
            *(uint32_t *)(pArg1 + 8540) = v402;  // 字段 nPhaseStamp(pArg1+8540) 读写
            sub_4C2530(v402);
          }
          while ( *(uint32_t *)(pArg1 + 8540) < v14 );
        }
      }
      else
      {
        *(uint32_t *)(pArg1 + 8540) = -1;  // 字段 nPhaseStamp(pArg1+8540) 读写
      }
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 3] 大状态 7：★ 跳跃/落闪（ReduceRevolverDelayJump 系）—— 着地冲量 ──
    //   +8616 为 1/2 分型；需 +8560 时刻到点且 +616 无占用；
    //   sub_4AECE0 切动画后按宿主 +16 速度取模长，按朝向（vt+152==0 时取负）算 +8620；
    //   vt+876 双段位移 + vt+896 挂帧（朝向不对则 sub_432E50 翻转） + sub_495890(2,0) 帧率 + vt+888 帧长；
    //   sub_41A5E0(+8276) 与宿主 +24 值合成 sub_494F20(2, 时长) 用；sub_4C46B0(2) 取表后
    //   sub_4C17C0 三点采样（+52/+48/+44 三虚函数）→ sub_45FE80 挂接粒子（+60 绑主）；
    //   本机支再采样一次（30/0/83）按 +8616 分型 ±4 后 vt+40 设位 + sub_4B2580 打表 + vt+12/vt+112/vt+92；
    //   vt+1096 分型 0/1/2 三支各挂不同粒子（MusketDust 大小 / ReduceRevolverDelayJump）；
    //   尾段 sub_423340(+8348, szPassword) 判定后按 +8372 是否 <0x10 择内联/堆指针播技能名，最后清 +8560=-1
    case 7:
      v84 = *(uint32_t *)(pArg1 + 8616);  // 字段 bPhase8616(pArg1+8616) 读写
      if ( (v84 == 1 || v84 == 2)
        && *(uint32_t *)(pArg1 + 8560) != -1
        && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8560)  // 【clock_now(clk)】
        && *(uint32_t *)(pArg1 + 616) == -1 )
      {
        sub_4AECE0(*(uint32_t *)(pArg1 + 8616) != 1 ? 4 : 1);
        v85 = (uint64_t)*(float *)(*(uint32_t *)(pArg1 + 112) + 16);  // 字段 pHostComp(pArg1+112) 读写
        *(uint32_t *)(pArg1 + 8620) = v85;  // 字段 bAlarmFlag(pArg1+8620) 读写
        if ( (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 152))(pArg1, HIDWORD(v85)) == 0 )  // 虚槽+152 → 取值(参数)
          *(uint32_t *)(pArg1 + 8620) = -*(uint32_t *)(pArg1 + 8620);  // 字段 bAlarmFlag(pArg1+8620) 读写
        v86 = *(uint32_t *)(pArg1 + 8620) - sub_41A5E0(pArg1 + 8262);  // v86 = sub_41A5E0 · crypt4byte 解密校验
        *(uint32_t *)(pArg1 + 8620) = v86;  // 字段 bAlarmFlag(pArg1+8620) 读写
        v396 = abs32(v86);
        (*(void (/*thiscall*/ **)(int, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 调用
          pArg1,
          0,
          v396,
          v396,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 调用
          pArg1,
          1,
          0,
          0,
          0,
          0,
          0);
        v87 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
        if ( *(int *)(pArg1 + 8620) < 0 )  // 字段 bAlarmFlag(pArg1+8620) 判定
          v87 = sub_432E50(v87);  // v87 = sub_432E50 · 关系码对调映射
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 896))(pArg1, v87, 4);  // 虚槽+896
        sub_495890(2, 0);  // sub_495890 · 模式选择式方位设置
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)pArg1 + 888))(pArg1, 0, 0, 1000, 1000);  // 虚槽+888 → 帧长标定
        *(float *)&v88 = COERCE_FLOAT(sub_41A5E0(pArg1 + 8276));  // sub_41A5E0 · crypt4byte 解密校验
        v89 = *(float *)(*(uint32_t *)(pArg1 + 112) + 24);  // 字段 pHostComp(pArg1+112) 读写
        nRand8 = v88;
        v406 = v89 * 0.5 + (double)v88;
        sub_494F20(2, v406);  // sub_494F20 · 属性浮点槽写入
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 8))(  // 调用
          *(uint32_t *)(pArg1 + 8216),
          *(uint32_t *)(pArg1 + 8244));
        nRand4 = 0;
        nRand2 = 0;
        *(float *)&v438 = 0.0;  // 写内存
        // ── [段 4] 大状态 7 之粒子/尘效主体：sub_4C46B0(2) 取表 → sub_4C17C0 三点采样 ──
        //   +52/+48/+44 三虚函数取尺寸后 sub_45FE80 挂接（+60 绑主），sub_4A06D0 设置完收尾
        v90 = sub_4C46B0(2);
        if ( v90 != 0 )  // v90 != 0 判定
        {
          pObj10 = *(uint32_t *)(pArg1 + 8216);  // 字段 nAtkActionType(pArg1+8216) 读写
          v92 = *(uint32_t *)pObj10;  // 缓存对象虚表基址
          m = pObj10;
          v407 = (*(int (**)(void))(v92 + 52))();
          v398 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj10 + 48))(pObj10);  // 虚槽+48 → 归属坐标x
          v93 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj10 + 44))(pObj10);  // 虚槽+44
          sub_4C17C0(&nRand4, &nRand2, &v438, v93, v398, v407);
          nRand8 = *(int *)(*(uint32_t *)(pArg1 + 120) + 164);  // 字段 pAnimObj(pArg1+120) 读写
          sub_493D00(*(float *)&nRand8);  // sub_493D00 · 变速
          *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
          v450 = 16;
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            pObj26 = 0;
          else
            pObj26 = sub_44E1F0(v90, 1);  // pObj26 = sub_44E1F0 · CNRDPooledObject 构造
          v95 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_45FE80(v95, pObj26, 2, 0, pObj26, pArg1, 0);  // sub_45FE80 · 对象注册
          v96 = *(uint32_t *)pObj26;  // 缓存对象虚表基址
          v408 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
          (*(void (/*thiscall*/ **)(int))(v96 + 148))(pObj26);  // 虚槽+148 → 位置/朝向写入
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj26 + 112))(pObj26, nRand4, nRand2, v438);  // 虚槽+112 → 坐标三元组写入
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj26 + 60))(pObj26, pArg1);  // 虚槽+60 → 对象销毁/释放
          sub_4A06D0(v408);  // sub_4A06D0 · 绑定目标对象并记录相对偏移
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚槽+308 → 是否本地玩家
        {
          sub_4C17C0(&nRand4, &nRand2, &v438, 30, 0, 83);
          if ( *(uint32_t *)(pArg1 + 8616) == 1 )  // 字段 bPhase8616(pArg1+8616) 条件判定
          {
            v97 = nRand2 + 4;
            v98 = v438 + 4;
          }
          else
          {
            v97 = nRand2 - 4;
            v98 = v438 - 4;
          }
          v438 = v98;
          v99 = v98;
          pObj29 = *(uint32_t *)(pArg1 + 8216);  // 字段 nAtkActionType(pArg1+8216) 读写
          nRand2 = v97;
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj29 + 40))(pObj29, nRand4, v97, v99);  // 虚槽+40 → 条件查询(273等)
          v101 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216));  // 字段 nAtkActionType(pArg1+8216) 读写
          sub_4B2580(pArg1 + 8568, pArg1 + 8572, pArg1, nRand4, nRand2, v438, 0, *(uint32_t *)(v101 + 76), 4, 4, -1, 480, 34, 34, 34);  // sub_4B2580 · 目标搜索 + 瞄准角输出
          v102 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216));  // 字段 nAtkActionType(pArg1+8216) 读写
          *(uint32_t *)(v102 + 72) += *(uint32_t *)(pArg1 + 8568);  // 字段 +72(v102+72) 自增/更新
          v103 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216));  // 字段 nAtkActionType(pArg1+8216) 读写
          *(uint32_t *)(v103 + 76) += *(uint32_t *)(pArg1 + 8572);  // 字段 +76(v103+76) 自增/更新
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 12))(*(uint32_t *)(pArg1 + 8216), 0);  // 字段 nAtkActionType(pArg1+8216) 读写
          v104 = **(uint32_t **)(pArg1 + 8216);
          v105 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
          (*(void (/*thiscall*/ **)(uint32_t, int))(v104 + 112))(*(uint32_t *)(pArg1 + 8216), v105 == 3 ? pArg1 : 0);  // 字段 nAtkActionType(pArg1+8216) 读写
          (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(pArg1 + 8216) + 92))(*(uint32_t *)(pArg1 + 8216), v423);  // 字段 nAtkActionType(pArg1+8216) 读写
          sub_5E5260(v423);  // sub_5E5260：清理临时缓冲
        }
        // ── [段 5] 大状态 7 之枪种分派：vt+1096() 三支（1 走 dword_8F830C 专用件 + vt+28+84 朝向位）──
        v106 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
        if ( v106 != 0 )  // v106 != 0 判定
        {
          if ( v106 == 1 )  // v106 == 1 判定
          {
            sub_4C17C0(&nRand4, &nRand2, &v438, 42, 0, 76);
            pObj34 = dword_8F830C;  // dword_8F830C＝专用件
            v112 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) == 0;  // 虚槽+152 → 取值(参数)
            v113 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj34 + 28))(pObj34);  // 虚槽+28
            v410 = v438;
            nRand42 = nRand4;
            nRand22 = nRand2;
            *(uint8_t *)(v113 + 84) = v112;  // 字节字段 +84(v113+84) 判定
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj34 + 40))(pObj34, nRand42, nRand22, v410);  // 虚槽+40 → 条件查询(273等)
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj34 + 12))(pObj34, 0);  // 虚槽+12
            (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj34 + 92))(pObj34, v445);  // 虚槽+92 → 读剩余(返回长度)
            v115 = *(void **)(pArg1 + 116);
            v450 = 19;
            sub_4600B0(v115, 2, 0, (int)v445);  // sub_4600B0：演播层注册
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_5E5260(v445);  // sub_5E5260：清理临时缓冲
          }
          else if ( v106 == 2 )  // 否则 v106==2 分支
          {
            sub_4C17C0(&nRand4, &nRand2, &v438, 28, 0, 97);
            sub_401710("Character/Gunner/Effect/Animation/MusketDust/MusketDustSmall3.ani");  // sub_401710 · std::string 复位并赋值 C 串
            v450 = 20;
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            LOBYTE(v450) = 21;  // 把 21 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            {
              pObj24 = 0;
            }
            else
            {
              v434 = sub_42FCB0(228);  // v434 = sub_42FCB0 · CRT 一次性初始化
              LOBYTE(v450) = 22;  // 把 22 低字节存入 v450(短串内联指针)
              if ( v434 != 0 )  // v434 != 0 判定
              {
                LOBYTE(v116) = v444[0];  // 取 std::string v444 首字节(短串内联首个 char)
                if ( v448 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                  v116 = v444;
                v117 = sub_431860((char)v116, 1);  // v117 = sub_431860 · 动画件构造
              }
              else
              {
                v117 = 0;
              }
              LOBYTE(v450) = 21;  // 把 21 低字节存入 v450(短串内联指针)
              pObj24 = sub_44E1F0(v117, 1);  // pObj24 = sub_44E1F0 · CNRDPooledObject 构造
            }
            v119 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            LOBYTE(v450) = 20;  // 把 20 低字节存入 v450(短串内联指针)
            sub_45FE80(v119, pObj24, 2, 0, pObj24, pArg1, 1);  // sub_45FE80 · 对象注册
            v120 = *(uint32_t *)pObj24;  // 缓存对象虚表基址
            v121 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int, int))(v120 + 148))(pObj24, v121);  // 虚槽+148 → 位置/朝向写入
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj24 + 112))(pObj24, nRand4, nRand2, v438);  // 虚槽+112 → 坐标三元组写入
            sub_4C17C0(&nRand4, &nRand2, &v438, -12, 0, 132);
            sub_406D60("Character/Gunner/Effect/Animation/MusketDust/MusketDustLarge.ani");  // sub_406D60 · std::string 从 C 串赋值
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            LOBYTE(v450) = 23;  // 把 23 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            {
              pObj14 = 0;
            }
            else
            {
              v434 = sub_42FCB0(228);  // v434 = sub_42FCB0 · CRT 一次性初始化
              LOBYTE(v450) = 24;  // 把 24 低字节存入 v450(短串内联指针)
              if ( v434 != 0 )  // v434 != 0 判定
              {
                LOBYTE(v122) = v444[0];  // 取 std::string v444 首字节(短串内联首个 char)
                if ( v448 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                  v122 = v444;
                v123 = sub_431860((char)v122, 1);  // v123 = sub_431860 · 动画件构造
              }
              else
              {
                v123 = 0;
              }
              LOBYTE(v450) = 23;  // 把 23 低字节存入 v450(短串内联指针)
              pObj14 = sub_44E1F0(v123, 1);  // pObj14 = sub_44E1F0 · CNRDPooledObject 构造
            }
            v125 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            LOBYTE(v450) = 20;  // 把 20 低字节存入 v450(短串内联指针)
            sub_45FE80(v125, pObj14, 2, 0, pObj14, pArg1, 0);  // sub_45FE80 · 对象注册
            v126 = *(uint32_t *)pObj14;  // 缓存对象虚表基址
            v127 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int, int))(v126 + 148))(pObj14, v127);  // 虚槽+148 → 位置/朝向写入
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj14 + 112))(pObj14, nRand4, nRand2, v438);  // 虚槽+112 → 坐标三元组写入
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_501490(v443);
          }
        }
        else if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 22) > 0 )  // 虚槽+1140 → 读技能表
        {
          sub_4C17C0(&nRand4, &nRand2, &v438, 0, 0, 0);
          *(float *)&nRand8 = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
          v450 = 17;
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            v107 = 0;
          else
            v107 = sub_431860((char)"Character/Gunner/Effect/Animation/ReduceRevolverDelayJump.ani", 1);  // v107 = sub_431860 · 动画件构造
          nRand8 = *(int *)(*(uint32_t *)(pArg1 + 120) + 164);  // 字段 pAnimObj(pArg1+120) 读写
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_493D00(*(float *)&nRand8);  // sub_493D00 · 变速
          *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
          v450 = 18;
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            pObj32 = 0;
          else
            pObj32 = sub_44E1F0(v107, 1);  // pObj32 = sub_44E1F0 · CNRDPooledObject 构造
          v109 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_45FE80(v109, pObj32, 2, 0, pObj32, pArg1, 0);  // sub_45FE80 · 对象注册
          v110 = *(uint32_t *)pObj32;  // 缓存对象虚表基址
          v409 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
          (*(void (/*thiscall*/ **)(int))(v110 + 148))(pObj32);  // 虚槽+148 → 位置/朝向写入
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj32 + 112))(pObj32, nRand4, nRand2, v438);  // 虚槽+112 → 坐标三元组写入
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj32 + 60))(pObj32, pArg1);  // 虚槽+60 → 对象销毁/释放
          sub_4A06D0(v409);  // sub_4A06D0 · 绑定目标对象并记录相对偏移
        }
        if ( (uint8_t)sub_423340(pArg1 + 8348, szPassword) != 0 )  // sub_423340 · 串首比较判定
        {
          if ( *(uint32_t *)(pArg1 + 8372) < 0x10u )  // 字段 nDiffVal(pArg1+8372) 条件判定
            v128 = pArg1 + 8352;
          else
            v128 = *(uint32_t *)(pArg1 + 8352);  // 字段 nVtRet(pArg1+8352) 读写
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, v128, -1, 0, 0);  // 虚槽+212 → vt+212
        }
        *(uint32_t *)(pArg1 + 8560) = -1;  // 字段 +8560(pArg1+8560) 读写
      }
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 6] 大状态 8：★ 拔枪/上膛（GUN_DRAW1 / BOWGUN_DRAW1）—— +8577 分型 0..3 ──
    //   0/2 支：+8576==0 且（帧数达标）时按 vt+1096 分型 0..4 选武器串（v444），vt+212 播报后置 +8576=1；
    //   1/3 支：NapalmBombShoot.ani + Particle/NapalmBomb（NAPALM_SHOT）—— 见下面 828-1160 段
    case 8:
      if ( sub_41A5E0(pArg1 + 8577) == 0 || sub_41A5E0(pArg1 + 8577) == 2 )  // sub_41A5E0 · crypt4byte 解密校验
      {
        if ( *(uint8_t *)(pArg1 + 8576) == 0  // 字节字段 nFadeAlpha(pArg1+8576) 判定
          && (sub_41A5E0(pArg1 + 8577) == 0 || sub_41A5E0(pArg1 + 8577) == 2 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 2) )  // sub_41A5E0：crypt4byte 解密校验
        {
          v448 = 15;
          v447 = 0;
          LOBYTE(v444[0]) = 0;  // 清短串 v444 首字节
          v82 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
          v450 = 0;
          v83 = (*(int (/*thiscall*/ **)(int))(v82 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
          if ( v83 >= 0 )  // v83 >= 0 判定(取值有效)
          {
            if ( v83 <= 3 )  // v83 <= 3 判定
            {
              sub_4015C0("GUN_DRAW1", 9u);  // 【std::string构造赋值】
            }
            else if ( v83 == 4 )  // 否则 v83==4 分支
            {
              sub_406D60("BOWGUN_DRAW1");  // sub_406D60 · std::string 从 C 串赋值
            }
          }
          (*(void (/*thiscall*/ **)(int, uint32_t *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, v444, -1, 0, 0);  // 虚槽+212 → vt+212
          *(uint8_t *)(pArg1 + 8576) = 1;  // 字节字段 nFadeAlpha(pArg1+8576) 判定
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_501490(v443);
        }
      }
      // ── [段 7] 大状态 8 之 1/3 支主体：★ 燃烧弹（NapalmBombShoot.ani + NAPALM_SHOT）──
      //   sub_431920 建 NapalmBombShoot.ani（内联/堆指针二选一）+ sub_4C17C0 三点采样定位；
      //   sub_44B6C0(284) 粒子池门控 → sub_44E1F0 构造 → sub_45FE80 挂接 → vt+148 时刻同步 → vt+112 落位；
      //   LABEL_121/122/133 为中途汇合点；末尾若 +8516==26 跳 LABEL_463（交给 26 号技能态）
      else if ( (sub_41A5E0(pArg1 + 8577) == 1 || sub_41A5E0(pArg1 + 8577) == 3)  // sub_41A5E0 · crypt4byte 解密校验
             && *(uint32_t *)(pArg1 + 8560) != -1
             && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8560) )  // 【clock_now(clk)】
      {
        sub_4AECE0(1);
        if ( *(uint8_t *)(pArg1 + 8596) != 0 )  // 字节字段 +8596(pArg1+8596) 判定
          v21 = *(uint32_t *)(pArg1 + 8224);  // 字段 f_2020(pArg1+8224) 读写
        else
          v21 = *(uint32_t *)(pArg1 + 8220);  // 字段 nGrabTargetSel(pArg1+8220) 读写
        v403 = v21;
        (*(void (**)(void))(**(uint32_t **)(pArg1 + 8216) + 8))();  // 调用
        pObj15 = *(uint32_t *)(pArg1 + 8216);  // 字段 nAtkActionType(pArg1+8216) 读写
        v23 = *(uint32_t *)pObj15;  // 缓存对象虚表基址
        nRand2 = 0;
        nRand4 = 0;
        *(float *)&v438 = 0.0;  // 写内存
        m = pObj15;
        v397 = (*(int (**)(void))(v23 + 52))();
        v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj15 + 48))(pObj15);  // 虚槽+48 → 归属坐标x
        v25 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj15 + 44))(pObj15, v24);  // 虚槽+44
        sub_4C17C0(&nRand2, &nRand4, &v438, v25, v397, v403);
        v26 = *(uint32_t *)(pArg1 + 8516);  // 字段 f_2144(pArg1+8516) 读写
        if ( v26 == 53 )  // v26 == 53 判定
        {
          *(float *)&nRand8 = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
          v450 = 1;
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
          {
            v28 = 0;
          }
          else
          {
            if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // 字段 nAnimPoolCap(pArg1+384) 条件判定
              LOBYTE(v27) = pArg1 + 108;
            else
              v27 = *(uint32_t *)(pArg1 + 364);  // 字段 pAnimPool(pArg1+364) 读写
            v28 = sub_431920(v27, (char)"Effect/Animation/NapalmBombShoot.ani", 1);  // v28 = sub_431920 · 动画件构造
          }
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
          v450 = 2;
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            pObj20 = 0;
          else
            pObj20 = sub_44E1F0(v28, 1);  // pObj20 = sub_44E1F0 · CNRDPooledObject 构造
          v30 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_45FE80(v30, pObj20, 2, 0, pObj20, pArg1, 0);  // sub_45FE80 · 对象注册
          v31 = *(uint32_t *)pObj20;  // 缓存对象虚表基址
          v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
          (*(void (/*thiscall*/ **)(int, int))(v31 + 148))(pObj20, v32);  // 虚槽+148 → 位置/朝向写入
          v33 = v438;
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj20 + 112))(pObj20, nRand2, nRand4, v438);  // 虚槽+112 → 坐标三元组写入
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚槽+308 → 是否本地玩家
          {
            nRand23 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 588))(pArg1, "Particle/NapalmBomb.ptl");  // 虚槽+588
            nRand43 = nRand4;
            nRand232 = nRand23;
            *(uint32_t *)nRand23 = nRand2;  // 写内存
            *(uint32_t *)(nRand23 + 4) = nRand43;  // 字段 +4(nRand23+4) 读写
            *(uint32_t *)(nRand23 + 8) = v33;  // 字段 +8(nRand23+8) 读写
            v418 = 0.0;  // 置 v418 = 0.0(浮点初值)
            *(uint8_t *)(nRand23 + 84) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) == 0;  // 虚槽+152 → 取值(参数)
            v37 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1140))(pArg1);  // 虚槽+1140 → 读技能表
            sub_4E4C10(pArg1, 22209, v37, 53, nRand232, 0, 0, 0);  // sub_4E4C10 · 与
          }
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用
            pArg1,
            "NAPALM_SHOT",  // 事件/标签 NAPALM_SHOT
            -1,
            0,
            0);
        }
        else
        {
          if ( v26 == 5 )  // v26 == 5 判定
          {
            v38 = "Effect/Animation/HeadShotDown.ani";  // 播 动画 HeadShotDown.ani
            if ( *(uint8_t *)(pArg1 + 8596) == 0 )  // 字节字段 +8596(pArg1+8596) 判定
              v38 = "Effect/Animation/HeadShotUp.ani";  // 播 动画 HeadShotUp.ani
            sub_401710(v38);  // sub_401710 · std::string 复位并赋值 C 串
            v450 = 3;
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            LOBYTE(v450) = 4;  // 把 4 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            {
              pObj2 = 0;
            }
            else
            {
              v434 = sub_42FCB0(228);  // v434 = sub_42FCB0 · CRT 一次性初始化
              LOBYTE(v450) = 5;  // 把 5 低字节存入 v450(短串内联指针)
              if ( v434 != 0 )  // v434 != 0 判定
              {
                LOBYTE(v39) = v441[0];  // 取 std::string v441 首字节(短串内联首个 char)
                if ( v442 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                  v39 = v441;
                if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // 字段 nAnimPoolCap(pArg1+384) 条件判定
                  v40 = sub_431920(pArg1 + 108, (char)v39, 1);  // v40 = sub_431920 · 动画件构造
                else
                  v40 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)v39, 1);  // v40 = sub_431920 · 动画件构造
              }
              else
              {
                v40 = 0;
              }
              LOBYTE(v450) = 4;  // 把 4 低字节存入 v450(短串内联指针)
              pObj2 = sub_44E1F0(v40, 1);  // pObj2 = sub_44E1F0 · CNRDPooledObject 构造
            }
            v42 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            LOBYTE(v450) = 3;  // 把 3 低字节存入 v450(短串内联指针)
            sub_45FE80(v42, pObj2, 2, 0, pObj2, pArg1, 0);  // sub_45FE80 · 对象注册
            v43 = *(uint32_t *)pObj2;  // 缓存对象虚表基址
            v404 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int))(v43 + 148))(pObj2);  // 虚槽+148 → 位置/朝向写入
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, nRand2, nRand4, v438);  // 虚槽+112 → 坐标三元组写入
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 60))(pObj2, pArg1);  // 虚槽+60 → 对象销毁/释放
            sub_4A06D0(v404);  // sub_4A06D0 · 绑定目标对象并记录相对偏移
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_501490(v440);
          }
          v44 = sub_4C46B0(*(uint8_t *)(pArg1 + 8596) != 0);
          if ( v44 != 0 )  // v44 != 0 判定
          {
            nRand8 = *(int *)(*(uint32_t *)(pArg1 + 120) + 164);  // 字段 pAnimObj(pArg1+120) 读写
            sub_493D00(*(float *)&nRand8);  // sub_493D00 · 变速
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            v450 = 6;
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
              pObj21 = 0;
            else
              pObj21 = sub_44E1F0(v44, 1);  // pObj21 = sub_44E1F0 · CNRDPooledObject 构造
            v46 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_45FE80(v46, pObj21, 2, 0, pObj21, pArg1, 0);  // sub_45FE80 · 对象注册
            v47 = *(uint32_t *)pObj21;  // 缓存对象虚表基址
            v405 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int))(v47 + 148))(pObj21);  // 虚槽+148 → 位置/朝向写入
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj21 + 112))(pObj21, nRand2, nRand4, v438);  // 虚槽+112 → 坐标三元组写入
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj21 + 60))(pObj21, pArg1);  // 虚槽+60 → 对象销毁/释放
            sub_4A06D0(v405);  // sub_4A06D0 · 绑定目标对象并记录相对偏移
          }
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚槽+308 → 是否本地玩家
          {
            if ( *(uint8_t *)(pArg1 + 8596) != 0 )  // 字节字段 +8596(pArg1+8596) 判定
              sub_4C17C0(&nRand2, &nRand4, &v438, 44, 0, 90);
            else
              sub_4C17C0(&nRand2, &nRand4, &v438, 47, 0, 119);
            (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 8216) + 40))(  // 调用
              *(uint32_t *)(pArg1 + 8216),
              nRand2,
              nRand4,
              v438);
            v48 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216));  // 字段 nAtkActionType(pArg1+8216) 读写
            *(uint32_t *)(v48 + 72) += *(uint32_t *)(pArg1 + 8568);  // 字段 +72(v48+72) 自增/更新
            v49 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216));  // 字段 nAtkActionType(pArg1+8216) 读写
            *(uint32_t *)(v49 + 76) += *(uint32_t *)(pArg1 + 8572);  // 字段 +76(v49+76) 自增/更新
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 12))(*(uint32_t *)(pArg1 + 8216), 0);  // 字段 nAtkActionType(pArg1+8216) 读写
            v50 = **(uint32_t **)(pArg1 + 8216);
            v51 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
            (*(void (/*thiscall*/ **)(uint32_t, int))(v50 + 112))(*(uint32_t *)(pArg1 + 8216), v51 == 3 ? pArg1 : 0);  // 字段 nAtkActionType(pArg1+8216) 读写
            (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(pArg1 + 8216) + 92))(*(uint32_t *)(pArg1 + 8216), v422);  // 字段 nAtkActionType(pArg1+8216) 读写
            sub_5E5260(v422);  // sub_5E5260：清理临时缓冲
          }
          v52 = sub_41A5E0(pArg1 + 8577);  // v52 = sub_41A5E0 · crypt4byte 解密校验
          if ( (uint8_t)sub_423340(28 * (v52 != 1) + pArg1 + 8348, szPassword) != 0 )  // sub_423340 · 串首比较判定
          {
            v53 = 28 * (sub_41A5E0(pArg1 + 8577) != 1);  // v53 = sub_41A5E0 · crypt4byte 解密校验
            if ( *(uint32_t *)(v53 + pArg1 + 8372) < 0x10u )
              v54 = v53 + pArg1 + 8352;
            else
              v54 = *(uint32_t *)(v53 + pArg1 + 8352);
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, v54, -1, 0, 0);  // 虚槽+212 → vt+212
          }
        }
        v55 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
        if ( v55 == 0 )  // v55 == 0 判定
        {
          if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 22) > 0 )  // 虚槽+1140 → 读技能表
          {
            v56 = "Character/Gunner/Effect/Animation/ReduceRevolverDelayDown.ani";  // 播 动画 ReduceRevolverDelayDown.ani
            if ( *(uint8_t *)(pArg1 + 8596) == 0 )  // 字节字段 +8596(pArg1+8596) 判定
              v56 = "Character/Gunner/Effect/Animation/ReduceRevolverDelayUp.ani";  // 播 动画 ReduceRevolverDelayUp.ani
            sub_401710(v56);  // sub_401710 · std::string 复位并赋值 C 串
            v450 = 7;
            *(float *)&nRand8 = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
            LOBYTE(v450) = 8;  // 把 8 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            {
              v58 = 0;
            }
            else
            {
              LOBYTE(v57) = v441[0];  // 取 std::string v441 首字节(短串内联首个 char)
              if ( v442 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                v57 = v441;
              v58 = sub_431860((char)v57, 1);  // v58 = sub_431860 · 动画件构造
            }
            nRand8 = *(int *)(*(uint32_t *)(pArg1 + 120) + 164);  // 字段 pAnimObj(pArg1+120) 读写
            LOBYTE(v450) = 7;  // 把 7 低字节存入 v450(短串内联指针)
            sub_493D00(*(float *)&nRand8);  // sub_493D00 · 变速
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            LOBYTE(v450) = 9;  // 把 9 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
              pObj33 = 0;
            else
              pObj33 = sub_44E1F0(v58, 1);  // pObj33 = sub_44E1F0 · CNRDPooledObject 构造
            v60 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            LOBYTE(v450) = 7;  // 把 7 低字节存入 v450(短串内联指针)
            sub_45FE80(v60, pObj33, 2, 0, pObj33, pArg1, 0);  // sub_45FE80 · 对象注册
            v61 = *(uint32_t *)pObj33;  // 缓存对象虚表基址
            v62 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int, int))(v61 + 148))(pObj33, v62);  // 虚槽+148 → 位置/朝向写入
            sub_4C17C0(&nRand2, &nRand4, &v438, 0, 0, 0);
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj33 + 112))(pObj33, nRand2, nRand4, v438);  // 虚槽+112 → 坐标三元组写入
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj33 + 60))(pObj33, pArg1);  // 虚槽+60 → 对象销毁/释放
            sub_4A06D0(LODWORD(v418));  // sub_4A06D0 · 绑定目标对象并记录相对偏移
            v418 = 0.0;  // 置 v418 = 0.0(浮点初值)
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "R_PANING", -1, 0);  // 虚槽+212 → vt+212
            v63 = v440;
// ── [段 8] 大状态 0x12 之中段汇合点 LABEL_121（追瞄对象更新链）──
LABEL_121:
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_501490(v63);
            goto LABEL_122;  // 跳转 LABEL_122(收尾/共用分支)
          }
          goto LABEL_122;  // 跳转 LABEL_122(收尾/共用分支)
        }
        if ( v55 != 1 )  // v55 != 1 判定
        {
          if ( v55 == 2 )  // v55 == 2 判定
          {
            if ( *(uint8_t *)(pArg1 + 8596) != 0 )  // 字节字段 +8596(pArg1+8596) 判定
              sub_4C17C0(&nRand2, &nRand4, &v438, 54, 0, 103);
            else
              sub_4C17C0(&nRand2, &nRand4, &v438, 49, 0, 127);
            v69 = "Character/Gunner/Effect/Animation/MusketDust/MusketDustSmall2.ani";  // 播 动画 MusketDustSmall2.ani
            if ( *(uint8_t *)(pArg1 + 8596) == 0 )  // 字节字段 +8596(pArg1+8596) 判定
              v69 = "Character/Gunner/Effect/Animation/MusketDust/MusketDustSmall1.ani";  // 播 动画 MusketDustSmall1.ani
            sub_401710(v69);  // sub_401710 · std::string 复位并赋值 C 串
            v450 = 11;
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            LOBYTE(v450) = 12;  // 把 12 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            {
              pObj17 = 0;
            }
            else
            {
              v434 = sub_42FCB0(228);  // v434 = sub_42FCB0 · CRT 一次性初始化
              LOBYTE(v450) = 13;  // 把 13 低字节存入 v450(短串内联指针)
              if ( v434 != 0 )  // v434 != 0 判定
              {
                LOBYTE(v70) = v444[0];  // 取 std::string v444 首字节(短串内联首个 char)
                if ( v448 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                  v70 = v444;
                v71 = sub_431860((char)v70, 1);  // v71 = sub_431860 · 动画件构造
              }
              else
              {
                v71 = 0;
              }
              LOBYTE(v450) = 12;  // 把 12 低字节存入 v450(短串内联指针)
              pObj17 = sub_44E1F0(v71, 1);  // pObj17 = sub_44E1F0 · CNRDPooledObject 构造
            }
            v73 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            LOBYTE(v450) = 11;  // 把 11 低字节存入 v450(短串内联指针)
            sub_45FE80(v73, pObj17, 2, 0, pObj17, pArg1, 1);  // sub_45FE80 · 对象注册
            v74 = *(uint32_t *)pObj17;  // 缓存对象虚表基址
            v75 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int, int))(v74 + 148))(pObj17, v75);  // 虚槽+148 → 位置/朝向写入
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj17 + 112))(pObj17, nRand2, nRand4, v438);  // 虚槽+112 → 坐标三元组写入
            if ( *(uint8_t *)(pArg1 + 8596) != 0 )  // 字节字段 +8596(pArg1+8596) 判定
              sub_4C17C0(&nRand2, &nRand4, &v438, 14, 0, 138);
            else
              sub_4C17C0(&nRand2, &nRand4, &v438, 9, 0, 127);
            sub_406D60("Character/Gunner/Effect/Animation/MusketDust/MusketDustLarge.ani");  // sub_406D60 · std::string 从 C 串赋值
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            LOBYTE(v450) = 14;  // 把 14 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            {
              pObj8 = 0;
            }
            else
            {
              v434 = sub_42FCB0(228);  // v434 = sub_42FCB0 · CRT 一次性初始化
              LOBYTE(v450) = 15;  // 把 15 低字节存入 v450(短串内联指针)
              if ( v434 != 0 )  // v434 != 0 判定
              {
                LOBYTE(v76) = v444[0];  // 取 std::string v444 首字节(短串内联首个 char)
                if ( v448 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                  v76 = v444;
                v77 = sub_431860((char)v76, 1);  // v77 = sub_431860 · 动画件构造
              }
              else
              {
                v77 = 0;
              }
              LOBYTE(v450) = 14;  // 把 14 低字节存入 v450(短串内联指针)
              pObj8 = sub_44E1F0(v77, 1);  // pObj8 = sub_44E1F0 · CNRDPooledObject 构造
            }
            v79 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            LOBYTE(v450) = 11;  // 把 11 低字节存入 v450(短串内联指针)
            sub_45FE80(v79, pObj8, 2, 0, pObj8, pArg1, 0);  // sub_45FE80 · 对象注册
            v80 = *(uint32_t *)pObj8;  // 缓存对象虚表基址
            v81 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int, int))(v80 + 148))(pObj8, v81);  // 虚槽+148 → 位置/朝向写入
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 112))(pObj8, nRand2, nRand4, v438);  // 虚槽+112 → 坐标三元组写入
            v63 = v443;
            goto LABEL_121;  // 跳转 LABEL_121(收尾/共用分支)
          }
LABEL_122:
          *(uint32_t *)(pArg1 + 8560) = -1;  // 字段 +8560(pArg1+8560) 读写
          goto LABEL_133;  // 跳转 LABEL_133(收尾/共用分支)
        }
        if ( *(uint8_t *)(pArg1 + 8596) != 0 )  // 字节字段 +8596(pArg1+8596) 判定
          sub_4C17C0(&nRand2, &nRand4, &v438, 67, 0, 110);
        else
          sub_4C17C0(&nRand2, &nRand4, &v438, 67, 0, 122);
        pObj4 = dword_8F830C;  // dword_8F830C＝专用件
        v65 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) == 0;  // 虚槽+152 → 取值(参数)
        v66 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 28))(pObj4);  // 虚槽+28
        nRand44 = nRand4;
        *(uint8_t *)(v66 + 84) = v65;  // 字节字段 +84(v66+84) 判定
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 40))(pObj4, nRand2, nRand44, v438);  // 虚槽+40 → 条件查询(273等)
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj4 + 12))(pObj4, 0);  // 虚槽+12
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj4 + 92))(pObj4, v445);  // 虚槽+92 → 读剩余(返回长度)
        v68 = *(void **)(pArg1 + 116);
        v450 = 10;
        sub_4600B0(v68, 2, 0, (int)v445);  // sub_4600B0：演播层注册
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);  // sub_5E5260：清理临时缓冲
        *(uint32_t *)(pArg1 + 8560) = -1;  // 字段 +8560(pArg1+8560) 读写
      }
// ── [段 9] 大状态 8 之收束汇合点 LABEL_133：+8516==26 门 → 公共尾 ──
LABEL_133:
      // ── [段 10] 大状态 8 之尾判：+8516==26 时跳公共尾（技能 26 优先于 8 态演出）──
      if ( *(uint32_t *)(pArg1 + 8516) == 26 )  // 字段 f_2144(pArg1+8516) 条件判定
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 612))(pArg1, 1, 2);  // 虚槽+612 → 拆分/脱离
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 11] 大状态 0xC（12）：★ 冲刺攻击尘土（DashAttackDust1/2.ani）──
    //   按 +120 对象与 +7252 是否一致分两支，各带时刻门（150 / +8644+400）；
    //   sub_431860 建 Dust 动画后 sub_45FE80 挂接；goto LABEL_463
    case 0xC:
      if ( *(uint32_t *)(pArg1 + 120) != *(uint32_t *)(pArg1 + 7252) && sub_699000(pArg1 + 6560) >= 150 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(pArg1 + 7252));  // 虚槽+196 → 物件非空判定
        sub_4926A0(*(uint32_t *)(pArg1 + 120));  // sub_4926A0 · 帧游标复位
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pArg1 + 876))(  // 调用
          pArg1,
          0,
          *(uint32_t *)(pArg1 + 8632),
          *(uint32_t *)(pArg1 + 8632),
          0,
          *(uint32_t *)(pArg1 + 8636),
          1);
        v129 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
        v130 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 152))(pArg1, 4);  // 虚槽+152 → 取值(参数)
        (*(void (/*thiscall*/ **)(int, int))(v129 + 896))(pArg1, v130);  // 虚槽+896
        v450 = 25;
        if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 · CRT 一次性初始化
          v131 = sub_431860((char)"Character/Gunner/Effect/Animation/DashAttackDust1.ani", 1);  // v131 = sub_431860 · 动画件构造
        else
          v131 = 0;
        *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
        v450 = 26;
        if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
          v132 = nullptr;
        else
          v132 = (int *)sub_44E1F0(v131, 1);  // v132 = sub_44E1F0 · CNRDPooledObject 构造
        v133 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_45FE80(v133, (int)v132, 2, 0, (int)v132, pArg1, 0);  // sub_45FE80 · 对象注册
        v134 = *v132;  // v134 = 取 v132 首 dword(对象虚表基址)
        v135 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
        (*(void (/*thiscall*/ **)(int *, int))(v134 + 148))(v132, v135);  // 虚槽+148 → 位置/朝向写入
        v136 = *v132;  // v136 = 取 v132 首 dword(对象虚表基址)
        v137 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚槽+128 → 目标坐标y上界
        v138 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v137);  // 虚槽+124 → 目标坐标y下界
        v139 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v138);  // 虚槽+120 → 转发(对象+缓冲)
        (*(void (/*thiscall*/ **)(int *, int))(v136 + 112))(v132, v139);  // 虚槽+112 → 坐标三元组写入
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "SLIDING", -1, 0, 0);  // 虚槽+212 → vt+212
      }
      if ( *(uint32_t *)(pArg1 + 120) == *(uint32_t *)(pArg1 + 7252) && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8644) + 400 )  // 【clock_now(clk)】
      {
        v450 = 27;
        if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 · CRT 一次性初始化
          v140 = sub_431860((char)"Character/Gunner/Effect/Animation/DashAttackDust2.ani", 1);  // v140 = sub_431860 · 动画件构造
        else
          v140 = 0;
        *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
        v450 = 28;
        if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
          pObj23 = 0;
        else
          pObj23 = sub_44E1F0(v140, 1);  // pObj23 = sub_44E1F0 · CNRDPooledObject 构造
        v142 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_45FE80(v142, pObj23, 2, 0, pObj23, pArg1, 0);  // sub_45FE80 · 对象注册
        v143 = *(uint32_t *)pObj23;  // 缓存对象虚表基址
        v411 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
        (*(void (/*thiscall*/ **)(int))(v143 + 148))(pObj23);  // 虚槽+148 → 位置/朝向写入
        v144 = *(uint32_t *)pObj23;  // 缓存对象虚表基址
        v145 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚槽+128 → 目标坐标y上界
        v146 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v145);  // 虚槽+124 → 目标坐标y下界
        v147 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v146);  // 虚槽+120 → 转发(对象+缓冲)
        (*(void (/*thiscall*/ **)(int, int))(v144 + 112))(pObj23, v147);  // 虚槽+112 → 坐标三元组写入
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj23 + 60))(pObj23, pArg1);  // 虚槽+60 → 对象销毁/释放
        sub_4A06D0(v411);  // sub_4A06D0 · 绑定目标对象并记录相对偏移
        *(uint32_t *)(pArg1 + 8644) = sub_699000(pArg1 + 6560);  // sub_699000 · clock_now
      }
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 12] 大状态 0xF（15）：★ 旋风（WindmillDust3.ani）—— +120 对象帧 170 非 0 才建 ──
    //   +8676 标志与前方帧数 >=2 的门控；sub_431860 建件；goto LABEL_463
    case 0xF:
      if ( *(uint8_t *)(pArg1 + 8676) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 2 )  // 字段 pAnimObj(pArg1+120) 条件判定
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);  // 虚槽+352
        *(uint8_t *)(pArg1 + 8676) = 1;  // 字节字段 bPhase8676(pArg1+8676) 判定
      }
      v148 = *(uint32_t *)(pArg1 + 120);  // 字段 pAnimObj(pArg1+120) 读写
      if ( *(uint8_t *)(v148 + 170) != 0 )  // 字节字段 +170(v148+170) 判定
      {
        v149 = *(uint32_t *)(pArg1 + 8668);  // 字段 nDollMode(pArg1+8668) 读写
        v150 = *(uint32_t *)(pArg1 + 8672);  // 字段 nPhase8672(pArg1+8672) 读写
        if ( v149 == v150 )  // v149 == v150 判定
          goto LABEL_462;  // 跳转 LABEL_462(收尾/共用分支)
        v151 = v149 + 1;
        *(uint32_t *)(pArg1 + 8668) = v151;  // 字段 nDollMode(pArg1+8668) 读写
        if ( v151 >= v150 )  // v151 >= v150 判定
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 32));  // 虚槽+196 → 物件非空判定
          sub_4926A0(*(uint32_t *)(pArg1 + 120));  // sub_4926A0 · 帧游标复位
          v163 = (uint32_t *)(pArg1 + 8680);
          for ( i = 2; i != 0; --i )  // 重复 2 次回挂(倒计数)
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *v163++);  // 虚槽+208 → 动画件回挂
        }
        else
        {
          sub_4926A0(v148);  // sub_4926A0 · 帧游标复位
          v152 = (uint32_t *)(pArg1 + 8680);
          for ( j = 2; j != 0; --j )  // 重复 2 次回挂(倒计数)
            sub_4926A0(*v152++);  // sub_4926A0 · 帧游标复位
          v154 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
          *(uint8_t *)(pArg1 + 8676) = 0;  // 字节字段 bPhase8676(pArg1+8676) 判定
          (*(void (/*thiscall*/ **)(int))(v154 + 352))(pArg1);  // 虚槽+352
          if ( *(uint32_t *)(pArg1 + 8668) == *(uint32_t *)(pArg1 + 8672) - 1 )  // 字段 nDollMode(pArg1+8668) 条件判定
          {
            *(float *)&nRand8 = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
            v450 = 29;
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
              v155 = 0;
            else
              v155 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust3.ani", 1);  // v155 = sub_431860 · 动画件构造
            sub_493D00(*(float *)(*(uint32_t *)(pArg1 + 120) + 164));  // sub_493D00 · 变速
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            v450 = 30;
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
              pObj3 = 0;
            else
              pObj3 = sub_44E1F0(v155, 1);  // pObj3 = sub_44E1F0 · CNRDPooledObject 构造
            v157 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_45FE80(v157, pObj3, 2, 0, pObj3, pArg1, 0);  // sub_45FE80 · 对象注册
            v158 = *(uint32_t *)pObj3;  // 缓存对象虚表基址
            v412 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int))(v158 + 148))(pObj3);  // 虚槽+148 → 位置/朝向写入
            v159 = *(uint32_t *)pObj3;  // 缓存对象虚表基址
            v160 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚槽+128 → 目标坐标y上界
            v161 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v160);  // 虚槽+124 → 目标坐标y下界
            v162 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v161);  // 虚槽+120 → 转发(对象+缓冲)
            (*(void (/*thiscall*/ **)(int, int))(v159 + 112))(pObj3, v162);  // 虚槽+112 → 坐标三元组写入
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 60))(pObj3, pArg1);  // 虚槽+60 → 对象销毁/释放
            sub_4A06D0(v412);  // sub_4A06D0 · 绑定目标对象并记录相对偏移
          }
        }
      }
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 13] 大状态 0x10（16）：★ 前方帧数 >= 1 时的动画推进（goto LABEL_463）──
    case 0x10:
      if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )  // 字段 pAnimObj(pArg1+120) 条件判定
      {
        if ( *(uint8_t *)(pArg1 + 8694) == 0 )  // 字节字段 +8694(pArg1+8694) 判定
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用
            pArg1,
            "JACKSPIKE_SWING",  // 事件/标签 JACKSPIKE_SWING
            -1,
            0,
            0);
          *(uint8_t *)(pArg1 + 8694) = 1;  // 字节字段 +8694(pArg1+8694) 判定
        }
        if ( *(uint8_t *)(pArg1 + 8693) != 0 )  // 字节字段 +8693(pArg1+8693) 判定
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)pArg1 + 876))(  // 调用
            pArg1,
            0,
            600,
            600,
            0,
            -8000,
            1);
          *(uint8_t *)(pArg1 + 8693) = 0;  // 字节字段 +8693(pArg1+8693) 判定
        }
      }
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 14] 大状态 0x12（18）：★ 二段拔枪 + 追瞄对象更新（GUN_DRAW1 / BOWGUN_DRAW1）──
    //   +8696==0 且 +8576==0 且帧 >=6 时同段 4 的双音效；
    //   +8700 对象 vt+724 判定与 vt+724 双路（1350-1370 行）用于追瞄/停瞄
    case 0x12:
      if ( *(uint32_t *)(pArg1 + 8696) == 0 && *(uint8_t *)(pArg1 + 8576) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 6 )  // 字段 nFrameCursorSnap(pArg1+8696) 条件判定
      {
        v448 = 15;
        v447 = 0;
        LOBYTE(v444[0]) = 0;  // 清短串 v444 首字节
        v165 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
        v450 = 31;
        v166 = (*(int (/*thiscall*/ **)(int))(v165 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
        if ( v166 >= 0 )  // v166 >= 0 判定(取值有效)
        {
          if ( v166 <= 3 )  // v166 <= 3 判定
          {
            sub_4015C0("GUN_DRAW1", 9u);  // 【std::string构造赋值】
          }
          else if ( v166 == 4 )  // 否则 v166==4 分支
          {
            sub_406D60("BOWGUN_DRAW1");  // sub_406D60 · std::string 从 C 串赋值
          }
        }
        (*(void (/*thiscall*/ **)(int, uint32_t *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, v444, -1, 0, 0);  // 虚槽+212 → vt+212
        *(uint8_t *)(pArg1 + 8576) = 1;  // 字节字段 nFadeAlpha(pArg1+8576) 判定
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_501490(v443);
      }
      pObj16 = *(uint32_t *)(pArg1 + 8700);  // 字段 bThrowInit(pArg1+8700) 读写
      if ( pObj16 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj16 + 724))(pObj16) != 0 )  // 虚槽+724 → 取值
      {
        pObj6 = *(uint32_t *)(pArg1 + 8716);  // 字段 +8716(pArg1+8716) 读写
        *(uint32_t *)(pArg1 + 8700) = 0;  // 字段 bThrowInit(pArg1+8700) 读写
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj6 + 76))(pObj6, 0);  // 虚槽+76
      }
      pObj35 = *(uint32_t *)(pArg1 + 8700);  // 字段 bThrowInit(pArg1+8700) 读写
      if ( pObj35 != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj35 + 308))(pObj35) != 0  // 调虚槽 +308：是否本地玩家
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8700) + 840))(*(uint32_t *)(pArg1 + 8700)) != 9
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8700) + 840))(*(uint32_t *)(pArg1 + 8700)) != 5 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(pArg1 + 8700) + 560))(  // 调用
          *(uint32_t *)(pArg1 + 8700),
          9,
          0,
          2,
          0);
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8700) + 564))(*(uint32_t *)(pArg1 + 8700));  // 字段 bThrowInit(pArg1+8700) 读写
      }
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 15] 大状态 0x14（20）：★ 连射收束 —— +8744++8748 时刻窗内的 MusketDust 大尘 ──
    //   v170 >= v171（两时刻之和）时播 MusketDustSmall5.ani + MusketDustLarge.ani
    case 0x14:
      *(float *)&v170 = COERCE_FLOAT(sub_4C0390(pArg1));  // sub_4C0390
      v171 = *(uint32_t *)(pArg1 + 8744) + *(uint32_t *)(pArg1 + 8748);  // 字段 nCountdown8744(pArg1+8744) 读写
      nRand8 = v170;
      if ( v170 >= v171 )  // v170 >= v171 判定
      {
        v172 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);  // 虚槽+120 → 转发(对象+缓冲)
        nRand = v172 + rand() % 200 - 100;  // 取伪随机数
        v174 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);  // 虚槽+124 → 目标坐标y下界
        nRand2 = v174 + rand() % 100 - 50;  // 取伪随机数
        nRand3 = rand() % 100;  // 取伪随机数
        v176 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);  // 虚槽+120 → 转发(对象+缓冲)
        v177 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
        v438 = nRand >= v176;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(v177 + 308))(pArg1) != 0 )  // 虚槽+308 → 是否本地玩家
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 8))(  // 调用
            *(uint32_t *)(pArg1 + 8216),
            *(uint32_t *)(pArg1 + 8220));
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 8216) + 40))(  // 调用
            *(uint32_t *)(pArg1 + 8216),
            nRand,
            nRand2,
            nRand3);
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 8216) + 104))(*(uint32_t *)(pArg1 + 8216), v438);  // 字段 nAtkActionType(pArg1+8216) 读写
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 12))(*(uint32_t *)(pArg1 + 8216), 0);  // 字段 nAtkActionType(pArg1+8216) 读写
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 112))(*(uint32_t *)(pArg1 + 8216), 0);  // 字段 nAtkActionType(pArg1+8216) 读写
          (*(void (/*thiscall*/ **)(uint32_t, int *))(**(uint32_t **)(pArg1 + 8216) + 92))(*(uint32_t *)(pArg1 + 8216), v421);  // 字段 nAtkActionType(pArg1+8216) 读写
          sub_5E5260(v421);  // sub_5E5260：清理临时缓冲
          (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 8216) + 104))(*(uint32_t *)(pArg1 + 8216), 4);  // 字段 nAtkActionType(pArg1+8216) 读写
        }
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1) == 2 )  // 虚槽+1096 → 枪种分派
        {
          // ── [段 16] 大状态 0x14 主体：连射尘效两段（Small5 → Large），时刻窗为 +8744++8748 ──
          sub_401710("Character/Gunner/Effect/Animation/MusketDust/MusketDustSmall5.ani");  // sub_401710 · std::string 复位并赋值 C 串
          v450 = 32;
          v434 = sub_44B6C0(284);  // v434 = sub_44B6C0 · CRT 一次性池初始化 2
          LOBYTE(v450) = 33;  // 把 33 低字节存入 v450(短串内联指针)
          if ( v434 != 0 )  // v434 != 0 判定
          {
            m = sub_42FCB0(228);  // m = sub_42FCB0 · CRT 一次性初始化
            LOBYTE(v450) = 34;  // 把 34 低字节存入 v450(短串内联指针)
            if ( m != 0 )  // m != 0 判定
            {
              LOBYTE(v178) = v444[0];  // 取 std::string v444 首字节(短串内联首个 char)
              if ( v448 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                v178 = v444;
              v179 = sub_431860((char)v178, 1);  // v179 = sub_431860 · 动画件构造
            }
            else
            {
              v179 = 0;
            }
            LOBYTE(v450) = 33;  // 把 33 低字节存入 v450(短串内联指针)
            pObj = sub_44E1F0(v179, 1);  // pObj = sub_44E1F0 · CNRDPooledObject 构造
          }
          else
          {
            pObj = 0;
          }
          v181 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
          LOBYTE(v450) = 32;  // 把 32 低字节存入 v450(短串内联指针)
          sub_45FE80(v181, pObj, 2, 0, pObj, pArg1, 1);  // sub_45FE80 · 对象注册
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 148))(pObj, v438);  // 虚槽+148 → 位置/朝向写入
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 112))(pObj, nRand, nRand2, 100);  // 虚槽+112 → 坐标三元组写入
          sub_406D60("Character/Gunner/Effect/Animation/MusketDust/MusketDustLarge.ani");  // sub_406D60 · std::string 从 C 串赋值
          v434 = sub_44B6C0(284);  // v434 = sub_44B6C0 · CRT 一次性池初始化 2
          LOBYTE(v450) = 35;  // 把 35 低字节存入 v450(短串内联指针)
          if ( v434 != 0 )  // v434 != 0 判定
          {
            m = sub_42FCB0(228);  // m = sub_42FCB0 · CRT 一次性初始化
            LOBYTE(v450) = 36;  // 把 36 低字节存入 v450(短串内联指针)
            if ( m != 0 )  // m != 0 判定
            {
              LOBYTE(v182) = v444[0];  // 取 std::string v444 首字节(短串内联首个 char)
              if ( v448 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                v182 = v444;
              v183 = sub_431860((char)v182, 1);  // v183 = sub_431860 · 动画件构造
            }
            else
            {
              v183 = 0;
            }
            LOBYTE(v450) = 35;  // 把 35 低字节存入 v450(短串内联指针)
            pObj9 = sub_44E1F0(v183, 1);  // pObj9 = sub_44E1F0 · CNRDPooledObject 构造
          }
          else
          {
            pObj9 = 0;
          }
          v185 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
          LOBYTE(v450) = 32;  // 把 32 低字节存入 v450(短串内联指针)
          sub_45FE80(v185, pObj9, 2, 0, pObj9, pArg1, 0);  // sub_45FE80 · 对象注册
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj9 + 148))(pObj9, v438);  // 虚槽+148 → 位置/朝向写入
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 112))(pObj9, nRand, nRand2, 100);  // 虚槽+112 → 坐标三元组写入
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_501490(v443);
        }
        if ( (uint8_t)sub_423340(pArg1 + 8348, szPassword) != 0 )  // sub_423340 · 串首比较判定
        {
          if ( *(uint32_t *)(pArg1 + 8372) < 0x10u )  // 字段 nDiffVal(pArg1+8372) 条件判定
            v186 = pArg1 + 8352;
          else
            v186 = *(uint32_t *)(pArg1 + 8352);  // 字段 nVtRet(pArg1+8352) 读写
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, v186, -1, 0, 0);  // 虚槽+212 → vt+212
        }
        *(float *)(pArg1 + 8744) = *(float *)&nRand8;  // 写内存
      }
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 17] 大状态 0x16（22）：★★ 本函数最大分支 —— 技能表现主表（约 235 行）──
    //   +8968/+9300 门控与帧 >=3 前置；+8516 技能号分 12·14 / 13·36 / 39 三组；
    //   12/14 支（1493-1633）走 LABEL_301；13/36 支（1634-1654）另一路；
    //   39 支（1655-1713）：+8968==0 且 +9428!=0 且 +200!=2 时 sub_431920 建件
    case 0x16:
      if ( *(uint32_t *)(pArg1 + 8968) == 0 && *(uint8_t *)(pArg1 + 9300) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 )  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用
          pArg1,
          "SUBWEAPON_GRAB",  // 事件/标签 SUBWEAPON_GRAB
          -1,
          0,
          0);
        *(uint8_t *)(pArg1 + 9300) = 1;  // 字节字段 +9300(pArg1+9300) 判定
      }
      v187 = *(uint32_t *)(pArg1 + 8516);  // 字段 f_2144(pArg1+8516) 读写
      if ( v187 == 12 || v187 == 14 )
      {
        if ( *(uint32_t *)(pArg1 + 8968) != 1 || *(uint8_t *)(pArg1 + 9301) != 0 && v187 != 14 )  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
          goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
        v197 = *(uint32_t *)(pArg1 + 9324);  // 字段 +9324(pArg1+9324) 读写
        if ( v197 != -1 && *(uint32_t *)(pArg1 + 9320) >= v197 )  // 字段 +9320(pArg1+9320) 条件判定
          goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
        v198 = sub_4C03D0(pArg1);
        v199 = *(uint32_t *)(pArg1 + 9316) + *(uint32_t *)(pArg1 + 9312);  // 字段 +9316(pArg1+9316) 读写
        v434 = v198;
        if ( v198 >= v199 )  // v198 >= v199 判定
        {
          v200 = *(uint32_t *)(pArg1 + 8516);  // 字段 f_2144(pArg1+8516) 读写
          *(float *)&v438 = 0.0;  // 写内存
          if ( v200 == 12 )  // v200 == 12 判定
          {
            nRand4 = rand() % 10 - 5;  // 取伪随机数
            nRand2 = rand() % 10 - 5;  // 取伪随机数
          }
          else
          {
            nRand4 = rand() % 10 - 5;  // 取伪随机数
            nRand5 = rand();  // 取伪随机数
            v202 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
            v203 = nRand5 % 6 - 3;
            nRand2 = v203;
            if ( (*(int (/*thiscall*/ **)(int))(v202 + 152))(pArg1) == 0 )  // 虚槽+152 → 取值(参数)
              v203 = -v203;
            v438 = v203;
          }
          v204 = 0;
          v442 = 15;
          v441[4] = 0;  // 技能号表 v441[4] = 0
          LOBYTE(v441[0]) = 0;  // 清短串 v441 首字节
          v205 = *(uint32_t *)(pArg1 + 8516) == 12;  // 字段 f_2144(pArg1+8516) 读写
          v450 = 37;
          if ( v205 )  // v205 为真则进入
          {
            nRand6 = rand() & 0x80000001;  // 取伪随机数
            v205 = nRand6 == 0;
            if ( nRand6 < 0 )  // nRand6 < 0 判定(无效值)
              v205 = (((uint8_t)nRand6 - 1) | 0xFFFFFFFE) == -1;
            v207 = "Character/Gunner/Effect/Animation/GatlingShoot1.ani";  // 播 动画 GatlingShoot1.ani
            if ( !v205 )  // v205 为假判定
              v207 = "Character/Gunner/Effect/Animation/GatlingShoot2.ani";  // 播 动画 GatlingShoot2.ani
          }
          else
          {
            nRand7 = rand() & 0x80000001;
            v208 = nRand7 == 0;
            if ( nRand7 < 0 )  // nRand7 < 0 判定(无效值)
              v208 = (((uint8_t)nRand7 - 1) | 0xFFFFFFFE) == -1;
            v207 = "Character/Gunner/Effect/Animation/AerialGatlingShoot1.ani";  // 播 动画 AerialGatlingShoot1.ani
            if ( !v208 )  // v208 为假判定
              v207 = "Character/Gunner/Effect/Animation/AerialGatlingShoot2.ani";  // 播 动画 AerialGatlingShoot2.ani
          }
          sub_406D60(v207);  // sub_406D60 · std::string 从 C 串赋值
          LOBYTE(v450) = 38;  // 把 38 低字节存入 v450(短串内联指针)
          if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 · CRT 一次性初始化
            v204 = sub_431860((char)v441, 1);  // v204 = sub_431860 · 动画件构造
          LOBYTE(v450) = 37;  // 把 37 低字节存入 v450(短串内联指针)
          *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
          LOBYTE(v450) = 39;  // 把 39 低字节存入 v450(短串内联指针)
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            v210 = nullptr;
          else
            v210 = (int *)sub_44E1F0(v204, 1);  // v210 = sub_44E1F0 · CNRDPooledObject 构造
          v211 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
          LOBYTE(v450) = 37;  // 把 37 低字节存入 v450(短串内联指针)
          sub_45FE80(v211, (int)v210, 2, 0, (int)v210, pArg1, 0);  // sub_45FE80 · 对象注册
          v212 = *v210;  // v212 = 取 v210 首 dword(对象虚表基址)
          v213 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
          (*(void (/*thiscall*/ **)(int *, int))(v212 + 148))(v210, v213);  // 虚槽+148 → 位置/朝向写入
          v214 = *v210;  // v214 = 取 v210 首 dword(对象虚表基址)
          v215 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚槽+128 → 目标坐标y上界
          v216 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, nRand2 + v215);  // 虚槽+124 → 目标坐标y下界
          v217 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, nRand4 + v216);  // 虚槽+120 → 转发(对象+缓冲)
          (*(void (/*thiscall*/ **)(int *, int))(v214 + 112))(v210, v438 + v217);  // 虚槽+112 → 坐标三元组写入
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚槽+308 → 是否本地玩家
          {
            v218 = *(uint32_t *)(pArg1 + 8516) != 12 ? 148 : 175;  // 字段 f_2144(pArg1+8516) 读写
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 )  // 虚槽+152 → 取值(参数)
              v219 = v218 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);  // 虚槽+120 → 转发(对象+缓冲)
            else
              v219 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - v218;  // 虚槽+120 → 转发(对象+缓冲)
            *(float *)&nRand8 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1));  // 虚槽+124 → 目标坐标y下界
            if ( *(uint32_t *)(pArg1 + 8516) == 12 )  // 字段 f_2144(pArg1+8516) 条件判定
              v220 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) + 57;  // 虚槽+128 → 目标坐标y上界
            else
              v220 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) + 155;  // 虚槽+128 → 目标坐标y上界
            (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 8216) + 40))(  // 调用
              *(uint32_t *)(pArg1 + 8216),
              v219 + v438,
              nRand8 + nRand4,
              v220 + nRand2);
            (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 8216) + 12))(  // 调用
              *(uint32_t *)(pArg1 + 8216),
              v434 - *(uint32_t *)(pArg1 + 9312) - *(uint32_t *)(pArg1 + 9316));
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 112))(*(uint32_t *)(pArg1 + 8216), 0);  // 字段 nAtkActionType(pArg1+8216) 读写
            (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(pArg1 + 8216) + 92))(*(uint32_t *)(pArg1 + 8216), v425);  // 字段 nAtkActionType(pArg1+8216) 读写
            sub_5E5260(v425);  // sub_5E5260：清理临时缓冲
          }
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用
            pArg1,
            "G_MACHINEGUNA",  // 事件/标签 G_MACHINEGUNA
            -1,
            0,
            0);
          v221 = *(uint32_t *)(pArg1 + 9320);  // 字段 +9320(pArg1+9320) 读写
          *(uint32_t *)(pArg1 + 9312) += *(uint32_t *)(pArg1 + 9316);  // 字段 +9312(pArg1+9312) 自增/更新
          *(uint32_t *)(pArg1 + 9320) = v221 + 1;  // 字段 +9320(pArg1+9320) 读写
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_501490(v440);
        }
        v222 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);  // 虚槽+120 → 转发(对象+缓冲)
        *(float *)&v223 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1));  // 虚槽+124 → 目标坐标y下界
        v224 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
        nRand8 = v223;
        v225 = (*(int (/*thiscall*/ **)(int))(v224 + 128))(pArg1);  // 虚槽+128 → 目标坐标y上界
        if ( *(uint32_t *)(pArg1 + 8516) == 12 )  // 字段 f_2144(pArg1+8516) 条件判定
        {
          v226 = ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 ? 77 : -77) + v222;  // 虚槽+152 → 取值(参数)
          v227 = v225 + 64;
        }
        else
        {
          v226 = ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 ? 79 : -79) + v222;  // 虚槽+152 → 取值(参数)
          v227 = v225 + 86;
        }
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 9328) + 40))(  // 调用
          *(uint32_t *)(pArg1 + 9328),
          v226,
          nRand8,
          v227);
        (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(pArg1 + 9328) + 92))(*(uint32_t *)(pArg1 + 9328), v445);  // 字段 +9328(pArg1+9328) 读写
        v450 = 40;
        sub_4600B0(*(void **)(pArg1 + 116), 2, 0, (int)v445);  // sub_4600B0：演播层注册
// ── [段 18] 大状态 0x16 之 12/14 支出口 LABEL_301 ──
LABEL_301:
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);  // sub_5E5260：清理临时缓冲
        goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
      }
      if ( v187 == 13 || v187 == 36 )
      {
        if ( *(uint32_t *)(pArg1 + 8968) != 1 || *(uint8_t *)(pArg1 + 9301) != 0 )  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
          goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 )  // 虚槽+152 → 取值(参数)
          v194 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 232;  // 虚槽+120 → 转发(对象+缓冲)
        else
          v194 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 232;  // 虚槽+120 → 转发(对象+缓冲)
        v195 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);  // 虚槽+124 → 目标坐标y下界
        v196 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚槽+128 → 目标坐标y上界
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 8216) + 40))(  // 调用
          *(uint32_t *)(pArg1 + 8216),
          v194,
          v195,
          v196 + 88);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 112))(*(uint32_t *)(pArg1 + 8216), 0);  // 字段 nAtkActionType(pArg1+8216) 读写
        (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(pArg1 + 8216) + 92))(*(uint32_t *)(pArg1 + 8216), v445);  // 字段 nAtkActionType(pArg1+8216) 读写
        v450 = 41;
        sub_4600B0(*(void **)(pArg1 + 116), 2, 0, (int)v445);  // sub_4600B0：演播层注册
        goto LABEL_301;  // 跳转 LABEL_301(收尾/共用分支)
      }
      if ( v187 == 39 && *(uint32_t *)(pArg1 + 8968) == 0 && *(uint8_t *)(pArg1 + 9428) != 0 && *(uint32_t *)(pArg1 + 200) != 2 )  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
      {
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3 && *(uint8_t *)(pArg1 + 9416) == 0 )  // 虚槽+200 → 取值比较
        {
          v188 = *(uint32_t *)(pArg1 + 9372);  // 字段 +9372(pArg1+9372) 读写
          *(uint8_t *)(pArg1 + 9416) = 1;  // 字节字段 +9416(pArg1+9416) 判定
          sub_4926A0(v188);  // sub_4926A0 · 帧游标复位
          sub_494240(1000, *(uint32_t *)(pArg1 + 9372));  // sub_494240 · 子链变换/重建
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用
            pArg1,
            "LASERGUN_CHARGE_LOOP",  // 事件/标签 LASERGUN_CHARGE_LOOP
            13,
            0,
            0);
        }
        if ( *(uint32_t *)(pArg1 + 9420) == 0 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 9424) )  // 【clock_now(clk)】
        {
          v189 = 0;
          v190 = (uint32_t *)(pArg1 + 9408);
          do
          {
            sub_4926A0(*v190);  // sub_4926A0 · 帧游标复位
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 调用
              pArg1,
              ++v189,
              *v190,
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(v190 - 2));  // 虚槽+208 → 动画件回挂
            ++v190;  // 递进计数 v190
          }
          while ( v189 < 2 );
          v191 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
          *(uint32_t *)(pArg1 + 9420) = 1;  // 字段 +9420(pArg1+9420) 读写
          (*(void (/*thiscall*/ **)(int, int))(v191 + 216))(pArg1, 13);  // 虚槽+216 → 全场广播
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 调用
            pArg1,
            "GHOSTSLASH_CHARGE_END",  // 事件/标签 GHOSTSLASH_CHARGE_END
            -1,
            0,
            0);
        }
        if ( *(uint32_t *)(pArg1 + 9420) == 1 )  // 字段 +9420(pArg1+9420) 条件判定
        {
          v192 = (uint32_t *)(pArg1 + 9408);
          if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 9408) + 170) != 0 )  // 字段 +9408(pArg1+9408) 条件判定
          {
            for ( k = 2; k != 0; --k )  // 重复 2 次回挂(倒计数)
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *v192++);  // 虚槽+208 → 动画件回挂
            *(uint8_t *)(*(uint32_t *)(pArg1 + 9372) + 160) = 0;  // 字段 +9372(pArg1+9372) 读写
            sub_493400(8);  // sub_493400 · 应用帧索引 a2
            sub_4926A0(*(uint32_t *)(pArg1 + 9376));  // sub_4926A0 · 帧游标复位
            sub_494240(1001, *(uint32_t *)(pArg1 + 9376));  // sub_494240 · 子链变换/重建
            *(uint32_t *)(pArg1 + 9420) = 2;  // 字段 +9420(pArg1+9420) 读写
          }
        }
      }
// ── [段 19] ★ LABEL_463：本帧公共尾入口（全部 case 汇合）──
//   前段（1716-1752）：状态 16(+8692) 或 22(+8516==14) 时对 +9344 对象做 vt+724/vt+308/vt+840/vt+560/vt+564 收束；
//   中段（1754-1815）：非本地主角直接 return；状态 8 支按 +8577 分型收尾（LABEL_496）；
//   后段（1832-1959）：按 +6556 状态号逐一做「武器/装填/瞄准」的帧长与动画收尾，
//   含状态 7（LABEL_510）/12/4/16/19/17/18 及 +8516 表驱动两条 do-while
LABEL_463:
      result = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( result == 16 && *(uint8_t *)(pArg1 + 8692) != 0 || result == 22 && *(uint32_t *)(pArg1 + 8516) == 14 )  // 字段 f_2144(pArg1+8516) 条件判定
      {
        pObj28 = *(uint32_t *)(pArg1 + 9344);  // 字段 +9344(pArg1+9344) 读写
        if ( pObj28 != 0 )  // pObj28 != 0 判定
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj28 + 724))(pObj28);  // 虚槽+724 → 取值
          if ( (uint8_t)result != 0 )  // result 非 0 判定
          {
            pObj7 = *(uint32_t *)(pArg1 + 9360);  // 字段 +9360(pArg1+9360) 读写
            *(uint32_t *)(pArg1 + 9344) = 0;  // 字段 +9344(pArg1+9344) 读写
            result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj7 + 76))(pObj7, 0);  // 虚槽+76
          }
        }
        pObj18 = *(uint32_t *)(pArg1 + 9344);  // 字段 +9344(pArg1+9344) 读写
        if ( pObj18 != 0 )  // pObj18 != 0 判定
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj18 + 308))(pObj18);  // 虚槽+308 → 是否本地玩家
          if ( (uint8_t)result != 0 )  // result 非 0 判定
          {
            result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 9344) + 840))(*(uint32_t *)(pArg1 + 9344));  // 字段 +9344(pArg1+9344) 读写
            if ( result != 9 )  // 结果!=9 分支
            {
              result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 9344) + 840))(*(uint32_t *)(pArg1 + 9344));  // 字段 +9344(pArg1+9344) 读写
              if ( result != 5 )  // 结果!=5 分支
              {
                (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(pArg1 + 9344) + 560))(  // 调用
                  *(uint32_t *)(pArg1 + 9344),
                  9,
                  0,
                  2,
                  0);
                result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 9344) + 564))(*(uint32_t *)(pArg1 + 9344));  // 字段 +9344(pArg1+9344) 读写
              }
            }
          }
        }
      }
      if ( dword_8F7C04 != pArg1 || *(uint32_t *)(pArg1 + 200) == 2 )  // 字段 nMainState(pArg1+200) 条件判定
        return result;
      if ( *(uint32_t *)(pArg1 + 6556) == 8 )  // 字段 nBigState(pArg1+6556) 条件判定
      {
        if ( sub_41A5E0(pArg1 + 8577) == 0 || sub_41A5E0(pArg1 + 8577) == 2 )  // sub_41A5E0 · crypt4byte 解密校验
        {
          v326 = *(uint32_t **)(pArg1 + 120);
          v327 = v326[11];
          nRand8 = v326[37];
          v328 = v327 != 0 ? (v326[12] - v327) / 88 : 0;
          if ( nRand8 == v328 - 1 )  // nRand8 == v328-1(末帧判定)
          {
            Block = nullptr;
            v447 = 0;
            v448 = 0;
            v450 = 55;
            *(float *)&nRand8 = COERCE_FLOAT(sub_41A5E0(pArg1 + 7028));  // sub_41A5E0 · crypt4byte 解密校验
            sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
            *(float *)&nRand8 = COERCE_FLOAT(sub_4C18E0(pArg1 + 8568, pArg1 + 8572));  // sub_4C18E0
            sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 8, v445, 0, 0);  // 虚槽+560
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_5E5260(v445);  // sub_5E5260：清理临时缓冲
          }
        }
        if ( sub_41A5E0(pArg1 + 8577) == 1 )  // sub_41A5E0 · crypt4byte 解密校验
        {
          if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8564)  // 【clock_now(clk)】
            && (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0  // sub_4BFBC0：列表登记与状态判定
            && *(uint32_t *)(pArg1 + 8516) != 26 )
          {
            m = 0;
            v329 = sub_41A5E0(pArg1 + 8544);  // v329 = sub_41A5E0 · crypt4byte 解密校验
            if ( v329 >= sub_41A5E0(pArg1 + 8228) - 1 )  // sub_41A5E0 · crypt4byte 解密校验
              m = 1;
            v330 = sub_41A5E0(pArg1 + 7028);  // v330 = sub_41A5E0 · crypt4byte 解密校验
            v448 = 0;
            v447 = 0;
            Block = nullptr;
            if ( v330 != 0 )  // v330 != 0 判定
            {
              v450 = 57;
              v331 = &m;
            }
            else
            {
              v450 = 56;
              sub_431230(&m);  // sub_431230 · uint32 vector push_back
              *(float *)&nRand8 = COERCE_FLOAT(sub_4C18E0(pArg1 + 8568, pArg1 + 8572));  // sub_4C18E0
              v331 = &nRand8;
            }
            sub_431230(v331);  // sub_431230 · uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 8, v445, 0, 0);  // 虚槽+560
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_5E5260(v445);
          }
          if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8592) )  // 【clock_now(clk)】
            goto LABEL_496;  // 跳转 LABEL_496(收尾/共用分支)
        }
        else if ( sub_41A5E0(pArg1 + 8577) == 3 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8592) )  // sub_41A5E0 · crypt4byte 解密校验
        {
          if ( *(uint32_t *)(pArg1 + 8516) == 47 )  // 字段 f_2144(pArg1+8516) 条件判定
          {
LABEL_496:
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
            goto LABEL_501;  // 跳转 LABEL_501(收尾/共用分支)
          }
          Block = nullptr;
          v447 = 0;
          v448 = 0;
          v450 = 58;
          *(float *)&nRand8 = COERCE_FLOAT(sub_41A5E0(pArg1 + 7028));  // sub_41A5E0 · crypt4byte 解密校验
          sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
          (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 8, v445, 0, 0);  // 虚槽+560
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_5E5260(v445);
        }
      }
LABEL_501:
      if ( *(uint32_t *)(pArg1 + 6556) == 7 )  // 字段 nBigState(pArg1+6556) 条件判定
      {
        v332 = *(uint32_t *)(pArg1 + 8616);  // 字段 bPhase8616(pArg1+8616) 读写
        if ( v332 != 0 )  // v332 != 0 判定
        {
          if ( (v332 == 1 || v332 == 2) && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8564) )  // 【clock_now(clk)】
          {
            v335 = sub_41A5E0(pArg1 + 8544);  // v335 = sub_41A5E0 · crypt4byte 解密校验
            if ( v335 >= sub_41A5E0(pArg1 + 8248) || (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 )  // sub_41A5E0 · crypt4byte 解密校验
              goto LABEL_510;  // 跳转 LABEL_510(收尾/共用分支)
          }
        }
        else
        {
          v333 = *(uint32_t *)(pArg1 + 120);  // 字段 pAnimObj(pArg1+120) 读写
          v334 = *(uint32_t *)(v333 + 148);  // 字段 +148(v333+148) 读写
          if ( v334 == sub_42FC90(v333) - 1 )  // sub_42FC90 · 88B 元素计数
LABEL_510:
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 7, 0, 0, 0);  // 虚槽+560
        }
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 12  // 字段 nBigState(pArg1+6556) 条件判定
        && *(uint32_t *)(pArg1 + 8648) != -1
        && sub_699000(pArg1 + 6560) > *(uint32_t *)(pArg1 + 8648) )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 3);  // 虚槽+1160 → 读技能表(变体)
        sub_47E440(0);
        byte_9A0358 = 0;
        *(uint32_t *)(pArg1 + 8648) = -1;  // 字段 nDistSolve(pArg1+8648) 读写
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 4 && *(uint32_t *)(pArg1 + 6832) == 2 )  // 字段 nBigState(pArg1+6556) 条件判定
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 988))(pArg1) != 0 )  // 虚槽+988
        {
          if ( *(uint32_t *)(pArg1 + 8664) != -1 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8664) )  // 【clock_now(clk)】
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 3);  // 虚槽+1160 → 读技能表(变体)
            sub_47E440(1);
            byte_9A0358 = 1;
            *(uint32_t *)(pArg1 + 8664) = -1;  // 字段 bAI8664(pArg1+8664) 读写
          }
        }
        else
        {
          v336 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 3);  // 虚槽+1160 → 读技能表(变体)
          if ( (uint8_t)sub_47DF30(v336) != 0 )  // sub_47DF30
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 3);  // 虚槽+1160 → 读技能表(变体)
            sub_47E440(0);
            byte_9A0358 = 0;
          }
        }
      }
      v337 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v337 == 0 || v337 == 11 || v337 == 12 || v337 == 4)  // 大状态 v337 ∈ {0,11...} 成组判定
        && (sub_4842B0(3, nullptr) != -1  // sub_4842B0：技能槽对象查询与结果收集
         || ((v338 = *(uint32_t *)(pArg1 + 6556)) == 12 || v338 == 4) && (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0)  // sub_4BFBC0：列表登记与状态判定
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 3) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 59;
        nRand8 = 3;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 15, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      v339 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v339 == 0 || v339 == 11)  // 大状态 v339 ∈ {0,11...} 成组判定
        && sub_4842B0(4, nullptr) != -1  // sub_4842B0：技能槽对象查询与结果收集
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 4) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 60;
        nRand8 = 4;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 16, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      v340 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v340 == 0 || v340 == 11 || v340 == 8)  // 大状态 v340 ∈ {0,11...} 成组判定
        && sub_4842B0(14, nullptr) != -1  // sub_4842B0：技能槽对象查询与结果收集
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 14) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 61;
        nRand8 = 14;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 16, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      // ── [段 20] 公共尾之中段：状态 16 的帧长维护（+8272/+8276 双分支与 LABEL_229 出口）──
      if ( *(uint32_t *)(pArg1 + 6556) == 16 )  // 字段 nBigState(pArg1+6556) 条件判定
      {
        if ( *(uint32_t *)(pArg1 + 8688) == 14 && *(uint8_t *)(pArg1 + 8692) != 0 )  // 字段 anThrowPlan2(pArg1+8688) 条件判定
        {
          if ( sub_699000(pArg1 + 6560) < 200 )  // 【clock_now(clk)】
            goto LABEL_553;  // 跳转 LABEL_553(收尾/共用分支)
          pObj19 = *(uint32_t *)(pArg1 + 9344);  // 字段 +9344(pArg1+9344) 读写
          if ( pObj19 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj19 + 724))(pObj19) == 0 )  // 虚槽+724 → 取值
          {
            Block = nullptr;
            v447 = 0;
            v448 = 0;
            v450 = 62;
            nRand8 = 14;
            sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
            *(float *)&nRand8 = 0.0;  // 写内存
            sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 22, v445, 0, 0);  // 虚槽+560
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_5E5260(v445);
            goto LABEL_553;  // 跳转 LABEL_553(收尾/共用分支)
          }
        }
        else if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) == 0 )  // 字段 pAnimObj(pArg1+120) 读写
        {
          goto LABEL_553;  // 跳转 LABEL_553(收尾/共用分支)
        }
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
      }
// ── [段 21] 公共尾之状态表驱动（一）：+6556 状态号 == 0/11/8 时的成组处理（五连段）──
//   LABEL_553 为汇合点；每段都做「状态判定 + vt+560/vt+252/vt+216 收束」
LABEL_553:
      v342 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v342 == 0 || v342 == 11 || v342 == 8)  // 大状态 v342 ∈ {0,11...} 成组判定
        && sub_4842B0(7, nullptr) != -1  // sub_4842B0：技能槽对象查询与结果收集
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 7) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 19, 0, 0, 0);  // 虚槽+560
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 19 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 字段 nBigState(pArg1+6556) 条件判定
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
      v343 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v343 == 0 || v343 == 11 || v343 == 8)  // 大状态 v343 ∈ {0,11...} 成组判定
        && sub_4842B0(6, nullptr) != -1  // sub_4842B0：技能槽对象查询与结果收集
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 6) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 17, 0, 0, 0);  // 虚槽+560
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 17 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 字段 nBigState(pArg1+6556) 条件判定
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
      if ( *(uint32_t *)(pArg1 + 6556) == 18 )  // 字段 nBigState(pArg1+6556) 条件判定
      {
        v344 = *(uint32_t *)(pArg1 + 8696);  // 字段 nFrameCursorSnap(pArg1+8696) 读写
        if ( v344 != 0 )  // v344 != 0 判定
        {
          if ( v344 == 1 )  // v344 == 1 判定
          {
            if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 12 )  // 字段 pAnimObj(pArg1+120) 条件判定
            {
              Block = nullptr;
              v447 = 0;
              v448 = 0;
              v205 = *(uint32_t *)(pArg1 + 8700) == 0;  // 字段 bThrowInit(pArg1+8700) 读写
              v450 = 64;
              if ( v205 || (v349 = sub_41A5E0(pArg1 + 8544), v350 = sub_41A5E0(pArg1 + 8290), nRand8 = 1, v349 >= v350) )  // sub_41A5E0 · crypt4byte 解密校验
                nRand8 = 2;
              sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
              (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 18, v445, 0, 0);  // 虚槽+560
              v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
              sub_5E5260(v445);
            }
          }
          else if ( v344 == 2 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 字段 pAnimObj(pArg1+120) 读写
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
          }
        }
        else
        {
          if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 && *(uint8_t *)(pArg1 + 8728) == 0 )  // 字段 pAnimObj(pArg1+120) 条件判定
          {
            v345 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 388))(pArg1, 0);  // 虚槽+388 → 攻击计算
            v346 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 6, v345);  // 虚槽+1140 → 读技能表
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 6, 1, v346);  // 虚槽+1160 → 读技能表(变体)
            v347 = sub_4AED90(v418, v419, v420, v421[0]);
            v348 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
            v421[0] = 0;  // 技能号表 v421[0] = 0
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(v348 + 580))(  // 调用
              pArg1,
              22207,
              v347,
              0,
              0,
              100,
              0,
              0);
            *(uint8_t *)(pArg1 + 8728) = 1;  // 字节字段 nSegThrCap8728(pArg1+8728) 判定
          }
          if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 8 )  // 字段 pAnimObj(pArg1+120) 条件判定
          {
            Block = nullptr;
            v447 = 0;
            v448 = 0;
            v450 = 63;
            nRand8 = 1;
            sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 18, v445, 0, 0);  // 虚槽+560
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_5E5260(v445);
          }
        }
      }
      // ── [段 22] 公共尾之全局表遍历：do-while 扫 &unk_791CD4 起，哨兵为 &CNRDActiveStatus RTTI 描述符 ──
      //   即编译期状态表边界（RTTI 名当哨兵是 IDA 常见还原手法）；循环内按 +6556 与 +1312 逐项判定
      v351 = (int *)&unk_791CD4;
      do
      {
        v352 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
        if ( (v352 == 0 || v352 == 11)  // 大状态 v352 ∈ {0,11...} 成组判定
          && sub_4842B0(*v351, nullptr) != -1  // sub_4842B0：技能槽对象查询与结果收集
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, *v351) != 0 )
        {
          Block = nullptr;
          v447 = 0;
          v448 = 0;
          nRand8 = *v351;  // nRand8 = 取 v351 首 dword(对象虚表基址)
          v450 = 65;
          sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
          (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 14, v445, 0, 0);  // 虚槽+560
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_5E5260(v445);
        }
        ++v351;  // 递进计数 v351
      }
      while ( (int)v351 < (int)&CNRDActiveStatus `RTTI Type Descriptor' );
      // ── [段 23] 公共尾之状态表驱动（二）：状态 0/11/8 与 0/11 的更多成组处理（六连段）──
      //   含状态 20 与 21（+120 对象帧 170 非 0）两支；v426=12 后 for m<5 循环（2220-2246）
      v353 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v353 == 0 || v353 == 11 || v353 == 8)  // 大状态 v353 ∈ {0,11...} 成组判定
        && sub_4842B0(5, nullptr) != -1  // sub_4842B0：技能槽对象查询与结果收集
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 5) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 66;
        nRand8 = 1;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 5;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 24, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      v354 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v354 == 0 || v354 == 11 || v354 == 8)  // 大状态 v354 ∈ {0,11...} 成组判定
        && sub_4842B0(20, nullptr) != -1  // sub_4842B0：技能槽对象查询与结果收集
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 5) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 67;
        nRand8 = 1;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 20;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 24, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      v355 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v355 == 0 || v355 == 11)  // 大状态 v355 ∈ {0,11...} 成组判定
        && sub_4842B0(47, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 47) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 68;
        nRand8 = 1;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 47;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 24, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      v356 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v356 == 0 || v356 == 11)  // 大状态 v356 ∈ {0,11...} 成组判定
        && sub_4842B0(53, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 53) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 69;
        nRand8 = 1;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 53;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 24, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      v357 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v357 == 0 || v357 == 11)  // 大状态 v357 ∈ {0,11...} 成组判定
        && sub_4842B0(11, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 11) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 70;
        *(float *)&nRand8 = 0.0;  // 写内存
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 11;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 24, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      v358 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v358 == 0 || v358 == 11)  // 大状态 v358 ∈ {0,11...} 成组判定
        && sub_4842B0(9, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 9) != 0 )
      {
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 71;
        nRand8 = rand() % 4;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        *(float *)&nRand8 = 0.0;  // 写内存
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 100;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 20, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_5E5260(v445);
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 20 )  // 字段 nBigState(pArg1+6556) 条件判定
      {
        if ( (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 )  // sub_4BFBC0 · 列表登记与状态判定
          sub_4C27D0(pArg1);
        v359 = *(uint32_t *)(pArg1 + 8732);  // 字段 bSegLatch8732(pArg1+8732) 读写
        v360 = 3;
        // ── [段 24] 公共尾之内层 switch(+8516)：技能号 13/36/39 收尾选型 ──
        switch ( v359 )
        {
          case 1:
            v360 = 8;
            break;  // 跳出本 switch(单 case 处理完)
          case 2:
            v360 = 13;
            break;  // 跳出本 switch(单 case 处理完)
          case 3:
            v360 = 18;
            break;  // 跳出本 switch(单 case 处理完)
          default:
            break;  // 跳出本 switch(单 case 处理完)
        }
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) >= v360 )  // 字段 pAnimObj(pArg1+120) 条件判定
        {
          *(float *)&nRand8 = sub_4C16F0(pArg1);  // sub_4C16F0
          v361 = sub_4C0390(pArg1);
          v15 = v361 < *(uint32_t *)(pArg1 + 8736);  // 字段 +8736(pArg1+8736) 读写
          v434 = v361;
          if ( v15 && (sub_699000(pArg1 + 8) < *(uint32_t *)(pArg1 + 8532) + 500 || *(float *)&nRand8 >= 1.0) )  // 【clock_now(clk)】
          {
            m = sub_423A80(100, 300, (uint64_t)((*(float *)&nRand8 - 2.0) * 1000.0), 8000);  // m = sub_423A80 · 同上 int 版
            Block = nullptr;
            v447 = 0;
            v448 = 0;
            v450 = 72;
            nRand8 = rand() % 4;
            sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
            sub_431230(&v434);  // sub_431230 · uint32 vector push_back
            sub_431230(&m);  // sub_431230 · uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 20, v445, 0, 0);  // 虚槽+560
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_5E5260(v445);
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
          }
        }
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 21 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 字段 nBigState(pArg1+6556) 条件判定
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
      v426 = 12;
      v427[0] = 13;  // 技能号表 v427[0] = 13
      v427[1] = 36;  // 技能号表 v427[1] = 36
      v427[2] = 39;  // 技能号表 v427[2] = 39
      v427[3] = 40;  // 技能号表 v427[3] = 40
      for ( m = 0; m < 5; ++m )  // 循环遍历
      {
        v362 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
        if ( v362 == 0 || v362 == 11 || v362 == 8 )
        {
          v363 = v427[m - 1];
          if ( sub_4842B0(v363, (void *)(pArg1 + 8116)) != -1  // sub_4842B0 · 技能槽对象查询与结果收集
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, v363) != 0 )
          {
            Block = nullptr;
            v447 = 0;
            v448 = 0;
            v450 = 73;
            nRand8 = v363;
            sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
            *(float *)&nRand8 = 0.0;  // 写内存
            sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 22, v445, 0, 0);  // 虚槽+560
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            if ( Block != nullptr )  // Block != nullptr 判定
              j__free(Block);  // 释放临时缓冲
            Block = nullptr;
            v447 = 0;
            v448 = 0;
          }
        }
      }
      if ( *(uint32_t *)(pArg1 + 6556) != 22 )  // 字段 nBigState(pArg1+6556) 条件判定
        goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
      // ── [段 25] 公共尾之 switch(+8516 技能号)：★ 收尾小表（LABEL_676/659/679/657/691 五个出口）──
      //   仅当 +6556 != 22 时进入；末尾按 v365（+120 对象帧 170==0）落 LABEL_658/697
      v364 = *(uint32_t *)(pArg1 + 8516);  // 字段 f_2144(pArg1+8516) 读写
      switch ( v364 )
      {
        case 40:
          if ( *(uint32_t *)(pArg1 + 8968) != 0 )  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
            goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
          goto LABEL_657;  // 跳转 LABEL_657(收尾/共用分支)
        case 39:
          if ( *(uint32_t *)(pArg1 + 8968) == 0  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
            && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0
            && (*(uint8_t *)(pArg1 + 9428) == 0 || (uint8_t)sub_4BFC10(pArg1 + 8116) == 0) )  // sub_4BFC10：全称判定
          {
            goto LABEL_659;  // 跳转 LABEL_659(收尾/共用分支)
          }
          goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
        case 12:
          if ( *(uint32_t *)(pArg1 + 8968) != 0 )  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
          {
            if ( *(uint8_t *)(pArg1 + 9301) == 0 )  // 字节字段 +9301(pArg1+9301) 判定
            {
              if ( (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 )  // sub_4BFBC0 · 列表登记与状态判定
                sub_4C27D0(pArg1);
              if ( sub_699000(pArg1 + 8) < *(uint32_t *)(pArg1 + 8532) + 1000 || sub_4C16F0(pArg1) >= 1.0 )  // 【clock_now(clk)】
              {
LABEL_676:
                if ( sub_4C03D0(pArg1) < *(uint32_t *)(pArg1 + 9304) )  // sub_4C03D0
                  goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
              }
LABEL_659:
              Block = nullptr;
              v447 = 0;
              v448 = 0;
              v450 = 74;
              sub_431230(pArg1 + 8516);  // sub_431230 · uint32 vector push_back
              nRand8 = 1;
              sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
              if ( *(uint32_t *)(pArg1 + 8516) == 39 && *(uint8_t *)(pArg1 + 9428) != 0 )  // 字段 f_2144(pArg1+8516) 条件判定
              {
                nRand8 = *(int *)(pArg1 + 9424);  // 字段 +9424(pArg1+9424) 判定
                v366 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
                if ( nRand8 >= v366 )  // nRand8 >= v366 判定
                  *(float *)&nRand8 = COERCE_FLOAT(sub_699000(pArg1 + 6560));  // sub_699000 · clock_now
                sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
              }
              (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 22, v445, 0, 0);  // 虚槽+560
              v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
              if ( Block != nullptr )  // Block != nullptr 判定
                j__free(Block);  // 释放临时缓冲
              goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
            }
            if ( sub_4C03D0(pArg1) < *(uint32_t *)(pArg1 + 9308) )  // sub_4C03D0
              goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
LABEL_679:
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
            goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
          }
LABEL_657:
          v365 = *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) == 0;  // 字段 pAnimObj(pArg1+120) 读写
          goto LABEL_658;  // 跳转 LABEL_658(收尾/共用分支)
        default:
          break;  // 跳出本 switch(单 case 处理完)
      }
      if ( v364 != 13 && v364 != 36 )
      {
        if ( v364 != 14 )  // v364 != 14 判定
          goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
        if ( *(uint32_t *)(pArg1 + 8968) == 0 )  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
          goto LABEL_657;  // 跳转 LABEL_657(收尾/共用分支)
        v367 = sub_4C03D0(pArg1);
        v368 = *(uint32_t *)(pArg1 + 9304);  // 字段 +9304(pArg1+9304) 读写
LABEL_691:
        if ( v367 < v368 )
          goto LABEL_697;  // 跳转 LABEL_697(收尾/共用分支)
        goto LABEL_679;  // 跳转 LABEL_679(收尾/共用分支)
      }
      if ( *(uint32_t *)(pArg1 + 8968) != 0 )  // 字段 nDmgCapCtx(pArg1+8968) 条件判定
      {
        if ( *(uint8_t *)(pArg1 + 9301) == 0 )  // 字节字段 +9301(pArg1+9301) 判定
        {
          if ( (uint8_t)sub_4BFC10(pArg1 + 8116) == 0 )  // sub_4BFC10 · 全称判定
            goto LABEL_659;  // 跳转 LABEL_659(收尾/共用分支)
          goto LABEL_676;  // 跳转 LABEL_676(收尾/共用分支)
        }
        v367 = sub_4C03D0(pArg1);
        v368 = *(uint32_t *)(pArg1 + 9308);  // 字段 +9308(pArg1+9308) 读写
        goto LABEL_691;  // 跳转 LABEL_691(收尾/共用分支)
      }
      v365 = *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) == 0;  // 字段 pAnimObj(pArg1+120) 读写
LABEL_658:
      if ( !v365 )  // v365 为假判定
        goto LABEL_659;  // 跳转 LABEL_659(收尾/共用分支)
LABEL_697:
      // ── [段 26] 公共尾之收结（一）：状态 0/11 与 23、0/11、25、0/11、0/11 五连段 ──
      //   每段为「状态 + 组件对象」的收尾组合（vt+1160/vt+560/vt+252 等）
      v369 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v369 == 0 || v369 == 11)  // 大状态 v369 ∈ {0,11...} 成组判定
        && sub_4842B0(15, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 15) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 23, 0, 0, 0);  // 虚槽+560
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 23 )  // 字段 nBigState(pArg1+6556) 条件判定
      {
        v433 = 0;
        nRand8 = sub_699000(pArg1 + 6560) - *(uint32_t *)(pArg1 + 9460);  // 【clock_now(clk)】
        v370 = (double)nRand8 * *(float *)(pArg1 + 9452) + *(float *)(pArg1 + 9456);
        *(float *)(pArg1 + 9456) = v370;  // 写内存
        if ( v372 == 0 )  // v372 == 0 判定
        {
          v373 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
          m = (uint64_t)v370;  // m = 取 v370(转指针/类型)
          *(float *)(pArg1 + 9456) = v370 - (double)m;  // 写内存
          if ( (int)(uint64_t)v370 > (*(int (/*thiscall*/ **)(int))(v373 + 752))(pArg1) )  // 虚槽+752
          {
            v374 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
            v433 = 1;
            m = (*(int (/*thiscall*/ **)(int))(v374 + 752))(pArg1);  // 虚槽+752
          }
          v375 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
          v376 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 752))(pArg1, 0);  // 虚槽+752
          (*(void (/*thiscall*/ **)(int, int))(v375 + 744))(pArg1, v376 - m);  // 虚槽+744
        }
        *(uint32_t *)(pArg1 + 9460) = sub_699000(pArg1 + 6560);  // sub_699000 · clock_now
        if ( (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 || sub_4842B0(15, nullptr) != -1 || v433 != 0 )  // sub_4BFBC0 · 列表登记与状态判定
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
        if ( sub_4842B0(32, nullptr) != -1 )  // sub_4842B0 · 技能槽对象查询与结果收集
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 32);  // 虚槽+1312
        if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8564) && (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 )  // 【clock_now(clk)】
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 23, 0, 0, 0);  // 虚槽+560
      }
      v377 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( v377 == 0 || v377 == 11 )
      {
        m = (int)"\x1B";
        do
        {
          v378 = *(int *)m;
          v434 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          if ( sub_4842B0(v378, nullptr) != -1 )  // sub_4842B0 · 技能槽对象查询与结果收集
          {
            if ( sub_4C1AF0(pArg1) >= 30 )  // sub_4C1AF0
            {
              v380 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528＝主管理器(消息/弹窗)
              v381 = sub_422E70(0);  // sub_422E70：存 CStringManager::getStr 取本地化串
              sub_43BEE0(v380, v381, -6567706, 0, -1);  // sub_43BEE0：【播报上屏】
              sub_4B07B0(pArg1);  // sub_4B07B0 · 启动 300 时长倒计时
              break;  // 跳出本 switch(单 case 处理完)
            }
            if ( v378 == 51 )  // v378 == 51 判定
            {
              v434 = 51;
              v378 = 28;
            }
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, v378) != 0 )  // 虚槽+1312
            {
              Block = nullptr;
              v447 = 0;
              v448 = 0;
              v450 = 75;
              nRand8 = v378;
              sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 )  // 虚槽+152 → 取值(参数)
                v379 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 30;  // 虚槽+120 → 转发(对象+缓冲)
              else
                v379 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 30;  // 虚槽+120 → 转发(对象+缓冲)
              nRand8 = v379;
              sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
              *(float *)&nRand8 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1));  // 虚槽+124 → 目标坐标y下界
              sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
              sub_431230(&v434);  // sub_431230 · uint32 vector push_back
              (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 25, v445, 0, 0);  // 虚槽+560
              v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
              if ( Block != nullptr )  // Block != nullptr 判定
                j__free(Block);  // 释放临时缓冲
              Block = nullptr;
              v447 = 0;
              v448 = 0;
            }
          }
          m += 4;  // m 累加 4
        }
        while ( m < (int)"Effect/Animation/ShootEffect/CrossShoot2.ani" );
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 25 && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 170) != 0 )  // 虚槽+200 → 取值比较
      {
        v382 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 80))(pArg1);  // 虚槽+80 → 读 4 字节
        v383 = sub_460230(v382);  // v383 = sub_460230 · 图标槽随机 id 分配
        v384 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
        *(uint32_t *)(pArg1 + 9480) = v383;  // 字段 +9480(pArg1+9480) 读写
        v385 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(v384 + 152))(  // 调虚槽 +152：取朝向
                 pArg1,
                 0,
                 0,
                 0,
                 v383,
                 0,
                 1,
                 0,
                 0);
        v386 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pArg1 + 376))(
                 pArg1,
                 *(uint32_t *)(pArg1 + 9468),
                 *(uint32_t *)(pArg1 + 9472),
                 *(uint32_t *)(pArg1 + 9476),
                 0,
                 v385);
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(v384 + 592))(pArg1, *(uint32_t *)(pArg1 + 9464), v386);  // 虚槽+592
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
      }
      v387 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v387 == 0 || v387 == 11)  // 大状态 v387 ∈ {0,11...} 成组判定
        && sub_4842B0(43, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 43) != 0 )
      {
        v388 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 43);  // 虚槽+1160 → 读技能表(变体)
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 76;
        *(float *)&nRand8 = 0.0;  // 写内存
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        *(float *)&nRand8 = 0.0;  // 写内存
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 43;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        v389 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 43);  // 虚槽+1140 → 读技能表
        if ( v389 == -1 )
          v389 = sub_41A5E0(v388 + 510);  // v389 = sub_41A5E0 · crypt4byte 解密校验
        *(float *)&nRand8 = COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(v388 + 316) + 14 * (v389 - 1)));  // sub_41A5E0 · crypt4byte 解密校验
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        *(float *)&nRand8 = COERCE_FLOAT(sub_47E9D0(0));  // sub_47E9D0
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 1;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 4;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 4;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        if ( Block != nullptr )  // Block != nullptr 判定
          j__free(Block);  // 释放临时缓冲
      }
      v390 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v390 == 0 || v390 == 11)  // 大状态 v390 ∈ {0,11...} 成组判定
        && sub_4842B0(45, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 45) != 0 )
      {
        v391 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 45);  // 虚槽+1160 → 读技能表(变体)
        Block = nullptr;
        v447 = 0;
        v448 = 0;
        v450 = 77;
        *(float *)&nRand8 = 0.0;  // 写内存
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        *(float *)&nRand8 = 0.0;  // 写内存
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 45;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        v392 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 45);  // 虚槽+1140 → 读技能表
        if ( v392 == -1 )
          v392 = sub_41A5E0(v391 + 510);  // v392 = sub_41A5E0 · crypt4byte 解密校验
        *(float *)&nRand8 = COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(v391 + 316) + 14 * (v392 - 1)));  // sub_41A5E0 · crypt4byte 解密校验
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        *(float *)&nRand8 = COERCE_FLOAT(sub_47E9D0(0));  // sub_47E9D0
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 1;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 4;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 4;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, v445, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        if ( Block != nullptr )  // Block != nullptr 判定
          j__free(Block);  // 释放临时缓冲
      }
      v393 = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      if ( (v393 == 0 || v393 == 11)  // 大状态 v393 ∈ {0,11...} 成组判定
        && sub_4842B0(50, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 50) != 0 )
      {
        v394 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 50);  // 虚槽+1160 → 读技能表(变体)
        v430 = nullptr;
        v431 = 0;
        v432 = 0;
        v450 = 78;
        *(float *)&nRand8 = 0.0;  // 写内存
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        *(float *)&nRand8 = 0.0;  // 写内存
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 50;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        v395 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 50);  // 虚槽+1140 → 读技能表
        if ( v395 == -1 )
          v395 = sub_41A5E0(v394 + 510);  // v395 = sub_41A5E0 · crypt4byte 解密校验
        *(float *)&nRand8 = COERCE_FLOAT(sub_41A5E0(*(uint32_t *)(v394 + 316) + 14 * (v395 - 1)));  // sub_41A5E0 · crypt4byte 解密校验
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        *(float *)&nRand8 = COERCE_FLOAT(sub_47E9D0(0));  // sub_47E9D0
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 1;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 4;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        nRand8 = 4;
        sub_431230(&nRand8);  // sub_431230 · uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, v429, 0, 0);  // 虚槽+560
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        if ( v430 != nullptr )  // v430 != nullptr 判定
          j__free(v430);  // 释放临时缓冲
        v430 = nullptr;
        v431 = 0;
        v432 = 0;
      }
      result = *(uint32_t *)(pArg1 + 6556);  // 字段 nBigState(pArg1+6556) 读写
      // ── [段 27] 公共尾之收结（二）：result 为 0 或 11 时的末段处理，随后 return result ──
      if ( result == 0 || result == 11 )
      {
        result = sub_4842B0(48, nullptr);  // result = sub_4842B0 · 技能槽对象查询与结果收集
        if ( result != -1 )
        {
          result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 48);  // 虚槽+1312
          if ( (uint8_t)result != 0 )  // result 非 0 判定
            return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 27, 0, 0, 0);  // 虚槽+560
        }
      }
      return result;
    // ── [段 28] 大状态 0x17（23）：★ 投掷/过肩（MusketDust + ReduceRevolverDelayUp）──
    //   vt+184/vt+188 取两值比对 vt+152 朝向判定；v438 为第三参（1 或 0.0 特例）；
    //   +9436 与 +9448 联合判定后（v234 与 v438 的 4 号特例）按 +8560 时刻播：
    //   MusketDustSmall1.ani + MusketDustLarge.ani + ReduceRevolverDelayUp.ani 三件；
    //   2737-2846 行为建件与挂接主体；goto LABEL_463
    case 0x17:
      v229 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 184))(pArg1);  // 虚槽+184 → 字符串/朝向写入
      v230 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 188))(pArg1);  // 虚槽+188 → 取尺寸
      if ( v229 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) )  // 虚槽+152 → 取值(参数)
      {
        v438 = 1;
      }
      else
      {
        v231 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
        if ( v229 == sub_432E50(v231) )  // sub_432E50 · 关系码对调映射
        {
          *(float *)&v438 = 0.0;  // 写内存
        }
        else if ( v230 == 4 )  // 否则 v230==4 分支
        {
          v438 = 4;
        }
        else
        {
          v232 = *(int *)(pArg1 + 9436);  // 字段 +9436(pArg1+9436) 判定
          v438 = 1;
          if ( v232 != 4 )  // v232 != 4 判定
            v438 = v232;
        }
      }
      v233 = 23;
      if ( v438 == 1 )  // v438 == 1 判定
      {
        v233 = 24;
      }
      else if ( *(float *)&v438 == 0.0 )
      {
        v233 = 25;
      }
      if ( *(uint32_t *)(pArg1 + 9448) != -1  // 字段 +9448(pArg1+9448) 条件判定
        && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 9448) + 100  // 【clock_now(clk)】
        && sub_699000(pArg1 + 6560) < *(uint32_t *)(pArg1 + 9448) + 300 )  // 【clock_now(clk)】
      {
        v233 += *(uint32_t *)(pArg1 + 9440) + 2 * *(uint32_t *)(pArg1 + 9440) + 3;  // 字段 +9440(pArg1+9440) 读写
      }
      v234 = *(uint32_t *)(pArg1 + 9436);  // 字段 +9436(pArg1+9436) 读写
      if ( v438 == v234 )  // v438 == v234 判定
      {
        v237 = *(uint32_t *)(pArg1 + 6216);  // 字段 pSubCtx(pArg1+6216) 读写
        v238 = *(uint32_t *)(pArg1 + 120);  // 字段 pAnimObj(pArg1+120) 读写
        v239 = 4 * v233;
        if ( v238 != *(uint32_t *)(v237 + v239) )
        {
          *(float *)&v240 = COERCE_FLOAT(sub_4910A0(v238));  // sub_4910A0 · 沿 +212 同步源链上溯，返回链尾对象的累计播放时刻
          v241 = *(uint32_t *)pArg1;  // 缓存对象虚表基址
          nRand8 = v240;
          (*(void (/*thiscall*/ **)(int, uint32_t))(v241 + 196))(pArg1, *(uint32_t *)(v237 + v239));  // 虚槽+196 → 物件非空判定
          sub_493A60(*(uint32_t *)(pArg1 + 120), nRand8);  // sub_493A60 · 时间推进包装
        }
      }
      else if ( v234 == 4 || v438 == 4 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4 * v233));  // 虚槽+196 → 物件非空判定
        sub_4926A0(*(uint32_t *)(pArg1 + 120));  // sub_4926A0 · 帧游标复位
        *(float *)(pArg1 + 9436) = *(float *)&v438;  // 写内存
      }
      else
      {
        v235 = *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148);  // 字段 pAnimObj(pArg1+120) 读写
        v236 = 7 - v235 + 1;
        if ( v234 != 1 )  // v234 != 1 判定
          v236 = 7 - v235 + 7;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4 * v233));  // 虚槽+196 → 物件非空判定
        sub_4AECE0(v236 % 8);
        *(float *)(pArg1 + 9436) = *(float *)&v438;  // 写内存
      }
      if ( *(uint32_t *)(pArg1 + 8560) != -1 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8560) )  // 【clock_now(clk)】
      {
        pObj5 = *(uint32_t *)(pArg1 + 8216);  // 字段 nAtkActionType(pArg1+8216) 读写
        *(uint32_t *)(pArg1 + 9440) = 1 - *(uint32_t *)(pArg1 + 9440);  // 字段 +9440(pArg1+9440) 读写
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj5 + 8))(pObj5, *(uint32_t *)(pArg1 + 8220));  // 虚槽+8
        nRand4 = 0;
        nRand2 = 0;
        *(float *)&v438 = 0.0;  // 写内存
        v243 = sub_4C46B0(0);
        if ( v243 != 0 )  // v243 != 0 判定
        {
          pObj22 = *(uint32_t *)(pArg1 + 8216);  // 字段 nAtkActionType(pArg1+8216) 读写
          v245 = *(uint32_t *)pObj22;  // 缓存对象虚表基址
          m = pObj22;
          v413 = (*(int (/*thiscall*/ **)(int))(v245 + 52))(pObj22);  // 虚槽+52 → 归属坐标y
          v400 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj22 + 48))(pObj22);  // 虚槽+48 → 归属坐标x
          v246 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj22 + 44))(pObj22);  // 虚槽+44
          sub_4C17C0(&nRand4, &nRand2, &v438, v246, v400, v413);
          nRand8 = *(int *)(*(uint32_t *)(pArg1 + 120) + 164);  // 字段 pAnimObj(pArg1+120) 读写
          sub_493D00(*(float *)&nRand8);  // sub_493D00 · 变速
          *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
          v450 = 42;
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            pObj27 = 0;
          else
            pObj27 = sub_44E1F0(v243, 1);  // pObj27 = sub_44E1F0 · CNRDPooledObject 构造
          v248 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_45FE80(v248, pObj27, 2, 0, pObj27, pArg1, 0);  // sub_45FE80 · 对象注册
          v249 = *(uint32_t *)pObj27;  // 缓存对象虚表基址
          v414 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
          (*(void (/*thiscall*/ **)(int))(v249 + 148))(pObj27);  // 虚槽+148 → 位置/朝向写入
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj27 + 112))(pObj27, nRand4, nRand2, v438);  // 虚槽+112 → 坐标三元组写入
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj27 + 60))(pObj27, pArg1);  // 虚槽+60 → 对象销毁/释放
          sub_4A06D0(v414);  // sub_4A06D0 · 绑定目标对象并记录相对偏移
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚槽+308 → 是否本地玩家
        {
          sub_4C17C0(&nRand4, &nRand2, &v438, 47, 0, 119);
          if ( *(uint32_t *)(pArg1 + 9440) == 1 )  // 字段 +9440(pArg1+9440) 条件判定
          {
            ++nRand2;  // 递进计数 nRand2
            ++v438;  // 递进计数 v438
          }
          else
          {
            nRand2 -= 2;
            v438 -= 2;
          }
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 8216) + 40))(  // 调用
            *(uint32_t *)(pArg1 + 8216),
            nRand4,
            nRand2,
            v438);
          v250 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216));  // 字段 nAtkActionType(pArg1+8216) 读写
          sub_4B2580(pArg1 + 8568, pArg1 + 8572, pArg1, nRand4, nRand2, v438, 0, *(uint32_t *)(v250 + 76), 4, 4, -1, 480, 34, 34, 34);  // sub_4B2580 · 目标搜索 + 瞄准角输出
          v251 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216));  // 字段 nAtkActionType(pArg1+8216) 读写
          *(uint32_t *)(v251 + 72) += *(uint32_t *)(pArg1 + 8568);  // 字段 +72(v251+72) 自增/更新
          v252 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216));  // 字段 nAtkActionType(pArg1+8216) 读写
          *(uint32_t *)(v252 + 76) += *(uint32_t *)(pArg1 + 8572);  // 字段 +76(v252+76) 自增/更新
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 12))(*(uint32_t *)(pArg1 + 8216), 0);  // 字段 nAtkActionType(pArg1+8216) 读写
          v253 = **(uint32_t **)(pArg1 + 8216);
          v254 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
          (*(void (/*thiscall*/ **)(uint32_t, int))(v253 + 112))(*(uint32_t *)(pArg1 + 8216), v254 == 3 ? pArg1 : 0);  // 字段 nAtkActionType(pArg1+8216) 读写
          (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(pArg1 + 8216) + 92))(*(uint32_t *)(pArg1 + 8216), v424);  // 字段 nAtkActionType(pArg1+8216) 读写
          sub_5E5260(v424);
        }
        v255 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
        if ( v255 != 0 )  // v255 != 0 判定
        {
          if ( v255 == 1 )  // v255 == 1 判定
          {
            sub_4C17C0(&nRand4, &nRand2, &v438, 67, 0, 123);
            pObj12 = dword_8F830C;  // dword_8F830C＝专用件
            v261 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) == 0;  // 虚槽+152 → 取值(参数)
            v262 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 28))(pObj12);  // 虚槽+28
            v416 = v438;
            nRand45 = nRand4;
            nRand24 = nRand2;
            *(uint8_t *)(v262 + 84) = v261;  // 字节字段 +84(v262+84) 判定
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj12 + 40))(pObj12, nRand45, nRand24, v416);  // 虚槽+40 → 条件查询(273等)
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj12 + 12))(pObj12, 0);  // 虚槽+12
            (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj12 + 92))(pObj12, v445);  // 虚槽+92 → 读剩余(返回长度)
            v264 = *(void **)(pArg1 + 116);
            v450 = 45;
            sub_4600B0(v264, 2, 0, (int)v445);  // sub_4600B0：演播层注册
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_5E5260(v445);
          }
          else if ( v255 == 2 )  // 否则 v255==2 分支
          {
            sub_4C17C0(&nRand4, &nRand2, &v438, 49, 0, 127);
            // ── [段 29] 大状态 0x17 主体：投掷三连件（Small1 → Large → ReduceRevolverDelayUp）──
            sub_401710("Character/Gunner/Effect/Animation/MusketDust/MusketDustSmall1.ani");  // sub_401710 · std::string 复位并赋值 C 串
            v450 = 46;
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            LOBYTE(v450) = 47;  // 把 47 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            {
              pObj31 = 0;
            }
            else
            {
              v434 = sub_42FCB0(228);  // v434 = sub_42FCB0 · CRT 一次性初始化
              LOBYTE(v450) = 48;  // 把 48 低字节存入 v450(短串内联指针)
              if ( v434 != 0 )  // v434 != 0 判定
              {
                LOBYTE(v265) = v441[0];  // 取 std::string v441 首字节(短串内联首个 char)
                if ( v442 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                  v265 = v441;
                v266 = sub_431860((char)v265, 1);  // v266 = sub_431860 · 动画件构造
              }
              else
              {
                v266 = 0;
              }
              LOBYTE(v450) = 47;  // 把 47 低字节存入 v450(短串内联指针)
              pObj31 = sub_44E1F0(v266, 1);  // pObj31 = sub_44E1F0 · CNRDPooledObject 构造
            }
            v268 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            LOBYTE(v450) = 46;  // 把 46 低字节存入 v450(短串内联指针)
            sub_45FE80(v268, pObj31, 2, 0, pObj31, pArg1, 1);  // sub_45FE80 · 对象注册
            v269 = *(uint32_t *)pObj31;  // 缓存对象虚表基址
            v270 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int, int))(v269 + 148))(pObj31, v270);  // 虚槽+148 → 位置/朝向写入
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj31 + 112))(pObj31, nRand4, nRand2, v438);  // 虚槽+112 → 坐标三元组写入
            sub_4C17C0(&nRand4, &nRand2, &v438, 9, 0, 127);
            sub_406D60("Character/Gunner/Effect/Animation/MusketDust/MusketDustLarge.ani");  // sub_406D60 · std::string 从 C 串赋值
            *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
            LOBYTE(v450) = 49;  // 把 49 低字节存入 v450(短串内联指针)
            if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            {
              pObj25 = 0;
            }
            else
            {
              v434 = sub_42FCB0(228);  // v434 = sub_42FCB0 · CRT 一次性初始化
              LOBYTE(v450) = 50;  // 把 50 低字节存入 v450(短串内联指针)
              if ( v434 != 0 )  // v434 != 0 判定
              {
                LOBYTE(v271) = v441[0];  // 取 std::string v441 首字节(短串内联首个 char)
                if ( v442 < 0x10 )  // SSO 容量判定(<0x10 短串走内联缓冲)
                  v271 = v441;
                v272 = sub_431860((char)v271, 1);  // v272 = sub_431860 · 动画件构造
                LOBYTE(v450) = 49;  // 把 49 低字节存入 v450(短串内联指针)
                pObj25 = sub_44E1F0(v272, 1);  // pObj25 = sub_44E1F0 · CNRDPooledObject 构造
              }
              else
              {
                LOBYTE(v450) = 49;  // 把 49 低字节存入 v450(短串内联指针)
                pObj25 = sub_44E1F0(0, 1);  // pObj25 = sub_44E1F0 · CNRDPooledObject 构造
              }
            }
            v274 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
            LOBYTE(v450) = 46;  // 把 46 低字节存入 v450(短串内联指针)
            sub_45FE80(v274, pObj25, 2, 0, pObj25, pArg1, 0);  // sub_45FE80 · 对象注册
            v275 = *(uint32_t *)pObj25;  // 缓存对象虚表基址
            v276 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
            (*(void (/*thiscall*/ **)(int, int))(v275 + 148))(pObj25, v276);  // 虚槽+148 → 位置/朝向写入
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj25 + 112))(pObj25, nRand4, nRand2, v438);  // 虚槽+112 → 坐标三元组写入
            v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_501490(v440);
          }
        }
        else if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 22) > 0 )  // 虚槽+1140 → 读技能表
        {
          sub_4C17C0(&nRand4, &nRand2, &v438, 0, 0, 0);
          *(float *)&nRand8 = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
          v450 = 43;
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            v256 = 0;
          else
            v256 = sub_431860((char)"Character/Gunner/Effect/Animation/ReduceRevolverDelayUp.ani", 1);  // v256 = sub_431860 · 动画件构造
          nRand8 = *(int *)(*(uint32_t *)(pArg1 + 120) + 164);  // 字段 pAnimObj(pArg1+120) 读写
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_493D00(*(float *)&nRand8);  // sub_493D00 · 变速
          *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
          v450 = 44;
          if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
            pObj30 = 0;
          else
            pObj30 = sub_44E1F0(v256, 1);  // pObj30 = sub_44E1F0 · CNRDPooledObject 构造
          v258 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
          v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_45FE80(v258, pObj30, 2, 0, pObj30, pArg1, 0);  // sub_45FE80 · 对象注册
          v259 = *(uint32_t *)pObj30;  // 缓存对象虚表基址
          v415 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
          (*(void (/*thiscall*/ **)(int))(v259 + 148))(pObj30);  // 虚槽+148 → 位置/朝向写入
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj30 + 112))(pObj30, nRand4, nRand2, v438);  // 虚槽+112 → 坐标三元组写入
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj30 + 60))(pObj30, pArg1);  // 虚槽+60 → 对象销毁/释放
          sub_4A06D0(v415);  // sub_4A06D0 · 绑定目标对象并记录相对偏移
        }
        if ( (uint8_t)sub_423340(pArg1 + 8348, szPassword) != 0 )  // sub_423340 · 串首比较判定
        {
          if ( *(uint32_t *)(pArg1 + 8372) < 0x10u )  // 字段 nDiffVal(pArg1+8372) 条件判定
            v277 = pArg1 + 8352;
          else
            v277 = *(uint32_t *)(pArg1 + 8352);  // 字段 nVtRet(pArg1+8352) 读写
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, v277, -1, 0, 0);  // 虚槽+212 → vt+212
        }
        *(uint32_t *)(pArg1 + 9448) = *(uint32_t *)(pArg1 + 8560);  // 字段 +9448(pArg1+9448) 读写
        *(uint32_t *)(pArg1 + 8560) = -1;  // 字段 +8560(pArg1+8560) 读写
      }
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 30] 大状态 0x1A（26）：★ 武器 39/40 且 vt+184==4 时直接跳公共尾（无演出）──
    case 0x1A:
      v228 = *(uint32_t *)(pArg1 + 8516);  // 字段 f_2144(pArg1+8516) 读写
      if ( (v228 == 39 || v228 == 40) && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 184))(pArg1) == 4 )  // 虚槽+184 → 字符串/朝向写入
        goto LABEL_462;  // 跳转 LABEL_462(收尾/共用分支)
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 31] 大状态 0x1B（27）：★ 十字射击（CrossShoot1/2.ani）—— 时刻到点且目标帧归零 ──
    //   sub_699000 >= +8560 且 +120 对象帧 148==0；建 CrossShoot1.ani（2962）与 CrossShoot2.ani（2994）两件；
    //   LABEL_462：再按 +8592 时刻做第二段；goto LABEL_463
    case 0x1B:
      if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8560) && *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) == 0 )  // 【clock_now(clk)】
      {
        nRand2 = 0;
        v428 = 0;
        nRand4 = 0;
        sub_4C17C0(&nRand2, &v428, &nRand4, 87, 0, 112);
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚槽+308 → 是否本地玩家
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 8))(  // 调用
            *(uint32_t *)(pArg1 + 8216),
            *(uint32_t *)(pArg1 + 8220));
          nRand25 = nRand2;
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(pArg1 + 8216) + 40))(  // 调用
            *(uint32_t *)(pArg1 + 8216),
            nRand2,
            v428,
            nRand4);
          v279 = **(uint32_t **)(pArg1 + 8216);
          v280 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1);  // 虚槽+1096 → 枪种分派
          (*(void (/*thiscall*/ **)(uint32_t, int))(v279 + 112))(*(uint32_t *)(pArg1 + 8216), v280 == 3 ? pArg1 : 0);  // 字段 nAtkActionType(pArg1+8216) 读写
          v281 = pArg1 + 8318;
          if ( sub_41A5E0(pArg1 + 8318) == 1 )  // sub_41A5E0 · crypt4byte 解密校验
          {
            m = 60;
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 48);  // 虚槽+1160 → 读技能表(变体)
            m = sub_47E9D0(2) / 2;  // sub_47E9D0：收招/结束例程
          }
          *(float *)&nRand8 = 0.0;  // 写内存
          if ( sub_41A5E0(pArg1 + 8318) > 0 )  // sub_41A5E0 · crypt4byte 解密校验
          {
            v282 = (double)m;  // v282 = 取 m(转指针/类型)
            m = 0;
            *(float *)&v438 = v282;  // 写内存
            while ( 1 )
            {
              v283 = sub_41A5E0(v281);  // v283 = sub_41A5E0 · crypt4byte 解密校验
              v284 = m / v283;
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1096))(pArg1) == 3 )  // 虚槽+1096 → 枪种分派
              {
                v285 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 ? nRand25 - 70 : nRand25 + 70;  // 虚槽+152 → 取值(参数)
                v286 = *(int **)(pArg1 + 8216);
                v434 = v285;
                v287 = *v286;  // v287 = 取 v286 首 dword(对象虚表基址)
                v288 = sub_4053E0(v284);  // v288 = sub_4053E0 · sin 查表
                v417 = (uint64_t)(v288 * *(float *)&v438 + (double)nRand4);
                v289 = sub_405400(v284);  // v289 = sub_405400 · cos 查表
                (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int))(v287 + 40))(  // 调用
                  *(uint32_t *)(pArg1 + 8216),
                  v434,
                  (uint64_t)(v289 * (double)dword_7930D4 * *(float *)&v438 * 0.0099999998 + (double)v428),  // 常量 0.01f
                  v417);
              }
              else
              {
                v290 = *(int **)(pArg1 + 8216);
                v291 = sub_405400(v284);  // v291 = sub_405400 · cos 查表
                v292 = *v290;  // v292 = 取 v290 首 dword(对象虚表基址)
                v434 = (uint64_t)(v291 * *(float *)&v438);
                v293 = (*(int (/*thiscall*/ **)(int *))(v292 + 28))(v290);  // 虚槽+28
                *(uint32_t *)(v293 + 72) = v434;  // 字段 +72(v293+72) 读写
                pObj13 = *(uint32_t *)(pArg1 + 8216);  // 字段 nAtkActionType(pArg1+8216) 读写
                v295 = sub_4053E0(v284);  // v295 = sub_4053E0 · sin 查表
                v296 = (uint64_t)(v295 * *(float *)&v438);
                *(uint32_t *)((*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pObj13 + 28))(
                              pObj13,
                              (uint64_t)(v295 * *(float *)&v438) >> 32)
                          + 76) = v296;
                v297 = (int *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216))  // 字段 nAtkActionType(pArg1+8216) 读写
                             + 72);
                v298 = (uint64_t)((double)*v297 + (double)*v297);
                *v297 = v298;  // 写内存
                if ( *(int *)((*(int (/*fastcall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(
                                *(uint32_t *)(pArg1 + 8216),
                                HIDWORD(v298))
                            + 76) > 0 )
                {
                  v299 = (int *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8216) + 28))(*(uint32_t *)(pArg1 + 8216))  // 字段 nAtkActionType(pArg1+8216) 读写
                               + 76);
                  *v299 = (uint64_t)((double)*v299 * 0.30000001);  // 写内存
                }
              }
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8216) + 12))(*(uint32_t *)(pArg1 + 8216), 0);  // 字段 nAtkActionType(pArg1+8216) 读写
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t *))(**(uint32_t **)(pArg1 + 8216) + 92))(*(uint32_t *)(pArg1 + 8216), v427);  // 字段 nAtkActionType(pArg1+8216) 读写
              sub_5E5260(v427);
              v281 = pArg1 + 8318;
              v300 = ++nRand8;
              m += 360;  // m 累加 360
              if ( v300 >= sub_41A5E0(pArg1 + 8318) )  // sub_41A5E0 · crypt4byte 解密校验
                break;  // 跳出本 switch(单 case 处理完)
              nRand25 = nRand2;
            }
          }
        }
        *(float *)&nRand8 = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
        v450 = 51;
        if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
        {
          v302 = 0;
        }
        else
        {
          if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // 字段 nAnimPoolCap(pArg1+384) 条件判定
            LOBYTE(v301) = pArg1 + 108;
          else
            v301 = *(uint32_t *)(pArg1 + 364);  // 字段 pAnimPool(pArg1+364) 读写
          v302 = sub_431920(v301, (char)"Effect/Animation/ShootEffect/CrossShoot1.ani", 1);  // v302 = sub_431920 · 动画件构造
        }
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
        v450 = 52;
        if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
          v303 = nullptr;
        else
          v303 = (int *)sub_44E1F0(v302, 1);  // v303 = sub_44E1F0 · CNRDPooledObject 构造
        v304 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_45FE80(v304, (int)v303, 2, 0, (int)v303, pArg1, 0);  // sub_45FE80 · 对象注册
        v305 = *v303;  // v305 = 取 v303 首 dword(对象虚表基址)
        v306 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
        (*(void (/*thiscall*/ **)(int *, int))(v305 + 148))(v303, v306);  // 虚槽+148 → 位置/朝向写入
        v307 = *v303;  // v307 = 取 v303 首 dword(对象虚表基址)
        v308 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚槽+128 → 目标坐标y上界
        v309 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v308);  // 虚槽+124 → 目标坐标y下界
        v310 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v309);  // 虚槽+120 → 转发(对象+缓冲)
        (*(void (/*thiscall*/ **)(int *, int))(v307 + 112))(v303, v310);  // 虚槽+112 → 坐标三元组写入
        *(float *)&nRand8 = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
        v450 = 53;
        if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
        {
          v312 = 0;
        }
        else
        {
          if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // 字段 nAnimPoolCap(pArg1+384) 条件判定
            LOBYTE(v311) = pArg1 + 108;
          else
            v311 = *(uint32_t *)(pArg1 + 364);  // 字段 pAnimPool(pArg1+364) 读写
          v312 = sub_431920(v311, (char)"Effect/Animation/ShootEffect/CrossShoot2.ani", 1);  // v312 = sub_431920 · 动画件构造
        }
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        *(float *)&nRand8 = COERCE_FLOAT(sub_44B6C0(284));  // sub_44B6C0 · CRT 一次性池初始化 2
        v450 = 54;
        if ( *(float *)&nRand8 == 0.0 )  // 浮点 nRand8 为 0 判定(未取到参)
          v313 = nullptr;
        else
          v313 = (int *)sub_44E1F0(v312, 1);  // v313 = sub_44E1F0 · CNRDPooledObject 构造
        v314 = *(uint32_t *)(pArg1 + 116);  // 字段 f_0074(pArg1+116) 读写
        v450 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        sub_45FE80(v314, (int)v313, 2, 0, (int)v313, pArg1, 0);  // sub_45FE80 · 对象注册
        v315 = *v313;  // v315 = 取 v313 首 dword(对象虚表基址)
        v316 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚槽+152 → 取值(参数)
        (*(void (/*thiscall*/ **)(int *, int))(v315 + 148))(v313, v316);  // 虚槽+148 → 位置/朝向写入
        v317 = *v313;  // v317 = 取 v313 首 dword(对象虚表基址)
        v318 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚槽+128 → 目标坐标y上界
        v319 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v318);  // 虚槽+124 → 目标坐标y下界
        v320 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v319);  // 虚槽+120 → 转发(对象+缓冲)
        (*(void (/*thiscall*/ **)(int *, int))(v317 + 112))(v313, v320);  // 虚槽+112 → 坐标三元组写入
        if ( (uint8_t)sub_423340(pArg1 + 8376, szPassword) != 0 )  // sub_423340 · 串首比较判定
        {
          if ( *(uint32_t *)(pArg1 + 8400) < 0x10u )  // 字段 pAppendage(pArg1+8400) 条件判定
            v321 = pArg1 + 8380;
          else
            v321 = *(uint32_t *)(pArg1 + 8380);  // 字段 pAnimC(pArg1+8380) 读写
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, v321, -1, 0, 0);  // 虚槽+212 → vt+212
        }
        sub_4AECE0(1);
      }
      if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8592) )  // 【clock_now(clk)】
// ── [段 32] 大状态 0x1B 之末段 LABEL_462：+8592 时刻二次判定 ──
LABEL_462:
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚槽+560
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
    // ── [段 33] default：直接 goto LABEL_463 走公共尾（未知大状态静默）──
    default:
      goto LABEL_463;  // 跳转 LABEL_463(收尾/共用分支)
  }
}

