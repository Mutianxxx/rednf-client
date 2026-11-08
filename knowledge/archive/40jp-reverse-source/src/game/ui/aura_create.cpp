// ============================================================
// 【40JP逆向源代码工程】ui/aura_create.cpp
// 模块: 0x64 区块 —— 气功/光环对象族 + 商城购买窗 + 转职/公会/好友/PVP 窗
// 来源: work/dump_skills.txt  区块: 0x640000-0x650000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
// 函数数: 294
// ------------------------------------------------------------
// ★ 光环对象族（0x648F90-0x64FC60，本区研究重点）——基类 CNRDAuraMaster/
//   CNRDAuraMinion + 按属性的派生族，动画/粒子资源即"技能表现层"证据：
//     冰  CNAuraMasterIce     Common/Etc/Animation/Aura/IceAuraMaster.ani、
//         IceAuraMinionSnowFlake.ptl / IceAuraMinionSteam.ptl，事件 AURA_ICE_SET
//     诅咒 CNAuraMasterCurse  CurseAura.ptl / Monster/Ghoul/Particle/GhoulCurse.ptl
//         （食尸鬼诅咒共用），受方 CNDarkDamageFromCurseAura
//     火焰 CNAuraMasterFlame  Character/Fighter/Effect/Particle/NenMaster.ptl
//         （气功师念气），受方 CNFlameDamageFromFlameAura
//     战斗 CNAuraMasterBattle BattleAuraMaster.ani + BattleAuraMinion/S/E.ani，
//         事件 AURA_POWER_SET；派生 CNAttackUpFromBattleAura、
//         CNAuraMasterATDFSPEEDUp(+_KingGalok/_Father 王加洛克/父王变体)、
//         CNChangeDamageBonusRate(AttackPowerUp.ptl)
//     缓速 CNAuraMasterSlow   SlowAuraMaster.ani，受方 CNSlowFromSlowAura
//     护盾 CNAuraShield       AuraShieldStart/Loop/End/Hit1/Hit2.ani，
//         事件 AURA_SHIELD_LOOP（vmt1C/vmt34）
//     其它：CNProvocationDollAura 挑衅人偶（ProvocationDoll*.ani）、
//         CNSummonMonsterAura 召唤兽光环、CNFireBomb 暗黑火（DarkFire*.ani）、
//         CNFollowMe 跟随（FollowMeFlag1-3.ani）、CNWhipped 鞭挞、
//         CNAuraChangeStatusMaster(+SpikeKing 钉刺王变体)、CNTargetIt 指定目标、
//         CNSuplexed 过肩摔。
//   槽位语义（对 CNRDObject 系对象）：vmt0=析构、vmt4=初始化/复位、vmt1C=
//   生成时动画/粒子装配、vmt78=光环生效（SET 事件）、vmt7C=光环失效/转移、
//   vmt84=受击方伤害事件、vmt68=特效触发。
// ------------------------------------------------------------
// 窗口部分（0x640250-0x648EB0）：转职窗 CNRDClassChangeWindow（vmtC 223 行
//   含日志 "CRITICAL ERROR : CHARACTER CREATE FAIL! %d"——转职复用角色创建
//   表现管线）、PVP 战争房间邀请、好友列表、PVP 房间列表、副本地图、充值网页窗
//   CNRDPayWebWindow（http://www.d-fighter.com + interface/payweb.img +
//   Common/Etc/MonoLayer.img）、公会列表、商城购买窗 CNRDCashShopBuyWindow
//   （cashshopdoubleevent.img，CLICK_MOVE/COMMAND_SELECT/SCROLL_ARROW）。
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】转职窗 CNRDClassChangeWindow（0x640250-0x640A60）
// vmtC 打开主函数（223 行）：职业列表装配 + 640320/640570 表现件；
// 失败分支日志 "CRITICAL ERROR : CHARACTER CREATE FAIL! %d"——
// 转职复用角色创建管线（详见 combat/bigfunc_583B90）。
// ============================================================
// ------------------------------------------------------------
// 0x640250 sub_640250 —— 转职窗关闭清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_640250(int this)  // 函数: 转职窗关闭清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  int result; // eax

  *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 108);  // this+40 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(uint32_t *)(this + 36) = v3;  // this+36 = v3
  result = sub_69A840(v3);  // 调 sub_69A840
  *(uint8_t *)(this + 48) = 0;  // this+48 = 0
  *(uint8_t *)(this + 49) = 0;  // this+49 = 0
  *(uint8_t *)(this + 50) = 0;  // this+50 = 0
  *(uint8_t *)(this + 51) = 0;  // this+51 = 0
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  *(uint32_t *)(this + 64) = 6;  // this+64 = 6
  *(uint32_t *)(this + 68) = 12;  // this+68 = 12
  *(uint32_t *)(this + 76) = 1600;  // this+76 = 1600
  *(uint32_t *)(this + 96) = dword_99FCCC;  // this+96 = dword_99FCCC
  *(uint32_t *)(this + 52) = -16777216;  // this+52 = -16777216
  return result;
}



// ------------------------------------------------------------
// 0x640320 sub_640320 —— 转职表现公共件（558090 + 44BD30/5E51F0/41FEB0/44BD00 + 63A7C0 强化结果件复用，122 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_640320(int this, uint32_t *uArg2, unsigned int uArg3, int pArg4)  // 函数: 转职表现公共件（558090 + 44BD30/5E51F0/41FEB0/44BD00 + 63A7C0 强化结果件复用，122 行）
{
  void *v4; // edx
  int fld_4; // ecx
  unsigned int fld_C; // eax
  int fld_8; // edx
  int fld_82; // edx
  unsigned int v11; // eax
  int fld_87; // edx
  int fld_88; // eax
  char *pMem; // edi
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v17; // ebx
  int fld_83; // eax
  bool v20; // cf
  int v21; // ecx
  int fld_86; // ebx
  int v23; // ebx
  int fld_42; // [esp-18h] [ebp-40h]
  int fld_85; // [esp-Ch] [ebp-34h]
  unsigned int fld_84; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int fld_832; // [esp+38h] [ebp+10h]

  v4 = *(void **)(pArg4 + 4);
  v28[0] = *(void **)pArg4;  // v28[0] 写入 *(void **)pArg4
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // this+12 物品类型号
  else
    fld_C = 0;
  if ( uArg3 != 0 )  // 若 uArg3 != 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )  // 若 0x1FFFFFFF - fld_8 < uArg3
      sub_558090(this);  // 信息窗共用
    if ( fld_4 != 0 )  // 若 fld_4 != 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )  // 若 fld_C >= uArg3 + fld_82
    {
      fld_83 = *(uint32_t *)(this + 8);  // fld_83 = this+8
      v20 = (fld_83 - (int)uArg2) >> 3 < uArg3;  // fld_83=this+8 物品 id
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;  // fld_83=this+8 物品 id
      if ( v20 )  // 若 v20
      {
        sub_44BD30(uArg2, fld_83, &uArg2[v21 / 4u]);  // 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - (int)uArg2) >> 3);  // this+8 物品 id
        fld_85 = *(uint32_t *)(this + 8);  // fld_85 = this+8
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // 调 sub_5E51F0
        fld_86 = v30 + *(uint32_t *)(this + 8);  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_86;  // this+8 = fld_86
        sub_41FEB0(uArg2, (uint32_t *)(fld_86 - v30), v28);  // 8B 元素区间拷贝
      }
      else
      {
        v23 = fld_83 - v21;  // fld_83=this+8 物品 id
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // 8 字节元素正向拷贝
        sub_44BD00(uArg2, v23, fld_832);  // 8 字节元素反向拷贝
        sub_41FEB0(uArg2, &uArg2[v30 / 4u], v28);  // 8B 元素区间拷贝
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )  // 若 0x1FFFFFFF - (fld_C >> 1) >= fld_C
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 != 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )  // 若 v11 < uArg3 + fld_87
      {
        if ( fld_4 != 0 )  // 若 fld_4 != 0
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, uArg2, pMem);  // 结果 = 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // 强化结果公共件
      sub_44BD30(uArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;  // this+8 物品 id
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 != 0
        j__free(*(void **)(this + 4));  // 调 j__free
      *(uint32_t *)(this + 12) = &pMem[v31];  // this+12 = &pMem[v31]
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // this+8 = &pMem[8 * v17]
      *(uint32_t *)(this + 4) = pMem;  // this+4 = pMem
    }
  }
}


// ------------------------------------------------------------
// 0x640570 sub_640570 —— 转职表现中层（63A7C0 + 640320）
// ------------------------------------------------------------
void /*thiscall*/ sub_640570(int this, uint32_t *uArg2)  // 函数: 转职表现中层（63A7C0 + 640320）
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  if ( fld_4 != 0 )  // 若 fld_4 != 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3 )  // 若 fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3
  {
    fld_82 = *(uint32_t **)(this + 8);  // this+8 物品 id
    sub_63A7C0(fld_82, (uint32_t *)1, uArg2);  // 强化结果公共件
    *(uint32_t *)(this + 8) = fld_82 + 2;  // this+8 = fld_82 + 2
  }
  else
  {
    sub_640320(this, *(char **)(this + 8), 1u, (int)uArg2);  // 转职表现公共件
  }
}



// ------------------------------------------------------------
// 0x6405E0 CNRDClassChangeWindow__vmtC —— CNRDClassChangeWindow__vmtC 打开主函数（223 行：4CE8A0 + 47E720 职业 + 565EE0 + 69A5F0 定位）；失败日志 "CRITICAL ERROR : CHARACTER CREATE FAIL! %d"
// ------------------------------------------------------------
char /*thiscall*/ sub_6405E0(void **this, int nArg2, int pArg3)  // 【CNRDClassChangeWindow__vmtC】
{
  void **pThis; // ebx
  int v4; // esi
  int v6; // eax
  uint32_t *v7; // esi
  bool v8; // zf
  int v9; // eax
  int v10; // edx
  char *v11; // ecx
  int *v12; // edi
  int v13; // esi
  int v14; // edx
  unsigned int i; // ecx
  uint8_t *v16; // edx
  unsigned int j; // ecx
  uint8_t *v18; // edx
  int v19; // eax
  uint8_t *v20; // edx
  char *v21; // esi
  unsigned int v22; // ecx
  int *v23; // eax
  uint32_t *v24; // edi
  int v25; // eax
  void *v26; // edx
  char *v27; // ebx
  unsigned int v28; // esi
  int *v29; // ecx
  uint8_t *v30; // eax
  int v31; // esi
  uint8_t *v32; // eax
  int v33; // edx
  uint8_t *v34; // eax
  int v35; // ecx
  uint8_t *v36; // edi
  int v37; // eax
  uint32_t *v38; // ecx
  int v39; // edi
  int v40; // esi
  int v41; // [esp+Ch] [ebp-14h] BYREF
  int v42; // [esp+10h] [ebp-10h] BYREF
  int v43; // [esp+14h] [ebp-Ch]
  char ArgList[4]; // [esp+18h] [ebp-8h]
  void **pThis2; // [esp+1Ch] [ebp-4h]

  pThis = this;
  pThis2 = this;
  *(uint32_t *)ArgList = *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 44);  // 表按键查找（uint16）
  v4 = sub_4CE8A0(*(uint32_t *)ArgList);  // 调 sub_4CE8A0
  if ( v4 != 0 )  // 若 v4 != 0
  {
    if ( pThis[26] != nullptr )  // 若 pThis[26] != nullptr
      j__free(pThis[26]);  // 调 j__free
    pThis[26] = nullptr;  // pThis[26] = nullptr 空指针
    pThis[27] = nullptr;  // pThis[27] = nullptr 空指针
    pThis[28] = nullptr;  // pThis[28] = nullptr 空指针
    if ( pThis[30] != nullptr )  // 若 pThis[30] != nullptr
      j__free(pThis[30]);  // 调 j__free
    pThis[30] = nullptr;  // pThis[30] = nullptr 空指针
    pThis[31] = nullptr;  // pThis[31] = nullptr 空指针
    pThis[32] = nullptr;  // pThis[32] = nullptr 空指针
    if ( pThis[34] != nullptr )  // 若 pThis[34] != nullptr
      j__free(pThis[34]);  // 调 j__free
    v6 = 16 * pArg3 + v4;
    pThis[34] = nullptr;  // pThis[34] = nullptr 空指针
    pThis[35] = nullptr;  // pThis[35] = nullptr 空指针
    pThis[36] = nullptr;  // pThis[36] = nullptr 空指针
    v7 = *(uint32_t **)(v6 + 648);
    v8 = v7 == *(uint32_t **)(v6 + 652);
    v43 = v6;
    if ( !v8 )  // 若 !v8
    {
      do
      {
        if ( v7[1] != 0 )  // 若 v7[1] != 0
        {
          v9 = sub_47E720(*(uint32_t *)ArgList, *v7);  // 调 sub_47E720
          if ( v9 != 0 )  // 若 v9 != 0
          {
            v10 = v7[1];
            v41 = v9;
            v42 = v10;
            sub_640570(&v41);  // 转职表现中层（63A7C0 + 640320）
          }
        }
        v6 = v43;
        v7 += 2;
      }
      while ( v7 != *(uint32_t **)(v43 + 652) );  // 当 v7 != *(uint32_t **)(v43 + 652) 循环
    }
    v11 = (char *)&unk_99FC30 + 16 * *(uint32_t *)ArgList;
    v12 = *((int **)v11 + 1);
    v8 = v12 == *((int **)v11 + 2);
    v42 = (int)v11;
    if ( !v8 )  // 若 !v8
    {
      do
      {
        v13 = *v12;
        if ( *v12 != 0 && sub_41A5E0(v13 + 212) == 0 && sub_41A5E0(14 * pArg3 + v13 + 212) > 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v14 = *(uint32_t *)(v13 + 468);  // v14 = v13+468
          for ( i = 0; v14 != 0 && i < (*(uint32_t *)(v13 + 472) - v14) >> 2; ++i )  // 循环：i = 0; v14 != 0 && i < (*(uint32_t *)(v13 + 472) - v14) >> 2
          {
            if ( *(uint32_t *)(*(uint32_t *)(v13 + 468) + 4 * i) == pArg3 )  // 若 *(uint32_t *)(*(uint32_t *)(v13 + 468) + 4 * i) == pArg3
            {
              v16 = pThis2[26];
              for ( j = 0; v16 != nullptr && j < ((uint8_t *)pThis2[27] - v16) >> 3 && *((uint32_t *)pThis2[26] + 2 * j) != *v12; ++j )  // 循环：j = 0; v16 != nullptr && j < ((uint8_t *)pThis2[27] - v16) >
                ;
              v18 = pThis2[26];
              if ( v18 != nullptr )  // 若 v18 非空
                v19 = ((uint8_t *)pThis2[27] - v18) >> 3;
              else
                v19 = 0;
              if ( j == v19 )  // 若 j == v19
              {
                v20 = pThis2[30];
                v21 = (char *)(pThis2 + 29);
                if ( v20 != nullptr )  // 若 v20 非空
                  v22 = ((uint8_t *)pThis2[31] - v20) >> 2;
                else
                  v22 = 0;
                if ( v20 != nullptr && v22 < ((uint8_t *)pThis2[32] - v20) >> 2 )  // 若 v20 != nullptr && v22 < ((uint8_t *)pThis2[32] - v20) >> 2
                {
                  v23 = (int *)pThis2[31];
                  *v23 = *v12;  // *v23 写入 *v12
                  *((uint32_t *)v21 + 2) = v23 + 1;
                }
                else
                {
                  sub_565EE0(pThis2[31], 1, (int)v12);  // 商城/任务共用文本辅助
                }
              }
              pThis = pThis2;
              break;
            }
            pThis = pThis2;
          }
        }
        ++v12;  // 自增v12
      }
      while ( v12 != *(int **)(v42 + 8) );  // 当 v12 != *(int **)(v42 + 8) 循环
      v6 = v43;
    }
    v24 = *(uint32_t **)(v6 + 648);
    if ( v24 != *(uint32_t **)(v6 + 652) )  // 若 v24 != *(uint32_t **)(v6 + 652)
    {
      do
      {
        if ( v24[1] == 0 )  // 若 v24[1] == 0
        {
          v25 = sub_47E720(*(uint32_t *)ArgList, *v24);  // 调 sub_47E720
          v26 = pThis[34];
          v27 = (char *)(pThis + 33);
          v42 = v25;
          if ( v26 != nullptr )  // 若 v26 非空
            v28 = (*((uint32_t *)v27 + 2) - (int)v26) >> 2;
          else
            v28 = 0;
          if ( v26 != nullptr && v28 < (*((uint32_t *)v27 + 3) - (int)v26) >> 2 )  // 若 v26 != nullptr && v28 < (*((uint32_t *)v27 + 3) - (int)v26) >> 2
          {
            v29 = *((int **)v27 + 2);
            *v29 = v25;  // *v29 写入 v25
            *((uint32_t *)v27 + 2) = v29 + 1;
          }
          else
          {
            sub_565EE0(*((void **)v27 + 2), 1, (int)&v42);  // 商城/任务共用文本辅助
          }
          pThis = pThis2;
        }
        v24 += 2;
      }
      while ( v24 != *(uint32_t **)(v43 + 652) );  // 当 v24 != *(uint32_t **)(v43 + 652) 循环
    }
    pThis[11] = (void *)sub_418DD0(pArg3 + 4 * *(uint32_t *)ArgList + 4);  // pThis[11] 写入 (void *)sub_418DD0(pArg3 + 4 * *(uint32_t ..
    v30 = pThis[26];
    if ( v30 != nullptr )  // 若 v30 非空
      v31 = ((uint8_t *)pThis[27] - v30) >> 3;
    else
      v31 = 0;
    v32 = pThis[30];
    if ( v32 != nullptr )  // 若 v32 非空
      v33 = ((uint8_t *)pThis[31] - v32) >> 2;
    else
      v33 = 0;
    v34 = pThis[34];
    if ( v34 != nullptr )  // 若 v34 非空
      v35 = ((uint8_t *)pThis[35] - v34) >> 2;
    else
      v35 = 0;
    v36 = pThis[34];
    if ( v36 != nullptr )  // 若 v36 非空
      v37 = ((uint8_t *)pThis[35] - v36) >> 2;
    else
      v37 = 0;
    (*((void (/*thiscall*/ **)(void **, int, unsigned int))*pThis + 6))(  // 虚调用 vt+6
      pThis,
      22,
      3 * (((unsigned int)(v31 + 1) >> 1) + ((unsigned int)(v33 + 1) >> 1) + ((unsigned int)(v37 + 1) >> 1))  // CNRDClassChangeWindow__vmtC 打开主函数（223 行：4CE8A0 + 47E720 职业 + 565EE0 + 69A5F0 定位）；失败日志 「CRITICAL ERROR : CHARACTER CREATE FAIL! %d「
    + (v35 != 0 ? 3 : 0)
    + 14);
    v38 = pThis[2];
    v39 = (480 - v38[8]) / 2;
    v40 = (640 - v38[7]) / 2;
    sub_69A5F0(v38, v40, v39);  // 调 sub_69A5F0
    sub_69A5F0(  // 调 设位、sub_69A840 登记
      pThis[9],
      v40 + ((unsigned int)(*((uint32_t *)pThis[2] + 7) - *((uint32_t *)pThis[9] + 7)) >> 1),
      *((uint32_t *)pThis[2] + 8) + v39 - 34);
    return 1;
  }
  else
  {
    off_77F3FC("CRITICAL ERROR : CHARACTER CREATE FAIL! %d", *(uint32_t *)ArgList);  // 字符串 “CRITICAL ERROR : CHARACTER CREATE FAIL! %d”
    return 0;
  }
}


// ------------------------------------------------------------
// 0x640990 sub_640990 —— 转职窗列表（46 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_640990(uint32_t *this)  // 函数: 转职窗列表（46 行）
{
  int (/*thiscall*/ ***fld_e20)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e21)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e22)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e23)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e19)(uint32_t, int); // ecx
  uint32_t *pThis_A; // esi
  int i; // edi

  fld_e20 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 20);  // this+20 频道页号
  if ( fld_e20 != nullptr )  // 若 fld_e20 非空
    result = (**fld_e20)(fld_e20, 1);
  fld_e21 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 21);  // this+21 霸体状态字节
  *(this + 20) = 0;  // this+80 = 0
  if ( fld_e21 != nullptr )  // 若 fld_e21 非空
    result = (**fld_e21)(fld_e21, 1);
  fld_e22 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 22);
  *(this + 21) = 0;  // this+84 = 0
  if ( fld_e22 != nullptr )  // 若 fld_e22 非空
    result = (**fld_e22)(fld_e22, 1);
  fld_e23 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 23);
  *(this + 22) = 0;  // this+88 = 0
  if ( fld_e23 != nullptr )  // 若 fld_e23 非空
    result = (**fld_e23)(fld_e23, 1);
  fld_e19 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 19);
  *(this + 23) = 0;  // this+92 = 0
  if ( fld_e19 != nullptr )  // 若 fld_e19 非空
    result = (**fld_e19)(fld_e19, 1);
  *(this + 19) = 0;  // this+76 = 0
  pThis_A = this + 10;
  for ( i = 9; i != 0; --i )  // 循环：i = 9; i != 0; --i
  {
    if ( *pThis_A != 0 )  // 若 *pThis_A != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_A)(*pThis_A, 1);
    *pThis_A++ = 0;  // *pThis_A++ 写入 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x640A10 sub_640A10 —— PVP 邀请数据（20 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_640A10(int this)  // 函数: PVP 邀请数据（20 行）
{
  if ( *(uint32_t *)(this + 100) != 0 )  // 若 *(uint32_t *)(this + 100) != 0
    j__free(*(void **)(this + 100));  // 调 j__free
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  if ( *(uint32_t *)(this + 116) != 0 )  // 若 *(uint32_t *)(this + 116) != 0
    j__free(*(void **)(this + 116));  // 调 j__free
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint32_t *)(this + 120) = 0;  // this+120 = 0
  *(uint32_t *)(this + 124) = 0;  // this+124 = 0
  *(uint32_t *)(this + 128) = 0;  // this+128 = 0
}



// ------------------------------------------------------------
// 0x640A60 sub_640A60 —— PVP 邀请页绘制（418DD0/429830/42B340 + 491530/491630 + 42A430/42A410，111 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_640A60(int *this, int nArg2, int nArg3)  // 函数: PVP 邀请页绘制（418DD0/429830/42B340 + 491530/491630 + 42A430/42A410，111 行）
{
  int pObj; // eax
  int v5; // ebx
  int v6; // ecx
  int fld_e25; // edx
  unsigned int fld_e32; // eax
  int result; // eax
  int v10; // esi
  int pObj4; // eax
  int pObj3; // eax
  int pObj2; // eax
  int v14; // esi
  int v15; // esi
  int v16; // ebx
  bool v17; // cc
  int v18; // [esp+Ch] [ebp-Ch]
  int v19; // [esp+10h] [ebp-8h]
  int *pThis_A; // [esp+14h] [ebp-4h]
  int v21; // [esp+20h] [ebp+8h]
  int v22; // [esp+24h] [ebp+Ch]

  pObj = sub_418DD0(81);  // 调 sub_418DD0
  if ( pObj != 0 )  // 若 pObj != 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, nArg2, nArg3, dword_79C0B0);  // 调用虚函数槽 +152
  v5 = nArg3 + 35;
  v21 = nArg2 + 6;
  v6 = 0;
  v22 = nArg3 + 35;
  v19 = 0;
  pThis_A = this + 10;
  do
  {
    fld_e25 = *(this + 25);  // fld_e25 = this+25
    fld_e32 = v6 + *(this + 32);  // this+32 格子像素尺寸
    if ( fld_e25 != 0 && fld_e32 < (*(this + 26) - fld_e25) >> 2 )  // 若 fld_e25 != 0 && fld_e32 < (*(this + 26) - fld_e25) >> 2
    {
      v18 = 4 * fld_e32;
      result = sub_429830(*(uint16_t *)(4 * fld_e32 + *(this + 25)));  // 结果 = 表按键查找（uint16）
      v10 = result;
      if ( result != 0 )  // 若 result != 0
      {
        pObj4 = sub_42B340(result);  // 结果 = 虚拟角色惰性创建（0x294 字节）
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj4 + 384))(  // 虚槽+384 槽数组 getter（+348 起，越界返回 0）
          pObj4,
          v21 + 3,
          v5 + 1,
          16,
          16,
          1065353216);
        sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        pObj3 = sub_42A430(v10);  // 结果 = 同构 ·0x42A410
        if ( pObj3 != 0 )  // 若 pObj3 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v21 + 22, v5, dword_79C0B0);  // 调用虚函数槽 +152
        sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
        pObj2 = sub_42A410(v10);  // 结果 = 图标句柄取用（+116 槽）
        if ( pObj2 != 0 )  // 若 pObj2 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v21 + 22, v5, dword_79C0B0);  // 调用虚函数槽 +152
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 33);  // 调用虚函数槽 +72
        if ( *(uint32_t *)(v10 + 40) < 0x10u )  // 若 *(uint32_t *)(v10 + 40) < 0x10u
          v14 = v10 + 20;
        else
          v14 = *(uint32_t *)(v10 + 20);  // v14 = v10+20
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          v21 + 55,
          v5 + 4,
          -1,
          v14);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
        if ( *(uint32_t *)(*(this + 29) + v18) != 0 )  // 若 *(uint32_t *)(*(this + 29) + v18) != 0
        {
          *(uint8_t *)(*pThis_A + 16) = 0;
          v15 = *(uint32_t *)(*pThis_A + 24);
          v16 = *(uint32_t *)(*pThis_A + 20);
          result = sub_418DD0(86);  // 调 sub_418DD0
          if ( result != 0 )  // 若 result != 0
            result = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 虚槽+152 效果通道 3
                       result,
                       v16,
                       v15,
                       dword_79C0B0);  // dword_79C0B0（文本/图像绘制对象）
          v5 = v22;
        }
        else
        {
          result = *pThis_A;
          *(uint8_t *)(*pThis_A + 16) = 1;
        }
        v5 += 20;
        v22 = v5;
      }
    }
    else
    {
      result = (int)pThis_A;
      *(uint8_t *)(*pThis_A + 16) = 0;
    }
    v6 = v19 + 1;
    v17 = ++v19 < 9;
    ++pThis_A;  // 自增pThis_A
  }
  while ( v17 );  // 当 v17 循环
  return result;
}



// ============================================================
// 【分区 2】PVP 战争房间邀请窗 CNRDPVPWarRoomInviteWindow（0x640C50-0x6414F0）
// vmtC 打开（287 行：4A2CF0 + 52DAA0/468240/430C80 房间数据 + 69C680）。
// ============================================================
// ------------------------------------------------------------
// 0x640C50 sub_640C50 —— PVP 邀请清理（42B530 + 423200/423290/423380）
// ------------------------------------------------------------
int /*thiscall*/ sub_640C50(uint32_t *this, int nArg2)  // 函数: PVP 邀请清理（42B530 + 423200/423290/423380）
{
  int result; // eax
  int v4; // ecx
  int fld_e25; // esi
  int v6; // eax

  if ( *(uint32_t *)(dword_8F7A24 + 12) != 6 || (uint8_t)(result = sub_42B530(*(uint32_t **)(dword_8F7A24 + 40))) != 0 )  // 类别判定取反
  {
    v4 = 4 * nArg2;
    *(uint32_t *)(4 * nArg2 + *(this + 29)) = 1;  // this+29 pSessionCtx
    fld_e25 = *(uint32_t *)(*(this + 25) + v4);
    sub_423200(dword_8F7B08, 10);  // 【发送网络包API】
    nArg2 = fld_e25;
    sub_423290(dword_8F7B08, (int)&nArg2, 2);  // 调 sub_423290
    v6 = *(uint32_t *)(dword_8F7A24 + 12);  // 全局 dword_8F7A24 = 登录/选区管理器
    if ( v6 == 4 )  // 若 v6 == 4
    {
      HIBYTE(nArg2) = 2;
      sub_423290(dword_8F7B08, (int)&nArg2 + 3, 1);  // 调 sub_423290
    }
    else if ( v6 == 6 )  // 否则若 v6 == 6
    {
      HIBYTE(nArg2) = 3;
      sub_423290(dword_8F7B08, (int)&nArg2 + 3, 1);  // 调 sub_423290
    }
    nArg2 = 0;
    sub_423290(dword_8F7B08, (int)&nArg2, 4);  // 调 sub_423290
    return sub_423380(dword_8F7B08);  // 发包提交：Commit()
  }
  return result;
}



// ------------------------------------------------------------
// 0x640D10 sub_640D10 —— PVP 邀请页绘制 2（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630，132 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_640D10(int this)  // 函数: PVP 邀请页绘制 2（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630，132 行）
{
  uint32_t *pMem; // eax
  uint32_t *fld_24; // eax
  uint32_t *pThis_28; // ebx
  uint8_t *pMem2; // eax
  uint32_t *pMem22; // edi
  int fld_242; // ebx
  uint32_t *pMem222; // ecx
  uint8_t *pMem3; // edi
  int v10; // ebx
  uint8_t *pMem4; // edi
  int v12; // ebx
  uint8_t *pMem5; // edi
  uint32_t *fld_50; // eax
  int result; // eax
  int Block; // [esp+Ch] [ebp-14h]
  void *Blocka; // [esp+Ch] [ebp-14h]
  uint32_t *pThis_282; // [esp+10h] [ebp-10h]

  *(uint32_t *)(this + 36) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 100);  // this+36 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_24 = sub_43C410(pMem, *(uint32_t *)(this + 36), 52, 53, 54, 52, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_24 = nullptr;  // fld_24 = nullptr 空指针
  *(uint32_t *)(this + 76) = fld_24;  // this+76 = fld_24
  sub_69A5F0(fld_24, 103, 218);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t *)(this + 76));  // 调 sub_69A840
  pThis_28 = (uint32_t *)(this + 40);  // this+40 物品状态附属标志
  Block = 37;
  pThis_282 = (uint32_t *)(this + 40);  // this+40 物品状态附属标志
  do
  {
    pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
    pMem22 = pMem2;
    if ( pMem2 != nullptr )  // 若 pMem2 非空
    {
      fld_242 = *(uint32_t *)(this + 36);  // fld_242 = this+36
      sub_426BD0(pMem2);  // nengine::IControl 构造
      *pMem22 = &nengine::CNButton::`vftable';
      sub_69C780(v6);  // 调 sub_69C780
      sub_69C7B0(v7, 83, 84, 85, 83, 0, 0);  // 调 sub_69C7B0
      v4 = v18;
      v8 = v6;
    }
    else
    {
      v8 = nullptr;  // v8 = nullptr 空指针
    }
    *v4 = v8;  // *v4 写入 v8
    sub_69A5F0(v8, 173, Block);  // 调 sub_69A5F0
    sub_69A840(*v4++);  // 调 sub_69A840
    v18 = v4;
    Block += 20;
  }
  while ( Block < 217 );  // 当 Block < 217 循环
  v9 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( v9 != nullptr )  // 若 v9 非空
  {
    v10 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
    sub_426BD0(v9);  // nengine::IControl 构造
    *(uint32_t *)v9 = &nengine::CNButton::`vftable';
    sub_69C780(pMem3);  // 调 sub_69C780
    sub_69C7B0(v10, 4, 4, 5, 4, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    pMem3 = nullptr;  // pMem3 = nullptr 空指针
  }
  *(uint32_t *)(this + 80) = pMem3;  // this+80 = pMem3
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
  {
    v12 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
    sub_426BD0(pMem4);  // nengine::IControl 构造
    *(uint32_t *)pMem4 = &nengine::CNButton::`vftable';
    sub_69C780(v11);  // 调 sub_69C780
    sub_69C7B0(v12, 6, 6, 7, 6, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    v11 = nullptr;  // v11 = nullptr 空指针
  }
  *(uint32_t *)(this + 84) = v11;  // this+84 = v11
  v13 = operator new(0x88u);  // 堆分配 136 字节对象
  if ( v13 != nullptr )  // 若 v13 非空
  {
    Blocka = *(void **)(this + 36);  // this+36 物品状态字
    sub_426BD0(v13);  // nengine::IControl 构造
    *(uint32_t *)v13 = &nengine::CNSlider::`vftable';
    sub_69CA20(pMem5);  // 调 sub_69CA20
    sub_69CA50(Blocka, 61, 60);  // 调 sub_69CA50
    *(uint32_t *)pMem5 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    pMem5 = nullptr;  // pMem5 = nullptr 空指针
  }
  *(uint32_t *)(this + 88) = pMem5;  // this+88 = pMem5
  if ( operator new(0x74u) != nullptr )  // 堆分配 116 字节对象
    fld_50 = (uint32_t *)sub_43C630(*(uint32_t *)(this + 80), *(uint32_t *)(this + 84), *(uint32_t *)(this + 88));  // 结果 = nengine::CNVScroll 构造
  else
    fld_50 = nullptr;  // fld_50 = nullptr 空指针
  *(uint32_t *)(this + 92) = fld_50;  // this+92 = fld_50
  sub_69A5F0(fld_50, 239, 37);  // 调 sub_69A5F0
  result = sub_69A840(*(uint32_t *)(this + 92));  // 调 sub_69A840
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint32_t *)(this + 156) = 0;  // this+156 = 0
  *(uint32_t *)(this + 164) = 0;  // this+164 = 0
  *(uint32_t *)(this + 168) = 0;  // this+168 = 0
  *(uint32_t *)(this + 172) = 0;  // this+172 = 0
  *(uint32_t *)(this + 176) = 0;  // this+176 = 0
  *(uint32_t *)(this + 180) = 0;  // this+180 = 0
  *(uint8_t *)(this + 132) = 0;  // this+132 = 0
  *(uint8_t *)(this + 133) = 0;  // this+133 = 0
  *(uint8_t *)(this + 134) = 0;  // this+134 = 0
  *(uint8_t *)(this + 135) = 0;  // this+135 = 0
  *(uint32_t *)(this + 148) = 6;  // this+148 = 6
  *(uint32_t *)(this + 152) = 12;  // this+152 = 12
  *(uint32_t *)(this + 160) = 1600;  // this+160 = 1600
  *(uint32_t *)(this + 180) = dword_99FCCC;  // this+180 = dword_99FCCC
  *(uint32_t *)(this + 160) = 120;  // this+160 = 120
  *(uint32_t *)(this + 144) = 1;  // this+144 = 1
  *(uint32_t *)(this + 136) = -16777216;  // this+136 = -16777216
  return result;
}


// ------------------------------------------------------------
// 0x641050 CNRDPVPWarRoomInviteWindow__vmt8 —— CNRDPVPWarRoomInviteWindow__vmt8 Update（CLICK_BUTTON2 + 69C690 + 640C50 接受）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPVPWarRoomInviteWindow__vmt8(uint32_t *this)  // CNRDPVPWarRoomInviteWindow__vmt8 Update（CLICK_BUTTON2 + 69C690 + 640C50 接受）
{
  int v2; // edi
  uint32_t *pThis_A; // ebx
  uint8_t *result; // eax

  *(this + 32) = sub_69C690(*(this + 23));  // 取设备对象 +112 字段（类型或句柄）
  v2 = 0;
  pThis_A = this + 10;
  do
  {
    if ( *(uint8_t *)(*pThis_A + 17) != 0
      && dword_79BE34 == *(uint32_t *)(*pThis_A + 12)
      && *(uint32_t *)(*(this + 29) + 4 * (v2 + *(this + 32))) == 0 )
    {
      sub_640C50(this, v2 + *(this + 32));  // PVP 邀请清理（42B530 + 423200/423290/423380）
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    }
    ++v2;  // 自增v2
    ++pThis_A;  // 自增pThis_A
  }
  while ( v2 < 9 );  // 当 v2 < 9 循环
  result = (uint8_t *)*(this + 19);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 虚调用 vt+32
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  return result;
}



// ------------------------------------------------------------
// 0x6410F0 CNRDPVPWarRoomInviteWindow__vmt0 —— CNRDPVPWarRoomInviteWindow__vmt0 构造（转发 640A60 页绘制）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPVPWarRoomInviteWindow__vmt0(int *this, int pArg2)  // 函数: CNRDPVPWarRoomInviteWindow__vmt0 构造（转发 640A60 页绘制）
{
  int result; // eax

  result = IRDPopupWindow__vmt0(pArg2);
  if ( pArg2 == *(this + 2) )  // 若 pArg2 == *(this + 2)
    return sub_640A60(this, *(uint32_t *)(pArg2 + 20), *(uint32_t *)(pArg2 + 24));  // PVP 邀请页绘制
  return result;
}



// ------------------------------------------------------------
// 0x641120 CNRDPVPWarRoomInviteWindow__vmtC —— CNRDPVPWarRoomInviteWindow__vmtC 打开槽（287 行：4ED3F0 + 4A2CF0 + 52DAA0/468240/430C80 房间数据 + 69C680）
// ------------------------------------------------------------
char /*thiscall*/ sub_641120(uint32_t *this, int nArg2, int nArg3)  // 【CNRDPVPWarRoomInviteWindow__vmtC】
{
  uint32_t *pThis; // edi
  uint32_t *fld_e2; // ecx
  uint32_t *v5; // ebx
  uint32_t *v6; // esi
  int v7; // eax
  uint32_t *v8; // eax
  bool v9; // zf
  uint32_t *v10; // edi
  int v11; // edx
  int16_t *v12; // eax
  int v13; // edx
  unsigned int v14; // edx
  int v15; // ecx
  int v16; // edi
  signed int v17; // eax
  uint32_t *j; // esi
  int v19; // eax
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // edi
  uint32_t *v24; // esi
  int v25; // ecx
  unsigned int v26; // edx
  uint32_t *v27; // eax
  void *v28; // eax
  uint32_t *v29; // esi
  int v30; // edi
  int *pThis22; // edx
  uint32_t *k; // eax
  int v33; // ecx
  int v34; // edx
  unsigned int v35; // ecx
  uint32_t *v36; // eax
  int v37; // ecx
  int v38; // ecx
  int v39; // eax
  int *v40; // edx
  int v41; // ecx
  int v42; // eax
  int v43; // eax
  int v44; // ecx
  int v45; // eax
  int v46; // ebx
  uint32_t *v47; // eax
  uint32_t *v48; // edi
  uint32_t *v50; // [esp+10h] [ebp-38h]
  uint32_t v51[2]; // [esp+18h] [ebp-30h] BYREF
  int v52; // [esp+20h] [ebp-28h] BYREF
  int v53; // [esp+24h] [ebp-24h]
  int v54; // [esp+28h] [ebp-20h]
  int v55; // [esp+2Ch] [ebp-1Ch]
  int v56; // [esp+30h] [ebp-18h]
  unsigned int i; // [esp+34h] [ebp-14h]
  uint32_t *pThis2; // [esp+38h] [ebp-10h]
  int v59; // [esp+44h] [ebp-4h]
  uint32_t *v60; // [esp+50h] [ebp+8h]
  char v61; // [esp+53h] [ebp+Bh]

  pThis = this;
  fld_e2 = (uint32_t *)*(this + 2);
  pThis2 = pThis;
  sub_69A5F0(fld_e2, 80, 80);  // 调 sub_69A5F0
  v5 = pThis + 24;
  sub_4ED3F0((int)(pThis + 24), nArg2);  // int 向量拷贝赋值（全容量路径）
  v6 = sub_4A2CF0();  // 调 sub_4A2CF0
  v50 = v6;
  v59 = 0;
  v7 = sub_429830((uint16_t)word_77F804);  // 结果 = 表按键查找（uint16）
  v53 = v7;
  if ( v7 == 0 )  // 若 v7 == 0
  {
    v8 = (uint32_t *)*v6;
    v9 = *v6 == (uint32_t)v6;
    *v6 = v6;  // *v6 写入 v6
    v6[1] = v6;
    if ( !v9 )  // 若 !v9
    {
      do
      {
        v10 = (uint32_t *)*v8;
        j__free(v8);  // 调 j__free
        v8 = v10;
      }
      while ( v10 != v6 );  // 当 v10 != v6 循环
    }
    goto LABEL_66;  // 跳转 LABEL_66
  }
  v11 = *(uint32_t *)(v7 + 116);  // v11 = v7+116
  v56 = -1;
  v55 = -1;
  v9 = *(uint32_t *)(dword_8F7A24 + 12) == 6;  // 全局 dword_8F7A24 = 登录/选区管理器
  v54 = v11;
  v61 = 0;
  if ( v9 )  // 若 v9
  {
    v12 = (int16_t *)((char *)dword_8F7C48 + 20 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76));  // dword_8F7A24（当前场景状态对象）
    v13 = v12[1];
    v56 = *v12;
    v55 = v13;
    v61 = 1;
  }
  v14 = 0;
  for ( i = 0; ; v14 = i )  // 循环：i = 0; ; v14 = i
  {
    v15 = v5[1];
    if ( v15 == 0 || v14 >= (v5[2] - v15) >> 2 )  // 若 v15 == 0 || v14 >= (v5[2] - v15) >> 2
      break;
    v16 = sub_429830(*(uint16_t *)(pThis[25] + 4 * v14));  // 结果 = 表按键查找（uint16）
    if ( v16 != 0 )  // 若 v16 != 0
    {
      v17 = abs32(v54 - *(uint32_t *)(v16 + 116));
      v52 = v17;
      if ( v16 != v53 )  // 若 v16 != v53
      {
        for ( j = (uint32_t *)*v6; j != v50; j = (uint32_t *)*j )  // 循环：j = (uint32_t *)*v6; j != v50; j = (uint32_t *)*j
        {
          if ( j[2] >= v17 )  // 若 j[2] >= v17
            break;
        }
        if ( v61 != 0 )  // 若 v61 != 0
        {
          v19 = sub_41A5E0(v16 + 53);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
          if ( v19 >= v56 )  // 若 v19 >= v56
          {
            v20 = sub_41A5E0(v16 + 53);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
            if ( v20 <= v55 )  // 若 v20 <= v55
            {
              v17 = v52;
              goto LABEL_19;  // 跳转 LABEL_19
            }
          }
        }
        else
        {
LABEL_19:
          v21 = j[1];
          v22 = *(uint16_t *)(v16 + 4);  // v22 = v16+4
          v51[0] = v17;
          v51[1] = v22;
          v23 = sub_52DAA0(j, v21, v51);  // 调 sub_52DAA0
          sub_468240(1);  // list 元素数预留（溢出抛错）
          j[1] = v23;
          **(uint32_t **)(v23 + 4) = v23;
        }
        v6 = v50;
      }
    }
    pThis = pThis2;
    ++i;  // 自增i
  }
  if ( v5[1] != 0 )  // 若 v5[1] != 0
    j__free((void *)v5[1]);  // 调 j__free
  v5[1] = 0;
  v5[2] = 0;
  v5[3] = 0;
  v24 = (uint32_t *)*v6;
  if ( v24 != v50 )  // 若 v24 != v50
  {
    do
    {
      v25 = v5[1];
      if ( v25 != 0 )  // 若 v25 != 0
        v26 = (v5[2] - v25) >> 2;
      else
        v26 = 0;
      if ( v25 != 0 && v26 < (v5[3] - v25) >> 2 )  // 若 v25 != 0 && v26 < (v5[3] - v25) >> 2
      {
        v27 = (uint32_t *)v5[2];
        *v27 = v24[3];  // *v27 写入 v24[3]
        v5[2] = v27 + 1;  // v5[2] 写入 v27 + 1
      }
      else
      {
        sub_430C80((void *)v5[2], 1, (int)(v24 + 3));  // uint32 vector 区间插入（同值填充）
      }
      v24 = (uint32_t *)*v24;
    }
    while ( v24 != v50 );  // 当 v24 != v50 循环
    pThis = pThis2;
  }
  v28 = (void *)pThis[29];
  v29 = pThis + 28;
  v30 = 0;
  if ( v28 != nullptr )  // 若 v28 非空
    j__free(v28);  // 调 j__free
  pThis22 = pThis2;
  v29[1] = 0;
  v29[2] = 0;
  v29[3] = 0;
  for ( k = pThis22 + 10; ; k = v60 + 1 )  // 循环：k = pThis22 + 10; ; k = v60 + 1
  {
    v33 = v5[1];
    v60 = k;
    if ( v33 == 0 || v30 >= (unsigned int)((v5[2] - v33) >> 2) )  // 若 v33 == 0 || v30 >= (unsigned int)((v5[2] - v33) >> 2)
      break;
    v34 = v29[1];
    v52 = 0;
    if ( v34 != 0 )  // 若 v34 != 0
      v35 = (v29[2] - v34) >> 2;
    else
      v35 = 0;
    if ( v34 != 0 && v35 < (v29[3] - v34) >> 2 )  // 若 v34 != 0 && v35 < (v29[3] - v34) >> 2
    {
      v36 = (uint32_t *)v29[2];
      *v36 = 0;  // *v36 写入 0
      v29[2] = v36 + 1;  // v29[2] 写入 v36 + 1
    }
    else
    {
      sub_430C80((void *)v29[2], 1, (int)&v52);  // uint32 vector 区间插入（同值填充）
    }
    if ( v30 < 9 )  // 若 v30 < 9
      *(uint8_t *)(*v60 + 16) = 1;
    pThis22 = pThis2;
    ++v30;  // 自增v30
  }
  v37 = v5[1];
  if ( v37 == 0 || (unsigned int)((v5[2] - v37) >> 2) < 9 )  // 若 v37 == 0 || (unsigned int)((v5[2] - v37) >> 2) < 9
  {
    v38 = v5[1];
    if ( v38 != 0 )  // 若 v38 != 0
    {
      v39 = (v5[2] - v38) >> 2;
      if ( v39 < 9 )  // 若 v39 < 9
        goto LABEL_54;  // 跳转 LABEL_54
    }
    else
    {
      v39 = 0;
LABEL_54:
      v40 = &pThis22[v39 + 10];
      v41 = 9 - v39;
      do
      {
        v42 = *v40++;  // 取 *v40 后自增
        --v41;  // 自减v41
        *(uint8_t *)(v42 + 16) = 0;  // v42+16 = 0
      }
      while ( v41 != 0 );  // 当 v41 != 0 循环
      pThis22 = pThis2;
    }
  }
  v43 = *pThis22;
  pThis22[32] = 0;
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v43 + 24))(pThis22, 0, 0);  // 调用虚函数槽 +24
  v44 = v5[1];
  if ( v44 != 0 && (unsigned int)((v5[2] - v44) >> 2) >= 9 )  // 若 v44 != 0 && (unsigned int)((v5[2] - v44) >> 2) >= 9
  {
    v45 = v5[1];
    if ( v45 != 0 )  // 若 v45 != 0
      v46 = (v5[2] - v45) >> 2;
    else
      v46 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pThis2[23] + 32))(pThis2[23], v46);  // 调用虚函数槽 +32
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pThis2[23] + 32))(pThis2[23], 0);  // 调用虚函数槽 +32
  }
  sub_69C680(0);  // 调 sub_69C680
  v6 = v50;
  v47 = (uint32_t *)*v50;
  v9 = *v50 == (uint32_t)v50;
  *v50 = v50;  // *v50 写入 v50
  v50[1] = v50;
  if ( !v9 )  // 若 !v9
  {
    do
    {
      v48 = (uint32_t *)*v47;
      j__free(v47);  // 调 j__free
      v47 = v48;
    }
    while ( v48 != v50 );  // 当 v48 != v50 循环
  }
LABEL_66:
  j__free(v6);  // 调 j__free
  return 1;
}


// ------------------------------------------------------------
// 0x6414D0 sub_6414D0 —— PVP 邀请收尾（18 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6414D0(uint32_t *this)  // 函数: PVP 邀请收尾（18 行）
{
  *(this + 9) = 0;  // this+36 = 0
  *(this + 10) = 0;  // this+40 = 0
  *(this + 11) = 0;  // this+44 = 0
  *(this + 12) = 0;  // this+48 = 0
  *(this + 13) = 0;  // this+52 = 0
  *(this + 14) = 0;  // this+56 = 0
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 0;  // this+64 = 0
  return 0;
}



// ============================================================
// 【分区 3】好友列表窗 CNRDFriendListWindow（0x6414F0-0x6421A0）
// vmt0 构造（163 行：641C00 好友数据 + 479240 + 42B340）。
// ============================================================
// ------------------------------------------------------------
// 0x6414F0 sub_6414F0 —— 好友窗数据（52 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6414F0(uint32_t *this)  // 函数: 好友窗数据（52 行）
{
  void (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  uint32_t *pThis_B; // edi
  int i; // ebx
  void (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e15)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e16)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e43)(uint32_t, int); // ecx
  int result; // eax

  fld_e10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    (**fld_e10)(fld_e10, 1);
  *(this + 10) = 0;  // this+40 = 0
  pThis_B = this + 11;
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    if ( *pThis_B != 0 )  // 若 *pThis_B != 0
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_B)(*pThis_B, 1);
    *pThis_B++ = 0;  // *pThis_B++ 写入 0
  }
  fld_e13 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( fld_e13 != nullptr )  // 若 fld_e13 非空
    (**fld_e13)(fld_e13, 1);
  fld_e14 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;  // this+52 = 0
  if ( fld_e14 != nullptr )  // 若 fld_e14 非空
    (**fld_e14)(fld_e14, 1);
  fld_e15 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;  // this+56 = 0
  if ( fld_e15 != nullptr )  // 若 fld_e15 非空
    (**fld_e15)(fld_e15, 1);
  fld_e16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 16);  // this+16 频道型选中索引
  *(this + 15) = 0;  // this+60 = 0
  if ( fld_e16 != nullptr )  // 若 fld_e16 非空
    (**fld_e16)(fld_e16, 1);
  fld_e43 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 43);
  result = 0;
  *(this + 16) = 0;  // this+64 = 0
  if ( fld_e43 != nullptr )  // 若 fld_e43 非空
    result = (**fld_e43)(fld_e43, 1);
  *(this + 43) = 0;  // this+172 = 0
  return result;
}



// ------------------------------------------------------------
// 0x6415A0 CNRDFriendListWindow__vmtC —— CNRDFriendListWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDFriendListWindow__vmtC(uint32_t **this, int nArg2, int nArg3)  // 函数: CNRDFriendListWindow__vmtC 打开槽（69A5F0）
{
  dword_9B9530 = (int)this;
  sub_69A5F0(*(this + 2), 280, 55);  // 调 sub_69A5F0
  return 1;
}



// ------------------------------------------------------------
// 0x6415C0 CNRDFriendListWindow__vmt10 —— CNRDFriendListWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDFriendListWindow__vmt10()  // CNRDFriendListWindow__vmt10 状态切换槽（10 行）
{
  dword_9B9530 = 0;
}



// ------------------------------------------------------------
// 0x6415D0 sub_6415D0 —— 好友列表构建（25 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6415D0(uint32_t *this)  // 函数: 好友列表构建（25 行）
{
  int fld_e2; // eax
  int v2; // edx
  int v3; // ecx
  int result; // eax
  LONG i; // ecx

  fld_e2 = *(this + 2);  // fld_e2 = this+2
  v2 = *(uint32_t *)(fld_e2 + 20) + 11;  // fld_e2=this+8 物品 id
  v3 = *(uint32_t *)(fld_e2 + 24) + 38;  // fld_e2=this+8 物品 id
  result = 0;
  for ( i = v3 + 17; pt.x < v2 - 3 || pt.x >= v2 + 226 || pt.y < i - 18 || pt.y >= i; i += 18 )  // 循环：i = v3 + 17; pt.x < v2 - 3 || pt.x >= v2 + 226 || pt.y < i -
  {
    if ( ++result >= 8 )  // 若 ++result >= 8
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return result;
}



// ------------------------------------------------------------
// 0x641630 CNRDFriendListWindow__vmt8 —— CNRDFriendListWindow__vmt8 Update（CLICK_BUTTON2 + 69C690 + 479240/42B340 + 526BF0 私聊 + 527A60）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDFriendListWindow__vmt8(uint32_t *this)  // CNRDFriendListWindow__vmt8 Update（CLICK_BUTTON2 + 69C690 + 479240/42B340 + 526BF0 私聊 + 527A60）
{
  int fld_e10; // eax
  int fld_e2; // eax
  int v4; // ebx
  int fld_e45; // eax
  unsigned int fld_e46; // edi
  int fld_e14; // eax
  uint32_t *fld_e452; // eax
  int v9; // ecx
  int fld_e4; // edi
  int *v11; // eax
  void *v12; // eax
  uint32_t *pThis_B; // edi
  int i; // ebx
  int fld_e15; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));  // 调 sub_69A650
  fld_e10 = *(this + 10);  // fld_e10 = this+10
  if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 虚调用 vt+32
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  fld_e2 = *(this + 2);  // fld_e2 = this+2
  if ( *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e2 + 12) )  // 若 *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    v4 = sub_6415D0(this);  // 结果 = 好友列表构建
    if ( v4 != -1 )  // 若 v4 != -1
    {
      fld_e45 = *(this + 45);  // fld_e45 = this+45
      fld_e46 = fld_e45 != 0 ? (*(this + 46) - fld_e45) >> 2 : 0;  // fld_e45=this+180 半径/计数
      if ( v4 + sub_69C690(*(this + 14)) < fld_e46 )  // 取设备对象 +112 字段（类型或句柄）
      {
        fld_e14 = sub_69C690(*(this + 14));  // 结果 = 取设备对象 +112 字段（类型或句柄）
        fld_e452 = (uint32_t *)sub_479240((uint32_t *)dword_8F8510, *(uint32_t *)(*(this + 45) + 4 * (v4 + fld_e14)));
        v9 = fld_e452[12];
        if ( v9 != 0 )  // 若 v9 != 0
        {
          fld_e4 = *(uint32_t *)(*(this + 4) + 48);  // this+4 宿主对象
          v11 = (int *)sub_42B340(v9);  // 结果 = 虚拟角色惰性创建（0x294 字节）
          sub_526BF0(fld_e4, v11, 1);  // 调 sub_526BF0
        }
        else
        {
          if ( fld_e452[6] < 0x10u )  // 若 fld_e452[6] < 0x10u
            v12 = fld_e452 + 1;
          else
            v12 = (void *)fld_e452[1];
          sub_527A60(*(int ***)(*(this + 4) + 48), v12);  // 调 sub_527A60
        }
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
      }
    }
  }
  pThis_B = this + 11;
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    if ( *(uint8_t *)(*pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t *)(*pThis_B + 12) )  // 若 *(uint8_t *)(*pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t..
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    ++pThis_B;  // 自增pThis_B
  }
  fld_e15 = *(this + 15);  // fld_e15 = this+15
  if ( *(uint8_t *)(fld_e15 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e15 + 12) )  // 若 *(uint8_t *)(fld_e15 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    sub_44E8D0((char *)*(this + 4), (void *)9, 0, 0);  // 对象池借出（按池号取可用对象）
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  result = (uint8_t *)*(this + 16);  // this+16 频道型选中索引
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    sub_44E8D0((char *)*(this + 4), (void *)9, 0, 1);  // 对象池借出（按池号取可用对象）
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  return result;
}



// ------------------------------------------------------------
// 0x6417E0 sub_6417E0 —— 好友列表页绘制（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630 + 699E20/699E40，174 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6417E0(uint32_t *this)  // 函数: 好友列表页绘制（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630 + 699E20/699E40，174 行）
{
  uint32_t *pMem; // eax
  uint8_t *pMem72; // ebx
  uint32_t *fld_e9; // eax
  uint8_t *pMem2; // edi
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  uint32_t *pMem322; // eax
  uint8_t *pMem4; // eax
  uint8_t *fld_e11; // eax
  uint8_t *pMem5; // edi
  uint32_t *pMem52; // ecx
  uint8_t *pMem6; // edi
  uint32_t *pMem62; // ecx
  int dword_99FCCC; // ecx
  uint8_t *pMem7; // edi
  int v17; // edx
  void *Block; // [esp+10h] [ebp-18h]
  void *Blocka; // [esp+10h] [ebp-18h]
  void *Blockb; // [esp+10h] [ebp-18h]
  void *Blockc; // [esp+10h] [ebp-18h]
  void *Blockd; // [esp+10h] [ebp-18h]
  uint32_t *pThis_B; // [esp+14h] [ebp-14h]
  int dword_79C0B0; // [esp+14h] [ebp-14h]
  int v26; // [esp+18h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // 堆分配 132 字节对象
  pMem72 = nullptr;  // pMem72 = nullptr 空指针
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 23, 24, 25, 23, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 10) = fld_e9;  // this+40 = fld_e9
  sub_69A5F0(fld_e9, 230, 11);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 10));  // 调 sub_69A840
  v26 = 4;
  pThis_B = this + 11;
  do
  {
    pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
    if ( pMem2 != nullptr )  // 若 pMem2 非空
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(pMem2);  // nengine::IControl 构造
      *(uint32_t *)pMem2 = &nengine::CNButton::`vftable';
      sub_69C780((int)v5);  // 调 sub_69C780
      sub_69C7B0((int)v5, (int)Block, v26, v26, v26 + 1, v26, 0, 0);  // 调 sub_69C7B0
    }
    else
    {
      v5 = nullptr;  // v5 = nullptr 空指针
    }
    *v24++ = v5;  // *v24++ 写入 v5
    v26 += 2;
  }
  while ( v26 < 8 );  // 当 v26 < 8 循环
  v6 = operator new(0x88u);  // 堆分配 136 字节对象
  v7 = v6;
  if ( v6 != nullptr )  // 若 v6 非空
  {
    Blocka = (void *)*(this + 9);
    sub_426BD0(v6);  // nengine::IControl 构造
    *v7 = &nengine::CNSlider::`vftable';
    sub_69CA20((int)pMem32);  // 调 sub_69CA20
    sub_69CA50((int)pMem32, (int)Blocka, 151, 86);  // 调 sub_69CA50
    *pMem32 = &nengine::CNVSlider::`vftable';
    v8 = v7;
  }
  else
  {
    v8 = nullptr;  // v8 = nullptr 空指针
  }
  *(this + 13) = v8;  // this+52 = v8
  v9 = operator new(0x74u);  // 堆分配 116 字节对象
  if ( v9 != nullptr )  // 若 v9 非空
    v10 = sub_43C630(v9, *(this + 11), *(this + 12), *(this + 13));  // 结果 = nengine::CNVScroll 构造
  else
    v10 = nullptr;  // v10 = nullptr 空指针
  *(this + 14) = v10;  // this+56 = v10
  sub_69A5F0(v10, 239, 35);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 14));  // 调 sub_69A840
  v11 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( v11 != nullptr )  // 若 v11 非空
  {
    Blockb = (void *)*(this + 9);
    sub_426BD0(v11);  // nengine::IControl 构造
    *(uint32_t *)v11 = &nengine::CNButton::`vftable';
    sub_69C780((int)pMem5);  // 调 sub_69C780
    sub_69C7B0((int)pMem5, (int)Blockb, 144, 145, 146, 144, 0, 0);  // 调 sub_69C7B0
    pMem52 = pMem5;
  }
  else
  {
    pMem52 = nullptr;  // pMem52 = nullptr 空指针
  }
  *(this + 15) = pMem52;  // this+60 = pMem52
  sub_69A5F0(pMem52, 54, 202);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 15));  // 调 sub_69A840
  pMem6 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem6 != nullptr )  // 若 pMem6 非空
  {
    Blockc = (void *)*(this + 9);
    sub_426BD0(pMem6);  // nengine::IControl 构造
    *(uint32_t *)pMem6 = &nengine::CNButton::`vftable';
    sub_69C780((int)v13);  // 调 sub_69C780
    sub_69C7B0((int)v13, (int)Blockc, 147, 148, 149, 147, 0, 0);  // 调 sub_69C7B0
    v14 = v13;
  }
  else
  {
    v14 = nullptr;  // v14 = nullptr 空指针
  }
  *(this + 16) = v14;  // this+64 = v14
  sub_69A5F0(v14, 136, 202);  // 调 sub_69A5F0
  sub_69A840((uint32_t *)*(this + 2), *(this + 16));  // 调 sub_69A840
  *((uint8_t *)this + 68) = 0;  // this+68 角色数（begin/end 差 >>2；>=8 …
  *((uint8_t *)this + 69) = 0;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 71) = 0;  // this+71 移动类型
  *(this + 20) = 0;  // this+80 = 0
  *(this + 23) = 0;  // this+92 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  *(this + 28) = 0;  // this+112 = 0
  *(this + 29) = 0;  // this+116 = 0
  *(this + 22) = 12;  // this+88 = 12
  *(this + 24) = 1600;  // this+96 = 1600
  *(this + 21) = 6;  // this+84 = 6
  *(this + 29) = dword_99FCCC;  // this+116 = dword_99FCCC
  *(this + 18) = -16777216;  // this+72 = -16777216
  *((uint8_t *)this + 120) = 0;  // this+120 动画对象指针
  *((uint8_t *)this + 121) = 0;
  *((uint8_t *)this + 122) = 0;
  *((uint8_t *)this + 123) = 0;
  *(this + 33) = 0;  // this+132 = 0
  *(this + 34) = 6;  // this+136 = 6
  *(this + 35) = 12;  // this+140 = 12
  *(this + 36) = 0;  // this+144 = 0
  *(this + 37) = 1600;  // this+148 = 1600
  *(this + 38) = 0;  // this+152 = 0
  *(this + 39) = 0;  // this+156 = 0
  *(this + 40) = 0;  // this+160 = 0
  *(this + 41) = 0;  // this+164 = 0
  *(this + 42) = 0;  // this+168 = 0
  v15 = dword_99FCCC;
  *(this + 31) = -16777216;  // this+124 = -16777216
  *(this + 42) = v15;  // this+168 = v15
  *(this + 37) = 144;  // this+148 = 144
  *(this + 33) = 1;  // this+132 = 1
  *(this + 38) = 1;  // this+152 = 1
  v16 = operator new(0x2Cu);  // 堆分配 44 字节对象
  if ( v16 != nullptr )  // 若 v16 非空
  {
    Blockd = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 12);
    v25 = dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
    v16[4] = 0;
    *(uint32_t *)v16 = &nengine::CNNumberSet::`vftable';
    sub_699E20((int)pMem7);  // 调 sub_699E20
    sub_699E40((int)pMem7, dword_79C0B0, (int)Blockd, 25, 2);  // 调 sub_699E40
    pMem72 = pMem7;
  }
  v17 = *this;
  *(this + 43) = pMem72;  // this+172 = pMem72
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v17 + 24))(this, 20, 17);  // 调用虚函数槽 +24
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);  // 虚调用 vt+28
}


// ------------------------------------------------------------
// 0x641C00 sub_641C00 —— 好友数据重建（479110/479240/430C80，148 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_641C00(int this)  // 函数: 好友数据重建（479110/479240/430C80，148 行）
{
  int result; // eax
  void *fld_B4; // eax
  int pThis_B0; // esi
  int v4; // eax
  int v5; // edi
  int v6; // edx
  unsigned int v7; // ecx
  int *v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edx
  unsigned int v12; // ecx
  int *v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // edx
  unsigned int v17; // ecx
  int *v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v23; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h] BYREF

  result = dword_8F8510;
  if ( dword_8F8510 != 0 )  // 若 dword_8F8510 != 0
  {
    fld_B4 = *(void **)(this + 180);  // this+180 半径/计数
    pThis_B0 = this + 176;  // this+176 附属对象向量 cap
    if ( fld_B4 != nullptr )  // 若 fld_B4 非空
      j__free(fld_B4);  // 调 j__free
    *(uint32_t *)(pThis_B0 + 4) = 0;  // pThis_B0+4 = 0
    *(uint32_t *)(pThis_B0 + 8) = 0;  // pThis_B0+8 = 0
    *(uint32_t *)(pThis_B0 + 12) = 0;  // pThis_B0+12 = 0
    v4 = sub_479110(dword_8F8510);  // 调 sub_479110
    v5 = 0;
    v23 = v4;
    for ( i = 0; v5 < v23; i = v5 )  // 循环：i = 0; v5 < v23; i = v5
    {
      if ( *(uint32_t *)(sub_479240(v5) + 48) != 0 )  // 若 *(uint32_t *)(sub_479240(v5) + 48) != 0
      {
        v6 = *(uint32_t *)(pThis_B0 + 4);  // v6 = pThis_B0+4
        if ( v6 != 0 )  // 若 v6 != 0
          v7 = (*(uint32_t *)(pThis_B0 + 8) - v6) >> 2;  // pThis_B0=this+176 附属对象向量 cap
        else
          v7 = 0;
        if ( v6 != 0 && v7 < (*(uint32_t *)(pThis_B0 + 12) - v6) >> 2 )  // 若 v6 != 0 && v7 < (*(uint32_t *)(pThis_B0 + 12) - v6) >> 2
        {
          v8 = *(int **)(pThis_B0 + 8);  // pThis_B0=this+176 附属对象向量 cap
          *v8 = v5;  // *v8 写入 v5
          *(uint32_t *)(pThis_B0 + 8) = v8 + 1;  // pThis_B0+8 = v8 + 1
        }
        else
        {
          sub_430C80(*(void **)(pThis_B0 + 8), 1, (int)&i);  // uint32 vector 区间插入（同值填充）
        }
      }
      v4 = v23;
      ++v5;  // 自增v5
    }
    v9 = 0;
    i = 0;
    if ( v4 > 0 )  // 若 v4 > 0
    {
      do
      {
        v10 = sub_479240(v9);  // 调 sub_479240
        if ( *(int *)(v10 + 40) >= 0 && *(uint32_t *)(v10 + 48) == 0 )  // 若 *(int *)(v10 + 40) >= 0 && *(uint32_t *)(v10 + 48) == 0
        {
          v11 = *(uint32_t *)(pThis_B0 + 4);  // v11 = pThis_B0+4
          if ( v11 != 0 )  // 若 v11 != 0
            v12 = (*(uint32_t *)(pThis_B0 + 8) - v11) >> 2;  // pThis_B0=this+176 附属对象向量 cap
          else
            v12 = 0;
          if ( v11 != 0 && v12 < (*(uint32_t *)(pThis_B0 + 12) - v11) >> 2 )  // 若 v11 != 0 && v12 < (*(uint32_t *)(pThis_B0 + 12) - v11) >> 2
          {
            v13 = *(int **)(pThis_B0 + 8);  // pThis_B0=this+176 附属对象向量 cap
            *v13 = v9;  // *v13 写入 v9
            *(uint32_t *)(pThis_B0 + 8) = v13 + 1;  // pThis_B0+8 = v13 + 1
          }
          else
          {
            sub_430C80(*(void **)(pThis_B0 + 8), 1, (int)&i);  // uint32 vector 区间插入（同值填充）
          }
        }
        v4 = v23;
        i = ++v9;
      }
      while ( v9 < v23 );  // 当 v9 < v23 循环
    }
    v14 = 0;
    i = 0;
    if ( v4 > 0 )  // 若 v4 > 0
    {
      do
      {
        v15 = sub_479240(v14);  // 调 sub_479240
        if ( *(int *)(v15 + 40) < 0 && *(uint32_t *)(v15 + 48) == 0 )  // 若 *(int *)(v15 + 40) < 0 && *(uint32_t *)(v15 + 48) == 0
        {
          v16 = *(uint32_t *)(pThis_B0 + 4);  // v16 = pThis_B0+4
          if ( v16 != 0 )  // 若 v16 != 0
            v17 = (*(uint32_t *)(pThis_B0 + 8) - v16) >> 2;  // pThis_B0=this+176 附属对象向量 cap
          else
            v17 = 0;
          if ( v16 != 0 && v17 < (*(uint32_t *)(pThis_B0 + 12) - v16) >> 2 )  // 若 v16 != 0 && v17 < (*(uint32_t *)(pThis_B0 + 12) - v16) >> 2
          {
            v18 = *(int **)(pThis_B0 + 8);  // pThis_B0=this+176 附属对象向量 cap
            *v18 = v14;  // *v18 写入 v14
            *(uint32_t *)(pThis_B0 + 8) = v18 + 1;  // pThis_B0+8 = v18 + 1
          }
          else
          {
            sub_430C80(*(void **)(pThis_B0 + 8), 1, (int)&i);  // uint32 vector 区间插入（同值填充）
          }
        }
        i = ++v14;
      }
      while ( v14 < v23 );  // 当 v14 < v23 循环
    }
    v19 = *(uint32_t *)(pThis_B0 + 4);  // v19 = pThis_B0+4
    if ( v19 != 0 )  // 若 v19 != 0
      v20 = (*(uint32_t *)(pThis_B0 + 8) - v19) >> 2;  // pThis_B0=this+176 附属对象向量 cap
    else
      v20 = 0;
    if ( v20 - 8 >= 0 )  // 若 v20 - 8 >= 0
    {
      v21 = *(uint32_t *)(pThis_B0 + 4);  // v21 = pThis_B0+4
      if ( v21 != 0 )  // 若 v21 != 0
        return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(  // this+56 键盘输入使能
                 *(uint32_t *)(this + 56),  // this+56 键盘输入使能
                 ((*(uint32_t *)(pThis_B0 + 8) - v21) >> 2) - 8);  // pThis_B0=this+176 附属对象向量 cap
      else
        return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), -8);  // 调用虚函数槽 +32
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), 0);  // 调用虚函数槽 +32
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x641E10 CNRDFriendListWindow__vmt0 —— CNRDFriendListWindow__vmt0 构造（163 行：554930 + 641C00/6415D0/479240/42B340 + 69A110）
// ------------------------------------------------------------
int /*thiscall*/ sub_641E10(uint32_t *this, int pArg2)  // 【CNRDFriendListWindow__vmt0】
{
  int result; // eax
  int v4; // ebx
  int v5; // esi
  int pObj5; // eax
  int pObj2; // eax
  int v8; // ebx
  int fld_e14; // eax
  int pHostCtrl; // ecx
  int v11; // esi
  int v12; // esi
  int pObj3; // eax
  int fld_e45; // ecx
  uint32_t *fld_e452; // esi
  int v16; // ecx
  int pObj; // eax
  int pObj7; // eax
  uint32_t *v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int pObj6; // eax
  int pObj4; // eax
  int pObj8; // eax
  int v26; // [esp+8h] [ebp-18h]
  int v27; // [esp+Ch] [ebp-14h]
  int v28; // [esp+10h] [ebp-10h]
  int v29; // [esp+14h] [ebp-Ch]
  unsigned int fld_e142; // [esp+18h] [ebp-8h]
  int v31; // [esp+1Ch] [ebp-4h]
  int v32; // [esp+28h] [ebp+8h]

  result = sub_554930(pArg2);  // 【IRDPopupWindow__vmt0】
  if ( pArg2 == *(this + 2) )  // 若 pArg2 == *(this + 2)
  {
    sub_641C00(this);  // 好友数据重建
    v4 = *(uint32_t *)(pArg2 + 20);  // v4 = pArg2+20
    v5 = *(uint32_t *)(pArg2 + 24);  // v5 = pArg2+24
    pObj5 = sub_418DD0(143);  // 调 sub_418DD0
    if ( pObj5 != 0 )  // 若 pObj5 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v4 + 6, v5 + 6, dword_79C0B0);  // 调用虚函数槽 +152
    pObj2 = sub_418DD0(150);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v4 + 6, v5 + 32, dword_79C0B0);  // 调用虚函数槽 +152
    v8 = v4 + 11;
    v27 = v8;
    v32 = v5 + 38;
    fld_e14 = sub_69C690(*(this + 14));  // 结果 = 取设备对象 +112 字段（类型或句柄）
    pHostCtrl = *(this + 2);  // fld_e2 = this+2
    fld_e142 = fld_e14;
    if ( *(uint8_t *)(pHostCtrl + 17) != 0  // fld_e2=this+8 物品 id
      && ((v11 = *(uint32_t *)(pHostCtrl + 12), dword_79BE3C == v11) || dword_79BE34 == v11 || dword_79BE38 == v11) )  // CNRDFriendListWindow__vmt0 构造（163 行：554930 + 641C00/6415D0/479240/42B340 + 69A110）
    {
      v29 = sub_6415D0(this);  // 结果 = 好友列表构建
    }
    else
    {
      v29 = -1;
    }
    v12 = 0;
    v28 = 0;
    v31 = v32 + 3;
    do
    {
      pObj3 = sub_418DD0(94);  // 调 sub_418DD0
      if ( pObj3 != 0 )  // 若 pObj3 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v8, v32, dword_79C0B0);  // 调用虚函数槽 +152
      fld_e45 = *(this + 45);  // fld_e45 = this+45
      if ( fld_e45 != 0 && fld_e142 < (*(this + 46) - fld_e45) >> 2 )  // 若 fld_e45 != 0 && fld_e142 < (*(this + 46) - fld_e45) >> 2
      {
        fld_e452 = (uint32_t *)sub_479240(*(uint32_t *)(*(this + 45) + 4 * fld_e142));
        v16 = fld_e452[12];
        if ( v16 != 0 )  // 若 v16 != 0
        {
          pObj = sub_42B340(v16);  // 结果 = 虚拟角色惰性创建（0x294 字节）
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj + 384))(  // 虚槽+384 槽数组 getter（+348 起，越界返回 0）
            pObj,
            v8,
            v32,
            16,
            16,
            1065353216);
        }
        else
        {
          pObj7 = sub_418DD0(108);  // 调 sub_418DD0
          if ( pObj7 != 0 )  // 若 pObj7 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v8, v32, dword_79C0B0);  // 调用虚函数槽 +152
        }
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 17);  // 调用虚函数槽 +72
        (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          v8 + 23,
          v31,
          fld_e452[12] != 0 ? -4928551 : -8947849,
          "Lv.%d",  // 字符串 “Lv.%d”
          fld_e452[7]);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, this + 30);  // 调用虚函数槽 +68
        if ( fld_e452[6] < 0x10u )  // 若 fld_e452[6] < 0x10u
          v19 = fld_e452 + 1;
        else
          v19 = (uint32_t *)fld_e452[1];
        (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          v8 + 17,
          v31,
          fld_e452[12] != 0 ? -4928551 : -8947849,
          v19);
        v26 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
        v20 = sub_4B0EC0(fld_e452[8], fld_e452[9]);  // 结果 = 表记录字符串取值（28 字节/条）
        v8 = v27;
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v26 + 80))(
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          v27 + 96,
          v31,
          fld_e452[12] != 0 ? -8005942 : -9934744,
          v20);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
        v21 = fld_e452[12];
        if ( v21 != 0 )  // 若 v21 != 0
        {
          if ( *(uint32_t *)(v21 + 68) != 0 )  // 若 *(uint32_t *)(v21 + 68) != 0
            v22 = 154;
          else
            v22 = *(uint32_t *)(v21 + 184) != 0 ? 158 : 155;
          pObj6 = sub_418DD0(v22);  // 调 sub_418DD0
          if ( pObj6 != 0 )  // 若 pObj6 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v27 + 212, v32, dword_79C0B0);  // 调用虚函数槽 +152
        }
        else if ( (int)fld_e452[10] >= 0 )  // 否则若 (int)fld_e452[10] >= 0
        {
          pObj4 = sub_418DD0(155);  // 调 sub_418DD0
          if ( pObj4 != 0 )  // 若 pObj4 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v27 + 212, v32, dword_79C0B0);  // 调用虚函数槽 +152
          sub_69A110(v27 + 208, v31 + 1, fld_e452[10], -1);  // 调 sub_69A110
        }
        v12 = v28;
        if ( v28 == v29 )  // 若 v28 == v29
        {
          sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
          pObj8 = sub_418DD0(22);  // 调 sub_418DD0
          if ( pObj8 != 0 )  // 若 pObj8 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v27 - 3, v31 - 4, dword_79C0B0);  // 调用虚函数槽 +152
          sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
        }
      }
      ++v12;  // 自增v12
      ++fld_e142;  // 自增fld_e142
      result = 19;
      v28 = v12;
      v32 += 19;
      v31 += 19;
    }
    while ( v12 < 8 );  // 当 v12 < 8 循环
  }
  return result;
}


// ============================================================
// 【分区 4】PVP 房间列表窗 CNRDPVPRoomListWindow（0x6421A0-0x643210）
// vmt0 构造（204 行：642990 列表件 162 行 + 48F4C0/48FBB0）；
// vmt8 Update（4873D0/487420 进入房间）。
// ============================================================
// ------------------------------------------------------------
// 0x6421A0 sub_6421A0 —— PVP 房间列表数据（47 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6421A0(uint32_t *this)  // 函数: PVP 房间列表数据（47 行）
{
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e15)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e16)(uint32_t, int); // ecx

  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    result = (**fld_e10)(fld_e10, 1);
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;  // this+40 = 0
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  fld_e15 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e15 != nullptr )  // 若 fld_e15 非空
    result = (**fld_e15)(fld_e15, 1);
  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);  // this+12 物品类型号
  *(this + 15) = 0;  // this+60 = 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    result = (**fld_e12)(fld_e12, 1);
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 12) = 0;  // this+48 = 0
  if ( fld_e13 != nullptr )  // 若 fld_e13 非空
    result = (**fld_e13)(fld_e13, 1);
  fld_e14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;  // this+52 = 0
  if ( fld_e14 != nullptr )  // 若 fld_e14 非空
    result = (**fld_e14)(fld_e14, 1);
  fld_e16 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 16);  // this+16 频道型选中索引
  *(this + 14) = 0;  // this+56 = 0
  if ( fld_e16 != nullptr )  // 若 fld_e16 非空
    result = (**fld_e16)(fld_e16, 1);
  *(this + 16) = 0;  // this+64 = 0
  return result;
}



// ------------------------------------------------------------
// 0x642220 CNRDPVPRoomListWindow__vmt10 —— CNRDPVPRoomListWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDPVPRoomListWindow__vmt10()  // CNRDPVPRoomListWindow__vmt10 状态切换槽（10 行）
{
  dword_9B9534 = 0;
}



// ------------------------------------------------------------
// 0x642230 CNRDPVPRoomListWindow__vmt20 —— CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90/41D520 房间刷新）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPVPRoomListWindow__vmt20(void *this)  // 函数: CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90/41D520 房间刷新）
{
  if ( (uint8_t)sub_41C590(dword_8F7A24) != 1 )  // 状态查询（this+348 == 4）
    return IRDPopupWindow__vmt20(this);
  sub_46ED90(*(int **)(dword_8F7A24 + 36));  // reserveConnectionToConnectionHistory（按连接历史预约）
  return sub_41D520(dword_8F7A24);  // 切换到模块 5 的切换流程
}



// ------------------------------------------------------------
// 0x642270 sub_642270 —— PVP 房间列表条目（22 行）
// ------------------------------------------------------------
int sub_642270()  // PVP 房间列表条目
{
  LONG v0; // ecx
  int result; // eax

  v0 = 73;
  result = 0;
  while ( pt.x < 384 || pt.x >= 626 || pt.y < v0 || pt.y >= v0 + 20 )  // 当 pt.x < 384 || pt.x >= 626 || pt.y < v0 || pt.y >= v0 + 20 循环
  {
    ++result;  // 自增result
    v0 += 24;
    if ( result >= 12 )  // 若 result >= 12
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return result;
}



// ------------------------------------------------------------
// 0x6422B0 sub_6422B0 —— PVP 房间列表绘制件（69A5F0/69C980，50 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_6422B0(int this, uint8_t uArg2)  // 函数: PVP 房间列表绘制件（69A5F0/69C980，50 行）
{
  int fld_8; // ecx
  int fld_C4; // eax
  int v5; // edx
  int fld_82; // eax
  int v7; // edi
  int v8; // ebx
  int fld_34; // eax

  *(uint8_t *)(this + 196) = uArg2;  // this+196 = uArg2
  sub_69A5F0(*(uint32_t **)(this + 8), dword_73E0F4[2 * uArg2], dword_73E0F8[2 * uArg2]);  // 调 sub_69A5F0
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = this+8
  fld_C4 = 2 * *(uint8_t *)(this + 196);
  v5 = dword_73E108[fld_C4];
  *(uint32_t *)(fld_8 + 28) = dword_73E104[fld_C4];  // fld_8+28 = dword_73E104[fld_C4]
  *(uint32_t *)(fld_8 + 32) = v5;  // fld_8+32 = v5
  fld_82 = *(uint32_t *)(this + 8);  // fld_82 = this+8
  v7 = *(uint32_t *)(fld_82 + 20);  // v7 = fld_82+20
  v8 = *(uint32_t *)(fld_82 + 24);  // v8 = fld_82+24
  if ( uArg2 != 0 )  // 若 uArg2 != 0
  {
    sub_69C980(*(uint32_t *)(this + 36), 256, 257, 258, -1, 0, 0);  // 调 sub_69C980
    sub_69A5F0(*(uint32_t **)(this + 40), v7 + 15, v8 + 47);  // 调 sub_69A5F0
    sub_69A5F0(*(uint32_t **)(this + 48), v7 + 141, v8 + 46);  // 调 sub_69A5F0
    sub_69A5F0(*(uint32_t **)(this + 44), v7 + 240, v8 + 15);  // 调 sub_69A5F0
    sub_69A5F0(*(uint32_t **)(this + 60), v7 + 60, v8 + 46);  // 调 sub_69A5F0
    fld_34 = *(uint32_t *)(this + 52);  // fld_34 = this+52
    *(uint8_t *)(fld_34 + 16) = 0;  // fld_34+16 = 0
    *(uint8_t *)(*(uint32_t *)(this + 56) + 16) = 0;  // this+56 键盘输入使能
  }
  else
  {
    sub_69C980(*(uint32_t *)(this + 36), 253, 254, 255, -1, 0, 0);  // 调 sub_69C980
    sub_69A5F0(*(uint32_t **)(this + 40), v7 + 15, v8 + 362);  // 调 sub_69A5F0
    sub_69A5F0(*(uint32_t **)(this + 48), v7 + 141, v8 + 361);  // 调 sub_69A5F0
    sub_69A5F0(*(uint32_t **)(this + 44), v7 + 240, v8 + 15);  // 调 sub_69A5F0
    sub_69A5F0(*(uint32_t **)(this + 60), v7 + 60, v8 + 361);  // 调 sub_69A5F0
    *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 1;  // this+52 光环状态字节
    *(uint8_t *)(*(uint32_t *)(this + 56) + 16) = 1;  // this+56 键盘输入使能
    LOBYTE(fld_34) = 1;  // fld_34=this+52 光环状态字节
  }
  return fld_34;  // fld_34=this+52 光环状态字节
}



// ------------------------------------------------------------
// 0x642410 sub_642410 —— PVP 房间列表数据 2（14 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_642410(uint32_t *this, char pszArg2)  // 函数: PVP 房间列表数据 2（14 行）
{
  int result; // eax

  result = *(this + 15);  // result = this+15
  *(uint8_t *)(result + 17) = pszArg2;  // result+17 = pszArg2
  return result;  // result=this+60 fade 值
}



// ------------------------------------------------------------
// 0x642420 sub_642420 —— PVP 房间列表页绘制（43C410/69A840/69A5F0 + 423B30 + 6422B0，127 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_642420(int this)  // 函数: PVP 房间列表页绘制（43C410/69A840/69A5F0 + 423B30 + 6422B0，127 行）
{
  uint32_t *pMem; // eax
  uint32_t *fld_24; // eax
  uint32_t *fld_8; // ecx
  uint32_t *pMem2; // eax
  uint32_t *fld_242; // eax
  uint32_t *fld_82; // ecx
  uint32_t *pMem3; // eax
  uint32_t *fld_243; // eax
  uint32_t *fld_83; // ecx
  uint32_t *pMem4; // eax
  uint32_t *fld_244; // eax
  uint32_t *fld_84; // ecx
  uint32_t *pMem5; // eax
  uint32_t *fld_245; // eax
  uint32_t *pMem6; // eax
  uint32_t *fld_246; // eax
  uint8_t *pMem7; // eax
  uint8_t *fld_247; // eax
  int dword_99FCCC2; // edx

  *(uint32_t *)(this + 36) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_24 = sub_43C410(pMem, *(uint32_t *)(this + 36), 253, 254, 255, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_24 = nullptr;  // fld_24 = nullptr 空指针
  fld_8 = *(uint32_t **)(this + 8);  // this+8 物品 id
  *(uint32_t *)(this + 44) = fld_24;  // this+44 = fld_24
  sub_69A840(fld_8, (int)fld_24);  // 调 sub_69A840
  pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_242 = sub_43C410(pMem2, *(uint32_t *)(this + 36), 284, 285, 286, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_242 = nullptr;  // fld_242 = nullptr 空指针
  fld_82 = *(uint32_t **)(this + 8);  // this+8 物品 id
  *(uint32_t *)(this + 40) = fld_242;  // this+40 = fld_242
  sub_69A840(fld_82, (int)fld_242);  // 调 sub_69A840
  pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem3 != nullptr )  // 若 pMem3 非空
    fld_243 = sub_43C410(pMem3, *(uint32_t *)(this + 36), 247, 248, 249, -1, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_243 = nullptr;  // fld_243 = nullptr 空指针
  fld_83 = *(uint32_t **)(this + 8);  // this+8 物品 id
  *(uint32_t *)(this + 48) = fld_243;  // this+48 = fld_243
  sub_69A840(fld_83, (int)fld_243);  // 调 sub_69A840
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem4 != nullptr )  // 若 pMem4 非空
    fld_244 = sub_43C410(pMem4, *(uint32_t *)(this + 36), 287, 288, 289, 287, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_244 = nullptr;  // fld_244 = nullptr 空指针
  fld_84 = *(uint32_t **)(this + 8);  // this+8 物品 id
  *(uint32_t *)(this + 60) = fld_244;  // this+60 = fld_244
  sub_69A840(fld_84, (int)fld_244);  // 调 sub_69A840
  pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
    fld_245 = sub_43C410(pMem5, *(uint32_t *)(this + 36), 76, 77, 78, 76, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_245 = nullptr;  // fld_245 = nullptr 空指针
  *(uint32_t *)(this + 52) = fld_245;  // this+52 = fld_245
  sub_69A5F0(fld_245, 110, 340);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t **)(this + 8), *(uint32_t *)(this + 52));  // 调 sub_69A840
  pMem6 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem6 != nullptr )  // 若 pMem6 非空
    fld_246 = sub_43C410(pMem6, *(uint32_t *)(this + 36), 79, 80, 81, 79, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_246 = nullptr;  // fld_246 = nullptr 空指针
  *(uint32_t *)(this + 56) = fld_246;  // this+56 = fld_246
  sub_69A5F0(fld_246, 150, 340);  // 调 sub_69A5F0
  sub_69A840(*(uint32_t **)(this + 8), *(uint32_t *)(this + 56));  // 调 sub_69A840
  pMem7 = operator new(0x2Cu);  // 堆分配 44 字节对象
  if ( pMem7 != nullptr )  // 若 pMem7 非空
    fld_247 = sub_423B30(pMem7, dword_79C0B0, *(uint32_t *)(this + 36), 51, 3);  // 结果 = CNNumberSet 构造
  else
    fld_247 = nullptr;  // fld_247 = nullptr 空指针
  *(uint32_t *)(this + 64) = fld_247;  // this+64 = fld_247
  fld_247[24] = 1;
  *(uint8_t *)(this + 68) = 0;  // this+68 = 0
  *(uint8_t *)(this + 69) = 0;  // this+69 = 0
  *(uint8_t *)(this + 70) = 0;  // this+70 = 0
  *(uint8_t *)(this + 71) = 0;  // this+71 = 0
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 6;  // this+84 = 6
  *(uint32_t *)(this + 88) = 12;  // this+88 = 12
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint32_t *)(this + 96) = 1600;  // this+96 = 1600
  *(uint32_t *)(this + 116) = dword_99FCCC;  // this+116 = dword_99FCCC
  *(uint32_t *)(this + 96) = 100;  // this+96 = 100
  *(uint32_t *)(this + 80) = 1;  // this+80 = 1
  *(uint32_t *)(this + 100) = 1;  // this+100 = 1
  *(uint32_t *)(this + 72) = -16777216;  // this+72 = -16777216
  *(uint8_t *)(this + 120) = 0;  // this+120 = 0
  *(uint8_t *)(this + 121) = 0;  // this+121 = 0
  *(uint8_t *)(this + 122) = 0;  // this+122 = 0
  *(uint8_t *)(this + 123) = 0;  // this+123 = 0
  *(uint32_t *)(this + 132) = 0;  // this+132 = 0
  *(uint32_t *)(this + 136) = 6;  // this+136 = 6
  *(uint32_t *)(this + 140) = 12;  // this+140 = 12
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint32_t *)(this + 148) = 1600;  // this+148 = 1600
  *(uint32_t *)(this + 152) = 0;  // this+152 = 0
  *(uint32_t *)(this + 156) = 0;  // this+156 = 0
  *(uint32_t *)(this + 160) = 0;  // this+160 = 0
  *(uint32_t *)(this + 164) = 0;  // this+164 = 0
  *(uint32_t *)(this + 168) = 0;  // this+168 = 0
  dword_99FCCC2 = dword_99FCCC;
  *(uint32_t *)(this + 124) = -16777216;  // this+124 = -16777216
  *(uint32_t *)(this + 168) = dword_99FCCC2;  // this+168 = dword_99FCCC2
  *(uint32_t *)(this + 148) = 144;  // this+148 = 144
  *(uint32_t *)(this + 132) = 1;  // this+132 = 1
  *(uint32_t *)(this + 152) = 1;  // this+152 = 1
  sub_6422B0(0);  // PVP 房间列表绘制件
  *(uint8_t *)(this + 225) = 0;  // this+225 = 0
  *(uint8_t *)(this + 226) = 0;  // this+226 = 0
  return sub_698F90(this + 212, 5000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}


// ------------------------------------------------------------
// 0x642770 sub_642770 —— 房间列表文本（4014D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_642770(uint32_t *this, uint32_t *pArg2)  // 房间列表文本（4014D0）
{
  qmemcpy(this, pArg2, 0x4Cu);  // 调 qmemcpy 内联块拷贝
  sub_4014D0((std::_String_base *)(this + 19), pArg2 + 19, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径
  *(this + 26) = pArg2[26];  // this+104 = pArg2[26]
  *(this + 27) = pArg2[27];  // this+108 = pArg2[27]
  *(this + 28) = pArg2[28];  // this+112 = pArg2[28]
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x6427C0 sub_6427C0 —— 转发 642770
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6427C0(uint32_t *this, int pArg2)  // 转发 642770
{
  sub_642770(this + 1, (uint32_t *)(pArg2 + 4));  // 房间列表文本（4014D0）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x6427E0 sub_6427E0 —— 房间操作（4875C0）
// ------------------------------------------------------------
void */*thiscall*/ sub_6427E0(void **this, int *pDwArg2, int nArg3)  // 房间操作（4875C0）
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);  // Block = this+1
  v3 = *((uint8_t *)pDwArg2 + 137);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )  // 若 v3 == 0
  {
    fld_e1 = (uint32_t *)sub_4875C0(*(this + 1), nArg3, *(this + 1), pDwArg2 + 3, *((uint8_t *)pDwArg2 + 136));  // 结果 = 红黑树节点分配（0x8C 字节 · 内嵌房间对象）
    if ( *((uint8_t *)Block + 137) != 0 )  // 若 *((uint8_t *)Block + 137) != 0
      Block = fld_e1;  // Block=this+4 宿主对象
    v6 = *pDwArg2;
    v10 = 0;
    *fld_e1 = sub_6427E0(v6, fld_e1);  // 结果 = 房间操作（4875C0）
    fld_e1[2] = sub_6427E0(pDwArg2[2], fld_e1);  // 结果 = 房间操作（4875C0）
  }
  return Block;  // Block=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x6428A0 sub_6428A0 —— 房间操作 2（436CA0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6428A0(int this)  // 房间操作 2（436CA0）
{
  int pThis_C8; // esi
  uint32_t *result; // eax

  pThis_C8 = this + 200;  // this+200 主状态（0x5DE690: dword_8F7C…
  *(uint32_t *)(this + 36) = 0;  // this+36 = 0
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  *(uint32_t *)(this + 56) = 0;  // this+56 = 0
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 188) = 0;  // this+188 = 0
  *(uint32_t *)(this + 192) = 0;  // this+192 = 0
  *(uint8_t *)(this + 196) = 0;  // this+196 = 0
  sub_436CA0(*(void ***)(*(uint32_t *)(this + 204) + 4));  // 红黑树递归销毁（CNPvpRoom 值版）
  *(uint32_t *)(*(uint32_t *)(pThis_C8 + 4) + 4) = *(uint32_t *)(pThis_C8 + 4);  // pThis_C8=this+200 主状态（0x5DE690: dword_8F7C…
  result = *(uint32_t **)(pThis_C8 + 4);  // pThis_C8=this+200 主状态（0x5DE690: dword_8F7C…
  *(uint32_t *)(pThis_C8 + 8) = 0;  // pThis_C8+8 = 0
  *result = result;  // *result 写入 result
  *(uint32_t *)(*(uint32_t *)(pThis_C8 + 4) + 8) = *(uint32_t *)(pThis_C8 + 4);  // pThis_C8=this+200 主状态（0x5DE690: dword_8F7C…
  return result;
}



// ------------------------------------------------------------
// 0x642900 sub_642900 —— 房间列表刷新（6427E0，46 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_642900(int this, int pArg2)  // 房间列表刷新
{
  int fld_4; // edi
  int **fld_42; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_43; // esi
  int **v8; // ecx

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
  *(uint32_t *)(fld_4 + 4) = sub_6427E0((void **)this, *(int **)(*(uint32_t *)(pArg2 + 4) + 4), fld_4);  // 房间操作（4875C0）
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);  // this+8 = *(uint32_t *)(pArg2 + 8)
  fld_42 = *(int ***)(this + 4);  // this+4 宿主对象
  result = fld_42[1];  // fld_42=this+4 宿主对象
  if ( *((uint8_t *)result + 137) != 0 )  // 若 *((uint8_t *)result + 137) != 0
  {
    *fld_42 = (int *)fld_42;  // *fld_42 写入 (int *)fld_42
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);  // this+4 宿主对象 等2字段
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 137) == 0 )  // 若 *(uint8_t *)(*result + 137) == 0
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 137) == 0 );  // 当 *((uint8_t *)v6 + 137) == 0 循环
    }
    *fld_42 = result;  // *fld_42 写入 result
    fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
    v8 = *(int ***)(fld_43 + 4);  // fld_43=this+4 宿主对象
    for ( result = v8[2]; *((uint8_t *)result + 137) == 0; result = (int *)result[2] )  // 循环：result = v8[2]; *((uint8_t *)result + 137) == 0; result = (i
      v8 = (int **)result;
    *(uint32_t *)(fld_43 + 8) = v8;  // fld_43+8 = v8
  }
  return result;
}



// ------------------------------------------------------------
// 0x642990 sub_642990 —— PVP 房间列表重建（162 行：699000/698F90 + 438820/642900/430C80/4332F0/44E850）
// ------------------------------------------------------------
int /*thiscall*/ sub_642990(int this, uint32_t *uArg2)  // 函数: PVP 房间列表重建（162 行：699000/698F90 + 438820/642900/430C80/4332F0/44E850）
{
  int fld_EC; // ebx
  int result; // eax
  int pThis_AC; // esi
  int v6; // ebx
  int pThis_C8; // edi
  int pThis; // edi
  uint32_t *fld_CC; // ecx
  uint32_t *uArg22; // eax
  int v11; // ecx
  uint32_t *v12; // edi
  unsigned int v13; // edx
  uint32_t *v14; // eax
  uint32_t *v15; // ecx
  uint32_t *uArg23; // eax
  int v17; // ecx
  uint32_t *v18; // edi
  unsigned int v19; // edx
  uint32_t *v20; // eax
  uint32_t *v21; // ecx
  uint32_t *v22; // eax
  int v23; // ecx
  int v24; // eax
  int v25; // eax
  int v26; // esi
  bool v27; // cc

  if ( (uint8_t)uArg2 == 0 )  // 若 (uint8_t)uArg2 == 0
  {
    fld_EC = *(uint32_t *)(this + 236);  // fld_EC = this+236
    result = sub_699000(this + 212);  // 【clock_now(clk)】
    if ( result < fld_EC )  // 若 result < fld_EC
      return result;
    *(uint8_t *)(this + 225) = 0;  // this+225 = 0
    *(uint8_t *)(this + 226) = 0;  // this+226 = 0
    sub_698F90(this + 212, 5000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  pThis_AC = this + 172;  // this+172 附属对象向量 end
  if ( *(uint32_t *)(this + 176) != 0 )  // 若 *(uint32_t *)(this + 176) != 0
    j__free(*(void **)(this + 176));  // 调 j__free
  *(uint32_t *)(this + 176) = 0;  // this+176 = 0
  *(uint32_t *)(this + 180) = 0;  // this+180 = 0
  *(uint32_t *)(this + 184) = 0;  // this+184 = 0
  v6 = dword_8F8504 + 4;
  pThis_C8 = this + 200;  // this+200 主状态（0x5DE690: dword_8F7C…
  if ( pThis_C8 != dword_8F8504 + 4 )  // 若 pThis_C8 != dword_8F8504 + 4
  {
    sub_438820(&uArg2, **(uint32_t **)(pThis_C8 + 4), *(uint32_t *)(pThis_C8 + 4));  // map 区间擦除（CNPvpRoom 值版）
    sub_642900(v6);  // 房间列表刷新
  }
  pThis = this;
  fld_CC = *(uint32_t **)(this + 204);  // this+204 子动画链指针
  uArg22 = (uint32_t *)*fld_CC;  // fld_CC=this+204 子动画链指针
  uArg2 = (uint32_t *)*fld_CC;  // fld_CC=this+204 子动画链指针
  if ( uArg2 != fld_CC )  // 若 uArg2 != fld_CC
  {
    do
    {
      if ( uArg22[22] == 1 )  // 若 uArg22[22] == 1
      {
        v11 = *(uint32_t *)(pThis_AC + 4);  // v11 = pThis_AC+4
        v12 = uArg22 + 3;
        if ( v11 != 0 )  // 若 v11 != 0
          v13 = (*(uint32_t *)(pThis_AC + 8) - v11) >> 2;  // pThis_AC=this+172 附属对象向量 end
        else
          v13 = 0;
        if ( v11 != 0 && v13 < (*(uint32_t *)(pThis_AC + 12) - v11) >> 2 )  // 若 v11 != 0 && v13 < (*(uint32_t *)(pThis_AC + 12) - v11) >> 2
        {
          v14 = *(uint32_t **)(pThis_AC + 8);  // pThis_AC=this+172 附属对象向量 end
          *v14 = *v12;  // *v14 写入 *v12
          *(uint32_t *)(pThis_AC + 8) = v14 + 1;  // pThis_AC+8 = v14 + 1
        }
        else
        {
          sub_430C80(*(void **)(pThis_AC + 8), 1, (int)v12);  // uint32 vector 区间插入（同值填充）
        }
        pThis = this;
      }
      sub_4332F0(&uArg2);  // 红黑树迭代器自增（后继）
      uArg22 = uArg2;
    }
    while ( uArg2 != *(uint32_t **)(pThis + 204) );  // 当 uArg2 != *(uint32_t **)(pThis + 204) 循环
  }
  v15 = *(uint32_t **)(pThis + 204);
  uArg23 = (uint32_t *)*v15;
  uArg2 = (uint32_t *)*v15;
  if ( uArg2 != v15 )  // 若 uArg2 != v15
  {
    do
    {
      if ( uArg23[22] == 2 )  // 若 uArg23[22] == 2
      {
        v17 = *(uint32_t *)(pThis_AC + 4);  // v17 = pThis_AC+4
        v18 = uArg23 + 3;
        if ( v17 != 0 )  // 若 v17 != 0
          v19 = (*(uint32_t *)(pThis_AC + 8) - v17) >> 2;  // pThis_AC=this+172 附属对象向量 end
        else
          v19 = 0;
        if ( v17 != 0 && v19 < (*(uint32_t *)(pThis_AC + 12) - v17) >> 2 )  // 若 v17 != 0 && v19 < (*(uint32_t *)(pThis_AC + 12) - v17) >> 2
        {
          v20 = *(uint32_t **)(pThis_AC + 8);  // pThis_AC=this+172 附属对象向量 end
          *v20 = *v18;  // *v20 写入 *v18
          *(uint32_t *)(pThis_AC + 8) = v20 + 1;  // pThis_AC+8 = v20 + 1
        }
        else
        {
          sub_430C80(*(void **)(pThis_AC + 8), 1, (int)v18);  // uint32 vector 区间插入（同值填充）
        }
        pThis = this;
      }
      sub_4332F0(&uArg2);  // 红黑树迭代器自增（后继）
      uArg23 = uArg2;
    }
    while ( uArg2 != *(uint32_t **)(pThis + 204) );  // 当 uArg2 != *(uint32_t **)(pThis + 204) 循环
  }
  if ( dword_795D3C != -1 )  // 若 dword_795D3C != -1
  {
    v21 = *(uint32_t **)(pThis + 180);
    v22 = *(uint32_t **)(pThis + 176);
    if ( v22 == v21 )  // 若 v22 == v21
      goto LABEL_35;  // 跳转 LABEL_35
    do
    {
      if ( *v22 == dword_795D3C )  // 若 *v22 == dword_795D3C
        break;
      ++v22;  // 自增v22
    }
    while ( v22 != v21 );  // 当 v22 != v21 循环
    if ( v22 == v21 )  // 若 v22 == v21
LABEL_35:
      sub_44E850(*(uint32_t **)(pThis + 16), 3);  // 按池号批量回收活动对象
  }
  v23 = *(uint32_t *)(pThis_AC + 4);  // v23 = pThis_AC+4
  if ( v23 != 0 )  // 若 v23 != 0
    v24 = (*(uint32_t *)(pThis_AC + 8) - v23) >> 2;  // pThis_AC=this+172 附属对象向量 end
  else
    v24 = 0;
  if ( (v24 - 1) / 12 <= 0 )  // 若 (v24 - 1) / 12 <= 0
  {
    result = 0;
  }
  else
  {
    v25 = *(uint32_t *)(pThis_AC + 4);  // v25 = pThis_AC+4
    if ( v25 != 0 )  // 若 v25 != 0
      v26 = (*(uint32_t *)(pThis_AC + 8) - v25) >> 2;  // pThis_AC=this+172 附属对象向量 end
    else
      v26 = 0;
    result = (v26 - 1) / 12;
  }
  v27 = *(uint32_t *)(pThis + 188) <= result;
  *(uint32_t *)(pThis + 192) = result;  // pThis+192 = result
  if ( !v27 )  // 若 !v27
    *(uint32_t *)(pThis + 188) = result;  // pThis+188 = result
  return result;
}


// ------------------------------------------------------------
// 0x642BC0 CNRDPVPRoomListWindow__vmt8 —— CNRDPVPRoomListWindow__vmt8 Update（108 行：CLICK_BUTTON2 + 4873D0/487420 进入 + 642990 重建）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPVPRoomListWindow__vmt8(void *this)  // CNRDPVPRoomListWindow__vmt8 Update（108 行：CLICK_BUTTON2 + 4873D0/487420 进入 + 642990 重建）
{
  int pThis_2; // eax
  int v3; // eax
  int pThis_2C; // edx
  unsigned int pThis_2D; // ecx
  unsigned int pThis_2F; // eax
  int pThis_2C2; // edi
  int v8; // ebx
  int v9; // eax
  int pThis_B; // eax
  int pThis_C; // eax
  int pThis_D; // eax
  int pThis_2F2; // eax
  int pThis_E; // eax
  int pThis_2F3; // eax
  int pThis_A; // eax
  uint8_t *result; // eax
  int v18; // [esp+4h] [ebp-Ch] BYREF
  int pThis_2C22; // [esp+8h] [ebp-8h] BYREF
  uint8_t v20[4]; // [esp+Ch] [ebp-4h] BYREF

  pThis_2 = *((uint32_t *)this + 2);  // pThis_2=this+8 物品 id
  if ( *(uint8_t *)(pThis_2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_2 + 12) )  // 若 *(uint8_t *)(pThis_2 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    v3 = sub_642270();  // 结果 = PVP 房间列表条目
    if ( v3 != -1 )  // 若 v3 != -1
    {
      pThis_2C = *((uint32_t *)this + 44);  // this+44 剩余时间 ms
      pThis_2D = pThis_2C != 0 ? (*((uint32_t *)this + 45) - pThis_2C) >> 2 : 0;  // pThis_2C=this+176 附属对象向量 cap
      pThis_2F = v3 + 12 * *((uint32_t *)this + 47);
      if ( pThis_2F < pThis_2D )  // 若 pThis_2F < pThis_2D
      {
        pThis_2C2 = *(uint32_t *)(*((uint32_t *)this + 44) + 4 * pThis_2F);  // this+44 剩余时间 ms
        pThis_2C22 = pThis_2C2;
        sub_4873D0(&v18, &pThis_2C22);  // 红黑树查找定位（回传命中节点或哨兵）
        v8 = v18;
        if ( v18 != *((uint32_t *)this + 51) )  // 若 v18 != *((uint32_t *)this + 51)
        {
          v9 = sub_487420(pThis_2C2);  // 结果 = 按键取节点载荷（未命中返回 0）
          if ( v9 != 0 )  // 若 v9 != 0
          {
            sub_6427C0((uint32_t *)(v8 + 16), v9);  // 转发 642770
            sub_44E8D0(*((char **)this + 4), (void *)3, 0, pThis_2C2);  // 对象池借出（按池号取可用对象）
            sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
          }
        }
      }
    }
  }
  pThis_B = *((uint32_t *)this + 11);  // pThis_B=this+44 剩余时间 ms
  if ( *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_B + 12) )  // 若 *(uint8_t *)(pThis_B + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    sub_6422B0((int)this, *((uint8_t *)this + 196) == 0);  // PVP 房间列表绘制件
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  pThis_C = *((uint32_t *)this + 12);  // this+12 物品类型号
  if ( *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_C + 12) )  // 若 *(uint8_t *)(pThis_C + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    sub_44E8D0(*((char **)this + 4), (void *)4, 0, 0);  // 对象池借出（按池号取可用对象）
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  pThis_D = *((uint32_t *)this + 13);  // pThis_D=this+52 光环状态字节
  if ( *(uint8_t *)(pThis_D + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_D + 12) )  // 若 *(uint8_t *)(pThis_D + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    pThis_2F2 = *((uint32_t *)this + 47);  // pThis_2F2=this+188 状态槽索引
    if ( pThis_2F2 > 0 )  // 若 pThis_2F2 > 0
    {
      *((uint32_t *)this + 47) = pThis_2F2 - 1;  // this+188 = pThis_2F2 - 1
      sub_642990((int)this, (uint32_t *)1);  // PVP 房间列表重建
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    }
  }
  pThis_E = *((uint32_t *)this + 14);  // pThis_E=this+56 键盘输入使能
  if ( *(uint8_t *)(pThis_E + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_E + 12) )  // 若 *(uint8_t *)(pThis_E + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    pThis_2F3 = *((uint32_t *)this + 47);  // pThis_2F3=this+188 状态槽索引
    if ( pThis_2F3 < *((uint32_t *)this + 48) )  // 若 pThis_2F3 < *((uint32_t *)this + 48)
    {
      *((uint32_t *)this + 47) = pThis_2F3 + 1;  // this+188 = pThis_2F3 + 1
      sub_642990((int)this, (uint32_t *)1);  // PVP 房间列表重建
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    }
  }
  pThis_A = *((uint32_t *)this + 10);  // pThis_A=this+40 物品状态附属标志
  if ( *(uint8_t *)(pThis_A + 17) != 0 && dword_79BE34 == *(uint32_t *)(pThis_A + 12) )  // 若 *(uint8_t *)(pThis_A + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);  // 调用虚函数槽 +32
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  result = *((uint8_t **)this + 15);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 若 result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3)
  {
    sub_423200(dword_8F7B08, 101);  // 【发送网络包API】
    v20[0] = 0;
    sub_423290(dword_8F7B08, (int)v20, 1);  // 调 sub_423290
    sub_423380(dword_8F7B08);  // 发包提交：Commit()
    *(uint8_t *)(*((uint32_t *)this + 15) + 17) = 0;
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  return result;
}



// ------------------------------------------------------------
// 0x642E20 CNRDPVPRoomListWindow__vmtC —— CNRDPVPRoomListWindow__vmtC 打开槽（642990 + 6422B0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPRoomListWindow__vmtC(void *this, int nArg2, int nArg3)  // 函数: CNRDPVPRoomListWindow__vmtC 打开槽（642990 + 6422B0）
{
  dword_9B9534 = (int)this;
  sub_642990((int)this, (uint32_t *)1);  // PVP 房间列表重建
  sub_6422B0((int)this, 0);  // PVP 房间列表绘制件
  return 1;
}



// ------------------------------------------------------------
// 0x642E40 CNRDPVPRoomListWindow__vmt0 —— CNRDPVPRoomListWindow__vmt0 构造（204 行：642990/642270 + 69A110 + 48F4C0/48FBB0）
// ------------------------------------------------------------
int /*userpurge*/ sub_642E40@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int pArg3)  // 函数: CNRDPVPRoomListWindow__vmt0 构造（204 行：642990/642270 + 69A110 + 48F4C0/48FBB0）
{
  int result; // eax
  int v5; // edi
  int pObj3; // eax
  int v7; // ebx
  int i; // edi
  int pObj; // eax
  int v10; // ecx
  char v11; // al
  unsigned int v12; // ebx
  int v13; // edi
  int pObj5; // eax
  int v15; // ecx
  int *v16; // ecx
  int *v17; // eax
  uint32_t *v18; // edx
  int *v19; // eax
  int *v20; // eax
  int v21; // edi
  int v22; // eax
  uint32_t *v23; // edi
  int v24; // eax
  int v25; // eax
  int pObj2; // eax
  int v27; // eax
  int v28; // eax
  int pObj4; // eax
  bool v30; // cc
  int v32; // [esp+8h] [ebp-20h]
  int v33; // [esp+Ch] [ebp-1Ch]
  int *v34; // [esp+10h] [ebp-18h] BYREF
  int *v35; // [esp+14h] [ebp-14h] BYREF
  int v36; // [esp+18h] [ebp-10h]
  unsigned int v37; // [esp+1Ch] [ebp-Ch]
  int v38; // [esp+20h] [ebp-8h]
  int v39; // [esp+24h] [ebp-4h]
  int v40; // [esp+30h] [ebp+8h]

  result = *(uint32_t *)(pArg1 + 8);  // result = pArg1+8
  if ( pArg3 == result )  // 若 pArg3 == result
  {
    sub_642990(0);  // PVP 房间列表重建
    v5 = *(uint32_t *)(pArg3 + 24);  // v5 = pArg3+24
    v39 = *(uint32_t *)(pArg3 + 20);  // v39 = pArg3+20
    v33 = v5;
    pObj3 = sub_418DD0(244);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v39, v5, dword_79C0B0);  // 调用虚函数槽 +152
    v7 = *(uint32_t *)(sub_418DD0(244) + 24) + v5;  // 调 资源句柄 (101)
    if ( *(uint8_t *)(pArg1 + 196) == 0 )  // 若 *(uint8_t *)(pArg1 + 196) == 0
    {
      for ( i = 21; i != 0; --i )  // 循环：i = 21; i != 0; --i
      {
        pObj = sub_418DD0(245);  // 调 sub_418DD0
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v39, v7, dword_79C0B0);  // 调用虚函数槽 +152
        v7 += *(uint32_t *)(sub_418DD0(245) + 24);  // 调 资源句柄 (101)
      }
      v10 = *(uint32_t *)(pArg1 + 8);  // v10 = pArg1+8
      v32 = v7;
      v11 = *(uint8_t *)(v10 + 17);  // v11 = v10+17
      v12 = 12 * *(uint32_t *)(pArg1 + 188);
      v37 = v12;
      if ( v11 != 0
        && ((v13 = *(uint32_t *)(v10 + 12), dword_79BE3C == v13) || dword_79BE34 == v13 || dword_79BE38 == v13) )  // CNRDPVPRoomListWindow__vmt0 构造（204 行：642990/642270 + 69A110 + 48F4C0/48FBB0）
      {
        v36 = sub_642270(pArg1);  // 结果 = PVP 房间列表条目
      }
      else
      {
        v36 = -1;
      }
      v38 = 0;
      v40 = 74;
      do
      {
        pObj5 = sub_418DD0(21);  // 调 sub_418DD0
        if ( pObj5 != 0 )  // 若 pObj5 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
            pObj5,
            384,
            v40 - 1,
            dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
            1065353216,
            1065353216,
            0,
            -1929379841,
            1333788672,
            1333788672);
        v15 = *(uint32_t *)(pArg1 + 176);  // v15 = pArg1+176
        if ( v15 != 0 && v12 < (*(uint32_t *)(pArg1 + 180) - v15) >> 2 )  // 若 v15 != 0 && v12 < (*(uint32_t *)(pArg1 + 180) - v15) >> 2
        {
          v16 = *(int **)(pArg1 + 204);
          v17 = (int *)v16[1];
          v18 = (uint32_t *)(*(uint32_t *)(pArg1 + 176) + 4 * v12);
          while ( *((uint8_t *)v17 + 137) == 0 )  // 当 *((uint8_t *)v17 + 137) == 0 循环
          {
            if ( v17[3] >= *v18 )  // 若 v17[3] >= *v18
            {
              v16 = v17;
              v17 = (int *)*v17;
            }
            else
            {
              v17 = (int *)v17[2];
            }
          }
          v19 = *(int **)(pArg1 + 204);
          v35 = v16;
          if ( v16 == v19 || *v18 < v16[3] )  // 若 v16 == v19 || *v18 < v16[3]
          {
            v34 = v19;
            v20 = (int *)&v34;
          }
          else
          {
            v20 = (int *)&v35;
          }
          v21 = *v20;
          if ( *v20 != *(uint32_t *)(pArg1 + 204) )  // 若 *v20 != *(uint32_t *)(pArg1 + 204)
          {
            v22 = *(uint32_t *)(v21 + 20);  // v22 = v21+20
            v23 = (uint32_t *)(v21 + 16);
            sub_69A110(389, v40 + 3, v22, -1);  // 调 sub_69A110
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 120, nArg2);  // 调用虚函数槽 +72
            v24 = v23[19];
            if ( v24 != 0 )  // 若 v24 != 0
            {
              v25 = dword_99FEC4[v24];
            }
            else if ( v23[26] < 0x10u )  // 否则若 v23[26] < 0x10u
            {
              v25 = (int)(v23 + 21);
            }
            else
            {
              v25 = v23[21];
            }
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              423,
              v40 + 4,
              -4928551,
              v25);
            if ( v23[18] == 1 )  // 若 v23[18] == 1
              pObj2 = sub_418DD0(74);  // 调 sub_418DD0
            else
              pObj2 = sub_418DD0(75);  // 调 sub_418DD0
            if ( pObj2 != 0 )  // 若 pObj2 != 0
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 607, v40, dword_79C0B0);  // 调用虚函数槽 +152
            nArg2 = pArg1 + 68;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0);  // 调用虚函数槽 +68
            v35 = *(int **)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
            v27 = sub_48F4C0(v23);  // 结果 = 槽表计数（+8..+36 中不等于 254 的字段数）
            v28 = sub_48FBB0(v23, v27);  // 结果 = 槽表计数（+40..+68 中不等于 0xFFFF 的字段数）
            ((void (/*cdecl*/ *)(int, int, int, int, const char *, int))v35[20])(
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              536,
              v40 + 4,
              -3750202,
              "%d/%d",  // 字符串 “%d/%d”
              v28);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
            if ( v38 == v36 || v23[1] == dword_795D3C )  // 若 v38 == v36 || v23[1] == dword_795D3C
            {
              sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
              pObj4 = sub_418DD0(46);  // 调 sub_418DD0
              if ( pObj4 != 0 )  // 若 pObj4 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 384, v40 - 1, dword_79C0B0);  // 调用虚函数槽 +152
              sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
            }
            v12 = v37;
          }
        }
        ++v12;  // 自增v12
        v30 = ++v38 < 12;
        v37 = v12;
        v40 += 24;
      }
      while ( v30 );  // 当 v30 循环
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 68);  // 调用虚函数槽 +72
      (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        v39 + 86,
        v33 + 340,
        -3750202,
        "%d/%d",  // 字符串 “%d/%d”
        *(uint32_t *)(pArg1 + 188) + 1,
        *(uint32_t *)(pArg1 + 192) + 1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
      v7 = v32;
    }
    result = sub_418DD0(246);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, v39, v7, dword_79C0B0);  // 调用虚函数槽 +152
  }
  return result;
}


// ============================================================
// 【分区 5】副本地图 CNRDDungeonMap（0x643210-0x643970）
// vmt0 构造（303 行：69A5F0 + 40FC80 + 4D33A0）；vmt4 析构（643260/5542F0）。
// ============================================================
// ------------------------------------------------------------
// 0x643210 CNRDDungeonMap__vmt8 —— CNRDDungeonMap__vmt8 Update 槽（15 行）
// ------------------------------------------------------------
int /*thiscall*/ CNRDDungeonMap__vmt8(int *this)  // 函数: CNRDDungeonMap__vmt8 Update 槽（15 行）
{
  int result; // eax

  result = *(this + 9);  // result = this+9
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 若 *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *..
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 虚调用 vt+32
  return result;  // result=this+36 物品状态字
}



// ------------------------------------------------------------
// 0x643230 CNRDDungeonMap__vmtC —— CNRDDungeonMap__vmtC 打开槽（13 行）
// ------------------------------------------------------------
bool /*stdcall*/ CNRDDungeonMap__vmtC(int nArg1, int nArg2)  // 函数: CNRDDungeonMap__vmtC 打开槽（13 行）
{
  int v2; // eax

  v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);  // 全局 dword_8F7A24 = 登录/选区管理器
  return *(uint32_t *)(dword_8F7A24 + 12) == 3 && v2 != 0 && *(uint32_t *)(v2 + 68) != 0;  // 全局 dword_8F7A24 = 登录/选区管理器
}



// ------------------------------------------------------------
// 0x643260 sub_643260 —— 副本地图成员清理（5542F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_643260(uint32_t *this)  // 函数: 副本地图成员清理（5542F0）
{
  void (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx

  *this = &vftbl_CNRDDungeonMap;  // *this 写入 &vftbl_CNRDDungeonMap
  fld_e9 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( fld_e9 != nullptr )  // 若 fld_e9 非空
    (**fld_e9)(fld_e9, 1);
  *(this + 9) = 0;  // this+36 = 0
  *this = &vftbl_IRDPopupWindow;  // *this 写入 &vftbl_IRDPopupWindow
  return sub_5542F0(this);  // 窗口页数据 2
}



// ------------------------------------------------------------
// 0x6432D0 CNRDDungeonMap__vmt4 —— CNRDDungeonMap__vmt4 析构（转发 643260）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDDungeonMap__vmt4(uint32_t *Block, char pszArg2)  // CNRDDungeonMap__vmt4 析构（转发 643260）
{
  sub_643260(Block);  // 副本地图成员清理（5542F0）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x643300 sub_643300 —— 副本地图清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_643300(uint32_t *this)  // 函数: 副本地图清理（43C410/69A840）
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  int result; // eax

  pMem = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_43C410(pMem, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116), 23, 24, 25, 23, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(this + 9) = v3;  // this+36 = v3
  sub_69A840(v3);  // 调 sub_69A840
  result = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 84);
  *(this + 10) = result;  // this+40 = result
  return result;
}



// ------------------------------------------------------------
// 0x643390 CNRDDungeonMap__vmt0 —— CNRDDungeonMap__vmt0 构造（303 行：69A5F0 + 418DD0/40FC80 + 4D33A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_643390(uint32_t *this, int nArg2)  // 【CNRDDungeonMap__vmt0】
{
  int result; // eax
  int fld_e2; // ecx
  int *v5; // eax
  int v6; // edx
  int v7; // edi
  int v8; // eax
  uint32_t *fld_e22; // ecx
  int v10; // edx
  int fld_e23; // eax
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int fld_e24; // eax
  int v16; // edi
  int v17; // ebx
  int pObj11; // eax
  bool v19; // zf
  int fld_e25; // eax
  int v21; // edi
  int v22; // ebx
  int pObj9; // eax
  int v24; // ebx
  int fld_e26; // eax
  int v26; // edi
  int pObj4; // eax
  int v28; // edi
  int fld_e28; // ebx
  int pObj6; // eax
  int v31; // eax
  int pObj2; // eax
  int v33; // ebx
  uint32_t *v34; // ecx
  uint32_t *v35; // eax
  int v36; // eax
  int pObj5; // eax
  int pObj14; // eax
  int pObj12; // eax
  int pObj7; // eax
  int pObj13; // eax
  int fld_e27; // edi
  int pObj; // eax
  int fld_e29; // eax
  int v45; // edi
  int v46; // ebx
  int pObj3; // eax
  int fld_e210; // eax
  int v49; // ebx
  int v50; // edi
  int pObj8; // eax
  int fld_e211; // eax
  int v53; // edi
  int v54; // ebx
  int pObj10; // eax
  int fld_e212; // eax
  int v57; // edi
  int v58; // ebx
  uint32_t *v59; // [esp+4h] [ebp-38h]
  int v60; // [esp+8h] [ebp-34h]
  int v61; // [esp+Ch] [ebp-30h] BYREF
  uint32_t *v62; // [esp+10h] [ebp-2Ch]
  int v63; // [esp+14h] [ebp-28h]
  int v64; // [esp+18h] [ebp-24h]
  int v65; // [esp+1Ch] [ebp-20h]
  int v66; // [esp+20h] [ebp-1Ch]
  int v67; // [esp+24h] [ebp-18h]
  int v68; // [esp+28h] [ebp-14h]
  int v69; // [esp+2Ch] [ebp-10h]
  int fld_e282; // [esp+30h] [ebp-Ch]
  int v71; // [esp+34h] [ebp-8h]
  int v72; // [esp+38h] [ebp-4h]
  int v73; // [esp+44h] [ebp+8h]
  int v74; // [esp+44h] [ebp+8h]
  int v75; // [esp+44h] [ebp+8h]
  int v76; // [esp+44h] [ebp+8h]

  result = nArg2;
  fld_e2 = *(this + 2);  // fld_e2 = this+2
  if ( nArg2 == fld_e2 )  // 若 nArg2 == fld_e2
  {
    v59 = *(uint32_t **)(*(uint32_t *)(dword_8F7A24 + 28) + 16);  // 全局 dword_8F7A24 = 登录/选区管理器
    v62 = (uint32_t *)v59[27];
    if ( v62 != nullptr && (v68 = v62[17]) != 0 )  // 若 v62 != nullptr && (v68 = v62[17]) != 0
    {
      v5 = (int *)(v62[42] + 8 * dword_99FB78);
      v6 = *v5;
      v64 = v6;
      v72 = v6;
      if ( v6 <= 3 )  // 若 v6 <= 3
        v72 = 3;
      if ( v6 == 2 )  // 若 v6 == 2
        v72 = 3;
      v7 = v72;
      v63 = v5[1] + 1;
      v8 = 18 * v63;
      *(uint32_t *)(fld_e2 + 32) = 18 * v63;  // fld_e2+32 = 18 * v63
      v65 = v8;
      v7 *= 18;
      *(uint32_t *)(fld_e2 + 28) = v7;  // fld_e2+28 = v7
      fld_e22 = (uint32_t *)*(this + 2);
      v69 = v7;
      sub_69A5F0(fld_e22, 627 - v7, 30);  // 调 sub_69A5F0
      sub_69A5F0((uint32_t *)*(this + 9), *(uint32_t *)(*(this + 2) + 20) + v7 - 16, *(uint32_t *)(*(this + 2) + 24) + 2);  // 调 sub_69A5F0
      v66 = *(uint32_t *)(sub_418DD0(30) + 20);  // 调 资源句柄 (101)
      v10 = *(uint32_t *)(sub_418DD0(28) + 24);  // 调 资源句柄 (101)
      fld_e23 = *(this + 2);  // fld_e23 = this+2
      v12 = *(uint32_t *)(fld_e23 + 24);  // v12 = fld_e23+24
      v13 = *(uint32_t *)(fld_e23 + 20);  // v13 = fld_e23+20
      fld_e282 = v10;
      v14 = sub_418DD0(27);  // 调 sub_418DD0
      sub_40FC80(v13 - v66, v12 - fld_e282, v14);  // 贴图转发（目标对象虚发 +152(this, x, y)）
      if ( v72 > 0 )  // 若 v72 > 0
      {
        v73 = 0;
        v67 = v72;
        do
        {
          fld_e24 = *(this + 2);  // fld_e24 = this+2
          v16 = *(uint32_t *)(fld_e24 + 24);  // v16 = fld_e24+24
          v17 = *(uint32_t *)(fld_e24 + 20);  // v17 = fld_e24+20
          pObj11 = sub_418DD0(28);  // 调 sub_418DD0
          if ( pObj11 != 0 )  // 若 pObj11 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj11 + 152))(pObj11, v73 + v17, v16 - fld_e282, dword_79C0B0);  // 调用虚函数槽 +152
          v19 = v67 == 1;
          v73 += 18;
          --v67;  // 自减v67
        }
        while ( !v19 );  // 当 !v19 循环
      }
      fld_e25 = *(this + 2);  // fld_e25 = this+2
      v21 = *(uint32_t *)(fld_e25 + 24);  // v21 = fld_e25+24
      v22 = *(uint32_t *)(fld_e25 + 20);  // v22 = fld_e25+20
      pObj9 = sub_418DD0(29);  // 调 sub_418DD0
      if ( pObj9 != 0 )  // 若 pObj9 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 152))(pObj9, v22 + v69, v21 - fld_e282, dword_79C0B0);  // 调用虚函数槽 +152
      v24 = 0;
      v67 = 0;
      if ( v63 > 0 )  // 若 v63 > 0
      {
        while ( 1 )  // 当 1 循环
        {
          fld_e26 = *(this + 2);  // fld_e26 = this+2
          v26 = *(uint32_t *)(fld_e26 + 20);  // v26 = fld_e26+20
          v74 = *(uint32_t *)(fld_e26 + 24) + 18 * v24;  // fld_e26=this+8 物品 id
          pObj4 = sub_418DD0(30);  // 调 sub_418DD0
          if ( pObj4 != 0 )  // 若 pObj4 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v26 - v66, v74, dword_79C0B0);  // 调用虚函数槽 +152
          v28 = 0;
          v71 = 0;
          if ( v72 > 0 )  // 若 v72 > 0
            break;
LABEL_53:
          fld_e27 = *(uint32_t *)(*(this + 2) + 20);
          pObj = sub_418DD0(32);  // 调 sub_418DD0
          if ( pObj != 0 )  // 若 pObj != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, fld_e27 + v69, v74, dword_79C0B0);  // 调用虚函数槽 +152
          v67 = ++v24;
          if ( v24 >= v63 )  // 若 v24 >= v63
            goto LABEL_56;  // 跳转 LABEL_56
        }
        while ( 1 )  // 当 1 循环
        {
          fld_e28 = *(uint32_t *)(*(this + 2) + 20) + 18 * v28;
          fld_e282 = fld_e28;
          pObj6 = sub_418DD0(31);  // 调 sub_418DD0
          if ( pObj6 != 0 )  // 若 pObj6 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, fld_e28, v74, dword_79C0B0);  // 调用虚函数槽 +152
          if ( v67 == 0 )  // 若 v67 == 0
          {
            if ( v28 != 0 )  // 若 v28 != 0
              v31 = (v28 == v72 - 1) + 39;
            else
              v31 = 38;
            pObj2 = sub_418DD0(v31);  // 调 sub_418DD0
            if ( pObj2 != 0 )  // 若 pObj2 != 0
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
                pObj2,
                fld_e28,
                v74,
                dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                1065353216,
                1065353216,
                0,
                1694498815,
                1333788672,
                1333788672);
            goto LABEL_51;  // 跳转 LABEL_51
          }
          v33 = v67 - 1;
          v61 = -1;
          if ( v64 == v72 )  // 若 v64 == v72
            goto LABEL_30;  // 跳转 LABEL_30
          if ( v71 != 0 )  // 若 v71 != 0
            break;
LABEL_50:
          v28 = v71;
LABEL_51:
          v71 = ++v28;
          if ( v28 >= v72 )  // 若 v28 >= v72
          {
            v24 = v67;
            goto LABEL_53;  // 跳转 LABEL_53
          }
        }
        v28 = v71 - 1;
LABEL_30:
        v34 = (uint32_t *)(v62[42] + 8 * dword_99FB78);
        v60 = *(uint32_t *)(*(uint32_t *)(v62[46] + 16 * dword_99FB78 + 4) + 4 * (v28 + v33 * *v34));  // 结果 = 虚调用 vt+4
        if ( v60 != 0 && v28 < v64 && (v35 = *(uint32_t **)(dword_99FBC4 + 4 * (v28 + v33 * *v34))) != nullptr )  // 若 v60 != 0 && v28 < v64 && (v35 = *(uint32_t **)(dword_99FBC4 + ..
        {
          v61 = v28 * v33 * *v35;
          v36 = sub_4D33A0(&v61) % 4 + 8 * v60 - 8;  // 调 掷 0..9999
        }
        else
        {
          v36 = v61;
        }
        if ( v59[28] == v28 && v59[29] == v33 )  // 若 v59[28] == v28 && v59[29] == v33
        {
          pObj5 = sub_418DD0(v36 + 4);  // 调 sub_418DD0
          if ( pObj5 != 0 )  // 若 pObj5 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, fld_e282, v74, dword_79C0B0);  // 调用虚函数槽 +152
          pObj14 = sub_418DD0(3);  // 调 sub_418DD0
          if ( pObj14 != 0 )  // 若 pObj14 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj14 + 152))(pObj14, fld_e282 + 6, v74 + 4, dword_79C0B0);  // 调用虚函数槽 +152
        }
        else if ( dword_99FB7C == v28 && dword_99FB80 == v33 )  // 否则若 dword_99FB7C == v28 && dword_99FB80 == v33
        {
          pObj12 = sub_418DD0(120);  // 调 sub_418DD0
          if ( pObj12 != 0 )  // 若 pObj12 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj12 + 152))(pObj12, fld_e282, v74, dword_79C0B0);  // 调用虚函数槽 +152
          pObj7 = sub_418DD0(37);  // 调 sub_418DD0
          if ( pObj7 != 0 )  // 若 pObj7 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, fld_e282 + 1, v74 + 2, dword_79C0B0);  // 调用虚函数槽 +152
        }
        else if ( v36 != -1 )  // 否则若 v36 != -1
        {
          pObj13 = sub_418DD0(v36);  // 调 sub_418DD0
          if ( pObj13 != 0 )  // 若 pObj13 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj13 + 152))(pObj13, fld_e282, v74, dword_79C0B0);  // 调用虚函数槽 +152
        }
        goto LABEL_50;  // 跳转 LABEL_50
      }
LABEL_56:
      fld_e29 = *(this + 2);  // fld_e29 = this+2
      v45 = *(uint32_t *)(fld_e29 + 24);  // v45 = fld_e29+24
      v46 = *(uint32_t *)(fld_e29 + 20);  // v46 = fld_e29+20
      v75 = *(uint32_t *)(sub_418DD0(36) + 20);  // 调 资源句柄 (101)
      pObj3 = sub_418DD0(36);  // 调 sub_418DD0
      if ( pObj3 != 0 )  // 若 pObj3 != 0
        (*(void (/*thiscall*/ **)(int, unsigned int, int, int))(*(uint32_t *)pObj3 + 152))(  // 虚槽+152 效果通道 3
          pObj3,
          ((unsigned int)(v69 - v75) >> 1) + v46 - 3,
          v45 + 3,
          dword_79C0B0);  // dword_79C0B0（文本/图像绘制对象）
      fld_e210 = *(this + 2);  // fld_e210 = this+2
      v49 = *(uint32_t *)(fld_e210 + 24);  // v49 = fld_e210+24
      v50 = *(uint32_t *)(fld_e210 + 20);  // v50 = fld_e210+20
      pObj8 = sub_418DD0(33);  // 调 sub_418DD0
      if ( pObj8 != 0 )  // 若 pObj8 != 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v50 - v66, v49 + v65, dword_79C0B0);  // 调用虚函数槽 +152
      if ( v72 > 0 )  // 若 v72 > 0
      {
        v76 = 0;
        v63 = v72;
        do
        {
          fld_e211 = *(this + 2);  // fld_e211 = this+2
          v53 = *(uint32_t *)(fld_e211 + 24);  // v53 = fld_e211+24
          v54 = *(uint32_t *)(fld_e211 + 20);  // v54 = fld_e211+20
          pObj10 = sub_418DD0(34);  // 调 sub_418DD0
          if ( pObj10 != 0 )  // 若 pObj10 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj10 + 152))(pObj10, v76 + v54, v53 + v65, dword_79C0B0);  // 调用虚函数槽 +152
          v19 = v63 == 1;
          v76 += 18;
          --v63;  // 自减v63
        }
        while ( !v19 );  // 当 !v19 循环
      }
      fld_e212 = *(this + 2);  // fld_e212 = this+2
      v57 = *(uint32_t *)(fld_e212 + 24);  // v57 = fld_e212+24
      v58 = *(uint32_t *)(fld_e212 + 20);  // v58 = fld_e212+20
      result = sub_418DD0(35);  // 调 sub_418DD0
      if ( result != 0 )  // 若 result != 0
        return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 虚槽+152 效果通道 3
                 result,
                 v58 + v69,
                 v57 + v65,
                 dword_79C0B0);  // dword_79C0B0（文本/图像绘制对象）
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 虚调用 vt+32
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x643910 sub_643910 —— 副本地图页部件（5542C0/5548B0 + 643300）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_643910(uint32_t *this, int nArg2)  // 副本地图页部件（5542C0/5548B0 + 643300）
{
  *this = &vftbl_IRDPopupWindow;  // *this 写入 &vftbl_IRDPopupWindow
  sub_5542C0();  // 窗口页数据
  sub_5548B0(nArg2, 67);  // vmt4 三件套的公共尾
  *this = &vftbl_CNRDDungeonMap;  // *this 写入 &vftbl_CNRDDungeonMap
  *(this + 9) = 0;  // this+36 = 0
  sub_643300(this);  // 副本地图清理（43C410/69A840）
  return this;  // 返回自身指针
}



// ============================================================
// 【分区 6】充值网页窗 CNRDPayWebWindow（0x643970-0x643F60）
// vmtC 打开（6439D0）：跳转 http://www.d-fighter.com（55CB40/652D30/652DE0）；
// vmt0 加载 Common/Etc/MonoLayer.img；643E10 装载 interface/payweb.img。
// ============================================================
// ------------------------------------------------------------
// 0x643970 sub_643970 —— 充值窗数据（32 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_643970(int this)  // 函数: 充值窗数据（32 行）
{
  void (/*thiscall*/ ***pThis_44)(uint32_t, int); // ecx

  (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 68) + 8))(*(uint32_t *)(this + 68));  // 调用虚函数槽 +8
  pThis_44 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 68);  // this+68 角色数（begin/end 差 >>2；>=8 …
  if ( pThis_44 != nullptr )  // 若 pThis_44 非空
  {
    if ( *(pThis_44 - 1) != nullptr )  // 若 *(pThis_44 - 1) != nullptr
    {
      (**pThis_44)(pThis_44, 3);
      *(uint32_t *)(this + 36) = 0;  // this+36 = 0
      *(uint32_t *)(this + 60) = 0;  // this+60 = 0
      *(uint32_t *)(this + 64) = 0;  // this+64 = 0
      *(uint32_t *)(this + 68) = 0;  // this+68 = 0
      *(uint32_t *)(this + 56) = 0;  // this+56 = 0
      return;
    }
    j_j__free(pThis_44 - 1);  // 调 j__free
  }
  *(uint32_t *)(this + 36) = 0;  // this+36 = 0
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 68) = 0;  // this+68 = 0
  *(uint32_t *)(this + 56) = 0;  // this+56 = 0
}



// ------------------------------------------------------------
// 0x6439D0 CNRDPayWebWindow__vmtC —— CNRDPayWebWindow__vmtC 打开：跳转 http://www.d-fighter.com 充值站（55CB40 + 652D30/652DE0 + 422E70/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPayWebWindow__vmtC(uint32_t *this, int pArg2, int nArg3)  // CNRDPayWebWindow__vmtC 打开：跳转 http://www.d-fighter.com 充值站（55CB40 + 652D30/652DE0 + 422E70/44E8D0）
{
  char *v4; // eax
  HWND v6; // eax
  int v7; // eax
  int v8; // ecx
  LONG right; // edx
  LONG bottom; // eax
  LONG left; // [esp+4h] [ebp-124h]
  LONG top; // [esp+8h] [ebp-120h]
  struct tagRECT Rect; // [esp+14h] [ebp-114h] BYREF
  char Buffer[256]; // [esp+24h] [ebp-104h] BYREF
  int dword_796E502; // [esp+124h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0A4 + 64))(dword_79C0A4, 1) == 1 )  // 虚槽+64 CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/4015C0/45A340
  {
    sprintf(Buffer, "http://www.d-fighter.com");
    *(this + 14) = *(uint32_t *)(pArg2 + 4);  // this+56 = *(uint32_t *)(pArg2 + 4)
    sub_55CB40();  // 调 sub_55CB40
    GetWindowRect(*(HWND *)(dword_79C0A0 + 16), &Rect);  // 调 GetWindowRect 取窗口矩形
    left = Rect.left;
    top = Rect.top;
    Rect.left += (Rect.right - Rect.left - 450) / 2;
    Rect.top += (Rect.bottom - Rect.top - 307) / 2;
    Rect.right = 450;
    Rect.bottom = 307;
    v6 = (HWND)sub_652D30(*(HWND *)(dword_79C0A0 + 16), *(HINSTANCE *)(dword_79C0A0 + 20), (int)&Rect, 0);
    *(this + 9) = v6;  // this+36 = v6
    if ( v6 != nullptr )  // 若 v6 非空
    {
      sub_652DE0(v6, Buffer);  // 【zlib 1.2.3 静态链接（uncompress / inflateInit2_…】
      v7 = Rect.left - left;
      v8 = Rect.top - top;
      right = Rect.right;
      *(this + 10) = Rect.left - left;  // this+40 = Rect.left - left
      *(this + 12) = right + v7;  // this+48 = right + v7
      bottom = Rect.bottom;
      *(this + 11) = v8;  // this+44 = v8
      *(this + 13) = bottom + v8;  // this+52 = bottom + v8
      while ( ShowCursor(true) < 0 )  // 当 ShowCursor(true) < 0 循环
        ;
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 60) = 0;  // 全局 dword_8F8528 = 消息/弹窗管理器
      *(this + 15) = 1;  // this+60 = 1
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v4 = sub_422E70(1952);  // 调 sub_422E70
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v4, 0);  // 对象池借出（按池号取可用对象）
    return 0;
  }
}



// ------------------------------------------------------------
// 0x643B90 CNRDPayWebWindow__vmt10 —— CNRDPayWebWindow__vmt10 槽（55CB50）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPayWebWindow__vmt10(HWND *this)  // 函数: CNRDPayWebWindow__vmt10 槽（55CB50）
{
  HWND fld_e9; // eax
  int result; // eax

  fld_e9 = *(this + 9);  // fld_e9 = this+9
  if ( fld_e9 != nullptr )  // 若 fld_e9 非空
  {
    SendMessageA(fld_e9, 0x10u, 0, 0);  // 调 SendMessageA 发窗口消息
    *(this + 9) = nullptr;  // this+36 = nullptr
  }
  sub_55CB50(*(this + 14));  // 调 sub_55CB50
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0A4 + 64))(dword_79C0A4, 0);  // 调用虚函数槽 +64
  do
    result = ShowCursor(false);
  while ( result >= 0 );  // 当 result >= 0 循环
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 60) = 255;  // 全局 dword_8F8528 = 消息/弹窗管理器
  return result;
}



// ------------------------------------------------------------
// 0x643BF0 CNRDPayWebWindow__vmt8 —— CNRDPayWebWindow__vmt8 Update（CLICK_BUTTON2 + 652CC0 关闭网页层）
// ------------------------------------------------------------
HWND /*thiscall*/ CNRDPayWebWindow__vmt8(HWND *this)  // 函数: CNRDPayWebWindow__vmt8 Update（CLICK_BUTTON2 + 652CC0 关闭网页层）
{
  HWND result; // eax
  int v3; // edi
  int v4; // ebx
  int fld_e17; // eax
  HWND v6; // edx
  BOOL v7; // [esp+Ch] [ebp-4h]

  result = *(this + 9);  // result = this+9
  v3 = 0;
  v4 = 0;
  if ( result != nullptr )  // 若 result 非空
  {
    v7 = !IsWindow(result);  // result=this+36 物品状态字
    fld_e17 = (int)*(this + 17);  // this+17 激活/可命中标志
    if ( *(uint8_t *)(fld_e17 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e17 + 12) )  // 若 *(uint8_t *)(fld_e17 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    {
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
      v4 = 1;
    }
    if ( sub_652CC0(*(this + 9)) == 0 )  // 控件存活性（窗口句柄探测）
      v3 = 1;
    result = (HWND)((char *)*(this + 15) - 1);  // result=this+36 物品状态字
    if ( *(this + 15) == (HWND)1 )  // 若 *(this + 15) == (HWND)1
    {
      if ( v3 == 1 )  // 若 v3 == 1
      {
        ShowWindow(*(this + 9), 5);  // 调 ShowWindow 显示窗口
        result = (HWND)UpdateWindow(*(this + 9));  // result=this+36 物品状态字
        *(this + 15) = (HWND)2;  // this+60 = (HWND)2
      }
    }
    else
    {
      result = (HWND)((char *)*(this + 15) - 2);  // result=this+36 物品状态字
      if ( *(this + 15) == (HWND)2 )  // 若 *(this + 15) == (HWND)2
      {
        if ( v3 != 0 )  // 若 v3 != 0
        {
          result = (HWND)v7;  // result=this+36 物品状态字
          if ( v7 )  // 若 v7
          {
            v6 = *this;
            *(this + 9) = nullptr;  // this+36 = nullptr
            result = (HWND)(*((int (/*thiscall*/ **)(HWND *))v6 + 8))(this);  // result=this+36 物品状态字
            *(this + 15) = nullptr;  // this+60 = nullptr
          }
          else if ( v4 != 0 )  // 否则若 v4 != 0
          {
            result = (HWND)(*((int (/*thiscall*/ **)(HWND *))*this + 8))(this);  // 结果 = 虚调用 vt+8
            *(this + 15) = nullptr;  // this+60 = nullptr
          }
        }
        else
        {
          result = (HWND)ShowWindow(*(this + 9), 0);  // result=this+36 物品状态字
          *(this + 15) = (HWND)1;  // this+60 = (HWND)1
        }
      }
    }
  }
  return result;  // result=this+36 物品状态字
}



// ------------------------------------------------------------
// 0x643CF0 CNRDPayWebWindow__vmt0 —— CNRDPayWebWindow__vmt0 构造：加载 Common/Etc/MonoLayer.img 遮罩层（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPayWebWindow__vmt0(uint32_t *this, int nArg2)  // 函数: CNRDPayWebWindow__vmt0 构造：加载 Common/Etc/MonoLayer.img 遮罩层（418DD0）
{
  int result; // eax
  int pObj; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2) )  // 若 nArg2 == *(this + 2)
  {
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Common/Etc/MonoLayer.img");  // 字符串 “Common/Etc/MonoLayer.img”
    pObj = sub_418DD0(0);  // 调 sub_418DD0
    if ( pObj != 0 )  // 若 pObj != 0
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj,
        0,
        0,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1098907648,
        1094713344,
        0,
        -922746881,
        1333788672,
        1333788672);
    result = sub_418DD0(0);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 虚槽+152 效果通道 3
               result,
               *(this + 10) - 24,
               *(this + 11) - 31,
               dword_79C0B0);  // dword_79C0B0（文本/图像绘制对象）
  }
  return result;
}



// ------------------------------------------------------------
// 0x643D80 sub_643D80 —— 充值窗收尾（643970 + 5542F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_643D80(uint32_t *this)  // 函数: 充值窗收尾（643970 + 5542F0）
{
  *this = &vftbl_CNRDPayWebWindow;  // *this 写入 &vftbl_CNRDPayWebWindow
  sub_643970((int)this);  // 充值窗数据
  *this = &vftbl_IRDPopupWindow;  // *this 写入 &vftbl_IRDPopupWindow
  return sub_5542F0(this);  // 窗口页数据 2
}



// ------------------------------------------------------------
// 0x643DE0 CNRDPayWebWindow__vmt4 —— CNRDPayWebWindow__vmt4 析构（转发 643D80）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDPayWebWindow__vmt4(uint32_t *Block, char pszArg2)  // CNRDPayWebWindow__vmt4 析构（转发 643D80）
{
  sub_643D80(Block);  // 充值窗收尾（643970 + 5542F0）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x643E10 sub_643E10 —— 装载资源 interface/payweb.img（69A5F0/69A840 定位，38 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_643E10(uint32_t *this)  // 函数: 装载资源 interface/payweb.img（69A5F0/69A840 定位，38 行）
{
  int v2; // ebx
  uint32_t *pMem; // eax
  uint32_t *v4; // ecx
  uint32_t *v5; // edi

  *(this + 16) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // this+16 频道型选中索引
                   dword_8F84B8,
                   "interface/payweb.img");  // 字符串 “interface/payweb.img”
  v2 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  pMem = operator new(0x88u);  // 堆分配 136 字节对象
  v4 = nullptr;  // v4 = nullptr 空指针
  if ( pMem != nullptr )  // 若 pMem 非空
  {
    v5 = pMem + 1;
    *pMem = 1;  // *pMem 写入 1
    `eh vector constructor iterator'(
      pMem + 1,
      0x84u,
      1,
      (void (/*thiscall*/ *)(void *))sub_46F750,  // 调 nengine::CNButton 构造
      (void (/*thiscall*/ *)(void *))sub_43C480);  // 调 nengine::CNButton 析构
    v4 = v5;
  }
  *(this + 17) = v4;  // this+68 = v4
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int, uint32_t, uint32_t, uint32_t))(*v4 + 32))(v4, v2, 68, 69, 70, 0, 0, 0);  // 虚调用 vt+32
  sub_69A5F0((uint32_t *)*(this + 17), 299, 403);  // 调 sub_69A5F0
  sub_69A840(*(this + 17));  // 调 sub_69A840
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 1);  // 虚调用 vt+28
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 24))(this, 0, 0);  // 虚调用 vt+24
}



// ------------------------------------------------------------
// 0x643EF0 sub_643EF0 —— 充值窗页部件（5542C0/5548B0 + 643E10）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_643EF0(uint32_t *this, int nArg2)  // 充值窗页部件（5542C0/5548B0 + 643E10）
{
  *this = &vftbl_IRDPopupWindow;  // *this 写入 &vftbl_IRDPopupWindow
  sub_5542C0();  // 窗口页数据
  sub_5548B0(nArg2, 51);  // vmt4 三件套的公共尾
  *this = &vftbl_CNRDPayWebWindow;  // *this 写入 &vftbl_CNRDPayWebWindow
  *(this + 9) = 0;  // this+36 = 0
  *(this + 15) = 0;  // this+60 = 0
  *(this + 16) = 0;  // this+64 = 0
  *(this + 17) = 0;  // this+68 = 0
  *(this + 14) = 0;  // this+56 = 0
  sub_643E10(this);  // 装载资源 interface/payweb.img
  return this;  // 返回自身指针
}



// ============================================================
// 【分区 7】公会列表窗 CNRDGuildListWindow（0x643F60-0x6453A0）
// vmt0 构造（309 行：644A20 公会数据 + 4BE300/4BE1D0 + 43BCB0）。
// ============================================================
// ------------------------------------------------------------
// 0x643F60 sub_643F60 —— 公会窗数据（52 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_643F60(uint32_t *this)  // 函数: 公会窗数据（52 行）
{
  void (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  uint32_t *pThis_D; // edi
  int i; // ebx
  void (/*thiscall*/ ***fld_e15)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e16)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e56)(uint32_t, int); // ecx
  int result; // eax

  fld_e12 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 12);  // this+12 物品类型号
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    (**fld_e12)(fld_e12, 1);
  *(this + 12) = 0;  // this+48 = 0
  pThis_D = this + 13;
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    if ( *pThis_D != 0 )  // 若 *pThis_D != 0
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_D)(*pThis_D, 1);
    *pThis_D++ = 0;  // *pThis_D++ 写入 0
  }
  fld_e15 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  if ( fld_e15 != nullptr )  // 若 fld_e15 非空
    (**fld_e15)(fld_e15, 1);
  fld_e16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 16);  // this+16 频道型选中索引
  *(this + 15) = 0;  // this+60 = 0
  if ( fld_e16 != nullptr )  // 若 fld_e16 非空
    (**fld_e16)(fld_e16, 1);
  fld_e10 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 16) = 0;  // this+64 = 0
  if ( fld_e10 != nullptr )  // 若 fld_e10 非空
    (**fld_e10)(fld_e10, 1);
  fld_e11 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;  // this+40 = 0
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    (**fld_e11)(fld_e11, 1);
  fld_e56 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 56);  // this+56 键盘输入使能
  result = 0;
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e56 != nullptr )  // 若 fld_e56 非空
    result = (**fld_e56)(fld_e56, 1);
  *(this + 56) = 0;  // this+224 = 0
  return result;
}



// ------------------------------------------------------------
// 0x644010 CNRDGuildListWindow__vmtC —— CNRDGuildListWindow__vmtC 打开槽（69A5F0 + 478EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDGuildListWindow__vmtC(uint32_t **this, int nArg2, int nArg3)  // 函数: CNRDGuildListWindow__vmtC 打开槽（69A5F0 + 478EA0）
{
  dword_9B9538 = (int)this;
  sub_69A5F0(*(this + 2), 378, 51);  // 调 sub_69A5F0
  sub_478EA0(dword_8F8514, 0);  // 调 sub_478EA0
  return 1;
}



// ------------------------------------------------------------
// 0x644040 CNRDGuildListWindow__vmt10 —— CNRDGuildListWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDGuildListWindow__vmt10()  // CNRDGuildListWindow__vmt10 状态切换槽（10 行）
{
  dword_9B9538 = 0;
}



// ------------------------------------------------------------
// 0x644050 sub_644050 —— 公会列表构建（25 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_644050(uint32_t *this)  // 函数: 公会列表构建（25 行）
{
  int fld_e2; // eax
  int v2; // edx
  int v3; // ecx
  int result; // eax
  LONG i; // ecx

  fld_e2 = *(this + 2);  // fld_e2 = this+2
  v2 = *(uint32_t *)(fld_e2 + 20) + 11;  // fld_e2=this+8 物品 id
  v3 = *(uint32_t *)(fld_e2 + 24) + 67;  // fld_e2=this+8 物品 id
  result = 0;
  for ( i = v3 + 17; pt.x < v2 - 3 || pt.x >= v2 + 226 || pt.y < i - 18 || pt.y >= i; i += 18 )  // 循环：i = v3 + 17; pt.x < v2 - 3 || pt.x >= v2 + 226 || pt.y < i -
  {
    if ( ++result >= 8 )  // 若 ++result >= 8
      return -1;  // 返回 -1（0xFFFFFFFF）
  }
  return result;
}



// ------------------------------------------------------------
// 0x6440B0 CNRDGuildListWindow__vmt8 —— CNRDGuildListWindow__vmt8 Update（CLICK_BUTTON2 + 69C690 + 479240/42B340/526BF0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDGuildListWindow__vmt8(uint32_t *this)
{
  int fld_e12; // eax
  uint8_t *result; // eax
  int fld_e2; // eax
  int v5; // ebx
  int fld_e59; // eax
  unsigned int fld_e60; // edi
  int fld_e16; // eax
  int fld_e592; // ecx
  int fld_e4; // edi
  int *v11; // eax
  uint32_t *pThis_D; // edi
  int i; // ebx
  int fld_e10; // eax
  int fld_e11; // eax

  sub_69A650(*(this + 2));  // 调 sub_69A650
  fld_e12 = *(this + 12);  // fld_e12 = this+12
  if ( *(uint8_t *)(fld_e12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e12 + 12) )  // 若 *(uint8_t *)(fld_e12 + 17) != 0 && dword_79BE34 == *(uint32_t ..
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);  // 虚调用 vt+32
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
  }
  else
  {
    fld_e2 = *(this + 2);  // fld_e2 = this+2
    if ( *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e2 + 12) )  // 若 *(uint8_t *)(fld_e2 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    {
      v5 = sub_644050(this);  // 结果 = 公会列表构建
      if ( v5 != -1 )  // 若 v5 != -1
      {
        fld_e59 = *(this + 59);  // fld_e59 = this+59
        fld_e60 = fld_e59 != 0 ? (*(this + 60) - fld_e59) >> 2 : 0;  // this+60 fade 值
        if ( v5 + sub_69C690(*(this + 16)) < fld_e60 )  // 取设备对象 +112 字段（类型或句柄）
        {
          fld_e16 = sub_69C690(*(this + 16));  // 结果 = 取设备对象 +112 字段（类型或句柄）
          fld_e592 = *(uint32_t *)(sub_479240((uint32_t *)dword_8F8514, *(uint32_t *)(*(this + 59) + 4 * (v5 + fld_e16))) + 48);
          if ( fld_e592 != 0 )  // 若 fld_e592 != 0
          {
            fld_e4 = *(uint32_t *)(*(this + 4) + 48);  // this+4 宿主对象
            v11 = (int *)sub_42B340(fld_e592);  // 结果 = 虚拟角色惰性创建（0x294 字节）
            sub_526BF0(fld_e4, v11, 1);  // 调 sub_526BF0
          }
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
        }
      }
    }
    pThis_D = this + 13;
    for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
    {
      if ( *(uint8_t *)(*pThis_D + 17) != 0 && dword_79BE34 == *(uint32_t *)(*pThis_D + 12) )  // 若 *(uint8_t *)(*pThis_D + 17) != 0 && dword_79BE34 == *(uint32_t..
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
      ++pThis_D;  // 自增pThis_D
    }
    fld_e10 = *(this + 10);  // fld_e10 = this+10
    if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 若 *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    {
      *(this + 57) = 1;  // this+228 = 1
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    }
    fld_e11 = *(this + 11);  // fld_e11 = this+11
    if ( *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e11 + 12) )  // 若 *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t ..
    {
      *(this + 57) = 0;  // this+228 = 0
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
    }
    result = (uint8_t *)*(this + 57);
    if ( result != nullptr )  // 若 result 非空
    {
      if ( result == (uint8_t *)1 )  // 若 result == (uint8_t *)1
      {
        *(uint8_t *)(*(this + 10) + 16) = 0;
        *(uint8_t *)(*(this + 11) + 16) = 1;
      }
    }
    else
    {
      *(uint8_t *)(*(this + 10) + 16) = 1;
      result = (uint8_t *)*(this + 11);
      result[16] = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x644260 sub_644260 —— 公会窗页部件（643F60 + 5542F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_644260(int this)  // 函数: 公会窗页部件（643F60 + 5542F0）
{
  *(uint32_t *)this = &vftbl_CNRDGuildListWindow;
  sub_643F60((uint32_t *)this);  // 公会窗数据
  if ( *(uint32_t *)(this + 236) != 0 )  // 若 *(uint32_t *)(this + 236) != 0
    j__free(*(void **)(this + 236));  // 调 j__free
  *(uint32_t *)(this + 236) = 0;  // this+236 = 0
  *(uint32_t *)(this + 240) = 0;  // this+240 = 0
  *(uint32_t *)(this + 244) = 0;  // this+244 = 0
  if ( *(uint32_t *)(this + 216) != 0 )  // 若 *(uint32_t *)(this + 216) != 0
  {
    DeleteObject(*(HGDIOBJ *)(this + 216));  // 调 DeleteObject 删除 GDI 对象
    *(uint32_t *)(this + 216) = 0;  // this+216 = 0
  }
  *(uint8_t *)(this + 172) = 0;  // this+172 = 0
  *(uint8_t *)(this + 173) = 0;  // this+173 = 0
  *(uint8_t *)(this + 174) = 0;  // this+174 = 0
  *(uint8_t *)(this + 175) = 0;  // this+175 = 0
  *(uint32_t *)(this + 184) = 0;  // this+184 = 0
  *(uint32_t *)(this + 188) = 0;  // this+188 = 0
  *(uint32_t *)(this + 192) = 0;  // this+192 = 0
  *(uint32_t *)(this + 196) = 0;  // this+196 = 0
  *(uint32_t *)(this + 200) = 0;  // this+200 = 0
  *(uint32_t *)(this + 204) = 0;  // this+204 = 0
  *(uint32_t *)(this + 208) = 0;  // this+208 = 0
  *(uint32_t *)(this + 212) = 0;  // this+212 = 0
  *(uint32_t *)(this + 216) = 0;  // this+216 = 0
  *(uint32_t *)(this + 220) = 0;  // this+220 = 0
  if ( *(uint32_t *)(this + 164) != 0 )  // 若 *(uint32_t *)(this + 164) != 0
  {
    DeleteObject(*(HGDIOBJ *)(this + 164));  // 调 DeleteObject 删除 GDI 对象
    *(uint32_t *)(this + 164) = 0;  // this+164 = 0
  }
  *(uint8_t *)(this + 120) = 0;  // this+120 = 0
  *(uint8_t *)(this + 121) = 0;  // this+121 = 0
  *(uint8_t *)(this + 122) = 0;  // this+122 = 0
  *(uint8_t *)(this + 123) = 0;  // this+123 = 0
  *(uint32_t *)(this + 132) = 0;  // this+132 = 0
  *(uint32_t *)(this + 136) = 0;  // this+136 = 0
  *(uint32_t *)(this + 140) = 0;  // this+140 = 0
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint32_t *)(this + 148) = 0;  // this+148 = 0
  *(uint32_t *)(this + 152) = 0;  // this+152 = 0
  *(uint32_t *)(this + 156) = 0;  // this+156 = 0
  *(uint32_t *)(this + 160) = 0;  // this+160 = 0
  *(uint32_t *)(this + 164) = 0;  // this+164 = 0
  *(uint32_t *)(this + 168) = 0;  // this+168 = 0
  if ( *(uint32_t *)(this + 112) != 0 )  // 若 *(uint32_t *)(this + 112) != 0
  {
    DeleteObject(*(HGDIOBJ *)(this + 112));  // 调 DeleteObject 删除 GDI 对象
    *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  }
  *(uint8_t *)(this + 68) = 0;  // this+68 = 0
  *(uint8_t *)(this + 69) = 0;  // this+69 = 0
  *(uint8_t *)(this + 70) = 0;  // this+70 = 0
  *(uint8_t *)(this + 71) = 0;  // this+71 = 0
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  return sub_5542F0(this);  // 窗口页数据 2
}



// ------------------------------------------------------------
// 0x6443E0 CNRDGuildListWindow__vmt4 —— CNRDGuildListWindow__vmt4 析构（转发 644260）
// ------------------------------------------------------------
void */*thiscall*/ CNRDGuildListWindow__vmt4(void *Block, char pszArg2)  // CNRDGuildListWindow__vmt4 析构（转发 644260）
{
  sub_644260((int)Block);  // 公会窗页部件（643F60 + 5542F0）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x644410 sub_644410 —— 公会列表页绘制（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630 + 699E20/699E40，188 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_644410(uint32_t *this)  // 函数: 公会列表页绘制（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630 + 699E20/699E40，188 行）
{
  uint32_t *pMem; // eax
  uint8_t *pMem62; // ebx
  uint32_t *fld_e9; // eax
  uint8_t *pMem2; // edi
  uint8_t *pMem3; // eax
  uint32_t *pMem32; // edi
  uint32_t *pMem322; // eax
  uint32_t *fld_e13; // eax
  uint8_t *pMem4; // edi
  uint32_t *pMem42; // ecx
  uint8_t *pMem5; // edi
  uint32_t *pMem52; // ecx
  uint8_t *pMem6; // edi
  int v15; // edx
  void *Block; // [esp+10h] [ebp-18h]
  void *Blocka; // [esp+10h] [ebp-18h]
  void *Blockb; // [esp+10h] [ebp-18h]
  void *Blockc; // [esp+10h] [ebp-18h]
  void *Blockd; // [esp+10h] [ebp-18h]
  uint32_t *pThis_D; // [esp+14h] [ebp-14h]
  int dword_79C0B0; // [esp+14h] [ebp-14h]
  int v24; // [esp+18h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // this+36 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  pMem = operator new(0x84u);  // 堆分配 132 字节对象
  pMem62 = nullptr;  // pMem62 = nullptr 空指针
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e9 = sub_43C410(pMem, *(this + 9), 23, 24, 25, 23, 0, 0);  // 结果 = nengine::CNButton 构造
  else
    fld_e9 = nullptr;  // fld_e9 = nullptr 空指针
  *(this + 12) = fld_e9;  // this+48 = fld_e9
  sub_69A5F0(fld_e9, 230, 11);  // 调 sub_69A5F0
  sub_69A840(*(this + 12));  // 调 sub_69A840
  v24 = 4;
  pThis_D = this + 13;
  do
  {
    pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
    if ( pMem2 != nullptr )  // 若 pMem2 非空
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(pMem2);  // nengine::IControl 构造
      *(uint32_t *)pMem2 = &nengine::CNButton::`vftable';
      sub_69C780(v5);  // 调 sub_69C780
      sub_69C7B0(Block, v24, v24, v24 + 1, v24, 0, 0);  // 调 sub_69C7B0
    }
    else
    {
      v5 = nullptr;  // v5 = nullptr 空指针
    }
    *v22++ = v5;  // *v22++ 写入 v5
    v24 += 2;
  }
  while ( v24 < 8 );  // 当 v24 < 8 循环
  v6 = operator new(0x88u);  // 堆分配 136 字节对象
  v7 = v6;
  if ( v6 != nullptr )  // 若 v6 非空
  {
    Blocka = (void *)*(this + 9);
    sub_426BD0(v6);  // nengine::IControl 构造
    *v7 = &nengine::CNSlider::`vftable';
    sub_69CA20(pMem32);  // 调 sub_69CA20
    sub_69CA50(Blocka, 151, 86);  // 调 sub_69CA50
    *pMem32 = &nengine::CNVSlider::`vftable';
    v8 = v7;
  }
  else
  {
    v8 = nullptr;  // v8 = nullptr 空指针
  }
  *(this + 15) = v8;  // this+60 = v8
  if ( operator new(0x74u) != nullptr )  // 堆分配 116 字节对象
    v9 = (uint32_t *)sub_43C630(*(this + 13), *(this + 14), *(this + 15));  // 结果 = nengine::CNVScroll 构造
  else
    v9 = nullptr;  // v9 = nullptr 空指针
  *(this + 16) = v9;  // this+64 = v9
  sub_69A5F0(v9, 239, 65);  // 调 sub_69A5F0
  sub_69A840(*(this + 16));  // 调 sub_69A840
  v10 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( v10 != nullptr )  // 若 v10 非空
  {
    Blockb = (void *)*(this + 9);
    sub_426BD0(v10);  // nengine::IControl 构造
    *(uint32_t *)v10 = &nengine::CNButton::`vftable';
    sub_69C780(pMem4);  // 调 sub_69C780
    sub_69C7B0(Blockb, 162, 163, 164, -1, 0, 0);  // 调 sub_69C7B0
    pMem42 = pMem4;
  }
  else
  {
    pMem42 = nullptr;  // pMem42 = nullptr 空指针
  }
  *(this + 10) = pMem42;  // this+40 = pMem42
  sub_69A5F0(pMem42, 91, 229);  // 调 sub_69A5F0
  sub_69A840(*(this + 10));  // 调 sub_69A840
  pMem5 = operator new(0x84u);  // 堆分配 132 字节对象
  if ( pMem5 != nullptr )  // 若 pMem5 非空
  {
    Blockc = (void *)*(this + 9);
    sub_426BD0(pMem5);  // nengine::IControl 构造
    *(uint32_t *)pMem5 = &nengine::CNButton::`vftable';
    sub_69C780(v12);  // 调 sub_69C780
    sub_69C7B0(Blockc, 159, 160, 161, -1, 0, 0);  // 调 sub_69C7B0
    v13 = v12;
  }
  else
  {
    v13 = nullptr;  // v13 = nullptr 空指针
  }
  *(this + 11) = v13;  // this+44 = v13
  sub_69A5F0(v13, 91, 229);  // 调 sub_69A5F0
  sub_69A840(*(this + 11));  // 调 sub_69A840
  *((uint8_t *)this + 68) = 0;  // this+68 角色数（begin/end 差 >>2；>=8 …
  *((uint8_t *)this + 69) = 0;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 71) = 0;  // this+71 移动类型
  *(this + 20) = 0;  // this+80 = 0
  *(this + 23) = 0;  // this+92 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  *(this + 28) = 0;  // this+112 = 0
  *(this + 29) = 0;  // this+116 = 0
  *(this + 24) = 1600;  // this+96 = 1600
  *(this + 21) = 6;  // this+84 = 6
  *(this + 22) = 12;  // this+88 = 12
  *(this + 29) = dword_99FCCC;  // this+116 = dword_99FCCC
  *(this + 18) = -16777216;  // this+72 = -16777216
  *(this + 34) = 6;  // this+136 = 6
  *((uint8_t *)this + 120) = 0;  // this+120 动画对象指针
  *((uint8_t *)this + 121) = 0;
  *((uint8_t *)this + 122) = 0;
  *((uint8_t *)this + 123) = 0;
  *(this + 33) = 0;  // this+132 = 0
  *(this + 35) = 12;  // this+140 = 12
  *(this + 36) = 0;  // this+144 = 0
  *(this + 37) = 1600;  // this+148 = 1600
  *(this + 38) = 0;  // this+152 = 0
  *(this + 39) = 0;  // this+156 = 0
  *(this + 40) = 0;  // this+160 = 0
  *(this + 41) = 0;  // this+164 = 0
  *(this + 42) = 0;  // this+168 = 0
  *(this + 42) = dword_99FCCC;  // this+168 = dword_99FCCC
  *(this + 31) = -16777216;  // this+124 = -16777216
  *(this + 37) = 144;  // this+148 = 144
  *(this + 33) = 1;  // this+132 = 1
  *(this + 38) = 1;  // this+152 = 1
  *((uint8_t *)this + 172) = 0;  // this+172 附属对象向量 end
  *((uint8_t *)this + 173) = 0;  // this+173 动画辅助标志
  *((uint8_t *)this + 174) = 0;  // this+174 动画辅助标志
  *((uint8_t *)this + 175) = 0;
  *(this + 46) = 0;  // this+184 = 0
  *(this + 47) = 6;  // this+188 = 6
  *(this + 48) = 12;  // this+192 = 12
  *(this + 49) = 0;  // this+196 = 0
  *(this + 50) = 1600;  // this+200 = 1600
  *(this + 51) = 0;  // this+204 = 0
  *(this + 52) = 0;  // this+208 = 0
  *(this + 53) = 0;  // this+212 = 0
  *(this + 54) = 0;  // this+216 = 0
  *(this + 55) = 0;  // this+220 = 0
  *(this + 55) = dword_99FCCC;  // this+220 = dword_99FCCC
  *(this + 44) = -16777216;  // this+176 = -16777216
  *(this + 46) = 1;  // this+184 = 1
  *(this + 51) = 1;  // this+204 = 1
  v14 = operator new(0x2Cu);  // 堆分配 44 字节对象
  if ( v14 != nullptr )  // 若 v14 非空
  {
    Blockd = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 12);
    v23 = dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
    v14[4] = 0;
    *(uint32_t *)v14 = &nengine::CNNumberSet::`vftable';
    sub_699E20(pMem6);  // 调 sub_699E20
    sub_699E40(dword_79C0B0, Blockd, 25, 2);  // 调 sub_699E40
    pMem62 = pMem6;
  }
  v15 = *this;
  *(this + 56) = pMem62;  // this+224 = pMem62
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v15 + 24))(this, 20, 19);  // 调用虚函数槽 +24
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);  // 虚调用 vt+28
}


// ------------------------------------------------------------
// 0x644890 sub_644890 —— 公会列表页部件 2（5542C0/5548B0 + 422E70 + 644410）
// ------------------------------------------------------------
int /*thiscall*/ sub_644890(int this, int nArg2)  // 函数: 公会列表页部件 2（5542C0/5548B0 + 422E70 + 644410）
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  sub_5542C0();  // 窗口页数据
  sub_5548B0(nArg2, 11);  // vmt4 三件套的公共尾
  *(uint32_t *)this = &vftbl_CNRDGuildListWindow;
  *(uint8_t *)(this + 68) = 0;  // this+68 = 0
  *(uint8_t *)(this + 69) = 0;  // this+69 = 0
  *(uint8_t *)(this + 70) = 0;  // this+70 = 0
  *(uint8_t *)(this + 71) = 0;  // this+71 = 0
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 6;  // this+84 = 6
  *(uint32_t *)(this + 88) = 12;  // this+88 = 12
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 1600;  // this+96 = 1600
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  *(uint32_t *)(this + 112) = 0;  // this+112 = 0
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint8_t *)(this + 120) = 0;  // this+120 = 0
  *(uint8_t *)(this + 121) = 0;  // this+121 = 0
  *(uint8_t *)(this + 122) = 0;  // this+122 = 0
  *(uint8_t *)(this + 123) = 0;  // this+123 = 0
  *(uint32_t *)(this + 132) = 0;  // this+132 = 0
  *(uint32_t *)(this + 136) = 6;  // this+136 = 6
  *(uint32_t *)(this + 140) = 12;  // this+140 = 12
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint32_t *)(this + 148) = 1600;  // this+148 = 1600
  *(uint32_t *)(this + 152) = 0;  // this+152 = 0
  *(uint32_t *)(this + 156) = 0;  // this+156 = 0
  *(uint32_t *)(this + 160) = 0;  // this+160 = 0
  *(uint32_t *)(this + 164) = 0;  // this+164 = 0
  *(uint32_t *)(this + 168) = 0;  // this+168 = 0
  *(uint8_t *)(this + 172) = 0;  // this+172 = 0
  *(uint8_t *)(this + 173) = 0;  // this+173 = 0
  *(uint8_t *)(this + 174) = 0;  // this+174 = 0
  *(uint8_t *)(this + 175) = 0;  // this+175 = 0
  *(uint32_t *)(this + 184) = 0;  // this+184 = 0
  *(uint32_t *)(this + 188) = 6;  // this+188 = 6
  *(uint32_t *)(this + 192) = 12;  // this+192 = 12
  *(uint32_t *)(this + 196) = 0;  // this+196 = 0
  *(uint32_t *)(this + 200) = 1600;  // this+200 = 1600
  *(uint32_t *)(this + 204) = 0;  // this+204 = 0
  *(uint32_t *)(this + 208) = 0;  // this+208 = 0
  *(uint32_t *)(this + 212) = 0;  // this+212 = 0
  *(uint32_t *)(this + 216) = 0;  // this+216 = 0
  *(uint32_t *)(this + 220) = 0;  // this+220 = 0
  *(uint32_t *)(this + 236) = 0;  // this+236 = 0
  *(uint32_t *)(this + 240) = 0;  // this+240 = 0
  *(uint32_t *)(this + 244) = 0;  // this+244 = 0
  if ( dword_9B953C[0] == 0 )  // 若 dword_9B953C[0] == 0
  {
    dword_9B953C[0] = (int)sub_422E70(939);  // dword_9B953C[0] 写入 (int)sub_422E70(939)
    dword_9B9540[0] = (int)sub_422E70(940);  // dword_9B9540[0] 写入 (int)sub_422E70(940)
  }
  *(uint32_t *)(this + 36) = 0;  // this+36 = 0
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  *(uint32_t *)(this + 52) = 0;  // this+52 = 0
  *(uint32_t *)(this + 56) = 0;  // this+56 = 0
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 40) = 0;  // this+40 = 0
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 228) = 0;  // this+228 = 0
  sub_644410((uint32_t *)this);  // 公会列表页绘制
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x644A20 sub_644A20 —— 公会数据重建（479110/479240/430C80，158 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_644A20(int this)  // 函数: 公会数据重建（479110/479240/430C80，158 行）
{
  void *fld_EC; // eax
  int pThis_E8; // esi
  int v3; // edx
  int v4; // edi
  int v5; // edx
  unsigned int v6; // ecx
  int *v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // edx
  unsigned int v13; // ecx
  int *v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // edx
  unsigned int v20; // ecx
  int *v21; // eax
  int v22; // ecx
  int v23; // eax
  int v25; // eax
  int v27; // [esp+8h] [ebp-8h]
  int v28; // [esp+Ch] [ebp-4h] BYREF

  fld_EC = *(void **)(this + 236);  // this+236 动画同步参数 A
  pThis_E8 = this + 232;  // this+232 动画时刻同步开关
  if ( fld_EC != nullptr )  // 若 fld_EC 非空
    j__free(fld_EC);  // 调 j__free
  *(uint32_t *)(pThis_E8 + 4) = 0;  // pThis_E8+4 = 0
  *(uint32_t *)(pThis_E8 + 8) = 0;  // pThis_E8+8 = 0
  *(uint32_t *)(pThis_E8 + 12) = 0;  // pThis_E8+12 = 0
  v3 = sub_479110(dword_8F8514);  // 调 sub_479110
  v4 = 0;
  v27 = v3;
  v28 = 0;
  if ( v3 > 0 )  // 若 v3 > 0
  {
    do
    {
      if ( *(uint32_t *)(sub_479240(v4) + 48) != 0 )  // 若 *(uint32_t *)(sub_479240(v4) + 48) != 0
      {
        v5 = *(uint32_t *)(pThis_E8 + 4);  // v5 = pThis_E8+4
        if ( v5 != 0 )  // 若 v5 != 0
          v6 = (*(uint32_t *)(pThis_E8 + 8) - v5) >> 2;  // pThis_E8=this+232 动画时刻同步开关
        else
          v6 = 0;
        if ( v5 != 0 && v6 < (*(uint32_t *)(pThis_E8 + 12) - v5) >> 2 )  // 若 v5 != 0 && v6 < (*(uint32_t *)(pThis_E8 + 12) - v5) >> 2
        {
          v7 = *(int **)(pThis_E8 + 8);  // pThis_E8=this+232 动画时刻同步开关
          *v7 = v4;  // *v7 写入 v4
          *(uint32_t *)(pThis_E8 + 8) = v7 + 1;  // pThis_E8+8 = v7 + 1
        }
        else
        {
          sub_430C80(*(void **)(pThis_E8 + 8), 1, (int)&v28);  // uint32 vector 区间插入（同值填充）
        }
      }
      v28 = ++v4;
    }
    while ( v4 < v27 );  // 当 v4 < v27 循环
    v3 = v27;
  }
  v8 = *(uint32_t *)(pThis_E8 + 4);  // v8 = pThis_E8+4
  if ( v8 != 0 )  // 若 v8 != 0
    v9 = (*(uint32_t *)(pThis_E8 + 8) - v8) >> 2;  // pThis_E8=this+232 动画时刻同步开关
  else
    v9 = 0;
  v10 = 0;
  *(uint32_t *)(this + 248) = v9;  // this+248 = v9
  v28 = 0;
  if ( v3 > 0 )  // 若 v3 > 0
  {
    do
    {
      v11 = sub_479240(v10);  // 调 sub_479240
      if ( *(int *)(v11 + 40) >= 0 && *(uint32_t *)(v11 + 48) == 0 )  // 若 *(int *)(v11 + 40) >= 0 && *(uint32_t *)(v11 + 48) == 0
      {
        v12 = *(uint32_t *)(pThis_E8 + 4);  // v12 = pThis_E8+4
        if ( v12 != 0 )  // 若 v12 != 0
          v13 = (*(uint32_t *)(pThis_E8 + 8) - v12) >> 2;  // pThis_E8=this+232 动画时刻同步开关
        else
          v13 = 0;
        if ( v12 != 0 && v13 < (*(uint32_t *)(pThis_E8 + 12) - v12) >> 2 )  // 若 v12 != 0 && v13 < (*(uint32_t *)(pThis_E8 + 12) - v12) >> 2
        {
          v14 = *(int **)(pThis_E8 + 8);  // pThis_E8=this+232 动画时刻同步开关
          *v14 = v10;  // *v14 写入 v10
          *(uint32_t *)(pThis_E8 + 8) = v14 + 1;  // pThis_E8+8 = v14 + 1
        }
        else
        {
          sub_430C80(*(void **)(pThis_E8 + 8), 1, (int)&v28);  // uint32 vector 区间插入（同值填充）
        }
      }
      v28 = ++v10;
    }
    while ( v10 < v27 );  // 当 v10 < v27 循环
    v3 = v27;
  }
  v15 = *(uint32_t *)(pThis_E8 + 4);  // v15 = pThis_E8+4
  if ( v15 != 0 )  // 若 v15 != 0
    v16 = (*(uint32_t *)(pThis_E8 + 8) - v15) >> 2;  // pThis_E8=this+232 动画时刻同步开关
  else
    v16 = 0;
  v17 = 0;
  *(uint32_t *)(this + 252) = v16;  // this+252 = v16
  v28 = 0;
  if ( v3 > 0 )  // 若 v3 > 0
  {
    do
    {
      v18 = sub_479240(v17);  // 调 sub_479240
      if ( *(int *)(v18 + 40) < 0 && *(uint32_t *)(v18 + 48) == 0 )  // 若 *(int *)(v18 + 40) < 0 && *(uint32_t *)(v18 + 48) == 0
      {
        v19 = *(uint32_t *)(pThis_E8 + 4);  // v19 = pThis_E8+4
        if ( v19 != 0 )  // 若 v19 != 0
          v20 = (*(uint32_t *)(pThis_E8 + 8) - v19) >> 2;  // pThis_E8=this+232 动画时刻同步开关
        else
          v20 = 0;
        if ( v19 != 0 && v20 < (*(uint32_t *)(pThis_E8 + 12) - v19) >> 2 )  // 若 v19 != 0 && v20 < (*(uint32_t *)(pThis_E8 + 12) - v19) >> 2
        {
          v21 = *(int **)(pThis_E8 + 8);  // pThis_E8=this+232 动画时刻同步开关
          *v21 = v17;  // *v21 写入 v17
          *(uint32_t *)(pThis_E8 + 8) = v21 + 1;  // pThis_E8+8 = v21 + 1
        }
        else
        {
          sub_430C80(*(void **)(pThis_E8 + 8), 1, (int)&v28);  // uint32 vector 区间插入（同值填充）
        }
      }
      v28 = ++v17;
    }
    while ( v17 < v27 );  // 当 v17 < v27 循环
  }
  v22 = *(uint32_t *)(pThis_E8 + 4);  // v22 = pThis_E8+4
  if ( v22 != 0 )  // 若 v22 != 0
    v23 = (*(uint32_t *)(pThis_E8 + 8) - v22) >> 2;  // pThis_E8=this+232 动画时刻同步开关
  else
    v23 = 0;
  if ( v23 - 8 < 0 )  // 若 v23 - 8 < 0
    return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 64) + 32))(*(uint32_t *)(this + 64), 0);  // 调用虚函数槽 +32
  v25 = *(uint32_t *)(pThis_E8 + 4);  // v25 = pThis_E8+4
  if ( v25 != 0 )  // 若 v25 != 0
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 64) + 32))(  // this+64 服务器页签按钮组 6 个
             *(uint32_t *)(this + 64),  // this+64 服务器页签按钮组 6 个
             ((*(uint32_t *)(pThis_E8 + 8) - v25) >> 2) - 8);  // pThis_E8=this+232 动画时刻同步开关
  else
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 64) + 32))(*(uint32_t *)(this + 64), -8);  // 调用虚函数槽 +32
}


// ------------------------------------------------------------
// 0x644C60 CNRDGuildListWindow__vmt0 —— CNRDGuildListWindow__vmt0 构造（309 行：554930/429830/429900/4BF0F0 + 644A20/418DD0/4BE300/4BE1D0 + 43BCB0）
// ------------------------------------------------------------
int /*userpurge*/ sub_644C60@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int pArg3)  // 函数: CNRDGuildListWindow__vmt0 构造（309 行：554930/429830/429900/4BF0F0 + 644A20/418DD0/4BE300/4BE1D0 + 43BCB0）
{
  int result; // eax
  int v5; // edi
  int v6; // ebx
  void *v7; // eax
  int v8; // edi
  int pObj; // eax
  int v10; // ecx
  int pObj7; // eax
  int v12; // edx
  int v13; // edi
  int v14; // ebx
  int v15; // eax
  int v16; // edx
  int v17; // edi
  int v18; // eax
  uint8_t v19; // al
  int pObj8; // eax
  int v21; // ecx
  int v22; // edi
  int v23; // eax
  int v24; // ecx
  int v25; // ebx
  int pObj2; // eax
  int v27; // ecx
  uint32_t *v28; // edi
  int v29; // ecx
  int pObj5; // eax
  int pObj3; // eax
  uint32_t *v32; // ecx
  int v33; // edx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int pObj4; // eax
  int pObj9; // eax
  int pObj6; // eax
  bool v40; // cc
  LONG x; // esi
  LONG y; // edi
  uint8_t v43; // bl
  int v44; // eax
  const char *v45; // eax
  int v46; // [esp-Ch] [ebp-248h]
  int v47; // [esp-Ch] [ebp-248h]
  int v48; // [esp-Ch] [ebp-248h]
  int v49; // [esp-8h] [ebp-244h]
  int v50; // [esp-8h] [ebp-244h]
  int v51; // [esp-8h] [ebp-244h]
  int v52; // [esp-8h] [ebp-244h]
  RECT rc; // [esp+8h] [ebp-234h] BYREF
  int v55; // [esp+18h] [ebp-224h]
  int v56; // [esp+1Ch] [ebp-220h]
  int v57; // [esp+20h] [ebp-21Ch]
  unsigned int v58; // [esp+24h] [ebp-218h]
  int v59; // [esp+28h] [ebp-214h]
  int v60; // [esp+2Ch] [ebp-210h]
  int v61; // [esp+30h] [ebp-20Ch]
  int v62; // [esp+34h] [ebp-208h]
  char Buffer[512]; // [esp+38h] [ebp-204h] BYREF
  int dword_796E502; // [esp+238h] [ebp-4h]
  int v65; // [esp+244h] [ebp+8h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = sub_554930(pArg3);  // 【IRDPopupWindow__vmt0】
  if ( pArg3 == pArg1[2] )  // 若 pArg3 == pArg1[2]
  {
    v5 = *(uint32_t *)(pArg3 + 20);  // v5 = pArg3+20
    v6 = *(uint32_t *)(pArg3 + 24);  // v6 = pArg3+24
    v65 = v5;
    v59 = v6;
    result = sub_429830((uint16_t)word_77F804);  // 结果 = 表按键查找（uint16）
    if ( result != 0 )  // 若 result != 0
    {
      v7 = (void *)sub_429900(dword_8F8500);  // 结果 = 本机槽实体查询（word_77F804 键）
      if ( v7 != nullptr )  // 若 v7 非空
      {
        v61 = sub_4BF0F0(v7);  // 结果 = 取或建工会信息对象（get_or_create）
        sub_644A20(pArg1);  // 公会数据重建
        v8 = v5 + 6;
        pObj = sub_418DD0(165);  // 调 sub_418DD0
        if ( pObj != 0 )  // 若 pObj != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v8, v6 + 6, dword_79C0B0);  // 调用虚函数槽 +152
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 43, nArg2);  // 调用虚函数槽 +72
        pArg1[50] = 243;
        pArg1[46] = 1;
        if ( *(uint32_t *)(dword_8F8514 + 44) < 0x10u )  // 若 *(uint32_t *)(dword_8F8514 + 44) < 0x10u
          v10 = dword_8F8514 + 24;
        else
          v10 = *(uint32_t *)(dword_8F8514 + 24);  // v10 = dword_8F8514+24
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          v65 + 6,
          v6 + 13,
          -5512193,
          v10);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
        sub_4BE300(v61);  // 技能图标装载（+48 槽；sub_419480/419550）
        pObj7 = sub_418DD0(189);  // 调 sub_418DD0
        if ( pObj7 != 0 )  // 若 pObj7 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v65 + 7, v6 + 33, dword_79C0B0);  // 调用虚函数槽 +152
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 43);  // 调用虚函数槽 +72
        v12 = pArg1[62];
        v49 = pArg1[63];
        pArg1[50] = 147;
        pArg1[46] = 1;
        v13 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
        v46 = v12;
        v14 = v6 + 40;
        v15 = sub_422E70(941);  // 调 sub_422E70
        (*(void (/*cdecl*/ **)(int, int, int, int, int, int, int))(v13 + 80))(
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          v65 + 101,
          v14,
          -4928551,
          v15,
          v46,
          v49);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 43);  // 调用虚函数槽 +72
        v16 = pArg1[62];
        v50 = pArg1[63];
        pArg1[46] = 0;
        v17 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
        v47 = v16;
        v18 = sub_422E70(942);  // 调 sub_422E70
        (*(void (/*cdecl*/ **)(int, int, int, int, int, int, int))(v17 + 80))(
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          v65 + 22,
          v14,
          -4928551,
          v18,
          v47,
          v50);
        if ( (uint8_t)sub_4BE1D0(v61) != 0xFF )  // 标志读取（this+12）
        {
          v60 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
          v19 = sub_4BE1D0(v61);  // 结果 = 标志读取（this+12）
          (*(void (**)(int, int, int, int, const char *, ...))(v60 + 80))(
            dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
            v65 + 72,
            v14,
            -701185,
            "%d",  // 字符串 “%d”
            v19 + 1);
        }
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
        pObj8 = sub_418DD0(150);  // 调 sub_418DD0
        if ( pObj8 != 0 )  // 若 pObj8 != 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj8 + 152))(pObj8, v65 + 7, v59 + 63, dword_79C0B0);  // 调用虚函数槽 +152
        v21 = pArg1[16];
        v22 = v59 + 69;
        v62 = v59 + 69;
        v23 = sub_69C690(v21);  // 结果 = 取设备对象 +112 字段（类型或句柄）
        v24 = pArg1[2];
        v58 = v23;
        if ( (uint8_t)sub_43BCB0(v24) == 1 )  // 焦点窗口判定（三选）
          v56 = sub_644050(pArg1);  // 结果 = 公会列表构建
        else
          v56 = -1;
        v25 = v59 + 72;
        v57 = 0;
        v60 = v59 + 72;
        do
        {
          pObj2 = sub_418DD0(94);  // 调 sub_418DD0
          if ( pObj2 != 0 )  // 若 pObj2 != 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v65 + 12, v22, dword_79C0B0);  // 调用虚函数槽 +152
          v27 = pArg1[59];
          if ( v27 != 0 && v58 < (pArg1[60] - v27) >> 2 )  // 若 v27 != 0 && v58 < (pArg1[60] - v27) >> 2
          {
            v28 = (uint32_t *)sub_479240(*(uint32_t *)(pArg1[59] + 4 * v58));
            v29 = v28[12];
            if ( v29 != 0 )  // 若 v29 != 0
            {
              pObj5 = sub_42B340(v29);  // 结果 = 虚拟角色惰性创建（0x294 字节）
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)pObj5 + 384))(  // 虚槽+384 槽数组 getter（+348 起，越界返回 0）
                pObj5,
                v65 + 12,
                v62,
                16,
                16,
                1065353216);
            }
            else
            {
              pObj3 = sub_418DD0(108);  // 调 sub_418DD0
              if ( pObj3 != 0 )  // 若 pObj3 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v65 + 12, v62, dword_79C0B0);  // 调用虚函数槽 +152
            }
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 17);  // 调用虚函数槽 +72
            (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              v65 + 35,
              v25,
              v28[12] != 0 ? -4928551 : -8947849,
              "Lv.%d",  // 字符串 “Lv.%d”
              v28[7]);
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, pArg1 + 30);  // 调用虚函数槽 +68
            if ( v28[6] < 0x10u )  // 若 v28[6] < 0x10u
              v32 = v28 + 1;
            else
              v32 = (uint32_t *)v28[1];
            (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
              dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
              v65 + 29,
              v25,
              v28[12] != 0 ? -4928551 : -8947849,
              v32);
            if ( pArg1[57] == 0 )  // 若 pArg1[57] == 0
            {
              v33 = v28[8];
              v51 = v28[9];
              v55 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
              v34 = sub_4B0EC0(v33, v51);  // 结果 = 表记录字符串取值（28 字节/条）
              v25 = v60;
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(v55 + 80))(
                dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                v65 + 108,
                v60,
                v28[12] != 0 ? -8005942 : -9934744,
                v34);
            }
            if ( pArg1[57] == 1 )  // 若 pArg1[57] == 1
              (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
                dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
                v65 + 108,
                v25,
                v28[12] != 0 ? -3897898 : -9934744,
                v28 + 13);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
            v35 = v28[12];
            if ( v35 != 0 )  // 若 v35 != 0
            {
              if ( *(uint32_t *)(v35 + 68) != 0 )  // 若 *(uint32_t *)(v35 + 68) != 0
                v36 = 154;
              else
                v36 = *(uint32_t *)(v35 + 184) != 0 ? 158 : 155;
              pObj4 = sub_418DD0(v36);  // 调 sub_418DD0
              if ( pObj4 != 0 )  // 若 pObj4 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v65 + 224, v62, dword_79C0B0);  // 调用虚函数槽 +152
            }
            else if ( (int)v28[10] >= 0 )  // 否则若 (int)v28[10] >= 0
            {
              pObj9 = sub_418DD0(155);  // 调 sub_418DD0
              if ( pObj9 != 0 )  // 若 pObj9 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj9 + 152))(pObj9, v65 + 224, v62, dword_79C0B0);  // 调用虚函数槽 +152
              sub_69A110(v65 + 220, v25 + 1, v28[10], -1);  // 调 sub_69A110
            }
            if ( v57 == v56 )  // 若 v57 == v56
            {
              sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
              pObj6 = sub_418DD0(22);  // 调 sub_418DD0
              if ( pObj6 != 0 )  // 若 pObj6 != 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, v65 + 9, v25 - 4, dword_79C0B0);  // 调用虚函数槽 +152
              sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
            }
          }
          v22 = v62 + 19;
          v25 += 19;
          v40 = ++v57 < 8;
          ++v58;  // 自增v58
          v62 += 19;
          v60 = v25;
        }
        while ( v40 );  // 当 v40 循环
        result = sub_4BE1D0(v61);  // 结果 = 标志读取（this+12）
        if ( (uint8_t)result != 0xFF )  // 若 (uint8_t)result != 0xFF
        {
          x = pt.x;
          y = pt.y;
          v43 = sub_4BE1D0(v61);  // 结果 = 标志读取（this+12）
          rc.left = v65 + 7;
          rc.top = v59 + 33;
          rc.right = v65 + 98;
          rc.bottom = v59 + 58;
          result = PtInRect(&rc, (POINT)__PAIR64__(y, x));  // 调 __PAIR64__（拼装 64 位值(高32,低32)）
          if ( result == 1 )  // 若 result == 1
          {
            if ( v43 == 1 )  // 若 v43 == 1
            {
              sprintf(Buffer, "%s\n", (const char *)dword_9B9540[0]);  // 字符串 “%s\n”
            }
            else
            {
              v44 = v43;
              v52 = dword_9B9540[v44];
              v48 = dword_9B953C[v44];
              v45 = (const char *)sub_422E70(943);  // 调 存 CStringManager::getStr 取本地化串
              sprintf(Buffer, v45, v48, v52);  // 调 sprintf 格式化
            }
            return sub_4649B0(rc.left + (rc.right - rc.left) / 2, rc.top - 2, -1, -16777216, 2, Buffer, 0, 0, 1600, 1);  // 带框文本上屏（静态一次性初始化）
          }
        }
      }
      else
      {
        return (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 32))(pArg1);  // 虚调用 vt+32
      }
    }
  }
  return result;
}


// ============================================================
// 【分区 8】商城购买窗 CNRDCashShopBuyWindow（0x6453A0-0x648F90）
// vmt0 装配（648770：6466D0/646C70 双倍活动面板 cashshopdoubleevent.img +
// 645680/645930 列表）；648980 Update（139 行：CLICK_MOVE/COMMAND_SELECT/
// SCROLL_ARROW 事件）；647BF0 购买页绘制（509 行）；
// 648EB0 CFileVersionInfo（版本信息查询桩）。
// ============================================================
// ------------------------------------------------------------
// 0x6453A0 sub_6453A0 —— 商城数据（17 行）
// ------------------------------------------------------------
int /*cdecl*/ sub_6453A0(int nArg1, unsigned int uArg2)  // 函数: 商城数据（17 行）
{
  if ( uArg2 < 2 )  // 若 uArg2 < 2
    return nArg1;
  if ( uArg2 == 2 )  // 若 uArg2 == 2
    return 2 * nArg1;
  if ( uArg2 == 3 )  // 若 uArg2 == 3
    return 4 * nArg1;
  else
    return nArg1;
}



// ------------------------------------------------------------
// 0x6453D0 sub_6453D0 —— 商城数据 2（26 行）
// ------------------------------------------------------------
const CHAR */*cdecl*/ sub_6453D0(int nArg1)  // 商城数据 2
{
  const CHAR *result; // eax

  switch ( nArg1 )  // 分支：按 nArg1 分派
  {
    case 0:
      return (const CHAR *)&unk_73E2A4;
    case 1:
      return (const CHAR *)&unk_73E2A0;
    case 2:
      return (const CHAR *)&unk_73E298;
    default:
      break;
  }
  result = (const CHAR *)&unk_73E2A4;
  if ( nArg1 != 3 )  // 若 nArg1 != 3
    return szPassword;
  return result;
}



// ------------------------------------------------------------
// 0x645410 sub_645410 —— 商城数据 3（45 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645410(int this)  // 函数: 商城数据 3（45 行）
{
  uint32_t *pThis_20; // ecx

  *(uint32_t *)(this + 4) = 0;  // this+4 = 0
  *(uint32_t *)(this + 8) = 0;  // this+8 = 0
  *(uint32_t *)(this + 12) = 0;  // this+12 = 0
  *(uint32_t *)(this + 20) = 0;  // this+20 = 0
  *(uint32_t *)(this + 24) = 0;  // this+24 = 0
  *(uint32_t *)(this + 28) = 0;  // this+28 = 0
  pThis_20 = (uint32_t *)(this + 32);  // this+32 格子像素尺寸
  *pThis_20 = 0;  // *pThis_20 写入 0
  pThis_20[1] = 0;  // pThis_20=this+32 格子像素尺寸
  pThis_20[2] = 0;  // pThis_20=this+32 格子像素尺寸
  *(uint32_t *)(this + 44) = 0;  // this+44 = 0
  *(uint32_t *)(this + 48) = 0;  // this+48 = 0
  memset((void *)(this + 52), 0, 0x40u);  // 清零 64 字节块
  *(uint32_t *)(this + 116) = 0;  // this+116 = 0
  *(uint32_t *)(this + 120) = 0;  // this+120 = 0
  *(uint32_t *)(this + 124) = 0;  // this+124 = 0
  *(uint32_t *)(this + 128) = 0;  // this+128 = 0
  *(uint32_t *)(this + 2072) = 0;  // this+2072 = 0
  *(uint32_t *)(this + 2076) = 0;  // this+2076 = 0
  *(uint32_t *)(this + 2080) = 0;  // this+2080 = 0
  *(uint32_t *)(this + 2084) = 0;  // this+2084 = 0
  memset((void *)(this + 2088), 0, 0xF0u);  // 清零 240 字节块
  memset((void *)(this + 340), 0, 0x690u);  // 清零 1680 字节块
  *(uint32_t *)(this + 2020) = 0;  // this+2020 = 0
  *(uint32_t *)(this + 2024) = 0;  // this+2024 = 0
  *(uint32_t *)(this + 2028) = 0;  // this+2028 = 0
  *(uint32_t *)(this + 2032) = 0;  // this+2032 = 0
  *(uint32_t *)(this + 2036) = 0;  // this+2036 = 0
  *(uint32_t *)(this + 2040) = 0;  // this+2040 = 0
  *(uint32_t *)(this + 2044) = 0;  // this+2044 = 0
  *(uint32_t *)(this + 2048) = 0;  // this+2048 = 0
  *(uint8_t *)(this + 2052) = 0;  // this+2052 = 0
  *(uint32_t *)(this + 2068) = 0;  // this+2068 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x6454C0 sub_6454C0 —— 商城 MonoLayer 面板（Common/Etc/MonoLayer.img + 418DD0，78 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6454C0(uint32_t *this)  // 函数: 商城 MonoLayer 面板（Common/Etc/MonoLayer.img + 418DD0，78 行）
{
  int (/*thiscall*/ ***fld_e3)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx
  uint32_t *pThis_8; // edi
  int i; // ebx
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  uint32_t *pThis_1D; // edi
  int j; // ebx
  int (/*thiscall*/ ***fld_e32)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e31)(uint32_t, int); // ecx
  uint32_t *pThis_206; // edi
  int k; // ebx
  uint32_t *pThis_20A; // esi
  int m; // edi

  fld_e3 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  if ( fld_e3 != nullptr )  // 若 fld_e3 非空
    result = (**fld_e3)(fld_e3, 1);
  fld_e4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);  // this+4 宿主对象
  *(this + 3) = 0;  // this+12 = 0
  if ( fld_e4 != nullptr )  // 若 fld_e4 非空
    result = (**fld_e4)(fld_e4, 1);
  *(this + 4) = 0;  // this+16 = 0
  pThis_8 = this + 8;  // this+8 物品 id
  for ( i = 3; i != 0; --i )  // 循环：i = 3; i != 0; --i
  {
    if ( *pThis_8 != 0 )  // 若 *pThis_8 != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_8)(*pThis_8, 1);  // pThis_8=this+8 物品 id
    *pThis_8++ = 0;  // *pThis_8++ 写入 0
  }
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( fld_e11 != nullptr )  // 若 fld_e11 非空
    result = (**fld_e11)(fld_e11, 1);
  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);  // this+12 物品类型号
  *(this + 11) = 0;  // this+44 = 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 非空
    result = (**fld_e12)(fld_e12, 1);
  *(this + 12) = 0;  // this+48 = 0
  pThis_1D = this + 29;  // this+29 pSessionCtx
  for ( j = 2; j != 0; --j )  // 循环：j = 2; j != 0; --j
  {
    if ( *pThis_1D != 0 )  // 若 *pThis_1D != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_1D)(*pThis_1D, 1);  // pThis_1D=this+29 pSessionCtx
    *pThis_1D++ = 0;  // *pThis_1D++ 写入 0
  }
  fld_e32 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 32);  // this+32 格子像素尺寸
  if ( fld_e32 != nullptr )  // 若 fld_e32 非空
    result = (**fld_e32)(fld_e32, 1);
  fld_e31 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 32) = 0;  // this+128 = 0
  if ( fld_e31 != nullptr )  // 若 fld_e31 非空
    result = (**fld_e31)(fld_e31, 1);
  *(this + 31) = 0;  // this+124 = 0
  pThis_206 = this + 518;
  for ( k = 4; k != 0; --k )  // 循环：k = 4; k != 0; --k
  {
    if ( *pThis_206 != 0 )  // 若 *pThis_206 != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_206)(*pThis_206, 1);
    *pThis_206++ = 0;  // *pThis_206++ 写入 0
  }
  pThis_20A = this + 522;
  for ( m = 60; m != 0; --m )  // 循环：m = 60; m != 0; --m
  {
    if ( *pThis_20A != 0 )  // 若 *pThis_20A != 0
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_20A)(*pThis_20A, 1);
    *pThis_20A++ = 0;  // *pThis_20A++ 写入 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x6455D0 sub_6455D0 —— 商城面板（418DD0，42 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6455D0(uint32_t *this)  // 函数: 商城面板（418DD0，42 行）
{
  int pObj; // eax
  int fld_e510; // esi
  int result; // eax

  (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Common/Etc/MonoLayer.img");  // 字符串 “Common/Etc/MonoLayer.img”
  pObj = sub_418DD0(0);  // 调 sub_418DD0
  if ( pObj != 0 )  // 若 pObj != 0
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
      pObj,
      0,
      0,
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      1098907648,
      1094713344,
      0,
      -922746881,
      1333788672,
      1333788672);
  fld_e510 = *(this + 510);  // fld_e510 = this+510
  result = sub_418DD0(fld_e510 != 0 ? 0 : 0x23);  // 调 sub_418DD0
  if ( result != 0 )  // 若 result != 0
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
             result,
             dword_73E220[fld_e510],
             58,
             dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
             1065353216,
             1065353216,
             0,
             -1,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x645680 sub_645680 —— 商城列表构建（422E70 + 69A110，137 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645680(int16_t *this)  // 函数: 商城列表构建（422E70 + 69A110，137 行）
{
  int v2; // edi
  int v3; // ebx
  int16_t *pThis_B7; // edx
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  bool v10; // zf
  const char *v11; // eax
  const char *v12; // eax
  const char *v13; // eax
  int v14; // edi
  int v15; // eax
  int pThis_1FD2; // [esp-4h] [ebp-11Ch]
  int pThis_1FD; // [esp+Ch] [ebp-10Ch]
  int Value; // [esp+10h] [ebp-108h]
  char Buffer[256]; // [esp+14h] [ebp-104h] BYREF
  int dword_796E502; // [esp+114h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (uint32_t *)this + 33);  // 调用虚函数槽 +72
  sprintf(Buffer, "%2d/%-2d", *((uint32_t *)this + 511) + 1, *((uint32_t *)this + 512) + 1);  // 字符串 “%2d/%-2d”
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 160, 409, -1, Buffer);  // 调用虚函数槽 +80
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  v2 = 0;
  v3 = 0;
  Value = 0;
  if ( *((int *)this + 509) > 0 )  // 若 *((int *)this + 509) > 0
  {
    pThis_B7 = this + 183;
    pThis_1FD = *((uint32_t *)this + 509);
    while ( 1 )  // 当 1 循环
    {
      v5 = *pThis_B7;
      v6 = *(uint32_t *)(pThis_B7 + 3);  // v6 = pThis_B7+3
      if ( *pThis_B7 != 0 && v5 != 1 )  // 若 *pThis_B7 != 0 && v5 != 1
      {
        if ( v5 == 2 )  // 若 v5 == 2
        {
          v6 *= 2;
        }
        else if ( v5 == 3 )  // 否则若 v5 == 3
        {
          v6 *= 4;
        }
      }
      v3 += v6;  // v3 累加 v6
      v7 = *(uint32_t *)(pThis_B7 + 5);  // v7 = pThis_B7+5
      if ( *pThis_B7 != 0 && v5 != 1 )  // 若 *pThis_B7 != 0 && v5 != 1
      {
        if ( v5 == 2 )  // 若 v5 == 2
        {
          v7 *= 2;
        }
        else if ( v5 == 3 )  // 否则若 v5 == 3
        {
          v7 *= 4;
        }
      }
      v2 += v7;  // v2 累加 v7
      v8 = *(uint32_t *)(pThis_B7 + 7);  // v8 = pThis_B7+7
      if ( *pThis_B7 == 0 || v5 == 1 )  // 若 *pThis_B7 == 0 || v5 == 1
        break;
      if ( v5 == 2 )  // 若 v5 == 2
      {
        v9 = 2 * v8;
      }
      else
      {
        v10 = v5 == 3;
        v9 = 4 * v8;
        if ( !v10 )  // 若 !v10
          break;
      }
LABEL_21:
      pThis_B7 += 42;
      v10 = pThis_1FD == 1;
      Value += v9;  // Value 累加 v9
      --pThis_1FD;  // 自减pThis_1FD
      if ( v10 )  // 若 v10
        goto LABEL_22;  // 跳转 LABEL_22
    }
    v9 = *(uint32_t *)(pThis_B7 + 7);  // v9 = pThis_B7+7
    goto LABEL_21;  // 跳转 LABEL_21
  }
LABEL_22:
  (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (uint32_t *)this + 72);  // 调用虚函数槽 +72
  pThis_1FD2 = *((uint32_t *)this + 509);
  v11 = (const char *)sub_422E70(891);  // 调 存 CStringManager::getStr 取本地化串
  sprintf(Buffer, v11, pThis_1FD2);  // 调 sprintf 格式化
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 403, 141, -1, Buffer);  // 调用虚函数槽 +80
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (uint32_t *)this + 46);  // 调用虚函数槽 +72
  if ( v2 > 0 )  // 若 v2 > 0
  {
    v12 = (const char *)sub_422E70(892);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v12, v2);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      454 - *((uint32_t *)this + 53),
      187,
      -15920333,
      Buffer);
  }
  if ( v3 > 0 )  // 若 v3 > 0
  {
    v13 = (const char *)sub_422E70(893);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v13, v3);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      593 - *((uint32_t *)this + 53),
      187,
      -15920333,
      Buffer);
  }
  if ( Value > 0 )  // 若 Value > 0
  {
    sub_69A110(568, 215, Value, -1);  // 调 sub_69A110
    v14 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
    v15 = sub_422E70(894);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v14 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      592 - *((uint32_t *)this + 53),
      219,
      -15920333,
      v15);
  }
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
}


// ------------------------------------------------------------
// 0x645930 sub_645930 —— 商城列表构建 2（422E70 + 69A110，164 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645930(uint32_t *this)  // 函数: 商城列表构建 2（422E70 + 69A110，164 行）
{
  int fld_e510; // ecx
  BOOL v3; // edi
  int fld_e509; // eax
  int16_t *pThis_B7; // edx
  unsigned int v6; // eax
  int v7; // ecx
  int v8; // ebx
  int v9; // ecx
  int v10; // ebx
  int v11; // ecx
  int v12; // eax
  bool v13; // zf
  int v14; // eax
  int v15; // ecx
  const char *v16; // eax
  unsigned int v17; // edi
  const char *v18; // eax
  int v19; // ebx
  int v20; // eax
  int fld_e515; // [esp-4h] [ebp-164h]
  int fld_e514; // [esp-4h] [ebp-164h]
  int v24; // [esp+Ch] [ebp-154h]
  int v25; // [esp+10h] [ebp-150h]
  int v26; // [esp+14h] [ebp-14Ch]
  int v27; // [esp+18h] [ebp-148h]
  int v28; // [esp+1Ch] [ebp-144h]
  int v29; // [esp+20h] [ebp-140h]
  int v30; // [esp+24h] [ebp-13Ch]
  uint32_t v31[9]; // [esp+28h] [ebp-138h]
  int fld_e5092; // [esp+4Ch] [ebp-114h]
  int v33; // [esp+50h] [ebp-110h]
  int v34; // [esp+54h] [ebp-10Ch]
  int v35; // [esp+58h] [ebp-108h]
  char Buffer[256]; // [esp+5Ch] [ebp-104h] BYREF
  int dword_796E502; // [esp+15Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v25 = 265;
  v27 = 265;
  fld_e510 = *(this + 510);  // fld_e510 = this+510
  v31[2] = 255;
  v31[4] = 255;
  v24 = 454;
  v26 = 593;
  v28 = 572;
  v29 = 289;
  v30 = 596;
  v3 = fld_e510 != 0;
  fld_e509 = *(this + 509);  // fld_e509 = this+509
  v31[0] = 293;
  v31[1] = 307;
  v31[3] = 447;
  v31[5] = 416;
  v31[6] = 281;
  v31[7] = 440;
  v31[8] = 284;
  v33 = 0;
  v34 = 0;
  v35 = 0;
  if ( fld_e509 > 0 )  // 若 fld_e509 > 0
  {
    pThis_B7 = (int16_t *)this + 183;
    fld_e5092 = fld_e509;
    while ( 1 )  // 当 1 循环
    {
      v6 = *pThis_B7;
      v7 = *(uint32_t *)(pThis_B7 + 3);  // v7 = pThis_B7+3
      if ( *pThis_B7 != 0 && v6 != 1 )  // 若 *pThis_B7 != 0 && v6 != 1
      {
        if ( v6 == 2 )  // 若 v6 == 2
        {
          v7 *= 2;
        }
        else if ( v6 == 3 )  // 否则若 v6 == 3
        {
          v7 *= 4;
        }
      }
      v8 = v7 + v33;
      v9 = *(uint32_t *)(pThis_B7 + 5);  // v9 = pThis_B7+5
      v33 = v8;
      if ( v6 >= 2 )  // 若 v6 >= 2
      {
        if ( v6 == 2 )  // 若 v6 == 2
        {
          v9 *= 2;
        }
        else if ( v6 == 3 )  // 否则若 v6 == 3
        {
          v9 *= 4;
        }
      }
      v10 = v9 + v34;
      v11 = *(uint32_t *)(pThis_B7 + 7);  // v11 = pThis_B7+7
      v34 = v10;
      if ( v6 < 2 )  // 若 v6 < 2
        break;
      if ( v6 == 2 )  // 若 v6 == 2
      {
        v12 = 2 * v11;
      }
      else
      {
        v13 = v6 == 3;
        v12 = 4 * v11;
        if ( !v13 )  // 若 !v13
          break;
      }
LABEL_19:
      pThis_B7 += 42;
      v13 = fld_e5092 == 1;
      v35 += v12;  // v35 累加 v12
      --fld_e5092;  // 自减fld_e5092
      if ( v13 )  // 若 v13
        goto LABEL_20;  // 跳转 LABEL_20
    }
    v12 = v11;
    goto LABEL_19;  // 跳转 LABEL_19
  }
LABEL_20:
  *(this + 514) = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3))  // 全局 dword_8F852C = 角色/物品栏管理器
                - v33;
  v14 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));  // 全局 dword_8F852C = 角色/物品栏管理器
  v15 = v35;
  *(this + 515) = v14 - v34;  // this+2060 = v14 - v34
  *(this + 516) = dword_8F7C0C - v15;  // 全局 dword_8F7C0C = 现金(Cash)
  (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 46);  // 调用虚函数槽 +72
  fld_e515 = *(this + 515);  // fld_e515 = this+515
  v16 = (const char *)sub_422E70(899);  // 调 存 CStringManager::getStr 取本地化串
  sprintf(Buffer, v16, fld_e515);  // 调 sprintf 格式化
  v17 = 32 * v3;
  (*(void (/*cdecl*/ **)(int, int, uint32_t, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
    *(int *)((char *)&v24 + v17) - *(this + 53),
    *(int *)((char *)&v25 + v17),
    (int)*(this + 515) < 0 ? -16776961 : -1,
    Buffer);
  fld_e514 = *(this + 514);  // fld_e514 = this+514
  v18 = (const char *)sub_422E70(900);  // 调 存 CStringManager::getStr 取本地化串
  sprintf(Buffer, v18, fld_e514);  // 调 sprintf 格式化
  (*(void (/*cdecl*/ **)(int, int, uint32_t, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
    *(int *)((char *)&v26 + v17) - *(this + 53),
    *(int *)((char *)&v27 + v17),
    (int)*(this + 514) < 0 ? -16776961 : -1,
    Buffer);
  sub_69A110(*(int *)((char *)&v28 + v17), *(int *)((char *)&v29 + v17), *(this + 516), -1);  // 调 sub_69A110
  v19 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
  v20 = sub_422E70(901);  // 调 sub_422E70
  (*(void (/*cdecl*/ **)(int, int, uint32_t, int, int))(v19 + 80))(
    dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
    v31[v17 / 4 - 1] - *(this + 53),
    v31[v17 / 4],
    (int)*(this + 514) < 0 ? -16776961 : -1,
    v20);
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
}


// ------------------------------------------------------------
// 0x645CA0 sub_645CA0 —— 商城取消（12 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645CA0(uint32_t *this)  // 函数: 商城取消（12 行）
{
  *(uint8_t *)(*(this + 3) + 16) = 0;
  memset(this + 85, 0, 0x690u);  // 清零 1680 字节块
  return 0;
}



// ------------------------------------------------------------
// 0x645CC0 sub_645CC0 —— 商城下单确认（423200 系参数 + 55F160/55D300/55CB40，45 行——被确认窗 vmt38 调用）
// ------------------------------------------------------------
int /*thiscall*/ sub_645CC0(int this)  // 函数: 商城下单确认（423200 系参数 + 55F160/55D300/55CB40，45 行——被确认窗 vmt38 调用）
{
  int v2; // ebx
  int pThis_164; // esi
  int v5; // [esp+8h] [ebp-8h] BYREF
  uint8_t v6[4]; // [esp+Ch] [ebp-4h] BYREF

  v2 = 0;
  *(uint32_t *)(*(uint32_t *)(this + 8) + 10108) = 0;  // this+8 物品 id
  sub_423200(dword_8F7B08, 67);  // 【发送网络包API】
  v6[0] = *(uint8_t *)(this + 2036);  // v6[0] 写入 *(uint8_t *)(this + 2036)
  sub_423290(dword_8F7B08, (int)v6, 1);  // 调 sub_423290
  if ( *(int *)(this + 2036) > 0 )  // 若 *(int *)(this + 2036) > 0
  {
    pThis_164 = this + 356;
    do
    {
      if ( *(uint32_t *)(pThis_164 + 60) != 0 )  // 若 *(uint32_t *)(pThis_164 + 60) != 0
      {
        v6[0] = *(uint8_t *)pThis_164;  // v6[0] 写入 *(uint8_t *)pThis_164
        sub_423290(dword_8F7B08, (int)v6, 1);  // 调 sub_423290
        v5 = *(uint16_t *)(pThis_164 + 10);  // v5 = pThis_164+10
        sub_423290(dword_8F7B08, (int)&v5, 2);  // 调 sub_423290
        v5 = *(uint32_t *)(pThis_164 - 16);
        sub_423290(dword_8F7B08, (int)&v5, 4);  // 调 sub_423290
      }
      ++v2;  // 自增v2
      pThis_164 += 84;
    }
    while ( v2 < *(uint32_t *)(this + 2036) );  // 当 v2 < *(uint32_t *)(this + 2036) 循环
  }
  sub_423380(dword_8F7B08);  // 发包提交：Commit()
  sub_55F160(*(uint32_t *)(*(uint32_t *)(this + 8) + 44));  // 礼赠参数（55CE00/4015C0）
  sub_55D300(*(uint32_t *)(this + 8));  // 商城确认状态（422E70/44E8D0）
  sub_55CB40(*(uint32_t *)(this + 8));  // 调 sub_55CB40
  *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 0;  // this+12 物品类型号
  memset((void *)(this + 340), 0, 0x690u);  // 清零 1680 字节块
  return 0;
}



// ------------------------------------------------------------
// 0x645DB0 sub_645DB0 —— 商城条目状态（44E850/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_645DB0(uint32_t *this)  // 函数: 商城条目状态（44E850/44E8D0）
{
  int v1; // eax
  int fld_e510; // eax
  int pThis_15; // edx
  int v4; // esi
  int v5; // edi
  uint32_t *pThis_68; // edi
  LONG v7; // edx
  LONG v8; // edx
  char *pHostObj; // [esp+Ch] [ebp-4h]

  pHostObj = (char *)*(this + 1);
  v1 = *((uint32_t *)pHostObj + 626);
  if ( v1 == 1 || v1 == 2 )  // 若 v1 == 1 || v1 == 2
    goto LABEL_20;  // 跳转 LABEL_20
  fld_e510 = *(this + 510);  // fld_e510 = this+510
  if ( fld_e510 == 0 )  // 若 fld_e510 == 0
  {
    fld_e510 = 0;
    pThis_68 = this + 104;  // this+104 插值终点 Z
    while ( fld_e510 < 20 )  // 当 fld_e510 < 20 循环
    {
      if ( *pThis_68 != 0 )  // 若 *pThis_68 != 0
      {
        v7 = dword_795DB0[2 * fld_e510];
        if ( pt.x >= v7 && pt.x <= v7 + 28 )  // 若 pt.x >= v7 && pt.x <= v7 + 28
        {
          v8 = dword_795DB4[2 * fld_e510];
          if ( pt.y >= v8 && pt.y <= v8 + 28 )  // 若 pt.y >= v8 && pt.y <= v8 + 28
          {
            v5 = dword_795DB4[2 * fld_e510];
            pThis_15 = *(this + 21 * fld_e510 + 104);
            v4 = dword_795DB0[2 * fld_e510];
            goto LABEL_19;  // 跳转 LABEL_19
          }
        }
      }
      ++fld_e510;  // 自增fld_e510
      pThis_68 += 21;  // pThis_68=this+104 插值终点 Z
    }
    goto LABEL_20;  // 跳转 LABEL_20
  }
  pThis_15 = *(this + 104);  // pThis_15 = this+104
  if ( pThis_15 == 0 || pt.x < 191 || pt.x > 219 || pt.y < 118 || pt.y > 146 )  // 若 pThis_15 == 0 || pt.x < 191 || pt.x > 219 || pt.y < 118 || pt...
    goto LABEL_20;  // 跳转 LABEL_20
  v4 = 191;
  v5 = 118;
LABEL_19:
  if ( pThis_15 == 0 )  // 若 pThis_15 == 0
  {
LABEL_20:
    LOBYTE(fld_e510) = dword_9B88D0;
    if ( dword_9B88D0 != 0 && dword_795378 == 5 )  // 若 dword_9B88D0 != 0 && dword_795378 == 5
      LOBYTE(fld_e510) = sub_44E850(pHostObj, 26);  // 按池号批量回收活动对象
    return fld_e510;
  }
  if ( dword_9B88D0 != pThis_15 || dword_795378 != 5 )  // 若 dword_9B88D0 != pThis_15 || dword_795378 != 5
  {
    fld_e510 = sub_44E8D0(pHostObj, (void *)0x1A, pThis_15, 5);  // 结果 = 对象池借出（按池号取可用对象）
    if ( fld_e510 != 0 )  // 若 fld_e510 != 0
      LOBYTE(fld_e510) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)fld_e510 + 48))(fld_e510, v4, v5, 28, 28);  // 虚槽+48 CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0）
  }
  return fld_e510;
}



// ------------------------------------------------------------
// 0x645EE0 sub_645EE0 —— 商城数据 4（23 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_645EE0(int *this)  // 商城数据 4
{
  int *result; // eax
  int i; // ecx
  int v3; // esi

  *(uint8_t *)(*(this + 519) + 16) = 0;
  *(uint8_t *)(*(this + 520) + 16) = 0;  // this+520 能力槽时长/基础值
  *(uint8_t *)(*(this + 521) + 16) = 0;
  result = this + 522;
  for ( i = 60; i != 0; --i )  // 循环：i = 60; i != 0; --i
  {
    v3 = *result++;  // 取 *result 后自增
    *(uint8_t *)(v3 + 16) = 0;  // v3+16 = 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x645F20 sub_645F20 —— 商城数据 5（55ECC0 + 645EE0）
// ------------------------------------------------------------
void /*thiscall*/ sub_645F20(int *this, int nArg2)  // 函数: 商城数据 5（55ECC0 + 645EE0）
{
  int fld_e517; // eax
  int16_t v5; // di
  int fld_e5172; // eax
  const void *v7; // eax
  int fld_e5173; // edx
  const void *v9; // esi
  int v10; // ecx
  int *i; // eax
  int *pThis_15; // edx
  char v13; // [esp+10h] [ebp+8h]

  if ( nArg2 > 0 && nArg2 <= 3 )  // 若 nArg2 > 0 && nArg2 <= 3
  {
    fld_e517 = *(this + 517);  // fld_e517 = this+517
    v5 = *(uint16_t *)(fld_e517 + 26);  // v5 = fld_e517+26
    *(uint16_t *)(fld_e517 + 26) = 1;  // fld_e517+26 = 1
    fld_e5172 = *(this + 517);  // fld_e5172 = this+517
    v13 = *(uint8_t *)(fld_e5172 + 16);  // v13 = fld_e5172+16
    v7 = (const void *)sub_55ECC0(*(uint32_t *)(fld_e5172 + 12), *(int16_t *)(fld_e5172 + 26), nArg2);  // 结果 = 礼赠条目（55CE70/55CED0）
    fld_e5173 = *(this + 517);  // fld_e5173 = this+517
    v9 = v7;
    if ( v7 != nullptr )  // 若 v7 非空
    {
      v10 = 0;
      for ( i = this + 85; (int *)fld_e5173 != i; i += 21 )  // 循环：i = this + 85; (int *)fld_e5173 != i; i += 21
      {
        if ( ++v10 >= 20 )  // 若 ++v10 >= 20
          return;
      }
      pThis_15 = this + 21 * v10;
      qmemcpy(pThis_15 + 85, v9, 0x54u);  // 调 qmemcpy 内联块拷贝
      *((uint8_t *)pThis_15 + 420) = 0;
      *((uint8_t *)pThis_15 + 356) = v13;
      sub_645EE0(this);  // 商城数据 4
    }
    else
    {
      *(uint16_t *)(fld_e5173 + 26) = v5;  // fld_e5173+26 = v5
    }
  }
}



// ------------------------------------------------------------
// 0x645FD0 sub_645FD0 —— 商城条目刷新（422E70，155 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645FD0(void *this, int pArg2, int pArg3, unsigned int uArg4, uint32_t *pArg5)  // 函数: 商城条目刷新（422E70，155 行）
{
  int v5; // edi
  int v6; // esi
  int v7; // eax
  const char *v8; // eax
  char *v9; // eax
  unsigned int nLen; // eax
  char *v11; // edi
  char v12; // cl
  char *v13; // edi
  uint32_t *v14; // esi
  char nLen4; // cl
  int v16; // eax
  char *v17; // eax
  unsigned int nLen2; // eax
  char *v19; // edi
  char v20; // cl
  char *v21; // edi
  uint32_t *v22; // esi
  char nLen22; // cl
  char *v24; // eax
  unsigned int nLen3; // eax
  char *v26; // edi
  char v27; // cl
  int v29; // [esp-4h] [ebp-21Ch]
  int v30; // [esp-4h] [ebp-21Ch]
  int v31; // [esp+Ch] [ebp-20Ch]
  void *pThis; // [esp+10h] [ebp-208h] BYREF
  char Buffer[256]; // [esp+14h] [ebp-204h] BYREF
  uint32_t pBuf[65]; // [esp+114h] [ebp-104h] BYREF
  int v35; // [esp+22Ch] [ebp+14h]

  pBuf[64] = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  pThis = this;
  memset(Buffer, 0, sizeof(Buffer));  // 调 memset 按字节填充
  memset(pBuf, 0, 256);  // 清零 256 字节块
  v5 = pArg5[9];
  v6 = pArg5[8];
  v7 = pArg5[10];
  v31 = v5;
  v35 = v7;
  if ( uArg4 != 0 )  // 若 uArg4 != 0
  {
    if ( uArg4 == 1 )  // 若 uArg4 == 1
    {
      v8 = (const char *)&unk_73E2A0;
    }
    else if ( uArg4 == 2 )  // 否则若 uArg4 == 2
    {
      v8 = (const char *)&unk_73E298;
    }
    else
    {
      v8 = (const char *)&unk_73E2A4;
      if ( uArg4 != 3 )  // 若 uArg4 != 3
        v8 = szPassword;
    }
    sprintf(Buffer, "%5s :", v8);  // 字符串 “%5s :”
    v7 = v35;
  }
  if ( v6 > 0 )  // 若 v6 > 0
  {
    if ( uArg4 >= 2 )  // 若 uArg4 >= 2
    {
      if ( uArg4 == 2 )  // 若 uArg4 == 2
      {
        v6 *= 2;
      }
      else if ( uArg4 == 3 )  // 否则若 uArg4 == 3
      {
        v6 *= 4;
      }
    }
    v9 = sub_422E70(908);  // 调 sub_422E70
    sprintf((char *const)pBuf, v9, v6);  // 调 sprintf 格式化
    nLen = strlen((const char *)pBuf) + 1;  // 调 strlen（求串长）
    v11 = (char *)&pThis + 3;
    do
      v12 = *++v11;
    while ( v12 != 0 );  // 当 v12 != 0 循环
    qmemcpy(v11, pBuf, 4 * (nLen >> 2));  // 调 qmemcpy 内联块拷贝
    v14 = &pBuf[nLen >> 2];
    v13 = &v11[4 * (nLen >> 2)];
    nLen4 = nLen;
    v7 = v35;
    qmemcpy(v13, v14, nLen4 & 3);  // 调 qmemcpy 内联块拷贝
    v5 = v31;
  }
  if ( v5 > 0 )  // 若 v5 > 0
  {
    if ( uArg4 < 2 )  // 若 uArg4 < 2
      goto LABEL_23;  // 跳转 LABEL_23
    if ( uArg4 == 2 )  // 若 uArg4 == 2
    {
      v16 = 2 * v5;
      goto LABEL_24;  // 跳转 LABEL_24
    }
    v16 = 4 * v5;
    if ( uArg4 != 3 )  // 若 uArg4 != 3
LABEL_23:
      v16 = v5;
LABEL_24:
    v29 = v16;
    v17 = sub_422E70(909);  // 调 sub_422E70
    sprintf((char *const)pBuf, v17, v29);  // 调 sprintf 格式化
    nLen2 = strlen((const char *)pBuf) + 1;  // 调 strlen（求串长）
    v19 = (char *)&pThis + 3;
    do
      v20 = *++v19;
    while ( v20 != 0 );  // 当 v20 != 0 循环
    qmemcpy(v19, pBuf, 4 * (nLen2 >> 2));  // 调 qmemcpy 内联块拷贝
    v22 = &pBuf[nLen2 >> 2];
    v21 = &v19[4 * (nLen2 >> 2)];
    nLen22 = nLen2;
    v7 = v35;
    qmemcpy(v21, v22, nLen22 & 3);  // 调 qmemcpy 内联块拷贝
  }
  if ( v7 > 0 )  // 若 v7 > 0
  {
    if ( uArg4 >= 2 )  // 若 uArg4 >= 2
    {
      if ( uArg4 == 2 )  // 若 uArg4 == 2
      {
        v7 *= 2;
      }
      else if ( uArg4 == 3 )  // 否则若 uArg4 == 3
      {
        v7 *= 4;
      }
    }
    v30 = v7;
    v24 = sub_422E70(910);  // 调 sub_422E70
    sprintf((char *const)pBuf, v24, v30);  // 调 sprintf 格式化
    nLen3 = strlen((const char *)pBuf) + 1;  // 调 strlen（求串长）
    v26 = (char *)&pThis + 3;
    do
      v27 = *++v26;
    while ( v27 != 0 );  // 当 v27 != 0 循环
    qmemcpy(v26, pBuf, nLen3);  // 调 qmemcpy 内联块拷贝
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)pThis + 132);  // 调用虚函数槽 +72
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
    pArg2 + 4,
    pArg3 + 3,
    -15920331,
    Buffer);
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
}


// ------------------------------------------------------------
// 0x646240 sub_646240 —— 商城条目刷新 2（55ECC0 + 6453D0/6453A0 + 422E70，115 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_646240(void *this, int pArg2, int pArg3, int nArg4, uint32_t *pArg5, char pszArg6, int nArg7)  // 函数: 商城条目刷新 2（55ECC0 + 6453D0/6453A0 + 422E70，115 行）
{
  int v8; // edi
  int v9; // ecx
  int v10; // esi
  const char *v11; // eax
  char *v12; // eax
  unsigned int nLen; // eax
  char *v14; // edi
  char v15; // cl
  char *v16; // eax
  unsigned int nLen2; // eax
  char *v18; // edi
  char v19; // cl
  char *v20; // eax
  unsigned int nLen3; // eax
  char *v22; // edi
  char v23; // cl
  char *v24; // eax
  char *v25; // eax
  int v27; // [esp-4h] [ebp-21Ch]
  int v28; // [esp-4h] [ebp-21Ch]
  int v29; // [esp-4h] [ebp-21Ch]
  const CHAR *v30; // [esp-4h] [ebp-21Ch]
  int v31; // [esp+Ch] [ebp-20Ch]
  char psz[255]; // [esp+14h] [ebp-204h] BYREF
  char v34; // [esp+113h] [ebp-105h] BYREF
  char Buffer[256]; // [esp+114h] [ebp-104h] BYREF
  int dword_796E502; // [esp+214h] [ebp-4h]
  int v37; // [esp+22Ch] [ebp+14h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  memset(Buffer, 0, sizeof(Buffer));  // 调 memset 按字节填充
  memset(psz, 0, sizeof(psz));  // 调 memset 按字节填充
  v34 = 0;
  v8 = pArg5[9];
  v9 = pArg5[10];
  v10 = pArg5[8];
  v37 = v8;
  v31 = v9;
  if ( nArg4 != 0 )  // 若 nArg4 != 0
  {
    if ( nArg4 > 0 && nArg4 <= 3 )  // 若 nArg4 > 0 && nArg4 <= 3
    {
      if ( sub_55ECC0(pArg5[3], 1, nArg4) != 0 )  // 礼赠条目（55CE70/55CED0）
      {
        v11 = sub_6453D0(nArg4);  // 结果 = 商城数据 2
        sprintf(Buffer, "%5s : ", v11);  // 字符串 “%5s : ”
        if ( v10 > 0 )  // 若 v10 > 0
        {
          v27 = sub_6453A0(v10, nArg4);  // 结果 = 商城数据
          v12 = sub_422E70(912);  // 调 sub_422E70
          sprintf(psz, v12, v27);  // 调 sprintf 格式化
          nLen = strlen(psz) + 1;  // 调 strlen（求串长）
          v14 = &v34;
          do
            v15 = *++v14;
          while ( v15 != 0 );  // 当 v15 != 0 循环
          qmemcpy(v14, psz, nLen);  // 调 qmemcpy 内联块拷贝
          v8 = v37;
        }
        if ( v8 > 0 )  // 若 v8 > 0
        {
          v28 = sub_6453A0(v8, nArg4);  // 结果 = 商城数据
          v16 = sub_422E70(913);  // 调 sub_422E70
          sprintf(psz, v16, v28);  // 调 sprintf 格式化
          nLen2 = strlen(psz) + 1;  // 调 strlen（求串长）
          v18 = &v34;
          do
            v19 = *++v18;
          while ( v19 != 0 );  // 当 v19 != 0 循环
          qmemcpy(v18, psz, nLen2);  // 调 qmemcpy 内联块拷贝
        }
        if ( v31 > 0 )  // 若 v31 > 0
        {
          v29 = sub_6453A0(v31, nArg4);  // 结果 = 商城数据
          v20 = sub_422E70(914);  // 调 sub_422E70
          sprintf(psz, v20, v29);  // 调 sprintf 格式化
          nLen3 = strlen(psz) + 1;  // 调 strlen（求串长）
          v22 = &v34;
          do
            v23 = *++v22;
          while ( v23 != 0 );  // 当 v23 != 0 循环
          qmemcpy(v22, psz, nLen3);  // 调 qmemcpy 内联块拷贝
        }
      }
      else
      {
        v30 = sub_6453D0(nArg4);  // 结果 = 商城数据 2
        v24 = sub_422E70(915);  // 调 sub_422E70
        sprintf(Buffer, v24, v30);  // 调 sprintf 格式化
        nArg7 = -16776961;
      }
    }
  }
  else if ( pszArg6 == 0 )  // 否则若 pszArg6 == 0
  {
    v25 = sub_422E70(911);  // 调 sub_422E70
    sprintf(Buffer, v25);  // 调 sprintf 格式化
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)this + 132);  // 调用虚函数槽 +72
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
    pArg2 + 4,
    pArg3 + 3,
    nArg7,
    Buffer);
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
}



// ------------------------------------------------------------
// 0x6464C0 sub_6464C0 —— 商城条目刷新 3（55CCB0 + 422E70/4EB900）
// ------------------------------------------------------------
int /*thiscall*/ sub_6464C0(void *this, int pArg2, int pArg3, int nArg4, int nArg5, int nArg6)  // 函数: 商城条目刷新 3（55CCB0 + 422E70/4EB900）
{
  int result; // eax
  int v8; // esi
  char *v9; // eax
  int v10; // edi

  result = sub_55CCB0(nArg5);  // 结果 = 两区块商城函数共同调用
  if ( result != 0 )  // 若 result != 0
  {
    if ( nArg4 == -1 )  // 若 nArg4 == -1
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)this + 132);  // 调用虚函数槽 +72
      v8 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
      v9 = sub_422E70(916);  // 调 sub_422E70
      (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v8 + 80))(dword_79C0B0, pArg2 + 4, pArg3 + 3, -1, v9);  // 调用虚函数槽 +80
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
    }
    else
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)result + 176))(result);  // 调用虚函数槽 +176
      result = sub_4EB900(nArg4);  // 结果 = 属性条目文本格式化（按条目 id 分支，输出静态缓冲 byte_9B0990）
      v10 = result;
      if ( result != 0 )  // 若 result != 0
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)this + 132);  // 调用虚函数槽 +72
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
          dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
          pArg2 + 4,
          pArg3 + 3,
          -1,
          v10);
        return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x646590 sub_646590 —— 商城条目刷新 4（55CCB0）
// ------------------------------------------------------------
bool /*thiscall*/ sub_646590(char *this)  // 函数: 商城条目刷新 4（55CCB0）
{
  char *pThis_16C; // esi
  int i; // ebx
  int v3; // ecx
  int v4; // esi
  int v5; // eax
  int v7; // [esp+Ch] [ebp-4h]

  v7 = 0;
  pThis_16C = this + 364;  // this+364 动画件名缓冲 SSO 内联首址
  for ( i = 20; i != 0; --i )  // 循环：i = 20; i != 0; --i
  {
    if ( sub_55CCB0(*((uint32_t *)pThis_16C + 13)) != 0 && *pThis_16C == 22 )  // 两区块商城函数共同调用
      ++v7;  // 自增v7
    pThis_16C += 84;  // pThis_16C=this+364 动画件名缓冲 SSO 内联首址
  }
  if ( v7 != 8 )  // 若 v7 != 8
    return true;
  v3 = *((uint32_t *)dword_8F8534 + 2);  // dword_8F8534（技能槽装载对象）
  v4 = 0;
  v5 = 0;
  if ( v3 <= 0 )  // 若 v3 <= 0
    return false;
  do
  {
    if ( *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v5) == 0 )  // 若 *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v5) == 0
      ++v4;  // 自增v4
    ++v5;  // 自增v5
  }
  while ( v5 < v3 );  // 当 v5 < v3 循环
  return v4 >= 16;
}



// ------------------------------------------------------------
// 0x646610 sub_646610 —— 商城条目刷新 5（55CCB0 + 422E70/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_646610(char **this, uint8_t uArg2)  // 函数: 商城条目刷新 5（55CCB0 + 422E70/44E8D0）
{
  char **pThis_5B; // esi
  int i; // ebx
  char *v5; // eax
  int v7; // [esp+Ch] [ebp-8h]
  int v8; // [esp+10h] [ebp-4h]

  v8 = 0;
  v7 = 0;
  pThis_5B = this + 91;  // this+91 pAnimNameStr
  for ( i = 20; i != 0; --i )  // 循环：i = 20; i != 0; --i
  {
    if ( sub_55CCB0(pThis_5B[13]) != 0 )  // 两区块商城函数共同调用
    {
      if ( *(uint8_t *)pThis_5B == 22 )  // 若 *(uint8_t *)pThis_5B == 22
        ++v8;  // 自增v8
      else
        ++v7;  // 自增v7
    }
    pThis_5B += 21;  // pThis_5B=this+91 pAnimNameStr
  }
  if ( v8 == 8 )  // 若 v8 == 8
  {
    if ( uArg2 == 1 )  // 若 uArg2 == 1
    {
      v5 = sub_422E70(3012);  // 调 sub_422E70
      sub_44E8D0(*(this + 1), (void *)0x1B, (int)v5, 0);  // 对象池借出（按池号取可用对象）
    }
    return 1;
  }
  if ( v8 <= 0 || v7 < 0 )  // 若 v8 <= 0 || v7 < 0
    return 1;
  sub_44E8D0(*(this + 1), (void *)0x45, (int)this, uArg2);  // 对象池借出（按池号取可用对象）
  return 0;
}



// ------------------------------------------------------------
// 0x6466D0 sub_6466D0 —— 双倍活动面板 A：加载 interface/cashshop/cashshopdoubleevent.img（667620/4F33A0/4F2C10 + 418DD0/69A110 + 55CCB0 系，252 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6466D0(int this)  // 函数: 双倍活动面板 A：加载 interface/cashshop/cashshopdoubleevent.img（667620/4F33A0/4F2C10 + 418DD0/69A110 + 55CCB0 系，252 行）
{
  int fld_1A0; // ecx
  int fld_174; // edx
  int pThis_154; // ebx
  unsigned int fld_16E; // eax
  int fld_178; // edx
  int fld_17C; // edx
  int v8; // edi
  int fld_160; // eax
  int pObj2; // eax
  int v11; // edi
  int pThis_188; // ecx
  const CHAR *v13; // eax
  const char *v14; // eax
  int pObj3; // eax
  int pObj4; // eax
  const char *v17; // eax
  const char *v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // esi
  int v24; // eax
  int result; // eax
  int fld_168; // [esp-4h] [ebp-130h]
  const CHAR *v27; // [esp-4h] [ebp-130h]
  int fld_1682; // [esp+Ch] [ebp-120h]
  int fld_164; // [esp+10h] [ebp-11Ch]
  unsigned int fld_16E2; // [esp+14h] [ebp-118h]
  int pObj; // [esp+18h] [ebp-114h]
  int fld_1782; // [esp+1Ch] [ebp-110h]
  int Value; // [esp+20h] [ebp-10Ch]
  int fld_1742; // [esp+24h] [ebp-108h]
  char Buffer[256]; // [esp+28h] [ebp-104h] BYREF
  int dword_796E502; // [esp+128h] [ebp-4h]

  fld_1A0 = *(uint32_t *)(this + 416);  // fld_1A0 = this+416
  fld_174 = *(uint32_t *)(this + 372);  // fld_174 = this+372
  pThis_154 = this + 340;  // this+340 职业槽表起点
  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  fld_16E = *(int16_t *)(this + 366);  // fld_16E = this+366
  pObj = fld_1A0;
  fld_16E2 = fld_16E;
  if ( *(uint16_t *)(this + 366) != 0 && fld_16E != 1 )  // 若 *(uint16_t *)(this + 366) != 0 && fld_16E != 1
  {
    if ( fld_16E == 2 )  // 若 fld_16E == 2
    {
      fld_174 *= 2;  // fld_174=this+372 绑定参考值 A
    }
    else if ( fld_16E == 3 )  // 否则若 fld_16E == 3
    {
      fld_174 *= 4;  // fld_174=this+372 绑定参考值 A
    }
  }
  fld_1742 = fld_174;  // fld_174=this+372 绑定参考值 A
  fld_178 = *(uint32_t *)(this + 376);  // fld_178 = this+376
  if ( fld_16E >= 2 )  // 若 fld_16E >= 2
  {
    if ( fld_16E == 2 )  // 若 fld_16E == 2
    {
      fld_178 *= 2;  // fld_178=this+376 绑定参考值 B
    }
    else if ( fld_16E == 3 )  // 否则若 fld_16E == 3
    {
      fld_178 *= 4;  // fld_178=this+376 绑定参考值 B
    }
  }
  fld_1782 = fld_178;  // fld_178=this+376 绑定参考值 B
  fld_17C = *(uint32_t *)(this + 380);  // fld_17C = this+380
  if ( fld_16E >= 2 )  // 若 fld_16E >= 2
  {
    if ( fld_16E == 2 )  // 若 fld_16E == 2
    {
      Value = 2 * fld_17C;
      goto LABEL_18;  // 跳转 LABEL_18
    }
    if ( fld_16E == 3 )  // 若 fld_16E == 3
      fld_17C *= 4;
  }
  Value = fld_17C;
LABEL_18:
  v8 = sub_667620(fld_1A0);  // 结果 = 取 +8 字段（getter）
  fld_168 = *(uint32_t *)(this + 360);  // fld_168 = this+360
  fld_1682 = fld_168;
  fld_164 = *(char *)(this + 356);  // fld_164 = this+356
  fld_160 = sub_4F33A0(*(uint32_t *)(this + 352));  // 调 sub_4F33A0
  sub_4F2C10(192, 118, fld_160, fld_168);  // 调 sub_4F2C10
  if ( v8 > 1 )  // 若 v8 > 1
  {
    pObj2 = sub_418DD0(10);  // 调 sub_418DD0
    if ( pObj2 != 0 )  // 若 pObj2 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj2,
        190,
        155,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_69A110(207, 157, v8, -1);  // 调 sub_69A110
  }
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 108))(pObj);  // 调用虚函数槽 +108
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 236);  // 调用虚函数槽 +72
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 231, 119, -15920333, v11);  // 调用虚函数槽 +80
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 230, 119, -15920333, v11);  // 调用虚函数槽 +80
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 132);  // 调用虚函数槽 +72
  if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 1 )  // 若 *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 1
  {
    if ( fld_1682 <= 1 )  // 若 fld_1682 <= 1
      v13 = szPassword;
    else
      v13 = (const CHAR *)sub_422E70(885);  // 调 存 CStringManager::getStr 取本地化串
    v27 = v13;
    v14 = (const char *)sub_422E70(884);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v14, fld_1682, v27);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      230,
      136,
      -15920333,
      Buffer);
  }
  else if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 2 )  // 否则若 *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 2
  {
    if ( *(uint32_t *)(this + 412) < 0x10u )  // 若 *(uint32_t *)(this + 412) < 0x10u
      pThis_188 = this + 392;
    else
      pThis_188 = *(uint32_t *)(this + 392);  // pThis_188 = this+392
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      230,
      136,
      -15920333,
      pThis_188);
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  if ( sub_55CCB0(pObj) != 0 )  // 两区块商城函数共同调用
  {
    pObj3 = sub_418DD0(34);  // 调 sub_418DD0
    if ( pObj3 != 0 )  // 若 pObj3 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj3,
        226,
        133,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_6464C0(226, 133, fld_164, pObj, 0);  // 商城条目刷新 3（55CCB0 + 422E70/4EB900）
    pObj4 = sub_418DD0(34);  // 调 sub_418DD0
    if ( pObj4 != 0 )  // 若 pObj4 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj4 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        pObj4,
        226,
        153,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_646240(226, 153, fld_16E2, this + 340, 0, -1);  // 商城条目刷新 2
  }
  else
  {
    sub_645FD0(226, 153, fld_16E2, this + 340);  // 商城条目刷新
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 184);  // 调用虚函数槽 +72
  if ( fld_1782 > 0 )  // 若 fld_1782 > 0
  {
    v17 = (const char *)sub_422E70(886);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v17, fld_1782);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      309 - *(uint32_t *)(this + 212),  // this+212 子链状态槽
      181,
      -15920333,
      Buffer);
  }
  if ( fld_1742 > 0 )  // 若 fld_1742 > 0
  {
    v18 = (const char *)sub_422E70(887);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v18, fld_1742);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      448 - *(uint32_t *)(this + 212),  // this+212 子链状态槽
      181,
      -15920333,
      Buffer);
  }
  if ( Value > 0 )  // 若 Value > 0
  {
    sub_69A110(416, 207, Value, -1);  // 调 sub_69A110
    v19 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
    v20 = sub_422E70(888);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v19 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      440 - *(uint32_t *)(this + 212),  // this+212 子链状态槽
      210,
      -15920333,
      v20);
    v21 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
    v22 = sub_422E70(889);  // 调 sub_422E70
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v21 + 80))(
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      439 - *(uint32_t *)(this + 212),  // this+212 子链状态槽
      210,
      -15920333,
      v22);
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 288);  // 调用虚函数槽 +72
  v23 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
  v24 = sub_422E70(890);  // 调 sub_422E70
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(v23 + 80))(dword_79C0B0, 250, 319, -1, v24);  // 调用虚函数槽 +80
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  if ( *(uint8_t *)(pThis_154 + 24) == 22 )  // 若 *(uint8_t *)(pThis_154 + 24) == 22
  {
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚槽+60 CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行：4BE520 + 48
      dword_8F84B8,
      "interface/cashshop/cashshopdoubleevent.img");  // 字符串 “interface/cashshop/cashshopdoubleevent.img”
    result = sub_418DD0(3);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
               result,
               200,
               131,
               dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
               1065353216,
               1065353216,
               0,
               -1,
               1333788672,
               1333788672);
  }
  return result;
}


// ------------------------------------------------------------
// 0x646C10 sub_646C10 —— 双倍面板刷新（646240）
// ------------------------------------------------------------
int /*thiscall*/ sub_646C10(int *this, int nArg2)  // 函数: 双倍面板刷新（646240）
{
  int v3; // esi
  int *pThis_207; // ebx
  int result; // eax
  uint32_t *fld_e517; // ecx

  v3 = 1;
  pThis_207 = this + 519;
  do
  {
    result = *pThis_207;
    if ( *pThis_207 == nArg2 && *(uint8_t *)(result + 16) != 0 )  // 若 *pThis_207 == nArg2 && *(uint8_t *)(result + 16) != 0
    {
      fld_e517 = (uint32_t *)*(this + 517);
      if ( fld_e517 != nullptr )  // 若 fld_e517 非空
        result = sub_646240(this, *(uint32_t *)(result + 20) + 2, *(uint32_t *)(result + 24) + 1, v3, fld_e517, 1, -1);  // 结果 = 商城条目刷新 2
    }
    ++v3;  // 自增v3
    ++pThis_207;  // 自增pThis_207
  }
  while ( v3 < 4 );  // 当 v3 < 4 循环
  return result;
}



// ------------------------------------------------------------
// 0x646C70 sub_646C70 —— 双倍活动面板 B：同 6466D0 结构（cashshopdoubleevent.img，186 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_646C70(int this, int Value)  // 函数: 双倍活动面板 B：同 6466D0 结构（cashshopdoubleevent.img，186 行）
{
  int result; // eax
  uint32_t *pThis_7E4; // ecx
  uint32_t *i; // edx
  int pThis_4; // ebx
  int pThis_34; // esi
  int v8; // eax
  int fld_18; // eax
  int v10; // ecx
  const CHAR *v11; // eax
  const char *v12; // eax
  int fld_14; // eax
  int fld_142; // eax
  uint32_t *v15; // eax
  int v16; // [esp-4h] [ebp-134h]
  const CHAR *v17; // [esp-4h] [ebp-134h]
  int v18; // [esp+Ch] [ebp-124h]
  int v19; // [esp+10h] [ebp-120h]
  int v20; // [esp+14h] [ebp-11Ch]
  int v21; // [esp+18h] [ebp-118h]
  int v22; // [esp+1Ch] [ebp-114h]
  int v23; // [esp+1Ch] [ebp-114h]
  int v24; // [esp+20h] [ebp-110h]
  int v25; // [esp+20h] [ebp-110h]
  uint32_t *v26; // [esp+24h] [ebp-10Ch]
  int v27; // [esp+28h] [ebp-108h]
  int v28; // [esp+28h] [ebp-108h]
  char Buffer[256]; // [esp+2Ch] [ebp-104h] BYREF
  int dword_796E502; // [esp+12Ch] [ebp-4h]
  int Valuea; // [esp+138h] [ebp+8h]
  int Valueb; // [esp+138h] [ebp+8h]
  int Valuec; // [esp+138h] [ebp+8h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  result = 0;
  pThis_7E4 = (uint32_t *)(this + 2020);
  for ( i = (uint32_t *)(this + 52); *i != Value || *pThis_7E4 == 0; i += 4 )  // 循环：i = (uint32_t *)(this + 52); *i != Value || *pThis_7E4 == 0;
  {
    ++result;  // 自增result
    ++pThis_7E4;  // 自增pThis_7E4
    if ( result >= 4 )  // 若 result >= 4
      return result;
  }
  pThis_4 = *(uint32_t *)(this + 4 * result + 2020);
  pThis_34 = *(uint32_t *)(16 * result + this + 52);  // this+52 光环状态字节
  v26 = *(uint32_t **)(pThis_4 + 76);
  v19 = *(int16_t *)(pThis_4 + 26);  // v19 = pThis_4+26
  Valuea = sub_667620(v26);  // 结果 = 取 +8 字段（getter）
  v22 = *(char *)(pThis_4 + 16);  // v22 = pThis_4+16
  v18 = *(uint32_t *)(pThis_34 + 20) + 11;
  v16 = *(uint32_t *)(pThis_4 + 20);  // v16 = pThis_4+20
  v20 = v16;
  v21 = *(uint32_t *)(pThis_34 + 24) + 14;
  v8 = sub_4F33A0(*(uint32_t *)(pThis_4 + 12));  // 调 sub_4F33A0
  sub_4F2C10(v18, v21, v8, v16);  // 调 sub_4F2C10
  if ( Valuea > 1 )  // 若 Valuea > 1
  {
    v27 = *(uint32_t *)(pThis_34 + 24);  // v27 = pThis_34+24
    v24 = *(uint32_t *)(pThis_34 + 20);  // v24 = pThis_34+20
    fld_18 = sub_418DD0(*(uint32_t **)(this + 24), 0xAu);  // 调 sub_418DD0
    if ( fld_18 != 0 )  // 若 fld_18 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_18 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        fld_18,
        v24 + 9,
        v27 + 48,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_69A110(*(uint32_t *)(pThis_34 + 20) + 26, *(uint32_t *)(pThis_34 + 24) + 50, Valuea, -1);  // 调 sub_69A110
  }
  v28 = (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 108))(v26);  // 结果 = 虚调用 vt+108
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 236);  // 调用虚函数槽 +72
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
    *(uint32_t *)(pThis_34 + 20) + 49,
    *(uint32_t *)(pThis_34 + 24) + 14,
    -15920333,
    v28);
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
    *(uint32_t *)(pThis_34 + 20) + 48,
    *(uint32_t *)(pThis_34 + 24) + 14,
    -15920333,
    v28);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 132);  // 调用虚函数槽 +72
  if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 1 )  // 若 *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 1
  {
    if ( v20 <= 1 )  // 若 v20 <= 1
      v11 = szPassword;
    else
      v11 = (const CHAR *)sub_422E70(898);  // 调 存 CStringManager::getStr 取本地化串
    v17 = v11;
    v12 = (const char *)sub_422E70(897);  // 调 存 CStringManager::getStr 取本地化串
    sprintf(Buffer, v12, v20, v17);  // 调 sprintf 格式化
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      *(uint32_t *)(pThis_34 + 20) + 48,
      *(uint32_t *)(pThis_34 + 24) + 31,
      -16051403,
      Buffer);
  }
  else if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 2 )  // 否则若 *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 2
  {
    if ( *(uint32_t *)(pThis_4 + 72) < 0x10u )  // 若 *(uint32_t *)(pThis_4 + 72) < 0x10u
      v10 = pThis_4 + 52;
    else
      v10 = *(uint32_t *)(pThis_4 + 52);  // v10 = pThis_4+52
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
      *(uint32_t *)(pThis_34 + 20) + 48,
      *(uint32_t *)(pThis_34 + 24) + 31,
      -16051403,
      v10);
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调用虚函数槽 +76
  if ( sub_55CCB0(v26) != 0 )  // 两区块商城函数共同调用
  {
    Valueb = *(uint32_t *)(pThis_34 + 24);  // Valueb = pThis_34+24
    v25 = *(uint32_t *)(pThis_34 + 20);  // v25 = pThis_34+20
    fld_14 = sub_418DD0(*(uint32_t **)(this + 20), 0x22u);  // 调 sub_418DD0
    if ( fld_14 != 0 )  // 若 fld_14 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_14 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        fld_14,
        v25 + 46,
        Valueb + 28,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_6464C0(*(uint32_t *)(pThis_34 + 20) + 46, *(uint32_t *)(pThis_34 + 24) + 28, v22, v26, 0);  // 商城条目刷新 3（55CCB0 + 422E70/4EB900）
    v23 = *(uint32_t *)(pThis_34 + 20);  // v23 = pThis_34+20
    Valuec = *(uint32_t *)(pThis_34 + 24);  // Valuec = pThis_34+24
    fld_142 = sub_418DD0(*(uint32_t **)(this + 20), 0x22u);  // 调 sub_418DD0
    if ( fld_142 != 0 )  // 若 fld_142 != 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_142 + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        fld_142,
        v23 + 46,
        Valuec + 48,
        dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    result = sub_646240(*(uint32_t *)(pThis_34 + 20) + 46, *(uint32_t *)(pThis_34 + 24) + 48, v19, pThis_4, 0, -1);  // 结果 = 商城条目刷新 2
  }
  else
  {
    result = sub_645FD0(*(uint32_t *)(pThis_34 + 20) + 46, *(uint32_t *)(pThis_34 + 24) + 48, v19, pThis_4);  // 结果 = 商城条目刷新
  }
  if ( *(uint8_t *)(pThis_4 + 24) == 22 )  // 若 *(uint8_t *)(pThis_4 + 24) == 22
  {
    v15 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚槽+60 CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行：4BE520 + 48
                      dword_8F84B8,
                      "interface/cashshop/cashshopdoubleevent.img");  // 字符串 “interface/cashshop/cashshopdoubleevent.img”
    result = sub_418DD0(v15, 3u);  // 调 sub_418DD0
    if ( result != 0 )  // 若 result != 0
      return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
               result,
               v18 + 8,
               v21 + 13,
               dword_79C0B0,  // dword_79C0B0（文本/图像绘制对象）
               1065353216,
               1065353216,
               0,
               -1,
               1333788672,
               1333788672);
  }
  return result;
}


// ------------------------------------------------------------
// 0x6470A0 sub_6470A0 —— 商城条目选择刷新（422E70/44E8D0 + 55CCB0/646590/646610，123 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6470A0(int this)  // 函数: 商城条目选择刷新（422E70/44E8D0 + 55CCB0/646590/646610，123 行）
{
  int v1; // eax
  char *v3; // eax
  int result; // eax
  int fld_808; // eax
  char *v6; // eax
  int fld_80C; // eax
  char *v8; // eax
  int fld_810; // eax
  char *v10; // eax
  int v11; // ebx
  int pThis_164; // edi
  int v13; // ebx
  int pThis_16E; // edi
  char *v15; // [esp-10h] [ebp-218h]
  char *v16; // [esp-10h] [ebp-218h]
  char *v17; // [esp-10h] [ebp-218h]
  int v18; // [esp-4h] [ebp-20Ch]
  int v19; // [esp-4h] [ebp-20Ch]
  int v20; // [esp-4h] [ebp-20Ch]
  char Buffer[512]; // [esp+4h] [ebp-204h] BYREF
  int dword_796E502; // [esp+204h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v1 = *(uint32_t *)(dword_8F7C08 + 648);  // v1 = dword_8F7C08+648
  if ( v1 != 0 && *(uint8_t *)(v1 + 284) != 0 )  // 若 v1 != 0 && *(uint8_t *)(v1 + 284) != 0
  {
    v3 = sub_422E70(1340);  // 调 sub_422E70
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);  // 对象池借出（按池号取可用对象）
  }
  else
  {
    fld_808 = *(uint32_t *)(this + 2056);  // fld_808 = this+2056
    if ( fld_808 >= 0 )  // 若 fld_808 >= 0
    {
      fld_80C = *(uint32_t *)(this + 2060);  // fld_80C = this+2060
      if ( fld_80C >= 0 )  // 若 fld_80C >= 0
      {
        fld_810 = *(uint32_t *)(this + 2064);  // fld_810 = this+2064
        if ( fld_810 >= 0 )  // 若 fld_810 >= 0
        {
          v11 = 0;
          pThis_164 = this + 356;
          do
          {
            if ( sub_55CCB0(*(uint32_t *)(pThis_164 + 60)) != 0 && *(uint8_t *)pThis_164 == 0xFF )  // 两区块商城函数共同调用
            {
              v16 = sub_422E70(906);  // 调 sub_422E70
              return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v16, 0);  // 对象池借出（按池号取可用对象）
            }
            ++v11;  // 自增v11
            pThis_164 += 84;
          }
          while ( v11 < 20 );  // 当 v11 < 20 循环
          v13 = 0;
          pThis_16E = this + 366;
          do
          {
            if ( sub_55CCB0(*(uint32_t *)(pThis_16E + 50)) != 0 && *(uint16_t *)pThis_16E == 0 )  // 两区块商城函数共同调用
            {
              v17 = sub_422E70(907);  // 调 sub_422E70
              return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v17, 0);  // 对象池借出（按池号取可用对象）
            }
            ++v13;  // 自增v13
            pThis_16E += 84;
          }
          while ( v13 < 20 );  // 当 v13 < 20 循环
          if ( *(uint8_t *)(*(uint32_t *)(this + 8) + 10128) == 0 )  // 若 *(uint8_t *)(*(uint32_t *)(this + 8) + 10128) == 0
            goto LABEL_24;  // 跳转 LABEL_24
          if ( (uint8_t)sub_646590(this) == 0 )  // 商城条目刷新 4（55CCB0）
          {
            v15 = sub_422E70(3010);  // 调 sub_422E70
            return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v15, 0);  // 对象池借出（按池号取可用对象）
          }
          result = sub_646610(0);  // 结果 = 商城条目刷新 5（55CCB0 + 422E70/44E8D0）
          if ( (uint8_t)result == 1 )  // 若 (uint8_t)result == 1
          {
LABEL_24:
            result = *(uint32_t *)(this + 2056);  // result = this+2056
            if ( result >= 0 )  // 若 result >= 0
            {
              result = *(uint32_t *)(this + 2060);  // result = this+2060
              if ( result >= 0 )  // 若 result >= 0
              {
                result = *(uint32_t *)(this + 2064);  // result = this+2064
                if ( result >= 0 )  // 若 result >= 0
                  return sub_44E8D0(*(char **)(this + 4), (void *)0x2F, this, 0);  // 对象池借出（按池号取可用对象）
              }
            }
          }
        }
        else
        {
          v20 = -fld_810;
          v10 = sub_422E70(905);  // 调 sub_422E70
          sprintf(Buffer, v10, v20);  // 调 sprintf 格式化
          return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)Buffer, 0);  // 对象池借出（按池号取可用对象）
        }
      }
      else
      {
        v19 = -fld_80C;  // fld_80C=this+2060 nParamCnt
        v8 = sub_422E70(904);  // 调 sub_422E70
        sprintf(Buffer, v8, v19);  // 调 sprintf 格式化
        return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)Buffer, 0);  // 对象池借出（按池号取可用对象）
      }
    }
    else
    {
      v18 = -fld_808;
      v6 = sub_422E70(903);  // 调 sub_422E70
      sprintf(Buffer, v6, v18);  // 调 sprintf 格式化
      return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)Buffer, 0);  // 对象池借出（按池号取可用对象）
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6472C0 sub_6472C0 —— 商城点击音（CLICK_BUTTON1 事件 432EA0，137 行判定）
// ------------------------------------------------------------
void */*thiscall*/ sub_6472C0(int *this, int nArg2)  // 商城点击音
{
  int fld_e511; // eax
  int v3; // eax
  int fld_e5112; // eax
  int fld_e5113; // esi
  int fld_e15; // eax
  int fld_e13; // eax
  int fld_e19; // eax
  int fld_e17; // eax
  int fld_e23; // eax
  int fld_e21; // eax
  int fld_e27; // eax
  int fld_e25; // eax
  int *pThis_20A; // eax
  int i; // ecx
  int v16; // esi

  if ( nArg2 == -1 )  // 若 nArg2 == -1
  {
    fld_e511 = *(this + 511);  // fld_e511 = this+511
    if ( fld_e511 <= 0 )  // 若 fld_e511 <= 0
      return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 字符串 “CLICK_BUTTON1”
    v3 = fld_e511 - 1;
  }
  else
  {
    if ( nArg2 != 1 )  // 若 nArg2 != 1
      goto LABEL_8;  // 跳转 LABEL_8
    fld_e5112 = *(this + 511);  // fld_e5112 = this+511
    if ( fld_e5112 >= *(this + 512) )  // 若 fld_e5112 >= *(this + 512)
      return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 字符串 “CLICK_BUTTON1”
    v3 = fld_e5112 + 1;
  }
  *(this + 511) = v3;  // this+2044 = v3
LABEL_8:
  fld_e5113 = 4 * *(this + 511);
  if ( fld_e5113 >= *(this + 509) )  // 若 fld_e5113 >= *(this + 509)
  {
    fld_e13 = *(this + 13);  // fld_e13 = this+13
    *(this + 505) = 0;  // this+2020 = 0
  }
  else
  {
    *(this + 505) = (int)(this + 84 * *(this + 511) + 85);  // this+2020 = (int)(this + 84 * *(this + 511) + 85)
    *(uint8_t *)(*(this + 13) + 16) = 1;
    fld_e15 = *(this + 15);  // fld_e15 = this+15
    if ( *(uint32_t *)(*(this + 505) + 4) == 0 )  // 若 *(uint32_t *)(*(this + 505) + 4) == 0
    {
      *(uint8_t *)(fld_e15 + 16) = 1;  // fld_e15+16 = 1
      *(uint8_t *)(*(this + 16) + 16) = 1;  // this+16 频道型选中索引
      goto LABEL_14;  // 跳转 LABEL_14
    }
    *(uint8_t *)(fld_e15 + 16) = 0;  // fld_e15+16 = 0
    fld_e13 = *(this + 16);  // fld_e13 = this+16
  }
  *(uint8_t *)(fld_e13 + 16) = 0;  // fld_e13+16 = 0
LABEL_14:
  if ( fld_e5113 + 1 >= *(this + 509) )  // 若 fld_e5113 + 1 >= *(this + 509)
  {
    fld_e17 = *(this + 17);  // fld_e17 = this+17
    *(this + 506) = 0;  // this+2024 = 0
  }
  else
  {
    *(this + 506) = (int)(this + 21 * fld_e5113 + 106);  // this+2024 = (int)(this + 21 * fld_e5113 + 106)
    *(uint8_t *)(*(this + 17) + 16) = 1;  // this+17 激活/可命中标志
    fld_e19 = *(this + 19);  // fld_e19 = this+19
    if ( *(uint32_t *)(*(this + 506) + 4) == 0 )  // 若 *(uint32_t *)(*(this + 506) + 4) == 0
    {
      *(uint8_t *)(fld_e19 + 16) = 1;  // fld_e19+16 = 1
      *(uint8_t *)(*(this + 20) + 16) = 1;  // this+20 频道页号
      goto LABEL_20;  // 跳转 LABEL_20
    }
    *(uint8_t *)(fld_e19 + 16) = 0;  // fld_e19+16 = 0
    fld_e17 = *(this + 20);  // fld_e17 = this+20
  }
  *(uint8_t *)(fld_e17 + 16) = 0;  // fld_e17+16 = 0
LABEL_20:
  if ( fld_e5113 + 2 >= *(this + 509) )  // 若 fld_e5113 + 2 >= *(this + 509)
  {
    fld_e21 = *(this + 21);  // fld_e21 = this+21
    *(this + 507) = 0;  // this+2028 = 0
  }
  else
  {
    *(this + 507) = (int)(this + 21 * fld_e5113 + 127);  // this+2028 = (int)(this + 21 * fld_e5113 + 127)
    *(uint8_t *)(*(this + 21) + 16) = 1;  // this+21 霸体状态字节
    fld_e23 = *(this + 23);  // fld_e23 = this+23
    if ( *(uint32_t *)(*(this + 507) + 4) == 0 )  // 若 *(uint32_t *)(*(this + 507) + 4) == 0
    {
      *(uint8_t *)(fld_e23 + 16) = 1;  // fld_e23+16 = 1
      *(uint8_t *)(*(this + 24) + 16) = 1;  // this+24 页数上限
      goto LABEL_26;  // 跳转 LABEL_26
    }
    *(uint8_t *)(fld_e23 + 16) = 0;  // fld_e23+16 = 0
    fld_e21 = *(this + 24);  // fld_e21 = this+24
  }
  *(uint8_t *)(fld_e21 + 16) = 0;  // fld_e21+16 = 0
LABEL_26:
  if ( fld_e5113 + 3 >= *(this + 509) )  // 若 fld_e5113 + 3 >= *(this + 509)
  {
    fld_e25 = *(this + 25);  // fld_e25 = this+25
    *(this + 508) = 0;  // this+2032 = 0
  }
  else
  {
    *(this + 508) = (int)(this + 21 * fld_e5113 + 148);  // this+2032 = (int)(this + 21 * fld_e5113 + 148)
    *(uint8_t *)(*(this + 25) + 16) = 1;
    fld_e27 = *(this + 27);  // fld_e27 = this+27
    if ( *(uint32_t *)(*(this + 508) + 4) == 0 )  // 若 *(uint32_t *)(*(this + 508) + 4) == 0
    {
      *(uint8_t *)(fld_e27 + 16) = 1;  // fld_e27+16 = 1
      *(uint8_t *)(*(this + 28) + 16) = 1;  // this+28 逐帧驱动对象
      goto LABEL_32;  // 跳转 LABEL_32
    }
    *(uint8_t *)(fld_e27 + 16) = 0;  // fld_e27+16 = 0
    fld_e25 = *(this + 28);  // fld_e25 = this+28
  }
  *(uint8_t *)(fld_e25 + 16) = 0;  // fld_e25+16 = 0
LABEL_32:
  *(uint8_t *)(*(this + 519) + 16) = 0;
  *(uint8_t *)(*(this + 520) + 16) = 0;  // this+520 能力槽时长/基础值
  *(uint8_t *)(*(this + 521) + 16) = 0;
  pThis_20A = this + 522;
  for ( i = 60; i != 0; --i )  // 循环：i = 60; i != 0; --i
  {
    v16 = *pThis_20A++;  // 取 *pThis_20A 后自增
    *(uint8_t *)(v16 + 16) = 0;  // v16+16 = 0
  }
  return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);  // 字符串 “CLICK_BUTTON1”
}


// ------------------------------------------------------------
// 0x6474A0 sub_6474A0 —— 商城页部件（645EE0 + 69A5F0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6474A0(int *this, int pArg2, int nArg3)  // 商城页部件（645EE0 + 69A5F0）
{
  BOOL fld_e519; // esi
  int pArg22; // eax
  int v6; // edi
  uint32_t **pThis_207; // esi
  uint32_t *result; // eax
  bool fld_e5192; // [esp+1Bh] [ebp+Fh]

  fld_e519 = nArg3;
  if ( nArg3 == -1 )  // 若 nArg3 == -1
    fld_e519 = *(uint8_t *)(*(this + 519) + 16) == 0;
  if ( fld_e519 )  // 若 fld_e519
  {
    sub_645EE0(this);  // 商城数据 4
    pArg22 = pArg2;
    *(this + 517) = *(this + pArg2 + 505);  // this+2068 = *(this + pArg2 + 505)
  }
  else
  {
    pArg22 = pArg2;
    *(this + 517) = 0;  // this+2068 = 0
  }
  fld_e5192 = fld_e519;
  v6 = 18;
  pThis_207 = (uint32_t **)(this + 519);
  while ( 1 )  // 当 1 循环
  {
    *((uint8_t *)*pThis_207 + 16) = fld_e5192;
    result = *(this + 510) != 0
           ? sub_69A5F0(*pThis_207, 226, v6 + 153)  // 商城页部件（645EE0 + 69A5F0）
           : sub_69A5F0(*pThis_207, dword_73E228[2 * pArg22], v6 + dword_73E22C[2 * pArg22]);  // 调 设位、sub_69A840 登记
    v6 += 18;
    ++pThis_207;  // 自增pThis_207
    if ( v6 >= 72 )  // 若 v6 >= 72
      break;
    pArg22 = pArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x647550 sub_647550 —— 商城页部件 2（55CCB0/645EE0 + 69A5F0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_647550(uint32_t *this, int pArg2, int nArg3)  // 商城页部件 2（55CCB0/645EE0 + 69A5F0）
{
  int pObj; // eax
  int v5; // edi
  int fld_e522; // eax
  int v7; // esi
  int v8; // ecx
  unsigned int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  uint32_t **pThis_20A3; // ebx
  int v15; // esi
  int v16; // eax
  uint32_t *result; // eax
  uint32_t **pThis_20A; // esi
  unsigned int v19; // edi
  int v20; // ebx
  int v21; // eax
  bool v22; // zf
  int v23; // [esp+Ch] [ebp-1Ch]
  int v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+14h] [ebp-14h]
  int v26; // [esp+18h] [ebp-10h]
  uint32_t *v27; // [esp+18h] [ebp-10h]
  uint32_t *pThis_20A2; // [esp+1Ch] [ebp-Ch]
  int i; // [esp+20h] [ebp-8h]
  int v31; // [esp+24h] [ebp-4h]
  int v32; // [esp+24h] [ebp-4h]
  int v33; // [esp+30h] [ebp+8h]

  pObj = sub_55CCB0(*(uint32_t *)(*(this + pArg2 + 505) + 76));  // 结果 = 两区块商城函数共同调用
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj) + 916;  // 虚槽+176 目标是否在前方/后方（按 walkDir 朝向 +152）
  v25 = v5;
  if ( nArg3 == -1 )  // 若 nArg3 == -1
    nArg3 = *(uint8_t *)(*(this + 522) + 16) == 0;
  if ( nArg3 != 0 )  // 若 nArg3 != 0
  {
    sub_645EE0(this);  // 商城数据 4
    *(this + 517) = *(this + pArg2 + 505);  // this+2068 = *(this + pArg2 + 505)
  }
  else
  {
    *(this + 517) = 0;  // this+2068 = 0
  }
  fld_e522 = *(this + 522);  // fld_e522 = this+522
  v23 = *(uint32_t *)(fld_e522 + 28);  // v23 = fld_e522+28
  v7 = *(uint32_t *)(v5 + 4);  // v7 = v5+4
  v26 = *(uint32_t *)(fld_e522 + 32);  // v26 = fld_e522+32
  v8 = 480 / v26 - 1;
  v24 = v8;
  if ( v7 != 0 )  // 若 v7 != 0
    v9 = (*(uint32_t *)(v5 + 8) - v7) / 80;
  else
    v9 = 0;
  v10 = v9 / v8;
  if ( v10 != 0 )  // 若 v10 != 0
  {
    result = (uint32_t *)(v10 + 1);
    v33 = 100;
    if ( (int)result > 0 )  // 若 (int)result > 0
    {
      pThis_20A = (uint32_t **)(this + 522);
      v19 = 0;
      v32 = 0;
      pThis_20A2 = this + 522;
      v27 = result;
      do
      {
        if ( v8 > 0 )  // 若 v8 > 0
        {
          v20 = 24;
          for ( i = v8; i != 0; --i )  // 循环：i = v8; i != 0; --i
          {
            *((uint8_t *)*pThis_20A + 16) = nArg3 != 0
                                 && (v21 = *(uint32_t *)(v25 + 4)) != 0
                                 && v19 < (*(uint32_t *)(v25 + 8) - v21) / 80;
            sub_69A5F0(*pThis_20A++, v33, v20);  // 调 sub_69A5F0
            ++v19;  // 自增v19
            v20 += 18;
          }
          v8 = v24;
        }
        v33 += v23;  // v33 累加 v23
        pThis_20A = (uint32_t **)&pThis_20A2[v8];
        v19 = v8 + v32;
        result = (uint32_t *)((char *)v27 - 1);
        v22 = v27 == (uint32_t *)1;
        v32 += v8;  // v32 累加 v8
        pThis_20A2 = pThis_20A;
        v27 = (uint32_t *)((char *)v27 - 1);
      }
      while ( !v22 );  // 当 !v22 循环
    }
  }
  else
  {
    if ( v7 != 0 )  // 若 v7 != 0
      v10 = (*(uint32_t *)(v5 + 8) - v7) / 80;
    v11 = v26 * v10;
    if ( *(this + 510) != 0 )  // 若 *(this + 510) != 0
      v12 = 151;
    else
      v12 = dword_73E22C[2 * pArg2];
    v13 = v12 + v11;
    if ( 480 - v13 < 0 )  // 若 480 - v13 < 0
      v12 += 470 - v13;
    pThis_20A3 = (uint32_t **)(this + 522);
    v15 = 0;
    v31 = v12;
    do
    {
      *((uint8_t *)*pThis_20A3 + 16) = nArg3 != 0
                           && (v16 = *(uint32_t *)(v5 + 4)) != 0
                           && v15 < (unsigned int)((*(uint32_t *)(v5 + 8) - v16) / 80);
      if ( *(this + 510) != 0 )  // 若 *(this + 510) != 0
        result = sub_69A5F0(*pThis_20A3, 226, v31);  // 调 sub_69A5F0
      else
        result = sub_69A5F0(*pThis_20A3, dword_73E228[2 * pArg2], v31);  // 调 sub_69A5F0
      ++v15;  // 自增v15
      ++pThis_20A3;  // 自增pThis_20A3
      v31 += 18;
    }
    while ( v15 < 60 );  // 当 v15 < 60 循环
  }
  return result;
}


// ------------------------------------------------------------
// 0x6477B0 sub_6477B0 —— 商城页部件 3（69A5F0 + 6472C0/646610/646590 + 422E70/44E8D0，172 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6477B0(int this, uint32_t *uArg2, char pszArg3)  // 函数: 商城页部件 3（69A5F0 + 6472C0/646610/646590 + 422E70/44E8D0，172 行）
{
  uint32_t *v4; // eax
  uint8_t *fld_7F4; // edx
  int fld_7F42; // ecx
  uint8_t *fld_7F43; // edx
  int fld_7F44; // ecx
  uint8_t *fld_7F45; // edx
  int fld_7F46; // ecx
  uint8_t *fld_7F47; // edx
  int fld_7F48; // ecx
  uint8_t *fld_7F49; // edx
  int fld_7F410; // ecx
  int v15; // esi
  uint32_t **pThis_20; // edi
  int fld_7F8; // eax
  int fld_7F82; // eax
  int fld_7F411; // eax
  int pThis_158; // ecx
  int v21; // eax
  int *pThis_828; // eax
  int j; // ecx
  int v24; // edx
  int result; // eax
  char *v26; // eax
  int i; // [esp+18h] [ebp+Ch]

  *(uint8_t *)(this + 2052) = 0;  // this+2052 = 0
  *(uint32_t *)(this + 2036) = 0;  // this+2036 = 0
  if ( pszArg3 != 0 )  // 若 pszArg3 != 0
  {
    v4 = uArg2 + 40;
    for ( i = 4; i != 0; --i )  // 循环：i = 4; i != 0; --i
    {
      if ( *(v4 - 21) != 0 )  // 若 *(v4 - 21) != 0
      {
        fld_7F4 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);  // this+340 职业槽表起点
        qmemcpy(fld_7F4, v4 - 40, 0x54u);  // 调 qmemcpy 内联块拷贝
        fld_7F4[80] = 0;
        fld_7F42 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(fld_7F42 + 344) == 0 )  // 若 *(uint32_t *)(fld_7F42 + 344) == 0
          *(uint16_t *)(fld_7F42 + 366) = 0;  // fld_7F42+366 = 0
        ++*(uint32_t *)(this + 2036);
      }
      if ( *v4 != 0 )  // 若 *v4 != 0
      {
        fld_7F43 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);  // this+340 职业槽表起点
        qmemcpy(fld_7F43, v4 - 19, 0x54u);  // 调 qmemcpy 内联块拷贝
        fld_7F43[80] = 0;
        fld_7F44 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(fld_7F44 + 344) == 0 )  // 若 *(uint32_t *)(fld_7F44 + 344) == 0
          *(uint16_t *)(fld_7F44 + 366) = 0;  // fld_7F44+366 = 0
        ++*(uint32_t *)(this + 2036);
      }
      if ( v4[21] != 0 )  // 若 v4[21] != 0
      {
        fld_7F45 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);  // this+340 职业槽表起点
        qmemcpy(fld_7F45, v4 + 2, 0x54u);  // 调 qmemcpy 内联块拷贝
        fld_7F45[80] = 0;
        fld_7F46 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(fld_7F46 + 344) == 0 )  // 若 *(uint32_t *)(fld_7F46 + 344) == 0
          *(uint16_t *)(fld_7F46 + 366) = 0;  // fld_7F46+366 = 0
        ++*(uint32_t *)(this + 2036);
      }
      if ( v4[42] != 0 )  // 若 v4[42] != 0
      {
        fld_7F47 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);  // this+340 职业槽表起点
        qmemcpy(fld_7F47, v4 + 23, 0x54u);  // 调 qmemcpy 内联块拷贝
        fld_7F47[80] = 0;
        fld_7F48 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(fld_7F48 + 344) == 0 )  // 若 *(uint32_t *)(fld_7F48 + 344) == 0
          *(uint16_t *)(fld_7F48 + 366) = 0;  // fld_7F48+366 = 0
        ++*(uint32_t *)(this + 2036);
      }
      if ( v4[63] != 0 )  // 若 v4[63] != 0
      {
        fld_7F49 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);  // this+340 职业槽表起点
        qmemcpy(fld_7F49, v4 + 44, 0x54u);  // 调 qmemcpy 内联块拷贝
        fld_7F49[80] = 0;
        fld_7F410 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(fld_7F410 + 344) == 0 )  // 若 *(uint32_t *)(fld_7F410 + 344) == 0
          *(uint16_t *)(fld_7F410 + 366) = 0;  // fld_7F410+366 = 0
        ++*(uint32_t *)(this + 2036);
      }
      v4 += 105;
    }
    *(uint32_t *)(this + 2040) = 0;  // this+2040 = 0
  }
  else
  {
    qmemcpy((void *)(this + 340), uArg2, 0x54u);  // 调 qmemcpy 内联块拷贝
    *(uint8_t *)(this + 420) = 0;  // this+420 = 0
    *(uint32_t *)(this + 2020) = this + 340;  // this+2020 = this + 340
    fld_7F411 = 84 * *(uint32_t *)(this + 2036);
    pThis_158 = *(uint32_t *)(fld_7F411 + this + 344);  // this+344 预约重连延迟 ms
    v21 = this + fld_7F411;
    if ( pThis_158 == 0 )  // 若 pThis_158 == 0
      *(uint16_t *)(v21 + 366) = 0;  // v21+366 = 0
    ++*(uint32_t *)(this + 2036);
    *(uint32_t *)(this + 2040) = 1;  // this+2040 = 1
  }
  v15 = 0;
  pThis_20 = (uint32_t **)(this + 32);  // this+32 格子像素尺寸
  do
  {
    fld_7F8 = 2 * (*(uint32_t *)(this + 2040) + v15 + 2 * *(uint32_t *)(this + 2040));
    sub_69A5F0(*pThis_20, dword_73E248[fld_7F8], dword_73E24C[fld_7F8]);  // 调 sub_69A5F0
    ++v15;  // 自增v15
    ++pThis_20;  // 自增pThis_20
  }
  while ( v15 < 3 );  // 当 v15 < 3 循环
  *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 1;  // this+12 物品类型号
  *(uint32_t *)(this + 2048) = (*(uint32_t *)(this + 2036) - 1) / 4;  // this+2048 = (*(uint32_t *)(this + 2036) - 1) / 4
  fld_7F82 = *(uint32_t *)(this + 2040);  // fld_7F82 = this+2040
  *(uint32_t *)(this + 2044) = 0;  // this+2044 = 0
  if ( fld_7F82 != 0 )  // 若 fld_7F82 != 0
  {
    *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 0;  // this+44 剩余时间 ms
    *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 0;  // this+48 UDP 上报使能位
    *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 0;  // this+52 光环状态字节
    *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = 0;  // this+68 角色数（begin/end 差 >>2；>=8 …
    *(uint8_t *)(*(uint32_t *)(this + 84) + 16) = 0;  // this+84 插值起点 X
    *(uint8_t *)(*(uint32_t *)(this + 100) + 16) = 0;  // this+100 插值终点 Y
    if ( *(uint32_t *)(*(uint32_t *)(this + 2020) + 4) != 0 )  // 若 *(uint32_t *)(*(uint32_t *)(this + 2020) + 4) != 0
    {
      *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 0;  // this+124 第 2 组·+858/+1292 增量
      *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;  // this+128 第 2 组·+1208 增量子倍率
    }
    else
    {
      *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 1;  // this+124 第 2 组·+858/+1292 增量
      *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 1;  // this+128 第 2 组·+1208 增量子倍率
    }
  }
  else
  {
    *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 1;  // this+44 剩余时间 ms
    *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 1;  // this+48 UDP 上报使能位
    *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;  // this+128 第 2 组·+1208 增量子倍率
    *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 0;  // this+124 第 2 组·+858/+1292 增量
    sub_6472C0(0);  // 商城点击音
  }
  *(uint8_t *)(*(uint32_t *)(this + 2076) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 2080) + 16) = 0;  // this+2080 pHoldHost
  *(uint8_t *)(*(uint32_t *)(this + 2084) + 16) = 0;  // this+2084 pVtStack
  pThis_828 = (int *)(this + 2088);  // this+2088 nRideHost8352
  for ( j = 60; j != 0; --j )  // 循环：j = 60; j != 0; --j
  {
    v24 = *pThis_828++;  // 取 *pThis_828 后自增
    *(uint8_t *)(v24 + 16) = 0;  // v24+16 = 0
  }
  result = *(uint32_t *)(this + 8);  // result = this+8
  if ( *(uint8_t *)(result + 10128) != 0 )  // 若 *(uint8_t *)(result + 10128) != 0
  {
    sub_646610(1);  // 商城条目刷新 5（55CCB0 + 422E70/44E8D0）
    result = sub_646590(this);  // 结果 = 商城条目刷新 4（55CCB0）
    if ( (uint8_t)result == 0 )  // 若 (uint8_t)result == 0
    {
      v26 = sub_422E70(3010);  // 调 sub_422E70
      sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v26, 0);  // 对象池借出（按池号取可用对象）
      *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 0;  // this+12 物品类型号
      memset((void *)(this + 340), 0, 0x690u);  // 清零 1680 字节块
      return 0;
    }
  }
  return result;  // result=this+8 物品 id
}


// ------------------------------------------------------------
// 0x647B60 sub_647B60 —— 商城页部件 4（55CCB0 + 41A5E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_647B60(uint32_t *this, int nArg2, int nArg3)  // 函数: 商城页部件 4（55CCB0 + 41A5E0）
{
  int pObj2; // eax
  int pObj; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax

  pObj2 = sub_55CCB0(nArg2);  // 结果 = 两区块商城函数共同调用
  pObj = pObj2;
  if ( pObj2 != 0
    && (v5 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 176))(pObj2) + 920) + 80 * nArg3),  // 虚槽+176 目标是否在前方/后方（按 walkDir 朝向 +152）
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj),  // 虚槽+176 目标是否在前方/后方（按 walkDir 朝向 +152）
        v7 = sub_41A5E0(80 * nArg3 + *(uint32_t *)(v6 + 920) + 24),  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        v5 == 43) )
  {
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(*(this + 2) + 9952) + 1140))(
             *(uint32_t *)(*(this + 2) + 9952),
             v7);
  }
  else
  {
    return 1;
  }
}



// ------------------------------------------------------------
// 0x647BF0 sub_647BF0 —— 商城购买页绘制（509 行：426BD0/423B30 + 43C410/69A840 + 69C780/69C7B0 + 69A5F0/699E20/699E40/698F90）
// ------------------------------------------------------------
char /*thiscall*/ sub_647BF0(int this)  // 函数: 商城购买页绘制（509 行：426BD0/423B30 + 43C410/69A840 + 69C780/69C7B0 + 69A5F0/699E20/699E40/698F90）
{
  uint8_t *pMem; // eax
  uint8_t *v3; // eax
  int fld_18; // eax
  int *v5; // edi
  uint32_t *pMem3; // eax
  uint32_t *fld_142; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_14; // eax
  int pThis_202; // ecx
  bool v11; // zf
  uint32_t *pMem4; // edi
  uint32_t *pMem5; // eax
  uint32_t *pMem52; // edi
  uint32_t **pThis_64; // edi
  uint8_t *pMem6; // eax
  void *fld_1C2; // ecx
  uint32_t *fld_1C3; // eax
  uint8_t *pMem7; // eax
  void *fld_1C4; // ecx
  uint32_t *fld_1C5; // eax
  uint8_t *pMem8; // eax
  void *fld_1C6; // ecx
  uint32_t *fld_1C7; // eax
  uint8_t *pMem9; // eax
  void *fld_1C8; // ecx
  uint32_t *fld_1C9; // eax
  uint32_t *pMem10; // edi
  uint32_t *pMem11; // eax
  uint32_t *pMem112; // edi
  uint32_t *pMem12; // eax
  uint32_t *pMem122; // edi
  uint32_t *pMem1222; // eax
  char *pObj; // edi
  uint32_t *pMem13; // eax
  uint32_t *pMem132; // edi
  uint32_t *pMem1322; // eax
  char *pObj3; // edi
  uint32_t *pMem14; // edi
  int pObj2; // ecx
  char *v41; // eax
  int v42; // edx
  int v43; // edx
  int v45; // [esp-4h] [ebp-78h]
  int v46; // [esp+Ch] [ebp-68h]
  int v47; // [esp+10h] [ebp-64h]
  uint32_t v48[10]; // [esp+14h] [ebp-60h] BYREF
  uint32_t v49[2]; // [esp+3Ch] [ebp-38h]
  uint32_t v50[2]; // [esp+44h] [ebp-30h]
  void *v51[3]; // [esp+4Ch] [ebp-28h]
  void *Block; // [esp+58h] [ebp-1Ch]
  int fld_143; // [esp+5Ch] [ebp-18h]
  void *fld_1C; // [esp+60h] [ebp-14h]
  int pThis_20; // [esp+64h] [ebp-10h]
  int v56; // [esp+70h] [ebp-4h]

  pMem = operator new(0x68u);  // 堆分配 104 字节对象
  Block = pMem;
  v56 = 0;
  if ( pMem != nullptr )  // 若 pMem 非空
    v3 = sub_426BD0(pMem);  // 结果 = nengine::IControl 构造
  else
    v3 = nullptr;  // v3 = nullptr 空指针
  *(uint32_t *)(this + 12) = v3;  // this+12 = v3
  *((uint32_t *)v3 + 7) = 640;
  *((uint32_t *)v3 + 8) = 480;
  *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 0;  // this+12 物品类型号
  *(uint32_t *)(*(uint32_t *)(this + 12) + 68) = this;  // this+12 物品类型号
  *(uint32_t *)(this + 20) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 164);  // this+20 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  *(uint32_t *)(this + 24) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 156);  // this+24 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  *(uint32_t *)(this + 28) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 160);  // this+28 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 +..
  Block = operator new(0x2Cu);  // 堆分配 44 字节对象
  v56 = 1;
  if ( Block != nullptr )  // 若 Block 非空
    fld_18 = sub_423B30(dword_79C0B0, *(uint32_t *)(this + 24), 28, 2);  // 结果 = CNNumberSet 构造
  else
    fld_18 = 0;
  *(uint32_t *)(this + 16) = fld_18;  // this+16 = fld_18
  *(uint32_t *)(fld_18 + 36) = 0;  // fld_18+36 = 0
  *(uint8_t *)(*(uint32_t *)(this + 16) + 24) = 0;  // this+16 频道型选中索引
  *(uint8_t *)(this + 132) = 0;  // this+132 = 0
  *(uint8_t *)(this + 133) = 0;  // this+133 = 0
  *(uint8_t *)(this + 134) = 0;  // this+134 = 0
  *(uint8_t *)(this + 135) = 0;  // this+135 = 0
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint32_t *)(this + 156) = 0;  // this+156 = 0
  *(uint32_t *)(this + 164) = 0;  // this+164 = 0
  *(uint32_t *)(this + 168) = 0;  // this+168 = 0
  *(uint32_t *)(this + 172) = 0;  // this+172 = 0
  *(uint32_t *)(this + 176) = 0;  // this+176 = 0
  *(uint32_t *)(this + 180) = 0;  // this+180 = 0
  *(uint32_t *)(this + 160) = 1600;  // this+160 = 1600
  *(uint32_t *)(this + 148) = 6;  // this+148 = 6
  *(uint32_t *)(this + 152) = 12;  // this+152 = 12
  v56 = -1;
  *(uint32_t *)(this + 180) = dword_99FCCC;  // this+180 = dword_99FCCC
  *(uint32_t *)(this + 160) = 205;  // this+160 = 205
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  *(uint8_t *)(this + 184) = 0;  // this+184 = 0
  *(uint8_t *)(this + 185) = 0;  // this+185 = 0
  *(uint8_t *)(this + 186) = 0;  // this+186 = 0
  *(uint8_t *)(this + 187) = 0;  // this+187 = 0
  *(uint32_t *)(this + 196) = 0;  // this+196 = 0
  *(uint32_t *)(this + 200) = 6;  // this+200 = 6
  *(uint32_t *)(this + 204) = 12;  // this+204 = 12
  *(uint32_t *)(this + 208) = 0;  // this+208 = 0
  *(uint32_t *)(this + 212) = 1600;  // this+212 = 1600
  *(uint32_t *)(this + 216) = 0;  // this+216 = 0
  *(uint32_t *)(this + 220) = 0;  // this+220 = 0
  *(uint32_t *)(this + 224) = 0;  // this+224 = 0
  *(uint32_t *)(this + 228) = 0;  // this+228 = 0
  *(uint32_t *)(this + 232) = 0;  // this+232 = 0
  *(uint32_t *)(this + 232) = dword_99FCCC;  // this+232 = dword_99FCCC
  *(uint32_t *)(this + 212) = 165;  // this+212 = 165
  *(uint32_t *)(this + 196) = 2;  // this+196 = 2
  *(uint8_t *)(this + 236) = 0;  // this+236 = 0
  *(uint8_t *)(this + 237) = 0;  // this+237 = 0
  *(uint8_t *)(this + 238) = 0;  // this+238 = 0
  *(uint8_t *)(this + 239) = 0;  // this+239 = 0
  *(uint32_t *)(this + 248) = 0;  // this+248 = 0
  *(uint32_t *)(this + 252) = 6;  // this+252 = 6
  *(uint32_t *)(this + 256) = 12;  // this+256 = 12
  *(uint32_t *)(this + 260) = 0;  // this+260 = 0
  *(uint32_t *)(this + 264) = 1600;  // this+264 = 1600
  *(uint32_t *)(this + 268) = 0;  // this+268 = 0
  *(uint32_t *)(this + 272) = 0;  // this+272 = 0
  *(uint32_t *)(this + 276) = 0;  // this+276 = 0
  *(uint32_t *)(this + 280) = 0;  // this+280 = 0
  *(uint32_t *)(this + 284) = 0;  // this+284 = 0
  *(uint32_t *)(this + 284) = dword_99FCCC;  // this+284 = dword_99FCCC
  *(uint32_t *)(this + 248) = 0;  // this+248 = 0
  *(uint32_t *)(this + 264) = 205;  // this+264 = 205
  *(uint8_t *)(this + 288) = 0;  // this+288 = 0
  *(uint8_t *)(this + 289) = 0;  // this+289 = 0
  *(uint8_t *)(this + 290) = 0;  // this+290 = 0
  *(uint8_t *)(this + 291) = 0;  // this+291 = 0
  *(uint32_t *)(this + 300) = 0;  // this+300 = 0
  *(uint32_t *)(this + 304) = 6;  // this+304 = 6
  *(uint32_t *)(this + 308) = 12;  // this+308 = 12
  *(uint32_t *)(this + 312) = 0;  // this+312 = 0
  *(uint32_t *)(this + 316) = 1600;  // this+316 = 1600
  *(uint32_t *)(this + 320) = 0;  // this+320 = 0
  *(uint32_t *)(this + 324) = 0;  // this+324 = 0
  *(uint32_t *)(this + 328) = 0;  // this+328 = 0
  *(uint32_t *)(this + 332) = 0;  // this+332 = 0
  *(uint32_t *)(this + 336) = 0;  // this+336 = 0
  *(uint32_t *)(this + 336) = dword_99FCCC;  // this+336 = dword_99FCCC
  *(uint32_t *)(this + 316) = 205;  // this+316 = 205
  *(uint32_t *)(this + 300) = 0;  // this+300 = 0
  v48[1] = -1;
  v48[4] = 6;
  v48[5] = -1;
  *(uint32_t *)(this + 292) = -16777216;  // this+292 = -16777216
  *(uint8_t *)(this + 290) = 1;  // this+290 = 1
  v46 = 1;
  v47 = 2;
  v48[0] = 3;
  v48[2] = 4;
  v48[3] = 5;
  v48[6] = 7;
  v48[7] = 8;
  v48[8] = 9;
  v48[9] = 7;
  v5 = v48;
  pThis_20 = this + 32;  // this+32 格子像素尺寸
  fld_1C = (void *)3;
  do
  {
    if ( v5[1] == -1 )  // 若 v5[1] == -1
    {
      pMem2 = operator new(0x84u);  // 堆分配 132 字节对象
      Block = pMem2;
      v56 = 3;
      if ( pMem2 != nullptr )  // 若 pMem2 非空
        fld_14 = sub_43C410(pMem2, *(uint32_t *)(this + 20), *(v5 - 2), *(v5 - 1), *v5, -1, 0, 0);  // 结果 = nengine::CNButton 构造
      else
        fld_14 = nullptr;  // fld_14 = nullptr 空指针
      *(uint32_t *)pThis_20 = fld_14;  // pThis_20=this+32 格子像素尺寸
    }
    else
    {
      pMem3 = operator new(0x84u);  // 堆分配 132 字节对象
      Block = pMem3;
      v56 = 2;
      if ( pMem3 != nullptr )  // 若 pMem3 非空
      {
        fld_142 = sub_43C410(pMem3, *(uint32_t *)(this + 20), *(v5 - 2), *(v5 - 1), *v5, v5[1], 0, 0);  // 结果 = nengine::CNButton 构造
        *(uint32_t *)pThis_20 = fld_142;  // pThis_20=this+32 格子像素尺寸
      }
      else
      {
        *(uint32_t *)pThis_20 = 0;  // pThis_20=this+32 格子像素尺寸
      }
    }
    v45 = *(uint32_t *)pThis_20;  // pThis_20=this+32 格子像素尺寸
    v56 = -1;
    sub_69A840(v45);  // 调 sub_69A840
    sub_69A840(*(uint32_t *)pThis_20);  // 调 sub_69A840
    pThis_202 = pThis_20;  // pThis_20=this+32 格子像素尺寸
    *(uint32_t *)(*(uint32_t *)pThis_20 + 68) = this;  // pThis_20=this+32 格子像素尺寸
    v5 += 4;
    v11 = fld_1C == (void *)1;
    pThis_20 = pThis_202 + 4;  // pThis_20=this+32 格子像素尺寸
    fld_1C = (char *)fld_1C - 1;
  }
  while ( !v11 );  // 当 !v11 循环
  pMem4 = operator new(0x84u);  // 堆分配 132 字节对象
  Block = pMem4;
  v56 = 4;
  if ( pMem4 != nullptr )  // 若 pMem4 非空
  {
    fld_1C = *(void **)(this + 28);  // this+28 逐帧驱动对象
    sub_426BD0(pMem4);  // nengine::IControl 构造
    LOBYTE(v56) = 5;
    *pMem4 = &nengine::CNButton::`vftable';
    sub_69C780(v12);  // 调 sub_69C780
    sub_69C7B0(v54, 46, 47, 48, -1, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    v12 = nullptr;  // v12 = nullptr 空指针
  }
  v56 = -1;
  *(uint32_t *)(this + 44) = v12;  // this+44 = v12
  sub_69A840(v12);  // 调 sub_69A840
  *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 0;  // this+44 剩余时间 ms
  sub_69A5F0(*(uint32_t **)(this + 44), 137, 408);  // 调 sub_69A5F0
  v13 = operator new(0x84u);  // 堆分配 132 字节对象
  v14 = v13;
  Block = v13;
  v56 = 6;
  if ( v13 != nullptr )  // 若 v13 非空
  {
    v54 = *(void **)(this + 28);  // this+28 逐帧驱动对象
    sub_426BD0(v13);  // nengine::IControl 构造
    LOBYTE(v56) = 7;
    *v14 = &nengine::CNButton::`vftable';
    sub_69C780(pMem52);  // 调 sub_69C780
    sub_69C7B0(fld_1C, 49, 50, 51, -1, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    pMem52 = nullptr;  // pMem52 = nullptr 空指针
  }
  v56 = -1;
  *(uint32_t *)(this + 48) = pMem52;  // this+48 = pMem52
  sub_69A840(pMem52);  // 调 sub_69A840
  *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 0;  // this+48 UDP 上报使能位
  sub_69A5F0(*(uint32_t **)(this + 48), 195, 408);  // 调 sub_69A5F0
  pThis_20 = (int)&unk_73E290;  // pThis_20=this+32 格子像素尺寸
  pThis_64 = (uint32_t **)(this + 100);  // this+100 插值终点 Y
  do
  {
    pMem6 = operator new(0x84u);  // 堆分配 132 字节对象
    fld_1C = pMem6;  // fld_1C=this+28 逐帧驱动对象
    v56 = 8;
    if ( pMem6 != nullptr )  // 若 pMem6 非空
    {
      fld_143 = *(uint32_t *)(this + 20);  // fld_143 = this+20
      sub_426BD0(pMem6);  // nengine::IControl 构造
      fld_1C2 = fld_1C;  // fld_1C=this+28 逐帧驱动对象
      LOBYTE(v56) = 9;
      *(uint32_t *)fld_1C = &nengine::CNButton::`vftable';  // fld_1C=this+28 逐帧驱动对象
      sub_69C780(v17);  // 调 sub_69C780
      sub_69C7B0(v53, 36, 36, 36, -1, 0, 0);  // 调 sub_69C7B0
      v18 = v54;  // v54=this+28 逐帧驱动对象
    }
    else
    {
      v18 = nullptr;  // v18 = nullptr 空指针
    }
    *v15 = v18;  // *v15 写入 v18
    v56 = -1;
    sub_69A840(v18);  // 调 sub_69A840
    sub_69A5F0(*v15, *(uint32_t *)v55, *(uint32_t *)(v55 + 4));  // 调 sub_69A5F0
    *((uint8_t *)*v15 + 16) = 0;
    (*v15)[17] = this;
    v19 = operator new(0x84u);  // 堆分配 132 字节对象
    v54 = v19;  // v54=this+28 逐帧驱动对象
    v56 = 10;
    if ( v19 != nullptr )  // 若 v19 非空
    {
      v53 = *(uint32_t *)(this + 20);  // v53 = this+20
      sub_426BD0(v19);  // nengine::IControl 构造
      v20 = v54;  // v54=this+28 逐帧驱动对象
      LOBYTE(v56) = 11;
      *(uint32_t *)v54 = &nengine::CNButton::`vftable';  // v54=this+28 逐帧驱动对象
      sub_69C780(fld_1C4);  // 调 sub_69C780
      sub_69C7B0(fld_143, 37, 38, 39, -1, 0, 0);  // 调 sub_69C7B0
      fld_1C5 = fld_1C;  // fld_1C=this+28 逐帧驱动对象
    }
    else
    {
      fld_1C5 = nullptr;  // fld_1C5 = nullptr 空指针
    }
    v56 = -1;
    pThis_64[1] = fld_1C5;  // pThis_64=this+100 插值终点 Y
    sub_69A840(fld_1C5);  // 调 sub_69A840
    sub_69A5F0(pThis_64[1], *(uint32_t *)pThis_20 + 256, *(uint32_t *)(pThis_20 + 4) + 8);  // 调 sub_69A5F0
    *((uint8_t *)pThis_64[1] + 16) = 1;  // pThis_64=this+100 插值终点 Y
    pMem8 = operator new(0x84u);  // 堆分配 132 字节对象
    fld_1C = pMem8;  // fld_1C=this+28 逐帧驱动对象
    v56 = 12;
    if ( pMem8 != nullptr )  // 若 pMem8 非空
    {
      fld_143 = *(uint32_t *)(this + 20);  // fld_143 = this+20
      sub_426BD0(pMem8);  // nengine::IControl 构造
      fld_1C6 = fld_1C;  // fld_1C=this+28 逐帧驱动对象
      LOBYTE(v56) = 13;
      *(uint32_t *)fld_1C = &nengine::CNButton::`vftable';  // fld_1C=this+28 逐帧驱动对象
      sub_69C780(v23);  // 调 sub_69C780
      sub_69C7B0(v53, 43, 44, 45, -1, 0, 0);  // 调 sub_69C7B0
      v24 = v54;  // v54=this+28 逐帧驱动对象
    }
    else
    {
      v24 = nullptr;  // v24 = nullptr 空指针
    }
    v56 = -1;
    v15[3] = v24;
    sub_69A840(v24);  // 调 sub_69A840
    sub_69A5F0(v15[3], *(uint32_t *)v55 + 46, *(uint32_t *)(v55 + 4) + 28);  // 调 sub_69A5F0
    *((uint8_t *)v15[3] + 16) = 1;
    v25 = operator new(0x84u);  // 堆分配 132 字节对象
    v54 = v25;  // v54=this+28 逐帧驱动对象
    v56 = 14;
    if ( v25 != nullptr )  // 若 v25 非空
    {
      v53 = *(uint32_t *)(this + 20);  // v53 = this+20
      sub_426BD0(v25);  // nengine::IControl 构造
      v26 = v54;  // v54=this+28 逐帧驱动对象
      LOBYTE(v56) = 15;
      *(uint32_t *)v54 = &nengine::CNButton::`vftable';  // v54=this+28 逐帧驱动对象
      sub_69C780(fld_1C8);  // 调 sub_69C780
      sub_69C7B0(fld_143, 43, 44, 45, -1, 0, 0);  // 调 sub_69C7B0
      fld_1C9 = fld_1C;  // fld_1C=this+28 逐帧驱动对象
    }
    else
    {
      fld_1C9 = nullptr;  // fld_1C9 = nullptr 空指针
    }
    v56 = -1;
    pThis_64[2] = fld_1C9;  // pThis_64=this+100 插值终点 Y
    sub_69A840(fld_1C9);  // 调 sub_69A840
    sub_69A5F0(pThis_64[2], *(uint32_t *)pThis_20 + 46, *(uint32_t *)(pThis_20 + 4) + 48);  // 调 sub_69A5F0
    *((uint8_t *)pThis_64[2] + 16) = 1;  // pThis_64=this+100 插值终点 Y
    pThis_64 -= 4;  // pThis_64=this+100 插值终点 Y
    pThis_20 -= 8;  // pThis_20=this+32 格子像素尺寸
  }
  while ( pThis_20 >= (int)&unk_73E278 );  // 当 pThis_20 >= (int)&unk_73E278 循环
  pMem10 = operator new(0x84u);  // 堆分配 132 字节对象
  Block = pMem10;
  v56 = 16;
  if ( pMem10 != nullptr )  // 若 pMem10 非空
  {
    fld_143 = *(uint32_t *)(this + 20);  // fld_143 = this+20
    sub_426BD0(pMem10);  // nengine::IControl 构造
    LOBYTE(v56) = 17;
    *pMem10 = &nengine::CNButton::`vftable';
    sub_69C780(v28);  // 调 sub_69C780
    sub_69C7B0(v53, 43, 44, 45, -1, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    v28 = nullptr;  // v28 = nullptr 空指针
  }
  v56 = -1;
  *(uint32_t *)(this + 128) = v28;  // this+128 = v28
  sub_69A840(v28);  // 调 sub_69A840
  sub_69A5F0(*(uint32_t **)(this + 128), 226, 133);  // 调 sub_69A5F0
  *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 1;  // this+128 第 2 组·+1208 增量子倍率
  v29 = operator new(0x84u);  // 堆分配 132 字节对象
  v30 = v29;
  Block = v29;
  v56 = 18;
  if ( v29 != nullptr )  // 若 v29 非空
  {
    v53 = *(uint32_t *)(this + 20);  // v53 = this+20
    sub_426BD0(v29);  // nengine::IControl 构造
    LOBYTE(v56) = 19;
    *v30 = &nengine::CNButton::`vftable';
    sub_69C780(pMem112);  // 调 sub_69C780
    sub_69C7B0(fld_143, 43, 44, 45, -1, 0, 0);  // 调 sub_69C7B0
  }
  else
  {
    pMem112 = nullptr;  // pMem112 = nullptr 空指针
  }
  v56 = -1;
  *(uint32_t *)(this + 124) = pMem112;  // this+124 = pMem112
  sub_69A840(pMem112);  // 调 sub_69A840
  sub_69A5F0(*(uint32_t **)(this + 124), 226, 153);  // 调 sub_69A5F0
  *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 1;  // this+124 第 2 组·+858/+1292 增量
  fld_1C = (void *)(this + 2076);
  pThis_20 = 3;  // pThis_20=this+32 格子像素尺寸
  do
  {
    pMem12 = operator new(0x84u);  // 堆分配 132 字节对象
    pMem122 = pMem12;
    Block = pMem12;
    v56 = 20;
    if ( pMem12 != nullptr )  // 若 pMem12 非空
    {
      fld_143 = *(uint32_t *)(this + 20);  // fld_143 = this+20
      sub_426BD0(pMem12);  // nengine::IControl 构造
      LOBYTE(v56) = 21;
      *pMem122 = &nengine::CNButton::`vftable';
      sub_69C780(v32);  // 调 sub_69C780
      sub_69C7B0(v53, 40, 41, 41, -1, 0, 0);  // 调 sub_69C7B0
      v33 = v32;
    }
    else
    {
      v33 = nullptr;  // v33 = nullptr 空指针
    }
    v34 = (char *)v54;  // v54=this+28 逐帧驱动对象
    *(uint32_t *)v54 = v33;  // v54=this+28 逐帧驱动对象
    v56 = -1;
    sub_69A840(v33);  // 调 sub_69A840
    *(uint8_t *)(*(uint32_t *)v34 + 16) = 0;
    *(uint32_t *)(*(uint32_t *)v34 + 68) = this;
    v11 = v55 == 1;
    v54 = v34 + 4;  // v54=this+28 逐帧驱动对象
    --v55;  // 自减v55
  }
  while ( !v11 );  // 当 !v11 循环
  v54 = (void *)(this + 2088);  // this+2088 nRideHost8352
  v55 = 60;
  do
  {
    v35 = operator new(0x84u);  // 堆分配 132 字节对象
    v36 = v35;
    Block = v35;
    v56 = 22;
    if ( v35 != nullptr )  // 若 v35 非空
    {
      v53 = *(uint32_t *)(this + 20);  // v53 = this+20
      sub_426BD0(v35);  // nengine::IControl 构造
      LOBYTE(v56) = 23;
      *v36 = &nengine::CNButton::`vftable';
      sub_69C780(pMem132);  // 调 sub_69C780
      sub_69C7B0(fld_143, 40, 41, 41, -1, 0, 0);  // 调 sub_69C7B0
      pMem1322 = pMem132;
    }
    else
    {
      pMem1322 = nullptr;  // pMem1322 = nullptr 空指针
    }
    pObj3 = (char *)fld_1C;
    *(uint32_t *)fld_1C = pMem1322;
    v56 = -1;
    sub_69A840(pMem1322);  // 调 sub_69A840
    *(uint8_t *)(*(uint32_t *)pObj3 + 16) = 0;
    *(uint32_t *)(*(uint32_t *)pObj3 + 68) = this;
    v11 = pThis_20 == 1;  // pThis_20=this+32 格子像素尺寸
    fld_1C = pObj3 + 4;
    --pThis_20;  // 自减pThis_20
  }
  while ( !v11 );  // 当 !v11 循环
  v51[0] = (void *)10;  // v51[0] 写入 (void *)10
  v51[1] = (void *)22;  // v51[1] 写入 (void *)22
  v50[0] = 0;
  v50[1] = 0;
  v49[0] = 2;
  v49[1] = 2;
  pThis_20 = this + 116;  // this+116 观察者 vector 尾针
  fld_1C = nullptr;  // fld_1C = nullptr 空指针
  do
  {
    pMem14 = operator new(0x2Cu);  // 堆分配 44 字节对象
    v51[2] = pMem14;
    v56 = 24;
    if ( pMem14 != nullptr )  // 若 pMem14 非空
    {
      fld_143 = *(uint32_t *)(this + 20);  // fld_143 = this+20
      Block = (void *)dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
      *((uint8_t *)pMem14 + 4) = 0;
      LOBYTE(v56) = 25;
      *pMem14 = &nengine::CNNumberSet::`vftable';
      sub_699E20(pMem14);  // 调 sub_699E20
      sub_699E40(Block, fld_143, *(void **)((char *)v51 + (uint32_t)fld_1C), 10);  // 调 sub_699E40
    }
    else
    {
      pMem14 = nullptr;  // pMem14 = nullptr 空指针
    }
    pObj2 = pThis_20;  // pThis_20=this+116 观察者 vector 尾针
    v41 = (char *)fld_1C;
    v42 = *(uint32_t *)((char *)v50 + (uint32_t)fld_1C);
    *(uint32_t *)pThis_20 = pMem14;  // pThis_20=this+116 观察者 vector 尾针
    pMem14[10] = v42;
    *(uint32_t *)(*(uint32_t *)pObj2 + 36) = *(uint32_t *)((char *)v49 + (uint32_t)v41);
    v43 = *(uint32_t *)pObj2;  // v43 = pObj2
    v56 = -1;
    *(uint8_t *)(v43 + 24) = 0;  // v43+24 = 0
    fld_1C = v41 + 4;
    pThis_20 = pObj2 + 4;  // pThis_20=this+116 观察者 vector 尾针
  }
  while ( (int)(v41 + 4) < 8 );  // 当 (int)(v41 + 4) < 8 循环
  *(uint8_t *)(this + 2341) = 0;  // this+2341 = 0
  *(uint8_t *)(this + 2342) = 0;  // this+2342 = 0
  return sub_698F90(this + 2328, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}


// ------------------------------------------------------------
// 0x648630 sub_648630 —— 商城页装配（6464C0/647B60 + 422E70/4649B0）
// ------------------------------------------------------------
char /*thiscall*/ sub_648630(uint32_t *this, int nArg2)  // 函数: 商城页装配（6464C0/647B60 + 422E70/4649B0）
{
  uint32_t *pThis; // edi
  int v3; // ebx
  int v4; // eax
  int v5; // esi
  int v6; // ebx
  unsigned int v7; // edi
  char *v8; // eax
  int v9; // ebx
  unsigned int v10; // edi
  int v11; // esi
  char *v12; // eax
  int v15; // [esp+10h] [ebp-Ch]
  int v16; // [esp+14h] [ebp-8h]
  int *pThis_20A; // [esp+18h] [ebp-4h]

  pThis = this;
  v3 = 0;
  LOBYTE(v4) = (uint8_t)this + 40;  // this+40 物品状态附属标志
  v16 = 0;
  pThis_20A = this + 522;
  do
  {
    v5 = *pThis_20A;
    if ( *pThis_20A == nArg2 )  // 若 *pThis_20A == nArg2
    {
      LOBYTE(v4) = *(uint8_t *)(v5 + 16);
      if ( (uint8_t)v4 != 0 )  // 若 (uint8_t)v4 != 0
      {
        v4 = pThis[517];
        if ( v4 != 0 )  // 若 v4 != 0
        {
          sub_6464C0(pThis, *(uint32_t *)(v5 + 20) + 2, *(uint32_t *)(v5 + 24) + 1, v3, *(uint32_t *)(v4 + 76), 1);  // 商城条目刷新 3（55CCB0 + 422E70/4EB900）
          LOBYTE(v4) = *(uint8_t *)(v5 + 17);
          if ( (uint8_t)v4 != 0 && dword_79BE3C == *(uint32_t *)(v5 + 12) )  // 若 (uint8_t)v4 != 0 && dword_79BE3C == *(uint32_t *)(v5 + 12)
          {
            v4 = sub_647B60(pThis, *(uint32_t *)(pThis[517] + 76), v3);  // 结果 = 商城页部件 4（55CCB0 + 41A5E0）
            if ( v4 == 0 )  // 若 v4 == 0
            {
              v6 = *(uint32_t *)(v5 + 24);  // v6 = v5+24
              v7 = *(uint32_t *)(v5 + 28);  // v7 = v5+28
              v15 = *(uint32_t *)(v5 + 20);  // v15 = v5+20
              v8 = sub_422E70(895);  // 调 sub_422E70
              sub_4649B0(v15 + (v7 >> 1), v6, -16776961, -16777216, 2, (int)v8, 0, 0, 1600, 0);  // 带框文本上屏（静态一次性初始化）
              v9 = *(uint32_t *)(v5 + 24);  // v9 = v5+24
              v10 = *(uint32_t *)(v5 + 28);  // v10 = v5+28
              v11 = *(uint32_t *)(v5 + 20);  // v11 = v5+20
              v12 = sub_422E70(896);  // 调 sub_422E70
              LOBYTE(v4) = sub_4649B0(v11 + (v10 >> 1), v9, -16776961, -16777216, 2, (int)v12, 0, 0, 1600, 0);  // 带框文本上屏（静态一次性初始化）
              v3 = v16;
              pThis = this;
            }
          }
        }
      }
    }
    v16 = ++v3;
    ++pThis_20A;  // 自增pThis_20A
  }
  while ( v3 < 60 );  // 当 v3 < 60 循环
  return v4;
}



// ------------------------------------------------------------
// 0x648770 CNRDCashShopBuyWindow__vmt0 —— CNRDCashShopBuyWindow__vmt0 构造（6455D0/6466D0/645680/645930/645DB0/646C70/646C10/648630 + 422E70/4649B0 装配链）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCashShopBuyWindow__vmt0(int16_t *this, int Value)  // 函数: CNRDCashShopBuyWindow__vmt0 构造（6455D0/6466D0/645680/645930/645DB0/646C70/646C10/648630 + 422E70/4649B0 装配链）
{
  int pThis_A; // eax
  unsigned int v4; // esi
  int v5; // edi
  int v6; // ebx
  char *v7; // eax

  if ( Value == *((uint32_t *)this + 3) )  // 若 Value == *((uint32_t *)this + 3)
  {
    sub_6455D0(this);  // 商城面板
    if ( *((uint32_t *)this + 510) != 0 )  // 若 *((uint32_t *)this + 510) != 0
      sub_6466D0((int)this);  // 双倍活动面板 A：加载 interface/cashshop/cashshopdoublee
    else
      sub_645680(this);  // 商城列表构建
    sub_645930(this);  // 商城列表构建 2
    LOBYTE(pThis_A) = sub_645DB0(this);  // 商城条目状态（44E850/44E8D0）
  }
  else
  {
    if ( *((uint32_t *)this + 510) == 0 )  // 若 *((uint32_t *)this + 510) == 0
      sub_646C70(this, Value);  // 双倍活动面板 B：同 6466D0 结构
    sub_646C10((int *)this, Value);  // 双倍面板刷新（646240）
    sub_648630(this, Value);  // 商城页装配（6464C0/647B60 + 422E70/4649B0）
    pThis_A = *((uint32_t *)this + 10);  // 读 pThis_A = this+40（关闭按钮）
    if ( Value == pThis_A && *(uint8_t *)(pThis_A + 17) != 0 && dword_79BE3C == *(uint32_t *)(pThis_A + 12) )  // 若 Value == pThis_A && *(uint8_t *)(pThis_A + 17) != 0 && dword_7..
    {
      v4 = *(uint32_t *)(pThis_A + 28);  // v4 = pThis_A+28
      v5 = *(uint32_t *)(pThis_A + 24);  // v5 = pThis_A+24
      v6 = *(uint32_t *)(pThis_A + 20);  // v6 = pThis_A+20
      v7 = sub_422E70(902);  // 调 sub_422E70
      LOBYTE(pThis_A) = sub_4649B0(v6 + (v4 >> 1), v5 - 5, -1, -16777216, 2, (int)v7, 0, 0, 1600, 0);  // 带框文本上屏（静态一次性初始化）
    }
  }
  return pThis_A;  // pThis_A=this+40 pCloseBtn
}



// ------------------------------------------------------------
// 0x648850 sub_648850 —— 商城数据 6（645EE0 + 4015C0）
// ------------------------------------------------------------
int /*fastcall*/ sub_648850(int pArg1, int nArg2, int nArg3)  // 商城数据 6（645EE0 + 4015C0）
{
  int v4; // esi
  int result; // eax
  uint8_t *v6; // eax
  bool v7; // zf
  int v8; // ecx
  int v9; // edx
  int v10; // [esp+14h] [ebp+8h]
  int v11; // [esp+14h] [ebp+8h]

  v4 = nArg3 + 4 * *(uint32_t *)(pArg1 + 2044);
  result = 84 * v4 + pArg1;
  v10 = result;
  if ( *(uint32_t *)(result + 416) != 0 )  // 若 *(uint32_t *)(result + 416) != 0
  {
    sub_645EE0((int *)pArg1);  // 商城数据 4
    if ( v4 < 19 )  // 若 v4 < 19
    {
      v6 = (uint8_t *)(v10 + 340);
      v11 = 19 - v4;
      do
      {
        qmemcpy(v6, v6 + 84, 0x54u);  // 调 qmemcpy 内联块拷贝
        v7 = v11 == 1;
        v6[80] = 0;
        v6 += 84;
        --v11;  // 自减v11
      }
      while ( !v7 );  // 当 !v7 循环
    }
    *(uint32_t *)(pArg1 + 1936) = -1;  // pArg1+1936 = -1
    *(uint32_t *)(pArg1 + 1940) = -1;  // pArg1+1940 = -1
    *(uint32_t *)(pArg1 + 1944) = 0;  // pArg1+1944 = 0
    *(uint32_t *)(pArg1 + 1948) = -1;  // pArg1+1948 = -1
    *(uint8_t *)(pArg1 + 1952) = -1;  // pArg1+1952 = -1
    *(uint32_t *)(pArg1 + 1956) = 0;  // pArg1+1956 = 0
    *(uint8_t *)(pArg1 + 1960) = 0;  // pArg1+1960 = 0
    *(uint16_t *)(pArg1 + 1962) = 0;  // pArg1+1962 = 0
    *(uint32_t *)(pArg1 + 1964) = 0;  // pArg1+1964 = 0
    *(uint32_t *)(pArg1 + 1968) = 0;  // pArg1+1968 = 0
    *(uint32_t *)(pArg1 + 1972) = 0;  // pArg1+1972 = 0
    *(uint32_t *)(pArg1 + 1976) = 0;  // pArg1+1976 = 0
    *(uint8_t *)(pArg1 + 1980) = -1;  // pArg1+1980 = -1
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    *(uint32_t *)(pArg1 + 2012) = 0;  // pArg1+2012 = 0
    v8 = *(uint32_t *)(pArg1 + 2036) - 1;
    *(uint32_t *)(pArg1 + 2036) = v8;  // pArg1+2036 = v8
    v9 = *(uint32_t *)(pArg1 + 2044);  // v9 = pArg1+2044
    result = (v8 - 1) / 4;
    *(uint32_t *)(pArg1 + 2048) = result;  // pArg1+2048 = result
    if ( v9 > result )  // 若 v9 > result
      *(uint32_t *)(pArg1 + 2044) = result;  // pArg1+2044 = result
    if ( v8 == 0 )  // 若 v8 == 0
    {
      *(uint8_t *)(*(uint32_t *)(pArg1 + 12) + 16) = 0;
      memset((void *)(pArg1 + 340), 0, 0x690u);  // 清零 1680 字节块
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x648980 sub_648980 —— CNRDCashShopBuyWindow__vmt8 Update（139 行：CLICK_BUTTON2/CLICK_MOVE/COMMAND_SELECT/SCROLL_ARROW 事件 + 6470A0/6472C0/647550/6474A0/645F20 刷新链）
// ------------------------------------------------------------
int /*thiscall*/ sub_648980(int this)  // 函数: CNRDCashShopBuyWindow__vmt8 Update（139 行：CLICK_BUTTON2/CLICK_MOVE/COMMAND_SELECT/SCROLL_ARROW 事件 + 6470A0/6472C0/647550/6474A0/645F20 刷新链）
{
  int fld_20; // eax
  int dword_79BE342; // edi
  int result; // eax
  int pCloseBtn; // eax
  int nStateWord36; // eax
  int fld_2C; // eax
  int fld_30; // eax
  int v9; // edi
  uint32_t *pThis_40; // ebx
  int v11; // eax
  int v12; // ecx
  int pThis_81C; // edx
  int i; // edx

  fld_20 = *(uint32_t *)(this + 32);  // fld_20 = this+32
  dword_79BE342 = dword_79BE34;
  if ( *(uint8_t *)(fld_20 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_20 + 12) )  // 若 *(uint8_t *)(fld_20 + 17) != 0 && dword_79BE34 == *(uint32_t *..
  {
    sub_432EA0("COMMAND_SELECT", -1, 0, 0);  // 字符串 “COMMAND_SELECT”
    return sub_6470A0(this);  // 商城条目选择刷新
  }
  else
  {
    pCloseBtn = *(uint32_t *)(this + 40);  // fld_28 = this+40
    if ( *(uint8_t *)(pCloseBtn + 17) != 0 && dword_79BE34 == *(uint32_t *)(pCloseBtn + 12) )  // 若 *(uint8_t *)(fld_28 + 17) != 0 && dword_79BE34 == *(uint32_t *..
    {
      sub_432EA0("COMMAND_SELECT", -1, 0, 0);  // 字符串 “COMMAND_SELECT”
      *(uint8_t *)(this + 2341) = 0;  // this+2341 = 0
      *(uint8_t *)(this + 2342) = 0;  // this+2342 = 0
      sub_698F90(this + 2328, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      *(uint8_t *)(*(uint32_t *)(this + 40) + 17) = 0;  // this+40 物品状态附属标志
      return sub_55E2D0(*(uint32_t *)(this + 8));  // 商城参数串（423200/423380/698F90）
    }
    else
    {
      nStateWord36 = *(uint32_t *)(this + 36);  // fld_24 = this+36
      if ( *(uint8_t *)(nStateWord36 + 17) != 0 && dword_79BE34 == *(uint32_t *)(nStateWord36 + 12) )  // 若 *(uint8_t *)(fld_24 + 17) != 0 && dword_79BE34 == *(uint32_t *..
      {
        sub_432EA0("COMMAND_SELECT", -1, 0, 0);  // 字符串 “COMMAND_SELECT”
        *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 0;  // this+12 物品类型号
        memset((void *)(this + 340), 0, 0x690u);  // 清零 1680 字节块
        return 0;
      }
      else
      {
        fld_2C = *(uint32_t *)(this + 44);  // fld_2C = this+44
        if ( *(uint8_t *)(fld_2C + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_2C + 12) )  // 若 *(uint8_t *)(fld_2C + 17) != 0 && dword_79BE34 == *(uint32_t *..
        {
          sub_432EA0("SCROLL_ARROW", -1, 0, 0);  // 字符串 “SCROLL_ARROW”
          return sub_6472C0(-1);  // 商城点击音
        }
        else
        {
          fld_30 = *(uint32_t *)(this + 48);  // fld_30 = this+48
          if ( *(uint8_t *)(fld_30 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_30 + 12) )  // 若 *(uint8_t *)(fld_30 + 17) != 0 && dword_79BE34 == *(uint32_t *..
          {
            sub_432EA0("SCROLL_ARROW", -1, 0, 0);  // 字符串 “SCROLL_ARROW”
            return sub_6472C0(1);  // 商城点击音
          }
          else if ( *(uint32_t *)(this + 2040) != 0 )  // 否则若 *(uint32_t *)(this + 2040) != 0
          {
            if ( (uint8_t)sub_43B500(*(uint32_t *)(this + 128)) != 0 )  // 焦点窗口判定（34 号）
            {
              sub_647550((uint32_t *)this, 0, -1);  // 商城页部件 2（55CCB0/645EE0 + 69A5F0）
            }
            else if ( (uint8_t)sub_43B500(*(uint32_t *)(this + 124)) != 0 )  // 焦点窗口判定（34 号）
            {
              sub_6474A0(0, -1);  // 商城页部件（645EE0 + 69A5F0）
            }
            else
            {
LABEL_28:
              v12 = 1;
              pThis_81C = this + 2076;
              do
              {
                if ( *(uint8_t *)(*(uint32_t *)pThis_81C + 17) != 0 && dword_79BE342 == *(uint32_t *)(*(uint32_t *)pThis_81C + 12) )  // 若 *(uint8_t *)(*(uint32_t *)pThis_81C + 17) != 0 && dword_79BE34..
                {
                  sub_645F20(v12);  // 商城数据 5（55ECC0 + 645EE0）
                  return (int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
                }
                ++v12;  // 自增v12
                pThis_81C += 4;
              }
              while ( v12 < 4 );  // 当 v12 < 4 循环
              result = 0;
              for ( i = this + 2088; *(uint8_t *)(*(uint32_t *)i + 17) == 0 || dword_79BE342 != *(uint32_t *)(*(uint32_t *)i + 12); i += 4 )  // 循环：i = this + 2088; *(uint8_t *)(*(uint32_t *)i + 17) == 0 || d
              {
                if ( ++result >= 60 )  // 若 ++result >= 60
                  return result;
              }
              *(uint8_t *)(*(uint32_t *)(this + 2068) + 16) = result;  // this+2068 pAnimPool2
              sub_645EE0(this);  // 商城数据 4
            }
            return (int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
          }
          else
          {
            v9 = 0;
            pThis_40 = (uint32_t *)(this + 64);  // this+64 服务器页签按钮组 6 个
            while ( 1 )  // 当 1 循环
            {
              v11 = *(pThis_40 - 2);  // pThis_40=this+64 服务器页签按钮组 6 个
              if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )  // 若 *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v..
              {
                sub_432EA0("CLICK_MOVE", -1, 0, 0);  // 字符串 “CLICK_MOVE”
                sub_648850(v9);  // 商城数据 6（645EE0 + 4015C0）
                return sub_6472C0(0);  // 商城点击音
              }
              if ( (uint8_t)sub_43B500(*pThis_40) != 0 )  // 焦点窗口判定（34 号）
              {
                sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
                return (int)sub_647550((uint32_t *)this, v9, -1);  // 商城页部件 2（55CCB0/645EE0 + 69A5F0）
              }
              if ( (uint8_t)sub_43B500(*(pThis_40 - 1)) != 0 )  // 焦点窗口判定（34 号）
                break;
              ++v9;  // 自增v9
              pThis_40 += 4;  // pThis_40=this+64 服务器页签按钮组 6 个
              if ( v9 >= 4 )  // 若 v9 >= 4
              {
                dword_79BE342 = dword_79BE34;
                goto LABEL_28;  // 跳转 LABEL_28
              }
            }
            sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 字符串 “CLICK_BUTTON2”
            return sub_6474A0(v9, -1);  // 商城页部件（645EE0 + 69A5F0）
          }
        }
      }
    }
  }
}


// ------------------------------------------------------------
// 0x648C10 CNRDCashShopBuyWindow__vmt4 —— CNRDCashShopBuyWindow__vmt4 析构（648980 + 699000）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopBuyWindow__vmt4(int this)  // 函数: CNRDCashShopBuyWindow__vmt4 析构（648980 + 699000）
{
  int result; // eax

  if ( *(uint8_t *)(*(uint32_t *)(this + 12) + 16) != 0 && *(uint8_t *)(this + 2052) == 0 )  // 判定 “+12 确认控件；+2052 购买中标志”
    sub_648980(this);  // CNRDCashShopBuyWindow__vmt8 Update
  result = sub_699000(this + 2328);  // 【clock_now(clk)】
  if ( result > 5000 )  // 若 result > 5000
    *(uint8_t *)(*(uint32_t *)(this + 40) + 17) = 1;  // this+40 pCloseBtn
  return result;
}



// ------------------------------------------------------------
// 0x648C50 sub_648C50 —— 版本信息数据（36 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_648C50(int this, LPCSTR lptstrFilename)  // 函数: 版本信息数据（36 行）
{
  const CHAR *v2; // edi
  size_t FileVersionInfoSizeA; // eax
  DWORD v5; // esi
  void *pMem; // eax
  unsigned int puLen; // [esp+Ch] [ebp-8h] BYREF
  DWORD dwHandle; // [esp+10h] [ebp-4h] BYREF

  v2 = lptstrFilename;
  dwHandle = 0;
  FileVersionInfoSizeA = GetFileVersionInfoSizeA(lptstrFilename, &dwHandle);
  v5 = FileVersionInfoSizeA;
  if ( FileVersionInfoSizeA != 0 )  // 若 FileVersionInfoSizeA != 0
  {
    pMem = malloc(FileVersionInfoSizeA);  // 调 malloc 堆分配
    *(uint32_t *)(this + 56) = pMem;  // this+56 = pMem
    if ( pMem != nullptr && GetFileVersionInfoA(v2, 0, v5, pMem) )  // 若 pMem != nullptr && GetFileVersionInfoA(v2, 0, v5, pMem)
    {
      puLen = 0;
      lptstrFilename = nullptr;  // lptstrFilename = nullptr 空指针
      if ( VerQueryValueA(*(LPCVOID *)(this + 56), SubBlock, (LPVOID *)&lptstrFilename, &puLen) )  // 若 VerQueryValueA(*(LPCVOID *)(this + 56), SubBlock, (LPVOID *)&l..
      {
        qmemcpy((void *)(this + 4), lptstrFilename, 0x34u);  // 调 qmemcpy 内联块拷贝
        *(uint32_t *)(this + 72) = *(uint32_t *)(this + 4) == -17890115;  // this+72 = *(uint32_t *)(this + 4) == -17890115
      }
    }
  }
  return *(uint32_t *)(this + 72);  // this+72 快照槽（0x6491A0：*(this+72) …
}



// ------------------------------------------------------------
// 0x648CE0 sub_648CE0 —— 版本信息数据 2（26 行）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_648CE0(uint32_t *this)  // 函数: 版本信息数据 2（26 行）
{
  unsigned int v3; // ecx
  const void *fld_e14; // [esp-10h] [ebp-1Ch]
  unsigned int puLen; // [esp+4h] [ebp-8h] BYREF
  LPVOID lpBuffer; // [esp+8h] [ebp-4h] BYREF

  if ( *(this + 18) == 0 )  // 若 *(this + 18) == 0
    return false;
  fld_e14 = (const void *)*(this + 14);
  puLen = 0;
  lpBuffer = nullptr;  // lpBuffer = nullptr 空指针
  if ( VerQueryValueA(fld_e14, "\\VarFileInfo\\Translation", &lpBuffer, &puLen) )  // 字符串 “\\VarFileInfo\\Translation”
  {
    v3 = puLen >> 2;
    *(this + 15) = lpBuffer;  // this+60 = lpBuffer
    *(this + 17) = v3;  // this+68 = v3
  }
  return *(this + 15) != 0;
}



// ------------------------------------------------------------
// 0x648D40 sub_648D40 —— 版本信息数据 3（19 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_648D40(int this)  // 函数: 版本信息数据 3（19 行）
{
  *(uint32_t *)(this + 68) = 0;  // this+68 = 0
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  memset((void *)(this + 4), 0, 0x34u);  // 清零 52 字节块
  if ( *(uint32_t *)(this + 56) != 0 )  // 若 *(uint32_t *)(this + 56) != 0
  {
    free(*(void **)(this + 56));  // 调 free 堆释放
    *(uint32_t *)(this + 56) = 0;  // this+56 = 0
  }
}



// ------------------------------------------------------------
// 0x648D80 sub_648D80 —— 版本信息数据 4（22 行）
// ------------------------------------------------------------
char */*thiscall*/ sub_648D80(char *this)  // 版本信息数据 4
{
  *((uint32_t *)this + 14) = 0;  // this+56 = 0
  *(uint32_t *)this = &vftbl_CFileVersionInfo;
  *((uint32_t *)this + 17) = 0;  // this+68 = 0
  *((uint32_t *)this + 16) = 0;  // this+64 = 0
  *((uint32_t *)this + 18) = 0;  // this+72 = 0
  *((uint32_t *)this + 15) = 0;  // this+60 = 0
  memset(this + 4, 0, 0x34u);  // 清零 52 字节块
  if ( *((uint32_t *)this + 14) != 0 )  // 若 *((uint32_t *)this + 14) != 0
  {
    free(*((void **)this + 14));  // 调 free 堆释放
    *((uint32_t *)this + 14) = 0;  // this+56 = 0
  }
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x648DD0 sub_648DD0 —— 版本信息数据 5（20 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_648DD0(char *this)  // 函数: 版本信息数据 5（20 行）
{
  *(uint32_t *)this = &vftbl_CFileVersionInfo;
  *((uint32_t *)this + 17) = 0;  // this+68 = 0
  *((uint32_t *)this + 16) = 0;  // this+64 = 0
  *((uint32_t *)this + 18) = 0;  // this+72 = 0
  *((uint32_t *)this + 15) = 0;  // this+60 = 0
  memset(this + 4, 0, 0x34u);  // 清零 52 字节块
  if ( *((uint32_t *)this + 14) != 0 )  // 若 *((uint32_t *)this + 14) != 0
  {
    free(*((void **)this + 14));  // 调 free 堆释放
    *((uint32_t *)this + 14) = 0;  // this+56 = 0
  }
}



// ------------------------------------------------------------
// 0x648E10 sub_648E10 —— 版本信息查询（648C50/648CE0，35 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_648E10(int this, LPCSTR lptstrFilename)  // 函数: 版本信息查询（648C50/648CE0，35 行）
{
  if ( lptstrFilename == nullptr )  // 若 lptstrFilename 为空
    return 0;
  *(uint32_t *)(this + 68) = 0;  // this+68 = 0
  *(uint32_t *)(this + 64) = 0;  // this+64 = 0
  *(uint32_t *)(this + 72) = 0;  // this+72 = 0
  *(uint32_t *)(this + 60) = 0;  // this+60 = 0
  memset((void *)(this + 4), 0, 0x34u);  // 清零 52 字节块
  if ( *(uint32_t *)(this + 56) != 0 )  // 若 *(uint32_t *)(this + 56) != 0
  {
    free(*(void **)(this + 56));  // 调 free 堆释放
    *(uint32_t *)(this + 56) = 0;  // this+56 = 0
  }
  if ( sub_648C50(this, lptstrFilename) == 0 || !sub_648CE0((uint32_t *)this) )  // 版本信息数据
  {
    *(uint32_t *)(this + 68) = 0;  // this+68 = 0
    *(uint32_t *)(this + 64) = 0;  // this+64 = 0
    *(uint32_t *)(this + 72) = 0;  // this+72 = 0
    *(uint32_t *)(this + 60) = 0;  // this+60 = 0
    memset((void *)(this + 4), 0, 0x34u);  // 清零 52 字节块
    if ( *(uint32_t *)(this + 56) != 0 )  // 若 *(uint32_t *)(this + 56) != 0
    {
      free(*(void **)(this + 56));  // 调 free 堆释放
      *(uint32_t *)(this + 56) = 0;  // this+56 = 0
    }
  }
  return *(uint32_t *)(this + 72);  // this+72 快照槽（0x6491A0：*(this+72) …
}



// ------------------------------------------------------------
// 0x648EB0 CFileVersionInfo__vmt0 —— CFileVersionInfo__vmt0 构造（23 行——GetFileVersionInfo 系封装）
// ------------------------------------------------------------
char */*thiscall*/ CFileVersionInfo__vmt0(char *Block, char pszArg2)  // CFileVersionInfo__vmt0 构造（23 行——GetFileVersionInfo 系封装）
{
  *(uint32_t *)Block = &vftbl_CFileVersionInfo;
  *((uint32_t *)Block + 17) = 0;
  *((uint32_t *)Block + 16) = 0;
  *((uint32_t *)Block + 18) = 0;
  *((uint32_t *)Block + 15) = 0;
  memset(Block + 4, 0, 0x34u);  // 清零 52 字节块
  if ( *((uint32_t *)Block + 14) != 0 )  // 若 *((uint32_t *)Block + 14) != 0
  {
    free(*((void **)Block + 14));  // 调 free 堆释放
    *((uint32_t *)Block + 14) = 0;
  }
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x648F10 sub_648F10 —— 版本信息转发（648E10）
// ------------------------------------------------------------
int /*thiscall*/ sub_648F10(void *this, HMODULE hModule)  // 函数: 版本信息转发（648E10）
{
  CHAR Filename[260]; // [esp+8h] [ebp-108h] BYREF
  int dword_796E502; // [esp+10Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  memset(Filename, 0, sizeof(Filename));  // 调 memset 按字节填充
  if ( GetModuleFileNameA(hModule, Filename, 0x104u) != 0 )  // 若 GetModuleFileNameA(hModule, Filename, 0x104u) != 0
    return sub_648E10((int)this, Filename);  // 版本信息查询
  else
    return 0;
}



// ============================================================
// 【分区 9】冰光环族 CNAuraMasterIce / CNIceDamageFromIceAura（0x648F90-0x649D70）
// 资源 IceAuraMaster.ani + IceAuraMinionSnowFlake.ptl/IceAuraMinionSteam.ptl；
// 事件 AURA_ICE_SET（vmt78 生效）+ AURA_ICE_DMG；648FB0=冰冻伤害结算
// （605840/4E4A50/432FA0）。
// ============================================================
// ------------------------------------------------------------
// 0x648F90 CNAuraMasterIce__vmt1C —— CNAuraMasterIce__vmt1C 生成装配：Common/Etc/Animation/Aura/IceAuraMaster.ani
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterIce__vmt1C(void *this)  // 函数: CNAuraMasterIce__vmt1C 生成装配：Common/Etc/Animation/Aura/IceAuraMaster.ani
{
  CNRDAuraMaster__vmt1C();  // 调 CNRDAuraMaster__vmt1C 生成装配
  return (*(int (/*thiscall*/ **)(void *, const char *))(*(uint32_t *)this + 128))(  // this+128 第 2 组·+1208 增量子倍率
           this,
           "Common/Etc/Animation/Aura/IceAuraMaster.ani");  // 字符串 “Common/Etc/Animation/Aura/IceAuraMaster.ani”
}



// ------------------------------------------------------------
// 0x648FB0 sub_648FB0 —— 冰冻伤害结算：AURA_ICE_DMG 事件（605840 目标 + 4E4A50/432FA0），79 行
// ------------------------------------------------------------
int /*thiscall*/ sub_648FB0(int this)  // 函数: 冰冻伤害结算：AURA_ICE_DMG 事件（605840 目标 + 4E4A50/432FA0），79 行
{
  int result; // eax
  int fld_4; // ecx
  int v4; // eax
  int fld_42; // ecx
  int v6; // eax
  int fld_43; // edi
  int v8; // ebx
  int v9; // ebx
  int fld_44; // eax
  int16_t *v11; // eax
  float v12; // [esp+4h] [ebp-20h] BYREF
  float v13; // [esp+8h] [ebp-1Ch]
  float v14; // [esp+Ch] [ebp-18h]
  int v15; // [esp+10h] [ebp-14h]
  int v16; // [esp+14h] [ebp-10h]
  int v17; // [esp+18h] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-8h]
  int v19; // [esp+20h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 100) + 12))(*(uint32_t *)(this + 100), 0);  // 调用虚函数槽 +12
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 104) + 12))(*(uint32_t *)(this + 104), 0);  // 调用虚函数槽 +12
  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +308
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 624))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +624
    if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
    {
      fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
      v12 = 0.0;
      v13 = 0.0;
      v14 = 0.0;
      v15 = 0;
      v16 = 0;
      v17 = 0;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 120))(fld_4);  // 调用虚函数槽 +120
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
      v18 = v4;
      v12 = (float)v4;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_42 + 124))(fld_42);  // 调用虚函数槽 +124
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
      v18 = v6;
      v13 = (float)v6;
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 192))(fld_43) / 2;  // fld_43=this+4 宿主对象
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 128))(fld_43) + v8;  // fld_43=this+4 宿主对象
      fld_44 = *(uint32_t *)(this + 4);  // fld_44 = this+4
      v18 = v9;
      v14 = (float)v9;
      v19 = 0;
      v11 = sub_605840(&v19, fld_44, (int *)&v12, 1);  // 结果 = 30 字节全局包
      sub_4E4A50(*(uint32_t *)(this + 36), 42003, *(uint32_t *)(this + 96), 0, 0, 0, 1, 0, v19, v11);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(  // this+4 宿主对象
        *(uint32_t *)(this + 4),  // this+4 宿主对象
        "AURA_ICE_DMG",  // 字符串 “AURA_ICE_DMG”
        -1,
        0,
        0);
      sub_432FA0();  // srand 播种
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 776))(*(uint32_t *)(this + 4), 1) == 0 )  // this+4 宿主对象 等2字段
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 760))(  // this+4 宿主对象
          *(uint32_t *)(this + 4),  // this+4 宿主对象
          1,
          1103626240,
          2,
          *(uint32_t *)(this + 36),  // this+36 物品状态字
          0);
      result = *(uint32_t *)(this + 108);  // result = this+108
      *(uint32_t *)(this + 72) = result;  // this+72 = result
    }
  }
  return result;  // result=this+108 第 1 组·宿主属性 +886 增量
}



// ------------------------------------------------------------
// 0x649100 CNAuraMasterCurse__vmt84 —— CNAuraMasterCurse__vmt84 受击伤害事件槽（22 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraMasterCurse__vmt84(uint32_t **this, int nArg2)  // 函数: CNAuraMasterCurse__vmt84 受击伤害事件槽（22 行）
{
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（0x6499A0: vt+940 判、vt+340 图类型）（CNAuraMasterCurse；va=006499A0）
  bool result; // al

  result = true;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) == 0 )  // 虚槽+40 CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/4868
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) == 0 )  // 虚槽+40 CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/4868
      return false;
    pHostObj = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 376))(*(this + 1));  // 调用虚函数槽 +376
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) != pHostObj )  // 虚槽+376 坐标同步包（type 37）
      return false;
  }
  return result;
}



// ------------------------------------------------------------
// 0x649160 CNDarkDamageFromCurseAura__vmt1C —— CNDarkDamageFromCurseAura__vmt1C 生成装配（5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNDarkDamageFromCurseAura__vmt1C(void *this)  // 函数: CNDarkDamageFromCurseAura__vmt1C 生成装配（5F66A0）
{
  return sub_5F66A0((int)this, 1);  // 调 sub_5F66A0
}



// ------------------------------------------------------------
// 0x649170 CNDarkDamageFromCurseAura__vmt78 —— CNDarkDamageFromCurseAura__vmt78 光环生效槽（17 行）
// ------------------------------------------------------------
int /*thiscall*/ CNDarkDamageFromCurseAura__vmt78(uint32_t *this)  // 函数: CNDarkDamageFromCurseAura__vmt78 光环生效槽（17 行）
{
  int (/*thiscall*/ ***fld_e26)(uint32_t, int); // ecx
  int result; // eax

  fld_e26 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  if ( fld_e26 != nullptr )  // 若 fld_e26 非空
    result = (**fld_e26)(fld_e26, 1);
  *(this + 26) = 0;  // this+104 = 0
  return result;
}



// ------------------------------------------------------------
// 0x6491A0 CNDarkDamageFromCurseAura__vmt4 —— CNDarkDamageFromCurseAura__vmt4 复位/伤害（605840/4E4A50/699000，80 行）
// ------------------------------------------------------------
int /*thiscall*/ CNDarkDamageFromCurseAura__vmt4(int this)  // 函数: CNDarkDamageFromCurseAura__vmt4 复位/伤害（605840/4E4A50/699000，80 行）
{
  int result; // eax
  int pHost4; // ecx  | +0x0004 → 宿主对象（CNDarkDamageFromCurseAura；va=006491A0）
  int v4; // eax
  int pHost4_; // ecx  | +0x0004 → 宿主对象（CNDarkDamageFromCurseAura；va=006491A0）
  int v6; // eax
  int *pHost4_2; // edi
  int v8; // eax
  int v9; // edx
  int v10; // ecx
  int pHost4_3; // eax  | +0x0004 → 宿主对象（CNDarkDamageFromCurseAura；va=006491A0）
  int16_t *v12; // eax
  int nParam132; // edi  | +0x0084 → 光环参数槽（CNDarkDamageFromCurseAura；va=006491A0）
  float v14; // [esp+8h] [ebp-20h] BYREF
  float v15; // [esp+Ch] [ebp-1Ch]
  float v16; // [esp+10h] [ebp-18h]
  int v17; // [esp+14h] [ebp-14h]
  int v18; // [esp+18h] [ebp-10h]
  int v19; // [esp+1Ch] [ebp-Ch]
  int v20; // [esp+20h] [ebp-8h]
  int v21; // [esp+24h] [ebp-4h] BYREF

  CNRDAuraMinion__vmt4();  // 调 CNRDAuraMinion__vmt4 复位槽
  result = *(uint32_t *)(this + 136);  // 读 result = this+136（相位门）
  if ( result == 2 )  // 若 result == 2
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +308
    if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4)) < 50  // 判定 “+4 宿主对象”
        && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 624))(*(uint32_t *)(this + 4)) != 0 )  // CNDarkDamageFromCurseAura__vmt4 复位/伤害（605840/4E4A50/699000，80 行）
      {
        pHost4 = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象）
        v14 = 0.0;
        v15 = 0.0;
        v16 = 0.0;
        v17 = 0;
        v18 = 0;
        v19 = 0;
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHost4 + 120))(pHost4);  // 调用虚函数槽 +120
        pHost4_ = *(uint32_t *)(this + 4);  // 读 fld_42 = this+4（宿主对象）
        v20 = v4;
        v14 = (float)v4;
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHost4_ + 124))(pHost4_);  // 调用虚函数槽 +124
        pHost4_2 = *(int **)(this + 4);  // this+4 pHost4
        v20 = v6;
        v15 = (float)v6;
        v8 = (*(int (/*thiscall*/ **)(int *))(*pHost4_2 + 192))(pHost4_2);  // 结果 = 虚调用 vt+192
        v9 = *pHost4_2;  // fld_43=this+4 pHost4
        v20 = v8 / 2;
        v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 128))(pHost4_2) + v8 / 2;  // fld_43=this+4 pHost4
        pHost4_3 = *(uint32_t *)(this + 4);  // 读 fld_44 = this+4（宿主对象）
        v20 = v10;
        v16 = (float)v10;
        v21 = 0;
        v12 = sub_605840(&v21, pHost4_3, (int *)&v14, 1);  // 结果 = 30 字节全局包
        sub_4E4A50(*(uint32_t *)(this + 36), 42005, *(uint32_t *)(this + 96), 0, 0, 0, 1, 0, v21, v12);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      }
      result = *(uint32_t *)(this + 100);  // 读 result = this+100（源值槽）
      *(uint32_t *)(this + 72) = result;  // 写 this+72 = result（快照槽）
      *(uint8_t *)(this + 140) = 1;  // 写 this+140 = 1（已触发标志）
      *(uint32_t *)(this + 136) = 0;  // 写 this+136 = 0（相位门）
    }
  }
  else if ( result == 1 )  // 否则若 result == 1
  {
    nParam132 = *(uint32_t *)(this + 132);  // 读 fld_84 = this+132（光环参数槽）
    result = sub_699000(this + 108);  // 【clock_now(clk)】
    if ( result >= nParam132 )  // 若 result >= fld_84
      *(uint32_t *)(this + 136) = 2;  // 写 this+136 = 2（相位门）
  }
  return result;  // result=this+100 nSrc100
}



// ------------------------------------------------------------
// 0x649300 sub_649300 —— 召唤受方表现初始化（64A880 + 5F6640）
// ------------------------------------------------------------
int /*thiscall*/ sub_649300(int this)  // 函数: 召唤受方表现初始化（64A880 + 5F6640）
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRDAuraMinion;
  sub_64A880();  // 受击表现（42AF90/657740）
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);  // 调 sub_5F6640
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;  // this+8 = &vftbl_nengine__IObject
  *(uint8_t *)(this + 12) = 0;  // this+12 = 0
  return result;
}



// ------------------------------------------------------------
// 0x649360 CNRDAuraMinion__vmt0 —— CNRDAuraMinion__vmt0 析构（转发 649300）
// ------------------------------------------------------------
void */*thiscall*/ CNRDAuraMinion__vmt0(void *Block, char pszArg2)  // CNRDAuraMinion__vmt0 析构（转发 649300）
{
  sub_649300((int)Block);  // 召唤受方表现初始化（64A880 + 5F6640）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x649390 sub_649390 —— 冰受方装配（4B1030 + 64A350）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_649390(uint32_t *this, int nArg2, int nArg3)  // 冰受方装配（4B1030 + 64A350）
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNRDAuraMinion;  // *this 写入 &vftbl_CNRDAuraMinion
  sub_64A350(this);  // 受方表现转发
  *this = &vftbl_CNIceDamageFromIceAura;  // *this 写入 &vftbl_CNIceDamageFromIceAura
  *(this + 24) = nArg2;  // this+96 = nArg2
  *(this + 27) = nArg3;  // this+108 = nArg3
  *(this + 18) = (uint64_t)((double)nArg3 * 0.5);  // this+72 = (uint64_t)((double)nArg3 * 0.5)
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x649400 CNIceDamageFromIceAura__vmt0 —— CNIceDamageFromIceAura__vmt0 析构（转发 649430）
// ------------------------------------------------------------
void */*thiscall*/ CNIceDamageFromIceAura__vmt0(void *Block, char pszArg2)  // CNIceDamageFromIceAura__vmt0 析构（转发 649430）
{
  sub_649430();  // 冰受方初始化
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x649430 sub_649430 —— 冰受方初始化（649300 系，22 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_649430(uint32_t *this)  // 函数: 冰受方初始化（649300 系，22 行）
{
  void (/*thiscall*/ ***fld_e25)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e26)(uint32_t, int); // ecx

  *this = &vftbl_CNIceDamageFromIceAura;  // *this 写入 &vftbl_CNIceDamageFromIceAura
  fld_e25 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  if ( fld_e25 != nullptr )  // 若 fld_e25 非空
    (**fld_e25)(fld_e25, 1);
  fld_e26 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  *(this + 25) = 0;  // this+100 = 0
  if ( fld_e26 != nullptr )  // 若 fld_e26 非空
    (**fld_e26)(fld_e26, 1);
  *(this + 26) = 0;  // this+104 = 0
  return sub_649300((int)this);  // 召唤受方表现初始化（64A880 + 5F6640）
}



// ------------------------------------------------------------
// 0x6494B0 sub_6494B0 —— 诅咒受方装配（4B1030 + 64A350 + 698F90）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_6494B0(uint8_t *this, int nArg2, int nArg3)  // 诅咒受方装配（4B1030 + 64A350 + 698F90）
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *(uint32_t *)this = &vftbl_CNRDAuraMinion;
  sub_64A350(this);  // 受方表现转发
  *(uint32_t *)this = &vftbl_CNDarkDamageFromCurseAura;
  *(this + 112) = 0;  // this+448 = 0
  *((uint32_t *)this + 27) = &vftbl_nengine__CNTimer;  // this+108 = &vftbl_nengine__CNTimer
  *((uint32_t *)this + 29) = 0;  // this+116 = 0
  *(this + 120) = 1;  // this+480 = 1
  *(this + 122) = 0;  // this+488 = 0
  *(this + 121) = 0;  // this+484 = 0
  *((uint32_t *)this + 33) = 0;  // this+132 = 0
  *((uint32_t *)this + 32) = 0;  // this+128 = 0
  *((uint32_t *)this + 31) = 0;  // this+124 = 0
  *((uint32_t *)this + 25) = nArg3;  // this+100 = nArg3
  *((uint32_t *)this + 24) = nArg2;  // this+96 = nArg2
  *(this + 121) = 0;  // this+484 = 0
  *(this + 122) = 0;  // this+488 = 0
  sub_698F90((int)(this + 108), 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint32_t *)this + 26) = 0;  // this+104 = 0
  *((uint32_t *)this + 34) = 1;  // this+136 = 1
  *(this + 140) = 1;  // this+560 = 1
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x649560 sub_649560 —— 诅咒受方初始化（649300，19 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_649560(uint32_t *this)  // 函数: 诅咒受方初始化（649300，19 行）
{
  void (/*thiscall*/ ***fld_e26)(uint32_t, int); // ecx

  *this = &vftbl_CNDarkDamageFromCurseAura;  // *this 写入 &vftbl_CNDarkDamageFromCurseAura
  fld_e26 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  if ( fld_e26 != nullptr )  // 若 fld_e26 非空
    (**fld_e26)(fld_e26, 1);
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = &vftbl_nengine__IObject;  // this+108 = &vftbl_nengine__IObject
  *((uint8_t *)this + 112) = 0;  // this+112 第 1 组·宿主属性 +46 增量子倍率
  return sub_649300((int)this);  // 召唤受方表现初始化（64A880 + 5F6640）
}



// ------------------------------------------------------------
// 0x6495D0 CNAuraMasterIce__vmt78 —— CNAuraMasterIce__vmt78 光环生效：AURA_ICE_SET 事件（转发 649390）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterIce__vmt78(int *this, int nArg2)  // 函数: CNAuraMasterIce__vmt78 光环生效：AURA_ICE_SET 事件（转发 649390）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e32; // eax

  pMem = operator new(0x70u);  // 堆分配 112 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e32 = sub_649390(pMem, *(this + 32), *(this + 33));  // 结果 = 冰受方装配（4B1030 + 64A350）
  else
    fld_e32 = nullptr;  // fld_e32 = nullptr 空指针
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*fld_e32 + 56))(  // 虚调用 vt+56
    fld_e32,
    nArg2,
    *(this + 1),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 212))(  // 虚槽+212 音效标签播放（szPassword 去重 → sub_65FE10 分发到 50 声道）
           nArg2,
           "AURA_ICE_SET",  // 字符串 “AURA_ICE_SET”
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x649670 CNDarkDamageFromCurseAura__vmt0 —— CNDarkDamageFromCurseAura__vmt0 析构（转发 649560）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNDarkDamageFromCurseAura__vmt0(uint32_t *Block, char pszArg2)  // CNDarkDamageFromCurseAura__vmt0 析构（转发 649560）
{
  sub_649560(Block);  // 诅咒受方初始化
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x6496A0 CNAuraMasterIce__vmt7C —— CNAuraMasterIce__vmt7C 光环失效/转移槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterIce__vmt7C(int nArg1)  // 函数: CNAuraMasterIce__vmt7C 光环失效/转移槽（58 行）
{
  unsigned int i; // edi
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int pObj; // eax

  if ( nArg1 != 0 )  // 若 nArg1 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v3 = *(uint32_t *)(v2 + 4);  // v3 = v2+4
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )  // 若 (int)i >= v4
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v6 = *(uint32_t *)(v5 + 4);  // v6 = v5+4
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )  // 若 v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == nArg1 )  // 若 *(uint32_t *)(v7 + 4) == nArg1
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
        v9 = *(uint32_t *)(v8 + 4);  // v9 = v8+4
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )  // 若 v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        pObj = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNIceDamageFromIceAura `RTTI Type Descriptor',
                0);
        if ( pObj != 0 )  // 若 pObj != 0
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 调用虚函数槽 +76
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x649750 CNAuraMasterCurse__vmt7C —— CNAuraMasterCurse__vmt7C 光环失效/转移槽（108 行）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterCurse__vmt7C(uint32_t *this, int nArg2)  // 函数: CNAuraMasterCurse__vmt7C 光环失效/转移槽（108 行）
{
  unsigned int i; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int pObj2; // eax
  int result; // eax
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（0x6499A0: vt+940 判、vt+340 图类型）（CNAuraMasterCurse；va=006499A0）
  int v16; // ebx
  unsigned int j; // edi
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // ecx
  int v23; // eax
  int v24; // ecx
  int v25; // ecx
  int pObj; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) != 0 )  // 虚槽+40 CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/4868
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v5 = *(uint32_t *)(v4 + 4);  // v5 = v4+4
      v6 = v5 != 0 ? (*(uint32_t *)(v4 + 8) - v5) >> 2 : 0;
      if ( (int)i >= v6 )  // 若 (int)i >= v6
        break;
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v8 = *(uint32_t *)(v7 + 4);  // v8 = v7+4
      if ( v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2 )  // 若 v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2
        v9 = *(uint32_t *)(v8 + 4 * i);
      else
        v9 = 0;
      if ( *(uint32_t *)(v9 + 4) == nArg2 )  // 若 *(uint32_t *)(v9 + 4) == nArg2
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
        v11 = *(uint32_t *)(v10 + 4);  // v11 = v10+4
        if ( v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2 )  // 若 v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2
          v12 = *(uint32_t *)(v11 + 4 * i);
        else
          v12 = 0;
        pObj2 = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                v12,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNDarkDamageFromCurseAura `RTTI Type Descriptor',
                0);
        if ( pObj2 != 0 )  // 若 pObj2 != 0
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);  // 调用虚函数槽 +76
          break;
        }
      }
    }
  }
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529);  // 调用虚函数槽 +40
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    pHostObj = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 调用虚函数槽 +376
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 376))(pHostObj);  // 调用虚函数槽 +376
    if ( v16 == result )  // 若 v16 == result
    {
      for ( j = 0; ; ++j )  // 循环：j = 0; ; ++j
      {
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
        v19 = *(uint32_t *)(v18 + 4);  // v19 = v18+4
        result = v19 != 0 ? (*(uint32_t *)(v18 + 8) - v19) >> 2 : 0;
        if ( (int)j >= result )  // 若 (int)j >= result
          break;
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
        v21 = *(uint32_t *)(v20 + 4);  // v21 = v20+4
        if ( v21 != 0 && j < (*(uint32_t *)(v20 + 8) - v21) >> 2 )  // 若 v21 != 0 && j < (*(uint32_t *)(v20 + 8) - v21) >> 2
          v22 = *(uint32_t *)(v21 + 4 * j);
        else
          v22 = 0;
        if ( *(uint32_t *)(v22 + 4) == nArg2 )  // 若 *(uint32_t *)(v22 + 4) == nArg2
        {
          v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
          v24 = *(uint32_t *)(v23 + 4);  // v24 = v23+4
          if ( v24 != 0 && j < (*(uint32_t *)(v23 + 8) - v24) >> 2 )  // 若 v24 != 0 && j < (*(uint32_t *)(v23 + 8) - v24) >> 2
            v25 = *(uint32_t *)(v24 + 4 * j);
          else
            v25 = 0;
          pObj = __RTDynamicCast(v25, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeStatus `RTTI Type Descriptor', 0);  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
          if ( pObj != 0 )  // 若 pObj != 0
            return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 调用虚函数槽 +76
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6498E0 CNIceDamageFromIceAura__vmt4 —— CNIceDamageFromIceAura__vmt4 伤害/复位（4600B0，62 行）
// ------------------------------------------------------------
int /*thiscall*/ CNIceDamageFromIceAura__vmt4(char *this)  // 函数: CNIceDamageFromIceAura__vmt4 伤害/复位（4600B0，62 行）
{
  char *pThis; // esi
  int **v2; // edi
  int pObj; // esi
  int v4; // ebx
  int *v5; // ecx
  int v6; // edx
  void *v7; // eax
  bool v8; // zf
  int result; // eax
  int v10; // [esp-Ch] [ebp-3Ch]
  int v11; // [esp-8h] [ebp-38h]
  int v12; // [esp-4h] [ebp-34h]
  char v13[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int v15; // [esp+14h] [ebp-1Ch]
  int v16; // [esp+18h] [ebp-18h]
  char *pThis2; // [esp+1Ch] [ebp-14h]
  int v18; // [esp+20h] [ebp-10h]
  int v19; // [esp+2Ch] [ebp-4h]

  pThis = this;
  pThis2 = this;
  CNRDAuraMinion__vmt4();  // 调 CNRDAuraMinion__vmt4 复位槽
  v2 = (int **)(pThis + 100);
  v18 = 2;
  do
  {
    pObj = *((uint32_t *)pThis + 1);
    v4 = **v2;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);  // 调用虚函数槽 +128
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调用虚函数槽 +124
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调用虚函数槽 +120
    (*(void (/*thiscall*/ **)(int *))(v4 + 40))(*v2);  // 调用虚函数槽 +40
    (*(void (/*thiscall*/ **)(int *, char *))(**v2 + 92))(*v2, v13);  // 虚调用 vt+92
    pThis = pThis2;
    v5 = *((int **)pThis2 + 1);
    v6 = *v5;
    v19 = 0;
    v7 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v6 + 80))(v5, 2, 0, v13);
    sub_4600B0(v7, v10, v11, v12);  // 调 sub_4600B0
    v19 = -1;
    if ( Block != nullptr )  // 若 Block 非空
      j__free(Block);  // 调 j__free
    ++v2;  // 自增v2
    result = v18 - 1;
    v8 = v18 == 1;
    Block = nullptr;  // Block = nullptr 空指针
    v15 = 0;
    v16 = 0;
    --v18;  // 自减v18
  }
  while ( !v8 );  // 当 !v8 循环
  return result;
}



// ------------------------------------------------------------
// 0x6499A0 CNAuraMasterCurse__vmt4 —— CNAuraMasterCurse__vmt4 复位（699000/698F90/4600B0/41C5E0，99 行）
// ------------------------------------------------------------
void /*thiscall*/ CNAuraMasterCurse__vmt4(int this)  // 函数: CNAuraMasterCurse__vmt4 复位（699000/698F90/4600B0/41C5E0，99 行）
{
  int nNextTickMs; // ebx  | +0x00A4 → 下个周期时刻 ms（CNAuraMasterCurse；va=006499A0）
  int pHostObj_; // edi  | +0x0004 → 宿主对象指针（0x6499A0: vt+940 判、vt+340 图类型）（CNAuraMasterCurse；va=006499A0）
  int pCurseAnim; // ebx  | +0x0080 → 诅咒动画件（0x6499A0: *(this+128) 经 vt+12/vt+112 复位 + 宿主坐标合成落位）（CNAuraMasterCurse；va=006499A0）
  int v5; // eax
  int v6; // eax
  int *pHostObj_2; // ecx
  int v8; // edx
  void *v9; // eax
  uint32_t *fld_74; // eax
  uint32_t *v11; // ecx
  int pObj; // edi
  int fld_802; // ebx  | +0x0080 → 诅咒动画件（0x6499A0: *(this+128) 经 vt+12/vt+112 复位 + 宿主坐标合成落位）（CNAuraMasterCurse；va=006499A0）
  int v14; // eax
  int v15; // eax
  int *pHostObj_3; // ecx
  int v17; // edx
  void *v18; // eax
  int v19; // [esp-Ch] [ebp-48h]
  int v20; // [esp-Ch] [ebp-48h]
  int pHostObj; // [esp-8h] [ebp-44h]  | +0x0004 → 宿主对象指针（0x6499A0: vt+940 判、vt+340 图类型）（CNAuraMasterCurse；va=006499A0）
  char v22[4]; // [esp+Ch] [ebp-30h] BYREF
  void *v23; // [esp+10h] [ebp-2Ch]
  char v24[4]; // [esp+1Ch] [ebp-20h] BYREF
  void *Block; // [esp+20h] [ebp-1Ch]
  int v26; // [esp+24h] [ebp-18h]
  int v27; // [esp+28h] [ebp-14h]
  uint32_t *v28; // [esp+2Ch] [ebp-10h] BYREF
  int v29; // [esp+38h] [ebp-4h]

  CNRDAuraMaster__vmt4();  // 调 CNRDAuraMaster__vmt4 析构复位
  nNextTickMs = *(uint32_t *)(this + 164);  // 读 fld_A4 = this+164（下个周期时刻 ms）
  if ( sub_699000(this + 140) >= nNextTickMs )  // 【clock_now(clk)】
  {
    *(uint8_t *)(this + 153) = 0;  // 写 this+153 = 0（施放标志 A）
    *(uint8_t *)(this + 154) = 0;  // 写 this+154 = 0（施放标志 B）
    sub_698F90(this + 140, 125, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 128) + 12))(*(uint32_t *)(this + 128));  // 调用虚函数槽 +12
    pHostObj = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 128) + 112))(*(uint32_t *)(this + 128));  // 调用虚函数槽 +112
    pHostObj_ = *(uint32_t *)(this + 4);  // 读 fld_42 = this+4（宿主对象指针）
    pCurseAnim = **(uint32_t **)(this + 128);  // this+128 pCurseAnim
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_ + 128))(pHostObj_) + 32;  // fld_42=this+4 pHostObj
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj_ + 124))(pHostObj_);  // 调用虚函数槽 +124
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pHostObj_ + 120))(pHostObj_, v5);  // 调用虚函数槽 +120
    (*(void (/*thiscall*/ **)(uint32_t, int))(pCurseAnim + 40))(*(uint32_t *)(this + 128), v6);  // 调用虚函数槽 +40
    (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(this + 128) + 92))(*(uint32_t *)(this + 128), v22);  // 调用虚函数槽 +92
    pHostObj_2 = *(int **)(this + 4);  // this+4 pHostObj
    v8 = *pHostObj_2;  // fld_43=this+4 pHostObj
    v29 = 0;
    v9 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v8 + 80))(pHostObj_2, 2, 0, v22);  // fld_43=this+4 pHostObj
    sub_4600B0(v9, v19, pHostObj, 0);  // 调 sub_4600B0
    fld_74 = *(uint32_t **)(this + 116);  // this+116 观察者 vector 尾针
    v11 = (uint32_t *)*fld_74;  // fld_74=this+116 观察者 vector 尾针
    v28 = (uint32_t *)*fld_74;  // fld_74=this+116 观察者 vector 尾针
    if ( v28 != fld_74 )  // 若 v28 != fld_74
    {
      do
      {
        pObj = v11[4];
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 273) == 0  // 虚槽+40 CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/4868
          || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) < 50 )  // CNAuraMasterCurse__vmt4 复位（699000/698F90/4600B0/41C5E0，99 行）
        {
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 128) + 12))(*(uint32_t *)(this + 128));  // 调用虚函数槽 +12
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 128) + 112))(*(uint32_t *)(this + 128));  // 调用虚函数槽 +112
          fld_802 = **(uint32_t **)(this + 128);  // this+128 pCurseAnim
          v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) + 32;  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调用虚函数槽 +124
          v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v14);  // 调用虚函数槽 +120
          (*(void (/*thiscall*/ **)(uint32_t, int))(fld_802 + 40))(*(uint32_t *)(this + 128), v15);  // 调用虚函数槽 +40
          (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(this + 128) + 92))(*(uint32_t *)(this + 128), v24);  // 调用虚函数槽 +92
          pHostObj_3 = *(int **)(this + 4);  // this+4 pHostObj
          v17 = *pHostObj_3;  // fld_44=this+4 pHostObj
          LOBYTE(v29) = 1;
          v18 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v17 + 80))(pHostObj_3, 2, 0, v24);  // fld_44=this+4 pHostObj
          sub_4600B0(v18, v20, pObj, 0);  // 调 sub_4600B0
          LOBYTE(v29) = 0;
          if ( Block != nullptr )  // 若 Block 非空
            j__free(Block);  // 调 j__free
          Block = nullptr;  // Block = nullptr 空指针
          v26 = 0;
          v27 = 0;
        }
        sub_41C5E0(&v28);  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
        v11 = v28;
      }
      while ( v28 != *(uint32_t **)(this + 116) );  // 当 v28 != *(uint32_t **)(this + 116) 循环
    }
    if ( v23 != nullptr )  // 若 v23 非空
      j__free(v23);  // 调 j__free
  }
}



// ------------------------------------------------------------
// 0x649B70 CNAuraMasterCurse__vmt78 —— CNAuraMasterCurse__vmt78 光环生效（6494B0 + 5101B0，79 行）
// ------------------------------------------------------------
void */*userpurge*/ CNAuraMasterCurse__vmt78@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int *Block)  // CNAuraMasterCurse__vmt78 光环生效（6494B0 + 5101B0，79 行）
{
  uint8_t *pMem; // eax
  uint8_t *v6; // eax
  int v7; // edx
  void *result; // eax
  int pObj; // ebx
  double v10; // st7
  int v11; // eax
  uint64_t v12; // rax
  uint32_t *pMem2; // eax
  int *v14; // eax
  int v15; // edx
  int v16; // [esp-14h] [ebp-3Ch]
  int v18; // [esp+8h] [ebp-20h] BYREF
  char v19; // [esp+Ch] [ebp-1Ch]
  int v20; // [esp+10h] [ebp-18h]
  double v21; // [esp+14h] [ebp-14h]
  int v22; // [esp+24h] [ebp-4h]
  void *Blocka; // [esp+30h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*Block + 40))(Block, 273) != 0 )  // 虚调用 vt+40
  {
    pMem = operator new(0x90u);  // 堆分配 144 字节对象
    v22 = 0;
    if ( pMem != nullptr )  // 若 pMem 非空
      v6 = sub_6494B0(pMem, pArg1[34], pArg1[33]);  // 结果 = 诅咒受方装配（4B1030 + 64A350 + 698F90）
    else
      v6 = nullptr;  // v6 = nullptr 空指针
    v7 = *(uint32_t *)v6;  // v7 = v6
    v16 = pArg1[1];
    v22 = -1;
    (*(void (/*thiscall*/ **)(uint8_t *, int *, int, uint32_t, uint32_t, uint32_t, int))(v7 + 56))(v6, Block, v16, 0, 0, 0, -1);  // 调用虚函数槽 +56
  }
  result = (void *)(*(int (/*thiscall*/ **)(int *, int))(*Block + 40))(Block, 529);  // 结果 = 虚调用 vt+40
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    pObj = pArg1[1];
    Blocka = (void *)(*(int (/*thiscall*/ **)(int *))(*Block + 376))(Block);  // 结果 = 虚调用 vt+376
    result = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 虚槽+376 坐标同步包（type 37）
    if ( Blocka == result )  // 若 Blocka == result
    {
      result = (void *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1] + 308))(pArg1[1]);
      if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
      {
        v10 = (double)(*(int (/*thiscall*/ **)(int *, int))(*Block + 740))(Block, nArg2);  // 结果 = 虚调用 vt+740
        v11 = *Block;
        v21 = v10 * 0.01;
        v12 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(v11 + 736))(Block) + v21);
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*Block + 728))(Block, v12, 1, 0);  // 虚调用 vt+728
        v18 = 7;
        v19 = 1;
        v20 = 1133903872;
        pMem2 = operator new(0x7Cu);  // 堆分配 124 字节对象
        v22 = 1;
        if ( pMem2 != nullptr )  // 若 pMem2 非空
          v14 = sub_5101B0(pMem2, (int)&v18, 1, 5000, 0);  // 调 sub_5101B0
        else
          v14 = nullptr;  // v14 = nullptr 空指针
        v15 = *v14;
        v22 = -1;
        return (void *)(*(int (/*thiscall*/ **)(int *, int *, int *, uint32_t, uint32_t, uint32_t))(v15 + 56))(
                         v14,
                         Block,
                         Block,
                         0,
                         0,
                         0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x649CF0 sub_649CF0 —— 诅咒动画查询（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_649CF0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 诅咒动画查询（5910D0）
{
  sub_5910D0(nArg2, 18, 500, 0);  // CNRDAuraMaster 构造函数
  *this = &vftbl_CNAuraMasterIce;  // *this 写入 &vftbl_CNAuraMasterIce
  *(this + 32) = nArg4;  // this+128 = nArg4
  *(this + 33) = nArg3;  // this+132 = nArg3
  return this;  // 返回自身指针
}



// ============================================================
// 【分区 10】诅咒光环族 CNAuraMasterCurse / CNDarkDamageFromCurseAura（0x649D30-0x64A150）
// 资源 CurseAura.ptl；649FF0 挂 Monster/Ghoul/Particle/GhoulCurse.ptl
// （食尸鬼诅咒共用）；CNAuraChangeStatusMaster 系变化状态基类在本区尾段。
// ============================================================
// ------------------------------------------------------------
// 0x649D30 CNAuraMasterIce__vmt0 —— CNAuraMasterIce__vmt0 析构（转发 649D60）
// ------------------------------------------------------------
void */*thiscall*/ CNAuraMasterIce__vmt0(void *Block, char pszArg2)  // CNAuraMasterIce__vmt0 析构（转发 649D60）
{
  sub_649D60();  // 冰光环析构成员（591190）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x649D60 sub_649D60 —— 冰光环析构成员（591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_649D60(uint32_t *this)  // 函数: 冰光环析构成员（591190）
{
  *this = &vftbl_CNAuraMasterIce;  // *this 写入 &vftbl_CNAuraMasterIce
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// ------------------------------------------------------------
// 0x649D70 CNIceDamageFromIceAura__vmt1C —— CNIceDamageFromIceAura__vmt1C 生成装配：IceAuraMinionSnowFlake.ptl / IceAuraMinionSteam.ptl（428F30/5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNIceDamageFromIceAura__vmt1C(int *this)  // 函数: CNIceDamageFromIceAura__vmt1C 生成装配：IceAuraMinionSnowFlake.ptl / IceAuraMinionSteam.ptl（428F30/5F66A0）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e1; // eax
  int pHostObj; // ecx  | +0x0004 → 宿主对象指针（0x649390 构造: *(this+18)=nArg3*0.5 半量；0x64A900 族更新槽）（CNIceDamageFromIceAura；va=0064A900）
  uint32_t *pMem2; // eax
  uint32_t *fld_e13; // eax
  int pHostObj_; // ecx  | +0x0004 → 宿主对象指针（0x649390 构造: *(this+18)=nArg3*0.5 半量；0x64A900 族更新槽）（CNIceDamageFromIceAura；va=0064A900）

  pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e1 = sub_428F30(pMem, (int)"Common/Etc/Particle/Aura/IceAuraMinionSnowFlake.ptl", *(this + 1));  // 字符串 “Common/Etc/Particle/Aura/IceAuraMinionSnowFl”
  else
    fld_e1 = nullptr;  // fld_e1 = nullptr 空指针
  pHostObj = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
  *(this + 25) = (int)fld_e1;  // this+100 = (int)fld_e1
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e1 + 112))(fld_e1, pHostObj);  // 虚调用 vt+112
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 25) + 12))(*(this + 25), 0);  // 调用虚函数槽 +12
  pMem2 = operator new(0x12Cu);  // 堆分配 300 字节对象
  if ( pMem2 != nullptr )  // 若 pMem2 非空
    fld_e13 = sub_428F30(pMem2, (int)"Common/Etc/Particle/Aura/IceAuraMinionSteam.ptl", *(this + 1));  // 字符串 “Common/Etc/Particle/Aura/IceAuraMinionSteam.”
  else
    fld_e13 = nullptr;  // fld_e13 = nullptr 空指针
  pHostObj_ = *(this + 1);  // 读 fld_e14 = this+4（宿主对象指针）
  *(this + 26) = (int)fld_e13;  // this+104 = (int)fld_e13
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e13 + 112))(fld_e13, pHostObj_);  // 虚调用 vt+112
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 26) + 12))(*(this + 26), 0);  // 调用虚函数槽 +12
  return sub_5F66A0((int)this, 1);  // 调 sub_5F66A0
}



// ------------------------------------------------------------
// 0x649E40 sub_649E40 —— 诅咒动画查询 2（5910D0 + 698F90）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_649E40(uint8_t *this, int nArg2, int nArg3, int nArg4)  // 诅咒动画查询 2（5910D0 + 698F90）
{
  sub_5910D0(nArg2, 18, 100, 0);  // CNRDAuraMaster 构造函数
  *(uint32_t *)this = &vftbl_CNAuraMasterCurse;
  *(this + 144) = 0;  // this+576 = 0
  *((uint32_t *)this + 35) = &vftbl_nengine__CNTimer;  // this+140 = &vftbl_nengine__CNTimer
  *((uint32_t *)this + 37) = 0;  // this+148 = 0
  *(this + 152) = 1;  // this+608 = 1
  *(this + 154) = 0;  // this+616 = 0
  *(this + 153) = 0;  // this+612 = 0
  *((uint32_t *)this + 41) = 0;  // this+164 = 0
  *((uint32_t *)this + 40) = 0;  // this+160 = 0
  *((uint32_t *)this + 39) = 0;  // this+156 = 0
  *((uint32_t *)this + 34) = nArg4;  // this+136 = nArg4
  *((uint32_t *)this + 33) = nArg3;  // this+132 = nArg3
  *(this + 153) = 0;  // this+612 = 0
  *(this + 154) = 0;  // this+616 = 0
  sub_698F90((int)(this + 140), 125, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint32_t *)this + 32) = 0;  // this+128 = 0
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x649EE0 sub_649EE0 —— 诅咒光环析构成员（591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_649EE0(uint32_t *this)  // 函数: 诅咒光环析构成员（591190）
{
  void (/*thiscall*/ ***fld_e32)(uint32_t, int); // ecx

  *this = &vftbl_CNAuraMasterCurse;  // *this 写入 &vftbl_CNAuraMasterCurse
  fld_e32 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 32);  // this+32 格子像素尺寸
  if ( fld_e32 != nullptr )  // 若 fld_e32 非空
    (**fld_e32)(fld_e32, 1);
  *(this + 32) = 0;  // this+128 = 0
  *(this + 35) = &vftbl_nengine__IObject;  // this+140 = &vftbl_nengine__IObject
  *((uint8_t *)this + 144) = 0;  // this+144 第 4 组·+1040 增量子倍率
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// ------------------------------------------------------------
// 0x649F60 CNAuraMasterCurse__vmt1C —— CNAuraMasterCurse__vmt1C 生成装配：Common/Etc/Particle/Aura/CurseAura.ptl（428F30/5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraMasterCurse__vmt1C(int *this)  // 函数: CNAuraMasterCurse__vmt1C 生成装配：Common/Etc/Particle/Aura/CurseAura.ptl（428F30/5F66A0）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e1; // eax

  CNRDAuraMaster__vmt1C();  // 调 CNRDAuraMaster__vmt1C 生成装配
  if ( *(this + 32) == 0 )  // 若 *(this + 32) == 0
  {
    pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
    if ( pMem != nullptr )  // 若 pMem 非空
      fld_e1 = sub_428F30(pMem, (int)"Common/Etc/Particle/Aura/CurseAura.ptl", *(this + 1));  // 字符串 “Common/Etc/Particle/Aura/CurseAura.ptl”
    else
      fld_e1 = nullptr;  // fld_e1 = nullptr 空指针
    *(this + 32) = (int)fld_e1;  // 写 this+128 = (int)fld_e1（诅咒动画件）
  }
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 32) + 112))(*(this + 32), *(this + 1));  // 调用虚函数槽 +112
  return sub_5F66A0((int)this, 1);  // 调 sub_5F66A0
}



// ------------------------------------------------------------
// 0x649FF0 sub_649FF0 —— 食尸鬼诅咒特效：挂 Monster/Ghoul/Particle/GhoulCurse.ptl（428F30/4600B0/698F90）
// ------------------------------------------------------------
void /*thiscall*/ sub_649FF0(int this)  // 函数: 食尸鬼诅咒特效：挂 Monster/Ghoul/Particle/GhoulCurse.ptl（428F30/4600B0/698F90）
{
  uint32_t *pMem; // eax
  uint32_t *fld_4; // eax
  int fld_43; // edi
  int fld_68; // ebx
  int v6; // eax
  int v7; // eax
  int *fld_44; // ecx
  int v9; // edx
  void *v10; // eax
  void *Block2; // eax
  int v12; // [esp-Ch] [ebp-38h]
  int fld_42; // [esp-4h] [ebp-30h]
  uint8_t v14[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *pMem2; // [esp+1Ch] [ebp-10h]
  int v17; // [esp+28h] [ebp-4h]

  if ( *(uint32_t *)(this + 104) == 0 )  // 若 *(uint32_t *)(this + 104) == 0
  {
    pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
    pMem2 = pMem;
    v17 = 0;
    if ( pMem != nullptr )  // 若 pMem 非空
      fld_4 = sub_428F30(pMem, (int)"Monster/Ghoul/Particle/GhoulCurse.ptl", *(uint32_t *)(this + 4));  // 字符串 “Monster/Ghoul/Particle/GhoulCurse.ptl”
    else
      fld_4 = nullptr;  // fld_4 = nullptr 空指针
    v17 = -1;
    *(uint32_t *)(this + 104) = fld_4;  // this+104 = fld_4
  }
  fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
  (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 104) + 112))(*(uint32_t *)(this + 104));  // 调用虚函数槽 +112
  (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 104) + 12))(*(uint32_t *)(this + 104));  // 调用虚函数槽 +12
  fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
  fld_68 = **(uint32_t **)(this + 104);  // this+104 插值终点 Z
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 128))(fld_43);  // 调用虚函数槽 +128
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 124))(fld_43);  // 调用虚函数槽 +124
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_43 + 120))(fld_43, v6);  // 调用虚函数槽 +120
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_68 + 40))(*(uint32_t *)(this + 104), v7);  // 调用虚函数槽 +40
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 104) + 92))(*(uint32_t *)(this + 104), v14);  // 调用虚函数槽 +92
  fld_44 = *(int **)(this + 4);  // this+4 宿主对象
  v9 = *fld_44;  // fld_44=this+4 宿主对象
  v17 = 1;
  v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v9 + 80))(fld_44, 2, 0, v14);  // fld_44=this+4 宿主对象
  sub_4600B0(v10, v12, 0, fld_42);  // 调 sub_4600B0
  *(uint8_t *)(this + 121) = 0;  // this+121 = 0
  *(uint8_t *)(this + 122) = 0;  // this+122 = 0
  sub_698F90(this + 108, 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  Block2 = Block;
  *(uint32_t *)(this + 136) = 1;  // this+136 = 1
  if ( Block2 != nullptr )  // 若 Block2 非空
    j__free(Block2);  // 调 j__free
}



// ------------------------------------------------------------
// 0x64A100 CNAuraMasterCurse__vmt0 —— CNAuraMasterCurse__vmt0 析构（转发 649EE0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNAuraMasterCurse__vmt0(uint32_t *Block, char pszArg2)  // CNAuraMasterCurse__vmt0 析构（转发 649EE0）
{
  sub_649EE0(Block);  // 诅咒光环析构成员（591190）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64A130 CNDarkDamageFromCurseAura__vmt68 —— CNDarkDamageFromCurseAura__vmt68 特效触发槽（转发 649FF0）
// ------------------------------------------------------------
void /*thiscall*/ CNDarkDamageFromCurseAura__vmt68(uint8_t *this)  // 函数: CNDarkDamageFromCurseAura__vmt68 特效触发槽（转发 649FF0）
{
  if ( *(this + 140) == 1 )  // 若 *(this + 140) == 1
  {
    sub_649FF0((int)this);  // 食尸鬼诅咒特效：挂 Monster/Ghoul/Particle/GhoulCurse.pt
    *(this + 140) = 0;  // 写 this+140 = 0（已触发标志）
  }
}



// ============================================================
// 【分区 11】光环基类 CNRDAuraMaster / CNRDAuraMinion（0x64A150-0x64A930）
// vmt18/vmt1C=生成（4938F0/491D00 + 64A3D0/64A5A0 装配）；vmt20/vmt30=
// 更新（41C5E0/52E4D0）；vmt4=析构复位；vmt80=受击入口（42AF90/657740）；
// vmt90=槽。64A3D0/64A5A0/64A680=召唤/跟随装配（4BE520 + 614810/6148D0）。
// ============================================================
// ------------------------------------------------------------
// 0x64A150 sub_64A150 —— 光环基类数据（14 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A150(int this)  // 函数: 光环基类数据（14 行）
{
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint8_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 124) = 0;  // this+124 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x64A160 sub_64A160 —— 光环基类数据 2（607260）
// ------------------------------------------------------------
char /*thiscall*/ sub_64A160(int this, int nArg2, int nArg3, int nArg4, char pszArg5)  // 函数: 光环基类数据 2（607260）
{
  *(uint32_t *)(this + 80) = nArg3;  // this+80 = nArg3
  *(uint32_t *)(this + 84) = nArg2;  // this+84 = nArg2
  sub_607260((uint32_t *)(this + 92), nArg4, -1, 1, 1);  // 计时参数写入
  *(uint8_t *)(this + 88) = pszArg5;  // this+88 = pszArg5
  return pszArg5;
}



// ------------------------------------------------------------
// 0x64A190 CNRDAuraMaster__vmt18 —— CNRDAuraMaster__vmt18 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMaster__vmt18(int this, char pszArg2, int nArg3, int nArg4, float fArg5)  // 函数: CNRDAuraMaster__vmt18 生成槽（4938F0/491D00）
{
  int fld_7C; // eax  | +0x007C → 光环动画件（CNRDAuraMaster；va=0064A190）

  fld_7C = *(uint32_t *)(this + 124);  // 读 fld_7C = this+124（光环动画件）
  if ( fld_7C != 0 )  // 若 fld_7C != 0
  {
    LOBYTE(fld_7C) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));  // this+4 pHostObj 等2字段
    if ( (uint8_t)fld_7C == 0 )  // 若 (uint8_t)fld_7C == 0
    {
      LOBYTE(fld_7C) = pszArg2;  // fld_7C=this+124 pAuraAnim
      if ( pszArg2 != 0 )  // 若 pszArg2 != 0
      {
        sub_4938F0(*(uint32_t *)(this + 124));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        LOBYTE(fld_7C) = sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
    }
  }
  return fld_7C;  // | +0x007C → 光环动画件（CNRDAuraMaster；va=0064A190）
}



// ------------------------------------------------------------
// 0x64A1E0 CNRDAuraMinion__vmt18 —— CNRDAuraMinion__vmt18 生成槽（4938F0/491D00）
// ------------------------------------------------------------
void /*thiscall*/ CNRDAuraMinion__vmt18(int *this, char pszArg2, int nArg3, int nArg4, float fArg5)  // 函数: CNRDAuraMinion__vmt18 生成槽（4938F0/491D00）
{
  int pFxObjA; // edi  | +0x0054 → 特效对象 A（0x64A300: 与 +88/+92 齐备为四槽判据之一）【推断】（CNRDAuraMinion；va=0064A300）
  int pFxObjB; // ecx  | +0x0058 → 特效对象 B（0x64A300 四槽判据之二）【推断】（CNRDAuraMinion；va=0064A300）
  int nAuraStage; // eax  | +0x0050 → 光环阶段值（0x64A300: ==2 时不再走 52 分支）（CNRDAuraMinion；va=0064A300）
  int v9; // eax

  pFxObjA = *(this + 21);  // 读 fld_e21 = this+84（特效对象 A）
  if ( pFxObjA != 0 )  // 若 fld_e21 != 0
  {
    pFxObjB = *(this + 22);  // 读 fld_e22 = this+88（特效对象 B）
    if ( pFxObjB != 0 && *(this + 23) != 0 && pszArg2 != 0 )  // 若 fld_e22 != 0 && *(this + 23) != 0 && pszArg2 != 0
    {
      nAuraStage = *(this + 20);  // 读 fld_e20 = this+80（光环阶段值）
      if ( nAuraStage != 0 )  // 若 fld_e20 != 0
      {
        v9 = nAuraStage - 1;  // fld_e20=this+80 nAuraStage
        if ( v9 != 0 )  // 若 v9 != 0
        {
          if ( v9 == 1 )  // 若 v9 == 1
          {
            sub_4938F0(*(this + 23));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
            sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          }
        }
        else
        {
          sub_4938F0(pFxObjA);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
          sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
      }
      else
      {
        sub_4938F0(pFxObjB);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64A2A0 CNRDAuraMinion__vmt4 —— CNRDAuraMinion__vmt4 复位槽（41 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMinion__vmt4(int *this)  // 函数: CNRDAuraMinion__vmt4 复位槽（41 行）
{
  int fld_e21; // eax  | +0x0054 → 特效对象 A（0x64A300: 与 +88/+92 齐备为四槽判据之一）【推断】（CNRDAuraMinion；va=0064A300）
  int pFxObjB; // edx  | +0x0058 → 特效对象 B（0x64A300 四槽判据之二）【推断】（CNRDAuraMinion；va=0064A300）
  int pFxObjC; // ecx  | +0x005C → 特效对象 C（0x64A300 四槽判据之三；0x64CD00 构造 *(this+25) 即本槽）【推断】（CNRDAuraMinion；va=0064A300）

  IRDAppendage__vmt4(this);
  fld_e21 = *(this + 21);  // 读 fld_e21 = this+84（特效对象 A）
  if ( fld_e21 != 0 )  // 若 fld_e21 != 0
  {
    pFxObjB = *(this + 22);  // 读 fld_e22 = this+88（特效对象 B）
    if ( pFxObjB != 0 )  // 若 fld_e22 != 0
    {
      pFxObjC = *(this + 23);  // 读 fld_e23 = this+92（特效对象 C）
      if ( pFxObjC != 0 )  // 若 fld_e23 != 0
      {
        fld_e21 = *(this + 20);  // 读 fld_e21 = this+80（光环阶段值）
        if ( fld_e21 != 0 || *(uint8_t *)(pFxObjB + 170) == 0 )  // 若 fld_e21 != 0 || *(uint8_t *)(fld_e22 + 170) == 0
        {
          if ( fld_e21 == 2 )  // 若 fld_e21 == 2
          {
            LOBYTE(fld_e21) = *(uint8_t *)(pFxObjC + 170);  // fld_e21=this+80 nAuraStage
            if ( (uint8_t)fld_e21 != 0 )  // 若 (uint8_t)fld_e21 != 0
              LOBYTE(fld_e21) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);  // 虚调用 vt+76
          }
        }
        else
        {
          *(this + 20) = 1;  // 写 this+80 = 1（光环阶段值）
        }
      }
    }
  }
  return fld_e21;  // | +0x0054 → 特效对象 A（0x64A300: 与 +88/+92 齐备为四槽判据之一）【推断】（CNRDAuraMinion；va=0064A300）
}



// ------------------------------------------------------------
// 0x64A300 CNRDAuraMinion__vmt4C —— CNRDAuraMinion__vmt4C 槽（28 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMinion__vmt4C(int this, char pszArg2)  // 函数: CNRDAuraMinion__vmt4C 槽（28 行）
{
  char result; // al

  result = pszArg2;
  if ( pszArg2 == 1 )  // 若 pszArg2 == 1
  {
    *(uint8_t *)(this + 52) = 1;  // 写 this+52 = 1（光环状态字节）
  }
  else if ( *(uint32_t *)(this + 84) != 0  // 判定 “+84 特效对象 A”
         && *(uint32_t *)(this + 88) != 0  // this+88 pFxObjB
         && *(uint32_t *)(this + 92) != 0  // this+92 pFxObjC
         && *(uint32_t *)(this + 80) != 2 )  // CNRDAuraMinion__vmt4C 槽（28 行）
  {
    *(uint32_t *)(this + 80) = 2;  // 写 this+80 = 2（光环阶段值）
  }
  else
  {
    *(uint8_t *)(this + 52) = pszArg2;  // 写 this+52 = pszArg2（光环状态字节）
  }
  return result;
}



// ------------------------------------------------------------
// 0x64A350 sub_64A350 —— 受方表现转发（14 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A350(uint32_t *this)  // 函数: 受方表现转发（14 行）
{
  *(this + 20) = 0;  // this+80 = 0
  *(this + 23) = 0;  // this+92 = 0
  *(this + 22) = 0;  // this+88 = 0
  *(this + 21) = 0;  // this+84 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x64A360 CNRDAuraMaster__vmt20 —— CNRDAuraMaster__vmt20 更新槽（41C5E0 + 52E4D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDAuraMaster__vmt20(uint32_t *this, uint32_t *uArg2)  // CNRDAuraMaster__vmt20 更新槽（41C5E0 + 52E4D0）
{
  uint32_t *fld_e29; // ecx
  uint32_t *uArg22; // eax
  void **fld_e292; // edx
  uint32_t *pThis_1C; // esi
  uint32_t *result; // eax

  if ( (uint8_t)uArg2 == 0 )  // 若 (uint8_t)uArg2 == 0
  {
    fld_e29 = (uint32_t *)*(this + 29);  // this+29 pSessionCtx
    uArg22 = (uint32_t *)*fld_e29;
    uArg2 = (uint32_t *)*fld_e29;
    if ( uArg2 != fld_e29 )  // 若 uArg2 != fld_e29
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, uArg22[4]);  // 虚调用 vt+124
        sub_41C5E0(&uArg2);  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
        uArg22 = uArg2;
      }
      while ( uArg2 != (uint32_t *)*(this + 29) );  // 当 uArg2 != (uint32_t *)*(this + 29) 循环
    }
  }
  fld_e292 = *(void ***)(*(this + 29) + 4);  // this+29 pSessionCtx
  pThis_1C = this + 28;  // this+28 逐帧驱动对象
  sub_52E4D0(fld_e292);  // 调 sub_52E4D0
  *(uint32_t *)(pThis_1C[1] + 4) = pThis_1C[1];  // pThis_1C=this+28 逐帧驱动对象
  result = (uint32_t *)pThis_1C[1];  // pThis_1C=this+28 逐帧驱动对象
  pThis_1C[2] = 0;  // pThis_1C=this+28 逐帧驱动对象
  *result = result;  // *result 写入 result
  *(uint32_t *)(pThis_1C[1] + 8) = pThis_1C[1];  // pThis_1C=this+28 逐帧驱动对象
  return result;
}



// ------------------------------------------------------------
// 0x64A3D0 sub_64A3D0 —— 召唤装配（4BE520 + 614810，117 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_64A3D0(uint8_t *this, int nArg2)  // 函数: 召唤装配（4BE520 + 614810，117 行）
{
  uint32_t *pThis; // ebx
  bool fld_e88; // zf
  uint32_t *v4; // eax
  int nArg22; // esi
  uint32_t *v6; // eax
  int pObj2; // edi
  unsigned int v8; // ebx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int pObj; // esi
  uint8_t v19[8]; // [esp+Ch] [ebp-1Ch] BYREF
  int nArg23; // [esp+14h] [ebp-14h] BYREF
  int nArg24; // [esp+18h] [ebp-10h] BYREF
  uint8_t v22[4]; // [esp+1Ch] [ebp-Ch] BYREF
  uint32_t *pThis2; // [esp+20h] [ebp-8h] BYREF
  char v24; // [esp+27h] [ebp-1h]

  pThis = this;
  fld_e88 = *(this + 88) == 0;  // this+88 插值起点 Y
  pThis2 = this;
  if ( fld_e88 )  // 若 fld_e88
  {
    v4 = (uint32_t *)sub_4BE520(&pThis2, &nArg2);  // 结果 = 映射下界查找（lower_bound）
    if ( *v4 == pThis[29] )  // 若 *v4 == pThis[29]
    {
      nArg22 = nArg2;
      nArg23 = nArg2;
      nArg24 = nArg2;
      sub_614810(v22, &nArg23);  // 调 sub_614810
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pThis + 120))(pThis, nArg22);  // 虚调用 vt+120
    }
    return (char)v4;
  }
  v6 = (uint32_t *)sub_4BE520(&nArg24, &nArg2);  // 结果 = 映射下界查找（lower_bound）
  pObj2 = nArg2;
  if ( *v6 == pThis[29] )  // 若 *v6 == pThis[29]
  {
    nArg23 = nArg2;
    nArg24 = nArg2;
    sub_614810(v19, &nArg23);  // 调 sub_614810
  }
  HIBYTE(nArg2) = 0;
  v24 = 0;
  if ( pObj2 == 0 )  // 若 pObj2 == 0
  {
LABEL_31:
    LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pThis + 120))(pThis, pObj2);  // 虚调用 vt+120
    return (char)v4;
  }
  v8 = 0;
  while ( 1 )  // 当 1 循环
  {
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 700))(pObj2);  // 调用虚函数槽 +700
    v10 = *(uint32_t *)(v9 + 4);  // v10 = v9+4
    v11 = v10 != 0 ? (*(uint32_t *)(v9 + 8) - v10) >> 2 : 0;
    if ( (int)v8 >= v11 )  // 若 (int)v8 >= v11
      break;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 700))(pObj2);  // 调用虚函数槽 +700
    v13 = *(uint32_t *)(v12 + 4);  // v13 = v12+4
    if ( v13 != 0 && v8 < (*(uint32_t *)(v12 + 8) - v13) >> 2 )  // 若 v13 != 0 && v8 < (*(uint32_t *)(v12 + 8) - v13) >> 2
      v14 = *(uint32_t *)(v13 + 4 * v8);
    else
      v14 = 0;
    if ( *(uint32_t *)(v14 + 4) == pObj2
      && (v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 700))(pObj2), (v16 = *(uint32_t *)(v15 + 4)) != 0)  // 召唤装配（4BE520 + 614810，117 行）
      && v8 < (*(uint32_t *)(v15 + 8) - v16) >> 2
      && (pObj = *(uint32_t *)(v16 + 4 * v8)) != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pObj + 80))(*(uint32_t *)(v16 + 4 * v8)) != 0  // 虚槽+80 CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis2 + 136))(pThis2, pObj) != 0 )  // 虚调用 vt+136
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis2 + 144))(pThis2, pObj) != 0 )  // 虚调用 vt+144
      {
        HIBYTE(nArg2) = 1;
        ++v8;  // 自增v8
      }
      else
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis2 + 140))(pThis2, pObj) == 0 )  // 虚调用 vt+140
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 调用虚函数槽 +76
          goto LABEL_27;  // 跳转 LABEL_27
        }
        v24 = 1;
        ++v8;  // 自增v8
      }
    }
    else
    {
LABEL_27:
      ++v8;  // 自增v8
    }
  }
  LOBYTE(v4) = HIBYTE(nArg2);
  if ( HIBYTE(nArg2) == 0 )  // 若 HIBYTE(nArg2) == 0
  {
    LOBYTE(v4) = v24;
    if ( v24 == 0 )  // 若 v24 == 0
    {
      pThis = pThis2;
      goto LABEL_31;  // 跳转 LABEL_31
    }
  }
  return (char)v4;
}


// ------------------------------------------------------------
// 0x64A570 CNRDAuraMaster__vmt1C —— CNRDAuraMaster__vmt1C 生成装配（699000 + 607290 + 64A3D0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMaster__vmt1C(int this)  // 函数: CNRDAuraMaster__vmt1C 生成装配（699000 + 607290 + 64A3D0）
{
  int pThis_8; // eax
  int fld_50; // eax  | +0x0050 → 光环标志组（CNRDAuraMaster；va=0064A570）

  pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
  sub_607290((uint8_t *)(this + 92), pThis_8);  // 首帧基准记录
  fld_50 = *(uint32_t *)(this + 80) >> 5;  // this+80 nAuraFlags
  if ( (*(uint32_t *)(this + 80) & 0x20) != 0 )  // 判定 “+80 光环标志组”
    LOBYTE(fld_50) = sub_64A3D0((int **)this, *(uint32_t *)(this + 4));  // 召唤装配
  return fld_50;  // | +0x0050 → 光环标志组（CNRDAuraMaster；va=0064A570）
}



// ------------------------------------------------------------
// 0x64A5A0 sub_64A5A0 —— 跟随装配（4BE520 + 6148D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64A5A0(uint32_t *this, int nArg2)  // 跟随装配（4BE520 + 6148D0）
{
  uint32_t *pThis_1C; // edi
  uint32_t *result; // eax
  uint8_t v5[4]; // [esp+8h] [ebp-4h] BYREF

  pThis_1C = this + 28;  // this+28 逐帧驱动对象
  result = (uint32_t *)sub_4BE520(v5, &nArg2);  // 结果 = 映射下界查找（lower_bound）
  if ( *result != *(this + 29) )  // 若 *result != *(this + 29)
  {
    sub_6148D0(pThis_1C, &nArg2);  // 调 sub_6148D0
    return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nArg2);  // 虚调用 vt+124
  }
  return result;
}



// ------------------------------------------------------------
// 0x64A5E0 CNRDAuraMaster__vmt30 —— CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDAuraMaster__vmt30(uint32_t *this, uint32_t *pArg2)  // 函数: CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0）
{
  int v2; // ebx
  uint32_t *fld_e29; // ecx
  uint32_t *pArg22; // eax
  uint32_t *fld_e292; // eax

  v2 = (int)pArg2;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) == 0 )  // 虚调用 vt+40
    return IRDAppendage__vmt30(this, v2);
  if ( v2 != *(this + 1) )  // 判定 “+4 宿主对象指针”
  {
    sub_64A5A0(this, v2);  // 跟随装配（4BE520 + 6148D0）
    return IRDAppendage__vmt30(this, v2);
  }
  fld_e29 = (uint32_t *)*(this + 29);  // this+29 pSessionCtx
  pArg22 = (uint32_t *)*fld_e29;
  pArg2 = (uint32_t *)*fld_e29;
  if ( pArg2 != fld_e29 )  // 若 pArg2 != fld_e29
  {
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, pArg22[4]);  // 虚调用 vt+124
      sub_41C5E0(&pArg2);  // 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
      pArg22 = pArg2;
    }
    while ( pArg2 != (uint32_t *)*(this + 29) );  // 当 pArg2 != (uint32_t *)*(this + 29) 循环
  }
  sub_52E4D0(*(void ***)(*(this + 29) + 4));  // 调 sub_52E4D0
  *(uint32_t *)(*(this + 29) + 4) = *(this + 29);  // this+29 pSessionCtx 等2字段
  fld_e292 = (uint32_t *)*(this + 29);  // this+29 pSessionCtx
  *(this + 30) = 0;  // this+120 = 0
  *fld_e292 = fld_e292;  // *fld_e292 写入 fld_e292
  *(uint32_t *)(*(this + 29) + 8) = *(this + 29);  // this+29 pSessionCtx 等2字段
  return IRDAppendage__vmt30(this, v2);
}



// ------------------------------------------------------------
// 0x64A680 sub_64A680 —— 跟随装配 2（699000 + 6072C0 + 64A5A0/64A3D0，73 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_64A680(int this)  // 函数: 跟随装配 2（699000 + 6072C0 + 64A5A0/64A3D0，73 行）
{
  signed int fld_50; // eax
  int pThis_8; // eax
  int fld_4; // eax
  unsigned int v5; // edx
  int fld_42; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int pObj; // esi
  unsigned int i; // [esp+4h] [ebp-4h]

  fld_50 = *(uint32_t *)(this + 80) >> 4;  // this+80 关联角色对象
  if ( (*(uint32_t *)(this + 80) & 0x10) != 0 )  // 若 (*(uint32_t *)(this + 80) & 0x10) != 0
  {
    pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
    LOBYTE(fld_50) = sub_6072C0((uint8_t *)(this + 92), pThis_8);  // 调 子弹静态辅助（33 行，无外部调用）——(推断：枪种/弹种参数快查表)
    if ( (uint8_t)fld_50 != 0 )  // 若 (uint8_t)fld_50 != 0
    {
      fld_4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +80
      v5 = 0;
      fld_42 = fld_4;
      for ( i = 0; ; v5 = i )  // 循环：i = 0; ; v5 = i
      {
        while ( 1 )  // 当 1 循环
        {
          v7 = *(uint32_t *)(fld_42 + 120);  // v7 = fld_42+120
          if ( v7 != 0 )  // 若 v7 != 0
            fld_50 = (*(uint32_t *)(fld_42 + 124) - v7) >> 2;
          else
            fld_50 = 0;
          if ( (int)v5 >= fld_50 )  // 若 (int)v5 >= fld_50
            return fld_50;
          v8 = *(uint32_t *)(fld_42 + 120);  // v8 = fld_42+120
          if ( v8 != 0 && v5 < (*(uint32_t *)(fld_42 + 124) - v8) >> 2 )  // 若 v8 != 0 && v5 < (*(uint32_t *)(fld_42 + 124) - v8) >> 2
            v9 = *(uint32_t *)(v8 + 4 * v5);
          else
            v9 = 0;
          v10 = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                  v9,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDActiveObject `RTTI Type Descriptor',
                  0);
          pObj = v10;
          if ( v10 != 0 )  // 若 v10 != 0
            break;
LABEL_20:
          v5 = ++i;
        }
        if ( *(uint32_t *)(this + 4) == v10 && (*(uint32_t *)(this + 80) & 2) != 0  // this+4 宿主对象 等2字段
          || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 132))(this, v10) == 0  // this+132 第 3 组·+60 增量项
          || (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t))(**(uint32_t **)(this + 4) + 8))(*(uint32_t *)(this + 4), pObj, 0) > *(uint32_t *)(this + 84)  // 跟随装配 2（699000 + 6072C0 + 64A5A0/64A3D0，73 行）
          || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) != 0 )
        {
          sub_64A5A0((uint32_t *)this, pObj);  // 跟随装配（4BE520 + 6148D0）
          goto LABEL_20;  // 跳转 LABEL_20
        }
        sub_64A3D0((int **)this, pObj);  // 召唤装配
        ++i;  // 自增i
      }
    }
  }
  return fld_50;
}



// ------------------------------------------------------------
// 0x64A790 CNRDAuraMaster__vmt4 —— CNRDAuraMaster__vmt4 析构复位（转发 64A680）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMaster__vmt4(int this)  // 函数: CNRDAuraMaster__vmt4 析构复位（转发 64A680）
{
  IRDAppendage__vmt4((int *)this);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 724))(*(uint32_t *)(this + 4)) != 0 )  // 判定 “+4 宿主对象指针”
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 76))(this, 0);  // 调用虚函数槽 +76
  return sub_64A680(this);  // 跟随装配 2
}



// ------------------------------------------------------------
// 0x64A7C0 sub_64A7C0 —— 受击前置（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A7C0(void ***this)  // 函数: 受击前置（42AF90/657740）
{
  int fld_e31; // esi
  int result; // eax

  fld_e31 = (int)*(this + 31);
  if ( fld_e31 != 0 )  // 若 fld_e31 != 0
  {
    sub_42AF90(*(this + 31));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e31, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 31) = nullptr;  // this+124 = nullptr
  return result;
}



// ------------------------------------------------------------
// 0x64A7F0 CNRDAuraMaster__vmt80 —— CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
// ------------------------------------------------------------
int /*thiscall*/ CNRDAuraMaster__vmt80(void ***this, const char *pArg2)  // 函数: CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
{
  int pAuraAnim; // edi  | +0x007C → 光环动画件（CNRDAuraMaster；va=0064A190）
  int v4; // eax
  int result; // eax

  pAuraAnim = (int)*(this + 31);
  if ( pAuraAnim != 0 )  // 若 fld_e31 != 0
  {
    sub_42AF90(*(this + 31));  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(pAuraAnim, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 31) = nullptr;  // 写 this+124 = nullptr（光环动画件）
  v4 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v4 != 0 )  // 若 v4 != 0
    result = sub_431860(v4, pArg2, 1);  // 结果 = 动画件构造（资源 id 版）
  else
    result = 0;
  *(this + 31) = (void **)result;  // 写 this+124 = (void **)result（光环动画件）
  return result;
}



// ------------------------------------------------------------
// 0x64A880 sub_64A880 —— 受击表现（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A880(void ***this)  // 函数: 受击表现（42AF90/657740）
{
  int fld_e21; // edi
  int result; // eax
  void **fld_e22; // edi
  void **fld_e23; // edi

  fld_e21 = (int)*(this + 21);  // this+21 霸体状态字节
  if ( fld_e21 != 0 )  // 若 fld_e21 != 0
  {
    sub_42AF90(*(this + 21));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e21, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_e22 = *(this + 22);  // fld_e22 = this+22
  *(this + 21) = nullptr;  // this+84 = nullptr
  if ( fld_e22 != nullptr )  // 若 fld_e22 非空
  {
    sub_42AF90(fld_e22);  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e22, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_e23 = *(this + 23);  // fld_e23 = this+23
  *(this + 22) = nullptr;  // this+88 = nullptr
  if ( fld_e23 != nullptr )  // 若 fld_e23 非空
  {
    sub_42AF90(fld_e23);  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e23, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 23) = nullptr;  // this+92 = nullptr
  return result;
}



// ------------------------------------------------------------
// 0x64A900 CNRDAuraMinion__vmt30 —— CNRDAuraMinion__vmt30 更新槽（转发 64A880）
// ------------------------------------------------------------
int /*thiscall*/ CNRDAuraMinion__vmt30(int this, int nArg2)  // 函数: CNRDAuraMinion__vmt30 更新槽（转发 64A880）
{
  if ( nArg2 == *(uint32_t *)(this + 4) )  // 判定 “+4 宿主对象指针”
    sub_64A880((void ***)this);  // 受击表现（42AF90/657740）
  return IRDAppendage__vmt30((uint32_t *)this, nArg2);
}



// ============================================================
// 【分区 12】挑衅人偶光环 CNProvocationDollAura（0x64A930-0x64AEC0）
// 64AD30 装载 Character/Mage/Effect/Animation/ProvocationDollSymbol1/2.ani +
// ProvocationDollAreaStart/Loop.ani；vmt78=嘲讽生效（433F60/4B3DF0/60FA60）。
// ============================================================
// ------------------------------------------------------------
// 0x64A930 sub_64A930 —— 挑衅查询（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A930(uint32_t *this)  // 函数: 挑衅查询（16 行）
{
  *(this + 32) = 0;  // this+128 = 0
  *(this + 33) = 1065353216;  // this+132 = 1065353216
  *(this + 34) = 0;  // this+136 = 0
  *(this + 36) = 0;  // this+144 = 0
  *(this + 35) = 0;  // this+140 = 0
  *(this + 37) = 0;  // this+148 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x64A960 CNProvocationDollAura__vmt1C —— CNProvocationDollAura__vmt1C 生成装配（4926A0/4922F0 嘲讽目标）
// ------------------------------------------------------------
int /*thiscall*/ CNProvocationDollAura__vmt1C(int *this)  // 函数: CNProvocationDollAura__vmt1C 生成装配（4926A0/4922F0 嘲讽目标）
{
  double fld_e21; // st7
  int *pThis_24; // esi
  int v4; // ebx
  double v5; // st7
  int result; // eax
  float v7; // [esp+Ch] [ebp-4h]

  CNRDAuraMaster__vmt1C((int)this);  // 调 CNRDAuraMaster__vmt1C 生成装配
  fld_e21 = (double)*(this + 21);  // this+21 霸体状态字节
  pThis_24 = this + 36;  // this+36 物品状态字
  v4 = 2;
  v5 = fld_e21 * 0.0062500001;
  v7 = v5 / *((float *)pThis_24 - 3);  // pThis_24=this+36 物品状态字
  *((float *)pThis_24 - 3) = v5;  // pThis_24=this+36 物品状态字
  do
  {
    sub_4926A0(*(pThis_24 - 2));  // 帧游标复位（+44 帧数组；递归子链 +204）
    sub_4926A0(*pThis_24);  // 帧游标复位（+44 帧数组；递归子链 +204）
    sub_4922F0(v7);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    result = sub_4922F0(v7);  // 结果 = 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    ++pThis_24;  // 自增pThis_24
    --v4;  // 自减v4
  }
  while ( v4 != 0 );  // 当 v4 != 0 循环
  return result;
}



// ------------------------------------------------------------
// 0x64A9C0 CNProvocationDollAura__vmt84 —— CNProvocationDollAura__vmt84 受击事件槽（4E4630）
// ------------------------------------------------------------
char /*stdcall*/ CNProvocationDollAura__vmt84(int nArg1)  // 函数: CNProvocationDollAura__vmt84 受击事件槽（4E4630）
{
  char result; // al

  result = sub_4E4630(nArg1);  // 调 敌我关系判定辅助
  if ( result != 0 )  // 若 result != 0
    return (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 724))(nArg1) == 0;  // 虚槽+724 读 +6552 霸体字节
  return result;
}



// ------------------------------------------------------------
// 0x64A9F0 CNProvocationDollAura__vmt94 —— CNProvocationDollAura__vmt94 槽（12 行）
// ------------------------------------------------------------
int /*thiscall*/ CNProvocationDollAura__vmt94(uint32_t *this, int nArg2, int nArg3)  // 函数: CNProvocationDollAura__vmt94 槽（12 行）
{
  *(this + 21) = nArg2;  // this+84 = nArg2
  *(this + 32) = nArg3;  // this+128 = nArg3
  return nArg2;
}



// ------------------------------------------------------------
// 0x64AA10 CNProvocationDollAura__vmt18 —— CNProvocationDollAura__vmt18 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNProvocationDollAura__vmt18(int *this, char pszArg2, int nArg3, int nArg4, float fArg5)  // 函数: CNProvocationDollAura__vmt18 生成槽（4938F0/491D00）
{
  char result; // al
  int *pThis_22; // esi
  int i; // [esp+10h] [ebp+8h]

  CNRDAuraMaster__vmt18((int)this, pszArg2, nArg3, nArg4, fArg5);  // 调 CNRDAuraMaster__vmt18 生成槽
  result = pszArg2;
  if ( pszArg2 != 0 )  // 若 pszArg2 != 0
  {
    pThis_22 = this + 34;
    for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
    {
      sub_4938F0(*pThis_22);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_491D00(dword_79C0B0, nArg3, nArg4, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      ++pThis_22;  // 自增pThis_22
    }
    sub_4938F0(*(this + (*(uint8_t *)(*(this + 36) + 170) != 0) + 36));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    return sub_491D00(dword_79C0B0, nArg3, nArg4, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  }
  return result;
}



// ------------------------------------------------------------
// 0x64AAB0 CNProvocationDollAura__vmt88 —— CNProvocationDollAura__vmt88 槽（10 行）
// ------------------------------------------------------------
BOOL /*stdcall*/ CNProvocationDollAura__vmt88(int pArg1)  // 函数: CNProvocationDollAura__vmt88 槽（10 行）
{
  return *(uint32_t *)(pArg1 + 64) == 15;
}



// ------------------------------------------------------------
// 0x64AAD0 CNProvocationDollAura__vmt8C —— CNProvocationDollAura__vmt8C 槽（17 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNProvocationDollAura__vmt8C(uint32_t **this, int nArg2)  // 函数: CNProvocationDollAura__vmt8C 槽（17 行）
{
  int pObj; // esi
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（CNProvocationDollAura；va=0064A790）

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 64))(nArg2) + 32) == 0 )  // 虚槽+64 CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/4015C0/45A340
    return false;
  pObj = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 64))(nArg2) + 32);  // 虚槽+64 CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/4015C0/45A340
  pHostObj = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 388))(*(this + 1));  // 调用虚函数槽 +388
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 388))(pObj) >= pHostObj;  // 虚槽+388 属性块（vt+672(3)）首 DWORD
}



// ------------------------------------------------------------
// 0x64AB20 CNRDAuraMaster__vmt90 —— CNRDAuraMaster__vmt90 槽（13 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNRDAuraMaster__vmt90(uint32_t *this, int nArg2)  // 函数: CNRDAuraMaster__vmt90 槽（13 行）
{
  int pHostObj; // esi  | +0x0004 → 宿主对象指针（CNRDAuraMaster；va=0064A790）

  pHostObj = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  return *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 64))(nArg2) + 32) == pHostObj;  // pHostObj=this+4 pHostObj
}



// ------------------------------------------------------------
// 0x64AB40 CNProvocationDollAura__vmt7C —— CNProvocationDollAura__vmt7C 光环失效/转移槽（62 行）
// ------------------------------------------------------------
void /*thiscall*/ CNProvocationDollAura__vmt7C(uint32_t *this, int nArg2)  // 函数: CNProvocationDollAura__vmt7C 光环失效/转移槽（62 行）
{
  unsigned int i; // edi
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int pObj; // ecx
  int pHostObj; // ebx  | +0x0004 → 宿主对象指针（CNProvocationDollAura；va=0064A790）
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx

  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v4 = *(uint32_t *)(v3 + 4);  // v4 = v3+4
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )  // 若 (int)i >= v5
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v7 = *(uint32_t *)(v6 + 4);  // v7 = v6+4
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )  // 若 v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == nArg2 )  // 若 *(uint32_t *)(v8 + 4) == nArg2
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
        v10 = *(uint32_t *)(v9 + 4);  // v10 = v9+4
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )  // 若 v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2
          pObj = *(uint32_t *)(v10 + 4 * i);
        else
          pObj = 0;
        pHostObj = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 32) == pHostObj )  // pHostObj=this+4 pHostObj
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
          v14 = *(uint32_t *)(v13 + 4);  // v14 = v13+4
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )  // 若 v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2
          {
            v15 = *(uint32_t **)(v14 + 4 * i);
            if ( v15 != nullptr && v15[16] == 15 )  // 若 v15 != nullptr && v15[16] == 15
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v15 + 76))(v15, 0);  // 虚调用 vt+76
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64AC30 CNProvocationDollAura__vmt78 —— CNProvocationDollAura__vmt78 嘲讽生效（433F60/4B3DF0/60FA60，60 行）
// ------------------------------------------------------------
int /*thiscall*/ CNProvocationDollAura__vmt78(uint32_t *this, uint32_t *Block)  // 函数: CNProvocationDollAura__vmt78 嘲讽生效（433F60/4B3DF0/60FA60，60 行）
{
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int result; // eax
  uint32_t *pMem2; // eax
  uint32_t *v7; // eax
  int v8; // [esp+0h] [ebp-24h]
  float fld_e32; // [esp+14h] [ebp-10h]
  int v10; // [esp+14h] [ebp-10h]

  fld_e32 = (float)(int)*(this + 32);  // this+32 格子像素尺寸
  v10 = (uint64_t)(fld_e32 / sub_433F60((int)Block, 1));  // 调 调 PVP 平衡系数路由（研究第 17/27 轮）
  pMem = operator new(0x7Cu);  // 堆分配 124 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
  {
    *(float *)&v8 = (float)v10;
    v4 = sub_4B3DF0(pMem, 26, 0, v8, 0, 6);  // 结果 = CNChangeStatus 构造（六参）
  }
  else
  {
    v4 = nullptr;  // v4 = nullptr 空指针
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int, int))(*v4 + 56))(  // 虚调用 vt+56
    v4,
    Block,
    *(this + 1),
    0,
    0,
    15,
    -1);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*Block + 40))(Block, 529);  // 结果 = 虚调用 vt+40
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    result = Block[1943];
    if ( result == 0 )  // 若 result == 0
    {
      pMem2 = operator new(0x54u);  // 堆分配 84 字节对象
      if ( pMem2 != nullptr )  // 若 pMem2 非空
        v7 = sub_60FA60(pMem2, 0, 0);  // 结果 = CNProvocationed 构造（IRDAppendage 基类 + 两参转发）
      else
        v7 = nullptr;  // v7 = nullptr 空指针
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int, int))(*v7 + 56))(  // 虚调用 vt+56
               v7,
               Block,
               *(this + 1),
               0,
               0,
               15,
               -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x64AD30 sub_64AD30 —— 装载 ProvocationDollSymbol1/2.ani + ProvocationDollAreaStart/Loop.ani（42FCB0/431860）
// ------------------------------------------------------------
int /*thiscall*/ sub_64AD30(uint32_t *this, int nArg2, int nArg3)  // 函数: 装载 ProvocationDollSymbol1/2.ani + ProvocationDollAreaStart/Loop.ani（42FCB0/431860）
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax

  v4 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v4 != 0 )  // 若 v4 != 0
    v5 = sub_431860(v4, "Character/Mage/Effect/Animation/ProvocationDollSymbol1.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/ProvocationD”
  else
    v5 = 0;
  *(this + 34) = v5;  // this+136 = v5
  v6 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v6 != 0 )  // 若 v6 != 0
    v7 = sub_431860(v6, "Character/Mage/Effect/Animation/ProvocationDollSymbol2.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/ProvocationD”
  else
    v7 = 0;
  *(this + 35) = v7;  // this+140 = v7
  v8 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v8 != 0 )  // 若 v8 != 0
    v9 = sub_431860(v8, "Character/Mage/Effect/Animation/ProvocationDollAreaStart.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/ProvocationD”
  else
    v9 = 0;
  *(this + 36) = v9;  // this+144 = v9
  v10 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v10 != 0 )  // 若 v10 != 0
    v11 = sub_431860(v10, "Character/Mage/Effect/Animation/ProvocationDollAreaLoop.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/ProvocationD”
  else
    v11 = 0;
  *(this + 37) = v11;  // this+148 = v11
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 148))(this, nArg2, nArg3);  // 虚调用 vt+148
}



// ------------------------------------------------------------
// 0x64AE50 sub_64AE50 —— 受击表现 2（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64AE50(void ***this)  // 函数: 受击表现 2（42AF90/657740）
{
  void ***pThis_24; // esi
  int i; // ebx
  int v3; // edi
  int result; // eax
  void **v5; // edi
  bool v6; // zf

  pThis_24 = this + 36;  // this+36 物品状态字
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    v3 = (int)*(pThis_24 - 2);  // pThis_24=this+36 物品状态字
    if ( v3 != 0 )  // 若 v3 != 0
    {
      sub_42AF90(*(pThis_24 - 2));  // 帧对象析构（帧数组 + 元素数组）
      result = sub_657740(v3, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
    }
    v5 = *pThis_24;  // pThis_24=this+36 物品状态字
    v6 = *pThis_24 == nullptr;  // pThis_24=this+36 物品状态字
    *(pThis_24 - 2) = nullptr;  // pThis_24=this+36 物品状态字
    if ( !v6 )  // 若 !v6
    {
      sub_42AF90(v5);  // 帧对象析构（帧数组 + 元素数组）
      result = sub_657740(v5, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_24++ = nullptr;  // *pThis_24++ 写入 nullptr
  }
  return result;
}



// ============================================================
// 【分区 13】冰冷光环变体 CNAuraMasterChilling + 变化状态王（0x64AEC0-0x64B6C0）
// vmt78/vmt7C=生效/失效（41A5E0/41A590 粒子挂载）；
// 64B0F0 动画装载 "%s.ani"/"%sDamage.ani" 模板；
// CNAuraChangeStatusMaster(+SpikeKing) vmt84/vmt7C/vmt78（5F8000/5101B0）。
// ============================================================
// ------------------------------------------------------------
// 0x64AEC0 j_CNRDAuraMaster__vmt1C —— j_CNRDAuraMaster__vmt1C 尾调用桩（11 行）
// ------------------------------------------------------------
// attributes: thunk
char /*thiscall*/ j_CNRDAuraMaster__vmt1C(int this)  // 函数: j_CNRDAuraMaster__vmt1C 尾调用桩（11 行）
{
  return CNRDAuraMaster__vmt1C(this);
}



// ------------------------------------------------------------
// 0x64AED0 CNAuraMasterChilling__vmt20 —— CNAuraMasterChilling__vmt20 更新槽（10 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNAuraMasterChilling__vmt20(uint32_t *this, uint32_t *uArg2)  // CNAuraMasterChilling__vmt20 更新槽（10 行）
{
  return CNRDAuraMaster__vmt20(this, uArg2);
}



// ------------------------------------------------------------
// 0x64AEE0 CNAuraMasterChilling__vmt78 —— CNAuraMasterChilling__vmt78 光环生效（41A5E0/41A590 粒子挂载）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterChilling__vmt78(int this, int nArg2)  // 函数: CNAuraMasterChilling__vmt78 光环生效（41A5E0/41A590 粒子挂载）
{
  unsigned int pHostObj; // edi  | +0x0004 → 宿主对象指针（CNAuraMasterChilling；va=0064A790）
  int v4; // edx
  unsigned int fld_42; // edi  | +0x0004 → 宿主对象指针（CNAuraMasterChilling；va=0064A790）
  int v6; // edx
  float fChillPct; // [esp+8h] [ebp-8h]  | +0x0080 → 冰冷百分比（CNAuraMasterChilling；va=0064AEE0）
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+8h] [ebp-8h]
  float fld_802; // [esp+Ch] [ebp-4h]  | +0x0080 → 冰冷百分比（CNAuraMasterChilling；va=0064AEE0）

  fChillPct = *(float *)(this + 128) - 1.0;  // this+128 fChillPct
  pHostObj = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 158;  // this+4 pHostObj 等2字段
  *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pHostObj)) + fChillPct;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pHostObj, v4, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_802 = *(float *)(this + 128) - 1.0;  // this+128 fChillPct
  fld_42 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 102;  // this+4 pHostObj 等2字段
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(fld_42)) + fld_802;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(fld_42, v6, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 676))(*(uint32_t *)(this + 4), 0);  // 调用虚函数槽 +676
}



// ------------------------------------------------------------
// 0x64AF80 CNAuraMasterChilling__vmt7C —— CNAuraMasterChilling__vmt7C 光环失效（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterChilling__vmt7C(int this, int nArg2)  // 函数: CNAuraMasterChilling__vmt7C 光环失效（41A5E0/41A590）
{
  unsigned int pHostObj; // edi  | +0x0004 → 宿主对象指针（CNAuraMasterChilling；va=0064A790）
  int v4; // edx
  unsigned int fld_42; // edi  | +0x0004 → 宿主对象指针（CNAuraMasterChilling；va=0064A790）
  int v6; // edx
  float fChillPct; // [esp+8h] [ebp-8h]  | +0x0080 → 冰冷百分比（CNAuraMasterChilling；va=0064AEE0）
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+8h] [ebp-8h]
  float fld_802; // [esp+Ch] [ebp-4h]  | +0x0080 → 冰冷百分比（CNAuraMasterChilling；va=0064AEE0）

  fChillPct = *(float *)(this + 128) - 1.0;  // this+128 fChillPct
  pHostObj = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 158;  // this+4 pHostObj 等2字段
  *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pHostObj)) - fChillPct;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pHostObj, v4, v9);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_802 = *(float *)(this + 128) - 1.0;  // this+128 fChillPct
  fld_42 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 102;  // this+4 pHostObj 等2字段
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(fld_42)) - fld_802;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(fld_42, v6, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 676))(*(uint32_t *)(this + 4), 0);  // 调用虚函数槽 +676
}



// ------------------------------------------------------------
// 0x64B020 CNAuraMasterChilling__vmt24 —— CNAuraMasterChilling__vmt24 槽（4926A0）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterChilling__vmt24(int *this, int nArg2, int nArg3, int nArg4)  // 函数: CNAuraMasterChilling__vmt24 槽（4926A0）
{
  float fld_e33; // [esp+4h] [ebp-18h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 308))(*(this + 1)) != 0  // 判定 “+4 宿主对象指针”
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )  // CNAuraMasterChilling__vmt24 槽（4926A0）
  {
    fld_e33 = (float)*(this + 33);  // this+33 职业数据脏位
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 760))(  // 虚槽+760 CNDragonHeadFrontNentan__vmt2F8
      nArg2,
      1,
      LODWORD(fld_e33),
      5,
      *(this + 1),
      0);
  }
  return sub_4926A0(*(this + 34));  // 帧游标复位（+44 帧数组；递归子链 +204）
}



// ------------------------------------------------------------
// 0x64B080 CNAuraMasterChilling__vmt14 —— CNAuraMasterChilling__vmt14 生成槽（4938F0/491D00）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterChilling__vmt14(int *this, int nArg2, int nArg3, int nArg4, float fArg5)  // 函数: CNAuraMasterChilling__vmt14 生成槽（4938F0/491D00）
{
  int pAuraAnim; // ecx  | +0x007C → 光环动画件（CNRDAuraMaster·基类；va=0064A190）
  int result; // eax

  pAuraAnim = *(this + 31);  // fld_e31 = this+31
  if ( pAuraAnim != 0 )  // 若 fld_e31 != 0
  {
    result = *(this + 34);  // result = this+34
    if ( result != 0 )  // 若 result != 0
    {
      sub_4938F0(pAuraAnim);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      sub_4938F0(*(this + 34));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      return sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    }
  }
  return result;  // result=this+136 演出已播标志
}



// ------------------------------------------------------------
// 0x64B0F0 sub_64B0F0 —— 动画装载模板 "%s.ani"/"%sDamage.ani"（5910D0/42FCB0/431860/493400）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64B0F0(uint32_t *this, int nArg2, int nArg3, int nArg4, const char *pArg5)  // 动画装载模板 ”%s.ani”/”%sDamage.ani”（5910D0/42FCB0/4
{
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  char Buffer[512]; // [esp+10h] [ebp-410h] BYREF
  char v12[512]; // [esp+210h] [ebp-210h] BYREF
  int dword_796E502; // [esp+410h] [ebp-10h]
  int v14; // [esp+41Ch] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  sub_5910D0(0, 33, 500, 0);  // CNRDAuraMaster 构造函数
  v14 = 0;
  *this = &vftbl_CNAuraMasterChilling;  // *this 写入 &vftbl_CNAuraMasterChilling
  *(this + 32) = nArg3;  // this+128 = nArg3
  *(this + 33) = nArg4;  // this+132 = nArg4
  sprintf(Buffer, "%s.ani", pArg5);  // 字符串 “%s.ani”
  sprintf(v12, "%sDamage.ani", pArg5);  // 字符串 “%sDamage.ani”
  v6 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  LOBYTE(v14) = 1;
  if ( v6 != 0 )  // 若 v6 != 0
    v7 = sub_431860(v6, Buffer, 1);  // 结果 = 动画件构造（资源 id 版）
  else
    v7 = 0;
  LOBYTE(v14) = 0;
  *(this + 31) = v7;  // this+124 = v7
  v8 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  LOBYTE(v14) = 2;
  if ( v8 != 0 )  // 若 v8 != 0
    v9 = sub_431860(v8, v12, 1);  // 结果 = 动画件构造（资源 id 版）
  else
    v9 = 0;
  LOBYTE(v14) = 0;
  *(this + 34) = v9;  // this+136 = v9
  sub_493400(v9, 2);  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64B210 CNAuraMasterChilling__vmt0 —— CNAuraMasterChilling__vmt0 析构（转发 64B240）
// ------------------------------------------------------------
void */*thiscall*/ CNAuraMasterChilling__vmt0(void *Block, char pszArg2)  // CNAuraMasterChilling__vmt0 析构（转发 64B240）
{
  sub_64B240();  // 冰冷光环析构成员（42AF90/42A1B0/591190）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64B240 sub_64B240 —— 冰冷光环析构成员（42AF90/42A1B0/591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_64B240(void ***this)  // 函数: 冰冷光环析构成员（42AF90/42A1B0/591190）
{
  void **fld_e34; // edi

  *this = (void **)&vftbl_CNAuraMasterChilling;  // *this 写入 (void **)&vftbl_CNAuraMasterChilling
  fld_e34 = *(this + 34);  // fld_e34 = this+34
  if ( fld_e34 != nullptr )  // 若 fld_e34 非空
  {
    sub_42AF90(fld_e34);  // 帧对象析构（帧数组 + 元素数组）
    sub_42A1B0((int)fld_e34, 228);  // thunk → sub_657740
  }
  *(this + 34) = nullptr;  // this+136 = nullptr
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// ------------------------------------------------------------
// 0x64B2C0 CNAuraChangeStatusMaster__vmt84 —— CNAuraChangeStatusMaster__vmt84 受击事件槽（15 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraChangeStatusMaster__vmt84(int this, int nArg2)  // 函数: CNAuraChangeStatusMaster__vmt84 受击事件槽（15 行）
{
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（0x64A790 族；0x64B2C0: nArg2 == *(this+4) 判自身）（CNAuraChangeStatusMaster；va=0064A790）

  if ( *(uint8_t *)(this + 460) == 0 && nArg2 == *(uint32_t *)(this + 4) )  // 判定 “+460 精灵魂标志；+4 宿主对象指针”
    return false;
  pHostObj = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 376))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +376
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) == pHostObj;  // 虚槽+376 坐标同步包（type 37）
}



// ------------------------------------------------------------
// 0x64B300 CNAuraChangeStatusMasterSpikeKing__vmt84 —— CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉刺王变体，23 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraChangeStatusMasterSpikeKing__vmt84(int this, int nArg2)  // 函数: CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉刺王变体，23 行）
{
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（0x64A790 族；0x64B300: nArg2 == *(this+4) 判自身）（CNAuraChangeStatusMasterSpikeKing；va=0064A790）
  bool result; // al

  result = false;
  if ( *(uint8_t *)(this + 460) != 0 || nArg2 != *(uint32_t *)(this + 4) )  // 判定 “+460 精灵魂标志；+4 宿主对象指针”
  {
    pHostObj = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 376))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +376
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) == pHostObj  // 虚槽+376 坐标同步包（type 37）
      && __RTDynamicCast(nArg2, 0, &IRDActiveObject `RTTI Type Descriptor', &CNSpirit `RTTI Type Descriptor', 0) != 0 )  // CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉刺王变体，23 行）
    {
      return true;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x64B360 CNAuraChangeStatusMaster__vmt7C —— CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行）
// ------------------------------------------------------------
void /*thiscall*/ CNAuraChangeStatusMaster__vmt7C(int this, int nArg2)  // 函数: CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行）
{
  unsigned int i; // ebx
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int pObj; // ecx
  int pHostObj; // esi  | +0x0004 → 宿主对象指针（0x64A790 族；0x64B2C0: nArg2 == *(this+4) 判自身）（CNAuraChangeStatusMaster；va=0064A790）
  int v13; // eax
  int v14; // ecx
  int v15; // ecx
  int *v16; // esi

  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v4 = *(uint32_t *)(v3 + 4);  // v4 = v3+4
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )  // 若 (int)i >= v5
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v7 = *(uint32_t *)(v6 + 4);  // v7 = v6+4
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )  // 若 v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == nArg2 )  // 若 *(uint32_t *)(v8 + 4) == nArg2
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
        v10 = *(uint32_t *)(v9 + 4);  // v10 = v9+4
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )  // 若 v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2
          pObj = *(uint32_t *)(v10 + 4 * i);
        else
          pObj = 0;
        pHostObj = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 32) == pHostObj )  // pHostObj=this+4 pHostObj
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
          v14 = *(uint32_t *)(v13 + 4);  // v14 = v13+4
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )  // 若 v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2
            v15 = *(uint32_t *)(v14 + 4 * i);
          else
            v15 = 0;
          v16 = (int *)__RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                         v15,
                         0,
                         &IRDAppendage `RTTI Type Descriptor',
                         &CNChangeStatus `RTTI Type Descriptor',
                         0);
          if ( v16 != nullptr && sub_5F8000(v16, (char *)(this + 128), *(uint32_t *)(this + 456)) != 0 )  // 若 v16 != nullptr && sub_5F8000(v16, (char *)(this + 128), *(uint..
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*v16 + 76))(v16, 0);  // 虚调用 vt+76
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64B480 sub_64B480 —— 状态变化文本（4015C0/4022F0）
// ------------------------------------------------------------
void /*thiscall*/ sub_64B480(void *this, void *Src, const char *pArg3)  // 函数: 状态变化文本（4015C0/4022F0）
{
  void **Block2; // eax
  uint8_t v5[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+Ch] [ebp-28h] BYREF
  unsigned int v7; // [esp+20h] [ebp-14h]
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v9; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;  // 全局 dword_796E50 = 帧时刻快照源
  v7 = 15;
  Block[4] = nullptr;  // Block[4] = nullptr 空指针
  LOBYTE(Block[0]) = 0;
  sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
  v9 = 0;
  sub_4022F0((std::_String_base *)v5, pArg3, strlen(pArg3));  // std::string::insert(pos, s, n) 模板实例（指定位置插入，qme
  Block2 = (void **)Block[0];
  if ( v7 < 0x10 )  // 若 v7 < 0x10
    Block2 = Block;
  (*(void (/*thiscall*/ **)(void *, void **))(*(uint32_t *)this + 128))(this, Block2);  // 调用虚函数槽 +128
  if ( v7 >= 0x10 )  // 若 v7 >= 0x10
    j__free(Block[0]);  // 调 j__free
}



// ------------------------------------------------------------
// 0x64B540 CNAuraChangeStatusMaster__vmt78 —— CNAuraChangeStatusMaster__vmt78 变化生效（5F8000/5101B0，94 行）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraChangeStatusMaster__vmt78(int this, void *Block)  // 函数: CNAuraChangeStatusMaster__vmt78 变化生效（5F8000/5101B0，94 行）
{
  uint32_t *pThis; // edi
  unsigned int i; // ebx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int pObj; // ecx
  int v13; // edi
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int *v17; // eax
  char result; // al
  uint32_t *pMem; // eax
  uint32_t *v20; // eax

  pThis = (uint32_t *)this;
  if ( Block != nullptr )  // 若 Block 非空
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);  // 调用虚函数槽 +700
      v5 = *(uint32_t *)(v4 + 4);  // v5 = v4+4
      v6 = v5 != 0 ? (*(uint32_t *)(v4 + 8) - v5) >> 2 : 0;
      if ( (int)i >= v6 )  // 若 (int)i >= v6
        break;
      v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);  // 调用虚函数槽 +700
      v8 = *(uint32_t *)(v7 + 4);  // v8 = v7+4
      if ( v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2 )  // 若 v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2
        v9 = *(uint32_t *)(v8 + 4 * i);
      else
        v9 = 0;
      if ( *(void **)(v9 + 4) == Block )  // 若 *(void **)(v9 + 4) == Block
      {
        v10 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);  // 调用虚函数槽 +700
        v11 = *(uint32_t *)(v10 + 4);  // v11 = v10+4
        if ( v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2 )  // 若 v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2
          pObj = *(uint32_t *)(v11 + 4 * i);
        else
          pObj = 0;
        v13 = pThis[1];
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 32) == v13 )  // 虚槽+64 CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/4015C0/45A340
        {
          v14 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);  // 调用虚函数槽 +700
          v15 = *(uint32_t *)(v14 + 4);  // v15 = v14+4
          if ( v15 != 0 && i < (*(uint32_t *)(v14 + 8) - v15) >> 2 )  // 若 v15 != 0 && i < (*(uint32_t *)(v14 + 8) - v15) >> 2
            v16 = *(uint32_t *)(v15 + 4 * i);
          else
            v16 = 0;
          v17 = (int *)__RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                         v16,
                         0,
                         &IRDAppendage `RTTI Type Descriptor',
                         &CNChangeStatus `RTTI Type Descriptor',
                         0);
          if ( v17 != nullptr )  // 若 v17 非空
          {
            result = sub_5F8000(v17, (char *)(this + 128), *(uint32_t *)(this + 456));  // 调 sub_5F8000
            if ( result != 0 )  // 若 result != 0
              return result;
            pThis = (uint32_t *)this;
            break;
          }
        }
        pThis = (uint32_t *)this;
      }
    }
  }
  pMem = operator new(0x7Cu);  // 堆分配 124 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    v20 = sub_5101B0(pMem, (int)(pThis + 32), pThis[114], pThis[113], 1);  // 调 sub_5101B0
  else
    v20 = nullptr;  // v20 = nullptr 空指针
  return (*(int (/*thiscall*/ **)(uint32_t *, void *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v20 + 56))(  // 虚调用 vt+56
           v20,
           Block,
           pThis[1],
           0,
           0,
           0,
           -1);
}



// ============================================================
// 【分区 14】火焰光环族 CNAuraMasterFlame / CNFlameDamageFromFlameAura（0x64B6C0-0x64BDF0）
// 资源 Character/Fighter/Effect/Particle/NenMaster.ptl（气功师念气球）；
// vmt78 生效事件复用 AURA_ICE_SET 标签（二进制事实，与冰族共用常量）；
// 64B740=SIZZLE_HIT 灼烧事件（605840/4E4A50）。
// ============================================================
// ------------------------------------------------------------
// 0x64B6C0 sub_64B6C0 —— 火焰动画查询（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64B6C0(uint32_t *this, int nArg2, const void *pArg3, int nArg4, int nArg5, char pszArg6, int nArg7)  // 火焰动画查询（5910D0）
{
  sub_5910D0(nArg2, 17, 500, nArg7);  // CNRDAuraMaster 构造函数
  *this = &vftbl_CNAuraChangeStatusMaster;  // *this 写入 &vftbl_CNAuraChangeStatusMaster
  qmemcpy(this + 32, pArg3, 4 * ((unsigned int)(12 * nArg4) >> 2));  // 调 qmemcpy 内联块拷贝
  *(this + 114) = nArg4;  // this+456 = nArg4
  *(this + 113) = nArg5;  // this+452 = nArg5
  *((uint8_t *)this + 460) = pszArg6;  // this+460 精灵魂标志
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64B730 CNAuraMasterFlame__vmt68 —— CNAuraMasterFlame__vmt68 特效触发槽（10 行）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterFlame__vmt68(uint32_t **this)  // 函数: CNAuraMasterFlame__vmt68 特效触发槽（10 行）
{
  return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 34) + 12))(*(this + 34), 0);  // 调用虚函数槽 +12
}



// ------------------------------------------------------------
// 0x64B740 sub_64B740 —— 火焰灼烧事件：SIZZLE_HIT（605840 目标 + 4E4A50 伤害，64 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64B740(int this)  // 函数: 火焰灼烧事件：SIZZLE_HIT（605840 目标 + 4E4A50 伤害，64 行）
{
  int result; // eax
  int fld_4; // ecx
  int v4; // eax
  int fld_42; // ecx
  int v6; // eax
  int fld_43; // edi
  int v8; // ebx
  int v9; // ebx
  int fld_44; // eax
  int16_t *v11; // eax
  float v12; // [esp+4h] [ebp-20h] BYREF
  float v13; // [esp+8h] [ebp-1Ch]
  float v14; // [esp+Ch] [ebp-18h]
  int v15; // [esp+10h] [ebp-14h]
  int v16; // [esp+14h] [ebp-10h]
  int v17; // [esp+18h] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-8h]
  int v19; // [esp+20h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 100) + 12))(*(uint32_t *)(this + 100), 0);  // 调用虚函数槽 +12
  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +308
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    fld_4 = *(uint32_t *)(this + 4);  // fld_4 = this+4
    v12 = 0.0;
    v13 = 0.0;
    v14 = 0.0;
    v15 = 0;
    v16 = 0;
    v17 = 0;
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 120))(fld_4);  // 调用虚函数槽 +120
    fld_42 = *(uint32_t *)(this + 4);  // fld_42 = this+4
    v18 = v4;
    v12 = (float)v4;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_42 + 124))(fld_42);  // 调用虚函数槽 +124
    fld_43 = *(uint32_t *)(this + 4);  // fld_43 = this+4
    v18 = v6;
    v13 = (float)v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 192))(fld_43) / 2;  // fld_43=this+4 宿主对象
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_43 + 128))(fld_43) + v8;  // fld_43=this+4 宿主对象
    fld_44 = *(uint32_t *)(this + 4);  // fld_44 = this+4
    v18 = v9;
    v14 = (float)v9;
    v19 = 0;
    v11 = sub_605840(&v19, fld_44, (int *)&v12, 0);  // 结果 = 30 字节全局包
    sub_4E4A50(*(uint32_t *)(this + 36), 42004, *(uint32_t *)(this + 96), 0, 0, 0, 1, 0, v19, v11);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    result = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(  // this+4 宿主对象
               *(uint32_t *)(this + 4),  // this+4 宿主对象
               "SIZZLE_HIT",  // 字符串 “SIZZLE_HIT”
               -1,
               0,
               0);
    *(uint32_t *)(this + 72) = *(uint32_t *)(this + 104);  // this+72 = *(uint32_t *)(this + 104)
  }
  return result;
}



// ------------------------------------------------------------
// 0x64B850 sub_64B850 —— 火焰受方装配（4B1030 + 64A350）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64B850(uint32_t *this, int nArg2, int nArg3)  // 火焰受方装配（4B1030 + 64A350）
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNRDAuraMinion;  // *this 写入 &vftbl_CNRDAuraMinion
  sub_64A350(this);  // 受方表现转发
  *this = &vftbl_CNFlameDamageFromFlameAura;  // *this 写入 &vftbl_CNFlameDamageFromFlameAura
  *(this + 24) = nArg2;  // this+96 = nArg2
  *(this + 26) = nArg3;  // this+104 = nArg3
  *(this + 18) = (uint64_t)((double)nArg3 * 0.5);  // this+72 = (uint64_t)((double)nArg3 * 0.5)
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64B8C0 CNFlameDamageFromFlameAura__vmt0 —— CNFlameDamageFromFlameAura__vmt0 析构（转发 64B8F0）
// ------------------------------------------------------------
void */*thiscall*/ CNFlameDamageFromFlameAura__vmt0(void *Block, char pszArg2)  // CNFlameDamageFromFlameAura__vmt0 析构（转发 64B8F0）
{
  sub_64B8F0();  // 火焰受方初始化（649300 系）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64B8F0 sub_64B8F0 —— 火焰受方初始化（649300 系）
// ------------------------------------------------------------
int /*thiscall*/ sub_64B8F0(uint32_t *this)  // 函数: 火焰受方初始化（649300 系）
{
  void (/*thiscall*/ ***fld_e25)(uint32_t, int); // ecx

  *this = &vftbl_CNFlameDamageFromFlameAura;  // *this 写入 &vftbl_CNFlameDamageFromFlameAura
  fld_e25 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  if ( fld_e25 != nullptr )  // 若 fld_e25 非空
    (**fld_e25)(fld_e25, 1);
  *(this + 25) = 0;  // this+100 = 0
  return sub_649300((int)this);  // 召唤受方表现初始化（64A880 + 5F6640）
}



// ------------------------------------------------------------
// 0x64B950 CNAuraMasterFlame__vmt78 —— CNAuraMasterFlame__vmt78 光环生效：事件标签复用 AURA_ICE_SET（转发 64B850）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterFlame__vmt78(int *this, int nArg2)  // 函数: CNAuraMasterFlame__vmt78 光环生效：事件标签复用 AURA_ICE_SET（转发 64B850）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e32; // eax

  pMem = operator new(0x6Cu);  // 堆分配 108 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e32 = sub_64B850(pMem, *(this + 32), *(this + 33));  // 结果 = 火焰受方装配（4B1030 + 64A350）
  else
    fld_e32 = nullptr;  // fld_e32 = nullptr 空指针
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*fld_e32 + 56))(  // 虚调用 vt+56
    fld_e32,
    nArg2,
    *(this + 1),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 212))(  // 虚槽+212 音效标签播放（szPassword 去重 → sub_65FE10 分发到 50 声道）
           nArg2,
           "AURA_ICE_SET",  // 字符串 “AURA_ICE_SET”
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64B9F0 CNAuraMasterFlame__vmt7C —— CNAuraMasterFlame__vmt7C 光环失效槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterFlame__vmt7C(int nArg1)  // 函数: CNAuraMasterFlame__vmt7C 光环失效槽（58 行）
{
  unsigned int i; // edi
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int pObj; // eax

  if ( nArg1 != 0 )  // 若 nArg1 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v3 = *(uint32_t *)(v2 + 4);  // v3 = v2+4
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )  // 若 (int)i >= v4
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v6 = *(uint32_t *)(v5 + 4);  // v6 = v5+4
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )  // 若 v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == nArg1 )  // 若 *(uint32_t *)(v7 + 4) == nArg1
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
        v9 = *(uint32_t *)(v8 + 4);  // v9 = v8+4
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )  // 若 v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        pObj = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNFlameDamageFromFlameAura `RTTI Type Descriptor',
                0);
        if ( pObj != 0 )  // 若 pObj != 0
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 调用虚函数槽 +76
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64BAA0 CNAuraMasterFlame__vmt4 —— CNAuraMasterFlame__vmt4 复位（4600B0）
// ------------------------------------------------------------
void /*thiscall*/ CNAuraMasterFlame__vmt4(int this)  // 函数: CNAuraMasterFlame__vmt4 复位（4600B0）
{
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（CNAuraMasterFlame；va=0064BAA0）
  int pFlameAnim; // ebx  | +0x0088 → 火焰动画件（CNAuraMasterFlame；va=0064BAA0）
  int *pHostObj_; // ecx
  int v5; // edx
  void *v6; // eax
  int v7; // [esp-Ch] [ebp-34h]
  int v8; // [esp-8h] [ebp-30h]
  int v9; // [esp-4h] [ebp-2Ch]
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+24h] [ebp-4h]

  CNRDAuraMaster__vmt4(this);  // 调 CNRDAuraMaster__vmt4 析构复位
  pHostObj = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
  pFlameAnim = **(uint32_t **)(this + 136);  // this+136 pFlameAnim
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 128))(pHostObj);  // 调用虚函数槽 +128
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 124))(pHostObj);  // 调用虚函数槽 +124
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 120))(pHostObj);  // 调用虚函数槽 +120
  (*(void (/*thiscall*/ **)(uint32_t))(pFlameAnim + 40))(*(uint32_t *)(this + 136));  // 调用虚函数槽 +40
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 136) + 92))(*(uint32_t *)(this + 136), v10);  // 调用虚函数槽 +92
  pHostObj_ = *(int **)(this + 4);  // this+4 pHostObj
  v5 = *pHostObj_;  // fld_42=this+4 pHostObj
  v12 = 0;
  v6 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v5 + 80))(pHostObj_, 2, 0, v10);  // fld_42=this+4 pHostObj
  sub_4600B0(v6, v7, v8, v9);  // 调 sub_4600B0
  if ( Block != nullptr )  // 若 Block 非空
    j__free(Block);  // 调 j__free
}



// ------------------------------------------------------------
// 0x64BB50 CNFlameDamageFromFlameAura__vmt4 —— CNFlameDamageFromFlameAura__vmt4 伤害（4600B0）
// ------------------------------------------------------------
void /*thiscall*/ CNFlameDamageFromFlameAura__vmt4(int this)  // 函数: CNFlameDamageFromFlameAura__vmt4 伤害（4600B0）
{
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（0x64BB50: CNRDAuraMinion__vmt4 转发后取宿主坐标）（CNFlameDamageFromFlameAura；va=0064BB50）
  int pDmgAnim; // ebx  | +0x0064 → 伤害动画件（CNFlameDamageFromFlameAura；va=0064BB50）
  int *pHostObj_; // ecx
  int v5; // edx
  void *v6; // eax
  int v7; // [esp-Ch] [ebp-34h]
  int v8; // [esp-8h] [ebp-30h]
  int v9; // [esp-4h] [ebp-2Ch]
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+24h] [ebp-4h]

  CNRDAuraMinion__vmt4((int *)this);  // 调 CNRDAuraMinion__vmt4 复位槽
  pHostObj = *(uint32_t *)(this + 4);  // 读 fld_4 = this+4（宿主对象指针）
  pDmgAnim = **(uint32_t **)(this + 100);  // this+100 pDmgAnim
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 128))(pHostObj);  // 调用虚函数槽 +128
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 124))(pHostObj);  // 调用虚函数槽 +124
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 120))(pHostObj);  // 调用虚函数槽 +120
  (*(void (/*thiscall*/ **)(uint32_t))(pDmgAnim + 40))(*(uint32_t *)(this + 100));  // 调用虚函数槽 +40
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 100) + 92))(*(uint32_t *)(this + 100), v10);  // 调用虚函数槽 +92
  pHostObj_ = *(int **)(this + 4);  // this+4 pHostObj
  v5 = *pHostObj_;  // fld_42=this+4 pHostObj
  v12 = 0;
  v6 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v5 + 80))(pHostObj_, 2, 0, v10);  // fld_42=this+4 pHostObj
  sub_4600B0(v6, v7, v8, v9);  // 调 sub_4600B0
  if ( Block != nullptr )  // 若 Block 非空
    j__free(Block);  // 调 j__free
}



// ------------------------------------------------------------
// 0x64BBF0 sub_64BBF0 —— 火焰动画查询 2（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64BBF0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 火焰动画查询 2（5910D0）
{
  sub_5910D0(nArg2, 18, 500, 0);  // CNRDAuraMaster 构造函数
  *(this + 33) = nArg3;  // this+132 = nArg3
  *(this + 18) = nArg3;  // this+72 = nArg3
  *this = &vftbl_CNAuraMasterFlame;  // *this 写入 &vftbl_CNAuraMasterFlame
  *(this + 32) = nArg4;  // this+128 = nArg4
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64BC30 CNAuraMasterFlame__vmt0 —— CNAuraMasterFlame__vmt0 析构（转发 64BC60）
// ------------------------------------------------------------
void */*thiscall*/ CNAuraMasterFlame__vmt0(void *Block, char pszArg2)  // CNAuraMasterFlame__vmt0 析构（转发 64BC60）
{
  sub_64BC60();  // 火焰光环析构成员（591190）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64BC60 sub_64BC60 —— 火焰光环析构成员（591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_64BC60(uint32_t *this)  // 函数: 火焰光环析构成员（591190）
{
  void (/*thiscall*/ ***fld_e34)(uint32_t, int); // ecx

  *this = &vftbl_CNAuraMasterFlame;  // *this 写入 &vftbl_CNAuraMasterFlame
  fld_e34 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 34);
  if ( fld_e34 != nullptr )  // 若 fld_e34 非空
    (**fld_e34)(fld_e34, 1);
  *(this + 34) = 0;  // this+136 = 0
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// ------------------------------------------------------------
// 0x64BCD0 CNAuraMasterFlame__vmt1C —— CNAuraMasterFlame__vmt1C 生成装配：Character/Fighter/Effect/Particle/NenMaster.ptl（气功师念气，428F30/5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraMasterFlame__vmt1C(int *this)  // 函数: CNAuraMasterFlame__vmt1C 生成装配：Character/Fighter/Effect/Particle/NenMaster.ptl（气功师念气，428F30/5F66A0）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e1; // eax
  int pHostObj; // ecx  | +0x0004 → 宿主对象指针（CNAuraMasterFlame；va=0064BAA0）

  CNRDAuraMaster__vmt1C((int)this);  // 调 CNRDAuraMaster__vmt1C 生成装配
  pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e1 = sub_428F30(pMem, (int)"Character/Fighter/Effect/Particle/NenMaster.ptl", *(this + 1));  // 字符串 “Character/Fighter/Effect/Particle/NenMaster.”
  else
    fld_e1 = nullptr;  // fld_e1 = nullptr 空指针
  pHostObj = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
  *(this + 34) = (int)fld_e1;  // 写 this+136 = (int)fld_e1（火焰动画件）
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e1 + 112))(fld_e1, pHostObj);  // 虚调用 vt+112
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 34) + 12))(*(this + 34), 0);  // 调用虚函数槽 +12
  return sub_5F66A0((int)this, 1);  // 调 sub_5F66A0
}



// ------------------------------------------------------------
// 0x64BD60 CNFlameDamageFromFlameAura__vmt1C —— CNFlameDamageFromFlameAura__vmt1C 生成装配：NenMaster.ptl（428F30/5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNFlameDamageFromFlameAura__vmt1C(int *this)  // 函数: CNFlameDamageFromFlameAura__vmt1C 生成装配：NenMaster.ptl（428F30/5F66A0）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e1; // eax
  int pHostObj; // ecx  | +0x0004 → 宿主对象指针（0x64BB50: CNRDAuraMinion__vmt4 转发后取宿主坐标）（CNFlameDamageFromFlameAura；va=0064BB50）

  pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e1 = sub_428F30(pMem, (int)"Character/Fighter/Effect/Particle/NenMaster.ptl", *(this + 1));  // 字符串 “Character/Fighter/Effect/Particle/NenMaster.”
  else
    fld_e1 = nullptr;  // fld_e1 = nullptr 空指针
  pHostObj = *(this + 1);  // 读 fld_e12 = this+4（宿主对象指针）
  *(this + 25) = (int)fld_e1;  // 写 this+100 = (int)fld_e1（伤害动画件）
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e1 + 112))(fld_e1, pHostObj);  // 虚调用 vt+112
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 25) + 12))(*(this + 25), 0);  // 调用虚函数槽 +12
  return sub_5F66A0((int)this, 1);  // 调 sub_5F66A0
}



// ============================================================
// 【分区 15】战斗光环族 CNAuraMasterBattle 系（0x64BDF0-0x64CC30）
// 资源 BattleAuraMaster.ani + BattleAuraMinion/S/E.ani（64C2F0/64C760 装配）；
// vmt78 生效事件 AURA_POWER_SET；派生：CNAttackUpFromBattleAura（攻击上升）、
// CNAuraMasterATDFSPEEDUp（+ATDF/SPEED，_KingGalok 王加洛克/_Father 变体）、
// CNChangeDamageBonusRate（Common/CommonEffect/Particle/AttackPowerUp.ptl）。
// ============================================================
// ------------------------------------------------------------
// 0x64BDF0 sub_64BDF0 —— 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
// ------------------------------------------------------------
char /*userpurge*/ sub_64BDF0@<al>(int pArg1@<ecx>, int nArg2@<edi>, uint32_t *pArg3, int nArg4)  // 函数: 战斗光环基础数据（4049C0 + 4DAB60/4DB200 播报，175 行）
{
  int v4; // eax
  int v6; // edi
  int v7; // edi
  uint32_t *v8; // ebx
  int v9; // eax
  uint64_t v10; // rax
  int v11; // edi
  int v12; // edi
  uint32_t *v13; // ebx
  int v14; // eax
  uint64_t v15; // rax
  unsigned int v16; // ebx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // edx
  int pObj3; // ecx
  int v24; // eax
  int v25; // edx
  uint32_t *v26; // edi
  int v27; // ebx
  int v28; // ebx
  int v29; // eax
  int v30; // ebx
  int v31; // eax
  int pObj; // eax
  int v33; // edi
  int v34; // eax
  int v35; // ebx
  int v36; // eax
  int v37; // ebx
  int v38; // eax
  bool v39; // cc
  int nRand; // eax
  int v41; // et2
  int nRand2; // eax
  int v45; // [esp+0h] [ebp-18h]
  int pArg12; // [esp+4h] [ebp-14h]
  int pObj2; // [esp+8h] [ebp-10h]
  int v48; // [esp+Ch] [ebp-Ch]
  int v49; // [esp+10h] [ebp-8h]
  int v50; // [esp+14h] [ebp-4h]
  unsigned int v51; // [esp+20h] [ebp+8h]
  char v52; // [esp+27h] [ebp+Fh]

  LOBYTE(v4) = *(uint8_t *)(pArg1 + 5);
  pArg12 = pArg1;
  if ( (uint8_t)v4 != 0 )  // 若 (uint8_t)v4 != 0
  {
    *(uint8_t *)(pArg1 + 4) = 0;  // pArg1+4 = 0
    if ( nArg4 != 0 )  // 若 nArg4 != 0
    {
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 576))(nArg4);  // 调用虚函数槽 +576
      pObj2 = v4;
      if ( v4 != 0 )  // 若 v4 != 0
      {
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3);  // 结果 = 虚调用 vt+1032
        v7 = *(uint32_t *)(v6 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3) + 48);  // 结果 = 虚调用 vt+1032
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 672))(pArg3, 3);  // 结果 = 虚调用 vt+672
        v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3);  // 结果 = 虚调用 vt+1032
        v10 = (uint64_t)sub_4049C0(800.0, 1200.0, *v8 - *(uint32_t *)(v9 + 48), v7);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        HIDWORD(v10) = *pArg3;
        v48 = v10;
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(HIDWORD(v10) + 1032))(pArg3);  // 调用虚函数槽 +1032
        v12 = *(uint32_t *)(v11 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3) + 48);  // 结果 = 虚调用 vt+1032
        v13 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 672))(pArg3, 3);  // 结果 = 虚调用 vt+672
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 1032))(pArg3);  // 结果 = 虚调用 vt+1032
        v15 = (uint64_t)sub_4049C0(3.0, 6.0, *v13 - *(uint32_t *)(v14 + 48), v12);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        HIDWORD(v15) = *pArg3;
        v49 = v15;
        if ( *(int *)(*(int (/*thiscall*/ **)(uint32_t *))(HIDWORD(v15) + 340))(pArg3) >= 5
          && *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 340))(pArg3) != 63 )  // 虚调用 vt+340
        {
          v49 = 6;
        }
        v16 = 0;
        v52 = 1;
        v50 = 0;
        while ( 1 )  // 当 1 循环
        {
          v51 = v16;
          v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 80))(pArg3);  // 结果 = 虚调用 vt+80
          v18 = *(uint32_t *)(v17 + 8);  // v18 = v17+8
          v19 = v17 + 4;
          v20 = v18 != 0 ? (*(uint32_t *)(v19 + 8) - v18) >> 2 : 0;
          if ( (int)v16 >= v20 )  // 若 (int)v16 >= v20
            break;
          v21 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 80))(pArg3, nArg2);  // 结果 = 虚调用 vt+80
          v22 = *(uint32_t *)(v21 + 8);  // v22 = v21+8
          if ( v22 != 0 && v16 < (*(uint32_t *)(v21 + 12) - v22) >> 2 )  // 若 v22 != 0 && v16 < (*(uint32_t *)(v21 + 12) - v22) >> 2
            pObj3 = *(uint32_t *)(v22 + 4 * v16);
          else
            pObj3 = 0;
          nArg2 = 529;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 40))(pObj3) != 0 )  // 虚槽+40 CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/4868
          {
            v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 80))(pArg3);  // 结果 = 虚调用 vt+80
            v25 = *(uint32_t *)(v24 + 8);  // v25 = v24+8
            if ( v25 != 0 && v16 < (*(uint32_t *)(v24 + 12) - v25) >> 2 )  // 若 v25 != 0 && v16 < (*(uint32_t *)(v24 + 12) - v25) >> 2
              v26 = *(uint32_t **)(v25 + 4 * v16);
            else
              v26 = nullptr;  // v26 = nullptr 空指针
            if ( v26[1943] != 3 )  // 若 v26[1943] != 3
            {
              v27 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg3 + 376))(pArg3);  // 结果 = 虚调用 vt+376
              if ( v27 == (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 376))(v26)  // 虚调用 vt+376
                && pArg3 != v26
                && (uint8_t)sub_4DAB60(19) != 0  // 标签/条件集合成员判定
                && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t))(*pArg3 + 8))(pArg3, v26, 0) <= v48  // 虚调用 vt+8
                && (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 304))(v26) != 0 )  // 虚调用 vt+304
              {
                (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);  // 调用虚函数槽 +8
                v28 = *(uint32_t *)dword_8F8520;  // dword_8F8520（会话/UDP 管理器）
                v29 = (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 48))(v26);  // 结果 = 虚调用 vt+48
                (*(void (/*thiscall*/ **)(int, int))(v28 + 36))(dword_8F8520, v29);  // 调用虚函数槽 +36
                v30 = *(uint32_t *)dword_8F8520;  // dword_8F8520（会话/UDP 管理器）
                v31 = (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 52))(v26);  // 结果 = 虚调用 vt+52
                (*(void (/*thiscall*/ **)(int, int))(v30 + 36))(dword_8F8520, v31);  // 调用虚函数槽 +36
                pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 304))(v26);  // 结果 = 虚调用 vt+304
                v33 = *(uint32_t *)dword_8F8520;  // dword_8F8520（会话/UDP 管理器）
                v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 调用虚函数槽 +52
                (*(void (/*thiscall*/ **)(int, int))(v33 + 36))(dword_8F8520, v34);  // 调用虚函数槽 +36
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 11);  // 调用虚函数槽 +36
                v35 = *(uint32_t *)dword_8F8520;  // dword_8F8520（会话/UDP 管理器）
                v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);  // 调用虚函数槽 +48
                (*(void (/*thiscall*/ **)(int, int))(v35 + 36))(dword_8F8520, v36);  // 调用虚函数槽 +36
                v37 = *(uint32_t *)dword_8F8520;  // dword_8F8520（会话/UDP 管理器）
                v38 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);  // 调用虚函数槽 +52
                (*(void (/*thiscall*/ **)(int, int))(v37 + 36))(dword_8F8520, v38);  // 调用虚函数槽 +36
                (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调用虚函数槽 +60
                v39 = v50 + 1 <= v49;
                v52 = 0;
                ++v50;  // 自增v50
                if ( !v39 )  // 若 !v39
                  break;
              }
              v16 = v51;
            }
          }
          ++v16;  // 自增v16
        }
        v4 = pArg3[1909];
        if ( v4 != 0 )  // 若 v4 != 0
        {
          LOBYTE(v4) = v52;
          if ( v52 != 0 && pArg3[1787] != 6 )  // 若 v52 != 0 && pArg3[1787] != 6
          {
            nRand = rand();  // 调 rand 伪随机
            v41 = nRand % 100;
            v4 = nRand / 100;
            if ( v41 < 50 )  // 若 v41 < 50
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg3 + 1140))(pArg3, -1, -1);  // 虚调用 vt+1140
              *(uint8_t *)(pArg12 + 4) = 1;  // pArg12+4 = 1
              v45 = 0;
              pArg12 = 1;
              nRand2 = rand() % 2;  // 调 rand（取伪随机数）
              LOBYTE(v4) = sub_4DB200(24, *(&v45 + nRand2));  // 15% 概率随机文案触发（0x4DB130 的门包装）
            }
          }
        }
      }
    }
  }
  return v4;
}


// ------------------------------------------------------------
// 0x64C140 CNAuraMasterBattle__vmt1C —— CNAuraMasterBattle__vmt1C 生成装配：Common/Etc/Animation/Aura/BattleAuraMaster.ani
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterBattle__vmt1C(void *this)  // 函数: CNAuraMasterBattle__vmt1C 生成装配：Common/Etc/Animation/Aura/BattleAuraMaster.ani
{
  CNRDAuraMaster__vmt1C((int)this);  // 调 CNRDAuraMaster__vmt1C 生成装配
  return (*(int (/*thiscall*/ **)(void *, const char *))(*(uint32_t *)this + 128))(  // this+128 第 2 组·+1208 增量子倍率
           this,
           "Common/Etc/Animation/Aura/BattleAuraMaster.ani");  // 字符串 “Common/Etc/Animation/Aura/BattleAuraMaster.a”
}



// ------------------------------------------------------------
// 0x64C160 CNAttackUpFromBattleAura__vmtC —— CNAttackUpFromBattleAura__vmtC 打开槽（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNAttackUpFromBattleAura__vmtC(uint32_t *this, int pArg2)  // 函数: CNAttackUpFromBattleAura__vmtC 打开槽（41A5E0/41A590）
{
  int fld_e24; // ebx
  int v4; // eax
  int v5; // edx
  int fld_e242; // esi
  int v7; // eax
  int v8; // edx

  fld_e24 = *(this + 24);  // fld_e24 = this+24
  v4 = sub_41A5E0(pArg2 + 1306);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg2 + 1306, v5, fld_e24 + v4);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_e242 = *(this + 24);  // fld_e242 = this+24
  v7 = sub_41A5E0(pArg2 + 1334);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pArg2 + 1334, v8, fld_e242 + v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x64C1B0 CNAuraMasterBattleGoblinKinol__vmt84 —— CNAuraMasterBattleGoblinKinol__vmt84 受击事件槽（哥布林奇诺尔变体）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraMasterBattleGoblinKinol__vmt84(uint32_t *this, int nArg2)  // 函数: CNAuraMasterBattleGoblinKinol__vmt84 受击事件槽（哥布林奇诺尔变体）
{
  int pHostObj; // esi  | +0x0004 → 宿主对象指针（CNAuraMasterBattleGoblinKinol；va=0064A790）
  int v4; // edi
  bool result; // al

  result = false;
  if ( __RTDynamicCast(nArg2, 0, &IRDActiveObject `RTTI Type Descriptor', &CNGoblinGoblin `RTTI Type Descriptor', 0) != 0 )  // 若 __RTDynamicCast(nArg2, 0, &IRDActiveObject `RTTI Type Descript..
  {
    pHostObj = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 调用虚函数槽 +376
    if ( v4 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 376))(pHostObj) )  // pHostObj=this+4 pHostObj
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64C210 CNAuraMasterBattle__vmt7C —— CNAuraMasterBattle__vmt7C 光环失效槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterBattle__vmt7C(int nArg1)  // 函数: CNAuraMasterBattle__vmt7C 光环失效槽（58 行）
{
  unsigned int i; // edi
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int pObj; // eax

  if ( nArg1 != 0 )  // 若 nArg1 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v3 = *(uint32_t *)(v2 + 4);  // v3 = v2+4
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )  // 若 (int)i >= v4
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v6 = *(uint32_t *)(v5 + 4);  // v6 = v5+4
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )  // 若 v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == nArg1 )  // 若 *(uint32_t *)(v7 + 4) == nArg1
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
        v9 = *(uint32_t *)(v8 + 4);  // v9 = v8+4
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )  // 若 v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        pObj = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNAttackUpFromBattleAura `RTTI Type Descriptor',
                0);
        if ( pObj != 0 )  // 若 pObj != 0
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 调用虚函数槽 +76
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64C2C0 sub_64C2C0 —— 战斗动画查询（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64C2C0(uint32_t *this, int nArg2, int nArg3)  // 战斗动画查询（5910D0）
{
  sub_5910D0(nArg2, 18, 500, 0);  // CNRDAuraMaster 构造函数
  *this = &vftbl_CNAuraMasterBattle;  // *this 写入 &vftbl_CNAuraMasterBattle
  *(this + 32) = nArg3;  // this+128 = nArg3
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64C2F0 sub_64C2F0 —— 战斗光环随从装配：BattleAuraMinion.ani/BattleAuraMinionS.ani/BattleAuraMinionE.ani（4B1030/64A350/42FCB0/431860）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64C2F0(uint32_t *this, int nArg2)  // 战斗光环随从装配：BattleAuraMinion.ani/BattleAuraMinion
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax

  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNRDAuraMinion;  // *this 写入 &vftbl_CNRDAuraMinion
  sub_64A350(this);  // 受方表现转发
  *this = &vftbl_CNAttackUpFromBattleAura;  // *this 写入 &vftbl_CNAttackUpFromBattleAura
  *(this + 24) = nArg2;  // this+96 = nArg2
  v3 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v3 != 0 )  // 若 v3 != 0
    v4 = sub_431860(v3, "Common/Etc/Animation/Aura/BattleAuraMinion.ani", 1);  // 字符串 “Common/Etc/Animation/Aura/BattleAuraMinion.a”
  else
    v4 = 0;
  *(this + 21) = v4;  // this+84 = v4
  v5 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v5 != 0 )  // 若 v5 != 0
    v6 = sub_431860(v5, "Common/Etc/Animation/Aura/BattleAuraMinionS.ani", 1);  // 字符串 “Common/Etc/Animation/Aura/BattleAuraMinionS.”
  else
    v6 = 0;
  *(this + 22) = v6;  // this+88 = v6
  v7 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v7 != 0 )  // 若 v7 != 0
    v8 = sub_431860(v7, "Common/Etc/Animation/Aura/BattleAuraMinionE.ani", 1);  // 字符串 “Common/Etc/Animation/Aura/BattleAuraMinionE.”
  else
    v8 = 0;
  *(this + 23) = v8;  // this+92 = v8
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64C3E0 CNAttackUpFromBattleAura__vmt0 —— CNAttackUpFromBattleAura__vmt0 析构（转发 64C410）
// ------------------------------------------------------------
void */*thiscall*/ CNAttackUpFromBattleAura__vmt0(void *Block, char pszArg2)  // CNAttackUpFromBattleAura__vmt0 析构（转发 64C410）
{
  sub_64C410();  // 攻击上升受方初始化（649300 系）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64C410 sub_64C410 —— 攻击上升受方初始化（649300 系）
// ------------------------------------------------------------
int /*thiscall*/ sub_64C410(int this)  // 函数: 攻击上升受方初始化（649300 系）
{
  *(uint32_t *)this = &vftbl_CNAttackUpFromBattleAura;
  return sub_649300(this);  // 召唤受方表现初始化（64A880 + 5F6640）
}



// ------------------------------------------------------------
// 0x64C420 CNAuraMasterBattle__vmt78 —— CNAuraMasterBattle__vmt78 光环生效：AURA_POWER_SET 事件（转发 64C2F0）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterBattle__vmt78(int *this, int nArg2)  // 函数: CNAuraMasterBattle__vmt78 光环生效：AURA_POWER_SET 事件（转发 64C2F0）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e32; // eax

  pMem = operator new(0x64u);  // 堆分配 100 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e32 = sub_64C2F0(pMem, *(this + 32));  // 结果 = 战斗光环随从装配：BattleAuraMinion.ani/BattleAuraMinion
  else
    fld_e32 = nullptr;  // fld_e32 = nullptr 空指针
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*fld_e32 + 56))(  // 虚调用 vt+56
    fld_e32,
    nArg2,
    *(this + 1),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 212))(  // 虚槽+212 音效标签播放（szPassword 去重 → sub_65FE10 分发到 50 声道）
           nArg2,
           "AURA_POWER_SET",  // 字符串 “AURA_POWER_SET”
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64C4B0 CNATDFSPEEDUpFromAura__vmtC —— CNATDFSPEEDUpFromAura__vmtC 打开槽（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNATDFSPEEDUpFromAura__vmtC(float *this, int pArg2)  // 函数: CNATDFSPEEDUpFromAura__vmtC 打开槽（41A5E0/41A590）
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int fld_e24; // [esp+Ch] [ebp-4h]
  float fld_e26; // [esp+Ch] [ebp-4h]
  float fld_e27; // [esp+Ch] [ebp-4h]
  int fld_e242; // [esp+18h] [ebp+8h]
  int fld_e25; // [esp+18h] [ebp+8h]
  int v18; // [esp+18h] [ebp+8h]
  int v19; // [esp+18h] [ebp+8h]

  fld_e24 = (uint64_t)*(this + 24);  // this+24 页数上限
  v4 = sub_41A5E0(pArg2 + 1306);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg2 + 1306, v5, fld_e24 + v4);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_e242 = (uint64_t)*(this + 24);  // this+24 页数上限
  v6 = sub_41A5E0(pArg2 + 1334);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg2 + 1334, fld_e242, fld_e242 + v6);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_e25 = (uint64_t)*(this + 25);
  v7 = sub_41A5E0(pArg2 + 1320);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg2 + 1320, v8, fld_e25 + v7);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_e26 = *(this + 26);  // fld_e26 = this+26
  *(float *)&v18 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830)) + fld_e26;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg2 + 830, v9, v18);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_e27 = *(this + 27);  // fld_e27 = this+27
  *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fld_e27;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(pArg2 + 858, v19, v19);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v10 = sub_41A5E0(pArg2 + 760);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pArg2 + 760, v11, v10 + 32);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x64C5A0 CNAuraMasterATDFSPEEDUpFather__vmt84 —— CNAuraMasterATDFSPEEDUpFather__vmt84 受击事件槽（父王变体）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraMasterATDFSPEEDUpFather__vmt84(uint32_t **this, int nArg2)  // 函数: CNAuraMasterATDFSPEEDUpFather__vmt84 受击事件槽（父王变体）
{
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（CNAuraMasterATDFSPEEDUpFather；va=0064A790）
  bool result; // al

  result = false;
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 340))(nArg2) == 260  // 虚槽+340 三元组基址（+284，vt+340）
    || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 340))(nArg2) == 264 )  // CNAuraMasterATDFSPEEDUpFather__vmt84 受击事件槽（父王变体）
  {
    pHostObj = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 376))(*(this + 1));  // 调用虚函数槽 +376
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2) == pHostObj )  // 虚槽+376 坐标同步包（type 37）
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64C600 CNAuraMasterATDFSPEEDUp_KingGalok__vmt84 —— CNAuraMasterATDFSPEEDUp_KingGalok__vmt84 受击事件槽（王加洛克变体）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraMasterATDFSPEEDUp_KingGalok__vmt84(uint32_t *this, uint32_t *pArg2)  // 函数: CNAuraMasterATDFSPEEDUp_KingGalok__vmt84 受击事件槽（王加洛克变体）
{
  uint32_t *v2; // edx
  uint32_t *v3; // eax
  int pHostObj; // esi  | +0x0004 → 宿主对象指针（CNAuraMasterATDFSPEEDUp_KingGalok；va=0064A790）
  int v5; // edi

  v2 = (uint32_t *)pArg2[84];
  v3 = (uint32_t *)pArg2[83];
  if ( v3 == v2 )  // 若 v3 == v2
    return false;
  do
  {
    if ( *v3 == 19 )  // 若 *v3 == 19
      break;
    ++v3;  // 自增v3
  }
  while ( v3 != v2 );  // 当 v3 != v2 循环
  if ( v3 == v2 )  // 若 v3 == v2
    return false;
  pHostObj = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
  v5 = (*(int (**)(void))(*pArg2 + 376))();  // 结果 = 虚调用 vt+376
  return v5 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pHostObj + 376))(pHostObj);  // pHostObj=this+4 pHostObj
}



// ------------------------------------------------------------
// 0x64C660 CNAuraMasterATDFSPEEDUp__vmt7C —— CNAuraMasterATDFSPEEDUp__vmt7C 光环失效槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterATDFSPEEDUp__vmt7C(int nArg1)  // 函数: CNAuraMasterATDFSPEEDUp__vmt7C 光环失效槽（58 行）
{
  unsigned int i; // edi
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int pObj; // eax

  if ( nArg1 != 0 )  // 若 nArg1 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v3 = *(uint32_t *)(v2 + 4);  // v3 = v2+4
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )  // 若 (int)i >= v4
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v6 = *(uint32_t *)(v5 + 4);  // v6 = v5+4
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )  // 若 v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == nArg1 )  // 若 *(uint32_t *)(v7 + 4) == nArg1
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
        v9 = *(uint32_t *)(v8 + 4);  // v9 = v8+4
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )  // 若 v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        pObj = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNATDFSPEEDUpFromAura `RTTI Type Descriptor',
                0);
        if ( pObj != 0 )  // 若 pObj != 0
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 调用虚函数槽 +76
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64C710 sub_64C710 —— 战斗动画查询 2（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64C710(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 战斗动画查询 2（5910D0）
{
  sub_5910D0(nArg2, 18, 500, 0);  // CNRDAuraMaster 构造函数
  *(this + 32) = nArg3;  // this+128 = nArg3
  *(this + 34) = nArg5;  // this+136 = nArg5
  *this = &vftbl_CNAuraMasterATDFSPEEDUp;  // *this 写入 &vftbl_CNAuraMasterATDFSPEEDUp
  *(this + 33) = nArg4;  // this+132 = nArg4
  *(this + 35) = nArg6;  // this+140 = nArg6
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64C760 sub_64C760 —— ATDF/SPEED 随从装配：BattleAuraMinion/S/E.ani（4B1030/64A350/42FCB0/431860）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64C760(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // ATDF/SPEED 随从装配：BattleAuraMinion/S/E.ani（4B103
{
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax

  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNRDAuraMinion;  // *this 写入 &vftbl_CNRDAuraMinion
  sub_64A350(this);  // 受方表现转发
  *(this + 24) = nArg2;  // this+96 = nArg2
  *this = &vftbl_CNATDFSPEEDUpFromAura;  // *this 写入 &vftbl_CNATDFSPEEDUpFromAura
  *(this + 25) = nArg3;  // this+100 = nArg3
  *(this + 26) = nArg4;  // this+104 = nArg4
  *(this + 27) = nArg5;  // this+108 = nArg5
  v6 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v6 != 0 )  // 若 v6 != 0
    v7 = sub_431860(v6, "Common/Etc/Animation/Aura/BattleAuraMinion.ani", 1);  // 字符串 “Common/Etc/Animation/Aura/BattleAuraMinion.a”
  else
    v7 = 0;
  *(this + 21) = v7;  // this+84 = v7
  v8 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v8 != 0 )  // 若 v8 != 0
    v9 = sub_431860(v8, "Common/Etc/Animation/Aura/BattleAuraMinionS.ani", 1);  // 字符串 “Common/Etc/Animation/Aura/BattleAuraMinionS.”
  else
    v9 = 0;
  *(this + 22) = v9;  // this+88 = v9
  v10 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v10 != 0 )  // 若 v10 != 0
    v11 = sub_431860(v10, "Common/Etc/Animation/Aura/BattleAuraMinionE.ani", 1);  // 字符串 “Common/Etc/Animation/Aura/BattleAuraMinionE.”
  else
    v11 = 0;
  *(this + 23) = v11;  // this+92 = v11
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64C860 CNATDFSPEEDUpFromAura__vmt0 —— CNATDFSPEEDUpFromAura__vmt0 析构（转发 64C890）
// ------------------------------------------------------------
void */*thiscall*/ CNATDFSPEEDUpFromAura__vmt0(void *Block, char pszArg2)  // CNATDFSPEEDUpFromAura__vmt0 析构（转发 64C890）
{
  sub_64C890();  // ATDF 受方初始化（649300 系）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64C890 sub_64C890 —— ATDF 受方初始化（649300 系）
// ------------------------------------------------------------
int /*thiscall*/ sub_64C890(int this)  // 函数: ATDF 受方初始化（649300 系）
{
  *(uint32_t *)this = &vftbl_CNATDFSPEEDUpFromAura;
  return sub_649300(this);  // 召唤受方表现初始化（64A880 + 5F6640）
}



// ------------------------------------------------------------
// 0x64C8A0 CNAuraMasterATDFSPEEDUp__vmt78 —— CNAuraMasterATDFSPEEDUp__vmt78 光环生效：AURA_POWER_SET 事件（76 行转发 64C760）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterATDFSPEEDUp__vmt78(int *this, void *Block)  // 函数: CNAuraMasterATDFSPEEDUp__vmt78 光环生效：AURA_POWER_SET 事件（76 行转发 64C760）
{
  unsigned int i; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *fld_e32; // eax

  if ( Block != nullptr )  // 若 Block 非空
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);  // 调用虚函数槽 +700
      v5 = *(uint32_t *)(v4 + 4);  // v5 = v4+4
      v6 = v5 != 0 ? (*(uint32_t *)(v4 + 8) - v5) >> 2 : 0;
      if ( (int)i >= v6 )  // 若 (int)i >= v6
        break;
      v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);  // 调用虚函数槽 +700
      v8 = *(uint32_t *)(v7 + 4);  // v8 = v7+4
      if ( v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2 )  // 若 v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2
        v9 = *(uint32_t *)(v8 + 4 * i);
      else
        v9 = 0;
      if ( *(void **)(v9 + 4) == Block )  // 若 *(void **)(v9 + 4) == Block
      {
        v10 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);  // 调用虚函数槽 +700
        v11 = *(uint32_t *)(v10 + 4);  // v11 = v10+4
        if ( v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2 )  // 若 v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2
          v12 = *(uint32_t *)(v11 + 4 * i);
        else
          v12 = 0;
        result = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                   v12,
                   0,
                   &IRDAppendage `RTTI Type Descriptor',
                   &CNATDFSPEEDUpFromAura `RTTI Type Descriptor',
                   0);
        if ( result != 0 )  // 若 result != 0
          return result;
      }
    }
  }
  pMem = operator new(0x70u);  // 堆分配 112 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e32 = sub_64C760(pMem, *(this + 32), *(this + 33), *(this + 34), *(this + 35));  // 结果 = ATDF/SPEED 随从装配：BattleAuraMinion/S/E.ani（4B103
  else
    fld_e32 = nullptr;  // fld_e32 = nullptr 空指针
  (*(void (/*thiscall*/ **)(uint32_t *, void *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*fld_e32 + 56))(  // 虚调用 vt+56
    fld_e32,
    Block,
    *(this + 1),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)Block + 212))(  // 虚槽+212 音效标签播放（szPassword 去重 → sub_65FE10 分发到 50 声道）
           Block,
           "AURA_POWER_SET",  // 字符串 “AURA_POWER_SET”
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64C9F0 sub_64C9F0 —— 战斗光环查询（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64C9F0(int this)  // 函数: 战斗光环查询（15 行）
{
  *(uint8_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 3;  // this+84 = 3
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint8_t *)(this + 92) = 1;  // this+92 = 1
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x64CA10 sub_64CA10 —— 战斗光环查询 2（15 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_64CA10(int this, char pszArg2, int nArg3, int nArg4, int nArg5, char pszArg6)  // 函数: 战斗光环查询 2（15 行）
{
  *(uint8_t *)(this + 80) = pszArg2;  // this+80 = pszArg2
  *(uint32_t *)(this + 84) = nArg3;  // this+84 = nArg3
  *(uint32_t *)(this + 88) = nArg4;  // this+88 = nArg4
  *(uint32_t *)(this + 44) = nArg5;  // this+44 = nArg5
  *(uint8_t *)(this + 92) = pszArg6;  // this+92 = pszArg6
  return pszArg6;
}



// ------------------------------------------------------------
// 0x64CA40 sub_64CA40 —— 战斗光环查询 3（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64CA40(uint32_t *this)  // 函数: 战斗光环查询 3（17 行）
{
  int (/*thiscall*/ ***fld_e24)(uint32_t, int); // ecx
  int result; // eax

  fld_e24 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 24);  // this+24 页数上限
  if ( fld_e24 != nullptr )  // 若 fld_e24 非空
    result = (**fld_e24)(fld_e24, 1);
  *(this + 24) = 0;  // this+96 = 0
  return result;
}



// ------------------------------------------------------------
// 0x64CA60 CNChangeDamageBonusRate__vmtC —— CNChangeDamageBonusRate__vmtC 打开槽（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNChangeDamageBonusRate__vmtC(int this, int pArg2)  // 函数: CNChangeDamageBonusRate__vmtC 打开槽（41A5E0/41A590）
{
  int nBonusType; // eax  | +0x0054 → 加成类型（0x64CA60: *(this+84) ∈{0,3} 走物理侧、∈{1,3} 走魔法侧）（CNChangeDamageBonusRate；va=0064CA60）
  int nBonusValue; // ebx  | +0x0058 → 加成数值（0x64CA60: *(this+88) 加算进宿主 +1306/+1320/+1334/+1348）（CNChangeDamageBonusRate；va=0064CB10）
  int v5; // eax
  int v6; // edx
  int result; // eax
  unsigned int v8; // edi
  int nBonusValue_2; // ebx  | +0x0058 → 加成数值（0x64CA60: *(this+88) 加算进宿主 +1306/+1320/+1334/+1348）（CNChangeDamageBonusRate；va=0064CB10）
  int v10; // eax
  int v11; // edx
  int nBonusValue_; // esi  | +0x0058 → 加成数值（0x64CA60: *(this+88) 加算进宿主 +1306/+1320/+1334/+1348）（CNChangeDamageBonusRate；va=0064CB10）
  int v13; // eax
  int v14; // edx

  nBonusType = *(uint32_t *)(this + 84);  // 读 fld_54 = this+84（加成类型）
  if ( *(uint8_t *)(this + 80) != 0 )  // 判定 “+80 攻击加成开关”
  {
    if ( nBonusType == 0 || nBonusType == 3 )  // 若 fld_54 == 0 || fld_54 == 3
    {
      nBonusValue = *(uint32_t *)(this + 88);  // 读 fld_58 = this+88（加成数值）
      v5 = sub_41A5E0(pArg2 + 1306);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1306, v6, nBonusValue + v5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    result = *(uint32_t *)(this + 84);  // 读 result = this+84（加成类型）
    if ( result == 1 || result == 3 )  // 若 result == 1 || result == 3
    {
      v8 = pArg2 + 1334;
LABEL_14:
      nBonusValue_ = *(uint32_t *)(this + 88);  // 读 fld_582 = this+88（加成数值）
      v13 = sub_41A5E0(v8);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      return sub_41A590(v8, v14, nBonusValue_ + v13);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
  }
  else
  {
    if ( nBonusType == 0 || nBonusType == 3 )  // 若 fld_54 == 0 || fld_54 == 3
    {
      nBonusValue_2 = *(uint32_t *)(this + 88);  // 读 fld_583 = this+88（加成数值）
      v10 = sub_41A5E0(pArg2 + 1320);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590(pArg2 + 1320, v11, nBonusValue_2 + v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
    result = *(uint32_t *)(this + 84);  // 读 result = this+84（加成类型）
    if ( result == 1 || result == 3 )  // 若 result == 1 || result == 3
    {
      v8 = pArg2 + 1348;
      goto LABEL_14;  // 跳转 LABEL_14
    }
  }
  return result;  // result=this+84 nBonusType
}



// ------------------------------------------------------------
// 0x64CB10 CNChangeDamageBonusRate__vmt4 —— CNChangeDamageBonusRate__vmt4 伤害率变更：AttackPowerUp.ptl（428F30/4600B0）
// ------------------------------------------------------------
void /*thiscall*/ CNChangeDamageBonusRate__vmt4(int this)  // 函数: CNChangeDamageBonusRate__vmt4 伤害率变更：AttackPowerUp.ptl（428F30/4600B0）
{
  int *pHostObj; // edi
  uint32_t *pMem; // eax
  int *pFxObj_; // eax
  int v5; // edx
  int pFxObj; // ebx  | +0x0060 → 特效对象（0x64CB10: *(this+96)==0 时新建 AttackPowerUp.ptl 粒子对象）（CNChangeDamageBonusRate；va=0064CB10）
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int pFxObj_2; // esi  | +0x0060 → 特效对象（0x64CB10: *(this+96)==0 时新建 AttackPowerUp.ptl 粒子对象）（CNChangeDamageBonusRate；va=0064CB10）
  int v11; // eax
  void *v12; // eax
  uint8_t v13[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  void *pMem2; // [esp+14h] [ebp-10h]
  int v16; // [esp+20h] [ebp-4h]

  IRDAppendage__vmt4((int *)this);
  if ( *(uint8_t *)(this + 92) != 0 && (*(uint32_t *)(dword_8F7A24 + 12) != 4 || *(uint32_t *)(this + 4) == dword_8F7C04) )  // 全局 dword_8F7A24 = 登录/选区管理器
  {
    pHostObj = *(int **)(this + 4);  // this+4 pHostObj
    if ( *(uint8_t *)(this + 80) != 0 && *(int *)(this + 88) > 0 )  // 判定 “+80 攻击加成开关；+88 加成数值”
    {
      if ( *(uint32_t *)(this + 96) == 0 )  // 判定 “+96 特效对象”
      {
        pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
        pMem2 = pMem;
        v16 = 0;
        if ( pMem != nullptr )  // 若 pMem 非空
          pFxObj_ = sub_428F30(pMem, (int)"Common/CommonEffect/Particle/AttackPowerUp.ptl", *(uint32_t *)(this + 4));  // 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
        else
          pFxObj_ = nullptr;  // fld_42 = nullptr 空指针
        *(uint32_t *)(this + 96) = pFxObj_;  // 写 this+96 = fld_42（特效对象）
        v5 = *pFxObj_;
        v16 = -1;
        (*(void (/*thiscall*/ **)(int *, int *))(v5 + 112))(pFxObj_, pHostObj);  // 调用虚函数槽 +112
      }
      pFxObj = **(uint32_t **)(this + 96);  // this+96 pFxObj
      v7 = (*(int (/*thiscall*/ **)(int *))(*pHostObj + 128))(pHostObj);  // 结果 = 虚调用 vt+128
      v8 = (*(int (/*thiscall*/ **)(int *, int))(*pHostObj + 124))(pHostObj, v7 + 50);  // 结果 = 虚调用 vt+124
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*pHostObj + 120))(pHostObj, v8);  // 结果 = 虚调用 vt+120
      (*(void (/*thiscall*/ **)(uint32_t, int))(pFxObj + 40))(*(uint32_t *)(this + 96), v9);  // 调用虚函数槽 +40
    }
    pFxObj_2 = *(uint32_t *)(this + 96);  // 读 fld_602 = this+96（特效对象）
    if ( pFxObj_2 != 0 )  // 若 fld_602 != 0
    {
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)pFxObj_2 + 92))(pFxObj_2, v13);  // 调用虚函数槽 +92
      v11 = *pHostObj;  // fld_4=this+4 pHostObj
      v16 = 1;
      v12 = (void *)(*(int (/*thiscall*/ **)(int *))(v11 + 80))(pHostObj);  // fld_4=this+4 pHostObj
      sub_4600B0(v12, 2, 0, (int)v13);  // 调 sub_4600B0
      if ( Block != nullptr )  // 若 Block 非空
        j__free(Block);  // 调 j__free
    }
  }
}



// ============================================================
// 【分区 16】缓速光环族 CNAuraMasterSlow / CNSlowFromSlowAura（0x64CC30-0x64CF70）
// 资源 Common/Etc/Animation/Aura/SlowAuraMaster.ani；
// vmt78 生效（64CD00）、vmt7C 失效（58 行）。
// ============================================================
// ------------------------------------------------------------
// 0x64CC30 CNAuraMasterSlow__vmt1C —— CNAuraMasterSlow__vmt1C 生成装配：Common/Etc/Animation/Aura/SlowAuraMaster.ani
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterSlow__vmt1C(void *this)  // 函数: CNAuraMasterSlow__vmt1C 生成装配：Common/Etc/Animation/Aura/SlowAuraMaster.ani
{
  CNRDAuraMaster__vmt1C((int)this);  // 调 CNRDAuraMaster__vmt1C 生成装配
  return (*(int (/*thiscall*/ **)(void *, const char *))(*(uint32_t *)this + 128))(  // this+128 第 2 组·+1208 增量子倍率
           this,
           "Common/Etc/Animation/Aura/SlowAuraMaster.ani");  // 字符串 “Common/Etc/Animation/Aura/SlowAuraMaster.ani”
}



// ------------------------------------------------------------
// 0x64CC50 CNAuraMasterIce__vmt84 —— CNAuraMasterIce__vmt84 受击事件槽（4E4630）
// ------------------------------------------------------------
bool /*stdcall*/ CNAuraMasterIce__vmt84(int nArg1)  // 函数: CNAuraMasterIce__vmt84 受击事件槽（4E4630）
{
  return (uint8_t)sub_4E4630(nArg1) != 0;  // 返回 ★ 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
}



// ------------------------------------------------------------
// 0x64CC70 CNSlowFromSlowAura__vmt1C —— CNSlowFromSlowAura__vmt1C 生成装配（5F66A0）
// ------------------------------------------------------------
int /*thiscall*/ CNSlowFromSlowAura__vmt1C(int this)  // 函数: CNSlowFromSlowAura__vmt1C 生成装配（5F66A0）
{
  int result; // eax

  sub_5F66A0(this, 1);  // 调 sub_5F66A0
  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +308
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 776))(*(uint32_t *)(this + 4), 0);  // 调用虚函数槽 +776
    if ( (uint8_t)result == 0 )  // 若 (uint8_t)result == 0
      return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 760))(  // this+4 pHostObj
               0,
               *(uint32_t *)(this + 96),  // this+96 nSlowValue
               *(uint32_t *)(this + 100),  // this+100 nSlowDuration
               *(uint32_t *)(this + 4),  // this+4 pHostObj
               0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64CCC0 CNSlowFromSlowAura__vmt68 —— CNSlowFromSlowAura__vmt68 特效触发槽（24 行）
// ------------------------------------------------------------
int /*thiscall*/ CNSlowFromSlowAura__vmt68(int this)  // 函数: CNSlowFromSlowAura__vmt68 特效触发槽（24 行）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +308
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 776))(*(uint32_t *)(this + 4), 0);  // 调用虚函数槽 +776
    if ( (uint8_t)result == 0 )  // 若 (uint8_t)result == 0
      return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 760))(  // this+4 pHostObj
               0,
               *(uint32_t *)(this + 96),  // this+96 nSlowValue
               *(uint32_t *)(this + 100),  // this+100 nSlowDuration
               *(uint32_t *)(this + 4),  // this+4 pHostObj
               0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64CD00 sub_64CD00 —— 缓速受方装配（4B1030 + 64A350）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64CD00(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 缓速受方装配（4B1030 + 64A350）
{
  sub_4B1030(this);  // IRDAppendage 基类构造
  *this = &vftbl_CNRDAuraMinion;  // *this 写入 &vftbl_CNRDAuraMinion
  sub_64A350(this);  // 受方表现转发
  *(this + 25) = nArg3;  // this+100 = nArg3
  *(this + 24) = nArg2;  // this+96 = nArg2
  *this = &vftbl_CNSlowFromSlowAura;  // *this 写入 &vftbl_CNSlowFromSlowAura
  *(this + 18) = nArg4;  // this+72 = nArg4
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64CD70 CNSlowFromSlowAura__vmt0 —— CNSlowFromSlowAura__vmt0 析构（转发 64CDA0）
// ------------------------------------------------------------
void */*thiscall*/ CNSlowFromSlowAura__vmt0(void *Block, char pszArg2)  // CNSlowFromSlowAura__vmt0 析构（转发 64CDA0）
{
  sub_64CDA0();  // 缓速受方初始化（649300 系）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64CDA0 sub_64CDA0 —— 缓速受方初始化（649300 系）
// ------------------------------------------------------------
int /*thiscall*/ sub_64CDA0(int this)  // 函数: 缓速受方初始化（649300 系）
{
  *(uint32_t *)this = &vftbl_CNSlowFromSlowAura;
  return sub_649300(this);  // 召唤受方表现初始化（64A880 + 5F6640）
}



// ------------------------------------------------------------
// 0x64CDB0 CNAuraMasterSlow__vmt78 —— CNAuraMasterSlow__vmt78 光环生效（转发 64CD00）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterSlow__vmt78(int *this, int nArg2)  // 函数: CNAuraMasterSlow__vmt78 光环生效（转发 64CD00）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e32; // eax

  pMem = operator new(0x68u);  // 堆分配 104 字节对象
  if ( pMem != nullptr )  // 若 pMem 非空
    fld_e32 = sub_64CD00(pMem, *(this + 32), *(this + 33), *(this + 34));  // 结果 = 缓速受方装配（4B1030 + 64A350）
  else
    fld_e32 = nullptr;  // fld_e32 = nullptr 空指针
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*fld_e32 + 56))(  // 虚调用 vt+56
           fld_e32,
           nArg2,
           *(this + 1),
           0,
           0,
           0,
           -1);
}



// ------------------------------------------------------------
// 0x64CE40 CNAuraMasterSlow__vmt7C —— CNAuraMasterSlow__vmt7C 光环失效槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterSlow__vmt7C(int nArg1)  // 函数: CNAuraMasterSlow__vmt7C 光环失效槽（58 行）
{
  unsigned int i; // edi
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int pObj; // eax

  if ( nArg1 != 0 )  // 若 nArg1 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v3 = *(uint32_t *)(v2 + 4);  // v3 = v2+4
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )  // 若 (int)i >= v4
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
      v6 = *(uint32_t *)(v5 + 4);  // v6 = v5+4
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )  // 若 v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == nArg1 )  // 若 *(uint32_t *)(v7 + 4) == nArg1
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 700))(nArg1);  // 调用虚函数槽 +700
        v9 = *(uint32_t *)(v8 + 4);  // v9 = v8+4
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )  // 若 v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        pObj = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNSlowFromSlowAura `RTTI Type Descriptor',
                0);
        if ( pObj != 0 )  // 若 pObj != 0
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 调用虚函数槽 +76
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64CEF0 sub_64CEF0 —— 缓速动画查询（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64CEF0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 缓速动画查询（5910D0）
{
  sub_5910D0(nArg2, 18, 500, 0);  // CNRDAuraMaster 构造函数
  *(this + 34) = nArg3;  // this+136 = nArg3
  *this = &vftbl_CNAuraMasterSlow;  // *this 写入 &vftbl_CNAuraMasterSlow
  *(this + 32) = nArg4;  // this+128 = nArg4
  *(this + 33) = nArg5;  // this+132 = nArg5
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64CF30 CNAuraMasterSlow__vmt0 —— CNAuraMasterSlow__vmt0 析构（转发 64CF60）
// ------------------------------------------------------------
void */*thiscall*/ CNAuraMasterSlow__vmt0(void *Block, char pszArg2)  // CNAuraMasterSlow__vmt0 析构（转发 64CF60）
{
  sub_64CF60();  // 缓速光环析构成员（591190）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64CF60 sub_64CF60 —— 缓速光环析构成员（591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_64CF60(uint32_t *this)  // 函数: 缓速光环析构成员（591190）
{
  *this = &vftbl_CNAuraMasterSlow;  // *this 写入 &vftbl_CNAuraMasterSlow
  return sub_591190(this);  // CNRDAuraMaster 析构函数
}



// ------------------------------------------------------------
// 0x64CF70 sub_64CF70 —— 缓速辅助（41A590）
// ------------------------------------------------------------
int /*fastcall*/ sub_64CF70(int pArg1, int nArg2)  // 缓速辅助（41A590）
{
  int v3; // edx
  int v4; // edx
  int result; // eax

  sub_41A590(pArg1 + 84, nArg2, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(pArg1 + 98, v3, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  result = sub_41A590(pArg1 + 112, v4, 0);  // 结果 = crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint8_t *)(pArg1 + 141) = 0;  // pArg1+141 = 0
  *(uint8_t *)(pArg1 + 142) = 0;  // pArg1+142 = 0
  *(uint32_t *)(pArg1 + 156) = 0;  // pArg1+156 = 0
  *(uint32_t *)(pArg1 + 160) = 0;  // pArg1+160 = 0
  *(uint8_t *)(pArg1 + 181) = 0;  // pArg1+181 = 0
  *(uint8_t *)(pArg1 + 182) = 0;  // pArg1+182 = 0
  *(uint8_t *)(pArg1 + 209) = 0;  // pArg1+209 = 0
  *(uint8_t *)(pArg1 + 210) = 0;  // pArg1+210 = 0
  *(uint8_t *)(pArg1 + 237) = 0;  // pArg1+237 = 0
  *(uint8_t *)(pArg1 + 238) = 0;  // pArg1+238 = 0
  *(uint8_t *)(pArg1 + 265) = 0;  // pArg1+265 = 0
  *(uint8_t *)(pArg1 + 266) = 0;  // pArg1+266 = 0
  *(uint8_t *)(pArg1 + 293) = 0;  // pArg1+293 = 0
  *(uint8_t *)(pArg1 + 294) = 0;  // pArg1+294 = 0
  *(uint8_t *)(pArg1 + 321) = 0;  // pArg1+321 = 0
  *(uint8_t *)(pArg1 + 322) = 0;  // pArg1+322 = 0
  *(uint8_t *)(pArg1 + 349) = 0;  // pArg1+349 = 0
  *(uint8_t *)(pArg1 + 350) = 0;  // pArg1+350 = 0
  *(uint8_t *)(pArg1 + 377) = 0;  // pArg1+377 = 0
  *(uint8_t *)(pArg1 + 378) = 0;  // pArg1+378 = 0
  *(uint8_t *)(pArg1 + 405) = 0;  // pArg1+405 = 0
  *(uint8_t *)(pArg1 + 406) = 0;  // pArg1+406 = 0
  *(uint8_t *)(pArg1 + 433) = 0;  // pArg1+433 = 0
  *(uint8_t *)(pArg1 + 434) = 0;  // pArg1+434 = 0
  return result;
}



// ============================================================
// 【分区 17】暗黑火炸弹 CNFireBomb（0x64D030-0x64D880）
// 资源 DarkFire.ani/DarkFireAura.ani/DarkFireExp.ani（64D510 装配）；
// vmt14=爆炸流程（90 行）、vmt24/vmt4=回收。
// ============================================================
// ------------------------------------------------------------
// 0x64D030 CNFireBomb__vmt1C —— CNFireBomb__vmt1C 生成装配（698F90/41A590）
// ------------------------------------------------------------
char /*thiscall*/ CNFireBomb__vmt1C(int this)  // 函数: CNFireBomb__vmt1C 生成装配（698F90/41A590）
{
  int v2; // edx

  sub_698F90(this + 168, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  sub_41A590(this + 112, v2, 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  *(uint8_t *)(this + 141) = 0;  // 写 this+141 = 0（淡出标志 A）
  *(uint8_t *)(this + 142) = 0;  // 写 this+142 = 0（淡出标志 B）
  return sub_698F90(this + 128, *(uint32_t *)(this + 80), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x64D070 CNFireBomb__vmt14 —— CNFireBomb__vmt14 爆炸流程（90 行：4049C0/491DE0/699000/493A60/4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNFireBomb__vmt14(int this, char pszArg2, int nArg3, int nArg4, float fArg5)  // 函数: CNFireBomb__vmt14 爆炸流程（90 行：4049C0/491DE0/699000/493A60/4938F0/491D00）
{
  int pThis_702; // eax
  int pThis_62; // ebx
  int pThis_70; // eax
  int pThis_622; // ebx
  uint8_t v10; // bl
  int v11; // edi
  int pThis_80; // eax
  int v13; // edi
  int dword_79C0B02; // [esp-28h] [ebp-30h]
  int v16; // [esp-Ch] [ebp-14h]
  int nLifeMs; // [esp-Ch] [ebp-14h]  | +0x0050 → 存活时长 ms（0x64D480: sub_698F90(this+128, *(this+80)) 倒计时时长）（CNFireBomb；va=0064D480）
  int pThis_6222; // [esp+10h] [ebp+8h]
  int pHostObj; // [esp+14h] [ebp+Ch]  | +0x0004 → 宿主对象指针（CNFireBomb；va=0064D480）
  int v20; // [esp+18h] [ebp+10h]
  int pThis_A8; // [esp+1Ch] [ebp+14h]

  LOBYTE(pThis_702) = pszArg2;
  if ( pszArg2 != 0 )  // 若 pszArg2 != 0
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4)) == 0  // 判定 “+4 宿主对象指针”
      && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) != 0 )  // CNFireBomb__vmt14 爆炸流程（90 行：4049C0/491DE0/699000/493A60/4938F0/491D00）
    {
      pThis_62 = sub_41A5E0(this + 98);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      pThis_70 = sub_41A5E0(this + 112);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      v16 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 200.0, pThis_70, pThis_62) << 24) | 0xFFFFFF;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      dword_79C0B02 = dword_79C0B0;  // dword_79C0B0（文本/图像绘制对象）
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +200
      sub_491DE0(dword_79C0B02, nArg3, nArg4, fArg5, 2, 1, -16776961, v16);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
    }
    pThis_622 = nArg3 + (15 - 15 * sub_41A5E0(this + 98)) / 2;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    pHostObj = nArg4
        - (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))
                           * *(float *)&dword_77F6DC)
        - 20;
    v20 = 0;
    pThis_702 = sub_41A5E0(this + 112);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( pThis_702 > 0 )  // 若 pThis_702 > 0
    {
      pThis_6222 = pThis_622;
      pThis_A8 = this + 168;  // this+168 附属对象向量 begin
      do
      {
        v10 = -1;
        v11 = sub_699000(pThis_A8);  // 【clock_now(clk)】
        sub_493A60(*(uint32_t *)(this + 156), v11);  // 时间推进包装（累计 +32；+212 同步源优先）
        sub_4938F0(*(uint32_t *)(this + 156));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        sub_493A60(*(uint32_t *)(this + 160), v11);  // 时间推进包装（累计 +32；+212 同步源优先）
        sub_4938F0(*(uint32_t *)(this + 160));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        if ( v11 < 200 )  // 若 v11 < 200
          v10 = (uint64_t)sub_4049C0(0.0, 255.0, v11, 200);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        sub_493A60(*(uint32_t *)(this + 164), v11);  // 时间推进包装（累计 +32；+212 同步源优先）
        sub_4938F0(*(uint32_t *)(this + 164));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        if ( *(uint8_t *)(*(uint32_t *)(this + 164) + 170) == 0 )  // 判定 “+164 爆炸动画件 C”
          sub_491D00(dword_79C0B0, pThis_6222, pHostObj, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        if ( v20 >= sub_41A5E0(this + 112) - 2  // crypt4byte 解密校验（·0x41A590 逆运算）
          && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 44))(*(uint32_t *)(this + 4)) == 273 )
        {
          nLifeMs = *(uint32_t *)(this + 80);  // 读 fld_50 = this+80（存活时长 ms）
          pThis_80 = sub_699000(this + 128);  // 【clock_now(clk)】
          v10 = (uint64_t)(sub_4049C0(1.0, 0.0, pThis_80, nLifeMs) * (double)v10);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        }
        if ( v10 == 0xFF )  // 若 v10 == 0xFF
        {
          sub_491D00(dword_79C0B0, pThis_6222, pHostObj, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          sub_491D00(dword_79C0B0, pThis_6222, pHostObj, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        }
        else
        {
          v13 = (v10 << 24) | 0xFFFFFF;
          sub_491DE0(dword_79C0B0, pThis_6222, pHostObj, 0.0, 0, 0, 0, v13);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
          sub_491DE0(dword_79C0B0, pThis_6222, pHostObj, 0.0, 2, 0, 0, v13);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
        }
        ++v20;  // 自增v20
        pThis_A8 += 28;  // pThis_A8=this+168 附属对象向量 begin
        pThis_6222 += 15;
        pThis_702 = sub_41A5E0(this + 112);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      }
      while ( v20 < pThis_702 );  // 当 v20 < pThis_702 循环
    }
  }
  return pThis_702;
}



// ------------------------------------------------------------
// 0x64D310 sub_64D310 —— 暗黑火表现（698F90/41A5E0/41A590 + 49C620/4E4A50/424120，60 行）
// ------------------------------------------------------------
char /*usercall*/ sub_64D310@<al>(int pArg1@<ecx>, int nArg2@<edi>)  // 函数: 暗黑火表现（698F90/41A5E0/41A590 + 49C620/4E4A50/424120，60 行）
{
  char result; // al
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // edi
  int pObj; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // [esp-1Ch] [ebp-20h]
  int v14; // [esp-18h] [ebp-1Ch]

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 80))(pArg1);  // 调用虚函数槽 +80
  if ( result != 0 )  // 若 result != 0
  {
    *(uint8_t *)(pArg1 + 141) = 0;  // pArg1+141 = 0
    *(uint8_t *)(pArg1 + 142) = 0;  // pArg1+142 = 0
    sub_698F90(pArg1 + 128, *(uint32_t *)(pArg1 + 80), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    v4 = pArg1 + 28 * (sub_41A5E0(pArg1 + 112) + 6);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    *(uint8_t *)(v4 + 13) = 0;  // v4+13 = 0
    *(uint8_t *)(v4 + 14) = 0;  // v4+14 = 0
    v5 = sub_41A5E0(pArg1 + 112);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_698F90(pArg1 + 28 * (v5 + 6), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    v6 = sub_41A5E0(pArg1 + 112);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(pArg1 + 112, v7, v6 + 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    v8 = sub_41A5E0(pArg1 + 112);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    if ( v8 == sub_41A5E0(pArg1 + 98) && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 80))(pArg1) == 1 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(pArg1 + 4) + 308))(*(uint32_t *)(pArg1 + 4), nArg2) == 1 )
      {
        if ( *(uint8_t *)(*(uint32_t *)(pArg1 + 4) + 7093) == 1 )  // 若 *(uint8_t *)(*(uint32_t *)(pArg1 + 4) + 7093) == 1
          sub_49C620(1, 0, 0);  // 命令下发包装（组 id = this+4，值重复两遍）
        pObj = *(uint32_t *)(pArg1 + 4);  // pObj = pArg1+4
        v10 = sub_41A5E0(pArg1 + 84);  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) - 10;  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 调用虚函数槽 +124
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 调用虚函数槽 +120
        sub_4E4A50(0, 40008, v10, v11, v13, v14, 4, 0, 0, 0);  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
        v12 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 4) + 80))(*(uint32_t *)(pArg1 + 4));  // 调用虚函数槽 +80
        sub_424120(*(uint32_t **)(v12 + 132), 8, 500);  // [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 76))(pArg1, 0);  // 调用虚函数槽 +76
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x64D440 CNFireBomb__vmt24 —— CNFireBomb__vmt24 槽（20 行）
// ------------------------------------------------------------
int /*thiscall*/ CNFireBomb__vmt24(void *this, int nArg2, int nArg3, int nArg4)  // 函数: CNFireBomb__vmt24 槽（20 行）
{
  int result; // eax

  result = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
             nArg2,
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &CNShootingStarExp `RTTI Type Descriptor',
             0);
  if ( result != 0 )  // 若 result != 0
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 76))(this, 0);  // 调用虚函数槽 +76
  return result;
}



// ------------------------------------------------------------
// 0x64D480 CNFireBomb__vmt4 —— CNFireBomb__vmt4 复位（699000/41A5E0/41A590/698F90）
// ------------------------------------------------------------
char /*thiscall*/ CNFireBomb__vmt4(int this)  // 函数: CNFireBomb__vmt4 复位（699000/41A5E0/41A590/698F90）
{
  int nFrameCount; // edi  | +0x0098 → 爆炸帧数（0x64D480: clock_now(this+128) >= *(this+152) 判到期）（CNFireBomb；va=0064D480）
  int pThis_80; // eax
  int v4; // edx
  int pThis_70; // eax

  IRDAppendage__vmt4((int *)this);
  nFrameCount = *(uint32_t *)(this + 152);  // 读 fld_98 = this+152（爆炸帧数）
  pThis_80 = sub_699000(this + 128);  // 【clock_now(clk)】
  if ( pThis_80 >= nFrameCount )  // 若 pThis_80 >= fld_98
  {
    pThis_80 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 44))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +44
    if ( pThis_80 == 273 )  // 若 pThis_80 == 273
    {
      if ( sub_41A5E0(this + 112) - 2 >= 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
        pThis_70 = sub_41A5E0(this + 112) - 2;  // 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      else
        pThis_70 = 0;
      sub_41A590(this + 112, v4, pThis_70);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      if ( sub_41A5E0(this + 112) != 0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
      {
        *(uint8_t *)(this + 141) = 0;  // 写 this+141 = 0（淡出标志 A）
        *(uint8_t *)(this + 142) = 0;  // 写 this+142 = 0（淡出标志 B）
        LOBYTE(pThis_80) = sub_698F90(this + 128, *(uint32_t *)(this + 80), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      else
      {
        LOBYTE(pThis_80) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 76))(this, 0);  // this+76 纹章路径串
      }
    }
  }
  return pThis_80;
}



// ------------------------------------------------------------
// 0x64D510 sub_64D510 —— 装载 DarkFire.ani/DarkFireAura.ani/DarkFireExp.ani（41A590/42FCB0/431860）
// ------------------------------------------------------------
int /*fastcall*/ sub_64D510(uint32_t *pArg1, int nArg2, int nArg3, int nArg4, int nArg5)  // 装载 DarkFire.ani/DarkFireAura.ani/DarkFireExp.ani（41A590/42FCB0/431860）
{
  int nArg32; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int result; // eax

  nArg32 = nArg3;
  if ( nArg3 >= 10 )  // 若 nArg3 >= 10
    nArg32 = 10;
  sub_41A590((unsigned int)pArg1 + 98, nArg2, nArg32);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  pArg1[20] = nArg4;
  sub_41A590((unsigned int)(pArg1 + 21), v7, nArg5);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v8 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v8 != 0 )  // 若 v8 != 0
    v9 = sub_431860(v8, "Common/CommonEffect/Animation/DarkFire.ani", 1);  // 字符串 “Common/CommonEffect/Animation/DarkFire.ani”
  else
    v9 = 0;
  pArg1[39] = v9;
  v10 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v10 != 0 )  // 若 v10 != 0
    v11 = sub_431860(v10, "Common/CommonEffect/Animation/DarkFireAura.ani", 1);  // 字符串 “Common/CommonEffect/Animation/DarkFireAura.a”
  else
    v11 = 0;
  pArg1[40] = v11;
  v12 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v12 != 0 )  // 若 v12 != 0
    result = sub_431860(v12, "Common/CommonEffect/Animation/DarkFireExp.ani", 1);  // 字符串 “Common/CommonEffect/Animation/DarkFireExp.an”
  else
    result = 0;
  pArg1[41] = result;
  return result;
}



// ------------------------------------------------------------
// 0x64D610 sub_64D610 —— 暗黑火受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D610(void ***this)  // 函数: 暗黑火受击（42AF90/657740）
{
  int fld_e39; // edi
  int result; // eax
  void **fld_e40; // edi
  void **fld_e41; // edi

  fld_e39 = (int)*(this + 39);
  if ( fld_e39 != 0 )  // 若 fld_e39 != 0
  {
    sub_42AF90(*(this + 39));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e39, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_e40 = *(this + 40);  // fld_e40 = this+40
  *(this + 39) = nullptr;  // this+156 = nullptr
  if ( fld_e40 != nullptr )  // 若 fld_e40 非空
  {
    sub_42AF90(fld_e40);  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e40, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_e41 = *(this + 41);  // fld_e41 = this+41
  *(this + 40) = nullptr;  // this+160 = nullptr
  if ( fld_e41 != nullptr )  // 若 fld_e41 非空
  {
    sub_42AF90(fld_e41);  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e41, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 41) = nullptr;  // this+164 = nullptr
  return result;
}



// ------------------------------------------------------------
// 0x64D6A0 sub_64D6A0 —— 暗黑火装配（4B1030/41A630/64CF70/64D510）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D6A0(int this, int nArg2, int nArg3, int nArg4)  // 函数: 暗黑火装配（4B1030/41A630/64CF70/64D510）
{
  int v5; // edx

  sub_4B1030(this);  // IRDAppendage 基类构造
  *(uint32_t *)this = &vftbl_CNFireBomb;
  sub_41A630(this + 84);  // 调 sub_41A630
  *(uint32_t *)(this + 84) = &vftbl_clong;  // this+84 = &vftbl_clong
  sub_41A630(this + 98);  // 调 sub_41A630
  *(uint32_t *)(this + 98) = &vftbl_clong;  // this+98 = &vftbl_clong
  sub_41A630(this + 112);  // 调 sub_41A630
  *(uint32_t *)(this + 112) = &vftbl_clong;  // this+112 = &vftbl_clong
  *(uint8_t *)(this + 132) = 0;  // this+132 = 0
  *(uint32_t *)(this + 128) = &vftbl_nengine__CNTimer;  // this+128 = &vftbl_nengine__CNTimer
  *(uint32_t *)(this + 136) = 0;  // this+136 = 0
  *(uint8_t *)(this + 140) = 1;  // this+140 = 1
  *(uint8_t *)(this + 142) = 0;  // this+142 = 0
  *(uint8_t *)(this + 141) = 0;  // this+141 = 0
  *(uint32_t *)(this + 152) = 0;  // this+152 = 0
  *(uint32_t *)(this + 148) = 0;  // this+148 = 0
  *(uint32_t *)(this + 144) = 0;  // this+144 = 0
  `eh vector constructor iterator'((void *)(this + 168), 0x1Cu, 10, sub_401170, sub_401000);  // 调 nengine::CNTimer 计时子对象构造（挂 off_6C2B88 = CNTimer::vftable，+12 置 1）
  sub_64CF70(this, v5);  // 缓速辅助（41A590）
  sub_64D510((uint32_t *)this, nArg3, nArg2, nArg3, nArg4);  // 装载 DarkFire.ani/DarkFireAura.ani/DarkFireExp.a
  return this;  // 返回自身指针
}



// ------------------------------------------------------------
// 0x64D7A0 CNFireBomb__vmt0 —— CNFireBomb__vmt0 析构（转发 64D7D0）
// ------------------------------------------------------------
void */*thiscall*/ CNFireBomb__vmt0(void *Block, char pszArg2)  // CNFireBomb__vmt0 析构（转发 64D7D0）
{
  sub_64D7D0();  // 暗黑火析构成员（64D610 + 41A580/5F6640）
  if ( (pszArg2 & 1) != 0 )  // 若 (pszArg2 & 1) != 0
    j__free(Block);  // 调 j__free
  return Block;
}



// ------------------------------------------------------------
// 0x64D7D0 sub_64D7D0 —— 暗黑火析构成员（64D610 + 41A580/5F6640）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D7D0(int this)  // 函数: 暗黑火析构成员（64D610 + 41A580/5F6640）
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNFireBomb;
  sub_64D610((void ***)this);  // 暗黑火受击（42AF90/657740）
  `eh vector destructor iterator'((void *)(this + 168), 0x1Cu, 10, sub_401000);  // 调 【基础设施：nengine::IObject 构造/析构桩 + MSVC std::s…】
  *(uint32_t *)(this + 128) = &vftbl_nengine__IObject;  // this+128 = &vftbl_nengine__IObject
  *(uint8_t *)(this + 132) = 0;  // this+132 = 0
  sub_41A580(this + 112);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 98);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 84);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);  // 调 sub_5F6640
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;  // this+8 = &vftbl_nengine__IObject
  *(uint8_t *)(this + 12) = 0;  // this+12 = 0
  return result;
}



// ============================================================
// 【分区 18】鞭挞与跟随（0x64D880-0x64EB30）
// CNWhipped 鞭挞（vmt1C 136 行 AttackPowerUp.ptl + 64E260 主循环）；
// CNFollowMe 跟随（64E960 装载 Character/Mage/Effect/Animation/FollowMeFlag1-3.ani）。
// ============================================================
// ------------------------------------------------------------
// 0x64D880 sub_64D880 —— 鞭挞数据（18 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D880(int this)  // 函数: 鞭挞数据（18 行）
{
  *(uint8_t *)(this + 80) = 0;  // this+80 = 0
  *(uint32_t *)(this + 84) = 0;  // this+84 = 0
  *(uint32_t *)(this + 88) = 0;  // this+88 = 0
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 104) = 0;  // this+104 = 0
  *(uint32_t *)(this + 108) = 0;  // this+108 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x64D8A0 CNWhipped__vmtC —— CNWhipped__vmtC 打开槽（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNWhipped__vmtC(float *this, int pArg2)  // 函数: CNWhipped__vmtC 打开槽（41A5E0/41A590）
{
  unsigned int v4; // edi
  int v5; // edx
  int v6; // edx
  float fld_e21; // [esp+Ch] [ebp-4h]
  float fld_e22; // [esp+Ch] [ebp-4h]
  int v10; // [esp+18h] [ebp+8h]
  int v11; // [esp+18h] [ebp+8h]

  v4 = pArg2 + 830;
  fld_e21 = *(this + 21);  // fld_e21 = this+21
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830)) + fld_e21;  // crypt4byte 解密校验（·0x41A590 逆运算）
  sub_41A590(v4, v5, v10);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_e22 = *(this + 22);  // fld_e22 = this+22
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fld_e22;  // crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A590(pArg2 + 858, v6, v11);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
}



// ------------------------------------------------------------
// 0x64D910 sub_64D910 —— 鞭挞数据 2（20 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D910(uint32_t *this)  // 函数: 鞭挞数据 2（20 行）
{
  *(this + 20) = 0;  // this+80 = 0
  *(this + 21) = 0;  // this+84 = 0
  *(this + 22) = 0;  // this+88 = 0
  *(this + 23) = 0;  // this+92 = 0
  *(this + 24) = 0;  // this+96 = 0
  *(this + 25) = 0;  // this+100 = 0
  *(this + 26) = 0;  // this+104 = 0
  *(this + 27) = 0;  // this+108 = 0
  *(this + 29) = 0;  // this+116 = 0
  *(this + 30) = 0;  // this+120 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x64D940 sub_64D940 —— 鞭挞数据 3（47E720/47EF20）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D940(int this, int nArg2)  // 函数: 鞭挞数据 3（47E720/47EF20）
{
  int result; // eax

  sub_47E720(3, 30);  // 调 sub_47E720
  *(uint32_t *)(this + 84) = sub_47EF20(1, nArg2, -1, -1, 11);  // this+84 = sub_47EF20(1, nArg2, -1, -1, 11)
  *(float *)(this + 88) = (double)(int)sub_47EF20(2, nArg2, -1, -1, 11) * 0.001;  // this+88 = (double)(int)sub_47EF20(2, nArg2, -1, -1, ..
  *(float *)(this + 92) = (double)(int)sub_47EF20(3, nArg2, -1, -1, 11) * 0.001;  // this+92 = (double)(int)sub_47EF20(3, nArg2, -1, -1, ..
  *(uint32_t *)(this + 100) = sub_47EF20(4, nArg2, -1, -1, 11);  // this+100 = sub_47EF20(4, nArg2, -1, -1, 11)
  *(uint32_t *)(this + 104) = sub_47EF20(5, nArg2, -1, -1, 11);  // this+104 = sub_47EF20(5, nArg2, -1, -1, 11)
  result = sub_47EF20(6, nArg2, -1, -1, 11);  // 调 sub_47EF20
  *(float *)(this + 96) = (double)result * 0.001;  // this+96 = (double)result * 0.001
  return result;
}



// ------------------------------------------------------------
// 0x64DA00 CNFollowMe__vmtC —— CNFollowMe__vmtC 打开槽（4D8FE0 + 41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNFollowMe__vmtC(int this, int pArg2)  // 函数: CNFollowMe__vmtC 打开槽（4D8FE0 + 41A5E0/41A590）
{
  int pFollowTarget; // eax  | +0x0050 → 跟随目标对象（CNFollowMe；va=0064DA00）
  int pFollowTarget_; // eax  | +0x0050 → 跟随目标对象（CNFollowMe；va=0064DA00）
  uint32_t *pFollowTarget_2; // ecx
  int result; // eax
  unsigned int v8; // edi
  int v9; // edx
  int v10; // edx
  float fld_502; // [esp+4h] [ebp-8h]  | +0x0050 → 跟随目标对象（CNFollowMe；va=0064DA00）
  float fSpeedAddX; // [esp+4h] [ebp-8h]  | +0x0058 → X 速度加值（0x64DA00: sub_41A590(pArg2+830, +88) 累加）（CNFollowMe；va=0064DA00）
  float fSpeedAddY; // [esp+4h] [ebp-8h]  | +0x005C → Y 速度加值（0x64DA00: sub_41A590(pArg2+858, +92) 累加）（CNFollowMe；va=0064DA00）
  int v14; // [esp+14h] [ebp+8h]
  int v15; // [esp+14h] [ebp+8h]

  pFollowTarget = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 1032))(*(uint32_t *)(this + 80)) + 16);  // this+80 pFollowTarget 等2字段
  if ( pFollowTarget != 0 )  // 若 fld_50 != 0
  {
    fld_502 = (float)(*(int (/*thiscall*/ **)(uint32_t, int, uint32_t))(**(uint32_t **)(this + 80) + 8))(  // this+80 pFollowTarget
                   *(uint32_t *)(this + 80),  // this+80 pFollowTarget
                   pFollowTarget,
                   0);
    if ( (double)sub_4D8FE0(*(uint32_t *)(this + 80)) * 0.5 < fld_502 )  // 若 (double)sub_4D8FE0(*(uint32_t *)(this + 80)) * 0.5 < fld_502
    {
      pFollowTarget_ = *(uint32_t *)(this + 80);  // 读 fld_503 = this+80（跟随目标对象）
      if ( pFollowTarget_ != 0 && (*(int (**)(void))(*(uint32_t *)pFollowTarget_ + 840))() == 0 )  // 若 fld_503 != 0 && (*(int (**)(void))(*(uint32_t *)fld_503 + 840)..
      {
        pFollowTarget_2 = *(uint32_t **)(this + 80);  // this+80 pFollowTarget
        if ( pFollowTarget_2[1787] != 24 )  // 若 fld_504[1787] != 24
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*pFollowTarget_2 + 1104))(pFollowTarget_2, 24);  // 虚调用 vt+1104
      }
    }
  }
  result = *(uint32_t *)(this + 108);  // 读 result = this+108（跟随标志）
  if ( result != 0 )  // 若 result != 0
  {
    v8 = pArg2 + 830;
    fSpeedAddX = *(float *)(this + 88);  // 读 fld_58 = this+88（X 速度加值）
    *(float *)&v14 = COERCE_FLOAT(sub_41A5E0(pArg2 + 830)) + fSpeedAddX;  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(v8, v9, v14);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    fSpeedAddY = *(float *)(this + 92);  // 读 fld_5C = this+92（Y 速度加值）
    *(float *)&v15 = COERCE_FLOAT(sub_41A5E0(pArg2 + 858)) + fSpeedAddY;  // crypt4byte 解密校验（·0x41A590 逆运算）
    return sub_41A590(pArg2 + 858, v10, v15);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  return result;  // result=this+108 nFollowFlag
}



// ------------------------------------------------------------
// 0x64DAF0 CNFollowMe__vmt14 —— CNFollowMe__vmt14 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNFollowMe__vmt14(int this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 函数: CNFollowMe__vmt14 生成槽（4938F0/491D00）
{
  char result; // al
  int pFollowTarget; // eax  | +0x0050 → 跟随目标对象（CNFollowMe；va=0064DA00）

  result = pszArg2;
  if ( pszArg2 != 0 )  // 若 pszArg2 != 0
  {
    sub_4938F0(*(uint32_t *)(this + 4 * (*(uint8_t *)(*(uint32_t *)(this + 116) + 170) != 0) + 116));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    pFollowTarget = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 192))(*(uint32_t *)(this + 80));  // 调用虚函数槽 +192
    return sub_491D00(dword_79C0B0, nArg3, nArg4 - pFollowTarget, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  }
  return result;
}



// ------------------------------------------------------------
// 0x64DB50 CNWhipped__vmt14 —— CNWhipped__vmt14 生成槽（699000/42B420/491690）
// ------------------------------------------------------------
char /*thiscall*/ CNWhipped__vmt14(int this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 函数: CNWhipped__vmt14 生成槽（699000/42B420/491690）
{
  uint32_t **fld_4; // eax
  uint32_t **fld_42; // ebx
  int nDurationMs; // esi  | +0x0068 → 持续时间 ms（CNWhipped；va=0064DB50）
  int pThis_8; // eax
  int v10; // edi
  uint32_t *v11; // esi

  LOBYTE(fld_4) = pszArg2;
  if ( pszArg2 == 0 )  // 若 pszArg2 == 0
  {
    fld_4 = (uint32_t **)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));  // this+4 pHostObj 等2字段
    fld_42 = fld_4;
    if ( fld_4 != nullptr )  // 若 fld_4 非空
    {
      nDurationMs = *(uint32_t *)(this + 104);  // 读 fld_68 = this+104（持续时间 ms）
      pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
      v10 = ((uint8_t)sub_42B420(nDurationMs / 3, nDurationMs, pThis_8, 250) << 24) | 0xFFFFFF;  // 结果 = 往返插值（三角波）
      sub_491690(1, 2, 1, -16776961, v10, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
      fld_4 = (uint32_t **)fld_42[51];
      v11 = *fld_4;
      if ( *fld_4 != fld_4 )  // 若 *fld_4 != fld_4
      {
        do
        {
          LOBYTE(fld_4) = sub_491690(1, 2, 1, -16776961, v10, 1);  // 图层后处理配置（this+176..196 图层参数块写入）
          v11 = (uint32_t *)*v11;
        }
        while ( v11 != fld_42[51] );  // 当 v11 != fld_42[51] 循环
      }
    }
  }
  return (char)fld_4;
}



// ------------------------------------------------------------
// 0x64DC00 sub_64DC00 —— 鞭挞数据 4（47E720/47EF20/47E9D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_64DC00(int this, char pszArg2, int nArg3)  // 函数: 鞭挞数据 4（47E720/47EF20/47E9D0）
{
  int result; // eax

  *(uint8_t *)(this + 80) = pszArg2;  // this+80 = pszArg2
  sub_47E720(3, 20);  // 调 sub_47E720
  *(uint32_t *)(this + 44) = sub_47EF20(0, nArg3, -1, -1, 11);  // this+44 = sub_47EF20(0, nArg3, -1, -1, 11)
  if ( pszArg2 != 0 )  // 若 pszArg2 != 0
  {
    *(float *)(this + 84) = (double)(int)sub_47EF20(1, nArg3, -1, -1, 11) * 0.001;  // this+84 = (double)(int)sub_47EF20(1, nArg3, -1, -1, ..
    *(float *)(this + 88) = (double)(int)sub_47EF20(2, nArg3, -1, -1, 11) * 0.001;  // this+88 = (double)(int)sub_47EF20(2, nArg3, -1, -1, ..
    *(uint32_t *)(this + 96) = sub_47EF20(3, nArg3, -1, -1, 11);  // this+96 = sub_47EF20(3, nArg3, -1, -1, 11)
    *(uint32_t *)(this + 100) = sub_47EF20(4, nArg3, -1, -1, 11);  // this+100 = sub_47EF20(4, nArg3, -1, -1, 11)
    result = sub_47EF20(5, nArg3, -1, -1, 11);  // 调 sub_47EF20
    *(float *)(this + 92) = (double)result * 0.0099999998;  // this+92 = (double)result * 0.0099999998
  }
  else
  {
    *(float *)(this + 84) = (double)(int)sub_47EF20(6, nArg3, -1, -1, 11) * 0.001;  // this+84 = (double)(int)sub_47EF20(6, nArg3, -1, -1, ..
    result = sub_47EF20(7, nArg3, -1, -1, 11);  // 调 sub_47EF20
    *(float *)(this + 88) = (double)result * 0.001;  // this+88 = (double)result * 0.001
  }
  if ( dword_795FD4 == -1 )  // 若 dword_795FD4 == -1
  {
    dword_795FD4 = 200 / sub_47E9D0(0);  // 调 收招/结束例程
    result = 200 / sub_47E9D0(1);  // 调 收招/结束例程
    dword_795FD8 = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64DD40 sub_64DD40 —— 鞭挞主数据（52 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64DD40(int this, char pszArg2)  // 鞭挞主数据
{
  unsigned int v2; // edi
  int fld_4; // ebx  | +0x0004 → 宿主对象指针（CNWhipped；va=0064DB50）
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // esi
  uint32_t *result; // eax
  int v11; // [esp+Ch] [ebp-8h]
  uint32_t *v12; // [esp+10h] [ebp-4h]

  v2 = 0;
  fld_4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 700))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +700
  v12 = nullptr;  // v12 = nullptr 空指针
  v11 = 0;
  while ( 1 )  // 当 1 循环
  {
    v4 = *(uint32_t *)(fld_4 + 4);  // v4 = fld_4+4
    v5 = v4 != 0 ? (*(uint32_t *)(fld_4 + 8) - v4) >> 2 : 0;
    if ( (int)v2 >= v5 )  // 若 (int)v2 >= v5
      break;
    if ( v4 != 0 && v2 < (*(uint32_t *)(fld_4 + 8) - v4) >> 2 )  // 若 v4 != 0 && v2 < (*(uint32_t *)(fld_4 + 8) - v4) >> 2
      v6 = *(uint32_t *)(v4 + 4 * v2);
    else
      v6 = 0;
    v7 = (uint32_t *)__RTDynamicCast(v6, 0, &IRDAppendage `RTTI Type Descriptor', &CNWhipped `RTTI Type Descriptor', 0);  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
    v8 = v7;
    if ( v7 != nullptr
      && v7[16] == 11
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v7 + 80))(v7) != 0  // 虚调用 vt+80
      && (pszArg2 == 0 || v8 != (uint32_t *)this) )  // 鞭挞主数据（52 行）
    {
      if ( v12 == nullptr )  // 若 v12 为空
        v12 = v8;
      v8[26] = 0;
      ++v11;  // 自增v11
    }
    ++v2;  // 自增v2
  }
  result = v12;
  if ( v12 != nullptr )  // 若 v12 非空
    v12[26] = v11 * dword_795FD4[*(uint8_t *)(this + 80) == 0];  // v12[26] 写入 v11 * dword_795FD4[*(uint8_t *)(this + 80)..
  return result;
}



// ------------------------------------------------------------
// 0x64DE20 sub_64DE20 —— 鞭挞循环数据（119 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64DE20(int this)  // 函数: 鞭挞循环数据（119 行）
{
  int fld_50; // eax
  int v2; // edx
  int v3; // eax
  int result; // eax
  signed int v5; // ebx
  int v6; // edi
  int fld_502; // edx
  int v8; // esi
  int v9; // eax
  int fld_503; // edx
  int v11; // esi
  unsigned int v12; // eax
  int v13; // eax
  int fld_504; // edx
  int v15; // esi
  int v16; // eax
  int fld_505; // edx
  int v18; // esi
  unsigned int v19; // eax
  int v20; // eax
  int v21; // edi
  int fld_506; // edx
  int v23; // esi
  int v24; // eax
  signed int v25; // [esp+0h] [ebp-Ch]
  signed int v26; // [esp+4h] [ebp-8h]
  unsigned int v27; // [esp+8h] [ebp-4h]

  fld_50 = *(uint32_t *)(this + 80);  // fld_50 = this+80
  v2 = *(uint32_t *)(fld_50 + 7620);  // v2 = fld_50+7620
  v3 = fld_50 + 7616;  // fld_50=this+80 关联角色对象
  if ( v2 != 0 )  // 若 v2 != 0
  {
    result = (*(uint32_t *)(v3 + 8) - v2) >> 5;
    v26 = result;
  }
  else
  {
    result = 0;
    v26 = 0;
  }
  v5 = 0;
  if ( result >= 4 )  // 若 result >= 4
  {
    v25 = result - 3;
    v27 = 2;
    v6 = 0;
    do
    {
      fld_502 = *(uint32_t *)(this + 80);  // fld_502 = this+80
      v8 = *(uint32_t *)(fld_502 + 7620);  // v8 = fld_502+7620
      if ( v8 != 0 && v5 < (unsigned int)((*(uint32_t *)(fld_502 + 7624) - v8) >> 5) )  // 若 v8 != 0 && v5 < (unsigned int)((*(uint32_t *)(fld_502 + 7624) ..
        v9 = v6 + v8;
      else
        v9 = 0;
      *(float *)(v9 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v9 + 4);  // v9+4 = (*(float *)(this + 96) + 1.0) * *(float *)..
      fld_503 = *(uint32_t *)(this + 80);  // fld_503 = this+80
      v11 = *(uint32_t *)(fld_503 + 7620);  // v11 = fld_503+7620
      if ( v11 != 0 )  // 若 v11 != 0
        v12 = (*(uint32_t *)(fld_503 + 7624) - v11) >> 5;  // fld_503=this+80 关联角色对象
      else
        v12 = 0;
      if ( v27 - 1 >= v12 )  // 若 v27 - 1 >= v12
        v13 = 0;
      else
        v13 = *(uint32_t *)(fld_503 + 7620) + v6 + 32;  // fld_503=this+80 关联角色对象
      *(float *)(v13 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v13 + 4);  // v13+4 = (*(float *)(this + 96) + 1.0) * *(float *)..
      fld_504 = *(uint32_t *)(this + 80);  // fld_504 = this+80
      v15 = *(uint32_t *)(fld_504 + 7620);  // v15 = fld_504+7620
      if ( v15 != 0 && v27 < (*(uint32_t *)(fld_504 + 7624) - v15) >> 5 )  // 若 v15 != 0 && v27 < (*(uint32_t *)(fld_504 + 7624) - v15) >> 5
        v16 = *(uint32_t *)(fld_504 + 7620) + v6 + 64;  // fld_504=this+80 关联角色对象
      else
        v16 = 0;
      *(float *)(v16 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v16 + 4);  // v16+4 = (*(float *)(this + 96) + 1.0) * *(float *)..
      fld_505 = *(uint32_t *)(this + 80);  // fld_505 = this+80
      v18 = *(uint32_t *)(fld_505 + 7620);  // v18 = fld_505+7620
      if ( v18 != 0 )  // 若 v18 != 0
        v19 = (*(uint32_t *)(fld_505 + 7624) - v18) >> 5;  // fld_505=this+80 关联角色对象
      else
        v19 = 0;
      if ( v27 + 1 >= v19 )  // 若 v27 + 1 >= v19
        v20 = 0;
      else
        v20 = *(uint32_t *)(fld_505 + 7620) + v6 + 96;  // fld_505=this+80 关联角色对象
      v5 += 4;
      v6 += 128;
      v27 += 4;
      *(float *)(v20 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v20 + 4);  // v20+4 = (*(float *)(this + 96) + 1.0) * *(float *)..
    }
    while ( v5 < v25 );  // 当 v5 < v25 循环
    result = v26;
  }
  if ( v5 < result )  // 若 v5 < result
  {
    v21 = 32 * v5;
    do
    {
      fld_506 = *(uint32_t *)(this + 80);  // fld_506 = this+80
      v23 = *(uint32_t *)(fld_506 + 7620);  // v23 = fld_506+7620
      if ( v23 != 0 && v5 < (unsigned int)((*(uint32_t *)(fld_506 + 7624) - v23) >> 5) )  // 若 v23 != 0 && v5 < (unsigned int)((*(uint32_t *)(fld_506 + 7624)..
        v24 = v21 + v23;
      else
        v24 = 0;
      ++v5;  // 自增v5
      v21 += 32;
      *(float *)(v24 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v24 + 4);  // v24+4 = (*(float *)(this + 96) + 1.0) * *(float *)..
      result = v26;
    }
    while ( v5 < v26 );  // 当 v5 < v26 循环
  }
  return result;
}


// ------------------------------------------------------------
// 0x64DFE0 sub_64DFE0 —— 跟随数据（117 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64DFE0(int this)  // 函数: 跟随数据（117 行）
{
  int fld_50; // eax
  int v2; // edx
  int v3; // eax
  int result; // eax
  signed int v5; // ebx
  int v6; // edi
  int fld_502; // edx
  int v8; // esi
  int v9; // eax
  int fld_503; // edx
  int v11; // esi
  unsigned int v12; // eax
  int v13; // eax
  int fld_504; // edx
  int v15; // esi
  int v16; // eax
  int fld_505; // edx
  int v18; // esi
  unsigned int v19; // eax
  int v20; // eax
  int v21; // edi
  int fld_506; // edx
  int v23; // esi
  signed int v24; // [esp+0h] [ebp-Ch]
  signed int v25; // [esp+4h] [ebp-8h]
  unsigned int v26; // [esp+8h] [ebp-4h]

  fld_50 = *(uint32_t *)(this + 80);  // fld_50 = this+80
  v2 = *(uint32_t *)(fld_50 + 7620);  // v2 = fld_50+7620
  v3 = fld_50 + 7616;  // fld_50=this+80 关联角色对象
  if ( v2 != 0 )  // 若 v2 != 0
  {
    result = (*(uint32_t *)(v3 + 8) - v2) >> 5;
    v25 = result;
  }
  else
  {
    result = 0;
    v25 = 0;
  }
  v5 = 0;
  if ( result >= 4 )  // 若 result >= 4
  {
    v24 = result - 3;
    v26 = 2;
    v6 = 0;
    do
    {
      fld_502 = *(uint32_t *)(this + 80);  // fld_502 = this+80
      v8 = *(uint32_t *)(fld_502 + 7620);  // v8 = fld_502+7620
      if ( v8 != 0 && v5 < (unsigned int)((*(uint32_t *)(fld_502 + 7624) - v8) >> 5) )  // 若 v8 != 0 && v5 < (unsigned int)((*(uint32_t *)(fld_502 + 7624) ..
        v9 = v6 + v8;
      else
        v9 = 0;
      *(float *)(v9 + 4) = *(float *)(v9 + 4) / (*(float *)(this + 96) + 1.0);  // v9+4 = *(float *)(v9 + 4) / (*(float *)(this + 96..
      fld_503 = *(uint32_t *)(this + 80);  // fld_503 = this+80
      v11 = *(uint32_t *)(fld_503 + 7620);  // v11 = fld_503+7620
      if ( v11 != 0 )  // 若 v11 != 0
        v12 = (*(uint32_t *)(fld_503 + 7624) - v11) >> 5;  // fld_503=this+80 关联角色对象
      else
        v12 = 0;
      if ( v26 - 1 >= v12 )  // 若 v26 - 1 >= v12
        v13 = 0;
      else
        v13 = *(uint32_t *)(fld_503 + 7620) + v6 + 32;  // fld_503=this+80 关联角色对象
      *(float *)(v13 + 4) = *(float *)(v13 + 4) / (*(float *)(this + 96) + 1.0);  // v13+4 = *(float *)(v13 + 4) / (*(float *)(this + 9..
      fld_504 = *(uint32_t *)(this + 80);  // fld_504 = this+80
      v15 = *(uint32_t *)(fld_504 + 7620);  // v15 = fld_504+7620
      if ( v15 != 0 && v26 < (*(uint32_t *)(fld_504 + 7624) - v15) >> 5 )  // 若 v15 != 0 && v26 < (*(uint32_t *)(fld_504 + 7624) - v15) >> 5
        v16 = *(uint32_t *)(fld_504 + 7620) + v6 + 64;  // fld_504=this+80 关联角色对象
      else
        v16 = 0;
      *(float *)(v16 + 4) = *(float *)(v16 + 4) / (*(float *)(this + 96) + 1.0);  // v16+4 = *(float *)(v16 + 4) / (*(float *)(this + 9..
      fld_505 = *(uint32_t *)(this + 80);  // fld_505 = this+80
      v18 = *(uint32_t *)(fld_505 + 7620);  // v18 = fld_505+7620
      if ( v18 != 0 )  // 若 v18 != 0
        v19 = (*(uint32_t *)(fld_505 + 7624) - v18) >> 5;  // fld_505=this+80 关联角色对象
      else
        v19 = 0;
      if ( v26 + 1 >= v19 )  // 若 v26 + 1 >= v19
        v20 = 0;
      else
        v20 = *(uint32_t *)(fld_505 + 7620) + v6 + 96;  // fld_505=this+80 关联角色对象
      v5 += 4;
      v6 += 128;
      v26 += 4;
      *(float *)(v20 + 4) = *(float *)(v20 + 4) / (*(float *)(this + 96) + 1.0);  // v20+4 = *(float *)(v20 + 4) / (*(float *)(this + 9..
    }
    while ( v5 < v24 );  // 当 v5 < v24 循环
    result = v25;
  }
  if ( v5 < result )  // 若 v5 < result
  {
    v21 = 32 * v5;
    do
    {
      fld_506 = *(uint32_t *)(this + 80);  // fld_506 = this+80
      v23 = *(uint32_t *)(fld_506 + 7620);  // v23 = fld_506+7620
      if ( v23 != 0 && v5 < (unsigned int)((*(uint32_t *)(fld_506 + 7624) - v23) >> 5) )  // 若 v23 != 0 && v5 < (unsigned int)((*(uint32_t *)(fld_506 + 7624)..
        result = v21 + v23;
      else
        result = 0;
      ++v5;  // 自增v5
      v21 += 32;
      *(float *)(result + 4) = *(float *)(result + 4) / (*(float *)(this + 96) + 1.0);  // result+4 = *(float *)(result + 4) / (*(float *)(this ..
    }
    while ( v5 < v25 );  // 当 v5 < v25 循环
  }
  return result;
}


// ------------------------------------------------------------
// 0x64E1A0 CNWhipped__vmt4 —— CNWhipped__vmt4 复位（4600B0）
// ------------------------------------------------------------
void /*thiscall*/ CNWhipped__vmt4(int this)  // 函数: CNWhipped__vmt4 复位（4600B0）
{
  int *pHostObj; // esi
  int pFxObj; // ebx  | +0x006C → 特效对象（CNWhipped；va=0064E1A0）
  int v4; // edx
  void *v5; // eax
  int v6; // [esp-Ch] [ebp-3Ch]
  int v7; // [esp-8h] [ebp-38h]
  int v8; // [esp-4h] [ebp-34h]
  uint8_t v9[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int pThis; // [esp+1Ch] [ebp-14h]
  int v12; // [esp+20h] [ebp-10h]
  int v13; // [esp+2Ch] [ebp-4h]

  pThis = this;
  IRDAppendage__vmt4((int *)this);
  pHostObj = *(int **)(this + 4);  // this+4 pHostObj
  pFxObj = **(uint32_t **)(this + 108);  // this+108 pFxObj
  v12 = (*(int (/*thiscall*/ **)(int *))(*pHostObj + 192))(pHostObj);  // 结果 = 虚调用 vt+192
  v8 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*pHostObj + 128))(pHostObj, (uint64_t)((double)v12 * -0.5) >> 32)  // 结果 = 虚调用 vt+128
     - (uint64_t)((double)v12 * -0.5);
  v7 = (*(int (/*thiscall*/ **)(int *))(*pHostObj + 124))(pHostObj);  // 结果 = 虚调用 vt+124
  v6 = (*(int (/*thiscall*/ **)(int *))(*pHostObj + 120))(pHostObj);  // 结果 = 虚调用 vt+120
  (*(void (/*thiscall*/ **)(uint32_t))(pFxObj + 40))(*(uint32_t *)(pThis + 108));  // 调用虚函数槽 +40
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(pThis + 108) + 92))(*(uint32_t *)(pThis + 108), v9);  // 调用虚函数槽 +92
  v4 = *pHostObj;  // fld_4=this+4 pHostObj
  v13 = 0;
  v5 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v4 + 80))(pHostObj, 2, 0, v9);  // fld_4=this+4 pHostObj
  sub_4600B0(v5, v6, v7, v8);  // 调 sub_4600B0
  if ( Block != nullptr )  // 若 Block 非空
    j__free(Block);  // 调 j__free
}



// ------------------------------------------------------------
// 0x64E260 CNWhipped__vmt20 —— CNWhipped__vmt20 主循环（64E260 + 64DD40，127 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_64E260(int this, char pszArg2)  // 【CNWhipped__vmt20】
{
  char result; // al
  uint32_t *fld_4; // esi
  int v5; // eax
  uint32_t *v6; // eax
  int v7; // eax
  signed int v8; // edi
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  unsigned int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  unsigned int v18; // eax
  int v19; // eax
  int v20; // edx
  int v21; // ecx
  int v22; // eax
  signed int v23; // [esp+4h] [ebp-8h]
  int v24; // [esp+8h] [ebp-4h]
  unsigned int v25; // [esp+14h] [ebp+8h]

  result = pszArg2;
  if ( pszArg2 == 0 )  // 若 pszArg2 == 0
  {
    fld_4 = __RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
           *(uint32_t **)(this + 4),  // this+4 pHostObj
           0,
           &IRDActiveObject `RTTI Type Descriptor',
           &IRDMonster `RTTI Type Descriptor',
           0);
    if ( *(uint8_t *)(this + 80) != 0 && fld_4 != nullptr )  // 判定 “+80 加算开关”
    {
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*fld_4 + 1040))(fld_4);  // 结果 = 虚调用 vt+1040
      *(uint32_t *)(v5 + 72) -= *(uint32_t *)(this + 96);  // this+96 nAddValueA
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*fld_4 + 1040))(fld_4) != 0 )  // 虚调用 vt+1040
      {
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*fld_4 + 1040))(fld_4);  // 结果 = 虚调用 vt+1040
        *v6 -= *(uint32_t *)(this + 100);  // this+100 nAddValueB
      }
      v7 = fld_4[1905];
      if ( v7 != 0 )  // 若 v7 != 0
      {
        v24 = (fld_4[1906] - v7) >> 5;
        v7 = v24;
      }
      else
      {
        v24 = 0;
      }
      v8 = 0;
      if ( v7 >= 4 )  // 若 v7 >= 4
      {
        v23 = v7 - 3;
        v25 = 2;
        v9 = 0;
        do
        {
          v10 = fld_4[1905];
          if ( v10 != 0 && v8 < (unsigned int)((fld_4[1906] - v10) >> 5) )  // 若 v10 != 0 && v8 < (unsigned int)((fld_4[1906] - v10) >> 5)
            v11 = v9 + v10;
          else
            v11 = 0;
          *(float *)(v11 + 4) = *(float *)(v11 + 4) / (*(float *)(this + 92) + 1.0);  // v11+4 = *(float *)(v11 + 4) / (*(float *)(this + 9..
          v12 = fld_4[1905];
          if ( v12 != 0 )  // 若 v12 != 0
            v13 = (fld_4[1906] - v12) >> 5;
          else
            v13 = 0;
          if ( v25 - 1 >= v13 )  // 若 v25 - 1 >= v13
            v14 = 0;
          else
            v14 = fld_4[1905] + v9 + 32;
          *(float *)(v14 + 4) = *(float *)(v14 + 4) / (*(float *)(this + 92) + 1.0);  // v14+4 = *(float *)(v14 + 4) / (*(float *)(this + 9..
          v15 = fld_4[1905];
          if ( v15 != 0 && v25 < (fld_4[1906] - v15) >> 5 )  // 若 v15 != 0 && v25 < (fld_4[1906] - v15) >> 5
            v16 = fld_4[1905] + v9 + 64;
          else
            v16 = 0;
          *(float *)(v16 + 4) = *(float *)(v16 + 4) / (*(float *)(this + 92) + 1.0);  // v16+4 = *(float *)(v16 + 4) / (*(float *)(this + 9..
          v17 = fld_4[1905];
          if ( v17 != 0 )  // 若 v17 != 0
            v18 = (fld_4[1906] - v17) >> 5;
          else
            v18 = 0;
          if ( v25 + 1 >= v18 )  // 若 v25 + 1 >= v18
            v19 = 0;
          else
            v19 = fld_4[1905] + v9 + 96;
          v8 += 4;
          v9 += 128;
          v25 += 4;
          *(float *)(v19 + 4) = *(float *)(v19 + 4) / (*(float *)(this + 92) + 1.0);  // v19+4 = *(float *)(v19 + 4) / (*(float *)(this + 9..
        }
        while ( v8 < v23 );  // 当 v8 < v23 循环
        v7 = v24;
      }
      if ( v8 < v7 )  // 若 v8 < v7
      {
        v20 = 32 * v8;
        do
        {
          v21 = fld_4[1905];
          if ( v21 != 0 && v8 < (unsigned int)((fld_4[1906] - v21) >> 5) )  // 若 v21 != 0 && v8 < (unsigned int)((fld_4[1906] - v21) >> 5)
            v22 = v20 + v21;
          else
            v22 = 0;
          ++v8;  // 自增v8
          v20 += 32;
          *(float *)(v22 + 4) = *(float *)(v22 + 4) / (*(float *)(this + 92) + 1.0);  // v22+4 = *(float *)(v22 + 4) / (*(float *)(this + 9..
        }
        while ( v8 < v24 );  // 当 v8 < v24 循环
      }
    }
    return sub_64DD40(1);  // 鞭挞主数据
  }
  return result;
}


// ------------------------------------------------------------
// 0x64E470 sub_64E470 —— 跟随循环装配（64DE20/699000/64DFE0）
// ------------------------------------------------------------
void /*thiscall*/ sub_64E470(uint32_t *this, int nArg2)  // 函数: 跟随循环装配（64DE20/699000/64DFE0）
{
  int fld_e20; // ecx
  int fld_e27; // edi
  int fld_e202; // eax
  uint32_t *fld_e203; // eax
  int v7; // eax
  uint32_t *fld_e204; // eax

  fld_e20 = *(this + 20);  // fld_e20 = this+20
  if ( fld_e20 != 0 )  // 若 fld_e20 != 0
  {
    fld_e27 = *(this + 27);  // fld_e27 = this+27
    *(this + 27) = nArg2;  // this+108 = nArg2
    if ( nArg2 != 0 )  // 若 nArg2 != 0
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e20 + 1152))(fld_e20, nArg2);  // 调用虚函数槽 +1152
      if ( fld_e27 == 0 )  // 若 fld_e27 == 0
      {
        fld_e202 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));  // 调用虚函数槽 +1040
        *(uint32_t *)(fld_e202 + 76) += *(this + 25);
        fld_e203 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));  // this+20 频道页号 等2字段
        *fld_e203 += *(this + 26);
        sub_64DE20((int)this);  // 鞭挞循环数据
      }
      *(this + 28) = sub_699000(*(this + 20) + 36);  // clock_now(clk)
    }
    else if ( fld_e27 != 0 )  // 否则若 fld_e27 != 0
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e20 + 1040))(fld_e20);  // 调用虚函数槽 +1040
      *(uint32_t *)(v7 + 76) -= *(this + 25);
      fld_e204 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));  // this+20 频道页号 等2字段
      *fld_e204 -= *(this + 26);
      sub_64DFE0((int)this);  // 跟随数据
    }
  }
}



// ------------------------------------------------------------
// 0x64E520 CNFollowMe__vmt28 —— CNFollowMe__vmt28 槽（转发 64E470）
// ------------------------------------------------------------
void /*thiscall*/ CNFollowMe__vmt28(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 函数: CNFollowMe__vmt28 槽（转发 64E470）
{
  int v6; // eax
  int v7; // eax

  if ( nArg2 == *(uint32_t *)(*(this + 20) + 8352) )  // 若 nArg2 == *(uint32_t *)(*(this + 20) + 8352)
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3);  // 调用虚函数槽 +348
    if ( (*(uint8_t *)(v6 + 16) != 0
       || *(float *)v6 > 0.0
       || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 348))(nArg3) + 60) != 0)  // CNFollowMe__vmt28 槽（转发 64E470）
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 576))(nArg3) != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 576))(nArg3);  // 调用虚函数槽 +576
      sub_64E470(this, v7);  // 跟随循环装配（64DE20/699000/64DFE0）
    }
  }
}



// ------------------------------------------------------------
// 0x64E590 CNFollowMe__vmt4 —— CNFollowMe__vmt4 复位（699000 + 64DFE0）
// ------------------------------------------------------------
int /*thiscall*/ CNFollowMe__vmt4(int *this)  // 函数: CNFollowMe__vmt4 复位（699000 + 64DFE0）
{
  int pFollowTarget; // ecx  | +0x0050 → 跟随目标对象（CNFollowMe；va=0064DA00）
  int nFollowFlag; // eax  | +0x006C → 跟随标志（0x64DA00: *(this+108)!=0 才做速度累加）（CNFollowMe；va=0064DA00）
  int v4; // eax
  uint32_t *fld_e202; // eax
  int fld_e9; // eax
  int pObj; // ecx
  int result; // eax

  IRDAppendage__vmt4(this);
  if ( *(this + 27) != 0 && sub_699000(*(this + 20) + 36) >= *(this + 21) + *(this + 28) )  // 【clock_now(clk)】
  {
    pFollowTarget = *(this + 20);  // 读 fld_e20 = this+80（跟随目标对象）
    if ( pFollowTarget != 0 )  // 若 fld_e20 != 0
    {
      nFollowFlag = *(this + 27);  // 读 fld_e27 = this+108（跟随标志）
      *(this + 27) = 0;  // 写 this+108 = 0（跟随标志）
      if ( nFollowFlag != 0 )  // 若 fld_e27 != 0
      {
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pFollowTarget + 1040))(pFollowTarget);  // 调用虚函数槽 +1040
        *(uint32_t *)(v4 + 76) -= *(this + 25);
        fld_e202 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));  // this+20 频道页号 等2字段
        *fld_e202 -= *(this + 26);
        sub_64DFE0((int)this);  // 跟随数据
      }
    }
  }
  fld_e9 = __RTDynamicCast(*(this + 9), 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
  if ( fld_e9 == 0 )  // 若 fld_e9 == 0
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);  // 虚调用 vt+76
  pObj = *(uint32_t *)(fld_e9 + 8372);  // pObj = fld_e9+8372
  if ( pObj == 0 )  // 若 pObj == 0
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);  // 虚调用 vt+76
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 80))(pObj);  // 调用虚函数槽 +80
  if ( (uint8_t)result == 0 )  // 若 (uint8_t)result == 0
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);  // 虚调用 vt+76
  return result;
}



// ------------------------------------------------------------
// 0x64E640 CNFollowMe__vmt20 —— CNFollowMe__vmt20 主循环（64DFE0）
// ------------------------------------------------------------
char /*thiscall*/ CNFollowMe__vmt20(uint32_t *this, char pszArg2)  // 函数: CNFollowMe__vmt20 主循环（64DFE0）
{
  int fld_e27; // eax  | +0x006C → 跟随标志（0x64DA00: *(this+108)!=0 才做速度累加）（CNFollowMe；va=0064DA00）
  int pFollowTarget; // ecx  | +0x0050 → 跟随目标对象（CNFollowMe；va=0064DA00）
  int v5; // eax
  uint32_t *fld_e202; // eax

  LOBYTE(fld_e27) = pszArg2;
  if ( pszArg2 == 0 )  // 若 pszArg2 == 0
  {
    pFollowTarget = *(this + 20);  // 读 fld_e20 = this+80（跟随目标对象）
    if ( pFollowTarget != 0 )  // 若 fld_e20 != 0
    {
      fld_e27 = *(this + 27);  // 读 fld_e27 = this+108（跟随标志）
      *(this + 27) = 0;  // 写 this+108 = 0（跟随标志）
      if ( fld_e27 != 0 )  // 若 fld_e27 != 0
      {
        v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pFollowTarget + 1040))(pFollowTarget);  // 调用虚函数槽 +1040
        *(uint32_t *)(v5 + 76) -= *(this + 25);
        fld_e202 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));  // this+20 频道页号 等2字段
        *fld_e202 -= *(this + 26);
        LOBYTE(fld_e27) = sub_64DFE0((int)this);  // 跟随数据
      }
    }
  }
  return fld_e27;  // | +0x006C → 跟随标志（0x64DA00: *(this+108)!=0 才做速度累加）（CNFollowMe；va=0064DA00）
}



// ------------------------------------------------------------
// 0x64E6A0 CNWhipped__vmt1C —— CNWhipped__vmt1C 生成装配：Common/CommonEffect/Particle/AttackPowerUp.ptl（428F30/64DD40，136 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64E6A0(int this)  // 【CNWhipped__vmt1C】
{
  uint32_t *fld_4; // esi
  int v3; // eax
  uint32_t *v4; // eax
  int v5; // eax
  signed int v6; // ebx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  unsigned int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  unsigned int v16; // eax
  int v17; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // eax
  uint32_t *pMem; // eax
  uint32_t *pFxObj; // eax
  int pHostObj; // ecx  | +0x0004 → 宿主对象指针（CNWhipped；va=0064DB50）
  void *Block; // [esp+8h] [ebp-18h]
  int v26; // [esp+Ch] [ebp-14h]
  unsigned int v27; // [esp+10h] [ebp-10h]

  fld_4 = (uint32_t *)__RTDynamicCast(  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
                   *(uint32_t *)(this + 4),  // this+4 pHostObj
                   0,
                   &IRDActiveObject `RTTI Type Descriptor',
                   &IRDMonster `RTTI Type Descriptor',
                   0);
  if ( *(uint8_t *)(this + 80) != 0 && fld_4 != nullptr )  // 判定 “+80 加算开关”
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*fld_4 + 1040))(fld_4);  // 结果 = 虚调用 vt+1040
    *(uint32_t *)(v3 + 72) += *(uint32_t *)(this + 96);  // this+96 nAddValueA
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*fld_4 + 1040))(fld_4) != 0 )  // 虚调用 vt+1040
    {
      v4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*fld_4 + 1040))(fld_4);  // 结果 = 虚调用 vt+1040
      *v4 += *(uint32_t *)(this + 100);  // this+100 nAddValueB
    }
    v5 = fld_4[1905];
    if ( v5 != 0 )  // 若 v5 != 0
    {
      v26 = (fld_4[1906] - v5) >> 5;
      v5 = v26;
    }
    else
    {
      v26 = 0;
    }
    v6 = 0;
    if ( v5 >= 4 )  // 若 v5 >= 4
    {
      Block = (void *)(v5 - 3);
      v27 = 2;
      v7 = 0;
      do
      {
        v8 = fld_4[1905];
        if ( v8 != 0 && v6 < (unsigned int)((fld_4[1906] - v8) >> 5) )  // 若 v8 != 0 && v6 < (unsigned int)((fld_4[1906] - v8) >> 5)
          v9 = v7 + v8;
        else
          v9 = 0;
        *(float *)(v9 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v9 + 4);  // v9+4 = (*(float *)(this + 92) + 1.0) * *(float *)..
        v10 = fld_4[1905];
        if ( v10 != 0 )  // 若 v10 != 0
          v11 = (fld_4[1906] - v10) >> 5;
        else
          v11 = 0;
        if ( v27 - 1 >= v11 )  // 若 v27 - 1 >= v11
          v12 = 0;
        else
          v12 = v7 + fld_4[1905] + 32;
        *(float *)(v12 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v12 + 4);  // v12+4 = (*(float *)(this + 92) + 1.0) * *(float *)..
        v13 = fld_4[1905];
        if ( v13 != 0 && v27 < (fld_4[1906] - v13) >> 5 )  // 若 v13 != 0 && v27 < (fld_4[1906] - v13) >> 5
          v14 = v7 + fld_4[1905] + 64;
        else
          v14 = 0;
        *(float *)(v14 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v14 + 4);  // v14+4 = (*(float *)(this + 92) + 1.0) * *(float *)..
        v15 = fld_4[1905];
        if ( v15 != 0 )  // 若 v15 != 0
          v16 = (fld_4[1906] - v15) >> 5;
        else
          v16 = 0;
        if ( v27 + 1 >= v16 )  // 若 v27 + 1 >= v16
          v17 = 0;
        else
          v17 = v7 + fld_4[1905] + 96;
        v6 += 4;
        v7 += 128;
        v27 += 4;
        *(float *)(v17 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v17 + 4);  // v17+4 = (*(float *)(this + 92) + 1.0) * *(float *)..
      }
      while ( v6 < (int)Block );  // 当 v6 < (int)Block 循环
      v5 = v26;
    }
    if ( v6 < v5 )  // 若 v6 < v5
    {
      v18 = 32 * v6;
      do
      {
        v19 = fld_4[1905];
        if ( v19 != 0 && v6 < (unsigned int)((fld_4[1906] - v19) >> 5) )  // 若 v19 != 0 && v6 < (unsigned int)((fld_4[1906] - v19) >> 5)
          v20 = v18 + v19;
        else
          v20 = 0;
        ++v6;  // 自增v6
        v18 += 32;
        *(float *)(v20 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v20 + 4);  // v20+4 = (*(float *)(this + 92) + 1.0) * *(float *)..
      }
      while ( v6 < v26 );  // 当 v6 < v26 循环
    }
  }
  if ( *(uint32_t *)(this + 108) == 0 )  // 判定 “+108 特效对象”
  {
    pMem = operator new(0x12Cu);  // 堆分配 300 字节对象
    if ( pMem != nullptr )  // 若 pMem 非空
      pFxObj = sub_428F30(pMem, (int)"Common/CommonEffect/Particle/AttackPowerUp.ptl", *(uint32_t *)(this + 4));  // 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
    else
      pFxObj = nullptr;  // fld_42 = nullptr 空指针
    pHostObj = *(uint32_t *)(this + 4);  // 读 fld_43 = this+4（宿主对象指针）
    *(uint32_t *)(this + 108) = pFxObj;  // 写 this+108 = fld_42（特效对象）
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pFxObj + 112))(pFxObj, pHostObj);  // 虚调用 vt+112
  }
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 108) + 12))(*(uint32_t *)(this + 108), 0);  // 调用虚函数槽 +12
  return sub_64DD40(0);  // 鞭挞主数据
}


// ------------------------------------------------------------
// 0x64E920 sub_64E920 —— 跟随受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64E920(void ***this)  // 函数: 跟随受击（42AF90/657740）
{
  void ***pThis_1D; // esi
  int i; // ebx
  void **v3; // edi
  int result; // eax

  pThis_1D = this + 29;  // this+29 pSessionCtx
  for ( i = 2; i != 0; --i )  // 循环：i = 2; i != 0; --i
  {
    v3 = *pThis_1D;  // pThis_1D=this+29 pSessionCtx
    if ( *pThis_1D != nullptr )  // 若 *pThis_1D != nullptr
    {
      sub_42AF90(*pThis_1D);  // 帧对象析构（帧数组 + 元素数组）
      result = sub_657740(v3, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_1D++ = nullptr;  // *pThis_1D++ 写入 nullptr
  }
  return result;
}



// ------------------------------------------------------------
// 0x64E960 CNFollowMe__vmt1C —— CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/Animation/FollowMeFlag1/2/3.ani（42FCB0/431860/44B6C0/44E0D0/45FE80/4A06D0/4922F0）
// ------------------------------------------------------------
int /*thiscall*/ CNFollowMe__vmt1C(int *this)  // 函数: CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/Animation/FollowMeFlag1/2/3.ani（42FCB0/431860/44B6C0/44E0D0/45FE80/4A06D0/4922F0）
{
  int pFollowTarget; // eax
  int pObj2; // esi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int result; // eax
  int v9; // eax
  int v10; // ebx
  char *v11; // eax
  int pObj; // edi
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // eax
  int v17; // edi
  float v18; // [esp+Ch] [ebp-24h]

  pFollowTarget = __RTDynamicCast(*(this + 1), 0, &IRDActiveObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
  pObj2 = pFollowTarget;
  if ( pFollowTarget == 0 )  // 若 fld_e1 == 0
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);  // 虚调用 vt+76
  *(this + 20) = pFollowTarget;  // 写 this+80 = fld_e1（跟随目标对象）
  v4 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v4 != 0 )  // 若 v4 != 0
    v5 = sub_431860(v4, "Character/Mage/Effect/Animation/FollowMeFlag1.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/FollowMeFlag”
  else
    v5 = 0;
  *(this + 29) = v5;  // 写 this+116 = v5（跟随动画件）
  v6 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v6 != 0 )  // 若 v6 != 0
    v7 = sub_431860(v6, "Character/Mage/Effect/Animation/FollowMeFlag2.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/FollowMeFlag”
  else
    v7 = 0;
  *(this + 30) = v7;  // this+120 = v7
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 80))(pObj2);  // 调用虚函数槽 +80
  if ( result != 0 )  // 若 result != 0
  {
    v9 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
    if ( v9 != 0 )  // 若 v9 != 0
      v10 = sub_431860(v9, "Character/Mage/Effect/Animation/FollowMeFlag3.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/FollowMeFlag”
    else
      v10 = 0;
    v11 = (char *)sub_44B6C0(284);  // 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
    pObj = (int)v11;
    if ( v11 != nullptr )  // 若 v11 非空
    {
      sub_44E0D0(v11, v10, 1);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)pObj = &vftbl_CNRDPooledObject;
    }
    else
    {
      pObj = 0;
    }
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 80))(pObj2);  // 调用虚函数槽 +80
    sub_45FE80(v13, pObj, 2, 0, pObj, pObj2, 0);  // 调 sub_45FE80
    v14 = *(uint32_t *)pObj;  // v14 = pObj
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 124))(pObj2);  // 调用虚函数槽 +124
    v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v15 + 1);  // 调用虚函数槽 +120
    (*(void (/*thiscall*/ **)(int, int))(v14 + 112))(pObj, v16);  // 调用虚函数槽 +112
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 60))(pObj, pObj2);  // 调用虚函数槽 +60
    sub_4A06D0(0);  // 调 sub_4A06D0
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 192))(pObj2);  // 调用虚函数槽 +192
    v18 = (double)(v17 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2) + 30) * 0.0095238099;  // 虚槽+128 CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
    return sub_4922F0(v18);  // 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
  }
  return result;
}



// ============================================================
// 【分区 19】气功护盾 CNAuraShield（0x64EB30-0x64EEA0）
// 64ED00 装载 AuraShieldStart/Loop/End/Hit1/Hit2.ani；
// vmt1C/vmt34 播 AURA_SHIELD_LOOP 循环事件；vmt78=受击消耗。
// ============================================================
// ------------------------------------------------------------
// 0x64EB30 CNAuraShield__vmt4 —— CNAuraShield__vmt4 复位（491C10/699000/4926A0）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraShield__vmt4(int *this)  // 函数: CNAuraShield__vmt4 复位（491C10/699000/4926A0）
{
  int fld_e25; // eax
  int fld_e11; // edi
  int fld_e112; // edi

  IRDAppendage__vmt4(this);
  fld_e25 = *(this + 25);  // fld_e25 = this+25
  if ( fld_e25 != 0 )  // 若 fld_e25 != 0
  {
    if ( fld_e25 == 1 )  // 若 fld_e25 == 1
    {
      fld_e11 = *(this + 11) - sub_491C10(*(this + 22));  // 结果 = 遍历帧数组（首+44/尾+48，步长 88）
      fld_e25 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
      if ( fld_e25 < fld_e11 )  // 若 fld_e25 < fld_e11
        return fld_e25;  // fld_e25=this+100 插值终点 Y
    }
    else
    {
      if ( fld_e25 != 3 )  // 若 fld_e25 != 3
        return fld_e25;  // fld_e25=this+100 插值终点 Y
      LOBYTE(fld_e25) = *(uint8_t *)(*(this + 23) + 170);  // fld_e25=this+100 插值终点 Y
      if ( (uint8_t)fld_e25 == 0 )  // 若 (uint8_t)fld_e25 == 0
        return fld_e25;  // fld_e25=this+100 插值终点 Y
      fld_e112 = *(this + 11) - sub_491C10(*(this + 22));  // 结果 = 遍历帧数组（首+44/尾+48，步长 88）
      fld_e25 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
      if ( fld_e25 < fld_e112 )  // 若 fld_e25 < fld_e112
      {
        *(this + 25) = 1;  // this+100 = 1
        LOBYTE(fld_e25) = sub_4926A0(*(this + 21));  // 帧游标复位（+44 帧数组；递归子链 +204）
        return fld_e25;  // fld_e25=this+100 插值终点 Y
      }
    }
    *(this + 25) = 2;  // this+100 = 2
    return fld_e25;  // fld_e25=this+100 插值终点 Y
  }
  fld_e25 = *(this + 20);  // fld_e25 = this+20
  if ( *(uint8_t *)(fld_e25 + 170) != 0 )  // 若 *(uint8_t *)(fld_e25 + 170) != 0
    *(this + 25) = 1;  // this+100 = 1
  return fld_e25;  // fld_e25=this+80 关联角色对象
}



// ------------------------------------------------------------
// 0x64EBC0 CNAuraShield__vmt14 —— CNAuraShield__vmt14 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraShield__vmt14(int *this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 函数: CNAuraShield__vmt14 生成槽（4938F0/491D00）
{
  char result; // al

  result = pszArg2;
  if ( pszArg2 != 0 )  // 若 pszArg2 != 0
  {
    sub_4938F0(*(this + *(this + 25) + 20));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    result = sub_491D00(dword_79C0B0, nArg3, nArg4, 0.0);  // 结果 = 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    if ( *(this + 25) == 3 )  // 若 *(this + 25) == 3
    {
      sub_4938F0(*(this + 24));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      return sub_491D00(dword_79C0B0, nArg3 + *(this + 26), nArg4 + *(this + 27), 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x64EC30 CNAuraShield__vmt1C —— CNAuraShield__vmt1C 播 AURA_SHIELD_LOOP 循环事件（4926A0）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraShield__vmt1C(int *this)  // 函数: CNAuraShield__vmt1C 播 AURA_SHIELD_LOOP 循环事件（4926A0）
{
  int *pThis_14; // esi
  int i; // ebx
  int fld_e1; // ecx

  pThis_14 = this + 20;  // this+20 频道页号
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
    sub_4926A0(*pThis_14++);  // 帧游标复位（+44 帧数组；递归子链 +204）
  fld_e1 = *(this + 1);  // fld_e1 = this+1
  *(this + 25) = 0;  // this+100 = 0
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)fld_e1 + 212))(  // fld_e1=this+4 宿主对象
           fld_e1,  // fld_e1=this+4 宿主对象
           "AURA_SHIELD_LOOP",  // 字符串 “AURA_SHIELD_LOOP”
           5,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64EC70 CNAuraShield__vmt20 —— CNAuraShield__vmt20 更新槽（15 行）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraShield__vmt20(uint32_t **this, char pszArg2)  // 函数: CNAuraShield__vmt20 更新槽（15 行）
{
  char result; // al

  result = pszArg2;
  if ( pszArg2 == 0 )  // 若 pszArg2 == 0
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 1) + 216))(*(this + 1), 5);  // 调用虚函数槽 +216
  return result;
}



// ------------------------------------------------------------
// 0x64EC90 CNAuraShield__vmt78 —— CNAuraShield__vmt78 受击消耗槽（4926A0）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraShield__vmt78(int *this)  // 函数: CNAuraShield__vmt78 受击消耗槽（4926A0）
{
  int nRand; // eax
  int fld_e23; // ecx
  int result; // eax

  *(this + 26) = rand() % 60 - 30;  // this+104 = rand() % 60 - 30
  nRand = rand();  // 调 rand 伪随机
  fld_e23 = *(this + 23);  // fld_e23 = this+23
  *(this + 27) = nRand % 40 - 20;  // this+108 = nRand % 40 - 20
  sub_4926A0(fld_e23);  // 帧游标复位（+44 帧数组；递归子链 +204）
  result = sub_4926A0(*(this + 24));  // 结果 = 帧游标复位（+44 帧数组；递归子链 +204）
  *(this + 25) = 3;  // this+100 = 3
  return result;
}



// ------------------------------------------------------------
// 0x64ECE0 CNAuraShield__vmt34 —— CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraShield__vmt34(uint32_t **this)  // 函数: CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行）
{
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(this + 1) + 212))(
           *(this + 1),
           "AURA_SHIELD_LOOP",  // 字符串 “AURA_SHIELD_LOOP”
           5,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64ED00 sub_64ED00 —— 装载 AuraShieldStart/Loop/End/Hit1/Hit2.ani（42FCB0/431860）
// ------------------------------------------------------------
int /*thiscall*/ sub_64ED00(uint32_t *this)  // 函数: 装载 AuraShieldStart/Loop/End/Hit1/Hit2.ani（42FCB0/431860）
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int result; // eax

  v2 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v2 != 0 )  // 若 v2 != 0
    v3 = sub_431860(v2, "Character/Mage/Effect/Animation/AuraShieldStart.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/AuraShieldSt”
  else
    v3 = 0;
  *(this + 20) = v3;  // this+80 = v3
  v4 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v4 != 0 )  // 若 v4 != 0
    v5 = sub_431860(v4, "Character/Mage/Effect/Animation/AuraShieldLoop.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/AuraShieldLo”
  else
    v5 = 0;
  *(this + 21) = v5;  // this+84 = v5
  v6 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v6 != 0 )  // 若 v6 != 0
    v7 = sub_431860(v6, "Character/Mage/Effect/Animation/AuraShieldEnd.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/AuraShieldEn”
  else
    v7 = 0;
  *(this + 22) = v7;  // this+88 = v7
  v8 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v8 != 0 )  // 若 v8 != 0
    v9 = sub_431860(v8, "Character/Mage/Effect/Animation/AuraShieldHit1.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/AuraShieldHi”
  else
    v9 = 0;
  *(this + 23) = v9;  // this+92 = v9
  v10 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v10 != 0 )  // 若 v10 != 0
  {
    result = sub_431860(v10, "Character/Mage/Effect/Animation/AuraShieldHit2.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/AuraShieldHi”
    *(this + 24) = result;  // this+96 = result
  }
  else
  {
    *(this + 24) = 0;  // this+96 = 0
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64EE40 sub_64EE40 —— 护盾受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64EE40(void ***this)  // 函数: 护盾受击（42AF90/657740）
{
  void ***pThis_14; // esi
  int i; // ebx
  void **v3; // edi
  int result; // eax

  pThis_14 = this + 20;  // this+20 频道页号
  for ( i = 5; i != 0; --i )  // 循环：i = 5; i != 0; --i
  {
    v3 = *pThis_14;  // pThis_14=this+20 频道页号
    if ( *pThis_14 != nullptr )  // 若 *pThis_14 != nullptr
    {
      sub_42AF90(*pThis_14);  // 帧对象析构（帧数组 + 元素数组）
      result = sub_657740(v3, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_14++ = nullptr;  // *pThis_14++ 写入 nullptr
  }
  return result;
}



// ------------------------------------------------------------
// 0x64EE80 sub_64EE80 —— 13 行小函数
// ------------------------------------------------------------
int /*thiscall*/ sub_64EE80(uint32_t *this)  // 函数: 13 行小函数
{
  *(this + 32) = 0;  // this+128 = 0
  *(this + 33) = 0;  // this+132 = 0
  *(this + 34) = 0;  // this+136 = 0
  return 0;
}



// ============================================================
// 【分区 20】召唤兽光环与指定目标（0x64EEA0-0x64FC60+）
// CNSummonMonsterAura（64F170 装载 SummonMonsterAuraArea.ani）；
// CNTargetIt（64FB80 装载 TargetIt.ani；vmt24=目标锁定 102 行）；
// CNSuplexed 过肩摔（vmt10 191 行）。
// ============================================================
// ------------------------------------------------------------
// 0x64EEA0 CNSummonMonsterAura__vmt84 —— CNSummonMonsterAura__vmt84 受击事件槽（14 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNSummonMonsterAura__vmt84(uint32_t **this, int nArg2)  // 函数: CNSummonMonsterAura__vmt84 受击事件槽（14 行）
{
  int pHostObj; // edi  | +0x0004 → 宿主对象指针（CNSummonMonsterAura；va=0064A790）

  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0  // 虚槽+40 CNRDAvatarInventoryWindow__vmt28 槽（548E20/4872A0/549000/4868
      && (pHostObj = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 376))(*(this + 1))) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2)  // CNSummonMonsterAura__vmt84 受击事件槽（14 行）
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 724))(nArg2) == 0;  // 虚槽+724 读 +6552 霸体字节
}



// ------------------------------------------------------------
// 0x64EF00 CNSummonMonsterAura__vmt18 —— CNSummonMonsterAura__vmt18 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNSummonMonsterAura__vmt18(int *this, char pszArg2, int nArg3, int nArg4, float fArg5)  // 函数: CNSummonMonsterAura__vmt18 生成槽（4938F0/491D00）
{
  char result; // al

  result = CNRDAuraMaster__vmt18((int)this, pszArg2, nArg3, nArg4, fArg5);
  if ( pszArg2 != 0 )  // 若 pszArg2 != 0
  {
    sub_4938F0(*(this + 34));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    return sub_491D00(dword_79C0B0, nArg3, nArg4, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  }
  return result;
}



// ------------------------------------------------------------
// 0x64EF50 CNSummonMonsterAura__vmt88 —— CNSummonMonsterAura__vmt88 槽（10 行）
// ------------------------------------------------------------
BOOL /*stdcall*/ CNSummonMonsterAura__vmt88(int pArg1)  // 函数: CNSummonMonsterAura__vmt88 槽（10 行）
{
  return *(uint32_t *)(pArg1 + 64) == 17;
}



// ------------------------------------------------------------
// 0x64EF70 CNSummonMonsterAura__vmt7C —— CNSummonMonsterAura__vmt7C 光环失效槽（65 行）
// ------------------------------------------------------------
void /*thiscall*/ CNSummonMonsterAura__vmt7C(uint32_t *this, int nArg2)  // 函数: CNSummonMonsterAura__vmt7C 光环失效槽（65 行）
{
  unsigned int i; // edi
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int pObj; // ecx
  int pHostObj; // ebx  | +0x0004 → 宿主对象指针（CNSummonMonsterAura；va=0064A790）
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx

  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v4 = *(uint32_t *)(v3 + 4);  // v4 = v3+4
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )  // 若 (int)i >= v5
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v7 = *(uint32_t *)(v6 + 4);  // v7 = v6+4
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )  // 若 v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == nArg2 )  // 若 *(uint32_t *)(v8 + 4) == nArg2
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
        v10 = *(uint32_t *)(v9 + 4);  // v10 = v9+4
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )  // 若 v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2
          pObj = *(uint32_t *)(v10 + 4 * i);
        else
          pObj = 0;
        pHostObj = *(this + 1);  // 读 fld_e1 = this+4（宿主对象指针）
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 32) == pHostObj )  // pHostObj=this+4 pHostObj
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
          v14 = *(uint32_t *)(v13 + 4);  // v14 = v13+4
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )  // 若 v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2
          {
            v15 = *(uint32_t **)(v14 + 4 * i);
            if ( v15 != nullptr && v15[16] == 17 )  // 若 v15 != nullptr && v15[16] == 17
            {
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v15 + 76))(v15, 0);  // 虚调用 vt+76
              return;
            }
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64F060 CNSummonMonsterAura__vmt8C —— CNSummonMonsterAura__vmt8C 槽（18 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNSummonMonsterAura__vmt8C(float *this, int pArg2)  // 函数: CNSummonMonsterAura__vmt8C 槽（18 行）
{
  int v2; // eax
  int v3; // esi

  v2 = *(uint32_t *)(pArg2 + 84);  // v2 = pArg2+84
  if ( v2 != 0 && (*(uint32_t *)(pArg2 + 88) - v2) / 12 != 0 )  // 若 v2 != 0 && (*(uint32_t *)(pArg2 + 88) - v2) / 12 != 0
    v3 = *(uint32_t *)(pArg2 + 84);  // v3 = pArg2+84
  else
    v3 = 0;
  return *(float *)(v3 + 8) >= (double)*(this + 32);  // this+32 格子像素尺寸
}



// ------------------------------------------------------------
// 0x64F0B0 CNSummonMonsterAura__vmt78 —— CNSummonMonsterAura__vmt78 光环生效（4B3C90）
// ------------------------------------------------------------
int /*thiscall*/ CNSummonMonsterAura__vmt78(uint32_t *this, int nArg2)  // 函数: CNSummonMonsterAura__vmt78 光环生效（4B3C90）
{
  int pObj; // esi

  if ( operator new(0x7Cu) != nullptr )  // 堆分配 124 字节对象
    pObj = sub_4B3C90(0, 7);  // 结果 = CNChangeStatus 构造（双参）
  else
    pObj = 0;
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 120))(pObj, 4, 1, *(this + 32));  // 调用虚函数槽 +120
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 120))(pObj, 25, 1, *(this + 32));  // 调用虚函数槽 +120
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 120))(pObj, 5, 1, *(this + 33));  // 调用虚函数槽 +120
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pObj + 120))(pObj, 26, 1, *(this + 33));  // 调用虚函数槽 +120
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)pObj + 56))(  // 虚槽+56 CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认动作：+84 标志时 4
           pObj,
           nArg2,
           *(this + 1),
           0,
           0,
           17,
           -1);
}



// ------------------------------------------------------------
// 0x64F170 sub_64F170 —— 装载 SummonMonsterAuraArea.ani（42FCB0/431860）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F170(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数: 装载 SummonMonsterAuraArea.ani（42FCB0/431860）
{
  int v5; // eax
  int v6; // eax

  v5 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v5 != 0 )  // 若 v5 != 0
    v6 = sub_431860(v5, "Character/Mage/Effect/Animation/SummonMonsterAuraArea.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/SummonMonste”
  else
    v6 = 0;
  *(this + 34) = v6;  // this+136 = v6
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 148))(this, nArg2, nArg3, nArg4);  // 虚调用 vt+148
}



// ------------------------------------------------------------
// 0x64F1F0 sub_64F1F0 —— 召唤受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F1F0(void ***this)  // 函数: 召唤受击（42AF90/657740）
{
  int fld_e34; // esi
  int result; // eax

  fld_e34 = (int)*(this + 34);
  if ( fld_e34 != 0 )  // 若 fld_e34 != 0
  {
    sub_42AF90(*(this + 34));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e34, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 34) = nullptr;  // this+136 = nullptr
  return result;
}



// ------------------------------------------------------------
// 0x64F230 sub_64F230 —— 13 行小函数 2
// ------------------------------------------------------------
int /*thiscall*/ sub_64F230(uint32_t *this)  // 函数: 13 行小函数 2
{
  *(this + 32) = 0;  // this+128 = 0
  *(this + 33) = 0;  // this+132 = 0
  *(this + 43) = 0;  // this+172 = 0
  return 0;
}



// ------------------------------------------------------------
// 0x64F250 sub_64F250 —— 目标数据（47EF20/607260/607280）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F250(uint32_t *this, int nArg2)  // 函数: 目标数据（47EF20/607260/607280）
{
  uint32_t *fld_e32; // ecx
  int v4; // eax
  int result; // eax

  fld_e32 = (uint32_t *)*(this + 32);  // this+32 格子像素尺寸
  *(this + 33) = nArg2;  // this+132 = nArg2
  v4 = sub_47EF20(fld_e32, 1u, nArg2, -1, -1, 11);  // 调 sub_47EF20
  sub_607260(this + 34, v4, -1, 0, 1);  // 计时参数写入
  sub_607280(this + 34);  // 调 sub_607280
  result = sub_47EF20((uint32_t *)*(this + 32), 4u, nArg2, -1, -1, 11);  // 调 sub_47EF20
  *(this + 21) = result;  // this+84 = result
  return result;
}



// ------------------------------------------------------------
// 0x64F2B0 CNTargetIt__vmt14 —— CNTargetIt__vmt14 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNTargetIt__vmt14(int this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 函数: CNTargetIt__vmt14 生成槽（4938F0/491D00）
{
  char result; // al
  int pHost4; // eax  | +0x0004 → 宿主对象（各槽 *(this+4) 取 vt+308/192 判存活与高度）（证据: va=0064F3E0）（CNTargetIt；va=0064F3E0）

  result = pszArg2;
  if ( pszArg2 != 0 )  // 若 pszArg2 != 0
  {
    sub_4938F0(*(uint32_t *)(this + 172));  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    pHost4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));  // 调用虚函数槽 +192
    return sub_491D00(dword_79C0B0, nArg3, nArg4 - pHost4 - 5, 0.0);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  }
  return result;
}



// ------------------------------------------------------------
// 0x64F300 CNTargetIt__vmt84 —— CNTargetIt__vmt84 受击事件槽（15 行）
// ------------------------------------------------------------
char /*thiscall*/ CNTargetIt__vmt84(uint32_t *this, uint32_t *pArg2)  // 函数: CNTargetIt__vmt84 受击事件槽（15 行）
{
  char result; // al

  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 529);  // 结果 = 虚调用 vt+40
  if ( result != 0 )  // 若 result != 0
    return pArg2[2088] == *(this + 9);
  return result;
}



// ------------------------------------------------------------
// 0x64F340 sub_64F340 —— 目标查询（23 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F340(int *this, const void *pArg2, unsigned int uArg3)  // 函数: 目标查询（23 行）
{
  int result; // eax
  signed int fld_e2; // esi

  result = (int)this;
  if ( pArg2 != nullptr )  // 若 pArg2 非空
  {
    qmemcpy((void *)(*(this + 2) + *(this + 1)), pArg2, uArg3);  // 调 qmemcpy 内联块拷贝
    fld_e2 = uArg3 + *(this + 2);
    *(this + 2) = fld_e2;  // this+8 = fld_e2
    result = *this;
    if ( fld_e2 > *this )  // 若 fld_e2 > *this
      return off_77F3FC(aCriticalError_40, result);  // off_77F3FC（引擎日志输出函数）
  }
  return result;
}



// ------------------------------------------------------------
// 0x64F390 sub_64F390 —— 目标初始化（4920E0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64F390(int this)  // 目标初始化（4920E0）
{
  int fld_A0; // edx
  int fld_A4; // eax
  float v4; // [esp+0h] [ebp-4h]

  fld_A0 = *(uint32_t *)(this + 160);  // fld_A0 = this+160
  if ( fld_A0 != 0 )  // 若 fld_A0 != 0
    fld_A4 = (*(uint32_t *)(this + 164) - fld_A0) >> 2;  // this+164 第 5 组·+88 增量子倍率
  else
    fld_A4 = 0;
  v4 = (double)(unsigned int)fld_A4 * 0.2 + 0.80000001;
  return sub_4920E0(*(uint32_t **)(this + 172), v4, v4);  // 调 批量改写全帧缩放
}



// ------------------------------------------------------------
// 0x64F3E0 CNTargetIt__vmt24 —— CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605840/64F340/5C6A50/5C6A90/41C5A0/5DAE20/4E4A50）
// ------------------------------------------------------------
char /*thiscall*/ CNTargetIt__vmt24(int this, int nArg2, int *pDwArg3, unsigned int uArg4)  // 函数: CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605840/64F340/5C6A50/5C6A90/41C5A0/5DAE20/4E4A50）
{
  int v5; // eax
  int v6; // ebx
  int fld_24; // eax  | +0x0024 → 目标宿主 id 匹配槽（CNTargetIt；va=0064F3E0）
  float *v8; // eax
  float v9; // eax
  float v10; // edx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int nRand2; // eax
  int nTargetHostId36; // ecx  | +0x0024 → 目标宿主 id 匹配槽（CNTargetIt；va=0064F3E0）
  int v16; // eax
  int fld_80; // edi
  int fld_243; // eax  | +0x0024 → 目标宿主 id 匹配槽（CNTargetIt；va=0064F3E0）
  int fld_802; // eax
  int v20; // ebx
  int16_t *fld_4; // eax
  float pThis_9C; // [esp+0h] [ebp-28h]
  float v24; // [esp+10h] [ebp-18h] BYREF
  float nRand; // [esp+14h] [ebp-14h]
  float v26; // [esp+18h] [ebp-10h]
  int v27; // [esp+1Ch] [ebp-Ch]
  int v28; // [esp+20h] [ebp-8h]
  int v29; // [esp+24h] [ebp-4h]

  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 调用虚函数槽 +576
  v6 = __RTDynamicCast(v5, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);  // 调 __RTDynamicCast（C++ RTTI 动态转换（失败抛 bad_cast））
  LOBYTE(fld_24) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));  // this+4 pHost4 等2字段
  if ( (uint8_t)fld_24 != 0 && v6 != 0 )  // 若 (uint8_t)fld_24 != 0 && v6 != 0
  {
    fld_24 = *(uint32_t *)(this + 36);  // 读 fld_24 = this+36（目标宿主 id 匹配槽）
    if ( *(uint32_t *)(v6 + 8352) == fld_24 && fld_24 != 0 )  // 若 *(uint32_t *)(v6 + 8352) == fld_24 && fld_24 != 0
    {
      v8 = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 虚槽+348 CNRDVirtualCharacter__vmt15C
      LOBYTE(fld_24) = sub_4AED00(v8);  // 调 (推断)有效性判定: this+16 字节非 0 或 this+0 浮点 > 0.0
      if ( (uint8_t)fld_24 != 0 )  // 若 (uint8_t)fld_24 != 0
      {
        LOBYTE(fld_24) = uArg4;  // fld_24=this+36 nTargetHostId36
        if ( (uint8_t)uArg4 == 0 )  // 若 (uint8_t)uArg4 == 0
        {
          fld_24 = __RTDynamicCast(  // fld_24=this+36 nTargetHostId36
                 nArg2,
                 0,
                 &IRDCollisionObject `RTTI Type Descriptor',
                 &CNTemporaryHit `RTTI Type Descriptor',
                 0);
          if ( fld_24 == 0 )  // 若 fld_24 == 0
          {
            v9 = *((float *)pDwArg3 + 1);
            v24 = *(float *)pDwArg3;
            v10 = *((float *)pDwArg3 + 2);
            nRand = v9;
            v11 = pDwArg3[3];
            v26 = v10;
            v12 = pDwArg3[4];
            v27 = v11;
            v13 = pDwArg3[5];
            v28 = v12;
            v29 = v13;
            nRand = (double)(rand() % 60 - 30) + nRand;  // 调 rand（取伪随机数）
            nRand2 = rand();  // 调 rand 伪随机
            nTargetHostId36 = *(uint32_t *)(this + 36);  // 读 fld_242 = this+36（目标宿主 id 匹配槽）
            v26 = (double)(nRand2 % 60 - 30) + v26;
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nTargetHostId36 + 388))(nTargetHostId36);  // 调用虚函数槽 +388
            fld_80 = sub_47EFD0(*(char **)(this + 128), COERCE_FLOAT(3), *(uint32_t *)(this + 132), v16, v16, 11) - 100;  // 调 技能表槽位设置（越界打 aCriticalError_8；+87 处 14 字节/项表）(推断)
            fld_243 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 36) + 388))(*(uint32_t *)(this + 36));  // 调用虚函数槽 +388
            fld_802 = sub_47EFD0(*(char **)(this + 128), COERCE_FLOAT(7), *(uint32_t *)(this + 132), fld_243, fld_243, 0);  // 调 sub_47EFD0
            uArg4 = 0;
            v20 = 100 * fld_802 / (fld_80 + 100);
            fld_4 = sub_605840(&uArg4, *(uint32_t *)(this + 4), (int *)&v24, 0);  // 结果 = 30 字节全局包
            dword_78FE2C = 0;
            sub_64F340((int *)dword_78FE24, fld_4, uArg4);  // 目标查询
            sub_5C6A50(1);  // 调 sub_5C6A50
            sub_5C6A90(fld_80);  // 调 sub_5C6A90
            pThis_9C = (double)(unsigned int)sub_41C5A0(this + 156) * 100.0;  // 结果 = vector<T 4B> 大小查询（空返回 0）
            sub_5DAE20(LODWORD(pThis_9C));  // 内联尾插（this[0]=容量上限、this[1]=基址、this[2]=游标；越界转·of
            LOBYTE(fld_24) = sub_4E4A50(  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
                           *(uint32_t *)(this + 36),  // this+36 nTargetHostId36
                           48011,
                           v20,
                           (uint64_t)v24,
                           (uint64_t)nRand,
                           (uint64_t)v26,
                           1,
                           0,
                           dword_78FE2C,
                           dword_78FE28);
          }
        }
      }
    }
  }
  return fld_24;  // | +0x0024 → 目标宿主 id 匹配槽（CNTargetIt；va=0064F3E0）
}



// ------------------------------------------------------------
// 0x64F600 CNTargetIt__vmt78 —— CNTargetIt__vmt78 生效槽（60FA60）
// ------------------------------------------------------------
int /*thiscall*/ CNTargetIt__vmt78(uint32_t *this, void *Block)  // 函数: CNTargetIt__vmt78 生效槽（60FA60）
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *v5; // eax

  result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529);  // 调用虚函数槽 +40
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    pMem = operator new(0x54u);  // 堆分配 84 字节对象
    if ( pMem != nullptr )  // 若 pMem 非空
      v5 = sub_60FA60(pMem, 0, 0);  // 结果 = CNProvocationed 构造（IRDAppendage 基类 + 两参转发）
    else
      v5 = nullptr;  // v5 = nullptr 空指针
    return (*(int (/*thiscall*/ **)(uint32_t *, void *, uint32_t, uint32_t, uint32_t, int, int))(*v5 + 56))(  // 虚调用 vt+56
             v5,
             Block,
             *(this + 1),
             0,
             0,
             22,
             -1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64F690 CNTargetIt__vmt4 —— CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 699000/64F390/6072C0/47EFD0/605840 等，134 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F690(char *this)  // 【CNTargetIt__vmt4】
{
  int pThis_9; // ecx
  int pThis_8; // eax
  char *pThis_28; // edi
  char *v5; // ebx
  int pThis_282; // ecx
  int result; // eax
  int pThis_82; // eax
  int pThis_1; // ecx
  int v10; // eax
  int pThis_12; // ecx
  int v12; // eax
  int pThis_13; // ecx
  int v14; // eax
  int pThis_14; // edi
  int v16; // ebx
  int v17; // eax
  int pThis_92; // ecx
  int v19; // eax
  int pThis_20; // edi
  int pThis_93; // eax
  int pThis_202; // eax
  int v23; // ebx
  int pThis_15; // eax
  float v25; // [esp+4h] [ebp-30h]
  float v26; // [esp+14h] [ebp-20h] BYREF
  float v27; // [esp+18h] [ebp-1Ch]
  float v28; // [esp+1Ch] [ebp-18h]
  int v29; // [esp+20h] [ebp-14h]
  int v30; // [esp+24h] [ebp-10h]
  int v31; // [esp+28h] [ebp-Ch]
  int pThis_83; // [esp+2Ch] [ebp-8h] BYREF
  unsigned int pThis_9C; // [esp+30h] [ebp-4h]

  sub_64A790();  // 【CNRDAuraMaster__vmt4】
  pThis_9 = *((uint32_t *)this + 9);  // 读 pThis_9 = this+36（目标宿主 id 匹配槽）
  if ( pThis_9 == 0  // pThis_9=this+36 nTargetHostId36
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_9 + 40))(pThis_9, 17) == 0  // pThis_9=this+36 nTargetHostId36
    || (*(uint8_t (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 9) + 724))(*((uint32_t *)this + 9)) != 0 )  // CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 699000/64F390/6072C0/47EFD0/605840 等，134 行）
  {
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 76))(this, 0);  // 调用虚函数槽 +76
  }
  pThis_8 = sub_699000((int)(this + 8));  // 【clock_now(clk)】
  pThis_28 = *((char **)this + 40);  // this+40 物品状态附属标志
  pThis_83 = pThis_8;
  if ( pThis_28 != *((char **)this + 41) )  // 若 pThis_28 != *((char **)this + 41)
  {
    v5 = pThis_28 + 4;  // pThis_28=this+40 物品状态附属标志
    do
    {
      if ( pThis_83 < *(uint32_t *)pThis_28 )  // 若 pThis_83 < *(uint32_t *)pThis_28
      {
        pThis_28 += 4;  // pThis_28=this+40 物品状态附属标志
        v5 += 4;
      }
      else
      {
        memcpy_0(pThis_28, v5, 4 * ((*((uint32_t *)this + 41) - (int)v5) >> 2));  // pThis_28=this+40 物品状态附属标志
        *((uint32_t *)this + 41) -= 4;
        sub_64F390(this);  // 目标初始化（4920E0）
      }
    }
    while ( pThis_28 != *((char **)this + 41) );  // 当 pThis_28 != *((char **)this + 41) 循环
  }
  pThis_282 = *((uint32_t *)this + 40);  // 读 pThis_282 = this+160（向量 begin）
  if ( pThis_282 == 0 || (*((uint32_t *)this + 41) - pThis_282) >> 2 == 0 )  // 若 pThis_282 == 0 || (*((uint32_t *)this + 41) - pThis_282) >> 2 ..
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 76))(this, 0);  // 调用虚函数槽 +76
  pThis_82 = sub_699000((int)(this + 8));  // 【clock_now(clk)】
  result = sub_6072C0(pThis_82);  // 调 sub_6072C0
  if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 308))(*((uint32_t *)this + 1));  // 调用虚函数槽 +308
    if ( (uint8_t)result != 0 )  // 若 (uint8_t)result != 0
    {
      pThis_1 = *((uint32_t *)this + 1);  // 读 pThis_1 = this+4（宿主对象）
      v26 = 0.0;
      v27 = 0.0;
      v28 = 0.0;
      v29 = 0;
      v30 = 0;
      v31 = 0;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_1 + 152))(pThis_1);  // 调用虚函数槽 +152
      pThis_12 = *((uint32_t *)this + 1);  // 读 pThis_12 = this+4（宿主对象）
      if ( v10 != 0 )  // 若 v10 != 0
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_12 + 120))(pThis_12) + 10;  // pThis_12=this+4 pHost4
      else
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_12 + 120))(pThis_12) - 10;  // pThis_12=this+4 pHost4
      pThis_13 = *((uint32_t *)this + 1);  // 读 pThis_13 = this+4（宿主对象）
      pThis_9C = v12;
      v26 = (float)v12;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_13 + 124))(pThis_13);  // 调用虚函数槽 +124
      pThis_14 = *((uint32_t *)this + 1);  // 读 pThis_14 = this+4（宿主对象）
      pThis_9C = v14;
      v27 = (float)v14;
      v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_14 + 192))(pThis_14) / 2;  // pThis_14=this+4 pHost4
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_14 + 128))(pThis_14);  // 调用虚函数槽 +128
      pThis_92 = *((uint32_t *)this + 9);  // 读 pThis_92 = this+36（目标宿主 id 匹配槽）
      pThis_9C = v17 + v16;
      v28 = (float)(v17 + v16);
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_92 + 388))(pThis_92);  // 调用虚函数槽 +388
      pThis_20 = sub_47EFD0(*((char **)this + 32), COERCE_FLOAT(2), *((uint32_t *)this + 33), v19, v19, 11) - 100;  // 调 技能表槽位设置（越界打 aCriticalError_8；+87 处 14 字节/项表）(推断)
      pThis_93 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 9) + 388))(*((uint32_t *)this + 9));  // 调用虚函数槽 +388
      pThis_202 = sub_47EFD0(*((char **)this + 32), COERCE_FLOAT(6), *((uint32_t *)this + 33), pThis_93, pThis_93, 0);  // 调 sub_47EFD0
      pThis_83 = 0;
      v23 = 100 * pThis_202 / (pThis_20 + 100);
      pThis_15 = sub_605840(&pThis_83, *((uint32_t *)this + 1), &v26, 0);  // 结果 = 30 字节全局包
      dword_78FE2C = 0;
      sub_64F340(pThis_15, pThis_83);  // 目标查询
      sub_5C6A50((int *)dword_78FE24, 1);  // 调 sub_5C6A50
      sub_5C6A90(pThis_20);  // 调 sub_5C6A90
      pThis_9C = sub_41C5A0(this + 156);  // 结果 = vector<T 4B> 大小查询（空返回 0）
      v25 = (double)pThis_9C * 100.0;
      sub_5DAE20(LODWORD(v25));  // 内联尾插（this[0]=容量上限、this[1]=基址、this[2]=游标；越界转·of
      return sub_4E4A50(  // 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
               *((uint32_t *)this + 9),
               48011,
               v23,
               (uint64_t)v26,
               (uint64_t)v27,
               (uint64_t)v28,
               1,
               0,
               dword_78FE2C,
               dword_78FE28);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x64F940 CNTargetIt__vmt1C —— CNTargetIt__vmt1C 生成槽（15 行）
// ------------------------------------------------------------
void /*thiscall*/ CNTargetIt__vmt1C(int this)  // 函数: CNTargetIt__vmt1C 生成槽（15 行）
{
  CNRDAuraMaster__vmt1C(this);  // 调 CNRDAuraMaster__vmt1C 生成装配
  if ( *(uint32_t *)(this + 160) != 0 )  // 判定 “+160 向量 begin”
    j__free(*(void **)(this + 160));  // 调 j__free
  *(uint32_t *)(this + 160) = 0;  // 写 this+160 = 0（向量 begin）
  *(uint32_t *)(this + 164) = 0;  // 写 this+164 = 0（向量 end）
  *(uint32_t *)(this + 168) = 0;  // 写 this+168 = 0（向量 cap）
}



// ------------------------------------------------------------
// 0x64F980 CNTargetIt__vmt20 —— CNTargetIt__vmt20 更新槽（15 行）
// ------------------------------------------------------------
void /*thiscall*/ CNTargetIt__vmt20(int this, uint32_t *uArg2)  // 函数: CNTargetIt__vmt20 更新槽（15 行）
{
  CNRDAuraMaster__vmt20((uint32_t *)this, uArg2);  // 调 CNRDAuraMaster__vmt20 更新槽
  if ( *(uint32_t *)(this + 160) != 0 )  // 判定 “+160 向量 begin”
    j__free(*(void **)(this + 160));  // 调 j__free
  *(uint32_t *)(this + 160) = 0;  // 写 this+160 = 0（向量 begin）
  *(uint32_t *)(this + 164) = 0;  // 写 this+164 = 0（向量 end）
  *(uint32_t *)(this + 168) = 0;  // 写 this+168 = 0（向量 cap）
}



// ------------------------------------------------------------
// 0x64F9D0 CNTargetIt__vmt7C —— CNTargetIt__vmt7C 失效槽（65 行）
// ------------------------------------------------------------
void /*thiscall*/ CNTargetIt__vmt7C(uint32_t *this, int nArg2)  // 函数: CNTargetIt__vmt7C 失效槽（65 行）
{
  unsigned int i; // edi
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int pObj; // ecx
  int pHost4; // ebx  | +0x0004 → 宿主对象（各槽 *(this+4) 取 vt+308/192 判存活与高度）（证据: va=0064F3E0）（CNTargetIt；va=0064F3E0）
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx

  if ( nArg2 != 0 )  // 若 nArg2 != 0
  {
    for ( i = 0; ; ++i )  // 循环：i = 0; ; ++i
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v4 = *(uint32_t *)(v3 + 4);  // v4 = v3+4
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )  // 若 (int)i >= v5
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
      v7 = *(uint32_t *)(v6 + 4);  // v7 = v6+4
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )  // 若 v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == nArg2 )  // 若 *(uint32_t *)(v8 + 4) == nArg2
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
        v10 = *(uint32_t *)(v9 + 4);  // v10 = v9+4
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )  // 若 v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2
          pObj = *(uint32_t *)(v10 + 4 * i);
        else
          pObj = 0;
        pHost4 = *(this + 1);  // 读 fld_e1 = this+4（宿主对象）
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 32) == pHost4 )  // pHost4=this+4 pHost4
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 700))(nArg2);  // 调用虚函数槽 +700
          v14 = *(uint32_t *)(v13 + 4);  // v14 = v13+4
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )  // 若 v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2
          {
            v15 = *(uint32_t **)(v14 + 4 * i);
            if ( v15 != nullptr && v15[16] == 22 )  // 若 v15 != nullptr && v15[16] == 22
            {
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v15 + 76))(v15, 0);  // 虚调用 vt+76
              return;
            }
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64FAC0 sub_64FAC0 —— 目标锁业务（699000/430C80/47E9D0/64F390）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64FAC0(int this, int nArg2)  // 目标锁业务（699000/430C80/47E9D0/64F390）
{
  int pThis_8; // eax
  int v4; // eax
  int fld_A0; // edx
  unsigned int fld_A4; // edi
  int *fld_A42; // ecx
  int fld_A02; // eax
  unsigned int fld_A43; // edi

  pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
  v4 = nArg2 + pThis_8;
  fld_A0 = *(uint32_t *)(this + 160);  // fld_A0 = this+160
  nArg2 = v4;
  if ( fld_A0 != 0 )  // 若 fld_A0 != 0
    fld_A4 = (*(uint32_t *)(this + 164) - fld_A0) >> 2;  // this+164 第 5 组·+88 增量子倍率
  else
    fld_A4 = 0;
  if ( fld_A0 != 0 && fld_A4 < (*(uint32_t *)(this + 168) - fld_A0) >> 2 )  // 若 fld_A0 != 0 && fld_A4 < (*(uint32_t *)(this + 168) - fld_A0) >..
  {
    fld_A42 = *(int **)(this + 164);  // this+164 第 5 组·+88 增量子倍率
    *fld_A42 = v4;  // *fld_A42 写入 v4
    *(uint32_t *)(this + 164) = fld_A42 + 1;  // this+164 = fld_A42 + 1
  }
  else
  {
    sub_430C80(this + 156, *(uint32_t *)(this + 164), 1u, &nArg2);  // uint32 vector 区间插入（同值填充）
  }
  fld_A02 = *(uint32_t *)(this + 160);  // fld_A02 = this+160
  if ( fld_A02 != 0 )  // 若 fld_A02 != 0
    fld_A43 = (*(uint32_t *)(this + 164) - fld_A02) >> 2;  // this+164 第 5 组·+88 增量子倍率
  else
    fld_A43 = 0;
  if ( fld_A43 > sub_47E9D0(*(uint32_t **)(this + 128), 1u) )  // 若 fld_A43 > sub_47E9D0(*(uint32_t **)(this + 128), 1u)
  {
    memcpy_0(
      *(void **)(this + 160),  // this+160 第 5 组·+1040 增量子倍率
      (const void *)(*(uint32_t *)(this + 160) + 4),  // this+160 第 5 组·+1040 增量子倍率
      4 * ((*(uint32_t *)(this + 164) - (*(uint32_t *)(this + 160) + 4)) >> 2));  // this+164 第 5 组·+88 增量子倍率 等2字段
    *(uint32_t *)(this + 164) -= 4;  // this+164 第 5 组·+88 增量子倍率
  }
  return sub_64F390(this);  // 目标初始化（4920E0）
}



// ------------------------------------------------------------
// 0x64FB80 sub_64FB80 —— 装载 Character/Mage/Effect/Animation/TargetIt.ani（42FCB0/431860/47E720）
// ------------------------------------------------------------
int /*thiscall*/ sub_64FB80(uint32_t *this)  // 函数: 装载 Character/Mage/Effect/Animation/TargetIt.ani（42FCB0/431860/47E720）
{
  int v2; // eax
  int v3; // eax
  int result; // eax

  v2 = sub_42FCB0(228);  // 结果 = CRT 一次性初始化
  if ( v2 != 0 )  // 若 v2 != 0
    v3 = sub_431860(v2, "Character/Mage/Effect/Animation/TargetIt.ani", 1);  // 字符串 “Character/Mage/Effect/Animation/TargetIt.ani”
  else
    v3 = 0;
  *(this + 43) = v3;  // this+172 = v3
  result = sub_47E720(3, 0x32u);  // 调 sub_47E720
  *(this + 32) = result;  // this+128 = result
  return result;
}



// ------------------------------------------------------------
// 0x64FC00 sub_64FC00 —— 目标受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64FC00(void ***this)  // 函数: 目标受击（42AF90/657740）
{
  int fld_e43; // esi
  int result; // eax

  fld_e43 = (int)*(this + 43);
  if ( fld_e43 != 0 )  // 若 fld_e43 != 0
  {
    sub_42AF90(*(this + 43));  // 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e43, 228);  // 结果 = 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 43) = nullptr;  // this+172 = nullptr
  return result;
}



// ------------------------------------------------------------
// 0x64FC40 sub_64FC40 —— 18 行小函数
// ------------------------------------------------------------
int /*thiscall*/ sub_64FC40(int this)  // 函数: 18 行小函数
{
  *(uint32_t *)(this + 80) = 0;  // this+80 = 0
  *(uint8_t *)(this + 84) = 0;  // this+84 = 0
  *(uint8_t *)(this + 85) = 0;  // this+85 = 0
  *(uint32_t *)(this + 88) = -1;  // this+88 = -1
  *(uint32_t *)(this + 92) = 0;  // this+92 = 0
  *(uint32_t *)(this + 96) = 0;  // this+96 = 0
  *(uint32_t *)(this + 100) = 0;  // this+100 = 0
  *(uint8_t *)(this + 104) = 1;  // this+104 = 1
  return 0;
}



// ------------------------------------------------------------
// 0x64FC60 CNSuplexed__vmt10 —— CNSuplexed__vmt10 过肩摔主流程（191 行：4938F0 目标 + 432E50 播报）
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_64FC60@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // CNSuplexed__vmt10 过肩摔主流程（191 行：4938F0 目标 + 432E50 播报）
{
  uint32_t *result; // eax
  int *v5; // edi
  uint32_t *v6; // ebx
  int v7; // ebx
  int v8; // eax
  char v9; // dl
  int v10; // eax
  int v11; // ecx
  char v12; // al
  int v13; // ebx
  int v14; // eax
  int v15; // ebx
  int v16; // ebx
  uint64_t v17; // rax
  int v18; // ebx
  char v19; // al
  int v20; // ebx
  int pObj; // ecx
  int v22; // ebx
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // ebx
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v33; // [esp+8h] [ebp-Ch]
  int v34; // [esp+8h] [ebp-Ch]
  int v35; // [esp+Ch] [ebp-8h]
  int pObj2; // [esp+Ch] [ebp-8h]
  int v37; // [esp+10h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 840))(*(uint32_t *)(pArg1 + 80));
  if ( result == (uint32_t *)19 )  // 若 result == (uint32_t *)19
  {
    v5 = *(int **)(pArg1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);  // 结果 = 虚调用 vt+840
    if ( result == (uint32_t *)9 )  // 若 result == (uint32_t *)9
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 236))(v5) == 1 )  // 虚调用 vt+236
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);  // 虚调用 vt+228
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 200))(*(uint32_t *)(pArg1 + 80));
      v6 = result;
      if ( result != nullptr )  // 若 result 非空
      {
        sub_4938F0((int)result);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        v7 = v6[37];
        v37 = v7;
        v8 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80), nArg2, nArg3);  // 调用虚函数槽 +152
        v35 = v8;
        if ( *(uint8_t *)(pArg1 + 85) == 0 )  // 若 *(uint8_t *)(pArg1 + 85) == 0
          v35 = sub_432E50(v8);  // 结果 = 关系码对调映射
        if ( v7 == *(uint32_t *)(pArg1 + 88) )  // 若 v7 == *(uint32_t *)(pArg1 + 88)
          goto LABEL_45;  // 跳转 LABEL_45
        v9 = *(uint8_t *)(pArg1 + 85);  // v9 = pArg1+85
        v10 = 2 * (v9 != 0) + 2;
        if ( v7 < v10 )  // 若 v7 < v10
        {
          *(uint32_t *)(pArg1 + 92) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80)) != 0
                               ? 60
                               : -60;
          *(uint32_t *)(pArg1 + 96) = -1;  // pArg1+96 = -1
          if ( 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) <= 0 )  // 虚调用 vt+192
            v11 = 0;
          else
            v11 = 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5);  // 结果 = 虚调用 vt+192
          v12 = *(uint8_t *)(pArg1 + 85);  // v12 = pArg1+85
          *(uint32_t *)(pArg1 + 100) = v11;  // pArg1+100 = v11
          if ( v12 != 0 && v7 == 3 )  // 若 v12 != 0 && v7 == 3
          {
            *(uint32_t *)(pArg1 + 100) = v11 + 8;  // pArg1+100 = v11 + 8
LABEL_44:
            *(uint32_t *)(pArg1 + 88) = v7;  // pArg1+88 = v7
LABEL_45:
            *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v5 + 60))(v5) + 52) = v35;  // 虚调用 vt+60
            if ( *(uint8_t *)(pArg1 + 104) != 0 )  // 若 *(uint8_t *)(pArg1 + 104) != 0
            {
              v26 = *v5;
              pObj2 = *(uint32_t *)(pArg1 + 80);  // pObj2 = pArg1+80
              v27 = (*(int (**)(void))(*(uint32_t *)pObj2 + 128))();  // 调用虚函数槽 +128
              v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 124))(pObj2, *(uint32_t *)(pArg1 + 100) + v27);  // 调用虚函数槽 +124
              v29 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, *(uint32_t *)(pArg1 + 96) + v28);  // 调用虚函数槽 +120
              (*(void (/*thiscall*/ **)(int *, int))(v26 + 112))(v5, *(uint32_t *)(pArg1 + 92) + v29);  // 调用虚函数槽 +112
            }
            (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);  // 虚调用 vt+612
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);  // 虚调用 vt+820
            result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);  // 结果 = 虚调用 vt+200
            if ( result != nullptr )  // 若 result 非空
            {
              v30 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);  // 结果 = 虚调用 vt+200
              return sub_4938F0(v30);  // 调 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
            }
            return result;
          }
          if ( v7 != 0 )  // 若 v7 != 0
            goto LABEL_44;  // 跳转 LABEL_44
          v13 = *v5;
          v14 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);  // 结果 = 虚调用 vt+688
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 196))(v5, *(uint32_t *)(v14 + 12));  // 调用虚函数槽 +196
LABEL_43:
          v7 = v37;
          goto LABEL_44;  // 跳转 LABEL_44
        }
        if ( v7 == v10 )  // 若 v7 == v10
        {
          *(uint32_t *)(pArg1 + 92) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80)) != 0
                               ? 55
                               : -55;
          *(uint32_t *)(pArg1 + 96) = -1;  // pArg1+96 = -1
          if ( 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) <= 0 )  // 虚调用 vt+192
            *(uint32_t *)(pArg1 + 100) = 0;  // pArg1+100 = 0
          else
            *(uint32_t *)(pArg1 + 100) = 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5);  // 虚调用 vt+192
          goto LABEL_44;  // 跳转 LABEL_44
        }
        if ( v7 == 2 * (v9 != 0) + 3 )  // 若 v7 == 2 * (v9 != 0) + 3
        {
          v33 = 25;
          v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 192))(*(uint32_t *)(pArg1 + 80));  // 调用虚函数槽 +192
          if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) >= v15 )  // 虚调用 vt+192
          {
            v18 = 55;
          }
          else
          {
            v16 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 192))(*(uint32_t *)(pArg1 + 80));  // 调用虚函数槽 +192
            v17 = (uint64_t)((double)(v16 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5)) * 0.70721358);  // 结果 = 虚调用 vt+192
            v18 = 55 - v17;
            v33 = v17 + 25;
          }
          if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80)) == 0 )
            v18 = -v18;
          *(uint32_t *)(pArg1 + 100) = v33;  // pArg1+100 = v33
          v19 = *(uint8_t *)(pArg1 + 85);  // v19 = pArg1+85
          *(uint32_t *)(pArg1 + 92) = v18;  // pArg1+92 = v18
          *(uint32_t *)(pArg1 + 96) = -1;  // pArg1+96 = -1
          v34 = 1061746115;
          if ( v19 == 0 )  // 若 v19 == 0
            v34 = -1085737533;
        }
        else
        {
          if ( *(uint8_t *)(pArg1 + 84) == 0 )  // 若 *(uint8_t *)(pArg1 + 84) == 0
          {
            if ( v7 != 2 * (v9 != 0) + 4 )  // 若 v7 != 2 * (v9 != 0) + 4
              goto LABEL_44;  // 跳转 LABEL_44
            *(uint32_t *)(pArg1 + 92) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 80) + 152))(*(uint32_t *)(pArg1 + 80)) != 0
                                 ? -45
                                 : 45;
            *(uint32_t *)(pArg1 + 96) = -1;  // pArg1+96 = -1
            *(uint32_t *)(pArg1 + 100) = 0;  // pArg1+100 = 0
            v24 = *v5;
            v25 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);  // 结果 = 虚调用 vt+688
            (*(void (/*thiscall*/ **)(int *, uint32_t))(v24 + 196))(v5, *(uint32_t *)(v25 + 24));  // 调用虚函数槽 +196
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v5 + 272))(v5, 0, 0);  // 虚调用 vt+272
            goto LABEL_43;  // 跳转 LABEL_43
          }
          if ( v7 > 2 * (v9 != 0) + 6 )  // 若 v7 > 2 * (v9 != 0) + 6
          {
            *(uint8_t *)(pArg1 + 104) = 0;  // pArg1+104 = 0
            goto LABEL_44;  // 跳转 LABEL_44
          }
          v20 = 2 * (v9 != 0) + 5;
          pObj = *(uint32_t *)(pArg1 + 80);  // pObj = pArg1+80
          *(uint32_t *)(pArg1 + 92) = v37 != v20 ? -4 : 15;  // pArg1+92 = v37 != v20 ? -4 : 15
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 152))(pObj) == 0 )  // 虚槽+152 效果通道 3
            *(uint32_t *)(pArg1 + 92) = -*(uint32_t *)(pArg1 + 92);  // pArg1+92 = -*(uint32_t *)(pArg1 + 92)
          *(uint32_t *)(pArg1 + 96) = -1;  // pArg1+96 = -1
          *(uint32_t *)(pArg1 + 100) = -6;  // pArg1+100 = -6
          if ( v37 == v20 )  // 若 v37 == v20
            LOBYTE(v35) = sub_432E50(v35);  // 关系码对调映射
          v22 = *v5;
          v23 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);  // 结果 = 虚调用 vt+688
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v22 + 196))(v5, *(uint32_t *)(v23 + 24));  // 调用虚函数槽 +196
          v34 = 1057350484;
          if ( *(uint8_t *)(pArg1 + 85) == 0 )  // 若 *(uint8_t *)(pArg1 + 85) == 0
            v34 = -1090133164;
        }
        (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 272))(v5, 1, v34);  // 虚调用 vt+272
        goto LABEL_43;  // 跳转 LABEL_43
      }
    }
  }
  return result;
}

