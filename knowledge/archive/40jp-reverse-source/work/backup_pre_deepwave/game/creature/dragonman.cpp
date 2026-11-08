// ============================================================
// 【40JP逆向源代码工程】creature/dragonman.cpp
// 模块: 怪物AI 0x5B —— 龙人(Draconian)/光之王齐格/宇宙鱼/ZGM/信徒/炮车/飞艇/魅魔
// 来源: work/dump_monster.txt  区块: 0x5B0000-0x5C0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 233
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：0x5B14D0×4表 / 0x5B2E20×1 / 0x5B7400×9 /
//     0x5B8240×1（虚表农场 0x6CB000-0x6EB000 +512 槽, 纯 Python 直读 PE 定位）；
//     ★ 0x5B4D90×4 表（CNStarFish 系反击 proc 覆写：10%/15%/2% 随机触发 +
//     CNStarFishKing/CNStarFishRukuku RTTI 分型）位于缺口补漏文件 missing_monster.cpp ——
//     本文件 0x5B4820-0x5B6380 缺口区函数均在 missing_monster.cpp（会话 5 审计补齐）
//   · AI 状态：this+200 主状态 / vt+560 反应态 / vt+840=大状态读取器(0x4A1010→this+6556)
//   · 语音 TAG 组（DRAGONMAN_*/ZIEG_*/SFISH_*/BELIEVER_*/WRAITH_*）经 sub_4015C0 写语音槽，
//     vt+212(sub_499110) 播报（研究 28）；sub_431230=vector 打包 setState 参数表
//   · 资源标注：sub_431860/431920=.ani 装载 / sub_4BA9E0=.equ 外观 / sub_4049C0=帧间插值 /
//     sub_406D60=BGM 曲名槽写入 / sub_493D00=动画变速换锚（研究 26）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】龙人·本体（Draconian / Lakius 拉基乌斯）（0x5B00D0-0x5B1890）
// 证据：DRAGONMAN_ATK/ATK_SHORT/ATK_LONG/CAST/SPARK_LOOP/JAIL/STATIC_READY_LOOP 技能播报、
//       DRGM_SHIELD_LOOP、DLAni/EF_Hallucination{1,2}.ani 幻觉、PassiveObject/MapObject/Trap/
//       Particle/Cage.ptl 囚笼、B_RAKIUS_01 登场曲、Monster/Draconian/Lakius/armor.equ、
//       vmt200 格挡覆写 0x5B14D0（GuardEffect.ani）

// AI 相位辅助（50L）
// ------------------------------------------------------------
// 0x5B00D0 sub_5B00D0
// ------------------------------------------------------------
int /*usercall*/ sub_5B00D0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int pObj; // edi
  int nRand; // edx
  int result; // eax

  sub_5AFE80();
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);
      if ( result == 0 && pArg1[1787] != 22 )
      {
        result = pArg1[1813];
        if ( result != 0 )
        {
          result = (*(int (/*cdecl*/ **)(int))(*(uint32_t *)result + 40))(17);
          if ( (uint8_t)result != 0 )
          {
            pObj = pArg1[1813];
            if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 840))(pObj, nArg2) == 8
              || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 7
              || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273)) != 0
              && (result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj)) == 12 )
            {
              result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pObj, 0);
              if ( result < 100 )
              {
                nRand = rand() % 100;
                result = pArg1[1908] != 0 ? 20 : 50;
                if ( nRand < result )
                  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 22);
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B00F0 sub_5B00F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B00F0(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int v5; // edi
  int v6; // edx
  int result; // eax
  unsigned int v8; // edi
  int v9; // edx
  int v10; // [esp+14h] [ebp+8h]
  int v11; // [esp+14h] [ebp+8h]

  if ( nArg2 == 0 )
  {
    *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 1.3;
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.76923078;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;
    sub_41A590(v5, v6, v10);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = nArg3;
  if ( nArg3 == 0 && nArg2 == 1 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v8)) - 0.30000001;
    sub_41A590(v8, v9, v11);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// AI 相位辅助（65L）
// ------------------------------------------------------------
// 0x5B01C0 sub_5B01C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B01C0(char *this, int nArg2, int nArg3)
{
  int result; // eax
  char *pThis_1D73; // ecx
  int v6; // edx
  unsigned int v7; // edi
  int v8; // edx
  int v9; // eax
  unsigned int v10; // edi
  int v11; // edx
  int v12; // [esp+Ch] [ebp-4h]
  int v13; // [esp+18h] [ebp+8h]

  result = 0;
  *(this + 7558) = 0;
  *(this + 7557) = 0;
  *(this + 7556) = 0;
  *(this + 7534) = 0;
  *(this + 7533) = 0;
  *(this + 7532) = 0;
  *(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  pThis_1D73 = this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *((uint32_t *)this + 1893) = 0;
  *((uint32_t *)this + 1892) = 0;
  *((uint32_t *)this + 1891) = 0;
  *((uint32_t *)this + 1897) = 0;
  *((uint32_t *)this + 1896) = 0;
  *((uint32_t *)this + 1895) = 0;
  *((uint32_t *)this + 1894) = 0;
  *((uint32_t *)this + 1899) = 0;
  *((uint32_t *)this + 1895) = 1;
  if ( nArg2 == 0 )
  {
    *(float *)(*((uint32_t *)this + 1905) + 4) = *(float *)(*((uint32_t *)this + 1905) + 4) * 0.76923078;
    *(float *)(*((uint32_t *)this + 1905) + 68) = *(float *)(*((uint32_t *)this + 1905) + 68) * 1.3;
    v6 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;
    v7 = (*(int (/*thiscall*/ **)(char *, uint32_t))(v6 + 672))(this, 0) + 830;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;
    sub_41A590(v7, v8, v12);
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  if ( nArg3 == 0 && nArg2 == 1 )
  {
    v9 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;
    v10 = (*(int (/*thiscall*/ **)(char *, uint32_t))(v9 + 672))(this, 0) + 830;
    *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(v10)) + 0.30000001;
    sub_41A590(v10, v11, v13);
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// AI 相位辅助（94L）
// ------------------------------------------------------------
// 0x5B0320 sub_5B0320
// ------------------------------------------------------------
int /*thiscall*/ sub_5B0320(int *this)
{
  int *pThis; // ebx
  unsigned int v2; // edi
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int result; // eax
  int v7; // eax
  int v8; // edx
  int pObj; // ecx
  int v10; // eax
  int v11; // edx
  int pObj2; // esi
  int v13; // edi
  int nRand; // edi
  int nRand2; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // [esp+Ch] [ebp-10h]
  int v22; // [esp+14h] [ebp-8h]
  unsigned int v23; // [esp+18h] [ebp-4h]

  pThis = this;
  v2 = 0;
LABEL_2:
  while ( 1 )
  {
    v23 = v2;
    v3 = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v3 + 4;
    result = v4 != 0 ? (*(uint32_t *)(v5 + 8) - v4) >> 2 : 0;
    if ( (int)v2 >= result )
      return result;
    v7 = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);
    v8 = *(uint32_t *)(v7 + 8);
    if ( v8 != 0 && v2 < (*(uint32_t *)(v7 + 12) - v8) >> 2 )
      pObj = *(uint32_t *)(v8 + 4 * v2);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
    {
      v10 = (*(int (/*thiscall*/ **)(int *))(*pThis + 80))(pThis);
      v11 = *(uint32_t *)(v10 + 8);
      if ( v11 != 0 && v2 < (*(uint32_t *)(v10 + 12) - v11) >> 2 )
        pObj2 = *(uint32_t *)(v11 + 4 * v2);
      else
        pObj2 = 0;
      if ( (uint8_t)sub_4E4630(pObj2) != 0
        && (*(uint8_t (/*thiscall*/ **)(int *, int))(*pThis + 1244))(pThis, pObj2) == 1 )
      {
        v13 = 0;
        while ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 776))(pObj2, v13) == 0 || rand() % 100 >= 1 )
        {
          if ( ++v13 >= 17 )
          {
            v2 = v23 + 1;
            goto LABEL_2;
          }
        }
        nRand = rand() % 50 - 25;
        nRand2 = rand();
        v20 = *pThis;
        v22 = nRand2 % 50 - 25;
        v16 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 124))(
                pObj2,
                30071,
                10,
                0,
                4,
                100,
                1,
                0,
                0);
        v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v22 + v16);
        v18 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj2 + 124))(pObj2, 0, nRand + v17);
        v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v22 + v18);
        pThis = this;
        (*(void (/*thiscall*/ **)(int *, int))(v20 + 584))(this, nRand + v19);
        v2 = v23;
      }
    }
    ++v2;
  }
}



// AI 相位辅助（92L）
// ------------------------------------------------------------
// 0x5B04A0 sub_5B04A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B04A0(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi
  int v6; // eax
  unsigned int v7; // esi
  int v8; // ecx
  int pObj2; // ecx
  int *pThis; // edi
  int i; // esi
  int v12; // esi
  unsigned int v13; // esi
  int v14; // edx
  int v16; // eax
  int pObj; // ecx
  int pObj3; // eax
  int v19; // [esp+4h] [ebp-8h]
  int v21; // [esp+14h] [ebp+8h]
  int v22; // [esp+14h] [ebp+8h]
  char v23; // [esp+17h] [ebp+Bh]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )
  {
    v23 = 0;
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
    v6 = *(uint32_t *)(v5 + 4);
    v7 = 0;
    if ( v6 != 0 )
      v19 = (*(uint32_t *)(v5 + 8) - v6) >> 2;
    else
      v19 = 0;
    if ( v19 <= 0 )
    {
LABEL_12:
      pThis = this;
    }
    else
    {
      while ( 1 )
      {
        v8 = *(uint32_t *)(v5 + 4);
        if ( v8 != 0 && v7 < (*(uint32_t *)(v5 + 8) - v8) >> 2 )
          pObj2 = *(uint32_t *)(v8 + 4 * v7);
        else
          pObj2 = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 92))(pObj2) != 0 )
          break;
        if ( (int)++v7 >= v19 )
          goto LABEL_12;
      }
      v16 = *(uint32_t *)(v5 + 4);
      if ( v16 != 0 && v7 < (*(uint32_t *)(v5 + 8) - v16) >> 2 )
        pObj = *(uint32_t *)(v16 + 4 * v7);
      else
        pObj = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);
      pThis = this;
      sub_4DB130(24, 0);
      v23 = 1;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 956))(nArg2);
    }
    for ( i = 0; i < 16; ++i )
    {
      if ( sub_496F80(i) == 16 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 776))(nArg2, i) != 0 )
      {
        pObj3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 772))(nArg2, i);
        (*(void (/*thiscall*/ **)(int, uint32_t, int *))(*(uint32_t *)pObj3 + 4))(pObj3, 0, pThis);
        goto LABEL_19;
      }
    }
    if ( v23 != 1 )
      return sub_5AFB00(this, nArg2, nArg3, nArg4);
    pThis = this;
LABEL_19:
    v12 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pThis + 672))(pThis, 0);
    v21 = sub_41A5E0(v12 + 60);
    if ( (double)pThis[2160] + (double)pThis[2160] > (double)(int)(uint64_t)((double)v21
                                                                               * COERCE_FLOAT(sub_41A5E0(v12 + 74))) )
    {
      v13 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 74;
      *(float *)&v22 = COERCE_FLOAT(sub_41A5E0(v13)) + 0.1;
      sub_41A590(v13, v14, v22);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    }
  }
  return sub_5AFB00(this, nArg2, nArg3, nArg4);
}



// 龙人语音装载：DRAGONMAN_DMG/DIE + DRAGONMAN_FIND 发现播报（sub_4015C0+sub_699000）
// ------------------------------------------------------------
// 0x5B0660 sub_5B0660
// ------------------------------------------------------------
int /*thiscall*/ sub_5B0660(uint32_t *this)
{
  int v3; // [esp+4h] [ebp-4h] BYREF

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("DRAGONMAN_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("DRAGONMAN_DIE", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("DRAGONMAN_FIND", 0xEu);  // 【std::string构造赋值】
  *(this + 2151) = 0;
  *(this + 2152) = sub_699000((int)(this + 9));
  v3 = 100000;
  return sub_4E1390(196614, &v3);
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5B0700 sub_5B0700
// ------------------------------------------------------------
void /*thiscall*/ sub_5B0700(uint32_t *this)
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( rand() % 100 < 50
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1813) + 40))(*(this + 1813), 17) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 100 )
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = rand() % 3;
    sub_431230((int)v2, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// AI 相位辅助（this+8614）
// ------------------------------------------------------------
// 0x5B07C0 sub_5B07C0
// ------------------------------------------------------------
char /*thiscall*/ sub_5B07C0(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // eax
  void *pBuf[4]; // [esp+Ch] [ebp-24h] BYREF
  float fld_e29; // [esp+1Ch] [ebp-14h] BYREF
  int v12; // [esp+20h] [ebp-10h]
  int v13; // [esp+2Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0 )
    return 0;
  if ( *(this + 1943) != 3 )
    return 0;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0 )
    return 0;
  if ( *((uint8_t *)this + 8614) != 0 )
    return 0;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) <= 0 )
    return 0;
  v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
  v2 = *this;
  fld_e29 = (float)v12;
  v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v2 + 740))(this);
  if ( (double)v12 * 0.5 <= fld_e29 )
    return 0;
  v3 = *this;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v4);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v3 + 136))(this, v5 - 80) != 1 )
    return 0;
  v6 = *this;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v7);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v6 + 136))(this, v8 + 80) != 1 )
    return 0;
  memset(&pBuf[1], 0, 12);
  v13 = 0;
  LODWORD(fld_e29) = rand() % 2;
  sub_431230((int)pBuf, &fld_e29);
  fld_e29 = COERCE_FLOAT(sub_460230(*(this + 29)));
  sub_431230((int)pBuf, &fld_e29);
  (*(void (/*thiscall*/ **)(uint32_t *, int, void **, int, uint32_t))(*this + 560))(this, 15, pBuf, 2, 0);
  sub_5E5260(pBuf);
  return 1;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5B0930 sub_5B0930
// ------------------------------------------------------------
void /*thiscall*/ sub_5B0930(uint32_t *this)
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && *(this + 1943) == 3 )
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 3;
    sub_431230((int)v2, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 囚笼技能：PassiveObject/MapObject/Trap/Particle/Cage.ptl（51L；sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B09C0 sub_5B09C0
// ------------------------------------------------------------
int /*usercall*/ sub_5B09C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *v6; // eax
  int v7; // edi
  bool v8; // cc
  int v9; // edi
  int v10; // edi
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  void *Block; // [esp+4h] [ebp-14h]
  int v15; // [esp+8h] [ebp-10h]

  result = pArg1[1813];
  if ( result != 0 )
  {
    if ( pArg1[2151] == 0 )
    {
      pMem = operator new(0x12Cu);
      if ( pMem != nullptr )
        v6 = sub_428F30(pMem, (int)"PassiveObject/MapObject/Trap/Particle/Cage.ptl", 0);
      else
        v6 = nullptr;
      pArg1[2151] = v6;
    }
    v7 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[1813] + 120))(pArg1[1813], nArg3, nArg2);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) < v7;
    v9 = (*(int (**)(void))(*(uint32_t *)pArg1[1813] + 120))();
    if ( v8 )
      v15 = v9 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
    else
      v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - v9;
    v10 = *pArg1;
    Block = (void *)pArg1[2151];
    v11 = (*(int (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813], 500, 4, 0);
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);
    v13 = (*(int (/*thiscall*/ **)(void *, uint32_t, int, int))(*(uint32_t *)Block + 28))(Block, 0, v15, v11 - v12);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v10 + 580))(pArg1, 267, 0, v13);
    result = sub_699000((int)(pArg1 + 9)) + 2000;  // 【clock_now(clk)】
    pArg1[2152] = result;
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_RAKIUS_01"（拉基乌斯曲目槽, 83L）
// ------------------------------------------------------------
// 0x5B0AF0 sub_5B0AF0
// ------------------------------------------------------------
char /*thiscall*/ sub_5B0AF0(uint32_t *this)
{
  char result; // al
  int fld_e1813; // eax
  int fld_e18132; // edi
  int pObj; // edi
  int v6; // ebx

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
      if ( *(this + 1943) != 3 )
        goto LABEL_24;
      sub_406D60("B_RAKIUS_01");
      return sub_5B07C0(this);
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_14;
      if ( rand() % 100 >= 20 )
        goto LABEL_24;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
      return sub_5B07C0(this);
    case 5:
      if ( *(this + 1813) == 0 )
        goto LABEL_14;
      if ( rand() % 100 >= 30 )
        goto LABEL_24;
      goto LABEL_5;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) == 0 )
        goto LABEL_24;
LABEL_5:
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      result = sub_5B07C0(this);
      break;
    case 0x16:
      if ( *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 )
      {
        fld_e1813 = *(this + 1813);
        if ( fld_e1813 != 0
          && ((fld_e18132 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813),
               (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < fld_e18132)
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0
           || (pObj = *(this + 1813),
               (v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) >= (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj))
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1) )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
          result = sub_5B07C0(this);
        }
        else
        {
          if ( rand() % 100 < 20 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
            sub_5B0700(this);
          }
LABEL_24:
          result = sub_5B07C0(this);
        }
      }
      else
      {
LABEL_14:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
        result = sub_5B07C0(this);
      }
      break;
    default:
      goto LABEL_24;
  }
  return result;
}



// 龙人主技能组（313L 全族最大）：vt+212 连播 DRAGONMAN_ATK / ATK_SHORT /
//   STATIC_READY_LOOP / ATK_LONG / CAST / SPARK_LOOP / JAIL + DRGM_SHIELD_LOOP；
//   sub_431920 装载 DLAni/EF_Hallucination1/2.ani 幻觉特效
// ------------------------------------------------------------
// 0x5B0CF0 sub_5B0CF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B0CF0(int *this)
{
  int result; // eax

  sub_5B0AF0(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
    return sub_5B0320(this);
  return result;
}



// ------------------------------------------------------------
// 0x5B0D10 sub_5B0D10
// ------------------------------------------------------------
void /*userpurge*/ sub_5B0D10(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)
{
  int v7; // edi
  int v8; // eax
  int v9; // edx
  int v10; // edx
  int v11; // edi
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ecx
  int v20; // edi
  int *v21; // edi
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // edx
  int v27; // eax
  int v28; // edx
  void **v29; // eax
  int pObj; // eax
  size_t *v31; // edi
  int v32; // eax
  int v33; // edi
  int v34; // eax
  int v35; // eax
  int v36; // edi
  int v37; // eax
  int pObj5; // edi
  int v39; // eax
  int pObj2; // ecx
  int v41; // eax
  int v42; // edi
  int v43; // eax
  int v44; // edi
  int pObj4; // ecx
  int pObj3; // ecx
  int v47; // eax
  int v48; // [esp-10h] [ebp-28h]
  int v49; // [esp-4h] [ebp-1Ch]
  int ArgLista; // [esp+20h] [ebp+8h]

  v7 = pDwArg1[1639];
  if ( v7 == 15 )
  {
    if ( ArgList != 16 )
      return;
    goto LABEL_23;
  }
  if ( v7 != 0 )
  {
    if ( v7 == 14 )
    {
      if ( ArgList != 14 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 8));
        (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 9);
      }
    }
    else if ( v7 == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )
    {
      if ( ArgList == 8 )
      {
LABEL_14:
        if ( **(uint32_t **)(pArg4 + 4) == 4
          && (pDwArg1[1813] == 0
           || (uint8_t)sub_5AFE40(pDwArg1[1813]) == 1
           || sub_699000((int)(pDwArg1 + 9)) < (unsigned int)pDwArg1[2152]) )  // 【clock_now(clk)】
        {
          **(uint32_t **)(pArg4 + 4) = 0;
        }
        goto LABEL_19;
      }
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 10);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 12));
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 12);
    *((uint8_t *)pDwArg1 + 8613) = 0;
  }
  if ( ArgList == 8 )
    goto LABEL_14;
LABEL_19:
  if ( v7 == 8 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1 && ArgList != 8 )
  {
    v8 = pDwArg1[1554];
    v9 = *pDwArg1;
    *((uint8_t *)pDwArg1 + 8601) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v9 + 208))(pDwArg1, *(uint32_t *)(v8 + 16));
    fArg2 = ((double (/*thiscall*/ *)(int *, uint32_t))*(uint32_t *)(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 20));
  }
LABEL_23:
  sub_4E33D0((int)pDwArg1, pArg4, fArg2, ArgList, pArg4, *(float *)&nArg5, *(float *)&nArg6);
  switch ( ArgList )
  {
    case 0:
      *((uint8_t *)pDwArg1 + 8613) = 0;
      break;
    case 8:
      v10 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8612) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v10 + 212))(pDwArg1, "DRAGONMAN_ATK", -1, 0, 0);
      switch ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) )
      {
        case 0:
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
            pDwArg1,
            "DRAGONMAN_ATK_SHORT",
            -1,
            0,
            0);
          break;
        case 1:
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
            pDwArg1,
            "DRAGONMAN_STATIC_READY_LOOP",
            11,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 16));
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 20));
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
            pDwArg1,
            100,
            *(uint32_t *)(pDwArg1[1554] + 16),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
            pDwArg1,
            100,
            *(uint32_t *)(pDwArg1[1554] + 20),
            0,
            0,
            0,
            0);
          break;
        case 2:
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
            pDwArg1,
            "DRAGONMAN_ATK_LONG",
            -1,
            0,
            0);
          break;
        case 3:
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
            pDwArg1,
            200,
            *(uint32_t *)(pDwArg1[1554] + 12),
            0,
            0,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 12));
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRAGONMAN_CAST", -1, 0, 0);
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(
            pDwArg1,
            "DRAGONMAN_SPARK_LOOP",
            10,
            0,
            0);
          break;
        case 4:
          sub_5B09C0(pDwArg1);
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRAGONMAN_JAIL", -1, 0, 0);
          break;
        default:
          return;
      }
      break;
    case 14:
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 4));
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
        pDwArg1,
        200,
        *(uint32_t *)(pDwArg1[1554] + 8),
        0,
        0,
        0,
        0);
      sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 8));
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DRGM_SHIELD_LOOP", 9, 0, 0);
      break;
    case 15:
      v11 = 0;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
      *((uint16_t *)pDwArg1 + 4310) = **(uint16_t **)(pArg4 + 4);
      ArgLista = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4);
      *((uint8_t *)pDwArg1 + 8614) = 1;
      if ( sub_42FCB0(228) != 0 )
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          LOBYTE(v12) = (uint8_t)pDwArg1 + 108;
        else
          v12 = pDwArg1[91];
        v11 = sub_431920(v12, (char)"DLAni/EF_Hallucination1.ani", 1);
      }
      if ( sub_44B6C0(284) != 0 )
        v13 = sub_44E1F0(v11, 0);
      else
        v13 = 0;
      v14 = pDwArg1[29];
      pDwArg1[2154] = v13;
      sub_45FE80(v14, v11, 2, 0, v13, (int)pDwArg1, 0);
      v15 = *(uint32_t *)pDwArg1[2154];
      v16 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
      v17 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v16);
      v18 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v17);
      (*(void (/*thiscall*/ **)(int, int))(v15 + 112))(pDwArg1[2154], v18);
      if ( sub_42FCB0(228) != 0 )
      {
        if ( (unsigned int)pDwArg1[96] < 0x10 )
          LOBYTE(v19) = (uint8_t)pDwArg1 + 108;
        else
          v19 = pDwArg1[91];
        v20 = sub_431920(v19, (char)"DLAni/EF_Hallucination2.ani", 1);
      }
      else
      {
        v20 = 0;
      }
      if ( sub_44B6C0(284) != 0 )
        v21 = (int *)sub_44E1F0(v20, 1);
      else
        v21 = nullptr;
      sub_45FE80(pDwArg1[29], (int)v21, 2, 0, (int)v21, (int)pDwArg1, 0);
      v22 = *v21;
      v49 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
      v23 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
      v24 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v23 + 1);
      (*(void (/*thiscall*/ **)(int *, int))(v22 + 112))(v21, v24);
      v25 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);
      v26 = *pDwArg1;
      pDwArg1[2156] = v25;
      pDwArg1[2157] = (*(int (/*thiscall*/ **)(int *))(v26 + 124))(pDwArg1);
      v27 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
      v28 = *pDwArg1;
      pDwArg1[2158] = v27;
      v29 = (void **)(*(int (/*thiscall*/ **)(int *, int))(v28 + 672))(pDwArg1, 3);
      pObj = sub_4ABE10((void *)0x47, *v29, 0);
      pDwArg1[2159] = pObj;
      v31 = (size_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) + 4);
      v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2159] + 340))(pDwArg1[2159]);
      sub_4014D0((size_t *)(v32 + 4), v31, 0, 0xFFFFFFFF);
      v33 = *(uint32_t *)pDwArg1[2159];
      v34 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 376))(pDwArg1);
      (*(void (/*thiscall*/ **)(int, int))(v33 + 372))(pDwArg1[2159], v34);
      v48 = pDwArg1[2159];
      v35 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
      sub_45FE80(v35, v33, 100, ArgLista, v48, 0, 0);
      v36 = *(uint32_t *)pDwArg1[2159];
      v37 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
      (*(void (/*thiscall*/ **)(int, int))(v36 + 148))(pDwArg1[2159], v37);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2159] + 604))(pDwArg1[2159], 0);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 604))(pDwArg1, 0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2159] + 112))(pDwArg1[2159], -10000, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t))(*pDwArg1 + 112))(pDwArg1, -10000, 0, 0);
      pObj5 = pDwArg1[2159];
      v39 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 684))(pDwArg1);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 684))(pObj5, v39);
      sub_46AE40(v49);
      *(uint8_t *)(pDwArg1[2159] + 8614) = 1;
      break;
    case 16:
      pObj2 = pDwArg1[2159];
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 604))(pObj2, 1);
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 604))(pDwArg1, 1);
      v41 = pDwArg1[2156];
      v42 = v41;
      if ( *((uint16_t *)pDwArg1 + 4310) != 0 )
      {
        v43 = v41 - 80;
        v44 = v42 + 80;
      }
      else
      {
        v43 = v41 + 80;
        v44 = v42 - 80;
      }
      (*(void (/*thiscall*/ **)(int *, int, int, int))(*pDwArg1 + 112))(pDwArg1, v43, pDwArg1[2157], pDwArg1[2158]);
      pObj4 = pDwArg1[2159];
      if ( pObj4 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 112))(pObj4, v44, pDwArg1[2157], pDwArg1[2158]);
      pObj3 = pDwArg1[2154];
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj3 + 84))(pObj3, 0);
      v47 = *pDwArg1;
      pDwArg1[2154] = 0;
      pDwArg1[2159] = 0;
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(v47 + 472))(pDwArg1, 0, 0, 1, 1);
      break;
    default:
      return;
  }
}


// 【vmt200 命中处理器覆写】格挡反应 handler（虚表 0x6E2AB4/0x6E2FDC/0x6E3504/0x6E3A2C 四张 +512 槽, 145L）：
//   Character/Swordman/Effect/Animation/{GuardSpark,GuardCircle}.ani +
//   Monster/Draconian/PassiveObject/GuardEffect.ani 龙人专属盾 + SWD_GUARDED + DRAGONMAN_DMG
// ------------------------------------------------------------
// 0x5B14D0 sub_5B14D0
// ------------------------------------------------------------
int /*userpurge*/ sub_5B14D0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, float *pArg4, int nArg5)
{
  float *pArg42; // edi
  unsigned int v7; // ebx
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int pObj2; // edi
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // edi
  int pObj3; // edi
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // edi
  int pObj; // edi
  int v26; // ebx
  int v27; // ebx
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // edi
  int v34; // [esp-4h] [ebp-28h]
  int v35; // [esp+Ch] [ebp-18h]
  int v36; // [esp+Ch] [ebp-18h]
  int v37; // [esp+10h] [ebp-14h]
  int v38; // [esp+14h] [ebp-10h]

  pArg42 = pArg4;
  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) != 14 || (uint8_t)nArg5 != 0 )
    goto LABEL_33;
  if ( *((uint8_t *)pDwArg1 + 642) != 0 )
  {
    v7 = pDwArg1[161];
    goto LABEL_9;
  }
  v8 = pDwArg1[30];
  if ( v8 != 0 )
  {
    if ( *(uint32_t *)(v8 + 148) == -1 )
      sub_4938F0(pDwArg1[30]);
    v7 = *(uint32_t *)(v8 + 112);
LABEL_9:
    if ( v7 > 1 )
      goto LABEL_33;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 12) != 0
    || (v35 = *pDwArg1,
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3),
        (*(uint8_t (/*thiscall*/ **)(int *, int))(v35 + 180))(pDwArg1, v9) != 0) )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1104))(pDwArg1, 13);
  }
  else
  {
    *((uint8_t *)pDwArg1 + 8600) = 1;
  }
  if ( *((uint8_t *)pDwArg1 + 8600) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int, int))(*pDwArg1 + 876))(
      pDwArg1,
      0,
      300,
      300,
      0,
      -3000,
      1,
      nArg2);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 888))(pDwArg1, 0, 0, 1000, 1000);
    v10 = *pDwArg1;
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
    v12 = sub_432E50(v11);
    (*(void (/*thiscall*/ **)(int *, int))(v10 + 896))(pDwArg1, v12);
    v36 = (uint64_t)(pArg4[3] * 0.5 + *pArg4);
    v37 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*pDwArg1 + 124))(pDwArg1, (uint64_t)(pArg4[3] * 0.5 + *pArg4) >> 32);
    v38 = (uint64_t)(pArg4[5] * 0.5 + pArg4[2]);
    v13 = sub_42FCB0(228);
    v14 = 0;
    if ( v13 != 0 )
      v14 = sub_431860(v13, "Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
    if ( sub_44B6C0(284) != 0 )
      pObj2 = sub_44E1F0(v14, 1);
    else
      pObj2 = 0;
    sub_45FE80(pDwArg1[29], pObj2, 2, 0, pObj2, (int)pDwArg1, 0);
    v16 = *(uint32_t *)pObj2;
    v17 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
    (*(void (/*thiscall*/ **)(int, int))(v16 + 148))(pObj2, v17);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, v36, v37, v38);
    v18 = sub_42FCB0(228);
    if ( v18 != 0 )
      v19 = sub_431860(v18, "Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
    else
      v19 = 0;
    if ( sub_44B6C0(284) != 0 )
      pObj3 = sub_44E1F0(v19, 1);
    else
      pObj3 = 0;
    sub_45FE80(pDwArg1[29], pObj3, 2, 0, pObj3, (int)pDwArg1, 0);
    v21 = *(uint32_t *)pObj3;
    v22 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
    (*(void (/*thiscall*/ **)(int, int))(v21 + 148))(pObj3, v22);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 112))(pObj3, v36, v37, v38);
    v23 = sub_42FCB0(228);
    if ( v23 != 0 )
      v24 = sub_431860(v23, "Monster/Draconian/PassiveObject/GuardEffect.ani", 1);
    else
      v24 = 0;
    if ( sub_44B6C0(284) != 0 )
      pObj = sub_44E1F0(v24, 1);
    else
      pObj = 0;
    sub_45FE80(pDwArg1[29], pObj, 2, 0, pObj, (int)pDwArg1, 0);
    v26 = *(uint32_t *)pObj;
    v34 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
    (*(void (/*thiscall*/ **)(int))(v26 + 148))(pObj);
    v27 = *(uint32_t *)pObj;
    v28 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
    v29 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v28);
    v30 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v29 + 1);
    (*(void (/*thiscall*/ **)(int, int))(v27 + 112))(pObj, v30);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, pDwArg1);
    sub_4A06D0(v34);
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t))(*pDwArg1 + 212))(pDwArg1, "SWD_GUARDED", -1, 0);
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pArg42 = pArg4;
  }
LABEL_33:
  v31 = sub_4DA3B0(nArg3, pArg42, nArg5);
  *((uint8_t *)pDwArg1 + 8600) = 0;
  sub_4015C0("DRAGONMAN_DMG", 0xDu);  // 【std::string构造赋值】
  return v31;
}


// ============================================================
// 【分区 2】光之王·齐格（Zieg / Lord of Light）（0x5B1890-0x5B3230）
// 证据：ZIEG_FLOAT_LOOP/LAUGH/NOVA_READY_LOOP/CAST_NOVA/LASER_FIRE/DIE_EFFECT、
//       SHIELD_FLASH、R_ZIEG_DMG/ZIEG_DIE_VOICE、ConcentrationEffect.ani 聚焦、
//       Monster/LordofLight/LOL/{Die.ani,Armor,Glow,Wing}.equ、LOLParticle/{DieArmorParticle,
//       DieHikari}.ptl、vmt200 覆写 0x5B2E20（LOL/GuardEffect.ani）

// 外观装载：Monster/Draconian/Lakius/armor.equ（拉基乌斯甲壳）
// ------------------------------------------------------------
// 0x5B1890 sub_5B1890
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1890(void *this)
{
  char *pMem; // eax
  char *v3; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Draconian/Lakius/armor.equ", 0);
  else
    v3 = nullptr;
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// 子类扩展字段复位（this+8628..8640）
// ------------------------------------------------------------
// 0x5B1910 sub_5B1910
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1910(int this)
{
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8636) = 0;
  *(uint8_t *)(this + 8638) = 0;
  *(uint32_t *)(this + 8640) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B1940 sub_5B1940
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1940(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2157)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2158)(uint32_t, int); // ecx

  fld_e2157 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2157);
  if ( fld_e2157 != nullptr )
    result = (**fld_e2157)(fld_e2157, 1);
  fld_e2158 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2158);
  *(this + 2157) = 0;
  if ( fld_e2158 != nullptr )
    result = (**fld_e2158)(fld_e2158, 1);
  *(this + 2158) = 0;
  return result;
}



// 浮空播报：ZIEG_FLOAT_LOOP（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B1980 sub_5B1980
// ------------------------------------------------------------
int /*thiscall*/ sub_5B1980(uint32_t *this)
{
  int result; // eax

  sub_4D9760();
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
    this,
    "ZIEG_FLOAT_LOOP",
    45566,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2154) = result;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B1F10 sub_5B1F10
// ------------------------------------------------------------
int /*usercall*/ sub_5B1F10@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int v2; // edi
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int result; // eax

  sub_4D9600();
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = pArg1[2160];
    if ( result == 0 && pArg1[1943] == 3 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2, nArg2);
      v2 = *(uint32_t *)dword_8F8520;
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);
      (*(void (/*thiscall*/ **)(int, int))(v2 + 36))(dword_8F8520, v3);
      v4 = *(uint32_t *)dword_8F8520;
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
      (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, v5);
      v6 = *(uint32_t *)dword_8F8520;
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);
      v8 = *(uint32_t *)dword_8F8520;
      v9 = sub_460230(pArg1[29]);
      (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B1F50 sub_5B1F50
// ------------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int /*userpurge*/ sub_5B1F50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)
{
  int result; // eax
  int v6; // ebx
  int64_t v7; // rax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  int v12; // edi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);
    if ( v6 != 0 )
    {
      v8 = *(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44);
      v9 = *(uint32_t *)(v8 + 364);
      v10 = v8 + 360;
      if ( v9 != 0 )
        v11 = (*(uint32_t *)(v10 + 8) - v9) >> 5;
      else
        v11 = 0;
      v7 = 1374389535LL * (224 * v11 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));
    }
    else
    {
      v7 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
    }
    v12 = (SHIDWORD(v7) >> 5) + (HIDWORD(v7) >> 31);
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
             pArg1,
             nArg4,
             v12,
             0,
             0,
             70,
             0,
             120,
             v6,
             0,
             0,
             0);
  }
  return result;
}



