// ============================================================
// 【40JP逆向源代码工程】src/combat/bigfunc_5EA970_sub_5EA970.cpp
// 巨型函数专项（>8KB，批量转写时跳过，单独反编译 @0x5EA970）
// 层级: L2 转写层（单文件单函数，放宽行数上限）
// ============================================================
// ------------------------------------------------------------
// 路标注释（主代理自研流水线自动生成）：
//   函数体 2164 行；字符串证据 5 条；外调 6 个
//   串: "FT_SIT"
//   串: "G_BONECRUSHER"
//   串: "G_LOWKICK"
//   串: "R_FT_KICK_LOW"
//   串: "FT_KENSIN"
//   调: sub_5EA970 sub_5E6920 sub_49C620 sub_47E9D0 sub_49C5F0 sub_432E50
// ------------------------------------------------------------

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x5EA970 sub_5EA970  size=10856
// ------------------------------------------------------------
int /*thiscall*/ sub_5EA970(int this, int nArg2, uint32_t **pArg3, int nArg4, int nArg5)  // 实现：size=10856
{
  int pThis_47412; // ebx
  int nSubStateB; // eax  | +0x1E88 → ★ 子状态 B（CNFighter；va=005EA970）
  int v8; // edx
  uint32_t *pThis_488; // eax
  int v10; // eax
  uint32_t *pThis_204C; // edi
  int i; // ebx
  int pHoldObj; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int pHoldObj_4; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v15; // edi
  int pThis_78; // eax
  int pHoldObj_5; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v18; // eax
  int pHoldObj_6; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  char bSubMode; // al  | +0x2085 → ★ 抱人子模式（0x5EA970: !=0 时按 vt+192()/10 算目标 X）（CNFighter；va=005EA970）
  int nHoldSrc; // eax  | +0x207C → 抱人朝向/源对象（0x5EA970 读 +8316 经 sub_432E50 转换）（CNFighter；va=005EA970）
  int pHoldHost; // ecx  | +0x2080 → 【推断】抱人宿主/锚（0x5EA970 收尾 *(this+8320) 调 vt+76(0)）（CNFighter；va=005EA970）
  uint32_t *fld_2084; // edi
  int v24; // eax
  uint32_t *pThis_2090; // edi
  int j; // ebx
  int pHoldTarget; // ecx  | +0x20A4 → ★ 抱人目标对象（CNFighter；va=005EA970）
  int v28; // edi
  int pThis_7C; // eax
  int pThis_782; // eax
  uint32_t *k; // edi
  int nChargeState; // eax  | +0x2130 → 0x5EA970 读取槽（CNFighter；va=005EA970）
  int nArg22; // edi
  int v34; // edi
  int pThis_474; // eax
  int pHostComp; // edi  | +0x0070 → 【推断】默认共享组件/宿主对象指针（CNFighter；va=005EA970）
  int v37; // eax
  int v38; // edi
  int pThis_98; // eax
  int v40; // edx
  int v41; // edi
  char *fld_2030; // ebx
  int nParamCnt; // eax  | +0x2030 → ★ 抓取参数个数（0x5EA970: *(this+8240)=v259，作 pArg3 索引）（CNFighter；va=005EA970）
  void *v44; // eax
  int v45; // eax
  int pThis_184; // eax
  int v47; // eax
  int v48; // ecx
  int v49; // edi
  int pThis_982; // eax
  int v51; // eax
  uint32_t *v52; // eax
  int nPhaseA; // ebx  | +0x2044 → ★ 相位值 A（0x5EA970: 与 +8244 配对，==4 特例）（CNFighter；va=005EA970）
  int nPhaseB; // edi  | +0x2048 → ★ 相位值 B（0x5EA970: +8248==15 组合）（CNFighter；va=005EA970）
  int nVariantVal; // eax  | +0x2038 → ★ 变体值（0x5EA970 与 +8244 配对判定）（CNFighter；va=005EA970）
  void *v56; // eax
  int v57; // edi
  uint64_t v58; // rax
  int v59; // ebx
  int pThis_783; // eax
  int v61; // edi
  int pThis_7C2; // eax
  int v63; // ebx
  int v64; // edi
  int pThis_983; // eax
  int pThis_80; // eax
  int pThis_1842; // eax
  int pThis_178; // eax
  bool v69; // zf
  int pThis_6C; // eax
  int pThis_6C2; // eax
  int v72; // edi
  int pThis_4744; // eax
  int pThis_4745; // edi
  int v75; // edi
  int pThis_4746; // eax
  int v77; // edx
  uint32_t *v78; // eax
  int nGrabSkillNo; // edx  | +0x205C → 0x5EA970 写入槽（v260）（CNFighter；va=005EA970）
  int v80; // eax
  int nGrabSkillNo_; // eax  | +0x205C → 0x5EA970 写入槽（v260）（CNFighter；va=005EA970）
  int pSubCtx; // eax  | +0x1848 → ★ 技能参数/子上下文指针（CNFighter；va=005EA970）
  int pThis_4747; // eax
  int nGrabDataVal; // ecx  | +0x2060 → 0x5EA970 写入槽（v80）（CNFighter；va=005EA970）
  int pHostComp_; // eax  | +0x0070 → 【推断】默认共享组件/宿主对象指针（CNFighter；va=005EA970）
  uint64_t v86; // rax
  int v87; // edi
  int pThis_984; // eax
  int pSkillObj; // ecx  | +0x2114 → 【推断】技能对象指针（0x5EA970 读 *(this+8468)，非 0 时经 vt+64 写 +40）（CNFighter；va=005EA970）
  bool v90; // al
  int v91; // eax
  int pObj4; // eax
  int v93; // eax
  int pHoldObj_9; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v95; // eax
  int pHoldObj_10; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int pHoldObj_11; // eax  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v98; // eax
  int v99; // edx
  uint32_t **pThis_20902; // edi
  uint32_t *pThis_6C5; // eax
  int pThis_6C6; // eax
  int pHoldObj_; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v104; // eax
  void *Block2; // ebx
  int v106; // edx
  int pSubCtx_; // eax  | +0x1848 → ★ 技能参数/子上下文指针（CNFighter；va=005EA970）
  int nGrabAnimBase; // eax  | +0x022C → ★ 投技/抓取动画偏移基（CNFighter；va=005EA970）
  int v109; // eax
  int fld_20842; // edi  | +0x2084 → ★ 抱人模式字节（0x5EA970: !=0 选 18 号参数否则 9 号 → vt+1160）（CNFighter；va=005EA970）
  int pThis_1845; // ebx
  void *pThis_47410; // eax
  int v113; // edx
  char *v114; // eax
  char bSubMode_; // al  | +0x2085 → ★ 抱人子模式（0x5EA970: !=0 时按 vt+192()/10 算目标 X）（CNFighter；va=005EA970）
  char *pThis_4885; // edi
  int pThis_47411; // ebx
  int pThis_1846; // eax
  int v119; // eax
  int fld_18484; // eax  | +0x1848 → ★ 技能参数/子上下文指针（CNFighter；va=005EA970）
  int pSubCtx_2; // eax  | +0x1848 → ★ 技能参数/子上下文指针（CNFighter；va=005EA970）
  int v122; // edx
  int v123; // eax
  int pObj3; // eax
  int fld_20A42; // edi  | +0x20A4 → ★ 抱人目标对象（CNFighter；va=005EA970）
  int v126; // eax
  int *v127; // eax
  int v128; // ecx
  int v129; // edi
  int v130; // eax
  int pHoldTarget_; // ecx  | +0x20A4 → ★ 抱人目标对象（CNFighter；va=005EA970）
  int v132; // ebx
  int *pHoldTarget_2; // edi
  int v134; // edx
  int v135; // eax
  int v136; // eax
  int v137; // edi
  int fld_20A45; // eax  | +0x20A4 → ★ 抱人目标对象（CNFighter；va=005EA970）
  int v139; // eax
  void *pThis_4945; // eax
  char *pThis_4886; // edi
  int pThis_1847; // eax
  int pHoldTarget_3; // eax  | +0x20A4 → ★ 抱人目标对象（CNFighter；va=005EA970）
  int v144; // edx
  void *pThis_35; // eax
  double v146; // st7
  int v147; // eax
  void *v148; // eax
  int v149; // edx
  int v150; // eax
  int pHoldTarget_4; // ecx  | +0x20A4 → ★ 抱人目标对象（CNFighter；va=005EA970）
  int nSkillGate; // edi  | +0x20FC → ★ 0x5EA970: nArg2!=21 && nArg2!=6 && *(this+8444)>0 门（CNFighter；va=005EA970）
  int v153; // edx
  int v154; // edi
  int pThis_47413; // ebx
  char *pThis_4887; // eax
  int pThis_47414; // edi
  char *pThis_4888; // ebx
  int pThis_1848; // eax
  void *v160; // eax
  int v161; // edx
  int v162; // edi
  int pThis_2A0; // eax
  int pThis_6C7; // eax
  int v165; // edx
  char *pThis_4889; // edi
  int pThis_47415; // ebx
  int pThis_1849; // eax
  int v169; // eax
  int pThis_2A02; // eax
  int v171; // edi
  int pThis_987; // eax
  int v173; // edi
  int v174; // eax
  void *pThis_4946; // eax
  int v176; // edx
  int pThis_18410; // edi
  int pThis_47416; // ebx
  char *pThis_48810; // eax
  void *v180; // eax
  int v181; // edx
  int v182; // edi
  int pThis_4947; // eax
  int v184; // eax
  int pObj; // eax
  int v186; // eax
  int pHoldObj_2; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v188; // eax
  int pHoldObj_3; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v190; // eax
  int v191; // eax
  char *v192; // edi
  int pThis_47417; // ebx
  int nChargeState_; // eax  | +0x2130 → 0x5EA970 读取槽（CNFighter；va=005EA970）
  uint64_t fld_703; // rax  | +0x0070 → 【推断】默认共享组件/宿主对象指针（CNFighter；va=005EA970）
  int fld_7032; // ebx
  void (/*thiscall*/ **v197)(int, int); // edi
  int pThis_988; // eax
  void *pAnimObj; // ecx
  int pThis_18411; // eax
  void *v201; // eax
  int v202; // edx
  int v203; // eax
  int v204; // eax
  void *fld_2134; // eax
  int nChargeTime; // edx  | +0x2134 → 0x5EA970: *(this+8500) >= dword_9B9348 门（CNFighter；va=005EA970）
  int v207; // eax
  int v208; // ebx
  int v209; // eax
  int pThis_6C8; // eax
  int result; // eax
  uint32_t *v213; // ecx
  int v214; // ecx
  char *pThis_4882; // edi
  int pThis_4748; // ebx
  int pThis_1843; // eax
  int v218; // eax
  int v219; // edx
  int v220; // edi
  int pThis_4943; // eax
  void *pThis_4944; // eax
  int v223; // edi
  int pThis_494; // eax
  void *pThis_4942; // eax
  int *v226; // ecx
  char *pThis_4883; // edi
  int nGrabTargetSel; // ebx  | +0x201C → ★ 抓取目标选择（CNFighter；va=005EA970）
  int pThis_1844; // eax
  char *pThis_4884; // edi
  int fld_201C2; // eax  | +0x201C → ★ 抓取目标选择（CNFighter；va=005EA970）
  int v232; // edx
  int fld_201C22; // ebx
  int v234; // eax
  int v235; // edx
  int pAppendage; // ecx  | +0x20D0 → ★ 附属物/状态组件指针（0x5EA970 非 0 且其 vt+80 通过时执行加算分支）（CNFighter；va=005EA970）
  int nSubStateB_; // eax  | +0x1E88 → ★ 子状态 B（CNFighter；va=005EA970）
  int pThis_6C3; // eax
  int pThis_6C4; // eax
  int v240; // edi
  int pThis_985; // eax
  int v242; // edx
  int v243; // edi
  int pThis_986; // eax
  int v245; // edi
  int pThis_4749; // eax
  int v247; // eax
  int pObj2; // eax
  int v249; // eax
  int pHoldObj_7; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v251; // eax
  int pHoldObj_8; // ecx  | +0x206C → ★ 被擒/被抱对象指针（CNFighter；va=005EA970）
  int v253; // eax
  int v254; // ecx
  int pThis_4743; // [esp-Ch] [ebp-60h]
  int v256; // [esp-Ch] [ebp-60h]
  int v257; // [esp-Ch] [ebp-60h]
  int fld_213422; // [esp-8h] [ebp-5Ch]
  int v259; // [esp-4h] [ebp-58h]
  int v260; // [esp-4h] [ebp-58h]
  int dword_9B93482; // [esp-4h] [ebp-58h]
  int v262; // [esp+0h] [ebp-54h]
  int v263; // [esp+4h] [ebp-50h]
  int v264; // [esp+8h] [ebp-4Ch]
  int v265; // [esp+Ch] [ebp-48h] BYREF
  float v266; // [esp+10h] [ebp-44h]
  float v267; // [esp+14h] [ebp-40h]
  int v268; // [esp+18h] [ebp-3Ch]
  int v269; // [esp+1Ch] [ebp-38h]
  int v270; // [esp+20h] [ebp-34h]
  void *v271; // [esp+24h] [ebp-30h] BYREF
  int v272; // [esp+28h] [ebp-2Ch]
  int v273; // [esp+2Ch] [ebp-28h]
  int v274; // [esp+30h] [ebp-24h]
  void *Block; // [esp+34h] [ebp-20h] BYREF
  int pThis_4742; // [esp+38h] [ebp-1Ch] BYREF
  int v277; // [esp+3Ch] [ebp-18h] BYREF
  int pThis_784; // [esp+40h] [ebp-14h] BYREF
  int nBigState; // [esp+44h] [ebp-10h]  | +0x199C → ★ 角色大状态 ID（0x5EA970 switch 总闸；IRDActiveObject +6556 定案）（CNFighter；va=005EA970）
  int v280; // [esp+50h] [ebp-4h]
  void *v281; // [esp+60h] [ebp+Ch]
  void *v282; // [esp+60h] [ebp+Ch]
  void *pMem; // [esp+60h] [ebp+Ch]

  // ── [段 1] 入口：取大状态机状态号 this+6556 → fld_199C，清 pThis_47412，进第一重 switch ──
  //   this = CNFighter 对象（本函数 = CNFighter::vt+472，class_method_slots.txt 直证）；
  //   nArg2 = 动作/事件号；pArg3 = 技能参数数组（pArg3[1][N] 取参）；字段语义见 include/arad/_fields/CNFighter.h
  nBigState = *(uint32_t *)(this + 6556);  // 字段 nBigState(this+6556) 读写
  pThis_47412 = 0;
  switch ( nBigState )  // 按 fld_199C 分派
  {
    // ── [段 2] 大状态 case 10：收招/形态切换分支 —— 按子状态 +7816 三型分派（12/16/49）──
    //   +7812 非 0 直接跳过；12 与 16 按 +7808 选回挂 +8380/+8388 缓存动画（vt+208 挂载）；
    //   49 且 nArg2 != 10 时：vt+604 + sub_5E6920（收招）+ sub_49C620/sub_49C5F0 音效对 + vt+1160(49,8) 取参
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      if ( *(uint32_t *)(this + 7812) == 0 )  // 字段 nSubStateA(this+7812) 判定
      {
        nSubStateB = *(uint32_t *)(this + 7816);  // 字段 nSubStateB(this+7816) 读写
        if ( nSubStateB == 12 )  // fld_1E88 == 12 判定
        {
          v8 = *(uint32_t *)this;  // 缓存对象虚表基址
          if ( *(uint32_t *)(this + 7808) != 0 )  // 字段 nStyleSel(this+7808) 判定
            (*(void (/*stdcall*/ **)(uint32_t))(v8 + 208))(*(uint32_t *)(this + 8388));  // 字段 pAnimD(this+8388) 读写
          else
            (*(void (/*stdcall*/ **)(uint32_t))(v8 + 208))(*(uint32_t *)(this + 8380));  // 字段 pAnimC(this+8380) 读写
        }
        else if ( nSubStateB == 16 )  // 子型 fld_1E88=16
        {
          if ( *(uint32_t *)(this + 7808) == 0 )  // 字段 nStyleSel(this+7808) 判定
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8380));  // 虚槽+208 → 动画件回挂
        }
        else if ( nSubStateB == 49 && nArg2 != 10 )  // 子型 fld_1E88=49
        {
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 604))(this);  // 虚槽+604 → 收招例程
          sub_5E6920(this);  // 调 抓取/投技子例程
          sub_49C620(0, 1, 0);  // sub_49C620 · 命令下发包装
          pThis_488 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1160))(this, 49, 8);  // 虚槽+1160 → 读技能表(变体)
          v10 = sub_47E9D0(pThis_488, 1u);  // 调 收招/结束例程
          sub_49C5F0(0, 0, 0, v10);  // sub_49C5F0 · 命令记录写入包装
        }
      }
      break;  // 跳出本 switch(单 case 处理完)
    // ── [段 3] 大状态 case 17：+8244==1 且 +8248==15 时把 +8268 起 2 个动画件回挂（vt+208）──
    case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
      if ( *(uint32_t *)(this + 8244) == 1 && *(uint32_t *)(this + 8248) == 15 )  // 字段 nVariantSel(this+8244) 判定
      {
        pThis_204C = (uint32_t *)(this + 8268);  // this+8268〔nParamArr(推断)〕
        for ( i = 2; i != 0; --i )  // 重复 2 次回挂(倒计数)
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_204C++);  // 虚槽+208 → 动画件回挂
        pThis_47412 = 0;
      }
      break;  // 跳出本 switch(单 case 处理完)
    // ── [段 4] 大状态 case 18：vt+604(1) 收招；+8292 抓取标志非 0 则跳 LABEL_62（磨能充能收束）──
    case 18:  // case 18 = ENUM_CMDPACKET_SEND_MESSAGE
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 604))(this, 1);  // 虚槽+604 → 收招例程
      if ( *(uint8_t *)(this + 8292) != 0 )  // 字节字段 bModeFlag(this+8292) 判定
        goto LABEL_62;  // 跳转 LABEL_62(收尾/共用分支)
      break;  // 跳出本 switch(单 case 处理完)
    // ── [段 5] 大状态 case 19：★ 擒抱把被擒目标放到指定位（+8300 目标对象族）──
    //   目标 vt+308 存活判据、vt+192 取尺寸、vt+124/128 取当前坐标，按 +8325 决定 1/10 或 3/4 偏移；
    //   vt+136/vt+132/vt+140 三条放置路径（精确落点 / 100 单位搜索 / 兜底用 +8304/+8308/+8312 存位）；
    //   随后 sub_431230 压 5 参（方向码/2/1/0.0/0.0）→ vt+560(4, buf, 2, 0) + vt+564 提交，sub_5E5260 释放缓冲；
    //   尾部 vt+596(1) + 清 +8300 + 宿主 vt+76(0) + vt+1160(18 或 9) 取参 + 音效对
    case 19:  // case 19 = ENUM_CMDPACKET_DELETE_ITEM
      pHoldObj = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
      if ( pHoldObj != 0 )  // 子型 fld_206C 非 0 判定
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj + 308))(pHoldObj) != 0 )  // 虚槽+308 → 是否本地玩家
        {
          pHoldObj_4 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
          if ( *(uint8_t *)(this + 8325) != 0 )  // 字节字段 bSubMode(this+8325) 判定
            v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_4 + 192))(pHoldObj_4) / 10;  // 虚槽+192 → 取尺寸/包围盒
          else
            v15 = 3 * (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_4 + 192))(pHoldObj_4) / 4;  // 虚槽+192 → 取尺寸/包围盒
          if ( *(uint32_t *)(this + 8316) != 0 )  // 字段 nHoldSrc(this+8316) 判定
            pThis_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - v15;  // 虚槽+120 → 转发(对象+缓冲)
          else
            pThis_78 = v15 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);  // 虚槽+120 → 转发(对象+缓冲)
          pHoldObj_5 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
          pThis_784 = pThis_78;
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_5 + 124))(pHoldObj_5);  // 虚槽+124 → 目标坐标y下界
          pHoldObj_6 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
          v277 = v18;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pHoldObj_6 + 136))(pHoldObj_6, pThis_784, v18, 0) != 0  // 虚槽+136 → 目标挂接
            && (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8300) + 132))(  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
                 *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
                 0) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 8300) + 108))(  // 调用
              *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
              pThis_784,
              v277,
              0);
          }
          else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int *, int *, int, int, int, int, int))(**(uint32_t **)(this + 8300) + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
                      *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
                      &pThis_784,
                      &v277,
                      pThis_784,
                      v277,
                      100,
                      1,
                      1) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 8300) + 108))(  // 调用
              *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
              pThis_784,
              v277,
              0);
          }
          else
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8300) + 108))(  // 调用
              *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
              *(uint32_t *)(this + 8304),  // this+8304〔nHoldPosX(推断)〕
              *(uint32_t *)(this + 8308),  // this+8308〔nHoldPosY(推断)〕
              *(uint32_t *)(this + 8312));  // this+8312〔nHoldPosZ(推断)〕
          }
          v272 = 0;
          v273 = 0;
          v274 = 0;
          bSubMode = *(uint8_t *)(this + 8325);  // 字节字段 bSubMode(this+8325) 判定
          v280 = 0;
          if ( bSubMode != 0 )  // 子型 fld_2085 非 0 判定
            nHoldSrc = *(uint32_t *)(this + 8316);  // 字段 nHoldSrc(this+8316) 读写
          else
            nHoldSrc = sub_432E50(*(uint32_t *)(this + 8316));  // fld_207C = sub_432E50 · 关系码对调映射
          pThis_4742 = nHoldSrc;
          sub_431230((int)&v271, &pThis_4742);  // sub_431230 · uint32 vector push_back
          Block = (void *)2;  // Block = 取 2(转指针/类型)
          sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
          Block = (void *)1;  // Block = 取 1(转指针/类型)
          sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
          *(float *)&Block = 0.0;  // 写内存
          sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
          *(float *)&Block = 0.0;  // 写内存
          sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
          (*(void (/*thiscall*/ **)(uint32_t, int, void **, int, uint32_t))(**(uint32_t **)(this + 8300) + 560))(  // 调用
            *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
            4,
            &v271,
            2,
            0);
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8300) + 564))(*(uint32_t *)(this + 8300));  // 字段 pHoldObj(this+8300) 读写
          v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          sub_5E5260(&v271);  // 调 动画子对象清理临时缓冲
        }
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8300) + 596))(*(uint32_t *)(this + 8300), 1);  // 字段 pHoldObj(this+8300) 读写
        pHoldHost = *(uint32_t *)(this + 8320);  // 字段 pHoldHost(this+8320) 读写
        *(uint32_t *)(this + 8300) = 0;  // 字段 pHoldObj(this+8300) 读写
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pHoldHost + 76))(pHoldHost, 0);  // 虚槽+76
        fld_2084 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(  // 调虚槽 +1160
                          this,
                          *(uint8_t *)(this + 8324) != 0 ? 18 : 9);  // this+8324〔bHoldMode(推断)〕
        sub_49C620(0, 1, 0);  // sub_49C620 · 命令下发包装
        v24 = sub_47E9D0(fld_2084, 1u);  // 调 收招/结束例程
        sub_49C5F0(0, 0, 0, v24);  // sub_49C5F0 · 命令记录写入包装
      }
      if ( *(uint8_t *)(this + 8324) != 0 && *(uint8_t *)(this + 8334) != 0 )  // 字节字段 bHoldMode(this+8324) 判定
      {
        pThis_2090 = (uint32_t *)(this + 8336);  // this+8336〔pVtStack〕
        for ( j = 2; j != 0; --j )  // 重复 2 次回挂(倒计数)
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_2090++);  // 虚槽+208 → 动画件回挂
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 11);  // 虚槽+216 → 全场广播
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 12);  // 虚槽+216 → 全场广播
        *(uint8_t *)(this + 8334) = 0;  // 字节字段 bPairOk(this+8334) 判定
        pThis_47412 = 0;
      }
      break;  // 跳出本 switch(单 case 处理完)
    // ── [段 6] 大状态 case 20：骑乘收尾 —— nArg2 != 20 时先释放 +8356 目标（vt+308 判活 → vt+612 拆分）──
    //   再按本帧位置与 +8364/+8368 存位比对（vt+136 判可站立）决定是否 vt+112 复位坐标
    case 20:  // case 20 = ENUM_CMDPACKET_MOVE_ITEMSPACE
      if ( nArg2 != 20 )  // 动作号非 20 判定
      {
        pHoldTarget = *(uint32_t *)(this + 8356);  // 字段 pHoldTarget(this+8356) 读写
        if ( pHoldTarget != 0 )  // 子型 fld_20A4 非 0 判定
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pHoldTarget + 308))(pHoldTarget) != 0 )  // 虚槽+308 → 是否本地玩家
          {
            v272 = 0;
            v273 = 0;
            v274 = 0;
            v280 = 1;
            Block = (void *)4;  // Block = 取 4(转指针/类型)
            sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
            Block = (void *)2;  // Block = 取 2(转指针/类型)
            sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
            Block = (void *)1;  // Block = 取 1(转指针/类型)
            sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
            *(float *)&Block = 0.0;  // 写内存
            sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
            *(float *)&Block = 0.0;  // 写内存
            sub_431230((int)&v271, &Block);  // sub_431230 · uint32 vector push_back
            (*(void (/*thiscall*/ **)(uint32_t, int, void **, int, uint32_t))(**(uint32_t **)(this + 8356) + 560))(  // 调用
              *(uint32_t *)(this + 8356),  // this+8356〔uPick8356(推断)〕
              4,
              &v271,
              2,
              0);
            (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8356) + 564))(*(uint32_t *)(this + 8356));  // 字段 pHoldTarget(this+8356) 读写
            v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            sub_5E5260(&v271);  // 调 动画子对象清理临时缓冲
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8356) + 612))(  // 调用
            *(uint32_t *)(this + 8356),  // this+8356〔uPick8356(推断)〕
            0,
            0);
          *(uint32_t *)(this + 8356) = 0;  // 字段 pHoldTarget(this+8356) 读写
        }
        v28 = *(uint32_t *)this;  // 缓存对象虚表基址
        pThis_7C = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 124))(this, 0);  // 虚槽+124 → 目标坐标y下界
        pThis_782 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);  // 虚槽+120 → 转发(对象+缓冲)
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(v28 + 136))(this, pThis_782) == 0 )  // 虚槽+136 → 目标挂接
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 112))(  // 调用
            this,
            *(uint32_t *)(this + 8364),  // this+8364〔pFrameObject(推断)〕
            *(uint32_t *)(this + 8368),  // this+8368〔nCoordB〕
            0);
      }
      break;  // 跳出本 switch(单 case 处理完)
    // ── [段 7] 大状态 case 22：FT_ONEINCH 收招 —— 回挂 +8412 动画 + 遍历 +8420/+8424 数组调各件 vt+260 ──
    //   尾部 j__free(+8420) 释放数组并三槽清零（+8420/+8424/+8428）
    case 22:  // case 22 = ENUM_CMDPACKET_BUY_ITEM
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8412));  // 虚槽+208 → 动画件回挂
      for ( k = *(uint32_t **)(this + 8420); k != *(uint32_t **)(this + 8424); k += 2 )  // 循环遍历
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*k + 260))(*k, 0, 0, 0);  // 调用
      if ( *(uint32_t *)(this + 8420) != 0 )  // 字段 pVecBegin(this+8420) 判定
        j__free(*(void **)(this + 8420));  // 释放临时缓冲
      *(uint32_t *)(this + 8420) = 0;  // 字段 pVecBegin(this+8420) 读写
      *(uint32_t *)(this + 8424) = 0;  // 字段 pVecEnd(this+8424) 读写
      *(uint32_t *)(this + 8428) = 0;  // 字段 pVecCap(this+8428) 读写
      break;  // 跳出本 switch(单 case 处理完)
    // ── [段 8] 大状态 case 24：vt+604(1) 收招；+8472==1 时调 sub_5E6640（24 态收束例程）──
    case 24:  // case 24 = ENUM_CMDPACKET_EXTEND_AVATAR
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 604))(this, 1);  // 虚槽+604 → 收招例程
      if ( *(uint32_t *)(this + 8472) == 1 )  // 字段 nFinishFlag(this+8472) 判定
        sub_5E6640(this);  // 调 收尾 → +8476 置位
      break;  // 跳出本 switch(单 case 处理完)
    // ── [段 9] 大状态 case 26：肩撞/冲撞态 —— +8496 分 0 / 1 两支 ──
    //   1 时回挂 +8512 动画；+8500 >= dword_9B9348 时跳 LABEL_62（vt+284(vt+612) 收束）；
    //   +8496==0 时走 sub_4BA730(2,4,0,0) 魔能充能 + vt+252 双槽复位 + vt+216(13)
    case 26:  // case 26 = ENUM_CMDPACKET_REPAIR_EQUIPMENT
      nChargeState = *(uint32_t *)(this + 8496);  // 字段 nChargeState(this+8496) 读写
      if ( nChargeState != 0 )  // 子型 fld_2130 非 0 判定
      {
        if ( nChargeState == 1 )  // fld_2130 == 1 判定
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8512));  // 虚槽+208 → 动画件回挂
          if ( *(uint32_t *)(this + 8500) >= dword_9B9348 )  // 字段 nChargeTime(this+8500) 判定
          {
LABEL_62:
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 284))(this, 0, 0, 1, 2);  // 虚槽+284 → 物件消耗/销毁
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);  // 虚槽+612 → 拆分/脱离
          }
        }
      }
      else
      {
        sub_4BA730((uint32_t *)this, 2, 4, 0, 0);  // sub_4BA730 · 魔能充能驱动
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, -1);  // 虚槽+252 → 缓存写入
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 252))(this, 1, -1);  // 虚槽+252 → 缓存写入
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 13);  // 虚槽+216 → 全场广播
      }
      break;  // 跳出本 switch(单 case 处理完)
    default:
      break;  // 跳出本 switch(单 case 处理完)
  }
  // ── [段 10] 状态 6/21 归一：nArg22 = nArg2；状态 25 连带改写 nArg2=8 / fld_199C=25（别名折叠）──
  //   状态 6/21 时若 nArg2 非 21/6 且 +8444>0：vt+308 判活后 vt+1140(17) 取参 + vt+1296 赋值，并清 +8444
  if ( nBigState == 21 || nBigState == 6 )  // 子型 fld_199C ∈ {21,6} 判定
  {
    nArg22 = nArg2;
    if ( nArg2 != 21 && nArg2 != 6 && *(int *)(this + 8444) > 0 )  // 字段 nSkillGate(this+8444) 判定
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚槽+308 → 是否本地玩家
      {
        v34 = *(uint32_t *)this;  // 缓存对象虚表基址
        pThis_474 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 17);  // 虚槽+1140 → 读技能表
        (*(void (/*thiscall*/ **)(int, int, int))(v34 + 1296))(this, 17, pThis_474);  // 虚槽+1296 → vt+1296
        nArg22 = nArg2;
      }
      *(uint32_t *)(this + 8444) = 0;  // 字段 nSkillGate(this+8444) 读写
    }
  }
  else
  {
    nArg22 = nArg2;
  }
  if ( nArg22 == 25 )  // nArg22 == 25 判定
  {
    nArg22 = 8;
    nArg2 = 8;
    nBigState = 25;
  }
  // ── [段 11] 第二重 switch(nArg22)：★ 技能演出主表（15/16/17/18/40 及 42 兜底）──
  switch ( nArg22 )  // 按 nArg22 分派
  {
    // ── [段 12] case 15：FT_SIT（坐下）—— vt+196 应用技能参 + vt+888 帧长标定 + vt+876 双段位移 ──
    //   位移量取 this+112 宿主组件 +16 的浮点绝对值（fld_70）；vt+896 挂帧后播音效 FT_SIT
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 6216));  // 虚槽+196 → 物件非空判定
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);  // 虚槽+888 → 帧长标定
      pHostComp = (uint64_t)fabs(*(float *)(*(uint32_t *)(this + 112) + 16));  // 字段 pHostComp(this+112) 读写
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 2);  // 虚槽+1160 → 读技能表(变体)
      *(float *)&pThis_4742 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 2));  // 虚槽+1140 → 读技能表
      v37 = 0;
      if ( pHostComp != 0 )  // 子型 fld_70 非 0 判定
        v37 = sub_47EF20(1, pThis_4742, -1, -1, 11);  // 调 读攻击数据表
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 调用
        this,
        0,
        pHostComp,
        pHostComp,
        0,
        v37,
        1);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      v38 = *(uint32_t *)this;  // 缓存对象虚表基址
      pThis_98 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);  // 虚槽+152 → 取值(参数)
      (*(void (/*thiscall*/ **)(int, int))(v38 + 896))(this, pThis_98);  // 虚槽+896
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚槽+308 → 是否本地玩家
        *(uint32_t *)(this + 8232) = sub_47EF20(0, pThis_4742, -1, -1, 11);  // sub_47EF20
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "FT_SIT", -1, 0, 0);  // 虚槽+212 → vt+212
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 13] case 16：腿法三态 —— 按 +8240 参数选 BONECRUSHER(4) / LOWKICK(6) ──
    //   v41 = vt+1140(+8240) 技能参数；fld_2030 = vt+1160(+8240) 参数字符串；
    //   4 → 应用 +6216+4 参 + vt+344(+556) 动画基 + sub_47EF20 读表写 +424(×0.1)/+436 + G_BONECRUSHER 音效；
    //   6 → +6216+12 参 + vt+344(+556+304) + G_LOWKICK；两路共用 R_FT_KICK_LOW 与 sub_47EFD0 伤害换算
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      v40 = *(uint32_t *)this;  // 缓存对象虚表基址
      v259 = *pArg3[1];
      *(uint32_t *)(this + 8240) = v259;  // 字段 nParamCnt(this+8240) 读写
      v41 = (*(int (/*thiscall*/ **)(int, int))(v40 + 1140))(this, v259);  // 虚槽+1140 → 读技能表
      fld_2030 = (char *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1160))(this, *(uint32_t *)(this + 8240));  // 虚槽+1160 → 读技能表(变体)
      nParamCnt = *(uint32_t *)(this + 8240);  // 字段 nParamCnt(this+8240) 读写
      if ( nParamCnt == 4 )  // fld_20302 == 4 判定
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));  // 虚槽+196 → 物件非空判定
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556));  // 虚槽+344 → 动画件访问(基偏移)
        v44 = (void *)sub_47EF20(2, v41, -1, -1, 11);  // v44 = sub_47EF20
        v265 = 11;
        Block = v44;
        *(float *)(this + 424) = (double)(int)v44 * 0.1;  // 写内存
        v45 = sub_47EF20(3, v41, -1, -1, v265);  // 调 读攻击数据表
        *(float *)&v265 = 0.0;  // 写内存
        *(uint32_t *)(this + 436) = v45;  // 字段 nAtkTableVal(this+436) 读写
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)this + 212))(  // 调用
          this,
          "G_BONECRUSHER",  // 标签 G_BONECRUSHER
          -1,
          0,
          v265);
      }
      else if ( nParamCnt == 6 )  // 子型 fld_20302=6
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 12));  // 虚槽+196 → 物件非空判定
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 304);  // 虚槽+344 → 动画件访问(基偏移)
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
          this,
          "G_LOWKICK",  // 标签 G_LOWKICK
          -1,
          0,
          0);
      }
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
        this,
        "R_FT_KICK_LOW",  // 标签 R_FT_KICK_LOW
        -1,
        0,
        0);
      pThis_184 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(fld_2030, COERCE_FLOAT(1), v41, pThis_184, pThis_184, 0));  // sub_47EFD0
      *(float *)(this + 388) = (float)(int)Block;  // 写内存
      *(float *)&Block = COERCE_FLOAT(sub_47EF20(0, v41, -1, -1, 11));  // sub_47EF20
      v47 = 0;
      v48 = 0;
      *(float *)&pThis_4742 = (double)(int)Block * 0.0099999998 + 1.0;  // 写内存
      if ( nBigState == 8 )  // fld_199C == 8 判定
      {
        v47 = 600;
        v48 = -10000;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 调用
        this,
        0,
        v47,
        v47,
        0,
        v48,
        1);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      *(float *)&Block = COERCE_FLOAT((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 900))(this, 3));  // 虚槽+900
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 888))(  // 调用
        this,
        0,
        0,
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742),
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742));
      v49 = *(uint32_t *)this;  // 缓存对象虚表基址
      pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);  // 虚槽+152 → 取值(参数)
      (*(void (/*thiscall*/ **)(int, int))(v49 + 896))(this, pThis_982);  // 虚槽+896
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 14] case 17：三型技能主表 —— 按 +8244(+8248) 走 +8248 switch（8/15/40/default 42）──
    //   +8244 为抓取/分型选择；+8244==0 时自 pArg3[1][1..7] 灌入 +8248..+8264 参数槽（含 sub_41C5A0 参数个数判据）
    case 17:  // case 17 = ENUM_CMDPACKET_SELECT_DUNGEON
      v51 = *pArg3[1];
      pThis_4742 = 1000;
      *(uint32_t *)(this + 8244) = v51;  // 字段 nVariantSel(this+8244) 读写
      if ( v51 != 0 )  // v51 != 0 判定
      {
        nPhaseA = *(uint32_t *)(this + 8260);  // 字段 nPhaseA(this+8260) 读写
        nPhaseB = *(uint32_t *)(this + 8264);  // 字段 nPhaseB(this+8264) 读写
      }
      else
      {
        *(uint32_t *)(this + 8248) = pArg3[1][1];  // 字段 nVariantVal(this+8248) 读写
        *(uint32_t *)(this + 8252) = pArg3[1][2];  // 字段 nParam2(this+8252) 读写
        *(uint32_t *)(this + 8256) = pArg3[1][3];  // 字段 nParam3(this+8256) 读写
        v52 = pArg3[1];
        nPhaseA = v52[4];
        *(uint32_t *)(this + 8260) = v52[5];  // 字段 nPhaseA(this+8260) 读写
        if ( (unsigned int)sub_41C5A0(pArg3) > 6 )  // sub_41C5A0 · vector<T 4B> 大小查询
          pThis_4742 = pArg3[1][6];
        if ( (unsigned int)sub_41C5A0(pArg3) <= 7 )  // sub_41C5A0 · vector<T 4B> 大小查询
        {
          nPhaseB = pThis_4742;
          *(uint32_t *)(this + 8264) = 1000;  // 字段 nPhaseB(this+8264) 读写
        }
        else
        {
          nPhaseB = pThis_4742;
          *(uint32_t *)(this + 8264) = pArg3[1][7];  // 字段 nPhaseB(this+8264) 读写
        }
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 16));  // 虚槽+196 → 物件非空判定
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, nPhaseA, nPhaseA, nPhaseB, nPhaseB);  // 虚槽+888 → 帧长标定
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚槽+896
      *(uint32_t *)(this + 4 * *(uint32_t *)(this + 8244) + 8252) = 1000  // 字段 nVariantSel(this+8244) 读写
                                                              * *(uint32_t *)(this + 4 * *(uint32_t *)(this + 8244) + 8252)  // 字段 nVariantSel(this+8244) 读写
                                                              / *(uint32_t *)(this + 6656);  // 字段 nRateDen(this+6656) 读写
      if ( *(uint32_t *)(this + 8244) == 0 && nPhaseA == 4 )  // 字段 nVariantSel(this+8244) 判定
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 992))(this, *(uint32_t *)(this + 8252), 0);  // 虚槽+992
      if ( *(uint32_t *)(this + 8244) == 1 )  // 字段 nVariantSel(this+8244) 判定
      {
        nVariantVal = *(uint32_t *)(this + 8248);  // 字段 nVariantVal(this+8248) 读写
        switch ( nVariantVal )  // 按 fld_2038 分派
        {
          // ── [段 15] case 17 子表 case 8：★ FT_KENSIN（剑心/连打）—— 环状批量生成 60001 号伤害区 ──
          //   仅本机（vt+308）执行；循环 v56 次按 sub_405400 余弦 / sub_4053E0 正弦算 XY 坐标，
          //   半径 75，圆心 60001（dword_7930D4 为圆周缩放），落点经 vt+152/vt+128/vt+388/vt+376 转世界后 vt+592 提交
          case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚槽+308 → 是否本地玩家
            {
              pThis_4743 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 1140))(this, 8, -1);  // 虚槽+1140 → 读技能表
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);  // 虚槽+1160 → 读技能表(变体)
              v56 = (void *)sub_47EF20(8, 0, pThis_4743, -1, 11);  // v56 = sub_47EF20
              pThis_4742 = (int)v56;  // pThis_4742 = 取 v56(转指针/类型)
              if ( (int)v56 > 0 )  // > 范围判定
              {
                pThis_784 = 0;
                Block = v56;
                do
                {
                  v57 = pThis_784 / pThis_4742;
                  v58 = (uint64_t)(sub_405400(pThis_784 / pThis_4742) * 75.0);  // v58 = sub_405400 · cos 查表
                  HIDWORD(v58) = *(uint32_t *)this;  // 拼装 64 位 v58(HIDWORD) = *(uint32_t *)this
                  v59 = v58;
                  v277 = v58;
                  if ( (*(int (/*thiscall*/ **)(int))(HIDWORD(v58) + 152))(this) == 0 )  // 虚槽+152 → 取值(参数)
                    v277 = -v59;
                  pThis_783 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);  // 虚槽+120 → 转发(对象+缓冲)
                  v277 += pThis_783;  // v277 累加 pThis_783
                  v61 = (int)(dword_7930D4[0] * (uint64_t)(sub_4053E0(v57) * 75.0)) / 100;  // v61 = sub_4053E0 · sin 查表
                  pThis_7C2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this);  // 虚槽+124 → 目标坐标y下界
                  v63 = *(uint32_t *)this;  // 缓存对象虚表基址
                  v64 = pThis_7C2 + v61;
                  pThis_983 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(  // pThis_983 = 虚调用取值
                          this,
                          0,
                          0,
                          0,
                          0xFFFF,
                          0,
                          0,
                          0,
                          0);
                  pThis_80 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 128))(this, pThis_983);  // 虚槽+128 → 目标坐标y上界
                  pThis_1842 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)this + 388))(this, v277, v64, pThis_80);  // 虚槽+388 → 攻击计算
                  pThis_178 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 376))(this, pThis_1842);  // 虚槽+376
                  (*(void (/*thiscall*/ **)(int, int, int))(v63 + 592))(this, 60001, pThis_178);  // 虚槽+592
                  v69 = Block == (void *)1;
                  pThis_784 += 360;  // pThis_784 累加 360
                  Block = (char *)Block - 1;
                }
                while ( !v69 );
              }
            }
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
              this,
              "FT_KENSIN",  // 标签 FT_KENSIN
              -1,
              0,
              0);
            break;  // 跳出本 switch(单 case 处理完)
          // ── [段 16] case 17 子表 case 15：★ 咆哮（RoarStun1/2.ani 双件 + SAJAHU 系）──
          //   sub_42FCB0(228) 门控；+8268/+8272 缓存两枚动画（+384<0x10 用 this+108 内联缓冲，否则 this+364 堆指针）；
          //   vt+204(1, anim, 0, -65, 1, 0) 双次挂载；本机时 vt+1140(15,...,4) + vt+580(21005) 提交；
          //   尾部播 FT_SAJAHU_CAST + SAJAHU_SPREAD 并清 +8276
          case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
            if ( *(uint32_t *)(this + 8268) == 0 )  // 字段 nParamArr(this+8268) 判定
            {
              *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
              v280 = 2;
              if ( *(float *)&Block == 0.0 )  // 浮点 Block 为 0 判定(未取到参)
              {
                pThis_6C = 0;
              }
              else if ( *(uint32_t *)(this + 384) < 0x10u )  // 字段 nAnimPoolCap(this+384) 读写
              {
                pThis_6C = sub_431920(this + 108, (char)"Effect/Animation/RoarStun1.ani", 1);  // pThis_6C = sub_431920 · 动画件构造
              }
              else
              {
                pThis_6C = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/RoarStun1.ani", 1);  // pThis_6C = sub_431920 · 动画件构造
              }
              v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
              *(uint32_t *)(this + 8268) = pThis_6C;  // 字段 nParamArr(this+8268) 读写
              *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
              v280 = 3;
              if ( *(float *)&Block == 0.0 )  // 浮点 Block 为 0 判定(未取到参)
              {
                pThis_6C2 = 0;
              }
              else if ( *(uint32_t *)(this + 384) < 0x10u )  // 字段 nAnimPoolCap(this+384) 读写
              {
                pThis_6C2 = sub_431920(this + 108, (char)"Effect/Animation/RoarStun2.ani", 1);  // pThis_6C2 = sub_431920 · 动画件构造
              }
              else
              {
                pThis_6C2 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/RoarStun2.ani", 1);  // pThis_6C2 = sub_431920 · 动画件构造
              }
              v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
              *(uint32_t *)(this + 8272) = pThis_6C2;  // 字段 pAnimPool2(this+8272) 读写
            }
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, uint32_t))(*(uint32_t *)this + 204))(  // 调用
              this,
              1,
              *(uint32_t *)(this + 8268),  // this+8268〔nParamArr(推断)〕
              0,
              -65,
              1,
              0);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, uint32_t))(*(uint32_t *)this + 204))(  // 调用
              this,
              1,
              *(uint32_t *)(this + 8272),  // this+8272〔pAnimPool2〕
              0,
              -65,
              1,
              0);
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚槽+308 → 是否本地玩家
            {
              v72 = *(uint32_t *)this;  // 缓存对象虚表基址
              pThis_4744 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(  // pThis_4744 = 虚调用取值
                      this,
                      15,
                      0,
                      0,
                      0,
                      0,
                      0,
                      4,
                      0,
                      0,
                      0);
              (*(void (/*thiscall*/ **)(int, int, int))(v72 + 580))(this, 21005, pThis_4744);  // 虚槽+580 → 音效/技能播放(12参)
            }
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
              this,
              "FT_SAJAHU_CAST",  // 标签 FT_SAJAHU_CAST
              -1,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
              this,
              "SAJAHU_SPREAD",  // 标签 SAJAHU_SPREAD
              -1,
              0,
              0);
            *(uint8_t *)(this + 8276) = 0;  // 字节字段 f_2054(this+8276) 判定
            break;  // 跳出本 switch(单 case 处理完)
          // ── [段 17] case 17 子表 case 40：★ 螺旋念气（Particle/SpiralNen.ptl + BUFF_SPIRAL_NEN）──
          //   +8280 惰性创建粒子对象（vt+588 加载 ptl），其 +85 槽写 sub_47EF20(1,...) 读表值；
          //   vt+580(21007, 动画, 粒子, ..., 50, 1, this) 提交；尾部双音效 FT_SPIRAL_NEN / BUFF_SPIRAL_NEN
          case 40:  // case 40 = ENUM_CMDPACKET_FISHING
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚槽+308 → 是否本地玩家
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 40);  // 虚槽+1160 → 读技能表(变体)
              pThis_4745 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 40);  // 虚槽+1140 → 读技能表
              if ( *(uint32_t *)(this + 8280) == 0 )  // 字段 pStatusObj(this+8280) 判定
                *(uint32_t *)(this + 8280) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(  // 字段 pStatusObj(this+8280) 读写
                                             this,
                                             "Particle/SpiralNen.ptl");  // 粒子 .ptl Particle/SpiralNen.ptl
              *(uint32_t *)(*(uint32_t *)(this + 8280) + 85) = sub_47EF20(1, pThis_4745, -1, -1, 11);  // sub_47EF20
              (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 580))(  // 调用
                this,
                21007,
                pThis_4745,
                *(uint32_t *)(this + 8280),  // this+8280〔pStatusObj〕
                0,
                0,
                0,
                50,
                1,
                this,
                0,
                0);
            }
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
              this,
              "FT_SPIRAL_NEN",  // 标签 FT_SPIRAL_NEN
              -1,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
              this,
              "BUFF_SPIRAL_NEN",  // 标签 BUFF_SPIRAL_NEN
              -1,
              0,
              0);
            break;  // 跳出本 switch(单 case 处理完)
          // ── [段 18] case 17 子表 default：仅 +8248==42 时处理（vt+1140(42,...,4) → vt+580(21010)）──
          default:
            if ( nVariantVal == 42 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚槽+308 → 是否本地玩家
            {
              v75 = *(uint32_t *)this;  // 缓存对象虚表基址
              pThis_4746 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(  // pThis_4746 = 虚调用取值
                      this,
                      42,
                      0,
                      0,
                      0,
                      0,
                      0,
                      4,
                      0,
                      0,
                      0);
              (*(void (/*thiscall*/ **)(int, int, int))(v75 + 580))(this, 21010, pThis_4746);  // 虚槽+580 → 音效/技能播放(12参)
            }
            break;  // 跳出本 switch(单 case 处理完)
        }
      }
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 19] case 18：★ FT_HOLD（抓取维持）—— 按 +8284 技能号取动画与参 ──
    //   9/18 → sub_47E9D0(v78,0)；49 → sub_47E9D0(v78,7)（v78 = vt+1160(+8284) 参数）；
    //   LABEL_137：9/49 取 +6216+20 参，18 取 +6216+48 参 → vt+196 应用；
    //   fld_199C==11 且 vt+1140(51) 有值时按 fld_2060 比例算位移（-500*|速度|/帧长）写 +8296；
    //   尾部 vt+344(+556+456) 动画基 + 音效 FT_HOLD + +8468 技能对象门控写 +8292 与 +464
    case 18:  // case 18 = ENUM_CMDPACKET_SEND_MESSAGE
      v77 = *(uint32_t *)this;  // 缓存对象虚表基址
      v260 = *pArg3[1];
      *(uint32_t *)(this + 8284) = v260;  // 字段 nGrabSkillNo(this+8284) 读写
      v78 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(v77 + 1160))(this, v260);  // 虚槽+1160 → 读技能表(变体)
      nGrabSkillNo = *(uint32_t *)(this + 8284);  // 字段 nGrabSkillNo(this+8284) 读写
      if ( nGrabSkillNo == 9 || nGrabSkillNo == 18 )  // 子型 fld_205C ∈ {9,18} 判定
      {
        v80 = sub_47E9D0(v78, 0);  // 调 收招/结束例程
      }
      else
      {
        if ( nGrabSkillNo != 49 )  // 子型 fld_205C 非 49 判定
          goto LABEL_137;  // 跳转 LABEL_137(收尾/共用分支)
        v80 = sub_47E9D0(v78, 7u);  // 调 收招/结束例程
      }
      *(uint32_t *)(this + 8288) = v80;  // 字段 nGrabDataVal(this+8288) 读写
