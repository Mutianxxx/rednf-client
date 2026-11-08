// ============================================================
// 【40JP逆向源代码工程】creature/spider_trap.cpp
// 模块: 怪物AI 0x5C —— 蜘蛛/机器人/树精/属性精灵/陷阱莲花/刺王/锤王/玛格纳/阿莫尔
// 来源: work/dump_monster.txt  区块: 0x5C0000-0x5D0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 232
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：本文件【无】—— 0x5C 段全部虚表在 +512 槽
//     继承基类 0x4D71B0（纯 Python 直读 PE 全域扫描证实），行为差异全靠数据与技能函数；
//     0x5B4D90 一类的覆写仅存在于 0x59-0x5B 段（见各文件头）
//   · 0x5C92D0 调 sub_4E4430 = HP 受击处理器（研究 31 Boss 终局族）
//   · AI 状态：this+200 主状态 / vt+560 反应态（研究 15）；陷阱类（章鱼/莲花/草）以
//     this+204/+208 硬直字段作触发节拍
//   · 语音 TAG 组（R_SPIDER_*/WATERSOUL_*/LOTUS_*/R_ECHEVERRA_*/R_GIANT_*）经 sub_4015C0
//     写语音槽，vt+212(sub_499110) 播报（研究 28）；sub_431230=vector 打包 setState 参数
//   · 资源标注：sub_431860/431920=.ani 装载 / sub_4BA9E0=.equ 外观 / sub_47EF20=数据表读数 /
//     sub_4049C0=帧间插值 / sub_406D60=BGM 曲名槽 / sub_493D00=动画变速换锚
//   · 高达梗粒子实证：particle/Rx78_Boom.ptl（ROBOT_EX_01 爆点）与 particle/Ez8_Boom.ptl
//     （ROBOT_EX_02 爆点）+ Monster/Gunner/Ez8/Ez8_Num.img —— ZGM 机动怪三件套
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】蜘蛛·本体与蜘蛛王（Spider / SpiderBoss）（0x5C0220-0x5C1FC0）
// 证据：BORROW_UP/BORROW_DOWN 钻地 + Monster/Spider{,Boss}Ani/BurrowEnd.ani 出土、
//       SPIDER_ROLLING_LOOP 滚冲、R_SPIDER_ATK/DMG + SPIDER_DIE/R_SPIDER 语音（另 PSPIDER/KSPIDER
//       毒/黑蜘蛛变体）、Thread.ani 吐丝 + MissileGero{Center,Left,Right}.ptl 三向吐酸、
//       ThreadSpark.ani 蛛丝火花

// 钻地/出土 AI：BORROW_UP + BORROW_DOWN 播报 + SPIDER_ROLLING_LOOP（76L；
//   this+8616/8617/8637/8638/8652 相位）
// ------------------------------------------------------------
// 0x5C0220 sub_5C0220
// ------------------------------------------------------------
char /*thiscall*/ sub_5C0220(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v6; // eax
  int v7; // edx
  uint32_t *v8; // edx
  int v9; // eax

  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( v6 == 15 )
  {
    sub_460110(this, 1);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BORROW_UP", -1, 0, 0);
  }
  else if ( v6 == 8 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);
  }
  if ( ArgList == 15 )
  {
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 12));
    sub_460110(this, 2);
    ++*(this + 2155);
    *((uint8_t *)this + 8637) = 0;
    *((uint8_t *)this + 8638) = 0;
    sub_698F90((int)(this + 2156), 4000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    v7 = *this;
    *((uint8_t *)this + 8652) = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v7 + 212))(this, "BORROW_DOWN", -1, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      0,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      1,
      0,
      0,
      0,
      0,
      0);
  }
  sub_5BF7E0((uint32_t **)this, ArgList, fArg3, nArg4, nArg5);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 0
     || sub_41A5E0((unsigned int)(this + 1757)) == 1
     || sub_41A5E0((unsigned int)(this + 1757)) == 2) )
  {
    v8 = (uint32_t *)*this;
    *((uint8_t *)this + 8616) = 0;
    *((uint8_t *)this + 8617) = 0;
    LOBYTE(v9) = ((int (/*thiscall*/ *)(uint32_t *, const char *, int, uint32_t, uint32_t))v8[53])(
                   this,
                   "SPIDER_ROLLING_LOOP",
                   9,
                   0,
                   0);
  }
  else
  {
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
    if ( v9 == 14 )
      LOBYTE(v9) = sub_5BF9E0(this);
  }
  return v9;
}



// 蜘蛛语音装载：R_SPIDER_ATK/DMG + SPIDER_DIE + R_SPIDER（this+8616..8620 相位）
// ------------------------------------------------------------
// 0x5C0390 sub_5C0390
// ------------------------------------------------------------
int /*thiscall*/ sub_5C0390(int this)
{
  *(uint8_t *)(this + 8616) = 0;
  *(uint8_t *)(this + 8617) = 0;
  *(uint8_t *)(this + 8618) = 0;
  *(uint32_t *)(this + 8620) = 0;
  sub_4015C0("R_SPIDER_ATK", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_SPIDER_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("SPIDER_DIE", 0xAu);  // 【std::string构造赋值】
  return sub_4015C0("R_SPIDER", 8u);  // 【std::string构造赋值】
}



// 毒蜘蛛语音：R_SPIDER_ATK/DMG + PSPIDER_DIE + R_PSPIDER
// ------------------------------------------------------------
// 0x5C0400 sub_5C0400
// ------------------------------------------------------------
int /*thiscall*/ sub_5C0400(uint8_t *this)
{
  int v2; // eax

  v2 = *(uint32_t *)this;
  *(this + 8616) = 0;
  *((uint32_t *)this + 2151) = 30017;
  (*(void (/*stdcall*/ **)(uint32_t))(v2 + 384))(0);
  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 1);
  *((uint32_t *)this + 2155) = 6;
  *((uint32_t *)this + 2152) = 1;
  sub_4015C0("R_SPIDER_ATK", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_SPIDER_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("PSPIDER_DIE", 0xBu);  // 【std::string构造赋值】
  return sub_4015C0("R_PSPIDER", 9u);  // 【std::string构造赋值】
}



// 黑蜘蛛语音：KSPIDER_ATK + R_KSPIDER_DMG/DIE/R_KSPIDER（this+8616..8764 相位）
// ------------------------------------------------------------
// 0x5C0490 sub_5C0490
// ------------------------------------------------------------
int /*thiscall*/ sub_5C0490(int this)
{
  *(uint8_t *)(this + 8616) = 0;
  *(uint8_t *)(this + 8617) = 0;
  *(uint32_t *)(this + 8640) = 0;
  *(uint32_t *)(this + 8636) = 0;
  *(uint8_t *)(this + 8652) = 0;
  *(uint8_t *)(this + 8653) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8764) = 0;
  sub_4015C0("KSPIDER_ATK", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_KSPIDER_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("KSPIDER_DIE", 0xBu);  // 【std::string构造赋值】
  return sub_4015C0("R_KSPIDER", 9u);  // 【std::string构造赋值】
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5C0520 sub_5C0520
// ------------------------------------------------------------
int /*thiscall*/ sub_5C0520(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  char v5; // al
  int pObj; // esi
  int v7; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-4h]

  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  pObj = nArg2;
  if ( v5 != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0
    && *(this + 154) != 14 )
  {
    memset(&pBuf[1], 0, 12);
    v7 = *(uint32_t *)pObj;
    v10 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v7 + 48))(pObj);
    sub_431230((int)pBuf, &nArg2);
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
    sub_431230((int)pBuf, &nArg2);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);
    v10 = -1;
    sub_5E5260(pBuf);
  }
  return sub_4DB480(pObj, nArg3, nArg4);
}



// 参数打包 AI（89L sub_431230）
// ------------------------------------------------------------
// 0x5C0600 sub_5C0600
// ------------------------------------------------------------
void /*usercall*/ sub_5C0600(int *pDwArg1@<ecx>, int nArg2@<ebx>)
{
  int pObj3; // ecx
  int pObj; // edi
  int v5; // edx
  int v6; // eax
  int v7; // eax
  char v8; // al
  int pObj2; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // eax
  char v13[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  int pObj4; // [esp+18h] [ebp-10h] BYREF
  int v18; // [esp+24h] [ebp-4h]

  pObj3 = pDwArg1[2152];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 612))(pDwArg1[2152], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 136))(
           pDwArg1[2152],
           pDwArg1[2156],
           pDwArg1[2157],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2152] + 112))(pDwArg1[2152], pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);
    }
    else
    {
      pObj = pDwArg1[2152];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2156, pDwArg1 + 2157, v7);
      pObj2 = pDwArg1[2152];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2158]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2152], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 308))(pDwArg1[2152]) != 0 )
    {
      Block = nullptr;
      v15 = 0;
      v16 = 0;
      v18 = 0;
      pObj4 = 4;
      sub_431230((int)v13, &pObj4);
      pObj4 = 0;
      sub_431230((int)v13, &pObj4);
      pObj4 = 1;
      sub_431230((int)v13, &pObj4);
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);
      pObj4 = 200;
      sub_431230((int)v13, &pObj4);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2152] + 560))(pDwArg1[2152], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2152] + 564))(pDwArg1[2152]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2152] + 848))(pDwArg1[2152], 0);
    pDwArg1[2152] = 0;
  }
}



// 参数打包+时钟门 AI（92L；sub_431230+sub_699000）
// ------------------------------------------------------------
// 0x5C0800 sub_5C0800
// ------------------------------------------------------------
void /*usercall*/ sub_5C0800(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int nRand; // eax
  int v5; // eax
  int v6; // edi
  int v7; // edi
  int v8; // eax
  uint8_t v9[4]; // [esp+4h] [ebp-28h] BYREF
  void *Block; // [esp+8h] [ebp-24h]
  int v11; // [esp+Ch] [ebp-20h]
  int v12; // [esp+10h] [ebp-1Ch]
  int v13; // [esp+14h] [ebp-18h] BYREF
  int nRand2; // [esp+18h] [ebp-14h] BYREF
  uint32_t v15[4]; // [esp+1Ch] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 184))(pArg1, nArg2);
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 188))(pArg1);
    v3 = pArg1[1787] - 4;
    v15[0] = 4;
    nRand2 = 4;
    switch ( v3 )
    {
      case 0:
        if ( rand() % 100 >= 80 || (uint8_t)sub_4DA6B0(v15) != 0 )
          goto LABEL_7;
        goto LABEL_6;
      case 1:
      case 5:
LABEL_6:
        sub_4DBDB0(v15, &nRand2);
        goto LABEL_7;
      case 9:
        if ( rand() % 100 >= 40 )
        {
LABEL_7:
          nRand = nRand2;
        }
        else
        {
          if ( (uint8_t)sub_4DA6B0(v15) == 0 )
            v15[0] = rand() % 2;
          nRand = rand() % 2 + 2;
          nRand2 = nRand;
        }
        if ( v15[0] == 4 && nRand == 4 )
          goto LABEL_10;
        v5 = sub_699000((int)(pArg1 + 9)) + 1000;  // 【clock_now(clk)】
        break;
      default:
LABEL_10:
        v5 = sub_699000((int)(pArg1 + 9)) + 300;  // 【clock_now(clk)】
        break;
    }
    v6 = pArg1[1787];
    pArg1[1818] = v5;
    if ( rand() % 100 < SLOWORD(pArg1[v6 + 2092]) )
      v15[0] = 4;
    v7 = pArg1[1787];
    if ( rand() % 100 < SHIWORD(pArg1[v7 + 2092]) )
      nRand2 = 4;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 896))(pArg1, v15[0]);
    sub_5FDFE0(pArg1[1932]);
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1080))(pArg1);
    if ( v15[0] != 4 || nRand2 != 4 )
    {
      Block = nullptr;
      v11 = 0;
      v12 = 0;
      v15[3] = 0;
      v13 = 0;
      sub_431230((int)v9, &v13);
      v13 = 0;
      sub_431230((int)v9, &v13);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 672))(pArg1, 3);
      v13 = sub_58E710(v8);
      sub_431230((int)v9, &v13);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 6, v9, 0, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C0A50 sub_5C0A50
// ------------------------------------------------------------
int /*userpurge*/ sub_5C0A50@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)
{
  int v7; // edi

  v7 = pDwArg1[1639];
  (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 184))(pDwArg1);
  (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 188))(pDwArg1);
  if ( v7 == 14 )
    sub_5C0600(pDwArg1, nArg2);
  if ( ArgList == 14 )
  {
    sub_5BF5F0(pDwArg1, nArg4);
  }
  else if ( ArgList == 15 )
  {
    sub_5BEB90(pDwArg1);
  }
  return sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C0AC0 sub_5C0AC0
// ------------------------------------------------------------
int /*userpurge*/ sub_5C0AC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2152] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
      sub_5C0600(pDwArg1, nArg2);
    pDwArg1[2152] = 0;
  }
  if ( pDwArg3 == pDwArg1 && pDwArg1[2152] != 0 )
  {
    sub_5C0600(pDwArg1, nArg2);
    pDwArg1[2152] = 0;
  }
  return sub_4D9170(pDwArg3);
}



// 出土演出（285L）：Monster/Spider/SpiderAni/BurrowEnd.ani（sub_431860+sub_699000;
//   this+200/8616..8652 相位 —— 蜘蛛钻地循环的出土半段）
// ------------------------------------------------------------
// 0x5C0B20 sub_5C0B20
// ------------------------------------------------------------
void /*thiscall*/ sub_5C0B20(int *this)
{
  int pThis_6DD; // ebx
  int pThis_6DD2; // eax
  int pThis_6DD3; // eax
  int v5; // edi
  int nRand; // edx
  int fld_e1813; // ecx
  int v8; // ebx
  unsigned int v9; // eax
  int fld_e18132; // ecx
  int v11; // ebx
  int64_t v12; // rax
  int v13; // ebx
  int nRand3; // ebx
  int fld_e18133; // ecx
  int v16; // ebx
  int v17; // ebx
  int v18; // edi
  int v19; // eax
  char pThis_21A8; // cl
  int fld_e28; // edx
  int pThis_6DD4; // edi
  uint32_t *fld_e1554; // edi
  int pThis_6DD5; // edi
  uint32_t *fld_e15542; // edi
  int fld_e2162; // edi
  int v27; // eax
  int v28; // edi
  int *v29; // edi
  int v30; // ebx
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // ebx
  int v35; // eax
  int pThis_6DD6; // eax
  int v37; // edi
  int v38; // eax
  uint8_t *pMem; // eax
  uint8_t *pObj; // eax
  int v41; // [esp+44h] [ebp-34h]
  int v42; // [esp+50h] [ebp-28h]
  int nRand2; // [esp+60h] [ebp-18h]
  int v44; // [esp+60h] [ebp-18h]
  double v45; // [esp+64h] [ebp-14h]
  void *Block; // [esp+68h] [ebp-10h]

  sub_5BECF0();
  if ( *((uint8_t *)this + 8617) == 1 )
    (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && ((*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 0
     || (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 1
     || (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 2) )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0 )
      goto LABEL_29;
    if ( *(int *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) >= 1 )
    {
      if ( *((uint8_t *)this + 8616) != 0 )
      {
LABEL_25:
        if ( *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8617) == 0 )
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
            this,
            1,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 2 )
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
        }
        goto LABEL_29;
      }
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 0
        || (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 1 )
      {
        v5 = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) != 1 ? 320 : 160;
        nRand = rand() % 60 + 60;
        fld_e1813 = *(this + 1813);
        nRand2 = nRand;
        if ( fld_e1813 != 0 )
        {
          v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
          v9 = abs32(v8 - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this));
          nRand = nRand2;
        }
        else
        {
          v9 = 0;
        }
        fld_e18132 = *(this + 1813);
        Block = (void *)v9;
        if ( fld_e18132 != 0 )
        {
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 124))(fld_e18132);
          v12 = v11 - (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
          v13 = v12;
          v9 = (unsigned int)Block;
          nRand3 = (HIDWORD(v12) ^ v13) - HIDWORD(v12);
        }
        else
        {
          nRand3 = nRand;
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, unsigned int, unsigned int, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          v9,
          v9,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, nRand3, nRand3, 0, 0, 0);
        fld_e18133 = *(this + 1813);
        v16 = 2;
        if ( fld_e18133 != 0 )
        {
          v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18133 + 124))(fld_e18133);
          v16 = (v17 > (*(int (/*thiscall*/ **)(int *))(*this + 124))(this)) + 2;
        }
        sub_4A0550(v5);
        v42 = v16;
      }
      else
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) != 2 )
          goto LABEL_24;
        pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
        pThis_6DD2 = sub_41A5E0((unsigned int)(this + 1757));
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          dword_72FD68[pThis_6DD2],
          dword_72FD68[pThis_6DD],
          0,
          0,
          0);
        pThis_6DD3 = sub_41A5E0((unsigned int)(this + 1757));
        sub_4A0550(dword_72FD70[pThis_6DD3]);
        v42 = 4;
      }
      v18 = *this;
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, v42);
      (*(void (/*thiscall*/ **)(int *, int))(v18 + 896))(this, v19);
    }
LABEL_24:
    if ( *((uint8_t *)this + 8616) != 0 )
      goto LABEL_25;
LABEL_29:
    pThis_21A8 = *((uint8_t *)this + 8616);
    if ( pThis_21A8 != 0 && *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8617) == 0 )
      *((uint8_t *)this + 8617) = 1;
    fld_e28 = *(this + 28);
    if ( *(float *)(fld_e28 + 24) > 0.0 && pThis_21A8 == 0 )
      *((uint8_t *)this + 8616) = 1;
    if ( *((uint8_t *)this + 8616) != 0 )
    {
      if ( *(float *)(fld_e28 + 24) > 0.0 )
      {
        pThis_6DD4 = sub_41A5E0((unsigned int)(this + 1757));
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > dword_72FD78[pThis_6DD4] )
        {
          fld_e1554 = (uint32_t *)(*(this + 1554) + 4);
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != *fld_e1554 )
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
            sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
          }
        }
      }
      if ( *((uint8_t *)this + 8616) != 0 && *(float *)(*(this + 28) + 24) < 0.0 )
      {
        pThis_6DD5 = sub_41A5E0((unsigned int)(this + 1757));
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < dword_72FD80[pThis_6DD5] )
        {
          fld_e15542 = (uint32_t *)(*(this + 1554) + 8);
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != *fld_e15542 )
          {
            sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));
          }
        }
      }
    }
    return;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14 )
  {
    if ( *((uint8_t *)this + 8618) != 0 )
      sub_5BF4E0(this);
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 15 )
    {
      fld_e2162 = *(this + 2162);
      if ( sub_699000((int)(this + 2156)) >= fld_e2162 )  // 【clock_now(clk)】
      {
        v27 = sub_42FCB0(228);
        v28 = 0;
        if ( v27 != 0 )
          v28 = sub_431860(v27, "Monster/Spider/SpiderAni/BurrowEnd.ani", 1);
        if ( v28 != 0 )
        {
          if ( sub_44B6C0(284) != 0 )
            v29 = (int *)sub_44E1F0(v28, 1);
          else
            v29 = nullptr;
          sub_45FE80(*(this + 29), (int)v29, 2, 0, (int)v29, (int)this, 0);
          v30 = *v29;
          v31 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
          v32 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v31);
          v33 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v32);
          (*(void (/*thiscall*/ **)(int *, int))(v30 + 112))(v29, v33);
          v34 = *v29;
          v35 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
          (*(void (/*thiscall*/ **)(int *, int))(v34 + 144))(v29, v35);
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          30,
          30,
          0,
          0,
          0);
        pThis_6DD6 = sub_41A5E0((unsigned int)(this + 1757));
        sub_4A0550(dword_72FD70[pThis_6DD6]);
        v37 = *this;
        v38 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);
        (*(void (/*thiscall*/ **)(int *, int))(v37 + 896))(this, v38);
      }
      if ( *((uint8_t *)this + 8652) == 0 && sub_699000((int)(this + 2156)) > 2000 )  // 【clock_now(clk)】
      {
        v44 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*this + 740))(this) * 0.30000001);
        pMem = operator new(0x80u);
        if ( pMem != nullptr )
        {
          *(float *)&v41 = (float)v44;
          pObj = sub_4D6810(pMem, v41, 3000, 1, 1);
        }
        else
        {
          pObj = nullptr;
        }
        (*(void (/*thiscall*/ **)(uint8_t *, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
          pObj,
          this,
          this,
          0,
          0,
          0,
          -1);
        *((uint8_t *)this + 8652) = 1;
      }
    }
  }
  else if ( *(this + 2155) == 0 )
  {
    v45 = (double)(*(int (/*thiscall*/ **)(int *))(*this + 740))(this) * 0.5;
    if ( (double)(*(int (/*thiscall*/ **)(int *))(*this + 736))(this) <= v45 )
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 15, 0, 0, 0);
  }
}


// 吐丝/吐酸：Thread.ani 蛛丝 + PassiveObject/Common/Particle/MissileGero{Center,Left,
//   Right}.ptl 三向喷吐（32L）
// ------------------------------------------------------------
// 0x5C11B0 sub_5C11B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C11B0(uint32_t *this)
{
  uint32_t *pThis_88C; // esi
  int i; // edi
  int result; // eax

  *(this + 2155) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Common/Particle/MissileGeroCenter.ptl");
  *(this + 2156) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Common/Particle/MissileGeroLeft.ptl");
  *(this + 2157) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Common/Particle/MissileGeroRight.ptl");
  pThis_88C = this + 2188;
  for ( i = 3; i != 0; --i )
  {
    if ( sub_42FCB0(228) != 0 )
      result = sub_431860((char)"Monster/Spider/SpiderBossAni/Thread.ani", 1);
    else
      result = 0;
    *pThis_88C++ = result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C1270 sub_5C1270
// ------------------------------------------------------------
int /*thiscall*/ sub_5C1270(void ***this)
{
  void ***pThis_88C; // esi
  int i; // ebx
  void **v3; // edi
  int result; // eax

  pThis_88C = this + 2188;
  for ( i = 3; i != 0; --i )
  {
    v3 = *pThis_88C;
    if ( *pThis_88C != nullptr )
    {
      sub_42AF90(*pThis_88C);
      result = sub_657740(v3, 228);
    }
    *pThis_88C++ = nullptr;
  }
  return result;
}



// 蜘蛛王出土（130L）：Monster/Spider/SpiderBossAni/BurrowEnd.ani（sub_431860+sub_699000）
// ------------------------------------------------------------
// 0x5C12B0 sub_5C12B0
// ------------------------------------------------------------
int /*usercall*/ sub_5C12B0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // ecx
  int result; // eax
  int v5; // edi
  int v6; // edi
  int v7; // eax
  int pObj; // ecx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int *v16; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // [esp-1Ch] [ebp-34h]
  int v25; // [esp-14h] [ebp-2Ch]
  int v27; // [esp+8h] [ebp-10h]

  if ( pArg1[2160] != 0 || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1) < 600 )
  {
    result = pArg1[2160];
    switch ( result )
    {
      case 1:
        v5 = pArg1[2178];
        result = sub_699000((int)(pArg1 + 2172));  // 【clock_now(clk)】
        if ( result >= v5 )
        {
          v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg2);
          v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);
          pObj = pArg1[1813];
          v9 = v7;
          if ( pObj != 0 )
          {
            v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
            v9 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);
            v27 = *pArg1;
            v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(v27 + 108))(pArg1, v6, v9, v10);
          }
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 17, 0, 0);
          v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
          return sub_4E4A50(pArg1, 48012, 2, v6, v9, 0, v11, 0, 0, 0);
        }
        break;
      case 2:
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
        if ( result <= 0 )
        {
          v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);
          sub_424120(*(uint32_t **)(v12 + 132), 2, 450);
          v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
          v14 = sub_491C70(v13, 1);
          sub_493A60(v13, v14);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
            pArg1,
            0,
            200,
            200,
            0,
            0,
            0);
          sub_4A0550(150);
          if ( sub_42FCB0(228) != 0 )
            v15 = sub_431860((char)"Monster/Spider/SpiderBossAni/BurrowEnd.ani", 1);
          else
            v15 = 0;
          if ( v15 != 0 )
          {
            if ( sub_44B6C0(284) != 0 )
              v16 = (int *)sub_44E1F0(v15, 1);
            else
              v16 = nullptr;
            sub_45FE80(pArg1[29], (int)v16, 2, 0, (int)v16, (int)pArg1, 0);
            v17 = *v16;
            v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
            v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v18);
            v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v19);
            (*(void (/*thiscall*/ **)(int *, int))(v17 + 112))(v16, v20);
            v21 = *v16;
            v22 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
            (*(void (/*thiscall*/ **)(int *, int))(v21 + 144))(v16, v22);
          }
          v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
          v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);
          v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
          result = sub_4E4A50(pArg1, 30201, 0, v23, v24, 0, v25, 0, 0, 0);
          pArg1[2160] = 3;
        }
        break;
      case 3:
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
        if ( *(uint8_t *)(result + 170) != 0 )
        {
          result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
          pArg1[2160] = 4;
        }
        break;
      default:
        break;
    }
  }
  else
  {
    *((uint8_t *)pArg1 + 8701) = 0;
    *((uint8_t *)pArg1 + 8702) = 0;
    sub_698F90((int)(pArg1 + 2172), 2000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    v3 = pArg1[28];
    pArg1[2160] = 1;
    pArg1[2186] = *(uint32_t *)(v3 + 36);
    sub_495890(2, 0);
    result = pArg1[28];
    *(uint32_t *)(result + 36) = 0;
  }
  return result;
}


// 蜘蛛王出土 2（83L；this+200 相位）
// ------------------------------------------------------------
// 0x5C15A0 sub_5C15A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C15A0(int *this)
{
  int pThis_875; // ecx
  int v3; // edi
  int v4; // ebx
  char *v5; // eax
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // edi
  int v14; // eax
  uint32_t *fld_e1554; // edi
  int result; // eax

  pThis_875 = (int)(this + 2165);
  v3 = *(uint32_t *)(pThis_875 + 24);
  if ( sub_699000(pThis_875) >= v3 )  // 【clock_now(clk)】
  {
    if ( sub_42FCB0(228) != 0 )
      v4 = sub_431860((char)"Monster/Spider/SpiderBossAni/BurrowEnd.ani", 1);
    else
      v4 = 0;
    if ( v4 != 0 )
    {
      v5 = (char *)sub_44B6C0(284);
      v6 = v5;
      if ( v5 != nullptr )
      {
        sub_44E0D0(v5, v4, 1);
        *(uint32_t *)v6 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v6 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v6, 2, 0, (int)v6, (int)this, 0);
      v7 = *(uint32_t *)v6;
      v8 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v8);
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v9);
      (*(void (/*thiscall*/ **)(char *, int))(v7 + 112))(v6, v10);
      v11 = *(uint32_t *)v6;
      v12 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v11 + 144))(v6, v12);
    }
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      0,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
    sub_4A0550(700);
    v13 = *this;
    v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);
    (*(void (/*thiscall*/ **)(int *, int))(v13 + 896))(this, v14);
  }
  fld_e1554 = (uint32_t *)(*(this + 1554) + 12);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
  if ( result != *fld_e1554 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( result <= 0 )
    {
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 12));
    }
  }
  return result;
}



// 滚冲/出土复合（231L）：SpiderAni/BurrowEnd.ani + this+200/8632..8744 相位字段
// ------------------------------------------------------------
// 0x5C1750 sub_5C1750
// ------------------------------------------------------------
char /*thiscall*/ sub_5C1750(int this)
{
  int fld_21BC; // eax
  int fld_2224; // ebx
  int v4; // eax
  int fld_21B8; // eax
  int v6; // edi
  int v7; // ebx
  int nRand; // eax
  int v9; // ebx
  int nRand2; // eax
  int v11; // eax
  int v12; // edi
  int v13; // ebx
  int pThis_98; // eax
  int pThis_80; // eax
  int pThis_178; // eax
  int pThis_982; // eax
  bool fld_21B82; // zf
  int fld_22242; // edi
  int pThis_78; // edi
  int pThis_7C; // eax
  int fld_1C54; // ecx
  int fld_1C542; // ebx
  int pThis_802; // eax
  int pThis_983; // eax
  int pThis_50; // eax
  void *pThis_C8; // eax
  int fld_21BC2; // edi
  int *v29; // edi
  int fld_74; // ecx
  int v31; // ebx
  int pThis_803; // eax
  int pThis_7C2; // eax
  int pThis_782; // eax
  int v35; // ebx
  int pThis_984; // eax
  int v38; // [esp+0h] [ebp-24h]
  int pObj; // [esp+Ch] [ebp-18h]
  int v40; // [esp+Ch] [ebp-18h]
  int v41; // [esp+10h] [ebp-14h] BYREF
  int v42; // [esp+14h] [ebp-10h] BYREF
  int v43; // [esp+20h] [ebp-4h]

  if ( *(uint32_t *)(this + 8636) == 1 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this) >= 600 )
  {
    *(uint8_t *)(this + 8701) = 0;
    *(uint8_t *)(this + 8702) = 0;
    sub_698F90(this + 8688, 30000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(uint32_t *)(this + 8744) = *(uint32_t *)(*(uint32_t *)(this + 112) + 36);
    sub_495890((int *)this, 2, 0);
    *(uint32_t *)(*(uint32_t *)(this + 112) + 36) = 0;
    *(uint32_t *)(this + 8636) = 2;
    *(uint32_t *)(this + 8632) = sub_5BF430(this);
    if ( dword_9A05D4 > 2 )
      *(uint32_t *)(this + 8632) = 0;
    *(uint8_t *)(this + 8729) = 0;
    *(uint8_t *)(this + 8730) = 0;
    LOBYTE(fld_21BC) = sub_698F90(this + 8716, 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  else
  {
    fld_21BC = *(uint32_t *)(this + 8636);
    switch ( fld_21BC )
    {
      case 2:
        LOBYTE(fld_21BC) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
        if ( (uint8_t)fld_21BC != 0 )
        {
          fld_2224 = *(uint32_t *)(this + 8740);
          fld_21BC = sub_699000(this + 8716);  // 【clock_now(clk)】
          if ( fld_21BC >= fld_2224 )
          {
            *(uint8_t *)(this + 8729) = 0;
            *(uint8_t *)(this + 8730) = 0;
            sub_698F90(this + 8716, 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
            if ( *(int *)(this + 8632) > 0 )
            {
              v4 = sub_456390(0);
              fld_21B8 = sub_5AE3C0(*(uint32_t *)(this + 8632) % v4);
              pObj = fld_21B8;
              if ( fld_21B8 != 0 )
              {
                v6 = *(uint32_t *)this;
                v7 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_21B8 + 124))(fld_21B8, 160, 1, 1);
                nRand = rand();
                v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, nRand % 50 + v7);
                nRand2 = rand();
                if ( (*(uint8_t (/*thiscall*/ **)(int, int *, int *, int))(v6 + 140))(
                       this,
                       &v41,
                       &v42,
                       nRand2 % 50 + v9) != 0 )
                {
                  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
                  v12 = *(uint32_t *)this;
                  v13 = *(uint32_t *)(*(uint32_t *)(v11 + 108) + 112);
                  pThis_98 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(
                          this,
                          2,
                          0,
                          0,
                          0xFFFF,
                          0,
                          0,
                          0,
                          0);
                  pThis_80 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 128))(this, pThis_98);
                  pThis_178 = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)this + 376))(
                          this,
                          v13,
                          v41,
                          v42,
                          pThis_80);
                  (*(void (/*thiscall*/ **)(int, int, int))(v12 + 592))(this, 420, pThis_178);
                  pThis_982 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
                  sub_4E4A50(v12, this, 48012, 1, v41, v42, 0, pThis_982, 0, 0, 0);
                }
              }
            }
            fld_21BC = *(uint32_t *)(this + 8632) - 1;
            fld_21B82 = *(uint32_t *)(this + 8632) == 1;
            *(uint32_t *)(this + 8632) = fld_21BC;
            if ( fld_21BC < 0 || fld_21B82 )
            {
              *(uint8_t *)(this + 8729) = 0;
              *(uint8_t *)(this + 8730) = 0;
              LOBYTE(fld_21BC) = sub_698F90(this + 8716, 3000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
              *(uint32_t *)(this + 8636) = 3;
            }
          }
        }
        break;
      case 3:
        fld_22242 = *(uint32_t *)(this + 8740);
        fld_21BC = sub_699000(this + 8716);  // 【clock_now(clk)】
        if ( fld_21BC >= fld_22242 )
        {
          pThis_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
          pThis_7C = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this);
          fld_1C54 = *(uint32_t *)(this + 7252);
          fld_1C542 = pThis_7C;
          if ( fld_1C54 != 0 )
          {
            pThis_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_1C54 + 120))(fld_1C54);
            fld_1C542 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 124))(*(uint32_t *)(this + 7252));
            v40 = *(uint32_t *)this;
            pThis_802 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
            (*(void (/*thiscall*/ **)(int, int, int, int))(v40 + 108))(this, pThis_78, fld_1C542, pThis_802);
          }
          pThis_983 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
          sub_4E4A50(pThis_78, this, 48012, 2, pThis_78, fld_1C542, 0, pThis_983, 0, 0, 0);
          LOBYTE(fld_21BC) = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(
                         this,
                         19,
                         0,
                         0,
                         0);
        }
        break;
      case 4:
        fld_21BC = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
        if ( fld_21BC <= 0 )
        {
          pThis_50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 80))(this);
          sub_424120(*(uint32_t **)(pThis_50 + 132), 2, 300);
          pThis_C8 = (void *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 200))(this, 1);
          sub_4AECE0(pThis_C8, v38);
          fld_21BC2 = 0;
          (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
            this,
            0,
            200,
            200,
            0,
            0);
          sub_4A0550(*(float **)(this + 112), 150);
          fld_21BC = sub_42FCB0(228);
          v43 = 0;
          if ( fld_21BC != 0 )
          {
            fld_21BC = sub_431860((char)"Monster/Spider/SpiderAni/BurrowEnd.ani", 1);
            fld_21BC2 = fld_21BC;
          }
          v43 = -1;
          if ( fld_21BC2 != 0 )
          {
            v43 = 1;
            if ( sub_44B6C0(284) != 0 )
              v29 = (int *)sub_44E1F0(fld_21BC2, 1);
            else
              v29 = nullptr;
            fld_74 = *(uint32_t *)(this + 116);
            v43 = -1;
            sub_45FE80(fld_74, (int)v29, 2, 0, (int)v29, this, 0);
            v31 = *v29;
            pThis_803 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
            pThis_7C2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_803);
            pThis_782 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C2);
            (*(void (/*thiscall*/ **)(int *, int))(v31 + 112))(v29, pThis_782);
            v35 = *v29;
            pThis_984 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
            LOBYTE(fld_21BC) = (*(int (/*thiscall*/ **)(int *, int))(v35 + 144))(v29, pThis_984);
          }
          *(uint32_t *)(this + 8636) = 5;
        }
        break;
      case 5:
        fld_21BC = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
        if ( *(uint8_t *)(fld_21BC + 170) != 0 )
        {
          LOBYTE(fld_21BC) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(
                         this,
                         0,
                         0,
                         0,
                         0);
          *(uint32_t *)(this + 8636) = 6;
        }
        break;
      default:
        break;
    }
  }
  return fld_21BC;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5C1C00 sub_5C1C00
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_5C1C00(uint32_t **this, char ArgList, int nArg3, int nArg4)
{
  sub_4A4EA0(ArgList, nArg3);
  *this = &CNYoungSpider::`vftable';
  sub_5BE7C0(this);
  sub_4D50A0(**(this + 1554));
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C1C70 sub_5C1C70
// ------------------------------------------------------------
void */*thiscall*/ sub_5C1C70(void *Block, char pszArg2)
{
  sub_5C1CA0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C1CA0 sub_5C1CA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C1CA0(uint32_t *this)
{
  *this = &CNYoungSpider::`vftable';
  return sub_4A50F0();
}



// 蛛丝火花：Monster/Spider/SpiderBossAni/ThreadSpark.ani（100L；sub_431860）
// ------------------------------------------------------------
// 0x5C1CB0 sub_5C1CB0
// ------------------------------------------------------------
void /*usercall*/ sub_5C1CB0(int *pDwArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // eax
  int v4; // edi
  int *v5; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax

  sub_5BECF0((int)pDwArg1);
  if ( *((uint8_t *)pDwArg1 + 8653) == 1 )
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 9);
  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 6 )
  {
    if ( *((uint8_t *)pDwArg1 + 8616) != 0 && *(int *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148) >= 4 )
    {
      v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
      sub_424120(*(uint32_t **)(v3 + 132), 2, 450);
      *((uint8_t *)pDwArg1 + 8616) = 0;
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 908))(pDwArg1) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 908))(pDwArg1) == 1 )
      {
        sub_5BF2D0(pDwArg1);
      }
      else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 908))(pDwArg1) == 2 )
      {
        sub_5BFE90(pDwArg1);
      }
      else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 908))(pDwArg1) == 3 )
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) <= 0 && *((uint8_t *)pDwArg1 + 8748) == 1 )
        {
          v4 = 0;
          if ( sub_42FCB0(228) != 0 )
            v4 = sub_431860((char)"Monster/Spider/SpiderBossAni/ThreadSpark.ani", 1);
          if ( v4 != 0 )
          {
            if ( sub_44B6C0(284) != 0 )
              v5 = (int *)sub_44E1F0(v4, 1);
            else
              v5 = nullptr;
            v6 = *v5;
            v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
            (*(void (/*thiscall*/ **)(int *, int))(v6 + 144))(v5, v7);
            sub_45FE80(pDwArg1[29], (int)v5, 2, 0, (int)v5, (int)pDwArg1, 0);
            v8 = *v5;
            v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
            v10 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v9);
            v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v10);
            (*(void (/*thiscall*/ **)(int *, int))(v8 + 112))(v5, v11);
            v12 = *v5;
            v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
            (*(void (/*thiscall*/ **)(int *, int))(v12 + 144))(v5, v13);
          }
          *((uint8_t *)pDwArg1 + 8748) = 0;
        }
        if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 170) != 0
          && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 568))(pDwArg1) != 18 )
        {
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 18, 0, 0, 0);
        }
      }
    }
    else
    {
      sub_5BF210(pDwArg1);
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 15 )
  {
    sub_5C15A0(pDwArg1);
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 16 || (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 17 )
  {
    sub_5C12B0(pDwArg1, nArg2);
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 18 || (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 19 )
  {
    if ( pDwArg1[2159] != 0 )
      sub_5C1750(pDwArg1);
    else
      sub_5BF3D0(pDwArg1);
  }
}



// ============================================================
// 【分区 2】机器人·自爆与弹簧（高达梗粒子）（0x5C1FC0-0x5C3A30）
// 证据：ROBOT_WORK_LOOP/SPRING_UNWINDS_LOOP/EX_SET/EX_READY/MOVE_LOOP/CLICK_LOOP、
//       ROBOT_EX_01 + PassiveObject/Common/Animation/EarthQuake.ani + particle/Rx78_Boom.ptl、
//       ROBOT_EX_02 + particle/Ez8_Boom.ptl、BOMB_READY_LOOP、Particle/{Exs_Bullet,EXS_Boom}.ptl

// 子类扩展字段复位（this+8600..8616）
// ------------------------------------------------------------
// 0x5C1FC0 sub_5C1FC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C1FC0(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8612) = 0xFFFF;
  *(uint8_t *)(this + 8616) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C1FF0 sub_5C1FF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C1FF0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2152)(uint32_t, int); // ecx
  int result; // eax

  fld_e2152 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2152);
  if ( fld_e2152 != nullptr )
    result = (**fld_e2152)(fld_e2152, 1);
  *(this + 2152) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C2010 sub_5C2010
