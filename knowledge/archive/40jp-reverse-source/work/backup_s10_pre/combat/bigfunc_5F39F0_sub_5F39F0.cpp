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
void /*thiscall*/ sub_5F39F0(char *this, int nArg2, int pArg3, float fArg4, float fArg5)
{
  int nArg22; // edi
  int v7; // ebx
  int pThis_474; // eax
  uint32_t *pThis_2068; // ebx
  int j; // edi
  uint32_t *pThis_2060; // ebx
  int k; // edi
  int v13; // ebx
  int pThis_4742; // eax
  int pThis_7A2; // eax
  int pThis_7A0; // eax
  uint32_t *pThis_20D4; // ebx
  int i; // edi
  int pThis_84A; // eax
  uint32_t *pThis_2138; // ebx
  int m; // edi
  int v22; // eax
  int v23; // edx
  uint32_t *pThis_488; // edi
  int v25; // edi
  int v26; // edi
  int pThis_98; // eax
  int v28; // eax
  int v29; // ebx
  int v30; // eax
  int v31; // ebx
  int v32; // edi
  int pThis_5B; // ecx
  int v34; // edi
  int pObj2; // edi
  int pThis_1D; // ecx
  int v37; // ebx
  int pThis_982; // eax
  int pThis_5B2; // ecx
  int v40; // edi
  int pObj; // edi
  int pThis_1D2; // ecx
  int v43; // ebx
  int pThis_983; // eax
  uint32_t *pThis_4882; // eax
  int v46; // ebx
  int *v47; // eax
  int v48; // edx
  int v49; // ebx
  int v50; // eax
  int v51; // edx
  int pThis_814; // eax
  int pThis_184; // edi
  char *pThis_4883; // eax
  int v55; // eax
  int v56; // ecx
  uint32_t *pThis_20682; // ebx
  int pThis_6C; // eax
  int pThis_6C2; // eax
  int v60; // eax
  int v61; // edi
  uint32_t *pThis_20602; // ebx
  int pThis_6C3; // eax
  int pThis_6C4; // eax
  int v65; // eax
  int v66; // edi
  int pThis_8142; // eax
  int pThis_1E; // edi
  int v69; // eax
  int pThis_8143; // eax
  int v71; // edi
  int pThis_494; // eax
  void *pThis_4942; // eax
  int v74; // edi
  int pThis_4943; // eax
  void *pThis_4944; // eax
  int pThis_1842; // edi
  int pThis_4746; // ebx
  char *pThis_4884; // eax
  int v80; // edx
  int pThis_612; // eax
  int v82; // eax
  char *pThis_4885; // edi
  int pThis_4747; // ebx
  int pThis_2A0; // eax
  int pThis_1843; // eax
  int v87; // eax
  int v88; // edi
  int pThis_984; // eax
  int pThis_81D; // eax
  int v91; // edi
  int v92; // eax
  void *pThis_4945; // eax
  int v94; // eax
  int pThis_6C5; // eax
  int v96; // eax
  void *v97; // eax
  int pThis_1844; // ebx
  int pThis_4748; // edi
  char *pThis_4886; // eax
  int v101; // ebx
  int pThis_4749; // eax
  int v103; // ebx
  int n; // edi
  int pThis_82A; // ecx
  int pThis_680; // eax
  int v107; // edi
  int pThis_825; // eax
  int pThis_6C6; // eax
  int v110; // edx
  int pThis_6C7; // eax
  uint32_t *pThis_4887; // eax
  int pThis_6C8; // eax
  int v114; // eax
  void **Block2; // eax
  int pThis_47410; // eax
  int pThis_6802; // eax
  void *pThis_1E3; // edi
  int v119; // eax
  int v120; // edi
  int pThis_987; // eax
  int pThis_8B; // eax
  int pThis_1848; // edi
  int pThis_47421; // ebx
  char *pThis_48814; // eax
  int v126; // eax
  int v127; // edi
  int v128; // eax
  void *pThis_49412; // eax
  int v130; // eax
  int v131; // eax
  int v132; // edx
  int v133; // edx
  int v134; // eax
  int pObj5; // eax
  int v136; // eax
  int pThis_842; // ecx
  int v138; // eax
  int pThis_8422; // ecx
  int v140; // eax
  char *pThis_48815; // ebx
  int pThis_47422; // edi
  int pThis_6C15; // eax
  int v144; // eax
  int v145; // edx
  int pThis_1849; // eax
  int v147; // eax
  int v148; // edx
  int v149; // eax
  int pThis_84A2; // eax
  uint32_t *pThis_21382; // ebx
  int pThis_6C16; // eax
  int pThis_6C17; // eax
  int v154; // eax
  int v155; // edi
  int pThis_6C18; // eax
  unsigned int pThis_84A3; // eax
  int v158; // ebx
  int pThis_49413; // eax
  int pThis_1E4; // ebx
  int v161; // eax
  int pThis_47423; // eax
  int v163; // eax
  int v164; // edx
  int *v165; // ecx
  int v166; // ecx
  int v167; // edx
  int pThis_47411; // eax
  double v169; // st7
  int v170; // edx
  int v171; // edi
  int pThis_47412; // ebx
  char *pThis_4888; // eax
  int v174; // edi
  int pThis_4946; // eax
  void *pThis_4947; // eax
  char *pThis_4889; // edi
  int pThis_47413; // ebx
  int pThis_1845; // eax
  int v180; // eax
  int v181; // edx
  int v182; // edi
  int pThis_4948; // eax
  void *pThis_4949; // eax
  uint32_t *pThis_48813; // eax
  int v186; // eax
  int pThis_1E2; // ecx
  int v188; // edi
  int pThis_49410; // eax
  void *pThis_49411; // eax
  int pThis_7A22; // eax
  int pThis_6C9; // eax
  int pThis_6C10; // eax
  int pThis_6C11; // eax
  int pThis_6C12; // eax
  int pThis_7A02; // eax
  int *v197; // eax
  int v198; // edx
  int pThis_833; // edi
  uint64_t pThis_2E4; // rax
  int v201; // eax
  double v202; // st7
  int pThis_7A03; // eax
  int pThis_1846; // edi
  int pThis_47415; // ebx
  char *pThis_48811; // eax
  int v207; // edi
  int pThis_5B3; // edx
  int v209; // edi
  int pObj3; // edi
  int pThis_1D3; // ecx
  int v212; // ebx
  int v213; // ebx
  int pThis_802; // eax
  int pThis_7C2; // eax
  int pThis_782; // eax
  int pThis_5B4; // ecx
  int v218; // edi
  int pObj4; // edi
  int pThis_1D4; // ecx
  int v221; // ebx
  int v222; // ebx
  int pThis_803; // eax
  int pThis_7C3; // eax
  int pThis_783; // eax
  int pThis_474142; // ebx
  int v227; // edi
  int *v228; // eax
  int v229; // edx
  int v230; // edi
  int pThis_47416; // eax
  int v232; // edi
  int pThis_47417; // eax
  int v234; // edi
  int pThis_47418; // eax
  int pThis_7A04; // eax
  int v237; // edi
  int pThis_47419; // eax
  int pThis_6C13; // eax
  int pThis_6C14; // eax
  char *pThis_48812; // ebx
  int pThis_47420; // edi
  int pThis_1847; // eax
  int v244; // eax
  int pThis_7C7; // eax
  int pThis_8252; // [esp+C4h] [ebp-88h]
  float v247; // [esp+C8h] [ebp-84h]
  int pThis_4745; // [esp+CCh] [ebp-80h]
  unsigned int v249; // [esp+D4h] [ebp-78h]
  int pThis_8B2; // [esp+D4h] [ebp-78h]
  int pThis_6803; // [esp+D4h] [ebp-78h]
  float v252; // [esp+D4h] [ebp-78h]
  int pThis_985; // [esp+D4h] [ebp-78h]
  int pThis_986; // [esp+D4h] [ebp-78h]
  int v255; // [esp+D8h] [ebp-74h]
  int v256; // [esp+DCh] [ebp-70h]
  int v257; // [esp+E0h] [ebp-6Ch]
  int pThis_80; // [esp+E4h] [ebp-68h]
  int pThis_78; // [esp+E8h] [ebp-64h]
  uint32_t *pThis_48816; // [esp+ECh] [ebp-60h]
  bool v261; // [esp+F3h] [ebp-59h]
  int pThis_4743; // [esp+F4h] [ebp-58h]
  float v263; // [esp+F4h] [ebp-58h]
  int pThis_667; // [esp+F8h] [ebp-54h]
  uint32_t *pThis_48810; // [esp+F8h] [ebp-54h]
  void *v266; // [esp+FCh] [ebp-50h]
  void *v267; // [esp+FCh] [ebp-50h]
  void *v268; // [esp+FCh] [ebp-50h]
  void *v269; // [esp+FCh] [ebp-50h]
  void *pMem; // [esp+FCh] [ebp-50h]
  void *v271; // [esp+FCh] [ebp-50h]
  void *v272; // [esp+FCh] [ebp-50h]
  void *v273; // [esp+FCh] [ebp-50h]
  void *v274; // [esp+FCh] [ebp-50h]
  void *pMem2; // [esp+FCh] [ebp-50h]
  void *v276; // [esp+FCh] [ebp-50h]
  void *v277; // [esp+FCh] [ebp-50h]
  int pThis_7C; // [esp+100h] [ebp-4Ch]
  int pThis_4744; // [esp+100h] [ebp-4Ch]
  float v280; // [esp+100h] [ebp-4Ch]
  char v281[4]; // [esp+104h] [ebp-48h] BYREF
  void *v282; // [esp+108h] [ebp-44h]
  int v283; // [esp+118h] [ebp-34h]
  unsigned int v284; // [esp+11Ch] [ebp-30h]
  void *Block[5]; // [esp+124h] [ebp-28h] BYREF
  unsigned int v286; // [esp+138h] [ebp-14h]
  int dword_796E502; // [esp+13Ch] [ebp-10h]
  int v288; // [esp+148h] [ebp-4h]
  int pThis_47414; // [esp+160h] [ebp+14h]
  int v290; // [esp+160h] [ebp+14h]
  int v291; // [esp+160h] [ebp+14h]

  dword_796E502 = dword_796E50;
  pThis_667 = *((uint32_t *)this + 1639);
  v284 = 15;
  v283 = 0;
  LOBYTE(v282) = 0;
  nArg22 = nArg2;
  v288 = 0;
  switch ( pThis_667 )
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
        pThis_7A2 = *((uint32_t *)this + 1954);
        switch ( pThis_7A2 )
        {
          case 23:
            pThis_7A0 = *((uint32_t *)this + 1952);
            if ( pThis_7A0 != 0 )
            {
              if ( pThis_7A0 == 1 )
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
            if ( nArg2 != 10 )
            {
              pThis_20D4 = this + 8404;
              for ( i = 2; i != 0; --i )
                (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_20D4++);
              (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);
              nArg22 = nArg2;
            }
            break;
          case 24:
            if ( nArg2 != 0 )
            {
              (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 24);
              sub_47DD30(this);
            }
            break;
          default:
            if ( pThis_7A2 == 44 && *((uint32_t *)this + 1952) == 1 && *((uint32_t *)this + 161) == 1 )
              (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);
            break;
        }
      }
      break;
    case 12:
      if ( *((int *)this + 2059) > 0 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
      {
        v7 = *(uint32_t *)this;
        pThis_474 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 11);
        (*(void (/*thiscall*/ **)(char *, int, int))(v7 + 1296))(this, 11, pThis_474);
      }
      break;
    case 15:
      if ( nArg2 != 15 )
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
          pThis_2068 = this + 8296;
          for ( j = 2; j != 0; --j )
            (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_2068++);
          nArg22 = nArg2;
        }
      }
      else
      {
        pThis_2060 = this + 8288;
        for ( k = 2; k != 0; --k )
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_2060++);
        nArg22 = nArg2;
      }
      break;
    case 18:
      if ( nArg2 != 18 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
      {
        v13 = *(uint32_t *)this;
        pThis_4742 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 8);
        (*(void (/*thiscall*/ **)(char *, int, int))(v13 + 1296))(this, 8, pThis_4742);
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
      if ( nArg2 != 22 )
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
      pThis_84A = *((uint32_t *)this + 2122);
      if ( pThis_84A != 0 )
      {
        if ( pThis_84A == 1 )
        {
          if ( *(this + 8496) != 0 )
          {
            (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, -1);
            (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 252))(this, 1, -1);
          }
          else
          {
            pThis_2138 = this + 8504;
            for ( m = 2; m != 0; --m )
              (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_2138++);
          }
          (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 216))(this, 12);
          (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 216))(this, 16);
          nArg22 = nArg2;
        }
        else if ( pThis_84A == 2 )
        {
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2125));
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 996))(this);
      }
      if ( nArg22 != 23 )
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 596))(this, 1);
      break;
    default:
      break;
  }
  if ( nArg22 == 24 )
  {
    nArg22 = 8;
    nArg2 = 8;
    pThis_667 = 24;
  }
  switch ( nArg22 )
  {
    case 8:
      sub_4014D0((std::_String_base *)v281, this + 7044, 0, -1);
      if ( pThis_667 != 8 )
      {
        if ( (unsigned int)sub_41C5A0(pArg3) <= 1 )
          v22 = -1;
        else
          v22 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
        *((uint32_t *)this + 2054) = v22;
      }
      if ( *((uint32_t *)this + 2054) == 46 )
        sub_406D60("SM_UPPER_SLASH");
      goto LABEL_290;
    case 15:
      if ( pThis_667 != 15 )
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
      *((uint32_t *)this + 2060) = **(uint32_t **)(pArg3 + 4);
      (*(void (/*thiscall*/ **)(char *, uint32_t))(v23 + 144))(this, *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12));
      pThis_488 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 1);
      pThis_48816 = pThis_488;
      pThis_4743 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 1);
      v256 = 0;
      v255 = 0;
      if ( *((uint32_t *)this + 2060) != 0 )
      {
        v261 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8) != 0;
        (*(void (/*thiscall*/ **)(char *, const char *, int))(*(uint32_t *)this + 212))(this, "SWD_GUARDED", -1);
        v25 = 0;
        *((uint32_t *)this + 2062) = 100;
        if ( !v261 )
        {
          v25 = sub_47EF20(0, pThis_4743, -1, -1, 11);
          *((uint32_t *)this + 2062) = sub_47EF20(1, pThis_4743, -1, -1, 11);
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
        pThis_98 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);
        v28 = sub_432E50(pThis_98);
        (*(void (/*thiscall*/ **)(char *, int))(v26 + 896))(this, v28);
        v29 = *(uint32_t *)(pArg3 + 4);
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
          pThis_78 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 120))(this) + v32;
        else
          pThis_78 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 120))(this) - v32;
        pThis_7C = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 124))(this);
        pThis_80 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this) + v31;
        LOBYTE(v288) = 1;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            LOBYTE(pThis_5B) = (uint8_t)this + 108;
          else
            pThis_5B = *((uint32_t *)this + 91);
          v34 = sub_431920(pThis_5B, (char)"Effect/Animation/GuardSpark.ani", 1);
        }
        else
        {
          v34 = 0;
        }
        LOBYTE(v288) = 2;
        if ( sub_44B6C0(284) != 0 )
          pObj2 = sub_44E1F0(v34, 1);
        else
          pObj2 = 0;
        pThis_1D = *((uint32_t *)this + 29);
        LOBYTE(v288) = 0;
        sub_45FE80(pThis_1D, pObj2, 2, 0, pObj2, (int)this, 0);
        v37 = *(uint32_t *)pObj2;
        pThis_982 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);
        (*(void (/*thiscall*/ **)(int, int))(v37 + 148))(pObj2, pThis_982);
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pThis_78, pThis_7C, pThis_80);
        LOBYTE(v288) = 3;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            LOBYTE(pThis_5B2) = (uint8_t)this + 108;
          else
            pThis_5B2 = *((uint32_t *)this + 91);
          v40 = sub_431920(pThis_5B2, (char)"Effect/Animation/GuardCircle.ani", 1);
        }
        else
        {
          v40 = 0;
        }
        LOBYTE(v288) = 4;
        if ( sub_44B6C0(284) != 0 )
          pObj = sub_44E1F0(v40, 1);
        else
          pObj = 0;
        pThis_1D2 = *((uint32_t *)this + 29);
        LOBYTE(v288) = 0;
        sub_45FE80(pThis_1D2, pObj, 2, 0, pObj, (int)this, 0);
        v43 = *(uint32_t *)pObj;
        pThis_983 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);
        (*(void (/*thiscall*/ **)(int, int))(v43 + 148))(pObj, pThis_983);
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 112))(pObj, pThis_78, pThis_7C, pThis_80);
        pThis_488 = pThis_48816;
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
      LOBYTE(fArg5) = 0;
      *((uint32_t *)this + 2061) = 0;
      if ( pThis_667 != 15 )
      {
        if ( *((uint32_t *)this + 2060) == 0 )
          *((uint32_t *)this + 2061) = sub_47E9D0(pThis_488, 0);
        if ( *((uint32_t *)this + 2060) == 1 )
        {
          *((uint32_t *)this + 2063) = -1;
        }
        else
        {
          pThis_4882 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 2);
          v46 = sub_47E9D0(pThis_4882, 0);
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
        v49 = sub_47EF20(4, pThis_4743, -1, -1, 11);
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
      v50 = **(uint32_t **)(pArg3 + 4);
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
      pThis_814 = *((uint32_t *)this + 2068);
      if ( pThis_814 == 0 || pThis_814 == 2 )
      {
        pThis_184 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
        pThis_4744 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 5);
        pThis_4883 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 5);
        *((float *)this + 97) = (float)sub_47EFD0(pThis_4883, 0.0, pThis_4744, pThis_184, pThis_184, 0);
      }
      if ( *((uint32_t *)this + 2068) == 2 )
      {
        pThis_4745 = (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 1140))(this, 6, -1);
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1160))(this);
        v55 = sub_47EF20(6, 0, pThis_4745, -1, 11);
        v56 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
        *((uint32_t *)this + 2070) = v56;
        *((float *)this + 97) = (double)(int)sub_423A80(0, v55, v56, dword_7959F8) + *((float *)this + 97);
      }
      if ( *((uint32_t *)this + 2068) == 1 )
      {
        pThis_20682 = this + 8296;
        if ( *((uint32_t *)this + 2074) == 0 )
        {
          LOBYTE(v288) = 6;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttackOnCharge1.ani", 1);
            else
              pThis_6C = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttackOnCharge1.ani", 1);
          }
          else
          {
            pThis_6C = 0;
          }
          *pThis_20682 = pThis_6C;
          LOBYTE(v288) = 7;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C2 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttackOnCharge2.ani", 1);
            else
              pThis_6C2 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttackOnCharge2.ani", 1);
          }
          else
          {
            pThis_6C2 = 0;
          }
          LOBYTE(v288) = 0;
          *((uint32_t *)this + 2075) = pThis_6C2;
        }
        v60 = 0;
        do
        {
          v61 = v60 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            v60 + 1,
            *pThis_20682,
            0,
            0,
            0,
            0);
          v60 = v61;
          ++pThis_20682;
        }
        while ( v61 < 2 );
      }
      else
      {
        pThis_20602 = this + 8288;
        if ( *((uint32_t *)this + 2072) == 0 )
        {
          LOBYTE(v288) = 8;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C3 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttack1.ani", 1);
            else
              pThis_6C3 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttack1.ani", 1);
          }
          else
          {
            pThis_6C3 = 0;
          }
          *pThis_20602 = pThis_6C3;
          LOBYTE(v288) = 9;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C4 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttack2.ani", 1);
            else
              pThis_6C4 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttack2.ani", 1);
          }
          else
          {
            pThis_6C4 = 0;
          }
          LOBYTE(v288) = 0;
          *((uint32_t *)this + 2073) = pThis_6C4;
        }
        v65 = 0;
        do
        {
          v66 = v65 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            v65 + 1,
            *pThis_20602,
            0,
            0,
            0,
            0);
          v65 = v66;
          ++pThis_20602;
        }
        while ( v66 < 2 );
      }
      pThis_8142 = *((uint32_t *)this + 2068);
      switch ( pThis_8142 )
      {
        case 0:
          *(this + 8276) = 0;
          goto LABEL_160;
        case 1:
          pThis_1E = *((uint32_t *)this + 30);
          v69 = sub_491C70(pThis_1E, 0);
          sub_493A60(pThis_1E, v69);
          sub_4939E0(*((uint32_t *)this + 30), 1);
          break;
        case 2:
          sub_4AECE0(*((void **)this + 30), 1);
          sub_4939E0(*((uint32_t *)this + 30), 0);
          break;
        default:
          goto LABEL_160;
      }
      LOBYTE(fArg5) = 0;