LABEL_137:
      nGrabSkillNo_ = *(uint32_t *)(this + 8284);  // 字段 nGrabSkillNo(this+8284) 读写
      // ── [段 20] case 18 之 LABEL_137/143 两段参应用：9/49 取 +6216+20，18 取 +6216+48 ──
      if ( nGrabSkillNo_ == 9 || nGrabSkillNo_ == 49 )  // 子型 fld_205C2 ∈ {9,49} 判定
      {
        pSubCtx = *(uint32_t *)(*(uint32_t *)(this + 6216) + 20);  // 字段 pSubCtx(this+6216) 读写
      }
      else
      {
        if ( nGrabSkillNo_ != 18 )  // 子型 fld_205C2 非 18 判定
          goto LABEL_143;  // 跳转 LABEL_143(收尾/共用分支)
        pSubCtx = *(uint32_t *)(*(uint32_t *)(this + 6216) + 48);  // 字段 pSubCtx(this+6216) 读写
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 196))(this, pSubCtx);  // 虚槽+196 → 物件非空判定
LABEL_143:
      if ( nBigState == 11 && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 51) > 0 )  // 虚槽+1140 → 读技能表
      {
        pThis_4747 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 1140))(this, 51, -1, -1, 11);  // 虚槽+1140 → 读技能表
        (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)this + 1160))(this, 51, 0, pThis_4747);  // 虚槽+1160 → 读技能表(变体)
        nGrabDataVal = sub_47EF20(v262, v263, v264, v265, LODWORD(v266)) + *(uint32_t *)(this + 8288);  // 调 读攻击数据表
        pHostComp_ = *(uint32_t *)(this + 112);  // 字段 pHostComp(this+112) 读写
        *(uint32_t *)(this + 8288) = nGrabDataVal;  // 字段 nGrabDataVal(this+8288) 读写
        v86 = (uint64_t)fabs(*(float *)(pHostComp_ + 16));
        HIDWORD(v86) = *(uint32_t *)this;  // 拼装 64 位 v86(HIDWORD) = *(uint32_t *)this
        LODWORD(v266) = 1;  // 拼装 64 位 v266(LODWORD) = 1
        v265 = -500 * (int)v86 / nGrabDataVal;
        (*(void (/*thiscall*/ **)(int, uint32_t))(HIDWORD(v86) + 876))(this, 0);  // 虚槽+876 → 双段位移
        *(uint32_t *)(this + 8296) = -250;  // 字段 nOffsetVal(this+8296) 读写
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
          this,
          0,
          0,
          0,
          0,
          0,
          0);
      }
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 3, 1000, 1000);  // 虚槽+888 → 帧长标定
      v87 = *(uint32_t *)this;  // 缓存对象虚表基址
      pThis_984 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);  // 虚槽+152 → 取值(参数)
      (*(void (/*thiscall*/ **)(int, int))(v87 + 896))(this, pThis_984);  // 虚槽+896
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 456);  // 虚槽+344 → 动画件访问(基偏移)
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
        this,
        "FT_HOLD",  // 标签 FT_HOLD
        -1,
        0,
        0);
      pSkillObj = *(uint32_t *)(this + 8468);  // 字段 pSkillObj(this+8468) 读写
      v90 = pSkillObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pSkillObj + 80))(pSkillObj) != 0;  // 虚槽+80 → 读 4 字节
      // ── [段 21] case 18 收尾：+8468 技能对象门控写 +8292 抓取标志，成立时 +464=-998637568（-1000.0f）──
      *(uint8_t *)(this + 8292) = v90;  // 字节字段 bModeFlag(this+8292) 判定
      if ( v90 )  // v90 为真则进入
        *(uint32_t *)(this + 464) = -998637568;  // 字段 f_01D0(this+464) 读写
