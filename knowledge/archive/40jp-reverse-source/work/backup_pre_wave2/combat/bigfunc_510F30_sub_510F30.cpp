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

  // ── [段 1] 初始化与分派总闸：清空两条输出槽，进入 Block 阈值四级 if 链（1055 → 4052 → 6505 → 6513） ──
  //   Block=物品/PO 的 ID；pBuf=输出对象数组、pBuf2=输出类型字数组（各 20 槽）；v125=编译器异常展开状态号
  memset(pBuf, 0, sizeof(pBuf));
  memset(pBuf2, 0, sizeof(pBuf2));
  // ── [段 2] Block > 1055 大区入口（本函数全部 PO 型物品 ID 都在这条链上） ──
  //   四级嵌套阈值依次收窄：>1055 → >4052 → >6505 → >6513
  if ( Block > 1055 )
  {
    if ( Block > 4052 )
    {
      if ( Block > 6505 )
      {
        if ( Block > 6513 )
        {
          // ── [段 3] Block > 6513 且非 6514：只剩 7099/7100 两型高级护符，其余 return nullptr ──
          if ( Block != 6514 )
          {
            if ( Block == 7099 )
            {
              // ── [段 4] case 7099 / 7100：两枚 30 分钟系护符 —— sub_4B3DF0 = CNChangeStatus(状态,1,50.0f,1800000ms) ──
              //   pBuf2 类型字 26/28；0x42480000=50.0f、1800000ms=30 分钟
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
          // ── [段 5] Block == 6514 主体：两枚 CNChangeStatus(25/26, 1, 10.0f, 1800000ms)，类型字 46/45 ──
          //   sub_50F990 = CNAppendageStackable 记录追加构造（0x50F850 的同构带三参追加版）
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
// ── [段 6] LABEL_433 公共尾（6514/1079 共用）：补一枚 CNChangeHp(550.0f,1000ms) 后提交 ──
//   sub_4D6810=CNChangeHp 构造（延滞伤/瞬回血）；0x44098000=550.0f；sub_602DA0(2,5.0,8) 写参量三元
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
        // ── [段 7] Block 处于 (6505, 6513] 的 switch：6513 / 6506 / 6511 / 6512 四型 ──
        switch ( Block )
        {
          // ── [段 8] case 6513：五枚 CNChangeStatus —— (0,0,100.0f)(1,0,100.0f)(3,1,-100.0f)(5,1,-100.0f)(20,1,-100.0f) ──
          //   全部 60000ms，类型字 26/28/27/30/23；前两枚为增益、后三枚 0xC2C80000=-100.0f 为减益系
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
          // ── [段 9] case 6506 / 6511 ──
          //   6506 → sub_50F7F0=CNItemScreamOfHysma 单对象构造；6511 → CNChangeStatus(12,0,50.0f,60000ms) 走 sub_50F850 提交
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
        // ── [段 10] 6512（与 case 1019 共用 LABEL_384）：sub_50FF30=CNOmozzaOfWorld 构造，三参留 0 ──
        if ( Block != 6512 )
          return nullptr;
LABEL_384:
        Blockce = operator new(0xB0u);
        v125 = 63;
        if ( Blockce != nullptr )
          return (uint32_t *)sub_50FF30(Block, 0, 0, 0);
        return nullptr;
      }
      // ── [段 11] case 6505：四枚 CNChangeStatus(16/17/18/19, 0, 15.0f, 1800000ms) 属性珠组，类型字 40..43 ──
      //   0x41700000=15.0f；与 case 1024（60000ms 短时版）为同组物品的两档时长
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
      // ── [段 12] Block 处于 (6501, 6505) 的三型：6502 / 6503 / 6504 ──
      //   6502=CNChangeStatus(8,1,10.0f,600000ms)+(7,1,10.0f,600000ms)；6503=(4,1)/(5,1) 同理但 1800000ms
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
          // ── [段 13] else 分支即 6504：单枚 CNChangeStatus(22, 0, 7.0f, 600000ms)，类型字 44 ──
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
      // ── [段 14] case 6501 / 6500：sub_50FC00=CNRateHpMp 构造（模式, 回复率, 时长） ──
      //   6501 → (1, 50, 100) 即 MP 回复；6500 → (0, 50, 100) 即 HP 回复
      if ( Block == 6501 )
      {
        Blockbz = operator new(0xB0u);
        v125 = 141;
        if ( Blockbz != nullptr )
          return (uint32_t *)sub_50FC00(6501, 1, 50, 100);
        return nullptr;
      }
      // ── [段 15] Block > 4102：只有 6500 有专属构造，其余统一 return nullptr ──
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
      // ── [段 16] 兜底门：Block 落在 4053..4078 或 4083..4086 一律 return nullptr ──
      //   仅 [4041..4052]、[4079..4082]、[4087..4102] 三区间穿透到段 35 的裸对象路径
      if ( Block < 4087 && (Block < 4079 || Block > 4082) )
        return nullptr;
    }
    else if ( Block < 4041 )
    {
      // ── [段 17] else if (Block < 4041)：1056..1088 段（护符/消耗品 PO 主区，共 30 型） ──
      //   每型骨架同构：new(0xC8) 结果壳 → new(小对象) 效果体 → sub_50F990/sub_50F850 提交
      switch ( Block )
      {
        // ── [段 18] case 1056-1060：回血/回蓝五连（sub_4D6810=CNChangeHp 瞬回血，sub_50F270=CNChangeMp 瞬回蓝） ──
        //   1056 CNChangeHp(190.0f,1500ms) / 1057 CNChangeMp(70,1000) / 1058 CNChangeMp(120,1500)
        //   1059 CNChangeHp(300.0f,700ms) / 1060 CNChangeMp(195,700)
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
        // ── [段 19] case 1061：双效果 —— CNChangeHp(200.0f,1000ms) + CNChangeMp(95,1000) 组合提交 ──
        //   尾部 sub_602DA0(8, 100.0, 3) 写参量三元（+180=8/+184=10000.0/+188=3）
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
        // ── [段 20] case 1062-1066：回血/回蓝五连之二（金额 100.0f/220.0f/290.0f 与 80/95） ──
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
        // ── [段 21] case 1067 / 1068 / 1069 ──
        //   1067 走 sub_50F850(150,0)；1068=CNChangeHp(300.0f,1000ms)+CNChangeStatus(5,1,20.0f,20000ms)
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
        // ── [段 22] case 1069-1072 ──
        //   1069 CNChangeMp(145,1000)+CNChangeStatus(2,0,30.0f,60000ms)；1070 双 CNChangeStatus(3,0)/(22,0) 20.0f 60s
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
        //   1071 双 CNChangeStatus(1,0,20.0f)/(21,0,50.0f) 60s；1072 五枚与 6513 完全同构（0/1/3/5/20 号） ──
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
        // ── [段 23] case 1074：sub_50FF30(1074, 0, 300, 0) = CNOmozzaOfWorld 三参版 ──
        case 1074:
          Blockbe = operator new(0xB0u);
          v125 = 7;
          if ( Blockbe == nullptr )
            return nullptr;
          return (uint32_t *)sub_50FF30(Block, 0, 300, 0);
        // ── [段 24] case 1075-1078：四型「单效果 + 时长」护符（280/100/280/380 系） ──
        //   1075 CNChangeHp(280.0f,2000ms) / 1076 CNChangeMp(150,700) / 1077 CNChangeHp(280.0f,100ms) / 1078 CNChangeHp(380.0f,100ms)
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
        // ── [段 25] case 1079 直接 goto LABEL_433（与 6514 共用 CNChangeHp 550.0f 尾） ──
        case 1079:
          goto LABEL_433;
        // ── [段 26] case 1080 / 1081：CNChangeHp(550.0f,1000ms)+sub_602DA0(15,10.0,8) / CNChangeMp(250,1000)+sub_602DA0(8,10.0,5) ──
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
        // ── [段 27] case 1082：武器属性变更 + 火焰护符 —— sub_510140(1,2,3)=CNChangeWeaponElement 属性参数包 ──
        //   对象 +40 写 60000（时长），随后 sub_510350(2,0,10,60000,1,CHARM_FIRE_USE) 注册火系属性珠，类型字 37/23
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
        // ── [段 28] case 1083-1088：CNRateHpMp 族（模式, 回复率, 时长） ──
        //   1083(0,15,1000) / 1084(1,15,1000) / 1085(1,30,100) / 1087(0,30,1000) / 1088(2,50,1000)
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
    // ── [段 29] Block 落在 [4041..4052]/[4079..4082]/[4087..4102] 三穿透区：裸构造兜底路径 ──
    //   new(0xB0) + sub_50F740=CNRDStackable 基类构造 + 挂 CNIncreaseStatusStackable::vftable（无效果参数）
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
  // ── [段 30] case 1055：单枚 CNChangeHp(100.0f,1000ms) 走 sub_50F850(1055, obj, 0) 提交 ──
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
  // ── [段 31] Block 处于 (1019, 1055) 区：1020..1054 段（属性护符 / 区域消耗品 / 主动状态三族） ──
  if ( Block > 1019 )
  {
    switch ( Block )
    {
      // ── [段 32] case 1020-1023：★ 四系属性护符本体 —— sub_510350(系别,0,30,60000,1,标签串) ──
      //   1020 CHARM_FIRE_USE / 1021 CHARM_ICE_USE / 1022 CHARM_MOON_USE / 1023 CHARM_SUN_USE
      //   sub_510350 = CNChangeElementTolerance 构造：标签串存 +27（+32=容量 15），即元素抗性变更 PO；均走 sub_50F850(type 23)
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
      // ── [段 33] case 1024：四枚 CNChangeStatus(16/17/18/19, 0, 15.0f, 60000ms)（与 6505 同组，时长缩为 1 分钟） ──
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
      // ── [段 34] case 1025 / 1026 ──
      //   1025 → sub_50F7F0=CNItemScreamOfHysma；1026 → CNChangeStatus(0,0,15.0f,600000ms) 单枚
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
      // ── [段 35] case 1027 / 1028 / 1030：★ CNItemAreaStackable 区域放置型消耗品（sub_510000） ──
      //   参数块 v120/v121/v122：状态字 12/0/1 + 数据 0x4E2042480000 与 0xEA6041700000 + 数据长 21/12
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
      // ── [段 36] case 1031 / 1034-1046：CNIncreaseStatusStackable 裸构造（sub_50F7C0）—— 15 个 ID 共用一个无参构造 ──
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
      // ── [段 37] case 1032 / 1033：CNChangeHp(80.0f,100ms)/(120.0f,100ms) 配 CNChangeMp(80,100)/(120,100) ──
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
      // ── [段 38] case 1047：sub_50FA30 = CNCoinOfFortune 构造（幸运硬币，单对象无参） ──
      case 1047:
        Blockt = operator new(0xA8u);
        v125 = 25;
        if ( Blockt == nullptr )
          return nullptr;
        return (uint32_t *)sub_50FA30(Block);
      // ── [段 39] case 1048 / 1049：CNChangeHp(260.0f,700ms) / CNChangeMp(130,700) 单效果两型 ──
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
      // ── [段 40] case 1050-1054：★ CNActiveStatusStackable 主动状态消耗品（sub_510640 + sub_602BC0 记录追加） ──
      //   状态索引依次 3 / 7 / 5 / 15 / 11；sub_602BC0(索引, 0, -1, 1) 是 16 字节栈记录尾插的薄封装
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
  // ── [段 41] case 1019：goto LABEL_384（与 6512 共用 CNOmozzaOfWorld 构造） ──
  if ( Block == 1019 )
    goto LABEL_384;
  if ( Block > 1006 )
  {
    // ── [段 42] Block 处于 (1006, 1019) 区：1007..1018 段 ──
    switch ( Block )
    {
      // ── [段 43] case 1007：两枚 CNChangeStatus(0,0,10.0f)/(3,0,10.0f)，600000ms ──
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
      // ── [段 44] case 1008 / 1010：CNActiveStatusStackable（sub_510640）—— 1008 参数 (0,0)、1010 参数 (200,0) ──
      //   两者收尾 sub_602BC0(2, 0, -1, 1) 状态索引 2
      case 1008:
        Blockl = operator new(0xBCu);
        v125 = 68;
        if ( Blockl == nullptr )
          goto LABEL_67;
        v11 = sub_510640(Block, 0, 0);
        goto LABEL_68;
      // ── [段 45] case 1009：CNAntiFreezePotion 防冻药水（sub_510E40(200,0)）+ sub_602BC0(1,…) ──
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
      // ── [段 46] case 1011 / 1014：CNChangeActiveProperty（sub_510230(4,1000,60000)）属性激活 PO ──
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
      // ── [段 47] case 1013：CNChangeHp(180.0f,2000ms) + sub_50F850 提交 + 尾部 sub_602DA0(2,30.0,2) ──
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
      // ── [段 48] case 1015：CNSummonMonsterStackable 召唤怪物消耗品（sub_5104B0(1,5,14) 怪物 ID+数量区间） ──
      case 1015:
        Blocki = operator new(0xB0u);
        v125 = 64;
        if ( Blocki == nullptr )
          return nullptr;
        return (uint32_t *)sub_5104B0(Block, 1, 5, 14);
      // ── [段 49] case 1016：CNChangeStatus(12, 0, 50.0f, 20000ms)（case 6511 的短时版），类型字 36 ──
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
      // ── [段 50] case 1017 / 1018：CNItemAreaStackable 包 48018（数据长 12）—— 段 35 两型的低配版 ──
      //   前 4 字节 60000 时长 + 1 字节状态 0/1 + 类型字 37
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
  // ── [段 51] case 1006：CNActiveStatusStackable(1006,0,0) + sub_602BC0(12, 100.0f, 7, 1) ──
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
  // ── [段 52] Block <= 1000 区（小 ID 段）：仅 0 / 3 / 8 / 10 / 14 / 15 六型有专属构造 ──
  if ( Block <= 1000 )
  {
    if ( Block != 1000 )
    {
      switch ( Block )
      {
        // ── [段 53] case 0 / 3 / 8 / 10 / 14 / 15：裸单对象族 ──
        //   0 → sub_485DA0=CNRDMoney 金币掉落物（吃 nArg2）；3 → CNIncreaseStatusStackable
        //   8 → sub_50FA90=CNTouchOfRemy；10 → sub_50FE70=CNCallStorageBird；14/15 → sub_50FFB0=CNUsableStackable
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
    // ── [段 54] case 1000：CNChangeHp(50.0f,1000ms) 走 sub_50F850(1000, obj, 0) ──
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
  // ── [段 55] Block 处于 (1000, 1006) 区：1001..1005 五型 ──
  //   1001 CNChangeHp(155.0f,1500ms) / 1002 CNChangeMp(120,1500) / 1003 CNChangeHp(350.0f,2000ms)
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
    //   1004 CNChangeMp(55,1000)；1005 → CNAntiFreezePotion(0,0) 防冻药水
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
// ── [段 56] 统一提交尾 LABEL_326：sub_50F850(Block, 效果对象, 0) ──
//   所有「CNChangeHp/CNChangeMp 单效果」路径共用：v6 为异常展开状态号，先还原再调构造
LABEL_326:
  LOBYTE(v125) = v6;
  return (uint32_t *)sub_50F850(Block, v7, 0);
}

