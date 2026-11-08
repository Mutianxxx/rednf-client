// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_5F10C0_sub_5F10C0.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x5F10C0）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 1673 行；字符串证据 5 条；外调 6 个
//   串: "R_SM_MOANING_LOOP"
//   串: "Effect/Animation/GuardDust.ani"
//   串: "Effect/Animation/HardAttackFullCharge2.ani"
//   串: "Effect/Animation/HardAttackFullCharge1.ani"
//   串: "GHOSTSLASH_CHARGE_END"
//   调: sub_5F10C0 sub_4B7430 sub_49C620 sub_699000 sub_47E9D0 sub_425100
//   case 分支地图（共 10 处）:
//     L239  case 0xA:
//     L327  case 0xF:
//     L392  case 0x10:
//     L501  case 0x11:
//     L506  case 0x12:
//     L1311  case 0x13:
//     L1339  case 0x14:
//     L1403  case 0x15:
//     L1445  case 0x16:
//     L1586  case 0x17:
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x5F10C0 sub_5F10C0  size=10468
// ------------------------------------------------------------
void /*usercall*/ sub_5F10C0(int pArg1@<ecx>, double fArg2@<st0>)
{
  int pObj4; // ecx
  int v4; // edx
  int v5; // edi
  float *v6; // edi
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  float v12; // edi
  int v13; // eax
  int v14; // eax
  uint32_t *v15; // edi
  void *v16; // eax
  int v17; // edx
  int v18; // ecx
  int v19; // edi
  int pObj7; // edi
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // ecx
  int v25; // edi
  int pObj; // edi
  int v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edi
  int v32; // eax
  int v33; // edi
  void **v34; // edi
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // edx
  int v39; // eax
  int v40; // eax
  int pObj2; // edi
  void *v42; // ecx
  bool v43; // cc
  int v44; // eax
  int v45; // edi
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int v51; // edx
  int v52; // edi
  int v53; // eax
  int v54; // eax
  int v55; // eax
  void *v56; // eax
  int v57; // edx
  int v58; // ecx
  int v59; // eax
  int v60; // eax
  int pObj9; // edi
  int v62; // edi
  unsigned int j; // edi
  int v64; // eax
  int pObj10; // ecx
  int v66; // eax
  int pObj3; // ecx
  int v68; // eax
  int v69; // eax
  int v70; // edx
  int v71; // eax
  int v72; // eax
  int v73; // edx
  char *v74; // edi
  int v75; // eax
  int v76; // edx
  bool v77; // zf
  int v78; // eax
  int v79; // eax
  int v80; // edx
  int v81; // eax
  int v82; // eax
  int v83; // edx
  int v84; // eax
  int v85; // eax
  uint32_t *pMem; // eax
  int *v87; // eax
  int v88; // edx
  uint32_t *v89; // edi
  int v90; // eax
  int v91; // edx
  int v92; // ecx
  int v93; // edi
  int pObj6; // edi
  int v95; // ecx
  int v96; // edx
  int v97; // eax
  int v98; // ecx
  int v99; // edi
  int pObj11; // edi
  int v101; // ecx
  int v102; // edx
  int v103; // eax
  int v104; // eax
  int v105; // edi
  int v106; // eax
  int v107; // eax
  int v108; // eax
  int v109; // edi
  int v110; // eax
  int v111; // eax
  int v112; // eax
  int v113; // eax
  int v114; // eax
  int v115; // eax
  int v116; // eax
  int v117; // edi
  int v118; // eax
  int v119; // eax
  int v120; // eax
  int v121; // eax
  int v122; // eax
  int v123; // eax
  bool v124; // al
  int v125; // eax
  int v126; // eax
  int v127; // eax
  int v128; // eax
  int *dword_795A982; // edi
  int v130; // eax
  int v131; // edi
  int v132; // eax
  int *v133; // edi
  int v134; // eax
  int v135; // eax
  int v136; // eax
  char *v137; // edi
  int v138; // eax
  char *v139; // edi
  int v140; // eax
  int v141; // eax
  void *v142; // eax
  int v143; // edi
  int v144; // eax
  int v145; // eax
  void *v146; // ecx
  int v147; // eax
  double v148; // st7
  int v149; // ecx
  void *pMem22; // edx
  int v151; // eax
  int pObj8; // ecx
  int v153; // edi
  int v154; // [esp+28Ch] [ebp-88h]
  float v155; // [esp+28Ch] [ebp-88h]
  int v156; // [esp+290h] [ebp-84h]
  float v157; // [esp+294h] [ebp-80h]
  char v158; // [esp+294h] [ebp-80h]
  int dword_795A0C2; // [esp+294h] [ebp-80h]
  int *v160; // [esp+298h] [ebp-7Ch]
  int v161; // [esp+29Ch] [ebp-78h]
  int v162; // [esp+2A0h] [ebp-74h]
  int v163; // [esp+2A4h] [ebp-70h] BYREF
  int v164; // [esp+2A8h] [ebp-6Ch]
  int v165; // [esp+2ACh] [ebp-68h]
  int v166; // [esp+2B0h] [ebp-64h]
  int v167; // [esp+2B4h] [ebp-60h]
  int v168; // [esp+2B8h] [ebp-5Ch]
  uint8_t v169[4]; // [esp+2BCh] [ebp-58h] BYREF
  void *v170; // [esp+2C0h] [ebp-54h]
  int v171; // [esp+2C4h] [ebp-50h]
  int v172; // [esp+2C8h] [ebp-4Ch]
  float v173; // [esp+2CCh] [ebp-48h] BYREF
  float v174; // [esp+2D0h] [ebp-44h]
  float v175; // [esp+2D4h] [ebp-40h] BYREF
  void *v176; // [esp+2D8h] [ebp-3Ch]
  int v177; // [esp+2DCh] [ebp-38h]
  int v178; // [esp+2E0h] [ebp-34h]
  int pObj5; // [esp+2E4h] [ebp-30h] BYREF
  float v180; // [esp+2E8h] [ebp-2Ch] BYREF
  int v181; // [esp+2ECh] [ebp-28h] BYREF
  void *Block; // [esp+2F0h] [ebp-24h]
  void *Src; // [esp+2F4h] [ebp-20h]
  void *pMem2; // [esp+2F8h] [ebp-1Ch] BYREF
  int k; // [esp+2FCh] [ebp-18h]
  int i; // [esp+300h] [ebp-14h]
  bool v187; // [esp+307h] [ebp-Dh]
  int v188; // [esp+310h] [ebp-4h]

  // ── [段 1] 入口序：sub_4B7430 通用逐帧前置 → 清理残留状态对象 → 进大状态 switch(this+6556) ──
  //   this = CNSwordman 对象（本函数 = CNSwordman::vt+332，class_method_slots.txt 直证）；
  //   +8440 标志位在 +8436 对象 vt+80 失效时由 sub_49C620(1,0,0) 收束并清位；
  //   case 表 0/8/0xA/0xF/0x10/0x11/0x12/0x13/0x14/0x15/0x16/0x17；大状态号语义见 _fields/CNSwordman.h（候选表）
  sub_4B7430((int *)pArg1, fArg2);
  if ( *(uint8_t *)(pArg1 + 8440) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8436) + 80))(*(uint32_t *)(pArg1 + 8436)) == 0 )
  {
    sub_49C620(1, 0, 0);
    *(uint8_t *)(pArg1 + 8440) = 0;
  }
  switch ( *(uint32_t *)(pArg1 + 6556) )
  {
    // ── [段 2] 大状态 0：待机态 —— R_SM_MOANING_LOOP 循环呻吟音效随 +6752 与 +8432 对象活否开关 ──
    //   +8441 为「已播」标志；失效时 vt+216(15) 停音；goto LABEL_198 走公共尾
    case 0:
      if ( *(uint8_t *)(pArg1 + 6752) != 0
        && (pObj4 = *(uint32_t *)(pArg1 + 8432)) != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 80))(pObj4) != 0 )
      {
        if ( *(uint8_t *)(pArg1 + 8441) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "R_SM_MOANING_LOOP",
            15,
            0,
            0);
          *(uint8_t *)(pArg1 + 8441) = 1;
        }
      }
      else if ( *(uint8_t *)(pArg1 + 8441) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 15);
        *(uint8_t *)(pArg1 + 8441) = 0;
      }
      goto LABEL_198;
    // ── [段 3] 大状态 8：突进态 —— +8216==46 且 +8220==0 且前方有敌（+120 对象的帧 148>1）时 vt+612 收束 ──
    case 8:
      if ( *(uint32_t *)(pArg1 + 8216) == 46 && *(uint8_t *)(pArg1 + 8220) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) > 1 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 612))(pArg1, 0, 0);
        *(uint8_t *)(pArg1 + 8220) = 1;
      }
      goto LABEL_198;
    // ── [段 4] 大状态 0xA（10）：★ 上斩/落剑 —— 仅子型 23 / 44 / 32 有演出 ──
    //   +7816 为技能子型；44 需 +7808==1 门控，23 与 32 直接 vt+612(1,1) 收束；
    //   23 支（+7808==0 且本机且已达 +7820 时刻）：sub_47E9D0(5)/(7)/(4)/(6)/(3) 五处读表算落点，
    //   sub_425100(+116) 取数量后 sub_425A00(i) 逐个取对象、sub_4E5F70 逐件挂接，
    //   最后 sub_431230 压 2 参（1, 0.0）→ vt+560(10, buf, 0, 0) + vt+564 提交，sub_5E5260 释放
    case 0xA:
      if ( *(uint32_t *)(pArg1 + 7812) != 0 )
        goto LABEL_198;
      v54 = *(uint32_t *)(pArg1 + 7816);
      if ( v54 != 23 )
      {
        if ( v54 == 44 )
        {
          if ( *(uint32_t *)(pArg1 + 7808) != 1 )
            goto LABEL_198;
        }
        else if ( v54 != 32 )
        {
          goto LABEL_198;
        }
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 612))(pArg1, 1, 1);
        goto LABEL_198;
      }
      if ( *(uint32_t *)(pArg1 + 7808) == 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0
        && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 7820) )  // 【clock_now(clk)】
      {
        v176 = nullptr;
        v177 = 0;
        v178 = 0;
        v55 = *(uint32_t *)pArg1;
        v188 = 8;
        v180 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(v55 + 1160))(pArg1, 23));
        v181 = 0;
        Block = nullptr;
        pMem2 = nullptr;
        Src = (void *)sub_47E9D0(5);
        v56 = (void *)sub_47E9D0(7);
        v57 = *(uint32_t *)pArg1;
        pMem2 = v56;
        if ( (*(int (/*thiscall*/ **)(int))(v57 + 152))(pArg1) == 1 )
        {
          pObj5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);
          v58 = sub_47E9D0(4) + pObj5;
        }
        else
        {
          pObj5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - (uint32_t)Src;
          v58 = pObj5 - sub_47E9D0(3);
        }
        v59 = *(uint32_t *)pArg1;
        v181 = v58;
        pObj5 = (*(int (/*thiscall*/ **)(int))(v59 + 124))(pArg1);
        Block = (void *)(sub_47E9D0(6) + pObj5);
        v180 = COERCE_FLOAT(sub_425100(*(uint32_t *)(pArg1 + 116)));
        for ( i = 0; i < SLODWORD(v180); ++i )
        {
          v60 = sub_425A00(i);
          pObj9 = v60;
          pObj5 = v60;
          if ( v60 != 0
            && v60 != pArg1
            && (uint8_t)sub_423970(v60, &v181) != 0
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj9 + 40))(pObj9, 273) != 0 )
          {
            v62 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj9 + 376))(pObj9);
            if ( v62 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 376))(pArg1) )
              sub_428430(&pObj5);
          }
        }
        v170 = nullptr;
        v171 = 0;
        v172 = 0;
        LOBYTE(v188) = 9;
        pObj5 = 1;
        sub_431230(&pObj5);
        v180 = 0.0;
        sub_431230(&v180);
        (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, v169, 0, 0);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 564))(pArg1);
        v163 = 0;
        v164 = 0;
        v165 = 0;
        v166 = 0;
        v167 = 0;
        v168 = 0;
        for ( j = 0; v176 != nullptr && j < (v177 - (int)v176) >> 2; ++j )
          sub_4E5F70(pArg1, *((uint32_t *)v176 + j), &v163, 1, 1);
        sub_5E5260(v169);
        v188 = -1;
        sub_5E5260(&v175);
      }
      goto LABEL_198;
    // ── [段 5] 大状态 0xF（15）：★ 防御 —— +8240==1 时在身前 40 单位内生成 GuardDust.ani 尘效 ──
    //   fabs(宿主+16 速度) < 40.0 且 +8256==0 才建；sub_42FCB0(228)/sub_44B6C0(284) 双门控（动画/粒子池）；
    //   sub_45FE80 登记 + vt+148 时刻同步 + vt+112 落坐标（按 vt+152 朝向取正负）；
    //   另一支达到 +8248 时刻时压 4 参（0,0,0,vt+152 朝向）→ vt+560(15, buf, 0, 0) 收招
    case 0xF:
      if ( *(uint32_t *)(pArg1 + 8240) == 1 )
      {
        if ( fabs(*(float *)(*(uint32_t *)(pArg1 + 112) + 16)) < 40.0 && *(uint8_t *)(pArg1 + 8256) == 0 )
        {
          pObj5 = sub_42FCB0(228);
          v188 = 0;
          if ( pObj5 != 0 )
          {
            if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
              LOBYTE(v4) = pArg1 + 108;
            else
              v4 = *(uint32_t *)(pArg1 + 364);
            v5 = sub_431920(v4, (char)"Effect/Animation/GuardDust.ani", 1);
          }
          else
          {
            v5 = 0;
          }
          pObj5 = sub_44B6C0(284);
          v188 = 1;
          if ( pObj5 != 0 )
            v6 = (float *)sub_44E1F0(v5, 1);
          else
            v6 = nullptr;
          v7 = *(uint32_t *)(pArg1 + 116);
          i = (int)v6;
          v188 = -1;
          sub_45FE80(v7, (int)v6, 2, 0, (int)v6, pArg1, 0);
          v8 = *(uint32_t *)pArg1;
          v180 = *v6;
          v9 = (*(int (/*thiscall*/ **)(int))(v8 + 152))(pArg1);
          (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v180) + 148))(v6, v9);
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 0 )
            v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 45;
          else
            v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 45;
          v11 = *(uint32_t *)pArg1;
          v12 = *v6;
          k = v10;
          v13 = (*(int (/*thiscall*/ **)(int))(v11 + 128))(pArg1);
          v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v13);
          (*(void (/*thiscall*/ **)(int, int, int))(LODWORD(v12) + 112))(i, k, v14);
          *(uint8_t *)(pArg1 + 8256) = 1;
        }
        if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8248) )  // 【clock_now(clk)】
        {
          v176 = nullptr;
          v177 = 0;
          v178 = 0;
          v188 = 2;
          v180 = 0.0;
          sub_431230(&v180);
          v180 = 0.0;
          sub_431230(&v180);
          v180 = 0.0;
          sub_431230(&v180);
          v180 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1));
          sub_431230(&v180);
          (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 15, &v175, 0, 0);
          v188 = -1;
          sub_5E5260(&v175);
        }
      }
      goto LABEL_198;
    // ── [段 6] 大状态 0x10（16）：★ 蓄力/硬直连击 —— GhostSlash 系两枚 Charge 动画 ──
    //   +8272==1 且达 dword_7959F8 时刻：+8284==0 时建 HardAttackFullCharge2.ani（430-499 行）并
    //   sub_45FE80 挂接+落位；+200ms 后（Clock >= dword_7959F8+200）第二段处理；
    //   +8272==2 且目标帧数 >= 3 且 +8304==0 时播 GHOSTSLASH_CHARGE_END 并置 +8304；
    //   +8272 落 0 或 2 → LABEL_66（走 0x11 分支），否则 LABEL_198 公共尾
    case 0x10:
      if ( *(uint32_t *)(pArg1 + 8272) == 1 && sub_699000(pArg1 + 6560) >= dword_7959F8 )  // 【clock_now(clk)】
      {
        if ( *(uint8_t *)(pArg1 + 8284) == 0 )
        {
          *(uint8_t *)(pArg1 + 8284) = 1;
          v15 = (uint32_t *)(pArg1 + 8296);
          for ( k = 2; k != 0; --k )
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *v15++);
          v180 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1));
          v16 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);
          v17 = *(uint32_t *)pArg1;
          pMem2 = v16;
          i = (*(int (/*thiscall*/ **)(int))(v17 + 128))(pArg1);
          pObj5 = sub_42FCB0(228);
          v188 = 3;
          if ( pObj5 != 0 )
          {
            if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
              LOBYTE(v18) = pArg1 + 108;
            else
              v18 = *(uint32_t *)(pArg1 + 364);
            v19 = sub_431920(v18, (char)"Effect/Animation/HardAttackFullCharge2.ani", 1);
          }
          else
          {
            v19 = 0;
          }
          pObj5 = sub_44B6C0(284);
          v188 = 4;
          if ( pObj5 != 0 )
            pObj7 = sub_44E1F0(v19, 1);
          else
            pObj7 = 0;
          v21 = *(uint32_t *)(pArg1 + 116);
          k = pObj7;
          v188 = -1;
          sub_45FE80(v21, pObj7, 2, 0, pObj7, pArg1, 0);
          v22 = *(uint32_t *)pArg1;
          pObj5 = *(uint32_t *)pObj7;
          v23 = (*(int (/*thiscall*/ **)(int))(v22 + 152))(pArg1);
          (*(void (/*thiscall*/ **)(int, int))(pObj5 + 148))(pObj7, v23);
          (*(void (/*thiscall*/ **)(int, float, void *, int))(*(uint32_t *)pObj7 + 112))(
            pObj7,
            COERCE_FLOAT(LODWORD(v180)),
            pMem2,
            i);
          pObj5 = sub_42FCB0(228);
          v188 = 5;
          if ( pObj5 != 0 )
          {
            if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
              LOBYTE(v24) = pArg1 + 108;
            else
              v24 = *(uint32_t *)(pArg1 + 364);
            v25 = sub_431920(v24, (char)"Effect/Animation/HardAttackFullCharge1.ani", 1);
          }
          else
          {
            v25 = 0;
          }
          pObj5 = sub_44B6C0(284);
          v188 = 6;
          if ( pObj5 != 0 )
            pObj = sub_44E1F0(v25, 1);
          else
            pObj = 0;
          v27 = *(uint32_t *)(pArg1 + 116);
          k = pObj;
          v188 = -1;
          sub_45FE80(v27, pObj, 2, 0, pObj, pArg1, 0);
          v28 = *(uint32_t *)pArg1;
          pObj5 = *(uint32_t *)pObj;
          v29 = (*(int (/*thiscall*/ **)(int))(v28 + 152))(pArg1);
          (*(void (/*thiscall*/ **)(int, int))(pObj5 + 148))(pObj, v29);
          (*(void (/*thiscall*/ **)(int, float, void *, int))(*(uint32_t *)pObj + 112))(
            pObj,
            COERCE_FLOAT(LODWORD(v180)),
            pMem2,
            i);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "GHOSTSLASH_CHARGE_END",
            -1,
            0,
            0);
        }
        if ( sub_699000(pArg1 + 6560) >= dword_7959F8 + 200 )  // 【clock_now(clk)】
        {
          v30 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
          v31 = sub_42B420(255, 220, -200 - dword_7959F8 + v30, 100);
          (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 252))(pArg1, 0, v31);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 252))(pArg1, 1, v31);
        }
      }
      if ( *(uint32_t *)(pArg1 + 8272) == 2 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 && *(uint8_t *)(pArg1 + 8304) == 0 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "GHOSTSLASH_CRY",
          -1,
          0,
          0);
        *(uint8_t *)(pArg1 + 8304) = 1;
      }
      v32 = *(uint32_t *)(pArg1 + 8272);
      if ( v32 == 0 || v32 == 2 )
        goto LABEL_66;
      goto LABEL_198;
    // ── [段 7] 大状态 0x11（17）与 0x12（18）：★ 蓄力完成斩（LABEL_66 为 0x10/0x11 共用入口）──
    //   LABEL_66：若 +120 对象的帧 170 非 0 则 goto LABEL_67（vt+560(0,0,0,0) 收招），否则公共尾；
    //   0x12 支：+8308<2 时按 +8328+200ms 节拍取 dword_8F8270[vt+924(this,2)] 对象，
    //   vt+152 朝向→vt+160 落位、对象 vt+10 打标、vt+28+84 置标志、vt+12(0) 与 vt+92(buf) 配置，
    //   sub_4600B0(2, 0, buf) 提交并记 +8328 时刻；另一条按 +8316/+8320 窗口与目标帧 2 决定收束
    case 0x11:
