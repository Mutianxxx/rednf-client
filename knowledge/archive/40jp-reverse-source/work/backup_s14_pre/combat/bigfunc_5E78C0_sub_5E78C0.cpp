// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_5E78C0_sub_5E78C0.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x5E78C0）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 1972 行；字符串证据 5 条；外调 6 个
//   串: "Particle/ThrowWeb.ptl"
//   串: "Effect/Animation/ThrowWebShoot.ani"
//   串: "G_SHOULDER"
//   串: "SPIRE_SPIN_LOOP"
//   串: "SPIRE_UP"
//   调: sub_5E78C0 sub_4B7430 sub_699000 sub_484E80 sub_44A980 sub_4F3460
//   case 分支地图（共 11 处）:
//     L266  case 0xA:
//     L466  case 0xC:
//     L475  case 0x11:
//     L487  case 0x12:
//     L519  case 0x13:
//     L819  case 0x14:
//     L889  case 0x15:
//     L924  case 0x16:
//     L1658  case 0x17:
//     L1711  case 0x18:
//     L1903  case 0x1A:
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x5E78C0 sub_5E78C0  size=12390
// ------------------------------------------------------------
void /*usercall*/ sub_5E78C0(int pArg1@<ecx>, double fArg2@<st0>)
{
  int v3; // eax
  int pObj11; // ecx
  int v5; // eax
  int v6; // eax
  int pObj3; // edi
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // edi
  int v18; // eax
  int pObj9; // ecx
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // edi
  int *v26; // edi
  int v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int v32; // edi
  int v33; // eax
  int v34; // eax
  uint32_t *v35; // edi
  int v36; // eax
  int pObj18; // edi
  bool v38; // bl
  int v39; // eax
  int v40; // ebx
  int v41; // eax
  int v42; // eax
  void *v43; // ecx
  int pObj7; // ecx
  int v45; // eax
  int v46; // eax
  int v47; // edx
  int v48; // eax
  int v49; // ecx
  int v50; // edi
  int v51; // eax
  int v52; // ecx
  bool v53; // zf
  int v54; // eax
  int *v55; // ecx
  int v56; // edx
  int v57; // eax
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int pObj20; // edi
  void *v62; // ecx
  int v63; // edx
  uint32_t *v64; // edi
  int pObj22; // ecx
  int v66; // eax
  int pObj12; // ecx
  int v68; // eax
  int pObj14; // ecx
  int v70; // eax
  int v71; // edx
  int v72; // edi
  int v73; // eax
  int v74; // edx
  char *v75; // eax
  int v76; // edi
  int v77; // eax
  int v78; // edx
  char *v79; // eax
  int pObj4; // eax
  int v81; // eax
  bool v82; // sf
  int pObj5; // ecx
  int v84; // eax
  int pObj10; // ecx
  int v86; // eax
  int pObj21; // ecx
  int v88; // eax
  int v89; // edx
  int v90; // eax
  int pObj8; // edi
  int v92; // eax
  int pObj17; // ecx
  int pObj16; // ecx
  int v95; // eax
  int pObj19; // ecx
  int v97; // edi
  int v98; // eax
  int v99; // eax
  int v100; // eax
  int v101; // edi
  int v102; // eax
  int v103; // edi
  int v104; // eax
  int v105; // eax
  int v106; // edx
  int v107; // edi
  int v108; // eax
  int v109; // eax
  int v110; // eax
  uint32_t *v111; // edi
  int v112; // eax
  int pObj13; // ecx
  int v114; // eax
  int v115; // eax
  int v116; // edi
  int v117; // eax
  int v118; // edi
  int v119; // eax
  int v120; // edx
  int v121; // eax
  int v122; // edx
  int *v123; // edi
  int v124; // eax
  int v125; // eax
  int v126; // edx
  int v127; // eax
  int v128; // eax
  int v129; // eax
  void *v130; // ecx
  int pObj; // ecx
  int pObj15; // ecx
  int v133; // edi
  int v134; // eax
  int v135; // eax
  int v136; // eax
  int v137; // eax
  int v138; // eax
  int pObj2; // ecx
  int v140; // edx
  int v141; // eax
  double v142; // st7
  int v143; // eax
  int v144; // eax
  int v145; // edx
  int v146; // eax
  int v147; // ecx
  int v148; // edi
  char *v149; // eax
  int v150; // eax
  int v151; // eax
  int v152; // edi
  int v153; // ecx
  int v154; // eax
  int v155; // edi
  int v156; // eax
  int v157; // edi
  int pObj23; // edi
  int v159; // eax
  int v160; // eax
  int v161; // ebx
  int v162; // eax
  int v163; // eax
  void *v164; // ecx
  int v165; // eax
  int v166; // eax
  int v167; // eax
  int v168; // eax
  int v169; // eax
  int v170; // eax
  int v171; // eax
  int v172; // eax
  int v173; // eax
  int v174; // edi
  int v175; // eax
  int v176; // edi
  int v177; // ecx
  int v178; // eax
  int v179; // edi
  int v180; // eax
  int v181; // eax
  int v182; // edi
  int v183; // eax
  int v184; // eax
  int v185; // eax
  int v186; // eax
  int v187; // eax
  int v188; // ecx
  int v189; // eax
  int v190; // eax
  unsigned int v191; // edi
  int v192; // ecx
  int v193; // edx
  int *v194; // edi
  int v195; // eax
  int v196; // eax
  uint32_t *v197; // eax
  int v198; // edx
  int v199; // eax
  int v200; // edx
  char *v201; // eax
  char *v202; // eax
  int pObj6; // ecx
  int v204; // eax
  int *v205; // edi
  int v206; // eax
  int v207; // eax
  int v208; // eax
  int v209; // edi
  int v210; // eax
  int v211; // eax
  int v212; // eax
  int v213; // edi
  int v214; // eax
  int v215; // eax
  int v216; // eax
  int v217; // eax
  int v218; // eax
  int v219; // eax
  int v220; // [esp-14h] [ebp-84h]
  int v221; // [esp-10h] [ebp-80h]
  int v222; // [esp-Ch] [ebp-7Ch]
  int v223; // [esp-8h] [ebp-78h]
  float v224; // [esp+0h] [ebp-70h]
  int v225; // [esp+0h] [ebp-70h]
  int v226; // [esp+4h] [ebp-6Ch]
  int v227; // [esp+8h] [ebp-68h]
  int v228; // [esp+Ch] [ebp-64h]
  float v229; // [esp+10h] [ebp-60h] BYREF
  float v230; // [esp+14h] [ebp-5Ch]
  float v231; // [esp+18h] [ebp-58h]
  int v232; // [esp+1Ch] [ebp-54h]
  int v233; // [esp+20h] [ebp-50h]
  int v234; // [esp+24h] [ebp-4Ch]
  uint8_t v235[4]; // [esp+28h] [ebp-48h] BYREF
  void *Block; // [esp+2Ch] [ebp-44h]
  int v237; // [esp+30h] [ebp-40h]
  int v238; // [esp+34h] [ebp-3Ch]
  float v239; // [esp+38h] [ebp-38h] BYREF
  float v240; // [esp+3Ch] [ebp-34h]
  float v241; // [esp+40h] [ebp-30h] BYREF
  void *v242; // [esp+44h] [ebp-2Ch]
  void *Src; // [esp+48h] [ebp-28h]
  int v244; // [esp+4Ch] [ebp-24h]
  uint8_t v245[4]; // [esp+50h] [ebp-20h] BYREF
  int v246; // [esp+54h] [ebp-1Ch] BYREF
  int v247; // [esp+58h] [ebp-18h] BYREF
  int i; // [esp+5Ch] [ebp-14h] BYREF
  bool v249; // [esp+63h] [ebp-Dh] BYREF
  int v250; // [esp+6Ch] [ebp-4h]

  // ── [段 1] 入口：sub_4B7430 做升级演出装配前置，随即进入 switch(this+6556 = 大状态机状态号) ──
  //   this=pArg1=CNFighter 格斗家对象（本函数 = CNFighter::vt+332，见 data/class_method_slots.txt）；fArg2=帧 delta
  sub_4B7430((int *)pArg1, fArg2);  // sub_4B7430 —— 升级演出装配（LevelNormalizeLibra.ani + LevelNormalize.ptl；LEVELING_OFF/FLASH；PVP_KO）
  // ── [段 2] ★ 大状态 switch 主表：case 0xA/0xC/0x11/0x12/0x13/0x14/0x15/0x16/0x17/0x18/0x1A ──
  //   文档 docs/21 §五：大状态 = this+6556 角色行为状态机（0-22+，逐帧 tick）；本函数即格斗家的 tick 主体
  switch ( *(uint32_t *)(pArg1 + 6556) )  // 按大状态（pArg1+6556）分派本帧行为
  {
    // ── [段 3] case 0xA（摔投/抓取族）：按 this+7812 分支 ──
    //   +7812==1 → +7808==1 时找投掷目标（CNThrowStackable）并 vt+136 触发投掷；+7812==0 → 按 +7816 分 13/12/49/52 四技能
    case 0xA:  // case 0xA 分派：按 this+7812 分支
      v3 = *(uint32_t *)(pArg1 + 7812);  // 读 v3 = pArg1+7812（子状态A）
      if ( v3 == 1 )  // 条件判定
      {
        if ( *(uint32_t *)(pArg1 + 7808) == 1 )  // 判定 pArg1+7808 == 1（风格/分支选择）
        {
          pObj11 = *(uint32_t *)(pArg1 + 8400);  // 读 pObj11 = pArg1+8400（附属物/状态组件指针）
          if ( pObj11 != 0  // 条件判定
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj11 + 80))(pObj11) != 0  // （上一表达式的参数/条件续行）
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0  // 虚调用 vt+308
            && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 7824)  // 【clock_now(clk)】
            && *(uint32_t *)(pArg1 + 8404) == 0 )  // （上一表达式的参数/条件续行）
          {
            //   +7816==13（背摔）：条件齐（+7808==1、目标 vt+148>=1、+8376 未置）时 vt+1140 建包 + vt+580 发 21004
            v5 = sub_484E80(*(uint32_t *)(pArg1 + 7816));  // sub_484E80 —— 按类型查找下标（同一匹配规则，未命中 -1）
            if ( v5 != -1 )  // 条件判定
            {
              v6 = sub_44A980(v5);  // sub_44A980 —— 带界索引 getter
              pObj3 = __RTDynamicCast(v6, 0, &IRDItem `RTTI Type Descriptor', &CNThrowStackable `RTTI Type Descriptor', 0);  // （表达式续行/复合语句）
              sub_4F3460();  // sub_4F3460 —— 投技对象初始化
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 136))(pObj3, pArg1, 2, -1);  // （表达式续行/复合语句）
              ++*(uint32_t *)(pArg1 + 8404);  // 对象字段自增（标志置位/计数）
            }
          }
        }
      }
      else if ( v3 == 0 )  // 否则条件分支
      {
        v8 = *(uint32_t *)(pArg1 + 7816);  // 读 v8 = pArg1+7816（子状态B）
        switch ( v8 )  // 分派 switch
        {
          case 13:  // 子状态 case 13 分派：按 this+7812 分支
            if ( *(uint32_t *)(pArg1 + 7808) == 1 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 && *(uint8_t *)(pArg1 + 8376) == 0 )  // 条件判定
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308
              {
                v9 = *(uint32_t *)pArg1;  // v9 = *pArg1（对象首字段=虚表）
                v10 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 1140))(  // 虚调用 vt+1140（取返回值）
                        pArg1,  // （上一表达式的参数/条件续行）
                        13,  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        65,  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        50,  // （上一表达式的参数/条件续行）
                        4,  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        0);  // （上一表达式的参数/条件续行）
                (*(void (/*thiscall*/ **)(int, int, int))(v9 + 580))(pArg1, 21004, v10);  // （表达式续行/复合语句）
              }
              *(uint8_t *)(pArg1 + 8376) = 1;  // 写 pArg1+8376 = 1（特效/技能对象B）
            }
            break;  // 跳出本分支
          //   +7816==12（过肩摔）：+8384 首次置位时 vt+876 设置位移 + vt+896 施加；随后 +8388 目标族走另一支（21002 包）
          case 12:  // 子状态 case 12 分派：按 this+7812 分支
            if ( *(uint32_t *)(pArg1 + 7808) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 4 && *(uint8_t *)(pArg1 + 8384) == 0 )  // 条件判定
            {
              (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)pArg1 + 876))(  // 虚调用 vt+876
                pArg1,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                200,  // （上一表达式的参数/条件续行）
                200,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                -10000,  // （上一表达式的参数/条件续行）
                1);  // （上一表达式的参数/条件续行）
              v11 = *(uint32_t *)pArg1;  // v11 = *pArg1（对象首字段=虚表）
              v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 152))(pArg1, 4);  // 虚调用 vt+152（取返回值）
              v13 = sub_432E50(v12);  // sub_432E50 —— 关系码对调映射
              (*(void (/*thiscall*/ **)(int, int))(v11 + 896))(pArg1, v13);  // （表达式续行/复合语句）
              *(uint8_t *)(pArg1 + 8384) = 1;  // 写 pArg1+8384 = 1（保留槽H(过肩摔已置位)）
            }
            if ( *(uint32_t *)(pArg1 + 7808) == 1  // 条件判定
              && *(int *)(*(uint32_t *)(pArg1 + 8388) + 148) >= 1  // （上一表达式的参数/条件续行）
              && *(uint8_t *)(pArg1 + 8392) == 0 )  // （上一表达式的参数/条件续行）
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308
              {
                v14 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 12, -1, -1, 11);  // 虚调用 vt+1140（取返回值）
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 12, 0, v14);  // 虚调用 vt+1160
                v15 = sub_47EF20(v226, v227, v228, LODWORD(v229), LODWORD(v230));  // sub_47EF20 —— 读攻击数据表
                v16 = *(uint32_t *)(pArg1 + 8396);  // 读 v16 = pArg1+8396（名称查询槽）
                v230 = 0.0;  // v230 = 0.0（浮点初值）
                v229 = 0.0;  // v229 = 0.0（浮点初值）
                v226 = 63;
                *(uint32_t *)(v16 + 85) = v15;  // （表达式续行/复合语句）
                v17 = *(uint32_t *)pArg1;  // v17 = *pArg1（对象首字段=虚表）
                v18 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, uint32_t))(*(uint32_t *)pArg1 + 1140))(  // 虚调用 vt+1140（取返回值）
                        pArg1,  // （上一表达式的参数/条件续行）
                        12,  // （上一表达式的参数/条件续行）
                        *(uint32_t *)(pArg1 + 8396),  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        70,  // （上一表达式的参数/条件续行）
                        0);  // （上一表达式的参数/条件续行）
                (*(void (/*thiscall*/ **)(int, int, int))(v17 + 580))(pArg1, 21002, v18);  // （表达式续行/复合语句）
              }
              *(uint8_t *)(pArg1 + 8392) = 1;  // 写 pArg1+8392 = 1（保留槽I）
            }
            break;  // 跳出本分支
          //   +7816==49：先给 +8300 目标施加状态 9（受击）+ vt+564；再按 +7808 决定 sub_5E6920 或建包
          case 49:  // 子状态 case 49 分派：按 this+7812 分支
            pObj9 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj9 = pArg1+8300（被擒/被抱对象）
            if ( pObj9 != 0  // 条件判定
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 840))(pObj9) != 9  // （上一表达式的参数/条件续行）
              && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 840))(*(uint32_t *)(pArg1 + 8300)) != 5  // （上一表达式的参数/条件续行）
              && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 308))(*(uint32_t *)(pArg1 + 8300)) != 0 )  // （上一表达式的参数/条件续行）
            {
              (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(pArg1 + 8300) + 560))(  // （表达式续行/复合语句）
                *(uint32_t *)(pArg1 + 8300),  // （上一表达式的参数/条件续行）
                9,  // （上一表达式的参数/条件续行）
                0,  // （上一表达式的参数/条件续行）
                2,  // （上一表达式的参数/条件续行）
                0);  // （上一表达式的参数/条件续行）
              (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 564))(*(uint32_t *)(pArg1 + 8300));  // （表达式续行/复合语句）
            }
            v20 = *(uint32_t *)(pArg1 + 7808);  // 读 v20 = pArg1+7808（风格/分支选择）
            if ( v20 != 0 )  // 条件判定
            {
              if ( v20 == 1 && *(uint32_t *)(pArg1 + 8300) != 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )  // 条件判定
                sub_5E6920(pArg1);  // sub_5E6920 —— 抓取/投技子例程
            }
            else if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0  // 否则条件分支
                   && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308
            {
              Block = nullptr;  // 临时缓冲指针清零
              v237 = 0;
              v238 = 0;
              v250 = 0;
              v247 = 1;
              sub_431230(&v247);  // sub_431230 —— uint32 vector push_back
              *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 1132))(pArg1, 0));  // 虚调用 vt+1132
              sub_431230(&v247);  // sub_431230 —— uint32 vector push_back
              (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, v235, 0, 0);  // 虚调用 vt+560
              goto LABEL_159;  // 跳转合流点 LABEL_159
            }
            break;  // 跳出本分支
          //   default（+7816==52，投网）：Particle/ThrowWeb.ptl + Effect/Animation/ThrowWebShoot.ani 双资源 ──
          //   sub_42FCB0/sub_44B6C0 两次 CRT 一次性初始化 → sub_431920 动画件 → sub_44E1F0 池化壳 → sub_45FE80 注册
          default:  // 未列出的值 → 兜底
            if ( v8 == 52  // 条件判定
              && *(uint32_t *)(pArg1 + 7808) == 1  // （上一表达式的参数/条件续行）
              && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1  // （上一表达式的参数/条件续行）
              && *(uint8_t *)(pArg1 + 8377) == 0 )  // （上一表达式的参数/条件续行）
            {
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308
              {
                v21 = *(uint32_t *)pArg1;  // v21 = *pArg1（对象首字段=虚表）
                v22 = (*(int (/*thiscall*/ **)(int, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 588))(  // 虚调用 vt+588（取返回值）
                        pArg1,  // （上一表达式的参数/条件续行）
                        "Particle/ThrowWeb.ptl",  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        65,  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        50,  // （上一表达式的参数/条件续行）
                        4,  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        0,  // （上一表达式的参数/条件续行）
                        0);  // （上一表达式的参数/条件续行）
                v23 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 52, v22);  // 虚调用 vt+1140（取返回值）
                (*(void (/*thiscall*/ **)(int, int, int))(v21 + 580))(pArg1, 21015, v23);  // （表达式续行/复合语句）
              }
              v246 = sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
              v250 = 1;
              if ( v246 != 0 )  // 条件判定
              {
                if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // 判定 pArg1+384 < 0x10u（动画池容量(SSO)）
                  LOBYTE(v24) = pArg1 + 108;  // （表达式续行/复合语句）
                else  // 否则分支
                  v24 = *(uint32_t *)(pArg1 + 364);  // 读 v24 = pArg1+364（场景动画池指针）
                v25 = sub_431920(v24, (char)"Effect/Animation/ThrowWebShoot.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
              }
              else  // 否则分支
              {
                v25 = 0;
              }
              v246 = sub_44B6C0(284);  // sub_44B6C0 —— CRT 一次性池初始化 2（池 &unk_98B6F8）
              v250 = 2;
              if ( v246 != 0 )  // 条件判定
                v26 = (int *)sub_44E1F0(v25, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
              else  // 否则分支
                v26 = nullptr;  // v26 = 空指针
              //   【段 3b】+7816==52 续：按朝向 ±65 计算投网落点（+65/-65）后 vt+112 设方位，+8377 置「已建」标志
              v27 = *(uint32_t *)(pArg1 + 116);  // 读 v27 = pArg1+116（观察者容器）
              i = (int)v26;  // （表达式续行/复合语句）
              v250 = -1;
              sub_45FE80(v27, (int)v26, 2, 0, (int)v26, pArg1, 0);  // sub_45FE80 —— 实体注册到演播层
              v28 = *(uint32_t *)pArg1;  // v28 = *pArg1（对象首字段=虚表）
              v247 = *v26;  // （表达式续行/复合语句）
              v29 = (*(int (/*thiscall*/ **)(int))(v28 + 152))(pArg1);  // （表达式续行/复合语句）
              (*(void (/*thiscall*/ **)(int *, int))(v247 + 148))(v26, v29);  // （表达式续行/复合语句）
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 )  // 虚调用 vt+152
                v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 65;  // 虚调用 vt+120（取返回值）
              else  // 否则分支
                v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 65;  // 虚调用 vt+120（取返回值）
              v31 = *(uint32_t *)pArg1;  // v31 = *pArg1（对象首字段=虚表）
              v32 = *v26;  // （表达式续行/复合语句）
              v247 = v30;
              v33 = (*(int (/*thiscall*/ **)(int))(v31 + 128))(pArg1);  // （表达式续行/复合语句）
              v34 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v33 + 50);  // 虚调用 vt+124（取返回值）
              (*(void (/*thiscall*/ **)(int, int, int))(v32 + 112))(i, v247, v34 - 10);  // （表达式续行/复合语句）
              *(uint8_t *)(pArg1 + 8377) = 1;  // 写 pArg1+8377 = 1（保留槽G(投网已建标志)）
            }
            break;  // 跳出本分支
        }
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 4] case 0xC：G_SHOULDER（抓肩动画）—— +8228 未置且 +8220==1 且目标可用时挂载 ──
    //   vt+212 挂动画 G_SHOULDER → vt+1160 关联 → sub_47DCD0(0,0) 设震动/资源档位
    case 0xC:  // case 0xC 分派：G_SHOULDER（抓肩动画）—— +8228 未置且 +8220==1 且目标可用时挂载
      if ( *(uint8_t *)(pArg1 + 8228) == 0 && *(uint32_t *)(pArg1 + 8220) == 1 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )  // 条件判定
      {
        (*(void (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)pArg1 + 212))(pArg1, "G_SHOULDER", -1);  // 虚调用 vt+212
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 1, pArg1, -1);  // 虚调用 vt+1160
        sub_47DCD0(0, 0);  // sub_47DCD0 —— 震动/资源档位设置
        *(uint8_t *)(pArg1 + 8228) = 1;  // 写 pArg1+8228 = 1（抓取标志字节）
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 5] case 0x11：震屏收尾 —— +8244==1 且 +8248==15 且节拍过 500 时调 sub_424120 震屏 ──
    //   sub_424120 = 屏幕震动启动（写震幅 +200、窗 +204），见 docs/21 §1.3
    case 0x11:  // case 0x11 分派：震屏收尾 —— +8244==1 且 +8248==15 且节拍过 500 时调 sub_424120 震屏
      if ( *(uint32_t *)(pArg1 + 8244) == 1  // 条件判定
        && *(uint32_t *)(pArg1 + 8248) == 15  // （上一表达式的参数/条件续行）
        && sub_699000(pArg1 + 6560) >= 500  // 【clock_now(clk)】
        && *(uint8_t *)(pArg1 + 8276) == 0 )  // （上一表达式的参数/条件续行）
      {
        v35 = *(uint32_t **)(*(uint32_t *)(pArg1 + 116) + 132);  // （表达式续行/复合语句）
        v36 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
        sub_424120(v35, 2, *(uint32_t *)(pArg1 + 8256) - v36);  // sub_424120 —— [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
        *(uint8_t *)(pArg1 + 8276) = 1;  // 写 pArg1+8276 = 1（保留槽B）
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 6] case 0x12：★ 抓取投掷的「受击者变色 + 投掷」—— +8292 起手 ──
    //   先给自身施加变色 (-16776961 = 0xFF00FFFF 青) + 状态 1；随后按 fabs(动画 +16) >= 50.0 判距离
    case 0x12:  // case 0x12 分派：★ 抓取投掷的「受击者变色 + 投掷」—— +8292 起手
      if ( *(uint8_t *)(pArg1 + 8292) != 0 )  // 判定 pArg1+8292 != 0（模式标志字节）
      {
        if ( *(uint8_t *)(pArg1 + 248) == 0 || *(uint32_t *)(pArg1 + 252) != -16776961 )  // 条件判定
          (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 284))(pArg1, 1, -16776961, 1, 2);  // 虚调用 vt+284
        if ( *(uint32_t *)(pArg1 + 644) != 1 )  // 判定 pArg1+644 != 1（帧时刻覆盖值）
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 612))(pArg1, 1, 1);  // 虚调用 vt+612
      }
      //   达距离且 +8296+250ms 到点：取 dword_8F8270[vt+924(2)] 目标对象 → 依朝向 ±40 计算落点 → vt+40 设位
      //   → vt+12 激活 + vt+92 取变换 → sub_4600B0 注册（2 号槽）→ +8296 记时刻 → sub_5E5260 清理临时缓冲
      if ( fabs(*(float *)(*(uint32_t *)(pArg1 + 112) + 16)) >= 50.0 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8296) + 250 )  // 【clock_now(clk)】
      {
        pObj18 = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 924))(pArg1, 2)];  // 虚调用 vt+924（取返回值）
        v38 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) == 0;  // 虚调用 vt+152（取返回值）
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj18 + 28))(pObj18) + 84) = v38;  // （表达式续行/复合语句）
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 )  // 虚调用 vt+152
          v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 40;  // 虚调用 vt+120（取返回值）
        else  // 否则分支
          v39 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 40;  // 虚调用 vt+120（取返回值）
        v40 = *(uint32_t *)pObj18;  // （表达式续行/复合语句）
        v247 = v39;
        v41 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚调用 vt+128（取返回值）
        v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v41);  // 虚调用 vt+124（取返回值）
        (*(void (/*thiscall*/ **)(int, int, int))(v40 + 40))(pObj18, v247, v42);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj18 + 12))(pObj18, 0);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)pObj18 + 92))(pObj18, &v241);  // （表达式续行/复合语句）
        v43 = *(void **)(pArg1 + 116);  // （表达式续行/复合语句）
        v250 = 3;
        sub_4600B0(v43, 2, 0, (int)&v241);  // sub_4600B0 —— 演播层注册(槽号)
        *(uint32_t *)(pArg1 + 8296) = sub_699000(pArg1 + 6560);  // （表达式续行/复合语句）
        v250 = -1;
        sub_5E5260(&v241);  // sub_5E5260 —— 清理临时缓冲
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 7] case 0x13：★ 摔投落地/落地冲击（SPIRE_UP/SPIRE_SPIN_LOOP/SPIRE_CRASH/SUPLEX_CRASH） ──
    //   先给 +8300 目标施加状态 9（受击）；然后按目标 vt+148（+120 的 +148 字段）分 2 / 6 两支
    case 0x13:  // case 0x13 分派：★ 摔投落地/落地冲击（SPIRE_UP/SPIRE_SPIN_LOOP/SPIRE_CRASH/SUPLEX_CRASH）
      pObj7 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj7 = pArg1+8300（被擒/被抱对象）
      if ( pObj7 != 0  // 条件判定
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj7 + 840))(pObj7) != 9  // （上一表达式的参数/条件续行）
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 840))(*(uint32_t *)(pArg1 + 8300)) != 5 )  // （上一表达式的参数/条件续行）
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 308))(*(uint32_t *)(pArg1 + 8300)) != 0 )  // 条件判定
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(pArg1 + 8300) + 560))(  // （表达式续行/复合语句）
            *(uint32_t *)(pArg1 + 8300),  // （上一表达式的参数/条件续行）
            9,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            2,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 564))(*(uint32_t *)(pArg1 + 8300));  // （表达式续行/复合语句）
        }
        goto LABEL_254;  // 跳转合流点 LABEL_254
      }
      //   vt+148==2 支：+8332 分型 —— 上抛（Y 速度 0<v<300 时反向加速度 sub_494F20(2,-v)）
      //   → Y 速度为负时 vt+204 卸两动画件 + vt+216 清状态 11 + vt+212 播 SPIRE_SPIN_LOOP + +8334 置位
      if ( *(uint8_t *)(pArg1 + 8324) == 0 )  // 判定 pArg1+8324 == 0（抱人模式字节）
        goto LABEL_108;  // 跳转合流点 LABEL_108
      v45 = *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148);  // （表达式续行/复合语句）
      if ( v45 == 2 )  // 条件判定
      {
        if ( *(uint8_t *)(pArg1 + 8332) != 0 )  // 判定 pArg1+8332 != 0（保留槽E）
        {
          v49 = *(uint32_t *)(pArg1 + 112);  // 读 v49 = pArg1+112（默认共享组件/坐标宿主）
          if ( *(float *)(v49 + 24) > 0.0 && *(float *)(v49 + 24) < 300.0 )  // 条件判定
          {
            v224 = -*(float *)(v49 + 24);  // （表达式续行/复合语句）
            sub_494F20(2, v224);  // sub_494F20 —— 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
          }
          if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) < 0.0 )  // 条件判定
          {
            sub_4AECE0(3);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 虚调用 vt+204
              pArg1,  // （上一表达式的参数/条件续行）
              -1,  // （上一表达式的参数/条件续行）
              *(uint32_t *)(pArg1 + 8336),  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 虚调用 vt+204
              pArg1,  // （上一表达式的参数/条件续行）
              1,  // （上一表达式的参数/条件续行）
              *(uint32_t *)(pArg1 + 8340),  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 11);  // 虚调用 vt+216
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212
              pArg1,  // （上一表达式的参数/条件续行）
              "SPIRE_SPIN_LOOP",  // （上一表达式的参数/条件续行）
              12,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
            *(uint8_t *)(pArg1 + 8334) = 1;  // 写 pArg1+8334 = 1（成对判定字节）
          }
        }
        //   否则（+8332 未置）：vt+1140 建 18 号包 → vt+1160 关联 → sub_494F20 设速率 → vt+212 播 SPIRE_UP
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308
        {
          v46 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 18, -1, -1);  // 虚调用 vt+1140（取返回值）
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 18, 2, v46);  // 虚调用 vt+1160
          *(float *)&v247 = (float)(int)sub_47EF20(11, v226, v227, v228, LODWORD(v229));  // （表达式续行/复合语句）
          sub_494F20(2, *(float *)&v247);  // sub_494F20 —— 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
          v47 = *(uint32_t *)pArg1;  // v47 = *pArg1（对象首字段=虚表）
          v229 = 0.0;  // v229 = 0.0（浮点初值）
          v226 = (int)"SPIRE_UP";  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int))(v47 + 212))(pArg1);  // （表达式续行/复合语句）
          v48 = *(uint32_t *)pArg1;  // v48 = *pArg1（对象首字段=虚表）
          *(uint8_t *)(pArg1 + 8332) = 1;  // 写 pArg1+8332 = 1（保留槽E）
          (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, uint32_t, uint32_t))(v48 + 876))(pArg1, 0, 143, 119, 1, 0, 0);  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int, int, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 虚调用 vt+876
            pArg1,  // （上一表达式的参数/条件续行）
            1,  // （上一表达式的参数/条件续行）
            95,  // （上一表达式的参数/条件续行）
            79,  // （上一表达式的参数/条件续行）
            1,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
        }
        //   +8332 已置且 Y >= 0：收招播 SPIRE_UP（第三支，11 号优先级）
        else if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) >= 0.0 )  // 否则条件分支
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212
            pArg1,  // （上一表达式的参数/条件续行）
            "SPIRE_UP",  // （上一表达式的参数/条件续行）
            11,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
          *(uint8_t *)(pArg1 + 8332) = 1;  // 写 pArg1+8332 = 1（保留槽E）
        }
      }
      //   vt+148==6 支（长动画形态）：按帧时刻 + vt+128 高度 >= 100 时用 sub_491C70/sub_493A60 重锚动画时间
      else if ( v45 == 6 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) >= 100 )  // 虚调用 vt+128
      {
        i = *(uint32_t *)(pArg1 + 120);  // 读 i = pArg1+120（动画对象）
        *(float *)&v247 = COERCE_FLOAT(sub_491C70(6));  // （表达式续行/复合语句）
        v50 = sub_4910A0(i) - v247;  // （表达式续行/复合语句）
        v51 = sub_491C70(4);  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
        sub_493A60(*(uint32_t *)(pArg1 + 120), v50 + v51);  // sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
      }
      //   随后 +8326 分型：+8333 未置且过 +8328+100ms 时 sub_4A0550(40)（重力写速）+ sub_4AECE0(7)（动画切 7）
      if ( *(uint8_t *)(pArg1 + 8326) != 0 )  // 判定 pArg1+8326 != 0（保留槽C）
      {
        if ( *(uint8_t *)(pArg1 + 8333) == 0 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8328) + 100 )  // 【clock_now(clk)】
        {
          sub_4A0550(40);
          sub_4AECE0(7);
          *(uint8_t *)(pArg1 + 8333) = 1;  // 写 pArg1+8333 = 1（保留槽F）
        }
