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
uint32_t */*cdecl*/ sub_510F30(int Block, int a2)
{
  uint32_t *result; // eax
  int v4; // eax
  int v5; // esi
  char v6; // bl
  int v7; // eax
  int v8; // esi
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  int v11; // esi
  uint32_t *v12; // eax
  uint32_t *v13; // eax
  uint32_t *v14; // eax
  uint32_t *v15; // eax
  void *v16; // eax
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
  void *v28; // eax
  uint32_t *v29; // eax
  uint32_t *v30; // eax
  uint32_t *v31; // eax
  uint32_t *v32; // eax
  char v33; // bl
  int v34; // eax
  int v35; // eax
  int v36; // eax
  uint32_t *v37; // eax
  uint32_t *v38; // eax
  uint32_t *v39; // eax
  uint32_t *v40; // eax
  uint32_t *v41; // eax
  uint32_t *v42; // eax
  uint32_t *v43; // eax
  uint32_t *v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  uint32_t *v50; // eax
  uint32_t *v51; // eax
  int v52; // eax
  uint32_t *v53; // eax
  uint32_t *v54; // eax
  uint32_t *v55; // eax
  uint32_t *v56; // eax
  uint32_t *v57; // eax
  uint32_t *v58; // eax
  uint32_t *v59; // eax
  uint32_t *v60; // eax
  uint32_t *v61; // eax
  uint32_t *v62; // eax
  uint32_t *v63; // eax
  uint32_t *v64; // eax
  uint32_t *v65; // eax
  uint32_t *v66; // eax
  uint32_t *v67; // eax
  uint32_t *v68; // eax
  uint32_t *v69; // eax
  uint32_t *v70; // eax
  uint32_t *v71; // eax
  uint32_t *v72; // eax
  int v73; // eax
  int v74; // eax
  int *v75; // eax
  int v76; // edx
  int v77; // eax
  uint32_t *v78; // esi
  uint32_t *v79; // eax
  uint32_t *v80; // eax
  uint32_t *v81; // eax
  uint32_t *v82; // eax
  uint32_t *v83; // eax
  uint32_t *v84; // eax
  uint32_t *v85; // eax
  uint32_t *v86; // eax
  uint32_t *v87; // eax
  uint32_t *v88; // eax
  uint32_t *v89; // eax
  uint32_t *v90; // eax
  uint32_t *v91; // eax
  uint32_t *v92; // eax
  uint32_t *v93; // eax
  uint32_t *v94; // eax
  uint32_t *v95; // eax
  uint32_t *v96; // eax
  uint32_t *v97; // eax
  uint32_t *v98; // eax
  uint32_t *v99; // eax
  uint32_t *v100; // eax
  uint32_t *v101; // eax
  uint32_t *v102; // eax
  uint32_t *v103; // eax
  uint32_t *v104; // eax
  uint32_t *v105; // eax
  uint32_t *v106; // eax
  uint32_t *v107; // eax
  uint32_t *v108; // eax
  uint32_t *v109; // eax
  uint32_t *v110; // eax
  uint32_t *v111; // eax
  uint32_t *v112; // eax
  uint32_t *v113; // eax
  uint32_t *v114; // eax
  uint32_t *v115; // eax
  uint32_t *v116; // eax
  int v117; // eax
  uint32_t v118[20]; // [esp+Ch] [ebp-CCh] BYREF
  uint32_t v119[20]; // [esp+5Ch] [ebp-7Ch] BYREF
  int v120; // [esp+ACh] [ebp-2Ch] BYREF
  char v121; // [esp+B0h] [ebp-28h]
  uint64_t v122[2]; // [esp+B1h] [ebp-27h] BYREF
  void *v123; // [esp+C4h] [ebp-14h]
  void *v124; // [esp+C8h] [ebp-10h]
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

  memset(v118, 0, sizeof(v118));
  memset(v119, 0, sizeof(v119));
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
              v111 = operator new(0x7Cu);
              v125 = 166;
              if ( v111 != nullptr )
                v112 = sub_4B3DF0(v111, 0, 0, 1112014848, 1800000, 1);
              else
                v112 = nullptr;
              v125 = -1;
              v118[0] = v112;
              v119[0] = 26;
              Blockcj = operator new(0xC8u);
              v125 = 167;
              if ( Blockcj != nullptr )
                return (uint32_t *)sub_50F990(7099, v118, v119, 1);
            }
            else if ( Block == 7100 )
            {
              v109 = operator new(0x7Cu);
              v125 = 168;
              v110 = v109 != nullptr ? sub_4B3DF0(v109, 1, 0, 1112014848, 1800000, 1) : nullptr;
              v125 = -1;
              v118[0] = v110;
              v119[0] = 28;
              Blockci = operator new(0xC8u);
              v125 = 169;
              if ( Blockci != nullptr )
                return (uint32_t *)sub_50F990(7100, v118, v119, 1);
            }
            return nullptr;
          }
          v113 = operator new(0x7Cu);
          v125 = 128;
          if ( v113 != nullptr )
            v114 = sub_4B3DF0(v113, 25, 1, 1092616192, 1800000, 1);
          else
            v114 = nullptr;
          v125 = -1;
          v118[0] = v114;
          v119[0] = 46;
          v115 = operator new(0x7Cu);
          v125 = 129;
          if ( v115 != nullptr )
            v116 = sub_4B3DF0(v115, 26, 1, 1092616192, 1800000, 1);
          else
            v116 = nullptr;
          v125 = -1;
          v118[1] = v116;
          v119[1] = 45;
          Blockck = operator new(0xC8u);
          v125 = 130;
          if ( Blockck != nullptr )
            sub_50F990(6514, v118, v119, 2);
          v125 = -1;
