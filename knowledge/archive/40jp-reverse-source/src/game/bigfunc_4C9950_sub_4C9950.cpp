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
  int nItemCtx; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
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
  int nItemCtx_; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
  uint32_t *pThis_91D; // edi
  int n; // ebx
  uint32_t *pThis_930; // edi
  int ii; // ebx
  uint32_t *pThis_9132; // edi
  int jj; // ebx
  int nItemCtx_2; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
  uint32_t *pThis_929; // edi
  int kk; // ebx
  int v49; // edx
  int v50; // edi
  int v51; // eax
  int fld_e15545; // eax
  int v53; // edi
  int nItemCtx_3; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
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
  int pTarget7252; // edi  | +0x1C54 → 当前目标（★已确证偏移语义 this+7252）（证据 va=确证语义）（IRDActiveObject·基类）
  long double pHostComp112; // st7  | +0x0070 → 宿主对象指针（IRDActiveObject·基类；va=004D6970）
  uint64_t v78; // rax
  int pAnimObj; // ecx  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）
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
  int pAnimObj_; // edi  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）
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
  int nDmgCapCtx; // ecx  | +0x2308 → ★ 上限上下文（0x4C0A30 与 +8516==12 组合判定）（CNGunner；va=004C0A30）
  uint64_t v226; // rax
  int v227; // eax
  int v228; // eax
  int v229; // edx
  int v230; // eax
  int v231; // eax
  int nDmgCapCtx_; // eax  | +0x2308 → ★ 上限上下文（0x4C0A30 与 +8516==12 组合判定）（CNGunner；va=004C0A30）
  int v233; // ebx
  int v234; // eax
  int v235; // eax
  char pThis_5A; // al
  int v237; // eax
  int nDmgCapCtx_2; // eax  | +0x2308 → ★ 上限上下文（0x4C0A30 与 +8516==12 组合判定）（CNGunner；va=004C0A30）
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
  int nDmgCapCtx_3; // eax  | +0x2308 → ★ 上限上下文（0x4C0A30 与 +8516==12 组合判定）（CNGunner；va=004C0A30）
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
  int nDmgCapCtx_4; // ecx  | +0x2308 → ★ 上限上下文（0x4C0A30 与 +8516==12 组合判定）（CNGunner；va=004C0A30）
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
  int nItemCtx_4; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
  unsigned int pThis_2181; // edi
  int v333; // edx
  int nItemCtx_5; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
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
  int nItemCtx_6; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
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
  int nItemCtx_7; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
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
  int pAnimObj_2; // edi  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）
  int v412; // eax
  int nItemCtx_8; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
  int v414; // edi
  int v415; // eax
  int v416; // eax
  char pThis_5A17; // al
  int v418; // eax
  int nItemCtx_9; // eax  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
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
  int pAnimObj_3; // edi  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）
  int fld_e21543; // eax
  int fld_e2156; // eax
  int pAnimObj_4; // eax  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）
  int v442; // ecx
  int v443; // edi
  int v444; // ebx
  int fld_e2163; // eax
  int pAnimObj_5; // edi  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）
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
  int nItemCtx_10; // [esp-10h] [ebp-17Ch]  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
  int nItemCtx_11; // [esp-10h] [ebp-17Ch]  | +0x2144 → ★ 弹药/道具上下文（0x4C0A30: ==12 且 +8968==1 组合；0x4C0760 同址读）（CNGunner；va=004C0A30）
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
  int nBigState; // [esp+Ch] [ebp-160h]  | +0x199C → ★ 枪手大状态 ID（CNGunner；va=004C0A30）
  int v488; // [esp+10h] [ebp-15Ch] BYREF
  float pAnimObj_6; // [esp+14h] [ebp-158h]  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主）【基类字段】（CNGunner；va=00499020）
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
  dword_796E502 = dword_796E50;  // 帧时刻快照源
  nBigState = *(this + 1639);  // 读字段 fld_e1639 = this[1639]
  if ( *(float *)&nArg2 == 0.0 || nArg2 == 11 || nArg2 == 6 )  // 条件判定
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 && *((uint8_t *)this + 9500) != 0 )  // 条件判定
    {
      fld_e2378 = *(this + 2378);  // 读字段 fld_e2378 = this[2378]
      if ( sub_699000((int)(this + 2372)) < fld_e2378 )  // 【clock_now(clk)】
      {
        v7 = *this;  // （表达式续行/复合语句）
        pThis_944 = sub_4238E0(this + 2372);  // sub_4238E0 —— 变焦剩余时间：remaining = clk->duration(+24) - now（≤0 返 0）。
        (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 944))(this, 1, pThis_944);  // （表达式续行/复合语句）
      }
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) != 0 )  // 否则条件分支
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*this + 944))(this, 0, -1);  // （表达式续行/复合语句）
  }
  // ── [段 2] 状态 16 / 22 归一与抓取体同步：+2336 目标存活时抄其坐标到局部 ──
  //   状态 22 且 this[2129]==14 时不归一；+2336 对象 vt+308 判活后 vt+120/124 取坐标
  fld_e16392 = nBigState;
  if ( nBigState == 16 )  // 判定字段 this[1639] == 16
  {
    if ( *((uint8_t *)this + 8692) == 0 )  // 判定 this[8692] == 0（uint8）
    {
LABEL_12:  // 标签 LABEL_12：合流点
      nArg22 = nArg2;
      goto LABEL_13;  // 跳转合流点 LABEL_13
    }
  }
  else if ( nBigState != 22 || *(this + 2129) != 14 )  // 判定字段 this[1639]（大状态/子状态门）
  {
    goto LABEL_12;  // 跳转合流点 LABEL_12
  }
  nArg22 = nArg2;
  if ( nArg2 != 22 )  // 条件判定
  {
    fld_e2336 = *(this + 2336);  // 读字段 fld_e2336 = this[2336]
    if ( fld_e2336 != 0 )  // 判定字段 this[2336] != 0
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2336 + 308))(fld_e2336) != 0 )  // 条件判定
      {
        fld_e23362 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2336) + 120))(*(this + 2336));  // （表达式续行/复合语句）
        fld_e23363 = *(this + 2336);  // 读字段 fld_e23363 = this[2336]
        pThis_22 = fld_e23362;
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e23363 + 124))(fld_e23363);  // （表达式续行/复合语句）
        fld_e23364 = *(this + 2336);  // 读字段 fld_e23364 = this[2336]
        pThis_88C3 = v14;
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e23364 + 128))(fld_e23364);  // （表达式续行/复合语句）
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 2336) + 136))(  // 条件判定
               *(this + 2336),  // （上一表达式的参数/条件续行）
               pThis_22,  // （上一表达式的参数/条件续行）
               pThis_88C3,  // （上一表达式的参数/条件续行）
               0) != 0  // （上一表达式的参数/条件续行）
          && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2336) + 132))(*(this + 2336), v16) != 0 )  // （上一表达式的参数/条件续行）
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2336) + 108))(  // （表达式续行/复合语句）
            *(this + 2336),  // （上一表达式的参数/条件续行）
            pThis_22,  // （上一表达式的参数/条件续行）
            pThis_88C3,  // （上一表达式的参数/条件续行）
            v16);  // （上一表达式的参数/条件续行）
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)*(this + 2336) + 140))(  // 否则条件分支
                    *(this + 2336),  // （上一表达式的参数/条件续行）
                    &pThis_22,  // （上一表达式的参数/条件续行）
                    &pThis_88C3,  // （上一表达式的参数/条件续行）
                    pThis_22,  // （上一表达式的参数/条件续行）
                    pThis_88C3,  // （上一表达式的参数/条件续行）
                    100,  // （上一表达式的参数/条件续行）
                    1,  // （上一表达式的参数/条件续行）
                    1) != 0 )  // （上一表达式的参数/条件续行）
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2336) + 108))(  // （表达式续行/复合语句）
            *(this + 2336),  // （上一表达式的参数/条件续行）
            pThis_22,  // （上一表达式的参数/条件续行）
            pThis_88C3,  // （上一表达式的参数/条件续行）
            v16);  // （上一表达式的参数/条件续行）
        }
        else  // 否则分支
        {
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2336) + 108))(  // （表达式续行/复合语句）
            *(this + 2336),  // （上一表达式的参数/条件续行）
            *(this + 2337),  // （上一表达式的参数/条件续行）
            *(this + 2338),  // （上一表达式的参数/条件续行）
            *(this + 2339));  // （上一表达式的参数/条件续行）
        }
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2336) + 724))(*(this + 2336)) == 0 )  // 条件判定
        {
          v502 = 0.0;  // v502 = 0.0（浮点初值）
          v503 = 0;
          *(float *)&v504 = 0.0;  // （表达式续行/复合语句）
          v506 = 0;
          pMem = (void *)4;  // （表达式续行/复合语句）
          sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
          pMem = nullptr;  // pMem = 空指针
          sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
          pMem = nullptr;  // pMem = 空指针
          sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
          pMem = (void *)100;  // （表达式续行/复合语句）
          sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
          pMem = (void *)10;  // （表达式续行/复合语句）
          sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
          (*(void (/*thiscall*/ **)(uint32_t, int, float *, int, uint32_t))(*(uint32_t *)*(this + 2336) + 560))(  // （表达式续行/复合语句）
            *(this + 2336),  // （上一表达式的参数/条件续行）
            4,  // （上一表达式的参数/条件续行）
            &v501,  // （上一表达式的参数/条件续行）
            2,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2336) + 564))(*(this + 2336));  // （表达式续行/复合语句）
          v506 = -1;
          sub_5E5260((void **)&v501);  // sub_5E5260 —— 清理临时缓冲
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2336) + 596))(*(this + 2336), 1);  // （表达式续行/复合语句）
      fld_e2340 = *(this + 2340);  // 读字段 fld_e2340 = this[2340]
      *(this + 2336) = 0;  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2340 + 76))(fld_e2340, 0);  // （表达式续行/复合语句）
      fld_e16392 = nBigState;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);  // （表达式续行/复合语句）
    (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);  // （表达式续行/复合语句）
    nArg22 = nArg2;
  }
LABEL_13:  // 标签 LABEL_13：合流点
  // ── [段 3] 第一重 switch(fld_e16392)：★ 收招/回挂主表（8/15/17/18/20/22/23/25/26/27）──
  switch ( fld_e16392 )  // 分派 switch
  {
    // ── [段 4] 第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派 ──
    //   LABEL_43/44 为汇合点；nArg22 != 0 时跳 LABEL_108（第一重出口）；
    //   否则 sub_4C2020(v494, vt+1096() 枪种) 组串后 LABEL_70 经 vt+212 播报（+498<0x10 用内联缓冲）
    case 8:  // case 8 分派：第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派
      nItemCtx = *(this + 2129);  // 读字段 fld_e2129 = this[2129]
      switch ( nItemCtx )  // 分派 switch
      {
        case 11:  // case 11 分派：第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派
          pThis_866 = this + 2150;  // （表达式续行/复合语句）
          for ( i = 2; i != 0; --i )  // 循环（遍历）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_866++);  // （表达式续行/复合语句）
          goto LABEL_43;  // 跳转合流点 LABEL_43
        case 5:  // case 5 分派：第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派
          if ( *((uint8_t *)this + 8608) == 0 )  // 判定 this[8608] == 0（uint8）
            goto LABEL_44;  // 跳转合流点 LABEL_44
          if ( nArg22 != 8 )  // 条件判定
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2153));  // （表达式续行/复合语句）
LABEL_43:  // 标签 LABEL_43：合流点
            nArg22 = nArg2;
LABEL_44:  // 标签 LABEL_44：合流点
            if ( nArg22 != 8 )  // 条件判定
              *(this + 2129) = -1;  // （表达式续行/复合语句）
          }
          break;  // 跳出本分支
        case 26:  // case 26 分派：第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派
          if ( nArg22 != 8 )  // 条件判定
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);  // （表达式续行/复合语句）
            sub_49C620(3, 1, 0);  // sub_49C620 —— 命令下发包装（组 id = this+4，值重复两遍）
            sub_49C5F0(3, 0, 0, 500);  // sub_49C5F0 —— 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
            goto LABEL_43;  // 跳转合流点 LABEL_43
          }
          break;  // 跳出本分支
        case 53:  // case 53 分派：第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派
          if ( nArg22 != 8 )  // 条件判定
          {
            (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);  // （表达式续行/复合语句）
            goto LABEL_43;  // 跳转合流点 LABEL_43
          }
          break;  // 跳出本分支
        default:  // 未列出的值 → 兜底
          goto LABEL_44;  // 跳转合流点 LABEL_44
      }
      if ( nArg22 != 0 )  // 条件判定
        goto LABEL_108;  // 跳转合流点 LABEL_108
      v498 = 15;
      v497 = 0;
      LOBYTE(v495[0]) = 0;  // （表达式续行/复合语句）
      v21 = *this;  // （表达式续行/复合语句）
      v506 = 1;
      v22 = (*(int (/*thiscall*/ **)(int *))(v21 + 1096))(this);  // （表达式续行/复合语句）
      sub_4C2020((int)v494, v22);
      v23 = (void **)v495[0];  // （表达式续行/复合语句）
      if ( v498 < 0x10 )  // 条件判定
        v23 = v495;
      goto LABEL_70;  // 跳转合流点 LABEL_70
    // ── [段 5] 第一重 case 15：回挂 +2170 起 2 件动画（vt+208）──
    case 15:  // case 15 分派：第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派
      pThis_87A = this + 2170;  // （表达式续行/复合语句）
      for ( j = 2; j != 0; --j )  // 循环（遍历）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_87A++);  // （表达式续行/复合语句）
      goto LABEL_108;  // 跳转合流点 LABEL_108
    // ── [段 6] 第一重 case 17/18：分支处理（VT_SM 组），goto LABEL_108（第一重出口）──
    case 17:  // case 17 分派：第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派
      (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);  // （表达式续行/复合语句）
      goto LABEL_108;  // 跳转合流点 LABEL_108
    case 18:  // case 18 分派：第一重 case 8：★ 拔枪/换弹收尾 —— 按 this[2129] 子状态 11/5/26/53 分派
      if ( nArg22 == 18 )  // 条件判定
        goto LABEL_108;  // 跳转合流点 LABEL_108
      fld_e2175 = *(this + 2175);  // 读字段 fld_e2175 = this[2175]
      if ( fld_e2175 != 0 )  // 判定字段 this[2175] != 0
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2175 + 308))(fld_e2175) != 0 )  // 条件判定
        {
          if ( (fld_e21752 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2175) + 120))(*(this + 2175)),  // 条件判定
                pObj12 = *(this + 2175),  // （上一表达式的参数/条件续行）
                pThis_88C3 = fld_e21752,  // （上一表达式的参数/条件续行）
                v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 124))(pObj12),  // （上一表达式的参数/条件续行）
                pObj11 = *(this + 2175),  // （上一表达式的参数/条件续行）
                pThis_22 = v29,  // （上一表达式的参数/条件续行）
                (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj11 + 136))(pObj11, pThis_88C3, v29, 0) != 0)  // （上一表达式的参数/条件续行）
            && (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2175) + 132))(*(this + 2175), 0) != 0  // （上一表达式的参数/条件续行）
            || (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(*(uint32_t *)*(this + 2175)  // （上一表达式的参数/条件续行）
                                                                                                + 140))(  // （表达式续行/复合语句）
                 *(this + 2175),  // （上一表达式的参数/条件续行）
                 &pThis_88C3,  // （上一表达式的参数/条件续行）
                 &pThis_22,  // （上一表达式的参数/条件续行）
                 pThis_88C3,  // （上一表达式的参数/条件续行）
                 pThis_22,  // （上一表达式的参数/条件续行）
                 100,  // （上一表达式的参数/条件续行）
                 1,  // （上一表达式的参数/条件续行）
                 1) != 0 )  // （上一表达式的参数/条件续行）
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)*(this + 2175) + 108))(  // （表达式续行/复合语句）
              *(this + 2175),  // （上一表达式的参数/条件续行）
              pThis_88C3,  // （上一表达式的参数/条件续行）
              pThis_22,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
          }
          else  // 否则分支
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2175) + 108))(  // （表达式续行/复合语句）
              *(this + 2175),  // （上一表达式的参数/条件续行）
              *(this + 2176),  // （上一表达式的参数/条件续行）
              *(this + 2177),  // （上一表达式的参数/条件续行）
              *(this + 2178));  // （上一表达式的参数/条件续行）
          }
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2175) + 724))(*(this + 2175)) == 0 )  // 条件判定
          {
            v502 = 0.0;  // v502 = 0.0（浮点初值）
            v503 = 0;
            *(float *)&v504 = 0.0;  // （表达式续行/复合语句）
            v506 = 2;
            pMem = (void *)4;  // （表达式续行/复合语句）
            sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
            pMem = (void *)2;  // （表达式续行/复合语句）
            sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
            pMem = (void *)1;  // （表达式续行/复合语句）
            sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
            pMem = nullptr;  // pMem = 空指针
            sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
            pMem = nullptr;  // pMem = 空指针
            sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
            (*(void (/*thiscall*/ **)(uint32_t, int, float *, int, uint32_t))(*(uint32_t *)*(this + 2175) + 560))(  // （表达式续行/复合语句）
              *(this + 2175),  // （上一表达式的参数/条件续行）
              4,  // （上一表达式的参数/条件续行）
              &v501,  // （上一表达式的参数/条件续行）
              2,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2175) + 564))(*(this + 2175));  // （表达式续行/复合语句）
            v506 = -1;
            sub_5E5260((void **)&v501);  // sub_5E5260 —— 清理临时缓冲
          }
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2175) + 596))(*(this + 2175), 1);  // （表达式续行/复合语句）
        fld_e2179 = *(this + 2179);  // 读字段 fld_e2179 = this[2179]
        *(this + 2175) = 0;  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2179 + 76))(fld_e2179, 0);  // （表达式续行/复合语句）
      }
      *(this + 2129) = -1;  // （表达式续行/复合语句）
      pThis_884 = this + 2180;  // （表达式续行/复合语句）
      for ( k = 2; k != 0; --k )  // 循环（遍历）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_884++);  // （表达式续行/复合语句）
      if ( *(float *)&nArg2 != 0.0 )  // 条件判定
        goto LABEL_108;  // 跳转合流点 LABEL_108
      v498 = 15;
      v497 = 0;
      LOBYTE(v495[0]) = 0;  // （表达式续行/复合语句）
      v34 = *this;  // （表达式续行/复合语句）
      v506 = 3;
      v35 = (*(int (/*thiscall*/ **)(int *))(v34 + 1096))(this);  // （表达式续行/复合语句）
      sub_4C2020((int)v494, v35);
      v23 = (void **)v495[0];  // （表达式续行/复合语句）
      if ( v498 < 0x10 )  // 条件判定
        v23 = v495;
