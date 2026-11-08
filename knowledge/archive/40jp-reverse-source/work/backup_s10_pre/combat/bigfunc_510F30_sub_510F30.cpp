// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_510F30_sub_510F30.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x510F30）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 1620 行；字符串证据 4 条；外调 6 个
//   串: "CHARM_FIRE_USE"
//   串: "CHARM_ICE_USE"
//   串: "CHARM_MOON_USE"
//   串: "CHARM_SUN_USE"
//   调: sub_510F30 sub_4B3DF0 sub_50F990 sub_4D6810 sub_602DA0 sub_50F7F0
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x510F30 sub_510F30  size=10754
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_510F30(int Block, int nArg2)
{
  uint32_t *result; // eax
  int v4; // eax
  int v5; // esi
  char v6; // bl
  int v7; // eax
  int v8; // esi
  uint32_t *pMem44; // eax
  uint32_t *v10; // eax
  int v11; // esi
  uint32_t *pMem42; // eax
  uint32_t *v13; // eax
  uint32_t *pMem43; // eax
  uint32_t *v15; // eax
  void *pMem33; // eax
  int v17; // eax
  int v18; // esi
  int v19; // esi
  int v20; // esi
  int v21; // esi
  int v22; // esi
  int v23; // esi
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  void *pMem40; // eax
  uint32_t *pMem41; // eax
  uint32_t *v30; // eax
  uint32_t *pMem39; // eax
  uint32_t *v32; // eax
  char v33; // bl
  int v34; // eax
  int v35; // eax
  int v36; // eax
  uint32_t *pMem35; // eax
  uint32_t *v38; // eax
  uint32_t *pMem36; // eax
  uint32_t *v40; // eax
  uint32_t *pMem37; // eax
  uint32_t *v42; // eax
  uint32_t *pMem38; // eax
  uint32_t *v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  uint32_t *pMem22; // eax
  uint32_t *v51; // eax
  int v52; // eax
  uint32_t *pMem23; // eax
  uint32_t *v54; // eax
  uint32_t *pMem24; // eax
  uint32_t *v56; // eax
  uint32_t *pMem25; // eax
  uint32_t *v58; // eax
  uint32_t *pMem26; // eax
  uint32_t *v60; // eax
  uint32_t *pMem27; // eax
  uint32_t *v62; // eax
  uint32_t *pMem28; // eax
  uint32_t *v64; // eax
  uint32_t *pMem29; // eax
  uint32_t *v66; // eax
  uint32_t *pMem30; // eax
  uint32_t *v68; // eax
  uint32_t *pMem31; // eax
  uint32_t *v70; // eax
  uint32_t *pMem32; // eax
  uint32_t *v72; // eax
  int v73; // eax
  int v74; // eax
  int *v75; // eax
  int v76; // edx
  int v77; // eax
  uint32_t *pMem34; // esi
  uint32_t *pMem19; // eax
  uint32_t *v80; // eax
  uint32_t *pMem17; // eax
  uint32_t *v82; // eax
  uint32_t *pMem18; // eax
  uint32_t *v84; // eax
  uint32_t *pMem15; // eax
  uint32_t *v86; // eax
  uint32_t *pMem16; // eax
  uint32_t *v88; // eax
  uint32_t *pMem11; // eax
  uint32_t *v90; // eax
  uint32_t *pMem12; // eax
  uint32_t *v92; // eax
  uint32_t *pMem13; // eax
  uint32_t *v94; // eax
  uint32_t *pMem14; // eax
  uint32_t *v96; // eax
  uint32_t *pMem10; // eax
  uint32_t *v98; // eax
  uint32_t *pMem5; // eax
  uint32_t *v100; // eax
  uint32_t *pMem6; // eax
  uint32_t *v102; // eax
  uint32_t *pMem7; // eax
  uint32_t *v104; // eax
  uint32_t *pMem8; // eax
  uint32_t *v106; // eax
  uint32_t *pMem9; // eax
  uint32_t *v108; // eax
  uint32_t *pMem2; // eax
  uint32_t *v110; // eax
  uint32_t *pMem; // eax
  uint32_t *v112; // eax
  uint32_t *pMem3; // eax
  uint32_t *v114; // eax
  uint32_t *pMem4; // eax
  uint32_t *v116; // eax
  int v117; // eax
  uint32_t pBuf[20]; // [esp+Ch] [ebp-CCh] BYREF
  uint32_t pBuf2[20]; // [esp+5Ch] [ebp-7Ch] BYREF
  int v120; // [esp+ACh] [ebp-2Ch] BYREF
  char v121; // [esp+B0h] [ebp-28h]
  uint64_t v122[2]; // [esp+B1h] [ebp-27h] BYREF
  void *pMem21; // [esp+C4h] [ebp-14h]
  void *pMem20; // [esp+C8h] [ebp-10h]
  int v125; // [esp+D4h] [ebp-4h]
  void *Blocka; // [esp+E0h] [ebp+8h]
  void *Blockb; // [esp+E0h] [ebp+8h]
  void *Blockc; // [esp+E0h] [ebp+8h]
  void *Blockd; // [esp+E0h] [ebp+8h]
  void *Blocke; // [esp+E0h] [ebp+8h]
  void *Blockf; // [esp+E0h] [ebp+8h]
  void *Blockg; // [esp+E0h] [ebp+8h]
  void *Blockh; // [esp+E0h] [ebp+8h]
  void *Blocki; // [esp+E0h] [ebp+8h]
  void *Blockj; // [esp+E0h] [ebp+8h]
  void *Blockk; // [esp+E0h] [ebp+8h]
  void *Blockl; // [esp+E0h] [ebp+8h]
  void *Blockm; // [esp+E0h] [ebp+8h]
  void *Blockn; // [esp+E0h] [ebp+8h]
  void *Blocko; // [esp+E0h] [ebp+8h]
  void *Blockp; // [esp+E0h] [ebp+8h]
  void *Blockq; // [esp+E0h] [ebp+8h]
  void *Blockr; // [esp+E0h] [ebp+8h]
  void *Blocks; // [esp+E0h] [ebp+8h]
  void *Blockt; // [esp+E0h] [ebp+8h]
  void *Blocku; // [esp+E0h] [ebp+8h]
  void *Blockv; // [esp+E0h] [ebp+8h]
  void *Blockw; // [esp+E0h] [ebp+8h]
  void *Blockx; // [esp+E0h] [ebp+8h]
  void *Blocky; // [esp+E0h] [ebp+8h]
  void *Blockz; // [esp+E0h] [ebp+8h]
  void *Blockba; // [esp+E0h] [ebp+8h]
  void *Blockbb; // [esp+E0h] [ebp+8h]
  void *Blockbc; // [esp+E0h] [ebp+8h]
  void *Blockbd; // [esp+E0h] [ebp+8h]
  void *Blockbe; // [esp+E0h] [ebp+8h]
  void *Blockbf; // [esp+E0h] [ebp+8h]
  void *Blockbg; // [esp+E0h] [ebp+8h]
  void *Blockbh; // [esp+E0h] [ebp+8h]
  void *Blockbi; // [esp+E0h] [ebp+8h]
  void *Blockbj; // [esp+E0h] [ebp+8h]
  void *Blockbk; // [esp+E0h] [ebp+8h]
  void *Blockbl; // [esp+E0h] [ebp+8h]
  void *Blockbm; // [esp+E0h] [ebp+8h]
  void *Blockbn; // [esp+E0h] [ebp+8h]
  void *Blockbo; // [esp+E0h] [ebp+8h]
  void *Blockbp; // [esp+E0h] [ebp+8h]
  void *Blockbq; // [esp+E0h] [ebp+8h]
  void *Blockbr; // [esp+E0h] [ebp+8h]
  void *Blockbs; // [esp+E0h] [ebp+8h]
  void *Blockbt; // [esp+E0h] [ebp+8h]
  void *Blockbu; // [esp+E0h] [ebp+8h]
  void *Blockbv; // [esp+E0h] [ebp+8h]
  void *Blockbw; // [esp+E0h] [ebp+8h]
  void *Blockbx; // [esp+E0h] [ebp+8h]
  void *Blockby; // [esp+E0h] [ebp+8h]
  void *Blockbz; // [esp+E0h] [ebp+8h]
  void *Blockca; // [esp+E0h] [ebp+8h]
  void *Blockcb; // [esp+E0h] [ebp+8h]
  void *Blockcc; // [esp+E0h] [ebp+8h]
  void *Blockcd; // [esp+E0h] [ebp+8h]
  void *Blockce; // [esp+E0h] [ebp+8h]
  void *Blockcf; // [esp+E0h] [ebp+8h]
  void *Blockcg; // [esp+E0h] [ebp+8h]
  void *Blockch; // [esp+E0h] [ebp+8h]
  void *Blockci; // [esp+E0h] [ebp+8h]
  void *Blockcj; // [esp+E0h] [ebp+8h]
  void *Blockck; // [esp+E0h] [ebp+8h]
  void *Blockcl; // [esp+E0h] [ebp+8h]
  void *Blockcm; // [esp+E0h] [ebp+8h]

  memset(pBuf, 0, sizeof(pBuf));
  memset(pBuf2, 0, sizeof(pBuf2));
  if ( Block > 1055 )
  {
    if ( Block > 4052 )
    {
      if ( Block > 6505 )
      {
        if ( Block > 6513 )
        {
          if ( Block != 6514 )
          {
            if ( Block == 7099 )
            {
              pMem = operator new(0x7Cu);
              v125 = 166;
              if ( pMem != nullptr )
                v112 = sub_4B3DF0(pMem, 0, 0, 1112014848, 1800000, 1);
              else
                v112 = nullptr;
              v125 = -1;
              pBuf[0] = v112;
              pBuf2[0] = 26;
              Blockcj = operator new(0xC8u);
              v125 = 167;
              if ( Blockcj != nullptr )
                return (uint32_t *)sub_50F990(7099, pBuf, pBuf2, 1);
            }
            else if ( Block == 7100 )
            {
              pMem2 = operator new(0x7Cu);
              v125 = 168;
              v110 = pMem2 != nullptr ? sub_4B3DF0(pMem2, 1, 0, 1112014848, 1800000, 1) : nullptr;
              v125 = -1;
              pBuf[0] = v110;
              pBuf2[0] = 28;
              Blockci = operator new(0xC8u);
              v125 = 169;
              if ( Blockci != nullptr )
                return (uint32_t *)sub_50F990(7100, pBuf, pBuf2, 1);
            }
            return nullptr;
          }
          pMem3 = operator new(0x7Cu);
          v125 = 128;
          if ( pMem3 != nullptr )
            v114 = sub_4B3DF0(pMem3, 25, 1, 1092616192, 1800000, 1);
          else
            v114 = nullptr;
          v125 = -1;
          pBuf[0] = v114;
          pBuf2[0] = 46;
          pMem4 = operator new(0x7Cu);
          v125 = 129;
          if ( pMem4 != nullptr )
            v116 = sub_4B3DF0(pMem4, 26, 1, 1092616192, 1800000, 1);
          else
            v116 = nullptr;
          v125 = -1;
          pBuf[1] = v116;
          pBuf2[1] = 45;
          Blockck = operator new(0xC8u);
          v125 = 130;
          if ( Blockck != nullptr )
            sub_50F990(6514, pBuf, pBuf2, 2);
          v125 = -1;
LABEL_433:
          Blockcl = operator new(0x80u);
          v125 = 131;
          if ( Blockcl != nullptr )
            v117 = sub_4D6810(1141473280, 1000, 1, 1);
          else
            v117 = 0;
          v125 = -1;
          pBuf[0] = v117;
          pBuf2[0] = 0;
          Blockcm = operator new(0xC8u);
          v125 = 132;
          if ( Blockcm != nullptr )
            v18 = sub_50F990(Block, pBuf, pBuf2, 1);
          else
            v18 = 0;
          v125 = -1;
          sub_602DA0(2, 5.0, 8);
          return (uint32_t *)v18;
        }
        switch ( Block )
        {
          case 6513:
            pMem5 = operator new(0x7Cu);
            v125 = 122;
            if ( pMem5 != nullptr )
              v100 = sub_4B3DF0(pMem5, 0, 0, 1120403456, 60000, 1);
            else
              v100 = nullptr;
            v125 = -1;
            pBuf[0] = v100;
            pBuf2[0] = 26;
            pMem6 = operator new(0x7Cu);
            v125 = 123;
            if ( pMem6 != nullptr )
              v102 = sub_4B3DF0(pMem6, 1, 0, 1120403456, 60000, 1);
            else
              v102 = nullptr;
            v125 = -1;
            pBuf[1] = v102;
            pBuf2[1] = 28;
            pMem7 = operator new(0x7Cu);
            v125 = 124;
            if ( pMem7 != nullptr )
              v104 = sub_4B3DF0(pMem7, 3, 1, -1027080192, 60000, 1);
            else
              v104 = nullptr;
            v125 = -1;
            pBuf[2] = v104;
            pBuf2[2] = 27;
            pMem8 = operator new(0x7Cu);
            v125 = 125;
            if ( pMem8 != nullptr )
              v106 = sub_4B3DF0(pMem8, 5, 1, -1027080192, 60000, 1);
            else
              v106 = nullptr;
            v125 = -1;
            pBuf[3] = v106;
            pBuf2[3] = 30;
            pMem9 = operator new(0x7Cu);
            v125 = 126;
            if ( pMem9 != nullptr )
              v108 = sub_4B3DF0(pMem9, 20, 1, -1027080192, 60000, 1);
            else
              v108 = nullptr;
            v125 = -1;
            pBuf[4] = v108;
            pBuf2[4] = 23;
            Blockch = operator new(0xC8u);
            v125 = 127;
            if ( Blockch != nullptr )
              return (uint32_t *)sub_50F990(6513, pBuf, pBuf2, 5);
            return nullptr;
          case 6506:
LABEL_391:
            Blockcg = operator new(0xA4u);
            v125 = 26;
            if ( Blockcg != nullptr )
              return (uint32_t *)sub_50F7F0(Block);
            return nullptr;
          case 6511:
            Blockcf = operator new(0xC8u);
            v125 = 43;
            if ( Blockcf != nullptr )
            {
              pMem10 = operator new(0x7Cu);
              pMem20 = pMem10;
              LOBYTE(v125) = 44;
              if ( pMem10 != nullptr )
                v98 = sub_4B3DF0(pMem10, 12, 0, 1112014848, 60000, 1);
              else
                v98 = nullptr;
              LOBYTE(v125) = 43;
              return (uint32_t *)sub_50F850(6511, v98, 36);
            }
            return nullptr;
          default:
            break;
        }
        if ( Block != 6512 )
          return nullptr;
LABEL_384:
        Blockce = operator new(0xB0u);
        v125 = 63;
        if ( Blockce != nullptr )
          return (uint32_t *)sub_50FF30(Block, 0, 0, 0);
        return nullptr;
      }
      if ( Block == 6505 )
      {
        pMem11 = operator new(0x7Cu);
        v125 = 58;
        if ( pMem11 != nullptr )
          v90 = sub_4B3DF0(pMem11, 16, 0, 1097859072, 1800000, 1);
        else
          v90 = nullptr;
        v125 = -1;
        pBuf[0] = v90;
        pBuf2[0] = 40;
        pMem12 = operator new(0x7Cu);
        v125 = 59;
        if ( pMem12 != nullptr )
          v92 = sub_4B3DF0(pMem12, 17, 0, 1097859072, 1800000, 1);
        else
          v92 = nullptr;
        v125 = -1;
        pBuf[1] = v92;
        pBuf2[1] = 41;
        pMem13 = operator new(0x7Cu);
        v125 = 60;
        if ( pMem13 != nullptr )
          v94 = sub_4B3DF0(pMem13, 18, 0, 1097859072, 1800000, 1);
        else
          v94 = nullptr;
        v125 = -1;
        pBuf[2] = v94;
        pBuf2[2] = 42;
        pMem14 = operator new(0x7Cu);
        v125 = 61;
        if ( pMem14 != nullptr )
          v96 = sub_4B3DF0(pMem14, 19, 0, 1097859072, 1800000, 1);
        else
          v96 = nullptr;
        v125 = -1;
        pBuf[3] = v96;
        pBuf2[3] = 43;
        Blockcd = operator new(0xC8u);
        v125 = 62;
        if ( Blockcd != nullptr )
          return (uint32_t *)sub_50F990(6505, pBuf, pBuf2, 4);
        return nullptr;
      }
      if ( Block > 6501 )
      {
        if ( Block == 6502 )
        {
          pMem15 = operator new(0x7Cu);
          v125 = 142;
          if ( pMem15 != nullptr )
            v86 = sub_4B3DF0(pMem15, 8, 1, 1092616192, 600000, 1);
          else
            v86 = nullptr;
          v125 = -1;
          pBuf[0] = v86;
          pBuf2[0] = 47;
          pMem16 = operator new(0x7Cu);
          v125 = 143;
          if ( pMem16 != nullptr )
            v88 = sub_4B3DF0(pMem16, 7, 1, 1092616192, 600000, 1);
          else
            v88 = nullptr;
          v125 = -1;
          pBuf[1] = v88;
          pBuf2[1] = 48;
          Blockcc = operator new(0xC8u);
          v125 = 144;
          if ( Blockcc != nullptr )
            return (uint32_t *)sub_50F990(6502, pBuf, pBuf2, 2);
        }
        else if ( Block == 6503 )
        {
          pMem17 = operator new(0x7Cu);
          v125 = 145;
          if ( pMem17 != nullptr )
            v82 = sub_4B3DF0(pMem17, 4, 1, 1092616192, 1800000, 1);
          else
            v82 = nullptr;
          v125 = -1;
          pBuf[0] = v82;
          pBuf2[0] = 49;
          pMem18 = operator new(0x7Cu);
          v125 = 146;
          if ( pMem18 != nullptr )
            v84 = sub_4B3DF0(pMem18, 5, 1, 1092616192, 1800000, 1);
          else
            v84 = nullptr;
          v125 = -1;
          pBuf[1] = v84;
          pBuf2[1] = 50;
          Blockcb = operator new(0xC8u);
          v125 = 147;
          if ( Blockcb != nullptr )
            return (uint32_t *)sub_50F990(6503, pBuf, pBuf2, 2);
        }
        else
        {
          pMem19 = operator new(0x7Cu);
          v125 = 111;
          if ( pMem19 != nullptr )
            v80 = sub_4B3DF0(pMem19, 22, 0, 1088421888, 600000, 1);
          else
            v80 = nullptr;
          v125 = -1;
          pBuf[0] = v80;
          pBuf2[0] = 44;
          Blockca = operator new(0xC8u);
          v125 = 112;
          if ( Blockca != nullptr )
            return (uint32_t *)sub_50F990(6504, pBuf, pBuf2, 1);
        }
        return nullptr;
      }
      if ( Block == 6501 )
      {
        Blockbz = operator new(0xB0u);
        v125 = 141;
        if ( Blockbz != nullptr )
          return (uint32_t *)sub_50FC00(6501, 1, 50, 100);
        return nullptr;
      }
      if ( Block > 4102 )
      {
        if ( Block == 6500 )
        {
          Blockby = operator new(0xB0u);
          v125 = 140;
          if ( Blockby != nullptr )
            return (uint32_t *)sub_50FC00(6500, 0, 50, 100);
        }
        return nullptr;
      }
      if ( Block < 4087 && (Block < 4079 || Block > 4082) )
        return nullptr;
    }
    else if ( Block < 4041 )
    {
      switch ( Block )
      {
        case 1056:
          pMem20 = operator new(0xC8u);
          v6 = 79;
          v125 = 79;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = 80;
          if ( pMem21 == nullptr )
            goto LABEL_325;
          v7 = sub_4D6810(1128136704, 1500, 1, 1);
          goto LABEL_326;
        case 1057:
          pMem20 = operator new(0xC8u);
          v6 = -104;
          v125 = 152;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x64u);
          LOBYTE(v125) = -103;
          if ( pMem21 == nullptr )
            goto LABEL_321;
          v7 = sub_50F270(70, 1000);
          goto LABEL_326;
        case 1058:
          pMem20 = operator new(0xC8u);
          v6 = -100;
          v125 = 156;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x64u);
          LOBYTE(v125) = -99;
          if ( pMem21 == nullptr )
            goto LABEL_325;
LABEL_324:
          v7 = sub_50F270(120, 1500);
          goto LABEL_326;
        case 1059:
          pMem20 = operator new(0xC8u);
          v6 = 83;
          v125 = 83;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = 84;
          if ( pMem21 == nullptr )
            goto LABEL_233;
          v7 = sub_4D6810(1133903872, 700, 1, 1);
          goto LABEL_326;
        case 1060:
          pMem20 = operator new(0xC8u);
          v6 = 85;
          v125 = 85;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x64u);
          LOBYTE(v125) = 86;
          if ( pMem21 == nullptr )
            goto LABEL_321;
          v7 = sub_50F270(195, 700);
          goto LABEL_326;
        case 1061:
          Blockbf = operator new(0x80u);
          v125 = 87;
          if ( Blockbf != nullptr )
            v46 = sub_4D6810(1128792064, 1000, 1, 1);
          else
            v46 = 0;
          v125 = -1;
          pBuf[0] = v46;
          pBuf2[0] = 0;
          Blockbg = operator new(0x64u);
          v125 = 88;
          if ( Blockbg != nullptr )
            v47 = sub_50F270(95, 1000);
          else
            v47 = 0;
          v125 = -1;
          pBuf[1] = v47;
          pBuf2[1] = 0;
          Blockbh = operator new(0xC8u);
          v125 = 89;
          if ( Blockbh != nullptr )
          {
            v18 = sub_50F990(Block, pBuf, pBuf2, 2);
            v125 = -1;
            sub_602DA0(8, 100.0, 3);
          }
          else
          {
            v18 = 0;
            v125 = -1;
            sub_602DA0(8, 100.0, 3);
          }
          return (uint32_t *)v18;
        case 1062:
          pMem20 = operator new(0xC8u);
          v6 = 90;
          v125 = 90;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = 91;
          if ( pMem21 == nullptr )
            goto LABEL_321;
          v7 = sub_4D6810(1120403456, 1000, 1, 1);
          goto LABEL_326;
        case 1063:
          pMem20 = operator new(0xC8u);
          v6 = 92;
          v125 = 92;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = 93;
          if ( pMem21 == nullptr )
            goto LABEL_325;
          v7 = sub_4D6810(1130102784, 700, 1, 1);
          goto LABEL_326;
        case 1064:
          pMem20 = operator new(0xC8u);
          v6 = 94;
          v125 = 94;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = 95;
          if ( pMem21 == nullptr )
            goto LABEL_233;
          v7 = sub_4D6810(1133576192, 700, 1, 1);
          goto LABEL_326;
        case 1065:
          pMem20 = operator new(0xC8u);
          v6 = 96;
          v125 = 96;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x64u);
          LOBYTE(v125) = 97;
          if ( pMem21 == nullptr )
            goto LABEL_321;
          v7 = sub_50F270(80, 700);
          goto LABEL_326;
        case 1066:
          pMem20 = operator new(0xC8u);
          v6 = 98;
          v125 = 98;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x64u);
          LOBYTE(v125) = 99;
          if ( pMem21 == nullptr )
            goto LABEL_325;
          v7 = sub_50F270(95, 700);
          goto LABEL_326;
        case 1067:
          Blockbi = operator new(0xC8u);
          v125 = 100;
          if ( Blockbi == nullptr )
            return nullptr;
          pMem20 = operator new(0x64u);
          LOBYTE(v125) = 101;
          if ( pMem20 != nullptr )
          {
            v48 = sub_50F270(150, 700);
            LOBYTE(v125) = 100;
            return (uint32_t *)sub_50F850(Block, v48, 0);
          }
          else
          {
            LOBYTE(v125) = 100;
            return (uint32_t *)sub_50F850(Block, 0, 0);
          }
        case 1068:
          Blockbj = operator new(0x80u);
          v125 = 102;
          if ( Blockbj != nullptr )
            v49 = sub_4D6810(1133903872, 1000, 1, 1);
          else
            v49 = 0;
          v125 = -1;
          pBuf[0] = v49;
          pBuf2[0] = 0;
          pMem22 = operator new(0x7Cu);
          v125 = 103;
          if ( pMem22 != nullptr )
            v51 = sub_4B3DF0(pMem22, 5, 1, 1101004800, 20000, 1);
          else
            v51 = nullptr;
          v125 = -1;
          pBuf[1] = v51;
          pBuf2[1] = 30;
          Blockbk = operator new(0xC8u);
          v125 = 104;
          if ( Blockbk == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);
        case 1069:
          Blockbl = operator new(0x64u);
          v125 = 105;
          if ( Blockbl != nullptr )
            v52 = sub_50F270(145, 1000);
          else
            v52 = 0;
          v125 = -1;
          pBuf[0] = v52;
          pBuf2[0] = 0;
          pMem23 = operator new(0x7Cu);
          v125 = 106;
          if ( pMem23 != nullptr )
            v54 = sub_4B3DF0(pMem23, 2, 0, 1106247680, 60000, 1);
          else
            v54 = nullptr;
          v125 = -1;
          pBuf[1] = v54;
          pBuf2[1] = 29;
          Blockbm = operator new(0xC8u);
          v125 = 107;
          if ( Blockbm == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);
        case 1070:
          pMem24 = operator new(0x7Cu);
          v125 = 108;
          if ( pMem24 != nullptr )
            v56 = sub_4B3DF0(pMem24, 3, 0, 1101004800, 60000, 1);
          else
            v56 = nullptr;
          v125 = -1;
          pBuf[0] = v56;
          pBuf2[0] = 26;
          pMem25 = operator new(0x7Cu);
          v125 = 109;
          if ( pMem25 != nullptr )
            v58 = sub_4B3DF0(pMem25, 22, 0, 1101004800, 60000, 1);
          else
            v58 = nullptr;
          v125 = -1;
          pBuf[1] = v58;
          pBuf2[1] = 24;
          Blockbn = operator new(0xC8u);
          v125 = 110;
          if ( Blockbn == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);
        case 1071:
          pMem26 = operator new(0x7Cu);
          v125 = 113;
          if ( pMem26 != nullptr )
            v60 = sub_4B3DF0(pMem26, 1, 0, 1101004800, 60000, 1);
          else
            v60 = nullptr;
          v125 = -1;
          pBuf[0] = v60;
          pBuf2[0] = 28;
          pMem27 = operator new(0x7Cu);
          v125 = 114;
          if ( pMem27 != nullptr )
            v62 = sub_4B3DF0(pMem27, 21, 0, 1112014848, 60000, 1);
          else
            v62 = nullptr;
          v125 = -1;
          pBuf[1] = v62;
          pBuf2[1] = 25;
          Blockbo = operator new(0xC8u);
          v125 = 115;
          if ( Blockbo == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);
        case 1072:
          pMem28 = operator new(0x7Cu);
          v125 = 116;
          if ( pMem28 != nullptr )
            v64 = sub_4B3DF0(pMem28, 0, 0, 1106247680, 60000, 1);
          else
            v64 = nullptr;
          v125 = -1;
          pBuf[0] = v64;
          pBuf2[0] = 26;
          pMem29 = operator new(0x7Cu);
          v125 = 117;
          if ( pMem29 != nullptr )
            v66 = sub_4B3DF0(pMem29, 1, 0, 1106247680, 60000, 1);
          else
            v66 = nullptr;
          v125 = -1;
          pBuf[1] = v66;
          pBuf2[1] = 28;
          pMem30 = operator new(0x7Cu);
          v125 = 118;
          if ( pMem30 != nullptr )
            v68 = sub_4B3DF0(pMem30, 3, 1, -1027080192, 60000, 1);
          else
            v68 = nullptr;
          v125 = -1;
          pBuf[2] = v68;
          pBuf2[2] = 27;
          pMem31 = operator new(0x7Cu);
          v125 = 119;
          if ( pMem31 != nullptr )
            v70 = sub_4B3DF0(pMem31, 5, 1, -1027080192, 60000, 1);
          else
            v70 = nullptr;
          v125 = -1;
          pBuf[3] = v70;
          pBuf2[3] = 30;
          pMem32 = operator new(0x7Cu);
          v125 = 120;
          if ( pMem32 != nullptr )
            v72 = sub_4B3DF0(pMem32, 20, 1, -1027080192, 60000, 1);
          else
            v72 = nullptr;
          v125 = -1;
          pBuf[4] = v72;
          pBuf2[4] = 23;
          Blockbp = operator new(0xC8u);
          v125 = 121;
          if ( Blockbp == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 5);
        case 1074:
          Blockbe = operator new(0xB0u);
          v125 = 7;
          if ( Blockbe == nullptr )
            return nullptr;
          return (uint32_t *)sub_50FF30(Block, 0, 300, 0);
        case 1075:
          pMem20 = operator new(0xC8u);
          v6 = 12;
          v125 = 12;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = 13;
          if ( pMem21 != nullptr )
            v7 = sub_4D6810(1133248512, 2000, 1, 1);
          else
