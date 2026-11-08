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

  // ── [段 1] 入口：取大状态机状态号 this[1639] → pThis_667，保存 nArg22=nArg2，进第一重 switch ──
  //   this = CNSwordman 对象（本函数 = CNSwordman::vt+472，class_method_slots.txt 直证）；
  //   nArg2 = 动作/事件号；pArg3 = 技能参数数组；v284/v283/v282 为 string 缓冲（最后按 >=0x10 决定 j__free）；
  //   两层 switch 结构：第一重按大状态收招/回挂，第二重(488 行)按动作号主演出
  dword_796E502 = dword_796E50;  // dword_796E502 复制自 dword_796E50
  pThis_667 = *((uint32_t *)this + 1639);  // 读 this+1639（nBigState6556）
  v284 = 15;  // 局部 v284 → 15
  v283 = 0;  // 局部 v283 → 0
  LOBYTE(v282) = 0;  // 异常展开状态号 → 0
  nArg22 = nArg2;  // nArg22 复制自 nArg2
  v288 = 0;  // 局部 v288 → 0
  switch ( pThis_667 )  // 第一重 switch：按剑魂大状态 ID 分派收招/收尾
  {
    // ── [段 2] 第一重 case 8：突进收束 —— +8216(2054 索引)==46 且 +8220==0 时 vt+612(0,0) 解围并置位 ──
    case 8:  // 【case 8】分型分支
      if ( *((uint32_t *)this + 2054) == 46 && *(this + 8220) == 0 )
      {
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);  // 虚表 +612 调用
        *(this + 8220) = 1;  // 写 this+8220 → 1
      }
      break;
    // ── [段 3] 第一重 case 10：魔能/上斩收尾 —— 子型 23/32/44 各处理 ──
    //   23 支按 +1952(1952 索引) 分 0/1 回挂 +2095..+2098 四枚动画（vt+208 逐个）；
    //   32 支按 nArg2 != 10 时回挂 +8404 起 2 件并 vt+612(0,0) 收束；
    //   24 支回挂 +2095/+2096 两件；44 且 +1952==1 且 +161==1 时 vt+612(0,0)
    case 10:  // 【case 10】分型分支
      if ( *((uint32_t *)this + 1953) == 0 )  // this+1953（nSubStateA） 等于 0
      {
        pThis_7A2 = *((uint32_t *)this + 1954);  // 读 this+1954（nSubStateB）
        switch ( pThis_7A2 )  // switch(pThis_7A2) 多路分派
        {
          case 23:  // 【case 23】分型分支
            pThis_7A0 = *((uint32_t *)this + 1952);  // 读 this+1952（nStyleSel）
            if ( pThis_7A0 != 0 )  // pThis_7A0 不等于 0
            {
              if ( pThis_7A0 == 1 )  // pThis_7A0 等于 1
              {
                (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2097));  // 虚表 +208 调用（挂动画件（槽 52））
                (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2098));  // 虚表 +208 调用（挂动画件（槽 52））
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2095));  // 虚表 +208 调用（挂动画件（槽 52））
              (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2096));  // 虚表 +208 调用（挂动画件（槽 52））
            }
            break;
          case 32:  // 【case 32】分型分支
            if ( nArg2 != 10 )  // nArg2 不等于 10
            {
              pThis_20D4 = this + 8404;  // 取 this 偏移 8404 的指针
              for ( i = 2; i != 0; --i )  // 倒序循环 0 次
                (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_20D4++);  // 虚表 +208 调用（挂动画件（槽 52））
              (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);  // 虚表 +612 调用
              nArg22 = nArg2;  // nArg22 复制自 nArg2
            }
            break;
          case 24:  // 【case 24】分型分支
            if ( nArg2 != 0 )  // nArg2 不等于 0
            {
              (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 24);  // 虚表 +1160 调用（取动画资源（槽 290））
              sub_47DD30(this);  // 复位变体
            }
            break;
          default:
            if ( pThis_7A2 == 44 && *((uint32_t *)this + 1952) == 1 && *((uint32_t *)this + 161) == 1 )
              (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);  // 虚表 +612 调用
            break;
        }
      }
      break;
    // ── [段 4] 第一重 case 12：vt+1140(11) 有参且本机时 vt+1296(11, 参) 赋值（技能号回写）──
    case 12:  // 【case 12】分型分支
      if ( *((int *)this + 2059) > 0 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
      {
        v7 = *(uint32_t *)this;  // 取虚表指针
        pThis_474 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 11);  // 虚表 +1140 调用（取技能值（槽 285））
        (*(void (/*thiscall*/ **)(char *, int, int))(v7 + 1296))(this, 11, pThis_474);  // 经虚表字节 +1296 调用
      }
      break;
    // ── [段 5] 第一重 case 15：★ 防御态收尾 —— nArg2 != 15 时播 SWD_GUARD_END 并停 +2065 对象 ──
    //   vt+212 播 SWD_GUARD_END；+2065 对象 vt+76(0) 停用（防御壳/火花对象）
    case 15:  // 【case 15】分型分支
      if ( nArg2 != 15 )  // nArg2 不等于 15
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
          this,  // 第 1 个实参 this
          "SWD_GUARD_END",  // 第 2 个实参：串 SWD_GUARD_END
          -1,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 2065) + 76))(*((uint32_t *)this + 2065), 0);
      }
      break;
    // ── [段 6] 第一重 case 16：蓄力态收尾 —— 按 +2068==1 分两支回挂动画对 ──
    //   +2068==1：+8284 非 0 → vt+252(0/1, -1) 停格；否则回挂 +8296 起 2 件；
    //   else：回挂 +8288 起 2 件（vt+208）
    case 16:  // 【case 16】分型分支
      if ( *((uint32_t *)this + 2068) == 1 )  // this+2068（pAnimPool2） 等于 1
      {
        if ( *(this + 8284) != 0 )
        {
          (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, -1);  // 虚表 +252 调用（清参（槽 63））
          (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 252))(this, 1, -1);  // 虚表 +252 调用（清参（槽 63））
        }
        else
        {
          pThis_2068 = this + 8296;  // 取 this 偏移 8296 的指针
          for ( j = 2; j != 0; --j )  // 倒序循环 0 次
            (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_2068++);  // 虚表 +208 调用（挂动画件（槽 52））
          nArg22 = nArg2;  // nArg22 复制自 nArg2
        }
      }
      else
      {
        pThis_2060 = this + 8288;  // 取 this 偏移 8288 的指针
        for ( k = 2; k != 0; --k )  // 倒序循环 0 次
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_2060++);  // 虚表 +208 调用（挂动画件（槽 52））
        nArg22 = nArg2;  // nArg22 复制自 nArg2
      }
      break;
    // ── [段 7] 第一重 case 18：nArg2 != 18 且本机时 vt+1140(8) + vt+1296(8, 参)（技能 8 回写）──
    case 18:  // 【case 18】分型分支
      if ( nArg2 != 18 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
      {
        v13 = *(uint32_t *)this;  // 取虚表指针
        pThis_4742 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 8);  // 虚表 +1140 调用（取技能值（槽 285））
        (*(void (/*thiscall*/ **)(char *, int, int))(v13 + 1296))(this, 8, pThis_4742);  // 经虚表字节 +1296 调用
      }
      break;
    // ── [段 8] 第一重 case 19/20/21：单件回挂 —— 19→+2084、20→+2087+vt+996、21→+2104 ──
    case 19:  // 【case 19】分型分支
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2084));  // 虚表 +208 调用（挂动画件（槽 52））
      break;
    case 20:  // 【case 20】分型分支
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2087));  // 虚表 +208 调用（挂动画件（槽 52））
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 996))(this);  // 虚表 +996 调用
      break;
    case 21:  // 【case 21】分型分支
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2104));  // 虚表 +208 调用（挂动画件（槽 52））
      break;
    // ── [段 9] 第一重 case 22：nArg2 != 22 时收招 —— vt+604(1) + (+2112==1 时 sub_5F0460 + 回挂 +2121)──
    case 22:  // 【case 22】分型分支
      if ( nArg2 != 22 )  // nArg2 不等于 22
      {
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 604))(this, 1);  // 虚表 +604 调用
        if ( *((uint32_t *)this + 2112) == 1 )  // this+2112（nFinishVal【推断】） 等于 1
        {
          sub_5F0460(this);  // 调: sub_5F0460 sub_431230
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2121));  // 虚表 +208 调用（挂动画件（槽 52））
        }
      }
      break;
    // ── [段 10] 第一重 case 23：抓取/巨浪态 —— 按 +2122 分 0 / 1 / 2 三支 ──
    //   1 支：+8496 非 0 → vt+252 停 + vt+216(12)/(16)；否则回挂 +8504 起 2 件，再 vt+216(12)/(16)；
    //   2 支：回挂 +2125 单件；0 支：vt+996 收束；末段 nArg22 != 23 时 vt+596(1)
    case 23:  // 【case 23】分型分支
      pThis_84A = *((uint32_t *)this + 2122);  // 读 this+2122
      if ( pThis_84A != 0 )  // pThis_84A 不等于 0
      {
        if ( pThis_84A == 1 )  // pThis_84A 等于 1
        {
          if ( *(this + 8496) != 0 )
          {
            (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, -1);  // 虚表 +252 调用（清参（槽 63））
            (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 252))(this, 1, -1);  // 虚表 +252 调用（清参（槽 63））
          }
          else
          {
            pThis_2138 = this + 8504;  // 取 this 偏移 8504 的指针
            for ( m = 2; m != 0; --m )  // 倒序循环 0 次
              (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_2138++);  // 虚表 +208 调用（挂动画件（槽 52））
          }
          (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 216))(this, 12);  // 虚表 +216 调用
          (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 216))(this, 16);  // 虚表 +216 调用
          nArg22 = nArg2;  // nArg22 复制自 nArg2
        }
        else if ( pThis_84A == 2 )  // 否则若 pThis_84A 等于 2
        {
          (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *((uint32_t *)this + 2125));  // 虚表 +208 调用（挂动画件（槽 52））
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 996))(this);  // 虚表 +996 调用
      }
      if ( nArg22 != 23 )  // nArg22 不等于 23
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 596))(this, 1);  // 虚表 +596 调用
      break;
    default:
      break;
  }
  // ── [段 11] 状态 24 归一：nArg22/nArg2 都改写为 8、pThis_667 改写 24（别名折叠）──
  if ( nArg22 == 24 )  // nArg22 等于 24
  {
    nArg22 = 8;  // 局部 nArg22 → 8
    nArg2 = 8;  // 局部 nArg2 → 8
    pThis_667 = 24;  // 局部 pThis_667 → 24
  }
  // ── [段 12] 第二重 switch(nArg22)：★ 动作主表（8/15/16/17/18/19/20/21/22/23）──
  switch ( nArg22 )  // 第二重 switch：按动作主表分派
  {
    // ── [段 13] 第二重 case 8：★ 上斩（SM_UPPER_SLASH）—— sub_4014D0 参数字符串转换 ──
    //   pThis_667 != 8 时按 sub_41C5A0(pArg3) 参数量取 +2054(2054 索引) 动作号；
    //   +2054==46 时 sub_406D60(SM_UPPER_SLASH) 并 goto LABEL_290（第二重出口）
    case 8:  // 【case 8】分型分支
      sub_4014D0((std::_String_base *)v281, this + 7044, 0, -1);  // std::string::assign
      if ( pThis_667 != 8 )  // pThis_667 不等于 8
      {
        if ( (unsigned int)sub_41C5A0(pArg3) <= 1 )
          v22 = -1;  // 局部 v22 → -1
        else
          v22 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
        *((uint32_t *)this + 2054) = v22;  // 写 this+2054（nAtkActionType） = v22
      }
      if ( *((uint32_t *)this + 2054) == 46 )  // this+2054（nAtkActionType） 等于 46
        sub_406D60("SM_UPPER_SLASH");  // std::string 从 C 串赋值
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 14] 第二重 case 15：★ 防御（SWD_GUARD + SM_GUARD + GuardSpark/GuardCircle.ani）──
    //   pThis_667 != 15 时双音效；+2060(2060 索引) 取 pArg3[1][0]；vt+144 取朝向；
    //   vt+1140/vt+1160(1) 取参；+2060 非 0 时：SWD_GUARDED 音效 + +2062=100 + sub_47EF20 读表，
    //   vt+876 双段位移（-1000*v25/+2062 反算） + vt+888 帧长；按 pArg3[1][4] 夹取 [22,71] 后
    //   sub_423A80(23, 6, 值-22, 49) 算落点；sub_42FCB0(228)/sub_44B6C0(284) 双门控建
    //   GuardSpark.ani 与 GuardCircle.ani（各 sub_45FE80 挂接 + vt+148 时刻同步 + vt+112 落坐标）；
    //   else 支为无格挡：vt+876 全零 + vt+888 帧长 + vt+896 挂帧；
    //   尾段 vt+196(+1554 表首参) + sub_4AECE0(+120 对象, 格挡与否) + sub_4939E0(…,1)；
    //   pThis_667 != 15 时按 +2060 置 +2061 或 +2063（sub_699000 时钟 + sub_47E9D0(2) 时长），
    //   +2065 惰性建（sub_510230(12,0,-1)）并 sub_5E5330/sub_5E5F00(12, 参) + vt+56 挂接
    case 15:  // 【case 15】分型分支
      if ( pThis_667 != 15 )  // pThis_667 不等于 15
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
          this,  // 第 1 个实参 this
          "SWD_GUARD",  // 第 2 个实参：串 SWD_GUARD
          -1,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
          this,  // 第 1 个实参 this
          "SM_GUARD",  // 第 2 个实参：串 SM_GUARD
          -1,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
      }
      v23 = *(uint32_t *)this;  // 取虚表指针
      // ── [段 15] 第二重 case 15：★ 防御主处理（SWD_GUARD/SM_GUARD + SWD_GUARDED + GuardSpark/GuardCircle.ani）──
      //   +2060 取 pArg3[1][0]；vt+144 取朝向；+2062 帧长、vt+876 双段位移、vt+888 帧长；
      //   pArg3[1][4] 夹取 [22,71] 后 sub_423A80(23,6,值-22,49) 算落点，再 sub_42FCB0/sub_44B6C0 双门控建两枚格挡特效件
      *((uint32_t *)this + 2060) = **(uint32_t **)(pArg3 + 4);  // 写 this+2060（nParamCnt【推断】） = **(uint32_t **)(pArg3 +
      (*(void (/*thiscall*/ **)(char *, uint32_t))(v23 + 144))(this, *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12));  // 经虚表字节 +144 调用
      pThis_488 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 1);  // 虚表 +1160 调用（取动画资源（槽 290））
      pThis_48816 = pThis_488;  // pThis_48816 复制自 pThis_488
      pThis_4743 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 1);  // 虚表 +1140 调用（取技能值（槽 285））
      v256 = 0;  // 局部 v256 → 0
      v255 = 0;  // 局部 v255 → 0
      if ( *((uint32_t *)this + 2060) != 0 )  // this+2060 不等于 0
      {
        v261 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8) != 0;
        (*(void (/*thiscall*/ **)(char *, const char *, int))(*(uint32_t *)this + 212))(this, "SWD_GUARDED", -1);  // 虚表 +212 调用（播放动作/播报（槽 53））：标签 SWD_GUARDED
        v25 = 0;  // 局部 v25 → 0
        *((uint32_t *)this + 2062) = 100;  // 写 this+2062（nVariantVal【推断】） = 100
        if ( !v261 )
        {
          v25 = sub_47EF20(0, pThis_4743, -1, -1, 11);  // 存 读技能数值表（16 字节条目）
          *((uint32_t *)this + 2062) = sub_47EF20(1, pThis_4743, -1, -1, 11);  // 写 this+2062（nVariantVal【推断】） = sub_47EF20(1, pThis_4743
        }
        (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          v25,  // 第 3 个实参
          v25,  // 第 4 个实参
          0,  // 第 5 个实参
          -1000 * v25 / *((uint32_t *)this + 2062),  // 第 6 个实参
          1);  // 第 7 个实参
        (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
        v26 = *(uint32_t *)this;  // 取虚表指针
        pThis_98 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);  // 虚表 +152 调用（取动作件（槽 38））
        v28 = sub_432E50(pThis_98);  // 存 关系码对调映射 【关系码对调映射】0 与 1 互换与 2 与 3 互换，其余返回 4
        (*(void (/*thiscall*/ **)(char *, int))(v26 + 896))(this, v28);  // 经虚表字节 +896 调用
        v29 = *(uint32_t *)(pArg3 + 4);  // 读 pArg3+4 处 4 字节
        v30 = *(uint32_t *)(v29 + 4);  // 读 v29+4 处 4 字节
        if ( v30 <= 22 )
        {
          v31 = 22;  // 局部 v31 → 22
        }
        else if ( v30 >= 71 )
        {
          v31 = 71;  // 局部 v31 → 71
        }
        else
        {
          v31 = *(uint32_t *)(v29 + 4);  // 读 v29+4 处 4 字节
        }
        v32 = sub_423A80(23, 6, v31 - 22, 49);  // 存 区间线性插值取整 sub_4049C0
        if ( (*(int (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 152))(this, 0, 0) != 0 )  // 虚表 +152 调用（取动作件（槽 38））
          pThis_78 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 120))(this) + v32;  // 虚表 +120 调用（取帧时长（槽 30））
        else
          pThis_78 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 120))(this) - v32;  // 虚表 +120 调用（取帧时长（槽 30））
        pThis_7C = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 124))(this);  // 虚表 +124 调用（取帧时长累加（槽 31））
        pThis_80 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this) + v31;  // 虚表 +128 调用（取帧数（槽 32））
        LOBYTE(v288) = 1;  // 异常展开状态号 → 1
        if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
        {
          if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
            LOBYTE(pThis_5B) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
          else
            pThis_5B = *((uint32_t *)this + 91);  // 读 this+91（pAnimNameStr【推断】）
          v34 = sub_431920(pThis_5B, (char)"Effect/Animation/GuardSpark.ani", 1);  // 存 建动画件 Effect/Animation/GuardSpark.ani
        }
        else
        {
          v34 = 0;  // 局部 v34 → 0
        }
        LOBYTE(v288) = 2;  // 异常展开状态号 → 2
        if ( sub_44B6C0(284) != 0 )  // 若 CRT 一次性池初始化 2(284) 不等于 0
          pObj2 = sub_44E1F0(v34, 1);  // 存 CNRDPooledObject
        else
          pObj2 = 0;  // 局部 pObj2 → 0
        pThis_1D = *((uint32_t *)this + 29);  // 读 this+29（pSessionCtx【推断】）
        LOBYTE(v288) = 0;  // 异常展开状态号 → 0
        sub_45FE80(pThis_1D, pObj2, 2, 0, pObj2, (int)this, 0);  // 注册场景对象
        v37 = *(uint32_t *)pObj2;  // 取 pObj2 首字段
        pThis_982 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);  // 虚表 +152 调用（取动作件（槽 38））
        (*(void (/*thiscall*/ **)(int, int))(v37 + 148))(pObj2, pThis_982);  // 经虚表字节 +148 调用
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pThis_78, pThis_7C, pThis_80);
        LOBYTE(v288) = 3;  // 异常展开状态号 → 3
        if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
        {
          if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
            LOBYTE(pThis_5B2) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
          else
            pThis_5B2 = *((uint32_t *)this + 91);  // 读 this+91（pAnimNameStr【推断】）
          v40 = sub_431920(pThis_5B2, (char)"Effect/Animation/GuardCircle.ani", 1);  // 存 建动画件 Effect/Animation/GuardCircle.ani
        }
        else
        {
          v40 = 0;  // 局部 v40 → 0
        }
        LOBYTE(v288) = 4;  // 异常展开状态号 → 4
        if ( sub_44B6C0(284) != 0 )  // 若 CRT 一次性池初始化 2(284) 不等于 0
          pObj = sub_44E1F0(v40, 1);  // 存 CNRDPooledObject
        else
          pObj = 0;  // 局部 pObj → 0
        pThis_1D2 = *((uint32_t *)this + 29);  // 读 this+29（pSessionCtx【推断】）
        LOBYTE(v288) = 0;  // 异常展开状态号 → 0
        sub_45FE80(pThis_1D2, pObj, 2, 0, pObj, (int)this, 0);  // 注册场景对象
        v43 = *(uint32_t *)pObj;  // 取 pObj 首字段
        pThis_983 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);  // 虚表 +152 调用（取动作件（槽 38））
        (*(void (/*thiscall*/ **)(int, int))(v43 + 148))(pObj, pThis_983);  // 经虚表字节 +148 调用
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 112))(pObj, pThis_78, pThis_7C, pThis_80);
        pThis_488 = pThis_48816;  // pThis_488 复制自 pThis_48816
        *(this + 8256) = 0;  // 写 this+8256 → 0
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(this, 0, 0, 0, 0);  // 虚表 +876 调用（位移下发（槽 219））
        (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
        (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚表 +896 调用（帧组设置（槽 224））
      }
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));  // 虚表 +196 调用（播放语音（槽 49））
      sub_4AECE0(*((void **)this + 30), *((uint32_t *)this + 2060) != 0);  // 【解读】 【推断】动画切换: sub_491C70
      sub_4939E0(*((uint32_t *)this + 30), 1);  // 播放/暂停级联
      LOBYTE(fArg5) = 0;  // 异常展开状态号 → 0
      *((uint32_t *)this + 2061) = 0;  // 写 this+2061（nVariantSel【推断】） = 0
      if ( pThis_667 != 15 )  // pThis_667 不等于 15
      {
        if ( *((uint32_t *)this + 2060) == 0 )  // this+2060（nParamCnt【推断】） 等于 0
          *((uint32_t *)this + 2061) = sub_47E9D0(pThis_488, 0);  // 写 this+2061（nVariantSel【推断】） = sub_47E9D0(pThis_488, 0)
        if ( *((uint32_t *)this + 2060) == 1 )  // this+2060（nParamCnt【推断】） 等于 1
        {
          *((uint32_t *)this + 2063) = -1;  // 写 this+2063（nParam2【推断】） = -1
        }
        else
        {
          pThis_4882 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 2);  // 虚表 +1160 调用（取动画资源（槽 290））
          v46 = sub_47E9D0(pThis_4882, 0);  // 存 读技能表（14 字节条目，索引=pThis_4882）
          *((uint32_t *)this + 2063) = sub_699000((int)(this + 64)) + v46;  // 写 this+2063（nParam2【推断】） = sub_699000((int)(this +
        }
        if ( *((uint32_t *)this + 2065) == 0 )  // this+2065（nPhaseA【推断】） 等于 0
        {
          LOBYTE(v288) = 5;  // 异常展开状态号 → 5
          if ( operator new(0x60u) != nullptr )
            v47 = (int *)sub_510230(12, 0, -1);  // 存 CNChangeActiveProperty
          else
            v47 = nullptr;  // v47 置空
          *((uint32_t *)this + 2065) = v47;  // 写 this+2065（nPhaseA【推断】） = v47
          v48 = *v47;  // 取 v47 的首字段
          LOBYTE(v288) = 0;  // 异常展开状态号 → 0
          *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v48 + 64))(v47) + 36) = 0;  // 经虚表字节 +64 调用
        }
        v49 = sub_47EF20(4, pThis_4743, -1, -1, 11);  // 存 读技能数值表（16 字节条目）
        sub_5E5330(*((uint32_t *)this + 2065));  // 调: sub_5E5330
        sub_5E5F00(12, v49);  // 调: sub_5E5F00 sub_5E5E60
        (*(void (/*thiscall*/ **)(uint32_t, char *, char *, uint32_t, uint32_t, uint32_t, int))(**((uint32_t **)this + 2065) + 56))(
          *((uint32_t *)this + 2065),  // 第 1 个实参 this
          this,  // 第 2 个实参
          this,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          -1);  // 第 7 个实参
      }
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 16] 第二重 case 16：★ 蓄力斩（HardAttackOnCharge/HardAttack.ani 四态）──
    //   pArg3[1][0] → +2068；非 0 时 1 → vt+216(11)+音效；2 → +2069=1+音效；
    //   +2068 落 0/2 时 vt+1160(6)+vt+996 收束；+2068==2 时 +2070=1；
    //   +2068==1：建 HardAttackOnCharge1/2.ani（各两路内联/堆指针）；否则建 HardAttack1/2.ani；
    //   switch(+2068)：LABEL_160 为出口（+2068==2 时 vt+996）；0/2 时再回挂处理
    case 16:  // 【case 16】分型分支
      // ── [段 17] 第二重 case 16：★ 蓄力斩主处理（+2068 三态 + HardAttackOnCharge/HardAttack.ani 四件）──
      //   1 → vt+216(11)+音效；2 → +2069=1+音效；0/2 → vt+1160(6)+vt+996 收束；
      //   +2068==1 建 HardAttackOnCharge1/2.ani，否则建 HardAttack1/2.ani（各含内联/堆指针二路）
      v50 = **(uint32_t **)(pArg3 + 4);  // 二级解引用取 pArg3+4
      *((uint32_t *)this + 2068) = v50;  // 写 this+2068（pAnimPool2） = v50
      if ( v50 != 0 )  // v50 不等于 0
      {
        v51 = *(uint32_t *)this;  // 取虚表指针
        if ( v50 == 1 )  // v50 等于 1
        {
          (*(void (/*stdcall*/ **)(int))(v51 + 216))(11);  // 经虚表字节 +216 调用
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
            this,  // 第 1 个实参 this
            "SM_GUE_CHARGE",  // 第 2 个实参：串 SM_GUE_CHARGE
            12,  // 第 3 个实参
            0,  // 第 4 个实参
            0);  // 第 5 个实参
        }
        else
        {
          (*(void (/*stdcall*/ **)(int))(v51 + 216))(12);  // 经虚表字节 +216 调用
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
            this,  // 第 1 个实参 this
            "R_SM_GUE",  // 第 2 个实参：串 R_SM_GUE
            11,  // 第 3 个实参
            0,  // 第 4 个实参
            0);  // 第 5 个实参
          *(this + 8304) = 0;  // 写 this+8304 → 0
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
          this,  // 第 1 个实参 this
          "R_SM_GUE",  // 第 2 个实参：串 R_SM_GUE
          11,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
      }
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 4));  // 虚表 +196 调用（播放语音（槽 49））
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139));  // 虚表 +344 调用（清参（槽 86））
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        0,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 2, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚表 +896 调用（帧组设置（槽 224））
      pThis_814 = *((uint32_t *)this + 2068);  // 读 this+2068（pAnimPool2）
      if ( pThis_814 == 0 || pThis_814 == 2 )
      {
        pThis_184 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
        pThis_4744 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 5);  // 虚表 +1140 调用（取技能值（槽 285））
        pThis_4883 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 5);  // 虚表 +1160 调用（取动画资源（槽 290））
        *((float *)this + 97) = (float)sub_47EFD0(pThis_4883, 0.0, pThis_4744, pThis_184, pThis_184, 0);  // this 浮点槽 +97 写入 技能表槽位设置
      }
      if ( *((uint32_t *)this + 2068) == 2 )  // this+2068（pAnimPool2） 等于 2
      {
        pThis_4745 = (*(int (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 1140))(this, 6, -1);  // 虚表 +1140 调用（取技能值（槽 285））
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1160))(this);  // 虚表 +1160 调用（取动画资源（槽 290））
        v55 = sub_47EF20(6, 0, pThis_4745, -1, 11);  // 存 读技能数值表（16 字节条目）
        v56 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
        *((uint32_t *)this + 2070) = v56;  // 写 this+2070（pStatusObj【推断】） = v56
        *((float *)this + 97) = (double)(int)sub_423A80(0, v55, v56, dword_7959F8) + *((float *)this + 97);
      }
      if ( *((uint32_t *)this + 2068) == 1 )  // this+2068（pAnimPool2） 等于 1
      {
        pThis_20682 = this + 8296;  // 取 this 偏移 8296 的指针
        if ( *((uint32_t *)this + 2074) == 0 )  // this+2074（nOffsetVal【推断】） 等于 0
        {
          LOBYTE(v288) = 6;  // 异常展开状态号 → 6
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttackOnCharge1.ani", 1);  // 存 建动画件 Effect/Animation/HardAttackOnCharge1.ani
            else
              pThis_6C = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttackOnCharge1.ani", 1);  // 存 建动画件 Effect/Animation/HardAttackOnCharge1.ani
          }
          else
          {
            pThis_6C = 0;  // 局部 pThis_6C → 0
          }
          *pThis_20682 = pThis_6C;
          LOBYTE(v288) = 7;  // 异常展开状态号 → 7
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C2 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttackOnCharge2.ani", 1);  // 存 建动画件 Effect/Animation/HardAttackOnCharge2.ani
            else
              pThis_6C2 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttackOnCharge2.ani", 1);  // 存 建动画件 Effect/Animation/HardAttackOnCharge2.ani
          }
          else
          {
            pThis_6C2 = 0;  // 局部 pThis_6C2 → 0
          }
          LOBYTE(v288) = 0;  // 异常展开状态号 → 0
          *((uint32_t *)this + 2075) = pThis_6C2;  // 写 this+2075（pHoldObj【推断】） = pThis_6C2
        }
        v60 = 0;  // 局部 v60 → 0
        do
        {
          v61 = v60 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
            this,  // 第 1 个实参 this
            v60 + 1,  // 第 2 个实参
            *pThis_20682,  // 第 3 个实参
            0,  // 第 4 个实参
            0,  // 第 5 个实参
            0,  // 第 6 个实参
            0);  // 第 7 个实参
          v60 = v61;  // v60 复制自 v61
          ++pThis_20682;  // pThis_20682 自增
        }
        while ( v61 < 2 );
      }
      else
      {
        pThis_20602 = this + 8288;  // 取 this 偏移 8288 的指针
        if ( *((uint32_t *)this + 2072) == 0 )  // this+2072（nGrabDataVal【推断】） 等于 0
        {
          LOBYTE(v288) = 8;  // 异常展开状态号 → 8
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C3 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttack1.ani", 1);  // 存 建动画件 Effect/Animation/HardAttack1.ani
            else
              pThis_6C3 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttack1.ani", 1);  // 存 建动画件 Effect/Animation/HardAttack1.ani
          }
          else
          {
            pThis_6C3 = 0;  // 局部 pThis_6C3 → 0
          }
          *pThis_20602 = pThis_6C3;
          LOBYTE(v288) = 9;  // 异常展开状态号 → 9
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C4 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/HardAttack2.ani", 1);  // 存 建动画件 Effect/Animation/HardAttack2.ani
            else
              pThis_6C4 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/HardAttack2.ani", 1);  // 存 建动画件 Effect/Animation/HardAttack2.ani
          }
          else
          {
            pThis_6C4 = 0;  // 局部 pThis_6C4 → 0
          }
          LOBYTE(v288) = 0;  // 异常展开状态号 → 0
          *((uint32_t *)this + 2073) = pThis_6C4;  // 写 this+2073（bModeFlag【推断】） = pThis_6C4
        }
        v65 = 0;  // 局部 v65 → 0
        do
        {
          v66 = v65 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
            this,  // 第 1 个实参 this
            v65 + 1,  // 第 2 个实参
            *pThis_20602,  // 第 3 个实参
            0,  // 第 4 个实参
            0,  // 第 5 个实参
            0,  // 第 6 个实参
            0);  // 第 7 个实参
          v65 = v66;  // v65 复制自 v66
          ++pThis_20602;  // pThis_20602 自增
        }
        while ( v66 < 2 );
      }
      pThis_8142 = *((uint32_t *)this + 2068);  // 读 this+2068（pAnimPool2）
      // ── [段 18] 第二重 case 16 之内层 switch(+2068)：0/1/2 三态动画选型与 LABEL_160 出口 ──
      switch ( pThis_8142 )  // switch(pThis_8142) 多路分派
      {
        case 0:  // 【case 0】分型分支
          *(this + 8276) = 0;  // 写 this+8276 → 0
          goto LABEL_160;  // 转到 LABEL_160
        case 1:  // 【case 1】分型分支
          pThis_1E = *((uint32_t *)this + 30);  // 读 this+30（pAnimObj【推断】）
          v69 = sub_491C70(pThis_1E, 0);  // 存 帧时刻换算
          sub_493A60(pThis_1E, v69);  // 时间推进包装
          sub_4939E0(*((uint32_t *)this + 30), 1);  // 播放/暂停级联
          break;
        case 2:  // 【case 2】分型分支
          sub_4AECE0(*((void **)this + 30), 1);  // 【解读】 【推断】动画切换: sub_491C70
          sub_4939E0(*((uint32_t *)this + 30), 0);  // 播放/暂停级联
          break;
        default:
          goto LABEL_160;  // 转到 LABEL_160
      }
      LOBYTE(fArg5) = 0;  // 异常展开状态号 → 0