LABEL_70:  // 标签 LABEL_70：合流点
      (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v23, -1, 0, 0);  // （表达式续行/复合语句）
      v506 = -1;
      sub_501490(v494);  // std::string 析构（本条目串：数据@+4/长度@+20/容量@+24）：容量
      break;  // 跳出本分支
    // ── [段 7] 第一重 case 20：nArg22 != 20 时清 this[2129]=-1 + 回挂 +2188 起 2 件 + vt+216(11) ──
    case 20:  // case 20 分派：第一重 case 20：nArg22 != 20 时清 this[2129]=-1 + 回挂 +2188 起 2 件 + vt+216(11)
      if ( nArg22 != 20 )  // 条件判定
      {
        *(this + 2129) = -1;  // （表达式续行/复合语句）
        pThis_88C = this + 2188;  // （表达式续行/复合语句）
        for ( m = 2; m != 0; --m )  // 循环（遍历）
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_88C++);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 11);  // （表达式续行/复合语句）
      }
      goto LABEL_108;  // 跳转合流点 LABEL_108
    // ── [段 8] 第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理 ──
    //   子 switch：12/14/13·36/39 四组，各自回挂不同动画件；
    //   nArg2 != 22 时清 this[2129]=-1；LABEL_96：nArg2 为 0 时播 SUBWEAPON_IN，
    //   +2242==0 时 vt+996 收束；LABEL_108 出口：nArg2==24 时改写 nArg2=8 与 fld_e1639=24（别名折叠）
    case 22:  // case 22 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
      pThis_913 = this + 2323;  // （表达式续行/复合语句）
      pThis_88C3 = 2;
      do
      {
        if ( *pThis_913 != 0 )  // 条件判定
        {
          sub_492980(*pThis_913);  // sub_492980 —— 子链节点按对象指针摘除（组件槽卸载/释放）
          *pThis_913 = 0;  // （表达式续行/复合语句）
        }
        ++pThis_913;  // 自增
        --pThis_88C3;  // （表达式续行/复合语句）
      }
      while ( *(float *)&pThis_88C3 != 0.0 );  // 循环
      nItemCtx_ = *(this + 2129);  // 读字段 fld_e21292 = this[2129]
      switch ( nItemCtx_ )  // 分派 switch
      {
        case 12:  // case 12 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
          pThis_91D = this + 2333;  // （表达式续行/复合语句）
          for ( n = 3; n != 0; --n )  // 循环（遍历）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_91D++);  // （表达式续行/复合语句）
          break;  // 跳出本分支
        case 14:  // case 14 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
          if ( nArg2 == 22 )  // 条件判定
            goto LABEL_96;  // 跳转合流点 LABEL_96
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2341));  // （表达式续行/复合语句）
          break;  // 跳出本分支
        case 13:  // case 13 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
        case 36:  // case 36 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
          if ( nArg2 == 22 )  // 条件判定
            goto LABEL_96;  // 跳转合流点 LABEL_96
          (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 12);  // （表达式续行/复合语句）
          break;  // 跳出本分支
        case 39:  // case 39 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
          sub_492980(*(this + 2343));  // sub_492980 —— 子链节点按对象指针摘除（组件槽卸载/释放）
          sub_492980(*(this + 2344));  // sub_492980 —— 子链节点按对象指针摘除（组件槽卸载/释放）
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2349));  // （表达式续行/复合语句）
          pThis_930 = this + 2352;  // （表达式续行/复合语句）
          for ( ii = 2; ii != 0; --ii )  // 循环（遍历）
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(pThis_930 - 5));  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_930);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(pThis_930 - 2));  // （表达式续行/复合语句）
            ++pThis_930;  // 自增
          }
          (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 13);  // （表达式续行/复合语句）
          break;  // 跳出本分支
        default:  // 未列出的值 → 兜底
          break;  // 跳出本分支
      }
      if ( nArg2 != 22 )  // 条件判定
        *(this + 2129) = -1;  // （表达式续行/复合语句）
LABEL_96:  // 标签 LABEL_96：合流点
      if ( *(float *)&nArg2 == 0.0 )  // 条件判定
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SUBWEAPON_IN", -1, 0, 0);  // （表达式续行/复合语句）
      if ( *(this + 2242) == 0 )  // 条件判定
        (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);  // （表达式续行/复合语句）
LABEL_108:  // 标签 LABEL_108：合流点
      if ( nArg2 == 24 )  // 条件判定
      {
        nArg2 = 8;
        nBigState = 24;
      }
      break;  // 跳出本分支
    // ── [段 9] 第一重 case 23：nArg22 != 23 时清 this[2129]=-1 并按本机 vt+308 处理（goto LABEL_108）──
    case 23:  // case 23 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
      if ( nArg22 != 23 )  // 条件判定
      {
        v49 = *this;  // （表达式续行/复合语句）
        *(this + 2129) = -1;  // （表达式续行/复合语句）
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(v49 + 308))(this) != 0 )  // 条件判定
        {
          v50 = *this;  // （表达式续行/复合语句）
          v51 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 15);  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *, int, int))(v50 + 1296))(this, 15, v51);  // （表达式续行/复合语句）
        }
      }
      goto LABEL_108;  // 跳转合流点 LABEL_108
    // ── [段 10] 第一重 case 25/26/27：25 → vt+996 + nArg2!=0 时 +2371=-1；──
    //   26 → 回挂 +2323 起 2 件后按 this[2129] 39/40 二支；27 → 落 LABEL_107（清 this[2129] 出口）；default → LABEL_108
    case 25:  // case 25 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
      (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);  // （表达式续行/复合语句）
      if ( *(float *)&nArg2 != 0.0 )  // 条件判定
        *(this + 2371) = -1;  // （表达式续行/复合语句）
      goto LABEL_108;  // 跳转合流点 LABEL_108
    case 26:  // case 26 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
      pThis_9132 = this + 2323;  // （表达式续行/复合语句）
      for ( jj = 2; jj != 0; --jj )  // 循环（遍历）
      {
        if ( *pThis_9132 != 0 )  // 条件判定
        {
          sub_492980(*pThis_9132);  // sub_492980 —— 子链节点按对象指针摘除（组件槽卸载/释放）
          *pThis_9132 = 0;  // （表达式续行/复合语句）
        }
        ++pThis_9132;  // 自增
      }
      nItemCtx_2 = *(this + 2129);  // 读字段 fld_e21293 = this[2129]
      if ( nItemCtx_2 == 39 )  // 判定字段 this[21293] == 39
      {
        pThis_929 = this + 2345;  // （表达式续行/复合语句）
        for ( kk = 2; kk != 0; --kk )  // 循环（遍历）
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_929++);  // （表达式续行/复合语句）
      }
      else if ( nItemCtx_2 == 40 )  // 判定字段 this[21293]（大状态/子状态门）
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2358));  // （表达式续行/复合语句）
      }
      goto LABEL_107;  // 跳转合流点 LABEL_107
    case 27:  // case 27 分派：第一重 case 22：★ 副武器收尾 —— 回挂 +2323 起 2 件后按 this[2129] 五型处理