LABEL_66:
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )
        goto LABEL_67;
      goto LABEL_198;
    case 0x12:
      if ( *(int *)(pArg1 + 8308) < 2 )
      {
        v33 = pArg1 + 6560;
        if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8328) + 200 )  // 【clock_now(clk)】
        {
          v34 = (void **)dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 924))(pArg1, 2)];
          v35 = *(uint32_t *)pArg1;
          pObj5 = (int)v34;
          v36 = (*(int (/*thiscall*/ **)(int))(v35 + 152))(pArg1);
          v187 = v36 == 0;
          if ( v36 != 0 )
            v37 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 20;
          else
            v37 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 20;
          v38 = *(uint32_t *)pArg1;
          v180 = *(float *)&v37;
          pMem2 = *v34;
          v39 = (*(int (/*thiscall*/ **)(int))(v38 + 128))(pArg1);
          v40 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v39);
          pObj2 = pObj5;
          (*((void (/*thiscall*/ **)(int, float, int))pMem2 + 10))(pObj5, COERCE_FLOAT(LODWORD(v180)), v40);
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 28))(pObj5) + 84) = v187;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 12))(pObj2, 0);
          (*(void (/*thiscall*/ **)(int, float *))(*(uint32_t *)pObj2 + 92))(pObj2, &v175);
          v42 = *(void **)(pArg1 + 116);
          v188 = 7;
          sub_4600B0(v42, 2, 0, (int)&v175);
          v33 = pArg1 + 6560;
          *(uint32_t *)(pArg1 + 8328) = sub_699000(pArg1 + 6560);
          v188 = -1;
          sub_5E5260(&v175);
        }
        if ( sub_699000(v33) >= *(uint32_t *)(pArg1 + 8316) )  // 【clock_now(clk)】
        {
          v43 = sub_699000(v33) < *(uint32_t *)(pArg1 + 8320);  // 【clock_now(clk)】
          v44 = *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148);
          if ( v43 )
          {
            if ( v44 == 0 )
              sub_4AECE0(1);
          }
          else if ( v44 == 2 )
          {
            sub_4AECE0(3);
          }
        }
      }
      if ( *(int *)(pArg1 + 8308) < 2 )
      {
        if ( sub_699000(pArg1 + 6560) < *(uint32_t *)(pArg1 + 8324) )  // 【clock_now(clk)】
          goto LABEL_198;
      }
      else if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) == 0 )
      {
// ── [段 8] ★ LABEL_198 公共尾入口（全部大状态汇合）：非本地主角且非 PVP 本体则直接 return ──
//   dword_8F7C04 = 本地主角；this+200 == 2 表示非本体（分身/幻影）—— 二者之外不做本地演出
LABEL_198:
        if ( dword_8F7C04 != pArg1 || *(uint32_t *)(pArg1 + 200) == 2 )
          return;
        // ── [段 9] 公共尾之 buff/光环轮询（一）：sub_4842B0(索引) 查光环表，命中则 vt+1312 判定后提交 ──
        //   索引 1 → vt+560(15, buf(0,0,0,朝向))；索引 5 → vt+560(16, buf(0,0))；
        //   状态 16 支：按 +8272 与 +8276 决定 vt+1160(6) 与 sub_47E9D0(0) 时刻门（LABEL_229/230）
        v106 = *(uint32_t *)(pArg1 + 6556);
        if ( (v106 == 0 || v106 == 11 || v106 == 8)
          && sub_4842B0(1, (void *)(pArg1 + 8116)) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 1) != 0 )
        {
          v176 = nullptr;
          v177 = 0;
          v178 = 0;
          v188 = 16;
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);
          sub_431230(&pObj5);
          (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 15, &v175, 0, 0);
          v188 = -1;
          sub_5E5260(&v175);
        }
        if ( *(uint32_t *)(pArg1 + 6556) == 15
          && *(uint32_t *)(pArg1 + 8240) == 0
          && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8244)  // 【clock_now(clk)】
          && (uint8_t)sub_4BFC10(pArg1 + 8116) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
        }
        v107 = *(uint32_t *)(pArg1 + 6556);
        if ( (v107 == 0 || v107 == 11 || v107 == 8)
          // ── [段 10] 公共尾之索引 5：vt+560(16, buf) 双参提交（状态 0/11/8 门控）──
          && sub_4842B0(5, (void *)(pArg1 + 8116)) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 5) != 0 )
        {
          v170 = nullptr;
          v171 = 0;
          v172 = 0;
          v188 = 17;
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 16, v169, 0, 0);
          v188 = -1;
          sub_5E5260(v169);
        }
        // ── [段 11] 公共尾之状态 16 前置：+8272==1 且达 dword_7959F8 时建 HardAttackFullCharge2.ani ──
        if ( *(uint32_t *)(pArg1 + 6556) == 16 )
        {
          v108 = *(uint32_t *)(pArg1 + 8272);
          if ( v108 != 0 )
          {
            if ( v108 != 1 || (uint8_t)sub_4BFC10(pArg1 + 8116) != 0 )
              goto LABEL_230;
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 19;
            pObj5 = 2;
            sub_431230(&pObj5);
            pObj5 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
            sub_431230(&pObj5);
            goto LABEL_229;
          }
          if ( *(uint8_t *)(pArg1 + 8276) == 0
            && ((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 6) == 0
             || (uint8_t)sub_4BFC10(pArg1 + 8116) == 0) )
          {
            *(uint8_t *)(pArg1 + 8276) = 1;
          }
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 6);
          v109 = sub_47E9D0(0);
          if ( *(uint8_t *)(pArg1 + 8276) == 0 && sub_699000(pArg1 + 6560) >= v109 )  // 【clock_now(clk)】
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 18;
            pObj5 = 1;
            sub_431230(&pObj5);
            pObj5 = 0;
            sub_431230(&pObj5);