// ------------------------------------------------------------
int /*stdcall*/ sub_5C2010(int nArg1)
{
  int result; // eax

  result = nArg1;
  if ( nArg1 != 24 )
    return sub_4DBA80(nArg1);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C2030 sub_5C2030
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2030(uint32_t *this)
{
  int result; // eax

  result = sub_4D9760();
  *(this + 1812) = 0;
  return result;
}



// 待机循环：ROBOT_WORK_LOOP + SPRING_UNWINDS_LOOP 播报（机器人待机/弹簧松脱, 47L）
// ------------------------------------------------------------
// 0x5C2050 sub_5C2050
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2050(int *this)
{
  int result; // eax

  sub_4E0120();
  result = *(this + 1787);
  if ( result != 0 )
  {
    if ( result == 5 )
    {
      result = *(this + 1813);
      if ( result == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 23);
    }
    else
    {
      if ( result == 21 )
        return result;
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 23);
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 23);
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "ROBOT_WORK_LOOP",
      10099,
      0,
      0);
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "SPRING_UNWINDS_LOOP",
             10101,
             0,
             0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C20F0 sub_5C20F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C20F0(uint32_t *this)
{
  int result; // eax

  if ( *(this + 2153) == 0xFFFF )
    return sub_4DA1D0();
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C2110 sub_5C2110
// ------------------------------------------------------------
int /*userpurge*/ sub_5C2110@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int *pDwArg3, uint32_t *uArg4, int nArg5)
{
  int result; // eax
  int v7; // eax

  switch ( pArg1[1787] )
  {
    case 5:
      return sub_4DBDB0(pDwArg3, uArg4);
    case 0x15:
      v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 184))(pArg1, nArg2);
      *pDwArg3 = sub_432E50(v7);
      *uArg4 = 3 - (rand() % 2 != 0);
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 144))(pArg1, *pDwArg3);
    case 0x17:
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
      *pDwArg3 = result;
      *uArg4 = 4;
      break;
    default:
      return sub_4DF2D0(pDwArg3, uArg4, nArg5);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C21D0 sub_5C21D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C21D0(uint32_t *this)
{
  if ( *(this + 2153) != 0xFFFF )
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 112))(this, -10000, -10000, 0);
  return sub_4D54E0(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C2200 sub_5C2200
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2200(uint32_t *this, uint32_t *pArg2)
{
  if ( pArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10099);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10101);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10100);
    return sub_4D9170(pArg2);
  }
  else
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 33) != 0
      && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 52))(pArg2) == *(this + 2153) )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1256))(this);
    }
    return sub_4D9170(pArg2);
  }
}



// 数据表读数 + RTTI cast（sub_47EF20 —— 目标数值读取, 研究 17/20）
// ------------------------------------------------------------
// 0x5C2280 sub_5C2280
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2280(int *this, int nArg2, int nArg3)
{
  int result; // eax
  int pObj; // esi
  int v6; // ebx
  uint64_t v7; // rax
  int v8; // ebx
  uint64_t v9; // rax
  char *v10; // ebx
  int v11; // eax
  int v12; // [esp+14h] [ebp+Ch]
  int v13; // [esp+14h] [ebp+Ch]
  int v14; // [esp+14h] [ebp+Ch]

  sub_4DD8F0(this, nArg2, nArg3);
  result = __RTDynamicCast(
             *(this + 2088),
             0,
             &IRDActiveObject `RTTI Type Descriptor',
             &CNGunner `RTTI Type Descriptor',
             0);
  pObj = result;
  if ( result != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 672))(result, 3);
    v12 = sub_41A5E0(v6 + 60);
    v7 = (uint64_t)((double)v12 * COERCE_FLOAT(sub_41A5E0(v6 + 74)));
    sub_41A590((unsigned int)(this + 184), SHIDWORD(v7), v7);
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
    v13 = sub_41A5E0(v8 + 116);
    v9 = (uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(v8 + 130)));
    sub_41A590((unsigned int)(this + 198), SHIDWORD(v9), v9);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    v10 = (char *)sub_47E720(2, 27);
    v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 27);
    *(this + 2150) = sub_47EF20(2, v14, -1, -1, 11);
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
    result = sub_47EFD0(v10, COERCE_FLOAT(1), v14, v11, v11, 0);
    *(this + 2151) = result;
  }
  return result;
}