// 笑播报：ZIEG_LAUGH（this+8608 相位, 62L）
// ------------------------------------------------------------
// 0x5B2010 sub_5B2010
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B2010(int *this, int nArg2)
{
  int v3; // edx
  int fld_e81; // edi
  uint32_t *fld_e28; // edi
  int v6; // edx
  unsigned int result; // eax
  unsigned int v8; // ecx
  int i; // edx
  int fld_e1905; // edi

  v3 = *this;
  *(this + 81) = nArg2;
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v3 + 876))(0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
  sub_4926A0(*(this + 30));
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);
  fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  if ( fld_e81 != 0 )
  {
    sub_495890(0, fld_e81 <= 0 ? 1000 : -1000);
    sub_4A0550(fld_e81);
    sub_4A0600(2);
  }
  else
  {
    fld_e28 = (uint32_t *)*(this + 28);
    if ( *fld_e28 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
      && *((float *)fld_e28 + 6) != 0.0 )
    {
      fld_e28[6] = 0;
      *((uint8_t *)fld_e28 + 196) = 1;
    }
    sub_495890(2, 0);
  }
  v6 = *this;
  *((uint8_t *)this + 8608) = 0;
  *(this + 2153) = 0;
  result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v6 + 212))(this, "ZIEG_LAUGH", -1, 0, 0);
  v8 = 0;
  for ( i = 0; ; i += 32 )
  {
    fld_e1905 = *(this + 1905);
    if ( fld_e1905 == 0 )
      break;
    result = (*(this + 1906) - fld_e1905) >> 5;
    if ( v8 >= result )
      break;
    result = i + fld_e1905;
    ++v8;
    *(uint8_t *)(i + fld_e1905) = 0;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B2160 sub_5B2160
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B2160(unsigned int *this)
{
  unsigned int v1; // edx
  int i; // esi
  int fld_e1905; // edi
  unsigned int result; // eax

  v1 = 0;
  for ( i = 0; ; i += 32 )
  {
    fld_e1905 = *(this + 1905);
    if ( fld_e1905 == 0 )
    {
      result = *(this + 2151);
      *(this + 81) = result;
      return result;
    }
    result = (int)(*(this + 1906) - fld_e1905) >> 5;
    if ( v1 >= result )
      break;
    ++v1;
    *(uint8_t *)(i + fld_e1905) = 1;
  }
  *(this + 81) = *(this + 2151);
  return result;
}



// 盾闪：SHIELD_FLASH 播报（this+8644 相位）
// ------------------------------------------------------------
// 0x5B21B0 sub_5B21B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B21B0(uint8_t *this)
{
  int v2; // eax
  unsigned int v3; // edi
  int v4; // eax
  int v5; // edx
  int v6; // ebx
  uint32_t *pThis_612; // edi
  int pThis_1B4; // eax

  v2 = *(uint32_t *)this;
  *(this + 8644) = 1;
  v3 = (*(int (/*stdcall*/ **)(uint32_t))(v2 + 672))(0) + 466;
  v4 = sub_41A5E0(v3);
  sub_41A590(v3, v5, v4 + 50);
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  v6 = *(uint32_t *)this;
  pThis_612 = (uint32_t *)(*((uint32_t *)this + 1554) + 24);
  pThis_1B4 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 436))(this, 0, 0);
  (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, int))(v6 + 204))(this, 100, *pThis_612, 0, -pThis_1B4);
  return (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
           this,
           "SHIELD_FLASH",
           -1,
           0,
           0);
}



// AI 字段访问（this+8644）
// ------------------------------------------------------------
// 0x5B2230 sub_5B2230
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2230(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int v5; // edi
  int v6; // edx
  float v7; // [esp+0h] [ebp-4h]
  int v8; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )
      return result;
    result = nArg2;
    if ( nArg2 == 0 )
    {
      *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 672))(this, 0, 1050253722);
      sub_4AED60(v7);
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    }
LABEL_8:
    if ( --result != 0 )
      return result;
    goto LABEL_9;
  }
  if ( *((uint8_t *)this + 8644) == 0 )
    sub_5B21B0(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
  *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;
  sub_41A590(v5, v6, v8);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  result = nArg2;
  if ( nArg2 != 0 )
    goto LABEL_8;
LABEL_9:
  *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;
  return result;
}



// AI 相位辅助（this+8644, 75L）
// ------------------------------------------------------------
// 0x5B2310 sub_5B2310
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2310(int *this, int nArg2, int nArg3)
{
  int pThis_1D73; // ecx
  int result; // eax
  int v6; // edx
  int v7; // edx
  unsigned int v8; // edi
  int v9; // edx
  float v10; // [esp+0h] [ebp-8h]
  int v11; // [esp+14h] [ebp+Ch]

  *((uint8_t *)this + 7558) = 0;
  *((uint8_t *)this + 7557) = 0;
  *((uint8_t *)this + 7556) = 0;
  *((uint8_t *)this + 7534) = 0;
  *((uint8_t *)this + 7533) = 0;
  *((uint8_t *)this + 7532) = 0;
  *((uint8_t *)this + 7531) = 0;
  *(int *)((char *)this + 7535) = 0;
  pThis_1D73 = (int)this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *(uint32_t *)(pThis_1D73 + 4) = 0;
  *(uint32_t *)(pThis_1D73 + 8) = 0;
  *(uint32_t *)(pThis_1D73 + 12) = 0;
  *(uint8_t *)(pThis_1D73 + 16) = 0;
  *(this + 1893) = 0;
  *(this + 1892) = 0;
  *(this + 1891) = 0;
  *(this + 1897) = 0;
  *(this + 1896) = 0;
  *(this + 1895) = 0;
  *(this + 1894) = 0;
  *(this + 1899) = 0;
  *((uint8_t *)this + 7538) = 1;
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )
      return result;
    result = nArg2;
    if ( nArg2 == 0 )
    {
      *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) + *(float *)(*(this + 1905) + 68);
      v6 = *this;
      *(this + 1899) = 50;
      (*(void (/*thiscall*/ **)(int *, uint32_t, int))(v6 + 672))(this, 0, 1050253722);
      sub_4AED60(v10);
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    }
LABEL_8:
    if ( --result != 0 )
      return result;
    goto LABEL_9;
  }
  if ( *((uint8_t *)this + 8644) == 0 )
    sub_5B21B0(this);
  v7 = *this;
  *(this + 1899) = 50;
  v8 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v7 + 672))(this, 0) + 830;
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v8)) + 0.30000001;
  sub_41A590(v8, v9, v11);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
  result = nArg2;
  if ( nArg2 != 0 )
    goto LABEL_8;
LABEL_9:
  *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) + *(float *)(*(this + 1905) + 68);
  return result;
}



// 新星技能：ZIEG_NOVA_READY_LOOP 蓄力 + ZIEG_CAST_NOVA 施放（136L；
//   this+204/+208 硬直与 8624/8637 相位）
// ------------------------------------------------------------
// 0x5B2480 sub_5B2480
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B2480(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v5; // ebx
  int fld_199C; // edi
  uint32_t *fld_1848; // eax
  float fArg32; // edi
  int fld_1C54; // eax
  unsigned int result; // eax
  int *fld_18482; // eax

  v5 = ArgList;
  fld_199C = *(uint32_t *)(this + 6556);
  if ( ArgList == 15 )
  {
    sub_5B2160((unsigned int *)this);
    v5 = 0;
  }
  if ( fld_199C == 14 )
  {
    if ( v5 != 15 )
      sub_5B2160((unsigned int *)this);
  }
  else
  {
    if ( fld_199C != 8 )
      goto LABEL_13;
    if ( v5 == 8 )
      goto LABEL_14;
    if ( sub_41A5E0(this + 7028) == 1 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
      fld_1848 = (uint32_t *)(*(uint32_t *)(this + 6216) + 8);
    }
    else
    {
      if ( sub_41A5E0(this + 7028) != 2 )
        goto LABEL_13;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 16));
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 20));
      fld_1848 = (uint32_t *)(*(uint32_t *)(this + 6216) + 12);
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *fld_1848);
  }
LABEL_13:
  if ( v5 != 8 )
  {
    fArg32 = fArg3;
    goto LABEL_19;
  }
LABEL_14:
  fArg32 = fArg3;
  if ( *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) == 1 )
  {
    fld_1C54 = *(uint32_t *)(this + 7252);
    if ( fld_1C54 != 0
      && (*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)this + 8))(this, fld_1C54, 0) < *(uint32_t *)(*(uint32_t *)(this + 7620) + 80) )
    {
      *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) = 2;
    }
  }
LABEL_19:
  result = sub_4E33D0(v5, fArg32, nArg4, nArg5);
  switch ( v5 )
  {
    case 5:
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45566);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45567);
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 45568);
    case 8:
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);
      *(uint8_t *)(this + 8637) = 0;
      if ( sub_41A5E0(this + 7028) == 1 )
      {
        return sub_5B1CD0(this);
      }
      else
      {
        result = sub_41A5E0(this + 7028);
        if ( result == 2 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "ZIEG_NOVA_READY_LOOP",
            45568,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "ZIEG_CAST_NOVA",
            -1,
            0,
            0);
          fld_18482 = (int *)(*(uint32_t *)(this + 6216) + 16);
          *(uint8_t *)(this + 8624) = 0;
          sub_4926A0(*fld_18482);
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 20));
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 12));
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            100,
            *(uint32_t *)(*(uint32_t *)(this + 6216) + 16),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
            this,
            100,
            *(uint32_t *)(*(uint32_t *)(this + 6216) + 20),
            0,
            0,
            0,
            0);
          return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
                   this,
                   100,
                   *(uint32_t *)(*(uint32_t *)(this + 6216) + 12),
                   0,
                   0,
                   0,
                   0);
        }
      }
      break;
    case 14:
      return sub_5B2010((int *)this, **(uint32_t **)(LODWORD(fArg32) + 4));
    default:
      break;
  }
  return result;
}


// 齐格语音：R_ZIEG_DMG + ZIEG_DIE_VOICE（this+8600/8604/8636 相位）
// ------------------------------------------------------------
// 0x5B2720 sub_5B2720
// ------------------------------------------------------------
bool /*thiscall*/ sub_5B2720(int this)
{
  int fld_144; // eax
  bool result; // al

  sub_4015C0("R_ZIEG_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("ZIEG_DIE_VOICE", 0xEu);  // 【std::string构造赋值】
  fld_144 = *(uint32_t *)(this + 324);
  *(uint32_t *)(this + 8600) = 20;
  *(uint32_t *)(this + 8604) = fld_144;
  result = (uint8_t)sub_47C080(20) == 0;
  *(uint8_t *)(this + 8636) = result;
  return result;
}



// 参数打包 AI（sub_431230+sub_699000）
// ------------------------------------------------------------
// 0x5B2780 sub_5B2780
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2780(uint32_t *this)
{
  int pThis_9; // edi
  int v3; // eax
  int v4; // edx
  uint8_t v5[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v7; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]
  uint32_t v9[4]; // [esp+18h] [ebp-10h] BYREF

  pThis_9 = (int)(this + 9);
  if ( sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2154) + 15000) )  // 【clock_now(clk)】
  {
    v3 = sub_699000(pThis_9);  // 【clock_now(clk)】
    v4 = *this;
    *(this + 2154) = v3;
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 840))(this) == 0 && *(this + 1813) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
      v9[0] = 200;
      Block = nullptr;
      v7 = 0;
      v8 = 0;
      v9[3] = 0;
      sub_431230((int)v5, v9);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 14, v5, 0, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5B2840 sub_5B2840
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2840(uint32_t *this)
{
  uint8_t v2[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v4; // [esp+10h] [ebp-18h]
  int v5; // [esp+14h] [ebp-14h]
  uint32_t v6[4]; // [esp+18h] [ebp-10h] BYREF

  v6[0] = *(uint32_t *)(*(this + 1905) + 80) + *(uint32_t *)(*(this + 1905) + 88);
  if ( (int)sub_4E0CD0(17, 0, 0, (uint64_t)((double)v6[0] * 1.5)) >= 2 && rand() % 100 < 40 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 2;
    sub_431230((int)v2, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B2900 sub_5B2900
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2900(uint32_t *this)
{
  sub_5B1BA0();
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1813) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0 )
  {
    sub_5B2840(this);
  }
}



// 激光技能：ZIEG_LASER_FIRE 播报 + Common/CommonEffect/Animation/ConcentrationEffect.ani
//   聚焦特效（103L；sub_431860）
// ------------------------------------------------------------
// 0x5B2940 sub_5B2940
// ------------------------------------------------------------
char /*usercall*/ sub_5B2940@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // edx
  int v5; // eax
  int v6; // ebx
  char *v7; // eax
  int *v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int *v15; // eax
  int v17; // [esp+8h] [ebp-10h]

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) != 2 || *(uint8_t *)(pArg1 + 8621) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) != 5 || *(uint8_t *)(pArg1 + 8622) != 0 )
    {
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);
      if ( *(uint32_t *)(v14 + 148) == 6 )
      {
        LOBYTE(v14) = *(uint8_t *)(pArg1 + 8623);
        if ( (uint8_t)v14 == 0 )
        {
          v15 = (int *)(*(uint32_t *)(pArg1 + 6216) + 4);
          *(uint8_t *)(pArg1 + 8623) = 1;
          sub_4926A0(*v15);
          sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 8));
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
            pArg1,
            100,
            *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
            pArg1,
            200,
            *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 8),
            0,
            0,
            0,
            0);
          LOBYTE(v14) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 45567);
        }
      }
    }
    else
    {
      *(uint8_t *)(pArg1 + 8622) = 1;
      sub_5B1F50((uint32_t *)pArg1, nArg2, nArg3, 46003);
      LOBYTE(v14) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
                      pArg1,
                      "ZIEG_LASER_FIRE",
                      -1,
                      0,
                      0);
    }
  }
  else
  {
    v4 = *(uint32_t *)pArg1;
    *(uint8_t *)(pArg1 + 8621) = 1;
    if ( (*(int (/*thiscall*/ **)(int))(v4 + 152))(pArg1) != 0 )
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 70;
    else
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 70;
    v17 = v5;
    v6 = 0;
    if ( sub_42FCB0(228) != 0 )
      v6 = sub_431860((char)"Common/CommonEffect/Animation/ConcentrationEffect.ani", 1);
    v7 = (char *)sub_44B6C0(284);
    v8 = (int *)v7;
    if ( v7 != nullptr )
    {
      sub_44E0D0(v7, v6, 1);
      *v8 = (int)&CNRDPooledObject::`vftable';
    }
    else
    {
      v8 = nullptr;
    }
    sub_45FE80(*(uint32_t *)(pArg1 + 116), (int)v8, 2, 0, (int)v8, pArg1, 0);
    v9 = *v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
    v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v10 + 120);
    (*(void (/*thiscall*/ **)(int *, int, int))(v9 + 112))(v8, v17, v11);
    v12 = *v8;
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);
    (*(void (/*thiscall*/ **)(int *, int))(v12 + 148))(v8, v13);
    LOBYTE(v14) = sub_5B1F50((uint32_t *)pArg1, v12, (int)v8, 48029);
  }
  return v14;
}



// 齐格死亡演出（129L）：Monster/LordofLight/LOL/Die.ani + LOLParticle/
//   {DieArmorParticle.ptl 装甲飞散, DieHikari.ptl 光尘} + ZIEG_DIE_EFFECT 播报
// ------------------------------------------------------------
// 0x5B2B80 sub_5B2B80
// ------------------------------------------------------------
void /*thiscall*/ sub_5B2B80(int *this)
{
  int v2; // ebx
  int *v3; // eax
  int *v4; // edi
  int fld_e29; // ecx
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  void *pMem; // eax
  int *pThis_5B; // eax
  int v14; // edx
  int fld_e2157; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  void *fld_e292; // ecx
  void *pMem2; // eax
  int *pThis_5B2; // eax
  int v22; // edx
  int fld_e2158; // edi
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int fld_e21582; // eax
  uint8_t v28[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  uint8_t v30[4]; // [esp+1Ch] [ebp-20h] BYREF
  void *v31; // [esp+20h] [ebp-1Ch]
  void *pMem3; // [esp+2Ch] [ebp-10h]
  int v33; // [esp+38h] [ebp-4h]

  v2 = 0;
  v33 = 0;
  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Monster/LordofLight/LOL/Die.ani", 1);
  v3 = (int *)sub_44B6C0(284);
  v4 = v3;
  pMem3 = v3;
  v33 = 1;
  if ( v3 != nullptr )
  {
    sub_44E0D0((char *)v3, v2, 1);
    *v4 = (int)&CNRDPooledObject::`vftable';
  }
  else
  {
    v4 = nullptr;
  }
  fld_e29 = *(this + 29);
  v33 = -1;
  sub_45FE80(fld_e29, (int)v4, 2, 0, (int)v4, (int)this, 0);
  v6 = *v4;
  v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v7);
  v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
  (*(void (/*thiscall*/ **)(int *, int))(v6 + 112))(v4, v9);
  v10 = *v4;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(int *, int))(v10 + 144))(v4, v11);
  pMem = operator new(0x12Cu);
  pMem3 = pMem;
  v33 = 2;
  if ( pMem != nullptr )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      pThis_5B = (int *)sub_4C3640((int)pMem, (int)(this + 91), (int)"LOLParticle/DieArmorParticle.ptl", (int)this);
    else
      pThis_5B = (int *)sub_4C3640((int)pMem, *(this + 91), (int)"LOLParticle/DieArmorParticle.ptl", (int)this);
  }
  else
  {
    pThis_5B = nullptr;
  }
  *(this + 2157) = (int)pThis_5B;
  v14 = *pThis_5B;
  v33 = -1;
  (*(void (/*thiscall*/ **)(int *, uint32_t))(v14 + 12))(pThis_5B, 0);
  fld_e2157 = *(uint32_t *)*(this + 2157);
  v16 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v17 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v16 + 50);
  v18 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v17);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2157 + 40))(*(this + 2157), v18);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2157) + 92))(*(this + 2157), v30);
  fld_e292 = (void *)*(this + 29);
  v33 = 3;
  sub_4600B0(fld_e292, 2, 0, (int)v30);
  pMem2 = operator new(0x12Cu);
  pMem3 = pMem2;
  LOBYTE(v33) = 4;
  if ( pMem2 != nullptr )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      pThis_5B2 = (int *)sub_4C3640((int)pMem2, (int)(this + 91), (int)"LOLParticle/DieHikari.ptl", (int)this);
    else
      pThis_5B2 = (int *)sub_4C3640((int)pMem2, *(this + 91), (int)"LOLParticle/DieHikari.ptl", (int)this);
  }
  else
  {
    pThis_5B2 = nullptr;
  }
  *(this + 2158) = (int)pThis_5B2;
  v22 = *pThis_5B2;
  LOBYTE(v33) = 3;
  (*(void (/*thiscall*/ **)(int *, uint32_t))(v22 + 12))(pThis_5B2, 0);
  fld_e2158 = *(uint32_t *)*(this + 2158);
  v24 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v25 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v24 + 50);
  v26 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v25);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2158 + 40))(*(this + 2158), v26);
  fld_e21582 = (*(int (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2158) + 92))(*(this + 2158), v28);
  LOBYTE(v33) = 5;
  sub_4E77D0((int)v30, fld_e21582);
  LOBYTE(v33) = 3;
  if ( Block != nullptr )
    j__free(Block);
  sub_4600B0((void *)*(this + 29), 2, 0, (int)v30);
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "ZIEG_DIE_EFFECT", -1, 0, 0);
  if ( v31 != nullptr )
    j__free(v31);
}


