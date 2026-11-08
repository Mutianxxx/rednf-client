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
int /*thiscall*/ sub_640250(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int result; // eax

  *(uint32_t *)(this + 40) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 108);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 9, 10, 11, 9, 0, 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 36) = v3;
  result = sub_69A840(v3);
  *(uint8_t *)(this + 48) = 0;
  *(uint8_t *)(this + 49) = 0;
  *(uint8_t *)(this + 50) = 0;
  *(uint8_t *)(this + 51) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 64) = 6;
  *(uint32_t *)(this + 68) = 12;
  *(uint32_t *)(this + 76) = 1600;
  *(uint32_t *)(this + 96) = dword_99FCCC;
  *(uint32_t *)(this + 52) = -16777216;
  return result;
}



// ------------------------------------------------------------
// 0x640320 sub_640320 —— 转职表现公共件（558090 + 44BD30/5E51F0/41FEB0/44BD00 + 63A7C0 强化结果件复用，122 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_640320(int this, uint32_t *a2, unsigned int a3, int a4)
{
  void *v4; // edx
  int v6; // ecx
  unsigned int v7; // eax
  int v9; // edx
  int v10; // edx
  unsigned int v11; // eax
  int v12; // edx
  int v13; // eax
  char *v14; // edi
  int v15; // ecx
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // eax
  bool v20; // cf
  int v21; // ecx
  int v22; // ebx
  int v23; // ebx
  int v24; // [esp-18h] [ebp-40h]
  int v25; // [esp-Ch] [ebp-34h]
  unsigned int v26; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int v33; // [esp+38h] [ebp+10h]

  v4 = *(void **)(a4 + 4);
  v28[0] = *(void **)a4;
  v6 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v6) >> 3;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v9 = 0;
    if ( 0x1FFFFFFF - v9 < a3 )
      sub_558090(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v18 = *(uint32_t *)(this + 8);
      v20 = (v18 - (int)a2) >> 3 < a3;
      v21 = 8 * a3;
      v30 = 8 * a3;
      v33 = v18;
      if ( v20 )
      {
        sub_44BD30(a2, v18, &a2[v21 / 4u]);
        v26 = a3 - ((*(uint32_t *)(this + 8) - (int)a2) >> 3);
        v25 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(v25, v26, v28);
        v22 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        sub_41FEB0(a2, (uint32_t *)(v22 - v30), v28);
      }
      else
      {
        v23 = v18 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(v18 - v21, v18, v18);
        sub_44BD00(a2, v23, v33);
        sub_41FEB0(a2, &a2[v30 / 4u], v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (v7 >> 1) >= v7 )
        v11 = (v7 >> 1) + v7;
      else
        v11 = 0;
      if ( v6 != 0 )
        v12 = (*(uint32_t *)(this + 8) - v6) >> 3;
      else
        v12 = 0;
      if ( v11 < a3 + v12 )
      {
        if ( v6 != 0 )
          v13 = (*(uint32_t *)(this + 8) - v6) >> 3;
        else
          v13 = 0;
        v11 = a3 + v13;
      }
      v31 = 8 * v11;
      v14 = (char *)operator new(8 * v11);
      v24 = *(uint32_t *)(this + 4);
      v28[2] = v14;
      v29 = 0;
      v32 = sub_44BD30(v24, a2, v14);
      sub_63A7C0(v32, a3, v28);
      sub_44BD30(a2, *(uint32_t *)(this + 8), v32 + 8 * a3);
      v15 = *(uint32_t *)(this + 4);
      if ( v15 != 0 )
        v16 = (*(uint32_t *)(this + 8) - v15) >> 3;
      else
        v16 = 0;
      v17 = v16 + a3;
      if ( v15 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v14[v31];
      *(uint32_t *)(this + 8) = &v14[8 * v17];
      *(uint32_t *)(this + 4) = v14;
    }
  }
}


// ------------------------------------------------------------
// 0x640570 sub_640570 —— 转职表现中层（63A7C0 + 640320）
// ------------------------------------------------------------
void /*thiscall*/ sub_640570(int this, uint32_t *a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  uint32_t *v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 3 )
  {
    v5 = *(uint32_t **)(this + 8);
    sub_63A7C0(v5, (uint32_t *)1, a2);
    *(uint32_t *)(this + 8) = v5 + 2;
  }
  else
  {
    sub_640320(this, *(char **)(this + 8), 1u, (int)a2);
  }
}



// ------------------------------------------------------------
// 0x6405E0 CNRDClassChangeWindow__vmtC —— CNRDClassChangeWindow__vmtC 打开主函数（223 行：4CE8A0 + 47E720 职业 + 565EE0 + 69A5F0 定位）；失败日志 "CRITICAL ERROR : CHARACTER CREATE FAIL! %d"
// ------------------------------------------------------------
char /*thiscall*/ sub_6405E0(void **this, int a2, int a3)
{
  void **v3; // ebx
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
  void **v45; // [esp+1Ch] [ebp-4h]

  v3 = this;
  v45 = this;
  *(uint32_t *)ArgList = *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 44);
  v4 = sub_4CE8A0(*(uint32_t *)ArgList);
  if ( v4 != 0 )
  {
    if ( v3[26] != nullptr )
      j__free(v3[26]);
    v3[26] = nullptr;
    v3[27] = nullptr;
    v3[28] = nullptr;
    if ( v3[30] != nullptr )
      j__free(v3[30]);
    v3[30] = nullptr;
    v3[31] = nullptr;
    v3[32] = nullptr;
    if ( v3[34] != nullptr )
      j__free(v3[34]);
    v6 = 16 * a3 + v4;
    v3[34] = nullptr;
    v3[35] = nullptr;
    v3[36] = nullptr;
    v7 = *(uint32_t **)(v6 + 648);
    v8 = v7 == *(uint32_t **)(v6 + 652);
    v43 = v6;
    if ( !v8 )
    {
      do
      {
        if ( v7[1] != 0 )
        {
          v9 = sub_47E720(*(uint32_t *)ArgList, *v7);
          if ( v9 != 0 )
          {
            v10 = v7[1];
            v41 = v9;
            v42 = v10;
            sub_640570(&v41);
          }
        }
        v6 = v43;
        v7 += 2;
      }
      while ( v7 != *(uint32_t **)(v43 + 652) );
    }
    v11 = (char *)&unk_99FC30 + 16 * *(uint32_t *)ArgList;
    v12 = *((int **)v11 + 1);
    v8 = v12 == *((int **)v11 + 2);
    v42 = (int)v11;
    if ( !v8 )
    {
      do
      {
        v13 = *v12;
        if ( *v12 != 0 && sub_41A5E0(v13 + 212) == 0 && sub_41A5E0(14 * a3 + v13 + 212) > 0 )
        {
          v14 = *(uint32_t *)(v13 + 468);
          for ( i = 0; v14 != 0 && i < (*(uint32_t *)(v13 + 472) - v14) >> 2; ++i )
          {
            if ( *(uint32_t *)(*(uint32_t *)(v13 + 468) + 4 * i) == a3 )
            {
              v16 = v45[26];
              for ( j = 0; v16 != nullptr && j < ((uint8_t *)v45[27] - v16) >> 3 && *((uint32_t *)v45[26] + 2 * j) != *v12; ++j )
                ;
              v18 = v45[26];
              if ( v18 != nullptr )
                v19 = ((uint8_t *)v45[27] - v18) >> 3;
              else
                v19 = 0;
              if ( j == v19 )
              {
                v20 = v45[30];
                v21 = (char *)(v45 + 29);
                if ( v20 != nullptr )
                  v22 = ((uint8_t *)v45[31] - v20) >> 2;
                else
                  v22 = 0;
                if ( v20 != nullptr && v22 < ((uint8_t *)v45[32] - v20) >> 2 )
                {
                  v23 = (int *)v45[31];
                  *v23 = *v12;
                  *((uint32_t *)v21 + 2) = v23 + 1;
                }
                else
                {
                  sub_565EE0(v45[31], 1, (int)v12);
                }
              }
              v3 = v45;
              break;
            }
            v3 = v45;
          }
        }
        ++v12;
      }
      while ( v12 != *(int **)(v42 + 8) );
      v6 = v43;
    }
    v24 = *(uint32_t **)(v6 + 648);
    if ( v24 != *(uint32_t **)(v6 + 652) )
    {
      do
      {
        if ( v24[1] == 0 )
        {
          v25 = sub_47E720(*(uint32_t *)ArgList, *v24);
          v26 = v3[34];
          v27 = (char *)(v3 + 33);
          v42 = v25;
          if ( v26 != nullptr )
            v28 = (*((uint32_t *)v27 + 2) - (int)v26) >> 2;
          else
            v28 = 0;
          if ( v26 != nullptr && v28 < (*((uint32_t *)v27 + 3) - (int)v26) >> 2 )
          {
            v29 = *((int **)v27 + 2);
            *v29 = v25;
            *((uint32_t *)v27 + 2) = v29 + 1;
          }
          else
          {
            sub_565EE0(*((void **)v27 + 2), 1, (int)&v42);
          }
          v3 = v45;
        }
        v24 += 2;
      }
      while ( v24 != *(uint32_t **)(v43 + 652) );
    }
    v3[11] = (void *)sub_418DD0(a3 + 4 * *(uint32_t *)ArgList + 4);
    v30 = v3[26];
    if ( v30 != nullptr )
      v31 = ((uint8_t *)v3[27] - v30) >> 3;
    else
      v31 = 0;
    v32 = v3[30];
    if ( v32 != nullptr )
      v33 = ((uint8_t *)v3[31] - v32) >> 2;
    else
      v33 = 0;
    v34 = v3[34];
    if ( v34 != nullptr )
      v35 = ((uint8_t *)v3[35] - v34) >> 2;
    else
      v35 = 0;
    v36 = v3[34];
    if ( v36 != nullptr )
      v37 = ((uint8_t *)v3[35] - v36) >> 2;
    else
      v37 = 0;
    (*((void (/*thiscall*/ **)(void **, int, unsigned int))*v3 + 6))(
      v3,
      22,
      3 * (((unsigned int)(v31 + 1) >> 1) + ((unsigned int)(v33 + 1) >> 1) + ((unsigned int)(v37 + 1) >> 1))
    + (v35 != 0 ? 3 : 0)
    + 14);
    v38 = v3[2];
    v39 = (480 - v38[8]) / 2;
    v40 = (640 - v38[7]) / 2;
    sub_69A5F0(v38, v40, v39);
    sub_69A5F0(
      v3[9],
      v40 + ((unsigned int)(*((uint32_t *)v3[2] + 7) - *((uint32_t *)v3[9] + 7)) >> 1),
      *((uint32_t *)v3[2] + 8) + v39 - 34);
    return 1;
  }
  else
  {
    off_77F3FC("CRITICAL ERROR : CHARACTER CREATE FAIL! %d", *(uint32_t *)ArgList);
    return 0;
  }
}


// ------------------------------------------------------------
// 0x640990 sub_640990 —— 转职窗列表（46 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_640990(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  uint32_t *v8; // esi
  int i; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 20);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 21);
  *(this + 20) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 22);
  *(this + 21) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 23);
  *(this + 22) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 19);
  *(this + 23) = 0;
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  *(this + 19) = 0;
  v8 = this + 10;
  for ( i = 9; i != 0; --i )
  {
    if ( *v8 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v8)(*v8, 1);
    *v8++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x640A10 sub_640A10 —— PVP 邀请数据（20 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_640A10(int this)
{
  if ( *(uint32_t *)(this + 100) != 0 )
    j__free(*(void **)(this + 100));
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  if ( *(uint32_t *)(this + 116) != 0 )
    j__free(*(void **)(this + 116));
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
}



// ------------------------------------------------------------
// 0x640A60 sub_640A60 —— PVP 邀请页绘制（418DD0/429830/42B340 + 491530/491630 + 42A430/42A410，111 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_640A60(int *this, int a2, int a3)
{
  int v4; // eax
  int v5; // ebx
  int v6; // ecx
  int v7; // edx
  unsigned int v8; // eax
  int result; // eax
  int v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // esi
  int v15; // esi
  int v16; // ebx
  bool v17; // cc
  int v18; // [esp+Ch] [ebp-Ch]
  int v19; // [esp+10h] [ebp-8h]
  int *v20; // [esp+14h] [ebp-4h]
  int v21; // [esp+20h] [ebp+8h]
  int v22; // [esp+24h] [ebp+Ch]

  v4 = sub_418DD0(81);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v4 + 152))(v4, a2, a3, dword_79C0B0);
  v5 = a3 + 35;
  v21 = a2 + 6;
  v6 = 0;
  v22 = a3 + 35;
  v19 = 0;
  v20 = this + 10;
  do
  {
    v7 = *(this + 25);
    v8 = v6 + *(this + 32);
    if ( v7 != 0 && v8 < (*(this + 26) - v7) >> 2 )
    {
      v18 = 4 * v8;
      result = sub_429830(*(uint16_t *)(4 * v8 + *(this + 25)));
      v10 = result;
      if ( result != 0 )
      {
        v11 = sub_42B340(result);
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v11 + 384))(
          v11,
          v21 + 3,
          v5 + 1,
          16,
          16,
          1065353216);
        sub_491530(2, 0);
        v12 = sub_42A430(v10);
        if ( v12 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v12 + 152))(v12, v21 + 22, v5, dword_79C0B0);
        sub_491630(2);
        v13 = sub_42A410(v10);
        if ( v13 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v13 + 152))(v13, v21 + 22, v5, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 33);
        if ( *(uint32_t *)(v10 + 40) < 0x10u )
          v14 = v10 + 20;
        else
          v14 = *(uint32_t *)(v10 + 20);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v21 + 55,
          v5 + 4,
          -1,
          v14);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        if ( *(uint32_t *)(*(this + 29) + v18) != 0 )
        {
          *(uint8_t *)(*v20 + 16) = 0;
          v15 = *(uint32_t *)(*v20 + 24);
          v16 = *(uint32_t *)(*v20 + 20);
          result = sub_418DD0(86);
          if ( result != 0 )
            result = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
                       result,
                       v16,
                       v15,
                       dword_79C0B0);
          v5 = v22;
        }
        else
        {
          result = *v20;
          *(uint8_t *)(*v20 + 16) = 1;
        }
        v5 += 20;
        v22 = v5;
      }
    }
    else
    {
      result = (int)v20;
      *(uint8_t *)(*v20 + 16) = 0;
    }
    v6 = v19 + 1;
    v17 = ++v19 < 9;
    ++v20;
  }
  while ( v17 );
  return result;
}



// ============================================================
// 【分区 2】PVP 战争房间邀请窗 CNRDPVPWarRoomInviteWindow（0x640C50-0x6414F0）
// vmtC 打开（287 行：4A2CF0 + 52DAA0/468240/430C80 房间数据 + 69C680）。
// ============================================================
// ------------------------------------------------------------
// 0x640C50 sub_640C50 —— PVP 邀请清理（42B530 + 423200/423290/423380）
// ------------------------------------------------------------
int /*thiscall*/ sub_640C50(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // esi
  int v6; // eax

  if ( *(uint32_t *)(dword_8F7A24 + 12) != 6 || (uint8_t)(result = sub_42B530(*(uint32_t **)(dword_8F7A24 + 40))) != 0 )
  {
    v4 = 4 * a2;
    *(uint32_t *)(4 * a2 + *(this + 29)) = 1;
    v5 = *(uint32_t *)(*(this + 25) + v4);
    sub_423200(dword_8F7B08, 10);
    a2 = v5;
    sub_423290(dword_8F7B08, (int)&a2, 2);
    v6 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v6 == 4 )
    {
      HIBYTE(a2) = 2;
      sub_423290(dword_8F7B08, (int)&a2 + 3, 1);
    }
    else if ( v6 == 6 )
    {
      HIBYTE(a2) = 3;
      sub_423290(dword_8F7B08, (int)&a2 + 3, 1);
    }
    a2 = 0;
    sub_423290(dword_8F7B08, (int)&a2, 4);
    return sub_423380(dword_8F7B08);
  }
  return result;
}



// ------------------------------------------------------------
// 0x640D10 sub_640D10 —— PVP 邀请页绘制 2（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630，132 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_640D10(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // ebx
  uint8_t *v5; // eax
  uint32_t *v6; // edi
  int v7; // ebx
  uint32_t *v8; // ecx
  uint8_t *v9; // edi
  int v10; // ebx
  uint8_t *v11; // edi
  int v12; // ebx
  uint8_t *v13; // edi
  uint32_t *v14; // eax
  int result; // eax
  int Block; // [esp+Ch] [ebp-14h]
  void *Blocka; // [esp+Ch] [ebp-14h]
  uint32_t *v18; // [esp+10h] [ebp-10h]

  *(uint32_t *)(this + 36) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 100);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(this + 36), 52, 53, 54, 52, 0, 0);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 76) = v3;
  sub_69A5F0(v3, 103, 218);
  sub_69A840(*(uint32_t *)(this + 76));
  v4 = (uint32_t *)(this + 40);
  Block = 37;
  v18 = (uint32_t *)(this + 40);
  do
  {
    v5 = operator new(0x84u);
    v6 = v5;
    if ( v5 != nullptr )
    {
      v7 = *(uint32_t *)(this + 36);
      sub_426BD0(v5);
      *v6 = &nengine::CNButton::`vftable';
      sub_69C780(v6);
      sub_69C7B0(v7, 83, 84, 85, 83, 0, 0);
      v4 = v18;
      v8 = v6;
    }
    else
    {
      v8 = nullptr;
    }
    *v4 = v8;
    sub_69A5F0(v8, 173, Block);
    sub_69A840(*v4++);
    v18 = v4;
    Block += 20;
  }
  while ( Block < 217 );
  v9 = operator new(0x84u);
  if ( v9 != nullptr )
  {
    v10 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
    sub_426BD0(v9);
    *(uint32_t *)v9 = &nengine::CNButton::`vftable';
    sub_69C780(v9);
    sub_69C7B0(v10, 4, 4, 5, 4, 0, 0);
  }
  else
  {
    v9 = nullptr;
  }
  *(uint32_t *)(this + 80) = v9;
  v11 = operator new(0x84u);
  if ( v11 != nullptr )
  {
    v12 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
    sub_426BD0(v11);
    *(uint32_t *)v11 = &nengine::CNButton::`vftable';
    sub_69C780(v11);
    sub_69C7B0(v12, 6, 6, 7, 6, 0, 0);
  }
  else
  {
    v11 = nullptr;
  }
  *(uint32_t *)(this + 84) = v11;
  v13 = operator new(0x88u);
  if ( v13 != nullptr )
  {
    Blocka = *(void **)(this + 36);
    sub_426BD0(v13);
    *(uint32_t *)v13 = &nengine::CNSlider::`vftable';
    sub_69CA20(v13);
    sub_69CA50(Blocka, 61, 60);
    *(uint32_t *)v13 = &nengine::CNVSlider::`vftable';
  }
  else
  {
    v13 = nullptr;
  }
  *(uint32_t *)(this + 88) = v13;
  if ( operator new(0x74u) != nullptr )
    v14 = (uint32_t *)sub_43C630(*(uint32_t *)(this + 80), *(uint32_t *)(this + 84), *(uint32_t *)(this + 88));
  else
    v14 = nullptr;
  *(uint32_t *)(this + 92) = v14;
  sub_69A5F0(v14, 239, 37);
  result = sub_69A840(*(uint32_t *)(this + 92));
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint8_t *)(this + 132) = 0;
  *(uint8_t *)(this + 133) = 0;
  *(uint8_t *)(this + 134) = 0;
  *(uint8_t *)(this + 135) = 0;
  *(uint32_t *)(this + 148) = 6;
  *(uint32_t *)(this + 152) = 12;
  *(uint32_t *)(this + 160) = 1600;
  *(uint32_t *)(this + 180) = dword_99FCCC;
  *(uint32_t *)(this + 160) = 120;
  *(uint32_t *)(this + 144) = 1;
  *(uint32_t *)(this + 136) = -16777216;
  return result;
}


// ------------------------------------------------------------
// 0x641050 CNRDPVPWarRoomInviteWindow__vmt8 —— CNRDPVPWarRoomInviteWindow__vmt8 Update（CLICK_BUTTON2 + 69C690 + 640C50 接受）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPVPWarRoomInviteWindow__vmt8(uint32_t *this)
{
  int v2; // edi
  uint32_t *v3; // ebx
  uint8_t *result; // eax

  *(this + 32) = sub_69C690(*(this + 23));
  v2 = 0;
  v3 = this + 10;
  do
  {
    if ( *(uint8_t *)(*v3 + 17) != 0
      && dword_79BE34 == *(uint32_t *)(*v3 + 12)
      && *(uint32_t *)(*(this + 29) + 4 * (v2 + *(this + 32))) == 0 )
    {
      sub_640C50(this, v2 + *(this + 32));
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
    ++v2;
    ++v3;
  }
  while ( v2 < 9 );
  result = (uint8_t *)*(this + 19);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6410F0 CNRDPVPWarRoomInviteWindow__vmt0 —— CNRDPVPWarRoomInviteWindow__vmt0 构造（转发 640A60 页绘制）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPVPWarRoomInviteWindow__vmt0(int *this, int a2)
{
  int result; // eax

  result = IRDPopupWindow__vmt0(a2);
  if ( a2 == *(this + 2) )
    return sub_640A60(this, *(uint32_t *)(a2 + 20), *(uint32_t *)(a2 + 24));
  return result;
}



// ------------------------------------------------------------
// 0x641120 CNRDPVPWarRoomInviteWindow__vmtC —— CNRDPVPWarRoomInviteWindow__vmtC 打开槽（287 行：4ED3F0 + 4A2CF0 + 52DAA0/468240/430C80 房间数据 + 69C680）
// ------------------------------------------------------------
char /*thiscall*/ sub_641120(uint32_t *this, int a2, int a3)
{
  uint32_t *v3; // edi
  uint32_t *v4; // ecx
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
  int *v31; // edx
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
  uint32_t *v58; // [esp+38h] [ebp-10h]
  int v59; // [esp+44h] [ebp-4h]
  uint32_t *v60; // [esp+50h] [ebp+8h]
  char v61; // [esp+53h] [ebp+Bh]

  v3 = this;
  v4 = (uint32_t *)*(this + 2);
  v58 = v3;
  sub_69A5F0(v4, 80, 80);
  v5 = v3 + 24;
  sub_4ED3F0((int)(v3 + 24), a2);
  v6 = sub_4A2CF0();
  v50 = v6;
  v59 = 0;
  v7 = sub_429830((uint16_t)word_77F804);
  v53 = v7;
  if ( v7 == 0 )
  {
    v8 = (uint32_t *)*v6;
    v9 = *v6 == (uint32_t)v6;
    *v6 = v6;
    v6[1] = v6;
    if ( !v9 )
    {
      do
      {
        v10 = (uint32_t *)*v8;
        j__free(v8);
        v8 = v10;
      }
      while ( v10 != v6 );
    }
    goto LABEL_66;
  }
  v11 = *(uint32_t *)(v7 + 116);
  v56 = -1;
  v55 = -1;
  v9 = *(uint32_t *)(dword_8F7A24 + 12) == 6;
  v54 = v11;
  v61 = 0;
  if ( v9 )
  {
    v12 = (int16_t *)((char *)dword_8F7C48 + 20 * *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76));
    v13 = v12[1];
    v56 = *v12;
    v55 = v13;
    v61 = 1;
  }
  v14 = 0;
  for ( i = 0; ; v14 = i )
  {
    v15 = v5[1];
    if ( v15 == 0 || v14 >= (v5[2] - v15) >> 2 )
      break;
    v16 = sub_429830(*(uint16_t *)(v3[25] + 4 * v14));
    if ( v16 != 0 )
    {
      v17 = abs32(v54 - *(uint32_t *)(v16 + 116));
      v52 = v17;
      if ( v16 != v53 )
      {
        for ( j = (uint32_t *)*v6; j != v50; j = (uint32_t *)*j )
        {
          if ( j[2] >= v17 )
            break;
        }
        if ( v61 != 0 )
        {
          v19 = sub_41A5E0(v16 + 53);
          if ( v19 >= v56 )
          {
            v20 = sub_41A5E0(v16 + 53);
            if ( v20 <= v55 )
            {
              v17 = v52;
              goto LABEL_19;
            }
          }
        }
        else
        {
LABEL_19:
          v21 = j[1];
          v22 = *(uint16_t *)(v16 + 4);
          v51[0] = v17;
          v51[1] = v22;
          v23 = sub_52DAA0(j, v21, v51);
          sub_468240(1);
          j[1] = v23;
          **(uint32_t **)(v23 + 4) = v23;
        }
        v6 = v50;
      }
    }
    v3 = v58;
    ++i;
  }
  if ( v5[1] != 0 )
    j__free((void *)v5[1]);
  v5[1] = 0;
  v5[2] = 0;
  v5[3] = 0;
  v24 = (uint32_t *)*v6;
  if ( v24 != v50 )
  {
    do
    {
      v25 = v5[1];
      if ( v25 != 0 )
        v26 = (v5[2] - v25) >> 2;
      else
        v26 = 0;
      if ( v25 != 0 && v26 < (v5[3] - v25) >> 2 )
      {
        v27 = (uint32_t *)v5[2];
        *v27 = v24[3];
        v5[2] = v27 + 1;
      }
      else
      {
        sub_430C80((void *)v5[2], 1, (int)(v24 + 3));
      }
      v24 = (uint32_t *)*v24;
    }
    while ( v24 != v50 );
    v3 = v58;
  }
  v28 = (void *)v3[29];
  v29 = v3 + 28;
  v30 = 0;
  if ( v28 != nullptr )
    j__free(v28);
  v31 = v58;
  v29[1] = 0;
  v29[2] = 0;
  v29[3] = 0;
  for ( k = v31 + 10; ; k = v60 + 1 )
  {
    v33 = v5[1];
    v60 = k;
    if ( v33 == 0 || v30 >= (unsigned int)((v5[2] - v33) >> 2) )
      break;
    v34 = v29[1];
    v52 = 0;
    if ( v34 != 0 )
      v35 = (v29[2] - v34) >> 2;
    else
      v35 = 0;
    if ( v34 != 0 && v35 < (v29[3] - v34) >> 2 )
    {
      v36 = (uint32_t *)v29[2];
      *v36 = 0;
      v29[2] = v36 + 1;
    }
    else
    {
      sub_430C80((void *)v29[2], 1, (int)&v52);
    }
    if ( v30 < 9 )
      *(uint8_t *)(*v60 + 16) = 1;
    v31 = v58;
    ++v30;
  }
  v37 = v5[1];
  if ( v37 == 0 || (unsigned int)((v5[2] - v37) >> 2) < 9 )
  {
    v38 = v5[1];
    if ( v38 != 0 )
    {
      v39 = (v5[2] - v38) >> 2;
      if ( v39 < 9 )
        goto LABEL_54;
    }
    else
    {
      v39 = 0;
LABEL_54:
      v40 = &v31[v39 + 10];
      v41 = 9 - v39;
      do
      {
        v42 = *v40++;
        --v41;
        *(uint8_t *)(v42 + 16) = 0;
      }
      while ( v41 != 0 );
      v31 = v58;
    }
  }
  v43 = *v31;
  v31[32] = 0;
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v43 + 24))(v31, 0, 0);
  v44 = v5[1];
  if ( v44 != 0 && (unsigned int)((v5[2] - v44) >> 2) >= 9 )
  {
    v45 = v5[1];
    if ( v45 != 0 )
      v46 = (v5[2] - v45) >> 2;
    else
      v46 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)v58[23] + 32))(v58[23], v46);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)v58[23] + 32))(v58[23], 0);
  }
  sub_69C680(0);
  v6 = v50;
  v47 = (uint32_t *)*v50;
  v9 = *v50 == (uint32_t)v50;
  *v50 = v50;
  v50[1] = v50;
  if ( !v9 )
  {
    do
    {
      v48 = (uint32_t *)*v47;
      j__free(v47);
      v47 = v48;
    }
    while ( v48 != v50 );
  }
LABEL_66:
  j__free(v6);
  return 1;
}


// ------------------------------------------------------------
// 0x6414D0 sub_6414D0 —— PVP 邀请收尾（18 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6414D0(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  return 0;
}



// ============================================================
// 【分区 3】好友列表窗 CNRDFriendListWindow（0x6414F0-0x6421A0）
// vmt0 构造（163 行：641C00 好友数据 + 479240 + 42B340）。
// ============================================================
// ------------------------------------------------------------
// 0x6414F0 sub_6414F0 —— 好友窗数据（52 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6414F0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  uint32_t *v3; // edi
  int i; // ebx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 10) = 0;
  v3 = this + 11;
  for ( i = 2; i != 0; --i )
  {
    if ( *v3 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v3)(*v3, 1);
    *v3++ = 0;
  }
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 14) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  *(this + 15) = 0;
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 43);
  result = 0;
  *(this + 16) = 0;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 43) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6415A0 CNRDFriendListWindow__vmtC —— CNRDFriendListWindow__vmtC 打开槽（69A5F0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDFriendListWindow__vmtC(uint32_t **this, int a2, int a3)
{
  dword_9B9530 = (int)this;
  sub_69A5F0(*(this + 2), 280, 55);
  return 1;
}



// ------------------------------------------------------------
// 0x6415C0 CNRDFriendListWindow__vmt10 —— CNRDFriendListWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDFriendListWindow__vmt10()
{
  dword_9B9530 = 0;
}



// ------------------------------------------------------------
// 0x6415D0 sub_6415D0 —— 好友列表构建（25 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6415D0(uint32_t *this)
{
  int v1; // eax
  int v2; // edx
  int v3; // ecx
  int result; // eax
  LONG i; // ecx

  v1 = *(this + 2);
  v2 = *(uint32_t *)(v1 + 20) + 11;
  v3 = *(uint32_t *)(v1 + 24) + 38;
  result = 0;
  for ( i = v3 + 17; pt.x < v2 - 3 || pt.x >= v2 + 226 || pt.y < i - 18 || pt.y >= i; i += 18 )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x641630 CNRDFriendListWindow__vmt8 —— CNRDFriendListWindow__vmt8 Update（CLICK_BUTTON2 + 69C690 + 479240/42B340 + 526BF0 私聊 + 527A60）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDFriendListWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  unsigned int v6; // edi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // ecx
  int v10; // edi
  int *v11; // eax
  void *v12; // eax
  uint32_t *v13; // edi
  int i; // ebx
  int v15; // eax
  uint8_t *result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 10);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v3 = *(this + 2);
  if ( *(uint8_t *)(v3 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v3 + 12) )
  {
    v4 = sub_6415D0(this);
    if ( v4 != -1 )
    {
      v5 = *(this + 45);
      v6 = v5 != 0 ? (*(this + 46) - v5) >> 2 : 0;
      if ( v4 + sub_69C690(*(this + 14)) < v6 )
      {
        v7 = sub_69C690(*(this + 14));
        v8 = (uint32_t *)sub_479240((uint32_t *)dword_8F8510, *(uint32_t *)(*(this + 45) + 4 * (v4 + v7)));
        v9 = v8[12];
        if ( v9 != 0 )
        {
          v10 = *(uint32_t *)(*(this + 4) + 48);
          v11 = (int *)sub_42B340(v9);
          sub_526BF0(v10, v11, 1);
        }
        else
        {
          if ( v8[6] < 0x10u )
            v12 = v8 + 1;
          else
            v12 = (void *)v8[1];
          sub_527A60(*(int ***)(*(this + 4) + 48), v12);
        }
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
  }
  v13 = this + 11;
  for ( i = 2; i != 0; --i )
  {
    if ( *(uint8_t *)(*v13 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*v13 + 12) )
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    ++v13;
  }
  v15 = *(this + 15);
  if ( *(uint8_t *)(v15 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v15 + 12) )
  {
    sub_44E8D0((char *)*(this + 4), (void *)9, 0, 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = (uint8_t *)*(this + 16);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    sub_44E8D0((char *)*(this + 4), (void *)9, 0, 1);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6417E0 sub_6417E0 —— 好友列表页绘制（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630 + 699E20/699E40，174 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6417E0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint8_t *v3; // ebx
  uint32_t *v4; // eax
  uint8_t *v5; // edi
  uint8_t *v6; // eax
  uint32_t *v7; // edi
  uint32_t *v8; // eax
  uint8_t *v9; // eax
  uint8_t *v10; // eax
  uint8_t *v11; // edi
  uint32_t *v12; // ecx
  uint8_t *v13; // edi
  uint32_t *v14; // ecx
  int v15; // ecx
  uint8_t *v16; // edi
  int v17; // edx
  void *Block; // [esp+10h] [ebp-18h]
  void *Blocka; // [esp+10h] [ebp-18h]
  void *Blockb; // [esp+10h] [ebp-18h]
  void *Blockc; // [esp+10h] [ebp-18h]
  void *Blockd; // [esp+10h] [ebp-18h]
  uint32_t *v24; // [esp+14h] [ebp-14h]
  int v25; // [esp+14h] [ebp-14h]
  int v26; // [esp+18h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v4 = sub_43C410(v2, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v4 = nullptr;
  *(this + 10) = v4;
  sub_69A5F0(v4, 230, 11);
  sub_69A840((uint32_t *)*(this + 2), *(this + 10));
  v26 = 4;
  v24 = this + 11;
  do
  {
    v5 = operator new(0x84u);
    if ( v5 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v5);
      *(uint32_t *)v5 = &nengine::CNButton::`vftable';
      sub_69C780((int)v5);
      sub_69C7B0((int)v5, (int)Block, v26, v26, v26 + 1, v26, 0, 0);
    }
    else
    {
      v5 = nullptr;
    }
    *v24++ = v5;
    v26 += 2;
  }
  while ( v26 < 8 );
  v6 = operator new(0x88u);
  v7 = v6;
  if ( v6 != nullptr )
  {
    Blocka = (void *)*(this + 9);
    sub_426BD0(v6);
    *v7 = &nengine::CNSlider::`vftable';
    sub_69CA20((int)v7);
    sub_69CA50((int)v7, (int)Blocka, 151, 86);
    *v7 = &nengine::CNVSlider::`vftable';
    v8 = v7;
  }
  else
  {
    v8 = nullptr;
  }
  *(this + 13) = v8;
  v9 = operator new(0x74u);
  if ( v9 != nullptr )
    v10 = sub_43C630(v9, *(this + 11), *(this + 12), *(this + 13));
  else
    v10 = nullptr;
  *(this + 14) = v10;
  sub_69A5F0(v10, 239, 35);
  sub_69A840((uint32_t *)*(this + 2), *(this + 14));
  v11 = operator new(0x84u);
  if ( v11 != nullptr )
  {
    Blockb = (void *)*(this + 9);
    sub_426BD0(v11);
    *(uint32_t *)v11 = &nengine::CNButton::`vftable';
    sub_69C780((int)v11);
    sub_69C7B0((int)v11, (int)Blockb, 144, 145, 146, 144, 0, 0);
    v12 = v11;
  }
  else
  {
    v12 = nullptr;
  }
  *(this + 15) = v12;
  sub_69A5F0(v12, 54, 202);
  sub_69A840((uint32_t *)*(this + 2), *(this + 15));
  v13 = operator new(0x84u);
  if ( v13 != nullptr )
  {
    Blockc = (void *)*(this + 9);
    sub_426BD0(v13);
    *(uint32_t *)v13 = &nengine::CNButton::`vftable';
    sub_69C780((int)v13);
    sub_69C7B0((int)v13, (int)Blockc, 147, 148, 149, 147, 0, 0);
    v14 = v13;
  }
  else
  {
    v14 = nullptr;
  }
  *(this + 16) = v14;
  sub_69A5F0(v14, 136, 202);
  sub_69A840((uint32_t *)*(this + 2), *(this + 16));
  *((uint8_t *)this + 68) = 0;
  *((uint8_t *)this + 69) = 0;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 71) = 0;
  *(this + 20) = 0;
  *(this + 23) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 22) = 12;
  *(this + 24) = 1600;
  *(this + 21) = 6;
  *(this + 29) = dword_99FCCC;
  *(this + 18) = -16777216;
  *((uint8_t *)this + 120) = 0;
  *((uint8_t *)this + 121) = 0;
  *((uint8_t *)this + 122) = 0;
  *((uint8_t *)this + 123) = 0;
  *(this + 33) = 0;
  *(this + 34) = 6;
  *(this + 35) = 12;
  *(this + 36) = 0;
  *(this + 37) = 1600;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *(this + 40) = 0;
  *(this + 41) = 0;
  *(this + 42) = 0;
  v15 = dword_99FCCC;
  *(this + 31) = -16777216;
  *(this + 42) = v15;
  *(this + 37) = 144;
  *(this + 33) = 1;
  *(this + 38) = 1;
  v16 = operator new(0x2Cu);
  if ( v16 != nullptr )
  {
    Blockd = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 12);
    v25 = dword_79C0B0;
    v16[4] = 0;
    *(uint32_t *)v16 = &nengine::CNNumberSet::`vftable';
    sub_699E20((int)v16);
    sub_699E40((int)v16, v25, (int)Blockd, 25, 2);
    v3 = v16;
  }
  v17 = *this;
  *(this + 43) = v3;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v17 + 24))(this, 20, 17);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);
}


// ------------------------------------------------------------
// 0x641C00 sub_641C00 —— 好友数据重建（479110/479240/430C80，148 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_641C00(int this)
{
  int result; // eax
  void *v2; // eax
  int v3; // esi
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
  if ( dword_8F8510 != 0 )
  {
    v2 = *(void **)(this + 180);
    v3 = this + 176;
    if ( v2 != nullptr )
      j__free(v2);
    *(uint32_t *)(v3 + 4) = 0;
    *(uint32_t *)(v3 + 8) = 0;
    *(uint32_t *)(v3 + 12) = 0;
    v4 = sub_479110(dword_8F8510);
    v5 = 0;
    v23 = v4;
    for ( i = 0; v5 < v23; i = v5 )
    {
      if ( *(uint32_t *)(sub_479240(v5) + 48) != 0 )
      {
        v6 = *(uint32_t *)(v3 + 4);
        if ( v6 != 0 )
          v7 = (*(uint32_t *)(v3 + 8) - v6) >> 2;
        else
          v7 = 0;
        if ( v6 != 0 && v7 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
        {
          v8 = *(int **)(v3 + 8);
          *v8 = v5;
          *(uint32_t *)(v3 + 8) = v8 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v3 + 8), 1, (int)&i);
        }
      }
      v4 = v23;
      ++v5;
    }
    v9 = 0;
    i = 0;
    if ( v4 > 0 )
    {
      do
      {
        v10 = sub_479240(v9);
        if ( *(int *)(v10 + 40) >= 0 && *(uint32_t *)(v10 + 48) == 0 )
        {
          v11 = *(uint32_t *)(v3 + 4);
          if ( v11 != 0 )
            v12 = (*(uint32_t *)(v3 + 8) - v11) >> 2;
          else
            v12 = 0;
          if ( v11 != 0 && v12 < (*(uint32_t *)(v3 + 12) - v11) >> 2 )
          {
            v13 = *(int **)(v3 + 8);
            *v13 = v9;
            *(uint32_t *)(v3 + 8) = v13 + 1;
          }
          else
          {
            sub_430C80(*(void **)(v3 + 8), 1, (int)&i);
          }
        }
        v4 = v23;
        i = ++v9;
      }
      while ( v9 < v23 );
    }
    v14 = 0;
    i = 0;
    if ( v4 > 0 )
    {
      do
      {
        v15 = sub_479240(v14);
        if ( *(int *)(v15 + 40) < 0 && *(uint32_t *)(v15 + 48) == 0 )
        {
          v16 = *(uint32_t *)(v3 + 4);
          if ( v16 != 0 )
            v17 = (*(uint32_t *)(v3 + 8) - v16) >> 2;
          else
            v17 = 0;
          if ( v16 != 0 && v17 < (*(uint32_t *)(v3 + 12) - v16) >> 2 )
          {
            v18 = *(int **)(v3 + 8);
            *v18 = v14;
            *(uint32_t *)(v3 + 8) = v18 + 1;
          }
          else
          {
            sub_430C80(*(void **)(v3 + 8), 1, (int)&i);
          }
        }
        i = ++v14;
      }
      while ( v14 < v23 );
    }
    v19 = *(uint32_t *)(v3 + 4);
    if ( v19 != 0 )
      v20 = (*(uint32_t *)(v3 + 8) - v19) >> 2;
    else
      v20 = 0;
    if ( v20 - 8 >= 0 )
    {
      v21 = *(uint32_t *)(v3 + 4);
      if ( v21 != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(
                 *(uint32_t *)(this + 56),
                 ((*(uint32_t *)(v3 + 8) - v21) >> 2) - 8);
      else
        return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), -8);
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 56) + 32))(*(uint32_t *)(this + 56), 0);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x641E10 CNRDFriendListWindow__vmt0 —— CNRDFriendListWindow__vmt0 构造（163 行：554930 + 641C00/6415D0/479240/42B340 + 69A110）
// ------------------------------------------------------------
int /*thiscall*/ sub_641E10(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // ecx
  int v11; // esi
  int v12; // esi
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // esi
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  uint32_t *v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // [esp+8h] [ebp-18h]
  int v27; // [esp+Ch] [ebp-14h]
  int v28; // [esp+10h] [ebp-10h]
  int v29; // [esp+14h] [ebp-Ch]
  unsigned int v30; // [esp+18h] [ebp-8h]
  int v31; // [esp+1Ch] [ebp-4h]
  int v32; // [esp+28h] [ebp+8h]

  result = sub_554930(a2);
  if ( a2 == *(this + 2) )
  {
    sub_641C00(this);
    v4 = *(uint32_t *)(a2 + 20);
    v5 = *(uint32_t *)(a2 + 24);
    v6 = sub_418DD0(143);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v4 + 6, v5 + 6, dword_79C0B0);
    v7 = sub_418DD0(150);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v4 + 6, v5 + 32, dword_79C0B0);
    v8 = v4 + 11;
    v27 = v8;
    v32 = v5 + 38;
    v9 = sub_69C690(*(this + 14));
    v10 = *(this + 2);
    v30 = v9;
    if ( *(uint8_t *)(v10 + 17) != 0
      && ((v11 = *(uint32_t *)(v10 + 12), dword_79BE3C == v11) || dword_79BE34 == v11 || dword_79BE38 == v11) )
    {
      v29 = sub_6415D0(this);
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
      v13 = sub_418DD0(94);
      if ( v13 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v13 + 152))(v13, v8, v32, dword_79C0B0);
      v14 = *(this + 45);
      if ( v14 != 0 && v30 < (*(this + 46) - v14) >> 2 )
      {
        v15 = (uint32_t *)sub_479240(*(uint32_t *)(*(this + 45) + 4 * v30));
        v16 = v15[12];
        if ( v16 != 0 )
        {
          v17 = sub_42B340(v16);
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v17 + 384))(
            v17,
            v8,
            v32,
            16,
            16,
            1065353216);
        }
        else
        {
          v18 = sub_418DD0(108);
          if ( v18 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v18 + 152))(v18, v8, v32, dword_79C0B0);
        }
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 17);
        (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v8 + 23,
          v31,
          v15[12] != 0 ? -4928551 : -8947849,
          "Lv.%d",
          v15[7]);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, this + 30);
        if ( v15[6] < 0x10u )
          v19 = v15 + 1;
        else
          v19 = (uint32_t *)v15[1];
        (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v8 + 17,
          v31,
          v15[12] != 0 ? -4928551 : -8947849,
          v19);
        v26 = *(uint32_t *)dword_79C0B0;
        v20 = sub_4B0EC0(v15[8], v15[9]);
        v8 = v27;
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v26 + 80))(
          dword_79C0B0,
          v27 + 96,
          v31,
          v15[12] != 0 ? -8005942 : -9934744,
          v20);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v21 = v15[12];
        if ( v21 != 0 )
        {
          if ( *(uint32_t *)(v21 + 68) != 0 )
            v22 = 154;
          else
            v22 = *(uint32_t *)(v21 + 184) != 0 ? 158 : 155;
          v23 = sub_418DD0(v22);
          if ( v23 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v23 + 152))(v23, v27 + 212, v32, dword_79C0B0);
        }
        else if ( (int)v15[10] >= 0 )
        {
          v24 = sub_418DD0(155);
          if ( v24 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v24 + 152))(v24, v27 + 212, v32, dword_79C0B0);
          sub_69A110(v27 + 208, v31 + 1, v15[10], -1);
        }
        v12 = v28;
        if ( v28 == v29 )
        {
          sub_491530(2, 0);
          v25 = sub_418DD0(22);
          if ( v25 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v25 + 152))(v25, v27 - 3, v31 - 4, dword_79C0B0);
          sub_491630(2);
        }
      }
      ++v12;
      ++v30;
      result = 19;
      v28 = v12;
      v32 += 19;
      v31 += 19;
    }
    while ( v12 < 8 );
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
int /*thiscall*/ sub_6421A0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  *(this + 11) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 15) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 12) = 0;
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  v8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v8 != nullptr )
    result = (**v8)(v8, 1);
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  *(this + 14) = 0;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 16) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x642220 CNRDPVPRoomListWindow__vmt10 —— CNRDPVPRoomListWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDPVPRoomListWindow__vmt10()
{
  dword_9B9534 = 0;
}



// ------------------------------------------------------------
// 0x642230 CNRDPVPRoomListWindow__vmt20 —— CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90/41D520 房间刷新）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPVPRoomListWindow__vmt20(void *this)
{
  if ( (uint8_t)sub_41C590(dword_8F7A24) != 1 )
    return IRDPopupWindow__vmt20(this);
  sub_46ED90(*(int **)(dword_8F7A24 + 36));
  return sub_41D520(dword_8F7A24);
}



// ------------------------------------------------------------
// 0x642270 sub_642270 —— PVP 房间列表条目（22 行）
// ------------------------------------------------------------
int sub_642270()
{
  LONG v0; // ecx
  int result; // eax

  v0 = 73;
  result = 0;
  while ( pt.x < 384 || pt.x >= 626 || pt.y < v0 || pt.y >= v0 + 20 )
  {
    ++result;
    v0 += 24;
    if ( result >= 12 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6422B0 sub_6422B0 —— PVP 房间列表绘制件（69A5F0/69C980，50 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_6422B0(int this, uint8_t a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // eax

  *(uint8_t *)(this + 196) = a2;
  sub_69A5F0(*(uint32_t **)(this + 8), dword_73E0F4[2 * a2], dword_73E0F8[2 * a2]);
  v3 = *(uint32_t *)(this + 8);
  v4 = 2 * *(uint8_t *)(this + 196);
  v5 = dword_73E108[v4];
  *(uint32_t *)(v3 + 28) = dword_73E104[v4];
  *(uint32_t *)(v3 + 32) = v5;
  v6 = *(uint32_t *)(this + 8);
  v7 = *(uint32_t *)(v6 + 20);
  v8 = *(uint32_t *)(v6 + 24);
  if ( a2 != 0 )
  {
    sub_69C980(*(uint32_t *)(this + 36), 256, 257, 258, -1, 0, 0);
    sub_69A5F0(*(uint32_t **)(this + 40), v7 + 15, v8 + 47);
    sub_69A5F0(*(uint32_t **)(this + 48), v7 + 141, v8 + 46);
    sub_69A5F0(*(uint32_t **)(this + 44), v7 + 240, v8 + 15);
    sub_69A5F0(*(uint32_t **)(this + 60), v7 + 60, v8 + 46);
    v9 = *(uint32_t *)(this + 52);
    *(uint8_t *)(v9 + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 56) + 16) = 0;
  }
  else
  {
    sub_69C980(*(uint32_t *)(this + 36), 253, 254, 255, -1, 0, 0);
    sub_69A5F0(*(uint32_t **)(this + 40), v7 + 15, v8 + 362);
    sub_69A5F0(*(uint32_t **)(this + 48), v7 + 141, v8 + 361);
    sub_69A5F0(*(uint32_t **)(this + 44), v7 + 240, v8 + 15);
    sub_69A5F0(*(uint32_t **)(this + 60), v7 + 60, v8 + 361);
    *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(this + 56) + 16) = 1;
    LOBYTE(v9) = 1;
  }
  return v9;
}



// ------------------------------------------------------------
// 0x642410 sub_642410 —— PVP 房间列表数据 2（14 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_642410(uint32_t *this, char a2)
{
  int result; // eax

  result = *(this + 15);
  *(uint8_t *)(result + 17) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x642420 sub_642420 —— PVP 房间列表页绘制（43C410/69A840/69A5F0 + 423B30 + 6422B0，127 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_642420(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // ecx
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // ecx
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // ecx
  uint32_t *v11; // eax
  uint32_t *v12; // eax
  uint32_t *v13; // ecx
  uint32_t *v14; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // eax
  uint32_t *v17; // eax
  uint8_t *v18; // eax
  uint8_t *v19; // eax
  int v20; // edx

  *(uint32_t *)(this + 36) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(this + 36), 253, 254, 255, -1, 0, 0);
  else
    v3 = nullptr;
  v4 = *(uint32_t **)(this + 8);
  *(uint32_t *)(this + 44) = v3;
  sub_69A840(v4, (int)v3);
  v5 = operator new(0x84u);
  if ( v5 != nullptr )
    v6 = sub_43C410(v5, *(uint32_t *)(this + 36), 284, 285, 286, -1, 0, 0);
  else
    v6 = nullptr;
  v7 = *(uint32_t **)(this + 8);
  *(uint32_t *)(this + 40) = v6;
  sub_69A840(v7, (int)v6);
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(uint32_t *)(this + 36), 247, 248, 249, -1, 0, 0);
  else
    v9 = nullptr;
  v10 = *(uint32_t **)(this + 8);
  *(uint32_t *)(this + 48) = v9;
  sub_69A840(v10, (int)v9);
  v11 = operator new(0x84u);
  if ( v11 != nullptr )
    v12 = sub_43C410(v11, *(uint32_t *)(this + 36), 287, 288, 289, 287, 0, 0);
  else
    v12 = nullptr;
  v13 = *(uint32_t **)(this + 8);
  *(uint32_t *)(this + 60) = v12;
  sub_69A840(v13, (int)v12);
  v14 = operator new(0x84u);
  if ( v14 != nullptr )
    v15 = sub_43C410(v14, *(uint32_t *)(this + 36), 76, 77, 78, 76, 0, 0);
  else
    v15 = nullptr;
  *(uint32_t *)(this + 52) = v15;
  sub_69A5F0(v15, 110, 340);
  sub_69A840(*(uint32_t **)(this + 8), *(uint32_t *)(this + 52));
  v16 = operator new(0x84u);
  if ( v16 != nullptr )
    v17 = sub_43C410(v16, *(uint32_t *)(this + 36), 79, 80, 81, 79, 0, 0);
  else
    v17 = nullptr;
  *(uint32_t *)(this + 56) = v17;
  sub_69A5F0(v17, 150, 340);
  sub_69A840(*(uint32_t **)(this + 8), *(uint32_t *)(this + 56));
  v18 = operator new(0x2Cu);
  if ( v18 != nullptr )
    v19 = sub_423B30(v18, dword_79C0B0, *(uint32_t *)(this + 36), 51, 3);
  else
    v19 = nullptr;
  *(uint32_t *)(this + 64) = v19;
  v19[24] = 1;
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 6;
  *(uint32_t *)(this + 88) = 12;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 96) = 1600;
  *(uint32_t *)(this + 116) = dword_99FCCC;
  *(uint32_t *)(this + 96) = 100;
  *(uint32_t *)(this + 80) = 1;
  *(uint32_t *)(this + 100) = 1;
  *(uint32_t *)(this + 72) = -16777216;
  *(uint8_t *)(this + 120) = 0;
  *(uint8_t *)(this + 121) = 0;
  *(uint8_t *)(this + 122) = 0;
  *(uint8_t *)(this + 123) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 6;
  *(uint32_t *)(this + 140) = 12;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 1600;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  v20 = dword_99FCCC;
  *(uint32_t *)(this + 124) = -16777216;
  *(uint32_t *)(this + 168) = v20;
  *(uint32_t *)(this + 148) = 144;
  *(uint32_t *)(this + 132) = 1;
  *(uint32_t *)(this + 152) = 1;
  sub_6422B0(0);
  *(uint8_t *)(this + 225) = 0;
  *(uint8_t *)(this + 226) = 0;
  return sub_698F90(this + 212, 5000, 0);
}


// ------------------------------------------------------------
// 0x642770 sub_642770 —— 房间列表文本（4014D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_642770(uint32_t *this, uint32_t *a2)
{
  qmemcpy(this, a2, 0x4Cu);
  sub_4014D0((std::_String_base *)(this + 19), a2 + 19, 0, -1);
  *(this + 26) = a2[26];
  *(this + 27) = a2[27];
  *(this + 28) = a2[28];
  return this;
}



// ------------------------------------------------------------
// 0x6427C0 sub_6427C0 —— 转发 642770
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6427C0(uint32_t *this, int a2)
{
  sub_642770(this + 1, (uint32_t *)(a2 + 4));
  return this;
}



// ------------------------------------------------------------
// 0x6427E0 sub_6427E0 —— 房间操作（4875C0）
// ------------------------------------------------------------
void */*thiscall*/ sub_6427E0(void **this, int *a2, int a3)
{
  char v3; // al
  uint32_t *v4; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)a2 + 137);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    v4 = (uint32_t *)sub_4875C0(*(this + 1), a3, *(this + 1), a2 + 3, *((uint8_t *)a2 + 136));
    if ( *((uint8_t *)Block + 137) != 0 )
      Block = v4;
    v6 = *a2;
    v10 = 0;
    *v4 = sub_6427E0(v6, v4);
    v4[2] = sub_6427E0(a2[2], v4);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x6428A0 sub_6428A0 —— 房间操作 2（436CA0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6428A0(int this)
{
  int v1; // esi
  uint32_t *result; // eax

  v1 = this + 200;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint8_t *)(this + 196) = 0;
  sub_436CA0(*(void ***)(*(uint32_t *)(this + 204) + 4));
  *(uint32_t *)(*(uint32_t *)(v1 + 4) + 4) = *(uint32_t *)(v1 + 4);
  result = *(uint32_t **)(v1 + 4);
  *(uint32_t *)(v1 + 8) = 0;
  *result = result;
  *(uint32_t *)(*(uint32_t *)(v1 + 4) + 8) = *(uint32_t *)(v1 + 4);
  return result;
}



// ------------------------------------------------------------
// 0x642900 sub_642900 —— 房间列表刷新（6427E0，46 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_642900(int this, int a2)
{
  int v3; // edi
  int **v4; // edx
  int *result; // eax
  int *v6; // ecx
  int v7; // esi
  int **v8; // ecx

  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(v3 + 4) = sub_6427E0((void **)this, *(int **)(*(uint32_t *)(a2 + 4) + 4), v3);
  *(uint32_t *)(this + 8) = *(uint32_t *)(a2 + 8);
  v4 = *(int ***)(this + 4);
  result = v4[1];
  if ( *((uint8_t *)result + 137) != 0 )
  {
    *v4 = (int *)v4;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 137) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 137) == 0 );
    }
    *v4 = result;
    v7 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(v7 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 137) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(v7 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x642990 sub_642990 —— PVP 房间列表重建（162 行：699000/698F90 + 438820/642900/430C80/4332F0/44E850）
// ------------------------------------------------------------
int /*thiscall*/ sub_642990(int this, uint32_t *a2)
{
  int v3; // ebx
  int result; // eax
  int v5; // esi
  int v6; // ebx
  int v7; // edi
  int v8; // edi
  uint32_t *v9; // ecx
  uint32_t *v10; // eax
  int v11; // ecx
  uint32_t *v12; // edi
  unsigned int v13; // edx
  uint32_t *v14; // eax
  uint32_t *v15; // ecx
  uint32_t *v16; // eax
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

  if ( (uint8_t)a2 == 0 )
  {
    v3 = *(uint32_t *)(this + 236);
    result = sub_699000(this + 212);
    if ( result < v3 )
      return result;
    *(uint8_t *)(this + 225) = 0;
    *(uint8_t *)(this + 226) = 0;
    sub_698F90(this + 212, 5000, 0);
  }
  v5 = this + 172;
  if ( *(uint32_t *)(this + 176) != 0 )
    j__free(*(void **)(this + 176));
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  v6 = dword_8F8504 + 4;
  v7 = this + 200;
  if ( v7 != dword_8F8504 + 4 )
  {
    sub_438820(&a2, **(uint32_t **)(v7 + 4), *(uint32_t *)(v7 + 4));
    sub_642900(v6);
  }
  v8 = this;
  v9 = *(uint32_t **)(this + 204);
  v10 = (uint32_t *)*v9;
  a2 = (uint32_t *)*v9;
  if ( a2 != v9 )
  {
    do
    {
      if ( v10[22] == 1 )
      {
        v11 = *(uint32_t *)(v5 + 4);
        v12 = v10 + 3;
        if ( v11 != 0 )
          v13 = (*(uint32_t *)(v5 + 8) - v11) >> 2;
        else
          v13 = 0;
        if ( v11 != 0 && v13 < (*(uint32_t *)(v5 + 12) - v11) >> 2 )
        {
          v14 = *(uint32_t **)(v5 + 8);
          *v14 = *v12;
          *(uint32_t *)(v5 + 8) = v14 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v5 + 8), 1, (int)v12);
        }
        v8 = this;
      }
      sub_4332F0(&a2);
      v10 = a2;
    }
    while ( a2 != *(uint32_t **)(v8 + 204) );
  }
  v15 = *(uint32_t **)(v8 + 204);
  v16 = (uint32_t *)*v15;
  a2 = (uint32_t *)*v15;
  if ( a2 != v15 )
  {
    do
    {
      if ( v16[22] == 2 )
      {
        v17 = *(uint32_t *)(v5 + 4);
        v18 = v16 + 3;
        if ( v17 != 0 )
          v19 = (*(uint32_t *)(v5 + 8) - v17) >> 2;
        else
          v19 = 0;
        if ( v17 != 0 && v19 < (*(uint32_t *)(v5 + 12) - v17) >> 2 )
        {
          v20 = *(uint32_t **)(v5 + 8);
          *v20 = *v18;
          *(uint32_t *)(v5 + 8) = v20 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v5 + 8), 1, (int)v18);
        }
        v8 = this;
      }
      sub_4332F0(&a2);
      v16 = a2;
    }
    while ( a2 != *(uint32_t **)(v8 + 204) );
  }
  if ( dword_795D3C != -1 )
  {
    v21 = *(uint32_t **)(v8 + 180);
    v22 = *(uint32_t **)(v8 + 176);
    if ( v22 == v21 )
      goto LABEL_35;
    do
    {
      if ( *v22 == dword_795D3C )
        break;
      ++v22;
    }
    while ( v22 != v21 );
    if ( v22 == v21 )
LABEL_35:
      sub_44E850(*(uint32_t **)(v8 + 16), 3);
  }
  v23 = *(uint32_t *)(v5 + 4);
  if ( v23 != 0 )
    v24 = (*(uint32_t *)(v5 + 8) - v23) >> 2;
  else
    v24 = 0;
  if ( (v24 - 1) / 12 <= 0 )
  {
    result = 0;
  }
  else
  {
    v25 = *(uint32_t *)(v5 + 4);
    if ( v25 != 0 )
      v26 = (*(uint32_t *)(v5 + 8) - v25) >> 2;
    else
      v26 = 0;
    result = (v26 - 1) / 12;
  }
  v27 = *(uint32_t *)(v8 + 188) <= result;
  *(uint32_t *)(v8 + 192) = result;
  if ( !v27 )
    *(uint32_t *)(v8 + 188) = result;
  return result;
}


// ------------------------------------------------------------
// 0x642BC0 CNRDPVPRoomListWindow__vmt8 —— CNRDPVPRoomListWindow__vmt8 Update（108 行：CLICK_BUTTON2 + 4873D0/487420 进入 + 642990 重建）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDPVPRoomListWindow__vmt8(void *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edx
  unsigned int v5; // ecx
  unsigned int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  uint8_t *result; // eax
  int v18; // [esp+4h] [ebp-Ch] BYREF
  int v19; // [esp+8h] [ebp-8h] BYREF
  uint8_t v20[4]; // [esp+Ch] [ebp-4h] BYREF

  v2 = *((uint32_t *)this + 2);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    v3 = sub_642270();
    if ( v3 != -1 )
    {
      v4 = *((uint32_t *)this + 44);
      v5 = v4 != 0 ? (*((uint32_t *)this + 45) - v4) >> 2 : 0;
      v6 = v3 + 12 * *((uint32_t *)this + 47);
      if ( v6 < v5 )
      {
        v7 = *(uint32_t *)(*((uint32_t *)this + 44) + 4 * v6);
        v19 = v7;
        sub_4873D0(&v18, &v19);
        v8 = v18;
        if ( v18 != *((uint32_t *)this + 51) )
        {
          v9 = sub_487420(v7);
          if ( v9 != 0 )
          {
            sub_6427C0((uint32_t *)(v8 + 16), v9);
            sub_44E8D0(*((char **)this + 4), (void *)3, 0, v7);
            sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
          }
        }
      }
    }
  }
  v10 = *((uint32_t *)this + 11);
  if ( *(uint8_t *)(v10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v10 + 12) )
  {
    sub_6422B0((int)this, *((uint8_t *)this + 196) == 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v11 = *((uint32_t *)this + 12);
  if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
  {
    sub_44E8D0(*((char **)this + 4), (void *)4, 0, 0);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  v12 = *((uint32_t *)this + 13);
  if ( *(uint8_t *)(v12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v12 + 12) )
  {
    v13 = *((uint32_t *)this + 47);
    if ( v13 > 0 )
    {
      *((uint32_t *)this + 47) = v13 - 1;
      sub_642990((int)this, (uint32_t *)1);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  v14 = *((uint32_t *)this + 14);
  if ( *(uint8_t *)(v14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v14 + 12) )
  {
    v15 = *((uint32_t *)this + 47);
    if ( v15 < *((uint32_t *)this + 48) )
    {
      *((uint32_t *)this + 47) = v15 + 1;
      sub_642990((int)this, (uint32_t *)1);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  v16 = *((uint32_t *)this + 10);
  if ( *(uint8_t *)(v16 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v16 + 12) )
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *((uint8_t **)this + 15);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    sub_423200(dword_8F7B08, 101);
    v20[0] = 0;
    sub_423290(dword_8F7B08, (int)v20, 1);
    sub_423380(dword_8F7B08);
    *(uint8_t *)(*((uint32_t *)this + 15) + 17) = 0;
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x642E20 CNRDPVPRoomListWindow__vmtC —— CNRDPVPRoomListWindow__vmtC 打开槽（642990 + 6422B0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPVPRoomListWindow__vmtC(void *this, int a2, int a3)
{
  dword_9B9534 = (int)this;
  sub_642990((int)this, (uint32_t *)1);
  sub_6422B0((int)this, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x642E40 CNRDPVPRoomListWindow__vmt0 —— CNRDPVPRoomListWindow__vmt0 构造（204 行：642990/642270 + 69A110 + 48F4C0/48FBB0）
// ------------------------------------------------------------
int /*userpurge*/ sub_642E40@<eax>(int a1@<ecx>, int a2@<ebx>, int a3)
{
  int result; // eax
  int v5; // edi
  int v6; // eax
  int v7; // ebx
  int i; // edi
  int v9; // eax
  int v10; // ecx
  char v11; // al
  unsigned int v12; // ebx
  int v13; // edi
  int v14; // eax
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
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
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

  result = *(uint32_t *)(a1 + 8);
  if ( a3 == result )
  {
    sub_642990(0);
    v5 = *(uint32_t *)(a3 + 24);
    v39 = *(uint32_t *)(a3 + 20);
    v33 = v5;
    v6 = sub_418DD0(244);
    if ( v6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v6 + 152))(v6, v39, v5, dword_79C0B0);
    v7 = *(uint32_t *)(sub_418DD0(244) + 24) + v5;
    if ( *(uint8_t *)(a1 + 196) == 0 )
    {
      for ( i = 21; i != 0; --i )
      {
        v9 = sub_418DD0(245);
        if ( v9 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v39, v7, dword_79C0B0);
        v7 += *(uint32_t *)(sub_418DD0(245) + 24);
      }
      v10 = *(uint32_t *)(a1 + 8);
      v32 = v7;
      v11 = *(uint8_t *)(v10 + 17);
      v12 = 12 * *(uint32_t *)(a1 + 188);
      v37 = v12;
      if ( v11 != 0
        && ((v13 = *(uint32_t *)(v10 + 12), dword_79BE3C == v13) || dword_79BE34 == v13 || dword_79BE38 == v13) )
      {
        v36 = sub_642270(a1);
      }
      else
      {
        v36 = -1;
      }
      v38 = 0;
      v40 = 74;
      do
      {
        v14 = sub_418DD0(21);
        if ( v14 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
            v14,
            384,
            v40 - 1,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            -1929379841,
            1333788672,
            1333788672);
        v15 = *(uint32_t *)(a1 + 176);
        if ( v15 != 0 && v12 < (*(uint32_t *)(a1 + 180) - v15) >> 2 )
        {
          v16 = *(int **)(a1 + 204);
          v17 = (int *)v16[1];
          v18 = (uint32_t *)(*(uint32_t *)(a1 + 176) + 4 * v12);
          while ( *((uint8_t *)v17 + 137) == 0 )
          {
            if ( v17[3] >= *v18 )
            {
              v16 = v17;
              v17 = (int *)*v17;
            }
            else
            {
              v17 = (int *)v17[2];
            }
          }
          v19 = *(int **)(a1 + 204);
          v35 = v16;
          if ( v16 == v19 || *v18 < v16[3] )
          {
            v34 = v19;
            v20 = (int *)&v34;
          }
          else
          {
            v20 = (int *)&v35;
          }
          v21 = *v20;
          if ( *v20 != *(uint32_t *)(a1 + 204) )
          {
            v22 = *(uint32_t *)(v21 + 20);
            v23 = (uint32_t *)(v21 + 16);
            sub_69A110(389, v40 + 3, v22, -1);
            (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 120, a2);
            v24 = v23[19];
            if ( v24 != 0 )
            {
              v25 = dword_99FEC4[v24];
            }
            else if ( v23[26] < 0x10u )
            {
              v25 = (int)(v23 + 21);
            }
            else
            {
              v25 = v23[21];
            }
            (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              423,
              v40 + 4,
              -4928551,
              v25);
            if ( v23[18] == 1 )
              v26 = sub_418DD0(74);
            else
              v26 = sub_418DD0(75);
            if ( v26 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v26 + 152))(v26, 607, v40, dword_79C0B0);
            a2 = a1 + 68;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0);
            v35 = *(int **)dword_79C0B0;
            v27 = sub_48F4C0(v23);
            v28 = sub_48FBB0(v23, v27);
            ((void (/*cdecl*/ *)(int, int, int, int, const char *, int))v35[20])(
              dword_79C0B0,
              536,
              v40 + 4,
              -3750202,
              "%d/%d",
              v28);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
            if ( v38 == v36 || v23[1] == dword_795D3C )
            {
              sub_491530(2, 0);
              v29 = sub_418DD0(46);
              if ( v29 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v29 + 152))(v29, 384, v40 - 1, dword_79C0B0);
              sub_491630(2);
            }
            v12 = v37;
          }
        }
        ++v12;
        v30 = ++v38 < 12;
        v37 = v12;
        v40 += 24;
      }
      while ( v30 );
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 68);
      (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v39 + 86,
        v33 + 340,
        -3750202,
        "%d/%d",
        *(uint32_t *)(a1 + 188) + 1,
        *(uint32_t *)(a1 + 192) + 1);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      v7 = v32;
    }
    result = sub_418DD0(246);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, v39, v7, dword_79C0B0);
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
int /*thiscall*/ CNRDDungeonMap__vmt8(int *this)
{
  int result; // eax

  result = *(this + 9);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  return result;
}



// ------------------------------------------------------------
// 0x643230 CNRDDungeonMap__vmtC —— CNRDDungeonMap__vmtC 打开槽（13 行）
// ------------------------------------------------------------
bool /*stdcall*/ CNRDDungeonMap__vmtC(int a1, int a2)
{
  int v2; // eax

  v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);
  return *(uint32_t *)(dword_8F7A24 + 12) == 3 && v2 != 0 && *(uint32_t *)(v2 + 68) != 0;
}



// ------------------------------------------------------------
// 0x643260 sub_643260 —— 副本地图成员清理（5542F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_643260(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *this = &vftbl_CNRDDungeonMap;
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 9) = 0;
  *this = &vftbl_IRDPopupWindow;
  return sub_5542F0(this);
}



// ------------------------------------------------------------
// 0x6432D0 CNRDDungeonMap__vmt4 —— CNRDDungeonMap__vmt4 析构（转发 643260）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDDungeonMap__vmt4(uint32_t *Block, char a2)
{
  sub_643260(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x643300 sub_643300 —— 副本地图清理（43C410/69A840）
// ------------------------------------------------------------
int /*thiscall*/ sub_643300(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int result; // eax

  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  sub_69A840(v3);
  result = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 84);
  *(this + 10) = result;
  return result;
}



// ------------------------------------------------------------
// 0x643390 CNRDDungeonMap__vmt0 —— CNRDDungeonMap__vmt0 构造（303 行：69A5F0 + 418DD0/40FC80 + 4D33A0）
// ------------------------------------------------------------
int /*thiscall*/ sub_643390(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // ecx
  int *v5; // eax
  int v6; // edx
  int v7; // edi
  int v8; // eax
  uint32_t *v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int v17; // ebx
  int v18; // eax
  bool v19; // zf
  int v20; // eax
  int v21; // edi
  int v22; // ebx
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // edi
  int v27; // eax
  int v28; // edi
  int v29; // ebx
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // ebx
  uint32_t *v34; // ecx
  uint32_t *v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // edi
  int v43; // eax
  int v44; // eax
  int v45; // edi
  int v46; // ebx
  int v47; // eax
  int v48; // eax
  int v49; // ebx
  int v50; // edi
  int v51; // eax
  int v52; // eax
  int v53; // edi
  int v54; // ebx
  int v55; // eax
  int v56; // eax
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
  int v70; // [esp+30h] [ebp-Ch]
  int v71; // [esp+34h] [ebp-8h]
  int v72; // [esp+38h] [ebp-4h]
  int v73; // [esp+44h] [ebp+8h]
  int v74; // [esp+44h] [ebp+8h]
  int v75; // [esp+44h] [ebp+8h]
  int v76; // [esp+44h] [ebp+8h]

  result = a2;
  v4 = *(this + 2);
  if ( a2 == v4 )
  {
    v59 = *(uint32_t **)(*(uint32_t *)(dword_8F7A24 + 28) + 16);
    v62 = (uint32_t *)v59[27];
    if ( v62 != nullptr && (v68 = v62[17]) != 0 )
    {
      v5 = (int *)(v62[42] + 8 * dword_99FB78);
      v6 = *v5;
      v64 = v6;
      v72 = v6;
      if ( v6 <= 3 )
        v72 = 3;
      if ( v6 == 2 )
        v72 = 3;
      v7 = v72;
      v63 = v5[1] + 1;
      v8 = 18 * v63;
      *(uint32_t *)(v4 + 32) = 18 * v63;
      v65 = v8;
      v7 *= 18;
      *(uint32_t *)(v4 + 28) = v7;
      v9 = (uint32_t *)*(this + 2);
      v69 = v7;
      sub_69A5F0(v9, 627 - v7, 30);
      sub_69A5F0((uint32_t *)*(this + 9), *(uint32_t *)(*(this + 2) + 20) + v7 - 16, *(uint32_t *)(*(this + 2) + 24) + 2);
      v66 = *(uint32_t *)(sub_418DD0(30) + 20);
      v10 = *(uint32_t *)(sub_418DD0(28) + 24);
      v11 = *(this + 2);
      v12 = *(uint32_t *)(v11 + 24);
      v13 = *(uint32_t *)(v11 + 20);
      v70 = v10;
      v14 = sub_418DD0(27);
      sub_40FC80(v13 - v66, v12 - v70, v14);
      if ( v72 > 0 )
      {
        v73 = 0;
        v67 = v72;
        do
        {
          v15 = *(this + 2);
          v16 = *(uint32_t *)(v15 + 24);
          v17 = *(uint32_t *)(v15 + 20);
          v18 = sub_418DD0(28);
          if ( v18 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v18 + 152))(v18, v73 + v17, v16 - v70, dword_79C0B0);
          v19 = v67 == 1;
          v73 += 18;
          --v67;
        }
        while ( !v19 );
      }
      v20 = *(this + 2);
      v21 = *(uint32_t *)(v20 + 24);
      v22 = *(uint32_t *)(v20 + 20);
      v23 = sub_418DD0(29);
      if ( v23 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v23 + 152))(v23, v22 + v69, v21 - v70, dword_79C0B0);
      v24 = 0;
      v67 = 0;
      if ( v63 > 0 )
      {
        while ( 1 )
        {
          v25 = *(this + 2);
          v26 = *(uint32_t *)(v25 + 20);
          v74 = *(uint32_t *)(v25 + 24) + 18 * v24;
          v27 = sub_418DD0(30);
          if ( v27 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v27 + 152))(v27, v26 - v66, v74, dword_79C0B0);
          v28 = 0;
          v71 = 0;
          if ( v72 > 0 )
            break;
LABEL_53:
          v42 = *(uint32_t *)(*(this + 2) + 20);
          v43 = sub_418DD0(32);
          if ( v43 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v43 + 152))(v43, v42 + v69, v74, dword_79C0B0);
          v67 = ++v24;
          if ( v24 >= v63 )
            goto LABEL_56;
        }
        while ( 1 )
        {
          v29 = *(uint32_t *)(*(this + 2) + 20) + 18 * v28;
          v70 = v29;
          v30 = sub_418DD0(31);
          if ( v30 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v30 + 152))(v30, v29, v74, dword_79C0B0);
          if ( v67 == 0 )
          {
            if ( v28 != 0 )
              v31 = (v28 == v72 - 1) + 39;
            else
              v31 = 38;
            v32 = sub_418DD0(v31);
            if ( v32 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v32 + 128))(
                v32,
                v29,
                v74,
                dword_79C0B0,
                1065353216,
                1065353216,
                0,
                1694498815,
                1333788672,
                1333788672);
            goto LABEL_51;
          }
          v33 = v67 - 1;
          v61 = -1;
          if ( v64 == v72 )
            goto LABEL_30;
          if ( v71 != 0 )
            break;
LABEL_50:
          v28 = v71;
LABEL_51:
          v71 = ++v28;
          if ( v28 >= v72 )
          {
            v24 = v67;
            goto LABEL_53;
          }
        }
        v28 = v71 - 1;
LABEL_30:
        v34 = (uint32_t *)(v62[42] + 8 * dword_99FB78);
        v60 = *(uint32_t *)(*(uint32_t *)(v62[46] + 16 * dword_99FB78 + 4) + 4 * (v28 + v33 * *v34));
        if ( v60 != 0 && v28 < v64 && (v35 = *(uint32_t **)(dword_99FBC4 + 4 * (v28 + v33 * *v34))) != nullptr )
        {
          v61 = v28 * v33 * *v35;
          v36 = sub_4D33A0(&v61) % 4 + 8 * v60 - 8;
        }
        else
        {
          v36 = v61;
        }
        if ( v59[28] == v28 && v59[29] == v33 )
        {
          v37 = sub_418DD0(v36 + 4);
          if ( v37 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v37 + 152))(v37, v70, v74, dword_79C0B0);
          v38 = sub_418DD0(3);
          if ( v38 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v38 + 152))(v38, v70 + 6, v74 + 4, dword_79C0B0);
        }
        else if ( dword_99FB7C == v28 && dword_99FB80 == v33 )
        {
          v39 = sub_418DD0(120);
          if ( v39 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v39 + 152))(v39, v70, v74, dword_79C0B0);
          v40 = sub_418DD0(37);
          if ( v40 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v40 + 152))(v40, v70 + 1, v74 + 2, dword_79C0B0);
        }
        else if ( v36 != -1 )
        {
          v41 = sub_418DD0(v36);
          if ( v41 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v41 + 152))(v41, v70, v74, dword_79C0B0);
        }
        goto LABEL_50;
      }
LABEL_56:
      v44 = *(this + 2);
      v45 = *(uint32_t *)(v44 + 24);
      v46 = *(uint32_t *)(v44 + 20);
      v75 = *(uint32_t *)(sub_418DD0(36) + 20);
      v47 = sub_418DD0(36);
      if ( v47 != 0 )
        (*(void (/*thiscall*/ **)(int, unsigned int, int, int))(*(uint32_t *)v47 + 152))(
          v47,
          ((unsigned int)(v69 - v75) >> 1) + v46 - 3,
          v45 + 3,
          dword_79C0B0);
      v48 = *(this + 2);
      v49 = *(uint32_t *)(v48 + 24);
      v50 = *(uint32_t *)(v48 + 20);
      v51 = sub_418DD0(33);
      if ( v51 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v51 + 152))(v51, v50 - v66, v49 + v65, dword_79C0B0);
      if ( v72 > 0 )
      {
        v76 = 0;
        v63 = v72;
        do
        {
          v52 = *(this + 2);
          v53 = *(uint32_t *)(v52 + 24);
          v54 = *(uint32_t *)(v52 + 20);
          v55 = sub_418DD0(34);
          if ( v55 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v55 + 152))(v55, v76 + v54, v53 + v65, dword_79C0B0);
          v19 = v63 == 1;
          v76 += 18;
          --v63;
        }
        while ( !v19 );
      }
      v56 = *(this + 2);
      v57 = *(uint32_t *)(v56 + 24);
      v58 = *(uint32_t *)(v56 + 20);
      result = sub_418DD0(35);
      if ( result != 0 )
        return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
                 result,
                 v58 + v69,
                 v57 + v65,
                 dword_79C0B0);
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x643910 sub_643910 —— 副本地图页部件（5542C0/5548B0 + 643300）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_643910(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  sub_5542C0();
  sub_5548B0(a2, 67);
  *this = &vftbl_CNRDDungeonMap;
  *(this + 9) = 0;
  sub_643300(this);
  return this;
}



// ============================================================
// 【分区 6】充值网页窗 CNRDPayWebWindow（0x643970-0x643F60）
// vmtC 打开（6439D0）：跳转 http://www.d-fighter.com（55CB40/652D30/652DE0）；
// vmt0 加载 Common/Etc/MonoLayer.img；643E10 装载 interface/payweb.img。
// ============================================================
// ------------------------------------------------------------
// 0x643970 sub_643970 —— 充值窗数据（32 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_643970(int this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 68) + 8))(*(uint32_t *)(this + 68));
  v2 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 68);
  if ( v2 != nullptr )
  {
    if ( *(v2 - 1) != nullptr )
    {
      (**v2)(v2, 3);
      *(uint32_t *)(this + 36) = 0;
      *(uint32_t *)(this + 60) = 0;
      *(uint32_t *)(this + 64) = 0;
      *(uint32_t *)(this + 68) = 0;
      *(uint32_t *)(this + 56) = 0;
      return;
    }
    j_j__free(v2 - 1);
  }
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 56) = 0;
}



// ------------------------------------------------------------
// 0x6439D0 CNRDPayWebWindow__vmtC —— CNRDPayWebWindow__vmtC 打开：跳转 http://www.d-fighter.com 充值站（55CB40 + 652D30/652DE0 + 422E70/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDPayWebWindow__vmtC(uint32_t *this, int a2, int a3)
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
  int v15; // [esp+124h] [ebp-4h]

  v15 = dword_796E50;
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0A4 + 64))(dword_79C0A4, 1) == 1 )
  {
    sprintf(Buffer, "http://www.d-fighter.com");
    *(this + 14) = *(uint32_t *)(a2 + 4);
    sub_55CB40();
    GetWindowRect(*(HWND *)(dword_79C0A0 + 16), &Rect);
    left = Rect.left;
    top = Rect.top;
    Rect.left += (Rect.right - Rect.left - 450) / 2;
    Rect.top += (Rect.bottom - Rect.top - 307) / 2;
    Rect.right = 450;
    Rect.bottom = 307;
    v6 = (HWND)sub_652D30(*(HWND *)(dword_79C0A0 + 16), *(HINSTANCE *)(dword_79C0A0 + 20), (int)&Rect, 0);
    *(this + 9) = v6;
    if ( v6 != nullptr )
    {
      sub_652DE0(v6, Buffer);
      v7 = Rect.left - left;
      v8 = Rect.top - top;
      right = Rect.right;
      *(this + 10) = Rect.left - left;
      *(this + 12) = right + v7;
      bottom = Rect.bottom;
      *(this + 11) = v8;
      *(this + 13) = bottom + v8;
      while ( ShowCursor(true) < 0 )
        ;
      *(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 60) = 0;
      *(this + 15) = 1;
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v4 = sub_422E70(1952);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v4, 0);
    return 0;
  }
}



// ------------------------------------------------------------
// 0x643B90 CNRDPayWebWindow__vmt10 —— CNRDPayWebWindow__vmt10 槽（55CB50）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPayWebWindow__vmt10(HWND *this)
{
  HWND v2; // eax
  int result; // eax

  v2 = *(this + 9);
  if ( v2 != nullptr )
  {
    SendMessageA(v2, 0x10u, 0, 0);
    *(this + 9) = nullptr;
  }
  sub_55CB50(*(this + 14));
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0A4 + 64))(dword_79C0A4, 0);
  do
    result = ShowCursor(false);
  while ( result >= 0 );
  *(uint32_t *)(*((uint32_t *)dword_8F8528 + 625) + 60) = 255;
  return result;
}



// ------------------------------------------------------------
// 0x643BF0 CNRDPayWebWindow__vmt8 —— CNRDPayWebWindow__vmt8 Update（CLICK_BUTTON2 + 652CC0 关闭网页层）
// ------------------------------------------------------------
HWND /*thiscall*/ CNRDPayWebWindow__vmt8(HWND *this)
{
  HWND result; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  HWND v6; // edx
  BOOL v7; // [esp+Ch] [ebp-4h]

  result = *(this + 9);
  v3 = 0;
  v4 = 0;
  if ( result != nullptr )
  {
    v7 = !IsWindow(result);
    v5 = (int)*(this + 17);
    if ( *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v5 + 12) )
    {
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      v4 = 1;
    }
    if ( sub_652CC0(*(this + 9)) == 0 )
      v3 = 1;
    result = (HWND)((char *)*(this + 15) - 1);
    if ( *(this + 15) == (HWND)1 )
    {
      if ( v3 == 1 )
      {
        ShowWindow(*(this + 9), 5);
        result = (HWND)UpdateWindow(*(this + 9));
        *(this + 15) = (HWND)2;
      }
    }
    else
    {
      result = (HWND)((char *)*(this + 15) - 2);
      if ( *(this + 15) == (HWND)2 )
      {
        if ( v3 != 0 )
        {
          result = (HWND)v7;
          if ( v7 )
          {
            v6 = *this;
            *(this + 9) = nullptr;
            result = (HWND)(*((int (/*thiscall*/ **)(HWND *))v6 + 8))(this);
            *(this + 15) = nullptr;
          }
          else if ( v4 != 0 )
          {
            result = (HWND)(*((int (/*thiscall*/ **)(HWND *))*this + 8))(this);
            *(this + 15) = nullptr;
          }
        }
        else
        {
          result = (HWND)ShowWindow(*(this + 9), 0);
          *(this + 15) = (HWND)1;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x643CF0 CNRDPayWebWindow__vmt0 —— CNRDPayWebWindow__vmt0 构造：加载 Common/Etc/MonoLayer.img 遮罩层（418DD0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDPayWebWindow__vmt0(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // eax

  result = a2;
  if ( a2 == *(this + 2) )
  {
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Common/Etc/MonoLayer.img");
    v4 = sub_418DD0(0);
    if ( v4 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v4 + 128))(
        v4,
        0,
        0,
        dword_79C0B0,
        1098907648,
        1094713344,
        0,
        -922746881,
        1333788672,
        1333788672);
    result = sub_418DD0(0);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
               result,
               *(this + 10) - 24,
               *(this + 11) - 31,
               dword_79C0B0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x643D80 sub_643D80 —— 充值窗收尾（643970 + 5542F0）
// ------------------------------------------------------------
int /*thiscall*/ sub_643D80(uint32_t *this)
{
  *this = &vftbl_CNRDPayWebWindow;
  sub_643970((int)this);
  *this = &vftbl_IRDPopupWindow;
  return sub_5542F0(this);
}



// ------------------------------------------------------------
// 0x643DE0 CNRDPayWebWindow__vmt4 —— CNRDPayWebWindow__vmt4 析构（转发 643D80）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDPayWebWindow__vmt4(uint32_t *Block, char a2)
{
  sub_643D80(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x643E10 sub_643E10 —— 装载资源 interface/payweb.img（69A5F0/69A840 定位，38 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_643E10(uint32_t *this)
{
  int v2; // ebx
  uint32_t *v3; // eax
  uint32_t *v4; // ecx
  uint32_t *v5; // edi

  *(this + 16) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                   dword_8F84B8,
                   "interface/payweb.img");
  v2 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v3 = operator new(0x88u);
  v4 = nullptr;
  if ( v3 != nullptr )
  {
    v5 = v3 + 1;
    *v3 = 1;
    `eh vector constructor iterator'(
      v3 + 1,
      0x84u,
      1,
      (void (/*thiscall*/ *)(void *))sub_46F750,
      (void (/*thiscall*/ *)(void *))sub_43C480);
    v4 = v5;
  }
  *(this + 17) = v4;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int, uint32_t, uint32_t, uint32_t))(*v4 + 32))(v4, v2, 68, 69, 70, 0, 0, 0);
  sub_69A5F0((uint32_t *)*(this + 17), 299, 403);
  sub_69A840(*(this + 17));
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 1);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 24))(this, 0, 0);
}



// ------------------------------------------------------------
// 0x643EF0 sub_643EF0 —— 充值窗页部件（5542C0/5548B0 + 643E10）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_643EF0(uint32_t *this, int a2)
{
  *this = &vftbl_IRDPopupWindow;
  sub_5542C0();
  sub_5548B0(a2, 51);
  *this = &vftbl_CNRDPayWebWindow;
  *(this + 9) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 14) = 0;
  sub_643E10(this);
  return this;
}



// ============================================================
// 【分区 7】公会列表窗 CNRDGuildListWindow（0x643F60-0x6453A0）
// vmt0 构造（309 行：644A20 公会数据 + 4BE300/4BE1D0 + 43BCB0）。
// ============================================================
// ------------------------------------------------------------
// 0x643F60 sub_643F60 —— 公会窗数据（52 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_643F60(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  uint32_t *v3; // edi
  int i; // ebx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v9)(uint32_t, int); // ecx
  int result; // eax

  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 12) = 0;
  v3 = this + 13;
  for ( i = 2; i != 0; --i )
  {
    if ( *v3 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v3)(*v3, 1);
    *v3++ = 0;
  }
  v5 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 15);
  if ( v5 != nullptr )
    (**v5)(v5, 1);
  v6 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 16);
  *(this + 15) = 0;
  if ( v6 != nullptr )
    (**v6)(v6, 1);
  v7 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 16) = 0;
  if ( v7 != nullptr )
    (**v7)(v7, 1);
  v8 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v8 != nullptr )
    (**v8)(v8, 1);
  v9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 56);
  result = 0;
  *(this + 11) = 0;
  if ( v9 != nullptr )
    result = (**v9)(v9, 1);
  *(this + 56) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x644010 CNRDGuildListWindow__vmtC —— CNRDGuildListWindow__vmtC 打开槽（69A5F0 + 478EA0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDGuildListWindow__vmtC(uint32_t **this, int a2, int a3)
{
  dword_9B9538 = (int)this;
  sub_69A5F0(*(this + 2), 378, 51);
  sub_478EA0(dword_8F8514, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x644040 CNRDGuildListWindow__vmt10 —— CNRDGuildListWindow__vmt10 状态切换槽（10 行）
// ------------------------------------------------------------
void CNRDGuildListWindow__vmt10()
{
  dword_9B9538 = 0;
}



// ------------------------------------------------------------
// 0x644050 sub_644050 —— 公会列表构建（25 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_644050(uint32_t *this)
{
  int v1; // eax
  int v2; // edx
  int v3; // ecx
  int result; // eax
  LONG i; // ecx

  v1 = *(this + 2);
  v2 = *(uint32_t *)(v1 + 20) + 11;
  v3 = *(uint32_t *)(v1 + 24) + 67;
  result = 0;
  for ( i = v3 + 17; pt.x < v2 - 3 || pt.x >= v2 + 226 || pt.y < i - 18 || pt.y >= i; i += 18 )
  {
    if ( ++result >= 8 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6440B0 CNRDGuildListWindow__vmt8 —— CNRDGuildListWindow__vmt8 Update（CLICK_BUTTON2 + 69C690 + 479240/42B340/526BF0）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDGuildListWindow__vmt8(uint32_t *this)
{
  int v2; // eax
  uint8_t *result; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  unsigned int v7; // edi
  int v8; // eax
  int v9; // ecx
  int v10; // edi
  int *v11; // eax
  uint32_t *v12; // edi
  int i; // ebx
  int v14; // eax
  int v15; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 12);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 32))(this);
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  else
  {
    v4 = *(this + 2);
    if ( *(uint8_t *)(v4 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v4 + 12) )
    {
      v5 = sub_644050(this);
      if ( v5 != -1 )
      {
        v6 = *(this + 59);
        v7 = v6 != 0 ? (*(this + 60) - v6) >> 2 : 0;
        if ( v5 + sub_69C690(*(this + 16)) < v7 )
        {
          v8 = sub_69C690(*(this + 16));
          v9 = *(uint32_t *)(sub_479240((uint32_t *)dword_8F8514, *(uint32_t *)(*(this + 59) + 4 * (v5 + v8))) + 48);
          if ( v9 != 0 )
          {
            v10 = *(uint32_t *)(*(this + 4) + 48);
            v11 = (int *)sub_42B340(v9);
            sub_526BF0(v10, v11, 1);
          }
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
      }
    }
    v12 = this + 13;
    for ( i = 2; i != 0; --i )
    {
      if ( *(uint8_t *)(*v12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(*v12 + 12) )
        sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      ++v12;
    }
    v14 = *(this + 10);
    if ( *(uint8_t *)(v14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v14 + 12) )
    {
      *(this + 57) = 1;
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
    v15 = *(this + 11);
    if ( *(uint8_t *)(v15 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v15 + 12) )
    {
      *(this + 57) = 0;
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
    result = (uint8_t *)*(this + 57);
    if ( result != nullptr )
    {
      if ( result == (uint8_t *)1 )
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
int /*thiscall*/ sub_644260(int this)
{
  *(uint32_t *)this = &vftbl_CNRDGuildListWindow;
  sub_643F60((uint32_t *)this);
  if ( *(uint32_t *)(this + 236) != 0 )
    j__free(*(void **)(this + 236));
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  if ( *(uint32_t *)(this + 216) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 216));
    *(uint32_t *)(this + 216) = 0;
  }
  *(uint8_t *)(this + 172) = 0;
  *(uint8_t *)(this + 173) = 0;
  *(uint8_t *)(this + 174) = 0;
  *(uint8_t *)(this + 175) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  if ( *(uint32_t *)(this + 164) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 164));
    *(uint32_t *)(this + 164) = 0;
  }
  *(uint8_t *)(this + 120) = 0;
  *(uint8_t *)(this + 121) = 0;
  *(uint8_t *)(this + 122) = 0;
  *(uint8_t *)(this + 123) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  if ( *(uint32_t *)(this + 112) != 0 )
  {
    DeleteObject(*(HGDIOBJ *)(this + 112));
    *(uint32_t *)(this + 112) = 0;
  }
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  return sub_5542F0(this);
}



// ------------------------------------------------------------
// 0x6443E0 CNRDGuildListWindow__vmt4 —— CNRDGuildListWindow__vmt4 析构（转发 644260）
// ------------------------------------------------------------
void */*thiscall*/ CNRDGuildListWindow__vmt4(void *Block, char a2)
{
  sub_644260((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x644410 sub_644410 —— 公会列表页绘制（43C410/69A5F0/69A840 + 426BD0/69C780/69C7B0/69CA20/69CA50/43C630 + 699E20/699E40，188 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_644410(uint32_t *this)
{
  uint32_t *v2; // eax
  uint8_t *v3; // ebx
  uint32_t *v4; // eax
  uint8_t *v5; // edi
  uint8_t *v6; // eax
  uint32_t *v7; // edi
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint8_t *v10; // edi
  uint32_t *v11; // ecx
  uint8_t *v12; // edi
  uint32_t *v13; // ecx
  uint8_t *v14; // edi
  int v15; // edx
  void *Block; // [esp+10h] [ebp-18h]
  void *Blocka; // [esp+10h] [ebp-18h]
  void *Blockb; // [esp+10h] [ebp-18h]
  void *Blockc; // [esp+10h] [ebp-18h]
  void *Blockd; // [esp+10h] [ebp-18h]
  uint32_t *v22; // [esp+14h] [ebp-14h]
  int v23; // [esp+14h] [ebp-14h]
  int v24; // [esp+18h] [ebp-10h]

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v4 = sub_43C410(v2, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v4 = nullptr;
  *(this + 12) = v4;
  sub_69A5F0(v4, 230, 11);
  sub_69A840(*(this + 12));
  v24 = 4;
  v22 = this + 13;
  do
  {
    v5 = operator new(0x84u);
    if ( v5 != nullptr )
    {
      Block = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 44);
      sub_426BD0(v5);
      *(uint32_t *)v5 = &nengine::CNButton::`vftable';
      sub_69C780(v5);
      sub_69C7B0(Block, v24, v24, v24 + 1, v24, 0, 0);
    }
    else
    {
      v5 = nullptr;
    }
    *v22++ = v5;
    v24 += 2;
  }
  while ( v24 < 8 );
  v6 = operator new(0x88u);
  v7 = v6;
  if ( v6 != nullptr )
  {
    Blocka = (void *)*(this + 9);
    sub_426BD0(v6);
    *v7 = &nengine::CNSlider::`vftable';
    sub_69CA20(v7);
    sub_69CA50(Blocka, 151, 86);
    *v7 = &nengine::CNVSlider::`vftable';
    v8 = v7;
  }
  else
  {
    v8 = nullptr;
  }
  *(this + 15) = v8;
  if ( operator new(0x74u) != nullptr )
    v9 = (uint32_t *)sub_43C630(*(this + 13), *(this + 14), *(this + 15));
  else
    v9 = nullptr;
  *(this + 16) = v9;
  sub_69A5F0(v9, 239, 65);
  sub_69A840(*(this + 16));
  v10 = operator new(0x84u);
  if ( v10 != nullptr )
  {
    Blockb = (void *)*(this + 9);
    sub_426BD0(v10);
    *(uint32_t *)v10 = &nengine::CNButton::`vftable';
    sub_69C780(v10);
    sub_69C7B0(Blockb, 162, 163, 164, -1, 0, 0);
    v11 = v10;
  }
  else
  {
    v11 = nullptr;
  }
  *(this + 10) = v11;
  sub_69A5F0(v11, 91, 229);
  sub_69A840(*(this + 10));
  v12 = operator new(0x84u);
  if ( v12 != nullptr )
  {
    Blockc = (void *)*(this + 9);
    sub_426BD0(v12);
    *(uint32_t *)v12 = &nengine::CNButton::`vftable';
    sub_69C780(v12);
    sub_69C7B0(Blockc, 159, 160, 161, -1, 0, 0);
    v13 = v12;
  }
  else
  {
    v13 = nullptr;
  }
  *(this + 11) = v13;
  sub_69A5F0(v13, 91, 229);
  sub_69A840(*(this + 11));
  *((uint8_t *)this + 68) = 0;
  *((uint8_t *)this + 69) = 0;
  *((uint8_t *)this + 70) = 0;
  *((uint8_t *)this + 71) = 0;
  *(this + 20) = 0;
  *(this + 23) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 24) = 1600;
  *(this + 21) = 6;
  *(this + 22) = 12;
  *(this + 29) = dword_99FCCC;
  *(this + 18) = -16777216;
  *(this + 34) = 6;
  *((uint8_t *)this + 120) = 0;
  *((uint8_t *)this + 121) = 0;
  *((uint8_t *)this + 122) = 0;
  *((uint8_t *)this + 123) = 0;
  *(this + 33) = 0;
  *(this + 35) = 12;
  *(this + 36) = 0;
  *(this + 37) = 1600;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *(this + 40) = 0;
  *(this + 41) = 0;
  *(this + 42) = 0;
  *(this + 42) = dword_99FCCC;
  *(this + 31) = -16777216;
  *(this + 37) = 144;
  *(this + 33) = 1;
  *(this + 38) = 1;
  *((uint8_t *)this + 172) = 0;
  *((uint8_t *)this + 173) = 0;
  *((uint8_t *)this + 174) = 0;
  *((uint8_t *)this + 175) = 0;
  *(this + 46) = 0;
  *(this + 47) = 6;
  *(this + 48) = 12;
  *(this + 49) = 0;
  *(this + 50) = 1600;
  *(this + 51) = 0;
  *(this + 52) = 0;
  *(this + 53) = 0;
  *(this + 54) = 0;
  *(this + 55) = 0;
  *(this + 55) = dword_99FCCC;
  *(this + 44) = -16777216;
  *(this + 46) = 1;
  *(this + 51) = 1;
  v14 = operator new(0x2Cu);
  if ( v14 != nullptr )
  {
    Blockd = *(void **)(*(uint32_t *)(dword_99FCC8 + 20) + 12);
    v23 = dword_79C0B0;
    v14[4] = 0;
    *(uint32_t *)v14 = &nengine::CNNumberSet::`vftable';
    sub_699E20(v14);
    sub_699E40(v23, Blockd, 25, 2);
    v3 = v14;
  }
  v15 = *this;
  *(this + 56) = v3;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v15 + 24))(this, 20, 19);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);
}


// ------------------------------------------------------------
// 0x644890 sub_644890 —— 公会列表页部件 2（5542C0/5548B0 + 422E70 + 644410）
// ------------------------------------------------------------
int /*thiscall*/ sub_644890(int this, int a2)
{
  *(uint32_t *)this = &vftbl_IRDPopupWindow;
  sub_5542C0();
  sub_5548B0(a2, 11);
  *(uint32_t *)this = &vftbl_CNRDGuildListWindow;
  *(uint8_t *)(this + 68) = 0;
  *(uint8_t *)(this + 69) = 0;
  *(uint8_t *)(this + 70) = 0;
  *(uint8_t *)(this + 71) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 6;
  *(uint32_t *)(this + 88) = 12;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 1600;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint8_t *)(this + 120) = 0;
  *(uint8_t *)(this + 121) = 0;
  *(uint8_t *)(this + 122) = 0;
  *(uint8_t *)(this + 123) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 6;
  *(uint32_t *)(this + 140) = 12;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 1600;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint8_t *)(this + 172) = 0;
  *(uint8_t *)(this + 173) = 0;
  *(uint8_t *)(this + 174) = 0;
  *(uint8_t *)(this + 175) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 6;
  *(uint32_t *)(this + 192) = 12;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 1600;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  if ( dword_9B953C[0] == 0 )
  {
    dword_9B953C[0] = (int)sub_422E70(939);
    dword_9B9540[0] = (int)sub_422E70(940);
  }
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 228) = 0;
  sub_644410((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x644A20 sub_644A20 —— 公会数据重建（479110/479240/430C80，158 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_644A20(int this)
{
  void *v1; // eax
  int v2; // esi
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

  v1 = *(void **)(this + 236);
  v2 = this + 232;
  if ( v1 != nullptr )
    j__free(v1);
  *(uint32_t *)(v2 + 4) = 0;
  *(uint32_t *)(v2 + 8) = 0;
  *(uint32_t *)(v2 + 12) = 0;
  v3 = sub_479110(dword_8F8514);
  v4 = 0;
  v27 = v3;
  v28 = 0;
  if ( v3 > 0 )
  {
    do
    {
      if ( *(uint32_t *)(sub_479240(v4) + 48) != 0 )
      {
        v5 = *(uint32_t *)(v2 + 4);
        if ( v5 != 0 )
          v6 = (*(uint32_t *)(v2 + 8) - v5) >> 2;
        else
          v6 = 0;
        if ( v5 != 0 && v6 < (*(uint32_t *)(v2 + 12) - v5) >> 2 )
        {
          v7 = *(int **)(v2 + 8);
          *v7 = v4;
          *(uint32_t *)(v2 + 8) = v7 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v2 + 8), 1, (int)&v28);
        }
      }
      v28 = ++v4;
    }
    while ( v4 < v27 );
    v3 = v27;
  }
  v8 = *(uint32_t *)(v2 + 4);
  if ( v8 != 0 )
    v9 = (*(uint32_t *)(v2 + 8) - v8) >> 2;
  else
    v9 = 0;
  v10 = 0;
  *(uint32_t *)(this + 248) = v9;
  v28 = 0;
  if ( v3 > 0 )
  {
    do
    {
      v11 = sub_479240(v10);
      if ( *(int *)(v11 + 40) >= 0 && *(uint32_t *)(v11 + 48) == 0 )
      {
        v12 = *(uint32_t *)(v2 + 4);
        if ( v12 != 0 )
          v13 = (*(uint32_t *)(v2 + 8) - v12) >> 2;
        else
          v13 = 0;
        if ( v12 != 0 && v13 < (*(uint32_t *)(v2 + 12) - v12) >> 2 )
        {
          v14 = *(int **)(v2 + 8);
          *v14 = v10;
          *(uint32_t *)(v2 + 8) = v14 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v2 + 8), 1, (int)&v28);
        }
      }
      v28 = ++v10;
    }
    while ( v10 < v27 );
    v3 = v27;
  }
  v15 = *(uint32_t *)(v2 + 4);
  if ( v15 != 0 )
    v16 = (*(uint32_t *)(v2 + 8) - v15) >> 2;
  else
    v16 = 0;
  v17 = 0;
  *(uint32_t *)(this + 252) = v16;
  v28 = 0;
  if ( v3 > 0 )
  {
    do
    {
      v18 = sub_479240(v17);
      if ( *(int *)(v18 + 40) < 0 && *(uint32_t *)(v18 + 48) == 0 )
      {
        v19 = *(uint32_t *)(v2 + 4);
        if ( v19 != 0 )
          v20 = (*(uint32_t *)(v2 + 8) - v19) >> 2;
        else
          v20 = 0;
        if ( v19 != 0 && v20 < (*(uint32_t *)(v2 + 12) - v19) >> 2 )
        {
          v21 = *(int **)(v2 + 8);
          *v21 = v17;
          *(uint32_t *)(v2 + 8) = v21 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v2 + 8), 1, (int)&v28);
        }
      }
      v28 = ++v17;
    }
    while ( v17 < v27 );
  }
  v22 = *(uint32_t *)(v2 + 4);
  if ( v22 != 0 )
    v23 = (*(uint32_t *)(v2 + 8) - v22) >> 2;
  else
    v23 = 0;
  if ( v23 - 8 < 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 64) + 32))(*(uint32_t *)(this + 64), 0);
  v25 = *(uint32_t *)(v2 + 4);
  if ( v25 != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 64) + 32))(
             *(uint32_t *)(this + 64),
             ((*(uint32_t *)(v2 + 8) - v25) >> 2) - 8);
  else
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 64) + 32))(*(uint32_t *)(this + 64), -8);
}


// ------------------------------------------------------------
// 0x644C60 CNRDGuildListWindow__vmt0 —— CNRDGuildListWindow__vmt0 构造（309 行：554930/429830/429900/4BF0F0 + 644A20/418DD0/4BE300/4BE1D0 + 43BCB0）
// ------------------------------------------------------------
int /*userpurge*/ sub_644C60@<eax>(uint32_t *a1@<ecx>, int a2@<edi>, int a3)
{
  int result; // eax
  int v5; // edi
  int v6; // ebx
  void *v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // edi
  int v14; // ebx
  int v15; // eax
  int v16; // edx
  int v17; // edi
  int v18; // eax
  uint8_t v19; // al
  int v20; // eax
  int v21; // ecx
  int v22; // edi
  int v23; // eax
  int v24; // ecx
  int v25; // ebx
  int v26; // eax
  int v27; // ecx
  uint32_t *v28; // edi
  int v29; // ecx
  int v30; // eax
  int v31; // eax
  uint32_t *v32; // ecx
  int v33; // edx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // eax
  int v38; // eax
  int v39; // eax
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
  int v64; // [esp+238h] [ebp-4h]
  int v65; // [esp+244h] [ebp+8h]

  v64 = dword_796E50;
  result = sub_554930(a3);
  if ( a3 == a1[2] )
  {
    v5 = *(uint32_t *)(a3 + 20);
    v6 = *(uint32_t *)(a3 + 24);
    v65 = v5;
    v59 = v6;
    result = sub_429830((uint16_t)word_77F804);
    if ( result != 0 )
    {
      v7 = (void *)sub_429900(dword_8F8500);
      if ( v7 != nullptr )
      {
        v61 = sub_4BF0F0(v7);
        sub_644A20(a1);
        v8 = v5 + 6;
        v9 = sub_418DD0(165);
        if ( v9 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v8, v6 + 6, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 43, a2);
        a1[50] = 243;
        a1[46] = 1;
        if ( *(uint32_t *)(dword_8F8514 + 44) < 0x10u )
          v10 = dword_8F8514 + 24;
        else
          v10 = *(uint32_t *)(dword_8F8514 + 24);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v65 + 6,
          v6 + 13,
          -5512193,
          v10);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        sub_4BE300(v61);
        v11 = sub_418DD0(189);
        if ( v11 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v11 + 152))(v11, v65 + 7, v6 + 33, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 43);
        v12 = a1[62];
        v49 = a1[63];
        a1[50] = 147;
        a1[46] = 1;
        v13 = *(uint32_t *)dword_79C0B0;
        v46 = v12;
        v14 = v6 + 40;
        v15 = sub_422E70(941);
        (*(void (/*cdecl*/ **)(int, int, int, int, int, int, int))(v13 + 80))(
          dword_79C0B0,
          v65 + 101,
          v14,
          -4928551,
          v15,
          v46,
          v49);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 43);
        v16 = a1[62];
        v50 = a1[63];
        a1[46] = 0;
        v17 = *(uint32_t *)dword_79C0B0;
        v47 = v16;
        v18 = sub_422E70(942);
        (*(void (/*cdecl*/ **)(int, int, int, int, int, int, int))(v17 + 80))(
          dword_79C0B0,
          v65 + 22,
          v14,
          -4928551,
          v18,
          v47,
          v50);
        if ( (uint8_t)sub_4BE1D0(v61) != 0xFF )
        {
          v60 = *(uint32_t *)dword_79C0B0;
          v19 = sub_4BE1D0(v61);
          (*(void (**)(int, int, int, int, const char *, ...))(v60 + 80))(
            dword_79C0B0,
            v65 + 72,
            v14,
            -701185,
            "%d",
            v19 + 1);
        }
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v20 = sub_418DD0(150);
        if ( v20 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 152))(v20, v65 + 7, v59 + 63, dword_79C0B0);
        v21 = a1[16];
        v22 = v59 + 69;
        v62 = v59 + 69;
        v23 = sub_69C690(v21);
        v24 = a1[2];
        v58 = v23;
        if ( (uint8_t)sub_43BCB0(v24) == 1 )
          v56 = sub_644050(a1);
        else
          v56 = -1;
        v25 = v59 + 72;
        v57 = 0;
        v60 = v59 + 72;
        do
        {
          v26 = sub_418DD0(94);
          if ( v26 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v26 + 152))(v26, v65 + 12, v22, dword_79C0B0);
          v27 = a1[59];
          if ( v27 != 0 && v58 < (a1[60] - v27) >> 2 )
          {
            v28 = (uint32_t *)sub_479240(*(uint32_t *)(a1[59] + 4 * v58));
            v29 = v28[12];
            if ( v29 != 0 )
            {
              v30 = sub_42B340(v29);
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int))(*(uint32_t *)v30 + 384))(
                v30,
                v65 + 12,
                v62,
                16,
                16,
                1065353216);
            }
            else
            {
              v31 = sub_418DD0(108);
              if ( v31 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v31 + 152))(v31, v65 + 12, v62, dword_79C0B0);
            }
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 17);
            (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v65 + 35,
              v25,
              v28[12] != 0 ? -4928551 : -8947849,
              "Lv.%d",
              v28[7]);
            (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0, a1 + 30);
            if ( v28[6] < 0x10u )
              v32 = v28 + 1;
            else
              v32 = (uint32_t *)v28[1];
            (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
              dword_79C0B0,
              v65 + 29,
              v25,
              v28[12] != 0 ? -4928551 : -8947849,
              v32);
            if ( a1[57] == 0 )
            {
              v33 = v28[8];
              v51 = v28[9];
              v55 = *(uint32_t *)dword_79C0B0;
              v34 = sub_4B0EC0(v33, v51);
              v25 = v60;
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(v55 + 80))(
                dword_79C0B0,
                v65 + 108,
                v60,
                v28[12] != 0 ? -8005942 : -9934744,
                v34);
            }
            if ( a1[57] == 1 )
              (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
                dword_79C0B0,
                v65 + 108,
                v25,
                v28[12] != 0 ? -3897898 : -9934744,
                v28 + 13);
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
            v35 = v28[12];
            if ( v35 != 0 )
            {
              if ( *(uint32_t *)(v35 + 68) != 0 )
                v36 = 154;
              else
                v36 = *(uint32_t *)(v35 + 184) != 0 ? 158 : 155;
              v37 = sub_418DD0(v36);
              if ( v37 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v37 + 152))(v37, v65 + 224, v62, dword_79C0B0);
            }
            else if ( (int)v28[10] >= 0 )
            {
              v38 = sub_418DD0(155);
              if ( v38 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v38 + 152))(v38, v65 + 224, v62, dword_79C0B0);
              sub_69A110(v65 + 220, v25 + 1, v28[10], -1);
            }
            if ( v57 == v56 )
            {
              sub_491530(2, 0);
              v39 = sub_418DD0(22);
              if ( v39 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v39 + 152))(v39, v65 + 9, v25 - 4, dword_79C0B0);
              sub_491630(2);
            }
          }
          v22 = v62 + 19;
          v25 += 19;
          v40 = ++v57 < 8;
          ++v58;
          v62 += 19;
          v60 = v25;
        }
        while ( v40 );
        result = sub_4BE1D0(v61);
        if ( (uint8_t)result != 0xFF )
        {
          x = pt.x;
          y = pt.y;
          v43 = sub_4BE1D0(v61);
          rc.left = v65 + 7;
          rc.top = v59 + 33;
          rc.right = v65 + 98;
          rc.bottom = v59 + 58;
          result = PtInRect(&rc, (POINT)__PAIR64__(y, x));
          if ( result == 1 )
          {
            if ( v43 == 1 )
            {
              sprintf(Buffer, "%s\n", (const char *)dword_9B9540[0]);
            }
            else
            {
              v44 = v43;
              v52 = dword_9B9540[v44];
              v48 = dword_9B953C[v44];
              v45 = (const char *)sub_422E70(943);
              sprintf(Buffer, v45, v48, v52);
            }
            return sub_4649B0(rc.left + (rc.right - rc.left) / 2, rc.top - 2, -1, -16777216, 2, Buffer, 0, 0, 1600, 1);
          }
        }
      }
      else
      {
        return (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 32))(a1);
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
int /*cdecl*/ sub_6453A0(int a1, unsigned int a2)
{
  if ( a2 < 2 )
    return a1;
  if ( a2 == 2 )
    return 2 * a1;
  if ( a2 == 3 )
    return 4 * a1;
  else
    return a1;
}



// ------------------------------------------------------------
// 0x6453D0 sub_6453D0 —— 商城数据 2（26 行）
// ------------------------------------------------------------
const CHAR */*cdecl*/ sub_6453D0(int a1)
{
  const CHAR *result; // eax

  switch ( a1 )
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
  if ( a1 != 3 )
    return szPassword;
  return result;
}



// ------------------------------------------------------------
// 0x645410 sub_645410 —— 商城数据 3（45 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645410(int this)
{
  uint32_t *v3; // ecx

  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  v3 = (uint32_t *)(this + 32);
  *v3 = 0;
  v3[1] = 0;
  v3[2] = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  memset((void *)(this + 52), 0, 0x40u);
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 2072) = 0;
  *(uint32_t *)(this + 2076) = 0;
  *(uint32_t *)(this + 2080) = 0;
  *(uint32_t *)(this + 2084) = 0;
  memset((void *)(this + 2088), 0, 0xF0u);
  memset((void *)(this + 340), 0, 0x690u);
  *(uint32_t *)(this + 2020) = 0;
  *(uint32_t *)(this + 2024) = 0;
  *(uint32_t *)(this + 2028) = 0;
  *(uint32_t *)(this + 2032) = 0;
  *(uint32_t *)(this + 2036) = 0;
  *(uint32_t *)(this + 2040) = 0;
  *(uint32_t *)(this + 2044) = 0;
  *(uint32_t *)(this + 2048) = 0;
  *(uint8_t *)(this + 2052) = 0;
  *(uint32_t *)(this + 2068) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6454C0 sub_6454C0 —— 商城 MonoLayer 面板（Common/Etc/MonoLayer.img + 418DD0，78 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6454C0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  uint32_t *v5; // edi
  int i; // ebx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v8)(uint32_t, int); // ecx
  uint32_t *v9; // edi
  int j; // ebx
  int (/*thiscall*/ ***v11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v12)(uint32_t, int); // ecx
  uint32_t *v13; // edi
  int k; // ebx
  uint32_t *v15; // esi
  int m; // edi

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 3);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 3) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 4) = 0;
  v5 = this + 8;
  for ( i = 3; i != 0; --i )
  {
    if ( *v5 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v5)(*v5, 1);
    *v5++ = 0;
  }
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  v8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;
  if ( v8 != nullptr )
    result = (**v8)(v8, 1);
  *(this + 12) = 0;
  v9 = this + 29;
  for ( j = 2; j != 0; --j )
  {
    if ( *v9 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v9)(*v9, 1);
    *v9++ = 0;
  }
  v11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 32);
  if ( v11 != nullptr )
    result = (**v11)(v11, 1);
  v12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 31);
  *(this + 32) = 0;
  if ( v12 != nullptr )
    result = (**v12)(v12, 1);
  *(this + 31) = 0;
  v13 = this + 518;
  for ( k = 4; k != 0; --k )
  {
    if ( *v13 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v13)(*v13, 1);
    *v13++ = 0;
  }
  v15 = this + 522;
  for ( m = 60; m != 0; --m )
  {
    if ( *v15 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v15)(*v15, 1);
    *v15++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x6455D0 sub_6455D0 —— 商城面板（418DD0，42 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6455D0(uint32_t *this)
{
  int v2; // eax
  int v3; // esi
  int result; // eax

  (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, "Common/Etc/MonoLayer.img");
  v2 = sub_418DD0(0);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v2 + 128))(
      v2,
      0,
      0,
      dword_79C0B0,
      1098907648,
      1094713344,
      0,
      -922746881,
      1333788672,
      1333788672);
  v3 = *(this + 510);
  result = sub_418DD0(v3 != 0 ? 0 : 0x23);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             dword_73E220[v3],
             58,
             dword_79C0B0,
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
int /*thiscall*/ sub_645680(int16_t *this)
{
  int v2; // edi
  int v3; // ebx
  int16_t *v4; // edx
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
  int v17; // [esp-4h] [ebp-11Ch]
  int v18; // [esp+Ch] [ebp-10Ch]
  int Value; // [esp+10h] [ebp-108h]
  char Buffer[256]; // [esp+14h] [ebp-104h] BYREF
  int v21; // [esp+114h] [ebp-4h]

  v21 = dword_796E50;
  (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (uint32_t *)this + 33);
  sprintf(Buffer, "%2d/%-2d", *((uint32_t *)this + 511) + 1, *((uint32_t *)this + 512) + 1);
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 160, 409, -1, Buffer);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  v2 = 0;
  v3 = 0;
  Value = 0;
  if ( *((int *)this + 509) > 0 )
  {
    v4 = this + 183;
    v18 = *((uint32_t *)this + 509);
    while ( 1 )
    {
      v5 = *v4;
      v6 = *(uint32_t *)(v4 + 3);
      if ( *v4 != 0 && v5 != 1 )
      {
        if ( v5 == 2 )
        {
          v6 *= 2;
        }
        else if ( v5 == 3 )
        {
          v6 *= 4;
        }
      }
      v3 += v6;
      v7 = *(uint32_t *)(v4 + 5);
      if ( *v4 != 0 && v5 != 1 )
      {
        if ( v5 == 2 )
        {
          v7 *= 2;
        }
        else if ( v5 == 3 )
        {
          v7 *= 4;
        }
      }
      v2 += v7;
      v8 = *(uint32_t *)(v4 + 7);
      if ( *v4 == 0 || v5 == 1 )
        break;
      if ( v5 == 2 )
      {
        v9 = 2 * v8;
      }
      else
      {
        v10 = v5 == 3;
        v9 = 4 * v8;
        if ( !v10 )
          break;
      }
LABEL_21:
      v4 += 42;
      v10 = v18 == 1;
      Value += v9;
      --v18;
      if ( v10 )
        goto LABEL_22;
    }
    v9 = *(uint32_t *)(v4 + 7);
    goto LABEL_21;
  }
LABEL_22:
  (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (uint32_t *)this + 72);
  v17 = *((uint32_t *)this + 509);
  v11 = (const char *)sub_422E70(891);
  sprintf(Buffer, v11, v17);
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 403, 141, -1, Buffer);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (uint32_t *)this + 46);
  if ( v2 > 0 )
  {
    v12 = (const char *)sub_422E70(892);
    sprintf(Buffer, v12, v2);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      454 - *((uint32_t *)this + 53),
      187,
      -15920333,
      Buffer);
  }
  if ( v3 > 0 )
  {
    v13 = (const char *)sub_422E70(893);
    sprintf(Buffer, v13, v3);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      593 - *((uint32_t *)this + 53),
      187,
      -15920333,
      Buffer);
  }
  if ( Value > 0 )
  {
    sub_69A110(568, 215, Value, -1);
    v14 = *(uint32_t *)dword_79C0B0;
    v15 = sub_422E70(894);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v14 + 80))(
      dword_79C0B0,
      592 - *((uint32_t *)this + 53),
      219,
      -15920333,
      v15);
  }
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
}


// ------------------------------------------------------------
// 0x645930 sub_645930 —— 商城列表构建 2（422E70 + 69A110，164 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645930(uint32_t *this)
{
  int v2; // ecx
  BOOL v3; // edi
  int v4; // eax
  int16_t *v5; // edx
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
  int v22; // [esp-4h] [ebp-164h]
  int v23; // [esp-4h] [ebp-164h]
  int v24; // [esp+Ch] [ebp-154h]
  int v25; // [esp+10h] [ebp-150h]
  int v26; // [esp+14h] [ebp-14Ch]
  int v27; // [esp+18h] [ebp-148h]
  int v28; // [esp+1Ch] [ebp-144h]
  int v29; // [esp+20h] [ebp-140h]
  int v30; // [esp+24h] [ebp-13Ch]
  uint32_t v31[9]; // [esp+28h] [ebp-138h]
  int v32; // [esp+4Ch] [ebp-114h]
  int v33; // [esp+50h] [ebp-110h]
  int v34; // [esp+54h] [ebp-10Ch]
  int v35; // [esp+58h] [ebp-108h]
  char Buffer[256]; // [esp+5Ch] [ebp-104h] BYREF
  int v37; // [esp+15Ch] [ebp-4h]

  v37 = dword_796E50;
  v25 = 265;
  v27 = 265;
  v2 = *(this + 510);
  v31[2] = 255;
  v31[4] = 255;
  v24 = 454;
  v26 = 593;
  v28 = 572;
  v29 = 289;
  v30 = 596;
  v3 = v2 != 0;
  v4 = *(this + 509);
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
  if ( v4 > 0 )
  {
    v5 = (int16_t *)this + 183;
    v32 = v4;
    while ( 1 )
    {
      v6 = *v5;
      v7 = *(uint32_t *)(v5 + 3);
      if ( *v5 != 0 && v6 != 1 )
      {
        if ( v6 == 2 )
        {
          v7 *= 2;
        }
        else if ( v6 == 3 )
        {
          v7 *= 4;
        }
      }
      v8 = v7 + v33;
      v9 = *(uint32_t *)(v5 + 5);
      v33 = v8;
      if ( v6 >= 2 )
      {
        if ( v6 == 2 )
        {
          v9 *= 2;
        }
        else if ( v6 == 3 )
        {
          v9 *= 4;
        }
      }
      v10 = v9 + v34;
      v11 = *(uint32_t *)(v5 + 7);
      v34 = v10;
      if ( v6 < 2 )
        break;
      if ( v6 == 2 )
      {
        v12 = 2 * v11;
      }
      else
      {
        v13 = v6 == 3;
        v12 = 4 * v11;
        if ( !v13 )
          break;
      }
LABEL_19:
      v5 += 42;
      v13 = v32 == 1;
      v35 += v12;
      --v32;
      if ( v13 )
        goto LABEL_20;
    }
    v12 = v11;
    goto LABEL_19;
  }
LABEL_20:
  *(this + 514) = (*(int (/*thiscall*/ **)(uint32_t))(***((uint32_t ***)dword_8F852C + 3) + 44))(**((uint32_t **)dword_8F852C + 3))
                - v33;
  v14 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 8) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 8));
  v15 = v35;
  *(this + 515) = v14 - v34;
  *(this + 516) = dword_8F7C0C - v15;
  (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 46);
  v22 = *(this + 515);
  v16 = (const char *)sub_422E70(899);
  sprintf(Buffer, v16, v22);
  v17 = 32 * v3;
  (*(void (/*cdecl*/ **)(int, int, uint32_t, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    *(int *)((char *)&v24 + v17) - *(this + 53),
    *(int *)((char *)&v25 + v17),
    (int)*(this + 515) < 0 ? -16776961 : -1,
    Buffer);
  v23 = *(this + 514);
  v18 = (const char *)sub_422E70(900);
  sprintf(Buffer, v18, v23);
  (*(void (/*cdecl*/ **)(int, int, uint32_t, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    *(int *)((char *)&v26 + v17) - *(this + 53),
    *(int *)((char *)&v27 + v17),
    (int)*(this + 514) < 0 ? -16776961 : -1,
    Buffer);
  sub_69A110(*(int *)((char *)&v28 + v17), *(int *)((char *)&v29 + v17), *(this + 516), -1);
  v19 = *(uint32_t *)dword_79C0B0;
  v20 = sub_422E70(901);
  (*(void (/*cdecl*/ **)(int, int, uint32_t, int, int))(v19 + 80))(
    dword_79C0B0,
    v31[v17 / 4 - 1] - *(this + 53),
    v31[v17 / 4],
    (int)*(this + 514) < 0 ? -16776961 : -1,
    v20);
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
}


// ------------------------------------------------------------
// 0x645CA0 sub_645CA0 —— 商城取消（12 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645CA0(uint32_t *this)
{
  *(uint8_t *)(*(this + 3) + 16) = 0;
  memset(this + 85, 0, 0x690u);
  return 0;
}



// ------------------------------------------------------------
// 0x645CC0 sub_645CC0 —— 商城下单确认（423200 系参数 + 55F160/55D300/55CB40，45 行——被确认窗 vmt38 调用）
// ------------------------------------------------------------
int /*thiscall*/ sub_645CC0(int this)
{
  int v2; // ebx
  int v3; // esi
  int v5; // [esp+8h] [ebp-8h] BYREF
  uint8_t v6[4]; // [esp+Ch] [ebp-4h] BYREF

  v2 = 0;
  *(uint32_t *)(*(uint32_t *)(this + 8) + 10108) = 0;
  sub_423200(dword_8F7B08, 67);
  v6[0] = *(uint8_t *)(this + 2036);
  sub_423290(dword_8F7B08, (int)v6, 1);
  if ( *(int *)(this + 2036) > 0 )
  {
    v3 = this + 356;
    do
    {
      if ( *(uint32_t *)(v3 + 60) != 0 )
      {
        v6[0] = *(uint8_t *)v3;
        sub_423290(dword_8F7B08, (int)v6, 1);
        v5 = *(uint16_t *)(v3 + 10);
        sub_423290(dword_8F7B08, (int)&v5, 2);
        v5 = *(uint32_t *)(v3 - 16);
        sub_423290(dword_8F7B08, (int)&v5, 4);
      }
      ++v2;
      v3 += 84;
    }
    while ( v2 < *(uint32_t *)(this + 2036) );
  }
  sub_423380(dword_8F7B08);
  sub_55F160(*(uint32_t *)(*(uint32_t *)(this + 8) + 44));
  sub_55D300(*(uint32_t *)(this + 8));
  sub_55CB40(*(uint32_t *)(this + 8));
  *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 0;
  memset((void *)(this + 340), 0, 0x690u);
  return 0;
}



// ------------------------------------------------------------
// 0x645DB0 sub_645DB0 —— 商城条目状态（44E850/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_645DB0(uint32_t *this)
{
  int v1; // eax
  int v2; // eax
  int v3; // edx
  int v4; // esi
  int v5; // edi
  uint32_t *v6; // edi
  LONG v7; // edx
  LONG v8; // edx
  char *v10; // [esp+Ch] [ebp-4h]

  v10 = (char *)*(this + 1);
  v1 = *((uint32_t *)v10 + 626);
  if ( v1 == 1 || v1 == 2 )
    goto LABEL_20;
  v2 = *(this + 510);
  if ( v2 == 0 )
  {
    v2 = 0;
    v6 = this + 104;
    while ( v2 < 20 )
    {
      if ( *v6 != 0 )
      {
        v7 = dword_795DB0[2 * v2];
        if ( pt.x >= v7 && pt.x <= v7 + 28 )
        {
          v8 = dword_795DB4[2 * v2];
          if ( pt.y >= v8 && pt.y <= v8 + 28 )
          {
            v5 = dword_795DB4[2 * v2];
            v3 = *(this + 21 * v2 + 104);
            v4 = dword_795DB0[2 * v2];
            goto LABEL_19;
          }
        }
      }
      ++v2;
      v6 += 21;
    }
    goto LABEL_20;
  }
  v3 = *(this + 104);
  if ( v3 == 0 || pt.x < 191 || pt.x > 219 || pt.y < 118 || pt.y > 146 )
    goto LABEL_20;
  v4 = 191;
  v5 = 118;
LABEL_19:
  if ( v3 == 0 )
  {
LABEL_20:
    LOBYTE(v2) = dword_9B88D0;
    if ( dword_9B88D0 != 0 && dword_795378 == 5 )
      LOBYTE(v2) = sub_44E850(v10, 26);
    return v2;
  }
  if ( dword_9B88D0 != v3 || dword_795378 != 5 )
  {
    v2 = sub_44E8D0(v10, (void *)0x1A, v3, 5);
    if ( v2 != 0 )
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)v2 + 48))(v2, v4, v5, 28, 28);
  }
  return v2;
}



// ------------------------------------------------------------
// 0x645EE0 sub_645EE0 —— 商城数据 4（23 行）
// ------------------------------------------------------------
int */*thiscall*/ sub_645EE0(int *this)
{
  int *result; // eax
  int i; // ecx
  int v3; // esi

  *(uint8_t *)(*(this + 519) + 16) = 0;
  *(uint8_t *)(*(this + 520) + 16) = 0;
  *(uint8_t *)(*(this + 521) + 16) = 0;
  result = this + 522;
  for ( i = 60; i != 0; --i )
  {
    v3 = *result++;
    *(uint8_t *)(v3 + 16) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x645F20 sub_645F20 —— 商城数据 5（55ECC0 + 645EE0）
// ------------------------------------------------------------
void /*thiscall*/ sub_645F20(int *this, int a2)
{
  int v4; // eax
  int16_t v5; // di
  int v6; // eax
  const void *v7; // eax
  int v8; // edx
  const void *v9; // esi
  int v10; // ecx
  int *i; // eax
  int *v12; // edx
  char v13; // [esp+10h] [ebp+8h]

  if ( a2 > 0 && a2 <= 3 )
  {
    v4 = *(this + 517);
    v5 = *(uint16_t *)(v4 + 26);
    *(uint16_t *)(v4 + 26) = 1;
    v6 = *(this + 517);
    v13 = *(uint8_t *)(v6 + 16);
    v7 = (const void *)sub_55ECC0(*(uint32_t *)(v6 + 12), *(int16_t *)(v6 + 26), a2);
    v8 = *(this + 517);
    v9 = v7;
    if ( v7 != nullptr )
    {
      v10 = 0;
      for ( i = this + 85; (int *)v8 != i; i += 21 )
      {
        if ( ++v10 >= 20 )
          return;
      }
      v12 = this + 21 * v10;
      qmemcpy(v12 + 85, v9, 0x54u);
      *((uint8_t *)v12 + 420) = 0;
      *((uint8_t *)v12 + 356) = v13;
      sub_645EE0(this);
    }
    else
    {
      *(uint16_t *)(v8 + 26) = v5;
    }
  }
}



// ------------------------------------------------------------
// 0x645FD0 sub_645FD0 —— 商城条目刷新（422E70，155 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_645FD0(void *this, int a2, int a3, unsigned int a4, uint32_t *a5)
{
  int v5; // edi
  int v6; // esi
  int v7; // eax
  const char *v8; // eax
  char *v9; // eax
  unsigned int v10; // eax
  char *v11; // edi
  char v12; // cl
  char *v13; // edi
  uint32_t *v14; // esi
  char v15; // cl
  int v16; // eax
  char *v17; // eax
  unsigned int v18; // eax
  char *v19; // edi
  char v20; // cl
  char *v21; // edi
  uint32_t *v22; // esi
  char v23; // cl
  char *v24; // eax
  unsigned int v25; // eax
  char *v26; // edi
  char v27; // cl
  int v29; // [esp-4h] [ebp-21Ch]
  int v30; // [esp-4h] [ebp-21Ch]
  int v31; // [esp+Ch] [ebp-20Ch]
  void *v32; // [esp+10h] [ebp-208h] BYREF
  char Buffer[256]; // [esp+14h] [ebp-204h] BYREF
  uint32_t v34[65]; // [esp+114h] [ebp-104h] BYREF
  int v35; // [esp+22Ch] [ebp+14h]

  v34[64] = dword_796E50;
  v32 = this;
  memset(Buffer, 0, sizeof(Buffer));
  memset(v34, 0, 256);
  v5 = a5[9];
  v6 = a5[8];
  v7 = a5[10];
  v31 = v5;
  v35 = v7;
  if ( a4 != 0 )
  {
    if ( a4 == 1 )
    {
      v8 = (const char *)&unk_73E2A0;
    }
    else if ( a4 == 2 )
    {
      v8 = (const char *)&unk_73E298;
    }
    else
    {
      v8 = (const char *)&unk_73E2A4;
      if ( a4 != 3 )
        v8 = szPassword;
    }
    sprintf(Buffer, "%5s :", v8);
    v7 = v35;
  }
  if ( v6 > 0 )
  {
    if ( a4 >= 2 )
    {
      if ( a4 == 2 )
      {
        v6 *= 2;
      }
      else if ( a4 == 3 )
      {
        v6 *= 4;
      }
    }
    v9 = sub_422E70(908);
    sprintf((char *const)v34, v9, v6);
    v10 = strlen((const char *)v34) + 1;
    v11 = (char *)&v32 + 3;
    do
      v12 = *++v11;
    while ( v12 != 0 );
    qmemcpy(v11, v34, 4 * (v10 >> 2));
    v14 = &v34[v10 >> 2];
    v13 = &v11[4 * (v10 >> 2)];
    v15 = v10;
    v7 = v35;
    qmemcpy(v13, v14, v15 & 3);
    v5 = v31;
  }
  if ( v5 > 0 )
  {
    if ( a4 < 2 )
      goto LABEL_23;
    if ( a4 == 2 )
    {
      v16 = 2 * v5;
      goto LABEL_24;
    }
    v16 = 4 * v5;
    if ( a4 != 3 )
LABEL_23:
      v16 = v5;
LABEL_24:
    v29 = v16;
    v17 = sub_422E70(909);
    sprintf((char *const)v34, v17, v29);
    v18 = strlen((const char *)v34) + 1;
    v19 = (char *)&v32 + 3;
    do
      v20 = *++v19;
    while ( v20 != 0 );
    qmemcpy(v19, v34, 4 * (v18 >> 2));
    v22 = &v34[v18 >> 2];
    v21 = &v19[4 * (v18 >> 2)];
    v23 = v18;
    v7 = v35;
    qmemcpy(v21, v22, v23 & 3);
  }
  if ( v7 > 0 )
  {
    if ( a4 >= 2 )
    {
      if ( a4 == 2 )
      {
        v7 *= 2;
      }
      else if ( a4 == 3 )
      {
        v7 *= 4;
      }
    }
    v30 = v7;
    v24 = sub_422E70(910);
    sprintf((char *const)v34, v24, v30);
    v25 = strlen((const char *)v34) + 1;
    v26 = (char *)&v32 + 3;
    do
      v27 = *++v26;
    while ( v27 != 0 );
    qmemcpy(v26, v34, v25);
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)v32 + 132);
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    a2 + 4,
    a3 + 3,
    -15920331,
    Buffer);
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
}


// ------------------------------------------------------------
// 0x646240 sub_646240 —— 商城条目刷新 2（55ECC0 + 6453D0/6453A0 + 422E70，115 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_646240(void *this, int a2, int a3, int a4, uint32_t *a5, char a6, int a7)
{
  int v8; // edi
  int v9; // ecx
  int v10; // esi
  const char *v11; // eax
  char *v12; // eax
  unsigned int v13; // eax
  char *v14; // edi
  char v15; // cl
  char *v16; // eax
  unsigned int v17; // eax
  char *v18; // edi
  char v19; // cl
  char *v20; // eax
  unsigned int v21; // eax
  char *v22; // edi
  char v23; // cl
  char *v24; // eax
  char *v25; // eax
  int v27; // [esp-4h] [ebp-21Ch]
  int v28; // [esp-4h] [ebp-21Ch]
  int v29; // [esp-4h] [ebp-21Ch]
  const CHAR *v30; // [esp-4h] [ebp-21Ch]
  int v31; // [esp+Ch] [ebp-20Ch]
  char v33[255]; // [esp+14h] [ebp-204h] BYREF
  char v34; // [esp+113h] [ebp-105h] BYREF
  char Buffer[256]; // [esp+114h] [ebp-104h] BYREF
  int v36; // [esp+214h] [ebp-4h]
  int v37; // [esp+22Ch] [ebp+14h]

  v36 = dword_796E50;
  memset(Buffer, 0, sizeof(Buffer));
  memset(v33, 0, sizeof(v33));
  v34 = 0;
  v8 = a5[9];
  v9 = a5[10];
  v10 = a5[8];
  v37 = v8;
  v31 = v9;
  if ( a4 != 0 )
  {
    if ( a4 > 0 && a4 <= 3 )
    {
      if ( sub_55ECC0(a5[3], 1, a4) != 0 )
      {
        v11 = sub_6453D0(a4);
        sprintf(Buffer, "%5s : ", v11);
        if ( v10 > 0 )
        {
          v27 = sub_6453A0(v10, a4);
          v12 = sub_422E70(912);
          sprintf(v33, v12, v27);
          v13 = strlen(v33) + 1;
          v14 = &v34;
          do
            v15 = *++v14;
          while ( v15 != 0 );
          qmemcpy(v14, v33, v13);
          v8 = v37;
        }
        if ( v8 > 0 )
        {
          v28 = sub_6453A0(v8, a4);
          v16 = sub_422E70(913);
          sprintf(v33, v16, v28);
          v17 = strlen(v33) + 1;
          v18 = &v34;
          do
            v19 = *++v18;
          while ( v19 != 0 );
          qmemcpy(v18, v33, v17);
        }
        if ( v31 > 0 )
        {
          v29 = sub_6453A0(v31, a4);
          v20 = sub_422E70(914);
          sprintf(v33, v20, v29);
          v21 = strlen(v33) + 1;
          v22 = &v34;
          do
            v23 = *++v22;
          while ( v23 != 0 );
          qmemcpy(v22, v33, v21);
        }
      }
      else
      {
        v30 = sub_6453D0(a4);
        v24 = sub_422E70(915);
        sprintf(Buffer, v24, v30);
        a7 = -16776961;
      }
    }
  }
  else if ( a6 == 0 )
  {
    v25 = sub_422E70(911);
    sprintf(Buffer, v25);
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)this + 132);
  (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    a2 + 4,
    a3 + 3,
    a7,
    Buffer);
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
}



// ------------------------------------------------------------
// 0x6464C0 sub_6464C0 —— 商城条目刷新 3（55CCB0 + 422E70/4EB900）
// ------------------------------------------------------------
int /*thiscall*/ sub_6464C0(void *this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax
  int v8; // esi
  char *v9; // eax
  int v10; // edi

  result = sub_55CCB0(a5);
  if ( result != 0 )
  {
    if ( a4 == -1 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)this + 132);
      v8 = *(uint32_t *)dword_79C0B0;
      v9 = sub_422E70(916);
      (*(void (/*cdecl*/ **)(int, int, int, int, char *))(v8 + 80))(dword_79C0B0, a2 + 4, a3 + 3, -1, v9);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    }
    else
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)result + 176))(result);
      result = sub_4EB900(a4);
      v10 = result;
      if ( result != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, (int)this + 132);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          a2 + 4,
          a3 + 3,
          -1,
          v10);
        return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x646590 sub_646590 —— 商城条目刷新 4（55CCB0）
// ------------------------------------------------------------
bool /*thiscall*/ sub_646590(char *this)
{
  char *v1; // esi
  int i; // ebx
  int v3; // ecx
  int v4; // esi
  int v5; // eax
  int v7; // [esp+Ch] [ebp-4h]

  v7 = 0;
  v1 = this + 364;
  for ( i = 20; i != 0; --i )
  {
    if ( sub_55CCB0(*((uint32_t *)v1 + 13)) != 0 && *v1 == 22 )
      ++v7;
    v1 += 84;
  }
  if ( v7 != 8 )
    return true;
  v3 = *((uint32_t *)dword_8F8534 + 2);
  v4 = 0;
  v5 = 0;
  if ( v3 <= 0 )
    return false;
  do
  {
    if ( *(uint32_t *)(*((uint32_t *)dword_8F8534 + 3) + 4 * v5) == 0 )
      ++v4;
    ++v5;
  }
  while ( v5 < v3 );
  return v4 >= 16;
}



// ------------------------------------------------------------
// 0x646610 sub_646610 —— 商城条目刷新 5（55CCB0 + 422E70/44E8D0）
// ------------------------------------------------------------
char /*thiscall*/ sub_646610(char **this, uint8_t a2)
{
  char **v3; // esi
  int i; // ebx
  char *v5; // eax
  int v7; // [esp+Ch] [ebp-8h]
  int v8; // [esp+10h] [ebp-4h]

  v8 = 0;
  v7 = 0;
  v3 = this + 91;
  for ( i = 20; i != 0; --i )
  {
    if ( sub_55CCB0(v3[13]) != 0 )
    {
      if ( *(uint8_t *)v3 == 22 )
        ++v8;
      else
        ++v7;
    }
    v3 += 21;
  }
  if ( v8 == 8 )
  {
    if ( a2 == 1 )
    {
      v5 = sub_422E70(3012);
      sub_44E8D0(*(this + 1), (void *)0x1B, (int)v5, 0);
    }
    return 1;
  }
  if ( v8 <= 0 || v7 < 0 )
    return 1;
  sub_44E8D0(*(this + 1), (void *)0x45, (int)this, a2);
  return 0;
}



// ------------------------------------------------------------
// 0x6466D0 sub_6466D0 —— 双倍活动面板 A：加载 interface/cashshop/cashshopdoubleevent.img（667620/4F33A0/4F2C10 + 418DD0/69A110 + 55CCB0 系，252 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6466D0(int this)
{
  int v2; // ecx
  int v3; // edx
  int v4; // ebx
  unsigned int v5; // eax
  int v6; // edx
  int v7; // edx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // edi
  int v12; // ecx
  const CHAR *v13; // eax
  const char *v14; // eax
  int v15; // eax
  int v16; // eax
  const char *v17; // eax
  const char *v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // esi
  int v24; // eax
  int result; // eax
  int v26; // [esp-4h] [ebp-130h]
  const CHAR *v27; // [esp-4h] [ebp-130h]
  int v28; // [esp+Ch] [ebp-120h]
  int v29; // [esp+10h] [ebp-11Ch]
  unsigned int v30; // [esp+14h] [ebp-118h]
  int v31; // [esp+18h] [ebp-114h]
  int v32; // [esp+1Ch] [ebp-110h]
  int Value; // [esp+20h] [ebp-10Ch]
  int v34; // [esp+24h] [ebp-108h]
  char Buffer[256]; // [esp+28h] [ebp-104h] BYREF
  int v36; // [esp+128h] [ebp-4h]

  v2 = *(uint32_t *)(this + 416);
  v3 = *(uint32_t *)(this + 372);
  v4 = this + 340;
  v36 = dword_796E50;
  v5 = *(int16_t *)(this + 366);
  v31 = v2;
  v30 = v5;
  if ( *(uint16_t *)(this + 366) != 0 && v5 != 1 )
  {
    if ( v5 == 2 )
    {
      v3 *= 2;
    }
    else if ( v5 == 3 )
    {
      v3 *= 4;
    }
  }
  v34 = v3;
  v6 = *(uint32_t *)(this + 376);
  if ( v5 >= 2 )
  {
    if ( v5 == 2 )
    {
      v6 *= 2;
    }
    else if ( v5 == 3 )
    {
      v6 *= 4;
    }
  }
  v32 = v6;
  v7 = *(uint32_t *)(this + 380);
  if ( v5 >= 2 )
  {
    if ( v5 == 2 )
    {
      Value = 2 * v7;
      goto LABEL_18;
    }
    if ( v5 == 3 )
      v7 *= 4;
  }
  Value = v7;
LABEL_18:
  v8 = sub_667620(v2);
  v26 = *(uint32_t *)(this + 360);
  v28 = v26;
  v29 = *(char *)(this + 356);
  v9 = sub_4F33A0(*(uint32_t *)(this + 352));
  sub_4F2C10(192, 118, v9, v26);
  if ( v8 > 1 )
  {
    v10 = sub_418DD0(10);
    if ( v10 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v10 + 128))(
        v10,
        190,
        155,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_69A110(207, 157, v8, -1);
  }
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v31 + 108))(v31);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 236);
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 231, 119, -15920333, v11);
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(dword_79C0B0, 230, 119, -15920333, v11);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 132);
  if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 1 )
  {
    if ( v28 <= 1 )
      v13 = szPassword;
    else
      v13 = (const CHAR *)sub_422E70(885);
    v27 = v13;
    v14 = (const char *)sub_422E70(884);
    sprintf(Buffer, v14, v28, v27);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      230,
      136,
      -15920333,
      Buffer);
  }
  else if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 2 )
  {
    if ( *(uint32_t *)(this + 412) < 0x10u )
      v12 = this + 392;
    else
      v12 = *(uint32_t *)(this + 392);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      230,
      136,
      -15920333,
      v12);
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  if ( sub_55CCB0(v31) != 0 )
  {
    v15 = sub_418DD0(34);
    if ( v15 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v15 + 128))(
        v15,
        226,
        133,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_6464C0(226, 133, v29, v31, 0);
    v16 = sub_418DD0(34);
    if ( v16 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v16 + 128))(
        v16,
        226,
        153,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_646240(226, 153, v30, this + 340, 0, -1);
  }
  else
  {
    sub_645FD0(226, 153, v30, this + 340);
  }
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 184);
  if ( v32 > 0 )
  {
    v17 = (const char *)sub_422E70(886);
    sprintf(Buffer, v17, v32);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      309 - *(uint32_t *)(this + 212),
      181,
      -15920333,
      Buffer);
  }
  if ( v34 > 0 )
  {
    v18 = (const char *)sub_422E70(887);
    sprintf(Buffer, v18, v34);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      448 - *(uint32_t *)(this + 212),
      181,
      -15920333,
      Buffer);
  }
  if ( Value > 0 )
  {
    sub_69A110(416, 207, Value, -1);
    v19 = *(uint32_t *)dword_79C0B0;
    v20 = sub_422E70(888);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v19 + 80))(
      dword_79C0B0,
      440 - *(uint32_t *)(this + 212),
      210,
      -15920333,
      v20);
    v21 = *(uint32_t *)dword_79C0B0;
    v22 = sub_422E70(889);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v21 + 80))(
      dword_79C0B0,
      439 - *(uint32_t *)(this + 212),
      210,
      -15920333,
      v22);
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 288);
  v23 = *(uint32_t *)dword_79C0B0;
  v24 = sub_422E70(890);
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(v23 + 80))(dword_79C0B0, 250, 319, -1, v24);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  if ( *(uint8_t *)(v4 + 24) == 22 )
  {
    (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
      dword_8F84B8,
      "interface/cashshop/cashshopdoubleevent.img");
    result = sub_418DD0(3);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
               result,
               200,
               131,
               dword_79C0B0,
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
int /*thiscall*/ sub_646C10(int *this, int a2)
{
  int v3; // esi
  int *v4; // ebx
  int result; // eax
  uint32_t *v6; // ecx

  v3 = 1;
  v4 = this + 519;
  do
  {
    result = *v4;
    if ( *v4 == a2 && *(uint8_t *)(result + 16) != 0 )
    {
      v6 = (uint32_t *)*(this + 517);
      if ( v6 != nullptr )
        result = sub_646240(this, *(uint32_t *)(result + 20) + 2, *(uint32_t *)(result + 24) + 1, v3, v6, 1, -1);
    }
    ++v3;
    ++v4;
  }
  while ( v3 < 4 );
  return result;
}



// ------------------------------------------------------------
// 0x646C70 sub_646C70 —— 双倍活动面板 B：同 6466D0 结构（cashshopdoubleevent.img，186 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_646C70(int this, int Value)
{
  int result; // eax
  uint32_t *v4; // ecx
  uint32_t *i; // edx
  int v6; // ebx
  int v7; // esi
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  const CHAR *v11; // eax
  const char *v12; // eax
  int v13; // eax
  int v14; // eax
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
  int v30; // [esp+12Ch] [ebp-4h]
  int Valuea; // [esp+138h] [ebp+8h]
  int Valueb; // [esp+138h] [ebp+8h]
  int Valuec; // [esp+138h] [ebp+8h]

  v30 = dword_796E50;
  result = 0;
  v4 = (uint32_t *)(this + 2020);
  for ( i = (uint32_t *)(this + 52); *i != Value || *v4 == 0; i += 4 )
  {
    ++result;
    ++v4;
    if ( result >= 4 )
      return result;
  }
  v6 = *(uint32_t *)(this + 4 * result + 2020);
  v7 = *(uint32_t *)(16 * result + this + 52);
  v26 = *(uint32_t **)(v6 + 76);
  v19 = *(int16_t *)(v6 + 26);
  Valuea = sub_667620(v26);
  v22 = *(char *)(v6 + 16);
  v18 = *(uint32_t *)(v7 + 20) + 11;
  v16 = *(uint32_t *)(v6 + 20);
  v20 = v16;
  v21 = *(uint32_t *)(v7 + 24) + 14;
  v8 = sub_4F33A0(*(uint32_t *)(v6 + 12));
  sub_4F2C10(v18, v21, v8, v16);
  if ( Valuea > 1 )
  {
    v27 = *(uint32_t *)(v7 + 24);
    v24 = *(uint32_t *)(v7 + 20);
    v9 = sub_418DD0(*(uint32_t **)(this + 24), 0xAu);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
        v9,
        v24 + 9,
        v27 + 48,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_69A110(*(uint32_t *)(v7 + 20) + 26, *(uint32_t *)(v7 + 24) + 50, Valuea, -1);
  }
  v28 = (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 108))(v26);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 236);
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    *(uint32_t *)(v7 + 20) + 49,
    *(uint32_t *)(v7 + 24) + 14,
    -15920333,
    v28);
  (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    *(uint32_t *)(v7 + 20) + 48,
    *(uint32_t *)(v7 + 24) + 14,
    -15920333,
    v28);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, this + 132);
  if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 1 )
  {
    if ( v20 <= 1 )
      v11 = szPassword;
    else
      v11 = (const CHAR *)sub_422E70(898);
    v17 = v11;
    v12 = (const char *)sub_422E70(897);
    sprintf(Buffer, v12, v20, v17);
    (*(void (/*cdecl*/ **)(int, int, int, int, char *))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      *(uint32_t *)(v7 + 20) + 48,
      *(uint32_t *)(v7 + 24) + 31,
      -16051403,
      Buffer);
  }
  else if ( *(uint32_t *)(*(uint32_t *)(this + 8) + 44) == 2 )
  {
    if ( *(uint32_t *)(v6 + 72) < 0x10u )
      v10 = v6 + 52;
    else
      v10 = *(uint32_t *)(v6 + 52);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      *(uint32_t *)(v7 + 20) + 48,
      *(uint32_t *)(v7 + 24) + 31,
      -16051403,
      v10);
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  if ( sub_55CCB0(v26) != 0 )
  {
    Valueb = *(uint32_t *)(v7 + 24);
    v25 = *(uint32_t *)(v7 + 20);
    v13 = sub_418DD0(*(uint32_t **)(this + 20), 0x22u);
    if ( v13 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
        v13,
        v25 + 46,
        Valueb + 28,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    sub_6464C0(*(uint32_t *)(v7 + 20) + 46, *(uint32_t *)(v7 + 24) + 28, v22, v26, 0);
    v23 = *(uint32_t *)(v7 + 20);
    Valuec = *(uint32_t *)(v7 + 24);
    v14 = sub_418DD0(*(uint32_t **)(this + 20), 0x22u);
    if ( v14 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v14 + 128))(
        v14,
        v23 + 46,
        Valuec + 48,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        -1,
        1333788672,
        1333788672);
    result = sub_646240(*(uint32_t *)(v7 + 20) + 46, *(uint32_t *)(v7 + 24) + 48, v19, v6, 0, -1);
  }
  else
  {
    result = sub_645FD0(*(uint32_t *)(v7 + 20) + 46, *(uint32_t *)(v7 + 24) + 48, v19, v6);
  }
  if ( *(uint8_t *)(v6 + 24) == 22 )
  {
    v15 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                      dword_8F84B8,
                      "interface/cashshop/cashshopdoubleevent.img");
    result = sub_418DD0(v15, 3u);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
               result,
               v18 + 8,
               v21 + 13,
               dword_79C0B0,
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
int /*thiscall*/ sub_6470A0(int this)
{
  int v1; // eax
  char *v3; // eax
  int result; // eax
  int v5; // eax
  char *v6; // eax
  int v7; // eax
  char *v8; // eax
  int v9; // eax
  char *v10; // eax
  int v11; // ebx
  int v12; // edi
  int v13; // ebx
  int v14; // edi
  char *v15; // [esp-10h] [ebp-218h]
  char *v16; // [esp-10h] [ebp-218h]
  char *v17; // [esp-10h] [ebp-218h]
  int v18; // [esp-4h] [ebp-20Ch]
  int v19; // [esp-4h] [ebp-20Ch]
  int v20; // [esp-4h] [ebp-20Ch]
  char Buffer[512]; // [esp+4h] [ebp-204h] BYREF
  int v22; // [esp+204h] [ebp-4h]

  v22 = dword_796E50;
  v1 = *(uint32_t *)(dword_8F7C08 + 648);
  if ( v1 != 0 && *(uint8_t *)(v1 + 284) != 0 )
  {
    v3 = sub_422E70(1340);
    return sub_44E8D0((char *)dword_8F8528, (void *)0x1B, (int)v3, 0);
  }
  else
  {
    v5 = *(uint32_t *)(this + 2056);
    if ( v5 >= 0 )
    {
      v7 = *(uint32_t *)(this + 2060);
      if ( v7 >= 0 )
      {
        v9 = *(uint32_t *)(this + 2064);
        if ( v9 >= 0 )
        {
          v11 = 0;
          v12 = this + 356;
          do
          {
            if ( sub_55CCB0(*(uint32_t *)(v12 + 60)) != 0 && *(uint8_t *)v12 == 0xFF )
            {
              v16 = sub_422E70(906);
              return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v16, 0);
            }
            ++v11;
            v12 += 84;
          }
          while ( v11 < 20 );
          v13 = 0;
          v14 = this + 366;
          do
          {
            if ( sub_55CCB0(*(uint32_t *)(v14 + 50)) != 0 && *(uint16_t *)v14 == 0 )
            {
              v17 = sub_422E70(907);
              return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v17, 0);
            }
            ++v13;
            v14 += 84;
          }
          while ( v13 < 20 );
          if ( *(uint8_t *)(*(uint32_t *)(this + 8) + 10128) == 0 )
            goto LABEL_24;
          if ( (uint8_t)sub_646590(this) == 0 )
          {
            v15 = sub_422E70(3010);
            return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v15, 0);
          }
          result = sub_646610(0);
          if ( (uint8_t)result == 1 )
          {
LABEL_24:
            result = *(uint32_t *)(this + 2056);
            if ( result >= 0 )
            {
              result = *(uint32_t *)(this + 2060);
              if ( result >= 0 )
              {
                result = *(uint32_t *)(this + 2064);
                if ( result >= 0 )
                  return sub_44E8D0(*(char **)(this + 4), (void *)0x2F, this, 0);
              }
            }
          }
        }
        else
        {
          v20 = -v9;
          v10 = sub_422E70(905);
          sprintf(Buffer, v10, v20);
          return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)Buffer, 0);
        }
      }
      else
      {
        v19 = -v7;
        v8 = sub_422E70(904);
        sprintf(Buffer, v8, v19);
        return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)Buffer, 0);
      }
    }
    else
    {
      v18 = -v5;
      v6 = sub_422E70(903);
      sprintf(Buffer, v6, v18);
      return sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)Buffer, 0);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6472C0 sub_6472C0 —— 商城点击音（CLICK_BUTTON1 事件 432EA0，137 行判定）
// ------------------------------------------------------------
void */*thiscall*/ sub_6472C0(int *this, int a2)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int *v14; // eax
  int i; // ecx
  int v16; // esi

  if ( a2 == -1 )
  {
    v2 = *(this + 511);
    if ( v2 <= 0 )
      return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
    v3 = v2 - 1;
  }
  else
  {
    if ( a2 != 1 )
      goto LABEL_8;
    v4 = *(this + 511);
    if ( v4 >= *(this + 512) )
      return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
    v3 = v4 + 1;
  }
  *(this + 511) = v3;
LABEL_8:
  v5 = 4 * *(this + 511);
  if ( v5 >= *(this + 509) )
  {
    v7 = *(this + 13);
    *(this + 505) = 0;
  }
  else
  {
    *(this + 505) = (int)(this + 84 * *(this + 511) + 85);
    *(uint8_t *)(*(this + 13) + 16) = 1;
    v6 = *(this + 15);
    if ( *(uint32_t *)(*(this + 505) + 4) == 0 )
    {
      *(uint8_t *)(v6 + 16) = 1;
      *(uint8_t *)(*(this + 16) + 16) = 1;
      goto LABEL_14;
    }
    *(uint8_t *)(v6 + 16) = 0;
    v7 = *(this + 16);
  }
  *(uint8_t *)(v7 + 16) = 0;
LABEL_14:
  if ( v5 + 1 >= *(this + 509) )
  {
    v9 = *(this + 17);
    *(this + 506) = 0;
  }
  else
  {
    *(this + 506) = (int)(this + 21 * v5 + 106);
    *(uint8_t *)(*(this + 17) + 16) = 1;
    v8 = *(this + 19);
    if ( *(uint32_t *)(*(this + 506) + 4) == 0 )
    {
      *(uint8_t *)(v8 + 16) = 1;
      *(uint8_t *)(*(this + 20) + 16) = 1;
      goto LABEL_20;
    }
    *(uint8_t *)(v8 + 16) = 0;
    v9 = *(this + 20);
  }
  *(uint8_t *)(v9 + 16) = 0;
LABEL_20:
  if ( v5 + 2 >= *(this + 509) )
  {
    v11 = *(this + 21);
    *(this + 507) = 0;
  }
  else
  {
    *(this + 507) = (int)(this + 21 * v5 + 127);
    *(uint8_t *)(*(this + 21) + 16) = 1;
    v10 = *(this + 23);
    if ( *(uint32_t *)(*(this + 507) + 4) == 0 )
    {
      *(uint8_t *)(v10 + 16) = 1;
      *(uint8_t *)(*(this + 24) + 16) = 1;
      goto LABEL_26;
    }
    *(uint8_t *)(v10 + 16) = 0;
    v11 = *(this + 24);
  }
  *(uint8_t *)(v11 + 16) = 0;
LABEL_26:
  if ( v5 + 3 >= *(this + 509) )
  {
    v13 = *(this + 25);
    *(this + 508) = 0;
  }
  else
  {
    *(this + 508) = (int)(this + 21 * v5 + 148);
    *(uint8_t *)(*(this + 25) + 16) = 1;
    v12 = *(this + 27);
    if ( *(uint32_t *)(*(this + 508) + 4) == 0 )
    {
      *(uint8_t *)(v12 + 16) = 1;
      *(uint8_t *)(*(this + 28) + 16) = 1;
      goto LABEL_32;
    }
    *(uint8_t *)(v12 + 16) = 0;
    v13 = *(this + 28);
  }
  *(uint8_t *)(v13 + 16) = 0;
LABEL_32:
  *(uint8_t *)(*(this + 519) + 16) = 0;
  *(uint8_t *)(*(this + 520) + 16) = 0;
  *(uint8_t *)(*(this + 521) + 16) = 0;
  v14 = this + 522;
  for ( i = 60; i != 0; --i )
  {
    v16 = *v14++;
    *(uint8_t *)(v16 + 16) = 0;
  }
  return sub_432EA0("CLICK_BUTTON1", -1, 0, 0);
}


// ------------------------------------------------------------
// 0x6474A0 sub_6474A0 —— 商城页部件（645EE0 + 69A5F0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6474A0(int *this, int a2, int a3)
{
  BOOL v3; // esi
  int v5; // eax
  int v6; // edi
  uint32_t **v7; // esi
  uint32_t *result; // eax
  bool v9; // [esp+1Bh] [ebp+Fh]

  v3 = a3;
  if ( a3 == -1 )
    v3 = *(uint8_t *)(*(this + 519) + 16) == 0;
  if ( v3 )
  {
    sub_645EE0(this);
    v5 = a2;
    *(this + 517) = *(this + a2 + 505);
  }
  else
  {
    v5 = a2;
    *(this + 517) = 0;
  }
  v9 = v3;
  v6 = 18;
  v7 = (uint32_t **)(this + 519);
  while ( 1 )
  {
    *((uint8_t *)*v7 + 16) = v9;
    result = *(this + 510) != 0
           ? sub_69A5F0(*v7, 226, v6 + 153)
           : sub_69A5F0(*v7, dword_73E228[2 * v5], v6 + dword_73E22C[2 * v5]);
    v6 += 18;
    ++v7;
    if ( v6 >= 72 )
      break;
    v5 = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x647550 sub_647550 —— 商城页部件 2（55CCB0/645EE0 + 69A5F0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_647550(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // esi
  int v8; // ecx
  unsigned int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  uint32_t **v14; // ebx
  int v15; // esi
  int v16; // eax
  uint32_t *result; // eax
  uint32_t **v18; // esi
  unsigned int v19; // edi
  int v20; // ebx
  int v21; // eax
  bool v22; // zf
  int v23; // [esp+Ch] [ebp-1Ch]
  int v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+14h] [ebp-14h]
  int v26; // [esp+18h] [ebp-10h]
  uint32_t *v27; // [esp+18h] [ebp-10h]
  uint32_t *v29; // [esp+1Ch] [ebp-Ch]
  int i; // [esp+20h] [ebp-8h]
  int v31; // [esp+24h] [ebp-4h]
  int v32; // [esp+24h] [ebp-4h]
  int v33; // [esp+30h] [ebp+8h]

  v4 = sub_55CCB0(*(uint32_t *)(*(this + a2 + 505) + 76));
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 176))(v4) + 916;
  v25 = v5;
  if ( a3 == -1 )
    a3 = *(uint8_t *)(*(this + 522) + 16) == 0;
  if ( a3 != 0 )
  {
    sub_645EE0(this);
    *(this + 517) = *(this + a2 + 505);
  }
  else
  {
    *(this + 517) = 0;
  }
  v6 = *(this + 522);
  v23 = *(uint32_t *)(v6 + 28);
  v7 = *(uint32_t *)(v5 + 4);
  v26 = *(uint32_t *)(v6 + 32);
  v8 = 480 / v26 - 1;
  v24 = v8;
  if ( v7 != 0 )
    v9 = (*(uint32_t *)(v5 + 8) - v7) / 80;
  else
    v9 = 0;
  v10 = v9 / v8;
  if ( v10 != 0 )
  {
    result = (uint32_t *)(v10 + 1);
    v33 = 100;
    if ( (int)result > 0 )
    {
      v18 = (uint32_t **)(this + 522);
      v19 = 0;
      v32 = 0;
      v29 = this + 522;
      v27 = result;
      do
      {
        if ( v8 > 0 )
        {
          v20 = 24;
          for ( i = v8; i != 0; --i )
          {
            *((uint8_t *)*v18 + 16) = a3 != 0
                                 && (v21 = *(uint32_t *)(v25 + 4)) != 0
                                 && v19 < (*(uint32_t *)(v25 + 8) - v21) / 80;
            sub_69A5F0(*v18++, v33, v20);
            ++v19;
            v20 += 18;
          }
          v8 = v24;
        }
        v33 += v23;
        v18 = (uint32_t **)&v29[v8];
        v19 = v8 + v32;
        result = (uint32_t *)((char *)v27 - 1);
        v22 = v27 == (uint32_t *)1;
        v32 += v8;
        v29 = v18;
        v27 = (uint32_t *)((char *)v27 - 1);
      }
      while ( !v22 );
    }
  }
  else
  {
    if ( v7 != 0 )
      v10 = (*(uint32_t *)(v5 + 8) - v7) / 80;
    v11 = v26 * v10;
    if ( *(this + 510) != 0 )
      v12 = 151;
    else
      v12 = dword_73E22C[2 * a2];
    v13 = v12 + v11;
    if ( 480 - v13 < 0 )
      v12 += 470 - v13;
    v14 = (uint32_t **)(this + 522);
    v15 = 0;
    v31 = v12;
    do
    {
      *((uint8_t *)*v14 + 16) = a3 != 0
                           && (v16 = *(uint32_t *)(v5 + 4)) != 0
                           && v15 < (unsigned int)((*(uint32_t *)(v5 + 8) - v16) / 80);
      if ( *(this + 510) != 0 )
        result = sub_69A5F0(*v14, 226, v31);
      else
        result = sub_69A5F0(*v14, dword_73E228[2 * a2], v31);
      ++v15;
      ++v14;
      v31 += 18;
    }
    while ( v15 < 60 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x6477B0 sub_6477B0 —— 商城页部件 3（69A5F0 + 6472C0/646610/646590 + 422E70/44E8D0，172 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_6477B0(int this, uint32_t *a2, char a3)
{
  uint32_t *v4; // eax
  uint8_t *v5; // edx
  int v6; // ecx
  uint8_t *v7; // edx
  int v8; // ecx
  uint8_t *v9; // edx
  int v10; // ecx
  uint8_t *v11; // edx
  int v12; // ecx
  uint8_t *v13; // edx
  int v14; // ecx
  int v15; // esi
  uint32_t **v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  int *v22; // eax
  int j; // ecx
  int v24; // edx
  int result; // eax
  char *v26; // eax
  int i; // [esp+18h] [ebp+Ch]

  *(uint8_t *)(this + 2052) = 0;
  *(uint32_t *)(this + 2036) = 0;
  if ( a3 != 0 )
  {
    v4 = a2 + 40;
    for ( i = 4; i != 0; --i )
    {
      if ( *(v4 - 21) != 0 )
      {
        v5 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);
        qmemcpy(v5, v4 - 40, 0x54u);
        v5[80] = 0;
        v6 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(v6 + 344) == 0 )
          *(uint16_t *)(v6 + 366) = 0;
        ++*(uint32_t *)(this + 2036);
      }
      if ( *v4 != 0 )
      {
        v7 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);
        qmemcpy(v7, v4 - 19, 0x54u);
        v7[80] = 0;
        v8 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(v8 + 344) == 0 )
          *(uint16_t *)(v8 + 366) = 0;
        ++*(uint32_t *)(this + 2036);
      }
      if ( v4[21] != 0 )
      {
        v9 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);
        qmemcpy(v9, v4 + 2, 0x54u);
        v9[80] = 0;
        v10 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(v10 + 344) == 0 )
          *(uint16_t *)(v10 + 366) = 0;
        ++*(uint32_t *)(this + 2036);
      }
      if ( v4[42] != 0 )
      {
        v11 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);
        qmemcpy(v11, v4 + 23, 0x54u);
        v11[80] = 0;
        v12 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(v12 + 344) == 0 )
          *(uint16_t *)(v12 + 366) = 0;
        ++*(uint32_t *)(this + 2036);
      }
      if ( v4[63] != 0 )
      {
        v13 = (uint8_t *)(84 * *(uint32_t *)(this + 2036) + this + 340);
        qmemcpy(v13, v4 + 44, 0x54u);
        v13[80] = 0;
        v14 = 84 * *(uint32_t *)(this + 2036) + this;
        if ( *(uint32_t *)(v14 + 344) == 0 )
          *(uint16_t *)(v14 + 366) = 0;
        ++*(uint32_t *)(this + 2036);
      }
      v4 += 105;
    }
    *(uint32_t *)(this + 2040) = 0;
  }
  else
  {
    qmemcpy((void *)(this + 340), a2, 0x54u);
    *(uint8_t *)(this + 420) = 0;
    *(uint32_t *)(this + 2020) = this + 340;
    v19 = 84 * *(uint32_t *)(this + 2036);
    v20 = *(uint32_t *)(v19 + this + 344);
    v21 = this + v19;
    if ( v20 == 0 )
      *(uint16_t *)(v21 + 366) = 0;
    ++*(uint32_t *)(this + 2036);
    *(uint32_t *)(this + 2040) = 1;
  }
  v15 = 0;
  v16 = (uint32_t **)(this + 32);
  do
  {
    v17 = 2 * (*(uint32_t *)(this + 2040) + v15 + 2 * *(uint32_t *)(this + 2040));
    sub_69A5F0(*v16, dword_73E248[v17], dword_73E24C[v17]);
    ++v15;
    ++v16;
  }
  while ( v15 < 3 );
  *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 1;
  *(uint32_t *)(this + 2048) = (*(uint32_t *)(this + 2036) - 1) / 4;
  v18 = *(uint32_t *)(this + 2040);
  *(uint32_t *)(this + 2044) = 0;
  if ( v18 != 0 )
  {
    *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 52) + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 68) + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 84) + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 100) + 16) = 0;
    if ( *(uint32_t *)(*(uint32_t *)(this + 2020) + 4) != 0 )
    {
      *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 0;
      *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;
    }
    else
    {
      *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 1;
      *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 1;
    }
  }
  else
  {
    *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 1;
    *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 0;
    *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 0;
    sub_6472C0(0);
  }
  *(uint8_t *)(*(uint32_t *)(this + 2076) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 2080) + 16) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 2084) + 16) = 0;
  v22 = (int *)(this + 2088);
  for ( j = 60; j != 0; --j )
  {
    v24 = *v22++;
    *(uint8_t *)(v24 + 16) = 0;
  }
  result = *(uint32_t *)(this + 8);
  if ( *(uint8_t *)(result + 10128) != 0 )
  {
    sub_646610(1);
    result = sub_646590(this);
    if ( (uint8_t)result == 0 )
    {
      v26 = sub_422E70(3010);
      sub_44E8D0(*(char **)(this + 4), (void *)0x1B, (int)v26, 0);
      *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 0;
      memset((void *)(this + 340), 0, 0x690u);
      return 0;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x647B60 sub_647B60 —— 商城页部件 4（55CCB0 + 41A5E0）
// ------------------------------------------------------------
int /*thiscall*/ sub_647B60(uint32_t *this, int a2, int a3)
{
  int v3; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax

  v3 = sub_55CCB0(a2);
  v4 = v3;
  if ( v3 != 0
    && (v5 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 176))(v3) + 920) + 80 * a3),
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 176))(v4),
        v7 = sub_41A5E0(80 * a3 + *(uint32_t *)(v6 + 920) + 24),
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
char /*thiscall*/ sub_647BF0(int this)
{
  uint8_t *v2; // eax
  uint8_t *v3; // eax
  int v4; // eax
  int *v5; // edi
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  int v10; // ecx
  bool v11; // zf
  uint32_t *v12; // edi
  uint32_t *v13; // eax
  uint32_t *v14; // edi
  uint32_t **v15; // edi
  uint8_t *v16; // eax
  void *v17; // ecx
  uint32_t *v18; // eax
  uint8_t *v19; // eax
  void *v20; // ecx
  uint32_t *v21; // eax
  uint8_t *v22; // eax
  void *v23; // ecx
  uint32_t *v24; // eax
  uint8_t *v25; // eax
  void *v26; // ecx
  uint32_t *v27; // eax
  uint32_t *v28; // edi
  uint32_t *v29; // eax
  uint32_t *v30; // edi
  uint32_t *v31; // eax
  uint32_t *v32; // edi
  uint32_t *v33; // eax
  char *v34; // edi
  uint32_t *v35; // eax
  uint32_t *v36; // edi
  uint32_t *v37; // eax
  char *v38; // edi
  uint32_t *v39; // edi
  int v40; // ecx
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
  int v53; // [esp+5Ch] [ebp-18h]
  void *v54; // [esp+60h] [ebp-14h]
  int v55; // [esp+64h] [ebp-10h]
  int v56; // [esp+70h] [ebp-4h]

  v2 = operator new(0x68u);
  Block = v2;
  v56 = 0;
  if ( v2 != nullptr )
    v3 = sub_426BD0(v2);
  else
    v3 = nullptr;
  *(uint32_t *)(this + 12) = v3;
  *((uint32_t *)v3 + 7) = 640;
  *((uint32_t *)v3 + 8) = 480;
  *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 0;
  *(uint32_t *)(*(uint32_t *)(this + 12) + 68) = this;
  *(uint32_t *)(this + 20) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 164);
  *(uint32_t *)(this + 24) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 156);
  *(uint32_t *)(this + 28) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 160);
  Block = operator new(0x2Cu);
  v56 = 1;
  if ( Block != nullptr )
    v4 = sub_423B30(dword_79C0B0, *(uint32_t *)(this + 24), 28, 2);
  else
    v4 = 0;
  *(uint32_t *)(this + 16) = v4;
  *(uint32_t *)(v4 + 36) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 16) + 24) = 0;
  *(uint8_t *)(this + 132) = 0;
  *(uint8_t *)(this + 133) = 0;
  *(uint8_t *)(this + 134) = 0;
  *(uint8_t *)(this + 135) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 160) = 1600;
  *(uint32_t *)(this + 148) = 6;
  *(uint32_t *)(this + 152) = 12;
  v56 = -1;
  *(uint32_t *)(this + 180) = dword_99FCCC;
  *(uint32_t *)(this + 160) = 205;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(this + 184) = 0;
  *(uint8_t *)(this + 185) = 0;
  *(uint8_t *)(this + 186) = 0;
  *(uint8_t *)(this + 187) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 6;
  *(uint32_t *)(this + 204) = 12;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 1600;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  *(uint32_t *)(this + 232) = 0;
  *(uint32_t *)(this + 232) = dword_99FCCC;
  *(uint32_t *)(this + 212) = 165;
  *(uint32_t *)(this + 196) = 2;
  *(uint8_t *)(this + 236) = 0;
  *(uint8_t *)(this + 237) = 0;
  *(uint8_t *)(this + 238) = 0;
  *(uint8_t *)(this + 239) = 0;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 6;
  *(uint32_t *)(this + 256) = 12;
  *(uint32_t *)(this + 260) = 0;
  *(uint32_t *)(this + 264) = 1600;
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint32_t *)(this + 276) = 0;
  *(uint32_t *)(this + 280) = 0;
  *(uint32_t *)(this + 284) = 0;
  *(uint32_t *)(this + 284) = dword_99FCCC;
  *(uint32_t *)(this + 248) = 0;
  *(uint32_t *)(this + 264) = 205;
  *(uint8_t *)(this + 288) = 0;
  *(uint8_t *)(this + 289) = 0;
  *(uint8_t *)(this + 290) = 0;
  *(uint8_t *)(this + 291) = 0;
  *(uint32_t *)(this + 300) = 0;
  *(uint32_t *)(this + 304) = 6;
  *(uint32_t *)(this + 308) = 12;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 1600;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 336) = dword_99FCCC;
  *(uint32_t *)(this + 316) = 205;
  *(uint32_t *)(this + 300) = 0;
  v48[1] = -1;
  v48[4] = 6;
  v48[5] = -1;
  *(uint32_t *)(this + 292) = -16777216;
  *(uint8_t *)(this + 290) = 1;
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
  v55 = this + 32;
  v54 = (void *)3;
  do
  {
    if ( v5[1] == -1 )
    {
      v8 = operator new(0x84u);
      Block = v8;
      v56 = 3;
      if ( v8 != nullptr )
        v9 = sub_43C410(v8, *(uint32_t *)(this + 20), *(v5 - 2), *(v5 - 1), *v5, -1, 0, 0);
      else
        v9 = nullptr;
      *(uint32_t *)v55 = v9;
    }
    else
    {
      v6 = operator new(0x84u);
      Block = v6;
      v56 = 2;
      if ( v6 != nullptr )
      {
        v7 = sub_43C410(v6, *(uint32_t *)(this + 20), *(v5 - 2), *(v5 - 1), *v5, v5[1], 0, 0);
        *(uint32_t *)v55 = v7;
      }
      else
      {
        *(uint32_t *)v55 = 0;
      }
    }
    v45 = *(uint32_t *)v55;
    v56 = -1;
    sub_69A840(v45);
    sub_69A840(*(uint32_t *)v55);
    v10 = v55;
    *(uint32_t *)(*(uint32_t *)v55 + 68) = this;
    v5 += 4;
    v11 = v54 == (void *)1;
    v55 = v10 + 4;
    v54 = (char *)v54 - 1;
  }
  while ( !v11 );
  v12 = operator new(0x84u);
  Block = v12;
  v56 = 4;
  if ( v12 != nullptr )
  {
    v54 = *(void **)(this + 28);
    sub_426BD0(v12);
    LOBYTE(v56) = 5;
    *v12 = &nengine::CNButton::`vftable';
    sub_69C780(v12);
    sub_69C7B0(v54, 46, 47, 48, -1, 0, 0);
  }
  else
  {
    v12 = nullptr;
  }
  v56 = -1;
  *(uint32_t *)(this + 44) = v12;
  sub_69A840(v12);
  *(uint8_t *)(*(uint32_t *)(this + 44) + 16) = 0;
  sub_69A5F0(*(uint32_t **)(this + 44), 137, 408);
  v13 = operator new(0x84u);
  v14 = v13;
  Block = v13;
  v56 = 6;
  if ( v13 != nullptr )
  {
    v54 = *(void **)(this + 28);
    sub_426BD0(v13);
    LOBYTE(v56) = 7;
    *v14 = &nengine::CNButton::`vftable';
    sub_69C780(v14);
    sub_69C7B0(v54, 49, 50, 51, -1, 0, 0);
  }
  else
  {
    v14 = nullptr;
  }
  v56 = -1;
  *(uint32_t *)(this + 48) = v14;
  sub_69A840(v14);
  *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 0;
  sub_69A5F0(*(uint32_t **)(this + 48), 195, 408);
  v55 = (int)&unk_73E290;
  v15 = (uint32_t **)(this + 100);
  do
  {
    v16 = operator new(0x84u);
    v54 = v16;
    v56 = 8;
    if ( v16 != nullptr )
    {
      v53 = *(uint32_t *)(this + 20);
      sub_426BD0(v16);
      v17 = v54;
      LOBYTE(v56) = 9;
      *(uint32_t *)v54 = &nengine::CNButton::`vftable';
      sub_69C780(v17);
      sub_69C7B0(v53, 36, 36, 36, -1, 0, 0);
      v18 = v54;
    }
    else
    {
      v18 = nullptr;
    }
    *v15 = v18;
    v56 = -1;
    sub_69A840(v18);
    sub_69A5F0(*v15, *(uint32_t *)v55, *(uint32_t *)(v55 + 4));
    *((uint8_t *)*v15 + 16) = 0;
    (*v15)[17] = this;
    v19 = operator new(0x84u);
    v54 = v19;
    v56 = 10;
    if ( v19 != nullptr )
    {
      v53 = *(uint32_t *)(this + 20);
      sub_426BD0(v19);
      v20 = v54;
      LOBYTE(v56) = 11;
      *(uint32_t *)v54 = &nengine::CNButton::`vftable';
      sub_69C780(v20);
      sub_69C7B0(v53, 37, 38, 39, -1, 0, 0);
      v21 = v54;
    }
    else
    {
      v21 = nullptr;
    }
    v56 = -1;
    v15[1] = v21;
    sub_69A840(v21);
    sub_69A5F0(v15[1], *(uint32_t *)v55 + 256, *(uint32_t *)(v55 + 4) + 8);
    *((uint8_t *)v15[1] + 16) = 1;
    v22 = operator new(0x84u);
    v54 = v22;
    v56 = 12;
    if ( v22 != nullptr )
    {
      v53 = *(uint32_t *)(this + 20);
      sub_426BD0(v22);
      v23 = v54;
      LOBYTE(v56) = 13;
      *(uint32_t *)v54 = &nengine::CNButton::`vftable';
      sub_69C780(v23);
      sub_69C7B0(v53, 43, 44, 45, -1, 0, 0);
      v24 = v54;
    }
    else
    {
      v24 = nullptr;
    }
    v56 = -1;
    v15[3] = v24;
    sub_69A840(v24);
    sub_69A5F0(v15[3], *(uint32_t *)v55 + 46, *(uint32_t *)(v55 + 4) + 28);
    *((uint8_t *)v15[3] + 16) = 1;
    v25 = operator new(0x84u);
    v54 = v25;
    v56 = 14;
    if ( v25 != nullptr )
    {
      v53 = *(uint32_t *)(this + 20);
      sub_426BD0(v25);
      v26 = v54;
      LOBYTE(v56) = 15;
      *(uint32_t *)v54 = &nengine::CNButton::`vftable';
      sub_69C780(v26);
      sub_69C7B0(v53, 43, 44, 45, -1, 0, 0);
      v27 = v54;
    }
    else
    {
      v27 = nullptr;
    }
    v56 = -1;
    v15[2] = v27;
    sub_69A840(v27);
    sub_69A5F0(v15[2], *(uint32_t *)v55 + 46, *(uint32_t *)(v55 + 4) + 48);
    *((uint8_t *)v15[2] + 16) = 1;
    v15 -= 4;
    v55 -= 8;
  }
  while ( v55 >= (int)&unk_73E278 );
  v28 = operator new(0x84u);
  Block = v28;
  v56 = 16;
  if ( v28 != nullptr )
  {
    v53 = *(uint32_t *)(this + 20);
    sub_426BD0(v28);
    LOBYTE(v56) = 17;
    *v28 = &nengine::CNButton::`vftable';
    sub_69C780(v28);
    sub_69C7B0(v53, 43, 44, 45, -1, 0, 0);
  }
  else
  {
    v28 = nullptr;
  }
  v56 = -1;
  *(uint32_t *)(this + 128) = v28;
  sub_69A840(v28);
  sub_69A5F0(*(uint32_t **)(this + 128), 226, 133);
  *(uint8_t *)(*(uint32_t *)(this + 128) + 16) = 1;
  v29 = operator new(0x84u);
  v30 = v29;
  Block = v29;
  v56 = 18;
  if ( v29 != nullptr )
  {
    v53 = *(uint32_t *)(this + 20);
    sub_426BD0(v29);
    LOBYTE(v56) = 19;
    *v30 = &nengine::CNButton::`vftable';
    sub_69C780(v30);
    sub_69C7B0(v53, 43, 44, 45, -1, 0, 0);
  }
  else
  {
    v30 = nullptr;
  }
  v56 = -1;
  *(uint32_t *)(this + 124) = v30;
  sub_69A840(v30);
  sub_69A5F0(*(uint32_t **)(this + 124), 226, 153);
  *(uint8_t *)(*(uint32_t *)(this + 124) + 16) = 1;
  v54 = (void *)(this + 2076);
  v55 = 3;
  do
  {
    v31 = operator new(0x84u);
    v32 = v31;
    Block = v31;
    v56 = 20;
    if ( v31 != nullptr )
    {
      v53 = *(uint32_t *)(this + 20);
      sub_426BD0(v31);
      LOBYTE(v56) = 21;
      *v32 = &nengine::CNButton::`vftable';
      sub_69C780(v32);
      sub_69C7B0(v53, 40, 41, 41, -1, 0, 0);
      v33 = v32;
    }
    else
    {
      v33 = nullptr;
    }
    v34 = (char *)v54;
    *(uint32_t *)v54 = v33;
    v56 = -1;
    sub_69A840(v33);
    *(uint8_t *)(*(uint32_t *)v34 + 16) = 0;
    *(uint32_t *)(*(uint32_t *)v34 + 68) = this;
    v11 = v55 == 1;
    v54 = v34 + 4;
    --v55;
  }
  while ( !v11 );
  v54 = (void *)(this + 2088);
  v55 = 60;
  do
  {
    v35 = operator new(0x84u);
    v36 = v35;
    Block = v35;
    v56 = 22;
    if ( v35 != nullptr )
    {
      v53 = *(uint32_t *)(this + 20);
      sub_426BD0(v35);
      LOBYTE(v56) = 23;
      *v36 = &nengine::CNButton::`vftable';
      sub_69C780(v36);
      sub_69C7B0(v53, 40, 41, 41, -1, 0, 0);
      v37 = v36;
    }
    else
    {
      v37 = nullptr;
    }
    v38 = (char *)v54;
    *(uint32_t *)v54 = v37;
    v56 = -1;
    sub_69A840(v37);
    *(uint8_t *)(*(uint32_t *)v38 + 16) = 0;
    *(uint32_t *)(*(uint32_t *)v38 + 68) = this;
    v11 = v55 == 1;
    v54 = v38 + 4;
    --v55;
  }
  while ( !v11 );
  v51[0] = (void *)10;
  v51[1] = (void *)22;
  v50[0] = 0;
  v50[1] = 0;
  v49[0] = 2;
  v49[1] = 2;
  v55 = this + 116;
  v54 = nullptr;
  do
  {
    v39 = operator new(0x2Cu);
    v51[2] = v39;
    v56 = 24;
    if ( v39 != nullptr )
    {
      v53 = *(uint32_t *)(this + 20);
      Block = (void *)dword_79C0B0;
      *((uint8_t *)v39 + 4) = 0;
      LOBYTE(v56) = 25;
      *v39 = &nengine::CNNumberSet::`vftable';
      sub_699E20(v39);
      sub_699E40(Block, v53, *(void **)((char *)v51 + (uint32_t)v54), 10);
    }
    else
    {
      v39 = nullptr;
    }
    v40 = v55;
    v41 = (char *)v54;
    v42 = *(uint32_t *)((char *)v50 + (uint32_t)v54);
    *(uint32_t *)v55 = v39;
    v39[10] = v42;
    *(uint32_t *)(*(uint32_t *)v40 + 36) = *(uint32_t *)((char *)v49 + (uint32_t)v41);
    v43 = *(uint32_t *)v40;
    v56 = -1;
    *(uint8_t *)(v43 + 24) = 0;
    v54 = v41 + 4;
    v55 = v40 + 4;
  }
  while ( (int)(v41 + 4) < 8 );
  *(uint8_t *)(this + 2341) = 0;
  *(uint8_t *)(this + 2342) = 0;
  return sub_698F90(this + 2328, 0, 0);
}


// ------------------------------------------------------------
// 0x648630 sub_648630 —— 商城页装配（6464C0/647B60 + 422E70/4649B0）
// ------------------------------------------------------------
char /*thiscall*/ sub_648630(uint32_t *this, int a2)
{
  uint32_t *v2; // edi
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
  int *v17; // [esp+18h] [ebp-4h]

  v2 = this;
  v3 = 0;
  LOBYTE(v4) = (uint8_t)this + 40;
  v16 = 0;
  v17 = this + 522;
  do
  {
    v5 = *v17;
    if ( *v17 == a2 )
    {
      LOBYTE(v4) = *(uint8_t *)(v5 + 16);
      if ( (uint8_t)v4 != 0 )
      {
        v4 = v2[517];
        if ( v4 != 0 )
        {
          sub_6464C0(v2, *(uint32_t *)(v5 + 20) + 2, *(uint32_t *)(v5 + 24) + 1, v3, *(uint32_t *)(v4 + 76), 1);
          LOBYTE(v4) = *(uint8_t *)(v5 + 17);
          if ( (uint8_t)v4 != 0 && dword_79BE3C == *(uint32_t *)(v5 + 12) )
          {
            v4 = sub_647B60(v2, *(uint32_t *)(v2[517] + 76), v3);
            if ( v4 == 0 )
            {
              v6 = *(uint32_t *)(v5 + 24);
              v7 = *(uint32_t *)(v5 + 28);
              v15 = *(uint32_t *)(v5 + 20);
              v8 = sub_422E70(895);
              sub_4649B0(v15 + (v7 >> 1), v6, -16776961, -16777216, 2, (int)v8, 0, 0, 1600, 0);
              v9 = *(uint32_t *)(v5 + 24);
              v10 = *(uint32_t *)(v5 + 28);
              v11 = *(uint32_t *)(v5 + 20);
              v12 = sub_422E70(896);
              LOBYTE(v4) = sub_4649B0(v11 + (v10 >> 1), v9, -16776961, -16777216, 2, (int)v12, 0, 0, 1600, 0);
              v3 = v16;
              v2 = this;
            }
          }
        }
      }
    }
    v16 = ++v3;
    ++v17;
  }
  while ( v3 < 60 );
  return v4;
}



// ------------------------------------------------------------
// 0x648770 CNRDCashShopBuyWindow__vmt0 —— CNRDCashShopBuyWindow__vmt0 构造（6455D0/6466D0/645680/645930/645DB0/646C70/646C10/648630 + 422E70/4649B0 装配链）
// ------------------------------------------------------------
char /*thiscall*/ CNRDCashShopBuyWindow__vmt0(int16_t *this, int Value)
{
  int v3; // eax
  unsigned int v4; // esi
  int v5; // edi
  int v6; // ebx
  char *v7; // eax

  if ( Value == *((uint32_t *)this + 3) )
  {
    sub_6455D0(this);
    if ( *((uint32_t *)this + 510) != 0 )
      sub_6466D0((int)this);
    else
      sub_645680(this);
    sub_645930(this);
    LOBYTE(v3) = sub_645DB0(this);
  }
  else
  {
    if ( *((uint32_t *)this + 510) == 0 )
      sub_646C70(this, Value);
    sub_646C10((int *)this, Value);
    sub_648630(this, Value);
    v3 = *((uint32_t *)this + 10);
    if ( Value == v3 && *(uint8_t *)(v3 + 17) != 0 && dword_79BE3C == *(uint32_t *)(v3 + 12) )
    {
      v4 = *(uint32_t *)(v3 + 28);
      v5 = *(uint32_t *)(v3 + 24);
      v6 = *(uint32_t *)(v3 + 20);
      v7 = sub_422E70(902);
      LOBYTE(v3) = sub_4649B0(v6 + (v4 >> 1), v5 - 5, -1, -16777216, 2, (int)v7, 0, 0, 1600, 0);
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x648850 sub_648850 —— 商城数据 6（645EE0 + 4015C0）
// ------------------------------------------------------------
int /*fastcall*/ sub_648850(int a1, int a2, int a3)
{
  int v4; // esi
  int result; // eax
  uint8_t *v6; // eax
  bool v7; // zf
  int v8; // ecx
  int v9; // edx
  int v10; // [esp+14h] [ebp+8h]
  int v11; // [esp+14h] [ebp+8h]

  v4 = a3 + 4 * *(uint32_t *)(a1 + 2044);
  result = 84 * v4 + a1;
  v10 = result;
  if ( *(uint32_t *)(result + 416) != 0 )
  {
    sub_645EE0((int *)a1);
    if ( v4 < 19 )
    {
      v6 = (uint8_t *)(v10 + 340);
      v11 = 19 - v4;
      do
      {
        qmemcpy(v6, v6 + 84, 0x54u);
        v7 = v11 == 1;
        v6[80] = 0;
        v6 += 84;
        --v11;
      }
      while ( !v7 );
    }
    *(uint32_t *)(a1 + 1936) = -1;
    *(uint32_t *)(a1 + 1940) = -1;
    *(uint32_t *)(a1 + 1944) = 0;
    *(uint32_t *)(a1 + 1948) = -1;
    *(uint8_t *)(a1 + 1952) = -1;
    *(uint32_t *)(a1 + 1956) = 0;
    *(uint8_t *)(a1 + 1960) = 0;
    *(uint16_t *)(a1 + 1962) = 0;
    *(uint32_t *)(a1 + 1964) = 0;
    *(uint32_t *)(a1 + 1968) = 0;
    *(uint32_t *)(a1 + 1972) = 0;
    *(uint32_t *)(a1 + 1976) = 0;
    *(uint8_t *)(a1 + 1980) = -1;
    sub_4015C0((void *)szPassword, 0);
    *(uint32_t *)(a1 + 2012) = 0;
    v8 = *(uint32_t *)(a1 + 2036) - 1;
    *(uint32_t *)(a1 + 2036) = v8;
    v9 = *(uint32_t *)(a1 + 2044);
    result = (v8 - 1) / 4;
    *(uint32_t *)(a1 + 2048) = result;
    if ( v9 > result )
      *(uint32_t *)(a1 + 2044) = result;
    if ( v8 == 0 )
    {
      *(uint8_t *)(*(uint32_t *)(a1 + 12) + 16) = 0;
      memset((void *)(a1 + 340), 0, 0x690u);
      return 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x648980 sub_648980 —— CNRDCashShopBuyWindow__vmt8 Update（139 行：CLICK_BUTTON2/CLICK_MOVE/COMMAND_SELECT/SCROLL_ARROW 事件 + 6470A0/6472C0/647550/6474A0/645F20 刷新链）
// ------------------------------------------------------------
int /*thiscall*/ sub_648980(int this)
{
  int v2; // eax
  int v3; // edi
  int result; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edi
  uint32_t *v10; // ebx
  int v11; // eax
  int v12; // ecx
  int v13; // edx
  int i; // edx

  v2 = *(uint32_t *)(this + 32);
  v3 = dword_79BE34;
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    sub_432EA0("COMMAND_SELECT", -1, 0, 0);
    return sub_6470A0(this);
  }
  else
  {
    v5 = *(uint32_t *)(this + 40);
    if ( *(uint8_t *)(v5 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v5 + 12) )
    {
      sub_432EA0("COMMAND_SELECT", -1, 0, 0);
      *(uint8_t *)(this + 2341) = 0;
      *(uint8_t *)(this + 2342) = 0;
      sub_698F90(this + 2328, 0, 0);
      *(uint8_t *)(*(uint32_t *)(this + 40) + 17) = 0;
      return sub_55E2D0(*(uint32_t *)(this + 8));
    }
    else
    {
      v6 = *(uint32_t *)(this + 36);
      if ( *(uint8_t *)(v6 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v6 + 12) )
      {
        sub_432EA0("COMMAND_SELECT", -1, 0, 0);
        *(uint8_t *)(*(uint32_t *)(this + 12) + 16) = 0;
        memset((void *)(this + 340), 0, 0x690u);
        return 0;
      }
      else
      {
        v7 = *(uint32_t *)(this + 44);
        if ( *(uint8_t *)(v7 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v7 + 12) )
        {
          sub_432EA0("SCROLL_ARROW", -1, 0, 0);
          return sub_6472C0(-1);
        }
        else
        {
          v8 = *(uint32_t *)(this + 48);
          if ( *(uint8_t *)(v8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v8 + 12) )
          {
            sub_432EA0("SCROLL_ARROW", -1, 0, 0);
            return sub_6472C0(1);
          }
          else if ( *(uint32_t *)(this + 2040) != 0 )
          {
            if ( (uint8_t)sub_43B500(*(uint32_t *)(this + 128)) != 0 )
            {
              sub_647550((uint32_t *)this, 0, -1);
            }
            else if ( (uint8_t)sub_43B500(*(uint32_t *)(this + 124)) != 0 )
            {
              sub_6474A0(0, -1);
            }
            else
            {
LABEL_28:
              v12 = 1;
              v13 = this + 2076;
              do
              {
                if ( *(uint8_t *)(*(uint32_t *)v13 + 17) != 0 && v3 == *(uint32_t *)(*(uint32_t *)v13 + 12) )
                {
                  sub_645F20(v12);
                  return (int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
                }
                ++v12;
                v13 += 4;
              }
              while ( v12 < 4 );
              result = 0;
              for ( i = this + 2088; *(uint8_t *)(*(uint32_t *)i + 17) == 0 || v3 != *(uint32_t *)(*(uint32_t *)i + 12); i += 4 )
              {
                if ( ++result >= 60 )
                  return result;
              }
              *(uint8_t *)(*(uint32_t *)(this + 2068) + 16) = result;
              sub_645EE0(this);
            }
            return (int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
          }
          else
          {
            v9 = 0;
            v10 = (uint32_t *)(this + 64);
            while ( 1 )
            {
              v11 = *(v10 - 2);
              if ( *(uint8_t *)(v11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v11 + 12) )
              {
                sub_432EA0("CLICK_MOVE", -1, 0, 0);
                sub_648850(v9);
                return sub_6472C0(0);
              }
              if ( (uint8_t)sub_43B500(*v10) != 0 )
              {
                sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
                return (int)sub_647550((uint32_t *)this, v9, -1);
              }
              if ( (uint8_t)sub_43B500(*(v10 - 1)) != 0 )
                break;
              ++v9;
              v10 += 4;
              if ( v9 >= 4 )
              {
                v3 = dword_79BE34;
                goto LABEL_28;
              }
            }
            sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
            return sub_6474A0(v9, -1);
          }
        }
      }
    }
  }
}


// ------------------------------------------------------------
// 0x648C10 CNRDCashShopBuyWindow__vmt4 —— CNRDCashShopBuyWindow__vmt4 析构（648980 + 699000）
// ------------------------------------------------------------
int /*thiscall*/ CNRDCashShopBuyWindow__vmt4(int this)
{
  int result; // eax

  if ( *(uint8_t *)(*(uint32_t *)(this + 12) + 16) != 0 && *(uint8_t *)(this + 2052) == 0 )
    sub_648980(this);
  result = sub_699000(this + 2328);
  if ( result > 5000 )
    *(uint8_t *)(*(uint32_t *)(this + 40) + 17) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x648C50 sub_648C50 —— 版本信息数据（36 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_648C50(int this, LPCSTR lptstrFilename)
{
  const CHAR *v2; // edi
  size_t FileVersionInfoSizeA; // eax
  DWORD v5; // esi
  void *v6; // eax
  unsigned int puLen; // [esp+Ch] [ebp-8h] BYREF
  DWORD dwHandle; // [esp+10h] [ebp-4h] BYREF

  v2 = lptstrFilename;
  dwHandle = 0;
  FileVersionInfoSizeA = GetFileVersionInfoSizeA(lptstrFilename, &dwHandle);
  v5 = FileVersionInfoSizeA;
  if ( FileVersionInfoSizeA != 0 )
  {
    v6 = malloc(FileVersionInfoSizeA);
    *(uint32_t *)(this + 56) = v6;
    if ( v6 != nullptr && GetFileVersionInfoA(v2, 0, v5, v6) )
    {
      puLen = 0;
      lptstrFilename = nullptr;
      if ( VerQueryValueA(*(LPCVOID *)(this + 56), SubBlock, (LPVOID *)&lptstrFilename, &puLen) )
      {
        qmemcpy((void *)(this + 4), lptstrFilename, 0x34u);
        *(uint32_t *)(this + 72) = *(uint32_t *)(this + 4) == -17890115;
      }
    }
  }
  return *(uint32_t *)(this + 72);
}



// ------------------------------------------------------------
// 0x648CE0 sub_648CE0 —— 版本信息数据 2（26 行）
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_648CE0(uint32_t *this)
{
  unsigned int v3; // ecx
  const void *v4; // [esp-10h] [ebp-1Ch]
  unsigned int puLen; // [esp+4h] [ebp-8h] BYREF
  LPVOID lpBuffer; // [esp+8h] [ebp-4h] BYREF

  if ( *(this + 18) == 0 )
    return false;
  v4 = (const void *)*(this + 14);
  puLen = 0;
  lpBuffer = nullptr;
  if ( VerQueryValueA(v4, "\\VarFileInfo\\Translation", &lpBuffer, &puLen) )
  {
    v3 = puLen >> 2;
    *(this + 15) = lpBuffer;
    *(this + 17) = v3;
  }
  return *(this + 15) != 0;
}



// ------------------------------------------------------------
// 0x648D40 sub_648D40 —— 版本信息数据 3（19 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_648D40(int this)
{
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 60) = 0;
  memset((void *)(this + 4), 0, 0x34u);
  if ( *(uint32_t *)(this + 56) != 0 )
  {
    free(*(void **)(this + 56));
    *(uint32_t *)(this + 56) = 0;
  }
}



// ------------------------------------------------------------
// 0x648D80 sub_648D80 —— 版本信息数据 4（22 行）
// ------------------------------------------------------------
char */*thiscall*/ sub_648D80(char *this)
{
  *((uint32_t *)this + 14) = 0;
  *(uint32_t *)this = &vftbl_CFileVersionInfo;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 15) = 0;
  memset(this + 4, 0, 0x34u);
  if ( *((uint32_t *)this + 14) != 0 )
  {
    free(*((void **)this + 14));
    *((uint32_t *)this + 14) = 0;
  }
  return this;
}



// ------------------------------------------------------------
// 0x648DD0 sub_648DD0 —— 版本信息数据 5（20 行）
// ------------------------------------------------------------
void /*thiscall*/ sub_648DD0(char *this)
{
  *(uint32_t *)this = &vftbl_CFileVersionInfo;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 15) = 0;
  memset(this + 4, 0, 0x34u);
  if ( *((uint32_t *)this + 14) != 0 )
  {
    free(*((void **)this + 14));
    *((uint32_t *)this + 14) = 0;
  }
}



// ------------------------------------------------------------
// 0x648E10 sub_648E10 —— 版本信息查询（648C50/648CE0，35 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_648E10(int this, LPCSTR lptstrFilename)
{
  if ( lptstrFilename == nullptr )
    return 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 60) = 0;
  memset((void *)(this + 4), 0, 0x34u);
  if ( *(uint32_t *)(this + 56) != 0 )
  {
    free(*(void **)(this + 56));
    *(uint32_t *)(this + 56) = 0;
  }
  if ( sub_648C50(this, lptstrFilename) == 0 || !sub_648CE0((uint32_t *)this) )
  {
    *(uint32_t *)(this + 68) = 0;
    *(uint32_t *)(this + 64) = 0;
    *(uint32_t *)(this + 72) = 0;
    *(uint32_t *)(this + 60) = 0;
    memset((void *)(this + 4), 0, 0x34u);
    if ( *(uint32_t *)(this + 56) != 0 )
    {
      free(*(void **)(this + 56));
      *(uint32_t *)(this + 56) = 0;
    }
  }
  return *(uint32_t *)(this + 72);
}



// ------------------------------------------------------------
// 0x648EB0 CFileVersionInfo__vmt0 —— CFileVersionInfo__vmt0 构造（23 行——GetFileVersionInfo 系封装）
// ------------------------------------------------------------
char */*thiscall*/ CFileVersionInfo__vmt0(char *Block, char a2)
{
  *(uint32_t *)Block = &vftbl_CFileVersionInfo;
  *((uint32_t *)Block + 17) = 0;
  *((uint32_t *)Block + 16) = 0;
  *((uint32_t *)Block + 18) = 0;
  *((uint32_t *)Block + 15) = 0;
  memset(Block + 4, 0, 0x34u);
  if ( *((uint32_t *)Block + 14) != 0 )
  {
    free(*((void **)Block + 14));
    *((uint32_t *)Block + 14) = 0;
  }
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x648F10 sub_648F10 —— 版本信息转发（648E10）
// ------------------------------------------------------------
int /*thiscall*/ sub_648F10(void *this, HMODULE hModule)
{
  CHAR Filename[260]; // [esp+8h] [ebp-108h] BYREF
  int v5; // [esp+10Ch] [ebp-4h]

  v5 = dword_796E50;
  memset(Filename, 0, sizeof(Filename));
  if ( GetModuleFileNameA(hModule, Filename, 0x104u) != 0 )
    return sub_648E10((int)this, Filename);
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
int /*thiscall*/ CNAuraMasterIce__vmt1C(void *this)
{
  CNRDAuraMaster__vmt1C();
  return (*(int (/*thiscall*/ **)(void *, const char *))(*(uint32_t *)this + 128))(
           this,
           "Common/Etc/Animation/Aura/IceAuraMaster.ani");
}



// ------------------------------------------------------------
// 0x648FB0 sub_648FB0 —— 冰冻伤害结算：AURA_ICE_DMG 事件（605840 目标 + 4E4A50/432FA0），79 行
// ------------------------------------------------------------
int /*thiscall*/ sub_648FB0(int this)
{
  int result; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // ebx
  int v10; // eax
  int16_t *v11; // eax
  float v12; // [esp+4h] [ebp-20h] BYREF
  float v13; // [esp+8h] [ebp-1Ch]
  float v14; // [esp+Ch] [ebp-18h]
  int v15; // [esp+10h] [ebp-14h]
  int v16; // [esp+14h] [ebp-10h]
  int v17; // [esp+18h] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-8h]
  int v19; // [esp+20h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 100) + 12))(*(uint32_t *)(this + 100), 0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 104) + 12))(*(uint32_t *)(this + 104), 0);
  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 624))(*(uint32_t *)(this + 4));
    if ( (uint8_t)result != 0 )
    {
      v3 = *(uint32_t *)(this + 4);
      v12 = 0.0;
      v13 = 0.0;
      v14 = 0.0;
      v15 = 0;
      v16 = 0;
      v17 = 0;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
      v5 = *(uint32_t *)(this + 4);
      v18 = v4;
      v12 = (float)v4;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 124))(v5);
      v7 = *(uint32_t *)(this + 4);
      v18 = v6;
      v13 = (float)v6;
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 192))(v7) / 2;
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 128))(v7) + v8;
      v10 = *(uint32_t *)(this + 4);
      v18 = v9;
      v14 = (float)v9;
      v19 = 0;
      v11 = sub_605840(&v19, v10, (int *)&v12, 1);
      sub_4E4A50(*(uint32_t *)(this + 36), 42003, *(uint32_t *)(this + 96), 0, 0, 0, 1, 0, v19, v11);
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
        *(uint32_t *)(this + 4),
        "AURA_ICE_DMG",
        -1,
        0,
        0);
      sub_432FA0();
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 4) + 776))(*(uint32_t *)(this + 4), 1) == 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 760))(
          *(uint32_t *)(this + 4),
          1,
          1103626240,
          2,
          *(uint32_t *)(this + 36),
          0);
      result = *(uint32_t *)(this + 108);
      *(uint32_t *)(this + 72) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x649100 CNAuraMasterCurse__vmt84 —— CNAuraMasterCurse__vmt84 受击伤害事件槽（22 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraMasterCurse__vmt84(uint32_t **this, int a2)
{
  int v3; // edi
  bool result; // al

  result = true;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 273) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529) == 0 )
      return false;
    v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 376))(*(this + 1));
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2) != v3 )
      return false;
  }
  return result;
}



// ------------------------------------------------------------
// 0x649160 CNDarkDamageFromCurseAura__vmt1C —— CNDarkDamageFromCurseAura__vmt1C 生成装配（5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNDarkDamageFromCurseAura__vmt1C(void *this)
{
  return sub_5F66A0((int)this, 1);
}



// ------------------------------------------------------------
// 0x649170 CNDarkDamageFromCurseAura__vmt78 —— CNDarkDamageFromCurseAura__vmt78 光环生效槽（17 行）
// ------------------------------------------------------------
int /*thiscall*/ CNDarkDamageFromCurseAura__vmt78(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 26) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6491A0 CNDarkDamageFromCurseAura__vmt4 —— CNDarkDamageFromCurseAura__vmt4 复位/伤害（605840/4E4A50/699000，80 行）
// ------------------------------------------------------------
int /*thiscall*/ CNDarkDamageFromCurseAura__vmt4(int this)
{
  int result; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int *v7; // edi
  int v8; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int16_t *v12; // eax
  int v13; // edi
  float v14; // [esp+8h] [ebp-20h] BYREF
  float v15; // [esp+Ch] [ebp-1Ch]
  float v16; // [esp+10h] [ebp-18h]
  int v17; // [esp+14h] [ebp-14h]
  int v18; // [esp+18h] [ebp-10h]
  int v19; // [esp+1Ch] [ebp-Ch]
  int v20; // [esp+20h] [ebp-8h]
  int v21; // [esp+24h] [ebp-4h] BYREF

  CNRDAuraMinion__vmt4();
  result = *(uint32_t *)(this + 136);
  if ( result == 2 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));
    if ( (uint8_t)result != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 128))(*(uint32_t *)(this + 4)) < 50
        && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 624))(*(uint32_t *)(this + 4)) != 0 )
      {
        v3 = *(uint32_t *)(this + 4);
        v14 = 0.0;
        v15 = 0.0;
        v16 = 0.0;
        v17 = 0;
        v18 = 0;
        v19 = 0;
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
        v5 = *(uint32_t *)(this + 4);
        v20 = v4;
        v14 = (float)v4;
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 124))(v5);
        v7 = *(int **)(this + 4);
        v20 = v6;
        v15 = (float)v6;
        v8 = (*(int (/*thiscall*/ **)(int *))(*v7 + 192))(v7);
        v9 = *v7;
        v20 = v8 / 2;
        v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 128))(v7) + v8 / 2;
        v11 = *(uint32_t *)(this + 4);
        v20 = v10;
        v16 = (float)v10;
        v21 = 0;
        v12 = sub_605840(&v21, v11, (int *)&v14, 1);
        sub_4E4A50(*(uint32_t *)(this + 36), 42005, *(uint32_t *)(this + 96), 0, 0, 0, 1, 0, v21, v12);
      }
      result = *(uint32_t *)(this + 100);
      *(uint32_t *)(this + 72) = result;
      *(uint8_t *)(this + 140) = 1;
      *(uint32_t *)(this + 136) = 0;
    }
  }
  else if ( result == 1 )
  {
    v13 = *(uint32_t *)(this + 132);
    result = sub_699000(this + 108);
    if ( result >= v13 )
      *(uint32_t *)(this + 136) = 2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x649300 sub_649300 —— 召唤受方表现初始化（64A880 + 5F6640）
// ------------------------------------------------------------
int /*thiscall*/ sub_649300(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNRDAuraMinion;
  sub_64A880();
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x649360 CNRDAuraMinion__vmt0 —— CNRDAuraMinion__vmt0 析构（转发 649300）
// ------------------------------------------------------------
void */*thiscall*/ CNRDAuraMinion__vmt0(void *Block, char a2)
{
  sub_649300((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x649390 sub_649390 —— 冰受方装配（4B1030 + 64A350）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_649390(uint32_t *this, int a2, int a3)
{
  sub_4B1030(this);
  *this = &vftbl_CNRDAuraMinion;
  sub_64A350(this);
  *this = &vftbl_CNIceDamageFromIceAura;
  *(this + 24) = a2;
  *(this + 27) = a3;
  *(this + 18) = (uint64_t)((double)a3 * 0.5);
  return this;
}



// ------------------------------------------------------------
// 0x649400 CNIceDamageFromIceAura__vmt0 —— CNIceDamageFromIceAura__vmt0 析构（转发 649430）
// ------------------------------------------------------------
void */*thiscall*/ CNIceDamageFromIceAura__vmt0(void *Block, char a2)
{
  sub_649430();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x649430 sub_649430 —— 冰受方初始化（649300 系，22 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_649430(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  *this = &vftbl_CNIceDamageFromIceAura;
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  v3 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  *(this + 25) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  *(this + 26) = 0;
  return sub_649300((int)this);
}



// ------------------------------------------------------------
// 0x6494B0 sub_6494B0 —— 诅咒受方装配（4B1030 + 64A350 + 698F90）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_6494B0(uint8_t *this, int a2, int a3)
{
  sub_4B1030(this);
  *(uint32_t *)this = &vftbl_CNRDAuraMinion;
  sub_64A350(this);
  *(uint32_t *)this = &vftbl_CNDarkDamageFromCurseAura;
  *(this + 112) = 0;
  *((uint32_t *)this + 27) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 29) = 0;
  *(this + 120) = 1;
  *(this + 122) = 0;
  *(this + 121) = 0;
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 25) = a3;
  *((uint32_t *)this + 24) = a2;
  *(this + 121) = 0;
  *(this + 122) = 0;
  sub_698F90((int)(this + 108), 1500, 0);
  *((uint32_t *)this + 26) = 0;
  *((uint32_t *)this + 34) = 1;
  *(this + 140) = 1;
  return this;
}



// ------------------------------------------------------------
// 0x649560 sub_649560 —— 诅咒受方初始化（649300，19 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_649560(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *this = &vftbl_CNDarkDamageFromCurseAura;
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 26);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 26) = 0;
  *(this + 27) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 112) = 0;
  return sub_649300((int)this);
}



// ------------------------------------------------------------
// 0x6495D0 CNAuraMasterIce__vmt78 —— CNAuraMasterIce__vmt78 光环生效：AURA_ICE_SET 事件（转发 649390）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterIce__vmt78(int *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  v3 = operator new(0x70u);
  if ( v3 != nullptr )
    v4 = sub_649390(v3, *(this + 32), *(this + 33));
  else
    v4 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v4 + 56))(
    v4,
    a2,
    *(this + 1),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a2 + 212))(
           a2,
           "AURA_ICE_SET",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x649670 CNDarkDamageFromCurseAura__vmt0 —— CNDarkDamageFromCurseAura__vmt0 析构（转发 649560）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNDarkDamageFromCurseAura__vmt0(uint32_t *Block, char a2)
{
  sub_649560(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x6496A0 CNAuraMasterIce__vmt7C —— CNAuraMasterIce__vmt7C 光环失效/转移槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterIce__vmt7C(int a1)
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
  int v11; // eax

  if ( a1 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v3 = *(uint32_t *)(v2 + 4);
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v6 = *(uint32_t *)(v5 + 4);
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == a1 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
        v9 = *(uint32_t *)(v8 + 4);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNIceDamageFromIceAura `RTTI Type Descriptor',
                0);
        if ( v11 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 76))(v11, 0);
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x649750 CNAuraMasterCurse__vmt7C —— CNAuraMasterCurse__vmt7C 光环失效/转移槽（108 行）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterCurse__vmt7C(uint32_t *this, int a2)
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
  int v13; // eax
  int result; // eax
  int v15; // edi
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
  int v26; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 273) != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v5 = *(uint32_t *)(v4 + 4);
      v6 = v5 != 0 ? (*(uint32_t *)(v4 + 8) - v5) >> 2 : 0;
      if ( (int)i >= v6 )
        break;
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v8 = *(uint32_t *)(v7 + 4);
      if ( v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2 )
        v9 = *(uint32_t *)(v8 + 4 * i);
      else
        v9 = 0;
      if ( *(uint32_t *)(v9 + 4) == a2 )
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v11 = *(uint32_t *)(v10 + 4);
        if ( v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2 )
          v12 = *(uint32_t *)(v11 + 4 * i);
        else
          v12 = 0;
        v13 = __RTDynamicCast(
                v12,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNDarkDamageFromCurseAura `RTTI Type Descriptor',
                0);
        if ( v13 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v13 + 76))(v13, 0);
          break;
        }
      }
    }
  }
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529);
  if ( (uint8_t)result != 0 )
  {
    v15 = *(this + 1);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 376))(v15);
    if ( v16 == result )
    {
      for ( j = 0; ; ++j )
      {
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v19 = *(uint32_t *)(v18 + 4);
        result = v19 != 0 ? (*(uint32_t *)(v18 + 8) - v19) >> 2 : 0;
        if ( (int)j >= result )
          break;
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v21 = *(uint32_t *)(v20 + 4);
        if ( v21 != 0 && j < (*(uint32_t *)(v20 + 8) - v21) >> 2 )
          v22 = *(uint32_t *)(v21 + 4 * j);
        else
          v22 = 0;
        if ( *(uint32_t *)(v22 + 4) == a2 )
        {
          v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
          v24 = *(uint32_t *)(v23 + 4);
          if ( v24 != 0 && j < (*(uint32_t *)(v23 + 8) - v24) >> 2 )
            v25 = *(uint32_t *)(v24 + 4 * j);
          else
            v25 = 0;
          v26 = __RTDynamicCast(v25, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeStatus `RTTI Type Descriptor', 0);
          if ( v26 != 0 )
            return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v26 + 76))(v26, 0);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6498E0 CNIceDamageFromIceAura__vmt4 —— CNIceDamageFromIceAura__vmt4 伤害/复位（4600B0，62 行）
// ------------------------------------------------------------
int /*thiscall*/ CNIceDamageFromIceAura__vmt4(char *this)
{
  char *v1; // esi
  int **v2; // edi
  int v3; // esi
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
  char *v17; // [esp+1Ch] [ebp-14h]
  int v18; // [esp+20h] [ebp-10h]
  int v19; // [esp+2Ch] [ebp-4h]

  v1 = this;
  v17 = this;
  CNRDAuraMinion__vmt4();
  v2 = (int **)(v1 + 100);
  v18 = 2;
  do
  {
    v3 = *((uint32_t *)v1 + 1);
    v4 = **v2;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 128))(v3);
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 124))(v3);
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
    (*(void (/*thiscall*/ **)(int *))(v4 + 40))(*v2);
    (*(void (/*thiscall*/ **)(int *, char *))(**v2 + 92))(*v2, v13);
    v1 = v17;
    v5 = *((int **)v17 + 1);
    v6 = *v5;
    v19 = 0;
    v7 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v6 + 80))(v5, 2, 0, v13);
    sub_4600B0(v7, v10, v11, v12);
    v19 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++v2;
    result = v18 - 1;
    v8 = v18 == 1;
    Block = nullptr;
    v15 = 0;
    v16 = 0;
    --v18;
  }
  while ( !v8 );
  return result;
}



// ------------------------------------------------------------
// 0x6499A0 CNAuraMasterCurse__vmt4 —— CNAuraMasterCurse__vmt4 复位（699000/698F90/4600B0/41C5E0，99 行）
// ------------------------------------------------------------
void /*thiscall*/ CNAuraMasterCurse__vmt4(int this)
{
  int v2; // ebx
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int *v7; // ecx
  int v8; // edx
  void *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // ecx
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int *v16; // ecx
  int v17; // edx
  void *v18; // eax
  int v19; // [esp-Ch] [ebp-48h]
  int v20; // [esp-Ch] [ebp-48h]
  int v21; // [esp-8h] [ebp-44h]
  char v22[4]; // [esp+Ch] [ebp-30h] BYREF
  void *v23; // [esp+10h] [ebp-2Ch]
  char v24[4]; // [esp+1Ch] [ebp-20h] BYREF
  void *Block; // [esp+20h] [ebp-1Ch]
  int v26; // [esp+24h] [ebp-18h]
  int v27; // [esp+28h] [ebp-14h]
  uint32_t *v28; // [esp+2Ch] [ebp-10h] BYREF
  int v29; // [esp+38h] [ebp-4h]

  CNRDAuraMaster__vmt4();
  v2 = *(uint32_t *)(this + 164);
  if ( sub_699000(this + 140) >= v2 )
  {
    *(uint8_t *)(this + 153) = 0;
    *(uint8_t *)(this + 154) = 0;
    sub_698F90(this + 140, 125, 0);
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 128) + 12))(*(uint32_t *)(this + 128));
    v21 = *(uint32_t *)(this + 4);
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 128) + 112))(*(uint32_t *)(this + 128));
    v3 = *(uint32_t *)(this + 4);
    v4 = **(uint32_t **)(this + 128);
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 128))(v3) + 32;
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 124))(v3);
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 120))(v3, v5);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v4 + 40))(*(uint32_t *)(this + 128), v6);
    (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(this + 128) + 92))(*(uint32_t *)(this + 128), v22);
    v7 = *(int **)(this + 4);
    v8 = *v7;
    v29 = 0;
    v9 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v8 + 80))(v7, 2, 0, v22);
    sub_4600B0(v9, v19, v21, 0);
    v10 = *(uint32_t **)(this + 116);
    v11 = (uint32_t *)*v10;
    v28 = (uint32_t *)*v10;
    if ( v28 != v10 )
    {
      do
      {
        v12 = v11[4];
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 40))(v12, 273) == 0
          || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 128))(v12) < 50 )
        {
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 128) + 12))(*(uint32_t *)(this + 128));
          (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 128) + 112))(*(uint32_t *)(this + 128));
          v13 = **(uint32_t **)(this + 128);
          v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 128))(v12) + 32;
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 124))(v12);
          v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 120))(v12, v14);
          (*(void (/*thiscall*/ **)(uint32_t, int))(v13 + 40))(*(uint32_t *)(this + 128), v15);
          (*(void (/*thiscall*/ **)(uint32_t, char *))(**(uint32_t **)(this + 128) + 92))(*(uint32_t *)(this + 128), v24);
          v16 = *(int **)(this + 4);
          v17 = *v16;
          LOBYTE(v29) = 1;
          v18 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v17 + 80))(v16, 2, 0, v24);
          sub_4600B0(v18, v20, v12, 0);
          LOBYTE(v29) = 0;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          v26 = 0;
          v27 = 0;
        }
        sub_41C5E0(&v28);
        v11 = v28;
      }
      while ( v28 != *(uint32_t **)(this + 116) );
    }
    if ( v23 != nullptr )
      j__free(v23);
  }
}



// ------------------------------------------------------------
// 0x649B70 CNAuraMasterCurse__vmt78 —— CNAuraMasterCurse__vmt78 光环生效（6494B0 + 5101B0，79 行）
// ------------------------------------------------------------
void */*userpurge*/ CNAuraMasterCurse__vmt78@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>, int *Block)
{
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  int v7; // edx
  void *result; // eax
  int v9; // ebx
  double v10; // st7
  int v11; // eax
  uint64_t v12; // rax
  uint32_t *v13; // eax
  int *v14; // eax
  int v15; // edx
  int v16; // [esp-14h] [ebp-3Ch]
  int v18; // [esp+8h] [ebp-20h] BYREF
  char v19; // [esp+Ch] [ebp-1Ch]
  int v20; // [esp+10h] [ebp-18h]
  double v21; // [esp+14h] [ebp-14h]
  int v22; // [esp+24h] [ebp-4h]
  void *Blocka; // [esp+30h] [ebp+8h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*Block + 40))(Block, 273) != 0 )
  {
    v5 = operator new(0x90u);
    v22 = 0;
    if ( v5 != nullptr )
      v6 = sub_6494B0(v5, a1[34], a1[33]);
    else
      v6 = nullptr;
    v7 = *(uint32_t *)v6;
    v16 = a1[1];
    v22 = -1;
    (*(void (/*thiscall*/ **)(uint8_t *, int *, int, uint32_t, uint32_t, uint32_t, int))(v7 + 56))(v6, Block, v16, 0, 0, 0, -1);
  }
  result = (void *)(*(int (/*thiscall*/ **)(int *, int))(*Block + 40))(Block, 529);
  if ( (uint8_t)result != 0 )
  {
    v9 = a1[1];
    Blocka = (void *)(*(int (/*thiscall*/ **)(int *))(*Block + 376))(Block);
    result = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 376))(v9);
    if ( Blocka == result )
    {
      result = (void *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[1] + 308))(a1[1]);
      if ( (uint8_t)result != 0 )
      {
        v10 = (double)(*(int (/*thiscall*/ **)(int *, int))(*Block + 740))(Block, a2);
        v11 = *Block;
        v21 = v10 * 0.01;
        v12 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(v11 + 736))(Block) + v21);
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*Block + 728))(Block, v12, 1, 0);
        v18 = 7;
        v19 = 1;
        v20 = 1133903872;
        v13 = operator new(0x7Cu);
        v22 = 1;
        if ( v13 != nullptr )
          v14 = sub_5101B0(v13, (int)&v18, 1, 5000, 0);
        else
          v14 = nullptr;
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
uint32_t */*thiscall*/ sub_649CF0(uint32_t *this, int a2, int a3, int a4)
{
  sub_5910D0(a2, 18, 500, 0);
  *this = &vftbl_CNAuraMasterIce;
  *(this + 32) = a4;
  *(this + 33) = a3;
  return this;
}



// ============================================================
// 【分区 10】诅咒光环族 CNAuraMasterCurse / CNDarkDamageFromCurseAura（0x649D30-0x64A150）
// 资源 CurseAura.ptl；649FF0 挂 Monster/Ghoul/Particle/GhoulCurse.ptl
// （食尸鬼诅咒共用）；CNAuraChangeStatusMaster 系变化状态基类在本区尾段。
// ============================================================
// ------------------------------------------------------------
// 0x649D30 CNAuraMasterIce__vmt0 —— CNAuraMasterIce__vmt0 析构（转发 649D60）
// ------------------------------------------------------------
void */*thiscall*/ CNAuraMasterIce__vmt0(void *Block, char a2)
{
  sub_649D60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x649D60 sub_649D60 —— 冰光环析构成员（591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_649D60(uint32_t *this)
{
  *this = &vftbl_CNAuraMasterIce;
  return sub_591190(this);
}



// ------------------------------------------------------------
// 0x649D70 CNIceDamageFromIceAura__vmt1C —— CNIceDamageFromIceAura__vmt1C 生成装配：IceAuraMinionSnowFlake.ptl / IceAuraMinionSteam.ptl（428F30/5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNIceDamageFromIceAura__vmt1C(int *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int v4; // ecx
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  int v7; // ecx

  v2 = operator new(0x12Cu);
  if ( v2 != nullptr )
    v3 = sub_428F30(v2, (int)"Common/Etc/Particle/Aura/IceAuraMinionSnowFlake.ptl", *(this + 1));
  else
    v3 = nullptr;
  v4 = *(this + 1);
  *(this + 25) = (int)v3;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*v3 + 112))(v3, v4);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 25) + 12))(*(this + 25), 0);
  v5 = operator new(0x12Cu);
  if ( v5 != nullptr )
    v6 = sub_428F30(v5, (int)"Common/Etc/Particle/Aura/IceAuraMinionSteam.ptl", *(this + 1));
  else
    v6 = nullptr;
  v7 = *(this + 1);
  *(this + 26) = (int)v6;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*v6 + 112))(v6, v7);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 26) + 12))(*(this + 26), 0);
  return sub_5F66A0((int)this, 1);
}



// ------------------------------------------------------------
// 0x649E40 sub_649E40 —— 诅咒动画查询 2（5910D0 + 698F90）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_649E40(uint8_t *this, int a2, int a3, int a4)
{
  sub_5910D0(a2, 18, 100, 0);
  *(uint32_t *)this = &vftbl_CNAuraMasterCurse;
  *(this + 144) = 0;
  *((uint32_t *)this + 35) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 37) = 0;
  *(this + 152) = 1;
  *(this + 154) = 0;
  *(this + 153) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 34) = a4;
  *((uint32_t *)this + 33) = a3;
  *(this + 153) = 0;
  *(this + 154) = 0;
  sub_698F90((int)(this + 140), 125, 0);
  *((uint32_t *)this + 32) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x649EE0 sub_649EE0 —— 诅咒光环析构成员（591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_649EE0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *this = &vftbl_CNAuraMasterCurse;
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 32);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 32) = 0;
  *(this + 35) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 144) = 0;
  return sub_591190(this);
}



// ------------------------------------------------------------
// 0x649F60 CNAuraMasterCurse__vmt1C —— CNAuraMasterCurse__vmt1C 生成装配：Common/Etc/Particle/Aura/CurseAura.ptl（428F30/5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraMasterCurse__vmt1C(int *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax

  CNRDAuraMaster__vmt1C();
  if ( *(this + 32) == 0 )
  {
    v2 = operator new(0x12Cu);
    if ( v2 != nullptr )
      v3 = sub_428F30(v2, (int)"Common/Etc/Particle/Aura/CurseAura.ptl", *(this + 1));
    else
      v3 = nullptr;
    *(this + 32) = (int)v3;
  }
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 32) + 112))(*(this + 32), *(this + 1));
  return sub_5F66A0((int)this, 1);
}



// ------------------------------------------------------------
// 0x649FF0 sub_649FF0 —— 食尸鬼诅咒特效：挂 Monster/Ghoul/Particle/GhoulCurse.ptl（428F30/4600B0/698F90）
// ------------------------------------------------------------
void /*thiscall*/ sub_649FF0(int this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int *v8; // ecx
  int v9; // edx
  void *v10; // eax
  void *v11; // eax
  int v12; // [esp-Ch] [ebp-38h]
  int v13; // [esp-4h] [ebp-30h]
  uint8_t v14[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *v16; // [esp+1Ch] [ebp-10h]
  int v17; // [esp+28h] [ebp-4h]

  if ( *(uint32_t *)(this + 104) == 0 )
  {
    v2 = operator new(0x12Cu);
    v16 = v2;
    v17 = 0;
    if ( v2 != nullptr )
      v3 = sub_428F30(v2, (int)"Monster/Ghoul/Particle/GhoulCurse.ptl", *(uint32_t *)(this + 4));
    else
      v3 = nullptr;
    v17 = -1;
    *(uint32_t *)(this + 104) = v3;
  }
  v13 = *(uint32_t *)(this + 4);
  (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 104) + 112))(*(uint32_t *)(this + 104));
  (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 104) + 12))(*(uint32_t *)(this + 104));
  v4 = *(uint32_t *)(this + 4);
  v5 = **(uint32_t **)(this + 104);
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 128))(v4);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 124))(v4);
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 120))(v4, v6);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v5 + 40))(*(uint32_t *)(this + 104), v7);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 104) + 92))(*(uint32_t *)(this + 104), v14);
  v8 = *(int **)(this + 4);
  v9 = *v8;
  v17 = 1;
  v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v9 + 80))(v8, 2, 0, v14);
  sub_4600B0(v10, v12, 0, v13);
  *(uint8_t *)(this + 121) = 0;
  *(uint8_t *)(this + 122) = 0;
  sub_698F90(this + 108, 1500, 0);
  v11 = Block;
  *(uint32_t *)(this + 136) = 1;
  if ( v11 != nullptr )
    j__free(v11);
}



// ------------------------------------------------------------
// 0x64A100 CNAuraMasterCurse__vmt0 —— CNAuraMasterCurse__vmt0 析构（转发 649EE0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNAuraMasterCurse__vmt0(uint32_t *Block, char a2)
{
  sub_649EE0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64A130 CNDarkDamageFromCurseAura__vmt68 —— CNDarkDamageFromCurseAura__vmt68 特效触发槽（转发 649FF0）
// ------------------------------------------------------------
void /*thiscall*/ CNDarkDamageFromCurseAura__vmt68(uint8_t *this)
{
  if ( *(this + 140) == 1 )
  {
    sub_649FF0((int)this);
    *(this + 140) = 0;
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
int /*thiscall*/ sub_64A150(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint8_t *)(this + 88) = 0;
  *(uint32_t *)(this + 124) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x64A160 sub_64A160 —— 光环基类数据 2（607260）
// ------------------------------------------------------------
char /*thiscall*/ sub_64A160(int this, int a2, int a3, int a4, char a5)
{
  *(uint32_t *)(this + 80) = a3;
  *(uint32_t *)(this + 84) = a2;
  sub_607260((uint32_t *)(this + 92), a4, -1, 1, 1);
  *(uint8_t *)(this + 88) = a5;
  return a5;
}



// ------------------------------------------------------------
// 0x64A190 CNRDAuraMaster__vmt18 —— CNRDAuraMaster__vmt18 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMaster__vmt18(int this, char a2, int a3, int a4, float a5)
{
  int v6; // eax

  v6 = *(uint32_t *)(this + 124);
  if ( v6 != 0 )
  {
    LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4));
    if ( (uint8_t)v6 == 0 )
    {
      LOBYTE(v6) = a2;
      if ( a2 != 0 )
      {
        sub_4938F0(*(uint32_t *)(this + 124));
        LOBYTE(v6) = sub_491D00(dword_79C0B0, a3, a4, a5);
      }
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x64A1E0 CNRDAuraMinion__vmt18 —— CNRDAuraMinion__vmt18 生成槽（4938F0/491D00）
// ------------------------------------------------------------
void /*thiscall*/ CNRDAuraMinion__vmt18(int *this, char a2, int a3, int a4, float a5)
{
  int v6; // edi
  int v7; // ecx
  int v8; // eax
  int v9; // eax

  v6 = *(this + 21);
  if ( v6 != 0 )
  {
    v7 = *(this + 22);
    if ( v7 != 0 && *(this + 23) != 0 && a2 != 0 )
    {
      v8 = *(this + 20);
      if ( v8 != 0 )
      {
        v9 = v8 - 1;
        if ( v9 != 0 )
        {
          if ( v9 == 1 )
          {
            sub_4938F0(*(this + 23));
            sub_491D00(dword_79C0B0, a3, a4, a5);
          }
        }
        else
        {
          sub_4938F0(v6);
          sub_491D00(dword_79C0B0, a3, a4, a5);
        }
      }
      else
      {
        sub_4938F0(v7);
        sub_491D00(dword_79C0B0, a3, a4, a5);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64A2A0 CNRDAuraMinion__vmt4 —— CNRDAuraMinion__vmt4 复位槽（41 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMinion__vmt4(int *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // ecx

  IRDAppendage__vmt4(this);
  v2 = *(this + 21);
  if ( v2 != 0 )
  {
    v3 = *(this + 22);
    if ( v3 != 0 )
    {
      v4 = *(this + 23);
      if ( v4 != 0 )
      {
        v2 = *(this + 20);
        if ( v2 != 0 || *(uint8_t *)(v3 + 170) == 0 )
        {
          if ( v2 == 2 )
          {
            LOBYTE(v2) = *(uint8_t *)(v4 + 170);
            if ( (uint8_t)v2 != 0 )
              LOBYTE(v2) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);
          }
        }
        else
        {
          *(this + 20) = 1;
        }
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x64A300 CNRDAuraMinion__vmt4C —— CNRDAuraMinion__vmt4C 槽（28 行）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMinion__vmt4C(int this, char a2)
{
  char result; // al

  result = a2;
  if ( a2 == 1 )
  {
    *(uint8_t *)(this + 52) = 1;
  }
  else if ( *(uint32_t *)(this + 84) != 0
         && *(uint32_t *)(this + 88) != 0
         && *(uint32_t *)(this + 92) != 0
         && *(uint32_t *)(this + 80) != 2 )
  {
    *(uint32_t *)(this + 80) = 2;
  }
  else
  {
    *(uint8_t *)(this + 52) = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64A350 sub_64A350 —— 受方表现转发（14 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A350(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 23) = 0;
  *(this + 22) = 0;
  *(this + 21) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x64A360 CNRDAuraMaster__vmt20 —— CNRDAuraMaster__vmt20 更新槽（41C5E0 + 52E4D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNRDAuraMaster__vmt20(uint32_t *this, uint32_t *a2)
{
  uint32_t *v3; // ecx
  uint32_t *v4; // eax
  void **v5; // edx
  uint32_t *v6; // esi
  uint32_t *result; // eax

  if ( (uint8_t)a2 == 0 )
  {
    v3 = (uint32_t *)*(this + 29);
    v4 = (uint32_t *)*v3;
    a2 = (uint32_t *)*v3;
    if ( a2 != v3 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, v4[4]);
        sub_41C5E0(&a2);
        v4 = a2;
      }
      while ( a2 != (uint32_t *)*(this + 29) );
    }
  }
  v5 = *(void ***)(*(this + 29) + 4);
  v6 = this + 28;
  sub_52E4D0(v5);
  *(uint32_t *)(v6[1] + 4) = v6[1];
  result = (uint32_t *)v6[1];
  v6[2] = 0;
  *result = result;
  *(uint32_t *)(v6[1] + 8) = v6[1];
  return result;
}



// ------------------------------------------------------------
// 0x64A3D0 sub_64A3D0 —— 召唤装配（4BE520 + 614810，117 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_64A3D0(uint8_t *this, int a2)
{
  uint32_t *v2; // ebx
  bool v3; // zf
  uint32_t *v4; // eax
  int v5; // esi
  uint32_t *v6; // eax
  int v7; // edi
  unsigned int v8; // ebx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // ecx
  int v17; // esi
  uint8_t v19[8]; // [esp+Ch] [ebp-1Ch] BYREF
  int v20; // [esp+14h] [ebp-14h] BYREF
  int v21; // [esp+18h] [ebp-10h] BYREF
  uint8_t v22[4]; // [esp+1Ch] [ebp-Ch] BYREF
  uint32_t *v23; // [esp+20h] [ebp-8h] BYREF
  char v24; // [esp+27h] [ebp-1h]

  v2 = this;
  v3 = *(this + 88) == 0;
  v23 = this;
  if ( v3 )
  {
    v4 = (uint32_t *)sub_4BE520(&v23, &a2);
    if ( *v4 == v2[29] )
    {
      v5 = a2;
      v20 = a2;
      v21 = a2;
      sub_614810(v22, &v20);
      LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v2 + 120))(v2, v5);
    }
    return (char)v4;
  }
  v6 = (uint32_t *)sub_4BE520(&v21, &a2);
  v7 = a2;
  if ( *v6 == v2[29] )
  {
    v20 = a2;
    v21 = a2;
    sub_614810(v19, &v20);
  }
  HIBYTE(a2) = 0;
  v24 = 0;
  if ( v7 == 0 )
  {
LABEL_31:
    LOBYTE(v4) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*v2 + 120))(v2, v7);
    return (char)v4;
  }
  v8 = 0;
  while ( 1 )
  {
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 700))(v7);
    v10 = *(uint32_t *)(v9 + 4);
    v11 = v10 != 0 ? (*(uint32_t *)(v9 + 8) - v10) >> 2 : 0;
    if ( (int)v8 >= v11 )
      break;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 700))(v7);
    v13 = *(uint32_t *)(v12 + 4);
    if ( v13 != 0 && v8 < (*(uint32_t *)(v12 + 8) - v13) >> 2 )
      v14 = *(uint32_t *)(v13 + 4 * v8);
    else
      v14 = 0;
    if ( *(uint32_t *)(v14 + 4) == v7
      && (v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 700))(v7), (v16 = *(uint32_t *)(v15 + 4)) != 0)
      && v8 < (*(uint32_t *)(v15 + 8) - v16) >> 2
      && (v17 = *(uint32_t *)(v16 + 4 * v8)) != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v17 + 80))(*(uint32_t *)(v16 + 4 * v8)) != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v23 + 136))(v23, v17) != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v23 + 144))(v23, v17) != 0 )
      {
        HIBYTE(a2) = 1;
        ++v8;
      }
      else
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v23 + 140))(v23, v17) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v17 + 76))(v17, 0);
          goto LABEL_27;
        }
        v24 = 1;
        ++v8;
      }
    }
    else
    {
LABEL_27:
      ++v8;
    }
  }
  LOBYTE(v4) = HIBYTE(a2);
  if ( HIBYTE(a2) == 0 )
  {
    LOBYTE(v4) = v24;
    if ( v24 == 0 )
    {
      v2 = v23;
      goto LABEL_31;
    }
  }
  return (char)v4;
}


// ------------------------------------------------------------
// 0x64A570 CNRDAuraMaster__vmt1C —— CNRDAuraMaster__vmt1C 生成装配（699000 + 607290 + 64A3D0）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMaster__vmt1C(int this)
{
  int v2; // eax
  int v3; // eax

  v2 = sub_699000(this + 8);
  sub_607290((uint8_t *)(this + 92), v2);
  v3 = *(uint32_t *)(this + 80) >> 5;
  if ( (*(uint32_t *)(this + 80) & 0x20) != 0 )
    LOBYTE(v3) = sub_64A3D0((int **)this, *(uint32_t *)(this + 4));
  return v3;
}



// ------------------------------------------------------------
// 0x64A5A0 sub_64A5A0 —— 跟随装配（4BE520 + 6148D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64A5A0(uint32_t *this, int a2)
{
  uint32_t *v3; // edi
  uint32_t *result; // eax
  uint8_t v5[4]; // [esp+8h] [ebp-4h] BYREF

  v3 = this + 28;
  result = (uint32_t *)sub_4BE520(v5, &a2);
  if ( *result != *(this + 29) )
  {
    sub_6148D0(v3, &a2);
    return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64A5E0 CNRDAuraMaster__vmt30 —— CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0）
// ------------------------------------------------------------
int /*thiscall*/ CNRDAuraMaster__vmt30(uint32_t *this, uint32_t *a2)
{
  int v2; // ebx
  uint32_t *v4; // ecx
  uint32_t *v5; // eax
  uint32_t *v6; // eax

  v2 = (int)a2;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) == 0 )
    return IRDAppendage__vmt30(this, v2);
  if ( v2 != *(this + 1) )
  {
    sub_64A5A0(this, v2);
    return IRDAppendage__vmt30(this, v2);
  }
  v4 = (uint32_t *)*(this + 29);
  v5 = (uint32_t *)*v4;
  a2 = (uint32_t *)*v4;
  if ( a2 != v4 )
  {
    do
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, v5[4]);
      sub_41C5E0(&a2);
      v5 = a2;
    }
    while ( a2 != (uint32_t *)*(this + 29) );
  }
  sub_52E4D0(*(void ***)(*(this + 29) + 4));
  *(uint32_t *)(*(this + 29) + 4) = *(this + 29);
  v6 = (uint32_t *)*(this + 29);
  *(this + 30) = 0;
  *v6 = v6;
  *(uint32_t *)(*(this + 29) + 8) = *(this + 29);
  return IRDAppendage__vmt30(this, v2);
}



// ------------------------------------------------------------
// 0x64A680 sub_64A680 —— 跟随装配 2（699000 + 6072C0 + 64A5A0/64A3D0，73 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_64A680(int this)
{
  signed int v2; // eax
  int v3; // eax
  int v4; // eax
  unsigned int v5; // edx
  int v6; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // esi
  unsigned int i; // [esp+4h] [ebp-4h]

  v2 = *(uint32_t *)(this + 80) >> 4;
  if ( (*(uint32_t *)(this + 80) & 0x10) != 0 )
  {
    v3 = sub_699000(this + 8);
    LOBYTE(v2) = sub_6072C0((uint8_t *)(this + 92), v3);
    if ( (uint8_t)v2 != 0 )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 80))(*(uint32_t *)(this + 4));
      v5 = 0;
      v6 = v4;
      for ( i = 0; ; v5 = i )
      {
        while ( 1 )
        {
          v7 = *(uint32_t *)(v6 + 120);
          if ( v7 != 0 )
            v2 = (*(uint32_t *)(v6 + 124) - v7) >> 2;
          else
            v2 = 0;
          if ( (int)v5 >= v2 )
            return v2;
          v8 = *(uint32_t *)(v6 + 120);
          if ( v8 != 0 && v5 < (*(uint32_t *)(v6 + 124) - v8) >> 2 )
            v9 = *(uint32_t *)(v8 + 4 * v5);
          else
            v9 = 0;
          v10 = __RTDynamicCast(
                  v9,
                  0,
                  &IRDCollisionObject `RTTI Type Descriptor',
                  &IRDActiveObject `RTTI Type Descriptor',
                  0);
          v11 = v10;
          if ( v10 != 0 )
            break;
LABEL_20:
          v5 = ++i;
        }
        if ( *(uint32_t *)(this + 4) == v10 && (*(uint32_t *)(this + 80) & 2) != 0
          || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 132))(this, v10) == 0
          || (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t))(**(uint32_t **)(this + 4) + 8))(*(uint32_t *)(this + 4), v11, 0) > *(uint32_t *)(this + 84)
          || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 724))(v11) != 0 )
        {
          sub_64A5A0((uint32_t *)this, v11);
          goto LABEL_20;
        }
        sub_64A3D0((int **)this, v11);
        ++i;
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x64A790 CNRDAuraMaster__vmt4 —— CNRDAuraMaster__vmt4 析构复位（转发 64A680）
// ------------------------------------------------------------
char /*thiscall*/ CNRDAuraMaster__vmt4(int this)
{
  IRDAppendage__vmt4((int *)this);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 724))(*(uint32_t *)(this + 4)) != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 76))(this, 0);
  return sub_64A680(this);
}



// ------------------------------------------------------------
// 0x64A7C0 sub_64A7C0 —— 受击前置（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A7C0(void ***this)
{
  int v2; // esi
  int result; // eax

  v2 = (int)*(this + 31);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 31));
    result = sub_657740(v2, 228);
  }
  *(this + 31) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x64A7F0 CNRDAuraMaster__vmt80 —— CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0/431860）
// ------------------------------------------------------------
int /*thiscall*/ CNRDAuraMaster__vmt80(void ***this, const char *a2)
{
  int v3; // edi
  int v4; // eax
  int result; // eax

  v3 = (int)*(this + 31);
  if ( v3 != 0 )
  {
    sub_42AF90(*(this + 31));
    sub_657740(v3, 228);
  }
  *(this + 31) = nullptr;
  v4 = sub_42FCB0(228);
  if ( v4 != 0 )
    result = sub_431860(v4, a2, 1);
  else
    result = 0;
  *(this + 31) = (void **)result;
  return result;
}



// ------------------------------------------------------------
// 0x64A880 sub_64A880 —— 受击表现（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A880(void ***this)
{
  int v2; // edi
  int result; // eax
  void **v4; // edi
  void **v5; // edi

  v2 = (int)*(this + 21);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 21));
    result = sub_657740(v2, 228);
  }
  v4 = *(this + 22);
  *(this + 21) = nullptr;
  if ( v4 != nullptr )
  {
    sub_42AF90(v4);
    result = sub_657740(v4, 228);
  }
  v5 = *(this + 23);
  *(this + 22) = nullptr;
  if ( v5 != nullptr )
  {
    sub_42AF90(v5);
    result = sub_657740(v5, 228);
  }
  *(this + 23) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x64A900 CNRDAuraMinion__vmt30 —— CNRDAuraMinion__vmt30 更新槽（转发 64A880）
// ------------------------------------------------------------
int /*thiscall*/ CNRDAuraMinion__vmt30(int this, int a2)
{
  if ( a2 == *(uint32_t *)(this + 4) )
    sub_64A880((void ***)this);
  return IRDAppendage__vmt30((uint32_t *)this, a2);
}



// ============================================================
// 【分区 12】挑衅人偶光环 CNProvocationDollAura（0x64A930-0x64AEC0）
// 64AD30 装载 Character/Mage/Effect/Animation/ProvocationDollSymbol1/2.ani +
// ProvocationDollAreaStart/Loop.ani；vmt78=嘲讽生效（433F60/4B3DF0/60FA60）。
// ============================================================
// ------------------------------------------------------------
// 0x64A930 sub_64A930 —— 挑衅查询（16 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64A930(uint32_t *this)
{
  *(this + 32) = 0;
  *(this + 33) = 1065353216;
  *(this + 34) = 0;
  *(this + 36) = 0;
  *(this + 35) = 0;
  *(this + 37) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x64A960 CNProvocationDollAura__vmt1C —— CNProvocationDollAura__vmt1C 生成装配（4926A0/4922F0 嘲讽目标）
// ------------------------------------------------------------
int /*thiscall*/ CNProvocationDollAura__vmt1C(int *this)
{
  double v2; // st7
  int *v3; // esi
  int v4; // ebx
  double v5; // st7
  int result; // eax
  float v7; // [esp+Ch] [ebp-4h]

  CNRDAuraMaster__vmt1C((int)this);
  v2 = (double)*(this + 21);
  v3 = this + 36;
  v4 = 2;
  v5 = v2 * 0.0062500001;
  v7 = v5 / *((float *)v3 - 3);
  *((float *)v3 - 3) = v5;
  do
  {
    sub_4926A0(*(v3 - 2));
    sub_4926A0(*v3);
    sub_4922F0(v7);
    result = sub_4922F0(v7);
    ++v3;
    --v4;
  }
  while ( v4 != 0 );
  return result;
}



// ------------------------------------------------------------
// 0x64A9C0 CNProvocationDollAura__vmt84 —— CNProvocationDollAura__vmt84 受击事件槽（4E4630）
// ------------------------------------------------------------
char /*stdcall*/ CNProvocationDollAura__vmt84(int a1)
{
  char result; // al

  result = sub_4E4630(a1);
  if ( result != 0 )
    return (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 724))(a1) == 0;
  return result;
}



// ------------------------------------------------------------
// 0x64A9F0 CNProvocationDollAura__vmt94 —— CNProvocationDollAura__vmt94 槽（12 行）
// ------------------------------------------------------------
int /*thiscall*/ CNProvocationDollAura__vmt94(uint32_t *this, int a2, int a3)
{
  *(this + 21) = a2;
  *(this + 32) = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x64AA10 CNProvocationDollAura__vmt18 —— CNProvocationDollAura__vmt18 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNProvocationDollAura__vmt18(int *this, char a2, int a3, int a4, float a5)
{
  char result; // al
  int *v7; // esi
  int i; // [esp+10h] [ebp+8h]

  CNRDAuraMaster__vmt18((int)this, a2, a3, a4, a5);
  result = a2;
  if ( a2 != 0 )
  {
    v7 = this + 34;
    for ( i = 2; i != 0; --i )
    {
      sub_4938F0(*v7);
      sub_491D00(dword_79C0B0, a3, a4, 0.0);
      ++v7;
    }
    sub_4938F0(*(this + (*(uint8_t *)(*(this + 36) + 170) != 0) + 36));
    return sub_491D00(dword_79C0B0, a3, a4, 0.0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64AAB0 CNProvocationDollAura__vmt88 —— CNProvocationDollAura__vmt88 槽（10 行）
// ------------------------------------------------------------
BOOL /*stdcall*/ CNProvocationDollAura__vmt88(int a1)
{
  return *(uint32_t *)(a1 + 64) == 15;
}



// ------------------------------------------------------------
// 0x64AAD0 CNProvocationDollAura__vmt8C —— CNProvocationDollAura__vmt8C 槽（17 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNProvocationDollAura__vmt8C(uint32_t **this, int a2)
{
  int v4; // esi
  int v5; // edi

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 64))(a2) + 32) == 0 )
    return false;
  v4 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 64))(a2) + 32);
  v5 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 388))(*(this + 1));
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 388))(v4) >= v5;
}



// ------------------------------------------------------------
// 0x64AB20 CNRDAuraMaster__vmt90 —— CNRDAuraMaster__vmt90 槽（13 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNRDAuraMaster__vmt90(uint32_t *this, int a2)
{
  int v2; // esi

  v2 = *(this + 1);
  return *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 64))(a2) + 32) == v2;
}



// ------------------------------------------------------------
// 0x64AB40 CNProvocationDollAura__vmt7C —— CNProvocationDollAura__vmt7C 光环失效/转移槽（62 行）
// ------------------------------------------------------------
void /*thiscall*/ CNProvocationDollAura__vmt7C(uint32_t *this, int a2)
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
  int v11; // ecx
  int v12; // ebx
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx

  if ( a2 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v4 = *(uint32_t *)(v3 + 4);
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v7 = *(uint32_t *)(v6 + 4);
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == a2 )
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v10 = *(uint32_t *)(v9 + 4);
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )
          v11 = *(uint32_t *)(v10 + 4 * i);
        else
          v11 = 0;
        v12 = *(this + 1);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 64))(v11) + 32) == v12 )
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
          v14 = *(uint32_t *)(v13 + 4);
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
          {
            v15 = *(uint32_t **)(v14 + 4 * i);
            if ( v15 != nullptr && v15[16] == 15 )
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v15 + 76))(v15, 0);
          }
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64AC30 CNProvocationDollAura__vmt78 —— CNProvocationDollAura__vmt78 嘲讽生效（433F60/4B3DF0/60FA60，60 行）
// ------------------------------------------------------------
int /*thiscall*/ CNProvocationDollAura__vmt78(uint32_t *this, uint32_t *Block)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int result; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  int v8; // [esp+0h] [ebp-24h]
  float v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+14h] [ebp-10h]

  v9 = (float)(int)*(this + 32);
  v10 = (uint64_t)(v9 / sub_433F60((int)Block, 1));
  v3 = operator new(0x7Cu);
  if ( v3 != nullptr )
  {
    *(float *)&v8 = (float)v10;
    v4 = sub_4B3DF0(v3, 26, 0, v8, 0, 6);
  }
  else
  {
    v4 = nullptr;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int, int))(*v4 + 56))(
    v4,
    Block,
    *(this + 1),
    0,
    0,
    15,
    -1);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*Block + 40))(Block, 529);
  if ( (uint8_t)result != 0 )
  {
    result = Block[1943];
    if ( result == 0 )
    {
      v6 = operator new(0x54u);
      if ( v6 != nullptr )
        v7 = sub_60FA60(v6, 0, 0);
      else
        v7 = nullptr;
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int, int))(*v7 + 56))(
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
int /*thiscall*/ sub_64AD30(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax

  v4 = sub_42FCB0(228);
  if ( v4 != 0 )
    v5 = sub_431860(v4, "Character/Mage/Effect/Animation/ProvocationDollSymbol1.ani", 1);
  else
    v5 = 0;
  *(this + 34) = v5;
  v6 = sub_42FCB0(228);
  if ( v6 != 0 )
    v7 = sub_431860(v6, "Character/Mage/Effect/Animation/ProvocationDollSymbol2.ani", 1);
  else
    v7 = 0;
  *(this + 35) = v7;
  v8 = sub_42FCB0(228);
  if ( v8 != 0 )
    v9 = sub_431860(v8, "Character/Mage/Effect/Animation/ProvocationDollAreaStart.ani", 1);
  else
    v9 = 0;
  *(this + 36) = v9;
  v10 = sub_42FCB0(228);
  if ( v10 != 0 )
    v11 = sub_431860(v10, "Character/Mage/Effect/Animation/ProvocationDollAreaLoop.ani", 1);
  else
    v11 = 0;
  *(this + 37) = v11;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 148))(this, a2, a3);
}



// ------------------------------------------------------------
// 0x64AE50 sub_64AE50 —— 受击表现 2（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64AE50(void ***this)
{
  void ***v1; // esi
  int i; // ebx
  int v3; // edi
  int result; // eax
  void **v5; // edi
  bool v6; // zf

  v1 = this + 36;
  for ( i = 2; i != 0; --i )
  {
    v3 = (int)*(v1 - 2);
    if ( v3 != 0 )
    {
      sub_42AF90(*(v1 - 2));
      result = sub_657740(v3, 228);
    }
    v5 = *v1;
    v6 = *v1 == nullptr;
    *(v1 - 2) = nullptr;
    if ( !v6 )
    {
      sub_42AF90(v5);
      result = sub_657740(v5, 228);
    }
    *v1++ = nullptr;
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
char /*thiscall*/ j_CNRDAuraMaster__vmt1C(int this)
{
  return CNRDAuraMaster__vmt1C(this);
}



// ------------------------------------------------------------
// 0x64AED0 CNAuraMasterChilling__vmt20 —— CNAuraMasterChilling__vmt20 更新槽（10 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ CNAuraMasterChilling__vmt20(uint32_t *this, uint32_t *a2)
{
  return CNRDAuraMaster__vmt20(this, a2);
}



// ------------------------------------------------------------
// 0x64AEE0 CNAuraMasterChilling__vmt78 —— CNAuraMasterChilling__vmt78 光环生效（41A5E0/41A590 粒子挂载）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterChilling__vmt78(int this, int a2)
{
  unsigned int v3; // edi
  int v4; // edx
  unsigned int v5; // edi
  int v6; // edx
  float v8; // [esp+8h] [ebp-8h]
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+8h] [ebp-8h]
  float v11; // [esp+Ch] [ebp-4h]

  v8 = *(float *)(this + 128) - 1.0;
  v3 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 158;
  *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v3)) + v8;
  sub_41A590(v3, v4, v9);
  v11 = *(float *)(this + 128) - 1.0;
  v5 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 102;
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v5)) + v11;
  sub_41A590(v5, v6, v10);
  return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 676))(*(uint32_t *)(this + 4), 0);
}



// ------------------------------------------------------------
// 0x64AF80 CNAuraMasterChilling__vmt7C —— CNAuraMasterChilling__vmt7C 光环失效（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterChilling__vmt7C(int this, int a2)
{
  unsigned int v3; // edi
  int v4; // edx
  unsigned int v5; // edi
  int v6; // edx
  float v8; // [esp+8h] [ebp-8h]
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+8h] [ebp-8h]
  float v11; // [esp+Ch] [ebp-4h]

  v8 = *(float *)(this + 128) - 1.0;
  v3 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 158;
  *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v3)) - v8;
  sub_41A590(v3, v4, v9);
  v11 = *(float *)(this + 128) - 1.0;
  v5 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 672))(*(uint32_t *)(this + 4), 0) + 102;
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v5)) - v11;
  sub_41A590(v5, v6, v10);
  return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 676))(*(uint32_t *)(this + 4), 0);
}



// ------------------------------------------------------------
// 0x64B020 CNAuraMasterChilling__vmt24 —— CNAuraMasterChilling__vmt24 槽（4926A0）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterChilling__vmt24(int *this, int a2, int a3, int a4)
{
  float v6; // [esp+4h] [ebp-18h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1) + 308))(*(this + 1)) != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) != 0 )
  {
    v6 = (float)*(this + 33);
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)a2 + 760))(
      a2,
      1,
      LODWORD(v6),
      5,
      *(this + 1),
      0);
  }
  return sub_4926A0(*(this + 34));
}



// ------------------------------------------------------------
// 0x64B080 CNAuraMasterChilling__vmt14 —— CNAuraMasterChilling__vmt14 生成槽（4938F0/491D00）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterChilling__vmt14(int *this, int a2, int a3, int a4, float a5)
{
  int v6; // ecx
  int result; // eax

  v6 = *(this + 31);
  if ( v6 != 0 )
  {
    result = *(this + 34);
    if ( result != 0 )
    {
      sub_4938F0(v6);
      sub_491D00(dword_79C0B0, a3, a4, a5);
      sub_4938F0(*(this + 34));
      return sub_491D00(dword_79C0B0, a3, a4, a5);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x64B0F0 sub_64B0F0 —— 动画装载模板 "%s.ani"/"%sDamage.ani"（5910D0/42FCB0/431860/493400）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64B0F0(uint32_t *this, int a2, int a3, int a4, const char *a5)
{
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  char Buffer[512]; // [esp+10h] [ebp-410h] BYREF
  char v12[512]; // [esp+210h] [ebp-210h] BYREF
  int v13; // [esp+410h] [ebp-10h]
  int v14; // [esp+41Ch] [ebp-4h]

  v13 = dword_796E50;
  sub_5910D0(0, 33, 500, 0);
  v14 = 0;
  *this = &vftbl_CNAuraMasterChilling;
  *(this + 32) = a3;
  *(this + 33) = a4;
  sprintf(Buffer, "%s.ani", a5);
  sprintf(v12, "%sDamage.ani", a5);
  v6 = sub_42FCB0(228);
  LOBYTE(v14) = 1;
  if ( v6 != 0 )
    v7 = sub_431860(v6, Buffer, 1);
  else
    v7 = 0;
  LOBYTE(v14) = 0;
  *(this + 31) = v7;
  v8 = sub_42FCB0(228);
  LOBYTE(v14) = 2;
  if ( v8 != 0 )
    v9 = sub_431860(v8, v12, 1);
  else
    v9 = 0;
  LOBYTE(v14) = 0;
  *(this + 34) = v9;
  sub_493400(v9, 2);
  return this;
}



// ------------------------------------------------------------
// 0x64B210 CNAuraMasterChilling__vmt0 —— CNAuraMasterChilling__vmt0 析构（转发 64B240）
// ------------------------------------------------------------
void */*thiscall*/ CNAuraMasterChilling__vmt0(void *Block, char a2)
{
  sub_64B240();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64B240 sub_64B240 —— 冰冷光环析构成员（42AF90/42A1B0/591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_64B240(void ***this)
{
  void **v2; // edi

  *this = (void **)&vftbl_CNAuraMasterChilling;
  v2 = *(this + 34);
  if ( v2 != nullptr )
  {
    sub_42AF90(v2);
    sub_42A1B0((int)v2, 228);
  }
  *(this + 34) = nullptr;
  return sub_591190(this);
}



// ------------------------------------------------------------
// 0x64B2C0 CNAuraChangeStatusMaster__vmt84 —— CNAuraChangeStatusMaster__vmt84 受击事件槽（15 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraChangeStatusMaster__vmt84(int this, int a2)
{
  int v3; // edi

  if ( *(uint8_t *)(this + 460) == 0 && a2 == *(uint32_t *)(this + 4) )
    return false;
  v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 376))(*(uint32_t *)(this + 4));
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2) == v3;
}



// ------------------------------------------------------------
// 0x64B300 CNAuraChangeStatusMasterSpikeKing__vmt84 —— CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉刺王变体，23 行）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraChangeStatusMasterSpikeKing__vmt84(int this, int a2)
{
  int v2; // edi
  bool result; // al

  result = false;
  if ( *(uint8_t *)(this + 460) != 0 || a2 != *(uint32_t *)(this + 4) )
  {
    v2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 376))(*(uint32_t *)(this + 4));
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2) == v2
      && __RTDynamicCast(a2, 0, &IRDActiveObject `RTTI Type Descriptor', &CNSpirit `RTTI Type Descriptor', 0) != 0 )
    {
      return true;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x64B360 CNAuraChangeStatusMaster__vmt7C —— CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行）
// ------------------------------------------------------------
void /*thiscall*/ CNAuraChangeStatusMaster__vmt7C(int this, int a2)
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
  int v11; // ecx
  int v12; // esi
  int v13; // eax
  int v14; // ecx
  int v15; // ecx
  int *v16; // esi

  if ( a2 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v4 = *(uint32_t *)(v3 + 4);
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v7 = *(uint32_t *)(v6 + 4);
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == a2 )
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v10 = *(uint32_t *)(v9 + 4);
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )
          v11 = *(uint32_t *)(v10 + 4 * i);
        else
          v11 = 0;
        v12 = *(uint32_t *)(this + 4);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 64))(v11) + 32) == v12 )
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
          v14 = *(uint32_t *)(v13 + 4);
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
            v15 = *(uint32_t *)(v14 + 4 * i);
          else
            v15 = 0;
          v16 = (int *)__RTDynamicCast(
                         v15,
                         0,
                         &IRDAppendage `RTTI Type Descriptor',
                         &CNChangeStatus `RTTI Type Descriptor',
                         0);
          if ( v16 != nullptr && sub_5F8000(v16, (char *)(this + 128), *(uint32_t *)(this + 456)) != 0 )
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*v16 + 76))(v16, 0);
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64B480 sub_64B480 —— 状态变化文本（4015C0/4022F0）
// ------------------------------------------------------------
void /*thiscall*/ sub_64B480(void *this, void *Src, const char *a3)
{
  void **v4; // eax
  uint8_t v5[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+Ch] [ebp-28h] BYREF
  unsigned int v7; // [esp+20h] [ebp-14h]
  int v8; // [esp+24h] [ebp-10h]
  int v9; // [esp+30h] [ebp-4h]

  v8 = dword_796E50;
  v7 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  sub_4015C0(Src, strlen((const char *)Src));
  v9 = 0;
  sub_4022F0((std::_String_base *)v5, a3, strlen(a3));
  v4 = (void **)Block[0];
  if ( v7 < 0x10 )
    v4 = Block;
  (*(void (/*thiscall*/ **)(void *, void **))(*(uint32_t *)this + 128))(this, v4);
  if ( v7 >= 0x10 )
    j__free(Block[0]);
}



// ------------------------------------------------------------
// 0x64B540 CNAuraChangeStatusMaster__vmt78 —— CNAuraChangeStatusMaster__vmt78 变化生效（5F8000/5101B0，94 行）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraChangeStatusMaster__vmt78(int this, void *Block)
{
  uint32_t *v2; // edi
  unsigned int i; // ebx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // edi
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int *v17; // eax
  char result; // al
  uint32_t *v19; // eax
  uint32_t *v20; // eax

  v2 = (uint32_t *)this;
  if ( Block != nullptr )
  {
    for ( i = 0; ; ++i )
    {
      v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);
      v5 = *(uint32_t *)(v4 + 4);
      v6 = v5 != 0 ? (*(uint32_t *)(v4 + 8) - v5) >> 2 : 0;
      if ( (int)i >= v6 )
        break;
      v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);
      v8 = *(uint32_t *)(v7 + 4);
      if ( v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2 )
        v9 = *(uint32_t *)(v8 + 4 * i);
      else
        v9 = 0;
      if ( *(void **)(v9 + 4) == Block )
      {
        v10 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);
        v11 = *(uint32_t *)(v10 + 4);
        if ( v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2 )
          v12 = *(uint32_t *)(v11 + 4 * i);
        else
          v12 = 0;
        v13 = v2[1];
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 64))(v12) + 32) == v13 )
        {
          v14 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);
          v15 = *(uint32_t *)(v14 + 4);
          if ( v15 != 0 && i < (*(uint32_t *)(v14 + 8) - v15) >> 2 )
            v16 = *(uint32_t *)(v15 + 4 * i);
          else
            v16 = 0;
          v17 = (int *)__RTDynamicCast(
                         v16,
                         0,
                         &IRDAppendage `RTTI Type Descriptor',
                         &CNChangeStatus `RTTI Type Descriptor',
                         0);
          if ( v17 != nullptr )
          {
            result = sub_5F8000(v17, (char *)(this + 128), *(uint32_t *)(this + 456));
            if ( result != 0 )
              return result;
            v2 = (uint32_t *)this;
            break;
          }
        }
        v2 = (uint32_t *)this;
      }
    }
  }
  v19 = operator new(0x7Cu);
  if ( v19 != nullptr )
    v20 = sub_5101B0(v19, (int)(v2 + 32), v2[114], v2[113], 1);
  else
    v20 = nullptr;
  return (*(int (/*thiscall*/ **)(uint32_t *, void *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v20 + 56))(
           v20,
           Block,
           v2[1],
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
uint32_t */*thiscall*/ sub_64B6C0(uint32_t *this, int a2, const void *a3, int a4, int a5, char a6, int a7)
{
  sub_5910D0(a2, 17, 500, a7);
  *this = &vftbl_CNAuraChangeStatusMaster;
  qmemcpy(this + 32, a3, 4 * ((unsigned int)(12 * a4) >> 2));
  *(this + 114) = a4;
  *(this + 113) = a5;
  *((uint8_t *)this + 460) = a6;
  return this;
}



// ------------------------------------------------------------
// 0x64B730 CNAuraMasterFlame__vmt68 —— CNAuraMasterFlame__vmt68 特效触发槽（10 行）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterFlame__vmt68(uint32_t **this)
{
  return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 34) + 12))(*(this + 34), 0);
}



// ------------------------------------------------------------
// 0x64B740 sub_64B740 —— 火焰灼烧事件：SIZZLE_HIT（605840 目标 + 4E4A50 伤害，64 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64B740(int this)
{
  int result; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // edi
  int v8; // ebx
  int v9; // ebx
  int v10; // eax
  int16_t *v11; // eax
  float v12; // [esp+4h] [ebp-20h] BYREF
  float v13; // [esp+8h] [ebp-1Ch]
  float v14; // [esp+Ch] [ebp-18h]
  int v15; // [esp+10h] [ebp-14h]
  int v16; // [esp+14h] [ebp-10h]
  int v17; // [esp+18h] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-8h]
  int v19; // [esp+20h] [ebp-4h] BYREF

  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 100) + 12))(*(uint32_t *)(this + 100), 0);
  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));
  if ( (uint8_t)result != 0 )
  {
    v3 = *(uint32_t *)(this + 4);
    v12 = 0.0;
    v13 = 0.0;
    v14 = 0.0;
    v15 = 0;
    v16 = 0;
    v17 = 0;
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 120))(v3);
    v5 = *(uint32_t *)(this + 4);
    v18 = v4;
    v12 = (float)v4;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 124))(v5);
    v7 = *(uint32_t *)(this + 4);
    v18 = v6;
    v13 = (float)v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 192))(v7) / 2;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 128))(v7) + v8;
    v10 = *(uint32_t *)(this + 4);
    v18 = v9;
    v14 = (float)v9;
    v19 = 0;
    v11 = sub_605840(&v19, v10, (int *)&v12, 0);
    sub_4E4A50(*(uint32_t *)(this + 36), 42004, *(uint32_t *)(this + 96), 0, 0, 0, 1, 0, v19, v11);
    result = (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 212))(
               *(uint32_t *)(this + 4),
               "SIZZLE_HIT",
               -1,
               0,
               0);
    *(uint32_t *)(this + 72) = *(uint32_t *)(this + 104);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64B850 sub_64B850 —— 火焰受方装配（4B1030 + 64A350）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64B850(uint32_t *this, int a2, int a3)
{
  sub_4B1030(this);
  *this = &vftbl_CNRDAuraMinion;
  sub_64A350(this);
  *this = &vftbl_CNFlameDamageFromFlameAura;
  *(this + 24) = a2;
  *(this + 26) = a3;
  *(this + 18) = (uint64_t)((double)a3 * 0.5);
  return this;
}



// ------------------------------------------------------------
// 0x64B8C0 CNFlameDamageFromFlameAura__vmt0 —— CNFlameDamageFromFlameAura__vmt0 析构（转发 64B8F0）
// ------------------------------------------------------------
void */*thiscall*/ CNFlameDamageFromFlameAura__vmt0(void *Block, char a2)
{
  sub_64B8F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64B8F0 sub_64B8F0 —— 火焰受方初始化（649300 系）
// ------------------------------------------------------------
int /*thiscall*/ sub_64B8F0(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *this = &vftbl_CNFlameDamageFromFlameAura;
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 25);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 25) = 0;
  return sub_649300((int)this);
}



// ------------------------------------------------------------
// 0x64B950 CNAuraMasterFlame__vmt78 —— CNAuraMasterFlame__vmt78 光环生效：事件标签复用 AURA_ICE_SET（转发 64B850）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterFlame__vmt78(int *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  v3 = operator new(0x6Cu);
  if ( v3 != nullptr )
    v4 = sub_64B850(v3, *(this + 32), *(this + 33));
  else
    v4 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v4 + 56))(
    v4,
    a2,
    *(this + 1),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a2 + 212))(
           a2,
           "AURA_ICE_SET",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64B9F0 CNAuraMasterFlame__vmt7C —— CNAuraMasterFlame__vmt7C 光环失效槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterFlame__vmt7C(int a1)
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
  int v11; // eax

  if ( a1 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v3 = *(uint32_t *)(v2 + 4);
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v6 = *(uint32_t *)(v5 + 4);
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == a1 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
        v9 = *(uint32_t *)(v8 + 4);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNFlameDamageFromFlameAura `RTTI Type Descriptor',
                0);
        if ( v11 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 76))(v11, 0);
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64BAA0 CNAuraMasterFlame__vmt4 —— CNAuraMasterFlame__vmt4 复位（4600B0）
// ------------------------------------------------------------
void /*thiscall*/ CNAuraMasterFlame__vmt4(int this)
{
  int v2; // edi
  int v3; // ebx
  int *v4; // ecx
  int v5; // edx
  void *v6; // eax
  int v7; // [esp-Ch] [ebp-34h]
  int v8; // [esp-8h] [ebp-30h]
  int v9; // [esp-4h] [ebp-2Ch]
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+24h] [ebp-4h]

  CNRDAuraMaster__vmt4(this);
  v2 = *(uint32_t *)(this + 4);
  v3 = **(uint32_t **)(this + 136);
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 128))(v2);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 124))(v2);
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
  (*(void (/*thiscall*/ **)(uint32_t))(v3 + 40))(*(uint32_t *)(this + 136));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 136) + 92))(*(uint32_t *)(this + 136), v10);
  v4 = *(int **)(this + 4);
  v5 = *v4;
  v12 = 0;
  v6 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v5 + 80))(v4, 2, 0, v10);
  sub_4600B0(v6, v7, v8, v9);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x64BB50 CNFlameDamageFromFlameAura__vmt4 —— CNFlameDamageFromFlameAura__vmt4 伤害（4600B0）
// ------------------------------------------------------------
void /*thiscall*/ CNFlameDamageFromFlameAura__vmt4(int this)
{
  int v2; // edi
  int v3; // ebx
  int *v4; // ecx
  int v5; // edx
  void *v6; // eax
  int v7; // [esp-Ch] [ebp-34h]
  int v8; // [esp-8h] [ebp-30h]
  int v9; // [esp-4h] [ebp-2Ch]
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+24h] [ebp-4h]

  CNRDAuraMinion__vmt4((int *)this);
  v2 = *(uint32_t *)(this + 4);
  v3 = **(uint32_t **)(this + 100);
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 128))(v2);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 124))(v2);
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
  (*(void (/*thiscall*/ **)(uint32_t))(v3 + 40))(*(uint32_t *)(this + 100));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 100) + 92))(*(uint32_t *)(this + 100), v10);
  v4 = *(int **)(this + 4);
  v5 = *v4;
  v12 = 0;
  v6 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v5 + 80))(v4, 2, 0, v10);
  sub_4600B0(v6, v7, v8, v9);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x64BBF0 sub_64BBF0 —— 火焰动画查询 2（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64BBF0(uint32_t *this, int a2, int a3, int a4)
{
  sub_5910D0(a2, 18, 500, 0);
  *(this + 33) = a3;
  *(this + 18) = a3;
  *this = &vftbl_CNAuraMasterFlame;
  *(this + 32) = a4;
  return this;
}



// ------------------------------------------------------------
// 0x64BC30 CNAuraMasterFlame__vmt0 —— CNAuraMasterFlame__vmt0 析构（转发 64BC60）
// ------------------------------------------------------------
void */*thiscall*/ CNAuraMasterFlame__vmt0(void *Block, char a2)
{
  sub_64BC60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64BC60 sub_64BC60 —— 火焰光环析构成员（591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_64BC60(uint32_t *this)
{
  void (/*thiscall*/ ***v2)(uint32_t, int); // ecx

  *this = &vftbl_CNAuraMasterFlame;
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 34);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 34) = 0;
  return sub_591190(this);
}



// ------------------------------------------------------------
// 0x64BCD0 CNAuraMasterFlame__vmt1C —— CNAuraMasterFlame__vmt1C 生成装配：Character/Fighter/Effect/Particle/NenMaster.ptl（气功师念气，428F30/5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraMasterFlame__vmt1C(int *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int v4; // ecx

  CNRDAuraMaster__vmt1C((int)this);
  v2 = operator new(0x12Cu);
  if ( v2 != nullptr )
    v3 = sub_428F30(v2, (int)"Character/Fighter/Effect/Particle/NenMaster.ptl", *(this + 1));
  else
    v3 = nullptr;
  v4 = *(this + 1);
  *(this + 34) = (int)v3;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*v3 + 112))(v3, v4);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 34) + 12))(*(this + 34), 0);
  return sub_5F66A0((int)this, 1);
}



// ------------------------------------------------------------
// 0x64BD60 CNFlameDamageFromFlameAura__vmt1C —— CNFlameDamageFromFlameAura__vmt1C 生成装配：NenMaster.ptl（428F30/5F66A0）
// ------------------------------------------------------------
char /*thiscall*/ CNFlameDamageFromFlameAura__vmt1C(int *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  int v4; // ecx

  v2 = operator new(0x12Cu);
  if ( v2 != nullptr )
    v3 = sub_428F30(v2, (int)"Character/Fighter/Effect/Particle/NenMaster.ptl", *(this + 1));
  else
    v3 = nullptr;
  v4 = *(this + 1);
  *(this + 25) = (int)v3;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*v3 + 112))(v3, v4);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 25) + 12))(*(this + 25), 0);
  return sub_5F66A0((int)this, 1);
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
char /*userpurge*/ sub_64BDF0@<al>(int a1@<ecx>, int a2@<edi>, uint32_t *a3, int a4)
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
  int v23; // ecx
  int v24; // eax
  int v25; // edx
  uint32_t *v26; // edi
  int v27; // ebx
  int v28; // ebx
  int v29; // eax
  int v30; // ebx
  int v31; // eax
  int v32; // eax
  int v33; // edi
  int v34; // eax
  int v35; // ebx
  int v36; // eax
  int v37; // ebx
  int v38; // eax
  bool v39; // cc
  int v40; // eax
  int v41; // et2
  int v42; // eax
  int v45; // [esp+0h] [ebp-18h]
  int v46; // [esp+4h] [ebp-14h]
  int v47; // [esp+8h] [ebp-10h]
  int v48; // [esp+Ch] [ebp-Ch]
  int v49; // [esp+10h] [ebp-8h]
  int v50; // [esp+14h] [ebp-4h]
  unsigned int v51; // [esp+20h] [ebp+8h]
  char v52; // [esp+27h] [ebp+Fh]

  LOBYTE(v4) = *(uint8_t *)(a1 + 5);
  v46 = a1;
  if ( (uint8_t)v4 != 0 )
  {
    *(uint8_t *)(a1 + 4) = 0;
    if ( a4 != 0 )
    {
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a4 + 576))(a4);
      v47 = v4;
      if ( v4 != 0 )
      {
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3);
        v7 = *(uint32_t *)(v6 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3) + 48);
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*a3 + 672))(a3, 3);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3);
        v10 = (uint64_t)sub_4049C0(800.0, 1200.0, *v8 - *(uint32_t *)(v9 + 48), v7);
        HIDWORD(v10) = *a3;
        v48 = v10;
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(HIDWORD(v10) + 1032))(a3);
        v12 = *(uint32_t *)(v11 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3) + 48);
        v13 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*a3 + 672))(a3, 3);
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 1032))(a3);
        v15 = (uint64_t)sub_4049C0(3.0, 6.0, *v13 - *(uint32_t *)(v14 + 48), v12);
        HIDWORD(v15) = *a3;
        v49 = v15;
        if ( *(int *)(*(int (/*thiscall*/ **)(uint32_t *))(HIDWORD(v15) + 340))(a3) >= 5
          && *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 340))(a3) != 63 )
        {
          v49 = 6;
        }
        v16 = 0;
        v52 = 1;
        v50 = 0;
        while ( 1 )
        {
          v51 = v16;
          v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 80))(a3);
          v18 = *(uint32_t *)(v17 + 8);
          v19 = v17 + 4;
          v20 = v18 != 0 ? (*(uint32_t *)(v19 + 8) - v18) >> 2 : 0;
          if ( (int)v16 >= v20 )
            break;
          v21 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a3 + 80))(a3, a2);
          v22 = *(uint32_t *)(v21 + 8);
          if ( v22 != 0 && v16 < (*(uint32_t *)(v21 + 12) - v22) >> 2 )
            v23 = *(uint32_t *)(v22 + 4 * v16);
          else
            v23 = 0;
          a2 = 529;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v23 + 40))(v23) != 0 )
          {
            v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 80))(a3);
            v25 = *(uint32_t *)(v24 + 8);
            if ( v25 != 0 && v16 < (*(uint32_t *)(v24 + 12) - v25) >> 2 )
              v26 = *(uint32_t **)(v25 + 4 * v16);
            else
              v26 = nullptr;
            if ( v26[1943] != 3 )
            {
              v27 = (*(int (/*thiscall*/ **)(uint32_t *))(*a3 + 376))(a3);
              if ( v27 == (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 376))(v26)
                && a3 != v26
                && (uint8_t)sub_4DAB60(19) != 0
                && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, uint32_t))(*a3 + 8))(a3, v26, 0) <= v48
                && (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 304))(v26) != 0 )
              {
                (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
                v28 = *(uint32_t *)dword_8F8520;
                v29 = (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 48))(v26);
                (*(void (/*thiscall*/ **)(int, int))(v28 + 36))(dword_8F8520, v29);
                v30 = *(uint32_t *)dword_8F8520;
                v31 = (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 52))(v26);
                (*(void (/*thiscall*/ **)(int, int))(v30 + 36))(dword_8F8520, v31);
                v32 = (*(int (/*thiscall*/ **)(uint32_t *))(*v26 + 304))(v26);
                v33 = *(uint32_t *)dword_8F8520;
                v34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v32 + 52))(v32);
                (*(void (/*thiscall*/ **)(int, int))(v33 + 36))(dword_8F8520, v34);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 11);
                v35 = *(uint32_t *)dword_8F8520;
                v36 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v47 + 48))(v47);
                (*(void (/*thiscall*/ **)(int, int))(v35 + 36))(dword_8F8520, v36);
                v37 = *(uint32_t *)dword_8F8520;
                v38 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v47 + 52))(v47);
                (*(void (/*thiscall*/ **)(int, int))(v37 + 36))(dword_8F8520, v38);
                (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
                v39 = v50 + 1 <= v49;
                v52 = 0;
                ++v50;
                if ( !v39 )
                  break;
              }
              v16 = v51;
            }
          }
          ++v16;
        }
        v4 = a3[1909];
        if ( v4 != 0 )
        {
          LOBYTE(v4) = v52;
          if ( v52 != 0 && a3[1787] != 6 )
          {
            v40 = rand();
            v41 = v40 % 100;
            v4 = v40 / 100;
            if ( v41 < 50 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*a3 + 1140))(a3, -1, -1);
              *(uint8_t *)(v46 + 4) = 1;
              v45 = 0;
              v46 = 1;
              v42 = rand() % 2;
              LOBYTE(v4) = sub_4DB200(24, *(&v45 + v42));
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
int /*thiscall*/ CNAuraMasterBattle__vmt1C(void *this)
{
  CNRDAuraMaster__vmt1C((int)this);
  return (*(int (/*thiscall*/ **)(void *, const char *))(*(uint32_t *)this + 128))(
           this,
           "Common/Etc/Animation/Aura/BattleAuraMaster.ani");
}



// ------------------------------------------------------------
// 0x64C160 CNAttackUpFromBattleAura__vmtC —— CNAttackUpFromBattleAura__vmtC 打开槽（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNAttackUpFromBattleAura__vmtC(uint32_t *this, int a2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // edx
  int v6; // esi
  int v7; // eax
  int v8; // edx

  v3 = *(this + 24);
  v4 = sub_41A5E0(a2 + 1306);
  sub_41A590(a2 + 1306, v5, v3 + v4);
  v6 = *(this + 24);
  v7 = sub_41A5E0(a2 + 1334);
  return sub_41A590(a2 + 1334, v8, v6 + v7);
}



// ------------------------------------------------------------
// 0x64C1B0 CNAuraMasterBattleGoblinKinol__vmt84 —— CNAuraMasterBattleGoblinKinol__vmt84 受击事件槽（哥布林奇诺尔变体）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraMasterBattleGoblinKinol__vmt84(uint32_t *this, int a2)
{
  int v3; // esi
  int v4; // edi
  bool result; // al

  result = false;
  if ( __RTDynamicCast(a2, 0, &IRDActiveObject `RTTI Type Descriptor', &CNGoblinGoblin `RTTI Type Descriptor', 0) != 0 )
  {
    v3 = *(this + 1);
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
    if ( v4 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 376))(v3) )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64C210 CNAuraMasterBattle__vmt7C —— CNAuraMasterBattle__vmt7C 光环失效槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterBattle__vmt7C(int a1)
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
  int v11; // eax

  if ( a1 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v3 = *(uint32_t *)(v2 + 4);
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v6 = *(uint32_t *)(v5 + 4);
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == a1 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
        v9 = *(uint32_t *)(v8 + 4);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNAttackUpFromBattleAura `RTTI Type Descriptor',
                0);
        if ( v11 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 76))(v11, 0);
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64C2C0 sub_64C2C0 —— 战斗动画查询（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64C2C0(uint32_t *this, int a2, int a3)
{
  sub_5910D0(a2, 18, 500, 0);
  *this = &vftbl_CNAuraMasterBattle;
  *(this + 32) = a3;
  return this;
}



// ------------------------------------------------------------
// 0x64C2F0 sub_64C2F0 —— 战斗光环随从装配：BattleAuraMinion.ani/BattleAuraMinionS.ani/BattleAuraMinionE.ani（4B1030/64A350/42FCB0/431860）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64C2F0(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax

  sub_4B1030(this);
  *this = &vftbl_CNRDAuraMinion;
  sub_64A350(this);
  *this = &vftbl_CNAttackUpFromBattleAura;
  *(this + 24) = a2;
  v3 = sub_42FCB0(228);
  if ( v3 != 0 )
    v4 = sub_431860(v3, "Common/Etc/Animation/Aura/BattleAuraMinion.ani", 1);
  else
    v4 = 0;
  *(this + 21) = v4;
  v5 = sub_42FCB0(228);
  if ( v5 != 0 )
    v6 = sub_431860(v5, "Common/Etc/Animation/Aura/BattleAuraMinionS.ani", 1);
  else
    v6 = 0;
  *(this + 22) = v6;
  v7 = sub_42FCB0(228);
  if ( v7 != 0 )
    v8 = sub_431860(v7, "Common/Etc/Animation/Aura/BattleAuraMinionE.ani", 1);
  else
    v8 = 0;
  *(this + 23) = v8;
  return this;
}



// ------------------------------------------------------------
// 0x64C3E0 CNAttackUpFromBattleAura__vmt0 —— CNAttackUpFromBattleAura__vmt0 析构（转发 64C410）
// ------------------------------------------------------------
void */*thiscall*/ CNAttackUpFromBattleAura__vmt0(void *Block, char a2)
{
  sub_64C410();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64C410 sub_64C410 —— 攻击上升受方初始化（649300 系）
// ------------------------------------------------------------
int /*thiscall*/ sub_64C410(int this)
{
  *(uint32_t *)this = &vftbl_CNAttackUpFromBattleAura;
  return sub_649300(this);
}



// ------------------------------------------------------------
// 0x64C420 CNAuraMasterBattle__vmt78 —— CNAuraMasterBattle__vmt78 光环生效：AURA_POWER_SET 事件（转发 64C2F0）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterBattle__vmt78(int *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  v3 = operator new(0x64u);
  if ( v3 != nullptr )
    v4 = sub_64C2F0(v3, *(this + 32));
  else
    v4 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v4 + 56))(
    v4,
    a2,
    *(this + 1),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a2 + 212))(
           a2,
           "AURA_POWER_SET",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64C4B0 CNATDFSPEEDUpFromAura__vmtC —— CNATDFSPEEDUpFromAura__vmtC 打开槽（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNATDFSPEEDUpFromAura__vmtC(float *this, int a2)
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v13; // [esp+Ch] [ebp-4h]
  float v14; // [esp+Ch] [ebp-4h]
  float v15; // [esp+Ch] [ebp-4h]
  int v16; // [esp+18h] [ebp+8h]
  int v17; // [esp+18h] [ebp+8h]
  int v18; // [esp+18h] [ebp+8h]
  int v19; // [esp+18h] [ebp+8h]

  v13 = (uint64_t)*(this + 24);
  v4 = sub_41A5E0(a2 + 1306);
  sub_41A590(a2 + 1306, v5, v13 + v4);
  v16 = (uint64_t)*(this + 24);
  v6 = sub_41A5E0(a2 + 1334);
  sub_41A590(a2 + 1334, v16, v16 + v6);
  v17 = (uint64_t)*(this + 25);
  v7 = sub_41A5E0(a2 + 1320);
  sub_41A590(a2 + 1320, v8, v17 + v7);
  v14 = *(this + 26);
  *(float *)&v18 = COERCE_FLOAT(sub_41A5E0(a2 + 830)) + v14;
  sub_41A590(a2 + 830, v9, v18);
  v15 = *(this + 27);
  *(float *)&v19 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v15;
  sub_41A590(a2 + 858, v19, v19);
  v10 = sub_41A5E0(a2 + 760);
  return sub_41A590(a2 + 760, v11, v10 + 32);
}



// ------------------------------------------------------------
// 0x64C5A0 CNAuraMasterATDFSPEEDUpFather__vmt84 —— CNAuraMasterATDFSPEEDUpFather__vmt84 受击事件槽（父王变体）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraMasterATDFSPEEDUpFather__vmt84(uint32_t **this, int a2)
{
  int v3; // edi
  bool result; // al

  result = false;
  if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 340))(a2) == 260
    || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 340))(a2) == 264 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 376))(*(this + 1));
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2) == v3 )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64C600 CNAuraMasterATDFSPEEDUp_KingGalok__vmt84 —— CNAuraMasterATDFSPEEDUp_KingGalok__vmt84 受击事件槽（王加洛克变体）
// ------------------------------------------------------------
bool /*thiscall*/ CNAuraMasterATDFSPEEDUp_KingGalok__vmt84(uint32_t *this, uint32_t *a2)
{
  uint32_t *v2; // edx
  uint32_t *v3; // eax
  int v4; // esi
  int v5; // edi

  v2 = (uint32_t *)a2[84];
  v3 = (uint32_t *)a2[83];
  if ( v3 == v2 )
    return false;
  do
  {
    if ( *v3 == 19 )
      break;
    ++v3;
  }
  while ( v3 != v2 );
  if ( v3 == v2 )
    return false;
  v4 = *(this + 1);
  v5 = (*(int (**)(void))(*a2 + 376))();
  return v5 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 376))(v4);
}



// ------------------------------------------------------------
// 0x64C660 CNAuraMasterATDFSPEEDUp__vmt7C —— CNAuraMasterATDFSPEEDUp__vmt7C 光环失效槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterATDFSPEEDUp__vmt7C(int a1)
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
  int v11; // eax

  if ( a1 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v3 = *(uint32_t *)(v2 + 4);
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v6 = *(uint32_t *)(v5 + 4);
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == a1 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
        v9 = *(uint32_t *)(v8 + 4);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNATDFSPEEDUpFromAura `RTTI Type Descriptor',
                0);
        if ( v11 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 76))(v11, 0);
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64C710 sub_64C710 —— 战斗动画查询 2（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64C710(uint32_t *this, int a2, int a3, int a4, int a5, int a6)
{
  sub_5910D0(a2, 18, 500, 0);
  *(this + 32) = a3;
  *(this + 34) = a5;
  *this = &vftbl_CNAuraMasterATDFSPEEDUp;
  *(this + 33) = a4;
  *(this + 35) = a6;
  return this;
}



// ------------------------------------------------------------
// 0x64C760 sub_64C760 —— ATDF/SPEED 随从装配：BattleAuraMinion/S/E.ani（4B1030/64A350/42FCB0/431860）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64C760(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax

  sub_4B1030(this);
  *this = &vftbl_CNRDAuraMinion;
  sub_64A350(this);
  *(this + 24) = a2;
  *this = &vftbl_CNATDFSPEEDUpFromAura;
  *(this + 25) = a3;
  *(this + 26) = a4;
  *(this + 27) = a5;
  v6 = sub_42FCB0(228);
  if ( v6 != 0 )
    v7 = sub_431860(v6, "Common/Etc/Animation/Aura/BattleAuraMinion.ani", 1);
  else
    v7 = 0;
  *(this + 21) = v7;
  v8 = sub_42FCB0(228);
  if ( v8 != 0 )
    v9 = sub_431860(v8, "Common/Etc/Animation/Aura/BattleAuraMinionS.ani", 1);
  else
    v9 = 0;
  *(this + 22) = v9;
  v10 = sub_42FCB0(228);
  if ( v10 != 0 )
    v11 = sub_431860(v10, "Common/Etc/Animation/Aura/BattleAuraMinionE.ani", 1);
  else
    v11 = 0;
  *(this + 23) = v11;
  return this;
}



// ------------------------------------------------------------
// 0x64C860 CNATDFSPEEDUpFromAura__vmt0 —— CNATDFSPEEDUpFromAura__vmt0 析构（转发 64C890）
// ------------------------------------------------------------
void */*thiscall*/ CNATDFSPEEDUpFromAura__vmt0(void *Block, char a2)
{
  sub_64C890();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64C890 sub_64C890 —— ATDF 受方初始化（649300 系）
// ------------------------------------------------------------
int /*thiscall*/ sub_64C890(int this)
{
  *(uint32_t *)this = &vftbl_CNATDFSPEEDUpFromAura;
  return sub_649300(this);
}



// ------------------------------------------------------------
// 0x64C8A0 CNAuraMasterATDFSPEEDUp__vmt78 —— CNAuraMasterATDFSPEEDUp__vmt78 光环生效：AURA_POWER_SET 事件（76 行转发 64C760）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterATDFSPEEDUp__vmt78(int *this, void *Block)
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
  uint32_t *v14; // eax
  uint32_t *v15; // eax

  if ( Block != nullptr )
  {
    for ( i = 0; ; ++i )
    {
      v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);
      v5 = *(uint32_t *)(v4 + 4);
      v6 = v5 != 0 ? (*(uint32_t *)(v4 + 8) - v5) >> 2 : 0;
      if ( (int)i >= v6 )
        break;
      v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);
      v8 = *(uint32_t *)(v7 + 4);
      if ( v8 != 0 && i < (*(uint32_t *)(v7 + 8) - v8) >> 2 )
        v9 = *(uint32_t *)(v8 + 4 * i);
      else
        v9 = 0;
      if ( *(void **)(v9 + 4) == Block )
      {
        v10 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)Block + 700))(Block);
        v11 = *(uint32_t *)(v10 + 4);
        if ( v11 != 0 && i < (*(uint32_t *)(v10 + 8) - v11) >> 2 )
          v12 = *(uint32_t *)(v11 + 4 * i);
        else
          v12 = 0;
        result = __RTDynamicCast(
                   v12,
                   0,
                   &IRDAppendage `RTTI Type Descriptor',
                   &CNATDFSPEEDUpFromAura `RTTI Type Descriptor',
                   0);
        if ( result != 0 )
          return result;
      }
    }
  }
  v14 = operator new(0x70u);
  if ( v14 != nullptr )
    v15 = sub_64C760(v14, *(this + 32), *(this + 33), *(this + 34), *(this + 35));
  else
    v15 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, void *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v15 + 56))(
    v15,
    Block,
    *(this + 1),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)Block + 212))(
           Block,
           "AURA_POWER_SET",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64C9F0 sub_64C9F0 —— 战斗光环查询（15 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64C9F0(int this)
{
  *(uint8_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 3;
  *(uint32_t *)(this + 88) = 0;
  *(uint8_t *)(this + 92) = 1;
  *(uint32_t *)(this + 96) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x64CA10 sub_64CA10 —— 战斗光环查询 2（15 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_64CA10(int this, char a2, int a3, int a4, int a5, char a6)
{
  *(uint8_t *)(this + 80) = a2;
  *(uint32_t *)(this + 84) = a3;
  *(uint32_t *)(this + 88) = a4;
  *(uint32_t *)(this + 44) = a5;
  *(uint8_t *)(this + 92) = a6;
  return a6;
}



// ------------------------------------------------------------
// 0x64CA40 sub_64CA40 —— 战斗光环查询 3（17 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64CA40(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 24);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 24) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x64CA60 CNChangeDamageBonusRate__vmtC —— CNChangeDamageBonusRate__vmtC 打开槽（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNChangeDamageBonusRate__vmtC(int this, int a2)
{
  int v3; // eax
  int v4; // ebx
  int v5; // eax
  int v6; // edx
  int result; // eax
  unsigned int v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // edx
  int v12; // esi
  int v13; // eax
  int v14; // edx

  v3 = *(uint32_t *)(this + 84);
  if ( *(uint8_t *)(this + 80) != 0 )
  {
    if ( v3 == 0 || v3 == 3 )
    {
      v4 = *(uint32_t *)(this + 88);
      v5 = sub_41A5E0(a2 + 1306);
      sub_41A590(a2 + 1306, v6, v4 + v5);
    }
    result = *(uint32_t *)(this + 84);
    if ( result == 1 || result == 3 )
    {
      v8 = a2 + 1334;
LABEL_14:
      v12 = *(uint32_t *)(this + 88);
      v13 = sub_41A5E0(v8);
      return sub_41A590(v8, v14, v12 + v13);
    }
  }
  else
  {
    if ( v3 == 0 || v3 == 3 )
    {
      v9 = *(uint32_t *)(this + 88);
      v10 = sub_41A5E0(a2 + 1320);
      sub_41A590(a2 + 1320, v11, v9 + v10);
    }
    result = *(uint32_t *)(this + 84);
    if ( result == 1 || result == 3 )
    {
      v8 = a2 + 1348;
      goto LABEL_14;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x64CB10 CNChangeDamageBonusRate__vmt4 —— CNChangeDamageBonusRate__vmt4 伤害率变更：AttackPowerUp.ptl（428F30/4600B0）
// ------------------------------------------------------------
void /*thiscall*/ CNChangeDamageBonusRate__vmt4(int this)
{
  int *v2; // edi
  uint32_t *v3; // eax
  int *v4; // eax
  int v5; // edx
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // esi
  int v11; // eax
  void *v12; // eax
  uint8_t v13[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  void *v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+20h] [ebp-4h]

  IRDAppendage__vmt4((int *)this);
  if ( *(uint8_t *)(this + 92) != 0 && (*(uint32_t *)(dword_8F7A24 + 12) != 4 || *(uint32_t *)(this + 4) == dword_8F7C04) )
  {
    v2 = *(int **)(this + 4);
    if ( *(uint8_t *)(this + 80) != 0 && *(int *)(this + 88) > 0 )
    {
      if ( *(uint32_t *)(this + 96) == 0 )
      {
        v3 = operator new(0x12Cu);
        v15 = v3;
        v16 = 0;
        if ( v3 != nullptr )
          v4 = sub_428F30(v3, (int)"Common/CommonEffect/Particle/AttackPowerUp.ptl", *(uint32_t *)(this + 4));
        else
          v4 = nullptr;
        *(uint32_t *)(this + 96) = v4;
        v5 = *v4;
        v16 = -1;
        (*(void (/*thiscall*/ **)(int *, int *))(v5 + 112))(v4, v2);
      }
      v6 = **(uint32_t **)(this + 96);
      v7 = (*(int (/*thiscall*/ **)(int *))(*v2 + 128))(v2);
      v8 = (*(int (/*thiscall*/ **)(int *, int))(*v2 + 124))(v2, v7 + 50);
      v9 = (*(int (/*thiscall*/ **)(int *, int))(*v2 + 120))(v2, v8);
      (*(void (/*thiscall*/ **)(uint32_t, int))(v6 + 40))(*(uint32_t *)(this + 96), v9);
    }
    v10 = *(uint32_t *)(this + 96);
    if ( v10 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)v10 + 92))(v10, v13);
      v11 = *v2;
      v16 = 1;
      v12 = (void *)(*(int (/*thiscall*/ **)(int *))(v11 + 80))(v2);
      sub_4600B0(v12, 2, 0, (int)v13);
      if ( Block != nullptr )
        j__free(Block);
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
int /*thiscall*/ CNAuraMasterSlow__vmt1C(void *this)
{
  CNRDAuraMaster__vmt1C((int)this);
  return (*(int (/*thiscall*/ **)(void *, const char *))(*(uint32_t *)this + 128))(
           this,
           "Common/Etc/Animation/Aura/SlowAuraMaster.ani");
}



// ------------------------------------------------------------
// 0x64CC50 CNAuraMasterIce__vmt84 —— CNAuraMasterIce__vmt84 受击事件槽（4E4630）
// ------------------------------------------------------------
bool /*stdcall*/ CNAuraMasterIce__vmt84(int a1)
{
  return (uint8_t)sub_4E4630(a1) != 0;
}



// ------------------------------------------------------------
// 0x64CC70 CNSlowFromSlowAura__vmt1C —— CNSlowFromSlowAura__vmt1C 生成装配（5F66A0）
// ------------------------------------------------------------
int /*thiscall*/ CNSlowFromSlowAura__vmt1C(int this)
{
  int result; // eax

  sub_5F66A0(this, 1);
  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 776))(*(uint32_t *)(this + 4), 0);
    if ( (uint8_t)result == 0 )
      return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 760))(
               0,
               *(uint32_t *)(this + 96),
               *(uint32_t *)(this + 100),
               *(uint32_t *)(this + 4),
               0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64CCC0 CNSlowFromSlowAura__vmt68 —— CNSlowFromSlowAura__vmt68 特效触发槽（24 行）
// ------------------------------------------------------------
int /*thiscall*/ CNSlowFromSlowAura__vmt68(int this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 776))(*(uint32_t *)(this + 4), 0);
    if ( (uint8_t)result == 0 )
      return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 4) + 760))(
               0,
               *(uint32_t *)(this + 96),
               *(uint32_t *)(this + 100),
               *(uint32_t *)(this + 4),
               0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64CD00 sub_64CD00 —— 缓速受方装配（4B1030 + 64A350）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64CD00(uint32_t *this, int a2, int a3, int a4)
{
  sub_4B1030(this);
  *this = &vftbl_CNRDAuraMinion;
  sub_64A350(this);
  *(this + 25) = a3;
  *(this + 24) = a2;
  *this = &vftbl_CNSlowFromSlowAura;
  *(this + 18) = a4;
  return this;
}



// ------------------------------------------------------------
// 0x64CD70 CNSlowFromSlowAura__vmt0 —— CNSlowFromSlowAura__vmt0 析构（转发 64CDA0）
// ------------------------------------------------------------
void */*thiscall*/ CNSlowFromSlowAura__vmt0(void *Block, char a2)
{
  sub_64CDA0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64CDA0 sub_64CDA0 —— 缓速受方初始化（649300 系）
// ------------------------------------------------------------
int /*thiscall*/ sub_64CDA0(int this)
{
  *(uint32_t *)this = &vftbl_CNSlowFromSlowAura;
  return sub_649300(this);
}



// ------------------------------------------------------------
// 0x64CDB0 CNAuraMasterSlow__vmt78 —— CNAuraMasterSlow__vmt78 光环生效（转发 64CD00）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraMasterSlow__vmt78(int *this, int a2)
{
  uint32_t *v3; // eax
  uint32_t *v4; // eax

  v3 = operator new(0x68u);
  if ( v3 != nullptr )
    v4 = sub_64CD00(v3, *(this + 32), *(this + 33), *(this + 34));
  else
    v4 = nullptr;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, int))(*v4 + 56))(
           v4,
           a2,
           *(this + 1),
           0,
           0,
           0,
           -1);
}



// ------------------------------------------------------------
// 0x64CE40 CNAuraMasterSlow__vmt7C —— CNAuraMasterSlow__vmt7C 光环失效槽（58 行）
// ------------------------------------------------------------
void /*stdcall*/ CNAuraMasterSlow__vmt7C(int a1)
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
  int v11; // eax

  if ( a1 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v3 = *(uint32_t *)(v2 + 4);
      v4 = v3 != 0 ? (*(uint32_t *)(v2 + 8) - v3) >> 2 : 0;
      if ( (int)i >= v4 )
        break;
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
      v6 = *(uint32_t *)(v5 + 4);
      if ( v6 != 0 && i < (*(uint32_t *)(v5 + 8) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( *(uint32_t *)(v7 + 4) == a1 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 700))(a1);
        v9 = *(uint32_t *)(v8 + 4);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(
                v10,
                0,
                &IRDAppendage `RTTI Type Descriptor',
                &CNSlowFromSlowAura `RTTI Type Descriptor',
                0);
        if ( v11 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 76))(v11, 0);
          return;
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x64CEF0 sub_64CEF0 —— 缓速动画查询（5910D0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64CEF0(uint32_t *this, int a2, int a3, int a4, int a5)
{
  sub_5910D0(a2, 18, 500, 0);
  *(this + 34) = a3;
  *this = &vftbl_CNAuraMasterSlow;
  *(this + 32) = a4;
  *(this + 33) = a5;
  return this;
}



// ------------------------------------------------------------
// 0x64CF30 CNAuraMasterSlow__vmt0 —— CNAuraMasterSlow__vmt0 析构（转发 64CF60）
// ------------------------------------------------------------
void */*thiscall*/ CNAuraMasterSlow__vmt0(void *Block, char a2)
{
  sub_64CF60();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64CF60 sub_64CF60 —— 缓速光环析构成员（591190）
// ------------------------------------------------------------
int /*thiscall*/ sub_64CF60(uint32_t *this)
{
  *this = &vftbl_CNAuraMasterSlow;
  return sub_591190(this);
}



// ------------------------------------------------------------
// 0x64CF70 sub_64CF70 —— 缓速辅助（41A590）
// ------------------------------------------------------------
int /*fastcall*/ sub_64CF70(int a1, int a2)
{
  int v3; // edx
  int v4; // edx
  int result; // eax

  sub_41A590(a1 + 84, a2, 0);
  sub_41A590(a1 + 98, v3, 0);
  result = sub_41A590(a1 + 112, v4, 0);
  *(uint8_t *)(a1 + 141) = 0;
  *(uint8_t *)(a1 + 142) = 0;
  *(uint32_t *)(a1 + 156) = 0;
  *(uint32_t *)(a1 + 160) = 0;
  *(uint8_t *)(a1 + 181) = 0;
  *(uint8_t *)(a1 + 182) = 0;
  *(uint8_t *)(a1 + 209) = 0;
  *(uint8_t *)(a1 + 210) = 0;
  *(uint8_t *)(a1 + 237) = 0;
  *(uint8_t *)(a1 + 238) = 0;
  *(uint8_t *)(a1 + 265) = 0;
  *(uint8_t *)(a1 + 266) = 0;
  *(uint8_t *)(a1 + 293) = 0;
  *(uint8_t *)(a1 + 294) = 0;
  *(uint8_t *)(a1 + 321) = 0;
  *(uint8_t *)(a1 + 322) = 0;
  *(uint8_t *)(a1 + 349) = 0;
  *(uint8_t *)(a1 + 350) = 0;
  *(uint8_t *)(a1 + 377) = 0;
  *(uint8_t *)(a1 + 378) = 0;
  *(uint8_t *)(a1 + 405) = 0;
  *(uint8_t *)(a1 + 406) = 0;
  *(uint8_t *)(a1 + 433) = 0;
  *(uint8_t *)(a1 + 434) = 0;
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
char /*thiscall*/ CNFireBomb__vmt1C(int this)
{
  int v2; // edx

  sub_698F90(this + 168, 0, 0);
  sub_41A590(this + 112, v2, 1);
  *(uint8_t *)(this + 141) = 0;
  *(uint8_t *)(this + 142) = 0;
  return sub_698F90(this + 128, *(uint32_t *)(this + 80), 0);
}



// ------------------------------------------------------------
// 0x64D070 CNFireBomb__vmt14 —— CNFireBomb__vmt14 爆炸流程（90 行：4049C0/491DE0/699000/493A60/4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNFireBomb__vmt14(int this, char a2, int a3, int a4, float a5)
{
  int v5; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  uint8_t v10; // bl
  int v11; // edi
  int v12; // eax
  int v13; // edi
  int v15; // [esp-28h] [ebp-30h]
  int v16; // [esp-Ch] [ebp-14h]
  int v17; // [esp-Ch] [ebp-14h]
  int v18; // [esp+10h] [ebp+8h]
  int v19; // [esp+14h] [ebp+Ch]
  int v20; // [esp+18h] [ebp+10h]
  int v21; // [esp+1Ch] [ebp+14h]

  LOBYTE(v5) = a2;
  if ( a2 != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 940))(*(uint32_t *)(this + 4)) == 0
      && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4)) != 0 )
    {
      v7 = sub_41A5E0(this + 98);
      v8 = sub_41A5E0(this + 112);
      v16 = ((uint8_t)(uint64_t)sub_4049C0(0.0, 200.0, v8, v7) << 24) | 0xFFFFFF;
      v15 = dword_79C0B0;
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));
      sub_491DE0(v15, a3, a4, a5, 2, 1, -16776961, v16);
    }
    v9 = a3 + (15 - 15 * sub_41A5E0(this + 98)) / 2;
    v19 = a4
        - (uint64_t)((double)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4))
                           * *(float *)&dword_77F6DC)
        - 20;
    v20 = 0;
    v5 = sub_41A5E0(this + 112);
    if ( v5 > 0 )
    {
      v18 = v9;
      v21 = this + 168;
      do
      {
        v10 = -1;
        v11 = sub_699000(v21);
        sub_493A60(*(uint32_t *)(this + 156), v11);
        sub_4938F0(*(uint32_t *)(this + 156));
        sub_493A60(*(uint32_t *)(this + 160), v11);
        sub_4938F0(*(uint32_t *)(this + 160));
        if ( v11 < 200 )
          v10 = (uint64_t)sub_4049C0(0.0, 255.0, v11, 200);
        sub_493A60(*(uint32_t *)(this + 164), v11);
        sub_4938F0(*(uint32_t *)(this + 164));
        if ( *(uint8_t *)(*(uint32_t *)(this + 164) + 170) == 0 )
          sub_491D00(dword_79C0B0, v18, v19, 0.0);
        if ( v20 >= sub_41A5E0(this + 112) - 2
          && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 44))(*(uint32_t *)(this + 4)) == 273 )
        {
          v17 = *(uint32_t *)(this + 80);
          v12 = sub_699000(this + 128);
          v10 = (uint64_t)(sub_4049C0(1.0, 0.0, v12, v17) * (double)v10);
        }
        if ( v10 == 0xFF )
        {
          sub_491D00(dword_79C0B0, v18, v19, 0.0);
          sub_491D00(dword_79C0B0, v18, v19, 0.0);
        }
        else
        {
          v13 = (v10 << 24) | 0xFFFFFF;
          sub_491DE0(dword_79C0B0, v18, v19, 0.0, 0, 0, 0, v13);
          sub_491DE0(dword_79C0B0, v18, v19, 0.0, 2, 0, 0, v13);
        }
        ++v20;
        v21 += 28;
        v18 += 15;
        v5 = sub_41A5E0(this + 112);
      }
      while ( v20 < v5 );
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x64D310 sub_64D310 —— 暗黑火表现（698F90/41A5E0/41A590 + 49C620/4E4A50/424120，60 行）
// ------------------------------------------------------------
char /*usercall*/ sub_64D310@<al>(int a1@<ecx>, int a2@<edi>)
{
  char result; // al
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // edi
  int v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // [esp-1Ch] [ebp-20h]
  int v14; // [esp-18h] [ebp-1Ch]

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 80))(a1);
  if ( result != 0 )
  {
    *(uint8_t *)(a1 + 141) = 0;
    *(uint8_t *)(a1 + 142) = 0;
    sub_698F90(a1 + 128, *(uint32_t *)(a1 + 80), 0);
    v4 = a1 + 28 * (sub_41A5E0(a1 + 112) + 6);
    *(uint8_t *)(v4 + 13) = 0;
    *(uint8_t *)(v4 + 14) = 0;
    v5 = sub_41A5E0(a1 + 112);
    sub_698F90(a1 + 28 * (v5 + 6), 0, 0);
    v6 = sub_41A5E0(a1 + 112);
    sub_41A590(a1 + 112, v7, v6 + 1);
    v8 = sub_41A5E0(a1 + 112);
    if ( v8 == sub_41A5E0(a1 + 98) && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 80))(a1) == 1 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(a1 + 4) + 308))(*(uint32_t *)(a1 + 4), a2) == 1 )
      {
        if ( *(uint8_t *)(*(uint32_t *)(a1 + 4) + 7093) == 1 )
          sub_49C620(1, 0, 0);
        v9 = *(uint32_t *)(a1 + 4);
        v10 = sub_41A5E0(a1 + 84);
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 128))(v9) - 10;
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 124))(v9);
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 120))(v9);
        sub_4E4A50(0, 40008, v10, v11, v13, v14, 4, 0, 0, 0);
        v12 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 4) + 80))(*(uint32_t *)(a1 + 4));
        sub_424120(*(uint32_t **)(v12 + 132), 8, 500);
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 76))(a1, 0);
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
int /*thiscall*/ CNFireBomb__vmt24(void *this, int a2, int a3, int a4)
{
  int result; // eax

  result = __RTDynamicCast(
             a2,
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &CNShootingStarExp `RTTI Type Descriptor',
             0);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 76))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x64D480 CNFireBomb__vmt4 —— CNFireBomb__vmt4 复位（699000/41A5E0/41A590/698F90）
// ------------------------------------------------------------
char /*thiscall*/ CNFireBomb__vmt4(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // edx
  int v5; // eax

  IRDAppendage__vmt4((int *)this);
  v2 = *(uint32_t *)(this + 152);
  v3 = sub_699000(this + 128);
  if ( v3 >= v2 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 44))(*(uint32_t *)(this + 4));
    if ( v3 == 273 )
    {
      if ( sub_41A5E0(this + 112) - 2 >= 0 )
        v5 = sub_41A5E0(this + 112) - 2;
      else
        v5 = 0;
      sub_41A590(this + 112, v4, v5);
      if ( sub_41A5E0(this + 112) != 0 )
      {
        *(uint8_t *)(this + 141) = 0;
        *(uint8_t *)(this + 142) = 0;
        LOBYTE(v3) = sub_698F90(this + 128, *(uint32_t *)(this + 80), 0);
      }
      else
      {
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 76))(this, 0);
      }
    }
  }
  return v3;
}



// ------------------------------------------------------------
// 0x64D510 sub_64D510 —— 装载 DarkFire.ani/DarkFireAura.ani/DarkFireExp.ani（41A590/42FCB0/431860）
// ------------------------------------------------------------
int /*fastcall*/ sub_64D510(uint32_t *a1, int a2, int a3, int a4, int a5)
{
  int v5; // eax
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int result; // eax

  v5 = a3;
  if ( a3 >= 10 )
    v5 = 10;
  sub_41A590((unsigned int)a1 + 98, a2, v5);
  a1[20] = a4;
  sub_41A590((unsigned int)(a1 + 21), v7, a5);
  v8 = sub_42FCB0(228);
  if ( v8 != 0 )
    v9 = sub_431860(v8, "Common/CommonEffect/Animation/DarkFire.ani", 1);
  else
    v9 = 0;
  a1[39] = v9;
  v10 = sub_42FCB0(228);
  if ( v10 != 0 )
    v11 = sub_431860(v10, "Common/CommonEffect/Animation/DarkFireAura.ani", 1);
  else
    v11 = 0;
  a1[40] = v11;
  v12 = sub_42FCB0(228);
  if ( v12 != 0 )
    result = sub_431860(v12, "Common/CommonEffect/Animation/DarkFireExp.ani", 1);
  else
    result = 0;
  a1[41] = result;
  return result;
}



// ------------------------------------------------------------
// 0x64D610 sub_64D610 —— 暗黑火受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D610(void ***this)
{
  int v2; // edi
  int result; // eax
  void **v4; // edi
  void **v5; // edi

  v2 = (int)*(this + 39);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 39));
    result = sub_657740(v2, 228);
  }
  v4 = *(this + 40);
  *(this + 39) = nullptr;
  if ( v4 != nullptr )
  {
    sub_42AF90(v4);
    result = sub_657740(v4, 228);
  }
  v5 = *(this + 41);
  *(this + 40) = nullptr;
  if ( v5 != nullptr )
  {
    sub_42AF90(v5);
    result = sub_657740(v5, 228);
  }
  *(this + 41) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x64D6A0 sub_64D6A0 —— 暗黑火装配（4B1030/41A630/64CF70/64D510）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D6A0(int this, int a2, int a3, int a4)
{
  int v5; // edx

  sub_4B1030(this);
  *(uint32_t *)this = &vftbl_CNFireBomb;
  sub_41A630(this + 84);
  *(uint32_t *)(this + 84) = &vftbl_clong;
  sub_41A630(this + 98);
  *(uint32_t *)(this + 98) = &vftbl_clong;
  sub_41A630(this + 112);
  *(uint32_t *)(this + 112) = &vftbl_clong;
  *(uint8_t *)(this + 132) = 0;
  *(uint32_t *)(this + 128) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 136) = 0;
  *(uint8_t *)(this + 140) = 1;
  *(uint8_t *)(this + 142) = 0;
  *(uint8_t *)(this + 141) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 144) = 0;
  `eh vector constructor iterator'((void *)(this + 168), 0x1Cu, 10, sub_401170, sub_401000);
  sub_64CF70(this, v5);
  sub_64D510((uint32_t *)this, a3, a2, a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x64D7A0 CNFireBomb__vmt0 —— CNFireBomb__vmt0 析构（转发 64D7D0）
// ------------------------------------------------------------
void */*thiscall*/ CNFireBomb__vmt0(void *Block, char a2)
{
  sub_64D7D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x64D7D0 sub_64D7D0 —— 暗黑火析构成员（64D610 + 41A580/5F6640）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D7D0(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_CNFireBomb;
  sub_64D610((void ***)this);
  `eh vector destructor iterator'((void *)(this + 168), 0x1Cu, 10, sub_401000);
  *(uint32_t *)(this + 128) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 132) = 0;
  sub_41A580(this + 112);
  sub_41A580(this + 98);
  sub_41A580(this + 84);
  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
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
int /*thiscall*/ sub_64D880(int this)
{
  *(uint8_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x64D8A0 CNWhipped__vmtC —— CNWhipped__vmtC 打开槽（41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNWhipped__vmtC(float *this, int a2)
{
  unsigned int v4; // edi
  int v5; // edx
  int v6; // edx
  float v8; // [esp+Ch] [ebp-4h]
  float v9; // [esp+Ch] [ebp-4h]
  int v10; // [esp+18h] [ebp+8h]
  int v11; // [esp+18h] [ebp+8h]

  v4 = a2 + 830;
  v8 = *(this + 21);
  *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(a2 + 830)) + v8;
  sub_41A590(v4, v5, v10);
  v9 = *(this + 22);
  *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v9;
  return sub_41A590(a2 + 858, v6, v11);
}



// ------------------------------------------------------------
// 0x64D910 sub_64D910 —— 鞭挞数据 2（20 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D910(uint32_t *this)
{
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x64D940 sub_64D940 —— 鞭挞数据 3（47E720/47EF20）
// ------------------------------------------------------------
int /*thiscall*/ sub_64D940(int this, int a2)
{
  int result; // eax

  sub_47E720(3, 30);
  *(uint32_t *)(this + 84) = sub_47EF20(1, a2, -1, -1, 11);
  *(float *)(this + 88) = (double)(int)sub_47EF20(2, a2, -1, -1, 11) * 0.001;
  *(float *)(this + 92) = (double)(int)sub_47EF20(3, a2, -1, -1, 11) * 0.001;
  *(uint32_t *)(this + 100) = sub_47EF20(4, a2, -1, -1, 11);
  *(uint32_t *)(this + 104) = sub_47EF20(5, a2, -1, -1, 11);
  result = sub_47EF20(6, a2, -1, -1, 11);
  *(float *)(this + 96) = (double)result * 0.001;
  return result;
}



// ------------------------------------------------------------
// 0x64DA00 CNFollowMe__vmtC —— CNFollowMe__vmtC 打开槽（4D8FE0 + 41A5E0/41A590）
// ------------------------------------------------------------
int /*thiscall*/ CNFollowMe__vmtC(int this, int a2)
{
  int v3; // eax
  int v4; // eax
  uint32_t *v5; // ecx
  int result; // eax
  unsigned int v8; // edi
  int v9; // edx
  int v10; // edx
  float v11; // [esp+4h] [ebp-8h]
  float v12; // [esp+4h] [ebp-8h]
  float v13; // [esp+4h] [ebp-8h]
  int v14; // [esp+14h] [ebp+8h]
  int v15; // [esp+14h] [ebp+8h]

  v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 1032))(*(uint32_t *)(this + 80)) + 16);
  if ( v3 != 0 )
  {
    v11 = (float)(*(int (/*thiscall*/ **)(uint32_t, int, uint32_t))(**(uint32_t **)(this + 80) + 8))(
                   *(uint32_t *)(this + 80),
                   v3,
                   0);
    if ( (double)sub_4D8FE0(*(uint32_t *)(this + 80)) * 0.5 < v11 )
    {
      v4 = *(uint32_t *)(this + 80);
      if ( v4 != 0 && (*(int (**)(void))(*(uint32_t *)v4 + 840))() == 0 )
      {
        v5 = *(uint32_t **)(this + 80);
        if ( v5[1787] != 24 )
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*v5 + 1104))(v5, 24);
      }
    }
  }
  result = *(uint32_t *)(this + 108);
  if ( result != 0 )
  {
    v8 = a2 + 830;
    v12 = *(float *)(this + 88);
    *(float *)&v14 = COERCE_FLOAT(sub_41A5E0(a2 + 830)) + v12;
    sub_41A590(v8, v9, v14);
    v13 = *(float *)(this + 92);
    *(float *)&v15 = COERCE_FLOAT(sub_41A5E0(a2 + 858)) + v13;
    return sub_41A590(a2 + 858, v10, v15);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64DAF0 CNFollowMe__vmt14 —— CNFollowMe__vmt14 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNFollowMe__vmt14(int this, char a2, int a3, int a4, int a5)
{
  char result; // al
  int v7; // eax

  result = a2;
  if ( a2 != 0 )
  {
    sub_4938F0(*(uint32_t *)(this + 4 * (*(uint8_t *)(*(uint32_t *)(this + 116) + 170) != 0) + 116));
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 80) + 192))(*(uint32_t *)(this + 80));
    return sub_491D00(dword_79C0B0, a3, a4 - v7, 0.0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64DB50 CNWhipped__vmt14 —— CNWhipped__vmt14 生成槽（699000/42B420/491690）
// ------------------------------------------------------------
char /*thiscall*/ CNWhipped__vmt14(int this, char a2, int a3, int a4, int a5)
{
  uint32_t **v5; // eax
  uint32_t **v7; // ebx
  int v8; // esi
  int v9; // eax
  int v10; // edi
  uint32_t *v11; // esi

  LOBYTE(v5) = a2;
  if ( a2 == 0 )
  {
    v5 = (uint32_t **)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 200))(*(uint32_t *)(this + 4));
    v7 = v5;
    if ( v5 != nullptr )
    {
      v8 = *(uint32_t *)(this + 104);
      v9 = sub_699000(this + 8);
      v10 = ((uint8_t)sub_42B420(v8 / 3, v8, v9, 250) << 24) | 0xFFFFFF;
      sub_491690(1, 2, 1, -16776961, v10, 1);
      v5 = (uint32_t **)v7[51];
      v11 = *v5;
      if ( *v5 != v5 )
      {
        do
        {
          LOBYTE(v5) = sub_491690(1, 2, 1, -16776961, v10, 1);
          v11 = (uint32_t *)*v11;
        }
        while ( v11 != v7[51] );
      }
    }
  }
  return (char)v5;
}



// ------------------------------------------------------------
// 0x64DC00 sub_64DC00 —— 鞭挞数据 4（47E720/47EF20/47E9D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_64DC00(int this, char a2, int a3)
{
  int result; // eax

  *(uint8_t *)(this + 80) = a2;
  sub_47E720(3, 20);
  *(uint32_t *)(this + 44) = sub_47EF20(0, a3, -1, -1, 11);
  if ( a2 != 0 )
  {
    *(float *)(this + 84) = (double)(int)sub_47EF20(1, a3, -1, -1, 11) * 0.001;
    *(float *)(this + 88) = (double)(int)sub_47EF20(2, a3, -1, -1, 11) * 0.001;
    *(uint32_t *)(this + 96) = sub_47EF20(3, a3, -1, -1, 11);
    *(uint32_t *)(this + 100) = sub_47EF20(4, a3, -1, -1, 11);
    result = sub_47EF20(5, a3, -1, -1, 11);
    *(float *)(this + 92) = (double)result * 0.0099999998;
  }
  else
  {
    *(float *)(this + 84) = (double)(int)sub_47EF20(6, a3, -1, -1, 11) * 0.001;
    result = sub_47EF20(7, a3, -1, -1, 11);
    *(float *)(this + 88) = (double)result * 0.001;
  }
  if ( dword_795FD4 == -1 )
  {
    dword_795FD4 = 200 / sub_47E9D0(0);
    result = 200 / sub_47E9D0(1);
    dword_795FD8 = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64DD40 sub_64DD40 —— 鞭挞主数据（52 行）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64DD40(int this, char a2)
{
  unsigned int v2; // edi
  int v3; // ebx
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  uint32_t *v7; // eax
  uint32_t *v8; // esi
  uint32_t *result; // eax
  int v11; // [esp+Ch] [ebp-8h]
  uint32_t *v12; // [esp+10h] [ebp-4h]

  v2 = 0;
  v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 700))(*(uint32_t *)(this + 4));
  v12 = nullptr;
  v11 = 0;
  while ( 1 )
  {
    v4 = *(uint32_t *)(v3 + 4);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
    if ( (int)v2 >= v5 )
      break;
    if ( v4 != 0 && v2 < (*(uint32_t *)(v3 + 8) - v4) >> 2 )
      v6 = *(uint32_t *)(v4 + 4 * v2);
    else
      v6 = 0;
    v7 = (uint32_t *)__RTDynamicCast(v6, 0, &IRDAppendage `RTTI Type Descriptor', &CNWhipped `RTTI Type Descriptor', 0);
    v8 = v7;
    if ( v7 != nullptr
      && v7[16] == 11
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v7 + 80))(v7) != 0
      && (a2 == 0 || v8 != (uint32_t *)this) )
    {
      if ( v12 == nullptr )
        v12 = v8;
      v8[26] = 0;
      ++v11;
    }
    ++v2;
  }
  result = v12;
  if ( v12 != nullptr )
    v12[26] = v11 * dword_795FD4[*(uint8_t *)(this + 80) == 0];
  return result;
}



// ------------------------------------------------------------
// 0x64DE20 sub_64DE20 —— 鞭挞循环数据（119 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64DE20(int this)
{
  int v1; // eax
  int v2; // edx
  int v3; // eax
  int result; // eax
  signed int v5; // ebx
  int v6; // edi
  int v7; // edx
  int v8; // esi
  int v9; // eax
  int v10; // edx
  int v11; // esi
  unsigned int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // esi
  int v16; // eax
  int v17; // edx
  int v18; // esi
  unsigned int v19; // eax
  int v20; // eax
  int v21; // edi
  int v22; // edx
  int v23; // esi
  int v24; // eax
  signed int v25; // [esp+0h] [ebp-Ch]
  signed int v26; // [esp+4h] [ebp-8h]
  unsigned int v27; // [esp+8h] [ebp-4h]

  v1 = *(uint32_t *)(this + 80);
  v2 = *(uint32_t *)(v1 + 7620);
  v3 = v1 + 7616;
  if ( v2 != 0 )
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
  if ( result >= 4 )
  {
    v25 = result - 3;
    v27 = 2;
    v6 = 0;
    do
    {
      v7 = *(uint32_t *)(this + 80);
      v8 = *(uint32_t *)(v7 + 7620);
      if ( v8 != 0 && v5 < (unsigned int)((*(uint32_t *)(v7 + 7624) - v8) >> 5) )
        v9 = v6 + v8;
      else
        v9 = 0;
      *(float *)(v9 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v9 + 4);
      v10 = *(uint32_t *)(this + 80);
      v11 = *(uint32_t *)(v10 + 7620);
      if ( v11 != 0 )
        v12 = (*(uint32_t *)(v10 + 7624) - v11) >> 5;
      else
        v12 = 0;
      if ( v27 - 1 >= v12 )
        v13 = 0;
      else
        v13 = *(uint32_t *)(v10 + 7620) + v6 + 32;
      *(float *)(v13 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v13 + 4);
      v14 = *(uint32_t *)(this + 80);
      v15 = *(uint32_t *)(v14 + 7620);
      if ( v15 != 0 && v27 < (*(uint32_t *)(v14 + 7624) - v15) >> 5 )
        v16 = *(uint32_t *)(v14 + 7620) + v6 + 64;
      else
        v16 = 0;
      *(float *)(v16 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v16 + 4);
      v17 = *(uint32_t *)(this + 80);
      v18 = *(uint32_t *)(v17 + 7620);
      if ( v18 != 0 )
        v19 = (*(uint32_t *)(v17 + 7624) - v18) >> 5;
      else
        v19 = 0;
      if ( v27 + 1 >= v19 )
        v20 = 0;
      else
        v20 = *(uint32_t *)(v17 + 7620) + v6 + 96;
      v5 += 4;
      v6 += 128;
      v27 += 4;
      *(float *)(v20 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v20 + 4);
    }
    while ( v5 < v25 );
    result = v26;
  }
  if ( v5 < result )
  {
    v21 = 32 * v5;
    do
    {
      v22 = *(uint32_t *)(this + 80);
      v23 = *(uint32_t *)(v22 + 7620);
      if ( v23 != 0 && v5 < (unsigned int)((*(uint32_t *)(v22 + 7624) - v23) >> 5) )
        v24 = v21 + v23;
      else
        v24 = 0;
      ++v5;
      v21 += 32;
      *(float *)(v24 + 4) = (*(float *)(this + 96) + 1.0) * *(float *)(v24 + 4);
      result = v26;
    }
    while ( v5 < v26 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x64DFE0 sub_64DFE0 —— 跟随数据（117 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64DFE0(int this)
{
  int v1; // eax
  int v2; // edx
  int v3; // eax
  int result; // eax
  signed int v5; // ebx
  int v6; // edi
  int v7; // edx
  int v8; // esi
  int v9; // eax
  int v10; // edx
  int v11; // esi
  unsigned int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // esi
  int v16; // eax
  int v17; // edx
  int v18; // esi
  unsigned int v19; // eax
  int v20; // eax
  int v21; // edi
  int v22; // edx
  int v23; // esi
  signed int v24; // [esp+0h] [ebp-Ch]
  signed int v25; // [esp+4h] [ebp-8h]
  unsigned int v26; // [esp+8h] [ebp-4h]

  v1 = *(uint32_t *)(this + 80);
  v2 = *(uint32_t *)(v1 + 7620);
  v3 = v1 + 7616;
  if ( v2 != 0 )
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
  if ( result >= 4 )
  {
    v24 = result - 3;
    v26 = 2;
    v6 = 0;
    do
    {
      v7 = *(uint32_t *)(this + 80);
      v8 = *(uint32_t *)(v7 + 7620);
      if ( v8 != 0 && v5 < (unsigned int)((*(uint32_t *)(v7 + 7624) - v8) >> 5) )
        v9 = v6 + v8;
      else
        v9 = 0;
      *(float *)(v9 + 4) = *(float *)(v9 + 4) / (*(float *)(this + 96) + 1.0);
      v10 = *(uint32_t *)(this + 80);
      v11 = *(uint32_t *)(v10 + 7620);
      if ( v11 != 0 )
        v12 = (*(uint32_t *)(v10 + 7624) - v11) >> 5;
      else
        v12 = 0;
      if ( v26 - 1 >= v12 )
        v13 = 0;
      else
        v13 = *(uint32_t *)(v10 + 7620) + v6 + 32;
      *(float *)(v13 + 4) = *(float *)(v13 + 4) / (*(float *)(this + 96) + 1.0);
      v14 = *(uint32_t *)(this + 80);
      v15 = *(uint32_t *)(v14 + 7620);
      if ( v15 != 0 && v26 < (*(uint32_t *)(v14 + 7624) - v15) >> 5 )
        v16 = *(uint32_t *)(v14 + 7620) + v6 + 64;
      else
        v16 = 0;
      *(float *)(v16 + 4) = *(float *)(v16 + 4) / (*(float *)(this + 96) + 1.0);
      v17 = *(uint32_t *)(this + 80);
      v18 = *(uint32_t *)(v17 + 7620);
      if ( v18 != 0 )
        v19 = (*(uint32_t *)(v17 + 7624) - v18) >> 5;
      else
        v19 = 0;
      if ( v26 + 1 >= v19 )
        v20 = 0;
      else
        v20 = *(uint32_t *)(v17 + 7620) + v6 + 96;
      v5 += 4;
      v6 += 128;
      v26 += 4;
      *(float *)(v20 + 4) = *(float *)(v20 + 4) / (*(float *)(this + 96) + 1.0);
    }
    while ( v5 < v24 );
    result = v25;
  }
  if ( v5 < result )
  {
    v21 = 32 * v5;
    do
    {
      v22 = *(uint32_t *)(this + 80);
      v23 = *(uint32_t *)(v22 + 7620);
      if ( v23 != 0 && v5 < (unsigned int)((*(uint32_t *)(v22 + 7624) - v23) >> 5) )
        result = v21 + v23;
      else
        result = 0;
      ++v5;
      v21 += 32;
      *(float *)(result + 4) = *(float *)(result + 4) / (*(float *)(this + 96) + 1.0);
    }
    while ( v5 < v25 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x64E1A0 CNWhipped__vmt4 —— CNWhipped__vmt4 复位（4600B0）
// ------------------------------------------------------------
void /*thiscall*/ CNWhipped__vmt4(int this)
{
  int *v2; // esi
  int v3; // ebx
  int v4; // edx
  void *v5; // eax
  int v6; // [esp-Ch] [ebp-3Ch]
  int v7; // [esp-8h] [ebp-38h]
  int v8; // [esp-4h] [ebp-34h]
  uint8_t v9[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  int v11; // [esp+1Ch] [ebp-14h]
  int v12; // [esp+20h] [ebp-10h]
  int v13; // [esp+2Ch] [ebp-4h]

  v11 = this;
  IRDAppendage__vmt4((int *)this);
  v2 = *(int **)(this + 4);
  v3 = **(uint32_t **)(this + 108);
  v12 = (*(int (/*thiscall*/ **)(int *))(*v2 + 192))(v2);
  v8 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*v2 + 128))(v2, (uint64_t)((double)v12 * -0.5) >> 32)
     - (uint64_t)((double)v12 * -0.5);
  v7 = (*(int (/*thiscall*/ **)(int *))(*v2 + 124))(v2);
  v6 = (*(int (/*thiscall*/ **)(int *))(*v2 + 120))(v2);
  (*(void (/*thiscall*/ **)(uint32_t))(v3 + 40))(*(uint32_t *)(v11 + 108));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(v11 + 108) + 92))(*(uint32_t *)(v11 + 108), v9);
  v4 = *v2;
  v13 = 0;
  v5 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v4 + 80))(v2, 2, 0, v9);
  sub_4600B0(v5, v6, v7, v8);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x64E260 CNWhipped__vmt20 —— CNWhipped__vmt20 主循环（64E260 + 64DD40，127 行）
// ------------------------------------------------------------
char /*thiscall*/ sub_64E260(int this, char a2)
{
  char result; // al
  uint32_t *v4; // esi
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

  result = a2;
  if ( a2 == 0 )
  {
    v4 = __RTDynamicCast(
           *(uint32_t **)(this + 4),
           0,
           &IRDActiveObject `RTTI Type Descriptor',
           &IRDMonster `RTTI Type Descriptor',
           0);
    if ( *(uint8_t *)(this + 80) != 0 && v4 != nullptr )
    {
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 1040))(v4);
      *(uint32_t *)(v5 + 72) -= *(uint32_t *)(this + 96);
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 1040))(v4) != 0 )
      {
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 1040))(v4);
        *v6 -= *(uint32_t *)(this + 100);
      }
      v7 = v4[1905];
      if ( v7 != 0 )
      {
        v24 = (v4[1906] - v7) >> 5;
        v7 = v24;
      }
      else
      {
        v24 = 0;
      }
      v8 = 0;
      if ( v7 >= 4 )
      {
        v23 = v7 - 3;
        v25 = 2;
        v9 = 0;
        do
        {
          v10 = v4[1905];
          if ( v10 != 0 && v8 < (unsigned int)((v4[1906] - v10) >> 5) )
            v11 = v9 + v10;
          else
            v11 = 0;
          *(float *)(v11 + 4) = *(float *)(v11 + 4) / (*(float *)(this + 92) + 1.0);
          v12 = v4[1905];
          if ( v12 != 0 )
            v13 = (v4[1906] - v12) >> 5;
          else
            v13 = 0;
          if ( v25 - 1 >= v13 )
            v14 = 0;
          else
            v14 = v4[1905] + v9 + 32;
          *(float *)(v14 + 4) = *(float *)(v14 + 4) / (*(float *)(this + 92) + 1.0);
          v15 = v4[1905];
          if ( v15 != 0 && v25 < (v4[1906] - v15) >> 5 )
            v16 = v4[1905] + v9 + 64;
          else
            v16 = 0;
          *(float *)(v16 + 4) = *(float *)(v16 + 4) / (*(float *)(this + 92) + 1.0);
          v17 = v4[1905];
          if ( v17 != 0 )
            v18 = (v4[1906] - v17) >> 5;
          else
            v18 = 0;
          if ( v25 + 1 >= v18 )
            v19 = 0;
          else
            v19 = v4[1905] + v9 + 96;
          v8 += 4;
          v9 += 128;
          v25 += 4;
          *(float *)(v19 + 4) = *(float *)(v19 + 4) / (*(float *)(this + 92) + 1.0);
        }
        while ( v8 < v23 );
        v7 = v24;
      }
      if ( v8 < v7 )
      {
        v20 = 32 * v8;
        do
        {
          v21 = v4[1905];
          if ( v21 != 0 && v8 < (unsigned int)((v4[1906] - v21) >> 5) )
            v22 = v20 + v21;
          else
            v22 = 0;
          ++v8;
          v20 += 32;
          *(float *)(v22 + 4) = *(float *)(v22 + 4) / (*(float *)(this + 92) + 1.0);
        }
        while ( v8 < v24 );
      }
    }
    return sub_64DD40(1);
  }
  return result;
}


// ------------------------------------------------------------
// 0x64E470 sub_64E470 —— 跟随循环装配（64DE20/699000/64DFE0）
// ------------------------------------------------------------
void /*thiscall*/ sub_64E470(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // edi
  int v5; // eax
  uint32_t *v6; // eax
  int v7; // eax
  uint32_t *v8; // eax

  v3 = *(this + 20);
  if ( v3 != 0 )
  {
    v4 = *(this + 27);
    *(this + 27) = a2;
    if ( a2 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 1152))(v3, a2);
      if ( v4 == 0 )
      {
        v5 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));
        *(uint32_t *)(v5 + 76) += *(this + 25);
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));
        *v6 += *(this + 26);
        sub_64DE20((int)this);
      }
      *(this + 28) = sub_699000(*(this + 20) + 36);
    }
    else if ( v4 != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 1040))(v3);
      *(uint32_t *)(v7 + 76) -= *(this + 25);
      v8 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));
      *v8 -= *(this + 26);
      sub_64DFE0((int)this);
    }
  }
}



// ------------------------------------------------------------
// 0x64E520 CNFollowMe__vmt28 —— CNFollowMe__vmt28 槽（转发 64E470）
// ------------------------------------------------------------
void /*thiscall*/ CNFollowMe__vmt28(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v6; // eax
  int v7; // eax

  if ( a2 == *(uint32_t *)(*(this + 20) + 8352) )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3);
    if ( (*(uint8_t *)(v6 + 16) != 0
       || *(float *)v6 > 0.0
       || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3) + 60) != 0)
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 576))(a3) != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 576))(a3);
      sub_64E470(this, v7);
    }
  }
}



// ------------------------------------------------------------
// 0x64E590 CNFollowMe__vmt4 —— CNFollowMe__vmt4 复位（699000 + 64DFE0）
// ------------------------------------------------------------
int /*thiscall*/ CNFollowMe__vmt4(int *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // eax
  uint32_t *v5; // eax
  int v6; // eax
  int v7; // ecx
  int result; // eax

  IRDAppendage__vmt4(this);
  if ( *(this + 27) != 0 && sub_699000(*(this + 20) + 36) >= *(this + 21) + *(this + 28) )
  {
    v2 = *(this + 20);
    if ( v2 != 0 )
    {
      v3 = *(this + 27);
      *(this + 27) = 0;
      if ( v3 != 0 )
      {
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 1040))(v2);
        *(uint32_t *)(v4 + 76) -= *(this + 25);
        v5 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));
        *v5 -= *(this + 26);
        sub_64DFE0((int)this);
      }
    }
  }
  v6 = __RTDynamicCast(*(this + 9), 0, &IRDCollisionObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
  if ( v6 == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);
  v7 = *(uint32_t *)(v6 + 8372);
  if ( v7 == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 80))(v7);
  if ( (uint8_t)result == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x64E640 CNFollowMe__vmt20 —— CNFollowMe__vmt20 主循环（64DFE0）
// ------------------------------------------------------------
char /*thiscall*/ CNFollowMe__vmt20(uint32_t *this, char a2)
{
  int v2; // eax
  int v4; // ecx
  int v5; // eax
  uint32_t *v6; // eax

  LOBYTE(v2) = a2;
  if ( a2 == 0 )
  {
    v4 = *(this + 20);
    if ( v4 != 0 )
    {
      v2 = *(this + 27);
      *(this + 27) = 0;
      if ( v2 != 0 )
      {
        v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 1040))(v4);
        *(uint32_t *)(v5 + 76) -= *(this + 25);
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 20) + 1040))(*(this + 20));
        *v6 -= *(this + 26);
        LOBYTE(v2) = sub_64DFE0((int)this);
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x64E6A0 CNWhipped__vmt1C —— CNWhipped__vmt1C 生成装配：Common/CommonEffect/Particle/AttackPowerUp.ptl（428F30/64DD40，136 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64E6A0(int this)
{
  uint32_t *v2; // esi
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
  uint32_t *v21; // eax
  uint32_t *v22; // eax
  int v23; // ecx
  void *Block; // [esp+8h] [ebp-18h]
  int v26; // [esp+Ch] [ebp-14h]
  unsigned int v27; // [esp+10h] [ebp-10h]

  v2 = (uint32_t *)__RTDynamicCast(
                   *(uint32_t *)(this + 4),
                   0,
                   &IRDActiveObject `RTTI Type Descriptor',
                   &IRDMonster `RTTI Type Descriptor',
                   0);
  if ( *(uint8_t *)(this + 80) != 0 && v2 != nullptr )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*v2 + 1040))(v2);
    *(uint32_t *)(v3 + 72) += *(uint32_t *)(this + 96);
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v2 + 1040))(v2) != 0 )
    {
      v4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v2 + 1040))(v2);
      *v4 += *(uint32_t *)(this + 100);
    }
    v5 = v2[1905];
    if ( v5 != 0 )
    {
      v26 = (v2[1906] - v5) >> 5;
      v5 = v26;
    }
    else
    {
      v26 = 0;
    }
    v6 = 0;
    if ( v5 >= 4 )
    {
      Block = (void *)(v5 - 3);
      v27 = 2;
      v7 = 0;
      do
      {
        v8 = v2[1905];
        if ( v8 != 0 && v6 < (unsigned int)((v2[1906] - v8) >> 5) )
          v9 = v7 + v8;
        else
          v9 = 0;
        *(float *)(v9 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v9 + 4);
        v10 = v2[1905];
        if ( v10 != 0 )
          v11 = (v2[1906] - v10) >> 5;
        else
          v11 = 0;
        if ( v27 - 1 >= v11 )
          v12 = 0;
        else
          v12 = v7 + v2[1905] + 32;
        *(float *)(v12 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v12 + 4);
        v13 = v2[1905];
        if ( v13 != 0 && v27 < (v2[1906] - v13) >> 5 )
          v14 = v7 + v2[1905] + 64;
        else
          v14 = 0;
        *(float *)(v14 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v14 + 4);
        v15 = v2[1905];
        if ( v15 != 0 )
          v16 = (v2[1906] - v15) >> 5;
        else
          v16 = 0;
        if ( v27 + 1 >= v16 )
          v17 = 0;
        else
          v17 = v7 + v2[1905] + 96;
        v6 += 4;
        v7 += 128;
        v27 += 4;
        *(float *)(v17 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v17 + 4);
      }
      while ( v6 < (int)Block );
      v5 = v26;
    }
    if ( v6 < v5 )
    {
      v18 = 32 * v6;
      do
      {
        v19 = v2[1905];
        if ( v19 != 0 && v6 < (unsigned int)((v2[1906] - v19) >> 5) )
          v20 = v18 + v19;
        else
          v20 = 0;
        ++v6;
        v18 += 32;
        *(float *)(v20 + 4) = (*(float *)(this + 92) + 1.0) * *(float *)(v20 + 4);
      }
      while ( v6 < v26 );
    }
  }
  if ( *(uint32_t *)(this + 108) == 0 )
  {
    v21 = operator new(0x12Cu);
    if ( v21 != nullptr )
      v22 = sub_428F30(v21, (int)"Common/CommonEffect/Particle/AttackPowerUp.ptl", *(uint32_t *)(this + 4));
    else
      v22 = nullptr;
    v23 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 108) = v22;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*v22 + 112))(v22, v23);
  }
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 108) + 12))(*(uint32_t *)(this + 108), 0);
  return sub_64DD40(0);
}


// ------------------------------------------------------------
// 0x64E920 sub_64E920 —— 跟随受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64E920(void ***this)
{
  void ***v1; // esi
  int i; // ebx
  void **v3; // edi
  int result; // eax

  v1 = this + 29;
  for ( i = 2; i != 0; --i )
  {
    v3 = *v1;
    if ( *v1 != nullptr )
    {
      sub_42AF90(*v1);
      result = sub_657740(v3, 228);
    }
    *v1++ = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64E960 CNFollowMe__vmt1C —— CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/Animation/FollowMeFlag1/2/3.ani（42FCB0/431860/44B6C0/44E0D0/45FE80/4A06D0/4922F0）
// ------------------------------------------------------------
int /*thiscall*/ CNFollowMe__vmt1C(int *this)
{
  int v2; // eax
  int v3; // esi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int result; // eax
  int v9; // eax
  int v10; // ebx
  char *v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // ebx
  int v15; // eax
  int v16; // eax
  int v17; // edi
  float v18; // [esp+Ch] [ebp-24h]

  v2 = __RTDynamicCast(*(this + 1), 0, &IRDActiveObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
  v3 = v2;
  if ( v2 == 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 76))(this, 0);
  *(this + 20) = v2;
  v4 = sub_42FCB0(228);
  if ( v4 != 0 )
    v5 = sub_431860(v4, "Character/Mage/Effect/Animation/FollowMeFlag1.ani", 1);
  else
    v5 = 0;
  *(this + 29) = v5;
  v6 = sub_42FCB0(228);
  if ( v6 != 0 )
    v7 = sub_431860(v6, "Character/Mage/Effect/Animation/FollowMeFlag2.ani", 1);
  else
    v7 = 0;
  *(this + 30) = v7;
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 80))(v3);
  if ( result != 0 )
  {
    v9 = sub_42FCB0(228);
    if ( v9 != 0 )
      v10 = sub_431860(v9, "Character/Mage/Effect/Animation/FollowMeFlag3.ani", 1);
    else
      v10 = 0;
    v11 = (char *)sub_44B6C0(284);
    v12 = (int)v11;
    if ( v11 != nullptr )
    {
      sub_44E0D0(v11, v10, 1);
      *(uint32_t *)v12 = &vftbl_CNRDPooledObject;
    }
    else
    {
      v12 = 0;
    }
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 80))(v3);
    sub_45FE80(v13, v12, 2, 0, v12, v3, 0);
    v14 = *(uint32_t *)v12;
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 124))(v3);
    v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 120))(v3, v15 + 1);
    (*(void (/*thiscall*/ **)(int, int))(v14 + 112))(v12, v16);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 60))(v12, v3);
    sub_4A06D0(0);
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 192))(v3);
    v18 = (double)(v17 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 128))(v3) + 30) * 0.0095238099;
    return sub_4922F0(v18);
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
char /*thiscall*/ CNAuraShield__vmt4(int *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // edi

  IRDAppendage__vmt4(this);
  v2 = *(this + 25);
  if ( v2 != 0 )
  {
    if ( v2 == 1 )
    {
      v3 = *(this + 11) - sub_491C10(*(this + 22));
      v2 = sub_699000((int)(this + 2));
      if ( v2 < v3 )
        return v2;
    }
    else
    {
      if ( v2 != 3 )
        return v2;
      LOBYTE(v2) = *(uint8_t *)(*(this + 23) + 170);
      if ( (uint8_t)v2 == 0 )
        return v2;
      v4 = *(this + 11) - sub_491C10(*(this + 22));
      v2 = sub_699000((int)(this + 2));
      if ( v2 < v4 )
      {
        *(this + 25) = 1;
        LOBYTE(v2) = sub_4926A0(*(this + 21));
        return v2;
      }
    }
    *(this + 25) = 2;
    return v2;
  }
  v2 = *(this + 20);
  if ( *(uint8_t *)(v2 + 170) != 0 )
    *(this + 25) = 1;
  return v2;
}



// ------------------------------------------------------------
// 0x64EBC0 CNAuraShield__vmt14 —— CNAuraShield__vmt14 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraShield__vmt14(int *this, char a2, int a3, int a4, int a5)
{
  char result; // al

  result = a2;
  if ( a2 != 0 )
  {
    sub_4938F0(*(this + *(this + 25) + 20));
    result = sub_491D00(dword_79C0B0, a3, a4, 0.0);
    if ( *(this + 25) == 3 )
    {
      sub_4938F0(*(this + 24));
      return sub_491D00(dword_79C0B0, a3 + *(this + 26), a4 + *(this + 27), 0.0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x64EC30 CNAuraShield__vmt1C —— CNAuraShield__vmt1C 播 AURA_SHIELD_LOOP 循环事件（4926A0）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraShield__vmt1C(int *this)
{
  int *v2; // esi
  int i; // ebx
  int v4; // ecx

  v2 = this + 20;
  for ( i = 5; i != 0; --i )
    sub_4926A0(*v2++);
  v4 = *(this + 1);
  *(this + 25) = 0;
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v4 + 212))(
           v4,
           "AURA_SHIELD_LOOP",
           5,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64EC70 CNAuraShield__vmt20 —— CNAuraShield__vmt20 更新槽（15 行）
// ------------------------------------------------------------
char /*thiscall*/ CNAuraShield__vmt20(uint32_t **this, char a2)
{
  char result; // al

  result = a2;
  if ( a2 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 1) + 216))(*(this + 1), 5);
  return result;
}



// ------------------------------------------------------------
// 0x64EC90 CNAuraShield__vmt78 —— CNAuraShield__vmt78 受击消耗槽（4926A0）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraShield__vmt78(int *this)
{
  int v2; // eax
  int v3; // ecx
  int result; // eax

  *(this + 26) = rand() % 60 - 30;
  v2 = rand();
  v3 = *(this + 23);
  *(this + 27) = v2 % 40 - 20;
  sub_4926A0(v3);
  result = sub_4926A0(*(this + 24));
  *(this + 25) = 3;
  return result;
}



// ------------------------------------------------------------
// 0x64ECE0 CNAuraShield__vmt34 —— CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行）
// ------------------------------------------------------------
int /*thiscall*/ CNAuraShield__vmt34(uint32_t **this)
{
  return (*(int (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(this + 1) + 212))(
           *(this + 1),
           "AURA_SHIELD_LOOP",
           5,
           0,
           0);
}



// ------------------------------------------------------------
// 0x64ED00 sub_64ED00 —— 装载 AuraShieldStart/Loop/End/Hit1/Hit2.ani（42FCB0/431860）
// ------------------------------------------------------------
int /*thiscall*/ sub_64ED00(uint32_t *this)
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

  v2 = sub_42FCB0(228);
  if ( v2 != 0 )
    v3 = sub_431860(v2, "Character/Mage/Effect/Animation/AuraShieldStart.ani", 1);
  else
    v3 = 0;
  *(this + 20) = v3;
  v4 = sub_42FCB0(228);
  if ( v4 != 0 )
    v5 = sub_431860(v4, "Character/Mage/Effect/Animation/AuraShieldLoop.ani", 1);
  else
    v5 = 0;
  *(this + 21) = v5;
  v6 = sub_42FCB0(228);
  if ( v6 != 0 )
    v7 = sub_431860(v6, "Character/Mage/Effect/Animation/AuraShieldEnd.ani", 1);
  else
    v7 = 0;
  *(this + 22) = v7;
  v8 = sub_42FCB0(228);
  if ( v8 != 0 )
    v9 = sub_431860(v8, "Character/Mage/Effect/Animation/AuraShieldHit1.ani", 1);
  else
    v9 = 0;
  *(this + 23) = v9;
  v10 = sub_42FCB0(228);
  if ( v10 != 0 )
  {
    result = sub_431860(v10, "Character/Mage/Effect/Animation/AuraShieldHit2.ani", 1);
    *(this + 24) = result;
  }
  else
  {
    *(this + 24) = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64EE40 sub_64EE40 —— 护盾受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64EE40(void ***this)
{
  void ***v1; // esi
  int i; // ebx
  void **v3; // edi
  int result; // eax

  v1 = this + 20;
  for ( i = 5; i != 0; --i )
  {
    v3 = *v1;
    if ( *v1 != nullptr )
    {
      sub_42AF90(*v1);
      result = sub_657740(v3, 228);
    }
    *v1++ = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x64EE80 sub_64EE80 —— 13 行小函数
// ------------------------------------------------------------
int /*thiscall*/ sub_64EE80(uint32_t *this)
{
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
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
bool /*thiscall*/ CNSummonMonsterAura__vmt84(uint32_t **this, int a2)
{
  int v4; // edi

  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529) != 0
      && (v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 376))(*(this + 1))) == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2)
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 724))(a2) == 0;
}



// ------------------------------------------------------------
// 0x64EF00 CNSummonMonsterAura__vmt18 —— CNSummonMonsterAura__vmt18 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNSummonMonsterAura__vmt18(int *this, char a2, int a3, int a4, float a5)
{
  char result; // al

  result = CNRDAuraMaster__vmt18((int)this, a2, a3, a4, a5);
  if ( a2 != 0 )
  {
    sub_4938F0(*(this + 34));
    return sub_491D00(dword_79C0B0, a3, a4, 0.0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64EF50 CNSummonMonsterAura__vmt88 —— CNSummonMonsterAura__vmt88 槽（10 行）
// ------------------------------------------------------------
BOOL /*stdcall*/ CNSummonMonsterAura__vmt88(int a1)
{
  return *(uint32_t *)(a1 + 64) == 17;
}



// ------------------------------------------------------------
// 0x64EF70 CNSummonMonsterAura__vmt7C —— CNSummonMonsterAura__vmt7C 光环失效槽（65 行）
// ------------------------------------------------------------
void /*thiscall*/ CNSummonMonsterAura__vmt7C(uint32_t *this, int a2)
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
  int v11; // ecx
  int v12; // ebx
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx

  if ( a2 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v4 = *(uint32_t *)(v3 + 4);
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v7 = *(uint32_t *)(v6 + 4);
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == a2 )
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v10 = *(uint32_t *)(v9 + 4);
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )
          v11 = *(uint32_t *)(v10 + 4 * i);
        else
          v11 = 0;
        v12 = *(this + 1);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 64))(v11) + 32) == v12 )
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
          v14 = *(uint32_t *)(v13 + 4);
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
          {
            v15 = *(uint32_t **)(v14 + 4 * i);
            if ( v15 != nullptr && v15[16] == 17 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v15 + 76))(v15, 0);
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
bool /*thiscall*/ CNSummonMonsterAura__vmt8C(float *this, int a2)
{
  int v2; // eax
  int v3; // esi

  v2 = *(uint32_t *)(a2 + 84);
  if ( v2 != 0 && (*(uint32_t *)(a2 + 88) - v2) / 12 != 0 )
    v3 = *(uint32_t *)(a2 + 84);
  else
    v3 = 0;
  return *(float *)(v3 + 8) >= (double)*(this + 32);
}



// ------------------------------------------------------------
// 0x64F0B0 CNSummonMonsterAura__vmt78 —— CNSummonMonsterAura__vmt78 光环生效（4B3C90）
// ------------------------------------------------------------
int /*thiscall*/ CNSummonMonsterAura__vmt78(uint32_t *this, int a2)
{
  int v3; // esi

  if ( operator new(0x7Cu) != nullptr )
    v3 = sub_4B3C90(0, 7);
  else
    v3 = 0;
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v3 + 120))(v3, 4, 1, *(this + 32));
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v3 + 120))(v3, 25, 1, *(this + 32));
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v3 + 120))(v3, 5, 1, *(this + 33));
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)v3 + 120))(v3, 26, 1, *(this + 33));
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)v3 + 56))(
           v3,
           a2,
           *(this + 1),
           0,
           0,
           17,
           -1);
}



// ------------------------------------------------------------
// 0x64F170 sub_64F170 —— 装载 SummonMonsterAuraArea.ani（42FCB0/431860）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F170(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // eax
  int v6; // eax

  v5 = sub_42FCB0(228);
  if ( v5 != 0 )
    v6 = sub_431860(v5, "Character/Mage/Effect/Animation/SummonMonsterAuraArea.ani", 1);
  else
    v6 = 0;
  *(this + 34) = v6;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 148))(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x64F1F0 sub_64F1F0 —— 召唤受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F1F0(void ***this)
{
  int v2; // esi
  int result; // eax

  v2 = (int)*(this + 34);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 34));
    result = sub_657740(v2, 228);
  }
  *(this + 34) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x64F230 sub_64F230 —— 13 行小函数 2
// ------------------------------------------------------------
int /*thiscall*/ sub_64F230(uint32_t *this)
{
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 43) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x64F250 sub_64F250 —— 目标数据（47EF20/607260/607280）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F250(uint32_t *this, int a2)
{
  uint32_t *v3; // ecx
  int v4; // eax
  int result; // eax

  v3 = (uint32_t *)*(this + 32);
  *(this + 33) = a2;
  v4 = sub_47EF20(v3, 1u, a2, -1, -1, 11);
  sub_607260(this + 34, v4, -1, 0, 1);
  sub_607280(this + 34);
  result = sub_47EF20((uint32_t *)*(this + 32), 4u, a2, -1, -1, 11);
  *(this + 21) = result;
  return result;
}



// ------------------------------------------------------------
// 0x64F2B0 CNTargetIt__vmt14 —— CNTargetIt__vmt14 生成槽（4938F0/491D00）
// ------------------------------------------------------------
char /*thiscall*/ CNTargetIt__vmt14(int this, char a2, int a3, int a4, int a5)
{
  char result; // al
  int v7; // eax

  result = a2;
  if ( a2 != 0 )
  {
    sub_4938F0(*(uint32_t *)(this + 172));
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 192))(*(uint32_t *)(this + 4));
    return sub_491D00(dword_79C0B0, a3, a4 - v7 - 5, 0.0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64F300 CNTargetIt__vmt84 —— CNTargetIt__vmt84 受击事件槽（15 行）
// ------------------------------------------------------------
char /*thiscall*/ CNTargetIt__vmt84(uint32_t *this, uint32_t *a2)
{
  char result; // al

  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 529);
  if ( result != 0 )
    return a2[2088] == *(this + 9);
  return result;
}



// ------------------------------------------------------------
// 0x64F340 sub_64F340 —— 目标查询（23 行）
// ------------------------------------------------------------
int /*thiscall*/ sub_64F340(int *this, const void *a2, unsigned int a3)
{
  int result; // eax
  signed int v4; // esi

  result = (int)this;
  if ( a2 != nullptr )
  {
    qmemcpy((void *)(*(this + 2) + *(this + 1)), a2, a3);
    v4 = a3 + *(this + 2);
    *(this + 2) = v4;
    result = *this;
    if ( v4 > *this )
      return off_77F3FC(aCriticalError_40, result);
  }
  return result;
}



// ------------------------------------------------------------
// 0x64F390 sub_64F390 —— 目标初始化（4920E0）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_64F390(int this)
{
  int v1; // edx
  int v2; // eax
  float v4; // [esp+0h] [ebp-4h]

  v1 = *(uint32_t *)(this + 160);
  if ( v1 != 0 )
    v2 = (*(uint32_t *)(this + 164) - v1) >> 2;
  else
    v2 = 0;
  v4 = (double)(unsigned int)v2 * 0.2 + 0.80000001;
  return sub_4920E0(*(uint32_t **)(this + 172), v4, v4);
}



// ------------------------------------------------------------
// 0x64F3E0 CNTargetIt__vmt24 —— CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605840/64F340/5C6A50/5C6A90/41C5A0/5DAE20/4E4A50）
// ------------------------------------------------------------
char /*thiscall*/ CNTargetIt__vmt24(int this, int a2, int *a3, unsigned int a4)
{
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  float *v8; // eax
  float v9; // eax
  float v10; // edx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // ebx
  int16_t *v21; // eax
  float v23; // [esp+0h] [ebp-28h]
  float v24; // [esp+10h] [ebp-18h] BYREF
  float v25; // [esp+14h] [ebp-14h]
  float v26; // [esp+18h] [ebp-10h]
  int v27; // [esp+1Ch] [ebp-Ch]
  int v28; // [esp+20h] [ebp-8h]
  int v29; // [esp+24h] [ebp-4h]

  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
  v6 = __RTDynamicCast(v5, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
  LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 308))(*(uint32_t *)(this + 4));
  if ( (uint8_t)v7 != 0 && v6 != 0 )
  {
    v7 = *(uint32_t *)(this + 36);
    if ( *(uint32_t *)(v6 + 8352) == v7 && v7 != 0 )
    {
      v8 = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
      LOBYTE(v7) = sub_4AED00(v8);
      if ( (uint8_t)v7 != 0 )
      {
        LOBYTE(v7) = a4;
        if ( (uint8_t)a4 == 0 )
        {
          v7 = __RTDynamicCast(
                 a2,
                 0,
                 &IRDCollisionObject `RTTI Type Descriptor',
                 &CNTemporaryHit `RTTI Type Descriptor',
                 0);
          if ( v7 == 0 )
          {
            v9 = *((float *)a3 + 1);
            v24 = *(float *)a3;
            v10 = *((float *)a3 + 2);
            v25 = v9;
            v11 = a3[3];
            v26 = v10;
            v12 = a3[4];
            v27 = v11;
            v13 = a3[5];
            v28 = v12;
            v29 = v13;
            v25 = (double)(rand() % 60 - 30) + v25;
            v14 = rand();
            v15 = *(uint32_t *)(this + 36);
            v26 = (double)(v14 % 60 - 30) + v26;
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 388))(v15);
            v17 = sub_47EFD0(*(char **)(this + 128), COERCE_FLOAT(3), *(uint32_t *)(this + 132), v16, v16, 11) - 100;
            v18 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 36) + 388))(*(uint32_t *)(this + 36));
            v19 = sub_47EFD0(*(char **)(this + 128), COERCE_FLOAT(7), *(uint32_t *)(this + 132), v18, v18, 0);
            a4 = 0;
            v20 = 100 * v19 / (v17 + 100);
            v21 = sub_605840(&a4, *(uint32_t *)(this + 4), (int *)&v24, 0);
            dword_78FE2C = 0;
            sub_64F340((int *)dword_78FE24, v21, a4);
            sub_5C6A50(1);
            sub_5C6A90(v17);
            v23 = (double)(unsigned int)sub_41C5A0(this + 156) * 100.0;
            sub_5DAE20(LODWORD(v23));
            LOBYTE(v7) = sub_4E4A50(
                           *(uint32_t *)(this + 36),
                           48011,
                           v20,
                           (uint64_t)v24,
                           (uint64_t)v25,
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
  return v7;
}



// ------------------------------------------------------------
// 0x64F600 CNTargetIt__vmt78 —— CNTargetIt__vmt78 生效槽（60FA60）
// ------------------------------------------------------------
int /*thiscall*/ CNTargetIt__vmt78(uint32_t *this, void *Block)
{
  int result; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529);
  if ( (uint8_t)result != 0 )
  {
    v4 = operator new(0x54u);
    if ( v4 != nullptr )
      v5 = sub_60FA60(v4, 0, 0);
    else
      v5 = nullptr;
    return (*(int (/*thiscall*/ **)(uint32_t *, void *, uint32_t, uint32_t, uint32_t, int, int))(*v5 + 56))(
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
int /*thiscall*/ sub_64F690(char *this)
{
  int v2; // ecx
  int v3; // eax
  char *v4; // edi
  char *v5; // ebx
  int v6; // ecx
  int result; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // edi
  int v16; // ebx
  int v17; // eax
  int v18; // ecx
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  float v25; // [esp+4h] [ebp-30h]
  float v26; // [esp+14h] [ebp-20h] BYREF
  float v27; // [esp+18h] [ebp-1Ch]
  float v28; // [esp+1Ch] [ebp-18h]
  int v29; // [esp+20h] [ebp-14h]
  int v30; // [esp+24h] [ebp-10h]
  int v31; // [esp+28h] [ebp-Ch]
  int v32; // [esp+2Ch] [ebp-8h] BYREF
  unsigned int v33; // [esp+30h] [ebp-4h]

  sub_64A790();
  v2 = *((uint32_t *)this + 9);
  if ( v2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 40))(v2, 17) == 0
    || (*(uint8_t (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 9) + 724))(*((uint32_t *)this + 9)) != 0 )
  {
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 76))(this, 0);
  }
  v3 = sub_699000((int)(this + 8));
  v4 = *((char **)this + 40);
  v32 = v3;
  if ( v4 != *((char **)this + 41) )
  {
    v5 = v4 + 4;
    do
    {
      if ( v32 < *(uint32_t *)v4 )
      {
        v4 += 4;
        v5 += 4;
      }
      else
      {
        memcpy_0(v4, v5, 4 * ((*((uint32_t *)this + 41) - (int)v5) >> 2));
        *((uint32_t *)this + 41) -= 4;
        sub_64F390(this);
      }
    }
    while ( v4 != *((char **)this + 41) );
  }
  v6 = *((uint32_t *)this + 40);
  if ( v6 == 0 || (*((uint32_t *)this + 41) - v6) >> 2 == 0 )
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 76))(this, 0);
  v8 = sub_699000((int)(this + 8));
  result = sub_6072C0(v8);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1) + 308))(*((uint32_t *)this + 1));
    if ( (uint8_t)result != 0 )
    {
      v9 = *((uint32_t *)this + 1);
      v26 = 0.0;
      v27 = 0.0;
      v28 = 0.0;
      v29 = 0;
      v30 = 0;
      v31 = 0;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 152))(v9);
      v11 = *((uint32_t *)this + 1);
      if ( v10 != 0 )
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 120))(v11) + 10;
      else
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 120))(v11) - 10;
      v13 = *((uint32_t *)this + 1);
      v33 = v12;
      v26 = (float)v12;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 124))(v13);
      v15 = *((uint32_t *)this + 1);
      v33 = v14;
      v27 = (float)v14;
      v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 192))(v15) / 2;
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 128))(v15);
      v18 = *((uint32_t *)this + 9);
      v33 = v17 + v16;
      v28 = (float)(v17 + v16);
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 388))(v18);
      v20 = sub_47EFD0(*((char **)this + 32), COERCE_FLOAT(2), *((uint32_t *)this + 33), v19, v19, 11) - 100;
      v21 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 9) + 388))(*((uint32_t *)this + 9));
      v22 = sub_47EFD0(*((char **)this + 32), COERCE_FLOAT(6), *((uint32_t *)this + 33), v21, v21, 0);
      v32 = 0;
      v23 = 100 * v22 / (v20 + 100);
      v24 = sub_605840(&v32, *((uint32_t *)this + 1), &v26, 0);
      dword_78FE2C = 0;
      sub_64F340(v24, v32);
      sub_5C6A50((int *)dword_78FE24, 1);
      sub_5C6A90(v20);
      v33 = sub_41C5A0(this + 156);
      v25 = (double)v33 * 100.0;
      sub_5DAE20(LODWORD(v25));
      return sub_4E4A50(
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
void /*thiscall*/ CNTargetIt__vmt1C(int this)
{
  CNRDAuraMaster__vmt1C(this);
  if ( *(uint32_t *)(this + 160) != 0 )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
}



// ------------------------------------------------------------
// 0x64F980 CNTargetIt__vmt20 —— CNTargetIt__vmt20 更新槽（15 行）
// ------------------------------------------------------------
void /*thiscall*/ CNTargetIt__vmt20(int this, uint32_t *a2)
{
  CNRDAuraMaster__vmt20((uint32_t *)this, a2);
  if ( *(uint32_t *)(this + 160) != 0 )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
}



// ------------------------------------------------------------
// 0x64F9D0 CNTargetIt__vmt7C —— CNTargetIt__vmt7C 失效槽（65 行）
// ------------------------------------------------------------
void /*thiscall*/ CNTargetIt__vmt7C(uint32_t *this, int a2)
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
  int v11; // ecx
  int v12; // ebx
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx

  if ( a2 != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v4 = *(uint32_t *)(v3 + 4);
      v5 = v4 != 0 ? (*(uint32_t *)(v3 + 8) - v4) >> 2 : 0;
      if ( (int)i >= v5 )
        break;
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
      v7 = *(uint32_t *)(v6 + 4);
      if ( v7 != 0 && i < (*(uint32_t *)(v6 + 8) - v7) >> 2 )
        v8 = *(uint32_t *)(v7 + 4 * i);
      else
        v8 = 0;
      if ( *(uint32_t *)(v8 + 4) == a2 )
      {
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
        v10 = *(uint32_t *)(v9 + 4);
        if ( v10 != 0 && i < (*(uint32_t *)(v9 + 8) - v10) >> 2 )
          v11 = *(uint32_t *)(v10 + 4 * i);
        else
          v11 = 0;
        v12 = *(this + 1);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 64))(v11) + 32) == v12 )
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 700))(a2);
          v14 = *(uint32_t *)(v13 + 4);
          if ( v14 != 0 && i < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
          {
            v15 = *(uint32_t **)(v14 + 4 * i);
            if ( v15 != nullptr && v15[16] == 22 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v15 + 76))(v15, 0);
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
uint32_t */*thiscall*/ sub_64FAC0(int this, int a2)
{
  int v3; // eax
  int v4; // eax
  int v5; // edx
  unsigned int v6; // edi
  int *v7; // ecx
  int v8; // eax
  unsigned int v9; // edi

  v3 = sub_699000(this + 8);
  v4 = a2 + v3;
  v5 = *(uint32_t *)(this + 160);
  a2 = v4;
  if ( v5 != 0 )
    v6 = (*(uint32_t *)(this + 164) - v5) >> 2;
  else
    v6 = 0;
  if ( v5 != 0 && v6 < (*(uint32_t *)(this + 168) - v5) >> 2 )
  {
    v7 = *(int **)(this + 164);
    *v7 = v4;
    *(uint32_t *)(this + 164) = v7 + 1;
  }
  else
  {
    sub_430C80(this + 156, *(uint32_t *)(this + 164), 1u, &a2);
  }
  v8 = *(uint32_t *)(this + 160);
  if ( v8 != 0 )
    v9 = (*(uint32_t *)(this + 164) - v8) >> 2;
  else
    v9 = 0;
  if ( v9 > sub_47E9D0(*(uint32_t **)(this + 128), 1u) )
  {
    memcpy_0(
      *(void **)(this + 160),
      (const void *)(*(uint32_t *)(this + 160) + 4),
      4 * ((*(uint32_t *)(this + 164) - (*(uint32_t *)(this + 160) + 4)) >> 2));
    *(uint32_t *)(this + 164) -= 4;
  }
  return sub_64F390(this);
}



// ------------------------------------------------------------
// 0x64FB80 sub_64FB80 —— 装载 Character/Mage/Effect/Animation/TargetIt.ani（42FCB0/431860/47E720）
// ------------------------------------------------------------
int /*thiscall*/ sub_64FB80(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int result; // eax

  v2 = sub_42FCB0(228);
  if ( v2 != 0 )
    v3 = sub_431860(v2, "Character/Mage/Effect/Animation/TargetIt.ani", 1);
  else
    v3 = 0;
  *(this + 43) = v3;
  result = sub_47E720(3, 0x32u);
  *(this + 32) = result;
  return result;
}



// ------------------------------------------------------------
// 0x64FC00 sub_64FC00 —— 目标受击（42AF90/657740）
// ------------------------------------------------------------
int /*thiscall*/ sub_64FC00(void ***this)
{
  int v2; // esi
  int result; // eax

  v2 = (int)*(this + 43);
  if ( v2 != 0 )
  {
    sub_42AF90(*(this + 43));
    result = sub_657740(v2, 228);
  }
  *(this + 43) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x64FC40 sub_64FC40 —— 18 行小函数
// ------------------------------------------------------------
int /*thiscall*/ sub_64FC40(int this)
{
  *(uint32_t *)(this + 80) = 0;
  *(uint8_t *)(this + 84) = 0;
  *(uint8_t *)(this + 85) = 0;
  *(uint32_t *)(this + 88) = -1;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 104) = 1;
  return 0;
}



// ------------------------------------------------------------
// 0x64FC60 CNSuplexed__vmt10 —— CNSuplexed__vmt10 过肩摔主流程（191 行：4938F0 目标 + 432E50 播报）
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_64FC60@<eax>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
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
  int v21; // ecx
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
  int v36; // [esp+Ch] [ebp-8h]
  int v37; // [esp+10h] [ebp-4h]

  result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 840))(*(uint32_t *)(a1 + 80));
  if ( result == (uint32_t *)19 )
  {
    v5 = *(int **)(a1 + 4);
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 840))(v5);
    if ( result == (uint32_t *)9 )
    {
      if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 236))(v5) == 1 )
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t))(*v5 + 228))(v5, 0, -1, 0);
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 200))(*(uint32_t *)(a1 + 80));
      v6 = result;
      if ( result != nullptr )
      {
        sub_4938F0((int)result);
        v7 = v6[37];
        v37 = v7;
        v8 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80), a2, a3);
        v35 = v8;
        if ( *(uint8_t *)(a1 + 85) == 0 )
          v35 = sub_432E50(v8);
        if ( v7 == *(uint32_t *)(a1 + 88) )
          goto LABEL_45;
        v9 = *(uint8_t *)(a1 + 85);
        v10 = 2 * (v9 != 0) + 2;
        if ( v7 < v10 )
        {
          *(uint32_t *)(a1 + 92) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80)) != 0
                               ? 60
                               : -60;
          *(uint32_t *)(a1 + 96) = -1;
          if ( 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) <= 0 )
            v11 = 0;
          else
            v11 = 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5);
          v12 = *(uint8_t *)(a1 + 85);
          *(uint32_t *)(a1 + 100) = v11;
          if ( v12 != 0 && v7 == 3 )
          {
            *(uint32_t *)(a1 + 100) = v11 + 8;
LABEL_44:
            *(uint32_t *)(a1 + 88) = v7;
LABEL_45:
            *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*v5 + 60))(v5) + 52) = v35;
            if ( *(uint8_t *)(a1 + 104) != 0 )
            {
              v26 = *v5;
              v36 = *(uint32_t *)(a1 + 80);
              v27 = (*(int (**)(void))(*(uint32_t *)v36 + 128))();
              v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v36 + 124))(v36, *(uint32_t *)(a1 + 100) + v27);
              v29 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v36 + 120))(v36, *(uint32_t *)(a1 + 96) + v28);
              (*(void (/*thiscall*/ **)(int *, int))(v26 + 112))(v5, *(uint32_t *)(a1 + 92) + v29);
            }
            (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 612))(v5, 1, 1);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(*v5 + 820))(v5, 0);
            result = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
            if ( result != nullptr )
            {
              v30 = (*(int (/*thiscall*/ **)(int *))(*v5 + 200))(v5);
              return sub_4938F0(v30);
            }
            return result;
          }
          if ( v7 != 0 )
            goto LABEL_44;
          v13 = *v5;
          v14 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 196))(v5, *(uint32_t *)(v14 + 12));
LABEL_43:
          v7 = v37;
          goto LABEL_44;
        }
        if ( v7 == v10 )
        {
          *(uint32_t *)(a1 + 92) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80)) != 0
                               ? 55
                               : -55;
          *(uint32_t *)(a1 + 96) = -1;
          if ( 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) <= 0 )
            *(uint32_t *)(a1 + 100) = 0;
          else
            *(uint32_t *)(a1 + 100) = 65 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5);
          goto LABEL_44;
        }
        if ( v7 == 2 * (v9 != 0) + 3 )
        {
          v33 = 25;
          v15 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 192))(*(uint32_t *)(a1 + 80));
          if ( (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5) >= v15 )
          {
            v18 = 55;
          }
          else
          {
            v16 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 192))(*(uint32_t *)(a1 + 80));
            v17 = (uint64_t)((double)(v16 - (*(int (/*thiscall*/ **)(int *))(*v5 + 192))(v5)) * 0.70721358);
            v18 = 55 - v17;
            v33 = v17 + 25;
          }
          if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80)) == 0 )
            v18 = -v18;
          *(uint32_t *)(a1 + 100) = v33;
          v19 = *(uint8_t *)(a1 + 85);
          *(uint32_t *)(a1 + 92) = v18;
          *(uint32_t *)(a1 + 96) = -1;
          v34 = 1061746115;
          if ( v19 == 0 )
            v34 = -1085737533;
        }
        else
        {
          if ( *(uint8_t *)(a1 + 84) == 0 )
          {
            if ( v7 != 2 * (v9 != 0) + 4 )
              goto LABEL_44;
            *(uint32_t *)(a1 + 92) = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(a1 + 80) + 152))(*(uint32_t *)(a1 + 80)) != 0
                                 ? -45
                                 : 45;
            *(uint32_t *)(a1 + 96) = -1;
            *(uint32_t *)(a1 + 100) = 0;
            v24 = *v5;
            v25 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
            (*(void (/*thiscall*/ **)(int *, uint32_t))(v24 + 196))(v5, *(uint32_t *)(v25 + 24));
            (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v5 + 272))(v5, 0, 0);
            goto LABEL_43;
          }
          if ( v7 > 2 * (v9 != 0) + 6 )
          {
            *(uint8_t *)(a1 + 104) = 0;
            goto LABEL_44;
          }
          v20 = 2 * (v9 != 0) + 5;
          v21 = *(uint32_t *)(a1 + 80);
          *(uint32_t *)(a1 + 92) = v37 != v20 ? -4 : 15;
          if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v21 + 152))(v21) == 0 )
            *(uint32_t *)(a1 + 92) = -*(uint32_t *)(a1 + 92);
          *(uint32_t *)(a1 + 96) = -1;
          *(uint32_t *)(a1 + 100) = -6;
          if ( v37 == v20 )
            LOBYTE(v35) = sub_432E50(v35);
          v22 = *v5;
          v23 = (*(int (/*thiscall*/ **)(int *))(*v5 + 688))(v5);
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v22 + 196))(v5, *(uint32_t *)(v23 + 24));
          v34 = 1057350484;
          if ( *(uint8_t *)(a1 + 85) == 0 )
            v34 = -1090133164;
        }
        (*(void (/*thiscall*/ **)(int *, int, int))(*v5 + 272))(v5, 1, v34);
        goto LABEL_43;
      }
    }
  }
  return result;
}