LABEL_233:
            v7 = 0;
          goto LABEL_326;
        case 1076:
          pMem20 = operator new(0xC8u);
          v6 = 14;
          v125 = 14;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x64u);
          LOBYTE(v125) = 15;
          if ( pMem21 == nullptr )
            goto LABEL_321;
          v7 = sub_50F270(150, 700);
          goto LABEL_326;
        case 1077:
          pMem20 = operator new(0xC8u);
          v6 = 8;
          v125 = 8;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = 9;
          if ( pMem21 != nullptr )
            v7 = sub_4D6810(1133248512, 100, 1, 1);
          else
LABEL_321:
            v7 = 0;
          goto LABEL_326;
        case 1078:
          pMem20 = operator new(0xC8u);
          v6 = 10;
          v125 = 10;
          if ( pMem20 == nullptr )
            return nullptr;
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = 11;
          if ( pMem21 != nullptr )
            v7 = sub_4D6810(1136525312, 100, 1, 1);
          else
LABEL_325:
            v7 = 0;
          goto LABEL_326;
        case 1079:
          goto LABEL_433;
        case 1080:
          Blockbq = operator new(0x80u);
          v125 = 133;
          if ( Blockbq != nullptr )
            v73 = sub_4D6810(1141473280, 1000, 1, 1);
          else
            v73 = 0;
          v125 = -1;
          pBuf[0] = v73;
          pBuf2[0] = 0;
          Blockbr = operator new(0xC8u);
          v125 = 134;
          if ( Blockbr != nullptr )
          {
            v18 = sub_50F990(Block, pBuf, pBuf2, 1);
            v125 = -1;
            sub_602DA0(15, 10.0, 8);
          }
          else
          {
            v18 = 0;
            v125 = -1;
            sub_602DA0(15, 10.0, 8);
          }
          return (uint32_t *)v18;
        case 1081:
          Blockbs = operator new(0x64u);
          v125 = 135;
          if ( Blockbs != nullptr )
            v74 = sub_50F270(250, 1000);
          else
            v74 = 0;
          v125 = -1;
          pBuf[0] = v74;
          pBuf2[0] = 0;
          Blockbt = operator new(0xC8u);
          v125 = 136;
          if ( Blockbt != nullptr )
          {
            v18 = sub_50F990(Block, pBuf, pBuf2, 1);
            v125 = -1;
            sub_602DA0(8, 10.0, 5);
          }
          else
          {
            v18 = 0;
            v125 = -1;
            sub_602DA0(8, 10.0, 5);
          }
          return (uint32_t *)v18;
        case 1082:
          Blockbu = operator new(0x84u);
          v125 = 137;
          if ( Blockbu != nullptr )
            v75 = (int *)sub_510140(1, 2, 3);
          else
            v75 = nullptr;
          pBuf[0] = v75;
          v76 = *v75;
          v125 = -1;
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v76 + 64))(v75) + 40) = 60000;
          pBuf2[0] = 37;
          Blockbv = operator new(0x84u);
          v125 = 138;
          if ( Blockbv != nullptr )
            v77 = sub_510350(2, 0, 10, 60000, 1, "CHARM_FIRE_USE");
          else
            v77 = 0;
          v125 = -1;
          pBuf[1] = v77;
          pBuf2[1] = 23;
          pMem33 = operator new(0xC8u);
          v125 = 139;