// 【vmt200 命中处理器覆写】光之王格挡 handler（虚表 0x6E447C +512 槽, 48L）：
//   Monster/LordOfLight/LOL/GuardEffect.ani 专属格挡特效（sub_431860）
// ------------------------------------------------------------
// 0x5B2E20 sub_5B2E20
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2E20(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // ebx
  char *v6; // eax
  int pObj; // edi
  int v8; // ebx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v14; // [esp-Ch] [ebp-20h]

  if ( *((uint8_t *)this + 8644) != 0 )
  {
    v5 = 0;
    if ( sub_42FCB0(228) != 0 )
      v5 = sub_431860((char)"Monster/LordOfLight/LOL/GuardEffect.ani", 1);
    v6 = (char *)sub_44B6C0(284);
    pObj = (int)v6;
    if ( v6 != nullptr )
    {
      sub_44E0D0(v6, v5, 1);
      *(uint32_t *)pObj = &CNRDPooledObject::`vftable';
    }
    else
    {
      pObj = 0;
    }
    sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);
    v8 = *(uint32_t *)pObj;
    v14 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int))(v8 + 148))(pObj);
    v9 = *(uint32_t *)pObj;
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
    v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11 + 1);
    (*(void (/*thiscall*/ **)(int, int))(v9 + 112))(pObj, v12);
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);
    sub_4A06D0(v14);
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);
}



// AI 相位辅助（this+8636/8640）
// ------------------------------------------------------------
// 0x5B2F40 sub_5B2F40
// ------------------------------------------------------------
int /*thiscall*/ sub_5B2F40(int this, int nArg2)
{
  int fld_21C0; // edi
  int pThis_1B4; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int fld_21C02; // edi
  int pThis_98; // eax
  int fld_21C03; // edi
  int v10; // eax
  int pThis_982; // [esp-Ch] [ebp-14h]

  if ( this != nArg2 )
    return sub_4D9170(nArg2);
  if ( *(uint32_t *)(this + 7772) != 3 || *(uint32_t *)(this + 8640) == 0 || *(uint8_t *)(this + 8636) != 1 )
  {
    sub_5B2B80((int *)this);
    return sub_4D9170(nArg2);
  }
  fld_21C0 = **(uint32_t **)(this + 8640);
  pThis_1B4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 436))(this);
  pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_1B4);
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_21C0 + 112))(*(uint32_t *)(this + 8640), pThis_78);
  fld_21C02 = **(uint32_t **)(this + 8640);
  pThis_98 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_21C02 + 144))(*(uint32_t *)(this + 8640), pThis_98);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8640) + 308))(*(uint32_t *)(this + 8640)) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 8640) + 580))(
      *(uint32_t *)(this + 8640),
      48001,
      1,
      0,
      0,
      0,
      0,
      0,
      4,
      0,
      0,
      0);
  fld_21C03 = *(uint32_t *)(this + 8640);
  pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 10000);
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_21C03 + 64))(fld_21C03);
  sub_50EF20(v10, "......", pThis_982);
  return sub_4D9170(nArg2);
}



// 技能播报：ZIEG_NOVA_FIRE + SWING_LONG 挥击
// ------------------------------------------------------------
// 0x5B3050 sub_5B3050
// ------------------------------------------------------------
void /*usercall*/ sub_5B3050(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v3; // edx
  int v5; // eax
  int v6; // eax

  sub_4E1780((uint32_t *)pArg1);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 14 )
  {
    sub_5B1D20(pArg1);
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 8 )
  {
    v5 = sub_41A5E0(pArg1 + 7028);
    if ( v5 != 0 )
    {
      v6 = v5 - 1;
      if ( v6 != 0 )
      {
        if ( v6 == 1
          && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 4
          && *(uint8_t *)(pArg1 + 8624) == 0 )
        {
          v3 = *(uint32_t *)pArg1;
          *(uint8_t *)(pArg1 + 8624) = 1;
          (*(void (/*thiscall*/ **)(int, int))(v3 + 216))(pArg1, 45568);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "ZIEG_NOVA_FIRE",
            -1,
            0,
            0);
        }
      }
      else
      {
        sub_5B2940(pArg1, nArg2, nArg3);
      }
    }
    else if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3 && *(uint8_t *)(pArg1 + 8637) == 0 )
    {
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "SWING_LONG", -1, 0, 0);
      *(uint8_t *)(pArg1 + 8637) = 1;
    }
  }
  else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )
  {
    sub_5B2780((uint32_t *)pArg1);
  }
}



// 齐格外观装载：Monster/LordofLight/LOL/{Armor,Glow,Wing}.equ 三件（甲/辉光/翼）
// ------------------------------------------------------------
// 0x5B3100 sub_5B3100
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3100(uint8_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  int v4; // edx
  int pObj; // eax
  char *pMem2; // eax
  char *v7; // eax
  int v8; // edx
  int pObj2; // eax
  char *pMem3; // eax
  char *v11; // eax
  int v12; // edx
  int pObj3; // eax
  int v15; // [esp+8h] [ebp-10h] BYREF
  int v16; // [esp+14h] [ebp-4h]

  pMem = (char *)operator new(0x544u);
  v16 = 0;
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/LordofLight/LOL/Armor.equ", 0);
  else
    v3 = nullptr;
  v4 = *(uint32_t *)this;
  v16 = -1;
  pObj = (*(int (/*thiscall*/ **)(uint8_t *, char *))(v4 + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  v16 = 1;
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/LordofLight/LOL/Glow.equ", 0);
  else
    v7 = nullptr;
  v8 = *(uint32_t *)this;
  v16 = -1;
  pObj2 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(v8 + 784))(this, v7);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = (char *)operator new(0x544u);
  v16 = 2;
  if ( pMem3 != nullptr )
    v11 = sub_4BA9E0(pMem3, "Monster/LordofLight/LOL/Wing.equ", 0);
  else
    v11 = nullptr;
  v12 = *(uint32_t *)this;
  v16 = -1;
  pObj3 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(v12 + 784))(this, v11);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  *(this + 8644) = 0;
  v15 = 100000;
  return sub_4E1390(196614, &v15);
}



// ============================================================
// 【分区 3】宇宙鱼·克罗库塔（SpaceFish / Crokuta）（0x5B3230-0x5B6380）
// 证据：SFISH_BUG_SPIT/BUG_FIRE/FIND/BITE/DMG/DIE、Particle/BugShot.ptl、
//       Particle/CrokutaDestroyHead.ptl + JOINT1-5/TAIL 分段破坏（0x5B4430）、BUFF_TAKE、
//       ★ 0x5B4820-0x5B6380 缺口区在 missing_monster.cpp（含 vmt200 覆写 0x5B4D90）

// 子类扩展字段复位（this+8600..8620）
// ------------------------------------------------------------
// 0x5B3230 sub_5B3230
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3230(int this)
{
  *(uint32_t *)(this + 8600) = 1;
  *(uint8_t *)(this + 8612) = 0;
  *(uint8_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8616) = 0;
  return 0;
}



// 虫弹技能：引用 Particle/BugShot.ptl（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B3250 sub_5B3250
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3250(uint32_t *this)
{
  int result; // eax
  int v3; // eax

  *(this + 2152) = sub_699000((int)(this + 9));
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
      v3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BugShot.ptl");
    else
      v3 = 0;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
             this,
             30013,
             *(this + 2150),
             v3,
             0,
             0,
             0,
             0,
             4,
             0,
             0,
             0);
  }
  return result;
}



// AI 字段访问（this+8620）
// ------------------------------------------------------------
// 0x5B32C0 sub_5B32C0
// ------------------------------------------------------------
char /*thiscall*/ sub_5B32C0(int this, int nArg2)
{
  int fld_1C54; // ebx
  int fld_1DA8; // eax
  bool v5; // zf

  fld_1C54 = *(uint32_t *)(this + 7252);
  LOBYTE(fld_1DA8) = sub_4D97E0(nArg2);
  if ( fld_1C54 != nArg2 && nArg2 != 0 )
  {
    LOBYTE(fld_1DA8) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
    if ( (uint8_t)fld_1DA8 != 0 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);
      v5 = (uint8_t)sub_53FD00(nArg2) == 1;
      LOBYTE(fld_1DA8) = *(uint8_t *)(this + 8620);
      if ( v5 )
      {
        if ( (uint8_t)fld_1DA8 == 0 )
        {
          fld_1DA8 = *(uint32_t *)(this + 7592) + 50;
          *(uint8_t *)(this + 8620) = 1;
          *(uint32_t *)(this + 7592) = fld_1DA8;
        }
      }
      else if ( (uint8_t)fld_1DA8 == 1 )
      {
        fld_1DA8 = *(uint32_t *)(this + 7592) - 50;
        *(uint8_t *)(this + 8620) = 0;
        *(uint32_t *)(this + 7592) = fld_1DA8;
      }
    }
  }
  return fld_1DA8;
}



// 主状态门（this+200/8612）
// ------------------------------------------------------------
// 0x5B3350 sub_5B3350
// ------------------------------------------------------------
char /*thiscall*/ sub_5B3350(int this)
{
  int pThis_348; // eax

  sub_4E1780((uint32_t *)this);
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( pThis_348 == 8 && (sub_41A5E0(this + 7028) == 1 || (pThis_348 = sub_41A5E0(this + 7028)) == 2) )
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8612);
    if ( (uint8_t)pThis_348 == 0 )
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
      if ( *(uint8_t *)(pThis_348 + 170) != 0 )
      {
        LOBYTE(pThis_348) = sub_5B3250((uint32_t *)this);
        *(uint8_t *)(this + 8612) = 1;
      }
    }
  }
  return pThis_348;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B33C0 sub_5B33C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B33C0(int *this)
{
  int v2; // edi
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);
  result = *(this + 1639);
  if ( result == 0 && v2 != 4 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v2);
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v2);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3400 sub_5B3400
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3400(uint32_t *this)
{
  *(this + 2151) = 30010;
  *(this + 2154) = 1;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3420 sub_5B3420
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3420(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

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
  *(uint8_t *)(this + 7557) = 1;
  *(uint32_t *)(this + 7588) = 1;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7596) = 0;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = -50;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B34D0 sub_5B34D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B34D0(uint32_t *this)
{
  int v2; // [esp+0h] [ebp-4h] BYREF

  *(this + 2151) = 30011;
  *(this + 2154) = 2;
  v2 = 100000;
  return sub_4E1390(196613, &v2);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3510 sub_5B3510
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3510(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

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
  *(uint8_t *)(this + 7557) = 1;
  *(uint32_t *)(this + 7588) = 1;
  nArg32 = nArg3;
  *(uint32_t *)(this + 7596) = 0;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = 50;
  return result;
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5B35C0 sub_5B35C0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5B35C0(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint64_t result; // rax
  float v5; // [esp+Ch] [ebp-1Ch]
  float v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+20h] [ebp-8h]
  int v8; // [esp+24h] [ebp-4h]

  v2 = *this;
  *(this + 2151) = 30012;
  v7 = (*(int (/*stdcall*/ **)(int))(v2 + 384))(12);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 13);
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v6 = (float)v8;
  v5 = (float)v7;
  result = (uint64_t)sub_4049C0(v5, v6, *v3 - 1, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2150) = result;
  *(this + 2154) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3640 sub_5B3640
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3640(void *this)
{
  int pObj; // eax

  sub_4DE410();
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 700))(this);
  sub_53F6A0(this);
  if ( operator new(0x8Cu) != nullptr )
    pObj = sub_64CEF0(300, 3000, 1120403456, 10);
  else
    pObj = 0;
  return (*(int (/*thiscall*/ **)(int, void *, void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
           pObj,
           this,
           this,
           0,
           0,
           0,
           -1);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B36E0 sub_5B36E0
// ------------------------------------------------------------
// attributes: thunk
int sub_5B36E0()
{
  return sub_6098E0();  // 【CNRDJoint__vmt14C】
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B36F0 sub_5B36F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B36F0(uint32_t *this)
{
  int result; // eax

  switch ( *(this + 252) )
  {
    case 0:
    case 1:
    case 5:
    case 6:
      result = 15;
      break;
    case 2:
      result = 13;
      break;
    case 3:
      result = 10;
      break;
    case 4:
      result = 5;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}



// 时钟门+插值 AI（sub_699000+sub_4049C0）
// ------------------------------------------------------------
// 0x5B3740 sub_5B3740
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3740(uint32_t *this)
{
  unsigned int fld_e248; // edi
  uint64_t v3; // rax

  if ( *((uint8_t *)this + 264) != 1 )
  {
    fld_e248 = sub_699000((int)(this + 2)) - *(this + 248);  // 【clock_now(clk)】
    if ( *(this + 30) != 0 )
    {
      v3 = (uint64_t)sub_4049C0(255.0, 0.0, fld_e248, 600);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 252))(this, 3, v3);
    }
    if ( fld_e248 >= 0x258 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    }
  }
}



// AI 相位辅助（81L）
// ------------------------------------------------------------
// 0x5B37C0 sub_5B37C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B37C0(uint32_t *this)
{
  int result; // eax
  int16_t v3; // ax
  int v4; // edx
  int16_t v5; // ax
  int v6; // edx
  int v7; // edi
  int v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // edx
  int16_t v12; // di
  int fld_e2151; // [esp-34h] [ebp-50h]
  uint16_t v14[2]; // [esp+4h] [ebp-18h] BYREF
  int16_t v15; // [esp+8h] [ebp-14h]
  int16_t v16; // [esp+Ah] [ebp-12h]
  int v17; // [esp+Ch] [ebp-10h]
  int16_t v18; // [esp+10h] [ebp-Ch]
  float v19; // [esp+14h] [ebp-8h]
  int v20; // [esp+18h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v14[0] = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
    v4 = *this;
    v14[1] = v3;
    v15 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 48))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
    v6 = *this;
    v16 = v5;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v6 + 672))(this, 3);
    v20 = sub_41A5E0(v7 + 816);
    v19 = COERCE_FLOAT(sub_41A5E0(v7 + 830));
    v17 = (uint64_t)((double)v20 * v19);
    result = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 384))(
               this,
               (uint64_t)((double)v20 * v19) >> 32,
               0);
    v8 = 0;
    v19 = *(float *)&result;
    if ( result > 0 )
    {
      do
      {
        v9 = v8 + 1;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8 + 1);
        v11 = *this;
        fld_e2151 = *(this + 2151);
        v18 = v8;
        v12 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, uint16_t *))(v11 + 580))(
                this,
                fld_e2151,
                v10,
                0,
                0,
                0,
                0,
                0,
                4,
                0,
                14,
                v14);
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
        result = LODWORD(v19);
        v16 = v12;
        v8 = v9;
      }
      while ( v9 < SLODWORD(v19) );
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B38C0 sub_5B38C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B38C0(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int *v4; // ecx
  int v5; // ecx
  unsigned int v6; // edi
  int v7; // edx
  unsigned int v8; // edi
  int v9; // edx
  int v11; // [esp+8h] [ebp-4h]
  int v12; // [esp+8h] [ebp-4h]

  sub_4D9600();
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this) % 2;
  (*(void (/*thiscall*/ **)(uint32_t *, bool))(v2 + 148))(this, v3 == 0);
  v4 = nullptr;
  switch ( *(uint32_t *)(dword_8F7A24 + 12) )
  {
    case 3:
      v4 = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);
      break;
    case 4:
      v4 = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);
      break;
    case 6:
      v4 = *(int **)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);
      break;
    default:
      break;
  }
  v5 = *v4;
  if ( v5 >= 15 && v5 <= 16 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v6)) + 0.2;
    sub_41A590(v6, v7, v11);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v8)) + 0.2;
    sub_41A590(v8, v9, v12);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return sub_5B37C0(this);
}



// 虫弹连射：SFISH_BUG_SPIT 蓄力 + SFISH_BUG_FIRE 发射（91L；this+8612 相位）
// ------------------------------------------------------------
// 0x5B39C0 sub_5B39C0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5B39C0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  unsigned int result; // eax
  unsigned int i; // edi
  int fld_e1769; // ecx
  unsigned int j; // edi
  int fld_e17692; // ecx

  if ( ArgList == 14 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 1144))(
             this,
             **(uint32_t **)(LODWORD(fArg3) + 4),
             *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4));
  if ( ArgList == 8 )
  {
    result = *(uint32_t *)(LODWORD(fArg3) + 4);
    if ( *(uint32_t *)result == 1 || *(uint32_t *)result == 2 )
    {
      if ( dword_9B9414 >= 20 )
        return result;
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( *(this + 2152) + 3000 >= result )
        return result;
      *((uint8_t *)this + 8612) = 0;
    }
  }
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 5 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 45931);
    for ( i = 0; ; ++i )
    {
      fld_e1769 = *(this + 1769);
      if ( fld_e1769 == 0 )
        break;
      result = (*(this + 1770) - fld_e1769) >> 2;
      if ( i >= result )
        break;
      result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(fld_e1769 + 4 * i) + 712))(*(uint32_t *)(fld_e1769 + 4 * i), 2);
    }
  }
  else if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result != 0 )
    {
      if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "SFISH_BUG_SPIT",
                 -1,
                 0,
                 0);
      }
      else
      {
        result = sub_41A5E0((unsigned int)(this + 1757));
        if ( result == 2 )
          return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                   this,
                   "SFISH_BUG_FIRE",
                   -1,
                   0,
                   0);
      }
    }
    else
    {
      for ( j = 0; ; ++j )
      {
        fld_e17692 = *(this + 1769);
        if ( fld_e17692 == 0 )
          break;
        result = (*(this + 1770) - fld_e17692) >> 2;
        if ( j >= result )
          break;
        result = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(fld_e17692 + 4 * j) + 712))(*(uint32_t *)(fld_e17692 + 4 * j), 1);
      }
      if ( *(this + 1787) == 25 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3B50 sub_5B3B50
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3B50(uint32_t *this, int nArg2)
{
  int result; // eax
  int *v4; // ecx

  result = sub_4DBA80(nArg2);
  if ( *(this + 1787) == 25 )
  {
    *(uint32_t *)(*(this + 1905) + 12) = 1120403456;
    v4 = (int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this) + 40);
    result = *v4 / 2;
    *v4 = result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3B90 sub_5B3B90
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3B90(uint32_t *this, int nArg2)
{
  int v2; // eax

  if ( *(this + 1787) == 25 )
  {
    *(uint32_t *)(*(this + 1905) + 12) = 0;
    v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this);
    *(uint32_t *)(v2 + 40) *= 2;
  }
  return sub_4DBC20(nArg2);
}



// 增益拾取：BUFF_TAKE 播报（114L）
// ------------------------------------------------------------
// 0x5B3BD0 sub_5B3BD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3BD0(uint32_t *this, uint32_t *pArg2, int nArg3, int nArg4)
{
  uint32_t *pArg22; // esi
  int v5; // edi
  int v6; // eax
  unsigned int v7; // esi
  int v8; // ebx
  int v9; // ecx
  int pObj; // ecx
  int v11; // ecx
  int pObj2; // ecx
  uint32_t *v13; // eax
  const char *v14; // eax
  int *v15; // eax
  int v16; // edx
  float v18; // [esp+Ch] [ebp-130h]
  uint32_t *v19; // [esp+10h] [ebp-12Ch]
  int Block; // [esp+24h] [ebp-118h]
  void *Blocka; // [esp+24h] [ebp-118h]
  int v23; // [esp+28h] [ebp-114h]
  int v24; // [esp+28h] [ebp-114h]
  char Buffer[256]; // [esp+2Ch] [ebp-110h] BYREF
  int dword_796E502; // [esp+12Ch] [ebp-10h]
  int v27; // [esp+138h] [ebp-4h]

  pArg22 = pArg2;
  dword_796E502 = dword_796E50;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 700))(pArg2);
    v6 = *(uint32_t *)(v5 + 4);
    v7 = 0;
    if ( v6 != 0 )
      Block = (*(uint32_t *)(v5 + 8) - v6) >> 2;
    else
      Block = 0;
    v8 = 0;
    v23 = 0;
    if ( Block > 0 )
    {
      do
      {
        v9 = *(uint32_t *)(v5 + 4);
        if ( v9 != 0 && v7 < (*(uint32_t *)(v5 + 8) - v9) >> 2 )
          pObj = *(uint32_t *)(v9 + 4 * v7);
        else
          pObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 92))(pObj) != 0 )
        {
          v11 = *(uint32_t *)(v5 + 4);
          if ( v11 != 0 && v7 < (*(uint32_t *)(v5 + 8) - v11) >> 2 )
            pObj2 = *(uint32_t *)(v11 + 4 * v7);
          else
            pObj2 = 0;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);
          if ( ++v8 >= *(this + 2154) )
            break;
        }
        ++v7;
      }
      while ( (int)v7 < Block );
      v23 = v8;
      if ( v8 > 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg2 + 956))(pArg2);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 273) != 0 )
        {
          if ( pArg2[78] < 0x10u )
            v13 = pArg2 + 73;
          else
            v13 = (uint32_t *)pArg2[73];
          v19 = v13;
          v14 = (const char *)sub_422E70(880);
          sprintf(Buffer, v14, v19);
          sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -13487396, 0, -1);
        }
      }
    }
    v24 = (uint64_t)((double)v23 * *(float *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this));
    if ( v24 > 0 )
    {
      Blocka = operator new(0x80u);
      v27 = 0;
      if ( Blocka != nullptr )
      {
        v18 = (float)v24;
        v15 = (int *)sub_4D6810(LODWORD(v18), 1000, 1, 1);
      }
      else
      {
        v15 = nullptr;
      }
      v16 = *v15;
      v27 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v16 + 56))(
        v15,
        this,
        this,
        0,
        0,
        0,
        -1);
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BUFF_TAKE", -1, 0, 0);
    }
    pArg22 = pArg2;
  }
  return sub_4DB480(pArg22, nArg3, nArg4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B3E00 sub_5B3E00
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3E00(unsigned int *this)
{
  unsigned int fld_e252; // eax
  int result; // eax

  fld_e252 = *(this + 252);
  if ( fld_e252 <= 6 )
    (*(void (/*thiscall*/ **)(unsigned int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4 * fld_e252));
  result = 3 * (*(int (/*thiscall*/ **)(unsigned int *))(*this + 708))(this);
  *(this + 251) = result;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B3E40 sub_5B3E40
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3E40(int *this, int nArg2)
{
  int result; // eax
  uint32_t *fld_e36; // eax

  result = *(this + 243);
  if ( result != nArg2 )
  {
    result = sub_609720(nArg2);  // 【CNRDJoint__vmt2C8】
    if ( nArg2 == 1 )
    {
      if ( *(this + 252) == 5 )
      {
        sub_4926A0(*(uint32_t *)(*(this + 36) + 28));
        fld_e36 = (uint32_t *)(*(this + 36) + 28);
      }
      else
      {
        if ( *(this + 252) != 6 )
          return (*(int (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);
        sub_4926A0(*(uint32_t *)(*(this + 36) + 32));
        fld_e36 = (uint32_t *)(*(this + 36) + 32);
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *fld_e36);
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 596))(this, 1);
    }
    if ( nArg2 == 2 )
      return (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 260))(this, 1, 5, -1);
  }
  return result;
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x5B3EF0 sub_5B3EF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3EF0(uint32_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  if ( *(uint8_t *)(result + 170) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4 * *(this + 252)));
  return result;
}



// 宇宙鱼语音装载：SFISH_FIND/BITE/DMG/DIE 四件套（sub_4015C0+sub_699000）
// ------------------------------------------------------------
// 0x5B3F30 sub_5B3F30
// ------------------------------------------------------------
int /*thiscall*/ sub_5B3F30(uint32_t *this)
{
  int result; // eax

  sub_4015C0("SFISH_FIND", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SFISH_BITE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SFISH_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("SFISH_DIE", 9u);  // 【std::string构造赋值】
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2152) = result;
  return result;
}



// AI 相位辅助（69L）
// ------------------------------------------------------------
// 0x5B3F90 sub_5B3F90
// ------------------------------------------------------------
void /*thiscall*/ sub_5B3F90(uint32_t *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int *v10; // esi
  int v11; // edx
  uint8_t v12[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  void *Src; // [esp+14h] [ebp-1Ch]
  int v15; // [esp+18h] [ebp-18h]
  uint32_t *pThis; // [esp+1Ch] [ebp-14h]
  int v17[4]; // [esp+20h] [ebp-10h] BYREF

  pThis = this;
  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj = *(uint32_t *)(v6 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 545) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        v10 = *(int **)(v9 + 4 * i);
      else
        v10 = nullptr;
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int *))(*this + 1244))(this, v10) != 0
        && *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v10 + 340))(v10) == 258 )
      {
        if ( v10 != nullptr )
        {
          Block = nullptr;
          Src = nullptr;
          v15 = 0;
          v11 = *v10;
          v17[3] = 0;
          v17[0] = (*(int (/*thiscall*/ **)(int *))(v11 + 120))(v10);
          sub_430C80(nullptr, 1, (int)v17);
          v17[0] = (*(int (/*thiscall*/ **)(int *))(*v10 + 124))(v10);
          sub_430C80(nullptr, 1, (int)v17);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*pThis + 560))(pThis, 14, v12, 0, 0);
          if ( Block != nullptr )
            j__free(Block);
        }
        return;
      }
    }
  }
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5B4120 sub_5B4120
// ------------------------------------------------------------
int /*thiscall*/ sub_5B4120(void *this)
{
  uint8_t v3[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v5; // [esp+Ch] [ebp-18h]
  int v6; // [esp+10h] [ebp-14h]
  int v7; // [esp+14h] [ebp-10h] BYREF
  int v8; // [esp+20h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0 )
  {
    Block = nullptr;
    v5 = 0;
    v6 = 0;
    v8 = 0;
    v7 = 0;
    sub_431230((int)v3, &v7);
    (*(void (/*thiscall*/ **)(void *, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 8, v3, 0, 0);
    v8 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v5 = 0;
    v6 = 0;
  }
  return sub_4D9F40(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B41C0 sub_5B41C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5B41C0(uint32_t *this)
{
  float v2; // [esp+4h] [ebp-8h]

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_4;
      if ( rand() % 100 < 2 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        if ( rand() % 100 < 2 )
          goto LABEL_11;
      }
      else
      {
LABEL_4:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      }
      break;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )
LABEL_11:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      break;
    default:
      break;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v2 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
    if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * 0.5 > v2 && *(this + 1787) != 25 )
      sub_5B3F90(this);
  }
}



// 破坏特效：PassiveObject/Monster/SpaceFish/Particle/CrokutaDestroyHead.ptl（头部击破, 53L）
// ------------------------------------------------------------
// 0x5B42F0 sub_5B42F0
// ------------------------------------------------------------
void /*thiscall*/ sub_5B42F0(uint32_t *this)
{
  uint32_t *pMem; // eax
  uint32_t *v3; // esi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int nRand; // ebx
  void *fld_e29; // ecx
  uint8_t v11[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *pMem2; // [esp+1Ch] [ebp-10h]
  int v14; // [esp+28h] [ebp-4h]

  pMem = operator new(0x12Cu);
  pMem2 = pMem;
  v14 = 0;
  if ( pMem != nullptr )
    v3 = sub_428F30(pMem, (int)"PassiveObject/Monster/SpaceFish/Particle/CrokutaDestroyHead.ptl", (int)this);
  else
    v3 = nullptr;
  v4 = *v3;
  v14 = -1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 12))(v3, 0);
  v5 = *v3;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v6);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v7);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v5 + 40))(v3, v8);
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3) + 15) = 800;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3) + 19) = 500;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3) + 23) = 800;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3) + 27) = 500;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3) + 31) = 800;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3) + 35) = 500;
  nRand = rand() % 360;
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3) + 76) = nRand;
  (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *))(*v3 + 92))(v3, v11);
  fld_e29 = (void *)*(this + 29);
  v14 = 1;
  sub_4600B0(fld_e29, 2, 0, (int)v11);
  (*(void (/*thiscall*/ **)(uint32_t *, int))*v3)(v3, 1);
  if ( Block != nullptr )
    j__free(Block);
}



// 分段破坏系统：JOINT1-5 + TAIL 部位播报 + Particle/CrokutaDestroy%s.ptl 按部位加载
//   （91L；克罗库塔节段破坏 = 部位破坏玩法的客户端实现）
// ------------------------------------------------------------
// 0x5B4430 sub_5B4430
// ------------------------------------------------------------
void /*thiscall*/ sub_5B4430(uint32_t *this)
{
  unsigned int fld_e248; // esi
  uint64_t v3; // rax
  int fld_e252; // eax
  int *pThis_5B; // esi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int nRand; // ebx
  void *fld_e29; // ecx
  void *pMem; // [esp+4h] [ebp-230h]
  uint32_t v14[3]; // [esp+8h] [ebp-22Ch]
  const char *v15; // [esp+14h] [ebp-220h] BYREF
  void *Block; // [esp+18h] [ebp-21Ch]
  char (**v17)[10]; // [esp+1Ch] [ebp-218h]
  const char *v18; // [esp+20h] [ebp-214h]
  char Buffer[512]; // [esp+24h] [ebp-210h] BYREF
  int dword_796E502; // [esp+224h] [ebp-10h]
  int v21; // [esp+230h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *((uint8_t *)this + 264) != 1 )
  {
    fld_e248 = sub_699000((int)(this + 2)) - *(this + 248);  // 【clock_now(clk)】
    if ( *(this + 30) != 0 )
    {
      v3 = (uint64_t)sub_4049C0(255.0, 80.0, fld_e248, 500);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 252))(this, 3, v3);
    }
    if ( fld_e248 >= 0x1F4 )
    {
      fld_e252 = *(this + 252);
      v14[0] = "JOINT1";
      v14[1] = "JOINT2";
      v14[2] = "JOINT3";
      v15 = "JOINT4";
      Block = "JOINT5";
      v17 = &off_72F738;
      v18 = "TAIL";
      sprintf(Buffer, "Particle/CrokutaDestroy%s.ptl", (const char *)v14[fld_e252]);
      pMem = operator new(0x12Cu);
      v21 = 0;
      if ( pMem != nullptr )
      {
        if ( *(this + 96) < 0x10u )
          pThis_5B = (int *)sub_4C3640(this + 91, Buffer, this);
        else
          pThis_5B = (int *)sub_4C3640(*(this + 91), Buffer, this);
      }
      else
      {
        pThis_5B = nullptr;
      }
      v6 = *pThis_5B;
      v21 = -1;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(v6 + 12))(pThis_5B, 0);
      v7 = *pThis_5B;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v8);
      v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v9);
      (*(void (/*thiscall*/ **)(int *, int))(v7 + 40))(pThis_5B, v10);
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pThis_5B + 28))(pThis_5B) + 15) = 800;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pThis_5B + 28))(pThis_5B) + 19) = 500;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pThis_5B + 28))(pThis_5B) + 23) = 800;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pThis_5B + 28))(pThis_5B) + 27) = 500;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pThis_5B + 28))(pThis_5B) + 31) = 800;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pThis_5B + 28))(pThis_5B) + 35) = 500;
      nRand = rand() % 360;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pThis_5B + 28))(pThis_5B) + 76) = nRand;
      (*(void (/*thiscall*/ **)(int *, const char **))(*pThis_5B + 92))(pThis_5B, &v15);
      fld_e29 = (void *)*(this + 29);
      v21 = 1;
      sub_4600B0(fld_e29, 2, 0, (int)&v15);
      (*(void (/*thiscall*/ **)(int *, int))*pThis_5B)(pThis_5B, 1);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B46A0 sub_5B46A0
// ------------------------------------------------------------
bool /*cdecl*/ sub_5B46A0(int nArg1)
{
  return *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 250
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 251
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 252
      || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 340))(nArg1) == 253;
}



// 子类扩展字段复位（this+8604..8652, 26L）
// ------------------------------------------------------------
// 0x5B4700 sub_5B4700
// ------------------------------------------------------------
int /*thiscall*/ sub_5B4700(int this)
{
  *(uint32_t *)(this + 6792) = 0;
  *(uint32_t *)(this + 6796) = 0;
  *(uint32_t *)(this + 6800) = 0;
  *(uint32_t *)(this + 6804) = 0;
  *(uint32_t *)(this + 6808) = 0;
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8612) = 0;
  *(uint8_t *)(this + 8632) = 0;
  *(uint8_t *)(this + 8633) = 0;
  *(uint32_t *)(this + 8636) = 0xFFFF;
  *(uint32_t *)(this + 8640) = 0;
  *(uint32_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8652) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B4770 sub_5B4770
// ------------------------------------------------------------
int /*stdcall*/ sub_5B4770(int *pDwArg1, int nArg2)
{
  int v2; // esi

  v2 = sub_4DC390(pDwArg1, nArg2);
  if ( v2 == 3 || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128) != 0 )
    return v2;
  *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.69999999);
  return 0;
}



// ============================================================
// 【分区 4】ZGM 机动怪（高达梗：Rx78/Ez8 系粒子在 0x5C 区）（0x5B6380-0x5B8120）
// 证据：ZGM_ATK/ZGM_SPRING/ZGM_DIE、MOVING_ATTACK_LOOP、SHIELD_FLASH、
//       Particle/Dagger.ptl + THROW_STONE 投刀

// ZGM 攻击主循环（198L；usercall 三寄存器参）：ZGM_ATK 播报（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B6380 sub_5B6380
// ------------------------------------------------------------
void /*usercall*/ sub_5B6380(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  char v3; // al
  int v4; // edi
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  char v14; // al
  int v15; // edi
  int v16; // eax
  char v17; // al
  int v18; // edi
  int v19; // eax
  int v20; // edi
  char v21; // cl
  int v22; // edx
  uint32_t *v23; // edi
  uint32_t *v24; // edi

  sub_4E1780(pDwArg1);
  if ( pDwArg1[1639] != 8 )
  {
    if ( pDwArg1[1639] == 14 )
    {
      sub_5B5390(pDwArg1, nArg2, nArg3);
    }
    else if ( pDwArg1[1639] == 15 )
    {
      v14 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 308))(pDwArg1, nArg3);
      if ( v14 != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(
          pDwArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);
      }
      if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
      {
        v15 = pDwArg1[30];
        v16 = sub_491C70(v15, 1);
        sub_493A60(v15, v16);
        *((uint8_t *)pDwArg1 + 8605) = 1;
      }
      if ( *(uint8_t *)(pDwArg1[30] + 170) != 0 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);
    }
    return;
  }
  if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 0
    && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 2
    && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 6 )
  {
    if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 1 && sub_41A5E0((unsigned int)(pDwArg1 + 1757)) != 4 )
    {
      if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) < 30 )
        {
          v10 = *pDwArg1;
          v11 = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 124))(pDwArg1, 30, nArg3);
          v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
          (*(void (/*thiscall*/ **)(int *, int))(v10 + 112))(pDwArg1, v12);
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
        {
          v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 844))(pDwArg1);
          if ( sub_699000(v13) > 1000 )  // 【clock_now(clk)】
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);
        }
      }
      return;
    }
    v17 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
    if ( v17 == 0 )
      goto LABEL_60;
    if ( *(int *)(pDwArg1[30] + 148) >= 1 )
    {
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
        goto LABEL_57;
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 80, 80, 0, 0, 0);
      v18 = *pDwArg1;
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
      (*(void (/*thiscall*/ **)(int *, int))(v18 + 896))(pDwArg1, v19);
      v20 = 150;
      if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 4 )
        v20 = 300;
      sub_4A0550(v20);
    }
    if ( *((uint8_t *)pDwArg1 + 8604) == 0 )
    {
LABEL_60:
      v21 = *((uint8_t *)pDwArg1 + 8604);
      if ( v21 != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
        *((uint8_t *)pDwArg1 + 8605) = 1;
      v22 = pDwArg1[28];
      if ( *(float *)(v22 + 24) > 0.0 && v21 == 0 )
        *((uint8_t *)pDwArg1 + 8604) = 1;
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
      {
        if ( *(float *)(v22 + 24) > 0.0 && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) > 130 )
        {
          v23 = (uint32_t *)(pDwArg1[1554] + 8);
          if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) != *v23 )
          {
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_ATK", -1, 0, 0);
            (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 344))(pDwArg1, pDwArg1[139] + 152);
            sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 8));
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 8));
          }
        }
        if ( *((uint8_t *)pDwArg1 + 8604) != 0
          && *(float *)(pDwArg1[28] + 24) < 0.0
          && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) < 15 )
        {
          v24 = (uint32_t *)(pDwArg1[1554] + 12);
          if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) != *v24 )
          {
            sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 12));
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 12));
          }
        }
      }
      return;
    }
LABEL_57:
    if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);
    }
    goto LABEL_60;
  }
  v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
  if ( v3 == 0 )
    goto LABEL_24;
  if ( *(int *)(pDwArg1[30] + 148) >= 1 )
  {
    if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
    {
LABEL_21:
      if ( *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(
          pDwArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 896))(pDwArg1, 4, 4);
      }
LABEL_24:
      if ( *((uint8_t *)pDwArg1 + 8604) != 0 && *(uint32_t *)(pDwArg1[28] + 192) == 4 && *((uint8_t *)pDwArg1 + 8605) == 0 )
      {
        v6 = pDwArg1[30];
        v7 = sub_491C70(v6, 15);
        sub_493A60(v6, v7);
        *((uint8_t *)pDwArg1 + 8605) = 1;
      }
      goto LABEL_28;
    }
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 0, 200, 200, 0, 0, 0);
    v4 = *pDwArg1;
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
    (*(void (/*thiscall*/ **)(int *, int))(v4 + 896))(pDwArg1, v5);
    sub_4A0550(120);
  }
  if ( *((uint8_t *)pDwArg1 + 8604) != 0 )
    goto LABEL_21;
LABEL_28:
  if ( *(float *)(pDwArg1[28] + 24) > 0.0 && *((uint8_t *)pDwArg1 + 8604) == 0 )
  {
    v8 = pDwArg1[30];
    if ( *(int *)(v8 + 148) < 1 )
    {
      v9 = sub_491C70(v8, 1);
      sub_493A60(v8, v9);
    }
    *((uint8_t *)pDwArg1 + 8604) = 1;
  }
}


// 移动攻击：MOVING_ATTACK_LOOP 播报（83L）
// ------------------------------------------------------------
// 0x5B6420 sub_5B6420
// ------------------------------------------------------------
int /*usercall*/ sub_5B6420@<eax>(int pArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // edi
  int result; // eax
  int v9; // [esp+8h] [ebp-4h]

  sub_5B6380((int *)pArg1, nArg2);
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);
  if ( v3 == 8 )
  {
    if ( sub_41A5E0(pArg1 + 7028) == 5 )
    {
      v4 = *(uint32_t *)pArg1;
      v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, 30);
      v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 120))(pArg1, v5);
      (*(void (/*thiscall*/ **)(int, int))(v4 + 112))(pArg1, v6);
      v7 = (uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) == *v7 )
      {
        if ( sub_699000(pArg1 + 6560) < 10000 )  // 【clock_now(clk)】
        {
          v9 = *(uint32_t *)(pArg1 + 8684);
          if ( sub_699000(pArg1 + 8660) >= v9 )  // 【clock_now(clk)】
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )
              sub_5B51D0(pArg1);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);
            *(uint8_t *)(pArg1 + 8673) = 0;
            *(uint8_t *)(pArg1 + 8674) = 0;
            sub_698F90(pArg1 + 8660, 1428, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
          }
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && *(uint32_t *)(pArg1 + 616) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
        }
      }
      else if ( sub_699000(pArg1 + 6560) >= 2000 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 16));
        sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20));
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20));
        *(uint8_t *)(pArg1 + 6573) = 0;
        *(uint8_t *)(pArg1 + 6574) = 0;
        sub_698F90(pArg1 + 6560, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        *(uint8_t *)(pArg1 + 8673) = 0;
        *(uint8_t *)(pArg1 + 8674) = 0;
        sub_698F90(pArg1 + 8660, 1428, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        sub_5B51D0(pArg1);
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "MOVING_ATTACK_LOOP",
          9,
          0,
          0);
        *(uint8_t *)(pArg1 + 8652) = 1;
      }
    }
  }
  else if ( v3 == 16
         && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0
         && (*(uint8_t (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pArg1 + 1248))(pArg1, 2, *(uint32_t *)(pArg1 + 7252)) == 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);
  if ( result != 8 && *(uint8_t *)(pArg1 + 8652) == 1 )
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 9);
    *(uint8_t *)(pArg1 + 8652) = 0;
  }
  return result;
}



// ZGM 死亡：ZGM_DIE 播报（sub_4015C0+sub_4049C0）
// ------------------------------------------------------------
// 0x5B6630 sub_5B6630
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5B6630(uint32_t *this)
{
  int fld_e1821; // edi
  uint32_t *v3; // eax
  uint64_t result; // rax
  float v5; // [esp+Ch] [ebp-20h]
  float v6; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+24h] [ebp-8h]
  int v8; // [esp+28h] [ebp-4h]

  sub_4015C0("ZGM_DIE", 7u);  // 【std::string构造赋值】
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v6 = (float)v8;
  v5 = (float)v7;
  result = (uint64_t)sub_4049C0(v5, v6, *v3 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2155) = result;
  return result;
}



// 参数打包 AI（sub_431230+RTTI cast）
// ------------------------------------------------------------
// 0x5B66C0 sub_5B66C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5B66C0(uint32_t *this, int nArg2)
{
  int nArg22; // edi
  int pObj; // edi
  uint8_t v5[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  nArg22 = nArg2;
  if ( __RTDynamicCast(nArg2, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0) != 0 )
  {
    pObj = __RTDynamicCast(nArg22, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj) == *(this + 2159)
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      Block = nullptr;
      v7 = 0;
      v8 = 0;
      v9 = 0;
      sub_431230((int)v5, this + 2159);
      nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);
      sub_431230((int)v5, &nArg2);
      nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
      sub_431230((int)v5, &nArg2);
      nArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
      sub_431230((int)v5, &nArg2);
      nArg2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
      sub_431230((int)v5, &nArg2);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 17, v5, 2, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// 参数打包 AI（sub_431230+RTTI cast, 73L）
// ------------------------------------------------------------
// 0x5B67F0 sub_5B67F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B67F0(uint32_t *this, int *Block, int nArg3, int nArg4)
{
  int *Block2; // edi
  int v6; // edx
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int *v10; // eax
  int v11; // edx
  float v13; // [esp+18h] [ebp-38h]
  void *pBuf[4]; // [esp+34h] [ebp-1Ch] BYREF
  int v15; // [esp+4Ch] [ebp-4h]

  Block2 = Block;
  if ( *(this + 1639) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 0
     || sub_41A5E0((unsigned int)(this + 1757)) == 2
     || sub_41A5E0((unsigned int)(this + 1757)) == 6)
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *, int))(*Block2 + 40))(Block2, 17) != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*Block2 + 948))(Block2) != 0 && *(this + 154) != 14 )
    {
      memset(&pBuf[1], 0, 12);
      v6 = *Block2;
      v15 = 0;
      Block = (int *)(*(int (/*thiscall*/ **)(int *))(v6 + 48))(Block2);
      sub_431230((int)pBuf, &Block);
      Block = (int *)(*(int (/*thiscall*/ **)(int *))(*Block2 + 52))(Block2);
      sub_431230((int)pBuf, &Block);
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);
      v15 = -1;
      sub_5E5260(pBuf);
    }
    v7 = *Block2;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v9 = sub_432E50(v8);
    (*(void (/*thiscall*/ **)(int *, int))(v7 + 144))(Block2, v9);
  }
  if ( __RTDynamicCast((int)this, 0, &CNStarFish `RTTI Type Descriptor', &CNStarFishDevourer `RTTI Type Descriptor', 0) != 0
    && sub_41A5E0((unsigned int)(this + 1757)) == 0 )
  {
    Block = (int *)operator new(0x80u);
    v15 = 1;
    if ( Block != nullptr )
    {
      v13 = *(float *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this) * 0.89999998;
      v10 = (int *)sub_4D6810(LODWORD(v13), 500, 1, 1);
    }
    else
    {
      v10 = nullptr;
    }
    v11 = *v10;
    v15 = -1;
    (*(void (/*thiscall*/ **)(int *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v11 + 56))(
      v10,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  return sub_4DB480(Block2, nArg3, nArg4);
}



// 参数打包 AI（95L sub_431230）
// ------------------------------------------------------------
// 0x5B69C0 sub_5B69C0
// ------------------------------------------------------------
void /*usercall*/ sub_5B69C0(int *pDwArg1@<ecx>, int nArg2@<ebx>)
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
           pDwArg1[2160],
           pDwArg1[2161],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2152] + 112))(pDwArg1[2152], pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);
    }
    else
    {
      pObj = pDwArg1[2152];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2160, pDwArg1 + 2161, v7);
      pObj2 = pDwArg1[2152];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2162]);
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
    if ( pDwArg1[2153] < pDwArg1[2155]
      && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[2152] + 772))(pDwArg1[2152], 5) != 0
      && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int *, int))(*(uint32_t *)pDwArg1[2152] + 764))(pDwArg1[2152], 5, 0, pDwArg1, 1);
    }
    pDwArg1[2152] = 0;
  }
}



// 参数打包 AI（this+8632 相位）
// ------------------------------------------------------------
// 0x5B6C00 sub_5B6C00
// ------------------------------------------------------------
void /*thiscall*/ sub_5B6C00(uint32_t *this)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // edi
  int v5; // edx
  void *pBuf[4]; // [esp+4h] [ebp-24h] BYREF
  float v7; // [esp+14h] [ebp-14h] BYREF
  int v8; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 2164) == 0
    && *((uint8_t *)this + 8632) == 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
    v2 = *this;
    v7 = (float)v8;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v2 + 740))(this);
    if ( (double)v8 * 0.30000001 >= v7 )
    {
      v3 = (uint32_t *)sub_5B6080(this);
      v4 = v3;
      if ( v3 != nullptr )
      {
        memset(&pBuf[1], 0, 12);
        v5 = *v3;
        v9 = 0;
        v7 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v5 + 48))(v3));
        sub_431230((int)pBuf, &v7);
        v7 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 52))(v4));
        sub_431230((int)pBuf, &v7);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 16, pBuf, 0, 0);
        sub_5E5260(pBuf);
      }
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B6CF0 sub_5B6CF0
// ------------------------------------------------------------
void /*thiscall*/ sub_5B6CF0(uint32_t *this, int nArg2)
{
  int v3; // ebx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);
    if ( v3 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      sub_5B46A0(nArg2);
  }
  if ( (uint32_t *)nArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
    *(this + 2164) = 8;
  }
  sub_5B66C0(this, nArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B6D70 sub_5B6D70
// ------------------------------------------------------------
int /*userpurge*/ sub_5B6D70@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
    sub_5B69C0(pDwArg1, nArg2);
  if ( pDwArg3 == pDwArg1 && pDwArg1[2152] != 0 )
    sub_5B69C0(pDwArg1, nArg2);
  return sub_4D9170(pDwArg3);
}



// 弹射技能：ZGM_SPRING 播报（118L；RTTI cast 目标解算 —— 弹簧顶飞演出）
// ------------------------------------------------------------
// 0x5B6DC0 sub_5B6DC0
// ------------------------------------------------------------
int /*userpurge*/ sub_5B6DC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int *v7; // eax
  int v8; // ebx
  int v9; // eax
  int *v10; // edi
  int v11; // eax
  int result; // eax
  int v13; // esi
  int v14; // eax
  int pObj; // ecx
  int v16; // edi
  int v17; // eax
  int v18; // [esp-18h] [ebp-24h]
  int v19; // [esp-14h] [ebp-20h]
  float v20; // [esp+0h] [ebp-Ch]
  int ArgLista; // [esp+14h] [ebp+8h]
  int v22; // [esp+18h] [ebp+Ch]

  if ( ArgList == 17 )
  {
    v7 = *(int **)(LODWORD(fArg4) + 4);
    v8 = v7[3];
    ArgLista = *v7;
    v19 = v7[2];
    v18 = v7[1];
    v22 = v7[4];
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
    v9 = sub_45EBE0(v18, v19);
    v10 = (int *)__RTDynamicCast(v9, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);
    v11 = sub_45EBE0(v8, v22);
    result = __RTDynamicCast(v11, 0, &CNRDObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0);
    if ( v10 != nullptr && result != 0 )
    {
      v13 = *v10;
      v10[2159] = ArgLista;
      v14 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)result + 736))(result, 0, 1);
      return (*(int (/*thiscall*/ **)(int *, int))(v13 + 732))(v10, v14);
    }
  }
  else
  {
    if ( pDwArg1[1639] == 14 )
    {
      if ( ArgList != 14 && (ArgList == 3 || ArgList == 5) )
      {
        pObj = pDwArg1[2152];
        if ( pObj != 0
          && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 772))(pObj, 5) != 0
          && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int *, int))(*(uint32_t *)pDwArg1[2152] + 764))(pDwArg1[2152], 5, 0, pDwArg1, 1);
        }
      }
      sub_5B69C0(pDwArg1, nArg2);
    }
    switch ( ArgList )
    {
      case 8:
        *((uint8_t *)pDwArg1 + 8604) = 0;
        *((uint8_t *)pDwArg1 + 8605) = 0;
        if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 4 )
        {
          (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1065353216);
          sub_4E99C0(v20);
          v20 = 0.0;
          (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 676))(pDwArg1);
        }
        break;
      case 14:
        sub_5B5B90(LODWORD(fArg4));
        break;
      case 15:
        sub_5B5DC0(pDwArg1);
        break;
      default:
        break;
    }
    result = sub_4E33D0(ArgList, fArg4, nArg5, nArg6);
    if ( ArgList == 11 )
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);
    if ( ArgList != 8 )
      return result;
    if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 0
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 6
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1
      || sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2 )
    {
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);
    }
    else if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 3 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 400, 400, 0, -200, 1);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
      v16 = *pDwArg1;
      v17 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
      return (*(int (/*thiscall*/ **)(int *, int))(v16 + 896))(pDwArg1, v17);
    }
    else
    {
      result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
      if ( result == 4 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 672))(pDwArg1, 0, 1065353216);
        sub_4AED60(v20);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 676))(pDwArg1, 0);
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "ZGM_SPRING", -1, 0, 0);
      }
    }
  }
  return result;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5B7080 sub_5B7080