LABEL_229:
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 16, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
LABEL_230:
        // ── [段 12] 公共尾之 buff/光环轮询（二）：索引 8/9/20/21/22/24/32/34/44/46 ──
        //   索引 8/20/21/22 为浮点型（sub_4842B0 返回非 NAN 判定）；9/23/24/34/44/46 为整型（!= -1 判定）；
        //   24 与 32、44 为「多参打包」型：sub_431230 逐参压栈后 vt+560(10, buf) 一次性提交；
        //   34 走 sub_47E440(bool) + 决策；23 按 vt+740/vt+736 比值与 flt_9B934C 阈值分支
        v110 = *(uint32_t *)(pArg1 + 6556);
        if ( v110 == 0 || v110 == 11 || v110 == 8 )
        {
          v180 = COERCE_FLOAT(sub_4842B0(8, nullptr));
          if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 8) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 20;
            pObj5 = 0;
            sub_431230(&pObj5);
            sub_431230(&v180);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 18, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        if ( *(uint32_t *)(pArg1 + 6556) == 18 && *(int *)(pArg1 + 8308) < 2 && *(uint32_t *)(pArg1 + 8312) != -1 )
        {
          if ( sub_699000(pArg1 + 6560) > *(uint32_t *)(pArg1 + 8312) )  // 【clock_now(clk)】
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 8);
            sub_47E440(0);
            *(uint32_t *)(pArg1 + 8312) = -1;
          }
          else
          {
            v180 = COERCE_FLOAT(sub_4842B0(8, nullptr));
            if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 8) != 0 )
            {
              v170 = nullptr;
              v171 = 0;
              v172 = 0;
              v111 = *(uint32_t *)(pArg1 + 8308) + 1;
              v188 = 21;
              pObj5 = v111;
              sub_431230(&pObj5);
              sub_431230(&v180);
              (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 18, v169, 0, 0);
              v188 = -1;
              sub_5E5260(v169);
            }
          }
        }
        v112 = *(uint32_t *)(pArg1 + 6556);
        if ( v112 == 0 || v112 == 11 )
        {
          pObj5 = sub_4842B0(9, nullptr);
          if ( pObj5 != -1 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 9) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 22;
            sub_431230(&pObj5);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 19, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        v113 = *(uint32_t *)(pArg1 + 6556);
        if ( v113 == 0 || v113 == 11 || v113 == 8 )
        {
          v180 = COERCE_FLOAT(sub_4842B0(20, nullptr));
          if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 20) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 23;
            pObj5 = 20;
            sub_431230(&pObj5);
            sub_431230(&v180);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 20, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        v114 = *(uint32_t *)(pArg1 + 6556);
        if ( v114 == 0 || v114 == 11 || v114 == 8 )
        {
          v180 = COERCE_FLOAT(sub_4842B0(21, nullptr));
          if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 21) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 24;
            pObj5 = 21;
            sub_431230(&pObj5);
            sub_431230(&v180);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 20, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        v115 = *(uint32_t *)(pArg1 + 6556);
        if ( v115 == 0 || v115 == 11 || v115 == 8 )
        {
          v180 = COERCE_FLOAT(sub_4842B0(22, nullptr));
          if ( v180 != NAN && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 22) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 25;
            pObj5 = 22;
            sub_431230(&pObj5);
            sub_431230(&v180);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 20, v169, 0, 0);
            v188 = -1;
            sub_5E5260(v169);
          }
        }
        if ( *(uint32_t *)(pArg1 + 6556) == 20 && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8364) )  // 【clock_now(clk)】
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
        v116 = *(uint32_t *)(pArg1 + 6556);
        if ( (v116 == 0 || v116 == 11) && sub_4842B0(23, nullptr) != -1 )
        {
          pObj5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 740))(pArg1);
          v117 = (uint64_t)((double)pObj5 * flt_9B934C);
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 736))(pArg1) > v117
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 23) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 23);
            Block = nullptr;
            Src = nullptr;
            pMem2 = nullptr;
            v188 = 26;
            pObj5 = 0;
            sub_431230(&pObj5);
            pObj5 = 0;
            sub_431230(&pObj5);
            pObj5 = 23;
            sub_431230(&pObj5);
            v118 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 23);
            pObj5 = sub_4B1C40(v118);
            sub_431230(&pObj5);
            pObj5 = sub_47E9D0(8);
            sub_431230(&pObj5);
            pObj5 = 0;
            sub_431230(&pObj5);
            pObj5 = 4;
            sub_431230(&pObj5);
            pObj5 = 4;
            sub_431230(&pObj5);
            (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, &v181, 0, 0);
            v188 = -1;
            sub_5E5260(&v181);
          }
        }
        v119 = *(uint32_t *)(pArg1 + 6556);
        if ( (v119 == 0 || v119 == 11)
          // ── [段 13] 公共尾之索引 24：多参 vt+560(10) 大打包（含 24 号状态与 sub_47E9D0(3) 时刻）──
          && sub_4842B0(24, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 24) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 24);
          Block = nullptr;
          Src = nullptr;
          pMem2 = nullptr;
          v188 = 27;
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 24;
          sub_431230(&pObj5);
          v120 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 24, -1, -1, 11);
          pObj5 = sub_47EF20(1, v120, v160, v161, v162);
          sub_431230(&pObj5);
          pObj5 = sub_47E9D0(3);
          sub_431230(&pObj5);
          pObj5 = 1;
          sub_431230(&pObj5);
          pObj5 = 3;
          sub_431230(&pObj5);
          pObj5 = 3;
          sub_431230(&pObj5);
          v162 = 0;
          v161 = 0;
          v160 = &v181;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 560))(pArg1, 10);
          v188 = -1;
          sub_5E5260(&v181);
        }
        v121 = *(uint32_t *)(pArg1 + 6556);
        if ( (v121 == 0 || v121 == 11)
          && sub_4842B0(32, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 32) != 0 )
        {
          Block = nullptr;
          Src = nullptr;
          pMem2 = nullptr;
          v188 = 28;
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 32;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pArg1 + 1160))(pArg1, 32, 0);
          pObj5 = sub_47E9D0(v160);
          sub_431230(&pObj5);
          pObj5 = 1;
          sub_431230(&pObj5);
          pObj5 = 4;
          sub_431230(&pObj5);
          pObj5 = 4;
          sub_431230(&pObj5);
          v160 = nullptr;
          (*(void (/*thiscall*/ **)(int, int, int *, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, &v181, 0);
          v188 = -1;
          sub_5E5260(&v181);
        }
        v122 = *(uint32_t *)(pArg1 + 6556);
        if ( v122 == 0 || v122 == 11 )
        {
          v124 = false;
          if ( *(uint8_t *)(pArg1 + 7730) != 0 )
          {
            pObj5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 736))(pArg1);
            v123 = *(uint32_t *)pArg1;
            v180 = (double)pObj5 * 100.0;
            pObj5 = (*(int (/*thiscall*/ **)(int))(v123 + 740))(pArg1);
            if ( (double)dword_795A08 >= v180 / (double)pObj5 )
              v124 = true;
          }
          v158 = v124;
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 34);
          sub_47E440(v158);
          if ( sub_4842B0(34, nullptr) != -1
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 34) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 34);
            Block = nullptr;
            Src = nullptr;
            pMem2 = nullptr;
            v188 = 29;
            pObj5 = 0;
            sub_431230(&pObj5);
            pObj5 = 0;
            sub_431230(&pObj5);
            pObj5 = 34;
            sub_431230(&pObj5);
            v125 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 34);
            pObj5 = sub_4B1C40(v125);
            sub_431230(&pObj5);
            pObj5 = sub_47E9D0(1);
            sub_431230(&pObj5);
            pObj5 = 1;
            sub_431230(&pObj5);
            pObj5 = 4;
            sub_431230(&pObj5);
            pObj5 = 4;
            sub_431230(&pObj5);
            (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, &v181, 0, 0);
            v188 = -1;
            sub_5E5260(&v181);
          }
        }
        v126 = *(uint32_t *)(pArg1 + 6556);
        if ( (v126 == 0 || v126 == 11)
          && sub_4842B0(44, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 44) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 44);
          Block = nullptr;
          Src = nullptr;
          pMem2 = nullptr;
          v188 = 30;
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 44;
          sub_431230(&pObj5);
          v127 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 44);
          pObj5 = sub_4B1C40(v127);
          sub_431230(&pObj5);
          v128 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 44, -1, -1, 11);
          pObj5 = sub_47EF20(1, v128, v160, v161, v162);
          sub_431230(&pObj5);
          pObj5 = 1;
          sub_431230(&pObj5);
          pObj5 = 4;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 560))(pArg1, 10);
          v188 = -1;
          sub_5E5260(&v181);
        }
        // ── [段 14] 公共尾之 10 号特例：+7812==0 且 +7808==1 且 +7816==44 且 sub_4BFBC0 门时 vt+560(0) ──
        if ( *(uint32_t *)(pArg1 + 6556) == 10
          && *(uint32_t *)(pArg1 + 7812) == 0
          && *(uint32_t *)(pArg1 + 7808) == 1
          && *(uint32_t *)(pArg1 + 7816) == 44
          && (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
        }
        // ── [段 15] 公共尾之光环批量遍历：两段 do-while 扫 dword_795A98 起与 &unk_795A88 起的注册表 ──
        //   终止条件用 RTTI 类型描述符地址当哨兵（&CNAuraBoss / dword_795A98），即编译期表边界
        dword_795A982 = dword_795A98;
        i = (int)dword_795A98;
        do
        {
          v130 = *(uint32_t *)(pArg1 + 6556);
          if ( (v130 == 0 || v130 == 11)
            && sub_4842B0(*dword_795A982, nullptr) != -1
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, *dword_795A982) != 0 )
          {
            v131 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 1160))(pArg1, *(uint32_t *)i);
            Block = nullptr;
            Src = nullptr;
            pMem2 = nullptr;
            v188 = 31;
            pObj5 = 0;
            sub_431230(&pObj5);
            pObj5 = 0;
            sub_431230(&pObj5);
            pObj5 = *(uint32_t *)i;
            sub_431230(&pObj5);
            v132 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 1140))(pArg1, *(uint32_t *)i);
            if ( v132 == -1 )
              v132 = sub_41A5E0(v131 + 510);
            pObj5 = sub_41A5E0(*(uint32_t *)(v131 + 316) + 14 * (v132 - 1));
            sub_431230(&pObj5);
            pObj5 = sub_47E9D0(0);
            sub_431230(&pObj5);
            pObj5 = 0;
            sub_431230(&pObj5);
            pObj5 = 4;
            sub_431230(&pObj5);
            pObj5 = 0;
            sub_431230(&pObj5);
            (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 10, &v181, 0, 0);
            v188 = -1;
            if ( Block != nullptr )
              j__free(Block);
            dword_795A982 = (int *)i;
            Block = nullptr;
            Src = nullptr;
            pMem2 = nullptr;
          }
          i = (int)++dword_795A982;
        }
        while ( (int)dword_795A982 < (int)&CNAuraBoss `RTTI Type Descriptor' );
        // ── [段 16] 光环遍历第二段：&unk_795A88 起扫到 dword_795A98（另一张注册表的编译期边界）──
        v133 = (int *)&unk_795A88;
        do
        {
          v134 = *(uint32_t *)(pArg1 + 6556);
          if ( (v134 == 0 || v134 == 11)
            && sub_4842B0(*v133, nullptr) != -1
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, *v133) != 0 )
          {
            v176 = nullptr;
            v177 = 0;
            v178 = 0;
            pObj5 = *v133;
            v188 = 32;
            sub_430C80(nullptr, 1, (int)&pObj5);
            (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 14, &v175, 0, 0);
            v188 = -1;
            if ( v176 != nullptr )
              j__free(v176);
            v176 = nullptr;
            v177 = 0;
            v178 = 0;
          }
          ++v133;
        }
        while ( (int)v133 < (int)dword_795A98 );
        // ── [段 17] 公共尾之技能特例：大状态 6/21/12 的专属触发 ──
        //   状态 6 且 +6892==1 且光环 16/17 命中 → vt+560(21,...) 或 sub_431230(17)+vt+560(7, buf)；
        //   状态 21 且宿主 +192==4 且 +8424 >= dword_795A04 → vt+560(1,...)；
        //   状态 12 且 vt+1140(11)>0 且达 +8228++8232 且 +8236 < dword_7959FC 且 +548 非 0 →
        //   vt+1160(11) + sub_47E440(1) + sub_4842B0(11) 追加判定
        if ( *(uint32_t *)(pArg1 + 6556) == 6
          && *(uint32_t *)(pArg1 + 6892) == 1
          && sub_4842B0(16, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 16) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 21, 0, 0, 0);
        }
        if ( *(uint32_t *)(pArg1 + 6556) == 21 && *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 )
        {
          v135 = *(uint32_t *)(pArg1 + 8424);
          if ( v135 >= dword_795A04 )
            (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 580))(
              pArg1,
              20016,
              v135 - dword_795A04,
              0,
              0,
              0,
              0,
              0,
              4,
              0,
              0,
              0);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 1, 0, 0, 0);
        }
        if ( *(uint32_t *)(pArg1 + 6556) == 6
          && *(uint32_t *)(pArg1 + 6892) == 1
          && sub_4842B0(17, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 17) != 0 )
        {
          v170 = nullptr;
          v171 = 0;
          v172 = 0;
          v188 = 33;
          pObj5 = 17;
          sub_431230(&pObj5);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 7, v169, 0, 0);
          v188 = -1;
          if ( v170 != nullptr )
            j__free(v170);
        }
        if ( *(uint32_t *)(pArg1 + 6556) == 12
          && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 11) > 0
          && sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8228) + *(uint32_t *)(pArg1 + 8232)  // 【clock_now(clk)】
          && *(uint32_t *)(pArg1 + 8236) < dword_7959FC
          && *(uint32_t *)(pArg1 + 548) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 11);
          sub_47E440(1);
          if ( sub_4842B0(11, nullptr) != -1 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 11);
        }
        v136 = *(uint32_t *)(pArg1 + 6556);
        // ── [段 18] 公共尾之索引 46：sub_430C80 打包 + 数组游标修正（Block/Src/pMem2 三指针）──
        //   LABEL_357 为数组遍历共用出口（1109-1127 行，按指针差算元素下标）
        if ( (v136 == 0 || v136 == 11 || v136 == 8)
          && sub_4842B0(46, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 46) != 0 )
        {
          Block = nullptr;
          Src = nullptr;
          pMem2 = nullptr;
          v188 = 34;
          pObj5 = 2;
          sub_430C80(nullptr, 1, (int)&pObj5);
          v137 = (char *)Src;
          pObj5 = 46;
          if ( Block == nullptr )
            goto LABEL_357;
          if ( ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)(((uint8_t *)pMem2 - (uint8_t *)Block) >> 2) )
          {
            *(uint32_t *)Src = 46;
            Src = v137 + 4;
          }
          else
          {
LABEL_357:
            sub_430C80(Src, 1, (int)&pObj5);
          }
          (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 24, &v181, 0, 0);
          v188 = -1;
          if ( Block != nullptr )
            j__free(Block);
        }
        // ── [段 19] 公共尾续：状态 0/11/8 与 22 / 6 / 0/11 / 23 的四个条件块 ──
        //   LABEL_368/LABEL_377 为中间汇合点；状态 23 且 +8488==1（LABEL_357→LABEL_398 链）
        v138 = *(uint32_t *)(pArg1 + 6556);
        if ( (v138 == 0 || v138 == 11 || v138 == 8)
          && sub_4842B0(31, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 31) != 0 )
        {
          Block = nullptr;
          Src = nullptr;
          pMem2 = nullptr;
          v188 = 35;
          pObj5 = 0;
          sub_430C80(nullptr, 1, (int)&pObj5);
          v139 = (char *)Src;
          pObj5 = 31;
          if ( Block == nullptr )
            goto LABEL_368;
          if ( ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)(((uint8_t *)pMem2 - (uint8_t *)Block) >> 2) )
          {
            *(uint32_t *)Src = 31;
            Src = v139 + 4;
          }
          else
          {
LABEL_368:
            sub_430C80(Src, 1, (int)&pObj5);
          }
          (*(void (/*thiscall*/ **)(int, int, int *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 22, &v181, 0, 0);
          v188 = -1;
          if ( Block != nullptr )
            j__free(Block);
        }
        if ( *(uint32_t *)(pArg1 + 6556) == 22 )
        {
          if ( *(uint32_t *)(pArg1 + 8448) != 0 )
          {
            if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8472) && *(uint32_t *)(pArg1 + 8476) == 2 )  // 【clock_now(clk)】
              goto LABEL_377;
          }
          else if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )
          {
LABEL_377:
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
          }
        }
        if ( *(uint32_t *)(pArg1 + 6556) == 6
          && *(uint8_t *)(pArg1 + 6988) != 0
          && *(uint32_t *)(pArg1 + 6896) < *(uint32_t *)(pArg1 + 6900)
          && sub_4842B0(49, nullptr) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 49) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 7, 0, 0, 0);
        }
        v140 = *(uint32_t *)(pArg1 + 6556);
        if ( (v140 == 0 || v140 == 11)
          && sub_4842B0(50, (void *)(pArg1 + 8116)) != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 50) != 0 )
        {
          v170 = nullptr;
          v171 = 0;
          v172 = 0;
          v188 = 36;
          pObj5 = 0;
          sub_431230(&pObj5);
          pObj5 = 0;
          sub_431230(&pObj5);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 23, v169, 0, 0);
          v188 = -1;
          if ( v170 != nullptr )
            j__free(v170);
        }
        // ── [段 20] 状态 23 主体：+8488==1 / 非 1 / 0 三支，末段按 +8512 时刻收招（LABEL_412）──
        //   LABEL_412 汇合后做光环 52 的判定（+8444 对象 vt+80 活否 / vt+1312(52)），随后 return
        if ( *(uint32_t *)(pArg1 + 6556) != 23 )
          goto LABEL_412;
        v141 = *(uint32_t *)(pArg1 + 8488);
        if ( v141 != 0 )
        {
          if ( v141 != 1 )
          {
            if ( v141 == 2 )
            {
              if ( *(uint8_t *)(pArg1 + 8516) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 4 )
              {
                v143 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 588))(pArg1);
                v144 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1140))(pArg1);
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 50, 0, v144);
                v145 = sub_47EF20(50, -1, -1, 11, "Particle/GrandWave.ptl");
                v146 = *(void **)(v143 + 19);
                *(uint32_t *)(v143 + 85) = v145;
                Src = *(void **)(v143 + 15);
                v147 = *(uint32_t *)(pArg1 + 8492);
                pMem2 = v146;
                if ( v147 > 0 )
                {
                  dword_795A0C2 = dword_795A0C;
                  v156 = v147;
                  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 51);
                  pObj5 = sub_47E9D0(2);
                  v148 = (double)pObj5 * 0.0099999998;
                  v155 = v148;
                  sub_4049C0(1.0, v155, v156, dword_795A0C2);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
                  i = v143 + 15;
                  LODWORD(v180) = 2;
                  do
                  {
                    v149 = i;
                    *(uint32_t *)i = (uint64_t)((double)*(int *)i * v148);
                    v77 = LODWORD(v180) == 1;
                    i = v149 + 4;
                    --LODWORD(v180);
                  }
                  while ( !v77 );
                }
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 580))(
                  pArg1,
                  20019,
                  *(uint32_t *)(pArg1 + 8492),
                  v143,
                  0,
                  80,
                  0,
                  0,
                  4,
                  0,
                  0,
                  0);
                pMem22 = pMem2;
                *(uint32_t *)(v143 + 15) = Src;
                *(uint32_t *)(v143 + 19) = pMem22;
                *(uint8_t *)(pArg1 + 8516) = 1;
              }
              if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 17 )
                (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
            }
            goto LABEL_412;
          }
          if ( (uint8_t)sub_4BFC10(pArg1 + 8116) == 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 38;
            pObj5 = 2;
            sub_431230(&pObj5);
            pObj5 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
            sub_431230(&pObj5);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 23, v169, 0, 0);
            v142 = v170;
            goto LABEL_398;
          }
        }
        else if ( sub_699000(pArg1 + 6560) >= *(uint32_t *)(pArg1 + 8512) )  // 【clock_now(clk)】
        {
          v176 = nullptr;
          v177 = 0;
          v178 = 0;
          v188 = 37;
          if ( (uint8_t)sub_4BFC10(pArg1 + 8116) != 0
            && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 51) > 0 )
          {
            pObj5 = 1;
            sub_431230(&pObj5);
          }
          else
          {
            pObj5 = 2;
            sub_431230(&pObj5);
          }
          pObj5 = 0;
          sub_431230(&pObj5);
          (*(void (/*thiscall*/ **)(int, int, float *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 23, &v175, 0, 0);
          v142 = v176;
LABEL_398:
          v188 = -1;
          if ( v142 != nullptr )
            j__free(v142);
        }
LABEL_412:
        v151 = *(uint32_t *)(pArg1 + 6556);
        if ( (v151 == 0 || v151 == 11) && sub_4842B0(52, nullptr) != -1 )
        {
          pObj8 = *(uint32_t *)(pArg1 + 8444);
          if ( pObj8 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj8 + 80))(pObj8) != 0 )
          {
            v153 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 52);
            pObj5 = sub_41A5E0(v153 + 524);
            sub_47DEE0(0.0);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 52);
            sub_47DEE0(*(float *)&pObj5);
          }
          else if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1312))(pArg1, 52) != 0 )
          {
            v170 = nullptr;
            v171 = 0;
            v172 = 0;
            v188 = 39;
            pObj5 = 52;
            sub_431230(&pObj5);
            (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 14, v169, 0, 0);
            if ( v170 != nullptr )
              j__free(v170);
          }
        }
        return;
      }
      // ── [段 21] ▲ 唯一不走公共尾的分支（0x12 内 goto 至 1330）：vt+560(0,0,0,0) 直接收招后回公共尾 ──
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
      goto LABEL_198;
    // ── [段 22] 大状态 0x13（19）：★ 抓取斩 —— 按动画帧数两段推进（2 帧 / 8 帧阈值）──
    //   +8332 与 +8333 分别为两段「已播」标志；两段都调 vt+212 播音效 + vt+1172 取动作串；
    //   末段 goto LABEL_67（vt+560(0,0,0,0) 收招）
    case 0x13:
      if ( *(uint8_t *)(pArg1 + 8332) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 2 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "SM_BAL_SHOT",
          -1,
          0,
          0);
        v45 = *(uint32_t *)pArg1;
        v46 = (*(int (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 1172))(pArg1, 0, -1, 0, 0);
        (*(void (/*thiscall*/ **)(int, int))(v45 + 212))(pArg1, v46);
        *(uint8_t *)(pArg1 + 8332) = 1;
      }
      if ( *(uint8_t *)(pArg1 + 8333) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 8 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "SWD_BAL_END",
          -1,
          0,
          0);
        *(uint8_t *)(pArg1 + 8333) = 1;
      }
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 120) + 170) != 0 )
LABEL_67:
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
      goto LABEL_198;
    // ── [段 23] 大状态 0x14（20）：★ 投掷/跃起 —— 回挂 +8348 动画 + 按 +8340 技能号分 20/22/21 三支 ──
    //   +8348 对象帧 170 非 0 时 vt+208 回挂；动画帧归零且 sub_4910A0 达 +8360 时 sub_4AECE0(1)+vt+204 挂载；
    //   20/22 支：vt+1140/+1160(+8340) 取参 → sub_47EF20 读表写 +8356 对象 +85 槽 → vt+580(+8352, 参数)；
    //   21 支：vt+1140(21) → 12 参 vt+560 提交并置 +8344=1；LABEL_106 为置位出口
    case 0x14:
      if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 8348) + 170) != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(pArg1 + 8348));
      if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 120) + 148) == 0 && sub_4910A0(*(uint32_t *)(pArg1 + 120)) >= *(uint32_t *)(pArg1 + 8360) )
      {
        sub_4AECE0(1);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
          pArg1,
          1,
          *(uint32_t *)(pArg1 + 8348),
          59,
          0,
          0,
          0);
      }
      if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) < 4 || *(uint8_t *)(pArg1 + 8344) != 0 )
        goto LABEL_198;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 )
        goto LABEL_106;
      v47 = *(uint32_t *)(pArg1 + 8340);
      if ( v47 == 20 || v47 == 22 )
      {
        v49 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, v47, -1, -1, 11);
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pArg1 + 1160))(pArg1, *(uint32_t *)(pArg1 + 8340), 0, v49);
        v50 = sub_47EF20(v160, v161, v162, v163, v164);
        v51 = *(uint32_t *)(pArg1 + 8356);
        v164 = 0;
        v163 = 0;
        v162 = 0;
        v161 = 4;
        v160 = nullptr;
        *(uint32_t *)(v51 + 85) = v50;
        v52 = *(uint32_t *)pArg1;
        v53 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t))(*(uint32_t *)pArg1 + 1140))(
                pArg1,
                *(uint32_t *)(pArg1 + 8340),
                *(uint32_t *)(pArg1 + 8356),
                0,
                80,
                0);
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(v52 + 580))(pArg1, *(uint32_t *)(pArg1 + 8352), v53);
      }
      else if ( v47 == 21 )
      {
        v48 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 21);
        (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, int, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 580))(
          pArg1,
          *(uint32_t *)(pArg1 + 8352),
          v48,
          *(uint32_t *)(pArg1 + 8356),
          0,
          100,
          -4,
          0,
          4,
          0,
          0,
          0);
        *(uint8_t *)(pArg1 + 8344) = 1;
        goto LABEL_198;
      }
LABEL_106:
      *(uint8_t *)(pArg1 + 8344) = 1;
      goto LABEL_198;
    // ── [段 24] 大状态 0x15（21）：JumpAttackHold 起手 —— 200ms 与 +8413 门 ──
    //   vt+876 双段位移 + sub_494F20(2, -0.9×+6652) 帧率标定；+8416 惰性建 JumpAttackHold.ani；
    //   vt+204 挂载后置 +8413=1，goto LABEL_198
    case 0x15:
      if ( sub_699000(pArg1 + 6560) >= 200 && *(uint8_t *)(pArg1 + 8413) == 0 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(
          pArg1,
          0,
          470,
          470,
          0,
          0,
          0);
        v157 = (double)*(int *)(pArg1 + 6652) * -0.89999998;
        sub_494F20(2, v157);
        if ( *(uint32_t *)(pArg1 + 8416) == 0 )
        {
          pObj5 = sub_42FCB0(228);
          v188 = 10;
          if ( pObj5 != 0 )
          {
            if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
              v64 = sub_431920(pArg1 + 108, (char)"Effect/Animation/JumpAttackHold.ani", 1);
            else
              v64 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)"Effect/Animation/JumpAttackHold.ani", 1);
          }
          else
          {
            v64 = 0;
          }
          v188 = -1;
          *(uint32_t *)(pArg1 + 8416) = v64;
        }
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
          pArg1,
          1,
          *(uint32_t *)(pArg1 + 8416),
          0,
          0,
          0,
          0);
        *(uint8_t *)(pArg1 + 8413) = 1;
      }
      goto LABEL_198;
    // ── [段 25] 大状态 0x16（22）：★ 嗜血/吸血（BLOOD_SPREAD + BLOOD_SUCK + sub_4B3DF0 状态挂）──
    //   +8448==1 时对 +8456 对象（vt+80 判定）与 +8476 计时器两支处理；
    //   收招段 sub_5F0460(this) + sub_47DCD0(this,-1) + sub_4B3DF0(状态,0,0,时长, buf,1) 挂状态
    case 0x16:
      if ( *(uint32_t *)(pArg1 + 8448) == 1 )
      {
        pObj10 = *(uint32_t *)(pArg1 + 8456);
        if ( pObj10 != 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj10 + 840))(pObj10) != 9
          && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8456) + 840))(*(uint32_t *)(pArg1 + 8456)) != 5
          && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8456) + 308))(*(uint32_t *)(pArg1 + 8456)) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(**(uint32_t **)(pArg1 + 8456) + 560))(
            *(uint32_t *)(pArg1 + 8456),
            9,
            0,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 8456) + 564))(*(uint32_t *)(pArg1 + 8456));
        }
        v66 = *(uint32_t *)(pArg1 + 8476);
        if ( v66 != 0 )
        {
          if ( v66 == 1 && sub_699000(pArg1 + 6560) >= 750 )  // 【clock_now(clk)】
          {
            v74 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 31);
            v75 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 31);
            v76 = *(uint32_t *)pArg1;
            i = v75;
            if ( (*(uint8_t (/*thiscall*/ **)(int))(v76 + 308))(pArg1) != 0 )
            {
              v77 = *(uint32_t *)(pArg1 + 8456) == 0;
              pMem2 = nullptr;
              v180 = 0.0;
              if ( !v77 )
              {
                v78 = *(uint32_t *)pArg1;
                v173 = 0.0;
                v174 = 0.0;
                v175 = 0.0;
                v176 = nullptr;
                v177 = 0;
                v178 = 0;
                if ( (*(int (/*thiscall*/ **)(int))(v78 + 152))(pArg1) != 0 )
                  v79 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 43;
                else
                  v79 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 43;
                v80 = *(uint32_t *)pArg1;
                v180 = *(float *)&v79;
                v173 = (float)v79;
                pObj5 = (*(int (/*thiscall*/ **)(int))(v80 + 124))(pArg1);
                v81 = *(uint32_t *)pArg1;
                v174 = (float)pObj5;
                v82 = (*(int (/*thiscall*/ **)(int))(v81 + 128))(pArg1);
                v83 = *(uint32_t *)(pArg1 + 8456);
                pObj5 = v82 + 90;
                v175 = (float)(v82 + 90);
                v180 = COERCE_FLOAT(sub_605840(&pMem2, v83, &v173, 1));
              }
              v84 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 388))(pArg1);
              v85 = sub_47EFD0(v74, COERCE_FLOAT(1), i, v84, v84, 0);
              (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, void *, float))(*(uint32_t *)pArg1 + 580))(
                pArg1,
                20017,
                v85,
                0,
                0,
                43,
                1,
                90,
                4,
                0,
                pMem2,
                COERCE_FLOAT(LODWORD(v180)));
            }
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
              pArg1,
              "BLOOD_SPREAD",
              -1,
              0,
              0);
            sub_5F0460(pArg1);
            sub_47DCD0(pArg1, -1);
            pObj5 = sub_47EF20(2, i, -1, -1, 11);
            v180 = COERCE_FLOAT(sub_47EF20(3, i, -1, -1, 11));
            pMem = operator new(0x7Cu);
            pMem2 = pMem;
            v188 = 11;
            if ( pMem != nullptr )
            {
              *(float *)&v154 = (float)SLODWORD(v180);
              v87 = sub_4B3DF0(pMem, 0, 0, v154, pObj5, 1);
            }
            else
            {
              v87 = nullptr;
            }
            v88 = *v87;
            v188 = -1;
            (*(void (/*thiscall*/ **)(int *, int, int, int, uint32_t, int, int))(v88 + 56))(v87, pArg1, pArg1, 1, 0, 9, -1);
            *(uint32_t *)(pArg1 + 8476) = 2;
          }
        }
        else if ( sub_699000(pArg1 + 6560) >= 100 )  // 【clock_now(clk)】
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )
          {
            pObj3 = *(uint32_t *)(pArg1 + 8456);
            if ( pObj3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 724))(pObj3) == 0 )
            {
              v68 = *(uint32_t *)pArg1;
              v173 = 0.0;
              v174 = 0.0;
              v175 = 0.0;
              v176 = nullptr;
              v177 = 0;
              v178 = 0;
              if ( (*(int (/*thiscall*/ **)(int))(v68 + 152))(pArg1) != 0 )
                v69 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 43;
              else
                v69 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 43;
              v70 = *(uint32_t *)pArg1;
              v180 = *(float *)&v69;
              v173 = (float)v69;
              pObj5 = (*(int (/*thiscall*/ **)(int))(v70 + 124))(pArg1);
              v71 = *(uint32_t *)pArg1;
              v174 = (float)pObj5;
              v72 = (*(int (/*thiscall*/ **)(int))(v71 + 128))(pArg1);
              v73 = *(uint32_t *)(pArg1 + 8456);
              pObj5 = v72 + 90;
              v175 = (float)(v72 + 90);
              sub_4E5F70(pArg1, v73, &v173, 1, 1);
            }
          }
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "BLOOD_SUCK",
            -1,
            0,
            0);
          *(uint32_t *)(pArg1 + 8476) = 1;
        }
      }
      goto LABEL_198;
    // ── [段 26] 大状态 0x17（23）：★ 巨浪蓄力（grandWaveFullCharge1/2.ani）──
    //   +8488==1 且达 dword_795A0C 时刻：+8496==0 时建 grandWaveFullCharge2.ani + sub_45FE80 挂接落位，
    //   grandWaveFullCharge1.ani 同法；+200ms 后（Clock >= dword_795A0C+200）播 GHOSTSLASH_CHARGE_END
    //   （v105 = sub_42B420(255,220,-200-dword_795A0C+Clock,100) 彩色渐变参数）
    case 0x17:
      if ( *(uint32_t *)(pArg1 + 8488) == 1 && sub_699000(pArg1 + 6560) >= dword_795A0C )  // 【clock_now(clk)】
      {
        if ( *(uint8_t *)(pArg1 + 8496) == 0 )
        {
          *(uint8_t *)(pArg1 + 8496) = 1;
          v89 = (uint32_t *)(pArg1 + 8504);
          LODWORD(v180) = 2;
          do
          {
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *v89++);
            --LODWORD(v180);
          }
          while ( v180 != 0.0 );
          i = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);
          v90 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);
          v91 = *(uint32_t *)pArg1;
          k = v90;
          pMem2 = (void *)(*(int (/*thiscall*/ **)(int))(v91 + 128))(pArg1);
          pObj5 = sub_42FCB0(228);
          v188 = 12;
          if ( pObj5 != 0 )
          {
            if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
              LOBYTE(v92) = pArg1 + 108;
            else
              v92 = *(uint32_t *)(pArg1 + 364);
            v93 = sub_431920(v92, (char)"Effect/Animation/grandWaveFullCharge2.ani", 1);
          }
          else
          {
            v93 = 0;
          }
          pObj5 = sub_44B6C0(284);
          v188 = 13;
          if ( pObj5 != 0 )
            *(float *)&pObj6 = COERCE_FLOAT(sub_44E1F0(v93, 1));
          else
            *(float *)&pObj6 = 0.0;
          v95 = *(uint32_t *)(pArg1 + 116);
          v180 = *(float *)&pObj6;
          v188 = -1;
          sub_45FE80(v95, pObj6, 2, 0, pObj6, pArg1, 0);
          v96 = *(uint32_t *)pArg1;
          pObj5 = *(uint32_t *)pObj6;
          v97 = (*(int (/*thiscall*/ **)(int))(v96 + 152))(pArg1);
          (*(void (/*thiscall*/ **)(int, int))(pObj5 + 148))(pObj6, v97);
          (*(void (/*thiscall*/ **)(int, int, int, void *))(*(uint32_t *)pObj6 + 112))(pObj6, i, k, pMem2);
          pObj5 = sub_42FCB0(228);
          v188 = 14;
          if ( pObj5 != 0 )
          {
            if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
              LOBYTE(v98) = pArg1 + 108;
            else
              v98 = *(uint32_t *)(pArg1 + 364);
            v99 = sub_431920(v98, (char)"Effect/Animation/grandWaveFullCharge1.ani", 1);
          }
          else
          {
            v99 = 0;
          }
          pObj5 = sub_44B6C0(284);
          v188 = 15;
          if ( pObj5 != 0 )
            *(float *)&pObj11 = COERCE_FLOAT(sub_44E1F0(v99, 1));
          else
            *(float *)&pObj11 = 0.0;
          v101 = *(uint32_t *)(pArg1 + 116);
          v180 = *(float *)&pObj11;
          v188 = -1;
          sub_45FE80(v101, pObj11, 2, 0, pObj11, pArg1, 0);
          v102 = *(uint32_t *)pArg1;
          pObj5 = *(uint32_t *)pObj11;
          v103 = (*(int (/*thiscall*/ **)(int))(v102 + 152))(pArg1);
          (*(void (/*thiscall*/ **)(int, int))(pObj5 + 148))(pObj11, v103);
          (*(void (/*thiscall*/ **)(int, int, int, void *))(*(uint32_t *)pObj11 + 112))(pObj11, i, k, pMem2);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "GHOSTSLASH_CHARGE_END",
            -1,
            0,
            0);
        }
        if ( sub_699000(pArg1 + 6560) >= dword_795A0C + 200 )  // 【clock_now(clk)】
        {
          v104 = sub_699000(pArg1 + 6560);  // 【clock_now(clk)】
          v105 = sub_42B420(255, 220, -200 - dword_795A0C + v104, 100);
          (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 252))(pArg1, 0, v105);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 252))(pArg1, 1, v105);
        }
      }
      goto LABEL_198;
    // ── [段 27] default：无专属处理，直接 goto LABEL_198 走公共尾 ──
    default:
      goto LABEL_198;
  }
}

