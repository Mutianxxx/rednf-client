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
void /*thiscall*/ sub_4C9950(int *this, int nArg2, int pArg3, int nArg4, int nArg5)
{
  int fld_e2378; // ebx
  int v7; // ebx
  int pThis_944; // eax
  int fld_e16392; // edi
  int nArg22; // ecx
  int fld_e2336; // ecx
  int fld_e23362; // eax
  int fld_e23363; // ecx
  int v14; // eax
  int fld_e23364; // ecx
  int v16; // edi
  int fld_e2340; // ecx
  int fld_e2129; // eax
  uint32_t *pThis_866; // edi
  int i; // ebx
  int v21; // edx
  int v22; // eax
  void **v23; // eax
  uint32_t *pThis_87A; // edi
  int j; // ebx
  int fld_e2175; // ecx
  int fld_e21752; // eax
  int pObj12; // ecx
  int v29; // eax
  int pObj11; // ecx
  int fld_e2179; // ecx
  uint32_t *pThis_884; // edi
  int k; // ebx
  int v34; // edx
  int v35; // eax
  uint32_t *pThis_88C; // edi
  int m; // ebx
  uint32_t *pThis_913; // edi
  int fld_e21292; // eax
  uint32_t *pThis_91D; // edi
  int n; // ebx
  uint32_t *pThis_930; // edi
  int ii; // ebx
  uint32_t *pThis_9132; // edi
  int jj; // ebx
  int fld_e21293; // eax
  uint32_t *pThis_929; // edi
  int kk; // ebx
  int v49; // edx
  int v50; // edi
  int v51; // eax
  int fld_e15545; // eax
  int v53; // edi
  int fld_e212912; // eax
  int pThis_6C; // eax
  int pThis_6C2; // eax
  int fld_e2356; // edi
  int fld_e913; // ecx
  int v59; // edi
  int *v60; // edi
  int fld_e2910; // ecx
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
  int pObj3; // ebx
  int v73; // edi
  int v74; // eax
  int v75; // eax
  int fld_e1813; // edi
  long double fld_e28; // st7
  uint64_t v78; // rax
  int fld_e30; // ecx
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
  int fld_e2170; // eax
  int v93; // edi
  int v94; // eax
  int v95; // eax
  void *fld_e302; // edx
  int pObj10; // edi
  int fld_e29; // ecx
  int v99; // ebx
  int v100; // ebx
  int v101; // eax
  int v102; // eax
  int v103; // eax
  int v104; // eax
  bool v105; // al
  int v106; // eax
  int pObj8; // eax
  int v108; // eax
  int fld_e23365; // ecx
  int v110; // eax
  int fld_e23366; // ecx
  int v112; // eax
  int v113; // edi
  int v114; // eax
  char *v115; // edi
  int v116; // ebx
  int v117; // eax
  int v118; // eax
  int fld_e2172; // eax
  int v120; // edi
  int v121; // edx
  int fld_e2174; // eax
  int v123; // eax
  int pObj; // eax
  int v125; // eax
  int fld_e21753; // ecx
  int v127; // eax
  int fld_e21754; // ecx
  int v129; // eax
  int v130; // eax
  int v131; // eax
  int v132; // edx
  int pThis_2062; // edi
  int v134; // eax
  int v135; // eax
  int v136; // edi
  int pObj4; // edi
  int fld_e292; // ecx
  int v139; // ebx
  int v140; // ebx
  int v141; // eax
  int v142; // eax
  int v143; // eax
  uint32_t *pThis_828; // edi
  int fld_e2054; // edi
  int v146; // eax
  int v147; // eax
  int v148; // eax
  int v149; // eax
  int pObj2; // edi
  bool v151; // bl
  int v152; // eax
  int pThis_222; // ecx
  void *v154; // edi
  void **Block2; // ecx
  int v156; // eax
  int pObj5; // ebx
  int fld_e293; // ecx
  int v159; // edi
  int v160; // eax
  int nRand2; // eax
  void **Block3; // ecx
  int v163; // eax
  int pObj6; // edi
  int fld_e294; // ecx
  int v166; // ebx
  int v167; // eax
  char *v168; // ebx
  int v169; // edi
  int v170; // eax
  int v171; // eax
  void *pThis_81C; // eax
  int v173; // edi
  int v174; // eax
  int v175; // eax
  int v176; // eax
  int pThis_81C2; // ebx
  int v178; // eax
  int v179; // edx
  int v180; // eax
  void **Block4; // eax
  int fld_e2187; // edx
  int v183; // edi
  int v184; // ebx
  int pThis_2; // ecx
  int v186; // eax
  const char *fld_e96; // edx
  int v188; // eax
  int v189; // eax
  const char *fld_e962; // ecx
  int v191; // eax
  int mm; // edi
  int pThis_23; // ecx
  int v194; // eax
  int *v195; // ebx
  int *pThis_88C2; // eax
  int v197; // edi
  int v198; // eax
  int v199; // eax
  void *v200; // eax
  void *fld_e2183; // ecx
  int v202; // ebx
  int fld_e303; // edi
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
  int pObj7; // ebx
  int fld_e295; // ecx
  int v217; // ebx
  int pObj9; // ebx
  int fld_e296; // ecx
  int v220; // edx
  uint32_t *pThis_851; // edi
  int v222; // ecx
  int v223; // ebx
  int v224; // ebx
  int fld_e2242; // ecx
  uint64_t v226; // rax
  int v227; // eax
  int v228; // eax
  int v229; // edx
  int v230; // eax
  int v231; // eax
  int fld_e22422; // eax
  int v233; // ebx
  int v234; // eax
  int v235; // eax
  char pThis_5A; // al
  int v237; // eax
  int fld_e22423; // eax
  bool v239; // al
  int fld_e2343; // eax
  char pThis_5A5; // al
  int v242; // eax
  char pThis_5A6; // al
  int v244; // eax
  char pThis_5A7; // al
  int v246; // eax
  char pThis_5A8; // al
  int v248; // eax
  char pThis_5A9; // al
  int v250; // eax
  char pThis_5A10; // al
  int v252; // eax
  int v253; // ebx
  char pThis_5A2; // al
  int v255; // eax
  char pThis_5A3; // al
  int v257; // eax
  char pThis_5A4; // al
  int v259; // eax
  int v260; // edi
  int v261; // eax
  int fld_e22424; // eax
  bool v263; // al
  int v264; // eax
  int v265; // eax
  int pThis_5A13; // eax
  int v267; // eax
  char pThis_5A14; // al
  int v269; // eax
  int v270; // eax
  int v271; // eax
  void *fld_e305; // ecx
  char pThis_5A11; // al
  int v274; // eax
  char pThis_5A12; // al
  int v276; // eax
  int v277; // eax
  int v278; // eax
  int fld_e2329; // ecx
  int fld_e2332; // eax
  int pThis_5A15; // eax
  int v282; // eax
  char pThis_5A16; // al
  int v284; // eax
  int fld_e22425; // ecx
  char *v286; // eax
  int v287; // ebx
  int v288; // eax
  int v289; // eax
  int v290; // eax
  int v291; // eax
  void *fld_e306; // ecx
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
  int fld_e15543; // eax
  int v311; // edx
  int v312; // eax
  int v313; // eax
  void **Block5; // eax
  int pThis_6684; // edi
  int pThis_823; // edi
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
  int fld_e21294; // eax
  unsigned int pThis_2181; // edi
  int v333; // edx
  int fld_e21295; // eax
  int v335; // eax
  int v336; // eax
  int v337; // ebx
  int v338; // eax
  int v339; // eax
  int pThis_6DD; // eax
  int v341; // edx
  unsigned int pThis_21812; // ecx
  int v343; // eax
  int v344; // edx
  unsigned int pThis_21813; // ecx
  int v346; // eax
  int v347; // edx
  unsigned int pThis_21814; // ecx
  int v349; // edx
  int v350; // edx
  int *fld_e1554; // eax
  int v352; // eax
  int fld_e15542; // eax
  int v354; // eax
  int v355; // edx
  int v356; // ebx
  int v357; // eax
  int v358; // ebx
  int v359; // edx
  int v360; // eax
  void **v361; // eax
  int pThis_8583; // eax
  int v363; // edx
  int v364; // edi
  int v365; // eax
  int fld_e21296; // eax
  int fld_e91; // edx
  int v368; // edi
  int *v369; // edi
  int fld_e297; // ecx
  int v371; // ebx
  int v372; // eax
  int v373; // ebx
  int v374; // eax
  int v375; // eax
  int v376; // eax
  int fld_e912; // ecx
  int v378; // edi
  int *v379; // edi
  int fld_e298; // ecx
  int v381; // ebx
  int v382; // eax
  int v383; // ebx
  int v384; // eax
  int v385; // eax
  int v386; // eax
  int fld_e21297; // eax
  char pThis_5A18; // al
  int v389; // eax
  int fld_e2151; // edi
  char pThis_5A19; // al
  int v392; // eax
  int v393; // eax
  int v394; // edi
  int v395; // eax
  int v396; // eax
  int v397; // eax
  int v398; // eax
  uint64_t v399; // rax
  char pThis_5A20; // al
  int v401; // edi
  int *v402; // edi
  int fld_e299; // ecx
  int v404; // ebx
  int v405; // ebx
  int v406; // eax
  int v407; // eax
  int v408; // eax
  int v409; // eax
  uint64_t v410; // rax
  int fld_e309; // edi
  int v412; // eax
  int fld_e21298; // eax
  int v414; // edi
  int v415; // eax
  int v416; // eax
  char pThis_5A17; // al
  int v418; // eax
  int fld_e212911; // eax
  int v420; // eax
  int v421; // eax
  int v422; // eax
  void **v423; // eax
  int fld_e2154; // eax
  int pThis_858; // edi
  int fld_e21542; // eax
  int v427; // edx
  int v428; // eax
  void **v429; // eax
  int fld_e21562; // eax
  int v431; // edi
  int v432; // eax
  int pThis_8582; // eax
  int v434; // edx
  int pThis_6683; // edi
  int v436; // eax
  int v437; // edx
  int fld_e308; // edi
  int fld_e21543; // eax
  int fld_e2156; // eax
  int fld_e307; // eax
  int v442; // ecx
  int v443; // edi
  int v444; // ebx
  int fld_e2163; // eax
  int fld_e3010; // edi
  int fld_e2160; // eax
  int fld_e1954; // eax
  int fld_e19542; // ecx
  int fld_e1952; // ecx
  int v451; // edi
  int fld_e19522; // eax
  int v453; // ebx
  int v454; // eax
  int v455; // eax
  int v456; // eax
  double v457; // st7
  int v458; // eax
  char pThis_5A21; // al
  int v460; // ebx
  int *v461; // ebx
  int v462; // edx
  int v463; // edi
  int v464; // eax
  int v465; // edi
  int v466; // eax
  int v467; // eax
  int v468; // eax
  int fld_e1991; // eax
  unsigned int fld_e2155; // [esp-14h] [ebp-180h]
  int fld_e21299; // [esp-10h] [ebp-17Ch]
  int fld_e212910; // [esp-10h] [ebp-17Ch]
  int v473; // [esp-Ch] [ebp-178h]
  int v474; // [esp-Ch] [ebp-178h]
  int pThis_668; // [esp-8h] [ebp-174h]
  int pThis_6682; // [esp-8h] [ebp-174h]
  int v477; // [esp-8h] [ebp-174h]
  int v478; // [esp-4h] [ebp-170h]
  int v479; // [esp-4h] [ebp-170h]
  int nRand; // [esp-4h] [ebp-170h]
  int fld_e2326; // [esp-4h] [ebp-170h]
  int fld_e23262; // [esp-4h] [ebp-170h]
  int fld_e139; // [esp-4h] [ebp-170h]
  int v484; // [esp-4h] [ebp-170h]
  int v485; // [esp+0h] [ebp-16Ch]
  int fld_e15544; // [esp+0h] [ebp-16Ch]
  int fld_e1639; // [esp+Ch] [ebp-160h]
  int v488; // [esp+10h] [ebp-15Ch] BYREF
  float fld_e304; // [esp+14h] [ebp-158h]
  int pThis_22; // [esp+18h] [ebp-154h] BYREF
  int pThis_88C3; // [esp+1Ch] [ebp-150h] BYREF
  void *pMem; // [esp+20h] [ebp-14Ch] BYREF
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
  int dword_796E502; // [esp+15Ch] [ebp-10h]
  int v506; // [esp+168h] [ebp-4h]
  float v507; // [esp+174h] [ebp+8h]
  float v508; // [esp+180h] [ebp+14h]
  float v509; // [esp+180h] [ebp+14h]
  int v510; // [esp+180h] [ebp+14h]

  // ── [段 1] 入口序：dword_796E502 快照 → 取大状态 fld_e1639=this[1639] → 冲刺/停步态预处理 ──
  //   this = CNGunner 对象（本函数 = CNGunner::vt+472，class_method_slots.txt 直证）；
  //   nArg2 = 动作/事件号；pArg3 = 技能参数数组；nArg4/nArg5 = 两浮点参；
  //   状态 0/11/6 时按 vt+940 与 +9500 判定并 vt+944(1, sub_4238E0(+2372)) 施加速；其余态 vt+944(0,-1) 复位；
  //   三层 switch：第一重 fld_e16392（=1639）收招、第二重 nArg2 主演出、第三重(LABEL_482) 动作事件号
  dword_796E502 = dword_796E50;
  fld_e1639 = *(this + 1639);
  if ( *(float *)&nArg2 == 0.0 || nArg2 == 11 || nArg2 == 6 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 && *((uint8_t *)this + 9500) != 0 )
    {
      fld_e2378 = *(this + 2378);
      if ( sub_699000((int)(this + 2372)) < fld_e2378 )  // 【clock_now(clk)】
      {
        v7 = *this;
        pThis_944 = sub_4238E0(this + 2372);
        (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 944))(this, 1, pThis_944);
      }
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*this + 944))(this, 0, -1);
  }
  // ── [段 2] 状态 16 / 22 归一与抓取体同步：+2336 目标存活时抄其坐标到局部 ──
  //   状态 22 且 this[2129]==14 时不归一；+2336 对象 vt+308 判活后 vt+120/124 取坐标
  fld_e16392 = fld_e1639;
  if ( fld_e1639 == 16 )
  {
    if ( *((uint8_t *)this + 8692) == 0 )
    {
LABEL_12:
      nArg22 = nArg2;
      goto LABEL_13;
    }
  }
  else if ( fld_e1639 != 22 || *(this + 2129) != 14 )
  {
    goto LABEL_12;
  }
  nArg22 = nArg2;
  if ( nArg2 != 22 )
  {
    fld_e2336 = *(this + 2336);
    if ( fld_e2336 != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2336 + 308))(fld_e2336) != 0 )
      {
        fld_e23362 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2336) + 120))(*(this + 2336));
        fld_e23363 = *(this + 2336);
        pThis_22 = fld_e23362;
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e23363 + 124))(fld_e23363);
        fld_e23364 = *(this + 2336);
        pThis_88C3 = v14;
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e23364 + 128))(fld_e23364);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 2336) + 136))(
               *(this + 2336),
               pThis_22,
               pThis_88C3,
               0) != 0
          && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2336) + 132))(*(this + 2336), v16) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2336) + 108))(
            *(this + 2336),
            pThis_22,
            pThis_88C3,
            v16);
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)*(this + 2336) + 140))(
                    *(this + 2336),
                    &pThis_22,
                    &pThis_88C3,
                    pThis_22,
                    pThis_88C3,
                    100,
                    1,
                    1) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2336) + 108))(
            *(this + 2336),
            pThis_22,
            pThis_88C3,
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
          pMem = (void *)4;
          sub_431230((int)&v501, &pMem);
          pMem = nullptr;
          sub_431230((int)&v501, &pMem);
          pMem = nullptr;
          sub_431230((int)&v501, &pMem);
          pMem = (void *)100;
          sub_431230((int)&v501, &pMem);
          pMem = (void *)10;
          sub_431230((int)&v501, &pMem);
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
      fld_e2340 = *(this + 2340);
      *(this + 2336) = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2340 + 76))(fld_e2340, 0);
      fld_e16392 = fld_e1639;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);
    nArg22 = nArg2;
  }