// ------------------------------------------------------------
int /*userpurge*/ sub_5B7080@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2164] )
  {
    sub_5B5F90();
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 472))(pDwArg1, 0, 0, 1, 1);
  }
  if ( pDwArg3 == (int *)pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
    sub_5B69C0(pDwArg1, nArg2);
  if ( pDwArg3 == pDwArg1 && pDwArg1[2152] != 0 )
    sub_5B69C0(pDwArg1, nArg2);
  return sub_4D9170(pDwArg3);
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B70F0 sub_5B70F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B70F0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // [esp-18h] [ebp-24h]
  int v11; // [esp-14h] [ebp-20h]

  result = sub_5B6DC0(this, ArgList, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 16 )
  {
    v7 = *(int **)(LODWORD(fArg3) + 4);
    v11 = v7[1];
    v10 = *v7;
    (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);
    v8 = sub_45EBE0(v10, v11);
    v9 = __RTDynamicCast(v8, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
    *(this + 2164) = v9;
    if ( v9 != 0 )
      sub_5B6000(this);
    return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7170 sub_5B7170
// ------------------------------------------------------------
void /*thiscall*/ sub_5B7170(uint32_t *this)
{
  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 4:
      if ( *(this + 1813) != 0 )
        goto LABEL_6;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      sub_5B6C00(this);
      break;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      goto LABEL_6;
    default:
LABEL_6:
      sub_5B6C00(this);
      break;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B71F0 sub_5B71F0
// ------------------------------------------------------------
int /*userpurge*/ sub_5B71F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3)
{
  int v4; // ebx
  bool v5; // zf
  int nArg22; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 724))(pDwArg1) == 0 )
  {
    nArg22 = nArg2;
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 376))(nArg3);
    v5 = v4 == (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 376))(pDwArg1);
    nArg2 = nArg22;
    if ( v5 )
      sub_5B46A0(nArg3);
  }
  if ( nArg3 == pDwArg1[2152] && (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
    sub_5B69C0(pDwArg1, nArg2);
  if ( (int *)nArg3 == pDwArg1 && pDwArg1[2152] != 0 )
    sub_5B69C0(pDwArg1, nArg2);
  return sub_4D9170(nArg3);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7280 sub_5B7280
// ------------------------------------------------------------
int /*userpurge*/ sub_5B7280@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int result; // eax
  int nRand; // eax
  int v9; // et2

  if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 8 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 208))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 16));
  result = sub_5B6DC0(pDwArg1, nArg2, ArgList, fArg4, nArg5, nArg6);
  switch ( ArgList )
  {
    case 5:
      if ( pDwArg1[1943] != 3 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, 0);
        return sub_5B4A50(3, 2, -1, -1);
      }
      break;
    case 3:
      result = pDwArg1[2164];
      if ( result > 0 )
      {
        if ( pDwArg1[1908] == 2 && rand() % 100 < 1
          || (result = pDwArg1[1908]) == 0 && (nRand = rand(), v9 = nRand % 100, result = nRand / 100, v9 < 5) )
        {
          sub_5B4A50(1, 1, -1, -1);
          result = pDwArg1[2164] - 1;
          pDwArg1[2164] = result;
        }
      }
      break;
    case 8:
      result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
      if ( result == 5 )
      {
        sub_4926A0(*(uint32_t *)(pDwArg1[1554] + 16));
        return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 204))(
                 pDwArg1,
                 100,
                 *(uint32_t *)(pDwArg1[1554] + 16),
                 0,
                 0,
                 0,
                 0);
      }
      break;
    default:
      break;
  }
  return result;
}



// 子类扩展字段复位（this+8604..8660, 20L）
// ------------------------------------------------------------
// 0x5B73B0 sub_5B73B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B73B0(int this)
{
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 0;
  *(uint8_t *)(this + 8606) = 0;
  *(uint8_t *)(this + 8607) = 0;
  *(uint32_t *)(this + 8640) = -1;
  *(uint32_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8656) = -1;
  *(uint32_t *)(this + 8660) = -1;
  return 0;
}



// 【vmt200 命中处理器覆写】（39L；虚表 0x6E7334..0x6EA274 九张 +512 槽共享 —— ZGM/炮车族通用受击处理）
// ------------------------------------------------------------
// 0x5B7400 sub_5B7400
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7400(void *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi
  int pThis_877; // eax
  int v7; // eax
  unsigned int pThis_2A0; // edi
  int v9; // eax
  int v10; // edx
  int v12; // [esp+18h] [ebp+10h]

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);
  v12 = v5;
  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0
    && *((uint32_t *)this + 1909) == 2
    && rand() % 100 < *((uint32_t *)this + 2166) )
  {
    (**((void (/*thiscall*/ ***)(int, void *, uint32_t))this + 2150))((int)this + 8600, this, *((uint32_t *)this + 1814));
  }
  pThis_877 = *((uint32_t *)this + 2167);
  if ( pThis_877 <= 0 )
    return v5;
  v7 = pThis_877 - 1;
  *((uint32_t *)this + 2167) = v7;
  if ( v7 > 0 )
    return v5;
  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 466;
  v9 = sub_41A5E0(pThis_2A0);
  sub_41A590(pThis_2A0, v10, v9 - 100000);
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  *((uint8_t *)this + 8621) = 0;
  *((uint8_t *)this + 8622) = 0;
  return v12;
}



// AI 字段访问（this+8621/8622）
// ------------------------------------------------------------
// 0x5B74D0 sub_5B74D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B74D0(uint32_t *this)
{
  int result; // eax
  int v3; // edi

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*(this + 2150) + 4))(this + 2150, this);
    return v3;
  }
  return result;
}



// 盾闪：SHIELD_FLASH 播报（55L）
// ------------------------------------------------------------
// 0x5B7500 sub_5B7500
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7500(void *this, char pszArg2)
{
  unsigned int pThis_2A0; // edi
  int v4; // eax
  int v5; // edx
  unsigned int pThis_2A02; // edi
  int v7; // edx
  unsigned int pThis_2A03; // edi
  int v9; // edx
  unsigned int pThis_2A04; // edi
  int v12; // edx
  unsigned int pThis_2A05; // edi
  int v14; // edx
  int v15; // [esp+10h] [ebp+8h]
  int v16; // [esp+10h] [ebp+8h]
  int v17; // [esp+10h] [ebp+8h]
  int v18; // [esp+10h] [ebp+8h]

  pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 466;
  v4 = sub_41A5E0(pThis_2A0);
  if ( pszArg2 != 0 )
  {
    sub_41A590(pThis_2A0, v5, v4 + 100);
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;
    *(float *)&v15 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) + 9.0;
    sub_41A590(pThis_2A02, v7, v15);
    pThis_2A03 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(pThis_2A03)) + 9.0;
    sub_41A590(pThis_2A03, v9, v16);
    (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "SHIELD_FLASH",
             -1,
             0,
             0);
  }
  else
  {
    sub_41A590(pThis_2A0, v5, v4 - 100);
    pThis_2A04 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;
    *(float *)&v17 = COERCE_FLOAT(sub_41A5E0(pThis_2A04)) - 9.0;
    sub_41A590(pThis_2A04, v12, v17);
    pThis_2A05 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;
    *(float *)&v18 = COERCE_FLOAT(sub_41A5E0(pThis_2A05)) - 9.0;
    sub_41A590(pThis_2A05, v14, v18);
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B7660 sub_5B7660
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7660(uint32_t *this)
{
  int v2; // eax
  int pObj; // esi
  int v4; // edx
  unsigned int v5; // ebx
  int v6; // eax
  int v7; // edx
  int fld_e2164; // [esp-18h] [ebp-20h]
  int fld_e2165; // [esp-14h] [ebp-1Ch]

  fld_e2165 = *(this + 2165);
  fld_e2164 = *(this + 2164);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);
  v2 = sub_45EBE0(fld_e2164, fld_e2165);
  pObj = __RTDynamicCast(v2, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) == 0 )
  {
    v4 = *(uint32_t *)pObj;
    *(uint32_t *)(pObj + 8668) = 5;
    v5 = (*(int (/*thiscall*/ **)(int, uint32_t))(v4 + 672))(pObj, 0) + 466;
    v6 = sub_41A5E0(v5);
    sub_41A590(v5, v7, v6 + 100000);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 676))(pObj, 0);
    *(uint8_t *)(pObj + 8621) = 0;
    *(uint8_t *)(pObj + 8622) = 0;
    sub_698F90(pObj + 8608, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  *(this + 2164) = -1;
  *(this + 2165) = -1;
  return -1;
}



// 主状态门（this+200/8604）
// ------------------------------------------------------------
// 0x5B7720 sub_5B7720
// ------------------------------------------------------------
char /*thiscall*/ sub_5B7720(int this)
{
  int pThis_C8; // eax

  sub_4E1780((uint32_t *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8
    && (sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2) )
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
    if ( *(uint32_t *)(pThis_C8 + 148) == 1 )
    {
      LOBYTE(pThis_C8) = *(uint8_t *)(this + 8604);
      if ( (uint8_t)pThis_C8 == 0 )
      {
        LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
        if ( (uint8_t)pThis_C8 != 0 )
          LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1316))(this);
        *(uint8_t *)(this + 8604) = 1;
      }
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 15
         && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )
  {
    LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);
  }
  else
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( pThis_C8 == 14 )
      LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);
  }
  return pThis_C8;
}



// 时钟门 AI（sub_699000, 58L）
// ------------------------------------------------------------
// 0x5B77F0 sub_5B77F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B77F0(int *this)
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_12;
      nRand = rand();
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) == 0 )
        goto LABEL_12;
      nRand2 = rand();
      v4 = nRand2 % 100;
      result = nRand2 / 100;
      if ( v4 < 1 )
        goto LABEL_4;
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    case 25:
      result = sub_699000((int)(this + 1910)) - *(this + 1926);  // 【clock_now(clk)】
      if ( result > 5000 )
LABEL_12:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    default:
      return result;
  }
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5B7900 sub_5B7900
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7900(uint32_t *this, int nArg2)
{
  int result; // eax

  if ( *(this + 1787) != 25 )
    return sub_4D9040(nArg2);
  result = sub_699000((int)(this + 1910)) - *(this + 1926);  // 【clock_now(clk)】
  if ( result >= 5000 )
    return sub_4D9040(nArg2);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B7940 sub_5B7940
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7940(int *this, int nArg2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int result; // eax

  v3 = *this;
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
  v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v4);
  (*(void (/*thiscall*/ **)(int *, int))(v3 + 1144))(this, v5);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 1040))(this);
  *(uint8_t *)(result + 8) = 0;
  return result;
}



// 投刀技能：Particle/Dagger.ptl + THROW_STONE 播报（33L）
// ------------------------------------------------------------
// 0x5B7980 sub_5B7980
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7980(uint32_t *this)
{
  int pThis_6DD; // eax
  int v3; // edi
  int v4; // eax

  pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
  v3 = *this;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(
         this,
         "Particle/Dagger.ptl",
         0,
         40,
         0,
         pThis_6DD != 1 ? 20 : 50,
         4,
         0,
         0,
         0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(v3 + 580))(this, *(this + 2168), 0, v4);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "THROW_STONE",
           -1,
           0,
           0);
}



// AI 相位辅助（67L）
// ------------------------------------------------------------
// 0x5B79F0 sub_5B79F0
// ------------------------------------------------------------
int /*usercall*/ sub_5B79F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  int nRand; // edi
  int nRand4; // eax
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int nRand5; // eax
  int v12; // ebx
  int nRand6; // eax
  uint32_t v16[2]; // [esp+4h] [ebp-18h]
  uint16_t v17[3]; // [esp+Ch] [ebp-10h] BYREF
  bool nRand2; // [esp+12h] [ebp-Ah]
  char nRand3; // [esp+13h] [ebp-9h]
  uint32_t *v20; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand() % 2 + 2;
    result = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 672))(pDwArg1, 3);
    v16[0] = 250;
    v16[1] = 252;
    if ( nRand > 0 )
    {
      for ( i = nRand; i != 0; --i )
      {
        v17[0] = rand() % 200 + 100;
        v17[1] = rand() % 100 + 50;
        nRand2 = rand() % 2 == 0;
        nRand3 = 3 - (rand() % 2 != 0);
        nRand4 = rand();
        v7 = *pDwArg1;
        v17[2] = nRand4 % 60 + 40;
        v20 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int, int))(v7 + 672))(pDwArg1, 3, nArg2, nArg3);
        v8 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 152))(
               pDwArg1,
               1,
               v17,
               8,
               0xFFFF,
               0,
               0,
               0,
               0);
        v9 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 128))(pDwArg1, v8);
        v10 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v9 + 20);
        nRand5 = rand();
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v10 + nRand5 % 20 - 10);
        nRand6 = rand();
        nArg3 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*pDwArg1 + 376))(pDwArg1, *v20, v12 + nRand6 % 40 - 20);
        nArg2 = v16[rand() % 2];
        result = (*(int (/*thiscall*/ **)(int *))(v7 + 592))(pDwArg1);
      }
    }
  }
  return result;
}



// AI 相位门（this+8607/8668）
// ------------------------------------------------------------
// 0x5B7CC0 sub_5B7CC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7CC0(int this)
{
  int result; // eax
  int nRand; // eax
  int v3; // et2

  sub_5B77F0((int *)this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( result == 0 )
    {
      result = *(uint8_t *)(this + 8607);
      if ( (uint8_t)result == 0 )
      {
        result = *(uint32_t *)(this + 8668);
        if ( result <= 0 )
        {
          result = *(uint32_t *)(this + 7632);
          if ( result == 0 )
          {
            nRand = rand();
            v3 = nRand % 300;
            result = nRand / 300;
            if ( v3 < 5 )
              return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(
                       this,
                       14,
                       0,
                       0,
                       0);
          }
        }
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7CD0 sub_5B7CD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7CD0(int this, int nArg2, int nArg3)
{
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
  *(uint32_t *)(this + 7584) = 1;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7D60 sub_5B7D60
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7D60(int this, int nArg2, int nArg3)
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
  *(uint32_t *)(this + 7588) = 1;
  if ( nArg3 == 2 && nArg2 == 0 )
    *(uint32_t *)(this + 7596) = -50;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7E00 sub_5B7E00
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7E00(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

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
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7564) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = 50;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B7EB0 sub_5B7EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7EB0(int *this, int *pDwArg2)
{
  int result; // eax
  int v4; // eax

  result = (int)pDwArg2;
  if ( pDwArg2 == this )
  {
    v4 = *this;
    *(this + 2166) = 30;
    result = (*(int (/*stdcall*/ **)(uint32_t))(v4 + 384))(0);
    *(this + 2160) = result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7EE0 sub_5B7EE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7EE0(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && rand() % 100 < 5 )
  {
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 124))(
           nArg2,
           30073,
           3,
           0,
           4,
           100,
           1,
           0,
           0);
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v6);
    v8 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)nArg2 + 124))(nArg2, 0, v7);
    v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v8);
    (*(void (/*thiscall*/ **)(int *, int))(v5 + 584))(this, v9);
  }
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B7F90 sub_5B7F90
// ------------------------------------------------------------
int /*thiscall*/ sub_5B7F90(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

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
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint8_t *)(this + 7534) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(uint32_t *)(this + 7596) = 50;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8040 sub_5B8040
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8040(void *this, int nArg2, void *Block)
{
  int result; // eax
  int pObj; // eax

  result = sub_5B7D60((int)this, nArg2, (int)Block);
  if ( Block == nullptr )
  {
    (*(void (**)(void))(*(uint32_t *)this + 700))();
    sub_53F6A0(this);
    if ( operator new(0x8Cu) != nullptr )
      pObj = sub_64B0F0(0, 0x40000000, 7, "Monster/Soceress/Animation_Keraha/ChillingAura");
    else
      pObj = 0;
    (*(void (/*thiscall*/ **)(int, void *, void *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
      pObj,
      this,
      this,
      1,
      0,
      0,
      -1);
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "SHIELD_ICE",
      -1,
      0,
      0);
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 163);
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "WINDSHIELD_LOOP",
             163,
             0,
             0);
  }
  return result;
}



// ============================================================
// 【分区 5】信徒（Believer）（0x5B8120-0x5B9F60）
// 证据：BELIEVER_COMMAND/ATK/PRAY/DMG/DIE/FIND、KNIFE_STICK/KNIFE_HIT、
//       REPAIR_OBJECT 修复、0x5B8CE0 243L 大型主状态机

// 信徒指挥：BELIEVER_COMMAND（97L；this+208/8607/8621/8622 相位）
// ------------------------------------------------------------
// 0x5B8120 sub_5B8120
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8120(void *this, void *pArg2)
{
  int result; // eax

  result = sub_4D9170(pArg2);
  if ( this == pArg2 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 163);
  return result;
}



// 冰盾技能（Soceress 复用）：sub_64B0F0 发射 Monster/Soceress/Animation_Keraha/
//   ChillingAura 光环 + SHIELD_ICE + WINDSHIELD_LOOP（44L）
// ------------------------------------------------------------
// 0x5B8150 sub_5B8150
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8150(uint32_t *this)
{
  int v2; // eax
  int i; // esi
  int v4; // eax
  int fld_e2168; // ecx
  uint32_t v7[3]; // [esp+Ch] [ebp-7Ch]
  int pThis_6DD; // [esp+18h] [ebp-70h]
  bool nRand; // [esp+1Fh] [ebp-69h]
  uint32_t v10[26]; // [esp+20h] [ebp-68h] BYREF

  v10[25] = dword_796E50;
  pThis_6DD = sub_41A5E0((unsigned int)(this + 1757)) != 1 ? 20 : 50;
  v2 = *this;
  v7[0] = 0;
  v7[1] = 45;
  v7[2] = 320;
  qmemcpy(
    v10,
    (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(v2 + 588))(this, "Particle/Dagger.ptl"),
    0x62u);
  nRand = rand() % 100 < 30;
  for ( i = 0; i < 3; ++i )
  {
    v4 = *this;
    fld_e2168 = *(this + 2168);
    v10[18] = v7[i];
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
      this,
      fld_e2168,
      0,
      v10,
      0,
      40,
      0,
      pThis_6DD,
      4,
      0,
      0,
      0);
    if ( !nRand )
      break;
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "THROW_STONE",
           -1,
           0,
           0);
}



// 【vmt200 命中处理器覆写】（44L；虚表 0x6E97F4 +512 槽 —— 信徒族受击处理）
// ------------------------------------------------------------
// 0x5B8240 sub_5B8240
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8240(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi
  int v6; // edx
  uint32_t *v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  char v13; // [esp+7h] [ebp-1h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1908) == 0
    && (int)*(this + 2159) < 6
    && rand() % 100 < 10 )
  {
    v5 = *this;
    v6 = *this;
    v13 = 4;
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int, char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 152))(
           this,
           2,
           &v13,
           1,
           0xFFFF,
           0,
           0,
           0,
           0);
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 124))(this, 0, v8);
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v9);
    v11 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 376))(this, *v7, v10);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v5 + 592))(this, 603, v11);
    ++*(this + 2159);
  }
  return sub_5B7400(this, nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8310 sub_5B8310
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8310(int *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && rand() % 100 < 30 )
  {
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 124))(
           nArg2,
           30074,
           10,
           0,
           4,
           100,
           1,
           0,
           0);
    v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v6);
    v8 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)nArg2 + 124))(nArg2, 0, v7);
    v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v8);
    (*(void (/*thiscall*/ **)(int *, int))(v5 + 584))(this, v9);
  }
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B83C0 sub_5B83C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B83C0(void *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int pThis_2A0; // edi
  int v6; // edx
  unsigned int pThis_2A02; // edi
  int v8; // edx
  int v9; // [esp+10h] [ebp+Ch]
  int v10; // [esp+10h] [ebp+Ch]

  result = nArg3;
  if ( nArg3 == 0 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 830;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 0.5;
    sub_41A590(pThis_2A0, v6, v9);
    pThis_2A02 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pThis_2A02)) - 0.5;
    sub_41A590(pThis_2A02, v8, v10);
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8450 sub_5B8450
// ------------------------------------------------------------
void /*thiscall*/ sub_5B8450(uint32_t *this)
{
  int fld_e1; // ecx
  int fld_e12; // ecx
  int v4; // eax
  int fld_e13; // ecx
  int v6; // eax
  int fld_e14; // edi
  int v8; // ebx
  int v9; // ebx
  int fld_e15; // eax
  int fld_e16; // eax
  int v12; // [esp-10h] [ebp-34h]
  int v13; // [esp-Ch] [ebp-30h]
  float v14; // [esp+4h] [ebp-20h] BYREF
  float v15; // [esp+8h] [ebp-1Ch]
  float v16; // [esp+Ch] [ebp-18h]
  int v17; // [esp+10h] [ebp-14h]
  int v18; // [esp+14h] [ebp-10h]
  int v19; // [esp+18h] [ebp-Ch]
  int v20; // [esp+1Ch] [ebp-8h]
  int v21; // [esp+20h] [ebp-4h] BYREF

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1 + 308))(fld_e1) != 0 )
  {
    fld_e12 = *(this + 1);
    v14 = 0.0;
    v15 = 0.0;
    v16 = 0.0;
    v17 = 0;
    v18 = 0;
    v19 = 0;
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e12 + 120))(fld_e12);
    fld_e13 = *(this + 1);
    v20 = v4;
    v14 = (float)v4;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 124))(fld_e13);
    fld_e14 = *(this + 1);
    v20 = v6;
    v15 = (float)v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e14 + 192))(fld_e14) / 2;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e14 + 128))(fld_e14) + v8;
    fld_e15 = *(this + 1);
    v20 = v9;
    v16 = (float)v9;
    v21 = 0;
    v13 = sub_605840(&v21, fld_e15, &v14, 0);
    v12 = v21;
    fld_e16 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 152))(*(this + 1));
    sub_4E4A50(*(this + 9), 42004, *(this + 20), 0, 0, 0, fld_e16, 0, v12, v13);
    *(this + 18) = *(this + 21);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B8550 sub_5B8550
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8550(int *this, int nArg2)
{
  int result; // eax
  int v4; // eax

  result = sub_4DBC20(nArg2);
  if ( nArg2 == 25 )
  {
    v4 = *this;
    *(this + 2073) = 1000;
    result = (*(int (/*thiscall*/ **)(int *))(v4 + 1040))(this);
    *(uint8_t *)(result + 8) = 1;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8590 sub_5B8590
// ------------------------------------------------------------
int /*usercall*/ sub_5B8590@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 && *(uint8_t *)(pArg1 + 8605) == 1 )
    return sub_5B79F0((int *)pArg1, nArg2, nArg3);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B85C0 sub_5B85C0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5B85C0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int fld_e21; // edx

  sub_4B1030();
  *(this + 20) = nArg4;
  *this = &CNAppendageTimerFireDamage::`vftable';
  *(this + 21) = nArg3;
  sub_5F66A0(1);
  fld_e21 = *(this + 21);
  *(this + 11) = nArg2;
  *(this + 18) = fld_e21;
  *(this + 22) = 0;
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8630 sub_5B8630
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8630(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e22)(uint32_t, int); // ecx
  int result; // eax

  *this = &CNAppendageTimerFireDamage::`vftable';
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 22);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 22) = 0;
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B86A0 sub_5B86A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5B86A0(uint32_t *Block, char pszArg2)
{
  sub_5B8630(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助（this+204/+208 硬直）
// ------------------------------------------------------------
// 0x5B86D0 sub_5B86D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B86D0(uint32_t *this, char pszArg2)
{
  int fld_e1554; // eax

  fld_e1554 = *(this + 1554);
  if ( pszArg2 != 0 )
  {
    sub_4926A0(*(uint32_t *)(fld_e1554 + 16));
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 20));
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 24));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      -100,
      *(uint32_t *)(*(this + 1554) + 16),
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 1554) + 20),
      0,
      0,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
             this,
             200,
             *(uint32_t *)(*(this + 1554) + 24),
             0,
             0,
             0,
             0);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(fld_e1554 + 16));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
  }
}



// RTTI cast 目标解算（73L）
// ------------------------------------------------------------
// 0x5B87C0 sub_5B87C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B87C0(uint32_t *this)
{
  uint32_t *pThis; // ebx
  int result; // eax
  unsigned int v3; // edi
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj3; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int pObj; // eax
  int pObj2; // esi
  int v14; // [esp+4h] [ebp-Ch]
  int v15; // [esp+4h] [ebp-Ch]
  int pObj4; // [esp+8h] [ebp-8h]

  pThis = this;
  result = (*(int (/*fastcall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v3 = 0;
    pObj4 = 0;
    while ( 1 )
    {
      v4 = pThis[29];
      v5 = *(uint32_t *)(v4 + 8);
      v6 = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
      if ( (int)v3 >= v6 )
        break;
      v7 = *(uint32_t *)(v4 + 8);
      if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
        pObj3 = *(uint32_t *)(v7 + 4 * v3);
      else
        pObj3 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 529) != 0 )
      {
        v9 = pThis[29];
        v10 = *(uint32_t *)(v9 + 8);
        if ( v10 != 0 && v3 < (*(uint32_t *)(v9 + 12) - v10) >> 2 )
          v11 = *(uint32_t *)(v10 + 4 * v3);
        else
          v11 = 0;
        pObj = __RTDynamicCast(v11, 0, &CNRDObject `RTTI Type Descriptor', &CNVehicle `RTTI Type Descriptor', 0);
        pObj2 = pObj;
        if ( pObj != 0 )
        {
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
          if ( v14 == (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis)
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj2) != 0
            && (pObj4 == 0
             || (v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 736))(pObj2)) < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 736))(pObj4)) )
          {
            pObj4 = pObj2;
          }
          pThis = this;
        }
      }
      ++v3;
    }
    pThis[1812] = pObj4;
    return pObj4;
  }
  return result;
}



// 信徒指挥 AI：BELIEVER_COMMAND（97L；RTTI 解算 + this+208/8607/8621/8622 相位）
// ------------------------------------------------------------
// 0x5B88E0 sub_5B88E0
// ------------------------------------------------------------
char /*thiscall*/ sub_5B88E0(int *this, char pszArg2)
{
  char result; // al
  int v4; // eax
  unsigned int v5; // edi
  int v6; // edx
  unsigned int v7; // edi
  int v8; // edx
  unsigned int v9; // edi
  int v10; // edx
  unsigned int v11; // edi
  int v12; // edx
  int v13; // edx
  unsigned int v14; // edi
  int v15; // edx
  unsigned int v16; // edi
  int v17; // edx
  unsigned int v18; // edi
  int v19; // edx
  unsigned int v20; // edi
  int v21; // edx
  int v22; // [esp+14h] [ebp+8h]
  int v23; // [esp+14h] [ebp+8h]
  int v24; // [esp+14h] [ebp+8h]
  int v25; // [esp+14h] [ebp+8h]
  int v26; // [esp+14h] [ebp+8h]
  int v27; // [esp+14h] [ebp+8h]
  int v28; // [esp+14h] [ebp+8h]
  int v29; // [esp+14h] [ebp+8h]

  result = pszArg2;
  if ( pszArg2 == 1 )
  {
    if ( *((uint8_t *)this + 8607) == 0 )
    {
      v4 = *this;
      *((uint8_t *)this + 7559) = 1;
      *(this + 1899) = 100;
      v5 = (*(int (/*stdcall*/ **)(uint32_t))(v4 + 672))(0) + 74;
      *(float *)&v22 = COERCE_FLOAT(sub_41A5E0(v5)) + 0.30000001;
      sub_41A590(v5, v6, v22);
      v7 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 830;
      *(float *)&v23 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;
      sub_41A590(v7, v8, v23);
      v9 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 102;
      *(float *)&v24 = COERCE_FLOAT(sub_41A5E0(v9)) - 0.30000001;
      sub_41A590(v9, v10, v24);
      v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 158;
      *(float *)&v25 = COERCE_FLOAT(sub_41A5E0(v11)) - 0.30000001;
      sub_41A590(v11, v12, v25);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
      *((uint8_t *)this + 8607) = 1;
      *((uint8_t *)this + 8621) = 0;
      *((uint8_t *)this + 8622) = 0;
      sub_698F90((int)(this + 2152), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      sub_5B86D0(this, 1);
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "BELIEVER_COMMAND",
               -1,
               0,
               0);
    }
  }
  else if ( pszArg2 == 0 && *((uint8_t *)this + 8607) == 1 )
  {
    v13 = *this;
    *((uint8_t *)this + 7559) = 0;
    *(this + 1899) = 0;
    v14 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v13 + 672))(this, 0) + 74;
    *(float *)&v26 = COERCE_FLOAT(sub_41A5E0(v14)) - 0.30000001;
    sub_41A590(v14, v15, v26);
    v16 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v27 = COERCE_FLOAT(sub_41A5E0(v16)) - 0.30000001;
    sub_41A590(v16, v17, v27);
    v18 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 102;
    *(float *)&v28 = COERCE_FLOAT(sub_41A5E0(v18)) + 0.30000001;
    sub_41A590(v18, v19, v28);
    v20 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0) + 158;
    *(float *)&v29 = COERCE_FLOAT(sub_41A5E0(v20)) + 0.30000001;
    sub_41A590(v20, v21, v29);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    *((uint8_t *)this + 8607) = 0;
    *((uint8_t *)this + 8621) = 0;
    *((uint8_t *)this + 8622) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8B80 sub_5B8B80
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5B8B80(uint32_t *this, int nArg2, uint8_t *uArg3)
{
  uint8_t *result; // eax

  result = uArg3;
  if ( uArg3 == nullptr )
  {
    result = (uint8_t *)(*(this + 1905) + 96);
    *result = 0;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B8BA0 sub_5B8BA0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5B8BA0(void *this, int nArg2, int nArg3)
{
  uint8_t *result; // eax
  int v4; // ecx

  result = (uint8_t *)sub_5B7D60((int)this, nArg2, nArg3);
  if ( nArg3 == 0 )
  {
    result = (uint8_t *)(*(uint32_t *)(v4 + 7620) + 96);
    *result = 1;
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5B8BD0 sub_5B8BD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8BD0(uint32_t *this)
{
  int v2; // eax
  int *v3; // edi
  int fld_e2164; // [esp-18h] [ebp-20h]
  int fld_e2165; // [esp-14h] [ebp-1Ch]

  fld_e2165 = *(this + 2165);
  fld_e2164 = *(this + 2164);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);
  v2 = sub_45EBE0(fld_e2164, fld_e2165);
  v3 = (int *)__RTDynamicCast(v2, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);
  if ( v3 != nullptr && (*(uint8_t (/*thiscall*/ **)(int *))(*v3 + 724))(v3) == 0 )
    sub_5B88E0(v3, 1);
  *(this + 2164) = -1;
  *(this + 2165) = -1;
  return -1;
}



// 信徒语音装载：BELIEVER_DMG/DIE/FIND + KNIFE_HIT 刀命中播报（sub_4015C0）
// ------------------------------------------------------------
// 0x5B8C40 sub_5B8C40
// ------------------------------------------------------------
int /*thiscall*/ sub_5B8C40(uint32_t *this)
{
  *(this + 1698) = 1;
  *(this + 1700) = 1;
  *(this + 1699) = 2;
  *(this + 1701) = 2;
  *(this + 1702) = 3;
  sub_4015C0("BELIEVER_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("BELIEVER_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("BELIEVER_FIND", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("KNIFE_HIT", 9u);  // 【std::string构造赋值】
  *(this + 2166) = 10;
  *(this + 2167) = 0;
  *(this + 2159) = 0;
  *(this + 2168) = 30014;
  return 0;
}



// 信徒大型主状态机（243L）：BELIEVER_COMMAND/ATK/PRAY + REPAIR_OBJECT 修复演出
//   （sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5B8CE0 sub_5B8CE0
// ------------------------------------------------------------
void /*userpurge*/ sub_5B8CE0(uint32_t *pArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // edi
  uint32_t *v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int *v17; // eax
  int pObj; // edi
  uint8_t *v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int fArg22; // [esp+1Ch] [ebp-30h]
  int v25; // [esp+24h] [ebp-28h]
  int v26; // [esp+28h] [ebp-24h]
  uint8_t *Block; // [esp+38h] [ebp-14h]
  char v28; // [esp+3Fh] [ebp-Dh] BYREF
  int v29; // [esp+48h] [ebp-4h]

  v7 = pArg1[1639];
  if ( v7 == 8 )
  {
    v8 = ArgList;
    if ( ArgList != 8 && (sub_41A5E0((unsigned int)(pArg1 + 1757)) == 1 || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 2) )
      *((uint8_t *)pArg1 + 8604) = 0;
  }
  else
  {
    if ( v7 == 10 )
    {
      if ( ArgList == 0 )
      {
        v9 = pArg1[2072];
        if ( v9 != 0 )
        {
          if ( v9 == 1 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(
              pArg1,
              "BELIEVER_COMMAND",
              -1,
              0,
              0);
            sub_5B8BD0(pArg1);
          }
          else if ( v9 == 2 )
          {
            sub_5B7660(pArg1);
          }
        }
        else
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )
          {
            v10 = pArg1[2160] - 600;
            v28 = 0;
            switch ( v10 )
            {
              case 0:
                v28 = 2;
                break;
              case 1:
                v28 = 1;
                break;
              case 2:
                v28 = 3;
                break;
              case 3:
                v28 = 4;
                break;
              default:
                break;
            }
            v11 = *pArg1;
            v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 672))(pArg1, 0);
            v13 = (*(int (/*thiscall*/ **)(uint32_t *, int, char *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v11 + 152))(
                    pArg1,
                    2,
                    &v28,
                    1,
                    0xFFFF,
                    0,
                    0,
                    0,
                    0);
            v14 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 124))(pArg1, 0, v13);
            v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v14);
            v16 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 376))(pArg1, *v12, v15);
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v11 + 592))(pArg1, pArg1[2160], v16);
          }
          ++pArg1[2159];
        }
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 16));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 20));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 24));
      sub_5B7500(0);
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 996))(pArg1);
    }
    v8 = ArgList;
  }
  if ( v8 == 15 )
  {
    v17 = *(int **)(pArg4 + 4);
    v26 = v17[1];
    v25 = *v17;
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);
    pObj = sub_45EBE0(v25, v26);
    if ( pObj == 0 )
      return;
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "REPAIR_OBJECT", -1, 0, 0);
    Block = operator new(0x80u);
    v29 = 0;
    if ( Block != nullptr )
    {
      fArg2 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 740))(pObj) * 0.30000001;
      *(float *)&fArg22 = fArg2;
      v19 = sub_4D6810(Block, fArg22, 5000, 1, 1);
    }
    else
    {
      v19 = nullptr;
    }
    v20 = *(uint32_t *)v19;
    v29 = -1;
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v20 + 56))(v19, pObj, pArg1, 0, 0, 0, -1);
    sub_4926A0(*(uint32_t *)(pArg1[1554] + 4));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 4));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 0, 0, 0, 0, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);
    v8 = ArgList;
    pArg1[2161] = sub_699000((int)(pArg1 + 9));  // 【clock_now(clk)】
    ++pArg1[2162];
  }
  sub_4E33D0((int)pArg1, pArg4, fArg2, v8, pArg4, *(float *)&nArg5, *(float *)&nArg6);
  switch ( v8 )
  {
    case 8:
      if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 0
        || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 1
        || sub_41A5E0((unsigned int)(pArg1 + 1757)) == 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "BELIEVER_ATK", -1, 0, 0);
      }
      break;
    case 3:
      if ( pArg1[1787] == 25 )
      {
        v21 = sub_699000((int)(pArg1 + 1910));  // 【clock_now(clk)】
        v22 = *pArg1;
        pArg1[1926] = v21 + 5000;
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v22 + 1104))(pArg1, 4);
      }
      break;
    case 14:
      sub_4926A0(*(uint32_t *)pArg1[1554]);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)pArg1[1554]);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);
      break;
    case 10:
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "BELIEVER_PRAY", -1, 0, 0);
      v23 = pArg1[2072];
      if ( v23 != 0 )
      {
        if ( v23 == 1 || v23 == 2 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
            pArg1,
            1,
            0,
            0,
            0,
            0,
            0);
          sub_4926A0(*(uint32_t *)(pArg1[1554] + 8));
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 992))(
            pArg1,
            *(uint32_t *)(*(uint32_t *)(pArg1[1554] + 8) + 36),
            1);
          sub_5B86D0(1);
          ++pArg1[2163];
          pArg1[2164] = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 4);
          pArg1[2165] = *(uint32_t *)(*(uint32_t *)(pArg4 + 4) + 8);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
          pArg1,
          0,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
          pArg1,
          1,
          0,
          0,
          0,
          0,
          0);
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 992))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1[1554] + 8) + 36), 1);
        sub_5B86D0(1);
        sub_5B7500(1);
      }
      break;
    default:
      break;
  }
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5B9240 sub_5B9240
// ------------------------------------------------------------
int /*thiscall*/ sub_5B9240(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  result = sub_5B8CE0(this, ArgList, fArg3, nArg4, nArg5);
  if ( *(this + 1639) == 5 )
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 216))(this, 163);
  return result;
}



