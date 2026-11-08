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
  int fld_e1954; // eax
  int fld_e2109; // eax
  uint32_t *pThis_842; // edi
  int i; // ebx
  uint32_t *pThis_845; // edi
  int j; // ebx
  uint32_t *pThis_848; // edi
  int k; // ebx
  int v15; // edx
  int fld_e2142; // eax
  int v17; // eax
  int pArg32; // ecx
  int v19; // edi
  int v20; // eax
  int fld_e91; // ecx
  int v22; // edi
  int *v23; // edi
  int fld_e29; // ecx
  int v25; // ebx
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int fld_e912; // ecx
  int v30; // edi
  int *v31; // edi
  int fld_e292; // ecx
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
  int *fld_e1625; // ecx
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
  int fld_e2128; // eax
  void *v77; // eax
  uint32_t *pThis_6C3; // eax
  int v79; // edx
  char *v80; // edi
  int fld_e2129; // ebx
  int fld_e21292; // eax
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
  int fld_e2133; // ecx
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
  int fld_e21332; // eax
  uint32_t *pThis_6C5; // eax
  uint32_t *pThis_838; // edi
  int n; // ebx
  int v114; // eax
  int fld_e2136; // ecx
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
  int fld_e1952; // eax
  int v129; // eax
  int pThis_9; // eax
  int v131; // eax
  int fld_e2058; // ecx
  int fld_e21442; // eax
  bool v134; // al
  int fld_e2144; // edi
  uint32_t *pThis_6C6; // eax
  uint32_t *fld_e913; // eax
  uint32_t *pThis_8382; // edi
  int ii; // ebx
  int fld_e19542; // edx
  int fld_e19522; // eax
  int fld_e19523; // eax
  uint32_t *v143; // edi
  int v144; // eax
  int v145; // eax
  int v146; // edx
  int v147; // eax
  int v148; // ebx
  int v149; // eax
  int v150; // eax
  int v151; // ecx
  int fld_e19524; // eax
  char pThis_2188; // al
  int v154; // ebx
  int v155; // edi
  int v156; // eax
  int v157; // edx
  int fld_e19525; // eax
  uint32_t *pThis_6C9; // eax
  int v160; // eax
  int v161; // ebx
  int v162; // eax
  int v163; // eax
  int v164; // eax
  int fld_e19526; // eax
  uint32_t *pThis_6C10; // eax
  int fld_e19545; // eax
  int v168; // edx
  int fld_e19546; // ebx
  int v170; // edi
  int v171; // eax
  int v172; // eax
  int fld_e19527; // eax
  uint32_t *pThis_6C11; // eax
  uint32_t *pThis_6C12; // eax
  int v176; // edi
  int v177; // eax
  int fld_e19528; // eax
  int v179; // edi
  int v180; // eax
  int v181; // eax
  int fld_e19529; // eax
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
  int fld_e195210; // eax
  int fld_e30; // eax
  uint32_t *pThis_6C13; // eax
  int fld_e2116; // ebx
  int v198; // edi
  int fld_e914; // edx
  int v200; // edi
  int *v201; // edi
  int fld_e293; // ecx
  int v203; // ebx
  int v204; // ebx
  int v205; // eax
  int v206; // eax
  int v207; // eax
  int v208; // eax
  double v209; // st7
  int nArg52; // eax
  int fld_e915; // ecx
  int v212; // edi
  int *v213; // edi
  int v214; // edx
  int v215; // ebx
  int v216; // eax
  int v217; // ebx
  int v218; // eax
  int v219; // eax
  int v220; // eax
  int fld_e195211; // eax
  uint32_t *pThis_8452; // edi
  int pThis_6C14; // eax
  uint32_t *pThis_6C15; // eax
  uint32_t *pThis_6C16; // eax
  int v226; // eax
  int fld_e16642; // ecx
  int jj; // edi
  int v229; // eax
  int v230; // edi
  int fld_e40; // eax
  int fld_e916; // ecx
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
  int fld_e195214; // eax
  uint32_t *pThis_8482; // edi
  int pThis_6C17; // eax
  uint32_t *pThis_6C18; // eax
  double v251; // st7
  int v252; // eax
  int v253; // eax
  int v254; // edx
  int v255; // ebx
  int v256; // ebx
  int fld_e294; // ecx
  uint32_t *v258; // edi
  int v259; // edx
  int v260; // eax
  int v261; // eax
  int v262; // ecx
  int *v263; // eax
  int v264; // ebx
  int fld_e195213; // eax
  int v266; // edi
  int v267; // eax
  int v268; // eax
  int v269; // edx
  int fld_e195212; // eax
  int v271; // eax
  float fld_e19548; // eax
  int fld_e19549; // eax
  uint32_t *pThis_6C7; // eax
  uint32_t *pThis_6C8; // eax
  int64_t fld_e19544; // rax
  int fld_e19543; // eax
  int v278; // eax
  int fld_e1991; // eax
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
  int fld_e21422; // [esp+D8h] [ebp-180h]
  int v305; // [esp+D8h] [ebp-180h]
  int v306; // [esp+D8h] [ebp-180h]
  int fld_e19547; // [esp+D8h] [ebp-180h]
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
  int fld_e1639; // [esp+120h] [ebp-138h] BYREF
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
  dword_796E502 = dword_796E50;
  fld_e1639 = (int)*(this + 1639);
  v327 = 15;
  v326 = 0;
  Buffer[260] = 0;
  nArg22 = nArg2;
  v329 = 0;
  // ── [段 2] 第一重 switch(fld_e1639)：★ 收招/收尾分支——把已建好的动画件回挂到角色身上 ──
  //   case 10/18/19/20/21 各自取缓存的动画指针 → LABEL_51 经 vt+208 挂载
  switch ( fld_e1639 )
  {
    // ── [段 3] case 10（施法/投掷态收尾）：按 this+1954 子类型逐个回挂缓存的投掷动画 ──
    //   this+1952=左右手/分型，+2106..+2120 是 case 10 主体预先建好的动画件槽
    case 10:
      if ( *(this + 1953) == nullptr )
      {
        if ( *(this + 1957) == nullptr && *(this + 1954) == (uint32_t *)11 )
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + (uint32_t)*(this + 1952) + 2106));
        fld_e1954 = (int)*(this + 1954);
        switch ( fld_e1954 )
        {
          case 5:
          case 6:
          case 7:
          case 9:
          case 8:
            v15 = (int)*this;
            if ( *(this + 1952) != nullptr )
              fld_e2109 = (int)*(this + 2109);
            else
              fld_e2109 = (int)*(this + 2108);
            goto LABEL_51;
          case 16:
            if ( nArg2 != 10 )
            {
              fld_e2109 = (int)*(this + 2112);
              goto LABEL_50;
            }
            break;
          case 17:
            if ( *(this + 1952) == (uint32_t *)1 )
            {
              fld_e2109 = (int)*(this + 2113);
              goto LABEL_50;
            }
            break;
          case 18:
            if ( *(this + 1952) == nullptr )
            {
              pThis_842 = this + 2114;
              for ( i = 2; i != 0; --i )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *pThis_842++);
              nArg22 = nArg2;
            }
            break;
          case 28:
            if ( *(this + 1952) == nullptr )
            {
              fld_e2109 = (int)*(this + 2116);
              goto LABEL_50;
            }
            break;
          case 31:
            if ( *(this + 1952) == nullptr )
            {
              pThis_845 = this + 2117;
              for ( j = 3; j != 0; --j )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *pThis_845++);
              nArg22 = nArg2;
            }
            break;
          case 15:
            if ( nArg2 != 10 )
              ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t))(*this)[68])(this, 0, 0);
            break;
          default:
            if ( fld_e1954 == 49 && nArg2 != 10 )
            {
              pThis_848 = this + 2120;
              for ( k = 2; k != 0; --k )
                ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *pThis_848++);
              nArg22 = nArg2;
            }
            break;
        }
      }
      break;
    // ── [段 4] case 18/19/20 收尾：18 回挂 +2102/+2103 双动画（须 +2100==4） ──
    //   19 回挂 +2125；20 回挂 +2131（须 +2129==20）—— 三者终点都是 LABEL_50 → LABEL_51 vt+208 挂载
    case 18:
      if ( *(this + 2100) == (uint32_t *)4 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + 2102));
        fld_e2109 = (int)*(this + 2103);
        goto LABEL_50;
      }
      break;
    case 19:
      fld_e2109 = (int)*(this + 2125);
      goto LABEL_50;
    case 20:
      if ( *(this + 2129) == (uint32_t *)20 )
      {
        fld_e2109 = (int)*(this + 2131);
LABEL_50:
        v15 = (int)*this;
LABEL_51:
        (*(void (/*stdcall*/ **)(int))(v15 + 208))(fld_e2109);
      }
      break;
    // ── [段 5] case 21 收尾：+2136 回挂 + 无 +2133 时补起魔能充能（sub_4BA730） ──
    case 21:
      if ( nArg2 != 21 )
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, *(this + 2136));
      if ( *(this + 2133) == nullptr )
        sub_4BA730(2, 4, 0, 0);
      break;
    default:
      break;
  }
  // ── [段 6] 大状态 15 归一：nArg22 与 nArg2 都改写为 8、fld_e1639 改写 15（形态切换别名） ──
  if ( nArg22 == 15 )
  {
    nArg22 = 8;
    nArg2 = 8;
    fld_e1639 = 15;
  }
  // ── [段 7] 魔能充能收尾：+2142 表参非 -1 且非 0/11 态时，按 sub_5DA1E0 组号驱动 ENERGY_CHARGE 收束 ──
  //   sub_4BA730(2, 组号, 0, 0) 起充能；vt+63 两路清参后 +2142 复位为 -1
  fld_e2142 = (int)*(this + 2142);
  if ( fld_e2142 != -1 && nArg22 != 0 && nArg22 != 11 )
  {
    if ( fld_e2142 >= 55 )
      v17 = 4;
    else
      v17 = dword_738048[fld_e2142];
    sub_4BA730(2, v17, 0, 0);
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, int))(*this)[63])(this, 0, -1);
    ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[63])(this, 1, -1);
    *(this + 2142) = (uint32_t *)-1;
  }
  pArg32 = pArg3;
  // ── [段 8] 第二重 switch(nArg22)：★ 施法/技能演出分型主表（16/17/18/19/20/21/26/27/28/31/43） ──
  //   每 case 骨架：门控 +1952（左右/分型）与 +195x 表参 → 建动画件 → 注册场景 → 播语音
  switch ( nArg22 )
  {
    // ── [段 9] case 16：WZ_DASH_FALL（冲刺坠落）—— 仅播报，无动画件 ──
    case 16:
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 1554));
      ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 1, 1, 1000, 1000);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, int, int, uint32_t, int, int))(*this)[219])(this, 0, 250, 250, 0, -480, 1);
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      v19 = (int)*this;
      v20 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[38])(this, 4);
      (*(void (/*thiscall*/ **)(uint32_t **, int))(v19 + 896))(this, v20);
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_DASH_FALL", -1, 0, 0);
      break;
    // ── [段 10] case 17：★ 相位穿梭（WarpCloud.ani）—— 存 pArg3 的坐标/资源到 this+2099 ──
    //   sub_431920 建动画件 → sub_44E1F0 池化壳 → sub_45FE80 注册场景对象表
    case 17:
      fld_e99 = sub_42FCB0(228);
      LOBYTE(v329) = 1;
      if ( fld_e99 != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(fld_e91) = (uint8_t)this + 108;
        else
          fld_e91 = (int)*(this + 91);
        v22 = sub_431920(fld_e91, (char)"Effect/Animation/WarpCloud.ani", 1);
      }
      else
      {
        v22 = 0;
      }
      fld_e99 = sub_44B6C0(284);
      LOBYTE(v329) = 2;
      if ( fld_e99 != 0 )
        v23 = (int *)sub_44E1F0(v22, 1);
      else
        v23 = nullptr;
      fld_e29 = (int)*(this + 29);
      LOBYTE(v329) = 0;
      sub_45FE80(fld_e29, (int)v23, 2, 0, (int)v23, 0, 0);
      v25 = *v23;
      v26 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
      v27 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v26);
      v28 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v27 + 1);
      (*(void (/*thiscall*/ **)(int *, int))(v25 + 112))(v23, v28);
      if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this)[145])(
          this,
          23001,
          *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 20),
          0,
          0,
          0,
          0,
          50,
          4,
          0,
          0,
          0);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t))(*this)[28])(
        this,
        *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4),
        *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8),
        0);
      fld_e99 = sub_42FCB0(228);
      LOBYTE(v329) = 3;
      if ( fld_e99 != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(fld_e912) = (uint8_t)this + 108;
        else
          fld_e912 = (int)*(this + 91);
        v30 = sub_431920(fld_e912, (char)"Effect/Animation/WarpCloud.ani", 1);
      }
      else
      {
        v30 = 0;
      }
      fld_e99 = sub_44B6C0(284);
      LOBYTE(v329) = 4;
      if ( fld_e99 != 0 )
        v31 = (int *)sub_44E1F0(v30, 1);
      else
        v31 = nullptr;
      fld_e292 = (int)*(this + 29);
      LOBYTE(v329) = 0;
      sub_45FE80(fld_e292, (int)v31, 2, 0, (int)v31, (int)this, 0);
      v33 = *v31;
      v34 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
      v35 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v34);
      v36 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v35);
      (*(void (/*thiscall*/ **)(int *, int))(v33 + 112))(v31, v36);
      //   sub_49C620/sub_49C5F0 写命令记录（时空域指令，参数含 pArg3 的 +12/+16 字段）；尾部播 PHASE_SHIFT + WZ_PHASE_SHIFT
      sub_49C620(0, 1, 0);
      pArg33 = pArg3;
      sub_49C5F0(0, 0, 0, *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12));
      fld_e1542 = (int)*(this + 1542);
      v39 = (int)*this;
      *(this + 2099) = *(uint32_t **)(*(uint32_t *)(pArg33 + 4) + 16);
      (*(void (/*thiscall*/ **)(uint32_t **, int))(v39 + 196))(this, fld_e1542);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, int, int))(*this)[222])(this, 0, 0, 1000, 1000);
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "PHASE_SHIFT", -1, 0, 0);
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_PHASE_SHIFT", -1, 0, 0);
      break;
    // ── [段 11] case 18：★ 投掷剑（ThrustUnder/ThrustOver）—— 技能表查参 + 帧时长反算 ──
    //   +2100 存分型（==4 走另一支）；sub_47EFD0/sub_47EF20 读技能表（+87 处 14 字节项表）
    case 18:
      v40 = (int)*this;
      v300 = **(uint32_t ***)(pArg3 + 4);
      *(this + 2100) = v300;
      *((uint8_t *)this + 8404) = 0;
      v41 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v40 + 1160))(this, v300);
      fld_e2100 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2100));
      if ( *(this + 2100) == (uint32_t *)4 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[86])(this, *(this + 139));
        v43 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);
        v44 = sub_47EFD0(v41, 0.0, fld_e2100, v43, v43, 11);
        v45 = (int)*this;
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v44 - 100);
        v46 = (*(int (/*thiscall*/ **)(uint32_t **))(v45 + 388))(this);
        LODWORD(v323) = 100 * sub_47EFD0(v41, COERCE_FLOAT(2), fld_e2100, v46, v46, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)SLODWORD(v323) + *((float *)this + 97);
        *(float *)&v47 = COERCE_FLOAT(sub_47EF20(1, fld_e2100, -1, -1, 11));
        v48 = (int)*this;
        v323 = *(float *)&v47;
        v321 = (double)v47 * 0.001 + 1.0;
        v49 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v48 + 672))(this, 3);
        v323 = COERCE_FLOAT(sub_495500(v49));
        v50 = (uint64_t)((double)SLODWORD(v323) * v321);
        ((void (/*fastcall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          (uint64_t)((double)SLODWORD(v323) * v321) >> 32,
          0,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, int, int))(*this)[222])(this, 0, 0, v50, v50);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[1]);
        if ( *(this + 2102) == nullptr )
        {
          fld_e99 = sub_42FCB0(228);
          LOBYTE(v329) = 5;
          if ( fld_e99 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ThrustUnder.ani", 1);
            else
              pThis_6C = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/ThrustUnder.ani", 1);
          }
          else
          {
            pThis_6C = nullptr;
          }
          *(this + 2102) = pThis_6C;
          fld_e99 = sub_42FCB0(228);
          LOBYTE(v329) = 6;
          if ( fld_e99 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C2 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ThrustOver.ani", 1);
            else
              pThis_6C2 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/ThrustOver.ani", 1);
          }
          else
          {
            pThis_6C2 = nullptr;
          }
          LOBYTE(v329) = 0;
          *(this + 2103) = pThis_6C2;
        }
        fld_e1625 = *(this + 1625);
        v54 = *fld_e1625;
        v323 = 0.0;
        fld_e992 = (*(int (/*thiscall*/ **)(int *))(v54 + 248))(fld_e1625);
        fld_e99 = fld_e992;
        v320 = 0;
        v321 = 0.0;
        //   +99 槽累加动画长度、+97(浮点) 累加帧数比 —— 把技能时长按动画帧标定（除 +25 补偿）
        while ( 1 )
        {
          v56 = *(uint32_t *)(fld_e992 + 4);
          if ( v56 == 0 || v320 >= (*(uint32_t *)(fld_e992 + 8) - v56) / 124 )
            break;
          if ( *(uint32_t *)(*(uint32_t *)(LODWORD(v321) + v56 + 60) + 4) != 0 )
          {
            v57 = sub_4924C0(5);
            v58 = *(float **)(v57 + 60);
            for ( m = *(float **)(v57 + 64); v58 != m; v58 += 6 )
            {
              v60 = v58[3] + *v58;
              if ( v60 > (double)SLODWORD(v323) )
                LODWORD(v323) = (uint64_t)v60;
            }
          }
          LODWORD(v321) += 124;
          fld_e992 = fld_e99;
          ++v320;
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(
          this,
          -1,
          *(this + 2102),
          LODWORD(v323) - 5,
          -41,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(
          this,
          1,
          *(this + 2103),
          LODWORD(v323) - 5,
          -41,
          0,
          0);
      }
      //   随后按帧链表（fld_e992）逐帧扫 DELAY 字段（v323 比较）挑出最长帧，再播 R_WZ_PRICK
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "R_WZ_PRICK", -1, 0, 0);
      break;
    // ── [段 12] case 19：★ 天上斩（WZ_PRE_HEAVENHIT / HEAVEN_HIT_MOVE 双段播报） ──
    //   +2124 存分型（12 走另一支）；UpperSwing.ani 预载到 +2125；+2127 初值 -150（位移量）
    case 19:
      v61 = (int)*this;
      v301 = **(uint32_t ***)(pArg3 + 4);
      *(this + 2124) = v301;
      v62 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v61 + 1160))(this, v301);
      fld_e2124 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2124));
      if ( *(this + 2124) == (uint32_t *)12 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 38);
        v64 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);
        v65 = sub_47EFD0(v62, 0.0, fld_e2124, v64, v64, 11);
        v66 = (int)*this;
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v65 - 100);
        v67 = (*(int (/*thiscall*/ **)(uint32_t **))(v66 + 388))(this);
        fld_e99 = 100 * sub_47EFD0(v62, COERCE_FLOAT(4), fld_e2124, v67, v67, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)fld_e99 + *((float *)this + 97);
        *(this + 114) = (uint32_t *)sub_47EF20(2, fld_e2124, -1, -1, 11);
        v68 = (uint32_t *)sub_47EF20(3, fld_e2124, -1, -1, 11);
        v69 = (int)*this;
        *(this + 113) = v68;
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t))(v69 + 196))(this, (*(this + 1554))[2]);
        v70 = sub_47EF20(1, fld_e2124, -1, -1, 11);
        v71 = (int)*this;
        fld_e99 = v70;
        v323 = (double)v70 * 0.001 + 1.0;
        v72 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v71 + 672))(this, 3);
        fld_e99 = sub_495500(v72);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[222])(
          this,
          0,
          0,
          (uint64_t)((double)fld_e99 * v323),
          (uint64_t)((double)fld_e99 * v323));
        v73 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1);
        v74 = (int)*this;
        *(this + 2128) = (uint32_t *)v73;
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t, int, int, uint32_t, int, int))(v74 + 876))(
          this,
          0,
          360,
          360,
          0,
          -1800,
          1);
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, int))(*this)[219])(this, 1, 300, 300, 0, -1500, 1);
        v75 = (int)*this;
        fld_e2128 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[38])(this, *(this + 2128));
        (*(void (/*thiscall*/ **)(uint32_t **, int))(v75 + 896))(this, fld_e2128);
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
          this,
          "WZ_PRE_HEAVENHIT",
          -1,
          0,
          0);
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
        this,
        "HEAVEN_HIT_MOVE",
        -1,
        0,
        0);
      v77 = (void *)((int (/*thiscall*/ *)(uint32_t **, int))(*this)[293])(this, 1);
      sub_406D60(v77);
      if ( *(this + 2125) == nullptr )
      {
        fld_e99 = sub_42FCB0(228);
        LOBYTE(v329) = 7;
        if ( fld_e99 != 0 )
        {
          if ( (unsigned int)*(this + 96) < 0x10 )
            pThis_6C3 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/UpperSwing.ani", 1);
          else
            pThis_6C3 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/UpperSwing.ani", 1);
        }
        else
        {
          pThis_6C3 = nullptr;
        }
        LOBYTE(v329) = 0;
        *(this + 2125) = pThis_6C3;
      }
      ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
        this,
        1,
        *(this + 2125),
        0,
        0,
        0,
        0);
      *((uint8_t *)this + 8504) = 0;
      *(this + 2127) = (uint32_t *)-150;
      break;
    // ── [段 13] case 20：★ 挥击（WhipToMonsterSwing / WZ_SWING_READY / PALM_FLASH） ──
    //   +2129 存分型；13 走掌击支（PALM_FLASH + R_WZ_PALMFLASH），20 走鞭击支（+2131 动画件）
    case 20:
      v79 = (int)*this;
      v302 = **(uint32_t ***)(pArg3 + 4);
      *(this + 2129) = v302;
      *((uint8_t *)this + 8520) = 0;
      v80 = (char *)(*(int (/*thiscall*/ **)(uint32_t **, uint32_t *))(v79 + 1160))(this, v302);
      fld_e2129 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2129));
      fld_e21292 = (int)*(this + 2129);
      if ( fld_e21292 == 13 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 76);
        v83 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);
        v84 = sub_47EFD0(v80, 0.0, fld_e2129, v83, v83, 11);
        v85 = (int)*this;
        *(this + 99) = (uint32_t *)((char *)*(this + 99) + v84 - 100);
        v86 = (*(int (/*thiscall*/ **)(uint32_t **))(v85 + 388))(this);
        fld_e99 = 100 * sub_47EFD0(v80, COERCE_FLOAT(3), fld_e2129, v86, v86, 0) / (int)(*(this + 99) + 25);
        *((float *)this + 97) = (double)fld_e99 + *((float *)this + 97);
        //   sub_47EF20(1..4, 分型) 连续查技能表取伤害/时长；sub_495500 取槽对乘积（+844/+858）
        *(this + 113) = (uint32_t *)sub_47EF20(1, fld_e2129, -1, -1, 11);
        v87 = (uint32_t *)sub_47EF20(2, fld_e2129, -1, -1, 11);
        v88 = (int)*this;
        *(this + 114) = v87;
        (*(void (/*thiscall*/ **)(uint32_t **, uint32_t))(v88 + 196))(this, (*(this + 1554))[3]);
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 2, 2, 1000, 1000);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
          this,
          "WZ_SWING_READY",
          -1,
          0,
          0);
      }
      else if ( fld_e21292 == 20 )
      {
        v89 = (int)*this;
        fld_e139 = (int)(*(this + 139) + 152);
        *(this + 2132) = (uint32_t *)4;
        (*(void (/*thiscall*/ **)(uint32_t **, int))(v89 + 344))(this, fld_e139);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[5]);
        ((void (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[222])(this, 3, 3, 1000, 1000);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);
        if ( *(this + 2131) == nullptr )
        {
          fld_e99 = sub_42FCB0(228);
          LOBYTE(v329) = 8;
          if ( fld_e99 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C4 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/WhipToMonsterSwing.ani", 1);
            else
              pThis_6C4 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/WhipToMonsterSwing.ani", 1);
          }
          else
          {
            pThis_6C4 = nullptr;
          }
          LOBYTE(v329) = 0;
          *(this + 2131) = pThis_6C4;
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
          this,
          1,
          *(this + 2131),
          0,
          0,
          0,
          0);
      }
      break;
    // ── [段 14] case 21：★ 替身/挑衅（SPIRIT_SACRIFICE 前置）—— 分型 14 走 PALM_FLASH 支 ──
    //   +2133/+2134/+2135 三表参；sub_432E50 关系码对调（左右朝向）；sub_4939E0/sub_493A60 动画冻结+时间推进
    case 21:
      v91 = **(uint32_t ***)(pArg3 + 4);
      *(this + 2133) = v91;
      if ( v91 != nullptr )
      {
        if ( v91 == (uint32_t *)1 )
          *(this + 2135) = *(uint32_t **)(*(uint32_t *)(pArg32 + 4) + 4);
      }
      else
      {
        *(this + 2134) = *(uint32_t **)(*(uint32_t *)(pArg32 + 4) + 4);
      }
      fld_e2134 = (char *)((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[290])(this, *(this + 2134));
      fld_e21342 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[285])(this, *(this + 2134));
      fld_e21343 = *(this + 2134) == (uint32_t *)14;
      fld_e99 = fld_e21342;
      if ( fld_e21343 )
      {
        fld_e2133 = (int)*(this + 2133);
        if ( fld_e2133 != 0 )
        {
          if ( fld_e2133 == 1 )
          {
            v98 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
            v99 = sub_432E50(v98);
            v100 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[283])(this, 0);
            v101 = (int)*this;
            if ( v100 == v99 )
              (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v101 + 876))(0, 0, 0, 0, 0, 0);
            else
              (*(void (/*stdcall*/ **)(uint32_t, int, int, uint32_t, int, int))(v101 + 876))(
                0,
                dword_9B9338,
                dword_9B9338,
                0,
                dword_9B933C,
                1);
            v102 = (int)*this;
            v103 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[38])(this, 4);
            (*(void (/*thiscall*/ **)(uint32_t **, int))(v102 + 896))(this, v103);
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "PALM_FLASH",
              -1,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "R_WZ_PALMFLASH",
              -1,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, uint32_t *))(*this)[86])(this, *(this + 139) + 114);
            v104 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[97])(this);
            fld_e993 = fld_e99;
            v106 = sub_47EFD0(fld_e2134, COERCE_FLOAT(1), fld_e99, v104, v104, 0);
            v107 = (int)*this;
            fld_e99 = v106;
            v108 = (*(int (/*thiscall*/ **)(uint32_t **))(v107 + 388))(this);
            v109 = sub_47EFD0(fld_e2134, 0.0, fld_e993, v108, v108, 0);
            fld_e99 = sub_423A80(v109, fld_e99, *(this + 2135), dword_9B9340);
            *((float *)this + 97) = (float)fld_e99;
            *(this + 113) = (uint32_t *)sub_47EF20(2, fld_e993, -1, -1, 11);
            *(this + 114) = (uint32_t *)sub_47EF20(3, fld_e993, -1, -1, 11);
          }
        }
        else
        {
          v96 = sub_47EF20(4, fld_e21342, -1, -1, 11);
          v97 = (int)*this;
          fld_e99 = v96;
          v323 = (double)v96 * 0.001 + 1.0;
          fld_e99 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v97 + 900))(this, 3);
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[222])(
            this,
            0,
            0,
            (uint64_t)((double)fld_e99 * v323),
            (uint64_t)((double)fld_e99 * v323));
          ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
            this,
            1,
            0,
            0,
            0,
            0,
            0);
          ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, 4, 4);
        }
      }
      fld_e21332 = (int)*(this + 2133);
      if ( fld_e21332 != 0 )
      {
        if ( fld_e21332 == 1 )
        {
          *(this + 2137) = (uint32_t *)-200;
          pThis_838 = this + 2104;
          for ( n = 2; n != 0; --n )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_838 + 12))(*pThis_838, 0);
            ++pThis_838;
          }
          sub_4939E0((int)*(this + 30), 0);
          v114 = sub_491C70(8);
          sub_493A60(v114);
          fld_e2136 = (int)*(this + 2136);
          LOBYTE(nArg5) = 0;
          sub_4939E0(fld_e2136, 0);
          v116 = sub_491C70(8);
          sub_493A60(v116);
          sub_491F80(-1, -1, -1, -1, 1);
        }
      }
      else
      {
        //   分支：+21332 为 1 时补 HandStrike.ani 预载（+2136）+ 满帧 DELAY 覆写 + vt+51 挂载
        if ( *(this + 2136) == nullptr )
        {
          fld_e99 = sub_42FCB0(228);
          LOBYTE(v329) = 9;
          if ( fld_e99 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C5 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HandStrike.ani", 1);
            else
              pThis_6C5 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/HandStrike.ani", 1);
          }
          else
          {
            pThis_6C5 = nullptr;
          }
          LOBYTE(v329) = 0;
          *(this + 2136) = pThis_6C5;
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
          this,
          1,
          *(this + 2136),
          0,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, (*(this + 1554))[4]);
        *(this + 2145) = nullptr;
      }
      break;
    // ── [段 15] 第二重 switch 结束 ──
    default:
      break;
  }
  pArg34 = pArg3;
  sub_4B89D0(nArg2, pArg3, *(float *)&pArg4, *(float *)&nArg5);
  // ── [段 16] 第三重 switch(nArg2)：★ 动作事件号分派（0/6/7/8/10/11/12/14）—— 与「技能分型」正交 ──
  //   本层先调 sub_4B89D0 做跑步地面循环/蓄气特效的公共前置
  switch ( nArg2 )
  {
    case 0:
      goto LABEL_156;
    // ── [段 17] case 6：★ 冲刺/连打位移——按 +8585 标志决定是否施加 vt+219 双段位移（左右手分算） ──
    //   随后关系码对调 + vt+224（末段动作）
    case 6:
      fld_e1723 = (int)*(this + 1723);
      if ( fld_e1723 == 0 )
        *((uint8_t *)this + 8585) = 0;
      if ( *((uint8_t *)this + 8585) != 0 && fld_e1723 == 1 )
      {
        fld_e2147 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          fld_e2147,
          fld_e2147,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v124 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
        if ( (int)*(this + 2147) < 0 )
          v124 = sub_432E50(v124);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v124, 4);
        *((uint8_t *)this + 6996) = 1;
      }
      return;
    // ── [段 18] case 7：同上但清 +8220，并多一步 vt+1172 取动作数据后交 sub_406D60 赋值 ──
    case 7:
      v125 = (int)*this;
      *((uint8_t *)this + 8220) = 0;
      v126 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v125 + 1172))(this, 1);
      sub_406D60(v126);
      if ( *((uint8_t *)this + 8585) != 0 )
      {
        fld_e21472 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          fld_e21472,
          fld_e21472,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v127 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
        if ( (int)*(this + 2147) < 0 )
          v127 = sub_432E50(v127);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v127, 4);
      }
      return;
    // ── [段 19] case 8：★ 普攻（R_WZ_ATK / R_WZ_LAST_ATK）—— +2054 存目标 id，按连击数选语音 ──
    case 8:
      if ( fld_e1639 != 8 )
      {
        if ( (unsigned int)sub_41C5A0(pArg34) <= 1 )
          v118 = -1;
        else
          v118 = *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 4);
        *(this + 2054) = (uint32_t *)v118;
      }
      if ( *(this + 2054) != (uint32_t *)-1 )
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[332])(this, 0);
      v119 = (int)*this;
      *((uint8_t *)this + 8220) = 0;
      v120 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v119 + 1172))(this, 1);
      sub_406D60(v120);
      if ( sub_41A5E0(this + 1757) >= 2 )
        ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("R_WZ_LAST_ATK", -1, 0, 0);
      else
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "R_WZ_ATK", -1, 0, 0);
      return;
    // ── [段 20] case 10：★ 投掷主处理（OneHandThrow1/2 预载 + 技能表时长标定 + 魔能充能） ──
    //   门 this+1953 非空即返回；+2144 存时长(ms)、+2142 存充能组、+2143 存到期时刻、+8584 存快速投掷标志
    case 10:
      if ( *(this + 1953) != nullptr )
        return;
      fld_e1952 = (int)*(this + 1952);
      pArg3 = 0;
      v321 = 0.0;
      if ( fld_e1952 != 0 )
      {
        if ( fld_e1952 == 1 )
        {
          fld_e2144 = (int)*(this + 2144);
          if ( fld_e2144 > 0 && (unsigned int)sub_41C5A0(pArg34) > 1 )
            pArg3 = 1000 * *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 4) / fld_e2144;
          *((uint8_t *)this + 8585) = 0;
        }
      }
      else
      {
        if ( (unsigned int)sub_41C5A0(pArg34) <= 0xA )
          v129 = 0;
        else
          v129 = *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 40);
        *(this + 2144) = (uint32_t *)v129;
        if ( v129 > 0 )
        {
          //   sub_699000(this+9) 取当前节拍；+1955 回收为 -1；sub_4BA610 按组号选充能动画；+2145 清空
          *(this + 2142) = *(this + 1954);
          pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
          fld_e21422 = (int)*(this + 2142);
          *(this + 2143) = (uint32_t *)((char *)*(this + 1955) + pThis_9);
          *(this + 1955) = (uint32_t *)-1;
          v131 = sub_5DA1E0(fld_e21422);
          sub_4BA610(v131);
          fld_e2058 = (int)*(this + 2058);
          *(this + 2145) = nullptr;
          if ( fld_e2058 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2058 + 80))(fld_e2058) != 0 )
          {
            v289 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[285])(this, 2, -1);
            ((void (/*thiscall*/ *)(uint32_t **))(*this)[290])(this);
            fld_e21442 = (int)*(this + 2144) * (1000 - sub_47EF20(2, 3, v289, -1, 11)) / 1000;
            *(this + 2144) = (uint32_t *)fld_e21442;
            if ( fld_e21442 <= 1 )
              fld_e21442 = 1;
            *(this + 2144) = (uint32_t *)fld_e21442;
          }
        }
        v134 = (unsigned int)sub_41C5A0(pArg34) > 0xB && *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 44) == 1;
        *((uint8_t *)this + 8584) = v134;
        v294 = 2;
        if ( v134 )
        {
          sub_494F20(2, 0.0);
          v294 = 0;
        }
        sub_495890(v294, 0);
      }
      //   this+1954==11 且 +1957 空时：预载 OneHandThrow1/2 两动画件到 +2106/+2107
      if ( *(this + 1957) == nullptr && *(this + 1954) == (uint32_t *)11 )
      {
        if ( *(this + 2106) == nullptr )
        {
          fld_e99 = sub_42FCB0(228);
          LOBYTE(v329) = 10;
          if ( fld_e99 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C6 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/OneHandThrow1.ani", 1);
            else
              pThis_6C6 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/OneHandThrow1.ani", 1);
          }
          else
          {
            pThis_6C6 = nullptr;
          }
          *(this + 2106) = pThis_6C6;
          fld_e99 = sub_42FCB0(228);
          LOBYTE(v329) = 11;
          if ( fld_e99 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
            {
              LOBYTE(v329) = 0;
              *(this + 2107) = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/OneHandThrow2.ani", 1);
            }
            else
            {
              fld_e913 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/OneHandThrow2.ani", 1);
              LOBYTE(v329) = 0;
              *(this + 2107) = fld_e913;
            }
          }
          else
          {
            LOBYTE(v329) = 0;
            *(this + 2107) = nullptr;
          }
        }
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
          this,
          1,
          *(this + (uint32_t)*(this + 1952) + 2106),
          0,
          0,
          0,
          0);
        if ( *(this + 1952) == (uint32_t *)1 )
        {
          pThis_8382 = this + 2104;
          for ( ii = 2; ii != 0; --ii )
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_8382 + 12))(*pThis_8382, 0);
            ++pThis_8382;
          }
        }
      }
      fld_e19542 = (int)*(this + 1954);
      //   this+1954（分型）进入第四重 switch(fld_e19542)：10/11/15/16/17/18/26/27/28/31/43 各一技法 ──
      //   骨架：按 +1952 左右手/分型建动画件 → 播 WZ_ 或 R_WZ_ 语音 → goto LABEL_509 公共尾
      switch ( fld_e19542 )
      {
        case 5:
        case 6:
        case 7:
        case 9:
        case 8:
          if ( *(this + 1952) != nullptr )
          {
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2109),
              0,
              0,
              0,
              0);
            if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
            {
              fld_e19543 = sub_5DA920(*(this + 1954));
              sub_5DC480(fld_e19543, 0);
            }
            *(this + 2061) = *(this + 1954);
          }
          else
          {
            if ( *(this + 2108) == nullptr )
            {
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 12;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C7 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/Chaser/Cast1.ani", 1);
                else
                  pThis_6C7 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/Chaser/Cast1.ani", 1);
              }
              else
              {
                pThis_6C7 = nullptr;
              }
              *(this + 2108) = pThis_6C7;
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 13;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C8 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/Chaser/Cast2.ani", 1);
                else
                  pThis_6C8 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/Chaser/Cast2.ani", 1);
              }
              else
              {
                pThis_6C8 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2109) = pThis_6C8;
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2108),
              0,
              0,
              0,
              0);
            fld_e19544 = sub_5DA920(*(this + 1954));
            (*(void (/*thiscall*/ **)(uint32_t **, char *, int, uint32_t, uint32_t))(HIDWORD(fld_e19544) + 212))(
              this,
              off_795828[(uint32_t)fld_e19544],
              -1,
              0,
              0);
          }
          goto LABEL_509;
        //   案例 10 = 追击弹爆炸（WZ_CHASER_EXPLOSION；分型 1 时走 sub_5DCF20 全清理） ──
        case 10:
          fld_e19522 = (int)*(this + 1952);
          if ( fld_e19522 != 0 )
          {
            if ( fld_e19522 == 1 )
              sub_5DCF20(this);
          }
          else
          {
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "WZ_CHASER_EXPLOSION",
              -1,
              0,
              0);
          }
          goto LABEL_509;
        //   案例 11 = 魔法飞弹（MagicMissile.ptl + R_WZ_MAGIC_MISSILE / R_WZ_MAGIC_MISSILE_READY） ──
        case 11:
          fld_e19523 = (int)*(this + 1952);
          if ( fld_e19523 != 0 )
          {
            if ( fld_e19523 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 11);
                v330 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 11);
                v143 = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(
                                   this,
                                   "Particle/MagicMissile.ptl");
                v295 = (uint16_t)pArg3;
                v290 = sub_47EF20(3, v330, -1, -1, 11);
                v144 = sub_47EF20(2, v330, -1, -1, 11);
                *(uint32_t *)((char *)v143 + 85) = sub_423A80(v144, v290, v295, 1000);
                v145 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[283])(this, 0);
                v146 = (int)*this;
                fld_e1639 = v145;
                v147 = (*(int (/*thiscall*/ **)(uint32_t **, int))(v146 + 1132))(this, 1);
                if ( v147 == 2 )
                {
                  if ( fld_e1639 == ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) )
                    v143[18] = -sub_47E9D0(1);
                  else
                    v143[18] = -sub_47E9D0(2);
                }
                else if ( v147 == 3 )
                {
                  if ( fld_e1639 == ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) )
                    v143[18] = sub_47E9D0(1);
                  else
                    v143[18] = sub_47E9D0(2);
                }
                else
                {
                  v143[18] = 0;
                }
                *(float *)&nArg5 = 0.0;
                pArg4 = 0;
                if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 0 )
                  v148 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + 44;
                else
                  v148 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - 44;
                v288 = *(uint32_t *)((char *)v143 + 85) * *(uint32_t *)((char *)v143 + 15) / 1000;
                v284 = v143[19];
                v282 = v143[18];
                v281 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) + 60;
                v149 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);
                sub_4B2580(&nArg5, &pArg4, this, v148, v149, v281, v282, v284, 15, 0, -1, v288, 30, 30, 30);
                v150 = v143[19];
                v143[18] += nArg5;
                v143[19] = pArg4 + v150;
                ((void (/*thiscall*/ *)(uint32_t **, int, int, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(
                  this,
                  23007,
                  v330,
                  v143,
                  0,
                  44,
                  0,
                  60,
                  4,
                  0,
                  2,
                  &pArg3);
                v151 = v143[19];
                v143[18] -= nArg5;
                v143[19] = v151 - pArg4;
              }
              sub_5DBBD0("R_WZ_MAGIC_MISSILE", 500);
            }
          }
          else
          {
            sub_5DADE0("R_WZ_MAGIC_MISSILE_READY");
          }
          goto LABEL_509;
        //   案例 15 = 灯笼火（R_WZ_LANTERN_FIRE）；dword_78FE2C 全局配合 sub_5C6A90 + sub_5DAE20 相位槽 ──
        case 15:
          fld_e19524 = (int)*(this + 1952);
          if ( fld_e19524 != 0 )
          {
            if ( fld_e19524 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                pThis_2188 = *((uint8_t *)this + 8584);
                dword_78FE2C = 0;
                v154 = pThis_2188 != 0 ? 73 : 68;
                v331 = pThis_2188 != 0 ? 0 : 0x35;
                sub_5C6A90(pArg3);
                if ( *((uint8_t *)this + 8584) != 0 )
                  sub_5DAE20(dword_9B9344);
                v155 = (int)*this;
                v156 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, int, int))(*this)[285])(
                         this,
                         15,
                         0,
                         0,
                         v154,
                         0,
                         v331,
                         4,
                         0,
                         dword_78FE2C,
                         dword_78FE28);
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v155 + 580))(this, 23008, v156);
              }
              sub_5DBBD0("R_WZ_LANTERN_FIRE", 500);
              if ( *((uint8_t *)this + 8584) != 0 )
              {
                v157 = (int)*this;
                *((uint8_t *)this + 8585) = 1;
                (*(void (/*thiscall*/ **)(uint32_t **, int))(v157 + 1160))(this, 42);
                *(this + 2147) = (uint32_t *)-sub_47E9D0(0);
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 42);
                v321 = COERCE_FLOAT(sub_47E9D0(1));
              }
            }
          }
          else
          {
            sub_5DADE0("R_WZ_LANTERN_FIRE_READY");
          }
          goto LABEL_509;
        //   案例 16 = LaunchFrostHead（冰霜头）；案例 17 = LaunchFluorescentShoot（荧光弹）；案例 18 = 黑猫 ──
        case 16:
          fld_e19525 = (int)*(this + 1952);
          if ( fld_e19525 == 0 )
          {
            if ( *(this + 2112) == nullptr )
            {
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 14;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C9 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchFrostHead.ani", 1);
                else
                  pThis_6C9 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchFrostHead.ani", 1);
              }
              else
              {
                pThis_6C9 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2112) = pThis_6C9;
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2112),
              0,
              0,
              0,
              0);
            sub_5DADE0("R_WZ_FROSTHEAD_READY");
            goto LABEL_509;
          }
          if ( fld_e19525 != 1 )
            goto LABEL_509;
          if ( *(this + 2112) != nullptr )
            sub_4AECE0(2);
          if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) == 0 )
          {
LABEL_278:
            sub_5DBBD0("R_WZ_FROSTHEAD", 450);
            goto LABEL_509;
          }
          ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 16);
          v332 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 16);
          v160 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/LaunchFrostHead.ptl");
          v296 = (uint16_t)pArg3;
          v161 = v160;
          v291 = sub_47EF20(3, v332, -1, -1, 11);
          v162 = sub_47EF20(2, v332, -1, -1, 11);
          *(uint32_t *)(v161 + 85) = sub_423A80(v162, v291, v296, 1000);
          v163 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1);
          v305 = 1;
          if ( v163 != 2 )
          {
            if ( ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[283])(this, 1) == 3 )
            {
              v164 = sub_47E9D0(3);
LABEL_277:
              *(uint32_t *)(v161 + 31) = v164;
              ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(
                this,
                23009,
                v332,
                v161,
                0,
                42,
                0,
                100,
                4,
                0,
                2,
                &pArg3);
              goto LABEL_278;
            }
            v305 = 2;
          }
          v164 = sub_47E9D0(v305);
          goto LABEL_277;
        case 17:
          fld_e19526 = (int)*(this + 1952);
          if ( fld_e19526 != 0 )
          {
            if ( fld_e19526 == 1 )
            {
              if ( *(this + 2113) == nullptr )
              {
                fld_e99 = sub_42FCB0(228);
                LOBYTE(v329) = 15;
                if ( fld_e99 != 0 )
                {
                  if ( (unsigned int)*(this + 96) < 0x10 )
                    pThis_6C10 = (uint32_t *)sub_431920(
                                       (uint8_t)this + 108,
                                       (char)"Effect/Animation/LaunchFluorescentShoot.ani",
                                       1);
                  else
                    pThis_6C10 = (uint32_t *)sub_431920(
                                       (char)*(this + 91),
                                       (char)"Effect/Animation/LaunchFluorescentShoot.ani",
                                       1);
                }
                else
                {
                  pThis_6C10 = nullptr;
                }
                LOBYTE(v329) = 0;
                *(this + 2113) = pThis_6C10;
              }
              ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, uint32_t, uint32_t))(*this)[51])(
                this,
                1,
                *(this + 2113),
                44,
                -60,
                0,
                0);
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                *(float *)&fld_e19545 = COERCE_FLOAT(((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[290])(this, *(this + 1954)));
                v168 = (int)*this;
                v323 = *(float *)&fld_e19545;
                fld_e19546 = (*(int (/*thiscall*/ **)(uint32_t **, uint32_t))(v168 + 1140))(this, *(this + 1954));
                v170 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(
                         this,
                         "Particle/LaunchFluorescent.ptl");
                v297 = (uint16_t)pArg3;
                v292 = sub_47EF20(3, fld_e19546, -1, -1, 11);
                v171 = sub_47EF20(2, fld_e19546, -1, -1, 11);
                *(uint32_t *)(v170 + 85) = sub_423A80(v171, v292, v297, 1000);
                *(float *)&v172 = COERCE_FLOAT(sub_47E9D0(1));
                nArg5 = v172;
                if ( v172 > 0 )
                {
                  v333 = 0;
                  pArg4 = v172;
                  do
                  {
                    *(uint32_t *)(v170 + 72) = v333 / nArg5;
                    ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, uint32_t, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(
                      this,
                      23010,
                      fld_e19546,
                      v170,
                      0,
                      0,
                      0,
                      60,
                      4,
                      0,
                      2,
                      &pArg3);
                    fld_e21343 = pArg4 == 1;
                    v333 += 360;
                    --pArg4;
                  }
                  while ( !fld_e21343 );
                }
              }
              sub_5DBBD0("R_WZ_FLUORE", 400);
            }
          }
          else
          {
            sub_5DADE0("R_WZ_FLUORE_READY");
          }
          goto LABEL_509;
        //   案例 18 主体：R_WZ_LAUNCH_PLUTO 播报 + LaunchBlackCatCast1/2.ani 双动画件 ──
        case 18:
          fld_e19527 = (int)*(this + 1952);
          if ( fld_e19527 != 0 )
          {
            if ( fld_e19527 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                v176 = (int)*this;
                v177 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[285])(
                         this,
                         18,
                         0,
                         0,
                         44,
                         0,
                         60,
                         4,
                         0,
                         2,
                         &pArg3);
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v176 + 580))(this, 23011, v177);
              }
              sub_5DBBD0("R_WZ_LAUNCH_PLUTO", 0);
            }
          }
          else
          {
            if ( *(this + 2114) == nullptr )
            {
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 16;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C11 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchBlackCatCast1.ani", 1);
                else
                  pThis_6C11 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchBlackCatCast1.ani", 1);
              }
              else
              {
                pThis_6C11 = nullptr;
              }
              *(this + 2114) = pThis_6C11;
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 17;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C12 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/LaunchBlackCatCast2.ani", 1);
                else
                  pThis_6C12 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/LaunchBlackCatCast2.ani", 1);
              }
              else
              {
                pThis_6C12 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2115) = pThis_6C12;
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2114),
              0,
              0,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2115),
              0,
              0,
              0,
              0);
            sub_5DADE0("R_WZ_LAUNCH_PLUTO_READY");
          }
          goto LABEL_509;
        //   案例 26 = Void（虚空）：Particle/Void.ptl + R_WZ_VOID 播报 ──
        case 26:
          fld_e19528 = (int)*(this + 1952);
          if ( fld_e19528 != 0 )
          {
            if ( fld_e19528 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 26);
                v179 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 26);
                v180 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/Void.ptl");
                v298 = (uint16_t)pArg3;
                fld_e99 = v180;
                v293 = sub_47EF20(3, v179, -1, -1, 11);
                v181 = sub_47EF20(2, v179, -1, -1, 11);
                fld_e994 = fld_e99;
                *(uint32_t *)(fld_e99 + 85) = sub_423A80(v181, v293, v298, 1000) + 300;
                ((void (/*thiscall*/ *)(uint32_t **, int, int, int, uint32_t, int, uint32_t, int, int, uint32_t, int, int *))(*this)[145])(
                  this,
                  23012,
                  v179,
                  fld_e994,
                  0,
                  38,
                  0,
                  62,
                  4,
                  0,
                  2,
                  &pArg3);
              }
              sub_5DBBD0("R_WZ_VOID", 500);
            }
          }
          else
          {
            sub_5DADE0("R_WZ_VOID_READY");
          }
          goto LABEL_509;
        //   案例 27 = HalloweenBuster（万圣节爆弹）：R_WZ_SHOOTING_STAR 播报 ──
        case 27:
          fld_e19529 = (int)*(this + 1952);
          if ( fld_e19529 != 0 )
          {
            if ( fld_e19529 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 27);
                pArg4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[285])(this, 27);
                v183 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/HalloweenBuster.ptl");
                v184 = sub_47E9D0(1);
                v185 = (int)*this;
                v334 = v184;
                v186 = v184 - *(uint32_t *)(v183 + 15);
                fld_e99 = -*(uint32_t *)(v183 + 31);
                if ( (*(int (/*thiscall*/ **)(uint32_t **))(v185 + 152))(this) != 0 )
                  v187 = v334 + ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this);
                else
                  v187 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v334;
                v335 = v187;
                if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 0 )
                  LODWORD(v188) = v186 + ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this);
                else
                  LODWORD(v188) = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v186;
                v189 = (int)*this;
                *(float *)&nArg5 = v188;
                v190 = (*(int (/*thiscall*/ **)(uint32_t **, int, int, int, int *))(v189 + 152))(this, 200, 4, 2, &pArg3);
                v191 = ((int (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[31])(this, 23013, pArg4, v183, v190);
                v192 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[32])(this, v335, v191);
                v193 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, fld_e99 + v192);
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v189 + 584))(this, nArg5, v193);
              }
              sub_5DBBD0("R_WZ_SHOOTING_STAR", 700);
            }
          }
          else
          {
            sub_5DADE0("R_WZ_SHOOTING_STAR_READY");
          }
          goto LABEL_509;
        //   案例 28 = Disenchant（驱散）：DisenchantCast2.ani + DisenchantArea1-4.ani 序列 + WZ_DISENCHANT ──
        case 28:
          fld_e195210 = (int)*(this + 1952);
          if ( fld_e195210 != 0 )
          {
            if ( fld_e195210 == 1 )
            {
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 19;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  LOBYTE(fld_e914) = (uint8_t)this + 108;
                else
                  fld_e914 = (int)*(this + 91);
                v200 = sub_431920(fld_e914, (char)"Effect/Animation/DisenchantCast2.ani", 1);
              }
              else
              {
                v200 = 0;
              }
              fld_e99 = sub_44B6C0(284);
              LOBYTE(v329) = 20;
              v201 = fld_e99 != 0 ? (int *)sub_44E1F0(v200, 1) : nullptr;
              fld_e293 = (int)*(this + 29);
              LOBYTE(v329) = 0;
              sub_45FE80(fld_e293, (int)v201, 2, 0, (int)v201, (int)this, 0);
              v203 = *v201;
              v306 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
              (*(void (/*thiscall*/ **)(int *))(v203 + 148))(v201);
              v204 = *v201;
              v205 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
              v206 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v205);
              v207 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v206);
              (*(void (/*thiscall*/ **)(int *, int))(v204 + 112))(v201, v207);
              v208 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[285])(this);
              ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int))(*this)[290])(this, 28, 0, v208);
              v209 = (double)(int)sub_47EF20(28, -1, -1, 11, v306);
              nArg52 = 0;
              do
              {
                nArg5 = nArg52 + 1;
                sprintf(Buffer, "Effect/Animation/DisenchantArea%d.ani", nArg52 + 1);
                fld_e99 = sub_42FCB0(228);
                LOBYTE(v329) = 21;
                if ( fld_e99 != 0 )
                {
                  if ( (unsigned int)*(this + 96) < 0x10 )
                    LOBYTE(fld_e915) = (uint8_t)this + 108;
                  else
                    fld_e915 = (int)*(this + 91);
                  v212 = sub_431920(fld_e915, (char)Buffer, 1);
                }
                else
                {
                  v212 = 0;
                }
                LOBYTE(v329) = 0;
                v337 = v209 * 0.0018867925;
                sub_4922F0(v337);
                fld_e99 = sub_44B6C0(284);
                LOBYTE(v329) = 22;
                if ( fld_e99 != 0 )
                  v213 = (int *)sub_44E1F0(v212, 1);
                else
                  v213 = nullptr;
                v214 = *v213;
                LOBYTE(v329) = 0;
                *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v214 + 36))(v213) + 8) = 2;
                sub_45FE80((int)*(this + 29), (int)v213, 2, 0, (int)v213, 0, 0);
                v215 = *v213;
                v216 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
                (*(void (/*thiscall*/ **)(int *, int))(v215 + 148))(v213, v216);
                v217 = *v213;
                v218 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
                v219 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v218);
                v220 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v219);
                (*(void (/*thiscall*/ **)(int *, int))(v217 + 112))(v213, v220);
                nArg52 = nArg5;
              }
              while ( nArg5 < 4 );
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
                ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this)[145])(
                  this,
                  48015,
                  *(this + 1954),
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
          }
          else
          {
            fld_e30 = sub_42FC90(*(this + 30));
            sub_4AECE0(fld_e30 - 1);
            if ( *(this + 2116) == nullptr )
            {
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 18;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C13 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/DisenchantCast1.ani", 1);
                else
                  pThis_6C13 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/DisenchantCast1.ani", 1);
              }
              else
              {
                pThis_6C13 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2116) = pThis_6C13;
            }
            fld_e2116 = (int)*(this + 2116);
            v198 = 0;
            fld_e1664 = (int)*(this + 1664) * (int)*(this + 1955) / 1000 / sub_42FC90(fld_e2116);
            if ( sub_42FC90(fld_e2116) > 0 )
            {
              do
                *(uint32_t *)(sub_4924C0(v198++) + 48) = fld_e1664;
              while ( v198 < sub_42FC90(*(this + 2116)) );
            }
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2116),
              0,
              0,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "WZ_DISENCHANT",
              -1,
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "DISENCHANT",
              -1,
              0,
              0);
          }
          goto LABEL_509;
        //   案例 31 = SunBurst（阳光爆发）：SunBurstFloor1/2.ani + SunBurstCast1/2.ani 四动画件 + R_WZ_SUNBURST ──
        case 31:
          fld_e195211 = (int)*(this + 1952);
          if ( fld_e195211 != 0 )
          {
            if ( fld_e195211 == 1 )
            {
              if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
              {
                v230 = (int)*this;
                fld_e40 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t **, int, int *))(*this)[285])(
                         this,
                         31,
                         0,
                         0,
                         0,
                         0,
                         *(this + 40),
                         4,
                         this,
                         2,
                         &pArg3);
                (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v230 + 580))(this, 23015, fld_e40);
              }
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 26;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  LOBYTE(fld_e916) = (uint8_t)this + 108;
                else
                  fld_e916 = (int)*(this + 91);
                v233 = sub_431920(fld_e916, (char)"Effect/Animation/SunBurstFloor2.ani", 1);
              }
              else
              {
                v233 = 0;
              }
              fld_e99 = sub_44B6C0(284);
              LOBYTE(v329) = 27;
              if ( fld_e99 != 0 )
                v234 = (int *)sub_44E1F0(v233, 1);
              else
                v234 = nullptr;
              v235 = *v234;
              LOBYTE(v329) = 0;
              *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v235 + 36))(v234) + 8) = 2;
              sub_45FE80((int)*(this + 29), (int)v234, 2, 0, (int)v234, 0, 0);
              v236 = *v234;
              v237 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
              v238 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v237);
              v239 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v238);
              (*(void (/*thiscall*/ **)(int *, int))(v236 + 112))(v234, v239);
              v240 = *v234;
              v241 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
              (*(void (/*thiscall*/ **)(int *, int))(v240 + 148))(v234, v241);
              sub_5DBBD0("R_WZ_SUNBURST", 400);
            }
          }
          else
          {
            pThis_8452 = this + 2117;
            if ( *(this + 2117) == nullptr )
            {
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 23;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C14 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstCast1.ani", 1);
                else
                  pThis_6C14 = sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstCast1.ani", 1);
              }
              else
              {
                pThis_6C14 = 0;
              }
              *pThis_8452 = pThis_6C14;
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 24;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C15 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstCast2.ani", 1);
                else
                  pThis_6C15 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstCast2.ani", 1);
              }
              else
              {
                pThis_6C15 = nullptr;
              }
              *(this + 2118) = pThis_6C15;
              fld_e99 = sub_42FCB0(228);
              LOBYTE(v329) = 25;
              if ( fld_e99 != 0 )
              {
                if ( (unsigned int)*(this + 96) < 0x10 )
                  pThis_6C16 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SunBurstFloor1.ani", 1);
                else
                  pThis_6C16 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SunBurstFloor1.ani", 1);
              }
              else
              {
                pThis_6C16 = nullptr;
              }
              LOBYTE(v329) = 0;
              *(this + 2119) = pThis_6C16;
            }
            v226 = sub_42FC90(*pThis_8452);
            fld_e16642 = (uint32_t)*(this + 1664) * (uint32_t)*(this + 1955);
            pThis_8453 = this + 2117;
            nArg5 = 3;
            pArg4 = fld_e16642 / 1000 / v226;
            do
            {
              for ( jj = 0; jj < sub_42FC90(*pThis_8453); ++jj )
              {
                v229 = sub_4924C0(jj);
                *(uint32_t *)(v229 + 48) = pArg4;
              }
              fld_e21343 = nArg5 == 1;
              ++pThis_8453;
              --nArg5;
            }
            while ( !fld_e21343 );
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this)[51])(
              this,
              1,
              *(this + 2117),
              0,
              -(int)*(this + 40),
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this)[51])(
              this,
              2,
              *(this + 2118),
              0,
              -(int)*(this + 40),
              0,
              0);
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this)[51])(
              this,
              1,
              *(this + 2119),
              0,
              0,
              0,
              1);
            sub_5DADE0("R_WZ_SUNBURST_READY");
          }
          goto LABEL_509;
        //   案例 43 = 挑衅人形（ProvocationDoll.ptl）+ WZ_FOLLOW_ME_03 ──
        case 43:
          if ( *(this + 1952) != (uint32_t *)1 )
            return;
          if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
          {
            v242 = (int)*this;
            v243 = ((int (/*thiscall*/ *)(uint32_t **, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this)[147])(
                     this,
                     "Particle/ProvocationDoll.ptl",
                     0,
                     50,
                     0,
                     33,
                     4,
                     0,
                     0,
                     0);
            v244 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[285])(this, 43, v243);
            (*(void (/*thiscall*/ **)(uint32_t **, int, int))(v242 + 580))(this, 23017, v244);
          }