LABEL_433:
          Blockcl = operator new(0x80u);
          v125 = 131;
          if ( Blockcl != nullptr )
            v117 = sub_4D6810(1141473280, 1000, 1, 1);
          else
            v117 = 0;
          v125 = -1;
          v118[0] = v117;
          v119[0] = 0;
          Blockcm = operator new(0xC8u);
          v125 = 132;
          if ( Blockcm != nullptr )
            v18 = sub_50F990(Block, v118, v119, 1);
          else
            v18 = 0;
          v125 = -1;
          sub_602DA0(2, 5.0, 8);
          return (uint32_t *)v18;
        }
        switch ( Block )
        {
          case 6513:
            v99 = operator new(0x7Cu);
            v125 = 122;
            if ( v99 != nullptr )
              v100 = sub_4B3DF0(v99, 0, 0, 1120403456, 60000, 1);
            else
              v100 = nullptr;
            v125 = -1;
            v118[0] = v100;
            v119[0] = 26;
            v101 = operator new(0x7Cu);
            v125 = 123;
            if ( v101 != nullptr )
              v102 = sub_4B3DF0(v101, 1, 0, 1120403456, 60000, 1);
            else
              v102 = nullptr;
            v125 = -1;
            v118[1] = v102;
            v119[1] = 28;
            v103 = operator new(0x7Cu);
            v125 = 124;
            if ( v103 != nullptr )
              v104 = sub_4B3DF0(v103, 3, 1, -1027080192, 60000, 1);
            else
              v104 = nullptr;
            v125 = -1;
            v118[2] = v104;
            v119[2] = 27;
            v105 = operator new(0x7Cu);
            v125 = 125;
            if ( v105 != nullptr )
              v106 = sub_4B3DF0(v105, 5, 1, -1027080192, 60000, 1);
            else
              v106 = nullptr;
            v125 = -1;
            v118[3] = v106;
            v119[3] = 30;
            v107 = operator new(0x7Cu);
            v125 = 126;
            if ( v107 != nullptr )
              v108 = sub_4B3DF0(v107, 20, 1, -1027080192, 60000, 1);
            else
              v108 = nullptr;
            v125 = -1;
            v118[4] = v108;
            v119[4] = 23;
            Blockch = operator new(0xC8u);
            v125 = 127;
            if ( Blockch != nullptr )
              return (uint32_t *)sub_50F990(6513, v118, v119, 5);
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
              v97 = operator new(0x7Cu);
              v124 = v97;
              LOBYTE(v125) = 44;
              if ( v97 != nullptr )
                v98 = sub_4B3DF0(v97, 12, 0, 1112014848, 60000, 1);
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
        v89 = operator new(0x7Cu);
        v125 = 58;
        if ( v89 != nullptr )
          v90 = sub_4B3DF0(v89, 16, 0, 1097859072, 1800000, 1);
        else
          v90 = nullptr;
        v125 = -1;
        v118[0] = v90;
        v119[0] = 40;
        v91 = operator new(0x7Cu);
        v125 = 59;
        if ( v91 != nullptr )
          v92 = sub_4B3DF0(v91, 17, 0, 1097859072, 1800000, 1);
        else
          v92 = nullptr;
        v125 = -1;
        v118[1] = v92;
        v119[1] = 41;
        v93 = operator new(0x7Cu);
        v125 = 60;
        if ( v93 != nullptr )
          v94 = sub_4B3DF0(v93, 18, 0, 1097859072, 1800000, 1);
        else
          v94 = nullptr;
        v125 = -1;
        v118[2] = v94;
        v119[2] = 42;
        v95 = operator new(0x7Cu);
        v125 = 61;
        if ( v95 != nullptr )
          v96 = sub_4B3DF0(v95, 19, 0, 1097859072, 1800000, 1);
        else
          v96 = nullptr;
        v125 = -1;
        v118[3] = v96;
        v119[3] = 43;
        Blockcd = operator new(0xC8u);
        v125 = 62;
        if ( Blockcd != nullptr )
          return (uint32_t *)sub_50F990(6505, v118, v119, 4);
        return nullptr;
      }
      if ( Block > 6501 )
      {
        if ( Block == 6502 )
        {
          v85 = operator new(0x7Cu);
          v125 = 142;
          if ( v85 != nullptr )
            v86 = sub_4B3DF0(v85, 8, 1, 1092616192, 600000, 1);
          else
            v86 = nullptr;
          v125 = -1;
          v118[0] = v86;
          v119[0] = 47;
          v87 = operator new(0x7Cu);
          v125 = 143;
          if ( v87 != nullptr )
            v88 = sub_4B3DF0(v87, 7, 1, 1092616192, 600000, 1);
          else
            v88 = nullptr;
          v125 = -1;
          v118[1] = v88;
          v119[1] = 48;
          Blockcc = operator new(0xC8u);
          v125 = 144;
          if ( Blockcc != nullptr )
            return (uint32_t *)sub_50F990(6502, v118, v119, 2);
        }
        else if ( Block == 6503 )
        {
          v81 = operator new(0x7Cu);
          v125 = 145;
          if ( v81 != nullptr )
            v82 = sub_4B3DF0(v81, 4, 1, 1092616192, 1800000, 1);
          else
            v82 = nullptr;
          v125 = -1;
          v118[0] = v82;
          v119[0] = 49;
          v83 = operator new(0x7Cu);
          v125 = 146;
          if ( v83 != nullptr )
            v84 = sub_4B3DF0(v83, 5, 1, 1092616192, 1800000, 1);
          else
            v84 = nullptr;
          v125 = -1;
          v118[1] = v84;
          v119[1] = 50;
          Blockcb = operator new(0xC8u);
          v125 = 147;
          if ( Blockcb != nullptr )
            return (uint32_t *)sub_50F990(6503, v118, v119, 2);
        }
        else
        {
          v79 = operator new(0x7Cu);
          v125 = 111;
          if ( v79 != nullptr )
            v80 = sub_4B3DF0(v79, 22, 0, 1088421888, 600000, 1);
          else
            v80 = nullptr;
          v125 = -1;
          v118[0] = v80;
          v119[0] = 44;
          Blockca = operator new(0xC8u);
          v125 = 112;
          if ( Blockca != nullptr )
            return (uint32_t *)sub_50F990(6504, v118, v119, 1);
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
          v124 = operator new(0xC8u);
          v6 = 79;
          v125 = 79;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x80u);
          LOBYTE(v125) = 80;
          if ( v123 == nullptr )
            goto LABEL_325;
          v7 = sub_4D6810(1128136704, 1500, 1, 1);
          goto LABEL_326;
        case 1057:
          v124 = operator new(0xC8u);
          v6 = -104;
          v125 = 152;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x64u);
          LOBYTE(v125) = -103;
          if ( v123 == nullptr )
            goto LABEL_321;
          v7 = sub_50F270(70, 1000);
          goto LABEL_326;
        case 1058:
          v124 = operator new(0xC8u);
          v6 = -100;
          v125 = 156;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x64u);
          LOBYTE(v125) = -99;
          if ( v123 == nullptr )
            goto LABEL_325;
