// ============================================================
// 【40JP逆向源代码工程】src/game/bigfunc_4471E0_sub_4471E0.cpp
// 模块: ★战斗分发器 sub_4471E0 = CNRDUdpModule::vmt0（docs/90 P2 定案）
// 来源: work/dump_combat.txt  区块: 0x44（单独反编译，size=11291 字节）
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 1（单文件单函数，放宽行数上限）
// ------------------------------------------------------------
// ★ 包接收结构（函数前导直证）：
//   +0  BYTE   附加标识（仅入 "RECV %d %d" 日志第二参数）
//   +1  WORD   包类型 = switch 分发键
//   +3  DWORD  校验和（sub_48BE40(体,len) 比对，不符仅打日志返回）
//   +7  ...    包体（先经 sub_48BDC0 解密/预处理）
//   读包四档读取器：vt+72=1 字节 / vt+76=2 字节 / vt+80=4 字节 / vt+88=定长块
// ★ 宿主字段：this+262149(int*下标)=+0x100034 对象容器宿主(+104=对象列表)；
//   dword_8F7A24+12=当前模块类型(1主城/2选图/4PVP/6WARROOM，docs/13 §3)；
//   dword_8F7C04=本地主角；dword_8F8548=全局通知管理器【推断】；dword_99FD58=震屏管理器
// ★ 全 case 语义表见各 case 行上注释；缺席分支：0x01、0x24（服务器侧专用或废弃【待验证】）
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x4471E0 sub_4471E0  size=11291
// ------------------------------------------------------------
// ★ CNRDUdpModule::vmt0 —— 网络 UDP 包分发虚入口（docs/90 P2：被判定者算法命名定案）。
// 流程：vt+64 登记读指针(+7 跳过包头) → vt+140 "RECV %d %d"(类型, 附加标识) 日志 →
//       sub_48BDC0(体,len,0) 解密/预处理 → sub_48BE40 校验和与 +3 DWORD 比对 →
//       switch(包类型) 分发 43 个 case（0x00..0x2C，缺 0x01/0x24）→ default 忽略。
// 下方每个 case 行上注释 = 本次扫描产出：字符串自证标【字符串自证】，其余为
// 结构推断【推断】，0x13/0x14 为打击感研究已定案锚点（研究 20）。