LABEL_160:
      if ( *((uint32_t *)this + 2068) != 2 )  // this+2068 不等于 2
        *(this + 8284) = 0;  // 写 this+8284 → 0
      pThis_8143 = *((uint32_t *)this + 2068);  // 读 this+2068（pAnimPool2）
      if ( pThis_8143 == 0 || pThis_8143 == 2 )
      {
        v71 = *(uint32_t *)this;  // 取虚表指针
        pThis_494 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);  // 虚表 +1172 调用（取动作数据（槽 293））
        (*(void (/*thiscall*/ **)(char *, int))(v71 + 212))(this, pThis_494);  // 经虚表字节 +212 调用
        pThis_4942 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);  // 虚表 +1172 调用（取动作数据（槽 293））
        sub_4015C0(pThis_4942, strlen((const char *)pThis_4942));  // 【std::string构造赋值】
      }
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 19] 第二重 case 17：★ 居合/拔刀 —— sub_47E9D0 三读表 + vt+1172 动作串 ──
    //   本机时 vt+1172(0,-1) 与 vt+1172(2) 取两串 → vt+212；vt+388 取参 → 1948 行 vt+888 帧长
    case 17:  // 【case 17】分型分支
      (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
        this,  // 第 1 个实参 this
        "SM_HITBACK",  // 第 2 个实参：串 SM_HITBACK
        -1,  // 第 3 个实参
        0,  // 第 4 个实参
        0);  // 第 5 个实参
      if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 604))(this, 1);  // 虚表 +604 调用
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, **(uint32_t **)(pArg3 + 4));  // 虚表 +144 调用
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 8));  // 虚表 +196 调用（播放语音（槽 49））
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 152);  // 虚表 +344 调用（清参（槽 86））
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        0,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 2, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚表 +896 调用（帧组设置（槽 224））
      v74 = *(uint32_t *)this;  // 取虚表指针
      pThis_4943 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);  // 虚表 +1172 调用（取动作数据（槽 293））
      (*(void (/*thiscall*/ **)(char *, int))(v74 + 212))(this, pThis_4943);  // 经虚表字节 +212 调用
      pThis_4944 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);  // 虚表 +1172 调用（取动作数据（槽 293））
      sub_406D60(pThis_4944);  // std::string 从 C 串赋值
      pThis_1842 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
      pThis_4746 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 7);  // 虚表 +1140 调用（取技能值（槽 285））
      pThis_4884 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 7);  // 虚表 +1160 调用（取动画资源（槽 290））
      *((float *)this + 97) = (float)sub_47EFD0(pThis_4884, COERCE_FLOAT(1), pThis_4746, pThis_1842, pThis_1842, 0);  // this 浮点槽 +97 写入 技能表槽位设置
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 20] 第二重 case 18：★ 三段斩/连斩 —— 按 +2077 连击数分 2 档 ──
    //   vt+1160/+1140(8) 取参；+2077>=2 时另一路；sub_47E9D0(8,0) 读表 → 963 行；
    //   再按 +2077 分 0/1/2 三支（1017/1019/1026 行）设不同帧长
    case 18:  // 【case 18】分型分支
      v80 = *(uint32_t *)this;  // 取虚表指针
      *((uint32_t *)this + 2077) = **(uint32_t **)(pArg3 + 4);  // 写 this+2077（nHoldPosY【推断】） = **(uint32_t **)(pArg3 +
      (*(void (/*thiscall*/ **)(char *, uint32_t))(v80 + 144))(this, *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));  // 经虚表字节 +144 调用
      pThis_612 = *((uint32_t *)this + 1554);  // 读 this+1554（pTbl6216【推断】）
      if ( *((int *)this + 2077) >= 2 )
        v82 = *(uint32_t *)(pThis_612 + 16);  // 读 pThis_612+16 处 4 字节
      else
        v82 = *(uint32_t *)(pThis_612 + 12);  // 读 pThis_612+12 处 4 字节
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 196))(v82);  // 虚表 +196 调用（播放语音（槽 49））
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(  // 虚表 +344 调用（清参（槽 86））
        this,  // 第 1 个实参 this
        *((uint32_t *)this + 139) + 152 * (*((uint32_t *)this + 2077) + 2));  // 第 2 个实参
      pThis_4885 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 8);  // 虚表 +1160 调用（取动画资源（槽 290））
      pThis_4747 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 8);  // 虚表 +1140 调用（取技能值（槽 285））
      if ( *((int *)this + 2077) < 2 )
      {
        pThis_2A0 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 672))(this, 3);  // 虚表 +672 调用
        v263 = 1000.0 / (double)sub_4954C0(pThis_2A0);
        *((uint32_t *)this + 2079) = (uint64_t)((double)sub_47E9D0(pThis_4885, 1u) * v263);  // 写 this+2079（nHoldSrc【推断】） = (uint64_t)((double)sub_4
        *((uint32_t *)this + 2080) = (uint64_t)((double)sub_47E9D0(pThis_4885, 2u) * v263);  // 写 this+2080（pHoldHost【推断】） = (uint64_t)((double)sub_4
        *((uint32_t *)this + 2081) = (uint64_t)((double)sub_47E9D0(pThis_4885, 3u) * v263);  // 写 this+2081（bHoldMode【推断】） = (uint64_t)((double)sub_4
      }
      pThis_1843 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
      *((float *)this + 97) = (float)sub_47EFD0(pThis_4885, *((float *)this + 2077), pThis_4747, pThis_1843, pThis_1843, 0);  // this 浮点槽 +97 写入 技能表槽位设置
      v87 = sub_47E9D0(pThis_4885, 0);  // 存 读技能表（14 字节条目，索引=pThis_4885）
      if ( *((int *)this + 2077) >= 2 )
        (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          0,  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
      else
        (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
          this,  // 第 1 个实参 this
          0,  // 第 2 个实参
          v87,  // 第 3 个实参
          v87,  // 第 4 个实参
          0,  // 第 5 个实参
          -700,  // 第 6 个实参
          1);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 2, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
      v88 = *(uint32_t *)this;  // 取虚表指针
      pThis_984 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);  // 虚表 +152 调用（取动作件（槽 38））
      (*(void (/*thiscall*/ **)(char *, int))(v88 + 896))(this, pThis_984);  // 经虚表字节 +896 调用
      pThis_81D = *((uint32_t *)this + 2077);  // 读 this+2077（nHoldPosY【推断】）
      *((uint32_t *)this + 2078) = -1;  // 写 this+2078（nHoldPosZ【推断】） = -1
      *((uint32_t *)this + 2082) = -200;  // 写 this+2082（f_2088【推断】） = -200
      if ( pThis_81D != 0 )  // pThis_81D 不等于 0
      {
        if ( pThis_81D == 1 )  // pThis_81D 等于 1
        {
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
            this,  // 第 1 个实参 this
            "SM_TRIPLE2",  // 第 2 个实参：串 SM_TRIPLE2
            -1,  // 第 3 个实参
            0,  // 第 4 个实参
            0);  // 第 5 个实参
        }
        else if ( pThis_81D == 2 )  // 否则若 pThis_81D 等于 2
        {
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
            this,  // 第 1 个实参 this
            "SM_TRIPLE3",  // 第 2 个实参：串 SM_TRIPLE3
            -1,  // 第 3 个实参
            0,  // 第 4 个实参
            0);  // 第 5 个实参
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
          this,  // 第 1 个实参 this
          "SM_TRIPLE1",  // 第 2 个实参：串 SM_TRIPLE1
          -1,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
      }
      v91 = *(uint32_t *)this;  // 取虚表指针
      if ( *((uint32_t *)this + 2077) == 2 )  // this+2077（nHoldPosY【推断】） 等于 2
      {
        v92 = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(v91 + 1172))(this, 1, -1, 0, 0);  // 经虚表字节 +1172 调用
        (*(void (/*thiscall*/ **)(char *, int))(v91 + 212))(this, v92);  // 经虚表字节 +212 调用
        pThis_4945 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);  // 虚表 +1172 调用（取动作数据（槽 293））
      }
      else
      {
        v94 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(v91 + 1172))(this, 0, -1, 0, 0);  // 经虚表字节 +1172 调用
        (*(void (/*thiscall*/ **)(char *, int))(v91 + 212))(this, v94);  // 经虚表字节 +212 调用
        pThis_4945 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);  // 虚表 +1172 调用（取动作数据（槽 293））
      }
      sub_406D60(pThis_4945);  // std::string 从 C 串赋值
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 21] 第二重 case 19：★ 瞬间斩（MomentarySlash.ani）—— +2084==0 时建件 ──
    //   vt+1172(2) + vt+388 取参 + vt+1140/+1160(9) 取参 → （1104 行）
    case 19:  // 【case 19】分型分支
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, **(uint32_t **)(pArg3 + 4));  // 虚表 +144 调用
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 20));  // 虚表 +196 调用（播放语音（槽 49））
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 760);  // 虚表 +344 调用（清参（槽 86））
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        0,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 2, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚表 +896 调用（帧组设置（槽 224））
      if ( *((uint32_t *)this + 2084) == 0 )  // this+2084（pVtStack【推断】） 等于 0
      {
        LOBYTE(v288) = 10;  // 异常展开状态号 → 10
        if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
        {
          if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
            pThis_6C5 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/MomentarySlash.ani", 1);  // 存 建动画件 Effect/Animation/MomentarySlash.ani
          else
            pThis_6C5 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/MomentarySlash.ani", 1);  // 存 建动画件 Effect/Animation/MomentarySlash.ani
        }
        else
        {
          pThis_6C5 = 0;  // 局部 pThis_6C5 → 0
        }
        LOBYTE(v288) = 0;  // 异常展开状态号 → 0
        *((uint32_t *)this + 2084) = pThis_6C5;  // 写 this+2084（pVtStack【推断】） = pThis_6C5
      }
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        *((uint32_t *)this + 2084),  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
        this,  // 第 1 个实参 this
        "SM_BAL_READY",  // 第 2 个实参：串 SM_BAL_READY
        -1,  // 第 3 个实参
        0,  // 第 4 个实参
        0);  // 第 5 个实参
      v96 = *(uint32_t *)this;  // 取虚表指针
      *(this + 8332) = 0;  // 写 this+8332 → 0
      *(this + 8333) = 0;  // 写 this+8333 → 0
      v97 = (void *)(*(int (/*thiscall*/ **)(char *, int))(v96 + 1172))(this, 2);  // 经虚表字节 +1172 调用
      sub_406D60(v97);  // std::string 从 C 串赋值
      pThis_1844 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
      pThis_4748 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 9);  // 虚表 +1140 调用（取技能值（槽 285））
      pThis_4886 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 9);  // 虚表 +1160 调用（取动画资源（槽 290））
      *((float *)this + 97) = (float)sub_47EFD0(pThis_4886, 0.0, pThis_4748, pThis_1844, pThis_1844, 0);  // this 浮点槽 +97 写入 技能表槽位设置
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 22] 第二重 case 20：★ 波动剑（NormalWave/IceWave/FireWave.ani 三色）──
    //   pArg3[1][1]+4 != 4 的门控；vt+1140(+2085) 取参；sub_4B1C40 与 sub_495540 读表算帧长；
    //   +2085==20 → NormalWave.ani + sub_4015C0(SM_WAVE,7)；21 → IceWave.ani + sub_406D60(SM_ICEWAVE)；
    //   22 或 +2094==0 → FireWave.ani + Particle/FireWave.ptl + sub_406D60(SM_FIREWAVE)；
    //   LABEL_216/226/227 为三色汇合点，末段 sub_47EF20(+2085,…)×0.01 写 v280
    case 20:  // 【case 20】分型分支
      *((uint32_t *)this + 2085) = **(uint32_t **)(pArg3 + 4);  // 写 this+2085（pAnimA【推断】） = **(uint32_t **)(pArg3 +
      *(this + 8344) = 0;  // 写 this+8344 → 0
      v101 = *(uint32_t *)(pArg3 + 4);  // 读 pArg3+4 处 4 字节
      if ( *(uint32_t *)(v101 + 4) != 4 )
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 144))(this, *(uint32_t *)(v101 + 4));  // 虚表 +144 调用
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 24));  // 虚表 +196 调用（播放语音（槽 49））
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        0,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 4, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚表 +896 调用（帧组设置（槽 224））
      pThis_4749 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 2085));  // 虚表 +1140 调用（取技能值（槽 285））
      (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 1160))(this, *((uint32_t *)this + 2085), pThis_4749);  // 虚表 +1160 调用（取动画资源（槽 290））
      v103 = sub_4B1C40(v255);  // 存 14 字节表按 1 基索引取值 基址 *
      v255 = 1;  // 局部 v255 → 1
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 992))(this, v103);  // 虚表 +992 调用
      *((uint32_t *)this + 2090) = v103;  // 写 this+2090（pPickInfo8360【推断】） = v103
      for ( n = 1; n < 4; ++n )
      {
        pThis_82A = *((uint32_t *)this + 2090) - *(uint32_t *)(sub_4924C0(n) + 48);
        *((uint32_t *)this + 2090) = pThis_82A;  // 写 this+2090（pPickInfo8360【推断】） = pThis_82A
      }
      pThis_680 = 1000 * pThis_82A / *((uint32_t *)this + 1664);  // 乘算后按 this+1664 归一
      v107 = 0;  // 局部 v107 → 0
      v286 = 15;  // 局部 v286 → 15
      Block[4] = nullptr;
      LOBYTE(Block[0]) = 0;
      *((uint32_t *)this + 2090) = pThis_680;  // 写 this+2090（pPickInfo8360【推断】） = pThis_680
      pThis_825 = *((uint32_t *)this + 2085);  // 读 this+2085（pAnimA【推断】）
      LOBYTE(v288) = 11;  // 异常展开状态号 → 11
      if ( pThis_825 == 20 )  // pThis_825 等于 20
      {
        if ( *((uint32_t *)this + 2092) == 0 )  // this+2092（nCoordB【推断】） 等于 0
        {
          LOBYTE(v288) = 12;  // 异常展开状态号 → 12
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C6 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/NormalWave.ani", 1);  // 存 建动画件 Effect/Animation/NormalWave.ani
            else
              pThis_6C6 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/NormalWave.ani", 1);  // 存 建动画件 Effect/Animation/NormalWave.ani
          }
          else
          {
            pThis_6C6 = 0;  // 局部 pThis_6C6 → 0
          }
          LOBYTE(v288) = 11;  // 异常展开状态号 → 11
          *((uint32_t *)this + 2092) = pThis_6C6;  // 写 this+2092（nCoordB【推断】） = pThis_6C6
        }
        v110 = *(uint32_t *)this;  // 取虚表指针
        *((uint32_t *)this + 2087) = *((uint32_t *)this + 2092);  // 写 this+2087（nPhaseParity【推断】） = *((uint32_t *)this + 209
        *((uint32_t *)this + 2088) = 20001;  // 写 this+2088（nRideHost8352【推断】） = 20001
        *((uint32_t *)this + 2089) = (*(int (/*thiscall*/ **)(char *, const char *))(v110 + 588))(  // 经虚表字节 +588 调用
                                     this,  // 第 1 个实参 this
                                     "Particle/NormalWave.ptl");  // 第 2 个实参：串 Particle/NormalWave.ptl
        sub_4015C0("SM_WAVE", 7u);  // 【std::string构造赋值】
        v249 = 0;  // 局部 v249 → 0