LABEL_324:
          v7 = sub_50F270(120, 1500);
          goto LABEL_326;
        case 1059:
          v124 = operator new(0xC8u);
          v6 = 83;
          v125 = 83;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x80u);
          LOBYTE(v125) = 84;
          if ( v123 == nullptr )
            goto LABEL_233;
          v7 = sub_4D6810(1133903872, 700, 1, 1);
          goto LABEL_326;
        case 1060:
          v124 = operator new(0xC8u);
          v6 = 85;
          v125 = 85;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x64u);
          LOBYTE(v125) = 86;
          if ( v123 == nullptr )
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
          v118[0] = v46;
          v119[0] = 0;
          Blockbg = operator new(0x64u);
          v125 = 88;
          if ( Blockbg != nullptr )
            v47 = sub_50F270(95, 1000);
          else
            v47 = 0;
          v125 = -1;
          v118[1] = v47;
          v119[1] = 0;
          Blockbh = operator new(0xC8u);
          v125 = 89;
          if ( Blockbh != nullptr )
          {
            v18 = sub_50F990(Block, v118, v119, 2);
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
          v124 = operator new(0xC8u);
          v6 = 90;
          v125 = 90;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x80u);
          LOBYTE(v125) = 91;
          if ( v123 == nullptr )
            goto LABEL_321;
          v7 = sub_4D6810(1120403456, 1000, 1, 1);
          goto LABEL_326;
        case 1063:
          v124 = operator new(0xC8u);
          v6 = 92;
          v125 = 92;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x80u);
          LOBYTE(v125) = 93;
          if ( v123 == nullptr )
            goto LABEL_325;
          v7 = sub_4D6810(1130102784, 700, 1, 1);
          goto LABEL_326;
        case 1064:
          v124 = operator new(0xC8u);
          v6 = 94;
          v125 = 94;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x80u);
          LOBYTE(v125) = 95;
          if ( v123 == nullptr )
            goto LABEL_233;
          v7 = sub_4D6810(1133576192, 700, 1, 1);
          goto LABEL_326;
        case 1065:
          v124 = operator new(0xC8u);
          v6 = 96;
          v125 = 96;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x64u);
          LOBYTE(v125) = 97;
          if ( v123 == nullptr )
            goto LABEL_321;
          v7 = sub_50F270(80, 700);
          goto LABEL_326;
        case 1066:
          v124 = operator new(0xC8u);
          v6 = 98;
          v125 = 98;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x64u);
          LOBYTE(v125) = 99;
          if ( v123 == nullptr )
            goto LABEL_325;
          v7 = sub_50F270(95, 700);
          goto LABEL_326;
        case 1067:
          Blockbi = operator new(0xC8u);
          v125 = 100;
          if ( Blockbi == nullptr )
            return nullptr;
          v124 = operator new(0x64u);
          LOBYTE(v125) = 101;
          if ( v124 != nullptr )
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
          v118[0] = v49;
          v119[0] = 0;
          v50 = operator new(0x7Cu);
          v125 = 103;
          if ( v50 != nullptr )
            v51 = sub_4B3DF0(v50, 5, 1, 1101004800, 20000, 1);
          else
            v51 = nullptr;
          v125 = -1;
          v118[1] = v51;
          v119[1] = 30;
          Blockbk = operator new(0xC8u);
          v125 = 104;
          if ( Blockbk == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, v118, v119, 2);
        case 1069:
          Blockbl = operator new(0x64u);
          v125 = 105;
          if ( Blockbl != nullptr )
            v52 = sub_50F270(145, 1000);
          else
            v52 = 0;
          v125 = -1;
          v118[0] = v52;
          v119[0] = 0;
          v53 = operator new(0x7Cu);
          v125 = 106;
          if ( v53 != nullptr )
            v54 = sub_4B3DF0(v53, 2, 0, 1106247680, 60000, 1);
          else
            v54 = nullptr;
          v125 = -1;
          v118[1] = v54;
          v119[1] = 29;
          Blockbm = operator new(0xC8u);
          v125 = 107;
          if ( Blockbm == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, v118, v119, 2);
        case 1070:
          v55 = operator new(0x7Cu);
          v125 = 108;
          if ( v55 != nullptr )
            v56 = sub_4B3DF0(v55, 3, 0, 1101004800, 60000, 1);
          else
            v56 = nullptr;
          v125 = -1;
          v118[0] = v56;
          v119[0] = 26;
          v57 = operator new(0x7Cu);
          v125 = 109;
          if ( v57 != nullptr )
            v58 = sub_4B3DF0(v57, 22, 0, 1101004800, 60000, 1);
          else
            v58 = nullptr;
          v125 = -1;
          v118[1] = v58;
          v119[1] = 24;
          Blockbn = operator new(0xC8u);
          v125 = 110;
          if ( Blockbn == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, v118, v119, 2);
        case 1071:
          v59 = operator new(0x7Cu);
          v125 = 113;
          if ( v59 != nullptr )
            v60 = sub_4B3DF0(v59, 1, 0, 1101004800, 60000, 1);
          else
            v60 = nullptr;
          v125 = -1;
          v118[0] = v60;
          v119[0] = 28;
          v61 = operator new(0x7Cu);
          v125 = 114;
          if ( v61 != nullptr )
            v62 = sub_4B3DF0(v61, 21, 0, 1112014848, 60000, 1);
          else
            v62 = nullptr;
          v125 = -1;
          v118[1] = v62;
          v119[1] = 25;
          Blockbo = operator new(0xC8u);
          v125 = 115;
          if ( Blockbo == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, v118, v119, 2);
        case 1072:
          v63 = operator new(0x7Cu);
          v125 = 116;
          if ( v63 != nullptr )
            v64 = sub_4B3DF0(v63, 0, 0, 1106247680, 60000, 1);
          else
            v64 = nullptr;
          v125 = -1;
          v118[0] = v64;
          v119[0] = 26;
          v65 = operator new(0x7Cu);
          v125 = 117;
          if ( v65 != nullptr )
            v66 = sub_4B3DF0(v65, 1, 0, 1106247680, 60000, 1);
          else
            v66 = nullptr;
          v125 = -1;
          v118[1] = v66;
          v119[1] = 28;
          v67 = operator new(0x7Cu);
          v125 = 118;
          if ( v67 != nullptr )
            v68 = sub_4B3DF0(v67, 3, 1, -1027080192, 60000, 1);
          else
            v68 = nullptr;
          v125 = -1;
          v118[2] = v68;
          v119[2] = 27;
          v69 = operator new(0x7Cu);
          v125 = 119;
          if ( v69 != nullptr )
            v70 = sub_4B3DF0(v69, 5, 1, -1027080192, 60000, 1);
          else
            v70 = nullptr;
          v125 = -1;
          v118[3] = v70;
          v119[3] = 30;
          v71 = operator new(0x7Cu);
          v125 = 120;
          if ( v71 != nullptr )
            v72 = sub_4B3DF0(v71, 20, 1, -1027080192, 60000, 1);
          else
            v72 = nullptr;
          v125 = -1;
          v118[4] = v72;
          v119[4] = 23;
          Blockbp = operator new(0xC8u);
          v125 = 121;
          if ( Blockbp == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, v118, v119, 5);
        case 1074:
          Blockbe = operator new(0xB0u);
          v125 = 7;
          if ( Blockbe == nullptr )
            return nullptr;
          return (uint32_t *)sub_50FF30(Block, 0, 300, 0);
        case 1075:
          v124 = operator new(0xC8u);
          v6 = 12;
          v125 = 12;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x80u);
          LOBYTE(v125) = 13;
          if ( v123 != nullptr )
            v7 = sub_4D6810(1133248512, 2000, 1, 1);
          else