// RTTI cast 目标解算（87L）
// ------------------------------------------------------------
// 0x5B9280 sub_5B9280
// ------------------------------------------------------------
int /*thiscall*/ sub_5B9280(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int *v6; // eax
  int result; // eax
  int pObj; // esi
  unsigned int i; // edi
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // ecx
  int pObj2; // eax
  uint32_t *pMem; // eax
  uint32_t *v21; // eax
  int v22; // [esp-8h] [ebp-20h]
  int v23; // [esp-4h] [ebp-1Ch]

  if ( ArgList != 16 )
    return sub_5B8CE0(this, ArgList, fArg3, nArg4, nArg5);
  v6 = *(int **)(LODWORD(fArg3) + 4);
  v23 = v6[1];
  v22 = *v6;
  (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);
  result = sub_45EBE0(v22, v23);
  pObj = result;
  if ( result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
      v11 = *(uint32_t *)(v10 + 4);
      v12 = v11 != 0 ? (*(uint32_t *)(v10 + 8) - v11) >> 2 : 0;
      if ( (int)i >= v12 )
        break;
      v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
      v14 = *(uint32_t *)(v13 + 4);
      if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
        v15 = *(uint32_t *)(v14 + 4 * i);
      else
        v15 = 0;
      if ( *(uint32_t *)(v15 + 4) == pObj )
      {
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
        v17 = *(uint32_t *)(v16 + 4);
        if ( v17 != 0 && i < (*(uint32_t *)(v16 + 8) - v17) >> 2 )
          v18 = *(uint32_t *)(v17 + 4 * i);
        else
          v18 = 0;
        pObj2 = __RTDynamicCast(
                v18,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNAppendageTimerFireDamage `RTTI Type Descriptor',
                0);
        if ( pObj2 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);
          break;
        }
      }
    }
    pMem = operator new(0x5Cu);
    if ( pMem != nullptr )
      v21 = sub_5B85C0(pMem, 10000, 999, 20);
    else
      v21 = nullptr;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int *, uint32_t, uint32_t, uint32_t, int))(*v21 + 56))(
             v21,
             pObj,
             this,
             0,
             0,
             0,
             -1);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B93F0 sub_5B93F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5B93F0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  void *pMem; // eax
  int pObj; // eax
  unsigned int v7; // edi
  int v8; // edx
  unsigned int v9; // edi
  int v10; // edx
  int v11; // [esp+20h] [ebp+Ch]
  int v12; // [esp+20h] [ebp+Ch]

  result = sub_5B7CD0((int)this, nArg2, nArg3);
  if ( nArg3 == 0 )
  {
    if ( *(this + 2169) == 0 )
    {
      pMem = operator new(0x64u);
      if ( pMem != nullptr )
        pObj = sub_51A7D0(pMem);
      else
        pObj = 0;
      *(this + 2169) = pObj;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2169) + 56))(
        *(this + 2169),
        this,
        this,
        1,
        0,
        0,
        -1);
    }
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.5;
    sub_41A590(v7, v8, v11);
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v9)) + 0.5;
    sub_41A590(v9, v10, v12);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// 插刀技能：KNIFE_STICK 播报（sub_431230 参数打包; this+200/8605/8606 相位）
// ------------------------------------------------------------
// 0x5B9500 sub_5B9500
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9500(uint8_t *this)
{
  void *Block2; // eax
  bool v3; // zf
  uint8_t v4[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v6; // [esp+10h] [ebp-18h]
  int v7; // [esp+14h] [ebp-14h]
  uint32_t v8[4]; // [esp+18h] [ebp-10h] BYREF

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) == 2 && *(this + 8606) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "KNIFE_STICK",
      -1,
      0,
      0);
    *(this + 8606) = 1;
  }
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 170) != 0 )
  {
    Block = nullptr;
    v6 = 0;
    v7 = 0;
    v8[3] = 0;
    v8[0] = 5;
    sub_431230((int)v4, v8);
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint8_t *, int, int))(*(uint32_t *)this + 472))(this, 5, v4, 1, 1);
    Block2 = Block;
    v3 = Block == nullptr;
    *(this + 8605) = 1;
    if ( !v3 )
      j__free(Block2);
  }
}



// AI 复合（sub_431230+sub_699000+RTTI cast, 84L）
// ------------------------------------------------------------
// 0x5B95D0 sub_5B95D0
// ------------------------------------------------------------
void /*thiscall*/ sub_5B95D0(uint32_t *this)
{
  unsigned int i; // ebx
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // eax
  int pObj; // esi
  int v12; // ebx
  int v13; // eax
  int v14; // edx
  void *pBuf[4]; // [esp+4h] [ebp-28h] BYREF
  float v16; // [esp+14h] [ebp-18h] BYREF
  int v17; // [esp+18h] [ebp-14h]
  unsigned int v18; // [esp+1Ch] [ebp-10h]
  int v19; // [esp+28h] [ebp-4h]

  if ( (int)*(this + 2162) < 3
    && *(this + 2161) + 7000 <= (unsigned int)sub_699000((int)(this + 9))  // 【clock_now(clk)】
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);
      v4 = *(uint32_t *)(fld_e29 + 8);
      v18 = i;
      v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
      if ( (int)i >= v5 )
        break;
      v6 = *(uint32_t *)(fld_e29 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
        pObj2 = *(uint32_t *)(v6 + 4 * i);
      else
        pObj2 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )
      {
        fld_e292 = *(this + 29);
        v9 = *(uint32_t *)(fld_e292 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        pObj = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNVehicle `RTTI Type Descriptor', 0);
        if ( pObj != 0 )
        {
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
          if ( v12 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
            && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj, 0) <= 100 )
          {
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 736))(pObj);
            v13 = *(uint32_t *)pObj;
            v16 = (float)v17;
            v17 = (*(int (/*thiscall*/ **)(int))(v13 + 740))(pObj);
            if ( (double)v17 * 0.30000001 >= v16 )
            {
              memset(&pBuf[1], 0, 12);
              v14 = *(uint32_t *)pObj;
              v19 = 0;
              v16 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(v14 + 48))(pObj));
              sub_431230((int)pBuf, &v16);
              v16 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj));
              sub_431230((int)pBuf, &v16);
              (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 15, pBuf, 0, 0);
              sub_5E5260(pBuf);
              return;
            }
          }
          i = v18;
        }
      }
    }
  }
}



// 参数打包 AI（sub_431230+RTTI cast）
// ------------------------------------------------------------
// 0x5B97A0 sub_5B97A0
// ------------------------------------------------------------
void /*thiscall*/ sub_5B97A0(uint32_t *this)
{
  int fld_e1908; // eax
  int i; // edi
  int fld_e29; // ecx
  int v5; // edx
  int v6; // eax
  int pObj; // eax
  int v8; // eax
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v10[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    fld_e1908 = *(this + 1908);
    if ( (fld_e1908 == 0 || fld_e1908 == 2 && *(this + 1909) == 0)
      && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
      && *(this + 1787) != 25
      && *(this + 1813) != 0
      && (int)*(this + 2159) < 3
      && rand() % 300 < 20 )
    {
      v10[0] = 0;
      for ( i = 0; ; ++i )
      {
        fld_e29 = *(this + 29);
        v5 = *(uint32_t *)(fld_e29 + 8);
        v6 = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;
        if ( i >= v6 )
          break;
        pObj = sub_4259D0(i);
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
        {
          v8 = sub_4259D0(i);
          if ( *(uint32_t **)(__RTDynamicCast(
                              v8,
                              0,
                              &CNRDObject `RTTI Type Descriptor',
                              &IRDMonster `RTTI Type Descriptor',
                              0)
                          + 8352) == this )
            ++v10[0];
        }
      }
      if ( v10[0] < 2 )
      {
        memset(&pBuf[1], 0, 12);
        v10[3] = 0;
        v10[0] = 0;
        sub_431230((int)pBuf, v10);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 10, pBuf, 0, 0);
        sub_5E5260(pBuf);
      }
    }
  }
}



// 参数打包 AI（sub_431230+RTTI cast, 88L）
// ------------------------------------------------------------
// 0x5B98F0 sub_5B98F0
// ------------------------------------------------------------
void /*thiscall*/ sub_5B98F0(uint32_t *this, int nArg2)
{
  int fld_e1908; // eax
  int v4; // ebx
  int fld_e29; // ecx
  int v6; // edx
  int v7; // eax
  int pObj; // eax
  int v9; // eax
  int pObj2; // esi
  void *v11; // [esp+4h] [ebp-1Ch] BYREF
  int v12; // [esp+8h] [ebp-18h]
  int v13; // [esp+Ch] [ebp-14h]
  int v14; // [esp+10h] [ebp-10h]
  int v15; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 0 )
    return;
  fld_e1908 = *(this + 1908);
  if ( fld_e1908 != 0 && (fld_e1908 != 2 || *(this + 1909) != 1) )
    return;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 0
    || *(this + 1787) == 25
    || nArg2 != 1 && nArg2 != 2
    || (int)*(this + 2163) >= 3
    || *(this + 1813) == 0
    || rand() % 300 >= 20 )
  {
    return;
  }
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  sub_431230((int)&v11, &nArg2);
  v4 = 0;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v6 = *(uint32_t *)(fld_e29 + 8);
    v7 = v6 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 : 0;
    if ( v4 >= v7 )
      break;
    pObj = sub_4259D0(v4);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) == 0 )
      goto LABEL_28;
    v9 = sub_4259D0(v4);
    pObj2 = __RTDynamicCast(v9, 0, &CNRDObject `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0);
    if ( pObj2 == 0 )
      goto LABEL_28;
    if ( nArg2 != 1 )
    {
      if ( nArg2 != 2 || *(int *)(pObj2 + 8668) > 0 )
        goto LABEL_28;
      goto LABEL_24;
    }
    if ( *(uint8_t *)(pObj2 + 8607) != 0 )
    {
      ++v4;
    }
    else
    {
LABEL_24:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj2) != 0
        && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 260
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 263
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 264) )
      {
        nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);
        sub_431230((int)&v11, &nArg2);
        nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);
        sub_431230((int)&v11, &nArg2);
        break;
      }
LABEL_28:
      ++v4;
    }
  }
  if ( v12 != 0 && (unsigned int)((v13 - v12) >> 2) > 1 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 10, &v11, 0, 0);
  sub_5E5260(&v11);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B00 sub_5B9B00
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B00(int *this)
{
  sub_5B77F0(this);
  sub_5B87C0(this);
  sub_5B95D0(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B20 sub_5B9B20
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B20(int *this)
{
  sub_5B77F0(this);
  sub_5B97A0(this);
  sub_5B98F0(this, 2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5B9B40 sub_5B9B40
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9B40(int *this)
{
  sub_5B77F0(this);
  sub_5B97A0(this);
  sub_5B98F0(this, 1);
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5B9B60 sub_5B9B60
// ------------------------------------------------------------
int /*thiscall*/ sub_5B9B60(void *this, int nArg2, int nArg3, int nArg4)
{
  int pThis_348; // eax
  int pObj; // edi
  int v7; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v10; // [esp+20h] [ebp-4h]

  pThis_348 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  pObj = nArg2;
  if ( pThis_348 == 8
    && sub_41A5E0((unsigned int)this + 7028) == 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0
    && rand() % 100 < 30 )
  {
    memset(&pBuf[1], 0, 12);
    v7 = *(uint32_t *)pObj;
    v10 = 0;
    nArg2 = (*(int (/*thiscall*/ **)(int))(v7 + 48))(pObj);
    sub_431230((int)pBuf, &nArg2);
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
    sub_431230((int)pBuf, &nArg2);
    (*(void (/*thiscall*/ **)(void *, int, void **, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 16, pBuf, 0, 0);
    v10 = -1;
    sub_5E5260(pBuf);
  }
  return sub_4DB480(pObj, nArg3, nArg4);
}



// 祈祷技能：BELIEVER_PRAY 播报（103L；this+208 相位 —— 治疗channel/咏唱【推断】）
// ------------------------------------------------------------
// 0x5B9C60 sub_5B9C60
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9C60(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1639; // edi
  bool v7; // zf
  int v8; // edi
  uint8_t v9[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v11; // [esp+10h] [ebp-14h]
  int v12; // [esp+14h] [ebp-10h]
  int v13; // [esp+20h] [ebp-4h]

  fld_e1639 = *(this + 1639);
  if ( ArgList == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 3 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      Block = nullptr;
      v11 = 0;
      v12 = 0;
      v13 = 0;
      ArgList = 3;
      sub_431230((int)v9, &ArgList);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 10, v9, 0, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
  else
  {
    v7 = fld_e1639 == 10;
    v8 = ArgList;
    if ( v7 )
    {
      if ( ArgList == 0 && *(this + 2072) == 3 )
      {
        sub_49C970(8, ArgList, ArgList);
        sub_49C5F0(9, 0, 0, 4000);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
          (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
            this,
            20014,
            10,
            0,
            0,
            0,
            0,
            0,
            4,
            0,
            0,
            0);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 16));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 24));
      sub_5B7500(this, 0);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 996))(this);
    }
    sub_5B8CE0(this, v8, fArg3, nArg4, nArg5);
    if ( v8 == 10 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "BELIEVER_PRAY",
        -1,
        0,
        0);
      if ( *(this + 2072) == 3 )
      {
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
        sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 992))(
          this,
          *(uint32_t *)(*(uint32_t *)(*(this + 1554) + 8) + 36),
          1);
        sub_5B86D0(this, 1);
        sub_5B7500(this, 1);
      }
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5B9EA0 sub_5B9EA0
// ------------------------------------------------------------
void */*thiscall*/ sub_5B9EA0(uint32_t *this, uint32_t *Block)
{
  void *result; // eax
  int v4; // eax
  uint32_t *pMem; // edi
  uint32_t *pMem2; // ecx

  result = Block;
  if ( Block == this )
  {
    v4 = *this;
    *(this + 2166) = 20;
    (*(void (**)(void))(v4 + 700))();
    sub_53F6A0(this);
    pMem = operator new(0x90u);
    if ( pMem != nullptr )
    {
      sub_64C710(300, 1041865114, 1041865114, 0, 0);
      *pMem = &CNAuraMasterATDFSPEEDUpFather::`vftable';
      pMem2 = pMem;
    }
    else
    {
      pMem2 = nullptr;
    }
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*pMem2 + 56))(
      pMem2,
      this,
      this,
      0,
      0,
      0,
      -1);
    result = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
    *(this + 2160) = result;
  }
  return result;
}



// ============================================================
// 【分区 6】炮车牛 & 激光炮（CowCannon / DrgCannon）（0x5B9F60-0x5BAC30）
// 证据：Particle/FireMissileParticleFloor.ptl、COWCANNON_READY/SHOOT、
//       Particle/CannonBall{Direct,Angle}.ptl、LASERCANNON_READY、DRGCANNON_READY/SHOOT/MOVE_LOOP

// 地面火导弹：引用 PassiveObject/Common/Particle/FireMissileParticleFloor.ptl
// ------------------------------------------------------------
// 0x5B9F60 sub_5B9F60
// ------------------------------------------------------------
void /*thiscall*/ sub_5B9F60(int *this)
{
  uint32_t *pMem; // eax
  int *fld_e1; // eax
  int fld_e12; // ecx
  int v5; // edx
  int fld_e13; // edi
  int fld_e22; // ebx
  int *fld_e14; // esi
  int v9; // edx
  void *v10; // eax
  int v11; // [esp-Ch] [ebp-38h]
  int v12; // [esp-8h] [ebp-34h]
  int v13; // [esp-4h] [ebp-30h]
  uint8_t v14[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *pMem2; // [esp+1Ch] [ebp-10h]
  int v17; // [esp+28h] [ebp-4h]

  sub_5F66C0();  // 【IRDAppendage__vmt4】
  if ( *(this + 22) == 0 )
  {
    pMem = operator new(0x12Cu);
    pMem2 = pMem;
    v17 = 0;
    if ( pMem != nullptr )
      fld_e1 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/FireMissileParticleFloor.ptl", *(this + 1));
    else
      fld_e1 = nullptr;
    fld_e12 = *(this + 1);
    *(this + 22) = (int)fld_e1;
    v5 = *fld_e1;
    v17 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(v5 + 112))(fld_e1, fld_e12);
  }
  fld_e13 = *(this + 1);
  fld_e22 = *(uint32_t *)*(this + 22);
  v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 128))(fld_e13);
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 124))(fld_e13);
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 120))(fld_e13);
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e22 + 40))(*(this + 22));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 22) + 92))(*(this + 22), v14);
  fld_e14 = (int *)*(this + 1);
  v9 = *fld_e14;
  v17 = 1;
  v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v9 + 80))(fld_e14, 2, 0, v14);
  sub_4600B0(v10, v11, v12, v13);
  if ( Block != nullptr )
    j__free(Block);
}



// 子类扩展字段复位（this+8600/8604/8605）
// ------------------------------------------------------------
// 0x5BA050 sub_5BA050
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA050(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 0;
  *(uint32_t *)(this + 6792) = 0;
  *(uint32_t *)(this + 6796) = 0;
  *(uint32_t *)(this + 6800) = 0;
  *(uint32_t *)(this + 6804) = 0;
  *(uint32_t *)(this + 6808) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BA090 sub_5BA090
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA090(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2150)(uint32_t, int); // ecx
  int result; // eax

  fld_e2150 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2150);
  if ( fld_e2150 != nullptr )
    result = (**fld_e2150)(fld_e2150, 1);
  *(this + 2150) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA0B0 sub_5BA0B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA0B0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // edi
  BOOL v8; // edi

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    result = *(this + 1813);
    if ( result != 0 )
    {
      v7 = (*(int (**)(void))(*(uint32_t *)result + 120))();
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < v7;
      (*(void (/*thiscall*/ **)(uint32_t *, BOOL))(*this + 148))(this, v8);
      return (*(int (/*thiscall*/ **)(uint32_t *, BOOL))(*this + 144))(this, v8);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA120 sub_5BA120
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA120(int *this)
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_4;
      nRand = rand();
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        nRand2 = rand();
        v4 = nRand2 % 100;
        result = nRand2 / 100;
        if ( v4 < 2 )
          goto LABEL_11;
      }
      else
      {
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_11:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA200 sub_5BA200
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA200(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2153)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2154)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e2155)(uint32_t, int); // ecx

  fld_e2153 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2153);
  if ( fld_e2153 != nullptr )
    result = (**fld_e2153)(fld_e2153, 1);
  fld_e2154 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2154);
  *(this + 2153) = 0;
  if ( fld_e2154 != nullptr )
    result = (**fld_e2154)(fld_e2154, 1);
  fld_e2155 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2155);
  *(this + 2154) = 0;
  if ( fld_e2155 != nullptr )
    result = (**fld_e2155)(fld_e2155, 1);
  *(this + 2155) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA250 sub_5BA250
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA250(int *this)
{
  int result; // eax
  int fld_e1813; // edi
  int fld_e18132; // edi

  sub_5BA120(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 2 )
    {
      result = *(this + 1813);
      if ( result != 0 )
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
          if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e1813 )
            (*(void (/*thiscall*/ **)(int *, int))(*this + 144))(this, 1);
        }
        result = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        if ( result == 1 )
        {
          fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
          result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
          if ( result >= fld_e18132 )
            return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 144))(this, 0);
        }
      }
    }
  }
  return result;
}



// 炮弹技能：引用 Particle/CannonBallDirect.ptl + CannonBallAngle.ptl（平射/抛射两种弹道）
// ------------------------------------------------------------
// 0x5BA2F0 sub_5BA2F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA2F0(uint32_t *this)
{
  int v2; // eax

  if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )
    v2 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/CannonBallDirect.ptl");
  else
    v2 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/CannonBallAngle.ptl");
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
           this,
           *(this + 2156),
           0,
           v2,
           0,
           70,
           0,
           50,
           4,
           0,
           0,
           0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA350 sub_5BA350
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA350(int this, int nArg2, int nArg3)
{
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
  *(uint8_t *)(this + 7535) = 1;
  return 0;
}



// 蓄力播报：COWCANNON_READY（炮车牛瞄准, this+8612 相位）
// ------------------------------------------------------------
// 0x5BA3E0 sub_5BA3E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA3E0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // eax

  result = sub_5BA0B0(this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    v7 = *this;
    *((uint8_t *)this + 8612) = 0;
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v7 + 212))(
             this,
             "COWCANNON_READY",
             -1,
             0,
             0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA430 sub_5BA430
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA430(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  unsigned int v5; // eax
  bool v6; // zf
  signed int v7; // eax
  unsigned int v8; // eax

  if ( (uint8_t)nArg4 == 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 1 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 684))(nArg2);
    v7 = sub_41A5E0(v5) & 0x80000001;
    v6 = v7 == 0;
    if ( v7 < 0 )
      v6 = (((uint8_t)v7 - 1) | 0xFFFFFFFE) == -1;
    if ( !v6 )
    {
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 684))(nArg2);
      if ( sub_41A5E0(v8) > 0 && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0) > 90 )
        *(this + 2152) = 0;
    }
  }
  return sub_4D4A20(this, nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA4B0 sub_5BA4B0
// ------------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int /*userpurge*/ sub_5BA4B0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)
{
  int result; // eax
  int v6; // ebx
  int64_t v7; // rax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edi
  int v12; // edi

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);
    if ( v6 != 0 )
    {
      v8 = *(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44);
      v9 = *(uint32_t *)(v8 + 364);
      v10 = v8 + 360;
      if ( v9 != 0 )
        v11 = (*(uint32_t *)(v10 + 8) - v9) >> 5;
      else
        v11 = 0;
      v7 = 1374389535LL * (224 * v11 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));
    }
    else
    {
      v7 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
    }
    v12 = (SHIDWORD(v7) >> 5) + (HIDWORD(v7) >> 31);
    (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
             pArg1,
             nArg4,
             v12,
             0,
             0,
             85,
             0,
             50,
             v6,
             0,
             0,
             0);
  }
  return result;
}



// 激光炮播报组：LASERCANNON_READY + DRGCANNON_READY/SHOOT（79L；激光炮/龙炮共用）
// ------------------------------------------------------------
// 0x5BA570 sub_5BA570
// ------------------------------------------------------------
int /*userpurge*/ sub_5BA570@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int result; // eax
  int v8; // edx
  int savedregs; // [esp+8h] [ebp+0h]
  int savedregsa; // [esp+8h] [ebp+0h]

  if ( *(uint32_t *)(pArg1 + 6556) == 8 )
  {
    if ( sub_41A5E0(pArg1 + 7028) == 4 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, **(uint32_t **)(pArg1 + 6216));
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));
    }
    else if ( sub_41A5E0(pArg1 + 7028) == 2 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 9);
    }
  }
  result = sub_5BA0B0((uint32_t *)pArg1, ArgList, fArg4, nArg5, nArg6);
  if ( ArgList == 8 )
  {
    *(uint8_t *)(pArg1 + 8608) = 0;
    if ( sub_41A5E0(pArg1 + 7028) == 3 )
      sub_41A590(pArg1 + 7028, v8, 4);
    if ( sub_41A5E0(pArg1 + 7028) == 4 )
    {
      sub_5BA4B0((uint32_t *)pArg1, nArg2, pArg1 + 7028, 48029);
      sub_4926A0(**(uint32_t **)(pArg1 + 6216));
      sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
        pArg1,
        100,
        **(uint32_t **)(pArg1 + 6216),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 204))(
        pArg1,
        200,
        *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4),
        0,
        0,
        0,
        0);
      savedregs = 0;
      (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 212))(pArg1, "LASERCANNON_READY");
    }
    else if ( sub_41A5E0(pArg1 + 7028) == 2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(pArg1 + 8620) + 12))(*(uint32_t *)(pArg1 + 8620), 0);
      savedregsa = 0;
      (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 212))(pArg1, "DRGCANNON_READY");
    }
    if ( sub_41A5E0(pArg1 + 7028) == 0 )
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
               pArg1,
               "DRGCANNON_SHOOT",
               -1,
               0,
               0);
    result = sub_41A5E0(pArg1 + 7028);
    if ( result == 1 )
      return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
               pArg1,
               "DRGCANNON_SHOOT",
               -1,
               0,
               0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BA700 sub_5BA700
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA700(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax

  result = nArg3;
  if ( nArg3 == 2 )
    result = nArg2;
  if ( result == 0 )
  {
    result = *(this + 1905);
    *(float *)(result + 4) = *(float *)(result + 4) * 0.33333334;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA730 sub_5BA730
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA730(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

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
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7568) = 1;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(float *)(*(uint32_t *)(this + 7620) + 4) = *(float *)(*(uint32_t *)(this + 7620) + 4) * 3.0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BA7E0 sub_5BA7E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA7E0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e1905; // eax
  double v5; // st7

  result = nArg3;
  if ( nArg3 == 2 )
    result = nArg2;
  if ( result == 0 )
  {
    fld_e1905 = *(this + 1905);
    v5 = *(float *)(fld_e1905 + 132);
    result = fld_e1905 + 128;
    *(float *)(result + 4) = v5 * 0.33333334;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA810 sub_5BA810
// ------------------------------------------------------------
int /*thiscall*/ sub_5BA810(int this, int nArg2, int nArg3)
{
  int result; // eax
  int nArg32; // edx

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
  nArg32 = nArg3;
  *(uint32_t *)(this + 7572) = 0;
  *(uint32_t *)(this + 7568) = 0;
  *(uint32_t *)(this + 7564) = 0;
  *(uint32_t *)(this + 7588) = 0;
  *(uint32_t *)(this + 7584) = 0;
  *(uint32_t *)(this + 7580) = 0;
  *(uint32_t *)(this + 7576) = 0;
  *(uint32_t *)(this + 7596) = 0;
  *(uint32_t *)(this + 7564) = 2;
  if ( nArg3 == 2 )
    nArg32 = nArg2;
  if ( nArg32 == 0 )
    *(float *)(*(uint32_t *)(this + 7620) + 132) = *(float *)(*(uint32_t *)(this + 7620) + 132) * 3.0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BA8D0 sub_5BA8D0
// ------------------------------------------------------------
void /*thiscall*/ sub_5BA8D0(uint32_t **this)
{
  int fld_e2150; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  void *fld_e29; // ecx
  uint8_t v7[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v9; // [esp+20h] [ebp-4h]

  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 2150) + 12))(*(this + 2150), 0);
  fld_e2150 = **(this + 2150);
  v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this);
  v4 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[31])(this, v3 + 50);
  v5 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[30])(this, v4);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2150 + 40))(*(this + 2150), v5);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 2150) + 92))(*(this + 2150), v7);
  fld_e29 = *(this + 29);
  v9 = 0;
  sub_4600B0(fld_e29, 2, 0, (int)v7);
  if ( Block != nullptr )
    j__free(Block);
}



// 移动循环：DRGCANNON_MOVE_LOOP 播报（91L；this+200/8604/8605）
// ------------------------------------------------------------
// 0x5BA980 sub_5BA980
// ------------------------------------------------------------
void /*thiscall*/ sub_5BA980(int *this)
{
  uint32_t *v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // edi
  uint32_t *v10; // edi
  void *fld_e29; // ecx
  void *Block2; // eax
  bool v13; // zf
  int v14; // [esp-Ch] [ebp-34h]
  char v15[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v17; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h]
  uint32_t *v19; // [esp+14h] [ebp-14h]
  bool v20; // [esp+1Bh] [ebp-Dh]
  int v21; // [esp+24h] [ebp-4h]

  sub_4E1780(this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 0
    || (*(int (/*thiscall*/ **)(int *))(*this + 184))(this) == 4
    && (*(int (/*thiscall*/ **)(int *))(*this + 188))(this) == 4 )
  {
    if ( *((uint8_t *)this + 8605) == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);
      *((uint8_t *)this + 8605) = 0;
    }
  }
  else
  {
    if ( *((uint8_t *)this + 8604) == 0
      && (*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 1
       || *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 3) )
    {
      v2 = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];
      v3 = *this;
      v19 = v2;
      v4 = (*(int (/*thiscall*/ **)(int *))(v3 + 152))(this);
      v5 = *this;
      v6 = *v2;
      v20 = v4 == 0;
      v7 = (*(int (/*thiscall*/ **)(int *))(v5 + 128))(this);
      v8 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v7);
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, v8 + 1) != 0 ? -20 : 20;
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v9;
      v10 = v19;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v6 + 40))(v19, v14);
      *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v19 + 28))(v19) + 84) = v20;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v10 + 12))(v10, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, char *))(*v10 + 92))(v10, v15);
      fld_e29 = (void *)*(this + 29);
      v21 = 0;
      sub_4600B0(fld_e29, 2, 0, (int)v15);
      Block2 = Block;
      v13 = Block == nullptr;
      *((uint8_t *)this + 8604) = 1;
      v21 = -1;
      if ( !v13 )
        j__free(Block2);
      Block = nullptr;
      v17 = 0;
      v18 = 0;
    }
    else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 0 && *((uint8_t *)this + 8604) == 1 )
    {
      *((uint8_t *)this + 8604) = 0;
    }
    if ( *((uint8_t *)this + 8605) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "DRGCANNON_MOVE_LOOP",
        9,
        0,
        0);
      *((uint8_t *)this + 8605) = 1;
    }
  }
}



// 开火：COWCANNON_SHOOT 播报（this+200/8608/8612 相位, 60L）
// ------------------------------------------------------------
// 0x5BAB60 sub_5BAB60
// ------------------------------------------------------------
char /*thiscall*/ sub_5BAB60(int this)
{
  int pThis_348; // eax
  int fld_21A0; // ecx

  sub_5BA980((int *)this);
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( pThis_348 == 8 )
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
    if ( *(int *)(pThis_348 + 148) >= 9 )
    {
      LOBYTE(pThis_348) = *(uint8_t *)(this + 8612);
      if ( (uint8_t)pThis_348 == 0 )
      {
        LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                       this,
                       "COWCANNON_SHOOT",
                       -1,
                       0,
                       0);
        *(uint8_t *)(this + 8612) = 1;
      }
    }
  }
  fld_21A0 = *(uint32_t *)(this + 8608);
  if ( fld_21A0 != 0 )
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_21A0 + 840))(fld_21A0);
    if ( pThis_348 == 3 )
    {
      pThis_348 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8608) + 236))(*(uint32_t *)(this + 8608));
      if ( pThis_348 == 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, uint32_t, int, int))(**(uint32_t **)(this + 8608) + 876))(
          *(uint32_t *)(this + 8608),
          0,
          -400,
          -400,
          0,
          2000,
          1);
        LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, int, int))(**(uint32_t **)(this + 8608) + 888))(
                       *(uint32_t *)(this + 8608),
                       0,
                       0,
                       1000,
                       1000);
        *(uint32_t *)(this + 8608) = 0;
      }
    }
  }
  return pThis_348;
}



// ============================================================
// 【分区 7】载具·飞艇（Vehicle / Airship / Zepplin）（0x5BAC30-0x5BCAB0）
// 证据：DRGCANNON_BREAK、Particle/{FCATADestroy,LCATADestroy,CATADestroy,BATIDestroy,
//       EF_Fire,EF_Hikari,FlameThrower}.ptl 破坏粒子族、Monster/Vehicle/Particle/ani/FireSmoke.ani、
//       FLAMETHROWER_FIRE/LOOP + LASERCANNON_SHOOT、AIRSHIP_{01_LOOP,SHOOT,UP,UNLOAD,DOWN,BREAK}、
//       Particle/Zepplin{EX,}Destroy{Fly,Drop}.ptl