LABEL_216:
        pThis_4887 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(  // 虚表 +1160 调用（取动画资源（槽 290））
                           this,  // 第 1 个实参 this
                           *((uint32_t *)this + 2085));  // 第 2 个实参
        goto LABEL_226;  // 转到 LABEL_226
      }
      if ( pThis_825 == 21 )  // pThis_825 等于 21
      {
        if ( *((uint32_t *)this + 2093) == 0 )  // this+2093（nDiffVal【推断】） 等于 0
        {
          LOBYTE(v288) = 13;  // 异常展开状态号 → 13
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C7 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/IceWave.ani", 1);  // 存 建动画件 Effect/Animation/IceWave.ani
            else
              pThis_6C7 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/IceWave.ani", 1);  // 存 建动画件 Effect/Animation/IceWave.ani
          }
          else
          {
            pThis_6C7 = 0;  // 局部 pThis_6C7 → 0
          }
          LOBYTE(v288) = 11;  // 异常展开状态号 → 11
          *((uint32_t *)this + 2093) = pThis_6C7;  // 写 this+2093（nDiffVal【推断】） = pThis_6C7
        }
        *((uint32_t *)this + 2087) = *((uint32_t *)this + 2093);  // 写 this+2087（nPhaseParity【推断】） = *((uint32_t *)this + 209
        *((uint32_t *)this + 2088) = 20002;  // 写 this+2088（nRideHost8352【推断】） = 20002
        *((uint32_t *)this + 2089) = 0;  // 写 this+2089（uPick8356【推断】） = 0
        sub_406D60("SM_ICEWAVE");  // std::string 从 C 串赋值
        v249 = 1;  // 局部 v249 → 1
        goto LABEL_216;  // 转到 LABEL_216
      }
      if ( pThis_825 != 22 )  // pThis_825 不等于 22
        goto LABEL_227;  // 转到 LABEL_227
      if ( *((uint32_t *)this + 2094) == 0 )  // this+2094（pFxObjB【推断】） 等于 0
      {
        LOBYTE(v288) = 14;  // 异常展开状态号 → 14
        if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
        {
          if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
            pThis_6C8 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/FireWave.ani", 1);  // 存 建动画件 Effect/Animation/FireWave.ani
          else
            pThis_6C8 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/FireWave.ani", 1);  // 存 建动画件 Effect/Animation/FireWave.ani
        }
        else
        {
          pThis_6C8 = 0;  // 局部 pThis_6C8 → 0
        }
        LOBYTE(v288) = 11;  // 异常展开状态号 → 11
        *((uint32_t *)this + 2094) = pThis_6C8;  // 写 this+2094（pFxObjB【推断】） = pThis_6C8
      }
      v114 = *(uint32_t *)this;  // 取虚表指针
      v249 = (unsigned int)"Particle/FireWave.ptl";
      *((uint32_t *)this + 2087) = *((uint32_t *)this + 2094);  // 写 this+2087（nPhaseParity【推断】） = *((uint32_t *)this + 209
      *((uint32_t *)this + 2088) = 20008;  // 写 this+2088（nRideHost8352【推断】） = 20008
      *((uint32_t *)this + 2089) = (*(int (/*thiscall*/ **)(char *))(v114 + 588))(this);  // 写 this+2089（uPick8356【推断】） = (*(int (·thiscall· **)
      sub_406D60("SM_FIREWAVE");  // std::string 从 C 串赋值
      pThis_4887 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 1160))(  // 虚表 +1160 调用（取动画资源（槽 290））
                         this,  // 第 1 个实参 this
                         *((uint32_t *)this + 2085),  // 第 2 个实参
                         0);  // 第 3 个实参