LABEL_108:  // 标签 LABEL_108：合流点
        if ( *(uint8_t *)(pArg1 + 8326) != 0 )  // 判定 pArg1+8326 != 0（保留槽C）
          goto LABEL_254;  // 跳转合流点 LABEL_254
      }
      //   再按 +8324/+8325 两标志与动画 Y/状态位选「落地」支路
      if ( *(uint8_t *)(pArg1 + 8324) != 0 )  // 判定 pArg1+8324 != 0（抱人模式字节）
      {
        if ( *(uint8_t *)(pArg1 + 8332) == 0 )  // 判定 pArg1+8332 == 0（保留槽E）
          goto LABEL_254;  // 跳转合流点 LABEL_254
        v52 = *(uint32_t *)(pArg1 + 112);  // 读 v52 = pArg1+112（默认共享组件/坐标宿主）
        if ( *(float *)(v52 + 24) >= 0.0 || *(uint32_t *)(v52 + 192) != 4 )  // 条件判定
          goto LABEL_254;  // 跳转合流点 LABEL_254
      }
      else  // 否则分支
      {
        if ( *(uint8_t *)(pArg1 + 8325) != 0 )  // 判定 pArg1+8325 != 0（抱人子模式）
          v53 = *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) == 6;  // （表达式续行/复合语句）
        else  // 否则分支
          v53 = *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) == 4;  // （表达式续行/复合语句）
        if ( !v53 )  // 条件判定
          goto LABEL_254;  // 跳转合流点 LABEL_254
      }
      //   落地确认后三件事：sub_424120 震屏(10,200) → 目标对象取位 → sub_4600B0 注册特效 → vt+876 归位
      sub_424120(*(uint32_t **)(*(uint32_t *)(pArg1 + 116) + 132), 10, 200);  // sub_424120 —— [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
      if ( *(uint32_t *)(pArg1 + 8300) != 0 )  // 判定 pArg1+8300 != 0（被擒/被抱对象）
      {
        v54 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 924))(pArg1, 0);  // 虚调用 vt+924（取返回值）
        v55 = *(int **)(pArg1 + 8300);  // （表达式续行/复合语句）
        v56 = *v55;  // （表达式续行/复合语句）
        v247 = dword_8F8270[v54];  // （表达式续行/复合语句）
        v57 = *(uint32_t *)v247;  // （表达式续行/复合语句）
        i = (int)v55;  // （表达式续行/复合语句）
        v246 = v57;
        v58 = (*(int (**)(void))(v56 + 128))();  // （表达式续行/复合语句）
        v59 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)i + 124))(i, v58);  // （表达式续行/复合语句）
        v60 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)i + 120))(i, v59);  // （表达式续行/复合语句）
        pObj20 = v247;
        (*(void (/*thiscall*/ **)(int, int))(v246 + 40))(v247, v60);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj20 + 12))(pObj20, 0);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)pObj20 + 92))(pObj20, &v241);  // （表达式续行/复合语句）
        v62 = *(void **)(pArg1 + 116);  // （表达式续行/复合语句）
        v250 = 4;
        sub_4600B0(v62, 2, 0, (int)&v241);  // sub_4600B0 —— 演播层注册(槽号)
        v250 = -1;
        sub_5E5260(&v241);  // sub_5E5260 —— 清理临时缓冲
      }
      //   收尾：+8324 时 vt+876 清双动画 + 循环 vt+208 卸两件 + vt+216 + vt+212 播 SPIRE_CRASH；否则按 vt+1140(22) 播 SUPLEX_CRASH
      v63 = *(uint32_t *)pArg1;  // v63 = *pArg1（对象首字段=虚表）
      if ( *(uint8_t *)(pArg1 + 8324) != 0 )  // 判定 pArg1+8324 != 0（抱人模式字节）
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v63 + 876))(pArg1, 0, 0, 0, 0, 0, 0);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(  // 虚调用 vt+876
          pArg1,  // （上一表达式的参数/条件续行）
          1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        v64 = (uint32_t *)(pArg1 + 8336);  // （表达式续行/复合语句）
        v247 = 2;
        do
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *v64++);  // 虚调用 vt+208
          --v247;  // （表达式续行/复合语句）
        }
        while ( *(float *)&v247 != 0.0 );  // 循环
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 12);  // 虚调用 vt+216
        *(uint8_t *)(pArg1 + 8334) = 0;  // 写 pArg1+8334 = 0（成对判定字节）
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212
          pArg1,  // （上一表达式的参数/条件续行）
          "SPIRE_CRASH",  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
      }
      else if ( (*(int (/*thiscall*/ **)(int, int))(v63 + 1140))(pArg1, 22) > 0 )  // 否则条件分支
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212
          pArg1,  // （上一表达式的参数/条件续行）
          "SUPLEX_CRASH",  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
      }
      //   最后（vt+308 存活门）：取 +8300 目标坐标三轴浮点 → sub_4E5F70（★硬直率掷+上报）→ 伤害包 21008/21001
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308
      {
        pObj22 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj22 = pArg1+8300（被擒/被抱对象）
        if ( pObj22 != 0 )  // 条件判定
        {
          v229 = 0.0;  // v229 = 0.0（浮点初值）
          v230 = 0.0;  // v230 = 0.0（浮点初值）
          v231 = 0.0;  // v231 = 0.0（浮点初值）
          v232 = 0;
          v233 = 0;
          v234 = 0;
          v66 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj22 + 120))(pObj22);  // （表达式续行/复合语句）
          pObj12 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj12 = pArg1+8300（被擒/被抱对象）
          v246 = v66;
          v229 = (float)v66;  // （表达式续行/复合语句）
          v68 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj12 + 124))(pObj12);  // （表达式续行/复合语句）
          pObj14 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj14 = pArg1+8300（被擒/被抱对象）
          v246 = v68;
          v230 = (float)v68;  // （表达式续行/复合语句）
          v70 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj14 + 128))(pObj14);  // （表达式续行/复合语句）
          v71 = *(uint32_t *)(pArg1 + 8300);  // 读 v71 = pArg1+8300（被擒/被抱对象）
          v246 = v70;
          v231 = (float)v70;  // （表达式续行/复合语句）
          sub_4E5F70(pArg1, v71, &v229, 1, 1);  // sub_4E5F70 —— ★ 硬直率掷（研究 §5.1 第 14 轮定案：同构于暴击掷）
          v72 = *(uint8_t *)(pArg1 + 8324) != 0 ? 18 : 9;  // （表达式续行/复合语句）
          v246 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 388))(pArg1);  // 虚调用 vt+388（取返回值）
          v73 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, v72);  // 虚调用 vt+1140（取返回值）
          v74 = *(uint32_t *)pArg1;  // v74 = *pArg1（对象首字段=虚表）
          v247 = v73;
          v75 = (char *)(*(int (/*thiscall*/ **)(int, int))(v74 + 1160))(pArg1, v72);  // （表达式续行/复合语句）
          v76 = sub_47EFD0(v75, COERCE_FLOAT(1), v247, v246, v246, 0);  // sub_47EFD0 —— 攻击上下文计算
          v53 = *(uint8_t *)(pArg1 + 8325) == 0;  // （表达式续行/复合语句）
          v247 = v76;
          if ( !v53 )  // 条件判定
          {
            v246 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 388))(pArg1);  // 虚调用 vt+388（取返回值）
            v77 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 10);  // 虚调用 vt+1140（取返回值）
            v78 = *(uint32_t *)pArg1;  // v78 = *pArg1（对象首字段=虚表）
            v247 = v77;
            v79 = (char *)(*(int (/*thiscall*/ **)(int, int))(v78 + 1160))(pArg1, 10);  // （表达式续行/复合语句）
            v76 += sub_47EFD0(v79, COERCE_FLOAT(1), v247, v246, v246, 0);  // （表达式续行/复合语句）
            v247 = v76;
          }
          pObj4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 792))(pArg1, 10);  // 虚调用 vt+792（取返回值）
          i = pObj4;
          if ( pObj4 != 0  // 条件判定
            && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 16))(pObj4) + 4) == 10876  // （上一表达式的参数/条件续行）
            && (uint8_t)sub_4C1070(i) != 0  // （上一表达式的参数/条件续行）
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)i + 224))(i) != 0 )  // （上一表达式的参数/条件续行）
          {
            v76 = (uint64_t)((double)v247 * 1.15);  // （表达式续行/复合语句）
          }
          v81 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 22);  // 虚调用 vt+1140（取返回值）
          v53 = v81 == 0;  // （表达式续行/复合语句）
          v82 = v81 < 0;  // （表达式续行/复合语句）
          LOBYTE(v81) = *(uint8_t *)(pArg1 + 8324);  // （表达式续行/复合语句）
          v249 = !v82 && !v53;  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, unsigned int, uint32_t, uint32_t, int, uint32_t, int, bool *))(*(uint32_t *)pArg1 + 580))(  // 虚调用 vt+580
            pArg1,  // （上一表达式的参数/条件续行）
            (uint8_t)v81 != 0 ? 21008 : 21001,  // （上一表达式的参数/条件续行）
            v76,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            (uint8_t)v81 != 0 ? 0 : 0xFFFFFFD1,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            4,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            1,  // （上一表达式的参数/条件续行）
            &v249);  // （上一表达式的参数/条件续行）
          //   +8324 未置且 vt+1140(11)>0 时：sub_605840 打包 + sub_4E4A50(21011, 动作 11) 二次上报
          if ( *(uint8_t *)(pArg1 + 8324) == 0 && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 11) > 0 )  // 虚调用 vt+8324
          {
            pObj5 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj5 = pArg1+8300（被擒/被抱对象）
            v239 = 0.0;  // v239 = 0.0（浮点初值）
            v240 = 0.0;  // v240 = 0.0（浮点初值）
            v241 = 0.0;  // v241 = 0.0（浮点初值）
            v242 = nullptr;  // v242 = 空指针
            Src = nullptr;  // 源缓冲指针清零
            v244 = 0;
            v84 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 120))(pObj5, v226);  // （表达式续行/复合语句）
            pObj10 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj10 = pArg1+8300（被擒/被抱对象）
            v246 = v84;
            v239 = (float)v84;  // （表达式续行/复合语句）
            v86 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj10 + 124))(pObj10);  // （表达式续行/复合语句）
            pObj21 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj21 = pArg1+8300（被擒/被抱对象）
            v246 = v86;
            v240 = (float)v86;  // （表达式续行/复合语句）
            v88 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj21 + 128))(pObj21);  // （表达式续行/复合语句）
            v89 = *(uint32_t *)(pArg1 + 8300);  // 读 v89 = pArg1+8300（被擒/被抱对象）
            v246 = v88;
            v241 = (float)v88;  // （表达式续行/复合语句）
            v244 = 1106247680;
            *(float *)&v247 = 0.0;  // （表达式续行/复合语句）
            v90 = sub_605840(&v247, v89, &v239, 1);  // sub_605840 —— 30 字节全局包
            pObj8 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj8 = pArg1+8300（被擒/被抱对象）
            v226 = v90;
            v225 = v247;
            v223 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚调用 vt+152（取返回值）
            v222 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 128))(pObj8);  // （表达式续行/复合语句）
            v221 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 124))(pObj8);  // （表达式续行/复合语句）
            v220 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 120))(pObj8);  // （表达式续行/复合语句）
            v92 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1140))(pArg1);  // 虚调用 vt+1140（取返回值）
            sub_4E4A50(pArg1, 21011, v92, 11, v220, v221, v222, v223, 0, v225);  // sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
          }
        }
      }
      // ── [段 8] case 0x13 尾部：+8326 置位 + +8328 记当前节拍（本态完成时间戳） ──
      *(uint8_t *)(pArg1 + 8326) = 1;  // 写 pArg1+8326 = 1（保留槽C）
      *(uint32_t *)(pArg1 + 8328) = sub_699000(pArg1 + 6560);  // （表达式续行/复合语句）
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 9] case 0x14：★ 抓取持续（跟随被抓目标位置 + 位移同步） ──
    //   +8356 = 被抓对象；vt+724（存活判定）为真则解绑；vt+840（大状态）==9 走位置跟随支
    case 0x14:  // case 0x14 分派：★ 抓取持续（跟随被抓目标位置 + 位移同步）
      pObj17 = *(uint32_t *)(pArg1 + 8356);  // 读 pObj17 = pArg1+8356（抱人目标对象）
      if ( pObj17 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj17 + 724))(pObj17) != 0 )  // 条件判定
        *(uint32_t *)(pArg1 + 8356) = 0;  // 写 pArg1+8356 = 0（抱人目标对象）
      pObj16 = *(uint32_t *)(pArg1 + 8356);  // 读 pObj16 = pArg1+8356（抱人目标对象）
      if ( pObj16 != 0 )  // 条件判定
      {
        v95 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj16 + 840))(pObj16);  // （表达式续行/复合语句）
        pObj19 = *(uint32_t *)(pArg1 + 8356);  // 读 pObj19 = pArg1+8356（抱人目标对象）
        if ( v95 == 9 )  // 条件判定
        {
          //   vt+688 取目标动画对象 +20 → vt+200（命中处理器基址）比对；不一致则 vt+196 重设 + sub_4AECE0 切动画
          v97 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj19 + 688))(pObj19) + 20);  // （表达式续行/复合语句）
          if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8356) + 200))(*(uint32_t *)(pArg1 + 8356)) == v97 )  // 条件判定
          {
            if ( *(uint32_t *)(pArg1 + 8344) != 1 || *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) != 0 )  // 条件判定
            {
              if ( *(uint8_t *)(pArg1 + 8360) != 0 )  // 判定 pArg1+8360 != 0（抱人清零字节）
              {
                v99 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8356) + 688))(*(uint32_t *)(pArg1 + 8356));  // （表达式续行/复合语句）
                v100 = sub_42FC90(*(uint32_t *)(v99 + 20));  // sub_42FC90 —— 88B 元素计数（+44 组）
                sub_4AECE0(v100 - 1);
                *(uint8_t *)(pArg1 + 8360) = 0;  // 写 pArg1+8360 = 0（抱人清零字节）
              }
            }
            else if ( *(uint8_t *)(pArg1 + 8360) == 0 )  // 否则条件分支
            {
              (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8356) + 688))(*(uint32_t *)(pArg1 + 8356));  // （表达式续行/复合语句）
              v98 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8356) + 912))(*(uint32_t *)(pArg1 + 8356));  // （表达式续行/复合语句）
              sub_4AECE0(v98);
              *(uint8_t *)(pArg1 + 8360) = 1;  // 写 pArg1+8360 = 1（抱人清零字节）
            }
          }
          else  // 否则分支
          {
            v101 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8356) + 688))(*(uint32_t *)(pArg1 + 8356))  // （表达式续行/复合语句）
                             + 20);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 8356) + 196))(*(uint32_t *)(pArg1 + 8356), v101);  // （表达式续行/复合语句）
            v102 = sub_42FC90(v101);  // sub_42FC90 —— 88B 元素计数（+44 组）
            sub_4AECE0(v102 - 1);
            (*(void (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 8356) + 612))(*(uint32_t *)(pArg1 + 8356), 1, 1);  // （表达式续行/复合语句）
          }
        }
        else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj19 + 840))(pObj19) != 5  // 否则条件分支
               && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8356) + 308))(*(uint32_t *)(pArg1 + 8356)) != 0 )  // （上一表达式的参数/条件续行）
        {
          v103 = **(uint32_t **)(pArg1 + 8356);  // （表达式续行/复合语句）
          i = *(uint32_t *)(pArg1 + 8356);  // 读 i = pArg1+8356（抱人目标对象）
          v104 = (*(int (/*stdcall*/ **)(uint32_t))(v103 + 124))(0);  // （表达式续行/复合语句）
          v105 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)i + 120))(i, v104);  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int, int))(v103 + 108))(i, v105);  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(pArg1 + 8356) + 560))(  // （表达式续行/复合语句）
            *(uint32_t *)(pArg1 + 8356),  // （上一表达式的参数/条件续行）
            9,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            2,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8356) + 564))(*(uint32_t *)(pArg1 + 8356));  // （表达式续行/复合语句）
        }
        //   尾部 vt+112 把自身位置跟随到「+8372 偏移 + 目标 X」（+1 格）
        v106 = **(uint32_t **)(pArg1 + 8356);  // （表达式续行/复合语句）
        v107 = *(uint32_t *)pArg1;  // v107 = *pArg1（对象首字段=虚表）
        i = *(uint32_t *)(pArg1 + 8356);  // 读 i = pArg1+8356（抱人目标对象）
        v108 = (*(int (/*stdcall*/ **)(uint32_t))(v106 + 124))(0);  // （表达式续行/复合语句）
        v109 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)i + 120))(i, v108 + 1);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, int))(v107 + 112))(pArg1, *(uint32_t *)(pArg1 + 8372) + v109);  // （表达式续行/复合语句）
      }
      //   若 +8356 为空：vt+560(0,...) 自行退出本态
      else  // 否则分支
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 10] case 0x15：★ 抓取/掉落的包同步（同一编码发两种状态号） ──
    //   分支一（目标 +170 非 0）：包 = [1, +6988!=0, 0] → vt+560(6, 包) 发 6 号态
    case 0x15:  // case 0x15 分派：★ 抓取/掉落的包同步（同一编码发两种状态号）
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 条件判定
      {
        Block = nullptr;  // 临时缓冲指针清零
        v237 = 0;
        v238 = 0;
        v250 = 5;
        v246 = 1;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = *(uint8_t *)(pArg1 + 6988) != 0;  // （表达式续行/复合语句）
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 6, v235, 0, 0);  // 虚调用 vt+560
LABEL_159:  // 标签 LABEL_159：合流点
        v250 = -1;
        sub_5E5260(v235);  // sub_5E5260 —— 清理临时缓冲
      }
      //   分支二（动画 +192==4）：包 = [2, +6988!=0, 0] → vt+560(6, 包)
      else if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 )  // 否则条件分支
      {
        Block = nullptr;  // 临时缓冲指针清零
        v237 = 0;
        v238 = 0;
        v250 = 6;
        v246 = 2;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = *(uint8_t *)(pArg1 + 6988) != 0;  // （表达式续行/复合语句）
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 6, v235, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        sub_5E5260(v235);  // sub_5E5260 —— 清理临时缓冲
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 11] case 0x16：★ 连击计数器的三相位显示（+8420 起为 2 元组数组 {对象, 时间}） ──
    //   相位判定：now < 起始 → 亮 (1,5,-12788993 黄)；起始+33ms 内 → 黄；+33..+66ms → 橙 (-16738561)
    case 0x16:  // case 0x16 分派：★ 连击计数器的三相位显示（+8420 起为 2 元组数组 {对象, 时间}）
      v110 = sub_699000(pArg1 + 8);  // 【clock_now(clk)】
      v111 = *(uint32_t **)(pArg1 + 8420);  // （表达式续行/复合语句）
      v246 = v110;
      if ( v111 != *(uint32_t **)(pArg1 + 8424) )  // 条件判定
      {
        while ( 1 )  // 循环
        {
          v112 = v111[1] + *(uint32_t *)(pArg1 + 520);  // （表达式续行/复合语句）
          if ( v246 < v112 )  // 条件判定
            goto LABEL_168;  // 跳转合流点 LABEL_168
          if ( v246 >= v112 + 33 )  // 条件判定
            break;  // 跳出本分支
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*v111 + 260))(*v111, 1, 5, -12788993);  // （表达式续行/复合语句）
          v111 += 2;  // （表达式续行/复合语句）
