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
void /*thiscall*/ sub_5E1000(uint32_t **this, int nArg2, int pArg3, int pArg4, int nArg5)
{
  int nArg22; // edi
  int nSubStateB; // eax  | +0x1E88 → ★ 子状态 B（0x5DE690: +7816==11 判据）（CNMage；va=005DE690）
  int fld_e2109; // eax
  uint32_t *pThis_842; // edi
  int i; // ebx
  uint32_t *pThis_845; // edi
  int j; // ebx
  uint32_t *pThis_848; // edi
  int k; // ebx
  int v15; // edx
  int nPhaseGroupIdx; // eax  | +0x2178 → ★ 相位组索引（CNMage；va=005DE690）
  int v17; // eax
  int pArg32; // ecx
  int v19; // edi
  int v20; // eax
  int fld_16C; // ecx  | +0x016C → ★ 场景动画池指针（CNMage；va=005DE690）
  int v22; // edi
  int *v23; // edi
  int fld_e29; // ecx  | +0x0074 → 0x5DE690 读取槽（fld_74）（CNMage；va=005DE690）
  int v25; // ebx
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int fld_e912; // ecx  | +0x016C → ★ 场景动画池指针（CNMage；va=005DE690）
  int v30; // edi
  int *v31; // edi
  int fld_e292; // ecx  | +0x0074 → 0x5DE690 读取槽（fld_74）（CNMage；va=005DE690）
  int v33; // ebx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int pArg33; // edi
  int fld_e1542; // eax
  int v39; // edx
  int v40; // edx
  char *v41; // edi
  int fld_e2100; // ebx
  int v43; // eax
  int v44; // eax
  int v45; // edx
  int v46; // eax
  int v47; // eax
  int v48; // edx
  int v49; // eax
  int v50; // edi
  uint32_t *pThis_6C; // eax
  uint32_t *pThis_6C2; // eax
  int *nWeaponItemId; // ecx
  int v54; // edx
  int fld_e992; // eax
  int v56; // edi
  int v57; // eax
  float *v58; // edi
  float *m; // ebx
  double v60; // st7
  int v61; // edx
  char *v62; // edi
  int fld_e2124; // ebx
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
  int nPhaseRefA; // eax  | +0x2140 → 0x5DE690: sub_432E50(*(this+8512)) 取值（CNMage；va=005DE690）
  void *v77; // eax
  uint32_t *pThis_6C3; // eax
  int v79; // edx
  char *v80; // edi
  int nPhaseValA; // ebx  | +0x2144 → 0x5DE690 相位值 A（CNMage；va=005DE690）
  int nPhaseValA_; // eax  | +0x2144 → 0x5DE690 相位值 A（CNMage；va=005DE690）
  int v83; // eax
  int v84; // eax
  int v85; // edx
  int v86; // eax
  uint32_t *v87; // eax
  int v88; // edx
  int v89; // edx
  uint32_t *pThis_6C4; // eax
  uint32_t *v91; // eax
  char *fld_e2134; // edi
  int fld_e21342; // eax
  bool fld_e21343; // zf
  int nPhaseValB; // ecx  | +0x2154 → 0x5DE690 相位值 B（fld_2154）（CNMage；va=005DE690）
  int v96; // eax
  int v97; // edx
  int v98; // eax
  int v99; // ebx
  int v100; // eax
  int v101; // edx
  int v102; // ebx
  int v103; // eax
  int v104; // eax
  int fld_e993; // ebx
  int v106; // eax
  int v107; // edx
  int v108; // eax
  int v109; // eax
  int nPhaseValB_; // eax  | +0x2154 → 0x5DE690 相位值 B（fld_2154）（CNMage；va=005DE690）
  uint32_t *pThis_6C5; // eax
  uint32_t *pThis_838; // edi
  int n; // ebx
  int v114; // eax
  int nFxCtx; // ecx  | +0x2160 → 0x5DE690 经 sub_4939E0(*(this+8544), 1) 消费（CNMage；va=005DE690）
  int v116; // eax
  int pArg34; // ebx
  int v118; // eax
  int v119; // eax
  void *v120; // eax
  int v121; // edx
  void *v122; // eax
  int fld_e1723; // eax
  int v124; // eax
  int v125; // eax
  void *v126; // eax
  int v127; // eax
  int nVariantSel; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  int v129; // eax
  int pThis_9; // eax
  int v131; // eax
  int fld_e2058; // ecx
  int fld_e21442; // eax  | +0x2180 → ★ 渐变 alpha（CNMage；va=005DE690）
  bool v134; // al
  int nFadeAlpha; // edi  | +0x2180 → ★ 渐变 alpha（CNMage；va=005DE690）
  uint32_t *pThis_6C6; // eax
  uint32_t *pSkillCtx; // eax
  uint32_t *pThis_8382; // edi
  int ii; // ebx
  int nSubStateB_; // edx  | +0x1E88 → ★ 子状态 B（0x5DE690: +7816==11 判据）（CNMage；va=005DE690）
  int nVariantSel_6; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  int nVariantSel_7; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  uint32_t *v143; // edi
  int v144; // eax
  int v145; // eax
  int v146; // edx
  int v147; // eax
  int v148; // ebx
  int v149; // eax
  int v150; // eax
  int v151; // ecx
  int nVariantSel_8; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  char pThis_2188; // al
  int v154; // ebx
  int v155; // edi
  int v156; // eax
  int v157; // edx
  int nVariantSel_9; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  uint32_t *pThis_6C9; // eax
  int v160; // eax
  int v161; // ebx
  int v162; // eax
  int v163; // eax
  int v164; // eax
  int nVariantSel_10; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  uint32_t *pThis_6C10; // eax
  int fld_e19545; // eax
  int v168; // edx
  int fld_e19546; // ebx  | +0x1E88 → ★ 子状态 B（0x5DE690: +7816==11 判据）（CNMage；va=005DE690）
  int v170; // edi
  int v171; // eax
  int v172; // eax
  int nVariantSel_11; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  uint32_t *pThis_6C11; // eax
  uint32_t *pThis_6C12; // eax
  int v176; // edi
  int v177; // eax
  int nVariantSel_12; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  int v179; // edi
  int v180; // eax
  int v181; // eax
  int nVariantSel_13; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
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
  int nVariantSel_; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  int pAnimObj; // eax  | +0x0078 → 动画对象指针（0x499020 帧时刻同步宿主；0x5DE690 经此 +148 取剩余硬直）【基类字段】（CNMage；va=00499020）
  uint32_t *pThis_6C13; // eax
  int fld_e2116; // ebx
  int v198; // edi
  int fld_e914; // edx  | +0x016C → ★ 场景动画池指针（CNMage；va=005DE690）
  int v200; // edi
  int *v201; // edi
  int fld_e293; // ecx  | +0x0074 → 0x5DE690 读取槽（fld_74）（CNMage；va=005DE690）
  int v203; // ebx
  int v204; // ebx
  int v205; // eax
  int v206; // eax
  int v207; // eax
  int v208; // eax
  double v209; // st7
  int nArg52; // eax
  int fld_e915; // ecx  | +0x016C → ★ 场景动画池指针（CNMage；va=005DE690）
  int v212; // edi
  int *v213; // edi
  int v214; // edx
  int v215; // ebx
  int v216; // eax
  int v217; // ebx
  int v218; // eax
  int v219; // eax
  int v220; // eax
  int nVariantSel_2; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  uint32_t *pThis_8452; // edi
  int pThis_6C14; // eax
  uint32_t *pThis_6C15; // eax
  uint32_t *pThis_6C16; // eax
  int v226; // eax
  int fld_e16642; // ecx
  int jj; // edi
  int v229; // eax
  int v230; // edi
  int nPhaseArg; // eax
  int fld_e916; // ecx  | +0x016C → ★ 场景动画池指针（CNMage；va=005DE690）
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
  int nVariantSel_5; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  uint32_t *pThis_8482; // edi
  int pThis_6C17; // eax
  uint32_t *pThis_6C18; // eax
  double v251; // st7
  int v252; // eax
  int v253; // eax
  int v254; // edx
  int v255; // ebx
  int v256; // ebx
  int fld_e294; // ecx  | +0x0074 → 0x5DE690 读取槽（fld_74）（CNMage；va=005DE690）
  uint32_t *v258; // edi
  int v259; // edx
  int v260; // eax
  int v261; // eax
  int v262; // ecx
  int *v263; // eax
  int v264; // ebx
  int nVariantSel_4; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  int v266; // edi
  int v267; // eax
  int v268; // eax
  int v269; // edx
  int nVariantSel_3; // eax  | +0x1E80 → ★ 变体选择（0x5DE690: +7808==1 分支）（CNMage；va=005DE690）
  int v271; // eax
  float fld_e19548; // eax  | +0x1E88 → ★ 子状态 B（0x5DE690: +7816==11 判据）（CNMage；va=005DE690）
  int nSubStateB_3; // eax  | +0x1E88 → ★ 子状态 B（0x5DE690: +7816==11 判据）（CNMage；va=005DE690）
  uint32_t *pThis_6C7; // eax
  uint32_t *pThis_6C8; // eax
  int64_t fld_e19544; // rax  | +0x1E88 → ★ 子状态 B（0x5DE690: +7816==11 判据）（CNMage；va=005DE690）
  int fld_e19543; // eax  | +0x1E88 → ★ 子状态 B（0x5DE690: +7816==11 判据）（CNMage；va=005DE690）
  int v278; // eax
  int nSkillNo; // eax  | +0x1F1C → ★ 技能号（0x5DE690: ==30 时走 case 14 的 FollowMeCast 召集演出）（CNMage；va=005DE690）
  int v280; // ecx
  int v281; // [esp+B4h] [ebp-1A4h]
  int v282; // [esp+B8h] [ebp-1A0h]
  int fld_e994; // [esp+B8h] [ebp-1A0h]
  int v284; // [esp+BCh] [ebp-19Ch]
  unsigned int fld_e2147; // [esp+C8h] [ebp-190h]
  unsigned int fld_e21472; // [esp+C8h] [ebp-190h]
  unsigned int fld_e21473; // [esp+C8h] [ebp-190h]
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
  int fld_e139; // [esp+D8h] [ebp-180h]
  int nPhaseGroupIdx_; // [esp+D8h] [ebp-180h]  | +0x2178 → ★ 相位组索引（CNMage；va=005DE690）
  int v305; // [esp+D8h] [ebp-180h]
  int v306; // [esp+D8h] [ebp-180h]
  int nSubStateB_2; // [esp+D8h] [ebp-180h]  | +0x1E88 → ★ 子状态 B（0x5DE690: +7816==11 判据）（CNMage；va=005DE690）
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
  int nBigState; // [esp+120h] [ebp-138h] BYREF  | +0x199C → ★ 法师大状态 ID（CNMage；va=005DE690）
  float v323; // [esp+124h] [ebp-134h]
  int fld_e99; // [esp+128h] [ebp-130h]
  char Buffer[276]; // [esp+12Ch] [ebp-12Ch] BYREF
  int v326; // [esp+240h] [ebp-18h]
  int v327; // [esp+244h] [ebp-14h]
  int dword_796E502; // [esp+248h] [ebp-10h]
  int v329; // [esp+254h] [ebp-4h]
  int v330; // [esp+260h] [ebp+8h]
  int v331; // [esp+260h] [ebp+8h]
  int v332; // [esp+260h] [ebp+8h]
  int v333; // [esp+260h] [ebp+8h]
  int v334; // [esp+260h] [ebp+8h]
  int v335; // [esp+260h] [ebp+8h]
  int fld_e1664; // [esp+260h] [ebp+8h]
  float v337; // [esp+260h] [ebp+8h]
  uint32_t *pThis_8453; // [esp+260h] [ebp+8h]
  int v339; // [esp+260h] [ebp+8h]
  int v340; // [esp+260h] [ebp+8h]

  // ── [段 1] 入口序：保存 this+6556（大状态机状态号）到 fld_e1639，初始化局部量，进入第一重 switch ──
  //   this=CNMage 法师对象（本函数 = CNMage::vt+472，见 data/class_method_slots.txt）；nArg2=动作/事件号
  dword_796E502 = dword_796E50;  // dword_796E502 复制自 dword_796E50
  nBigState = (int)*(this + 1639);  // 读 this+1639（0x199C）= nBigState6556
  v327 = 15;  // 局部 v327 → 15
  v326 = 0;  // 局部 v326 → 0
  Buffer[260] = 0;
  nArg22 = nArg2;  // nArg22 复制自 nArg2
  v329 = 0;  // 局部 v329 → 0
  // ── [段 2] 第一重 switch(fld_e1639)：★ 收招/收尾分支——把已建好的动画件回挂到角色身上 ──
  //   case 10/18/19/20/21 各自取缓存的动画指针 → LABEL_51 经 vt+208 挂载
  switch ( nBigState )  // 第一重 switch：按法师大状态 ID 分派收招/收尾
  {
    // ── [段 3] case 10（施法/投掷态收尾）：按 this+1954 子类型逐个回挂缓存的投掷动画 ──
    //   this+1952=左右手/分型，+2106..+2120 是 case 10 主体预先建好的动画件槽
    case 10:  // 【case 10】分型分支
      if ( *(this + 1953) == nullptr )  // this+1953（nSubStateA） 为空
      {
        if ( *(this + 1957) == nullptr && *(this + 1954) == (uint32_t *)11 )
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + (uint32_t)*(this + 1952) + 2106));  // vt[52]（+208）挂动画件
        nSubStateB = (int)*(this + 1954);  // 读 this+1954（0x1E88）= nSubStateB
        switch ( nSubStateB )  // switch(fld_e1954) 多路分派
        {
          case 5:  // 【case 5】分型分支
          case 6:  // 【case 6】分型分支
          case 7:  // 【case 7】分型分支
          case 9:  // 【case 9】分型分支
          case 8:  // 【case 8】分型分支
            v15 = (int)*this;  // 取虚表指针
            if ( *(this + 1952) != nullptr )  // this+1952（nSubStateA） 非空
              fld_e2109 = (int)*(this + 2109);  // 读 this+2109（0x20F4）= pBuffObjB
            else
              fld_e2109 = (int)*(this + 2108);  // 读 this+2108（0x20F0）= pBuffObjA
            goto LABEL_51;  // 转到 LABEL_51
          case 16:  // 【case 16】分型分支
            if ( nArg2 != 10 )  // nArg2 不等于 10
            {
              fld_e2109 = (int)*(this + 2112);  // 读 this+2112（0x2100）= nThrustMode
              goto LABEL_50;  // 转到 LABEL_50
            }
            break;
          case 17:  // 【case 17】分型分支
            if ( *(this + 1952) == (uint32_t *)1 )  // this+1952（nSubStateA） 等于 1
            {
              fld_e2109 = (int)*(this + 2113);  // 读 this+2113（0x2104）
              goto LABEL_50;  // 转到 LABEL_50
            }
            break;
          case 18:  // 【case 18】分型分支
            if ( *(this + 1952) == nullptr )  // this+1952（nSubStateA） 为空
            {
              pThis_842 = this + 2114;  // 取 this 偏移 2114 的指针
              for ( i = 2; i != 0; --i )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *pThis_842++);  // vt[52]（+208）挂动画件
              nArg22 = nArg2;  // nArg22 复制自 nArg2
            }
            break;
          case 28:  // 【case 28】分型分支
            if ( *(this + 1952) == nullptr )  // this+1952（nSubStateA） 为空
            {
              fld_e2109 = (int)*(this + 2116);  // 读 this+2116（0x2110）
              goto LABEL_50;  // 转到 LABEL_50
            }
            break;
          case 31:  // 【case 31】分型分支
            if ( *(this + 1952) == nullptr )  // this+1952（nSubStateA） 为空
            {
              pThis_845 = this + 2117;  // 取 this 偏移 2117 的指针
              for ( j = 3; j != 0; --j )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *pThis_845++);  // vt[52]（+208）挂动画件
              nArg22 = nArg2;  // nArg22 复制自 nArg2
            }
            break;
          case 15:  // 【case 15】分型分支
            if ( nArg2 != 10 )  // nArg2 不等于 10
              ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t))(*this)[68])(this, 0, 0);  // vt[68]（+272）清参
            break;
          default:
            if ( nSubStateB == 49 && nArg2 != 10 )
            {
              pThis_848 = this + 2120;  // 取 this 偏移 2120 的指针
              for ( k = 2; k != 0; --k )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *pThis_848++);  // vt[52]（+208）挂动画件
              nArg22 = nArg2;  // nArg22 复制自 nArg2
            }
            break;
        }
      }
      break;
    // ── [段 4] case 18/19/20 收尾：18 回挂 +2102/+2103 双动画（须 +2100==4） ──
    //   19 回挂 +2125；20 回挂 +2131（须 +2129==20）—— 三者终点都是 LABEL_50 → LABEL_51 vt+208 挂载
    case 18:  // 【case 18】分型分支
      if ( *(this + 2100) == (uint32_t *)4 )  // this+2100（pAppendage） 等于 4
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + 2102));  // vt[52]（+208）挂动画件
        fld_e2109 = (int)*(this + 2103);  // 读 this+2103（0x20DC）= pAnimE
        goto LABEL_50;  // 转到 LABEL_50
      }
      break;
    case 19:  // 【case 19】分型分支
      fld_e2109 = (int)*(this + 2125);  // 读 this+2125（0x2134）= nHeavenHitVal
      goto LABEL_50;  // 转到 LABEL_50
    case 20:  // 【case 20】分型分支
      if ( *(this + 2129) == (uint32_t *)20 )  // this+2129（nPhaseValA） 等于 20
      {
        fld_e2109 = (int)*(this + 2131);  // 读 this+2131（0x214C）= nSwingMode
LABEL_50:
        v15 = (int)*this;  // 取虚表指针
LABEL_51:
        (*(void (/*stdcall*/ **)(int))(v15 + 208))(fld_e2109);  // 经 v15 的虚表 +208 调用
      }
      break;
    // ── [段 5] case 21 收尾：+2136 回挂 + 无 +2133 时补起魔能充能（sub_4BA730） ──
    case 21:  // 【case 21】分型分支
      if ( nArg2 != 21 )  // nArg2 不等于 21
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + 2136));  // vt[52]（+208）挂动画件
      if ( *(this + 2133) == nullptr )  // this+2133（nPhaseValB） 为空
        sub_4BA730(2, 4, 0, 0);  // 魔能充能下发（模式=2, 组号=4）
      break;
    default:
      break;
  }
  // ── [段 6] 大状态 15 归一：nArg22 与 nArg2 都改写为 8、fld_e1639 改写 15（形态切换别名） ──
  if ( nArg22 == 15 )  // nArg22 等于 15
  {
    nArg22 = 8;  // 局部 nArg22 → 8
    nArg2 = 8;  // 局部 nArg2 → 8
    nBigState = 15;  // 局部 fld_e1639 → 15
  }
  // ── [段 7] 魔能充能收尾：+2142 表参非 -1 且非 0/11 态时，按 sub_5DA1E0 组号驱动 ENERGY_CHARGE 收束 ──
  //   sub_4BA730(2, 组号, 0, 0) 起充能；vt+63 两路清参后 +2142 复位为 -1
  nPhaseGroupIdx = (int)*(this + 2142);  // 读 this+2142（0x2178）= nPhaseGroupIdx
  if ( nPhaseGroupIdx != -1 && nArg22 != 0 && nArg22 != 11 )
  {
    if ( nPhaseGroupIdx >= 55 )
      v17 = 4;  // 局部 v17 → 4
    else
      v17 = dword_738048[nPhaseGroupIdx];  // 按索引取 dword_738048[fld_e2142]
    sub_4BA730(2, v17, 0, 0);  // 魔能充能下发（模式=2, 组号=v17）
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, int))(*this)[63])(this, 0, -1);  // vt[63]（+252）清参
    ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[63])(this, 1, -1);  // vt[63]（+252）清参
    *(this + 2142) = (uint32_t *)-1;  // 写 this+2142（nPhaseGroupIdx） = (uint32_t *)-1
  }
  pArg32 = pArg3;  // pArg32 复制自 pArg3
  // ── [段 8] 第二重 switch(nArg22)：★ 施法/技能演出分型主表（16/17/18/19/20/21/26/27/28/31/43） ──
  //   每 case 骨架：门控 +1952（左右/分型）与 +195x 表参 → 建动画件 → 注册场景 → 播语音
  switch ( nArg22 )  // 第二重 switch：按技能演出分型分派
  {
    // ── [段 9] case 16：WZ_DASH_FALL（冲刺坠落）—— 仅播报，无动画件 ──
    case 16:  // 【case 16】分型分支
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 1554));  // vt[49]（+196）播放语音
      ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 1, 1, 1000, 1000);  // vt[222]（+888）动画时长设置
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, int, int, uint32_t, int, int))(*this)[219])(this, 0, 250, 250, 0, -480, 1);  // vt[219]（+876）位移/动作下发
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      v19 = (int)*this;  // 取虚表指针
      v20 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[38])(this, 4);  // vt[38]（+152）取动作件
      (*(void (/*thiscall*/ **)(uint32_t **, int))(v19 + 896))(this, v20);  // 经 v19 的虚表 +896 调用
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_DASH_FALL", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 WZ_DASH_FALL
      break;
    // ── [段 10] case 17：★ 相位穿梭（WarpCloud.ani）—— 存 pArg3 的坐标/资源到 this+2099 ──
    //   sub_431920 建动画件 → sub_44E1F0 池化壳 → sub_45FE80 注册场景对象表
    case 17:  // 【case 17】分型分支
      fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
      LOBYTE(v329) = 1;  // 异常展开状态号 → 1
      if ( fld_e99 != 0 )  // fld_e99 不等于 0
      {
        if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
          LOBYTE(fld_16C) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
        else
          fld_16C = (int)*(this + 91);  // 读 this+91（0x16C）= pSceneAnimPool
        v22 = sub_431920(fld_16C, (char)"Effect/Animation/WarpCloud.ani", 1);  // 存 建动画件 Effect/Animation/WarpCloud.ani
      }
      else
      {
        v22 = 0;  // 局部 v22 → 0
      }
      fld_e99 = sub_44B6C0(284);  // 存 CRT 一次性池初始化 2
      LOBYTE(v329) = 2;  // 异常展开状态号 → 2
      if ( fld_e99 != 0 )  // fld_e99 不等于 0
        v23 = (int *)sub_44E1F0(v22, 1);  // 存 CNRDPooledObject
      else
        v23 = nullptr;  // v23 置空
      fld_e29 = (int)*(this + 29);  // 读 this+29（0x74）= nReadSlot74
      LOBYTE(v329) = 0;  // 异常展开状态号 → 0
      sub_45FE80(fld_e29, (int)v23, 2, 0, (int)v23, 0, 0);  // 注册场景对象
      v25 = *v23;  // 取 v23 的首字段
      v26 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);  // vt[32]（+128）取帧数
      v27 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v26);  // vt[31]（+124）取帧时长(累加)
      v28 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v27 + 1);  // vt[30]（+120）取帧时长
      (*(void (/*thiscall*/ **)(int *, int))(v25 + 112))(v23, v28);  // 经 v25 的虚表 +112 调用
      if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this)[145])(  // vt[145]（+580）发射 PO 对象
          this,  // 第 1 个实参 this
          23001,  // 第 2 个实参
          *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 20),  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0,  // 第 7 个实参
          50,  // 第 8 个实参
          4,  // 第 9 个实参
          0,  // 第 10 个实参
          0,  // 第 11 个实参
          0);  // 第 12 个实参
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t))(*this)[28])(  // vt[28]（+112）设方位
        this,  // 第 1 个实参 this
        *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4),  // 第 2 个实参
        *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8),  // 第 3 个实参
        0);  // 第 4 个实参
      fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
      LOBYTE(v329) = 3;  // 异常展开状态号 → 3
      if ( fld_e99 != 0 )  // fld_e99 不等于 0
      {
        if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
          LOBYTE(fld_e912) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
        else
          fld_e912 = (int)*(this + 91);  // 读 this+91（0x16C）= pSceneAnimPool
        v30 = sub_431920(fld_e912, (char)"Effect/Animation/WarpCloud.ani", 1);  // 存 建动画件 Effect/Animation/WarpCloud.ani
      }
      else
      {
        v30 = 0;  // 局部 v30 → 0
      }
      fld_e99 = sub_44B6C0(284);  // 存 CRT 一次性池初始化 2
      LOBYTE(v329) = 4;  // 异常展开状态号 → 4
      if ( fld_e99 != 0 )  // fld_e99 不等于 0
        v31 = (int *)sub_44E1F0(v30, 1);  // 存 CNRDPooledObject
      else
        v31 = nullptr;  // v31 置空
      fld_e292 = (int)*(this + 29);  // 读 this+29（0x74）= nReadSlot74
      LOBYTE(v329) = 0;  // 异常展开状态号 → 0
      sub_45FE80(fld_e292, (int)v31, 2, 0, (int)v31, (int)this, 0);  // 注册场景对象
      v33 = *v31;  // 取 v31 的首字段
      v34 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);  // vt[32]（+128）取帧数
      v35 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v34);  // vt[31]（+124）取帧时长(累加)
      v36 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v35);  // vt[30]（+120）取帧时长
      (*(void (/*thiscall*/ **)(int *, int))(v33 + 112))(v31, v36);  // 经 v33 的虚表 +112 调用
      //   sub_49C620/sub_49C5F0 写命令记录（时空域指令，参数含 pArg3 的 +12/+16 字段）；尾部播 PHASE_SHIFT + WZ_PHASE_SHIFT
      sub_49C620(0, 1, 0);  // 命令下发包装
      pArg33 = pArg3;  // pArg33 复制自 pArg3
      sub_49C5F0(0, 0, 0, *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12));  // 命令记录写入包装
      fld_e1542 = (int)*(this + 1542);  // 读 this+1542（0x1818）
      v39 = (int)*this;  // 取虚表指针
      *(this + 2099) = *(uint32_t **)(*(uint32_t *)(pArg33 + 4) + 16);  // 写 this+2099（nNameLookup） = *(uint32_t **)(*(uint32_
      (*(void (/*thiscall*/ **)(uint32_t **, int))(v39 + 196))(this, fld_e1542);  // 经 v39 的虚表 +196 调用
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
        this,  // 第 1 个实参 this
        0,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, int, int))(*this)[222])(this, 0, 0, 1000, 1000);  // vt[222]（+888）动画时长设置
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "PHASE_SHIFT", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 PHASE_SHIFT
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_PHASE_SHIFT", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 WZ_PHASE_SHIFT
      break;
    // ── [段 11] case 18：★ 投掷剑（ThrustUnder/ThrustOver）—— 技能表查参 + 帧时长反算 ──
    //   +2100 存分型（==4 走另一支）；sub_47EFD0/sub_47EF20 读技能表（+87 处 14 字节项表）
    case 18:  // 【case 18】分型分支
      v40 = (int)*this;  // 取虚表指针
      v300 = **(uint32_t ***)(pArg3 + 4);  // 二级解引用取参数包首值
      *(this + 2100) = v300;  // 写 this+2100（pAppendage） = v300
      *((uint8_t *)this + 8404) = 0;  // this 字节 +8404 置 0
      v41 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v40 + 1160))(this, v300);
      fld_e2100 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2100));  // vt[285]（+1140）取技能值
      if ( *(this + 2100) == (uint32_t *)4 )  // this+2100（pAppendage） 等于 4
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[86])(this, *(this + 139));  // vt[86]（+344）清参
        v43 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);  // vt[97]（+388）取时长
        v44 = sub_47EFD0(v41, 0.0, fld_e2100, v43, v43, 11);  // 存 技能表槽位设置
        v45 = (int)*this;  // 取虚表指针
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v44 - 100);  // 写 this+99（uReflectCtx） = (uint32_t *)((char *)*(t
        v46 = (*(int (/*thiscall*/ **)(uint32_t **))(v45 + 388))(this);
        LODWORD(v323) = 100 * sub_47EFD0(v41, COERCE_FLOAT(2), fld_e2100, v46, v46, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)SLODWORD(v323) + *((float *)this + 97);
        *(float *)&v47 = COERCE_FLOAT(sub_47EF20(1, fld_e2100, -1, -1, 11));
        v48 = (int)*this;  // 取虚表指针
        v323 = *(float *)&v47;
        v321 = (double)v47 * 0.001 + 1.0;
        v49 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v48 + 672))(this, 3);
        v323 = COERCE_FLOAT(sub_495500(v49));
        v50 = (uint64_t)((double)SLODWORD(v323) * v321);
        ((void (/*fastcall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          (uint64_t)((double)SLODWORD(v323) * v321) >> 32,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0,  // 第 7 个实参
          0);  // 第 8 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, int, int))(*this)[222])(this, 0, 0, v50, v50);  // vt[222]（+888）动画时长设置
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);  // vt[224]（+896）帧组设置
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[1]);  // vt[49]（+196）播放语音
        if ( *(this + 2102) == nullptr )  // this+2102（nEplpMode） 为空
        {
          fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
          LOBYTE(v329) = 5;  // 异常展开状态号 → 5
          if ( fld_e99 != 0 )  // fld_e99 不等于 0
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
              pThis_6C = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ThrustUnder.ani", 1);
            else
              pThis_6C = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/ThrustUnder.ani", 1);
          }
          else
          {
            pThis_6C = nullptr;  // pThis_6C 置空
          }
          *(this + 2102) = pThis_6C;  // 写 this+2102（nEplpMode） = pThis_6C
          fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
          LOBYTE(v329) = 6;  // 异常展开状态号 → 6
          if ( fld_e99 != 0 )  // fld_e99 不等于 0
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
              pThis_6C2 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ThrustOver.ani", 1);
            else
              pThis_6C2 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/ThrustOver.ani", 1);
          }
          else
          {
            pThis_6C2 = nullptr;  // pThis_6C2 置空
          }
          LOBYTE(v329) = 0;  // 异常展开状态号 → 0
          *(this + 2103) = pThis_6C2;  // 写 this+2103（pAnimE） = pThis_6C2
        }
        nWeaponItemId = *(this + 1625);  // 取 this+1625（nWeaponItemId）
        v54 = *nWeaponItemId;  // 取 fld_e1625 的首字段
        v323 = 0.0;
        fld_e992 = (*(int (/*thiscall*/ **)(int *))(v54 + 248))(nWeaponItemId);
        fld_e99 = fld_e992;  // fld_e99 复制自 fld_e992
        v320 = 0;  // 局部 v320 → 0
        v321 = 0.0;
        //   +99 槽累加动画长度、+97(浮点) 累加帧数比 —— 把技能时长按动画帧标定（除 +25 补偿）
        while ( 1 )
        {
          v56 = *(uint32_t *)(fld_e992 + 4);
          if ( v56 == 0 || v320 >= (*(uint32_t *)(fld_e992 + 8) - v56) / 124 )
            break;
          if ( *(uint32_t *)(*(uint32_t *)(LODWORD(v321) + v56 + 60) + 4) != 0 )
          {
            v57 = sub_4924C0(5);  // 存 按索引取帧并确保图像就绪
            v58 = *(float **)(v57 + 60);
            for ( m = *(float **)(v57 + 64); v58 != m; v58 += 6 )
            {
              v60 = v58[3] + *v58;
              if ( v60 > (double)SLODWORD(v323) )
                LODWORD(v323) = (uint64_t)v60;
            }
          }
          LODWORD(v321) += 124;
          fld_e992 = fld_e99;  // fld_e992 复制自 fld_e99
          ++v320;  // 帧计数自增
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
          this,  // 第 1 个实参 this
          -1,  // 第 2 个实参
          *(this + 2102),  // 第 3 个实参
          LODWORD(v323) - 5,  // 第 4 个实参
          -41,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          *(this + 2103),  // 第 3 个实参
          LODWORD(v323) - 5,  // 第 4 个实参
          -41,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
      }
      //   随后按帧链表（fld_e992）逐帧扫 DELAY 字段（v323 比较）挑出最长帧，再播 R_WZ_PRICK
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "R_WZ_PRICK", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 R_WZ_PRICK
      break;
    // ── [段 12] case 19：★ 天上斩（WZ_PRE_HEAVENHIT / HEAVEN_HIT_MOVE 双段播报） ──
    //   +2124 存分型（12 走另一支）；UpperSwing.ani 预载到 +2125；+2127 初值 -150（位移量）
    case 19:  // 【case 19】分型分支
      v61 = (int)*this;  // 取虚表指针
      v301 = **(uint32_t ***)(pArg3 + 4);  // 二级解引用取参数包首值
      *(this + 2124) = v301;  // 写 this+2124（nChargeState） = v301
      v62 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v61 + 1160))(this, v301);
      fld_e2124 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2124));  // vt[285]（+1140）取技能值
      if ( *(this + 2124) == (uint32_t *)12 )  // this+2124（nChargeState） 等于 12
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 38);  // vt[86]（+344）清参
        v64 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);  // vt[97]（+388）取时长
        v65 = sub_47EFD0(v62, 0.0, fld_e2124, v64, v64, 11);  // 存 技能表槽位设置
        v66 = (int)*this;  // 取虚表指针
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v65 - 100);  // 写 this+99（uReflectCtx） = (uint32_t *)((char *)*(t
        v67 = (*(int (/*thiscall*/ **)(uint32_t **))(v66 + 388))(this);
        fld_e99 = 100 * sub_47EFD0(v62, COERCE_FLOAT(4), fld_e2124, v67, v67, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)fld_e99 + *((float *)this + 97);
        *(this + 114) = (uint32_t *)sub_47EF20(2, fld_e2124, -1, -1, 11);  // 写 this+114（pKeyVecEnd） = (uint32_t *)sub_47EF20(2
        v68 = (uint32_t *)sub_47EF20(3, fld_e2124, -1, -1, 11);
        v69 = (int)*this;  // 取虚表指针
        *(this + 113) = v68;  // 写 this+113（nAtkRollVal） = v68
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t))(v69 + 196))(this, (*(this + 1554))[2]);  // 经 v69 的虚表 +196 调用
        v70 = sub_47EF20(1, fld_e2124, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
        v71 = (int)*this;  // 取虚表指针
        fld_e99 = v70;  // fld_e99 复制自 v70
        v323 = (double)v70 * 0.001 + 1.0;
        v72 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v71 + 672))(this, 3);
        fld_e99 = sub_495500(v72);  // 存 槽对乘积读取
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[222])(  // vt[222]（+888）动画时长设置
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          0,  // 第 3 个实参
          (uint64_t)((double)fld_e99 * v323),  // 第 4 个实参
          (uint64_t)((double)fld_e99 * v323));  // 第 5 个实参
        v73 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1);  // vt[283]（+1132）取动画资源
        v74 = (int)*this;  // 取虚表指针
        *(this + 2128) = (uint32_t *)v73;  // 写 this+2128（nChargeSelIdx） = (uint32_t *)v73
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t, int, int, uint32_t, int, int))(v74 + 876))(
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          360,  // 第 3 个实参
          360,  // 第 4 个实参
          0,  // 第 5 个实参
          -1800,  // 第 6 个实参
          1);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, int))(*this)[219])(this, 1, 300, 300, 0, -1500, 1);  // vt[219]（+876）位移/动作下发
        v75 = (int)*this;  // 取虚表指针
        nPhaseRefA = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[38])(this, *(this + 2128));  // vt[38]（+152）取动作件
        (*(void (/*thiscall*/ **)(uint32_t **, int))(v75 + 896))(this, nPhaseRefA);  // 经 v75 的虚表 +896 调用
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
          this,  // 第 1 个实参 this
          "WZ_PRE_HEAVENHIT",  // 第 2 个实参：串 WZ_PRE_HEAVENHIT
          -1,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
        this,  // 第 1 个实参 this
        "HEAVEN_HIT_MOVE",  // 第 2 个实参：串 HEAVEN_HIT_MOVE
        -1,  // 第 3 个实参
        0,  // 第 4 个实参
        0);  // 第 5 个实参
      v77 = (void *)((int (/*thiscall*/ *)(uint32_t **, int))(*this)[293])(this, 1);  // vt[293]（+1172）调用
      sub_406D60(v77);  // std::string 从 C 串赋值
      if ( *(this + 2125) == nullptr )  // this+2125（nHeavenHitVal） 为空
      {
        fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
        LOBYTE(v329) = 7;  // 异常展开状态号 → 7
        if ( fld_e99 != 0 )  // fld_e99 不等于 0
        {
          if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
            pThis_6C3 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/UpperSwing.ani", 1);
          else
            pThis_6C3 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/UpperSwing.ani", 1);
        }
        else
        {
          pThis_6C3 = nullptr;  // pThis_6C3 置空
        }
        LOBYTE(v329) = 0;  // 异常展开状态号 → 0
        *(this + 2125) = pThis_6C3;  // 写 this+2125（nHeavenHitVal） = pThis_6C3
      }
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        *(this + 2125),  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      *((uint8_t *)this + 8504) = 0;  // this 字节 +8504 置 0
      *(this + 2127) = (uint32_t *)-150;  // 写 this+2127（f_213C） = (uint32_t *)-150
      break;
    // ── [段 13] case 20：★ 挥击（WhipToMonsterSwing / WZ_SWING_READY / PALM_FLASH） ──
    //   +2129 存分型；13 走掌击支（PALM_FLASH + R_WZ_PALMFLASH），20 走鞭击支（+2131 动画件）
    case 20:  // 【case 20】分型分支
      v79 = (int)*this;  // 取虚表指针
      v302 = **(uint32_t ***)(pArg3 + 4);  // 二级解引用取参数包首值
      *(this + 2129) = v302;  // 写 this+2129（nPhaseValA） = v302
      *((uint8_t *)this + 8520) = 0;  // this 字节 +8520 置 0
      v80 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v79 + 1160))(this, v302);
      nPhaseValA = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2129));  // vt[285]（+1140）取技能值
      nPhaseValA_ = (int)*(this + 2129);  // 读 this+2129（0x2144）= nPhaseValA
      if ( nPhaseValA_ == 13 )  // fld_e21292 等于 13
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 76);  // vt[86]（+344）清参
        v83 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);  // vt[97]（+388）取时长
        v84 = sub_47EFD0(v80, 0.0, nPhaseValA, v83, v83, 11);  // 存 技能表槽位设置
        v85 = (int)*this;  // 取虚表指针
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v84 - 100);  // 写 this+99（uReflectCtx） = (uint32_t *)((char *)*(t
        v86 = (*(int (/*thiscall*/ **)(uint32_t **))(v85 + 388))(this);
        fld_e99 = 100 * sub_47EFD0(v80, COERCE_FLOAT(3), nPhaseValA, v86, v86, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)fld_e99 + *((float *)this + 97);
        //   sub_47EF20(1..4, 分型) 连续查技能表取伤害/时长；sub_495500 取槽对乘积（+844/+858）
        *(this + 113) = (uint32_t *)sub_47EF20(1, nPhaseValA, -1, -1, 11);  // 写 this+113（nAtkRollVal） = (uint32_t *)sub_47EF20(1
        v87 = (uint32_t *)sub_47EF20(2, nPhaseValA, -1, -1, 11);
        v88 = (int)*this;  // 取虚表指针
        *(this + 114) = v87;  // 写 this+114（pKeyVecEnd） = v87
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t))(v88 + 196))(this, (*(this + 1554))[3]);  // 经 v88 的虚表 +196 调用
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 2, 2, 1000, 1000);  // vt[222]（+888）动画时长设置
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);  // vt[224]（+896）帧组设置
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
          this,  // 第 1 个实参 this
          "WZ_SWING_READY",  // 第 2 个实参：串 WZ_SWING_READY
          -1,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
      }
      else if ( nPhaseValA_ == 20 )
      {
        v89 = (int)*this;  // 取虚表指针
        fld_e139 = (int)(*(this + 139) + 152);
        *(this + 2132) = (uint32_t *)4;  // 写 this+2132（szMonText） = (uint32_t *)4
        (*(void (/*thiscall*/ **)(uint32_t **, int))(v89 + 344))(this, fld_e139);  // 经 v89 的虚表 +344 调用
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[5]);  // vt[49]（+196）播放语音
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 3, 3, 1000, 1000);  // vt[222]（+888）动画时长设置
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);  // vt[224]（+896）帧组设置
        if ( *(this + 2131) == nullptr )  // this+2131（nSwingMode） 为空
        {
          fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
          LOBYTE(v329) = 8;  // 异常展开状态号 → 8
          if ( fld_e99 != 0 )  // fld_e99 不等于 0
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
              pThis_6C4 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/WhipToMonsterSwing.ani", 1);
            else
              pThis_6C4 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/WhipToMonsterSwing.ani", 1);
          }
          else
          {
            pThis_6C4 = nullptr;  // pThis_6C4 置空
          }
          LOBYTE(v329) = 0;  // 异常展开状态号 → 0
          *(this + 2131) = pThis_6C4;  // 写 this+2131（nSwingMode） = pThis_6C4
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          *(this + 2131),  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
      }
      break;
    // ── [段 14] case 21：★ 替身/挑衅（SPIRIT_SACRIFICE 前置）—— 分型 14 走 PALM_FLASH 支 ──
    //   +2133/+2134/+2135 三表参；sub_432E50 关系码对调（左右朝向）；sub_4939E0/sub_493A60 动画冻结+时间推进
    case 21:  // 【case 21】分型分支
      v91 = **(uint32_t ***)(pArg3 + 4);  // 二级解引用取参数包首值
      *(this + 2133) = v91;  // 写 this+2133（nPhaseValB） = v91
      if ( v91 != nullptr )  // v91 不等于 nullptr
      {
        if ( v91 == (uint32_t *)1 )
          *(this + 2135) = *(uint32_t **)(*(uint32_t *)(pArg32 + 4) + 4);  // 写 this+2135（nPhaseStamp） = *(uint32_t **)(*(uint32_
      }
      else
      {
        *(this + 2134) = *(uint32_t **)(*(uint32_t *)(pArg32 + 4) + 4);  // 写 this+2134 = *(uint32_t **)(*(uint32_
      }
      fld_e2134 = (char *)((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[290])(this, *(this + 2134));  // vt[290]（+1160）取动画资源
      fld_e21342 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2134));  // vt[285]（+1140）取技能值
      fld_e21343 = *(this + 2134) == (uint32_t *)14;
      fld_e99 = fld_e21342;  // fld_e99 复制自 fld_e21342
      if ( fld_e21343 )
      {
        nPhaseValB = (int)*(this + 2133);  // 读 this+2133（0x2154）= nPhaseValB
        if ( nPhaseValB != 0 )  // fld_e2133 不等于 0
        {
          if ( nPhaseValB == 1 )  // fld_e2133 等于 1
          {
            v98 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);  // vt[38]（+152）取动作件
            v99 = sub_432E50(v98);  // 存 关系码对调映射 【关系码对调映射】0 与 1 互换与 2 与 3 互换，其余返回 4
            v100 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[283])(this, 0);  // vt[283]（+1132）取动画资源
            v101 = (int)*this;  // 取虚表指针
            if ( v100 == v99 )  // v100 等于 v99
              (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v101 + 876))(0, 0, 0, 0, 0, 0);  // 经 v101 的虚表 +876 调用
            else
              (*(void (/*stdcall*/ **)(uint32_t, int, int, uint32_t, int, int))(v101 + 876))(
                0,  // 第 1 个实参 this
                dword_9B9338,  // 第 2 个实参
                dword_9B9338,  // 第 3 个实参
                0,  // 第 4 个实参
                dword_9B933C,  // 第 5 个实参
                1);  // 第 6 个实参
            v102 = (int)*this;  // 取虚表指针
            v103 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[38])(this, 4);  // vt[38]（+152）取动作件
            (*(void (/*thiscall*/ **)(uint32_t **, int))(v102 + 896))(this, v103);  // 经 v102 的虚表 +896 调用
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
              this,  // 第 1 个实参 this
              "PALM_FLASH",  // 第 2 个实参：串 PALM_FLASH
              -1,  // 第 3 个实参
              0,  // 第 4 个实参
              0);  // 第 5 个实参
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
              this,  // 第 1 个实参 this
              "R_WZ_PALMFLASH",  // 第 2 个实参：串 R_WZ_PALMFLASH
              -1,  // 第 3 个实参
              0,  // 第 4 个实参
              0);  // 第 5 个实参
            ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 114);  // vt[86]（+344）清参
            v104 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);  // vt[97]（+388）取时长
            fld_e993 = fld_e99;  // fld_e993 复制自 fld_e99
            v106 = sub_47EFD0(fld_e2134, COERCE_FLOAT(1), fld_e99, v104, v104, 0);  // 存 技能表槽位设置
            v107 = (int)*this;  // 取虚表指针
            fld_e99 = v106;  // fld_e99 复制自 v106
            v108 = (*(int (/*thiscall*/ **)(uint32_t **))(v107 + 388))(this);
            v109 = sub_47EFD0(fld_e2134, 0.0, fld_e993, v108, v108, 0);  // 存 技能表槽位设置
            fld_e99 = sub_423A80(v109, fld_e99, *(this + 2135), dword_9B9340);  // 存 区间线性插值取整 sub_4049C0
            *((float *)this + 97) = (float)fld_e99;
            *(this + 113) = (uint32_t *)sub_47EF20(2, fld_e993, -1, -1, 11);  // 写 this+113（nAtkRollVal） = (uint32_t *)sub_47EF20(2
            *(this + 114) = (uint32_t *)sub_47EF20(3, fld_e993, -1, -1, 11);  // 写 this+114（pKeyVecEnd） = (uint32_t *)sub_47EF20(3
          }
        }
        else
        {
          v96 = sub_47EF20(4, fld_e21342, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
          v97 = (int)*this;  // 取虚表指针
          fld_e99 = v96;  // fld_e99 复制自 v96
          v323 = (double)v96 * 0.001 + 1.0;
          fld_e99 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v97 + 900))(this, 3);
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[222])(  // vt[222]（+888）动画时长设置
            this,  // 第 1 个实参 this
            0,  // 第 2 个实参
            0,  // 第 3 个实参
            (uint64_t)((double)fld_e99 * v323),  // 第 4 个实参
            (uint64_t)((double)fld_e99 * v323));  // 第 5 个实参
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
            this,  // 第 1 个实参 this
            0,  // 第 2 个实参
            0,  // 第 3 个实参
            0,  // 第 4 个实参
            0,  // 第 5 个实参
            0,  // 第 6 个实参
            0);  // 第 7 个实参
          ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
            this,  // 第 1 个实参 this
            1,  // 第 2 个实参
            0,  // 第 3 个实参
            0,  // 第 4 个实参
            0,  // 第 5 个实参
            0,  // 第 6 个实参
            0);  // 第 7 个实参
          ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);  // vt[224]（+896）帧组设置
        }
      }
      nPhaseValB_ = (int)*(this + 2133);  // 读 this+2133（0x2154）= nPhaseValB
      if ( nPhaseValB_ != 0 )  // fld_e21332 不等于 0
      {
        if ( nPhaseValB_ == 1 )  // fld_e21332 等于 1
        {
          *(this + 2137) = (uint32_t *)-200;  // 写 this+2137（nPhaseEndB） = (uint32_t *)-200
          pThis_838 = this + 2104;  // 取 this 偏移 2104 的指针
          for ( n = 2; n != 0; --n )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_838 + 12))(*pThis_838, 0);
            ++pThis_838;  // pThis_838 自增
          }
          sub_4939E0((int)*(this + 30), 0);  // 播放/暂停级联
          v114 = sub_491C70(8);  // 存 ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48
          sub_493A60(v114);  // 时间推进包装
          nFxCtx = (int)*(this + 2136);  // 读 this+2136（0x2160）= nFxCtx
          LOBYTE(nArg5) = 0;
          sub_4939E0(nFxCtx, 0);  // 播放/暂停级联
          v116 = sub_491C70(8);  // 存 ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48
          sub_493A60(v116);  // 时间推进包装
          sub_491F80(-1, -1, -1, -1, 1);  // RGBA 设置
        }
      }
      else
      {
        //   分支：+21332 为 1 时补 HandStrike.ani 预载（+2136）+ 满帧 DELAY 覆写 + vt+51 挂载
        if ( *(this + 2136) == nullptr )  // this+2136（nFxCtx） 为空
        {
          fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
          LOBYTE(v329) = 9;  // 异常展开状态号 → 9
          if ( fld_e99 != 0 )  // fld_e99 不等于 0
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
              pThis_6C5 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HandStrike.ani", 1);
            else
              pThis_6C5 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/HandStrike.ani", 1);
          }
          else
          {
            pThis_6C5 = nullptr;  // pThis_6C5 置空
          }
          LOBYTE(v329) = 0;  // 异常展开状态号 → 0
          *(this + 2136) = pThis_6C5;  // 写 this+2136（nFxCtx） = pThis_6C5
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          *(this + 2136),  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[4]);  // vt[49]（+196）播放语音
        *(this + 2145) = nullptr;  // 写 this+2145（nPhaseStage） = nullptr
      }
      break;
    // ── [段 15] 第二重 switch 结束 ──
    default:
      break;
  }
  pArg34 = pArg3;  // pArg34 复制自 pArg3
  sub_4B89D0(nArg2, pArg3, *(float *)&pArg4, *(float *)&nArg5);  // 跑步地面循环 + 蓄气/霸体特效 G_RUN_FLOOR_LOOP/RUN_GRASS/SOIL/STONE_LOOP 按 +212 地形选播
  // ── [段 16] 第三重 switch(nArg2)：★ 动作事件号分派（0/6/7/8/10/11/12/14）—— 与「技能分型」正交 ──
  //   本层先调 sub_4B89D0 做跑步地面循环/蓄气特效的公共前置
  switch ( nArg2 )  // 第三重 switch：按动作事件号分派
  {
    case 0:  // 【case 0】分型分支
      goto LABEL_156;  // 转到 LABEL_156
    // ── [段 17] case 6：★ 冲刺/连打位移——按 +8585 标志决定是否施加 vt+219 双段位移（左右手分算） ──
    //   随后关系码对调 + vt+224（末段动作）
    case 6:  // 【case 6】分型分支
      fld_e1723 = (int)*(this + 1723);  // 读 this+1723（0x1AEC）= nSkillCtxVal
      if ( fld_e1723 == 0 )  // fld_e1723 等于 0
        *((uint8_t *)this + 8585) = 0;  // this 字节 +8585 置 0
      if ( *((uint8_t *)this + 8585) != 0 && fld_e1723 == 1 )
      {
        fld_e2147 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          fld_e2147,  // 第 3 个实参
          fld_e2147,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        v124 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);  // vt[38]（+152）取动作件
        if ( (int)*(this + 2147) < 0 )
          v124 = sub_432E50(v124);  // 存 关系码对调映射 【关系码对调映射】0 与 1 互换与 2 与 3 互换，其余返回 4
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v124, 4);  // vt[224]（+896）帧组设置
        *((uint8_t *)this + 6996) = 1;  // this 字节 +6996 置 1
      }
      return;
    // ── [段 18] case 7：同上但清 +8220，并多一步 vt+1172 取动作数据后交 sub_406D60 赋值 ──
    case 7:  // 【case 7】分型分支
      v125 = (int)*this;  // 取虚表指针
      *((uint8_t *)this + 8220) = 0;  // this 字节 +8220 置 0
      v126 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v125 + 1172))(this, 1);
      sub_406D60(v126);  // std::string 从 C 串赋值
      if ( *((uint8_t *)this + 8585) != 0 )
      {
        fld_e21472 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          fld_e21472,  // 第 3 个实参
          fld_e21472,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        v127 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);  // vt[38]（+152）取动作件
        if ( (int)*(this + 2147) < 0 )
          v127 = sub_432E50(v127);  // 存 关系码对调映射 【关系码对调映射】0 与 1 互换与 2 与 3 互换，其余返回 4
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v127, 4);  // vt[224]（+896）帧组设置
      }
      return;
    // ── [段 19] case 8：★ 普攻（R_WZ_ATK / R_WZ_LAST_ATK）—— +2054 存目标 id，按连击数选语音 ──
    case 8:  // 【case 8】分型分支
      if ( nBigState != 8 )  // fld_e1639 不等于 8
      {
        if ( (unsigned int)sub_41C5A0(pArg34) <= 1 )
          v118 = -1;
        else
          v118 = *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 4);
        *(this + 2054) = (uint32_t *)v118;  // 写 this+2054（nAtkActionType） = (uint32_t *)v118
      }
      if ( *(this + 2054) != (uint32_t *)-1 )
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[332])(this, 0);  // vt[332]（+1328）调用
      v119 = (int)*this;  // 取虚表指针
      *((uint8_t *)this + 8220) = 0;  // this 字节 +8220 置 0
      v120 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v119 + 1172))(this, 1);
      sub_406D60(v120);  // std::string 从 C 串赋值
      if ( sub_41A5E0(this + 1757) >= 2 )
        ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("R_WZ_LAST_ATK", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 R_WZ_LAST_ATK
      else
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "R_WZ_ATK", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 R_WZ_ATK
      return;
    // ── [段 20] case 10：★ 投掷主处理（OneHandThrow1/2 预载 + 技能表时长标定 + 魔能充能） ──
    //   门 this+1953 非空即返回；+2144 存时长(ms)、+2142 存充能组、+2143 存到期时刻、+8584 存快速投掷标志
    case 10:  // 【case 10】分型分支
      if ( *(this + 1953) != nullptr )  // this+1953（nSubStateA） 非空
        return;
      nVariantSel = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
      pArg3 = 0;  // 局部 pArg3 → 0
      v321 = 0.0;
      if ( nVariantSel != 0 )  // fld_e1952 不等于 0
      {
        if ( nVariantSel == 1 )  // fld_e1952 等于 1
        {
          nFadeAlpha = (int)*(this + 2144);  // 读 this+2144（0x2180）= nFadeAlpha
          if ( nFadeAlpha > 0 && (unsigned int)sub_41C5A0(pArg34) > 1 )
            pArg3 = 1000 * *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 4) / nFadeAlpha;
          *((uint8_t *)this + 8585) = 0;  // this 字节 +8585 置 0
        }
      }
      else
      {
        if ( (unsigned int)sub_41C5A0(pArg34) <= 0xA )
          v129 = 0;  // 局部 v129 → 0
        else
          v129 = *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 40);
        *(this + 2144) = (uint32_t *)v129;  // 写 this+2144（nFadeAlpha） = (uint32_t *)v129
        if ( v129 > 0 )
        {
          //   sub_699000(this+9) 取当前节拍；+1955 回收为 -1；sub_4BA610 按组号选充能动画；+2145 清空
          *(this + 2142) = *(this + 1954);  // 写 this+2142（nPhaseGroupIdx） = *(this + 1954)
          pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
          nPhaseGroupIdx_ = (int)*(this + 2142);  // 读 this+2142（0x2178）= nPhaseGroupIdx
          *(this + 2143) = (uint32_t *)((char *)*(this + 1955) + pThis_9);  // 写 this+2143（nPhaseElapsed） = (uint32_t *)((char *)*(t
          *(this + 1955) = (uint32_t *)-1;  // 写 this+1955（pInteractSnap） = (uint32_t *)-1
          v131 = sub_5DA1E0(nPhaseGroupIdx_);  // 存 索引→组号映射
          sub_4BA610(v131);  // 魔能充能动画选择
          fld_e2058 = (int)*(this + 2058);  // 读 this+2058（0x2028）= nGrabTable
          *(this + 2145) = nullptr;  // 写 this+2145（nPhaseStage） = nullptr
          if ( fld_e2058 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2058 + 80))(fld_e2058) != 0 )
          {
            v289 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[285])(this, 2, -1);  // vt[285]（+1140）取技能值
            ((void (/*thiscall*/ *)(uint32_t **))(*this)[290])(this);  // vt[290]（+1160）取动画资源
            fld_e21442 = (int)*(this + 2144) * (1000 - sub_47EF20(2, 3, v289, -1, 11)) / 1000;
            *(this + 2144) = (uint32_t *)fld_e21442;  // 写 this+2144（nFadeAlpha） = (uint32_t *)fld_e21442
            if ( fld_e21442 <= 1 )
              fld_e21442 = 1;  // 局部 fld_e21442 → 1
            *(this + 2144) = (uint32_t *)fld_e21442;  // 写 this+2144（nFadeAlpha） = (uint32_t *)fld_e21442
          }
        }
        v134 = (unsigned int)sub_41C5A0(pArg34) > 0xB && *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 44) == 1;
        *((uint8_t *)this + 8584) = v134;
        v294 = 2;  // 局部 v294 → 2
        if ( v134 )
        {
          sub_494F20(2, 0.0);  // 属性浮点槽写入
          v294 = 0;  // 局部 v294 → 0
        }
        sub_495890(v294, 0);  // 模式选择式方位设置
      }
      //   this+1954==11 且 +1957 空时：预载 OneHandThrow1/2 两动画件到 +2106/+2107
      if ( *(this + 1957) == nullptr && *(this + 1954) == (uint32_t *)11 )
      {
        if ( *(this + 2106) == nullptr )  // this+2106（pVecEnd） 为空
        {
          fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
          LOBYTE(v329) = 10;  // 异常展开状态号 → 10
          if ( fld_e99 != 0 )  // fld_e99 不等于 0
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
              pThis_6C6 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/OneHandThrow1.ani", 1);
            else
              pThis_6C6 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/OneHandThrow1.ani", 1);
          }
          else
          {
            pThis_6C6 = nullptr;  // pThis_6C6 置空
          }
          *(this + 2106) = pThis_6C6;  // 写 this+2106（pVecEnd） = pThis_6C6
          fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
          LOBYTE(v329) = 11;  // 异常展开状态号 → 11
          if ( fld_e99 != 0 )  // fld_e99 不等于 0
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
            {
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              *(this + 2107) = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/OneHandThrow2.ani", 1);  // 写 this+2107（pVecCap） = (uint32_t *)sub_431920((
            }
            else
            {
              pSkillCtx = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/OneHandThrow2.ani", 1);
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              *(this + 2107) = pSkillCtx;  // 写 this+2107（pVecCap） = fld_e913
            }
          }
          else
          {
            LOBYTE(v329) = 0;  // 异常展开状态号 → 0
            *(this + 2107) = nullptr;  // 写 this+2107（pVecCap） = nullptr
          }
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          *(this + (uint32_t)*(this + 1952) + 2106),  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        if ( *(this + 1952) == (uint32_t *)1 )  // this+1952（nSubStateA） 等于 1
        {
          pThis_8382 = this + 2104;  // 取 this 偏移 2104 的指针
          for ( ii = 2; ii != 0; --ii )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_8382 + 12))(*pThis_8382, 0);
            ++pThis_8382;  // pThis_8382 自增
          }
        }
      }
      nSubStateB_ = (int)*(this + 1954);  // 读 this+1954（0x1E88）= nSubStateB
      //   this+1954（分型）进入第四重 switch(fld_e19542)：10/11/15/16/17/18/26/27/28/31/43 各一技法 ──
      //   骨架：按 +1952 左右手/分型建动画件 → 播 WZ_ 或 R_WZ_ 语音 → goto LABEL_509 公共尾
      switch ( nSubStateB_ )  // switch(fld_e19542) 多路分派
      {
        case 5:  // 【case 5】分型分支
        case 6:  // 【case 6】分型分支
        case 7:  // 【case 7】分型分支
        case 9:  // 【case 9】分型分支
        case 8:  // 【case 8】分型分支
          if ( *(this + 1952) != nullptr )  // this+1952（nSubStateA） 非空
          {
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              1,  // 第 2 个实参
              *(this + 2109),  // 第 3 个实参
              0,  // 第 4 个实参
              0,  // 第 5 个实参
              0,  // 第 6 个实参
              0);  // 第 7 个实参
            if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
            {
              fld_e19543 = sub_5DA920(*(this + 1954));  // 存 主状态→组号映射
              sub_5DC480(fld_e19543, 0);  // 追击弹发射
            }
            *(this + 2061) = *(this + 1954);  // 写 this+2061（nVariantSel） = *(this + 1954)
          }
          else
          {
            if ( *(this + 2108) == nullptr )  // this+2108（pBuffObjA） 为空
            {
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 12;  // 异常展开状态号 → 12
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C7 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/Chaser/Cast1.ani", 1);
                else
                  pThis_6C7 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/Chaser/Cast1.ani", 1);
              }
              else
              {
                pThis_6C7 = nullptr;  // pThis_6C7 置空
              }
              *(this + 2108) = pThis_6C7;  // 写 this+2108（pBuffObjA） = pThis_6C7
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 13;  // 异常展开状态号 → 13
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C8 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/Chaser/Cast2.ani", 1);
                else
                  pThis_6C8 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/Chaser/Cast2.ani", 1);
              }
              else
              {
                pThis_6C8 = nullptr;  // pThis_6C8 置空
              }
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              *(this + 2109) = pThis_6C8;  // 写 this+2109（pBuffObjB） = pThis_6C8
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              1,  // 第 2 个实参
              *(this + 2108),  // 第 3 个实参
              0,  // 第 4 个实参
              0,  // 第 5 个实参
              0,  // 第 6 个实参
              0);  // 第 7 个实参
            fld_e19544 = sub_5DA920(*(this + 1954));  // 存 主状态→组号映射
            (*(void (/*thiscall*/ **)(uint32_t **, char *, int, uint32_t, uint32_t))(HIDWORD(fld_e19544) + 212))(
              this,  // 第 1 个实参 this
              off_795828[(uint32_t)fld_e19544],  // 第 2 个实参
              -1,  // 第 3 个实参
              0,  // 第 4 个实参
              0);  // 第 5 个实参
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 10 = 追击弹爆炸（WZ_CHASER_EXPLOSION；分型 1 时走 sub_5DCF20 全清理） ──
        case 10:  // 【case 10】分型分支
          nVariantSel_6 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_6 != 0 )  // fld_e19522 不等于 0
          {
            if ( nVariantSel_6 == 1 )  // fld_e19522 等于 1
              sub_5DCF20(this);  // 追击弹爆炸总清理：
          }
          else
          {
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
              this,  // 第 1 个实参 this
              "WZ_CHASER_EXPLOSION",  // 第 2 个实参：串 WZ_CHASER_EXPLOSION
              -1,  // 第 3 个实参
              0,  // 第 4 个实参
              0);  // 第 5 个实参
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 11 = 魔法飞弹（MagicMissile.ptl + R_WZ_MAGIC_MISSILE / R_WZ_MAGIC_MISSILE_READY） ──
        case 11:  // 【case 11】分型分支
          nVariantSel_7 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_7 != 0 )  // fld_e19523 不等于 0
          {
            if ( nVariantSel_7 == 1 )  // fld_e19523 等于 1
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 11);  // vt[290]（+1160）取动画资源
                v330 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 11);  // vt[285]（+1140）取技能值
                v143 = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(  // vt[147]（+588）取资源
                                   this,  // 第 1 个实参 this
                                   "Particle/MagicMissile.ptl");  // 第 2 个实参：串 Particle/MagicMissile.ptl
                v295 = (uint16_t)pArg3;  // 类型转换 pArg3 → v295
                v290 = sub_47EF20(3, v330, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
                v144 = sub_47EF20(2, v330, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
                *(uint32_t *)((char *)v143 + 85) = sub_423A80(v144, v290, v295, 1000);
                v145 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[283])(this, 0);  // vt[283]（+1132）取动画资源
                v146 = (int)*this;  // 取虚表指针
                nBigState = v145;  // fld_e1639 复制自 v145
                v147 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v146 + 1132))(this, 1);
                if ( v147 == 2 )  // v147 等于 2
                {
                  if ( nBigState == ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) )  // vt[38]（+152）取动作件
                    v143[18] = -sub_47E9D0(1);
                  else
                    v143[18] = -sub_47E9D0(2);
                }
                else if ( v147 == 3 )
                {
                  if ( nBigState == ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) )  // vt[38]（+152）取动作件
                    v143[18] = sub_47E9D0(1);
                  else
                    v143[18] = sub_47E9D0(2);
                }
                else
                {
                  v143[18] = 0;
                }
                *(float *)&nArg5 = 0.0;
                pArg4 = 0;  // 局部 pArg4 → 0
                if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 0 )  // vt[38]（+152）取动作件
                  v148 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + 44;  // vt[30]（+120）取帧时长
                else
                  v148 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - 44;  // vt[30]（+120）取帧时长
                v288 = *(uint32_t *)((char *)v143 + 85) * *(uint32_t *)((char *)v143 + 15) / 1000;
                v284 = v143[19];  // 按索引取 v143[19]
                v282 = v143[18];  // 按索引取 v143[18]
                v281 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) + 60;  // vt[32]（+128）取帧数
                v149 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);  // vt[31]（+124）取帧时长(累加)
                sub_4B2580(&nArg5, &pArg4, this, v148, v149, v281, v282, v284, 15, 0, -1, v288, 30, 30, 30);  // 目标搜索 + 瞄准角输出 遍历对象列表
                v150 = v143[19];  // 按索引取 v143[19]
                v143[18] += nArg5;
                v143[19] = pArg4 + v150;
                ((void (/*thiscall*/ *)(uint32_t **, int, int, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(  // vt[145]（+580）发射 PO 对象
                  this,  // 第 1 个实参 this
                  23007,  // 第 2 个实参
                  v330,  // 第 3 个实参
                  v143,  // 第 4 个实参
                  0,  // 第 5 个实参
                  44,  // 第 6 个实参
                  0,  // 第 7 个实参
                  60,  // 第 8 个实参
                  4,  // 第 9 个实参
                  0,  // 第 10 个实参
                  2,  // 第 11 个实参
                  &pArg3);  // 第 12 个实参
                v151 = v143[19];  // 按索引取 v143[19]
                v143[18] -= nArg5;
                v143[19] = v151 - pArg4;
              }
              sub_5DBBD0("R_WZ_MAGIC_MISSILE", 500);  // 延时播报登记
            }
          }
          else
          {
            sub_5DADE0("R_WZ_MAGIC_MISSILE_READY");  // 死亡/移除锚定
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 15 = 灯笼火（R_WZ_LANTERN_FIRE）；dword_78FE2C 全局配合 sub_5C6A90 + sub_5DAE20 相位槽 ──
        case 15:  // 【case 15】分型分支
          nVariantSel_8 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_8 != 0 )  // fld_e19524 不等于 0
          {
            if ( nVariantSel_8 == 1 )  // fld_e19524 等于 1
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
              {
                pThis_2188 = *((uint8_t *)this + 8584);
                dword_78FE2C = 0;  // 局部 dword_78FE2C → 0
                v154 = pThis_2188 != 0 ? 73 : 68;
                v331 = pThis_2188 != 0 ? 0 : 0x35;
                sub_5C6A90(pArg3);  // 网络流写 uint16
                if ( *((uint8_t *)this + 8584) != 0 )
                  sub_5DAE20(dword_9B9344);  // 内联尾插
                v155 = (int)*this;  // 取虚表指针
                v156 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, int, int))(*this)[285])(  // vt[285]（+1140）取技能值
                         this,  // 第 1 个实参 this
                         15,  // 第 2 个实参
                         0,  // 第 3 个实参
                         0,  // 第 4 个实参
                         v154,  // 第 5 个实参
                         0,  // 第 6 个实参
                         v331,  // 第 7 个实参
                         4,  // 第 8 个实参
                         0,  // 第 9 个实参
                         dword_78FE2C,  // 第 10 个实参
                         dword_78FE28);  // 第 11 个实参
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v155 + 580))(this, 23008, v156);  // 经 v155 的虚表 +580 调用
              }
              sub_5DBBD0("R_WZ_LANTERN_FIRE", 500);  // 延时播报登记
              if ( *((uint8_t *)this + 8584) != 0 )
              {
                v157 = (int)*this;  // 取虚表指针
                *((uint8_t *)this + 8585) = 1;  // this 字节 +8585 置 1
                (*(void (/*thiscall*/ **)(uint32_t **, int))(v157 + 1160))(this, 42);  // 经 v157 的虚表 +1160 调用
                *(this + 2147) = (uint32_t *)-sub_47E9D0(0);  // 写 this+2147（f_218C） = (uint32_t *)-sub_47E9D0(
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 42);  // vt[290]（+1160）取动画资源
                v321 = COERCE_FLOAT(sub_47E9D0(1));
              }
            }
          }
          else
          {
            sub_5DADE0("R_WZ_LANTERN_FIRE_READY");  // 死亡/移除锚定
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 16 = LaunchFrostHead（冰霜头）；案例 17 = LaunchFluorescentShoot（荧光弹）；案例 18 = 黑猫 ──
        case 16:  // 【case 16】分型分支
          nVariantSel_9 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_9 == 0 )  // fld_e19525 等于 0
          {
            if ( *(this + 2112) == nullptr )  // this+2112（nThrustMode） 为空
            {
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 14;  // 异常展开状态号 → 14
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C9 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchFrostHead.ani", 1);
                else
                  pThis_6C9 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchFrostHead.ani", 1);
              }
              else
              {
                pThis_6C9 = nullptr;  // pThis_6C9 置空
              }
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              *(this + 2112) = pThis_6C9;  // 写 this+2112（nThrustMode） = pThis_6C9
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              1,  // 第 2 个实参
              *(this + 2112),  // 第 3 个实参
              0,  // 第 4 个实参
              0,  // 第 5 个实参
              0,  // 第 6 个实参
              0);  // 第 7 个实参
            sub_5DADE0("R_WZ_FROSTHEAD_READY");  // 死亡/移除锚定
            goto LABEL_509;  // 转到 LABEL_509
          }
          if ( nVariantSel_9 != 1 )  // fld_e19525 不等于 1
            goto LABEL_509;  // 转到 LABEL_509
          if ( *(this + 2112) != nullptr )  // this+2112（nThrustMode） 非空
            sub_4AECE0(2);  // 【解读】 【推断】动画切换: sub_491C70
          if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) == 0 )  // vt[77]（+308）标志查询
          {
LABEL_278:
            sub_5DBBD0("R_WZ_FROSTHEAD", 450);  // 延时播报登记
            goto LABEL_509;  // 转到 LABEL_509
          }
          ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 16);  // vt[290]（+1160）取动画资源
          v332 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 16);  // vt[285]（+1140）取技能值
          v160 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/LaunchFrostHead.ptl");  // vt[147]（+588）取资源
          v296 = (uint16_t)pArg3;  // 类型转换 pArg3 → v296
          v161 = v160;  // v161 复制自 v160
          v291 = sub_47EF20(3, v332, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
          v162 = sub_47EF20(2, v332, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
          *(uint32_t *)(v161 + 85) = sub_423A80(v162, v291, v296, 1000);
          v163 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1);  // vt[283]（+1132）取动画资源
          v305 = 1;  // 局部 v305 → 1
          if ( v163 != 2 )  // v163 不等于 2
          {
            if ( ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1) == 3 )  // vt[283]（+1132）取动画资源
            {
              v164 = sub_47E9D0(3);  // 存 取 this+103/104 的 14 字节条目表中第 uArg2 条的 clong 值； 越界则退回 sub_461750
LABEL_277:
              *(uint32_t *)(v161 + 31) = v164;
              ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(  // vt[145]（+580）发射 PO 对象
                this,  // 第 1 个实参 this
                23009,  // 第 2 个实参
                v332,  // 第 3 个实参
                v161,  // 第 4 个实参
                0,  // 第 5 个实参
                42,  // 第 6 个实参
                0,  // 第 7 个实参
                100,  // 第 8 个实参
                4,  // 第 9 个实参
                0,  // 第 10 个实参
                2,  // 第 11 个实参
                &pArg3);  // 第 12 个实参
              goto LABEL_278;  // 转到 LABEL_278
            }
            v305 = 2;  // 局部 v305 → 2
          }
          v164 = sub_47E9D0(v305);  // 存 取 this+103/104 的 14 字节条目表中第 uArg2 条的 clong 值； 越界则退回 sub_461750
          goto LABEL_277;  // 转到 LABEL_277
        case 17:  // 【case 17】分型分支
          nVariantSel_10 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_10 != 0 )  // fld_e19526 不等于 0
          {
            if ( nVariantSel_10 == 1 )  // fld_e19526 等于 1
            {
              if ( *(this + 2113) == nullptr )  // this+2113 为空
              {
                fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                LOBYTE(v329) = 15;  // 异常展开状态号 → 15
                if ( fld_e99 != 0 )  // fld_e99 不等于 0
                {
                  if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                    pThis_6C10 = (uint32_t *)sub_431920(
                                       (uint8_t)this + 108,  // 第 1 个实参 this（this 内联缓冲）
                                       (char)"Effect/Animation/LaunchFluorescentShoot.ani",  // 第 2 个实参：串 Effect/Animation/LaunchFluorescentShoot.ani
                                       1);  // 第 3 个实参
                  else
                    pThis_6C10 = (uint32_t *)sub_431920(
                                       (char)*(this + 91),  // 第 1 个实参 this
                                       (char)"Effect/Animation/LaunchFluorescentShoot.ani",  // 第 2 个实参：串 Effect/Animation/LaunchFluorescentShoot.ani
                                       1);  // 第 3 个实参
                }
                else
                {
                  pThis_6C10 = nullptr;  // pThis_6C10 置空
                }
                LOBYTE(v329) = 0;  // 异常展开状态号 → 0
                *(this + 2113) = pThis_6C10;  // 写 this+2113 = pThis_6C10
              }
              ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
                this,  // 第 1 个实参 this
                1,  // 第 2 个实参
                *(this + 2113),  // 第 3 个实参
                44,  // 第 4 个实参
                -60,  // 第 5 个实参
                0,  // 第 6 个实参
                0);  // 第 7 个实参
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
              {
                *(float *)&fld_e19545 = COERCE_FLOAT(((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[290])(this, *(this + 1954)));  // vt[290]（+1160）取动画资源
                v168 = (int)*this;  // 取虚表指针
                v323 = *(float *)&fld_e19545;
                fld_e19546 = (*(int (/*thiscall*/ **)(uint32_t **, uint32_t))(v168 + 1140))(this, *(this + 1954));
                v170 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(  // vt[147]（+588）取资源
                         this,  // 第 1 个实参 this
                         "Particle/LaunchFluorescent.ptl");  // 第 2 个实参：串 Particle/LaunchFluorescent.ptl
                v297 = (uint16_t)pArg3;  // 类型转换 pArg3 → v297
                v292 = sub_47EF20(3, fld_e19546, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
                v171 = sub_47EF20(2, fld_e19546, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
                *(uint32_t *)(v170 + 85) = sub_423A80(v171, v292, v297, 1000);
                *(float *)&v172 = COERCE_FLOAT(sub_47E9D0(1));
                nArg5 = v172;  // nArg5 复制自 v172
                if ( v172 > 0 )
                {
                  v333 = 0;  // 局部 v333 → 0
                  pArg4 = v172;  // pArg4 复制自 v172
                  do
                  {
                    *(uint32_t *)(v170 + 72) = v333 / nArg5;
                    ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, uint32_t, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(  // vt[145]（+580）发射 PO 对象
                      this,  // 第 1 个实参 this
                      23010,  // 第 2 个实参
                      fld_e19546,  // 第 3 个实参
                      v170,  // 第 4 个实参
                      0,  // 第 5 个实参
                      0,  // 第 6 个实参
                      0,  // 第 7 个实参
                      60,  // 第 8 个实参
                      4,  // 第 9 个实参
                      0,  // 第 10 个实参
                      2,  // 第 11 个实参
                      &pArg3);  // 第 12 个实参
                    fld_e21343 = pArg4 == 1;
                    v333 += 360;
                    --pArg4;
                  }
                  while ( !fld_e21343 );
                }
              }
              sub_5DBBD0("R_WZ_FLUORE", 400);  // 延时播报登记
            }
          }
          else
          {
            sub_5DADE0("R_WZ_FLUORE_READY");  // 死亡/移除锚定
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 18 主体：R_WZ_LAUNCH_PLUTO 播报 + LaunchBlackCatCast1/2.ani 双动画件 ──
        case 18:  // 【case 18】分型分支
          nVariantSel_11 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_11 != 0 )  // fld_e19527 不等于 0
          {
            if ( nVariantSel_11 == 1 )  // fld_e19527 等于 1
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
              {
                v176 = (int)*this;  // 取虚表指针
                v177 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[285])(  // vt[285]（+1140）取技能值
                         this,  // 第 1 个实参 this
                         18,  // 第 2 个实参
                         0,  // 第 3 个实参
                         0,  // 第 4 个实参
                         44,  // 第 5 个实参
                         0,  // 第 6 个实参
                         60,  // 第 7 个实参
                         4,  // 第 8 个实参
                         0,  // 第 9 个实参
                         2,  // 第 10 个实参
                         &pArg3);  // 第 11 个实参
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v176 + 580))(this, 23011, v177);  // 经 v176 的虚表 +580 调用
              }
              sub_5DBBD0("R_WZ_LAUNCH_PLUTO", 0);  // 延时播报登记
            }
          }
          else
          {
            if ( *(this + 2114) == nullptr )  // this+2114（pAtkRateObj） 为空
            {
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 16;  // 异常展开状态号 → 16
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C11 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchBlackCatCast1.ani", 1);
                else
                  pThis_6C11 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchBlackCatCast1.ani", 1);
              }
              else
              {
                pThis_6C11 = nullptr;  // pThis_6C11 置空
              }
              *(this + 2114) = pThis_6C11;  // 写 this+2114（pAtkRateObj） = pThis_6C11
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 17;  // 异常展开状态号 → 17
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C12 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchBlackCatCast2.ani", 1);
                else
                  pThis_6C12 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchBlackCatCast2.ani", 1);
              }
              else
              {
                pThis_6C12 = nullptr;  // pThis_6C12 置空
              }
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              *(this + 2115) = pThis_6C12;  // 写 this+2115（f_AtkRate） = pThis_6C12
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              1,  // 第 2 个实参
              *(this + 2114),  // 第 3 个实参
              0,  // 第 4 个实参
              0,  // 第 5 个实参
              0,  // 第 6 个实参
              0);  // 第 7 个实参
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              1,  // 第 2 个实参
              *(this + 2115),  // 第 3 个实参
              0,  // 第 4 个实参
              0,  // 第 5 个实参
              0,  // 第 6 个实参
              0);  // 第 7 个实参
            sub_5DADE0("R_WZ_LAUNCH_PLUTO_READY");  // 死亡/移除锚定
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 26 = Void（虚空）：Particle/Void.ptl + R_WZ_VOID 播报 ──
        case 26:  // 【case 26】分型分支
          nVariantSel_12 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_12 != 0 )  // fld_e19528 不等于 0
          {
            if ( nVariantSel_12 == 1 )  // fld_e19528 等于 1
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 26);  // vt[290]（+1160）取动画资源
                v179 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 26);  // vt[285]（+1140）取技能值
                v180 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/Void.ptl");  // vt[147]（+588）取资源
                v298 = (uint16_t)pArg3;  // 类型转换 pArg3 → v298
                fld_e99 = v180;  // fld_e99 复制自 v180
                v293 = sub_47EF20(3, v179, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
                v181 = sub_47EF20(2, v179, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
                fld_e994 = fld_e99;  // fld_e994 复制自 fld_e99
                *(uint32_t *)(fld_e99 + 85) = sub_423A80(v181, v293, v298, 1000) + 300;
                ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(  // vt[145]（+580）发射 PO 对象
                  this,  // 第 1 个实参 this
                  23012,  // 第 2 个实参
                  v179,  // 第 3 个实参
                  fld_e994,  // 第 4 个实参
                  0,  // 第 5 个实参
                  38,  // 第 6 个实参
                  0,  // 第 7 个实参
                  62,  // 第 8 个实参
                  4,  // 第 9 个实参
                  0,  // 第 10 个实参
                  2,  // 第 11 个实参
                  &pArg3);  // 第 12 个实参
              }
              sub_5DBBD0("R_WZ_VOID", 500);  // 延时播报登记
            }
          }
          else
          {
            sub_5DADE0("R_WZ_VOID_READY");  // 死亡/移除锚定
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 27 = HalloweenBuster（万圣节爆弹）：R_WZ_SHOOTING_STAR 播报 ──
        case 27:  // 【case 27】分型分支
          nVariantSel_13 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_13 != 0 )  // fld_e19529 不等于 0
          {
            if ( nVariantSel_13 == 1 )  // fld_e19529 等于 1
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 27);  // vt[290]（+1160）取动画资源
                pArg4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 27);  // vt[285]（+1140）取技能值
                v183 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/HalloweenBuster.ptl");  // vt[147]（+588）取资源
                v184 = sub_47E9D0(1);  // 存 取 this+103/104 的 14 字节条目表中第 uArg2 条的 clong 值； 越界则退回 sub_461750
                v185 = (int)*this;  // 取虚表指针
                v334 = v184;  // v334 复制自 v184
                v186 = v184 - *(uint32_t *)(v183 + 15);
                fld_e99 = -*(uint32_t *)(v183 + 31);
                if ( (*(int (/*thiscall*/ **)(uint32_t **))(v185 + 152))(this) != 0 )
                  v187 = v334 + ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this);  // vt[30]（+120）取帧时长
                else
                  v187 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v334;  // vt[30]（+120）取帧时长
                v335 = v187;  // v335 复制自 v187
                if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 0 )  // vt[38]（+152）取动作件
                  LODWORD(v188) = v186 + ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this);  // vt[30]（+120）取帧时长
                else
                  LODWORD(v188) = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v186;  // vt[30]（+120）取帧时长
                v189 = (int)*this;  // 取虚表指针
                *(float *)&nArg5 = v188;
                v190 = (*(int (/*thiscall*/ **)(uint32_t **, int, int, int, int *))(v189 + 152))(this, 200, 4, 2, &pArg3);
                v191 = ((int (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[31])(this, 23013, pArg4, v183, v190);  // vt[31]（+124）取帧时长(累加)
                v192 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[32])(this, v335, v191);  // vt[32]（+128）取帧数
                v193 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, fld_e99 + v192);  // vt[31]（+124）取帧时长(累加)
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v189 + 584))(this, nArg5, v193);  // 经 v189 的虚表 +584 调用
              }
              sub_5DBBD0("R_WZ_SHOOTING_STAR", 700);  // 延时播报登记
            }
          }
          else
          {
            sub_5DADE0("R_WZ_SHOOTING_STAR_READY");  // 死亡/移除锚定
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 28 = Disenchant（驱散）：DisenchantCast2.ani + DisenchantArea1-4.ani 序列 + WZ_DISENCHANT ──
        case 28:  // 【case 28】分型分支
          nVariantSel_ = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_ != 0 )  // fld_e195210 不等于 0
          {
            if ( nVariantSel_ == 1 )  // fld_e195210 等于 1
            {
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 19;  // 异常展开状态号 → 19
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  LOBYTE(fld_e914) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
                else
                  fld_e914 = (int)*(this + 91);  // 读 this+91（0x16C）= pSceneAnimPool
                v200 = sub_431920(fld_e914, (char)"Effect/Animation/DisenchantCast2.ani", 1);  // 存 建动画件 Effect/Animation/DisenchantCast2.ani
              }
              else
              {
                v200 = 0;  // 局部 v200 → 0
              }
              fld_e99 = sub_44B6C0(284);  // 存 CRT 一次性池初始化 2
              LOBYTE(v329) = 20;  // 异常展开状态号 → 20
              v201 = fld_e99 != 0 ? (int *)sub_44E1F0(v200, 1) : nullptr;
              fld_e293 = (int)*(this + 29);  // 读 this+29（0x74）= nReadSlot74
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              sub_45FE80(fld_e293, (int)v201, 2, 0, (int)v201, (int)this, 0);  // 注册场景对象
              v203 = *v201;  // 取 v201 的首字段
              v306 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);  // vt[38]（+152）取动作件
              (*(void (/*thiscall*/ **)(int *))(v203 + 148))(v201);  // 经 v203 的虚表 +148 调用
              v204 = *v201;  // 取 v201 的首字段
              v205 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);  // vt[32]（+128）取帧数
              v206 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v205);  // vt[31]（+124）取帧时长(累加)
              v207 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v206);  // vt[30]（+120）取帧时长
              (*(void (/*thiscall*/ **)(int *, int))(v204 + 112))(v201, v207);  // 经 v204 的虚表 +112 调用
              v208 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[285])(this);  // vt[285]（+1140）取技能值
              ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int))(*this)[290])(this, 28, 0, v208);  // vt[290]（+1160）取动画资源
              v209 = (double)(int)sub_47EF20(28, -1, -1, 11, v306);
              nArg52 = 0;  // 局部 nArg52 → 0
              do
              {
                nArg5 = nArg52 + 1;
                sprintf(Buffer, "Effect/Animation/DisenchantArea%d.ani", nArg52 + 1);
                fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                LOBYTE(v329) = 21;  // 异常展开状态号 → 21
                if ( fld_e99 != 0 )  // fld_e99 不等于 0
                {
                  if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                    LOBYTE(fld_e915) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
                  else
                    fld_e915 = (int)*(this + 91);  // 读 this+91（0x16C）= pSceneAnimPool
                  v212 = sub_431920(fld_e915, (char)Buffer, 1);  // 存 建动画件
                }
                else
                {
                  v212 = 0;  // 局部 v212 → 0
                }
                LOBYTE(v329) = 0;  // 异常展开状态号 → 0
                v337 = v209 * 0.0018867925;
                sub_4922F0(v337);  // 全帧缩放与盒缩放统一乘算
                fld_e99 = sub_44B6C0(284);  // 存 CRT 一次性池初始化 2
                LOBYTE(v329) = 22;  // 异常展开状态号 → 22
                if ( fld_e99 != 0 )  // fld_e99 不等于 0
                  v213 = (int *)sub_44E1F0(v212, 1);  // 存 CNRDPooledObject
                else
                  v213 = nullptr;  // v213 置空
                v214 = *v213;  // 取 v213 的首字段
                LOBYTE(v329) = 0;  // 异常展开状态号 → 0
                *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v214 + 36))(v213) + 8) = 2;
                sub_45FE80((int)*(this + 29), (int)v213, 2, 0, (int)v213, 0, 0);  // 注册场景对象
                v215 = *v213;  // 取 v213 的首字段
                v216 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);  // vt[38]（+152）取动作件
                (*(void (/*thiscall*/ **)(int *, int))(v215 + 148))(v213, v216);  // 经 v215 的虚表 +148 调用
                v217 = *v213;  // 取 v213 的首字段
                v218 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);  // vt[32]（+128）取帧数
                v219 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v218);  // vt[31]（+124）取帧时长(累加)
                v220 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v219);  // vt[30]（+120）取帧时长
                (*(void (/*thiscall*/ **)(int *, int))(v217 + 112))(v213, v220);  // 经 v217 的虚表 +112 调用
                nArg52 = nArg5;  // nArg52 复制自 nArg5
              }
              while ( nArg5 < 4 );
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
                ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this)[145])(  // vt[145]（+580）发射 PO 对象
                  this,  // 第 1 个实参 this
                  48015,  // 第 2 个实参
                  *(this + 1954),  // 第 3 个实参
                  0,  // 第 4 个实参
                  0,  // 第 5 个实参
                  0,  // 第 6 个实参
                  0,  // 第 7 个实参
                  0,  // 第 8 个实参
                  4,  // 第 9 个实参
                  0,  // 第 10 个实参
                  0,  // 第 11 个实参
                  0);  // 第 12 个实参
            }
          }
          else
          {
            pAnimObj = sub_42FC90(*(this + 30));  // 存 88B 元素计数
            sub_4AECE0(pAnimObj - 1);  // 【解读】 【推断】动画切换: sub_491C70
            if ( *(this + 2116) == nullptr )  // this+2116 为空
            {
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 18;  // 异常展开状态号 → 18
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C13 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/DisenchantCast1.ani", 1);
                else
                  pThis_6C13 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/DisenchantCast1.ani", 1);
              }
              else
              {
                pThis_6C13 = nullptr;  // pThis_6C13 置空
              }
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              *(this + 2116) = pThis_6C13;  // 写 this+2116 = pThis_6C13
            }
            fld_e2116 = (int)*(this + 2116);  // 读 this+2116（0x2110）
            v198 = 0;  // 局部 v198 → 0
            fld_e1664 = (int)*(this + 1664) * (int)*(this + 1955) / 1000 / sub_42FC90(fld_e2116);
            if ( sub_42FC90(fld_e2116) > 0 )
            {
              do
                *(uint32_t *)(sub_4924C0(v198++) + 48) = fld_e1664;
              while ( v198 < sub_42FC90(*(this + 2116)) );
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              1,  // 第 2 个实参
              *(this + 2116),  // 第 3 个实参
              0,  // 第 4 个实参
              0,  // 第 5 个实参
              0,  // 第 6 个实参
              0);  // 第 7 个实参
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
              this,  // 第 1 个实参 this
              "WZ_DISENCHANT",  // 第 2 个实参：串 WZ_DISENCHANT
              -1,  // 第 3 个实参
              0,  // 第 4 个实参
              0);  // 第 5 个实参
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
              this,  // 第 1 个实参 this
              "DISENCHANT",  // 第 2 个实参：串 DISENCHANT
              -1,  // 第 3 个实参
              0,  // 第 4 个实参
              0);  // 第 5 个实参
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 31 = SunBurst（阳光爆发）：SunBurstFloor1/2.ani + SunBurstCast1/2.ani 四动画件 + R_WZ_SUNBURST ──
        case 31:  // 【case 31】分型分支
          nVariantSel_2 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
          if ( nVariantSel_2 != 0 )  // fld_e195211 不等于 0
          {
            if ( nVariantSel_2 == 1 )  // fld_e195211 等于 1
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
              {
                v230 = (int)*this;  // 取虚表指针
                nPhaseArg = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t **, int, int *))(*this)[285])(  // vt[285]（+1140）取技能值
                         this,  // 第 1 个实参 this
                         31,  // 第 2 个实参
                         0,  // 第 3 个实参
                         0,  // 第 4 个实参
                         0,  // 第 5 个实参
                         0,  // 第 6 个实参
                         *(this + 40),  // 第 7 个实参
                         4,  // 第 8 个实参
                         this,  // 第 9 个实参
                         2,  // 第 10 个实参
                         &pArg3);  // 第 11 个实参
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v230 + 580))(this, 23015, nPhaseArg);  // 经 v230 的虚表 +580 调用
              }
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 26;  // 异常展开状态号 → 26
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  LOBYTE(fld_e916) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
                else
                  fld_e916 = (int)*(this + 91);  // 读 this+91（0x16C）= pSceneAnimPool
                v233 = sub_431920(fld_e916, (char)"Effect/Animation/SunBurstFloor2.ani", 1);  // 存 建动画件 Effect/Animation/SunBurstFloor2.ani
              }
              else
              {
                v233 = 0;  // 局部 v233 → 0
              }
              fld_e99 = sub_44B6C0(284);  // 存 CRT 一次性池初始化 2
              LOBYTE(v329) = 27;  // 异常展开状态号 → 27
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
                v234 = (int *)sub_44E1F0(v233, 1);  // 存 CNRDPooledObject
              else
                v234 = nullptr;  // v234 置空
              v235 = *v234;  // 取 v234 的首字段
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v235 + 36))(v234) + 8) = 2;
              sub_45FE80((int)*(this + 29), (int)v234, 2, 0, (int)v234, 0, 0);  // 注册场景对象
              v236 = *v234;  // 取 v234 的首字段
              v237 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);  // vt[32]（+128）取帧数
              v238 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v237);  // vt[31]（+124）取帧时长(累加)
              v239 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v238);  // vt[30]（+120）取帧时长
              (*(void (/*thiscall*/ **)(int *, int))(v236 + 112))(v234, v239);  // 经 v236 的虚表 +112 调用
              v240 = *v234;  // 取 v234 的首字段
              v241 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);  // vt[38]（+152）取动作件
              (*(void (/*thiscall*/ **)(int *, int))(v240 + 148))(v234, v241);  // 经 v240 的虚表 +148 调用
              sub_5DBBD0("R_WZ_SUNBURST", 400);  // 延时播报登记
            }
          }
          else
          {
            pThis_8452 = this + 2117;  // 取 this 偏移 2117 的指针
            if ( *(this + 2117) == nullptr )  // this+2117（pSkillObj） 为空
            {
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 23;  // 异常展开状态号 → 23
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C14 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstCast1.ani", 1);  // 存 建动画件 Effect/Animation/SunBurstCast1.ani
                else
                  pThis_6C14 = sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstCast1.ani", 1);  // 存 建动画件 Effect/Animation/SunBurstCast1.ani
              }
              else
              {
                pThis_6C14 = 0;  // 局部 pThis_6C14 → 0
              }
              *pThis_8452 = pThis_6C14;
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 24;  // 异常展开状态号 → 24
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C15 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstCast2.ani", 1);
                else
                  pThis_6C15 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstCast2.ani", 1);
              }
              else
              {
                pThis_6C15 = nullptr;  // pThis_6C15 置空
              }
              *(this + 2118) = pThis_6C15;  // 写 this+2118（nFinishFlag） = pThis_6C15
              fld_e99 = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
              LOBYTE(v329) = 25;  // 异常展开状态号 → 25
              if ( fld_e99 != 0 )  // fld_e99 不等于 0
              {
                if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
                  pThis_6C16 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstFloor1.ani", 1);
                else
                  pThis_6C16 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstFloor1.ani", 1);
              }
              else
              {
                pThis_6C16 = nullptr;  // pThis_6C16 置空
              }
              LOBYTE(v329) = 0;  // 异常展开状态号 → 0
              *(this + 2119) = pThis_6C16;  // 写 this+2119（bFinishFlag） = pThis_6C16
            }
            v226 = sub_42FC90(*pThis_8452);  // 存 88B 元素计数
            fld_e16642 = (uint32_t)*(this + 1664) * (uint32_t)*(this + 1955);
            pThis_8453 = this + 2117;  // 取 this 偏移 2117 的指针
            nArg5 = 3;  // 局部 nArg5 → 3
            pArg4 = fld_e16642 / 1000 / v226;
            do
            {
              for ( jj = 0; jj < sub_42FC90(*pThis_8453); ++jj )
              {
                v229 = sub_4924C0(jj);  // 存 按索引取帧并确保图像就绪
                *(uint32_t *)(v229 + 48) = pArg4;
              }
              fld_e21343 = nArg5 == 1;
              ++pThis_8453;  // pThis_8453 自增
              --nArg5;
            }
            while ( !fld_e21343 );
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              1,  // 第 2 个实参
              *(this + 2117),  // 第 3 个实参
              0,  // 第 4 个实参
              -(int)*(this + 40),  // 第 5 个实参
              0,  // 第 6 个实参
              0);  // 第 7 个实参
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              2,  // 第 2 个实参
              *(this + 2118),  // 第 3 个实参
              0,  // 第 4 个实参
              -(int)*(this + 40),  // 第 5 个实参
              0,  // 第 6 个实参
              0);  // 第 7 个实参
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this)[51])(  // vt[51]（+204）挂动画件
              this,  // 第 1 个实参 this
              1,  // 第 2 个实参
              *(this + 2119),  // 第 3 个实参
              0,  // 第 4 个实参
              0,  // 第 5 个实参
              0,  // 第 6 个实参
              1);  // 第 7 个实参
            sub_5DADE0("R_WZ_SUNBURST_READY");  // 死亡/移除锚定
          }
          goto LABEL_509;  // 转到 LABEL_509
        //   案例 43 = 挑衅人形（ProvocationDoll.ptl）+ WZ_FOLLOW_ME_03 ──
        case 43:  // 【case 43】分型分支
          if ( *(this + 1952) != (uint32_t *)1 )
            return;
          if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
          {
            v242 = (int)*this;  // 取虚表指针
            v243 = ((int (/*thiscall*/ *)(uint32_t **, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this)[147])(  // vt[147]（+588）取资源
                     this,  // 第 1 个实参 this
                     "Particle/ProvocationDoll.ptl",  // 第 2 个实参：串 Particle/ProvocationDoll.ptl
                     0,  // 第 3 个实参
                     50,  // 第 4 个实参
                     0,  // 第 5 个实参
                     33,  // 第 6 个实参
                     4,  // 第 7 个实参
                     0,  // 第 8 个实参
                     0,  // 第 9 个实参
                     0);  // 第 10 个实参
            v244 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[285])(this, 43, v243);  // vt[285]（+1140）取技能值
            (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v242 + 580))(this, 23017, v244);  // 经 v242 的虚表 +580 调用
          }