void /*thiscall*/ sub_4471E0(int *this, int a2, int i, int a4)
{
  uint8_t *v4; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // esi
  int v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // edx
  int v26; // edi
  int v27; // esi
  int v28; // eax
  int v29; // eax
  int v30; // esi
  int v31; // edi
  int v32; // eax
  int v33; // eax
  int v34; // edi
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int v38; // edx
  int v39; // esi
  int v40; // eax
  int v41; // edi
  uint32_t *v42; // eax
  uint32_t *v43; // esi
  const char *v44; // esi
  int v45; // edx
  int v46; // eax
  int v47; // eax
  int *v48; // edi
  int v49; // esi
  int v50; // eax
  int v51; // edx
  int v52; // esi
  int v53; // eax
  int v54; // eax
  int v55; // eax
  int v56; // esi
  int v57; // eax
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int v62; // eax
  int v63; // edi
  int v64; // eax
  int v65; // eax
  int v66; // eax
  int v67; // eax
  void *v68; // eax
  int v69; // eax
  int *v70; // edi
  int v71; // eax
  int v72; // eax
  int v73; // edx
  int v74; // eax
  int v75; // edi
  double v76; // st7
  float *v77; // eax
  int v78; // edi
  int v79; // eax
  int v80; // edx
  int v81; // edx
  int v82; // esi
  int v83; // eax
  int v84; // esi
  int v85; // eax
  char v86; // al
  int v87; // eax
  int v88; // eax
  int v89; // eax
  int v90; // edi
  int v91; // eax
  int v92; // esi
  int v93; // ecx
  int v94; // eax
  int v95; // eax
  int v96; // edi
  int v97; // eax
  int v98; // edx
  int v99; // edx
  int v100; // esi
  int v101; // eax
  int v102; // eax
  int v103; // edx
  int v104; // esi
  int v105; // eax
  int v106; // eax
  int v107; // edx
  int v108; // eax
  int v109; // eax
  int v110; // edi
  int v111; // eax
  int v112; // eax
  int v113; // edx
  int v114; // esi
  int v115; // eax
  int v116; // eax
  int v117; // esi
  int v118; // edi
  int v119; // esi
  int v120; // edi
  int v121; // eax
  const char *v122; // eax
  int v123; // edx
  int v124; // esi
  int v125; // eax
  int v126; // eax
  float *v127; // eax
  int v128; // eax
  int v129; // esi
  int v130; // eax
  int v131; // eax
  int v132; // eax
  int v133; // edx
  int v134; // esi
  int v135; // eax
  int v136; // eax
  int v137; // eax
  uint32_t *j; // ecx
  int v139; // edx
  int v140; // edx
  int v141; // edx
  int v142; // edx
  int v143; // edx
  int v144; // edx
  int v145; // edi
  double v146; // st7
  int v147; // eax
  int v148; // eax
  int v149; // edi
  int v150; // eax
  int v151; // eax
  int v152; // esi
  int v153; // edi
  int v154; // eax
  int v155; // esi
  int v156; // eax
  int v157; // eax
  int v158; // eax
  int v159; // eax
  int v160; // eax
  int v161; // eax
  int v162; // eax
  int v163; // edx
  int v164; // edx
  int v165; // edx
  int v166; // edx
  int v167; // edx
  int v168; // eax
  int v169; // eax
  int v170; // edi
  int v171; // eax
  int v172; // eax
  int v173; // eax
  uint32_t *v174; // edi
  int v175; // ecx
  int v176; // eax
  int v177; // eax
  int v178; // eax
  int v179; // ecx
  int v180; // eax
  int v181; // eax
  int v182; // edx
  int v183; // edx
  char *v184; // eax
  char v185; // cl
  int v186; // edi
  int v187; // eax
  int v188; // eax
  int v189; // edx
  int v190; // eax
  int v191; // edx
  int v192; // edx
  int v193; // eax
  int v194; // edx
  int v195; // edx
  int v196; // eax
  int v197; // edx
  int v198; // eax
  int v199; // edx
  int v200; // edx
  int v201; // edx
  int v202; // edx
  void *v203; // eax
  int v204; // edx
  char *v205; // eax
  int v206; // edx
  int v207; // eax
  int v208; // eax
  int v209; // edi
  int v210; // eax
  int v211; // eax
  int v212; // eax
  int v213; // edx
  int v214; // esi
  int v215; // eax
  int v216; // eax
  int v217; // edx
  int v218; // esi
  int v219; // eax
  int v220; // edi
  int v221; // eax
  int v222; // esi
  int v223; // edx
  int v224; // esi
  int v225; // eax
  int v226; // esi
  int v227; // edx
  int v228; // eax
  int v229; // edx
  int v230; // eax
  int v231; // edi
  int v232; // eax
  int v233; // eax
  int v234; // edx
  int v235; // esi
  int v236; // eax
  int v237; // esi
  int v238; // eax
  int v239; // eax
  uint32_t *v240; // esi
  uint32_t *v241; // eax
  uint32_t *v242; // edi
  int v243; // ecx
  uint32_t *v244; // esi
  const char *v245; // eax
  uint32_t *v246; // edi
  uint32_t *v247; // esi
  const char *v248; // eax
  int v249; // edx
  int v250; // esi
  int v251; // eax
  int v252; // eax
  int v253; // eax
  int v254; // eax
  int v255; // eax
  int v256; // eax
  int v257; // eax
  int v258; // esi
  int v259; // edx
  int v260; // eax
  int v261; // esi
  int v262; // eax
  int v263; // [esp-8h] [ebp-12Ch]
  int v264; // [esp-4h] [ebp-128h]
  int v265; // [esp-4h] [ebp-128h]
  int v266; // [esp-4h] [ebp-128h]
  int v267; // [esp-4h] [ebp-128h]
  void *v268; // [esp+0h] [ebp-124h]
  char v269[4]; // [esp+Ch] [ebp-118h] BYREF
  int v270; // [esp+10h] [ebp-114h]
  int v271; // [esp+14h] [ebp-110h]
  int v272; // [esp+18h] [ebp-10Ch]
  char v273[4]; // [esp+1Ch] [ebp-108h] BYREF
  int v274; // [esp+20h] [ebp-104h]
  int v275; // [esp+24h] [ebp-100h]
  int v276; // [esp+28h] [ebp-FCh]
  int v277; // [esp+2Ch] [ebp-F8h]
  int v278; // [esp+30h] [ebp-F4h] BYREF
  float v279; // [esp+34h] [ebp-F0h] BYREF
  float v280; // [esp+38h] [ebp-ECh]
  float v281; // [esp+3Ch] [ebp-E8h] BYREF
  float v282; // [esp+40h] [ebp-E4h]
  float v283; // [esp+44h] [ebp-E0h]
  float v284; // [esp+48h] [ebp-DCh]
  int v285; // [esp+4Ch] [ebp-D8h] BYREF
  int v286; // [esp+50h] [ebp-D4h] BYREF
  int v287; // [esp+54h] [ebp-D0h] BYREF
  void *v288; // [esp+58h] [ebp-CCh] BYREF
  int v289; // [esp+5Ch] [ebp-C8h] BYREF
  uint8_t v290; // [esp+62h] [ebp-C2h] BYREF
  char v291; // [esp+63h] [ebp-C1h] BYREF
  int v292; // [esp+64h] [ebp-C0h] BYREF
  int v293; // [esp+68h] [ebp-BCh] BYREF
  int v294; // [esp+6Ch] [ebp-B8h] BYREF
  int v295; // [esp+70h] [ebp-B4h] BYREF
  uint8_t v296; // [esp+77h] [ebp-ADh] BYREF
  int v297; // [esp+78h] [ebp-ACh] BYREF
  int v298; // [esp+7Ch] [ebp-A8h] BYREF
  int v299; // [esp+80h] [ebp-A4h] BYREF
  int v300; // [esp+84h] [ebp-A0h] BYREF
  void *Block; // [esp+88h] [ebp-9Ch] BYREF
  int v302; // [esp+8Ch] [ebp-98h] BYREF
  void *v303; // [esp+90h] [ebp-94h] BYREF
  char v304[64]; // [esp+94h] [ebp-90h] BYREF
  char Buffer[4]; // [esp+D4h] [ebp-50h] BYREF
  int v306; // [esp+D8h] [ebp-4Ch] BYREF
  char v307[14]; // [esp+DCh] [ebp-48h] BYREF
  char v308[14]; // [esp+F8h] [ebp-2Ch] BYREF
  char v309[14]; // [esp+106h] [ebp-1Eh] BYREF
  int v310; // [esp+114h] [ebp-10h]
  int v311; // [esp+120h] [ebp-4h]

  v4 = (uint8_t *)i;
  v310 = dword_796E50;
  (*(void (/*thiscall*/ **)(int *, int))(*this + 64))(this, i + 7);
  (*(void (**)(int *, const char *, ...))(*this + 140))(this, "RECV %d %d", *(uint16_t *)(v4 + 1), *v4);
  v6 = 0;
  i = a4 - 7;
  sub_48BDC0(v4 + 7, a4 - 7, 0);
  v7 = sub_48BE40(v4 + 7, i);
  if ( v7 != *(uint32_t *)(v4 + 3) )
  {
    off_77F3FC(byte_6C63BC, i, v7, *(uint32_t *)(v4 + 3));
    return;
  }
  switch ( *(uint16_t *)(v4 + 1) )
  {
    // case 0 ——【字符串自证】UDP 通道握手回报：子码 0=REPLY TO / 1=RETURN / 2=FINISH（sub_446CF0/sub_4456C0/sub_52D970）
    case 0:
      v12 = *this;
      HIBYTE(a2) = 0;
      HIBYTE(i) = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v12 + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&v294 + 3);
      if ( HIBYTE(i) != 0 )
      {
        if ( HIBYTE(i) == 1 )
        {
          sub_446CF0(HIBYTE(a2), 0, 1);
          sub_4456C0(HIBYTE(a2), 2, 0);
          off_77F3FC("!UDP RETURN FROM [%d]", HIBYTE(a2));
        }
        else if ( HIBYTE(i) == 2 )
        {
          sub_446CF0(HIBYTE(a2), 0, 1);
          sub_52D970(HIBYTE(a2), 1);
          off_77F3FC("!UDP FINISH FROM [%d]", HIBYTE(a2));
        }
      }
      else
      {
        sub_4456C0(HIBYTE(a2), 1, 0);
        off_77F3FC("!UDP REPLY TO [%d]", HIBYTE(a2));
      }
      return;
    // case 2 —— 对象可见列表刷新：按计数循环 sub_455EB0 注册，尾部 (字节,字节) → sub_453DD0（选中槽同步）
    case 2:
      v13 = *this;
      HIBYTE(a2) = 0;
      v296 = 0;
      HIBYTE(i) = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v13 + 72))(this, (char *)&a2 + 3);
      v298 = *(uint32_t *)(dword_8F7A24 + 24);
      sub_446960();
      v14 = 0;
      if ( HIBYTE(a2) != 0 )
      {
        do
        {
          v15 = *this;
          v303 = nullptr;
          (*(void (/*thiscall*/ **)(int *, void **))(v15 + 76))(this, &v303);
          sub_455EB0((uint16_t)v303);
          ++v14;
        }
        while ( v14 < HIBYTE(a2) );
      }
      (*(void (/*thiscall*/ **)(int *, uint8_t *))(*this + 72))(this, &v296);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
      sub_453DD0(v296, HIBYTE(i));
      return;
    // case 3 —— 选中槽同步：两个字节直传 sub_453DD0（座位/选中项 + 状态）
    case 3:
      v16 = *this;
      HIBYTE(i) = 0;
      HIBYTE(a2) = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v16 + 72))(this, (char *)&i + 3);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      sub_453DD0(HIBYTE(i), HIBYTE(a2));
      return;
    // case 4 ——【推断】远程物件移除：id 对查对象 → 校验归属(vt+304/48/52) → vt+60 析构 + sub_4A0180 释放
    case 4:
      v17 = *this;
      HIBYTE(a2) = 0;
      HIBYTE(i) = 0;
      Block = nullptr;
      v303 = nullptr;
      v299 = 0;
      v300 = 0;
      (*(void (/*thiscall*/ **)(int *, void **))(v17 + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v299);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v300);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v302);
      v18 = *(this + 262149);
      if ( v18 != 0 && *(uint32_t *)(v18 + 104) != 0 )
      {
        v19 = sub_45EBE0((uint16_t)Block, (uint16_t)v303);
        if ( v19 != 0 && __PAIR64__(HIBYTE(i), HIBYTE(a2)) == *(uint64_t *)(*(this + 262149) + 112) )
        {
          v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 304))(v19);
          v21 = v20;
          if ( v20 == 0
            || (v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 48))(v20)) == (uint16_t)v299
            && (v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 52))(v21)) == (uint16_t)v300 )
          {
            v264 = v302;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 60))(v19);
            sub_4A0180(v264);
          }
        }
      }
      return;
    // case 5 ——【推断】对象状态/击退同步：id 对 + 3D 向量(sub_4469A0/446AB0/4E7DA0) → 判定体 vt+472 施向量、vt+228 状态机、vt+568/572 → sub_49FFC0
    case 5:
      HIBYTE(a2) = 0;
      v303 = nullptr;
      v298 = 0;
      Block = nullptr;
      v292 = 0;
      v282 = 0.0;
      v283 = 0.0;
      v284 = 0.0;
      v24 = *this;
      v311 = 0;
      (*(void (/*thiscall*/ **)(int *, void **))(v24 + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v298);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v292);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      v25 = *this;
      a4 = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v25 + 76))(this, &a4);
      v274 = 0;
      v275 = 0;
      v276 = 0;
      LOBYTE(v311) = 1;
      sub_4469A0((uint16_t)a4);
      v26 = 0;
      if ( (uint16_t)a4 != 0 )
      {
        do
        {
          (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
          sub_446BE0((char *)&i + 3);
          ++v26;
        }
        while ( v26 < (uint16_t)a4 );
      }
      v270 = 0;
      v271 = 0;
      v272 = 0;
      LOBYTE(v311) = 2;
      sub_446AB0(v273);
      sub_4E7DA0(&v281);
      v27 = *(this + 262149);
      if ( v27 != 0 && *(uint32_t *)(v27 + 104) != 0 )
      {
        v28 = sub_45EBE0((uint16_t)v303, (uint16_t)v298);
        v29 = __RTDynamicCast(v28, 0, &CNRDObject `RTTI Type Descriptor', &IRDCollisionObject `RTTI Type Descriptor', 0);
        v30 = v29;
        if ( v29 != 0 )
        {
          v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v29 + 304))(v29);
          if ( v31 == 0
            || (v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v31 + 48))(v31)) == (uint16_t)Block
            && (v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v31 + 52))(v31)) == (uint16_t)v292 )
          {
            v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 236))(v30);
            v35 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 244))(v30);
            v36 = *(uint32_t *)v30;
            i = v35;
            v302 = (*(int (/*thiscall*/ **)(int))(v36 + 240))(v30);
            if ( v34 != 0 )
              (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t))(*(uint32_t *)v30 + 228))(v30, 0, -1, 0);
            (*(void (/*thiscall*/ **)(int, uint32_t, float *, int, int))(*(uint32_t *)v30 + 472))(
              v30,
              HIBYTE(a2),
              &v281,
              1,
              1);
            if ( v34 != 0
              && ((*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v30 + 40))(v30, 17) == 0
               || HIBYTE(a2) == 3
               || HIBYTE(a2) == 4
               || HIBYTE(a2) == 5
               || HIBYTE(a2) == 9
               || v34 != 1
               || i == -1) )
            {
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v30 + 228))(v30, v34, i, v302);
            }
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 308))(v30) != 0 )
            {
              v37 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 568))(v30);
              if ( v37 == HIBYTE(a2) )
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 572))(v30);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v30 + 60))(v30);
              sub_49FFC0(1, 1);
            }
          }
        }
      }
      sub_5E5260(v269);
      sub_5E5260(v273);
      sub_5E5260(&v281);
      return;
    // case 6 ——【推断】怪物归属绑定：IRDMonster ← 玩家槽(sub_429830)[49] 经 vt+1044 设主；失败打 aCriticalError 串
    case 6:
      v38 = *this;
      v303 = nullptr;
      i = 0;
      a2 = 0;
      (*(void (/*thiscall*/ **)(int *, void **))(v38 + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      v39 = *(this + 262149);
      if ( v39 == 0 || *(uint32_t *)(v39 + 104) == 0 )
        return;
      v40 = sub_45EBE0((uint16_t)v303, (uint16_t)i);
      v41 = __RTDynamicCast(v40, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      v42 = (uint32_t *)sub_429830(a2);
      v43 = v42;
      if ( v41 != 0 )
      {
        if ( v42 == nullptr )
          goto LABEL_59;
        if ( v42[49] != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v41 + 1044))(v41, v42[49]);
      }
      if ( v43 != nullptr )
      {
        if ( v43[49] == 0 )
          off_77F3FC(aCriticalError_0, (uint16_t)a2);
      }
      else
      {
LABEL_59:
        off_77F3FC(aCriticalError_45, (uint16_t)a2);
      }
      if ( v41 == 0 )
      {
        if ( v43 != nullptr )
        {
          if ( v43[10] < 0x10u )
            v44 = (const char *)(v43 + 5);
          else
            v44 = (const char *)v43[5];
        }
        else
        {
          v44 = "NULL";
        }
        off_77F3FC(aFail_11, (uint16_t)v303, (uint16_t)i, v44);
      }
      return;
    // case 7 ——【推断】怪物行为触发：IRDMonster vt+1088（AI 事件）
    case 7:
      v51 = *this;
      i = 0;
      a2 = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v51 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      v52 = *(this + 262149);
      if ( v52 != 0 && *(uint32_t *)(v52 + 104) != 0 )
      {
        v53 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v54 = __RTDynamicCast(v53, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
        if ( v54 != 0 )
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v54 + 1088))(v54);
      }
      return;
    // case 8 —— 被动物体目标绑定：CNRDPassiveObject vt+680(目标碰撞体)；模块 4(PVP)→sub_446130 / 6(WARROOM)→sub_446190
    case 8:
      v59 = *this;
      i = 0;
      a2 = 0;
      v303 = nullptr;
      Block = nullptr;
      (*(void (/*thiscall*/ **)(int *, int *))(v59 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &Block);
      v60 = *(this + 262149);
      if ( v60 != 0 && *(uint32_t *)(v60 + 104) != 0 )
      {
        v61 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v62 = __RTDynamicCast(v61, 0, &CNRDObject `RTTI Type Descriptor', &CNRDPassiveObject `RTTI Type Descriptor', 0);
        v298 = v62;
        if ( v62 != 0 )
        {
          v63 = 0;
          if ( (uint16_t)v303 != 0xFFFF )
          {
            v64 = sub_45EBE0((uint16_t)v303, (uint16_t)Block);
            v63 = __RTDynamicCast(
                    v64,
                    0,
                    &CNRDObject `RTTI Type Descriptor',
                    &IRDCollisionObject `RTTI Type Descriptor',
                    0);
            v62 = v298;
          }
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v62 + 680))(v62, v63);
          if ( v63 != 0 )
          {
            v65 = dword_8F7A24;
            if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
            {
              sub_446130(v298, v63);
              v65 = dword_8F7A24;
            }
            if ( *(uint32_t *)(v65 + 12) == 6 )
              sub_446190(v298, v63);
          }
        }
      }
      return;
    // case 9 ——【推断】对象管理器接管：为对象创建 156B 管理对象(sub_445D00/445B90/4A0B60)，同步 3 float、vt+148/vt+4
    case 9:
      v66 = *this;
      HIBYTE(a2) = 0;
      v303 = nullptr;
      i = 0;
      (*(void (/*thiscall*/ **)(int *, void **))(v66 + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      v67 = *(this + 262149);
      if ( v67 != 0 && *(uint32_t *)(v67 + 104) != 0 )
      {
        v68 = (void *)sub_45EBE0((uint16_t)v303, (uint16_t)i);
        Block = v68;
        if ( v68 != nullptr )
        {
          v69 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)v68 + 60))(v68);
          v298 = v69;
          if ( HIBYTE(a2) != 0 )
          {
            v300 = *(uint32_t *)(v69 + 104);
            v70 = (int *)v300;
            if ( v300 == 0 )
            {
              v71 = sub_445D00(156);
              v277 = v71;
              v311 = 3;
              if ( v71 != 0 )
                v72 = sub_445B90(v71);
              else
                v72 = 0;
              v70 = (int *)v72;
              v311 = -1;
              v300 = v72;
              sub_4A0B60(v72);
            }
            v73 = *v70;
            v302 = *this;
            v74 = (*(int (/*thiscall*/ **)(int *, int))(v73 + 16))(v70, 98);
            (*(void (/*thiscall*/ **)(int *, int))(v302 + 88))(this, v74);
            v75 = 0;
            a4 = v298 + 4;
            do
            {
              v302 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v300 + 16))(v300) + v75);
              v76 = (double)v302;
              v77 = (float *)a4;
              *(uint8_t *)(v298 + 124) = 1;
              *v77 = v76;
              v75 += 4;
              a4 = (int)(v77 + 1);
            }
            while ( v75 < 12 );
            v78 = *(uint32_t *)Block;
            v79 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v300 + 16))(v300);
            (*(void (/*thiscall*/ **)(void *, bool))(v78 + 148))(Block, *(uint8_t *)(v79 + 84) == 0);
            v80 = *this;
            v299 = 0;
            (*(void (/*thiscall*/ **)(int *, int *))(v80 + 80))(this, &v299);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v300 + 4))(v300, v299);
          }
          else
          {
            sub_4A0B60(0);
          }
        }
      }
      return;
    // case 0xA ——【结构自证】角色装备槽同步：0xFFFF=卸槽(vt+792/vt+1080)；否则 sub_522300 生成 CNRDEquipment → vt+784 穿戴 + 槽表 sub_429830(...)74+4*槽
    case 0xA:
      HIBYTE(a2) = 0;
      v303 = nullptr;
      v300 = 0;
      i = 0;
      sub_4E9A50(&v306);
      v81 = *this;
      v311 = 4;
      (*(void (/*thiscall*/ **)(int *, void **))(v81 + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v300);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v302);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v293);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v289);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v285);
      v306 = v302;
      sub_41A590(v293);
      sub_41A590(v289);
      sub_41A590(v285);
      v82 = *(this + 262149);
      if ( v82 == 0 )
        goto LABEL_125;
      if ( *(uint32_t *)(v82 + 104) == 0 )
        goto LABEL_125;
      v83 = sub_45EBE0((uint16_t)v303, (uint16_t)v300);
      v84 = __RTDynamicCast(v83, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
      v298 = __RTDynamicCast(v84, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
      if ( v84 == 0 )
        goto LABEL_125;
      if ( (uint16_t)i == 0xFFFF )
      {
        if ( (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v84 + 792))(v84, HIBYTE(a2)) != 0 )
        {
          v85 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v84 + 788))(v84, HIBYTE(a2));
          if ( v85 != 0 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v85 + 4))(v85, 1);
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v84 + 40))(v84, 273) != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v84 + 1080))(v84, HIBYTE(a2));
        goto LABEL_120;
      }
      a4 = sub_41A5E0(v309);
      v86 = sub_41A5E0(v307);
      LOBYTE(a4) = (32 * a4) | v86 & 0x1F;
      v87 = sub_41A5E0(v308);
      v88 = sub_522300((void *)(uint16_t)i, v306, a4, 0, v87, 1);
      v89 = __RTDynamicCast(v88, 0, &IRDItem `RTTI Type Descriptor', &CNRDEquipment `RTTI Type Descriptor', 0);
      v90 = v89;
      if ( v89 == 0 )
      {
        off_77F3FC(aCriticalError_1, (uint16_t)i);
LABEL_120:
        if ( v298 != 0 && *(uint32_t *)(dword_8F7A24 + 12) != 3 && HIBYTE(a2) <= 9u )
        {
          v92 = sub_429830(v300) + 16;
          *(uint32_t *)(v92 + 4 * HIBYTE(a2) + 56) = (uint16_t)i;
          v93 = *(uint32_t *)(sub_429830(v300) + 192);
          if ( v93 != 0 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v93 + 348))(v93, v92);
        }
        goto LABEL_125;
      }
      v91 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v84 + 784))(v84, v89);
      if ( v91 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v91 + 4))(v91, 1);
      if ( v298 != 0 )
      {
        if ( dword_8F7C04 == v298 )
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v90 + 100))(v90);
        goto LABEL_120;
      }
