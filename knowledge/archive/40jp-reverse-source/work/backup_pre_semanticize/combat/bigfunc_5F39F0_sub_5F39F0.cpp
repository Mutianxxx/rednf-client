// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_5F39F0_sub_5F39F0.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x5F39F0）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 2251 行；字符串证据 5 条；外调 6 个
//   串: "SWD_GUARD_END"
//   串: "SM_UPPER_SLASH"
//   串: "SWD_GUARD"
//   串: "SM_GUARD"
//   串: "SWD_GUARDED"
//   调: sub_5F39F0 sub_47DD30 sub_5F0460 sub_4014D0 sub_41C5A0 sub_406D60
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x5F39F0 sub_5F39F0  size=11125
// ------------------------------------------------------------
void /*thiscall*/ sub_5F39F0(char *this, int a2, int a3, float a4, float a5)
{
  int v6; // edi
  int v7; // ebx
  int v8; // eax
  uint32_t *v9; // ebx
  int j; // edi
  uint32_t *v11; // ebx
  int k; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  uint32_t *v17; // ebx
  int i; // edi
  int v19; // eax
  uint32_t *v20; // ebx
  int m; // edi
  int v22; // eax
  int v23; // edx
  uint32_t *v24; // edi
  int v25; // edi
  int v26; // edi
  int v27; // eax
  int v28; // eax
  int v29; // ebx
  int v30; // eax
  int v31; // ebx
  int v32; // edi
  int v33; // ecx
  int v34; // edi
  int v35; // edi
  int v36; // ecx
  int v37; // ebx
  int v38; // eax
  int v39; // ecx
  int v40; // edi
  int v41; // edi
  int v42; // ecx
  int v43; // ebx
  int v44; // eax
  uint32_t *v45; // eax
  int v46; // ebx
  int *v47; // eax
  int v48; // edx
  int v49; // ebx
  int v50; // eax
  int v51; // edx
  int v52; // eax
  int v53; // edi
  char *v54; // eax
  int v55; // eax
  int v56; // ecx
  uint32_t *v57; // ebx
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int v61; // edi
  uint32_t *v62; // ebx
  int v63; // eax
  int v64; // eax
  int v65; // eax
  int v66; // edi
  int v67; // eax
  int v68; // edi
  int v69; // eax
  int v70; // eax
  int v71; // edi
  int v72; // eax
  void *v73; // eax
  int v74; // edi
  int v75; // eax
  void *v76; // eax
  int v77; // edi
  int v78; // ebx
  char *v79; // eax
  int v80; // edx
  int v81; // eax
  int v82; // eax
  char *v83; // edi
  int v84; // ebx
  int v85; // eax
  int v86; // eax
  int v87; // eax
  int v88; // edi
  int v89; // eax
  int v90; // eax
  int v91; // edi
  int v92; // eax
  void *v93; // eax
  int v94; // eax
  int v95; // eax
  int v96; // eax
  void *v97; // eax
  int v98; // ebx
  int v99; // edi
  char *v100; // eax
  int v101; // ebx
  int v102; // eax
  int v103; // ebx
  int n; // edi
  int v105; // ecx
  int v106; // eax
  int v107; // edi
  int v108; // eax
  int v109; // eax
  int v110; // edx
  int v111; // eax
  uint32_t *v112; // eax
  int v113; // eax
  int v114; // eax
  void **v115; // eax
  int v116; // eax
  int v117; // eax
  void *v118; // edi
  int v119; // eax
  int v120; // edi
  int v121; // eax
  int v122; // eax
  int v123; // edi
  int v124; // ebx
  char *v125; // eax
  int v126; // eax
  int v127; // edi
  int v128; // eax
  void *v129; // eax
  int v130; // eax
  int v131; // eax
  int v132; // edx
  int v133; // edx
  int v134; // eax
  int v135; // eax
  int v136; // eax
  int v137; // ecx
  int v138; // eax
  int v139; // ecx
  int v140; // eax
  char *v141; // ebx
  int v142; // edi
  int v143; // eax
  int v144; // eax
  int v145; // edx
  int v146; // eax
  int v147; // eax
  int v148; // edx
  int v149; // eax
  int v150; // eax
  uint32_t *v151; // ebx
  int v152; // eax
  int v153; // eax
  int v154; // eax
  int v155; // edi
  int v156; // eax
  unsigned int v157; // eax
  int v158; // ebx
  int v159; // eax
  int v160; // ebx
  int v161; // eax
  int v162; // eax
  int v163; // eax
  int v164; // edx
  int *v165; // ecx
  int v166; // ecx
  int v167; // edx
  int v168; // eax
  double v169; // st7
  int v170; // edx
  int v171; // edi
  int v172; // ebx
  char *v173; // eax
  int v174; // edi
  int v175; // eax
  void *v176; // eax
  char *v177; // edi
  int v178; // ebx
  int v179; // eax
  int v180; // eax
  int v181; // edx
  int v182; // edi
  int v183; // eax
  void *v184; // eax
  uint32_t *v185; // eax
  int v186; // eax
  int v187; // ecx
  int v188; // edi
  int v189; // eax
  void *v190; // eax
  int v191; // eax
  int v192; // eax
  int v193; // eax
  int v194; // eax
  int v195; // eax
  int v196; // eax
  int *v197; // eax
  int v198; // edx
  int v199; // edi
  uint64_t v200; // rax
  int v201; // eax
  double v202; // st7
  int v203; // eax
  int v204; // edi
  int v205; // ebx
  char *v206; // eax
  int v207; // edi
  int v208; // edx
  int v209; // edi
  int v210; // edi
  int v211; // ecx
  int v212; // ebx
  int v213; // ebx
  int v214; // eax
  int v215; // eax
  int v216; // eax
  int v217; // ecx
  int v218; // edi
  int v219; // edi
  int v220; // ecx
  int v221; // ebx
  int v222; // ebx
  int v223; // eax
  int v224; // eax
  int v225; // eax
  int v226; // ebx
  int v227; // edi
  int *v228; // eax
  int v229; // edx
  int v230; // edi
  int v231; // eax
  int v232; // edi
  int v233; // eax
  int v234; // edi
  int v235; // eax
  int v236; // eax
  int v237; // edi
  int v238; // eax
  int v239; // eax
  int v240; // eax
  char *v241; // ebx
  int v242; // edi
  int v243; // eax
  int v244; // eax
  int v245; // eax
  int v246; // [esp+C4h] [ebp-88h]
  float v247; // [esp+C8h] [ebp-84h]
  int v248; // [esp+CCh] [ebp-80h]
  unsigned int v249; // [esp+D4h] [ebp-78h]
  int v250; // [esp+D4h] [ebp-78h]
  int v251; // [esp+D4h] [ebp-78h]
  float v252; // [esp+D4h] [ebp-78h]
  int v253; // [esp+D4h] [ebp-78h]
  int v254; // [esp+D4h] [ebp-78h]
  int v255; // [esp+D8h] [ebp-74h]
  int v256; // [esp+DCh] [ebp-70h]
  int v257; // [esp+E0h] [ebp-6Ch]
  int v258; // [esp+E4h] [ebp-68h]
  int v259; // [esp+E8h] [ebp-64h]
  uint32_t *v260; // [esp+ECh] [ebp-60h]
  bool v261; // [esp+F3h] [ebp-59h]
  int v262; // [esp+F4h] [ebp-58h]
  float v263; // [esp+F4h] [ebp-58h]
  int v264; // [esp+F8h] [ebp-54h]
  uint32_t *v265; // [esp+F8h] [ebp-54h]
  void *v266; // [esp+FCh] [ebp-50h]
  void *v267; // [esp+FCh] [ebp-50h]
  void *v268; // [esp+FCh] [ebp-50h]
  void *v269; // [esp+FCh] [ebp-50h]
  void *v270; // [esp+FCh] [ebp-50h]
  void *v271; // [esp+FCh] [ebp-50h]
  void *v272; // [esp+FCh] [ebp-50h]
  void *v273; // [esp+FCh] [ebp-50h]
  void *v274; // [esp+FCh] [ebp-50h]
  void *v275; // [esp+FCh] [ebp-50h]
  void *v276; // [esp+FCh] [ebp-50h]
  void *v277; // [esp+FCh] [ebp-50h]
  int v278; // [esp+100h] [ebp-4Ch]
  int v279; // [esp+100h] [ebp-4Ch]
  float v280; // [esp+100h] [ebp-4Ch]
  char v281[4]; // [esp+104h] [ebp-48h] BYREF
  void *v282; // [esp+108h] [ebp-44h]
  int v283; // [esp+118h] [ebp-34h]
  unsigned int v284; // [esp+11Ch] [ebp-30h]
  void *Block[5]; // [esp+124h] [ebp-28h] BYREF
  unsigned int v286; // [esp+138h] [ebp-14h]
  int v287; // [esp+13Ch] [ebp-10h]
  int v288; // [esp+148h] [ebp-4h]
  int v289; // [esp+160h] [ebp+14h]
  int v290; // [esp+160h] [ebp+14h]
  int v291; // [esp+160h] [ebp+14h]

  v287 = dword_796E50;
  v264 = *((uint32_t *)this + 1639);
  v284 = 15;
  v283 = 0;
  LOBYTE(v282) = 0;
  v6 = a2;
  v288 = 0;
  switch ( v264 )
  {
    case 8:
      if ( *((uint32_t *)this + 2054) == 46 && *(this + 8220) == 0 )
      {
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);
        *(this + 8220) = 1;
      }
      break;
    case 10:
      if ( *((uint32_t *)this + 1953) == 0 )
      {
        v15 = *((uint32_t *)this + 1954);
        switch ( v15 )
        {
          case 23:
            v16 = *((uint32_t *)this + 1952);
            if ( v16 != 0 )
            {
              if ( v16 == 1 )
              {
                (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2097));
                (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2098));
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2095));
              (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2096));
            }
            break;
          case 32:
            if ( a2 != 10 )
            {
              v17 = this + 8404;
              for ( i = 2; i != 0; --i )
                (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *v17++);
              (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);
              v6 = a2;
            }
            break;
          case 24:
            if ( a2 != 0 )
            {
              (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 24);
              sub_47DD30(this);
            }
            break;
          default:
            if ( v15 == 44 && *((uint32_t *)this + 1952) == 1 && *((uint32_t *)this + 161) == 1 )
              (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);
            break;
        }
      }
      break;
    case 12:
      if ( *((int *)this + 2059) > 0 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
      {
        v7 = *(uint32_t *)this;
        v8 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 11);
        (*(void (/*thiscall*/ **)(char *, int, int))(v7 + 1296))(this, 11, v8);
      }
      break;
    case 15:
      if ( a2 != 15 )
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "SWD_GUARD_END",
          -1,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 2065) + 76))(*((uint32_t *)this + 2065), 0);
      }
      break;
    case 16:
      if ( *((uint32_t *)this + 2068) == 1 )
      {
        if ( *(this + 8284) != 0 )
        {
          (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, -1);
          (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 252))(this, 1, -1);
        }
        else
        {
          v9 = this + 8296;
          for ( j = 2; j != 0; --j )
            (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *v9++);
          v6 = a2;
        }
      }
      else
      {
        v11 = this + 8288;
        for ( k = 2; k != 0; --k )
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *v11++);
        v6 = a2;
      }
      break;
    case 18:
      if ( a2 != 18 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
      {
        v13 = *(uint32_t *)this;
        v14 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 8);
        (*(void (/*thiscall*/ **)(char *, int, int))(v13 + 1296))(this, 8, v14);
      }
      break;
    case 19:
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2084));
      break;
    case 20:
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2087));
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 996))(this);
      break;
    case 21:
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2104));
      break;
    case 22:
      if ( a2 != 22 )
      {
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 604))(this, 1);
        if ( *((uint32_t *)this + 2112) == 1 )
        {
          sub_5F0460(this);
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2121));
        }
      }
      break;
    case 23:
      v19 = *((uint32_t *)this + 2122);
      if ( v19 != 0 )
      {
        if ( v19 == 1 )
        {
          if ( *(this + 8496) != 0 )
          {
            (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, -1);
            (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 252))(this, 1, -1);
          }
          else
          {
            v20 = this + 8504;
            for ( m = 2; m != 0; --m )
              (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *v20++);
          }
          (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 216))(this, 12);
          (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 216))(this, 16);
          v6 = a2;
        }
        else if ( v19 == 2 )
        {
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2125));
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 996))(this);
      }
      if ( v6 != 23 )
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 596))(this, 1);
      break;
    default:
      break;
  }
  if ( v6 == 24 )
  {
    v6 = 8;
    a2 = 8;
    v264 = 24;
  }
  switch ( v6 )
  {
    case 8:
      sub_4014D0((std::_String_base *)v281, this + 7044, 0, -1);
      if ( v264 != 8 )
      {
        if ( (unsigned int)sub_41C5A0(a3) <= 1 )
          v22 = -1;
        else
          v22 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
        *((uint32_t *)this + 2054) = v22;
      }
      if ( *((uint32_t *)this + 2054) == 46 )
        sub_406D60("SM_UPPER_SLASH");
      goto LABEL_290;
    case 15:
      if ( v264 != 15 )
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "SWD_GUARD",
          -1,
          0,
          0);
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "SM_GUARD",
          -1,
          0,
          0);
      }
      v23 = *(uint32_t *)this;
      *((uint32_t *)this + 2060) = **(uint32_t **)(a3 + 4);
      (*(void (/*thiscall*/ **)(char *, uint32_t))(v23 + 144))(this, *(uint32_t *)(*(uint32_t *)(a3 + 4) + 12));
      v24 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 1);
      v260 = v24;
      v262 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 1);
      v256 = 0;
      v255 = 0;
      if ( *((uint32_t *)this + 2060) != 0 )
      {
        v261 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 8) != 0;
        (*(void (/*thiscall*/ **)(char *, const char *, int))(*(uint32_t *)this + 212))(this, "SWD_GUARDED", -1);
        v25 = 0;
        *((uint32_t *)this + 2062) = 100;
        if ( !v261 )
        {
          v25 = sub_47EF20(0, v262, -1, -1, 11);
          *((uint32_t *)this + 2062) = sub_47EF20(1, v262, -1, -1, 11);
        }
        (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
          this,
          0,
          v25,
          v25,
          0,
          -1000 * v25 / *((uint32_t *)this + 2062),
          1);
        (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);
        v26 = *(uint32_t *)this;
        v27 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);
        v28 = sub_432E50(v27);
        (*(void (/*thiscall*/ **)(char *, int))(v26 + 896))(this, v28);
        v29 = *(uint32_t *)(a3 + 4);
        v30 = *(uint32_t *)(v29 + 4);
        if ( v30 <= 22 )
        {
          v31 = 22;
        }
        else if ( v30 >= 71 )
        {
          v31 = 71;
        }
        else
        {
          v31 = *(uint32_t *)(v29 + 4);
        }
        v32 = sub_423A80(23, 6, v31 - 22, 49);
        if ( (*(int (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 152))(this, 0, 0) != 0 )
          v259 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 120))(this) + v32;
        else
          v259 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 120))(this) - v32;
        v278 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 124))(this);
        v258 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this) + v31;
        LOBYTE(v288) = 1;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            LOBYTE(v33) = (uint8_t)this + 108;
          else
            v33 = *((uint32_t *)this + 91);
          v34 = sub_431920(v33, (char)"Effect/Animation/GuardSpark.ani", 1);
        }
        else
        {
          v34 = 0;
        }
        LOBYTE(v288) = 2;
        if ( sub_44B6C0(284) != 0 )
          v35 = sub_44E1F0(v34, 1);
        else
          v35 = 0;
        v36 = *((uint32_t *)this + 29);
        LOBYTE(v288) = 0;
        sub_45FE80(v36, v35, 2, 0, v35, (int)this, 0);
        v37 = *(uint32_t *)v35;
        v38 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);
        (*(void (/*thiscall*/ **)(int, int))(v37 + 148))(v35, v38);
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v35 + 112))(v35, v259, v278, v258);
        LOBYTE(v288) = 3;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            LOBYTE(v39) = (uint8_t)this + 108;
          else
            v39 = *((uint32_t *)this + 91);
          v40 = sub_431920(v39, (char)"Effect/Animation/GuardCircle.ani", 1);
        }
        else
        {
          v40 = 0;
        }
        LOBYTE(v288) = 4;
        if ( sub_44B6C0(284) != 0 )
          v41 = sub_44E1F0(v40, 1);
        else
          v41 = 0;
        v42 = *((uint32_t *)this + 29);
        LOBYTE(v288) = 0;
        sub_45FE80(v42, v41, 2, 0, v41, (int)this, 0);
        v43 = *(uint32_t *)v41;
        v44 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);
        (*(void (/*thiscall*/ **)(int, int))(v43 + 148))(v41, v44);
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v41 + 112))(v41, v259, v278, v258);
        v24 = v260;
        *(this + 8256) = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(this, 0, 0, 0, 0);
        (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);
        (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      }
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));
      sub_4AECE0(*((void **)this + 30), *((uint32_t *)this + 2060) != 0);
      sub_4939E0(*((uint32_t *)this + 30), 1);
      LOBYTE(a5) = 0;
      *((uint32_t *)this + 2061) = 0;
      if ( v264 != 15 )
      {
        if ( *((uint32_t *)this + 2060) == 0 )
          *((uint32_t *)this + 2061) = sub_47E9D0(v24, 0);
        if ( *((uint32_t *)this + 2060) == 1 )
        {
          *((uint32_t *)this + 2063) = -1;
        }
        else
        {
          v45 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 2);
          v46 = sub_47E9D0(v45, 0);
          *((uint32_t *)this + 2063) = sub_699000((int)(this + 64)) + v46;
        }
        if ( *((uint32_t *)this + 2065) == 0 )
        {
          LOBYTE(v288) = 5;
          if ( operator new(0x60u) != nullptr )
            v47 = (int *)sub_510230(12, 0, -1);
          else
            v47 = nullptr;
          *((uint32_t *)this + 2065) = v47;
          v48 = *v47;
          LOBYTE(v288) = 0;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v48 + 64))(v47) + 36) = 0;
        }
        v49 = sub_47EF20(4, v262, -1, -1, 11);
        sub_5E5330(*((uint32_t *)this + 2065));
        sub_5E5F00(12, v49);
        (*(void (/*thiscall*/ **)(uint32_t, char *, char *, uint32_t, uint32_t, uint32_t, int))(**((uint32_t **)this + 2065) + 56))(
          *((uint32_t *)this + 2065),
          this,
          this,
          0,
          0,
          0,
          -1);
      }
      goto LABEL_290;
    case 16:
      v50 = **(uint32_t **)(a3 + 4);
      *((uint32_t *)this + 2068) = v50;
      if ( v50 != 0 )
      {
        v51 = *(uint32_t *)this;
        if ( v50 == 1 )
        {
          (*(void (/*stdcall*/ **)(int))(v51 + 216))(11);
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "SM_GUE_CHARGE",
            12,
            0,
            0);
        }
        else
        {
          (*(void (/*stdcall*/ **)(int))(v51 + 216))(12);
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "R_SM_GUE",
            11,
            0,
            0);
          *(this + 8304) = 0;
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "R_SM_GUE",
          11,
          0,
          0);
      }
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 4));
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139));
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 2, 1000, 1000);
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      v52 = *((uint32_t *)this + 2068);
      if ( v52 == 0 || v52 == 2 )
      {
        v53 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
        v279 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 5);
        v54 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 5);
        *((float *)this + 97) = (float)sub_47EFD0(v54, 0.0, v279, v53, v53, 0);
      }
      if ( *((uint32_t *)this + 2068) == 2 )
      {
        v248 = (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 1140))(this, 6, -1);
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1160))(this);
        v55 = sub_47EF20(6, 0, v248, -1, 11);
        v56 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
        *((uint32_t *)this + 2070) = v56;
        *((float *)this + 97) = (double)(int)sub_423A80(0, v55, v56, dword_7959F8) + *((float *)this + 97);
      }
      if ( *((uint32_t *)this + 2068) == 1 )
      {
        v57 = this + 8296;
        if ( *((uint32_t *)this + 2074) == 0 )
        {
          LOBYTE(v288) = 6;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v58 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttackOnCharge1.ani", 1);
            else
              v58 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttackOnCharge1.ani", 1);
          }
          else
          {
            v58 = 0;
          }
          *v57 = v58;
          LOBYTE(v288) = 7;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v59 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttackOnCharge2.ani", 1);
            else
              v59 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttackOnCharge2.ani", 1);
          }
          else
          {
            v59 = 0;
          }
          LOBYTE(v288) = 0;
          *((uint32_t *)this + 2075) = v59;
        }
        v60 = 0;
        do
        {
          v61 = v60 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            v60 + 1,
            *v57,
            0,
            0,
            0,
            0);
          v60 = v61;
          ++v57;
        }
        while ( v61 < 2 );
      }
      else
      {
        v62 = this + 8288;
        if ( *((uint32_t *)this + 2072) == 0 )
        {
          LOBYTE(v288) = 8;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v63 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttack1.ani", 1);
            else
              v63 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttack1.ani", 1);
          }
          else
          {
            v63 = 0;
          }
          *v62 = v63;
          LOBYTE(v288) = 9;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v64 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttack2.ani", 1);
            else
              v64 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttack2.ani", 1);
          }
          else
          {
            v64 = 0;
          }
          LOBYTE(v288) = 0;
          *((uint32_t *)this + 2073) = v64;
        }
        v65 = 0;
        do
        {
          v66 = v65 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            v65 + 1,
            *v62,
            0,
            0,
            0,
            0);
          v65 = v66;
          ++v62;
        }
        while ( v66 < 2 );
      }
      v67 = *((uint32_t *)this + 2068);
      switch ( v67 )
      {
        case 0:
          *(this + 8276) = 0;
          goto LABEL_160;
        case 1:
          v68 = *((uint32_t *)this + 30);
          v69 = sub_491C70(v68, 0);
          sub_493A60(v68, v69);
          sub_4939E0(*((uint32_t *)this + 30), 1);
          break;
        case 2:
          sub_4AECE0(*((void **)this + 30), 1);
          sub_4939E0(*((uint32_t *)this + 30), 0);
          break;
        default:
          goto LABEL_160;
      }
      LOBYTE(a5) = 0;