LABEL_233:
            v7 = 0;
          goto LABEL_326;
        case 1076:
          v124 = operator new(0xC8u);
          v6 = 14;
          v125 = 14;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x64u);
          LOBYTE(v125) = 15;
          if ( v123 == nullptr )
            goto LABEL_321;
          v7 = sub_50F270(150, 700);
          goto LABEL_326;
        case 1077:
          v124 = operator new(0xC8u);
          v6 = 8;
          v125 = 8;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x80u);
          LOBYTE(v125) = 9;
          if ( v123 != nullptr )
            v7 = sub_4D6810(1133248512, 100, 1, 1);
          else
LABEL_321:
            v7 = 0;
          goto LABEL_326;
        case 1078:
          v124 = operator new(0xC8u);
          v6 = 10;
          v125 = 10;
          if ( v124 == nullptr )
            return nullptr;
          v123 = operator new(0x80u);
          LOBYTE(v125) = 11;
          if ( v123 != nullptr )
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
          v118[0] = v73;
          v119[0] = 0;
          Blockbr = operator new(0xC8u);
          v125 = 134;
          if ( Blockbr != nullptr )
          {
            v18 = sub_50F990(Block, v118, v119, 1);
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
          v118[0] = v74;
          v119[0] = 0;
          Blockbt = operator new(0xC8u);
          v125 = 136;
          if ( Blockbt != nullptr )
          {
            v18 = sub_50F990(Block, v118, v119, 1);
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
          v118[0] = v75;
          v76 = *v75;
          v125 = -1;
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v76 + 64))(v75) + 40) = 60000;
          v119[0] = 37;
          Blockbv = operator new(0x84u);
          v125 = 138;
          if ( Blockbv != nullptr )
            v77 = sub_510350(2, 0, 10, 60000, 1, "CHARM_FIRE_USE");
          else
            v77 = 0;
          v125 = -1;
          v118[1] = v77;
          v119[1] = 23;
          v16 = operator new(0xC8u);
          v125 = 139;