LABEL_160:
      if ( *((uint32_t *)this + 2068) != 2 )
        *(this + 8284) = 0;
      pThis_8143 = *((uint32_t *)this + 2068);
      if ( pThis_8143 == 0 || pThis_8143 == 2 )
      {
        v71 = *(uint32_t *)this;
        pThis_494 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
        (*(void (/*thiscall*/ **)(char *, int))(v71 + 212))(this, pThis_494);
        pThis_4942 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
        sub_4015C0(pThis_4942, strlen((const char *)pThis_4942));  // 【std::string构造赋值】
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
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, **(uint32_t **)(pArg3 + 4));
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
      pThis_4943 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
      (*(void (/*thiscall*/ **)(char *, int))(v74 + 212))(this, pThis_4943);
      pThis_4944 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
      sub_406D60(pThis_4944);
      pThis_1842 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
      pThis_4746 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 7);
      pThis_4884 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 7);
      *((float *)this + 97) = (float)sub_47EFD0(pThis_4884, COERCE_FLOAT(1), pThis_4746, pThis_1842, pThis_1842, 0);
      goto LABEL_290;
    case 18:
      v80 = *(uint32_t *)this;
      *((uint32_t *)this + 2077) = **(uint32_t **)(pArg3 + 4);
      (*(void (/*thiscall*/ **)(char *, uint32_t))(v80 + 144))(this, *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));
      pThis_612 = *((uint32_t *)this + 1554);
      if ( *((int *)this + 2077) >= 2 )
        v82 = *(uint32_t *)(pThis_612 + 16);
      else
        v82 = *(uint32_t *)(pThis_612 + 12);
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 196))(v82);
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(
        this,
        *((uint32_t *)this + 139) + 152 * (*((uint32_t *)this + 2077) + 2));
      pThis_4885 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 8);
      pThis_4747 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 8);
      if ( *((int *)this + 2077) < 2 )
      {
        pThis_2A0 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 672))(this, 3);
        v263 = 1000.0 / (double)sub_4954C0(pThis_2A0);
        *((uint32_t *)this + 2079) = (uint64_t)((double)sub_47E9D0(pThis_4885, 1u) * v263);
        *((uint32_t *)this + 2080) = (uint64_t)((double)sub_47E9D0(pThis_4885, 2u) * v263);
        *((uint32_t *)this + 2081) = (uint64_t)((double)sub_47E9D0(pThis_4885, 3u) * v263);
      }
      pThis_1843 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
      *((float *)this + 97) = (float)sub_47EFD0(pThis_4885, *((float *)this + 2077), pThis_4747, pThis_1843, pThis_1843, 0);
      v87 = sub_47E9D0(pThis_4885, 0);
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
      pThis_984 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(char *, int))(v88 + 896))(this, pThis_984);
      pThis_81D = *((uint32_t *)this + 2077);
      *((uint32_t *)this + 2078) = -1;
      *((uint32_t *)this + 2082) = -200;
      if ( pThis_81D != 0 )
      {
        if ( pThis_81D == 1 )
        {
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "SM_TRIPLE2",
            -1,
            0,
            0);
        }
        else if ( pThis_81D == 2 )
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
        pThis_4945 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);
      }
      else
      {
        v94 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(v91 + 1172))(this, 0, -1, 0, 0);
        (*(void (/*thiscall*/ **)(char *, int))(v91 + 212))(this, v94);
        pThis_4945 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
      }
      sub_406D60(pThis_4945);
      goto LABEL_290;
    case 19:
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, **(uint32_t **)(pArg3 + 4));
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
            pThis_6C5 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/MomentarySlash.ani", 1);
          else
            pThis_6C5 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/MomentarySlash.ani", 1);
        }
        else
        {
          pThis_6C5 = 0;
        }
        LOBYTE(v288) = 0;
        *((uint32_t *)this + 2084) = pThis_6C5;
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
      pThis_1844 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
      pThis_4748 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 9);
      pThis_4886 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 9);
      *((float *)this + 97) = (float)sub_47EFD0(pThis_4886, 0.0, pThis_4748, pThis_1844, pThis_1844, 0);
      goto LABEL_290;
    case 20:
      *((uint32_t *)this + 2085) = **(uint32_t **)(pArg3 + 4);
      *(this + 8344) = 0;
      v101 = *(uint32_t *)(pArg3 + 4);
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
      pThis_4749 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 2085));
      (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 1160))(this, *((uint32_t *)this + 2085), pThis_4749);
      v103 = sub_4B1C40(v255);
      v255 = 1;
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 992))(this, v103);
      *((uint32_t *)this + 2090) = v103;
      for ( n = 1; n < 4; ++n )
      {
        pThis_82A = *((uint32_t *)this + 2090) - *(uint32_t *)(sub_4924C0(n) + 48);
        *((uint32_t *)this + 2090) = pThis_82A;
      }
      pThis_680 = 1000 * pThis_82A / *((uint32_t *)this + 1664);
      v107 = 0;
      v286 = 15;
      Block[4] = nullptr;
      LOBYTE(Block[0]) = 0;
      *((uint32_t *)this + 2090) = pThis_680;
      pThis_825 = *((uint32_t *)this + 2085);
      LOBYTE(v288) = 11;
      if ( pThis_825 == 20 )
      {
        if ( *((uint32_t *)this + 2092) == 0 )
        {
          LOBYTE(v288) = 12;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C6 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/NormalWave.ani", 1);
            else
              pThis_6C6 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/NormalWave.ani", 1);
          }
          else
          {
            pThis_6C6 = 0;
          }
          LOBYTE(v288) = 11;
          *((uint32_t *)this + 2092) = pThis_6C6;
        }
        v110 = *(uint32_t *)this;
        *((uint32_t *)this + 2087) = *((uint32_t *)this + 2092);
        *((uint32_t *)this + 2088) = 20001;
        *((uint32_t *)this + 2089) = (*(int (/*thiscall*/ **)(char *, const char *))(v110 + 588))(
                                     this,
                                     "Particle/NormalWave.ptl");
        sub_4015C0("SM_WAVE", 7u);  // 【std::string构造赋值】
        v249 = 0;