LABEL_160:
      if ( *((uint32_t *)this + 2068) != 2 )
        *(this + 8284) = 0;
      v70 = *((uint32_t *)this + 2068);
      if ( v70 == 0 || v70 == 2 )
      {
        v71 = *(uint32_t *)this;
        v72 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
        (*(void (/*thiscall*/ **)(char *, int))(v71 + 212))(this, v72);
        v73 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
        sub_4015C0(v73, strlen((const char *)v73));
      }
      goto LABEL_290;
    case 17:
      (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "SM_HITBACK",
        -1,
        0,
        0);
      if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 604))(this, 1);
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, **(uint32_t **)(a3 + 4));
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 8));
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 152);
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 2, 1000, 1000);
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      v74 = *(uint32_t *)this;
      v75 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
      (*(void (/*thiscall*/ **)(char *, int))(v74 + 212))(this, v75);
      v76 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
      sub_406D60(v76);
      v77 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
      v78 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 7);
      v79 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 7);
      *((float *)this + 97) = (float)sub_47EFD0(v79, COERCE_FLOAT(1), v78, v77, v77, 0);
      goto LABEL_290;
    case 18:
      v80 = *(uint32_t *)this;
      *((uint32_t *)this + 2077) = **(uint32_t **)(a3 + 4);
      (*(void (/*thiscall*/ **)(char *, uint32_t))(v80 + 144))(this, *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4));
      v81 = *((uint32_t *)this + 1554);
      if ( *((int *)this + 2077) >= 2 )
        v82 = *(uint32_t *)(v81 + 16);
      else
        v82 = *(uint32_t *)(v81 + 12);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 196))(v82);
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(
        this,
        *((uint32_t *)this + 139) + 152 * (*((uint32_t *)this + 2077) + 2));
      v83 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 8);
      v84 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 8);
      if ( *((int *)this + 2077) < 2 )
      {
        v85 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 672))(this, 3);
        v263 = 1000.0 / (double)sub_4954C0(v85);
        *((uint32_t *)this + 2079) = (uint64_t)((double)sub_47E9D0(v83, 1u) * v263);
        *((uint32_t *)this + 2080) = (uint64_t)((double)sub_47E9D0(v83, 2u) * v263);
        *((uint32_t *)this + 2081) = (uint64_t)((double)sub_47E9D0(v83, 3u) * v263);
      }
      v86 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
      *((float *)this + 97) = (float)sub_47EFD0(v83, *((float *)this + 2077), v84, v86, v86, 0);
      v87 = sub_47E9D0(v83, 0);
      if ( *((int *)this + 2077) >= 2 )
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
          this,
          0,
          0,
          0,
          0,
          0,
          0);
      else
        (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
          this,
          0,
          v87,
          v87,
          0,
          -700,
          1);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 2, 1000, 1000);
      v88 = *(uint32_t *)this;
      v89 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(char *, int))(v88 + 896))(this, v89);
      v90 = *((uint32_t *)this + 2077);
      *((uint32_t *)this + 2078) = -1;
      *((uint32_t *)this + 2082) = -200;
      if ( v90 != 0 )
      {
        if ( v90 == 1 )
        {
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "SM_TRIPLE2",
            -1,
            0,
            0);
        }
        else if ( v90 == 2 )
        {
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "SM_TRIPLE3",
            -1,
            0,
            0);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "SM_TRIPLE1",
          -1,
          0,
          0);
      }
      v91 = *(uint32_t *)this;
      if ( *((uint32_t *)this + 2077) == 2 )
      {
        v92 = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(v91 + 1172))(this, 1, -1, 0, 0);
        (*(void (/*thiscall*/ **)(char *, int))(v91 + 212))(this, v92);
        v93 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);
      }
      else
      {
        v94 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(v91 + 1172))(this, 0, -1, 0, 0);
        (*(void (/*thiscall*/ **)(char *, int))(v91 + 212))(this, v94);
        v93 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
      }
      sub_406D60(v93);
      goto LABEL_290;
    case 19:
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, **(uint32_t **)(a3 + 4));
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 20));
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 760);
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 2, 1000, 1000);
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      if ( *((uint32_t *)this + 2084) == 0 )
      {
        LOBYTE(v288) = 10;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            v95 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/MomentarySlash.ani", 1);
          else
            v95 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/MomentarySlash.ani", 1);
        }
        else
        {
          v95 = 0;
        }
        LOBYTE(v288) = 0;
        *((uint32_t *)this + 2084) = v95;
      }
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
        this,
        1,
        *((uint32_t *)this + 2084),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "SM_BAL_READY",
        -1,
        0,
        0);
      v96 = *(uint32_t *)this;
      *(this + 8332) = 0;
      *(this + 8333) = 0;
      v97 = (void *)(*(int (/*thiscall*/ **)(char *, int))(v96 + 1172))(this, 2);
      sub_406D60(v97);
      v98 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
      v99 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 9);
      v100 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 9);
      *((float *)this + 97) = (float)sub_47EFD0(v100, 0.0, v99, v98, v98, 0);
      goto LABEL_290;
    case 20:
      *((uint32_t *)this + 2085) = **(uint32_t **)(a3 + 4);
      *(this + 8344) = 0;
      v101 = *(uint32_t *)(a3 + 4);
      if ( *(uint32_t *)(v101 + 4) != 4 )
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, *(uint32_t *)(v101 + 4));
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 24));
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 4, 1000, 1000);
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      v102 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 2085));
      (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 1160))(this, *((uint32_t *)this + 2085), v102);
      v103 = sub_4B1C40(v255);
      v255 = 1;
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 992))(this, v103);
      *((uint32_t *)this + 2090) = v103;
      for ( n = 1; n < 4; ++n )
      {
        v105 = *((uint32_t *)this + 2090) - *(uint32_t *)(sub_4924C0(n) + 48);
        *((uint32_t *)this + 2090) = v105;
      }
      v106 = 1000 * v105 / *((uint32_t *)this + 1664);
      v107 = 0;
      v286 = 15;
      Block[4] = nullptr;
      LOBYTE(Block[0]) = 0;
      *((uint32_t *)this + 2090) = v106;
      v108 = *((uint32_t *)this + 2085);
      LOBYTE(v288) = 11;
      if ( v108 == 20 )
      {
        if ( *((uint32_t *)this + 2092) == 0 )
        {
          LOBYTE(v288) = 12;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v109 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/NormalWave.ani", 1);
            else
              v109 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/NormalWave.ani", 1);
          }
          else
          {
            v109 = 0;
          }
          LOBYTE(v288) = 11;
          *((uint32_t *)this + 2092) = v109;
        }
        v110 = *(uint32_t *)this;
        *((uint32_t *)this + 2087) = *((uint32_t *)this + 2092);
        *((uint32_t *)this + 2088) = 20001;
        *((uint32_t *)this + 2089) = (*(int (/*thiscall*/ **)(char *, const char *))(v110 + 588))(
                                     this,
                                     "Particle/NormalWave.ptl");
        sub_4015C0("SM_WAVE", 7u);
        v249 = 0;