LABEL_125:
      v311 = -1;
      sub_445150(&v306);
      return;
    // case 0xB —— 全装备栏校验刷新：本地主角 18 槽逐一比对 item id，不符即 vt+812(卸下)/vt+816(清槽)
    case 0xB:
      if ( dword_8F7C04 != 0 )
      {
        v94 = *this;
        HIBYTE(a2) = 0;
        v303 = nullptr;
        (*(void (/*thiscall*/ **)(int *, char *))(v94 + 72))(this, (char *)&a2 + 3);
        for ( i = 0; i < 18; ++i )
        {
          (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v303);
          v95 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, i);
          v96 = v95;
          if ( v95 != 0 )
            v97 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v95 + 16))(v95) + 4);
          else
            v97 = 0xFFFF;
          if ( (uint16_t)v303 != v97 )
          {
            v98 = *(uint32_t *)dword_8F7C04;
            if ( v96 != 0 )
              (*(void (/*stdcall*/ **)(int, uint32_t))(v98 + 812))(v96, HIBYTE(a2));
            else
              (*(void (/*stdcall*/ **)(int, uint32_t))(v98 + 816))(i, HIBYTE(a2));
          }
        }
      }
      return;
    // case 0xC ——【推断】对象数据注入：IRDActiveObject vt+732(data, 0, 1)
    case 0xC:
      v99 = *this;
      i = 0;
      a2 = 0;
      v303 = nullptr;
      (*(void (/*thiscall*/ **)(int *, int *))(v99 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 80))(this, &v303);
      v100 = *(this + 262149);
      if ( v100 != 0 && *(uint32_t *)(v100 + 104) != 0 )
      {
        v101 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v102 = __RTDynamicCast(v101, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        if ( v102 != 0 )
          (*(void (/*thiscall*/ **)(int, void *, uint32_t, int))(*(uint32_t *)v102 + 732))(v102, v303, 0, 1);
      }
      return;
    // case 0xD ——【推断】对象数据注入：IRDActiveObject vt+748(data, 1)
    case 0xD:
      v103 = *this;
      i = 0;
      a2 = 0;
      v303 = nullptr;
      (*(void (/*thiscall*/ **)(int *, int *))(v103 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 80))(this, &v303);
      v104 = *(this + 262149);
      if ( v104 != 0 && *(uint32_t *)(v104 + 104) != 0 )
      {
        v105 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v106 = __RTDynamicCast(v105, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        if ( v106 != 0 )
          (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)v106 + 748))(v106, v303, 1);
      }
      return;
    // case 0xE ——【推断】技能/状态事件：IRDActiveObject vt+768(子码, WORD, 目标碰撞体)
    case 0xE:
      v107 = *this;
      HIBYTE(a2) = 0;
      v303 = nullptr;
      i = 0;
      v300 = 0;
      Block = nullptr;
      v299 = 0;
      (*(void (/*thiscall*/ **)(int *, void **))(v107 + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v300);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v299);
      v108 = *(this + 262149);
      if ( v108 != 0 && *(uint32_t *)(v108 + 104) != 0 )
      {
        v109 = sub_45EBE0((uint16_t)v303, (uint16_t)i);
        v110 = __RTDynamicCast(v109, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        if ( v110 != 0 )
        {
          v111 = 0;
          if ( (uint16_t)Block != 0xFFFF )
          {
            v112 = sub_45EBE0((uint16_t)Block, (uint16_t)v299);
            v111 = __RTDynamicCast(
                     v112,
                     0,
                     &CNRDObject `RTTI Type Descriptor',
                     &IRDCollisionObject `RTTI Type Descriptor',
                     0);
          }
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)v110 + 768))(
            v110,
            HIBYTE(a2),
            (uint16_t)v300,
            v111);
        }
      }
      return;
    // case 0xF ——【推断】队伍编号同步：vt+672(0)=队号、vt+676(0)；本地主角且队号变化 → 48001 音效 + 502 号串横幅 + sub_41C150
    case 0xF:
      v113 = *this;
      HIBYTE(i) = 0;
      HIBYTE(a2) = 0;
      Block = nullptr;
      v303 = nullptr;
      (*(void (/*thiscall*/ **)(int *, void **))(v113 + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      v114 = *(this + 262149);
      if ( v114 != 0 && *(uint32_t *)(v114 + 104) != 0 )
      {
        v115 = sub_45EBE0((uint16_t)Block, (uint16_t)v303);
        v116 = __RTDynamicCast(v115, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        v117 = v116;
        if ( v116 != 0 )
        {
          v118 = HIBYTE(a2);
          *(uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v116 + 672))(v116, 0) = v118;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v117 + 676))(v117, 0);
          v119 = __RTDynamicCast(
                   v117,
                   0,
                   &IRDActiveObject `RTTI Type Descriptor',
                   &IRDCharacter `RTTI Type Descriptor',
                   0);
          if ( v119 != 0 )
          {
            v120 = sub_429830(v303);
            if ( v120 != 0 )
            {
              if ( HIBYTE(a2) > HIBYTE(i) )
              {
                if ( dword_8F7C04 == v119 )
                {
                  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v119 + 580))(
                    v119,
                    48001,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    4,
                    0,
                    0,
                    0);
                  sub_4451C0(1);
                }
                if ( *(uint32_t *)(v120 + 40) < 0x10u )
                  v121 = v120 + 20;
                else
                  v121 = *(uint32_t *)(v120 + 20);
                v265 = HIBYTE(a2);
                v263 = v121;
                v122 = (const char *)sub_422E70(502);
                sprintf(Buffer, v122, v263, v265);
                sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
              }
              sub_41C150(HIBYTE(a2));
            }
          }
        }
      }
      return;
    // case 0x10 ——【推断】对象渲染数据块 +0 字段增量（vt+348 取块首 float *f += 值）
    case 0x10:
      v123 = *this;
      i = 0;
      a2 = 0;
      v303 = nullptr;
      (*(void (/*thiscall*/ **)(int *, int *))(v123 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 80))(this, &v303);
      v124 = *(this + 262149);
      if ( v124 != 0 && *(uint32_t *)(v124 + 104) != 0 )
      {
        v125 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v126 = __RTDynamicCast(
                 v125,
                 0,
                 &CNRDObject `RTTI Type Descriptor',
                 &IRDCollisionObject `RTTI Type Descriptor',
                 0);
        if ( v126 != 0 )
        {
          v127 = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v126 + 348))(v126);
          *v127 = (double)(int)v303 + *v127;
        }
      }
      return;
    // case 0x11 ——【推断】对象渲染数据块 +8 字段增量（int16 累加）
    case 0x11:
      v128 = *this;
      i = 0;
      a2 = 0;
      v303 = nullptr;
      (*(void (/*thiscall*/ **)(int *, int *))(v128 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v303);
      v129 = *(this + 262149);
      if ( v129 != 0 && *(uint32_t *)(v129 + 104) != 0 )
      {
        v130 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v131 = __RTDynamicCast(
                 v130,
                 0,
                 &CNRDObject `RTTI Type Descriptor',
                 &IRDCollisionObject `RTTI Type Descriptor',
                 0);
        if ( v131 != 0 )
        {
          v132 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v131 + 348))(v131);
          *(uint32_t *)(v132 + 8) += (int16_t)v303;
        }
      }
      return;
    // case 0x12 ——【推断】对象叠加状态表：vt+348 块 +24 起 3 槽（id / 权重×0.01 / 参数，17 结尾）
    case 0x12:
      v133 = *this;
      HIBYTE(a2) = 0;
      HIBYTE(i) = 0;
      Block = nullptr;
      v303 = nullptr;
      v299 = 0;
      (*(void (/*thiscall*/ **)(int *, void **))(v133 + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v299);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
      v134 = *(this + 262149);
      if ( v134 != 0 && *(uint32_t *)(v134 + 104) != 0 )
      {
        v135 = sub_45EBE0((uint16_t)Block, (uint16_t)v303);
        v136 = __RTDynamicCast(
                 v135,
                 0,
                 &CNRDObject `RTTI Type Descriptor',
                 &IRDCollisionObject `RTTI Type Descriptor',
                 0);
        if ( v136 != 0 )
        {
          v137 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v136 + 348))(v136);
          for ( j = (uint32_t *)(v137 + 24); *j != 17; ++j )
          {
            if ( ++v6 >= 3 )
              return;
          }
          *(uint32_t *)(v137 + 4 * v6 + 24) = HIBYTE(a2);
          a4 = (uint16_t)v299;
          *(float *)(v137 + 4 * v6 + 36) = (double)(uint16_t)v299 * 0.0099999998;
          *(uint32_t *)(v137 + 4 * v6 + 48) = HIBYTE(i);
        }
      }
      return;
    // case 0x13 ——【研究定案】碰撞体交互同步：两判定体(vt+380)间 6 参数链式设定(vt+496/508/500/512/504/516)，17 状态判定体 → vt+700 + sub_53FB90
    case 0x13:
      v139 = *this;
      HIBYTE(a2) = 0;
      Block = nullptr;
      v300 = 0;
      v295 = 0;
      v303 = nullptr;
      v299 = 0;
      v279 = 0.0;
      v280 = 0.0;
      v281 = 0.0;
      v282 = 0.0;
      v283 = 0.0;
      v284 = 0.0;
      (*(void (/*thiscall*/ **)(int *, void **))(v139 + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v300);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v295);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, float *, int))(*this + 88))(this, &v279, 4);
      (*(void (/*thiscall*/ **)(int *, char *, int))(*this + 88))(this, (char *)&i + 2, 2);
      v140 = *this;
      v302 = SHIWORD(i);
      v280 = (float)SHIWORD(i);
      (*(void (/*thiscall*/ **)(int *, char *, int))(v140 + 88))(this, (char *)&i + 2, 2);
      v141 = *this;
      v302 = SHIWORD(i);
      v281 = (float)SHIWORD(i);
      (*(void (/*thiscall*/ **)(int *, char *, int))(v141 + 88))(this, (char *)&i + 2, 2);
      v142 = *this;
      v302 = SHIWORD(i);
      v282 = (float)SHIWORD(i);
      (*(void (/*thiscall*/ **)(int *, char *, int))(v142 + 88))(this, (char *)&i + 2, 2);
      v143 = *this;
      v302 = SHIWORD(i);
      v283 = (float)SHIWORD(i);
      (*(void (/*thiscall*/ **)(int *, char *, int))(v143 + 88))(this, (char *)&i + 2, 2);
      v144 = *this;
      v302 = SHIWORD(i);
      v284 = (float)SHIWORD(i);
      (*(void (/*thiscall*/ **)(int *, char *))(v144 + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v299);
      v145 = (uint16_t)Block;
      a4 = (uint16_t)v299 * ((uint16_t)Block + 1);
      v146 = (double)a4;
      a4 = (uint16_t)v303;
      *(this + 262496) = (uint64_t)(v146 * (v279 + v280 + 1.0) + (double)(uint16_t)v303);
      v147 = *(this + 262149);
      if ( v147 != 0 && *(uint32_t *)(v147 + 104) != 0 )
      {
        v148 = sub_45EBE0(v145, (uint16_t)v300);
        v149 = __RTDynamicCast(
                 v148,
                 0,
                 &CNRDObject `RTTI Type Descriptor',
                 &IRDCollisionObject `RTTI Type Descriptor',
                 0);
        v150 = sub_45EBE0((uint16_t)v295, (uint16_t)v303);
        v151 = __RTDynamicCast(
                 v150,
                 0,
                 &CNRDObject `RTTI Type Descriptor',
                 &IRDCollisionObject `RTTI Type Descriptor',
                 0);
        v152 = v151;
        if ( v149 != 0 && v151 != 0 )
        {
          v153 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v149 + 380))(v149);
          v154 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v152 + 380))(v152);
          v155 = v154;
          LOBYTE(v154) = HIBYTE(a2) != 0;
          v156 = (*(int (/*thiscall*/ **)(int, int, float *, int))(*(uint32_t *)v153 + 496))(v153, v155, &v279, v154);
          LOBYTE(v156) = HIBYTE(a2) != 0;
          v157 = (*(int (/*thiscall*/ **)(int, int, float *, int))(*(uint32_t *)v155 + 508))(v155, v153, &v279, v156);
          LOBYTE(v157) = HIBYTE(a2) != 0;
          v158 = (*(int (/*thiscall*/ **)(int, int, float *, int))(*(uint32_t *)v153 + 500))(v153, v155, &v279, v157);
          LOBYTE(v158) = HIBYTE(a2) != 0;
          v159 = (*(int (/*thiscall*/ **)(int, int, float *, int))(*(uint32_t *)v155 + 512))(v155, v153, &v279, v158);
          LOBYTE(v159) = HIBYTE(a2) != 0;
          v160 = (*(int (/*thiscall*/ **)(int, int, float *, int))(*(uint32_t *)v153 + 504))(v153, v155, &v279, v159);
          LOBYTE(v160) = HIBYTE(a2) != 0;
          (*(void (/*thiscall*/ **)(int, int, float *, int))(*(uint32_t *)v155 + 516))(v155, v153, &v279, v160);
          v161 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v155 + 40))(v155, 17);
          if ( (uint8_t)v161 != 0 )
          {
            LOBYTE(v161) = HIBYTE(a2) != 0;
            v266 = v161;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v155 + 700))(v155);
            sub_53FB90(v153, &v279, v266);
          }
        }
      }
      return;
    // case 0x14 ——【研究定案】命中/伤害包：受击方 vt+576 判定体、攻击方 vt+732 受击状态、飘字咽喉 sub_4D7960（研究 20 §1.1）、受击位移 sub_424270；PVP 本体受击 → sub_496010 震屏(8)
    case 0x14:
      v162 = *this;
      HIBYTE(a2) = 0;
      HIBYTE(i) = 0;
      v299 = 0;
      Block = nullptr;
      v288 = nullptr;
      v300 = 0;
      v287 = 0;
      v295 = 0;
      v286 = 0;
      v303 = nullptr;
      v279 = 0.0;
      v280 = 0.0;
      v281 = 0.0;
      v282 = 0.0;
      v283 = 0.0;
      v284 = 0.0;
      (*(void (/*thiscall*/ **)(int *, int *))(v162 + 76))(this, &v299);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v288);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v300);
      (*(void (/*thiscall*/ **)(int *, float *, int))(*this + 88))(this, &v279, 4);
      (*(void (/*thiscall*/ **)(int *, char *, int))(*this + 88))(this, (char *)&v294 + 2, 2);
      v163 = *this;
      v302 = SHIWORD(v294);
      v280 = (float)SHIWORD(v294);
      (*(void (/*thiscall*/ **)(int *, char *, int))(v163 + 88))(this, (char *)&v294 + 2, 2);
      v164 = *this;
      v302 = SHIWORD(v294);
      v281 = (float)SHIWORD(v294);
      (*(void (/*thiscall*/ **)(int *, char *, int))(v164 + 88))(this, (char *)&v294 + 2, 2);
      v165 = *this;
      v302 = SHIWORD(v294);
      v282 = (float)SHIWORD(v294);
      (*(void (/*thiscall*/ **)(int *, char *, int))(v165 + 88))(this, (char *)&v294 + 2, 2);
      v302 = SHIWORD(v294);
      v166 = *this;
      v283 = (float)SHIWORD(v294);
      (*(void (/*thiscall*/ **)(int *, char *, int))(v166 + 88))(this, (char *)&v294 + 2, 2);
      v167 = *this;
      v302 = SHIWORD(v294);
      v284 = (float)SHIWORD(v294);
      (*(void (/*thiscall*/ **)(int *, int *))(v167 + 80))(this, &v287);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v295);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v286);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 80))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
      v168 = *(this + 262149);
      if ( v168 != 0 && *(uint32_t *)(v168 + 104) != 0 )
      {
        v169 = sub_45EBE0((uint16_t)v299, (uint16_t)Block);
        v170 = __RTDynamicCast(
                 v169,
                 0,
                 &CNRDObject `RTTI Type Descriptor',
                 &IRDCollisionObject `RTTI Type Descriptor',
                 0);
        v297 = v170;
        if ( v170 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v170 + 576))(v170) != 0 )
        {
          v171 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v170 + 576))(v170);
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v171 + 40))(v171, 273) == 1 )
            v297 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v170 + 576))(v170);
        }
        v172 = sub_45EBE0((uint16_t)v288, (uint16_t)v300);
        v173 = __RTDynamicCast(v172, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        v174 = (uint32_t *)v173;
        if ( v173 != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v173 + 308))(v173) == 0 )
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*v174 + 732))(v174, v286, v297, 1);
          v175 = v297;
          LOBYTE(v175) = dword_8F7C04 == v297;
          sub_4D7960(
            (uint64_t)(v282 * 0.5 + v279),
            (uint64_t)(v283 * 0.5 + v280),
            (uint64_t)(v284 * 0.5 + v281 + 50.0),
            v287,
            HIBYTE(a2) != 0,
            dword_8F7C04 == (uint32_t)v174,
            v175);
          if ( HIBYTE(i) != 0 )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, float *))(*v174 + 528))(v174, v174, &v279);
          if ( (uint8_t)sub_445120(v174) != 0 )
            sub_495470(v295 + v174[1668]);
          else
            sub_495470(v295);
          sub_495490(v295 + v174[1671]);
          if ( v297 != 0 )
          {
            if ( HIBYTE(a2) == 1 )
              (*(void (/*thiscall*/ **)(int, uint32_t *, float *))(*(uint32_t *)v297 + 520))(v297, v174, &v279);
            if ( v303 != nullptr )
            {
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v297 + 524))(v297);
              (*(void (/*thiscall*/ **)(int *, uint32_t *, void *))(*this + 120))(this, v174, v303);
              sub_424270(v174, &v279);
            }
            v176 = *(uint32_t *)(dword_8F7A24 + 12);
            if ( (v176 == 4 || v176 == 6)
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v297 + 576))(v297) == dword_8F7C04
              && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v174 + 40))(v174, 273) != 0 )
            {
              v267 = v295;
              v177 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
              sub_496010((int)dword_99FD58, v177, 8, v267);
            }
          }
        }
      }
      return;
    // case 0x15 ——【推断】实体批量生成 I：按模块类型取场景管理器(4→+32/6→+40/余+28)，sub_53A220 创建 + sub_45FE80 注册；分支A 建 156B 管理对象(sub_52A2A0)，分支B vt+148/vt+112
    case 0x15:
      v178 = *this;
      v303 = nullptr;
      Block = nullptr;
      v287 = 0;
      v286 = 0;
      (*(void (/*thiscall*/ **)(int *, void **))(v178 + 76))(this, &v303);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v287);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v286);
      v179 = *(uint32_t *)(dword_8F7A24 + 12);
      v295 = 0;
      if ( v179 == 4 )
      {
        v180 = *(uint32_t *)(dword_8F7A24 + 32);
      }
      else if ( v179 == 6 )
      {
        v180 = *(uint32_t *)(dword_8F7A24 + 40);
      }
      else
      {
        v180 = *(uint32_t *)(dword_8F7A24 + 28);
      }
      v298 = *(uint32_t *)(*(uint32_t *)(v180 + 16) + 104);
      if ( v298 != 0 )
      {
        if ( (uint16_t)v303 != 0xFFFF )
        {
          v181 = sub_45EBE0((uint16_t)v303, (uint16_t)Block);
          v295 = __RTDynamicCast(
                   v181,
                   0,
                   &CNRDObject `RTTI Type Descriptor',
                   &IRDCollisionObject `RTTI Type Descriptor',
                   0);
          if ( v295 == 0 && (uint16_t)v303 == 273 )
            v295 = *(uint32_t *)(sub_429830(Block) + 196);
        }
        v292 = 0;
        if ( (uint16_t)v287 != 0xFFFF )
          v292 = sub_45EBE0((uint16_t)v287, (uint16_t)v286);
        v182 = *this;
        v300 = 0;
        (*(void (/*thiscall*/ **)(int *, int *))(v182 + 76))(this, &v300);
        a4 = 0;
        if ( (uint16_t)v300 != 0 )
        {
          do
          {
            v183 = *this;
            v294 = 0xFFFF;
            v278 = 0;
            v299 = 0;
            v288 = nullptr;
            (*(void (/*thiscall*/ **)(int *, int *))(v183 + 76))(this, &v294);
            (*(void (/*thiscall*/ **)(int *, void **))(*this + 80))(this, &v288);
            (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v278);
            (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v299);
            if ( (uint16_t)v299 == 0xFFFF )
            {
              v184 = (char *)sub_422E70(503);
              off_77F3F8(v185, v184);
            }
            else
            {
              v186 = sub_53A220((void *)(uint16_t)v294, v288);
              v187 = *(uint32_t *)v186;
              v293 = v186;
              (*(void (/*thiscall*/ **)(int, int))(v187 + 680))(v186, v295);
              sub_45FE80(v298, v186, (uint16_t)v278, (uint16_t)v299, v186, 0, 0);
              v188 = *(uint32_t *)(dword_8F7A24 + 12);
              if ( v188 == 4 )
              {
                sub_446130(v186, v295);
              }
              else if ( v188 == 6 )
              {
                sub_446190(v186, v295);
              }
              v189 = *this;
              HIBYTE(a2) = 0;
              (*(void (/*thiscall*/ **)(int *, char *))(v189 + 72))(this, (char *)&a2 + 3);
              if ( HIBYTE(a2) == 1 )
              {
                v190 = sub_445D00(156);
                v277 = v190;
                v311 = 5;
                if ( v190 != 0 )
                  v297 = sub_445B90(v190);
                else
                  v297 = 0;
                v191 = *this;
                v311 = -1;
                (*(void (/*thiscall*/ **)(int *))(v191 + 80))(this);
                sub_52A2A0(v302);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v186 + 60))(v186, v297);
                sub_4A0B60(&v302);
                v192 = *(uint32_t *)v297;
                i = *(uint32_t *)v186;
                v193 = (*(int (/*thiscall*/ **)(int))(v192 + 16))(v297);
                v186 = v293;
                (*(void (/*thiscall*/ **)(int, bool))(i + 148))(v293, *(uint8_t *)(v193 + 84) == 0);
                v194 = *this;
                v285 = 0;
                (*(void (/*thiscall*/ **)(int *, int *))(v194 + 80))(this, &v285);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v297 + 4))(v297, v285);
              }
              else
              {
                v195 = *this;
                HIBYTE(i) = 0;
                v293 = 0;
                v289 = 0;
                v297 = 0;
                (*(void (/*thiscall*/ **)(int *, char *))(v195 + 72))(this, (char *)&i + 3);
                (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v293);
                (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v289);
                (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v297);
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v186 + 148))(v186, HIBYTE(i));
                (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v186 + 112))(
                  v186,
                  (int16_t)v293,
                  (int16_t)v289,
                  (int16_t)v297);
              }
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v186 + 60))(v186, v292);
              sub_4A06D0(v268);
              v268 = &unk_97B6F8;
              v196 = (*(int (/*thiscall*/ **)(int *))(*this + 92))(this);
              if ( v196 > 0 )
                (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)v186 + 700))(v186, &unk_97B6F8, v196);
            }
            ++a4;
          }
          while ( a4 < (uint16_t)v300 );
        }
      }
      else
      {
        off_77F3FC(aCriticalError_2, v179);
      }
      return;
    // case 0x16 ——【推断】实体批量生成 II（带数据 blob）：sub_4ABE10 创建(+7801 头目标记)、vt+1164/1168/372/148/136/140/112/1112；aCriticalError_3 自证
    case 0x16:
      v197 = *this;
      v278 = 0xFFFF;
      v285 = 0xFFFF;
      HIBYTE(i) = 0;
      v291 = 0;
      v287 = 0;
      v286 = 0;
      v293 = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v197 + 72))(this, &v291);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v278);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v285);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v287);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v286);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
      v198 = *(this + 262149);
      if ( v198 == 0 || *(uint32_t *)(v198 + 104) == 0 )
        HIBYTE(i) = 0;
      a4 = 0;
      if ( HIBYTE(i) != 0 )
      {
        do
        {
          v199 = *this;
          v290 = 0;
          HIBYTE(v294) = 0;
          HIBYTE(a2) = 0;
          v296 = 0;
          v289 = 0;
          v302 = 0;
          v288 = nullptr;
          v299 = 0;
          v297 = 0;
          v300 = 0;
          v295 = 0;
          Block = nullptr;
          v303 = nullptr;
          (*(void (/*thiscall*/ **)(int *, int *))(v199 + 76))(this, &v289);
          (*(void (/*thiscall*/ **)(int *, uint8_t *))(*this + 72))(this, &v290);
          (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v302);
          (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v288);
          (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&v294 + 3);
          (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v297);
          v200 = *this;
          v300 = (int16_t)v297;
          (*(void (/*thiscall*/ **)(int *, int *))(v200 + 76))(this, &v297);
          v201 = *this;
          v295 = (int16_t)v297;
          (*(void (/*thiscall*/ **)(int *, int *))(v201 + 76))(this, &v297);
          v202 = *this;
          v277 = (int16_t)v297;
          (*(void (/*thiscall*/ **)(int *, char *))(v202 + 72))(this, (char *)&a2 + 3);
          (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v299);
          if ( (uint16_t)v299 != 0 )
          {
            v203 = operator new((uint16_t)v299);
            v204 = *this;
            Block = v203;
            (*(void (/*thiscall*/ **)(int *, void *, uint32_t))(v204 + 88))(this, v203, (uint16_t)v299);
          }
          (*(void (/*thiscall*/ **)(int *, uint8_t *))(*this + 72))(this, &v296);
          if ( v296 != 0 )
          {
            v205 = (char *)operator new(7u);
            if ( v205 != nullptr )
            {
              *v205 = 0;
              v205[1] = 0;
              v205[2] = 0;
              *(uint32_t *)(v205 + 3) = 0;
            }
            else
            {
              v205 = nullptr;
            }
            v206 = *this;
            v303 = v205;
            (*(void (/*thiscall*/ **)(int *, char *, int))(v206 + 88))(this, v205, 7);
          }
          (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v293);
          if ( v290 != 0 )
            v207 = v290;
          else
            v207 = 1;
          v208 = sub_4ABE10((void *)(uint16_t)v289, (void *)v207, v293);
          v209 = v208;
          if ( v208 != 0 )
          {
            if ( v291 != 0 )
              *(uint8_t *)(v208 + 7801) = 1;
            v210 = sub_45EBE0((uint16_t)v278, (uint16_t)v285);
            v211 = __RTDynamicCast(
                     v210,
                     0,
                     &CNRDObject `RTTI Type Descriptor',
                     &IRDCollisionObject `RTTI Type Descriptor',
                     0);
            v292 = v211;
            if ( v211 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v211 + 40))(v211, 17) != 0 )
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v209 + 1164))(v209, v292);
            (*(void (/*thiscall*/ **)(int, void *, uint32_t))(*(uint32_t *)v209 + 1168))(v209, v303, (uint16_t)v287);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v209 + 372))(v209, (uint16_t)v286);
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v209 + 148))(v209, HIBYTE(v294));
            sub_45FE80(
              *(uint32_t *)(*(this + 262149) + 104),
              v209,
              (uint16_t)v302,
              (uint16_t)v288,
              v209,
              0,
              0);
            if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v209 + 136))(v209, v300, v295, 0) == 0
              && (*(uint8_t (/*thiscall*/ **)(int, int *, int *, int, int, int, int, int))(*(uint32_t *)v209 + 140))(
                   v209,
                   &v300,
                   &v295,
                   v300,
                   v295,
                   200,
                   1,
                   1) == 0 )
            {
              off_77F3FC(aCriticalError_3);
            }
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v209 + 112))(v209, v300, v295, v277);
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v209 + 436))(v209) > 0 && HIBYTE(a2) == 1 )
              HIBYTE(a2) = 0;
            (*(void (/*thiscall*/ **)(int, uint32_t, void *, uint32_t))(*(uint32_t *)v209 + 1112))(
              v209,
              HIBYTE(a2),
              Block,
              (uint16_t)v299);
            v212 = *(uint32_t *)(dword_8F7A24 + 12);
            if ( v212 == 4 )
            {
              sub_446130(v209, v292);
            }
            else if ( v212 == 6 )
            {
              sub_446190(v209, v292);
            }
          }
          if ( Block != nullptr )
            j__free(Block);
          if ( v303 != nullptr )
            j__free(v303);
          ++a4;
        }
        while ( a4 < HIBYTE(i) );
      }
      return;
    // case 0x17 ——【推断】对象清理：vt+84(0)（退出可视/停止）
    case 0x17:
      v213 = *this;
      i = 0;
      a2 = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v213 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      v214 = *(this + 262149);
      if ( v214 != 0 && *(uint32_t *)(v214 + 104) != 0 )
      {
        v215 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        if ( v215 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v215 + 84))(v215, 0);
      }
      return;
    // case 0x18 —— 场景级事件 → sub_4450E0()（分发器配套，见 script_string.cpp）
    case 0x18:
      v216 = *this;
      HIBYTE(a2) = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v216 + 72))(this, (char *)&a2 + 3);
      if ( *(this + 262149) != 0 )
        sub_4450E0();
      return;
    // case 0x19 ——【推断】掉落物生成挂接：IRDActiveObject vt+868(物品id) + sub_522300 物品 + vt+136
    case 0x19:
      v217 = *this;
      v302 = 0;
      i = 0;
      a2 = 0;
      v293 = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v217 + 76))(this, &v302);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v293);
      v218 = *(this + 262149);
      if ( v218 != 0 && *(uint32_t *)(v218 + 104) != 0 )
      {
        v219 = sub_45EBE0((uint16_t)v302, (uint16_t)i);
        v220 = __RTDynamicCast(v219, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        if ( v220 != 0 )
        {
          v221 = sub_522300((void *)(uint16_t)a2, 1, 0, 0, -1, 1);
          v222 = v221;
          if ( v221 != 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v221 + 20))(v221, 1) != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v222 + 136))(v222, v220, 1, v293);
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v222 + 4))(v222, 1);
          }
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v220 + 868))(v220, (uint16_t)a2);
        }
      }
      return;
    // case 0x1A ——【推断】对象状态对同步：vt+904(b1,b2)；无判定体时补 vt+748
    case 0x1A:
      v223 = *this;
      HIBYTE(i) = 0;
      HIBYTE(a2) = 0;
      v293 = 0;
      v302 = 0;
      v289 = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v223 + 76))(this, &v293);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v302);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&i + 3);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 80))(this, &v289);
      v224 = *(this + 262149);
      if ( v224 != 0 && *(uint32_t *)(v224 + 104) != 0 )
      {
        v225 = sub_45EBE0((uint16_t)v293, (uint16_t)v302);
        v226 = __RTDynamicCast(v225, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        if ( v226 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)v226 + 904))(v226, HIBYTE(i), HIBYTE(a2));
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v226 + 308))(v226) == 0 )
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v226 + 748))(v226, v289, 1);
        }
      }
      return;
    // case 0x1B ——【推断】批量状态竞争设置：vt+236==0 或 (state 相同且 vt+248 参数更小) → vt+228(state,param,0)
    case 0x1B:
      v227 = *this;
      i = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v227 + 76))(this, &i);
      v228 = *(this + 262149);
      if ( v228 == 0 || *(uint32_t *)(v228 + 104) == 0 )
        i = 0;
      a4 = 0;
      if ( (uint16_t)i != 0 )
      {
        do
        {
          v229 = *this;
          HIBYTE(a2) = 0;
          v293 = 0;
          v302 = 0;
          v303 = nullptr;
          (*(void (/*thiscall*/ **)(int *, int *))(v229 + 76))(this, &v293);
          (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v302);
          (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
          (*(void (/*thiscall*/ **)(int *, void **))(*this + 80))(this, &v303);
          v230 = sub_45EBE0((uint16_t)v293, (uint16_t)v302);
          v231 = v230;
          if ( v230 != 0
            && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v230 + 236))(v230) == 0
             || (v232 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v231 + 236))(v231)) == HIBYTE(a2)
             && (v233 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v231 + 248))(v231)) < (unsigned int)v303) )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, void *, uint32_t))(*(uint32_t *)v231 + 228))(v231, HIBYTE(a2), v303, 0);
          }
          ++a4;
        }
        while ( a4 < (uint16_t)i );
      }
      return;
    // case 0x1C ——【字符串自证】装备破碎事件：角色槽物品 vt+196!=0 且为本地主角 → "ITEM_BREAK" 音效
    case 0x1C:
      v234 = *this;
      HIBYTE(a2) = 0;
      v302 = 0;
      i = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v234 + 76))(this, &v302);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      v235 = *(this + 262149);
      if ( v235 != 0 && *(uint32_t *)(v235 + 104) != 0 )
      {
        v236 = sub_45EBE0((uint16_t)v302, (uint16_t)i);
        v237 = __RTDynamicCast(v236, 0, &CNRDObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
        if ( v237 != 0 )
        {
          v238 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v237 + 792))(v237, HIBYTE(a2));
          if ( v238 != 0
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v238 + 196))(v238) != 0
            && dword_8F7C04 == v237 )
          {
            sub_432EA0("ITEM_BREAK", -1, 0, 0);
          }
        }
      }
      return;
    // case 0x1D ——【推断】怪物事件：IRDMonster vt+1060
    case 0x1D:
      v55 = *this;
      i = 0;
      a2 = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v55 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      v56 = *(this + 262149);
      if ( v56 != 0 && *(uint32_t *)(v56 + 104) != 0 )
      {
        v57 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v58 = __RTDynamicCast(v57, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
        if ( v58 != 0 )
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v58 + 1060))(v58);
      }
      return;
    // case 0x1E ——【推断】归属播报：两名玩家槽(sub_429830)；同名→504 号串、异名→505 号串，横幅 sub_43BEE0(-6567706)；主人 vt+1248(1)
    case 0x1E:
      v239 = *this;
      a2 = 0;
      i = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v239 + 76))(this, &a2);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &i);
      v240 = (uint32_t *)sub_429830(a2);
      v241 = (uint32_t *)sub_429830(i);
      v242 = v241;
      if ( v240 != nullptr && v241 != nullptr )
      {
        v243 = v240[49];
        if ( v243 != 0 )
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v243 + 1248))(v243, 1);
        if ( v240 == v242 )
        {
          if ( v240[10] < 0x10u )
            v244 = v240 + 5;
          else
            v244 = (uint32_t *)v240[5];
          v245 = (const char *)sub_422E70(504);
          sprintf(v304, v245, v244);
        }
        else
        {
          if ( v242[10] < 0x10u )
            v246 = v242 + 5;
          else
            v246 = (uint32_t *)v242[5];
          if ( v240[10] < 0x10u )
            v247 = v240 + 5;
          else
            v247 = (uint32_t *)v240[5];
          v248 = (const char *)sub_422E70(505);
          sprintf(v304, v248, v247, v246);
        }
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v304, -6567706, 0, -1);
      }
      return;
    // case 0x1F ——【推断】角色槽物品操作：IRDCharacter 槽(vt+792) → 物品 vt+284（耐久/消耗类）
    case 0x1F:
      v249 = *this;
      HIBYTE(a2) = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v249 + 76))(this, (char *)&v294 + 2);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 76))(this, (char *)&i + 2);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      v250 = *(this + 262149);
      if ( v250 != 0 && *(uint32_t *)(v250 + 104) != 0 )
      {
        v251 = sub_45EBE0(HIWORD(v294), HIWORD(i));
        v252 = __RTDynamicCast(v251, 0, &CNRDObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
        if ( v252 != 0 )
        {
          v253 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v252 + 792))(v252, HIBYTE(a2));
          if ( v253 != 0 )
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v253 + 284))(v253);
        }
      }
      return;
    // case 0x20 ——【推断】怪物目标绑定：IRDMonster vt+1152(目标对象)
    case 0x20:
      v45 = *this;
      i = 0;
      a2 = 0;
      Block = nullptr;
      v303 = nullptr;
      (*(void (/*thiscall*/ **)(int *, int *))(v45 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &Block);
      (*(void (/*thiscall*/ **)(int *, void **))(*this + 76))(this, &v303);
      v46 = *(this + 262149);
      if ( v46 != 0 && *(uint32_t *)(v46 + 104) != 0 )
      {
        v47 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v48 = (int *)__RTDynamicCast(v47, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
        if ( v48 != nullptr )
        {
          v49 = *v48;
          v50 = sub_45EBE0((uint16_t)Block, (uint16_t)v303);
          (*(void (/*thiscall*/ **)(int *, int))(v49 + 1152))(v48, v50);
        }
      }
      return;
    // case 0x21 —— 对象移除 → sub_45ED80（分发器配套，见 worldmap_reward.cpp）
    case 0x21:
      v254 = *this;
      i = 0;
      a2 = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v254 + 76))(this, &i);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &a2);
      v255 = *(this + 262149);
      if ( v255 != 0 && *(uint32_t *)(v255 + 104) != 0 )
      {
        v256 = sub_45EBE0((uint16_t)i, (uint16_t)a2);
        v257 = __RTDynamicCast(v256, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        if ( v257 != 0 )
          sub_45ED80(v257);
      }
      return;
    // case 0x22 —— 全场怪物参数批量同步 → sub_45EF30（分发器配套，见 worldmap_reward.cpp）
    case 0x22:
      v258 = *(this + 262149);
      if ( v258 != 0 && *(uint32_t *)(v258 + 104) != 0 )
        sub_45EF30();
      return;
    // case 0x23 —— 震屏复位 → sub_496320(dword_99FD58)（震屏管理器，docs/12）
    case 0x23:
      sub_496320(dword_99FD58);
      return;
    // case 0x25 —— 加载门推进 → sub_452700(byte)：8 门全开触发事件（见 worldmap_reward.cpp）
    case 0x25:
      v259 = *this;
      HIBYTE(a2) = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v259 + 72))(this, (char *)&a2 + 3);
      sub_452700(HIBYTE(a2));
      return;
    // case 0x26 ——【推断】WARROOM 专属事件：仅模块类型 6 处理；IRDCharacter → sub_4B09B0(byte)
    case 0x26:
      v292 = 0xFFFF;
      v298 = 0xFFFF;
      v260 = *this;
      HIBYTE(a4) = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v260 + 76))(this, &v292);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 76))(this, &v298);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a4 + 3);
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 )
      {
        v261 = *(this + 262149);
        if ( v261 != 0 && *(uint32_t *)(v261 + 104) != 0 )
        {
          v262 = sub_45EBE0((uint16_t)v292, (uint16_t)v298);
          if ( __RTDynamicCast(v262, 0, &CNRDObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0) != 0 )
            sub_4B09B0(HIBYTE(a4));
          else
            off_77F3FC((char *)&byte_6C61C4, (uint16_t)v298, (uint16_t)v292, HIBYTE(a4));
        }
      }
      else
      {
        off_77F3FC(byte_6C6200, (uint16_t)v298, (uint16_t)v292, HIBYTE(a4));
      }
      return;
    // case 0x27 ——【推断】全局通知管理器 dword_8F8548 vt+0(a2, dword)
    case 0x27:
      v8 = *this;
      i = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v8 + 80))(this, &i);
      (**(void (/*thiscall*/ ***)(int, int, int))dword_8F8548)(dword_8F8548, a2, i);
      return;
    // case 0x28 ——【推断】dword_8F8548 vt+4(a2)
    case 0x28:
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8548 + 4))(dword_8F8548, a2);
      return;
    // case 0x29 ——【推断】dword_8F8548 vt+8(a2, dword)
    case 0x29:
      v9 = *this;
      i = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v9 + 80))(this, &i);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8548 + 8))(dword_8F8548, a2, i);
      return;
    // case 0x2A ——【推断】声音事件 → sub_656080(a2)（0x656xxx 声音通道区，docs/13 §2）
    case 0x2A:
      sub_656080(a2);
      return;
    // case 0x2B ——【推断】dword_8F8548 vt+12(byte, dword)
    case 0x2B:
      v10 = *this;
      HIBYTE(a2) = 0;
      (*(void (/*thiscall*/ **)(int *, char *))(v10 + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 92))(this, &i);
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8548 + 12))(dword_8F8548, HIBYTE(a2), i);
      return;
    // case 0x2C ——【推断】dword_8F8548 vt+16(dword, byte)
    case 0x2C:
      v11 = *this;
      i = 0;
      HIBYTE(a2) = 0;
      (*(void (/*thiscall*/ **)(int *, int *))(v11 + 80))(this, &i);
      (*(void (/*thiscall*/ **)(int *, char *))(*this + 72))(this, (char *)&a2 + 3);
      (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8548 + 16))(dword_8F8548, i, HIBYTE(a2));
      return;
    // default —— 未知包类型：静默忽略
    default:
      return;
  }
}