LABEL_447:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
            this,  // 第 1 个实参 this
            "WZ_FOLLOW_ME_03",  // 第 2 个实参：串 WZ_FOLLOW_ME_03
            -1,  // 第 3 个实参
            0,  // 第 4 个实参
            0);  // 第 5 个实参
          goto LABEL_509;  // 转到 LABEL_509
        default:
          break;
      }
      // ── [段 21] 召唤兽分支（+1954 为 49/50 之外且过 sub_5DA9B0 表包含门）：sub_5E09B0 建召唤体 ──
      //   按 +1954 播 SUMMON_ADOR(21)/SUMMON_NIAS(22)/SUMMON_STALKER(23)/SUMMON_WISP(24)
      if ( nSubStateB_ != 49 )  // fld_e19542 不等于 49
      {
        if ( nSubStateB_ != 50 )  // fld_e19542 不等于 50
        {
          if ( (uint8_t)sub_5DA9B0(*(this + 1954)) != 0 )
          {
            nVariantSel_3 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
            if ( nVariantSel_3 != 0 )  // fld_e195212 不等于 0
            {
              if ( nVariantSel_3 == 1 )  // fld_e195212 等于 1
              {
                if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
                {
                  nSubStateB_2 = (int)*(this + 1954);  // 读 this+1954（0x1E88）= nSubStateB
                  v271 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[285])(this);  // vt[285]（+1140）取技能值
                  fld_e19548 = COERCE_FLOAT(((int (/*thiscall*/ *)(uint32_t **, uint32_t, int))(*this)[290])(this, *(this + 1954), v271));  // vt[290]（+1160）取动画资源
                  sub_5E09B0(fld_e19548, nSubStateB_2);  // 调: sub_5E09B0 sub_47E9D0 sub_5DD040 sub_47EF20 sub_422E70
                }
                nSubStateB_3 = (int)*(this + 1954);  // 读 this+1954（0x1E88）= nSubStateB
                switch ( nSubStateB_3 )  // switch(fld_e19549) 多路分派
                {
                  case 21:  // 【case 21】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "SUMMON_ADOR",  // 第 2 个实参：串 SUMMON_ADOR
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  case 22:  // 【case 22】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "SUMMON_NIAS",  // 第 2 个实参：串 SUMMON_NIAS
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  case 23:  // 【case 23】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "SUMMON_STALKER",  // 第 2 个实参：串 SUMMON_STALKER
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  case 24:  // 【case 24】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "SUMMON_WISP",  // 第 2 个实参：串 SUMMON_WISP
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  //   GBLN_INVOKE(25)/SANDOR_INVOKE(44)/AUXO_INVOKE(45)/LUIS_INVOKE(46) —— 对应召唤师各契约兽
                  case 25:  // 【case 25】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "GBLN_INVOKE",  // 第 2 个实参：串 GBLN_INVOKE
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  case 44:  // 【case 44】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "SANDOR_INVOKE",  // 第 2 个实参：串 SANDOR_INVOKE
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  case 45:  // 【case 45】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "AUXO_INVOKE",  // 第 2 个实参：串 AUXO_INVOKE
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  case 46:  // 【case 46】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "LUIS_INVOKE",  // 第 2 个实参：串 LUIS_INVOKE
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  case 47:  // 【case 47】分型分支
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                      this,  // 第 1 个实参 this
                      "ECHEVERRA_INVOKE",  // 第 2 个实参：串 ECHEVERRA_INVOKE
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    break;
                  default:
                    break;
                }
              }
            }
            else
            {
              switch ( v269 )  // switch(v269) 多路分派
              {
                case 21:  // 【case 21】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_SUMMON_ADOR",  // 第 2 个实参：串 WZ_SUMMON_ADOR
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                case 22:  // 【case 22】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_SUMMON_NIAS",  // 第 2 个实参：串 WZ_SUMMON_NIAS
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                case 23:  // 【case 23】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_SUMMON_STALKER",  // 第 2 个实参：串 WZ_SUMMON_STALKER
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                case 24:  // 【case 24】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_SUMMON_WISP",  // 第 2 个实参：串 WZ_SUMMON_WISP
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                case 25:  // 【case 25】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_INVOKE",  // 第 2 个实参：串 WZ_INVOKE
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                case 44:  // 【case 44】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_INVOKE_SANDOR",  // 第 2 个实参：串 WZ_INVOKE_SANDOR
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                case 45:  // 【case 45】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_INVOKE_AUXO",  // 第 2 个实参：串 WZ_INVOKE_AUXO
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                case 46:  // 【case 46】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_INVOKE_LUIS",  // 第 2 个实参：串 WZ_INVOKE_LUIS
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                case 47:  // 【case 47】分型分支
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
                    this,  // 第 1 个实参 this
                    "WZ_INVOKE_ECHEVERRA",  // 第 2 个实参：串 WZ_INVOKE_ECHEVERRA
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  break;
                default:
                  break;
              }
            }
          }
          goto LABEL_509;  // 转到 LABEL_509
        }
        nVariantSel_4 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
        if ( nVariantSel_4 != 0 )  // fld_e195213 不等于 0
        {
          if ( nVariantSel_4 == 1 && ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // vt[77]（+308）标志查询
          {
            v266 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/TargetItBall.ptl");  // vt[147]（+588）取资源
            v267 = ((int (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[285])(this, 50, -1, -1, 11);  // vt[285]（+1140）取技能值
            ((void (/*thiscall*/ *)(uint32_t **, int, int, int))(*this)[290])(this, 50, 5, v267);  // vt[290]（+1160）取动画资源
            v268 = sub_47EF20(v309, v310, v311, v312, v313);  // 存 技能数值查表：this+107/108 的 16 字节条目
            v313 = 0;  // 局部 v313 → 0
            v312 = 0;  // 局部 v312 → 0
            *(uint32_t *)(v266 + 85) = v268;
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, uint32_t, int, uint32_t))(*this)[145])(  // vt[145]（+580）发射 PO 对象
              this,  // 第 1 个实参 this
              23018,  // 第 2 个实参
              0,  // 第 3 个实参
              v266,  // 第 4 个实参
              0,  // 第 5 个实参
              44,  // 第 6 个实参
              0);  // 第 7 个实参
          }
          goto LABEL_509;  // 转到 LABEL_509
        }
        goto LABEL_447;  // 转到 LABEL_447
      }
      v245 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 49);  // vt[290]（+1160）取动画资源
      v246 = (int)*this;  // 取虚表指针
      fld_e99 = v245;  // fld_e99 复制自 v245
      *(float *)&nArg5 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t **, int))(v246 + 1140))(this, 49));
      nVariantSel_5 = (int)*(this + 1952);  // 读 this+1952（0x1E80）= nSubStateA
      if ( nVariantSel_5 == 0 )  // fld_e195214 等于 0
      {
        pThis_8482 = this + 2120;  // 取 this 偏移 2120 的指针
        if ( *(this + 2120) == nullptr )  // this+2120（pAtkObj） 为空
        {
          nBigState = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
          LOBYTE(v329) = 28;  // 异常展开状态号 → 28
          if ( nBigState != 0 )  // fld_e1639 不等于 0
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
              pThis_6C17 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SacrificeSpirit1.ani", 1);  // 存 建动画件 Effect/Animation/SacrificeSpirit1.ani
            else
              pThis_6C17 = sub_431920((char)*(this + 91), (char)"Effect/Animation/SacrificeSpirit1.ani", 1);  // 存 建动画件 Effect/Animation/SacrificeSpirit1.ani
          }
          else
          {
            pThis_6C17 = 0;  // 局部 pThis_6C17 → 0
          }
          *pThis_8482 = pThis_6C17;
          nBigState = sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
          LOBYTE(v329) = 29;  // 异常展开状态号 → 29
          if ( nBigState != 0 )  // fld_e1639 不等于 0
          {
            if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 长度 < 0x10（短串内联判定）
              pThis_6C18 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SacrificeSpirit2.ani", 1);
            else
              pThis_6C18 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SacrificeSpirit2.ani", 1);
          }
          else
          {
            pThis_6C18 = nullptr;  // pThis_6C18 置空
          }
          LOBYTE(v329) = 0;  // 异常展开状态号 → 0
          *(this + 2121) = pThis_6C18;  // 写 this+2121 = pThis_6C18
        }
        v339 = 2;  // 局部 v339 → 2
        v251 = (double)(int)sub_47EF20(0, nArg5, -1, -1, 11) * 0.0071428572;
        *(float *)&nArg5 = v251 / *((float *)this + 2122);
        *((float *)this + 2122) = v251;
        do
        {
          sub_4922F0(*(float *)&nArg5);  // 全帧缩放与盒缩放统一乘算
          pArg4 = (int)*this;  // 取虚表指针
          v252 = sub_47E9D0(0);  // 存 取 this+103/104 的 14 字节条目表中第 uArg2 条的 clong 值； 越界则退回 sub_461750
          (*(void (/*thiscall*/ **)(uint32_t **, int, uint32_t, int, uint32_t, uint32_t, int))(pArg4 + 204))(
            this,  // 第 1 个实参 this
            1,  // 第 2 个实参
            *pThis_8482++,  // 第 3 个实参
            v252,  // 第 4 个实参
            0,  // 第 5 个实参
            0,  // 第 6 个实参
            1);  // 第 7 个实参
          --v339;
        }
        while ( v339 != 0 );
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
          this,  // 第 1 个实参 this
          "R_WZ_SACRIFICE_SPIRIT",  // 第 2 个实参：串 R_WZ_SACRIFICE_SPIRIT
          -1,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
        goto LABEL_509;  // 转到 LABEL_509
      }
      if ( nVariantSel_5 != 1 )  // fld_e195214 不等于 1
        goto LABEL_509;  // 转到 LABEL_509
      v253 = sub_47EF20(0, nArg5, -1, -1, 11);  // 存 技能数值查表：this+107/108 的 16 字节条目
      v254 = (int)*this;  // 取虚表指针
      LODWORD(v323) = v253 / 2;
      if ( (*(int (/*thiscall*/ **)(uint32_t **))(v254 + 152))(this) == 1 )
      {
        v255 = sub_47E9D0(0);  // 存 取 this+103/104 的 14 字节条目表中第 uArg2 条的 clong 值； 越界则退回 sub_461750
        pArg4 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + v255;  // vt[30]（+120）取帧时长
      }
      else
      {
        v256 = sub_47E9D0(0);  // 存 取 this+103/104 的 14 字节条目表中第 uArg2 条的 clong 值； 越界则退回 sub_461750
        pArg4 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v256;  // vt[30]（+120）取帧时长
      }
      fld_e99 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);  // vt[31]（+124）取帧时长(累加)
      v313 = 0;  // 局部 v313 → 0
      v314 = 0;  // 局部 v314 → 0
      v315 = 0;  // 局部 v315 → 0
      v317 = 0;  // 局部 v317 → 0
      v318 = 0;  // 局部 v318 → 0
      v319 = 0;  // 局部 v319 → 0
      fld_e294 = (int)*(this + 29);  // 读 this+29（0x74）= nReadSlot74
      LOBYTE(v329) = 31;  // 异常展开状态号 → 31
      v340 = 0;  // 局部 v340 → 0
      if ( sub_425100(fld_e294) > 0 )
      {
        do
        {
          v258 = (uint32_t *)sub_425A00(v340);
          v259 = *v258;  // 取 v258 的首字段
          nBigState = (int)v258;  // 类型转换 v258 → fld_e1639
          v299 = (*(int (/*thiscall*/ **)(uint32_t *))(v259 + 124))(v258);
          v260 = (*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 120))(v258);
          v261 = sub_499240(pArg4, fld_e99, v260, v299, 0);  // 存 像素距离
          if ( v261 <= SLODWORD(v323) )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v258 + 40))(v258, 529) == 0 )
              goto LABEL_437;  // 转到 LABEL_437
            v262 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 340))(v258);
            v263 = &dword_738020;
            while ( v262 != *v263 )
            {
              if ( (int)++v263 >= (int)&dword_738030 )
                goto LABEL_437;  // 转到 LABEL_437
            }
            if ( (uint32_t **)v258[2088] == this )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v258 + 308))(v258) == 0 )
                goto LABEL_440;  // 转到 LABEL_440
            }
            else
            {
// ── [段 22] LABEL_437/LABEL_440：★ 献祭目标存活判定子循环（遍历场景对象表，条件位测试 17 + 关系码比对） ──
LABEL_437:
              v264 = (*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 376))(v258);
              if ( v264 != ((int (/*thiscall*/ *)(uint32_t **))(*this)[94])(this)  // vt[94]（+376）取资源
                || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v258 + 40))(v258, 17) == 0 )  // 第 1 个实参 this
              {
                goto LABEL_440;  // 转到 LABEL_440
              }
            }
            sub_428430(&nBigState);  // STL 内联 vector push_back
          }