LABEL_13:
  // ── [段 3] 第一重 switch(fld_e16392)：★ 收招/回挂主表（8/15/17/18/20/22/23/25/26/27）──
  switch ( fld_e16392 )
  {
    // ── [段 4] 第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派 ──
    //   LABEL_43/44 为汇合点；nArg22 != 0 时跳 LABEL_108（第一重出口）；
    //   否则 sub_4C2020(v494, vt+1096() 枪种) 组串后 LABEL_70 经 vt+212 播报（+498<0x10 用内联缓冲）
    case 8:
      fld_e2129 = *(this + 2129);
      switch ( fld_e2129 )
      {
        case 11:
          pThis_866 = this + 2150;
          for ( i = 2; i != 0; --i )
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_866++);
          goto LABEL_43;
        case 5:
          if ( *((uint8_t *)this + 8608) == 0 )
            goto LABEL_44;
          if ( nArg22 != 8 )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2153));
LABEL_43:
            nArg22 = nArg2;
LABEL_44:
            if ( nArg22 != 8 )
              *(this + 2129) = -1;
          }
          break;
        case 26:
          if ( nArg22 != 8 )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);
            sub_49C620(3, 1, 0);
            sub_49C5F0(3, 0, 0, 500);
            goto LABEL_43;
          }
          break;
        case 53:
          if ( nArg22 != 8 )
          {
            (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);
            goto LABEL_43;
          }
          break;
        default:
          goto LABEL_44;
      }
      if ( nArg22 != 0 )
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
    // ── [段 5] 第一重 case 15：回挂 +2170 起 2 件动画（vt+208）──
    case 15:
      pThis_87A = this + 2170;
      for ( j = 2; j != 0; --j )
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_87A++);
      goto LABEL_108;
    // ── [段 6] 第一重 case 17/18：分支处理（VT_SM 组），goto LABEL_108（第一重出口）──
    case 17:
      (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);
      goto LABEL_108;
    case 18:
      if ( nArg22 == 18 )
        goto LABEL_108;
      fld_e2175 = *(this + 2175);
      if ( fld_e2175 != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2175 + 308))(fld_e2175) != 0 )
        {
          if ( (fld_e21752 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2175) + 120))(*(this + 2175)),
                pObj12 = *(this + 2175),
                pThis_88C3 = fld_e21752,
                v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 124))(pObj12),
                pObj11 = *(this + 2175),
                pThis_22 = v29,
                (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj11 + 136))(pObj11, pThis_88C3, v29, 0) != 0)
            && (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2175) + 132))(*(this + 2175), 0) != 0
            || (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)*(this + 2175)
                                                                                                + 140))(
                 *(this + 2175),
                 &pThis_88C3,
                 &pThis_22,
                 pThis_88C3,
                 pThis_22,
                 100,
                 1,
                 1) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 2175) + 108))(
              *(this + 2175),
              pThis_88C3,
              pThis_22,
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
            pMem = (void *)4;
            sub_431230((int)&v501, &pMem);
            pMem = (void *)2;
            sub_431230((int)&v501, &pMem);
            pMem = (void *)1;
            sub_431230((int)&v501, &pMem);
            pMem = nullptr;
            sub_431230((int)&v501, &pMem);
            pMem = nullptr;
            sub_431230((int)&v501, &pMem);
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
        fld_e2179 = *(this + 2179);
        *(this + 2175) = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2179 + 76))(fld_e2179, 0);
      }
      *(this + 2129) = -1;
      pThis_884 = this + 2180;
      for ( k = 2; k != 0; --k )
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_884++);
      if ( *(float *)&nArg2 != 0.0 )
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
    // ── [段 7] 第一重 case 20：nArg22 != 20 时清 this[2129]=-1 + 回挂 +2188 起 2 件 + vt+216(11) ──
    case 20:
      if ( nArg22 != 20 )
      {
        *(this + 2129) = -1;
        pThis_88C = this + 2188;
        for ( m = 2; m != 0; --m )
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_88C++);
        (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 11);
      }
      goto LABEL_108;
    // ── [段 8] 第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理 ──
    //   子 switch：12/14/13·36/39 四组，各自回挂不同动画件；
    //   nArg2 != 22 时清 this[2129]=-1；LABEL_96：nArg2 为 0 时播 SUBWEAPON_IN，
    //   +2242==0 时 vt+996 收束；LABEL_108 出口：nArg2==24 时改写 nArg2=8 与 fld_e1639=24（别名折叠）
    case 22:
      pThis_913 = this + 2323;
      pThis_88C3 = 2;
      do
      {
        if ( *pThis_913 != 0 )
        {
          sub_492980(*pThis_913);
          *pThis_913 = 0;
        }
        ++pThis_913;
        --pThis_88C3;
      }
      while ( *(float *)&pThis_88C3 != 0.0 );
      fld_e21292 = *(this + 2129);
      switch ( fld_e21292 )
      {
        case 12:
          pThis_91D = this + 2333;
          for ( n = 3; n != 0; --n )
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_91D++);
          break;
        case 14:
          if ( nArg2 == 22 )
            goto LABEL_96;
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2341));
          break;
        case 13:
        case 36:
          if ( nArg2 == 22 )
            goto LABEL_96;
          (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 12);
          break;
        case 39:
          sub_492980(*(this + 2343));
          sub_492980(*(this + 2344));
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2349));
          pThis_930 = this + 2352;
          for ( ii = 2; ii != 0; --ii )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(pThis_930 - 5));
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_930);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(pThis_930 - 2));
            ++pThis_930;
          }
          (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 13);
          break;
        default:
          break;
      }
      if ( nArg2 != 22 )
        *(this + 2129) = -1;
LABEL_96:
      if ( *(float *)&nArg2 == 0.0 )
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SUBWEAPON_IN", -1, 0, 0);
      if ( *(this + 2242) == 0 )
        (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);