// ── [段 22] ★ LABEL_251 公共尾 + 第三重 switch(nArg2)：动作事件号分派（6/7/8/10/12/14/19..26）──
//   sub_4B89D0(nArg2, pArg3, fNArg4, fNArg5) 先做参数登记；本表与上面「技能分型」正交
LABEL_251:
      sub_4B89D0(nArg2, pArg3, *(float *)&nArg4, *(float *)&nArg5);  // sub_4B89D0 · 跑步地面循环 + 蓄气/霸体特效
      result = nArg2 - 6;
      switch ( nArg2 )  // 按 nArg2 分派
      {
        // ── [段 23] 第三重 case 6：★ 起跳/上勾预备 —— +6892 取参，vt+1140(17) 读表写 +8444/+8448 ──
        case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
          result = *(uint32_t *)(this + 6892);  // 字段 nSkillCtxVal(this+6892) 读写
          if ( result == 0 )  // 结果==0 分支
          {
            result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 17);  // 虚槽+1140 → 读技能表
            if ( result > 0 )  // 数量>0 判定
            {
              v235 = *(uint32_t *)this;  // 缓存对象虚表基址
              *(uint32_t *)(this + 8444) = 0;  // 字段 nSkillGate(this+8444) 读写
              v257 = (*(int (/*thiscall*/ **)(int, int, int))(v235 + 1140))(this, 17, -1);  // 虚槽+1140 → 读技能表
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1160))(this);  // 虚槽+1160 → 读技能表(变体)
              result = sub_47EF20(17, 1, v257, -1, 11);  // 调 读攻击数据表
              *(uint32_t *)(this + 8448) = result;  // 字段 nFinishVal(this+8448) 读写
            }
          }
          return result;
        // ── [段 24] 第三重 case 7：JUMP_KICK / R_FT_KICK_JUMP（跳跃踢双音效后 return）──
        case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
            this,
            "JUMP_KICK",  // 标签 JUMP_KICK
            -1,
            0,
            0);
          return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                   this,
                   "R_FT_KICK_JUMP",  // 标签 R_FT_KICK_JUMP
                   -1,
                   0,
                   0);
        // ── [段 25] 第三重 case 8：★ 普攻 —— 按 +8216 分型（46 = FT_HAMMER_KICK / 斧踢系）──
        //   +8216 为 vt+1172 取来的动作类型；46 时 vt+344(+556+1520) + sub_47EFD0 伤害 + FT_HAMMER_KICK；
        //   sub_41A5E0(this+7028) 取普攻分型 0/1/2/3 决定 R_FT_ATK / R_FT_KICK_AX+KICK_AX 组合
        case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
          if ( nBigState != 8 )  // 子型 fld_199C 非 8 判定
          {
            v213 = pArg3[1];
            if ( v213 != nullptr && (unsigned int)(pArg3[2] - v213) > 1 )  // v213 非空 且 (unsigned int)(pArg3[2] - v213) > 1
              v214 = v213[1];
            else
              v214 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            *(uint32_t *)(this + 8216) = v214;  // 字段 nAtkActionType(this+8216) 读写
          }
          if ( *(uint32_t *)(this + 8216) != -1 )  // 字段 nAtkActionType(this+8216) 判定
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1328))(this, 0);  // 虚槽+1328 → vt+1328
          if ( *(uint32_t *)(this + 8216) == 46 )  // 字段 nAtkActionType(this+8216) 判定
          {
            pThis_4882 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 46);  // 虚槽+1160 → 读技能表(变体)
            pThis_4748 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 46);  // 虚槽+1140 → 读技能表
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1520);  // 虚槽+344 → 动画件访问(基偏移)
            pThis_1843 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
            *(float *)(this + 388) = (float)sub_47EFD0(pThis_4882, COERCE_FLOAT(2), pThis_4748, pThis_1843, pThis_1843, 0);  // sub_47EFD0
            *(uint32_t *)(this + 452) = sub_47EF20(0, pThis_4748, -1, -1, 11);  // sub_47EF20
            v218 = sub_47EF20(1, pThis_4748, -1, -1, 11);  // 调 读攻击数据表
            v219 = *(uint32_t *)this;  // 缓存对象虚表基址
            *(uint32_t *)(this + 456) = v218;  // 字段 f_01C8(this+456) 读写
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v219 + 212))(  // 调用
              this,
              "FT_HAMMER_KICK",  // 标签 FT_HAMMER_KICK
              -1,
              0,
              0);
          }
          if ( sub_41A5E0(this + 7028) != 0 )  // sub_41A5E0 · crypt4byte 解密校验
          {
            if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 )  // sub_41A5E0 · crypt4byte 解密校验
            {
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
                this,
                "R_FT_ATK",  // 标签 R_FT_ATK
                -1,
                0,
                0);
              v223 = *(uint32_t *)this;  // 缓存对象虚表基址
              pThis_494 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);  // 虚槽+1172 → 技能名/ID换算
              (*(void (/*thiscall*/ **)(int, int))(v223 + 212))(this, pThis_494);  // 虚槽+212 → vt+212
              pThis_4942 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);  // 虚槽+1172 → 技能名/ID换算
              return sub_406D60(pThis_4942);  // sub_406D60 · std::string 从 C 串赋值
            }
            else
            {
              result = sub_41A5E0(this + 7028);  // result = sub_41A5E0 · crypt4byte 解密校验
              if ( result == 3 && *(uint32_t *)(this + 8216) != 46 )  // 字段 nAtkActionType(this+8216) 读写
              {
                (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
                  this,
                  "R_FT_KICK_AX",  // 标签 R_FT_KICK_AX
                  -1,
                  0,
                  0);
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                         this,
                         "KICK_AX",  // 标签 KICK_AX
                         -1,
                         0,
                         0);
              }
            }
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
              this,
              "R_FT_ATK",  // 标签 R_FT_ATK
              -1,
              0,
              0);
            v220 = *(uint32_t *)this;  // 缓存对象虚表基址
            pThis_4943 = (*(int (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);  // 虚槽+1172 → 技能名/ID换算
            (*(void (/*thiscall*/ **)(int, int))(v220 + 212))(this, pThis_4943);  // 虚槽+212 → vt+212
            pThis_4944 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 2);  // 虚槽+1172 → 技能名/ID换算
            return sub_406D60(pThis_4944);  // sub_406D60 · std::string 从 C 串赋值
          }
          return result;
        // ── [段 26] 第三重 case 10：★ 魔能充能组（EnergyCharge.ani + HELLTER/NENTAN/ENERGY_SHOT）──
        //   +7812==1 时按 +8400 状态对象 vt+80 判活并标定 vt+888 帧长（2×+6652 / 2×+6656）；
        //   +7816 (12/16) 时惰性建 EnergyCharge.ani 写 +8380；16 时 vt+1160(16)+sub_47DCD0 预取参；
        //   子 switch(+7816)：13 → FT_HELLTER；12 → EnergyBallShoot.ani / Particle/EnergyBall.ptl / FT_NENTAN；
        //   16 → FT_ENERGY_SHOT（本机 vt+1140(16,...,107,1,62,4)→vt+580(21006)）或 ENERGYING+FT_ENERGYING；
        //   49 → 抓取式（RTDynamicCast 到 IRDActiveObject 存 +8300，sub_5E4FC0 建 0x68 缓冲 +988）→ FT_ROPLING；52 → 同 13
        case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
          if ( *(uint32_t *)(this + 7812) == 1 )  // 字段 nSubStateA(this+7812) 判定
          {
            if ( nBigState != 10 )  // 子型 fld_199C 非 10 判定
              *(uint32_t *)(this + 8404) = 0;  // 字段 pFxObjD(this+8404) 读写
            pAppendage = *(uint32_t *)(this + 8400);  // 字段 pAppendage(this+8400) 读写
            if ( pAppendage != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pAppendage + 80))(pAppendage) != 0 )  // 虚槽+80 → 读 4 字节
            {
              (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(  // 调用
                this,
                0,
                0,
                2 * *(uint32_t *)(this + 6652),  // this+6652〔nRateNum〕
                2 * *(uint32_t *)(this + 6656));  // this+6656〔nRateDen〕
              if ( *(uint32_t *)(this + 7808) == 0 )  // 字段 nStyleSel(this+7808) 判定
              {
                *(int *)(this + 7820) /= 2;  // 字段 nGrabW(this+7820) 判定
                *(int *)(this + 7824) /= 2;  // 字段 nGrabH(this+7824) 判定
              }
            }
          }
          result = *(uint32_t *)(this + 7812);  // 字段 nSubStateA(this+7812) 读写
          if ( result != 0 )  // 结果!=0 分支
            return result;
          nSubStateB_ = *(uint32_t *)(this + 7816);  // 字段 nSubStateB(this+7816) 读写
          if ( (nSubStateB_ == 12 || nSubStateB_ == 16) && *(uint32_t *)(this + 8380) == 0 )  // 字段 pAnimC(this+8380) 读写
          {
            v281 = (void *)sub_42FCB0(228);  // v281 = sub_42FCB0 · CRT 一次性初始化
            v280 = 10;
            if ( v281 != nullptr )  // v281 != nullptr 判定
            {
              if ( *(uint32_t *)(this + 384) < 0x10u )  // 字段 nAnimPoolCap(this+384) 判定
                pThis_6C3 = sub_431920(this + 108, (char)"Effect/Animation/EnergyCharge.ani", 1);  // pThis_6C3 = sub_431920 · 动画件构造
              else
                pThis_6C3 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/EnergyCharge.ani", 1);  // pThis_6C3 = sub_431920 · 动画件构造
            }
            else
            {
              pThis_6C3 = 0;
            }
            v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            *(uint32_t *)(this + 8380) = pThis_6C3;  // 字段 pAnimC(this+8380) 读写
          }
          // ── [段 27] case 10 之 16 号子型：vt+1160(16) + sub_47DCD0 预取参（充能射击前置）──
          if ( *(uint32_t *)(this + 7816) == 16 )  // 字段 nSubStateB(this+7816) 判定
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 16);  // 虚槽+1160 → 读技能表(变体)
            sub_47DCD0(this, -1);  // 调 震动/资源档位设置
          }
          result = *(uint32_t *)(this + 7816);  // 字段 nSubStateB(this+7816) 读写
          switch ( result )  // 按 result 分派
          {
            case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
              *(uint8_t *)(this + 8376) = 0;  // 字节字段 pFxObjB(this+8376) 判定
LABEL_303:
              if ( *(uint32_t *)(this + 7808) == 1 )  // 字段 nStyleSel(this+7808) 判定
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                         this,
                         "FT_HELLTER",  // 标签 FT_HELLTER
                         -1,
                         0,
                         0);
              return result;
            case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
              result = *(uint32_t *)(this + 7808);  // 字段 nStyleSel(this+7808) 读写
              if ( result != 0 )  // 结果!=0 分支
              {
                if ( result == 1 )  // 结果==1 分支
                {
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8380));  // 虚槽+208 → 动画件回挂
                  if ( *(uint32_t *)(this + 8388) == 0 )  // 字段 pAnimD(this+8388) 判定
                  {
                    v282 = (void *)sub_42FCB0(228);  // v282 = sub_42FCB0 · CRT 一次性初始化
                    v280 = 11;
                    if ( v282 != nullptr )  // v282 != nullptr 判定
                    {
                      if ( *(uint32_t *)(this + 384) < 0x10u )  // 字段 nAnimPoolCap(this+384) 判定
                        pThis_6C4 = sub_431920(this + 108, (char)"Effect/Animation/EnergyBallShoot.ani", 1);  // pThis_6C4 = sub_431920 · 动画件构造
                      else
                        pThis_6C4 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/EnergyBallShoot.ani", 1);  // pThis_6C4 = sub_431920 · 动画件构造
                    }
                    else
                    {
                      pThis_6C4 = 0;
                    }
                    v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
                    *(uint32_t *)(this + 8388) = pThis_6C4;  // 字段 pAnimD(this+8388) 读写
                  }
                  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调用
                    this,
                    1,
                    *(uint32_t *)(this + 8388),  // this+8388〔pAnimD〕
                    0,
                    0,
                    0,
                    0);
                  (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 调用
                    this,
                    0,
                    200,
                    200,
                    0,
                    -10000,
                    1);
                  v240 = *(uint32_t *)this;  // 缓存对象虚表基址
                  pThis_985 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);  // 虚槽+152 → 取值(参数)
                  result = (*(int (/*thiscall*/ **)(int, int))(v240 + 896))(this, pThis_985);  // 虚槽+896
                  *(uint8_t *)(this + 8392) = 0;  // 字节字段 f_20C8(this+8392) 判定
                }
              }
              else
              {
                (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调用
                  this,
                  1,
                  *(uint32_t *)(this + 8380),  // this+8380〔pAnimC〕
                  0,
                  0,
                  0,
                  0);
                *(uint32_t *)(this + 8396) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(  // 字段 nNameLookup(this+8396) 读写
                                             this,
                                             "Particle/EnergyBall.ptl");  // 粒子 .ptl Particle/EnergyBall.ptl
                *(uint8_t *)(this + 8384) = 0;  // 字节字段 f_20C0(this+8384) 判定
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                         this,
                         "FT_NENTAN",  // 标签 FT_NENTAN
                         -1,
                         0,
                         0);
              }
              break;  // 跳出本 switch(单 case 处理完)
            case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
              result = *(uint32_t *)(this + 7808);  // 字段 nStyleSel(this+7808) 读写
              if ( result != 0 )  // 结果!=0 分支
              {
                if ( result == 1 )  // 结果==1 分支
                {
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(this + 8380));  // 虚槽+208 → 动画件回挂
                  (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(  // 调用
                    this,
                    0,
                    200,
                    200,
                    0,
                    -10000,
                    1);
                  v243 = *(uint32_t *)this;  // 缓存对象虚表基址
                  pThis_986 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);  // 虚槽+152 → 取值(参数)
                  (*(void (/*thiscall*/ **)(int, int))(v243 + 896))(this, pThis_986);  // 虚槽+896
                  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚槽+308 → 是否本地玩家
                  {
                    v245 = *(uint32_t *)this;  // 缓存对象虚表基址
                    pThis_4749 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 1140))(  // pThis_4749 = 虚调用取值
                             this,
                             16,
                             0,
                             0,
                             107,
                             1,
                             62,
                             4,
                             0,
                             0,
                             0);
                    (*(void (/*thiscall*/ **)(int, int, int))(v245 + 580))(this, 21006, pThis_4749);  // 虚槽+580 → 音效/技能播放(12参)
                  }
                  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                           this,
                           "FT_ENERGY_SHOT",  // 标签 FT_ENERGY_SHOT
                           -1,
                           0,
                           0);
                }
              }
              else
              {
                (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调用
                  this,
                  1,
                  *(uint32_t *)(this + 8380),  // this+8380〔pAnimC〕
                  0,
                  0,
                  0,
                  0);
                v242 = *(uint32_t *)this;  // 缓存对象虚表基址
                *(uint8_t *)(this + 8384) = 0;  // 字节字段 f_20C0(this+8384) 判定
                (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v242 + 212))(  // 调用
                  this,
                  "ENERGYING",  // 标签 ENERGYING
                  -1,
                  0,
                  0);
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                         this,
                         "FT_ENERGYING",  // 标签 FT_ENERGYING
                         -1,
                         0,
                         0);
              }
              break;  // 跳出本 switch(单 case 处理完)
            case 49:  // case 49 = ENUM_CMDPACKET_MOVE_MAP
              result = *(uint32_t *)(this + 7808);  // 字段 nStyleSel(this+7808) 读写
              if ( result != 0 )  // 结果!=0 分支
              {
                if ( result == 1 )  // 结果==1 分支
                {
                  result = (int)pArg3[1];
                  v254 = *(uint32_t *)(result + 4);  // 字段 +4(result+4) 读写
                  if ( v254 != 4 )  // v254 != 4 判定
                    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 148))(this, v254);  // 虚槽+148 → 位置/朝向写入
                }
              }
              else
              {
                v247 = sub_45EBE0(pArg3[1][10], pArg3[1][11]);  // v247 = sub_45EBE0 · 对象查找
                pObj2 = __RTDynamicCast(  // 动态类型转换(取目标接口)
                         v247,
                         0,
                         &CNRDObject `RTTI Type Descriptor',
                         &IRDActiveObject `RTTI Type Descriptor',
                         0);
                *(uint32_t *)(this + 8300) = pObj2;  // 字段 pHoldObj(this+8300) 读写
                if ( pObj2 != 0 )  // pObj2 != 0 判定
                {
                  v249 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);  // 虚槽+120 → 转发(对象+缓冲)
                  pHoldObj_7 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
                  *(uint32_t *)(this + 8304) = v249;  // 字段 nHoldPosX(this+8304) 读写
                  v251 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_7 + 124))(pHoldObj_7);  // 虚槽+124 → 目标坐标y下界
                  pHoldObj_8 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
                  *(uint32_t *)(this + 8308) = v251;  // 字段 nHoldPosY(this+8308) 读写
                  *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_8 + 128))(pHoldObj_8);  // 虚槽+128 → 目标坐标y上界
                }
                if ( *(uint32_t *)(this + 8300) != 0 )  // 字段 pHoldObj(this+8300) 判定
                {
                  if ( *(uint32_t *)(this + 8408) == 0 )  // 字段 pRoplingObj(this+8408) 判定
                  {
                    pMem = operator new(0x68u);  // 分配堆内存
                    v280 = 12;
                    if ( pMem != nullptr )  // pMem != nullptr 判定
                      v253 = sub_5E4FC0(this);
                    else
                      v253 = 0;
                    v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
                    *(uint32_t *)(this + 8408) = v253;  // 字段 pRoplingObj(this+8408) 读写
                  }
                  (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8408)  // 调用
                                                                                           + 56))(
                    *(uint32_t *)(this + 8408),  // this+8408〔pRoplingObj〕
                    *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
                    this,
                    0,
                    0,
                    0,
                    -1);
                }
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);  // 虚槽+604 → 收招例程
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(  // 调用
                  this,
                  *(uint32_t *)(*(uint32_t *)(this + 6216) + 20));  // this+6216〔pTbl6216(推断)〕
                return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                         this,
                         "FT_ROPLING",  // 标签 FT_ROPLING
                         -1,
                         0,
                         0);
              }
              break;  // 跳出本 switch(单 case 处理完)
            case 52:  // case 52 = ENUM_CMDPACKET_DECREASE_DURABILITY
              *(uint8_t *)(this + 8377) = 0;  // 字节字段 f_20B9(this+8377) 判定
              goto LABEL_303;  // 跳转 LABEL_303(收尾/共用分支)
            default:
              return result;
          }
          return result;
        // ── [段 28] 第三重 case 12：抓取目标选择 —— +8220 取 pArg3[1][0]（1 = 分型1 / 2 = 分型2）──
        //   两型各自 vt+1160(1或2) + vt+1140(+8220) 读表（1 用 +556+1368 动画基，2 用 vt+388 双参）
        case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
          v226 = pArg3[1];
          if ( v226 != nullptr && pArg3[2] - v226 != 0 )  // v226 非空 且 pArg3[2] - v226 != 0
            result = *v226;  // result = 取 v226 首 dword(对象虚表基址)
          else
            result = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          *(uint32_t *)(this + 8220) = result;  // 字段 nGrabTargetSel(this+8220) 读写
          if ( result == 1 )  // 结果==1 分支
          {
            pThis_4883 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 1);  // 虚槽+1160 → 读技能表(变体)
            nGrabTargetSel = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *(uint32_t *)(this + 8220));  // 虚槽+1140 → 读技能表
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1368);  // 虚槽+344 → 动画件访问(基偏移)
            pThis_1844 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
            result = sub_47EFD0(pThis_4883, 0.0, nGrabTargetSel, pThis_1844, pThis_1844, 0);
            *(uint32_t *)(this + 8224) = 0;  // 字段 f_2020(this+8224) 读写
            *(float *)(this + 388) = (float)result;  // 写内存
            *(uint8_t *)(this + 8228) = 0;  // 字节字段 bGrabFlag(this+8228) 判定
          }
          else if ( result == 2 )  // 否则 result==2 分支
          {
            pThis_4884 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 2);  // 虚槽+1160 → 读技能表(变体)
            fld_201C2 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *(uint32_t *)(this + 8220));  // 虚槽+1140 → 读技能表
            v232 = *(uint32_t *)this;  // 缓存对象虚表基址
            fld_201C22 = fld_201C2;
            *(uint32_t *)(this + 396) = 0;  // 字段 nSkillParamIdx(this+396) 读写
            v234 = (*(int (/*thiscall*/ **)(int))(v232 + 388))(this);  // 虚槽+388 → 攻击计算
            result = sub_47EFD0(pThis_4884, COERCE_FLOAT(2), fld_201C22, v234, v234, 0);
            *(float *)(this + 388) = (float)result;  // 写内存
          }
          return result;
        // ── [段 29] 第三重 case 14：★ 技能号语音小表 —— switch(this+7964) 六型 buff/姿态音效 ──
        //   176 FT_ANCIENT_MEMORY / 175 FT_LEAP_BUFF / 36 FT_SUN_CURTAIN / 31 FT_FAST_FIST_BUFF /
        //   37 FT_STRONG_FIST / 39 FT_FATAL_SPOT / 38 R_FT_POISON_SPREAD（纯播音效后返回）
        case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
          result = *(uint32_t *)(this + 7964);  // 字段 nSkillNo(this+7964) 读写
          switch ( result )  // 按 result 分派
          {
            case 176:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                       this,
                       "FT_ANCIENT_MEMORY",  // 标签 FT_ANCIENT_MEMORY
                       -1,
                       0,
                       0);
            case 175:
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                       this,
                       "FT_LEAP_BUFF",  // 标签 FT_LEAP_BUFF
                       -1,
                       0,
                       0);
            case 36:  // case 36 = ENUM_CMDPACKET_SET_QUEST_TRIGGER
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                       this,
                       "FT_SUN_CURTAIN",  // 标签 FT_SUN_CURTAIN
                       -1,
                       0,
                       0);
            case 31:  // case 31 = ENUM_CMDPACKET_CHANGE_SKILLSLOT
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                       this,
                       "FT_FAST_FIST_BUFF",  // 标签 FT_FAST_FIST_BUFF
                       -1,
                       0,
                       0);
            case 37:  // case 37 = ENUM_CMDPACKET_FINISH_QUEST
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                       this,
                       "FT_STRONG_FIST",  // 标签 FT_STRONG_FIST
                       -1,
                       0,
                       0);
            case 39:  // case 39 = ENUM_CMDPACKET_SET_USER_AREA
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                       this,
                       "FT_FATAL_SPOT",  // 标签 FT_FATAL_SPOT
                       -1,
                       0,
                       0);
            case 38:  // case 38 = ENUM_CMDPACKET_SET_USER_POSITION
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // return 虚调用
                       this,
                       "R_FT_POISON_SPREAD",  // 标签 R_FT_POISON_SPREAD
                       -1,
                       0,
                       0);
            default:
              break;  // 跳出本 switch(单 case 处理完)
          }
          return result;
        default:
          return result;
      }
    // ── [段 30] 第三重 case 19：★ 投技/背摔（FT_SPIRE + FT_SUPLEX）──
    //   同 case 19 大状态：RTDynamicCast 取被抱对象存 +8300 并抄坐标到 +8304/+8308/+8312；
    //   +8316 存朝向（vt+152）、+8324 与 +8325 由 pArg3[1][2]/[3] 灌入；
    //   建 0x6C 缓冲 sub_5E4DC0 存 +8320 并 vt+120/124/56 配置；本机时 vt+196(+6216+52) + FT_SPIRE；
    //   惰性建 JumpSuplexRollUnder/Over.ani 存 +8336/+8340，sub_4049C0(1.0,3.0,尺寸-100,150) 插值缩放后
    //   sub_4920E0 逐件施缩放；+8324 否则走 FT_SUPLEX / FT_SUPLEX_CRASH（vt+1140(22)>0 判分型）+ G_(BACK_)SUPLEX_START；
    //   尾部 vt+344(+556+1064 或 +608) + sub_47EFD0 伤害 + HOLD 音效
    case 19:  // case 19 = ENUM_CMDPACKET_DELETE_ITEM
      v91 = sub_45EBE0(*pArg3[1], pArg3[1][1]);  // v91 = sub_45EBE0 · 对象查找
      pObj4 = __RTDynamicCast(v91, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // pObj4 = 动态转型 CNRDObject→IRDActiveObject
      *(uint32_t *)(this + 8300) = pObj4;  // 字段 pHoldObj(this+8300) 读写
      if ( pObj4 != 0 )  // pObj4 != 0 判定
      {
        v93 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 120))(pObj4);  // 虚槽+120 → 转发(对象+缓冲)
        pHoldObj_9 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
        *(uint32_t *)(this + 8304) = v93;  // 字段 nHoldPosX(this+8304) 读写
        v95 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_9 + 124))(pHoldObj_9);  // 虚槽+124 → 目标坐标y下界
        pHoldObj_10 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
        *(uint32_t *)(this + 8308) = v95;  // 字段 nHoldPosY(this+8308) 读写
        *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_10 + 128))(pHoldObj_10);  // 虚槽+128 → 目标坐标y上界
      }
      *(uint32_t *)(this + 8316) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 虚槽+152 → 取值(参数)
      *(uint8_t *)(this + 8326) = 0;  // 字节字段 f_2086(this+8326) 判定
      *(uint32_t *)(this + 8328) = 0;  // 字段 f_2088(this+8328) 读写
      *(uint8_t *)(this + 8332) = 0;  // 字节字段 f_208C(this+8332) 判定
      *(uint8_t *)(this + 8333) = 0;  // 字节字段 f_208D(this+8333) 判定
      pHoldObj_11 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
      *(uint8_t *)(this + 8324) = pArg3[1][2] != 0;  // 字节字段 bHoldMode(this+8324) 判定
      *(uint8_t *)(this + 8325) = pArg3[1][3] != 0;  // 字节字段 bSubMode(this+8325) 判定
      if ( pHoldObj_11 != 0 )  // 子型 fld_206C9 非 0 判定
      {
        if ( *(uint32_t *)(this + 8320) == 0 )  // 字段 pHoldHost(this+8320) 判定
        {
          *(float *)&Block = COERCE_FLOAT(operator new(0x6Cu));  // 分配堆内存
          v280 = 4;
          if ( *(float *)&Block == 0.0 )  // 浮点 Block 为 0 判定(未取到参)
            v98 = 0;
          else
            v98 = sub_5E4DC0(this);  // 调 存 +8320 并 vt+120/124/56 配置
          v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          *(uint32_t *)(this + 8320) = v98;  // 字段 pHoldHost(this+8320) 读写
        }
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8320) + 120))(  // 调用
          *(uint32_t *)(this + 8320),  // this+8320〔pHoldHost(推断)〕
          *(uint8_t *)(this + 8324));  // this+8324〔bHoldMode(推断)〕
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8320) + 124))(  // 调用
          *(uint32_t *)(this + 8320),  // this+8320〔pHoldHost(推断)〕
          *(uint8_t *)(this + 8325));  // this+8325〔bSubMode〕
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8320) + 56))(  // 调用
          *(uint32_t *)(this + 8320),  // this+8320〔pHoldHost(推断)〕
          *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
          this,
          0,
          0,
          0,
          -1);
      }
      v99 = *(uint32_t *)this;  // 缓存对象虚表基址
      if ( *(uint8_t *)(this + 8324) != 0 )  // 字节字段 bHoldMode(this+8324) 判定
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(v99 + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 52));  // 虚槽+196 → 物件非空判定
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
          this,
          "FT_SPIRE",  // 标签 FT_SPIRE
          -1,
          0,
          0);
        pThis_20902 = (uint32_t **)(this + 8336);  // this+8336〔pVtStack〕
        if ( *(uint32_t *)(this + 8336) == 0 )  // 字段 pVtStack(this+8336) 判定
        {
          *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
          v280 = 5;
          if ( *(float *)&Block == 0.0 )  // 浮点 Block 为 0 判定(未取到参)
          {
            pThis_6C5 = nullptr;
          }
          else if ( *(uint32_t *)(this + 384) < 0x10u )  // 字段 nAnimPoolCap(this+384) 读写
          {
            pThis_6C5 = (uint32_t *)sub_431920(this + 108, (char)"Effect/Animation/JumpSuplexRollUnder.ani", 1);  // pThis_6C5 = sub_431920 · 动画件构造
          }
          else
          {
            pThis_6C5 = (uint32_t *)sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/JumpSuplexRollUnder.ani", 1);  // pThis_6C5 = sub_431920 · 动画件构造
          }
          v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          *pThis_20902 = pThis_6C5;  // 写内存
          *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
          v280 = 6;
          if ( *(float *)&Block == 0.0 )  // 浮点 Block 为 0 判定(未取到参)
          {
            pThis_6C6 = 0;
          }
          else if ( *(uint32_t *)(this + 384) < 0x10u )  // 字段 nAnimPoolCap(this+384) 读写
          {
            pThis_6C6 = sub_431920(this + 108, (char)"Effect/Animation/JumpSuplexRollOver.ani", 1);  // pThis_6C6 = sub_431920 · 动画件构造
          }
          else
          {
            pThis_6C6 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/JumpSuplexRollOver.ani", 1);  // pThis_6C6 = sub_431920 · 动画件构造
          }
          v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
          *(uint32_t *)(this + 8340) = pThis_6C6;  // 字段 pAnimA(this+8340) 读写
        }
        pHoldObj_ = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
        *(float *)&Block = 1.0;  // 写内存
        if ( pHoldObj_ != 0 )  // 子型 fld_206C10 非 0 判定
        {
          v104 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_ + 192))(pHoldObj_);  // 虚槽+192 → 取尺寸/包围盒
          *(float *)&Block = sub_4049C0(1.0, 3.0, v104 - 100, 150);  // sub_4049C0 · 区间线性插值
        }
        Block2 = Block;
        pThis_4742 = 2;
        do
        {
          sub_4920E0(*pThis_20902++, *(float *)&Block2, *(float *)&Block2);  // sub_4920E0 · 批量改写全帧缩放
          --pThis_4742;  // 递减 pThis_4742
        }
        while ( *(float *)&pThis_4742 != 0.0 );
        *(uint8_t *)(this + 8334) = 0;  // 字节字段 bPairOk(this+8334) 判定
      }
      else
      {
        // ── [段 31] case 19 之无马支：vt+1140(22) 分派 FT_SUPLEX / FT_SUPLEX_CRASH 双音效 ──
        if ( (*(int (/*thiscall*/ **)(int, int))(v99 + 1140))(this, 22) <= 0 )  // 虚槽+1140 → 读技能表
          (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 212))(this, "FT_SUPLEX");  // 虚槽+212 → vt+212
        else
          (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 212))(this, "FT_SUPLEX_CRASH");  // 虚槽+212 → vt+212
        v106 = *(uint32_t *)this;  // 缓存对象虚表基址
        pSubCtx_ = *(uint32_t *)(this + 6216);  // 字段 pSubCtx(this+6216) 读写
        if ( *(uint8_t *)(this + 8325) != 0 )  // 字节字段 bSubMode(this+8325) 判定
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, int))(v106 + 196))(  // 调用
            this,
            *(uint32_t *)(pSubCtx_ + 28),
            -1,
            0,
            0,
            v265);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
            this,
            "G_BACK_SUPLEX_START",  // 标签 G_BACK_SUPLEX_START
            -1,
            0,
            0);
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t, int))(v106 + 196))(  // 调用
            this,
            *(uint32_t *)(pSubCtx_ + 24),
            -1,
            0,
            0,
            v265);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
            this,
            "G_SUPLEX_START",  // 标签 G_SUPLEX_START
            -1,
            0,
            0);
        }
      }
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 3, 1000, 1000);  // 虚槽+888 → 帧长标定
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚槽+896
      sub_495890(2, 0);  // sub_495890 · 模式选择式方位设置
      nGrabAnimBase = *(uint32_t *)(this + 556);  // 字段 nGrabAnimBase(this+556) 读写
      if ( *(uint8_t *)(this + 8324) != 0 )  // 字节字段 bHoldMode(this+8324) 判定
        v109 = nGrabAnimBase + 1064;
      else
        v109 = nGrabAnimBase + 608;
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)this + 344))(v109);  // 虚槽+344 → 动画件访问(基偏移)
      fld_20842 = *(uint8_t *)(this + 8324) != 0 ? 18 : 9;  // 字节字段 bHoldMode(this+8324) 判定
      pThis_1845 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
      pThis_47410 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, fld_20842);  // 虚槽+1140 → 读技能表
      v113 = *(uint32_t *)this;  // 缓存对象虚表基址
      Block = pThis_47410;
      v114 = (char *)(*(int (/*thiscall*/ **)(int, int))(v113 + 1160))(this, fld_20842);  // 虚槽+1160 → 读技能表(变体)
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(v114, 0.0, (int)Block, pThis_1845, pThis_1845, 0));  // sub_47EFD0
      bSubMode_ = *(uint8_t *)(this + 8325);  // 字节字段 bSubMode(this+8325) 判定
      *(float *)(this + 388) = (float)(int)Block;  // 写内存
      if ( bSubMode_ != 0 )  // 子型 fld_20852 非 0 判定
      {
        pThis_4885 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 10);  // 虚槽+1160 → 读技能表(变体)
        pThis_47411 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 10);  // 虚槽+1140 → 读技能表
        pThis_1846 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
        *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4885, 0.0, pThis_47411, pThis_1846, pThis_1846, 0));  // sub_47EFD0
        *(float *)(this + 388) = (double)(int)Block + *(float *)(this + 388);  // 写内存
        *(float *)&Block = COERCE_FLOAT(sub_47EF20(2, pThis_47411, -1, -1, 11));  // sub_47EF20
        *(float *)(this + 460) = (double)(int)Block + *(float *)(this + 460);  // 写内存
      }
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "HOLD", -1, 0, 0);  // 虚槽+212 → vt+212
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 32] 第三重 case 20：★ 骑乘（RIDE / FT_MOUNTAIN）—— 上坐与维持两支 ──
    //   +8344 取 pArg3[1][0]；非 0 时 vt+196(+6216+32/36/40 按 +8348 奇偶)；
    //   fld_199C != 20（新进）时清 +8348/+8360 并记当前 XY 到 +8364/+8368，抓被骑对象（+8356，vt+776(3) 判可骑）
    //   并 vt+556/vt+768 配置；vt+688→sub_42FC90→sub_4924C0 取尺寸算 +8372 偏移（vt+152 定正负）后 vt+112 落点；
    //   +8344==1 维持支：+++8348 计数，本机时 sub_4E5F70(this+? 对象, this, 被骑体, 3 浮点坐标, 1, 1) 同步
    case 20:  // case 20 = ENUM_CMDPACKET_MOVE_ITEMSPACE
      v119 = *pArg3[1];
      *(uint32_t *)(this + 8344) = v119;  // 字段 nRideMode(this+8344) 读写
      if ( v119 != 0 )  // v119 != 0 判定
      {
        pSubCtx_2 = *(uint32_t *)(this + 6216);  // 字段 pSubCtx(this+6216) 读写
        if ( *(uint32_t *)(this + 8348) % 2 != 0 )  // 字段 nPhaseParity(this+8348) 读写
          fld_18484 = *(uint32_t *)(pSubCtx_2 + 40);  // 字段 +40(fld_18483+40) 读写
        else
          fld_18484 = *(uint32_t *)(pSubCtx_2 + 36);  // 字段 +36(fld_18483+36) 读写
      }
      else
      {
        fld_18484 = *(uint32_t *)(*(uint32_t *)(this + 6216) + 32);  // 字段 pSubCtx(this+6216) 读写
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 196))(this, fld_18484);  // 虚槽+196 → 物件非空判定
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 2, 2, 1000, 1000);  // 虚槽+888 → 帧长标定
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚槽+896
      if ( nBigState != 20 )  // 子型 fld_199C 非 20 判定
      {
        v122 = *(uint32_t *)this;  // 缓存对象虚表基址
        *(uint32_t *)(this + 8348) = 0;  // 字段 nPhaseParity(this+8348) 读写
        *(uint8_t *)(this + 8360) = 0;  // 字节字段 bHoldClear(this+8360) 判定
        *(uint32_t *)(this + 8364) = (*(int (/*thiscall*/ **)(int))(v122 + 120))(this);  // 虚槽+120 → 转发(对象+缓冲)
        *(uint32_t *)(this + 8368) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this);  // 虚槽+124 → 目标坐标y下界
        v123 = sub_45EBE0(pArg3[1][1], pArg3[1][2]);  // v123 = sub_45EBE0 · 对象查找
        pObj3 = __RTDynamicCast(v123, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // pObj3 = 动态转型 CNRDObject→IRDActiveObject
        *(uint32_t *)(this + 8356) = pObj3;  // 字段 pHoldTarget(this+8356) 读写
        if ( pObj3 != 0 )  // pObj3 != 0 判定
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 776))(pObj3, 3) != 0 )  // 虚槽+776
          {
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8356) + 556))(*(uint32_t *)(this + 8356), 0);  // 字段 pHoldTarget(this+8356) 读写
            (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 8356) + 768))(  // 调用
              *(uint32_t *)(this + 8356),  // this+8356〔uPick8356(推断)〕
              3,
              0,
              0);
            (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 8356) + 556))(*(uint32_t *)(this + 8356), 1);  // 字段 pHoldTarget(this+8356) 读写
          }
          fld_20A42 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8356) + 688))(*(uint32_t *)(this + 8356))  // 字段 pHoldTarget(this+8356) 读写
                           + 20);
          v126 = sub_42FC90(fld_20A42);  // v126 = sub_42FC90 · 88B 元素计数
          v127 = (int *)sub_4924C0(v126 - 1);  // v127 = sub_4924C0 · 按索引取帧并确保图像就绪
          v128 = *v127;  // v128 = 取 v127 首 dword(对象虚表基址)
          if ( *v127 != 0 )  // v127 首 dword 非 0 判定
          {
            if ( (unsigned int)((*(uint32_t *)(v128 + 20) >> 2) + 40) <= 0x50 )  // 字段 +20(v128+20) 条件判定
              v129 = 80;
            else
              v129 = (*(uint32_t *)(v128 + 20) >> 2) + 40;  // 字段 +20(v128+20) 读写
            v130 = sub_4918E0(v127, 0);  // v130 = sub_4918E0 · 动画盒四边界提取
            pHoldTarget_ = *(uint32_t *)(this + 8356);  // 字段 pHoldTarget(this+8356) 读写
            *(uint32_t *)(this + 8372) = v129 - v130;  // 字段 nDiffVal(this+8372) 读写
            if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldTarget_ + 152))(pHoldTarget_) == 0 )  // 虚槽+152 → 取值(参数)
              *(uint32_t *)(this + 8372) = -*(uint32_t *)(this + 8372);  // 字段 nDiffVal(this+8372) 读写
            v132 = *(uint32_t *)this;  // 缓存对象虚表基址
            pHoldTarget_2 = *(int **)(this + 8356);  // this+8356〔uPick8356(推断)〕
            v134 = *pHoldTarget_2;  // v134 = 取 fld_20A44 首 dword(对象虚表基址)
            Block = pHoldTarget_2;
            v135 = (*(int (/*stdcall*/ **)(uint32_t))(v134 + 124))(0);  // 虚槽+124 → 目标坐标y下界
            v136 = (*(int (/*thiscall*/ **)(int *, int))(*pHoldTarget_2 + 120))(pHoldTarget_2, v135 + 1);  // 虚槽+120 → 转发(对象+缓冲)
            (*(void (/*thiscall*/ **)(int, int))(v132 + 112))(this, *(uint32_t *)(this + 8372) + v136);  // 虚槽+112 → 坐标三元组写入
            v137 = *(uint32_t *)this;  // 缓存对象虚表基址
            fld_20A45 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8356) + 152))(*(uint32_t *)(this + 8356));  // 字段 pHoldTarget(this+8356) 读写
            v139 = sub_432E50(fld_20A45);  // v139 = sub_432E50 · 关系码对调映射
            (*(void (/*thiscall*/ **)(int, int))(v137 + 148))(this, v139);  // 虚槽+148 → 位置/朝向写入
          }
        }
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 760);  // 虚槽+344 → 动画件访问(基偏移)
        pThis_4945 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);  // 虚槽+1172 → 技能名/ID换算
        sub_406D60(pThis_4945);  // sub_406D60 · std::string 从 C 串赋值
        pThis_4886 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 14);  // 虚槽+1160 → 读技能表(变体)
        pThis_47412 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 14);  // 虚槽+1140 → 读技能表
        pThis_1847 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
        *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4886, 0.0, pThis_47412, pThis_1847, pThis_1847, 0));  // sub_47EFD0
        *(float *)(this + 388) = (float)(int)Block;  // 写内存
        *(uint32_t *)(this + 8352) = sub_47E9D0(pThis_4886, 0);  // sub_47E9D0
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "RIDE", -1, 0, 0);  // 虚槽+212 → vt+212
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
          this,
          "FT_MOUNTAIN",  // 标签 FT_MOUNTAIN
          -1,
          0,
          0);
      }
      if ( *(uint32_t *)(this + 8344) == 1 )  // 字段 nRideMode(this+8344) 判定
      {
        pHoldTarget_3 = *(uint32_t *)(this + 8356);  // 字段 pHoldTarget(this+8356) 读写
        ++*(uint32_t *)(this + 8348);  // 字段 nPhaseParity(this+8348) 读写
        if ( pHoldTarget_3 != 0 )  // 子型 fld_20A46 非 0 判定
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚槽+308 → 是否本地玩家
          {
            v144 = *(uint32_t *)this;  // 缓存对象虚表基址
            *(float *)&v265 = 0.0;  // 写内存
            v266 = 0.0;  // 置 v266 = 0.0(浮点初值)
            v267 = 0.0;  // 置 v267 = 0.0(浮点初值)
            v268 = 0;
            v269 = 0;
            v270 = 0;
            if ( (*(int (/*thiscall*/ **)(int))(v144 + 152))(this) != 0 )  // 虚槽+152 → 取值(参数)
              pThis_35 = (void *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 53);  // 虚槽+120 → 转发(对象+缓冲)
            else
              pThis_35 = (void *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 53);  // 虚槽+120 → 转发(对象+缓冲)
            Block = pThis_35;
            v146 = (double)(int)pThis_35;
            v147 = *(uint32_t *)this;  // 缓存对象虚表基址
            *(float *)&v265 = v146;  // 写内存
            v148 = (void *)(*(int (/*thiscall*/ **)(int))(v147 + 124))(this);  // 虚槽+124 → 目标坐标y下界
            v149 = *(uint32_t *)this;  // 缓存对象虚表基址
            Block = v148;
            v266 = (float)(int)v148;
            v150 = (*(int (/*thiscall*/ **)(int))(v149 + 128))(this);  // 虚槽+128 → 目标坐标y上界
            pHoldTarget_4 = *(uint32_t *)(this + 8356);  // 字段 pHoldTarget(this+8356) 读写
            Block = (void *)(v150 + 17);
            v267 = (float)(v150 + 17);
            sub_4E5F70(pThis_47412, this, pHoldTarget_4, (float *)&v265, 1, 1);  // sub_4E5F70 · 硬直率掷
          }
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 14);  // 虚槽+1160 → 读技能表(变体)
          sub_47DCD0(this, -1);  // 调 震动/资源档位设置
        }
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
          this,
          "R_FT_MOUNTAIN_ATK",  // 标签 R_FT_MOUNTAIN_ATK
          -1,
          0,
          0);
      }
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 33] 第三重 case 21：FT_SKYSTEP（踏空步）—— +6216+44 参 + vt+344(+556+912) ──
    //   ++(+8444) 计次、++(+6896) 帧计数；vt+1140/vt+1160(17) 取伤害表后 vt+388 写 +388
    case 21:  // case 21 = ENUM_CMDPACKET_SORT_ITEM
      LOBYTE(nArg4) = 0;  // 把 0 低字节存入 nArg4(短串内联指针)
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 44));  // 虚槽+196 → 物件非空判定
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 912);  // 虚槽+344 → 动画件访问(基偏移)
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 2, 1000, 1000);  // 虚槽+888 → 帧长标定
      nSkillGate = *(uint32_t *)(this + 8444) + 1;  // 字段 nSkillGate(this+8444) 读写
      ++*(uint32_t *)(this + 6896);  // 字段 nTickCount(this+6896) 读写
      v153 = *(uint32_t *)this;  // 缓存对象虚表基址
      *(uint32_t *)(this + 8444) = nSkillGate;  // 字段 nSkillGate(this+8444) 读写
      v154 = (*(int (/*thiscall*/ **)(int))(v153 + 388))(this);  // 虚槽+388 → 攻击计算
      pThis_47413 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 17);  // 虚槽+1140 → 读技能表
      pThis_4887 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 17);  // 虚槽+1160 → 读技能表(变体)
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4887, 0.0, pThis_47413, v154, v154, 0));  // sub_47EFD0
      *(float *)(this + 388) = (float)(int)Block;  // 写内存
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
        this,
        "FT_SKYSTEP",  // 标签 FT_SKYSTEP
        -1,
        0,
        0);
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 34] 第三重 case 22：★ FT_ONEINCH（寸拳）+ ClosePunchExecute.ani ──
    //   vt+196(+6216+56) + vt+344(+556+1216)；sub_495500(vt+672(3)) 表读数乘 0.01+1.0 作倍率；
    //   惰性建 ClosePunchExecute.ani 存 +8412 → vt+204(1, anim, 33, -49, 0, 0)；sub_5E5260(+8416) 清缓冲；
    //   清 +8432/+8436 后双音效 FT_ONEINCH + ONE_INCH_PUNCH
    case 22:  // case 22 = ENUM_CMDPACKET_BUY_ITEM
      pThis_47414 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 19);  // 虚槽+1140 → 读技能表
      pThis_4888 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 19);  // 虚槽+1160 → 读技能表(变体)
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 56));  // 虚槽+196 → 物件非空判定
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1216);  // 虚槽+344 → 动画件访问(基偏移)
      pThis_1848 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4888, 0.0, pThis_47414, pThis_1848, pThis_1848, 0));  // sub_47EFD0
      *(float *)(this + 388) = (float)(int)Block;  // 写内存
      v160 = (void *)sub_47EF20(1, pThis_47414, -1, -1, 11);  // v160 = sub_47EF20
      v161 = *(uint32_t *)this;  // 缓存对象虚表基址
      Block = v160;
      *(float *)&pThis_4742 = (double)(int)v160 * 0.0099999998 + 1.0;  // 写内存
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v161 + 876))(this, 0, 0, 0, 0, 0, 0);  // 虚槽+876 → 双段位移
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      v162 = *(uint32_t *)this;  // 缓存对象虚表基址
      pThis_2A0 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);  // 虚槽+672 → 队伍编号取址
      *(float *)&Block = COERCE_FLOAT(sub_495500(pThis_2A0));  // sub_495500 · 槽对乘积读取
      (*(void (/*fastcall*/ **)(int, uint32_t, uint32_t, uint32_t, int, uint32_t))(v162 + 888))(  // 调用
        this,
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742) >> 32,
        0,
        0,
        1000,
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742));
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚槽+896
      if ( *(uint32_t *)(this + 8412) == 0 )  // 字段 pAnimE(this+8412) 判定
      {
        *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
        v280 = 7;
        if ( *(float *)&Block == 0.0 )  // 浮点 Block 为 0 判定(未取到参)
        {
          pThis_6C7 = 0;
        }
        else if ( *(uint32_t *)(this + 384) < 0x10u )  // 字段 nAnimPoolCap(this+384) 读写
        {
          // ── [段 35] case 22 之 +8412 惰性建 ClosePunchExecute.ani（内联/堆指针二选一）──
          pThis_6C7 = sub_431920(this + 108, (char)"Effect/Animation/ClosePunchExecute.ani", 1);  // pThis_6C7 = sub_431920 · 动画件构造
        }
        else
        {
          pThis_6C7 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/ClosePunchExecute.ani", 1);  // pThis_6C7 = sub_431920 · 动画件构造
        }
        v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
        *(uint32_t *)(this + 8412) = pThis_6C7;  // 字段 pAnimE(this+8412) 读写
      }
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调用
        this,
        1,
        *(uint32_t *)(this + 8412),  // this+8412〔动画〕
        33,
        -49,
        0,
        0);
      sub_5E5260((void **)(this + 8416));  // 调 动画子对象清理临时缓冲
      v165 = *(uint32_t *)this;  // 缓存对象虚表基址
      *(uint32_t *)(this + 8432) = 0;  // 字段 pBuffObjA(this+8432) 读写
      *(uint8_t *)(this + 8436) = 0;  // 字节字段 pBuffObjB(this+8436) 判定
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v165 + 212))(this, "FT_ONEINCH", -1, 0, 0);  // 虚槽+212 → vt+212
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
        this,
        "ONE_INCH_PUNCH",  // 标签 ONE_INCH_PUNCH
        -1,
        0,
        0);
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 36] 第三重 case 23：FT_UPPER_READY（上段预备）—— 动画基 +556+152 ──
    //   vt+196(+6216+8)；sub_47EFD0 伤害 + sub_47EF20 写 +456；sub_495500(vt+672(3)) 倍率 → vt+888；
    //   清 +8437 后 vt+1172(1,-1) 取动作串经 vt+212 播报，再 vt+1172(3) → sub_406D60 赋值
    case 23:  // case 23 = ENUM_CMDPACKET_RENT_AVATAR
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 8));  // 虚槽+196 → 物件非空判定
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 152);  // 虚槽+344 → 动画件访问(基偏移)
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
        this,
        "FT_UPPER_READY",  // 标签 FT_UPPER_READY
        -1,
        0,
        0);
      pThis_4889 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 5);  // 虚槽+1160 → 读技能表(变体)
      pThis_47415 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 5);  // 虚槽+1140 → 读技能表
      pThis_1849 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
      *(float *)&Block = COERCE_FLOAT(sub_47EFD0(pThis_4889, COERCE_FLOAT(1), pThis_47415, pThis_1849, pThis_1849, 0));  // sub_47EFD0
      *(float *)(this + 388) = (float)(int)Block;  // 写内存
      *(uint32_t *)(this + 456) = sub_47EF20(2, pThis_47415, -1, -1, 11);  // sub_47EF20
      *(float *)&Block = COERCE_FLOAT(sub_47EF20(0, pThis_47415, -1, -1, 11));  // sub_47EF20
      v169 = *(uint32_t *)this;  // 缓存对象虚表基址
      *(float *)&pThis_4742 = (double)(int)Block * 0.0099999998 + 1.0;  // 写内存
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v169 + 876))(this, 0, 0, 0, 0, 0, 0);  // 虚槽+876 → 双段位移
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      pThis_2A02 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 672))(this, 3);  // 虚槽+672 → 队伍编号取址
      *(float *)&Block = COERCE_FLOAT(sub_495500(pThis_2A02));  // sub_495500 · 槽对乘积读取
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 888))(  // 调用
        this,
        0,
        0,
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742),
        (uint64_t)((double)(int)Block * *(float *)&pThis_4742));
      v171 = *(uint32_t *)this;  // 缓存对象虚表基址
      pThis_987 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);  // 虚槽+152 → 取值(参数)
      (*(void (/*thiscall*/ **)(int, int))(v171 + 896))(this, pThis_987);  // 虚槽+896
      v173 = *(uint32_t *)this;  // 缓存对象虚表基址
      *(uint8_t *)(this + 8437) = 0;  // 字节字段 f_20F5(this+8437) 判定
      v174 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(v173 + 1172))(this, 1, -1, 0, 0);  // 虚槽+1172 → 技能名/ID换算
      (*(void (/*thiscall*/ **)(int, int))(v173 + 212))(this, v174);  // 虚槽+212 → vt+212
      pThis_4946 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1172))(this, 3);  // 虚槽+1172 → 技能名/ID换算
      sub_406D60(pThis_4946);  // sub_406D60 · std::string 从 C 串赋值
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 37] 第三重 case 24：★ SKYRADE_SWING（空掠斩）—— +8472 分 0 / 非 0 两支 ──
    //   非 0：vt+604(0) + 抓取（RTDynamicCast 存 +8300 抄坐标）+60 缓冲 sub_5E4ED0 存 +8480 → 播 SKYRADE_SWING；
    //   0：vt+196(+6216+60) + vt+344(+556+1672) + R_FT_ATK + vt+1172(1,-1) 播报
    case 24:  // case 24 = ENUM_CMDPACKET_EXTEND_AVATAR
      v176 = *(uint32_t *)this;  // 缓存对象虚表基址
      *(uint32_t *)(this + 8472) = *pArg3[1];  // 字段 nFinishFlag(this+8472) 读写
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v176 + 876))(this, 0, 0, 0, 0, 0, 0);  // 虚槽+876 → 双段位移
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);  // 虚槽+896
      sub_495890(2, 0);  // sub_495890 · 模式选择式方位设置
      if ( *(uint32_t *)(this + 8472) != 0 )  // 字段 nFinishFlag(this+8472) 判定
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);  // 虚槽+604 → 收招例程
        LOBYTE(nArg5) = 0;  // 把 0 低字节存入 nArg5(短串内联指针)
        v184 = sub_45EBE0(pArg3[1][1], pArg3[1][2]);  // v184 = sub_45EBE0 · 对象查找
        pObj = __RTDynamicCast(v184, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);  // pObj = 动态转型 CNRDObject→IRDActiveObject
        *(uint32_t *)(this + 8300) = pObj;  // 字段 pHoldObj(this+8300) 读写
        if ( pObj != 0 )  // pObj != 0 判定
        {
          v186 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚槽+120 → 转发(对象+缓冲)
          pHoldObj_2 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
          *(uint32_t *)(this + 8304) = v186;  // 字段 nHoldPosX(this+8304) 读写
          v188 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_2 + 124))(pHoldObj_2);  // 虚槽+124 → 目标坐标y下界
          pHoldObj_3 = *(uint32_t *)(this + 8300);  // 字段 pHoldObj(this+8300) 读写
          *(uint32_t *)(this + 8308) = v188;  // 字段 nHoldPosY(this+8308) 读写
          *(uint32_t *)(this + 8312) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHoldObj_3 + 128))(pHoldObj_3);  // 虚槽+128 → 目标坐标y上界
          if ( *(uint32_t *)(this + 8480) == 0 )  // 字段 pAtkObj(this+8480) 判定
          {
            *(float *)&Block = COERCE_FLOAT(operator new(0x64u));  // 分配堆内存
            v280 = 8;
            if ( *(float *)&Block == 0.0 )  // 浮点 Block 为 0 判定(未取到参)
              v190 = 0;
            else
              v190 = sub_5E4ED0(this);  // 调 存 +8480 → 播 SKYRADE_SWING
            v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            *(uint32_t *)(this + 8480) = v190;  // 字段 pAtkObj(this+8480) 读写
          }
          (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8480) + 56))(  // 调用
            *(uint32_t *)(this + 8480),  // this+8480〔pAtkObj〕
            *(uint32_t *)(this + 8300),  // this+8300〔抄坐标〕
            this,
            0,
            0,
            0,
            -1);
        }
        *(uint8_t *)(this + 8476) = 0;  // 字节字段 bFinishFlag(this+8476) 判定
        *(uint8_t *)(this + 8477) = 0;  // 字节字段 f_211D(this+8477) 判定
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
          this,
          "SKYRADE_SWING",  // 标签 SKYRADE_SWING
          -1,
          0,
          0);
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 60));  // 虚槽+196 → 物件非空判定
        (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 1, 2, 1000, 1000);  // 虚槽+888 → 帧长标定
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1672);  // 虚槽+344 → 动画件访问(基偏移)
        pThis_18410 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
        pThis_47416 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 3);  // 虚槽+1140 → 读技能表
        pThis_48810 = (char *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 3);  // 虚槽+1160 → 读技能表(变体)
        v180 = (void *)sub_47EFD0(pThis_48810, 0.0, pThis_47416, pThis_18410, pThis_18410, 0);  // v180 = sub_47EFD0
        v181 = *(uint32_t *)this;  // 缓存对象虚表基址
        Block = v180;
        *(float *)(this + 388) = (float)(int)v180;  // 写内存
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(v181 + 212))(this, "R_FT_ATK", -1, 0, 0);  // 虚槽+212 → vt+212
        v182 = *(uint32_t *)this;  // 缓存对象虚表基址
        pThis_4947 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 1, -1, 0, 0);  // 虚槽+1172 → 技能名/ID换算
        (*(void (/*thiscall*/ **)(int, int))(v182 + 212))(this, pThis_4947);  // 虚槽+212 → vt+212
      }
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 38] 第三重 case 26：★ 肩撞（ShoulderTackle.ani / FT_TK / QUICK_MOTION_02）──
    //   +8496 分 0 / 1；1 时 +8500 取 pArg3[1][1]，sub_4AECE0(avt+120,2)+sub_4939E0 停动画，
    //   sub_423A80 两次（sub_47EFD0 伤害链 + sub_47E9D0(3)/(2) 读表）算 vt+219 分帧位移，写 +8504=-200/+8516=0；
    //   惰性建 ShoulderTackle.ani 存 +8512 → vt+204(1,...) 挂载 → 双音效 FT_TK + QUICK_MOTION_02；
    //   0 支：vt+196(+6216+64) + 位移链（fabs(宿主+16) 作帧长） + vt+224 挂帧 + sub_4BA610(4) + FT_TK_READY(13 参)
    case 26:  // case 26 = ENUM_CMDPACKET_REPAIR_EQUIPMENT
      v191 = *(uint32_t *)this;  // 缓存对象虚表基址
      *(uint32_t *)(this + 8496) = *pArg3[1];  // 字段 nChargeState(this+8496) 读写
      v192 = (char *)(*(int (/*thiscall*/ **)(int, int))(v191 + 1160))(this, 54);  // 虚槽+1160 → 读技能表(变体)
      pThis_47417 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 54);  // 虚槽+1140 → 读技能表
      nChargeState_ = *(uint32_t *)(this + 8496);  // 字段 nChargeState(this+8496) 读写
      if ( nChargeState_ != 0 )  // 子型 fld_21302 非 0 判定
      {
        if ( nChargeState_ == 1 )  // fld_21302 == 1 判定
        {
          pAnimObj = *(void **)(this + 120);  // this+120〔pAnimObj〕
          *(uint32_t *)(this + 8500) = pArg3[1][1];  // 字段 nChargeTime(this+8500) 读写
          sub_4AECE0(pAnimObj, 2);  // 调 切武器动画
          sub_4939E0(*(uint32_t *)(this + 120), 0);  // sub_4939E0 · 播放/暂停级联
          LOBYTE(nArg5) = 0;  // 把 0 低字节存入 nArg5(短串内联指针)
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 344))(this, *(uint32_t *)(this + 556) + 1824);  // 虚槽+344 → 动画件访问(基偏移)
          pThis_18411 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 388))(this);  // 虚槽+388 → 攻击计算
          v201 = (void *)sub_47EFD0(v192, 0.0, pThis_47417, pThis_18411, pThis_18411, 0);  // v201 = sub_47EFD0
          v202 = *(uint32_t *)this;  // 缓存对象虚表基址
          Block = v201;
          v203 = (*(int (/*thiscall*/ **)(int))(v202 + 388))(this);  // 虚槽+388 → 攻击计算
          v204 = sub_47EFD0(v192, COERCE_FLOAT(1), pThis_47417, v203, v203, 0);
          fld_2134 = (void *)sub_423A80(Block, v204, *(uint32_t *)(this + 8500), dword_9B9348);  // fld_2134 = sub_423A80 · 同上 int 版
          nChargeTime = *(uint32_t *)(this + 8500);  // 字段 nChargeTime(this+8500) 读写
          Block = fld_2134;
          *(float *)(this + 388) = (float)(int)fld_2134;  // 写内存
          dword_9B93482 = dword_9B9348;
          fld_213422 = nChargeTime;
          v256 = sub_47E9D0(v192, 3u);  // 调 收招/结束例程
          v207 = sub_47E9D0(v192, 2u);  // 调 收招/结束例程
          v208 = sub_423A80(v207, v256, fld_213422, dword_9B93482);  // v208 = sub_423A80 · 同上 int 版
          Block = *(void **)this;
          v209 = sub_47E9D0(v192, 4u);  // 调 收招/结束例程
          (*((void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))Block + 219))(  // 调用
            this,
            0,
            v208,
            v208,
            0,
            v209,
            1);
          *(uint32_t *)(this + 8504) = -200;  // 字段 f_2138(this+8504) 读写
          *(uint32_t *)(this + 8516) = 0;  // 字段 f_2144(this+8516) 读写
          if ( *(uint32_t *)(this + 8512) == 0 )  // 字段 pAnimF(this+8512) 判定
          {
            *(float *)&Block = COERCE_FLOAT(sub_42FCB0(228));  // sub_42FCB0 · CRT 一次性初始化
            v280 = 9;
            if ( *(float *)&Block == 0.0 )  // 浮点 Block 为 0 判定(未取到参)
            {
              pThis_6C8 = 0;
            }
            else if ( *(uint32_t *)(this + 384) < 0x10u )  // 字段 nAnimPoolCap(this+384) 读写
            {
              pThis_6C8 = sub_431920(this + 108, (char)"Effect/Animation/ShoulderTackle.ani", 1);  // pThis_6C8 = sub_431920 · 动画件构造
            }
            else
            {
              pThis_6C8 = sub_431920(*(uint32_t *)(this + 364), (char)"Effect/Animation/ShoulderTackle.ani", 1);  // pThis_6C8 = sub_431920 · 动画件构造
            }
            v280 = -1;  // 置 -1(SEH 展开状态/空槽哨兵)
            *(uint32_t *)(this + 8512) = pThis_6C8;  // 字段 pAnimF(this+8512) 读写
          }
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 调用
            this,
            1,
            *(uint32_t *)(this + 8512),  // this+8512〔动画〕
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
            this,
            "FT_TK",  // 标签 FT_TK
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
            this,
            "QUICK_MOTION_02",  // 标签 QUICK_MOTION_02
            -1,
            0,
            0);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 64));  // 虚槽+196 → 物件非空判定
        fld_703 = (uint64_t)fabs(*(float *)(*(uint32_t *)(this + 112) + 16));  // 字段 pHostComp(this+112) 读写
        fld_7032 = fld_703;
        if ( (uint32_t)fld_703 != 0 )  // fld_703 非 0 判定
          LODWORD(fld_703) = sub_47E9D0(v192, 1u);  // sub_47E9D0
        (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t, int))(*(uint32_t *)this + 876))(  // 调用
          this,
          0,
          fld_7032,
          fld_7032,
          0,
          fld_703,
          1);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(  // 调用
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        v197 = *(void (/*thiscall*/ ***)(int, int))this;
        pThis_988 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);  // 虚槽+152 → 取值(参数)
        v197[224](this, pThis_988);  // 通过函数表 v197[224] 调用
        (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 888))(this, 3, 3, 1000, 1000);  // 虚槽+888 → 帧长标定
        *(uint32_t *)(this + 8508) = 0;  // 字段 f_213C(this+8508) 读写
        sub_4BA610(4);  // sub_4BA610 · 魔能充能动画选择
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 调用
          this,
          "FT_TK_READY",  // 标签 FT_TK_READY
          13,
          0,
          0);
      }
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
    // ── [段 39] 第三重 default：无专属处理，直接 goto LABEL_251 走公共尾（非法事件号静默）──
    default:
      goto LABEL_251;  // 跳转 LABEL_251(收尾/共用分支)
  }
}