LABEL_170:  // 标签 LABEL_170：合流点
          if ( v111 == *(uint32_t **)(pArg1 + 8424) )  // 条件判定
            goto LABEL_171;  // 跳转合流点 LABEL_171
        //   now >= 起始+66ms → vt+260(0,0,0) 熄灭并把该元素从 +8420 数组移除（sub_5E5220 尾删）
        }
        pObj13 = *v111;  // （表达式续行/复合语句）
        if ( v246 >= v112 + 66 )  // 条件判定
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj13 + 260))(pObj13, 0, 0, 0);  // （表达式续行/复合语句）
          v111 = *(uint32_t **)sub_5E5220(v245, v111);  // （表达式续行/复合语句）
          goto LABEL_170;  // 跳转合流点 LABEL_170
        }
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj13 + 260))(pObj13, 1, 5, -16738561);  // （表达式续行/复合语句）
LABEL_168:  // 标签 LABEL_168：合流点
        v111 += 2;  // （表达式续行/复合语句）
        goto LABEL_170;  // 跳转合流点 LABEL_170
      }
LABEL_171:  // 标签 LABEL_171：合流点
      //   随后：动作 +148 ∈ {1,2} 且距 +8432 满 50ms 时，向左右 ±1 步试探 vt+136（可站立）与 vt+132，成功则 vt+112 位移
      v114 = *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148);  // （表达式续行/复合语句）
      if ( (v114 == 1 || v114 == 2) && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8432) + 50 )  // 【clock_now(clk)】
      {
        v115 = *(uint32_t *)pArg1;  // v115 = *pArg1（对象首字段=虚表）
        v116 = 2 * (*(uint8_t *)(pArg1 + 8436) == 0) - 1;  // （表达式续行/复合语句）
        v247 = v116;
        if ( (*(int (/*thiscall*/ **)(int))(v115 + 152))(pArg1) == 0 )  // 条件判定
          v247 = -v116;  // （表达式续行/复合语句）
        v117 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);  // 虚调用 vt+120（取返回值）
        v118 = v247 + v117;  // （表达式续行/复合语句）
        v119 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);  // 虚调用 vt+124（取返回值）
        v120 = *(uint32_t *)pArg1;  // v120 = *pArg1（对象首字段=虚表）
        i = v119;
        *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(v120 + 128))(pArg1));  // （表达式续行/复合语句）
        if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pArg1 + 136))(pArg1, v118, i, 0) != 0  // 虚调用 vt+136
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 132))(pArg1, v247) != 0 )  // 虚调用 vt+132
        {
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pArg1 + 112))(pArg1, v118, i, v247);  // 虚调用 vt+112
        }
        //   +8436 左右翻转 + +8432 记时刻 —— 即「喝醉/摇晃」式游走
        *(uint8_t *)(pArg1 + 8436) = *(uint8_t *)(pArg1 + 8436) == 0;  // （表达式续行/复合语句）
        *(uint32_t *)(pArg1 + 8432) = sub_699000(pArg1 + 6560);  // （表达式续行/复合语句）
      }