LABEL_107:  // 标签 LABEL_107：合流点
      *(this + 2129) = -1;  // （表达式续行/复合语句）
      goto LABEL_108;  // 跳转合流点 LABEL_108
    default:  // 未列出的值 → 兜底
      goto LABEL_108;  // 跳转合流点 LABEL_108
  }
  // ── [段 11] 第二重 switch(nArg2)：★ 动作主表（12/15/16/17/18/19/20/21/22/23/25/26/27）──
  switch ( nArg2 )  // 分派 switch
  {
    // ── [段 12] 第二重 case 12：★ R_GN_SLIDING（滑铲）—— 速度×4.1 夹取 >=200 后反算帧长 ──
    //   fld_e1813 = sub_491C70(this[1813], this[1982]) 帧时长；+2158 存夹取量，+2159 = -1000*v78/fld_e1813；
    //   +2160 存 v78 后 vt+876 全零 + +2161=-400 偏移 + 播 R_GN_SLIDING（goto LABEL_482）
    case 12:  // case 12 分派：第二重 case 12：★ R_GN_SLIDING（滑铲）—— 速度×4.1 夹取 >=200 后反算帧长
      pTarget7252 = sub_491C70(*(this + 1813), *(this + 1982));  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
      pHostComp112 = *(float *)(*(this + 28) + 16) * 4.0999999;  // （表达式续行/复合语句）
      if ( (int)(uint64_t)fabs(pHostComp112) <= 200 )  // 条件判定
        LODWORD(v78) = 200;  // （表达式续行/复合语句）
      else  // 否则分支
        v78 = (uint64_t)fabs(pHostComp112);  // （表达式续行/复合语句）
      *(this + 2158) = v78;  // （表达式续行/复合语句）
      pAnimObj = *(this + 30);  // 读字段 fld_e30 = this[30]
      HIDWORD(v78) = *this;  // （表达式续行/复合语句）
      *(this + 2159) = -1000 * (int)v78 / pTarget7252;  // （表达式续行/复合语句）
      *(this + 2160) = *(uint32_t *)(pAnimObj + 148);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(HIDWORD(v78) + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      v80 = *this;  // （表达式续行/复合语句）
      *(this + 2161) = -400;  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v80 + 212))(this, "R_GN_SLIDING", -1, 0, 0);  // （表达式续行/复合语句）
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 13] 第二重 case 15：★ 旋风（Windmill 系）—— pArg3[1][0]==3 时主演出 ──
    //   vt+196(this[1554]+28) 应用技能参 + vt+344(this[139]) 动画基；
    //   sub_47EFD0 伤害写 this[97] 索引；sub_47EF20(1)/(2) 读表写 +2168 与 fld_e304 倍率；
    //   sub_477 之后 vt+900(3) 与 vt+888 帧长；vt+896(4,4) 挂帧；vt+1140(35) 分支（991/1010 两支）；
    //   +2170 惰性建 WindmillDust1/2.ani（1045-1066）；+2168==1 时再建 WindmillDust3.ani（1088）；goto LABEL_482
    case 15:  // case 15 分派：第二重 case 15：★ 旋风（Windmill 系）—— pArg3[1][0]==3 时主演出
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 28));  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));  // （表达式续行/复合语句）
      if ( **(uint32_t **)(pArg3 + 4) == 3 )  // 条件判定
      {
        v81 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 3);  // （表达式续行/复合语句）
        v82 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 3);  // （表达式续行/复合语句）
        v83 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);  // （表达式续行/复合语句）
        pMem = (void *)sub_47EFD0(v81, 0.0, v82, v83, v83, 0);  // sub_47EFD0 —— 攻击上下文计算
        *((float *)this + 97) = (float)(int)pMem;  // （表达式续行/复合语句）
        *(this + 2168) = sub_47EF20(1, v82, -1, -1, 11);  // （表达式续行/复合语句）
        v84 = (void *)sub_47EF20(2, v82, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
        v85 = *this;  // （表达式续行/复合语句）
        pMem = v84;
        pAnimObj_6 = (double)(int)v84 * 0.0099999998 + 1.0;  // （表达式续行/复合语句）
        pMem = (void *)(*(int (/*thiscall*/ **)(int *, int))(v85 + 900))(this, 3);  // （表达式续行/复合语句）
        (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, int, uint32_t))(v85 + 888))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          (uint64_t)((double)(int)pMem * pAnimObj_6) >> 32,  // （上一表达式的参数/条件续行）
          1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          1000,  // （上一表达式的参数/条件续行）
          (uint64_t)((double)(int)pMem * pAnimObj_6));  // （上一表达式的参数/条件续行）
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
        v86 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 35);  // （表达式续行/复合语句）
        v87 = *this;  // （表达式续行/复合语句）
        if ( v86 <= 0 )  // 条件判定
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v87 + 876))(  // （表达式续行/复合语句）
            this,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
            this,  // （上一表达式的参数/条件续行）
            1,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
        }
        else  // 否则分支
        {
          (*(void (/*thiscall*/ **)(int *, int))(v87 + 1160))(this, 35);  // （表达式续行/复合语句）
          v88 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 35);  // （表达式续行/复合语句）
          *(float *)&pThis_88C3 = COERCE_FLOAT(sub_47EF20(0, v88, -1, -1, 11));  // （表达式续行/复合语句）
          v89 = (void *)sub_47EF20(1, v88, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
          v90 = *this;  // （表达式续行/复合语句）
          v91 = v89;
          pMem = v89;
          (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(v90 + 876))(  // （表达式续行/复合语句）
            this,  // （上一表达式的参数/条件续行）
            (uint64_t)((double)pThis_88C3 * 0.82999998) >> 32,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            pThis_88C3,  // （上一表达式的参数/条件续行）
            (uint64_t)((double)pThis_88C3 * 0.82999998),  // （上一表达式的参数/条件续行）
            1,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
          (*(void (/*fastcall*/ **)(int *, uint32_t, int, void *, uint32_t, int, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
            this,  // （上一表达式的参数/条件续行）
            (uint64_t)((double)(int)pMem * 0.82999998) >> 32,  // （上一表达式的参数/条件续行）
            1,  // （上一表达式的参数/条件续行）
            v91,  // （上一表达式的参数/条件续行）
            (uint64_t)((double)(int)pMem * 0.82999998),  // （上一表达式的参数/条件续行）
            1,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
        }
      }
      fld_e2170 = *(this + 2170);  // 读字段 fld_e2170 = this[2170]
      v93 = 0;
      *(this + 2167) = 0;  // （表达式续行/复合语句）
      *((uint8_t *)this + 8676) = 0;  // （表达式续行/复合语句）
      if ( fld_e2170 == 0 )  // 判定字段 this[2170] == 0
      {
        pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
        v506 = 9;
        if ( pMem != nullptr )  // 条件判定
          // ── [段 14] 第二重 case 15 之 +2170 惰性建件：WindmillDust1/2.ani 双枚（内联/堆指针二选一）──
          v94 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust1.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
        else  // 否则分支
          v94 = 0;
        v506 = -1;
        *(this + 2170) = v94;  // （表达式续行/复合语句）
        pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
        v506 = 10;
        if ( pMem != nullptr )  // 条件判定
        {
          v95 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust2.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
          v506 = -1;
          *(this + 2171) = v95;  // （表达式续行/复合语句）
        }
        else  // 否则分支
        {
          v506 = -1;
          *(this + 2171) = 0;  // （表达式续行/复合语句）
        }
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        1,  // （上一表达式的参数/条件续行）
        *(this + 2170),  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        -1,  // （上一表达式的参数/条件续行）
        *(this + 2171),  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      if ( *(this + 2168) == 1 )  // 条件判定
      {
        pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
        v506 = 11;
        if ( pMem != nullptr )  // 条件判定
          v93 = sub_431860((char)"Character/Gunner/Effect/Animation/WindmillDust3.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
        fld_e302 = *(void **)(*(this + 30) + 164);  // （表达式续行/复合语句）
        v506 = -1;
        pMem = fld_e302;
        sub_493D00(v93, *(float *)&fld_e302);  // sub_493D00 —— ★变速（研究§26）
        pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
        v506 = 12;
        if ( pMem != nullptr )  // 条件判定
          pObj10 = sub_44E1F0(v93, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
        else  // 否则分支
          pObj10 = 0;
        fld_e29 = *(this + 29);  // 读字段 fld_e29 = this[29]
        v506 = -1;
        sub_45FE80(fld_e29, pObj10, 2, 0, pObj10, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
        v99 = *(uint32_t *)pObj10;  // （表达式续行/复合语句）
        v478 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int))(v99 + 148))(pObj10);  // （表达式续行/复合语句）
        v100 = *(uint32_t *)pObj10;  // （表达式续行/复合语句）
        v101 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // （表达式续行/复合语句）
        v102 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v101);  // （表达式续行/复合语句）
        v103 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v102);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, int))(v100 + 112))(pObj10, v103);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj10 + 60))(pObj10, this);  // （表达式续行/复合语句）
        sub_4A06D0(v478);
      }
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_WINDMILL", -1, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WINDMILL_SWING", -1, 0, 0);  // （表达式续行/复合语句）
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 15] 第二重 case 16：★ 散射/连射（RandomShoot1/2.ani）—— 14==14 与 fld_e1639 特例 ──
    //   pArg3[1][0] 读入 v104；v105 = (v104==14 && fld_e1639==16) 门控；
    //   this[8692] 分两支（1170/1180）各处理；goto LABEL_482
    case 16:  // case 16 分派：第二重 case 16：★ 散射/连射（RandomShoot1/2.ani）—— 14==14 与 fld_e1639 特例
      v104 = **(uint32_t **)(pArg3 + 4);  // （表达式续行/复合语句）
      *(this + 2172) = v104;  // （表达式续行/复合语句）
      v105 = v104 == 14 && nBigState == 16;  // （表达式续行/复合语句）
      *((uint8_t *)this + 8692) = v105;  // （表达式续行/复合语句）
      if ( v105 )  // 条件判定
      {
        v106 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8));  // sub_45EBE0
        pObj8 = __RTDynamicCast(v106, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // （表达式续行/复合语句）
        *(this + 2336) = pObj8;  // （表达式续行/复合语句）
        if ( pObj8 != 0 )  // 条件判定
        {
          v108 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 120))(pObj8);  // （表达式续行/复合语句）
          fld_e23365 = *(this + 2336);  // 读字段 fld_e23365 = this[2336]
          *(this + 2337) = v108;  // （表达式续行/复合语句）
          v110 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e23365 + 124))(fld_e23365);  // （表达式续行/复合语句）
          fld_e23366 = *(this + 2336);  // 读字段 fld_e23366 = this[2336]
          *(this + 2338) = v110;  // （表达式续行/复合语句）
          *(this + 2339) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e23366 + 128))(fld_e23366);  // （表达式续行/复合语句）
          if ( *(this + 2340) == 0 )  // 条件判定
          {
            pMem = operator new(0x8Cu);  // （表达式续行/复合语句）
            v506 = 13;
            if ( pMem != nullptr )  // 条件判定
              v112 = sub_4C12C0(this);  // sub_4C12C0
            else  // 否则分支
              v112 = 0;
            v506 = -1;
            *(this + 2340) = v112;  // （表达式续行/复合语句）
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2340) + 56))(  // （表达式续行/复合语句）
            *(this + 2340),  // （上一表达式的参数/条件续行）
            *(this + 2336),  // （上一表达式的参数/条件续行）
            this,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            -1);  // （上一表达式的参数/条件续行）
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 36));  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 152);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
      v113 = *this;  // （表达式续行/复合语句）
      v114 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int))(v113 + 896))(this, v114);  // （表达式续行/复合语句）
      if ( *((uint8_t *)this + 8692) != 0 )  // 判定 this[8692] != 0（uint8）
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // （表达式续行/复合语句）
        sub_4AECE0((void *)*(this + 30), 2);  // 字段 this+30〔动画时间轴并置〕
        LOBYTE(nArg5) = 0;  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);  // （表达式续行/复合语句）
        *((uint8_t *)this + 8694) = 1;  // （表达式续行/复合语句）
      }
      else  // 否则分支
      {
        v115 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 4);  // （表达式续行/复合语句）
        v116 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 4);  // （表达式续行/复合语句）
        v117 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);  // （表达式续行/复合语句）
        pMem = (void *)sub_47EFD0(v115, 0.0, v116, v117, v117, 0);  // sub_47EFD0 —— 攻击上下文计算
        *((float *)this + 97) = (float)(int)pMem;  // （表达式续行/复合语句）
        pMem = (void *)sub_47EF20(1, v116, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
        v118 = *this;  // （表达式续行/复合语句）
        pAnimObj_6 = (double)(int)pMem * 0.0099999998 + 1.0;  // （表达式续行/复合语句）
        pMem = (void *)(*(int (/*thiscall*/ **)(int *, int))(v118 + 900))(this, 3);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          (uint64_t)((double)(int)pMem * pAnimObj_6),  // （上一表达式的参数/条件续行）
          (uint64_t)((double)(int)pMem * pAnimObj_6));  // （上一表达式的参数/条件续行）
        *(this + 114) = sub_47EF20(2, v116, -1, -1, 11);  // （表达式续行/复合语句）
        fld_e2172 = *(this + 2172);  // 读字段 fld_e2172 = this[2172]
        if ( fld_e2172 == 4 )  // 判定字段 this[2172] == 4
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
            this,  // （上一表达式的参数/条件续行）
            "R_GN_JACKSPIKE",  // （上一表达式的参数/条件续行）
            -1,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
        }
        else if ( fld_e2172 == 14 )  // 判定字段 this[2172]（大状态/子状态门）
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_BBQ", -1, 0, 0);  // （表达式续行/复合语句）
        }
        *((uint8_t *)this + 8694) = 0;  // （表达式续行/复合语句）
      }
      *((uint8_t *)this + 8693) = *(this + 2172) == 4  // （表达式续行/复合语句）
                             && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0  // （上一表达式的参数/条件续行）
                             && (v120 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1132))(this, 0)) == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （上一表达式的参数/条件续行）
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 16] 第二重 case 17：单指令分支（goto LABEL_482）──
    case 17:  // case 17 分派：第二重 case 16：★ 散射/连射（RandomShoot1/2.ani）—— 14==14 与 fld_e1639 特例
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 40));  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 3, 1000, 1000);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 304);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GN_PUNISHER", -1, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "PUNISHER_SWING", -1, 0, 0);  // （表达式续行/复合语句）
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 17] 第二重 case 18：★ 连射/踏射（MusketDustSmall4 + TreadShootDust1/2.ani）──
    //   +2174 计时器两支：非 0 走 MusketDust 大尘（1332/1369）；0 走 TreadShootDust1/2.ani（1456/1464）；
    //   goto LABEL_482
    case 18:  // case 18 分派：第二重 case 16：★ 散射/连射（RandomShoot1/2.ani）—— 14==14 与 fld_e1639 特例
      v121 = *this;  // （表达式续行/复合语句）
      *(this + 2174) = **(uint32_t **)(pArg3 + 4);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(v121 + 196))(this, *(uint32_t *)(*(this + 1554) + 44));  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
      fld_e2174 = *(this + 2174);  // 读字段 fld_e2174 = this[2174]
      if ( fld_e2174 != 0 )  // 判定字段 this[2174] != 0
      {
        if ( fld_e2174 == 1 )  // 判定字段 this[2174] == 1
        {
          if ( sub_41A5E0((unsigned int)this + 8290) > 3 )  // 条件判定
          {
            pThis_2062 = sub_41A5E0((unsigned int)this + 8290);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
            v134 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // （表达式续行/复合语句）
            v135 = sub_495500(v134);  // sub_495500 —— 槽对乘积读取（+844/+858）
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, pThis_2062 * v135 / 3);  // （表达式续行/复合语句）
          }
          sub_4AECE0((void *)*(this + 30), 9);  // 字段 this+30〔动画时间轴并置〕
          LOBYTE(nArg5) = 0;  // （表达式续行/复合语句）
          sub_4450B0(1);  // sub_4450B0 —— 计数器加值
          v136 = sub_4C46B0(this, 3);  // sub_4C46B0
          if ( v136 != 0 )  // 条件判定
          {
            pMem = *(void **)(*(this + 30) + 164);  // （表达式续行/复合语句）
            sub_493D00(v136, *(float *)&pMem);  // sub_493D00 —— ★变速（研究§26）
            pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
            v506 = 17;
            if ( pMem != nullptr )  // 条件判定
              pObj4 = sub_44E1F0(v136, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
            else  // 否则分支
              pObj4 = 0;
            fld_e292 = *(this + 29);  // 读字段 fld_e292 = this[29]
            v506 = -1;
            sub_45FE80(fld_e292, pObj4, 2, 0, pObj4, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
            v139 = *(uint32_t *)pObj4;  // （表达式续行/复合语句）
            v479 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int))(v139 + 148))(pObj4);  // （表达式续行/复合语句）
            v140 = *(uint32_t *)pObj4;  // （表达式续行/复合语句）
            v141 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // （表达式续行/复合语句）
            v142 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v141);  // （表达式续行/复合语句）
            v143 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v142);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int))(v140 + 112))(pObj4, v143);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj4 + 60))(pObj4, this);  // （表达式续行/复合语句）
            sub_4A06D0(v479);
          }
          if ( (uint8_t)sub_423340(this + 2087, szPassword) != 0 )  // 条件判定
          {
            if ( (unsigned int)*(this + 2093) < 0x10 )  // 条件判定
              pThis_828 = this + 2088;  // （表达式续行/复合语句）
            else  // 否则分支
              pThis_828 = (uint32_t *)*(this + 2088);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_828, -1, 0, 0);  // （表达式续行/复合语句）
          }
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 条件判定
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), *(this + 2055));  // （表达式续行/复合语句）
            fld_e2054 = *(uint32_t *)*(this + 2054);  // （表达式续行/复合语句）
            v146 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // （表达式续行/复合语句）
            v147 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v146);  // （表达式续行/复合语句）
            v148 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v147);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2054 + 40))(*(this + 2054), v148);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 12))(*(this + 2054), 0);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 112))(*(this + 2054), 0);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 2054) + 92))(*(this + 2054), v496);  // （表达式续行/复合语句）
            sub_5E5260(v496);  // sub_5E5260 —— 清理临时缓冲
          }
          v149 = *this;  // （表达式续行/复合语句）
          *(float *)&pThis_88C3 = 0.0;  // （表达式续行/复合语句）
          pThis_22 = 0;
          v488 = 0;
          if ( (*(int (/*thiscall*/ **)(int *))(v149 + 1096))(this) == 1 )  // 条件判定
          {
            sub_4C17C0(&pThis_88C3, &pThis_22, &v488, 74, 0, 57);
            pObj2 = dword_8F830C;
            v151 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;  // （表达式续行/复合语句）
            v152 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 28))(pObj2);  // （表达式续行/复合语句）
            pThis_222 = pThis_22;
            *(uint8_t *)(v152 + 84) = v151;  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 40))(pObj2, pThis_88C3, pThis_222, v488);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)pObj2 + 92))(pObj2, &v501);  // （表达式续行/复合语句）
            v506 = 18;
            sub_4600B0((void *)*(this + 29), 2, 0, (int)&v501);  // sub_4600B0 —— 演播层注册(槽号)
            goto LABEL_232;  // 跳转合流点 LABEL_232
          }
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 1096))(this) == 2 )  // 条件判定
          {
            sub_4C17C0(&pThis_88C3, &pThis_22, &v488, 63, 0, 85);
            // ── [段 18] 第二重 case 18 之 +2174 计时器支：MusketDustSmall4 + MusketDustLarge 两件 ──
            sub_401710("Character/Gunner/Effect/Animation/MusketDust/MusketDustSmall4.ani");  // sub_401710 —— std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
            v506 = 19;
            v154 = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
            pMem = v154;
            LOBYTE(v506) = 20;  // （表达式续行/复合语句）
            if ( v154 != nullptr )  // 条件判定
            {
              pAnimObj_6 = COERCE_FLOAT(sub_42FCB0(228));  // （表达式续行/复合语句）
              LOBYTE(v506) = 21;  // （表达式续行/复合语句）
              if ( pAnimObj_6 == 0.0 )  // 判定字段 this[304]（大状态/子状态门）
              {
                v156 = 0;
              }
              else  // 否则分支
              {
                LOBYTE(Block2) = Block[0];  // （表达式续行/复合语句）
                if ( v504 < 0x10 )  // 条件判定
                  Block2 = Block;
                v156 = sub_431860((char)Block2, 1);  // sub_431860 —— 动画件构造（资源 id 版）
              }
              LOBYTE(v506) = 20;  // （表达式续行/复合语句）
              pObj5 = sub_44E1F0(v156, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
            }
            else  // 否则分支
            {
              pObj5 = 0;
            }
            fld_e293 = *(this + 29);  // 读字段 fld_e293 = this[29]
            LOBYTE(v506) = 19;  // （表达式续行/复合语句）
            sub_45FE80(fld_e293, (int)v154, 2, 0, pObj5, (int)this, 1);  // sub_45FE80 —— 实体注册到演播层
            v159 = *(uint32_t *)pObj5;  // （表达式续行/复合语句）
            v160 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int))(v159 + 148))(pObj5, v160);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 112))(pObj5, pThis_88C3, pThis_22, v488);  // （表达式续行/复合语句）
            nRand = rand() % 40 + 110;  // （表达式续行/复合语句）
            nRand2 = rand();  // （表达式续行/复合语句）
            sub_4C17C0(&pThis_88C3, &pThis_22, &v488, nRand2 % 40 + 13, 0, nRand);
            sub_406D60("Character/Gunner/Effect/Animation/MusketDust/MusketDustLarge.ani");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
            pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
            LOBYTE(v506) = 22;  // （表达式续行/复合语句）
            if ( pMem != nullptr )  // 条件判定
            {
              pAnimObj_6 = COERCE_FLOAT(sub_42FCB0(228));  // （表达式续行/复合语句）
              LOBYTE(v506) = 23;  // （表达式续行/复合语句）
              if ( pAnimObj_6 == 0.0 )  // 判定字段 this[304]（大状态/子状态门）
              {
                v163 = 0;
              }
              else  // 否则分支
              {
                LOBYTE(Block3) = Block[0];  // （表达式续行/复合语句）
                if ( v504 < 0x10 )  // 条件判定
                  Block3 = Block;
                v163 = sub_431860((char)Block3, 1);  // sub_431860 —— 动画件构造（资源 id 版）
              }
              LOBYTE(v506) = 22;  // （表达式续行/复合语句）
              pObj6 = sub_44E1F0(v163, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
            }
            else  // 否则分支
            {
              pObj6 = 0;
            }
            fld_e294 = *(this + 29);  // 读字段 fld_e294 = this[29]
            LOBYTE(v506) = 19;  // （表达式续行/复合语句）
            sub_45FE80(fld_e294, pObj6, 2, 0, pObj6, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
            v166 = *(uint32_t *)pObj6;  // （表达式续行/复合语句）
            v167 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int))(v166 + 148))(pObj6, v167);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 112))(pObj6, pThis_88C3, pThis_22, v488);  // （表达式续行/复合语句）
            v506 = -1;
            sub_501490(v499);  // std::string 析构（本条目串：数据@+4/长度@+20/容量@+24）：容量
          }
        }
        else if ( fld_e2174 == 2 )  // 判定字段 this[2174]（大状态/子状态门）
        {
          sub_4AECE0((void *)*(this + 30), 13);  // 字段 this+30〔动画时间轴并置〕
          LOBYTE(nArg5) = 0;  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
            this,  // （上一表达式的参数/条件续行）
            "R_GN_PUNISHER_END",  // （上一表达式的参数/条件续行）
            -1,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
        }
      }
      else  // 否则分支
      {
        v123 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8));  // sub_45EBE0
        pObj = __RTDynamicCast(v123, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // （表达式续行/复合语句）
        *(this + 2175) = pObj;  // （表达式续行/复合语句）
        if ( pObj != 0 )  // 条件判定
        {
          v125 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // （表达式续行/复合语句）
          fld_e21753 = *(this + 2175);  // 读字段 fld_e21753 = this[2175]
          *(this + 2176) = v125;  // （表达式续行/复合语句）
          v127 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21753 + 124))(fld_e21753);  // （表达式续行/复合语句）
          fld_e21754 = *(this + 2175);  // 读字段 fld_e21754 = this[2175]
          *(this + 2177) = v127;  // （表达式续行/复合语句）
          *(this + 2178) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21754 + 128))(fld_e21754);  // （表达式续行/复合语句）
          if ( *(this + 2179) == 0 )  // 条件判定
          {
            pMem = operator new(0x5Cu);  // （表达式续行/复合语句）
            v506 = 14;
            if ( pMem != nullptr )  // 条件判定
              v129 = sub_4C11D0(this);  // sub_4C11D0
            else  // 否则分支
              v129 = 0;
            v506 = -1;
            *(this + 2179) = v129;  // （表达式续行/复合语句）
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2179) + 56))(  // （表达式续行/复合语句）
            *(this + 2179),  // （上一表达式的参数/条件续行）
            *(this + 2175),  // （上一表达式的参数/条件续行）
            this,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            -1);  // （上一表达式的参数/条件续行）
        }
        if ( *(this + 2180) == 0 )  // 条件判定
        {
          pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
          v506 = 15;
          if ( pMem != nullptr )  // 条件判定
            // ── [段 19] 第二重 case 18 之 else 支：+2174==0 时建 TreadShootDust1/2.ani 双枚 ──
            v130 = sub_431860((char)"Character/Gunner/Effect/Animation/TreadShootDust1.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
          else  // 否则分支
            v130 = 0;
          v506 = -1;
          *(this + 2180) = v130;  // （表达式续行/复合语句）
          pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
          v506 = 16;
          if ( pMem != nullptr )  // 条件判定
            v131 = sub_431860((char)"Character/Gunner/Effect/Animation/TreadShootDust2.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
          else  // 否则分支
            v131 = 0;
          v506 = -1;
          *(this + 2181) = v131;  // （表达式续行/复合语句）
        }
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 204))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          *(this + 2180),  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          1);  // （上一表达式的参数/条件续行）
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          1,  // （上一表达式的参数/条件续行）
          *(this + 2181),  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        sub_41A590((unsigned int)(this + 2136), v132, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
        *(this + 2129) = 6;  // （表达式续行/复合语句）
        *((uint8_t *)this + 8576) = 0;  // （表达式续行/复合语句）
        *((uint8_t *)this + 8728) = 0;  // （表达式续行/复合语句）
      }
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 20] 第二重 case 19：★ 速射帧长标定 —— vt+1140(7) 读表 + vt+388 伤害链 ──
    //   vt+1160/vt+1140(7) 取参，vt+388 取当前伤害，sub_47EFD0 三参写回；goto LABEL_482
    case 19:  // case 19 分派：第二重 case 19：★ 速射帧长标定 —— vt+1140(7) 读表 + vt+388 伤害链
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 48));  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int))(*this + 344))(this, *(this + 139) + 456);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
      v168 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 7);  // （表达式续行/复合语句）
      v169 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 7);  // （表达式续行/复合语句）
      v170 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);  // （表达式续行/复合语句）
      pMem = (void *)sub_47EFD0(v168, 0.0, v169, v170, v170, 0);  // sub_47EFD0 —— 攻击上下文计算
      *((float *)this + 97) = (float)(int)pMem;  // （表达式续行/复合语句）
      pMem = (void *)sub_47EF20(2, v169, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      *((float *)this + 106) = (double)(int)pMem * 0.1;  // （表达式续行/复合语句）
      *(this + 109) = sub_47EF20(3, v169, -1, -1, 11);  // （表达式续行/复合语句）
      pMem = (void *)sub_47EF20(1, v169, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      v171 = *this;  // （表达式续行/复合语句）
      pAnimObj_6 = (double)(int)pMem * 0.0099999998 + 1.0;  // （表达式续行/复合语句）
      pMem = (void *)(*(int (/*thiscall*/ **)(int *, int))(v171 + 900))(this, 3);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        (uint64_t)((double)(int)pMem * pAnimObj_6),  // （上一表达式的参数/条件续行）
        (uint64_t)((double)(int)pMem * pAnimObj_6));  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_MACH", -1, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "MACH_SWING", -1, 0, 0);  // （表达式续行/复合语句）
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 21] 第二重 case 20：★ 擦弹/接近射击（GRAZE_LOOP + RandomShoot1/2.ani）──
    //   fld_e304 = pArg3[1][2]；sub_41A5E0(this+2076) 与 vt+672(3)+sub_495500 算帧长；
    //   fld_e1639 != 20 时按枪种播 R_GUN_GRAZE_LOOP 或 R_BOWGUN_GRAZE_LOOP；
    //   vt+1096 枪种 1/4 分别支：sub_4C1000 或按 this[2*(pMem+v184)] 取件，
    //   sub_4319E0 建 RandomShoot1/2.ani（各带 3 参）；末段按 pArg3[1][0] 1/2/3 三支与 +2183 比对（1697-1742）
    case 20:  // case 20 分派：第二重 case 19：★ 速射帧长标定 —— vt+1140(7) 读表 + vt+388 伤害链
      pAnimObj_6 = *(float *)(*(uint32_t *)(pArg3 + 4) + 8);  // （表达式续行/复合语句）
      pThis_81C = (void *)sub_41A5E0((unsigned int)(this + 2076));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
      v173 = *this;  // （表达式续行/复合语句）
      pMem = pThis_81C;
      v174 = (*(int (/*thiscall*/ **)(int *, int))(v173 + 672))(this, 3);  // （表达式续行/复合语句）
      v175 = sub_495500(v174);  // sub_495500 —— 槽对乘积读取（+844/+858）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v173 + 888))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        1000,  // （上一表达式的参数/条件续行）
        LODWORD(pAnimObj_6) * (int)pMem * v175 / 10000);  // （上一表达式的参数/条件续行）
      if ( nBigState != 20 )  // 判定字段 this[1639] != 20
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 52));  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 9);  // （表达式续行/复合语句）
        v176 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 9);  // （表达式续行/复合语句）
        *(this + 2184) = sub_47EF20(1, v176, -1, -1, 11);  // （表达式续行/复合语句）
        *(this + 2184) = sub_41A5E0((unsigned int)(this + 2076)) * *(this + 2184) / 100;  // （表达式续行/复合语句）
        pThis_81C2 = sub_41A5E0((unsigned int)(this + 2076));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
        v178 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
        *(this + 2129) = 9;  // （表达式续行/复合语句）
        v504 = 15;
        v503 = 0;
        LOBYTE(Block[0]) = 0;  // （表达式续行/复合语句）
        *(this + 2187) = 100000 / (pThis_81C2 * v178);  // （表达式续行/复合语句）
        v179 = *this;  // （表达式续行/复合语句）
        v506 = 24;
        v180 = (*(int (/*thiscall*/ **)(int *))(v179 + 1096))(this);  // （表达式续行/复合语句）
        if ( v180 >= 0 )  // 条件判定
        {
          if ( v180 <= 3 )  // 条件判定
          {
            sub_406D60("R_GUN_GRAZE_LOOP");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          }
          else if ( v180 == 4 )  // 否则条件分支
          {
            sub_406D60("R_BOWGUN_GRAZE_LOOP");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          }
        }
        Block4 = (void **)Block[0];  // （表达式续行/复合语句）
        if ( v504 < 0x10 )  // 条件判定
          Block4 = Block;
        (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, Block4, 11, 0, 0);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          "GN_RANDOMSHOT",  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        *(this + 2188) = 0;  // （表达式续行/复合语句）
        *(this + 2189) = 0;  // （表达式续行/复合语句）
        fld_e2187 = -*(this + 2187);  // （表达式续行/复合语句）
        *(this + 2183) = -1;  // （表达式续行/复合语句）
        *(this + 2186) = fld_e2187;  // （表达式续行/复合语句）
        sub_6569D0(this + 2130);  // 通用双向链表清空器: free 全部节点 + 哨兵自指 + 计数清零
        *(this + 2133) = sub_699000((int)(this + 2));  // （表达式续行/复合语句）
        v506 = -1;
        if ( v504 >= 0x10 )  // 条件判定
          j__free(Block[0]);  // （表达式续行/复合语句）
      }
      v183 = (*(int (/*thiscall*/ **)(int *))(*this + 1096))(this);  // （表达式续行/复合语句）
      if ( v183 == 1 )  // 条件判定
        v183 = 0;
      v184 = sub_4C1000(this);  // sub_4C1000
      if ( v183 == 4 )  // 条件判定
        v184 = 4;
      pMem = (void *)(5 * v183 + 1095);  // （表达式续行/复合语句）
      pThis_2 = *(this + 2 * ((uint32_t)pMem + v184));  // （表达式续行/复合语句）
      pThis_22 = (int)(this + 2 * ((uint32_t)pMem + v184));  // （表达式续行/复合语句）
      if ( pThis_2 == 0 )  // 条件判定
      {
        v186 = sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
        pAnimObj_6 = *(float *)&v186;  // （表达式续行/复合语句）
        v506 = 25;
        if ( v186 != 0 )  // 条件判定
        {
          fld_e96 = (unsigned int)*(this + 96) < 0x10 ? (const char *)(this + 91) : (const char *)*(this + 91);  // （表达式续行/复合语句）
          // ── [段 22] 第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚 ──
          v188 = sub_4319E0(v186, v183, v184, fld_e96, "Effect/Animation/ShootEffect/RandomShoot1.ani", 1);  // sub_4319E0 —— 动画件构造（文件名与参数版）
        }
        else  // 否则分支
        {
          v188 = 0;
        }
        v506 = -1;
        *(uint32_t *)pThis_22 = v188;  // （表达式续行/复合语句）
        v189 = sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
        pAnimObj_6 = *(float *)&v189;  // （表达式续行/复合语句）
        v506 = 26;
        if ( v189 != 0 )  // 条件判定
        {
          fld_e962 = (unsigned int)*(this + 96) < 0x10 ? (const char *)(this + 91) : (const char *)*(this + 91);  // （表达式续行/复合语句）
          v191 = sub_4319E0(v189, v183, v184, fld_e962, "Effect/Animation/ShootEffect/RandomShoot2.ani", 1);  // sub_4319E0 —— 动画件构造（文件名与参数版）
        }
        else  // 否则分支
        {
          v191 = 0;
        }
        v506 = -1;
        *(this + 8 * v183 + 2 * v183 + 2 * v184 + 2191) = v191;  // （表达式续行/复合语句）
        if ( v184 == 1 )  // 条件判定
        {
          pThis_88C3 = 2;
          do
          {
            for ( mm = 0; ; ++mm )  // 循环（遍历）
            {
              pThis_23 = *(this + 2 * (uint32_t)pMem + 2);  // （表达式续行/复合语句）
              v194 = *(uint32_t *)(pThis_23 + 44);  // （表达式续行/复合语句）
              if ( v194 != 0 )  // 条件判定
                v194 = (*(uint32_t *)(pThis_23 + 48) - v194) / 88;  // （表达式续行/复合语句）
              if ( mm >= v194 )  // 条件判定
                break;  // 跳出本分支
              *(uint32_t *)(sub_4924C0(mm) + 40) = 2;  // （表达式续行/复合语句）
            }
            --pThis_88C3;  // （表达式续行/复合语句）
          }
          while ( *(float *)&pThis_88C3 != 0.0 );  // 循环
        }
      }
      v195 = (int *)pThis_22;  // （表达式续行/复合语句）
      pThis_88C2 = this + 2188;  // （表达式续行/复合语句）
      v197 = 0;
      pThis_88C3 = (int)(this + 2188);  // （表达式续行/复合语句）
      do
      {
        v198 = *pThis_88C2;  // （表达式续行/复合语句）
        if ( v198 != *v195 )  // 条件判定
        {
          if ( v198 != 0 )  // 条件判定
            (*(void (/*thiscall*/ **)(int *, int))(*this + 208))(this, v198);  // （表达式续行/复合语句）
          v199 = *v195;  // （表达式续行/复合语句）
          *(uint32_t *)pThis_88C3 = *v195;  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
            this,  // （上一表达式的参数/条件续行）
            2 * (v197 == 0) - 1,  // （上一表达式的参数/条件续行）
            v199,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
        }
        ++v197;  // 自增
        pThis_88C2 = (int *)(pThis_88C3 + 4);  // （表达式续行/复合语句）
        ++v195;  // 自增
        pThis_88C3 += 4;  // （表达式续行/复合语句）
      }
      while ( v197 < 2 );  // 循环
      v200 = **(void ***)(pArg3 + 4);  // （表达式续行/复合语句）
      fld_e2183 = (void *)*(this + 2183);  // （表达式续行/复合语句）
      v202 = 0;
      pMem = fld_e2183;
      *(this + 2183) = (int)v200;  // （表达式续行/复合语句）
      if ( v200 == (void *)1 )  // 条件判定
      {
        v202 = 4;
      }
      else if ( v200 == (void *)2 )  // 否则条件分支
      {
        v202 = 9;
      }
      else if ( v200 == (void *)3 )  // 否则条件分支
      {
        v202 = 14;
      }
      if ( fld_e2183 == v200 )  // 判定字段 this[2183] == v200
        ++v202;  // 自增
      pAnimObj_ = *(this + 30);  // 读字段 fld_e303 = this[30]
      v204 = sub_491C70(pAnimObj_, v202);  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
      sub_493A60(pAnimObj_, v204);  // sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
      LOBYTE(nArg5) = 0;  // （表达式续行/复合语句）
      pThis_88C3 = (int)(this + 2188);  // （表达式续行/复合语句）
      pThis_22 = 2;
      do
      {
        v205 = *(uint32_t *)pThis_88C3;  // （表达式续行/复合语句）
        v206 = sub_491C70(*(uint32_t *)pThis_88C3, v202);  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
        sub_493A60(v205, v206);  // sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
        v207 = pThis_22 == 1;  // （表达式续行/复合语句）
        pThis_88C3 += 4;  // （表达式续行/复合语句）
        --pThis_22;  // （表达式续行/复合语句）
      }
      while ( !v207 );  // 循环
      *(this + 2185) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);  // （表达式续行/复合语句）
      if ( nBigState != 20 && pMem != (void *)*(this + 2183) )  // 判定字段 this[1639]（大状态/子状态门）
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          "R_GN_RANDOMSHOT_CHANGE",  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          "R_QUICK_MOTION",  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
      }
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 23] 第二重 case 21：★ 格挡反击/照准（Swordman GuardSpark/GuardCircle.ani 复用）──
    //   pArg3[1][0]/[1]/[2] 三读取入 v209/v210/v213；vt+124 取坐标 + v506 状态号栈；
    //   sub_431860 三次建 Character/Swordman/Effect/Animation/GuardSpark.ani 与 GuardCircle.ani；
    //   （1775 行）fld_e295/fld_e296 存对象槽后 goto LABEL_482
    case 21:  // case 21 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SWD_GUARDED", -1, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_GN_GUNGUARD", -1, 0, 0);  // （表达式续行/复合语句）
      v208 = *(int **)(pArg3 + 4);  // （表达式续行/复合语句）
      v209 = *v208;  // （表达式续行/复合语句）
      v210 = v208[1];  // （表达式续行/复合语句）
      v211 = *this;  // （表达式续行/复合语句）
      pThis_88C3 = v209;
      v488 = v210;
      v212 = (*(int (/*thiscall*/ **)(int *))(v211 + 124))(this);  // （表达式续行/复合语句）
      v213 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);  // （表达式续行/复合语句）
      pThis_22 = v212;
      pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
      v506 = 27;
      if ( pMem != nullptr )  // 条件判定
        v214 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else  // 否则分支
        v214 = 0;
      v506 = -1;
      pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
      v506 = 28;
      if ( pMem != nullptr )  // 条件判定
        pObj7 = sub_44E1F0(v214, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
      else  // 否则分支
        pObj7 = 0;
      fld_e295 = *(this + 29);  // 读字段 fld_e295 = this[29]
      v506 = -1;
      sub_45FE80(fld_e295, v213, 2, 0, pObj7, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj7 + 148))(pObj7, pThis_88C3);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 112))(pObj7, v488, pThis_22, v213);  // （表达式续行/复合语句）
      pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
      v506 = 29;
      if ( pMem != nullptr )  // 条件判定
        v217 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardCircle.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else  // 否则分支
        v217 = 0;
      v506 = -1;
      pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
      v506 = 30;
      if ( pMem != nullptr )  // 条件判定
        pObj9 = sub_44E1F0(v217, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
      else  // 否则分支
        pObj9 = 0;
      fld_e296 = *(this + 29);  // 读字段 fld_e296 = this[29]
      v506 = -1;
      sub_45FE80(fld_e296, v213, 2, 0, pObj9, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj9 + 148))(pObj9, pThis_88C3);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 112))(pObj9, v488, pThis_22, v213);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 56));  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 3, 1000, 1000);  // （表达式续行/复合语句）
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 24] 第二重 case 22：★ 副武器发射（SteyrShoot / LaserRifle / Gatling 系）──
    //   pArg3[1][0] → v220，pArg3[1][1] → v222；this[2129] 副武器状态号；
    //   switch(v220) 五型：LABEL_332 汇合；含 sub_431920 建 SteyrShoot.ani、LaserRifleEffect 四件
    //   （FireOnceEffect/FireOnceSpark/FireRing/ChargingEffect/ChargeFullEffect）、
    //   GatlingGunOverHeat/GatlingOverHeat/GatlingGunShoot/AerialGatlingGunShoot.ani 与
    //   sub_4C3640 建 Effect/Particle/GatlingShell.ptl 两处；末段按 this[2242]==0 处理（2473）
    case 22:  // case 22 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
      pMem = (void *)*(this + 2242);  // （表达式续行/复合语句）
      v220 = **(uint32_t **)(pArg3 + 4);  // （表达式续行/复合语句）
      pThis_851 = this + 2129;  // （表达式续行/复合语句）
      *(this + 2129) = v220;  // （表达式续行/复合语句）
      v222 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);  // （表达式续行/复合语句）
      v223 = -1;
      *(this + 2242) = v222;  // （表达式续行/复合语句）
      pThis_88C3 = 5;
      switch ( v220 )  // 分派 switch
      {
        case 12:  // case 12 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
          pThis_88C3 = 1;
LABEL_332:  // 标签 LABEL_332：合流点
          v223 = 17;
          break;  // 跳出本分支
        case 13:  // case 13 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
        case 36:  // case 36 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
          *(float *)&pThis_88C3 = 0.0;  // （表达式续行/复合语句）
          goto LABEL_332;  // 跳转合流点 LABEL_332
        case 14:  // case 14 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
          pThis_88C3 = 1;
          v223 = 21;
          break;  // 跳出本分支
        case 39:  // case 39 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
          pThis_88C3 = 2;
          goto LABEL_332;  // 跳转合流点 LABEL_332
        case 40:  // case 40 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
          pThis_88C3 = 4;
          v223 = 15;
          break;  // 跳出本分支
        default:  // 未列出的值 → 兜底
          break;  // 跳出本分支
      }
      v224 = v222 + v223;  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4 * v224));  // （表达式续行/复合语句）
      sub_4C4890(this, pThis_88C3, v224);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *pThis_851);  // （表达式续行/复合语句）
      LODWORD(v226) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *pThis_851);  // （表达式续行/复合语句）
      nDmgCapCtx = *(this + 2242);  // 读字段 fld_e2242 = this[2242]
      pThis_88C3 = v226;
      LODWORD(v226) = 1000;  // （表达式续行/复合语句）
      v488 = 1000;
      if ( nDmgCapCtx == 0 )  // 判定字段 this[2242] == 0
      {
        pAnimObj_6 = *(float *)(*(this + 30) + 36);  // （表达式续行/复合语句）
        pThis_22 = LODWORD(pAnimObj_6);  // （表达式续行/复合语句）
        switch ( *pThis_851 )  // 分派 switch
        {
          case 0xC:  // case 0xC 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
            v488 = (*(int (/*thiscall*/ **)(int *, int))(*this + 900))(this, 3);  // （表达式续行/复合语句）
            v230 = sub_47EF20(1, pThis_88C3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
            goto LABEL_338;  // 跳转合流点 LABEL_338
          case 0xD:  // case 0xD 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
          case 0x24:  // case 0x24 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
          case 0x27:  // case 0x27 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
            v227 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // （表达式续行/复合语句）
            v488 = sub_495540(v227);  // sub_495540 —— 槽对乘积读取（+872/+886）
            v228 = sub_4B1C40(pThis_88C3);  // sub_4B1C40 —— 14 字节表按 1 基索引取值
            v229 = *this;  // （表达式续行/复合语句）
            pThis_22 = v228;
            (*(void (/*thiscall*/ **)(int *, float, int))(v229 + 992))(this, COERCE_FLOAT(LODWORD(pAnimObj_6)), 1);  // （表达式续行/复合语句）
            break;  // 跳出本分支
          case 0x28:  // case 0x28 分派：第二重 case 20 之建件主体：sub_4319E0(件, 枪种, ...) 建 RandomShoot1/2.ani 两枚
            v488 = (*(int (/*thiscall*/ **)(int *, int))(*this + 900))(this, 3);  // （表达式续行/复合语句）
            v230 = sub_47EF20(2, pThis_88C3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
LABEL_338:  // 标签 LABEL_338：合流点
            pThis_22 = v230;
            break;  // 跳出本分支
          default:  // 未列出的值 → 兜底
            break;  // 跳出本分支
        }
        v226 = (uint64_t)((double)v488 * ((double)SLODWORD(pAnimObj_6) / (double)pThis_22));  // （表达式续行/复合语句）
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, uint32_t))(*this + 888))(this, 0, 0, 1000, v226);  // （表达式续行/复合语句）
      v231 = *pThis_851;  // （表达式续行/复合语句）
      if ( *pThis_851 == 40 )  // 条件判定
      {
        nDmgCapCtx_ = *(this + 2242);  // 读字段 fld_e22422 = this[2242]
        if ( nDmgCapCtx_ != 0 )  // 判定字段 this[22422] != 0
        {
          if ( nDmgCapCtx_ == 1 )  // 判定字段 this[22422] == 1
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 条件判定
            {
              v233 = *this;  // （表达式续行/复合语句）
              v234 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t))(*this + 152))(this, 0, 0, 0);  // （表达式续行/复合语句）
              v235 = (*(int (/*thiscall*/ **)(int *, const char *, uint32_t, int, uint32_t, int, int))(*this + 588))(  // （表达式续行/复合语句）
                       this,  // （上一表达式的参数/条件续行）
                       "Particle/SubWeapon/Steyr.ptl",  // （上一表达式的参数/条件续行）
                       0,  // （上一表达式的参数/条件续行）
                       150,  // （上一表达式的参数/条件续行）
                       0,  // （上一表达式的参数/条件续行）
                       85,  // （上一表达式的参数/条件续行）
                       v234);  // （上一表达式的参数/条件续行）
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(v233 + 580))(this, 22203, 0, v235);  // （表达式续行/复合语句）
            }
            v502 = 0.0;  // v502 = 0.0（浮点初值）
            v503 = 0;
            *(float *)&v504 = 0.0;  // （表达式续行/复合语句）
            v506 = 31;
            sub_431230((int)&v501, this + 2129);  // sub_431230 —— uint32 vector push_back
            pMem = nullptr;  // pMem = 空指针
            sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
            pMem = nullptr;  // pMem = 空指针
            sub_431230((int)&v501, &pMem);  // sub_431230 —— uint32 vector push_back
            (*(void (/*thiscall*/ **)(int *, int, float *, uint32_t, uint32_t))(*this + 560))(this, 26, &v501, 0, 0);  // （表达式续行/复合语句）
            if ( *(this + 2358) == 0 )  // 条件判定
            {
              pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
              LOBYTE(v506) = 32;  // （表达式续行/复合语句）
              if ( pMem != nullptr )  // 条件判定
              {
                pThis_5A = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                // ── [段 25] 第二重 case 22 之 40 号状态：★ SteyrShoot.ani（斯泰尔射击主件）──
                v237 = sub_431920(pThis_5A, (char)"Effect/Animation/ShootEffect/SteyrShoot.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
              }
              else  // 否则分支
              {
                v237 = 0;
              }
              LOBYTE(v506) = 31;  // （表达式续行/复合语句）
              *(this + 2358) = v237;  // （表达式续行/复合语句）
            }
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
              this,  // （上一表达式的参数/条件续行）
              1,  // （上一表达式的参数/条件续行）
              *(this + 2358),  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
            v506 = -1;
            sub_5E5260((void **)&v501);  // sub_5E5260 —— 清理临时缓冲
          }
        }
        else  // 否则分支
        {
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GN_STEYR", -1, 0, 0);  // （表达式续行/复合语句）
        }
      }
      else  // 否则分支
      {
        // ── [段 26] 第二重 case 22 之内层 switch(v231)+2085：各副武器状态的效果选型 ──
        switch ( v231 )  // 分派 switch
        {
          case 39:  // case 39 分派：第二重 case 22 之内层 switch(v231)+2085：各副武器状态的效果选型
            nDmgCapCtx_2 = *(this + 2242);  // 读字段 fld_e22423 = this[2242]
            if ( nDmgCapCtx_2 != 0 )  // 判定字段 this[22423] != 0
            {
              if ( nDmgCapCtx_2 == 1 )  // 判定字段 this[22423] == 1
              {
                if ( *((uint8_t *)this + 9428) != 0 )  // 判定 this[9428] != 0（uint8）
                  v253 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);  // （表达式续行/复合语句）
                else  // 否则分支
                  v253 = 0;
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  "R_GN_LASER_SHOT",  // （上一表达式的参数/条件续行）
                  -1,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
                (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 13);  // （表达式续行/复合语句）
                if ( v253 < *(this + 2356) )  // 条件判定
                {
                  if ( *(this + 2347) == 0 )  // 条件判定
                  {
                    pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                    v506 = 39;
                    if ( pMem != nullptr )  // 条件判定
                    {
                      pThis_5A2 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                      v255 = sub_431920(pThis_5A2, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireOnceEffect.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                    }
                    else  // 否则分支
                    {
                      v255 = 0;
                    }
                    v506 = -1;
                    *(this + 2347) = v255;  // （表达式续行/复合语句）
                  }
                  if ( *(this + 2348) == 0 )  // 条件判定
                  {
                    pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                    v506 = 40;
                    if ( pMem != nullptr )  // 条件判定
                    {
                      pThis_5A3 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                      v257 = sub_431920(pThis_5A3, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireOnceSpark.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                    }
                    else  // 否则分支
                    {
                      v257 = 0;
                    }
                    v506 = -1;
                    *(this + 2348) = v257;  // （表达式续行/复合语句）
                  }
                  sub_4926A0(*(this + 2347));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
                  sub_4926A0(*(this + 2348));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    1,  // （上一表达式的参数/条件续行）
                    *(this + 2348),  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0);  // （上一表达式的参数/条件续行）
                }
                if ( *(this + 2349) == 0 )  // 条件判定
                {
                  pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                  v506 = 41;
                  if ( pMem != nullptr )  // 条件判定
                  {
                    pThis_5A4 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                    v259 = sub_431920(pThis_5A4, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireRing.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                  }
                  else  // 否则分支
                  {
                    v259 = 0;
                  }
                  v506 = -1;
                  *(this + 2349) = v259;  // （表达式续行/复合语句）
                }
                sub_4926A0(*(this + 2349));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  3,  // （上一表达式的参数/条件续行）
                  *(this + 2349),  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
                if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 条件判定
                {
                  v260 = *this;  // （表达式续行/复合语句）
                  v261 = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t))(*this + 152))(this, 0, 0, 0);  // （表达式续行/复合语句）
                  (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, int, uint32_t, int, int))(v260 + 580))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    22017,  // （上一表达式的参数/条件续行）
                    v253,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    150,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    85,  // （上一表达式的参数/条件续行）
                    v261);  // （上一表达式的参数/条件续行）
                }
              }
            }
            else  // 否则分支
            {
              v239 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 41) > 0;  // （表达式续行/复合语句）
              *((uint8_t *)this + 9428) = v239;  // （表达式续行/复合语句）
              if ( v239 )  // 条件判定
              {
                v473 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 41, -1);  // （表达式续行/复合语句）
                (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);  // （表达式续行/复合语句）
                *(this + 2356) = sub_47EF20(41, 0, v473, -1, 11);  // （表达式续行/复合语句）
              }
              else  // 否则分支
              {
                *(this + 2356) = 0;  // （表达式续行/复合语句）
              }
              fld_e2343 = *(this + 2343);  // 读字段 fld_e2343 = this[2343]
              *((uint8_t *)this + 9416) = 0;  // （表达式续行/复合语句）
              *(this + 2355) = 0;  // （表达式续行/复合语句）
              if ( fld_e2343 != 0 )  // 判定字段 this[2343] != 0
              {
                *(uint8_t *)(fld_e2343 + 160) = 1;  // （表达式续行/复合语句）
              }
              else  // 否则分支
              {
                pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                v506 = 33;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A5 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  // ── [段 27] 第二重 case 22 之 39 号状态（激光步枪）：ChargingEffect/ChargeFullEffect.ani 充能双件 ──
                  v242 = sub_431920(pThis_5A5, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/ChargingEffect.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                }
                else  // 否则分支
                {
                  v242 = 0;
                }
                v506 = -1;
                *(this + 2343) = v242;  // （表达式续行/复合语句）
                pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                v506 = 34;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A6 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  v244 = sub_431920(pThis_5A6, (char)"Effect/Animation/SubWeapon/LaserRifleEffect/ChargeFullEffect.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                  v506 = -1;
                  *(this + 2344) = v244;  // （表达式续行/复合语句）
                }
                else  // 否则分支
                {
                  v506 = -1;
                  *(this + 2344) = 0;  // （表达式续行/复合语句）
                }
              }
              if ( *(this + 2350) == 0 )  // 条件判定
              {
                pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                v506 = 35;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A7 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  v246 = sub_431920(  // （表达式续行/复合语句）
                           pThis_5A7,  // （上一表达式的参数/条件续行）
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleOnCharge1.ani",  // （上一表达式的参数/条件续行）
                           1);  // （上一表达式的参数/条件续行）
                }
                else  // 否则分支
                {
                  v246 = 0;
                }
                v506 = -1;
                *(this + 2350) = v246;  // （表达式续行/复合语句）
                pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                v506 = 36;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A8 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  v248 = sub_431920(  // （表达式续行/复合语句）
                           pThis_5A8,  // （上一表达式的参数/条件续行）
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleOnCharge2.ani",  // （上一表达式的参数/条件续行）
                           1);  // （上一表达式的参数/条件续行）
                }
                else  // 否则分支
                {
                  v248 = 0;
                }
                v506 = -1;
                *(this + 2351) = v248;  // （表达式续行/复合语句）
                pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                v506 = 37;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A9 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  v250 = sub_431920(  // （表达式续行/复合语句）
                           pThis_5A9,  // （上一表达式的参数/条件续行）
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleFullCharge2.ani",  // （上一表达式的参数/条件续行）
                           1);  // （上一表达式的参数/条件续行）
                }
                else  // 否则分支
                {
                  v250 = 0;
                }
                v506 = -1;
                *(this + 2352) = v250;  // （表达式续行/复合语句）
                pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                v506 = 38;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A10 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  v252 = sub_431920(  // （表达式续行/复合语句）
                           pThis_5A10,  // （上一表达式的参数/条件续行）
                           (char)"Effect/Animation/SubWeapon/LaserRifleEffect/LaserRifleFullCharge1.ani",  // （上一表达式的参数/条件续行）
                           1);  // （上一表达式的参数/条件续行）
                }
                else  // 否则分支
                {
                  v252 = 0;
                }
                v506 = -1;
                *(this + 2353) = v252;  // （表达式续行/复合语句）
              }
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                "GN_LASER",  // （上一表达式的参数/条件续行）
                -1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
            }
            break;  // 跳出本分支
          case 12:  // case 12 分派：第二重 case 22 之 39 号状态（激光步枪）：ChargingEffect/ChargeFullEffect.ani 充能双件
            nDmgCapCtx_3 = *(this + 2242);  // 读字段 fld_e22424 = this[2242]
            if ( nDmgCapCtx_3 != 0 )  // 判定字段 this[22424] != 0
            {
              if ( nDmgCapCtx_3 == 1 )  // 判定字段 this[22424] == 1
              {
                v263 = pMem == (void *)1;  // （表达式续行/复合语句）
                *((uint8_t *)this + 9301) = pMem == (void *)1;  // （表达式续行/复合语句）
                if ( v263 )  // 条件判定
                {
                  fld_e2326 = *(this + 2326);  // 读字段 fld_e2326 = this[2326]
                  pThis_668 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
                  v270 = sub_47EF20(1, pThis_88C3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
                  v271 = sub_423A80(0, v270, pThis_668, fld_e2326);  // sub_423A80 —— 同上 int 版（FTOL 截断）
                  fld_e305 = (void *)*(this + 30);  // （表达式续行/复合语句）
                  *(this + 2327) = v271;  // （表达式续行/复合语句）
                  sub_4AECE0(fld_e305, 0);
                  sub_4939E0(*(this + 30), 1);  // sub_4939E0 —— 播放/暂停级联（递归子链 +204）
                  LOBYTE(nArg5) = 0;  // （表达式续行/复合语句）
                  if ( *(this + 2334) == 0 )  // 条件判定
                  {
                    pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                    v506 = 44;
                    if ( pMem != nullptr )  // 条件判定
                    {
                      pThis_5A11 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                      // ── [段 28] 第二重 case 22 之加特林组：GatlingGunOverHeat/GatlingOverHeat/GatlingGunShoot.ani 三件 ──
                      v274 = sub_431920(pThis_5A11, (char)"Effect/Animation/GatlingGunOverHeat.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                    }
                    else  // 否则分支
                    {
                      v274 = 0;
                    }
                    v506 = -1;
                    *(this + 2334) = v274;  // （表达式续行/复合语句）
                    pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                    v506 = 45;
                    if ( pMem != nullptr )  // 条件判定
                    {
                      pThis_5A12 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                      v276 = sub_431920(pThis_5A12, (char)"Effect/Animation/GatlingOverHeat.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                    }
                    else  // 否则分支
                    {
                      v276 = 0;
                    }
                    v506 = -1;
                    *(this + 2335) = v276;  // （表达式续行/复合语句）
                  }
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    1,  // （上一表达式的参数/条件续行）
                    *(this + 2334),  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0);  // （上一表达式的参数/条件续行）
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    2,  // （上一表达式的参数/条件续行）
                    *(this + 2335),  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0);  // （上一表达式的参数/条件续行）
                  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    "MACHINEGUN_OVERHIT",  // （上一表达式的参数/条件续行）
                    -1,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0);  // （上一表达式的参数/条件续行）
                }
                else  // 否则分支
                {
                  *(this + 2326) = sub_47EF20(2, pThis_88C3, -1, -1, 11);  // （表达式续行/复合语句）
                  sub_4C1440(this);
                  v264 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // （表达式续行/复合语句）
                           dword_8F84E4,  // （上一表达式的参数/条件续行）
                           "Character/Gunner/Particle/SubWeapon/Gatling.ptl");  // （上一表达式的参数/条件续行）
                  (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), v264);  // （表达式续行/复合语句）
                  v265 = 1000 / sub_47E9D0(0);  // （表达式续行/复合语句）
                  *(this + 2330) = 0;  // （表达式续行/复合语句）
                  *(this + 2331) = -1;  // （表达式续行/复合语句）
                  *(this + 2329) = v265;  // （表达式续行/复合语句）
                  *(this + 2328) = -v265;  // （表达式续行/复合语句）
                  if ( *(this + 2332) == 0 )  // 条件判定
                  {
                    pMem = operator new(0x12Cu);  // （表达式续行/复合语句）
                    v506 = 42;
                    if ( pMem != nullptr )  // 条件判定
                    {
                      pThis_5A13 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                      v267 = sub_4C3640(pThis_5A13, "Effect/Particle/GatlingShell.ptl", this);  // sub_4C3640
                    }
                    else  // 否则分支
                    {
                      v267 = 0;
                    }
                    v506 = -1;
                    *(this + 2332) = v267;  // （表达式续行/复合语句）
                  }
                  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2332) + 12))(*(this + 2332), 0);  // （表达式续行/复合语句）
                  if ( *(this + 2333) == 0 )  // 条件判定
                  {
                    pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                    v506 = 43;
                    if ( pMem != nullptr )  // 条件判定
                    {
                      pThis_5A14 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                      v269 = sub_431920(pThis_5A14, (char)"Effect/Animation/GatlingGunShoot.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                    }
                    else  // 否则分支
                    {
                      v269 = 0;
                    }
                    v506 = -1;
                    *(this + 2333) = v269;  // （表达式续行/复合语句）
                  }
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    1,  // （上一表达式的参数/条件续行）
                    *(this + 2333),  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0);  // （上一表达式的参数/条件续行）
                }
              }
            }
            else  // 否则分支
            {
              *((uint8_t *)this + 9301) = 0;  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                "GN_GATTLING",  // （上一表达式的参数/条件续行）
                -1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
            }
            break;  // 跳出本分支
          case 13:  // case 13 分派：第二重 case 22 之加特林组：GatlingGunOverHeat/GatlingOverHeat/GatlingGunShoot.ani 三件
          case 36:  // case 36 分派：第二重 case 22 之加特林组：GatlingGunOverHeat/GatlingOverHeat/GatlingGunShoot.ani 三件
            nDmgCapCtx_4 = *(this + 2242);  // 读字段 fld_e22425 = this[2242]
            if ( nDmgCapCtx_4 != 0 )  // 判定字段 this[22425] != 0
            {
              if ( nDmgCapCtx_4 == 1 )  // 判定字段 this[22425] == 1
              {
                v207 = pMem != (void *)1;  // （表达式续行/复合语句）
                *((uint8_t *)this + 9301) = pMem == (void *)1;  // （表达式续行/复合语句）
                if ( v207 )  // 条件判定
                {
                  *(this + 2326) = sub_47EF20(1, pThis_88C3, -1, -1, 11);  // （表达式续行/复合语句）
                  v286 = "Character/Gunner/Effect/Particle/FlameThrower.ptl";  // （表达式续行/复合语句）
                  if ( *pThis_851 != 13 )  // 条件判定
                    v286 = "Character/Gunner/Effect/Particle/FlameThrowerBoost.ptl";  // （表达式续行/复合语句）
                  sub_401710(v286);  // sub_401710 —— std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
                  v287 = *(uint32_t *)dword_8F84E4;  // （表达式续行/复合语句）
                  v506 = 46;
                  v288 = unknown_libname_2(v499);  // （表达式续行/复合语句）
                  v289 = (*(int (/*thiscall*/ **)(int, int))(v287 + 4))(dword_8F84E4, v288);  // （表达式续行/复合语句）
                  (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), v289);  // （表达式续行/复合语句）
                  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2054) + 12))(*(this + 2054), 0);  // （表达式续行/复合语句）
                  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 条件判定
                    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // （表达式续行/复合语句）
                      this,  // （上一表达式的参数/条件续行）
                      *pThis_851 != 13 ? 22204 : 22201,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      141,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      88,  // （上一表达式的参数/条件续行）
                      4,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0);  // （上一表达式的参数/条件续行）
                  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    "FLAMETHROWER_FIRE",  // （上一表达式的参数/条件续行）
                    -1,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0);  // （上一表达式的参数/条件续行）
                  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    "FLAMETHROWER_LOOP",  // （上一表达式的参数/条件续行）
                    12,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0);  // （上一表达式的参数/条件续行）
                  v506 = -1;
                  sub_501490(v499);  // std::string 析构（本条目串：数据@+4/长度@+20/容量@+24）：容量
                }
                else  // 否则分支
                {
                  fld_e23262 = *(this + 2326);  // 读字段 fld_e23262 = this[2326]
                  pThis_6682 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
                  v290 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
                  v291 = sub_423A80(0, v290, pThis_6682, fld_e23262);  // sub_423A80 —— 同上 int 版（FTOL 截断）
                  fld_e306 = (void *)*(this + 30);  // （表达式续行/复合语句）
                  *(this + 2327) = v291;  // （表达式续行/复合语句）
                  sub_4AECE0(fld_e306, 0);
                  sub_4939E0(*(this + 30), 1);  // sub_4939E0 —— 播放/暂停级联（递归子链 +204）
                  LOBYTE(nArg5) = 0;  // （表达式续行/复合语句）
                  (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 12);  // （表达式续行/复合语句）
                }
              }
            }
            else  // 否则分支
            {
              *((uint8_t *)this + 9301) = 0;  // （表达式续行/复合语句）
              if ( v231 == 13 )  // 条件判定
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  "GN_FLAMETHROWER",  // （上一表达式的参数/条件续行）
                  -1,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
              else  // 否则分支
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  "R_GN_FLAMETHROWER_SHOT",  // （上一表达式的参数/条件续行）
                  -1,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
            }
            break;  // 跳出本分支
          default:  // 未列出的值 → 兜底
            if ( v231 == 14 && *(this + 2242) == 1 )  // 条件判定
            {
              v277 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(  // （表达式续行/复合语句）
                       dword_8F84E4,  // （上一表达式的参数/条件续行）
                       "Character/Gunner/Particle/SubWeapon/AerialGatling.ptl");  // （上一表达式的参数/条件续行）
              (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2054) + 8))(*(this + 2054), v277);  // （表达式续行/复合语句）
              *(this + 2329) = 100;  // （表达式续行/复合语句）
              *(this + 2328) = -100;  // （表达式续行/复合语句）
              *(this + 2330) = 0;  // （表达式续行/复合语句）
              v278 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
              fld_e2329 = v278 * *(this + 2329);  // （表达式续行/复合语句）
              *(this + 2331) = v278;  // （表达式续行/复合语句）
              fld_e2332 = *(this + 2332);  // 读字段 fld_e2332 = this[2332]
              *(this + 2326) = fld_e2329 + 200;  // （表达式续行/复合语句）
              if ( fld_e2332 == 0 )  // 判定字段 this[2332] == 0
              {
                pMem = operator new(0x12Cu);  // （表达式续行/复合语句）
                v506 = 47;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A15 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  // ── [段 29] 第二重 case 22 之弹壳粒子：sub_4C3640 建 Effect/Particle/GatlingShell.ptl 两处 ──
                  v282 = sub_4C3640(pThis_5A15, "Effect/Particle/GatlingShell.ptl", this);  // sub_4C3640
                }
                else  // 否则分支
                {
                  v282 = 0;
                }
                v506 = -1;
                *(this + 2332) = v282;  // （表达式续行/复合语句）
              }
              (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2332) + 12))(*(this + 2332), 0);  // （表达式续行/复合语句）
              if ( *(this + 2341) == 0 )  // 条件判定
              {
                pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                v506 = 48;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A16 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  v284 = sub_431920(pThis_5A16, (char)"Effect/Animation/AerialGatlingGunShoot.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                }
                else  // 否则分支
                {
                  v284 = 0;
                }
                v506 = -1;
                *(this + 2341) = v284;  // （表达式续行/复合语句）
              }
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                1,  // （上一表达式的参数/条件续行）
                *(this + 2341),  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
            }
            break;  // 跳出本分支
        }
      }
      if ( *(this + 2242) == 0 )  // 条件判定
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          "SUBWEAPON_DRAW",  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        *((uint8_t *)this + 9300) = 0;  // （表达式续行/复合语句）
        for ( nn = 2; nn <= 3; ++nn )  // 循环（遍历）
        {
          v294 = sub_4924C0(nn);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
          sub_5E5260((void **)(v294 + 56));  // sub_5E5260 —— 清理临时缓冲
        }
        if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 34) > 0 )  // 条件判定
        {
          Block[1] = (void *)-1049624576;  // （表达式续行/复合语句）
          v503 = 1106247680;
          for ( i1 = 2; i1 <= 3; ++i1 )  // 循环（遍历）
          {
            v296 = (uint32_t *)sub_4924C0(i1);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
            v297 = *v296;  // （表达式续行/复合语句）
            v298 = *(char **)(*v296 + 28);  // （表达式续行/复合语句）
            v502 = (float)*(unsigned int *)(*v296 + 20);  // （表达式续行/复合语句）
            pMem = v298;
            pMem = &v298[v296[3]];  // （表达式续行/复合语句）
            v299 = *(uint32_t *)(v297 + 24);  // （表达式续行/复合语句）
            *(float *)Block = (float)(int)pMem;  // （表达式续行/复合语句）
            v300 = (double)*(int *)(v297 + 24);  // （表达式续行/复合语句）
            if ( v299 < 0 )  // 条件判定
              v300 = v300 + 4294967300.0;  // （表达式续行/复合语句）
            v301 = v296[4];  // （表达式续行/复合语句）
            *(float *)&v504 = v300;  // （表达式续行/复合语句）
            pMem = (void *)-(*(uint32_t *)(v297 + 32) + v299 + v301);  // （表达式续行/复合语句）
            v501 = (float)(unsigned int)pMem;  // （表达式续行/复合语句）
            v302 = sub_4924C0(i1);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
            sub_4931A0((int *)(v302 + 56), Block);  // sub_4931A0 —— 盒 vector 追加一组（6 float=24B；容量不足走 sub_493000 扩容）
          }
          fld_e139 = *(this + 139) + 608;  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *))(*this + 344))(this);  // （表达式续行/复合语句）
          v303 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 1160))(this, 34, 0, v303);  // （表达式续行/复合语句）
          pMem = (void *)sub_47EF20(34, -1, -1, 11, fld_e139);  // sub_47EF20 —— 读攻击数据表
          *((float *)this + 97) = (float)(int)pMem;  // （表达式续行/复合语句）
        }
      }