// 破损播报：DRGCANNON_BREAK（sub_4015C0 —— 载具破坏语音）
// ------------------------------------------------------------
// 0x5BAC30 sub_5BAC30
// ------------------------------------------------------------
int sub_5BAC30()
{
  return sub_4015C0("DRGCANNON_BREAK", 0xFu);  // 【std::string构造赋值】
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BAC50 sub_5BAC50
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAC50(uint32_t **this, uint32_t **uArg2)
{
  if ( this == uArg2 )
  {
    sub_5BA8D0(this);
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
  }
  return sub_4D9170(uArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BAC80 sub_5BAC80
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAC80(uint32_t **this, uint32_t **uArg2)
{
  if ( this == uArg2 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
    sub_5BA8D0(this);
    ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[54])(this, 9);
  }
  return sub_4D9170(uArg2);
}



// AI 字段访问（this+8608）
// ------------------------------------------------------------
// 0x5BACC0 sub_5BACC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BACC0(int this, int nArg2)
{
  int result; // eax

  if ( this == nArg2 )
  {
    sub_5BA8D0((uint32_t **)this);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 9);
  }
  result = sub_4D9170(nArg2);
  if ( *(uint32_t *)(this + 8608) == nArg2 )
    *(uint32_t *)(this + 8608) = 0;
  return result;
}



// 破坏粒子族（88L）：Particle/{EF_Fire,EF_Hikari,FCATADestroy,LCATADestroy,CATADestroy,
//   FlameThrower}.ptl（F=火焰/L=激光/C=通常/BATI=坠落 前缀分型）
// ------------------------------------------------------------
// 0x5BAD00 sub_5BAD00
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAD00(uint8_t *this)
{
  int pThis_16C; // eax
  int pThis_16C2; // eax
  int pThis_154; // eax
  int v5; // eax
  const char *v6; // edi
  int pThis_16C3; // eax
  int pThis_16C4; // eax
  int result; // eax

  *(this + 8608) = 0;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C = sub_4C3640(this + 364, "Particle/EF_Fire.ptl", this);
    else
      pThis_16C = sub_4C3640(*((uint32_t *)this + 91), "Particle/EF_Fire.ptl", this);
  }
  else
  {
    pThis_16C = 0;
  }
  *((uint32_t *)this + 2153) = pThis_16C;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C2 = sub_4C3640(this + 364, "Particle/EF_Hikari.ptl", this);
    else
      pThis_16C2 = sub_4C3640(*((uint32_t *)this + 91), "Particle/EF_Hikari.ptl", this);
  }
  else
  {
    pThis_16C2 = 0;
  }
  *((uint32_t *)this + 2154) = pThis_16C2;
  pThis_154 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 340))(this) - 270;
  if ( pThis_154 != 0 )
  {
    v5 = pThis_154 - 2;
    if ( v5 == 0 )
    {
      v6 = "Particle/FCATADestroy.ptl";
      goto LABEL_17;
    }
    if ( v5 == 1 )
    {
      v6 = "Particle/LCATADestroy.ptl";
      goto LABEL_17;
    }
  }
  v6 = "Particle/CATADestroy.ptl";
LABEL_17:
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C3 = sub_4C3640(this + 364, v6, this);
    else
      pThis_16C3 = sub_4C3640(*((uint32_t *)this + 91), v6, this);
  }
  else
  {
    pThis_16C3 = 0;
  }
  *((uint32_t *)this + 2150) = pThis_16C3;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C4 = sub_4C3640(this + 364, "Particle/FlameThrower.ptl", this);
    else
      pThis_16C4 = sub_4C3640(*((uint32_t *)this + 91), "Particle/FlameThrower.ptl", this);
  }
  else
  {
    pThis_16C4 = 0;
  }
  *((uint32_t *)this + 2155) = pThis_16C4;
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pThis_16C4 + 112))(pThis_16C4, this);
  result = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  *((uint32_t *)this + 2156) = result;
  return result;
}



// 坠落破坏：引用 Particle/BATIDestroy.ptl
// ------------------------------------------------------------
// 0x5BAEF0 sub_5BAEF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAEF0(uint32_t *this)
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/BATIDestroy.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/BATIDestroy.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 2150) = result;
  *(this + 2152) = 0;
  return result;
}



// 载具烟火：Monster/Vehicle/Particle/ani/FireSmoke.ani（102L；sub_431860）
// ------------------------------------------------------------
// 0x5BAF80 sub_5BAF80
// ------------------------------------------------------------
int /*thiscall*/ sub_5BAF80(uint32_t *this)
{
  int v2; // edi
  int v3; // edi
  int **pThis_869; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  void *fld_e29; // ecx
  bool v9; // zf
  int v10; // edi
  int v11; // edi
  char *v12; // eax
  char *v13; // edi
  int fld_e292; // ecx
  int v15; // ebx
  int v16; // eax
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  char v21[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v23; // [esp+14h] [ebp-20h]
  int v24; // [esp+18h] [ebp-1Ch]
  char *v25; // [esp+1Ch] [ebp-18h]
  int v26; // [esp+20h] [ebp-14h]
  int v27; // [esp+24h] [ebp-10h]
  int v28; // [esp+30h] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
    v3 = v2 + 85;
  else
    v3 = v2 - 85;
  v27 = v3;
  pThis_869 = (int **)(this + 2153);
  v26 = 2;
  do
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(**pThis_869 + 12))(*pThis_869, 0);
    v5 = **pThis_869;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v6 + 60);
    (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 40))(*pThis_869, v27, v7);
    (*(void (/*thiscall*/ **)(int *, char *))(**pThis_869 + 92))(*pThis_869, v21);
    fld_e29 = (void *)*(this + 29);
    v28 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v21);
    v28 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++pThis_869;
    v9 = v26 == 1;
    Block = nullptr;
    v23 = 0;
    v24 = 0;
    --v26;
  }
  while ( !v9 );
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
    v11 = v10 + 75;
  else
    v11 = v10 - 75;
  v27 = v11;
  v26 = sub_42FCB0(228);
  v28 = 1;
  if ( v26 != 0 )
    v26 = sub_431860((char)"Monster/Vehicle/Particle/ani/FireSmoke.ani", 1);
  else
    v26 = 0;
  v28 = -1;
  v12 = (char *)sub_44B6C0(284);
  v13 = v12;
  v25 = v12;
  v28 = 2;
  if ( v12 != nullptr )
  {
    sub_44E0D0(v12, v26, 1);
    *(uint32_t *)v13 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v13 = nullptr;
  }
  fld_e292 = *(this + 29);
  v28 = -1;
  sub_45FE80(fld_e292, (int)v13, 2, 0, (int)v13, (int)this, 0);
  v15 = *(uint32_t *)v13;
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(char *, int))(v15 + 148))(v13, v16);
  v17 = *(uint32_t *)v13;
  v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v18 + 55);
  return (*(int (/*thiscall*/ **)(char *, int, int))(v17 + 112))(v13, v27, v19);
}



// 武器开火播报：FLAMETHROWER_FIRE/LOOP + LASERCANNON_SHOOT（107L；火喷/激光二系）
// ------------------------------------------------------------
// 0x5BB130 sub_5BB130
// ------------------------------------------------------------
void /*usercall*/ sub_5BB130(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // ebx
  int v10; // edx
  void *v11; // eax
  int v12; // [esp-14h] [ebp-34h]
  int v13; // [esp-10h] [ebp-30h]
  int v14; // [esp-Ch] [ebp-2Ch]
  void *v15[7]; // [esp+4h] [ebp-1Ch] BYREF

  sub_5BA980((int *)pArg1);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 8 )
  {
    switch ( sub_41A5E0(pArg1 + 7028) )
    {
      case 0:
      case 1:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 && *(uint8_t *)(pArg1 + 8608) == 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )
            sub_5BA2F0((uint32_t *)pArg1);
          sub_5BAF80((uint32_t *)pArg1);
          v4 = *(uint32_t *)pArg1;
          *(uint8_t *)(pArg1 + 8608) = 1;
          (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t))(v4 + 876))(pArg1, 0, 70, 70, 0);
          v5 = *(uint32_t *)pArg1;
          v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 152))(pArg1, 4);
          v7 = sub_432E50(v6);
          (*(void (/*thiscall*/ **)(int, int))(v5 + 896))(pArg1, v7);
        }
        return;
      case 2:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) < 6 )
          goto LABEL_21;
        if ( *(uint8_t *)(pArg1 + 8608) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "FLAMETHROWER_FIRE",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "FLAMETHROWER_LOOP",
            9,
            0,
            0);
          *(uint8_t *)(pArg1 + 8608) = 1;
LABEL_21:
          if ( *(uint8_t *)(pArg1 + 8608) == 0 )
            return;
        }
        v8 = **(uint32_t **)(pArg1 + 8620);
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1) + 50;
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1) + 1;
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1) != 1 ? -80 : 80;
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + v9;
        (*(void (/*thiscall*/ **)(uint32_t))(v8 + 40))(*(uint32_t *)(pArg1 + 8620));
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(pArg1 + 8620) + 92))(*(uint32_t *)(pArg1 + 8620), v15);
        v10 = *(uint32_t *)pArg1;
        v15[6] = nullptr;
        v11 = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, void **))(v10 + 80))(pArg1, 2, 0, v15);
        sub_4600B0(v11, v12, v13, v14);
        sub_5E5260(v15);
        return;
      case 3:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 1 && *(uint8_t *)(pArg1 + 8608) == 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )
            sub_5BA4B0((uint32_t *)pArg1, 1, nArg3, 30015);
          (*(void (/*thiscall*/ **)(int, const char *, int))(*(uint32_t *)pArg1 + 212))(pArg1, "LASERCANNON_SHOOT", -1);
          *(uint8_t *)(pArg1 + 8608) = 1;
        }
        return;
      case 4:
        if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 && *(uint8_t *)(pArg1 + 8608) == 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 308))(pArg1, nArg3, nArg2) != 0 )
            sub_5BA4B0((uint32_t *)pArg1, nArg2, nArg3, 30036);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, **(uint32_t **)(pArg1 + 6216));
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
            pArg1,
            "LASERCANNON_SHOOT",
            -1,
            0,
            0);
          *(uint8_t *)(pArg1 + 8608) = 1;
        }
        return;
      default:
        return;
    }
  }
}



// AI 字段访问（this+8672）
// ------------------------------------------------------------
// 0x5BB420 sub_5BB420
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB420(uint32_t *this)
{
  int v1; // edx

  v1 = *this;
  *(this + 2150) = *(this + 81);
  *((uint8_t *)this + 8672) = 0;
  *(this + 2169) = 5;
  return (*(int (**)(void))(v1 + 1308))();
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB450 sub_5BB450
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB450(int *this)
{
  int result; // eax
  int nRand2; // eax
  int v4; // et2
  int nRand; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
    case 4:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      nRand = rand();
      v6 = nRand % 100;
      result = nRand / 100;
      if ( v6 < 5 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      return result;
    case 5:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      nRand2 = rand();
      v4 = nRand2 % 100;
      result = nRand2 / 100;
      if ( v4 < 5 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      return result;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      return result;
    default:
      return result;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB530 sub_5BB530
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB530(int *this)
{
  int v2; // edi
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);
  result = *(this + 1639);
  if ( (result == 0 || result == 15) && v2 != 4 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, v2);
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 144))(this, v2);
  }
  return result;
}



// 航行循环：AIRSHIP_01_LOOP 播报（this+200/8672 相位）
// ------------------------------------------------------------
// 0x5BB570 sub_5BB570
// ------------------------------------------------------------
void /*thiscall*/ sub_5BB570(int *this)
{
  int v2; // eax
  int v3; // eax
  int fld_e2150; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int fld_e28; // ecx

  sub_4E1780(this);
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( v2 != 0 )
  {
    v3 = v2 - 14;
    if ( v3 != 0 )
    {
      if ( v3 == 1 )
        (*(void (/*thiscall*/ **)(int *))(*this + 1316))(this);
    }
    else if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0
           && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 15, 0, 0, 0);
    }
  }
  else
  {
    if ( *(this + 2151) == 1 )
    {
      fld_e2150 = *(this + 2150);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) >= fld_e2150 )
      {
        v5 = *this;
        *(this + 2151) = 0;
        v6 = (*(int (/*thiscall*/ **)(int *, int))(v5 + 124))(this, fld_e2150);
        v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);
        (*(void (/*thiscall*/ **)(int *, int))(v5 + 112))(this, v7);
      }
    }
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 184))(this) == 4
      && (*(int (/*thiscall*/ **)(int *))(*this + 188))(this) == 4 )
    {
      if ( *((uint8_t *)this + 8672) == 1 )
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);
        *((uint8_t *)this + 8672) = 0;
      }
    }
    else if ( *((uint8_t *)this + 8672) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "AIRSHIP_01_LOOP", 9, 0, 0);
      *((uint8_t *)this + 8672) = 1;
    }
    fld_e28 = *(this + 28);
    if ( *(uint32_t *)(fld_e28 + 36) == 0 && *(float *)(fld_e28 + 24) != 0.0 )
      sub_494F20(2, 0.0);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB6B0 sub_5BB6B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BB6B0(int *this)
{
  int result; // eax
  int fld_e1813; // edi
  int fld_e18132; // edi
  int pObj; // edi
  int v6; // ebx
  int v7; // edi
  int v8; // edi
  int nRand; // eax
  int v10; // et2

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( result == 0 )
    {
      result = *(this + 1813);
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        if ( result >= *(this + 2150) )
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
          result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - fld_e1813);
          if ( result < 30 )
          {
            if ( (fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                  (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < fld_e18132)
              && (pObj = *(this + 1813),
                  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this),
                  (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) - v6 < 200)
              || (v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                  (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this)) >= v7)
              && (v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                  (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - v8) < 200) )
            {
              nRand = rand();
              v10 = nRand % 300;
              result = nRand / 300;
              if ( v10 < 50 )
                return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
            }
          }
        }
      }
    }
  }
  return result;
}



// AI 相位辅助（97L）
// ------------------------------------------------------------
// 0x5BB7C0 sub_5BB7C0
// ------------------------------------------------------------
int /*usercall*/ sub_5BB7C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  int nRand; // eax
  int v6; // et2
  bool v7; // zf
  signed int nRand2; // eax
  int nRand5; // eax
  int v10; // edi
  uint32_t *v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  uint16_t v19[3]; // [esp+4h] [ebp-8h] BYREF
  bool nRand3; // [esp+Ah] [ebp-2h]
  char nRand4; // [esp+Bh] [ebp-1h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);
  if ( result == 0 )
  {
    result = pArg1[2169];
    if ( result > 0 )
    {
      result = pArg1[1813];
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
        if ( (uint8_t)result != 0 && dword_9A05D4 < 5 )
        {
          nRand = rand();
          v6 = nRand % 300;
          result = nRand / 300;
          if ( v6 < 10 )
          {
            nRand2 = rand() & 0x80000001;
            v7 = nRand2 == 0;
            if ( nRand2 < 0 )
              v7 = (((uint8_t)nRand2 - 1) | 0xFFFFFFFE) == -1;
            if ( v7 )
            {
              v10 = *pArg1;
              v11 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 672))(pArg1, 3, nArg3, nArg2);
              v14 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(v10 + 152))(
                      pArg1,
                      0,
                      0,
                      0,
                      0xFFFF,
                      0,
                      0,
                      0,
                      0);
              v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 128))(pArg1, v14);
            }
            else
            {
              v19[0] = rand() % 200 + 100;
              v19[1] = rand() % 100 + 50;
              nRand3 = rand() % 2 == 0;
              nRand4 = 3 - (rand() % 2 != 0);
              nRand5 = rand();
              v10 = *pArg1;
              v19[2] = nRand5 % 60 + 40;
              v11 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(v10 + 672))(pArg1, 3, nArg3, nArg2);
              v12 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint16_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(v10 + 152))(
                      pArg1,
                      1,
                      v19,
                      8,
                      0xFFFF,
                      0,
                      0,
                      0,
                      0);
              v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 128))(pArg1, v12) + 10;
            }
            v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v13);
            v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v15);
            v17 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 376))(pArg1, *v11, v16);
            (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v10 + 592))(pArg1, 260, v17);
            return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 17, 0, 0, 0);
          }
        }
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BB970 sub_5BB970
// ------------------------------------------------------------
int /*usercall*/ sub_5BB970@<eax>(int nArg1@<ecx>, int nArg2@<edi>)
{
  int result; // eax
  int nRand; // eax
  int v5; // et2
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // esi
  int v11; // eax
  int nRand2; // esi
  int nRand3; // edi

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 308))(nArg1);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v5 = nRand % 100;
    result = nRand / 100;
    if ( v5 < 25 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2, nArg2);
      v6 = *(uint32_t *)dword_8F8520;
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 48))(nArg1);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);
      v8 = *(uint32_t *)dword_8F8520;
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 52))(nArg1);
      (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
      v10 = *(uint32_t *)dword_8F8520;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
      (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);
      nRand2 = rand() % 2;
      nRand3 = rand() % 2;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nRand2);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, nRand3);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BBA60 sub_5BBA60
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBA60(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  uint32_t v6[2]; // [esp+8h] [ebp-14h]
  uint32_t v7[2]; // [esp+10h] [ebp-Ch]
  uint8_t v8; // [esp+1Ah] [ebp-2h] BYREF
  uint8_t v9; // [esp+1Bh] [ebp-1h] BYREF

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 )
    {
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v9);
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v8);
      v4 = *this;
      v6[0] = 0;
      v6[1] = 1;
      v7[0] = 2;
      v7[1] = 3;
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(v4 + 876))(this, v9, 60, 60, 0, -12, 1);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
      v5 = *this;
      if ( v9 == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, int))(v5 + 896))(this, v6[v8], 4);
        return 14;
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t))(v5 + 896))(this, 4, v7[v8]);
    }
    return v3;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BBB30 sub_5BBB30
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBB30(int *this)
{
  int result; // eax

  result = *(this + 2151);
  if ( result == 0 )
    return sub_4DA1D0();
  return result;
}



// 子弹技能：引用 Particle/Bullet.ptl
// ------------------------------------------------------------
// 0x5BBB40 sub_5BBB40
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBB40(int *this, int nArg2, int pArg3, int nArg4, int nArg5)
{
  uint32_t v7[26]; // [esp+Ch] [ebp-68h] BYREF

  v7[25] = dword_796E50;
  qmemcpy(
    v7,
    (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/Bullet.ptl"),
    0x62u);
  if ( nArg2 != -1 )
    v7[19] += nArg2;
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
    this,
    30018,
    0,
    v7,
    0,
    pArg3 + 65,
    10,
    -44,
    4,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
    this,
    30018,
    0,
    v7,
    0,
    pArg3 + 72,
    -10,
    -37,
    4,
    0,
    0,
    0);
  sub_4926A0(*(this + 2179));
  return sub_4926A0(*(this + 2180));
}



// 炸弹技能：引用 Particle/Bomb.ptl
// ------------------------------------------------------------
// 0x5BBC00 sub_5BBC00
// ------------------------------------------------------------
int /*thiscall*/ sub_5BBC00(int *this)
{
  const void *v2; // eax
  int v3; // edx
  uint8_t v5[100]; // [esp+Ch] [ebp-68h] BYREF
  int dword_796E502; // [esp+70h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v2 = (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/Bomb.ptl");
  v3 = *this;
  qmemcpy(v5, v2, 0x62u);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v3 + 580))(
    this,
    30019,
    0,
    v5,
    0,
    55,
    0,
    0,
    4,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
    this,
    30019,
    0,
    v5,
    0,
    0,
    0,
    0,
    4,
    0,
    0,
    0);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
           this,
           30019,
           0,
           v5,
           0,
           -55,
           0,
           0,
           4,
           0,
           0,
           0);
}



// 空袭：AIRSHIP_SHOOT 播报（92L）
// ------------------------------------------------------------
// 0x5BC100 sub_5BC100
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC100(int *this)
{
  int v1; // eax
  int fld_e21714; // eax
  int v3; // eax
  int fld_e2171; // ecx
  int fld_e21712; // eax
  int fld_e21713; // eax
  int result; // eax

  sub_5BB570(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result != 1 )
        return result;
      result = *(this + 2173);
      if ( result == 0 && *(uint32_t *)(*(this + 2175) + 148) == 1 )
      {
        v3 = *this;
        *(this + 2173) = 1;
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(v3 + 308))(this) != 0 )
        {
          fld_e2171 = *(this + 2171);
          if ( fld_e2171 <= 10 )
            fld_e21712 = *(this + 2171);
          else
            fld_e21712 = 20 - fld_e2171;
          (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t))(*this + 1324))(
            this,
            *(this + 2174),
            -9 * fld_e21712,
            0,
            0);
        }
        fld_e21713 = *(this + 2171);
        *(this + 2171) = fld_e21713 + 1;
        if ( fld_e21713 >= *(this + 2172) && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "AIRSHIP_SHOOT",
                 -1,
                 0,
                 0);
      }
      if ( result == 1 )
      {
        result = *(this + 2175);
        if ( *(uint32_t *)(result + 148) != 1 )
          *(this + 2173) = 0;
      }
    }
    else
    {
      result = *(this + 2173);
      if ( result == 0 && *(uint32_t *)(*(this + 2175) + 148) == 1 )
      {
        v1 = *this;
        *(this + 2173) = 1;
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(v1 + 308))(this) != 0 )
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 1324))(this, -1, 0, 0, 0);
        fld_e21714 = *(this + 2171);
        *(this + 2171) = fld_e21714 + 1;
        if ( fld_e21714 >= *(this + 2172) && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
        return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "AIRSHIP_SHOOT",
                 -1,
                 0,
                 0);
      }
      if ( result == 1 )
      {
        result = *(this + 2175);
        if ( *(uint32_t *)(result + 148) != 1 )
          *(this + 2173) = 0;
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BC150 sub_5BC150
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5BC150(uint32_t *this)
{
  int v2; // edi
  int fld_e1813; // ebx
  int v4; // eax
  unsigned int result; // eax
  unsigned int v6; // ecx
  int i; // edx
  int fld_e1905; // edi

  sub_4926A0(*(uint32_t *)(*(this + 1554) + 16));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  v2 = *this;
  fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, bool))(v2 + 148))(this, v4 < fld_e1813);
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
  v6 = 0;
  for ( i = 0; ; i += 32 )
  {
    fld_e1905 = *(this + 1905);
    if ( fld_e1905 == 0 )
      break;
    result = (*(this + 1906) - fld_e1905) >> 5;
    if ( v6 >= result )
      break;
    result = i + fld_e1905;
    ++v6;
    *(uint8_t *)(i + fld_e1905) = 0;
  }
  return result;
}



// 上升播报：AIRSHIP_UP（this+208 相位）
// ------------------------------------------------------------
// 0x5BC210 sub_5BC210
// ------------------------------------------------------------
void */*thiscall*/ sub_5BC210(uint32_t *this)
{
  int v2; // edx
  int fld_e1554; // eax

  v2 = *this;
  *(this + 81) = *(this + 2150);
  fld_e1554 = *(this + 1554);
  *(this + 2151) = 1;
  (*(void (/*stdcall*/ **)(uint32_t))(v2 + 208))(*(uint32_t *)(fld_e1554 + 24));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 28));
  sub_49C5F0(10, 0, 0, 1000);
  return sub_432EA0("AIRSHIP_UP", -1, 0, 0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BC280 sub_5BC280
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5BC280(uint32_t *this, uint32_t *uArg2)
{
  unsigned int result; // eax
  unsigned int v4; // edx
  int i; // edi
  int fld_e1905; // ecx

  result = sub_4D90A0(uArg2);
  if ( *uArg2 == 10 )
  {
    v4 = 0;
    for ( i = 0; ; i += 32 )
    {
      fld_e1905 = *(this + 1905);
      if ( fld_e1905 == 0 )
        break;
      result = (*(this + 1906) - fld_e1905) >> 5;
      if ( v4 >= result )
        break;
      result = i + fld_e1905;
      ++v4;
      *(uint8_t *)(i + fld_e1905) = 1;
    }
  }
  return result;
}



// 卸载/下降：AIRSHIP_UNLOAD + AIRSHIP_DOWN 播报（84L；this+8608 相位）
// ------------------------------------------------------------
// 0x5BC2D0 sub_5BC2D0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5BC2D0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  unsigned int result; // eax
  int v7; // edx
  int fld_e81; // edi
  int v9; // edx

  if ( ArgList == 17 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "AIRSHIP_UNLOAD",
      -1,
      0,
      0);
    result = *(this + 2169) - 1;
    *(this + 2169) = result;
  }
  else
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 15 && ArgList != 16 )
      sub_5BC210(this);
    sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
    if ( ArgList == 14 )
    {
      if ( *(this + 1813) != 0 )
        return sub_5BC150(this);
      else
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);
    }
    else if ( ArgList == 15 )
    {
      v7 = *this;
      *(this + 81) = *(this + 2153);
      *(this + 2151) = -1;
      fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 128))(this);
      sub_495890(0, 3000);
      sub_4A0550(fld_e81);
      sub_4A0600(2);
      sub_4926A0(*(uint32_t *)(*(this + 1554) + 20));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 20));
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
      v9 = *this;
      *((uint8_t *)this + 8608) = 0;
      return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v9 + 212))(
               this,
               "AIRSHIP_DOWN",
               -1,
               0,
               0);
    }
    else
    {
      result = ArgList - 16;
      if ( ArgList == 16 )
      {
        sub_5BC210(this);
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);
      }
    }
  }
  return result;
}



// 硬直字段（this+204/+208）
// ------------------------------------------------------------
// 0x5BC460 sub_5BC460
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC460(int *this, int nArg2)
{
  int result; // eax

  sub_4926A0(*(this + 2177));
  sub_4926A0(*(this + 2175));
  sub_4926A0(*(this + 2178));
  sub_4926A0(*(this + 2176));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2177));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2175));
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2178));
  result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 2176));
  if ( nArg2 != -1 )
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 1554) + 4 * nArg2),
      25,
      5,
      0,
      0);
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
             this,
             -100,
             *(uint32_t *)(*(this + 1554) + 4 * nArg2 + 8),
             32,
             -3,
             0,
             0);
  }
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5BC530 sub_5BC530
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC530(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);
  result = sub_5BC2D0(this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 5 )
    return (*(int (/*thiscall*/ **)(int *, int))(*this + 1328))(this, -1);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result >= 0 )
    {
      if ( result <= 1 )
      {
        *(this + 2170) = sub_699000((int)(this + 9));
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1328))(this, 1);
        *(this + 2172) = 20;
        *(this + 2171) = 0;
        *(this + 2173) = 0;
        return sub_5BB970((int)this, 8);
      }
      else if ( result == 2 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
        if ( (uint8_t)result != 0 )
        {
          sub_5BBC00(this);
          return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
        }
      }
    }
  }
  return result;
}



// 时钟门 AI（this+204/8608 相位）
// ------------------------------------------------------------
// 0x5BC620 sub_5BC620
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC620(int *this)
{
  int fld_e2153; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int *fld_e1554; // eax
  int v7; // eax
  int result; // eax

  fld_e2153 = *(this + 2153);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) <= fld_e2153 && *((uint8_t *)this + 8608) == 0 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, fld_e2153);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v4);
    (*(void (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v5);
    fld_e1554 = (int *)(*(this + 1554) + 24);
    *((uint8_t *)this + 8608) = 1;
    sub_4926A0(*fld_e1554);
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 28));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      -500,
      *(uint32_t *)(*(this + 1554) + 24),
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      500,
      *(uint32_t *)(*(this + 1554) + 28),
      0,
      0,
      0,
      0);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
    sub_424120(*(uint32_t **)(v7 + 132), 2, 300);
  }
  result = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
  if ( result > 1500 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);
  }
  return result;
}



// 飞艇破坏语音：Particle/ZepplinEXDestroyFly/Drop.ptl 引用 + sub_4015C0（54L）
// ------------------------------------------------------------
// 0x5BC720 sub_5BC720
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC720(int *this)
{
  int *fld_e1554; // eax
  int v3; // ecx
  int v4; // eax
  int fld_e2180; // ecx
  int v6; // eax

  fld_e1554 = (int *)*(this + 1554);
  *(this + 2175) = fld_e1554[1];
  *(this + 2177) = *fld_e1554;
  *(this + 2176) = fld_e1554[3];
  *(this + 2178) = fld_e1554[2];
  v3 = fld_e1554[8];
  *(this + 2179) = v3;
  *(this + 2180) = fld_e1554[9];
  v4 = *(uint32_t *)(v3 + 44);
  if ( v4 != 0 )
    v4 = (*(uint32_t *)(v3 + 48) - v4) / 88;
  sub_493400(v3, v4 - 1);
  fld_e2180 = *(this + 2180);
  v6 = *(uint32_t *)(fld_e2180 + 44);
  if ( v6 != 0 )
    v6 = (*(uint32_t *)(fld_e2180 + 48) - v6) / 88;
  sub_493400(fld_e2180, v6 - 1);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
    this,
    100,
    *(this + 2179),
    25,
    5,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(this + 2180),
    32,
    -3,
    0,
    0);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1328))(this, 0);
  *(this + 2173) = 0;
  *(this + 2151) = 0;
  *(this + 2153) = 30;
  sub_4015C0("Particle/ZepplinEXDestroyFly.ptl", 0x20u);  // 【std::string构造赋值】
  return sub_4015C0("Particle/ZepplinEXDestroyDrop.ptl", 0x21u);  // 【std::string构造赋值】
}



// 飞艇破坏 2：Particle/ZepplinDestroyFly/Drop.ptl（空中/坠落两段）
// ------------------------------------------------------------
// 0x5BC840 sub_5BC840
// ------------------------------------------------------------
int /*thiscall*/ sub_5BC840(uint32_t *this)
{
  *(this + 2153) = 1;
  sub_4015C0("Particle/ZepplinDestroyFly.ptl", 0x1Eu);  // 【std::string构造赋值】
  return sub_4015C0("Particle/ZepplinDestroyDrop.ptl", 0x1Fu);  // 【std::string构造赋值】
}



// 破损播报：AIRSHIP_BREAK（108L）
// ------------------------------------------------------------
// 0x5BC880 sub_5BC880
// ------------------------------------------------------------
void /*userpurge*/ sub_5BC880(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, uint32_t *uArg3)
{
  uint32_t *v4; // ecx
  int *v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  uint32_t *v12; // ecx
  int *v13; // edi
  int v14; // eax
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  uint8_t v20[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  uint8_t v22[4]; // [esp+18h] [ebp-1Ch] BYREF
  void *v23; // [esp+1Ch] [ebp-18h]
  int v24; // [esp+20h] [ebp-14h]
  int v25; // [esp+24h] [ebp-10h]
  int v26; // [esp+30h] [ebp-4h]
  void *pMem; // [esp+3Ch] [ebp+8h]

  sub_4D9170(uArg3);
  if ( uArg3 == pArg1 )
  {
    v23 = nullptr;
    v24 = 0;
    v25 = 0;
    v26 = 1;
    if ( operator new(0x12Cu) != nullptr )
    {
      if ( pArg1[2160] < 0x10u )
        v4 = pArg1 + 2155;
      else
        v4 = (uint32_t *)pArg1[2155];
      if ( pArg1[96] < 0x10u )
        v5 = (int *)sub_4C3640(pArg1 + 91, v4, pArg1);
      else
        v5 = (int *)sub_4C3640(pArg1[91], v4, pArg1);
    }
    else
    {
      v5 = nullptr;
    }
    v6 = *v5;
    LOBYTE(v26) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t, int))(v6 + 12))(v5, 0, nArg2);
    v7 = *v5;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v8 + 50);
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v9);
    (*(void (/*thiscall*/ **)(int *, int))(v7 + 40))(v5, v10);
    v11 = (*(int (/*thiscall*/ **)(int *, uint8_t *))(*v5 + 92))(v5, v20);
    LOBYTE(v26) = 2;
    sub_4E77D0((int)v22, v11);
    LOBYTE(v26) = 0;
    if ( Block != nullptr )
      j__free(Block);
    sub_4600B0((void *)pArg1[29], 2, 0, (int)v22);
    pMem = operator new(0x12Cu);
    LOBYTE(v26) = 3;
    if ( pMem != nullptr )
    {
      if ( pArg1[2167] < 0x10u )
        v12 = pArg1 + 2162;
      else
        v12 = (uint32_t *)pArg1[2162];
      if ( pArg1[96] < 0x10u )
        v13 = (int *)sub_4C3640(pArg1 + 91, v12, pArg1);
      else
        v13 = (int *)sub_4C3640(pArg1[91], v12, pArg1);
    }
    else
    {
      v13 = nullptr;
    }
    v14 = *v13;
    LOBYTE(v26) = 0;
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v14 + 12))(v13, 0);
    v15 = *v13;
    v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v16 + 50);
    v18 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v17);
    (*(void (/*thiscall*/ **)(int *, int))(v15 + 40))(v13, v18);
    v19 = (*(int (/*thiscall*/ **)(int *, uint8_t *))(*v13 + 92))(v13, v20);
    LOBYTE(v26) = 4;
    sub_4E77D0((int)v22, v19);
    LOBYTE(v26) = 0;
    if ( Block != nullptr )
      j__free(Block);
    sub_4600B0((void *)pArg1[29], 2, 0, (int)v22);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "AIRSHIP_BREAK", -1, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 216))(pArg1, 9);
    if ( v23 != nullptr )
      j__free(v23);
  }
}



// ============================================================
// 【分区 8】僵尸撕咬变体与字段群（0x5BCAB0-0x5BD1B0）
// 证据：ZOMBIE_BITE 撕咬（0x5BCAB0 101L）、HOLD 蓄力（0x5BCFE0）