// ── [段 12] ★ LABEL_254：本帧通用尾（所有 case 汇合于此）──
//   门：仅当自身是本地玩家（dword_8F7C04 == this 且非主状态 2 冻结）时才继续
LABEL_254:  // 标签 LABEL_254：合流点
      //   随后一长串「技能槽就绪 → 发对应状态包」的检查表（sub_4842B0 查技能槽 + vt+1312 条件 + vt+560 发包）
      if ( dword_8F7C04 != pArg1 || *(uint32_t *)(pArg1 + 200) == 2 )  // 条件判定
        return;  // 返回（本帧结束）
      v165 = *(uint32_t *)(pArg1 + 6556);  // 读 v165 = pArg1+6556（枪手大状态ID）
      //   状态白名单 0/11/15 → 包 12（+1312(1)）；0/11 → 包 15；15 → 包 12（+4BFBC0 表登记门）
      if ( (v165 == 0 || v165 == 11 || v165 == 15)  // 条件判定
        && sub_4842B0(1, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 1) != 0 )  // 虚调用 vt+1312
      {
        Block = nullptr;  // 临时缓冲指针清零
        v237 = 0;
        v238 = 0;
        v250 = 12;
        v246 = 1;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 12, v235, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        sub_5E5260(v235);  // sub_5E5260 —— 清理临时缓冲
      }
      //   0/11 → 包 15（+1312(2)）；15 态 → 包 0 复位；0/11/8 → 包 16（+1312(4)）
      v166 = *(uint32_t *)(pArg1 + 6556);  // 读 v166 = pArg1+6556（枪手大状态ID）
      if ( (v166 == 0 || v166 == 11)  // 条件判定
        && sub_4842B0(2, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 2) != 0 )  // 虚调用 vt+1312
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 15, 0, 0, 0);  // 虚调用 vt+560
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 15 )  // 判定 pArg1+6556 == 15（枪手大状态ID）
      {
        if ( (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 )  // 条件判定
        {
          Block = nullptr;  // 临时缓冲指针清零
          v237 = 0;
          v238 = 0;
          v250 = 13;
          v246 = 2;
          sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 12, v235, 0, 0);  // 虚调用 vt+560
          v250 = -1;
          sub_5E5260(v235);  // sub_5E5260 —— 清理临时缓冲
        }
        if ( (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 || sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8232) )  // 条件判定
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
      }
      //   0/11/8 → 包 16（+1312(6)）；16 态退出条件 +170；0/11/8 → 包 23（+1312(5)）
      v167 = *(uint32_t *)(pArg1 + 6556);  // 读 v167 = pArg1+6556（枪手大状态ID）
      if ( (v167 == 0 || v167 == 11 || v167 == 8)  // 条件判定
        && sub_4842B0(4, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 4) != 0 )  // 虚调用 vt+1312
      {
        Block = nullptr;  // 临时缓冲指针清零
        v237 = 0;
        v238 = 0;
        v250 = 14;
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 16, v235, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        sub_5E5260(v235);  // sub_5E5260 —— 清理临时缓冲
      }
      //   23 态退出：包 0；0/11 → 包 17（8 号技能，含坐标/动作参数序列）
      v168 = *(uint32_t *)(pArg1 + 6556);  // 读 v168 = pArg1+6556（枪手大状态ID）
      if ( (v168 == 0 || v168 == 11 || v168 == 8)  // 条件判定
        && sub_4842B0(6, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 6) != 0 )  // 虚调用 vt+1312
      {
        Block = nullptr;  // 临时缓冲指针清零
        v237 = 0;
        v238 = 0;
        v250 = 15;
        v246 = 6;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 16, v235, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        sub_5E5260(v235);  // sub_5E5260 —— 清理临时缓冲
      }
      //   0/11 → 包 17（15 号技能，同构参数序列）
      if ( *(uint32_t *)(pArg1 + 6556) == 16 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 条件判定
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
      v169 = *(uint32_t *)(pArg1 + 6556);  // 读 v169 = pArg1+6556（枪手大状态ID）
      if ( (v169 == 0 || v169 == 11 || v169 == 8)  // 条件判定
        && sub_4842B0(5, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 5) != 0 )  // 虚调用 vt+1312
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 23, 0, 0, 0);  // 虚调用 vt+560
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 23 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 条件判定
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
      //   17 态超时：v174 分型——非 0 发包 0 退出，否则 ++ 包 17
      v170 = *(uint32_t *)(pArg1 + 6556);  // 读 v170 = pArg1+6556（枪手大状态ID）
      if ( (v170 == 0 || v170 == 11)  // 条件判定
        && sub_4842B0(8, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 8) != 0 )  // 虚调用 vt+1312
      {
        v242 = nullptr;  // v242 = 空指针
        Src = nullptr;  // 源缓冲指针清零
        v244 = 0;
        v250 = 16;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 8;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v171 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 8);  // 虚调用 vt+1140（取返回值）
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 8, v171);  // 虚调用 vt+1160
        v246 = sub_4B1C40(v226);  // sub_4B1C40 —— 14 字节表按 1 基索引取值
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 8);  // 虚调用 vt+1160
        v246 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v226 = 0;
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 17, &v241, 0);  // 虚调用 vt+560
        v250 = -1;
        sub_5E5260(&v241);  // sub_5E5260 —— 清理临时缓冲
      }
      //   0/11/8/26 → 包 18（依次试 9/18/49 三技能槽）
      v172 = *(uint32_t *)(pArg1 + 6556);  // 读 v172 = pArg1+6556（枪手大状态ID）
      if ( (v172 == 0 || v172 == 11)  // 条件判定
        && sub_4842B0(15, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 15) != 0 )  // 虚调用 vt+1312
      {
        v242 = nullptr;  // v242 = 空指针
        Src = nullptr;  // 源缓冲指针清零
        v244 = 0;
        v250 = 17;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 15;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v173 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 15);  // 虚调用 vt+1140（取返回值）
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 15, v173);  // 虚调用 vt+1160
        v246 = sub_4B1C40(v226);  // sub_4B1C40 —— 14 字节表按 1 基索引取值
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 15);  // 虚调用 vt+1160
        v246 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v226 = 0;
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 17, &v241, 0);  // 虚调用 vt+560
        v250 = -1;
        sub_5E5260(&v241);  // sub_5E5260 —— 清理临时缓冲
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 17 )  // 判定 pArg1+6556 == 17（枪手大状态ID）
      {
        v174 = *(uint32_t *)(pArg1 + 8244);  // 读 v174 = pArg1+8244（变体选择）
        if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 4 * v174 + 8252) )  // 【clock_now(clk)】
        {
          if ( v174 != 0 )  // 条件判定
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
          }
          else  // 否则分支
          {
            Block = nullptr;  // 临时缓冲指针清零
            v237 = 0;
            v238 = 0;
            v250 = 18;
            v246 = 1;
            sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 17, v235, 0, 0);  // 虚调用 vt+560
            v250 = -1;
            sub_5E5260(v235);  // sub_5E5260 —— 清理临时缓冲
          }
        }
      }
      //   18 态超时（+8288）→ 包 0；19 态按 +8324/+8333 与动画 Y 负值判定退出
      v175 = *(uint32_t *)(pArg1 + 6556);  // 读 v175 = pArg1+6556（枪手大状态ID）
      if ( v175 == 0 || v175 == 11 || v175 == 8 || v175 == 26 )  // 条件判定
      {
        v242 = (void *)9;  // （表达式续行/复合语句）
        Src = (void *)18;  // （表达式续行/复合语句）
        v244 = 49;
        for ( i = 0; i < 3; ++i )  // 循环（遍历）
        {
          v176 = (int)*(&v242 + i);  // （表达式续行/复合语句）
          if ( sub_4842B0(v176, nullptr) != -1  // 条件判定
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, v176) != 0 )  // 虚调用 vt+1312
          {
            Block = nullptr;  // 临时缓冲指针清零
            v237 = 0;
            v238 = 0;
            v250 = 19;
            v246 = v176;
            sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 18, v235, 0, 0);  // 虚调用 vt+560
            v250 = -1;
            if ( Block != nullptr )  // 条件判定
              j__free(Block);  // （表达式续行/复合语句）
            Block = nullptr;  // 临时缓冲指针清零
            v237 = 0;
            v238 = 0;
          }
        }
      }
      // ── [段 13] 包 10 族（技能 12/16/13/52/14 的 14 号包装载器）—— ★ 每个都是一长串 sub_431230 参数压栈 ──
      //   sub_431230 = uint32 vector push_back（全工程 733 处）；包体由 vt+560 一次性发出
      if ( *(uint32_t *)(pArg1 + 6556) == 18 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8288) )  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
      //   12 号技能：+1140/+1160/+41A5E0 查表取参 → 包 10
      if ( *(uint32_t *)(pArg1 + 6556) == 19 )  // 判定 pArg1+6556 == 19（枪手大状态ID）
      {
        if ( *(uint8_t *)(pArg1 + 8324) != 0 )  // 判定 pArg1+8324 != 0（抱人模式字节）
        {
          if ( *(uint8_t *)(pArg1 + 8333) != 0 )  // 判定 pArg1+8333 != 0（保留槽F）
          {
            v177 = *(uint32_t *)(pArg1 + 112);  // 读 v177 = pArg1+112（默认共享组件/坐标宿主）
            if ( *(float *)(v177 + 24) < 0.0 && *(uint32_t *)(v177 + 192) == 4 )  // 条件判定
              (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 1, 0, 0, 0);  // 虚调用 vt+560
          }
        }
        else if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 否则条件分支
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
        }
      }
      //   16 号技能：同构；随后 14 号技能走「场景对象遍历」支（条件位 17 + vt+840==4 + vt+128<20 + vt+724==0）
      v178 = *(uint32_t *)(pArg1 + 6556);  // 读 v178 = pArg1+6556（枪手大状态ID）
      if ( (v178 == 0 || v178 == 11 || v178 == 8)  // 条件判定
        && sub_4842B0(12, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 12) != 0 )  // 虚调用 vt+1312
      {
        v179 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 12);  // 虚调用 vt+1160（取返回值）
        v242 = nullptr;  // v242 = 空指针
        Src = nullptr;  // 源缓冲指针清零
        v244 = 0;
        v250 = 20;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 12;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v180 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 12);  // 虚调用 vt+1140（取返回值）
        if ( v180 == -1 )  // 条件判定
          v180 = sub_41A5E0(v179 + 510);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
        v246 = sub_41A5E0(*(uint32_t *)(v179 + 316) + 14 * (v180 - 1));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 1;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, &v241, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( v242 != nullptr )  // 条件判定
          j__free(v242);  // （表达式续行/复合语句）
      }
      v181 = *(uint32_t *)(pArg1 + 6556);  // 读 v181 = pArg1+6556（枪手大状态ID）
      if ( (v181 == 0 || v181 == 11)  // 条件判定
        && sub_4842B0(16, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 16) != 0 )  // 虚调用 vt+1312
      {
        v182 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 16);  // 虚调用 vt+1160（取返回值）
        v242 = nullptr;  // v242 = 空指针
        Src = nullptr;  // 源缓冲指针清零
        v244 = 0;
        v250 = 21;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 16;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v183 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 16);  // 虚调用 vt+1140（取返回值）
        if ( v183 == -1 )  // 条件判定
          v183 = sub_41A5E0(v182 + 510);  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
        v246 = sub_41A5E0(*(uint32_t *)(v182 + 316) + 14 * (v183 - 1));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 1;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, &v241, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( v242 != nullptr )  // 条件判定
          j__free(v242);  // （表达式续行/复合语句）
      }
      v184 = *(uint32_t *)(pArg1 + 6556);  // 读 v184 = pArg1+6556（枪手大状态ID）
      if ( (v184 == 0 || v184 == 11 || v184 == 8)  // 条件判定
        && sub_4842B0(13, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 13) != 0 )  // 虚调用 vt+1312
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 13);  // 虚调用 vt+1160
        v242 = nullptr;  // v242 = 空指针
        Src = nullptr;  // 源缓冲指针清零
        v244 = 0;
        v250 = 22;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 13;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = sub_47E9D0(1);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 3;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 3;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, &v241, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( v242 != nullptr )  // 条件判定
          j__free(v242);  // （表达式续行/复合语句）
      }
      v185 = *(uint32_t *)(pArg1 + 6556);  // 读 v185 = pArg1+6556（枪手大状态ID）
      if ( (v185 == 0 || v185 == 11 || v185 == 8)  // 条件判定
        && sub_4842B0(52, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 52) != 0 )  // 虚调用 vt+1312
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 52);  // 虚调用 vt+1160
        v242 = nullptr;  // v242 = 空指针
        Src = nullptr;  // 源缓冲指针清零
        v244 = 0;
        v250 = 23;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 52;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = sub_47E9D0(0);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = sub_47E9D0(1);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 3;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 3;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, &v241, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( v242 != nullptr )  // 条件判定
          j__free(v242);  // （表达式续行/复合语句）
      }
      v186 = *(uint32_t *)(pArg1 + 6556);  // 读 v186 = pArg1+6556（枪手大状态ID）
      //   遍历命中者：vt+688 取其对象 → sub_42FC90 计数 → sub_4924C0 取帧 → sub_423970 取参 → sub_430C80 追加 → 包 20
      if ( (v186 == 0 || v186 == 11) && sub_4842B0(14, nullptr) != -1 )  // 条件判定
      {
        v187 = *(uint32_t *)(pArg1 + 116);  // 读 v187 = pArg1+116（观察者容器）
        v188 = *(uint32_t *)(v187 + 120);  // （表达式续行/复合语句）
        v189 = v187 + 116;  // （表达式续行/复合语句）
        v190 = v188 != 0 ? (*(uint32_t *)(v189 + 8) - v188) >> 2 : 0;  // （表达式续行/复合语句）
        v247 = v190;
        i = 0;
        if ( v190 > 0 )  // 条件判定
        {
          v191 = 0;
          while ( 1 )  // 循环
          {
            v192 = *(uint32_t *)(pArg1 + 116);  // 读 v192 = pArg1+116（观察者容器）
            v193 = *(uint32_t *)(v192 + 120);  // （表达式续行/复合语句）
            if ( v193 != 0 && v191 < (*(uint32_t *)(v192 + 124) - v193) >> 2 )  // 条件判定
              v194 = *(int **)(*(uint32_t *)(v192 + 120) + 4 * i);  // （表达式续行/复合语句）
            //   14 号技能收尾：vt+1312(14) 条件门 → sub_430C80 两次追加 vt+48/vt+52 坐标 → 包 20
            else  // 否则分支
              v194 = nullptr;  // v194 = 空指针
            if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v194 + 40))(v194, 17) != 0  // 条件判定
              && (*(int (/*thiscall*/ **)(int *))(*v194 + 840))(v194) == 4  // （上一表达式的参数/条件续行）
              && (*(int (/*thiscall*/ **)(int *))(*v194 + 128))(v194) < 20  // （上一表达式的参数/条件续行）
              && (*(uint8_t (/*thiscall*/ **)(int *))(*v194 + 724))(v194) == 0  // （上一表达式的参数/条件续行）
              && (uint8_t)sub_4E4630(v194) != 0 )  // （上一表达式的参数/条件续行）
            {
              v195 = *v194;  // （表达式续行/复合语句）
              v241 = 0.0;  // v241 = 0.0（浮点初值）
              v242 = nullptr;  // v242 = 空指针
              Src = nullptr;  // 源缓冲指针清零
              v244 = 0;
              v246 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v195 + 688))(v194) + 20);  // （表达式续行/复合语句）
              v196 = sub_42FC90(v246);  // sub_42FC90 —— 88B 元素计数（+44 组）
              v197 = (uint32_t *)sub_4924C0(v196 - 1);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
              if ( *v197 != 0 )  // 条件判定
              {
                Src = *(void **)(*v197 + 20);  // （表达式续行/复合语句）
                v198 = *v194;  // （表达式续行/复合语句）
                LODWORD(v241) = *(uint32_t *)(*v197 + 28) + v197[3];  // （表达式续行/复合语句）
                if ( (*(int (/*thiscall*/ **)(int *))(v198 + 152))(v194) == 0 )  // 条件判定
                  LODWORD(v241) = -LODWORD(v241) - (uint32_t)Src;  // （表达式续行/复合语句）
                v199 = (*(int (/*thiscall*/ **)(int *))(*v194 + 120))(v194);  // （表达式续行/复合语句）
                v200 = *v194;  // （表达式续行/复合语句）
                LODWORD(v241) += v199;  // （表达式续行/复合语句）
                v242 = (void *)((*(int (/*thiscall*/ **)(int *))(v200 + 448))(v194) - 20);  // （表达式续行/复合语句）
                v244 = (*(int (/*thiscall*/ **)(int *))(*v194 + 432))(v194) + 40;  // （表达式续行/复合语句）
                if ( (uint8_t)sub_423970(pArg1, &v241) != 0 )  // 条件判定
                  break;  // 跳出本分支
              }
            }
            v191 = ++i;  // （表达式续行/复合语句）
            if ( i >= v247 )  // 条件判定
              goto LABEL_399;  // 跳转合流点 LABEL_399
          }
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 14) != 0 )  // 虚调用 vt+1312
          {
            v242 = nullptr;  // v242 = 空指针
            Src = nullptr;  // 源缓冲指针清零
            v244 = 0;
            v250 = 24;
            v246 = 0;
            sub_430C80(nullptr, 1, (int)&v246);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
            *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*v194 + 48))(v194));  // （表达式续行/复合语句）
            v201 = (char *)Src;  // （表达式续行/复合语句）
            if ( v242 == nullptr )  // 条件判定
              goto LABEL_392;  // 跳转合流点 LABEL_392
            if ( ((uint8_t *)Src - (uint8_t *)v242) >> 2 < (unsigned int)((v244 - (int)v242) >> 2) )  // 条件判定
            {
              *(float *)Src = *(float *)&v247;  // （表达式续行/复合语句）
              Src = v201 + 4;  // （表达式续行/复合语句）
            }
            else  // 否则分支
            {
LABEL_392:  // 标签 LABEL_392：合流点
              sub_430C80(Src, 1, (int)&v247);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
            }
            *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *))(*v194 + 52))(v194));  // （表达式续行/复合语句）
            v202 = (char *)Src;  // （表达式续行/复合语句）
            if ( v242 != nullptr && ((uint8_t *)Src - (uint8_t *)v242) >> 2 < (unsigned int)((v244 - (int)v242) >> 2) )  // 条件判定
            {
              *(float *)Src = *(float *)&v247;  // （表达式续行/复合语句）
              Src = v202 + 4;  // （表达式续行/复合语句）
            }
            else  // 否则分支
            {
              sub_430C80(Src, 1, (int)&v247);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
            }
            (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 20, &v241, 0, 0);  // 虚调用 vt+560
            v250 = -1;
            if ( v242 != nullptr )  // 条件判定
              j__free(v242);  // （表达式续行/复合语句）
          }
        }
      }