LABEL_482:  // 标签 LABEL_482：合流点
      sub_4B89D0(nArg2, pArg3, *(float *)&nArg4, *(float *)&nArg5);  // sub_4B89D0 —— 跑步地面循环 + 蓄气/霸体特效
      // ── [段 30] ★ LABEL_482：本帧公共尾 —— sub_4B89D0 参数登记 + 第三重 switch(nArg2) 动作事件号 ──
      //   第三重 case 表：0/4/6/7/8/10/12/14（各 case 多为 return，不落公共尾）
      switch ( nArg2 )  // 分派 switch
      {
        // ── [段 31] 第三重 case 0：清 this[2134]/[2135] 双槽后 return（空操作态）──
        case 0:  // case 0 分派：★ LABEL_482：本帧公共尾 —— sub_4B89D0 参数登记 + 第三重 switch(nArg2) 动作事件号
          *(this + 2134) = -1;  // （表达式续行/复合语句）
          *(this + 2135) = -1;  // （表达式续行/复合语句）
          return;  // 返回（本帧结束）
        // ── [段 32] 第三重 case 4：this[1708]==2 时按 vt+1140(8) 正负两支处理，return ──
        case 4:  // case 4 分派：第三重 case 4：this[1708]==2 时按 vt+1140(8) 正负两支处理，return
          if ( *(this + 1708) == 2 )  // 条件判定
          {
            if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 8) <= 0 )  // 条件判定
            {
              *(this + 2166) = -1;  // （表达式续行/复合语句）
            }
            else  // 否则分支
            {
              pAnimObj_4 = *(this + 30);  // 读字段 fld_e307 = this[30]
              v442 = *(uint32_t *)(pAnimObj_4 + 212);  // （表达式续行/复合语句）
              if ( v442 != 0 )  // 条件判定
                v443 = sub_4910A0(v442);  // sub_4910A0 —— 沿 +212 同步源链上溯，返回链尾对象的累计播放时刻（+32）
              else  // 否则分支
                v443 = *(uint32_t *)(pAnimObj_4 + 32);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 8);  // （表达式续行/复合语句）
              v444 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
              *(this + 2166) = sub_491C10(*(this + 30)) - v443 - v444;  // （表达式续行/复合语句）
            }
          }
          return;  // 返回（本帧结束）
        // ── [段 33] 第三重 case 6：fld_e1639==7 时（+1723==1 特例）sub_4C2020(v494, vt+1096()) 组串 + vt+212 播报后 return ──
        case 6:  // case 6 分派：第三重 case 6：fld_e1639==7 时（+1723==1 特例）sub_4C2020(v494, vt+1096()) 组串 + vt+212 
          if ( nBigState == 7 )  // 判定字段 this[1639] == 7
          {
            if ( *(this + 1723) == 1 )  // 条件判定
            {
              fld_e2155 = abs32(*(this + 2155));  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                fld_e2155,  // （上一表达式的参数/条件续行）
                fld_e2155,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              v420 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
              if ( *(this + 2155) < 0 )  // 条件判定
                v420 = sub_432E50(v420);  // sub_432E50 —— 关系码对调映射
              (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, v420, 4);  // （表达式续行/复合语句）
            }
            v498 = 15;
            v497 = 0;
            LOBYTE(v495[0]) = 0;  // （表达式续行/复合语句）
            v421 = *this;  // （表达式续行/复合语句）
            v506 = 60;
            v422 = (*(int (/*thiscall*/ **)(int *))(v421 + 1096))(this);  // （表达式续行/复合语句）
            sub_4C2020((int)v494, v422);
            v423 = (void **)v495[0];  // （表达式续行/复合语句）
            if ( v498 < 0x10 )  // 条件判定
              v423 = v495;
            (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v423, -1, 0, 0);  // （表达式续行/复合语句）
            if ( v498 >= 0x10 )  // 条件判定
              goto LABEL_630;  // 跳转合流点 LABEL_630
          }
          return;  // 返回（本帧结束）
        // ── [段 34] 第三重 case 7：★★ 本函数最大分支 —— 连发计数与枪口烟雾/弹壳（约 590 行）──
        //   fld_e1639==7 时 --this[1724] 计数并取 +2154 计时器两支（2593-2613）；
        //   else 清 +2154=0 与 sub_41A590(+2136, 0)（2617-2618）；
        //   主体含 sub_431920 建多枚 .ani（含 WindmillDust3.ani 与 Character/Swordman/ 系复用）、
        //   vt+1140/vt+1160 多次取参、vt+876 位移链、sub_44B6C0/sub_44E1F0/sub_45FE80 粒子挂接三件套；
        //   LABEL_630 为 j__free(v495[0]) 释放 string 的 return 点（2716-2719）
        case 7:  // case 7 分派：第三重 case 6：fld_e1639==7 时（+1723==1 特例）sub_4C2020(v494, vt+1096()) 组串 + vt+212 
          if ( nBigState == 7 )  // 判定字段 this[1639] == 7
          {
            --*(this + 1724);  // （表达式续行/复合语句）
            fld_e2154 = *(this + 2154);  // 读字段 fld_e2154 = this[2154]
            if ( fld_e2154 != 0 )  // 判定字段 this[2154] != 0
            {
              if ( fld_e2154 == 1 || fld_e2154 == 2 )  // 判定字段 this[2154]（大状态/子状态门）
              {
                pThis_858 = sub_41A5E0((unsigned int)(this + 2136));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
                if ( pThis_858 < sub_41A5E0((unsigned int)(this + 2062)) )  // 条件判定
                  *(this + 2154) = (*(this + 2154) == 1) + 1;  // （表达式续行/复合语句）
                else  // 否则分支
                  *(this + 2154) = 3;  // （表达式续行/复合语句）
              }
              else  // 否则分支
              {
                off_77F3FC(aCriticalErrorJ, *(this + 2154));  // （表达式续行/复合语句）
              }
            }
            else  // 否则分支
            {
              *(this + 2154) = 1;  // （表达式续行/复合语句）
            }
          }
          else  // 否则分支
          {
            *(this + 2154) = 0;  // （表达式续行/复合语句）
            sub_41A590((unsigned int)(this + 2136), v327, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
          }
          fld_e21542 = *(this + 2154);  // 读字段 fld_e21542 = this[2154]
          if ( fld_e21542 != 0 )  // 判定字段 this[21542] != 0
          {
            if ( fld_e21542 == 1 || fld_e21542 == 2 )  // 判定字段 this[21542]（大状态/子状态门）
            {
              pThis_8582 = sub_41A5E0((unsigned int)(this + 2136));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
              sub_41A590((unsigned int)(this + 2136), v434, pThis_8582 + 1);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
              pThis_6683 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
              *(this + 2140) = sub_4C0DF0(0) + pThis_6683;  // （表达式续行/复合语句）
              v436 = sub_4C0DF0(1);
              v437 = *this;  // （表达式续行/复合语句）
              *(this + 2141) = *(this + 2140) + v436;  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, uint32_t))(v437 + 196))(this, *(uint32_t *)(*(this + 1554) + 20));  // （表达式续行/复合语句）
              pAnimObj_3 = *(this + 30);  // 读字段 fld_e308 = this[30]
              fld_e21543 = sub_491C70(pAnimObj_3, *(this + 2154) != 1 ? 3 : 0);  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
              sub_493A60(pAnimObj_3, fld_e21543);  // sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
              fld_e2156 = *(this + 2156);  // 读字段 fld_e2156 = this[2156]
              if ( fld_e2156 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2156 + 80))() != 0 )  // 判定字段 this[2156]（大状态/子状态门）
              {
                (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  1,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
                (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
                sub_495890(0, 0);  // sub_495890 —— 模式选择式方位设置（1/2/其他 三分支）
                sub_494F20(2, 0.0);  // sub_494F20 —— 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
              }
            }
            else if ( fld_e21542 == 3 )  // 判定字段 this[21542]（大状态/子状态门）
            {
              v431 = *this;  // （表达式续行/复合语句）
              v432 = sub_4C0EB0(this);  // sub_4C0EB0
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v431 + 888))(this, 0, 0, 1000, v432);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 24));  // （表达式续行/复合语句）
              sub_4926A0(*(this + 30));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
            }
          }
          else  // 否则分支
          {
            v498 = 15;
            v497 = 0;
            LOBYTE(v495[0]) = 0;  // （表达式续行/复合语句）
            v427 = *this;  // （表达式续行/复合语句）
            v506 = 61;
            v428 = (*(int (/*thiscall*/ **)(int *))(v427 + 1096))(this);  // （表达式续行/复合语句）
            if ( v428 >= 0 )  // 条件判定
            {
              if ( v428 <= 3 )  // 条件判定
              {
                sub_406D60("GUN_DRAW3");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
              }
              else if ( v428 == 4 )  // 否则条件分支
              {
                sub_406D60("BOWGUN_DRAW3");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
              }
            }
            v429 = (void **)v495[0];  // （表达式续行/复合语句）
            if ( v498 < 0x10 )  // 条件判定
              v429 = v495;
            (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v429, -1, 0, 0);  // （表达式续行/复合语句）
            fld_e21562 = *(this + 2156);  // 读字段 fld_e21562 = this[2156]
            if ( fld_e21562 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e21562 + 80))() != 0 )  // 判定字段 this[21562]（大状态/子状态门）
            {
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
              sub_495890(0, 0);  // sub_495890 —— 模式选择式方位设置（1/2/其他 三分支）
              sub_494F20(2, 0.0);  // sub_494F20 —— 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
            }
            if ( v498 >= 0x10 )  // 条件判定