LABEL_312:
          if ( v16 == nullptr )
            return nullptr;
          return (uint32_t *)sub_50F990(Block, v118, v119, 2);
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
    v78 = operator new(0xB0u);
    v125 = 3;
    if ( v78 != nullptr )
    {
      sub_50F740(Block);
      *v78 = &CNIncreaseStatusStackable::`vftable';
      return v78;
    }
    return nullptr;
  }
  if ( Block == 1055 )
  {
    Blockba = operator new(0xC8u);
    v125 = 75;
    if ( Blockba != nullptr )
    {
      v124 = operator new(0x80u);
      LOBYTE(v125) = 76;
      if ( v124 != nullptr )
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
        v124 = operator new(0xC8u);
        v33 = 45;
        v125 = 45;
        if ( v124 == nullptr )
          return nullptr;
        v123 = operator new(0x84u);
        LOBYTE(v125) = 46;
        if ( v123 == nullptr )
          goto LABEL_162;
        v34 = sub_510350(0, 0, 30, 60000, 1, "CHARM_FIRE_USE");
        goto LABEL_163;
      case 1021:
        v124 = operator new(0xC8u);
        v125 = 47;
        if ( v124 == nullptr )
          return nullptr;
        v123 = operator new(0x84u);
        LOBYTE(v125) = 48;
        if ( v123 != nullptr )
          v35 = sub_510350(1, 0, 30, 60000, 1, "CHARM_ICE_USE");
        else
          v35 = 0;
        LOBYTE(v125) = 47;
        return (uint32_t *)sub_50F850(Block, v35, 23);
      case 1022:
        v124 = operator new(0xC8u);
        v125 = 49;
        if ( v124 == nullptr )
          return nullptr;
        v123 = operator new(0x84u);
        LOBYTE(v125) = 50;
        if ( v123 != nullptr )
          v36 = sub_510350(2, 0, 30, 60000, 1, "CHARM_MOON_USE");
        else
          v36 = 0;
        LOBYTE(v125) = 49;
        return (uint32_t *)sub_50F850(Block, v36, 23);
      case 1023:
        v124 = operator new(0xC8u);
        v33 = 51;
        v125 = 51;
        if ( v124 == nullptr )
          return nullptr;
        v123 = operator new(0x84u);
        LOBYTE(v125) = 52;
        if ( v123 != nullptr )
          v34 = sub_510350(3, 0, 30, 60000, 1, "CHARM_SUN_USE");
        else
LABEL_162:
          v34 = 0;
LABEL_163:
        LOBYTE(v125) = v33;
        return (uint32_t *)sub_50F850(Block, v34, 23);
      case 1024:
        v37 = operator new(0x7Cu);
        v124 = v37;
        v125 = 53;
        if ( v37 != nullptr )
          v38 = sub_4B3DF0(v37, 16, 0, 1097859072, 60000, 1);
        else
          v38 = nullptr;
        v125 = -1;
        v118[0] = v38;
        v119[0] = 51;
        v39 = operator new(0x7Cu);
        v124 = v39;
        v125 = 54;
        if ( v39 != nullptr )
          v40 = sub_4B3DF0(v39, 17, 0, 1097859072, 60000, 1);
        else
          v40 = nullptr;
        v125 = -1;
        v118[1] = v40;
        v119[1] = 52;
        v41 = operator new(0x7Cu);
        v124 = v41;
        v125 = 55;
        if ( v41 != nullptr )
          v42 = sub_4B3DF0(v41, 18, 0, 1097859072, 60000, 1);
        else
          v42 = nullptr;
        v125 = -1;
        v118[2] = v42;
        v119[2] = 53;
        v43 = operator new(0x7Cu);
        v124 = v43;
        v125 = 56;
        if ( v43 != nullptr )
          v44 = sub_4B3DF0(v43, 19, 0, 1097859072, 60000, 1);
        else
          v44 = nullptr;
        v125 = -1;
        v118[3] = v44;
        v119[3] = 54;
        v124 = operator new(0xC8u);
        v125 = 57;
        if ( v124 == nullptr )
          return nullptr;
        return (uint32_t *)sub_50F990(Block, v118, v119, 4);
      case 1025:
        goto LABEL_391;
      case 1026:
        v124 = operator new(0xC8u);
        v125 = 39;
        if ( v124 == nullptr )
          return nullptr;
        v31 = operator new(0x7Cu);
        v123 = v31;
        LOBYTE(v125) = 40;
        if ( v31 != nullptr )
          v32 = sub_4B3DF0(v31, 0, 0, 1097859072, 600000, 1);
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
        v28 = operator new(0x4ACu);
        v125 = 37;
        goto LABEL_137;
      case 1029:
        v124 = operator new(0xC8u);
        v125 = 35;
        if ( v124 == nullptr )
          return nullptr;
        v29 = operator new(0x7Cu);
        v123 = v29;
        LOBYTE(v125) = 36;
        if ( v29 != nullptr )
          v30 = sub_4B3DF0(v29, 1, 0, 1097859072, 600000, 1);
        else
          v30 = nullptr;
        LOBYTE(v125) = 35;
        return (uint32_t *)sub_50F850(Block, v30, 28);
      case 1030:
        v120 = 1;
        v121 = 0;
        v122[0] = 0xEA6041700000LL;
        v122[1] = 0x1C00000001LL;
        v28 = operator new(0x4ACu);
        v125 = 34;
LABEL_137:
        if ( v28 == nullptr )
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
        v118[0] = v24;
        v119[0] = 0;
        Blockv = operator new(0x64u);
        v125 = 28;
        if ( Blockv != nullptr )
          v25 = sub_50F270(80, 100);
        else
          v25 = 0;
        v125 = -1;
        v118[1] = v25;
        v119[1] = 0;
        v16 = operator new(0xC8u);
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
        v118[0] = v26;
        v119[0] = 0;
        Blockx = operator new(0x64u);
        v125 = 31;
        if ( Blockx != nullptr )
          v27 = sub_50F270(120, 100);
        else
          v27 = 0;
        v125 = -1;
        v118[1] = v27;
        v119[1] = 0;
        v16 = operator new(0xC8u);
        v125 = 32;
        goto LABEL_312;
      case 1047:
        Blockt = operator new(0xA8u);
        v125 = 25;
        if ( Blockt == nullptr )
          return nullptr;
        return (uint32_t *)sub_50FA30(Block);
      case 1048:
        v124 = operator new(0xC8u);
        v6 = 23;
        v125 = 23;
        if ( v124 == nullptr )
          return nullptr;
        v123 = operator new(0x80u);
        LOBYTE(v125) = 24;
        if ( v123 == nullptr )
          goto LABEL_233;
        v7 = sub_4D6810(1132593152, 700, 1, 1);
        goto LABEL_326;
      case 1049:
        v124 = operator new(0xC8u);
        v6 = 21;
        v125 = 21;
        if ( v124 == nullptr )
          return nullptr;
        v123 = operator new(0x64u);
        LOBYTE(v125) = 22;
        if ( v123 == nullptr )
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
        v12 = operator new(0x7Cu);
        v125 = 70;
        if ( v12 != nullptr )
          v13 = sub_4B3DF0(v12, 0, 0, 1092616192, 600000, 1);
        else
          v13 = nullptr;
        v125 = -1;
        v118[0] = v13;
        v119[0] = 26;
        v14 = operator new(0x7Cu);
        v125 = 71;
        if ( v14 != nullptr )
          v15 = sub_4B3DF0(v14, 3, 0, 1092616192, 600000, 1);
        else
          v15 = nullptr;
        v125 = -1;
        v118[1] = v15;
        v119[1] = 27;
        v16 = operator new(0xC8u);
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
        v124 = operator new(0xC8u);
        v6 = -96;
        v125 = 160;
        if ( v124 == nullptr )
          return nullptr;
        v123 = operator new(0x60u);
        LOBYTE(v125) = -95;
        if ( v123 != nullptr )
          goto LABEL_78;
        goto LABEL_321;
      case 1013:
        v124 = operator new(0xC8u);
        v125 = 164;
        if ( v124 != nullptr )
        {
          v123 = operator new(0x80u);
          LOBYTE(v125) = -91;
          if ( v123 != nullptr )
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
        v124 = operator new(0xC8u);
        v6 = -94;
        v125 = 162;
        if ( v124 == nullptr )
          return nullptr;
        v123 = operator new(0x60u);
        LOBYTE(v125) = -93;
        if ( v123 == nullptr )
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
        v124 = operator new(0xC8u);
        v125 = 41;
        if ( v124 == nullptr )
          return nullptr;
        v9 = operator new(0x7Cu);
        v123 = v9;
        LOBYTE(v125) = 42;
        if ( v9 != nullptr )
          v10 = sub_4B3DF0(v9, 12, 0, 1112014848, 20000, 1);
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
          result = (uint32_t *)sub_485DA0(a2);
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
      v123 = operator new(0x80u);
      LOBYTE(v125) = 78;
      if ( v123 != nullptr )
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
      v123 = operator new(0xC8u);
      v6 = 81;
      v125 = 81;
      if ( v123 == nullptr )
        return nullptr;
      v124 = operator new(0x80u);
      LOBYTE(v125) = 82;
      if ( v124 == nullptr )
        goto LABEL_233;
      v7 = sub_4D6810(1125842944, 1500, 1, 1);
      break;
    case 1002:
      v124 = operator new(0xC8u);
      v6 = -98;
      v125 = 158;
      if ( v124 == nullptr )
        return nullptr;
      v123 = operator new(0x64u);
      LOBYTE(v125) = -97;
      if ( v123 != nullptr )
        goto LABEL_324;
      goto LABEL_233;
    case 1003:
      v124 = operator new(0xC8u);
      v6 = -106;
      v125 = 150;
      if ( v124 == nullptr )
        return nullptr;
      v123 = operator new(0x80u);
      LOBYTE(v125) = -105;
      if ( v123 == nullptr )
        goto LABEL_321;
      v7 = sub_4D6810(1135542272, 2000, 1, 1);
      break;
    case 1004:
      v124 = operator new(0xC8u);
      v6 = -102;
      v125 = 154;
      if ( v124 == nullptr )
        return nullptr;
      v123 = operator new(0x64u);
      LOBYTE(v125) = -101;
      if ( v123 == nullptr )
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