LABEL_216:
        pThis_4887 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(
                           this,
                           *((uint32_t *)this + 2085));
        goto LABEL_226;
      }
      if ( pThis_825 == 21 )
      {
        if ( *((uint32_t *)this + 2093) == 0 )
        {
          LOBYTE(v288) = 13;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C7 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/IceWave.ani", 1);
            else
              pThis_6C7 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/IceWave.ani", 1);
          }
          else
          {
            pThis_6C7 = 0;
          }
          LOBYTE(v288) = 11;
          *((uint32_t *)this + 2093) = pThis_6C7;
        }
        *((uint32_t *)this + 2087) = *((uint32_t *)this + 2093);
        *((uint32_t *)this + 2088) = 20002;
        *((uint32_t *)this + 2089) = 0;
        sub_406D60("SM_ICEWAVE");
        v249 = 1;
        goto LABEL_216;
      }
      if ( pThis_825 != 22 )
        goto LABEL_227;
      if ( *((uint32_t *)this + 2094) == 0 )
      {
        LOBYTE(v288) = 14;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( *((uint32_t *)this + 96) < 0x10u )
            pThis_6C8 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/FireWave.ani", 1);
          else
            pThis_6C8 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/FireWave.ani", 1);
        }
        else
        {
          pThis_6C8 = 0;
        }
        LOBYTE(v288) = 11;
        *((uint32_t *)this + 2094) = pThis_6C8;
      }
      v114 = *(uint32_t *)this;
      v249 = (unsigned int)"Particle/FireWave.ptl";
      *((uint32_t *)this + 2087) = *((uint32_t *)this + 2094);
      *((uint32_t *)this + 2088) = 20008;
      *((uint32_t *)this + 2089) = (*(int (/*thiscall*/ **)(char *))(v114 + 588))(this);
      sub_406D60("SM_FIREWAVE");
      pThis_4887 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 1160))(
                         this,
                         *((uint32_t *)this + 2085),
                         0);