LABEL_216:
        v112 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(
                           this,
                           *((uint32_t *)this + 2085));
        goto LABEL_226;
      }
      if ( v108 == 21 )
      {
        if ( *((uint32_t *)this + 2093) == 0 )
        {
          LOBYTE(v288) = 13;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v111 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/IceWave.ani", 1);
            else
              v111 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/IceWave.ani", 1);
          }
          else
          {
            v111 = 0;
          }
          LOBYTE(v288) = 11;
          *((uint32_t *)this + 2093) = v111;
        }
        *((uint32_t *)this + 2087) = *((uint32_t *)this + 2093);
        *((uint32_t *)this + 2088) = 20002;
        *((uint32_t *)this + 2089) = 0;
        sub_406D60("SM_ICEWAVE");
        v249 = 1;
        goto LABEL_216;
      }
      if ( v108 != 22 )
        goto LABEL_227;
      if ( *((uint32_t *)this + 2094) == 0 )
      {
        LOBYTE(v288) = 14;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            v113 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/FireWave.ani", 1);
          else
            v113 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/FireWave.ani", 1);
        }
        else
        {
          v113 = 0;
        }
        LOBYTE(v288) = 11;
        *((uint32_t *)this + 2094) = v113;
      }
      v114 = *(uint32_t *)this;
      v249 = (unsigned int)"Particle/FireWave.ptl";
      *((uint32_t *)this + 2087) = *((uint32_t *)this + 2094);
      *((uint32_t *)this + 2088) = 20008;
      *((uint32_t *)this + 2089) = (*(int (/*thiscall*/ **)(char *))(v114 + 588))(this);
      sub_406D60("SM_FIREWAVE");
      v112 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 1160))(
                         this,
                         *((uint32_t *)this + 2085),
                         0);