// ── [段 23] LABEL_440 收尾：播 SPIRIT_SACRIFICE（灵魂献祭）并清理临时缓冲 ──
LABEL_440:
          ++v340;  // v340 自增
        }
        while ( v340 < sub_425100(*(this + 29)) );
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
        this,  // 第 1 个实参 this
        "SPIRIT_SACRIFICE",  // 第 2 个实参：串 SPIRIT_SACRIFICE
        -1,  // 第 3 个实参
        0,  // 第 4 个实参
        0);  // 第 5 个实参
      sub_5E5260(v316);  // 调: sub_5E5260
      LOBYTE(v329) = 0;  // 异常展开状态号 → 0
      sub_5E5260(&v312);  // 调: sub_5E5260
// ── [段 24] ★ LABEL_509 公共尾：+1952==1 且两标志齐备时施加 双段位移 + 末段动作 + 方位/速率复位 ──
//   vt+219 双段位移(±2147)——vt+38 取关系码、sub_432E50 对调、vt+224 施加末段动作
LABEL_509:
      if ( *(this + 1952) == (uint32_t *)1 && *((uint8_t *)this + 8584) != 0 && *((uint8_t *)this + 8585) != 0 )
      {
        fld_e21473 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          fld_e21473,  // 第 3 个实参
          fld_e21473,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(  // vt[219]（+876）位移/动作下发
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        v278 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);  // vt[38]（+152）取动作件
        if ( (int)*(this + 2147) < 0 )
          v278 = sub_432E50(v278);  // 存 关系码对调映射 【关系码对调映射】0 与 1 互换与 2 与 3 互换，其余返回 4
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v278, 4);  // vt[224]（+896）帧组设置
        sub_495890(2, 0);  // 模式选择式方位设置
        v308 = (float)SLODWORD(v321);
        sub_494F20(2, v308);  // 属性浮点槽写入
      }
      return;
    // ── [段 25] case 11：DASH_LOOP 播报 → LABEL_156 → sub_5DACE0（数据表 + 变速换锚 AI） ──
    case 11:  // 【case 11】分型分支
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "DASH_LOOP", 9, 0, 0);  // vt[53]（+212）播放动作/播报：标签 DASH_LOOP
LABEL_156:
      if ( *(this + 2142) != (uint32_t *)-1 )
        sub_5DACE0(this);  // 换锚重定
      return;
    // ── [段 26] case 12：清两标志 + vt+1172 取动作数据 + sub_406D60 赋值（收招） ──
    case 12:  // 【case 12】分型分支
      v121 = (int)*this;  // 取虚表指针
      *((uint8_t *)this + 8228) = 0;  // this 字节 +8228 置 0
      *((uint8_t *)this + 8220) = 0;  // this 字节 +8220 置 0
      v122 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v121 + 1172))(this, 1);
      sub_406D60(v122);  // std::string 从 C 串赋值
      return;
    // ── [段 27] case 14：★ 形态/技能播报小表 —— 按 this+1991 索引播 WZ_ 系语音 ──
    //   176 WZ_ANCIENT_MEMORY / 175 WZ_LEAP / 180 WZ_UNYIELD_WILL / 30 R_WZ_FOLLOW_ME / 29 WZ_ELEMENTAL_BURN
    case 14:  // 【case 14】分型分支
      nSkillNo = (int)*(this + 1991);  // 读 this+1991（0x1F1C）= nSkillNo
      switch ( nSkillNo )  // switch(fld_e1991) 多路分派
      {
        case 176:  // 【case 176】分型分支
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_ANCIENT_MEMORY", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 WZ_ANCIENT_MEMORY
          break;
        case 175:  // 【case 175】分型分支
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_LEAP", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 WZ_LEAP
          break;
        case 180:  // 【case 180】分型分支
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_UNYIELD_WILL", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 WZ_UNYIELD_WILL
          break;
        case 30:  // 【case 30】分型分支
          v280 = *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 4);
          *((uint8_t *)this + 8368) = v280 == 0;
          *((uint8_t *)this + 8376) = 0;  // this 字节 +8376 置 0
          if ( v280 != 0 )  // v280 不等于 0
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
              this,  // 第 1 个实参 this
              "R_WZ_FOLLOW_ME",  // 第 2 个实参：串 R_WZ_FOLLOW_ME
              -1,  // 第 3 个实参
              0,  // 第 4 个实参
              0);  // 第 5 个实参
          break;
        case 29:  // 【case 29】分型分支
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_ELEMENTAL_BURN", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 WZ_ELEMENTAL_BURN
          break;
        //   41 WZ_ANCIENT_LIBRARY / 37 WZ_SHIELD / 2 WZ_SHOWTIME / 40 WZ_AUTO_CHASER
        case 41:  // 【case 41】分型分支
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
            this,  // 第 1 个实参 this
            "WZ_ANCIENT_LIBRARY",  // 第 2 个实参：串 WZ_ANCIENT_LIBRARY
            -1,  // 第 3 个实参
            0,  // 第 4 个实参
            0);  // 第 5 个实参
          break;
        case 37:  // 【case 37】分型分支
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_SHIELD", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 WZ_SHIELD
          break;
        case 2:  // 【case 2】分型分支
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(  // vt[53]（+212）播放动作/播报
            this,  // 第 1 个实参 this
            "WZ_SHOWTIME",  // 第 2 个实参：串 WZ_SHOWTIME
            -1,  // 第 3 个实参
            0,  // 第 4 个实参
            0);  // 第 5 个实参
          break;
        case 40:  // 【case 40】分型分支
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_AUTO_CHASER", -1, 0, 0);  // vt[53]（+212）播放动作/播报：标签 WZ_AUTO_CHASER
          break;
        default:
          break;
      }
      return;
    // ── [段 28] default：无操作返回（非法状态号静默） ──
    default:
      return;
  }
}