// ── [段 14] LABEL_399：20 号态维护（投掷物飞行/落地判定） ──
//   +8344==0：+8356 目标存活则按 +170 决定 ++ 包 20（[1,0xFFFF,0xFFFF]）或包 0 退出
LABEL_399:  // 标签 LABEL_399：合流点
      if ( *(uint32_t *)(pArg1 + 6556) != 20 )  // 判定 pArg1+6556 != 20（枪手大状态ID）
        goto LABEL_410;  // 跳转合流点 LABEL_410
      if ( *(uint32_t *)(pArg1 + 8344) == 0 )  // 判定 pArg1+8344 == 0（骑乘模式）
      {
        pObj6 = *(uint32_t *)(pArg1 + 8356);  // 读 pObj6 = pArg1+8356（抱人目标对象）
        if ( pObj6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 724))(pObj6) == 0 )  // 条件判定
        {
          if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 条件判定
          {
            Block = nullptr;  // 临时缓冲指针清零
            v237 = 0;
            v238 = 0;
            v250 = 25;
            v246 = 1;
            sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
            v246 = 0xFFFF;
            sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
            v246 = 0xFFFF;
            sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 20, v235, 0, 0);  // 虚调用 vt+560
            v250 = -1;
            sub_5E5260(v235);  // sub_5E5260 —— 清理临时缓冲
          }
          goto LABEL_410;  // 跳转合流点 LABEL_410
        }