LABEL_630:  // 标签 LABEL_630：合流点
              j__free(v495[0]);  // （表达式续行/复合语句）
          }
          return;  // 返回（本帧结束）
        // ── [段 35] 第三重 case 8：★★ 拔枪态（约 460 行）—— +8577/+2136 状态位与枪种分支 ──
        //   fld_e1639==8 时读 +1757 与 +8577；sub_41A5E0(+8577) 1/2 时 sub_41A590 写 2/3（2730-2740）；
        //   后续含大量 vt+1160/vt+1140 取参与动画建件（含 ShootEffect 与 LaserRifle 系）；
        //   （3177）this[2129] != -1 且 != 11 时 vt+1328(0) 收束后 return
        case 8:  // case 8 分派：第三重 case 8：★★ 拔枪态（约 460 行）—— +8577/+2136 状态位与枪种分支
          if ( nBigState == 8 )  // 判定字段 this[1639] == 8
          {
            pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
            pThis_2181 = (unsigned int)this + 8577;  // （表达式续行/复合语句）
            pThis_21812 = (unsigned int)this + 8577;  // （表达式续行/复合语句）
            if ( pThis_6DD != 0 )  // 条件判定
            {
              v343 = sub_41A5E0(pThis_21812);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
              pThis_21813 = (unsigned int)this + 8577;  // （表达式续行/复合语句）
              if ( v343 == 1 )  // 条件判定
              {
                sub_41A590(pThis_21813, v344, 2);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
              }
              else  // 否则分支
              {
                v346 = sub_41A5E0(pThis_21813);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
                pThis_21814 = (unsigned int)this + 8577;  // （表达式续行/复合语句）
                if ( v346 == 2 )  // 条件判定
                {
                  sub_41A590(pThis_21814, v347, 3);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
                }
                else if ( sub_41A5E0(pThis_21814) == 3 )  // 否则条件分支
                {
                  sub_41C150((unsigned int)this + 8577, v349, 4);  // sub_41C150 —— crypt4byte 初始化转发（0x41A590）
                }
              }
            }
            else  // 否则分支
            {
              sub_41A590(pThis_21812, v341, 1);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
            }
          }
          else  // 否则分支
          {
            v328 = *(uint32_t *)(pArg3 + 4);  // （表达式续行/复合语句）
            if ( v328 != 0 && (unsigned int)((*(uint32_t *)(pArg3 + 8) - v328) >> 2) > 1 )  // 条件判定
              v329 = *(uint32_t *)(v328 + 4);  // （表达式续行/复合语句）
            else  // 否则分支
              v329 = -1;
            v330 = -1;
            *(this + 2129) = v329;  // （表达式续行/复合语句）
            if ( v329 == 20 )  // 条件判定
            {
              *((uint8_t *)this + 8608) = 1;  // （表达式续行/复合语句）
              *(this + 2129) = 5;  // （表达式续行/复合语句）
            }
            else  // 否则分支
            {
              *((uint8_t *)this + 8608) = 0;  // （表达式续行/复合语句）
            }
            nItemCtx_4 = *(this + 2129);  // 读字段 fld_e21294 = this[2129]
            if ( nItemCtx_4 == 5 || nItemCtx_4 == 47 || nItemCtx_4 == 53 )  // 判定字段 this[21294]（大状态/子状态门）
            {
              pThis_2181 = (unsigned int)this + 8577;  // （表达式续行/复合语句）
              sub_41A590((unsigned int)this + 8577, v327, 2);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
              nItemCtx_5 = *(this + 2129);  // 读字段 fld_e21295 = this[2129]
              if ( nItemCtx_5 == 5 )  // 判定字段 this[21295] == 5
              {
                (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 5);  // （表达式续行/复合语句）
                sub_47DCD0(this, -1);  // sub_47DCD0 —— 震动/资源档位设置
              }
              else if ( nItemCtx_5 == 53 )  // 判定字段 this[21295]（大状态/子状态门）
              {
                v335 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 53);  // （表达式续行/复合语句）
                (*(void (/*thiscall*/ **)(int *, int, int))(*this + 1160))(this, 53, v335);  // （表达式续行/复合语句）
                v336 = sub_4B1C40(v485);  // sub_4B1C40 —— 14 字节表按 1 基索引取值
                v485 = 3;
                v337 = 1000 * v336;  // （表达式续行/复合语句）
                v338 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);  // （表达式续行/复合语句）
                v339 = sub_495540(v338);  // sub_495540 —— 槽对乘积读取（+872/+886）
                v333 = v337 % v339;  // （表达式续行/复合语句）
                v330 = v337 / v339;  // （表达式续行/复合语句）
              }
            }
            else  // 否则分支
            {
              pThis_2181 = (unsigned int)this + 8577;  // （表达式续行/复合语句）
              sub_41A590((unsigned int)this + 8577, v327, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
            }
            sub_41A590((unsigned int)(this + 2136), v333, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
            if ( v330 != -1 )  // 条件判定
              (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*this + 992))(this, v330, 0);  // （表达式续行/复合语句）
          }
          if ( sub_41A5E0(pThis_2181) == 0 || sub_41A5E0(pThis_2181) == 2 )  // 条件判定
            *((uint8_t *)this + 8576) = 0;  // （表达式续行/复合语句）
          if ( sub_41A5E0(pThis_2181) != 1 && sub_41A5E0(pThis_2181) != 3 )  // 条件判定
            goto LABEL_542;  // 跳转合流点 LABEL_542
          *((uint8_t *)this + 8596) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4) == 1;  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // （表达式续行/复合语句）
          if ( sub_41A5E0(pThis_2181) == 1 )  // 条件判定
          {
            v350 = *this;  // （表达式续行/复合语句）
            fld_e1554 = (int *)*(this + 1554);  // （表达式续行/复合语句）
            if ( *((uint8_t *)this + 8596) != 0 )  // 判定 this[8596] != 0（uint8）
              v352 = fld_e1554[1];  // （表达式续行/复合语句）
            else  // 否则分支
              v352 = *fld_e1554;  // （表达式续行/复合语句）
          }
          else  // 否则分支
          {
            if ( sub_41A5E0(pThis_2181) != 3 )  // 条件判定
              goto LABEL_524;  // 跳转合流点 LABEL_524
            v350 = *this;  // （表达式续行/复合语句）
            fld_e15542 = *(this + 1554);  // 读字段 fld_e15542 = this[1554]
            if ( *((uint8_t *)this + 8596) != 0 )  // 判定 this[8596] != 0（uint8）
              v352 = *(uint32_t *)(fld_e15542 + 12);  // （表达式续行/复合语句）
            else  // 否则分支
              v352 = *(uint32_t *)(fld_e15542 + 8);  // （表达式续行/复合语句）
          }
          (*(void (/*stdcall*/ **)(int))(v350 + 196))(v352);  // （表达式续行/复合语句）
