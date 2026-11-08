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
  memset(pBuf, 0, sizeof(pBuf));  // 清零输出缓冲
  memset(pBuf2, 0, sizeof(pBuf2));  // 清零输出缓冲
  // ── [段 2] Block > 1055 大区入口（本函数全部 PO 型物品 ID 都在这条链上） ──
  //   四级嵌套阈值依次收窄：>1055 → >4052 → >6505 → >6513
  if ( Block > 1055 )  // Block > 1055：大区入口（本函数物品 ID 全在此链）
  {
    if ( Block > 4052 )  // Block > 4052：中区
    {
      if ( Block > 6505 )  // Block > 6505：护符区
      {
        if ( Block > 6513 )  // Block > 6513：仅剩 7099/7100
        {
          // ── [段 3] Block > 6513 且非 6514：只剩 7099/7100 两型高级护符，其余 return nullptr ──
          if ( Block != 6514 )
          {
            if ( Block == 7099 )
            {
              // ── [段 4] case 7099 / 7100：两枚 30 分钟系护符 —— sub_4B3DF0 = CNChangeStatus(状态,1,50.0f,1800000ms) ──
              //   pBuf2 类型字 26/28；0x42480000=50.0f、1800000ms=30 分钟
              pMem = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
              v125 = 166;  // 异常展开状态号 → 166
              if ( pMem != nullptr )  // 非空（new 成功）才继续构造
                v112 = sub_4B3DF0(pMem, 0, 0, 1112014848, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=0, 标志=0, 数值=50.0f, 时长=1800000ms, 1)
              else
                v112 = nullptr;
              v125 = -1;  // 异常展开状态号 → -1
              pBuf[0] = v112;  // 输出槽 0 存效果对象 v112
              pBuf2[0] = 26;  // 输出槽 0 类型字 = 26
              Blockcj = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
              v125 = 167;  // 异常展开状态号 → 167
              if ( Blockcj != nullptr )  // 非空（new 成功）才继续构造
                return (uint32_t *)sub_50F990(7099, pBuf, pBuf2, 1);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=7099, 输出槽, 类型槽, 记录数=1)
            }
            else if ( Block == 7100 )
            {
              pMem2 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
              v125 = 168;  // 异常展开状态号 → 168
              v110 = pMem2 != nullptr ? sub_4B3DF0(pMem2, 1, 0, 1112014848, 1800000, 1) : nullptr;  // 三元：非空则 CNChangeStatus 状态附加(状态=1, 标志=0, 数值=50.0f, 时长=1800000ms, 1)，否则 nullptr
              v125 = -1;  // 异常展开状态号 → -1
              pBuf[0] = v110;  // 输出槽 0 存效果对象 v110
              pBuf2[0] = 28;  // 输出槽 0 类型字 = 28
              Blockci = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
              v125 = 169;  // 异常展开状态号 → 169
              if ( Blockci != nullptr )  // 非空（new 成功）才继续构造
                return (uint32_t *)sub_50F990(7100, pBuf, pBuf2, 1);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=7100, 输出槽, 类型槽, 记录数=1)
            }
            return nullptr;  // 返回空（未识别 ID）
          }
          // ── [段 5] Block == 6514 主体：两枚 CNChangeStatus(25/26, 1, 10.0f, 1800000ms)，类型字 46/45 ──
          //   sub_50F990 = CNAppendageStackable 记录追加构造（0x50F850 的同构带三参追加版）
          pMem3 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 128;  // 异常展开状态号 → 128
          if ( pMem3 != nullptr )  // 非空（new 成功）才继续构造
            v114 = sub_4B3DF0(pMem3, 25, 1, 1092616192, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=25, 标志=1, 数值=10.0f, 时长=1800000ms, 1)
          else
            v114 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v114;  // 输出槽 0 存效果对象 v114
          pBuf2[0] = 46;  // 输出槽 0 类型字 = 46
          pMem4 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 129;  // 异常展开状态号 → 129
          if ( pMem4 != nullptr )  // 非空（new 成功）才继续构造
            v116 = sub_4B3DF0(pMem4, 26, 1, 1092616192, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=26, 标志=1, 数值=10.0f, 时长=1800000ms, 1)
          else
            v116 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v116;  // 输出槽 1 存效果对象 v116
          pBuf2[1] = 45;  // 输出槽 1 类型字 = 45
          Blockck = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 130;  // 异常展开状态号 → 130
          if ( Blockck != nullptr )  // 非空（new 成功）才继续构造
            sub_50F990(6514, pBuf, pBuf2, 2);  // CNAppendageStackable 记录追加构造（三参版）(Block=6514, 输出槽, 类型槽, 记录数=2)
          v125 = -1;  // 异常展开状态号 → -1
// ── [段 6] LABEL_433 公共尾（6514/1079 共用）：补一枚 CNChangeHp(550.0f,1000ms) 后提交 ──
//   sub_4D6810=CNChangeHp 构造（延滞伤/瞬回血）；0x44098000=550.0f；sub_602DA0(2,5.0,8) 写参量三元
LABEL_433:
          Blockcl = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          v125 = 131;  // 异常展开状态号 → 131
          if ( Blockcl != nullptr )  // 非空（new 成功）才继续构造
            v117 = sub_4D6810(1141473280, 1000, 1, 1);  // 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
          else
            v117 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v117;  // 输出槽 0 存效果对象 v117
          pBuf2[0] = 0;  // 输出槽 0 类型字 = 0
          Blockcm = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 132;  // 异常展开状态号 → 132
          if ( Blockcm != nullptr )  // 非空（new 成功）才继续构造
            v18 = sub_50F990(Block, pBuf, pBuf2, 1);  // 存 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=1)
          else
            v18 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          sub_602DA0(2, 5.0, 8);  // 参量三元写入 +180/+184/+188(槽=2, 值=5.0, 档=8)
          return (uint32_t *)v18;
        }
        // ── [段 7] Block 处于 (6505, 6513] 的 switch：6513 / 6506 / 6511 / 6512 四型 ──
        switch ( Block )
        {
          // ── [段 8] case 6513：五枚 CNChangeStatus —— (0,0,100.0f)(1,0,100.0f)(3,1,-100.0f)(5,1,-100.0f)(20,1,-100.0f) ──
          //   全部 60000ms，类型字 26/28/27/30/23；前两枚为增益、后三枚 0xC2C80000=-100.0f 为减益系
          case 6513:
            pMem5 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
            v125 = 122;  // 异常展开状态号 → 122
            if ( pMem5 != nullptr )  // 非空（new 成功）才继续构造
              v100 = sub_4B3DF0(pMem5, 0, 0, 1120403456, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=0, 标志=0, 数值=100.0f, 时长=60000ms, 1)
            else
              v100 = nullptr;
            v125 = -1;  // 异常展开状态号 → -1
            pBuf[0] = v100;  // 输出槽 0 存效果对象 v100
            pBuf2[0] = 26;  // 输出槽 0 类型字 = 26
            pMem6 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
            v125 = 123;  // 异常展开状态号 → 123
            if ( pMem6 != nullptr )  // 非空（new 成功）才继续构造
              v102 = sub_4B3DF0(pMem6, 1, 0, 1120403456, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=1, 标志=0, 数值=100.0f, 时长=60000ms, 1)
            else
              v102 = nullptr;
            v125 = -1;  // 异常展开状态号 → -1
            pBuf[1] = v102;  // 输出槽 1 存效果对象 v102
            pBuf2[1] = 28;  // 输出槽 1 类型字 = 28
            pMem7 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
            v125 = 124;  // 异常展开状态号 → 124
            if ( pMem7 != nullptr )  // 非空（new 成功）才继续构造
              v104 = sub_4B3DF0(pMem7, 3, 1, -1027080192, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=3, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
            else
              v104 = nullptr;
            v125 = -1;  // 异常展开状态号 → -1
            pBuf[2] = v104;  // 输出槽 2 存效果对象 v104
            pBuf2[2] = 27;  // 输出槽 2 类型字 = 27
            pMem8 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
            v125 = 125;  // 异常展开状态号 → 125
            if ( pMem8 != nullptr )  // 非空（new 成功）才继续构造
              v106 = sub_4B3DF0(pMem8, 5, 1, -1027080192, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=5, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
            else
              v106 = nullptr;
            v125 = -1;  // 异常展开状态号 → -1
            pBuf[3] = v106;  // 输出槽 3 存效果对象 v106
            pBuf2[3] = 30;  // 输出槽 3 类型字 = 30
            pMem9 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
            v125 = 126;  // 异常展开状态号 → 126
            if ( pMem9 != nullptr )  // 非空（new 成功）才继续构造
              v108 = sub_4B3DF0(pMem9, 20, 1, -1027080192, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=20, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
            else
              v108 = nullptr;
            v125 = -1;  // 异常展开状态号 → -1
            pBuf[4] = v108;  // 输出槽 4 存效果对象 v108
            pBuf2[4] = 23;  // 输出槽 4 类型字 = 23
            Blockch = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
            v125 = 127;  // 异常展开状态号 → 127
            if ( Blockch != nullptr )  // 非空（new 成功）才继续构造
              return (uint32_t *)sub_50F990(6513, pBuf, pBuf2, 5);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=6513, 输出槽, 类型槽, 记录数=5)
            return nullptr;  // 返回空（未识别 ID）
          // ── [段 9] case 6506 / 6511 ──
          //   6506 → sub_50F7F0=CNItemScreamOfHysma 单对象构造；6511 → CNChangeStatus(12,0,50.0f,60000ms) 走 sub_50F850 提交
          case 6506:  // case 6506 → 返回 CNItemScreamOfHysma 构造
LABEL_391:
            Blockcg = operator new(0xA4u);  // 分配 0xA4 字节对象壳（164 字节）
            v125 = 26;  // 异常展开状态号 → 26
            if ( Blockcg != nullptr )  // 非空（new 成功）才继续构造
              return (uint32_t *)sub_50F7F0(Block);  // 返回 CNItemScreamOfHysma 构造(Block)
            return nullptr;  // 返回空（未识别 ID）
          case 6511:
            Blockcf = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
            v125 = 43;  // 异常展开状态号 → 43
            if ( Blockcf != nullptr )  // 非空（new 成功）才继续构造
            {
              pMem10 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
              pMem20 = pMem10;
              LOBYTE(v125) = 44;  // 低字节写异常展开状态号 → 44
              if ( pMem10 != nullptr )  // 非空（new 成功）才继续构造
                v98 = sub_4B3DF0(pMem10, 12, 0, 1112014848, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=12, 标志=0, 数值=50.0f, 时长=60000ms, 1)
              else
                v98 = nullptr;
              LOBYTE(v125) = 43;  // 低字节写异常展开状态号 → 43
              return (uint32_t *)sub_50F850(6511, v98, 36);  // 返回 CNAppendageStackable 记录追加构造(Block=6511, 效果对象=v98, 类型字=36)
            }
            return nullptr;  // 返回空（未识别 ID）
          default:
            break;
        }
        // ── [段 10] 6512（与 case 1019 共用 LABEL_384）：sub_50FF30=CNOmozzaOfWorld 构造，三参留 0 ──
        if ( Block != 6512 )
          return nullptr;  // 返回空（未识别 ID）
LABEL_384:
        Blockce = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
        v125 = 63;  // 异常展开状态号 → 63
        if ( Blockce != nullptr )  // 非空（new 成功）才继续构造
          return (uint32_t *)sub_50FF30(Block, 0, 0, 0);  // 返回 CNOmozzaOfWorld 构造(Block, 0, 0, 0)
        return nullptr;  // 返回空（未识别 ID）
      }
      // ── [段 11] case 6505：四枚 CNChangeStatus(16/17/18/19, 0, 15.0f, 1800000ms) 属性珠组，类型字 40..43 ──
      //   0x41700000=15.0f；与 case 1024（60000ms 短时版）为同组物品的两档时长
      if ( Block == 6505 )  // Block == 6505：护符区
      {
        pMem11 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        v125 = 58;  // 异常展开状态号 → 58
        if ( pMem11 != nullptr )  // 非空（new 成功）才继续构造
          v90 = sub_4B3DF0(pMem11, 16, 0, 1097859072, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=16, 标志=0, 数值=15.0f, 时长=1800000ms, 1)
        else
          v90 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[0] = v90;  // 输出槽 0 存效果对象 v90
        pBuf2[0] = 40;  // 输出槽 0 类型字 = 40
        pMem12 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        v125 = 59;  // 异常展开状态号 → 59
        if ( pMem12 != nullptr )  // 非空（new 成功）才继续构造
          v92 = sub_4B3DF0(pMem12, 17, 0, 1097859072, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=17, 标志=0, 数值=15.0f, 时长=1800000ms, 1)
        else
          v92 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[1] = v92;  // 输出槽 1 存效果对象 v92
        pBuf2[1] = 41;  // 输出槽 1 类型字 = 41
        pMem13 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        v125 = 60;  // 异常展开状态号 → 60
        if ( pMem13 != nullptr )  // 非空（new 成功）才继续构造
          v94 = sub_4B3DF0(pMem13, 18, 0, 1097859072, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=18, 标志=0, 数值=15.0f, 时长=1800000ms, 1)
        else
          v94 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[2] = v94;  // 输出槽 2 存效果对象 v94
        pBuf2[2] = 42;  // 输出槽 2 类型字 = 42
        pMem14 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        v125 = 61;  // 异常展开状态号 → 61
        if ( pMem14 != nullptr )  // 非空（new 成功）才继续构造
          v96 = sub_4B3DF0(pMem14, 19, 0, 1097859072, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=19, 标志=0, 数值=15.0f, 时长=1800000ms, 1)
        else
          v96 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[3] = v96;  // 输出槽 3 存效果对象 v96
        pBuf2[3] = 43;  // 输出槽 3 类型字 = 43
        Blockcd = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 62;  // 异常展开状态号 → 62
        if ( Blockcd != nullptr )  // 非空（new 成功）才继续构造
          return (uint32_t *)sub_50F990(6505, pBuf, pBuf2, 4);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=6505, 输出槽, 类型槽, 记录数=4)
        return nullptr;  // 返回空（未识别 ID）
      }
      // ── [段 12] Block 处于 (6501, 6505) 的三型：6502 / 6503 / 6504 ──
      //   6502=CNChangeStatus(8,1,10.0f,600000ms)+(7,1,10.0f,600000ms)；6503=(4,1)/(5,1) 同理但 1800000ms
      if ( Block > 6501 )  // Block > 6501：6502-6504 三型
      {
        if ( Block == 6502 )
        {
          pMem15 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 142;  // 异常展开状态号 → 142
          if ( pMem15 != nullptr )  // 非空（new 成功）才继续构造
            v86 = sub_4B3DF0(pMem15, 8, 1, 1092616192, 600000, 1);  // 存 CNChangeStatus 状态附加(状态=8, 标志=1, 数值=10.0f, 时长=600000ms, 1)
          else
            v86 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v86;  // 输出槽 0 存效果对象 v86
          pBuf2[0] = 47;  // 输出槽 0 类型字 = 47
          pMem16 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 143;  // 异常展开状态号 → 143
          if ( pMem16 != nullptr )  // 非空（new 成功）才继续构造
            v88 = sub_4B3DF0(pMem16, 7, 1, 1092616192, 600000, 1);  // 存 CNChangeStatus 状态附加(状态=7, 标志=1, 数值=10.0f, 时长=600000ms, 1)
          else
            v88 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v88;  // 输出槽 1 存效果对象 v88
          pBuf2[1] = 48;  // 输出槽 1 类型字 = 48
          Blockcc = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 144;  // 异常展开状态号 → 144
          if ( Blockcc != nullptr )  // 非空（new 成功）才继续构造
            return (uint32_t *)sub_50F990(6502, pBuf, pBuf2, 2);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=6502, 输出槽, 类型槽, 记录数=2)
        }
        else if ( Block == 6503 )
        {
          pMem17 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 145;  // 异常展开状态号 → 145
          if ( pMem17 != nullptr )  // 非空（new 成功）才继续构造
            v82 = sub_4B3DF0(pMem17, 4, 1, 1092616192, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=4, 标志=1, 数值=10.0f, 时长=1800000ms, 1)
          else
            v82 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v82;  // 输出槽 0 存效果对象 v82
          pBuf2[0] = 49;  // 输出槽 0 类型字 = 49
          pMem18 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 146;  // 异常展开状态号 → 146
          if ( pMem18 != nullptr )  // 非空（new 成功）才继续构造
            v84 = sub_4B3DF0(pMem18, 5, 1, 1092616192, 1800000, 1);  // 存 CNChangeStatus 状态附加(状态=5, 标志=1, 数值=10.0f, 时长=1800000ms, 1)
          else
            v84 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v84;  // 输出槽 1 存效果对象 v84
          pBuf2[1] = 50;  // 输出槽 1 类型字 = 50
          Blockcb = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 147;  // 异常展开状态号 → 147
          if ( Blockcb != nullptr )  // 非空（new 成功）才继续构造
            return (uint32_t *)sub_50F990(6503, pBuf, pBuf2, 2);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=6503, 输出槽, 类型槽, 记录数=2)
        }
        else
        {
          // ── [段 13] else 分支即 6504：单枚 CNChangeStatus(22, 0, 7.0f, 600000ms)，类型字 44 ──
          pMem19 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 111;  // 异常展开状态号 → 111
          if ( pMem19 != nullptr )  // 非空（new 成功）才继续构造
            v80 = sub_4B3DF0(pMem19, 22, 0, 1088421888, 600000, 1);  // 存 CNChangeStatus 状态附加(状态=22, 标志=0, 数值=7.0f, 时长=600000ms, 1)
          else
            v80 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v80;  // 输出槽 0 存效果对象 v80
          pBuf2[0] = 44;  // 输出槽 0 类型字 = 44
          Blockca = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 112;  // 异常展开状态号 → 112
          if ( Blockca != nullptr )  // 非空（new 成功）才继续构造
            return (uint32_t *)sub_50F990(6504, pBuf, pBuf2, 1);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=6504, 输出槽, 类型槽, 记录数=1)
        }
        return nullptr;  // 返回空（未识别 ID）
      }
      // ── [段 14] case 6501 / 6500：sub_50FC00=CNRateHpMp 构造（模式, 回复率, 时长） ──
      //   6501 → (1, 50, 100) 即 MP 回复；6500 → (0, 50, 100) 即 HP 回复
      if ( Block == 6501 )  // Block == 6501：6502-6504 三型
      {
        Blockbz = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
        v125 = 141;  // 异常展开状态号 → 141
        if ( Blockbz != nullptr )  // 非空（new 成功）才继续构造
          return (uint32_t *)sub_50FC00(6501, 1, 50, 100);  // 返回 CNRateHpMp 回复率构造(模式=MP, 回复率=50, 时长=100)
        return nullptr;  // 返回空（未识别 ID）
      }
      // ── [段 15] Block > 4102：只有 6500 有专属构造，其余统一 return nullptr ──
      if ( Block > 4102 )  // Block > 4102：仅 6500
      {
        if ( Block == 6500 )
        {
          Blockby = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
          v125 = 140;  // 异常展开状态号 → 140
          if ( Blockby != nullptr )  // 非空（new 成功）才继续构造
            return (uint32_t *)sub_50FC00(6500, 0, 50, 100);  // 返回 CNRateHpMp 回复率构造(模式=HP, 回复率=50, 时长=100)
        }
        return nullptr;  // 返回空（未识别 ID）
      }
      // ── [段 16] 兜底门：Block 落在 4053..4078 或 4083..4086 一律 return nullptr ──
      //   仅 [4041..4052]、[4079..4082]、[4087..4102] 三区间穿透到段 35 的裸对象路径
      if ( Block < 4087 && (Block < 4079 || Block > 4082) )
        return nullptr;  // 返回空（未识别 ID）
    }
    else if ( Block < 4041 )  // Block < 4041：护符/消耗品主区外
    {
      // ── [段 17] else if (Block < 4041)：1056..1088 段（护符/消耗品 PO 主区，共 30 型） ──
      //   每型骨架同构：new(0xC8) 结果壳 → new(小对象) 效果体 → sub_50F990/sub_50F850 提交
      switch ( Block )
      {
        // ── [段 18] case 1056-1060：回血/回蓝五连（sub_4D6810=CNChangeHp 瞬回血，sub_50F270=CNChangeMp 瞬回蓝） ──
        //   1056 CNChangeHp(190.0f,1500ms) / 1057 CNChangeMp(70,1000) / 1058 CNChangeMp(120,1500)
        //   1059 CNChangeHp(300.0f,700ms) / 1060 CNChangeMp(195,700)
        case 1056:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 79;
          v125 = 79;  // 异常展开状态号 → 79
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = 80;  // 低字节写异常展开状态号 → 80
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_325;  // 跳 LABEL_325
          v7 = sub_4D6810(1128136704, 1500, 1, 1);  // 存 CNChangeHp 回血(伤害值=190.0f, 时长=1500ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1057:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = -104;
          v125 = 152;  // 异常展开状态号 → 152
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          LOBYTE(v125) = -103;  // 低字节写异常展开状态号 → -103
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_321;  // 跳 LABEL_321
          v7 = sub_50F270(70, 1000);  // 存 CNChangeMp 回蓝(MP=70, 时长=1000ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1058:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = -100;
          v125 = 156;  // 异常展开状态号 → 156
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          LOBYTE(v125) = -99;  // 低字节写异常展开状态号 → -99
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_325;  // 跳 LABEL_325
LABEL_324:
          v7 = sub_50F270(120, 1500);  // 存 CNChangeMp 回蓝(MP=120, 时长=1500ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1059:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 83;
          v125 = 83;  // 异常展开状态号 → 83
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = 84;  // 低字节写异常展开状态号 → 84
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_233;  // 跳 LABEL_233
          v7 = sub_4D6810(1133903872, 700, 1, 1);  // 存 CNChangeHp 回血(伤害值=300.0f, 时长=700ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1060:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 85;
          v125 = 85;  // 异常展开状态号 → 85
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          LOBYTE(v125) = 86;  // 低字节写异常展开状态号 → 86
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_321;  // 跳 LABEL_321
          v7 = sub_50F270(195, 700);  // 存 CNChangeMp 回蓝(MP=195, 时长=700ms)
          goto LABEL_326;  // 跳 LABEL_326
        // ── [段 19] case 1061：双效果 —— CNChangeHp(200.0f,1000ms) + CNChangeMp(95,1000) 组合提交 ──
        //   尾部 sub_602DA0(8, 100.0, 3) 写参量三元（+180=8/+184=10000.0/+188=3）
        case 1061:
          Blockbf = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          v125 = 87;  // 异常展开状态号 → 87
          if ( Blockbf != nullptr )  // 非空（new 成功）才继续构造
            v46 = sub_4D6810(1128792064, 1000, 1, 1);  // 存 CNChangeHp 回血(伤害值=200.0f, 时长=1000ms)
          else
            v46 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v46;  // 输出槽 0 存效果对象 v46
          pBuf2[0] = 0;  // 输出槽 0 类型字 = 0
          Blockbg = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          v125 = 88;  // 异常展开状态号 → 88
          if ( Blockbg != nullptr )  // 非空（new 成功）才继续构造
            v47 = sub_50F270(95, 1000);  // 存 CNChangeMp 回蓝(MP=95, 时长=1000ms)
          else
            v47 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v47;  // 输出槽 1 存效果对象 v47
          pBuf2[1] = 0;  // 输出槽 1 类型字 = 0
          Blockbh = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 89;  // 异常展开状态号 → 89
          if ( Blockbh != nullptr )  // 非空（new 成功）才继续构造
          {
            v18 = sub_50F990(Block, pBuf, pBuf2, 2);  // 存 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=2)
            v125 = -1;  // 异常展开状态号 → -1
            sub_602DA0(8, 100.0, 3);  // 参量三元写入 +180/+184/+188(槽=8, 值=100.0, 档=3)
          }
          else
          {
            v18 = 0;
            v125 = -1;  // 异常展开状态号 → -1
            sub_602DA0(8, 100.0, 3);  // 参量三元写入 +180/+184/+188(槽=8, 值=100.0, 档=3)
          }
          return (uint32_t *)v18;
        // ── [段 20] case 1062-1066：回血/回蓝五连之二（金额 100.0f/220.0f/290.0f 与 80/95） ──
        case 1062:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 90;
          v125 = 90;  // 异常展开状态号 → 90
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = 91;  // 低字节写异常展开状态号 → 91
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_321;  // 跳 LABEL_321
          v7 = sub_4D6810(1120403456, 1000, 1, 1);  // 存 CNChangeHp 回血(伤害值=100.0f, 时长=1000ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1063:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 92;
          v125 = 92;  // 异常展开状态号 → 92
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = 93;  // 低字节写异常展开状态号 → 93
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_325;  // 跳 LABEL_325
          v7 = sub_4D6810(1130102784, 700, 1, 1);  // 存 CNChangeHp 回血(伤害值=220.0f, 时长=700ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1064:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 94;
          v125 = 94;  // 异常展开状态号 → 94
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = 95;  // 低字节写异常展开状态号 → 95
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_233;  // 跳 LABEL_233
          v7 = sub_4D6810(1133576192, 700, 1, 1);  // 存 CNChangeHp 回血(伤害值=290.0f, 时长=700ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1065:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 96;
          v125 = 96;  // 异常展开状态号 → 96
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          LOBYTE(v125) = 97;  // 低字节写异常展开状态号 → 97
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_321;  // 跳 LABEL_321
          v7 = sub_50F270(80, 700);  // 存 CNChangeMp 回蓝(MP=80, 时长=700ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1066:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 98;
          v125 = 98;  // 异常展开状态号 → 98
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          LOBYTE(v125) = 99;  // 低字节写异常展开状态号 → 99
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_325;  // 跳 LABEL_325
          v7 = sub_50F270(95, 700);  // 存 CNChangeMp 回蓝(MP=95, 时长=700ms)
          goto LABEL_326;  // 跳 LABEL_326
        // ── [段 21] case 1067 / 1068 / 1069 ──
        //   1067 走 sub_50F850(150,0)；1068=CNChangeHp(300.0f,1000ms)+CNChangeStatus(5,1,20.0f,20000ms)
        case 1067:
          Blockbi = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 100;  // 异常展开状态号 → 100
          if ( Blockbi == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem20 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          LOBYTE(v125) = 101;  // 低字节写异常展开状态号 → 101
          if ( pMem20 != nullptr )  // 非空（new 成功）才继续构造
          {
            v48 = sub_50F270(150, 700);  // 存 CNChangeMp 回蓝(MP=150, 时长=700ms)
            LOBYTE(v125) = 100;  // 低字节写异常展开状态号 → 100
            return (uint32_t *)sub_50F850(Block, v48, 0);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v48, 类型字=0)
          }
          else
          {
            LOBYTE(v125) = 100;  // 低字节写异常展开状态号 → 100
            return (uint32_t *)sub_50F850(Block, 0, 0);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=0, 类型字=0)
          }
        case 1068:
          Blockbj = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          v125 = 102;  // 异常展开状态号 → 102
          if ( Blockbj != nullptr )  // 非空（new 成功）才继续构造
            v49 = sub_4D6810(1133903872, 1000, 1, 1);  // 存 CNChangeHp 回血(伤害值=300.0f, 时长=1000ms)
          else
            v49 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v49;  // 输出槽 0 存效果对象 v49
          pBuf2[0] = 0;  // 输出槽 0 类型字 = 0
          pMem22 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 103;  // 异常展开状态号 → 103
          if ( pMem22 != nullptr )  // 非空（new 成功）才继续构造
            v51 = sub_4B3DF0(pMem22, 5, 1, 1101004800, 20000, 1);  // 存 CNChangeStatus 状态附加(状态=5, 标志=1, 数值=20.0f, 时长=20000ms, 1)
          else
            v51 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v51;  // 输出槽 1 存效果对象 v51
          pBuf2[1] = 30;  // 输出槽 1 类型字 = 30
          Blockbk = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 104;  // 异常展开状态号 → 104
          if ( Blockbk == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=2)
        // ── [段 22] case 1069-1072 ──
        //   1069 CNChangeMp(145,1000)+CNChangeStatus(2,0,30.0f,60000ms)；1070 双 CNChangeStatus(3,0)/(22,0) 20.0f 60s
        case 1069:  // case 1069 → CNChangeMp 构造
          Blockbl = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          v125 = 105;  // 异常展开状态号 → 105
          if ( Blockbl != nullptr )  // 非空（new 成功）才继续构造
            v52 = sub_50F270(145, 1000);  // 存 CNChangeMp 回蓝(MP=145, 时长=1000ms)
          else
            v52 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v52;  // 输出槽 0 存效果对象 v52
          pBuf2[0] = 0;  // 输出槽 0 类型字 = 0
          pMem23 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 106;  // 异常展开状态号 → 106
          if ( pMem23 != nullptr )  // 非空（new 成功）才继续构造
            v54 = sub_4B3DF0(pMem23, 2, 0, 1106247680, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=2, 标志=0, 数值=30.0f, 时长=60000ms, 1)
          else
            v54 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v54;  // 输出槽 1 存效果对象 v54
          pBuf2[1] = 29;  // 输出槽 1 类型字 = 29
          Blockbm = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 107;  // 异常展开状态号 → 107
          if ( Blockbm == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=2)
        case 1070:
          pMem24 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 108;  // 异常展开状态号 → 108
          if ( pMem24 != nullptr )  // 非空（new 成功）才继续构造
            v56 = sub_4B3DF0(pMem24, 3, 0, 1101004800, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=3, 标志=0, 数值=20.0f, 时长=60000ms, 1)
          else
            v56 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v56;  // 输出槽 0 存效果对象 v56
          pBuf2[0] = 26;  // 输出槽 0 类型字 = 26
          pMem25 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 109;  // 异常展开状态号 → 109
          if ( pMem25 != nullptr )  // 非空（new 成功）才继续构造
            v58 = sub_4B3DF0(pMem25, 22, 0, 1101004800, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=22, 标志=0, 数值=20.0f, 时长=60000ms, 1)
          else
            v58 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v58;  // 输出槽 1 存效果对象 v58
          pBuf2[1] = 24;  // 输出槽 1 类型字 = 24
          Blockbn = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 110;  // 异常展开状态号 → 110
          if ( Blockbn == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=2)
        case 1071:
          pMem26 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 113;  // 异常展开状态号 → 113
          if ( pMem26 != nullptr )  // 非空（new 成功）才继续构造
            v60 = sub_4B3DF0(pMem26, 1, 0, 1101004800, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=1, 标志=0, 数值=20.0f, 时长=60000ms, 1)
          else
            v60 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v60;  // 输出槽 0 存效果对象 v60
          pBuf2[0] = 28;  // 输出槽 0 类型字 = 28
          pMem27 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 114;  // 异常展开状态号 → 114
          if ( pMem27 != nullptr )  // 非空（new 成功）才继续构造
            v62 = sub_4B3DF0(pMem27, 21, 0, 1112014848, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=21, 标志=0, 数值=50.0f, 时长=60000ms, 1)
          else
            v62 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v62;  // 输出槽 1 存效果对象 v62
          pBuf2[1] = 25;  // 输出槽 1 类型字 = 25
          Blockbo = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 115;  // 异常展开状态号 → 115
          if ( Blockbo == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=2)
        //   1071 双 CNChangeStatus(1,0,20.0f)/(21,0,50.0f) 60s；1072 五枚与 6513 完全同构（0/1/3/5/20 号） ──
        case 1072:
          pMem28 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 116;  // 异常展开状态号 → 116
          if ( pMem28 != nullptr )  // 非空（new 成功）才继续构造
            v64 = sub_4B3DF0(pMem28, 0, 0, 1106247680, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=0, 标志=0, 数值=30.0f, 时长=60000ms, 1)
          else
            v64 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v64;  // 输出槽 0 存效果对象 v64
          pBuf2[0] = 26;  // 输出槽 0 类型字 = 26
          pMem29 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 117;  // 异常展开状态号 → 117
          if ( pMem29 != nullptr )  // 非空（new 成功）才继续构造
            v66 = sub_4B3DF0(pMem29, 1, 0, 1106247680, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=1, 标志=0, 数值=30.0f, 时长=60000ms, 1)
          else
            v66 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v66;  // 输出槽 1 存效果对象 v66
          pBuf2[1] = 28;  // 输出槽 1 类型字 = 28
          pMem30 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 118;  // 异常展开状态号 → 118
          if ( pMem30 != nullptr )  // 非空（new 成功）才继续构造
            v68 = sub_4B3DF0(pMem30, 3, 1, -1027080192, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=3, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
          else
            v68 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[2] = v68;  // 输出槽 2 存效果对象 v68
          pBuf2[2] = 27;  // 输出槽 2 类型字 = 27
          pMem31 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 119;  // 异常展开状态号 → 119
          if ( pMem31 != nullptr )  // 非空（new 成功）才继续构造
            v70 = sub_4B3DF0(pMem31, 5, 1, -1027080192, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=5, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
          else
            v70 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[3] = v70;  // 输出槽 3 存效果对象 v70
          pBuf2[3] = 30;  // 输出槽 3 类型字 = 30
          pMem32 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
          v125 = 120;  // 异常展开状态号 → 120
          if ( pMem32 != nullptr )  // 非空（new 成功）才继续构造
            v72 = sub_4B3DF0(pMem32, 20, 1, -1027080192, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=20, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
          else
            v72 = nullptr;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[4] = v72;  // 输出槽 4 存效果对象 v72
          pBuf2[4] = 23;  // 输出槽 4 类型字 = 23
          Blockbp = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 121;  // 异常展开状态号 → 121
          if ( Blockbp == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 5);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=5)
        // ── [段 23] case 1074：sub_50FF30(1074, 0, 300, 0) = CNOmozzaOfWorld 三参版 ──
        case 1074:  // case 1074 → 返回 CNOmozzaOfWorld 构造
          Blockbe = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
          v125 = 7;  // 异常展开状态号 → 7
          if ( Blockbe == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50FF30(Block, 0, 300, 0);  // 返回 CNOmozzaOfWorld 构造(Block, 0, 300, 0)
        // ── [段 24] case 1075-1078：四型「单效果 + 时长」护符（280/100/280/380 系） ──
        //   1075 CNChangeHp(280.0f,2000ms) / 1076 CNChangeMp(150,700) / 1077 CNChangeHp(280.0f,100ms) / 1078 CNChangeHp(380.0f,100ms)
        case 1075:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 12;
          v125 = 12;  // 异常展开状态号 → 12
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = 13;  // 低字节写异常展开状态号 → 13
          if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
            v7 = sub_4D6810(1133248512, 2000, 1, 1);  // 存 CNChangeHp 回血(伤害值=280.0f, 时长=2000ms)
          else
LABEL_233:
            v7 = 0;
          goto LABEL_326;  // 跳 LABEL_326
        case 1076:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 14;
          v125 = 14;  // 异常展开状态号 → 14
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          LOBYTE(v125) = 15;  // 低字节写异常展开状态号 → 15
          if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
            goto LABEL_321;  // 跳 LABEL_321
          v7 = sub_50F270(150, 700);  // 存 CNChangeMp 回蓝(MP=150, 时长=700ms)
          goto LABEL_326;  // 跳 LABEL_326
        case 1077:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 8;
          v125 = 8;  // 异常展开状态号 → 8
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = 9;  // 低字节写异常展开状态号 → 9
          if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
            v7 = sub_4D6810(1133248512, 100, 1, 1);  // 存 CNChangeHp 回血(伤害值=280.0f, 时长=100ms)
          else
LABEL_321:
            v7 = 0;
          goto LABEL_326;  // 跳 LABEL_326
        case 1078:
          pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v6 = 10;
          v125 = 10;  // 异常展开状态号 → 10
          if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = 11;  // 低字节写异常展开状态号 → 11
          if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
            v7 = sub_4D6810(1136525312, 100, 1, 1);  // 存 CNChangeHp 回血(伤害值=380.0f, 时长=100ms)
          else
LABEL_325:
            v7 = 0;
          goto LABEL_326;  // 跳 LABEL_326
        // ── [段 25] case 1079 直接 goto LABEL_433（与 6514 共用 CNChangeHp 550.0f 尾） ──
        case 1079:
          goto LABEL_433;  // 跳 LABEL_433
        // ── [段 26] case 1080 / 1081：CNChangeHp(550.0f,1000ms)+sub_602DA0(15,10.0,8) / CNChangeMp(250,1000)+sub_602DA0(8,10.0,5) ──
        case 1080:
          Blockbq = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          v125 = 133;  // 异常展开状态号 → 133
          if ( Blockbq != nullptr )  // 非空（new 成功）才继续构造
            v73 = sub_4D6810(1141473280, 1000, 1, 1);  // 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
          else
            v73 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v73;  // 输出槽 0 存效果对象 v73
          pBuf2[0] = 0;  // 输出槽 0 类型字 = 0
          Blockbr = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 134;  // 异常展开状态号 → 134
          if ( Blockbr != nullptr )  // 非空（new 成功）才继续构造
          {
            v18 = sub_50F990(Block, pBuf, pBuf2, 1);  // 存 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=1)
            v125 = -1;  // 异常展开状态号 → -1
            sub_602DA0(15, 10.0, 8);  // 参量三元写入 +180/+184/+188(槽=15, 值=10.0, 档=8)
          }
          else
          {
            v18 = 0;
            v125 = -1;  // 异常展开状态号 → -1
            sub_602DA0(15, 10.0, 8);  // 参量三元写入 +180/+184/+188(槽=15, 值=10.0, 档=8)
          }
          return (uint32_t *)v18;
        case 1081:  // case 1081 → CNChangeMp 构造
          Blockbs = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
          v125 = 135;  // 异常展开状态号 → 135
          if ( Blockbs != nullptr )  // 非空（new 成功）才继续构造
            v74 = sub_50F270(250, 1000);  // 存 CNChangeMp 回蓝(MP=250, 时长=1000ms)
          else
            v74 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[0] = v74;  // 输出槽 0 存效果对象 v74
          pBuf2[0] = 0;  // 输出槽 0 类型字 = 0
          Blockbt = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 136;  // 异常展开状态号 → 136
          if ( Blockbt != nullptr )  // 非空（new 成功）才继续构造
          {
            v18 = sub_50F990(Block, pBuf, pBuf2, 1);  // 存 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=1)
            v125 = -1;  // 异常展开状态号 → -1
            sub_602DA0(8, 10.0, 5);  // 参量三元写入 +180/+184/+188(槽=8, 值=10.0, 档=5)
          }
          else
          {
            v18 = 0;
            v125 = -1;  // 异常展开状态号 → -1
            sub_602DA0(8, 10.0, 5);  // 参量三元写入 +180/+184/+188(槽=8, 值=10.0, 档=5)
          }
          return (uint32_t *)v18;
        // ── [段 27] case 1082：武器属性变更 + 火焰护符 —— sub_510140(1,2,3)=CNChangeWeaponElement 属性参数包 ──
        //   对象 +40 写 60000（时长），随后 sub_510350(2,0,10,60000,1,CHARM_FIRE_USE) 注册火系属性珠，类型字 37/23
        case 1082:
          Blockbu = operator new(0x84u);  // 分配 0x84 字节对象壳（132 字节）
          v125 = 137;  // 异常展开状态号 → 137
          if ( Blockbu != nullptr )  // 非空（new 成功）才继续构造
            v75 = (int *)sub_510140(1, 2, 3);
          else
            v75 = nullptr;
          pBuf[0] = v75;  // 输出槽 0 存效果对象 v75
          v76 = *v75;
          v125 = -1;  // 异常展开状态号 → -1
          *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v76 + 64))(v75) + 40) = 60000;
          pBuf2[0] = 37;  // 输出槽 0 类型字 = 37
          Blockbv = operator new(0x84u);  // 分配 0x84 字节对象壳（132 字节）
          v125 = 138;  // 异常展开状态号 → 138
          if ( Blockbv != nullptr )  // 非空（new 成功）才继续构造
            v77 = sub_510350(2, 0, 10, 60000, 1, "CHARM_FIRE_USE");  // 存 CNChangeElementTolerance 元素抗性变更(系别=2, 时长=60000ms, 标签=「CHARM_FIRE_USE「)
          else
            v77 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          pBuf[1] = v77;  // 输出槽 1 存效果对象 v77
          pBuf2[1] = 23;  // 输出槽 1 类型字 = 23
          pMem33 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
          v125 = 139;  // 异常展开状态号 → 139
LABEL_312:
          if ( pMem33 == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 2);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=2)
        // ── [段 28] case 1083-1088：CNRateHpMp 族（模式, 回复率, 时长） ──
        //   1083(0,15,1000) / 1084(1,15,1000) / 1085(1,30,100) / 1087(0,30,1000) / 1088(2,50,1000)
        case 1083:  // case 1083 → 返回 CNRateHpMp 回复率构造
          Blockbb = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
          v125 = 4;  // 异常展开状态号 → 4
          if ( Blockbb == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50FC00(Block, 0, 15, 1000);  // 返回 CNRateHpMp 回复率构造(模式=HP, 回复率=15, 时长=1000)
        case 1084:  // case 1084 → 返回 CNRateHpMp 回复率构造
          Blockbc = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
          v125 = 5;  // 异常展开状态号 → 5
          if ( Blockbc == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50FC00(Block, 1, 15, 1000);  // 返回 CNRateHpMp 回复率构造(模式=MP, 回复率=15, 时长=1000)
        case 1085:  // case 1085 → 返回 CNRateHpMp 回复率构造
          Blockbd = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
          v125 = 6;  // 异常展开状态号 → 6
          if ( Blockbd == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50FC00(Block, 1, 30, 100);  // 返回 CNRateHpMp 回复率构造(模式=MP, 回复率=30, 时长=100)
        case 1087:  // case 1087 → 返回 CNRateHpMp 回复率构造
          Blockbw = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
          v125 = 148;  // 异常展开状态号 → 148
          if ( Blockbw == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50FC00(Block, 0, 30, 1000);  // 返回 CNRateHpMp 回复率构造(模式=HP, 回复率=30, 时长=1000)
        case 1088:  // case 1088 → 返回 CNRateHpMp 回复率构造
          Blockbx = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
          v125 = 149;  // 异常展开状态号 → 149
          if ( Blockbx == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          return (uint32_t *)sub_50FC00(Block, 2, 50, 1000);  // 返回 CNRateHpMp 回复率构造(模式=HP+MP, 回复率=50, 时长=1000)
        default:
          return nullptr;  // 返回空（未识别 ID）
      }
    }
    // ── [段 29] Block 落在 [4041..4052]/[4079..4082]/[4087..4102] 三穿透区：裸构造兜底路径 ──
    //   new(0xB0) + sub_50F740=CNRDStackable 基类构造 + 挂 CNIncreaseStatusStackable::vftable（无效果参数）
    pMem34 = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
    v125 = 3;  // 异常展开状态号 → 3
    if ( pMem34 != nullptr )  // 非空（new 成功）才继续构造
    {
      sub_50F740(Block);  // CNRDStackable 基类构造
      *pMem34 = &CNIncreaseStatusStackable::`vftable';  // 挂 CNIncreaseStatusStackable 虚表
      return pMem34;
    }
    return nullptr;  // 返回空（未识别 ID）
  }
  // ── [段 30] case 1055：单枚 CNChangeHp(100.0f,1000ms) 走 sub_50F850(1055, obj, 0) 提交 ──
  if ( Block == 1055 )  // Block == 1055：大区入口（本函数物品 ID 全在此链）
  {
    Blockba = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
    v125 = 75;  // 异常展开状态号 → 75
    if ( Blockba != nullptr )  // 非空（new 成功）才继续构造
    {
      pMem20 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
      LOBYTE(v125) = 76;  // 低字节写异常展开状态号 → 76
      if ( pMem20 != nullptr )  // 非空（new 成功）才继续构造
        v45 = sub_4D6810(1120403456, 1000, 1, 1);  // 存 CNChangeHp 回血(伤害值=100.0f, 时长=1000ms)
      else
        v45 = 0;
      LOBYTE(v125) = 75;  // 低字节写异常展开状态号 → 75
      return (uint32_t *)sub_50F850(1055, v45, 0);  // 返回 CNAppendageStackable 记录追加构造(Block=1055, 效果对象=v45, 类型字=0)
    }
    return nullptr;  // 返回空（未识别 ID）
  }
  // ── [段 31] Block 处于 (1019, 1055) 区：1020..1054 段（属性护符 / 区域消耗品 / 主动状态三族） ──
  if ( Block > 1019 )  // Block > 1019：1020-1054 段
  {
    switch ( Block )
    {
      // ── [段 32] case 1020-1023：★ 四系属性护符本体 —— sub_510350(系别,0,30,60000,1,标签串) ──
      //   1020 CHARM_FIRE_USE / 1021 CHARM_ICE_USE / 1022 CHARM_MOON_USE / 1023 CHARM_SUN_USE
      //   sub_510350 = CNChangeElementTolerance 构造：标签串存 +27（+32=容量 15），即元素抗性变更 PO；均走 sub_50F850(type 23)
      case 1020:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v33 = 45;
        v125 = 45;  // 异常展开状态号 → 45
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem21 = operator new(0x84u);  // 分配 0x84 字节对象壳（132 字节）
        LOBYTE(v125) = 46;  // 低字节写异常展开状态号 → 46
        if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
          goto LABEL_162;  // 跳 LABEL_162
        v34 = sub_510350(0, 0, 30, 60000, 1, "CHARM_FIRE_USE");  // 存 CNChangeElementTolerance 元素抗性变更(系别=0, 时长=60000ms, 标签=「CHARM_FIRE_USE「)
        goto LABEL_163;  // 跳 LABEL_163
      case 1021:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 47;  // 异常展开状态号 → 47
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem21 = operator new(0x84u);  // 分配 0x84 字节对象壳（132 字节）
        LOBYTE(v125) = 48;  // 低字节写异常展开状态号 → 48
        if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
          v35 = sub_510350(1, 0, 30, 60000, 1, "CHARM_ICE_USE");  // 存 CNChangeElementTolerance 元素抗性变更(系别=1, 时长=60000ms, 标签=「CHARM_ICE_USE「)
        else
          v35 = 0;
        LOBYTE(v125) = 47;  // 低字节写异常展开状态号 → 47
        return (uint32_t *)sub_50F850(Block, v35, 23);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v35, 类型字=23)
      case 1022:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 49;  // 异常展开状态号 → 49
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem21 = operator new(0x84u);  // 分配 0x84 字节对象壳（132 字节）
        LOBYTE(v125) = 50;  // 低字节写异常展开状态号 → 50
        if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
          v36 = sub_510350(2, 0, 30, 60000, 1, "CHARM_MOON_USE");  // 存 CNChangeElementTolerance 元素抗性变更(系别=2, 时长=60000ms, 标签=「CHARM_MOON_USE「)
        else
          v36 = 0;
        LOBYTE(v125) = 49;  // 低字节写异常展开状态号 → 49
        return (uint32_t *)sub_50F850(Block, v36, 23);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v36, 类型字=23)
      case 1023:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v33 = 51;
        v125 = 51;  // 异常展开状态号 → 51
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem21 = operator new(0x84u);  // 分配 0x84 字节对象壳（132 字节）
        LOBYTE(v125) = 52;  // 低字节写异常展开状态号 → 52
        if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
          v34 = sub_510350(3, 0, 30, 60000, 1, "CHARM_SUN_USE");  // 存 CNChangeElementTolerance 元素抗性变更(系别=3, 时长=60000ms, 标签=「CHARM_SUN_USE「)
        else
LABEL_162:
          v34 = 0;
LABEL_163:
        LOBYTE(v125) = v33;
        return (uint32_t *)sub_50F850(Block, v34, 23);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v34, 类型字=23)
      // ── [段 33] case 1024：四枚 CNChangeStatus(16/17/18/19, 0, 15.0f, 60000ms)（与 6505 同组，时长缩为 1 分钟） ──
      case 1024:
        pMem35 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        pMem20 = pMem35;
        v125 = 53;  // 异常展开状态号 → 53
        if ( pMem35 != nullptr )  // 非空（new 成功）才继续构造
          v38 = sub_4B3DF0(pMem35, 16, 0, 1097859072, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=16, 标志=0, 数值=15.0f, 时长=60000ms, 1)
        else
          v38 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[0] = v38;  // 输出槽 0 存效果对象 v38
        pBuf2[0] = 51;  // 输出槽 0 类型字 = 51
        pMem36 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        pMem20 = pMem36;
        v125 = 54;  // 异常展开状态号 → 54
        if ( pMem36 != nullptr )  // 非空（new 成功）才继续构造
          v40 = sub_4B3DF0(pMem36, 17, 0, 1097859072, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=17, 标志=0, 数值=15.0f, 时长=60000ms, 1)
        else
          v40 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[1] = v40;  // 输出槽 1 存效果对象 v40
        pBuf2[1] = 52;  // 输出槽 1 类型字 = 52
        pMem37 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        pMem20 = pMem37;
        v125 = 55;  // 异常展开状态号 → 55
        if ( pMem37 != nullptr )  // 非空（new 成功）才继续构造
          v42 = sub_4B3DF0(pMem37, 18, 0, 1097859072, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=18, 标志=0, 数值=15.0f, 时长=60000ms, 1)
        else
          v42 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[2] = v42;  // 输出槽 2 存效果对象 v42
        pBuf2[2] = 53;  // 输出槽 2 类型字 = 53
        pMem38 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        pMem20 = pMem38;
        v125 = 56;  // 异常展开状态号 → 56
        if ( pMem38 != nullptr )  // 非空（new 成功）才继续构造
          v44 = sub_4B3DF0(pMem38, 19, 0, 1097859072, 60000, 1);  // 存 CNChangeStatus 状态附加(状态=19, 标志=0, 数值=15.0f, 时长=60000ms, 1)
        else
          v44 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[3] = v44;  // 输出槽 3 存效果对象 v44
        pBuf2[3] = 54;  // 输出槽 3 类型字 = 54
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 57;  // 异常展开状态号 → 57
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        return (uint32_t *)sub_50F990(Block, pBuf, pBuf2, 4);  // 返回 CNAppendageStackable 记录追加构造（三参版）(Block=Block, 输出槽, 类型槽, 记录数=4)
      // ── [段 34] case 1025 / 1026 ──
      //   1025 → sub_50F7F0=CNItemScreamOfHysma；1026 → CNChangeStatus(0,0,15.0f,600000ms) 单枚
      case 1025:
        goto LABEL_391;  // 跳 LABEL_391
      case 1026:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 39;  // 异常展开状态号 → 39
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem39 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        pMem21 = pMem39;
        LOBYTE(v125) = 40;  // 低字节写异常展开状态号 → 40
        if ( pMem39 != nullptr )  // 非空（new 成功）才继续构造
          v32 = sub_4B3DF0(pMem39, 0, 0, 1097859072, 600000, 1);  // 存 CNChangeStatus 状态附加(状态=0, 标志=0, 数值=15.0f, 时长=600000ms, 1)
        else
          v32 = nullptr;
        LOBYTE(v125) = 39;  // 低字节写异常展开状态号 → 39
        return (uint32_t *)sub_50F850(Block, v32, 26);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v32, 类型字=26)
      // ── [段 35] case 1027 / 1028 / 1030：★ CNItemAreaStackable 区域放置型消耗品（sub_510000） ──
      //   参数块 v120/v121/v122：状态字 12/0/1 + 数据 0x4E2042480000 与 0xEA6041700000 + 数据长 21/12
      case 1027:
        v120 = 12;
        v121 = 0;
        v122[0] = 0x4E2042480000LL;  // 数据块写入
        v122[1] = 0x2400000001LL;  // 数据块写入
        Blockz = operator new(0x4ACu);  // 分配 0x4AC 字节对象壳（1196 字节）
        v125 = 38;  // 异常展开状态号 → 38
        if ( Blockz == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        return (uint32_t *)sub_510000(Block, 48017, &v120, 21);  // 返回 CNItemAreaStackable 区域放置型消耗品(物品ID=48017, 数据长=21)
      case 1028:
        v120 = 0;
        v121 = 0;
        v122[0] = 0xEA6041700000LL;  // 数据块写入
        v122[1] = 0x1A00000001LL;  // 数据块写入
        pMem40 = operator new(0x4ACu);  // 分配 0x4AC 字节对象壳（1196 字节）
        v125 = 37;  // 异常展开状态号 → 37
        goto LABEL_137;  // 跳 LABEL_137
      case 1029:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 35;  // 异常展开状态号 → 35
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem41 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        pMem21 = pMem41;
        LOBYTE(v125) = 36;  // 低字节写异常展开状态号 → 36
        if ( pMem41 != nullptr )  // 非空（new 成功）才继续构造
          v30 = sub_4B3DF0(pMem41, 1, 0, 1097859072, 600000, 1);  // 存 CNChangeStatus 状态附加(状态=1, 标志=0, 数值=15.0f, 时长=600000ms, 1)
        else
          v30 = nullptr;
        LOBYTE(v125) = 35;  // 低字节写异常展开状态号 → 35
        return (uint32_t *)sub_50F850(Block, v30, 28);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v30, 类型字=28)
      case 1030:
        v120 = 1;
        v121 = 0;
        v122[0] = 0xEA6041700000LL;  // 数据块写入
        v122[1] = 0x1C00000001LL;  // 数据块写入
        pMem40 = operator new(0x4ACu);  // 分配 0x4AC 字节对象壳（1196 字节）
        v125 = 34;  // 异常展开状态号 → 34
LABEL_137:
        if ( pMem40 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        return (uint32_t *)sub_510000(Block, 48017, &v120, 21);  // 返回 CNItemAreaStackable 区域放置型消耗品(物品ID=48017, 数据长=21)
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
      case 1043:  // case 1043 → 返回 CNIncreaseStatusStackable 构造
      case 1044:  // case 1044 → 返回 CNIncreaseStatusStackable 构造
      case 1045:  // case 1045 → 返回 CNIncreaseStatusStackable 构造
      case 1046:  // case 1046 → 返回 CNIncreaseStatusStackable 构造
        Blocky = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
        v125 = 33;  // 异常展开状态号 → 33
        if ( Blocky == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        return (uint32_t *)sub_50F7C0(Block);  // 返回 CNIncreaseStatusStackable 构造(Block)
      // ── [段 37] case 1032 / 1033：CNChangeHp(80.0f,100ms)/(120.0f,100ms) 配 CNChangeMp(80,100)/(120,100) ──
      case 1032:
        Blocku = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
        v125 = 27;  // 异常展开状态号 → 27
        if ( Blocku != nullptr )  // 非空（new 成功）才继续构造
          v24 = sub_4D6810(1117782016, 100, 1, 1);  // 存 CNChangeHp 回血(伤害值=80.0f, 时长=100ms)
        else
          v24 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[0] = v24;  // 输出槽 0 存效果对象 v24
        pBuf2[0] = 0;  // 输出槽 0 类型字 = 0
        Blockv = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
        v125 = 28;  // 异常展开状态号 → 28
        if ( Blockv != nullptr )  // 非空（new 成功）才继续构造
          v25 = sub_50F270(80, 100);  // 存 CNChangeMp 回蓝(MP=80, 时长=100ms)
        else
          v25 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[1] = v25;  // 输出槽 1 存效果对象 v25
        pBuf2[1] = 0;  // 输出槽 1 类型字 = 0
        pMem33 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 29;  // 异常展开状态号 → 29
        goto LABEL_312;  // 跳 LABEL_312
      case 1033:
        Blockw = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
        v125 = 30;  // 异常展开状态号 → 30
        if ( Blockw != nullptr )  // 非空（new 成功）才继续构造
          v26 = sub_4D6810(1123024896, 100, 1, 1);  // 存 CNChangeHp 回血(伤害值=120.0f, 时长=100ms)
        else
          v26 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[0] = v26;  // 输出槽 0 存效果对象 v26
        pBuf2[0] = 0;  // 输出槽 0 类型字 = 0
        Blockx = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
        v125 = 31;  // 异常展开状态号 → 31
        if ( Blockx != nullptr )  // 非空（new 成功）才继续构造
          v27 = sub_50F270(120, 100);  // 存 CNChangeMp 回蓝(MP=120, 时长=100ms)
        else
          v27 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[1] = v27;  // 输出槽 1 存效果对象 v27
        pBuf2[1] = 0;  // 输出槽 1 类型字 = 0
        pMem33 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 32;  // 异常展开状态号 → 32
        goto LABEL_312;  // 跳 LABEL_312
      // ── [段 38] case 1047：sub_50FA30 = CNCoinOfFortune 构造（幸运硬币，单对象无参） ──
      case 1047:
        Blockt = operator new(0xA8u);  // 分配 0xA8 字节对象壳（168 字节）
        v125 = 25;  // 异常展开状态号 → 25
        if ( Blockt == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        return (uint32_t *)sub_50FA30(Block);  // 返回 CNCoinOfFortune 幸运硬币(Block)
      // ── [段 39] case 1048 / 1049：CNChangeHp(260.0f,700ms) / CNChangeMp(130,700) 单效果两型 ──
      case 1048:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v6 = 23;
        v125 = 23;  // 异常展开状态号 → 23
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
        LOBYTE(v125) = 24;  // 低字节写异常展开状态号 → 24
        if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
          goto LABEL_233;  // 跳 LABEL_233
        v7 = sub_4D6810(1132593152, 700, 1, 1);  // 存 CNChangeHp 回血(伤害值=260.0f, 时长=700ms)
        goto LABEL_326;  // 跳 LABEL_326
      case 1049:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v6 = 21;
        v125 = 21;  // 异常展开状态号 → 21
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
        LOBYTE(v125) = 22;  // 低字节写异常展开状态号 → 22
        if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
          goto LABEL_325;  // 跳 LABEL_325
        v7 = sub_50F270(130, 700);  // 存 CNChangeMp 回蓝(MP=130, 时长=700ms)
        goto LABEL_326;  // 跳 LABEL_326
      // ── [段 40] case 1050-1054：★ CNActiveStatusStackable 主动状态消耗品（sub_510640 + sub_602BC0 记录追加） ──
      //   状态索引依次 3 / 7 / 5 / 15 / 11；sub_602BC0(索引, 0, -1, 1) 是 16 字节栈记录尾插的薄封装
      case 1050:
        Blocks = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
        v125 = 20;  // 异常展开状态号 → 20
        if ( Blocks != nullptr )  // 非空（new 成功）才继续构造
          v23 = sub_510640(Block, 0, 0);  // 存 CNActiveStatusStackable 主动状态(Block=Block, 0, 0)
        else
          v23 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        sub_602BC0(3, 0, -1, 1);  // 记录追加薄封装（16 字节栈记录尾插）(状态索引=3, 0, -1, 1)
        return (uint32_t *)v23;
      case 1051:
        Blockr = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
        v125 = 19;  // 异常展开状态号 → 19
        if ( Blockr != nullptr )  // 非空（new 成功）才继续构造
          v22 = sub_510640(Block, 0, 0);  // 存 CNActiveStatusStackable 主动状态(Block=Block, 0, 0)
        else
          v22 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        sub_602BC0(7, 0, -1, 1);  // 记录追加薄封装（16 字节栈记录尾插）(状态索引=7, 0, -1, 1)
        return (uint32_t *)v22;
      case 1052:
        Blockq = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
        v125 = 18;  // 异常展开状态号 → 18
        if ( Blockq != nullptr )  // 非空（new 成功）才继续构造
          v21 = sub_510640(Block, 0, 0);  // 存 CNActiveStatusStackable 主动状态(Block=Block, 0, 0)
        else
          v21 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        sub_602BC0(5, 0, -1, 1);  // 记录追加薄封装（16 字节栈记录尾插）(状态索引=5, 0, -1, 1)
        return (uint32_t *)v21;
      case 1053:
        Blockp = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
        v125 = 17;  // 异常展开状态号 → 17
        if ( Blockp != nullptr )  // 非空（new 成功）才继续构造
          v20 = sub_510640(Block, 0, 0);  // 存 CNActiveStatusStackable 主动状态(Block=Block, 0, 0)
        else
          v20 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        sub_602BC0(15, 0, -1, 1);  // 记录追加薄封装（16 字节栈记录尾插）(状态索引=15, 0, -1, 1)
        return (uint32_t *)v20;
      case 1054:
        Blocko = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
        v125 = 16;  // 异常展开状态号 → 16
        if ( Blocko != nullptr )  // 非空（new 成功）才继续构造
          v19 = sub_510640(Block, 0, 0);  // 存 CNActiveStatusStackable 主动状态(Block=Block, 0, 0)
        else
          v19 = 0;
        v125 = -1;  // 异常展开状态号 → -1
        sub_602BC0(11, 0, -1, 1);  // 记录追加薄封装（16 字节栈记录尾插）(状态索引=11, 0, -1, 1)
        return (uint32_t *)v19;
      default:
        return nullptr;  // 返回空（未识别 ID）
    }
  }
  // ── [段 41] case 1019：goto LABEL_384（与 6512 共用 CNOmozzaOfWorld 构造） ──
  if ( Block == 1019 )  // Block == 1019：1020-1054 段
    goto LABEL_384;  // 跳 LABEL_384
  if ( Block > 1006 )  // Block > 1006：1007-1018 段
  {
    // ── [段 42] Block 处于 (1006, 1019) 区：1007..1018 段 ──
    switch ( Block )
    {
      // ── [段 43] case 1007：两枚 CNChangeStatus(0,0,10.0f)/(3,0,10.0f)，600000ms ──
      case 1007:
        pMem42 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        v125 = 70;  // 异常展开状态号 → 70
        if ( pMem42 != nullptr )  // 非空（new 成功）才继续构造
          v13 = sub_4B3DF0(pMem42, 0, 0, 1092616192, 600000, 1);  // 存 CNChangeStatus 状态附加(状态=0, 标志=0, 数值=10.0f, 时长=600000ms, 1)
        else
          v13 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[0] = v13;  // 输出槽 0 存效果对象 v13
        pBuf2[0] = 26;  // 输出槽 0 类型字 = 26
        pMem43 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        v125 = 71;  // 异常展开状态号 → 71
        if ( pMem43 != nullptr )  // 非空（new 成功）才继续构造
          v15 = sub_4B3DF0(pMem43, 3, 0, 1092616192, 600000, 1);  // 存 CNChangeStatus 状态附加(状态=3, 标志=0, 数值=10.0f, 时长=600000ms, 1)
        else
          v15 = nullptr;
        v125 = -1;  // 异常展开状态号 → -1
        pBuf[1] = v15;  // 输出槽 1 存效果对象 v15
        pBuf2[1] = 27;  // 输出槽 1 类型字 = 27
        pMem33 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 72;  // 异常展开状态号 → 72
        goto LABEL_312;  // 跳 LABEL_312
      // ── [段 44] case 1008 / 1010：CNActiveStatusStackable（sub_510640）—— 1008 参数 (0,0)、1010 参数 (200,0) ──
      //   两者收尾 sub_602BC0(2, 0, -1, 1) 状态索引 2
      case 1008:
        Blockl = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
        v125 = 68;  // 异常展开状态号 → 68
        if ( Blockl == nullptr )  // 为空（new 失败）则走异常路径
          goto LABEL_67;  // 跳 LABEL_67
        v11 = sub_510640(Block, 0, 0);  // 存 CNActiveStatusStackable 主动状态(Block=Block, 0, 0)
        goto LABEL_68;  // 跳 LABEL_68
      // ── [段 45] case 1009：CNAntiFreezePotion 防冻药水（sub_510E40(200,0)）+ sub_602BC0(1,…) ──
      case 1009:
        Blockn = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
        v125 = 74;  // 异常展开状态号 → 74
        if ( Blockn != nullptr )  // 非空（new 成功）才继续构造
          v5 = sub_510E40(Block, 200, 0);  // 存 CNAntiFreezePotion 防冻药水(Block=Block, 200, 0)
        else
LABEL_71:
          v5 = 0;
LABEL_72:
        v125 = -1;  // 异常展开状态号 → -1
        sub_602BC0(1, 0, -1, 1);  // 记录追加薄封装（16 字节栈记录尾插）(状态索引=1, 0, -1, 1)
        return (uint32_t *)v5;
      case 1010:
        Blockm = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
        v125 = 73;  // 异常展开状态号 → 73
        if ( Blockm != nullptr )  // 非空（new 成功）才继续构造
          v11 = sub_510640(Block, 200, 0);  // 存 CNActiveStatusStackable 主动状态(Block=Block, 200, 0)
        else
LABEL_67:
          v11 = 0;
LABEL_68:
        v125 = -1;  // 异常展开状态号 → -1
        sub_602BC0(2, 0, -1, 1);  // 记录追加薄封装（16 字节栈记录尾插）(状态索引=2, 0, -1, 1)
        return (uint32_t *)v11;
      // ── [段 46] case 1011 / 1014：CNChangeActiveProperty（sub_510230(4,1000,60000)）属性激活 PO ──
      case 1011:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v6 = -96;
        v125 = 160;  // 异常展开状态号 → 160
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem21 = operator new(0x60u);  // 分配 0x60 字节对象壳（96 字节）
        LOBYTE(v125) = -95;  // 低字节写异常展开状态号 → -95
        if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
          goto LABEL_78;  // 跳 LABEL_78
        goto LABEL_321;  // 跳 LABEL_321
      // ── [段 47] case 1013：CNChangeHp(180.0f,2000ms) + sub_50F850 提交 + 尾部 sub_602DA0(2,30.0,2) ──
      case 1013:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 164;  // 异常展开状态号 → 164
        if ( pMem20 != nullptr )  // 非空（new 成功）才继续构造
        {
          pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
          LOBYTE(v125) = -91;  // 低字节写异常展开状态号 → -91
          if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
            v17 = sub_4D6810(1127481344, 2000, 1, 1);  // 存 CNChangeHp 回血(伤害值=180.0f, 时长=2000ms)
          else
            v17 = 0;
          LOBYTE(v125) = -92;  // 低字节写异常展开状态号 → -92
          v18 = sub_50F850(Block, v17, 0);  // 存 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v17, 类型字=0)
          v125 = -1;  // 异常展开状态号 → -1
          sub_602DA0(2, 30.0, 2);  // 参量三元写入 +180/+184/+188(槽=2, 值=30.0, 档=2)
        }
        else
        {
          v18 = 0;
          v125 = -1;  // 异常展开状态号 → -1
          sub_602DA0(2, 30.0, 2);  // 参量三元写入 +180/+184/+188(槽=2, 值=30.0, 档=2)
        }
        return (uint32_t *)v18;
      case 1014:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v6 = -94;
        v125 = 162;  // 异常展开状态号 → 162
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem21 = operator new(0x60u);  // 分配 0x60 字节对象壳（96 字节）
        LOBYTE(v125) = -93;  // 低字节写异常展开状态号 → -93
        if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
          goto LABEL_325;  // 跳 LABEL_325
LABEL_78:
        v7 = sub_510230(4, 1000, 60000);  // sub_510230：存 CNChangeActiveProperty
        goto LABEL_326;  // 跳 LABEL_326
      // ── [段 48] case 1015：CNSummonMonsterStackable 召唤怪物消耗品（sub_5104B0(1,5,14) 怪物 ID+数量区间） ──
      case 1015:
        Blocki = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
        v125 = 64;  // 异常展开状态号 → 64
        if ( Blocki == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        return (uint32_t *)sub_5104B0(Block, 1, 5, 14);  // 返回 CNSummonMonsterStackable 召唤怪物(Block=Block, 1, 5, 14)
      // ── [段 49] case 1016：CNChangeStatus(12, 0, 50.0f, 20000ms)（case 6511 的短时版），类型字 36 ──
      case 1016:
        pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
        v125 = 41;  // 异常展开状态号 → 41
        if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        pMem44 = operator new(0x7Cu);  // 分配 0x7C 字节对象壳（124 字节）
        pMem21 = pMem44;
        LOBYTE(v125) = 42;  // 低字节写异常展开状态号 → 42
        if ( pMem44 != nullptr )  // 非空（new 成功）才继续构造
          v10 = sub_4B3DF0(pMem44, 12, 0, 1112014848, 20000, 1);  // 存 CNChangeStatus 状态附加(状态=12, 标志=0, 数值=50.0f, 时长=20000ms, 1)
        else
          v10 = nullptr;
        LOBYTE(v125) = 41;  // 低字节写异常展开状态号 → 41
        return (uint32_t *)sub_50F850(Block, v10, 36);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v10, 类型字=36)
      // ── [段 50] case 1017 / 1018：CNItemAreaStackable 包 48018（数据长 12）—— 段 35 两型的低配版 ──
      //   前 4 字节 60000 时长 + 1 字节状态 0/1 + 类型字 37
      case 1017:
        *(uint32_t *)((char *)v122 + 3) = 60000;  // 区域参数块 +3 写 60000
        *(uint32_t *)((char *)v122 + 7) = 0;  // 区域参数块 +7 写 0
        *(uint32_t *)((char *)&v122[1] + 3) = 37;  // 区域参数块尾写类型字 37
        Blockj = operator new(0x4ACu);  // 分配 0x4AC 字节对象壳（1196 字节）
        v125 = 65;  // 异常展开状态号 → 65
        if ( Blockj == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        return (uint32_t *)sub_510000(Block, 48018, (char *)v122 + 3, 12);  // 返回 CNItemAreaStackable 区域放置型消耗品(物品ID=48018, 数据长=12)
      case 1018:
        *(uint32_t *)((char *)v122 + 3) = 60000;  // 区域参数块 +3 写 60000
        *(uint32_t *)((char *)v122 + 7) = 1;  // 区域参数块 +7 写 1
        *(uint32_t *)((char *)&v122[1] + 3) = 37;  // 区域参数块尾写类型字 37
        Blockk = operator new(0x4ACu);  // 分配 0x4AC 字节对象壳（1196 字节）
        v125 = 66;  // 异常展开状态号 → 66
        if ( Blockk == nullptr )  // 为空（new 失败）则走异常路径
          return nullptr;  // 返回空（未识别 ID）
        return (uint32_t *)sub_510000(Block, 48018, (char *)v122 + 3, 12);  // 返回 CNItemAreaStackable 区域放置型消耗品(物品ID=48018, 数据长=12)
      default:
        return nullptr;  // 返回空（未识别 ID）
    }
  }
  // ── [段 51] case 1006：CNActiveStatusStackable(1006,0,0) + sub_602BC0(12, 100.0f, 7, 1) ──
  if ( Block == 1006 )  // Block == 1006：1007-1018 段
  {
    Blockh = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
    v125 = 67;  // 异常展开状态号 → 67
    if ( Blockh != nullptr )  // 非空（new 成功）才继续构造
      v8 = sub_510640(1006, 0, 0);  // 存 CNActiveStatusStackable 主动状态(Block=1006, 0, 0)
    else
      v8 = 0;
    v125 = -1;  // 异常展开状态号 → -1
    sub_602BC0(12, 1120403456, 7, 1);  // 记录追加薄封装（16 字节栈记录尾插）(状态索引=12, 1120403456, 7, 1)
    return (uint32_t *)v8;
  }
  // ── [段 52] Block <= 1000 区（小 ID 段）：仅 0 / 3 / 8 / 10 / 14 / 15 六型有专属构造 ──
  if ( Block <= 1000 )  // Block <= 1000：小 ID 段
  {
    if ( Block != 1000 )  // Block != 1000：小 ID 段
    {
      switch ( Block )
      {
        // ── [段 53] case 0 / 3 / 8 / 10 / 14 / 15：裸单对象族 ──
        //   0 → sub_485DA0=CNRDMoney 金币掉落物（吃 nArg2）；3 → CNIncreaseStatusStackable
        //   8 → sub_50FA90=CNTouchOfRemy；10 → sub_50FE70=CNCallStorageBird；14/15 → sub_50FFB0=CNUsableStackable
        case 0:  // case 0 → CNRDMoney 构造
          Blockd = operator new(0xA4u);  // 分配 0xA4 字节对象壳（164 字节）
          v125 = 170;  // 异常展开状态号 → 170
          if ( Blockd == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          result = (uint32_t *)sub_485DA0(nArg2);  // sub_485DA0：CNRDMoney 构造
          break;
        case 3:  // case 3 → 返回 CNIncreaseStatusStackable 构造
          Blockc = operator new(0xB0u);  // 分配 0xB0 字节对象壳（176 字节）
          v125 = 2;  // 异常展开状态号 → 2
          if ( Blockc == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          result = (uint32_t *)sub_50F7C0(3);  // sub_50F7C0：返回 CNIncreaseStatusStackable 构造
          break;
        case 8:  // case 8 → CNTouchOfRemy 构造
          Blockb = operator new(0xA4u);  // 分配 0xA4 字节对象壳（164 字节）
          v125 = 1;  // 异常展开状态号 → 1
          if ( Blockb == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          result = (uint32_t *)sub_50FA90(8);  // sub_50FA90：CNTouchOfRemy 构造
          break;
        case 10:  // case 10 → CNCallStorageBird 构造
          Blocka = operator new(0xA4u);  // 分配 0xA4 字节对象壳（164 字节）
          v125 = 0;  // 异常展开状态号 → 0
          if ( Blocka == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          result = (uint32_t *)sub_50FE70(10);  // sub_50FE70：CNCallStorageBird 构造
          break;
        case 14:  // case 14 → CNUsableStackable 构造
        case 15:  // case 15 → CNUsableStackable 构造
          Blocke = operator new(0xA4u);  // 分配 0xA4 字节对象壳（164 字节）
          v125 = 171;  // 异常展开状态号 → 171
          if ( Blocke == nullptr )  // 为空（new 失败）则走异常路径
            return nullptr;  // 返回空（未识别 ID）
          result = (uint32_t *)sub_50FFB0(Block);  // sub_50FFB0：CNUsableStackable 构造
          break;
        default:
          return nullptr;  // 返回空（未识别 ID）
      }
      return result;
    }
    // ── [段 54] case 1000：CNChangeHp(50.0f,1000ms) 走 sub_50F850(1000, obj, 0) ──
    Blockf = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
    v125 = 77;  // 异常展开状态号 → 77
    if ( Blockf != nullptr )  // 非空（new 成功）才继续构造
    {
      pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
      LOBYTE(v125) = 78;  // 低字节写异常展开状态号 → 78
      if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
        v4 = sub_4D6810(1112014848, 1000, 1, 1);  // 存 CNChangeHp 回血(伤害值=50.0f, 时长=1000ms)
      else
        v4 = 0;
      LOBYTE(v125) = 77;  // 低字节写异常展开状态号 → 77
      return (uint32_t *)sub_50F850(1000, v4, 0);  // 返回 CNAppendageStackable 记录追加构造(Block=1000, 效果对象=v4, 类型字=0)
    }
    return nullptr;  // 返回空（未识别 ID）
  }
  // ── [段 55] Block 处于 (1000, 1006) 区：1001..1005 五型 ──
  //   1001 CNChangeHp(155.0f,1500ms) / 1002 CNChangeMp(120,1500) / 1003 CNChangeHp(350.0f,2000ms)
  switch ( Block )
  {
    case 1001:
      pMem21 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
      v6 = 81;
      v125 = 81;  // 异常展开状态号 → 81
      if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
        return nullptr;  // 返回空（未识别 ID）
      pMem20 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
      LOBYTE(v125) = 82;  // 低字节写异常展开状态号 → 82
      if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
        goto LABEL_233;  // 跳 LABEL_233
      v7 = sub_4D6810(1125842944, 1500, 1, 1);  // 存 CNChangeHp 回血(伤害值=155.0f, 时长=1500ms)
      break;
    case 1002:
      pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
      v6 = -98;
      v125 = 158;  // 异常展开状态号 → 158
      if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
        return nullptr;  // 返回空（未识别 ID）
      pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
      LOBYTE(v125) = -97;  // 低字节写异常展开状态号 → -97
      if ( pMem21 != nullptr )  // 非空（new 成功）才继续构造
        goto LABEL_324;  // 跳 LABEL_324
      goto LABEL_233;  // 跳 LABEL_233
    case 1003:
      pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
      v6 = -106;
      v125 = 150;  // 异常展开状态号 → 150
      if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
        return nullptr;  // 返回空（未识别 ID）
      pMem21 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
      LOBYTE(v125) = -105;  // 低字节写异常展开状态号 → -105
      if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
        goto LABEL_321;  // 跳 LABEL_321
      v7 = sub_4D6810(1135542272, 2000, 1, 1);  // 存 CNChangeHp 回血(伤害值=350.0f, 时长=2000ms)
      break;
    //   1004 CNChangeMp(55,1000)；1005 → CNAntiFreezePotion(0,0) 防冻药水
    case 1004:
      pMem20 = operator new(0xC8u);  // 分配 0xC8 字节对象壳（200 字节）
      v6 = -102;
      v125 = 154;  // 异常展开状态号 → 154
      if ( pMem20 == nullptr )  // 为空（new 失败）则走异常路径
        return nullptr;  // 返回空（未识别 ID）
      pMem21 = operator new(0x64u);  // 分配 0x64 字节对象壳（100 字节）
      LOBYTE(v125) = -101;  // 低字节写异常展开状态号 → -101
      if ( pMem21 == nullptr )  // 为空（new 失败）则走异常路径
        goto LABEL_325;  // 跳 LABEL_325
      v7 = sub_50F270(55, 1000);  // 存 CNChangeMp 回蓝(MP=55, 时长=1000ms)
      break;
    case 1005:
      Blockg = operator new(0xBCu);  // 分配 0xBC 字节对象壳（188 字节）
      v125 = 69;  // 异常展开状态号 → 69
      if ( Blockg == nullptr )  // 为空（new 失败）则走异常路径
        goto LABEL_71;  // 跳 LABEL_71
      v5 = sub_510E40(Block, 0, 0);  // 存 CNAntiFreezePotion 防冻药水(Block=Block, 0, 0)
      goto LABEL_72;  // 跳 LABEL_72
  }
// ── [段 56] 统一提交尾 LABEL_326：sub_50F850(Block, 效果对象, 0) ──
//   所有「CNChangeHp/CNChangeMp 单效果」路径共用：v6 为异常展开状态号，先还原再调构造
LABEL_326:
  LOBYTE(v125) = v6;
  return (uint32_t *)sub_50F850(Block, v7, 0);  // 返回 CNAppendageStackable 记录追加构造(Block=Block, 效果对象=v7, 类型字=0)
}