// 撕咬 AI（僵尸变体）：ZOMBIE_BITE 播报（101L）
// ------------------------------------------------------------
// 0x5BCAB0 sub_5BCAB0
// ------------------------------------------------------------
int /*usercall*/ sub_5BCAB0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  int result; // eax
  int pObj2; // eax
  int v7; // eax
  int v8; // ebx
  int pObj; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  unsigned int v19; // eax
  int v20; // [esp+4h] [ebp-18h] BYREF
  int v21; // [esp+8h] [ebp-14h] BYREF
  uint32_t pBuf[4]; // [esp+Ch] [ebp-10h] BYREF

  sub_4E1780(pArg1);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) - 14;
  if ( v4 != 0 )
  {
    result = v4 - 1;
    if ( result == 0 )
    {
      result = *(uint8_t *)(pArg1[30] + 170);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
    }
  }
  else
  {
    pObj2 = pArg1[2157];
    if ( pObj2 != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 840))(pObj2) == 9 )
      {
        if ( *(uint8_t *)(pArg1[30] + 170) != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg3) != 0 )
          {
            v7 = *pArg1;
            v20 = 0;
            v21 = 0;
            memset(pBuf, 0, sizeof(pBuf));
            (*(void (/*thiscall*/ **)(uint32_t *, int *, int *, uint32_t *))(v7 + 1312))(pArg1, &v20, &v21, pBuf);
            sub_4E5F70(nArg2, (int)pArg1, pArg1[2157], (float *)&v20, 1, 1);
          }
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*pArg1 + 212))(pArg1, "ZOMBIE_BITE", -1, 0);
        }
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 604))(pArg1[2157], 0);
        (*(void (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2157] + 612))(pArg1[2157], 1, 1);
        v8 = *(uint32_t *)pArg1[2157];
        pObj = pArg1[2157];
        v10 = (*(int (**)(void))(v8 + 128))();
        v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v10);
        v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v11 - 1);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 112))(pArg1[2157], v12);
        v13 = *(uint32_t *)pArg1[2157];
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
        v15 = sub_432E50(v14);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v13 + 148))(pArg1[2157], v15);
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 840))(pArg1[2157]) != 5
             && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 308))(pArg1[2157]) != 0 )
      {
        v16 = *(uint32_t *)pArg1[2157];
        v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
        v18 = sub_432E50(v17);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v16 + 144))(pArg1[2157], v18);
        (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, int, uint32_t))(*(uint32_t *)pArg1[2157] + 560))(pArg1[2157], 9, 0, 2, 0);
        (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 564))(pArg1[2157]);
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
    }
    if ( *(uint8_t *)(pArg1[30] + 170) != 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
    result = pArg1[2157];
    if ( result != 0 )
    {
      v19 = (*(int (**)(void))(*(uint32_t *)result + 684))();
      result = sub_41A5E0(v19);
      if ( result <= 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BCCF0 sub_5BCCF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BCCF0(void *this, int nArg2, int nArg3, int nArg4)
{
  (*(void (/*thiscall*/ **)(void *, int, int, int))(*(uint32_t *)this + 1308))(this, nArg2, nArg3, nArg4);
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// RTTI cast 大型 AI（114L）
// ------------------------------------------------------------
// 0x5BCD30 sub_5BCD30
// ------------------------------------------------------------
float */*thiscall*/ sub_5BCD30(int *this, float *pArg2, float *pArg3, float *pArg4)
{
  char fld_e2157; // al
  int fld_e21572; // ecx
  int pObj2; // eax
  float *result; // eax
  int v9; // eax
  int fld_e21573; // ecx
  int v11; // eax
  double fld_e21574; // st7
  int v13; // eax
  int fld_e21579; // ecx
  int v15; // eax
  double fld_e215710; // st7
  int v17; // eax
  int fld_e21575; // ecx
  int v19; // eax
  double fld_e21576; // st7
  int v21; // eax
  int fld_e21577; // ecx
  int v23; // eax
  double fld_e21578; // st7
  int fld_e215711; // edi
  int pObj; // ebx
  int v27; // esi
  int v28; // edi
  int v29; // edi

  fld_e2157 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273);
  fld_e21572 = *(this + 2157);
  if ( fld_e2157 != 0 )
  {
    pObj2 = __RTDynamicCast(fld_e21572, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
    result = *(float **)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1032))(pObj2);
    if ( result == (float *)1 )
    {
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      fld_e21573 = *(this + 2157);
      if ( v9 != 0 )
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21573 + 120))(fld_e21573) - 52;
      else
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21573 + 120))(fld_e21573) + 52;
      *pArg2 = (float)v11;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
      fld_e21574 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 5);
      *pArg4 = fld_e21574;
      return pArg4;
    }
    else if ( result != nullptr )
    {
      if ( result == (float *)2 )
      {
        v17 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        fld_e21575 = *(this + 2157);
        if ( v17 != 0 )
          v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21575 + 120))(fld_e21575) - 44;
        else
          v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21575 + 120))(fld_e21575) + 44;
        *pArg2 = (float)v19;
        *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
        fld_e21576 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 32);
        *pArg4 = fld_e21576;
        return pArg4;
      }
      else if ( result == (float *)3 )
      {
        v21 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        fld_e21577 = *(this + 2157);
        if ( v21 != 0 )
          v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21577 + 120))(fld_e21577) - 40;
        else
          v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21577 + 120))(fld_e21577) + 40;
        *pArg2 = (float)v23;
        *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
        fld_e21578 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 2);
        *pArg4 = fld_e21578;
        return pArg4;
      }
    }
    else
    {
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      fld_e21579 = *(this + 2157);
      if ( v13 != 0 )
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21579 + 120))(fld_e21579) - 34;
      else
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21579 + 120))(fld_e21579) + 34;
      *pArg2 = (float)v15;
      *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
      fld_e215710 = (double)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 128))(*(this + 2157)) + 12);
      *pArg4 = fld_e215710;
      return pArg4;
    }
  }
  else
  {
    *pArg2 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21572 + 120))(fld_e21572);
    *pArg3 = (float)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2157) + 124))(*(this + 2157)) + 1);
    fld_e215711 = *(this + 2157);
    pObj = fld_e215711;
    v27 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
    v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e215711 + 128))(fld_e215711) - v27;
    v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 192))(pObj) + v28;
    *pArg4 = (float)v29;
    return pArg4;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BCFC0 sub_5BCFC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BCFC0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2167)(uint32_t, int); // ecx
  int result; // eax

  fld_e2167 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);
  if ( fld_e2167 != nullptr )
    result = (**fld_e2167)(fld_e2167, 1);
  *(this + 2167) = 0;
  return result;
}



// 蓄力技能：vt+212 "HOLD"（81L）
// ------------------------------------------------------------
// 0x5BCFE0 sub_5BCFE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BCFE0(uint32_t *this, int nArg2, int pArg3)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2157; // ecx
  int v7; // eax
  int fld_e21572; // ecx
  int v9; // eax
  int fld_e21573; // ecx
  int v11; // eax
  int v12; // edx
  int fld_e1554; // ecx
  int v14; // edx
  int v15; // eax
  uint32_t *fld_e28; // edi
  float v18; // [esp+Ch] [ebp-Ch] BYREF
  float v19; // [esp+10h] [ebp-8h] BYREF
  float v20; // [esp+14h] [ebp-4h] BYREF

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg3 + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
    || (*(this + 2157) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2157) = 0;
  }
  fld_e2157 = *(this + 2157);
  if ( fld_e2157 != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2157 + 120))(fld_e2157);
    fld_e21572 = *(this + 2157);
    *(this + 2159) = v7;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21572 + 124))(fld_e21572);
    fld_e21573 = *(this + 2157);
    *(this + 2160) = v9;
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21573 + 128))(fld_e21573);
    v12 = *this;
    *(this + 2161) = v11;
    (*(void (/*thiscall*/ **)(uint32_t *, float *, float *, float *))(v12 + 1312))(this, &v18, &v19, &v20);
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 112))(
      this,
      (uint64_t)v18 >> 32,
      (uint64_t)v18,
      (uint64_t)v19,
      (uint64_t)v20);
  }
  fld_e1554 = *(this + 1554);
  v14 = *this;
  v15 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
  *(this + 2158) = v15;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v14 + 196))(this, *(uint32_t *)(fld_e1554 + 4 * (v15 != 1 ? 4 : 0)));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152 * (*(this + 2158) != 1));
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
}



// ============================================================
// 【分区 9】幽灵 & 魅魔（Wraith / Spectress）（0x5BD1B0-0x5BE7C0）
// 证据：WRAITH_ATK + R_WRAITH_DMG/DIE/R_WRAITH、WRAITH_KISS 吻杀（0x5BD3C0/0x5BD8F0,
//       后者读 +568 最后受击时刻）、R_WRAITH_KISS、Monster/Wraith/{WraithAni,WraithSpectressAni}/
//       {Die,KissWind,KissCircle}.ani、Particle/{KissHeart,Bat}.ptl

// 幽灵语音装载：WRAITH_ATK + R_WRAITH_DMG/DIE/R_WRAITH 四件套 +
//   Monster/Wraith/WraithAni/Die.ani 死亡特效（this+8628..8648 相位）
// ------------------------------------------------------------
// 0x5BD1B0 sub_5BD1B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD1B0(int this)
{
  uint32_t *pThis_21BC; // ecx
  int result; // eax

  *(uint32_t *)(this + 6792) = 3;
  *(uint32_t *)(this + 6796) = 3;
  *(uint32_t *)(this + 6804) = 6;
  *(uint32_t *)(this + 6808) = 6;
  *(uint32_t *)(this + 6800) = 5;
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8632) = -1;
  pThis_21BC = (uint32_t *)(this + 8636);
  *pThis_21BC = 0;
  pThis_21BC[1] = 0;
  pThis_21BC[2] = 0;
  sub_4015C0("WRAITH_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_WRAITH", 8u);  // 【std::string构造赋值】
  result = sub_4015C0("Monster/Wraith/WraithAni/Die.ani", 0x20u);  // 【std::string构造赋值】
  *(uint8_t *)(this + 8648) = 0;
  return result;
}



// 女妖死亡特效：Monster/Wraith/WraithSpectressAni/Die.ani（this+8648/8700 相位）
// ------------------------------------------------------------
// 0x5BD270 sub_5BD270
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD270(uint8_t *this)
{
  *(this + 8700) = 0;
  *(this + 8648) = 1;
  return sub_4015C0("Monster/Wraith/WraithSpectressAni/Die.ani", 0x29u);  // 【std::string构造赋值】
}



// AI 相位辅助（55L）
// ------------------------------------------------------------
// 0x5BD2A0 sub_5BD2A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD2A0(uint32_t *this)
{
  uint32_t *pMem; // eax
  int pObj; // esi
  uint32_t *v4; // eax
  uint32_t *pMem2; // eax
  uint32_t *v6; // eax
  void *pMem3; // eax

  pMem = operator new(0x7Cu);
  pObj = 0;
  if ( pMem != nullptr )
    v4 = sub_4B3DF0(pMem, 7, 1, 1101004800, 15000, 0);
  else
    v4 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v4 + 56))(
    v4,
    *(this + 2157),
    *(this + 2157),
    0,
    0,
    0,
    -1);
  pMem2 = operator new(0x7Cu);
  if ( pMem2 != nullptr )
    v6 = sub_4B3DF0(pMem2, 8, 1, 1101004800, 15000, 0);
  else
    v6 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v6 + 56))(
    v6,
    *(this + 2157),
    *(this + 2157),
    0,
    0,
    0,
    -1);
  pMem3 = operator new(0x64u);
  if ( pMem3 != nullptr )
    pObj = sub_51A7D0(pMem3);
  *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 40) = 15000;
  return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
           pObj,
           *(this + 2157),
           *(this + 2157),
           0,
           0,
           0,
           -1);
}