// 布设状态机：ROBOT_EX_SET + ROBOT_EX_READY + ROBOT_MOVE_LOOP 三段播报（60L）
// ------------------------------------------------------------
// 0x5C23A0 sub_5C23A0
// ------------------------------------------------------------
int **/*thiscall*/ sub_5C23A0(int **this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int **result; // eax
  int fld_e1639; // eax

  if ( ArgList == 14 )
  {
    result = *(int ***)(LODWORD(fArg3) + 4);
    *(this + 2153) = *result;
  }
  else
  {
    fld_e1639 = (int)*(this + 1639);
    if ( fld_e1639 == 8 )
    {
      ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[52])(this, **(this + 1554));
    }
    else if ( fld_e1639 == 0 )
    {
      ((void (/*thiscall*/ *)(int **, int))(*this)[54])(this, 10100);
    }
    result = (int **)sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
    if ( ArgList == 8 )
    {
      ((void (/*thiscall*/ *)(int **, uint32_t, uint32_t, int, int))(*this)[222])(this, 0, 0, 1000, 1000);
      sub_4926A0(**(this + 1554));
      ((void (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
        this,
        1000,
        **(this + 1554),
        0,
        0,
        0,
        0);
      ((void (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "ROBOT_EX_SET", -1, 0, 0);
      return (int **)((int (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                       this,
                       "ROBOT_EX_READY",
                       -1,
                       0,
                       0);
    }
    else if ( ArgList == 0 )
    {
      return (int **)((int (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(
                       this,
                       "ROBOT_MOVE_LOOP",
                       10100,
                       0,
                       0);
    }
  }
  return result;
}



// 自爆一型（125L）：ROBOT_EX_01 播报 + PassiveObject/Common/Animation/EarthQuake.ani
//   震地 + particle/Rx78_Boom.ptl 爆点（★高达梗: Rx78）
// ------------------------------------------------------------
// 0x5C24B0 sub_5C24B0
// ------------------------------------------------------------
void /*usercall*/ sub_5C24B0(int *pDwArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int v4; // edx
  int v5; // ebx
  int v6; // ebx
  char *pObj; // edi
  void *v8; // eax
  int v9; // eax
  int v10; // eax
  int *v11; // eax
  int v12; // edx
  void *v13; // ecx
  int v14; // edx
  int v15; // eax
  char v16[4]; // [esp+4h] [ebp-3Ch] BYREF
  void *v17; // [esp+8h] [ebp-38h]
  int v18; // [esp+Ch] [ebp-34h]
  int v19; // [esp+10h] [ebp-30h]
  char v20[4]; // [esp+14h] [ebp-2Ch] BYREF
  void *Block; // [esp+18h] [ebp-28h]
  int v22; // [esp+1Ch] [ebp-24h]
  int v23; // [esp+20h] [ebp-20h]
  void *pMem; // [esp+24h] [ebp-1Ch]
  char *pObj2; // [esp+28h] [ebp-18h]
  int v26; // [esp+2Ch] [ebp-14h]
  int v27; // [esp+30h] [ebp-10h]
  int v28; // [esp+3Ch] [ebp-4h]

  if ( *((uint8_t *)pDwArg1 + 8616) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, "ROBOT_EX_01", -1, 0, 0, nArg2);
    v27 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);
    v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
    v4 = *pDwArg1;
    v26 = v3;
    v5 = (*(int (/*thiscall*/ **)(int *))(v4 + 128))(pDwArg1);
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )
    {
      v27 += (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) != 0 ? 65 : -65;
      v6 = v5 + 20;
    }
    else
    {
      v6 = v5 + 30;
    }
    pObj = (char *)sub_44B6C0(284);
    pObj2 = pObj;
    v28 = 0;
    if ( pObj != nullptr )
    {
      v8 = (void *)sub_42FCB0(228);
      pMem = v8;
      LOBYTE(v28) = 1;
      if ( v8 != nullptr )
        v9 = sub_431860((int)v8, "PassiveObject/Common/Animation/EarthQuake.ani", 1);
      else
        v9 = 0;
      LOBYTE(v28) = 0;
      sub_44E0D0(pObj, v9, 1);
      *(uint32_t *)pObj = &CNRDPooledObject::`vftable';
    }
    else
    {
      pObj = nullptr;
    }
    v10 = *(uint32_t *)pObj;
    v28 = -1;
    (*(void (/*thiscall*/ **)(char *, int))(v10 + 72))(pObj, 2);
    sub_45FE80(pDwArg1[29], (int)pObj, 2, 0, (int)pObj, (int)pDwArg1, 0);
    (*(void (/*thiscall*/ **)(char *, int, int, int))(*(uint32_t *)pObj + 112))(pObj, v27, v26 + 1, v6);
    if ( pDwArg1[2152] == 0 )
    {
      pMem = operator new(0x12Cu);
      v28 = 2;
      if ( pMem != nullptr )
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          v11 = (int *)sub_4C3640(pDwArg1 + 91, "particle/Rx78_Boom.ptl", pDwArg1);
        else
          v11 = (int *)sub_4C3640(pDwArg1[91], "particle/Rx78_Boom.ptl", pDwArg1);
      }
      else
      {
        v11 = nullptr;
      }
      pDwArg1[2152] = (int)v11;
      v12 = *v11;
      v28 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(v12 + 12))(v11, 0);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2152] + 40))(pDwArg1[2152], v27, v26, v6);
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pDwArg1[2152] + 92))(pDwArg1[2152], v20);
      v13 = (void *)pDwArg1[29];
      v28 = 3;
      sub_4600B0(v13, 2, 0, (int)v20);
      v28 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v22 = 0;
      v23 = 0;
    }
    v14 = *pDwArg1;
    *((uint8_t *)pDwArg1 + 8616) = 1;
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(v14 + 308))(pDwArg1) != 0 )
    {
      v15 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
      pDwArg1[2153] = sub_4E4A50(pDwArg1, 40002, pDwArg1[2151], v27, v26, v6, v15, 0, 0, 0);
      v17 = nullptr;
      v18 = 0;
      v19 = 0;
      v28 = 4;
      sub_431230((int)v16, pDwArg1 + 2153);
      (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 14, v16, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*pDwArg1 + 108))(pDwArg1, -10000, -10000, 0);
      if ( v17 != nullptr )
        j__free(v17);
    }
  }
}


// 时钟门 AI（sub_699000; this+8600/8612）
// ------------------------------------------------------------
// 0x5C2760 sub_5C2760
// ------------------------------------------------------------
void /*thiscall*/ sub_5C2760(int this)
{
  int fld_2198; // ebx
  int pThis_24; // eax
  uint8_t v4; // al
  int fld_78; // eax

  sub_4E1780((uint32_t *)this);
  fld_2198 = *(uint32_t *)(this + 8600) - sub_699000(this + 36);  // 【clock_now(clk)】
  if ( *(uint32_t *)(this + 8612) == 0xFFFF )
  {
    if ( fld_2198 <= 1500 && *(uint32_t *)(this + 120) != 0 )
    {
      pThis_24 = sub_699000(this + 36);  // 【clock_now(clk)】
      v4 = sub_42B420(50, 255, pThis_24, 250);
      sub_491690(1, 2, 1, -16776961, (v4 << 24) | 0xFFFFFF, 1);
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
    {
      fld_78 = *(uint32_t *)(this + 120);
      if ( fld_78 != 0 && *(uint8_t *)(fld_78 + 170) != 0 )
        sub_5C24B0((int *)this, fld_2198);
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 8 && fld_2198 <= 0 && *(uint8_t *)(this + 264) == 0 )
      sub_5C24B0((int *)this, fld_2198);
  }
}



// 子类扩展字段复位（this+8600..8630）
// ------------------------------------------------------------
// 0x5C2830 sub_5C2830
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2830(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8624) = 0xFFFF;
  *(uint8_t *)(this + 8628) = 0;
  *(uint8_t *)(this + 8629) = 0;
  *(uint8_t *)(this + 8630) = 0;
  return 0;
}



// 号码牌资源：Monster/Gunner/Ez8/Ez8_Num.img（★高达梗: Ez8 机体编号图, 18L）
// ------------------------------------------------------------
// 0x5C2870 sub_5C2870
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2870(int this)
{
  int result; // eax

  *(uint8_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 4;
  result = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
             dword_8F84B8,
             "Monster/Gunner/Ez8/Ez8_Num.img");
  *(uint32_t *)(this + 8608) = result;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C28A0 sub_5C28A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C28A0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2155)(uint32_t, int); // ecx
  int result; // eax

  fld_e2155 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2155);
  if ( fld_e2155 != nullptr )
    result = (**fld_e2155)(fld_e2155, 1);
  *(this + 2155) = 0;
  return result;
}



// AI 字段访问（this+8630）
// ------------------------------------------------------------
// 0x5C28C0 sub_5C28C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C28C0(uint8_t *this, uint8_t *uArg2)
{
  if ( this == uArg2 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 10);
    if ( *(this + 8630) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 9);
      return sub_4D9170(uArg2);
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)uArg2 + 40))(uArg2, 33) != 0
         && (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)uArg2 + 52))(uArg2) == *((uint32_t *)this + 2156) )
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1256))(this);
  }
  return sub_4D9170(uArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C2930 sub_5C2930
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2930(uint32_t *this)
{
  int result; // eax

  result = sub_4E0120();
  if ( *(this + 1787) != 23 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 23);
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5C2950 sub_5C2950
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2950(int *this)
{
  int v2; // edi
  int result; // eax
  int fld_e30; // ecx

  sub_4D54E0(this);
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 376))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);
  if ( v2 != result )
  {
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( (unsigned int)(*(this + 2150) - result) > 0x3E8 )
    {
      fld_e30 = *(this + 30);
      if ( fld_e30 != 0 )
      {
        sub_4938F0(fld_e30);
        return sub_491F80(-1, -1, -1, 0, 1);
      }
    }
  }
  return result;
}



// 时钟门 AI（sub_699000, 53L）
// ------------------------------------------------------------
// 0x5C29B0 sub_5C29B0
// ------------------------------------------------------------
char /*thiscall*/ sub_5C29B0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int v7; // eax
  int v8; // ebx
  int fld_e2150; // ecx
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v17; // [esp+1Ch] [ebp+10h]

  LOBYTE(v7) = sub_4D8F90(nArg2, nArg3, nArg4, nArg5);
  if ( (uint8_t)nArg2 == 1 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this);
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);
    if ( v8 == v7 )
    {
      fld_e2150 = *(this + 2150) - sub_699000((int)(this + 9));  // 【clock_now(clk)】
      v10 = 0;
      v17 = 0;
      if ( fld_e2150 >= 500 )
      {
        v10 = (fld_e2150 - 500) / 1000 % 100;
        v17 = (fld_e2150 - 500) % 1000 / 10;
LABEL_6:
        v11 = sub_418DD0(v10 / 10);
        sub_499690(dword_79C0B0, nArg3, nArg4, -31, -63, 0.0, v11, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
        v12 = sub_418DD0(v10 % 10);
        sub_499690(dword_79C0B0, nArg3, nArg4, -16, -63, 0.0, v12, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
        v13 = sub_418DD0(10);
        sub_499690(dword_79C0B0, nArg3, nArg4, -1, -63, 0.0, v13, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
        v14 = sub_418DD0(v17 / 10 + 11);
        sub_499690(dword_79C0B0, nArg3, nArg4, 6, -63, 0.0, v14, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
        v15 = sub_418DD0(v17 % 10 + 11);
        LOBYTE(v7) = sub_499690(dword_79C0B0, nArg3, nArg4, 18, -63, 0.0, v15, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);
        return v7;
      }
      LOBYTE(v7) = fld_e2150 / 150 % 2 == 1;
      if ( fld_e2150 / 150 % 2 != 1 )
        goto LABEL_6;
    }
  }
  return v7;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C2BC0 sub_5C2BC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5C2BC0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  uint32_t *result; // eax

  if ( ArgList != 14 )
    return (uint32_t *)sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  result = *(uint32_t **)(LODWORD(fArg3) + 4);
  *(this + 2156) = *result;
  return result;
}



// 数据表读数 + RTTI cast（sub_47EF20; this+8352/8600/8604/8630 相位）
// ------------------------------------------------------------
// 0x5C2C00 sub_5C2C00
// ------------------------------------------------------------
int /*thiscall*/ sub_5C2C00(int this, int nArg2, int nArg3)
{
  int result; // eax
  uint32_t *v5; // esi
  int v6; // ebx
  uint64_t v7; // rax
  int v8; // ebx
  uint64_t v9; // rax
  char *v10; // ebx
  int v11; // eax
  uint32_t *v12; // eax
  int v13; // [esp+14h] [ebp+Ch]
  int v14; // [esp+14h] [ebp+Ch]
  int v15; // [esp+14h] [ebp+Ch]

  sub_4DD8F0((uint32_t *)this, nArg2, nArg3);
  result = __RTDynamicCast(
             *(uint32_t *)(this + 8352),
             0,
             &IRDActiveObject `RTTI Type Descriptor',
             &CNGunner `RTTI Type Descriptor',
             0);
  v5 = (uint32_t *)result;
  if ( result != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 672))(result, 3);
    v13 = sub_41A5E0(v6 + 60);
    v7 = (uint64_t)((double)v13 * COERCE_FLOAT(sub_41A5E0(v6 + 74)));
    sub_41A590(this + 736, SHIDWORD(v7), v7);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v5 + 672))(v5, 3);
    v14 = sub_41A5E0(v8 + 116);
    v9 = (uint64_t)((double)v14 * COERCE_FLOAT(sub_41A5E0(v8 + 130)));
    sub_41A590(this + 792, SHIDWORD(v9), v9);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    v10 = (char *)sub_47E720(2, 28);
    v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v5 + 1140))(v5, 28);
    *(uint32_t *)(this + 8600) = sub_47EF20(2, v15, -1, -1, 11);
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 388))(v5);
    result = sub_47EFD0(v10, COERCE_FLOAT(1), v15, v11, v11, 0);
    *(uint32_t *)(this + 8604) = result;
    if ( v5[2371] == 51 )
    {
      v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*v5 + 1160))(v5, 51);
      result = sub_47E9D0(v12, 0);
      *(uint32_t *)(this + 8600) = result;
      v5[2371] = -1;
      *(uint8_t *)(this + 8630) = 1;
    }
    *(uint32_t *)(this + 8600) += 500;
  }
  return result;
}



// 自爆二型（121L）：ROBOT_EX_02 播报 + EarthQuake.ani 震地 + particle/Ez8_Boom.ptl
//   爆点（★高达梗: Ez8）
// ------------------------------------------------------------
// 0x5C2D60 sub_5C2D60
// ------------------------------------------------------------
void /*usercall*/ sub_5C2D60(int *pDwArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // eax
  int v4; // edx
  char *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int *v12; // eax
  int v13; // edx
  void *v14; // ecx
  int v15; // edx
  int v16; // eax
  char v17[4]; // [esp+8h] [ebp-40h] BYREF
  void *v18; // [esp+Ch] [ebp-3Ch]
  int v19; // [esp+10h] [ebp-38h]
  int v20; // [esp+14h] [ebp-34h]
  char v21[4]; // [esp+18h] [ebp-30h] BYREF
  void *Block; // [esp+1Ch] [ebp-2Ch]
  int v23; // [esp+20h] [ebp-28h]
  int v24; // [esp+24h] [ebp-24h]
  void *pMem; // [esp+28h] [ebp-20h]
  char *v26; // [esp+2Ch] [ebp-1Ch]
  int v27; // [esp+30h] [ebp-18h]
  int v28; // [esp+34h] [ebp-14h]
  int v29; // [esp+38h] [ebp-10h]
  int v30; // [esp+44h] [ebp-4h]

  if ( *((uint8_t *)pDwArg1 + 8628) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, "ROBOT_EX_02", -1, 0, 0, nArg2);
    v27 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);
    v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
    v4 = *pDwArg1;
    v28 = v3;
    v29 = (*(int (/*thiscall*/ **)(int *))(v4 + 128))(pDwArg1) + 30;
    v5 = (char *)sub_44B6C0(284);
    v26 = v5;
    v30 = 0;
    if ( v5 != nullptr )
    {
      pMem = (void *)sub_42FCB0(228);
      LOBYTE(v30) = 1;
      if ( pMem != nullptr )
        v6 = sub_431860((char)"PassiveObject/Common/Animation/EarthQuake.ani", 1);
      else
        v6 = 0;
      LOBYTE(v30) = 0;
      sub_44E0D0(v5, v6, 1);
      *(uint32_t *)v5 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v5 = nullptr;
    }
    v7 = *(uint32_t *)v5;
    v30 = -1;
    (*(void (/*thiscall*/ **)(char *, int))(v7 + 72))(v5, 2);
    sub_45FE80(pDwArg1[29], (int)v5, 2, 0, (int)v5, (int)pDwArg1, 0);
    v8 = *(uint32_t *)v5;
    v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
    v10 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v9);
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v10 + 1);
    (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(v5, v11);
    if ( pDwArg1[2155] == 0 )
    {
      pMem = operator new(0x12Cu);
      v30 = 2;
      if ( pMem != nullptr )
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          v12 = (int *)sub_4C3640(pDwArg1 + 91, "particle/Ez8_Boom.ptl", pDwArg1);
        else
          v12 = (int *)sub_4C3640(pDwArg1[91], "particle/Ez8_Boom.ptl", pDwArg1);
      }
      else
      {
        v12 = nullptr;
      }
      pDwArg1[2155] = (int)v12;
      v13 = *v12;
      v30 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 12))(v12, 0);
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2155] + 40))(pDwArg1[2155], v27, v28, v29);
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pDwArg1[2155] + 92))(pDwArg1[2155], v21);
      v14 = (void *)pDwArg1[29];
      v30 = 3;
      sub_4600B0(v14, 2, 0, (int)v21);
      v30 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v23 = 0;
      v24 = 0;
    }
    v15 = *pDwArg1;
    *((uint8_t *)pDwArg1 + 8628) = 1;
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(v15 + 308))(pDwArg1) != 0 )
    {
      v16 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
      pDwArg1[2156] = sub_4E4A50(pDwArg1, 40002, pDwArg1[2151], v27, v28, v29, v16, 0, 0, 0);
      v18 = nullptr;
      v19 = 0;
      v20 = 0;
      v30 = 4;
      sub_431230((int)v17, pDwArg1 + 2156);
      (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 14, v17, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(*pDwArg1 + 108))(pDwArg1, -10000, -10000, 0);
      if ( v18 != nullptr )
        j__free(v18);
    }
  }
}


// 起爆倒计时：ROBOT_CLICK_LOOP + BOMB_READY_LOOP + ROBOT_CLICK_EX 播报（63L）
// ------------------------------------------------------------
// 0x5C2FE0 sub_5C2FE0
// ------------------------------------------------------------
void /*usercall*/ sub_5C2FE0(int pArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // ecx
  uint32_t *v4; // edi
  uint32_t *v5; // edi

  sub_4E1780((uint32_t *)pArg1);
  if ( *(uint8_t *)(pArg1 + 8629) == 0 )
  {
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
      pArg1,
      "ROBOT_CLICK_LOOP",
      10,
      0,
      0);
    if ( *(uint8_t *)(pArg1 + 8630) != 0 )
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
        pArg1,
        "BOMB_READY_LOOP",
        9,
        0,
        0);
    *(uint8_t *)(pArg1 + 8629) = 1;
  }
  v3 = *(uint32_t *)(pArg1 + 8600) - sub_699000(pArg1 + 36);  // 【clock_now(clk)】
  if ( v3 > 0 )
  {
    if ( v3 > 600 )
    {
      if ( v3 <= 5500 )
      {
        v5 = *(uint32_t **)(pArg1 + 6216);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) != *v5 )
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, **(uint32_t **)(pArg1 + 6216));
      }
    }
    else
    {
      v4 = (uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) != *v4 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 196))(
          pArg1,
          *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4),
          nArg2);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 10);
        if ( *(uint8_t *)(pArg1 + 8630) != 0 )
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 9);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "ROBOT_CLICK_EX", -1, 0);
      }
    }
  }
  else if ( *(uint32_t *)(pArg1 + 8624) == 0xFFFF )
  {
    sub_5C2D60((int *)pArg1, nArg2);
  }
}



// 子类扩展字段复位（this+8600..8652 全区, 25L）
// ------------------------------------------------------------
// 0x5C3100 sub_5C3100
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3100(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 1000;
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8636) = 0;
  *(uint32_t *)(this + 8640) = 0;
  *(uint32_t *)(this + 8644) = 0;
  *(uint8_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8656) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3170 sub_5C3170
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3170(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2160)(uint32_t, int); // ecx
  int result; // eax

  fld_e2160 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2160);
  if ( fld_e2160 != nullptr )
    result = (**fld_e2160)(fld_e2160, 1);
  *(this + 2160) = 0;
  return result;
}



// 时钟门 AI（sub_699000, 67L）
// ------------------------------------------------------------
// 0x5C31A0 sub_5C31A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C31A0(unsigned int *this)
{
  unsigned int result; // eax
  int nRand; // edi
  double v4; // st7
  double pThis_8732; // st7
  float pThis_873; // [esp+8h] [ebp-Ch]
  float v7; // [esp+Ch] [ebp-8h]
  float pThis_8733; // [esp+Ch] [ebp-8h]
  int nRand2; // [esp+10h] [ebp-4h]

  result = *(this + 1813);
  nRand = 0;
  if ( result != 0 )
  {
    v4 = ((double (/*thiscall*/ *)(unsigned int *, unsigned int, uint32_t))*(uint32_t *)(*this + 168))(this, result, 0);
    *((float *)this + 2163) = v4;
    if ( v4 > 80.0 )
      *(this + 2163) = 1117782016;
    if ( *((float *)this + 2163) < 0.0 )
      *(this + 2163) = 0;
    result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( *(this + 2151) + *(this + 2152) < result )
      {
        *(uint32_t *)(*(this + 2161) + 76) = (uint64_t)*((float *)this + 2163);
        nRand2 = 0;
        if ( *(uint32_t *)(*(this + 2161) + 76) == 0 )
        {
          nRand = rand() % 10 - 5;
          nRand2 = rand() % 10 - 5;
        }
        if ( (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this) != 0 )
        {
          pThis_873 = sub_405400((uint64_t)*((float *)this + 2163)) * 52.0;
          pThis_8732 = (double)(*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this) + pThis_873;
        }
        else
        {
          v7 = (float)(*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this);
          pThis_8732 = v7 - sub_405400((uint64_t)*((float *)this + 2163)) * 52.0;
        }
        *(uint32_t *)*(this + 2161) = (uint64_t)pThis_8732;
        *(uint32_t *)(*(this + 2161) + 4) = nRand + (*(int (/*thiscall*/ **)(unsigned int *))(*this + 124))(this);
        pThis_8733 = sub_4053E0((uint64_t)*((float *)this + 2163)) * 52.0;
        *(uint32_t *)(*(this + 2161) + 8) = (uint64_t)((double)((*(int (/*thiscall*/ **)(unsigned int *))(*this + 128))(this)
                                                                    + 60)
                                                           + pThis_8733
                                                           + (double)nRand2);
        *(uint8_t *)(*(this + 2161) + 84) = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this) != 1;
        sub_4E4C10(this, 22016, *(this + 2154), *(this + 2161), 0, 0, 0, 0);
        result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        *(this + 2151) = result;
      }
    }
    *((float *)this + 2163) = *((float *)this + 2163) * 0.017453289;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C33B0 sub_5C33B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C33B0(uint32_t *this, int nArg2)
{
  int result; // eax

  if ( *(this + 2155) == 4 )
  {
    *(this + 2155) = nArg2;
    return sub_498F00(nArg2);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C33D0 sub_5C33D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5C33D0(int *this)
{
  uint32_t *result; // eax
  int fld_e2158; // esi
  int fld_e2157; // edi

  sub_4D54E0(this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 5 )
  {
    result = sub_4938F0(*(this + 2158));
    fld_e2158 = *(this + 2158);
    if ( *(uint32_t *)(fld_e2158 + 148) == -1 )
      result = sub_4938F0(fld_e2158);
    *(uint32_t *)(fld_e2158 + 88) = 0;
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
         || (result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 840))(this)) == (uint32_t *)3 )
  {
    result = sub_4938F0(*(this + 2157));
    fld_e2157 = *(this + 2157);
    if ( *(uint32_t *)(fld_e2157 + 148) == -1 )
      result = sub_4938F0(*(this + 2157));
    *(uint32_t *)(fld_e2157 + 88) = *(this + 2163);
  }
  return result;
}



// 数据表读数 + RTTI cast（sub_47EF20, 69L）
// ------------------------------------------------------------
// 0x5C3460 sub_5C3460
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3460(int *this, int nArg2, int nArg3)
{
  uint64_t pObj2; // rax
  int pObj; // esi
  int v6; // ebx
  uint64_t v7; // rax
  int v8; // ebx
  uint64_t v9; // rax
  char *v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int pObj3; // esi
  double fld_e2154; // st7
  int v17; // [esp+14h] [ebp+Ch]
  int v18; // [esp+14h] [ebp+Ch]
  int v19; // [esp+14h] [ebp+Ch]

  sub_4DD8F0(this, nArg2, nArg3);
  LODWORD(pObj2) = __RTDynamicCast(
                  *(this + 2088),
                  0,
                  &IRDActiveObject `RTTI Type Descriptor',
                  &CNGunner `RTTI Type Descriptor',
                  0);
  pObj = pObj2;
  if ( (uint32_t)pObj2 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pObj2 + 672))(pObj2, 3);
    v17 = sub_41A5E0(v6 + 60);
    v7 = (uint64_t)((double)v17 * COERCE_FLOAT(sub_41A5E0(v6 + 74)));
    sub_41A590((unsigned int)(this + 184), SHIDWORD(v7), v7);
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
    v18 = sub_41A5E0(v8 + 116);
    v9 = (uint64_t)((double)v18 * COERCE_FLOAT(sub_41A5E0(v8 + 130)));
    sub_41A590((unsigned int)(this + 198), SHIDWORD(v9), v9);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    v10 = (char *)sub_47E720(2, 29);
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 29);
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
    *(this + 2164) = sub_47EFD0(v10, COERCE_FLOAT(3), v19, v11, v11, 0);
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj);
    *(this + 2154) = sub_47EFD0(v10, COERCE_FLOAT(1), v19, v12, v12, 0);
    v13 = sub_47EF20(2, v19, -1, -1, 11);
    *(this + 2152) = v13;
    *(this + 2151) = -v13;
    *(this + 2150) = sub_47EF20(4, v19, -1, -1, 11);
    LODWORD(pObj2) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, 8);
    pObj3 = pObj2;
    if ( (uint32_t)pObj2 != 0 )
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) == 32241
        || (LODWORD(pObj2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 16))(pObj3), *(uint32_t *)(pObj2 + 4) == 32267) )
      {
        fld_e2154 = (double)*(this + 2154);
        *(this + 2164) = (uint64_t)((double)*(this + 2164) * 1.25);
        pObj2 = (uint64_t)(fld_e2154 * 1.25);
        *(this + 2154) = pObj2;
      }
    }
  }
  return pObj2;
}



// 时钟门 AI（sub_699000, 68L）
// ------------------------------------------------------------
// 0x5C3630 sub_5C3630
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3630(uint32_t *this)
{
  int pThis_9; // eax
  uint8_t v3; // al
  uint8_t v4; // bl
  uint32_t **fld_e32; // eax
  uint32_t *v6; // edi
  int v7; // ebx
  int result; // eax

  sub_4E1780(this);
  if ( (unsigned int)(*(this + 2150) - sub_699000((int)(this + 9))) <= 0x5DC )  // 【clock_now(clk)】
  {
    pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    v3 = sub_42B420(50, 255, pThis_9, 250);
    v4 = v3;
    if ( *(this + 30) != 0 )
      sub_491690(1, 2, 1, -16776961, (v3 << 24) | 0xFFFFFF, 1);
    fld_e32 = (uint32_t **)*(this + 32);
    v6 = *fld_e32;
    if ( *fld_e32 != fld_e32 )
    {
      v7 = (v4 << 24) | 0xFFFFFF;
      do
      {
        sub_491690(1, 2, 1, -16776961, v7, 1);
        v6 = (uint32_t *)*v6;
      }
      while ( v6 != (uint32_t *)*(this + 32) );
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 )
  {
    sub_5C31A0(this);
    result = *(this + 1813);
    if ( result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
    if ( result != 5 )
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( (unsigned int)result >= *(this + 2150) )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
        if ( (uint8_t)result != 0 )
        {
          result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
          if ( result > 0 )
            return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t))(*this + 728))(this, 0, 1, 0);
        }
      }
    }
  }
  return result;
}



// 自爆子弹：引用 Particle/Exs_Bullet.ptl（this+8648 相位）
// ------------------------------------------------------------
// 0x5C3760 sub_5C3760
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3760(uint32_t *this)
{
  uint32_t *fld_e1554; // eax
  int v3; // edx
  int v4; // eax

  fld_e1554 = (uint32_t *)*(this + 1554);
  *(this + 2156) = fld_e1554[3];
  *(this + 2157) = fld_e1554[4];
  *(this + 2158) = fld_e1554[2];
  v3 = fld_e1554[5];
  v4 = *this;
  *(this + 2159) = v3;
  *(this + 2161) = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(v4 + 588))(this, "Particle/Exs_Bullet.ptl");
  *(this + 2153) = -1;
  *((uint8_t *)this + 8648) = 0;
  *(this + 2163) = 0;
  return 0;
}



// 自爆炸点：引用 particle/EXS_Boom.ptl（65L）
// ------------------------------------------------------------
// 0x5C37C0 sub_5C37C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C37C0(uint32_t *this)
{
  int v2; // ebx
  int v3; // edi
  int *pThis_5B; // eax
  int v5; // edx
  void *fld_e29; // ecx
  int result; // eax
  int v8; // eax
  uint8_t v9[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int v11; // [esp+14h] [ebp-1Ch]
  int v12; // [esp+18h] [ebp-18h]
  void *pMem; // [esp+1Ch] [ebp-14h]
  int v14; // [esp+20h] [ebp-10h]
  int v15; // [esp+2Ch] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 30;
  if ( *(this + 2160) == 0 )
  {
    pMem = operator new(0x12Cu);
    v15 = 0;
    if ( pMem != nullptr )
    {
      if ( *(this + 96) < 0x10u )
        pThis_5B = (int *)sub_4C3640(this + 91, "particle/EXS_Boom.ptl", this);
      else
        pThis_5B = (int *)sub_4C3640(*(this + 91), "particle/EXS_Boom.ptl", this);
    }
    else
    {
      pThis_5B = nullptr;
    }
    *(this + 2160) = pThis_5B;
    v5 = *pThis_5B;
    v15 = -1;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v5 + 12))(pThis_5B, 0);
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2160) + 40))(*(this + 2160), v2, v14, v3);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2160) + 92))(*(this + 2160), v9);
    fld_e29 = (void *)*(this + 29);
    v15 = 1;
    sub_4600B0(fld_e29, 2, 0, (int)v9);
    v15 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v11 = 0;
    v12 = 0;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    return sub_4E4A50(this, 40002, *(this + 2164), v2, v14, v3, v8, 0, 0, 0);
  }
  return result;
}



// 时钟门 AI（sub_699000; this+204/+208 硬直联动）
// ------------------------------------------------------------
// 0x5C3920 sub_5C3920
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3920(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int fld_e2156; // ecx
  int fld_e21562; // eax

  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2156));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2157));
  result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2159));
  switch ( ArgList )
  {
    case 5:
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this + 204))(
        this,
        -100,
        *(this + 2158),
        0,
        -60,
        0,
        0);
      return sub_5C37C0(this);
    case 8:
      sub_4926A0(*(this + 2157));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t))(*this + 204))(
        this,
        -100,
        *(this + 2157),
        0,
        -60,
        0,
        0);
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      *(this + 2153) = result;
      return result;
    case 0:
      fld_e2156 = *(this + 2156);
      *(this + 2163) = 0;
      sub_4926A0(fld_e2156);
      fld_e21562 = *(this + 2156);
      return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, int, uint32_t, uint32_t))(*this + 204))(
               this,
               -100,
               fld_e21562,
               0,
               -60,
               0,
               0);
    case 3:
    case 9:
      sub_4926A0(*(this + 2159));
      fld_e21562 = *(this + 2159);
      return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, int, uint32_t, uint32_t))(*this + 204))(
               this,
               -100,
               fld_e21562,
               0,
               -60,
               0,
               0);
    default:
      break;
  }
  return result;
}



// ============================================================
// 【分区 3】树精（Dendroid）（0x5C3A30-0x5C6190）
// 证据：DENDROID_SPIT/ATK/SWISH_01/02/DRIVE_01/01_LOOP、R_DENDROID_DMG + DENDROID_DIE、
//       Particle/Seed.ptl 种子弹、BEFORE_THUNDER 蓄雷、TRAP_OCTOPUS_TIGHTEN 缠绕（复用）、
//       Monster/Dendroid/CommonAni/{GrabAttack,Grab}.ani 抓取

// 子类扩展字段复位（this+8600..8656）
// ------------------------------------------------------------
// 0x5C3A30 sub_5C3A30
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3A30(int this)
{
  uint32_t *pThis_21D0; // ecx

  *(uint32_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = -1;
  *(uint32_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8640) = 0;
  *(uint32_t *)(this + 8644) = -1;
  *(uint32_t *)(this + 8652) = -1;
  pThis_21D0 = (uint32_t *)(this + 8656);
  *pThis_21D0 = 0;
  pThis_21D0[1] = 0;
  pThis_21D0[2] = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C3A90 sub_5C3A90
// ------------------------------------------------------------
int /*stdcall*/ sub_5C3A90(int *pDwArg1, int nArg2)
{
  int result; // eax
  int v3; // esi

  result = sub_4DC390(pDwArg1, nArg2);
  v3 = result;
  if ( result != 3 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.75);
      return 0;
    }
    else
    {
      return v3;
    }
  }
  return result;
}



// 主状态门（this+200/8640）
// ------------------------------------------------------------
// 0x5C3AF0 sub_5C3AF0
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3AF0(int *this)
{
  int fld_e1813; // eax
  int v3; // ebx
  int fld_e18132; // edi
  int v5; // eax
  int fld_e2167; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax

  LOBYTE(fld_e1813) = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)fld_e1813 != 0 )
  {
    fld_e1813 = *(this + 1813);
    if ( fld_e1813 != 0 )
    {
      fld_e1813 = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
      if ( *(int *)(fld_e1813 + 148) >= 3 )
      {
        LOBYTE(fld_e1813) = *((uint8_t *)this + 8640);
        if ( (uint8_t)fld_e1813 == 0 )
        {
          v3 = *this;
          fld_e18132 = *(this + 1813);
          v5 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*this + 152))(this, 150, 1, 0, 0);
          fld_e2167 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)fld_e18132 + 124))(
                 fld_e18132,
                 *(this + 2167),
                 0,
                 0,
                 v5);
          v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e18132 + 120))(fld_e18132, fld_e2167);
          v8 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e18132 + 124))(fld_e18132, 0, v7);
          v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e18132 + 120))(fld_e18132, v8);
          LOBYTE(fld_e1813) = (*(int (/*thiscall*/ **)(int *, int))(v3 + 584))(this, v9);
          *((uint8_t *)this + 8640) = 1;
        }
      }
    }
  }
  return fld_e1813;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3BA0 sub_5C3BA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3BA0(int *this)
{
  int result; // eax

  result = *(this + 2150);
  if ( result == 0 )
    return sub_4DA1D0();
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3BB0 sub_5C3BB0
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3BB0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( *(this + 2150) != 0 )
    return 0;
  else
    return sub_4D9210(nArg2, nArg3, nArg4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3BD0 sub_5C3BD0
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3BD0(uint32_t *this, int nArg2)
{
  if ( *(this + 2150) != 0 )
    return 0;
  else
    return sub_4D9200(nArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3BF0 sub_5C3BF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3BF0(int *this)
{
  int result; // eax

  result = *(this + 2150);
  if ( result == 0 )
    return sub_4D8750(this);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C3C00 sub_5C3C00
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3C00(uint32_t *this, int nArg2)
{
  int result; // eax

  result = *(this + 2150);
  if ( result == 0 )
    return sub_498F00(nArg2);
  return result;
}



// AI 相位辅助（76L）
// ------------------------------------------------------------
// 0x5C3C20 sub_5C3C20
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3C20(int *this)
{
  int result; // eax
  int fld_e2155; // ebx
  int fld_e21552; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int pThis_94; // edi
  bool v10; // zf
  int v11; // eax
  int v12; // edi
  int fld_e21553; // ebx
  int v14; // eax
  int v15; // eax
  uint32_t v16[2]; // [esp+Ch] [ebp-60h]
  uint32_t v17[22]; // [esp+14h] [ebp-58h]

  result = *(this + 2154);
  if ( result == 1 )
  {
    fld_e2155 = *(uint32_t *)*(this + 2155);
    fld_e21552 = *(this + 2155);
    v5 = (*(int (**)(void))(fld_e2155 + 128))();
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v5);
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21552 + 120))(fld_e21552, v6 - 1);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e2155 + 112))(*(this + 2155), v7);
  }
  else if ( result == 2 )
  {
    v16[1] = 0;
    v17[0] = 0;
    v17[2] = 0;
    v17[5] = 0;
    v17[6] = 185;
    v17[8] = 0;
    v17[11] = 0;
    v17[12] = 185;
    v17[14] = 0;
    v17[17] = 0;
    v17[18] = 185;
    v17[20] = 0;
    v17[21] = 0;
    v8 = *this;
    v16[0] = 345;
    v17[1] = 258;
    v17[3] = 232;
    v17[4] = 283;
    v17[7] = 258;
    v17[9] = 232;
    v17[10] = 283;
    v17[13] = 258;
    v17[15] = 232;
    v17[16] = 283;
    v17[19] = 313;
    pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v8 + 200))(this) + 148);
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0;
    v11 = 3 * pThis_94;
    if ( v10 )
      v12 = -v16[3 * pThis_94];
    else
      v12 = v16[3 * pThis_94];
    fld_e21553 = *(uint32_t *)*(this + 2155);
    v14 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, v17[v11]);
    v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v14 - 1);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e21553 + 112))(*(this + 2155), v12 + v15);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C3D40 sub_5C3D40
// ------------------------------------------------------------
int /*thiscall*/ sub_5C3D40(int *this, int nArg2, char pszArg3)
{
  int result; // eax
  int fld_e1813; // edi
  int fld_e18132; // edi
  int nRand; // eax
  int v8; // et2

  result = *(this + 2150);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
      if ( result == 0 )
      {
        result = *(this + 1813);
        if ( result != 0 )
        {
          if ( pszArg3 != 0 )
          {
            return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);
          }
          else
          {
            if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )
            {
              fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
              if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e1813 )
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);
            }
            result = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            if ( result == 1 )
            {
              fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
              result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
              if ( result >= fld_e18132 )
              {
                nRand = rand();
                v8 = nRand % 300;
                result = nRand / 300;
                if ( v8 < nArg2 )
                  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// 种子弹技能：DENDROID_SPIT 播报 + Particle/Seed.ptl（this+200/8640/8685 相位）
// ------------------------------------------------------------
// 0x5C3E20 sub_5C3E20
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3E20(uint8_t *this)
{
  int *pThis_C8; // eax
  int nRand3; // esi
  int nRand2; // eax
  int v5; // edx
  int nRand; // [esp+4h] [ebp-6Ch]
  uint32_t v8[26]; // [esp+8h] [ebp-68h] BYREF

  v8[25] = dword_796E50;
  if ( *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) >= 4 && *(this + 8685) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "DENDROID_SPIT",
      -1,
      0,
      0);
    *(this + 8685) = 1;
  }
  pThis_C8 = (int *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( pThis_C8[37] >= 6 )
  {
    LOBYTE(pThis_C8) = *(this + 8640);
    if ( (uint8_t)pThis_C8 == 0 )
    {
      LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
      if ( (uint8_t)pThis_C8 != 0 )
      {
        sub_432FA0();
        nRand = rand() % 5 + 4;
        pThis_C8 = (int *)(*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)this + 588))(this, "Particle/Seed.ptl");
        qmemcpy(v8, pThis_C8, 0x62u);
        nRand3 = nRand;
        if ( nRand > 0 )
        {
          do
          {
            v8[18] = rand() % 90 - 46;
            v8[19] = rand() % 90 - 46;
            v8[20] = rand() % 90 - 46;
            nRand2 = rand();
            v5 = *(uint32_t *)this;
            v8[17] = v8[17] + nRand2 % 50 - 26;
            LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t *, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(v5 + 580))(
                           this,
                           *((uint32_t *)this + 2161),
                           0,
                           v8,
                           0,
                           50,
                           1,
                           112,
                           4,
                           0,
                           0,
                           0);
            --nRand3;
          }
          while ( nRand3 != 0 );
        }
      }
      *(this + 8640) = 1;
    }
  }
  return (char)pThis_C8;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C3F70 sub_5C3F70
// ------------------------------------------------------------
char /*thiscall*/ sub_5C3F70(uint32_t *this, char pszArg2)
{
  int v2; // eax
  int nRand; // eax
  int v5; // et2
  int nRand2; // eax
  int v7; // et2
  int v8; // edx
  int v9; // edi
  int nRand3; // edi
  int v11; // ebx
  int nRand4; // ebx
  int nRand5; // eax
  int v15; // [esp+4h] [ebp-4h]
  int v16; // [esp+10h] [ebp+8h]

  LOBYTE(v2) = pszArg2;
  if ( pszArg2 != 0 || *(this + 1908) != 2 && (nRand = rand(), v5 = nRand % 100, v2 = nRand / 100, v5 >= 95) )
  {
    LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( (uint8_t)v2 != 0 )
    {
      sub_432FA0();
      nRand2 = rand();
      v7 = nRand2 % 3;
      v2 = nRand2 / 3;
      v8 = v7 + 3;
      if ( v7 + 3 > 0 )
      {
        v15 = v8;
        do
        {
          v16 = 100;
          while ( 1 )
          {
            v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
            nRand3 = v9 + rand() % 200 - 100;
            v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
            nRand4 = v11 + rand() % 70 - 35;
            if ( (uint8_t)sub_4D9210(nRand3, nRand4, 0) != 0 )
              break;
            LOBYTE(v2) = --v16;
            if ( v16 <= 0 )
              goto LABEL_12;
          }
          nRand5 = rand() % 2;
          LOBYTE(v2) = sub_4E4A50(this, 30052 - (nRand5 != 0), 5, nRand3, nRand4, 0, 4, 0, 0, 0);
LABEL_12:
          --v15;
        }
        while ( v15 != 0 );
      }
    }
  }
  return v2;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C4080 sub_5C4080
// ------------------------------------------------------------
void /*thiscall*/ sub_5C4080(uint32_t *this)
{
  *(this + 2162) = 3;
  *(this + 2167) = 30038;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C40A0 sub_5C40A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C40A0(uint32_t *this, int *pDwArg2, int nArg3)
{
  int result; // eax
  int v5; // ebx

  result = sub_5C3A90(pDwArg2, nArg3);
  v5 = result;
  if ( result != 3 )
  {
    if ( *(this + 2150) == 2 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 20) != 0 )
    {
      *pDwArg2 = 0;
      return 2;
    }
    else
    {
      return v5;
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C4100 sub_5C4100
// ------------------------------------------------------------
void /*thiscall*/ sub_5C4100(uint32_t *this)
{
  *(this + 2162) = 1;
  *(this + 2167) = 30039;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C4120 sub_5C4120
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4120(uint32_t *this, void *Block, int nArg3, int nArg4)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( result != 14 )
  {
    result = *(this + 2150);
    if ( result == 0 )
      return sub_4D6030((int)this, Block, nArg3, nArg4);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C4160 sub_5C4160
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4160(uint32_t *this)
{
  int result; // eax
  int fld_e2155; // edi
  int v4; // eax
  int v5; // [esp-20h] [ebp-24h]
  int v6; // [esp-18h] [ebp-1Ch]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    fld_e2155 = *(this + 2155);
    v6 = (*(int (**)(void))(*(uint32_t *)fld_e2155 + 152))();
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2155 + 124))(fld_e2155);
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2155 + 120))(fld_e2155);
    return sub_4E4A50(this, 30032, 0, v4, v5, 0, v6, 0, 0, 0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C41B0 sub_5C41B0
// ------------------------------------------------------------
void /*thiscall*/ sub_5C41B0(uint32_t *this)
{
  *(this + 2162) = 9999;
  *(this + 2167) = 30040;
  *(this + 2120) = 10;
  *(this + 2121) = 2000;
}



// 蓄雷 AI：BEFORE_THUNDER 播报（91L；树精复用雷系演出）
// ------------------------------------------------------------
// 0x5C41E0 sub_5C41E0
// ------------------------------------------------------------
char /*usercall*/ sub_5C41E0@<al>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int pObj; // ecx
  int v8; // edi
  int v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // edi
  uint16_t v13; // dx
  int v14; // eax
  uint32_t v17[4]; // [esp+4h] [ebp-14h]
  int v18; // [esp+14h] [ebp-4h]

  LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1);
  if ( (uint8_t)v4 != 0 )
  {
    if ( *((uint32_t *)pArg1 + 1813) != 0 )
    {
      v5 = *(uint32_t *)pArg1;
      v17[0] = 2;
      v17[1] = 4;
      v17[2] = 6;
      v17[3] = 8;
      v4 = (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 200))(pArg1);
      if ( *(uint32_t *)(v4 + 148) != v17[*((uint32_t *)pArg1 + 2168)] || (LOBYTE(v4) = pArg1[8640], (uint8_t)v4 != 0) )
      {
        pArg1[8640] = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "BEFORE_THUNDER",
          -1,
          0,
          0);
        if ( *((uint32_t *)pArg1 + 2172) == -1 )
        {
          v6 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)pArg1 + 1813) + 120))(*((uint32_t *)pArg1 + 1813));
          pObj = *((uint32_t *)pArg1 + 1813);
          *((uint32_t *)pArg1 + 2172) = v6;
          *((uint32_t *)pArg1 + 2173) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
        }
        v8 = *((uint32_t *)pArg1 + 2168) - 1;
        if ( (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 152))(pArg1, nArg3, nArg2) == 1 )
          v9 = 50 * v8;
        else
          v9 = -50 * v8;
        v10 = *((uint32_t *)pArg1 + 2173);
        v11 = v9;
        v12 = *(uint32_t *)pArg1;
        v13 = *((uint16_t *)pArg1 + 4336) + 1;
        v18 = v11 + *((uint32_t *)pArg1 + 2172);
        v14 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(v12 + 152))(pArg1, 100 * v13, 1);
        (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t, int))(v12 + 584))(
          pArg1,
          v18,
          v10,
          0,
          v18,
          v10,
          *((uint32_t *)pArg1 + 2167),
          0,
          0,
          v14);
        v4 = *((uint32_t *)pArg1 + 2168) + 1;
        *((uint32_t *)pArg1 + 2168) = v4;
        pArg1[8640] = 1;
      }
    }
    else
    {
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(
                     pArg1,
                     0,
                     0,
                     0,
                     0);
    }
  }
  return v4;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C4340 sub_5C4340
// ------------------------------------------------------------
void /*thiscall*/ sub_5C4340(uint32_t *this, int nArg2)
{
  int pObj3; // ebx
  int pObj2; // esi
  int v6; // eax
  int fld_e2167; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // [esp+8h] [ebp-8h]
  int pObj; // [esp+Ch] [ebp-4h]
  int pObj4; // [esp+18h] [ebp+8h]

  if ( nArg2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )
  {
    pObj3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
    pObj4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
    pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
    pObj2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
    v11 = *this;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*this + 152))(this, 100, 1, 0, 0);
    fld_e2167 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj3 + 124))(pObj3, *(this + 2167), 0, 0, v6);
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 120))(pObj4, fld_e2167);
    v9 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, 0, v8);
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v9);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v11 + 584))(this, v10);
  }
}



// 缠绕技能：TRAP_OCTOPUS_TIGHTEN 播报（114L；章鱼陷阱触手收紧, 树精复用）
// ------------------------------------------------------------
// 0x5C4400 sub_5C4400
// ------------------------------------------------------------
int /*usercall*/ sub_5C4400@<eax>(uint32_t **pArg1@<ecx>, int nArg2@<ebx>)
{
  uint32_t *v3; // ecx
  int v4; // eax
  int v5; // edx
  uint32_t *v6; // ecx
  int v7; // eax
  uint32_t *v8; // ecx
  int v9; // eax
  uint32_t *v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // edx
  uint32_t *v14; // ecx
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int result; // eax
  float v19; // [esp+4h] [ebp-20h] BYREF
  float v20; // [esp+8h] [ebp-1Ch]
  float v21; // [esp+Ch] [ebp-18h]
  int v22; // [esp+10h] [ebp-14h]
  int v23; // [esp+14h] [ebp-10h]
  int v24; // [esp+18h] [ebp-Ch]
  float v25; // [esp+1Ch] [ebp-8h]
  int v26; // [esp+20h] [ebp-4h]

  v3 = pArg1[2155];
  if ( v3 == nullptr )
    return ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*pArg1)[140])(pArg1, 15, 0, 0, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 840))(v3);
  v5 = *pArg1[2155];
  if ( v4 == 9 )
  {
    *(uint32_t *)((*(int (**)(void))(v5 + 60))() + 24) = 0;
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1[2155] + 60))(pArg1[2155]) + 36) = 0;
    if ( *(uint8_t *)(((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1) + 170) != 0 )
    {
      if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*pArg1)[77])(pArg1) != 0 )
      {
        v6 = pArg1[2155];
        v19 = 0.0;
        v20 = 0.0;
        v21 = 0.0;
        v22 = 0;
        v23 = 0;
        v24 = 0;
        v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*v6 + 120))(v6);
        v8 = pArg1[2155];
        v26 = v7;
        v19 = (float)v7;
        v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*v8 + 124))(v8);
        v10 = pArg1[2155];
        v26 = v9;
        v20 = (float)v9;
        v26 = (*(int (/*thiscall*/ **)(uint32_t *))(*v10 + 192))(v10);
        v11 = *v10;
        v25 = (double)v26 * 0.69999999;
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v11 + 128))(v10);
        v13 = (int)pArg1[2155];
        v26 = v12;
        v21 = (double)v12 + v25;
        sub_4E5F70(nArg2, (int)pArg1, v13, &v19, 1, 1);
      }
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*pArg1)[53])(
        pArg1,
        "TRAP_OCTOPUS_TIGHTEN",
        -1,
        0,
        0);
      v14 = pArg1[2157];
      v15 = (int)pArg1[2156] + 1;
      pArg1[2156] = (uint32_t *)v15;
      if ( v15 >= (int)v14 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1[2155] + 724))(pArg1[2155]) != 0 )
      {
        ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*pArg1)[140])(pArg1, 15, 0, 0, 0);
      }
      else
      {
        v16 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1);
        sub_4926A0(v16);
      }
      if ( pArg1[2154] == (uint32_t *)2 )
      {
        v17 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[20])(pArg1);
        sub_424120(*(uint32_t **)(v17 + 132), 2, 300);
        if ( (int)pArg1[2156] >= (int)pArg1[2157]
          || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1[2155] + 724))(pArg1[2155]) != 0 )
        {
          ((void (/*thiscall*/ *)(uint32_t **))(*pArg1)[331])(pArg1);
        }
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1[2155] + 604))(pArg1[2155], 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1[2155] + 612))(pArg1[2155], 1, 1);
    return sub_5C3C20(pArg1);
  }
  else
  {
    result = (*(int (**)(void))(v5 + 840))();
    if ( result != 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1[2155] + 308))(pArg1[2155]);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1[2155] + 560))(pArg1[2155], 9, 0, 0, 0);
    }
  }
  return result;
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5C4650 sub_5C4650
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4650(int *this, int nArg2, int nArg3, int nArg4)
{
  int v6; // eax
  int v7; // edi
  int pObj; // eax
  float v10; // [esp+0h] [ebp-2Ch]
  int v11; // [esp+34h] [ebp+8h]

  if ( *(this + 2150) == 1 && (uint8_t)sub_4E5AF0(this, nArg2) != 0 )
    sub_5C3D40(this, 50, 0);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
  if ( *(uint32_t *)(v6 + 20) == 1 )
  {
    v7 = (uint64_t)(*(float *)v6 * 0.0099999998);
    if ( operator new(0x80u) != nullptr )
    {
      v11 = 1;
      if ( v7 >= 1 )
        v11 = v7;
      v10 = (float)v11;
      pObj = sub_4D6810(LODWORD(v10), 100, 1, 1);
    }
    else
    {
      pObj = 0;
    }
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
      pObj,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  *(this + 2163) = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 20);
  return sub_4DA3B0(nArg2, nArg3, nArg4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C4750 sub_5C4750
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4750(int *this, int nArg2, int nArg3, int nArg4)
{
  sub_5C3F70(this, 0);
  return sub_5C4650(this, nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C4780 sub_5C4780
// ------------------------------------------------------------
int /*thiscall*/ sub_5C4780(uint32_t *this)
{
  uint32_t *fld_e1554; // eax
  uint32_t *pThis_879; // esi
  int i; // edi
  int result; // eax

  if ( *(this + 2150) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1316))(this);
  fld_e1554 = (uint32_t *)*(this + 1554);
  if ( *(this + 1543) == fld_e1554[2] )
    *(this + 1543) = *(this + 2151);
  if ( *(this + 1544) == fld_e1554[3] )
    *(this + 1544) = *(this + 2152);
  if ( *(this + 1540) == fld_e1554[7] )
    *(this + 1540) = *(this + 2153);
  pThis_879 = this + 2169;
  for ( i = 2; i != 0; --i )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*pThis_879 + 84))(*pThis_879, 0);
    ++pThis_879;
  }
  return result;
}



// 树精行进状态机（141L）：DENDROID_SWISH_02/SWISH_01/DRIVE_01/01_LOOP 四段播报
//   （this+200/8600/8620/8684/8685 相位 —— 钻地行进→突刺循环【推断】）
// ------------------------------------------------------------
// 0x5C4810 sub_5C4810
// ------------------------------------------------------------
char /*thiscall*/ sub_5C4810(int this)
{
  uint32_t *fld_1838; // edi
  uint32_t *fld_1848; // edi
  char fld_78; // al
  int pThis_348; // eax

  switch ( *(uint32_t *)(this + 6556) )
  {
    case 8:
      if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 )
      {
        fld_1838 = (uint32_t *)(*(uint32_t *)(this + 6200) + 4 * sub_41A5E0(this + 7028));
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *fld_1838
          && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0
          && *(uint32_t *)(this + 8620) == 0 )
        {
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 24));
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(
            this,
            *(uint32_t *)(*(uint32_t *)(this + 6216) + 24));
        }
        else
        {
          fld_1848 = (uint32_t *)(*(uint32_t *)(this + 6216) + 24);
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *fld_1848
            && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0
            && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
          }
        }
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 2
          && *(uint8_t *)(this + 8685) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "DENDROID_SWISH_02",
            -1,
            0,
            0);
          *(uint8_t *)(this + 8685) = 1;
        }
      }
      else if ( sub_41A5E0(this + 7028) == 3 )
      {
        sub_5C3E20(this);
      }
      else if ( sub_41A5E0(this + 7028) == 4 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1308))(this);
      }
      else if ( sub_41A5E0(this + 7028) == 0
             && *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3
             && *(uint8_t *)(this + 8685) == 0 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "DENDROID_SWISH_01",
          -1,
          0,
          0);
        *(uint8_t *)(this + 8685) = 1;
      }
      break;
    case 0xE:
      sub_5C4400(this);
      break;
    case 0xF:
      fld_78 = *(uint8_t *)(*(uint32_t *)(this + 120) + 170);
      goto LABEL_33;
    case 0x10:
      if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3
        && *(uint8_t *)(this + 8685) == 0 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "DENDROID_DRIVE_01",
          -1,
          0,
          0);
        *(uint8_t *)(this + 8685) = 1;
      }
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
      {
        goto LABEL_34;
      }
      break;
    case 0x11:
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )
      {
        fld_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
LABEL_33:
        if ( fld_78 != 0 )
LABEL_34:
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
      }
      break;
    default:
      break;
  }
  sub_4E1780((uint32_t *)this);
  if ( *(uint32_t *)(this + 8600) == 2
    && *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(this + 6216) + 32) + 170) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 17, 0, 0, 0);
  }
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( pThis_348 != 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this) == 4
    && (pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 188))(this)) == 4 )
  {
    if ( *(uint8_t *)(this + 8684) == 1 )
    {
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 9);
      *(uint8_t *)(this + 8684) = 0;
    }
  }
  else
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8684);
    if ( (uint8_t)pThis_348 == 0 )
    {
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                     this,
                     "DENDROID_01_LOOP",
                     9,
                     0,
                     0);
      *(uint8_t *)(this + 8684) = 1;
    }
  }
  return pThis_348;
}


// AI 相位辅助（83L）
// ------------------------------------------------------------
// 0x5C5720 sub_5C5720
// ------------------------------------------------------------
int /*thiscall*/ sub_5C5720(uint32_t *this)
{
  uint32_t *pThis2; // esi
  int result; // eax
  int v3; // edi
  unsigned int v4; // ebx
  int i; // edx
  int v6; // edi
  uint8_t *v7; // ecx
  uint32_t *pThis; // ecx

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
      pThis = this;
      break;
    case 4:
      if ( *(this + 1813) != 0 )
        goto LABEL_10;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      pThis = this;
      break;
    case 0xC:
      if ( *(this + 2150) == 1 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);
      goto LABEL_10;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) == 0 )
        goto LABEL_10;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      pThis = this;
      break;
    default:
LABEL_10:
      pThis = this;
      break;
  }
  pThis2 = pThis;
  result = pThis[2150];
  if ( result == 0 )
  {
    result = pThis[1813];
    if ( result != 0 )
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);
      result = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*pThis2 + 120))(pThis2) - v3);
      v4 = 0;
      for ( i = 0; ; i += 32 )
      {
        while ( 1 )
        {
          v6 = pThis2[1905];
          if ( v6 == 0 || v4 >= (pThis2[1906] - v6) >> 5 )
            return result;
          if ( i > 0 && i <= 64 )
            break;
LABEL_21:
          ++v4;
          i += 32;
        }
        v7 = (uint8_t *)(i + v6);
        if ( result <= 280 )
        {
          *v7 = 0;
          goto LABEL_21;
        }
        ++v4;
        *v7 = 1;
      }
    }
  }
  return result;
}



// 树精语音：R_DENDROID_DMG + DENDROID_DIE（this+8684/8685 相位）
// ------------------------------------------------------------
// 0x5C57F0 sub_5C57F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C57F0(uint32_t *this)
{
  int v2; // eax
  int result; // eax
  int fld_e1540; // ecx
  int v5; // [esp+4h] [ebp-4h] BYREF

  sub_4015C0("R_DENDROID_DMG", 0xEu);  // 【std::string构造赋值】
  sub_4015C0("DENDROID_DIE", 0xCu);  // 【std::string构造赋值】
  v2 = *this;
  *(this + 2158) = 8;
  *(this + 2161) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v2 + 384))(this, 2);
  *((uint8_t *)this + 8684) = 0;
  *((uint8_t *)this + 8685) = 0;
  v5 = 100000;
  sub_4E1390(196613, &v5);
  result = *(this + 1544);
  fld_e1540 = *(this + 1540);
  *(this + 2151) = *(this + 1543);
  *(this + 2152) = result;
  *(this + 2153) = fld_e1540;
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5C5890 sub_5C5890
// ------------------------------------------------------------
int /*thiscall*/ sub_5C5890(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2)
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0
    && *(this + 154) != 14 )
  {
    memset(&pBuf[1], 0, 12);
    v6 = *(uint32_t *)pObj;
    v9 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v6 + 48))(pObj);
    sub_431230((int)pBuf, &nArg2);
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
    sub_431230((int)pBuf, &nArg2);
    nArg2 = sub_41A5E0((unsigned int)(this + 1757));
    sub_431230((int)pBuf, &nArg2);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);
    v9 = -1;
    sub_5E5260(pBuf);
  }
  return sub_4DB480(pObj, nArg3, nArg4);
}



// 参数打包 AI（107L sub_431230）
// ------------------------------------------------------------
// 0x5C59C0 sub_5C59C0
// ------------------------------------------------------------
void /*usercall*/ sub_5C59C0(int *pDwArg1@<ecx>, int nArg2@<ebx>)
{
  int pObj3; // ecx
  int pObj; // edi
  int v5; // edx
  int v6; // eax
  int v7; // eax
  char v8; // al
  int pObj2; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  char v15[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v17; // [esp+10h] [ebp-18h]
  int v18; // [esp+14h] [ebp-14h]
  int pObj4; // [esp+18h] [ebp-10h] BYREF
  int v20; // [esp+24h] [ebp-4h]

  pObj3 = pDwArg1[2155];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2155] + 612))(pDwArg1[2155], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2155] + 136))(
           pDwArg1[2155],
           pDwArg1[2164],
           pDwArg1[2165],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pDwArg1[2155] + 112))(pDwArg1[2155], pDwArg1[2164], pDwArg1[2165]);
    }
    else
    {
      pObj = pDwArg1[2155];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2164, pDwArg1 + 2165, v7);
      pObj2 = pDwArg1[2155];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2164], pDwArg1[2165]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2166]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2155], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2155] + 308))(pDwArg1[2155]) != 0 )
    {
      Block = nullptr;
      v17 = 0;
      v18 = 0;
      v20 = 0;
      pObj4 = 4;
      sub_431230((int)v15, &pObj4);
      pObj4 = 0;
      sub_431230((int)v15, &pObj4);
      pObj4 = 1;
      sub_431230((int)v15, &pObj4);
      pObj4 = 200;
      sub_431230((int)v15, &pObj4);
      pObj4 = 200;
      sub_431230((int)v15, &pObj4);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2155] + 560))(pDwArg1[2155], 4, v15, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2155] + 564))(pDwArg1[2155]);
      v20 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v17 = 0;
      v18 = 0;
    }
    v13 = pDwArg1[2154];
    if ( v13 == 1 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2155] + 848))(pDwArg1[2155], 0);
    }
    else if ( v13 == 2 )
    {
      sub_495890(2, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2155] + 60))(pDwArg1[2155]);
      sub_4A0550(10);
      if ( pDwArg1[2155] == dword_8F7C04 )
      {
        v14 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
        sub_424A40(*(uint32_t **)(v14 + 132), pDwArg1[2155]);
      }
    }
    pDwArg1[2155] = 0;
  }
  pDwArg1[2154] = -1;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5C5C20 sub_5C5C20
// ------------------------------------------------------------
void /*thiscall*/ sub_5C5C20(uint32_t *this, int nArg2, int nArg3)
{
  void *pBuf[7]; // [esp+8h] [ebp-1Ch] BYREF

  if ( *(this + 2150) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1787) != 12
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
    && *(this + 1813) != 0
    && rand() % 300 < nArg3
    && (int)*(this + 2162) > 0
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 200 )
  {
    memset(&pBuf[1], 0, 12);
    pBuf[6] = nullptr;
    sub_431230((int)pBuf, &nArg2);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 16, pBuf, 0, 0);
    sub_5E5260(pBuf);
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C5D00 sub_5C5D00
// ------------------------------------------------------------
int /*thiscall*/ sub_5C5D00(int *this)
{
  sub_5C5720(this);
  sub_5C5C20(this, 1, 30);
  return sub_5C3D40(this, 50, 0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C5D20 sub_5C5D20
// ------------------------------------------------------------
void /*thiscall*/ sub_5C5D20(uint32_t *this)
{
  float v2; // [esp+4h] [ebp-8h]

  sub_5C5720(this);
  v2 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.25 > v2 )
    sub_5C5C20(this, 2, 300);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C5D80 sub_5C5D80
// ------------------------------------------------------------
int /*thiscall*/ sub_5C5D80(int *this)
{
  sub_5C5720(this);
  sub_5C5C20(this, 1, 300);
  return sub_5C3D40(this, 100, 0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C5DB0 sub_5C5DB0
// ------------------------------------------------------------
int /*userpurge*/ sub_5C5DB0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2155] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
      sub_5C59C0(pDwArg1, nArg2);
    pDwArg1[2155] = 0;
  }
  if ( pDwArg3 == pDwArg1 )
  {
    if ( pDwArg1[2155] != 0 )
    {
      sub_5C59C0(pDwArg1, nArg2);
      pDwArg1[2155] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 9);
  }
  return sub_4D9170(pDwArg3);
}



// 攻击 AI：DENDROID_ATK 播报（92L）
// ------------------------------------------------------------
// 0x5C5E20 sub_5C5E20
// ------------------------------------------------------------
char /*userpurge*/ sub_5C5E20@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, uint32_t **Block, int nArg5, int nArg6)
{
  int v7; // eax
  int v8; // eax
  int pObj; // eax
  float v11; // [esp+18h] [ebp-2Ch]
  int v12; // [esp+34h] [ebp-10h]
  int ArgLista; // [esp+4Ch] [ebp+8h]
  float Blocka; // [esp+50h] [ebp+Ch]

  v12 = *(uint32_t *)(pArg1 + 6556);
  if ( v12 == 14 )
    sub_5C59C0((int *)pArg1, nArg2);
  switch ( ArgList )
  {
    case 14:
      sub_5C4CA0(Block);
      break;
    case 15:
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 24));
      break;
    case 16:
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 1312))(pArg1, *Block[1]);
      break;
    case 17:
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1316))(pArg1);
      break;
    default:
      break;
  }
  *(uint8_t *)(pArg1 + 8685) = 0;
  LOBYTE(v7) = sub_4E33D0(ArgList, *(float *)&Block, nArg5, nArg6);
  if ( ArgList != 0 )
  {
    if ( ArgList == 5 )
    {
      if ( *(uint32_t *)(pArg1 + 8652) == 0 )
        LOBYTE(v7) = sub_5C3F70((uint32_t *)pArg1, 1);
    }
    else if ( ArgList == 8 )
    {
      *(uint8_t *)(pArg1 + 8640) = 0;
      *(uint32_t *)(pArg1 + 8672) = 0;
      if ( sub_41A5E0(pArg1 + 7028) == 0 || (v7 = sub_41A5E0(pArg1 + 7028)) == 4 )
        LOBYTE(v7) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
                       pArg1,
                       "DENDROID_ATK",
                       -1,
                       0,
                       0);
    }
  }
  else if ( v12 == 16 && *(uint32_t *)(pArg1 + 8600) == 2 )
  {
    sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 32));
    (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
      pArg1,
      100,
      *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 32),
      0,
      0,
      0,
      0);
    Blocka = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 740))(pArg1) * 0.75;
    ArgLista = (uint64_t)(Blocka - (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 736))(pArg1));
    if ( operator new(0x80u) != nullptr )
    {
      v8 = sub_4924C0(0);
      v11 = (float)ArgLista;
      pObj = sub_4D6810(LODWORD(v11), *(uint32_t *)(v8 + 48), 1, 1);
    }
    else
    {
      pObj = 0;
    }
    LOBYTE(v7) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
                   pObj,
                   pArg1,
                   pArg1,
                   0,
                   0,
                   0,
                   -1);
  }
  return v7;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C6040 sub_5C6040
// ------------------------------------------------------------
char /*userpurge*/ sub_5C6040@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, uint32_t **Block, int nArg5, int nArg6)
{
  int v7; // eax

  LOBYTE(v7) = sub_5C5E20(pArg1, nArg2, ArgList, Block, nArg5, nArg6);
  if ( ArgList == 8 )
  {
    v7 = sub_41A5E0(pArg1 + 7028);
    if ( v7 == 4 )
    {
      *(uint32_t *)(pArg1 + 8688) = -1;
      *(uint32_t *)(pArg1 + 8692) = -1;
      LOBYTE(v7) = -1;
    }
  }
  return v7;
}



// 抓取技能：Monster/Dendroid/CommonAni/{GrabAttack,Grab}.ani（51L；抓取→拖拽两段）
// ------------------------------------------------------------
// 0x5C6090 sub_5C6090
// ------------------------------------------------------------
int /*thiscall*/ sub_5C6090(int *this)
{
  int v2; // edi
  int *pThis_879; // esi
  void *pMem; // eax
  char *v5; // eax
  int v6; // edx
  int result; // eax
  void *v8[3]; // [esp+Ch] [ebp-1Ch]
  int v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+24h] [ebp-4h]

  sub_4DA130();
  v8[0] = "Monster/Dendroid/CommonAni/GrabAttack.ani";
  v8[1] = "Monster/Dendroid/CommonAni/Grab.ani";
  v2 = 0;
  pThis_879 = this + 2169;
  do
  {
    v9 = sub_42FCB0(228);
    v10 = 0;
    if ( v9 != 0 )
      v9 = sub_431860((char)v8[v2], 1);
    else
      v9 = 0;
    v10 = -1;
    pMem = operator new(0x11Cu);
    v8[2] = pMem;
    v10 = 1;
    if ( pMem != nullptr )
      v5 = sub_44E0D0((char *)pMem, v9, 0);
    else
      v5 = nullptr;
    *pThis_879 = (int)v5;
    v6 = *(uint32_t *)v5;
    v10 = -1;
    (*(void (/*thiscall*/ **)(char *, int))(v6 + 72))(v5, 2);
    sub_45FE80(*(this + 29), v2, 2, 0, *pThis_879, (int)this, 1);
    result = (*(int (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)*pThis_879 + 112))(*pThis_879, -1000, -1000, 0);
    ++v2;
    ++pThis_879;
  }
  while ( v2 < 2 );
  return result;
}



// ============================================================
// 【分区 4】属性精灵四色（Water/Fire/Dark/Light Soul）（0x5C6190-0x5C9360）
// 证据：{WATER,FIRESOUL,DARKSOUL,LIGHTSOUL}_{CREATE,CAST,ATK_1/2(+READY),DMG,DIE,01_LOOP} 全套、
//       Monster/Spirit/{Water,Fire,Dark,Light}Animation/Die.ani + LightAnimation/DieGlow.ani、
//       Particle/NaiasSacrificeAttack.ptl 水精灵献祭、Monster/Spirit/Light1Glow.equ、
//       0x5C92D0 调 sub_4E4430（HP 受击处理器/Boss 终局族）

// AI 字段访问
// ------------------------------------------------------------
// 0x5C6190 sub_5C6190
// ------------------------------------------------------------
void /*thiscall*/ sub_5C6190(uint32_t *this)
{
  *(this + 2184) = 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C61A0 sub_5C61A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C61A0(void *this, int nArg2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 724))(this);
    if ( (uint8_t)result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1316))(this, nArg2);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1320))(this, 1);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C61F0 sub_5C61F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C61F0(uint32_t *this, uint32_t *pArg2)
{
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t *))(*this + 1316))(this, pArg2) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1320))(this, 0);
  }
  if ( this == pArg2 )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);
  if ( (uint32_t *)*(this + 2184) == pArg2 )
    *(this + 2184) = 0;
  return sub_4D9170(pArg2);
}



// AI 相位辅助（63L）
// ------------------------------------------------------------
// 0x5C6B50 sub_5C6B50
// ------------------------------------------------------------
int /*usercall*/ sub_5C6B50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  int v4; // edi
  int v5; // ebx
  int pObj; // edi
  int v7; // eax
  int v8; // eax

  sub_4E0120();
  switch ( pArg1[1787] )
  {
    case 4:
      if ( pArg1[1813] == 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 13);
      break;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( pArg1[1813] != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 4);
      break;
    default:
      break;
  }
  if ( pArg1[2184] == 0 )
    __asm { jmp     dword ptr [eax+51Ch] }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*pArg1 + 8))(pArg1, pArg1[2184], 0, nArg3);
    result = sub_4D8FE0(pArg1);
    if ( v4 < result )
    {
      if ( v4 > 50 )
      {
        if ( pArg1[1787] != 25 )
        {
          v5 = *pArg1;
          pObj = pArg1[2184];
          v7 = (*(int (/*cdecl*/ **)(int))(*(uint32_t *)pObj + 124))(nArg2);
          v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v7);
          return (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 1144))(pArg1, v8);
        }
      }
      else
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
      }
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 16, 0, 0, 0);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C6BE0 sub_5C6BE0
// ------------------------------------------------------------
int /*usercall*/ sub_5C6BE0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  if ( pArg1[1787] == 7 )
    return sub_4E0120();
  else
    return sub_5C6B50(pArg1, nArg2, nArg3);
}



// 时钟门+插值 AI（sub_699000+sub_4049C0, 55L）
// ------------------------------------------------------------
// 0x5C6C00 sub_5C6C00
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C6C00(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  uint32_t *pThis; // esi
  unsigned int result; // eax
  int v7; // ebx
  int v8; // edi
  uint32_t **v9; // eax
  uint32_t *v10; // esi
  unsigned int v12; // [esp+20h] [ebp+14h]

  pThis = this;
  result = sub_4D8F90(nArg2, nArg3, nArg4, nArg5);
  if ( (uint8_t)nArg2 == 0 && pThis[1639] == 19 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 200))(pThis);
    result = sub_699000((int)(pThis + 2)) - pThis[2185];  // 【clock_now(clk)】
    v12 = result;
    if ( v7 != 0 )
    {
      if ( result >= 0x5DC )
      {
LABEL_9:
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 316))(pThis);
        if ( (uint8_t)result == 0 )
          return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis + 312))(pThis, 0);
        return result;
      }
      v8 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 255.0, result, 1500) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_491690(1, 5, 1, -1, v8, 1);
      v9 = *(uint32_t ***)(v7 + 204);
      v10 = *v9;
      if ( *v9 != v9 )
      {
        do
        {
          sub_491690(1, 5, 1, -1, v8, 1);
          v10 = (uint32_t *)*v10;
        }
        while ( v10 != *(uint32_t **)(v7 + 204) );
      }
      result = v12;
      pThis = this;
    }
    if ( result < 0x5DC )
      return result;
    goto LABEL_9;
  }
  return result;
}



// 时钟门+插值 AI（this+200 相位）
// ------------------------------------------------------------
// 0x5C6D00 sub_5C6D00
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C6D00(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  unsigned int result; // eax
  unsigned int fld_e2186; // eax
  uint64_t v8; // rax

  result = sub_5C6C00(this, nArg2, nArg3, nArg4, nArg5);
  if ( (uint8_t)nArg2 == 0 )
  {
    if ( *(this + 1787) == 7 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) != 0 )
    {
      fld_e2186 = sub_699000((int)(this + 9)) - *(this + 2186);  // 【clock_now(clk)】
      if ( fld_e2186 >= 0x2BC )
        LOBYTE(v8) = -36;
      else
        v8 = (uint64_t)sub_4049C0(100.0, 220.0, fld_e2186, 700);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_491690(1, 2, 1, -16776961, ((uint8_t)v8 << 24) | 0xFFFFFF, 1);
    }
    return sub_5C6C00(this, 0, nArg3, nArg4, nArg5);
  }
  return result;
}



// 复合字段（this+200/568/8700..8732 —— +568=最后受击时刻, 研究 20 §1.2）
// ------------------------------------------------------------
// 0x5C6DC0 sub_5C6DC0
// ------------------------------------------------------------
char /*thiscall*/ sub_5C6DC0(int this)
{
  int fld_2210; // eax
  unsigned int fld_2214; // ebx
  unsigned int pThis_1B74; // eax
  int pThis_94; // ebx
  unsigned int pThis_1B742; // ebx
  int pThis_1B743; // eax
  int fld_2200; // edx
  unsigned int v9; // ecx
  int v10; // eax
  int v11; // eax

  sub_4E1780((uint32_t *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
  {
    fld_2210 = *(uint32_t *)(this + 8720);
    if ( fld_2210 != 0 )
      fld_2214 = (*(uint32_t *)(this + 8724) - fld_2210) >> 2;
    else
      fld_2214 = 0;
    pThis_1B74 = sub_41A5E0(this + 7028);
    if ( fld_2214 > pThis_1B74 )
    {
      pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148);
      pThis_1B74 = *(uint32_t *)(this + 8720) + 4 * sub_41A5E0(this + 7028);
      if ( pThis_94 >= *(uint32_t *)pThis_1B74 )
      {
        LOBYTE(pThis_1B74) = *(uint8_t *)(this + 8732);
        if ( (uint8_t)pThis_1B74 == 0 )
        {
          pThis_1B742 = sub_41A5E0(this + 7028);
          pThis_1B74 = sub_52AEF0(this + 8700);
          if ( pThis_1B74 > pThis_1B742 )
          {
            pThis_1B743 = 28 * sub_41A5E0(this + 7028);
            fld_2200 = *(uint32_t *)(this + 8704);
            v9 = *(uint32_t *)(pThis_1B743 + fld_2200 + 24);
            v10 = fld_2200 + pThis_1B743;
            if ( v9 < 0x10 )
              v11 = v10 + 4;
            else
              v11 = *(uint32_t *)(v10 + 4);
            LOBYTE(pThis_1B74) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                           this,
                           v11,
                           -1,
                           0,
                           0);
          }
          *(uint8_t *)(this + 8732) = 1;
        }
      }
    }
  }
  else
  {
    pThis_1B74 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( pThis_1B74 == 15 )
    {
      LOBYTE(pThis_1B74) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
      if ( (uint8_t)pThis_1B74 != 0 )
      {
        pThis_1B74 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
        if ( *(uint8_t *)(pThis_1B74 + 170) != 0 )
          LOBYTE(pThis_1B74) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(
                         this,
                         0,
                         0,
                         0,
                         0);
      }
    }
  }
  return pThis_1B74;
}



// 字段访问（this+200/8744）
// ------------------------------------------------------------
// 0x5C6EE0 sub_5C6EE0
// ------------------------------------------------------------
char /*thiscall*/ sub_5C6EE0(uint8_t *this)
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 8
    && sub_41A5E0((unsigned int)(this + 7028)) == 1
    && *(this + 8744) == 0
    && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) > 0 )
  {
    sub_5C63E0(this);
  }
  return sub_5C6DC0((int)this);
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5C6F30 sub_5C6F30
// ------------------------------------------------------------
char /*thiscall*/ sub_5C6F30(uint32_t *this)
{
  float v3; // [esp+4h] [ebp-8h]

  if ( *(this + 1787) != 7 )
  {
    v3 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.15000001 >= v3 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 7);
      *(this + 2186) = sub_699000((int)(this + 9));
    }
  }
  return sub_5C6DC0((int)this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C6FA0 sub_5C6FA0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5C6FA0(uint8_t **this, int nArg2)
{
  uint8_t *result; // eax

  result = (uint8_t *)sub_4DBA80(nArg2);
  if ( nArg2 == 7 )
  {
    **(this + 1905) = 0;
    result = *(this + 1905) + 32;
    *result = 1;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C6FD0 sub_5C6FD0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5C6FD0(uint8_t **this, int nArg2)
{
  uint8_t *result; // eax

  result = (uint8_t *)sub_4DBC20(nArg2);
  if ( nArg2 == 7 )
  {
    **(this + 1905) = 1;
    result = *(this + 1905) + 32;
    *result = 0;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C7000 sub_5C7000
// ------------------------------------------------------------
int /*thiscall*/ sub_5C7000(void *this)
{
  float pThis_180; // [esp+4h] [ebp-4h]

  pThis_180 = (double)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 384))(this) * 0.0099999998;
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 688))(this, LODWORD(pThis_180));
  return sub_4EB2C0(0.0);
}



// AI 相位辅助（100L）
// ------------------------------------------------------------
// 0x5C7040 sub_5C7040
// ------------------------------------------------------------
int /*thiscall*/ sub_5C7040(uint32_t *this)
{
  uint32_t *pThis; // ebx
  unsigned int i; // esi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj4; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // ecx
  unsigned int v11; // esi
  int v12; // ecx
  int pObj2; // ecx
  int v14; // ecx
  int pObj3; // ecx
  int j; // esi
  int pObj; // eax
  unsigned int v19; // [esp+10h] [ebp-Ch]
  int v20; // [esp+14h] [ebp-8h]
  int v21; // [esp+14h] [ebp-8h]
  int v22; // [esp+18h] [ebp-4h]

  pThis = this;
  for ( i = 0; ; ++i )
  {
    v3 = pThis[29];
    v4 = *(uint32_t *)(v3 + 8);
    v19 = i;
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      pObj4 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj4 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 40))(pObj4, 17) != 0 )
    {
      v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 376))(pObj4);
      if ( v20 != (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis) )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 700))(pObj4);
        v9 = v8;
        v10 = *(uint32_t *)(v8 + 4);
        v11 = 0;
        if ( v10 != 0 )
          v22 = (*(uint32_t *)(v8 + 8) - v10) >> 2;
        else
          v22 = 0;
        v21 = 0;
        if ( v22 > 0 )
        {
          do
          {
            v12 = *(uint32_t *)(v9 + 4);
            if ( v12 != 0 && v11 < (*(uint32_t *)(v9 + 8) - v12) >> 2 )
              pObj2 = *(uint32_t *)(v12 + 4 * v11);
            else
              pObj2 = 0;
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 92))(pObj2) != 0 )
            {
              v14 = *(uint32_t *)(v9 + 4);
              if ( v14 != 0 && v11 < (*(uint32_t *)(v9 + 8) - v14) >> 2 )
                pObj3 = *(uint32_t *)(v14 + 4 * v11);
              else
                pObj3 = 0;
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 76))(pObj3, 0);
            }
            ++v11;
          }
          while ( (int)v11 < v22 );
        }
        for ( j = 0; j < 16; ++j )
        {
          if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 772))(pObj4, j) != 0
            && sub_496F80(j) == 16
            && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 776))(pObj4, j) != 0 )
          {
            pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 772))(pObj4, j);
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t *))(*(uint32_t *)pObj + 4))(pObj, 0, this);
            ++v21;
          }
        }
        if ( v21 > 0 )
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 956))(pObj4);
        i = v19;
      }
    }
    pThis = this;
  }
  return result;
}



// AI 字段访问（this+8748）
// ------------------------------------------------------------
// 0x5C71C0 sub_5C71C0
// ------------------------------------------------------------
char /*thiscall*/ sub_5C71C0(int this)
{
  int fld_78; // edi
  int pThis_1B74; // eax

  fld_78 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148);
  if ( *(uint32_t *)(this + 6556) == 8 )
  {
    pThis_1B74 = sub_41A5E0(this + 7028) - 2;
    if ( pThis_1B74 != 0 )
    {
      if ( pThis_1B74 == 1 && *(uint8_t *)(this + 8748) != 0 )
      {
        *(uint8_t *)(this + 8748) = 0;
        return sub_5C6F30((uint32_t *)this);
      }
    }
    else if ( *(uint8_t *)(this + 8748) != 0 && fld_78 >= 8 )
    {
      sub_5C7040((uint32_t *)this);
      *(uint8_t *)(this + 8748) = 0;
    }
  }
  return sub_5C6F30((uint32_t *)this);
}



// 语音注册（sub_4015C0; 23L）
// ------------------------------------------------------------
// 0x5C7230 sub_5C7230
// ------------------------------------------------------------
void /*noreturn*/ sub_5C7230()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5C72A0 sub_5C72A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C72A0(int this, int Src, unsigned int uArg3, int *pDwArg4)
{
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_85; // ecx
  int fld_86; // eax
  char *fld_42; // eax
  void *v15; // eax
  int fld_43; // eax
  int fld_87; // ecx
  unsigned int v18; // edi
  uint8_t *fld_83; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *fld_84; // edi
  int v24; // edi
  char *pMem; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  fld_4 = *(uint32_t *)(this + 4);
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_5C7230(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v28];
      *(uint32_t *)(this + 8) = &pMem[4 * v18];
      *(uint32_t *)(this + 4) = pMem;
      return (unsigned int)pMem;
    }
  }
  return result;
}



// 献祭攻击：Particle/NaiasSacrificeAttack.ptl（100L；sub_47EF20 数据表读数 ——
//   水精灵 Naias 献祭爆【推断】）
// ------------------------------------------------------------
// 0x5C7480 sub_5C7480
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C7480(unsigned int *this, int nArg2, int nArg3, unsigned int pArg4)
{
  uint32_t *v5; // edi
  unsigned int i; // ebx
  unsigned int result; // eax
  int v8; // ecx
  int pObj; // edi
  char *v10; // eax
  bool v11; // cc
  uint32_t *v12; // edi
  int j; // ebx
  int fld_e2088; // eax
  int v15; // eax
  int v16; // [esp+10h] [ebp-14h]
  char *v17; // [esp+10h] [ebp-14h]
  int v18; // [esp+14h] [ebp-10h]
  int fld_e20882; // [esp+14h] [ebp-10h]
  float v20; // [esp+2Ch] [ebp+8h]
  int dword_78FE2C2; // [esp+2Ch] [ebp+8h]
  float v22; // [esp+34h] [ebp+10h]
  float v23; // [esp+34h] [ebp+10h]
  int dword_78FE282; // [esp+34h] [ebp+10h]

  v5 = (uint32_t *)sub_47E720(3, 49);
  v18 = sub_47EF20(1, nArg2, -1, -1, 11);
  v20 = (float)(int)sub_47EF20(3, nArg2, -1, -1, 11);
  v16 = sub_47E9D0(v5, 1u);
  for ( i = 0; ; ++i )
  {
    result = pArg4;
    v8 = *(uint32_t *)(pArg4 + 4);
    if ( v8 == 0 )
      break;
    result = (*(uint32_t *)(pArg4 + 8) - v8) >> 2;
    if ( i >= result )
      break;
    pObj = 0;
    if ( operator new(0x7Cu) != nullptr )
      pObj = sub_4B3C90(v18, 1);
    (*(void (/*thiscall*/ **)(int, int, uint32_t, float))(*(uint32_t *)pObj + 120))(pObj, 5, 0, COERCE_FLOAT(LODWORD(v20)));
    (*(void (/*thiscall*/ **)(int, int, uint32_t, float))(*(uint32_t *)pObj + 120))(pObj, 26, 0, COERCE_FLOAT(LODWORD(v20)));
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(
      pObj,
      *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4 * i),
      *(this + 2088),
      1,
      0,
      19,
      v16);
  }
  if ( nArg3 > 0 )
  {
    result = *(this + 2088);
    if ( result != 0 )
    {
      v10 = (char *)sub_47E720(3, 52);
      dword_78FE2C = 0;
      *(uint16_t *)dword_78FE28 = 100;
      v11 = dword_78FE2C + 2 <= *(uint32_t *)dword_78FE24;
      v17 = v10;
      dword_78FE2C += 2;
      if ( !v11 )
        off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
      v22 = (double)(int)sub_47EF20(2, nArg3, -1, -1, 11) * 0.1;
      *(float *)(dword_78FE28 + dword_78FE2C) = v22;
      dword_78FE2C += 4;
      if ( dword_78FE2C > *(int *)dword_78FE24 )
        off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
      v23 = (float)(int)sub_47EF20(3, nArg3, -1, -1, 11);
      *(float *)(dword_78FE28 + dword_78FE2C) = v23;
      dword_78FE2C += 4;
      if ( dword_78FE2C > *(int *)dword_78FE24 )
        off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
      v12 = (uint32_t *)(*(int (/*thiscall*/ **)(unsigned int *, const char *))(*this + 588))(
                        this,
                        "Particle/NaiasSacrificeAttack.ptl");
      *(uint32_t *)((char *)v12 + 85) = sub_47EF20(0, nArg3, -1, -1, 11);
      for ( j = 0; j < 360; j += 45 )
      {
        *v12 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 120))(this);
        v12[1] = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 124))(this);
        v12[2] = 0;
        v12[18] = j;
        dword_78FE282 = dword_78FE28;
        dword_78FE2C2 = dword_78FE2C;
        fld_e2088 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2088) + 388))(*(this + 2088));
        fld_e20882 = *(this + 2088);
        v15 = sub_47EFD0(v17, COERCE_FLOAT(1), nArg3, fld_e2088, fld_e2088, 0);
        result = sub_4E4C10(fld_e20882, 42007, v15, v12, 0, 0, dword_78FE2C2, dword_78FE282);
      }
    }
  }
  return result;
}



// 数据表读数 AI（sub_47EF20, 95L）
// ------------------------------------------------------------
// 0x5C7750 sub_5C7750
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C7750(int *this, int nArg2, int nArg3, unsigned int pArg4)
{
  uint32_t *v5; // edi
  unsigned int i; // ebx
  unsigned int result; // eax
  int v8; // ecx
  int pObj; // edi
  char *v10; // edi
  int fld_e2088; // eax
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // [esp-18h] [ebp-3Ch]
  int v16; // [esp-14h] [ebp-38h]
  int v17; // [esp-10h] [ebp-34h]
  int v18; // [esp+10h] [ebp-14h]
  int v19; // [esp+14h] [ebp-10h]
  float v20; // [esp+2Ch] [ebp+8h]
  int dword_78FE2C2; // [esp+2Ch] [ebp+8h]
  int fld_e20882; // [esp+30h] [ebp+Ch]
  float v23; // [esp+34h] [ebp+10h]
  float v24; // [esp+34h] [ebp+10h]
  int dword_78FE282; // [esp+34h] [ebp+10h]

  v5 = (uint32_t *)sub_47E720(3, 49);
  v19 = sub_47EF20(1, nArg2, -1, -1, 11);
  v20 = (float)(int)sub_47EF20(2, nArg2, -1, -1, 11);
  v18 = sub_47E9D0(v5, 1u);
  for ( i = 0; ; ++i )
  {
    result = pArg4;
    v8 = *(uint32_t *)(pArg4 + 4);
    pObj = 0;
    if ( v8 == 0 )
      break;
    result = (*(uint32_t *)(pArg4 + 8) - v8) >> 2;
    if ( i >= result )
      break;
    if ( operator new(0x7Cu) != nullptr )
      pObj = sub_4B3C90(v19, 1);
    (*(void (/*thiscall*/ **)(int, int, uint32_t, float))(*(uint32_t *)pObj + 120))(pObj, 1, 0, COERCE_FLOAT(LODWORD(v20)));
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(
      pObj,
      *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4 * i),
      *(this + 2088),
      1,
      0,
      18,
      v18);
  }
  if ( nArg3 > 0 && *(this + 2088) != 0 )
  {
    v10 = (char *)sub_47E720(3, 51);
    dword_78FE2C = 0;
    *(uint16_t *)dword_78FE28 = sub_47EF20(0, nArg3, -1, -1, 11);
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    *(uint16_t *)(dword_78FE28 + dword_78FE2C) = 0;
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    *(uint8_t *)(dword_78FE28 + dword_78FE2C++) = 9;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    v23 = (double)(int)sub_47EF20(2, nArg3, -1, -1, 11) * 0.1;
    *(float *)(dword_78FE28 + dword_78FE2C) = v23;
    dword_78FE2C += 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    v24 = (float)(int)sub_47EF20(3, nArg3, -1, -1, 11);
    *(float *)(dword_78FE28 + dword_78FE2C) = v24;
    dword_78FE2C += 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    dword_78FE282 = dword_78FE28;
    dword_78FE2C2 = dword_78FE2C;
    fld_e2088 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2088) + 388))(*(this + 2088));
    v12 = sub_47EFD0(v10, COERCE_FLOAT(1), nArg3, fld_e2088, fld_e2088, 0);
    fld_e20882 = *(this + 2088);
    v17 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    v13 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this) / 2;
    v16 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + v13;
    v15 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v14 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    return sub_4E4A50(fld_e20882, 40002, v12, v14, v15, v16, v17, 0, dword_78FE2C2, dword_78FE282);
  }
  return result;
}



// 数据表读数 AI（sub_47EF20, 95L）
// ------------------------------------------------------------
// 0x5C7A60 sub_5C7A60
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C7A60(int *this, int nArg2, int nArg3, unsigned int pArg4)
{
  uint32_t *v5; // edi
  unsigned int i; // ebx
  unsigned int result; // eax
  int v8; // ecx
  int pObj; // edi
  char *v10; // edi
  int fld_e2088; // eax
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // [esp-18h] [ebp-3Ch]
  int v16; // [esp-14h] [ebp-38h]
  int v17; // [esp-10h] [ebp-34h]
  int v18; // [esp+10h] [ebp-14h]
  int v19; // [esp+14h] [ebp-10h]
  float v20; // [esp+2Ch] [ebp+8h]
  int dword_78FE2C2; // [esp+2Ch] [ebp+8h]
  int fld_e20882; // [esp+30h] [ebp+Ch]
  float v23; // [esp+34h] [ebp+10h]
  float v24; // [esp+34h] [ebp+10h]
  int dword_78FE282; // [esp+34h] [ebp+10h]

  v5 = (uint32_t *)sub_47E720(3, 49);
  v19 = sub_47EF20(1, nArg2, -1, -1, 11);
  v20 = (double)(int)sub_47EF20(4, nArg2, -1, -1, 11) * 0.1;
  v18 = sub_47E9D0(v5, 1u);
  for ( i = 0; ; ++i )
  {
    result = pArg4;
    v8 = *(uint32_t *)(pArg4 + 4);
    pObj = 0;
    if ( v8 == 0 )
      break;
    result = (*(uint32_t *)(pArg4 + 8) - v8) >> 2;
    if ( i >= result )
      break;
    if ( operator new(0x7Cu) != nullptr )
      pObj = sub_4B3C90(v19, 1);
    (*(void (/*thiscall*/ **)(int, int, uint32_t, float))(*(uint32_t *)pObj + 120))(pObj, 12, 0, COERCE_FLOAT(LODWORD(v20)));
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(
      pObj,
      *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4 * i),
      *(this + 2088),
      1,
      0,
      20,
      v18);
  }
  if ( nArg3 > 0 && *(this + 2088) != 0 )
  {
    v10 = (char *)sub_47E720(3, 53);
    dword_78FE2C = 0;
    *(uint16_t *)dword_78FE28 = sub_47EF20(0, nArg3, -1, -1, 11);
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    *(uint16_t *)(dword_78FE28 + dword_78FE2C) = 0;
    dword_78FE2C += 2;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    *(uint8_t *)(dword_78FE28 + dword_78FE2C++) = 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    v23 = (double)(int)sub_47EF20(2, nArg3, -1, -1, 11) * 0.1;
    *(float *)(dword_78FE28 + dword_78FE2C) = v23;
    dword_78FE2C += 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    v24 = (float)(int)sub_47EF20(3, nArg3, -1, -1, 11);
    *(float *)(dword_78FE28 + dword_78FE2C) = v24;
    dword_78FE2C += 4;
    if ( dword_78FE2C > *(int *)dword_78FE24 )
      off_77F3FC(aCriticalError_40, *(uint32_t *)dword_78FE24);
    dword_78FE282 = dword_78FE28;
    dword_78FE2C2 = dword_78FE2C;
    fld_e2088 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2088) + 388))(*(this + 2088));
    v12 = sub_47EFD0(v10, COERCE_FLOAT(1), nArg3, fld_e2088, fld_e2088, 0);
    fld_e20882 = *(this + 2088);
    v17 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    v13 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this) / 2;
    v16 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + v13;
    v15 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v14 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    return sub_4E4A50(fld_e20882, 44001, v12, v14, v15, v16, v17, 0, dword_78FE2C2, dword_78FE282);
  }
  return result;
}



// 数据表读数 AI（sub_47EF20, 99L）
// ------------------------------------------------------------
// 0x5C7D80 sub_5C7D80
// ------------------------------------------------------------
int /*thiscall*/ sub_5C7D80(int *this, int nArg2, int nArg3, int pArg4)
{
  uint32_t *v5; // esi
  unsigned int i; // ebx
  int result; // eax
  int v8; // ecx
  int pObj; // esi
  unsigned int j; // ebx
  int fld_e29; // ecx
  int v12; // edx
  int v13; // edx
  int pObj2; // esi
  int fld_e2088; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // [esp+10h] [ebp-14h]
  int fld_e20882; // [esp+10h] [ebp-14h]
  int v24; // [esp+14h] [ebp-10h]
  float v25; // [esp+2Ch] [ebp+8h]
  int v26; // [esp+2Ch] [ebp+8h]
  unsigned int v27; // [esp+34h] [ebp+10h]

  v5 = (uint32_t *)sub_47E720(3, 49);
  v24 = sub_47EF20(1, nArg2, -1, -1, 11);
  v25 = (double)(int)sub_47EF20(5, nArg2, -1, -1, 11) * 0.1;
  v22 = sub_47E9D0(v5, 1u);
  for ( i = 0; ; ++i )
  {
    result = pArg4;
    v8 = *(uint32_t *)(pArg4 + 4);
    if ( v8 == 0 )
      break;
    result = (*(uint32_t *)(pArg4 + 8) - v8) >> 2;
    if ( i >= result )
      break;
    pObj = 0;
    if ( operator new(0x7Cu) != nullptr )
      pObj = sub_4B3C90(v24, 1);
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pObj + 120))(pObj, 8, 1, COERCE_FLOAT(LODWORD(v25)));
    (*(void (/*thiscall*/ **)(int, int, int, float))(*(uint32_t *)pObj + 120))(pObj, 7, 1, COERCE_FLOAT(LODWORD(v25)));
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, int))(*(uint32_t *)pObj + 56))(
      pObj,
      *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4 * i),
      *(this + 2088),
      1,
      0,
      21,
      v22);
  }
  if ( nArg3 > 0 )
  {
    result = *(this + 2088);
    if ( result != 0 )
    {
      sub_47E720(3, 54);
      v26 = sub_47EF20(0, nArg3, -1, -1, 11);
      for ( j = 0; ; ++j )
      {
        fld_e29 = *(this + 29);
        v12 = *(uint32_t *)(fld_e29 + 120);
        v27 = j;
        result = v12 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v12) >> 2 : 0;
        if ( (int)j >= result )
          break;
        v13 = *(uint32_t *)(fld_e29 + 120);
        if ( v13 != 0 && j < (*(uint32_t *)(fld_e29 + 124) - v13) >> 2 )
          pObj2 = *(uint32_t *)(v13 + 4 * j);
        else
          pObj2 = 0;
        if ( (uint8_t)sub_4E4630(pObj2) != 0
          && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 624))(pObj2) != 0
          && (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, pObj2, 0) <= v26 )
        {
          fld_e2088 = *(uint32_t *)*(this + 2088);
          fld_e20882 = *(this + 2088);
          v16 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*this + 152))(this, 250, 1, 0, 0);
          v17 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int))(*(uint32_t *)pObj2 + 124))(pObj2, 23019, nArg3, 0, v16);
          v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v17);
          v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 128))(pObj2, v18);
          v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 124))(pObj2, v19);
          v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v20);
          (*(void (/*thiscall*/ **)(int, int))(fld_e2088 + 584))(fld_e20882, v21);
          j = v27;
        }
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C7FB0 sub_5C7FB0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C7FB0(int *this, int *pDwArg2)
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 2;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )
    return sub_5C72A0((int)this, *(this + 2), 1u, pDwArg2);
  fld_e22 = (int *)*(this + 2);
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;
  return result;
}



// 大型 AI（161L；精灵相位）
// ------------------------------------------------------------
// 0x5C8000 sub_5C8000
// ------------------------------------------------------------
char /*usercall*/ sub_5C8000@<al>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>)
{
  unsigned int v4; // esi
  uint32_t *v5; // ebx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int pObj2; // ecx
  int v11; // ecx
  int v12; // edx
  int pObj; // ecx
  int v14; // ecx
  int v15; // edx
  unsigned int v16; // eax
  int *v18; // esi
  unsigned int i; // ebx
  bool v20; // cf
  int v21; // eax
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // ebx
  int v26; // eax
  char *v27; // ebx
  int v28; // ebx
  char *v29; // eax
  int v30; // [esp-10h] [ebp-4Ch]
  int v33; // [esp+4h] [ebp-38h] BYREF
  void *v34; // [esp+8h] [ebp-34h]
  int v35; // [esp+Ch] [ebp-30h]
  int v36; // [esp+10h] [ebp-2Ch]
  uint8_t v37[4]; // [esp+14h] [ebp-28h] BYREF
  void *Block; // [esp+18h] [ebp-24h]
  void *Src; // [esp+1Ch] [ebp-20h]
  int v40; // [esp+20h] [ebp-1Ch]
  int v41; // [esp+24h] [ebp-18h] BYREF
  int v42; // [esp+28h] [ebp-14h]
  int v43; // [esp+2Ch] [ebp-10h] BYREF
  int v44; // [esp+38h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) != 0 )
  {
    return 0;
  }
  v4 = 0;
  v5 = nullptr;
  v34 = nullptr;
  v35 = 0;
  v36 = 0;
  v44 = 0;
  while ( 1 )
  {
    v6 = pArg1[29];
    v7 = *(uint32_t *)(v6 + 120);
    v8 = v7 != 0 ? (*(uint32_t *)(v6 + 124) - v7) >> 2 : 0;
    if ( (int)v4 >= v8 )
      break;
    v9 = *(uint32_t *)(v6 + 120);
    if ( v9 != 0 && v4 < (*(uint32_t *)(v6 + 124) - v9) >> 2 )
      pObj2 = *(uint32_t *)(v9 + 4 * v4);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 33) != 0 )
    {
      v11 = pArg1[29];
      v12 = *(uint32_t *)(v11 + 120);
      if ( v12 != 0 && v4 < (*(uint32_t *)(v11 + 124) - v12) >> 2 )
        pObj = *(uint32_t *)(v12 + 4 * v4);
      else
        pObj = 0;
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 23001 )
      {
        v14 = pArg1[29];
        v15 = *(uint32_t *)(v14 + 120);
        if ( v15 != 0 && v4 < (*(uint32_t *)(v14 + 124) - v15) >> 2 )
          v43 = *(uint32_t *)(v15 + 4 * v4);
        else
          v43 = 0;
        sub_5C7FB0(&v33, &v43);
        v5 = v34;
      }
    }
    ++v4;
  }
  if ( v5 == nullptr )
    return 0;
  v16 = (v35 - (int)v5) >> 2;
  v41 = v16;
  if ( v16 == 0 )
  {
    j__free(v5);
    return 0;
  }
  v18 = (int *)*v5;
  for ( i = 1; ; ++i )
  {
    v20 = i < v16;
    v21 = *pArg1;
    v43 = i;
    if ( !v20 )
      break;
    v22 = (*(int (/*thiscall*/ **)(uint32_t *, int *, uint32_t))(v21 + 8))(pArg1, v18, 0);
    v23 = *pArg1;
    v30 = *((uint32_t *)v34 + i);
    v42 = v22;
    v24 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(v23 + 8))(pArg1, v30, 0);
    if ( v24 < v42 )
      v18 = *((int **)v34 + i);
    v16 = v41;
  }
  v25 = (*(int (/*thiscall*/ **)(uint32_t *, int *, uint32_t))(v21 + 8))(pArg1, v18, 0);
  if ( v25 >= sub_4D8FE0(pArg1) )
  {
    j__free(v34);
    return 0;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 564))(pArg1, nArg3, nArg2);
  Block = nullptr;
  Src = nullptr;
  v40 = 0;
  v26 = *v18;
  LOBYTE(v44) = 1;
  v43 = (*(int (/*thiscall*/ **)(int *))(v26 + 48))(v18);
  v27 = (char *)Src;
  if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v40 - (int)Block) >> 2) )
  {
    *(uint32_t *)Src = v43;
    Src = v27 + 4;
  }
  else
  {
    sub_430C80(Src, 1, (int)&v43);
  }
  v28 = (*(int (/*thiscall*/ **)(int *))(*v18 + 52))(v18);
  v29 = (char *)Src;
  v41 = v28;
  if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v40 - (int)Block) >> 2) )
  {
    *(uint32_t *)Src = v28;
    Src = v29 + 4;
  }
  else
  {
    sub_430C80(Src, 1, (int)&v41);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *))(*pArg1 + 560))(pArg1, 14, v37);
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  Src = nullptr;
  v40 = 0;
  j__free(v34);
  return 1;
}


// 水精灵语音全套：WATERSOUL_DIE/DMG/01_LOOP/CREATE/CAST/ATK_1_READY/ATK_2_READY/
//   ATK_1/ATK_2 九段播报（66L）
// ------------------------------------------------------------
// 0x5C8290 sub_5C8290
// ------------------------------------------------------------
int sub_5C8290()
{
  uint8_t v1[4]; // [esp+Ch] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-44h]
  int v3; // [esp+20h] [ebp-34h]
  unsigned int v4; // [esp+24h] [ebp-30h]
  uint8_t v5[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *v6; // [esp+2Ch] [ebp-28h]
  int v7; // [esp+3Ch] [ebp-18h]
  unsigned int v8; // [esp+40h] [ebp-14h]
  int v9; // [esp+44h] [ebp-10h] BYREF
  int v10; // [esp+50h] [ebp-4h]

  sub_4015C0("WATERSOUL_DIE", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("WATERSOUL_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("WATERSOUL_01_LOOP", 0x11u);  // 【std::string构造赋值】
  sub_4015C0("WATERSOUL_CREATE", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("WATERSOUL_CAST", 0xEu);  // 【std::string构造赋值】
  v4 = 15;
  v3 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("WATERSOUL_ATK_1_READY", 0x15u);  // 【std::string构造赋值】
  v10 = 0;
  sub_416C40(v1);
  v10 = -1;
  if ( v4 >= 0x10 )
    j__free(Block);
  v4 = 15;
  v3 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("WATERSOUL_ATK_2_READY", 0x15u);  // 【std::string构造赋值】
  v10 = 1;
  sub_416C40(v1);
  v10 = -1;
  if ( v4 >= 0x10 )
    j__free(Block);
  v4 = 15;
  v3 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("WATERSOUL_ATK_1", 0xFu);  // 【std::string构造赋值】
  v10 = 2;
  sub_416C40(v1);
  v10 = -1;
  if ( v4 >= 0x10 )
    j__free(Block);
  v8 = 15;
  v7 = 0;
  LOBYTE(v6) = 0;
  sub_4015C0("WATERSOUL_ATK_2", 0xFu);  // 【std::string构造赋值】
  v10 = 3;
  sub_416C40(v5);
  v10 = -1;
  if ( v8 >= 0x10 )
    j__free(v6);
  v8 = 15;
  v7 = 0;
  LOBYTE(v6) = 0;
  v9 = 100000;
  return sub_4E1390(196613, &v9);
}



// 火精灵语音全套：FIRESOUL_* 九段播报（69L；与水精灵同构）
// ------------------------------------------------------------
// 0x5C8470 sub_5C8470
// ------------------------------------------------------------
int /*thiscall*/ sub_5C8470(uint32_t *this)
{
  int result; // eax
  uint8_t v3[4]; // [esp+Ch] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-44h]
  int v5; // [esp+20h] [ebp-34h]
  unsigned int v6; // [esp+24h] [ebp-30h]
  uint8_t v7[4]; // [esp+28h] [ebp-2Ch] BYREF
  void *v8; // [esp+2Ch] [ebp-28h]
  int v9; // [esp+3Ch] [ebp-18h]
  unsigned int v10; // [esp+40h] [ebp-14h]
  int v11; // [esp+44h] [ebp-10h] BYREF
  int v12; // [esp+50h] [ebp-4h]

  sub_4015C0("FIRESOUL_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("FIRESOUL_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("FIRESOUL_01_LOOP", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("FIRESOUL_CREATE", 0xFu);  // 【std::string构造赋值】
  sub_4015C0("FIRESOUL_CAST", 0xDu);  // 【std::string构造赋值】
  v6 = 15;
  v5 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("FIRESOUL_ATK_1_READY", 0x14u);  // 【std::string构造赋值】
  v12 = 0;
  sub_416C40(v3);
  v12 = -1;
  if ( v6 >= 0x10 )
    j__free(Block);
  v6 = 15;
  v5 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("FIRESOUL_ATK_2_READY", 0x14u);  // 【std::string构造赋值】
  v12 = 1;
  sub_416C40(v3);
  v12 = -1;
  if ( v6 >= 0x10 )
    j__free(Block);
  v6 = 15;
  v5 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("FIRESOUL_ATK_1", 0xEu);  // 【std::string构造赋值】
  v12 = 2;
  sub_416C40(v3);
  v12 = -1;
  if ( v6 >= 0x10 )
    j__free(Block);
  v10 = 15;
  v9 = 0;
  LOBYTE(v8) = 0;
  sub_4015C0("FIRESOUL_ATK_2", 0xEu);  // 【std::string构造赋值】
  v12 = 3;
  sub_416C40(v7);
  v12 = -1;
  if ( v10 >= 0x10 )
    j__free(v8);
  v10 = 15;
  v9 = 0;
  LOBYTE(v8) = 0;
  v11 = 100000;
  result = sub_4E1390(196612, &v11);
  *(this + 2186) = 0;
  return result;
}



// 暗精灵语音全套：DARKSOUL_* 九段播报（98L；this+8720..8728 相位）
// ------------------------------------------------------------
// 0x5C8650 sub_5C8650
// ------------------------------------------------------------
int /*thiscall*/ sub_5C8650(int this)
{
  int fld_2210; // ecx
  unsigned int fld_2214; // edx
  uint32_t *fld_22142; // eax
  int fld_22102; // edx
  unsigned int fld_22143; // ecx
  uint32_t *fld_22144; // eax
  uint8_t v9[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  int v11; // [esp+20h] [ebp-1Ch]
  unsigned int v12; // [esp+24h] [ebp-18h]
  int v13; // [esp+28h] [ebp-14h] BYREF
  int v14; // [esp+2Ch] [ebp-10h] BYREF
  int v15; // [esp+38h] [ebp-4h]

  sub_4015C0("DARKSOUL_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("DARKSOUL_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("DARKSOUL_01_LOOP", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("DARKSOUL_CREATE", 0xFu);  // 【std::string构造赋值】
  sub_4015C0("DARKSOUL_CAST", 0xDu);  // 【std::string构造赋值】
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("DARKSOUL_ATK_1_READY", 0x14u);  // 【std::string构造赋值】
  v15 = 0;
  sub_416C40(v9);
  v15 = -1;
  if ( v12 >= 0x10 )
    j__free(Block);
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("DARKSOUL_ATK_2_READY", 0x14u);  // 【std::string构造赋值】
  v15 = 1;
  sub_416C40(v9);
  v15 = -1;
  if ( v12 >= 0x10 )
    j__free(Block);
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("DARKSOUL_ATK_1", 0xEu);  // 【std::string构造赋值】
  v15 = 2;
  sub_416C40(v9);
  v15 = -1;
  if ( v12 >= 0x10 )
    j__free(Block);
  v12 = 15;
  v11 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("DARKSOUL_ATK_2", 0xEu);  // 【std::string构造赋值】
  v15 = 3;
  sub_416C40(v9);
  v15 = -1;
  if ( v12 >= 0x10 )
    j__free(Block);
  fld_2210 = *(uint32_t *)(this + 8720);
  v14 = 2;
  if ( fld_2210 != 0 )
    fld_2214 = (*(uint32_t *)(this + 8724) - fld_2210) >> 2;
  else
    fld_2214 = 0;
  if ( fld_2210 != 0 && fld_2214 < (*(uint32_t *)(this + 8728) - fld_2210) >> 2 )
  {
    fld_22142 = *(uint32_t **)(this + 8724);
    *fld_22142 = 2;
    *(uint32_t *)(this + 8724) = fld_22142 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 8724), 1, (int)&v14);
  }
  fld_22102 = *(uint32_t *)(this + 8720);
  v14 = 3;
  if ( fld_22102 != 0 )
    fld_22143 = (*(uint32_t *)(this + 8724) - fld_22102) >> 2;
  else
    fld_22143 = 0;
  if ( fld_22102 != 0 && fld_22143 < (*(uint32_t *)(this + 8728) - fld_22102) >> 2 )
  {
    fld_22144 = *(uint32_t **)(this + 8724);
    *fld_22144 = 3;
    *(uint32_t *)(this + 8724) = fld_22144 + 1;
  }
  else
  {
    sub_430C80(*(void **)(this + 8724), 1, (int)&v14);
  }
  v13 = 100000;
  return sub_4E1390(196615, &v13);
}



// 精灵死亡特效分派（307L 全文件最大）：Monster/Spirit/{Water,Fire,Dark,Light}Animation/
//   Die.ani 四色分派 + LightAnimation/DieGlow.ani 光辉死亡（RTTI cast 分型）
// ------------------------------------------------------------
// 0x5C88C0 sub_5C88C0
// ------------------------------------------------------------
void /*userpurge*/ sub_5C88C0(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)
{
  int v6; // edi
  int pObj; // eax
  int pObj4; // edi
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  char *v17; // eax
  int pObj3; // edi
  int v19; // ebx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  uint32_t *v25; // eax
  int v26; // eax
  unsigned int v27; // ebx
  int v28; // eax
  int v29; // edx
  unsigned int v30; // ecx
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int pObj2; // edi
  int v36; // ebx
  int v37; // eax
  bool v38; // sf
  bool v39; // of
  int v40; // ebx
  int v41; // eax
  int v42; // eax
  int v43; // eax
  int *v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // [esp-18h] [ebp-44h]
  int v48; // [esp-14h] [ebp-40h]
  int v49; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  int v51; // [esp+10h] [ebp-1Ch]
  int v52; // [esp+14h] [ebp-18h]
  int v53; // [esp+18h] [ebp-14h]
  int pObj42; // [esp+1Ch] [ebp-10h] BYREF
  int v55; // [esp+28h] [ebp-4h]
  int ArgLista; // [esp+34h] [ebp+8h]
  int ArgListb; // [esp+34h] [ebp+8h]
  int ArgListc; // [esp+34h] [ebp+8h]
  int ArgListd; // [esp+34h] [ebp+8h]
  int v60; // [esp+38h] [ebp+Ch]
  int v61; // [esp+38h] [ebp+Ch]
  int v62; // [esp+38h] [ebp+Ch]
  int v63; // [esp+38h] [ebp+Ch]

  v6 = ArgList;
  if ( ArgList == 14 )
  {
    v44 = *(int **)(pArg4 + 4);
    v48 = v44[1];
    v47 = *v44;
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
    v45 = sub_45EBE0(v47, v48);
    v46 = __RTDynamicCast(v45, 0, &CNRDObject `RTTI Type Descriptor', &CNDecoy `RTTI Type Descriptor', 0);
    pDwArg1[2184] = v46;
    if ( v46 != 0 )
      sub_4D83E0(pDwArg1, 0, 0);
  }
  else
  {
    if ( ArgList == 16 )
    {
      pDwArg1[2184] = 0;
      return;
    }
    if ( ArgList == 18 )
    {
      v53 = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 8);
      Block = nullptr;
      v51 = 0;
      v52 = 0;
      v55 = 0;
      v60 = 0;
      if ( v53 > 0 )
      {
        do
        {
          pObj = sub_45EBE0(
                 *(uint32_t *)(8 * v60 + *(uint32_t *)(pArg4 + 4) + 12),
                 *(uint32_t *)(8 * v60 + *(uint32_t *)(pArg4 + 4) + 16));
          pObj4 = pObj;
          if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
          {
            pObj42 = pObj4;
            sub_4E7BA0(&v49, &pObj42);
          }
          ++v60;
        }
        while ( v60 < v53 );
        v6 = ArgList;
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int *))(*pDwArg1 + 1324))(
        pDwArg1,
        **(uint32_t **)(pArg4 + 4),
        *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4),
        &v49);
      if ( *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4) != 0 )
        (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 1256))(pDwArg1);
      else
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*pDwArg1 + 560))(pDwArg1, 13, 0, 2, 0);
      v55 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v51 = 0;
      v52 = 0;
    }
    sub_4E33D0((int)pDwArg1, pArg4, fArg2, v6, pArg4, *(float *)&nArg5, *(float *)&nArg6);
    switch ( v6 )
    {
      case 5:
        ArgLista = 0;
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, 0);
        switch ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 340))(pDwArg1) )
        {
          case 0x258:
            v61 = sub_42FCB0(228);
            v55 = 1;
            if ( v61 == 0 )
              goto LABEL_24;
            v11 = sub_431860((char)"Monster/Spirit/WaterAnimation/Die.ani", 1);
            v55 = -1;
            v12 = v11;
            goto LABEL_32;
          case 0x259:
            v62 = sub_42FCB0(228);
            v55 = 2;
            if ( v62 == 0 )
              goto LABEL_24;
            v13 = sub_431860((char)"Monster/Spirit/FireAnimation/Die.ani", 1);
            v55 = -1;
            v12 = v13;
            goto LABEL_32;
          case 0x25A:
            v63 = sub_42FCB0(228);
            v55 = 3;
            if ( v63 != 0 )
            {
              v14 = sub_431860((char)"Monster/Spirit/DarkAnimation/Die.ani", 1);
              v55 = -1;
              v12 = v14;
            }
            else
            {
LABEL_24:
              v55 = -1;
              v12 = 0;
            }
            goto LABEL_32;
          case 0x25B:
            ArgListb = sub_42FCB0(228);
            v55 = 4;
            if ( ArgListb != 0 )
              v15 = sub_431860((char)"Monster/Spirit/LightAnimation/Die.ani", 1);
            else
              v15 = 0;
            v55 = -1;
            v12 = v15;
            ArgListc = sub_42FCB0(228);
            v55 = 5;
            if ( ArgListc != 0 )
              v16 = sub_431860((char)"Monster/Spirit/LightAnimation/DieGlow.ani", 1);
            else
              v16 = 0;
            v55 = -1;
            ArgLista = v16;
LABEL_32:
            if ( v12 != 0 )
            {
              v17 = (char *)sub_44B6C0(284);
              pObj3 = (int)v17;
              v55 = 6;
              if ( v17 != nullptr )
              {
                sub_44E0D0(v17, v12, 1);
                *(uint32_t *)pObj3 = &CNRDPooledObject::`vftable';
              }
              else
              {
                pObj3 = 0;
              }
              v55 = -1;
              if ( ArgLista != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj3 + 204))(
                  pObj3,
                  100,
                  ArgLista,
                  0,
                  0,
                  0,
                  0);
              sub_45FE80(pDwArg1[29], pObj3, 2, 0, pObj3, (int)pDwArg1, 0);
              v19 = *(uint32_t *)pObj3;
              v20 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
              v21 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v20);
              v22 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v21);
              (*(void (/*thiscall*/ **)(int, int))(v19 + 112))(pObj3, v22);
              v23 = *(uint32_t *)pObj3;
              v24 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
              (*(void (/*thiscall*/ **)(int, int))(v23 + 144))(pObj3, v24);
            }
            break;
          default:
            return;
        }
        return;
      case 17:
        if ( (unsigned int)pDwArg1[2170] < 0x10 )
          v25 = pDwArg1 + 2165;
        else
          v25 = (uint32_t *)pDwArg1[2165];
        goto LABEL_44;
      case 8:
        *((uint8_t *)pDwArg1 + 8732) = 0;
        v26 = pDwArg1[2172];
        if ( v26 != 0 )
          v27 = (pDwArg1[2173] - v26) / 28;
        else
          v27 = 0;
        if ( v27 <= sub_41A5E0((unsigned int)(pDwArg1 + 1757)) )
          return;
        v28 = 28 * sub_41A5E0((unsigned int)(pDwArg1 + 1757));
        v29 = pDwArg1[2172];
        v30 = *(uint32_t *)(v28 + v29 + 24);
        v31 = v29 + v28;
        if ( v30 < 0x10 )
          v25 = (uint32_t *)(v31 + 4);
        else
          v25 = *(uint32_t **)(v31 + 4);
LABEL_44:
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, v25, -1, 0, 0);
        return;
      case 15:
        if ( pDwArg1[2184] != 0 )
        {
          v32 = (unsigned int)pDwArg1[2170] < 0x10 ? (int)(pDwArg1 + 2165) : pDwArg1[2165];
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, v32, -1, 0, 0);
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(
            pDwArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
          v33 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 688))(pDwArg1);
          sub_4926A0(**(uint32_t **)(v33 + 56));
          v34 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 688))(pDwArg1);
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, **(uint32_t **)(v34 + 56));
          sub_617370(pDwArg1);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2184] + 312))(pDwArg1[2184], 0);
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
            (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1104))(pDwArg1, 13);
        }
        break;
      case 19:
        pDwArg1[2185] = sub_699000((int)(pDwArg1 + 2));  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(
          pDwArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 604))(pDwArg1, 0);
        pObj2 = sub_45EBE0(**(uint32_t **)(pArg4 + 4), *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4));
        if ( pObj2 != 0 )
        {
          v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);
          v37 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);
          v39 = __OFSUB__(v37, v36);
          v38 = v37 - v36 < 0;
          v40 = *pDwArg1;
          ArgListd = v38 == v39 ? 70 : -70;
          v41 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
          v42 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 124))(pObj2, v41);
          v43 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v42);
          (*(void (/*thiscall*/ **)(int *, int))(v40 + 108))(pDwArg1, ArgListd + v43);
        }
        break;
      default:
        break;
    }
  }
}


// AI 字段访问（this+8744）
// ------------------------------------------------------------
// 0x5C8EE0 sub_5C8EE0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C8EE0(int this, unsigned int ArgList, float fArg3, int nArg4, int nArg5)
{
  if ( ArgList == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 1 )
    *(uint8_t *)(this + 8744) = 0;
  return sub_5C88C0((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5C8F20 sub_5C8F20
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C8F20(uint32_t *this, unsigned int ArgList, float fArg3, int nArg4, int nArg5)
{
  return sub_5C88C0(this, ArgList, fArg3, nArg4, nArg5);
}



// AI 字段访问（this+8748）
// ------------------------------------------------------------
// 0x5C8F30 sub_5C8F30
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5C8F30(int this, unsigned int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v5; // eax

  if ( ArgList == 8 )
  {
    v5 = **(uint32_t **)(LODWORD(fArg3) + 4);
    if ( v5 >= 2 && v5 <= 3 )
      *(uint8_t *)(this + 8748) = 1;
  }
  return sub_5C88C0((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);
}



// 硬直字段（this+204）
// ------------------------------------------------------------
// 0x5C8F70 sub_5C8F70
// ------------------------------------------------------------
int /*thiscall*/ sub_5C8F70(uint32_t *this, unsigned int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  result = sub_5C88C0(this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 1 )
    {
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
               this,
               100,
               *(uint32_t *)(*(this + 1554) + 12),
               0,
               0,
               0,
               0);
    }
  }
  return result;
}



// 光精灵语音全套：LIGHTSOUL_* 九段播报 + Monster/Spirit/Light1Glow.equ 发光外观（115L）
// ------------------------------------------------------------
// 0x5C8FE0 sub_5C8FE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C8FE0(int *this)
{
  int fld_e2180; // ecx
  unsigned int fld_e2181; // edx
  uint32_t *fld_e21812; // eax
  int fld_e21802; // edx
  unsigned int fld_e21813; // ecx
  uint32_t *fld_e21814; // eax
  void *pMem; // eax
  char *v9; // eax
  int v10; // edx
  int result; // eax
  uint8_t v12[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  int v14; // [esp+20h] [ebp-1Ch]
  unsigned int v15; // [esp+24h] [ebp-18h]
  int v16; // [esp+28h] [ebp-14h] BYREF
  void *pMem2; // [esp+2Ch] [ebp-10h] BYREF
  int v18; // [esp+38h] [ebp-4h]

  sub_4015C0("LIGHTSOUL_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("LIGHTSOUL_DIE", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("LIGHTSOUL_01_LOOP", 0x11u);  // 【std::string构造赋值】
  sub_4015C0("LIGHTSOUL_CREATE", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("LIGHTSOUL_CAST", 0xEu);  // 【std::string构造赋值】
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("LIGHTSOUL_ATK_1_READY", 0x15u);  // 【std::string构造赋值】
  v18 = 0;
  sub_416C40(v12);
  v18 = -1;
  if ( v15 >= 0x10 )
    j__free(Block);
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("LIGHTSOUL_ATK_2_READY", 0x15u);  // 【std::string构造赋值】
  v18 = 1;
  sub_416C40(v12);
  v18 = -1;
  if ( v15 >= 0x10 )
    j__free(Block);
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("LIGHTSOUL_ATK_1", 0xFu);  // 【std::string构造赋值】
  v18 = 2;
  sub_416C40(v12);
  v18 = -1;
  if ( v15 >= 0x10 )
    j__free(Block);
  v15 = 15;
  v14 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0("LIGHTSOUL_ATK_2", 0xFu);  // 【std::string构造赋值】
  v18 = 3;
  sub_416C40(v12);
  v18 = -1;
  if ( v15 >= 0x10 )
    j__free(Block);
  fld_e2180 = *(this + 2180);
  pMem2 = (void *)2;
  if ( fld_e2180 != 0 )
    fld_e2181 = (*(this + 2181) - fld_e2180) >> 2;
  else
    fld_e2181 = 0;
  if ( fld_e2180 != 0 && fld_e2181 < (*(this + 2182) - fld_e2180) >> 2 )
  {
    fld_e21812 = (uint32_t *)*(this + 2181);
    *fld_e21812 = 2;
    *(this + 2181) = (int)(fld_e21812 + 1);
  }
  else
  {
    sub_430C80((void *)*(this + 2181), 1, (int)&pMem2);
  }
  fld_e21802 = *(this + 2180);
  pMem2 = (void *)4;
  if ( fld_e21802 != 0 )
    fld_e21813 = (*(this + 2181) - fld_e21802) >> 2;
  else
    fld_e21813 = 0;
  if ( fld_e21802 != 0 && fld_e21813 < (*(this + 2182) - fld_e21802) >> 2 )
  {
    fld_e21814 = (uint32_t *)*(this + 2181);
    *fld_e21814 = 4;
    *(this + 2181) = (int)(fld_e21814 + 1);
  }
  else
  {
    sub_430C80((void *)*(this + 2181), 1, (int)&pMem2);
  }
  v16 = 100000;
  sub_4E1390(196614, &v16);
  pMem = operator new(0x544u);
  pMem2 = pMem;
  v18 = 4;
  if ( pMem != nullptr )
    v9 = sub_4BA9E0((char *)pMem, "Monster/Spirit/Light1Glow.equ", 0);
  else
    v9 = nullptr;
  v10 = *this;
  v18 = -1;
  result = (*(int (/*thiscall*/ **)(int *, char *))(v10 + 784))(this, v9);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C92A0 sub_5C92A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C92A0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2157)(uint32_t, int); // ecx
  int result; // eax

  fld_e2157 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2157);
  if ( fld_e2157 != nullptr )
    result = (**fld_e2157)(fld_e2157, 1);
  *(this + 2157) = 0;
  return result;
}



// 死亡/终局钩：调 sub_4E4430 = HP 受击处理器（研究 31 Boss 终局长震族, 20L）
// ------------------------------------------------------------
// 0x5C92D0 sub_5C92D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C92D0(int this, int nArg2, int nArg3, char pszArg4)  // 【调 sub_4E4430（HP 受击处理器/Boss 终局族）】
{
  int result; // eax
  int pThis_50; // eax

  sub_4E4430((char *)this, nArg2, nArg3, pszArg4);  // 【HP 受击处理器含 Boss 终局（研究 P35 第 31 轮）】
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this);
  if ( (uint8_t)result != 0 && *(uint32_t *)(this + 7772) == 3 )
  {
    pThis_50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 80))(this);
    return sub_424120(*(uint32_t **)(pThis_50 + 132), 4, 1000);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9320 sub_5C9320
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9320(void *this, int nArg2, int nArg3)
{
  int pThis_98; // eax

  pThis_98 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this);
  return sub_4DAE50((pThis_98 != 0 ? 90 : -90) + nArg2, nArg3);
}



// ============================================================
// 【分区 5】章鱼陷阱与莲花（Trap Octopus / Lotus）（0x5C9360-0x5CBC00）
// 证据：TRAP_OCTOPUS_READY/TIGHTEN/SWING 触手三连、LOTUS_DIE/BREAK/TWIST/READY/ATK/SWEEP/
//       SWEEP_LOOP/READY_LOOP/LAUGH/DMG 全套 + R_BELIEVER_ALERT（莲花=信徒伪装!）、
//       Particle/PoisonBug.ptl + TRAP_GRASS_UP 草丛升起、Particle/DieSmoke.ptl

// AI 字段访问（this+8624）
// ------------------------------------------------------------
// 0x5C9360 sub_5C9360
// ------------------------------------------------------------
bool /*thiscall*/ sub_5C9360(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  return *(this + 8624) != 0 || (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 5;
}



// AI 字段访问（this+8624）
// ------------------------------------------------------------
// 0x5C9380 sub_5C9380
// ------------------------------------------------------------
bool /*thiscall*/ sub_5C9380(uint8_t *this, int nArg2)
{
  return *(this + 8624) != 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9390 sub_5C9390
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9390(int *this, int nArg2, int nArg3, int nArg4, int nArg5, void *Block, int nArg7)
{
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax

  v8 = *this;
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v9);
  v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10);
  (*(void (/*thiscall*/ **)(int *, int))(v8 + 112))(this, v11 - 230);
  sub_4E22E0(nArg2, nArg3, nArg4, nArg5, Block, nArg7);
  v12 = *this;
  v13 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v13);
  v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v14);
  return (*(int (/*thiscall*/ **)(int *, int))(v12 + 112))(this, v15 + 230);
}



// 触手就绪：TRAP_OCTOPUS_READY 播报（83L；RTTI cast 触发判定）
// ------------------------------------------------------------
// 0x5C9410 sub_5C9410
// ------------------------------------------------------------
char /*thiscall*/ sub_5C9410(void *this, int nArg2, int pArg3)
{
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int pObj; // esi
  int *v8; // ebx
  int v9; // eax
  int v11; // [esp-20h] [ebp-28h]
  int v12; // [esp-1Ch] [ebp-24h]
  int v13; // [esp+4h] [ebp-4h]
  int v14; // [esp+10h] [ebp+8h]

  if ( nArg2 == 16 )
  {
    v4 = 0;
    do
    {
      v5 = *(uint32_t *)(pArg3 + 4);
      v13 = v4 + 12;
      v12 = *(uint32_t *)(v4 + v5 + 4);
      v14 = *(uint32_t *)(v4 + 12 + v5 - 4);
      v11 = *(uint32_t *)(v4 + v5);
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
      v6 = sub_45EBE0(v11, v12);
      pObj = __RTDynamicCast(v6, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
      if ( pObj != 0 )
      {
        v8 = &dword_730C10;
        while ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 776))(pObj, *v8) == 0 )
        {
          if ( (int)++v8 >= (int)dword_730C1C )
          {
            if ( pObj == dword_8F7C04 )
            {
              v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 792))(dword_8F7C04, 16);
              if ( __RTDynamicCast(
                     v9,
                     0,
                     &CNRDEquipment `RTTI Type Descriptor',
                     &CNEquipmentHyperJammer `RTTI Type Descriptor',
                     0) == 0 )
                (*(void (/*thiscall*/ **)(int, int, int, void *, uint32_t))(*(uint32_t *)dword_8F7C04 + 764))(
                  dword_8F7C04,
                  v14,
                  8,
                  this,
                  0);
            }
            else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int, void *, uint32_t))(*(uint32_t *)pObj + 764))(pObj, v14, 8, this, 0);
            }
            break;
          }
        }
      }
      v4 = v13;
    }
    while ( *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + v13) != 0xFFFF );
    return 1;
  }
  else if ( nArg2 == 15 )
  {
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TRAP_OCTOPUS_READY",
      -1,
      0,
      0);
    return 1;
  }
  else
  {
    return 0;
  }
}



// 触手复合 AI（191L；this+204/+208 硬直节拍 + 8653/8654 相位）
// ------------------------------------------------------------
// 0x5C9550 sub_5C9550
// ------------------------------------------------------------
char /*thiscall*/ sub_5C9550(uint32_t *this, int nArg2)
{
  char result; // al
  int savedregs; // [esp+8h] [ebp+0h]
  int savedregsa; // [esp+8h] [ebp+0h]

  switch ( nArg2 )
  {
    case 0:
    case 4:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                 this,
                 -600,
                 *(uint32_t *)(*(this + 1554) + 40),
                 0,
                 0,
                 0,
                 0);
      break;
    case 1:
    case 5:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                 this,
                 -100,
                 *(uint32_t *)(*(this + 1554) + 44),
                 0,
                 0,
                 0,
                 0);
      break;
    case 2:
    case 6:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
      savedregs = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*this + 204))(
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 48),
        0);
      goto LABEL_6;
    case 3:
    case 7:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
      savedregsa = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*this + 204))(
        this,
        300,
        *(uint32_t *)(*(this + 1554) + 52),
        0);
LABEL_6:
      result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1550) + 4 * nArg2));
      break;
    case 8:
    case 12:
    case 13:
    case 14:
    case 15:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -600,
        *(uint32_t *)(*(this + 1554) + 40),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -100,
        *(uint32_t *)(*(this + 1554) + 44),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 48),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
                 this,
                 300,
                 *(uint32_t *)(*(this + 1554) + 52),
                 0,
                 0,
                 0,
                 0);
      break;
    case 9:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -600,
        *(uint32_t *)(*(this + 1554) + 40),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -100,
        *(uint32_t *)(*(this + 1554) + 44),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 48),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        300,
        *(uint32_t *)(*(this + 1554) + 52),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 128));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 132));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 136));
      result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 140));
      break;
    case 16:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -600,
        *(uint32_t *)(*(this + 1554) + 40),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -100,
        *(uint32_t *)(*(this + 1554) + 44),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 48),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        300,
        *(uint32_t *)(*(this + 1554) + 52),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 68));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 64));
      *((uint8_t *)this + 8653) = 0;
      *((uint8_t *)this + 8654) = 0;
      result = sub_698F90((int)(this + 2160), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      break;
    default:
      return result;
  }
  return result;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5C9A00 sub_5C9A00
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9A00(uint32_t *this)
{
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 56));
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 56));
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9A30 sub_5C9A30
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9A30(uint32_t *this)
{
  unsigned int v1; // edi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // esi
  int v13; // [esp+Ch] [ebp-4h]

  v1 = 0;
  v13 = 0;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj2 = *(uint32_t *)(v6 + 4 * v1);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && v1 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        pObj = *(uint32_t *)(v9 + 4 * v1);
      else
        pObj = 0;
      if ( sub_5B46A0(pObj) )
      {
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
        if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
          ++v13;
      }
    }
    ++v1;
  }
  return v13;
}



// RTTI cast 目标解算（67L）
// ------------------------------------------------------------
// 0x5C9AF0 sub_5C9AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9AF0(int *this)
{
  char v2; // bl
  unsigned int i; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax
  int v8; // eax
  int v9; // edx
  int pObj2; // ecx
  int v11; // eax
  int v12; // edx
  int pObj; // ecx
  int v14; // eax

  v2 = 1;
  for ( i = 0; ; ++i )
  {
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v4 + 4;
    result = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
    v9 = *(uint32_t *)(v8 + 8);
    if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
      pObj2 = *(uint32_t *)(v9 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
      v12 = *(uint32_t *)(v11 + 8);
      if ( v12 != 0 && i < (*(uint32_t *)(v11 + 12) - v12) >> 2 )
        pObj = *(uint32_t *)(v12 + 4 * i);
      else
        pObj = 0;
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, 16);
      if ( __RTDynamicCast(
             v14,
             0,
             &CNRDEquipment `RTTI Type Descriptor',
             &CNEquipmentHyperJammer `RTTI Type Descriptor',
             0) == 0 )
        v2 = 0;
    }
  }
  if ( v2 != 0 )
  {
    result = *(this + 1908);
    if ( result == 0 )
      *(uint8_t *)(*(this + 1905) + 512) = 0;
  }
  else
  {
    *(uint8_t *)(*(this + 1905) + 512) = 1;
  }
  return result;
}



// 硬直联动 AI（this+204/+208, 72L）
// ------------------------------------------------------------
// 0x5C9BE0 sub_5C9BE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5C9BE0(uint32_t *this, int nArg2, int pArg3)
{
  int result; // eax
  int v5; // ebx
  uint32_t *fld_e1554; // eax
  int v7; // ecx
  int v8; // ebx

  result = nArg2;
  if ( nArg2 == pArg3 + 4 )
  {
    v5 = 4 * pArg3 + 112;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(v5 + *(this + 1554)));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      dword_730C90[pArg3],
      *(uint32_t *)(v5 + *(this + 1554)),
      0,
      0,
      0,
      0);
    if ( *(this + 2159) == -1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(4 * pArg3 + 80 + *(this + 1554)));
      fld_e1554 = (uint32_t *)(4 * pArg3 + 80 + *(this + 1554));
      v7 = dword_730C70[pArg3];
LABEL_7:
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        v7,
        *fld_e1554,
        0,
        0,
        0,
        0);
      result = sub_4924C0(0);
      *(uint32_t *)(result + 48) = 500;
      return result;
    }
  }
  else
  {
    if ( nArg2 != pArg3 )
      return result;
    v8 = 4 * pArg3 + 128;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(v8 + *(this + 1554)));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      dword_730CA0[pArg3],
      *(uint32_t *)(v8 + *(this + 1554)),
      0,
      0,
      0,
      0);
    if ( *(this + 2159) == -1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(4 * pArg3 + 96 + *(this + 1554)));
      fld_e1554 = (uint32_t *)(4 * pArg3 + 96 + *(this + 1554));
      v7 = dword_730C80[pArg3];
      goto LABEL_7;
    }
  }
  result = sub_4924C0(0);
  *(uint32_t *)(result + 48) = 70;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9D60 sub_5C9D60
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5C9D60(uint32_t *this, int nArg2, int nArg3)
{
  bool v3; // zf
  uint8_t *result; // eax

  if ( nArg2 != 0 )
  {
    if ( nArg2 <= 0 || nArg2 > 2 )
      goto LABEL_8;
    v3 = nArg3 == 0;
  }
  else
  {
    v3 = nArg3 == 2;
  }
  if ( v3 )
    *(this + 2152) /= 2;
LABEL_8:
  if ( nArg3 != 0 )
  {
    result = (uint8_t *)(nArg3 - 2);
    if ( nArg3 == 2 )
      *(this + 1891) = 0;
  }
  else
  {
    result = (uint8_t *)(*(this + 1905) + 512);
    *(this + 1892) = 0;
    *result = 0;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5C9DD0 sub_5C9DD0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5C9DD0(uint32_t *this, int nArg2, int nArg3)
{
  bool v3; // zf
  uint8_t *result; // eax

  if ( nArg2 != 0 )
  {
    if ( nArg2 <= 0 || nArg2 > 2 )
      goto LABEL_8;
    v3 = nArg3 == 0;
  }
  else
  {
    v3 = nArg3 == 2;
  }
  if ( v3 )
    *(this + 2152) *= 2;
LABEL_8:
  if ( nArg3 != 0 )
  {
    result = (uint8_t *)(nArg3 - 2);
    if ( nArg3 == 2 )
      *(this + 1891) = 2;
  }
  else
  {
    result = (uint8_t *)(*(this + 1905) + 512);
    *(this + 1892) = 1;
    *result = 1;
  }
  return result;
}



// 莲花死亡：LOTUS_DIE + LOTUS_BREAK 播报（105L；this+204/+208 节拍）
// ------------------------------------------------------------
// 0x5C9E30 sub_5C9E30
// ------------------------------------------------------------
void /*thiscall*/ sub_5C9E30(uint32_t *this)
{
  int v2; // edx
  int v3; // edi
  int v4; // edi
  int v5; // ebx
  int v6; // edx
  int v7; // eax
  void *fld_e29; // ecx
  int fld_e2155; // [esp-4h] [ebp-30h]
  uint8_t v10[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int fld_e2157; // [esp+1Ch] [ebp-10h]
  int v13; // [esp+28h] [ebp-4h]

  sub_432EA0("LOTUS_DIE", -1, 0, 0);
  sub_432EA0("LOTUS_BREAK", -1, 0, 0);
  v2 = *this;
  fld_e2155 = *(this + 2155);
  *(this + 1545) = fld_e2155;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v2 + 196))(this, fld_e2155);
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 ? 90 : -90;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v3;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 120;
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2157) + 12))(*(this + 2157), 0);
  v6 = *this;
  fld_e2157 = *(uint32_t *)*(this + 2157);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v6 + 124))(this, v5);
  (*(void (/*thiscall*/ **)(uint32_t, int, int))(fld_e2157 + 40))(*(this + 2157), v4, v7 + 2);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2157) + 92))(*(this + 2157), v10);
  fld_e29 = (void *)*(this + 29);
  v13 = 0;
  sub_4600B0(fld_e29, 2, 0, (int)v10);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 8));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -500,
    *(uint32_t *)(*(this + 1554) + 20),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -400,
    *(uint32_t *)(*(this + 1554) + 24),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -300,
    *(uint32_t *)(*(this + 1554) + 28),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 32));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(uint32_t *)(*(this + 1554) + 32),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 36));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(uint32_t *)(*(this + 1554) + 36),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 60));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    100,
    *(uint32_t *)(*(this + 1554) + 60),
    0,
    0,
    0,
    0);
  if ( Block != nullptr )
    j__free(Block);
}



// 触手挥击（175L）：TRAP_OCTOPUS_SWING + LOTUS_TWIST + LOTUS_READY 三段播报
//   （this+204/+208/8616 相位 —— 章鱼陷阱与莲花共演）
// ------------------------------------------------------------
// 0x5CA150 sub_5CA150
// ------------------------------------------------------------
void /*thiscall*/ sub_5CA150(uint32_t *this, int nArg2)
{
  int fld_e1554; // eax
  int v4; // edx
  uint32_t *fld_e15542; // eax
  int fld_e15543; // eax
  int v7; // edx

  *((uint8_t *)this + 8616) = 0;
  switch ( nArg2 )
  {
    case 0:
    case 4:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "TRAP_OCTOPUS_SWING",
        -1,
        0,
        0);
      sub_5C9BE0(this, nArg2, 0);
      return;
    case 1:
    case 5:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "TRAP_OCTOPUS_SWING",
        -1,
        0,
        0);
      sub_5C9BE0(this, nArg2, 1);
      return;
    case 2:
    case 6:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "TRAP_OCTOPUS_SWING",
        -1,
        0,
        0);
      sub_5C9BE0(this, nArg2, 2);
      return;
    case 3:
    case 7:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "TRAP_OCTOPUS_SWING",
        -1,
        0,
        0);
      sub_5C9BE0(this, nArg2, 3);
      return;
    case 8:
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "LOTUS_TWIST", -1, 0, 0);
      goto LABEL_11;
    case 9:
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "TRAP_OCTOPUS_SWING",
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 128));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -600,
        *(uint32_t *)(*(this + 1554) + 128),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 132));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -100,
        *(uint32_t *)(*(this + 1554) + 132),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 136));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        200,
        *(uint32_t *)(*(this + 1554) + 136),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 140));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        300,
        *(uint32_t *)(*(this + 1554) + 140),
        0,
        0,
        0,
        0);
      return;
    case 10:
      fld_e1554 = *(this + 1554);
      v4 = *this;
      *(this + 2158) = 6;
      *(this + 2159) = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 208))(this, *(uint32_t *)(fld_e1554 + 72));
      fld_e15542 = (uint32_t *)(*(this + 1554) + 72);
      goto LABEL_9;
    case 11:
      fld_e15543 = *(this + 1554);
      v7 = *this;
      *(this + 2158) = 6;
      *(this + 2159) = 1;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v7 + 208))(this, *(uint32_t *)(fld_e15543 + 76));
      fld_e15542 = (uint32_t *)(*(this + 1554) + 76);
LABEL_9:
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -200,
        *fld_e15542,
        0,
        0,
        0,
        0);
      break;
    case 12:
    case 13:
    case 14:
    case 15:
LABEL_11:
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "LOTUS_READY", -1, 0, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
      break;
    case 16:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 40));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 44));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 48));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 52));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 68));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        -200,
        *(uint32_t *)(*(this + 1554) + 68),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 64));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        400,
        *(uint32_t *)(*(this + 1554) + 64),
        0,
        0,
        0,
        0);
      break;
    default:
      return;
  }
}


// 大型触发 AI（287L 全文件第二；this+8624 相位 —— 陷阱触发→撕咬循环【推断】）
// ------------------------------------------------------------
// 0x5CA5F0 sub_5CA5F0
// ------------------------------------------------------------
char /*thiscall*/ sub_5CA5F0(uint8_t *this, int pArg2)
{
  int pArg22; // ebx
  int v4; // edi
  int v5; // ecx
  int nRand; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int nRand2; // edx
  int v15; // ebx
  int nRand3; // eax
  int pObj; // ecx
  int v18; // ebx
  int nRand5; // eax
  int v20; // ebx
  int v21; // eax
  int pThis_34; // eax
  int v23; // edx
  int pThis_342; // eax
  int nRand6; // eax
  int pObj2; // ecx
  int v27; // ebx
  int nRand7; // eax
  int pObj5; // ecx
  int v30; // ebx
  int nRand8; // eax
  int pObj3; // ecx
  int v33; // ebx
  int nRand9; // edx
  int v35; // ebx
  int v36; // eax
  int v37; // edx
  int v38; // ecx
  int v39; // ebx
  int v40; // ebx
  int nRand10; // eax
  int pObj6; // ecx
  int v43; // ebx
  int nRand11; // ebx
  int v46; // eax
  int v47; // eax
  int nRand12; // eax
  int pThis_50; // eax
  char result; // al
  int v51; // [esp-18h] [ebp-54h]
  int pThis_178; // [esp-4h] [ebp-40h]
  uint32_t v53[3]; // [esp+Ch] [ebp-30h]
  int pThis_2A0; // [esp+18h] [ebp-24h]
  int nRand4; // [esp+1Ch] [ebp-20h]
  int v56; // [esp+20h] [ebp-1Ch]
  int j; // [esp+24h] [ebp-18h]
  int pObj4; // [esp+28h] [ebp-14h]
  int i; // [esp+2Ch] [ebp-10h]
  unsigned int v60; // [esp+30h] [ebp-Ch]
  int nRand92; // [esp+34h] [ebp-8h]
  char v62; // [esp+3Bh] [ebp-1h]

  pArg22 = pArg2;
  v62 = 0;
  v56 = 1000;
  while ( 1 )
  {
    v4 = 0;
    v60 = 0;
    while ( 1 )
    {
      v5 = *(uint32_t *)(pArg22 + 4);
      if ( v5 == 0 || v60 >= (*(uint32_t *)(pArg22 + 8) - v5) >> 2 )
        break;
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v5 + v4) + 40))(*(uint32_t *)(v5 + v4), 17) == 0
        || (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + *(uint32_t *)(pArg22 + 4)) + 724))(*(uint32_t *)(v4 + *(uint32_t *)(pArg22 + 4))) == 1 )
      {
LABEL_35:
        ++v60;
        v4 += 4;
      }
      else
      {
        switch ( sub_41A5E0((unsigned int)(this + 7028)) )
        {
          case 12:
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) == 0 || rand() % 100 >= 75 )
              goto LABEL_35;
            nRand = rand() % 2;
            j = *(uint32_t *)(v4 + *(uint32_t *)(pArg22 + 4));
            pObj4 = j;
            i = j;
            v7 = *(uint32_t *)this;
            nRand4 = j;
            nRand92 = v7;
            v8 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, bool, int, int, uint32_t, uint32_t))(v7 + 52))(
                   this,
                   0,
                   nRand == 0,
                   200,
                   1,
                   0,
                   0);
            v9 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)j + 124))(j, 30028, v8);
            v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 120))(pObj4, v9);
            v11 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)i + 124))(i, 450, v10);
            v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nRand4 + 120))(nRand4, v11);
            (*(void (/*thiscall*/ **)(uint8_t *, int))(nRand92 + 584))(this, v12);
            v13 = *(uint32_t *)this;
            v62 = 1;
            (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t))(v13 + 560))(this, 15, 0, 0, 0);
            ++v60;
            v4 += 4;
            break;
          case 13:
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) == 0 || rand() % 100 >= 75 )
              goto LABEL_35;
            nRand2 = rand() % 3 + 2;
            if ( nRand2 > 0 )
            {
              for ( i = nRand2; i != 0; --i )
              {
                v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + *(uint32_t *)(pArg22 + 4)) + 120))(*(uint32_t *)(v4 + *(uint32_t *)(pArg22 + 4)));
                nRand3 = rand();
                pObj = *(uint32_t *)(v4 + *(uint32_t *)(pArg2 + 4));
                j = v15 + nRand3 % 140 - 71;
                v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
                nRand4 = v18 + rand() % 100 - 51;
                nRand5 = rand();
                nRand92 = *(uint32_t *)this;
                v20 = nRand5 % 200 + 399;
                v21 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(nRand92 + 152))(this, 200, 1, 0, 0);
                pThis_34 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, int))(*(uint32_t *)this + 52))(this, 0, v21);
                (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int, int, int, int))(nRand92 + 584))(
                  this,
                  j,
                  nRand4,
                  v20,
                  j,
                  nRand4,
                  30029,
                  pThis_34);
                pArg22 = pArg2;
              }
            }
            v23 = *(uint32_t *)this;
            v62 = 1;
            (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t))(v23 + 560))(this, 15, 0, 0, 0);
            ++v60;
            v4 += 4;
            break;
          case 14:
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0 )
            {
              for ( i = 5; i != 0; --i )
              {
                if ( rand() % 100 < 75 )
                {
                  nRand6 = rand();
                  pObj2 = *(uint32_t *)(v4 + *(uint32_t *)(pArg22 + 4));
                  nRand4 = nRand6 % 5;
                  v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);
                  nRand7 = rand();
                  pObj5 = *(uint32_t *)(v4 + *(uint32_t *)(pArg2 + 4));
                  pObj4 = v27 + nRand7 % 81 - 40;
                  v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 124))(pObj5);
                  nRand8 = rand();
                  pObj3 = *(uint32_t *)(v4 + *(uint32_t *)(pArg2 + 4));
                  j = v30 + nRand8 % 61 - 30;
                  v33 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 128))(pObj3);
                  nRand9 = v33 + rand() % 200 + 300;
                  v35 = *(uint32_t *)this;
                  nRand92 = nRand9;
                  v36 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(v35 + 152))(this, 130, 1, 0, 0);
                  (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int, int, int, int, uint32_t, int))(v35 + 584))(
                    this,
                    pObj4,
                    j,
                    nRand92,
                    pObj4,
                    j,
                    1029,
                    nRand4,
                    0,
                    v36);
                  pArg22 = pArg2;
                  v62 = 1;
                }
              }
              if ( sub_5C9A30(this) < 3 )
              {
                for ( j = 2; j != 0; --j )
                {
                  if ( rand() % 100 < 50 )
                  {
                    pThis_2A0 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 672))(this, 3) - 1;
                    v37 = **(uint32_t **)(v4 + *(uint32_t *)(pArg22 + 4));
                    v38 = *(uint32_t *)(v4 + *(uint32_t *)(pArg22 + 4));
                    v53[0] = 250;
                    v53[1] = 252;
                    v53[2] = 253;
                    i = 100;
                    v39 = (*(int (/*thiscall*/ **)(int))(v37 + 128))(v38);
                    nRand4 = v39 + rand() % 200 + 500;
                    do
                    {
                      v40 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + *(uint32_t *)(pArg2 + 4)) + 120))(*(uint32_t *)(v4 + *(uint32_t *)(pArg2 + 4)));
                      nRand10 = rand();
                      pObj6 = *(uint32_t *)(v4 + *(uint32_t *)(pArg2 + 4));
                      pObj4 = v40 + nRand10 % 40 - 20;
                      v43 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 124))(pObj6);
                      nRand11 = v43 + rand() % 20 - 10;
                      if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 136))(
                             this,
                             pObj4,
                             nRand11,
                             0) != 0 )
                        break;
                    }
                    while ( i-- > 0 );
                    v46 = *(uint32_t *)this;
                    *(this + 8624) = 1;
                    nRand92 = v46;
                    v47 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(v46 + 152))(
                            this,
                            0,
                            0,
                            0,
                            0xFFFF,
                            0,
                            0,
                            0,
                            0);
                    pThis_178 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int, int, int))(*(uint32_t *)this + 376))(
                            this,
                            pThis_2A0,
                            pObj4,
                            nRand11,
                            nRand4,
                            v47);
                    nRand12 = rand();
                    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, int))(nRand92 + 592))(this, v53[nRand12 % 3], pThis_178);
                    pArg22 = pArg2;
                    *(this + 8624) = 0;
                    v62 = 1;
                  }
                }
              }
            }
            if ( v62 != 0 )
            {
              pThis_50 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
              sub_424120(*(uint32_t **)(pThis_50 + 132), 3, 2000);
            }
            goto LABEL_35;
          case 15:
            if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) == 0 || rand() % 100 >= 75 )
              goto LABEL_35;
            v51 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + *(uint32_t *)(pArg22 + 4)) + 124))(*(uint32_t *)(v4 + *(uint32_t *)(pArg22 + 4)));
            pThis_342 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);
            sub_4E4A50(v4, (int)this, 1025, pThis_342, 0, v51, 500, 0, 0, 0, 0);
            v62 = 1;
            ++v60;
            v4 += 4;
            break;
          default:
            goto LABEL_35;
        }
      }
    }
    if ( --v56 <= 0 )
      return off_77F3FC(aCriticalError_41);
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( result != 0 )
    {
      result = v62;
      if ( v62 == 0 )
        continue;
    }
    return result;
  }
}


// 窃笑：LOTUS_LAUGH 播报（84L；sub_699000+sub_493D00 变速换锚 —— 笑时动画变速）
// ------------------------------------------------------------
// 0x5CABB0 sub_5CABB0
// ------------------------------------------------------------
char /*thiscall*/ sub_5CABB0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v5; // edi
  unsigned int pThis_870; // eax
  int fld_e2158; // eax
  int fld_e1639; // eax
  int pThis_6DD; // eax
  int pThis_6DD2; // eax
  unsigned int pThis_6DD3; // ecx
  int v13; // eax
  int pThis_6DD4; // eax
  int v15; // eax

  v5 = ArgList;
  LOBYTE(pThis_870) = sub_5C9410(ArgList, LODWORD(fArg3));
  if ( (uint8_t)pThis_870 == 0
    && (ArgList != 8 || **(uint32_t **)(LODWORD(fArg3) + 4) != 16 || (int)(pThis_870 = sub_699000((int)(this + 2160))) > 5000) )  // 【clock_now(clk)】
  {
    if ( *(this + 2159) != -1 )
    {
      if ( ArgList != 8 || (fld_e2158 = *(this + 2158), *(this + 2158) = fld_e2158 - 1, fld_e2158 <= 0) )
      {
        *(this + 2159) = -1;
        v5 = 0;
      }
    }
    fld_e1639 = *(this + 1639);
    if ( fld_e1639 == 8 )
    {
      pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
      sub_5C9550(pThis_6DD);
    }
    else if ( fld_e1639 == 14 )
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 604))(this, 1);
    }
    LOBYTE(pThis_870) = sub_4E33D0(v5, fArg3, nArg4, nArg5);
    switch ( v5 )
    {
      case 5:
        LOBYTE(pThis_870) = sub_5C9E30(this);
        break;
      case 8:
        pThis_6DD2 = sub_41A5E0((unsigned int)(this + 1757));
        sub_5CA150(pThis_6DD2);
        pThis_870 = sub_41A5E0((unsigned int)(this + 1757));
        if ( pThis_870 < 8 )
        {
          pThis_6DD3 = (unsigned int)(this + 1757);
          if ( *(this + 2159) == -1 )
          {
            v15 = sub_41A5E0(pThis_6DD3);
            sub_493D00(*(uint32_t *)(*(this + 1550) + 4 * v15), 100.0);
          }
          else
          {
            v13 = sub_41A5E0(pThis_6DD3);
            sub_493D00(*(uint32_t *)(*(this + 1550) + 4 * v13), 200.0);
          }
          pThis_6DD4 = sub_41A5E0((unsigned int)(this + 1757));
          LOBYTE(pThis_870) = sub_493B70(*(uint32_t *)(*(this + 1550) + 4 * pThis_6DD4));
        }
        break;
      case 14:
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 604))(this, 0);
        LOBYTE(pThis_870) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                       this,
                       "LOTUS_LAUGH",
                       -1,
                       0,
                       0);
        break;
      default:
        break;
    }
  }
  return pThis_870;
}



// 参数打包 AI（sub_431230; this+568 最后受击时刻）
// ------------------------------------------------------------
// 0x5CAD60 sub_5CAD60
// ------------------------------------------------------------
void /*thiscall*/ sub_5CAD60(uint32_t *this)
{
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v3[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 8
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
    && rand() % 300 < *(this + 2150) )
  {
    memset(&pBuf[1], 0, 12);
    v3[3] = 0;
    v3[0] = 12;
    sub_431230((int)pBuf, v3);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
    sub_5E5260(pBuf);
  }
}



// 参数打包 AI（sub_431230; this+568）
// ------------------------------------------------------------
// 0x5CAE10 sub_5CAE10
// ------------------------------------------------------------
void /*thiscall*/ sub_5CAE10(uint32_t *this)
{
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v3[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 8
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
    && rand() % 300 < *(this + 2151) )
  {
    memset(&pBuf[1], 0, 12);
    v3[3] = 0;
    v3[0] = 13;
    sub_431230((int)pBuf, v3);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
    sub_5E5260(pBuf);
  }
}



// 参数打包 AI（sub_431230; this+568）
// ------------------------------------------------------------
// 0x5CAEC0 sub_5CAEC0
// ------------------------------------------------------------
void /*thiscall*/ sub_5CAEC0(uint32_t *this)
{
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v3[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 8
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
    && rand() % 300 < *(this + 2152) )
  {
    memset(&pBuf[1], 0, 12);
    v3[3] = 0;
    v3[0] = 14;
    sub_431230((int)pBuf, v3);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
    sub_5E5260(pBuf);
  }
}



// 参数打包 AI（sub_431230; this+568）
// ------------------------------------------------------------
// 0x5CAF70 sub_5CAF70
// ------------------------------------------------------------
void /*thiscall*/ sub_5CAF70(uint32_t *this)
{
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v3[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 8
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
    && rand() % 300 < *(this + 2153) )
  {
    memset(&pBuf[1], 0, 12);
    v3[3] = 0;
    v3[0] = 15;
    sub_431230((int)pBuf, v3);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
    sub_5E5260(pBuf);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CB020 sub_5CB020
// ------------------------------------------------------------
int /*thiscall*/ sub_5CB020(int *this)
{
  sub_4E0120();
  if ( *(this + 1787) != 23 )
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 23);
  sub_5CAD60(this);
  sub_5CAE10(this);
  sub_5CAEC0(this);
  sub_5CAF70(this);
  return sub_5C9AF0(this);
}



// 大型 AI（124L）
// ------------------------------------------------------------
// 0x5CB070 sub_5CB070
// ------------------------------------------------------------
void /*thiscall*/ sub_5CB070(void *this)
{
  uint8_t *v1; // edx
  char *v2; // esi
  int v3; // ecx
  unsigned int v4; // ebx
  int nRand; // eax
  int pObj; // ecx
  int v7; // eax
  char *v8; // edi
  int v9; // eax
  char *v10; // esi
  uint32_t *v11; // edx
  uint32_t *v12; // eax
  unsigned int v13; // eax
  char v14[4]; // [esp+Ch] [ebp-38h] BYREF
  void *Block; // [esp+10h] [ebp-34h]
  int v16; // [esp+14h] [ebp-30h]
  int v17; // [esp+18h] [ebp-2Ch]
  char v18[4]; // [esp+1Ch] [ebp-28h] BYREF
  uint8_t *v19; // [esp+20h] [ebp-24h]
  void *Src; // [esp+24h] [ebp-20h]
  int v21; // [esp+28h] [ebp-1Ch]
  void *pThis; // [esp+2Ch] [ebp-18h]
  int v23; // [esp+30h] [ebp-14h] BYREF
  int v24; // [esp+34h] [ebp-10h] BYREF
  int v25; // [esp+40h] [ebp-4h]

  pThis = this;
  Block = nullptr;
  v16 = 0;
  v17 = 0;
  v25 = 0;
  sub_4E0CD0(17, 0, v14, -1);
  v1 = nullptr;
  v2 = nullptr;
  v3 = 0;
  v19 = nullptr;
  Src = nullptr;
  v21 = 0;
  LOBYTE(v25) = 1;
  v4 = 0;
  while ( Block != nullptr && v4 < (v16 - (int)Block) >> 2 )
  {
    nRand = rand();
    pObj = *((uint32_t *)Block + v4);
    v23 = dword_730C10[nRand % 3];
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);
    v8 = (char *)Src;
    v24 = v7;
    if ( v19 != nullptr && ((uint8_t *)Src - v19) >> 2 < (unsigned int)((v21 - (int)v19) >> 2) )
    {
      *(uint32_t *)Src = v7;
      Src = v8 + 4;
    }
    else
    {
      sub_430C80(Src, 1, (int)&v24);
    }
    v9 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v4) + 52))(*((uint32_t *)Block + v4));
    v10 = (char *)Src;
    v24 = v9;
    if ( v19 != nullptr && ((uint8_t *)Src - v19) >> 2 < (unsigned int)((v21 - (int)v19) >> 2) )
    {
      v11 = (char *)Src + 4;
      *(uint32_t *)Src = v9;
      Src = v10 + 4;
    }
    else
    {
      sub_430C80(Src, 1, (int)&v24);
      v11 = Src;
    }
    if ( v19 != nullptr && ((char *)v11 - v19) >> 2 < (unsigned int)((v21 - (int)v19) >> 2) )
    {
      v12 = v11;
      *v11 = v23;
      v3 = v21;
      v1 = v19;
      v2 = (char *)(v12 + 1);
      ++v4;
      Src = v12 + 1;
    }
    else
    {
      sub_430C80(v11, 1, (int)&v23);
      v2 = (char *)Src;
      v3 = v21;
      v1 = v19;
      ++v4;
    }
  }
  if ( v1 != nullptr )
  {
    v13 = (v2 - v1) >> 2;
    if ( v13 != 0 )
    {
      v23 = 0xFFFF;
      if ( v13 >= (v3 - (int)v1) >> 2 )
      {
        sub_430C80(v2, 1, (int)&v23);
      }
      else
      {
        *(uint32_t *)v2 = 0xFFFF;
        Src = v2 + 4;
      }
      (*(void (/*thiscall*/ **)(void *, int, char *, uint32_t, uint32_t))(*(uint32_t *)pThis + 560))(pThis, 16, v18, 0, 0);
      v1 = v19;
    }
    if ( v1 != nullptr )
      j__free(v1);
  }
  v19 = nullptr;
  Src = nullptr;
  v21 = 0;
  if ( Block != nullptr )
    j__free(Block);
}


// 参数打包 AI（sub_431230; this+200）
// ------------------------------------------------------------
// 0x5CB270 sub_5CB270
// ------------------------------------------------------------
void /*thiscall*/ sub_5CB270(uint32_t *this)
{
  uint32_t v2[8]; // [esp+8h] [ebp-40h]
  uint8_t v3[4]; // [esp+28h] [ebp-20h] BYREF
  void *Block; // [esp+2Ch] [ebp-1Ch]
  int v5; // [esp+30h] [ebp-18h]
  int v6; // [esp+34h] [ebp-14h]
  uint32_t v7[4]; // [esp+38h] [ebp-10h] BYREF

  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v2[0] = 4;
    v2[1] = 5;
    v2[2] = 6;
    v2[3] = 7;
    v2[4] = 0;
    v2[5] = 1;
    v2[6] = 2;
    v2[7] = 3;
    v7[0] = v2[4 * *(this + 2159) + rand() % 4];
    Block = nullptr;
    v5 = 0;
    v6 = 0;
    v7[3] = 0;
    sub_431230((int)v3, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v3, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 莲花受击演出：Particle/DieSmoke.ptl + LOTUS_DMG + LOTUS_LAUGH 播报（142L；
//   this+8616/8624/8653/8654/8668/8669 相位）
// ------------------------------------------------------------
// 0x5CB360 sub_5CB360
// ------------------------------------------------------------
char /*thiscall*/ sub_5CB360(uint32_t **this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  uint32_t *fld_e1545; // eax
  uint32_t *pThis_5B; // eax
  char result; // al
  int v9; // [esp+Ch] [ebp-10h] BYREF
  int v10; // [esp+18h] [ebp-4h]

  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 1554));
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -500,
    **(this + 1554),
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[1]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -400,
    (*(this + 1554))[1],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[2]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -300,
    (*(this + 1554))[2],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[3]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -100,
    (*(this + 1554))[3],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[4]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -100,
    (*(this + 1554))[4],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[10]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -600,
    (*(this + 1554))[10],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[11]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    -100,
    (*(this + 1554))[11],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[12]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    200,
    (*(this + 1554))[12],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, (*(this + 1554))[13]);
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    300,
    (*(this + 1554))[13],
    0,
    0,
    0,
    0);
  *(this + 2150) = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[96])(this, 0);
  v2 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[96])(this, 1);
  v3 = (int)*this;
  *(this + 2151) = (uint32_t *)v2;
  *(this + 2152) = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t **, int))(v3 + 384))(this, 2);
  v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[96])(this, 3);
  v5 = (int)*this;
  *(this + 2153) = (uint32_t *)v4;
  *((uint8_t *)this + 7528) = 0;
  *((uint8_t *)this + 8616) = 0;
  (*(void (/*thiscall*/ **)(uint32_t **, uint32_t))(v5 + 144))(this, 0);
  fld_e1545 = *(this + 1545);
  *(this + 1702) = nullptr;
  *(this + 2155) = fld_e1545;
  *(this + 1545) = nullptr;
  v10 = 0;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      pThis_5B = (uint32_t *)sub_4C3640(this + 91, "Particle/DieSmoke.ptl", this);
    else
      pThis_5B = (uint32_t *)sub_4C3640(*(this + 91), "Particle/DieSmoke.ptl", this);
  }
  else
  {
    pThis_5B = nullptr;
  }
  v10 = -1;
  *(this + 2157) = pThis_5B;
  sub_4015C0("LOTUS_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("LOTUS_LAUGH", 0xBu);  // 【std::string构造赋值】
  *(this + 40) = (uint32_t *)200;
  v9 = 100000;
  sub_4E1390(196613, &v9);
  *((uint8_t *)this + 8624) = 0;
  *(this + 2158) = nullptr;
  *(this + 2159) = (uint32_t *)-1;
  *((uint8_t *)this + 8653) = 0;
  *((uint8_t *)this + 8654) = 0;
  result = sub_698F90((int)(this + 2160), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint8_t *)this + 8668) = 0;
  *((uint8_t *)this + 8669) = 0;
  return result;
}


// 莲花攻击状态机（127L）：LOTUS_ATK + LOTUS_SWEEP + R_BELIEVER_ALERT（信徒警觉!）+
//   LOTUS_SWEEP_LOOP/READY_LOOP（this+200/8616/8636/8668/8669 相位）
// ------------------------------------------------------------
// 0x5CB690 sub_5CB690
// ------------------------------------------------------------
uint8_t /*thiscall*/ sub_5CB690(int this)
{
  bool pThis_348; // zf
  uint8_t result; // al
  void *v4; // [esp+8h] [ebp-1Ch] BYREF
  int v5; // [esp+Ch] [ebp-18h]
  int v6; // [esp+10h] [ebp-14h]
  int v7; // [esp+14h] [ebp-10h]
  int v8; // [esp+20h] [ebp-4h]

  sub_4E1780((uint32_t *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
  {
    switch ( sub_41A5E0(this + 7028) )
    {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3
          && *(uint8_t *)(this + 8616) == 0 )
        {
          sub_432EA0("LOTUS_ATK", -1, 0, 0);
          *(uint8_t *)(this + 8616) = 1;
        }
        if ( *(uint32_t *)(this + 8636) != -1 )
          goto LABEL_7;
        break;
      case 8:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3
          && *(uint8_t *)(this + 8616) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "LOTUS_SWEEP",
            -1,
            0,
            0);
          *(uint8_t *)(this + 8616) = 1;
        }
        break;
      case 10:
      case 11:
LABEL_7:
        sub_5CB270(this);
        break;
      case 12:
      case 13:
      case 14:
      case 15:
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 3
          && *(uint8_t *)(this + 8616) == 0 )
        {
          v5 = 0;
          v6 = 0;
          v7 = 0;
          v8 = 0;
          sub_4E0CD0((uint32_t *)this, 17, 0, (int)&v4, -1);
          if ( v5 != 0 && (v6 - v5) >> 2 != 0 )
            sub_5CA5F0((uint8_t *)this, (int)&v4);
          else
            sub_5C9A00(this);
          *(uint8_t *)(this + 8616) = 1;
          if ( sub_41A5E0(this + 7028) == 15 )
            sub_432EA0("R_BELIEVER_ALERT", -1, 0, 0);
          v8 = -1;
          sub_5E5260(&v4);
        }
        break;
      case 16:
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
        {
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
          }
          else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 1
                 && *(uint8_t *)(this + 8616) == 0 )
          {
            sub_5CB070(this);
            *(uint8_t *)(this + 8616) = 1;
          }
        }
        break;
      default:
        break;
    }
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 15 )
  {
    if ( *(uint8_t *)(this + 8668) == 0 )
    {
      sub_432EA0("LOTUS_SWEEP_LOOP", 9, 0, 0);
      *(uint8_t *)(this + 8668) = 1;
    }
  }
  else if ( *(uint8_t *)(this + 8668) == 1 )
  {
    sub_432EE0(9);
    *(uint8_t *)(this + 8668) = 0;
  }
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0;
  result = *(uint8_t *)(this + 8669);
  if ( pThis_348 )
  {
    if ( result == 0 )
    {
      result = (uint8_t)sub_432EA0("LOTUS_READY_LOOP", 9, 0, 0);
      *(uint8_t *)(this + 8669) = 1;
    }
  }
  else if ( result == 1 )
  {
    result = sub_432EE0(9);
    *(uint8_t *)(this + 8669) = 0;
  }
  return result;
}


// 子类扩展字段复位（this+8600..8609）
// ------------------------------------------------------------
// 0x5CB970 sub_5CB970
// ------------------------------------------------------------
int /*thiscall*/ sub_5CB970(int this)
{
  *(uint32_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8601) = 0;
  *(uint8_t *)(this + 8602) = 0;
  *(uint8_t *)(this + 8608) = 0;
  *(uint8_t *)(this + 8609) = 0;
  *(uint8_t *)(this + 7144) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CB9A0 sub_5CB9A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CB9A0(uint32_t *this, uint32_t *uArg2)
{
  if ( uArg2 == this && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 316))(this) == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  if ( uArg2 == (uint32_t *)*(this + 1815) && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 316))(this) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  return sub_4D9170(uArg2);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CBA00 sub_5CBA00
// ------------------------------------------------------------
void /*thiscall*/ sub_5CBA00(uint32_t *this)
{
  int fld_e1813; // esi
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax

  fld_e1813 = *(this + 1813);
  if ( fld_e1813 != 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*this + 152))(this, 100, 1, 0, 0);
    v5 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 30351, 0, 0, v4);
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v5);
    v7 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 0, v6);
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 584))(this, v8);
  }
}



// 草丛陷阱：Particle/PoisonBug.ptl 毒虫 + TRAP_GRASS_UP 草丛升起（102L）
// ------------------------------------------------------------
// 0x5CBA60 sub_5CBA60
// ------------------------------------------------------------
char /*thiscall*/ sub_5CBA60(uint8_t *this)
{
  int v2; // eax
  int pThis_1E; // edi
  int pThis_1B74; // eax
  int v5; // eax
  int pThis_180; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edi
  int v10; // ebx
  int pThis_98; // eax
  int pThis_982; // eax

  if ( *((uint32_t *)this + 2090) != 0 && *(this + 8608) == 0 )
  {
    v2 = *(uint32_t *)this;
    *(this + 8608) = 1;
    (*(void (**)(void))(v2 + 1308))();
  }
  if ( *((uint32_t *)this + 1639) == 8 )
  {
    pThis_1E = *(uint32_t *)(*((uint32_t *)this + 30) + 148);
    pThis_1B74 = sub_41A5E0((unsigned int)(this + 7028));
    if ( pThis_1B74 != 0 )
    {
      v5 = pThis_1B74 - 1;
      if ( v5 != 0 )
      {
        if ( v5 == 1 )
        {
          if ( pThis_1E >= 3
            && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
            && *(this + 8600) != 0 )
          {
            pThis_180 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
            (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t, int, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
              this,
              48021,
              pThis_180,
              0,
              0,
              100,
              1,
              0,
              4,
              0,
              0,
              0);
            *(this + 8600) = 0;
          }
          if ( pThis_1E >= 4
            && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
            && *(this + 8601) != 0 )
          {
            v7 = *(uint32_t *)this;
            *(this + 8601) = 0;
            v8 = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(v7 + 588))(this, "Particle/PoisonBug.ptl");
            v9 = *(uint32_t *)this;
            v10 = v8;
            pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(this, 0, 0, 0);
            pThis_982 = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 152))(
                    this,
                    v10,
                    0,
                    0,
                    0,
                    50,
                    pThis_98);
            (*(void (/*thiscall*/ **)(uint8_t *, int, int))(v9 + 580))(this, 30350, pThis_982);
            return sub_4E1780(this);
          }
        }
      }
      else if ( pThis_1E >= 2
             && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
             && *(this + 8602) != 0 )
      {
        *(this + 8602) = 0;
        sub_5CBA00(this);
        return sub_4E1780(this);
      }
    }
    else if ( pThis_1E >= 4 && *(this + 8609) == 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "TRAP_GRASS_UP",
        -1,
        0,
        0);
      *(this + 8609) = 1;
    }
  }
  return sub_4E1780(this);
}



// ============================================================
// 【分区 6】陷阱基类与字段群（0x5CBC00-0x5CC490）
// 证据：sub_4049C0 插值、RTTI cast 目标解算群（陷阱触发对象判定）

// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5CBC00 sub_5CBC00
// ------------------------------------------------------------
int /*thiscall*/ sub_5CBC00(void *this)
{
  int pThis_494; // edi
  float pThis_1802; // [esp+4h] [ebp-24h]
  float pThis_180; // [esp+8h] [ebp-20h]
  float v6; // [esp+20h] [ebp-8h]

  pThis_494 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1172))(this);
  pThis_180 = (float)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 384))(this);
  pThis_1802 = (float)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 1);
  v6 = (double)(int)(uint64_t)sub_4049C0(pThis_1802, pThis_180, pThis_494, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 688))(this, 1065353216);
  sub_4EB4B0(COERCE_FLOAT(2));
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 688))(this);
  return sub_4EB2C0(v6);
}



// 子类扩展字段复位（this+8600..8609）
// ------------------------------------------------------------
// 0x5CBCA0 sub_5CBCA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CBCA0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v6; // eax
  int v7; // eax
  int v8; // eax

  if ( *(this + 2151) == 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);
    if ( v6 > 0 )
    {
      if ( v6 <= 5 )
      {
        *(uint8_t *)(*(this + 1905) + 32) = 0;
      }
      else if ( v6 > 10 )
      {
        goto LABEL_8;
      }
      *(uint8_t *)(*(this + 1905) + 64) = 0;
    }
LABEL_8:
    *(this + 2151) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);
  }
  if ( ArgList == 8 )
  {
    v7 = **(uint32_t **)(LODWORD(fArg3) + 4);
    if ( v7 != 0 )
    {
      v8 = v7 - 1;
      if ( v8 != 0 )
      {
        if ( v8 == 1 )
        {
          *((uint8_t *)this + 8600) = 1;
          *((uint8_t *)this + 8601) = 1;
        }
      }
      else
      {
        *((uint8_t *)this + 8602) = 1;
      }
    }
    else
    {
      *((uint8_t *)this + 8609) = 0;
    }
  }
  return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CBD50 sub_5CBD50
// ------------------------------------------------------------
char /*thiscall*/ sub_5CBD50(int *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int fld_e2172; // [esp-8h] [ebp-Ch]

  (*(void (/*thiscall*/ **)(int *))(*this + 1308))(this);
  *(this + 2163) = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 21);
  v2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 22);
  v3 = *this;
  *(this + 2164) = v2;
  *(this + 2172) = (*(int (/*thiscall*/ **)(int *, int))(v3 + 384))(this, 23);
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 24);
  fld_e2172 = *(this + 2172);
  *(this + 2173) = v4;
  return sub_698F90((int)(this + 2165), fld_e2172, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CBDC0 sub_5CBDC0
// ------------------------------------------------------------
int /*userpurge*/ sub_5CBDC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, int nArg5)
{
  char v6; // al
  int pObj2; // ebx
  int pObj; // edi
  int v9; // edi
  int v10; // eax
  int v11; // edx
  int v12; // edi
  int v13; // eax
  int v15; // [esp+8h] [ebp-4h] BYREF

  v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
  pObj2 = nArg3;
  if ( v6 != 0 && rand() % 100 < 10 )
  {
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 576))(pObj2, nArg2) != 0 )
      pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 576))(pObj2);
    else
      pObj = pObj2;
    nArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) >= v9 )
      v10 = nArg3 - 50;
    else
      v10 = nArg3 + 50;
    v11 = *pDwArg1;
    nArg3 = v10;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int *, int *, int, int, int, int))(v11 + 140))(
           pDwArg1,
           &nArg3,
           &v15,
           v10,
           v15,
           100,
           1) != 0 )
    {
      v12 = *pDwArg1;
      v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
      (*(void (/*thiscall*/ **)(int *, int, int, int))(v12 + 108))(pDwArg1, nArg3, v15, v13);
    }
  }
  return sub_4DA3B0(pObj2, nArg4, nArg5);
}



// RTTI cast 目标解算（72L）
// ------------------------------------------------------------
// 0x5CBEA0 sub_5CBEA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CBEA0(void *this, int nArg2, int nArg3, int nArg4)
{
  int pObj2; // eax
  int pObj; // esi
  int v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // ecx
  int v11; // [esp+4h] [ebp-8h]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )
  {
    pObj2 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    pObj = pObj2;
    if ( pObj2 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 672))(pObj2, 3);
      v6 = sub_4DA0F0(0);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
      v7 = sub_4DA0F0(1);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
      v11 = sub_4DA0F0(2);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
      v8 = sub_4DA0F0(3);
      if ( v6 < 5 || v7 < 5 )
      {
        v9 = v11;
      }
      else
      {
        v9 = v11;
        if ( v11 >= 5 && v8 >= 5 )
        {
          *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 4;
          return sub_4DB480(nArg2, nArg3, nArg4);
        }
      }
      if ( v7 < v6 )
        goto LABEL_15;
      if ( v6 <= v9 && v6 <= v8 )
      {
        *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 0;
        return sub_4DB480(nArg2, nArg3, nArg4);
      }
      if ( v7 <= v6 )
      {
LABEL_15:
        if ( v7 <= v9 && v7 <= v8 )
        {
          *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 1;
          return sub_4DB480(nArg2, nArg3, nArg4);
        }
      }
      if ( v9 > v6 || v9 > v7 || v9 > v8 )
      {
        if ( v8 <= v6 && v8 <= v7 && v8 <= v9 )
          *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 3;
      }
      else
      {
        *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 20) = 2;
      }
    }
  }
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x5CC010 sub_5CC010
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC010(int *this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  uint32_t *fld_e2154; // eax
  uint32_t *v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int fld_e2163; // [esp+8h] [ebp-8h]
  uint8_t fld_e21632; // [esp+Fh] [ebp-1h]

  if ( (uint8_t)nArg2 == 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);
    fld_e2154 = (uint32_t *)*(this + 2154);
    v7 = (uint32_t *)*fld_e2154;
    fld_e2163 = *(this + 2163);
    if ( (uint32_t *)*fld_e2154 != fld_e2154 )
    {
      do
      {
        fld_e21632 = (uint64_t)((double)fld_e2163-- * 150.0 / (double)*(this + 2163));
        if ( fld_e21632 == 0 )
          break;
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);
        v9 = sub_45E490(v7[2], *(uint32_t *)(v8 + 8));
        v10 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);
        v11 = sub_45E4D0(v7[3], v7[4], *(uint32_t *)(v10 + 8), 1.0);
        sub_491DE0(dword_79C0B0, v9, v11, fArg5, 0, 0, 0, (fld_e21632 << 24) | 0xFFFFFF);
        v7 = (uint32_t *)*v7;
      }
      while ( v7 != (uint32_t *)*(this + 2154) );
    }
  }
  return sub_4D8F90(nArg2, nArg3, nArg4, LODWORD(fArg5));
}



// RTTI cast 目标解算（65L）
// ------------------------------------------------------------
// 0x5CC110 sub_5CC110
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC110(uint32_t *this)
{
  unsigned int v1; // esi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // ebx
  int v12; // eax
  int v13; // esi
  int v15; // [esp+Ch] [ebp-Ch]
  int v16; // [esp+10h] [ebp-8h]
  unsigned int v17; // [esp+14h] [ebp-4h]

  v1 = 0;
  v16 = 99999;
  v15 = 0;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v17 = v1;
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj2 = *(uint32_t *)(v6 + 4 * v1);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && v1 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        pObj = *(uint32_t *)(v9 + 4 * v1);
      else
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      {
        v12 = __RTDynamicCast(pObj, 0, &IRDActiveObject `RTTI Type Descriptor', &CNSpirit `RTTI Type Descriptor', 0);
        v13 = v12;
        if ( v12 != 0 && v16 > (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 8))(this, v12, 1) )
        {
          v16 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 8))(this, v13, 1);
          v15 = v13;
        }
      }
      v1 = v17;
    }
    ++v1;
  }
  return v15;
}