// ── [段 36] 公共尾第三重 case 8 之中段汇合点 LABEL_524（457 态切换链）──
LABEL_524:  // 标签 LABEL_524：合流点
          sub_4926A0(*(this + 30));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
          v354 = sub_4C0DF0(0);
          v355 = *this;  // （表达式续行/复合语句）
          *(this + 2140) = v354;  // （表达式续行/复合语句）
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(v355 + 1000))(this) != 0 )  // 条件判定
          {
            v356 = (*(int (/*thiscall*/ **)(int *))(*this + 1008))(this);  // （表达式续行/复合语句）
            v357 = (*(int (/*thiscall*/ **)(int *))(*this + 1004))(this) - v356;  // （表达式续行/复合语句）
            if ( v357 > *(this + 2140) )  // 条件判定
              *(this + 2140) = v357;  // （表达式续行/复合语句）
          }
          *(this + 2141) = *(this + 2140) + sub_4C0DF0(1);  // （表达式续行/复合语句）
          if ( sub_41A5E0(pThis_2181) == 1 )  // 条件判定
          {
            if ( 250000 / sub_4C0EB0(this) >= 125 )  // 条件判定
              *(this + 2148) = 250000 / sub_4C0EB0(this) + *(this + 2141);  // （表达式续行/复合语句）
            else  // 否则分支
              *(this + 2148) = *(this + 2141) + 125;  // （表达式续行/复合语句）
          }
          else  // 否则分支
          {
            if ( *(this + 2129) == 47 )  // 条件判定
            {
              (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 47);  // （表达式续行/复合语句）
              v358 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
            }
            else  // 否则分支
            {
              v358 = 100;
            }
            *(this + 2148) = *(this + 2141) + 1000 * v358 / sub_4C0EB0(this);  // （表达式续行/复合语句）
          }
          if ( sub_41A5E0(pThis_2181) == 3 || sub_41A5E0((unsigned int)(this + 2136)) == 0 )  // 条件判定
          {
            v498 = 15;
            v497 = 0;
            LOBYTE(v495[0]) = 0;  // （表达式续行/复合语句）
            v359 = *this;  // （表达式续行/复合语句）
            v506 = 50;
            v360 = (*(int (/*thiscall*/ **)(int *))(v359 + 1096))(this);  // （表达式续行/复合语句）
            sub_4C2060(v494, v360);
            v361 = (void **)v495[0];  // （表达式续行/复合语句）
            if ( v498 < 0x10 )  // 条件判定
              v361 = v495;
            (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, v361, -1, 0, 0);  // （表达式续行/复合语句）
            v506 = -1;
            if ( v498 >= 0x10 )  // 条件判定
              j__free(v495[0]);  // （表达式续行/复合语句）
          }
          pThis_8583 = sub_41A5E0((unsigned int)(this + 2136));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
          sub_41A590((unsigned int)(this + 2136), v363, pThis_8583 + 1);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