LABEL_108:
      if ( nArg2 == 24 )
      {
        nArg2 = 8;
        fld_e1639 = 24;
      }
      break;
    // ── [段 9] 第一重 case 23：nArg22 != 23 时清 this[2129]=-1 并按本机 vt+308 处理（goto LABEL_108）──
    case 23:
      if ( nArg22 != 23 )
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
    // ── [段 10] 第一重 case 25/26/27：25 → vt+996 + nArg2!=0 时 +2371=-1；──
    //   26 → 回挂 +2323 起 2 件后按 this[2129] 39/40 二支；27 → 落 LABEL_107（清 this[2129] 出口）；default → LABEL_108
    case 25:
      (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);
      if ( *(float *)&nArg2 != 0.0 )
        *(this + 2371) = -1;
      goto LABEL_108;
    case 26:
      pThis_9132 = this + 2323;
      for ( jj = 2; jj != 0; --jj )
      {
        if ( *pThis_9132 != 0 )
        {
          sub_492980(*pThis_9132);
          *pThis_9132 = 0;
        }
        ++pThis_9132;
      }
      fld_e21293 = *(this + 2129);
      if ( fld_e21293 == 39 )
      {
        pThis_929 = this + 2345;
        for ( kk = 2; kk != 0; --kk )
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_929++);
      }
      else if ( fld_e21293 == 40 )
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
  // ── [段 11] 第二重 switch(nArg2)：★ 动作主表（12/15/16/17/18/19/20/21/22/23/25/26/27）──
  switch ( nArg2 )
  {
    // ── [段 12] 第二重 case 12：★ R_GN_SLIDING（滑铲）—— 速度×4.1 夹取 >=200 后反算帧长 ──
    //   fld_e1813 = sub_491C70(this[1813], this[1982]) 帧时长；+2158 存夹取量，+2159 = -1000*v78/fld_e1813；
    //   +2160 存 v78 后 vt+876 全零 + +2161=-400 偏移 + 播 R_GN_SLIDING（goto LABEL_482）
    case 12:
      fld_e1813 = sub_491C70(*(this + 1813), *(this + 1982));
      fld_e28 = *(float *)(*(this + 28) + 16) * 4.0999999;
      if ( (int)(uint64_t)fabs(fld_e28) <= 200 )
        LODWORD(v78) = 200;
      else
        v78 = (uint64_t)fabs(fld_e28);
      *(this + 2158) = v78;
      fld_e30 = *(this + 30);
      HIDWORD(v78) = *this;
      *(this + 2159) = -1000 * (int)v78 / fld_e1813;
      *(this + 2160) = *(uint32_t *)(fld_e30 + 148);
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
    // ── [段 13] 第二重 case 15：★ 旋风（Windmill 系）—— pArg3[1][0]==3 时主演出 ──
    //   vt+196(this[1554]+28) 应用技能参 + vt+344(this[139]) 动画基；
    //   sub_47EFD0 伤害写 this[97] 索引；sub_47EF20(1)/(2) 读表写 +2168 与 fld_e304 倍率；
    //   sub_477 之后 vt+900(3) 与 vt+888 帧长；vt+896(4,4) 挂帧；vt+1140(35) 分支（991/1010 两支）；
    //   +2170 惰性建 WindmillDust1/2.ani（1045-1066）；+2168==1 时再建 WindmillDust3.ani（1088）；goto LABEL_482
    case 15:
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 28));
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
      if ( **(uint32_t **)(pArg3 + 4) == 3 )
      {
        v81 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 3);
        v82 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 3);
        v83 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
        pMem = (void *)sub_47EFD0(v81, 0.0, v82, v83, v83, 0);
        *((float *)this + 97) = (float)(int)pMem;
        *(this + 2168) = sub_47EF20(1, v82, -1, -1, 11);
        v84 = (void *)sub_47EF20(2, v82, -1, -1, 11);
        v85 = *this;
        pMem = v84;
        fld_e304 = (double)(int)v84 * 0.0099999998 + 1.0;
        pMem = (void *)(*(int (/*thiscall*/ **)(int *, int))(v85 + 900))(this, 3);
        (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, int, uint32_t))(v85 + 888))(
          this,
          (uint64_t)((double)(int)pMem * fld_e304) >> 32,
          1,
          0,
          1000,
          (uint64_t)((double)(int)pMem * fld_e304));
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
          *(float *)&pThis_88C3 = COERCE_FLOAT(sub_47EF20(0, v88, -1, -1, 11));
          v89 = (void *)sub_47EF20(1, v88, -1, -1, 11);
          v90 = *this;
          v91 = v89;
          pMem = v89;
          (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(v90 + 876))(
            this,
            (uint64_t)((double)pThis_88C3 * 0.82999998) >> 32,
            0,
            pThis_88C3,
            (uint64_t)((double)pThis_88C3 * 0.82999998),
            1,
            0,
            0);
          (*(void (/*fastcall*/ **)(int *, uint32_t, int, void *, uint32_t, int, uint32_t, uint32_t))(*this + 876))(
            this,
            (uint64_t)((double)(int)pMem * 0.82999998) >> 32,
            1,
            v91,
            (uint64_t)((double)(int)pMem * 0.82999998),
            1,
            0,
            0);
        }
      }
      fld_e2170 = *(this + 2170);
      v93 = 0;
      *(this + 2167) = 0;
      *((uint8_t *)this + 8676) = 0;
      if ( fld_e2170 == 0 )
      {
        pMem = (void *)sub_42FCB0(228);
        v506 = 9;
        if ( pMem != nullptr )
          // ── [段 14] 第二重 case 15 之 +2170 惰性建件：WindmillDust1/2.ani 双枚（内联/堆指针二选一）──
          v94 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust1.ani", 1);
        else
          v94 = 0;
        v506 = -1;
        *(this + 2170) = v94;
        pMem = (void *)sub_42FCB0(228);
        v506 = 10;
        if ( pMem != nullptr )
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
        pMem = (void *)sub_42FCB0(228);
        v506 = 11;
        if ( pMem != nullptr )
          v93 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust3.ani", 1);
        fld_e302 = *(void **)(*(this + 30) + 164);
        v506 = -1;
        pMem = fld_e302;
        sub_493D00(v93, *(float *)&fld_e302);
        pMem = (void *)sub_44B6C0(284);
        v506 = 12;
        if ( pMem != nullptr )
          pObj10 = sub_44E1F0(v93, 1);
        else
          pObj10 = 0;
        fld_e29 = *(this + 29);
        v506 = -1;
        sub_45FE80(fld_e29, pObj10, 2, 0, pObj10, (int)this, 0);
        v99 = *(uint32_t *)pObj10;
        v478 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        (*(void (/*thiscall*/ **)(int))(v99 + 148))(pObj10);
        v100 = *(uint32_t *)pObj10;
        v101 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        v102 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v101);
        v103 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v102);
        (*(void (/*thiscall*/ **)(int, int))(v100 + 112))(pObj10, v103);
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj10 + 60))(pObj10, this);
        sub_4A06D0(v478);
      }
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_WINDMILL", -1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WINDMILL_SWING", -1, 0, 0);
      goto LABEL_482;
    // ── [段 15] 第二重 case 16：★ 散射/连射（RandomShoot1/2.ani）—— 14==14 与 fld_e1639 特例 ──
    //   pArg3[1][0] 读入 v104；v105 = (v104==14 && fld_e1639==16) 门控；
    //   this[8692] 分两支（1170/1180）各处理；goto LABEL_482
    case 16:
      v104 = **(uint32_t **)(pArg3 + 4);
      *(this + 2172) = v104;
      v105 = v104 == 14 && fld_e1639 == 16;
      *((uint8_t *)this + 8692) = v105;
      if ( v105 )
      {
        v106 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8));
        pObj8 = __RTDynamicCast(v106, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *(this + 2336) = pObj8;
        if ( pObj8 != 0 )
        {
          v108 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 120))(pObj8);
          fld_e23365 = *(this + 2336);
          *(this + 2337) = v108;
          v110 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e23365 + 124))(fld_e23365);
          fld_e23366 = *(this + 2336);
          *(this + 2338) = v110;
          *(this + 2339) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e23366 + 128))(fld_e23366);
          if ( *(this + 2340) == 0 )
          {
            pMem = operator new(0x8Cu);
            v506 = 13;
            if ( pMem != nullptr )
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
        LOBYTE(nArg5) = 0;
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);
        *((uint8_t *)this + 8694) = 1;
      }
      else
      {
        v115 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 4);
        v116 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 4);
        v117 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
        pMem = (void *)sub_47EFD0(v115, 0.0, v116, v117, v117, 0);
        *((float *)this + 97) = (float)(int)pMem;
        pMem = (void *)sub_47EF20(1, v116, -1, -1, 11);
        v118 = *this;
        fld_e304 = (double)(int)pMem * 0.0099999998 + 1.0;
        pMem = (void *)(*(int (/*thiscall*/ **)(int *, int))(v118 + 900))(this, 3);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(
          this,
          0,
          0,
          (uint64_t)((double)(int)pMem * fld_e304),
          (uint64_t)((double)(int)pMem * fld_e304));
        *(this + 114) = sub_47EF20(2, v116, -1, -1, 11);
        fld_e2172 = *(this + 2172);
        if ( fld_e2172 == 4 )
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "R_GN_JACKSPIKE",
            -1,
            0,
            0);
        }
        else if ( fld_e2172 == 14 )
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_BBQ", -1, 0, 0);
        }
        *((uint8_t *)this + 8694) = 0;
      }
      *((uint8_t *)this + 8693) = *(this + 2172) == 4
                             && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
                             && (v120 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1132))(this, 0)) == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      goto LABEL_482;
    // ── [段 16] 第二重 case 17：单指令分支（goto LABEL_482）──
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
    // ── [段 17] 第二重 case 18：★ 连射/踏射（MusketDustSmall4 + TreadShootDust1/2.ani）──
    //   +2174 计时器两支：非 0 走 MusketDust 大尘（1332/1369）；0 走 TreadShootDust1/2.ani（1456/1464）；
    //   goto LABEL_482
    case 18:
      v121 = *this;
      *(this + 2174) = **(uint32_t **)(pArg3 + 4);
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
      fld_e2174 = *(this + 2174);
      if ( fld_e2174 != 0 )
      {
        if ( fld_e2174 == 1 )
        {
          if ( sub_41A5E0((unsigned int)this + 8290) > 3 )
          {
            pThis_2062 = sub_41A5E0((unsigned int)this + 8290);
            v134 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
            v135 = sub_495500(v134);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, pThis_2062 * v135 / 3);
          }
          sub_4AECE0((void *)*(this + 30), 9);
          LOBYTE(nArg5) = 0;
          sub_4450B0(1);
          v136 = sub_4C46B0(this, 3);
          if ( v136 != 0 )
          {
            pMem = *(void **)(*(this + 30) + 164);
            sub_493D00(v136, *(float *)&pMem);
            pMem = (void *)sub_44B6C0(284);
            v506 = 17;
            if ( pMem != nullptr )
              pObj4 = sub_44E1F0(v136, 1);
            else
              pObj4 = 0;
            fld_e292 = *(this + 29);
            v506 = -1;
            sub_45FE80(fld_e292, pObj4, 2, 0, pObj4, (int)this, 0);
            v139 = *(uint32_t *)pObj4;
            v479 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int))(v139 + 148))(pObj4);
            v140 = *(uint32_t *)pObj4;
            v141 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
            v142 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v141);
            v143 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v142);
            (*(void (/*thiscall*/ **)(int, int))(v140 + 112))(pObj4, v143);
            (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj4 + 60))(pObj4, this);
            sub_4A06D0(v479);
          }
          if ( (uint8_t)sub_423340(this + 2087, szPassword) != 0 )
          {
            if ( (unsigned int)*(this + 2093) < 0x10 )
              pThis_828 = this + 2088;
            else
              pThis_828 = (uint32_t *)*(this + 2088);
            (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_828, -1, 0, 0);
          }
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), *(this + 2055));
            fld_e2054 = *(uint32_t *)*(this + 2054);
            v146 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
            v147 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v146);
            v148 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v147);
            (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2054 + 40))(*(this + 2054), v148);
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 12))(*(this + 2054), 0);
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 112))(*(this + 2054), 0);
            (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 2054) + 92))(*(this + 2054), v496);
            sub_5E5260(v496);
          }
          v149 = *this;
          *(float *)&pThis_88C3 = 0.0;
          pThis_22 = 0;
          v488 = 0;
          if ( (*(int (/*thiscall*/ **)(int *))(v149 + 1096))(this) == 1 )
          {
            sub_4C17C0(&pThis_88C3, &pThis_22, &v488, 74, 0, 57);
            pObj2 = dword_8F830C;
            v151 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;
            v152 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 28))(pObj2);
            pThis_222 = pThis_22;
            *(uint8_t *)(v152 + 84) = v151;
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 40))(pObj2, pThis_88C3, pThis_222, v488);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);
            (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)pObj2 + 92))(pObj2, &v501);
            v506 = 18;
            sub_4600B0((void *)*(this + 29), 2, 0, (int)&v501);
            goto LABEL_232;
          }
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 1096))(this) == 2 )
          {
            sub_4C17C0(&pThis_88C3, &pThis_22, &v488, 63, 0, 85);
            // ── [段 18] 第二重 case 18 之 +2174 计时器支：MusketDustSmall4 + MusketDustLarge 两件 ──
            sub_401710("Character/Gunner/Effect/Animation/MusketDust/MusketDustSmall4.ani");
            v506 = 19;
            v154 = (void *)sub_44B6C0(284);
            pMem = v154;
            LOBYTE(v506) = 20;
            if ( v154 != nullptr )
            {
              fld_e304 = COERCE_FLOAT(sub_42FCB0(228));
              LOBYTE(v506) = 21;
              if ( fld_e304 == 0.0 )
              {
                v156 = 0;
              }
              else
              {
                LOBYTE(Block2) = Block[0];
                if ( v504 < 0x10 )
                  Block2 = Block;
                v156 = sub_431860((char)Block2, 1);
              }
              LOBYTE(v506) = 20;
              pObj5 = sub_44E1F0(v156, 1);
            }
            else
            {
              pObj5 = 0;
            }
            fld_e293 = *(this + 29);
            LOBYTE(v506) = 19;
            sub_45FE80(fld_e293, (int)v154, 2, 0, pObj5, (int)this, 1);
            v159 = *(uint32_t *)pObj5;
            v160 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int, int))(v159 + 148))(pObj5, v160);
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 112))(pObj5, pThis_88C3, pThis_22, v488);
            nRand = rand() % 40 + 110;
            nRand2 = rand();
            sub_4C17C0(&pThis_88C3, &pThis_22, &v488, nRand2 % 40 + 13, 0, nRand);
            sub_406D60("Character/Gunner/Effect/Animation/MusketDust/MusketDustLarge.ani");
            pMem = (void *)sub_44B6C0(284);
            LOBYTE(v506) = 22;
            if ( pMem != nullptr )
            {
              fld_e304 = COERCE_FLOAT(sub_42FCB0(228));
              LOBYTE(v506) = 23;
              if ( fld_e304 == 0.0 )
              {
                v163 = 0;
              }
              else
              {
                LOBYTE(Block3) = Block[0];
                if ( v504 < 0x10 )
                  Block3 = Block;
                v163 = sub_431860((char)Block3, 1);
              }
              LOBYTE(v506) = 22;
              pObj6 = sub_44E1F0(v163, 1);
            }
            else
            {
              pObj6 = 0;
            }
            fld_e294 = *(this + 29);
            LOBYTE(v506) = 19;
            sub_45FE80(fld_e294, pObj6, 2, 0, pObj6, (int)this, 0);
            v166 = *(uint32_t *)pObj6;
            v167 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int, int))(v166 + 148))(pObj6, v167);
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 112))(pObj6, pThis_88C3, pThis_22, v488);
            v506 = -1;
            sub_501490(v499);
          }
        }
        else if ( fld_e2174 == 2 )
        {
          sub_4AECE0((void *)*(this + 30), 13);
          LOBYTE(nArg5) = 0;
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
        v123 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8));
        pObj = __RTDynamicCast(v123, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *(this + 2175) = pObj;
        if ( pObj != 0 )
        {
          v125 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
          fld_e21753 = *(this + 2175);
          *(this + 2176) = v125;
          v127 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21753 + 124))(fld_e21753);
          fld_e21754 = *(this + 2175);
          *(this + 2177) = v127;
          *(this + 2178) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21754 + 128))(fld_e21754);
          if ( *(this + 2179) == 0 )
          {
            pMem = operator new(0x5Cu);
            v506 = 14;
            if ( pMem != nullptr )
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
          pMem = (void *)sub_42FCB0(228);
          v506 = 15;
          if ( pMem != nullptr )
            // ── [段 19] 第二重 case 18 之 else 支：+2174==0 时建 TreadShootDust1/2.ani 双枚 ──
            v130 = sub_431860((char)"Character/Gunner/Effect/Animation/TreadShootDust1.ani", 1);
          else
            v130 = 0;
          v506 = -1;
          *(this + 2180) = v130;
          pMem = (void *)sub_42FCB0(228);
          v506 = 16;
          if ( pMem != nullptr )
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
    // ── [段 20] 第二重 case 19：★ 速射帧长标定 —— vt+1140(7) 读表 + vt+388 伤害链 ──
    //   vt+1160/vt+1140(7) 取参，vt+388 取当前伤害，sub_47EFD0 三参写回；goto LABEL_482
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
      pMem = (void *)sub_47EFD0(v168, 0.0, v169, v170, v170, 0);
      *((float *)this + 97) = (float)(int)pMem;
      pMem = (void *)sub_47EF20(2, v169, -1, -1, 11);
      *((float *)this + 106) = (double)(int)pMem * 0.1;
      *(this + 109) = sub_47EF20(3, v169, -1, -1, 11);
      pMem = (void *)sub_47EF20(1, v169, -1, -1, 11);
      v171 = *this;
      fld_e304 = (double)(int)pMem * 0.0099999998 + 1.0;
      pMem = (void *)(*(int (/*thiscall*/ **)(int *, int))(v171 + 900))(this, 3);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(
        this,
        0,
        0,
        (uint64_t)((double)(int)pMem * fld_e304),
        (uint64_t)((double)(int)pMem * fld_e304));
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_MACH", -1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "MACH_SWING", -1, 0, 0);
      goto LABEL_482;
    // ── [段 21] 第二重 case 20：★ 擦弹/接近射击（GRAZE_LOOP + RandomShoot1/2.ani）──
    //   fld_e304 = pArg3[1][2]；sub_41A5E0(this+2076) 与 vt+672(3)+sub_495500 算帧长；
    //   fld_e1639 != 20 时按枪种播 R_GUN_GRAZE_LOOP 或 R_BOWGUN_GRAZE_LOOP；
    //   vt+1096 枪种 1/4 分别支：sub_4C1000 或按 this[2*(pMem+v184)] 取件，
    //   sub_4319E0 建 RandomShoot1/2.ani（各带 3 参）；末段按 pArg3[1][0] 1/2/3 三支与 +2183 比对（1697-1742）
    case 20:
      fld_e304 = *(float *)(*(uint32_t *)(pArg3 + 4) + 8);
      pThis_81C = (void *)sub_41A5E0((unsigned int)(this + 2076));
      v173 = *this;
      pMem = pThis_81C;
      v174 = (*(int (/*thiscall*/ **)(int *, int))(v173 + 672))(this, 3);
      v175 = sub_495500(v174);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v173 + 888))(
        this,
        0,
        0,
        1000,
        LODWORD(fld_e304) * (int)pMem * v175 / 10000);
      if ( fld_e1639 != 20 )
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
        pThis_81C2 = sub_41A5E0((unsigned int)(this + 2076));
        v178 = sub_47E9D0(0);
        *(this + 2129) = 9;
        v504 = 15;
        v503 = 0;
        LOBYTE(Block[0]) = 0;
        *(this + 2187) = 100000 / (pThis_81C2 * v178);
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
        Block4 = (void **)Block[0];
        if ( v504 < 0x10 )
          Block4 = Block;
        (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, Block4, 11, 0, 0);
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "GN_RANDOMSHOT",
          -1,
          0,
          0);
        *(this + 2188) = 0;
        *(this + 2189) = 0;
        fld_e2187 = -*(this + 2187);
        *(this + 2183) = -1;
        *(this + 2186) = fld_e2187;
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
      pMem = (void *)(5 * v183 + 1095);
      pThis_2 = *(this + 2 * ((uint32_t)pMem + v184));
      pThis_22 = (int)(this + 2 * ((uint32_t)pMem + v184));
      if ( pThis_2 == 0 )
      {
        v186 = sub_42FCB0(228);
        fld_e304 = *(float *)&v186;
        v506 = 25;
        if ( v186 != 0 )
        {
          fld_e96 = (unsigned int)*(this + 96) < 0x10 ? (const char *)(this + 91) : (const char *)*(this + 91);
          // ── [段 22] 第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚 ──
          v188 = sub_4319E0(v186, v183, v184, fld_e96, "Effect/Animation/ShootEffect/RandomShoot1.ani", 1);
        }
        else
        {
          v188 = 0;
        }
        v506 = -1;
        *(uint32_t *)pThis_22 = v188;
        v189 = sub_42FCB0(228);
        fld_e304 = *(float *)&v189;
        v506 = 26;
        if ( v189 != 0 )
        {
          fld_e962 = (unsigned int)*(this + 96) < 0x10 ? (const char *)(this + 91) : (const char *)*(this + 91);
          v191 = sub_4319E0(v189, v183, v184, fld_e962, "Effect/Animation/ShootEffect/RandomShoot2.ani", 1);
        }
        else
        {
          v191 = 0;
        }
        v506 = -1;
        *(this + 8 * v183 + 2 * v183 + 2 * v184 + 2191) = v191;
        if ( v184 == 1 )
        {
          pThis_88C3 = 2;
          do
          {
            for ( mm = 0; ; ++mm )
            {
              pThis_23 = *(this + 2 * (uint32_t)pMem + 2);
              v194 = *(uint32_t *)(pThis_23 + 44);
              if ( v194 != 0 )
                v194 = (*(uint32_t *)(pThis_23 + 48) - v194) / 88;
              if ( mm >= v194 )
                break;
              *(uint32_t *)(sub_4924C0(mm) + 40) = 2;
            }
            --pThis_88C3;
          }
          while ( *(float *)&pThis_88C3 != 0.0 );
        }
      }
      v195 = (int *)pThis_22;
      pThis_88C2 = this + 2188;
      v197 = 0;
      pThis_88C3 = (int)(this + 2188);
      do
      {
        v198 = *pThis_88C2;
        if ( v198 != *v195 )
        {
          if ( v198 != 0 )
            (*(void (/*thiscall*/ **)(int *, int))(*this + 208))(this, v198);
          v199 = *v195;
          *(uint32_t *)pThis_88C3 = *v195;
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
        pThis_88C2 = (int *)(pThis_88C3 + 4);
        ++v195;
        pThis_88C3 += 4;
      }
      while ( v197 < 2 );
      v200 = **(void ***)(pArg3 + 4);
      fld_e2183 = (void *)*(this + 2183);
      v202 = 0;
      pMem = fld_e2183;
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
      if ( fld_e2183 == v200 )
        ++v202;
      fld_e303 = *(this + 30);
      v204 = sub_491C70(fld_e303, v202);
      sub_493A60(fld_e303, v204);
      LOBYTE(nArg5) = 0;
      pThis_88C3 = (int)(this + 2188);
      pThis_22 = 2;
      do
      {
        v205 = *(uint32_t *)pThis_88C3;
        v206 = sub_491C70(*(uint32_t *)pThis_88C3, v202);
        sub_493A60(v205, v206);
        v207 = pThis_22 == 1;
        pThis_88C3 += 4;
        --pThis_22;
      }
      while ( !v207 );
      *(this + 2185) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
      if ( fld_e1639 != 20 && pMem != (void *)*(this + 2183) )
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
    // ── [段 23] 第二重 case 21：★ 格挡反击/照准（Swordman GuardSpark/GuardCircle.ani 复用）──
    //   pArg3[1][0]/[1]/[2] 三读取入 v209/v210/v213；vt+124 取坐标 + v506 状态号栈；
    //   sub_431860 三次建 Character/Swordman/Effect/Animation/GuardSpark.ani 与 GuardCircle.ani；
    //   （1775 行）fld_e295/fld_e296 存对象槽后 goto LABEL_482
    case 21:
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SWD_GUARDED", -1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_GUNGUARD", -1, 0, 0);
      v208 = *(int **)(pArg3 + 4);
      v209 = *v208;
      v210 = v208[1];
      v211 = *this;
      pThis_88C3 = v209;
      v488 = v210;
      v212 = (*(int (/*thiscall*/ **)(int *))(v211 + 124))(this);
      v213 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
      pThis_22 = v212;
      pMem = (void *)sub_42FCB0(228);
      v506 = 27;
      if ( pMem != nullptr )
        v214 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
      else
        v214 = 0;
      v506 = -1;
      pMem = (void *)sub_44B6C0(284);
      v506 = 28;
      if ( pMem != nullptr )
        pObj7 = sub_44E1F0(v214, 1);
      else
        pObj7 = 0;
      fld_e295 = *(this + 29);
      v506 = -1;
      sub_45FE80(fld_e295, v213, 2, 0, pObj7, (int)this, 0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj7 + 148))(pObj7, pThis_88C3);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 112))(pObj7, v488, pThis_22, v213);
      pMem = (void *)sub_42FCB0(228);
      v506 = 29;
      if ( pMem != nullptr )
        v217 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
      else
        v217 = 0;
      v506 = -1;
      pMem = (void *)sub_44B6C0(284);
      v506 = 30;
      if ( pMem != nullptr )
        pObj9 = sub_44E1F0(v217, 1);
      else
        pObj9 = 0;
      fld_e296 = *(this + 29);
      v506 = -1;
      sub_45FE80(fld_e296, v213, 2, 0, pObj9, (int)this, 0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj9 + 148))(pObj9, pThis_88C3);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 112))(pObj9, v488, pThis_22, v213);
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
    // ── [段 24] 第二重 case 22：★ 副武器发射（SteyrShoot / LaserRifle / Gatling 系）──
    //   pArg3[1][0] → v220，pArg3[1][1] → v222；this[2129] 副武器状态号；
    //   switch(v220) 五型：LABEL_332 汇合；含 sub_431920 建 SteyrShoot.ani、LaserRifleEffect 四件
    //   （FireOnceEffect/FireOnceSpark/FireRing/ChargingEffect/ChargeFullEffect）、
    //   GatlingGunOverHeat/GatlingOverHeat/GatlingGunShoot/AerialGatlingGunShoot.ani 与
    //   sub_4C3640 建 Effect/Particle/GatlingShell.ptl 两处；末段按 this[2242]==0 处理（2473）
    case 22:
      pMem = (void *)*(this + 2242);
      v220 = **(uint32_t **)(pArg3 + 4);
      pThis_851 = this + 2129;
      *(this + 2129) = v220;
      v222 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
      v223 = -1;
      *(this + 2242) = v222;
      pThis_88C3 = 5;
      switch ( v220 )
      {
        case 12:
          pThis_88C3 = 1;
LABEL_332:
          v223 = 17;
          break;
        case 13:
        case 36:
          *(float *)&pThis_88C3 = 0.0;
          goto LABEL_332;
        case 14:
          pThis_88C3 = 1;
          v223 = 21;
          break;
        case 39:
          pThis_88C3 = 2;
          goto LABEL_332;
        case 40:
          pThis_88C3 = 4;
          v223 = 15;
          break;
        default:
          break;
      }
      v224 = v222 + v223;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4 * v224));
      sub_4C4890(this, pThis_88C3, v224);
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
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *pThis_851);
      LODWORD(v226) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *pThis_851);
      fld_e2242 = *(this + 2242);
      pThis_88C3 = v226;
      LODWORD(v226) = 1000;
      v488 = 1000;
      if ( fld_e2242 == 0 )
      {
        fld_e304 = *(float *)(*(this + 30) + 36);
        pThis_22 = LODWORD(fld_e304);
        switch ( *pThis_851 )
        {
          case 0xC:
            v488 = (*(int (/*thiscall*/ **)(int *, int))(*this + 900))(this, 3);
            v230 = sub_47EF20(1, pThis_88C3, -1, -1, 11);
            goto LABEL_338;
          case 0xD:
          case 0x24:
          case 0x27:
            v227 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
            v488 = sub_495540(v227);
            v228 = sub_4B1C40(pThis_88C3);
            v229 = *this;
            pThis_22 = v228;
            (*(void (/*thiscall*/ **)(int *, float, int))(v229 + 992))(this, COERCE_FLOAT(LODWORD(fld_e304)), 1);
            break;
          case 0x28:
            v488 = (*(int (/*thiscall*/ **)(int *, int))(*this + 900))(this, 3);
            v230 = sub_47EF20(2, pThis_88C3, -1, -1, 11);
LABEL_338:
            pThis_22 = v230;
            break;
          default:
            break;
        }
        v226 = (uint64_t)((double)v488 * ((double)SLODWORD(fld_e304) / (double)pThis_22));
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, uint32_t))(*this + 888))(this, 0, 0, 1000, v226);
      v231 = *pThis_851;
      if ( *pThis_851 == 40 )
      {
        fld_e22422 = *(this + 2242);
        if ( fld_e22422 != 0 )
        {
          if ( fld_e22422 == 1 )
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
            pMem = nullptr;
            sub_431230((int)&v501, &pMem);
            pMem = nullptr;
            sub_431230((int)&v501, &pMem);
            (*(void (/*thiscall*/ **)(int *, int, float *, uint32_t, uint32_t))(*this + 560))(this, 26, &v501, 0, 0);
            if ( *(this + 2358) == 0 )
            {
              pMem = (void *)sub_42FCB0(228);
              LOBYTE(v506) = 32;
              if ( pMem != nullptr )
              {
                pThis_5A = unknown_libname_2(this + 90);
                // ── [段 25] 第二重 case 22 之 40 号状态：★ SteyrShoot.ani（斯泰尔射击主件）──
                v237 = sub_431920(pThis_5A, (char)"Effect/Animation/ShootEffect/SteyrShoot.ani", 1);
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
        // ── [段 26] 第二重 case 22 之内层 switch(v231)+2085：各副武器状态的效果选型 ──
        switch ( v231 )
        {
          case 39:
            fld_e22423 = *(this + 2242);
            if ( fld_e22423 != 0 )
            {
              if ( fld_e22423 == 1 )
              {
                if ( *((uint8_t *)this + 9428) != 0 )
                  v253 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
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
                    pMem = (void *)sub_42FCB0(228);
                    v506 = 39;
                    if ( pMem != nullptr )
                    {
                      pThis_5A2 = unknown_libname_2(this + 90);
                      v255 = sub_431920(pThis_5A2, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireOnceEffect.ani", 1);
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
                    pMem = (void *)sub_42FCB0(228);
                    v506 = 40;
                    if ( pMem != nullptr )
                    {
                      pThis_5A3 = unknown_libname_2(this + 90);
                      v257 = sub_431920(pThis_5A3, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireOnceSpark.ani", 1);
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
                  pMem = (void *)sub_42FCB0(228);
                  v506 = 41;
                  if ( pMem != nullptr )
                  {
                    pThis_5A4 = unknown_libname_2(this + 90);
                    v259 = sub_431920(pThis_5A4, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireRing.ani", 1);
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
              fld_e2343 = *(this + 2343);
              *((uint8_t *)this + 9416) = 0;
              *(this + 2355) = 0;
              if ( fld_e2343 != 0 )
              {
                *(uint8_t *)(fld_e2343 + 160) = 1;
              }
              else
              {
                pMem = (void *)sub_42FCB0(228);
                v506 = 33;
                if ( pMem != nullptr )
                {
                  pThis_5A5 = unknown_libname_2(this + 90);
                  // ── [段 27] 第二重 case 22 之 39 号状态（激光步枪）：ChargingEffect/ChargeFullEffect.ani 充能双件 ──
                  v242 = sub_431920(pThis_5A5, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/ChargingEffect.ani", 1);
                }
                else
                {
                  v242 = 0;
                }
                v506 = -1;
                *(this + 2343) = v242;
                pMem = (void *)sub_42FCB0(228);
                v506 = 34;
                if ( pMem != nullptr )
                {
                  pThis_5A6 = unknown_libname_2(this + 90);
                  v244 = sub_431920(pThis_5A6, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/ChargeFullEffect.ani", 1);
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
                pMem = (void *)sub_42FCB0(228);
                v506 = 35;
                if ( pMem != nullptr )
                {
                  pThis_5A7 = unknown_libname_2(this + 90);
                  v246 = sub_431920(
                           pThis_5A7,
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleOnCharge1.ani",
                           1);
                }
                else
                {
                  v246 = 0;
                }
                v506 = -1;
                *(this + 2350) = v246;
                pMem = (void *)sub_42FCB0(228);
                v506 = 36;
                if ( pMem != nullptr )
                {
                  pThis_5A8 = unknown_libname_2(this + 90);
                  v248 = sub_431920(
                           pThis_5A8,
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleOnCharge2.ani",
                           1);
                }
                else
                {
                  v248 = 0;
                }
                v506 = -1;
                *(this + 2351) = v248;
                pMem = (void *)sub_42FCB0(228);
                v506 = 37;
                if ( pMem != nullptr )
                {
                  pThis_5A9 = unknown_libname_2(this + 90);
                  v250 = sub_431920(
                           pThis_5A9,
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleFullCharge2.ani",
                           1);
                }
                else
                {
                  v250 = 0;
                }
                v506 = -1;
                *(this + 2352) = v250;
                pMem = (void *)sub_42FCB0(228);
                v506 = 38;
                if ( pMem != nullptr )
                {
                  pThis_5A10 = unknown_libname_2(this + 90);
                  v252 = sub_431920(
                           pThis_5A10,
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
            fld_e22424 = *(this + 2242);
            if ( fld_e22424 != 0 )
            {
              if ( fld_e22424 == 1 )
              {
                v263 = pMem == (void *)1;
                *((uint8_t *)this + 9301) = pMem == (void *)1;
                if ( v263 )
                {
                  fld_e2326 = *(this + 2326);
                  pThis_668 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
                  v270 = sub_47EF20(1, pThis_88C3, -1, -1, 11);
                  v271 = sub_423A80(0, v270, pThis_668, fld_e2326);
                  fld_e305 = (void *)*(this + 30);
                  *(this + 2327) = v271;
                  sub_4AECE0(fld_e305, 0);
                  sub_4939E0(*(this + 30), 1);
                  LOBYTE(nArg5) = 0;
                  if ( *(this + 2334) == 0 )
                  {
                    pMem = (void *)sub_42FCB0(228);
                    v506 = 44;
                    if ( pMem != nullptr )
                    {
                      pThis_5A11 = unknown_libname_2(this + 90);
                      // ── [段 28] 第二重 case 22 之加特林组：GatlingGunOverHeat/GatlingOverHeat/GatlingGunShoot.ani 三件 ──
                      v274 = sub_431920(pThis_5A11, (char)"Effect/Animation/GatlingGunOverHeat.ani", 1);
                    }
                    else
                    {
                      v274 = 0;
                    }
                    v506 = -1;
                    *(this + 2334) = v274;
                    pMem = (void *)sub_42FCB0(228);
                    v506 = 45;
                    if ( pMem != nullptr )
                    {
                      pThis_5A12 = unknown_libname_2(this + 90);
                      v276 = sub_431920(pThis_5A12, (char)"Effect/Animation/GatlingOverHeat.ani", 1);
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
                  *(this + 2326) = sub_47EF20(2, pThis_88C3, -1, -1, 11);
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
                    pMem = operator new(0x12Cu);
                    v506 = 42;
                    if ( pMem != nullptr )
                    {
                      pThis_5A13 = unknown_libname_2(this + 90);
                      v267 = sub_4C3640(pThis_5A13, "Effect/Particle/GatlingShell.ptl", this);
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
                    pMem = (void *)sub_42FCB0(228);
                    v506 = 43;
                    if ( pMem != nullptr )
                    {
                      pThis_5A14 = unknown_libname_2(this + 90);
                      v269 = sub_431920(pThis_5A14, (char)"Effect/Animation/GatlingGunShoot.ani", 1);
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
            fld_e22425 = *(this + 2242);
            if ( fld_e22425 != 0 )
            {
              if ( fld_e22425 == 1 )
              {
                v207 = pMem != (void *)1;
                *((uint8_t *)this + 9301) = pMem == (void *)1;
                if ( v207 )
                {
                  *(this + 2326) = sub_47EF20(1, pThis_88C3, -1, -1, 11);
                  v286 = "Character/Gunner/Effect/Particle/FlameThrower.ptl";
                  if ( *pThis_851 != 13 )
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
                      *pThis_851 != 13 ? 22204 : 22201,
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
                  fld_e23262 = *(this + 2326);
                  pThis_6682 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
                  v290 = sub_47E9D0(0);
                  v291 = sub_423A80(0, v290, pThis_6682, fld_e23262);
                  fld_e306 = (void *)*(this + 30);
                  *(this + 2327) = v291;
                  sub_4AECE0(fld_e306, 0);
                  sub_4939E0(*(this + 30), 1);
                  LOBYTE(nArg5) = 0;
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
              fld_e2329 = v278 * *(this + 2329);
              *(this + 2331) = v278;
              fld_e2332 = *(this + 2332);
              *(this + 2326) = fld_e2329 + 200;
              if ( fld_e2332 == 0 )
              {
                pMem = operator new(0x12Cu);
                v506 = 47;
                if ( pMem != nullptr )
                {
                  pThis_5A15 = unknown_libname_2(this + 90);
                  // ── [段 29] 第二重 case 22 之弹壳粒子：sub_4C3640 建 Effect/Particle/GatlingShell.ptl 两处 ──
                  v282 = sub_4C3640(pThis_5A15, "Effect/Particle/GatlingShell.ptl", this);
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
                pMem = (void *)sub_42FCB0(228);
                v506 = 48;
                if ( pMem != nullptr )
                {
                  pThis_5A16 = unknown_libname_2(this + 90);
                  v284 = sub_431920(pThis_5A16, (char)"Effect/Animation/AerialGatlingGunShoot.ani", 1);
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
            pMem = v298;
            pMem = &v298[v296[3]];
            v299 = *(uint32_t *)(v297 + 24);
            *(float *)Block = (float)(int)pMem;
            v300 = (double)*(int *)(v297 + 24);
            if ( v299 < 0 )
              v300 = v300 + 4294967300.0;
            v301 = v296[4];
            *(float *)&v504 = v300;
            pMem = (void *)-(*(uint32_t *)(v297 + 32) + v299 + v301);
            v501 = (float)(unsigned int)pMem;
            v302 = sub_4924C0(i1);
            sub_4931A0((int *)(v302 + 56), Block);
          }
          fld_e139 = *(this + 139) + 608;
          (*(void (/*thiscall*/ **)(int *))(*this + 344))(this);
          v303 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 1160))(this, 34, 0, v303);
          pMem = (void *)sub_47EF20(34, -1, -1, 11, fld_e139);
          *((float *)this + 97) = (float)(int)pMem;
        }
      }
LABEL_482:
      sub_4B89D0(nArg2, pArg3, *(float *)&nArg4, *(float *)&nArg5);
      // ── [段 30] ★ LABEL_482：本帧公共尾 —— sub_4B89D0 参数登记 + 第三重 switch(nArg2) 动作事件号 ──
      //   第三重 case 表：0/4/6/7/8/10/12/14（各 case 多为 return，不落公共尾）
      switch ( nArg2 )
      {
        // ── [段 31] 第三重 case 0：清 this[2134]/[2135] 双槽后 return（空操作态）──
        case 0:
          *(this + 2134) = -1;
          *(this + 2135) = -1;
          return;
        // ── [段 32] 第三重 case 4：this[1708]==2 时按 vt+1140(8) 正负两支处理，return ──
        case 4:
          if ( *(this + 1708) == 2 )
          {
            if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 8) <= 0 )
            {
              *(this + 2166) = -1;
            }
            else
            {
              fld_e307 = *(this + 30);
              v442 = *(uint32_t *)(fld_e307 + 212);
              if ( v442 != 0 )
                v443 = sub_4910A0(v442);
              else
                v443 = *(uint32_t *)(fld_e307 + 32);
              (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 8);
              v444 = sub_47E9D0(0);
              *(this + 2166) = sub_491C10(*(this + 30)) - v443 - v444;
            }
          }
          return;
        // ── [段 33] 第三重 case 6：fld_e1639==7 时（+1723==1 特例）sub_4C2020(v494, vt+1096()) 组串 + vt+212 播报后 return ──
        case 6:
          if ( fld_e1639 == 7 )
          {
            if ( *(this + 1723) == 1 )
            {
              fld_e2155 = abs32(*(this + 2155));
              (*(void (/*thiscall*/ **)(int *, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this + 876))(
                this,
                0,
                fld_e2155,
                fld_e2155,
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
        // ── [段 34] 第三重 case 7：★★ 本函数最大分支 —— 连发计数与枪口烟雾/弹壳（约 590 行）──
        //   fld_e1639==7 时 --this[1724] 计数并取 +2154 计时器两支（2593-2613）；
        //   else 清 +2154=0 与 sub_41A590(+2136, 0)（2617-2618）；
        //   主体含 sub_431920 建多枚 .ani（含 WindmillDust3.ani 与 Character/Swordman/ 系复用）、
        //   vt+1140/vt+1160 多次取参、vt+876 位移链、sub_44B6C0/sub_44E1F0/sub_45FE80 粒子挂接三件套；
        //   LABEL_630 为 j__free(v495[0]) 释放 string 的 return 点（2716-2719）
        case 7:
          if ( fld_e1639 == 7 )
          {
            --*(this + 1724);
            fld_e2154 = *(this + 2154);
            if ( fld_e2154 != 0 )
            {
              if ( fld_e2154 == 1 || fld_e2154 == 2 )
              {
                pThis_858 = sub_41A5E0((unsigned int)(this + 2136));
                if ( pThis_858 < sub_41A5E0((unsigned int)(this + 2062)) )
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
          fld_e21542 = *(this + 2154);
          if ( fld_e21542 != 0 )
          {
            if ( fld_e21542 == 1 || fld_e21542 == 2 )
            {
              pThis_8582 = sub_41A5E0((unsigned int)(this + 2136));
              sub_41A590((unsigned int)(this + 2136), v434, pThis_8582 + 1);
              pThis_6683 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
              *(this + 2140) = sub_4C0DF0(0) + pThis_6683;
              v436 = sub_4C0DF0(1);
              v437 = *this;
              *(this + 2141) = *(this + 2140) + v436;
              (*(void (/*thiscall*/ **)(int *, uint32_t))(v437 + 196))(this, *(uint32_t *)(*(this + 1554) + 20));
              fld_e308 = *(this + 30);
              fld_e21543 = sub_491C70(fld_e308, *(this + 2154) != 1 ? 3 : 0);
              sub_493A60(fld_e308, fld_e21543);
              fld_e2156 = *(this + 2156);
              if ( fld_e2156 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2156 + 80))() != 0 )
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
            else if ( fld_e21542 == 3 )
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
            fld_e21562 = *(this + 2156);
            if ( fld_e21562 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e21562 + 80))() != 0 )
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
        // ── [段 35] 第三重 case 8：★★ 拔枪态（约 460 行）—— +8577/+2136 状态位与枪种分支 ──
        //   fld_e1639==8 时读 +1757 与 +8577；sub_41A5E0(+8577) 1/2 时 sub_41A590 写 2/3（2730-2740）；
        //   后续含大量 vt+1160/vt+1140 取参与动画建件（含 ShootEffect 与 LaserRifle 系）；
        //   （3177）this[2129] != -1 且 != 11 时 vt+1328(0) 收束后 return
        case 8:
          if ( fld_e1639 == 8 )
          {
            pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
            pThis_2181 = (unsigned int)this + 8577;
            pThis_21812 = (unsigned int)this + 8577;
            if ( pThis_6DD != 0 )
            {
              v343 = sub_41A5E0(pThis_21812);
              pThis_21813 = (unsigned int)this + 8577;
              if ( v343 == 1 )
              {
                sub_41A590(pThis_21813, v344, 2);
              }
              else
              {
                v346 = sub_41A5E0(pThis_21813);
                pThis_21814 = (unsigned int)this + 8577;
                if ( v346 == 2 )
                {
                  sub_41A590(pThis_21814, v347, 3);
                }
                else if ( sub_41A5E0(pThis_21814) == 3 )
                {
                  sub_41C150((unsigned int)this + 8577, v349, 4);
                }
              }
            }
            else
            {
              sub_41A590(pThis_21812, v341, 1);
            }
          }
          else
          {
            v328 = *(uint32_t *)(pArg3 + 4);
            if ( v328 != 0 && (unsigned int)((*(uint32_t *)(pArg3 + 8) - v328) >> 2) > 1 )
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
            fld_e21294 = *(this + 2129);
            if ( fld_e21294 == 5 || fld_e21294 == 47 || fld_e21294 == 53 )
            {
              pThis_2181 = (unsigned int)this + 8577;
              sub_41A590((unsigned int)this + 8577, v327, 2);
              fld_e21295 = *(this + 2129);
              if ( fld_e21295 == 5 )
              {
                (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 5);
                sub_47DCD0(this, -1);
              }
              else if ( fld_e21295 == 53 )
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
              pThis_2181 = (unsigned int)this + 8577;
              sub_41A590((unsigned int)this + 8577, v327, 0);
            }
            sub_41A590((unsigned int)(this + 2136), v333, 0);
            if ( v330 != -1 )
              (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*this + 992))(this, v330, 0);
          }
          if ( sub_41A5E0(pThis_2181) == 0 || sub_41A5E0(pThis_2181) == 2 )
            *((uint8_t *)this + 8576) = 0;
          if ( sub_41A5E0(pThis_2181) != 1 && sub_41A5E0(pThis_2181) != 3 )
            goto LABEL_542;
          *((uint8_t *)this + 8596) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4) == 1;
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
          if ( sub_41A5E0(pThis_2181) == 1 )
          {
            v350 = *this;
            fld_e1554 = (int *)*(this + 1554);
            if ( *((uint8_t *)this + 8596) != 0 )
              v352 = fld_e1554[1];
            else
              v352 = *fld_e1554;
          }
          else
          {
            if ( sub_41A5E0(pThis_2181) != 3 )
              goto LABEL_524;
            v350 = *this;
            fld_e15542 = *(this + 1554);
            if ( *((uint8_t *)this + 8596) != 0 )
              v352 = *(uint32_t *)(fld_e15542 + 12);
            else
              v352 = *(uint32_t *)(fld_e15542 + 8);
          }
          (*(void (/*stdcall*/ **)(int))(v350 + 196))(v352);
// ── [段 36] 公共尾第三重 case 8 之中段汇合点 LABEL_524（457 态切换链）──
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
          if ( sub_41A5E0(pThis_2181) == 1 )
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
          if ( sub_41A5E0(pThis_2181) == 3 || sub_41A5E0((unsigned int)(this + 2136)) == 0 )
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
          pThis_8583 = sub_41A5E0((unsigned int)(this + 2136));
          sub_41A590((unsigned int)(this + 2136), v363, pThis_8583 + 1);
// ── [段 37] 公共尾第三重 case 8 之汇合点 LABEL_542（缓动/换弹 457 态）──
LABEL_542:
          if ( sub_41A5E0(pThis_2181) == 4 )
          {
            v364 = *this;
            v365 = sub_4C0EB0(this);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v364 + 888))(this, 0, 0, 1000, v365);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));
            sub_4926A0(*(this + 30));
            fld_e21296 = *(this + 2129);
            if ( fld_e21296 != 5 && fld_e21296 != 53 )
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                this,
                "R_GN_FINAL_SHOT",
                -1,
                0,
                0);
            if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 23) != 0
              && (*(int (/*thiscall*/ **)(int *))(*this + 1096))(this) == 0 )
            {
              pMem = (void *)sub_42FCB0(228);
              v506 = 51;
              if ( pMem != nullptr )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  LOBYTE(fld_e91) = (uint8_t)this + 108;
                else
                  fld_e91 = *(this + 91);
                v368 = sub_431920(fld_e91, (char)"Effect/Animation/ReduceRevolverReload1.ani", 1);
              }
              else
              {
                v368 = 0;
              }
              v506 = -1;
              pMem = (void *)sub_44B6C0(284);
              v506 = 52;
              if ( pMem != nullptr )
                v369 = (int *)sub_44E1F0(v368, 1);
              else
                v369 = nullptr;
              fld_e297 = *(this + 29);
              v506 = -1;
              sub_45FE80(fld_e297, (int)v369, 2, 0, (int)v369, (int)this, 0);
              v371 = *v369;
              v372 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
              (*(void (/*thiscall*/ **)(int *, int))(v371 + 148))(v369, v372);
              v373 = *v369;
              v374 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
              v375 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v374);
              v376 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v375);
              (*(void (/*thiscall*/ **)(int *, int))(v373 + 112))(v369, v376);
              pMem = (void *)sub_42FCB0(228);
              v506 = 53;
              if ( pMem != nullptr )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  LOBYTE(fld_e912) = (uint8_t)this + 108;
                else
                  fld_e912 = *(this + 91);
                v378 = sub_431920(fld_e912, (char)"Effect/Animation/ReduceRevolverReload2.ani", 1);
              }
              else
              {
                v378 = 0;
              }
              v506 = -1;
              pMem = (void *)sub_44B6C0(284);
              v506 = 54;
              if ( pMem != nullptr )
                v379 = (int *)sub_44E1F0(v378, 1);
              else
                v379 = nullptr;
              fld_e298 = *(this + 29);
              v506 = -1;
              sub_45FE80(fld_e298, (int)v379, 2, 0, (int)v379, (int)this, 0);
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
          fld_e21297 = *(this + 2129);
          if ( fld_e21297 == 5 || fld_e21297 == 47 || fld_e21297 == 53 )
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
              fld_e309 = *(this + 30);
              v412 = sub_491C70(fld_e309, 2);
              sub_493A60(fld_e309, v412);
              fld_e21298 = *(this + 2129);
              switch ( fld_e21298 )
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
                      pMem = (void *)sub_42FCB0(228);
                      v506 = 55;
                      if ( pMem != nullptr )
                      {
                        pThis_5A17 = unknown_libname_2(this + 90);
                        v418 = sub_431920(pThis_5A17, (char)"Effect/Animation/TurningShoot.ani", 1);
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
          else if ( fld_e21297 == 11 )
          {
            if ( sub_41A5E0((unsigned int)this + 8577) == 0 || sub_41A5E0((unsigned int)this + 8577) == 2 )
            {
              fld_e21299 = *(this + 2129);
              v393 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int))(*this + 1160))(this, *(this + 2129), 0, v393);
              v394 = sub_47EF20(fld_e21299, -1, -1, 11, v485);
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
            // ── [段 38] 第三重 case 7 之中段：+8577 与 +2136 双状态位联合判定（连发/换弹节流）──
            else if ( sub_41A5E0((unsigned int)this + 8577) == 1 && sub_41A5E0((unsigned int)(this + 2136)) == 1
                   || sub_41A5E0((unsigned int)this + 8577) == 3 )
            {
              if ( *((uint8_t *)this + 8596) != 0 )
              {
                if ( *(this + 2151) == 0 )
                {
                  pMem = (void *)sub_42FCB0(228);
                  v506 = 56;
                  if ( pMem != nullptr )
                  {
                    pThis_5A18 = unknown_libname_2(this + 90);
                    // ── [段 39] 公共尾第三重 case 8 之快速射击：FastShootDown/FastShootUp.ani 两件 ──
                    v389 = sub_431920(pThis_5A18, (char)"Effect/Animation/FastShootDown.ani", 1);
                  }
                  else
                  {
                    v389 = 0;
                  }
                  v506 = -1;
                  *(this + 2151) = v389;
                }
                fld_e2151 = *(this + 2151);
              }
              else
              {
                if ( *(this + 2150) == 0 )
                {
                  pMem = (void *)sub_42FCB0(228);
                  v506 = 57;
                  if ( pMem != nullptr )
                  {
                    pThis_5A19 = unknown_libname_2(this + 90);
                    v392 = sub_431920(pThis_5A19, (char)"Effect/Animation/FastShootUp.ani", 1);
                  }
                  else
                  {
                    v392 = 0;
                  }
                  v506 = -1;
                  *(this + 2150) = v392;
                }
                fld_e2151 = *(this + 2150);
              }
              if ( sub_41A5E0((unsigned int)this + 8577) == 1 )
                (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                  this,
                  1,
                  fld_e2151,
                  0,
                  0,
                  0,
                  0);
              else
                (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 204))(
                  this,
                  1,
                  fld_e2151,
                  32,
                  8,
                  0,
                  0);
            }
          }
          else if ( fld_e21297 == 26 && sub_41A5E0((unsigned int)this + 8577) == 0 )
          {
            fld_e212910 = *(this + 2129);
            v397 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
            (*(void (/*thiscall*/ **)(int *, uint32_t, int, int))(*this + 1160))(this, *(this + 2129), 1, v397);
            v508 = (double)(int)sub_47EF20(fld_e212910, -1, -1, 11, v485) * 0.0099999998 + 1.0;
            v398 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
            v399 = (uint64_t)((double)sub_495500(v398) * v508);
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(this, 0, 0, v399, v399);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 144))(this, *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8));
            pMem = (void *)sub_42FCB0(228);
            v506 = 58;
            if ( pMem != nullptr )
            {
              pThis_5A20 = unknown_libname_2(this + 90);
              // ── [段 40] 公共尾第三重 case 8 之反击射击：CounterShoot.ani 建件 ──
              v401 = sub_431920(pThis_5A20, (char)"Effect/Animation/CounterShoot.ani", 1);
            }
            else
            {
              v401 = 0;
            }
            v506 = -1;
            pMem = (void *)sub_44B6C0(284);
            // ── [段 41] 第三重 case 8 之收尾段：建件 + sub_45FE80 挂接 + vt+112 落坐标链 ──
            v506 = 59;
            if ( pMem != nullptr )
              v402 = (int *)sub_44E1F0(v401, 1);
            else
              v402 = nullptr;
            fld_e299 = *(this + 29);
            v506 = -1;
            sub_45FE80(fld_e299, (int)v402, 2, 0, (int)v402, (int)this, 0);
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
          fld_e212911 = *(this + 2129);
          if ( fld_e212911 != -1 && fld_e212911 != 11 )
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);
          return;
        // ── [段 42] 第三重 case 10：★ 副武器状态机（this[1953]==0 时按 this[1954] 分派）──
        //   43 号特例（3187 起）；goto LABEL_482 走公共尾
        case 10:
          if ( *(this + 1953) == 0 )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *(this + 1954));
            fld_e1954 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 1954));
            fld_e19542 = *(this + 1954);
            if ( fld_e19542 == 43 )
            {
              fld_e1952 = *(this + 1952);
              if ( fld_e1952 != 0 )
              {
                if ( fld_e1952 == 1 )
                {
                  v451 = sub_47EF20(0, fld_e1954, -1, -1, 11);
                  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 944))(this, 1, v451);
                  *((uint8_t *)this + 9500) = 1;
                  *((uint8_t *)this + 9501) = 0;
                  *((uint8_t *)this + 9502) = 0;
                  sub_698F90((int)(this + 2372), v451, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
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
            else if ( fld_e19542 == 45 )
            {
              fld_e19522 = *(this + 1952);
              if ( fld_e19522 != 0 )
              {
                if ( fld_e19522 == 1 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
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
            else if ( fld_e19542 == 50 && *(this + 1952) == 1 )
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
                pMem = (void *)sub_42FCB0(228);
                v506 = 62;
                if ( pMem != nullptr )
                {
                  pThis_5A21 = unknown_libname_2(this + 90);
                  v460 = sub_431920(pThis_5A21, (char)Buffer, 1);
                }
                else
                {
                  v460 = 0;
                }
                v506 = -1;
                v507 = v457 * 0.0018867925;
                sub_4922F0(v507);
                pMem = (void *)sub_44B6C0(284);
                v506 = 63;
                if ( pMem != nullptr )
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
        // ── [段 43] 第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表 ──
        //   vt+196(this[1812]) + sub_491C70/+493A60/+4939E0(+30 对象) 三连帧同步后 return
        case 12:
          fld_e2163 = *(this + 2163);
          if ( fld_e2163 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2163 + 80))() != 0 )
          {
            v474 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 37, -1);
            (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
            *(this + 114) = sub_47EF20(37, 1, v474, -1, 11);
          }
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1812));
          fld_e3010 = *(this + 30);
          fld_e2160 = sub_491C70(fld_e3010, *(this + 2160));
          sub_493A60(fld_e3010, fld_e2160);
          sub_4939E0(*(this + 30), 1);
          return;
        // ── [段 44] 第三重 case 14：★ 技能号语音小表 —— switch(this[1991])（175/176/1/…）──
        case 14:
          fld_e1991 = *(this + 1991);
          switch ( fld_e1991 )
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
    // ── [段 45] 第二重 case 23：★ 移动射击（GN_MOVESHOT）—— fld_e1639==23 与非 23 两支 ──
    //   23 支：sub_699000(this+1640) + sub_4C0DF0(0/1) 双时长 + sub_41A5E0(this+2083) 合成 +2140/+2141 时刻；
    //   非 23 支：vt+1160(15) + vt+672(3)+sub_4954C0 帧长 + sub_47EF20(1)/(2)/(3) 三读表写 +2361/+2362；
    //   vt+876 双段（0:143,119,1 / 1:114,95,1）+ vt+896(4,4) + vt+888 帧长；
    //   一长串槽位初始化（+2129=15/+2359=4/+2360=0/+2140=-1/+2141=0/+2362=-1 等）后播 GN_MOVESHOT；
    //   末段 sub_4C2020(Block, vt+1096()) 组串 + vt+212 播报；goto LABEL_482
    case 23:
      if ( fld_e1639 == 23 )
      {
        pThis_6684 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
        *(this + 2140) = sub_4C0DF0(0) + pThis_6684;
        pThis_823 = sub_41A5E0((unsigned int)(this + 2083));
        *(this + 2141) = pThis_823 + *(this + 2140) + *(this + 2361) + sub_4C0DF0(1);
        LOBYTE(nArg4) = 0;
        LOBYTE(nArg5) = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 15);
        *(float *)&pThis_88C3 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 15));
        v304 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
        v305 = sub_4954C0(v304);
        v306 = sub_47EF20(1, pThis_88C3, -1, -1, 11) + v305;
        *(this + 2361) = sub_47EF20(2, pThis_88C3, -1, -1, 11);
        v307 = (void *)sub_47EF20(3, pThis_88C3, -1, -1, 11);
        v308 = *this;
        pMem = v307;
        v309 = (double)(int)v307;
        fld_e15543 = *(this + 1554);
        *((float *)this + 2363) = v309 * 0.000099999997;
        (*(void (/*thiscall*/ **)(int *, uint32_t))(v308 + 196))(this, *(uint32_t *)(fld_e15543 + 92));
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
        Block5 = (void **)Block[0];
        if ( v504 < 0x10 )
          Block5 = Block;
        (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, Block5, -1, 0, 0);
        v506 = -1;
        sub_501490(v499);
      }
      goto LABEL_482;
    // ── [段 46] 第二重 case 25：★ 副武器状态 27/28/29 三支取参（sub_4B1C40/sub_495540 帧长链）──
    //   fld_e15544 与 fld_e304 交替写；goto LABEL_482
    case 25:
      v317 = **(uint32_t **)(pArg3 + 4);
      if ( v317 == 27 )
      {
        *(this + 2366) = 60002;
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ROBOT_SET_01", -1, 0, 0);
      }
      else if ( **(uint32_t **)(pArg3 + 4) == 28 )
      {
        v318 = *this;
        *(this + 2366) = 60003;
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v318 + 212))(this, "ROBOT_SET_02", -1, 0, 0);
      }
      else if ( **(uint32_t **)(pArg3 + 4) == 29 )
      {
        *(this + 2366) = 60004;
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ROBOT_SET_03", -1, 0, 0);
      }
      *(this + 2368) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
      *(this + 2369) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
      v319 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 1160))(this, v317, 0, v319);
      *(this + 2367) = sub_47EF20(v317, -1, -1, 11, v485);
      fld_e15544 = *(uint32_t *)(*(this + 1554) + 128);
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
      fld_e304 = COERCE_FLOAT(sub_4B1C40(fld_e15544));
      pMem = *(void **)(*(this + 30) + 36);
      v321 = *this;
      v485 = 3;
      *(float *)&pThis_88C3 = (double)(int)pMem / (double)SLODWORD(fld_e304);
      v322 = (*(int (/*thiscall*/ **)(int *))(v321 + 672))(this);
      fld_e304 = COERCE_FLOAT(sub_495540(v322));
      (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, int, uint32_t))(v321 + 888))(
        this,
        (uint64_t)((double)SLODWORD(fld_e304) * *(float *)&pThis_88C3) >> 32,
        0,
        0,
        1000,
        (uint64_t)((double)SLODWORD(fld_e304) * *(float *)&pThis_88C3));
      (*(void (/*thiscall*/ **)(int *, void *, int))(*this + 992))(this, pMem, 1);
      *(this + 2371) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12);
      goto LABEL_482;
    // ── [段 47] 第二重 case 26：★ 激光炮/加特林（this[2129] 40 / 39 两支）──
    //   先 sub_4926A0 与 vt+196(this[1554]+64) 双复位；40 支 sub_4C4890(this,4,16) + vt+876 位移；
    //   39 支 vt+1160(39) + sub_47DD30 + sub_4C4890(this,2,16) 后建两枚动画（+2345/+2346 惰性）；
    //   （3630）vt+152+sub_432E50 朝向 + dword_8F8270 表 + vt+924(this,2) 取件；LABEL_232 为收束点
    case 26:
      *(this + 2129) = **(uint32_t **)(pArg3 + 4);
      fld_e15545 = *(this + 1554);
      *(this + 2242) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
      v53 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
      sub_4926A0(*(uint32_t *)(fld_e15545 + 64));
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 64));
      fld_e212912 = *(this + 2129);
      if ( fld_e212912 == 40 )
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
      else if ( fld_e212912 == 39 )
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 39);
        sub_47DD30(this);
        // ── [段 48] 第二重 case 26 之 39 号支：vt+1160(39) + sub_47DD30 + sub_4C4890(this,2,16) ──
        sub_4C4890(this, 2, 16);
        if ( *(this + 2345) == 0 )
        {
          pMem = (void *)sub_42FCB0(228);
          v506 = 4;
          if ( pMem != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C = sub_431920(
                      (uint8_t)this + 108,
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeEffect.ani",
                      1);
            else
              pThis_6C = sub_431920(
                      *(this + 91),
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeEffect.ani",
                      1);
          }
          else
          {
            pThis_6C = 0;
          }
          v506 = -1;
          *(this + 2345) = pThis_6C;
        }
        // ── [段 49] 第二重 case 26 之第二枚惰性件（+2346，与 +2345 成对）──
        if ( *(this + 2346) == 0 )
        {
          pMem = (void *)sub_42FCB0(228);
          v506 = 5;
          if ( pMem != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C2 = sub_431920(
                      (uint8_t)this + 108,
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeSpark.ani",
                      1);
            else
              pThis_6C2 = sub_431920(*(this + 91), (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeSpark.ani", 1);
          }
          else
          {
            pThis_6C2 = 0;
          }
          v506 = -1;
          *(this + 2346) = pThis_6C2;
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
        fld_e2356 = sub_423A80(100, 400, v53, *(this + 2356));
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, int, int))(*this + 876))(
          this,
          0,
          fld_e2356,
          0,
          0,
          -500,
          1);
        if ( fld_e2356 > 150 )
        {
          pMem = (void *)sub_42FCB0(228);
          v506 = 6;
          if ( pMem != nullptr )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              LOBYTE(fld_e913) = (uint8_t)this + 108;
            else
              fld_e913 = *(this + 91);
            // ── [段 50] 第二重 case 26 之 39 号支末段：TurningShoot.ani 建件（+2129==39 与 40 双态）──
            v59 = sub_431920(fld_e913, (char)"Effect/Animation/TurningShoot.ani", 1);
          }
          else
          {
            v59 = 0;
          }
          v506 = -1;
          pMem = (void *)sub_44B6C0(284);
          v506 = 7;
          if ( pMem != nullptr )
            v60 = (int *)sub_44E1F0(v59, 1);
          else
            v60 = nullptr;
          fld_e2910 = *(this + 29);
          v506 = -1;
          sub_45FE80(fld_e2910, (int)v60, 2, 0, (int)v60, (int)this, 0);
          v62 = *v60;
          v63 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
          v64 = sub_432E50(v63);
          (*(void (/*thiscall*/ **)(int *, int))(v62 + 148))(v60, v64);
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )
            v65 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 130;
          else
            v65 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 130;
          v66 = *v60;
          pThis_88C3 = v65;
          v67 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
          v68 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v67);
          (*(void (/*thiscall*/ **)(int *, int, int))(v66 + 112))(v60, pThis_88C3, v68);
        }
      }
      v69 = *this;
      v70 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);
      v71 = sub_432E50(v70);
      (*(void (/*thiscall*/ **)(int *, int))(v69 + 896))(this, v71);
      pObj3 = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];
      v73 = *(uint32_t *)pObj3;
      v74 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
      v75 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v74);
      (*(void (/*thiscall*/ **)(int, int))(v73 + 40))(pObj3, v75);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 12))(pObj3, 0);
      (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)pObj3 + 92))(pObj3, &v501);
      v506 = 8;
      sub_4600B0((void *)*(this + 29), 2, 0, (int)&v501);
LABEL_232:
      v506 = -1;
      sub_5E5260((void **)&v501);
      goto LABEL_482;
    // ── [段 51] 第二重 case 27：单支处理（goto LABEL_482）──
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
    // ── [段 52] 第二重 default：直接 goto LABEL_482 走公共尾（未知动作号静默）──
    default:
      goto LABEL_482;
  }
}