// RTTI cast 目标解算（67L）
// ------------------------------------------------------------
// 0x5CC200 sub_5CC200
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC200(uint32_t *this, int nArg2)
{
  uint32_t *pThis; // ebx
  unsigned int v3; // edi
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj3; // ecx
  int v9; // ecx
  int v10; // edx
  int pObj2; // esi
  int pObj; // eax
  int v13; // esi
  int v15; // [esp+Ch] [ebp-Ch]
  int v16; // [esp+10h] [ebp-8h]

  pThis = this;
  v3 = 0;
  v16 = 0;
  while ( 1 )
  {
    v4 = pThis[29];
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
    if ( (int)v3 >= v6 )
      return v16;
    v7 = *(uint32_t *)(v4 + 8);
    if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
      pObj3 = *(uint32_t *)(v7 + 4 * v3);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 17) != 0 )
    {
      v9 = pThis[29];
      v10 = *(uint32_t *)(v9 + 8);
      if ( v10 != 0 && v3 < (*(uint32_t *)(v9 + 12) - v10) >> 2 )
        pObj2 = *(uint32_t *)(v10 + 4 * v3);
      else
        pObj2 = 0;
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);
      if ( v15 != (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis)
        || (pObj = __RTDynamicCast(pObj2, 0, &IRDActiveObject `RTTI Type Descriptor', &CNSpirit `RTTI Type Descriptor', 0)) == 0 )
      {
        pThis = this;
        goto LABEL_20;
      }
      pThis = this;
      v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 304))(pObj);
      if ( v13 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 304))(this) )
        goto LABEL_20;
      ++v16;
      ++v3;
    }
    else
    {
LABEL_20:
      ++v3;
    }
  }
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5CC300 sub_5CC300
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC300(uint32_t *this)
{
  int v2; // edi
  int result; // eax
  uint32_t *pThis_651; // esi
  int i; // ebx
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+8h] [ebp-24h]
  float v8; // [esp+24h] [ebp-8h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);
  v7 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 17);
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);
  sub_4EB4B0(COERCE_FLOAT(18));
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
  result = sub_4EB2C0(v8);
  pThis_651 = this + 1617;
  for ( i = 18; i != 0; --i )
  {
    if ( *pThis_651 != 0 )
    {
      sub_4EB6E0(1.0);
      result = sub_4EB6A0(v8);
    }
    ++pThis_651;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CC3C0 sub_5CC3C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5CC3C0(uint32_t *this)
{
  bool *fld_e1905; // edi
  float v3; // [esp+4h] [ebp-8h]

  *(uint8_t *)(*(this + 1905) + 32) = *(this + 2151) < (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 19)
                                 && sub_5CC200(this, 1) != 0;
  fld_e1905 = (bool *)(*(this + 1905) + 64);
  *fld_e1905 = sub_5CC200(this, 0) != 0;
  if ( *(this + 2152) >= (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 20) )
    *(uint8_t *)(*(this + 1905) + 64) = 0;
  v3 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.15000001 < v3 )
    *(uint8_t *)(*(this + 1905) + 64) = 0;
}