LABEL_312:
          if ( pMem33 == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);
        case 1083:
          Blockbb = operator new(0xB0u);
          v125 = 4;
          if ( Blockbb == nullptr )
            return nullptr;
          return (uint32_t *)sub_50FC00(Block, 0, 15, 1000);
        case 1084:
          Blockbc = operator new(0xB0u);
          v125 = 5;
          if ( Blockbc == nullptr )
            return nullptr;
          return (uint32_t *)sub_50FC00(Block, 1, 15, 1000);
        case 1085:
          Blockbd = operator new(0xB0u);
          v125 = 6;
          if ( Blockbd == nullptr )
            return nullptr;
          return (uint32_t *)sub_50FC00(Block, 1, 30, 100);
        case 1087:
          Blockbw = operator new(0xB0u);
          v125 = 148;
          if ( Blockbw == nullptr )
            return nullptr;
          return (uint32_t *)sub_50FC00(Block, 0, 30, 1000);
        case 1088:
          Blockbx = operator new(0xB0u);
          v125 = 149;
          if ( Blockbx == nullptr )
            return nullptr;
          return (uint32_t *)sub_50FC00(Block, 2, 50, 1000);
        default:
          return nullptr;
      }
    }
    pMem34 = operator new(0xB0u);
    v125 = 3;
    if ( pMem34 != nullptr )
    {
      sub_50F740(Block);
      *pMem34 = &CNIncreaseStatusStackable::`vftable';
      return pMem34;
    }
    return nullptr;
  }
  if ( Block == 1055 )
  {
    Blockba = operator new(0xC8u);
    v125 = 75;
    if ( Blockba != nullptr )
    {
      pMem20 = operator new(0x80u);
      LOBYTE(v125) = 76;
      if ( pMem20 != nullptr )
        v45 = sub_4D6810(1120403456, 1000, 1, 1);
      else
        v45 = 0;
      LOBYTE(v125) = 75;
      return (uint32_t *)sub_50F850(1055, v45, 0);
    }
    return nullptr;
  }
  if ( Block > 1019 )
  {
    switch ( Block )
    {
      case 1020:
        pMem20 = operator new(0xC8u);
        v33 = 45;
        v125 = 45;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem21 = operator new(0x84u);
        LOBYTE(v125) = 46;
        if ( pMem21 == nullptr )
          goto LABEL_162;
        v34 = sub_510350(0, 0, 30, 60000, 1, "CHARM_FIRE_USE");
        goto LABEL_163;
      case 1021:
        pMem20 = operator new(0xC8u);
        v125 = 47;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem21 = operator new(0x84u);
        LOBYTE(v125) = 48;
        if ( pMem21 != nullptr )
          v35 = sub_510350(1, 0, 30, 60000, 1, "CHARM_ICE_USE");
        else
          v35 = 0;
        LOBYTE(v125) = 47;
        return (uint32_t *)sub_50F850(Block, v35, 23);
      case 1022:
        pMem20 = operator new(0xC8u);
        v125 = 49;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem21 = operator new(0x84u);
        LOBYTE(v125) = 50;
        if ( pMem21 != nullptr )
          v36 = sub_510350(2, 0, 30, 60000, 1, "CHARM_MOON_USE");
        else
          v36 = 0;
        LOBYTE(v125) = 49;
        return (uint32_t *)sub_50F850(Block, v36, 23);
      case 1023:
        pMem20 = operator new(0xC8u);
        v33 = 51;
        v125 = 51;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem21 = operator new(0x84u);
        LOBYTE(v125) = 52;
        if ( pMem21 != nullptr )
          v34 = sub_510350(3, 0, 30, 60000, 1, "CHARM_SUN_USE");
        else
LABEL_162:
          v34 = 0;
LABEL_163:
        LOBYTE(v125) = v33;
        return (uint32_t *)sub_50F850(Block, v34, 23);
      case 1024:
        pMem35 = operator new(0x7Cu);
        pMem20 = pMem35;
        v125 = 53;
        if ( pMem35 != nullptr )
          v38 = sub_4B3DF0(pMem35, 16, 0, 1097859072, 60000, 1);
        else
          v38 = nullptr;
        v125 = -1;
        pBuf[0] = v38;
        pBuf2[0] = 51;
        pMem36 = operator new(0x7Cu);
        pMem20 = pMem36;
        v125 = 54;
        if ( pMem36 != nullptr )
          v40 = sub_4B3DF0(pMem36, 17, 0, 1097859072, 60000, 1);
        else
          v40 = nullptr;
        v125 = -1;
        pBuf[1] = v40;
        pBuf2[1] = 52;
        pMem37 = operator new(0x7Cu);
        pMem20 = pMem37;
        v125 = 55;
        if ( pMem37 != nullptr )
          v42 = sub_4B3DF0(pMem37, 18, 0, 1097859072, 60000, 1);
        else
          v42 = nullptr;
        v125 = -1;
        pBuf[2] = v42;
        pBuf2[2] = 53;
        pMem38 = operator new(0x7Cu);
        pMem20 = pMem38;
        v125 = 56;
        if ( pMem38 != nullptr )
          v44 = sub_4B3DF0(pMem38, 19, 0, 1097859072, 60000, 1);
        else
          v44 = nullptr;
        v125 = -1;
        pBuf[3] = v44;
        pBuf2[3] = 54;
        pMem20 = operator new(0xC8u);
        v125 = 57;
        if ( pMem20 == nullptr )
          return nullptr;
        return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 4);
      case 1025:
        goto LABEL_391;
      case 1026:
        pMem20 = operator new(0xC8u);
        v125 = 39;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem39 = operator new(0x7Cu);
        pMem21 = pMem39;
        LOBYTE(v125) = 40;
        if ( pMem39 != nullptr )
          v32 = sub_4B3DF0(pMem39, 0, 0, 1097859072, 600000, 1);
        else
          v32 = nullptr;
        LOBYTE(v125) = 39;
        return (uint32_t *)sub_50F850(Block, v32, 26);
      case 1027:
        v120 = 12;
        v121 = 0;
        v122[0] = 0x4E2042480000LL;
        v122[1] = 0x2400000001LL;
        Blockz = operator new(0x4ACu);
        v125 = 38;
        if ( Blockz == nullptr )
          return nullptr;
        return (uint32_t *)sub_510000(Block, 48017, &v120, 21);
      case 1028:
        v120 = 0;
        v121 = 0;
        v122[0] = 0xEA6041700000LL;
        v122[1] = 0x1A00000001LL;
        pMem40 = operator new(0x4ACu);
        v125 = 37;
        goto LABEL_137;
      case 1029:
        pMem20 = operator new(0xC8u);
        v125 = 35;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem41 = operator new(0x7Cu);
        pMem21 = pMem41;
        LOBYTE(v125) = 36;
        if ( pMem41 != nullptr )
          v30 = sub_4B3DF0(pMem41, 1, 0, 1097859072, 600000, 1);
        else
          v30 = nullptr;
        LOBYTE(v125) = 35;
        return (uint32_t *)sub_50F850(Block, v30, 28);
      case 1030:
        v120 = 1;
        v121 = 0;
        v122[0] = 0xEA6041700000LL;
        v122[1] = 0x1C00000001LL;
        pMem40 = operator new(0x4ACu);
        v125 = 34;
LABEL_137:
        if ( pMem40 == nullptr )
          return nullptr;
        return (uint32_t *)sub_510000(Block, 48017, &v120, 21);
      case 1031:
      case 1034:
      case 1035:
      case 1036:
      case 1037:
      case 1038:
      case 1039:
      case 1040:
      case 1041:
      case 1042:
      case 1043:
      case 1044:
      case 1045:
      case 1046:
        Blocky = operator new(0xB0u);
        v125 = 33;
        if ( Blocky == nullptr )
          return nullptr;
        return (uint32_t *)sub_50F7C0(Block);
      case 1032:
        Blocku = operator new(0x80u);
        v125 = 27;
        if ( Blocku != nullptr )
          v24 = sub_4D6810(1117782016, 100, 1, 1);
        else
          v24 = 0;
        v125 = -1;
        pBuf[0] = v24;
        pBuf2[0] = 0;
        Blockv = operator new(0x64u);
        v125 = 28;
        if ( Blockv != nullptr )
          v25 = sub_50F270(80, 100);
        else
          v25 = 0;
        v125 = -1;
        pBuf[1] = v25;
        pBuf2[1] = 0;
        pMem33 = operator new(0xC8u);
        v125 = 29;
        goto LABEL_312;
      case 1033:
        Blockw = operator new(0x80u);
        v125 = 30;
        if ( Blockw != nullptr )
          v26 = sub_4D6810(1123024896, 100, 1, 1);
        else
          v26 = 0;
        v125 = -1;
        pBuf[0] = v26;
        pBuf2[0] = 0;
        Blockx = operator new(0x64u);
        v125 = 31;
        if ( Blockx != nullptr )
          v27 = sub_50F270(120, 100);
        else
          v27 = 0;
        v125 = -1;
        pBuf[1] = v27;
        pBuf2[1] = 0;
        pMem33 = operator new(0xC8u);
        v125 = 32;
        goto LABEL_312;
      case 1047:
        Blockt = operator new(0xA8u);
        v125 = 25;
        if ( Blockt == nullptr )
          return nullptr;
        return (uint32_t *)sub_50FA30(Block);
      case 1048:
        pMem20 = operator new(0xC8u);
        v6 = 23;
        v125 = 23;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem21 = operator new(0x80u);
        LOBYTE(v125) = 24;
        if ( pMem21 == nullptr )
          goto LABEL_233;
        v7 = sub_4D6810(1132593152, 700, 1, 1);
        goto LABEL_326;
      case 1049:
        pMem20 = operator new(0xC8u);
        v6 = 21;
        v125 = 21;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem21 = operator new(0x64u);
        LOBYTE(v125) = 22;
        if ( pMem21 == nullptr )
          goto LABEL_325;
        v7 = sub_50F270(130, 700);
        goto LABEL_326;
      case 1050:
        Blocks = operator new(0xBCu);
        v125 = 20;
        if ( Blocks != nullptr )
          v23 = sub_510640(Block, 0, 0);
        else
          v23 = 0;
        v125 = -1;
        sub_602BC0(3, 0, -1, 1);
        return (uint32_t *)v23;
      case 1051:
        Blockr = operator new(0xBCu);
        v125 = 19;
        if ( Blockr != nullptr )
          v22 = sub_510640(Block, 0, 0);
        else
          v22 = 0;
        v125 = -1;
        sub_602BC0(7, 0, -1, 1);
        return (uint32_t *)v22;
      case 1052:
        Blockq = operator new(0xBCu);
        v125 = 18;
        if ( Blockq != nullptr )
          v21 = sub_510640(Block, 0, 0);
        else
          v21 = 0;
        v125 = -1;
        sub_602BC0(5, 0, -1, 1);
        return (uint32_t *)v21;
      case 1053:
        Blockp = operator new(0xBCu);
        v125 = 17;
        if ( Blockp != nullptr )
          v20 = sub_510640(Block, 0, 0);
        else
          v20 = 0;
        v125 = -1;
        sub_602BC0(15, 0, -1, 1);
        return (uint32_t *)v20;
      case 1054:
        Blocko = operator new(0xBCu);
        v125 = 16;
        if ( Blocko != nullptr )
          v19 = sub_510640(Block, 0, 0);
        else
          v19 = 0;
        v125 = -1;
        sub_602BC0(11, 0, -1, 1);
        return (uint32_t *)v19;
      default:
        return nullptr;
    }
  }
  if ( Block == 1019 )
    goto LABEL_384;
  if ( Block > 1006 )
  {
    switch ( Block )
    {
      case 1007:
        pMem42 = operator new(0x7Cu);
        v125 = 70;
        if ( pMem42 != nullptr )
          v13 = sub_4B3DF0(pMem42, 0, 0, 1092616192, 600000, 1);
        else
          v13 = nullptr;
        v125 = -1;
        pBuf[0] = v13;
        pBuf2[0] = 26;
        pMem43 = operator new(0x7Cu);
        v125 = 71;
        if ( pMem43 != nullptr )
          v15 = sub_4B3DF0(pMem43, 3, 0, 1092616192, 600000, 1);
        else
          v15 = nullptr;
        v125 = -1;
        pBuf[1] = v15;
        pBuf2[1] = 27;
        pMem33 = operator new(0xC8u);
        v125 = 72;
        goto LABEL_312;
      case 1008:
        Blockl = operator new(0xBCu);
        v125 = 68;
        if ( Blockl == nullptr )
          goto LABEL_67;
        v11 = sub_510640(Block, 0, 0);
        goto LABEL_68;
      case 1009:
        Blockn = operator new(0xBCu);
        v125 = 74;
        if ( Blockn != nullptr )
          v5 = sub_510E40(Block, 200, 0);
        else
LABEL_71:
          v5 = 0;
LABEL_72:
        v125 = -1;
        sub_602BC0(1, 0, -1, 1);
        return (uint32_t *)v5;
      case 1010:
        Blockm = operator new(0xBCu);
        v125 = 73;
        if ( Blockm != nullptr )
          v11 = sub_510640(Block, 200, 0);
        else
LABEL_67:
          v11 = 0;
LABEL_68:
        v125 = -1;
        sub_602BC0(2, 0, -1, 1);
        return (uint32_t *)v11;
      case 1011:
        pMem20 = operator new(0xC8u);
        v6 = -96;
        v125 = 160;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem21 = operator new(0x60u);
        LOBYTE(v125) = -95;
        if ( pMem21 != nullptr )
          goto LABEL_78;
        goto LABEL_321;
      case 1013:
        pMem20 = operator new(0xC8u);
        v125 = 164;
        if ( pMem20 != nullptr )
        {
          pMem21 = operator new(0x80u);
          LOBYTE(v125) = -91;
          if ( pMem21 != nullptr )
            v17 = sub_4D6810(1127481344, 2000, 1, 1);
          else
            v17 = 0;
          LOBYTE(v125) = -92;
          v18 = sub_50F850(Block, v17, 0);
          v125 = -1;
          sub_602DA0(2, 30.0, 2);
        }
        else
        {
          v18 = 0;
          v125 = -1;
          sub_602DA0(2, 30.0, 2);
        }
        return (uint32_t *)v18;
      case 1014:
        pMem20 = operator new(0xC8u);
        v6 = -94;
        v125 = 162;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem21 = operator new(0x60u);
        LOBYTE(v125) = -93;
        if ( pMem21 == nullptr )
          goto LABEL_325;
LABEL_78:
        v7 = sub_510230(4, 1000, 60000);
        goto LABEL_326;
      case 1015:
        Blocki = operator new(0xB0u);
        v125 = 64;
        if ( Blocki == nullptr )
          return nullptr;
        return (uint32_t *)sub_5104B0(Block, 1, 5, 14);
      case 1016:
        pMem20 = operator new(0xC8u);
        v125 = 41;
        if ( pMem20 == nullptr )
          return nullptr;
        pMem44 = operator new(0x7Cu);
        pMem21 = pMem44;
        LOBYTE(v125) = 42;
        if ( pMem44 != nullptr )
          v10 = sub_4B3DF0(pMem44, 12, 0, 1112014848, 20000, 1);
        else
          v10 = nullptr;
        LOBYTE(v125) = 41;
        return (uint32_t *)sub_50F850(Block, v10, 36);
      case 1017:
        *(uint32_t *)((char *)v122 + 3) = 60000;
        *(uint32_t *)((char *)v122 + 7) = 0;
        *(uint32_t *)((char *)&v122[1] + 3) = 37;
        Blockj = operator new(0x4ACu);
        v125 = 65;
        if ( Blockj == nullptr )
          return nullptr;
        return (uint32_t *)sub_510000(Block, 48018, (char *)v122 + 3, 12);
      case 1018:
        *(uint32_t *)((char *)v122 + 3) = 60000;
        *(uint32_t *)((char *)v122 + 7) = 1;
        *(uint32_t *)((char *)&v122[1] + 3) = 37;
        Blockk = operator new(0x4ACu);
        v125 = 66;
        if ( Blockk == nullptr )
          return nullptr;
        return (uint32_t *)sub_510000(Block, 48018, (char *)v122 + 3, 12);
      default:
        return nullptr;
    }
  }
  if ( Block == 1006 )
  {
    Blockh = operator new(0xBCu);
    v125 = 67;
    if ( Blockh != nullptr )
      v8 = sub_510640(1006, 0, 0);
    else
      v8 = 0;
    v125 = -1;
    sub_602BC0(12, 1120403456, 7, 1);
    return (uint32_t *)v8;
  }
  if ( Block <= 1000 )
  {
    if ( Block != 1000 )
    {
      switch ( Block )
      {
        case 0:
          Blockd = operator new(0xA4u);
          v125 = 170;
          if ( Blockd == nullptr )
            return nullptr;
          result = (uint32_t *)sub_485DA0(nArg2);
          break;
        case 3:
          Blockc = operator new(0xB0u);
          v125 = 2;
          if ( Blockc == nullptr )
            return nullptr;
          result = (uint32_t *)sub_50F7C0(3);
          break;
        case 8:
          Blockb = operator new(0xA4u);
          v125 = 1;
          if ( Blockb == nullptr )
            return nullptr;
          result = (uint32_t *)sub_50FA90(8);
          break;
        case 10:
          Blocka = operator new(0xA4u);
          v125 = 0;
          if ( Blocka == nullptr )
            return nullptr;
          result = (uint32_t *)sub_50FE70(10);
          break;
        case 14:
        case 15:
          Blocke = operator new(0xA4u);
          v125 = 171;
          if ( Blocke == nullptr )
            return nullptr;
          result = (uint32_t *)sub_50FFB0(Block);
          break;
        default:
          return nullptr;
      }
      return result;
    }
    Blockf = operator new(0xC8u);
    v125 = 77;
    if ( Blockf != nullptr )
    {
      pMem21 = operator new(0x80u);
      LOBYTE(v125) = 78;
      if ( pMem21 != nullptr )
        v4 = sub_4D6810(1112014848, 1000, 1, 1);
      else
        v4 = 0;
      LOBYTE(v125) = 77;
      return (uint32_t *)sub_50F850(1000, v4, 0);
    }
    return nullptr;
  }
  switch ( Block )
  {
    case 1001:
      pMem21 = operator new(0xC8u);
      v6 = 81;
      v125 = 81;
      if ( pMem21 == nullptr )
        return nullptr;
      pMem20 = operator new(0x80u);
      LOBYTE(v125) = 82;
      if ( pMem20 == nullptr )
        goto LABEL_233;
      v7 = sub_4D6810(1125842944, 1500, 1, 1);
      break;
    case 1002:
      pMem20 = operator new(0xC8u);
      v6 = -98;
      v125 = 158;
      if ( pMem20 == nullptr )
        return nullptr;
      pMem21 = operator new(0x64u);
      LOBYTE(v125) = -97;
      if ( pMem21 != nullptr )
        goto LABEL_324;
      goto LABEL_233;
    case 1003:
      pMem20 = operator new(0xC8u);
      v6 = -106;
      v125 = 150;
      if ( pMem20 == nullptr )
        return nullptr;
      pMem21 = operator new(0x80u);
      LOBYTE(v125) = -105;
      if ( pMem21 == nullptr )
        goto LABEL_321;
      v7 = sub_4D6810(1135542272, 2000, 1, 1);
      break;
    case 1004:
      pMem20 = operator new(0xC8u);
      v6 = -102;
      v125 = 154;
      if ( pMem20 == nullptr )
        return nullptr;
      pMem21 = operator new(0x64u);
      LOBYTE(v125) = -101;
      if ( pMem21 == nullptr )
        goto LABEL_325;
      v7 = sub_50F270(55, 1000);
      break;
    case 1005:
      Blockg = operator new(0xBCu);
      v125 = 69;
      if ( Blockg == nullptr )
        goto LABEL_71;
      v5 = sub_510E40(Block, 0, 0);
      goto LABEL_72;
  }
LABEL_326:
  LOBYTE(v125) = v6;
  return (uint32_t *)sub_50F850(Block, v7, 0);
}