LABEL_226:
      v107 = sub_47E9D0(pThis_4887, v249);  // 存 读技能表（14 字节条目，索引=pThis_4887）
      Block2 = (void **)Block[0];
      if ( v286 < 0x10 )
LABEL_227:
        Block2 = Block;  // Block2 复制自 Block
      (*(void (/*thiscall*/ **)(char *, void **, int, uint32_t))(*(uint32_t *)this + 212))(this, Block2, 13, 0);  // 虚表 +212 调用（播放动作/播报（槽 53））
      pThis_8252 = *((uint32_t *)this + 2085);  // 读 this+2085（pAnimA【推断】）
      pThis_47410 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 1140))(this);  // 虚表 +1140 调用（取技能值（槽 285））
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 1160))(  // 虚表 +1160 调用（取动画资源（槽 290））
        this,  // 第 1 个实参 this
        *((uint32_t *)this + 2085),  // 第 2 个实参
        2,  // 第 3 个实参
        pThis_47410);  // 第 4 个实参
      v280 = (double)(int)sub_47EF20(pThis_8252, -1, -1, 11, 0) * 0.0099999998;
      sub_4920E0(*((uint32_t **)this + 2087), v280, v280);  // ★批量改写全帧缩放
      pThis_6802 = 1000 * v103 / *((uint32_t *)this + 1664);  // 乘算后按 this+1664 归一
      LOBYTE(v288) = 0;  // 异常展开状态号 → 0
      *((uint32_t *)this + 2091) = v107 + pThis_6802;  // 写 this+2091（pFrameObject【推断】） = v107 + pThis_6802
      if ( v286 >= 0x10 )
        j__free(Block[0]);