// ── [段 37] 公共尾第三重 case 8 之汇合点 LABEL_542（缓动/换弹 457 态）──
LABEL_542:  // 标签 LABEL_542：合流点
          if ( sub_41A5E0(pThis_2181) == 4 )  // 条件判定
          {
            v364 = *this;  // （表达式续行/复合语句）
            v365 = sub_4C0EB0(this);  // sub_4C0EB0
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v364 + 888))(this, 0, 0, 1000, v365);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));  // （表达式续行/复合语句）
            sub_4926A0(*(this + 30));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
            nItemCtx_6 = *(this + 2129);  // 读字段 fld_e21296 = this[2129]
            if ( nItemCtx_6 != 5 && nItemCtx_6 != 53 )  // 判定字段 this[21296]（大状态/子状态门）
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                "R_GN_FINAL_SHOT",  // （上一表达式的参数/条件续行）
                -1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
            if ( (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 23) != 0  // 条件判定
              && (*(int (/*thiscall*/ **)(int *))(*this + 1096))(this) == 0 )  // （上一表达式的参数/条件续行）
            {
              pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
              v506 = 51;
              if ( pMem != nullptr )  // 条件判定
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // 条件判定
                  LOBYTE(fld_e91) = (uint8_t)this + 108;  // （表达式续行/复合语句）
                else  // 否则分支
                  fld_e91 = *(this + 91);  // 读字段 fld_e91 = this[91]
                v368 = sub_431920(fld_e91, (char)"Effect/Animation/ReduceRevolverReload1.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
              }
              else  // 否则分支
              {
                v368 = 0;
              }
              v506 = -1;
              pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
              v506 = 52;
              if ( pMem != nullptr )  // 条件判定
                v369 = (int *)sub_44E1F0(v368, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
              else  // 否则分支
                v369 = nullptr;  // v369 = 空指针
              fld_e297 = *(this + 29);  // 读字段 fld_e297 = this[29]
              v506 = -1;
              sub_45FE80(fld_e297, (int)v369, 2, 0, (int)v369, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
              v371 = *v369;  // （表达式续行/复合语句）
              v372 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, int))(v371 + 148))(v369, v372);  // （表达式续行/复合语句）
              v373 = *v369;  // （表达式续行/复合语句）
              v374 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // （表达式续行/复合语句）
              v375 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v374);  // （表达式续行/复合语句）
              v376 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v375);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, int))(v373 + 112))(v369, v376);  // （表达式续行/复合语句）
              pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
              v506 = 53;
              if ( pMem != nullptr )  // 条件判定
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // 条件判定
                  LOBYTE(fld_e912) = (uint8_t)this + 108;  // （表达式续行/复合语句）
                else  // 否则分支
                  fld_e912 = *(this + 91);  // 读字段 fld_e912 = this[91]
                v378 = sub_431920(fld_e912, (char)"Effect/Animation/ReduceRevolverReload2.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
              }
              else  // 否则分支
              {
                v378 = 0;
              }
              v506 = -1;
              pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
              v506 = 54;
              if ( pMem != nullptr )  // 条件判定
                v379 = (int *)sub_44E1F0(v378, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
              else  // 否则分支
                v379 = nullptr;  // v379 = 空指针
              fld_e298 = *(this + 29);  // 读字段 fld_e298 = this[29]
              v506 = -1;
              sub_45FE80(fld_e298, (int)v379, 2, 0, (int)v379, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
              v381 = *v379;  // （表达式续行/复合语句）
              v382 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, int))(v381 + 148))(v379, v382);  // （表达式续行/复合语句）
              v383 = *v379;  // （表达式续行/复合语句）
              v384 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // （表达式续行/复合语句）
              v385 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v384);  // （表达式续行/复合语句）
              v386 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v385);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, int))(v383 + 112))(v379, v386);  // （表达式续行/复合语句）
            }
          }
          nItemCtx_7 = *(this + 2129);  // 读字段 fld_e21297 = this[2129]
          if ( nItemCtx_7 == 5 || nItemCtx_7 == 47 || nItemCtx_7 == 53 )  // 判定字段 this[21297]（大状态/子状态门）
          {
            if ( sub_41A5E0((unsigned int)this + 8577) == 2 )  // 条件判定
            {
              if ( *(this + 2129) == 5 )  // 条件判定
              {
                v408 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);  // （表达式续行/复合语句）
                (*(void (/*thiscall*/ **)(int *, uint32_t, int, int))(*this + 1160))(this, *(this + 2129), 1, v408);  // （表达式续行/复合语句）
                v509 = (double)(int)sub_47EF20(5, -1, -1, 11, v485) * 0.0099999998 + 1.0;  // （表达式续行/复合语句）
                v409 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // （表达式续行/复合语句）
                v410 = (uint64_t)((double)sub_495500(v409) * v509);  // （表达式续行/复合语句）
                (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(this, 0, 0, v410, v410);  // （表达式续行/复合语句）
              }
              pAnimObj_2 = *(this + 30);  // 读字段 fld_e309 = this[30]
              v412 = sub_491C70(pAnimObj_2, 2);  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
              sub_493A60(pAnimObj_2, v412);  // sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
              nItemCtx_8 = *(this + 2129);  // 读字段 fld_e21298 = this[2129]
              switch ( nItemCtx_8 )  // 分派 switch
              {
                case 5:  // case 5 分派：第三重 case 8：★★ 拔枪态（约 460 行）—— +8577/+2136 状态位与枪种分支
                  if ( *((uint8_t *)this + 8608) != 0 )  // 判定 this[8608] != 0（uint8）
                  {
                    v414 = *this;  // （表达式续行/复合语句）
                    v415 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
                    v416 = sub_432E50(v415);  // sub_432E50 —— 关系码对调映射
                    (*(void (/*thiscall*/ **)(int *, int))(v414 + 144))(this, v416);  // （表达式续行/复合语句）
                    if ( *(this + 2153) == 0 )  // 条件判定
                    {
                      pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                      v506 = 55;
                      if ( pMem != nullptr )  // 条件判定
                      {
                        pThis_5A17 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                        v418 = sub_431920(pThis_5A17, (char)"Effect/Animation/TurningShoot.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                      }
                      else  // 否则分支
                      {
                        v418 = 0;  // SEH 展开状态号 = 0
                      }
                      v506 = -1;
                      *(this + 2153) = v418;  // （表达式续行/复合语句）
                    }
                    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                      this,  // （上一表达式的参数/条件续行）
                      1,  // （上一表达式的参数/条件续行）
                      *(this + 2153),  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0);  // （上一表达式的参数/条件续行）
                    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                      this,  // （上一表达式的参数/条件续行）
                      "GN_WESTERN_FIRE",  // （上一表达式的参数/条件续行）
                      -1,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0);  // （上一表达式的参数/条件续行）
                    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                      this,  // （上一表达式的参数/条件续行）
                      "QUICK_TURN",  // （上一表达式的参数/条件续行）
                      -1,  // （上一表达式的参数/条件续行）
                      0,  // （上一表达式的参数/条件续行）
                      0);  // （上一表达式的参数/条件续行）
                  }
                  else  // 否则分支
                  {
                    (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("R_GN_HEAD_SHOT", -1, 0, 0);  // （表达式续行/复合语句）
                  }
                  break;  // 跳出本分支
                case 47:  // case 47 分派：第三重 case 8：★★ 拔枪态（约 460 行）—— +8577/+2136 状态位与枪种分支
                  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                    this,  // （上一表达式的参数/条件续行）
                    "GN_RISING_SHOT",  // （上一表达式的参数/条件续行）
                    -1,  // （上一表达式的参数/条件续行）
                    0,  // （上一表达式的参数/条件续行）
                    0);  // （上一表达式的参数/条件续行）
                  break;  // 跳出本分支
                case 53:  // case 53 分派：第三重 case 8：★★ 拔枪态（约 460 行）—— +8577/+2136 状态位与枪种分支
                  (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("GN_NAPALM", -1, 0, 0);  // （表达式续行/复合语句）
                  break;  // 跳出本分支
                default:  // 未列出的值 → 兜底
                  break;  // 跳出本分支
              }
            }
          }
          else if ( nItemCtx_7 == 11 )  // 判定字段 this[21297]（大状态/子状态门）
          {
            if ( sub_41A5E0((unsigned int)this + 8577) == 0 || sub_41A5E0((unsigned int)this + 8577) == 2 )  // 条件判定
            {
              nItemCtx_10 = *(this + 2129);  // 读字段 fld_e21299 = this[2129]
              v393 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int))(*this + 1160))(this, *(this + 2129), 0, v393);  // （表达式续行/复合语句）
              v394 = sub_47EF20(nItemCtx_10, -1, -1, 11, v485);  // sub_47EF20 —— 读攻击数据表
              v395 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // （表达式续行/复合语句）
              v396 = sub_495500(v395);  // sub_495500 —— 槽对乘积读取（+844/+858）
              (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                v396 + v394,  // （上一表达式的参数/条件续行）
                v396 + v394);  // （上一表达式的参数/条件续行）
              if ( sub_41A5E0((unsigned int)this + 8577) == 0 )  // 条件判定
                (*(void (/*stdcall*/ **)(const char *, int, uint32_t, uint32_t))(*this + 212))("GN_FASTESTGUN", -1, 0, 0);  // （表达式续行/复合语句）
            }
            // ── [段 38] 第三重 case 7 之中段：+8577 与 +2136 双状态位联合判定（连发/换弹节流）──
            else if ( sub_41A5E0((unsigned int)this + 8577) == 1 && sub_41A5E0((unsigned int)(this + 2136)) == 1  // 否则条件分支
                   || sub_41A5E0((unsigned int)this + 8577) == 3 )  // （上一表达式的参数/条件续行）
            {
              if ( *((uint8_t *)this + 8596) != 0 )  // 判定 this[8596] != 0（uint8）
              {
                if ( *(this + 2151) == 0 )  // 条件判定
                {
                  pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                  v506 = 56;
                  if ( pMem != nullptr )  // 条件判定
                  {
                    pThis_5A18 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                    // ── [段 39] 公共尾第三重 case 8 之快速射击：FastShootDown/FastShootUp.ani 两件 ──
                    v389 = sub_431920(pThis_5A18, (char)"Effect/Animation/FastShootDown.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                  }
                  else  // 否则分支
                  {
                    v389 = 0;
                  }
                  v506 = -1;
                  *(this + 2151) = v389;  // （表达式续行/复合语句）
                }
                fld_e2151 = *(this + 2151);  // 读字段 fld_e2151 = this[2151]
              }
              else  // 否则分支
              {
                if ( *(this + 2150) == 0 )  // 条件判定
                {
                  pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                  v506 = 57;
                  if ( pMem != nullptr )  // 条件判定
                  {
                    pThis_5A19 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                    v392 = sub_431920(pThis_5A19, (char)"Effect/Animation/FastShootUp.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                  }
                  else  // 否则分支
                  {
                    v392 = 0;
                  }
                  v506 = -1;
                  *(this + 2150) = v392;  // （表达式续行/复合语句）
                }
                fld_e2151 = *(this + 2150);  // 读字段 fld_e2151 = this[2150]
              }
              if ( sub_41A5E0((unsigned int)this + 8577) == 1 )  // 条件判定
                (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  1,  // （上一表达式的参数/条件续行）
                  fld_e2151,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
              else  // 否则分支
                (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  1,  // （上一表达式的参数/条件续行）
                  fld_e2151,  // （上一表达式的参数/条件续行）
                  32,  // （上一表达式的参数/条件续行）
                  8,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
            }
          }
          else if ( nItemCtx_7 == 26 && sub_41A5E0((unsigned int)this + 8577) == 0 )  // 判定字段 this[21297]（大状态/子状态门）
          {
            nItemCtx_11 = *(this + 2129);  // 读字段 fld_e212910 = this[2129]
            v397 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, uint32_t, int, int))(*this + 1160))(this, *(this + 2129), 1, v397);  // （表达式续行/复合语句）
            v508 = (double)(int)sub_47EF20(nItemCtx_11, -1, -1, 11, v485) * 0.0099999998 + 1.0;  // （表达式续行/复合语句）
            v398 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // （表达式续行/复合语句）
            v399 = (uint64_t)((double)sub_495500(v398) * v508);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(this, 0, 0, v399, v399);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 144))(this, *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8));  // （表达式续行/复合语句）
            pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
            v506 = 58;
            if ( pMem != nullptr )  // 条件判定
            {
              pThis_5A20 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
              // ── [段 40] 公共尾第三重 case 8 之反击射击：CounterShoot.ani 建件 ──
              v401 = sub_431920(pThis_5A20, (char)"Effect/Animation/CounterShoot.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
            }
            else  // 否则分支
            {
              v401 = 0;
            }
            v506 = -1;
            pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
            // ── [段 41] 第三重 case 8 之收尾段：建件 + sub_45FE80 挂接 + vt+112 落坐标链 ──
            v506 = 59;
            if ( pMem != nullptr )  // 条件判定
              v402 = (int *)sub_44E1F0(v401, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
            else  // 否则分支
              v402 = nullptr;  // v402 = 空指针
            fld_e299 = *(this + 29);  // 读字段 fld_e299 = this[29]
            v506 = -1;
            sub_45FE80(fld_e299, (int)v402, 2, 0, (int)v402, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
            v404 = *v402;  // （表达式续行/复合语句）
            v484 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *))(v404 + 148))(v402);  // （表达式续行/复合语句）
            v405 = *v402;  // （表达式续行/复合语句）
            v477 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + 95;  // （表达式续行/复合语句）
            v406 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // （表达式续行/复合语句）
            v407 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v406);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, int))(v405 + 112))(v402, v407);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *, int, int *, int))(*this + 1160))(this, 26, this, -1);  // （表达式续行/复合语句）
            sub_47DCD0(v477, v484);  // sub_47DCD0 —— 震动/资源档位设置
          }
          nItemCtx_9 = *(this + 2129);  // 读字段 fld_e212911 = this[2129]
          if ( nItemCtx_9 != -1 && nItemCtx_9 != 11 )  // 判定字段 this[212911]（大状态/子状态门）
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);  // （表达式续行/复合语句）
          return;  // 返回（本帧结束）
        // ── [段 42] 第三重 case 10：★ 副武器状态机（this[1953]==0 时按 this[1954] 分派）──
        //   43 号特例（3187 起）；goto LABEL_482 走公共尾
        case 10:  // case 10 分派：第三重 case 8 之收尾段：建件 + sub_45FE80 挂接 + vt+112 落坐标链
          if ( *(this + 1953) == 0 )  // 条件判定
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *(this + 1954));  // （表达式续行/复合语句）
            fld_e1954 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 1954));  // （表达式续行/复合语句）
            fld_e19542 = *(this + 1954);  // 读字段 fld_e19542 = this[1954]
            if ( fld_e19542 == 43 )  // 判定字段 this[19542] == 43
            {
              fld_e1952 = *(this + 1952);  // 读字段 fld_e1952 = this[1952]
              if ( fld_e1952 != 0 )  // 判定字段 this[1952] != 0
              {
                if ( fld_e1952 == 1 )  // 判定字段 this[1952] == 1
                {
                  v451 = sub_47EF20(0, fld_e1954, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
                  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 944))(this, 1, v451);  // （表达式续行/复合语句）
                  *((uint8_t *)this + 9500) = 1;  // （表达式续行/复合语句）
                  *((uint8_t *)this + 9501) = 0;  // （表达式续行/复合语句）
                  *((uint8_t *)this + 9502) = 0;  // （表达式续行/复合语句）
                  sub_698F90((int)(this + 2372), v451, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
                }
              }
              else  // 否则分支
              {
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  "GN_CAMOUFLAGE",  // （上一表达式的参数/条件续行）
                  -1,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
              }
            }
            else if ( fld_e19542 == 45 )  // 判定字段 this[19542]（大状态/子状态门）
            {
              fld_e19522 = *(this + 1952);  // 读字段 fld_e19522 = this[1952]
              if ( fld_e19522 != 0 )  // 判定字段 this[19522] != 0
              {
                if ( fld_e19522 == 1 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 判定字段 this[19522]（大状态/子状态门）
                {
                  v453 = *this;  // （表达式续行/复合语句）
                  v454 = sub_47E9D0(1);  // sub_47E9D0 —— 收招/结束例程
                  v455 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 1140))(  // （表达式续行/复合语句）
                           this,  // （上一表达式的参数/条件续行）
                           45,  // （上一表达式的参数/条件续行）
                           0,  // （上一表达式的参数/条件续行）
                           0,  // （上一表达式的参数/条件续行）
                           0,  // （上一表达式的参数/条件续行）
                           0,  // （上一表达式的参数/条件续行）
                           v454,  // （上一表达式的参数/条件续行）
                           4,  // （上一表达式的参数/条件续行）
                           0,  // （上一表达式的参数/条件续行）
                           0,  // （上一表达式的参数/条件续行）
                           0);  // （上一表达式的参数/条件续行）
                  (*(void (/*thiscall*/ **)(int *, int, int))(v453 + 580))(this, 22206, v455);  // （表达式续行/复合语句）
                }
              }
              else  // 否则分支
              {
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  "GN_URANIUM_BOMBER",  // （上一表达式的参数/条件续行）
                  -1,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
              }
            }
            else if ( fld_e19542 == 50 && *(this + 1952) == 1 )  // 判定字段 this[19542]（大状态/子状态门）
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 条件判定
                (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // （表达式续行/复合语句）
                  this,  // （上一表达式的参数/条件续行）
                  48015,  // （上一表达式的参数/条件续行）
                  50,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  4,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0,  // （上一表达式的参数/条件续行）
                  0);  // （上一表达式的参数/条件续行）
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t))(*this + 212))(this, "BOMB_AREA", -1, 0);  // （表达式续行/复合语句）
              v456 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 1160))(this, 50, 0, v456);  // （表达式续行/复合语句）
              v457 = (double)(int)sub_47EF20(50, -1, -1, 11, 0);  // （表达式续行/复合语句）
              v458 = 0;
              do
              {
                v510 = v458 + 1;  // （表达式续行/复合语句）
                sprintf(Buffer, "Effect/Animation/RobotsExplosion%d.ani", v458 + 1);  // （表达式续行/复合语句）
                pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
                v506 = 62;
                if ( pMem != nullptr )  // 条件判定
                {
                  pThis_5A21 = unknown_libname_2(this + 90);  // （表达式续行/复合语句）
                  v460 = sub_431920(pThis_5A21, (char)Buffer, 1);  // sub_431920 —— 动画件构造（文件名版）
                }
                else  // 否则分支
                {
                  v460 = 0;
                }
                v506 = -1;
                v507 = v457 * 0.0018867925;  // （表达式续行/复合语句）
                sub_4922F0(v507);  // sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
                pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
                v506 = 63;
                if ( pMem != nullptr )  // 条件判定
                  v461 = (int *)sub_44E1F0(v460, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
                else  // 否则分支
                  v461 = nullptr;  // v461 = 空指针
                v462 = *v461;  // （表达式续行/复合语句）
                v506 = -1;
                *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v462 + 36))(v461) + 8) = 2;  // （表达式续行/复合语句）
                sub_45FE80(*(this + 29), -1, 2, 0, (int)v461, 0, 0);  // sub_45FE80 —— 实体注册到演播层
                v463 = *v461;  // （表达式续行/复合语句）
                v464 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
                (*(void (/*thiscall*/ **)(int *, int))(v463 + 148))(v461, v464);  // （表达式续行/复合语句）
                v465 = *v461;  // （表达式续行/复合语句）
                v466 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // （表达式续行/复合语句）
                v467 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v466);  // （表达式续行/复合语句）
                v468 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v467);  // （表达式续行/复合语句）
                (*(void (/*thiscall*/ **)(int *, int))(v465 + 112))(v461, v468);  // （表达式续行/复合语句）
                v458 = v510;
              }
              while ( v510 < 3 );  // 循环
            }
          }
          return;  // 返回（本帧结束）
        // ── [段 43] 第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表 ──
        //   vt+196(this[1812]) + sub_491C70/+493A60/+4939E0(+30 对象) 三连帧同步后 return
        case 12:  // case 12 分派：第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表
          fld_e2163 = *(this + 2163);  // 读字段 fld_e2163 = this[2163]
          if ( fld_e2163 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2163 + 80))() != 0 )  // 判定字段 this[2163]（大状态/子状态门）
          {
            v474 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 37, -1);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);  // （表达式续行/复合语句）
            *(this + 114) = sub_47EF20(37, 1, v474, -1, 11);  // （表达式续行/复合语句）
          }
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1812));  // （表达式续行/复合语句）
          pAnimObj_5 = *(this + 30);  // 读字段 fld_e3010 = this[30]
          fld_e2160 = sub_491C70(pAnimObj_5, *(this + 2160));  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
          sub_493A60(pAnimObj_5, fld_e2160);  // sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
          sub_4939E0(*(this + 30), 1);  // sub_4939E0 —— 播放/暂停级联（递归子链 +204）
          return;  // 返回（本帧结束）
        // ── [段 44] 第三重 case 14：★ 技能号语音小表 —— switch(this[1991])（175/176/1/…）──
        case 14:  // case 14 分派：第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表
          fld_e1991 = *(this + 1991);  // 读字段 fld_e1991 = this[1991]
          switch ( fld_e1991 )  // 分派 switch
          {
            case 175:  // case 175 分派：第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                "GN_LEAP_BUFF",  // （上一表达式的参数/条件续行）
                -1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              break;  // 跳出本分支
            case 176:  // case 176 分派：第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                "GN_ANCIENT_MEMORY",  // （上一表达式的参数/条件续行）
                -1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              break;  // 跳出本分支
            case 1:  // case 1 分派：第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                "GN_FLAMESHOT",  // （上一表达式的参数/条件续行）
                -1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              break;  // 跳出本分支
            case 2:  // case 2 分派：第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                "GN_ICESHOT",  // （上一表达式的参数/条件续行）
                -1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              break;  // 跳出本分支
            case 30:  // case 30 分派：第三重 case 12：★ 帧率与动画同步 —— +2163 对象 vt+80 判定后 vt+1140(37) 读表
              (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // （表达式续行/复合语句）
                this,  // （上一表达式的参数/条件续行）
                "GN_SILVERSHOT",  // （上一表达式的参数/条件续行）
                -1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              break;  // 跳出本分支
            default:  // 未列出的值 → 兜底
              break;  // 跳出本分支
          }
          return;  // 返回（本帧结束）
        default:  // 未列出的值 → 兜底
          return;  // 返回（本帧结束）
      }
    // ── [段 45] 第二重 case 23：★ 移动射击（GN_MOVESHOT）—— fld_e1639==23 与非 23 两支 ──
    //   23 支：sub_699000(this+1640) + sub_4C0DF0(0/1) 双时长 + sub_41A5E0(this+2083) 合成 +2140/+2141 时刻；
    //   非 23 支：vt+1160(15) + vt+672(3)+sub_4954C0 帧长 + sub_47EF20(1)/(2)/(3) 三读表写 +2361/+2362；
    //   vt+876 双段（0:143,119,1 / 1:114,95,1）+ vt+896(4,4) + vt+888 帧长；
    //   一长串槽位初始化（+2129=15/+2359=4/+2360=0/+2140=-1/+2141=0/+2362=-1 等）后播 GN_MOVESHOT；
    //   末段 sub_4C2020(Block, vt+1096()) 组串 + vt+212 播报；goto LABEL_482
    case 23:  // case 23 分派：第二重 case 23：★ 移动射击（GN_MOVESHOT）—— fld_e1639==23 与非 23 两支
      if ( nBigState == 23 )  // 判定字段 this[1639] == 23
      {
        pThis_6684 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
        *(this + 2140) = sub_4C0DF0(0) + pThis_6684;  // （表达式续行/复合语句）
        pThis_823 = sub_41A5E0((unsigned int)(this + 2083));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
        *(this + 2141) = pThis_823 + *(this + 2140) + *(this + 2361) + sub_4C0DF0(1);  // （表达式续行/复合语句）
        LOBYTE(nArg4) = 0;  // （表达式续行/复合语句）
        LOBYTE(nArg5) = 0;  // （表达式续行/复合语句）
      }
      else  // 否则分支
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 15);  // （表达式续行/复合语句）
        *(float *)&pThis_88C3 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 15));  // （表达式续行/复合语句）
        v304 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // （表达式续行/复合语句）
        v305 = sub_4954C0(v304);  // sub_4954C0 —— 槽对乘积读取（+816/+830）
        v306 = sub_47EF20(1, pThis_88C3, -1, -1, 11) + v305;  // （表达式续行/复合语句）
        *(this + 2361) = sub_47EF20(2, pThis_88C3, -1, -1, 11);  // （表达式续行/复合语句）
        v307 = (void *)sub_47EF20(3, pThis_88C3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
        v308 = *this;  // （表达式续行/复合语句）
        pMem = v307;
        v309 = (double)(int)v307;  // （表达式续行/复合语句）
        fld_e15543 = *(this + 1554);  // 读字段 fld_e15543 = this[1554]
        *((float *)this + 2363) = v309 * 0.000099999997;  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(v308 + 196))(this, *(uint32_t *)(fld_e15543 + 92));  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 0, 143, 119, 1, 0, 0);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 1, 114, 95, 1, 0, 0);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, v306, v306);  // （表达式续行/复合语句）
        v311 = *this;  // （表达式续行/复合语句）
        *(this + 2129) = 15;  // （表达式续行/复合语句）
        *(this + 2359) = 4;  // （表达式续行/复合语句）
        *(this + 2360) = 0;  // （表达式续行/复合语句）
        *(this + 2140) = -1;  // （表达式续行/复合语句）
        *(this + 2141) = 0;  // （表达式续行/复合语句）
        *(this + 2364) = 0;  // （表达式续行/复合语句）
        *(this + 2365) = 0;  // （表达式续行/复合语句）
        *(this + 2362) = -1;  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v311 + 212))(this, "GN_MOVESHOT", -1, 0, 0);  // （表达式续行/复合语句）
        v504 = 15;
        v503 = 0;
        LOBYTE(Block[0]) = 0;  // （表达式续行/复合语句）
        v312 = *this;  // （表达式续行/复合语句）
        v506 = 49;
        v313 = (*(int (/*thiscall*/ **)(int *))(v312 + 1096))(this);  // （表达式续行/复合语句）
        if ( v313 >= 0 )  // 条件判定
        {
          if ( v313 <= 3 )  // 条件判定
          {
            sub_406D60("GUN_DRAW3");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          }
          else if ( v313 == 4 )  // 否则条件分支
          {
            sub_406D60("BOWGUN_DRAW3");  // sub_406D60 —— std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          }
        }
        Block5 = (void **)Block[0];  // （表达式续行/复合语句）
        if ( v504 < 0x10 )  // 条件判定
          Block5 = Block;
        (*(void (/*thiscall*/ **)(int *, void **, int, uint32_t, uint32_t))(*this + 212))(this, Block5, -1, 0, 0);  // （表达式续行/复合语句）
        v506 = -1;
        sub_501490(v499);  // std::string 析构（本条目串：数据@+4/长度@+20/容量@+24）：容量
      }
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 46] 第二重 case 25：★ 副武器状态 27/28/29 三支取参（sub_4B1C40/sub_495540 帧长链）──
    //   fld_e15544 与 fld_e304 交替写；goto LABEL_482
    case 25:  // case 25 分派：第二重 case 23：★ 移动射击（GN_MOVESHOT）—— fld_e1639==23 与非 23 两支
      v317 = **(uint32_t **)(pArg3 + 4);  // （表达式续行/复合语句）
      if ( v317 == 27 )  // 条件判定
      {
        *(this + 2366) = 60002;  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ROBOT_SET_01", -1, 0, 0);  // （表达式续行/复合语句）
      }
      else if ( **(uint32_t **)(pArg3 + 4) == 28 )  // 否则条件分支
      {
        v318 = *this;  // （表达式续行/复合语句）
        *(this + 2366) = 60003;  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v318 + 212))(this, "ROBOT_SET_02", -1, 0, 0);  // （表达式续行/复合语句）
      }
      else if ( **(uint32_t **)(pArg3 + 4) == 29 )  // 否则条件分支
      {
        *(this + 2366) = 60004;  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ROBOT_SET_03", -1, 0, 0);  // （表达式续行/复合语句）
      }
      *(this + 2368) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);  // （表达式续行/复合语句）
      *(this + 2369) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);  // （表达式续行/复合语句）
      v319 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 1160))(this, v317, 0, v319);  // （表达式续行/复合语句）
      *(this + 2367) = sub_47EF20(v317, -1, -1, 11, v485);  // （表达式续行/复合语句）
      fld_e15544 = *(uint32_t *)(*(this + 1554) + 128);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *))(*this + 196))(this);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
      v320 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, v317);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 1160))(this, v317, v320);  // （表达式续行/复合语句）
      pAnimObj_6 = COERCE_FLOAT(sub_4B1C40(fld_e15544));  // （表达式续行/复合语句）
      pMem = *(void **)(*(this + 30) + 36);  // （表达式续行/复合语句）
      v321 = *this;  // （表达式续行/复合语句）
      v485 = 3;
      *(float *)&pThis_88C3 = (double)(int)pMem / (double)SLODWORD(pAnimObj_6);  // （表达式续行/复合语句）
      v322 = (*(int (/*thiscall*/ **)(int *))(v321 + 672))(this);  // （表达式续行/复合语句）
      pAnimObj_6 = COERCE_FLOAT(sub_495540(v322));  // （表达式续行/复合语句）
      (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, int, uint32_t))(v321 + 888))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        (uint64_t)((double)SLODWORD(pAnimObj_6) * *(float *)&pThis_88C3) >> 32,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        1000,  // （上一表达式的参数/条件续行）
        (uint64_t)((double)SLODWORD(pAnimObj_6) * *(float *)&pThis_88C3));  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, void *, int))(*this + 992))(this, pMem, 1);  // （表达式续行/复合语句）
      *(this + 2371) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12);  // （表达式续行/复合语句）
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 47] 第二重 case 26：★ 激光炮/加特林（this[2129] 40 / 39 两支）──
    //   先 sub_4926A0 与 vt+196(this[1554]+64) 双复位；40 支 sub_4C4890(this,4,16) + vt+876 位移；
    //   39 支 vt+1160(39) + sub_47DD30 + sub_4C4890(this,2,16) 后建两枚动画（+2345/+2346 惰性）；
    //   （3630）vt+152+sub_432E50 朝向 + dword_8F8270 表 + vt+924(this,2) 取件；LABEL_232 为收束点
    case 26:  // case 26 分派：第二重 case 23：★ 移动射击（GN_MOVESHOT）—— fld_e1639==23 与非 23 两支
      *(this + 2129) = **(uint32_t **)(pArg3 + 4);  // （表达式续行/复合语句）
      fld_e15545 = *(this + 1554);  // 读字段 fld_e15545 = this[1554]
      *(this + 2242) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);  // （表达式续行/复合语句）
      v53 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);  // （表达式续行/复合语句）
      sub_4926A0(*(uint32_t *)(fld_e15545 + 64));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 64));  // （表达式续行/复合语句）
      nItemCtx_3 = *(this + 2129);  // 读字段 fld_e212912 = this[2129]
      if ( nItemCtx_3 == 40 )  // 判定字段 this[212912] == 40
      {
        sub_4C4890(this, 4, 16);
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, int, int))(*this + 876))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          250,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          -500,  // （上一表达式的参数/条件续行）
          1);  // （上一表达式的参数/条件续行）
      }
      else if ( nItemCtx_3 == 39 )  // 判定字段 this[212912]（大状态/子状态门）
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 39);  // （表达式续行/复合语句）
        sub_47DD30(this);  // 复位变体：对 nArg1 对象 vt+80 资源的 +132 调 sub_424120(
        // ── [段 48] 第二重 case 26 之 39 号支：vt+1160(39) + sub_47DD30 + sub_4C4890(this,2,16) ──
        sub_4C4890(this, 2, 16);
        if ( *(this + 2345) == 0 )  // 条件判定
        {
          pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
          v506 = 4;
          if ( pMem != nullptr )  // 条件判定
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // 条件判定
              pThis_6C = sub_431920(  // （表达式续行/复合语句）
                      (uint8_t)this + 108,  // （上一表达式的参数/条件续行）
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeEffect.ani",  // （上一表达式的参数/条件续行）
                      1);  // （上一表达式的参数/条件续行）
            else  // 否则分支
              pThis_6C = sub_431920(  // （表达式续行/复合语句）
                      *(this + 91),  // （上一表达式的参数/条件续行）
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeEffect.ani",  // （上一表达式的参数/条件续行）
                      1);  // （上一表达式的参数/条件续行）
          }
          else  // 否则分支
          {
            pThis_6C = 0;
          }
          v506 = -1;
          *(this + 2345) = pThis_6C;  // （表达式续行/复合语句）
        }
        // ── [段 49] 第二重 case 26 之第二枚惰性件（+2346，与 +2345 成对）──
        if ( *(this + 2346) == 0 )  // 条件判定
        {
          pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
          v506 = 5;
          if ( pMem != nullptr )  // 条件判定
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // 条件判定
              pThis_6C2 = sub_431920(  // （表达式续行/复合语句）
                      (uint8_t)this + 108,  // （上一表达式的参数/条件续行）
                      (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeSpark.ani",  // （上一表达式的参数/条件续行）
                      1);  // （上一表达式的参数/条件续行）
            else  // 否则分支
              pThis_6C2 = sub_431920(*(this + 91), (char)"Effect/Animation/SubWeapon/LaserRifleEffect/FireChargeSpark.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
          }
          else  // 否则分支
          {
            pThis_6C2 = 0;
          }
          v506 = -1;
          *(this + 2346) = pThis_6C2;  // （表达式续行/复合语句）
        }
        sub_4926A0(*(this + 2345));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
        sub_4926A0(*(this + 2346));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          *(this + 2345),  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          1,  // （上一表达式的参数/条件续行）
          *(this + 2346),  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        fld_e2356 = sub_423A80(100, 400, v53, *(this + 2356));  // sub_423A80 —— 同上 int 版（FTOL 截断）
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, int, int))(*this + 876))(  // （表达式续行/复合语句）
          this,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          fld_e2356,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          -500,  // （上一表达式的参数/条件续行）
          1);  // （上一表达式的参数/条件续行）
        if ( fld_e2356 > 150 )  // 判定字段 this[2356]（大状态/子状态门）
        {
          pMem = (void *)sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
          v506 = 6;
          if ( pMem != nullptr )  // 条件判定
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // 条件判定
              LOBYTE(fld_e913) = (uint8_t)this + 108;  // （表达式续行/复合语句）
            else  // 否则分支
              fld_e913 = *(this + 91);  // 读字段 fld_e913 = this[91]
            // ── [段 50] 第二重 case 26 之 39 号支末段：TurningShoot.ani 建件（+2129==39 与 40 双态）──
            v59 = sub_431920(fld_e913, (char)"Effect/Animation/TurningShoot.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
          }
          else  // 否则分支
          {
            v59 = 0;
          }
          v506 = -1;
          pMem = (void *)sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
          v506 = 7;
          if ( pMem != nullptr )  // 条件判定
            v60 = (int *)sub_44E1F0(v59, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
          else  // 否则分支
            v60 = nullptr;  // v60 = 空指针
          fld_e2910 = *(this + 29);  // 读字段 fld_e2910 = this[29]
          v506 = -1;
          sub_45FE80(fld_e2910, (int)v60, 2, 0, (int)v60, (int)this, 0);  // sub_45FE80 —— 实体注册到演播层
          v62 = *v60;  // （表达式续行/复合语句）
          v63 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // （表达式续行/复合语句）
          v64 = sub_432E50(v63);  // sub_432E50 —— 关系码对调映射
          (*(void (/*thiscall*/ **)(int *, int))(v62 + 148))(v60, v64);  // （表达式续行/复合语句）
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 )  // 条件判定
            v65 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + 130;  // （表达式续行/复合语句）
          else  // 否则分支
            v65 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - 130;  // （表达式续行/复合语句）
          v66 = *v60;  // （表达式续行/复合语句）
          pThis_88C3 = v65;
          v67 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // （表达式续行/复合语句）
          v68 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v67);  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *, int, int))(v66 + 112))(v60, pThis_88C3, v68);  // （表达式续行/复合语句）
        }
      }
      v69 = *this;  // （表达式续行/复合语句）
      v70 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);  // （表达式续行/复合语句）
      v71 = sub_432E50(v70);  // sub_432E50 —— 关系码对调映射
      (*(void (/*thiscall*/ **)(int *, int))(v69 + 896))(this, v71);  // （表达式续行/复合语句）
      pObj3 = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];  // （表达式续行/复合语句）
      v73 = *(uint32_t *)pObj3;  // （表达式续行/复合语句）
      v74 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);  // （表达式续行/复合语句）
      v75 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v74);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int, int))(v73 + 40))(pObj3, v75);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 12))(pObj3, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)pObj3 + 92))(pObj3, &v501);  // （表达式续行/复合语句）
      v506 = 8;
      sub_4600B0((void *)*(this + 29), 2, 0, (int)&v501);  // sub_4600B0 —— 演播层注册(槽号)