LABEL_226:
      v107 = sub_47E9D0(pThis_4887, v249);
      Block2 = (void **)Block[0];
      if ( v286 < 0x10 )
LABEL_227:
        Block2 = Block;
      (*(void (/*thiscall*/ **)(char *, void **, int, uint32_t))(*(uint32_t *)this + 212))(this, Block2, 13, 0);
      pThis_8252 = *((uint32_t *)this + 2085);
      pThis_47410 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1140))(this);
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 1160))(
        this,
        *((uint32_t *)this + 2085),
        2,
        pThis_47410);
      v280 = (double)(int)sub_47EF20(pThis_8252, -1, -1, 11, 0) * 0.0099999998;
      sub_4920E0(*((uint32_t **)this + 2087), v280, v280);
      pThis_6802 = 1000 * v103 / *((uint32_t *)this + 1664);
      LOBYTE(v288) = 0;
      *((uint32_t *)this + 2091) = v107 + pThis_6802;
      if ( v286 >= 0x10 )
        j__free(Block[0]);
LABEL_290:
      sub_4B89D0(nArg2, pArg3, fArg4, fArg5);
      switch ( nArg2 )
      {
        case 7:
          v165 = *(int **)(pArg3 + 4);
          if ( v165 != nullptr && (*(uint32_t *)(pArg3 + 8) - (int)v165) >> 2 != 0 )
            v166 = *v165;
          else
            v166 = -1;
          v167 = *(uint32_t *)this;
          *((uint32_t *)this + 2056) = v166;
          if ( (*(int (/*thiscall*/ **)(char *, int))(v167 + 1140))(this, 43) > 0 )
          {
            pThis_47411 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 43);
            (*(void (/*thiscall*/ **)(char *, int, uint32_t, int, int))(*(uint32_t *)this + 1160))(this, 43, 0, 1, pThis_47411);
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
            pThis_47412 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 17);
            pThis_4888 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 17);
            *((float *)this + 97) = (float)sub_47EFD0(pThis_4888, 0.0, pThis_47412, v171, v171, 0);
          }
          v174 = *(uint32_t *)this;
          pThis_4946 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(
                   this,
                   0,
                   -1,
                   0,
                   0);
          (*(void (/*thiscall*/ **)(char *, int))(v174 + 212))(this, pThis_4946);
          pThis_4947 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
          sub_4015C0(pThis_4947, strlen((const char *)pThis_4947));  // 【std::string构造赋值】
          break;
        case 8:
          sub_4014D0((std::_String_base *)(this + 7044), v281, 0, -1);
          if ( *((uint32_t *)this + 2054) != -1 )
            (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1328))(this, 0);
          if ( *((uint32_t *)this + 2054) == 46 )
          {
            (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 1216);
            pThis_4889 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 46);
            pThis_47413 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 46);
            pThis_1845 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
            *((float *)this + 97) = (float)sub_47EFD0(pThis_4889, 0.0, pThis_47413, pThis_1845, pThis_1845, 0);
            *((uint32_t *)this + 114) = sub_47EF20(1, pThis_47413, -1, -1, 11);
            v180 = sub_47EF20(2, pThis_47413, -1, -1, 11);
            v181 = *(uint32_t *)this;
            *((uint32_t *)this + 113) = v180;
            *(this + 8220) = 0;
            (*(void (/*thiscall*/ **)(char *, int, int))(v181 + 612))(this, 1, 1);
          }
          v182 = *(uint32_t *)this;
          pThis_4948 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(
                   this,
                   0,
                   -1,
                   0,
                   0);
          (*(void (/*thiscall*/ **)(char *, int))(v182 + 212))(this, pThis_4948);
          pThis_4949 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);
          sub_4015C0(pThis_4949, strlen((const char *)pThis_4949));  // 【std::string构造赋值】
          break;
        case 10:
          if ( *((uint32_t *)this + 1953) == 0 )
          {
            pThis_48810 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(
                               this,
                               *((uint32_t *)this + 1954));
            pThis_47414 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 1954));
            pThis_7A22 = *((uint32_t *)this + 1954);
            switch ( pThis_7A22 )
            {
              case 23:
                if ( *((uint32_t *)this + 2095) == 0 )
                {
                  v266 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 20;
                  if ( v266 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      pThis_6C9 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodCharge1.ani", 1);
                    else
                      pThis_6C9 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodCharge1.ani", 1);
                  }
                  else
                  {
                    pThis_6C9 = 0;
                  }
                  LOBYTE(v288) = 0;
                  *((uint32_t *)this + 2095) = pThis_6C9;
                  v267 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 21;
                  if ( v267 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      pThis_6C10 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodCharge2.ani", 1);
                    else
                      pThis_6C10 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodCharge2.ani", 1);
                  }
                  else
                  {
                    pThis_6C10 = 0;
                  }
                  LOBYTE(v288) = 0;
                  *((uint32_t *)this + 2096) = pThis_6C10;
                  v268 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 22;
                  if ( v268 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      pThis_6C11 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodShoot1.ani", 1);
                    else
                      pThis_6C11 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodShoot1.ani", 1);
                  }
                  else
                  {
                    pThis_6C11 = 0;
                  }
                  LOBYTE(v288) = 0;
                  *((uint32_t *)this + 2097) = pThis_6C11;
                  v269 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 23;
                  if ( v269 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      pThis_6C12 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodShoot2.ani", 1);
                    else
                      pThis_6C12 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodShoot2.ani", 1);
                  }
                  else
                  {
                    pThis_6C12 = 0;
                  }
                  LOBYTE(v288) = 0;
                  *((uint32_t *)this + 2098) = pThis_6C12;
                }
                pThis_7A02 = *((uint32_t *)this + 1952);
                if ( pThis_7A02 != 0 )
                {
                  if ( pThis_7A02 == 1 )
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
                      pMem = operator new(0x80u);
                      LOBYTE(v288) = 24;
                      if ( pMem != nullptr )
                        v197 = (int *)sub_4D6810(0, 0, 1, 1);
                      else
                        v197 = nullptr;
                      *((uint32_t *)this + 2099) = v197;
                      v198 = *v197;
                      LOBYTE(v288) = 0;
                      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v198 + 64))(v197) + 36) = 0;
                    }
                    pThis_833 = **((uint32_t **)this + 2099);
                    pThis_2E4 = (uint64_t)((double)(*(int (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 740))(
                                                        this,
                                                        *((uint32_t *)this + 1956),
                                                        1,
                                                        1)
                                            * flt_9B934C);
                    v252 = (float)-(int)pThis_2E4;
                    (*(void (/*fastcall*/ **)(uint32_t, uint32_t, uint32_t))(pThis_833 + 120))(
                      *((uint32_t *)this + 2099),
                      HIDWORD(pThis_2E4),
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
                    v201 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
                    if ( v201 != 0 )
                    {
                      if ( v201 == 1 )
                      {
                        v202 = (double)sub_47E9D0(pThis_48810, 1u);
                      }
                      else if ( v201 == 2 )
                      {
                        v202 = (double)sub_47E9D0(pThis_48810, 2u);
                      }
                      else
                      {
                        v202 = (double)sub_47E9D0(pThis_48810, 3u);
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
                pThis_7A03 = *((uint32_t *)this + 1952);
                if ( pThis_7A03 != 0 )
                {
                  if ( pThis_7A03 == 1 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
                  {
                    pThis_1846 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
                    pThis_47415 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 24);
                    pThis_48811 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 24);
                    v207 = sub_47EFD0(pThis_48811, 0.0, pThis_47415, pThis_1846, pThis_1846, 0);
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
                      LOBYTE(pThis_5B3) = (uint8_t)this + 108;
                    else
                      pThis_5B3 = *((uint32_t *)this + 91);
                    v209 = sub_431920(pThis_5B3, (char)"Effect/Animation/PinchHpRegen1.ani", 1);
                  }
                  else
                  {
                    v209 = 0;
                  }
                  LOBYTE(v288) = 0;
                  v272 = (void *)sub_44B6C0(284);
                  LOBYTE(v288) = 26;
                  if ( v272 != nullptr )
                    pObj3 = sub_44E1F0(v209, 1);
                  else
                    pObj3 = 0;
                  pThis_1D3 = *((uint32_t *)this + 29);
                  LOBYTE(v288) = 0;
                  sub_45FE80(pThis_1D3, pObj3, 2, 0, pObj3, (int)this, 0);
                  v212 = *(uint32_t *)pObj3;
                  pThis_985 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);
                  (*(void (/*thiscall*/ **)(int))(v212 + 148))(pObj3);
                  v213 = *(uint32_t *)pObj3;
                  pThis_802 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
                  pThis_7C2 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, pThis_802);
                  pThis_782 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, pThis_7C2);
                  (*(void (/*thiscall*/ **)(int, int))(v213 + 112))(pObj3, pThis_782);
                  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj3 + 60))(pObj3, this);
                  sub_4A06D0(pThis_985);
                  v273 = (void *)sub_42FCB0(228);
                  LOBYTE(v288) = 27;
                  if ( v273 != nullptr )
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )
                      LOBYTE(pThis_5B4) = (uint8_t)this + 108;
                    else
                      pThis_5B4 = *((uint32_t *)this + 91);
                    v218 = sub_431920(pThis_5B4, (char)"Effect/Animation/PinchHpRegen2.ani", 1);
                  }
                  else
                  {
                    v218 = 0;
                  }
                  LOBYTE(v288) = 0;
                  v274 = (void *)sub_44B6C0(284);
                  LOBYTE(v288) = 28;
                  if ( v274 != nullptr )
                    pObj4 = sub_44E1F0(v218, 1);
                  else
                    pObj4 = 0;
                  pThis_1D4 = *((uint32_t *)this + 29);
                  LOBYTE(v288) = 0;
                  sub_45FE80(pThis_1D4, pObj4, 2, 0, pObj4, (int)this, 0);
                  v221 = *(uint32_t *)pObj4;
                  pThis_986 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);
                  (*(void (/*thiscall*/ **)(int))(v221 + 148))(pObj4);
                  v222 = *(uint32_t *)pObj4;
                  pThis_803 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
                  pThis_7C3 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, pThis_803);
                  pThis_783 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, pThis_7C3);
                  (*(void (/*thiscall*/ **)(int, int))(v222 + 112))(pObj4, pThis_783);
                  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj4 + 60))(pObj4, this);
                  sub_4A06D0(pThis_986);
                  pThis_474142 = pThis_47414;
                  v290 = sub_47EF20(0, pThis_47414, -1, -1, 11);
                  v227 = sub_47EF20(1, pThis_474142, -1, -1, 11);
                  pMem2 = operator new(0x80u);
                  LOBYTE(v288) = 29;
                  if ( pMem2 != nullptr )
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
                    pThis_47416 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
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
                    (*(void (/*thiscall*/ **)(char *, int, int))(v230 + 580))(this, 20011, pThis_47416);
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
                    pThis_47417 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
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
                    (*(void (/*thiscall*/ **)(char *, int, int))(v232 + 580))(this, 20012, pThis_47417);
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
                    pThis_47418 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
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
                    (*(void (/*thiscall*/ **)(char *, int, int))(v234 + 580))(this, 20013, pThis_47418);
                  }
                }
                break;
              case 44:
                pThis_7A04 = *((uint32_t *)this + 1952);
                if ( pThis_7A04 != 0 )
                {
                  if ( pThis_7A04 == 1 )
                  {
                    byte_9A0384 = 1;
                    if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )
                    {
                      v237 = *(uint32_t *)this;
                      pThis_47419 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(
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
                      (*(void (/*thiscall*/ **)(char *, int, int))(v237 + 580))(this, 20014, pThis_47419);
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
                if ( pThis_7A22 == 32 && *((uint32_t *)this + 1952) == 0 )
                {
                  (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 996))(this);
                  if ( *((uint32_t *)this + 2101) == 0 )
                  {
                    v276 = (void *)sub_42FCB0(228);
                    LOBYTE(v288) = 30;
                    if ( v276 != nullptr )
                    {
                      if ( *((uint32_t *)this + 96) < 0x10u )
                        pThis_6C13 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ReleaseWave1.ani", 1);
                      else
                        pThis_6C13 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/ReleaseWave1.ani", 1);
                    }
                    else
                    {
                      pThis_6C13 = 0;
                    }
                    LOBYTE(v288) = 0;
                    *((uint32_t *)this + 2101) = pThis_6C13;
                    v277 = (void *)sub_42FCB0(228);
                    LOBYTE(v288) = 31;
                    if ( v277 != nullptr )
                    {
                      if ( *((uint32_t *)this + 96) < 0x10u )
                        pThis_6C14 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ReleaseWave2.ani", 1);
                      else
                        pThis_6C14 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/ReleaseWave2.ani", 1);
                    }
                    else
                    {
                      pThis_6C14 = 0;
                    }
                    LOBYTE(v288) = 0;
                    *((uint32_t *)this + 2102) = pThis_6C14;
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
                    pThis_48812 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 32);
                    if ( (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 32) <= 1 )
                      pThis_47420 = 1;
                    else
                      pThis_47420 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 32);
                    pThis_1847 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
                    v291 = *(uint32_t *)this;
                    v244 = sub_47EFD0(pThis_48812, 0.0, pThis_47420, pThis_1847, pThis_1847, 0);
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
            pThis_48813 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 11);
            v186 = sub_47E9D0(pThis_48813, 0);
            pThis_1E2 = *((uint32_t *)this + 30);
            *((uint32_t *)this + 2058) = 1000 * v186 / *((uint32_t *)this + 1664);
            *((uint32_t *)this + 2057) = sub_491C70(pThis_1E2, 2);
            *((uint32_t *)this + 2059) = 0;
          }
          v188 = *(uint32_t *)this;
          pThis_49410 = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);
          (*(void (/*thiscall*/ **)(char *, int))(v188 + 212))(this, pThis_49410);
          pThis_49411 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);
          sub_4015C0(pThis_49411, strlen((const char *)pThis_49411));  // 【std::string构造赋值】
          break;
        case 14:
          pThis_7C7 = *((uint32_t *)this + 1991);
          switch ( pThis_7C7 )
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
      pThis_1E3 = *((void **)this + 30);
      v119 = sub_42FC90(pThis_1E3);
      sub_4AECE0(pThis_1E3, v119 - 1);
      LOBYTE(fArg5) = 0;
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
      pThis_987 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(char *, int))(v120 + 896))(this, pThis_987);
      pThis_8B = *((uint32_t *)this + 139) + 1064;
      ++*((uint32_t *)this + 1724);
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, pThis_8B);
      pThis_1848 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
      pThis_47421 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 16);
      pThis_48814 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 16);
      v126 = sub_47EFD0(pThis_48814, 0.0, pThis_47421, pThis_1848, pThis_1848, 0);
      v127 = *(uint32_t *)this;
      *((float *)this + 97) = (float)v126;
      v128 = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(v127 + 1172))(this, 1, -1, 0, 0);
      (*(void (/*thiscall*/ **)(char *, int))(v127 + 212))(this, v128);
      pThis_49412 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);
      sub_406D60(pThis_49412);
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
      *((uint32_t *)this + 2112) = **(uint32_t **)(pArg3 + 4);
      *((uint32_t *)this + 2113) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
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
        v134 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12));
        pObj5 = __RTDynamicCast(v134, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *((uint32_t *)this + 2114) = pObj5;
        if ( pObj5 != 0 )
        {
          v136 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 120))(pObj5);
          pThis_842 = *((uint32_t *)this + 2114);
          *((uint32_t *)this + 2115) = v136;
          v138 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_842 + 124))(pThis_842);
          pThis_8422 = *((uint32_t *)this + 2114);
          *((uint32_t *)this + 2116) = v138;
          *((uint32_t *)this + 2117) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_8422 + 128))(pThis_8422);
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
        pThis_48815 = (char *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(this, *((uint32_t *)this + 2113));
        pThis_47422 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 2113));
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(
          this,
          *(uint32_t *)(*((uint32_t *)this + 1554) + 28));
        if ( *((uint32_t *)this + 2113) == 31 )
        {
          LOBYTE(fArg5) = 0;
          sub_4AECE0(*((void **)this + 30), 16);
          if ( *((uint32_t *)this + 2121) == 0 )
          {
            LOBYTE(v288) = 16;
            if ( sub_42FCB0(228) != 0 )
            {
              if ( *((uint32_t *)this + 96) < 0x10u )
                pThis_6C15 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GrabBlastBlood.ani", 1);
              else
                pThis_6C15 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GrabBlastBlood.ani", 1);
            }
            else
            {
              pThis_6C15 = 0;
            }
            LOBYTE(v288) = 0;
            *((uint32_t *)this + 2121) = pThis_6C15;
          }
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            1,
            *((uint32_t *)this + 2121),
            43,
            -90,
            0,
            0);
          v144 = sub_47E9D0(pThis_48815, 0);
          v145 = *(uint32_t *)this;
          *((uint32_t *)this + 2118) = v144;
          pThis_8B2 = *((uint32_t *)this + 139) + 1520;
          *((uint32_t *)this + 2119) = 0;
          (*(void (/*thiscall*/ **)(char *, int))(v145 + 344))(this, pThis_8B2);
          pThis_1849 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);
          v147 = sub_47EFD0(pThis_48815, 0.0, pThis_47422, pThis_1849, pThis_1849, 0);
          v148 = *(uint32_t *)this;
          *((float *)this + 97) = (float)v147;
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(v148 + 212))(this, "BLOOD_HOLD", -1, 0, 0);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 1368);
        sub_4AECE0(*((void **)this + 30), 3);
        LOBYTE(fArg5) = 0;
      }
      goto LABEL_290;
    case 23:
      v149 = **(uint32_t **)(pArg3 + 4);
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
        *((uint32_t *)this + 2123) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
      pThis_84A2 = *((uint32_t *)this + 2122);
      if ( pThis_84A2 == 1 )
      {
        pThis_21382 = this + 8504;
        if ( *((uint32_t *)this + 2126) == 0 )
        {
          LOBYTE(v288) = 17;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C16 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWaveOnCharge1.ani", 1);
            else
              pThis_6C16 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWaveOnCharge1.ani", 1);
          }
          else
          {
            pThis_6C16 = 0;
          }
          *pThis_21382 = pThis_6C16;
          LOBYTE(v288) = 18;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C17 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWaveOnCharge2.ani", 1);
            else
              pThis_6C17 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWaveOnCharge2.ani", 1);
          }
          else
          {
            pThis_6C17 = 0;
          }
          LOBYTE(v288) = 0;
          *((uint32_t *)this + 2127) = pThis_6C17;
        }
        v154 = 0;
        do
        {
          v155 = v154 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            v154 + 1,
            *pThis_21382,
            0,
            0,
            0,
            0);
          v154 = v155;
          ++pThis_21382;
        }
        while ( v155 < 2 );
      }
      else if ( pThis_84A2 == 2 )
      {
        if ( *((uint32_t *)this + 2125) == 0 )
        {
          LOBYTE(v288) = 19;
          if ( sub_42FCB0(228) != 0 )
          {
            if ( *((uint32_t *)this + 96) < 0x10u )
              pThis_6C18 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWave.ani", 1);
            else
              pThis_6C18 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWave.ani", 1);
          }
          else
          {
            pThis_6C18 = 0;
          }
          LOBYTE(v288) = 0;
          *((uint32_t *)this + 2125) = pThis_6C18;
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
      pThis_84A3 = *((uint32_t *)this + 2122);
      if ( pThis_84A3 < 2 )
      {
        pThis_1E4 = *((uint32_t *)this + 30);
        v161 = sub_491C70(pThis_1E4, 0);
        sub_493A60(pThis_1E4, v161);
        sub_4939E0(*((uint32_t *)this + 30), 1);
        LOBYTE(fArg5) = 0;
      }
      else if ( pThis_84A3 == 2 )
      {
        sub_4AECE0(*((void **)this + 30), 1);
        sub_4939E0(*((uint32_t *)this + 30), 0);
        v158 = *(uint32_t *)this;
        LOBYTE(fArg5) = 0;
        pThis_49413 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
        (*(void (/*thiscall*/ **)(char *, int))(v158 + 212))(this, pThis_49413);
        *(this + 8516) = 0;
      }
      if ( *((uint32_t *)this + 2122) == 1 )
        *(this + 8496) = 0;
      if ( *((uint32_t *)this + 2122) == 0 )
      {
        pThis_47423 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 50);
        (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 1160))(this, 50, pThis_47423);
        v163 = sub_4B1C40(v255);
        v164 = *(uint32_t *)this;
        v255 = 0;
        pThis_6803 = 1000 * v163 / *((uint32_t *)this + 1664);
        *((uint32_t *)this + 2128) = pThis_6803;
        (*(void (/*thiscall*/ **)(char *, int))(v164 + 992))(this, pThis_6803);
      }
      goto LABEL_290;
    default:
      goto LABEL_290;
  }
}