// ============================================================
// 【分区 7】埃切维里亚/刺王（Echeverria / SpikeKing）（0x5CC490-0x5CD170）
// 证据：R_ECHEVERRA_DMG + ECHEVERRA_DIE、ECHEVERRA_ARM_ATK 触手攻击、
//       ECHEVERRA_INTENSE_AURA + Animation_SpikeKing/Aura.ani（368L 巨型 aura 态）、
//       Monster/SpikeKing/SpikeKing_{Acc,Clothes,Glow,Hair}.equ

// 刺王语音：R_ECHEVERRA_DMG + ECHEVERRA_DIE（this+8600..8696 相位）
// ------------------------------------------------------------
// 0x5CC490 sub_5CC490
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC490(int this)
{
  int result; // eax

  *(uint32_t *)(this + 6792) = 2;
  *(uint32_t *)(this + 6796) = 3;
  *(uint32_t *)(this + 6800) = 5;
  *(uint32_t *)(this + 6804) = 4;
  *(uint32_t *)(this + 6808) = 5;
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  sub_4015C0("R_ECHEVERRA_DMG", 0xFu);  // 【std::string构造赋值】
  result = sub_4015C0("ECHEVERRA_DIE", 0xDu);  // 【std::string构造赋值】
  *(uint8_t *)(this + 8673) = 0;
  *(uint8_t *)(this + 8674) = 0;
  *(uint8_t *)(this + 8696) = 0;
  return result;
}



