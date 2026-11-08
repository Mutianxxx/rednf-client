// ============================================================
// 【40JP逆向源代码工程】game/equ_buff.cpp
// 模块: 装备 .equ 解析（avatar）+ Buff 图标 + 外观/演出族
// 来源: work/dump_misca.txt  区块: 0x4B0000-0x4C0000
// 层级: L2 转写层 → L1 精修层（会话精修：职业表定案 + 功能族分区 + 字符串证据）
// 函数数: 256
//
// ★ 装备(.equ)解析链：sub_4BA8A0(job,growtype) → sub_4B0080 查 .equ 路径
//   （character/<职业>/growtype/<转职>.equ，输出 byte_9A0468）→ sub_442D00 打开 →
//   sub_4B5FD0 逐部件块解析装载（部件记录 sub_4B2970 / 部件组 sub_4B52F0/sub_4B5740）；
//   失败 "CHARACTER CREATE FAIL! JOB %d" / "CHARACTER CREATE FAIL! FILENAME[%s]"。
//   部件图像路径 → 资源 id 由 sub_4BC700 完成（anim_parser 的 [IMAGE] 也走它）。
//
// ★ sub_4B0080 职业表定案：
//   job0=swordman: 1=weaponmaster 3=berserker 4=asura
//   job1=fighter:  2=striker 3=streetfighter 4=grabbler
//   job2=gunner:   1=ranger 2=launcher 4=spitfire
//   job3=mage:     2=summoner 3=battlemage
//   sub_4B0210 = 裸身身体资源 id 表（growtype{1,3,4,5,8}×4 职业，未命中 0xFFFF）。
//
// ★ Buff 图标：sub_4B4170 装配 Common/CommonEffect/BuffIcon.img（3 槽 + 图标动画
//   BUFF_LEAP/BUFF_INTUP）；sub_4B49B0 技能使用调试 "-> ENUM_CMDPACKET_USE_SKILL"。
//   演出族锚点：升级 LevelNormalizeLibra.ani/LEVELING_FLASH、霸体 SuperArmorEffect.ani、
//   蓄气 BuffChargeGlow.ani、地面循环 RUN_GRASS/SOIL/STONE_LOOP、摆摊驴 Donkey_*/Store。
//
// 分区（按 VA 升序）：
//   §A 0x4B0080-0x4B0210  ★职业/转职表（.equ 路径 + 裸身资源 id）
//   §B 0x4B0210-0x4B12B0  外观状态位族（+48..54）
//   §C 0x4B12B0-0x4B15E0  事件分发
//   §D 0x4B15E0-0x4B1C80  avatar 部件管理
//   §E 0x4B1E50-0x4B2780  渲染主驱动/部件集
//   §F 0x4B2780-0x4B3820  avatar 配置记录（+40..56 字符串组）与容器
//   §G 0x4B3820-0x4B49B0  avatar 变更/比较（[none]）
//   §H 0x4B49B0-0x4B59A0  ★Buff 图标/职业特效（BuffIcon.img、ENUM_CMDPACKET_USE_SKILL）
//   §I 0x4B59A0-0x4B5FD0  角色动画包装器
//   §J 0x4B5FD0-0x4B7110  ★.equ 部件解析装载（CHARACTER CREATE FAIL）
//   §K 0x4B7110-0x4B89D0  升级/结算演出（LevelNormalizeLibra、PVP_KO）
//   §L 0x4B89D0-0x4B9280  跑步地面循环 + 蓄气/霸体特效
//   §M 0x4B9280-0x4BA8A0  奖励演出族（SpUp/Dice/金币/道具/FP_UP/ENERGY_CHARGE）
//   §N 0x4BA8A0-0x4BAED0  ★角色创建入口（job→.equ）
//   §O 0x4BAED0-0x4BC900  部件路径/名称解析（sub_4BC700 路径→id）
//   §P 0x4BC900-0x4BCE50  部件集合管理
//   §Q 0x4BCE50-0x4BE170  摆摊驴 Donkey 族
//   §R 0x4BE170-0x4BFFA0  杂项/容器收尾
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// §A 0x4B0080-0x4B0210  ★职业/转职表（.equ 路径 + 裸身资源 id）
// ============================================================
// ------------------------------------------------------------
// 0x4B0080 sub_4B0080 —— ★职业/转职 → .equ 路径表（输出 byte_9A0468）
//   job0=swordman: 1=weaponmaster 3=berserker 4=asura；job1=fighter: 2=striker
//   3=streetfighter 4=grabbler；job2=gunner: 1=ranger 2=launcher 4=spitfire；
//   job3=mage: 2=summoner 3=battlemage。未命中返回 nullptr。
// ------------------------------------------------------------
char */*cdecl*/ sub_4B0080(int nArg1, int nArg2)
{
  const char *v3; // esi

  if ( nArg1 != 0 )
  {
    if ( nArg1 != 1 )
    {
      if ( nArg1 == 2 )
      {
        if ( nArg2 != 1 )
        {
          if ( nArg2 == 2 )
          {
            strcpy(byte_9A0468, "character/gunner/growtype/launcher.equ");  // job2=gunner growtype2
            return byte_9A0468;
          }
          if ( nArg2 == 4 )
          {
            strcpy(byte_9A0468, "character/gunner/growtype/spitfire.equ");  // job2=gunner growtype4
            return byte_9A0468;
          }
          return nullptr;
        }
        v3 = "character/gunner/growtype/ranger.equ";  // job2=gunner growtype1
      }
      else
      {
        if ( nArg1 != 3 )
          return nullptr;
        if ( nArg2 == 3 )
        {
          strcpy(byte_9A0468, "character/mage/growtype/battlemage.equ");  // job3=mage growtype3
          return byte_9A0468;
        }
        if ( nArg2 != 2 )
          return nullptr;
        v3 = "character/mage/growtype/summoner.equ";  // job3=mage growtype2
      }
      qmemcpy(byte_9A0468, v3, 0x25u);
      return byte_9A0468;
    }
    switch ( nArg2 )
    {
      case 2:
        strcpy(byte_9A0468, "character/fighter/growtype/striker.equ");  // job1=fighter growtype2
        return byte_9A0468;
      case 3:
        strcpy(byte_9A0468, "character/fighter/growtype/streetfighter.equ");  // job1=fighter growtype3
        return byte_9A0468;
      case 4:
        strcpy(byte_9A0468, "character/fighter/growtype/grabbler.equ");  // job1=fighter growtype4
        return byte_9A0468;
      default:
        break;
    }
  }
  else
  {
    switch ( nArg2 )
    {
      case 1:
        strcpy(byte_9A0468, "character/swordman/growtype/weaponmaster.equ");  // job0=swordman growtype1
        return byte_9A0468;
      case 3:
        strcpy(byte_9A0468, "character/swordman/growtype/berserker.equ");  // job0=swordman growtype3
        return byte_9A0468;
      case 4:
        strcpy(byte_9A0468, "character/swordman/growtype/asura.equ");  // job0=swordman growtype4
        return byte_9A0468;
      default:
        break;
    }
  }
  return nullptr;
}



// ============================================================
// §B 0x4B0210-0x4B12B0  外观状态位族（+48..54）
// ============================================================
// ------------------------------------------------------------
// 0x4B0210 sub_4B0210 —— ★裸身身体资源 id 表（job×growtype）
//   growtype{1,3,4,5,8}：job0=39400/40600/41000/41800/27900，job1=43400/44600/45000/
//   45800/29000，job2=47400/48600/49000/49800/31300；未命中 0xFFFF。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B0210(int nArg1, int nArg2)
{
  int result; // eax

  switch ( nArg1 )
  {
    case 0:
      switch ( nArg2 )
      {
        case 1:
          return 39400;  // job0 裸身 id
        case 3:
          return 40600;  // job0 裸身 id
        case 4:
          return 41000;
        case 5:
          return 41800;
        case 8:
          return 27900;
        default:
          break;
      }
      return 0xFFFF;
    case 1:
      switch ( nArg2 )
      {
        case 1:
          return 43400;
        case 3:
          return 44600;
        case 4:
          return 45000;
        case 5:
          return 45800;
        case 8:
          return 29000;
        default:
          break;
      }
      return 0xFFFF;
    case 2:
      switch ( nArg2 )
      {
        case 1:
          return 47400;
        case 3:
          return 48600;
        case 4:
          return 49000;
        case 5:
          return 49800;
        case 8:
          return 31300;
        default:
          break;
      }
      return 0xFFFF;
    default:
      break;
  }
  if ( nArg1 != 3 )
    return 0xFFFF;
  switch ( nArg2 )
  {
    case 1:
      return 51400;
    case 3:
      return 52600;
    case 4:
      return 53000;
    case 5:
      return 53800;
    default:
      break;
  }
  result = 33300;
  if ( nArg2 != 8 )
    return 0xFFFF;
  return result;
}



// ------------------------------------------------------------
// 0x4B0340 sub_4B0340
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0340(uint32_t *this, int nArg2)
{
  int fld_e1787; // eax

  fld_e1787 = *(this + 1787);
  if ( fld_e1787 == 4 )
    return 0;
  else
    return sub_47E720(fld_e1787, nArg2);
}



// ------------------------------------------------------------
// 0x4B0370 sub_4B0370
// ------------------------------------------------------------
char /*thiscall*/ sub_4B0370(uint32_t *this)
{
  int fld_e50; // eax
  int fld_e1659; // edi
  int fld_e1675; // edx
  int fld_e1674; // eax
  char v6; // bl
  char v8; // [esp+4h] [ebp-8h]
  int fld_e1660; // [esp+8h] [ebp-4h]

  LOBYTE(fld_e50) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)fld_e50 == 0 )
    return fld_e50;
  fld_e50 = *(this + 50);
  if ( fld_e50 != 0 )
    return fld_e50;
  if ( *((uint8_t *)this + 6634) == 0 )
  {
    LOBYTE(fld_e50) = *((uint8_t *)this + 6635);
    if ( (uint8_t)fld_e50 == 0 )
      return fld_e50;
  }
  fld_e1659 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1132))(this, 0);
  fld_e1675 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1132))(this, 1);
  fld_e1660 = fld_e1675;
  if ( *((uint8_t *)this + 6634) == 0 )
  {
    fld_e1659 = *(this + 1659);
    goto LABEL_16;
  }
  if ( *((uint8_t *)this + 6635) == 0 )
    goto LABEL_16;
  fld_e1674 = *(this + 1674);
  if ( fld_e1674 != 0 )
  {
    if ( fld_e1674 != 1 )
      goto LABEL_16;
    if ( fld_e1675 == 4 )
    {
      fld_e1675 = *(this + 1675);
      fld_e1660 = fld_e1675;
      goto LABEL_16;
    }
LABEL_13:
    *(this + 1674) = -1;
    goto LABEL_16;
  }
  if ( fld_e1659 != 4 )
    goto LABEL_13;
  fld_e1659 = *(this + 1675);
LABEL_16:
  if ( *((uint8_t *)this + 6635) == 0 )
  {
    fld_e1660 = *(this + 1660);
    fld_e1675 = fld_e1660;
  }
  v8 = 1;
  if ( fld_e1659 == 4 || fld_e1675 == 4 )
    v8 = 0;
  fld_e50 = *(this + 1659);
  v6 = 1;
  if ( fld_e50 == 4 || *(this + 1660) == 4 )
    v6 = 0;
  if ( fld_e1659 != fld_e50 || v8 != v6 )
  {
    LOBYTE(fld_e50) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, char))(*this + 892))(this, 0, fld_e1659, v8);
    fld_e1675 = fld_e1660;
  }
  if ( fld_e1675 != *(this + 1660) || v8 != v6 )
    LOBYTE(fld_e50) = (*(int (/*thiscall*/ **)(uint32_t *, int, int, char))(*this + 892))(this, 1, fld_e1675, v8);
  return fld_e50;
}



// ------------------------------------------------------------
// 0x4B04B0 sub_4B04B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B04B0(void *this, int nArg2)
{
  void *v3; // eax
  int v4; // eax
  int v5; // esi

  v3 = &unk_9A0310;
  if ( nArg2 != 0 )
    v3 = &unk_9A0320;
  v4 = sub_4BF3D0(v3);
  v5 = 4;
  if ( v4 == 2 )
  {
    v5 = 0;
  }
  else if ( v4 == 3 )
  {
    v5 = 1;
  }
  else if ( v4 != 0 )
  {
    if ( v4 == 1 )
      v5 = 3;
  }
  else
  {
    v5 = 2;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 15) != 0 )
    return sub_432E50(v5);
  else
    return v5;
}



// ------------------------------------------------------------
// 0x4B0530 sub_4B0530
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0530(uint32_t *this, uint32_t *uArg2)
{
  int result; // eax

  result = sub_4D6E40(uArg2);
  if ( uArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);
  }
  if ( (uint32_t *)*(this + 1972) == uArg2 )
    *(this + 1972) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4B0580 sub_4B0580
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0580(uint32_t *this)
{
  int fld_e1625; // eax
  int v2; // eax

  fld_e1625 = *(this + 1625);
  if ( fld_e1625 == 0 )
    return -1;
  v2 = (*(int (**)(void))(*(uint32_t *)fld_e1625 + 172))();
  return sub_41A5E0(v2 + 4);
}



// ------------------------------------------------------------
// 0x4B05B0 sub_4B05B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4B05B0(uint32_t *this)
{
  *(this + 2001) = 1;
}



// ------------------------------------------------------------
// 0x4B05C0 sub_4B05C0
// ------------------------------------------------------------
char /*thiscall*/ sub_4B05C0(uint8_t *this, char pszArg2)
{
  *(this + 8052) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4B05D0 sub_4B05D0 —— 外观状态切换（+52；sub_48F690/578E80 场景联动）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B05D0(uint8_t *this, char pszArg2)
{
  int v2; // esi
  int v3; // ebx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  uint8_t *pObj; // edi
  int v14; // [esp+Ch] [ebp-Ch]
  int v15; // [esp+14h] [ebp-4h]
  int v16; // [esp+14h] [ebp-4h]
  int v17; // [esp+20h] [ebp+8h]

  v2 = 0;
  v14 = 16;
  v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);
  if ( v3 == 0 )
    return 0;
  v5 = 0;
  while ( 1 )
  {
    v6 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v6 == 4 )
    {
      v7 = sub_48F690((uint32_t *)dword_99FEC0, v5);
LABEL_9:
      v2 = v7;
      goto LABEL_10;
    }
    if ( v6 == 6 || v6 == 7 )
    {
      v7 = sub_578E80(v5);
      goto LABEL_9;
    }
LABEL_10:
    if ( v2 != 0 && *(uint32_t *)(v2 + 196) == *(uint32_t *)(*(uint32_t *)(v3 + 132) + 52) )
      break;
    if ( ++v5 >= 8 )
    {
      v8 = 0;
      goto LABEL_15;
    }
  }
  v8 = v5;
LABEL_15:
  v17 = 2 * (pszArg2 == 0) - 1;
  while ( 2 )
  {
    v8 += v17;
    if ( v8 < 0 )
    {
      v15 = 7;
      goto LABEL_20;
    }
    if ( v8 >= 8 )
    {
      v15 = 0;
LABEL_20:
      v8 = v15;
    }
    v9 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v9 == 4 )
    {
      v10 = sub_48F690((uint32_t *)dword_99FEC0, v8);
      goto LABEL_26;
    }
    if ( v9 == 6 || v9 == 7 )
    {
      v10 = sub_578E80(v8);
LABEL_26:
      v2 = v10;
    }
    if ( v2 == 0 || (pObj = *(uint8_t **)(v2 + 196)) == nullptr || pObj == this || pObj[8052] != 0 )
    {
LABEL_33:
      if ( v14-- <= 0 )
        return 0;
      continue;
    }
    break;
  }
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 7 )
  {
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 376))(pObj) == v16 )
      return *(uint32_t *)(v2 + 196);
    goto LABEL_33;
  }
  return *(uint32_t *)(v2 + 196);
}



// ------------------------------------------------------------
// 0x4B0780 sub_4B0780
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0780(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  *(this + 2014) = nArg2;
  *(this + 2015) = nArg3;
  *(this + 2016) = nArg4;
  return nArg4;
}



// ------------------------------------------------------------
// 0x4B07B0 sub_4B07B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4B07B0(uint8_t *this)
{
  char result; // al
  int pThis_1F98; // ecx

  result = 1;
  if ( *(this + 8100) != 1 )
  {
    *(this + 8100) = 1;
    pThis_1F98 = (int)(this + 8088);
    *(uint8_t *)(pThis_1F98 + 13) = 0;
    *(uint8_t *)(pThis_1F98 + 14) = 0;
    return sub_698F90(pThis_1F98, 300, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B07E0 sub_4B07E0
// ------------------------------------------------------------
bool /*cdecl*/ sub_4B07E0(
        int a1,
        int *a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13)
{
  int v14; // ebx
  int v15; // eax
  int v16; // edx
  int v17; // edi
  signed int v18; // ebx
  signed int v19; // esi
  bool result; // al
  int v21; // [esp+Ch] [ebp-Ch]
  int v22; // [esp+10h] [ebp-8h]
  int v23; // [esp+14h] [ebp-4h]
  signed int v24; // [esp+20h] [ebp+8h]
  float v25; // [esp+24h] [ebp+Ch]

  v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a2 + 340))(a2) + 32);
  v22 = v14;
  v23 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a2 + 340))(a2) + 36);
  v21 = 3 * (*(int (/*thiscall*/ **)(int *))(*a2 + 192))(a2) / 4;
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
  v16 = *a2;
  if ( v15 == 1 )
    v17 = v14 + (*(int (/*thiscall*/ **)(int *))(v16 + 120))(a2) + a11 / 2 - a3;
  else
    v17 = a3 + v14 + a11 / 2 - (*(int (/*thiscall*/ **)(int *))(v16 + 120))(a2);
  v18 = (*(int (/*thiscall*/ **)(int *))(*a2 + 124))(a2) - a4;
  v24 = (*(int (/*thiscall*/ **)(int *))(*a2 + 128))(a2) - a5;
  result = false;
  if ( v17 >= 0 && v17 <= a11 + a10 + 2 * v22 )
  {
    v25 = (float)v17;
    v19 = v23 + a12 / 2 - (uint64_t)(sub_405420(a6 + a8) * (double)dword_7930D4[0] * v25 * -0.0099999998);
    if ( v18 >= (int)(a12 / -2
                    - (uint64_t)(sub_405420(a6 - a8) * (double)dword_7930D4[0] * v25 * -0.0099999998)
                    - v23)
      && v18 <= v19
      && v24 >= (int)((uint64_t)(sub_405420((a7 - a9 + 360) % 360) * v25) - a13 / 2 - v21)
      && v24 <= (int)(a13 / 2 + (uint64_t)(sub_405420((a7 + a9 + 360) % 360) * v25)) )
    {
      return true;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B09B0 sub_4B09B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B09B0(uint8_t *this, int nArg2)
{
  int v3; // eax
  int dword_8F85202; // ebx
  int v5; // edi
  int result; // eax
  int v7; // edi
  int pThis_30; // eax
  int v9; // edi
  int pThis_34; // eax

  v3 = sub_48FCA0();
  dword_8F85202 = dword_8F8520;
  v5 = v3;
  if ( *(uint32_t *)(sub_656710() + 4 * v3) == -1 || (result = *(uint32_t *)(dword_8F85202 + 4 * v5 + 1048648)) == 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);
    *((uint32_t *)this + 2053) = nArg2;
    if ( (uint8_t)result != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 38, 1);
      v7 = *(uint32_t *)dword_8F8520;
      pThis_30 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, pThis_30);
      v9 = *(uint32_t *)dword_8F8520;
      pThis_34 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, pThis_34);
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 32))(*(this + 8212));
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0A60 sub_4B0A60
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0A60(int this)
{
  if ( *(uint32_t *)(this + 8212) == 1 )
    return sub_4B09B0((uint8_t *)this, 0);
  else
    return sub_4B09B0((uint8_t *)this, 1);
}



// ------------------------------------------------------------
// 0x4B0A80 sub_4B0A80
// ------------------------------------------------------------
int /*usercall*/ sub_4B0A80@<eax>(uint8_t *uArg1@<ecx>, int nArg2@<edi>)
{
  uint8_t *pObj; // esi
  int result; // eax
  int v4; // ebx
  int v5; // eax
  int v6; // esi
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int i; // esi

  pObj = uArg1;
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  v4 = *(uint32_t *)(result + 104);
  if ( v4 == 0 )
    return result;
  if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 0, nArg2) != 0 )
  {
    v5 = sub_4B05D0(pObj, 1);
    goto LABEL_19;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 1) != 0 )
  {
    v5 = sub_4B05D0(pObj, 0);
    goto LABEL_19;
  }
  v6 = 0;
  v7 = 0;
  while ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, v7 + 81) == 0 )
  {
LABEL_16:
    if ( ++v7 >= 8 )
    {
      pObj = uArg1;
      goto LABEL_21;
    }
  }
  v8 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v8 == 4 )
  {
    v9 = sub_48F690((uint32_t *)dword_99FEC0, v7);
LABEL_12:
    v6 = v9;
    goto LABEL_13;
  }
  if ( v8 == 6 )
  {
    v9 = sub_578E80(v7);
    goto LABEL_12;
  }
LABEL_13:
  if ( v6 == 0 )
    goto LABEL_16;
  v10 = *(uint32_t *)(v6 + 196);
  if ( v10 == 0 || *(uint8_t *)(v10 + 8052) != 0 )
    goto LABEL_16;
  v5 = *(uint32_t *)(v6 + 196);
  pObj = uArg1;
LABEL_19:
  if ( v5 != 0 )
    sub_424A40(*(uint32_t **)(v4 + 132), v5);
LABEL_21:
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 13) != 0 )
    sub_424530(*(uint32_t *)(v4 + 132), 2.0, 100, 100, -1, -1, -1, 1);
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 724))(pObj);
  if ( (uint8_t)result == 0 )
  {
    for ( i = 0; i < 4; ++i )
      result = sub_4BF300(i, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0BC0 sub_4B0BC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0BC0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 152;
  return result;
}



// ------------------------------------------------------------
// 0x4B0BE0 sub_4B0BE0
// ------------------------------------------------------------
int /*cdecl*/ sub_4B0BE0(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 25) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x4B0C00 sub_4B0C00
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0C00(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 25) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;
  *(uint32_t *)(result + 4) = pArg2[1];
  fld_e1 = *(this + 1);
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )
  {
    *(uint32_t *)(fld_e1 + 4) = result;
    *(uint32_t *)(result + 8) = pArg2;
    pArg2[1] = result;
  }
  else
  {
    v5 = (uint32_t *)pArg2[1];
    if ( pArg2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else
      *v5 = result;
    *(uint32_t *)(result + 8) = pArg2;
    pArg2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0C60 sub_4B0C60
// ------------------------------------------------------------
int */*thiscall*/ sub_4B0C60(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 25) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 25) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 25) == 0; result = (int *)result[1] )
      {
        if ( *this != result[2] )
          break;
        *this = (int)result;
      }
      *this = (int)result;
    }
    else
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 25) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 25) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0CC0 sub_4B0CC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0CC0(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 25) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 25) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 25) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 25) == 0 );
        if ( *(uint8_t *)(result + 25) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 25) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0D20 sub_4B0D20
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4B0D20(void *this)
{
  int pThis_3D8; // [esp+8h] [ebp-4h]

  pThis_3D8 = sub_41A5E0((unsigned int)this + 984);
  return (uint64_t)((double)pThis_3D8 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 998)));
}



// ------------------------------------------------------------
// 0x4B0D60 sub_4B0D60
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4B0D60(uint8_t *this)
{
  char *pThis_4; // esi

  pThis_4 = this + 4;
  *(this + 8) = 0;
  *((uint32_t *)this + 1) = &off_6C2B88;
  *((uint32_t *)this + 3) = 0;
  *(this + 16) = 1;
  *(this + 18) = 0;
  *(this + 17) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 5) = 0;
  *(uint32_t *)this = 0;
  sub_699070(2);  // 【clock_bind_domain(clk, newDomainId)】
  pThis_4[13] = 0;
  pThis_4[14] = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 10) = 0;
  *(this + 36) = 1;
  return this;
}



// ------------------------------------------------------------
// 0x4B0DE0 sub_4B0DE0
// ------------------------------------------------------------
void /*thiscall*/ sub_4B0DE0(int this)
{
  *(uint32_t *)(this + 4) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8) = 0;
}



// ------------------------------------------------------------
// 0x4B0DF0 sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
// ------------------------------------------------------------
void /*cdecl*/ sub_4B0DF0(int *pDwArg1, int *pDwArg2)
{
  int *pDwArg12; // ecx
  int *pDwArg22; // ebx
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // edx
  unsigned int v10; // edx
  int v11; // edi
  int v12; // eax
  int v13; // [esp+0h] [ebp-4h]

  pDwArg12 = pDwArg1;
  if ( pDwArg1 == nullptr )
    return;
  pDwArg22 = pDwArg2;
  if ( pDwArg2 == nullptr )
    return;
  v4 = pDwArg1[11];
  if ( v4 != 0 )
    v5 = (pDwArg1[12] - v4) / 88;
  else
    v5 = 0;
  v6 = pDwArg2[11];
  if ( v6 != 0 )
    v6 = (pDwArg2[12] - v6) / 88;
  if ( v5 >= v6 )
  {
    v7 = pDwArg2[11];
    if ( v7 == 0 )
    {
      v8 = 0;
      goto LABEL_16;
    }
    v9 = pDwArg2[12];
  }
  else
  {
    v7 = pDwArg1[11];
    if ( v7 == 0 )
    {
      v8 = 0;
      goto LABEL_16;
    }
    v9 = pDwArg1[12];
  }
  v10 = (int)((uint64_t)(780903145LL * (v9 - v7)) >> 32) >> 4;
  v8 = v10 + (v10 >> 31);
LABEL_16:
  v11 = 0;
  if ( v8 > 0 )
  {
    while ( 1 )
    {
      v13 = sub_4924C0(pDwArg12, v11);
      v12 = sub_4924C0(pDwArg22, v11++);
      *(uint32_t *)(v12 + 48) = *(uint32_t *)(v13 + 48);
      if ( v11 >= v8 )
        break;
      pDwArg12 = pDwArg1;
      pDwArg22 = pDwArg2;
    }
  }
}



// ------------------------------------------------------------
// 0x4B0EC0 sub_4B0EC0
// ------------------------------------------------------------
int /*cdecl*/ sub_4B0EC0(int nArg1, int nArg2)
{
  int result; // eax
  int v3; // eax

  result = sub_4CE8A0(nArg1);
  if ( result != 0 )
  {
    v3 = 28 * nArg2 + result + 4;
    if ( *(uint32_t *)(v3 + 24) < 0x10u )
      return v3 + 4;
    else
      return *(uint32_t *)(v3 + 4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0F00 sub_4B0F00
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0F00(int *this, int pArg2)
{
  int result; // eax
  int v4; // ecx
  int v5; // edi
  int v6; // eax

  result = *(this + pArg2 + 1617);
  if ( result == 0 )
  {
    result = sub_4B0210(*(this + 1787), pArg2);
    if ( result != 0xFFFF )
    {
      v5 = *this;
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1084))(this, v4);
      return (*(int (/*thiscall*/ **)(int *, int))(v5 + 784))(this, v6);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0F50 sub_4B0F50
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0F50(int *this, int pArg2)
{
  void *fld_e1787; // eax
  int pObj; // eax
  int v5; // eax
  int v6; // eax

  fld_e1787 = (void *)sub_4B0210(*(this + 1787), pArg2);
  if ( *(this + pArg2 + 1879) == 0 && fld_e1787 != (void *)0xFFFF )
  {
    pObj = sub_522300(fld_e1787, 0, 0, 0, -1, 1);
    *(this + pArg2 + 1879) = pObj;
    if ( pObj != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);
      v6 = sub_41A5E0(v5 + 18);
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + pArg2 + 1879) + 192))(*(this + pArg2 + 1879), v6);
    }
  }
  return *(this + pArg2 + 1879);
}



// ------------------------------------------------------------
// 0x4B0FD0 sub_4B0FD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B0FD0(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 25) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);
  fld_e1 = *(this + 1);
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )
  {
    *(uint32_t *)(fld_e1 + 4) = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);
    if ( pArg2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B1030 sub_4B1030
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4B1030(uint8_t *this)
{
  *(uint32_t *)this = &IRDAppendage::`vftable';
  sub_4B0D60(this + 4);
  sub_5F6610(this);
  sub_5F6750(this);
  return this;
}



// ------------------------------------------------------------
// 0x4B10B0 sub_4B10B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B10B0(uint32_t *this, int nArg2)
{
  *(this + 12) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4B10C0 sub_4B10C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B10C0(uint32_t *this)
{
  return *(this + 12);
}



// ------------------------------------------------------------
// 0x4B10D0 sub_4B10D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4B10D0(uint8_t *this, char pszArg2)
{
  *(this + 52) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4B10E0 sub_4B10E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4B10E0(uint8_t *this)
{
  return *(this + 52);
}



// ------------------------------------------------------------
// 0x4B10F0 sub_4B10F0
// ------------------------------------------------------------
char /*thiscall*/ sub_4B10F0(uint8_t *this)
{
  return *(this + 53);
}



// ------------------------------------------------------------
// 0x4B1100 sub_4B1100
// ------------------------------------------------------------
char /*thiscall*/ sub_4B1100(uint8_t *this)
{
  return *(this + 54);
}



// ------------------------------------------------------------
// 0x4B1110 sub_4B1110
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1110(uint32_t *this)
{
  return *(this + 14);
}



// ------------------------------------------------------------
// 0x4B1120 sub_4B1120
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1120(uint32_t *this)
{
  int result; // eax

  *this = &IRDAppendage::`vftable';
  result = sub_5F6640();
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4B1170 sub_4B1170
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B1170(uint32_t *Block, char pszArg2)
{
  sub_4B1120(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4B11A0 sub_4B11A0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4B11A0(uint8_t *this, int nArg2)
{
  sub_4B1030(this);
  *(uint32_t *)this = &CNArmorMastery::`vftable';
  sub_5F6E50(this);
  sub_5F6ED0(nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x4B1200 sub_4B1200
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1200(void *this)
{
  sub_5F66C0();  // 【IRDAppendage__vmt4】
  return sub_5F6FB0(this);
}



// ------------------------------------------------------------
// 0x4B1220 sub_4B1220
// ------------------------------------------------------------
void */*thiscall*/ sub_4B1220(void *Block, char pszArg2)
{
  sub_4B1250();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4B1250 sub_4B1250
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1250(uint32_t *this)
{
  int result; // eax

  *this = &CNArmorMastery::`vftable';
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ============================================================
// §C 0x4B12B0-0x4B15E0  事件分发
// ============================================================
// ------------------------------------------------------------
// 0x4B12B0 sub_4B12B0 —— 事件分发（音效 sub_422E70/43BEE0、sub_4BF300）
// ------------------------------------------------------------
char /*userpurge*/ sub_4B12B0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, char pszArg3)
{
  char v4; // cl
  char result; // al
  unsigned int v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // edi
  int v9; // eax
  uint32_t *v10; // edi
  int v11; // eax
  uint32_t *v12; // edi
  int v13; // eax
  uint32_t *v14; // esi
  const char *v15; // eax
  uint32_t *v16; // eax
  int i; // edi
  int v18; // eax
  uint32_t *v19; // esi
  const char *v20; // eax
  char Buffer[112]; // [esp+4h] [ebp-74h] BYREF
  int dword_796E502; // [esp+74h] [ebp-4h]

  v4 = *((uint8_t *)pArg1 + 8052);
  dword_796E502 = dword_796E50;
  result = pszArg3;
  if ( v4 != pszArg3 )
  {
    *((uint8_t *)pArg1 + 8052) = pszArg3;
    v6 = pArg1[78];
    if ( pszArg3 != 0 )
    {
      if ( v6 < 0x10 )
        v7 = pArg1 + 73;
      else
        v7 = (uint32_t *)pArg1[73];
      off_77F3FC(aS_5, v7);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg2) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
        v8 = *((uint32_t **)dword_8F8528 + 7);
        v9 = sub_422E70(858);
        sub_43BEE0(v8, v9, -13444046, 0, -1);
        v10 = *((uint32_t **)dword_8F8528 + 7);
        v11 = sub_422E70(859);
        sub_43BEE0(v10, v11, -13444046, 0, -1);
        v12 = *((uint32_t **)dword_8F8528 + 7);
        v13 = sub_422E70(860);
        sub_43BEE0(v12, v13, -13444046, 0, -1);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 2, 0, 0, 0, 0, 0);
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*pArg1 + 112))(pArg1, -10000, -10000, 0);
      if ( pArg1[78] < 0x10u )
        v14 = pArg1 + 73;
      else
        v14 = (uint32_t *)pArg1[73];
      v15 = (const char *)sub_422E70(861);
      sprintf(Buffer, v15, v14);
      return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
    }
    else
    {
      if ( v6 < 0x10 )
        v16 = pArg1 + 73;
      else
        v16 = (uint32_t *)pArg1[73];
      off_77F3FC(aS_6, v16);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*pArg1 + 108))(pArg1, pArg1[2014], pArg1[2015], pArg1[2016]);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
        for ( i = 0; i < 4; ++i )
          sub_4BF300(i, 1);
        v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);
        sub_424A40(*(uint32_t **)(v18 + 132), (int)pArg1);
      }
      if ( pArg1[78] < 0x10u )
        v19 = pArg1 + 73;
      else
        v19 = (uint32_t *)pArg1[73];
      v20 = (const char *)sub_422E70(862);
      sprintf(Buffer, v20, v19);
      return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B1550 sub_4B1550
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_4B1550(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)
{
  unsigned int **pDwArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pDwArg32 = pDwArg3;
  v6[4] = v6;
  v6[3] = pDwArg3;
  v7 = 0;
  while ( pDwArg1 != pDwArg2 )
  {
    LOBYTE(v7) = 1;
    if ( pDwArg32 != nullptr )
    {
      *pDwArg32 = nullptr;
      sub_41B0D0(pDwArg32, pDwArg1);
    }
    ++pDwArg32;
    LOBYTE(v7) = 0;
    ++pDwArg1;
  }
  return pDwArg32;
}



// ============================================================
// §D 0x4B15E0-0x4B1C80  avatar 部件管理
// ============================================================
// ------------------------------------------------------------
// 0x4B15E0 sub_4B15E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B15E0(uint32_t *this, int pArg2)
{
  uint32_t *pThis_1; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_1 = this + 1;
  *(this + 1) = *(uint32_t *)pArg2;
  sub_4B1630(pArg2 + 4);
  pThis_1[8] = *(uint32_t *)(pArg2 + 32);
  *((uint8_t *)pThis_1 + 36) = *(uint8_t *)(pArg2 + 36);
  pThis_1[10] = *(uint32_t *)(pArg2 + 40);
  return pThis_1;
}



// ------------------------------------------------------------
// 0x4B1630 sub_4B1630
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1630(int this, int pArg2)
{
  *(uint8_t *)(this + 4) = *(uint8_t *)(pArg2 + 4);
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);
  *(uint8_t *)(this + 12) = *(uint8_t *)(pArg2 + 12);
  *(uint8_t *)(this + 13) = *(uint8_t *)(pArg2 + 13);
  *(uint8_t *)(this + 14) = *(uint8_t *)(pArg2 + 14);
  *(uint32_t *)(this + 16) = *(uint32_t *)(pArg2 + 16);
  *(uint32_t *)(this + 20) = *(uint32_t *)(pArg2 + 20);
  *(uint32_t *)(this + 24) = *(uint32_t *)(pArg2 + 24);
  return this;
}



// ------------------------------------------------------------
// 0x4B1670 sub_4B1670 —— avatar 集合初始化（+252；sub_4F3460/47E8C0/6569D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1670(uint8_t *this)
{
  int v2; // eax
  int v3; // edi
  int pThis_2E4; // eax
  int v5; // edi
  int pThis_2F4; // eax
  int v7; // ebx
  int pThis_428; // edi
  int pThis_2E42; // eax
  int v10; // ebx
  int pThis_4282; // edi
  int pThis_2F42; // eax
  int v13; // edx

  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 12))(this);
  if ( (uint8_t *)dword_8F7C04 == this )
  {
    sub_4F3460();
    sub_47E8C0();
  }
  *(this + 7729) = 0;
  sub_6569D0(this + 124);
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 780))(this);
  sub_53FDD0(*((uint32_t *)this + 1574));
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1156))(this);
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  v2 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v2 == 4 || v2 == 6 )
  {
    v3 = *(uint32_t *)this;
    pThis_2E4 = (*(int (/*stdcall*/ **)(uint32_t, int))(*(uint32_t *)this + 740))(0, 1);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v3 + 732))(this, pThis_2E4);
    v5 = *(uint32_t *)this;
    pThis_2F4 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 756))(this, 1);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v5 + 748))(this, pThis_2F4);
  }
  else
  {
    v7 = *(uint32_t *)this;
    pThis_428 = (*(int (/*stdcall*/ **)(uint32_t, int))(*(uint32_t *)this + 1064))(0, 1);
    pThis_2E42 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 740))(this);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v7 + 732))(this, pThis_2E42 * pThis_428 / 100);
    v10 = *(uint32_t *)this;
    pThis_4282 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1064))(this, 1);
    pThis_2F42 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 756))(this);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v10 + 748))(this, pThis_2F42 * pThis_4282 / 100);
  }
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 720))(this, 0);
  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 604))(this, 1);
  v13 = *(uint32_t *)this;
  *(this + 7093) = 0;
  (*(void (/*thiscall*/ **)(uint8_t *, int, int))(v13 + 252))(this, 3, -1);
  return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);
}



// ------------------------------------------------------------
// 0x4B17B0 sub_4B17B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B17B0(uint32_t *this, int pArg2)
{
  int pArg22; // ebx
  int pObj; // edi
  int v6; // ebx
  int i; // edi
  int pObj2; // [esp+8h] [ebp-4h]

  pArg22 = pArg2;
  if ( *(this + pArg2 + 1617) == 0 )
    return 0;
  pObj = sub_52DBC0(pArg2);  // 【IRDActiveObject__vmt314】
  pObj2 = pObj;
  if ( pObj != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1152))(this);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1156))(this);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      sub_47E4F0();
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 248))(pObj);
    for ( i = *(uint32_t *)(v6 + 4); i != *(uint32_t *)(v6 + 8); i += 124 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int))(*this + 1076))(this, this + 1803, i + 72);
    sub_484D00((int *)dword_8F852C);
    pArg22 = pArg2;
    pObj = pObj2;
  }
  return pObj == *(this + pArg22 + 1879) ? 0 : pObj;
}



// ------------------------------------------------------------
// 0x4B1870 sub_4B1870
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1870(uint32_t *this)
{
  unsigned int fld_e1908; // eax
  int v3; // edx

  if ( *(this + 1625) != 0
    && (fld_e1908 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this), (v3 = *(this + 1908)) != 0)
    && (*(this + 1909) - v3) >> 2 > fld_e1908 )
  {
    return *(uint32_t *)(*(this + 1908) + 4 * fld_e1908);
  }
  else
  {
    return 4;
  }
}



// ------------------------------------------------------------
// 0x4B18C0 sub_4B18C0
// ------------------------------------------------------------
bool /*thiscall*/ sub_4B18C0(uint32_t *this)
{
  unsigned int fld_e1912; // eax
  int v3; // edx
  bool result; // al

  result = *(this + 1625) != 0
        && (fld_e1912 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this), (v3 = *(this + 1912)) != 0)
        && (*(this + 1913) - v3) >> 2 > fld_e1912
        && *(uint32_t *)(*(this + 1912) + 4 * fld_e1912) != 0;
  return result;
}



// ------------------------------------------------------------
// 0x4B1910 sub_4B1910
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1910(uint32_t *this)
{
  unsigned int fld_e1916; // eax
  int v3; // edx

  if ( *(this + 1625) != 0
    && (fld_e1916 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this), (v3 = *(this + 1916)) != 0)
    && (*(this + 1917) - v3) >> 2 > fld_e1916 )
  {
    return *(uint32_t *)(*(this + 1916) + 4 * fld_e1916);
  }
  else
  {
    return 0;
  }
}



// ------------------------------------------------------------
// 0x4B1950 sub_4B1950
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1950(uint32_t *this)
{
  int fld_e1954; // eax
  int *v4; // edi
  int v5; // ebx
  int v6; // edx
  int v7; // edi
  int v8; // edi
  const CHAR *v9; // eax
  int fld_e1962; // eax
  int v11; // edi
  int v12; // ebx
  char *v13; // eax
  int v14; // esi
  int v15; // edi
  int v16; // eax
  int v17; // [esp+4h] [ebp-4h]
  int fld_e1961; // [esp+4h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    fld_e1954 = sub_4CE8A0(*(this + 1954));
    if ( fld_e1954 != 0 )
    {
      v4 = *(int **)(fld_e1954 + 124);
      v17 = *v4;
      if ( v4 != nullptr && (unsigned int)((*(uint32_t *)(fld_e1954 + 128) - (int)v4) >> 2) > 1 )
        v5 = v4[1];
      else
        v5 = 0;
      v6 = *(uint32_t *)(fld_e1954 + 140);
      v7 = 0;
      if ( v6 != 0 && (*(uint32_t *)(fld_e1954 + 144) - v6) >> 2 != 0 )
      {
        v8 = *(uint32_t *)dword_8F84E4;
        v9 = sub_41ACF0(*(unsigned int ***)(fld_e1954 + 140));
        v7 = (*(int (/*thiscall*/ **)(int, const CHAR *))(v8 + 4))(dword_8F84E4, v9);
      }
      if ( *(this + 1953) == 2 )
        fld_e1962 = 0;
      else
        fld_e1962 = *(this + 1962);
      fld_e1961 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
              this,
              v17,
              v5,
              v7,
              0,
              *(this + 1961),
              0,
              fld_e1962,
              4,
              0,
              0,
              0);
      if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 177) > 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1312))(this, 177) != 0 )
      {
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 388))(this);
        v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 177);
        v13 = (char *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 177);
        v14 = sub_47EFD0(v13, 0.0, v12, v11, v11, 11);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 17, 2);
        v15 = *(uint32_t *)dword_8F8520;
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
        (*(void (/*thiscall*/ **)(int, int))(v15 + 36))(dword_8F8520, v16);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, fld_e1961);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v14);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      }
      return fld_e1961;
    }
    else
    {
      off_77F3FC((char *)&byte_6F5FDC, *(this + 1954));
      return -1;
    }
  }
  else
  {
    off_77F3FC(aMaster);
    return -1;
  }
}



// ------------------------------------------------------------
// 0x4B1B20 sub_4B1B20
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1B20(uint32_t *this)
{
  int v2; // edx

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 12))(this);
  if ( (uint32_t *)dword_8F7C04 == this )
  {
    sub_4F3460();
    sub_47E8C0();
  }
  sub_6569D0(this + 31);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 780))(this);
  sub_53FDD0(*(this + 1574));
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1156))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 604))(this, 1);
  v2 = *this;
  *((uint8_t *)this + 7093) = 0;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v2 + 252))(this, 3, -1);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);
}



// ------------------------------------------------------------
// 0x4B1BA0 sub_4B1BA0
// ------------------------------------------------------------
int **/*thiscall*/ sub_4B1BA0(int **this, int **pDwArg2, uint32_t *uArg3)
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);
  v4 = (int *)fld_e1[1];
  while ( *((uint8_t *)v4 + 25) == 0 )
  {
    if ( v4[3] >= *uArg3 )
    {
      fld_e1 = v4;
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( fld_e1 == *(this + 1) || *uArg3 < fld_e1[3] )
  {
    *pDwArg2 = *(this + 1);
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = fld_e1;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4B1C10 sub_4B1C10
// ------------------------------------------------------------
void /*thiscall*/ sub_4B1C10(int this)
{
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 300;
}



// ------------------------------------------------------------
// 0x4B1C40 sub_4B1C40
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1C40(uint32_t *this, int nArg2)
{
  int pThis_1FE; // eax

  pThis_1FE = nArg2;
  if ( nArg2 == -1 )
    pThis_1FE = sub_41A5E0((unsigned int)this + 510);
  return sub_41A5E0(*(this + 79) + 14 * (pThis_1FE - 1));
}



// ------------------------------------------------------------
// 0x4B1C80 sub_4B1C80 —— 部位参数组下发（+40/+44/+56 → sub_4B0DF0 重载动画）
// ------------------------------------------------------------
void /*cdecl*/ sub_4B1C80(int pArg1, int pArg2, int **pDwArg3, int **pDwArg4)
{
  int v6; // eax
  int **v7; // ebx
  unsigned int i; // ebx
  int v9; // ecx
  int v10; // ecx
  unsigned int j; // ebx
  int v12; // ecx
  int v13; // ecx
  int **v14; // esi
  int v15; // eax
  int **v16; // edi
  int v17; // [esp+14h] [ebp+8h]
  int v18; // [esp+18h] [ebp+Ch]
  int v19; // [esp+18h] [ebp+Ch]

  sub_4B0DF0(*(int **)pArg1, *(int **)pArg2);
  sub_4B0DF0(*(int **)(pArg1 + 4), *(int **)(pArg2 + 4));
  sub_4B0DF0(*(int **)(pArg1 + 8), *(int **)(pArg2 + 8));
  v6 = pArg2 - pArg1;
  v7 = (int **)(pArg1 + 12);
  v17 = pArg2 - pArg1;
  v18 = 2;
  while ( 1 )
  {
    sub_4B0DF0(*v7, *(int **)((char *)v7 + v6));
    ++v7;
    if ( --v18 == 0 )
      break;
    v6 = v17;
  }
  sub_4B0DF0(*(int **)(pArg1 + 20), *(int **)(pArg2 + 20));
  sub_4B0DF0(*(int **)(pArg1 + 24), *(int **)(pArg2 + 24));
  sub_4B0DF0(*(int **)(pArg1 + 28), *(int **)(pArg2 + 28));
  sub_4B0DF0(*(int **)(pArg1 + 32), *(int **)(pArg2 + 32));
  for ( i = 0; ; ++i )
  {
    v9 = *(uint32_t *)(pArg1 + 40);
    if ( v9 == 0 )
      break;
    if ( i >= (*(uint32_t *)(pArg1 + 44) - v9) >> 2 )
      break;
    v10 = *(uint32_t *)(pArg2 + 40);
    if ( v10 == 0 || i >= (*(uint32_t *)(pArg2 + 44) - v10) >> 2 )
      break;
    sub_4B0DF0(*(int **)(4 * i + *(uint32_t *)(pArg1 + 40)), *(int **)(4 * i + *(uint32_t *)(pArg2 + 40)));
  }
  for ( j = 0; ; ++j )
  {
    v12 = *(uint32_t *)(pArg1 + 56);
    if ( v12 == 0 )
      break;
    if ( j >= (*(uint32_t *)(pArg1 + 60) - v12) >> 2 )
      break;
    v13 = *(uint32_t *)(pArg2 + 56);
    if ( v13 == 0 || j >= (*(uint32_t *)(pArg2 + 60) - v13) >> 2 )
      break;
    sub_4B0DF0(*(int **)(4 * j + *(uint32_t *)(pArg1 + 56)), *(int **)(4 * j + *(uint32_t *)(pArg2 + 56)));
  }
  sub_4B0DF0(*pDwArg3, *pDwArg4);
  v14 = pDwArg3 + 1;
  v15 = (char *)pDwArg4 - (char *)pDwArg3;
  v16 = pDwArg4 + 5;
  v19 = 4;
  while ( 1 )
  {
    sub_4B0DF0(*v14, *(int **)((char *)v14 + v15));
    sub_4B0DF0(v14[4], *v16);
    ++v14;
    ++v16;
    if ( --v19 == 0 )
      break;
    v15 = (char *)pDwArg4 - (char *)pDwArg3;
  }
  sub_4B0DF0(pDwArg3[9], pDwArg4[9]);
  sub_4B0DF0(pDwArg3[10], pDwArg4[10]);
  sub_4B0DF0(pDwArg3[11], pDwArg4[11]);
  sub_4B0DF0(pDwArg3[12], pDwArg4[12]);
}



// ============================================================
// §E 0x4B1E50-0x4B2780  渲染主驱动/部件集
// ============================================================
// ------------------------------------------------------------
// 0x4B1E50 sub_4B1E50 —— ★外观渲染主驱动（帧推进 sub_4938F0、+52/+56 槽、sub_424760 提交、sub_42FDA0 变换）
// ------------------------------------------------------------
int /*userpurge*/ sub_4B1E50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3, int pArg4, int nArg5, int nArg6)
{
  int v7; // edi
  int v8; // eax
  int result; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edi
  unsigned int v17; // ebx
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // eax
  uint32_t *v22; // ecx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  unsigned int v26; // eax
  int v27; // edi
  int v28; // eax
  int v29; // [esp-20h] [ebp-28h]
  int v30; // [esp-8h] [ebp-10h]
  int v31; // [esp-8h] [ebp-10h]
  int v32; // [esp-8h] [ebp-10h]
  int v33; // [esp-4h] [ebp-Ch]
  int v34; // [esp-4h] [ebp-Ch]

  if ( (uint8_t)nArg3 != 0 )
  {
    sub_58E550(nArg3, pArg4, nArg5, nArg6);  // 【IRDActiveObject__vmt144】
    if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 && (uint32_t *)dword_8F7C04 != pArg1 )
    {
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 && (uint8_t)sub_48F620(dword_99FEC0) != 0 )
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 376))(pArg1) == 1 )
          v10 = sub_418DD0(16);
        else
          v10 = sub_418DD0(17);
        v29 = v10;
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 192))(pArg1);
        v12 = pArg4 - 33;
      }
      else
      {
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1216))(pArg1);
        v29 = sub_418DD0(v13 + 8);
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 192))(pArg1);
        v12 = pArg4 - 16;
      }
      sub_424760(dword_79C0B0, v12, nArg5 - v11 - 40, v29, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1);
      if ( (uint8_t)result == 0 )
      {
        v30 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 832))(pArg1);
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
        v15 = sub_429830(v14);
        sub_42FDA0(nArg2, (int)pArg1, pArg4, nArg5, (int)pArg1, v15, v30);
        sub_424680((int)&pArg4, (int)&nArg5, 0.0, 0.0);
        nArg6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 192))(pArg1);
        v16 = nArg5 - (uint64_t)((double)nArg6 * *(float *)&dword_77F6DC) - 55;
        nArg6 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 172);
        v17 = *(uint32_t *)(sub_418DD0(20) + 20);
        v18 = sub_418DD0(20);
        sub_43B560(pArg4 - (v17 >> 1), v16, v18, 1065353216, 1065353216, 0, -1, 1333788672, 1333788672);
        v19 = pArg4 - (*(uint32_t *)(sub_418DD0(21) + 20) >> 1);
        v31 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1);
        v20 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 736))(pArg1);
        v21 = sub_423A80(0, 74, v20, v31);
        v22 = (uint32_t *)dword_79C0B0;
        *(uint32_t *)(dword_79C0B0 + 56) = v19 + v21;
        v22[12] = 0;
        v22[13] = 0;
        v22[15] = 480;
        v23 = sub_418DD0(21);
        sub_40FC80(v19, v16 + 2, v23);
        result = sub_488670(dword_79C0B0);
      }
    }
    else
    {
      v32 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 832))(pArg1);
      v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
      v25 = sub_429830(v24);
      sub_42FDA0(nArg2, (int)pArg1, pArg4, nArg5, (int)pArg1, v25, v32);
      result = pArg1[1940];
      if ( result != 4 && result != *(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 100) )
      {
        v26 = sub_699000((int)(pArg1 + 16));  // 【clock_now(clk)】
        result = sub_418DD0(((v26 / 0xFA) & 1) + 2 * pArg1[1940] + 75);
        if ( result != 0 )
          result = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(
                     result,
                     pArg4 + 10,
                     nArg5 - pArg1[40] - 10,
                     dword_79C0B0);
      }
    }
    v27 = pArg1[30];
    if ( v27 != 0 )
    {
      if ( *(uint32_t *)(v27 + 148) == -1 )
        sub_4938F0(pArg1[30]);
      v34 = *(uint8_t *)(v27 + 95);
      v28 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 792))(pArg1, 9);
      return sub_432600(1, pArg4, nArg5, pArg1, v28, 0, v34);
    }
  }
  else
  {
    v7 = pArg1[30];
    if ( v7 != 0 )
    {
      if ( *(uint32_t *)(v7 + 148) == -1 )
        sub_4938F0(pArg1[30]);
      v33 = *(uint8_t *)(v7 + 95);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 792))(pArg1, 9);
      sub_432600(0, pArg4, nArg5, pArg1, v8, 0, v33);
    }
    return sub_58E550(0, pArg4, nArg5, nArg6);  // 【IRDActiveObject__vmt144】
  }
  return result;
}


// ------------------------------------------------------------
// 0x4B2230 sub_4B2230
// ------------------------------------------------------------
int /*thiscall*/ sub_4B2230(int **this, int nArg2)
{
  int *v4; // [esp+4h] [ebp-4h] BYREF

  sub_4B1BA0(this + 1854, &v4, &nArg2);
  if ( v4 == *(this + 1855) )
    return 0;
  else
    return v4[5];
}



// ------------------------------------------------------------
// 0x4B2270 sub_4B2270
// ------------------------------------------------------------
int /*thiscall*/ sub_4B2270(uint32_t *this)
{
  uint32_t *fld_e1855; // ecx
  uint32_t *pThis_6512; // eax
  int v4; // esi
  int result; // eax
  int pObj2; // ecx
  int pObj; // ebx
  int v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // esi
  bool v11; // zf
  char *v12; // ebx
  char *v13; // ebx
  int *v14; // eax
  int v15; // esi
  int v16; // eax
  int v17; // ebx
  int v18; // eax
  int v19; // ecx
  bool v20; // cc
  char v21[4]; // [esp+Ch] [ebp-28h] BYREF
  int v22; // [esp+10h] [ebp-24h] BYREF
  int v23; // [esp+14h] [ebp-20h]
  int v24; // [esp+18h] [ebp-1Ch]
  uint32_t *v25; // [esp+1Ch] [ebp-18h]
  uint32_t *pThis_651; // [esp+20h] [ebp-14h] BYREF
  int i; // [esp+24h] [ebp-10h]
  int v28; // [esp+28h] [ebp-Ch]
  uint32_t *v29; // [esp+2Ch] [ebp-8h]
  char *v30; // [esp+30h] [ebp-4h]

  fld_e1855 = (uint32_t *)*(this + 1855);
  pThis_6512 = (uint32_t *)*fld_e1855;
  pThis_651 = (uint32_t *)*fld_e1855;
  if ( pThis_651 != fld_e1855 )
  {
    do
    {
      pThis_6512[5] = pThis_6512[4];
      sub_4B0C60(&pThis_651);
      pThis_6512 = pThis_651;
    }
    while ( pThis_651 != (uint32_t *)*(this + 1855) );
  }
  v4 = 0;
  v23 = 0;
  pThis_651 = this + 1617;
  do
  {
    result = (int)pThis_651;
    pObj2 = *pThis_651;
    v28 = *pThis_651;
    if ( v28 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 200))(pObj2);
      if ( (uint8_t)result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1084))(this, v4);
        v28 = result;
      }
      pObj = v28;
      if ( v28 != 0 )
      {
        for ( i = 0; i < 2; ++i )
        {
          if ( i != 0 )
          {
            result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 224))(pObj);
            if ( (uint8_t)result == 0 )
              break;
            v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 228))(pObj);
          }
          else
          {
            v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);
          }
          v9 = (uint32_t *)(v8 + 892);
          v25 = v9;
          v24 = 2;
          do
          {
            v10 = (uint32_t *)*(v9 - 1);
            v11 = v10 == (uint32_t *)*v9;
            v29 = v10;
            if ( !v11 )
            {
              v12 = (char *)v10 + 18;
              v30 = (char *)v10 + 18;
              do
              {
                if ( *v10 == 4 || *v10 == *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this) )
                {
                  v13 = v12 - 14;
                  v22 = sub_41A5E0(v13);
                  v14 = (int *)sub_4B1BA0(v21, &v22);
                  v15 = *v14;
                  if ( *v14 != *(this + 1855) )
                  {
                    v16 = sub_41A5E0(v13);
                    v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, v16);
                    v22 = sub_41A5E0(v30);
                    v18 = sub_47DCC0(v17);
                    if ( v22 + *(uint32_t *)(v15 + 20) >= v18 )
                      v19 = sub_47DCC0(v17);
                    else
                      v19 = sub_41A5E0(v30) + *(uint32_t *)(v15 + 20);
                    *(uint32_t *)(v15 + 20) = v19;
                  }
                  v10 = v29;
                }
                v9 = v25;
                v10 += 8;
                v12 = v30 + 32;
                v11 = v10 == (uint32_t *)*v25;
                v29 = v10;
                v30 += 32;
              }
              while ( !v11 );
              pObj = v28;
            }
            v9 += 4;
            v11 = v24 == 1;
            v25 = v9;
            --v24;
          }
          while ( !v11 );
          result = i + 1;
        }
      }
    }
    v4 = v23 + 1;
    v20 = ++v23 < 18;
    ++pThis_651;
  }
  while ( v20 );
  return result;
}


// ------------------------------------------------------------
// 0x4B2440 sub_4B2440
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_4B2440(uint32_t *this, unsigned int uArg2)
{
  int fld_e1625; // esi
  int v5; // eax
  int v6; // ecx
  unsigned int uArg22; // edi
  int v8; // eax
  int v9; // eax
  int v10; // eax
  unsigned int v11; // eax
  int fld_e1904; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // eax

  fld_e1625 = *(this + 1625);
  if ( fld_e1625 == 0 )
    return (const CHAR *)off_791BBC[0];
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 172))(fld_e1625);
  v6 = *(uint32_t *)(v5 + 52);
  uArg22 = uArg2;
  v8 = v5 + 48;
  if ( v6 != 0 && (*(uint32_t *)(v8 + 8) - v6) >> 2 > uArg2 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 172))(fld_e1625);
    if ( (uint8_t)sub_42FD40(szPassword) != 0 )
    {
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 172))(fld_e1625);
      return sub_41ACF0((unsigned int **)(4 * uArg2 + *(uint32_t *)(v9 + 52)));
    }
    uArg22 = uArg2;
  }
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 172))(fld_e1625);
  v11 = sub_41A5E0(v10 + 4);
  fld_e1904 = *(this + 1904);
  if ( fld_e1904 != 0
    && (*(this + 1905) - fld_e1904) >> 4 > v11
    && (v13 = 16 * v11, v14 = *(uint32_t *)(v13 + fld_e1904 + 4), v15 = fld_e1904 + v13, v14 != 0)
    && (*(uint32_t *)(v15 + 8) - v14) >> 2 > uArg22 )
  {
    return sub_41ACF0((unsigned int **)(v14 + 4 * uArg22));
  }
  else
  {
    return (const CHAR *)off_791BBC[0];
  }
}



// ------------------------------------------------------------
// 0x4B2530 sub_4B2530
// ------------------------------------------------------------
double /*thiscall*/ sub_4B2530(uint32_t *this)
{
  unsigned int fld_e1920; // eax
  int v3; // edx

  if ( *(this + 1625) != 0
    && (fld_e1920 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this), (v3 = *(this + 1920)) != 0)
    && (*(this + 1921) - v3) >> 2 > fld_e1920 )
  {
    return *(float *)(*(this + 1920) + 4 * fld_e1920);
  }
  else
  {
    return 0.0;
  }
}



// ------------------------------------------------------------
// 0x4B2580 sub_4B2580
// ------------------------------------------------------------
int */*cdecl*/ sub_4B2580(
        int *a1,
        int *a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15)
{
  int v15; // edi
  int v16; // eax
  unsigned int v17; // edx
  int v18; // ecx
  int *v19; // esi
  int64_t v20; // rax
  int v21; // edi
  int *v22; // esi
  int v23; // edx
  int *v24; // ecx
  int v25; // ecx
  int v26; // eax
  int v27; // edi
  int v28; // edi
  int v29; // ebx
  int v30; // eax
  int v31; // edi
  double v33; // [esp+8h] [ebp-14h]
  int *v34; // [esp+Ch] [ebp-10h]
  int v35; // [esp+10h] [ebp-Ch]
  int v36; // [esp+14h] [ebp-8h]
  unsigned int v37; // [esp+18h] [ebp-4h]

  *a1 = 0;
  *a2 = 0;
  v34 = nullptr;
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 80))(a3);
  v16 = *(uint32_t *)(v15 + 120);
  v35 = v15;
  if ( v16 != 0 )
    v36 = (*(uint32_t *)(v15 + 124) - v16) >> 2;
  else
    v36 = 0;
  v17 = 0;
  v37 = 0;
  if ( v36 <= 0 )
    return nullptr;
  while ( 1 )
  {
    v18 = *(uint32_t *)(v15 + 120);
    if ( v18 != 0 && v17 < (*(uint32_t *)(v15 + 124) - v18) >> 2 )
      v19 = *(int **)(v18 + 4 * v17);
    else
      v19 = nullptr;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v19 + 40))(v19, 17) != 0
      && (uint8_t)sub_4E4630(v19) != 0 )
    {
      v20 = (*(int (/*thiscall*/ **)(int *))(*v19 + 120))(v19) - a4;
      v21 = (HIDWORD(v20) ^ v20) - HIDWORD(v20);
      if ( (a11 == -1 || v21 < a11) && sub_4B07E0(a3, v19, a4, a5, a6, a7, a8, a9, a10, a12, a13, a14, a15) )
      {
        a11 = v21;
        v34 = v19;
      }
      v15 = v35;
    }
    if ( (int)++v37 >= v36 )
      break;
    v17 = v37;
  }
  v22 = v34;
  if ( v34 != nullptr && a11 != 0 )
  {
    v23 = *v34;
    v24 = v34;
    v33 = (double)a11;
    v25 = -a7
        - (uint64_t)(atan2(
                               (double)((*(int (/*thiscall*/ **)(int *))(v23 + 124))(v24) - a5)
                             * 100.0
                             / (double)dword_7930D4[0]
                             / v33,
                               1.0)
                           * -57.29577951308232);
    v26 = -a9;
    v27 = v25;
    if ( v25 <= -a9 )
      v27 = -a9;
    if ( v27 >= a9 )
    {
      v26 = a9;
    }
    else if ( v25 > v26 )
    {
      v26 = v25;
    }
    *a1 = v26;
    v28 = 2 * (*(int (/*thiscall*/ **)(int *))(*v22 + 192))(v22) / 3 - a6;
    v29 = -a8
        - (uint64_t)(atan2((double)((*(int (/*thiscall*/ **)(int *))(*v22 + 128))(v22) + v28) / v33, 1.0)
                           * -57.29577951308232);
    v30 = -a10;
    v31 = v29;
    if ( v29 <= -a10 )
      v31 = -a10;
    if ( v31 >= a10 )
    {
      v30 = a10;
    }
    else if ( v29 > v30 )
    {
      *a2 = v29;
      return v22;
    }
    *a2 = v30;
  }
  return v22;
}


// ============================================================
// §F 0x4B2780-0x4B3820  avatar 配置记录（+40..56 字符串组）与容器
// ============================================================
// ------------------------------------------------------------
// 0x4B2780 sub_4B2780
// ------------------------------------------------------------
void /*thiscall*/ sub_4B2780(uint32_t *this)
{
  int fld_e2000; // edi
  int v3; // edx
  void *v4; // eax
  int v5; // [esp-Ch] [ebp-30h]
  int v6; // [esp-8h] [ebp-2Ch]
  int v7; // [esp-4h] [ebp-28h]
  uint8_t v8[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v10; // [esp+20h] [ebp-4h]

  fld_e2000 = *(uint32_t *)*(this + 2000);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e2000 + 40))(*(this + 2000));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2000) + 92))(*(this + 2000), v8);
  v3 = *this;
  v10 = 0;
  v4 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint8_t *))(v3 + 80))(this, 2, 0, v8);
  sub_4600B0(v4, v5, v6, v7);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x4B2820 sub_4B2820
// ------------------------------------------------------------
char */*thiscall*/ sub_4B2820(char *this, int pArg2)
{
  uint32_t *pThis_30; // ecx

  *(uint32_t *)this = *(uint32_t *)pArg2;
  *((uint32_t *)this + 1) = *(uint32_t *)(pArg2 + 4);
  *((uint32_t *)this + 2) = *(uint32_t *)(pArg2 + 8);
  *((uint32_t *)this + 3) = *(uint32_t *)(pArg2 + 12);
  *(this + 16) = *(uint8_t *)(pArg2 + 16);
  *(uint16_t *)(this + 17) = *(uint16_t *)(pArg2 + 17);
  *(this + 19) = *(uint8_t *)(pArg2 + 19);
  *((uint32_t *)this + 5) = *(uint32_t *)(pArg2 + 20);
  *((uint32_t *)this + 6) = *(uint32_t *)(pArg2 + 24);
  *((uint32_t *)this + 7) = *(uint32_t *)(pArg2 + 28);
  *((uint32_t *)this + 8) = *(uint32_t *)(pArg2 + 32);
  *((uint32_t *)this + 9) = *(uint32_t *)(pArg2 + 36);
  *((uint32_t *)this + 10) = *(uint32_t *)(pArg2 + 40);
  *((uint32_t *)this + 11) = *(uint32_t *)(pArg2 + 44);
  pThis_30 = this + 48;
  *pThis_30 = *(uint32_t *)(pArg2 + 48);
  pThis_30[1] = *(uint32_t *)(pArg2 + 52);
  pThis_30[2] = *(uint32_t *)(pArg2 + 56);
  *((uint32_t *)this + 15) = *(uint32_t *)(pArg2 + 60);
  *((uint32_t *)this + 16) = *(uint32_t *)(pArg2 + 64);
  *((uint32_t *)this + 17) = *(uint32_t *)(pArg2 + 68);
  *((uint32_t *)this + 18) = *(uint32_t *)(pArg2 + 72);
  *((uint32_t *)this + 19) = *(uint32_t *)(pArg2 + 76);
  *(this + 80) = *(uint8_t *)(pArg2 + 80);
  *(this + 81) = *(uint8_t *)(pArg2 + 81);
  *(this + 82) = *(uint8_t *)(pArg2 + 82);
  *((uint32_t *)this + 21) = *(uint32_t *)(pArg2 + 84);
  *((uint32_t *)this + 22) = *(uint32_t *)(pArg2 + 88);
  *((uint32_t *)this + 29) = 15;
  *((uint32_t *)this + 28) = 0;
  *(this + 96) = 0;
  sub_4014D0((size_t *)this + 23, (size_t *)(pArg2 + 92), 0, 0xFFFFFFFF);
  *((uint32_t *)this + 30) = *(uint32_t *)(pArg2 + 120);
  *((uint32_t *)this + 31) = *(uint32_t *)(pArg2 + 124);
  *(this + 128) = *(uint8_t *)(pArg2 + 128);
  *((uint32_t *)this + 33) = *(uint32_t *)(pArg2 + 132);
  *((uint32_t *)this + 34) = *(uint32_t *)(pArg2 + 136);
  *(this + 140) = *(uint8_t *)(pArg2 + 140);
  *(this + 141) = *(uint8_t *)(pArg2 + 141);
  *((uint32_t *)this + 36) = *(uint32_t *)(pArg2 + 144);
  *((uint32_t *)this + 37) = *(uint32_t *)(pArg2 + 148);
  return this;
}



// ------------------------------------------------------------
// 0x4B2970 sub_4B2970
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B2970(uint32_t *this, int pArg2)
{
  *this = *(uint32_t *)pArg2;
  *(this + 1) = *(uint32_t *)(pArg2 + 4);
  *(this + 2) = *(uint32_t *)(pArg2 + 8);
  *(this + 3) = *(uint32_t *)(pArg2 + 12);
  *((uint8_t *)this + 16) = *(uint8_t *)(pArg2 + 16);
  *((uint8_t *)this + 17) = *(uint8_t *)(pArg2 + 17);
  *((uint8_t *)this + 18) = *(uint8_t *)(pArg2 + 18);
  *((uint8_t *)this + 19) = *(uint8_t *)(pArg2 + 19);
  *(this + 5) = *(uint32_t *)(pArg2 + 20);
  *(this + 6) = *(uint32_t *)(pArg2 + 24);
  *(this + 7) = *(uint32_t *)(pArg2 + 28);
  *(this + 8) = *(uint32_t *)(pArg2 + 32);
  *(this + 9) = *(uint32_t *)(pArg2 + 36);
  *(this + 10) = *(uint32_t *)(pArg2 + 40);
  *(this + 11) = *(uint32_t *)(pArg2 + 44);
  *(this + 12) = *(uint32_t *)(pArg2 + 48);
  *(this + 13) = *(uint32_t *)(pArg2 + 52);
  *(this + 14) = *(uint32_t *)(pArg2 + 56);
  *(this + 15) = *(uint32_t *)(pArg2 + 60);
  *(this + 16) = *(uint32_t *)(pArg2 + 64);
  *(this + 17) = *(uint32_t *)(pArg2 + 68);
  *(this + 18) = *(uint32_t *)(pArg2 + 72);
  *(this + 19) = *(uint32_t *)(pArg2 + 76);
  *((uint8_t *)this + 80) = *(uint8_t *)(pArg2 + 80);
  *((uint8_t *)this + 81) = *(uint8_t *)(pArg2 + 81);
  *((uint8_t *)this + 82) = *(uint8_t *)(pArg2 + 82);
  *(this + 21) = *(uint32_t *)(pArg2 + 84);
  *(this + 22) = *(uint32_t *)(pArg2 + 88);
  sub_4014D0((std::_String_base *)(this + 23), pArg2 + 92, 0, -1);
  *(this + 30) = *(uint32_t *)(pArg2 + 120);
  *(this + 31) = *(uint32_t *)(pArg2 + 124);
  *((uint8_t *)this + 128) = *(uint8_t *)(pArg2 + 128);
  *(this + 33) = *(uint32_t *)(pArg2 + 132);
  *(this + 34) = *(uint32_t *)(pArg2 + 136);
  *((uint8_t *)this + 140) = *(uint8_t *)(pArg2 + 140);
  *((uint8_t *)this + 141) = *(uint8_t *)(pArg2 + 141);
  *(this + 36) = *(uint32_t *)(pArg2 + 144);
  *(this + 37) = *(uint32_t *)(pArg2 + 148);
  return this;
}



// ------------------------------------------------------------
// 0x4B2AA0 sub_4B2AA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B2AA0(size_t *this, int pArg2)
{
  int v3; // ebx
  int v4; // eax
  char *psz; // ecx
  int v6; // ebx
  unsigned int v7; // ecx
  int v8; // eax
  int v9; // eax
  size_t v10; // edx

  sub_4014D0(this + 72, (size_t *)pArg2, 0, 0xFFFFFFFF);
  *(this + 1787) = *(uint32_t *)(pArg2 + 28);
  v3 = *(uint32_t *)(pArg2 + 32);
  v4 = sub_4CE8A0(*(uint32_t *)(pArg2 + 28));
  if ( v4 != 0 )
  {
    v6 = 28 * v3;
    v7 = *(uint32_t *)(v6 + v4 + 28);
    v8 = v6 + v4 + 4;
    if ( v7 < 0x10 )
      psz = (char *)(v8 + 4);
    else
      psz = *(char **)(v8 + 4);
  }
  else
  {
    psz = nullptr;
  }
  sub_4015C0(this + 1790, psz, strlen(psz));  // 【std::string构造赋值】
  v9 = sub_41A5E0(pArg2 + 37);
  v10 = *this;
  *(this + 169) = v9;
  (*(void (/*thiscall*/ **)(size_t *, uint32_t))(v10 + 676))(this, 0);
  return (*(int (/*thiscall*/ **)(size_t *, uint32_t, uint32_t))(*this + 1320))(
           this,
           *(uint32_t *)(pArg2 + 32),
           *(uint8_t *)(pArg2 + 36));
}



// ------------------------------------------------------------
// 0x4B2B50 sub_4B2B50
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4B2B50(size_t *this, uint32_t *pArg2)
{
  uint32_t *pArg22; // esi
  int v4; // eax

  pArg22 = pArg2;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 576))(pArg2) != 0 )
    pArg22 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 576))(pArg2);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg22 + 40))(pArg22, 529) != 0 && pArg22[2088] != 0 )
    pArg22 = (uint32_t *)pArg22[2088];
  *(this + 2002) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 44))(pArg22);
  *(this + 2003) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 48))(pArg22);
  *(this + 2004) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 52))(pArg22);
  *(this + 2005) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 376))(pArg22);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 340))(pArg22);
  return sub_4014D0(this + 2006, (size_t *)(v4 + 4), 0, 0xFFFFFFFF);
}



// ------------------------------------------------------------
// 0x4B2BF0 sub_4B2BF0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4B2BF0(uint32_t *this, int ***uArg2, int **pDwArg3)
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 25) != 0 )
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v26 = 0;
    sub_401740(pExceptionObject, (int)v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_4B0C60(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 25) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 25) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 25) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_433190(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 25) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_4B0BE0(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 25) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 25) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 24);
  *((uint8_t *)v5 + 24) = *((uint8_t *)pDwArg32 + 24);
  *((uint8_t *)pDwArg32 + 24) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 24) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 24) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 24) == 0 )
          {
            *((uint8_t *)v16 + 24) = 1;
            *((uint8_t *)v6 + 24) = 0;
            sub_4B0FD0(v6);
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 25) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 24) != 1 || *(uint8_t *)(v16[2] + 24) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 24) == 1 )
            {
              *(uint8_t *)(*v16 + 24) = 1;
              *((uint8_t *)v16 + 24) = 0;
              sub_4B0C00(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 24) = *((uint8_t *)v6 + 24);
            *((uint8_t *)v6 + 24) = 1;
            *(uint8_t *)(v16[2] + 24) = 1;
            sub_4B0FD0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 24) == 0 )
          {
            *((uint8_t *)v16 + 24) = 1;
            *((uint8_t *)v6 + 24) = 0;
            sub_4B0C00(v6);
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 25) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 24) != 1 || *(uint8_t *)(*v16 + 24) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 24) == 1 )
            {
              *(uint8_t *)(v16[2] + 24) = 1;
              *((uint8_t *)v16 + 24) = 0;
              sub_4B0FD0(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 24) = *((uint8_t *)v6 + 24);
            *((uint8_t *)v6 + 24) = 1;
            *(uint8_t *)(*v16 + 24) = 1;
            sub_4B0C00(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 24) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 24) = 1;
  }
  j__free(Block);
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4B2EB0 sub_4B2EB0
// ------------------------------------------------------------
void /*noreturn*/ sub_4B2EB0()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "invalid vector<T> subscript", 0x1Bu);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::out_of_range::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x4B2F20 sub_4B2F20
// ------------------------------------------------------------
void /*noreturn*/ sub_4B2F20()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4B2F90 sub_4B2F90
// ------------------------------------------------------------
int */*thiscall*/ sub_4B2F90(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)
{
  int fld_e1; // ecx
  int *fld_e12; // eax
  int *fld_e13; // eax
  int fld_e14; // eax
  int *v10; // eax
  int fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  int fld_e15; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x15555554 )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_437740(*(this + 1), pDwArg4, *(this + 1), nArg5, 0);
  fld_e12 = *(this + 1);
  fld_e15 = fld_e1;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);
  if ( pDwArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    **(this + 1) = fld_e1;
    (*(this + 1))[2] = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pDwArg4 = fld_e1;
    fld_e13 = *(this + 1);
    if ( pDwArg4 == (int *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pDwArg4[2] = fld_e1;
    fld_e14 = (int)*(this + 1);
    if ( pDwArg4 == *(int **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = (int *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 24) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 24) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_4B0FD0(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 24) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 24) = 0;
          sub_4B0C00(this, *(uint32_t **)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 24) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4B0C00(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 24) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 24) = 0;
        sub_4B0FD0(this, *(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 24) = 1;
      *(uint8_t *)(v14 + 24) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 24) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 24) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)((*(this + 1))[1] + 24) = 1;
  *pDwArg2 = fld_e1;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x4B3140 sub_4B3140
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4B3140(uint32_t *uArg1, uint32_t *uArg2, int nArg3)
{
  uint32_t *i; // esi
  uint32_t *result; // eax

  for ( i = uArg1; i != uArg2; i += 38 )
    result = sub_4B2970(i, nArg3);
  return result;
}



// ------------------------------------------------------------
// 0x4B3170 sub_4B3170
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4B3170(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg22; // esi
  uint32_t *uArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    nArg22 -= 152;
    uArg32 -= 38;
    sub_4B2970(uArg32, nArg22);
  }
  while ( nArg22 != nArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x4B31B0 sub_4B31B0
// ------------------------------------------------------------
char */*cdecl*/ sub_4B31B0(int nArg1, int nArg2, char *pszArg3)
{
  char *pszArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg32 = pszArg3;
  v6[4] = v6;
  v6[3] = pszArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )
  {
    LOBYTE(v7) = 1;
    if ( pszArg32 != nullptr )
      sub_4B2820(pszArg32, nArg1);
    pszArg32 += 152;
    LOBYTE(v7) = 0;
    nArg1 += 152;
  }
  return pszArg32;
}



// ------------------------------------------------------------
// 0x4B3270 sub_4B3270
// ------------------------------------------------------------
void /*thiscall*/ sub_4B3270(uint32_t *this)
{
  sub_4017E0((int)(this + 12));
  sub_41A580(this + 8);
  sub_41A580((uint32_t *)((char *)this + 18));
  sub_41A580(this + 1);
}



// ------------------------------------------------------------
// 0x4B32E0 sub_4B32E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B32E0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // edi
  int result; // eax

  *(this + 1991) = -1;
  *((uint8_t *)this + 7609) = 0;
  sub_4D6970();
  *(uint32_t *)(*(this + 28) + 16) = 0;
  *(uint32_t *)(*(this + 28) + 28) = 0;
  *(uint32_t *)(*(this + 28) + 40) = 0;
  *(uint32_t *)(*(this + 28) + 20) = 0;
  *(uint32_t *)(*(this + 28) + 32) = 0;
  *(uint32_t *)(*(this + 28) + 44) = 0;
  *(uint32_t *)(*(this + 28) + 24) = 0;
  *(uint32_t *)(*(this + 28) + 36) = 0;
  *(uint32_t *)(*(this + 28) + 48) = 0;
  if ( (uint32_t *)dword_8F7C04 == this )
  {
    v2 = *(uint32_t **)dword_8F85A0;
    *(uint32_t *)dword_8F85A0 = dword_8F85A0;
    *(uint32_t *)(dword_8F85A0 + 4) = dword_8F85A0;
    dword_8F85A4 = 0;
    if ( v2 != (uint32_t *)dword_8F85A0 )
    {
      do
      {
        v3 = (uint32_t *)*v2;
        j__free(v2);
        v2 = v3;
      }
      while ( v3 != (uint32_t *)dword_8F85A0 );
    }
    if ( dword_8F8588 != nullptr )
      j__free(dword_8F8588);
    dword_8F8588 = nullptr;
    dword_8F858C = 0;
    dword_8F8590 = 0;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1232))(this, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 1240))(this, 0, 0);
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1248))(this, 0);
  *(this + 1972) = 0;
  *(this + 1940) = 4;
  return result;
}



// ------------------------------------------------------------
// 0x4B33E0 sub_4B33E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B33E0(uint32_t *this, unsigned int uArg2)
{
  int fld_e1; // edi

  fld_e1 = *(this + 1);
  if ( fld_e1 == 0 || (*(this + 2) - fld_e1) / 124 <= uArg2 )
    sub_4B2EB0();
  return fld_e1 + 124 * uArg2;
}



// ------------------------------------------------------------
// 0x4B3420 sub_4B3420
// ------------------------------------------------------------
char /*thiscall*/ sub_4B3420(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xFFFFFFF )
    sub_4B2F20(this);
  pMem = (char *)operator new(16 * uArg2);
  *(this + 3) = &pMem[16 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x4B3470 sub_4B3470
// ------------------------------------------------------------
int /*thiscall*/ sub_4B3470(int **this, int pArg2, int *pDwArg3)
{
  int *pDwArg32; // ebx
  int *fld_e1; // esi
  int v6; // eax
  bool v7; // cl
  int v8; // edx
  int *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  pDwArg32 = pDwArg3;
  fld_e1 = *(this + 1);
  v6 = fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 25) == 0 )
  {
    v8 = *pDwArg3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      fld_e1 = (int *)v6;
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )
        v6 = *(uint32_t *)(v6 + 8);
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 25) == 0 );
  }
  fld_e12 = fld_e1;
  pDwArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == (int *)**(this + 1) )
    {
      v10 = *sub_4B2F90(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4B0CC0(&pDwArg3);
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= *pDwArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_4B2F90(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4B3530 sub_4B3530
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4B3530(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_4B3170(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x4B3550 sub_4B3550
// ------------------------------------------------------------
char */*cdecl*/ sub_4B3550(char *pszArg1, int nArg2, int nArg3)
{
  char *pszArg12; // esi
  char *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg12 = pszArg1;
  v6[4] = v6;
  v6[3] = pszArg1;
  v7 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( pszArg12 != nullptr )
      result = sub_4B2820(pszArg12, nArg3);
    --nArg2;
    pszArg12 += 152;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B3600 sub_4B3600
// ------------------------------------------------------------
unsigned int ***/*thiscall*/ sub_4B3600(unsigned int ***this, int pArg2)
{
  int v3; // ecx
  unsigned int v4; // eax
  unsigned int **v6; // [esp-14h] [ebp-34h]
  unsigned int **v7; // [esp-10h] [ebp-30h]
  unsigned int **fld_e1; // [esp-Ch] [ebp-2Ch]
  uint32_t v9[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = *(uint32_t *)(pArg2 + 4);
  v9[4] = v9;
  v9[3] = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( sub_401950(this, v4) != 0 )
  {
    fld_e1 = *(this + 1);
    v7 = *(unsigned int ***)(pArg2 + 8);
    v6 = *(unsigned int ***)(pArg2 + 4);
    v9[7] = 0;
    *(this + 2) = sub_4B1550(v6, v7, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x4B36A0 sub_4B36A0
// ------------------------------------------------------------
int */*userpurge*/ sub_4B36A0@<eax>(int **pDwArg1@<ecx>, unsigned int uArg2@<ebx>, int *pDwArg3)
{
  int *pDwArg32; // edi
  int *v6; // ebx
  int v7; // eax
  uint32_t *v8; // ebx
  int **v9; // edi
  int v10; // eax
  uint32_t *v11; // eax
  int v12; // ebx
  int *v13; // ecx
  int v15; // [esp+8h] [ebp-8h]
  int *v16; // [esp+Ch] [ebp-4h]

  pDwArg32 = pDwArg3;
  if ( pDwArg3 == nullptr )
    return nullptr;
  v6 = (int *)sub_52DAD0(pDwArg3);  // 【IRDActiveObject__vmt310】
  v16 = v6;
  if ( v6 != pDwArg3 )
  {
    ((void (/*thiscall*/ *)(int **))(*pDwArg1)[288])(pDwArg1);
    ((void (/*thiscall*/ *)(int **))(*pDwArg1)[289])(pDwArg1);
    if ( ((uint8_t (/*thiscall*/ *)(int **))(*pDwArg1)[77])(pDwArg1) != 0 )
      sub_47E4F0();
    v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg3 + 248))(pDwArg3);
    v8 = *(uint32_t **)(v7 + 4);
    v15 = v7;
    if ( v8 != *(uint32_t **)(v7 + 8) )
    {
      v9 = (int **)(v8 + 18);
      do
      {
        sub_4B1C80((int)(pDwArg1 + 1540), (int)(v9 - 17), pDwArg1 + 1803, v9);
        ((void (/*thiscall*/ *)(int **, uint32_t, int **, int **))(*pDwArg1)[268])(pDwArg1, *v8, pDwArg1 + 1803, v9);
        v8 += 31;
        v9 += 31;
      }
      while ( v8 != *(uint32_t **)(v15 + 8) );
      pDwArg32 = pDwArg3;
    }
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pDwArg32 + 172))(pDwArg32) == 8 )
    {
      if ( pDwArg1[1857] != nullptr && v16 != nullptr )
      {
        v10 = (*(int (/*thiscall*/ **)(int *))(*v16 + 188))(v16);
        if ( sub_41A5E0(v10 + 4) != 0 )
        {
          v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1[1857] + 248))(pDwArg1[1857], 0);
          v12 = sub_4B33E0(v11, uArg2);
          ((void (/*thiscall*/ *)(int **, int **))(*pDwArg1)[174])(pDwArg1, pDwArg1 + 1540);
          ((void (/*thiscall*/ *)(int **, int **, int))(*pDwArg1)[269])(pDwArg1, pDwArg1 + 1803, v12 + 72);
        }
      }
      v13 = pDwArg1[1857];
      if ( v13 != nullptr )
        (*(void (/*thiscall*/ **)(int *, int))(*v13 + 4))(v13, 1);
      pDwArg1[1857] = nullptr;
    }
    sub_484D00((int *)dword_8F852C);
    v6 = v16;
  }
  return v6 == pDwArg1[*(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pDwArg32 + 172))(pDwArg32) + 1879] ? nullptr : v6;
}



// ============================================================
// §G 0x4B3820-0x4B49B0  avatar 变更/比较（[none]）
// ============================================================
// ------------------------------------------------------------
// 0x4B3820 sub_4B3820 —— avatar 名称查询/[none] 判定（sub_40BF00 比较）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4B3820(int *this, int nArg2)
{
  uint32_t *v2; // ebx
  unsigned int result; // eax
  int dword_8F85402; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edi
  uint32_t *v9; // edi
  int v10; // eax
  unsigned int v11; // esi
  int v12; // ecx
  unsigned int v13; // esi
  int v14; // edx
  uint32_t *v15; // esi
  int v16; // eax
  float v17; // [esp+0h] [ebp-10h]
  uint8_t v18[4]; // [esp+Ch] [ebp-4h] BYREF

  v2 = (uint32_t *)nArg2;
  result = *(uint32_t *)nArg2 - 11;
  switch ( *(uint32_t *)nArg2 )
  {
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
      goto LABEL_4;
    case 0xF:
    case 0x10:
      dword_8F85402 = dword_8F8540;
      nArg2 = 15;
      if ( *(uint32_t *)sub_472E30(v18, &nArg2) != *(uint32_t *)(dword_8F85402 + 52) )
      {
        v6 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 672))(this, 0, 1041865114);
        sub_4AED60((void *)(v6 + 830), v17);
        v7 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0);
        sub_4AED60((void *)(v7 + 858), 0.15000001);
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
LABEL_4:
        dword_8F85402 = dword_8F8540;
      }
      nArg2 = 7;
      result = *(uint32_t *)sub_472E30(v18, &nArg2);
      if ( result == *(uint32_t *)(dword_8F85402 + 52) )
      {
        v8 = *this;
        nArg2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 752))(this, 1);
        result = (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(v8 + 748))(
                   this,
                   (uint64_t)((double)nArg2 * 0.75) >> 32,
                   (uint64_t)((double)nArg2 * 0.75));
        if ( (int *)dword_8F7C04 != this )
          return result;
        v9 = *((uint32_t **)dword_8F8528 + 7);
        v10 = sub_422E70(857);
        result = sub_43BEE0(v9, v10, -6567706, 0, -1);
      }
LABEL_8:
      if ( (int *)dword_8F7C04 != this )
        return result;
      result = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);
      v11 = result;
      if ( result == 0 )
        return result;
      result = sub_40BF00((std::_String_base *)(result + 32), 0, *(uint32_t *)(result + 52), "[none]", 6u);
      if ( result == 0 )
        return result;
      v12 = *(uint32_t *)(v11 + 88);
      if ( v12 == 0 )
        return result;
      v13 = 0;
      break;
    default:
      goto LABEL_8;
  }
  while ( 1 )
  {
    v14 = *(uint32_t *)(v12 + 4);
    if ( v14 == 0 )
      break;
    result = (*(uint32_t *)(v12 + 8) - v14) >> 2;
    if ( v13 >= result )
      break;
    result = *(uint32_t *)(v14 + 4 * v13);
    if ( result == *v2 )
    {
      v15 = *((uint32_t **)dword_8F8528 + 7);
      v16 = sub_422E70(1245);
      return sub_43BEE0(v15, v16, -6567706, 0, -1);
    }
    ++v13;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B3A00 sub_4B3A00
// ------------------------------------------------------------
int */*thiscall*/ sub_4B3A00(int this, int *pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *fld_4; // eax
  int *pDwArg42; // esi
  int *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_4B2F90((int **)this, pDwArg2, 1, *(int **)(this + 4), (int)pDwArg4);
    return pDwArg2;
  }
  fld_4 = *(int **)(this + 4);
  pDwArg42 = pDwArg4;
  if ( pDwArg3 == (int *)*fld_4 )
  {
    if ( *pDwArg4 < pDwArg3[3] )
    {
      sub_4B2F90((int **)this, pDwArg2, 1, pDwArg3, (int)pDwArg4);
      return pDwArg2;
    }
    goto LABEL_22;
  }
  if ( pDwArg3 == fld_4 )
  {
    v8 = (int *)fld_4[2];
    if ( v8[3] < *pDwArg4 )
    {
      sub_4B2F90((int **)this, pDwArg2, 0, v8, (int)pDwArg4);
      return pDwArg2;
    }
    goto LABEL_22;
  }
  if ( *pDwArg4 >= pDwArg3[3] || (pDwArg4 = pDwArg3, sub_4B0CC0(&pDwArg4), pDwArg4[3] >= *pDwArg42) )
  {
    if ( pDwArg3[3] >= *pDwArg42 || (pDwArg4 = pDwArg3, sub_4B0C60((int *)&pDwArg4), pDwArg4 != *(int **)(this + 4)) && *pDwArg42 >= pDwArg4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4B3470((int **)this, (int)v10, pDwArg42);
      *pDwArg2 = v9;
      return pDwArg2;
    }
    if ( *(uint8_t *)(pDwArg3[2] + 25) != 0 )
      sub_4B2F90((int **)this, pDwArg2, 0, pDwArg3, (int)pDwArg42);
    else
      sub_4B2F90((int **)this, pDwArg2, 1, pDwArg4, (int)pDwArg42);
    return pDwArg2;
  }
  else
  {
    if ( *(uint8_t *)(pDwArg4[2] + 25) != 0 )
      sub_4B2F90((int **)this, pDwArg2, 0, pDwArg4, (int)pDwArg42);
    else
      sub_4B2F90((int **)this, pDwArg2, 1, pDwArg3, (int)pDwArg42);
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4B3B60 sub_4B3B60
// ------------------------------------------------------------
int /*cdecl*/ sub_4B3B60(int nArg1, int nArg2, int nArg3)
{
  int nArg12; // esi
  int nArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    sub_41DC80(nArg32, nArg12);
    nArg12 += 16;
    nArg32 += 16;
  }
  while ( nArg12 != nArg2 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x4B3BA0 sub_4B3BA0
// ------------------------------------------------------------
int /*cdecl*/ sub_4B3BA0(int nArg1, int nArg2, int nArg3)
{
  int nArg22; // esi
  int nArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    nArg22 -= 24;
    nArg32 -= 24;
    sub_4ED3F0(nArg32, nArg22);
    *(uint32_t *)(nArg32 + 16) = *(uint32_t *)(nArg22 + 16);
    *(uint32_t *)(nArg32 + 20) = *(uint32_t *)(nArg22 + 20);
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x4B3BE0 sub_4B3BE0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B3BE0(uint32_t *this)
{
  uint32_t *pThis_1; // ebx
  int v3; // edx
  int v4; // edx
  int v5; // edx

  pThis_1 = this + 1;
  sub_41A630((unsigned int)(this + 1));
  *pThis_1 = &clong::`vftable';
  sub_41A630((unsigned int)this + 18);
  *(uint32_t *)((char *)this + 18) = &clong::`vftable';
  sub_41A630((unsigned int)(this + 8));
  *(this + 8) = &clong::`vftable';
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *this = 18;
  sub_41A590((unsigned int)pThis_1, v3, 0);
  sub_41A590((unsigned int)this + 18, v4, 0);
  sub_41A590((unsigned int)(this + 8), v5, -1);
  sub_4017E0((int)(this + 12));
  return this;
}



// ------------------------------------------------------------
// 0x4B3C90 sub_4B3C90
// ------------------------------------------------------------
int /*thiscall*/ sub_4B3C90(int this, int nArg2, int nArg3)
{
  sub_4B1030((uint8_t *)this);
  *(uint32_t *)this = &CNChangeStatus::`vftable';
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  sub_5F76F0(this);
  sub_5F7700(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x4B3D20 sub_4B3D20
// ------------------------------------------------------------
void */*thiscall*/ sub_4B3D20(void *Block, char pszArg2)
{
  sub_4B3D50();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4B3D50 sub_4B3D50
// ------------------------------------------------------------
int /*thiscall*/ sub_4B3D50(void **this)
{
  int result; // eax

  *this = &CNChangeStatus::`vftable';
  sub_5F8960();
  if ( *(this + 28) != nullptr )
    j__free(*(this + 28));
  *(this + 28) = nullptr;
  *(this + 29) = nullptr;
  *(this + 30) = nullptr;
  if ( *(this + 21) != nullptr )
    j__free(*(this + 21));
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *((uint8_t *)this + 12) = 0;
  *(this + 2) = &nengine::IObject::`vftable';
  return result;
}



// ------------------------------------------------------------
// 0x4B3DF0 sub_4B3DF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B3DF0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  sub_4B1030();
  *this = &CNChangeStatus::`vftable';
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  sub_5F76F0(this);
  sub_5F7720(nArg2, nArg3, nArg4, nArg5, nArg6);
  return this;
}



// ------------------------------------------------------------
// 0x4B3E70 sub_4B3E70
// ------------------------------------------------------------
void /*thiscall*/ sub_4B3E70(int *this, void *Block, int nArg3)
{
  int *pObj3; // ebx
  int pObj; // eax
  int pObj2; // eax
  int fld_e1787; // eax
  float v8; // [esp+24h] [ebp+Ch]
  float v9; // [esp+24h] [ebp+Ch]

  if ( Block == (void *)187
    || Block == (void *)185
    || Block == (void *)172
    || Block == (void *)173
    || Block == (void *)174 )
  {
    if ( *(this + 2017) == 0 )
    {
      if ( operator new(0xB4u) != nullptr )
        fld_e1787 = sub_4B11A0(*(this + 1787));
      else
        fld_e1787 = 0;
      *(this + 2017) = fld_e1787;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1787 + 64))(fld_e1787) + 36) = 0;
    }
    if ( nArg3 != 0 )
      sub_5F74E0(*(this + 2017), (int)Block);
    else
      sub_5F6EE0(Block);
    if ( Block == (void *)187 )
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2017) + 56))(
        *(this + 2017),
        this,
        this,
        0,
        0,
        0,
        -1);
  }
  else
  {
    if ( Block != (void *)178 && Block != (void *)189 )
    {
      if ( Block != (void *)186 && Block != (void *)188 )
        return;
      pObj3 = this + (Block != (void *)186) + 2020;
      if ( nArg3 > 0 )
      {
        if ( *pObj3 == 0 )
        {
          if ( operator new(0x7Cu) != nullptr )
            pObj = sub_4B3C90(0, 0);
          else
            pObj = 0;
          *pObj3 = pObj;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
        }
        (*(void (/*thiscall*/ **)(int *, void *))(*this + 1160))(this, Block);
        v8 = (double)(int)sub_47EF20(0, nArg3, -1, -1, 11) * 0.1;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)*pObj3 + 124))(*pObj3);
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)*pObj3 + 120))(
          *pObj3,
          (Block != (void *)186) + 12,
          0,
          LODWORD(v8));
        (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*pObj3 + 56))(
          *pObj3,
          this,
          this,
          0,
          0,
          0,
          -1);
        return;
      }
      goto LABEL_24;
    }
    pObj3 = this + (Block != (void *)178) + 2018;
    if ( nArg3 <= 0 )
    {
LABEL_24:
      if ( *pObj3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)*pObj3 + 80))(*pObj3) != 0 )
        sub_53FE50(*pObj3);
      return;
    }
    if ( *pObj3 == 0 )
    {
      if ( operator new(0x7Cu) != nullptr )
        pObj2 = sub_4B3C90(0, 0);
      else
        pObj2 = 0;
      *pObj3 = pObj2;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;
    }
    (*(void (/*thiscall*/ **)(int *, void *))(*this + 1160))(this, Block);
    v9 = (double)(int)sub_47EF20(0, nArg3, -1, -1, 11) * 0.1;
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)*pObj3 + 124))(*pObj3);
    (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)*pObj3 + 120))(
      *pObj3,
      (Block != (void *)178) + 14,
      0,
      LODWORD(v9));
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*pObj3 + 56))(
      *pObj3,
      this,
      this,
      0,
      0,
      0,
      -1);
  }
}


// ------------------------------------------------------------
// 0x4B4170 sub_4B4170 —— ★Buff 图标条装配
//   Common/CommonEffect/BuffIcon.img ×3 槽（+40/+56/+212/+44）；图标动画
//   BUFF_LEAP/BUFF_INTUP；图标项 sub_4B3C90/sub_4B3DF0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B4170(float *this, uint32_t *Block, void *pArg3)
{
  int result; // eax
  int v5; // ebx
  uint32_t *pMem; // eax
  uint32_t *v7; // eax
  int pThis_7CA; // edi
  uint32_t *v9; // eax
  void *pMem2; // eax
  int pObj2; // eax
  int pThis_7CB; // edi
  uint32_t *v13; // eax
  double v14; // st7
  int pThis_7CC; // eax
  uint8_t *pMem3; // eax
  uint8_t *pObj; // eax
  int pThis_7CC2; // edi
  uint32_t *v19; // eax
  int v20; // [esp+0h] [ebp-28h]
  float v21; // [esp+8h] [ebp-20h]
  unsigned int v22; // [esp+Ch] [ebp-1Ch]
  void *Blocka; // [esp+30h] [ebp+8h]
  void *Blockb; // [esp+30h] [ebp+8h]
  void *v25; // [esp+34h] [ebp+Ch]
  void *v26; // [esp+34h] [ebp+Ch]

  result = sub_41A5E0((unsigned int)(Block + 1));
  switch ( result )
  {
    case 175:
      v5 = sub_47EF20(0, pArg3, -1, -1, 11);
      v25 = (void *)sub_47E9D0(Block, 0);
      if ( *((uint32_t *)this + 1994) == 0 )
      {
        pMem = operator new(0x7Cu);
        if ( pMem != nullptr )
        {
          *(float *)&v20 = (float)(int)v25;
          v7 = sub_4B3DF0(pMem, 6, 0, v20, v5, 1);
        }
        else
        {
          v7 = nullptr;
        }
        *((uint32_t *)this + 1994) = v7;
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 64))(v7) + 36) = 0;
      }
      if ( (uint8_t)sub_53F660(*((uint32_t *)this + 1994)) != 0 )
        sub_53FE50(*((uint32_t *)this + 1994));
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1994) + 64))(*((uint32_t *)this + 1994)) + 40) = v5;
      pThis_7CA = **((uint32_t **)this + 1994);
      v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
                       dword_8F84B8,
                       "Common/CommonEffect/BuffIcon.img",
                       4,
                       0,
                       -1);
      sub_418DD0(v9, v22);
      (*(void (/*thiscall*/ **)(uint32_t, float *, float *, int))(pThis_7CA + 56))(*((uint32_t *)this + 1994), this, this, 1);
      return (*(int (/*thiscall*/ **)(float *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "BUFF_LEAP",
               -1,
               0,
               0);
    case 176:
      Blocka = (void *)sub_47EF20(0, pArg3, -1, -1, 11);
      v26 = (void *)sub_47EF20(1, pArg3, -1, -1, 11);
      if ( *((uint32_t *)this + 1995) == 0 )
      {
        pMem2 = operator new(0x7Cu);
        if ( pMem2 != nullptr )
          pObj2 = sub_4B3C90((int)pMem2, 0, 1);
        else
          pObj2 = 0;
        *((uint32_t *)this + 1995) = pObj2;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;
      }
      if ( (uint8_t)sub_53F660(*((uint32_t *)this + 1995)) != 0 )
        sub_53FE50(*((uint32_t *)this + 1995));
      (*(void (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1995) + 124))(*((uint32_t *)this + 1995));
      v21 = (float)(int)v26;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(**((uint32_t **)this + 1995) + 120))(1, 0, LODWORD(v21));
      *(uint32_t *)(*((uint32_t *)this + 1995) + 44) = Blocka;
      pThis_7CB = **((uint32_t **)this + 1995);
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
                        dword_8F84B8,
                        "Common/CommonEffect/BuffIcon.img",
                        5,
                        0,
                        -1);
      sub_418DD0(v13, v22);
      (*(void (/*thiscall*/ **)(uint32_t, float *, float *, int))(pThis_7CB + 56))(*((uint32_t *)this + 1995), this, this, 1);
      return (*(int (/*thiscall*/ **)(float *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "BUFF_INTUP",
               -1,
               0,
               0);
    case 180:
      Blockb = (void *)sub_47EF20(1, pArg3, -1, -1, 11);
      v14 = (double)(int)sub_47EF20(0, pArg3, -1, -1, 11);
      pThis_7CC = *((uint32_t *)this + 1996);
      *(this + 1997) = v14 * 0.1;
      if ( pThis_7CC == 0 )
      {
        pMem3 = operator new(0x50u);
        if ( pMem3 != nullptr )
          pObj = sub_4B1030(pMem3);
        else
          pObj = nullptr;
        *((uint32_t *)this + 1996) = pObj;
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
      }
      if ( (uint8_t)sub_53F660(*((uint32_t *)this + 1996)) != 0 )
        sub_53FE50(*((uint32_t *)this + 1996));
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1996) + 64))(*((uint32_t *)this + 1996)) + 40) = Blockb;
      pThis_7CC2 = **((uint32_t **)this + 1996);
      v19 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(
                        dword_8F84B8,
                        "Common/CommonEffect/BuffIcon.img",
                        21,
                        0,
                        -1);
      sub_418DD0(v19, v22);
      return (*(int (/*thiscall*/ **)(uint32_t, float *, float *, int))(pThis_7CC2 + 56))(*((uint32_t *)this + 1996), this, this, 1);
    default:
      break;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4B44E0 sub_4B44E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4B44E0(int **this, int *pDwArg2)
{
  int *fld_e1; // edx
  int v3; // eax
  int v4; // edi
  int v6[3]; // [esp+Ch] [ebp-Ch] BYREF

  fld_e1 = *(this + 1);
  v3 = fld_e1[1];
  while ( *(uint8_t *)(v3 + 25) == 0 )
  {
    if ( *(uint32_t *)(v3 + 12) >= *pDwArg2 )
    {
      fld_e1 = (int *)v3;
      v3 = *(uint32_t *)v3;
    }
    else
    {
      v3 = *(uint32_t *)(v3 + 8);
    }
  }
  if ( fld_e1 != *(this + 1) && *pDwArg2 >= fld_e1[3] )
    return (int)(fld_e1 + 4);
  v4 = *pDwArg2;
  v6[1] = 0;
  v6[0] = v4;
  v6[2] = 0;
  return *sub_4B3A00((int)this, (int *)&pDwArg2, fld_e1, v6) + 16;
}



// ------------------------------------------------------------
// 0x4B4560 sub_4B4560
// ------------------------------------------------------------
char */*stdcall*/ sub_4B4560(char *pszArg1, int nArg2, int nArg3)
{
  sub_4B3550(pszArg1, nArg2, nArg3);
  return &pszArg1[152 * nArg2];
}



// ------------------------------------------------------------
// 0x4B4590 sub_4B4590
// ------------------------------------------------------------
void /*thiscall*/ sub_4B4590(int *this, int pArg2, unsigned int uArg3, int nArg4)
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-DCh]
  int fld_e28; // [esp-10h] [ebp-D4h]
  int fld_e25; // [esp-Ch] [ebp-D0h]
  unsigned int fld_e24; // [esp-8h] [ebp-CCh]
  int v23; // [esp+0h] [ebp-C4h] BYREF
  void *Block; // [esp+Ch] [ebp-B8h]
  int *pThis; // [esp+10h] [ebp-B4h]
  char *pMem2; // [esp+14h] [ebp-B0h]
  uint8_t v27[96]; // [esp+18h] [ebp-ACh] BYREF
  void *v28; // [esp+78h] [ebp-4Ch]
  unsigned int v29; // [esp+8Ch] [ebp-38h]
  int dword_796E502; // [esp+B0h] [ebp-14h]
  int *v31; // [esp+B4h] [ebp-10h]
  int v32; // [esp+C0h] [ebp-4h]
  int v33; // [esp+CCh] [ebp+8h]
  int v34; // [esp+D0h] [ebp+Ch]
  int fld_e232; // [esp+D4h] [ebp+10h]

  dword_796E502 = dword_796E50;
  v31 = &v23;
  pThis = this;
  sub_4B2820(nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v32 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 152;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 152;
    else
      fld_e2 = 0;
    if ( 28256363 - fld_e2 < uArg3 )
      sub_4A30C0();
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 152;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = *(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 152 >= uArg3 )
      {
        v33 = fld_e23 - 152 * uArg3;
        *(this + 2) = sub_4B31B0(v33, fld_e23, fld_e23);
        sub_4B3530(pArg2, v33, fld_e232);
        sub_4B3140(pArg2, pArg2 + 152 * uArg3, v27);
      }
      else
      {
        sub_4B31B0(pArg2, fld_e23, pArg2 + 152 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 152;
        fld_e25 = *(this + 2);
        LOBYTE(v32) = 3;
        sub_4B4560(fld_e25, fld_e24, v27);
        fld_e26 = 152 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v32 = 0;
        sub_4B3140(pArg2, fld_e26 - 152 * uArg3, v27);
      }
    }
    else
    {
      if ( 28256363 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 152;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_4B0BC0(this);
      v34 = 152 * v10;
      pMem = (char *)operator new(152 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v32) = 1;
      pMem2 = (char *)sub_4B31B0(fld_e12, pArg2, (int)pMem);
      sub_4B3550((int)pMem2, uArg3, (int)v27);
      fld_e28 = *(this + 2);
      pMem2 += 152 * uArg3;
      sub_4B31B0(pArg2, fld_e28, (int)pMem2);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 152;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_4A3870(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v34];
      *(this + 2) = (int)&pMem[152 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v29 >= 0x10 )
    j__free(v28);
}


// ------------------------------------------------------------
// 0x4B48D0 sub_4B48D0
// ------------------------------------------------------------
int /*cdecl*/ sub_4B48D0(int nArg1, int nArg2, int nArg3)
{
  return sub_4B3B60(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x4B48F0 sub_4B48F0
// ------------------------------------------------------------
int /*cdecl*/ sub_4B48F0(int nArg1, int nArg2, int pArg3)
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 24 )
  {
    sub_4ED3F0(i, pArg3);
    result = *(uint32_t *)(pArg3 + 16);
    *(uint32_t *)(i + 16) = result;
    *(uint32_t *)(i + 20) = *(uint32_t *)(pArg3 + 20);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B4930 sub_4B4930
// ------------------------------------------------------------
int /*cdecl*/ sub_4B4930(int nArg1, int nArg2, int nArg3)
{
  return sub_4B3BA0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x4B4950 sub_4B4950
// ------------------------------------------------------------
int /*cdecl*/ sub_4B4950(int nArg1, int nArg2)
{
  int result; // eax
  int i; // edi
  void **v4; // esi
  void **j; // ebx

  result = nArg2;
  for ( i = nArg1; i != nArg2; i += 16 )
  {
    v4 = *(void ***)(i + 4);
    if ( v4 != nullptr )
    {
      for ( j = *(void ***)(i + 8); v4 != j; ++v4 )
        sub_41B010(v4);
      j__free(*(void **)(i + 4));
    }
    *(uint32_t *)(i + 4) = 0;
    *(uint32_t *)(i + 8) = 0;
    *(uint32_t *)(i + 12) = 0;
    result = nArg2;
  }
  return result;
}



// ============================================================
// §H 0x4B49B0-0x4B59A0  ★Buff 图标/职业特效（BuffIcon.img、ENUM_CMDPACKET_USE_SKILL）
// ============================================================
// ------------------------------------------------------------
// 0x4B49B0 sub_4B49B0 —— ★Buff/技能使用处理
//   调试输出 "-> ENUM_CMDPACKET_USE_SKILL : SkillIndex %d"；ALERT_1 拒绝提示；
//   +48/+52/+40/+44 Buff 槽位读写（读包三元组 sub_423200/423290/423380）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B49B0(uint32_t *this, int ArgList)
{
  uint32_t *v3; // edi
  int v4; // eax
  int v5; // eax
  uint32_t *v6; // ebx
  int v7; // eax
  void *pThis_78E; // eax
  int v9; // eax
  void *Block2; // ecx
  int v11; // ebx
  bool v12; // zf
  int v13; // eax
  int v14; // eax
  int pObj; // ecx
  unsigned int v16; // eax
  void *pThis_78E2; // eax
  const char *v18; // eax
  void *pThis_78E3; // eax
  int v21; // eax
  int v22; // ebx
  int v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // ebx
  int v27; // eax
  int v28; // [esp-Ch] [ebp-254h]
  uint32_t v29[2]; // [esp+4h] [ebp-244h] BYREF
  int v30; // [esp+Ch] [ebp-23Ch]
  int v31; // [esp+10h] [ebp-238h]
  int v32; // [esp+14h] [ebp-234h]
  uint8_t v33[4]; // [esp+18h] [ebp-230h] BYREF
  void *Block; // [esp+1Ch] [ebp-22Ch]
  int v35; // [esp+20h] [ebp-228h]
  int v36; // [esp+24h] [ebp-224h]
  unsigned int v37; // [esp+28h] [ebp-220h]
  float v38; // [esp+2Ch] [ebp-21Ch]
  uint32_t *pThis_1802; // [esp+30h] [ebp-218h]
  char v40; // [esp+37h] [ebp-211h]
  char Buffer[512]; // [esp+38h] [ebp-210h] BYREF
  int dword_796E502; // [esp+238h] [ebp-10h]
  int v43; // [esp+244h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( (uint32_t *)dword_8F7C04 != this || *(this + 50) == 2 )
    return 0;
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, ArgList);
  v30 = sub_41A5E0((unsigned int)v3 + 510);
  v40 = 1;
  if ( v30 == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v3 + 12))(v3) != 0 )
  {
    pThis_1802 = *((uint32_t **)dword_8F8528 + 7);
    v4 = sub_422E70(853);
    sub_43BEE0(pThis_1802, v4, -6567706, 0, -1);
    sub_432EA0("ALERT_1", -1, 0, 0);
    v40 = 0;
  }
  v5 = sub_41A5E0((unsigned int)v3 + 510);
  pThis_1802 = (uint32_t *)sub_41A5E0(v3[75] + 14 * (v5 - 1));
  v38 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v3 + 131)));
  v31 = (uint64_t)((double)(int)pThis_1802 * v38);
  pThis_1802 = (uint32_t *)((char *)this + 6146);
  if ( sub_41A5E0((unsigned int)this + 6146) < v31 )
  {
    v6 = *((uint32_t **)dword_8F8528 + 7);
    v7 = sub_422E70(854);
    sub_43BEE0(v6, v7, -6567706, 0, -1);
    if ( *(this + 1939) < 0x10u )
      pThis_78E = this + 1934;
    else
      pThis_78E = (void *)*(this + 1934);
    sub_432EA0(pThis_78E, -1, 0, 0);
    v40 = 0;
  }
  v9 = 0;
  Block2 = nullptr;
  Block = nullptr;
  v35 = 0;
  v36 = 0;
  v11 = v3[83];
  v12 = v11 == v3[84];
  v43 = 0;
  if ( v12 )
  {
LABEL_21:
    if ( v40 == 1 )
    {
      if ( Block2 != nullptr && (v9 - (int)Block2) >> 3 != 0 && (uint8_t)sub_486190(v33, 2) == 0 )
      {
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)&unk_6F6130, -6567706, 0, -1);
        if ( *(this + 1939) < 0x10u )
          pThis_78E2 = this + 1934;
        else
          pThis_78E2 = (void *)*(this + 1934);
        sub_432EA0(pThis_78E2, -1, 0, 0);
        Block2 = Block;
LABEL_39:
        if ( *((uint8_t *)this + 8100) != 1 )
        {
          *((uint8_t *)this + 8100) = 1;
          *((uint8_t *)this + 8101) = 0;
          *((uint8_t *)this + 8102) = 0;
          sub_698F90((int)(this + 2022), 300, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
          Block2 = Block;
        }
        if ( Block2 != nullptr )
          j__free(Block2);
        return 0;
      }
    }
    else if ( v40 == 0 )
    {
      goto LABEL_39;
    }
    v21 = sub_41A5E0((unsigned int)pThis_1802);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 748))(this, v21 - v31, 1);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 26, 2);
    v22 = *(uint32_t *)dword_8F8520;
    v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v22 + 36))(dword_8F8520, v23);
    v24 = *(uint32_t *)dword_8F8520;
    v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v24 + 36))(dword_8F8520, v25);
    v26 = ArgList;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v30);
    v27 = sub_41A5E0((unsigned int)pThis_1802);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v27);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    if ( v3[31] != 1 )
    {
      sub_423200(dword_8F7B08, 41);  // 【发送网络包API】
      HIBYTE(ArgList) = v26;
      sub_423290((char *)&ArgList + 3, 1);
      sub_423380(dword_8F7B08);
      off_77F3FC("-> ENUM_CMDPACKET_USE_SKILL : SkillIndex %d", v26);
    }
    if ( Block != nullptr )
      j__free(Block);
    return 1;
  }
  while ( 1 )
  {
    v38 = *(float *)v11;
    v37 = sub_41A5E0((unsigned int)v3 + 510);
    v13 = sub_47DCC0(v3);
    v37 = *(uint32_t *)(v11 + 4) + (int)((v37 - 1) * (*(uint32_t *)(v11 + 8) - *(uint32_t *)(v11 + 4))) / (v13 - 1);
    if ( v37 != 0 )
      break;
LABEL_19:
    v11 += 12;
    if ( v11 == v3[84] )
    {
      v9 = v35;
      Block2 = Block;
      goto LABEL_21;
    }
  }
  v14 = sub_484E80(LODWORD(v38));
  v32 = v14;
  if ( v14 != -1 )
  {
    pObj = v14 >= *((uint32_t *)dword_8F852C + 2) ? 0 : *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v14);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);
    if ( v16 >= v37 )
    {
      v29[1] = v37;
      v29[0] = v32;
      sub_474950(v29);
      goto LABEL_19;
    }
  }
  v28 = sub_4F2CE0(LODWORD(v38));
  v18 = (const char *)sub_422E70(855);
  sprintf(Buffer, v18, v28);
  sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
  if ( *(this + 1939) < 0x10u )
    pThis_78E3 = this + 1934;
  else
    pThis_78E3 = (void *)*(this + 1934);
  sub_432EA0(pThis_78E3, -1, 0, 0);
  if ( *((uint8_t *)this + 8100) != 1 )
  {
    *((uint8_t *)this + 8100) = 1;
    *((uint8_t *)this + 8101) = 0;
    *((uint8_t *)this + 8102) = 0;
    sub_698F90((int)(this + 2022), 300, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  if ( Block != nullptr )
    j__free(Block);
  return 0;
}


// ------------------------------------------------------------
// 0x4B4EE0 sub_4B4EE0
// ------------------------------------------------------------
int */*thiscall*/ sub_4B4EE0(int this, int nArg2, int nArg3)
{
  int nArg32; // edi
  int *result; // eax

  nArg32 = nArg3;
  if ( nArg3 != 0 )
  {
    result = (int *)sub_4B44E0((int **)(this + 7416), &nArg2);
    *result = nArg32;
    result[1] = nArg32;
  }
  else
  {
    sub_4B1BA0((int **)(this + 7416), (int **)&nArg3, &nArg2);
    result = (int *)nArg3;
    if ( nArg3 != *(uint32_t *)(this + 7420) )
      return sub_4B2BF0((uint32_t *)(this + 7416), &nArg2, nArg3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B4F40 sub_4B4F40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B4F40(uint32_t *this, uint32_t *uArg2, char *pszArg3, int nArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 152 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 152;
  else
    v6 = 0;
  sub_4B4590((int)this, pszArg3, 1u, nArg4);
  *uArg2 = *(this + 1) + 152 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4B4FB0 sub_4B4FB0
// ------------------------------------------------------------
void /*cdecl*/ sub_4B4FB0(uint32_t *uArg1, int nArg2, void *pArg3)
{
  uint32_t *uArg12; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v5[4] = v5;
  v5[3] = uArg1;
  v6 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v6) = 1;
    if ( uArg12 != nullptr )
    {
      sub_435020(pArg3);
      uArg12[4] = *((uint32_t *)pArg3 + 4);
      uArg12[5] = *((uint32_t *)pArg3 + 5);
    }
    --nArg2;
    uArg12 += 6;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x4B5060 sub_4B5060
// ------------------------------------------------------------
unsigned int ***/*cdecl*/ sub_4B5060(int nArg1, int nArg2, unsigned int ***uArg3)
{
  unsigned int ***uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )
      sub_4B3600(uArg32, nArg1);
    uArg32 += 4;
    LOBYTE(v7) = 0;
    nArg1 += 16;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x4B50F0 sub_4B50F0 —— 职业代表特效粒子表（格斗 NenMaster / 漫游 Ranger / 元素 ElementalMaster / 鬼泣 SoulBringer .ptl）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4B50F0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3, uint8_t *uArg4, void *Block, int nArg6, int nArg7)
{
  uint32_t *v7; // esi
  uint32_t *pMem4; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // esi
  uint32_t *pMem; // eax
  uint32_t *v13; // eax
  uint32_t *pMem2; // eax
  uint32_t *v15; // eax
  uint32_t *pMem3; // eax
  uint32_t *v17; // eax

  v7 = nullptr;
  if ( Block != nullptr )
  {
    if ( Block == (void *)1 )
    {
      if ( nArg6 != 1 )
        return v7;
      pMem = operator new(0x12Cu);
      if ( pMem != nullptr )
        v13 = sub_428F30(pMem, (int)"Character/Fighter/Effect/Particle/NenMaster.ptl", nArg7);
      else
        v13 = nullptr;
      v7 = v13;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v13 + 112))(v13, nArg7);
      *uArg1 = 0;
      *uArg2 = -1;
      *uArg3 = 55;
    }
    else if ( Block == (void *)2 )
    {
      if ( nArg6 != 1 )
        return v7;
      pMem2 = operator new(0x12Cu);
      if ( pMem2 != nullptr )
        v15 = sub_428F30(pMem2, (int)"Character/Gunner/Effect/Particle/Ranger.ptl", nArg7);
      else
        v15 = nullptr;
      v7 = v15;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v15 + 112))(v15, nArg7);
      *uArg1 = 7;
      *uArg2 = 0;
      *uArg3 = 114;
    }
    else
    {
      if ( Block != (void *)3 || nArg6 != 1 )
        return v7;
      pMem3 = operator new(0x12Cu);
      if ( pMem3 != nullptr )
        v17 = sub_428F30(pMem3, (int)"Character/Mage/Effect/Particle/ElementalMaster.ptl", nArg7);
      else
        v17 = nullptr;
      v7 = v17;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v17 + 112))(v17, nArg7);
      *uArg1 = 0;
      *uArg2 = -1;
      *uArg3 = 20;
    }
    *uArg4 = 1;
    return v7;
  }
  if ( nArg6 != 2 )
    return v7;
  pMem4 = operator new(0x12Cu);
  if ( pMem4 != nullptr )
    v9 = sub_428F30(pMem4, (int)"Character/Swordman/Effect/Particle/SoulBringer.ptl", nArg7);
  else
    v9 = nullptr;
  v10 = v9;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*v9 + 112))(v9, nArg7);
  *uArg1 = 0;
  *uArg2 = -1;
  *uArg3 = 70;
  *uArg4 = 1;
  return v10;
}



// ------------------------------------------------------------
// 0x4B52F0 sub_4B52F0
// ------------------------------------------------------------
char */*thiscall*/ sub_4B52F0(int this, int nArg2)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  char *fld_82; // edi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 152;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 152 )
    return (char *)sub_4B4F40((uint32_t *)this, &nArg2, *(char **)(this + 8), nArg2);
  fld_82 = *(char **)(this + 8);
  result = sub_4B3550(fld_82, 1, nArg2);
  *(uint32_t *)(this + 8) = fld_82 + 152;
  return result;
}



// ------------------------------------------------------------
// 0x4B5380 sub_4B5380
// ------------------------------------------------------------
int /*stdcall*/ sub_4B5380(int nArg1, int nArg2)
{
  return sub_4B4950(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x4B53A0 sub_4B53A0
// ------------------------------------------------------------
void /*thiscall*/ sub_4B53A0(int *this)
{
  int fld_e1; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
  {
    sub_4B4950(fld_e1, *(this + 2));
    j__free((void *)*(this + 1));
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x4B53F0 sub_4B53F0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4B53F0(uint32_t *pArg1, int nArg2, void *pArg3)
{
  sub_4B4FB0(pArg1, nArg2, pArg3);
  return &pArg1[6 * nArg2];
}



// ------------------------------------------------------------
// 0x4B5420 sub_4B5420
// ------------------------------------------------------------
void /*thiscall*/ sub_4B5420(int *this, char *pszArg2, unsigned int uArg3, void *pArg4)
{
  int v5; // ecx
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v11; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v15; // edi
  void *fld_e14; // eax
  char *fld_e23; // ecx
  int fld_e26; // edi
  void *fld_e12; // [esp-18h] [ebp-54h]
  uint32_t *fld_e25; // [esp-Ch] [ebp-48h]
  int fld_e24; // [esp-8h] [ebp-44h]
  int v23; // [esp+0h] [ebp-3Ch] BYREF
  char v24[4]; // [esp+Ch] [ebp-30h] BYREF
  void *v25; // [esp+10h] [ebp-2Ch]
  int v26; // [esp+1Ch] [ebp-20h]
  int v27; // [esp+20h] [ebp-1Ch]
  void *Block; // [esp+24h] [ebp-18h]
  int *pThis; // [esp+28h] [ebp-14h]
  int *v30; // [esp+2Ch] [ebp-10h]
  int v31; // [esp+38h] [ebp-4h]
  char *v32; // [esp+44h] [ebp+8h]
  uint32_t *v33; // [esp+48h] [ebp+Ch]
  int v34; // [esp+4Ch] [ebp+10h]
  void *fld_e232; // [esp+4Ch] [ebp+10h]

  v30 = &v23;
  pThis = this;
  sub_435020(pArg4);
  v5 = *((uint32_t *)pArg4 + 5);
  v26 = *((uint32_t *)pArg4 + 4);
  v27 = v5;
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 24;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 24;
    else
      fld_e2 = 0;
    if ( 178956970 - fld_e2 < uArg3 )
      sub_434730(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 24;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pszArg2) / 24 >= uArg3 )
      {
        v32 = &fld_e23[-24 * uArg3];
        *(this + 2) = sub_437A50(v32, (int)fld_e23, fld_e23);
        sub_4B4930((int)pszArg2, (int)v32, (int)fld_e232);
        sub_4B48F0((int)pszArg2, (int)&pszArg2[24 * uArg3], (int)v24);
      }
      else
      {
        sub_437A50(pszArg2, (int)fld_e23, &pszArg2[24 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 24;
        fld_e25 = (uint32_t *)*(this + 2);
        LOBYTE(v31) = 3;
        sub_4B53F0(fld_e25, fld_e24, v24);
        fld_e26 = 24 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v31 = 0;
        sub_4B48F0((int)pszArg2, fld_e26 - 24 * uArg3, (int)v24);
      }
    }
    else
    {
      if ( 178956970 - (fld_e3 >> 1) >= fld_e3 )
        v11 = (fld_e3 >> 1) + fld_e3;
      else
        v11 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 24;
      else
        fld_e27 = 0;
      if ( v11 < uArg3 + fld_e27 )
        v11 = uArg3 + sub_4FEF30(this);
      v34 = 24 * v11;
      pMem = (char *)operator new(24 * v11);
      fld_e12 = (void *)*(this + 1);
      Block = pMem;
      LOBYTE(v31) = 1;
      v33 = (uint32_t *)sub_437A50(fld_e12, (int)pszArg2, pMem);
      sub_4B4FB0(v33, uArg3, v24);
      sub_437A50(pszArg2, *(this + 2), &v33[6 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 24;
      v15 = fld_e13 + uArg3;
      fld_e14 = (void *)*(this + 1);
      if ( fld_e14 != nullptr )
      {
        sub_435820(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v34];
      *(this + 2) = (int)&pMem[24 * v15];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v25 != nullptr )
    j__free(v25);
}


// ------------------------------------------------------------
// 0x4B5720 sub_4B5720
// ------------------------------------------------------------
unsigned int ***/*stdcall*/ sub_4B5720(int nArg1, int nArg2, unsigned int ***uArg3)
{
  return sub_4B5060(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x4B5740 sub_4B5740
// ------------------------------------------------------------
int */*thiscall*/ sub_4B5740(int *this, int *pDwArg2)
{
  int v3; // ebx
  unsigned int v4; // eax
  int fld_e1; // ecx
  unsigned int fld_e2; // edx
  int v8; // eax
  int v9; // eax
  int fld_e12; // edi
  unsigned int fld_e3; // edx
  int fld_e22; // eax
  int v13; // ebx
  int v14; // ecx
  unsigned int v15; // eax

  if ( this == pDwArg2 )
    return this;
  v3 = pDwArg2[1];
  if ( v3 == 0 || (v4 = (pDwArg2[2] - v3) >> 4) == 0 )
  {
    sub_4B53A0(this);
    return this;
  }
  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 4;
  else
    fld_e2 = 0;
  if ( v4 <= fld_e2 )
  {
    v8 = sub_4B3B60(v3, pDwArg2[2], fld_e1);
    sub_4B4950(v8, *(this + 2));
    v9 = pDwArg2[1];
    if ( v9 != 0 )
      fld_e12 = *(this + 1) + 16 * ((pDwArg2[2] - v9) >> 4);
    else
      fld_e12 = *(this + 1);
    *(this + 2) = fld_e12;
    return this;
  }
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) >> 4;
  else
    fld_e3 = 0;
  if ( v4 > fld_e3 )
  {
    if ( fld_e1 != 0 )
    {
      sub_4B5380(fld_e1, *(this + 2));
      j__free((void *)*(this + 1));
    }
    v14 = pDwArg2[1];
    if ( v14 != 0 )
      v15 = (pDwArg2[2] - v14) >> 4;
    else
      v15 = 0;
    if ( sub_4B3420(this, v15) != 0 )
      *(this + 2) = (int)sub_4B5720(pDwArg2[1], pDwArg2[2], (unsigned int ***)*(this + 1));
    return this;
  }
  if ( fld_e1 != 0 )
    fld_e22 = (*(this + 2) - fld_e1) >> 4;
  else
    fld_e22 = 0;
  v13 = pDwArg2[1] + 16 * fld_e22;
  sub_4B48D0(pDwArg2[1], v13, *(this + 1));
  *(this + 2) = (int)sub_4B5060(v13, pDwArg2[2], (unsigned int ***)*(this + 2));
  return this;
}



// ------------------------------------------------------------
// 0x4B58A0 sub_4B58A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B58A0(int *this, uint32_t *uArg2, char *pszArg3, void *pArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 24;
  else
    v6 = 0;
  sub_4B5420(this, pszArg3, 1u, pArg4);
  *uArg2 = *(this + 1) + 24 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4B5910 sub_4B5910
// ------------------------------------------------------------
void /*thiscall*/ sub_4B5910(int this, void *pArg2)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 24;
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) / 24 )
  {
    fld_82 = *(uint32_t **)(this + 8);
    sub_4B4FB0(fld_82, 1, pArg2);
    *(uint32_t *)(this + 8) = fld_82 + 6;
  }
  else
  {
    sub_4B58A0((int *)this, &pArg2, *(char **)(this + 8), pArg2);
  }
}



// ============================================================
// §I 0x4B59A0-0x4B5FD0  角色动画包装器
// ============================================================
// ------------------------------------------------------------
// 0x4B59A0 sub_4B59A0 —— 角色动画包装器复位（+204 子动画链、sub_493BD0 复位 / sub_494610 帧数组重置）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B59A0(int this, unsigned int uArg2)
{
  uint32_t *pThis_3C; // ecx

  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &off_6C2B88;
  *(uint32_t *)(this + 8) = 0;
  *(uint8_t *)(this + 12) = 1;
  *(uint8_t *)(this + 14) = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  pThis_3C = (uint32_t *)(this + 60);
  pThis_3C[15] = 0;
  pThis_3C[16] = 0;
  pThis_3C[17] = 0;
  pThis_3C[19] = 0;
  pThis_3C[20] = 0;
  pThis_3C[21] = 0;
  sub_430B70(pThis_3C);
  *(uint32_t *)(this + 204) = sub_4A2CF0();
  *(uint32_t *)(this + 208) = 0;
  sub_493BD0(this);
  sub_494610((int *)this, uArg2);
  return this;
}



// ------------------------------------------------------------
// 0x4B5A50 sub_4B5A50
// ------------------------------------------------------------
int /*thiscall*/ sub_4B5A50(void ***this)
{
  void **v2; // esi
  void ***pThis_5; // esi
  int v4; // ebx
  void **v5; // ebx
  bool v6; // zf
  int result; // eax
  int fld_e9; // esi
  void **fld_e10; // esi
  void **fld_e11; // esi
  void **fld_e12; // esi
  int v12; // [esp+Ch] [ebp-4h]

  v2 = *this;
  if ( *this != nullptr )
  {
    sub_42AF90(*this);
    sub_657740(v2, 228);
  }
  *this = nullptr;
  pThis_5 = this + 5;
  v12 = 4;
  do
  {
    v4 = (int)*(pThis_5 - 4);
    if ( v4 != 0 )
    {
      sub_42AF90(*(pThis_5 - 4));
      sub_657740(v4, 228);
    }
    v5 = *pThis_5;
    v6 = *pThis_5 == nullptr;
    *(pThis_5 - 4) = nullptr;
    if ( !v6 )
    {
      sub_42AF90(v5);
      sub_657740(v5, 228);
    }
    *pThis_5++ = nullptr;
    result = v12 - 1;
    v12 = result;
  }
  while ( result != 0 );
  fld_e9 = (int)*(this + 9);
  if ( fld_e9 != 0 )
  {
    sub_42AF90(*(this + 9));
    result = sub_657740(fld_e9, 228);
  }
  fld_e10 = *(this + 10);
  *(this + 9) = nullptr;
  if ( fld_e10 != nullptr )
  {
    sub_42AF90(fld_e10);
    result = sub_657740(fld_e10, 228);
  }
  fld_e11 = *(this + 11);
  *(this + 10) = nullptr;
  if ( fld_e11 != nullptr )
  {
    sub_42AF90(fld_e11);
    result = sub_657740(fld_e11, 228);
  }
  fld_e12 = *(this + 12);
  *(this + 11) = nullptr;
  if ( fld_e12 != nullptr )
  {
    sub_42AF90(fld_e12);
    result = sub_657740(fld_e12, 228);
  }
  *(this + 12) = nullptr;
  return result;
}



// ------------------------------------------------------------
// 0x4B5B80 sub_4B5B80
// ------------------------------------------------------------
void sub_4B5B80()
{
  char *v0; // edx
  uint32_t *dword_9A03182; // edx
  char *v2; // edx
  uint32_t *dword_9A03282; // edx
  int v4; // ebx
  char *v5; // edi
  int v6; // ebx
  char *v7; // edi
  char v8[4]; // [esp+Ch] [ebp-30h] BYREF
  void *Block; // [esp+10h] [ebp-2Ch]
  int v10; // [esp+14h] [ebp-28h]
  int v11; // [esp+18h] [ebp-24h]
  int v12; // [esp+1Ch] [ebp-20h]
  int v13; // [esp+20h] [ebp-1Ch]
  int v14; // [esp+24h] [ebp-18h] BYREF
  int v15; // [esp+28h] [ebp-14h] BYREF
  int v16[4]; // [esp+2Ch] [ebp-10h] BYREF

  v0 = (char *)dword_9A0318;
  v16[0] = 2;
  if ( dword_9A0314 != 0 && ((int)dword_9A0318 - dword_9A0314) >> 2 < (unsigned int)((dword_9A031C - dword_9A0314) >> 2) )
  {
    *(uint32_t *)dword_9A0318 = 2;
    dword_9A03182 = v0 + 4;
    dword_9A0318 = dword_9A03182;
  }
  else
  {
    sub_430C80(dword_9A0318, 1, (int)v16);
    dword_9A03182 = dword_9A0318;
  }
  v16[0] = 3;
  if ( dword_9A0314 != 0 && ((int)dword_9A03182 - dword_9A0314) >> 2 < (unsigned int)((dword_9A031C - dword_9A0314) >> 2) )
  {
    *dword_9A03182 = 3;
    dword_9A0318 = dword_9A03182 + 1;
  }
  else
  {
    sub_430C80(dword_9A03182, 1, (int)v16);
  }
  v2 = (char *)dword_9A0328;
  v16[0] = 0;
  if ( dword_9A0324 != 0 && ((int)dword_9A0328 - dword_9A0324) >> 2 < (unsigned int)((dword_9A032C - dword_9A0324) >> 2) )
  {
    *(uint32_t *)dword_9A0328 = 0;
    dword_9A03282 = v2 + 4;
    dword_9A0328 = dword_9A03282;
  }
  else
  {
    sub_430C80(dword_9A0328, 1, (int)v16);
    dword_9A03282 = dword_9A0328;
  }
  v16[0] = 1;
  if ( dword_9A0324 != 0 && ((int)dword_9A03282 - dword_9A0324) >> 2 < (unsigned int)((dword_9A032C - dword_9A0324) >> 2) )
  {
    *dword_9A03282 = 1;
    dword_9A0328 = dword_9A03282 + 1;
  }
  else
  {
    sub_430C80(dword_9A03282, 1, (int)v16);
  }
  v16[3] = 0;
  Block = nullptr;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 300;
  v16[0] = 5;
  sub_430C80(nullptr, 1, (int)v16);
  sub_4B5910(v8);
  sub_4C0090(&unk_9A0330);
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 300;
  v16[0] = 6;
  sub_430C80(nullptr, 1, (int)v16);
  sub_4B5910(v8);
  sub_4C0090(&unk_9A035C);
  v4 = 0;
  v5 = (char *)&unk_9A0388;
  do
  {
    if ( Block != nullptr )
      j__free(Block);
    v16[0] = 3 - (v4 != 0);
    Block = nullptr;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    sub_430C80(nullptr, 1, (int)v16);
    v13 = 500;
    sub_4B5910(v8);
    sub_4B5910(v8);
    sub_4C0090(v5);
    v5 += 44;
    ++v4;
  }
  while ( (int)v5 < (int)byte_9A03E0 );
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 300;
  v16[0] = 7;
  sub_430C80(nullptr, 1, (int)v16);
  v13 = 500;
  sub_4B5910(v8);
  v6 = 1;
  v14 = 7;
  v15 = 1;
  v7 = (char *)&unk_9A040C;
  do
  {
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v10 = 0;
    v16[0] = (v6 != 1) + 2;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    sub_430C80(nullptr, 1, (int)v16);
    v13 = 350;
    sub_4B5910(v8);
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    sub_430C80(nullptr, 1, (int)&v15);
    v13 = 350;
    sub_4B5910(v8);
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    v16[0] = 3 - (v6 != 1);
    sub_430C80(nullptr, 1, (int)v16);
    v13 = 350;
    sub_4B5910(v8);
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    sub_430C80(nullptr, 1, (int)&v14);
    v13 = 500;
    sub_4B5910(v8);
    v7 += 44;
    ++v6;
  }
  while ( (int)v7 < (int)byte_9A0464 );
  sub_5EEA20();
  sub_5E50B0();
  sub_4C5240();
  sub_5DB3E0();
  if ( Block != nullptr )
    j__free(Block);
}


// ============================================================
// §J 0x4B5FD0-0x4B7110  ★.equ 部件解析装载（CHARACTER CREATE FAIL）
// ============================================================
// ------------------------------------------------------------
// 0x4B5FD0 sub_4B5FD0 —— ★.equ 部件记录解析装载
//   经资源管理器(dword_8F84C0 vtable+4)打开 .equ → 逐部件块解析：sub_4B2970 部件记录
//   （名称/路径 +40..56）、sub_4B52F0/sub_4B5740 部件组、sub_480210 部位动画；失败
//   CHARACTER CREATE FAIL! FILENAME[%s]。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B5FD0(uint32_t *this, int ArgList)
{
  const char *v2; // esi
  int v3; // eax
  uint32_t *v4; // ebx
  unsigned int v5; // eax
  int v6; // esi
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // esi
  int v12; // eax
  uint32_t *v13; // edi
  int *v14; // esi
  int v15; // ecx
  int v16; // eax
  int v17; // esi
  int v18; // eax
  uint32_t *pThis2; // edi
  int v20; // esi
  int v21; // eax
  int v22; // esi
  int v23; // eax
  int v24; // esi
  int v25; // eax
  int v26; // esi
  int v27; // eax
  uint32_t *v28; // ebx
  int v29; // ecx
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  bool v33; // zf
  uint32_t *v34; // ebx
  int v35; // esi
  int v36; // eax
  int v37; // esi
  int v38; // eax
  int v39; // esi
  int v40; // eax
  int v41; // esi
  int v42; // eax
  int v43; // eax
  int v44; // ebx
  uint32_t *v45; // ebx
  int v46; // edi
  char v47; // al
  int v48; // eax
  int v49; // edx
  unsigned int v50; // esi
  int *v51; // ecx
  int v52; // edx
  unsigned int v53; // ecx
  uint32_t *v54; // eax
  uint32_t *v55; // ecx
  int v56; // edx
  uint32_t *v57; // ebx
  int v58; // edi
  char v59; // al
  int v60; // eax
  int v61; // edx
  unsigned int v62; // esi
  int *v63; // ecx
  int v64; // edx
  unsigned int v65; // ecx
  uint32_t *v66; // eax
  uint32_t *v67; // eax
  int v68; // edx
  uint32_t *v69; // ebx
  uint32_t *v70; // edx
  uint32_t *v71; // ecx
  int v72; // eax
  uint32_t *v73; // edx
  uint32_t *v74; // ecx
  int v75; // eax
  uint32_t *v76; // esi
  int v77; // edi
  int v78; // eax
  int v79; // eax
  int v80; // ecx
  uint32_t *v81; // esi
  int v82; // edi
  int v83; // eax
  int v84; // eax
  int v85; // ecx
  uint32_t *pThis3; // esi
  int v87; // edx
  int v88; // edx
  unsigned int i; // edi
  int v90; // ecx
  int v92; // [esp-8h] [ebp-C4h]
  uint32_t v93[23]; // [esp+8h] [ebp-B4h] BYREF
  void *Block; // [esp+68h] [ebp-54h]
  int v95; // [esp+78h] [ebp-44h]
  unsigned int v96; // [esp+7Ch] [ebp-40h]
  int v97; // [esp+A0h] [ebp-1Ch]
  int v98; // [esp+A4h] [ebp-18h] BYREF
  uint32_t *v99; // [esp+A8h] [ebp-14h]
  uint32_t *pThis; // [esp+ACh] [ebp-10h]
  int v101; // [esp+B8h] [ebp-4h]

  v2 = (const char *)ArgList;
  pThis = this;
  v3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84C0 + 4))(dword_8F84C0, ArgList);
  v4 = (uint32_t *)v3;
  v99 = (uint32_t *)v3;
  if ( v3 == 0 )
  {
    LOBYTE(v5) = off_77F3FC("CHARACTER CREATE FAIL! FILENAME[%s]", v2);
    return v5;
  }
  v6 = (int)pThis;
  sub_4014D0((std::_String_base *)(pThis + 90), v3 + 1640, 0, -1);
  pThis[1787] = *v4;
  *(uint32_t *)(v6 + 316) = v4[36];
  *(uint32_t *)(v6 + 320) = v4[37];
  v6 += 328;
  sub_4ED3F0(v6, (int)(v4 + 181));
  ArgList = 16;
  sub_431230(v6, &ArgList);
  if ( sub_40BF00((std::_String_base *)(v4 + 206), 0, v4[211], szPassword, 0) != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 0;
    if ( ArgList != 0 )
    {
      if ( v4[212] < 0x10u )
        LOBYTE(v7) = (uint8_t)v4 + 60;
      else
        v7 = v4[207];
      if ( v4[416] < 0x10u )
        v8 = sub_431920((uint8_t)v4 + 108, v7, 1);
      else
        v8 = sub_431920(v4[411], v7, 1);
    }
    else
    {
      v8 = 0;
    }
    v101 = -1;
    pThis[1540] = v8;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 213), 0, v4[218], szPassword, 0) != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 1;
    if ( ArgList != 0 )
    {
      if ( v4[219] < 0x10u )
        LOBYTE(v9) = (uint8_t)v4 + 88;
      else
        v9 = v4[214];
      if ( v4[416] < 0x10u )
        v10 = sub_431920((uint8_t)v4 + 108, v9, 1);
      else
        v10 = sub_431920(v4[411], v9, 1);
    }
    else
    {
      v10 = 0;
    }
    v101 = -1;
    pThis[1541] = v10;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 220), 0, v4[225], szPassword, 0) != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 2;
    if ( ArgList != 0 )
    {
      if ( v4[226] < 0x10u )
        LOBYTE(v11) = (uint8_t)v4 + 116;
      else
        v11 = v4[221];
      if ( v4[416] < 0x10u )
        v12 = sub_431920((uint8_t)v4 + 108, v11, 1);
      else
        v12 = sub_431920(v4[411], v11, 1);
    }
    else
    {
      v12 = 0;
    }
    v101 = -1;
    pThis[1542] = v12;
  }
  v13 = pThis + 1543;
  v14 = v4 + 228;
  for ( ArgList = 2; ArgList != 0; --ArgList )
  {
    if ( sub_40BF00((std::_String_base *)(v14 - 1), 0, v14[4], szPassword, 0) != 0 )
    {
      v98 = sub_42FCB0(228);
      v101 = 3;
      if ( v98 != 0 )
      {
        if ( (unsigned int)v14[5] < 0x10 )
          LOBYTE(v15) = (uint8_t)v14;
        else
          v15 = *v14;
        if ( v4[416] < 0x10u )
          v16 = sub_431920((uint8_t)v4 + 108, v15, 1);
        else
          v16 = sub_431920(v4[411], v15, 1);
      }
      else
      {
        v16 = 0;
      }
      v101 = -1;
      *v13 = v16;
    }
    ++v13;
    v14 += 7;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 241), 0, v4[246], szPassword, 0) != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 4;
    if ( ArgList != 0 )
    {
      if ( v4[247] < 0x10u )
        LOBYTE(v17) = (uint8_t)v4 - 56;
      else
        v17 = v4[242];
      if ( v4[416] < 0x10u )
        v18 = sub_431920((uint8_t)v4 + 108, v17, 1);
      else
        v18 = sub_431920(v4[411], v17, 1);
    }
    else
    {
      v18 = 0;
    }
    pThis2 = pThis;
    v101 = -1;
    pThis[1545] = v18;
  }
  else
  {
    pThis2 = pThis;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 248), 0, v4[253], szPassword, 0) != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 5;
    if ( ArgList != 0 )
    {
      if ( v4[254] < 0x10u )
        LOBYTE(v20) = (uint8_t)v4 - 28;
      else
        v20 = v4[249];
      if ( v4[416] < 0x10u )
        v21 = sub_431920((uint8_t)v4 + 108, v20, 1);
      else
        v21 = sub_431920(v4[411], v20, 1);
    }
    else
    {
      v21 = 0;
    }
    v101 = -1;
    pThis2[1546] = v21;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 255), 0, v4[260], szPassword, 0) != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 6;
    if ( ArgList != 0 )
    {
      if ( v4[261] < 0x10u )
        LOBYTE(v22) = (uint8_t)v4;
      else
        v22 = v4[256];
      if ( v4[416] < 0x10u )
        v23 = sub_431920((uint8_t)v4 + 108, v22, 1);
      else
        v23 = sub_431920(v4[411], v22, 1);
    }
    else
    {
      v23 = 0;
    }
    v101 = -1;
    pThis2[1547] = v23;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 262), 0, v4[267], szPassword, 0) != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 7;
    if ( ArgList != 0 )
    {
      if ( v4[268] < 0x10u )
        LOBYTE(v24) = (uint8_t)v4 + 28;
      else
        v24 = v4[263];
      if ( v4[416] < 0x10u )
        v25 = sub_431920((uint8_t)v4 + 108, v24, 1);
      else
        v25 = sub_431920(v4[411], v24, 1);
    }
    else
    {
      v25 = 0;
    }
    v101 = -1;
    pThis2[1548] = v25;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 269), 0, v4[274], szPassword, 0) != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 8;
    if ( ArgList != 0 )
    {
      if ( v4[275] < 0x10u )
        LOBYTE(v26) = (uint8_t)v4 + 56;
      else
        v26 = v4[270];
      if ( v4[416] < 0x10u )
        v27 = sub_431920((uint8_t)v4 + 108, v26, 1);
      else
        v27 = sub_431920(v4[411], v26, 1);
    }
    else
    {
      v27 = 0;
    }
    v101 = -1;
    pThis2[1803] = v27;
  }
  ArgList = (int)(pThis2 + 1808);
  v28 = v4 + 281;
  v98 = 4;
  do
  {
    if ( *v28 != 0 )
    {
      v97 = sub_42FCB0(228);
      v101 = 9;
      if ( v97 != 0 )
      {
        if ( v28[1] < 0x10u )
          LOBYTE(v29) = (uint8_t)v28 - 16;
        else
          v29 = *(v28 - 4);
        if ( v99[416] < 0x10u )
          v30 = sub_431920((uint8_t)v99 + 108, v29, 1);
        else
          v30 = sub_431920(v99[411], v29, 1);
      }
      else
      {
        v30 = 0;
      }
      v101 = -1;
      *(uint32_t *)(ArgList - 16) = v30;
    }
    if ( v28[28] != 0 )
    {
      v97 = sub_42FCB0(228);
      v101 = 10;
      if ( v97 != 0 )
      {
        if ( v28[29] < 0x10u )
          LOBYTE(v31) = (uint8_t)v28 + 96;
        else
          v31 = v28[24];
        if ( v99[416] < 0x10u )
          v32 = sub_431920((uint8_t)v99 + 108, v31, 1);
        else
          v32 = sub_431920(v99[411], v31, 1);
      }
      else
      {
        v32 = 0;
      }
      v101 = -1;
      *(uint32_t *)ArgList = v32;
    }
    v28 += 7;
    v33 = v98 == 1;
    ArgList += 4;
    --v98;
  }
  while ( !v33 );
  if ( v99[337] != 0 )
  {
    ArgList = sub_42FCB0(228);
    v34 = v99;
    v101 = 11;
    if ( ArgList != 0 )
    {
      if ( v99[338] < 0x10u )
        LOBYTE(v35) = (uint8_t)v99 + 52;
      else
        v35 = v99[333];
      if ( v99[416] < 0x10u )
        v36 = sub_431920((uint8_t)v99 + 108, v35, 1);
      else
        v36 = sub_431920(v99[411], v35, 1);
    }
    else
    {
      v36 = 0;
    }
    v101 = -1;
    pThis[1812] = v36;
  }
  else
  {
    v34 = v99;
  }
  if ( v34[344] != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 12;
    if ( ArgList != 0 )
    {
      if ( v34[345] < 0x10u )
        LOBYTE(v37) = (uint8_t)v34 + 80;
      else
        v37 = v34[340];
      if ( v34[416] < 0x10u )
        v38 = sub_431920((uint8_t)v34 + 108, v37, 1);
      else
        v38 = sub_431920(v34[411], v37, 1);
    }
    else
    {
      v38 = 0;
    }
    v101 = -1;
    pThis[1813] = v38;
  }
  if ( v34[351] != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 13;
    if ( ArgList != 0 )
    {
      if ( v34[352] < 0x10u )
        LOBYTE(v39) = (uint8_t)v34 + 108;
      else
        v39 = v34[347];
      if ( v34[416] < 0x10u )
        v40 = sub_431920((uint8_t)v34 + 108, v39, 1);
      else
        v40 = sub_431920(v34[411], v39, 1);
    }
    else
    {
      v40 = 0;
    }
    v101 = -1;
    pThis[1814] = v40;
  }
  if ( v34[358] != 0 )
  {
    ArgList = sub_42FCB0(228);
    v101 = 14;
    if ( ArgList != 0 )
    {
      if ( v34[359] < 0x10u )
        LOBYTE(v41) = (uint8_t)v34 - 120;
      else
        v41 = v34[354];
      if ( v34[416] < 0x10u )
        v42 = sub_431920((uint8_t)v34 + 108, v41, 1);
      else
        v42 = sub_431920(v34[411], v41, 1);
    }
    else
    {
      v42 = 0;
    }
    v101 = -1;
    pThis[1815] = v42;
  }
  v43 = v34[361];
  v44 = v34[362];
  ArgList = v43;
  if ( v43 != v44 )
  {
    v45 = pThis + 1549;
    while ( 1 )
    {
      if ( strcmp((const char *)sub_41ACF0(ArgList), szPassword) == 0 )
      {
        v52 = v45[1];
        v98 = 0;
        if ( v52 != 0 )
          v53 = (v45[2] - v52) >> 2;
        else
          v53 = 0;
        if ( v52 == 0 || v53 >= (v45[3] - v52) >> 2 )
          goto LABEL_181;
        v54 = (uint32_t *)v45[2];
        *v54 = 0;
        v45[2] = v54 + 1;
      }
      else
      {
        v97 = sub_42FCB0(228);
        v101 = 15;
        if ( v97 != 0 )
        {
          if ( v99[416] < 0x10u )
            LOBYTE(v46) = (uint8_t)v99 + 108;
          else
            v46 = v99[411];
          v47 = sub_41ACF0(ArgList);
          v48 = sub_431920(v46, v47, 1);
        }
        else
        {
          v48 = 0;
        }
        v49 = v45[1];
        v101 = -1;
        v98 = v48;
        if ( v49 != 0 )
          v50 = (v45[2] - v49) >> 2;
        else
          v50 = 0;
        if ( v49 == 0 || v50 >= (v45[3] - v49) >> 2 )
        {
LABEL_181:
          sub_42AC90((void *)v45[2], 1, (int)&v98);
          goto LABEL_182;
        }
        v51 = (int *)v45[2];
        *v51 = v48;
        v45[2] = v51 + 1;
      }
LABEL_182:
      v55 = v99;
      v56 = v99[362];
      ArgList += 4;
      if ( ArgList == v56 )
        goto LABEL_185;
    }
  }
  v55 = v99;
LABEL_185:
  v33 = v55[365] == v55[366];
  ArgList = v55[365];
  if ( !v33 )
  {
    v57 = pThis + 1553;
    while ( 1 )
    {
      if ( strcmp((const char *)sub_41ACF0(ArgList), szPassword) == 0 )
      {
        v64 = v57[1];
        v98 = 0;
        if ( v64 != 0 )
          v65 = (v57[2] - v64) >> 2;
        else
          v65 = 0;
        if ( v64 == 0 || v65 >= (v57[3] - v64) >> 2 )
          goto LABEL_207;
        v66 = (uint32_t *)v57[2];
        *v66 = 0;
        v57[2] = v66 + 1;
      }
      else
      {
        v97 = sub_42FCB0(228);
        v101 = 16;
        if ( v97 != 0 )
        {
          if ( v99[416] < 0x10u )
            LOBYTE(v58) = (uint8_t)v99 + 108;
          else
            v58 = v99[411];
          v59 = sub_41ACF0(ArgList);
          v60 = sub_431920(v58, v59, 1);
        }
        else
        {
          v60 = 0;
        }
        v61 = v57[1];
        v101 = -1;
        v98 = v60;
        if ( v61 != 0 )
          v62 = (v57[2] - v61) >> 2;
        else
          v62 = 0;
        if ( v61 == 0 || v62 >= (v57[3] - v61) >> 2 )
        {
LABEL_207:
          sub_42AC90((void *)v57[2], 1, (int)&v98);
          goto LABEL_208;
        }
        v63 = (int *)v57[2];
        *v63 = v60;
        v57[2] = v63 + 1;
      }
LABEL_208:
      v67 = v99;
      v68 = v99[366];
      ArgList += 4;
      if ( ArgList == v68 )
        goto LABEL_211;
    }
  }
  v67 = v99;
LABEL_211:
  if ( v67[380] != 0 )
  {
    v69 = v99;
    if ( v99[381] < 0x10u )
      v70 = v99 + 376;
    else
      v70 = (uint32_t *)v99[376];
    if ( v99[416] < 0x10u )
      v71 = v99 + 411;
    else
      v71 = (uint32_t *)v99[411];
    v72 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E0 + 12))(dword_8F84E0, "%s%s", v71, v70);
    sub_4B2970(pThis + 1816, v72);
  }
  else
  {
    v69 = v99;
  }
  if ( v69[373] != 0 )
  {
    if ( v69[374] < 0x10u )
      v73 = v69 + 369;
    else
      v73 = (uint32_t *)v69[369];
    if ( v69[416] < 0x10u )
      v74 = v69 + 411;
    else
      v74 = (uint32_t *)v69[411];
    v75 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E0 + 12))(dword_8F84E0, "%s%s", v74, v73);
    sub_4B2970(pThis + 1579, v75);
  }
  v33 = v69[383] == v69[384];
  ArgList = v69[383];
  if ( !v33 )
  {
    do
    {
      if ( strcmp((const char *)sub_41ACF0(ArgList), szPassword) == 0 )
      {
        v96 = 15;
        v95 = 0;
        LOBYTE(Block) = 0;
        v101 = 17;
        sub_4A3450(v93);
        v101 = 18;
        sub_4B52F0(v93);
        v101 = -1;
        if ( v96 >= 0x10 )
          j__free(Block);
        v96 = 15;
        v95 = 0;
        LOBYTE(Block) = 0;
      }
      else
      {
        if ( v69[416] < 0x10u )
          v76 = v69 + 411;
        else
          v76 = (uint32_t *)v69[411];
        v77 = *(uint32_t *)dword_8F84E0;
        v78 = sub_41ACF0(ArgList);
        v79 = (*(int (**)(int, const char *, ...))(v77 + 12))(dword_8F84E0, "%s%s", v76, v78);
        sub_4B52F0(v79);
      }
      v80 = v69[384];
      ArgList += 4;
    }
    while ( ArgList != v80 );
  }
  v33 = v69[387] == v69[388];
  ArgList = v69[387];
  if ( !v33 )
  {
    do
    {
      if ( strcmp((const char *)sub_41ACF0(ArgList), szPassword) == 0 )
      {
        v96 = 15;
        v95 = 0;
        LOBYTE(Block) = 0;
        v101 = 19;
        sub_4A3450(v93);
        v101 = 20;
        sub_4B52F0(v93);
        v101 = -1;
        if ( v96 >= 0x10 )
          j__free(Block);
        v96 = 15;
        v95 = 0;
        LOBYTE(Block) = 0;
      }
      else
      {
        if ( v69[416] < 0x10u )
          v81 = v69 + 411;
        else
          v81 = (uint32_t *)v69[411];
        v82 = *(uint32_t *)dword_8F84E0;
        v83 = sub_41ACF0(ArgList);
        v84 = (*(int (**)(int, const char *, ...))(v82 + 12))(dword_8F84E0, "%s%s", v81, v83);
        sub_4B52F0(v84);
      }
      v85 = v69[388];
      ArgList += 4;
    }
    while ( ArgList != v85 );
  }
  pThis3 = pThis;
  sub_4B5740(v69 + 390);
  sub_4ED3F0((int)(pThis3 + 1907), (int)(v69 + 394));
  sub_4ED3F0((int)(pThis3 + 1911), (int)(v69 + 398));
  sub_4ED3F0((int)(pThis3 + 1915), (int)(v69 + 402));
  sub_480210(v69 + 406);
  sub_41A590((unsigned int)(pThis3 + 408), v87, v69[205]);
  LOBYTE(v5) = byte_77F280;
  if ( byte_77F280 != 0 )
  {
    v92 = v69[205];
    *((uint8_t *)v69 + 230) = 100;
    sub_41A590((unsigned int)(pThis3 + 408), v88, v92);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pThis3 + 1048))(pThis3, v69 + 38);
    LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pThis3 + 1056))(pThis3, 1);
  }
  pThis3[162] |= 2u;
  *((uint8_t *)pThis3 + 6668) = 1;
  *((uint8_t *)pThis3 + 6681) = 1;
  *((uint8_t *)pThis3 + 8100) = 0;
  for ( i = 0; ; ++i )
  {
    v90 = pThis3[83];
    if ( v90 == 0 )
      break;
    v5 = (pThis3[84] - v90) >> 2;
    if ( i >= v5 )
      break;
    LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis3 + 464))(pThis3, *(uint32_t *)(v90 + 4 * i));
  }
  return v5;
}


// ============================================================
// §K 0x4B7110-0x4B89D0  升级/结算演出（LevelNormalizeLibra、PVP_KO）
// ============================================================
// ------------------------------------------------------------
// 0x4B7110 sub_4B7110
// ------------------------------------------------------------
int /*thiscall*/ sub_4B7110(int this)
{
  int *pThis_1D5C; // esi
  int i; // edi
  int pObj; // ecx
  int fld_1DA4; // ecx
  void (/*thiscall*/ ***pThis_1DA8)(uint32_t, int); // ecx
  int fld_1E0C; // ecx
  void (/*thiscall*/ ***pThis_1E0C)(uint32_t, int); // ecx
  int fld_1E10; // ecx
  void (/*thiscall*/ ***pThis_1E10)(uint32_t, int); // ecx
  void ***pThis_1E58; // esi
  void **v12; // edi
  void ***pThis_1E68; // esi
  void **v14; // edi
  int fld_1E74; // esi
  void (/*thiscall*/ ***pThis_1E78)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_1F20)(uint32_t, int); // ecx
  void **fld_1F24; // esi
  void (/*thiscall*/ ***pThis_1F28)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_1F2C)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_1F30)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_1F40)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_1F84)(uint32_t, int); // ecx
  void (/*thiscall*/ ****pThis_1F90)(uint32_t, int); // esi
  int m; // edi
  void (/*thiscall*/ ***v26)(uint32_t, int); // ecx
  void (/*thiscall*/ ***v27)(uint32_t, int); // ecx
  bool v28; // zf
  void ***pThis_1FEC; // esi
  int v30; // edi
  void **v31; // edi
  int result; // eax
  int fld_1D04; // ecx
  int fld_1E0C2; // [esp-4h] [ebp-18h]
  int fld_1E102; // [esp-4h] [ebp-18h]
  int n; // [esp+Ch] [ebp-8h]
  int j; // [esp+10h] [ebp-4h]
  int k; // [esp+10h] [ebp-4h]
  int v39; // [esp+10h] [ebp-4h]

  pThis_1D5C = (int *)(this + 7516);
  for ( i = 18; i != 0; --i )
  {
    pObj = *pThis_1D5C;
    if ( *pThis_1D5C != *(pThis_1D5C - 262) )
    {
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
      *pThis_1D5C = 0;
    }
    ++pThis_1D5C;
  }
  fld_1DA4 = *(uint32_t *)(this + 7588);
  if ( fld_1DA4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1DA4 + 4))(fld_1DA4, 1);
  pThis_1DA8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7592);
  *(uint32_t *)(this + 7588) = 0;
  if ( pThis_1DA8 != nullptr )
    (**pThis_1DA8)(pThis_1DA8, 1);
  fld_1E0C = *(uint32_t *)(this + 7692);
  *(uint32_t *)(this + 7592) = 0;
  if ( fld_1E0C != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_1E0C + 80))(fld_1E0C) != 0 )
  {
    fld_1E0C2 = *(uint32_t *)(this + 7692);
    (*(void (**)(void))(*(uint32_t *)fld_1E0C2 + 80))();
    sub_45F1E0(fld_1E0C2);
  }
  pThis_1E0C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7692);
  if ( pThis_1E0C != nullptr )
    (**pThis_1E0C)(pThis_1E0C, 1);
  fld_1E10 = *(uint32_t *)(this + 7696);
  *(uint32_t *)(this + 7692) = 0;
  if ( fld_1E10 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_1E10 + 80))(fld_1E10) != 0 )
  {
    fld_1E102 = *(uint32_t *)(this + 7696);
    (*(void (**)(void))(*(uint32_t *)fld_1E102 + 80))();
    sub_45F1E0(fld_1E102);
  }
  pThis_1E10 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7696);
  if ( pThis_1E10 != nullptr )
    (**pThis_1E10)(pThis_1E10, 1);
  *(uint32_t *)(this + 7696) = 0;
  pThis_1E58 = (void ***)(this + 7768);
  for ( j = 3; j != 0; --j )
  {
    v12 = *pThis_1E58;
    if ( *pThis_1E58 != nullptr )
    {
      sub_42AF90(*pThis_1E58);
      sub_657740(v12, 228);
    }
    *pThis_1E58++ = nullptr;
  }
  pThis_1E68 = (void ***)(this + 7784);
  for ( k = 2; k != 0; --k )
  {
    v14 = *pThis_1E68;
    if ( *pThis_1E68 != nullptr )
    {
      sub_42AF90(*pThis_1E68);
      sub_657740(v14, 228);
    }
    *pThis_1E68++ = nullptr;
  }
  fld_1E74 = *(uint32_t *)(this + 7796);
  if ( fld_1E74 != 0 )
  {
    sub_42AF90(*(void ***)(this + 7796));
    sub_657740(fld_1E74, 228);
  }
  pThis_1E78 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7800);
  *(uint32_t *)(this + 7796) = 0;
  if ( pThis_1E78 != nullptr )
    (**pThis_1E78)(pThis_1E78, 1);
  pThis_1F20 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7968);
  *(uint32_t *)(this + 7800) = 0;
  if ( pThis_1F20 != nullptr )
    (**pThis_1F20)(pThis_1F20, 1);
  fld_1F24 = *(void ***)(this + 7972);
  *(uint32_t *)(this + 7968) = 0;
  if ( fld_1F24 != nullptr )
  {
    sub_42AF90(fld_1F24);
    sub_657740(fld_1F24, 228);
  }
  pThis_1F28 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7976);
  *(uint32_t *)(this + 7972) = 0;
  if ( pThis_1F28 != nullptr )
    (**pThis_1F28)(pThis_1F28, 1);
  pThis_1F2C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7980);
  *(uint32_t *)(this + 7976) = 0;
  if ( pThis_1F2C != nullptr )
    (**pThis_1F2C)(pThis_1F2C, 1);
  pThis_1F30 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7984);
  *(uint32_t *)(this + 7980) = 0;
  if ( pThis_1F30 != nullptr )
    (**pThis_1F30)(pThis_1F30, 1);
  pThis_1F40 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8000);
  *(uint32_t *)(this + 7984) = 0;
  if ( pThis_1F40 != nullptr )
    (**pThis_1F40)(pThis_1F40, 1);
  pThis_1F84 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8068);
  *(uint32_t *)(this + 8000) = 0;
  if ( pThis_1F84 != nullptr )
    (**pThis_1F84)(pThis_1F84, 1);
  *(uint32_t *)(this + 8068) = 0;
  pThis_1F90 = (void (/*thiscall*/ ****)(uint32_t, int))(this + 8080);
  for ( m = 2; m != 0; --m )
  {
    v26 = *(pThis_1F90 - 2);
    if ( v26 != nullptr )
      (**v26)(v26, 1);
    v27 = *pThis_1F90;
    v28 = *pThis_1F90 == nullptr;
    *(pThis_1F90 - 2) = nullptr;
    if ( !v28 )
      (**v27)(v27, 1);
    *pThis_1F90++ = nullptr;
  }
  pThis_1FEC = (void ***)(this + 8172);
  for ( n = 5; n != 0; --n )
  {
    v39 = 2;
    do
    {
      v30 = (int)*(pThis_1FEC - 10);
      if ( v30 != 0 )
      {
        sub_42AF90(*(pThis_1FEC - 10));
        sub_657740(v30, 228);
      }
      v31 = *pThis_1FEC;
      v28 = *pThis_1FEC == nullptr;
      *(pThis_1FEC - 10) = nullptr;
      if ( !v28 )
      {
        sub_42AF90(v31);
        sub_657740(v31, 228);
      }
      *pThis_1FEC++ = nullptr;
      result = v39 - 1;
      v39 = result;
    }
    while ( result != 0 );
  }
  fld_1D04 = *(uint32_t *)(this + 7428);
  if ( fld_1D04 != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1D04 + 4))(fld_1D04, 1);
  *(uint32_t *)(this + 7428) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x4B7430 sub_4B7430 —— 升级演出装配（LevelNormalizeLibra.ani + LevelNormalize.ptl；LEVELING_OFF/FLASH；PVP_KO）
// ------------------------------------------------------------
void /*usercall*/ sub_4B7430(int *pDwArg1@<ecx>, double fArg2@<st0>)
{
  int v3; // eax
  int v4; // ecx
  void (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int v6; // ebx
  uint32_t *v7; // edi
  int *v8; // ecx
  int v9; // eax
  int v10; // edx
  int v11; // edi
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  uint32_t *pMem; // eax
  int *v17; // eax
  int v18; // edx
  int pObj2; // ecx
  int pObj6; // ecx
  const char *v21; // eax
  int v22; // eax
  int v23; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // edx
  int *v27; // edi
  int v28; // ebx
  int v29; // eax
  int v30; // eax
  void *v31; // ecx
  int v32; // eax
  int pObj3; // ecx
  int v34; // edx
  int v35; // eax
  int *v36; // edi
  int v37; // ebx
  int v38; // eax
  int v39; // eax
  void *v40; // ecx
  void *Block2; // eax
  int v42; // edi
  int v43; // eax
  int v44; // ecx
  bool v45; // zf
  char v46; // al
  int v47; // edx
  int v48; // ecx
  int v49; // eax
  void *v50; // eax
  int v51; // edx
  void *v52; // eax
  int v53; // edi
  unsigned int v54; // eax
  int *v55; // ebx
  const char *v56; // eax
  int v57; // eax
  int *v58; // eax
  const char *v59; // eax
  int v60; // eax
  int v61; // ecx
  int v62; // eax
  int v63; // eax
  int v64; // edi
  int pObj7; // eax
  int v66; // ebx
  char v67; // al
  int *pDwArg12; // ecx
  int v69; // eax
  int v70; // edi
  int v71; // ecx
  int v72; // edi
  int v73; // eax
  int *v74; // edi
  int v75; // eax
  int pObj4; // edi
  bool v77; // bl
  int v78; // ebx
  int v79; // eax
  int v80; // eax
  int v81; // eax
  void *v82; // ecx
  int v83; // edi
  int v84; // edi
  int v85; // ebx
  int v86; // eax
  int v87; // eax
  int v88; // eax
  void *v89; // ecx
  int i; // edi
  unsigned int v91; // eax
  int v92; // edx
  int v93; // ebx
  int v94; // ebx
  int v95; // eax
  void **v96; // edi
  int v97; // eax
  int pObj5; // ecx
  int *v99; // eax
  int *v100; // eax
  int pObj; // ecx
  uint32_t *v102; // edi
  int j; // ebx
  int v104; // ebx
  int v105; // edx
  float fArg23; // [esp+10h] [ebp-1C8h]
  float fArg22; // [esp+10h] [ebp-1C8h]
  float v108; // [esp+14h] [ebp-1C4h]
  float v109; // [esp+14h] [ebp-1C4h]
  int v110; // [esp+1Ch] [ebp-1BCh]
  int v111; // [esp+20h] [ebp-1B8h]
  int v112; // [esp+20h] [ebp-1B8h]
  int *v113; // [esp+20h] [ebp-1B8h]
  int v114; // [esp+24h] [ebp-1B4h]
  char v115[4]; // [esp+30h] [ebp-1A8h] BYREF
  void *Block; // [esp+34h] [ebp-1A4h]
  int v117; // [esp+40h] [ebp-198h]
  char v118[4]; // [esp+44h] [ebp-194h] BYREF
  void *v119; // [esp+48h] [ebp-190h]
  int v120; // [esp+4Ch] [ebp-18Ch]
  int v121; // [esp+50h] [ebp-188h]
  void *pMem2; // [esp+54h] [ebp-184h] BYREF
  char v123[256]; // [esp+58h] [ebp-180h] BYREF
  char Buffer[112]; // [esp+158h] [ebp-80h] BYREF
  int dword_796E502; // [esp+1C8h] [ebp-10h]
  int v126; // [esp+1D4h] [ebp-4h]

  dword_796E502 = dword_796E50;
  sub_58FC30();  // 【IRDActiveObject__vmt14C】
  v3 = pDwArg1[2001];
  if ( v3 != 0 )
  {
    v4 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v4 == 4 || v4 == 6 )
    {
      if ( v3 == 1 )
      {
        v5 = (void (/*thiscall*/ ***)(uint32_t, int))pDwArg1[2000];
        if ( v5 != nullptr )
          (**v5)(v5, pDwArg1[2001]);
        v6 = 0;
        pDwArg1[2000] = 0;
        v126 = 0;
        if ( sub_42FCB0(228) != 0 )
          v6 = sub_431860((char)"Common/Etc/Animation/LevelNormalizeLibra.ani", 1);
        v7 = (uint32_t *)sub_44B6C0(284);
        pMem2 = v7;
        v126 = 1;
        if ( v7 != nullptr )
        {
          sub_44E0D0(v6, 1);
          *v7 = &CNRDPooledObject::`vftable';
          v8 = v7;
        }
        else
        {
          v8 = nullptr;
        }
        a1[1999] = (int)v8;
        v9 = *v8;
        v126 = -1;
        (*(void (/*thiscall*/ **)(int *))(v9 + 72))(v8);
        sub_45FE80(a1[29], (int)v7, 2, 0, a1[1999], (int)a1, 0);
        v10 = *a1;
        v11 = *(uint32_t *)a1[1999];
        v117 = a1[1999];
        v12 = (*(int (/*thiscall*/ **)(int *))(v10 + 192))(a1);
        v13 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);
        v14 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 124))(a1, v13 + v12);
        v15 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 120))(a1, v14);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 112))(v117, v15);
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)a1[1999] + 60))(a1[1999], a1);
        sub_4A06D0(2);
        v16 = operator new(0x12Cu);
        v122 = v16;
        v126 = 2;
        if ( v16 != nullptr )
          v17 = sub_428F30(v16, (int)"Common/Etc/Particle/LevelNormalize.ptl", (int)a1);
        else
          v17 = nullptr;
        a1[2000] = (int)v17;
        v18 = *v17;
        v126 = -1;
        (*(void (/*thiscall*/ **)(int *, int *))(v18 + 112))(v17, a1);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[2000] + 64))(a1[2000], 1);
        a1[2001] = 2;
      }
      else
      {
        v19 = a1[1999];
        if ( v19 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 200))(v19) != 0 )
        {
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[1999] + 200))(a1[1999]) + 148) == 4
            && a1[2001] == 2 )
          {
            a1[2001] = 3;
            sub_432EA0("LEVELING_OFF", -1, 0, 0);
          }
          else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[1999] + 200))(a1[1999]) + 148) == 20
                 && a1[2001] == 3 )
          {
            a1[2001] = 4;
            sub_432EA0("LEVELING_FLASH", -1, 0, 0);
          }
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[1999] + 200))(a1[1999]) + 170) != 0 )
          {
            v20 = a1[2000];
            if ( v20 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v20 + 12))(v20, 0);
              v111 = sub_4633B0(a1);
              v21 = (const char *)sub_422E70(850);
              sprintf(Buffer, v21, v111);
              sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);
              a1[2001] = 0;
            }
          }
        }
      }
    }
  }
  (*(void (/*thiscall*/ **)(int *))(*a1 + 1308))(a1);
  if ( *((uint8_t *)a1 + 7764) != 0 && *(uint8_t *)(a1[1942] + 170) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 1232))(a1, 0);
  if ( *((uint8_t *)a1 + 7780) != 0 && *(uint8_t *)(a1[1946] + 170) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*a1 + 1240))(a1, 0, 0);
  if ( *((uint8_t *)a1 + 7792) != 0 )
  {
    v22 = a1[1949];
    if ( *(uint32_t *)(v22 + 212) != 0 )
      v23 = sub_4910A0();
    else
      v23 = *(uint32_t *)(v22 + 32);
    v24 = 0;
    if ( v23 >= 540 )
    {
      v34 = *a1;
      if ( v23 >= 1080 )
      {
        (*(void (/*stdcall*/ **)(uint32_t))(v34 + 1248))(0);
      }
      else
      {
        v122 = (void *)((*(int (/*fastcall*/ **)(int *))(v34 + 192))(a1) + 30);
        v109 = (float)(int)v122;
        v117 = (*(int (/*thiscall*/ **)(int *))(*a1 + 192))(a1) + 100;
        a2 = (double)v117;
        v107 = a2;
        sub_4049F0(v107, v109, v23 - 540, 540, 0);
        v24 = (uint64_t)a2;
      }
    }
    else
    {
      v25 = (*(int (/*thiscall*/ **)(int *))(*a1 + 192))(a1);
      v26 = *a1;
      v117 = v25 + 100;
      v108 = (float)(v25 + 100);
      v122 = (void *)((*(int (/*thiscall*/ **)(int *))(v26 + 192))(a1) + 30);
      a2 = (double)(int)v122;
      v106 = a2;
      sub_4049F0(v106, v108, v23, 540, 1);
      v27 = (int *)a1[1950];
      v28 = *v27;
      v117 = (uint64_t)a2;
      v29 = (*(int (/*fastcall*/ **)(int *, uint32_t, int))(*a1 + 124))(a1, (uint64_t)a2 >> 32, v117);
      v30 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 120))(a1, v29 - 1);
      (*(void (/*thiscall*/ **)(int *, int))(v28 + 40))(v27, v30);
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1[1950] + 92))(a1[1950], v115);
      v31 = (void *)a1[29];
      v126 = 3;
      sub_4600B0(v31, 2, 0, (int)v115);
      v126 = -1;
      if ( Block != nullptr )
        j__free(Block);
      v24 = v117;
    }
    v32 = a1[1951];
    if ( v32 != 0 )
      *(uint32_t *)(v32 + 12) = -v24;
  }
  v33 = a1[1898];
  if ( v33 != 0 && a1[29] != 0 )
  {
    if ( *((uint8_t *)a1 + 7608) != 0 && (a1[1639] != 0 || *((uint8_t *)a1 + 6752) == 0) )
    {
      *((uint8_t *)a1 + 7609) = 0;
    }
    else
    {
      if ( *((uint8_t *)a1 + 7609) == 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v33 + 12))(v33, 0);
      if ( (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1) != 0 )
        v35 = a1[1899] + (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1);
      else
        v35 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1) - a1[1899];
      v36 = (int *)a1[1898];
      v37 = *v36;
      v117 = v35;
      v38 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);
      v39 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 124))(a1, a1[1901] + v38);
      (*(void (/*thiscall*/ **)(int *, int, int))(v37 + 40))(v36, v117, a1[1900] + v39);
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1[1898] + 92))(a1[1898], v115);
      v40 = (void *)a1[29];
      v126 = 4;
      sub_4600B0(v40, 2, 0, (int)v115);
      v41 = Block;
      v45 = Block == nullptr;
      *((uint8_t *)a1 + 7609) = 1;
      v126 = -1;
      if ( !v45 )
        j__free(v41);
    }
  }
  v42 = (*(int (/*thiscall*/ **)(int *))(*a1 + 184))(a1);
  v43 = (*(int (/*thiscall*/ **)(int *))(*a1 + 188))(a1);
  switch ( a1[1639] )
  {
    case 0:
      if ( v42 != 4 && v42 != (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1) )
        (*(void (/*thiscall*/ **)(int *, int))(*a1 + 144))(a1, v42);
      if ( *((uint8_t *)a1 + 6752) == 0 || a1[1803] == 0 || a1[50] != 0 )
        goto LABEL_152;
      v44 = *(uint32_t *)(dword_8F7A24 + 12);
      if ( v44 == 4 )
      {
        v45 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 36) == 0;
      }
      else
      {
        if ( v44 == 6 )
        {
          v46 = sub_42B530(*(uint32_t *)(dword_8F7A24 + 40));
          goto LABEL_72;
        }
        v45 = *(uint8_t *)(a1[29] + 152) == 0;
      }
      v46 = v45;
LABEL_72:
      v47 = a1[30];
      if ( v46 != 0 )
      {
        if ( v47 != a1[1540] )
          goto LABEL_152;
        v48 = a1[1803];
      }
      else
      {
        if ( v47 != a1[1803] )
          goto LABEL_152;
        v48 = a1[1540];
      }
      (*(void (/*thiscall*/ **)(int *, int))(*a1 + 196))(a1, v48);
      sub_4926A0(a1[30]);
      goto LABEL_152;
    case 5:
      if ( sub_699000((int)(a1 + 1640)) < 1000 && ((sub_699000((int)(a1 + 1640)) / 0xC8u) & 1) != 0 )  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*a1 + 252))(a1, 3, 0);
      else
        (*(void (/*thiscall*/ **)(int *, int, int))(*a1 + 252))(a1, 3, -1);
      if ( sub_699000((int)(a1 + 1640)) >= 1000 && *((uint8_t *)a1 + 7960) == 0 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int *))(*a1 + 1224))(a1);
        *((uint8_t *)a1 + 7960) = 1;
        v49 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v49 == 4 || v49 == 6 )
        {
          v50 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);
          v51 = *a1;
          v122 = v50;
          v52 = (void *)(*(int (/*thiscall*/ **)(int *))(v51 + 376))(a1);
          v53 = v52 != v122 ? -13441486 : -13487386;
          v54 = a1[2012];
          if ( a1[2002] == 273 )
          {
            if ( v54 < 0x10 )
              v55 = a1 + 2007;
            else
              v55 = (int *)a1[2007];
            v112 = sub_4633B0(a1);
            v56 = (const char *)sub_422E70(851);
            sprintf(v123, v56, v55, v112);
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v123, v53, 0, -1);
            if ( a1[2003] == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 48))(dword_8F7C04)
              && a1[2004] == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04) )
            {
              v57 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
              sub_496010((int)dword_99FD58, v57, 7, 1);
            }
          }
          else
          {
            if ( v54 < 0x10 )
              v58 = a1 + 2007;
            else
              v58 = (int *)a1[2007];
            v113 = v58;
            v110 = sub_4633B0(a1);
            v59 = (const char *)sub_422E70(852);
            sprintf(v123, v59, v110, v113);
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v123, v53, 0, -1);
          }
          sub_432EA0("PVP_KO", -1, 0, 0);
        }
      }
      goto LABEL_152;
    case 10:
      v60 = a1[1952];
      if ( v60 == 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0
          && a1[1955] != -1
          && sub_699000((int)(a1 + 1640)) >= a1[1955] )  // 【clock_now(clk)】
        {
          v119 = nullptr;
          v120 = 0;
          v121 = 0;
          v126 = 5;
          v122 = (void *)1;
          sub_431230(&v122);
          (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 10, v118, 0, 0);
LABEL_103:
          v126 = -1;
          sub_5E5260(v118);
          goto LABEL_152;
        }
        goto LABEL_152;
      }
      if ( v60 != 1 )
        goto LABEL_152;
      if ( *((uint8_t *)a1 + 7840) != 0 )
        goto LABEL_126;
      v61 = a1[30];
      if ( v61 == 0 )
        goto LABEL_126;
      v62 = a1[1953];
      if ( v62 != 2 && (v62 != 1 || *(uint32_t *)(v61 + 148) < a1[1963]) )
        goto LABEL_126;
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0 )
      {
        v63 = sub_484E80(a1[1954]);
        v64 = v63;
        if ( v63 == -1
          || (v65 = sub_44A980(v63),
              (v66 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v65 + 44))(v65)) <= (unsigned int)sub_484790(dword_8F852C)) )
        {
          v68 = a1;
        }
        else
        {
          v67 = sub_486B40(v64, a1[1971]);
          v68 = a1;
          if ( v67 != 0 )
          {
            (*(void (/*thiscall*/ **)(int *))(*a1 + 1276))(a1);
            goto LABEL_117;
          }
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 560))(v68, 0, 0, 0, 0);
      }
LABEL_117:
      v69 = sub_4CE8A0(a1[1954]);
      v70 = v69;
      if ( v69 != 0 && (unsigned int)sub_41C5A0(v69 + 136) > 1 )
      {
        v71 = *(uint32_t *)(v70 + 140) + 4;
        v72 = *a1;
        v73 = sub_41ACF0(v71);
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v72 + 212))(a1, v73, -1, 0, 0);
      }
      if ( (uint8_t)sub_423340(a1 + 1964, szPassword) != 0 )
      {
        if ( (unsigned int)a1[1970] < 0x10 )
          v74 = a1 + 1965;
        else
          v74 = (int *)a1[1965];
        (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t))(*a1 + 212))(a1, v74, -1, 0, 0);
      }
      *((uint8_t *)a1 + 7840) = 1;
LABEL_126:
      v75 = a1[1953];
      if ( v75 == 2 || v75 == 1 )
      {
        if ( *((uint8_t *)a1 + 7840) != 0 && a1[1956] != -1 && sub_699000((int)(a1 + 1640)) >= a1[1956] )  // 【clock_now(clk)】
          goto LABEL_151;
      }
      else if ( a1[1956] != -1 && sub_699000((int)(a1 + 1640)) >= a1[1956] )  // 【clock_now(clk)】
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1) <= 0 )
          goto LABEL_151;
        v119 = nullptr;
        v120 = 0;
        v121 = 0;
        v126 = 6;
        v122 = (void *)1;
        sub_431230(&v122);
        v122 = nullptr;
        sub_431230(&v122);
        v122 = nullptr;
        sub_431230(&v122);
        (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 6, v118, 0, 0);
        goto LABEL_103;
      }
LABEL_152:
      if ( (int *)dword_8F7C04 == a1 )
      {
        if ( a1[1639] == 8 && (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 )
        {
          byte_9A0358 = 0;
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 1328))(a1, 0);
          byte_9A0384 = 0;
        }
        if ( (int *)dword_8F7C04 == a1 && a1[50] != 2 )
        {
          (*(void (/*thiscall*/ **)(int *))(*a1 + 1324))(a1);
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 852))(a1) != 0 )
          {
            for ( i = 0; i < 9; ++i )
            {
              if ( (uint8_t)sub_4BF450(i, 1) != 0 )
                break;
            }
            if ( i != 9 )
              (*(void (/*thiscall*/ **)(int *))(*a1 + 860))(a1);
          }
          switch ( a1[1639] )
          {
            case 0:
              if ( ((uint8_t)sub_4BFBC0(&unk_9A0388, 1) != 0 || (uint8_t)sub_4BFBC0(&unk_9A03B4, 1) != 0)
                && a1[1812] != 0 )
              {
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 11, 0, 0, 0);
              }
              else
              {
                if ( (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 )
                {
                  v119 = nullptr;
                  v120 = 0;
                  v121 = 0;
                  v126 = 9;
                  v122 = nullptr;
                  sub_431230(&v122);
                  v122 = nullptr;
                  sub_431230(&v122);
                  v122 = nullptr;
                  sub_431230(&v122);
                  (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 6, v118, 0, 0);
                  goto LABEL_171;
                }
                if ( (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 && a1[50] == 0 )
                {
                  if ( a1[1972] == 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )
                  {
                    v119 = nullptr;
                    v120 = 0;
                    v121 = 0;
                    v126 = 10;
                    v122 = nullptr;
                    sub_431230(&v122);
                    (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 8, v118, 0, 0);
                    goto LABEL_171;
                  }
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 13, 0, 0, 0);
                }
              }
              break;
            case 6:
              if ( a1[1723] == 1 && (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 && a1[1724] < a1[1725] )
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 7, 0, 0, 0);
              break;
            case 8:
              v91 = sub_41A5E0(a1 + 1757);
              v92 = a1[1974];
              if ( v92 != 0 && v91 < (a1[1975] - v92) >> 2 )
              {
                v93 = *(uint32_t *)(a1[30] + 148);
                if ( v93 >= *(uint32_t *)(a1[1974] + 4 * sub_41A5E0(a1 + 1757))
                  && (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0
                  && a1[50] == 0 )
                {
                  v94 = sub_41A5E0(a1 + 1757);
                  if ( v94 + 1 < (unsigned int)sub_41C5A0(a1 + 1549) )
                  {
                    v119 = nullptr;
                    v120 = 0;
                    v121 = 0;
                    v126 = 11;
                    v122 = (void *)(sub_41A5E0(a1 + 1757) + 1);
                    sub_431230(&v122);
                    (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 8, v118, 0, 0);
                    goto LABEL_171;
                  }
                }
              }
              break;
            case 11:
              if ( (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 )
              {
                v119 = nullptr;
                v120 = 0;
                v121 = 0;
                v126 = 12;
                v122 = nullptr;
                sub_431230(&v122);
                v122 = nullptr;
                sub_431230(&v122);
                v122 = nullptr;
                sub_431230(&v122);
                (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 6, v118, 0, 0);
LABEL_171:
                v126 = -1;
                sub_5E5260(v118);
              }
              else if ( (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 )
              {
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 12, 0, 0, 0);
              }
              break;
            default:
              break;
          }
          v95 = a1[1639];
          if ( (v95 == 0 || v95 == 11 || v95 == 8)
            && sub_4842B0(169, nullptr) != -1
            && (*(uint8_t (/*thiscall*/ **)(int *, int))(*a1 + 1312))(a1, 169) != 0 )
          {
            v119 = nullptr;
            v120 = 0;
            v121 = 0;
            v126 = 13;
            v122 = (void *)1;
            sub_431230(&v122);
            v122 = (void *)1;
            sub_431230(&v122);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*a1 + 1160))(a1, 169, 0);
            v122 = (void *)sub_47E9D0(v114);
            sub_431230(&v122);
            v114 = 0;
            (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t))(*a1 + 560))(a1, 6, v118, 0);
            v126 = -1;
            if ( v119 != nullptr )
              j__free(v119);
          }
          v96 = (void **)&unk_791BE0;
          do
          {
            v97 = a1[1639];
            if ( (v97 == 0 || v97 == 11)
              && sub_4842B0((int)*v96, nullptr) != -1
              && (*(uint8_t (/*thiscall*/ **)(int *, void *))(*a1 + 1312))(a1, *v96) != 0 )
            {
              v119 = nullptr;
              v120 = 0;
              v121 = 0;
              v122 = *v96;
              v126 = 14;
              sub_430C80(nullptr, 1, (int)&v122);
              (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 14, v118, 0, 0);
              v126 = -1;
              if ( v119 != nullptr )
                j__free(v119);
              v119 = nullptr;
              v120 = 0;
              v121 = 0;
            }
            ++v96;
          }
          while ( (int)v96 < (int)&CNImageLoader `RTTI Type Descriptor' );
          if ( pDwArg1[1639] != 5 )
          {
            pObj5 = pDwArg1[1924];
            if ( pObj5 != 0
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 688))(pObj5) != 3
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 688))(pDwArg1[1924]) != 4 )
            {
              if ( (uint8_t)sub_4BFBC0(&unk_9A0438, 0) != 0
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 700))(pDwArg1[1924]) == 0
                || (uint8_t)sub_4BFBC0(&unk_9A040C, 0) != 0
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 700))(pDwArg1[1924]) == 0 )
              {
                if ( (unsigned int)pDwArg1[1931] < 0x10 )
                  v99 = pDwArg1 + 1926;
                else
                  v99 = (int *)pDwArg1[1926];
                (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, v99, -1, 0, 0, v114);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[1924] + 712))(pDwArg1[1924], 1);
              }
              else if ( (uint8_t)sub_4BFBC0(&byte_9A03E0, 0) != 0
                     && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 700))(pDwArg1[1924]) == 1
                      || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 700))(pDwArg1[1924]) == 0) )
              {
                if ( (unsigned int)pDwArg1[1931] < 0x10 )
                  v100 = pDwArg1 + 1926;
                else
                  v100 = (int *)pDwArg1[1926];
                (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, v100, -1, 0, 0, v114);
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[1924] + 712))(pDwArg1[1924], 0);
              }
            }
          }
        }
      }
      pObj = pDwArg1[2000];
      if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 68))(pObj) == 0 )
        sub_4B2780(pDwArg1);
      v102 = pDwArg1 + 1617;
      for ( j = 18; j != 0; --j )
      {
        if ( *v102 != 0 )
          sub_4EAD30();
        ++v102;
      }
      if ( *((uint8_t *)pDwArg1 + 8100) == 1 )
      {
        v104 = pDwArg1[2028];
        if ( sub_699000((int)(pDwArg1 + 2022)) < v104 )  // 【clock_now(clk)】
        {
          v105 = sub_699000((int)(pDwArg1 + 2022)) % 74;  // 【clock_now(clk)】
          if ( v105 >= 37 )
            sub_4049C0(2.0, 0.0, v105 - 37, 37);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          else
            sub_4049C0(0.0, 2.0, v105, 37);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          if ( (unsigned int)(uint64_t)fArg2 != 0 )
          {
            if ( (unsigned int)(uint64_t)fArg2 == 1 )
              sub_499770(2, 0);
          }
          else
          {
            sub_499770(-2, 0);
          }
        }
        else
        {
          sub_499770(0, 0);
          *((uint8_t *)pDwArg1 + 8100) = 0;
        }
      }
      return;
    case 11:
      if ( v42 == 4 )
      {
        if ( v43 != 4 )
          goto LABEL_142;
      }
      else if ( v42 == (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) )
      {
        goto LABEL_142;
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);
LABEL_142:
      if ( pDwArg1[1772] == 7 && pDwArg1[29] != 0 && (uint8_t)sub_41C6E0(pDwArg1 + 1779) != 0 )
      {
        pObj4 = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 924))(pDwArg1, 2)];
        v77 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) == 0;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 28))(pObj4) + 84) = v77;
        v78 = *(uint32_t *)pObj4;
        v79 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
        v80 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v79);
        v81 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v80);
        (*(void (/*thiscall*/ **)(int, int))(v78 + 40))(pObj4, v81);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj4 + 12))(pObj4, 0);
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj4 + 92))(pObj4, v115);
        v82 = (void *)pDwArg1[29];
        v126 = 7;
        sub_4600B0(v82, 2, 0, (int)v115);
        *((uint8_t *)pDwArg1 + 7129) = 0;
        *((uint8_t *)pDwArg1 + 7130) = 0;
        sub_698F90((int)(pDwArg1 + 1779), 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        v126 = -1;
        sub_5E5260(v115);
      }
      goto LABEL_152;
    case 12:
      goto LABEL_150;
    case 13:
      if ( *(uint8_t *)(pDwArg1[30] + 170) != 0 )
        goto LABEL_151;
      goto LABEL_152;
    case 14:
      v83 = sub_699000((int)(pDwArg1 + 1640));  // 【clock_now(clk)】
      if ( v83 < sub_491C10(pDwArg1[30]) - 300 )
      {
        v84 = *(uint32_t *)pDwArg1[1992];
        pMem2 = (void *)pDwArg1[1992];
        v85 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 192))(pDwArg1);
        v86 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
        v87 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v85 + v86 + 30);
        v88 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v87);
        (*(void (/*thiscall*/ **)(void *, int))(v84 + 40))(pMem2, v88);
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pDwArg1[1992] + 92))(pDwArg1[1992], v115);
        v89 = (void *)pDwArg1[29];
        v126 = 8;
        sub_4600B0(v89, 2, 0, (int)v115);
        v126 = -1;
        sub_5E5260(v115);
      }
LABEL_150:
      if ( *(uint8_t *)(pDwArg1[30] + 170) != 0 )
LABEL_151:
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);
      goto LABEL_152;
    default:
      goto LABEL_152;
  }
}


// ============================================================
// §L 0x4B89D0-0x4B9280  跑步地面循环 + 蓄气/霸体特效
// ============================================================
// ------------------------------------------------------------
// 0x4B89D0 sub_4B89D0 —— 跑步地面循环 + 蓄气/霸体特效
//   G_RUN_FLOOR_LOOP/RUN_GRASS/SOIL/STONE_LOOP 按 +212 地形选播（sub_491C70 时刻换算）；
//   BuffChargeGlow.ani+BuffChargeParticle.ptl 挂子链 +204；MOON_CURTAIN_LIGHT。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B89D0(int *this, int nArg2, int pArg3, float fArg4, float fArg5)
{
  int fld_e1991; // edi
  int v7; // ebx
  int fld_e19912; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // edx
  int fld_e1955; // eax
  void *fld_e30; // ebx
  int v16; // eax
  int fld_e1953; // eax
  int fld_e1954; // eax
  int pObj; // eax
  int v20; // edx
  int v21; // eax
  int v22; // eax
  int *pThis_7C0; // eax
  uint64_t fld_e28; // rax
  int v25; // ebx
  int v26; // eax
  int fld_e1815; // eax
  int v28; // edx
  int fld_e19913; // eax
  int v30; // eax
  int v31; // ebx
  int v32; // eax
  uint64_t v33; // rax
  uint32_t *pMem; // eax
  uint32_t *v35; // eax
  int v36; // eax
  int v37; // ebx
  int v38; // eax
  int fld_e1977; // edi
  int fld_e1978; // ebx
  int v41; // edi
  int v42; // eax
  int fld_e29; // eax
  int v45; // [esp+0h] [ebp-24h]
  int v46; // [esp+4h] [ebp-20h]
  int v47; // [esp+8h] [ebp-1Ch]
  float Block; // [esp+Ch] [ebp-18h]
  int fld_e1639; // [esp+14h] [ebp-10h]
  int v50; // [esp+2Ch] [ebp+8h]
  int v51; // [esp+30h] [ebp+Ch]
  int fld_e302; // [esp+30h] [ebp+Ch]
  int fld_e303; // [esp+30h] [ebp+Ch]

  fld_e1639 = *(this + 1639);
  switch ( fld_e1639 )
  {
    case 10:
      if ( *(this + 1952) != 0 )
        goto LABEL_12;
      break;
    case 11:
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);
      goto LABEL_12;
    case 14:
      if ( nArg2 == 0 && *(this + 1991) != -1 )
      {
        fld_e1991 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *(this + 1991));
        if ( fld_e1991 != 0 )
        {
          v7 = *this;
          fld_e19912 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 1991));
          (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 1300))(this, fld_e1991, fld_e19912);
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 1993));
      break;
    default:
      goto LABEL_12;
  }
  (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);
LABEL_12:
  switch ( nArg2 )
  {
    case 5:
      *((uint8_t *)this + 7960) = 0;
      break;
    case 10:
      v10 = **(uint32_t **)(pArg3 + 4);
      *(this + 1952) = v10;
      if ( v10 != 0 )
      {
        v20 = *this;
        if ( *(this + 1953) == 2 )
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v20 + 196))(this, *(this + 1542));
        else
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v20 + 196))(this, *(this + *(this + 1957) + 1808));
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(
          this,
          *(this + 1958),
          *(this + 1958),
          *(this + 1959),
          *(this + 1959));
        *(this + 1956) = 1000 * *(this + 1956) / *(this + 1664);
      }
      else
      {
        *(this + 1953) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);
        *(this + 1954) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);
        *(this + 1955) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12);
        *(this + 1956) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 16);
        *(this + 1957) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 20);
        v11 = *(uint32_t *)(pArg3 + 4);
        v12 = *(uint32_t *)(v11 + 24);
        *(this + 1958) = *(uint32_t *)(v11 + 28);
        v51 = 1000;
        *(this + 1959) = 1000;
        if ( (unsigned int)sub_41C5A0(pArg3) > 8 )
          v51 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 32);
        if ( (unsigned int)sub_41C5A0(pArg3) > 9 )
          *(this + 1959) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 36);
        v13 = *this;
        if ( *(this + 1953) == 2 )
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 196))(this, *(this + 1542));
        else
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 196))(this, *(this + *(this + 1957) + 1804));
        (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, v12, v12, v51, v51);
        fld_e1955 = 1000 * *(this + 1955) / *(this + 1664);
        *(this + 1955) = fld_e1955;
        if ( v12 == 4 )
          (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*this + 992))(this, fld_e1955, 0);
        if ( *(this + 1955) == 0 )
        {
          fld_e30 = (void *)*(this + 30);
          v16 = sub_42FC90(fld_e30);
          sub_4AECE0(fld_e30, v16 - 1);
          *(this + 1955) = 70;
        }
        fld_e1953 = *(this + 1953);
        if ( fld_e1953 == 1 || fld_e1953 == 2 )
        {
          if ( (int *)dword_8F7C04 == this )
          {
            fld_e1954 = sub_484E80(*(this + 1954));
            if ( fld_e1954 != -1 )
            {
              pObj = sub_44A980(fld_e1954);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 100))(pObj);
            }
          }
          *(this + 1971) = (fld_e1639 == 10) + 1;
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      sub_495890(2, 0);
      *((uint8_t *)this + 7840) = 0;
      break;
    case 11:
      if ( *((uint8_t *)this + 7924) != 0 )
      {
        v21 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
        v22 = sub_4B0D20(v21);
        v47 = 0;
        v46 = 0;
        v45 = 9;
        if ( dword_9A012C != 0 )
        {
          (*(void (/*thiscall*/ **)(int *, const char *))(*this + 212))(this, "G_RUN_FLOOR_LOOP");
        }
        else if ( v22 >= 60000 )
        {
          if ( v22 >= 100000 )
            (*(void (/*thiscall*/ **)(int *, const char *))(*this + 212))(this, "RUN_GRASS_LOOP");
          else
            (*(void (/*thiscall*/ **)(int *, const char *))(*this + 212))(this, "RUN_SOIL_LOOP");
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, const char *))(*this + 212))(this, "RUN_STONE_LOOP");
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1812));
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 0, 286, 238, 1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 1, 136, 114, 1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 1, 1, 1000, 1000);
      sub_495890(2, 0);
      break;
    case 12:
      if ( (unsigned int)*(this + 1989) < 0x10 )
        pThis_7C0 = this + 1984;
      else
        pThis_7C0 = (int *)*(this + 1984);
      (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_7C0, -1, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 1816);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1813));
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 1, 2, 1000, 1000);
      fld_e302 = sub_491C70(*(this + 30), *(this + 1982));
      fld_e28 = (uint64_t)fabs(*(float *)(*(this + 28) + 16));
      (*(void (/*fastcall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*this + 876))(
        this,
        -1000 * (int)fld_e28 % fld_e302,
        0,
        fld_e28,
        fld_e28,
        0,
        -1000 * (int)fld_e28 / fld_e302,
        1);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      v25 = *this;
      v26 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int *, int))(v25 + 896))(this, v26);
      break;
    case 13:
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1814));
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      sub_495890(2, 0);
      if ( (int *)dword_8F7C04 == this && *(this + 1972) != 0 )
        sub_486470(*(this + 1972));
      break;
    case 14:
      fld_e1815 = *(this + 1815);
      v28 = *this;
      *(this + 1991) = **(uint32_t **)(pArg3 + 4);
      (*(void (/*thiscall*/ **)(int *, int))(v28 + 196))(this, fld_e1815);
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
      sub_495890(2, 0);
      fld_e19913 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 1991));
      (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*this + 1160))(this, *(this + 1991), fld_e19913);
      v30 = sub_4B1C40(v45);
      fld_e303 = *(uint32_t *)(*(this + 30) + 36);
      v31 = *this;
      Block = (double)fld_e303 / (double)v30;
      v32 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
      v33 = (uint64_t)((double)sub_495540(v32) * Block);
      (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, int, uint32_t))(v31 + 888))(
        this,
        HIDWORD(v33),
        0,
        0,
        1000,
        v33);
      if ( *(this + 1992) == 0 )
      {
        pMem = operator new(0x12Cu);
        if ( pMem != nullptr )
          v35 = sub_428F30(pMem, (int)"Common/CommonEffect/Particle/BuffChargeParticle.ptl", (int)this);
        else
          v35 = nullptr;
        *(this + 1992) = (int)v35;
        (*(void (/*thiscall*/ **)(uint32_t *, int *))(*v35 + 112))(v35, this);
      }
      if ( *(this + 1993) == 0 )
      {
        if ( sub_42FCB0(228) != 0 )
          v36 = sub_431860((char)"Common/CommonEffect/Animation/BuffChargeGlow.ani", 1);
        else
          v36 = 0;
        *(this + 1993) = v36;
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1992) + 12))(*(this + 1992), 0);
      v37 = *this;
      v38 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 192))(this, 1, 0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int))(v37 + 204))(this, 1, *(this + 1993), 0, -30 - v38);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "MOON_CURTAIN_LIGHT",
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 992))(this, fld_e303, 1);
      break;
    default:
      break;
  }
  sub_58E920(this, nArg2, pArg3, fArg4, fArg5);  // 【IRDActiveObject__vmt1D8】
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 6 )
    {
      if ( *(this + 1723) == 0 && fld_e1639 == 11 )
      {
        *(this + 1719) = 286;
        *(this + 1720) = 238;
        *(this + 1721) = 136;
        *(this + 1722) = 114;
      }
    }
    else if ( nArg2 == 8 && sub_41A5E0((unsigned int)(this + 1757)) > 0 )
    {
      fld_e1977 = 0;
      fld_e1978 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, int))(*this + 308))(this, v45, v46, v47) != 0 )
      {
        v50 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1132))(this, 0);
        if ( v50 == 4 )
        {
          fld_e1977 = *(this + 1977);
          fld_e1978 = *(this + 1978);
        }
        else if ( v50 == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) )
        {
          fld_e1977 = *(this + 1979);
          fld_e1978 = *(this + 1980);
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(this, 0, fld_e1977, fld_e1977, 0, fld_e1978, 1);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);
      v41 = *this;
      v42 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);
      (*(void (/*thiscall*/ **)(int *, int))(v41 + 896))(this, v42);
    }
  }
  else
  {
    fld_e29 = *(this + 29);
    if ( fld_e29 != 0 && *(uint8_t *)(fld_e29 + 152) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1803));
      sub_4926A0(*(this + 30));
    }
  }
  return (*(int (/*thiscall*/ **)(int *))(*this + 1316))(this);
}


// ============================================================
// §M 0x4B9280-0x4BA8A0  奖励演出族（SpUp/Dice/金币/道具/FP_UP/ENERGY_CHARGE）
// ============================================================
// ------------------------------------------------------------
// 0x4B9280 sub_4B9280 —— SP 增加演出（SpUp1/2/3.ani 按档位，挂子链 +204/+208）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B9280(char *this, char pszArg2)
{
  uint32_t *pThis_1E58; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int pThis_C0; // eax
  int result; // eax
  uint32_t *pThis_1E582; // edi
  int j; // ebx
  int i; // [esp+20h] [ebp+8h]

  if ( pszArg2 != 0 && *(this + 7764) != 0 )
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1232))(this, 0);
  *(this + 7764) = pszArg2;
  if ( pszArg2 != 0 )
  {
    pThis_1E58 = this + 7768;
    if ( *((uint32_t *)this + 1942) == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v4 = sub_431860((char)"Common/Etc/Animation/SpUp1.ani", 1);
      else
        v4 = 0;
      *pThis_1E58 = v4;
      if ( sub_42FCB0(228) != 0 )
        v5 = sub_431860((char)"Common/Etc/Animation/SpUp2.ani", 1);
      else
        v5 = 0;
      *((uint32_t *)this + 1943) = v5;
      if ( sub_42FCB0(228) != 0 )
        v6 = sub_431860((char)"Common/Etc/Animation/SpUp3.ani", 1);
      else
        v6 = 0;
      *((uint32_t *)this + 1944) = v6;
    }
    for ( i = 3; i != 0; --i )
    {
      v7 = *(uint32_t *)this;
      pThis_C0 = (*(int (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 192))(this, 1, 0);
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int))(v7 + 204))(this, 100, *pThis_1E58++, 0, -62 - pThis_C0);
      result = i - 1;
    }
  }
  else
  {
    pThis_1E582 = this + 7768;
    for ( j = 3; j != 0; --j )
      result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_1E582++);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B9400 sub_4B9400 —— BonusSpUp 图标/文字演出（BonusSpUpIcon.ani/BonusSpUpText.ani → sub_4924C0 +44）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B9400(int **this, char pszArg2, int nArg3)
{
  int *v4; // eax
  int *v5; // eax
  int v6; // ecx
  int fld_e1946; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edi
  unsigned int v11; // edx
  int i; // ebx
  uint32_t *fld_e19462; // eax
  uint32_t *pThis_79A; // ebx
  int *v15; // edi
  int v16; // eax
  int result; // eax
  uint32_t *pThis_79A2; // edi
  int k; // ebx
  int v20; // [esp+20h] [ebp+8h]
  int j; // [esp+20h] [ebp+8h]

  if ( pszArg2 != 0 && *((uint8_t *)this + 7780) != 0 )
    ((void (/*thiscall*/ *)(int **, uint32_t, uint32_t))(*this)[310])(this, 0, 0);
  *((uint8_t *)this + 7780) = pszArg2;
  if ( pszArg2 != 0 )
  {
    if ( *(this + 1946) == nullptr )
    {
      if ( sub_42FCB0(228) != 0 )
        v4 = (int *)sub_431860((char)"Common/Etc/Animation/BonusSpUpIcon.ani", 1);
      else
        v4 = nullptr;
      *(this + 1946) = v4;
      if ( sub_42FCB0(228) != 0 )
        v5 = (int *)sub_431860((char)"Common/Etc/Animation/BonusSpUpText.ani", 1);
      else
        v5 = nullptr;
      *(this + 1947) = v5;
    }
    v6 = *(uint32_t *)(((int (/*thiscall*/ *)(int **, int))(*this)[290])(this, nArg3) + 380);
    fld_e1946 = (int)*(this + 1946);
    v8 = *(uint32_t *)(fld_e1946 + 44);
    v9 = fld_e1946 + 40;
    v20 = v6;
    if ( v8 != 0 )
    {
      v11 = (int)((uint64_t)(780903145LL * (*(uint32_t *)(v9 + 8) - v8)) >> 32) >> 4;
      v10 = v11 + (v11 >> 31);
    }
    else
    {
      v10 = 0;
    }
    for ( i = 0; i < v10; *fld_e19462 = v20 )
      fld_e19462 = (uint32_t *)sub_4924C0(*(this + 1946), i++);
    pThis_79A = this + 1946;
    for ( j = 2; j != 0; --j )
    {
      v15 = *this;
      v16 = ((int (/*thiscall*/ *)(int **, int, uint32_t))(*this)[48])(this, 1, 0);
      ((void (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, int))v15[51])(this, 100, *pThis_79A++, 0, -25 - v16);
      result = j - 1;
    }
  }
  else
  {
    pThis_79A2 = this + 1946;
    for ( k = 2; k != 0; --k )
      result = ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[52])(this, *pThis_79A2++);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B95B0 sub_4B95B0 —— 金币演出（UseCoin.ani + UseCoinParticle.ptl）
// ------------------------------------------------------------
int */*thiscall*/ sub_4B95B0(int *this, void *Block)
{
  int v3; // eax
  uint32_t *pMem; // eax
  uint32_t *v5; // eax
  int v6; // edi
  int v7; // eax
  int *fld_e32; // ecx
  int *result; // eax
  int fld_e1949; // ecx
  int v11; // eax
  int fld_e19492; // [esp-4h] [ebp-1Ch]

  if ( (uint8_t)Block != 0 && *((uint8_t *)this + 7792) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1248))(this, 0);
  *((uint8_t *)this + 7792) = (uint8_t)Block;
  if ( (uint8_t)Block != 0 )
  {
    if ( *(this + 1949) == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v3 = sub_431860((char)"Common/Etc/Animation/UseCoin.ani", 1);
      else
        v3 = 0;
      *(this + 1949) = v3;
      pMem = operator new(0x12Cu);
      if ( pMem != nullptr )
        v5 = sub_428F30(pMem, (int)"Common/Etc/Particle/UseCoinParticle.ptl", (int)this);
      else
        v5 = nullptr;
      *(this + 1950) = (int)v5;
      (*(void (/*thiscall*/ **)(uint32_t *, int *))(*v5 + 112))(v5, this);
    }
    v6 = *this;
    v7 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 192))(this, 1, 0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int))(v6 + 204))(this, 102, *(this + 1949), 0, -30 - v7);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1950) + 12))(*(this + 1950), 0);
    fld_e32 = (int *)*(this + 32);
    result = (int *)*fld_e32;
    if ( (int *)*fld_e32 != fld_e32 )
    {
      fld_e1949 = *(this + 1949);
      do
      {
        if ( result[3] == fld_e1949 )
          *(this + 1951) = (int)(result + 2);
        result = (int *)*result;
      }
      while ( result != (int *)*(this + 32) );
    }
  }
  else
  {
    v11 = *this;
    fld_e19492 = *(this + 1949);
    *(this + 1951) = 0;
    return (int *)(*(int (/*thiscall*/ **)(int *, int))(v11 + 208))(this, fld_e19492);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B9720 sub_4B9720 —— 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/+52 槽；调 sub_4D71B0 命中主处理器【待验证】）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B9720(size_t *this, uint32_t *pArg2, int nArg3, int nArg4)
{
  uint32_t *pArg22; // edi
  size_t v6; // eax
  int v7; // ebx
  int v8; // eax
  int i; // ebx
  int v10; // edx
  int pObj; // eax
  int v12; // eax
  int v13; // eax
  uint32_t *v14; // ebx
  size_t v15; // eax
  char *v16; // eax
  char *v17; // edi
  int fld_e29; // ecx
  int v19; // ebx
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v27; // [esp+Ch] [ebp-14h]
  float v28; // [esp+Ch] [ebp-14h]
  int v29; // [esp+10h] [ebp-10h] BYREF
  int v30; // [esp+1Ch] [ebp-4h]

  pArg22 = pArg2;
  v6 = *this;
  v29 = 100;
  v7 = (*(int (/*thiscall*/ **)(size_t *, int *, uint32_t *))(v6 + 648))(this, &v29, pArg2);
  if ( (*(uint8_t (/*thiscall*/ **)(size_t *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(size_t *))(*this + 724))(this) == 0 )
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 348))(pArg2);
    if ( (*(uint8_t *)(v8 + 16) != 0 || *(float *)v8 > 0.0)
      && (uint8_t)nArg4 == 0
      && v29 > 0
      && v7 != 2
      && sub_4AED20((int)this) != 2 )
    {
      for ( i = 0; i < 18; ++i )
      {
        if ( i != 8 )
          (*(void (/*thiscall*/ **)(size_t *, int))(*this + 1104))(this, i);
      }
      v10 = *pArg2;
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v10 + 40))(pArg2, 529) != 0
          || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 576))(pArg2) != 0
          && (pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 576))(pArg2),
              (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0) )
        {
LABEL_21:
          v13 = (*(int (/*thiscall*/ **)(size_t *))(*this + 52))(this);
          sub_495A70(dword_99FD58, -1, 6, v13);
        }
      }
      else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v10 + 40))(pArg2, 273) != 0 )
      {
        v12 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v12 == 4 || v12 == 6 )
          goto LABEL_21;
      }
    }
  }
  if ( *((uint8_t *)this + 7992) != 0 )
  {
    v27 = sub_42FCB0(228);
    v14 = nullptr;
    v30 = 0;
    if ( v27 != 0 )
      v14 = (uint32_t *)sub_431860((char)"Common/CommonEffect/Animation/SuperArmorEffect.ani", 1);
    v15 = *this;
    v30 = -1;
    v28 = (double)(*(int (/*thiscall*/ **)(size_t *))(v15 + 192))(this) * 0.0071428572;
    sub_4920E0(v14, v28, v28);
    v16 = (char *)sub_44B6C0(284);
    v17 = v16;
    v30 = 1;
    if ( v16 != nullptr )
    {
      sub_44E0D0(v16, (int)v14, 1);
      *(uint32_t *)v17 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v17 = nullptr;
    }
    fld_e29 = *(this + 29);
    v30 = -1;
    sub_45FE80(fld_e29, (int)v17, 2, 0, (int)v17, (int)this, 0);
    v19 = *(uint32_t *)v17;
    v20 = (*(int (/*thiscall*/ **)(size_t *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(char *, int))(v19 + 148))(v17, v20);
    v21 = *(uint32_t *)v17;
    v22 = (*(int (/*thiscall*/ **)(size_t *))(*this + 128))(this);
    v23 = (*(int (/*thiscall*/ **)(size_t *, int))(*this + 124))(this, v22);
    v24 = (*(int (/*thiscall*/ **)(size_t *, int))(*this + 120))(this, v23);
    (*(void (/*thiscall*/ **)(char *, int))(v21 + 112))(v17, v24);
    pArg22 = pArg2;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(size_t *))(*this + 724))(this) == 0 && v29 > 0 && (uint8_t)nArg4 == 0 )
  {
    v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 348))(pArg22);
    if ( *(uint8_t *)(v25 + 16) != 0 || *(float *)v25 > 0.0 )
      sub_4B2B50(this, pArg22);
  }
  return sub_4D71B0(this, *(float *)&pArg22, nArg3, nArg4);  // 【命中主处理器 vt+512（§2 全文定案）】
}


// ------------------------------------------------------------
// 0x4B99C0 sub_4B99C0 —— 骰子演出（Dice.ani/DiceGlow.ani；DICE_ROLL/OUT/GET 事件；sub_493D00 变速）
// ------------------------------------------------------------
void */*userpurge*/ sub_4B99C0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, void *pArg3)
{
  void *result; // eax
  uint32_t *v5; // edi
  int pObj; // edi
  int v7; // ebx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // edi
  int v15; // eax
  uint32_t *v16; // edi
  int pMem; // edi
  int v18; // ebx
  int v19; // edi
  int v20; // eax
  int v21; // eax
  int i; // esi
  int v23; // eax
  int v24; // [esp-8h] [ebp-24h]
  void *Blocka; // [esp+8h] [ebp-14h]
  void *Block; // [esp+8h] [ebp-14h]
  uint32_t *v28; // [esp+Ch] [ebp-10h]
  void *pObj2; // [esp+24h] [ebp+8h]

  result = (void *)pDwArg1[29];
  v5 = nullptr;
  if ( result != nullptr )
  {
    if ( sub_42FCB0(228) != 0 )
      v5 = (uint32_t *)sub_431860((char)"Common/Etc/Animation/DiceGlow.ani", 1);
    v28 = v5;
    sub_493D00((int)v5, 20.0);
    sub_4920E0(v5, 0.80000001, 0.80000001);
    if ( operator new(0x11Cu) != nullptr )
      pObj = sub_44E0D0(v5, 1);
    else
      pObj = 0;
    Blocka = (void *)pObj;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 72))(pObj, 2);
    sub_45FE80(pDwArg1[29], pObj, 2, 0, pObj, (int)pDwArg1, 0);
    v7 = *(uint32_t *)pObj;
    v8 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 192))(pDwArg1);
    v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);
    v10 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v8 + v9 + 20);
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v10);
    (*(void (/*thiscall*/ **)(void *, int))(v7 + 112))(Blocka, v11);
    (*(void (/*thiscall*/ **)(void *, int *))(*(uint32_t *)Blocka + 60))(Blocka, pDwArg1);
    sub_4A06D0(nArg2);
    v12 = v28[11];
    if ( v12 != 0 )
      v13 = (v28[12] - v12) / 88;
    else
      v13 = 0;
    v14 = 0;
    for ( Block = (void *)v13; v14 < v13; ++v14 )
    {
      v15 = sub_4924C0(v14);
      *(uint32_t *)(v15 + 48) = 25;
      *(uint32_t *)(v15 + 32) = -1;
      if ( v14 != 0 )
      {
        switch ( v14 )
        {
          case 1:
            *(uint32_t *)(v15 + 16) = -40;
            break;
          case 2:
            *(uint32_t *)(v15 + 16) = -80;
            *(uint8_t *)(v15 + 36) = 1;
            break;
          case 3:
            *(uint32_t *)(v15 + 16) = -40;
            *(uint8_t *)(v15 + 36) = 1;
            break;
          case 4:
            *(uint32_t *)(v15 + 16) = 0;
            break;
          case 5:
            *(uint32_t *)(v15 + 16) = -20;
            break;
          case 6:
            *(uint32_t *)(v15 + 16) = -40;
            *(uint8_t *)(v15 + 36) = 1;
            break;
          case 7:
            *(uint32_t *)(v15 + 16) = -20;
            *(uint8_t *)(v15 + 36) = 1;
            break;
          case 8:
            *(uint32_t *)(v15 + 16) = 0;
            break;
          case 9:
            *(uint32_t *)(v15 + 16) = 0;
            if ( (int *)dword_8F7C04 == pDwArg1 )
            {
              if ( (uint8_t)pArg3 != 0 )
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DICE_GET", -1, 0, 0);
              else
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DICE_OUT", -1, 0, 0);
            }
            break;
          default:
            break;
        }
      }
      else
      {
        *(uint32_t *)(v15 + 16) = 0;
        if ( (int *)dword_8F7C04 == pDwArg1 )
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DICE_ROLL", -1, 0, 0);
      }
    }
    v16 = sub_42FCB0(228) != 0 ? (uint32_t *)sub_431860((char)"Common/Etc/Animation/Dice.ani", 1) : nullptr;
    sub_493D00((int)v16, 20.0);
    sub_4920E0(v16, 0.80000001, 0.80000001);
    pMem = operator new(0x11Cu) != nullptr ? sub_44E0D0(v16, 1) : 0;
    pObj2 = (void *)pMem;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pMem + 72))(pMem, 2);
    sub_45FE80(pDwArg1[29], pMem, 2, 0, pMem, (int)pDwArg1, 0);
    v18 = *(uint32_t *)pMem;
    v19 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 192))(pDwArg1);
    v24 = v19 + (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) + 20;
    v20 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
    v21 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v20);
    (*(void (/*thiscall*/ **)(void *, int))(v18 + 112))(pObj2, v21);
    (*(void (/*thiscall*/ **)(void *, int *))(*(uint32_t *)pObj2 + 60))(pObj2, pDwArg1);
    sub_4A06D0(v24);
    result = Block;
    for ( i = 0; i < (int)Block; ++i )
    {
      v23 = sub_4924C0(i);
      *(uint32_t *)(v23 + 48) = 25;
      *(uint32_t *)(v23 + 32) = -1;
      switch ( i )
      {
        case 0:
          goto LABEL_59;
        case 1:
          *(uint32_t *)(v23 + 16) = -40;
          break;
        case 2:
          *(uint32_t *)(v23 + 16) = -80;
          *(uint8_t *)(v23 + 36) = 1;
          break;
        case 3:
          *(uint32_t *)(v23 + 16) = -40;
          *(uint8_t *)(v23 + 36) = 1;
          break;
        case 4:
          goto LABEL_59;
        case 5:
          *(uint32_t *)(v23 + 16) = -20;
          break;
        case 6:
          *(uint32_t *)(v23 + 16) = -40;
          *(uint8_t *)(v23 + 36) = 1;
          break;
        case 7:
          *(uint32_t *)(v23 + 16) = -20;
          *(uint8_t *)(v23 + 36) = 1;
          break;
        case 8:
        case 9:
LABEL_59:
          *(uint32_t *)(v23 + 16) = 0;
          break;
        default:
          break;
      }
      result = Block;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4B9DB0 sub_4B9DB0 —— GET_GOLD 演出（MoneyUp.img/ExpUp.img → sub_4B59A0 包装 + +48/+40 槽）
// ------------------------------------------------------------
void /*userpurge*/ sub_4B9DB0(
        int *a1@<ecx>,
        int a2@<edi>,
        int a3,
        int a4,
        int a5,
        int a6,
        char a7,
        int a8,
        int a9,
        int a10)
{
  int *v10; // ebx
  int v11; // kr04_4
  int v12; // edi
  void **v13; // eax
  char v14; // al
  int v15; // eax
  char v16; // al
  int v17; // eax
  int v18; // edi
  int v19; // esi
  int v20; // ecx
  char *v21; // eax
  char *v22; // esi
  int v23; // edx
  int v24; // edi
  int v25; // eax
  int v26; // eax
  bool v27; // cc
  int v28; // [esp-8h] [ebp-94h]
  int v31; // [esp+14h] [ebp-78h]
  int v32; // [esp+18h] [ebp-74h]
  int v33; // [esp+1Ch] [ebp-70h]
  int v34; // [esp+1Ch] [ebp-70h]
  int v35; // [esp+1Ch] [ebp-70h]
  char Buffer[64]; // [esp+20h] [ebp-6Ch] BYREF
  void *Block[5]; // [esp+64h] [ebp-28h] BYREF
  unsigned int v38; // [esp+78h] [ebp-14h]
  int v39; // [esp+7Ch] [ebp-10h]
  int v40; // [esp+88h] [ebp-4h]
  int i; // [esp+98h] [ebp+Ch]
  int v42; // [esp+98h] [ebp+Ch]

  v10 = a1;
  v39 = dword_796E50;
  if ( a1[29] != 0 )
  {
    memset(Buffer, 0, sizeof(Buffer));
    v38 = 15;
    Block[4] = nullptr;
    LOBYTE(Block[0]) = 0;
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    v40 = 0;
    if ( a3 != 0 )
    {
      if ( a3 == 1 )
      {
        sub_4015C0("Common/Etc/MoneyUp.img", 0x16u);  // 【std::string构造赋值】
        sprintf(Buffer, off_6C789C, a4);
      }
    }
    else
    {
      sub_4015C0("Common/Etc/ExpUp.img", 0x14u);  // 【std::string构造赋值】
      if ( a5 != 0 )
        sprintf(Buffer, "%d+%dE", a4, a5);
      else
        sprintf(Buffer, "%dE", a4);
    }
    v11 = strlen(Buffer);
    v12 = 0;
    v13 = (void **)Block[0];
    if ( v38 < 0x10 )
      v13 = Block;
    (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v13);
    for ( i = 0; i < v11; ++i )
    {
      v14 = Buffer[i];
      if ( v14 == 43 )
      {
        v15 = sub_418DD0(11);
      }
      else if ( v14 == 69 || v14 == 71 )
      {
        v15 = sub_418DD0(10);
      }
      else
      {
        v15 = sub_418DD0(v14 - 48);
      }
      v12 += *(uint32_t *)(v15 + 36);
    }
    v32 = v12 / -2;
    v42 = 0;
    if ( v11 > 0 )
    {
      do
      {
        v16 = Buffer[v42];
        if ( v16 == 69 || v16 == 71 )
        {
          v17 = sub_418DD0(10);
        }
        else if ( v16 == 43 )
        {
          v17 = sub_418DD0(11);
        }
        else
        {
          v17 = sub_418DD0(v16 - 48);
        }
        v18 = v17;
        v31 = v17;
        v33 = sub_42FCB0(228);
        v19 = 0;
        LOBYTE(v40) = 1;
        if ( v33 != 0 )
          v34 = sub_4B59A0(3);
        else
          v34 = 0;
        LOBYTE(v40) = 0;
        do
        {
          v20 = sub_4924C0(v19);
          *(uint32_t *)v20 = v19 != 0 ? v18 : 0;
          *(uint32_t *)(v20 + 12) = v32;
          if ( v19 != 0 )
          {
            if ( v19 == 1 )
            {
              *(uint32_t *)(v20 + 48) = 300;
              *(uint32_t *)(v20 + 16) = *(uint32_t *)(v18 + 40) / -2;
              *(uint8_t *)(v20 + 36) = 1;
            }
            else if ( v19 == 2 )
            {
              *(uint32_t *)(v20 + 48) = 600;
              *(uint32_t *)(v20 + 16) = -30 - *(uint32_t *)(v18 + 40) / 2;
            }
          }
          else
          {
            *(uint32_t *)(v20 + 48) = a6;
            *(uint32_t *)(v20 + 16) = *(uint32_t *)(v18 + 40) / -2;
          }
          ++v19;
        }
        while ( v19 < 3 );
        v21 = (char *)operator new(0x11Cu);
        LOBYTE(v40) = 2;
        if ( v21 != nullptr )
          v22 = sub_44E0D0(v21, v34, 1);
        else
          v22 = nullptr;
        v23 = *(uint32_t *)v22;
        LOBYTE(v40) = 0;
        (*(void (/*thiscall*/ **)(char *, int, int))(v23 + 72))(v22, 2, a2);
        sub_45FE80(v10[29], v18, 2, 0, (int)v22, (int)v10, 0);
        if ( a7 != 0 )
        {
          a2 = a10 + 45;
          (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)v22 + 112))(v22, a8, a9);
        }
        else
        {
          v24 = *(uint32_t *)v22;
          v35 = (*(int (/*thiscall*/ **)(int *))(*v10 + 192))(v10);
          v25 = (*(int (/*thiscall*/ **)(int *))(*v10 + 128))(v10);
          v10 = a1;
          a2 = v35 + v25 + 45;
          v28 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1);
          v26 = (*(int (/*thiscall*/ **)(int *))(*v10 + 120))(v10);
          (*(void (/*thiscall*/ **)(char *, int))(v24 + 112))(v22, v26);
          (*(void (/*thiscall*/ **)(char *, int *))(*(uint32_t *)v22 + 60))(v22, a1);
          sub_4A06D0(v28);
          v18 = v31;
        }
        v27 = v42 + 1 < v11;
        v32 += *(uint32_t *)(v18 + 36);
        ++v42;
      }
      while ( v27 );
    }
    if ( a3 == 0 && (int *)dword_8F7C04 == v10 )
      sub_432EA0("GET_GOLD", -1, 0, 0);
    if ( v38 >= 0x10 )
      j__free(Block[0]);
  }
}


// ------------------------------------------------------------
// 0x4BA130 sub_4BA130 —— FP_UP 演出（Interface/BattleDungeon/battledungeon_result.img；战斗副本结算）
// ------------------------------------------------------------
void /*userpurge*/ sub_4BA130(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, char pszArg5, int nArg6, int nArg7, int nArg8)
{
  int *pDwArg12; // ebx
  int v9; // esi
  int nLen; // kr04_4
  void **Block2; // eax
  uint32_t *v12; // edi
  char v13; // al
  char v14; // al
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // esi
  int v19; // ecx
  char *pMem; // eax
  char *pObj; // esi
  int v22; // edx
  int v23; // edi
  int v24; // eax
  int v25; // eax
  int v26; // eax
  bool v27; // cc
  int v28; // [esp-8h] [ebp-98h]
  uint32_t *v31; // [esp+10h] [ebp-80h]
  int v32; // [esp+14h] [ebp-7Ch]
  int v33; // [esp+18h] [ebp-78h]
  int *v34; // [esp+20h] [ebp-70h]
  int v35; // [esp+20h] [ebp-70h]
  char Buffer[64]; // [esp+24h] [ebp-6Ch] BYREF
  size_t v37; // [esp+64h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+68h] [ebp-28h] BYREF
  unsigned int v39; // [esp+7Ch] [ebp-14h]
  int dword_796E502; // [esp+80h] [ebp-10h]
  int v41; // [esp+8Ch] [ebp-4h]
  int i; // [esp+98h] [ebp+8h]
  int v43; // [esp+98h] [ebp+8h]

  pDwArg12 = pDwArg1;
  dword_796E502 = dword_796E50;
  v9 = 0;
  if ( pDwArg1[29] != 0 )
  {
    memset(Buffer, 0, sizeof(Buffer));
    v39 = 15;
    Block[4] = nullptr;
    LOBYTE(Block[0]) = 0;
    sub_4015C0(&v37, szPassword, 0);  // 【std::string构造赋值】
    v41 = 0;
    sub_4015C0(&v37, "Interface/BattleDungeon/battledungeon_result.img", 0x30u);  // 【std::string构造赋值】
    sprintf(Buffer, off_6F6564, nArg3);
    nLen = strlen(Buffer);
    Block2 = (void **)Block[0];
    if ( v39 < 0x10 )
      Block2 = Block;
    v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, Block2);
    v31 = v12;
    for ( i = 0; i < nLen; ++i )
    {
      v13 = Buffer[i];
      if ( v13 == 102 )
        v9 += *(uint32_t *)(sub_418DD0(v12, 0xCu) + 36);
      else
        v9 = v9 + *(uint32_t *)(sub_418DD0(v12, v13 - 5) + 36) - 4;
    }
    v33 = v9 / -2;
    v43 = 0;
    if ( nLen > 0 )
    {
      while ( 1 )
      {
        v14 = Buffer[v43];
        v15 = v14 == 102 ? sub_418DD0(v12, 0xCu) : sub_418DD0(v12, v14 - 5);
        v16 = v15;
        v32 = v15;
        v17 = sub_42FCB0(228);
        v18 = 0;
        LOBYTE(v41) = 1;
        v34 = v17 != 0 ? (int *)sub_4B59A0(v17, 3u) : nullptr;
        LOBYTE(v41) = 0;
        do
        {
          v19 = sub_4924C0(v34, v18);
          *(uint32_t *)v19 = v18 != 0 ? v16 : 0;
          *(uint32_t *)(v19 + 12) = v33;
          if ( v18 != 0 )
          {
            if ( v18 == 1 )
            {
              *(uint32_t *)(v19 + 48) = 300;
              *(uint32_t *)(v19 + 16) = *(uint32_t *)(v16 + 40) / -2;
              *(uint8_t *)(v19 + 36) = 1;
            }
            else if ( v18 == 2 )
            {
              *(uint32_t *)(v19 + 48) = 600;
              *(uint32_t *)(v19 + 16) = -50 - *(uint32_t *)(v16 + 40) / 2;
            }
          }
          else
          {
            *(uint32_t *)(v19 + 48) = nArg4;
            *(uint32_t *)(v19 + 16) = *(uint32_t *)(v16 + 40) / -2;
          }
          ++v18;
        }
        while ( v18 < 3 );
        pMem = (char *)operator new(0x11Cu);
        LOBYTE(v41) = 2;
        pObj = pMem != nullptr ? sub_44E0D0(pMem, (int)v34, 1) : nullptr;
        v22 = *(uint32_t *)pObj;
        LOBYTE(v41) = 0;
        (*(void (/*thiscall*/ **)(char *, int, int))(v22 + 72))(pObj, 2, nArg2);
        sub_45FE80(pDwArg12[29], v16, 2, 0, (int)pObj, (int)pDwArg12, 0);
        if ( pszArg5 != 0 )
        {
          nArg2 = nArg8 + 45;
          (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 112))(pObj, nArg6, nArg7);
        }
        else
        {
          v23 = *(uint32_t *)pObj;
          v35 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 192))(pDwArg12);
          v24 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 128))(pDwArg12);
          pDwArg12 = pDwArg1;
          nArg2 = v35 + v24 + 45;
          v28 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
          v25 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 120))(pDwArg12);
          (*(void (/*thiscall*/ **)(char *, int))(v23 + 112))(pObj, v25);
          v26 = (*(int (/*thiscall*/ **)(char *, int *))(*(uint32_t *)pObj + 60))(pObj, pDwArg1);
          sub_4A06D0(v26, v28);
          v16 = v32;
        }
        v27 = v43 + 1 < nLen;
        v33 += *(uint32_t *)(v16 + 36);
        ++v43;
        if ( !v27 )
          break;
        v12 = v31;
      }
    }
    if ( (int *)dword_8F7C04 == pDwArg12 )
      sub_432EA0("FP_UP", -1, 0, 0);
    if ( v39 >= 0x10 )
      j__free(Block[0]);
  }
}


// ------------------------------------------------------------
// 0x4BA450 sub_4BA450 —— GET_ITEM 演出
// ------------------------------------------------------------
void /*thiscall*/ sub_4BA450(int *this, int nArg2, int nArg3)
{
  int v4; // edi
  int v6; // eax
  int v7; // esi
  int v8; // ecx
  char *pMem; // eax
  char *pObj; // esi
  int v11; // edi
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int *v17; // [esp+28h] [ebp+8h]
  int v18; // [esp+28h] [ebp+8h]

  v4 = 0;
  if ( nArg2 != 0 && *(this + 29) != 0 )
  {
    v6 = sub_42FCB0(228);
    if ( v6 != 0 )
      v17 = (int *)sub_4B59A0(v6, 3u);
    else
      v17 = nullptr;
    v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 68);
    do
    {
      v8 = sub_4924C0(v17, v4);
      *(uint32_t *)v8 = v4 != 0 ? v7 : 0;
      *(uint32_t *)(v8 + 12) = *(uint32_t *)(v7 + 36) / -2;
      if ( v4 != 0 )
      {
        if ( v4 == 1 )
        {
          *(uint32_t *)(v8 + 48) = 300;
          *(uint32_t *)(v8 + 16) = *(uint32_t *)(v7 + 40) / -2;
          *(uint8_t *)(v8 + 36) = 1;
        }
        else if ( v4 == 2 )
        {
          *(uint32_t *)(v8 + 48) = 600;
          *(uint32_t *)(v8 + 16) = -30 - *(uint32_t *)(v7 + 40) / 2;
        }
      }
      else
      {
        *(uint32_t *)(v8 + 48) = nArg3;
        *(uint32_t *)(v8 + 16) = *(uint32_t *)(v7 + 40) / -2;
      }
      ++v4;
    }
    while ( v4 < 3 );
    pMem = (char *)operator new(0x11Cu);
    if ( pMem != nullptr )
      pObj = sub_44E0D0(pMem, (int)v17, 1);
    else
      pObj = nullptr;
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 72))(pObj);
    sub_45FE80(*(this + 29), v4, 2, 0, (int)pObj, (int)this, 0);
    v18 = *(uint32_t *)pObj;
    v11 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);
    v12 = v11 + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + 20;
    v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v12);
    v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);
    (*(void (/*thiscall*/ **)(char *, int))(v18 + 112))(pObj, v14);
    v15 = (*(int (/*thiscall*/ **)(char *, int *))(*(uint32_t *)pObj + 60))(pObj, this);
    sub_4A06D0(v15, 2);
    if ( (int *)dword_8F7C04 == this && nArg3 == 0 )
      sub_432EA0("GET_ITEM", -1, 0, 0);
  }
}



// ------------------------------------------------------------
// 0x4BA610 sub_4BA610 —— 魔能充能动画选择（Character/Mage/Effect/Animation/MagicOnCharge%d%d.ani / MagicFullCharge%d%d.ani）
// ------------------------------------------------------------
int /*thiscall*/ sub_4BA610(uint32_t *this, int pArg2)
{
  int result; // eax
  int v4; // esi
  uint32_t *pThis_2; // edi
  int v6; // eax
  int v7; // eax
  bool v8; // zf
  int v9; // [esp+4h] [ebp-114h]
  int v10; // [esp+4h] [ebp-114h]
  char Buffer[256]; // [esp+8h] [ebp-110h] BYREF
  int dword_796E502; // [esp+108h] [ebp-10h]
  int v13; // [esp+114h] [ebp-4h]
  int v14; // [esp+120h] [ebp+8h]

  dword_796E502 = dword_796E50;
  result = *(this + 2 * pArg2 + 2033);
  if ( result == 0 )
  {
    v4 = 1;
    pThis_2 = this + 2 * pArg2 + 2043;
    v14 = 2;
    do
    {
      sprintf(Buffer, "Character/Mage/Effect/Animation/MagicOnCharge%d%d.ani", pArg2, v4);
      v9 = sub_42FCB0(228);
      v13 = 0;
      if ( v9 != 0 )
        v6 = sub_431860((char)Buffer, 1);
      else
        v6 = 0;
      v13 = -1;
      *(pThis_2 - 10) = v6;
      sprintf(Buffer, "Character/Mage/Effect/Animation/MagicFullCharge%d%d.ani", pArg2, v4);
      v10 = sub_42FCB0(228);
      v13 = 1;
      if ( v10 != 0 )
        v7 = sub_431860((char)Buffer, 1);
      else
        v7 = 0;
      *pThis_2++ = v7;
      ++v4;
      result = v14 - 1;
      v8 = v14 == 1;
      v13 = -1;
      --v14;
    }
    while ( !v8 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BA730 sub_4BA730 —— 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_CHARGE/ENERGY_CHARGE_END）
// ------------------------------------------------------------
int /*thiscall*/ sub_4BA730(uint32_t *this, int nArg2, int pArg3, int nArg4, int nArg5)
{
  uint32_t *pThis_2; // edi
  int result; // eax
  int *pThis_23; // edi
  int k; // ebx
  int *pThis_22; // edi
  int j; // ebx
  int i; // [esp+Ch] [ebp-4h]

  if ( *(this + 2 * pArg3 + 2033) == 0 )
    sub_4BA610(pArg3);
  pThis_2 = this + 2 * pArg3 + 2043;
  for ( i = 2; i != 0; --i )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(pThis_2 - 10));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_2++);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);
  result = nArg2;
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
        this,
        1,
        *(this + 2 * pArg3 + 2043),
        nArg4,
        nArg5,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
        this,
        1,
        *(this + 2 * pArg3 + 2044),
        nArg4,
        nArg5,
        0,
        0);
      pThis_22 = this + 2 * pArg3 + 2043;
      for ( j = 2; j != 0; --j )
        sub_493D00(*pThis_22++, 100.0);
      return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
               this,
               "ENERGY_CHARGE_END",
               -1,
               0,
               0);
    }
  }
  else
  {
    pThis_23 = this + 2 * pArg3 + 2033;
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int, uint32_t, uint32_t))(*this + 204))(this, 1, *pThis_23, nArg4, nArg5, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(
      this,
      1,
      *(this + 2 * pArg3 + 2034),
      nArg4,
      nArg5,
      0,
      0);
    for ( k = 2; k != 0; --k )
      sub_493D00(*pThis_23++, 100.0);
    return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "ENERGY_CHARGE",
             10,
             0,
             0);
  }
  return result;
}



// ============================================================
// §N 0x4BA8A0-0x4BAED0  ★角色创建入口（job→.equ）
// ============================================================
// ------------------------------------------------------------
// 0x4BA8A0 sub_4BA8A0 —— ★角色创建入口
//   job/growtype → sub_4B0080 .equ 路径 → sub_442D00 打开 → sub_4B5FD0 解析装载；
//   失败 CHARACTER CREATE FAIL! JOB %d。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BA8A0(uint32_t *this, int ArgList)
{
  int v2; // edi
  int v4; // eax
  int v6; // [esp+8h] [ebp-4h] BYREF

  v2 = ArgList;
  sub_442D00(&v6, &ArgList);
  if ( v6 == dword_9B7C40 )
    return off_77F3FC("CHARACTER CREATE FAIL! JOB %d", v2);
  v4 = *(uint32_t *)(v6 + 40) < 0x10u ? v6 + 20 : *(uint32_t *)(v6 + 20);
  if ( v4 == 0 )
    return off_77F3FC("CHARACTER CREATE FAIL! JOB %d", v2);
  else
    return sub_4B5FD0(this, v4);
}



// ------------------------------------------------------------
// 0x4BA910 sub_4BA910
// ------------------------------------------------------------
void /*thiscall*/ sub_4BA910(void ***this)
{
  sub_4B5A50(this + 18);
  sub_4A4940((int)(this + 1));
}



// ------------------------------------------------------------
// 0x4BA960 sub_4BA960
// ------------------------------------------------------------
void /*stdcall*/ sub_4BA960(void ***uArg1, void ***uArg2)
{
  void ***i; // esi

  for ( i = uArg1; i != uArg2; i += 31 )
    sub_4BA910(i);
}



// ------------------------------------------------------------
// 0x4BA990 sub_4BA990
// ------------------------------------------------------------
int /*thiscall*/ sub_4BA990(int this)
{
  void ***fld_4; // esi
  int result; // eax
  void ***i; // edi

  fld_4 = *(void ****)(this + 4);
  result = 0;
  if ( fld_4 != nullptr )
  {
    for ( i = *(void ****)(this + 8); fld_4 != i; fld_4 += 31 )
      sub_4BA910(fld_4);
    j__free(*(void **)(this + 4));
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4BA9E0 sub_4BA9E0
// ------------------------------------------------------------
char */*thiscall*/ sub_4BA9E0(char *this, void *Block, int nArg3)
{
  sub_485CC0();
  *(uint32_t *)this = &CNRDEquipment::`vftable';
  sub_4B3BE0(this + 148);
  sub_437E70(this + 212);
  sub_4E9A50(this + 1160);
  *(this + 1224) = 0;
  *((uint32_t *)this + 305) = &off_6C2B88;
  *((uint32_t *)this + 307) = 0;
  *(this + 1232) = 1;
  *(this + 1234) = 0;
  *(this + 1233) = 0;
  *((uint32_t *)this + 311) = 0;
  *((uint32_t *)this + 310) = 0;
  *((uint32_t *)this + 309) = 0;
  *((uint32_t *)this + 314) = 0;
  *((uint32_t *)this + 315) = 0;
  *((uint32_t *)this + 316) = 0;
  *((uint32_t *)this + 318) = 0;
  sub_41BFE0(szPassword);
  *((uint32_t *)this + 323) = 0;
  *((uint32_t *)this + 324) = 0;
  *((uint32_t *)this + 325) = 0;
  *((uint32_t *)this + 327) = 0;
  *((uint32_t *)this + 328) = 0;
  *((uint32_t *)this + 329) = 0;
  sub_4E9D70(this);
  sub_4EE580(Block, nArg3, -1, -1);
  return this;
}



// ------------------------------------------------------------
// 0x4BAB00 sub_4BAB00
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAB00(uint32_t *this, int nArg2)
{
  int result; // eax

  dword_9B08E8[2 * *(this + 37)] = nArg2;
  result = nArg2 + sub_699000((int)&unk_9B0C70);  // 【clock_now(clk)】
  dword_9B08EC[2 * *(this + 37)] = result;
  return result;
}



// ------------------------------------------------------------
// 0x4BAB40 sub_4BAB40
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAB40(uint32_t *this)
{
  return dword_9B08E8[2 * *(this + 37)];
}



// ------------------------------------------------------------
// 0x4BAB50 sub_4BAB50
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAB50(uint32_t *this)
{
  return dword_9B08EC[2 * *(this + 37)];
}



// ------------------------------------------------------------
// 0x4BAB60 sub_4BAB60
// ------------------------------------------------------------
float */*thiscall*/ sub_4BAB60(float *this, int nArg2, int nArg3, int nArg4, float *pArg5)
{
  *pArg5 = *(this + 336) * *pArg5;
  return pArg5;
}



// ------------------------------------------------------------
// 0x4BAB80 sub_4BAB80
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAB80(uint32_t *this, int nArg2)
{
  *(this + 336) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4BAB90 ?GetLocation@VirtualProcessor@details@Concurrency@@QBEABVlocation@3@XZ
// ------------------------------------------------------------
const struct Concurrency::location */*thiscall*/ Concurrency::details::VirtualProcessor::GetLocation(
        Concurrency::details::VirtualProcessor *this)
{
  return (Concurrency::details::VirtualProcessor *)((char *)this + 148);
}



// ------------------------------------------------------------
// 0x4BABA0 sub_4BABA0
// ------------------------------------------------------------
char */*thiscall*/ sub_4BABA0(char *this)
{
  return this + 212;
}



// ------------------------------------------------------------
// 0x4BABB0 sub_4BABB0
// ------------------------------------------------------------
char */*thiscall*/ sub_4BABB0(char *this)
{
  return this + 1160;
}



// ------------------------------------------------------------
// 0x4BABC0 sub_4BABC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BABC0(void *this)
{
  int pThis_4A8; // eax

  pThis_4A8 = sub_41A5E0((unsigned int)this + 1192);
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 192))(this, pThis_4A8 - 1);
}



// ------------------------------------------------------------
// 0x4BABE0 sub_4BABE0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4BABE0(void *this)
{
  return sub_41A5E0((unsigned int)this + 166) != 0 && sub_41A5E0((unsigned int)this + 1192) == 0;
}



// ------------------------------------------------------------
// 0x4BAC10 sub_4BAC10
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAC10(uint32_t *this)
{
  int pThis_131; // edi

  pThis_131 = (int)(this + 305);
  if ( *(this + 290) <= (unsigned int)(sub_699000((int)(this + 305)) / 1000) )  // 【clock_now(clk)】
    return 0;
  else
    return *(this + 290) - sub_699000(pThis_131) / 1000;  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x4BAC70 sub_4BAC70
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAC70(int this, int nArg2)
{
  int result; // eax

  result = nArg2;
  *(uint32_t *)(this + 1284) = nArg2;
  if ( nArg2 == 0 )
    *(uint8_t *)(this + 1276) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4BACA0 sub_4BACA0
// ------------------------------------------------------------
char /*thiscall*/ sub_4BACA0(uint8_t *this, char pszArg2)
{
  *(this + 1276) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4BACD0 sub_4BACD0
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_4BACD0(unsigned int **this)
{
  return sub_41ACF0(this + 318);
}



// ------------------------------------------------------------
// 0x4BACE0 sub_4BACE0
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4BACE0(uint32_t *this)
{
  return *(this + 320) != -1;
}



// ------------------------------------------------------------
// 0x4BAD10 sub_4BAD10
// ------------------------------------------------------------
char /*thiscall*/ sub_4BAD10(uint8_t *this, char pszArg2)
{
  *(this + 1320) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4BAD40 sub_4BAD40
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4BAD40(uint32_t *this)
{
  return sub_41C5A0(this + 313) != 0;
}



// ------------------------------------------------------------
// 0x4BAD60 sub_4BAD60
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAD60(uint32_t *this, unsigned int uArg2)
{
  int fld_e327; // edx

  fld_e327 = *(this + 327);
  if ( fld_e327 != 0 && (*(this + 328) - fld_e327) >> 2 > uArg2 )
    return *(uint32_t *)(*(this + 327) + 4 * uArg2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4BADA0 sub_4BADA0
// ------------------------------------------------------------
void */*thiscall*/ sub_4BADA0(void *Block, char pszArg2)
{
  sub_4BADD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4BADD0 sub_4BADD0
// ------------------------------------------------------------
void /*thiscall*/ sub_4BADD0(int this)
{
  *(uint32_t *)this = &CNRDEquipment::`vftable';
  sub_4EF270();
  if ( *(uint32_t *)(this + 1308) != 0 )
    j__free(*(void **)(this + 1308));
  *(uint32_t *)(this + 1308) = 0;
  *(uint32_t *)(this + 1312) = 0;
  *(uint32_t *)(this + 1316) = 0;
  sub_4BA990(this + 1288);
  sub_41B010((void **)(this + 1272));
  if ( *(uint32_t *)(this + 1256) != 0 )
    j__free(*(void **)(this + 1256));
  *(uint32_t *)(this + 1256) = 0;
  *(uint32_t *)(this + 1260) = 0;
  *(uint32_t *)(this + 1264) = 0;
  *(uint32_t *)(this + 1220) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 1224) = 0;
  sub_445150(this + 1160);
  sub_4382D0(this + 212);
  sub_4B3270((uint32_t *)(this + 148));
  sub_485920((uint32_t *)this);
}



// ============================================================
// §O 0x4BAED0-0x4BC900  部件路径/名称解析（sub_4BC700 路径→id）
// ============================================================
// ------------------------------------------------------------
// 0x4BAED0 sub_4BAED0 —— 角色组装（+248/+256 槽；.equ 子块 → sub_4B50F0 职业特效、sub_4B0080 路径、sub_4BA9E0 生命周期）
// ------------------------------------------------------------
char /*thiscall*/ sub_4BAED0(char *this, int nArg2, void *Block)
{
  int pThis_6FC; // eax
  int pThis_6FB; // ebx
  unsigned int i; // edi
  int pThis_6FC2; // ecx
  int v8; // edx
  unsigned int v9; // edi
  int v10; // ebx
  int v11; // ecx
  void (/*thiscall*/ ***pThis_76A)(uint32_t, int); // ecx
  int pThis_769; // ecx
  int v14; // ebx
  int j; // edi
  int pThis_7692; // ecx
  uint32_t *pThis_76B; // eax
  void *v18; // edi
  char *pMem; // eax
  char *pObj; // eax
  uint32_t *v21; // edi
  uint32_t *v22; // ebx
  int pThis_6FB2; // [esp-24h] [ebp-3Ch]
  uint32_t *Blocka; // [esp+24h] [ebp+Ch]

  pThis_6FC = *((uint32_t *)this + 1788);
  if ( pThis_6FC != nArg2 )
    goto LABEL_4;
  if ( *(this + 7156) == (uint8_t)Block )
    return pThis_6FC;
  if ( pThis_6FC != nArg2 )
  {
LABEL_4:
    pThis_6FB = sub_4CE8A0(*((uint32_t *)this + 1787));
    if ( pThis_6FB == 0 )
    {
      LOBYTE(pThis_6FC) = off_77F3FC(aCriticalError_11, *((uint32_t *)this + 1787));
      return pThis_6FC;
    }
    if ( *((int *)this + 1788) > 0 )
    {
      for ( i = 0; ; ++i )
      {
        pThis_6FC2 = 16 * *((uint32_t *)this + 1788) + pThis_6FB;
        v8 = *(uint32_t *)(pThis_6FC2 + 744);
        if ( v8 == 0 || i >= (*(uint32_t *)(pThis_6FC2 + 748) - v8) >> 2 )
          break;
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 460))(
          this,
          *(uint32_t *)(*(uint32_t *)(pThis_6FC2 + 744) + 4 * i));
      }
    }
    if ( nArg2 > 0 )
    {
      v9 = 0;
      v10 = 16 * nArg2 + pThis_6FB;
      while ( 1 )
      {
        v11 = *(uint32_t *)(v10 + 744);
        if ( v11 == 0 || v9 >= (*(uint32_t *)(v10 + 748) - v11) >> 2 )
          break;
        (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 456))(this, *(uint32_t *)(v11 + 4 * v9++), 1);
      }
    }
  }
  if ( *(this + 7156) != 0 )
  {
    pThis_76A = *((void (/*thiscall*/ ****)(uint32_t, int))this + 1898);
    if ( pThis_76A != nullptr )
      (**pThis_76A)(pThis_76A, 1);
    pThis_769 = *((uint32_t *)this + 1897);
    *((uint32_t *)this + 1898) = 0;
    if ( pThis_769 != 0 )
    {
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_769 + 248))(pThis_769);
      for ( j = *(uint32_t *)(v14 + 4); j != *(uint32_t *)(v14 + 8); j += 124 )
      {
        (*(void (/*thiscall*/ **)(char *, char *, int))(*(uint32_t *)this + 696))(this, this + 6160, j + 4);
        (*(void (/*thiscall*/ **)(char *, char *, int))(*(uint32_t *)this + 1076))(this, this + 7212, j + 72);
      }
      pThis_7692 = *((uint32_t *)this + 1897);
      if ( pThis_7692 != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_7692 + 4))(pThis_7692, 1);
      *((uint32_t *)this + 1897) = 0;
    }
  }
  LOBYTE(pThis_6FC) = (uint8_t)Block;
  *((uint32_t *)this + 1788) = nArg2;
  *(this + 7156) = (char)Block;
  if ( (uint8_t)Block != 0 )
  {
    pThis_76B = sub_4B50F0(
            (uint32_t *)this + 1899,
            (uint32_t *)this + 1900,
            (uint32_t *)this + 1901,
            this + 7608,
            *((void **)this + 1787),
            nArg2,
            (int)this);
    pThis_6FB2 = *((uint32_t *)this + 1787);
    *((uint32_t *)this + 1898) = pThis_76B;
    pThis_6FC = sub_4B0080(pThis_6FB2, nArg2);
    v18 = (void *)pThis_6FC;
    if ( pThis_6FC != 0 )
    {
      pMem = (char *)operator new(0x544u);
      if ( pMem != nullptr )
        pObj = sub_4BA9E0(pMem, v18, 0);
      else
        pObj = nullptr;
      *((uint32_t *)this + 1897) = pObj;
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 256))(pObj);
      pThis_6FC = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1897) + 248))(*((uint32_t *)this + 1897));
      v21 = *(uint32_t **)(pThis_6FC + 4);
      Blocka = (uint32_t *)pThis_6FC;
      if ( v21 != *(uint32_t **)(pThis_6FC + 8) )
      {
        v22 = v21 + 18;
        do
        {
          sub_4B1C80(this + 6160, v22 - 17, this + 7212, v22);
          (*(void (/*thiscall*/ **)(char *, uint32_t, char *, uint32_t *))(*(uint32_t *)this + 692))(
            this,
            *v21,
            this + 6160,
            v22 - 17);
          (*(void (/*thiscall*/ **)(char *, uint32_t, char *, uint32_t *))(*(uint32_t *)this + 1072))(
            this,
            *v21,
            this + 7212,
            v22);
          pThis_6FC = Blocka[2];
          v21 += 31;
          v22 += 31;
        }
        while ( v21 != (uint32_t *)pThis_6FC );
      }
    }
  }
  return pThis_6FC;
}


// ------------------------------------------------------------
// 0x4BB1A0 sub_4BB1A0
// ------------------------------------------------------------
int /*stdcall*/ sub_4BB1A0(int (/*thiscall*/ ***uArg1)(uint32_t, int))
{
  int result; // eax

  if ( uArg1 != nullptr )
    return (**uArg1)(uArg1, 1);
  return result;
}



// ------------------------------------------------------------
// 0x4BB1C0 sub_4BB1C0
// ------------------------------------------------------------
char /*stdcall*/ sub_4BB1C0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4BB1C0(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BB200 sub_4BB200
// ------------------------------------------------------------
int /*thiscall*/ sub_4BB200(uint32_t *this, unsigned int uArg2)
{
  int fld_e86; // eax
  int fld_e862; // edx

  fld_e86 = *(this + 86);
  if ( fld_e86 == 0 || (*(this + 87) - fld_e86) / 28 <= uArg2 )
    return 0;
  fld_e862 = *(this + 86) + 28 * uArg2;
  if ( *(uint32_t *)(fld_e862 + 24) < 0x10u )
    return fld_e862 + 4;
  else
    return *(uint32_t *)(fld_e862 + 4);
}



// ------------------------------------------------------------
// 0x4BB260 sub_4BB260
// ------------------------------------------------------------
char /*thiscall*/ sub_4BB260(uint32_t *this, char *pszArg2, unsigned int *pDwArg3, int nArg4)
{
  uint32_t *fld_e68; // eax
  uint32_t *v5; // edi
  uint32_t *v6; // esi
  unsigned int i; // ebx
  int v8; // eax
  int *v9; // ecx
  int *v10; // eax
  int j; // eax
  char result; // al
  const char *psz; // edi

  fld_e68 = (uint32_t *)*(this + 68);
  v5 = (uint32_t *)*fld_e68;
  if ( (uint32_t *)*fld_e68 != fld_e68 )
  {
    do
    {
      v6 = *(uint32_t **)v5[10];
      for ( i = 0; ; ++i )
      {
        v8 = v6[13];
        if ( v8 == 0 || i >= (v6[14] - v8) / 12 )
          break;
        if ( sub_418DD0(v6, i) == nArg4 )
        {
          if ( v5[9] < 0x10u )
            psz = (const char *)(v5 + 4);
          else
            psz = (const char *)v5[4];
          strcpy(pszArg2, psz);
          *pDwArg3 = i;
          return result;
        }
      }
      if ( *((uint8_t *)v5 + 45) == 0 )
      {
        v9 = (int *)v5[2];
        if ( *((uint8_t *)v9 + 45) != 0 )
        {
          for ( j = v5[1]; *(uint8_t *)(j + 45) == 0; j = *(uint32_t *)(j + 4) )
          {
            if ( v5 != *(uint32_t **)(j + 8) )
              break;
            v5 = (uint32_t *)j;
          }
          v5 = (uint32_t *)j;
        }
        else
        {
          v10 = (int *)*v9;
          if ( *(uint8_t *)(*v9 + 45) == 0 )
          {
            do
            {
              v9 = v10;
              v10 = (int *)*v10;
            }
            while ( *((uint8_t *)v10 + 45) == 0 );
          }
          v5 = v9;
        }
      }
    }
    while ( v5 != (uint32_t *)*(this + 68) );
  }
  *pszArg2 = 0;
  return (char)pszArg2;
}



// ------------------------------------------------------------
// 0x4BB350 sub_4BB350
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BB350(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
{
  int fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  int fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  int fld_e15; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 20) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_433130(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4BB500 sub_4BB500
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4BB500(uint32_t *this, int ***uArg2, int **pDwArg3)
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  void **pExceptionObject; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 21) != 0 )
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v26 = 0;
    sub_401740(v20);
    pExceptionObject = &std::out_of_range::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 21) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 21) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);
  *((uint8_t *)pDwArg32 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 20) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_433130(v6);
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 20) != 1 || *(uint8_t *)(v16[2] + 20) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 20) == 1 )
            {
              *(uint8_t *)(*v16 + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_4296E0(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_4296E0(v6);
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 20) != 1 || *(uint8_t *)(*v16 + 20) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 20) == 1 )
            {
              *(uint8_t *)(v16[2] + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_433130(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4BB7C0 sub_4BB7C0
// ------------------------------------------------------------
char */*stdcall*/ sub_4BB7C0(char *ArgList, int nArg2)
{
  char *pMem; // eax
  char *v3; // edi
  char v4; // al
  size_t v6; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v8; // [esp+1Ch] [ebp-18h]
  unsigned int v9; // [esp+20h] [ebp-14h]
  int dword_796E502; // [esp+24h] [ebp-10h]
  int v11; // [esp+30h] [ebp-4h]

  dword_796E502 = dword_796E50;
  pMem = (char *)operator new(0x68u);
  v11 = 0;
  if ( pMem != nullptr )
    v3 = sub_419480(pMem, dword_79C0A4);
  else
    v3 = nullptr;
  v4 = v3[4];
  v11 = -1;
  if ( v4 == 0 )
    off_77F3FC("IMAGE INIT FAIL [%s]", ArgList);
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(&v6, ArgList, strlen(ArgList));  // 【std::string构造赋值】
  v11 = 1;
  sub_419550((int)v3, &v6, 0);
  if ( v9 >= 0x10 )
    j__free(Block);
  return v3;
}



// ------------------------------------------------------------
// 0x4BB8C0 sub_4BB8C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BB8C0(uint32_t *this, int pArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_4BB350(this, &uArg3, 1, fld_e1, (int)uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&uArg3);
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_4BB350(this, &uArg3, v13, fld_e1, (int)uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4BB980 sub_4BB980
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BB980(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_4BB350((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4BB350((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )
  {
    v8 = (uint32_t *)fld_4[2];
    if ( v8[3] < *pArg4 )
    {
      sub_4BB350((uint32_t *)this, uArg2, 0, v8, (int)pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0((int *)&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4BB8C0((uint32_t *)this, (int)v10, pArg42);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )
      sub_4BB350((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);
    else
      sub_4BB350((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )
      sub_4BB350((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);
    else
      sub_4BB350((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4BBAE0 sub_4BBAE0
// ------------------------------------------------------------
int **/*thiscall*/ sub_4BBAE0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_4BB1C0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_4BB500(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4BBBA0 sub_4BBBA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4BBBA0(int this, uint32_t *Src, unsigned int uArg3, int *pDwArg4)
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
      sub_41D5A0(this);  // 【模块切换辅助（map 容器/观察者清理/资源卸载链）】
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (fld_83 - (uint8_t *)Src) >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);
        sub_5DAF70(Src, v24, v29);
        return (unsigned int)sub_49A9D0(Src, &Srca[(uint32_t)Src], &pDwArg4);
      }
      else
      {
        sub_55E7F0(Src, (int)fld_83, &Src[v22 / 4u]);
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - (int)Src) >> 2), &pDwArg4);
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;
        return (unsigned int)sub_49A9D0(Src, (uint32_t *)(fld_84 - Srca), &pDwArg4);
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
      Srcb = 4 * (((int)Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);
      memcpy_0(v15, Src, 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2));
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



// ------------------------------------------------------------
// 0x4BBD80 sub_4BBD80 —— 部件路径解析（+44/+45 字符串槽；sub_4429F0/442AC0 分割）
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4BBD80(uint32_t *this, int ***uArg2, int **pDwArg3)
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  void **v15; // eax
  uint32_t *pThis3; // ecx
  uint32_t *v17; // eax
  uint32_t *Block2; // eax
  int v19; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v22; // [esp+34h] [ebp-34h] BYREF
  char v23; // [esp+38h] [ebp-30h]
  int v24; // [esp+48h] [ebp-20h]
  int v25; // [esp+4Ch] [ebp-1Ch]
  int v26; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v29; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 45) != 0 )
  {
    v25 = 15;
    v24 = 0;
    v23 = 0;
    sub_4015C0(&v22, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v29 = 0;
    sub_401740(pExceptionObject, &v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_40BEA0((int *)&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 45) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 45) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_6600D0(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v26 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v26 + 8) = sub_4429F0(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 45) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 45) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 44);
  *((uint8_t *)v5 + 44) = *((uint8_t *)pDwArg32 + 44);
  *((uint8_t *)pDwArg32 + 44) = v14;
LABEL_35:
  v15 = (void **)Block;
  if ( *((uint8_t *)Block + 44) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 44) != 1 )
          break;
        v17 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v17 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_442AC0(v6);
            v17 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v17 + 44) != 1 || *(uint8_t *)(v17[2] + 44) != 1 )
          {
            if ( *(uint8_t *)(v17[2] + 44) == 1 )
            {
              *(uint8_t *)(*v17 + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;
              sub_433290(v17);
              v17 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(v17[2] + 44) = 1;
            sub_442AC0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;
            *((uint8_t *)v6 + 44) = 0;
            sub_433290(v6);
            v17 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v17 + 45) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v17[2] + 44) != 1 || *(uint8_t *)(*v17 + 44) != 1 )
          {
            if ( *(uint8_t *)(*v17 + 44) == 1 )
            {
              *(uint8_t *)(v17[2] + 44) = 1;
              *((uint8_t *)v17 + 44) = 0;
              sub_442AC0(v17);
              v17 = (uint32_t *)*v6;
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);
            *((uint8_t *)v6 + 44) = 1;
            *(uint8_t *)(*v17 + 44) = 1;
            sub_433290(v6);
            break;
          }
        }
        *((uint8_t *)v17 + 44) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 44) = 1;
  }
  if ( (unsigned int)v15[9] >= 0x10 )
    j__free(v15[4]);
  Block2 = Block;
  *((uint32_t *)Block + 9) = 15;
  Block2[8] = 0;
  *((uint8_t *)Block2 + 16) = 0;
  j__free(Block2);
  v19 = pThis[2];
  if ( v19 != 0 )
    pThis[2] = v19 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4BC060 sub_4BC060
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC060(uint32_t *this, uint32_t *uArg2)
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);
  v3 = (int *)fld_e1[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( (unsigned int)v3[3] >= *uArg2 )
    {
      fld_e1 = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  if ( fld_e1 != (uint32_t *)*(this + 1) && *uArg2 >= fld_e1[3] )
    return (int)(fld_e1 + 4);
  v5[0] = *uArg2;
  v5[1] = 0;
  return *sub_4BB980((int)this, &uArg2, fld_e1, v5) + 16;
}



// ------------------------------------------------------------
// 0x4BC0E0 sub_4BC0E0
// ------------------------------------------------------------
char /*stdcall*/ sub_4BC0E0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 45);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4BC0E0(i[2]);
    i = (void **)*i;
    sub_5014C0(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 45);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BC130 sub_4BC130
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4BC130(int nArg1, int nArg2, int nArg3, size_t *pArg4, char pszArg5)
{
  uint32_t *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x30u);
  v7[4] = pMem;
  v7[8] = (void *)1;
  v7[3] = pMem;
  if ( pMem != nullptr )
    sub_40C300(pMem, nArg1, nArg2, nArg3, pArg4, pszArg5);
  return pMem;
}



// ------------------------------------------------------------
// 0x4BC1C0 sub_4BC1C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC1C0(int *this, int *pDwArg2)
{
  int result; // eax
  int *pDwArg22; // ebx
  int v5; // edi
  int v6; // edx
  int v7; // eax

  if ( *((uint8_t *)this + 288) == 0 )
    return 0;
  pDwArg22 = pDwArg2;
  result = sub_4BB200(this, (unsigned int)pDwArg2);
  v5 = result;
  if ( result != 0 )
  {
    pDwArg2 = (int *)sub_4BC060(this + 78, &pDwArg2);
    if ( timeGetTime() - *pDwArg2 >= 0x1B7740 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 28))(this, 0);
      v6 = *this;
      pDwArg2 = (int *)(*(this + 82) + 4 * (uint32_t)pDwArg22);
      v7 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 60))(this, v5);
      *pDwArg2 = v7;
      (*(void (/*thiscall*/ **)(int *, int))(*this + 28))(this, 1);
    }
    return *(uint32_t *)(*(this + 82) + 4 * (uint32_t)pDwArg22);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BC260 sub_4BC260
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4BC260(int **this, int *pDwArg2)
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = (int)*(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = ((int)*(this + 2) - fld_e1) >> 2;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= ((int)*(this + 3) - fld_e1) >> 2 )
    return sub_4BBBA0((int)this, *(this + 2), 1u, pDwArg2);
  fld_e22 = *(this + 2);
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = (int *)result;
  return result;
}



// ------------------------------------------------------------
// 0x4BC2B0 sub_4BC2B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BC2B0(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, size_t *pArg5)
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  uint32_t *fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  uint32_t *fld_e15; // [esp+70h] [ebp+14h]

  if ( (unsigned int)*(this + 2) >= 0x7FFFFFE )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_4BC130(*(this + 1), (int)pArg4, *(this + 1), pArg5, 0);
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = fld_e1 + 1;
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 44) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 44) != 0 )
        {
          if ( fld_e16 == (uint32_t *)v12[2] )
          {
            fld_e16 = (uint32_t *)*v10;
            sub_442AC0(*v10);
          }
          *(uint8_t *)(fld_e16[1] + 44) = 1;
          *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
          sub_433290(*(uint32_t *)(fld_e16[1] + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 44) != 0 )
      {
        if ( fld_e16 == (uint32_t *)*v12 )
        {
          fld_e16 = (uint32_t *)*v10;
          sub_433290(*v10);
        }
        *(uint8_t *)(fld_e16[1] + 44) = 1;
        *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
        sub_442AC0(*(uint32_t *)(fld_e16[1] + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 44) = 1;
      *(uint8_t *)(v14 + 44) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 44) = 0;
      fld_e16 = *(uint32_t **)(*v10 + 4);
LABEL_21:
      v10 = fld_e16 + 1;
      if ( *(uint8_t *)(fld_e16[1] + 44) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 44) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4BC460 sub_4BC460
// ------------------------------------------------------------
int **/*thiscall*/ sub_4BC460(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_4BC0E0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 45) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 45) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 45) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 45) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_4BBD80(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4BC520 sub_4BC520
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC520(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4BBAE0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4BC560 sub_4BC560
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC560(int *this, int pArg2, size_t *pArg3)
{
  int fld_e1; // ebx
  size_t *fld_e12; // esi
  char v5; // al
  size_t *pArg32; // edi
  size_t i; // esi
  unsigned int v8; // ecx
  const char *v9; // eax
  unsigned int v10; // edx
  const char *v11; // esi
  int nCmp; // eax
  bool v13; // sf
  unsigned int v14; // esi
  int v15; // eax
  size_t *fld_e122; // ebx
  const char *v18; // eax
  size_t *v19; // [esp+Ch] [ebp-14h]
  int *pThis; // [esp+18h] [ebp-8h]
  char v21; // [esp+1Ch] [ebp-4h]

  fld_e1 = *(uint32_t *)(*(this + 1) + 4);
  fld_e12 = (size_t *)*(this + 1);
  v5 = 1;
  pArg32 = pArg3;
  pThis = this;
  v21 = 1;
  if ( *(uint8_t *)(fld_e1 + 45) == 0 )
  {
    for ( i = pArg3[5]; ; i = pArg3[5] )
    {
      v8 = *(uint32_t *)(fld_e1 + 32);
      v19 = (size_t *)fld_e1;
      if ( *(uint32_t *)(fld_e1 + 36) < 0x10u )
        v9 = (const char *)(fld_e1 + 16);
      else
        v9 = *(const char **)(fld_e1 + 16);
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10 ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];
      nCmp = memcmp(v11, v9, v8);
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )
      {
LABEL_16:
        v14 = *(uint32_t *)(fld_e1 + 32);
        if ( v10 >= v14 )
          v15 = v10 != v14;
        else
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);
      if ( *(uint8_t *)(fld_e1 + 45) != 0 )
        break;
    }
    fld_e12 = v19;
    this = pThis;
  }
  fld_e122 = fld_e12;
  pArg3 = fld_e12;
  if ( v5 != 0 )
  {
    if ( fld_e12 == *(size_t **)*(this + 1) )
    {
      *(uint32_t *)pArg2 = *sub_4BC2B0(this, &pArg3, 1, fld_e12, pArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      return pArg2;
    }
    sub_501430(&pArg3);
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10 )
    v18 = (const char *)(pArg32 + 1);
  else
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )
  {
    *(uint32_t *)pArg2 = fld_e122;
    *(uint8_t *)(pArg2 + 4) = 0;
  }
  else
  {
    *(uint32_t *)pArg2 = *sub_4BC2B0(pThis, &pArg3, v21, fld_e12, pArg32);
    *(uint8_t *)(pArg2 + 4) = 1;
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x4BC6C0 sub_4BC6C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC6C0(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4BC460((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4BC700 sub_4BC700 —— ★部件路径 → 资源 id
//   sub_698250/sub_4BC560 查表 → sub_4BB8C0/sub_4BC260 提交；anim_parser [IMAGE] 的
//   帧+4 路径资源即由本函数换算。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC700(uint32_t *this, int pArg2)
{
  int pArg22; // edi
  int v4; // eax
  void *v5; // eax
  int v6; // eax
  DWORD Time; // eax
  int fld_e733; // ecx
  uint8_t v10[8]; // [esp+Ch] [ebp-264h] BYREF
  uint8_t v11[4]; // [esp+14h] [ebp-25Ch] BYREF
  void *v12; // [esp+18h] [ebp-258h]
  int v13; // [esp+28h] [ebp-248h]
  unsigned int v14; // [esp+2Ch] [ebp-244h]
  int fld_e732; // [esp+30h] [ebp-240h]
  uint8_t v16[4]; // [esp+34h] [ebp-23Ch] BYREF
  void *Block; // [esp+38h] [ebp-238h]
  int v18; // [esp+48h] [ebp-228h]
  unsigned int v19; // [esp+4Ch] [ebp-224h]
  int fld_e7322; // [esp+50h] [ebp-220h]
  int fld_e73; // [esp+54h] [ebp-21Ch]
  int fld_e7332; // [esp+58h] [ebp-218h] BYREF
  DWORD v23; // [esp+5Ch] [ebp-214h] BYREF
  uint8_t v24[512]; // [esp+60h] [ebp-210h] BYREF
  int dword_796E502; // [esp+260h] [ebp-10h]
  int v26; // [esp+26Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  pArg22 = pArg2;
  fld_e73 = *(this + 73);
  if ( *(uint32_t *)(pArg2 + 24) < 0x10u )
    v4 = pArg2 + 4;
  else
    v4 = *(uint32_t *)(pArg2 + 4);
  v5 = (void *)sub_698250(v24, v4);
  sub_4015C0(v5, strlen((const char *)v5));  // 【std::string构造赋值】
  v6 = *(uint32_t *)sub_5014F0(&pArg2, pArg22);
  if ( v6 != *(this + 76) )
    return *(uint32_t *)(v6 + 40);
  v14 = 15;
  v13 = 0;
  LOBYTE(v12) = 0;
  sub_4014D0((std::_String_base *)v11, pArg22, 0, -1);
  fld_e732 = *(this + 73);
  v26 = 0;
  v19 = 15;
  v18 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0((std::_String_base *)v16, v11, 0, -1);
  fld_e7322 = fld_e732;
  LOBYTE(v26) = 1;
  sub_4BC560(&fld_e7332, v16);
  if ( v19 >= 0x10 )
    j__free(Block);
  v19 = 15;
  v18 = 0;
  LOBYTE(Block) = 0;
  v26 = -1;
  if ( v14 >= 0x10 )
    j__free(v12);
  Time = timeGetTime();
  fld_e733 = *(this + 73);
  v23 = Time - 1800000;
  fld_e7332 = fld_e733;
  sub_4BB8C0(v10, &fld_e7332);
  v23 = 0;
  sub_4BC260(&v23);
  sub_416C40(pArg22);
  ++*(this + 73);
  return fld_e73;
}



// ============================================================
// §P 0x4BC900-0x4BCE50  部件集合管理
// ============================================================
// ------------------------------------------------------------
// 0x4BC900 sub_4BC900
// ------------------------------------------------------------
char */*thiscall*/ sub_4BC900(char *this, int nArg2, char pszArg3, int nArg4)
{
  int pThis_12C; // eax
  int pThis_138; // eax
  uint32_t *pThis_4C; // eax
  uint32_t *pThis_4F; // eax
  int pThis_56; // eax

  sub_438DB0(0, nArg2, nArg4);
  *(uint32_t *)this = &CNImageLoader::`vftable';
  pThis_12C = sub_433B80(this + 300);
  *((uint32_t *)this + 76) = pThis_12C;
  *(uint8_t *)(pThis_12C + 45) = 1;
  *(uint32_t *)(*((uint32_t *)this + 76) + 4) = *((uint32_t *)this + 76);
  **((uint32_t **)this + 76) = *((uint32_t *)this + 76);
  *(uint32_t *)(*((uint32_t *)this + 76) + 8) = *((uint32_t *)this + 76);
  *((uint32_t *)this + 77) = 0;
  pThis_138 = sub_433AC0(this + 312);
  *((uint32_t *)this + 79) = pThis_138;
  *(uint8_t *)(pThis_138 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)this + 79) + 4) = *((uint32_t *)this + 79);
  **((uint32_t **)this + 79) = *((uint32_t *)this + 79);
  *(uint32_t *)(*((uint32_t *)this + 79) + 8) = *((uint32_t *)this + 79);
  *((uint32_t *)this + 80) = 0;
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;
  *((uint32_t *)this + 84) = 0;
  *((uint32_t *)this + 86) = 0;
  *((uint32_t *)this + 87) = 0;
  *((uint32_t *)this + 88) = 0;
  *(this + 288) = pszArg3;
  *((uint32_t *)this + 73) = 0;
  *((uint32_t *)this + 74) = timeGetTime();
  sub_4BC0E0(*(void ***)(*((uint32_t *)this + 76) + 4));
  *(uint32_t *)(*((uint32_t *)this + 76) + 4) = *((uint32_t *)this + 76);
  pThis_4C = *((uint32_t **)this + 76);
  *((uint32_t *)this + 77) = 0;
  *pThis_4C = pThis_4C;
  *(uint32_t *)(*((uint32_t *)this + 76) + 8) = *((uint32_t *)this + 76);
  sub_4BB1C0(*(void ***)(*((uint32_t *)this + 79) + 4));
  *(uint32_t *)(*((uint32_t *)this + 79) + 4) = *((uint32_t *)this + 79);
  pThis_4F = *((uint32_t **)this + 79);
  *((uint32_t *)this + 80) = 0;
  *pThis_4F = pThis_4F;
  *(uint32_t *)(*((uint32_t *)this + 79) + 8) = *((uint32_t *)this + 79);
  pThis_56 = *((uint32_t *)this + 86);
  if ( pThis_56 != 0 )
  {
    sub_4166A0(pThis_56, *((uint32_t *)this + 87));
    j__free(*((void **)this + 86));
  }
  *((uint32_t *)this + 86) = 0;
  *((uint32_t *)this + 87) = 0;
  *((uint32_t *)this + 88) = 0;
  if ( *((uint32_t *)this + 82) != 0 )
    j__free(*((void **)this + 82));
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;
  *((uint32_t *)this + 84) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4BCA90 sub_4BCA90
// ------------------------------------------------------------
int /*thiscall*/ sub_4BCA90(void *this)
{
  uint32_t *pThis_4C; // eax
  uint32_t *pThis_4F; // ecx
  int pThis_56; // edx
  int pThis_562; // edx
  int *v7; // [esp-8h] [ebp-28h]
  int *pThis_4F2; // [esp-4h] [ebp-24h]
  int *pThis_57; // [esp+10h] [ebp-10h] BYREF
  int v10; // [esp+1Ch] [ebp-4h]

  *(uint32_t *)this = &CNImageLoader::`vftable';
  v10 = 4;
  sub_697BD0();
  sub_4BC0E0(*(void ***)(*((uint32_t *)this + 76) + 4));
  *(uint32_t *)(*((uint32_t *)this + 76) + 4) = *((uint32_t *)this + 76);
  pThis_4C = *((uint32_t **)this + 76);
  *((uint32_t *)this + 77) = 0;
  *pThis_4C = pThis_4C;
  *(uint32_t *)(*((uint32_t *)this + 76) + 8) = *((uint32_t *)this + 76);
  sub_4BB1C0(*(void ***)(*((uint32_t *)this + 79) + 4));
  *(uint32_t *)(*((uint32_t *)this + 79) + 4) = *((uint32_t *)this + 79);
  pThis_4F = *((uint32_t **)this + 79);
  *((uint32_t *)this + 80) = 0;
  *pThis_4F = pThis_4F;
  *(uint32_t *)(*((uint32_t *)this + 79) + 8) = *((uint32_t *)this + 79);
  pThis_56 = *((uint32_t *)this + 86);
  if ( pThis_56 != 0 )
  {
    pThis_57 = *((int **)this + 87);
    sub_4166A0(pThis_56, (int)pThis_57);
    j__free(*((void **)this + 86));
  }
  *((uint32_t *)this + 86) = 0;
  *((uint32_t *)this + 87) = 0;
  *((uint32_t *)this + 88) = 0;
  if ( *((uint32_t *)this + 82) != 0 )
    j__free(*((void **)this + 82));
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;
  *((uint32_t *)this + 84) = 0;
  pThis_562 = *((uint32_t *)this + 86);
  if ( pThis_562 != 0 )
  {
    pThis_57 = *((int **)this + 87);
    sub_4166A0(pThis_562, (int)pThis_57);
    j__free(*((void **)this + 86));
  }
  *((uint32_t *)this + 86) = 0;
  *((uint32_t *)this + 87) = 0;
  *((uint32_t *)this + 88) = 0;
  if ( *((uint32_t *)this + 82) != 0 )
    j__free(*((void **)this + 82));
  *((uint32_t *)this + 82) = 0;
  *((uint32_t *)this + 83) = 0;
  *((uint32_t *)this + 84) = 0;
  pThis_4F2 = *((int **)this + 79);
  v7 = (int *)*pThis_4F2;
  LOBYTE(v10) = 1;
  sub_4BBAE0((int ***)this + 78, &pThis_57, v7, pThis_4F2);
  j__free(*((void **)this + 79));
  *((uint32_t *)this + 79) = 0;
  *((uint32_t *)this + 80) = 0;
  LOBYTE(v10) = 0;
  sub_4BC460((int ***)this + 75, &pThis_57, **((int ***)this + 76), *((int **)this + 76));
  j__free(*((void **)this + 76));
  *((uint32_t *)this + 76) = 0;
  *((uint32_t *)this + 77) = 0;
  v10 = -1;
  return sub_438EA0(this);
}



// ------------------------------------------------------------
// 0x4BCC70 sub_4BCC70
// ------------------------------------------------------------
void */*thiscall*/ sub_4BCC70(void *Block, char pszArg2)
{
  sub_4BCA90(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x4BCCA0 sub_4BCCA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BCCA0(int this)
{
  *(uint32_t *)(this + 96) = 66;
  *(uint8_t *)(this + 284) = 0;
  *(uint8_t *)(this + 285) = 0;
  *(uint32_t *)(this + 308) = 4;
  *(uint32_t *)(this + 312) = 4;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 336) = timeGetTime();
  *(uint8_t *)(this + 340) = 0;
  *(uint8_t *)(this + 341) = 0;
  *(uint32_t *)(this + 344) = 0;
  *(uint32_t *)(this + 356) = -1;
  *(uint32_t *)(this + 360) = -1;
  *(uint32_t *)(this + 364) = 0;
  *(uint32_t *)(this + 368) = 0;
  *(uint32_t *)(this + 304) = 0;
  *(uint8_t *)(this + 286) = 0;
  *(uint32_t *)(this + 348) = timeGetTime();
  *(uint32_t *)(this + 352) = 4;
  *(uint32_t *)(this + 372) = -1;
  *(uint32_t *)(this + 376) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x4BCD50 sub_4BCD50
// ------------------------------------------------------------
int /*thiscall*/ sub_4BCD50(uint32_t *this)
{
  uint32_t *pMem; // eax
  int result; // eax

  pMem = operator new(0x14u);
  *(this + 73) = pMem;
  *pMem = 0;
  *(uint32_t *)(*(this + 73) + 4) = 0;
  *(uint32_t *)(*(this + 73) + 8) = 0;
  result = *(this + 73);
  *(uint32_t *)(result + 12) = 0;
  *(uint32_t *)(*(this + 73) + 16) = 0;
  *(this + 74) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4BCDA0 sub_4BCDA0
// ------------------------------------------------------------
int /*usercall*/ sub_4BCDA0@<eax>(int pArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 288) + 80))(*(uint32_t *)(pArg1 + 288)) != 0
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 288) + 80))(*(uint32_t *)(pArg1 + 288)) != *(uint32_t *)(pArg1 + 116) )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 288) + 80))(*(uint32_t *)(pArg1 + 288));
    sub_45FE80(v3, nArg2, 66, 0, pArg1, 0, 0);
  }
  return sub_498CA0((float *)pArg1, nArg2);
}



// ------------------------------------------------------------
// 0x4BCDF0 sub_4BCDF0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BCDF0(int *this)
{
  int result; // eax
  int v3; // edi
  int fld_e72; // ebx
  int fld_e722; // eax

  result = *(this + 72);
  if ( result != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);
    fld_e72 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 72) + 124))(*(this + 72));
    fld_e722 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 72) + 128))(*(this + 72));
    sub_498EC0(this, v3, fld_e72 - 1, fld_e722);
    return sub_498C40(this);
  }
  return result;
}



// ============================================================
// §Q 0x4BCE50-0x4BE170  摆摊驴 Donkey 族
// ============================================================
// ------------------------------------------------------------
// 0x4BCE50 sub_4BCE50 —— 摆摊驴部件装载（Character/Common/PrivateStore/Donkey/Store.img → +284 槽）
// ------------------------------------------------------------
char /*thiscall*/ sub_4BCE50(uint32_t *this, int nArg2, int nArg3)
{
  int v5; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // eax
  int dword_9A05682; // eax
  int nArg22; // edi
  int v12; // esi
  int v13; // ecx
  int nArg32; // ecx
  int v15; // eax
  int v16; // [esp-10h] [ebp-2Ch]
  int v17; // [esp-Ch] [ebp-28h]
  int v18; // [esp-8h] [ebp-24h]
  int v19; // [esp+8h] [ebp-14h]
  char v20; // [esp+Fh] [ebp-Dh]

  if ( *(this + 29) == 0 )
    return 0;
  v18 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v6 = sub_45E490(v5, v18);
  v17 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8);
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v8 = sub_45E4D0(v7, v16, v17, 1.0);
  v19 = v8;
  v20 = 1;
  if ( *((uint8_t *)this + 284) != 0 )
  {
    if ( (dword_9A056C & 1) != 0 )
    {
      dword_9A05682 = dword_9A0568;
    }
    else
    {
      dword_9A056C |= 1u;
      v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                       dword_8F84B8,
                       "Character/Common/PrivateStore/Donkey/Store.img");
      dword_9A05682 = sub_418DD0(v9, 0);
      dword_9A0568 = dword_9A05682;
    }
    nArg22 = nArg2;
    v12 = *(uint32_t *)(dword_9A05682 + 24);
    v13 = *(uint32_t *)(dword_9A05682 + 20) >> 1;
    if ( nArg2 >= v6 - v13 && nArg2 < v13 + v6 )
    {
      if ( nArg3 >= v19 - 3 * v12 && nArg3 < v19 - 2 * v12 )
        return v20;
      nArg22 = nArg2;
    }
    v20 = 1;
    if ( nArg22 < v6 - v13 )
      return 0;
    if ( nArg22 >= v6 + v13 )
      return 0;
    nArg32 = nArg3;
    if ( nArg3 < v19 - v12 / 2 )
      return 0;
    v15 = v19 + v12 / 2;
  }
  else
  {
    if ( nArg2 < v6 - 50 )
      return 0;
    if ( nArg2 >= v6 + 50 )
      return 0;
    nArg32 = nArg3;
    if ( nArg3 < v8 - 50 )
      return 0;
    v15 = v8 + 10;
  }
  if ( nArg32 >= v15 )
    return 0;
  return v20;
}



// ------------------------------------------------------------
// 0x4BCFC0 sub_4BCFC0
// ------------------------------------------------------------
char /*thiscall*/ sub_4BCFC0(uint8_t *this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  uint32_t *v6; // eax
  uint32_t *v7; // eax

  sub_49A600(this, pszArg2, nArg3, nArg4, nArg5);
  LOBYTE(v6) = pszArg2;
  if ( pszArg2 != 0 )
  {
    LOBYTE(v6) = *(this + 284);
    if ( (uint8_t)v6 != 0 )
    {
      if ( (dword_9A0574 & 1) != 0 )
      {
        v6 = (uint32_t *)dword_9A0570;
      }
      else
      {
        dword_9A0574 |= 1u;
        v7 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                         dword_8F84B8,
                         "Character/Common/PrivateStore/Donkey/Store.img");
        v6 = (uint32_t *)sub_418DD0(v7, 3u);
        dword_9A0570 = (int)v6;
      }
      if ( v6 != nullptr )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t *, int, unsigned int, int))(*v6 + 152))(
                       v6,
                       nArg3 - (v6[5] >> 1),
                       nArg4 - ((unsigned int)(3 * v6[6]) >> 1),
                       dword_79C0B0);
    }
  }
  return (char)v6;
}



// ------------------------------------------------------------
// 0x4BD090 sub_4BD090
// ------------------------------------------------------------
char /*thiscall*/ sub_4BD090(uint8_t *this)
{
  signed int Time; // eax
  int pThis_40; // eax
  int v5; // [esp-Ch] [ebp-10h]

  LOBYTE(Time) = *(this + 286);
  if ( (uint8_t)Time != 0 )
  {
    Time = timeGetTime();
    if ( *(this + 340) != 0 && Time > *((uint32_t *)this + 88) + *((uint32_t *)this + 87) )
    {
      *((uint32_t *)this + 87) = Time;
      srand(Time);
      *((uint32_t *)this + 88) = 1000 * (rand() % 4 + 8);
      v5 = sub_422E70(1337);
      pThis_40 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 64))(this);
      LOBYTE(Time) = sub_50EF20(pThis_40, v5, 0, 4000);
    }
  }
  return Time;
}



// ------------------------------------------------------------
// 0x4BD120 sub_4BD120
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD120(uint32_t *this)
{
  int fld_e72; // ecx
  int v3; // edi
  int v4; // ebx
  int result; // eax
  int v6; // ecx
  int fld_e722; // [esp+4h] [ebp-8h]
  int v8; // [esp+8h] [ebp-4h]

  fld_e72 = *(this + 72);
  if ( fld_e72 == 0 )
    return off_77F3FC("Donkey doesn't have owner.");
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e72 + 120))(fld_e72);
  fld_e722 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 72) + 124))(*(this + 72));
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  result = v3 - v4;
  v6 = abs32(v3 - v4);
  if ( v6 >= 60 || (result = abs32(fld_e722 - v8)) >= 60 )
  {
    *(this + 79) = v3;
    *(this + 80) = fld_e722;
    if ( v6 > 180 )
      *(this + 83) = 4;
  }
  else
  {
    *(this + 80) = v8;
    result = 4;
    *(this + 79) = v4;
    *(this + 77) = 4;
    *(this + 78) = 4;
    *(this + 83) = 3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BD1F0 sub_4BD1F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD1F0(int *this)
{
  int fld_e81; // eax
  int fld_e79; // edi
  bool fld_e812; // cc
  int v5; // edi
  int v6; // eax
  int fld_e80; // edi
  bool fld_e82; // cc
  int v9; // edi
  int v10; // eax
  int fld_e78; // ecx
  int v12; // edi
  int result; // eax
  int fld_e792; // [esp+0h] [ebp-10h]
  int v15; // [esp+4h] [ebp-Ch]
  int v16; // [esp+8h] [ebp-8h]
  int v17; // [esp+Ch] [ebp-4h]

  fld_e81 = *(this + 81);
  fld_e79 = *(this + 79);
  fld_e812 = fld_e81 <= fld_e79;
  if ( fld_e81 < fld_e79 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e79 && *(this + 77) == 1 )
      goto LABEL_4;
    fld_e812 = *(this + 81) <= fld_e79;
  }
  if ( !fld_e812 && (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < *(this + 79) && *(this + 77) == 0 )
  {
LABEL_4:
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v6);
    fld_e792 = *(this + 79);
    (*(void (/*thiscall*/ **)(int *))(v5 + 112))(this);
LABEL_5:
    *(this + 77) = 4;
    goto LABEL_6;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) >= *(this + 79) )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= *(this + 79) )
      goto LABEL_5;
    *(this + 77) = 0;
  }
  else
  {
    *(this + 77) = 1;
  }
LABEL_6:
  fld_e80 = *(this + 80);
  fld_e82 = *(this + 82) <= fld_e80;
  if ( *(this + 82) < fld_e80 )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > fld_e80 && *(this + 78) == 3 )
      goto LABEL_9;
    fld_e82 = *(this + 82) <= fld_e80;
  }
  if ( !fld_e82 && (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) < *(this + 80) && *(this + 78) == 2 )
  {
LABEL_9:
    v9 = *this;
    (*(void (/*thiscall*/ **)(int *, int, int))(*this + 128))(this, fld_e792, v15);
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    (*(void (/*thiscall*/ **)(int *, int))(v9 + 112))(this, v10);
LABEL_10:
    *(this + 78) = 4;
    goto LABEL_11;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) >= *(this + 80) )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= *(this + 80) )
      goto LABEL_10;
    *(this + 78) = 2;
  }
  else
  {
    *(this + 78) = 3;
  }
LABEL_11:
  fld_e78 = *(this + 78);
  v12 = fld_e78 != 4 ? 112 : 134;
  result = *(this + 77);
  v17 = v12;
  v16 = result != 4 ? 73 : 90;
  if ( *(this + 83) == 4 )
  {
    v12 = 268;
    v17 = 268;
  }
  if ( result == 4 )
  {
    v17 = 0;
  }
  else if ( result == 0 )
  {
    v17 = -v12;
  }
  if ( fld_e78 == 4 )
  {
    v16 = 0;
  }
  else if ( fld_e78 == 2 )
  {
    v16 = -(result != 4 ? 73 : 90);
  }
  *(float *)(*(this + 28) + 16) = (float)v17;
  *(float *)(*(this + 28) + 20) = (float)v16;
  return result;
}


// ------------------------------------------------------------
// 0x4BD440 sub_4BD440
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD440(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  *(this + 89) = nArg2;
  *(this + 90) = nArg3;
  *(this + 91) = nArg4;
  *(this + 92) = nArg5;
  return nArg4;
}



// ------------------------------------------------------------
// 0x4BD470 sub_4BD470
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD470(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3, uint32_t *uArg4, uint32_t *uArg5)
{
  int result; // eax

  *uArg2 = *(this + 89);
  *uArg3 = *(this + 90);
  *uArg4 = *(this + 91);
  result = *(this + 92);
  *uArg5 = result;
  return result;
}



// ------------------------------------------------------------
// 0x4BD4B0 sub_4BD4B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4BD4B0(uint8_t *this)
{
  *(this + 284) = 1;
  *(this + 285) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x4BD500 sub_4BD500
// ------------------------------------------------------------
char /*thiscall*/ sub_4BD500(uint8_t *this, char pszArg2)
{
  *(this + 286) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4BD510 sub_4BD510
// ------------------------------------------------------------
char /*thiscall*/ sub_4BD510(int this, int nArg2, int nArg3, int nArg4)
{
  int v4; // eax
  int v5; // edi
  int *v6; // eax
  char result; // al
  int v9; // [esp+Ch] [ebp-4h]

  v4 = *(uint32_t *)(dword_8F7A24 + 20);
  v5 = *(uint32_t *)(v4 + 100);
  v6 = *(int **)(v4 + 104);
  if ( v6 != nullptr )
    v9 = *v6;
  else
    v9 = -1;
  sub_498EC0((uint32_t *)this, nArg2, nArg3 - 1, nArg4);
  result = *(uint8_t *)(this + 284);
  *(uint32_t *)(this + 372) = v5;
  *(uint32_t *)(this + 376) = v9;
  if ( result != 0 )
  {
    *(uint32_t *)(this + 364) = nArg2;
    *(uint32_t *)(this + 368) = nArg3;
    return nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BD5E0 sub_4BD5E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD5E0(uint32_t *this, int nArg2)
{
  int v3; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int result; // eax

  v3 = *this;
  *(this + 72) = nArg2;
  v5 = (*(int (**)(void))(*(uint32_t *)nArg2 + 128))();
  v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 124))(nArg2, v5);
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v6);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 112))(this, v7);
  *((uint8_t *)this + 286) = *(uint8_t *)(*(this + 72) + 652);
  return result;
}



// ------------------------------------------------------------
// 0x4BD630 sub_4BD630
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_4BD630(uint32_t *this)
{
  int fld_e76; // eax

  fld_e76 = *(this + 76);
  if ( fld_e76 == 0 )
    return szPassword;
  if ( *(uint32_t *)(fld_e76 + 24) < 0x10u )
    return (const CHAR *)(fld_e76 + 4);
  return *(const CHAR **)(fld_e76 + 4);
}



// ------------------------------------------------------------
// 0x4BD650 sub_4BD650
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD650(size_t *this, int pArg2, unsigned int uArg3, unsigned int uArg4)
{
  *(uint32_t *)(pArg2 + 20) = 0;
  *(uint32_t *)(pArg2 + 24) = 15;
  *(uint8_t *)(pArg2 + 4) = 0;
  sub_4014D0((size_t *)pArg2, this, uArg3, uArg4);
  return pArg2;
}



// ------------------------------------------------------------
// 0x4BD690 sub_4BD690
// ------------------------------------------------------------
void /*thiscall*/ sub_4BD690(size_t **this, char *Block)
{
  size_t *fld_e76; // ecx
  void *pMem; // eax
  int v5; // eax

  if ( Block != nullptr )
  {
    fld_e76 = *(this + 76);
    if ( fld_e76 != nullptr )
    {
      sub_4015C0(fld_e76, Block, strlen(Block));  // 【std::string构造赋值】
    }
    else
    {
      pMem = operator new(0x1Cu);
      if ( pMem != nullptr )
        v5 = sub_401710((int)pMem, Block);
      else
        v5 = 0;
      *(this + 76) = (size_t *)v5;
    }
  }
}



// ------------------------------------------------------------
// 0x4BD720 sub_4BD720 —— 摆摊驴整体装配（+284/+285/+286/+288 槽；+44 槽 → sub_491530/491630 图层）
// ------------------------------------------------------------
void /*thiscall*/ sub_4BD720(int this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int v6; // edx
  uint32_t *v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // eax
  void *v11; // eax
  uint32_t *fld_130; // eax
  unsigned int v13; // ecx
  uint32_t *v14; // eax
  int nArg32; // ebx
  int v16; // eax
  int fld_1302; // ecx
  int v18; // ecx
  uint32_t *v19; // eax
  int v20; // esi
  uint32_t *v21; // eax
  unsigned int v22; // eax
  uint32_t *v23; // edx
  int v24; // eax
  uint32_t *v25; // eax
  int v26; // eax
  uint32_t *v27; // edx
  int fld_120; // eax
  int v29; // eax
  int v30; // esi
  int v31; // eax
  char *psz; // eax
  const char *psz2; // esi
  void **Block2; // eax
  unsigned int v35; // eax
  void **Block3; // edx
  int v37; // ebx
  void *v38; // ecx
  int v39; // edx
  unsigned int v40; // eax
  uint32_t *v41; // ecx
  uint8_t v42[4]; // [esp+Ch] [ebp-88h] BYREF
  uint32_t v43[5]; // [esp+10h] [ebp-84h] BYREF
  unsigned int v44; // [esp+24h] [ebp-70h]
  uint8_t v45[4]; // [esp+28h] [ebp-6Ch] BYREF
  uint32_t v46[5]; // [esp+2Ch] [ebp-68h] BYREF
  unsigned int v47; // [esp+40h] [ebp-54h]
  uint32_t v48[5]; // [esp+48h] [ebp-4Ch] BYREF
  unsigned int v49; // [esp+5Ch] [ebp-38h]
  uint8_t v50[4]; // [esp+60h] [ebp-34h] BYREF
  void *Block[5]; // [esp+64h] [ebp-30h] BYREF
  unsigned int v52; // [esp+78h] [ebp-1Ch]
  char Buffer; // [esp+7Ch] [ebp-18h] BYREF
  int v54; // [esp+7Dh] [ebp-17h]
  char v55; // [esp+81h] [ebp-13h]
  int dword_796E502; // [esp+84h] [ebp-10h]
  int v57; // [esp+90h] [ebp-4h]
  int v58; // [esp+9Ch] [ebp+8h]

  dword_796E502 = dword_796E50;
  nullsub_2(nArg2, nArg3, nArg4, nArg5);
  if ( (uint8_t)nArg2 == 0 )
    return;
  if ( *(uint8_t *)(this + 284) != 0 )
  {
    if ( (dword_9A0580 & 1) != 0 )
    {
      v7 = (uint32_t *)dword_9A057C;
    }
    else
    {
      dword_9A0580 |= 1u;
      v6 = *(uint32_t *)dword_8F84B8;
      v57 = 0;
      (*(void (/*thiscall*/ **)(int, const char *))(v6 + 60))(
        dword_8F84B8,
        "Character/Common/PrivateStore/Donkey/Store.img");
      v7 = (uint32_t *)sub_418DD0(0);
      dword_9A057C = (int)v7;
      v57 = -1;
    }
    v8 = nArg4 - 3 * v7[6];
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int, int, uint32_t, int, int, int))(*v7 + 128))(
      v7,
      nArg3 - (v7[5] >> 1),
      v8,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      2030043135,
      1333788672,
      1333788672);
    v9 = 0;
    if ( *(uint8_t *)(*((uint32_t *)dword_8F8528 + 625) + 44) != 0 )
      v9 = sub_45E870(pt.x, pt.y, 1);
    if ( this == v9 )
    {
      if ( (dword_9A0580 & 2) == 0 )
      {
        dword_9A0580 |= 2u;
        v10 = *(uint32_t *)dword_8F84B8;
        v57 = 1;
        (*(void (/*thiscall*/ **)(int, const char *))(v10 + 60))(
          dword_8F84B8,
          "Character/Common/PrivateStore/Donkey/Store.img");
        dword_9A0578 = sub_418DD0(1);
        v57 = -1;
      }
      sub_491530(2, 0);
      (*(void (/*stdcall*/ **)(int, int, int))(*(uint32_t *)dword_9A0578 + 152))(
        nArg3 - (*(uint32_t *)(dword_9A0578 + 20) >> 1),
        v8,
        dword_79C0B0);
      sub_491630(2);
    }
    if ( *(uint8_t *)(this + 285) != 0 )
    {
      v11 = (void *)sub_422E70(1335);
      sub_4BD690(v11);
    }
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC);
    fld_130 = *(uint32_t **)(this + 304);
    v58 = v8 + 10;
    if ( fld_130 != nullptr )
    {
      v13 = fld_130[6];
      if ( fld_130[5] < 0x15u )
      {
        if ( v13 < 0x10 )
          v14 = fld_130 + 1;
        else
          v14 = (uint32_t *)fld_130[1];
        nArg32 = nArg3;
        v16 = nArg3 - (sub_4176A0(v14) >> 1);
        fld_1302 = *(uint32_t *)(this + 304);
        if ( *(uint32_t *)(fld_1302 + 24) < 0x10u )
          v18 = fld_1302 + 4;
        else
          v18 = *(uint32_t *)(fld_1302 + 4);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v16,
          v8 + 18,
          -16731649,
          v18);
LABEL_36:
        fld_120 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 288) + 52))(*(uint32_t *)(this + 288));
        v29 = sub_429830(fld_120);
        v54 = 0;
        v55 = 0;
        Block[4] = nullptr;
        LOBYTE(Block[0]) = 0;
        v30 = v29;
        Buffer = 0;
        v52 = 15;
        sub_4015C0((void *)"Lv.", 3u);  // 【std::string构造赋值】
        v57 = 4;
        v31 = sub_41A5E0(v30 + 53);
        psz = _itoa(v31, &Buffer, 10);
        sub_4022F0((std::_String_base *)v50, psz, strlen(psz));
        sub_4022F0((std::_String_base *)v50, " ", 1);
        if ( *(uint32_t *)(v30 + 40) < 0x10u )
          psz2 = (const char *)(v30 + 20);
        else
          psz2 = *(const char **)(v30 + 20);
        sub_4022F0((std::_String_base *)v50, psz2, strlen(psz2));
        Block2 = (void **)Block[0];
        if ( v52 < 0x10 )
          Block2 = Block;
        v35 = sub_4176A0(Block2);
        Block3 = (void **)Block[0];
        v37 = nArg32 - (v35 >> 1);
        if ( v52 < 0x10 )
          Block3 = Block;
        (*(void (/*cdecl*/ **)(int, int, int, int, void **))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v37,
          v58 + 32,
          -1,
          Block3);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        if ( v52 >= 0x10 )
        {
          v38 = Block[0];
LABEL_49:
          j__free(v38);
          return;
        }
        return;
      }
      if ( v13 < 0x10 )
        v19 = fld_130 + 1;
      else
        v19 = (uint32_t *)fld_130[1];
      v20 = sub_5515A0(v19, 20);
      sub_4BD650(v42, 0, v20);
      v57 = 2;
      sub_4BD650(v45, v20, -1);
      v21 = (uint32_t *)v43[0];
      LOBYTE(v57) = 3;
      if ( v44 < 0x10 )
        v21 = v43;
      v22 = sub_4176A0(v21);
      v23 = (uint32_t *)v43[0];
      v24 = nArg3 - (v22 >> 1);
      if ( v44 < 0x10 )
        v23 = v43;
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v24,
        v58,
        -16731649,
        v23);
      v25 = (uint32_t *)v46[0];
      if ( v47 < 0x10 )
        v25 = v46;
      v26 = nArg3 - (sub_4176A0(v25) >> 1);
      v27 = (uint32_t *)v46[0];
      if ( v47 < 0x10 )
        v27 = v46;
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
        dword_79C0B0,
        v26,
        v58 + 16,
        -16731649,
        v27);
      sub_501490(v45);
      v57 = -1;
      sub_501490(v42);
    }
    nArg32 = nArg3;
    goto LABEL_36;
  }
  v49 = 15;
  v48[4] = 0;
  LOBYTE(v48[0]) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  v39 = *(uint32_t *)dword_79C0B0;
  v57 = 5;
  (*(void (/*thiscall*/ **)(int, char *))(v39 + 72))(dword_79C0B0, &byte_77F8FC);
  v40 = sub_4176A0(v48);
  v41 = (uint32_t *)v48[0];
  if ( v49 < 0x10 )
    v41 = v48;
  (*(void (/*cdecl*/ **)(int, unsigned int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(
    dword_79C0B0,
    nArg3 - (v40 >> 1),
    nArg4 - 26,
    -6567706,
    v41);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
  if ( v49 >= 0x10 )
  {
    v38 = (void *)v48[0];
    goto LABEL_49;
  }
}


// ------------------------------------------------------------
// 0x4BDC40 sub_4BDC40
// ------------------------------------------------------------
void /*thiscall*/ sub_4BDC40(void **this)
{
  int i; // esi
  int fld_e73; // eax
  int v4; // edi

  for ( i = 0; i < 20; i += 4 )
  {
    fld_e73 = (int)*(this + 73);
    v4 = *(uint32_t *)(i + fld_e73);
    if ( v4 != 0 )
    {
      sub_42AF90(*(void ***)(i + fld_e73));
      sub_657740(v4, 228);
    }
    *(uint32_t *)((char *)*(this + 73) + i) = 0;
  }
  j_j__free(*(this + 73));
}



// ------------------------------------------------------------
// 0x4BDCA0 sub_4BDCA0 —— 摆摊驴动画装配
//   Donkey_Stay/Eat/Bite/Walk/Run.ani → +40 槽 sub_4924C0；
//   失败 "Donkey Ani was not Created"。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BDCA0(int *this)
{
  int *fld_e734; // eax
  uint32_t *fld_e73; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int *fld_e732; // eax
  DWORD Time; // ebx
  uint32_t *fld_e733; // ecx
  int v12; // eax
  int fld_e30; // edi
  int v14; // ecx
  int fld_e302; // ecx
  int fld_e86; // eax
  int fld_e735; // ecx
  int v18; // edx

  LOBYTE(fld_e734) = *((uint8_t *)this + 284);
  if ( (uint8_t)fld_e734 == 0 )
  {
    fld_e73 = (uint32_t *)*(this + 73);
    if ( fld_e73 == nullptr )
    {
      LOBYTE(fld_e734) = off_77F3FC("Donkey Ani was not Created");
      return (char)fld_e734;
    }
    if ( *fld_e73 == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v4 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Stay.ani", 1);
      else
        v4 = 0;
      *(uint32_t *)*(this + 73) = v4;
    }
    if ( *(uint32_t *)(*(this + 73) + 4) == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v5 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Eat.ani", 1);
      else
        v5 = 0;
      *(uint32_t *)(*(this + 73) + 4) = v5;
    }
    if ( *(uint32_t *)(*(this + 73) + 8) == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v6 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Bite.ani", 1);
      else
        v6 = 0;
      *(uint32_t *)(*(this + 73) + 8) = v6;
    }
    if ( *(uint32_t *)(*(this + 73) + 12) == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v7 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Walk.ani", 1);
      else
        v7 = 0;
      *(uint32_t *)(*(this + 73) + 12) = v7;
    }
    if ( *(uint32_t *)(*(this + 73) + 16) == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v8 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Run.ani", 1);
      else
        v8 = 0;
      *(uint32_t *)(*(this + 73) + 16) = v8;
    }
    if ( *(this + 40) < 0 )
    {
      fld_e732 = (int *)sub_4924C0(*(int **)*(this + 73), 0);
      *(this + 40) = sub_4918E0(fld_e732, 2);
    }
    Time = timeGetTime();
    if ( *(this + 77) == 4 && *(this + 78) == 4 )
    {
      if ( *((uint8_t *)this + 340) == 0 )
      {
        fld_e733 = (uint32_t *)*(this + 73);
        v12 = *this;
        *((uint8_t *)this + 340) = 1;
        *(this + 84) = Time;
        LOBYTE(fld_e734) = (*(int (/*thiscall*/ **)(int *, uint32_t))(v12 + 196))(this, *fld_e733);
        return (char)fld_e734;
      }
      LOBYTE(fld_e734) = *((uint8_t *)this + 341);
      if ( (uint8_t)fld_e734 != 0 )
      {
        fld_e30 = *(this + 30);
        fld_e734 = (int *)(sub_42FC90(fld_e30) - 1);
        if ( *(int **)(fld_e30 + 148) != fld_e734 )
          return (char)fld_e734;
        fld_e734 = (int *)*(this + 73);
        v14 = *fld_e734;
        if ( fld_e30 == *fld_e734 )
        {
          (*(void (/*thiscall*/ **)(int *, int))(*this + 196))(this, fld_e734[1]);
          fld_e302 = *(this + 30);
          goto LABEL_38;
        }
        if ( fld_e30 == fld_e734[1] && *(uint8_t *)(fld_e30 + 170) != 0 )
        {
          (*(void (/*thiscall*/ **)(int *, int))(*this + 196))(this, fld_e734[2]);
          sub_4926A0(*(this + 30));
          fld_e734 = (int *)(rand() % 4 + 1);
          *(this + 86) = (int)fld_e734;
          return (char)fld_e734;
        }
        if ( fld_e30 == fld_e734[2] )
        {
          LOBYTE(fld_e734) = *(uint8_t *)(fld_e30 + 170);
          if ( (uint8_t)fld_e734 != 0 )
          {
            fld_e86 = *(this + 86);
            if ( fld_e86 == 0 )
            {
              (*(void (/*thiscall*/ **)(int *, int))(*this + 196))(this, v14);
              LOBYTE(fld_e734) = sub_4926A0(*(this + 30));
              *(this + 84) = Time;
              *((uint8_t *)this + 341) = 0;
              return (char)fld_e734;
            }
            *(this + 86) = fld_e86 - 1;
            fld_e302 = fld_e30;
LABEL_38:
            LOBYTE(fld_e734) = sub_4926A0(fld_e302);
          }
        }
      }
      else if ( (int)(Time - *(this + 84)) > 6000 )
      {
        *((uint8_t *)this + 341) = 1;
      }
    }
    else
    {
      fld_e735 = *(this + 73);
      if ( *(this + 83) == 4 )
        v18 = *(uint32_t *)(fld_e735 + 16);
      else
        v18 = *(uint32_t *)(fld_e735 + 12);
      LOBYTE(fld_e734) = (*(int (/*thiscall*/ **)(int *, int))(*this + 196))(this, v18);
      *((uint8_t *)this + 340) = 0;
    }
  }
  return (char)fld_e734;
}


// ------------------------------------------------------------
// 0x4BE040 sub_4BE040 —— 摆摊驴 Store.ani 装配（+284）
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE040(uint8_t *this)
{
  char result; // al
  int v3; // eax

  result = *(this + 284);
  if ( result != 0 )
  {
    if ( *((uint32_t *)this + 74) == 0 )
    {
      if ( sub_42FCB0(228) != 0 )
        v3 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Store.ani", 1);
      else
        v3 = 0;
      *((uint32_t *)this + 74) = v3;
    }
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 74));
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE0D0 sub_4BE0D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE0D0(int *this)
{
  int v2; // eax
  int fld_e77; // eax
  int fld_e772; // edi
  int v5; // eax
  int v6; // edx

  nullsub_3(this);
  if ( *((uint8_t *)this + 284) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t))(*this + 112))(this, *(this + 91), *(this + 92), 0);
    LOBYTE(v2) = sub_4BE040(this);
  }
  else
  {
    fld_e77 = *(this + 77);
    if ( fld_e77 != 4 )
    {
      fld_e772 = *(this + 77);
      if ( fld_e77 != (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) )
        (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, fld_e772);
    }
    sub_4BD120(this);
    sub_4BD1F0(this);
    sub_4BDCA0(this);
    sub_4BD090(this);
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v6 = *this;
    *(this + 81) = v5;
    v2 = (*(int (/*thiscall*/ **)(int *))(v6 + 124))(this);
    *(this + 82) = v2;
  }
  return v2;
}



// ============================================================
// §R 0x4BE170-0x4BFFA0  杂项/容器收尾
// ============================================================
// ------------------------------------------------------------
// 0x4BE170 sub_4BE170
// ------------------------------------------------------------
int sub_4BE170()
{
  return dword_9A0584;
}



// ------------------------------------------------------------
// 0x4BE180 sub_4BE180
// ------------------------------------------------------------
int /*cdecl*/ sub_4BE180(int nArg1)
{
  dword_9A0584 = nArg1;
  return nArg1;
}



// ------------------------------------------------------------
// 0x4BE190 sub_4BE190
// ------------------------------------------------------------
unsigned int */*thiscall*/ sub_4BE190(unsigned int *this)
{
  unsigned int *pThis_2; // esi

  pThis_2 = this + 2;
  if ( sub_40BF00((std::_String_base *)(this + 2), 0, *(this + 7), szPassword, 0) == 0 )
    return nullptr;
  if ( pThis_2[6] < 0x10 )
    return pThis_2 + 1;
  return (unsigned int *)pThis_2[1];
}



// ------------------------------------------------------------
// 0x4BE1C0 sub_4BE1C0
// ------------------------------------------------------------
void /*thiscall*/ sub_4BE1C0(uint32_t *this)
{
  *this = &HttpFileCallBack::`vftable';
}



// ------------------------------------------------------------
// 0x4BE1D0 sub_4BE1D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE1D0(uint8_t *this)
{
  return *(this + 12);
}



// ------------------------------------------------------------
// 0x4BE1E0 sub_4BE1E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE1E0(uint8_t *this, char pszArg2)
{
  *(this + 12) = pszArg2;
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4BE1F0 sub_4BE1F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BE1F0(uint32_t *this)
{
  int result; // eax

  if ( *(this + 1) == 2 )
  {
    result = off_77F3FC("CNRDGuildInfo::on_stop - emblem download failed. guild = %d", *(this + 2));
    *(this + 1) = 6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE220 sub_4BE220
// ------------------------------------------------------------
int /*thiscall*/ sub_4BE220(uint32_t *this)
{
  int result; // eax
  char Buffer[1024]; // [esp+4h] [ebp-404h] BYREF
  int dword_796E502; // [esp+404h] [ebp-4h]

  result = dword_796E50;
  dword_796E502 = dword_796E50;
  if ( *(this + 1) == 1 )
  {
    sprintf(
      Buffer,
      "http://guildem.d-fighter.com:8080/guild/%d/%d/%d/%d.img",
      *(this + 2) & 0x1F,
      (*(this + 2) >> 5) % 251,
      *(this + 2) / 0x1F60u,
      *(this + 2));
    off_77F3FC("CNRDGuildInfo::download_emblem - %s", Buffer);
    result = sub_4F4710(Buffer, (int)this, 0);
    *(this + 1) = 2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE2B0 sub_4BE2B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BE2B0(int this, uint8_t uArg2)
{
  int result; // eax

  if ( uArg2 > 2u )
  {
    result = off_77F3FC("CNRDGuildInfo::on_receive_guild_info - guild level is too big. %d", uArg2);
    *(uint32_t *)(this + 4) = 6;
  }
  *(uint8_t *)(this + 12) = uArg2;
  if ( uArg2 != 0 )
  {
    *(uint32_t *)(this + 4) = 1;
    return sub_4BE220((uint32_t *)this);
  }
  else
  {
    *(uint32_t *)(this + 4) = 6;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE300 sub_4BE300 —— 技能图标装载（+48 槽；sub_419480/419550）
// ------------------------------------------------------------
int /*thiscall*/ sub_4BE300(int this)
{
  int v2; // edi
  uint32_t *fld_10; // ecx
  char *pMem; // eax
  char *v5; // eax
  void (/*thiscall*/ ***pThis_10)(uint32_t, int); // ecx
  const CHAR *pThis_50; // eax

  v2 = 0;
  switch ( *(uint32_t *)(this + 4) )
  {
    case 3:
      if ( (unsigned int)sub_699000(this + 20) > 0x7D0 )  // 【clock_now(clk)】
      {
LABEL_22:
        *(uint32_t *)(this + 4) = 1;
        sub_4BE220((uint32_t *)this);
      }
      break;
    case 4:
      if ( (unsigned int)sub_699000(this + 48) > 0x3E8 )  // 【clock_now(clk)】
      {
        *(uint32_t *)(this + 4) = 5;
        return 0;
      }
      break;
    case 5:
      fld_10 = *(uint32_t **)(this + 16);
      if ( fld_10 == nullptr )
      {
        pMem = (char *)operator new(0x68u);
        if ( pMem != nullptr )
          v5 = sub_419480(pMem, dword_79C0A4);
        else
          v5 = nullptr;
        *(uint32_t *)(this + 16) = v5;
        if ( sub_419550((int)v5, (size_t *)(this + 76), 1u) == 0 )
        {
          off_77F3FC("CNRDGuildInfo::get_emblem() - emblem load failed");
          *(uint32_t *)(this + 4) = 6;
          return 0;
        }
        return v2;
      }
      v2 = sub_418DD0(fld_10, 0);
      if ( v2 == sub_419F00() )
      {
        if ( *(uint8_t *)(this + 13) >= 2u )
          return 0;
        pThis_10 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 16);
        if ( pThis_10 != nullptr )
          (**pThis_10)(pThis_10, 1);
        *(uint32_t *)(this + 16) = 0;
        if ( *(uint32_t *)(this + 100) < 0x10u )
          pThis_50 = (const CHAR *)(this + 80);
        else
          pThis_50 = *(const CHAR **)(this + 80);
        DeleteFileA(pThis_50);
        ++*(uint8_t *)(this + 13);
        v2 = 0;
        goto LABEL_22;
      }
      break;
    default:
      break;
  }
  return v2;
}



// ------------------------------------------------------------
// 0x4BE470 sub_4BE470
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE470(int this)
{
  int fld_4; // eax
  void (/*thiscall*/ ***pThis_10)(uint32_t, int); // ecx
  const CHAR *pThis_50; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 == 5 || fld_4 == 6 || fld_4 == 4 )
  {
    LOBYTE(fld_4) = *(uint8_t *)(this + 12);
    if ( (uint8_t)fld_4 != 0 )
    {
      pThis_10 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 16);
      if ( pThis_10 != nullptr )
        (**pThis_10)(pThis_10, 1);
      *(uint32_t *)(this + 16) = 0;
      if ( *(uint32_t *)(this + 100) < 0x10u )
        pThis_50 = (const CHAR *)(this + 80);
      else
        pThis_50 = *(const CHAR **)(this + 80);
      DeleteFileA(pThis_50);
      *(uint32_t *)(this + 4) = 3;
      *(uint8_t *)(this + 33) = 0;
      *(uint8_t *)(this + 34) = 0;
      LOBYTE(fld_4) = sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  return fld_4;
}



// ------------------------------------------------------------
// 0x4BE4E0 sub_4BE4E0
// ------------------------------------------------------------
char /*stdcall*/ sub_4BE4E0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4BE4E0(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE520 sub_4BE520
// ------------------------------------------------------------
int **/*thiscall*/ sub_4BE520(int **this, int **pDwArg2, uint32_t *uArg3)
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);
  v4 = (int *)fld_e1[1];
  while ( *((uint8_t *)v4 + 21) == 0 )
  {
    if ( (unsigned int)v4[3] >= *uArg3 )
    {
      fld_e1 = v4;
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( fld_e1 == *(this + 1) || *uArg3 < (unsigned int)fld_e1[3] )
  {
    *pDwArg2 = *(this + 1);
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = fld_e1;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4BE590 sub_4BE590
// ------------------------------------------------------------
void **/*thiscall*/ sub_4BE590(void *this)
{
  void (/*thiscall*/ ***pThis_4)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNRDGuildInfo::`vftable';
  v2 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 4);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *((uint32_t *)this + 4) = 0;
  if ( *((uint32_t *)this + 25) >= 0x10u )
    j__free(*((void **)this + 20));
  *((uint32_t *)this + 24) = 0;
  *((uint32_t *)this + 25) = 15;
  *((uint8_t *)this + 80) = 0;
  *((uint8_t *)this + 52) = 0;
  *((uint32_t *)this + 12) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 24) = 0;
  *((uint32_t *)this + 5) = &nengine::IObject::`vftable';
  *(uint32_t *)this = &HttpFileCallBack::`vftable';
  return &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x4BE620 sub_4BE620
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BE620(uint32_t *this)
{
  int *fld_e2; // ecx
  int v3; // eax
  void *v4; // esi
  uint32_t *fld_e22; // ebx
  uint32_t *pThis_1; // edi
  uint32_t *i; // esi
  uint32_t *result; // eax
  int *v9; // [esp+Ch] [ebp-4h] BYREF

  fld_e2 = (int *)*(this + 2);
  v3 = *fld_e2;
  v9 = (int *)*fld_e2;
  if ( v9 != fld_e2 )
  {
    do
    {
      v4 = *(void **)(v3 + 16);
      if ( v4 != nullptr )
      {
        sub_4BE590(*(void **)(v3 + 16));
        j__free(v4);
      }
      sub_41C5E0((int *)&v9);
      v3 = (int)v9;
    }
    while ( v9 != (int *)*(this + 2) );
  }
  fld_e22 = *(uint32_t **)(*(this + 2) + 4);
  pThis_1 = this + 1;
  for ( i = fld_e22; *((uint8_t *)i + 21) == 0; fld_e22 = i )
  {
    sub_4BE4E0((void **)i[2]);
    i = (uint32_t *)*i;
    j__free(fld_e22);
  }
  *(uint32_t *)(pThis_1[1] + 4) = pThis_1[1];
  result = (uint32_t *)pThis_1[1];
  pThis_1[2] = 0;
  *result = result;
  *(uint32_t *)(pThis_1[1] + 8) = pThis_1[1];
  return result;
}



// ------------------------------------------------------------
// 0x4BE6B0 sub_4BE6B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BE6B0(uint32_t *this, char pszArg2)
{
  uint32_t *result; // eax

  if ( *(uint8_t *)this != pszArg2 )
    result = sub_4BE620(this);
  *(uint8_t *)this = pszArg2;
  return result;
}



// ------------------------------------------------------------
// 0x4BE6D0 sub_4BE6D0
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4BE6D0(uint32_t *this, int ***uArg2, int **pDwArg3)
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  uint8_t v20[20]; // [esp+34h] [ebp-34h] BYREF
  int v21; // [esp+48h] [ebp-20h]
  int v22; // [esp+4Ch] [ebp-1Ch]
  int v23; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v26; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 21) != 0 )
  {
    v22 = 15;
    v21 = 0;
    v20[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v26 = 0;
    sub_401740(pExceptionObject, (int)v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 21) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 21) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);
  *((uint8_t *)pDwArg32 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 20) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_433130(v6);
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 20) != 1 || *(uint8_t *)(v16[2] + 20) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 20) == 1 )
            {
              *(uint8_t *)(*v16 + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_4296E0(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_4296E0(v6);
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 20) != 1 || *(uint8_t *)(*v16 + 20) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 20) == 1 )
            {
              *(uint8_t *)(v16[2] + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_433130(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4BE990 sub_4BE990
// ------------------------------------------------------------
char */*thiscall*/ sub_4BE990(char *this, int nArg2)
{
  char *pThis_4C; // ecx
  int nArg22; // edi

  *(uint32_t *)this = &CNRDGuildInfo::`vftable';
  *(this + 24) = 0;
  *((uint32_t *)this + 5) = &off_6C2B88;
  *((uint32_t *)this + 7) = 0;
  *(this + 32) = 1;
  *(this + 34) = 0;
  *(this + 33) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 9) = 0;
  *(this + 52) = 0;
  *((uint32_t *)this + 12) = &off_6C2B88;
  *((uint32_t *)this + 14) = 0;
  *(this + 60) = 1;
  *(this + 62) = 0;
  *(this + 61) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 16) = 0;
  pThis_4C = this + 76;
  *((uint32_t *)pThis_4C + 6) = 15;
  *((uint32_t *)pThis_4C + 5) = 0;
  pThis_4C[4] = 0;
  nArg22 = nArg2;
  *((uint32_t *)this + 2) = nArg2;
  *((uint32_t *)this + 4) = 0;
  sub_4015C0((size_t *)pThis_4C, szPassword, 0);  // 【std::string构造赋值】
  *(this + 12) = -1;
  *((uint32_t *)this + 1) = 0;
  *(this + 13) = 0;
  sub_423200(dword_8F7B08, 77);  // 【发送网络包API】
  nArg2 = nArg22;
  sub_423290(&nArg2, 4);
  sub_423380(dword_8F7B08);
  return this;
}



// ------------------------------------------------------------
// 0x4BEA70 sub_4BEA70
// ------------------------------------------------------------
void /*thiscall*/ sub_4BEA70(int this, char *Src)
{
  int nLen; // eax

  if ( *(uint32_t *)(this + 4) == 2 )
  {
    off_77F3FC(
      "CNRDGuildInfo::on_complete - emblem download complete.\n\tguild = %d, filename = %s",
      *(uint32_t *)(this + 8),
      Src);
    nLen = strlen(Src);
    if ( nLen < 4 )
    {
      off_77F3FC("CNRDGuildInfo::on_complete - filename is too short");
LABEL_4:
      *(uint32_t *)(this + 4) = 6;
      return;
    }
    if ( strcmp(&Src[nLen - 3], (const char *)&off_6F6B58) != 0 )
    {
      off_77F3FC("CNRDGuildInfo::on_complete - invalid file extension");
      goto LABEL_4;
    }
    sub_4015C0((size_t *)(this + 76), Src, strlen(Src));  // 【std::string构造赋值】
    *(uint32_t *)(this + 4) = 4;
    *(uint8_t *)(this + 61) = 0;
    *(uint8_t *)(this + 62) = 0;
    sub_698F90(this + 48, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
}



// ------------------------------------------------------------
// 0x4BEB30 sub_4BEB30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BEB30(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)
{
  int fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  uint32_t *v10; // eax
  int fld_e16; // esi
  uint32_t *v12; // ecx
  int *v13; // ebx
  int v14; // edx
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-50h] BYREF
  size_t v17; // [esp+34h] [ebp-28h] BYREF
  char v18; // [esp+38h] [ebp-24h]
  int v19; // [esp+48h] [ebp-14h]
  int v20; // [esp+4Ch] [ebp-10h]
  int v21; // [esp+58h] [ebp-4h]
  int fld_e15; // [esp+70h] [ebp+14h]

  if ( *(this + 2) >= 0x1FFFFFFEu )
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);
  fld_e12 = (uint32_t *)*(this + 1);
  fld_e15 = fld_e1;
  ++*(this + 2);
  if ( pArg4 == fld_e12 )
  {
    fld_e12[1] = fld_e1;
    *(uint32_t *)*(this + 1) = fld_e1;
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);
    if ( pArg4 == (uint32_t *)*fld_e13 )
      *fld_e13 = fld_e1;
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )
      *(uint32_t *)(fld_e14 + 8) = fld_e1;
  }
  v10 = (uint32_t *)(fld_e1 + 4);
  fld_e16 = fld_e1;
  if ( *(uint8_t *)(*(uint32_t *)(fld_e1 + 4) + 20) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 20) != 0 )
        {
          if ( fld_e16 == v12[2] )
          {
            fld_e16 = *v10;
            sub_433130(*v10);
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 20) = 0;
      fld_e16 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (uint32_t *)(fld_e16 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4BECE0 sub_4BECE0
// ------------------------------------------------------------
int **/*thiscall*/ sub_4BECE0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_4BE4E0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_4BE6D0(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4BEDA0 sub_4BEDA0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BEDA0(uint32_t *this, int pArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  unsigned int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_4BEB30(this, &uArg3, 1, fld_e1, (int)uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_4A3B30(&uArg3);
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else
  {
    v12 = *sub_4BEB30(this, &uArg3, v13, fld_e1, (int)uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4BEE60 sub_4BEE60
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BEE60(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )
  {
    sub_4BEB30((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4BEB30((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )
  {
    v8 = (uint32_t *)fld_4[2];
    if ( v8[3] < *pArg4 )
    {
      sub_4BEB30((uint32_t *)this, uArg2, 0, v8, (int)pArg4);
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0((int *)&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4BEDA0((uint32_t *)this, (int)v10, pArg42);
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )
      sub_4BEB30((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);
    else
      sub_4BEB30((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )
      sub_4BEB30((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);
    else
      sub_4BEB30((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4BEFC0 sub_4BEFC0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BEFC0(uint32_t *this, uint32_t *uArg2)
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);
  v3 = (int *)fld_e1[1];
  while ( *((uint8_t *)v3 + 21) == 0 )
  {
    if ( (unsigned int)v3[3] >= *uArg2 )
    {
      fld_e1 = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  if ( fld_e1 != (uint32_t *)*(this + 1) && *uArg2 >= fld_e1[3] )
    return (int)(fld_e1 + 4);
  v5[0] = *uArg2;
  v5[1] = 0;
  return *sub_4BEE60((int)this, &uArg2, fld_e1, v5) + 16;
}



// ------------------------------------------------------------
// 0x4BF040 sub_4BF040
// ------------------------------------------------------------
int /*thiscall*/ sub_4BF040(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4BECE0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x4BF080 sub_4BF080
// ------------------------------------------------------------
void /*thiscall*/ sub_4BF080(int *this)
{
  int *pThis; // esi
  int *v2; // eax
  int *v3; // [esp-8h] [ebp-1Ch]
  int *pThis2; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  v5 = 0;
  sub_4BE620(this);
  v2 = (int *)pThis[2];
  ++pThis;
  v3 = (int *)*v2;
  v5 = -1;
  sub_4BECE0((int ***)pThis, &pThis2, v3, v2);
  j__free((void *)pThis[1]);
  pThis[1] = 0;
  pThis[2] = 0;
}



// ------------------------------------------------------------
// 0x4BF0F0 sub_4BF0F0
// ------------------------------------------------------------
int */*thiscall*/ sub_4BF0F0(int this, void *Block)
{
  int v2; // ebx
  uint32_t *pThis_4; // esi
  void *pMem; // eax
  int *v7; // eax
  int *v8; // edi
  char v9[8]; // [esp+8h] [ebp-1Ch] BYREF
  int v10; // [esp+10h] [ebp-14h] BYREF
  int *v11; // [esp+14h] [ebp-10h] BYREF
  int v12; // [esp+20h] [ebp-4h]

  v2 = (int)Block;
  if ( Block == nullptr )
    return nullptr;
  pThis_4 = (uint32_t *)(this + 4);
  if ( *sub_4BE520((int **)(this + 4), &v11, &Block) != *(int **)(this + 8) )
    return *(int **)sub_4BEFC0((uint32_t *)(this + 4), &Block);
  pMem = operator new(0x68u);
  Block = pMem;
  v12 = 0;
  if ( pMem != nullptr )
    v7 = (int *)sub_4BE990((char *)pMem, v2);
  else
    v7 = nullptr;
  v8 = v7;
  v11 = v7;
  v12 = -1;
  v10 = v2;
  sub_4BEDA0(pThis_4, (int)v9, &v10);
  return v8;
}



// ------------------------------------------------------------
// 0x4BF1B0 sub_4BF1B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BF1B0(int **this, int nArg2)
{
  int *v4; // [esp+4h] [ebp-4h] BYREF

  if ( nArg2 == 0 )
    return 0;
  if ( *sub_4BE520(this + 1, &v4, &nArg2) == *(this + 2) )
    return 0;
  return *(uint32_t *)sub_4BEFC0(this + 1, &nArg2);
}



// ------------------------------------------------------------
// 0x4BF200 sub_4BF200
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4BF200(uint8_t *this)
{
  uint8_t *pThis_4; // esi
  int pThis_42; // eax

  pThis_4 = this + 4;
  pThis_42 = sub_433AC0(this + 4);
  *((uint32_t *)pThis_4 + 1) = pThis_42;
  *(uint8_t *)(pThis_42 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)pThis_4 + 1) + 4) = *((uint32_t *)pThis_4 + 1);
  **((uint32_t **)pThis_4 + 1) = *((uint32_t *)pThis_4 + 1);
  *(uint32_t *)(*((uint32_t *)pThis_4 + 1) + 8) = *((uint32_t *)pThis_4 + 1);
  *((uint32_t *)pThis_4 + 2) = 0;
  *this = -1;
  return this;
}



// ------------------------------------------------------------
// 0x4BF240 sub_4BF240
// ------------------------------------------------------------
void /*thiscall*/ sub_4BF240(uint32_t *this)
{
  *(this + 16) = 16843009;
  *(this + 15) = 10000;
}



// ------------------------------------------------------------
// 0x4BF250 sub_4BF250
// ------------------------------------------------------------
char /*thiscall*/ sub_4BF250(uint8_t *this, uint32_t *pArg2)
{
  int v2; // eax
  bool v4; // bl
  char v5; // al
  char byte_89D2742; // al

  v2 = *pArg2;
  if ( (int)*pArg2 >= 4 )
  {
    off_77F3FC(aCriticalError_12, *pArg2);
    return 0;
  }
  if ( *(this + v2 + 64) == 0 )
    return 0;
  v4 = false;
  if ( v2 == 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, pArg2[1]);
    v4 = v5 != 0;
    if ( dword_79C0B8 == 0 )
      return v4;
    if ( v5 != 0 )
      return v4;
    v4 = (*(uint8_t (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_79C0B8 + 20))(pArg2[1]) != 0;
    if ( pArg2[1] < 4u )
      return v4;
    byte_89D2742 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B8 + 24))(dword_79C0B8, pArg2[1]);
    goto LABEL_13;
  }
  if ( v2 == 1 )
  {
    byte_89D2742 = byte_89D274;
    if ( pArg2[1] != 0 )
      byte_89D2742 = byte_89D275;
LABEL_13:
    if ( byte_89D2742 != 0 )
      return 1;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x4BF300 sub_4BF300
// ------------------------------------------------------------
char /*thiscall*/ sub_4BF300(uint8_t *this, int pArg2, char pszArg3)
{
  *(this + pArg2 + 64) = pszArg3;
  return pszArg3;
}



// ------------------------------------------------------------
// 0x4BF320 sub_4BF320
// ------------------------------------------------------------
int /*cdecl*/ sub_4BF320(int nArg1, int nArg2, int nArg3)
{
  return sub_5043F0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x4BF340 sub_4BF340
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4BF340(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax
  uint32_t *uArg22; // ecx

  result = uArg2;
  if ( uArg2 != nullptr )
  {
    uArg22 = uArg2;
    result = uArg1;
    do
    {
      if ( result != nullptr )
      {
        *result = *pArg3;
        result[1] = pArg3[1];
        result[2] = pArg3[2];
        result[3] = pArg3[3];
      }
      result += 4;
      uArg22 = (uint32_t *)((char *)uArg22 - 1);
    }
    while ( uArg22 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BF380 sub_4BF380
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BF380(uint32_t *this)
{
  uint32_t *result; // eax
  uint32_t *v3; // esi
  char v4; // bl

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 112))(this);
  result = (uint32_t *)*(this + 21);
  v3 = (uint32_t *)*result;
  v4 = 0;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      if ( v4 != 0 )
      {
        *(uint32_t *)(v3[2] + 36) = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 116))(this, v3[2]);
        result = *(uint32_t **)(v3[2] + 36);
        if ( result == (uint32_t *)1 || result == (uint32_t *)2 )
          v4 = 1;
      }
      v3 = (uint32_t *)*v3;
    }
    while ( v3 != (uint32_t *)*(this + 21) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BF3D0 sub_4BF3D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BF3D0(uint32_t *this, int pArg2)
{
  int fld_e12; // edx
  int fld_e13; // eax
  int v4; // edx
  int i; // esi
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  int fld_e122; // [esp+0h] [ebp-4h]

  fld_e12 = *(this + 12);
  if ( fld_e12 != 0 )
    fld_e13 = (*(this + 13) - fld_e12) >> 4;
  else
    fld_e13 = 0;
  v4 = fld_e13 - 1;
  if ( fld_e13 - 1 < 0 )
    return -1;
  fld_e122 = *(this + 12);
  for ( i = fld_e122 + 16 * v4; ; i -= 16 )
  {
    if ( *(uint8_t *)(i + 12) != 0 )
    {
      v6 = *(uint32_t **)(pArg2 + 8);
      v7 = *(uint32_t **)(pArg2 + 4);
      if ( v7 != v6 )
      {
        do
        {
          if ( *v7 == *(uint32_t *)i )
            break;
          ++v7;
        }
        while ( v7 != v6 );
        if ( v7 != v6 )
          break;
      }
    }
    if ( --v4 < 0 )
      return -1;
  }
  return *(uint32_t *)(fld_e122 + 16 * v4);
}



// ------------------------------------------------------------
// 0x4BF450 sub_4BF450
// ------------------------------------------------------------
char /*thiscall*/ sub_4BF450(uint32_t *this, int nArg2, char pszArg3)
{
  int fld_e12; // edx
  int fld_e13; // eax
  int v5; // eax
  int fld_e122; // edx
  uint32_t *i; // ecx
  int v9; // eax

  fld_e12 = *(this + 12);
  if ( fld_e12 != 0 )
    fld_e13 = (*(this + 13) - fld_e12) >> 4;
  else
    fld_e13 = 0;
  v5 = fld_e13 - 1;
  if ( v5 < 0 )
    return 0;
  fld_e122 = *(this + 12);
  for ( i = (uint32_t *)(fld_e122 + 16 * v5); *i != nArg2; i -= 4 )
  {
    if ( --v5 < 0 )
      return 0;
  }
  v9 = fld_e122 + 16 * v5;
  if ( pszArg3 == 0 )
    return *(uint8_t *)(v9 + 12);
  return *(uint8_t *)(v9 + 12) != 0 && *(uint8_t *)(v9 + 13) != 0;
}



// ------------------------------------------------------------
// 0x4BF4C0 sub_4BF4C0
// ------------------------------------------------------------
bool /*thiscall*/ sub_4BF4C0(uint32_t *this, int nArg2, char pszArg3)
{
  int fld_e12; // edx
  int fld_e13; // eax
  int v5; // eax
  int fld_e122; // edx
  uint32_t *i; // ecx
  int v9; // eax

  fld_e12 = *(this + 12);
  if ( fld_e12 != 0 )
    fld_e13 = (*(this + 13) - fld_e12) >> 4;
  else
    fld_e13 = 0;
  v5 = fld_e13 - 1;
  if ( v5 < 0 )
    return pszArg3 == 0;
  fld_e122 = *(this + 12);
  for ( i = (uint32_t *)(fld_e122 + 16 * v5); *i != nArg2; i -= 4 )
  {
    if ( --v5 < 0 )
      return pszArg3 == 0;
  }
  v9 = fld_e122 + 16 * v5;
  if ( pszArg3 == 0 )
    return *(uint8_t *)(v9 + 12) == 0;
  return *(uint8_t *)(v9 + 12) == 0 && *(uint8_t *)(v9 + 13) != 0;
}



// ------------------------------------------------------------
// 0x4BF540 sub_4BF540 —— Buff 槽查询（+40/+44/+52）
// ------------------------------------------------------------
char /*thiscall*/ sub_4BF540(int *this, int pArg2)
{
  int pArg22; // ebx
  int pThis_B; // eax
  int fld_e12; // esi
  int v6; // ecx
  int fld_e122; // esi
  uint32_t *v8; // esi
  uint32_t *v9; // esi
  int v10; // eax
  int v11; // esi
  int v12; // edi
  int v13; // esi
  int v14; // ebx
  uint32_t *v15; // ebx
  int v16; // esi
  uint32_t *v17; // edx
  int v18; // ecx
  uint32_t *fld_e123; // eax
  int v20; // edi
  uint32_t *fld_e125; // ecx
  int v22; // edx
  int fld_e1242; // ecx
  bool v24; // sf
  int v26; // [esp+8h] [ebp-1Ch]
  uint32_t *v27; // [esp+Ch] [ebp-18h]
  int fld_e124; // [esp+Ch] [ebp-18h]
  int j; // [esp+10h] [ebp-14h]
  int k; // [esp+10h] [ebp-14h]
  int i; // [esp+14h] [ebp-10h]
  int fld_e12422; // [esp+18h] [ebp-Ch]
  int v34; // [esp+20h] [ebp-4h]
  int v35; // [esp+20h] [ebp-4h]

  pArg22 = pArg2;
  if ( *(uint8_t *)(pArg2 + 40) == 0 )
  {
    pThis_B = *(uint32_t *)(pArg2 + 36);
    if ( pThis_B == 0 )
      return pThis_B;
  }
  pThis_B = *(uint32_t *)(pArg2 + 4);
  if ( pThis_B == 0 )
    goto LABEL_78;
  pThis_B = (*(uint32_t *)(pArg2 + 8) - pThis_B) / 24;
  if ( pThis_B == 0 )
    goto LABEL_78;
  fld_e12 = *(this + 12);
  if ( fld_e12 == 0 || (*(this + 13) - fld_e12) >> 4 == 0 )
    goto LABEL_78;
  v6 = *(uint32_t *)(pArg2 + 4) + 24 * pThis_B - 24;
  v34 = v6;
  fld_e122 = *(this + 12) + 16 * (((*(this + 13) - fld_e12) >> 4) + 0xFFFFFFF);
  pThis_B = *(uint32_t *)(pArg2 + 36);
  if ( pThis_B != 1 )
  {
    if ( pThis_B == 2 )
    {
      LOBYTE(pThis_B) = *(uint8_t *)(pArg2 + 40);
      if ( (uint8_t)pThis_B == 0 )
        *(uint32_t *)(pArg2 + 36) = 3;
    }
    else if ( pThis_B != 3 )
    {
      if ( (uint8_t)sub_484F10(pArg2 + 16) == 0 )
      {
        LOBYTE(pThis_B) = (*(int (/*thiscall*/ **)(int *, int))(*this + 52))(this, pArg2 + 16);
        if ( (uint8_t)pThis_B == 0 )
          return pThis_B;
      }
      v10 = *(uint32_t *)(pArg2 + 32);
      if ( v10 != 0 )
      {
        switch ( v10 )
        {
          case 1:
            LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);
            if ( (uint8_t)pThis_B == 0 )
              return pThis_B;
            if ( *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 24 * sub_4FEF30(pArg2) - 8) != 0 )
              goto LABEL_41;
            break;
          case 2:
            LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);
            if ( (uint8_t)pThis_B != 0 )
              return pThis_B;
            goto LABEL_41;
          case 3:
            LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);
            if ( (uint8_t)pThis_B != 0 )
              return pThis_B;
            break;
          default:
LABEL_41:
            fld_e12422 = 0;
            v11 = sub_4FEF30(pArg2) - 1;
            v26 = v11;
            pThis_B = sub_453C00(this + 11);
            v12 = pThis_B - 1;
            v35 = pThis_B - 1;
            if ( v11 < 0 )
            {
LABEL_69:
              *(uint32_t *)(pArg22 + 36) = 1;
            }
            else
            {
              v13 = 24 * v11;
              for ( i = v13; ; v13 = i )
              {
                v14 = *(uint32_t *)(pArg22 + 4);
                pThis_B = *(uint32_t *)(v14 + v13 + 4);
                v15 = (uint32_t *)(v13 + v14);
                v27 = v15;
                v16 = pThis_B != 0 ? (v15[2] - pThis_B) >> 2 : 0;
                if ( v12 < v16 - 1 )
                  break;
                v17 = (uint32_t *)pThis_B;
                pThis_B = v15[2];
                for ( j = pThis_B; v17 != (uint32_t *)pThis_B; ++v17 )
                {
                  v18 = 0;
                  if ( v16 > 0 )
                  {
                    fld_e123 = (uint32_t *)(*(this + 12) + 16 * v35);
                    do
                    {
                      if ( *fld_e123 == *v17 )
                        break;
                      ++v18;
                      fld_e123 -= 4;
                    }
                    while ( v18 < v16 );
                    v15 = v27;
                    pThis_B = j;
                    v12 = v35;
                  }
                  if ( v18 == v16 )
                    return pThis_B;
                }
                if ( v15[4] == 0 )
                {
                  pThis_B = *(this + 12);
                  if ( *(uint32_t *)(16 * v12 + pThis_B + 4) - *(uint32_t *)(16 * (v12 - v16) + pThis_B + 20) > 100 )
                    return pThis_B;
                }
                v20 = 16 * v12;
                fld_e124 = *(uint32_t *)(*(this + 12) + v20 + 4);
                pThis_B = sub_699000((int)(this + 1));  // 【clock_now(clk)】
                if ( v16 > 0 )
                {
                  fld_e125 = (uint32_t *)(*(this + 12) + v20 + 4);
                  for ( k = v16; k != 0; --k )
                  {
                    if ( *fld_e125 + fld_e125[1] < pThis_B )
                      pThis_B = *fld_e125 + fld_e125[1];
                    fld_e125 -= 4;
                  }
                }
                v22 = v15[4];
                if ( v22 <= 0 )
                {
                  fld_e1242 = fld_e124;
                  if ( fld_e124 + v15[5] < fld_e12422 )
                    return pThis_B;
                }
                else
                {
                  if ( pThis_B + v15[5] < fld_e12422 )
                    return pThis_B;
                  fld_e1242 = fld_e124;
                }
                pThis_B -= fld_e1242;
                if ( pThis_B < v22 )
                  return pThis_B;
                pArg22 = pArg2;
                LOBYTE(pThis_B) = v26 - 1;
                v24 = v26 - 1 < 0;
                fld_e12422 = fld_e1242;
                v35 -= v16;
                --v26;
                i -= 24;
                if ( v24 )
                  goto LABEL_69;
                v12 = v35;
              }
            }
            return pThis_B;
        }
        LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 13);
      }
      else
      {
        LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);
      }
      if ( (uint8_t)pThis_B == 0 )
        return pThis_B;
      goto LABEL_41;
    }
    if ( *(uint32_t *)(pArg2 + 32) != 1 )
      return pThis_B;
    v8 = *(uint32_t **)(v6 + 4);
    if ( v8 == *(uint32_t **)(v6 + 8) )
      return pThis_B;
    do
    {
      LOBYTE(pThis_B) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 44))(this, *v8, 0);
      if ( (uint8_t)pThis_B == 0 )
        break;
      pThis_B = *(uint32_t *)(v34 + 8);
      ++v8;
    }
    while ( v8 != (uint32_t *)pThis_B );
    goto LABEL_77;
  }
  pThis_B = *(uint32_t *)(pArg2 + 32);
  if ( pThis_B != 0 )
  {
    switch ( pThis_B )
    {
      case 1:
        v9 = *(uint32_t **)(v6 + 4);
        if ( v9 != *(uint32_t **)(v6 + 8) )
        {
          do
          {
            LOBYTE(pThis_B) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 44))(this, *v9, 0);
            if ( (uint8_t)pThis_B == 0 )
              break;
            pThis_B = *(uint32_t *)(v34 + 8);
            ++v9;
          }
          while ( v9 != (uint32_t *)pThis_B );
          if ( v9 != *(uint32_t **)(v34 + 8) )
            goto LABEL_78;
        }
        *(uint32_t *)(pArg2 + 36) = 3 - (*(uint8_t *)(pArg2 + 40) != 0);
        break;
      case 2:
        LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);
        if ( (uint8_t)pThis_B != 0 )
          *(uint32_t *)(pArg2 + 36) = 0;
        break;
      case 3:
        *(uint32_t *)(pArg2 + 36) = 0;
        break;
      default:
        break;
    }
    return pThis_B;
  }
  v8 = *(uint32_t **)(v6 + 4);
  if ( v8 == *(uint32_t **)(v6 + 8) )
    return pThis_B;
  do
  {
    LOBYTE(pThis_B) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 44))(this, *v8, 0);
    if ( (uint8_t)pThis_B == 0 )
      break;
    pThis_B = *(uint32_t *)(v34 + 8);
    ++v8;
  }
  while ( v8 != (uint32_t *)pThis_B );
LABEL_77:
  if ( v8 != *(uint32_t **)(v34 + 8) )
LABEL_78:
    *(uint32_t *)(pArg2 + 36) = 0;
  return pThis_B;
}


// ------------------------------------------------------------
// 0x4BF910 sub_4BF910
// ------------------------------------------------------------
int /*stdcall*/ sub_4BF910(int pArg1, uint32_t *pArg2)
{
  int pArg12; // ebx
  int v3; // ecx
  unsigned int v4; // esi
  int v5; // edi
  unsigned int v6; // eax
  int result; // eax
  unsigned int v8; // esi
  unsigned int v9; // eax
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // eax
  int v14; // esi
  uint32_t *v15; // ebx
  uint32_t *v16; // edx
  int v17; // ecx
  int v18; // edi
  int v19; // eax
  uint32_t *v20; // edi
  uint32_t *v21; // ecx
  uint32_t *v22; // eax
  int v23; // esi
  unsigned int v24; // ecx
  int v25; // eax
  int v26; // ecx
  int v27; // eax
  int v28; // ecx
  bool v29; // sf
  int v30; // eax
  unsigned int v31; // ecx
  int v32; // edx
  unsigned int v33; // eax
  unsigned int v34; // ecx
  int v35; // edx
  unsigned int v36; // eax
  int v37; // eax
  unsigned int v38; // ecx
  int v39; // edx
  int v40; // [esp+Ch] [ebp-14h]
  int v41; // [esp+10h] [ebp-10h]
  int v42; // [esp+14h] [ebp-Ch]
  int v43; // [esp+18h] [ebp-8h]
  int v44; // [esp+1Ch] [ebp-4h]

  pArg12 = pArg1;
  v3 = *(uint32_t *)(pArg1 + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg1 + 8) - v3) / 24;
  else
    v4 = 0;
  v5 = pArg2[1];
  if ( v5 != 0 )
    v6 = (pArg2[2] - v5) / 24;
  else
    v6 = 0;
  if ( v4 > v6 )
    return 1;
  if ( v5 != 0 )
    v8 = (pArg2[2] - v5) / 24;
  else
    v8 = 0;
  if ( v3 != 0 )
    v9 = (*(uint32_t *)(pArg1 + 8) - v3) / 24;
  else
    v9 = 0;
  if ( v8 > v9 )
    return 2;
  v10 = 0;
  v11 = 0;
  v42 = 0;
  v41 = 0;
  if ( v3 != 0 )
    v10 = (*(uint32_t *)(pArg1 + 8) - v3) / 24;
  v12 = v10 - 1;
  v40 = v12;
  if ( v12 < 0 )
  {
LABEL_46:
    v30 = *(uint32_t *)(pArg12 + 20);
    if ( v30 != 0 )
      v31 = (*(uint32_t *)(pArg12 + 24) - v30) >> 2;
    else
      v31 = 0;
    v35 = pArg2[5];
    if ( v35 != 0 )
      v36 = (pArg2[6] - v35) >> 2;
    else
      v36 = 0;
    if ( v31 > v36 )
      return 1;
    v37 = *(uint32_t *)(pArg12 + 20);
    if ( v37 != 0 )
      v38 = (*(uint32_t *)(pArg12 + 24) - v37) >> 2;
    else
      v38 = 0;
    v39 = pArg2[5];
    if ( v39 != 0 && v38 < (pArg2[6] - v39) >> 2 )
      return 2;
    result = v11;
    if ( v11 == 0 )
      return v41;
  }
  else
  {
    v13 = 24 * v12;
    v14 = v3 + v13 + 4;
    v15 = (uint32_t *)(v5 + v13);
    v44 = v14;
    v43 = v3 - v5;
    while ( 1 )
    {
      v16 = *(uint32_t **)v14;
      if ( *(uint32_t *)v14 != 0 )
        v17 = (*(uint32_t *)(v14 + 4) - (int)v16) >> 2;
      else
        v17 = 0;
      v18 = v15[1];
      if ( v18 != 0 )
        v19 = (v15[2] - v18) >> 2;
      else
        v19 = 0;
      if ( v17 != v19 )
        return 0;
      v20 = *(uint32_t **)(v14 + 4);
      if ( v16 != v20 )
        break;
LABEL_38:
      if ( v42 == 0 )
      {
        v25 = *(uint32_t *)(v14 + 12);
        v26 = v15[4];
        if ( v25 != v26 )
        {
          v14 = v44;
          v42 = (v25 <= v26) + 1;
        }
      }
      if ( v41 == 0 )
      {
        v27 = *(uint32_t *)(v14 + 16);
        v28 = v15[5];
        if ( v27 != v28 )
        {
          v14 = v44;
          v41 = (v27 > v28) + 1;
        }
      }
      v14 -= 24;
      v15 -= 6;
      v29 = --v40 < 0;
      v44 = v14;
      if ( v29 )
      {
        pArg12 = pArg1;
        v11 = v42;
        goto LABEL_46;
      }
    }
    v21 = (uint32_t *)v15[2];
    while ( 1 )
    {
      v22 = (uint32_t *)v15[1];
      if ( v22 == v21 )
        break;
      while ( *v22 != *v16 )
      {
        if ( ++v22 == v21 )
          goto LABEL_33;
      }
      if ( v22 == v21 )
        break;
      if ( ++v16 == v20 )
      {
        v14 = v44;
        goto LABEL_38;
      }
    }
LABEL_33:
    v23 = *(uint32_t *)((char *)v15 + v43 + 4);
    if ( v23 != 0 )
      v24 = (*(uint32_t *)((char *)v15 + v43 + 8) - v23) >> 2;
    else
      v24 = 0;
    v32 = v15[1];
    if ( v32 != 0 )
      v33 = (v15[2] - v32) >> 2;
    else
      v33 = 0;
    if ( v24 > v33 )
      return 1;
    if ( v32 != 0 )
      v34 = (v15[2] - v32) >> 2;
    else
      v34 = 0;
    if ( v23 != 0 )
      return (*(uint32_t *)((char *)v15 + v43 + 8) - v23) >> 2 < v34 ? 2 : 0;
    else
      return v34 != 0 ? 2 : 0;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4BFBC0 sub_4BFBC0
// ------------------------------------------------------------
char /*thiscall*/ sub_4BFBC0(uint32_t *this, int pArg2, char pszArg3)
{
  uint32_t *fld_e21; // edx
  uint32_t *v4; // eax
  char result; // al

  fld_e21 = (uint32_t *)*(this + 21);
  v4 = (uint32_t *)*fld_e21;
  if ( (uint32_t *)*fld_e21 == fld_e21 )
    goto LABEL_5;
  do
  {
    if ( v4[2] == pArg2 )
      break;
    v4 = (uint32_t *)*v4;
  }
  while ( v4 != fld_e21 );
  if ( v4 == fld_e21 )
  {
LABEL_5:
    if ( pszArg3 != 0 )
      return 0;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, pArg2);
  }
  if ( *(uint8_t *)(pArg2 + 40) == 0 )
    return 0;
  result = 1;
  if ( *(uint32_t *)(pArg2 + 36) != 1 )
    return 0;
  return result;
}



// ------------------------------------------------------------
// 0x4BFC10 sub_4BFC10
// ------------------------------------------------------------
char /*thiscall*/ sub_4BFC10(void *this, int pArg2)
{
  int v2; // esi

  v2 = *(uint32_t *)(pArg2 + 4);
  if ( v2 != 0 && (*(uint32_t *)(pArg2 + 8) - v2) >> 3 != 0 )
  {
    if ( v2 == *(uint32_t *)(pArg2 + 8) )
      return 1;
    while ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 48))(this, v2) != 0 )
    {
      v2 += 8;
      if ( v2 == *(uint32_t *)(pArg2 + 8) )
        return 1;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4BFC60 sub_4BFC60
// ------------------------------------------------------------
char /*thiscall*/ sub_4BFC60(void *this, int pArg2)
{
  uint32_t *v2; // esi

  v2 = *(uint32_t **)(pArg2 + 4);
  if ( v2 != nullptr && (*(uint32_t *)(pArg2 + 8) - (int)v2) >> 2 != 0 )
  {
    if ( v2 == *(uint32_t **)(pArg2 + 8) )
      return 1;
    while ( (*(uint8_t (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 44))(this, *v2, 0) != 0 )
    {
      if ( ++v2 == *(uint32_t **)(pArg2 + 8) )
        return 1;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4BFCB0 sub_4BFCB0
// ------------------------------------------------------------
int /*thiscall*/ sub_4BFCB0(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x4BFD40 sub_4BFD40
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4BFD40(int this, int pArg2, unsigned int uArg3, uint32_t *Block)
{
  int v5; // edx
  int v6; // ecx
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v12; // eax
  int fld_87; // ecx
  int fld_88; // eax
  int v15; // ebx
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v18; // edi
  char *fld_83; // eax
  int fld_86; // edi
  char *v21; // edi
  int fld_42; // [esp-18h] [ebp-44h]
  int fld_85; // [esp-Ch] [ebp-38h]
  unsigned int fld_84; // [esp-8h] [ebp-34h]
  int v25; // [esp+0h] [ebp-2Ch] BYREF
  uint32_t v26[5]; // [esp+Ch] [ebp-20h] BYREF
  int v27; // [esp+28h] [ebp-4h]
  int v28; // [esp+38h] [ebp+Ch]
  char *Blocka; // [esp+3Ch] [ebp+10h]
  void *Blockb; // [esp+3Ch] [ebp+10h]

  v5 = Block[1];
  v26[0] = *Block;
  v6 = Block[2];
  v26[1] = v5;
  v26[3] = Block[3];
  fld_4 = *(uint32_t *)(this + 4);
  v26[4] = &v25;
  v26[2] = v6;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 4;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_8 = 0;
    if ( 0xFFFFFFF - fld_8 < uArg3 )
      sub_434730(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(char **)(this + 8);
      Blockb = fld_83;
      if ( (int)&fld_83[-pArg2] >> 4 >= uArg3 )
      {
        v21 = &fld_83[-16 * uArg3];
        *(uint32_t *)(this + 8) = sub_602460(v21, fld_83, fld_83);
        sub_4BF320(pArg2, v21, Blockb);
        return sub_453C20(pArg2, pArg2 + 16 * uArg3, v26);
      }
      else
      {
        sub_602460(pArg2, fld_83, pArg2 + 16 * uArg3);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);
        fld_85 = *(uint32_t *)(this + 8);
        v27 = 2;
        sub_504650(fld_85, fld_84, v26);
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        return sub_453C20(pArg2, fld_86 - 16 * uArg3, v26);
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )
        v12 = (result >> 1) + result;
      else
        v12 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
      else
        fld_87 = 0;
      if ( v12 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;
        else
          fld_88 = 0;
        v12 = uArg3 + fld_88;
      }
      v28 = 16 * v12;
      Blocka = (char *)operator new(16 * v12);
      fld_42 = *(uint32_t *)(this + 4);
      v27 = 0;
      v15 = sub_602460(fld_42, pArg2, Blocka);
      sub_4BF340(v15, uArg3, v26);
      sub_602460(pArg2, *(uint32_t *)(this + 8), 16 * uArg3 + v15);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;
      else
        fld_89 = 0;
      v18 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &Blocka[v28];
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];
      *(uint32_t *)(this + 4) = Blocka;
      return (unsigned int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x4BFFA0 sub_4BFFA0
// ------------------------------------------------------------
char */*thiscall*/ sub_4BFFA0(int this, unsigned int uArg2)
{
  char *result; // eax
  int fld_4; // edx
  int fld_82; // edi
  unsigned int fld_C; // ecx
  char *pMem; // ebx
  int fld_43; // eax
  int fld_42; // [esp-18h] [ebp-38h]
  int fld_8; // [esp-14h] [ebp-34h]
  int v11; // [esp+0h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-14h]
  int *v13; // [esp+10h] [ebp-10h]
  int v14; // [esp+1Ch] [ebp-4h]
  size_t v15; // [esp+28h] [ebp+8h]

  result = (char *)uArg2;
  v13 = &v11;
  if ( uArg2 > 0xFFFFFFF )
    sub_434730(this);
  fld_4 = *(uint32_t *)(this + 4);
  fld_82 = 0;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 4;
  else
    fld_C = 0;
  if ( fld_C < uArg2 )
  {
    v15 = 16 * uArg2;
    pMem = (char *)operator new(v15);
    fld_8 = *(uint32_t *)(this + 8);
    fld_42 = *(uint32_t *)(this + 4);
    Block = pMem;
    v14 = 0;
    sub_602460(fld_42, fld_8, pMem);
    fld_43 = *(uint32_t *)(this + 4);
    if ( fld_43 != 0 )
    {
      fld_82 = (*(uint32_t *)(this + 8) - fld_43) >> 4;
      j__free(*(void **)(this + 4));
    }
    *(uint32_t *)(this + 12) = &pMem[v15];
    *(uint32_t *)(this + 8) = &pMem[16 * fld_82];
    *(uint32_t *)(this + 4) = pMem;
    return &pMem[v15];
  }
  return result;
}