LABEL_407:  // 标签 LABEL_407：合流点
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
        goto LABEL_410;  // 跳转合流点 LABEL_410
      }
      //   +8344!=0：+170 且 +8348 < +8352 时 ++ 包 20（[1,0xFFFF,0xFFFF]）；否则包 0
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) == 0 )  // 条件判定
        goto LABEL_410;  // 跳转合流点 LABEL_410
      if ( *(uint32_t *)(pArg1 + 8348) >= *(uint32_t *)(pArg1 + 8352) )  // 条件判定
        goto LABEL_407;  // 跳转合流点 LABEL_407
      Block = nullptr;  // 临时缓冲指针清零
      v237 = 0;
      v238 = 0;
      v250 = 26;
      v246 = 1;
      sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
      v246 = 0xFFFF;
      sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
      v246 = 0xFFFF;
      sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
      (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 20, v235, 0, 0);  // 虚调用 vt+560
      v250 = -1;
      if ( Block != nullptr )  // 条件判定
        j__free(Block);  // （表达式续行/复合语句）
// ── [段 15] LABEL_410：★ 其余技能/状态包检查表（6/17/19/22/8/15/40/42/46/3/24/54/26 …）──
LABEL_410:  // 标签 LABEL_410：合流点
      //   6 态 + 双子表计数 → 包 21（17 号技能）；0/11/8 → 包 22（19 号技能）
      if ( *(uint32_t *)(pArg1 + 6556) == 6  // 条件判定
        && *(uint32_t *)(pArg1 + 6892) == 1  // （上一表达式的参数/条件续行）
        && *(uint32_t *)(pArg1 + 6896) < *(uint32_t *)(pArg1 + 6900)  // （上一表达式的参数/条件续行）
        && sub_4842B0(17, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 17) != 0 )  // 虚调用 vt+1312
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 21, 0, 0, 0);  // 虚调用 vt+560
      }
      //   22 态退出 +170；0/11 循环 unk_7959D0..7959F8 表（8 项）→ 包 14（*v205 号技能）
      v204 = *(uint32_t *)(pArg1 + 6556);  // 读 v204 = pArg1+6556（枪手大状态ID）
      if ( (v204 == 0 || v204 == 11 || v204 == 8)  // 条件判定
        && sub_4842B0(19, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 19) != 0 )  // 虚调用 vt+1312
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 22, 0, 0, 0);  // 虚调用 vt+560
      }
      if ( *(uint32_t *)(pArg1 + 6556) == 22 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 条件判定
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
      v205 = (int *)&unk_7959D0;  // （表达式续行/复合语句）
      do
      {
        v206 = *(uint32_t *)(pArg1 + 6556);  // 读 v206 = pArg1+6556（枪手大状态ID）
        if ( (v206 == 0 || v206 == 11)  // 条件判定
          && sub_4842B0(*v205, nullptr) != -1  // （上一表达式的参数/条件续行）
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, *v205) != 0 )  // 虚调用 vt+1312
        {
          Block = nullptr;  // 临时缓冲指针清零
          v237 = 0;
          v238 = 0;
          v246 = *v205;  // （表达式续行/复合语句）
          v250 = 27;
          sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 14, v235, 0, 0);  // 虚调用 vt+560
          v250 = -1;
          if ( Block != nullptr )  // 条件判定
            j__free(Block);  // （表达式续行/复合语句）
          Block = nullptr;  // 临时缓冲指针清零
          v237 = 0;
          v238 = 0;
        }
        ++v205;  // 自增
      }
      while ( (int)v205 < (int)&dword_7959F8 );  // 循环
      //   0/11 → 包 17（40 号技能，参数含 +1140(40)/+1160(40) 两级查表）
      v207 = *(uint32_t *)(pArg1 + 6556);  // 读 v207 = pArg1+6556（枪手大状态ID）
      if ( (v207 == 0 || v207 == 11)  // 条件判定
        && sub_4842B0(40, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 40) != 0 )  // 虚调用 vt+1312
      {
        v242 = nullptr;  // v242 = 空指针
        Src = nullptr;  // 源缓冲指针清零
        v244 = 0;
        v250 = 28;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 40;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 40));  // 虚调用 vt+1140
        v208 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 40);  // 虚调用 vt+1160（取返回值）
        v209 = v208;
        v210 = *(float *)&v247 == NAN ? sub_41A5E0(v208 + 510) : v247;  // （表达式续行/复合语句）
        v246 = sub_41A5E0(*(uint32_t *)(v209 + 316) + 14 * (v210 - 1));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 40, 1);  // 虚调用 vt+1160
        v246 = sub_47E9D0(v226);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v226 = 0;
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 17, &v241, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( v242 != nullptr )  // 条件判定
          j__free(v242);  // （表达式续行/复合语句）
      }
      //   0/11 → 包 17（42 号技能，同构）
      v211 = *(uint32_t *)(pArg1 + 6556);  // 读 v211 = pArg1+6556（枪手大状态ID）
      if ( (v211 == 0 || v211 == 11)  // 条件判定
        && sub_4842B0(42, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 42) != 0 )  // 虚调用 vt+1312
      {
        v242 = nullptr;  // v242 = 空指针
        Src = nullptr;  // 源缓冲指针清零
        v244 = 0;
        v250 = 29;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 42;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        *(float *)&v247 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 42));  // 虚调用 vt+1140
        v212 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 42);  // 虚调用 vt+1160（取返回值）
        v213 = v212;
        v214 = *(float *)&v247 == NAN ? sub_41A5E0(v212 + 510) : v247;  // （表达式续行/复合语句）
        v246 = sub_41A5E0(*(uint32_t *)(v213 + 316) + 14 * (v214 - 1));  // sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pArg1 + 1160))(pArg1, 42, 0);  // 虚调用 vt+1160
        v246 = sub_47E9D0(v226);  // sub_47E9D0 —— 收招/结束例程
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 4;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, float *, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 17, &v241, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( v242 != nullptr )  // 条件判定
          j__free(v242);  // （表达式续行/复合语句）
      }
      //   0/11/8 → 包 25（46 号技能，参数 [3,46]）
      v215 = *(uint32_t *)(pArg1 + 6556);  // 读 v215 = pArg1+6556（枪手大状态ID）
      if ( (v215 == 0 || v215 == 11 || v215 == 8)  // 条件判定
        && sub_4842B0(46, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 46) != 0 )  // 虚调用 vt+1312
      {
        Block = nullptr;  // 临时缓冲指针清零
        v237 = 0;
        v238 = 0;
        v250 = 30;
        v246 = 3;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 46;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 25, v235, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( Block != nullptr )  // 条件判定
          j__free(Block);  // （表达式续行/复合语句）
      }
      //   0/11/8 → 包 24（3 号技能，参数 [0]）
      v216 = *(uint32_t *)(pArg1 + 6556);  // 读 v216 = pArg1+6556（枪手大状态ID）
      if ( (v216 == 0 || v216 == 11 || v216 == 8)  // 条件判定
        && sub_4842B0(3, nullptr) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 3) != 0 )  // 虚调用 vt+1312
      {
        Block = nullptr;  // 临时缓冲指针清零
        v237 = 0;
        v238 = 0;
        v250 = 31;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 24, v235, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( Block != nullptr )  // 条件判定
          j__free(Block);  // （表达式续行/复合语句）
      }
      //   24 态退出：+8472 表参 1 且 +170 → 包 0；表参 0 且动作 +148>=8 → 包 0
      if ( *(uint32_t *)(pArg1 + 6556) == 24 )  // 判定 pArg1+6556 == 24（枪手大状态ID）
      {
        v217 = *(uint32_t *)(pArg1 + 8472);  // 读 v217 = pArg1+8472（收束标志）
        if ( v217 != 0 )  // 条件判定
        {
          if ( v217 == 1 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 条件判定
            goto LABEL_472;  // 跳转合流点 LABEL_472
        }
        else if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 8 )  // 否则条件分支
        {
LABEL_472:  // 标签 LABEL_472：合流点
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
        }
      }
      //   0/11 → 包 26（54 号技能，载荷 +8116——即把 +8116 结构体作为门参数传入 sub_4842B0）
      v218 = *(uint32_t *)(pArg1 + 6556);  // 读 v218 = pArg1+6556（枪手大状态ID）
      if ( (v218 == 0 || v218 == 11)  // 条件判定
        && sub_4842B0(54, (void *)(pArg1 + 8116)) != -1  // （上一表达式的参数/条件续行）
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 54) != 0 )  // 虚调用 vt+1312
      {
        Block = nullptr;  // 临时缓冲指针清零
        v237 = 0;
        v238 = 0;
        v250 = 32;
        v246 = 0;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        v246 = 54;
        sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 26, v235, 0, 0);  // 虚调用 vt+560
        v250 = -1;
        if ( Block != nullptr )  // 条件判定
          j__free(Block);  // （表达式续行/复合语句）
      }
      //   26 态：+8496==1 且 +170 → 包 0；否则动作 +148==1 且 sub_4BFC10(+8116)==0 时 ++ 包 26（含节拍-帧差）
      //   并 sub_4BA730(2,4,0,0) 起魔能充能——本 case 是全函数唯一 return 出口（case 0x16 尾另有一处）
      if ( *(uint32_t *)(pArg1 + 6556) == 26 )  // 判定 pArg1+6556 == 26（枪手大状态ID）
      {
        v219 = *(uint32_t *)(pArg1 + 8496);  // 读 v219 = pArg1+8496（魔能充能态）
        if ( v219 != 0 )  // 条件判定
        {
          if ( v219 == 1 && *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )  // 条件判定
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
        }
        else if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) == 1 && (uint8_t)sub_4BFC10(pArg1 + 8116) == 0 )  // 否则条件分支
        {
          Block = nullptr;  // 临时缓冲指针清零
          v237 = 0;
          v238 = 0;
          v250 = 33;
          v246 = 1;
          sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
          v246 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
          v246 -= sub_491C70(1);  // （表达式续行/复合语句）
          sub_431230(&v246);  // sub_431230 —— uint32 vector push_back
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 26, v235, 0, 0);  // 虚调用 vt+560
          sub_4BA730(2, 4, 0, 0);  // sub_4BA730 —— 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_CHARGE/ENERGY_CHARGE_END）
          if ( Block != nullptr )  // 条件判定
            j__free(Block);  // （表达式续行/复合语句）
        }
      }
      return;  // 返回（本帧结束）
    // ── [段 16] case 0x17：★ 上段挥击（FT_UPPER_SWING / SWING_UPPER）—— 200ms 起手 ──
    //   vt+876 设位移(800,800,-4000) → +8440 记时刻(+60ms 偏移) → vt+212 播双动画名
    case 0x17:  // case 0x17 分派：★ 上段挥击（FT_UPPER_SWING / SWING_UPPER）—— 200ms 起手
      if ( *(uint8_t *)(pArg1 + 8437) != 0 )  // 判定 pArg1+8437 != 0（保留槽J）
        goto LABEL_185;  // 跳转合流点 LABEL_185
      if ( sub_699000(pArg1 + 6560) >= 200 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)pArg1 + 876))(  // 虚调用 vt+876
          pArg1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          800,  // （上一表达式的参数/条件续行）
          800,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          -4000,  // （上一表达式的参数/条件续行）
          1);  // （上一表达式的参数/条件续行）
        v121 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
        v122 = *(uint32_t *)pArg1;  // v122 = *pArg1（对象首字段=虚表）
        *(uint32_t *)(pArg1 + 8440) = v121 - 60;  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v122 + 212))(pArg1, "FT_UPPER_SWING", -1, 0, 0);  // （表达式续行/复合语句）
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212
          pArg1,  // （上一表达式的参数/条件续行）
          "SWING_UPPER",  // （上一表达式的参数/条件续行）
          -1,  // （上一表达式的参数/条件续行）
          0,  // （上一表达式的参数/条件续行）
          0);  // （上一表达式的参数/条件续行）
        *(uint8_t *)(pArg1 + 8437) = 1;  // 写 pArg1+8437 = 1（保留槽J）
      }
      //   350ms 内且距 +8440 满 60ms：取 dword_8F8270[vt+924(2)] 对象 → 依朝向 ±40 设位 → vt+40/vt+12/vt+92 → sub_4600B0
      if ( *(uint8_t *)(pArg1 + 8437) != 0 )  // 判定 pArg1+8437 != 0（保留槽J）
      {
LABEL_185:  // 标签 LABEL_185：合流点
        if ( sub_699000(pArg1 + 6560) <= 350 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8440) + 60 )  // 【clock_now(clk)】
        {
          v123 = (int *)dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 924))(pArg1, 2)];  // 虚调用 vt+924（取返回值）
          v124 = *(uint32_t *)pArg1;  // v124 = *pArg1（对象首字段=虚表）
          v246 = (int)v123;  // （表达式续行/复合语句）
          v125 = (*(int (/*thiscall*/ **)(int))(v124 + 152))(pArg1);  // （表达式续行/复合语句）
          v126 = *(uint32_t *)pArg1;  // v126 = *pArg1（对象首字段=虚表）
          v249 = v125 == 0;  // （表达式续行/复合语句）
          v247 = *v123;  // （表达式续行/复合语句）
          v127 = (*(int (/*thiscall*/ **)(int))(v126 + 128))(pArg1);  // （表达式续行/复合语句）
          v128 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v127);  // 虚调用 vt+124（取返回值）
          v129 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v128);  // 虚调用 vt+120（取返回值）
          (*(void (/*thiscall*/ **)(int *, int))(v247 + 40))(v123, v129);  // （表达式续行/复合语句）
          *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v123 + 28))(v123) + 84) = v249;  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*v123 + 12))(v123, 0);  // （表达式续行/复合语句）
          (*(void (/*thiscall*/ **)(int *, float *))(*v123 + 92))(v123, &v241);  // （表达式续行/复合语句）
          v130 = *(void **)(pArg1 + 116);  // （表达式续行/复合语句）
          v250 = 7;
          sub_4600B0(v130, 2, 0, (int)&v241);  // sub_4600B0 —— 演播层注册(槽号)
          *(uint32_t *)(pArg1 + 8440) += 60;  // 字段 pArg1+8440 += 60
          v250 = -1;
          sub_5E5260(&v241);  // sub_5E5260 —— 清理临时缓冲
        }
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 17] case 0x18：★ 燃烧抓取爆炸（GrabExplosion1/2/3.ani + BURN_ATK）—— +8472==1 起 ──
    //   先给 +8300 目标施加状态 9；目标动作 +148==8 时走爆炸支（sub_4AECE0(9) + vt+876 位移 + vt+896 + vt+888）
    case 0x18:  // case 0x18 分派：★ 燃烧抓取爆炸（GrabExplosion1/2/3.ani + BURN_ATK）—— +8472==1 起
      if ( *(uint32_t *)(pArg1 + 8472) == 1 )  // 判定 pArg1+8472 == 1（收束标志）
      {
        pObj = *(uint32_t *)(pArg1 + 8300);  // 读 pObj = pArg1+8300（被擒/被抱对象）
        if ( pObj != 0  // 条件判定
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) != 9  // （上一表达式的参数/条件续行）
          && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 840))(*(uint32_t *)(pArg1 + 8300)) != 5  // （上一表达式的参数/条件续行）
          && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 308))(*(uint32_t *)(pArg1 + 8300)) != 0 )  // （上一表达式的参数/条件续行）
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(pArg1 + 8300) + 560))(  // （表达式续行/复合语句）
            *(uint32_t *)(pArg1 + 8300),  // （上一表达式的参数/条件续行）
            9,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            2,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8300) + 564))(*(uint32_t *)(pArg1 + 8300));  // （表达式续行/复合语句）
        }
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) == 8 )  // 条件判定
        {
          pObj15 = *(uint32_t *)(pArg1 + 8300);  // 读 pObj15 = pArg1+8300（被擒/被抱对象）
          if ( pObj15 == 0 || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj15 + 840))(pObj15) == 5 )  // 条件判定
          {
            if ( *(uint32_t *)(pArg1 + 8300) != 0 )  // 判定 pArg1+8300 != 0（被擒/被抱对象）
            {
              pObj2 = *(uint32_t *)(pArg1 + 8480);  // 读 pObj2 = pArg1+8480（攻击挂接对象）
              *(uint32_t *)(pArg1 + 8300) = 0;  // 写 pArg1+8300 = 0（被擒/被抱对象）
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);  // （表达式续行/复合语句）
            }
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560
          }
          else  // 否则分支
          {
            sub_4AECE0(9);
            (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)pArg1 + 876))(  // 虚调用 vt+876
              pArg1,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              1000,  // （上一表达式的参数/条件续行）
              1000,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              -10000,  // （上一表达式的参数/条件续行）
              1);  // （上一表达式的参数/条件续行）
            v133 = *(uint32_t *)pArg1;  // v133 = *pArg1（对象首字段=虚表）
            v134 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 152))(pArg1, 4);  // 虚调用 vt+152（取返回值）
            (*(void (/*thiscall*/ **)(int, int))(v133 + 896))(pArg1, v134);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 888))(pArg1, 1, 3, 1000, 1000);  // 虚调用 vt+888
            //   爆炸动画三件懒加载（+8484/+8488/+8492）→ vt+204 逐件挂载 → vt+1172 查 1 号表名 → vt+212 播报
            if ( *(uint32_t *)(pArg1 + 8484) == 0 )  // 判定 pArg1+8484 == 0
            {
              v246 = sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
              v250 = 8;
              if ( v246 != 0 )  // 条件判定
              {
                if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // 判定 pArg1+384 < 0x10u（动画池容量(SSO)）
                  v135 = sub_431920(pArg1 + 108, (char)"Effect/Animation/GrabExplosion1.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                else  // 否则分支
                  v135 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)"Effect/Animation/GrabExplosion1.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
              }
              else  // 否则分支
              {
                v135 = 0;
              }
              *(uint32_t *)(pArg1 + 8484) = v135;  // 写 pArg1+8484 = v135
              v246 = sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
              v250 = 9;
              if ( v246 != 0 )  // 条件判定
              {
                if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // 判定 pArg1+384 < 0x10u（动画池容量(SSO)）
                  v136 = sub_431920(pArg1 + 108, (char)"Effect/Animation/GrabExplosion2.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                else  // 否则分支
                  v136 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)"Effect/Animation/GrabExplosion2.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
              }
              else  // 否则分支
              {
                v136 = 0;
              }
              *(uint32_t *)(pArg1 + 8488) = v136;  // 写 pArg1+8488 = v136
              v246 = sub_42FCB0(228);  // sub_42FCB0 —— CRT 一次性初始化
              v250 = 10;
              if ( v246 != 0 )  // 条件判定
              {
                if ( *(uint32_t *)(pArg1 + 384) < 0x10u )  // 判定 pArg1+384 < 0x10u（动画池容量(SSO)）
                {
                  v250 = -1;
                  *(uint32_t *)(pArg1 + 8492) = sub_431920(pArg1 + 108, (char)"Effect/Animation/GrabExplosion3.ani", 1);  // （表达式续行/复合语句）
                }
                else  // 否则分支
                {
                  v137 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)"Effect/Animation/GrabExplosion3.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
                  v250 = -1;
                  *(uint32_t *)(pArg1 + 8492) = v137;  // 写 pArg1+8492 = v137
                }
              }
              else  // 否则分支
              {
                v250 = -1;
                *(uint32_t *)(pArg1 + 8492) = 0;  // 写 pArg1+8492 = 0
              }
            }
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 虚调用 vt+204
              pArg1,  // （上一表达式的参数/条件续行）
              1,  // （上一表达式的参数/条件续行）
              *(uint32_t *)(pArg1 + 8484),  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 虚调用 vt+204
              pArg1,  // （上一表达式的参数/条件续行）
              2,  // （上一表达式的参数/条件续行）
              *(uint32_t *)(pArg1 + 8488),  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(  // 虚调用 vt+204
              pArg1,  // （上一表达式的参数/条件续行）
              2,  // （上一表达式的参数/条件续行）
              *(uint32_t *)(pArg1 + 8492),  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0,  // （上一表达式的参数/条件续行）
              0);  // （上一表达式的参数/条件续行）
            v246 = *(uint32_t *)pArg1;  // v246 = *pArg1（对象首字段=虚表）
            v138 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(v246 + 1172))(pArg1, 1, -1, 0, 0);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, int))(v246 + 212))(pArg1, v138);  // （表达式续行/复合语句）
          }
        }
        //   动作 +148>=12 且 +8477 未置：vt+212 播 BURN_ATK
        if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 12 && *(uint8_t *)(pArg1 + 8477) == 0 )  // 条件判定
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212
            pArg1,  // （上一表达式的参数/条件续行）
            "BURN_ATK",  // （上一表达式的参数/条件续行）
            -1,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0);  // （上一表达式的参数/条件续行）
          *(uint8_t *)(pArg1 + 8477) = 1;  // 写 pArg1+8477 = 1（保留槽K）
        }
        //   动作 +148==13 且 +8476 未置：★ 终段——按朝向 ±59 算落点 → sub_605840 打包 → vt+580(21014) 发伤害包
        //   → vt+1160(3, this, -1) 关联自身 → sub_47DCD0(3,3) → sub_5E6640 收尾 → +8476 置位
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) == 13 && *(uint8_t *)(pArg1 + 8476) == 0 )  // 条件判定
        {
          v53 = *(uint32_t *)(pArg1 + 8300) == 0;  // （表达式续行/复合语句）
          i = 0;
          *(float *)&v247 = 0.0;  // （表达式续行/复合语句）
          if ( !v53 )  // 条件判定
          {
            v140 = *(uint32_t *)pArg1;  // v140 = *pArg1（对象首字段=虚表）
            v229 = 0.0;  // v229 = 0.0（浮点初值）
            v230 = 0.0;  // v230 = 0.0（浮点初值）
            v231 = 0.0;  // v231 = 0.0（浮点初值）
            v232 = 0;
            v233 = 0;
            v234 = 0;
            if ( (*(int (/*thiscall*/ **)(int))(v140 + 152))(pArg1) != 0 )  // 条件判定
              v141 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 59;  // 虚调用 vt+120（取返回值）
            else  // 否则分支
              v141 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 59;  // 虚调用 vt+120（取返回值）
            v247 = v141;
            v142 = (double)v141;  // （表达式续行/复合语句）
            v143 = *(uint32_t *)pArg1;  // v143 = *pArg1（对象首字段=虚表）
            v229 = v142;
            v144 = (*(int (/*thiscall*/ **)(int))(v143 + 124))(pArg1);  // （表达式续行/复合语句）
            v145 = *(uint32_t *)pArg1;  // v145 = *pArg1（对象首字段=虚表）
            v246 = v144 - 1;  // （表达式续行/复合语句）
            v230 = (float)(v144 - 1);  // （表达式续行/复合语句）
            v146 = (*(int (/*thiscall*/ **)(int))(v145 + 128))(pArg1);  // （表达式续行/复合语句）
            v147 = *(uint32_t *)(pArg1 + 8300);  // 读 v147 = pArg1+8300（被擒/被抱对象）
            v246 = v146 + 94;  // （表达式续行/复合语句）
            v231 = (float)(v146 + 94);  // （表达式续行/复合语句）
            *(float *)&v247 = COERCE_FLOAT(sub_605840(&i, v147, &v229, 1));  // （表达式续行/复合语句）
          }
          v148 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 388))(pArg1);  // 虚调用 vt+388（取返回值）
          v246 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1140))(pArg1);  // 虚调用 vt+1140（取返回值）
          v149 = (char *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1160))(pArg1);  // 虚调用 vt+1160（取返回值）
          v150 = sub_47EFD0(v149, COERCE_FLOAT(1), v246, v148, v148, 0);  // sub_47EFD0 —— 攻击上下文计算
          (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, int, int))(*(uint32_t *)pArg1 + 580))(  // 虚调用 vt+580
            pArg1,  // （上一表达式的参数/条件续行）
            21014,  // （上一表达式的参数/条件续行）
            v150,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            59,  // （上一表达式的参数/条件续行）
            -1,  // （上一表达式的参数/条件续行）
            94,  // （上一表达式的参数/条件续行）
            4,  // （上一表达式的参数/条件续行）
            0,  // （上一表达式的参数/条件续行）
            i,  // （上一表达式的参数/条件续行）
            v247);  // （上一表达式的参数/条件续行）
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 3, pArg1, -1);  // 虚调用 vt+1160
          sub_47DCD0(3, 3);  // sub_47DCD0 —— 震动/资源档位设置
          sub_5E6640(pArg1);
          *(uint8_t *)(pArg1 + 8476) = 1;  // 写 pArg1+8476 = 1（收束门字节）
        }
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 18] case 0x1A：★ 濒死/倒地态（+8496 分型 + +8508 三相位）──
    //   +8496==1：按动画横向速度 fabs(+112 的 +16)>=20.0 且距 +8504 满 200ms 时周期性抖屏（同段 6 的 8F8270 取位模式）
    case 0x1A:  // 子状态 case 0x1A 分派：★ 燃烧抓取爆炸（GrabExplosion1/2/3.ani + BURN_ATK）—— +8472==1 起
      v151 = *(uint32_t *)(pArg1 + 8496);  // 读 v151 = pArg1+8496（魔能充能态）
      if ( v151 != 0 )  // 条件判定
      {
        if ( v151 == 1 )  // 条件判定
        {
          if ( fabs(*(float *)(*(uint32_t *)(pArg1 + 112) + 16)) >= 20.0  // 条件判定
            && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8504) + 200 )  // 【clock_now(clk)】
          {
            pObj23 = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 924))(pArg1, 2)];  // 虚调用 vt+924（取返回值）
            v159 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);  // 虚调用 vt+152（取返回值）
            v249 = v159 == 0;  // （表达式续行/复合语句）
            if ( v159 != 0 )  // 条件判定
              v160 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 20;  // 虚调用 vt+120（取返回值）
            else  // 否则分支
              v160 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 20;  // 虚调用 vt+120（取返回值）
            v161 = *(uint32_t *)pObj23;  // （表达式续行/复合语句）
            v247 = v160;
            v162 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚调用 vt+128（取返回值）
            v163 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v162);  // 虚调用 vt+124（取返回值）
            (*(void (/*thiscall*/ **)(int, int, int))(v161 + 40))(pObj23, v247, v163);  // （表达式续行/复合语句）
            *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj23 + 28))(pObj23) + 84) = v249;  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj23 + 12))(pObj23, 0);  // （表达式续行/复合语句）
            (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)pObj23 + 92))(pObj23, &v241);  // （表达式续行/复合语句）
            v164 = *(void **)(pArg1 + 116);  // （表达式续行/复合语句）
            v250 = 11;
            sub_4600B0(v164, 2, 0, (int)&v241);  // sub_4600B0 —— 演播层注册(槽号)
            *(uint32_t *)(pArg1 + 8504) = sub_699000(pArg1 + 6560);  // （表达式续行/复合语句）
            v250 = -1;
            sub_5E5260(&v241);  // sub_5E5260 —— 清理临时缓冲
          }
          //   +8500 >= dword_9B9348（全局阈值）：自身施加变色 0xFF00FFFF + 状态 1（濒死演出）
          if ( *(uint32_t *)(pArg1 + 8500) >= dword_9B9348 )  // 判定 pArg1+8500 >= dword_9B9348（充能计时）
          {
            if ( *(uint8_t *)(pArg1 + 248) == 0 || *(uint32_t *)(pArg1 + 252) != -16776961 )  // 条件判定
              (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 284))(pArg1, 1, -16776961, 1, 2);  // 虚调用 vt+284
            if ( *(uint32_t *)(pArg1 + 644) != 1 )  // 判定 pArg1+644 != 1（帧时刻覆盖值）
              (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 612))(pArg1, 1, 1);  // 虚调用 vt+612
          }
        }
      }
      //   +8496==0 支：动画 +148==1 且 sub_4910C0（暂停位）==0 时 sub_4939E0 冻帧；横向速度 <5.0 归零
      else  // 否则分支
      {
        v152 = *(uint32_t *)(pArg1 + 120);  // 读 v152 = pArg1+120（动画对象）
        if ( *(uint32_t *)(v152 + 148) == 1 && sub_4910C0(*(uint32_t *)(pArg1 + 120)) == 0 )  // 条件判定
          sub_4939E0(v152, 1);  // sub_4939E0 —— 播放/暂停级联（递归子链 +204）
        v153 = *(uint32_t *)(pArg1 + 112);  // 读 v153 = pArg1+112（默认共享组件/坐标宿主）
        if ( fabs(*(float *)(v153 + 16)) < 5.0 )  // 条件判定
          *(uint32_t *)(v153 + 16) = 0;  // （表达式续行/复合语句）
        //   +8508 三相：0 → sub_4BA730(0,4,11,-39) 起充能变 +1；1 → 到点后可转 2；2 → sub_42B420(255,220) 插值做呼吸闪
        v154 = *(uint32_t *)(pArg1 + 8508);  // 读 v154 = pArg1+8508（保留槽M）
        if ( v154 != 0 )  // 条件判定
        {
          if ( v154 == 1 )  // 条件判定
          {
            v155 = sub_491C70(1) + dword_9B9348;  // （表达式续行/复合语句）
            if ( sub_699000(pArg1 + 6560) >= v155 )  // 【clock_now(clk)】
            {
              sub_4BA730(1, 4, 11, -39);  // sub_4BA730 —— 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_CHARGE/ENERGY_CHARGE_END）
              *(uint32_t *)(pArg1 + 8508) = 2;  // 写 pArg1+8508 = 2（保留槽M）
            }
          }
          else if ( v154 == 2 )  // 否则条件分支
          {
            v156 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
            v157 = sub_42B420(255, 220, v156, 100);  // sub_42B420 —— 往返插值（三角波）
            (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 252))(pArg1, 0, v157);  // 虚调用 vt+252
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 252))(pArg1, 1, v157);  // 虚调用 vt+252
          }
        }
        //   兜底：动作 +148>=1 时起充能并置 +8508=1
        else if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )  // 否则条件分支
        {
          sub_4BA730(0, 4, 11, -39);  // sub_4BA730 —— 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_CHARGE/ENERGY_CHARGE_END）
          *(uint32_t *)(pArg1 + 8508) = 1;  // 写 pArg1+8508 = 1（保留槽M）
        }
      }
      goto LABEL_254;  // 跳转合流点 LABEL_254
    // ── [段 19] default：无操作，直接 goto LABEL_254 走本帧通用尾 ──
    default:  // 未列出的值 → 兜底
      goto LABEL_254;  // 跳转合流点 LABEL_254
  }
}