LABEL_232:  // 标签 LABEL_232：合流点
      v506 = -1;
      sub_5E5260((void **)&v501);  // sub_5E5260 —— 清理临时缓冲
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 51] 第二重 case 27：单支处理（goto LABEL_482）──
    case 27:  // case 27 分派：第二重 case 26 之 39 号支：vt+1160(39) + sub_47DD30 + sub_4C4890(this,2,16)
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 132));  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // （表达式续行/复合语句）
        this,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0,  // （上一表达式的参数/条件续行）
        0);  // （上一表达式的参数/条件续行）
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // （表达式续行/复合语句）
      v323 = *this;  // （表达式续行/复合语句）
      *(this + 2129) = 48;  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, int))(v323 + 1160))(this, 48);  // （表达式续行/复合语句）
      v324 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // （表达式续行/复合语句）
      v325 = sub_495500(v324);  // sub_495500 —— 槽对乘积读取（+844/+858）
      *(this + 2140) = 1000 * sub_47E9D0(0) / v325;  // （表达式续行/复合语句）
      v326 = 1000 * sub_47E9D0(1);  // （表达式续行/复合语句）
      *(this + 2148) = *(this + 2140) + v326 / sub_4C0EB0(this);  // （表达式续行/复合语句）
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "GN_CROSS_SHOT", -1, 0, 0);  // （表达式续行/复合语句）
      goto LABEL_482;  // 跳转合流点 LABEL_482
    // ── [段 52] 第二重 default：直接 goto LABEL_482 走公共尾（未知动作号静默）──
    default:  // 未列出的值 → 兜底
      goto LABEL_482;  // 跳转合流点 LABEL_482
  }
}