// ── [段 23] ★ LABEL_290：第二重出口 + 第三重 switch(nArg2)：动作事件号分派（7/8/10/12/14）──
//   此处起为「按动作号」的通用处理，与上面「按技能态」正交
LABEL_290:
      sub_4B89D0(nArg2, pArg3, fArg4, fArg5);  // 跑步地面循环 + 蓄气/霸体特效 G_RUN_FLOOR_LOOP/RUN_GRASS/SOIL/STONE_LOOP 按 +212 地形选播
      switch ( nArg2 )  // 第三重 switch：按动作事件号分派
      {
        // ── [段 24] 第三重 case 7：★ 上挑/挑击 —— sub_47EED0 三参读表 + +2056==17 特例 ──
        //   vt+1140(43) 有参时 sub_47EED0；+2056(2056 索引)==17 时 sub_47EFD0 伤害写 +97 索引(388 字节)
        case 7:  // 【case 7】分型分支
          v165 = *(int **)(pArg3 + 4);
          if ( v165 != nullptr && (*(uint32_t *)(pArg3 + 8) - (int)v165) >> 2 != 0 )
            v166 = *v165;  // 取 v165 的首字段
          else
            v166 = -1;  // 局部 v166 → -1
          v167 = *(uint32_t *)this;  // 取虚表指针
          *((uint32_t *)this + 2056) = v166;  // 写 this+2056（f_2020【推断】） = v166
          if ( (*(int (/*thiscall*/ **)(char *, int))(v167 + 1140))(this, 43) > 0 )  // 经虚表字节 +1140 调用
          {
            pThis_47411 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 43);  // 虚表 +1140 调用（取技能值（槽 285））
            (*(void (/*thiscall*/ **)(char *, int, uint32_t, int, int))(*(uint32_t *)this + 1160))(this, 43, 0, 1, pThis_47411);  // 虚表 +1160 调用（取动画资源（槽 290））
            v169 = sub_47EED0(v255, v256, v257);  // 存 上行 0x47EE70 的 void 版：同款插值但丢弃结果
            (*(void (/*fastcall*/ **)(char *, uint32_t, uint32_t))(*(uint32_t *)this + 888))(  // 虚表 +888 调用（动画时长设置（槽 222））
              this,  // 第 1 个实参 this
              (uint64_t)((double)*((int *)this + 1664) * (v169 * 0.0099999998 + 1.0)) >> 32,  // 第 2 个实参
              0);  // 第 3 个实参
          }
          if ( *((uint32_t *)this + 2056) == 17 )  // this+2056（f_2020【推断】） 等于 17
          {
            v170 = *(uint32_t *)this;  // 取虚表指针
            *((uint32_t *)this + 99) = 0;  // 写 this+99（uReflectCtx【推断】） = 0
            v171 = (*(int (/*thiscall*/ **)(char *))(v170 + 388))(this);  // 经虚表字节 +388 调用
            pThis_47412 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 17);  // 虚表 +1140 调用（取技能值（槽 285））
            pThis_4888 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 17);  // 虚表 +1160 调用（取动画资源（槽 290））
            *((float *)this + 97) = (float)sub_47EFD0(pThis_4888, 0.0, pThis_47412, v171, v171, 0);  // this 浮点槽 +97 写入 技能表槽位设置
          }
          v174 = *(uint32_t *)this;  // 取虚表指针
          pThis_4946 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(  // 虚表 +1172 调用（取动作数据（槽 293））
                   this,  // 第 1 个实参 this
                   0,  // 第 2 个实参
                   -1,  // 第 3 个实参
                   0,  // 第 4 个实参
                   0);  // 第 5 个实参
          (*(void (/*thiscall*/ **)(char *, int))(v174 + 212))(this, pThis_4946);  // 经虚表字节 +212 调用
          pThis_4947 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);  // 虚表 +1172 调用（取动作数据（槽 293））
          sub_4015C0(pThis_4947, strlen((const char *)pThis_4947));  // 【std::string构造赋值】
          break;
        // ── [段 25] 第三重 case 8：★ 普攻 —— +2054 动作号 46 特例 + sub_47EF20 双读表 ──
        //   46 时 sub_47EFD0 写 +388、sub_47EF20(1)/(2) 写 +114 索引与 v180；
        //   尾部 sub_4015C0(pThis_4949, strlen) 字符串赋回对象
        case 8:  // 【case 8】分型分支
          sub_4014D0((std::_String_base *)(this + 7044), v281, 0, -1);  // std::string::assign
          if ( *((uint32_t *)this + 2054) != -1 )
            (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1328))(this, 0);  // 虚表 +1328 调用
          if ( *((uint32_t *)this + 2054) == 46 )  // this+2054（nAtkActionType） 等于 46
          {
            (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 1216);  // 虚表 +344 调用（清参（槽 86））
            pThis_4889 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 46);  // 虚表 +1160 调用（取动画资源（槽 290））
            pThis_47413 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 46);  // 虚表 +1140 调用（取技能值（槽 285））
            pThis_1845 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
            *((float *)this + 97) = (float)sub_47EFD0(pThis_4889, 0.0, pThis_47413, pThis_1845, pThis_1845, 0);  // this 浮点槽 +97 写入 技能表槽位设置
            *((uint32_t *)this + 114) = sub_47EF20(1, pThis_47413, -1, -1, 11);  // 写 this+114（pKeyVecEnd【推断】） = sub_47EF20(1, pThis_4741
            v180 = sub_47EF20(2, pThis_47413, -1, -1, 11);  // 存 读技能数值表（16 字节条目）
            v181 = *(uint32_t *)this;  // 取虚表指针
            *((uint32_t *)this + 113) = v180;  // 写 this+113（nAtkRollVal【推断】） = v180
            *(this + 8220) = 0;  // 写 this+8220 → 0
            (*(void (/*thiscall*/ **)(char *, int, int))(v181 + 612))(this, 1, 1);  // 经虚表字节 +612 调用
          }
          v182 = *(uint32_t *)this;  // 取虚表指针
          pThis_4948 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(  // 虚表 +1172 调用（取动作数据（槽 293））
                   this,  // 第 1 个实参 this
                   0,  // 第 2 个实参
                   -1,  // 第 3 个实参
                   0,  // 第 4 个实参
                   0);  // 第 5 个实参
          (*(void (/*thiscall*/ **)(char *, int))(v182 + 212))(this, pThis_4948);  // 经虚表字节 +212 调用
          pThis_4949 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 2);  // 虚表 +1172 调用（取动作数据（槽 293））
          sub_4015C0(pThis_4949, strlen((const char *)pThis_4949));  // 【std::string构造赋值】
          break;
        // ── [段 26] 第三重 case 10：★ 嗜血（GiveBloodCharge/Shoot 四枚 .ani）+ 子型 23 分 0/1 ──
        //   +1953(1953 索引)==0 时惰性建 GiveBloodCharge1/2 与 GiveBloodShoot1/2 四件（+2095..+2098，
        //   每件均 sub_42FCB0(228) 门控 + this+108/this+91 内联或堆指针二选一）；
        //   switch(+1954)：23 → +1952==1 时 vt+204(1,+2097)/(2,+2098)，否则 vt+204(1,+2095)/(2,+2096)；
        //   32 → nArg2 != 10 时回挂 +8404 起 2 件并 vt+612(0,0)；24 → vt+1160(24) + sub_47DD30；
        //   default → +1954==44 且 +1952==1 且 +161==1 时 vt+612(0,0)（1857 行）
        case 10:  // 【case 10】分型分支
          if ( *((uint32_t *)this + 1953) == 0 )  // this+1953（nSubStateA） 等于 0
          {
            pThis_48810 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(  // 虚表 +1160 调用（取动画资源（槽 290））
                               this,  // 第 1 个实参 this
                               *((uint32_t *)this + 1954));  // 第 2 个实参
            pThis_47414 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 1954));  // 虚表 +1140 调用（取技能值（槽 285））
            pThis_7A22 = *((uint32_t *)this + 1954);  // 读 this+1954（nSubStateB）
            switch ( pThis_7A22 )  // switch(pThis_7A22) 多路分派
            {
              case 23:  // 【case 23】分型分支
                if ( *((uint32_t *)this + 2095) == 0 )  // this+2095（pAnimC【推断】） 等于 0
                {
                  v266 = (void *)sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                  LOBYTE(v288) = 20;  // 异常展开状态号 → 20
                  if ( v266 != nullptr )  // v266 非空
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                      pThis_6C9 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodCharge1.ani", 1);  // 存 建动画件 Effect/Animation/GiveBloodCharge1.ani
                    else
                      pThis_6C9 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodCharge1.ani", 1);  // 存 建动画件 Effect/Animation/GiveBloodCharge1.ani
                  }
                  else
                  {
                    pThis_6C9 = 0;  // 局部 pThis_6C9 → 0
                  }
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  *((uint32_t *)this + 2095) = pThis_6C9;  // 写 this+2095（pAnimC【推断】） = pThis_6C9
                  v267 = (void *)sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                  LOBYTE(v288) = 21;  // 异常展开状态号 → 21
                  if ( v267 != nullptr )  // v267 非空
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                      pThis_6C10 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodCharge2.ani", 1);  // 存 建动画件 Effect/Animation/GiveBloodCharge2.ani
                    else
                      pThis_6C10 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodCharge2.ani", 1);  // 存 建动画件 Effect/Animation/GiveBloodCharge2.ani
                  }
                  else
                  {
                    pThis_6C10 = 0;  // 局部 pThis_6C10 → 0
                  }
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  *((uint32_t *)this + 2096) = pThis_6C10;  // 写 this+2096（f_20C0【推断】） = pThis_6C10
                  v268 = (void *)sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                  LOBYTE(v288) = 22;  // 异常展开状态号 → 22
                  if ( v268 != nullptr )  // v268 非空
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                      pThis_6C11 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodShoot1.ani", 1);  // 存 建动画件 Effect/Animation/GiveBloodShoot1.ani
                    else
                      pThis_6C11 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodShoot1.ani", 1);  // 存 建动画件 Effect/Animation/GiveBloodShoot1.ani
                  }
                  else
                  {
                    pThis_6C11 = 0;  // 局部 pThis_6C11 → 0
                  }
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  *((uint32_t *)this + 2097) = pThis_6C11;  // 写 this+2097（pAnimD【推断】） = pThis_6C11
                  v269 = (void *)sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                  LOBYTE(v288) = 23;  // 异常展开状态号 → 23
                  if ( v269 != nullptr )  // v269 非空
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                      pThis_6C12 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GiveBloodShoot2.ani", 1);  // 存 建动画件 Effect/Animation/GiveBloodShoot2.ani
                    else
                      pThis_6C12 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GiveBloodShoot2.ani", 1);  // 存 建动画件 Effect/Animation/GiveBloodShoot2.ani
                  }
                  else
                  {
                    pThis_6C12 = 0;  // 局部 pThis_6C12 → 0
                  }
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  *((uint32_t *)this + 2098) = pThis_6C12;  // 写 this+2098（f_20C8【推断】） = pThis_6C12
                }
                pThis_7A02 = *((uint32_t *)this + 1952);  // 读 this+1952（nStyleSel）
                if ( pThis_7A02 != 0 )  // pThis_7A02 不等于 0
                {
                  if ( pThis_7A02 == 1 )  // pThis_7A02 等于 1
                  {
                    (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
                      this,  // 第 1 个实参 this
                      1,  // 第 2 个实参
                      *((uint32_t *)this + 2097),  // 第 3 个实参
                      0,  // 第 4 个实参
                      0,  // 第 5 个实参
                      0,  // 第 6 个实参
                      0);  // 第 7 个实参
                    (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
                      this,  // 第 1 个实参 this
                      2,  // 第 2 个实参
                      *((uint32_t *)this + 2098),  // 第 3 个实参
                      0,  // 第 4 个实参
                      0,  // 第 5 个实参
                      0,  // 第 6 个实参
                      0);  // 第 7 个实参
                    if ( *((uint32_t *)this + 2099) == 0 )  // this+2099（nNameLookup【推断】） 等于 0
                    {
                      pMem = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
                      LOBYTE(v288) = 24;  // 异常展开状态号 → 24
                      if ( pMem != nullptr )  // pMem 非空
                        v197 = (int *)sub_4D6810(0, 0, 1, 1);  // 存 ★ CNChangeHp
                      else
                        v197 = nullptr;  // v197 置空
                      *((uint32_t *)this + 2099) = v197;  // 写 this+2099（nNameLookup【推断】） = v197
                      v198 = *v197;  // 取 v197 的首字段
                      LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v198 + 64))(v197) + 36) = 0;  // 经虚表字节 +64 调用
                    }
                    pThis_833 = **((uint32_t **)this + 2099);
                    pThis_2E4 = (uint64_t)((double)(*(int (/*thiscall*/ **)(char *, uint32_t, int, int))(*(uint32_t *)this + 740))(  // 虚表 +740 调用
                                                        this,  // 第 1 个实参 this
                                                        *((uint32_t *)this + 1956),  // 第 2 个实参
                                                        1,  // 第 3 个实参
                                                        1)  // 第 4 个实参
                                            * flt_9B934C);  // 第 1 个实参 this
                    v252 = (float)-(int)pThis_2E4;
                    (*(void (/*fastcall*/ **)(uint32_t, uint32_t, uint32_t))(pThis_833 + 120))(  // 经虚表字节 +120 调用
                      *((uint32_t *)this + 2099),  // 第 1 个实参 this
                      HIDWORD(pThis_2E4),  // 第 2 个实参
                      LODWORD(v252));  // 第 3 个实参
                    (*(void (/*thiscall*/ **)(uint32_t, char *, char *, uint32_t, uint32_t, uint32_t, int))(**((uint32_t **)this + 2099)
                                                                                                + 56))(  // 第 1 个实参 this
                      *((uint32_t *)this + 2099),  // 第 1 个实参 this
                      this,  // 第 2 个实参
                      this,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0,  // 第 5 个实参
                      0,  // 第 6 个实参
                      -1);  // 第 7 个实参
                    v201 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
                    if ( v201 != 0 )  // v201 不等于 0
                    {
                      if ( v201 == 1 )  // v201 等于 1
                      {
                        v202 = (double)sub_47E9D0(pThis_48810, 1u);
                      }
                      else if ( v201 == 2 )  // 否则若 v201 等于 2
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
                      *((uint32_t *)this + 2100) = 0;  // 写 this+2100（pAppendage【推断】） = 0
                    }
                    (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                      this,  // 第 1 个实参 this
                      "SM_SACRIFICE_CAST",  // 第 2 个实参：串 SM_SACRIFICE_CAST
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                    (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                      this,  // 第 1 个实参 this
                      "SACRIFICE_BEGIN",  // 第 2 个实参：串 SACRIFICE_BEGIN
                      -1,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0);  // 第 5 个实参
                  }
                }
                else
                {
                  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 912);  // 虚表 +344 调用（清参（槽 86））
                  (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
                    this,  // 第 1 个实参 this
                    1,  // 第 2 个实参
                    *((uint32_t *)this + 2095),  // 第 3 个实参
                    0,  // 第 4 个实参
                    0,  // 第 5 个实参
                    0,  // 第 6 个实参
                    0);  // 第 7 个实参
                  (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
                    this,  // 第 1 个实参 this
                    2,  // 第 2 个实参
                    *((uint32_t *)this + 2096),  // 第 3 个实参
                    0,  // 第 4 个实参
                    0,  // 第 5 个实参
                    0,  // 第 6 个实参
                    0);  // 第 7 个实参
                }
                break;
              case 24:  // 【case 24】分型分支
                // ── [段 27] case 10 子表 24 号型：+1952 分 0/1 两支（1 且本机时 sub_47EFD0 伤害链）──
                pThis_7A03 = *((uint32_t *)this + 1952);  // 读 this+1952（nStyleSel）
                if ( pThis_7A03 != 0 )  // pThis_7A03 不等于 0
                {
                  if ( pThis_7A03 == 1 && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
                  {
                    pThis_1846 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
                    pThis_47415 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 24);  // 虚表 +1140 调用（取技能值（槽 285））
                    pThis_48811 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 24);  // 虚表 +1160 调用（取动画资源（槽 290））
                    v207 = sub_47EFD0(pThis_48811, 0.0, pThis_47415, pThis_1846, pThis_1846, 0);  // 存 读技能表（浮点插值）
                    (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 虚表 +580 调用（发射 PO（槽 145））
                      this,  // 第 1 个实参 this
                      20010,  // 第 2 个实参
                      v207,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0,  // 第 5 个实参
                      0,  // 第 6 个实参
                      0,  // 第 7 个实参
                      0,  // 第 8 个实参
                      4,  // 第 9 个实参
                      0,  // 第 10 个实参
                      0,  // 第 11 个实参
                      0);  // 第 12 个实参
                    (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 虚表 +580 调用（发射 PO（槽 145））
                      this,  // 第 1 个实参 this
                      20009,  // 第 2 个实参
                      v207,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0,  // 第 5 个实参
                      0,  // 第 6 个实参
                      50,  // 第 7 个实参
                      0,  // 第 8 个实参
                      4,  // 第 9 个实参
                      0,  // 第 10 个实参
                      0,  // 第 11 个实参
                      0);  // 第 12 个实参
                  }
                }
                else
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int))(*(uint32_t *)this + 212))(this, "SM_BLOOD_CAST", -1);  // 虚表 +212 调用（播放动作/播报（槽 53））：标签 SM_BLOOD_CAST
                  (*(void (/*thiscall*/ **)(char *, int, char *, uint32_t))(*(uint32_t *)this + 1160))(  // 虚表 +1160 调用（取动画资源（槽 290））
                    this,  // 第 1 个实参 this
                    24,  // 第 2 个实参
                    this,  // 第 3 个实参
                    *((uint32_t *)this + 1955));  // 第 4 个实参
                  sub_47DCD0(0, 0);  // 经 nArg2 对象 vt+80 取其 +132 资源，调 sub_424120
                }
                break;
              // ── [段 28] case 10 子表 34 号型：另一组动画回挂（+1952 门控）──
              case 34:  // 【case 34】分型分支
                if ( *((uint32_t *)this + 1952) == 1 )  // this+1952（nStyleSel） 等于 1
                {
                  v271 = (void *)sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                  LOBYTE(v288) = 25;  // 异常展开状态号 → 25
                  if ( v271 != nullptr )  // v271 非空
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                      LOBYTE(pThis_5B3) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
                    else
                      pThis_5B3 = *((uint32_t *)this + 91);  // 读 this+91（pAnimNameStr【推断】）
                    v209 = sub_431920(pThis_5B3, (char)"Effect/Animation/PinchHpRegen1.ani", 1);  // 存 建动画件 Effect/Animation/PinchHpRegen1.ani
                  }
                  else
                  {
                    v209 = 0;  // 局部 v209 → 0
                  }
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  v272 = (void *)sub_44B6C0(284);  // 存 CRT 一次性池初始化 2
                  LOBYTE(v288) = 26;  // 异常展开状态号 → 26
                  if ( v272 != nullptr )  // v272 非空
                    pObj3 = sub_44E1F0(v209, 1);  // 存 CNRDPooledObject
                  else
                    pObj3 = 0;  // 局部 pObj3 → 0
                  pThis_1D3 = *((uint32_t *)this + 29);  // 读 this+29（pSessionCtx【推断】）
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  sub_45FE80(pThis_1D3, pObj3, 2, 0, pObj3, (int)this, 0);  // 注册场景对象
                  v212 = *(uint32_t *)pObj3;  // 取 pObj3 首字段
                  pThis_985 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);  // 虚表 +152 调用（取动作件（槽 38））
                  (*(void (/*thiscall*/ **)(int))(v212 + 148))(pObj3);  // 经虚表字节 +148 调用
                  v213 = *(uint32_t *)pObj3;  // 取 pObj3 首字段
                  pThis_802 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);  // 虚表 +128 调用（取帧数（槽 32））
                  pThis_7C2 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, pThis_802);  // 虚表 +124 调用（取帧时长累加（槽 31））
                  pThis_782 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, pThis_7C2);  // 虚表 +120 调用（取帧时长（槽 30））
                  (*(void (/*thiscall*/ **)(int, int))(v213 + 112))(pObj3, pThis_782);  // 经虚表字节 +112 调用
                  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj3 + 60))(pObj3, this);
                  sub_4A06D0(pThis_985);  // 【解读】 【推断】绑定目标对象并记录相对偏移。this+128 = 目标指针； this+132/136/140 = 本坐标 − 目标坐标
                  v273 = (void *)sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                  LOBYTE(v288) = 27;  // 异常展开状态号 → 27
                  if ( v273 != nullptr )  // v273 非空
                  {
                    if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                      LOBYTE(pThis_5B4) = (uint8_t)this + 108;  // 取 this 内联缓冲（+108）低字节
                    else
                      pThis_5B4 = *((uint32_t *)this + 91);  // 读 this+91（pAnimNameStr【推断】）
                    v218 = sub_431920(pThis_5B4, (char)"Effect/Animation/PinchHpRegen2.ani", 1);  // 存 建动画件 Effect/Animation/PinchHpRegen2.ani
                  }
                  else
                  {
                    v218 = 0;  // 局部 v218 → 0
                  }
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  v274 = (void *)sub_44B6C0(284);  // 存 CRT 一次性池初始化 2
                  LOBYTE(v288) = 28;  // 异常展开状态号 → 28
                  if ( v274 != nullptr )  // v274 非空
                    pObj4 = sub_44E1F0(v218, 1);  // 存 CNRDPooledObject
                  else
                    pObj4 = 0;  // 局部 pObj4 → 0
                  pThis_1D4 = *((uint32_t *)this + 29);  // 读 this+29（pSessionCtx【推断】）
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  sub_45FE80(pThis_1D4, pObj4, 2, 0, pObj4, (int)this, 0);  // 注册场景对象
                  v221 = *(uint32_t *)pObj4;  // 取 pObj4 首字段
                  pThis_986 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 152))(this);  // 虚表 +152 调用（取动作件（槽 38））
                  (*(void (/*thiscall*/ **)(int))(v221 + 148))(pObj4);  // 经虚表字节 +148 调用
                  v222 = *(uint32_t *)pObj4;  // 取 pObj4 首字段
                  pThis_803 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);  // 虚表 +128 调用（取帧数（槽 32））
                  pThis_7C3 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, pThis_803);  // 虚表 +124 调用（取帧时长累加（槽 31））
                  pThis_783 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, pThis_7C3);  // 虚表 +120 调用（取帧时长（槽 30））
                  (*(void (/*thiscall*/ **)(int, int))(v222 + 112))(pObj4, pThis_783);  // 经虚表字节 +112 调用
                  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj4 + 60))(pObj4, this);
                  sub_4A06D0(pThis_986);  // 【解读】 【推断】绑定目标对象并记录相对偏移。this+128 = 目标指针； this+132/136/140 = 本坐标 − 目标坐标
                  pThis_474142 = pThis_47414;  // pThis_474142 复制自 pThis_47414
                  v290 = sub_47EF20(0, pThis_47414, -1, -1, 11);  // 存 读技能数值表（16 字节条目）
                  v227 = sub_47EF20(1, pThis_474142, -1, -1, 11);  // 存 读技能数值表（16 字节条目）
                  pMem2 = operator new(0x80u);  // 分配 0x80 字节对象壳（128 字节）
                  LOBYTE(v288) = 29;  // 异常展开状态号 → 29
                  if ( pMem2 != nullptr )  // pMem2 非空
                  {
                    v247 = (float)v290;
                    v228 = (int *)sub_4D6810(LODWORD(v247), v227, 1, 0);  // 存 ★ CNChangeHp
                  }
                  else
                  {
                    v228 = nullptr;  // v228 置空
                  }
                  v229 = *v228;  // 取 v228 的首字段
                  LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                  (*(void (/*thiscall*/ **)(int *, char *, char *, uint32_t, uint32_t, uint32_t, int))(v229 + 56))(  // 经虚表字节 +56 调用
                    v228,  // 第 1 个实参 this
                    this,  // 第 2 个实参
                    this,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0,  // 第 5 个实参
                    0,  // 第 6 个实参
                    -1);  // 第 7 个实参
                }
                break;
              // ── [段 29] case 10 子表 25 号型：单支处理 ──
              case 25:  // 【case 25】分型分支
                if ( *((uint32_t *)this + 1952) == 1 )  // this+1952（nStyleSel） 等于 1
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                    this,  // 第 1 个实参 this
                    "SM_GHOST_KAZHAN",  // 第 2 个实参：串 SM_GHOST_KAZHAN
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
                  {
                    v230 = *(uint32_t *)this;  // 取虚表指针
                    pThis_47416 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(  // 虚表 +1140 调用（取技能值（槽 285））
                             this,  // 第 1 个实参 this
                             25,  // 第 2 个实参
                             0,  // 第 3 个实参
                             0,  // 第 4 个实参
                             122,  // 第 5 个实参
                             0,  // 第 6 个实参
                             0,  // 第 7 个实参
                             4,  // 第 8 个实参
                             0,  // 第 9 个实参
                             0,  // 第 10 个实参
                             0);  // 第 11 个实参
                    (*(void (/*thiscall*/ **)(char *, int, int))(v230 + 580))(this, 20011, pThis_47416);  // 经虚表字节 +580 调用
                  }
                }
                break;
              // ── [段 30] case 10 子表 36/41 号型：+1952==1 门控下的两段处理 ──
              case 36:  // 【case 36】分型分支
                if ( *((uint32_t *)this + 1952) == 1 )  // this+1952（nStyleSel） 等于 1
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                    this,  // 第 1 个实参 this
                    "SM_GHOST_SAYA",  // 第 2 个实参：串 SM_GHOST_SAYA
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
                  {
                    v232 = *(uint32_t *)this;  // 取虚表指针
                    pThis_47417 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(  // 虚表 +1140 调用（取技能值（槽 285））
                             this,  // 第 1 个实参 this
                             36,  // 第 2 个实参
                             0,  // 第 3 个实参
                             0,  // 第 4 个实参
                             122,  // 第 5 个实参
                             0,  // 第 6 个实参
                             0,  // 第 7 个实参
                             4,  // 第 8 个实参
                             0,  // 第 9 个实参
                             0,  // 第 10 个实参
                             0);  // 第 11 个实参
                    (*(void (/*thiscall*/ **)(char *, int, int))(v232 + 580))(this, 20012, pThis_47417);  // 经虚表字节 +580 调用
                  }
                }
                break;
              case 41:  // 【case 41】分型分支
                if ( *((uint32_t *)this + 1952) == 1 )  // this+1952（nStyleSel） 等于 1
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                    this,  // 第 1 个实参 this
                    "SM_GHOST_BREMEN",  // 第 2 个实参：串 SM_GHOST_BREMEN
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                  if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
                  {
                    v234 = *(uint32_t *)this;  // 取虚表指针
                    pThis_47418 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(  // 虚表 +1140 调用（取技能值（槽 285））
                             this,  // 第 1 个实参 this
                             41,  // 第 2 个实参
                             0,  // 第 3 个实参
                             0,  // 第 4 个实参
                             122,  // 第 5 个实参
                             0,  // 第 6 个实参
                             0,  // 第 7 个实参
                             4,  // 第 8 个实参
                             0,  // 第 9 个实参
                             0,  // 第 10 个实参
                             0);  // 第 11 个实参
                    (*(void (/*thiscall*/ **)(char *, int, int))(v234 + 580))(this, 20013, pThis_47418);  // 经虚表字节 +580 调用
                  }
                }
                break;
              case 44:  // 【case 44】分型分支
                // ── [段 31] case 10 子表 44 号型：+1952 分 0/非 0 两支（44 号上斩/落剑收尾）──
                pThis_7A04 = *((uint32_t *)this + 1952);  // 读 this+1952（nStyleSel）
                if ( pThis_7A04 != 0 )  // pThis_7A04 不等于 0
                {
                  if ( pThis_7A04 == 1 )  // pThis_7A04 等于 1
                  {
                    byte_9A0384 = 1;  // 局部 byte_9A0384 → 1
                    if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
                    {
                      v237 = *(uint32_t *)this;  // 取虚表指针
                      pThis_47419 = (*(int (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(  // 虚表 +1140 调用（取技能值（槽 285））
                               this,  // 第 1 个实参 this
                               44,  // 第 2 个实参
                               0,  // 第 3 个实参
                               0,  // 第 4 个实参
                               0,  // 第 5 个实参
                               0,  // 第 6 个实参
                               0,  // 第 7 个实参
                               4,  // 第 8 个实参
                               0,  // 第 9 个实参
                               0,  // 第 10 个实参
                               0);  // 第 11 个实参
                      (*(void (/*thiscall*/ **)(char *, int, int))(v237 + 580))(this, 20014, pThis_47419);  // 经虚表字节 +580 调用
                    }
                  }
                }
                else
                {
                  (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                    this,  // 第 1 个实参 this
                    "SM_TOMBSTONE",  // 第 2 个实参：串 SM_TOMBSTONE
                    -1,  // 第 3 个实参
                    0,  // 第 4 个实参
                    0);  // 第 5 个实参
                }
                break;
              default:
                // ── [段 32] case 10 子表 default：仅 +1954==32 且 +1952==0 时处理（其余静默）──
                if ( pThis_7A22 == 32 && *((uint32_t *)this + 1952) == 0 )
                {
                  (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 996))(this);  // 虚表 +996 调用
                  if ( *((uint32_t *)this + 2101) == 0 )  // this+2101（pFxObjD【推断】） 等于 0
                  {
                    v276 = (void *)sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                    LOBYTE(v288) = 30;  // 异常展开状态号 → 30
                    if ( v276 != nullptr )  // v276 非空
                    {
                      if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                        pThis_6C13 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ReleaseWave1.ani", 1);  // 存 建动画件 Effect/Animation/ReleaseWave1.ani
                      else
                        pThis_6C13 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/ReleaseWave1.ani", 1);  // 存 建动画件 Effect/Animation/ReleaseWave1.ani
                    }
                    else
                    {
                      pThis_6C13 = 0;  // 局部 pThis_6C13 → 0
                    }
                    LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                    *((uint32_t *)this + 2101) = pThis_6C13;  // 写 this+2101（pFxObjD【推断】） = pThis_6C13
                    v277 = (void *)sub_42FCB0(228);  // 存 临时缓冲占位（228 字节）
                    LOBYTE(v288) = 31;  // 异常展开状态号 → 31
                    if ( v277 != nullptr )  // v277 非空
                    {
                      if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                        pThis_6C14 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/ReleaseWave2.ani", 1);  // 存 建动画件 Effect/Animation/ReleaseWave2.ani
                      else
                        pThis_6C14 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/ReleaseWave2.ani", 1);  // 存 建动画件 Effect/Animation/ReleaseWave2.ani
                    }
                    else
                    {
                      pThis_6C14 = 0;  // 局部 pThis_6C14 → 0
                    }
                    LOBYTE(v288) = 0;  // 异常展开状态号 → 0
                    *((uint32_t *)this + 2102) = pThis_6C14;  // 写 this+2102（pRoplingObj【推断】） = pThis_6C14
                  }
                  (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
                    this,  // 第 1 个实参 this
                    1,  // 第 2 个实参
                    *((uint32_t *)this + 2101),  // 第 3 个实参
                    0,  // 第 4 个实参
                    0,  // 第 5 个实参
                    0,  // 第 6 个实参
                    0);  // 第 7 个实参
                  (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
                    this,  // 第 1 个实参 this
                    -1,  // 第 2 个实参
                    *((uint32_t *)this + 2102),  // 第 3 个实参
                    0,  // 第 4 个实参
                    0,  // 第 5 个实参
                    0,  // 第 6 个实参
                    0);  // 第 7 个实参
                  if ( (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚表 +308 调用（标志查询（槽 77））
                  {
                    pThis_48812 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 32);  // 虚表 +1160 调用（取动画资源（槽 290））
                    if ( (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 32) <= 1 )  // 虚表 +1140 调用（取技能值（槽 285））
                      pThis_47420 = 1;  // 局部 pThis_47420 → 1
                    else
                      pThis_47420 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 32);  // 虚表 +1140 调用（取技能值（槽 285））
                    pThis_1847 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
                    v291 = *(uint32_t *)this;  // 取虚表指针
                    v244 = sub_47EFD0(pThis_48812, 0.0, pThis_47420, pThis_1847, pThis_1847, 0);  // 存 读技能表（浮点插值）
                    (*(void (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v291 + 580))(  // 经虚表字节 +580 调用
                      this,  // 第 1 个实参 this
                      20018,  // 第 2 个实参
                      v244,  // 第 3 个实参
                      0,  // 第 4 个实参
                      0,  // 第 5 个实参
                      0,  // 第 6 个实参
                      0,  // 第 7 个实参
                      0,  // 第 8 个实参
                      4,  // 第 9 个实参
                      0,  // 第 10 个实参
                      0,  // 第 11 个实参
                      0);  // 第 12 个实参
                  }
                  (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 612))(this, 1, 1);  // 虚表 +612 调用
                }
                break;
            }
          }
          break;
        // ── [段 33] 第三重 case 12：★ 技能 11 帧长标定 —— sub_47E9D0(11,0) 读表 ──
        //   *2058 = 1000*v186/+1664（帧长归一）；*2057 = sub_491C70(+30 对象, 2)；*2059 = 0；
        //   vt+1172(1,-1) 与 vt+1172(3) 取两串 → vt+212 播报 + sub_4015C0 字符串赋回
        case 12:  // 【case 12】分型分支
          if ( (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 11) > 0 )  // 虚表 +1140 调用（取技能值（槽 285））
          {
            pThis_48813 = (uint32_t *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 11);  // 虚表 +1160 调用（取动画资源（槽 290））
            // ── [段 34] 第二重 case 12：★ 帧长标定 —— sub_47E9D0(11,0) 读表 + sub_491C70(+30 对象,2) ──
            v186 = sub_47E9D0(pThis_48813, 0);  // 存 读技能表（14 字节条目，索引=pThis_48813）
            pThis_1E2 = *((uint32_t *)this + 30);  // 读 this+30（pAnimObj【推断】）
            *((uint32_t *)this + 2058) = 1000 * v186 / *((uint32_t *)this + 1664);  // 写 this+2058（nGrabTable【推断】） = 1000 * v186 / *((uint32_
            *((uint32_t *)this + 2057) = sub_491C70(pThis_1E2, 2);  // 写 this+2057（bGrabFlag【推断】） = sub_491C70(pThis_1E2, 2)
            *((uint32_t *)this + 2059) = 0;  // 写 this+2059（nReflectCnt【推断】） = 0
          }
          v188 = *(uint32_t *)this;  // 取虚表指针
          pThis_49410 = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);  // 虚表 +1172 调用（取动作数据（槽 293））
          (*(void (/*thiscall*/ **)(char *, int))(v188 + 212))(this, pThis_49410);  // 经虚表字节 +212 调用
          pThis_49411 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);  // 虚表 +1172 调用（取动作数据（槽 293））
          sub_4015C0(pThis_49411, strlen((const char *)pThis_49411));  // 【std::string构造赋值】
          break;
        // ── [段 35] 第三重 case 14：★ 技能号语音/表现小表 —— switch(this[1991]) 七型 ──
        //   176 / 175 / 30 / 40 / 38 / 52 / default —— 纯 vt+212 播音效后 break（1991 索引 = 技能表号）
        case 14:  // 【case 14】分型分支
          pThis_7C7 = *((uint32_t *)this + 1991);  // 读 this+1991（nSkillNo）
          switch ( pThis_7C7 )  // switch(pThis_7C7) 多路分派
          {
            case 176:  // 【case 176】分型分支
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                this,  // 第 1 个实参 this
                "SM_ANCIENT_MEMORY",  // 第 2 个实参：串 SM_ANCIENT_MEMORY
                -1,  // 第 3 个实参
                0,  // 第 4 个实参
                0);  // 第 5 个实参
              break;
            case 175:  // 【case 175】分型分支
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                this,  // 第 1 个实参 this
                "SM_LEAP_BUFF",  // 第 2 个实参：串 SM_LEAP_BUFF
                -1,  // 第 3 个实参
                0,  // 第 4 个实参
                0);  // 第 5 个实参
              break;
            case 30:  // 【case 30】分型分支
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                this,  // 第 1 个实参 this
                "SM_MOON_CURTAIN",  // 第 2 个实参：串 SM_MOON_CURTAIN
                -1,  // 第 3 个实参
                0,  // 第 4 个实参
                0);  // 第 5 个实参
              break;
            case 40:  // 【case 40】分型分支
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                this,  // 第 1 个实参 this
                "SM_CONGESTION",  // 第 2 个实参：串 SM_CONGESTION
                -1,  // 第 3 个实参
                0,  // 第 4 个实参
                0);  // 第 5 个实参
              break;
            case 38:  // 【case 38】分型分支
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                this,  // 第 1 个实参 this
                "SM_OVERDRIVE",  // 第 2 个实参：串 SM_OVERDRIVE
                -1,  // 第 3 个实参
                0,  // 第 4 个实参
                0);  // 第 5 个实参
              break;
            case 52:  // 【case 52】分型分支
              (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
                this,  // 第 1 个实参 this
                "SM_QUAKE_WAVE",  // 第 2 个实参：串 SM_QUAKE_WAVE
                -1,  // 第 3 个实参
                0,  // 第 4 个实参
                0);  // 第 5 个实参
              break;
            default:
              break;
          }
          break;
        // ── [段 36] 第三重 default 与提前出口：v284 >= 0x10 时 j__free(v282) 释放 string 后 return ──
        //   此处 return 直接从第二重 case 10 内部退出函数（不落第二重出口）
        default:
          break;
      }
      if ( v284 >= 0x10 )
        j__free(v282);
      return;
    // ── [段 37] 第二重 case 21：★★ 本函数最大分支 —— 巨剑/旋风斩主演出（约 325 行）──
    //   vt+196(this[1548] 表参)；sub_42FC90(+30 对象) 取武器种类后 sub_4AECE0 切武器动画；
    //   含 sub_431920 建 grandWave 系 / GrabBlastBlood.ani / HardAttack 系多枚动画，
    //   及 vt+1140/vt+1160 多次取参 + sub_47EFD0/sub_47EF20 伤害与时长链；goto LABEL_290 回第二重出口
    case 21:  // 【case 21】分型分支
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 1548));  // 虚表 +196 调用（播放语音（槽 49））
      pThis_1E3 = *((void **)this + 30);
      v119 = sub_42FC90(pThis_1E3);  // 存 88B 元素计数
      sub_4AECE0(pThis_1E3, v119 - 1);  // 【解读】 【推断】动画切换: sub_491C70
      LOBYTE(fArg5) = 0;  // 异常展开状态号 → 0
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 2, 0, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        0,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      sub_495890(0, 0);  // 模式选择式方位设置
      sub_494F20(2, 0.0);  // 属性浮点槽写入
      v120 = *(uint32_t *)this;  // 取虚表指针
      pThis_987 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, 4);  // 虚表 +152 调用（取动作件（槽 38））
      (*(void (/*thiscall*/ **)(char *, int))(v120 + 896))(this, pThis_987);  // 经虚表字节 +896 调用
      pThis_8B = *((uint32_t *)this + 139) + 1064;
      ++*((uint32_t *)this + 1724);
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, pThis_8B);  // 虚表 +344 调用（清参（槽 86））
      pThis_1848 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
      pThis_47421 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 16);  // 虚表 +1140 调用（取技能值（槽 285））
      pThis_48814 = (char *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1160))(this, 16);  // 虚表 +1160 调用（取动画资源（槽 290））
      v126 = sub_47EFD0(pThis_48814, 0.0, pThis_47421, pThis_1848, pThis_1848, 0);  // 存 读技能表（浮点插值）
      v127 = *(uint32_t *)this;  // 取虚表指针
      *((float *)this + 97) = (float)v126;  // this 浮点槽 +97 写 v126
      v128 = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(v127 + 1172))(this, 1, -1, 0, 0);  // 经虚表字节 +1172 调用
      (*(void (/*thiscall*/ **)(char *, int))(v127 + 212))(this, v128);  // 经虚表字节 +212 调用
      pThis_49412 = (void *)(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1172))(this, 3);  // 虚表 +1172 调用（取动作数据（槽 293））
      sub_406D60(pThis_49412);  // std::string 从 C 串赋值
      v130 = *(uint32_t *)this;  // 取虚表指针
      *((uint32_t *)this + 2105) = 0;  // 写 this+2105（pVecBegin【推断】） = 0
      v131 = (*(int (/*thiscall*/ **)(char *))(v130 + 128))(this);  // 经虚表字节 +128 调用
      v132 = *(uint32_t *)this;  // 取虚表指针
      *((uint32_t *)this + 2106) = v131;  // 写 this+2106（pVecEnd【推断】） = v131
      *(this + 8413) = 0;  // 写 this+8413 → 0
      (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(v132 + 212))(this, "SKYRADE_SWING", -1, 0, 0);  // 经虚表字节 +212 调用
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 38] 第二重 case 22：★ 抓取爆炸（GrabBlastBlood.ani 等）—— +2112 分两支 ──
    //   +2112 != 0 时建 GrabBlastBlood.ani（+2113..+2115 系列）；否则走另一路；goto LABEL_290
    case 22:  // 【case 22】分型分支
      v133 = *(uint32_t *)this;  // 取虚表指针
      *((uint32_t *)this + 2112) = **(uint32_t **)(pArg3 + 4);  // 写 this+2112（nFinishVal【推断】） = **(uint32_t **)(pArg3 +
      *((uint32_t *)this + 2113) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);  // 写 this+2113 = *(uint32_t *)(*(uint32_t
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v133 + 876))(  // 经虚表字节 +876 调用
        this,  // 第 1 个实参 this
        0,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 3, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚表 +896 调用（帧组设置（槽 224））
      sub_495890(2, 0);  // 模式选择式方位设置
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 28));  // 虚表 +196 调用（播放语音（槽 49））
      if ( *((uint32_t *)this + 2112) != 0 )  // this+2112 不等于 0
      {
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 604))(this, 0);  // 虚表 +604 调用
        v134 = sub_45EBE0(*(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12));  // 存 id 对 → 对象查找
        pObj5 = __RTDynamicCast(v134, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
        *((uint32_t *)this + 2114) = pObj5;  // 写 this+2114（pAtkRateObj【推断】） = pObj5
        if ( pObj5 != 0 )  // pObj5 不等于 0
        {
          v136 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 120))(pObj5);
          pThis_842 = *((uint32_t *)this + 2114);  // 读 this+2114（pAtkRateObj【推断】）
          *((uint32_t *)this + 2115) = v136;  // 写 this+2115（f_AtkRate【推断】） = v136
          v138 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_842 + 124))(pThis_842);
          pThis_8422 = *((uint32_t *)this + 2114);  // 读 this+2114（pAtkRateObj【推断】）
          *((uint32_t *)this + 2116) = v138;  // 写 this+2116 = v138
          *((uint32_t *)this + 2117) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_8422 + 128))(pThis_8422);  // 写 this+2117（pSkillObj【推断】） = (*(int (·thiscall· **)
        }
        if ( *((uint32_t *)this + 2114) != 0 )  // this+2114 不等于 0
        {
          if ( *((uint32_t *)this + 2120) == 0 )  // this+2120（pAtkObj【推断】） 等于 0
          {
            LOBYTE(v288) = 15;  // 异常展开状态号 → 15
            if ( operator new(0x60u) != nullptr )
              v140 = sub_5EE930(this);  // 存 调: sub_5EE930 sub_4B1030 sub_650D20 sub_650D30
            else
              v140 = 0;  // 局部 v140 → 0
            LOBYTE(v288) = 0;  // 异常展开状态号 → 0
            *((uint32_t *)this + 2120) = v140;  // 写 this+2120（pAtkObj【推断】） = v140
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, char *, uint32_t, uint32_t, uint32_t, int))(**((uint32_t **)this + 2120) + 56))(
            *((uint32_t *)this + 2120),  // 第 1 个实参 this
            *((uint32_t *)this + 2114),  // 第 2 个实参
            this,  // 第 3 个实参
            0,  // 第 4 个实参
            0,  // 第 5 个实参
            0,  // 第 6 个实参
            -1);  // 第 7 个实参
        }
        pThis_48815 = (char *)(*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1160))(this, *((uint32_t *)this + 2113));  // 虚表 +1160 调用（取动画资源（槽 290））
        pThis_47422 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1140))(this, *((uint32_t *)this + 2113));  // 虚表 +1140 调用（取技能值（槽 285））
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(  // 虚表 +196 调用（播放语音（槽 49））
          this,  // 第 1 个实参 this
          *(uint32_t *)(*((uint32_t *)this + 1554) + 28));  // 第 2 个实参
        if ( *((uint32_t *)this + 2113) == 31 )  // this+2113 等于 31
        {
          LOBYTE(fArg5) = 0;  // 异常展开状态号 → 0
          sub_4AECE0(*((void **)this + 30), 16);  // 【解读】 【推断】动画切换: sub_491C70
          if ( *((uint32_t *)this + 2121) == 0 )  // this+2121 等于 0
          {
            LOBYTE(v288) = 16;  // 异常展开状态号 → 16
            if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
            {
              if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
                pThis_6C15 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/GrabBlastBlood.ani", 1);  // 存 建动画件 Effect/Animation/GrabBlastBlood.ani
              else
                pThis_6C15 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/GrabBlastBlood.ani", 1);  // 存 建动画件 Effect/Animation/GrabBlastBlood.ani
            }
            else
            {
              pThis_6C15 = 0;  // 局部 pThis_6C15 → 0
            }
            LOBYTE(v288) = 0;  // 异常展开状态号 → 0
            *((uint32_t *)this + 2121) = pThis_6C15;  // 写 this+2121 = pThis_6C15
          }
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
            this,  // 第 1 个实参 this
            1,  // 第 2 个实参
            *((uint32_t *)this + 2121),  // 第 3 个实参
            43,  // 第 4 个实参
            -90,  // 第 5 个实参
            0,  // 第 6 个实参
            0);  // 第 7 个实参
          v144 = sub_47E9D0(pThis_48815, 0);  // 存 读技能表（14 字节条目，索引=pThis_48815）
          v145 = *(uint32_t *)this;  // 取虚表指针
          *((uint32_t *)this + 2118) = v144;  // 写 this+2118（nFinishFlag【推断】） = v144
          pThis_8B2 = *((uint32_t *)this + 139) + 1520;
          *((uint32_t *)this + 2119) = 0;  // 写 this+2119（bFinishFlag【推断】） = 0
          (*(void (/*thiscall*/ **)(char *, int))(v145 + 344))(this, pThis_8B2);  // 经虚表字节 +344 调用
          pThis_1849 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 388))(this);  // 虚表 +388 调用（取时长（槽 97））
          v147 = sub_47EFD0(pThis_48815, 0.0, pThis_47422, pThis_1849, pThis_1849, 0);  // 存 读技能表（浮点插值）
          v148 = *(uint32_t *)this;  // 取虚表指针
          *((float *)this + 97) = (float)v147;  // this 浮点槽 +97 写 v147
          (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(v148 + 212))(this, "BLOOD_HOLD", -1, 0, 0);  // 经虚表字节 +212 调用
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 344))(this, *((uint32_t *)this + 139) + 1368);  // 虚表 +344 调用（清参（槽 86））
        sub_4AECE0(*((void **)this + 30), 3);  // 【解读】 【推断】动画切换: sub_491C70
        LOBYTE(fArg5) = 0;  // 异常展开状态号 → 0
      }
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 39] 第二重 case 23：★ 巨浪三态（grandWaveOnCharge1/2 / grandWave.ani）──
    //   pArg3[1][0] 为 1 / 2 两支分别回挂；+2122 分 1/2 两支各建两枚 grandWaveOnCharge 或 grandWave.ani；
    //   末段按 +2122 <2 / ==2 / ==1 / ==0 四支处理（2252/2254 行），goto LABEL_290
    case 23:  // 【case 23】分型分支
      v149 = **(uint32_t **)(pArg3 + 4);  // 二级解引用取 pArg3+4
      *((uint32_t *)this + 2122) = v149;  // 写 this+2122 = v149
      if ( v149 == 1 )  // v149 等于 1
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
          this,  // 第 1 个实参 this
          "SM_GUE_CHARGE",  // 第 2 个实参：串 SM_GUE_CHARGE
          12,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
          this,  // 第 1 个实参 this
          "AIR_SWORD_READY",  // 第 2 个实参：串 AIR_SWORD_READY
          16,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
      }
      else if ( v149 == 2 )  // 否则若 v149 等于 2
      {
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚表 +212 调用（播放动作/播报（槽 53））
          this,  // 第 1 个实参 this
          "R_SM_GUE",  // 第 2 个实参：串 R_SM_GUE
          11,  // 第 3 个实参
          0,  // 第 4 个实参
          0);  // 第 5 个实参
      }
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 4));  // 虚表 +196 调用（播放语音（槽 49））
      (*(void (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        0,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 虚表 +876 调用（位移下发（槽 219））
        this,  // 第 1 个实参 this
        1,  // 第 2 个实参
        0,  // 第 3 个实参
        0,  // 第 4 个实参
        0,  // 第 5 个实参
        0,  // 第 6 个实参
        0);  // 第 7 个实参
      (*(void (/*thiscall*/ **)(char *, uint32_t, int, int, int))(*(uint32_t *)this + 888))(this, 0, 4, 1000, 1000);  // 虚表 +888 调用（动画时长设置（槽 222））
      (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚表 +896 调用（帧组设置（槽 224））
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 596))(this, 0);  // 虚表 +596 调用
      if ( *((uint32_t *)this + 2122) == 2 )  // this+2122 等于 2
        *((uint32_t *)this + 2123) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);  // 写 this+2123 = *(uint32_t *)(*(uint32_t
      pThis_84A2 = *((uint32_t *)this + 2122);  // 读 this+2122
      if ( pThis_84A2 == 1 )  // pThis_84A2 等于 1
      {
        pThis_21382 = this + 8504;  // 取 this 偏移 8504 的指针
        if ( *((uint32_t *)this + 2126) == 0 )  // this+2126（f_2138【推断】） 等于 0
        {
          LOBYTE(v288) = 17;  // 异常展开状态号 → 17
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C16 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWaveOnCharge1.ani", 1);  // 存 建动画件 Effect/Animation/grandWaveOnCharge1.ani
            else
              pThis_6C16 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWaveOnCharge1.ani", 1);  // 存 建动画件 Effect/Animation/grandWaveOnCharge1.ani
          }
          else
          {
            pThis_6C16 = 0;  // 局部 pThis_6C16 → 0
          }
          *pThis_21382 = pThis_6C16;
          LOBYTE(v288) = 18;  // 异常展开状态号 → 18
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C17 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWaveOnCharge2.ani", 1);  // 存 建动画件 Effect/Animation/grandWaveOnCharge2.ani
            else
              pThis_6C17 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWaveOnCharge2.ani", 1);  // 存 建动画件 Effect/Animation/grandWaveOnCharge2.ani
          }
          else
          {
            pThis_6C17 = 0;  // 局部 pThis_6C17 → 0
          }
          LOBYTE(v288) = 0;  // 异常展开状态号 → 0
          *((uint32_t *)this + 2127) = pThis_6C17;  // 写 this+2127（f_213C【推断】） = pThis_6C17
        }
        v154 = 0;  // 局部 v154 → 0
        do
        {
          v155 = v154 + 1;
          (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
            this,  // 第 1 个实参 this
            v154 + 1,  // 第 2 个实参
            *pThis_21382,  // 第 3 个实参
            0,  // 第 4 个实参
            0,  // 第 5 个实参
            0,  // 第 6 个实参
            0);  // 第 7 个实参
          v154 = v155;  // v154 复制自 v155
          ++pThis_21382;  // pThis_21382 自增
        }
        while ( v155 < 2 );
      }
      else if ( pThis_84A2 == 2 )  // 否则若 pThis_84A2 等于 2
      {
        if ( *((uint32_t *)this + 2125) == 0 )  // this+2125（nChargeTime【推断】） 等于 0
        {
          LOBYTE(v288) = 19;  // 异常展开状态号 → 19
          if ( sub_42FCB0(228) != 0 )  // 若 CRT 一次性初始化 【CRT 一次性初始化】首建全局容器 &unk_8F8130(228) 不等于 0
          {
            if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 长度 < 0x10u（短串内联判定）
              pThis_6C18 = sub_431920((uint8_t)this + 108, (char)"Effect/Animation/grandWave.ani", 1);  // 存 建动画件 Effect/Animation/grandWave.ani
            else
              pThis_6C18 = sub_431920(*((uint32_t *)this + 91), (char)"Effect/Animation/grandWave.ani", 1);  // 存 建动画件 Effect/Animation/grandWave.ani
          }
          else
          {
            pThis_6C18 = 0;  // 局部 pThis_6C18 → 0
          }
          LOBYTE(v288) = 0;  // 异常展开状态号 → 0
          *((uint32_t *)this + 2125) = pThis_6C18;  // 写 this+2125（nChargeTime【推断】） = pThis_6C18
        }
        (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚表 +204 调用（挂动画件（槽 51））
          this,  // 第 1 个实参 this
          1,  // 第 2 个实参
          *((uint32_t *)this + 2125),  // 第 3 个实参
          0,  // 第 4 个实参
          0,  // 第 5 个实参
          0,  // 第 6 个实参
          0);  // 第 7 个实参
      }
      pThis_84A3 = *((uint32_t *)this + 2122);  // 读 this+2122
      if ( pThis_84A3 < 2 )
      {
        pThis_1E4 = *((uint32_t *)this + 30);  // 读 this+30（pAnimObj【推断】）
        v161 = sub_491C70(pThis_1E4, 0);  // 存 帧时刻换算
        sub_493A60(pThis_1E4, v161);  // 时间推进包装
        sub_4939E0(*((uint32_t *)this + 30), 1);  // 播放/暂停级联
        LOBYTE(fArg5) = 0;  // 异常展开状态号 → 0
      }
      else if ( pThis_84A3 == 2 )  // 否则若 pThis_84A3 等于 2
      {
        sub_4AECE0(*((void **)this + 30), 1);  // 【解读】 【推断】动画切换: sub_491C70
        sub_4939E0(*((uint32_t *)this + 30), 0);  // 播放/暂停级联
        v158 = *(uint32_t *)this;  // 取虚表指针
        LOBYTE(fArg5) = 0;  // 异常展开状态号 → 0
        pThis_49413 = (*(int (/*thiscall*/ **)(char *, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);  // 虚表 +1172 调用（取动作数据（槽 293））
        (*(void (/*thiscall*/ **)(char *, int))(v158 + 212))(this, pThis_49413);  // 经虚表字节 +212 调用
        *(this + 8516) = 0;  // 写 this+8516 → 0
      }
      if ( *((uint32_t *)this + 2122) == 1 )  // this+2122 等于 1
        *(this + 8496) = 0;  // 写 this+8496 → 0
      if ( *((uint32_t *)this + 2122) == 0 )  // this+2122 等于 0
      {
        pThis_47423 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 1140))(this, 50);  // 虚表 +1140 调用（取技能值（槽 285））
        (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)this + 1160))(this, 50, pThis_47423);  // 虚表 +1160 调用（取动画资源（槽 290））
        v163 = sub_4B1C40(v255);  // 存 14 字节表按 1 基索引取值 基址 *
        v164 = *(uint32_t *)this;  // 取虚表指针
        v255 = 0;  // 局部 v255 → 0
        pThis_6803 = 1000 * v163 / *((uint32_t *)this + 1664);  // 乘算后按 this+1664 归一
        *((uint32_t *)this + 2128) = pThis_6803;  // 写 this+2128（pAnimF【推断】） = pThis_6803
        (*(void (/*thiscall*/ **)(char *, int))(v164 + 992))(this, pThis_6803);  // 经虚表字节 +992 调用
      }
      goto LABEL_290;  // 转到 LABEL_290
    // ── [段 40] 第二重 default：直接 goto LABEL_290 走第二重出口（非法动作号静默）──
    default:
      goto LABEL_290;  // 转到 LABEL_290
  }
}