LABEL_447:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
            this,
            "WZ_FOLLOW_ME_03",
            -1,
            0,
            0);
          goto LABEL_509;
        default:
          break;
      }
      // ── [段 21] 召唤兽分支（+1954 为 49/50 之外且过 sub_5DA9B0 表包含门）：sub_5E09B0 建召唤体 ──
      //   按 +1954 播 SUMMON_ADOR(21)/SUMMON_NIAS(22)/SUMMON_STALKER(23)/SUMMON_WISP(24)
      if ( fld_e19542 != 49 )
      {
        if ( fld_e19542 != 50 )
        {
          if ( (uint8_t)sub_5DA9B0(*(this + 1954)) != 0 )
          {
            fld_e195212 = (int)*(this + 1952);
            if ( fld_e195212 != 0 )
            {
              if ( fld_e195212 == 1 )
              {
                if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
                {
                  fld_e19547 = (int)*(this + 1954);
                  v271 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[285])(this);
                  fld_e19548 = COERCE_FLOAT(((int (/*thiscall*/ *)(uint32_t **, uint32_t, int))(*this)[290])(this, *(this + 1954), v271));
                  sub_5E09B0(fld_e19548, fld_e19547);
                }
                fld_e19549 = (int)*(this + 1954);
                switch ( fld_e19549 )
                {
                  case 21:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SUMMON_ADOR",
                      -1,
                      0,
                      0);
                    break;
                  case 22:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SUMMON_NIAS",
                      -1,
                      0,
                      0);
                    break;
                  case 23:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SUMMON_STALKER",
                      -1,
                      0,
                      0);
                    break;
                  case 24:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SUMMON_WISP",
                      -1,
                      0,
                      0);
                    break;
                  //   GBLN_INVOKE(25)/SANDOR_INVOKE(44)/AUXO_INVOKE(45)/LUIS_INVOKE(46) —— 对应召唤师各契约兽
                  case 25:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "GBLN_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  case 44:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "SANDOR_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  case 45:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "AUXO_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  case 46:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "LUIS_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  case 47:
                    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                      this,
                      "ECHEVERRA_INVOKE",
                      -1,
                      0,
                      0);
                    break;
                  default:
                    break;
                }
              }
            }
            else
            {
              switch ( v269 )
              {
                case 21:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_SUMMON_ADOR",
                    -1,
                    0,
                    0);
                  break;
                case 22:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_SUMMON_NIAS",
                    -1,
                    0,
                    0);
                  break;
                case 23:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_SUMMON_STALKER",
                    -1,
                    0,
                    0);
                  break;
                case 24:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_SUMMON_WISP",
                    -1,
                    0,
                    0);
                  break;
                case 25:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE",
                    -1,
                    0,
                    0);
                  break;
                case 44:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE_SANDOR",
                    -1,
                    0,
                    0);
                  break;
                case 45:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE_AUXO",
                    -1,
                    0,
                    0);
                  break;
                case 46:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE_LUIS",
                    -1,
                    0,
                    0);
                  break;
                case 47:
                  ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                    this,
                    "WZ_INVOKE_ECHEVERRA",
                    -1,
                    0,
                    0);
                  break;
                default:
                  break;
              }
            }
          }
          goto LABEL_509;
        }
        fld_e195213 = (int)*(this + 1952);
        if ( fld_e195213 != 0 )
        {
          if ( fld_e195213 == 1 && ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
          {
            v266 = ((int (/*thiscall*/ *)(uint32_t **, const char *))(*this)[147])(this, "Particle/TargetItBall.ptl");
            v267 = ((int (/*thiscall*/ *)(uint32_t **, int, int, int, int))(*this)[285])(this, 50, -1, -1, 11);
            ((void (/*thiscall*/ *)(uint32_t **, int, int, int))(*this)[290])(this, 50, 5, v267);
            v268 = sub_47EF20(v309, v310, v311, v312, v313);
            v313 = 0;
            v312 = 0;
            *(uint32_t *)(v266 + 85) = v268;
            ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, uint32_t, int, uint32_t))(*this)[145])(
              this,
              23018,
              0,
              v266,
              0,
              44,
              0);
          }
          goto LABEL_509;
        }
        goto LABEL_447;
      }
      v245 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[290])(this, 49);
      v246 = (int)*this;
      fld_e99 = v245;
      *(float *)&nArg5 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t **, int))(v246 + 1140))(this, 49));
      fld_e195214 = (int)*(this + 1952);
      if ( fld_e195214 == 0 )
      {
        pThis_8482 = this + 2120;
        if ( *(this + 2120) == nullptr )
        {
          fld_e1639 = sub_42FCB0(228);
          LOBYTE(v329) = 28;
          if ( fld_e1639 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C17 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SacrificeSpirit1.ani", 1);
            else
              pThis_6C17 = sub_431920((char)*(this + 91), (char)"Effect/Animation/SacrificeSpirit1.ani", 1);
          }
          else
          {
            pThis_6C17 = 0;
          }
          *pThis_8482 = pThis_6C17;
          fld_e1639 = sub_42FCB0(228);
          LOBYTE(v329) = 29;
          if ( fld_e1639 != 0 )
          {
            if ( (unsigned int)*(this + 96) < 0x10 )
              pThis_6C18 = (uint32_t *)sub_431920((uint8_t)this + 108, (char)"Effect/Animation/SacrificeSpirit2.ani", 1);
            else
              pThis_6C18 = (uint32_t *)sub_431920((char)*(this + 91), (char)"Effect/Animation/SacrificeSpirit2.ani", 1);
          }
          else
          {
            pThis_6C18 = nullptr;
          }
          LOBYTE(v329) = 0;
          *(this + 2121) = pThis_6C18;
        }
        v339 = 2;
        v251 = (double)(int)sub_47EF20(0, nArg5, -1, -1, 11) * 0.0071428572;
        *(float *)&nArg5 = v251 / *((float *)this + 2122);
        *((float *)this + 2122) = v251;
        do
        {
          sub_4922F0(*(float *)&nArg5);
          pArg4 = (int)*this;
          v252 = sub_47E9D0(0);
          (*(void (/*thiscall*/ **)(uint32_t **, int, uint32_t, int, uint32_t, uint32_t, int))(pArg4 + 204))(
            this,
            1,
            *pThis_8482++,
            v252,
            0,
            0,
            1);
          --v339;
        }
        while ( v339 != 0 );
        ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
          this,
          "R_WZ_SACRIFICE_SPIRIT",
          -1,
          0,
          0);
        goto LABEL_509;
      }
      if ( fld_e195214 != 1 )
        goto LABEL_509;
      v253 = sub_47EF20(0, nArg5, -1, -1, 11);
      v254 = (int)*this;
      LODWORD(v323) = v253 / 2;
      if ( (*(int (/*thiscall*/ **)(uint32_t **))(v254 + 152))(this) == 1 )
      {
        v255 = sub_47E9D0(0);
        pArg4 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + v255;
      }
      else
      {
        v256 = sub_47E9D0(0);
        pArg4 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) - v256;
      }
      fld_e99 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);
      v313 = 0;
      v314 = 0;
      v315 = 0;
      v317 = 0;
      v318 = 0;
      v319 = 0;
      fld_e294 = (int)*(this + 29);
      LOBYTE(v329) = 31;
      v340 = 0;
      if ( sub_425100(fld_e294) > 0 )
      {
        do
        {
          v258 = (uint32_t *)sub_425A00(v340);
          v259 = *v258;
          fld_e1639 = (int)v258;
          v299 = (*(int (/*thiscall*/ **)(uint32_t *))(v259 + 124))(v258);
          v260 = (*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 120))(v258);
          v261 = sub_499240(pArg4, fld_e99, v260, v299, 0);
          if ( v261 <= SLODWORD(v323) )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v258 + 40))(v258, 529) == 0 )
              goto LABEL_437;
            v262 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 340))(v258);
            v263 = &dword_738020;
            while ( v262 != *v263 )
            {
              if ( (int)++v263 >= (int)&dword_738030 )
                goto LABEL_437;
            }
            if ( (uint32_t **)v258[2088] == this )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v258 + 308))(v258) == 0 )
                goto LABEL_440;
            }
            else
            {
// ── [段 22] LABEL_437/LABEL_440：★ 献祭目标存活判定子循环（遍历场景对象表，条件位测试 17 + 关系码比对） ──
LABEL_437:
              v264 = (*(int (/*thiscall*/ **)(uint32_t *))(*v258 + 376))(v258);
              if ( v264 != ((int (/*thiscall*/ *)(uint32_t **))(*this)[94])(this)
                || (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v258 + 40))(v258, 17) == 0 )
              {
                goto LABEL_440;
              }
            }
            sub_428430(&fld_e1639);
          }