// 语音注册（sub_4015C0; 32L）
// ------------------------------------------------------------
// 0x5CC510 sub_5CC510
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC510(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 357913941 - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5CC5A0 sub_5CC5A0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5CC5A0(int this, int Src, unsigned int uArg3, int *pDwArg4)
{
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_85; // ecx
  int fld_86; // eax
  char *fld_42; // eax
  void *v15; // eax
  int fld_43; // eax
  int fld_87; // ecx
  unsigned int v18; // edi
  uint8_t *fld_83; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *fld_84; // edi
  int v24; // edi
  char *pMem; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  fld_4 = *(uint32_t *)(this + 4);
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_52E630(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v28];
      *(uint32_t *)(this + 8) = &pMem[4 * v18];
      *(uint32_t *)(this + 4) = pMem;
      return (unsigned int)pMem;
    }
  }
  return result;
}



// 触手攻击：ECHEVERRA_ARM_ATK 播报（76L；this+8600/8637/8638/8696 相位）
// ------------------------------------------------------------
// 0x5CC780 sub_5CC780
// ------------------------------------------------------------
char /*thiscall*/ sub_5CC780(int *this)
{
  int fld_e1639; // eax
  int v3; // edx
  int fld_e2162; // edi
  int fld_e2154; // ecx
  uint32_t **v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int fld_e21542; // ebx
  int v11; // eax
  uint32_t v13[3]; // [esp+8h] [ebp-10h] BYREF
  int v14; // [esp+14h] [ebp-4h]

  if ( *(this + 2090) != 0 && *((uint8_t *)this + 8600) == 0 )
  {
    *((uint8_t *)this + 8600) = 1;
    sub_5CC300(this);
  }
  fld_e1639 = *(this + 1639);
  if ( fld_e1639 != 0 )
  {
    if ( fld_e1639 == 8
      && sub_41A5E0((unsigned int)(this + 1757)) == 0
      && *(int *)(*(this + 30) + 148) >= 1
      && *((uint8_t *)this + 8696) == 0 )
    {
      v3 = *this;
      *((uint8_t *)this + 8696) = 1;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v3 + 212))(this, "ECHEVERRA_ARM_ATK", -1, 0, 0);
    }
  }
  else
  {
    sub_5CC3C0(this);
  }
  fld_e2162 = *(this + 2162);
  if ( sub_699000((int)(this + 2156)) >= fld_e2162 )  // 【clock_now(clk)】
  {
    if ( *(this + 2155) == *(this + 2163) )
    {
      fld_e2154 = *(this + 2154);
      v6 = *(uint32_t ***)(fld_e2154 + 4);
      if ( v6 != (uint32_t **)fld_e2154 )
      {
        *v6[1] = *v6;
        (*v6)[1] = v6[1];
        j__free(v6);
        --*(this + 2155);
      }
    }
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v8 = *this;
    v13[0] = v7;
    v13[1] = (*(int (/*thiscall*/ **)(int *))(v8 + 124))(this);
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    fld_e21542 = *(uint32_t *)*(this + 2154);
    v13[2] = v9;
    v14 = sub_5D1490(fld_e21542, *(uint32_t *)(fld_e21542 + 4), v13);
    sub_5CC510(this + 2153, 1u);
    v11 = v14;
    *(uint32_t *)(fld_e21542 + 4) = v14;
    **(uint32_t **)(v11 + 4) = v11;
    *((uint8_t *)this + 8637) = 0;
    *((uint8_t *)this + 8638) = 0;
    sub_698F90((int)(this + 2156), *(this + 2164), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return sub_4E1780(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC8E0 sub_5CC8E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC8E0(char *this)
{
  *(uint32_t *)this = &CNAuraChangeStatusMaster::`vftable';
  sub_64A7C0();
  return sub_591190(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC930 sub_5CC930
// ------------------------------------------------------------
char */*thiscall*/ sub_5CC930(char *Block, char pszArg2)
{
  sub_5CC8E0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC960 sub_5CC960
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5CC960(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, int nArg7)
{
  sub_64B6C0(nArg2, nArg3, nArg4, nArg5, pszArg6, nArg7);
  *this = &CNAuraChangeStatusMasterSpikeKing::`vftable';
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC9A0 sub_5CC9A0
// ------------------------------------------------------------
void */*thiscall*/ sub_5CC9A0(void *Block, char pszArg2)
{
  sub_5CC9D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CC9D0 sub_5CC9D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CC9D0(char *this)
{
  *(uint32_t *)this = &CNAuraChangeStatusMasterSpikeKing::`vftable';
  sub_64A7C0();
  return sub_5CC8E0(this);
}



// 强力光环态（368L 全文件最大）：ECHEVERRA_INTENSE_AURA 播报 +
//   Animation_SpikeKing/Aura.ani（sub_431230+RTTI cast —— 刺王 aura 形态切换）
// ------------------------------------------------------------
// 0x5CCA20 sub_5CCA20
// ------------------------------------------------------------
void /*userpurge*/ sub_5CCA20(int *pDwArg1@<ecx>, int nArg2@<edi>, double fArg3@<st0>, int ArgList, int pArg5, int nArg6, int nArg7)
{
  int v8; // eax
  int pObj3; // ebx
  int v10; // edi
  int v11; // eax
  uint32_t *v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // edx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int pObj; // eax
  int v22; // eax
  int v23; // edx
  void *v24; // eax
  int v25; // edx
  void *v26; // eax
  int v27; // edx
  int v28; // edi
  int *v29; // eax
  int v30; // edx
  uint8_t *pMem; // edi
  uint8_t *v32; // eax
  int v33; // edx
  void *v34; // eax
  int v35; // edx
  void *v36; // eax
  int v37; // edx
  int v38; // edi
  int *v39; // edi
  int v40; // edx
  void *v41; // eax
  int v42; // eax
  int v43; // edi
  int v44; // eax
  int v45; // edx
  unsigned int i; // edi
  int v47; // eax
  int v48; // ecx
  int v49; // eax
  int v50; // eax
  int v51; // ecx
  int v52; // ecx
  int v53; // eax
  int pObj2; // eax
  int *v55; // eax
  int v56; // edx
  int fArg33; // [esp+80h] [ebp-A8h]
  int v59; // [esp+98h] [ebp-90h] BYREF
  char v60; // [esp+9Ch] [ebp-8Ch]
  float v61; // [esp+A0h] [ebp-88h]
  int v62; // [esp+A4h] [ebp-84h]
  char v63; // [esp+A8h] [ebp-80h]
  float v64; // [esp+ACh] [ebp-7Ch]
  int v65; // [esp+B0h] [ebp-78h]
  char v66; // [esp+B4h] [ebp-74h]
  float v67; // [esp+B8h] [ebp-70h]
  int v68; // [esp+BCh] [ebp-6Ch]
  char v69; // [esp+C0h] [ebp-68h]
  float fArg32; // [esp+C4h] [ebp-64h]
  void *pBuf[4]; // [esp+C8h] [ebp-60h] BYREF
  int v72; // [esp+D8h] [ebp-50h] BYREF
  char v73; // [esp+DCh] [ebp-4Ch]
  float v74; // [esp+E0h] [ebp-48h]
  int v75; // [esp+E4h] [ebp-44h]
  char v76; // [esp+E8h] [ebp-40h]
  float v77; // [esp+ECh] [ebp-3Ch]
  int v78; // [esp+F0h] [ebp-38h]
  char v79; // [esp+F4h] [ebp-34h]
  float v80; // [esp+F8h] [ebp-30h]
  int v81; // [esp+FCh] [ebp-2Ch]
  char v82; // [esp+100h] [ebp-28h]
  float fArg34; // [esp+104h] [ebp-24h]
  int v84; // [esp+108h] [ebp-20h] BYREF
  int v85; // [esp+10Ch] [ebp-1Ch]
  void *pMem3; // [esp+110h] [ebp-18h]
  void *pMem2; // [esp+114h] [ebp-14h]
  void *Block; // [esp+118h] [ebp-10h]
  int v89; // [esp+124h] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )
  {
    v8 = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
    pObj3 = 0;
    if ( v8 != 0 )
    {
      if ( v8 == 2 )
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 4));
    }
    else
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)pDwArg1[1554]);
    }
  }
  else
  {
    pObj3 = 0;
  }
  if ( ArgList == 8 )
  {
    v10 = sub_5CC110(pDwArg1);
    v11 = 0;
    if ( v10 != 0 )
      v11 = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 8))(pDwArg1, v10, 1);
    v12 = *(uint32_t **)(pArg5 + 4);
    if ( *v12 == 2 && (v10 == 0 || v11 > 100) )
      *v12 = 1;
    v13 = **(uint32_t **)(pArg5 + 4);
    if ( v13 != 0 )
    {
      v14 = v13 - 1;
      if ( v14 != 0 )
      {
        if ( v14 == 1 && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
        {
          pObj3 = sub_5CC110(pDwArg1);
          v15 = 0;
          if ( pObj3 != 0 )
          {
            memset(&pBuf[1], 0, 12);
            v16 = *pDwArg1;
            v89 = 2;
            v84 = (*(int (/*thiscall*/ **)(int *, int))(v16 + 48))(pDwArg1, nArg2);
            sub_431230((int)pBuf, &v84);
            v84 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 52))(pDwArg1);
            sub_431230((int)pBuf, &v84);
            (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)pObj3 + 560))(pObj3, 19, pBuf, 0, 0);
            while ( 1 )
            {
              v17 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);
              v18 = *(uint32_t *)(v17 + 4);
              v19 = v18 != 0 ? (*(uint32_t *)(v17 + 8) - v18) >> 2 : 0;
              if ( v15 >= v19 )
                break;
              (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);
              if ( *(int **)(sub_517740(v15) + 4) == pDwArg1 )
              {
                (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);
                v20 = sub_517740(v15);
                pObj = __RTDynamicCast(
                        v20,
                        0,
                        &IRDAppendage `RTTI Type Descriptor',
                        &CNChangeStatus `RTTI Type Descriptor',
                        0);
                if ( pObj != 0 )
                {
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);
                  break;
                }
              }
              ++v15;
            }
            v22 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 9);
            v23 = *pDwArg1;
            v84 = v22;
            v85 = (*(int (/*thiscall*/ **)(int *, int))(v23 + 384))(pDwArg1, 10);
            v24 = (void *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 11);
            v25 = *pDwArg1;
            pMem3 = v24;
            Block = (void *)(*(int (/*thiscall*/ **)(int *, int))(v25 + 384))(pDwArg1, 12);
            v26 = (void *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 13);
            v27 = *pDwArg1;
            pMem2 = v26;
            v28 = (*(int (/*thiscall*/ **)(int *, int))(v27 + 384))(pDwArg1, 14);
            v61 = (float)v84;
            v59 = 0;
            v60 = 1;
            v62 = 3;
            v63 = 1;
            v64 = (float)v85;
            v65 = 7;
            v66 = 1;
            v68 = 8;
            v69 = 1;
            v67 = (float)(int)pMem3;
            fArg3 = (double)(int)Block;
            fArg32 = fArg3;
            Block = operator new(0x7Cu);
            LOBYTE(v89) = 3;
            if ( Block != nullptr )
              v29 = (int *)sub_5101B0(&v59, 4, v28, 1);
            else
              v29 = nullptr;
            v30 = *v29;
            LOBYTE(v89) = 2;
            (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v30 + 56))(
              v29,
              pDwArg1,
              pDwArg1,
              0,
              0,
              0,
              -1);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
              pDwArg1,
              100,
              *(uint32_t *)(pDwArg1[1554] + 4),
              0,
              0,
              0,
              0);
            (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pObj3 + 204))(
              pObj3,
              100,
              *(uint32_t *)(pDwArg1[1554] + 8),
              0,
              0,
              0,
              0);
            pMem = operator new(0x80u);
            pMem3 = pMem;
            LOBYTE(v89) = 4;
            if ( pMem != nullptr )
            {
              Block = (void *)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1);
              fArg3 = (double)(int)Block * ((double)(int)pMem2 * 0.0099999998);
              *(float *)&fArg33 = fArg3;
              v32 = sub_4D6810(pMem, fArg33, 1000, 1, 1);
            }
            else
            {
              v32 = nullptr;
            }
            v33 = *(uint32_t *)v32;
            LOBYTE(v89) = 2;
            (*(void (/*thiscall*/ **)(uint8_t *, int *, int *, uint32_t, uint32_t, uint32_t))(v33 + 56))(v32, pDwArg1, pDwArg1, 0, 0, 0);
            ++pDwArg1[2152];
            v89 = -1;
            sub_5E5260(pBuf);
          }
        }
      }
      else if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(
          pDwArg1,
          "ECHEVERRA_INTENSE_AURA",
          -1,
          0,
          0,
          nArg2);
        v34 = (void *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 4);
        v35 = *pDwArg1;
        pMem2 = v34;
        Block = (void *)(*(int (/*thiscall*/ **)(int *, int))(v35 + 384))(pDwArg1, 5);
        v36 = (void *)(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 6);
        v37 = *pDwArg1;
        pMem3 = v36;
        v85 = (*(int (/*thiscall*/ **)(int *, int))(v37 + 384))(pDwArg1, 7);
        v38 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 8);
        v74 = (float)(int)pMem2;
        v72 = 0;
        v73 = 1;
        v75 = 3;
        v76 = 1;
        v77 = (float)(int)Block;
        v78 = 7;
        v79 = 1;
        v81 = 8;
        v82 = 1;
        v80 = (float)(int)pMem3;
        fArg3 = (double)v85;
        fArg34 = fArg3;
        pMem2 = operator new(0x1D0u);
        v89 = 1;
        if ( pMem2 != nullptr )
          v39 = (int *)sub_5CC960(300, &v72, 4, v38, 0, 1);
        else
          v39 = nullptr;
        v40 = *v39;
        v89 = -1;
        (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t))(v40 + 56))(v39, pDwArg1, pDwArg1, 0, 0, 0);
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          v41 = pDwArg1 + 91;
        else
          v41 = (void *)pDwArg1[91];
        sub_64B480(v41, (int)"Animation_SpikeKing/Aura.ani");
        ++pDwArg1[2151];
      }
    }
    else
    {
      v42 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8696) = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(v42 + 308))(pDwArg1) != 0 )
      {
        v43 = sub_5CC200(0);
        pMem2 = (void *)(v43 * (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 384))(pDwArg1, 0, nArg2));
        v44 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 1);
        v45 = *pDwArg1;
        Block = (void *)(v43 * v44);
        pMem3 = (void *)(v43 * (*(int (/*thiscall*/ **)(int *, int))(v45 + 384))(pDwArg1, 2));
        v85 = v43 * (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 384))(pDwArg1, 3);
        for ( i = 0; ; ++i )
        {
          v47 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);
          v48 = *(uint32_t *)(v47 + 4);
          v49 = v48 != 0 ? (*(uint32_t *)(v47 + 8) - v48) >> 2 : 0;
          if ( (int)i >= v49 )
            break;
          v50 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);
          v51 = *(uint32_t *)(v50 + 4);
          if ( v51 != 0 && i < (*(uint32_t *)(v50 + 8) - v51) >> 2 )
            v52 = *(uint32_t *)(v51 + 4 * i);
          else
            v52 = 0;
          if ( *(int **)(v52 + 4) == pDwArg1 )
          {
            (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 700))(pDwArg1);
            v53 = sub_517740(i);
            pObj2 = __RTDynamicCast(
                    v53,
                    0,
                    &IRDAppendage `RTTI Type Descriptor',
                    &CNChangeStatus `RTTI Type Descriptor',
                    0);
            if ( pObj2 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);
              break;
            }
          }
        }
        v72 = 0;
        v73 = 1;
        v74 = (float)(int)pMem2;
        v75 = 3;
        v76 = 1;
        v78 = 7;
        v79 = 1;
        v77 = (float)(int)Block;
        v81 = 8;
        v82 = 1;
        v80 = (float)(int)pMem3;
        fArg3 = (double)v85;
        fArg34 = fArg3;
        pMem2 = operator new(0x7Cu);
        v89 = 0;
        if ( pMem2 != nullptr )
          v55 = (int *)sub_5101B0(&v72, 4, 0, 1);
        else
          v55 = nullptr;
        v56 = *v55;
        v89 = -1;
        (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t))(v56 + 56))(v55, pDwArg1, pDwArg1, 0, 0, 0);
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
          pDwArg1,
          100,
          *(uint32_t *)pDwArg1[1554],
          0,
          0,
          0,
          0);
      }
    }
  }
  sub_4E33D0(pDwArg1, pObj3, fArg3, ArgList, pArg5, *(float *)&nArg6, *(float *)&nArg7);
}


// 刺王外观装载：Monster/SpikeKing/SpikeKing_{Acc,Clothes,Glow,Hair}.equ 四件
// ------------------------------------------------------------
// 0x5CD050 sub_5CD050
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD050(int *this)
{
  int i; // edi
  void *pMem; // eax
  char *v4; // eax
  int v5; // edx
  int result; // eax
  void *v7[5]; // [esp+8h] [ebp-20h]
  int v8; // [esp+24h] [ebp-4h]

  v7[0] = "Monster/SpikeKing/SpikeKing_Acc.equ";
  v7[1] = "Monster/SpikeKing/SpikeKing_Clothes.equ";
  v7[2] = "Monster/SpikeKing/SpikeKing_Glow.equ";
  v7[3] = "Monster/SpikeKing/SpikeKing_Hair.equ";
  for ( i = 0; i < 4; ++i )
  {
    pMem = operator new(0x544u);
    v7[4] = pMem;
    v8 = 0;
    if ( pMem != nullptr )
      v4 = sub_4BA9E0((char *)pMem, v7[i], 0);
    else
      v4 = nullptr;
    v5 = *this;
    v8 = -1;
    result = (*(int (/*thiscall*/ **)(int *, char *))(v5 + 784))(this, v4);
    if ( result != 0 )
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  }
  return result;
}



// AI 相位门（this+8628..8676）
// ------------------------------------------------------------
// 0x5CD100 sub_5CD100
// ------------------------------------------------------------
char /*thiscall*/ sub_5CD100(uint8_t *this)
{
  int v2; // eax
  int v3; // eax
  char result; // al

  v2 = *(uint32_t *)this;
  *(this + 8628) = 0;
  *(this + 8676) = 0;
  v3 = (*(int (**)(void))(v2 + 52))();
  *((uint32_t *)this + 2161) = v3;
  *((uint32_t *)this + 2160) = v3;
  *(this + 8661) = 0;
  *(this + 8662) = 0;
  result = sub_698F90((int)(this + 8648), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint32_t *)this + 2170) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CD150 sub_5CD150
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD150(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2170)(uint32_t, int); // ecx
  int result; // eax

  fld_e2170 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2170);
  if ( fld_e2170 != nullptr )
    result = (**fld_e2170)(fld_e2170, 1);
  *(this + 2170) = 0;
  return result;
}



// ============================================================
// 【分区 8】锤王与巨人（HammerKing / Giant）（0x5CD170-0x5CDA80）
// 证据：HAMMER_KING_CRASH 崩击、TAU_GROUND_HIT 砸地（0x5CD6F0 复用 0x5A 音效）、
//       R_GIANT_ATK/ROAR/DMG/DIE + R_GOLEM_AMB 巨人语音组、B_FLATANY_01 登场曲、
//       Monster/Magma/Animation_Common/DownAttackEffect.ani

// 崩击：HAMMER_KING_CRASH 播报（27L）
// ------------------------------------------------------------
// 0x5CD170 sub_5CD170
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD170(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 4 )
    return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "HAMMER_KING_CRASH",
             -1,
             0,
             0);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 0 )
      *(this + 2158) = 0;
  }
  return result;
}



// 锤王相位字段（this+8684..8716, 20L）
// ------------------------------------------------------------
// 0x5CD1E0 sub_5CD1E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD1E0(int this)
{
  *(uint8_t *)(this + 8684) = 0;
  *(uint8_t *)(this + 8685) = 0;
  *(uint32_t *)(this + 8688) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint32_t *)(this + 8700) = 0;
  *(uint32_t *)(this + 8704) = 0;
  *(uint32_t *)(this + 8708) = 0;
  *(uint32_t *)(this + 8712) = 0;
  *(uint32_t *)(this + 8716) = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CD220 sub_5CD220
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD220(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  *(this + 2172) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v3 = *this;
  *(this + 2173) = v2;
  *(this + 2174) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 2);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v5 = *this;
  *(this + 2175) = v4;
  *(this + 2176) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 4);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);
  *(this + 2177) = result;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CD2A0 sub_5CD2A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD2A0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2178)(uint32_t, int); // ecx
  int result; // eax

  fld_e2178 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2178);
  if ( fld_e2178 != nullptr )
    result = (**fld_e2178)(fld_e2178, 1);
  *(this + 2178) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CD2C0 sub_5CD2C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD2C0(int this, int nArg2, int nArg3)
{
  int result; // eax

  result = 0;
  *(uint8_t *)(this + 7558) = 0;
  *(uint8_t *)(this + 7557) = 0;
  *(uint8_t *)(this + 7556) = 0;
  *(uint8_t *)(this + 7534) = 0;
  *(uint8_t *)(this + 7533) = 0;
  *(uint8_t *)(this + 7532) = 0;
  *(uint8_t *)(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  *(uint32_t *)(this + 7539) = 0;
  *(uint32_t *)(this + 7543) = 0;
  *(uint32_t *)(this + 7547) = 0;
  *(uint32_t *)(this + 7551) = 0;
  *(uint8_t *)(this + 7555) = 0;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  if ( nArg3 == 0 || nArg3 == 2 )
    *(uint8_t *)(this + 7535) = 1;
  return result;
}



// 锤王相位字段（this+8684..8696）
// ------------------------------------------------------------
// 0x5CD360 sub_5CD360
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD360(int this)
{
  *(uint32_t *)(this + 8684) = 0;
  *(uint8_t *)(this + 8688) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8696) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CD380 sub_5CD380
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD380(uint32_t *this)
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  *(this + 2171) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  *(this + 2173) = result;
  return result;
}



// 锤王相位字段（this+8684..8692）
// ------------------------------------------------------------
// 0x5CD3C0 sub_5CD3C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD3C0(int this)
{
  *(uint32_t *)(this + 8684) = 0;
  *(uint8_t *)(this + 8688) = 0;
  *(uint8_t *)(this + 8689) = 0;
  *(uint8_t *)(this + 8690) = 0;
  *(uint32_t *)(this + 8692) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CD3F0 sub_5CD3F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD3F0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2171)(uint32_t, int); // ecx
  int result; // eax

  fld_e2171 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2171);
  if ( fld_e2171 != nullptr )
    result = (**fld_e2171)(fld_e2171, 1);
  *(this + 2171) = 0;
  return result;
}



// 硬直字段（this+208）
// ------------------------------------------------------------
// 0x5CD410 sub_5CD410
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD410(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v6; // edi
  int result; // eax
  int nRand; // eax

  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  result = sub_5CD170(this, ArgList, fArg3, nArg4, nArg5);
  if ( v6 == 8 )
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 8));
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 1 )
    {
      result = sub_4DB130(24, 3);
      *(this + 2179) = 0;
    }
  }
  else if ( ArgList != 0 )
  {
    if ( ArgList == 5 )
    {
      if ( *(this + 1943) == 3 )
        return sub_4DB130(24, 5);
      else
        return sub_4DB130(24, 4);
    }
  }
  else
  {
    nRand = rand() % 2;
    return sub_4DB200(24, nRand == 0);
  }
  return result;
}



// 硬直/相位（this+208/8690/8692）
// ------------------------------------------------------------
// 0x5CD4E0 sub_5CD4E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD4E0(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int pThis_348; // edi
  int result; // eax
  int nRand; // eax

  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  result = sub_5CD170((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);
  if ( pThis_348 == 8 )
    result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(
               this,
               *(uint32_t *)(*(uint32_t *)(this + 6216) + 8));
  if ( ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 1 )
    {
      *(uint32_t *)(this + 8692) = 0;
      return sub_4DB130(24, 3);
    }
  }
  else if ( ArgList != 0 )
  {
    if ( ArgList == 5 )
    {
      if ( *(uint32_t *)(this + 7772) == 3 )
        return sub_4DB130(24, 7);
      else
        return sub_4DB130(24, 6);
    }
  }
  else
  {
    nRand = rand() % 2;
    result = sub_4DB200(24, nRand == 0);
    if ( pThis_348 == 8 )
    {
      result = sub_41A5E0(this + 7028);
      if ( result == 2 )
        *(uint8_t *)(this + 8690) = 1;
    }
  }
  return result;
}



// 锤王相位字段（this+8688/8689）
// ------------------------------------------------------------
// 0x5CD5E0 sub_5CD5E0
// ------------------------------------------------------------
char /*thiscall*/ sub_5CD5E0(int this)
{
  int v2; // eax
  int v3; // ebx
  int v4; // ecx
  unsigned int v5; // esi
  int v6; // ecx
  int pObj2; // ecx
  int v8; // esi
  int pObj; // eax
  char result; // al
  int fld_1C54; // [esp+Ch] [ebp-8h]
  int v12; // [esp+10h] [ebp-4h]

  fld_1C54 = *(uint32_t *)(this + 7252);
  v2 = (*(int (/*fastcall*/ **)(int))(*(uint32_t *)fld_1C54 + 700))(fld_1C54);
  v3 = v2;
  v4 = *(uint32_t *)(v2 + 4);
  v5 = 0;
  if ( v4 != 0 )
    v12 = (*(uint32_t *)(v2 + 8) - v4) >> 2;
  else
    v12 = 0;
  if ( v12 > 0 )
  {
    while ( 1 )
    {
      v6 = *(uint32_t *)(v3 + 4);
      if ( v6 != 0 && v5 < (*(uint32_t *)(v3 + 8) - v6) >> 2 )
        pObj2 = *(uint32_t *)(v6 + 4 * v5);
      else
        pObj2 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 92))(pObj2) != 0 )
        break;
      *(uint8_t *)(this + 8688) = 0;
      if ( (int)++v5 >= v12 )
        goto LABEL_13;
    }
    *(uint8_t *)(this + 8688) = 1;
  }
LABEL_13:
  v8 = 0;
  while ( sub_496F80(v8) != 16 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1C54 + 776))(fld_1C54, v8) == 0 )
  {
    ++v8;
    *(uint8_t *)(this + 8689) = 0;
    if ( v8 >= 16 )
      goto LABEL_19;
  }
  pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1C54 + 772))(fld_1C54, v8);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 12))(pObj);
  *(uint8_t *)(this + 8689) = 1;
LABEL_19:
  result = *(uint8_t *)(this + 8688);
  *(uint8_t *)(*(uint32_t *)(this + 7620) + 64) = result != 0 || (result = *(uint8_t *)(this + 8689)) != 0;
  return result;
}



// 砸地技能：TAU_GROUND_HIT 播报（90L；复用 0x5A 牛头系音效 TAG —— 锤王砸地）
// ------------------------------------------------------------
// 0x5CD6F0 sub_5CD6F0
// ------------------------------------------------------------
void /*thiscall*/ sub_5CD6F0(char *this)
{
  bool pThis_94; // zf
  char fld_e8636; // al
  int pThis_21982; // ebx
  uint32_t *pThis_39C; // edi
  int v6; // edx
  int v7; // eax
  int v8; // ebx
  int pThis_80; // edi
  int nRand; // eax
  int pThis_7C; // eax
  int pThis_98; // edi
  uint32_t *pThis_39C22; // edi
  void *pThis_1D; // ecx
  int v15; // ecx
  int pThis_78; // [esp-Ch] [ebp-38h]
  char v17[4]; // [esp+4h] [ebp-28h] BYREF
  void *Block; // [esp+8h] [ebp-24h]
  char *pThis_2198; // [esp+14h] [ebp-18h]
  uint32_t *pThis_39C2; // [esp+18h] [ebp-14h]
  bool v21; // [esp+1Fh] [ebp-Dh]
  int v22; // [esp+28h] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 200))(this) != 0
    && (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 200))(this) == *((uint32_t *)this + 1541) )
  {
    pThis_2198 = this + 8600;
    sub_698F90((int)(this + 8600), 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 200))(this) + 148) == 5;
    fld_e8636 = *(this + 8636);
    if ( pThis_94 )
    {
      if ( fld_e8636 == 0 )
      {
        sub_424120(*(uint32_t **)(*((uint32_t *)this + 29) + 132), 1, 100);
        (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "TAU_GROUND_HIT",
          -1,
          0,
          0);
        *(this + 8636) = 1;
      }
    }
    else if ( fld_e8636 == 1 )
    {
      *(this + 8636) = 0;
    }
    if ( *(this + 8628) != 0 || (pThis_21982 = *((uint32_t *)this + 2156), sub_699000((int)(this + 8600)) < pThis_21982) )  // 【clock_now(clk)】
    {
      *(this + 8628) = 0;
    }
    else
    {
      pThis_39C = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 924))(this, 42)];
      v6 = *(uint32_t *)this;
      pThis_39C2 = pThis_39C;
      v7 = (*(int (/*thiscall*/ **)(char *))(v6 + 152))(this);
      v8 = *pThis_39C;
      v21 = v7 == 0;
      pThis_80 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
      nRand = rand();
      pThis_7C = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, nRand % 40 + pThis_80);
      pThis_98 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 152))(this, pThis_7C + 20) != 0 ? -10 : 10;
      pThis_78 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 120))(this) + pThis_98;
      pThis_39C22 = pThis_39C2;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v8 + 40))(pThis_39C2, pThis_78);
      *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pThis_39C2 + 28))(pThis_39C2) + 84) = v21;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis_39C22 + 12))(pThis_39C22, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, char *))(*pThis_39C22 + 92))(pThis_39C22, v17);
      pThis_1D = *((void **)this + 29);
      v22 = 0;
      sub_4600B0(pThis_1D, 2, 0, (int)v17);
      v15 = (int)pThis_2198;
      *(this + 8628) = 1;
      *(uint8_t *)(v15 + 13) = 0;
      *(uint8_t *)(v15 + 14) = 0;
      sub_698F90(v15, 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// 巨人语音装载：R_GIANT_ATK/ROAR/DMG/DIE + R_GOLEM_AMB（this+8613..8636 相位）
// ------------------------------------------------------------
// 0x5CD8D0 sub_5CD8D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD8D0(int this)
{
  char v3; // [esp-24h] [ebp-2Ch] BYREF
  void *v4; // [esp-20h] [ebp-28h]
  int v5; // [esp-1Ch] [ebp-24h]
  int v6; // [esp-18h] [ebp-20h]
  int v7; // [esp-14h] [ebp-1Ch]
  int v8; // [esp-10h] [ebp-18h]
  int v9; // [esp-Ch] [ebp-14h]
  int v10; // [esp-8h] [ebp-10h]
  size_t v11; // [esp-4h] [ebp-Ch]
  char *v12; // [esp+4h] [ebp-4h]

  v11 = 11;
  v10 = (int)"R_GIANT_ATK";
  *(uint32_t *)(this + 6792) = 2;
  *(uint32_t *)(this + 6796) = 2;
  *(uint32_t *)(this + 6800) = 3;
  *(uint32_t *)(this + 6804) = 4;
  *(uint32_t *)(this + 6808) = 6;
  sub_4015C0((void *)v10, v11);  // 【std::string构造赋值】
  sub_4015C0("R_GIANT_ROAR", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GIANT_DMG", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("R_GIANT_DIE", 0xBu);  // 【std::string构造赋值】
  v11 = 10000;
  v10 = 5000;
  *(uint32_t *)(this + 7324) = 300;
  *(uint32_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8636) = 0;
  v12 = &v3;
  *(uint8_t *)(this + 8613) = 0;
  *(uint8_t *)(this + 8614) = 0;
  v9 = 15;
  v8 = 0;
  LOBYTE(v4) = 0;
  sub_4015C0("R_GOLEM_AMB", 0xBu);  // 【std::string构造赋值】
  return sub_4DE5E0(v3, v4, v5, v6, v7, v8, v9, v10, v11);
}



// 登场曲：sub_406D60 写 "B_FLATANY_01"（47L；与 0x5A6FF0 石魔像同曲）
// ------------------------------------------------------------
// 0x5CD9B0 sub_5CD9B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CD9B0(int *this)
{
  int result; // eax
  int *pThis; // ecx

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        result = sub_406D60("B_FLATANY_01");
      break;
    case 4:
      pThis = this;
      if ( *(this + 1813) != 0 )
        goto LABEL_10;
      goto LABEL_5;
    case 5:
      result = *(this + 1813);
      if ( result == 0 )
LABEL_5:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
      {
        pThis = this;
LABEL_10:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(pThis, 5);
      }
      break;
    default:
      return result;
  }
  return result;
}



// ============================================================
// 【分区 9】玛格纳三巨头（Goliath / Atlas / Titan）（0x5CDA80-0x5CEFD0）
// 证据：SIZZLE_CREATE/ENERGY_CHARGE 充能、Monster/Magma/Animation_Atlas/die.ani +
//       Equipment/Monster/Magma/Atlas/Atlas{Arm,Belly,Head,Leg1,Leg2}Animation/die.ani
//       五部件分体死亡、ThrowWeb.ptl + Animation_Atlas/ThrowWebEffect.ani + QUICK_TURN、
//       UPPER_HIT、Monster/Magma/{Goliath,Atlas,Titan}/* 五件套外观

// 巨人砸地（164L）：Monster/Magma/Animation_Common/DownAttackEffect.ani +
//   TAU_GROUND_HIT 播报（this+200/8632/8680 相位）
// ------------------------------------------------------------
// 0x5CDA80 sub_5CDA80
// ------------------------------------------------------------
char /*thiscall*/ sub_5CDA80(int this)
{
  void *pMem; // eax
  int *v3; // eax
  int v4; // edx
  int fld_21E8; // ecx
  int pThis_94; // eax
  int v7; // edi
  int *v8; // edi
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_98; // ebx
  int pThis_78; // eax
  int fld_74; // ecx
  int *pThis_39C; // edi
  int v20; // eax
  int v21; // eax
  int v22; // edx
  int v23; // ebx
  int v24; // edi
  int nRand; // eax
  int pThis_7C2; // eax
  int pThis_982; // edi
  void *pObj; // edi
  void *fld_742; // ecx
  int pThis_782; // [esp-8h] [ebp-34h]
  void *v32[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+18h] [ebp-14h]
  bool v34; // [esp+1Fh] [ebp-Dh]
  int v35; // [esp+28h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this) == 0 )
    sub_5CD6F0((char *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
  {
    if ( *(uint32_t *)(this + 8680) == 0 )
    {
      pMem = operator new(0x64u);
      Block = pMem;
      v35 = 0;
      if ( pMem != nullptr )
        v3 = (int *)sub_51A7D0(pMem);
      else
        v3 = nullptr;
      *(uint32_t *)(this + 8680) = v3;
      v4 = *v3;
      v35 = -1;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v4 + 64))(v3) + 36) = 0;
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8680) + 80))(*(uint32_t *)(this + 8680)) == 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, uint32_t, int))(**(uint32_t **)(this + 8680) + 56))(
        *(uint32_t *)(this + 8680),
        this,
        this,
        1,
        0,
        0,
        -1);
  }
  else
  {
    fld_21E8 = *(uint32_t *)(this + 8680);
    if ( fld_21E8 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_21E8 + 80))(fld_21E8) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8680) + 76))(*(uint32_t *)(this + 8680), 0);
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 0 )
  {
    pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148);
    if ( pThis_94 == 2 )
    {
      if ( *(uint32_t *)(this + 8632) == 0 )
      {
        *(uint32_t *)(this + 8632) = 1;
        v35 = 1;
        if ( sub_42FCB0(228) != 0 )
          v7 = sub_431860((char)"Monster/Magma/Animation_Common/DownAttackEffect.ani", 1);
        else
          v7 = 0;
        Block = (void *)sub_44B6C0(284);
        v35 = 2;
        if ( Block != nullptr )
          v8 = (int *)sub_44E1F0(v7, 1);
        else
          v8 = nullptr;
        v9 = *(uint32_t *)this;
        v10 = *v8;
        Block = v8;
        v35 = -1;
        v11 = (*(int (/*thiscall*/ **)(int))(v9 + 152))(this);
        v12 = sub_432E50(v11);
        (*(void (/*thiscall*/ **)(int *, int))(v10 + 148))(v8, v12);
        sub_45FE80(*(uint32_t *)(this + 116), (int)v8, 2, 0, (int)v8, this, 0);
        v13 = *v8;
        pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
        pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_80 + 21);
        pThis_98 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, pThis_7C) != 0 ? 150 : -150;
        pThis_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
        (*(void (/*thiscall*/ **)(void *, int))(v13 + 112))(Block, pThis_78 + pThis_98);
      }
    }
    else if ( pThis_94 < 2 )
    {
      return sub_4E1780((uint32_t *)this);
    }
    if ( *(uint32_t *)(this + 8632) == 1 )
    {
      fld_74 = *(uint32_t *)(this + 116);
      *(uint32_t *)(this + 8632) = 3;
      sub_424120(*(uint32_t **)(fld_74 + 132), 4, 400);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "TAU_GROUND_HIT",
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
        this,
        30054,
        2,
        0,
        0,
        100,
        0,
        0,
        4,
        0,
        0,
        0);
      pThis_39C = (int *)dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 924))(this, 40)];
      v20 = *(uint32_t *)this;
      Block = pThis_39C;
      v21 = (*(int (/*thiscall*/ **)(int))(v20 + 152))(this);
      v22 = *(uint32_t *)this;
      v23 = *pThis_39C;
      v34 = v21 == 0;
      v24 = (*(int (/*thiscall*/ **)(int))(v22 + 128))(this);
      nRand = rand();
      pThis_7C2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, nRand % 10 + v24);
      pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, pThis_7C2 + 30) != 0 ? 100 : -100;
      pThis_782 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + pThis_982;
      pObj = Block;
      (*(void (/*thiscall*/ **)(void *, int))(v23 + 40))(Block, pThis_782);
      *(uint8_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 28))(Block) + 84) = v34;
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
      (*(void (/*thiscall*/ **)(void *, void **))(*(uint32_t *)pObj + 92))(pObj, v32);
      fld_742 = *(void **)(this + 116);
      v35 = 3;
      sub_4600B0(fld_742, 2, 0, (int)v32);
      v35 = -1;
      sub_5E5260(v32);
    }
  }
  return sub_4E1780((uint32_t *)this);
}


// 充能态（197L）：SIZZLE_CREATE 生成 + ENERGY_CHARGE 充能播报
//   （this+200/204/208/8684/8685 相位）
// ------------------------------------------------------------
// 0x5CDDD0 sub_5CDDD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CDDD0(uint32_t *this)
{
  void *pMem; // eax
  int pObj; // eax
  int fld_e2178; // ecx
  int fld_e2172; // edi
  int v6; // ebx
  int v7; // edi
  int v8; // eax
  int v9; // eax
  uint64_t v10; // rax
  int fld_e2174; // eax
  int fld_e2173; // edi
  int v13; // ebx
  int v14; // edi
  int v15; // eax
  int v16; // eax
  uint64_t v17; // rax
  int fld_e2175; // eax
  int v19; // eax
  uint32_t *fld_e15542; // eax
  int v21; // edx
  int fld_e1554; // eax
  int v23; // edx
  float Block; // [esp+8h] [ebp-1Ch]
  void *Blocka; // [esp+8h] [ebp-1Ch]
  void *Blockb; // [esp+8h] [ebp-1Ch]
  long double v28; // [esp+Ch] [ebp-18h]
  long double v29; // [esp+Ch] [ebp-18h]
  float v30; // [esp+10h] [ebp-14h]
  int i; // [esp+14h] [ebp-10h]
  int j; // [esp+14h] [ebp-10h]

  v30 = (double)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 6) * 0.0099999998;
  Block = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * v30 < Block )
  {
    fld_e2178 = *(this + 2178);
    if ( fld_e2178 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2178 + 80))(fld_e2178) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2178) + 76))(*(this + 2178), 0);
  }
  else
  {
    if ( *(this + 2178) == 0 )
    {
      pMem = operator new(0x64u);
      if ( pMem != nullptr )
        pObj = sub_51A7D0(pMem);
      else
        pObj = 0;
      *(this + 2178) = pObj;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2178) + 80))(*(this + 2178)) == 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2178) + 56))(
        *(this + 2178),
        this,
        this,
        1,
        0,
        0,
        -1);
  }
  fld_e2172 = *(this + 2172) * (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) / 100;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) < fld_e2172 && *((uint8_t *)this + 8684) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      v6 = 0;
      for ( i = 0; v6 < *(this + 2176); i = v6 )
      {
        v7 = *this;
        v28 = (double)i * 51.42857142857143;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(*this + 152))(
               this,
               0,
               0,
               0,
               0xFFFF,
               0,
               1,
               0,
               0);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 128))(this, v8);
        v10 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v9 + 10)
                               + sin(v28) * 100.0);
        Blocka = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 120))(this, v10);
        fld_e2174 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 376))(
                this,
                *(this + 2174),
                (uint64_t)((double)(int)Blocka + cos(v28) * 100.0));
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v7 + 592))(this, 601, fld_e2174);
        ++v6;
      }
    }
    sub_4DB130(this, 24, 2u);
    *((uint8_t *)this + 8684) = 1;
  }
  fld_e2173 = *(this + 2173) * (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) / 100;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) < fld_e2173 && *((uint8_t *)this + 8685) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      v13 = 0;
      for ( j = 0; v13 < *(this + 2177); j = v13 )
      {
        v14 = *this;
        v29 = (double)j * 51.42857142857143;
        v15 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t))(*this + 152))(
                this,
                0,
                0,
                0,
                0xFFFF,
                0,
                1,
                0,
                0);
        v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 128))(this, v15);
        v17 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v16 + 10)
                               + sin(v29) * 100.0);
        Blockb = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 120))(this, v17);
        fld_e2175 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 376))(
                this,
                *(this + 2175),
                (uint64_t)((double)(int)Blockb + cos(v29) * 100.0));
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v14 + 592))(this, 601, fld_e2175);
        ++v13;
      }
    }
    sub_4DB130(this, 24, 2u);
    *((uint8_t *)this + 8685) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 1 )
  {
    v19 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148);
    if ( v19 != 0 )
    {
      if ( v19 >= 1 && *(this + 2179) == 1 )
      {
        fld_e1554 = *(this + 1554);
        v23 = *this;
        *(this + 2179) = 2;
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v23 + 208))(this, *(uint32_t *)(fld_e1554 + 4));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
          this,
          0,
          *(uint32_t *)(*(this + 1554) + 8),
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "SIZZLE_CREATE",
          -1,
          0,
          0);
      }
    }
    else if ( *(this + 2179) == 0 )
    {
      fld_e15542 = (uint32_t *)*(this + 1554);
      v21 = *this;
      *(this + 2179) = 1;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v21 + 204))(
        this,
        0,
        *fld_e15542,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        0,
        *(uint32_t *)(*(this + 1554) + 4),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "ENERGY_CHARGE",
        -1,
        0,
        0);
    }
  }
  return sub_5CDA80(this);
}


// 阿特拉斯分体死亡（113L）：Monster/Magma/Animation_Atlas/die.ani + Equipment/Monster/
//   Magma/Atlas/Atlas{Arm,Belly,Head,Leg1,Leg2}Animation/die.ani —— 五部件各自倒地
// ------------------------------------------------------------
// 0x5CE240 sub_5CE240
// ------------------------------------------------------------
int /*thiscall*/ sub_5CE240(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int nRand; // eax
  int v8; // ebx
  int v9; // edi
  int ArgLista; // [esp+24h] [ebp+8h]
  int v11; // [esp+28h] [ebp+Ch]
  int v12; // [esp+2Ch] [ebp+10h]
  int v13; // [esp+30h] [ebp+14h]

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  result = sub_5CD170(this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 2 )
        *(this + 2174) = 0;
    }
    else
    {
      return sub_4DB130(24, 2);
    }
  }
  else if ( ArgList != 0 )
  {
    if ( ArgList == 5 )
    {
      if ( *(this + 1943) == 3 )
        sub_4DB130(24, 4);
      else
        sub_4DB130(24, 3);
      if ( sub_42FCB0(228) != 0 )
        v13 = sub_431860((char)"Monster/Magma/Animation_Atlas/die.ani", 1);
      else
        v13 = 0;
      v8 = 0;
      if ( sub_42FCB0(228) != 0 )
        v12 = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasArmAnimation/die.ani", 1);
      else
        v12 = 0;
      if ( sub_42FCB0(228) != 0 )
        v11 = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasBellyAnimation/die.ani", 1);
      else
        v11 = 0;
      if ( sub_42FCB0(228) != 0 )
        ArgLista = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasHeadAnimation/die.ani", 1);
      else
        ArgLista = 0;
      if ( sub_42FCB0(228) != 0 )
        v8 = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasLeg1Animation/die.ani", 1);
      if ( sub_42FCB0(228) != 0 )
        v9 = sub_431860((char)"Equipment/Monster/Magma/Atlas/AtlasLeg2Animation/die.ani", 1);
      else
        v9 = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 196))(this, v13);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        1,
        v12,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        2,
        v11,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        3,
        ArgLista,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        4,
        v8,
        0,
        0,
        0,
        0);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
               this,
               5,
               v9,
               0,
               0,
               0,
               0);
    }
  }
  else
  {
    nRand = rand() % 2;
    return sub_4DB200(24, nRand == 0);
  }
  return result;
}



// 吐丝/转身（125L）：ENERGY_CHARGE + Particle/ThrowWeb.ptl +
//   Animation_Atlas/ThrowWebEffect.ani + QUICK_TURN 播报（sub_431920）
// ------------------------------------------------------------
// 0x5CE500 sub_5CE500
// ------------------------------------------------------------
int /*usercall*/ sub_5CE500@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, float fArg3@<edi>)
{
  int v4; // edi
  int v5; // edi
  uint32_t *v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // edi
  int v11; // eax
  int v12; // edi
  int v13; // ecx
  int *v14; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  float fArg32; // [esp-8h] [ebp-1Ch]
  int v23; // [esp+4h] [ebp-10h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
  {
    fArg32 = fArg3;
    if ( pDwArg1[1943] == 3 )
    {
      v4 = pDwArg1[2171] * (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1) / 100;
      if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1) < v4 && *((uint8_t *)pDwArg1 + 8688) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1069547520);
        sub_4AED60(fArg32);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 672))(pDwArg1, 0);
        sub_4AED60(1.5);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 676))(pDwArg1, 0);
        *((uint8_t *)pDwArg1 + 8688) = 1;
      }
    }
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2 )
    {
      v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148);
      if ( v5 == 0 && pDwArg1[2174] == 0 )
      {
        v6 = (uint32_t *)pDwArg1[1554];
        v7 = *pDwArg1;
        pDwArg1[2174] = 1;
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(
          pDwArg1,
          0,
          *v6,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
          pDwArg1,
          0,
          *(uint32_t *)(pDwArg1[1554] + 4),
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ENERGY_CHARGE", -1, 0, 0);
      }
      if ( pDwArg1[2174] == 1 && v5 == 4 )
      {
        v8 = pDwArg1[1554];
        v9 = *pDwArg1;
        pDwArg1[2174] = 2;
        (*(void (/*thiscall*/ **)(int *, uint32_t, float, int))(v9 + 208))(
          pDwArg1,
          *(uint32_t *)(v8 + 4),
          COERCE_FLOAT(LODWORD(fArg32)),
          nArg2);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)pDwArg1[1554]);
        v10 = *pDwArg1;
        v11 = (*(int (/*thiscall*/ **)(int *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 588))(
                pDwArg1,
                "Particle/ThrowWeb.ptl",
                0,
                65,
                0,
                50,
                4,
                0,
                0,
                0);
        (*(void (/*thiscall*/ **)(int *, int, int, int))(v10 + 580))(pDwArg1, 21015, pDwArg1[2173], v11);
        v12 = 0;
        if ( sub_42FCB0(228) != 0 )
        {
          if ( (unsigned int)pDwArg1[96] < 0x10 )
            LOBYTE(v13) = (uint8_t)pDwArg1 + 108;
          else
            v13 = pDwArg1[91];
          v12 = sub_431920(v13, (char)"Animation_Atlas/ThrowWebEffect.ani", 1);
        }
        if ( sub_44B6C0(284) != 0 )
          v14 = (int *)sub_44E1F0(v12, 1);
        else
          v14 = nullptr;
        sub_45FE80(pDwArg1[29], (int)v14, 2, 0, (int)v14, (int)pDwArg1, 0);
        v15 = *v14;
        v16 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
        (*(void (/*thiscall*/ **)(int *, int))(v15 + 148))(v14, v16);
        if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) != 0 )
          v17 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) + 65;
        else
          v17 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) - 65;
        v18 = *v14;
        v23 = v17;
        v19 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
        v20 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v19 + 50);
        (*(void (/*thiscall*/ **)(int *, int, int))(v18 + 112))(v14, v23, v20 - 10);
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "QUICK_TURN", -1, 0, 0);
      }
    }
  }
  return sub_5CDA80(pDwArg1);
}


// 上勾/充能（134L）：UPPER_HIT + ENERGY_CHARGE 播报（this+200/204/208/8690 相位）
// ------------------------------------------------------------
// 0x5CE7F0 sub_5CE7F0
// ------------------------------------------------------------
char /*thiscall*/ sub_5CE7F0(uint32_t *this)
{
  void *pMem; // eax
  int pObj; // eax
  int fld_e2171; // ecx
  int v5; // eax
  uint32_t *fld_e15542; // eax
  int v7; // edx
  int fld_e1554; // eax
  int v9; // edx
  float Block; // [esp+4h] [ebp-18h]
  float v12; // [esp+8h] [ebp-14h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    if ( *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0 )
      sub_5CD5E0((int)this);
    v12 = (double)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0) * 0.0099999998;
    Block = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * v12 < Block )
    {
      fld_e2171 = *(this + 2171);
      if ( fld_e2171 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2171 + 80))(fld_e2171) == 1 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2171) + 76))(*(this + 2171), 0);
    }
    else
    {
      if ( *(this + 2171) == 0 )
      {
        pMem = operator new(0x64u);
        if ( pMem != nullptr )
          pObj = sub_51A7D0(pMem);
        else
          pObj = 0;
        *(this + 2171) = pObj;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
        sub_4DB130(24, 4);
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2171) + 80))(*(this + 2171)) == 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2171) + 56))(
          *(this + 2171),
          this,
          this,
          1,
          0,
          0,
          -1);
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 1 )
    {
      v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148);
      if ( v5 != 0 )
      {
        if ( v5 >= 1 && *(this + 2173) == 1 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
          fld_e1554 = *(this + 1554);
          v9 = *this;
          *(this + 2173) = 2;
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v9 + 204))(
            this,
            0,
            *(uint32_t *)(fld_e1554 + 8),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "UPPER_HIT",
            -1,
            0,
            0);
        }
      }
      else if ( *(this + 2173) == 0 )
      {
        fld_e15542 = (uint32_t *)*(this + 1554);
        v7 = *this;
        *(this + 2173) = 1;
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(
          this,
          0,
          *fld_e15542,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
          this,
          0,
          *(uint32_t *)(*(this + 1554) + 4),
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "ENERGY_CHARGE",
          -1,
          0,
          0);
      }
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8
      && sub_41A5E0((unsigned int)(this + 1757)) == 2
      && *((uint8_t *)this + 8690) != 0
      && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) == 11 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        48043,
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
      sub_4DB130(24, 5);
      *((uint8_t *)this + 8690) = 0;
    }
  }
  return sub_5CDA80((int)this);
}


// 戈利亚外观：Monster/Magma/Goliath/{GoliathHead,Arm,Belly,Leg1,Leg2}.equ 五件
// ------------------------------------------------------------
// 0x5CEAC0 sub_5CEAC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEAC0(void *this)
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *pMem4; // eax
  char *pMem5; // eax
  char *v8; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int pThis_3104; // eax
  int result; // eax
  char *Block; // [esp+Ch] [ebp-18h]
  char *v15; // [esp+10h] [ebp-14h]
  char *v16; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    Block = sub_4BA9E0(pMem, "Monster/Magma/Goliath/GoliathHead.equ", 0);
  else
    Block = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v15 = sub_4BA9E0(pMem2, "Monster/Magma/Goliath/GoliathArm.equ", 0);
  else
    v15 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v16 = sub_4BA9E0(pMem3, "Monster/Magma/Goliath/GoliathBelly.equ", 0);
  else
    v16 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Magma/Goliath/GoliathLeg1.equ", 0);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v8 = sub_4BA9E0(pMem5, "Monster/Magma/Goliath/GoliathLeg2.equ", 0);
  else
    v8 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v8);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// 阿特拉斯外观：Monster/Magma/Atlas/{AtlasHead,Arm,Belly,Leg1,Leg2}.equ 五件
// ------------------------------------------------------------
// 0x5CEC70 sub_5CEC70
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEC70(void *this)
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *pMem4; // eax
  char *pMem5; // eax
  char *v8; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int pThis_3104; // eax
  int result; // eax
  char *v14; // [esp+Ch] [ebp-18h]
  char *v15; // [esp+10h] [ebp-14h]
  char *v16; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v14 = sub_4BA9E0(pMem, "Monster/Magma/Atlas/AtlasHead.equ", 0);
  else
    v14 = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v15 = sub_4BA9E0(pMem2, "Monster/Magma/Atlas/AtlasArm.equ", 0);
  else
    v15 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v16 = sub_4BA9E0(pMem3, "Monster/Magma/Atlas/AtlasBelly.equ", 0);
  else
    v16 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Magma/Atlas/AtlasLeg1.equ", 0);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v8 = sub_4BA9E0(pMem5, "Monster/Magma/Atlas/AtlasLeg2.equ", 0);
  else
    v8 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v8);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v14);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// 泰坦外观：Monster/Magma/Titan/{TitanHead,Arm,Belly,Leg1,Leg2}.equ 五件
// ------------------------------------------------------------
// 0x5CEE20 sub_5CEE20
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEE20(void *this)
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *pMem4; // eax
  char *pMem5; // eax
  char *v8; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int pThis_3104; // eax
  int result; // eax
  char *v14; // [esp+Ch] [ebp-18h]
  char *v15; // [esp+10h] [ebp-14h]
  char *v16; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v14 = sub_4BA9E0(pMem, "Monster/Magma/Titan/TitanHead.equ", 0);
  else
    v14 = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v15 = sub_4BA9E0(pMem2, "Monster/Magma/Titan/TitanArm.equ", 0);
  else
    v15 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v16 = sub_4BA9E0(pMem3, "Monster/Magma/Titan/TitanBelly.equ", 0);
  else
    v16 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Magma/Titan/TitanLeg1.equ", 0);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v8 = sub_4BA9E0(pMem5, "Monster/Magma/Titan/TitanLeg2.equ", 0);
  else
    v8 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v8);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v14);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// ============================================================
// 【分区 10】法师·阿莫尔（Amor）（0x5CEFD0-0x5CFF60）
// 证据：STAFF_HIT 法杖命中、AMOR_AMB_LOOP 环绕音、CONDITION_HASTE 加速状态播报、
//       this+8840..9012 扩展字段区（与 0x5D 守卫族同构, 见 expeller_guard.cpp）

// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5CEFD0 sub_5CEFD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEFD0(uint8_t *this, void *pArg2, int nArg3, int nArg4)
{
  int result; // eax

  if ( *(this + 8669) == 1 )
    return sub_4D6030((int)this, pArg2, nArg3, nArg4);
  return result;
}



// 法杖命中：STAFF_HIT 播报（this+200/8668..8686 相位）
// ------------------------------------------------------------
// 0x5CEFF0 sub_5CEFF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CEFF0(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  int pThis_C8; // eax
  int pThis_C82; // eax

  if ( *(this + 8668) == 1 && *((uint32_t *)this + 2175) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 144))(this);
    pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 200))(this, 0);
    sub_493400(pThis_C8, 1);
    pThis_C82 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
    sub_4939E0(pThis_C82, 1);
    *(this + 8668) = 1;
    *(this + 8685) = 0;
    *(this + 8686) = 0;
    sub_698F90((int)(this + 8672), 2000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *((uint32_t *)this + 2175) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 )
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "STAFF_HIT",
      -1,
      0,
      0);
  return sub_4DA3B0(nArg2, nArg3, nArg4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF0A0 sub_5CF0A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF0A0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2166)(uint32_t, int); // ecx
  int result; // eax

  fld_e2166 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2166);
  if ( fld_e2166 != nullptr )
    result = (**fld_e2166)(fld_e2166, 1);
  *(this + 2166) = 0;
  return result;
}



// AI 字段访问（this+8722）
// ------------------------------------------------------------
// 0x5CF0C0 sub_5CF0C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF0C0(uint8_t *this, uint8_t *uArg2)
{
  int result; // eax

  result = sub_4D9170(uArg2);
  if ( uArg2 == this && *(this + 8722) == 1 )
    return (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 10);
  return result;
}



// AI 字段访问（this+8668/8700）
// ------------------------------------------------------------
// 0x5CF0F0 sub_5CF0F0
// ------------------------------------------------------------
char /*thiscall*/ sub_5CF0F0(int this)
{
  int pThis_21E0; // ecx
  char result; // al

  pThis_21E0 = this + 8672;
  *(uint8_t *)(pThis_21E0 + 13) = 0;
  *(uint8_t *)(pThis_21E0 + 14) = 0;
  result = sub_698F90(pThis_21E0, 2000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 8700) = 1;
  *(uint8_t *)(this + 8668) = 0;
  return result;
}



// 主状态门（this+200/8668/8672）
// ------------------------------------------------------------
// 0x5CF120 sub_5CF120
// ------------------------------------------------------------
char /*thiscall*/ sub_5CF120(uint8_t *this)
{
  int pThis_21E0; // ecx
  int v3; // eax
  int v4; // eax
  int pThis_C8; // eax

  pThis_21E0 = (int)(this + 8672);
  *(this + 8668) = 0;
  *(uint8_t *)(pThis_21E0 + 13) = 0;
  *(uint8_t *)(pThis_21E0 + 14) = 0;
  sub_698F90(pThis_21E0, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  v3 = *(uint32_t *)this;
  *((uint32_t *)this + 2175) = 2;
  v4 = (*(int (/*thiscall*/ **)(uint8_t *))(v3 + 200))(this);
  sub_4926A0(v4);
  pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  return sub_4939E0(pThis_C8, 0);
}



// 环绕音：AMOR_AMB_LOOP 播报（57L；this+8600/8669/8721）
// ------------------------------------------------------------
// 0x5CF180 sub_5CF180
// ------------------------------------------------------------
char /*thiscall*/ sub_5CF180(uint32_t *this)
{
  int fld_e2176; // eax
  uint32_t *pThis_880; // ebx
  int i; // edi
  int v5; // edi
  int v6; // eax

  if ( *((uint8_t *)this + 8669) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1320))(this);
    fld_e2176 = *(this + 2176);
    pThis_880 = this + 2176;
    if ( fld_e2176 == -1 && *(this + 2177) == -1 && *(this + 2178) == -1 )
    {
      for ( i = 0; i < 3; ++i )
        *pThis_880++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, i);
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(*this + 108))(this, fld_e2176, *(this + 2177), *(this + 2178));
    }
  }
  if ( *((uint8_t *)this + 8600) == 1
    && *((uint8_t *)this + 8669) == 1
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this) >= 0 )
  {
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v5 + 1316))(this, v6);
  }
  if ( (int)*(this + 2175) > 0 && *(this + 50) == 1 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 232))(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 184))(this) == 4
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this) == 4 )
  {
    if ( *((uint8_t *)this + 8721) == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);
      *((uint8_t *)this + 8721) = 0;
    }
  }
  else if ( *((uint8_t *)this + 8721) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "AMOR_AMB_LOOP", 9, 0, 0);
    *((uint8_t *)this + 8721) = 1;
    return sub_4E1780(this);
  }
  return sub_4E1780(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CF2C0 sub_5CF2C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF2C0(int *this)
{
  int v1; // ebx
  int i; // edi
  int v4; // eax
  int v5; // edx
  uint32_t v7[3]; // [esp+Ch] [ebp-14h]
  float v8; // [esp+18h] [ebp-8h]
  int v9; // [esp+1Ch] [ebp-4h]

  v1 = -1;
  v7[0] = 1061158912;
  v7[1] = 1056964608;
  v7[2] = 1045220557;
  for ( i = 0; i < 3; ++i )
  {
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
    v5 = *this;
    v9 = v4;
    v8 = (float)v4;
    v9 = (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this);
    if ( (double)v9 * *(float *)&v7[i] >= v8 )
      ++v1;
  }
  return v1;
}



// AI 字段访问（this+8604）
// ------------------------------------------------------------
// 0x5CF330 sub_5CF330
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF330(uint8_t *this)
{
  int result; // eax

  if ( *(this + 8604) != 1 )
    return sub_4DA1D0();
  return result;
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5CF340 sub_5CF340
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF340(uint8_t *this, int *pDwArg2, int nArg3)
{
  int result; // eax
  int v5; // ebx

  result = sub_4DC390(pDwArg2, nArg3);
  v5 = result;
  if ( result != 3 )
  {
    if ( *(this + 8669) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 )
      {
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) == 1 )
        {
          *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.5);
          return 2;
        }
        else
        {
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 124) == 0 )
            *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.34999999);
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 124) == 1 )
            *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.25);
          return 2;
        }
      }
      else
      {
        return v5;
      }
    }
    else
    {
      *pDwArg2 = (uint64_t)((double)*pDwArg2 * 0.0099999998);
      return 0;
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF430 sub_5CF430
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF430(uint32_t *this)
{
  *(this + 2203) = 1;
  *(this + 2204) = 1;
  *(this + 2205) = 1;
  *(this + 2206) = 1;
  *(this + 2207) = 1;
  *(this + 2208) = 1;
  *(this + 2209) = 0;
  return 1;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF470 sub_5CF470
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF470(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 && (uint8_t)nArg4 == 0 )
    (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 1336))(this, nArg2, nArg3, 0);
  return sub_5CEFF0(this, nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CF4C0 sub_5CF4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF4C0(uint8_t *this, int *pDwArg2, int nArg3)
{
  int pThis_89B; // edx
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) != 8 )
    return sub_5CF340(this, pDwArg2, nArg3);
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 908))(this) >= 4 )
    return sub_5CF340(this, pDwArg2, nArg3);
  pThis_89B = *((uint32_t *)this + (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 908))(this) + 2203);
  result = 1;
  if ( pThis_89B != 1 )
    return sub_5CF340(this, pDwArg2, nArg3);
  return result;
}



// 时钟门 AI（sub_699000; this+200）
// ------------------------------------------------------------
// 0x5CF520 sub_5CF520
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF520(int *this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  int result; // eax
  int fld_e2209; // ecx
  int pObj; // eax
  int dword_79C0B02; // [esp-20h] [ebp-2Ch]
  int nRand2; // [esp-1Ch] [ebp-28h]
  int nRand; // [esp-18h] [ebp-24h]

  result = sub_4D8F90(nArg2, nArg3, nArg4, LODWORD(fArg5));
  if ( (uint8_t)nArg2 == 1 )
  {
    if ( *((uint8_t *)this + 7801) == 1 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 940))(this);
      if ( (uint8_t)result == 0 )
      {
        fld_e2209 = *(this + 2209);
        if ( fld_e2209 != 0 )
        {
          sub_4938F0(fld_e2209);
          pObj = sub_4924C0(0);
          return sub_491D00(dword_79C0B0, nArg3 - (*(uint32_t *)(*(uint32_t *)pObj + 20) >> 1) - 6, nArg4 - *(this + 40) - 30, 0.0);
        }
      }
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( result == 8 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 940))(this);
      if ( (uint8_t)result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this);
        if ( result < 4 )
        {
          result = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this);
          if ( *(this + result + 2203) == 1 )
          {
            result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
            if ( result != 0 && *(this + 2208) == 1 )
            {
              result = sub_699000((int)(this + 9)) - *(this + 1777);  // 【clock_now(clk)】
              if ( result > 1000 )
              {
                nRand = rand() % 8 + nArg4 - 4;
                nRand2 = rand() % 8 + nArg3 - 4;
                dword_79C0B02 = dword_79C0B0;
                (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);
                return sub_491DE0(dword_79C0B02, nRand2, nRand, fArg5, 2, 1, -16776961, -922746881);
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// 阿莫尔相位字段 A（this+8840..8972, 33L —— 与 0x5D 守卫族 88xx 字段区同构）
// ------------------------------------------------------------
// 0x5CF690 sub_5CF690
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF690(int this)
{
  *(uint8_t *)(this + 8853) = 0;
  *(uint8_t *)(this + 8854) = 0;
  *(uint8_t *)(this + 8881) = 0;
  *(uint8_t *)(this + 8882) = 0;
  *(uint8_t *)(this + 8909) = 0;
  *(uint8_t *)(this + 8910) = 0;
  *(uint8_t *)(this + 8924) = 1;
  *(uint32_t *)(this + 8928) = 0;
  *(uint32_t *)(this + 8932) = 0;
  *(uint8_t *)(this + 8936) = 0;
  *(uint8_t *)(this + 8953) = 0;
  *(uint8_t *)(this + 8954) = 0;
  *(uint32_t *)(this + 8968) = 0;
  *(uint32_t *)(this + 8972) = 0;
  *(uint32_t *)(this + 8976) = 0;
  *(uint32_t *)(this + 8980) = 0;
  *(uint32_t *)(this + 8984) = 0;
  *(uint32_t *)(this + 8988) = 0;
  *(uint32_t *)(this + 8992) = 0;
  *(uint32_t *)(this + 8996) = 0;
  *(uint32_t *)(this + 9000) = 0;
  *(uint32_t *)(this + 9004) = 0;
  *(uint32_t *)(this + 9008) = 0;
  return 0;
}



// 阿莫尔相位字段 B（this+8840..8912）
// ------------------------------------------------------------
// 0x5CF740 sub_5CF740
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF740(int this)
{
  *(uint32_t *)(this + 8840) = 0;
  *(uint32_t *)(this + 8844) = 0;
  *(uint8_t *)(this + 8848) = 0;
  *(uint8_t *)(this + 8865) = 0;
  *(uint8_t *)(this + 8866) = 0;
  *(uint32_t *)(this + 8880) = 0;
  *(uint32_t *)(this + 8884) = 0;
  *(uint32_t *)(this + 8888) = 0;
  *(uint32_t *)(this + 8892) = 0;
  *(uint32_t *)(this + 8896) = -1082130432;
  *(uint32_t *)(this + 8900) = 0;
  *(uint32_t *)(this + 8904) = 0;
  *(uint32_t *)(this + 8908) = 0;
  *(uint32_t *)(this + 8912) = 0;
  *(uint32_t *)(this + 8916) = 0;
  *(uint32_t *)(this + 8920) = 0;
  *(uint32_t *)(this + 8924) = 0;
  *(uint32_t *)(this + 8928) = 0;
  *(uint32_t *)(this + 8932) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF7C0 sub_5CF7C0
// ------------------------------------------------------------
void *sub_5CF7C0()
{
  void *result; // eax

  result = dword_8F8528;
  *((uint32_t *)dword_8F8528 + 623) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CF7E0 sub_5CF7E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF7E0(uint8_t *this)
{
  int result; // eax

  if ( *(this + 7801) == 1 )
    return sub_499FF0(this);
  return result;
}



// 阿莫尔相位字段 C（this+8840..9012）
// ------------------------------------------------------------
// 0x5CF7F0 sub_5CF7F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF7F0(int this)
{
  *(uint8_t *)(this + 8840) = 0;
  *(uint8_t *)(this + 8857) = 0;
  *(uint8_t *)(this + 8858) = 0;
  *(uint8_t *)(this + 8872) = 0;
  *(uint8_t *)(this + 8889) = 0;
  *(uint8_t *)(this + 8890) = 0;
  *(uint8_t *)(this + 8929) = 0;
  *(uint8_t *)(this + 8930) = 0;
  *(uint8_t *)(this + 8957) = 0;
  *(uint8_t *)(this + 8958) = 0;
  *(uint32_t *)(this + 8972) = 0;
  *(uint32_t *)(this + 8976) = 0;
  *(uint32_t *)(this + 8980) = 0;
  *(uint32_t *)(this + 9012) = 0;
  *(uint32_t *)(this + 9016) = 0;
  *(uint32_t *)(this + 9020) = 0;
  *(uint32_t *)(this + 9024) = 0;
  *(uint32_t *)(this + 9028) = 0;
  *(uint32_t *)(this + 9032) = 0;
  *(uint32_t *)(this + 9036) = 0;
  *(uint32_t *)(this + 9040) = 0;
  *(uint32_t *)(this + 9044) = 0;
  *(uint32_t *)(this + 9048) = 0;
  return 0;
}



// 加速状态：CONDITION_HASTE 播报（35L）
// ------------------------------------------------------------
// 0x5CF880 sub_5CF880
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF880(int *this)
{
  unsigned int v2; // edi
  int v3; // edx
  unsigned int v4; // edi
  int v5; // edx
  unsigned int v6; // edi
  int v7; // edx
  float fld_e2260; // [esp+8h] [ebp-Ch]
  int v10; // [esp+8h] [ebp-Ch]
  int v11; // [esp+Ch] [ebp-8h]
  int v12; // [esp+Ch] [ebp-8h]
  float fld_e2259; // [esp+10h] [ebp-4h]

  fld_e2259 = (double)*(this + 2259) * 0.0099999998;
  fld_e2260 = (double)*(this + 2260) * 0.0099999998;
  v2 = (*(int (/*stdcall*/ **)(uint32_t))(*this + 672))(0) + 830;
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v2)) + fld_e2259;
  sub_41A590(v2, v3, v11);
  v4 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 858;
  *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v4)) + fld_e2259;
  sub_41A590(v4, v5, v12);
  v6 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 914;
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v6)) + fld_e2260;
  sub_41A590(v6, v7, v10);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CONDITION_HASTE", -1, 0, 0);
  return sub_4DB130(24, *(this + 2243));
}



// 时钟门 AI（sub_699000; this+8840/8857/8858）
// ------------------------------------------------------------
// 0x5CF980 sub_5CF980
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF980(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // eax

  v5 = *this;
  *((uint8_t *)this + 8840) = 1;
  if ( (*(uint8_t (**)(void))(v5 + 940))() == 1 && sub_699000((int)(this + 9)) - *(this + 1777) > 1000 )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 944))(this, 0, -1);
    *((uint8_t *)this + 8857) = 0;
    *((uint8_t *)this + 8858) = 0;
    sub_698F90((int)(this + 2211), *(this + 2253), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return sub_4D4A80(this, nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CF9F0 sub_5CF9F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CF9F0(void *this)
{
  int result; // eax
  int v3; // [esp+8h] [ebp-8h] BYREF
  int v4; // [esp+Ch] [ebp-4h] BYREF

  result = sub_4DC630();
  if ( result == 17 )
  {
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v3);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v4);
    (*(void (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 108))(this, v3, v4, 0);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1104))(this, 13);
    return -1;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CFA60 sub_5CFA60
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFA60(void *this, int nArg2, int nArg3, int nArg4)
{
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) != 0 )
    *(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 348))(this) + 72) = 1120403456;
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// 阿莫尔相位字段 D（this+8853..8888）
// ------------------------------------------------------------
// 0x5CFAA0 sub_5CFAA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFAA0(int this)
{
  *(uint8_t *)(this + 8853) = 0;
  *(uint8_t *)(this + 8854) = 0;
  *(uint8_t *)(this + 8868) = 1;
  *(uint32_t *)(this + 8872) = 0;
  *(uint32_t *)(this + 8876) = 0;
  *(uint32_t *)(this + 8880) = 0;
  *(uint32_t *)(this + 8884) = 0;
  *(uint32_t *)(this + 8888) = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CFAE0 sub_5CFAE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFAE0(uint32_t *this)
{
  *(this + 2210) = 2;
  *(this + 2211) = 0;
  *(this + 2212) = 0;
  *(this + 2213) = 0;
  *(this + 2214) = 0;
  *(this + 2215) = 0;
  *(this + 2216) = 0;
  *(this + 2217) = 0;
  *(this + 2218) = 0;
  *(this + 2219) = 0;
  *(this + 2220) = 0;
  *(this + 2221) = 0;
  *(this + 2222) = 0;
  *(this + 2223) = 0;
  *(this + 2224) = 0;
  *(this + 2225) = 0;
  *(this + 2226) = 0;
  return 0;
}



// 复合门（this+200/8700/8840/8900/8904）
// ------------------------------------------------------------
// 0x5CFB50 sub_5CFB50
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFB50(int this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  int result; // eax
  int fld_22C4; // ebx
  int nRand; // edi
  int fld_22C42; // ebx
  int nRand2; // eax
  int dword_79C0B02; // [esp-24h] [ebp-2Ch]
  int v12; // [esp-1Ch] [ebp-24h]
  int fld_2288; // [esp-Ch] [ebp-14h]
  int fld_22C8; // [esp-8h] [ebp-10h]

  result = sub_5CF520((int *)this, nArg2, nArg3, nArg4, fArg5);
  if ( (uint8_t)nArg2 != 1 && *(uint32_t *)(this + 8840) != 2 && *(uint32_t *)(this + 8700) == -1 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 940))(this);
    if ( (uint8_t)result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
      if ( result != 0 )
      {
        fld_22C4 = *(uint32_t *)(this + 8900);
        nRand = 2 * (rand() % fld_22C4) - fld_22C4;
        fld_22C42 = *(uint32_t *)(this + 8900);
        nRand2 = rand();
        fld_22C8 = (*(uint8_t *)(this + 8904) << 24) | 0xFFFFFF;
        fld_2288 = *(uint32_t *)(this + 4 * *(uint32_t *)(this + 8840) + 8892);
        v12 = nArg4 + 2 * (nRand2 % fld_22C42) - fld_22C42;
        dword_79C0B02 = dword_79C0B0;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
        return sub_491DE0(dword_79C0B02, nArg3 + nRand, v12, fArg5, 2, 1, fld_2288, fld_22C8);
      }
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CFC30 sub_5CFC30
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFC30(uint32_t *this)
{
  int result; // eax

  if ( *(this + 2175) == -1 )
    return sub_4D7C60();  // 【吟唱条/进度渲染（EndofCasting.ani 分支）】
  return result;
}



// AI 字段访问（this+8840）
// ------------------------------------------------------------
// 0x5CFC40 sub_5CFC40
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFC40(int this, int *pDwArg2, int nArg3)
{
  int v5; // edx
  int result; // eax
  int v7; // [esp+18h] [ebp+Ch]

  v7 = sub_5CF4C0((uint8_t *)this, pDwArg2, nArg3);
  if ( *(uint32_t *)(this + 8840) == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) == 0 )
  {
    *pDwArg2 = 0;
    v7 = 1;
  }
  if ( *(uint32_t *)(this + 8840) != 1 )
    return v7;
  v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12);
  result = 1;
  if ( v5 != 1 )
    return v7;
  *pDwArg2 = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5CFCC0 sub_5CFCC0
// ------------------------------------------------------------
int /*fastcall*/ sub_5CFCC0(int pArg1, int nArg2)
{
  *(uint8_t *)(pArg1 + 8840) = 0;
  sub_41A590(pArg1 + 8841, nArg2, 0);
  *(uint32_t *)(pArg1 + 8856) = 0;
  *(uint32_t *)(pArg1 + 8868) = 0;
  *(uint32_t *)(pArg1 + 8872) = 0;
  *(uint32_t *)(pArg1 + 8876) = 0;
  *(uint32_t *)(pArg1 + 8880) = 0;
  *(uint32_t *)(pArg1 + 8884) = 0;
  *(uint32_t *)(pArg1 + 8896) = 0;
  *(uint32_t *)(pArg1 + 8900) = 0;
  *(uint32_t *)(pArg1 + 8904) = 0;
  *(uint32_t *)(pArg1 + 8908) = 0;
  *(uint32_t *)(pArg1 + 8912) = 0;
  *(uint32_t *)(pArg1 + 8916) = 0;
  *(uint32_t *)(pArg1 + 8920) = 0;
  *(uint32_t *)(pArg1 + 8924) = 0;
  *(uint32_t *)(pArg1 + 8928) = 0;
  *(uint32_t *)(pArg1 + 8932) = 0;
  *(uint32_t *)(pArg1 + 8936) = 0;
  *(uint32_t *)(pArg1 + 8860) = 1065353216;
  *(uint32_t *)(pArg1 + 8864) = 1065353216;
  return 1065353216;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5CFD60 sub_5CFD60
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFD60(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2214)(uint32_t, int); // ecx
  int result; // eax

  fld_e2214 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2214);
  if ( fld_e2214 != nullptr )
    result = (**fld_e2214)(fld_e2214, 1);
  *(this + 2214) = 0;
  return result;
}



// AI 字段访问（this+8840）
// ------------------------------------------------------------
// 0x5CFD80 sub_5CFD80
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFD80(uint8_t *this, void *Block)
{
  uint8_t fld_e8840; // al
  int pThis_28; // eax
  int pThis_8B3; // eax
  double v6; // st7
  unsigned int pThis_2A0; // edi
  int v8; // edx
  unsigned int pThis_2A02; // edi
  int v10; // edx
  int v12; // [esp+8h] [ebp-10h]
  float Blocka; // [esp+20h] [ebp+8h]
  int Blockb; // [esp+20h] [ebp+8h]

  fld_e8840 = *(this + 8840);
  if ( fld_e8840 <= 1u )
    *((uint32_t *)this + 2215) = 1065353216;
  else
    *((float *)this + 2215) = (double)(*((uint32_t *)this + 2226) * (fld_e8840 - 1)) * 0.0099999998 + 1.0;
  if ( (uint8_t)Block != 0 )
  {
    if ( fld_e8840 != 2 )
      goto LABEL_10;
    pThis_28 = *((uint32_t *)this + 40) + 20;
  }
  else
  {
    if ( fld_e8840 != 1 )
      goto LABEL_10;
    pThis_28 = *((uint32_t *)this + 40) - 20;
  }
  *((uint32_t *)this + 40) = pThis_28;
LABEL_10:
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
  sub_53F6A0(this);
  if ( *(this + 8840) != 0 )
  {
    if ( operator new(0x8Cu) != nullptr )
      pThis_8B3 = sub_64BBF0(*((uint32_t *)this + 2227), *((uint32_t *)this + 2228), *((uint32_t *)this + 2229));
    else
      pThis_8B3 = 0;
    (*(void (/*thiscall*/ **)(int, uint8_t *, uint8_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pThis_8B3 + 56))(
      pThis_8B3,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  if ( (uint8_t)Block != 0 )
    v6 = 1.0;
  else
    v6 = -1.0;
  Blocka = (double)*((int *)this + 2230) * v6 * 0.0099999998;
  pThis_2A0 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;
  *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + Blocka;
  sub_41A590(pThis_2A0, v8, v12);
  pThis_2A02 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;
  *(float *)&Blockb = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + Blocka;
  sub_41A590(pThis_2A02, v10, Blockb);
  return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
}



// AI 字段访问（this+8841）
// ------------------------------------------------------------
// 0x5CFF20 sub_5CFF20
// ------------------------------------------------------------
int /*thiscall*/ sub_5CFF20(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  unsigned int pThis_2289; // edi
  int pThis_22892; // eax
  int v7; // edx

  pThis_2289 = (unsigned int)this + 8841;
  pThis_22892 = sub_41A5E0((unsigned int)this + 8841);
  sub_41A590(pThis_2289, v7, pThis_22892 + 1);
  return sub_4D4A80(this, nArg2, nArg3, nArg4);
}



// 复合门（this+200/8840/8892..8900）
// ------------------------------------------------------------
// 0x5CFF60 sub_5CFF60
// ------------------------------------------------------------
void /*thiscall*/ sub_5CFF60(int this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  long double dwNow; // st7
  int dword_79C0B02; // [esp-20h] [ebp-2Ch]

  sub_5CF520((int *)this, nArg2, nArg3, nArg4, fArg5);
  if ( (uint8_t)nArg2 != 0
    && *(uint8_t *)(this + 8840) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 940))(this) == 0
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) != 0 )
  {
    dwNow = sin(
           (double)timeGetTime()
         * 6.283184
         / (double)(*(uint32_t *)(this + 8900) / (int)*(uint8_t *)(this + 8840)))
       * (double)(*(uint32_t *)(this + 8896) / 2)
       + (double)*(int *)(this + 8892);
    if ( dwNow > 0.0 && dwNow < 255.0 )
    {
      dword_79C0B02 = dword_79C0B0;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
      sub_491DE0(dword_79C0B02, nArg3, nArg4, fArg5, 2, 1, -16776961, ((uint8_t)(uint64_t)dwNow << 24) | 0xFFFFFF);
    }
  }
}