// 吻杀技能：WRAITH_KISS 播报（145L；sub_431230 打包 + RTTI cast 目标锁定）
// ------------------------------------------------------------
// 0x5BD3C0 sub_5BD3C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD3C0(int **this, int *Block, int nArg3, int nArg4)
{
  int result; // eax
  int pObj; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int fld_e2157; // edi
  uint8_t *pMem; // eax
  uint8_t *v12; // eax
  int v13; // edx
  int *fld_e21572; // ecx
  int v15; // ebx
  int v16; // eax
  int v17; // edi
  int fld_e21573; // ebx
  int v19; // eax
  int pObj2; // eax
  int v21; // [esp+10h] [ebp-38h]
  void *pBuf[4]; // [esp+2Ch] [ebp-1Ch] BYREF
  int v23; // [esp+44h] [ebp-4h]

  if ( (uint8_t)nArg4 == 0
    && ((int (/*thiscall*/ *)(int **))(*this)[210])(this) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *, int))(*Block + 40))(Block, 17);
      if ( (uint8_t)result != 0 )
      {
        pObj = __RTDynamicCast(
               (int)Block,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
        nArg4 = pObj;
        if ( pObj != 0
          && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 948))(pObj) != 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 840))(nArg4) == 0
          && ((int (/*thiscall*/ *)(int **))(*this)[142])(this) != 14 )
        {
          memset(&pBuf[1], 0, 12);
          v23 = 0;
          nArg4 = (*(int (/*thiscall*/ **)(int *))(*Block + 48))(Block);
          sub_431230((int)pBuf, &nArg4);
          nArg4 = (*(int (/*thiscall*/ **)(int *))(*Block + 52))(Block);
          sub_431230((int)pBuf, &nArg4);
          nArg4 = sub_41A5E0((unsigned int)(this + 1757));
          sub_431230((int)pBuf, &nArg4);
          ((void (/*thiscall*/ *)(int **, int, void **, uint32_t, uint32_t))(*this)[140])(this, 14, pBuf, 0, 0);
          v23 = -1;
          sub_5E5260(pBuf);
        }
        v7 = *Block;
        v8 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
        v9 = sub_432E50(v8);
        return (*(int (/*thiscall*/ **)(int *, int))(v7 + 144))(Block, v9);
      }
    }
  }
  else if ( ((int (/*thiscall*/ *)(int **))(*this)[210])(this) == 14 && *(this + 2157) != nullptr )
  {
    ((void (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "WRAITH_KISS", -1, 0, 0);
    result = (int)*(this + 2158);
    if ( result == 1 )
    {
      fld_e2157 = (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(this + 2157) + 740))(*(this + 2157)) * 0.1);
      nArg4 = fld_e2157;
      pMem = operator new(0x80u);
      v23 = 1;
      if ( pMem != nullptr )
      {
        *(float *)&v21 = (float)nArg4;
        v12 = sub_4D6810(pMem, v21, 100, 1, 1);
      }
      else
      {
        v12 = nullptr;
      }
      v13 = *(uint32_t *)v12;
      v23 = -1;
      (*(void (/*thiscall*/ **)(uint8_t *, int **, int **, uint32_t, uint32_t, uint32_t, int))(v13 + 56))(
        v12,
        this,
        this,
        0,
        0,
        0,
        -1);
      fld_e21572 = *(this + 2157);
      v15 = *fld_e21572;
      v16 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*fld_e21572 + 736))(fld_e21572, 1, 0);
      return (*(int (/*thiscall*/ **)(uint32_t, int))(v15 + 728))(*(this + 2157), v16 - fld_e2157);
    }
    else if ( result == 2 )
    {
      result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
      if ( (uint8_t)result != 0 )
      {
        nArg4 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2157) + 756))(*(this + 2157));
        v17 = (uint64_t)((double)nArg4 * 0.15000001);
        fld_e21573 = **(this + 2157);
        v19 = (*(int (/*stdcall*/ **)(int))(fld_e21573 + 752))(1);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e21573 + 744))(*(this + 2157), v19 - v17);
      }
    }
  }
  else
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[210])(this);
    if ( result == 8 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(int *, int))(*Block + 40))(Block, 17);
        if ( (uint8_t)result != 0 )
        {
          pObj2 = __RTDynamicCast(
                  (int)Block,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDActiveObject `RTTI Type Descriptor',
                  0);
          return (*(int (/*thiscall*/ **)(int, int, int, int, int **, uint32_t))(*(uint32_t *)pObj2 + 760))(
                   pObj2,
                   11,
                   1097859072,
                   5,
                   this,
                   0);
        }
      }
    }
  }
  return result;
}


// 参数打包 AI（sub_431230, 83L）
// ------------------------------------------------------------
// 0x5BD710 sub_5BD710
// ------------------------------------------------------------
void /*usercall*/ sub_5BD710(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int pObj; // ecx
  int *v4; // edi
  int v5; // edx
  int v6; // eax
  int v7; // eax
  char v8; // al
  int *v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // eax
  uint8_t v13[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  uint32_t v17[4]; // [esp+18h] [ebp-10h] BYREF

  pObj = pArg1[2157];
  if ( pObj != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 604))(pObj, 1, nArg2);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 612))(pArg1[2157], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 136))(
           pArg1[2157],
           pArg1[2159],
           pArg1[2160],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2157] + 112))(pArg1[2157], pArg1[2159], pArg1[2160]);
    }
    else
    {
      v4 = (int *)pArg1[2157];
      v5 = *v4;
      v17[0] = v4;
      v17[0] = *pArg1;
      v6 = (*(int (/*thiscall*/ **)(int *, int, int, int))(v5 + 124))(v4, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int *, int))(*v4 + 120))(v4, v6);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t *, int))(v17[0] + 140))(pArg1, pArg1 + 2159, pArg1 + 2160, v7);
      v9 = (int *)pArg1[2157];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v9 + 112))(v9, pArg1[2159], pArg1[2160]);
      }
      else
      {
        v10 = *v9;
        v11 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 124))(pArg1, pArg1[2161]);
        v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v11);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v10 + 112))(pArg1[2157], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 308))(pArg1[2157]) != 0 )
    {
      Block = nullptr;
      v15 = 0;
      v16 = 0;
      v17[3] = 0;
      v17[0] = 4;
      sub_431230((int)v13, v17);
      v17[0] = 0;
      sub_431230((int)v13, v17);
      v17[0] = 1;
      sub_431230((int)v13, v17);
      v17[0] = 100;
      sub_431230((int)v13, v17);
      v17[0] = 100;
      sub_431230((int)v13, v17);
      (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int, uint32_t))(*(uint32_t *)pArg1[2157] + 560))(pArg1[2157], 4, v13, 2, 0);
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2157] + 564))(pArg1[2157]);
      if ( Block != nullptr )
        j__free(Block);
    }
    pArg1[2157] = 0;
  }
}



// 吻杀执行（176L）：WRAITH_KISS + RTTI cast；读 this+568 最后受击时刻
//   （研究 20 §1.2 sub_4E48D0 记录字段 —— 吻杀与受击历史的联动【推断】）
// ------------------------------------------------------------
// 0x5BD8F0 sub_5BD8F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BD8F0(int *this, int nArg2, int nArg3, int nArg4)
{
  int result; // eax
  int pObj2; // eax
  int pObj; // ebx
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  bool fld_e2157; // zf
  int fld_e21572; // eax
  int v14; // edi
  int *v15; // eax
  int v16; // edx
  int *fld_e21573; // ecx
  int v18; // ebx
  int v19; // eax
  char fld_e21574; // al
  int *fld_e21575; // ecx
  int v22; // edi
  int fld_e21576; // ebx
  int v24; // eax
  float v25; // [esp+14h] [ebp-38h]
  void *pBuf[4]; // [esp+30h] [ebp-1Ch] BYREF
  int v27; // [esp+48h] [ebp-4h]

  if ( (uint8_t)nArg4 == 0
    && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 340))(nArg2);
        if ( *(uint32_t *)result != 410 )
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 340))(nArg2);
          if ( *(uint32_t *)result != 411 )
          {
            pObj2 = __RTDynamicCast(
                   nArg2,
                   0,
                   &IRDCollisionObject `RTTI Type Descriptor',
                   &IRDActiveObject `RTTI Type Descriptor',
                   0);
            pObj = pObj2;
            if ( pObj2 != 0
              && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 948))(pObj2) != 0
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 0
              && (*(int (/*thiscall*/ **)(int *))(*this + 568))(this) != 14 )
            {
              memset(&pBuf[1], 0, 12);
              v8 = *(uint32_t *)nArg2;
              v27 = 0;
              nArg4 = (*(int (/*thiscall*/ **)(int))(v8 + 48))(nArg2);
              sub_431230((int)pBuf, &nArg4);
              nArg4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);
              sub_431230((int)pBuf, &nArg4);
              nArg4 = sub_41A5E0((unsigned int)(this + 1757));
              sub_431230((int)pBuf, &nArg4);
              (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);
              v27 = -1;
              sub_5E5260(pBuf);
            }
            v9 = *(uint32_t *)nArg2;
            v10 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
            v11 = sub_432E50(v10);
            return (*(int (/*thiscall*/ **)(int, int))(v9 + 144))(nArg2, v11);
          }
        }
      }
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14 && *(this + 2157) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WRAITH_KISS", -1, 0, 0);
    result = *(this + 2158);
    if ( result == 1 )
    {
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
      if ( (uint8_t)result == 0 )
        return result;
      fld_e2157 = (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273) == 0;
      fld_e21572 = *(uint32_t *)*(this + 2157);
      if ( !fld_e2157 )
      {
        v14 = (uint64_t)((double)(*(int (**)(void))(fld_e21572 + 740))() * 0.050000001);
        nArg4 = v14;
        v27 = 1;
        if ( operator new(0x80u) != nullptr )
        {
          v25 = (float)nArg4;
          v15 = (int *)sub_4D6810(LODWORD(v25), 100, 1, 1);
        }
        else
        {
          v15 = nullptr;
        }
        v16 = *v15;
        v27 = -1;
        (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t, int))(v16 + 56))(
          v15,
          this,
          this,
          0,
          0,
          0,
          -1);
        fld_e21573 = (int *)*(this + 2157);
        v18 = *fld_e21573;
        v19 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*fld_e21573 + 736))(fld_e21573, 1, 0);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(v18 + 728))(*(this + 2157), v19 - v14);
      }
    }
    else
    {
      if ( result != 2 )
        return result;
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
      if ( (uint8_t)result == 0 )
        return result;
      fld_e21574 = (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2157) + 40))(*(this + 2157), 273);
      fld_e21575 = (int *)*(this + 2157);
      if ( fld_e21574 != 0 )
      {
        nArg4 = (*(int (/*thiscall*/ **)(int *))(*fld_e21575 + 756))(fld_e21575);
        v22 = (uint64_t)((double)nArg4 * 0.050000001);
        fld_e21576 = *(uint32_t *)*(this + 2157);
        v24 = (*(int (/*stdcall*/ **)(int))(fld_e21576 + 752))(1);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e21576 + 744))(*(this + 2157), v24 - v22);
      }
      fld_e21572 = *fld_e21575;
    }
    result = (*(int (/*stdcall*/ **)(int))(fld_e21572 + 40))(529);
    if ( (uint8_t)result != 0 )
      return sub_5BD2A0(this);
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( result == 8 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
        if ( (uint8_t)result != 0 )
        {
          result = __RTDynamicCast(
                     nArg2,
                     0,
                     &IRDCollisionObject `RTTI Type Descriptor',
                     &IRDActiveObject `RTTI Type Descriptor',
                     0);
          if ( result != 0 )
            return (*(int (/*thiscall*/ **)(int, int, int, int, int *, uint32_t))(*(uint32_t *)result + 760))(
                     result,
                     4,
                     1097859072,
                     5,
                     this,
                     0);
        }
      }
    }
  }
  return result;
}


// 蓄力技能：vt+212 "HOLD"（102L）
// ------------------------------------------------------------
// 0x5BDCD0 sub_5BDCD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BDCD0(uint32_t *this, int nArg2, int pArg3)
{
  int pObj2; // eax
  int pObj; // ebx
  uint32_t *pThis_86D; // edi
  uint32_t *fld_e2164; // eax
  int v8; // eax
  int pObj3; // ecx
  int v10; // eax
  int pObj4; // edi
  int fld_e1554; // ecx
  int v13; // edx
  int v14; // eax
  uint32_t *fld_e28; // edi
  float v17; // [esp+Ch] [ebp-Ch] BYREF
  float v18; // [esp+10h] [ebp-8h] BYREF
  float v19; // [esp+14h] [ebp-4h] BYREF

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg3 + 4), *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0 || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0 )
  {
    pThis_86D = this + 2157;
LABEL_14:
    *pThis_86D = 0;
    goto LABEL_15;
  }
  pThis_86D = this + 2157;
  *(this + 2157) = pObj;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0 )
    *pThis_86D = 0;
  if ( *pThis_86D != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*pThis_86D + 40))(*pThis_86D, 529) != 0
    && *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 340))(*pThis_86D) != 410
    && *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 340))(*pThis_86D) != 411 )
  {
    fld_e2164 = (uint32_t *)*(this + 2164);
    if ( fld_e2164 == (uint32_t *)*(this + 2165) )
    {
LABEL_12:
      sub_4E7BA0(this + 2157);
      goto LABEL_15;
    }
    while ( *fld_e2164 != *pThis_86D )
    {
      if ( ++fld_e2164 == (uint32_t *)*(this + 2165) )
        goto LABEL_12;
    }
    goto LABEL_14;
  }
LABEL_15:
  if ( *pThis_86D != 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pThis_86D + 120))(*pThis_86D);
    pObj3 = *pThis_86D;
    *(this + 2159) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);
    pObj4 = *pThis_86D;
    *(this + 2160) = v10;
    *(this + 2161) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 128))(pObj4);
    (*(void (/*thiscall*/ **)(uint32_t *, float *, float *, float *))(*this + 1312))(this, &v17, &v18, &v19);
    (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 112))(
      this,
      (uint64_t)v17 >> 32,
      (uint64_t)v17,
      (uint64_t)v18,
      (uint64_t)v19);
  }
  fld_e1554 = *(this + 1554);
  v13 = *this;
  v14 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
  *(this + 2158) = v14;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v13 + 196))(this, *(uint32_t *)(fld_e1554 + 4 * (v14 != 1 ? 4 : 0)));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 344))(this, *(this + 139) + 152 * (*(this + 2158) != 1));
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BDF10 sub_5BDF10
// ------------------------------------------------------------
int /*userpurge*/ sub_5BDF10@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, uint32_t *uArg3)
{
  if ( uArg3 == (uint32_t *)pArg1[2157] )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 14 )
      sub_5BD710(pArg1, nArg2);
    pArg1[2157] = 0;
  }
  if ( uArg3 == pArg1 && pArg1[2157] != 0 )
  {
    sub_5BD710(pArg1, nArg2);
    pArg1[2157] = 0;
  }
  return sub_4D9170(uArg3);
}



// 爱心技能：引用 Particle/KissHeart.ptl
// ------------------------------------------------------------
// 0x5BDF80 sub_5BDF80
// ------------------------------------------------------------
int /*thiscall*/ sub_5BDF80(uint32_t *this)
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/KissHeart.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/KissHeart.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 2167) = result;
  return result;
}



// 吻杀语音/特效：R_WRAITH_KISS 播报（121L；sub_431860）
// ------------------------------------------------------------
// 0x5BE010 sub_5BE010
// ------------------------------------------------------------
void /*userpurge*/ sub_5BE010(int *pDwArg1@<ecx>, double fArg2@<st0>, int ArgList, int pArg4, int nArg5, int nArg6)
{
  int v7; // edi
  int pArg42; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int pObj; // eax
  int v15; // ebx
  int pObj2; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  uint32_t *v21; // eax
  int v22; // ebx
  int v23; // edx
  char *v24; // eax
  char *v25; // edi
  int v26; // ebx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // ebx
  int v31; // eax
  float ArgLista; // [esp+24h] [ebp+8h]

  if ( pDwArg1[1639] == 14 )
    sub_5BD710();
  v7 = ArgList;
  pArg42 = pArg4;
  switch ( ArgList )
  {
    case 14:
      (*(void (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 1316))(pDwArg1, 14, pArg4);
      break;
    case 15:
      v9 = *pDwArg1;
      v10 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 124))(pDwArg1, 0);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v10);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v9 + 136))(pDwArg1, v11) == 0
        || (v12 = *pDwArg1,
            v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1),
            (*(uint8_t (/*thiscall*/ **)(int *, int))(v12 + 132))(pDwArg1, v13) == 0) )
      {
        pObj = pDwArg1[2157];
        if ( pObj != 0 )
        {
          v15 = *pDwArg1;
          pObj2 = pDwArg1[2157];
          v17 = (*(int (**)(void))(*(uint32_t *)pObj + 128))();
          v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 124))(pObj2, v17);
          v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v18);
          (*(void (/*thiscall*/ **)(int *, int))(v15 + 112))(pDwArg1, v19);
          pArg42 = pArg4;
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[1554] + 4));
      v7 = 15;
      break;
    case 8:
      v20 = **(uint32_t **)(pArg4 + 4);
      if ( v20 != 0 && v20 != 3 )
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "R_WRAITH_KISS", -1, 0, 0);
        ArgLista = (float)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1);
        fArg2 = (double)(*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1) * 0.5;
        v21 = *(uint32_t **)(pArg4 + 4);
        if ( fArg2 <= ArgLista )
          *v21 = 2;
        else
          *v21 = 1;
      }
      break;
    default:
      break;
  }
  sub_4E33D0((int)pDwArg1, pArg42, fArg2, v7, pArg42, *(float *)&nArg5, *(float *)&nArg6);
  if ( v7 == 5 )
  {
    v22 = 0;
    if ( sub_42FCB0(228) != 0 )
    {
      if ( (unsigned int)pDwArg1[2156] < 0x10 )
        LOBYTE(v23) = (uint8_t)pDwArg1 - 100;
      else
        v23 = pDwArg1[2151];
      v22 = sub_431860(v23, 1);
    }
    if ( v22 != 0 )
    {
      v24 = (char *)sub_44B6C0(284);
      v25 = v24;
      if ( v24 != nullptr )
      {
        sub_44E0D0(v24, v22, 1);
        *(uint32_t *)v25 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v25 = nullptr;
      }
      sub_45FE80(pDwArg1[29], (int)v25, 2, 0, (int)v25, (int)pDwArg1, 0);
      v26 = *(uint32_t *)v25;
      v27 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
      v28 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v27);
      v29 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v28);
      (*(void (/*thiscall*/ **)(char *, int))(v26 + 112))(v25, v29);
      v30 = *(uint32_t *)v25;
      v31 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
      (*(void (/*thiscall*/ **)(char *, int))(v30 + 144))(v25, v31);
    }
  }
}


// 吻杀风特效：Monster/Wraith/WraithSpectressAni/KissWind.ani（60L）
// ------------------------------------------------------------
// 0x5BE250 sub_5BE250
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE250(int *this)
{
  int result; // eax
  int v3; // ebx
  char *v4; // eax
  char *v5; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int fld_e2157; // [esp+8h] [ebp-10h]

  result = *(this + 2157);
  if ( result != 0 )
  {
    result = sub_42FCB0(228);
    if ( result != 0 )
    {
      result = sub_431860((char)"Monster/Wraith/WraithSpectressAni/KissWind.ani", 1);
      v3 = result;
    }
    else
    {
      v3 = 0;
    }
    if ( v3 != 0 )
    {
      v4 = (char *)sub_44B6C0(284);
      v5 = v4;
      if ( v4 != nullptr )
      {
        sub_44E0D0(v4, v3, 1);
        *(uint32_t *)v5 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v5 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v5, 2, 0, (int)v5, (int)this, 0);
      v6 = *(uint32_t *)v5;
      fld_e2157 = *(this + 2157);
      v7 = (*(int (**)(void))(*(uint32_t *)fld_e2157 + 128))();
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2157 + 124))(fld_e2157, v7);
      v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2157 + 120))(fld_e2157, v8);
      (*(void (/*thiscall*/ **)(char *, int))(v6 + 112))(v5, v9);
      v10 = *(uint32_t *)v5;
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      return (*(int (/*thiscall*/ **)(char *, int))(v10 + 144))(v5, v11);
    }
  }
  return result;
}



// 吻杀环特效：Monster/Wraith/WraithSpectressAni/KissCircle.ani（57L）
// ------------------------------------------------------------
// 0x5BE360 sub_5BE360
// ------------------------------------------------------------
int /*usercall*/ sub_5BE360@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>)
{
  int result; // eax
  int v4; // ebx
  char *v5; // eax
  char *v6; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v13; // [esp+8h] [ebp-10h]

  result = sub_42FCB0(228);
  if ( result != 0 )
  {
    result = sub_431860((char)"Monster/Wraith/WraithSpectressAni/KissCircle.ani", 1);
    v4 = result;
  }
  else
  {
    v4 = 0;
  }
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
    sub_45FE80(pDwArg1[29], (int)v6, 2, 0, (int)v6, (int)pDwArg1, 0);
    if ( (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, nArg2) == 1 )
      v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) + 30;
    else
      v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) - 30;
    v8 = *(uint32_t *)v6;
    v13 = v7;
    v9 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, 80);
    (*(void (/*thiscall*/ **)(char *, int, int))(v8 + 112))(v6, v13, v9);
    v10 = *(uint32_t *)v6;
    v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
    return (*(int (/*thiscall*/ **)(char *, int))(v10 + 144))(v6, v11);
  }
  return result;
}



// 硬直/相位字段（this+208/8649/8650/8700/8701）
// ------------------------------------------------------------
// 0x5BE470 sub_5BE470
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE470(uint8_t *this, int ArgList, int pArg3, int nArg4, int nArg5)
{
  int pThis_348; // eax
  int v7; // edi
  int pThis_154; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int pThis_612; // eax
  int v12; // edx
  int pThis_86D; // ecx
  bool v14; // al

  pThis_348 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this);
  if ( pThis_348 == 15 )
  {
    if ( *(this + 8701) != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)this + 944))(this, 1, 10000);
    v7 = *(uint32_t *)this;
    pThis_154 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 340))(this);
    pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 124))(this, *(uint32_t *)(pThis_154 + 40));
    pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, pThis_7C);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v7 + 112))(this, pThis_78);
  }
  else if ( pThis_348 == 8 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*((uint32_t *)this + 1554) + 20));
  }
  if ( ArgList == 8 )
  {
    if ( **(uint32_t **)(pArg3 + 4) == 3 )
    {
      pThis_612 = *((uint32_t *)this + 1554);
      v12 = *(uint32_t *)this;
      *(this + 8700) = 1;
      (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v12 + 204))(
        this,
        1,
        *(uint32_t *)(pThis_612 + 20),
        0,
        0,
        0,
        0);
    }
    *(this + 8649) = 1;
    *(this + 8650) = 1;
  }
  else if ( ArgList == 15 )
  {
    pThis_86D = *((uint32_t *)this + 2157);
    v14 = pThis_86D != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_86D + 40))(pThis_86D, 273) != 0;
    *(this + 8701) = v14;
  }
  return sub_5BE010(this, pArg3, ArgList, *(float *)&pArg3, nArg4, nArg5);
}



// 蝙蝠群：引用 Particle/Bat.ptl（97L；魅魔召蝙蝠演出）
// ------------------------------------------------------------
// 0x5BE570 sub_5BE570
// ------------------------------------------------------------
int /*usercall*/ sub_5BE570@<eax>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int (***pArg3)(void)@<edi>)
{
  char v4; // al
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int pObj; // ecx
  int v9; // ebx
  int (**v10)(void); // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  void *v14; // ecx
  int nArg22; // [esp-4h] [ebp-2Ch]
  void *v17[5]; // [esp+8h] [ebp-20h] BYREF
  int v18; // [esp+24h] [ebp-4h]

  v4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 940))(pArg1);
  v5 = *(uint32_t *)pArg1;
  pArg1[8524] = v4 == 0;
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(v5 + 840))(pArg1) == 8 )
  {
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 3
      && pArg1[8700] == 1
      && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 4 )
    {
      v6 = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)pArg1 + 588))(pArg1, "Particle/Bat.ptl");
      pArg3 = *(int (****)(void))pArg1;
      v7 = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 152))(
             pArg1,
             v6,
             0,
             0,
             0,
             0,
             4,
             0,
             0,
             0);
      ((void (/*thiscall*/ *)(uint8_t *, int, int))pArg3[145])(pArg1, 30300, v7);
      pArg1[8700] = 0;
    }
  }
  else if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 840))(pArg1) == 14
         && ((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 2
          || (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) == 1) )
  {
    pObj = *((uint32_t *)pArg1 + 2157);
    nArg22 = nArg2;
    if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
    {
      if ( pArg1[8649] != 0 && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 2 )
      {
        sub_5BE360((int *)pArg1, (int)pArg3);
        pArg1[8649] = 0;
      }
      if ( pArg1[8650] != 0 && *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3 )
      {
        sub_5BE250((int *)pArg1);
        pArg1[8650] = 0;
        pArg1[8685] = 0;
        pArg1[8686] = 0;
        sub_698F90((int)(pArg1 + 8672), 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      if ( *(int *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 3
        && (uint8_t)sub_41C6E0(pArg1 + 8672) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)pArg1 + 2167) + 12))(*((uint32_t *)pArg1 + 2167), 0);
        v9 = **((uint32_t **)pArg1 + 2167);
        pArg3 = *((int (****)(void))pArg1 + 2157);
        v10 = *pArg3;
        v17[4] = pArg3;
        v11 = v10[32]();
        v12 = ((int (/*thiscall*/ *)(int (***)(void), int))(*pArg3)[31])(pArg3, v11 + 32);
        v13 = ((int (/*thiscall*/ *)(int (***)(void), int))(*pArg3)[30])(pArg3, v12);
        (*(void (/*thiscall*/ **)(uint32_t, int))(v9 + 40))(*((uint32_t *)pArg1 + 2167), v13);
        (*(void (/*thiscall*/ **)(uint32_t, void **))(**((uint32_t **)pArg1 + 2167) + 92))(*((uint32_t *)pArg1 + 2167), v17);
        v14 = *((void **)pArg1 + 29);
        v18 = 0;
        sub_4600B0(v14, 2, 0, (int)v17);
        pArg1[8685] = 0;
        pArg1[8686] = 0;
        sub_698F90((int)(pArg1 + 8672), 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        v18 = -1;
        sub_5E5260(v17);
      }
    }
    nArg2 = nArg22;
  }
  return sub_5BCAB0(pArg1, nArg2, (int)pArg3);
}



// ============================================================
// 【分区 10】蜘蛛·毒网与弹幕（0x5BE7C0-0x5BFBC0）
// 证据：Particle/{Web,PoisonWeb,BossMissile1-4}.ptl、GAS_OUT 毒气、HOLD 蓄力

// 子类扩展字段复位（this+8600..8636）
// ------------------------------------------------------------
// 0x5BE7C0 sub_5BE7C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE7C0(int this)
{
  *(uint32_t *)(this + 6792) = 2;
  *(uint32_t *)(this + 6800) = 2;
  *(uint32_t *)(this + 6868) = 2;
  *(uint32_t *)(this + 6796) = 3;
  *(uint32_t *)(this + 6804) = 3;
  *(uint32_t *)(this + 6872) = 3;
  *(uint32_t *)(this + 6808) = 4;
  *(uint32_t *)(this + 6864) = 0;
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 7324) = 570;
  *(uint32_t *)(this + 8636) = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BE840 sub_5BE840
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE840(int *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_4;
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        nRand = rand();
        v4 = nRand % 100;
        result = nRand / 100;
        if ( v4 < 10 )
          goto LABEL_10;
      }
      else
      {
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_10:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BE910 sub_5BE910
// ------------------------------------------------------------
int /*thiscall*/ sub_5BE910(void *this, void *Block, int nArg3, int nArg4)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  if ( result != 14 )
    return sub_4D6030((int)this, Block, nArg3, nArg4);
  return result;
}



// AI 相位辅助（124L）
// ------------------------------------------------------------
// 0x5BE940 sub_5BE940
// ------------------------------------------------------------
int /*usercall*/ sub_5BE940@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pObj2; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int *v8; // edi
  int v9; // eax
  uint32_t *v10; // eax
  int *v11; // ecx
  int v12; // eax
  int v13; // edx
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int pObj; // ecx
  int v18; // ebx
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v23; // ebx
  int v24; // edi
  int v25; // eax
  int v26; // eax
  int v28; // [esp+4h] [ebp-64h]
  uint32_t v29[23]; // [esp+8h] [ebp-60h]
  int v30; // [esp+64h] [ebp-4h]

  pObj2 = pArg1[2152];
  if ( pObj2 != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 840))(pObj2) == 9 )
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0 )
      {
        v5 = pArg1[2154];
        v6 = pArg1[2153] + 1;
        pArg1[2153] = v6;
        if ( v6 >= v5 || (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 736))(pArg1[2152]) <= 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
        }
        else
        {
          v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
          sub_4926A0(v7);
        }
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 840))(pArg1[2152]) != 5
           && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 308))(pArg1[2152]) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2152] + 560))(pArg1[2152], 9, 0, 0, 0);
    }
    v29[0] = -15;
    v29[6] = -15;
    v28 = -10;
    v29[5] = -10;
    v29[8] = -19;
    v29[9] = -10;
    v29[14] = -19;
    v8 = (int *)pArg1[2152];
    v29[15] = 8;
    v29[16] = 10;
    v29[20] = 10;
    v29[21] = 8;
    v29[22] = 10;
    v9 = *v8;
    v29[1] = -6;
    v29[2] = -24;
    v29[3] = -4;
    v29[4] = -32;
    v29[7] = -14;
    v29[10] = -23;
    v29[11] = -8;
    v29[12] = -27;
    v29[13] = -14;
    v29[17] = 5;
    v29[18] = 13;
    v29[19] = 20;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, int))(v9 + 40))(v8, 273, nArg3, nArg2) != 0 )
    {
      v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v8 + 1032))(v8);
      v11 = (int *)pArg1[2152];
      v12 = 2 * (*v10 + 4 * pArg1[2159]);
      v13 = v29[v12];
      v14 = v29[v12 - 1];
      v15 = *v11;
      v30 = v13;
      v16 = (*(int (/*thiscall*/ **)(int *))(v15 + 152))(v11);
      pObj = pArg1[2152];
      if ( v16 != 0 )
      {
        v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        v18 = v30 + v19;
      }
      else
      {
        v18 = v14 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
      }
      v20 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 124))(pArg1[2152]) + 1;
      v21 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 128))(pArg1[2152]);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 112))(pArg1, v18, v20, v21 + 20);
    }
    else
    {
      v23 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 120))(pArg1[2152]);
      v24 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 124))(pArg1[2152]) + 1;
      v25 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2152] + 128))(pArg1[2152]);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*pArg1 + 112))(pArg1, v23, v24, v25 + 20);
    }
  }
  else
  {
    v26 = *pArg1;
    *((uint8_t *)pArg1 + 8600) = 1;
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(v26 + 560))(pArg1, 15, 0, 0, 0);
  }
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5BEB90 sub_5BEB90
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEB90(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int fld_e2152; // eax
  int fld_e21522; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v2 + 136))(this, v4) == 0
    || (v5 = *this,
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),
        (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v5 + 132))(this, v6) == 0) )
  {
    fld_e2152 = *(this + 2152);
    if ( fld_e2152 != 0 )
    {
      fld_e21522 = *(this + 2152);
      v9 = *this;
      v10 = (*(int (**)(void))(*(uint32_t *)fld_e2152 + 128))();
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522, v10 + 40);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21522 + 120))(fld_e21522, v11);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 112))(this, v12);
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 200, 200, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
  v13 = *this;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
  v15 = sub_432E50(v14);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(v13 + 896))(this, v15);
}



// AI 字段访问（this+8600/8608）
// ------------------------------------------------------------
// 0x5BEC80 sub_5BEC80
// ------------------------------------------------------------
void /*thiscall*/ sub_5BEC80(int this)
{
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8608) = -1;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BECA0 sub_5BECA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BECA0(uint32_t *this)
{
  *(this + 1698) = 2;
  *(this + 1699) = 3;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  *(this + 1716) = 0;
  *(this + 1717) = 2;
  *(this + 1718) = 3;
  *(this + 2153) = 0;
  return 3;
}



// 主状态门（this+200/8600/8608）
// ------------------------------------------------------------
// 0x5BECF0 sub_5BECF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BECF0(int this)
{
  int result; // eax

  sub_4E1780((uint32_t *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8
    && sub_41A5E0(this + 7028) == *(uint32_t *)(this + 8608)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0
    && *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 2
    && *(uint8_t *)(this + 8600) == 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1316))(this);
    *(uint8_t *)(this + 8600) = 1;
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( result == 6 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
    if ( *(uint8_t *)(result + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
               this,
               1,
               0,
               0,
               0,
               0,
               0);
    }
  }
  return result;
}



// 蛛网技能：引用 Particle/Web.ptl
// ------------------------------------------------------------
// 0x5BEDB0 sub_5BEDB0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEDB0(uint32_t *this)
{
  int v2; // edi
  int v3; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(
         this,
         "Particle/Web.ptl",
         0,
         60,
         0,
         10,
         4,
         0,
         0,
         0);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(v2 + 580))(this, *(this + 2151), 0, v3);
}



// AI 字段访问（this+8618）
// ------------------------------------------------------------
// 0x5BEDF0 sub_5BEDF0
// ------------------------------------------------------------
char /*thiscall*/ sub_5BEDF0(uint8_t *this, unsigned int uArg2, int nArg3, int nArg4)
{
  char result; // al
  int v6; // eax

  result = sub_495250(this, uArg2, nArg3, nArg4);
  if ( uArg2 != 2 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    if ( result != 0 && *(this + 8618) == 1 )
    {
      v6 = *(uint32_t *)this;
      *(this + 8618) = 0;
      result = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t))(v6 + 560))(this, 0, 0, 0, 0);
      *(this + 6573) = 0;
      *(this + 6574) = 0;
    }
  }
  return result;
}



// 毒网技能：引用 Particle/PoisonWeb.ptl
// ------------------------------------------------------------
// 0x5BEE60 sub_5BEE60
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEE60(uint32_t *this)
{
  int v2; // edi
  int v3; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(
         this,
         "Particle/PoisonWeb.ptl",
         0,
         60,
         0,
         10,
         4,
         0,
         0,
         0);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(v2 + 580))(this, *(this + 2151), 0, v3);
}



// 毒气技能：GAS_OUT 播报（this+8616 相位）
// ------------------------------------------------------------
// 0x5BEEA0 sub_5BEEA0
// ------------------------------------------------------------
char /*thiscall*/ sub_5BEEA0(uint32_t *this)
{
  int pThis_6DD; // eax
  int v3; // edi
  int v4; // eax

  sub_5BECF0((int)this);
  pThis_6DD = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( pThis_6DD == 8 )
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
    if ( pThis_6DD == 0 && *(int *)(*(this + 30) + 148) >= 2 )
    {
      LOBYTE(pThis_6DD) = *((uint8_t *)this + 8616);
      if ( (uint8_t)pThis_6DD == 0 )
      {
        LOBYTE(pThis_6DD) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
        if ( (uint8_t)pThis_6DD != 0 )
        {
          v3 = *this;
          *((uint8_t *)this + 8616) = 1;
          v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v3 + 152))(
                 this,
                 0,
                 10,
                 4,
                 0,
                 0,
                 0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int))(v3 + 580))(
            this,
            48003,
            *(this + 2155),
            0,
            0,
            v4 != 1 ? 0 : 20);
          LOBYTE(pThis_6DD) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                         this,
                         "GAS_OUT",
                         -1,
                         0,
                         0);
        }
      }
    }
  }
  return pThis_6DD;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BEF50 sub_5BEF50
// ------------------------------------------------------------
int /*thiscall*/ sub_5BEF50(int *this, int nArg2, int nArg3, int nArg4)
{
  int v6; // ebx
  int v7; // edx
  double v8; // st7
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // ebx
  int v13; // eax
  int nArg42; // [esp-8h] [ebp-2Ch]
  int v16; // [esp-4h] [ebp-28h]
  float v17; // [esp+Ch] [ebp-18h] BYREF
  float v18; // [esp+10h] [ebp-14h]
  float v19; // [esp+14h] [ebp-10h]
  int v20; // [esp+18h] [ebp-Ch]
  int v21; // [esp+1Ch] [ebp-8h]
  int v22; // [esp+20h] [ebp-4h]
  int v23; // [esp+2Ch] [ebp+8h]

  v6 = sub_4DB480(nArg2, nArg3, nArg4);
  v23 = v6;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) == 0
    || rand() % 100 >= 50 )
  {
    return v6;
  }
  v7 = *this;
  nArg4 = 0;
  v17 = 0.0;
  v18 = 0.0;
  v19 = 0.0;
  v20 = 0;
  v21 = 0;
  v22 = 0;
  v8 = (double)(*(int (/*thiscall*/ **)(int *))(v7 + 120))(this);
  v9 = *this;
  v17 = v8;
  v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 124))(this);
  v11 = *this;
  v18 = (float)v10;
  v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 192))(this) / 2;
  v19 = (float)((*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + v12);
  v16 = sub_605840(&nArg4, nArg2, &v17, 1);
  nArg42 = nArg4;
  v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  sub_4E4A50(nArg2, 42005, 100, 0, 0, 0, v13, 0, nArg42, v16);
  return v23;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF080 sub_5BF080
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF080(void *this, void *pArg2)
{
  if ( pArg2 == this )
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 9);
  return sub_4D9170(pArg2);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF0B0 sub_5BF0B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF0B0(void *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  if ( result == 0 )
    return sub_5D8DE0(this);
  return result;
}



// 蛛网收束：引用 Particle/Web.ptl（80L；this+204/+208 硬直联动）
// ------------------------------------------------------------
// 0x5BF0D0 sub_5BF0D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF0D0(int *this)
{
  int result; // eax
  int v3; // edi
  uint32_t *pThis_88C; // ebx
  int fld_e2191; // eax
  int *pThis_88C2; // ebx
  uint32_t *v7; // edi
  int v8; // ebx
  double v9; // [esp+Ch] [ebp-10h]
  int *i; // [esp+18h] [ebp-4h]

  result = sub_4D54E0();
  if ( *(this + 1639) == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 3 )
    {
      result = *(this + 30);
      if ( result != 0 )
      {
        result = *(uint32_t *)(result + 148);
        if ( result > *(this + 2191) && result >= 2 )
        {
          *(this + 2191) = result;
          v3 = 0;
          pThis_88C = this + 2188;
          do
          {
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *pThis_88C);
            fld_e2191 = 2 * (*(this + 2191) - 2 + v3 + 2 * (*(this + 2191) - 2));
            result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
                       this,
                       1,
                       *pThis_88C,
                       dword_72FD88[fld_e2191],
                       dword_72FD8C[fld_e2191],
                       0,
                       0);
            ++v3;
            ++pThis_88C;
          }
          while ( v3 < 3 );
        }
      }
    }
    if ( *(this + 1639) == 8 )
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 3 )
        goto LABEL_11;
    }
  }
  if ( *(this + 1639) == 18 )
  {
LABEL_11:
    pThis_88C2 = this + 2188;
    v7 = &unk_72FDEC;
    for ( i = this + 2188; ; pThis_88C2 = i )
    {
      v9 = atan2((double)(int)*(v7 - 1) / (double)(*v7 + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this)), 1.0);
      result = (int)sub_4938F0(*pThis_88C2);
      v8 = *pThis_88C2;
      if ( *(uint32_t *)(v8 + 148) == -1 )
        result = (int)sub_4938F0(v8);
      *(float *)(v8 + 88) = v9;
      v7 += 2;
      ++i;
      if ( (int)v7 >= (int)"icle/Web.ptl" )
        break;
    }
  }
  return result;
}



// 主状态门（this+200/8617）
// ------------------------------------------------------------
// 0x5BF210 sub_5BF210
// ------------------------------------------------------------
char /*thiscall*/ sub_5BF210(uint8_t *this)
{
  int pThis_C8; // eax

  LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)pThis_C8 != 0 )
  {
    pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
    if ( *(int *)(pThis_C8 + 148) >= 2 )
    {
      LOBYTE(pThis_C8) = *(this + 8617);
      if ( (uint8_t)pThis_C8 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
          this,
          30100,
          0,
          *((uint32_t *)this + 2155),
          0,
          60,
          0,
          30,
          4,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
          this,
          30100,
          0,
          *((uint32_t *)this + 2156),
          0,
          60,
          0,
          30,
          4,
          0,
          0,
          0);
        LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
                       this,
                       30100,
                       0,
                       *((uint32_t *)this + 2157),
                       0,
                       60,
                       0,
                       30,
                       4,
                       0,
                       0,
                       0);
        *(this + 8617) = 0;
      }
    }
  }
  return pThis_C8;
}



// Boss 弹幕：引用 Particle/BossMissile{1,3,2,4}.ptl 四连发（75L）
// ------------------------------------------------------------
// 0x5BF2D0 sub_5BF2D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF2D0(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int result; // eax
  int fld_e1813; // ecx
  bool fld_e2161; // cc
  int v10; // eax
  int fld_e21612; // ecx
  uint32_t v12[4]; // [esp+8h] [ebp-80h]
  int v13; // [esp+18h] [ebp-70h]
  int v14; // [esp+1Ch] [ebp-6Ch]
  uint8_t v15[100]; // [esp+20h] [ebp-68h] BYREF
  int dword_796E502; // [esp+84h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v2 = *this;
  v13 = 0;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(v2 + 588))(this, "Particle/BossMissile1.ptl");
  v4 = *this;
  v12[0] = v3;
  v12[1] = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(v4 + 588))(this, "Particle/BossMissile3.ptl");
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BossMissile2.ptl");
  v6 = *this;
  v12[2] = v5;
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(v6 + 588))(this, "Particle/BossMissile4.ptl");
  fld_e1813 = *(this + 1813);
  v12[3] = result;
  if ( fld_e1813 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813);
    v13 = result;
  }
  fld_e2161 = *(this + 2161) <= 0;
  v14 = 0;
  if ( fld_e2161 )
  {
    *(this + 2161) = 0;
  }
  else
  {
    do
    {
      v10 = *this;
      qmemcpy(v15, (const void *)v12[v14], 0x62u);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint8_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v10 + 580))(
        this,
        30200,
        v13,
        v15,
        0,
        60,
        0,
        30,
        4,
        0,
        0,
        0);
      fld_e21612 = *(this + 2161);
      result = ++v14;
    }
    while ( v14 < fld_e21612 );
    *(this + 2161) = 0;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF3D0 sub_5BF3D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF3D0(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v2 + 896))(this, v3);
  result = sub_4A0550(600);
  *(this + 2159) = 1;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF430 sub_5BF430
// ------------------------------------------------------------
int sub_5BF430()
{
  int result; // eax

  switch ( sub_456390(0) )
  {
    case 1:
      result = 2;
      break;
    case 2:
      result = 3;
      break;
    case 3:
      result = 4;
      break;
    case 4:
      result = 6;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF480 sub_5BF480
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF480(void *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  if ( result != 18 )
  {
    result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
    if ( result != 16 )
      return sub_499FF0(this);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5BF4B0 sub_5BF4B0
// ------------------------------------------------------------
int /*usercall*/ sub_5BF4B0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax

  sub_4E1780(pArg1);
  if ( pArg1[1639] == 14 )
    return sub_5BE940(pArg1, nArg2, nArg3);
  result = pArg1[1639] - 15;
  if ( pArg1[1639] == 15 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);
  return result;
}



// 时钟门 AI（sub_699000; this+8618）
// ------------------------------------------------------------
// 0x5BF4E0 sub_5BF4E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF4E0(uint8_t *this)
{
  int pThis_19A0; // ecx
  int v3; // edi
  int result; // eax
  int v5; // eax

  pThis_19A0 = (int)(this + 6560);
  v3 = *(uint32_t *)(pThis_19A0 + 24);
  result = sub_699000(pThis_19A0);  // 【clock_now(clk)】
  if ( result >= v3 )
  {
    v5 = *(uint32_t *)this;
    *(this + 8618) = 0;
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 560))(this, 0, 0, 0, 0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5BF520 sub_5BF520
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF520(uint32_t *this, int nArg2)
{
  int result; // eax
  int fld_e1554; // eax
  int fld_e2155; // edx
  int fld_e2152; // edi
  int fld_e21522; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2152) )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
    if ( result == 14 && (int)*(this + 2154) > 1 )
    {
      fld_e1554 = sub_491C10(*(uint32_t *)(*(this + 1554) + 4));
      fld_e2155 = *(this + 2155) + 1;
      *(this + 2155) = fld_e2155;
      if ( fld_e2155 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2154);
        *(this + 2155) = 0;
      }
      fld_e2152 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 120))(*(this + 2152));
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 916))(*(this + 2152));
      fld_e21522 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 120))(*(this + 2152));
      v8 = *this;
      v9 = fld_e2152 - fld_e21522;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v11);
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 112))(this, v12 - v9);
    }
  }
  return result;
}



// 蓄力技能：vt+212 "HOLD"（90L；sub_4049C0 插值）
// ------------------------------------------------------------
// 0x5BF5F0 sub_5BF5F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BF5F0(uint32_t *this, int pArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2152; // ecx
  int v6; // eax
  int fld_e21522; // ecx
  int v8; // eax
  int fld_e21523; // ecx
  int v10; // eax
  int fld_e21524; // ecx
  uint32_t *fld_e28; // edi
  int fld_e1821; // edi
  uint32_t *v14; // eax
  uint64_t fld_e1820; // rax
  float v17; // [esp+6Ch] [ebp-20h]
  float v18; // [esp+70h] [ebp-1Ch]
  int v19; // [esp+88h] [ebp-4h]
  int v20; // [esp+94h] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) == 0
    || (*(this + 2152) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2152) = 0;
  }
  fld_e2152 = *(this + 2152);
  if ( fld_e2152 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2152 + 120))(fld_e2152);
    fld_e21522 = *(this + 2152);
    *(this + 2156) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21522 + 124))(fld_e21522);
    fld_e21523 = *(this + 2152);
    *(this + 2157) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21523 + 128))(fld_e21523);
    fld_e21524 = *(this + 2152);
    *(this + 2158) = v10;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e21524 + 604))(fld_e21524, 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2152) + 612))(*(this + 2152), 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2152) + 852))(*(this + 2152)) == 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2152) + 848))(*(this + 2152), 1);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    0,
    0,
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  v19 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v14 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v18 = (float)v20;
  v17 = (float)v19;
  fld_e1820 = (uint64_t)sub_4049C0(v17, v18, *v14 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1820) = *this;
  *(this + 2154) = fld_e1820;
  *(this + 2153) = 0;
  *(this + 2155) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(HIDWORD(fld_e1820) + 212))(
           this,
           "HOLD",
           -1,
           0,
           0);
}



// AI 相位辅助（this+8600）
// ------------------------------------------------------------
// 0x5BF7E0 sub_5BF7E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5BF7E0(uint32_t **this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v6; // edi
  uint32_t *result; // eax
  int *fld_e1554; // eax
  uint32_t *v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int nRand; // et2
  uint32_t *v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // [esp+Ch] [ebp-4h]

  ((void (/*thiscall*/ *)(uint32_t **))(*this)[210])(this);
  v6 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[46])(this);
  v22 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[47])(this);
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList != 8 )
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 1554));
  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this) == 8 )
  {
    result = (uint32_t *)sub_41A5E0((unsigned int)(this + 1757));
    if ( result == *(this + 2152) )
    {
      fld_e1554 = *(this + 1554);
      *((uint8_t *)this + 8600) = 0;
      sub_4926A0(*fld_e1554);
      return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
                         this,
                         1000,
                         **(this + 1554),
                         0,
                         0,
                         0,
                         0);
    }
  }
  else
  {
    result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this);
    if ( result == (uint32_t *)6 )
    {
      result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[224])(this, v6, v22);
      if ( v6 != 4 )
      {
        v9 = *this;
        v10 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[168])(this, 3, 0, 0, 0);
        v11 = sub_4954C0(v10);
        v12 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, v11 / 10);
        v13 = sub_4954C0(v12);
        result = (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, uint32_t, int))v9[219])(this, 0, v13 / 4);
      }
      if ( v22 != 4 )
      {
        nRand = rand() % 100;
        v15 = *this;
        v16 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[168])(this, 3, 0, 0, 0);
        v17 = sub_4954C0(v16);
        if ( nRand >= 50 )
        {
          v20 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, v17 / 20);
          v21 = sub_4954C0(v20);
          return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))v15[219])(this, 1, v21 / 8);
        }
        else
        {
          v18 = ((int (/*thiscall*/ *)(uint32_t **, int, int))(*this)[168])(this, 3, v17 / 10);
          v19 = sub_4954C0(v18);
          return (uint32_t *)((int (/*thiscall*/ *)(uint32_t **, int, int))v15[219])(this, 1, v19 / 4);
        }
      }
    }
  }
  return result;
}



// AI 相位辅助（this+8618）
// ------------------------------------------------------------
// 0x5BF9E0 sub_5BF9E0
// ------------------------------------------------------------
char /*thiscall*/ sub_5BF9E0(uint32_t *this)
{
  int v2; // edi
  int v3; // edi
  float v4; // eax
  int v5; // eax
  int *fld_e28; // edi
  int pObj; // ecx
  int v8; // eax
  char result; // al
  int v10; // [esp+Ch] [ebp-Ch]
  float v11; // [esp+10h] [ebp-8h]
  int v12; // [esp+14h] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v12 = sub_41A5E0(v2 + 816);
  v11 = COERCE_FLOAT(sub_41A5E0(v2 + 830));
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v10 = sub_41A5E0(v3 + 816);
  v4 = COERCE_FLOAT(sub_41A5E0(v3 + 830));
  (*(void (/*fastcall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
    this,
    (uint64_t)((double)v10 * v4) >> 32,
    0,
    (uint64_t)((double)v10 * v4),
    (uint64_t)((double)v12 * v11),
    0,
    0,
    0);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  fld_e28 = (int *)*(this + 28);
  pObj = *fld_e28;
  if ( v5 == 1 )
  {
    if ( pObj == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 0 )
      goto LABEL_10;
    v8 = 1142292480;
  }
  else
  {
    if ( pObj == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 0 )
      goto LABEL_10;
    v8 = -1005191168;
  }
  if ( fld_e28[4] != v8 )
  {
    fld_e28[4] = v8;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
LABEL_10:
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
  *((uint8_t *)this + 6573) = 0;
  *((uint8_t *)this + 6574) = 0;
  result = sub_698F90((int)(this + 1640), 350, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint8_t *)this + 8618) = 1;
  return result;
}



// 硬直字段（this+204/+208/8616）
// ------------------------------------------------------------
// 0x5BFB20 sub_5BFB20
// ------------------------------------------------------------
int /*thiscall*/ sub_5BFB20(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  sub_5BF7E0((uint32_t **)this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList != 8 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( result == 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 0 )
    {
      *(uint8_t *)(this + 8616) = 0;
      sub_4926A0(*(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
      return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
               this,
               1000,
               *(uint32_t *)(*(uint32_t *)(this + 6216) + 4),
               0,
               0,
               0,
               0);
    }
  }
  return result;
}



// ============================================================
// 【分区 11】滚动蜘蛛（桥接 0x5C 区 spider_trap.cpp）（0x5BFBC0-0x5C0000）
// 证据：SPIDER_ROLLING_LOOP 滚动循环（174L/148L；this+8652/8653/8673/8674/8748 相位）

// 滚动蜘蛛 AI（174L）：SPIDER_ROLLING_LOOP 播报；this+204/+208 硬直 +
//   8616/8617/8652/8653/8673/8674/8748 相位字段（滚动冲撞状态机【推断】）
// ------------------------------------------------------------
// 0x5BFBC0 sub_5BFBC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5BFBC0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1639; // eax
  uint32_t *pThis_88C; // edi
  int i; // ebx
  uint32_t *pThis_88C2; // edi
  int j; // ebx
  int v11; // edi
  uint32_t *v12; // eax
  int v13; // edx
  int v14; // eax
  uint32_t *v15; // edi
  uint32_t *pThis_88C3; // ebx
  int fld_e1554; // eax
  uint32_t *fld_e15542; // eax
  int result; // eax
  int fld_e1547; // [esp-4h] [ebp-10h]
  int fld_e2186; // [esp-4h] [ebp-10h]

  fld_e1639 = *(this + 1639);
  switch ( fld_e1639 )
  {
    case 8:
      if ( sub_41A5E0((unsigned int)(this + 1757)) == 3 )
      {
        pThis_88C = this + 2188;
        for ( i = 3; i != 0; --i )
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_88C++);
      }
      else if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);
      }
      break;
    case 18:
      pThis_88C2 = this + 2188;
      for ( j = 3; j != 0; --j )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_88C2++);
      break;
    case 19:
    case 17:
      sub_495890(2, *(this + 2186));
      break;
    default:
      break;
  }
  v11 = ArgList;
  if ( ArgList == 6 )
  {
    *((uint8_t *)this + 8616) = 1;
    goto LABEL_40;
  }
  if ( ArgList != 8 )
  {
    switch ( ArgList )
    {
      case 18:
        v14 = *this;
        fld_e1547 = *(this + 1547);
        *(this + 2159) = 0;
        *(this + 2186) = -1;
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v14 + 196))(this, fld_e1547);
        v15 = &unk_72FDD0;
        pThis_88C3 = this + 2188;
        do
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
            this,
            1,
            *pThis_88C3,
            *v15,
            v15[1],
            0,
            0);
          v15 += 2;
          ++pThis_88C3;
        }
        while ( (int)v15 < (int)&dword_72FDE8 );
        v11 = 18;
        goto LABEL_40;
      case 19:
        fld_e2186 = 2 * *(this + 2186);
        *(this + 2159) = 4;
        sub_495890(2, fld_e2186);
        break;
      case 16:
        fld_e1554 = *(this + 1554);
        *(this + 2160) = 0;
        *(this + 2186) = -1;
        fld_e15542 = (uint32_t *)(fld_e1554 + 24);
LABEL_39:
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *fld_e15542);
        goto LABEL_40;
      case 17:
        sub_495890(2, 2 * *(this + 2186));
        *(this + 2160) = 2;
        break;
      default:
        goto LABEL_40;
    }
    fld_e15542 = (uint32_t *)(*(this + 1554) + 20);
    goto LABEL_39;
  }
  v12 = *(uint32_t **)(LODWORD(fArg3) + 4);
  if ( *v12 != 0 )
  {
    switch ( *v12 )
    {
      case 1:
        *(this + 2161) = rand() % 3 + 2;
        break;
      case 2:
        v13 = *this;
        *(this + 2164) = 10;
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v13 + 212))(
          this,
          "SPIDER_ROLLING_LOOP",
          9,
          0,
          0);
        break;
      case 3:
        *(this + 2191) = -1;
        *((uint8_t *)this + 8748) = 1;
        break;
      case 4:
        *((uint8_t *)this + 8673) = 0;
        *((uint8_t *)this + 8674) = 0;
        sub_698F90((int)(this + 2165), 4000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
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
        v11 = 15;
        break;
      default:
        break;
    }
  }
  else
  {
    *((uint8_t *)this + 8617) = 1;
  }
LABEL_40:
  sub_5BF7E0((uint32_t **)this, v11, fArg3, nArg4, nArg5);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( result == 8 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 908))(this);
    if ( result == 2 )
    {
      *((uint8_t *)this + 8652) = 0;
      *((uint8_t *)this + 8653) = 0;
    }
  }
  return result;
}


// 滚动蜘蛛辅助（148L；this+200/8652/8653 相位）
// ------------------------------------------------------------
// 0x5BFE90 sub_5BFE90
// ------------------------------------------------------------
void /*thiscall*/ sub_5BFE90(int *this)
{
  int nRand; // ebx
  int pThis_6DD; // eax
  int fld_e1813; // ecx
  int v5; // edi
  int v6; // edi
  int fld_e18132; // ebx
  int nRand2; // edi
  int fld_e28; // edi
  double v10; // st7
  double v11; // st7
  uint64_t v12; // rax
  int v13; // edi
  int v14; // eax
  int fld_e282; // ecx
  int v16; // edi
  int v17; // eax
  int v18; // edx
  int v19; // eax
  void *v20; // eax
  char pThis_21CC; // cl
  int fld_e283; // edx
  int pThis_6DD2; // edi
  uint32_t *fld_e1554; // edi
  uint32_t *fld_e15542; // edi
  float v26; // [esp+4h] [ebp-Ch]
  int v27; // [esp+8h] [ebp-8h] BYREF
  int v28; // [esp+Ch] [ebp-4h] BYREF

  if ( (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) != 2 )
    return;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    if ( *(int *)(*(this + 30) + 148) >= 1 )
    {
      if ( *((uint8_t *)this + 8652) != 0 )
      {
LABEL_11:
        if ( *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8653) == 0 )
        {
          v19 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
          sub_424120(*(uint32_t **)(v19 + 132), 2, 300);
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
          if ( *(this + 2164) > 0 )
          {
            v20 = (void *)(*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
            sub_4AECE0(v20, 0);
            *((uint8_t *)this + 8652) = 0;
            *((uint8_t *)this + 8653) = 0;
          }
        }
        goto LABEL_15;
      }
      nRand = rand() % 60 + 60;
      pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
      fld_e1813 = *(this + 1813);
      v5 = dword_72FD68[pThis_6DD];
      if ( fld_e1813 != 0 )
      {
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
        v5 = v6 - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
        fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
        nRand = fld_e18132 - (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, v5, v5, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, nRand, nRand, 0, 0, 0);
      rand();
      nRand2 = (rand() % 100 >= 50) + 2;
      sub_4A0550((float *)*(this + 28), 320);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, nRand2, nRand2);
      fld_e28 = *(this + 28);
      v10 = *(float *)(fld_e28 + 24) * -1000.0 / (double)*(int *)(fld_e28 + 36);
      v11 = (double)(int)(uint64_t)(v10 + v10);
      v26 = v11;
      v12 = (uint64_t)(v11 * *(float *)(fld_e28 + 16) * 0.001);
      v13 = v12;
      v14 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*this + 120))(this, HIDWORD(v12));
      fld_e282 = *(this + 28);
      v28 = v13 + v14;
      v16 = (uint64_t)(v26 * *(float *)(fld_e282 + 20) * 0.001);
      v17 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      v18 = *this;
      v27 = v16 + v17;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(v18 + 136))(this, v28, v16 + v17, 0) == 0 )
        (*(void (/*thiscall*/ **)(int *, int *, int *, int, int, int, uint32_t, int))(*this + 140))(
          this,
          &v28,
          &v27,
          v28,
          v27,
          480,
          0,
          1);
      sub_4E4A50(v16, (int)this, 48012, 1, v28, v27, 0, 0, 0, 0, 0);
      --*(this + 2164);
    }
    if ( *((uint8_t *)this + 8652) != 0 )
      goto LABEL_11;
  }
LABEL_15:
  pThis_21CC = *((uint8_t *)this + 8652);
  if ( pThis_21CC != 0 && *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8653) == 0 )
    *((uint8_t *)this + 8653) = 1;
  fld_e283 = *(this + 28);
  if ( *(float *)(fld_e283 + 24) > 0.0 && pThis_21CC == 0 )
    *((uint8_t *)this + 8652) = 1;
  if ( *((uint8_t *)this + 8652) != 0 )
  {
    if ( *(float *)(fld_e283 + 24) > 0.0 )
    {
      pThis_6DD2 = sub_41A5E0((unsigned int)(this + 1757));
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > dword_72FD78[pThis_6DD2] )
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
    if ( *((uint8_t *)this + 8652) != 0
      && *(float *)(*(this + 28) + 24) < 0.0
      && (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < 100 )
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