// ── [段 23] LABEL_440 收尾：播 SPIRIT_SACRIFICE（灵魂献祭）并清理临时缓冲 ──
LABEL_440:
          ++v340;
        }
        while ( v340 < sub_425100(*(this + 29)) );
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
        this,
        "SPIRIT_SACRIFICE",
        -1,
        0,
        0);
      sub_5E5260(v316);
      LOBYTE(v329) = 0;
      sub_5E5260(&v312);
// ── [段 24] ★ LABEL_509 公共尾：+1952==1 且两标志齐备时施加 双段位移 + 末段动作 + 方位/速率复位 ──
//   vt+219 双段位移(±2147)——vt+38 取关系码、sub_432E50 对调、vt+224 施加末段动作
LABEL_509:
      if ( *(this + 1952) == (uint32_t *)1 && *((uint8_t *)this + 8584) != 0 && *((uint8_t *)this + 8585) != 0 )
      {
        fld_e21473 = abs32((int)*(this + 2147));
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          0,
          fld_e21473,
          fld_e21473,
          0,
          0,
          0);
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v278 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this);
        if ( (int)*(this + 2147) < 0 )
          v278 = sub_432E50(v278);
        ((void (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v278, 4);
        sub_495890(2, 0);
        v308 = (float)SLODWORD(v321);
        sub_494F20(2, v308);
      }
      return;
    // ── [段 25] case 11：DASH_LOOP 播报 → LABEL_156 → sub_5DACE0（数据表 + 变速换锚 AI） ──
    case 11:
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "DASH_LOOP", 9, 0, 0);
LABEL_156:
      if ( *(this + 2142) != (uint32_t *)-1 )
        sub_5DACE0(this);
      return;
    // ── [段 26] case 12：清两标志 + vt+1172 取动作数据 + sub_406D60 赋值（收招） ──
    case 12:
      v121 = (int)*this;
      *((uint8_t *)this + 8228) = 0;
      *((uint8_t *)this + 8220) = 0;
      v122 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v121 + 1172))(this, 1);
      sub_406D60(v122);
      return;
    // ── [段 27] case 14：★ 形态/技能播报小表 —— 按 this+1991 索引播 WZ_ 系语音 ──
    //   176 WZ_ANCIENT_MEMORY / 175 WZ_LEAP / 180 WZ_UNYIELD_WILL / 30 R_WZ_FOLLOW_ME / 29 WZ_ELEMENTAL_BURN
    case 14:
      fld_e1991 = (int)*(this + 1991);
      switch ( fld_e1991 )
      {
        case 176:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_ANCIENT_MEMORY", -1, 0, 0);
          break;
        case 175:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WZ_LEAP", -1, 0, 0);
          break;
        case 180:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_UNYIELD_WILL", -1, 0, 0);
          break;
        case 30:
          v280 = *(uint32_t *)(*(uint32_t *)(pArg34 + 4) + 4);
          *((uint8_t *)this + 8368) = v280 == 0;
          *((uint8_t *)this + 8376) = 0;
          if ( v280 != 0 )
            ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
              this,
              "R_WZ_FOLLOW_ME",
              -1,
              0,
              0);
          break;
        case 29:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_ELEMENTAL_BURN", -1, 0, 0);
          break;
        //   41 WZ_ANCIENT_LIBRARY / 37 WZ_SHIELD / 2 WZ_SHOWTIME / 40 WZ_AUTO_CHASER
        case 41:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
            this,
            "WZ_ANCIENT_LIBRARY",
            -1,
            0,
            0);
          break;
        case 37:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_SHIELD", -1, 0, 0);
          break;
        case 2:
          ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
            this,
            "WZ_SHOWTIME",
            -1,
            0,
            0);
          break;
        case 40:
          ((void (/*stdcall*/ *)(const char *, int, uint32_t, uint32_t))(*this)[53])("WZ_AUTO_CHASER", -1, 0, 0);
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