LABEL_226:
      v107 = sub_47E9D0(v112, v249);
      v115 = (void **)Block[0];
      if ( v286 < 0x10 )
LABEL_227:
        v115 = Block;
      (*(void (/*thiscall*/ **)(char *, void **, int, uint32_t))(*(uint32_t *)this + 212))(this, v115, 13, 0);
      v246 = *((uint32_t *)this + 2085);
      v116 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1140))(this);
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 1160))(
        this,
        *((uint32_t *)this + 2085),
        2,
        v116);
      v280 = (double)(int)sub_47EF20(v246, -1, -1, 11, 0) * 0.0099999998;
      sub_4920E0(*((uint32_t **)this + 2087), v280, v280);
      v117 = 1000 * v103 / *((uint32_t *)this + 1664);
      LOBYTE(v288) = 0;
      *((uint32_t *)this + 2091) = v107 + v117;
      if ( v286 >= 0x10 )
        j__free(Block[0]);
LABEL_290:
      sub_4B89D0(a2, a3, a4, a5);
      switch ( a2 )
      {
        case 7:
          v165 = *(int **)(a3 + 4);
          if ( v165 != nullptr && (*(uint32_t *)(a3 + 8) - (int)v165) >> 2 != 0 )
            v166 = *v165;
          else
            v166 = -1;
          v167 = *(uint32_t *)this;
          *((uint32_t *)this + 2056) = v166;
          if ( (*(int (/*thiscall*/ **)(char *, int))(v167 + 1140))(this, 43) > 0 )
          {
            v168 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 43);
            (*(void (/*thiscall*/ **)(char *, int, uint32_t, int, int))(*(uint32_t *)this + 1160))(this, 43, 0, 1, v168);
            v169 = sub_47EED0(v255, v256, v257);
            (*(void (/*fastcall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 888))(
              this,
              (uint64_t)((double)*((int *)this + 1664) * (v169 * 0.0099999998 + 1.0)) >> 32,
              0);
          }
          if ( *((uint32_t *)this + 2056) == 17 )
          {
            v170 = *(uint32_t *)this;
            *((uint32_t *)this + 99) = 0;
            v171 = (*(int (/*thiscall*/ **)(char *))(v170 + 388))(this);
            v172 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 17);
            v173 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 17);
            *((float *)this + 97) = (float)sub_47EFD0(v173, 0.0, v172, v171, v171, 0);
          }
          v174 = *(uint32_t *)this;
          v175 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(
                   this,
                   0,
                   -1,
                   0,
                   0);
          (*(void (/*thiscall*/ **)(char *, int))(v174 + 212))(this, v175);
          v176 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
          sub_4015C0(v176, strlen((const char *)v176));
          break;
        case 8:
          sub_4014D0((std::_String_base *)(this + 7044), v281, 0, -1);
          if ( *((uint32_t *)this + 2054) != -1 )
            (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1328))(this, 0);
          if ( *((uint32_t *)this + 2054) == 46 )
          {
            (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 1216);
            v177 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 46);
            v178 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 46);
            v179 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
            *((float *)this + 97) = (float)sub_47EFD0(v177, 0.0, v178, v179, v179, 0);
            *((uint32_t *)this + 114) = sub_47EF20(1, v178, -1, -1, 11);
            v180 = sub_47EF20(2, v178, -1, -1, 11);
            v181 = *(uint32_t *)this;
            *((uint32_t *)this + 113) = v180;
            *(this + 8220) = 0;
            (*(void (/*thiscall*/ **)(char *, int, int))(v181 + 612))(this, 1, 1);
          }
          v182 = *(uint32_t *)this;
          v183 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(
                   this,
                   0,
                   -1,
                   0,
                   0);
          (*(void (/*thiscall*/ **)(char *, int))(v182 + 212))(this, v183);
          v184 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
          sub_4015C0(v184, strlen((const char *)v184));
          break;
        case 10:
          if ( *((uint32_t *)this + 1953) == 0 )
          {
            v265 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(
                               this,
                               *((uint32_t *)this + 1954));
            v289 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 1954));
            v191 = *((uint32_t *)this + 1954);
            switch ( v191 )
            {
              case 23:
                if ( *((uint32_t *)this + 2095) == 0 )
                {
                  v266 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 20;
                  if ( v266 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      v192 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodCharge1.ani", 1);
                    else
                      v192 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodCharge1.ani", 1);
                  }
                  else
                  {
                    v192 = 0;
                  }
                  LOBYTE(v288) = 0;
                  *((uint32_t *)this + 2095) = v192;
                  v267 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 21;
                  if ( v267 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      v193 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodCharge2.ani", 1);
                    else
                      v193 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodCharge2.ani", 1);
                  }
                  else
                  {
                    v193 = 0;
                  }
                  LOBYTE(v288) = 0;
                  *((uint32_t *)this + 2096) = v193;
                  v268 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 22;
                  if ( v268 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      v194 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodShoot1.ani", 1);
                    else
                      v194 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodShoot1.ani", 1);
                  }
                  else
                  {
                    v194 = 0;
                  }
                  LOBYTE(v288) = 0;
                  *((uint32_t *)this + 2097) = v194;
                  v269 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 23;
                  if ( v269 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      v195 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodShoot2.ani", 1);
                    else
                      v195 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodShoot2.ani", 1);
                  }
                  else
                  {
                    v195 = 0;
                  }
                  LOBYTE(v288) = 0;
                  *((uint32_t *)this + 2098) = v195;
                }
                v196 = *((uint32_t *)this + 1952);
                if ( v196 != 0 )
                {
                  if ( v196 == 1 )
                  {
                    (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                      this,
                      1,
                      *((uint32_t *)this + 2097),
                      0,
                      0,
                      0,
                      0);
                    (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                      this,
                      2,
                      *((uint32_t *)this + 2098),
                      0,
                      0,
                      0,
                      0);
                    if ( *((uint32_t *)this + 2099) == 0 )
                    {
                      v270 = operator new(0x80u);
                      LOBYTE(v288) = 24;
                      if ( v270 != nullptr )
                        v197 = (int *)sub_4D6810(0, 0, 1, 1);
                      else
                        v197 = nullptr;
                      *((uint32_t *)this + 2099) = v197;
                      v198 = *v197;
                      LOBYTE(v288) = 0;
                      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v198 + 64))(v197) + 36) = 0;
                    }
                    v199 = **((uint32_t **)this + 2099);
                    v200 = (uint64_t)((double)(*(int (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 740))(
                                                        this,
                                                        *((uint32_t *)this + 1956),
                                                        1,
                                                        1)
                                            * flt_9B934C);
                    v252 = (float)-(int)v200;
                    (*(void (/*fastcall*/ **)(uint32_t, uint32_t, uint32_t))(v199 + 120))(
                      *((uint32_t *)this + 2099),
                      HIDWORD(v200),
                      LODWORD(v252));
                    (*(void (/*thiscall*/ **)(uint32_t, char *, char *, uint32_t, uint32_t, uint32_t, int))(**((uint32_t **)this + 2099)
                                                                                                + 56))(
                      *((uint32_t *)this + 2099),
                      this,
                      this,
                      0,
                      0,
                      0,
                      -1);
                    v201 = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
                    if ( v201 != 0 )
                    {
                      if ( v201 == 1 )
                      {
                        v202 = (double)sub_47E9D0(v265, 1u);
                      }
                      else if ( v201 == 2 )
                      {
                        v202 = (double)sub_47E9D0(v265, 2u);
                      }
                      else
                      {
                        v202 = (double)sub_47E9D0(v265, 3u);
                      }
                      *((float *)this + 2100) = v202 * 0.0099999998;
                    }
                    else
                    {
                      *((uint32_t *)this + 2100) = 0;
                    }
                    (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                      this,
                      "SM_SACRIFICE_CAST",
                      -1,
                      0,
                      0);
                    (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                      this,
                      "SACRIFICE_BEGIN",
                      -1,
                      0,
                      0);
                  }
                }
                else
                {
                  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 912);
                  (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                    this,
                    1,
                    *((uint32_t *)this + 2095),
                    0,
                    0,
                    0,
                    0);
                  (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                    this,
                    2,
                    *((uint32_t *)this + 2096),
                    0,
                    0,
                    0,
                    0);
                }
                break;
              case 24:
                v203 = *((uint32_t *)this + 1952);
                if ( v203 != 0 )
                {
                  if ( v203 == 1 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
                  {
                    v204 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
                    v205 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 24);
                    v206 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 24);
                    v207 = sub_47EFD0(v206, 0.0, v205, v204, v204, 0);
                    (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
                      this,
                      20010,
                      v207,
                      0,
                      0,
                      0,
                      0,
                      0,
                      4,
                      0,
                      0,
                      0);
                    (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
                      this,
                      20009,
                      v207,
                      0,
                      0,
                      0,
                      50,
                      0,
                      4,
                      0,
                      0,
                      0);
                  }
                }
                else
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int))(*(uint32_t *)this + 212))(this, "SM_BLOOD_CAST", -1);
                  (*(void (/*thiscall*/ **)(char *, int, char *, uint32_t))(*(uint32_t *)this + 1160))(
                    this,
                    24,
                    this,
                    *((uint32_t *)this + 1955));
                  sub_47DCD0(0, 0);
                }
                break;
              case 34:
                if ( *((uint32_t *)this + 1952) == 1 )
                {
                  v271 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 25;
                  if ( v271 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      LOBYTE(v208) = (uint8_t)this + 108;
                    else
                      v208 = *((uint32_t *)this + 91);
                    v209 = sub_431920(v208, (char)"Effect/Animation/PinchHpRegen1.ani", 1);
                  }
                  else
                  {
                    v209 = 0;
                  }
                  LOBYTE(v288) = 0;
                  v272 = (void *)sub_44B6C0(284);
                  LOBYTE(v288) = 26;
                  if ( v272 != nullptr )
                    v210 = sub_44E1F0(v209, 1);
                  else
                    v210 = 0;
                  v211 = *((uint32_t *)this + 29);
                  LOBYTE(v288) = 0;
                  sub_45FE80(v211, v210, 2, 0, v210, (int)this, 0);
                  v212 = *(uint32_t *)v210;
                  v253 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);
                  (*(void (/*thiscall*/ **)(int))(v212 + 148))(v210);
                  v213 = *(uint32_t *)v210;
                  v214 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
                  v215 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, v214);
                  v216 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, v215);
                  (*(void (/*thiscall*/ **)(int, int))(v213 + 112))(v210, v216);
                  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v210 + 60))(v210, this);
                  sub_4A06D0(v253);
                  v273 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 27;
                  if ( v273 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      LOBYTE(v217) = (uint8_t)this + 108;
                    else
                      v217 = *((uint32_t *)this + 91);
                    v218 = sub_431920(v217, (char)"Effect/Animation/PinchHpRegen2.ani", 1);
                  }
                  else
                  {
                    v218 = 0;
                  }
                  LOBYTE(v288) = 0;
                  v274 = (void *)sub_44B6C0(284);
                  LOBYTE(v288) = 28;
                  if ( v274 != nullptr )
                    v219 = sub_44E1F0(v218, 1);
                  else
                    v219 = 0;
                  v220 = *((uint32_t *)this + 29);
                  LOBYTE(v288) = 0;
                  sub_45FE80(v220, v219, 2, 0, v219, (int)this, 0);
                  v221 = *(uint32_t *)v219;
                  v254 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);
                  (*(void (/*thiscall*/ **)(int))(v221 + 148))(v219);
                  v222 = *(uint32_t *)v219;
                  v223 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
                  v224 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, v223);
                  v225 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, v224);
                  (*(void (/*thiscall*/ **)(int, int))(v222 + 112))(v219, v225);
                  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)v219 + 60))(v219, this);
                  sub_4A06D0(v254);
                  v226 = v289;
                  v290 = sub_47EF20(0, v289, -1, -1, 11);
                  v227 = sub_47EF20(1, v226, -1, -1, 11);
                  v275 = operator new(0x80u);
                  LOBYTE(v288) = 29;
                  if ( v275 != nullptr )
                  {
                    v247 = (float)v290;
                    v228 = (int *)sub_4D6810(LODWORD(v247), v227, 1, 0);
                  }
                  else
                  {
                    v228 = nullptr;
                  }
                  v229 = *v228;
                  LOBYTE(v288) = 0;
                  (*(void (/*thiscall*/ **)(int *, char *, char *, uint32_t, uint32_t, uint32_t, int))(v229 + 56))(
                    v228,
                    this,
                    this,
                    0,
                    0,
                    0,
                    -1);
                }
                break;
              case 25:
                if ( *((uint32_t *)this + 1952) == 1 )
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                    this,
                    "SM_GHOST_KAZHAN",
                    -1,
                    0,
                    0);
                  if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
                  {
                    v230 = *(uint32_t *)this;
                    v231 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
                             this,
                             25,
                             0,
                             0,
                             122,
                             0,
                             0,
                             4,
                             0,
                             0,
                             0);
                    (*(void (/*thiscall*/ **)(char *, int, int))(v230 + 580))(this, 20011, v231);
                  }
                }
                break;
              case 36:
                if ( *((uint32_t *)this + 1952) == 1 )
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                    this,
                    "SM_GHOST_SAYA",
                    -1,
                    0,
                    0);
                  if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
                  {
                    v232 = *(uint32_t *)this;
                    v233 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
                             this,
                             36,
                             0,
                             0,
                             122,
                             0,
                             0,
                             4,
                             0,
                             0,
                             0);
                    (*(void (/*thiscall*/ **)(char *, int, int))(v232 + 580))(this, 20012, v233);
                  }
                }
                break;
              case 41:
                if ( *((uint32_t *)this + 1952) == 1 )
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                    this,
                    "SM_GHOST_BREMEN",
                    -1,
                    0,
                    0);
                  if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
                  {
                    v234 = *(uint32_t *)this;
                    v235 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
                             this,
                             41,
                             0,
                             0,
                             122,
                             0,
                             0,
                             4,
                             0,
                             0,
                             0);
                    (*(void (/*thiscall*/ **)(char *, int, int))(v234 + 580))(this, 20013, v235);
                  }
                }
                break;
              case 44:
                v236 = *((uint32_t *)this + 1952);
                if ( v236 != 0 )
                {
                  if ( v236 == 1 )
                  {
                    byte_9A0384 = 1;
                    if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
                    {
                      v237 = *(uint32_t *)this;
                      v238 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
                               this,
                               44,
                               0,
                               0,
                               0,
                               0,
                               0,
                               4,
                               0,
                               0,
                               0);
                      (*(void (/*thiscall*/ **)(char *, int, int))(v237 + 580))(this, 20014, v238);
                    }
                  }
                }
                else
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                    this,
                    "SM_TOMBSTONE",
                    -1,
                    0,
                    0);
                }
                break;
              default:
                if ( v191 == 32 && *((uint32_t *)this + 1952) == 0 )
                {
                  (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 996))(this);
                  if ( *((uint32_t *)this + 2101) == 0 )
                  {
                    v276 = (void *)sub_42FCB0(228);
                    LOBYTE(v288) = 30;
                    if ( v276 != nullptr )
                    {
                      if ( *((uint32_t *)this + 96) < 0x10u )
                        v239 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ReleaseWave1.ani", 1);
                      else
                        v239 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/ReleaseWave1.ani", 1);
                    }
                    else
                    {
                      v239 = 0;
                    }
                    LOBYTE(v288) = 0;
                    *((uint32_t *)this + 2101) = v239;
                    v277 = (void *)sub_42FCB0(228);
                    LOBYTE(v288) = 31;
                    if ( v277 != nullptr )
                    {
                      if ( *((uint32_t *)this + 96) < 0x10u )
                        v240 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ReleaseWave2.ani", 1);
                      else
                        v240 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/ReleaseWave2.ani", 1);
                    }
                    else
                    {
                      v240 = 0;
                    }
                    LOBYTE(v288) = 0;
                    *((uint32_t *)this + 2102) = v240;
                  }
                  (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                    this,
                    1,
                    *((uint32_t *)this + 2101),
                    0,
                    0,
                    0,
                    0);
                  (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                    this,
                    -1,
                    *((uint32_t *)this + 2102),
                    0,
                    0,
                    0,
                    0);
                  if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
                  {
                    v241 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 32);
                    if ( (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 32) <= 1 )
                      v242 = 1;
                    else
                      v242 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 32);
                    v243 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
                    v291 = *(uint32_t *)this;
                    v244 = sub_47EFD0(v241, 0.0, v242, v243, v243, 0);
                    (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v291 + 580))(
                      this,
                      20018,
                      v244,
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
                  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 612))(this, 1, 1);
                }
                break;
            }
          }
          break;
        case 12:
          if ( (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 11) > 0 )
          {
            v185 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 11);
            v186 = sub_47E9D0(v185, 0);
            v187 = *((uint32_t *)this + 30);
            *((uint32_t *)this + 2058) = 1000 * v186 / *((uint32_t *)this + 1664);
            *((uint32_t *)this + 2057) = sub_491C70(v187, 2);
            *((uint32_t *)this + 2059) = 0;
          }
          v188 = *(uint32_t *)this;
          v189 = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);
          (*(void (/*thiscall*/ **)(char *, int))(v188 + 212))(this, v189);
          v190 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);
          sub_4015C0(v190, strlen((const char *)v190));
          break;
        case 14:
          v245 = *((uint32_t *)this + 1991);
          switch ( v245 )
          {
            case 176:
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                this,
                "SM_ANCIENT_MEMORY",
                -1,
                0,
                0);
              break;
            case 175:
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                this,
                "SM_LEAP_BUFF",
                -1,
                0,
                0);
              break;
            case 30:
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                this,
                "SM_MOON_CURTAIN",
                -1,
                0,
                0);
              break;
            case 40:
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                this,
                "SM_CONGESTION",
                -1,
                0,
                0);
              break;
            case 38:
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                this,
                "SM_OVERDRIVE",
                -1,
                0,
                0);
              break;
            case 52:
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                this,
                "SM_QUAKE_WAVE",
                -1,
                0,
                0);
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
      if ( v284 >= 0x10 )
        j__free(v282);
      return;
    case 21:
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 1548));
      v118 = *((void **)this + 30);
      v119 = sub_42FC90(v118);
      sub_4AECE0(v118, v119 - 1);
      LOBYTE(a5) = 0;
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 2, 0, 1000, 1000);
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      sub_495890(0, 0);
      sub_494F20(2, 0.0);
      v120 = *(uint32_t *)this;
      v121 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(char *, int))(v120 + 896))(this, v121);
      v122 = *((uint32_t *)this + 139) + 1064;
      ++*((uint32_t *)this + 1724);
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, v122);
      v123 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
      v124 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 16);
      v125 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 16);
      v126 = sub_47EFD0(v125, 0.0, v124, v123, v123, 0);
      v127 = *(uint32_t *)this;
      *((float *)this + 97) = (float)v126;
      v128 = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(v127 + 1172))(this, 1, -1, 0, 0);
      (*(void (/*thiscall*/ **)(char *, int))(v127 + 212))(this, v128);
      v129 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);
      sub_406D60(v129);
      v130 = *(uint32_t *)this;
      *((uint32_t *)this + 2105) = 0;
      v131 = (*(int (/*thiscall*/ **)(char *))(v130 + 128))(this);
      v132 = *(uint32_t *)this;
      *((uint32_t *)this + 2106) = v131;
      *(this + 8413) = 0;
      (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(v132 + 212))(this, "SKYRADE_SWING", -1, 0, 0);
      goto LABEL_290;
    case 22:
      v133 = *(uint32_t *)this;
      *((uint32_t *)this + 2112) = **(uint32_t **)(a3 + 4);
      *((uint32_t *)this + 2113) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v133 + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 3, 1000, 1000);
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      sub_495890(2, 0);
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 28));
      if ( *((uint32_t *)this + 2112) != 0 )
      {
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 604))(this, 0);
        v134 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(a3 + 4) + 8), *(uint32_t *)(*(uint32_t *)(a3 + 4) + 12));
        v135 = __RTDynamicCast(v134, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *((uint32_t *)this + 2114) = v135;
        if ( v135 != 0 )
        {
          v136 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v135 + 120))(v135);
          v137 = *((uint32_t *)this + 2114);
          *((uint32_t *)this + 2115) = v136;
          v138 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v137 + 124))(v137);
          v139 = *((uint32_t *)this + 2114);
          *((uint32_t *)this + 2116) = v138;
          *((uint32_t *)this + 2117) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v139 + 128))(v139);
        }
        if ( *((uint32_t *)this + 2114) != 0 )
        {
          if ( *((uint32_t *)this + 2120) == 0 )
          {
            LOBYTE(v288) = 15;
            if ( operator new(0x60u) != nullptr )
              v140 = sub_5EE930(this);
            else
              v140 = 0;
            LOBYTE(v288) = 0;
            *((uint32_t *)this + 2120) = v140;
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, char *, uint32_t, uint32_t, uint32_t, int))(**((uint32_t **)this + 2120) + 56))(
            *((uint32_t *)this + 2120),
            *((uint32_t *)this + 2114),
            this,
            0,
            0,
            0,
            -1);
        }
        v141 = (char *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(this, *((uint32_t *)this + 2113));
        v142 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 2113));
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(
          this,
          *(uint32_t *)(*((uint32_t *)this + 1554) + 28));
        if ( *((uint32_t *)this + 2113) == 31 )
        {
          LOBYTE(a5) = 0;
          sub_4AECE0(*((void **)this + 30), 16);
          if ( *((uint32_t *)this + 2121) == 0 )
          {
            LOBYTE(v288) = 16;
            if ( sub_42FCB0(228) != 0 )
            {
              if ( *((uint32_t *)this + 96) < 0x10u )
                v143 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GrabBlastBlood.ani", 1);
              else
                v143 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GrabBlastBlood.ani", 1);
            }
            else
            {
              v143 = 0;
            }
            LOBYTE(v288) = 0;
            *((uint32_t *)this + 2121) = v143;
          }
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            1,
            *((uint32_t *)this + 2121),
            43,
            -90,
            0,
            0);
          v144 = sub_47E9D0(v141, 0);
          v145 = *(uint32_t *)this;
          *((uint32_t *)this + 2118) = v144;
          v250 = *((uint32_t *)this + 139) + 1520;
          *((uint32_t *)this + 2119) = 0;
          (*(void (/*thiscall*/ **)(char *, int))(v145 + 344))(this, v250);
          v146 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
          v147 = sub_47EFD0(v141, 0.0, v142, v146, v146, 0);
          v148 = *(uint32_t *)this;
          *((float *)this + 97) = (float)v147;
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(v148 + 212))(this, "BLOOD_HOLD", -1, 0, 0);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 1368);
        sub_4AECE0(*((void **)this + 30), 3);
        LOBYTE(a5) = 0;
      }
      goto LABEL_290;
    case 23:
      v149 = **(uint32_t **)(a3 + 4);
      *((uint32_t *)this + 2122) = v149;
      if ( v149 == 1 )
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "SM_GUE_CHARGE",
          12,
          0,
          0);
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "AIR_SWORD_READY",
          16,
          0,
          0);
      }
      else if ( v149 == 2 )
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "R_SM_GUE",
          11,
          0,
          0);
      }
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 4));
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 4, 1000, 1000);
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 596))(this, 0);
      if ( *((uint32_t *)this + 2122) == 2 )
        *((uint32_t *)this + 2123) = *(uint32_t *)(*(uint32_t *)(a3 + 4) + 4);
      v150 = *((uint32_t *)this + 2122);
      if ( v150 == 1 )
      {
        v151 = this + 8504;
        if ( *((uint32_t *)this + 2126) == 0 )
        {
          LOBYTE(v288) = 17;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v152 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWaveOnCharge1.ani", 1);
            else
              v152 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWaveOnCharge1.ani", 1);
          }
          else
          {
            v152 = 0;
          }
          *v151 = v152;
          LOBYTE(v288) = 18;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v153 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWaveOnCharge2.ani", 1);
            else
              v153 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWaveOnCharge2.ani", 1);
          }
          else
          {
            v153 = 0;
          }
          LOBYTE(v288) = 0;
          *((uint32_t *)this + 2127) = v153;
        }
        v154 = 0;
        do
        {
          v155 = v154 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            v154 + 1,
            *v151,
            0,
            0,
            0,
            0);
          v154 = v155;
          ++v151;
        }
        while ( v155 < 2 );
      }
      else if ( v150 == 2 )
      {
        if ( *((uint32_t *)this + 2125) == 0 )
        {
          LOBYTE(v288) = 19;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              v156 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWave.ani", 1);
            else
              v156 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWave.ani", 1);
          }
          else
          {
            v156 = 0;
          }
          LOBYTE(v288) = 0;
          *((uint32_t *)this + 2125) = v156;
        }
        (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
          this,
          1,
          *((uint32_t *)this + 2125),
          0,
          0,
          0,
          0);
      }
      v157 = *((uint32_t *)this + 2122);
      if ( v157 < 2 )
      {
        v160 = *((uint32_t *)this + 30);
        v161 = sub_491C70(v160, 0);
        sub_493A60(v160, v161);
        sub_4939E0(*((uint32_t *)this + 30), 1);
        LOBYTE(a5) = 0;
      }
      else if ( v157 == 2 )
      {
        sub_4AECE0(*((void **)this + 30), 1);
        sub_4939E0(*((uint32_t *)this + 30), 0);
        v158 = *(uint32_t *)this;
        LOBYTE(a5) = 0;
        v159 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
        (*(void (/*thiscall*/ **)(char *, int))(v158 + 212))(this, v159);
        *(this + 8516) = 0;
      }
      if ( *((uint32_t *)this + 2122) == 1 )
        *(this + 8496) = 0;
      if ( *((uint32_t *)this + 2122) == 0 )
      {
        v162 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 50);
        (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 1160))(this, 50, v162);
        v163 = sub_4B1C40(v255);
        v164 = *(uint32_t *)this;
        v255 = 0;
        v251 = 1000 * v163 / *((uint32_t *)this + 1664);
        *((uint32_t *)this + 2128) = v251;
        (*(void (/*thiscall*/ **)(char *, int))(v164 + 992))(this, v251);
      }
      goto LABEL_290;
    default:
      goto LABEL_290;
  }
}

