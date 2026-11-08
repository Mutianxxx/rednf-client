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
char */*cdecl*/ sub_4B0080(int nArg1, int nArg2)  // sub_4B0080 —— ★职业/转职 → .equ 路径表（输出 byte_9A0468）
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
            return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
          }
          if ( nArg2 == 4 )
          {
            strcpy(byte_9A0468, "character/gunner/growtype/spitfire.equ");  // job2=gunner growtype4
            return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
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
          return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
        }
        if ( nArg2 != 2 )
          return nullptr;
        v3 = "character/mage/growtype/summoner.equ";  // job3=mage growtype2
      }
      qmemcpy(byte_9A0468, v3, 0x25u);  // byte_9A0468 —— job2=gunner growtype2
      return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
    }
    switch ( nArg2 )  // 按 nArg2 分派
    {
      case 2:  // case 2 分派（§A 0x4B0080-0x4B0210 ★职业/转职表（.equ 路径 + 裸身资源 id））
        strcpy(byte_9A0468, "character/fighter/growtype/striker.equ");  // job1=fighter growtype2
        return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
      case 3:  // case 3 分派（§A 0x4B0080-0x4B0210 ★职业/转职表（.equ 路径 + 裸身资源 id））
        strcpy(byte_9A0468, "character/fighter/growtype/streetfighter.equ");  // job1=fighter growtype3
        return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
      case 4:  // case 4 分派（§A 0x4B0080-0x4B0210 ★职业/转职表（.equ 路径 + 裸身资源 id））
        strcpy(byte_9A0468, "character/fighter/growtype/grabbler.equ");  // job1=fighter growtype4
        return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
      default:
        break;
    }
  }
  else
  {
    switch ( nArg2 )  // 按 nArg2 分派
    {
      case 1:  // case 1 分派（§A 0x4B0080-0x4B0210 ★职业/转职表（.equ 路径 + 裸身资源 id））
        strcpy(byte_9A0468, "character/swordman/growtype/weaponmaster.equ");  // job0=swordman growtype1
        return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
      case 3:  // case 3 分派（§A 0x4B0080-0x4B0210 ★职业/转职表（.equ 路径 + 裸身资源 id））
        strcpy(byte_9A0468, "character/swordman/growtype/berserker.equ");  // job0=swordman growtype3
        return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
      case 4:  // case 4 分派（§A 0x4B0080-0x4B0210 ★职业/转职表（.equ 路径 + 裸身资源 id））
        strcpy(byte_9A0468, "character/swordman/growtype/asura.equ");  // job0=swordman growtype4
        return byte_9A0468;  // byte_9A0468 —— job2=gunner growtype2
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
int /*cdecl*/ sub_4B0210(int nArg1, int nArg2)  // sub_4B0210 —— ★裸身身体资源 id 表（job×growtype）
{
  int result; // eax

  switch ( nArg1 )  // 按 nArg1 分派
  {
    case 0:  // case 0 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
      switch ( nArg2 )  // 按 nArg2 分派
      {
        case 1:  // case 1 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 39400;  // job0 裸身 id
        case 3:  // case 3 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 40600;  // job0 裸身 id
        case 4:  // case 4 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 41000;
        case 5:  // case 5 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 41800;
        case 8:  // case 8 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 27900;
        default:
          break;
      }
      return 0xFFFF;
    case 1:  // case 1 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
      switch ( nArg2 )  // 按 nArg2 分派
      {
        case 1:  // case 1 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 43400;
        case 3:  // case 3 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 44600;
        case 4:  // case 4 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 45000;
        case 5:  // case 5 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 45800;
        case 8:  // case 8 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 29000;
        default:
          break;
      }
      return 0xFFFF;
    case 2:  // case 2 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
      switch ( nArg2 )  // 按 nArg2 分派
      {
        case 1:  // case 1 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 47400;
        case 3:  // case 3 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 48600;
        case 4:  // case 4 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 49000;
        case 5:  // case 5 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
          return 49800;
        case 8:  // case 8 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
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
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 1:  // case 1 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
      return 51400;
    case 3:  // case 3 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
      return 52600;
    case 4:  // case 4 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
      return 53000;
    case 5:  // case 5 分派（§B 0x4B0210-0x4B12B0 外观状态位族（+48..54））
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
// 0x4B0340 sub_4B0340 —— 职业配置查询（job 字段 +7148）
//   职业字段(+7148) 为 4（无职业/无效）时返回 0，否则转发 ·0x47E720(nArg2)。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0340(uint32_t *this, int nArg2)  // sub_4B0340 —— 职业配置查询（job 字段 +7148）
{
  int fld_e1787; // eax  | +0x1BEC → ★大状态 ID（IRDCharacter；va=005796C0）

  fld_e1787 = *(this + 1787);  // 读字段 fld_e1787 = this+1787（bBehaviorWord）
  if ( fld_e1787 == 4 )  // fld_e1787=this+1787 bBehaviorWord
    return 0;
  else
    return sub_47E720(fld_e1787, nArg2);  // sub_47E720 —— 调 sub_47E720
}



// ------------------------------------------------------------
// 0x4B0370 sub_4B0370 —— 双槽外观状态同步（vt+1132 取值/vt+892 下发）
//   先验 vt+308 有效性；对槽 0/1 取当前外观值(vt+1132)，值 4 时做互斥特判（+6696 置 -1），
//   与缓存(+6636/+6640) 或 4-标志(v8/v6) 不一致时经 vt+892 下发；+6634/+6635 为左右侧开关。【推断】
// ------------------------------------------------------------
char /*thiscall*/ sub_4B0370(uint32_t *this)  // sub_4B0370 —— 双槽外观状态同步（vt+1132 取值/vt+892 下发）
{
  int fld_e50; // eax
  int fld_e1659; // edi
  int fld_e1675; // edx
  int fld_e1674; // eax
  char v6; // bl
  char v8; // [esp+4h] [ebp-8h]
  int fld_e1660; // [esp+8h] [ebp-4h]

  LOBYTE(fld_e50) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)fld_e50 == 0 )
    return fld_e50;
  fld_e50 = *(this + 50);  // 读字段 fld_e50 = this+50（bCharSelSent）
  if ( fld_e50 != 0 )  // fld_e50=this+50 bCharSelSent
    return fld_e50;  // fld_e50=this+50 bCharSelSent
  if ( *((uint8_t *)this + 6634) == 0 )
  {
    LOBYTE(fld_e50) = *((uint8_t *)this + 6635);  // fld_e50=this+50 bCharSelSent
    if ( (uint8_t)fld_e50 == 0 )  // fld_e50=this+50 bCharSelSent
      return fld_e50;  // fld_e50=this+50 bCharSelSent
  }
  fld_e1659 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1132))(this, 0);  // 虚调用 vt+1132（this 虚表槽）
  fld_e1675 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1132))(this, 1);  // 虚调用 vt+1132（this 虚表槽）
  fld_e1660 = fld_e1675;
  if ( *((uint8_t *)this + 6634) == 0 )
  {
    fld_e1659 = *(this + 1659);  // 读字段 fld_e1659 = this+1659
    goto LABEL_16;
  }
  if ( *((uint8_t *)this + 6635) == 0 )
    goto LABEL_16;
  fld_e1674 = *(this + 1674);  // 读字段 fld_e1674 = this+1674
  if ( fld_e1674 != 0 )
  {
    if ( fld_e1674 != 1 )
      goto LABEL_16;
    if ( fld_e1675 == 4 )
    {
      fld_e1675 = *(this + 1675);  // 读字段 fld_e1675 = this+1675
      fld_e1660 = fld_e1675;
      goto LABEL_16;
    }
LABEL_13:
    *(this + 1674) = -1;  // 写字段 this+1674 ← -1
    goto LABEL_16;
  }
  if ( fld_e1659 != 4 )
    goto LABEL_13;
  fld_e1659 = *(this + 1675);  // 读字段 fld_e1659 = this+1675
LABEL_16:
  if ( *((uint8_t *)this + 6635) == 0 )
  {
    fld_e1660 = *(this + 1660);  // 读字段 fld_e1660 = this+1660
    fld_e1675 = fld_e1660;
  }
  v8 = 1;
  if ( fld_e1659 == 4 || fld_e1675 == 4 )  // 判定 fld_e1659 == 4 或 fld_e1675 == 4
    v8 = 0;
  fld_e50 = *(this + 1659);  // 读字段 fld_e50 = this+1659
  v6 = 1;
  if ( fld_e50 == 4 || *(this + 1660) == 4 )
    v6 = 0;
  if ( fld_e1659 != fld_e50 || v8 != v6 )  // 判定 fld_e1659 != fld_e50 或 v8 != v6
  {
    LOBYTE(fld_e50) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, char))(*this + 892))(this, 0, fld_e1659, v8);  // 虚调用 vt+892（this 虚表槽）
    fld_e1675 = fld_e1660;
  }
  if ( fld_e1675 != *(this + 1660) || v8 != v6 )
    LOBYTE(fld_e50) = (*(int (/*thiscall*/ **)(uint32_t *, int, int, char))(*this + 892))(this, 1, fld_e1675, v8);  // 虚调用 vt+892（this 虚表槽）
  return fld_e50;
}



// ------------------------------------------------------------
// 0x4B04B0 sub_4B04B0 —— 模式基值映射 0..4（含关系码对调）
//   由 ·0x4BF3D0 读 unk_9A0310/unk_9A0320 基值映射为 0..4 代号；vt+776(15) 置位时经 ·0x432E50 对调（阵营互换）。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_4B04B0(void *this, int nArg2)  // sub_4B04B0 —— 模式基值映射 0..4（含关系码对调）
{
  void *v3; // eax
  int v4; // eax
  int v5; // esi

  v3 = &unk_9A0310;  // 取全局对象/数组首址（v3 ← unk_9A0310）
  if ( nArg2 != 0 )
    v3 = &unk_9A0320;  // 取全局对象/数组首址（v3 ← unk_9A0320）
  v4 = sub_4BF3D0(v3);  // sub_4BF3D0 —— 反向查许可记录 id
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
  if ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 776))(this, 15) != 0 )  // 虚调用 vt+776（this 虚表槽）
    return sub_432E50(v5);  // sub_432E50 —— 存 关系码对调映射 【关系码对调映射】0 与 1 互换与 2 与 3 互换，其余返回 4
  else
    return v5;
}



// ------------------------------------------------------------
// 0x4B0530 sub_4B0530 —— 目标引用解除（清 +7888 缓存）
//   经 ·0x4D6E40 处理目标对象；若目标即自身则触发状态 9/10 收尾(vt+216)，并清空 +7888 目标缓存。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0530(uint32_t *this, uint32_t *uArg2)  // sub_4B0530 —— 结果 = 目标引用解除（清 +7888 缓存）
{
  int result; // eax

  result = sub_4D6E40(uArg2);  // 调 尾调 sub_53F8A0(nArg2)。0x4D6CA0 注释的 50% 预表现容器成员即条件 33 对象
  if ( uArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);  // 虚调用 vt+216（this）全场广播
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);  // 虚调用 vt+216（this）全场广播
  }
  if ( (uint32_t *)*(this + 1972) == uArg2 )
    *(this + 1972) = 0;  // 写字段 this+1972 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x4B0580 sub_4B0580 —— 取 +6500 组件数据字段
//   取 +6500 组件的 vt+172 对象，返回其 +4 字段值（·0x41A5E0 取值）；组件缺失返回 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0580(uint32_t *this)  // sub_4B0580 —— 取 +6500 组件数据字段
{
  int fld_e1625; // eax
  int v2; // eax

  fld_e1625 = *(this + 1625);  // 读字段 fld_e1625 = this+1625
  if ( fld_e1625 == 0 )  // fld_e1625=this+1625 nWeaponItemId
    return -1;
  v2 = (*(int (**)(void))(*(uint32_t *)fld_e1625 + 172))();  // 虚调用 vt+172（fld_e1625 虚表槽）
  return sub_41A5E0(v2 + 4);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4B05B0 sub_4B05B0 —— 置状态标志 +8004
//   置位 +8004（与 ·0x4B05C0 的隐藏位 +8052 配套的状态开关）。【推断】
// ------------------------------------------------------------
void /*thiscall*/ sub_4B05B0(uint32_t *this)  // sub_4B05B0 —— 置状态标志 +8004
{
  *(this + 2001) = 1;  // 写字段 this+2001 ← 1
}



// ------------------------------------------------------------
// 0x4B05C0 sub_4B05C0 —— 置隐藏/屏蔽位 +8052
//   写字节 +8052：外观切换（·0x4B05D0/·0x4B0A80）会跳过该位非 0 的角色。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B05C0(uint8_t *this, char pszArg2)  // sub_4B05C0 —— 置隐藏/屏蔽位 +8052
{
  *(this + 8052) = pszArg2;  // 写字段 this+8052 ← pszArg2
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4B05D0 sub_4B05D0 —— 外观状态切换（+52；sub_48F690/578E80 场景联动）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B05D0(uint8_t *this, char pszArg2)  // sub_4B05D0 —— 外观状态切换（+52；sub_48F690/578E80 场景联动）
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
  v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104);  // 虚调用 vt+120（dword_8F8520）转发(对象+缓冲)
  if ( v3 == 0 )
    return 0;
  v5 = 0;
  while ( 1 )
  {
    v6 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    if ( v6 == 4 )
    {
      v7 = sub_48F690((uint32_t *)dword_99FEC0, v5);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
LABEL_9:
      v2 = v7;
      goto LABEL_10;
    }
    if ( v6 == 6 || v6 == 7 )
    {
      v7 = sub_578E80(v5);  // sub_578E80 —— 存 调: sub_578E80 sub_48F660
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
    v9 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    if ( v9 == 4 )
    {
      v10 = sub_48F690((uint32_t *)dword_99FEC0, v8);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
      goto LABEL_26;
    }
    if ( v9 == 6 || v9 == 7 )
    {
      v10 = sub_578E80(v8);  // sub_578E80 —— 存 调: sub_578E80 sub_48F660
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
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 7 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  {
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 虚调用 vt+376（dword_8F7C04 虚表槽）
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 376))(pObj) == v16 )  // 虚调用 vt+376（pObj 虚表槽）
      return *(uint32_t *)(v2 + 196);  // 返回字段 v2+196（宽4字节）
    goto LABEL_33;
  }
  return *(uint32_t *)(v2 + 196);  // 返回字段 v2+196（宽4字节）
}



// ------------------------------------------------------------
// 0x4B0780 sub_4B0780 —— 设置三演出参数 +8056..+8064
//   写 +8056/+8060/+8064 三个参数，配套 +8088 倒计时器（·0x4B07B0）。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0780(uint32_t *this, int nArg2, int nArg3, int nArg4)  // sub_4B0780 —— 设置三演出参数 +8056..+8064
{
  *(this + 2014) = nArg2;  // 写字段 this+2014 ← nArg2
  *(this + 2015) = nArg3;  // 写字段 this+2015 ← nArg3
  *(this + 2016) = nArg4;  // 写字段 this+2016 ← nArg4
  return nArg4;
}



// ------------------------------------------------------------
// 0x4B07B0 sub_4B07B0 —— 启动 300 时长倒计时（时钟 +8088）
//   +8100 非运行态时置 1、清 +8101/+8102，并启动时钟 +8088 的 300 时长倒计时
//   （·0x698F90 clock_set_countdown，域 0）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B07B0(uint8_t *this)  // sub_4B07B0 —— 启动 300 时长倒计时（时钟 +8088）
{
  char result; // al
  int pThis_1F98; // ecx

  result = 1;
  if ( *(this + 8100) != 1 )
  {
    *(this + 8100) = 1;  // 写字段 this+8100 ← 1
    pThis_1F98 = (int)(this + 8088);
    *(uint8_t *)(pThis_1F98 + 13) = 0;  // 写字段 pThis_1F98+13 ← 0
    *(uint8_t *)(pThis_1F98 + 14) = 0;  // 写字段 pThis_1F98+14 ← 0
    return sub_698F90(pThis_1F98, 300, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B07E0 sub_4B07E0 —— 攻击包络命中判定（扇形/梯形）
//   由攻击者朝向(vt+152)、体宽(vt+192 的 3/4)、目标姿态(vt+120/+124/+128) 与角度参数 a6..a10
//   做三角函数投影(·0x405420，dword_7930D4 缩放) 判 (x,y,z) 是否落入包络；供 ·0x4B2580 选目标。【推断】
// ------------------------------------------------------------
bool /*cdecl*/ sub_4B07E0(  // sub_4B07E0 —— 攻击包络命中判定（扇形/梯形）
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

  v14 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a2 + 340))(a2) + 32);  // 虚调用 vt+340（a2 虚表槽）
  v22 = v14;
  v23 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a2 + 340))(a2) + 36);  // 虚调用 vt+340（a2 虚表槽）
  v21 = 3 * (*(int (/*thiscall*/ **)(int *))(*a2 + 192))(a2) / 4;  // 虚调用 vt+192（a2）取尺寸/包围盒
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);  // 虚调用 vt+152（a1）取值(参数)
  v16 = *a2;
  if ( v15 == 1 )
    v17 = v14 + (*(int (/*thiscall*/ **)(int *))(v16 + 120))(a2) + a11 / 2 - a3;  // 调虚槽 +120：动画对象
  else
    v17 = a3 + v14 + a11 / 2 - (*(int (/*thiscall*/ **)(int *))(v16 + 120))(a2);  // 调虚槽 +120：动画对象
  v18 = (*(int (/*thiscall*/ **)(int *))(*a2 + 124))(a2) - a4;  // 虚调用 vt+124（a2）目标坐标y下界
  v24 = (*(int (/*thiscall*/ **)(int *))(*a2 + 128))(a2) - a5;  // 虚调用 vt+128（a2）目标坐标y上界
  result = false;
  if ( v17 >= 0 && v17 <= a11 + a10 + 2 * v22 )
  {
    v25 = (float)v17;
    v19 = v23 + a12 / 2 - (uint64_t)(sub_405420(a6 + a8) * (double)dword_7930D4[0] * v25 * -0.0099999998);  // sub_405420 —— tan 查表（Block 表，角度 %360 归一含负角修正）
    if ( v18 >= (int)(a12 / -2
                    - (uint64_t)(sub_405420(a6 - a8) * (double)dword_7930D4[0] * v25 * -0.0099999998)  // sub_405420 —— tan 查表（Block 表，角度 %360 归一含负角修正）
                    - v23)
      && v18 <= v19
      && v24 >= (int)((uint64_t)(sub_405420((a7 - a9 + 360) % 360) * v25) - a13 / 2 - v21)  // sub_405420 —— tan 查表（Block 表，角度 %360 归一含负角修正）
      && v24 <= (int)(a13 / 2 + (uint64_t)(sub_405420((a7 + a9 + 360) % 360) * v25)) )  // sub_405420 —— tan 查表（Block 表，角度 %360 归一含负角修正）
    {
      return true;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B09B0 sub_4B09B0 —— 座位切换封包（操作码 38）
//   座位映射(·0x48FCA0 求下标、·0x656710 表) 为 -1 或本地槽对象为空时发包：dword_8F8520 封包器
//   vt+8(38,1) 开包，压入 vt+48/vt+52 与 +8212，vt+60(1,-1) 提交；nArg2 存 +8212。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B09B0(uint8_t *this, int nArg2)  // sub_4B09B0 —— 座位切换封包（操作码 38）
{
  int v3; // eax
  int dword_8F85202; // ebx
  int v5; // edi
  int result; // eax
  int v7; // edi
  int pThis_30; // eax
  int v9; // edi
  int pThis_34; // eax

  v3 = sub_48FCA0();  // sub_48FCA0 —— 结果 = 自身座位下标查找（表 dword_99FF08）
  dword_8F85202 = dword_8F8520;  // dword_8F85202 —— [esp+18h] [ebp-18h]
  v5 = v3;
  if ( *(uint32_t *)(sub_656710() + 4 * v3) == -1 || (result = *(uint32_t *)(dword_8F85202 + 4 * v5 + 1048648)) == 0 )  // sub_656710 —— 取全局单例地址（返回 unk_9BD5D0）
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
    *((uint32_t *)this + 2053) = nArg2;  // 写字段 this[2053]（宽4字节）
    if ( (uint8_t)result != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 38, 1);  // 虚调用 vt+8（dword_8F8520 虚表槽）
      v7 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
      pThis_30 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 48))(this);  // 虚调用 vt+48（this）归属坐标x
      (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, pThis_30);  // dword_8F8520 —— 虚表 +120 调用
      v9 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
      pThis_34 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 52))(this);  // 虚调用 vt+52（this）归属坐标y
      (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, pThis_34);  // dword_8F8520 —— 虚表 +120 调用
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 32))(*(this + 8212));  // 虚调用 vt+32（dword_8F8520 虚表槽）
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0A60 sub_4B0A60 —— 切换开关（按 +8212 翻转）
//   按 +8212 是否为 1 翻转调用 ·0x4B09B0(0/1)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0A60(int this)  // sub_4B0A60 —— 切换开关（按 +8212 翻转）
{
  if ( *(uint32_t *)(this + 8212) == 1 )  // this+8212〔pHintText8212〕
    return sub_4B09B0((uint8_t *)this, 0);  // sub_4B09B0 —— 座位切换封包（操作码 38）
  else
    return sub_4B09B0((uint8_t *)this, 1);  // sub_4B09B0 —— 座位切换封包（操作码 38）
}



// ------------------------------------------------------------
// 0x4B0A80 sub_4B0A80 —— 输入驱动的外观目标切换与镜头联动
//   键位查询(dword_79C0B4 vt+16/+20)：nArg2 与 1 号键经 ·0x4B05D0 前后切换外观目标，键 81..88 直选玩家槽；
//   命中者经 ·0x424A40 附着镜头、键 13 触发 ·0x424530 镜头演出；
//   末尾 vt+724 判定失败则重载 4 个部件资源(·0x4BF300)。【推断】
// ------------------------------------------------------------
int /*usercall*/ sub_4B0A80@<eax>(uint8_t *uArg1@<ecx>, int nArg2@<edi>)  // 实现：输入驱动的外观目标切换与镜头联动
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
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 虚调用 vt+120（dword_8F8520）转发(对象+缓冲)
  v4 = *(uint32_t *)(result + 104);  // 读字段 v4 = result+104（nTimerEnd）
  if ( v4 == 0 )
    return result;
  if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 0, nArg2) != 0 )  // 虚调用 vt+16（dword_79C0B4 虚表槽）
  {
    v5 = sub_4B05D0(pObj, 1);  // sub_4B05D0 —— 外观状态切换（+52；sub_48F690/578E80 场景联动）
    goto LABEL_19;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, 1) != 0 )  // 虚调用 vt+16（dword_79C0B4 虚表槽）
  {
    v5 = sub_4B05D0(pObj, 0);  // sub_4B05D0 —— 外观状态切换（+52；sub_48F690/578E80 场景联动）
    goto LABEL_19;
  }
  v6 = 0;
  v7 = 0;
  while ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 16))(dword_79C0B4, v7 + 81) == 0 )  // 虚调用 vt+16（dword_79C0B4 虚表槽）
  {
LABEL_16:
    if ( ++v7 >= 8 )
    {
      pObj = uArg1;
      goto LABEL_21;
    }
  }
  v8 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  if ( v8 == 4 )
  {
    v9 = sub_48F690((uint32_t *)dword_99FEC0, v7);  // sub_48F690 —— 结果 = 槽 id 解析·第二组（偏移 +10）
LABEL_12:
    v6 = v9;
    goto LABEL_13;
  }
  if ( v8 == 6 )
  {
    v9 = sub_578E80(v7);  // sub_578E80 —— 存 调: sub_578E80 sub_48F660
    goto LABEL_12;
  }
LABEL_13:
  if ( v6 == 0 )
    goto LABEL_16;
  v10 = *(uint32_t *)(v6 + 196);  // 读字段 v10 = v6+196
  if ( v10 == 0 || *(uint8_t *)(v10 + 8052) != 0 )
    goto LABEL_16;
  v5 = *(uint32_t *)(v6 + 196);  // 读字段 v5 = v6+196
  pObj = uArg1;
LABEL_19:
  if ( v5 != 0 )
    sub_424A40(*(uint32_t **)(v4 + 132), v5);  // sub_424A40 —— 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
LABEL_21:
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, 13) != 0 )  // 虚调用 vt+20（dword_79C0B4）条件位掩码测试(273受击/17有血/65机械)
    sub_424530(*(uint32_t *)(v4 + 132), 2.0, 100, 100, -1, -1, -1, 1);  // sub_424530 —— 变焦命令（暴击特写 1.5×/受击微特写 1.2×/连击冲拳 2.0× 的统一入口）。
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 724))(pObj);  // 虚调用 vt+724（pObj）取值
  if ( (uint8_t)result == 0 )
  {
    for ( i = 0; i < 4; ++i )  // 遍历计次循环（i < 4）
      result = sub_4BF300(i, 0);  // sub_4BF300 —— 槽写侧（+64 + 索引）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0BC0 sub_4B0BC0 —— 记录数统计（152 字节/条）
//   (尾-首)/152，即 152 字节/条的 avatar 配置记录数。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0BC0(int *this)  // sub_4B0BC0 —— 记录数统计（152 字节/条）
{
  int result; // eax

  result = *(this + 1);  // 读字段 result = this+1
  if ( result != 0 )  // result=this+4 宿主对象
    return (*(this + 2) - result) / 152;  // this+8〔nSkillRec8(推断)〕
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x4B0BE0 sub_4B0BE0 —— RB 树子树最大值（右脊下降）
//   沿右子(+8) 下降取子树最大节点，供删除时维护 header 右极值；节点布局 +0 左/+4 父/+8 右/+25 nil。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B0BE0(int pArg1)  // sub_4B0BE0 —— RB 树子树最大值（右脊下降）
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 25) == 0; i = *(uint32_t *)(i + 8) )  // 读字段 i = pArg1+8（nSkillRec8）
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x4B0C00 sub_4B0C00 —— RB 树右旋（左子提升）
//   以 pArg2 为轴右旋；节点布局 +0 左/+4 父/+8 右/+25 nil。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0C00(uint32_t *this, uint32_t *pArg2)  // sub_4B0C00 —— RB 树右旋（左子提升）
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);  // 读字段 v3 = result+8（nSkillRec8）
  if ( *(uint8_t *)(v3 + 25) == 0 )
    *(uint32_t *)(v3 + 4) = pArg2;  // 写字段 v3+4（pHostObj） ← pArg2
  *(uint32_t *)(result + 4) = pArg2[1];  // 写字段 result+4（pHostObj） ← pArg2[1]
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // 写字段 fld_e1+4（pHostObj） ← result
    *(uint32_t *)(result + 8) = pArg2;  // 写字段 result+8（nSkillRec8） ← pArg2
    pArg2[1] = result;
  }
  else
  {
    v5 = (uint32_t *)pArg2[1];
    if ( pArg2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else
      *v5 = result;
    *(uint32_t *)(result + 8) = pArg2;  // 写字段 result+8（nSkillRec8） ← pArg2
    pArg2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0C60 sub_4B0C60 —— RB 树迭代器自增（中序后继）
//   右子非 nil 取右子树最左；否则沿父上溯至不为右子处；原地更新 *this（+25 nil 判定）。
// ------------------------------------------------------------
int */*thiscall*/ sub_4B0C60(int *this)  // sub_4B0C60 —— RB 树迭代器自增（中序后继）
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
// 0x4B0CC0 sub_4B0CC0 —— RB 树迭代器自减（中序前驱）
//   nil 头节点时返回 header 右极值(+8)（end() 退化）；否则左子非空取左子树最右，反之沿父上溯。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0CC0(void *this)  // sub_4B0CC0 —— RB 树迭代器自减（中序前驱）
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 25) != 0 )  // this+100〔bEnchantDone(推断)〕
  {
    result = v1[2];
    *(uint32_t *)this = result;  // *this = result
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
          *(uint32_t *)this = result;  // *this = result
          result = *(uint32_t *)(result + 4);  // 读字段 result = result+4（pHostObj）
        }
        while ( *(uint8_t *)(result + 25) == 0 );  // 写字段 result+25 ← = 0 )
        if ( *(uint8_t *)(result + 25) == 0 )
          *(uint32_t *)this = result;  // *this = result
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 25) == 0; result = *(uint32_t *)(result + 8) )  // 读字段 result = v3+8（nSkillRec8）
        v3 = result;
      *(uint32_t *)this = v3;  // *this = v3
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0D20 sub_4B0D20 —— 双字段乘积取值
//   返回 +984 与 +998 两字段之积（各自经 ·0x41A5E0 取值，float 结果）。【推断】
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4B0D20(void *this)  // sub_4B0D20 —— 结果 = 双字段乘积取值
{
  int pThis_3D8; // [esp+8h] [ebp-4h]

  pThis_3D8 = sub_41A5E0((unsigned int)this + 984);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_3D8 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 998)));  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4B0D60 sub_4B0D60 —— 计时子对象初始化（时钟域 2）
//   挂 off_6C2B88 虚表(+4)、绑定时钟域 2（·0x699070），清零 +8..+40 各字段并置 +16/+36 为 1。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4B0D60(uint8_t *this)  // sub_4B0D60 —— 计时子对象初始化（时钟域 2）
{
  char *pThis_4; // esi

  pThis_4 = this + 4;  // this+4 宿主对象
  *(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *((uint32_t *)this + 1) = &off_6C2B88;  // 写字段 this[1]（宽4字节）
  *((uint32_t *)this + 3) = 0;  // 写字段 this[3]（宽4字节）
  *(this + 16) = 1;  // 写字段 this+16（nChannelTypeSel） ← 1
  *(this + 18) = 0;  // 写字段 this+18（bDragChild） ← 0
  *(this + 17) = 0;  // 写字段 this+17（bEnable） ← 0
  *((uint32_t *)this + 7) = 0;  // 写字段 this+7（uPathTerm）
  *((uint32_t *)this + 6) = 0;  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 5) = 0;  // 写字段 this[5]（宽4字节）
  *(uint32_t *)this = 0;  // *this = 0
  sub_699070(2);  // 【clock_bind_domain(clk, newDomainId)】
  pThis_4[13] = 0;  // pThis_4=this+4 宿主对象
  pThis_4[14] = 0;  // pThis_4=this+4 宿主对象
  *((uint32_t *)this + 8) = 0;  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *(this + 36) = 1;  // 写字段 this+36（nStateWord36） ← 1
  return this;
}



// ------------------------------------------------------------
// 0x4B0DE0 sub_4B0DE0 —— 子对象虚表复位（IObject）
//   +4 挂 nengine::IObject 虚表、+8 清零（子对象析构级联用）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B0DE0(int this)  // sub_4B0DE0 —— 子对象虚表复位（IObject）
{
  *(uint32_t *)(this + 4) = &nengine::IObject::`vftable';  // 写字段 this+4（pHostObj） ← &nengine::IObject::`vftable
  *(uint8_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
}



// ------------------------------------------------------------
// 0x4B0DF0 sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
// ------------------------------------------------------------
void /*cdecl*/ sub_4B0DF0(int *pDwArg1, int *pDwArg2)  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
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
      v13 = sub_4924C0(pDwArg12, v11);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      v12 = sub_4924C0(pDwArg22, v11++);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(uint32_t *)(v12 + 48) = *(uint32_t *)(v13 + 48);  // 写字段 v12+48（pCmdVecBegin48） ← *(uint32_t *)(v13 + 48)
      if ( v11 >= v8 )
        break;
      pDwArg12 = pDwArg1;
      pDwArg22 = pDwArg2;
    }
  }
}



// ------------------------------------------------------------
// 0x4B0EC0 sub_4B0EC0 —— 表记录字符串取值（28 字节/条）
//   由 ·0x4CE8A0 取表基址，按 28 字节/条 取第 nArg2 条内嵌 std::string 数据指针（长度 <0x10 为内联缓冲）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B0EC0(int nArg1, int nArg2)  // sub_4B0EC0 —— 结果 = 表记录字符串取值（28 字节/条）
{
  int result; // eax
  int v3; // eax

  result = sub_4CE8A0(nArg1);  // sub_4CE8A0 —— 调用 sub_4CE8A0
  if ( result != 0 )
  {
    v3 = 28 * nArg2 + result + 4;
    if ( *(uint32_t *)(v3 + 24) < 0x10u )
      return v3 + 4;  // 返回内嵌子对象/缓冲指针（v3+4）
    else
      return *(uint32_t *)(v3 + 4);  // 返回字段 v3+4（pHostObj）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0F00 sub_4B0F00 —— 部件槽组件获取或按裸身资源构造
//   取槽 pArg2 组件(+6468+4*槽)；为空且裸身资源表 ·0x4B0210(job,槽) 命中（非 0xFFFF）时经 vt+1084/vt+784 构造挂装。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0F00(int *this, int pArg2)  // sub_4B0F00 —— 部件槽组件获取或按裸身资源构造
{
  int result; // eax
  int v4; // ecx
  int v5; // edi
  int v6; // eax

  result = *(this + pArg2 + 1617);
  if ( result == 0 )
  {
    result = sub_4B0210(*(this + 1787), pArg2);  // sub_4B0210 —— ★裸身身体资源 id 表（job×growtype）
    if ( result != 0xFFFF )
    {
      v5 = *this;
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1084))(this, v4);  // 虚调用 vt+1084（this 虚表槽）
      return (*(int (/*thiscall*/ **)(int *, int))(v5 + 784))(this, v6);  // 虚函数调用 槽+784
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B0F50 sub_4B0F50 —— 第二组槽位组件懒创建（sub_522300）
//   取槽缓存(+7516+4*槽)；为空且裸身资源命中时用 ·0x522300 创建，并按其 vt+172 数据 +18 设置 vt+192。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_4B0F50(int *this, int pArg2)  // sub_4B0F50 —— 第二组槽位组件懒创建（sub_522300）
{
  void *fld_e1787; // eax
  int pObj; // eax
  int v5; // eax
  int v6; // eax

  fld_e1787 = (void *)sub_4B0210(*(this + 1787), pArg2);  // sub_4B0210 —— ★裸身身体资源 id 表（job×growtype）
  if ( *(this + pArg2 + 1879) == 0 && fld_e1787 != (void *)0xFFFF )
  {
    pObj = sub_522300(fld_e1787, 0, 0, 0, -1, 1);  // sub_522300 —— 存 ★ PO 工厂分发器
    *(this + pArg2 + 1879) = pObj;
    if ( pObj != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 172))(pObj);  // 虚调用 vt+172（pObj 虚表槽）
      v6 = sub_41A5E0(v5 + 18);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
      (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + pArg2 + 1879) + 192))(*(this + pArg2 + 1879), v6);  // 虚函数调用 槽+192
    }
  }
  return *(this + pArg2 + 1879);
}



// ------------------------------------------------------------
// 0x4B0FD0 sub_4B0FD0 —— RB 树左旋（右子提升）
//   与 ·0x4B0C00 镜像：以 pArg2 为轴左旋，右子(+8)提升。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B0FD0(uint32_t *this, int pArg2)  // sub_4B0FD0 —— RB 树左旋（右子提升）
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pArg2 + 8) = *result;  // 写字段 pArg2+8（nSkillRec8） ← *result
  if ( *(uint8_t *)(*result + 25) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // 写字段 fld_e1+4（pHostObj） ← result
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // 写字段 pArg2+4（pHostObj） ← result
  }
  else
  {
    v4 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( pArg2 == *v4 )
      *v4 = result;
    else
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // 写字段 pArg2+4（pHostObj） ← result
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B1030 sub_4B1030 —— IRDAppendage 基类构造
//   挂 IRDAppendage 虚表，初始化 +4 子对象(·0x4B0D60)，再经 ·0x5F6610/·0x5F6750 建立动画接口。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4B1030(uint8_t *this)  // sub_4B1030 —— IRDAppendage 基类构造
{
  *(uint32_t *)this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  sub_4B0D60(this + 4);  // sub_4B0D60 —— 计时子对象初始化（时钟域 2）
  sub_5F6610(this);
  sub_5F6750(this);
  return this;
}



// ------------------------------------------------------------
// 0x4B10B0 sub_4B10B0 —— 部位资源 id setter（+48）
//   写 +48 字段（部位动画/资源 id，见 ·0x4B0DF0 的 +48 传递）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B10B0(uint32_t *this, int nArg2)  // sub_4B10B0 —— 部位资源 id setter（+48）
{
  *(this + 12) = nArg2;  // 写字段 this+12（nSkillRec12） ← nArg2
  return nArg2;
}



// ------------------------------------------------------------
// 0x4B10C0 sub_4B10C0 —— +48 getter
//   读 +48（部位动画/资源 id）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B10C0(uint32_t *this)  // 实现：+48 getter
{
  return *(this + 12);  // 返回字段 this+48（pCmdVecBegin48）
}



// ------------------------------------------------------------
// 0x4B10D0 sub_4B10D0 —— 外观状态位 setter（+52）
//   写字节 +52（外观状态位，见 ·0x4B05D0 族）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B10D0(uint8_t *this, char pszArg2)  // sub_4B10D0 —— 外观状态位 setter（+52）
{
  *(this + 52) = pszArg2;  // 写字段 this+52（bAuraState） ← pszArg2
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4B10E0 sub_4B10E0 —— +52 getter
//   读字节 +52（外观状态位）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B10E0(uint8_t *this)  // 实现：+52 getter
{
  return *(this + 52);  // 返回字段 this+208（nField208）
}



// ------------------------------------------------------------
// 0x4B10F0 sub_4B10F0 —— +53 getter
//   读字节 +53（外观状态位族）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B10F0(uint8_t *this)  // 实现：+53 getter
{
  return *(this + 53);  // 返回字段 this+212（nField212）
}



// ------------------------------------------------------------
// 0x4B1100 sub_4B1100 —— +54 getter
//   读字节 +54（外观状态位族）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B1100(uint8_t *this)  // 实现：+54 getter
{
  return *(this + 54);  // 返回字段 this+216（bField216）
}



// ------------------------------------------------------------
// 0x4B1110 sub_4B1110 —— +56 getter
//   读 +56（外观状态位族，int）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1110(uint32_t *this)  // 实现：+56 getter
{
  return *(this + 14);  // 返回字段 this+56（pCmdVecCap56）
}



// ------------------------------------------------------------
// 0x4B1120 sub_4B1120 —— IRDAppendage 析构收尾
//   挂 IRDAppendage 虚表 → ·0x5F6640 释放，再将 +8 子对象虚表重置为 nengine::IObject、+12 清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1120(uint32_t *this)  // sub_4B1120 —— IRDAppendage 析构收尾
{
  int result; // eax

  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640();  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写字段 this+2 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  return result;
}



// ------------------------------------------------------------
// 0x4B1170 sub_4B1170 —— 删除器（析构+释放）
//   调 ·0x4B1120 析构；pszArg2 低位为 1 时 j__free 释放内存。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B1170(uint32_t *Block, char pszArg2)  // sub_4B1170 —— 删除器（析构+释放）
{
  sub_4B1120(Block);  // sub_4B1120 —— IRDAppendage 析构收尾
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4B11A0 sub_4B11A0 —— CNArmorMastery 构造（参数=职业）
//   基类 ·0x4B1030 → 挂 CNArmorMastery 虚表 → ·0x5F6E50/·0x5F6ED0(nArg2=职业)。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4B11A0(uint8_t *this, int nArg2)  // sub_4B11A0 —— CNArmorMastery 构造（参数=职业）
{
  sub_4B1030(this);  // sub_4B1030 —— IRDAppendage 基类构造
  *(uint32_t *)this = &CNArmorMastery::`vftable';  // 构造装配 vftable：CNArmorMastery
  sub_5F6E50(this);
  sub_5F6ED0(nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x4B1200 sub_4B1200 —— IRDAppendage vmt4（更新转发）
//   ·0x5F66C0 预处理后转 ·0x5F6FB0 更新（RTTI 对应 IRDAppendage vmt4）。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1200(void *this)  // sub_4B1200 —— IRDAppendage vmt4（更新转发）
{
  sub_5F66C0();  // 【IRDAppendage__vmt4】
  return sub_5F6FB0(this);
}



// ------------------------------------------------------------
// 0x4B1220 sub_4B1220 —— 删除器（析构+释放）
//   调 ·0x4B1250 析构；pszArg2 低位为 1 时 j__free 释放内存。
// ------------------------------------------------------------
void */*thiscall*/ sub_4B1220(void *Block, char pszArg2)  // sub_4B1220 —— 删除器（析构+释放）
{
  sub_4B1250();  // sub_4B1250 —— CNArmorMastery 析构
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4B1250 sub_4B1250 —— CNArmorMastery 析构
//   虚表 CNArmorMastery → nullsub_3 → 回退 IRDAppendage/nengine::IObject 并 ·0x5F6640、+12 清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1250(uint32_t *this)  // sub_4B1250 —— CNArmorMastery 析构
{
  int result; // eax

  *this = &CNArmorMastery::`vftable';  // 构造装配 vftable：CNArmorMastery
  nullsub_3(this);
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *(this + 2) = &nengine::IObject::`vftable';  // 写字段 this+2 ← &nengine::IObject::`vftable
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  return result;
}



// ============================================================
// §C 0x4B12B0-0x4B15E0  事件分发
// ============================================================
// ------------------------------------------------------------
// 0x4B12B0 sub_4B12B0 —— 事件分发（音效 sub_422E70/43BEE0、sub_4BF300）
// ------------------------------------------------------------
char /*userpurge*/ sub_4B12B0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, char pszArg3)  // 实现：事件分发（音效 sub_422E70/43BEE0、sub_4BF300）
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

  v4 = *((uint8_t *)pArg1 + 8052);  // 读字段 v4 = pArg1[8052]
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = pszArg3;
  if ( v4 != pszArg3 )
  {
    *((uint8_t *)pArg1 + 8052) = pszArg3;  // 写字段 pArg1[8052]（宽1字节）
    v6 = pArg1[78];
    if ( pszArg3 != 0 )
    {
      if ( v6 < 0x10 )
        v7 = pArg1 + 73;  // 计算 v7 = pArg1 + 73
      else
        v7 = (uint32_t *)pArg1[73];
      off_77F3FC(aS_5, v7);  // off_77F3FC —— 日志打印（printf 风格）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg2) != 0 )  // 虚调用 vt+308（pArg1）是否本地玩家
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560（pArg1 虚表槽）
        v8 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        v9 = sub_422E70(858);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
        sub_43BEE0(v8, v9, -13444046, 0, -1);  // sub_43BEE0 —— 【播报上屏】
        v10 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        v11 = sub_422E70(859);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
        sub_43BEE0(v10, v11, -13444046, 0, -1);  // sub_43BEE0 —— 【播报上屏】
        v12 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        v13 = sub_422E70(860);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
        sub_43BEE0(v12, v13, -13444046, 0, -1);  // sub_43BEE0 —— 【播报上屏】
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 0, 0, 0, 0, 0);  // 虚调用 vt+876（pArg1）双段位移
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);  // 虚调用 vt+876（pArg1）双段位移
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 2, 0, 0, 0, 0, 0);  // 虚调用 vt+876（pArg1）双段位移
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*pArg1 + 112))(pArg1, -10000, -10000, 0);  // 虚调用 vt+112（pArg1）坐标三元组写入
      if ( pArg1[78] < 0x10u )
        v14 = pArg1 + 73;  // 计算 v14 = pArg1 + 73
      else
        v14 = (uint32_t *)pArg1[73];
      v15 = (const char *)sub_422E70(861);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      sprintf(Buffer, v15, v14);  // 调 格式化到缓冲
      return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
    }
    else
    {
      if ( v6 < 0x10 )
        v16 = pArg1 + 73;  // 计算 v16 = pArg1 + 73
      else
        v16 = (uint32_t *)pArg1[73];
      off_77F3FC(aS_6, v16);  // off_77F3FC —— 日志打印（printf 风格）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308（pArg1）是否本地玩家
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*pArg1 + 108))(pArg1, pArg1[2014], pArg1[2015], pArg1[2016]);  // 虚调用 vt+108（pArg1 虚表槽）
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);  // 虚调用 vt+560（pArg1 虚表槽）
        for ( i = 0; i < 4; ++i )  // 遍历计次循环（i < 4）
          sub_4BF300(i, 1);  // sub_4BF300 —— 槽写侧（+64 + 索引）
        v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);  // 虚调用 vt+80（pArg1）读 4 字节
        sub_424A40(*(uint32_t **)(v18 + 132), (int)pArg1);  // sub_424A40 —— 锚定角色 setter 写 +13 = a2；+11 容器存在且 a2 非空时 sub_48C500 登记
      }
      if ( pArg1[78] < 0x10u )
        v19 = pArg1 + 73;  // 计算 v19 = pArg1 + 73
      else
        v19 = (uint32_t *)pArg1[73];
      v20 = (const char *)sub_422E70(862);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      sprintf(Buffer, v20, v19);  // 调 格式化到缓冲
      return sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B1550 sub_4B1550 —— 指针容器区间拷贝构造
//   对 [pDwArg1,pDwArg2) 逐元素先置空再 ·0x41B0D0 复制构造写入 pDwArg3，返回尾指针；v7 低字节为展开状态标记。
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_4B1550(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)  // sub_4B1550 —— 指针容器区间拷贝构造
{
  unsigned int **pDwArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pDwArg32 = pDwArg3;
  v6[4] = v6;
  v6[3] = pDwArg3;
  v7 = 0;
  while ( pDwArg1 != pDwArg2 )  // 循环直到 pDwArg1 != pDwArg2
  {
    LOBYTE(v7) = 1;
    if ( pDwArg32 != nullptr )
    {
      *pDwArg32 = nullptr;
      sub_41B0D0(pDwArg32, pDwArg1);  // sub_41B0D0 —— 驻留句柄赋值（旧引用释放 + 新引用 ++）
    }
    ++pDwArg32;  // 计数自增 pDwArg32
    LOBYTE(v7) = 0;
    ++pDwArg1;  // 计数自增 pDwArg1
  }
  return pDwArg32;
}



// ============================================================
// §D 0x4B15E0-0x4B1C80  avatar 部件管理
// ============================================================
// ------------------------------------------------------------
// 0x4B15E0 sub_4B15E0 —— avatar 配置记录拷贝（目标 +16 起）
//   首字段直拷，中段经 ·0x4B1630，尾字段(源 +32/+36/+40) 复制到目标 +36/+40/+44。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B15E0(uint32_t *this, int pArg2)  // sub_4B15E0 —— avatar 配置记录拷贝（目标 +16 起）
{
  uint32_t *pThis_1; // esi
  int savedregs; // [esp+0h] [ebp+0h] BYREF

  savedregs = (int)&savedregs;
  pThis_1 = this + 1;
  *(this + 1) = *(uint32_t *)pArg2;  // 写字段 this+1 ← *(uint32_t *)pArg2
  sub_4B1630(pArg2 + 4);  // sub_4B1630 —— 记录字段组拷贝（+4..+24）
  pThis_1[8] = *(uint32_t *)(pArg2 + 32);  // pArg2+32〔nHeight(推断)〕
  *((uint8_t *)pThis_1 + 36) = *(uint8_t *)(pArg2 + 36);  // 写字段 pThis_1+36（nStateWord36）
  pThis_1[10] = *(uint32_t *)(pArg2 + 40);  // pArg2+40〔bStateSub40(推断)〕
  return pThis_1;
}



// ------------------------------------------------------------
// 0x4B1630 sub_4B1630 —— 记录字段组拷贝（+4..+24）
//   逐字段拷贝 +4/+8/+12/+13/+14/+16/+20/+24（两结构同布局）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1630(int this, int pArg2)  // sub_4B1630 —— 记录字段组拷贝（+4..+24）
{
  *(uint8_t *)(this + 4) = *(uint8_t *)(pArg2 + 4);  // 写字段 this+4（pHostObj） ← *(uint8_t *)(pArg2 + 4)
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);  // 写字段 this+8（nSkillRec8） ← *(uint32_t *)(pArg2 + 8)
  *(uint8_t *)(this + 12) = *(uint8_t *)(pArg2 + 12);  // 写字段 this+12（nSkillRec12） ← *(uint8_t *)(pArg2 + 12)
  *(uint8_t *)(this + 13) = *(uint8_t *)(pArg2 + 13);  // 写字段 this+13 ← *(uint8_t *)(pArg2 + 13)
  *(uint8_t *)(this + 14) = *(uint8_t *)(pArg2 + 14);  // 写字段 this+14 ← *(uint8_t *)(pArg2 + 14)
  *(uint32_t *)(this + 16) = *(uint32_t *)(pArg2 + 16);  // 写字段 this+16（nChannelTypeSel） ← *(uint32_t *)(pArg2 + 16)
  *(uint32_t *)(this + 20) = *(uint32_t *)(pArg2 + 20);  // 写字段 this+20（nPage） ← *(uint32_t *)(pArg2 + 20)
  *(uint32_t *)(this + 24) = *(uint32_t *)(pArg2 + 24);  // 写字段 this+24（nPageMax） ← *(uint32_t *)(pArg2 + 24)
  return this;
}



// ------------------------------------------------------------
// 0x4B1670 sub_4B1670 —— avatar 集合初始化（+252；sub_4F3460/47E8C0/6569D0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1670(uint8_t *this)  // sub_4B1670 —— 结果 = avatar 集合初始化（+252；sub_4F3460/47E8C0/6569D0）
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

  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 12))(this);  // 虚调用 vt+12（this 虚表槽）
  if ( (uint8_t *)dword_8F7C04 == this )  // dword_8F7C04（本地玩家对象）
  {
    sub_4F3460();  // sub_4F3460 —— 投技对象初始化
    sub_47E8C0();  // 调 dword_99FC34 槽 vector 逐对象调 vt+8（对象重置/清理）
  }
  *(this + 7729) = 0;  // 写字段 this+7729 ← 0
  sub_6569D0(this + 124);  // sub_6569D0 —— (this+4)
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 780))(this);  // 虚调用 vt+780（this 虚表槽）
  sub_53FDD0(*((uint32_t *)this + 1574));
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1156))(this);  // 虚调用 vt+1156（this 虚表槽）
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 虚调用 vt+676（this）队伍编号刷新
  v2 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  if ( v2 == 4 || v2 == 6 )
  {
    v3 = *(uint32_t *)this;
    pThis_2E4 = (*(int (/*stdcall*/ **)(uint32_t, int))(*(uint32_t *)this + 740))(0, 1);  // 虚调用 vt+740（this 虚表槽）
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v3 + 732))(this, pThis_2E4);  // 调虚槽 +732：CNMapObject__vmt2DC
    v5 = *(uint32_t *)this;
    pThis_2F4 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 756))(this, 1);  // 虚调用 vt+756（this 虚表槽）
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v5 + 748))(this, pThis_2F4);  // 调虚槽 +748：[RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObj…
  }
  else
  {
    v7 = *(uint32_t *)this;
    pThis_428 = (*(int (/*stdcall*/ **)(uint32_t, int))(*(uint32_t *)this + 1064))(0, 1);  // 虚调用 vt+1064（this 虚表槽）
    pThis_2E42 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 740))(this);  // 虚调用 vt+740（this 虚表槽）
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v7 + 732))(this, pThis_2E42 * pThis_428 / 100);  // 调虚槽 +732：CNMapObject__vmt2DC
    v10 = *(uint32_t *)this;
    pThis_4282 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 1064))(this, 1);  // 虚调用 vt+1064（this 虚表槽）
    pThis_2F42 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 756))(this);  // 虚调用 vt+756（this 虚表槽）
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v10 + 748))(this, pThis_2F42 * pThis_4282 / 100);  // 调虚槽 +748：[RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObj…
  }
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 720))(this, 0);  // 虚调用 vt+720（this 虚表槽）
  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 604))(this, 1);  // 虚调用 vt+604（this）收招例程
  v13 = *(uint32_t *)this;
  *(this + 7093) = 0;  // 写字段 this+7093 ← 0
  (*(void (/*thiscall*/ **)(uint8_t *, int, int))(v13 + 252))(this, 3, -1);  // 虚函数调用 槽+252：时刻槽写入（-1 语义为推进并释放）
  return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 612))(this, 0, 0);  // 虚调用 vt+612（this）拆分/脱离
}



// ------------------------------------------------------------
// 0x4B17B0 sub_4B17B0 —— 卸下槽部件（观察者 vmt314）
//   槽空返回 0；经 ·0x52DBC0 装备观察者卸下后移除动画/渲染项(vt+1152/+1156)，遍历 vt+248 的
//   124 字节子项经 vt+1076 解绑，末尾 ·0x484D00 汇总槽统计；返回被卸对象（与缓存槽相同则 0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B17B0(uint32_t *this, int pArg2)  // sub_4B17B0 —— 卸下槽部件（观察者 vmt314）
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
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1152))(this);  // 虚调用 vt+1152（this）目标绑定
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1156))(this);  // 虚调用 vt+1156（this 虚表槽）
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
      sub_47E4F0();  // sub_47E4F0 —— 调用 sub_47E4F0
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 248))(pObj);  // 虚调用 vt+248（pObj 虚表槽）
    for ( i = *(uint32_t *)(v6 + 4); i != *(uint32_t *)(v6 + 8); i += 124 )  // 读字段 i = v6+4（pHostObj）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int))(*this + 1076))(this, this + 1803, i + 72);  // 虚调用 vt+1076（this 虚表槽）
    sub_484D00((int *)dword_8F852C);  // sub_484D00 —— 槽汇总统计（累加各对象虚表 +36 值）
    pArg22 = pArg2;
    pObj = pObj2;
  }
  return pObj == *(this + pArg22 + 1879) ? 0 : pObj;
}



// ------------------------------------------------------------
// 0x4B1870 sub_4B1870 —— 当前项 +7632 数组取值（缺省 4）
//   需 +6500 组件存在且 vt+1096 索引有效；越界返回缺省 4。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1870(uint32_t *this)  // sub_4B1870 —— 当前项 +7632 数组取值（缺省 4）
{
  unsigned int fld_e1908; // eax
  int v3; // edx

  if ( *(this + 1625) != 0  // this+6500〔nWeaponItemId〕
    && (fld_e1908 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this), (v3 = *(this + 1908)) != 0)  // 虚调用 vt+1096（this）枪种分派
    && (*(this + 1909) - v3) >> 2 > fld_e1908 )  // this+7636〔nPosWinY〕
  {
    return *(uint32_t *)(*(this + 1908) + 4 * fld_e1908);  // 返回 读 this+1908
  }
  else
  {
    return 4;
  }
}



// ------------------------------------------------------------
// 0x4B18C0 sub_4B18C0 —— +7648 数组项非零判定
//   与 ·0x4B1870 同结构，改判 +7648 数组项是否非 0（布尔）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4B18C0(uint32_t *this)  // 实现：+7648 数组项非零判定
{
  unsigned int fld_e1912; // eax
  int v3; // edx
  bool result; // al

  result = *(this + 1625) != 0  // this+6500〔nWeaponItemId〕
        && (fld_e1912 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this), (v3 = *(this + 1912)) != 0)  // 虚调用 vt+1096（this）枪种分派
        && (*(this + 1913) - v3) >> 2 > fld_e1912
        && *(uint32_t *)(*(this + 1912) + 4 * fld_e1912) != 0;
  return result;
}



// ------------------------------------------------------------
// 0x4B1910 sub_4B1910 —— 当前项 +7664 数组取值（缺省 0）
//   与 ·0x4B1870 同结构，数组 +7664，越界缺省 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1910(uint32_t *this)  // sub_4B1910 —— 当前项 +7664 数组取值（缺省 0）
{
  unsigned int fld_e1916; // eax
  int v3; // edx

  if ( *(this + 1625) != 0  // this+6500〔nWeaponItemId〕
    && (fld_e1916 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this), (v3 = *(this + 1916)) != 0)  // 虚调用 vt+1096（this）枪种分派
    && (*(this + 1917) - v3) >> 2 > fld_e1916 )  // this+7668〔nSwitchGuardT〕
  {
    return *(uint32_t *)(*(this + 1916) + 4 * fld_e1916);  // 返回 读 this+1916
  }
  else
  {
    return 0;
  }
}



// ------------------------------------------------------------
// 0x4B1950 sub_4B1950 —— 技能施展 + 特效与操作码 17 封包
//   查技能表(·0x4CE8A0) 取参数与技能名(·0x41ACF0)，vt+580 施展；177 号属性>0 时附加特效
//   (·0x47EFD0) 并发送操作码 17 封包(dword_8F8520)；技能缺失/不可用时经 ·0x77F3FC 提示
//   （aMaster/byte_6F5FDC）并返回 -1。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1950(uint32_t *this)  // sub_4B1950 —— 技能施展 + 特效与操作码 17 封包
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

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    fld_e1954 = sub_4CE8A0(*(this + 1954));  // sub_4CE8A0 —— 调用 sub_4CE8A0
    if ( fld_e1954 != 0 )
    {
      v4 = *(int **)(fld_e1954 + 124);
      v17 = *v4;
      if ( v4 != nullptr && (unsigned int)((*(uint32_t *)(fld_e1954 + 128) - (int)v4) >> 2) > 1 )
        v5 = v4[1];
      else
        v5 = 0;
      v6 = *(uint32_t *)(fld_e1954 + 140);  // 读字段 v6 = fld_e1954+140（nAdd140）
      v7 = 0;
      if ( v6 != 0 && (*(uint32_t *)(fld_e1954 + 144) - v6) >> 2 != 0 )
      {
        v8 = *(uint32_t *)dword_8F84E4;
        v9 = sub_41ACF0(*(unsigned int ***)(fld_e1954 + 140));  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        v7 = (*(int (/*thiscall*/ **)(int, const CHAR *))(v8 + 4))(dword_8F84E4, v9);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 699000/…
      }
      if ( *(this + 1953) == 2 )  // this+7812〔nSubStateA(推断)〕
        fld_e1962 = 0;
      else
        fld_e1962 = *(this + 1962);  // 读字段 fld_e1962 = this+1962
      fld_e1961 = (*(int (/*thiscall*/ **)(uint32_t *, int, int, int, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 虚调用 vt+580（this）音效/技能播放(12参)
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
      if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 177) > 0  // 虚调用 vt+1140（this）读技能表
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1312))(this, 177) != 0 )  // 虚调用 vt+1312（this 虚表槽）
      {
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 388))(this);  // 虚调用 vt+388（this）攻击计算
        v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 177);  // 虚调用 vt+1140（this）读技能表
        v13 = (char *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 177);  // 虚调用 vt+1160（this）读技能表(变体)
        v14 = sub_47EFD0(v13, 0.0, v12, v11, v11, 11);  // 调 技能表槽位设置（越界打 aCriticalError_8；+87 处 14 字节/项表）(推断)
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 17, 2);  // 虚调用 vt+8（dword_8F8520 虚表槽）
        v15 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 虚调用 vt+1220（dword_8F7C04 虚表槽）
        (*(void (/*thiscall*/ **)(int, int))(v15 + 36))(dword_8F8520, v16);  // dword_8F8520 —— 虚表 +120 调用
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, fld_e1961);  // 虚调用 vt+36（dword_8F8520 虚表槽）
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v14);  // 虚调用 vt+36（dword_8F8520 虚表槽）
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
      }
      return fld_e1961;
    }
    else
    {
      off_77F3FC((char *)&byte_6F5FDC, *(this + 1954));  // off_77F3FC —— 日志打印（printf 风格）
      return -1;
    }
  }
  else
  {
    off_77F3FC(aMaster);  // off_77F3FC —— 日志打印（printf 风格）
    return -1;
  }
}



// ------------------------------------------------------------
// 0x4B1B20 sub_4B1B20 —— avatar 集合复位（无缩放版）
//   与 ·0x4B1670 同构（差异：不含尺寸缩放分支与 +7729 重置），收尾 vt+252(3,-1)/vt+612(0,0)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1B20(uint32_t *this)  // sub_4B1B20 —— avatar 集合复位（无缩放版）
{
  int v2; // edx

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 12))(this);  // 虚调用 vt+12（this 虚表槽）
  if ( (uint32_t *)dword_8F7C04 == this )  // dword_8F7C04（本地玩家对象）
  {
    sub_4F3460();  // sub_4F3460 —— 投技对象初始化
    sub_47E8C0();  // 调 dword_99FC34 槽 vector 逐对象调 vt+8（对象重置/清理）
  }
  sub_6569D0(this + 31);  // sub_6569D0 —— (this+4)
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 780))(this);  // 虚调用 vt+780（this 虚表槽）
  sub_53FDD0(*(this + 1574));
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1156))(this);  // 虚调用 vt+1156（this 虚表槽）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);  // 虚调用 vt+676（this）队伍编号刷新
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 604))(this, 1);  // 虚调用 vt+604（this）收招例程
  v2 = *this;
  *((uint8_t *)this + 7093) = 0;  // 写字段 this[7093]（宽1字节）
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v2 + 252))(this, 3, -1);  // 虚函数调用 槽+252：时刻槽写入（-1 语义为推进并释放）
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);  // 虚调用 vt+612（this）拆分/脱离
}



// ------------------------------------------------------------
// 0x4B1BA0 sub_4B1BA0 —— map lower_bound（键在 +12）
//   返回 >= 键的首节点（+0 左/+8 右/+25 nil）；未命中回 header(this+4)。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4B1BA0(int **this, int **pDwArg2, uint32_t *uArg3)  // sub_4B1BA0 —— map lower_bound（键在 +12）
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v4 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *((uint8_t *)v4 + 25) == 0 )  // 当 *((uint8_t *)v4 + 25) == 0 循环
  {
    if ( v4[3] >= *uArg3 )
    {
      fld_e1 = v4;  // fld_e1=this+4 宿主对象
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( fld_e1 == *(this + 1) || *uArg3 < fld_e1[3] )  // fld_e1=this+4 宿主对象
  {
    *pDwArg2 = *(this + 1);  // this+4〔宿主对象〕
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = fld_e1;  // fld_e1=this+4 宿主对象
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4B1C10 sub_4B1C10 —— 容器释放复位（缺省 300）
//   free(+4) 后清零 +4..+16 头字段，+20 置缺省 300。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B1C10(int this)  // sub_4B1C10 —— 容器释放复位（缺省 300）
{
  if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
    j__free(*(void **)(this + 4));  // 释放堆块
  *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
  *(uint32_t *)(this + 20) = 300;  // 写字段 this+20（nPage） ← 300
}



// ------------------------------------------------------------
// 0x4B1C40 sub_4B1C40 —— 14 字节表按 1 基索引取值
//   基址 *(this+79)、14 字节/条；nArg2==-1 时改用 +510 当前值。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B1C40(uint32_t *this, int nArg2)  // sub_4B1C40 —— 14 字节表按 1 基索引取值
{
  int pThis_1FE; // eax

  pThis_1FE = nArg2;
  if ( nArg2 == -1 )
    pThis_1FE = sub_41A5E0((unsigned int)this + 510);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return sub_41A5E0(*(this + 79) + 14 * (pThis_1FE - 1));  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4B1C80 sub_4B1C80 —— 部位参数组下发（+40/+44/+56 → sub_4B0DF0 重载动画）
// ------------------------------------------------------------
void /*cdecl*/ sub_4B1C80(int pArg1, int pArg2, int **pDwArg3, int **pDwArg4)  // sub_4B1C80 —— 部位参数组下发（+40/+44/+56 → sub_4B0DF0 重载动画）
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

  sub_4B0DF0(*(int **)pArg1, *(int **)pArg2);  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  sub_4B0DF0(*(int **)(pArg1 + 4), *(int **)(pArg2 + 4));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  sub_4B0DF0(*(int **)(pArg1 + 8), *(int **)(pArg2 + 8));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  v6 = pArg2 - pArg1;  // 计算 v6 = pArg2 - pArg1
  v7 = (int **)(pArg1 + 12);  // pArg1+12〔nSkillRec12(推断)〕
  v17 = pArg2 - pArg1;  // 计算 v17 = pArg2 - pArg1
  v18 = 2;
  while ( 1 )
  {
    sub_4B0DF0(*v7, *(int **)((char *)v7 + v6));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
    ++v7;  // 计数自增 v7
    if ( --v18 == 0 )
      break;
    v6 = v17;
  }
  sub_4B0DF0(*(int **)(pArg1 + 20), *(int **)(pArg2 + 20));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  sub_4B0DF0(*(int **)(pArg1 + 24), *(int **)(pArg2 + 24));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  sub_4B0DF0(*(int **)(pArg1 + 28), *(int **)(pArg2 + 28));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  sub_4B0DF0(*(int **)(pArg1 + 32), *(int **)(pArg2 + 32));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  for ( i = 0; ; ++i )
  {
    v9 = *(uint32_t *)(pArg1 + 40);  // 读字段 v9 = pArg1+40（bStateSub40）
    if ( v9 == 0 )
      break;
    if ( i >= (*(uint32_t *)(pArg1 + 44) - v9) >> 2 )  // pArg1+44〔nExpireMs(推断)〕
      break;
    v10 = *(uint32_t *)(pArg2 + 40);  // 读字段 v10 = pArg2+40（bStateSub40）
    if ( v10 == 0 || i >= (*(uint32_t *)(pArg2 + 44) - v10) >> 2 )
      break;
    sub_4B0DF0(*(int **)(4 * i + *(uint32_t *)(pArg1 + 40)), *(int **)(4 * i + *(uint32_t *)(pArg2 + 40)));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  }
  for ( j = 0; ; ++j )
  {
    v12 = *(uint32_t *)(pArg1 + 56);  // 读字段 v12 = pArg1+56（pCmdVecCap56）
    if ( v12 == 0 )
      break;
    if ( j >= (*(uint32_t *)(pArg1 + 60) - v12) >> 2 )  // pArg1+60〔nFadeValue60(推断)〕
      break;
    v13 = *(uint32_t *)(pArg2 + 56);  // 读字段 v13 = pArg2+56（pCmdVecCap56）
    if ( v13 == 0 || j >= (*(uint32_t *)(pArg2 + 60) - v13) >> 2 )
      break;
    sub_4B0DF0(*(int **)(4 * j + *(uint32_t *)(pArg1 + 56)), *(int **)(4 * j + *(uint32_t *)(pArg2 + 56)));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  }
  sub_4B0DF0(*pDwArg3, *pDwArg4);  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  v14 = pDwArg3 + 1;  // 计算 v14 = pDwArg3 + 1
  v15 = (char *)pDwArg4 - (char *)pDwArg3;
  v16 = pDwArg4 + 5;  // 计算 v16 = pDwArg4 + 5
  v19 = 4;
  while ( 1 )
  {
    sub_4B0DF0(*v14, *(int **)((char *)v14 + v15));  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
    sub_4B0DF0(v14[4], *v16);  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
    ++v14;  // 计数自增 v14
    ++v16;  // 计数自增 v16
    if ( --v19 == 0 )
      break;
    v15 = (char *)pDwArg4 - (char *)pDwArg3;
  }
  sub_4B0DF0(pDwArg3[9], pDwArg4[9]);  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  sub_4B0DF0(pDwArg3[10], pDwArg4[10]);  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  sub_4B0DF0(pDwArg3[11], pDwArg4[11]);  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
  sub_4B0DF0(pDwArg3[12], pDwArg4[12]);  // sub_4B0DF0 —— 部位动画重载（+48 槽 → sub_4924C0 按索引确保图像）
}



// ============================================================
// §E 0x4B1E50-0x4B2780  渲染主驱动/部件集
// ============================================================
// ------------------------------------------------------------
// 0x4B1E50 sub_4B1E50 —— ★外观渲染主驱动（帧推进 sub_4938F0、+52/+56 槽、sub_424760 提交、sub_42FDA0 变换）
// ------------------------------------------------------------
int /*userpurge*/ sub_4B1E50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3, int pArg4, int nArg5, int nArg6)  // 实现：外观渲染主驱动（帧推进 sub_4938F0、+52/+56 槽、sub_424760 提交、sub_42FDA0 变换）
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
    if ( dword_8F7C04 != 0 && *(uint8_t *)(dword_8F7C04 + 8052) != 0 && (uint32_t *)dword_8F7C04 != pArg1 )  // 判定 dword_8F7C04 != 0 且 dword_8F7C04 != pArg1
    {
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 && (uint8_t)sub_48F620(dword_99FEC0) != 0 )  // sub_48F620 —— 对局中标志查询
      {
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 376))(pArg1) == 1 )  // 虚调用 vt+376（pArg1 虚表槽）
          v10 = sub_418DD0(16);  // sub_418DD0 —— 资源句柄 (101)
        else
          v10 = sub_418DD0(17);  // sub_418DD0 —— 资源句柄 (101)
        v29 = v10;
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 192))(pArg1);  // 虚调用 vt+192（pArg1）取尺寸/包围盒
        v12 = pArg4 - 33;  // 计算 v12 = pArg4 - 33
      }
      else
      {
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1216))(pArg1);  // 虚调用 vt+1216（pArg1 虚表槽）
        v29 = sub_418DD0(v13 + 8);  // sub_418DD0 —— 资源句柄 (101)
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 192))(pArg1);  // 虚调用 vt+192（pArg1）取尺寸/包围盒
        v12 = pArg4 - 16;  // 计算 v12 = pArg4 - 16
      }
      sub_424760(dword_79C0B0, v12, nArg5 - v11 - 40, v29, 1.0, 1065353216, 0.0, -1, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1);  // 虚调用 vt+724（pArg1）取值
      if ( (uint8_t)result == 0 )
      {
        v30 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 832))(pArg1);  // 虚调用 vt+832（pArg1 虚表槽）
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);  // 虚调用 vt+52（pArg1）归属坐标y
        v15 = sub_429830(v14);  // sub_429830 —— 结果 = 表按键查找（uint16）
        sub_42FDA0(nArg2, (int)pArg1, pArg4, nArg5, (int)pArg1, v15, v30);  // sub_42FDA0 —— 观战名牌绘制
        sub_424680((int)&pArg4, (int)&nArg5, 0.0, 0.0);  // sub_424680 —— 变焦点变换: p = pivot + (p − pivot) × globalZoom
        nArg6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 192))(pArg1);  // 虚调用 vt+192（pArg1）取尺寸/包围盒
        v16 = nArg5 - (uint64_t)((double)nArg6 * *(float *)&dword_77F6DC) - 55;  // 读 dword_77F6DC（全局变焦值）
        nArg6 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 172);  // dword_99FCC8 —— nengine::CNSlider 构造
        v17 = *(uint32_t *)(sub_418DD0(20) + 20);  // sub_418DD0 —— 资源句柄 (101)
        v18 = sub_418DD0(20);  // sub_418DD0 —— 资源句柄 (101)
        sub_43B560(pArg4 - (v17 >> 1), v16, v18, 1065353216, 1065353216, 0, -1, 1333788672, 1333788672);  // sub_43B560 —— 绘制转发（vt+128）
        v19 = pArg4 - (*(uint32_t *)(sub_418DD0(21) + 20) >> 1);  // sub_418DD0 —— 资源句柄 (101)
        v31 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 740))(pArg1);  // 虚调用 vt+740（pArg1 虚表槽）
        v20 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 736))(pArg1);  // 虚调用 vt+736（pArg1 虚表槽）
        v21 = sub_423A80(0, 74, v20, v31);  // sub_423A80 —— 同上 int 版（FTOL 截断）
        v22 = (uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        *(uint32_t *)(dword_79C0B0 + 56) = v19 + v21;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        v22[12] = 0;
        v22[13] = 0;
        v22[15] = 480;
        v23 = sub_418DD0(21);  // sub_418DD0 —— 资源句柄 (101)
        sub_40FC80(v19, v16 + 2, v23);  // sub_40FC80 —— 贴图转发（目标对象虚发 +152(this, x, y)）
        result = sub_488670(dword_79C0B0);  // sub_488670 —— 视口重置 640x480
      }
    }
    else
    {
      v32 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 832))(pArg1);  // 虚调用 vt+832（pArg1 虚表槽）
      v24 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);  // 虚调用 vt+52（pArg1）归属坐标y
      v25 = sub_429830(v24);  // sub_429830 —— 结果 = 表按键查找（uint16）
      sub_42FDA0(nArg2, (int)pArg1, pArg4, nArg5, (int)pArg1, v25, v32);  // sub_42FDA0 —— 观战名牌绘制
      result = pArg1[1940];
      if ( result != 4 && result != *(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 100) )
      {
        v26 = sub_699000((int)(pArg1 + 16));  // 【clock_now(clk)】
        result = sub_418DD0(((v26 / 0xFA) & 1) + 2 * pArg1[1940] + 75);  // sub_418DD0 —— 资源句柄 (101)
        if ( result != 0 )
          result = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(  // 虚调用 vt+152（result）取值(参数)
                     result,
                     pArg4 + 10,
                     nArg5 - pArg1[40] - 10,
                     dword_79C0B0);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
    }
    v27 = pArg1[30];
    if ( v27 != 0 )
    {
      if ( *(uint32_t *)(v27 + 148) == -1 )
        sub_4938F0(pArg1[30]);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      v34 = *(uint8_t *)(v27 + 95);  // 读字段 v34 = v27+95
      v28 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 792))(pArg1, 9);  // 虚调用 vt+792（pArg1）角色槽物品取
      return sub_432600(1, pArg4, nArg5, pArg1, v28, 0, v34);  // sub_432600 —— 称号气球触发包装
    }
  }
  else
  {
    v7 = pArg1[30];
    if ( v7 != 0 )
    {
      if ( *(uint32_t *)(v7 + 148) == -1 )
        sub_4938F0(pArg1[30]);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      v33 = *(uint8_t *)(v7 + 95);  // 读字段 v33 = v7+95
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 792))(pArg1, 9);  // 虚调用 vt+792（pArg1）角色槽物品取
      sub_432600(0, pArg4, nArg5, pArg1, v8, 0, v33);  // sub_432600 —— 称号气球触发包装
    }
    return sub_58E550(0, pArg4, nArg5, nArg6);  // 【IRDActiveObject__vmt144】
  }
  return result;
}


// ------------------------------------------------------------
// 0x4B2230 sub_4B2230 —— map 查键返回节点值 +20
//   在 map(this+7416) 中 lower_bound 查 nArg2，命中返回值字段 +20，未命中 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B2230(int **this, int nArg2)  // sub_4B2230 —— map 查键返回节点值 +20
{
  int *v4; // [esp+4h] [ebp-4h] BYREF

  sub_4B1BA0(this + 1854, &v4, &nArg2);  // sub_4B1BA0 —— map lower_bound（键在 +12）
  if ( v4 == *(this + 1855) )  // this+7420〔map7416End〕
    return 0;
  else
    return v4[5];  // 返回 取 v4[5]
}



// ------------------------------------------------------------
// 0x4B2270 sub_4B2270 —— 部件特效时长汇总（18 槽）
//   先把 this+7420 map 各节点值(+20) 复位为初值(+16)，再遍历 18 个部件槽（含互斥两形态
//   vt+176/vt+224）按动画项 id(vt+1032) 匹配 +4/+18 处数值，累加时长并以 ·0x47DCC0 上限截断。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B2270(uint32_t *this)  // sub_4B2270 —— 部件特效时长汇总（18 槽）
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

  fld_e1855 = (uint32_t *)*(this + 1855);  // this+7420〔map7416End〕
  pThis_6512 = (uint32_t *)*fld_e1855;  // fld_e1855=this+7420 map7416End
  pThis_651 = (uint32_t *)*fld_e1855;  // fld_e1855=this+7420 map7416End
  if ( pThis_651 != fld_e1855 )  // fld_e1855=this+7420 map7416End
  {
    do
    {
      pThis_6512[5] = pThis_6512[4];  // pThis_6512[5] = 取 pThis_6512[4]
      sub_4B0C60(&pThis_651);  // sub_4B0C60 —— RB 树迭代器自增（中序后继）
      pThis_6512 = pThis_651;
    }
    while ( pThis_651 != (uint32_t *)*(this + 1855) );  // this+7420〔map7416End〕
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
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 200))(pObj2);  // 虚调用 vt+200（pObj2）取值比较
      if ( (uint8_t)result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1084))(this, v4);  // 虚调用 vt+1084（this 虚表槽）
        v28 = result;
      }
      pObj = v28;
      if ( v28 != 0 )
      {
        for ( i = 0; i < 2; ++i )  // 遍历计次循环（i < 2）
        {
          if ( i != 0 )
          {
            result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 224))(pObj);  // 虚调用 vt+224（pObj）以 &hWnd 写出窗口句柄，返回该句柄非 4 —— 调用方据此判网页控件存活。
            if ( (uint8_t)result == 0 )
              break;
            v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 228))(pObj);  // 虚调用 vt+228（pObj）主状态写入(state,param,flag)
          }
          else
          {
            v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);  // 虚调用 vt+176（pObj 虚表槽）
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
                if ( *v10 == 4 || *v10 == *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 1032))(this) )  // 虚调用 vt+1032（this 虚表槽）
                {
                  v13 = v12 - 14;  // 计算 v13 = v12 - 14
                  v22 = sub_41A5E0(v13);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                  v14 = (int *)sub_4B1BA0(v21, &v22);  // sub_4B1BA0 —— map lower_bound（键在 +12）
                  v15 = *v14;
                  if ( *v14 != *(this + 1855) )  // this+7420〔map7416End〕
                  {
                    v16 = sub_41A5E0(v13);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                    v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, v16);  // 虚调用 vt+1160（this）读技能表(变体)
                    v22 = sub_41A5E0(v30);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                    v18 = sub_47DCC0(v17);
                    if ( v22 + *(uint32_t *)(v15 + 20) >= v18 )
                      v19 = sub_47DCC0(v17);
                    else
                      v19 = sub_41A5E0(v30) + *(uint32_t *)(v15 + 20);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                    *(uint32_t *)(v15 + 20) = v19;  // 写字段 v15+20（nPage） ← v19
                  }
                  v10 = v29;
                }
                v9 = v25;
                v10 += 8;
                v12 = v30 + 32;  // 计算 v12 = v30 + 32
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
            --v24;  // 计数自减 v24
          }
          while ( !v11 );
          result = i + 1;
        }
      }
    }
    v4 = v23 + 1;  // 计算 v4 = v23 + 1
    v20 = ++v23 < 18;
    ++pThis_651;  // 计数自增 pThis_651
  }
  while ( v20 );
  return result;
}


// ------------------------------------------------------------
// 0x4B2440 sub_4B2440 —— 名称串查询（含默认串特判）
//   优先取 +6500 组件名称向量(+48) 第 uArg2 项（首项不等 szPassword 时）；
//   否则回退 +7616 表 16 字节/条 记录的第 idx 项；均缺省返回 off_791BBC[0]。
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_4B2440(uint32_t *this, unsigned int uArg2)  // sub_4B2440 —— 名称串查询（含默认串特判）
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

  fld_e1625 = *(this + 1625);  // 读字段 fld_e1625 = this+1625
  if ( fld_e1625 == 0 )  // fld_e1625=this+1625 nWeaponItemId
    return (const CHAR *)off_791BBC[0];
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 172))(fld_e1625);  // 虚调用 vt+172（fld_e1625 虚表槽）
  v6 = *(uint32_t *)(v5 + 52);  // 读字段 v6 = v5+52（bAuraState）
  uArg22 = uArg2;
  v8 = v5 + 48;  // 计算 v8 = v5 + 48
  if ( v6 != 0 && (*(uint32_t *)(v8 + 8) - v6) >> 2 > uArg2 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 172))(fld_e1625);  // 虚调用 vt+172（fld_e1625 虚表槽）
    if ( (uint8_t)sub_42FD40(szPassword) != 0 )  // sub_42FD40 —— 字符串不等判定
    {
      v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 172))(fld_e1625);  // 虚调用 vt+172（fld_e1625 虚表槽）
      return sub_41ACF0((unsigned int **)(4 * uArg2 + *(uint32_t *)(v9 + 52)));  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    }
    uArg22 = uArg2;
  }
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1625 + 172))(fld_e1625);  // 虚调用 vt+172（fld_e1625 虚表槽）
  v11 = sub_41A5E0(v10 + 4);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  fld_e1904 = *(this + 1904);  // 读字段 fld_e1904 = this+1904
  if ( fld_e1904 != 0
    && (*(this + 1905) - fld_e1904) >> 4 > v11  // this+7620〔pStatusPanel(推断)〕
    && (v13 = 16 * v11, v14 = *(uint32_t *)(v13 + fld_e1904 + 4), v15 = fld_e1904 + v13, v14 != 0)  // 名称串查询（含默认串特判）
    && (*(uint32_t *)(v15 + 8) - v14) >> 2 > uArg22 )
  {
    return sub_41ACF0((unsigned int **)(v14 + 4 * uArg22));  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  }
  else
  {
    return (const CHAR *)off_791BBC[0];
  }
}



// ------------------------------------------------------------
// 0x4B2530 sub_4B2530 —— +7680 数组浮点取值（缺省 0.0）
//   与 ·0x4B1870 同结构，数组 +7680，浮点缺省 0.0。
// ------------------------------------------------------------
double /*thiscall*/ sub_4B2530(uint32_t *this)  // 实现：+7680 数组浮点取值（缺省 0.0）
{
  unsigned int fld_e1920; // eax
  int v3; // edx

  if ( *(this + 1625) != 0  // this+6500〔nWeaponItemId〕
    && (fld_e1920 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1096))(this), (v3 = *(this + 1920)) != 0)  // 虚调用 vt+1096（this）枪种分派
    && (*(this + 1921) - v3) >> 2 > fld_e1920 )  // +7680 数组浮点取值（缺省 0.0）
  {
    return *(float *)(*(this + 1920) + 4 * fld_e1920);
  }
  else
  {
    return 0.0;  // 返回 0.0
  }
}



// ------------------------------------------------------------
// 0x4B2580 sub_4B2580 —— 目标搜索 + 瞄准角输出
//   遍历对象列表(vt+80 的 +120 向量)：经标志 17 与 ·0x4E4630 敌我判定过滤，按 |x-a4| 用 ·0x4B07E0
//   选最近命中者；命中则 atan2 求 yaw/pitch（夹在 ±a9/±a10）写回 a1/a2。
// ------------------------------------------------------------
int */*cdecl*/ sub_4B2580(  // sub_4B2580 —— 目标搜索 + 瞄准角输出
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
  v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 80))(a3);  // 虚调用 vt+80（a3）读 4 字节
  v16 = *(uint32_t *)(v15 + 120);  // 读字段 v16 = v15+120（pAnimObj）
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
    v18 = *(uint32_t *)(v15 + 120);  // 读字段 v18 = v15+120（pAnimObj）
    if ( v18 != 0 && v17 < (*(uint32_t *)(v15 + 124) - v18) >> 2 )
      v19 = *(int **)(v18 + 4 * v17);
    else
      v19 = nullptr;
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(*v19 + 40))(v19, 17) != 0  // 虚调用 vt+40（v19）条件查询(273等)
      && (uint8_t)sub_4E4630(v19) != 0 )  // sub_4E4630 —— ★ 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
    {
      v20 = (*(int (/*thiscall*/ **)(int *))(*v19 + 120))(v19) - a4;  // 虚调用 vt+120（v19）转发(对象+缓冲)
      v21 = (HIDWORD(v20) ^ v20) - HIDWORD(v20);
      if ( (a11 == -1 || v21 < a11) && sub_4B07E0(a3, v19, a4, a5, a6, a7, a8, a9, a10, a12, a13, a14, a15) )  // sub_4B07E0 —— 攻击包络命中判定（扇形/梯形）
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
        - (uint64_t)(atan2(  // 调 反正切2
                               (double)((*(int (/*thiscall*/ **)(int *))(v23 + 124))(v24) - a5)  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
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
    v28 = 2 * (*(int (/*thiscall*/ **)(int *))(*v22 + 192))(v22) / 3 - a6;  // 虚调用 vt+192（v22）取尺寸/包围盒
    v29 = -a8
        - (uint64_t)(atan2((double)((*(int (/*thiscall*/ **)(int *))(*v22 + 128))(v22) + v28) / v33, 1.0)  // 虚调用 vt+128（v22）目标坐标y上界
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
// 0x4B2780 sub_4B2780 —— 坐标记录生成（·0x4600B0）
//   取自身坐标(vt+120/+124/+128) 与 +8000 组件状态帧(vt+92)，经 vt+80 生成临时记录后交 ·0x4600B0 并释放缓冲。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B2780(uint32_t *this)  // sub_4B2780 —— 坐标记录生成（·0x4600B0）
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
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e2000 + 40))(*(this + 2000));  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2000) + 92))(*(this + 2000), v8);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
  v3 = *this;
  v10 = 0;
  v4 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint8_t *))(v3 + 80))(this, 2, 0, v8);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  sub_4600B0(v4, v5, v6, v7);  // sub_4600B0 —— 演播层注册(槽号)
  if ( Block != nullptr )
    j__free(Block);  // 释放堆块
}



// ------------------------------------------------------------
// 0x4B2820 sub_4B2820 —— avatar 配置记录拷贝构造（152 字节）
//   逐字段复制 +0..+88（含 +17 半字、+80..+82 字节标志），重置 +92 处 std::string 头（容量 15/长度 0）
//   后经 ·0x4014D0 拷贝串，再复制尾部 +120..+148。
// ------------------------------------------------------------
char */*thiscall*/ sub_4B2820(char *this, int pArg2)  // sub_4B2820 —— avatar 配置记录拷贝构造（152 字节）
{
  uint32_t *pThis_30; // ecx

  *(uint32_t *)this = *(uint32_t *)pArg2;
  *((uint32_t *)this + 1) = *(uint32_t *)(pArg2 + 4);  // 写字段 this[1]（宽4字节）
  *((uint32_t *)this + 2) = *(uint32_t *)(pArg2 + 8);  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 3) = *(uint32_t *)(pArg2 + 12);  // 写字段 this[3]（宽4字节）
  *(this + 16) = *(uint8_t *)(pArg2 + 16);  // 写字段 this+16（nChannelTypeSel） ← *(uint8_t *)(pArg2 + 16)
  *(uint16_t *)(this + 17) = *(uint16_t *)(pArg2 + 17);  // 写字段 this+17（bEnable） ← *(uint16_t *)(pArg2 + 17)
  *(this + 19) = *(uint8_t *)(pArg2 + 19);  // 写字段 this+19 ← *(uint8_t *)(pArg2 + 19)
  *((uint32_t *)this + 5) = *(uint32_t *)(pArg2 + 20);  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 6) = *(uint32_t *)(pArg2 + 24);  // 写字段 this[6]（宽4字节）
  *((uint32_t *)this + 7) = *(uint32_t *)(pArg2 + 28);  // 写字段 this+7（uPathTerm）
  *((uint32_t *)this + 8) = *(uint32_t *)(pArg2 + 32);  // 写字段 this+8（nSkillRec8）
  *((uint32_t *)this + 9) = *(uint32_t *)(pArg2 + 36);  // 写字段 this[9]（宽4字节）
  *((uint32_t *)this + 10) = *(uint32_t *)(pArg2 + 40);  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 11) = *(uint32_t *)(pArg2 + 44);  // 写字段 this[11]（宽4字节）
  pThis_30 = this + 48;  // this+48 UDP 上报使能位
  *pThis_30 = *(uint32_t *)(pArg2 + 48);  // 读字段 pThis_30 = pArg2+48（pCmdVecBegin48）
  pThis_30[1] = *(uint32_t *)(pArg2 + 52);  // pArg2+52〔bAuraState(推断)〕
  pThis_30[2] = *(uint32_t *)(pArg2 + 56);  // pArg2+56〔pCmdVecCap56(推断)〕
  *((uint32_t *)this + 15) = *(uint32_t *)(pArg2 + 60);  // 写字段 this[15]（宽4字节）
  *((uint32_t *)this + 16) = *(uint32_t *)(pArg2 + 64);  // 写字段 this+16（nChannelTypeSel）
  *((uint32_t *)this + 17) = *(uint32_t *)(pArg2 + 68);  // 写字段 this+17（bEnable）
  *((uint32_t *)this + 18) = *(uint32_t *)(pArg2 + 72);  // 写字段 this+18（bDragChild）
  *((uint32_t *)this + 19) = *(uint32_t *)(pArg2 + 76);  // 写字段 this[19]（宽4字节）
  *(this + 80) = *(uint8_t *)(pArg2 + 80);  // 写字段 this+80（nAuraStage） ← *(uint8_t *)(pArg2 + 80)
  *(this + 81) = *(uint8_t *)(pArg2 + 81);  // 写字段 this+81 ← *(uint8_t *)(pArg2 + 81)
  *(this + 82) = *(uint8_t *)(pArg2 + 82);  // 写字段 this+82 ← *(uint8_t *)(pArg2 + 82)
  *((uint32_t *)this + 21) = *(uint32_t *)(pArg2 + 84);  // 写字段 this+21（bArmorState）
  *((uint32_t *)this + 22) = *(uint32_t *)(pArg2 + 88);  // 写字段 this[22]（宽4字节）
  *((uint32_t *)this + 29) = 15;  // 写字段 this[29]（宽4字节）
  *((uint32_t *)this + 28) = 0;  // 写字段 this+28（pPanelVec）
  *(this + 96) = 0;  // 写字段 this+96（nStatusMode） ← 0
  sub_4014D0((size_t *)this + 23, (size_t *)(pArg2 + 92), 0, 0xFFFFFFFF);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *((uint32_t *)this + 30) = *(uint32_t *)(pArg2 + 120);  // 写字段 this[30]（宽4字节）
  *((uint32_t *)this + 31) = *(uint32_t *)(pArg2 + 124);  // 写字段 this[31]（宽4字节）
  *(this + 128) = *(uint8_t *)(pArg2 + 128);  // 写字段 this+128（szStatusKeyBuf） ← *(uint8_t *)(pArg2 + 128)
  *((uint32_t *)this + 33) = *(uint32_t *)(pArg2 + 132);  // 写字段 this+33（bJobVecDirty）
  *((uint32_t *)this + 34) = *(uint32_t *)(pArg2 + 136);  // 写字段 this[34]（宽4字节）
  *(this + 140) = *(uint8_t *)(pArg2 + 140);  // 写字段 this+140（nAdd140） ← *(uint8_t *)(pArg2 + 140)
  *(this + 141) = *(uint8_t *)(pArg2 + 141);  // 写字段 this+141（bFadeFlagA） ← *(uint8_t *)(pArg2 + 141)
  *((uint32_t *)this + 36) = *(uint32_t *)(pArg2 + 144);  // 写字段 this+36（nStateWord36）
  *((uint32_t *)this + 37) = *(uint32_t *)(pArg2 + 148);  // 写字段 this+37（bFadeFlag37）
  return this;
}



// ------------------------------------------------------------
// 0x4B2970 sub_4B2970 —— 部件记录拷贝（同 ·0x4B2820）
//   与 ·0x4B2820 同构（差异：不预设 string 头，直接 ·0x4014D0 赋值；+16..+19 逐字节拷贝）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B2970(uint32_t *this, int pArg2)  // sub_4B2970 —— 部件记录拷贝（同 ·0x4B2820）
{
  *this = *(uint32_t *)pArg2;
  *(this + 1) = *(uint32_t *)(pArg2 + 4);  // 写字段 this+1 ← *(uint32_t *)(pArg2 + 4)
  *(this + 2) = *(uint32_t *)(pArg2 + 8);  // 写字段 this+2 ← *(uint32_t *)(pArg2 + 8)
  *(this + 3) = *(uint32_t *)(pArg2 + 12);  // 写字段 this+3 ← *(uint32_t *)(pArg2 + 12)
  *((uint8_t *)this + 16) = *(uint8_t *)(pArg2 + 16);  // 写字段 this+16（nChannelTypeSel）
  *((uint8_t *)this + 17) = *(uint8_t *)(pArg2 + 17);  // 写字段 this+17（bEnable）
  *((uint8_t *)this + 18) = *(uint8_t *)(pArg2 + 18);  // 写字段 this+18（bDragChild）
  *((uint8_t *)this + 19) = *(uint8_t *)(pArg2 + 19);  // 写字段 this[19]（宽1字节）
  *(this + 5) = *(uint32_t *)(pArg2 + 20);  // 写字段 this+5 ← *(uint32_t *)(pArg2 + 20)
  *(this + 6) = *(uint32_t *)(pArg2 + 24);  // 写字段 this+6 ← *(uint32_t *)(pArg2 + 24)
  *(this + 7) = *(uint32_t *)(pArg2 + 28);  // 写字段 this+7（uPathTerm） ← *(uint32_t *)(pArg2 + 28)
  *(this + 8) = *(uint32_t *)(pArg2 + 32);  // 写字段 this+8（nSkillRec8） ← *(uint32_t *)(pArg2 + 32)
  *(this + 9) = *(uint32_t *)(pArg2 + 36);  // 写字段 this+9 ← *(uint32_t *)(pArg2 + 36)
  *(this + 10) = *(uint32_t *)(pArg2 + 40);  // 写字段 this+10 ← *(uint32_t *)(pArg2 + 40)
  *(this + 11) = *(uint32_t *)(pArg2 + 44);  // 写字段 this+11 ← *(uint32_t *)(pArg2 + 44)
  *(this + 12) = *(uint32_t *)(pArg2 + 48);  // 写字段 this+12（nSkillRec12） ← *(uint32_t *)(pArg2 + 48)
  *(this + 13) = *(uint32_t *)(pArg2 + 52);  // 写字段 this+13 ← *(uint32_t *)(pArg2 + 52)
  *(this + 14) = *(uint32_t *)(pArg2 + 56);  // 写字段 this+14 ← *(uint32_t *)(pArg2 + 56)
  *(this + 15) = *(uint32_t *)(pArg2 + 60);  // 写字段 this+15 ← *(uint32_t *)(pArg2 + 60)
  *(this + 16) = *(uint32_t *)(pArg2 + 64);  // 写字段 this+16（nChannelTypeSel） ← *(uint32_t *)(pArg2 + 64)
  *(this + 17) = *(uint32_t *)(pArg2 + 68);  // 写字段 this+17（bEnable） ← *(uint32_t *)(pArg2 + 68)
  *(this + 18) = *(uint32_t *)(pArg2 + 72);  // 写字段 this+18（bDragChild） ← *(uint32_t *)(pArg2 + 72)
  *(this + 19) = *(uint32_t *)(pArg2 + 76);  // 写字段 this+19 ← *(uint32_t *)(pArg2 + 76)
  *((uint8_t *)this + 80) = *(uint8_t *)(pArg2 + 80);  // 写字段 this+80（nAuraStage）
  *((uint8_t *)this + 81) = *(uint8_t *)(pArg2 + 81);  // 写字段 this[81]（宽1字节）
  *((uint8_t *)this + 82) = *(uint8_t *)(pArg2 + 82);  // 写字段 this[82]（宽1字节）
  *(this + 21) = *(uint32_t *)(pArg2 + 84);  // 写字段 this+21（bArmorState） ← *(uint32_t *)(pArg2 + 84)
  *(this + 22) = *(uint32_t *)(pArg2 + 88);  // 写字段 this+22 ← *(uint32_t *)(pArg2 + 88)
  sub_4014D0((std::_String_base *)(this + 23), pArg2 + 92, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(this + 30) = *(uint32_t *)(pArg2 + 120);  // 写字段 this+30 ← *(uint32_t *)(pArg2 + 120)
  *(this + 31) = *(uint32_t *)(pArg2 + 124);  // 写字段 this+31 ← *(uint32_t *)(pArg2 + 124)
  *((uint8_t *)this + 128) = *(uint8_t *)(pArg2 + 128);  // 写字段 this+128（szStatusKeyBuf）
  *(this + 33) = *(uint32_t *)(pArg2 + 132);  // 写字段 this+33（bJobVecDirty） ← *(uint32_t *)(pArg2 + 132)
  *(this + 34) = *(uint32_t *)(pArg2 + 136);  // 写字段 this+34 ← *(uint32_t *)(pArg2 + 136)
  *((uint8_t *)this + 140) = *(uint8_t *)(pArg2 + 140);  // 写字段 this+140（nAdd140）
  *((uint8_t *)this + 141) = *(uint8_t *)(pArg2 + 141);  // 写字段 this+141（bFadeFlagA）
  *(this + 36) = *(uint32_t *)(pArg2 + 144);  // 写字段 this+36（nStateWord36） ← *(uint32_t *)(pArg2 + 144)
  *(this + 37) = *(uint32_t *)(pArg2 + 148);  // 写字段 this+37（bFadeFlag37） ← *(uint32_t *)(pArg2 + 148)
  return this;
}



// ------------------------------------------------------------
// 0x4B2AA0 sub_4B2AA0 —— 装载角色初始资料（职业名+外观）
//   拷贝 +288 字符串，置职业 +7148 并查表(·0x4CE8A0，28 字节/条) 按索引取职业名赋给 +7160(·0x4015C0)，
//   设置 +676 与索引字段，末尾 vt+1320 按(索引/字节标志) 应用初始外观。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B2AA0(size_t *this, int pArg2)  // sub_4B2AA0 —— 装载角色初始资料（职业名+外观）
{
  int v3; // ebx
  int v4; // eax
  char *psz; // ecx
  int v6; // ebx
  unsigned int v7; // ecx
  int v8; // eax
  int v9; // eax
  size_t v10; // edx

  sub_4014D0(this + 72, (size_t *)pArg2, 0, 0xFFFFFFFF);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(this + 1787) = *(uint32_t *)(pArg2 + 28);  // 写字段 this+1787（bBehaviorWord） ← *(uint32_t *)(pArg2 + 28)
  v3 = *(uint32_t *)(pArg2 + 32);  // 读字段 v3 = pArg2+32（nHeight）
  v4 = sub_4CE8A0(*(uint32_t *)(pArg2 + 28));  // sub_4CE8A0 —— 调用 sub_4CE8A0
  if ( v4 != 0 )
  {
    v6 = 28 * v3;  // 计算 v6 = 28 * v3
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
  v9 = sub_41A5E0(pArg2 + 37);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v10 = *this;
  *(this + 169) = v9;  // 写字段 this+169 ← v9
  (*(void (/*thiscall*/ **)(size_t *, uint32_t))(v10 + 676))(this, 0);  // 虚函数调用 槽+676：观察者/状态的对象绑定与解绑（a2 = 0/1/2）
  return (*(int (/*thiscall*/ **)(size_t *, uint32_t, uint32_t))(*this + 1320))(  // 虚调用 vt+1320（this 虚表槽）
           this,
           *(uint32_t *)(pArg2 + 32),
           *(uint8_t *)(pArg2 + 36));  // pArg2+36〔nStateWord36(推断)〕
}



// ------------------------------------------------------------
// 0x4B2B50 sub_4B2B50 —— 记录目标身份字段（+8008..+8024）
//   经 vt+576 归一化宿主(529 号标志取 +8352)，取 vt+44/+48/+52/+376 存 +8008..+8020，
//   并拷贝 vt+340 偏移 +4 的串到 +8024。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4B2B50(size_t *this, uint32_t *pArg2)  // sub_4B2B50 —— 记录目标身份字段（+8008..+8024）
{
  uint32_t *pArg22; // esi
  int v4; // eax

  pArg22 = pArg2;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 576))(pArg2) != 0 )  // 虚调用 vt+576（pArg2）受击方判定体
    pArg22 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 576))(pArg2);  // 虚调用 vt+576（pArg2）受击方判定体
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg22 + 40))(pArg22, 529) != 0 && pArg22[2088] != 0 )  // 虚调用 vt+40（pArg22）条件查询(273等)
    pArg22 = (uint32_t *)pArg22[2088];
  *(this + 2002) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 44))(pArg22);  // 虚调用 vt+44（pArg22 虚表槽）
  *(this + 2003) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 48))(pArg22);  // 虚调用 vt+48（pArg22）归属坐标x
  *(this + 2004) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 52))(pArg22);  // 虚调用 vt+52（pArg22）归属坐标y
  *(this + 2005) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 376))(pArg22);  // 虚调用 vt+376（pArg22 虚表槽）
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 340))(pArg22);  // 虚调用 vt+340（pArg22 虚表槽）
  return sub_4014D0(this + 2006, (size_t *)(v4 + 4), 0, 0xFFFFFFFF);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
}



// ------------------------------------------------------------
// 0x4B2BF0 sub_4B2BF0 —— std::map 节点删除（RB 再平衡）
//   迭代器为 nil 时抛 out_of_range（invalid map/set<T> iterator）；后继经 ·0x4B0C60、
//   header 极值经 ·0x433190/·0x4B0BE0 维护，再平衡用 ·0x4B0FD0/·0x4B0C00 旋转；
//   末尾节点数 -1 并释放节点。
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4B2BF0(uint32_t *this, int ***uArg2, int **pDwArg3)  // sub_4B2BF0 —— std::map 节点删除（RB 再平衡）
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
    sub_401740(pExceptionObject, (int)v20);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::out_of_range::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_4B0C60(&pDwArg3);  // sub_4B0C60 —— RB 树迭代器自增（中序后继）
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
      *(uint32_t *)(v8 + 4) = v4;  // 写字段 v8+4（pHostObj） ← v4
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
        v9 = (int *)sub_433190(v4);  // sub_433190 —— 最左节点（+25 版）
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;  // 写字段 v10+8（nSkillRec8） ← = (uint32_t)pDwArg32
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 25) != 0 )
        *(uint32_t *)(v10 + 8) = v6;  // 写字段 v10+8（nSkillRec8） ← v6
      else
        *(uint32_t *)(v23 + 8) = sub_4B0BE0(v4);  // sub_4B0BE0 —— RB 树子树最大值（右脊下降）
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
    *(uint32_t *)(v12 + 4) = v5;  // 写字段 v12+4（pHostObj） ← v5
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
  v14 = *((uint8_t *)v5 + 24);  // 读字段 v14 = v5+24（nPageMax）
  *((uint8_t *)v5 + 24) = *((uint8_t *)pDwArg32 + 24);  // 写字段 v5+24（nPageMax）
  *((uint8_t *)pDwArg32 + 24) = v14;  // 写字段 pDwArg32+24（nPageMax）
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
            *((uint8_t *)v16 + 24) = 1;  // 写字段 v16+24（nPageMax）
            *((uint8_t *)v6 + 24) = 0;  // 写字段 v6+24（nPageMax）
            sub_4B0FD0(v6);  // sub_4B0FD0 —— RB 树左旋（右子提升）
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
              *((uint8_t *)v16 + 24) = 0;  // 写字段 v16+24（nPageMax）
              sub_4B0C00(v16);  // sub_4B0C00 —— RB 树右旋（左子提升）
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 24) = *((uint8_t *)v6 + 24);  // 写字段 v16+24（nPageMax）
            *((uint8_t *)v6 + 24) = 1;  // 写字段 v6+24（nPageMax）
            *(uint8_t *)(v16[2] + 24) = 1;
            sub_4B0FD0(v6);  // sub_4B0FD0 —— RB 树左旋（右子提升）
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 24) == 0 )
          {
            *((uint8_t *)v16 + 24) = 1;  // 写字段 v16+24（nPageMax）
            *((uint8_t *)v6 + 24) = 0;  // 写字段 v6+24（nPageMax）
            sub_4B0C00(v6);  // sub_4B0C00 —— RB 树右旋（左子提升）
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
              *((uint8_t *)v16 + 24) = 0;  // 写字段 v16+24（nPageMax）
              sub_4B0FD0(v16);  // sub_4B0FD0 —— RB 树左旋（右子提升）
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 24) = *((uint8_t *)v6 + 24);  // 写字段 v16+24（nPageMax）
            *((uint8_t *)v6 + 24) = 1;  // 写字段 v6+24（nPageMax）
            *(uint8_t *)(*v16 + 24) = 1;
            sub_4B0C00(v6);  // sub_4B0C00 —— RB 树右旋（左子提升）
            break;
          }
        }
        *((uint8_t *)v16 + 24) = 0;  // 写字段 v16+24（nPageMax）
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 24) = 1;  // 写字段 v4+24（nPageMax）
  }
  j__free(Block);  // 释放堆块
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4B2EB0 sub_4B2EB0 —— vector 下标越界抛出
//   noreturn：抛 out_of_range（invalid vector<T> subscript），供容器下标检查调用。
// ------------------------------------------------------------
void /*noreturn*/ sub_4B2EB0()  // sub_4B2EB0 —— vector 下标越界抛出
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
  sub_401740(pExceptionObject, &v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject[0] = &std::out_of_range::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x4B2F20 sub_4B2F20 —— vector 长度超限抛出
//   noreturn：抛 length_error（vector<T> too long）。
// ------------------------------------------------------------
void /*noreturn*/ sub_4B2F20()  // sub_4B2F20 —— vector 长度超限抛出
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
  sub_401740(pExceptionObject, &v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x4B2F90 sub_4B2F90 —— std::map 插入 + 红黑再平衡
//   长度达上限先抛 length_error（map/set<T> too long）；经 ·0x437740 分配挂接节点，
//   再自底向上再平衡（·0x4B0FD0 左旋/·0x4B0C00 右旋），返回插入位置。
// ------------------------------------------------------------
int */*thiscall*/ sub_4B2F90(int **this, int *pDwArg2, char pszArg3, int *pDwArg4, int nArg5)  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
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

  if ( (unsigned int)*(this + 2) >= 0x15555554 )  // this+8〔nSkillRec8(推断)〕
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_437740(*(this + 1), pDwArg4, *(this + 1), nArg5, 0);  // sub_437740 —— 红黑节点构造（0x1C）
  fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
  fld_e15 = fld_e1;
  *(this + 2) = (int *)((char *)*(this + 2) + 1);  // 写字段 this+2 ← (int *)((char *)*(this + 2) + 1)
  if ( pDwArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    **(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    (*(this + 1))[2] = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pDwArg4 = fld_e1;
    fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
    if ( pDwArg4 == (int *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pDwArg4[2] = fld_e1;
    fld_e14 = (int)*(this + 1);  // this+4〔宿主对象〕
    if ( pDwArg4 == *(int **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
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
            sub_4B0FD0(this, *v10);  // sub_4B0FD0 —— RB 树左旋（右子提升）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 24) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 24) = 0;
          sub_4B0C00(this, *(uint32_t **)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_4B0C00 —— RB 树右旋（左子提升）
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 24) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4B0C00(this, (uint32_t *)*v10);  // sub_4B0C00 —— RB 树右旋（左子提升）
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 24) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 24) = 0;
        sub_4B0FD0(this, *(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_4B0FD0 —— RB 树左旋（右子提升）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 24) = 1;
      *(uint8_t *)(v14 + 24) = 1;  // 写字段 v14+24（nPageMax） ← 1
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
  *(uint8_t *)((*(this + 1))[1] + 24) = 1;  // this+4〔宿主对象〕
  *pDwArg2 = fld_e1;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x4B3140 sub_4B3140 —— 区间填充（·0x4B2970 逐条）
//   对 [uArg1,uArg2) 每条 152 字节(38 dwords) 用 ·0x4B2970 从 nArg3 拷贝构造。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4B3140(uint32_t *uArg1, uint32_t *uArg2, int nArg3)  // sub_4B3140 —— 区间填充（·0x4B2970 逐条）
{
  uint32_t *i; // esi
  uint32_t *result; // eax

  for ( i = uArg1; i != uArg2; i += 38 )
    result = sub_4B2970(i, nArg3);  // sub_4B2970 —— 部件记录拷贝（同 ·0x4B2820）
  return result;
}



// ------------------------------------------------------------
// 0x4B3170 sub_4B3170 —— 尾部右移拷贝（·0x4B2970 反向）
//   将 [nArg1,nArg2) 尾部记录自后向前拷贝到 uArg3 处（·0x4B2970 逐条），供 vector 插入腾位。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4B3170(int nArg1, int nArg2, uint32_t *uArg3)  // sub_4B3170 —— 尾部右移拷贝（·0x4B2970 反向）
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
    sub_4B2970(uArg32, nArg22);  // sub_4B2970 —— 部件记录拷贝（同 ·0x4B2820）
  }
  while ( nArg22 != nArg1 );  // 循环直到 nArg22 != nArg1
  return uArg32;
}



// ------------------------------------------------------------
// 0x4B31B0 sub_4B31B0 —— 前向拷贝（·0x4B2820 逐条）
//   前向拷贝 [nArg1,nArg2) 记录到 pszArg3（·0x4B2820 逐条，152 字节/条），返回尾地址。
// ------------------------------------------------------------
char */*cdecl*/ sub_4B31B0(int nArg1, int nArg2, char *pszArg3)  // sub_4B31B0 —— 前向拷贝（·0x4B2820 逐条）
{
  char *pszArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg32 = pszArg3;
  v6[4] = v6;
  v6[3] = pszArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 循环直到 nArg1 != nArg2
  {
    LOBYTE(v7) = 1;
    if ( pszArg32 != nullptr )
      sub_4B2820(pszArg32, nArg1);  // sub_4B2820 —— avatar 配置记录拷贝构造（152 字节）
    pszArg32 += 152;
    LOBYTE(v7) = 0;
    nArg1 += 152;
  }
  return pszArg32;
}



// ------------------------------------------------------------
// 0x4B3270 sub_4B3270 —— clong 组合析构
//   释放 +48 缓冲(·0x4017E0) 与 +4/+32/+72 三个 clong 成员(·0x41A580)。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B3270(uint32_t *this)  // sub_4B3270 —— clong 组合析构
{
  sub_4017E0((int)(this + 12));  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  sub_41A580(this + 8);  // sub_41A580 —— crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580((uint32_t *)((char *)this + 18));  // sub_41A580 —— crypt4byte 析构（vftable 复位 + 实例计数递减）
  sub_41A580(this + 1);  // sub_41A580 —— crypt4byte 析构（vftable 复位 + 实例计数递减）
}



// ------------------------------------------------------------
// 0x4B32E0 sub_4B32E0 —— 角色状态复位（含本地全局清理）
//   清 +7964(-1) 与 +7609，调 ·0x4D6970 出生/复活初始化，清零 *(this+112) 对象的 +16..+48 属性槽；
//   本地角色(dword_8F7C04) 时释放全局链表 dword_8F85A0 与缓冲 dword_8F8588；
//   末尾 vt+1232/1240/1248 复位并置 +7888=0、+7760=4。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B32E0(uint32_t *this)  // sub_4B32E0 —— 角色状态复位（含本地全局清理）
{
  uint32_t *v2; // eax
  uint32_t *v3; // edi
  int result; // eax

  *(this + 1991) = -1;  // 写字段 this+1991 ← -1
  *((uint8_t *)this + 7609) = 0;  // 写字段 this[7609]（宽1字节）
  sub_4D6970();  // sub_4D6970 —— ★ 角色出生/复活初始化（尾调 0x4E73B0 复活重置）
  *(uint32_t *)(*(this + 28) + 16) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 28) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 40) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 20) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 32) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 44) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 24) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 36) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(*(this + 28) + 48) = 0;  // this+112〔pHostComp112〕
  if ( (uint32_t *)dword_8F7C04 == this )  // dword_8F7C04（本地玩家对象）
  {
    v2 = *(uint32_t **)dword_8F85A0;
    *(uint32_t *)dword_8F85A0 = dword_8F85A0;  // *dword_8F85A0 = dword_8F85A0
    *(uint32_t *)(dword_8F85A0 + 4) = dword_8F85A0;  // 写字段 dword_8F85A0+4（pHostObj） ← dword_8F85A0
    dword_8F85A4 = 0;
    if ( v2 != (uint32_t *)dword_8F85A0 )
    {
      do
      {
        v3 = (uint32_t *)*v2;
        j__free(v2);  // 释放堆块
        v2 = v3;
      }
      while ( v3 != (uint32_t *)dword_8F85A0 );
    }
    if ( dword_8F8588 != nullptr )
      j__free(dword_8F8588);  // 释放堆块
    dword_8F8588 = nullptr;
    dword_8F858C = 0;
    dword_8F8590 = 0;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1232))(this, 0);  // 虚调用 vt+1232（this 虚表槽）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 1240))(this, 0, 0);  // 虚调用 vt+1240（this 虚表槽）
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1248))(this, 0);  // 虚调用 vt+1248（this）归属者标记
  *(this + 1972) = 0;  // 写字段 this+1972 ← 0
  *(this + 1940) = 4;  // 写字段 this+1940 ← 4
  return result;
}



// ------------------------------------------------------------
// 0x4B33E0 sub_4B33E0 —— 容器下标（124 字节/元素）
//   越界调用 ·0x4B2EB0 抛出；返回 base + 124*idx。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B33E0(uint32_t *this, unsigned int uArg2)  // sub_4B33E0 —— 容器下标（124 字节/元素）
{
  int fld_e1; // edi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 == 0 || (*(this + 2) - fld_e1) / 124 <= uArg2 )  // fld_e1=this+4 宿主对象
    sub_4B2EB0();  // sub_4B2EB0 —— vector 下标越界抛出
  return fld_e1 + 124 * uArg2;  // fld_e1=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x4B3420 sub_4B3420 —— 容器预分配（16 字节/元素）
//   按 16 字节/元素 operator new；uArg2==0 返回 0，超 0xFFFFFFF 经 ·0x4B2F20 抛出，成功返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4B3420(uint32_t *this, unsigned int uArg2)  // sub_4B3420 —— 容器预分配（16 字节/元素）
{
  char *pMem; // eax

  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  *(this + 3) = 0;  // 写字段 this+3 ← 0
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0xFFFFFFF )
    sub_4B2F20(this);  // sub_4B2F20 —— vector 长度超限抛出
  pMem = (char *)operator new(16 * uArg2);  // 堆分配
  *(this + 3) = &pMem[16 * uArg2];  // 写字段 this+3 ← &pMem[16 * uArg2]
  *(this + 1) = pMem;  // 写字段 this+1 ← pMem
  *(this + 2) = pMem;  // 写字段 this+2 ← pMem
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4B3470 sub_4B3470 —— map 带位置插入
//   按键(节点 +12) 定位并做前驱校正(·0x4B0CC0)，经 ·0x4B2F90 插入；返回插入位与新增标志。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B3470(int **this, int pArg2, int *pDwArg3)  // sub_4B3470 —— map 带位置插入
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v6 = fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *(uint8_t *)(v6 + 25) == 0 )
  {
    v8 = *pDwArg3;
    do
    {
      v7 = v8 < *(uint32_t *)(v6 + 12);
      fld_e1 = (int *)v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= *(uint32_t *)(v6 + 12) )
        v6 = *(uint32_t *)(v6 + 8);  // 读字段 v6 = v6+8（nSkillRec8）
      else
        v6 = *(uint32_t *)v6;
    }
    while ( *(uint8_t *)(v6 + 25) == 0 );  // 写字段 v6+25 ← = 0 )
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  pDwArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == (int *)**(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_4B2F90(this, (int *)&pDwArg3, 1, fld_e1, (int)pDwArg32);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4B0CC0(&pDwArg3);  // sub_4B0CC0 —— RB 树迭代器自减（中序前驱）
    fld_e12 = pDwArg3;
  }
  if ( fld_e12[3] >= *pDwArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_4B2F90(this, (int *)&pDwArg3, v13, fld_e1, (int)pDwArg32);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4B3530 sub_4B3530 —— 转发 thunk（·0x4B3170）
//   转发 ·0x4B3170（尾部记录右移拷贝）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4B3530(int nArg1, int nArg2, uint32_t *uArg3)  // sub_4B3530 —— 转发 thunk（·0x4B3170）
{
  return sub_4B3170(nArg1, nArg2, uArg3);  // sub_4B3170 —— 尾部右移拷贝（·0x4B2970 反向）
}



// ------------------------------------------------------------
// 0x4B3550 sub_4B3550 —— 记录填充（·0x4B2820 逐条）
//   用 nArg3 记录填充 nArg2 个槽（·0x4B2820 逐条，152 字节/条），返回尾地址。
// ------------------------------------------------------------
char */*cdecl*/ sub_4B3550(char *pszArg1, int nArg2, int nArg3)  // sub_4B3550 —— 记录填充（·0x4B2820 逐条）
{
  char *pszArg12; // esi
  char *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pszArg12 = pszArg1;
  v6[4] = v6;
  v6[3] = pszArg1;
  v7 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    LOBYTE(v7) = 1;
    if ( pszArg12 != nullptr )
      result = sub_4B2820(pszArg12, nArg3);  // sub_4B2820 —— avatar 配置记录拷贝构造（152 字节）
    --nArg2;  // 计数自减 nArg2
    pszArg12 += 152;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B3600 sub_4B3600 —— 指针容器拷贝赋值
//   先 ·0x401950 预分配，再经 ·0x4B1550 逐元素复制到 this+8，尾指针写入 this+16。
// ------------------------------------------------------------
unsigned int ***/*thiscall*/ sub_4B3600(unsigned int ***this, int pArg2)  // sub_4B3600 —— 指针容器拷贝赋值
{
  int v3; // ecx
  unsigned int v4; // eax
  unsigned int **v6; // [esp-14h] [ebp-34h]
  unsigned int **v7; // [esp-10h] [ebp-30h]
  unsigned int **fld_e1; // [esp-Ch] [ebp-2Ch]
  uint32_t v9[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = *(uint32_t *)(pArg2 + 4);  // 读字段 v3 = pArg2+4（pHostObj）
  v9[4] = v9;
  v9[3] = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
  else
    v4 = 0;
  if ( sub_401950(this, v4) != 0 )  // sub_401950 —— 指针 vector::reserve(n) 模板实例（new(4n)，起/止/容量三指针就位）
  {
    fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
    v7 = *(unsigned int ***)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v6 = *(unsigned int ***)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v9[7] = 0;
    *(this + 2) = sub_4B1550(v6, v7, fld_e1);  // sub_4B1550 —— 指针容器区间拷贝构造
  }
  return this;
}



// ------------------------------------------------------------
// 0x4B36A0 sub_4B36A0 —— 挂载槽部件（观察者 vmt310）
//   经 ·0x52DAD0 装备观察者挂载后刷新动画/渲染(vt+288/+289)，遍历 vt+248 的 124 字节子项
//   经 ·0x4B1C80 下发部位参数再 vt+268 绑定；类型(vt+172)==8 时从 +7428 宿主取元素
//   (·0x4B33E0) 走 vt+174/+269 通道并释放旧句柄；末尾 ·0x484D00 汇总槽统计。
// ------------------------------------------------------------
int */*userpurge*/ sub_4B36A0@<eax>(int **pDwArg1@<ecx>, unsigned int uArg2@<ebx>, int *pDwArg3)  // 实现：挂载槽部件（观察者 vmt310）
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
      sub_47E4F0();  // sub_47E4F0 —— 调用 sub_47E4F0
    v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg3 + 248))(pDwArg3);  // 虚调用 vt+248（pDwArg3 虚表槽）
    v8 = *(uint32_t **)(v7 + 4);
    v15 = v7;
    if ( v8 != *(uint32_t **)(v7 + 8) )
    {
      v9 = (int **)(v8 + 18);
      do
      {
        sub_4B1C80((int)(pDwArg1 + 1540), (int)(v9 - 17), pDwArg1 + 1803, v9);  // sub_4B1C80 —— 部位参数组下发（+40/+44/+56 → sub_4B0DF0 重载动画）
        ((void (/*thiscall*/ *)(int **, uint32_t, int **, int **))(*pDwArg1)[268])(pDwArg1, *v8, pDwArg1 + 1803, v9);
        v8 += 31;
        v9 += 31;
      }
      while ( v8 != *(uint32_t **)(v15 + 8) );
      pDwArg32 = pDwArg3;
    }
    if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pDwArg32 + 172))(pDwArg32) == 8 )  // 虚调用 vt+172（pDwArg32 虚表槽）
    {
      if ( pDwArg1[1857] != nullptr && v16 != nullptr )
      {
        v10 = (*(int (/*thiscall*/ **)(int *))(*v16 + 188))(v16);  // 虚调用 vt+188（v16）取尺寸
        if ( sub_41A5E0(v10 + 4) != 0 )  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        {
          v11 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1[1857] + 248))(pDwArg1[1857], 0);  // 调虚槽 +248：区间长 = vt+244 - vt+240
          v12 = sub_4B33E0(v11, uArg2);  // sub_4B33E0 —— 容器下标（124 字节/元素）
          ((void (/*thiscall*/ *)(int **, int **))(*pDwArg1)[174])(pDwArg1, pDwArg1 + 1540);
          ((void (/*thiscall*/ *)(int **, int **, int))(*pDwArg1)[269])(pDwArg1, pDwArg1 + 1803, v12 + 72);
        }
      }
      v13 = pDwArg1[1857];
      if ( v13 != nullptr )
        (*(void (/*thiscall*/ **)(int *, int))(*v13 + 4))(v13, 1);  // 虚调用 vt+4（v13）对象赋值/迁移
      pDwArg1[1857] = nullptr;
    }
    sub_484D00((int *)dword_8F852C);  // sub_484D00 —— 槽汇总统计（累加各对象虚表 +36 值）
    v6 = v16;
  }
  return v6 == pDwArg1[*(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*pDwArg32 + 172))(pDwArg32) + 1879] ? nullptr : v6;  // 虚调用 vt+172（pDwArg32 虚表槽）
}



// ============================================================
// §G 0x4B3820-0x4B49B0  avatar 变更/比较（[none]）
// ============================================================
// ------------------------------------------------------------
// 0x4B3820 sub_4B3820 —— avatar 名称查询/[none] 判定（sub_40BF00 比较）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4B3820(int *this, int nArg2)  // sub_4B3820 —— avatar 名称查询/[none] 判定（sub_40BF00 比较）
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
  switch ( *(uint32_t *)nArg2 )  // 按 *(uint32_t *)nArg2 分派
  {
    case 0xB:  // case 0xB 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
    case 0xC:  // case 0xC 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
    case 0xD:  // case 0xD 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
    case 0xE:  // case 0xE 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
      goto LABEL_4;
    case 0xF:  // case 0xF 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
    case 0x10:  // case 0x10 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
      dword_8F85402 = dword_8F8540;  // dword_8F8540 —— 逐条处理型别 fld[68]==0 的条件条目：为已注册
      nArg2 = 15;
      if ( *(uint32_t *)sub_472E30(v18, &nArg2) != *(uint32_t *)(dword_8F85402 + 52) )  // 物品栏刷新器
      {
        v6 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 672))(this, 0, 1041865114);  // 虚调用 vt+672（this）队伍编号取址
        sub_4AED60((void *)(v6 + 830), v17);  // 调 (推断)防篡改浮点自增（读 sub_41A5E0 → +a2 → 写 sub_41A590）
        v7 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 672))(this, 0);  // 虚调用 vt+672（this）队伍编号取址
        sub_4AED60((void *)(v7 + 858), 0.15000001);  // 调 (推断)防篡改浮点自增（读 sub_41A5E0 → +a2 → 写 sub_41A590）
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);  // 虚调用 vt+676（this）队伍编号刷新
LABEL_4:
        dword_8F85402 = dword_8F8540;  // dword_8F8540 —— 逐条处理型别 fld[68]==0 的条件条目：为已注册
      }
      nArg2 = 7;
      result = *(uint32_t *)sub_472E30(v18, &nArg2);  // 调 在本表定位：命中取节点值 +16 对象
      if ( result == *(uint32_t *)(dword_8F85402 + 52) )  // 物品栏刷新器
      {
        v8 = *this;
        nArg2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 752))(this, 1);  // 虚调用 vt+752（this 虚表槽）
        result = (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(v8 + 748))(  // 调虚槽 +748：[RTTI: IRDActiveObject__vmt2EC · 槽位 IRDActiveObj…
                   this,
                   (uint64_t)((double)nArg2 * 0.75) >> 32,
                   (uint64_t)((double)nArg2 * 0.75));
        if ( (int *)dword_8F7C04 != this )  // dword_8F7C04（本地玩家对象）
          return result;
        v9 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
        v10 = sub_422E70(857);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
        result = sub_43BEE0(v9, v10, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
      }
LABEL_8:
      if ( (int *)dword_8F7C04 != this )  // dword_8F7C04（本地玩家对象）
        return result;
      result = sub_568A70((uint8_t)byte_99FCD0, (uint8_t)byte_99FCD1);  // sub_568A70 —— 频道条目组装（568940/568800）
      v11 = result;
      if ( result == 0 )
        return result;
      result = sub_40BF00((std::_String_base *)(result + 32), 0, *(uint32_t *)(result + 52), "[none]", 6u);  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
      if ( result == 0 )
        return result;
      v12 = *(uint32_t *)(v11 + 88);  // 读字段 v12 = v11+88（pFxObjB）
      if ( v12 == 0 )
        return result;
      v13 = 0;
      break;
    default:
      goto LABEL_8;
  }
  while ( 1 )
  {
    v14 = *(uint32_t *)(v12 + 4);  // 读字段 v14 = v12+4（pHostObj）
    if ( v14 == 0 )
      break;
    result = (*(uint32_t *)(v12 + 8) - v14) >> 2;
    if ( v13 >= result )
      break;
    result = *(uint32_t *)(v14 + 4 * v13);
    if ( result == *v2 )
    {
      v15 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      v16 = sub_422E70(1245);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      return sub_43BEE0(v15, v16, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
    }
    ++v13;  // 计数自增 v13
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B3A00 sub_4B3A00 —— map 唯一插入总入口
//   空树或首/尾边界直接经 ·0x4B2F90 插入，否则按键(节点 +12) 定位后经 ·0x4B3470 插入。
// ------------------------------------------------------------
int */*thiscall*/ sub_4B3A00(int this, int *pDwArg2, int *pDwArg3, int *pDwArg4)  // sub_4B3A00 —— map 唯一插入总入口
{
  int *fld_4; // eax
  int *pDwArg42; // esi
  int *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    sub_4B2F90((int **)this, pDwArg2, 1, *(int **)(this + 4), (int)pDwArg4);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
    return pDwArg2;
  }
  fld_4 = *(int **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  pDwArg42 = pDwArg4;
  if ( pDwArg3 == (int *)*fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    if ( *pDwArg4 < pDwArg3[3] )
    {
      sub_4B2F90((int **)this, pDwArg2, 1, pDwArg3, (int)pDwArg4);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
      return pDwArg2;
    }
    goto LABEL_22;
  }
  if ( pDwArg3 == fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    v8 = (int *)fld_4[2];  // fld_4=this+16 nChannelTypeSel
    if ( v8[3] < *pDwArg4 )
    {
      sub_4B2F90((int **)this, pDwArg2, 0, v8, (int)pDwArg4);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
      return pDwArg2;
    }
    goto LABEL_22;
  }
  if ( *pDwArg4 >= pDwArg3[3] || (pDwArg4 = pDwArg3, sub_4B0CC0(&pDwArg4), pDwArg4[3] >= *pDwArg42) )  // sub_4B0CC0 —— RB 树迭代器自减（中序前驱）
  {
    if ( pDwArg3[3] >= *pDwArg42 || (pDwArg4 = pDwArg3, sub_4B0C60((int *)&pDwArg4), pDwArg4 != *(int **)(this + 4)) && *pDwArg42 >= pDwArg4[3] )  // sub_4B0C60 —— RB 树迭代器自增（中序后继）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4B3470((int **)this, (int)v10, pDwArg42);  // sub_4B3470 —— map 带位置插入
      *pDwArg2 = v9;
      return pDwArg2;
    }
    if ( *(uint8_t *)(pDwArg3[2] + 25) != 0 )
      sub_4B2F90((int **)this, pDwArg2, 0, pDwArg3, (int)pDwArg42);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
    else
      sub_4B2F90((int **)this, pDwArg2, 1, pDwArg4, (int)pDwArg42);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
    return pDwArg2;
  }
  else
  {
    if ( *(uint8_t *)(pDwArg4[2] + 25) != 0 )
      sub_4B2F90((int **)this, pDwArg2, 0, pDwArg4, (int)pDwArg42);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
    else
      sub_4B2F90((int **)this, pDwArg2, 1, pDwArg3, (int)pDwArg42);  // sub_4B2F90 —— std::map 插入 + 红黑再平衡
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4B3B60 sub_4B3B60 —— 16 字节元素区间拷贝
//   逐条 ·0x41DC80 拷贝（16 字节/元素），返回尾地址。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B3B60(int nArg1, int nArg2, int nArg3)  // sub_4B3B60 —— 16 字节元素区间拷贝
{
  int nArg12; // esi
  int nArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    sub_41DC80(nArg32, nArg12);  // sub_41DC80 —— vector<T 4B 驻留句柄> 拷贝赋值 operator=
    nArg12 += 16;
    nArg32 += 16;
  }
  while ( nArg12 != nArg2 );  // 循环直到 nArg12 != nArg2
  return nArg32;
}



// ------------------------------------------------------------
// 0x4B3BA0 sub_4B3BA0 —— 24 字节记录反向拷贝
//   自后向前 ·0x4ED3F0 拷贝并复制 +16/+20 字段（24 字节/条）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B3BA0(int nArg1, int nArg2, int nArg3)  // sub_4B3BA0 —— 24 字节记录反向拷贝
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
    sub_4ED3F0(nArg32, nArg22);  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
    *(uint32_t *)(nArg32 + 16) = *(uint32_t *)(nArg22 + 16);  // 写字段 nArg32+16（nChannelTypeSel） ← *(uint32_t *)(nArg22 + 16)
    *(uint32_t *)(nArg32 + 20) = *(uint32_t *)(nArg22 + 20);  // 写字段 nArg32+20（nPage） ← *(uint32_t *)(nArg22 + 20)
  }
  while ( nArg22 != nArg1 );  // 循环直到 nArg22 != nArg1
  return nArg32;
}



// ------------------------------------------------------------
// 0x4B3BE0 sub_4B3BE0 —— clong 组合初始化
//   三个 clong 成员(+4/+32/+72) 挂 clong 虚表并置初值 0/0/-1(·0x41A590)，+48 缓冲初始化，
//   类型码 *this=18、+52..+60 清零。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B3BE0(uint32_t *this)  // sub_4B3BE0 —— clong 组合初始化
{
  uint32_t *pThis_1; // ebx
  int v3; // edx
  int v4; // edx
  int v5; // edx

  pThis_1 = this + 1;
  sub_41A630((unsigned int)(this + 1));  // sub_41A630 —— 调 sub_41A630
  *pThis_1 = &clong::`vftable';  // 构造装配 vftable：clong
  sub_41A630((unsigned int)this + 18);  // sub_41A630 —— 调 sub_41A630
  *(uint32_t *)((char *)this + 18) = &clong::`vftable';  // this+18〔bDragChild〕
  sub_41A630((unsigned int)(this + 8));  // sub_41A630 —— 调 sub_41A630
  *(this + 8) = &clong::`vftable';  // 写字段 this+8（nSkillRec8） ← &clong::`vftable
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  *(this + 14) = 0;  // 写字段 this+14 ← 0
  *(this + 15) = 0;  // 写字段 this+15 ← 0
  *this = 18;
  sub_41A590((unsigned int)pThis_1, v3, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)this + 18, v4, 0);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590((unsigned int)(this + 8), v5, -1);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_4017E0((int)(this + 12));  // sub_4017E0 —— 指针 vector 释放（逐元素 ·sub_41B010 后 free 缓冲，三字段清零）
  return this;
}



// ------------------------------------------------------------
// 0x4B3C90 sub_4B3C90 —— CNChangeStatus 构造（双参）
//   基类 ·0x4B1030 + 挂 CNChangeStatus 虚表；清零两组容器头(+84..+92、+112..+120)，末经 ·0x5F7700 应用参数。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B3C90(int this, int nArg2, int nArg3)  // sub_4B3C90 —— 结果 = CNChangeStatus 构造（双参）
{
  sub_4B1030((uint8_t *)this);  // sub_4B1030 —— IRDAppendage 基类构造
  *(uint32_t *)this = &CNChangeStatus::`vftable';  // 构造装配 vftable：CNChangeStatus
  *(uint32_t *)(this + 84) = 0;  // 写字段 this+84（pFxObjA） ← 0
  *(uint32_t *)(this + 88) = 0;  // 写字段 this+88（pFxObjB） ← 0
  *(uint32_t *)(this + 92) = 0;  // 写字段 this+92（pFxObjC） ← 0
  *(uint32_t *)(this + 112) = 0;  // 写字段 this+112（pHostComp） ← 0
  *(uint32_t *)(this + 116) = 0;  // 写字段 this+116（pSessionCtx） ← 0
  *(uint32_t *)(this + 120) = 0;  // 写字段 this+120（pAnimObj） ← 0
  sub_5F76F0(this);
  sub_5F7700(nArg2, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x4B3D20 sub_4B3D20 —— 删除器（析构+释放）
//   调 ·0x4B3D50 析构；pszArg2 低位为 1 时 j__free 释放内存。
// ------------------------------------------------------------
void */*thiscall*/ sub_4B3D20(void *Block, char pszArg2)  // sub_4B3D20 —— 删除器（析构+释放）
{
  sub_4B3D50();  // sub_4B3D50 —— CNChangeStatus 析构
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4B3D50 sub_4B3D50 —— CNChangeStatus 析构
//   挂 CNChangeStatus 虚表 + ·0x5F8960，释放两组容器缓冲(+112/+84)，回退 IRDAppendage/nengine::IObject 并清零 +12。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B3D50(void **this)  // sub_4B3D50 —— CNChangeStatus 析构
{
  int result; // eax

  *this = &CNChangeStatus::`vftable';  // 构造装配 vftable：CNChangeStatus
  sub_5F8960();
  if ( *(this + 28) != nullptr )  // this+112〔pHostComp112〕
    j__free(*(this + 28));  // 释放堆块
  *(this + 28) = nullptr;  // 写字段 this+28（pPanelVec） ← nullptr
  *(this + 29) = nullptr;  // 写字段 this+29 ← nullptr
  *(this + 30) = nullptr;  // 写字段 this+30 ← nullptr
  if ( *(this + 21) != nullptr )  // this+84〔pFxObjA(推断)〕
    j__free(*(this + 21));  // 释放堆块
  *(this + 21) = nullptr;  // 写字段 this+21（bArmorState） ← nullptr
  *(this + 22) = nullptr;  // 写字段 this+22 ← nullptr
  *(this + 23) = nullptr;  // 写字段 this+23 ← nullptr
  *this = &IRDAppendage::`vftable';  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640(this);  // 调 基类析构
  *((uint8_t *)this + 12) = 0;  // 写字段 this+12（nSkillRec12）
  *(this + 2) = &nengine::IObject::`vftable';  // 写字段 this+2 ← &nengine::IObject::`vftable
  return result;
}



// ------------------------------------------------------------
// 0x4B3DF0 sub_4B3DF0 —— CNChangeStatus 构造（六参）
//   与 ·0x4B3C90 同构（差异：六参数经 ·0x5F7720 应用）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B3DF0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // sub_4B3DF0 —— 存 CNChangeStatus 状态附加(状态=3, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
{
  sub_4B1030();  // sub_4B1030 —— IRDAppendage 基类构造
  *this = &CNChangeStatus::`vftable';  // 构造装配 vftable：CNChangeStatus
  *(this + 21) = 0;  // 写字段 this+21（bArmorState） ← 0
  *(this + 22) = 0;  // 写字段 this+22 ← 0
  *(this + 23) = 0;  // 写字段 this+23 ← 0
  *(this + 28) = 0;  // 写字段 this+28（pPanelVec） ← 0
  *(this + 29) = 0;  // 写字段 this+29 ← 0
  *(this + 30) = 0;  // 写字段 this+30 ← 0
  sub_5F76F0(this);
  sub_5F7720(nArg2, nArg3, nArg4, nArg5, nArg6);
  return this;
}



// ------------------------------------------------------------
// 0x4B3E70 sub_4B3E70 —— Buff 图标/状态附加物增删
//   id 187/185/172/173/174 走 CNArmorMastery(+8068，参数=职业) 的 ·0x5F74E0(+)/·0x5F6EE0(-)；
//   178/189/186/188 在 +8072..+8084 建 CNChangeStatus(·0x4B3C90)，时长=·0x47EF20*0.1，
//   图标索引 178/189 取 14/15、186/188 取 12/13；nArg3 不大于 0 时经 ·0x53FE50 拆卸。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B3E70(int *this, void *Block, int nArg3)  // sub_4B3E70 —— Buff 图标/状态附加物增删
{
  int *pObj3; // ebx
  int pObj; // eax
  int pObj2; // eax
  int fld_e1787; // eax  | +0x1BEC → ★大状态 ID（IRDCharacter；va=005796C0）
  float v8; // [esp+24h] [ebp+Ch]
  float v9; // [esp+24h] [ebp+Ch]

  if ( Block == (void *)187
    || Block == (void *)185
    || Block == (void *)172
    || Block == (void *)173
    || Block == (void *)174 )  // Buff 图标/状态附加物增删
  {
    if ( *(this + 2017) == 0 )
    {
      if ( operator new(0xB4u) != nullptr )  // 堆分配
        fld_e1787 = sub_4B11A0(*(this + 1787));  // sub_4B11A0 —— CNArmorMastery 构造（参数=职业）
      else
        fld_e1787 = 0;
      *(this + 2017) = fld_e1787;  // 写字段 this+2017 ← fld_e1787
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1787 + 64))(fld_e1787) + 36) = 0;  // 虚调用 vt+64（fld_e1787）读游标登记(跳过包头)
    }
    if ( nArg3 != 0 )
      sub_5F74E0(*(this + 2017), (int)Block);
    else
      sub_5F6EE0(Block);
    if ( Block == (void *)187 )
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2017) + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
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
          if ( operator new(0x7Cu) != nullptr )  // 堆分配
            pObj = sub_4B3C90(0, 0);  // sub_4B3C90 —— 结果 = CNChangeStatus 构造（双参）
          else
            pObj = 0;
          *pObj3 = pObj;
          *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 虚调用 vt+64（pObj）读游标登记(跳过包头)
        }
        (*(void (/*thiscall*/ **)(int *, void *))(*this + 1160))(this, Block);  // 虚调用 vt+1160（this）读技能表(变体)
        v8 = (double)(int)sub_47EF20(0, nArg3, -1, -1, 11) * 0.1;  // sub_47EF20 —— 读攻击数据表
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)*pObj3 + 124))(*pObj3);  // 虚调用 vt+124（pObj3）目标坐标y下界
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)*pObj3 + 120))(  // 虚调用 vt+120（pObj3）转发(对象+缓冲)
          *pObj3,
          (Block != (void *)186) + 12,
          0,
          LODWORD(v8));
        (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*pObj3 + 56))(  // 虚调用 vt+56（pObj3 虚表槽）
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
      if ( *pObj3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)*pObj3 + 80))(*pObj3) != 0 )  // 虚调用 vt+80（pObj3）读 4 字节
        sub_53FE50(*pObj3);  // 调 按指针移除：找到 a2 → vt+32(0) → memmove 收缩 → vt+76/vt+68(0)
      return;
    }
    if ( *pObj3 == 0 )
    {
      if ( operator new(0x7Cu) != nullptr )  // 堆分配
        pObj2 = sub_4B3C90(0, 0);  // sub_4B3C90 —— 结果 = CNChangeStatus 构造（双参）
      else
        pObj2 = 0;
      *pObj3 = pObj2;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;  // 虚调用 vt+64（pObj2）读游标登记(跳过包头)
    }
    (*(void (/*thiscall*/ **)(int *, void *))(*this + 1160))(this, Block);  // 虚调用 vt+1160（this）读技能表(变体)
    v9 = (double)(int)sub_47EF20(0, nArg3, -1, -1, 11) * 0.1;  // sub_47EF20 —— 读攻击数据表
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)*pObj3 + 124))(*pObj3);  // 虚调用 vt+124（pObj3）目标坐标y下界
    (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t))(*(uint32_t *)*pObj3 + 120))(  // 虚调用 vt+120（pObj3）转发(对象+缓冲)
      *pObj3,
      (Block != (void *)178) + 14,
      0,
      LODWORD(v9));
    (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*pObj3 + 56))(  // 虚调用 vt+56（pObj3 虚表槽）
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
int /*thiscall*/ sub_4B4170(float *this, uint32_t *Block, void *pArg3)  // sub_4B4170 —— ★Buff 图标条装配
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

  result = sub_41A5E0((unsigned int)(Block + 1));  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  switch ( result )  // 按 result 分派
  {
    case 175:  // case 175 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
      v5 = sub_47EF20(0, pArg3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      v25 = (void *)sub_47E9D0(Block, 0);  // sub_47E9D0 —— 收招/结束例程
      if ( *((uint32_t *)this + 1994) == 0 )
      {
        pMem = operator new(0x7Cu);  // 堆分配
        if ( pMem != nullptr )
        {
          *(float *)&v20 = (float)(int)v25;
          v7 = sub_4B3DF0(pMem, 6, 0, v20, v5, 1);  // sub_4B3DF0 —— 存 CNChangeStatus 状态附加(状态=3, 标志=1, 数值=-100.0f, 时长=60000ms, 1)
        }
        else
        {
          v7 = nullptr;
        }
        *((uint32_t *)this + 1994) = v7;  // 写字段 this[1994]（宽4字节）
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 64))(v7) + 36) = 0;  // 虚调用 vt+64（v7）读游标登记(跳过包头)
      }
      if ( (uint8_t)sub_53F660(*((uint32_t *)this + 1994)) != 0 )  // 调 附属 vector 线性查找：+1/+2 首/尾，命中 *p==a2 返回 1
        sub_53FE50(*((uint32_t *)this + 1994));  // 调 按指针移除：找到 a2 → vt+32(0) → memmove 收缩 → vt+76/vt+68(0)
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1994) + 64))(*((uint32_t *)this + 1994)) + 40) = v5;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      pThis_7CA = **((uint32_t **)this + 1994);
      v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
                       dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
                       "Common/CommonEffect/BuffIcon.img",  // 资源路径 Common/CommonEffect/BuffIcon.img
                       4,
                       0,
                       -1);
      sub_418DD0(v9, v22);  // sub_418DD0 —— 资源句柄 (101)
      (*(void (/*thiscall*/ **)(uint32_t, float *, float *, int))(pThis_7CA + 56))(*((uint32_t *)this + 1994), this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      return (*(int (/*thiscall*/ **)(float *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
               this,
               "BUFF_LEAP",  // 资源/动画 TAG BUFF_LEAP
               -1,
               0,
               0);
    case 176:  // case 176 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
      Blocka = (void *)sub_47EF20(0, pArg3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      v26 = (void *)sub_47EF20(1, pArg3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      if ( *((uint32_t *)this + 1995) == 0 )
      {
        pMem2 = operator new(0x7Cu);  // 堆分配
        if ( pMem2 != nullptr )
          pObj2 = sub_4B3C90((int)pMem2, 0, 1);  // sub_4B3C90 —— 结果 = CNChangeStatus 构造（双参）
        else
          pObj2 = 0;
        *((uint32_t *)this + 1995) = pObj2;  // 写字段 this[1995]（宽4字节）
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;  // 虚调用 vt+64（pObj2）读游标登记(跳过包头)
      }
      if ( (uint8_t)sub_53F660(*((uint32_t *)this + 1995)) != 0 )  // 调 附属 vector 线性查找：+1/+2 首/尾，命中 *p==a2 返回 1
        sub_53FE50(*((uint32_t *)this + 1995));  // 调 按指针移除：找到 a2 → vt+32(0) → memmove 收缩 → vt+76/vt+68(0)
      (*(void (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1995) + 124))(*((uint32_t *)this + 1995));  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
      v21 = (float)(int)v26;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(**((uint32_t **)this + 1995) + 120))(1, 0, LODWORD(v21));  // 调虚槽 +120：动画对象
      *(uint32_t *)(*((uint32_t *)this + 1995) + 44) = Blocka;
      pThis_7CB = **((uint32_t **)this + 1995);
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
                        dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
                        "Common/CommonEffect/BuffIcon.img",  // 资源路径 Common/CommonEffect/BuffIcon.img
                        5,
                        0,
                        -1);
      sub_418DD0(v13, v22);  // sub_418DD0 —— 资源句柄 (101)
      (*(void (/*thiscall*/ **)(uint32_t, float *, float *, int))(pThis_7CB + 56))(*((uint32_t *)this + 1995), this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
      return (*(int (/*thiscall*/ **)(float *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
               this,
               "BUFF_INTUP",  // 资源/动画 TAG BUFF_INTUP
               -1,
               0,
               0);
    case 180:  // case 180 分派（§G 0x4B3820-0x4B49B0 avatar 变更/比较（[none]））
      Blockb = (void *)sub_47EF20(1, pArg3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      v14 = (double)(int)sub_47EF20(0, pArg3, -1, -1, 11);  // sub_47EF20 —— 读攻击数据表
      pThis_7CC = *((uint32_t *)this + 1996);  // 读字段 pThis_7CC = this[1996]
      *(this + 1997) = v14 * 0.1;  // 写字段 this+1997 ← v14 * 0.1
      if ( pThis_7CC == 0 )
      {
        pMem3 = operator new(0x50u);  // 堆分配
        if ( pMem3 != nullptr )
          pObj = sub_4B1030(pMem3);  // sub_4B1030 —— IRDAppendage 基类构造
        else
          pObj = nullptr;
        *((uint32_t *)this + 1996) = pObj;  // 写字段 this[1996]（宽4字节）
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;  // 虚调用 vt+64（pObj）读游标登记(跳过包头)
      }
      if ( (uint8_t)sub_53F660(*((uint32_t *)this + 1996)) != 0 )  // 调 附属 vector 线性查找：+1/+2 首/尾，命中 *p==a2 返回 1
        sub_53FE50(*((uint32_t *)this + 1996));  // 调 按指针移除：找到 a2 → vt+32(0) → memmove 收缩 → vt+76/vt+68(0)
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1996) + 64))(*((uint32_t *)this + 1996)) + 40) = Blockb;  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
      pThis_7CC2 = **((uint32_t **)this + 1996);
      v19 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, int))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
                        dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
                        "Common/CommonEffect/BuffIcon.img",  // 资源路径 Common/CommonEffect/BuffIcon.img
                        21,
                        0,
                        -1);
      sub_418DD0(v19, v22);  // sub_418DD0 —— 资源句柄 (101)
      return (*(int (/*thiscall*/ **)(uint32_t, float *, float *, int))(pThis_7CC2 + 56))(*((uint32_t *)this + 1996), this, this, 1);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 确认…
    default:
      break;
  }
  return result;
}


// ------------------------------------------------------------
// 0x4B44E0 sub_4B44E0 —— map 查或插入返回 +16
//   lower_bound 命中返回节点值 +16；未命中经 ·0x4B3A00 插入空值（键 +12）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B44E0(int **this, int *pDwArg2)  // sub_4B44E0 —— map 查或插入返回 +16
{
  int *fld_e1; // edx
  int v3; // eax
  int v4; // edi
  int v6[3]; // [esp+Ch] [ebp-Ch] BYREF

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v3 = fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *(uint8_t *)(v3 + 25) == 0 )  // 当 *(uint8_t *)(v3 + 25) == 0 循环
  {
    if ( *(uint32_t *)(v3 + 12) >= *pDwArg2 )
    {
      fld_e1 = (int *)v3;  // fld_e1=this+4 宿主对象
      v3 = *(uint32_t *)v3;
    }
    else
    {
      v3 = *(uint32_t *)(v3 + 8);  // 读字段 v3 = v3+8（nSkillRec8）
    }
  }
  if ( fld_e1 != *(this + 1) && *pDwArg2 >= fld_e1[3] )  // fld_e1=this+4 宿主对象
    return (int)(fld_e1 + 4);  // fld_e1=this+4 宿主对象
  v4 = *pDwArg2;
  v6[1] = 0;
  v6[0] = v4;
  v6[2] = 0;
  return *sub_4B3A00((int)this, (int *)&pDwArg2, fld_e1, v6) + 16;  // sub_4B3A00 —— map 唯一插入总入口
}



// ------------------------------------------------------------
// 0x4B4560 sub_4B4560 —— 填充包装（返回尾指针）
//   调 ·0x4B3550 填充 nArg2 条后返回 &pszArg1[152*nArg2]。
// ------------------------------------------------------------
char */*stdcall*/ sub_4B4560(char *pszArg1, int nArg2, int nArg3)  // sub_4B4560 —— 填充包装（返回尾指针）
{
  sub_4B3550(pszArg1, nArg2, nArg3);  // sub_4B3550 —— 记录填充（·0x4B2820 逐条）
  return &pszArg1[152 * nArg2];
}



// ------------------------------------------------------------
// 0x4B4590 sub_4B4590 —— vector 记录插入 _Insert_n
//   插入 nArg4 记录 uArg3 次：容量足够就地右移(·0x4B31B0/·0x4B3530/·0x4B3140) 或分批拼接
//   (·0x4B4560)，不足则扩容重建；总长超限经 ·0x4A30C0 抛异常。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B4590(int *this, int pArg2, unsigned int uArg3, int nArg4)  // sub_4B4590 —— vector 记录插入 _Insert_n
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v31 = &v23;
  pThis = this;
  sub_4B2820(nArg4);  // sub_4B2820 —— avatar 配置记录拷贝构造（152 字节）
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  fld_e3 = 0;
  v32 = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) / 152;  // this+12〔nSkillRec12(推断)〕
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 152;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 28256363 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_4A30C0();
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 152;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = *(this + 2);  // 读字段 fld_e23 = this+2
      fld_e232 = fld_e23;  // fld_e23=this+8 物品 id
      if ( (fld_e23 - pArg2) / 152 >= uArg3 )  // fld_e23=this+8 物品 id
      {
        v33 = fld_e23 - 152 * uArg3;  // fld_e23=this+8 物品 id
        *(this + 2) = sub_4B31B0(v33, fld_e23, fld_e23);  // sub_4B31B0 —— 前向拷贝（·0x4B2820 逐条）
        sub_4B3530(pArg2, v33, fld_e232);  // sub_4B3530 —— 转发 thunk（·0x4B3170）
        sub_4B3140(pArg2, pArg2 + 152 * uArg3, v27);  // sub_4B3140 —— 区间填充（·0x4B2970 逐条）
      }
      else
      {
        sub_4B31B0(pArg2, fld_e23, pArg2 + 152 * uArg3);  // sub_4B31B0 —— 前向拷贝（·0x4B2820 逐条）
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 152;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        LOBYTE(v32) = 3;
        sub_4B4560(fld_e25, fld_e24, v27);  // sub_4B4560 —— 填充包装（返回尾指针）
        fld_e26 = 152 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        v32 = 0;
        sub_4B3140(pArg2, fld_e26 - 152 * uArg3, v27);  // sub_4B3140 —— 区间填充（·0x4B2970 逐条）
      }
    }
    else
    {
      if ( 28256363 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v10 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else
        v10 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 152;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v10 = uArg3 + sub_4B0BC0(this);  // sub_4B0BC0 —— 记录数统计（152 字节/条）
      v34 = 152 * v10;  // 计算 v34 = 152 * v10
      pMem = (char *)operator new(152 * v10);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v32) = 1;
      pMem2 = (char *)sub_4B31B0(fld_e12, pArg2, (int)pMem);  // sub_4B31B0 —— 前向拷贝（·0x4B2820 逐条）
      sub_4B3550((int)pMem2, uArg3, (int)v27);  // sub_4B3550 —— 记录填充（·0x4B2820 逐条）
      fld_e28 = *(this + 2);  // 读字段 fld_e28 = this+2
      pMem2 += 152 * uArg3;
      sub_4B31B0(pArg2, fld_e28, (int)pMem2);  // sub_4B31B0 —— 前向拷贝（·0x4B2820 逐条）
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 152;  // this+8〔nSkillRec8(推断)〕
      v14 = fld_e13 + uArg3;  // 计算 v14 = fld_e13 + uArg3
      fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
      if ( fld_e14 != 0 )  // fld_e14=this+4 宿主对象
      {
        sub_4A3870(fld_e14, *(this + 2));  // this+8〔nSkillRec8(推断)〕
        j__free((void *)*(this + 1));  // 释放堆块
      }
      *(this + 3) = (int)&pMem[v34];  // 写字段 this+3 ← (int)&pMem[v34]
      *(this + 2) = (int)&pMem[152 * v14];  // 写字段 this+2 ← (int)&pMem[152 * v14]
      *(this + 1) = (int)pMem;  // 写字段 this+1 ← (int)pMem
    }
  }
  if ( v29 >= 0x10 )
    j__free(v28);  // 释放堆块
}


// ------------------------------------------------------------
// 0x4B48D0 sub_4B48D0 —— 转发 thunk（·0x4B3B60）
//   转发 ·0x4B3B60（16 字节元素区间拷贝）。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B48D0(int nArg1, int nArg2, int nArg3)  // sub_4B48D0 —— 转发 thunk（·0x4B3B60）
{
  return sub_4B3B60(nArg1, nArg2, nArg3);  // sub_4B3B60 —— 16 字节元素区间拷贝
}



// ------------------------------------------------------------
// 0x4B48F0 sub_4B48F0 —— 24 字节记录前向拷贝（逐元素置为新值）
//   区间 [nArg1, nArg2) 步长 24：每步先 ·0x4ED3F0 复制前 16 字节（clong 组合），
//   再并列拷 +16/+20 两字段；返回末条 +16。与 ·0x4B3BA0（反向版，经 ·0x4B4930 转发）成对。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B48F0(int nArg1, int nArg2, int pArg3)  // sub_4B48F0 —— 24 字节记录前向拷贝（逐元素置为新值）
{
  int i; // esi
  int result; // eax

  for ( i = nArg1; i != nArg2; i += 24 )
  {
    sub_4ED3F0(i, pArg3);  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
    result = *(uint32_t *)(pArg3 + 16);  // 读字段 result = pArg3+16（nChannelTypeSel）
    *(uint32_t *)(i + 16) = result;  // 写字段 i+16（nChannelTypeSel） ← result
    *(uint32_t *)(i + 20) = *(uint32_t *)(pArg3 + 20);  // 写字段 i+20（nPage） ← *(uint32_t *)(pArg3 + 20)
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B4930 sub_4B4930 —— 24 字节记录拷贝转发（·0x4B3BA0）
//   纯转发 ·0x4B3BA0（自后向前拷 24 字节记录），供 ·0x4B5420 扩容路径复用。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B4930(int nArg1, int nArg2, int nArg3)  // sub_4B4930 —— 24 字节记录拷贝转发（·0x4B3BA0）
{
  return sub_4B3BA0(nArg1, nArg2, nArg3);  // sub_4B3BA0 —— 24 字节记录反向拷贝
}



// ------------------------------------------------------------
// 0x4B4950 sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
//   遍历 [nArg1, nArg2) 步长 16：每元素先逐项 ·0x41B010 释放 +4 指针数组，再 free 自身；
//   元素 +4/+8/+12 写 0 后返回区间末。与 ·0x4B5380（转发）同族。
// ------------------------------------------------------------
int /*cdecl*/ sub_4B4950(int nArg1, int nArg2)  // sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
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
        sub_41B010(v4);  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
      j__free(*(void **)(i + 4));  // 释放堆块
    }
    *(uint32_t *)(i + 4) = 0;  // 写字段 i+4（pHostObj） ← 0
    *(uint32_t *)(i + 8) = 0;  // 写字段 i+8（nSkillRec8） ← 0
    *(uint32_t *)(i + 12) = 0;  // 写字段 i+12（nSkillRec12） ← 0
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
char /*thiscall*/ sub_4B49B0(uint32_t *this, int ArgList)  // sub_4B49B0 —— ★Buff/技能使用处理
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( (uint32_t *)dword_8F7C04 != this || *(this + 50) == 2 )  // this+50 M_CHARACTER_SELECT 一次性发送标志
    return 0;
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, ArgList);  // 虚调用 vt+1160（this）读技能表(变体)
  v30 = sub_41A5E0((unsigned int)v3 + 510);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v40 = 1;
  if ( v30 == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v3 + 12))(v3) != 0 )  // 虚调用 vt+12（v3 虚表槽）
  {
    pThis_1802 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v4 = sub_422E70(853);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    sub_43BEE0(pThis_1802, v4, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
    sub_432EA0("ALERT_1", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    v40 = 0;
  }
  v5 = sub_41A5E0((unsigned int)v3 + 510);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  pThis_1802 = (uint32_t *)sub_41A5E0(v3[75] + 14 * (v5 - 1));  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v38 = COERCE_FLOAT(sub_41A5E0((unsigned int)(v3 + 131)));  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  v31 = (uint64_t)((double)(int)pThis_1802 * v38);
  pThis_1802 = (uint32_t *)((char *)this + 6146);
  if ( sub_41A5E0((unsigned int)this + 6146) < v31 )  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  {
    v6 = *((uint32_t **)dword_8F8528 + 7);  // dword_8F8528 —— 对象池借出（按池号取可用对象）
    v7 = sub_422E70(854);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    sub_43BEE0(v6, v7, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
    if ( *(this + 1939) < 0x10u )
      pThis_78E = this + 1934;
    else
      pThis_78E = (void *)*(this + 1934);
    sub_432EA0(pThis_78E, -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
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
      if ( Block2 != nullptr && (v9 - (int)Block2) >> 3 != 0 && (uint8_t)sub_486190(v33, 2) == 0 )  // sub_486190 —— 请求 op 18 批量版（槽数组）
      {
        sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)&unk_6F6130, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
        if ( *(this + 1939) < 0x10u )
          pThis_78E2 = this + 1934;
        else
          pThis_78E2 = (void *)*(this + 1934);
        sub_432EA0(pThis_78E2, -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
        Block2 = Block;
LABEL_39:
        if ( *((uint8_t *)this + 8100) != 1 )
        {
          *((uint8_t *)this + 8100) = 1;  // 写字段 this[8100]（宽1字节）
          *((uint8_t *)this + 8101) = 0;  // 写字段 this[8101]（宽1字节）
          *((uint8_t *)this + 8102) = 0;  // 写字段 this[8102]（宽1字节）
          sub_698F90((int)(this + 2022), 300, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
          Block2 = Block;
        }
        if ( Block2 != nullptr )
          j__free(Block2);  // 释放堆块
        return 0;
      }
    }
    else if ( v40 == 0 )
    {
      goto LABEL_39;
    }
    v21 = sub_41A5E0((unsigned int)pThis_1802);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 748))(this, v21 - v31, 1);  // 虚调用 vt+748（this）对象数据注入(data,flag)
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 26, 2);  // 虚调用 vt+8（dword_8F8520 虚表槽）
    v22 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
    v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);  // 虚调用 vt+48（this）归属坐标x
    (*(void (/*thiscall*/ **)(int, int))(v22 + 36))(dword_8F8520, v23);  // dword_8F8520 —— 虚表 +120 调用
    v24 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
    v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 虚调用 vt+52（this）归属坐标y
    (*(void (/*thiscall*/ **)(int, int))(v24 + 36))(dword_8F8520, v25);  // dword_8F8520 —— 虚表 +120 调用
    v26 = ArgList;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);  // 虚调用 vt+32（dword_8F8520 虚表槽）
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, v30);  // 虚调用 vt+32（dword_8F8520 虚表槽）
    v27 = sub_41A5E0((unsigned int)pThis_1802);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v27);  // 虚调用 vt+40（dword_8F8520）条件查询(273等)
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
    if ( v3[31] != 1 )
    {
      sub_423200(dword_8F7B08, 41);  // 【发送网络包API】
      HIBYTE(ArgList) = v26;
      sub_423290((char *)&ArgList + 3, 1);  // sub_423290 —— 写 4B 长度
      sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
      off_77F3FC("-> ENUM_CMDPACKET_USE_SKILL : SkillIndex %d", v26);  // off_77F3FC —— 日志打印（printf 风格）
    }
    if ( Block != nullptr )
      j__free(Block);  // 释放堆块
    return 1;  // 返回 1(成功)
  }
  while ( 1 )
  {
    v38 = *(float *)v11;
    v37 = sub_41A5E0((unsigned int)v3 + 510);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
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
  v14 = sub_484E80(LODWORD(v38));  // sub_484E80 —— 按类型查找下标（同一匹配规则，未命中 -1）
  v32 = v14;
  if ( v14 != -1 )
  {
    pObj = v14 >= *((uint32_t *)dword_8F852C + 2) ? 0 : *(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4 * v14);  // 角色/物品栏管理器
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 44))(pObj);  // 虚调用 vt+44（pObj 虚表槽）
    if ( v16 >= v37 )
    {
      v29[1] = v37;
      v29[0] = v32;
      sub_474950(v29);  // sub_474950 —— 调用 sub_474950
      goto LABEL_19;
    }
  }
  v28 = sub_4F2CE0(LODWORD(v38));  // sub_4F2CE0 —— 存 按物品 id 取名称串：查模板表
  v18 = (const char *)sub_422E70(855);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
  sprintf(Buffer, v18, v28);  // 调 格式化到缓冲
  sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
  if ( *(this + 1939) < 0x10u )
    pThis_78E3 = this + 1934;
  else
    pThis_78E3 = (void *)*(this + 1934);
  sub_432EA0(pThis_78E3, -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  if ( *((uint8_t *)this + 8100) != 1 )
  {
    *((uint8_t *)this + 8100) = 1;  // 写字段 this[8100]（宽1字节）
    *((uint8_t *)this + 8101) = 0;  // 写字段 this[8101]（宽1字节）
    *((uint8_t *)this + 8102) = 0;  // 写字段 this[8102]（宽1字节）
    sub_698F90((int)(this + 2022), 300, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  if ( Block != nullptr )
    j__free(Block);  // 释放堆块
  return 0;
}


// ------------------------------------------------------------
// 0x4B4EE0 sub_4B4EE0 —— 键到值 map 插入或删除（this+7416 处 map）
//   nArg3 非 0 经 ·0x4B44E0 查或插入，再把值双写为 nArg3；nArg3 为 0 先 ·0x4B1BA0
//   lower_bound 定位，命中（非 end）则 ·0x4B2BF0 删节点。【推断：键为资源/状态 id】
// ------------------------------------------------------------
int */*thiscall*/ sub_4B4EE0(int this, int nArg2, int nArg3)  // sub_4B4EE0 —— 键到值 map 插入或删除（this+7416 处 map）
{
  int nArg32; // edi
  int *result; // eax

  nArg32 = nArg3;
  if ( nArg3 != 0 )
  {
    result = (int *)sub_4B44E0((int **)(this + 7416), &nArg2);  // sub_4B44E0 —— map 查或插入返回 +16
    *result = nArg32;
    result[1] = nArg32;
  }
  else
  {
    sub_4B1BA0((int **)(this + 7416), (int **)&nArg3, &nArg2);  // sub_4B1BA0 —— map lower_bound（键在 +12）
    result = (int *)nArg3;
    if ( nArg3 != *(uint32_t *)(this + 7420) )  // this+7420〔map7416End〕
      return sub_4B2BF0((uint32_t *)(this + 7416), &nArg2, nArg3);  // sub_4B2BF0 —— std::map 节点删除（RB 再平衡）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B4F40 sub_4B4F40 —— 152 字节记录 vector 定值插入（返回插入位）
//   由 pszArg3 现址与 this+4/+8 算下标 v6（152 字节/元素），经 ·0x4B4590 _Insert_n 插 1 条，
//   *uArg2 回写插入位地址。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B4F40(uint32_t *this, uint32_t *uArg2, char *pszArg3, int nArg4)  // sub_4B4F40 —— 152 字节记录 vector 定值插入（返回插入位）
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 152 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 152;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_4B4590((int)this, pszArg3, 1u, nArg4);  // sub_4B4590 —— vector 记录插入 _Insert_n
  *uArg2 = *(this + 1) + 152 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x4B4FB0 sub_4B4FB0 —— 24 字节记录区间定值填充
//   向 [uArg1 起 nArg2 条、步长 24）逐条写 pArg3 内容：先 ·0x435020 拷 +0..+15
//   （uint32 向量整体赋值），再并列写 +16/+20。
// ------------------------------------------------------------
void /*cdecl*/ sub_4B4FB0(uint32_t *uArg1, int nArg2, void *pArg3)  // sub_4B4FB0 —— 24 字节记录区间定值填充
{
  uint32_t *uArg12; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v5[4] = v5;
  v5[3] = uArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    LOBYTE(v6) = 1;
    if ( uArg12 != nullptr )
    {
      sub_435020(pArg3);  // sub_435020 —— uint32 向量整体赋值
      uArg12[4] = *((uint32_t *)pArg3 + 4);
      uArg12[5] = *((uint32_t *)pArg3 + 5);
    }
    --nArg2;  // 计数自减 nArg2
    uArg12 += 6;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x4B5060 sub_4B5060 —— 16 字节记录区间拷贝（返回尾址）
//   步长 16 逐元素 ·0x4B3600（指针容器拷贝赋值），返回尾地址，供 ·0x4B5740
//   尾段追加与 ·0x4B5720 转发用。
// ------------------------------------------------------------
unsigned int ***/*cdecl*/ sub_4B5060(int nArg1, int nArg2, unsigned int ***uArg3)  // sub_4B5060 —— 16 字节记录区间拷贝（返回尾址）
{
  unsigned int ***uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 循环直到 nArg1 != nArg2
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )
      sub_4B3600(uArg32, nArg1);  // sub_4B3600 —— 指针容器拷贝赋值
    uArg32 += 4;
    LOBYTE(v7) = 0;
    nArg1 += 16;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x4B50F0 sub_4B50F0 —— 职业代表特效粒子表（格斗 NenMaster / 漫游 Ranger / 元素 ElementalMaster / 鬼泣 SoulBringer .ptl）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4B50F0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3, uint8_t *uArg4, void *Block, int nArg6, int nArg7)  // sub_4B50F0 —— 职业代表特效粒子表（格斗 NenMaster / 漫游 Ranger / 元素 ElementalMaster / 鬼泣 SoulBringer .ptl）
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
      pMem = operator new(0x12Cu);  // 堆分配
      if ( pMem != nullptr )
        v13 = sub_428F30(pMem, (int)"Character/Fighter/Effect/Particle/NenMaster.ptl", nArg7);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
      else
        v13 = nullptr;
      v7 = v13;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v13 + 112))(v13, nArg7);  // 虚调用 vt+112（v13）坐标三元组写入
      *uArg1 = 0;
      *uArg2 = -1;
      *uArg3 = 55;
    }
    else if ( Block == (void *)2 )
    {
      if ( nArg6 != 1 )
        return v7;
      pMem2 = operator new(0x12Cu);  // 堆分配
      if ( pMem2 != nullptr )
        v15 = sub_428F30(pMem2, (int)"Character/Gunner/Effect/Particle/Ranger.ptl", nArg7);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
      else
        v15 = nullptr;
      v7 = v15;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v15 + 112))(v15, nArg7);  // 虚调用 vt+112（v15）坐标三元组写入
      *uArg1 = 7;
      *uArg2 = 0;
      *uArg3 = 114;
    }
    else
    {
      if ( Block != (void *)3 || nArg6 != 1 )
        return v7;
      pMem3 = operator new(0x12Cu);  // 堆分配
      if ( pMem3 != nullptr )
        v17 = sub_428F30(pMem3, (int)"Character/Mage/Effect/Particle/ElementalMaster.ptl", nArg7);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
      else
        v17 = nullptr;
      v7 = v17;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*v17 + 112))(v17, nArg7);  // 虚调用 vt+112（v17）坐标三元组写入
      *uArg1 = 0;
      *uArg2 = -1;
      *uArg3 = 20;
    }
    *uArg4 = 1;
    return v7;
  }
  if ( nArg6 != 2 )
    return v7;
  pMem4 = operator new(0x12Cu);  // 堆分配
  if ( pMem4 != nullptr )
    v9 = sub_428F30(pMem4, (int)"Character/Swordman/Effect/Particle/SoulBringer.ptl", nArg7);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
  else
    v9 = nullptr;
  v10 = v9;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*v9 + 112))(v9, nArg7);  // 虚调用 vt+112（v9）坐标三元组写入
  *uArg1 = 0;
  *uArg2 = -1;
  *uArg3 = 70;
  *uArg4 = 1;
  return v10;
}



// ------------------------------------------------------------
// 0x4B52F0 sub_4B52F0 —— 152 字节记录 append（尾插一条）
//   容量足够（已用 < 已分配）时在 this+8 尾位经 ·0x4B3550 填 nArg2；否则走
//   ·0x4B4F40 扩容插入路径。返回新记录地址。
// ------------------------------------------------------------
char */*thiscall*/ sub_4B52F0(int this, int nArg2)  // sub_4B52F0 —— 152 字节记录 append（尾插一条）
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  char *fld_82; // edi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 152;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 152 )  // this+12 物品类型号
    return (char *)sub_4B4F40((uint32_t *)this, &nArg2, *(char **)(this + 8), nArg2);  // sub_4B4F40 —— 152 字节记录 vector 定值插入（返回插入位）
  fld_82 = *(char **)(this + 8);  // this+32〔nHeight(推断)〕
  result = sub_4B3550(fld_82, 1, nArg2);  // sub_4B3550 —— 记录填充（·0x4B2820 逐条）
  *(uint32_t *)(this + 8) = fld_82 + 152;  // 写字段 this+8（nSkillRec8） ← fld_82 + 152
  return result;
}



// ------------------------------------------------------------
// 0x4B5380 sub_4B5380 —— 16 字节记录数组析构转发（·0x4B4950）
//   纯转发 ·0x4B4950（逐元素释放 +4 指针数组再 free）。
// ------------------------------------------------------------
int /*stdcall*/ sub_4B5380(int nArg1, int nArg2)  // sub_4B5380 —— 16 字节记录数组析构转发（·0x4B4950）
{
  return sub_4B4950(nArg1, nArg2);  // sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
}



// ------------------------------------------------------------
// 0x4B53A0 sub_4B53A0 —— 152 字节记录 vector 清空析构
//   非空时 ·0x4B4950 析构 [this+1, this+2) 后 free 首址，再清 +4/+8/+12 三槽。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B53A0(int *this)  // sub_4B53A0 —— 152 字节记录 vector 清空析构
{
  int fld_e1; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
  {
    sub_4B4950(fld_e1, *(this + 2));  // sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
    j__free((void *)*(this + 1));  // 释放堆块
  }
  *(this + 1) = 0;  // 写字段 this+1 ← 0
  *(this + 2) = 0;  // 写字段 this+2 ← 0
  *(this + 3) = 0;  // 写字段 this+3 ← 0
}



// ------------------------------------------------------------
// 0x4B53F0 sub_4B53F0 —— 24 字节记录区间填充（返回尾址）
//   转发 ·0x4B4FB0 后返回 &pArg1[6*nArg2]（24 字节/条）。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4B53F0(uint32_t *pArg1, int nArg2, void *pArg3)  // sub_4B53F0 —— 24 字节记录区间填充（返回尾址）
{
  sub_4B4FB0(pArg1, nArg2, pArg3);  // sub_4B4FB0 —— 24 字节记录区间定值填充
  return &pArg1[6 * nArg2];
}



// ------------------------------------------------------------
// 0x4B5420 sub_4B5420 —— 152 字节记录 vector 定点插入（_Insert_n 语义）
//   pArg4 为源记录（先 ·0x435020 拷 24 字节头，+16/+20 另存）。按剩余容量四路：
//   ① 容量足且尾部可移——左移让位（·0x437A50 前段 + ·0x4B4930 回搬 + ·0x4B48F0 填值）；
//   ② 容量足但尾段不够——·0x4B53F0 批量填 + 侧移；③ 容量不足——按 (size*1.5, 需量)
//   取大 ·0x4FEF30 重开缓冲，拷前后段并插入；④ 超长经 ·0x434730 抛 length_error。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B5420(int *this, char *pszArg2, unsigned int uArg3, void *pArg4)  // sub_4B5420 —— 152 字节记录 vector 定点插入（_Insert_n 语义）
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
  sub_435020(pArg4);  // sub_435020 —— uint32 向量整体赋值
  v5 = *((uint32_t *)pArg4 + 5);  // 读字段 v5 = pArg4[5]
  v26 = *((uint32_t *)pArg4 + 4);  // 读字段 v26 = pArg4+4（pHostObj）
  v27 = v5;
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  fld_e3 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) / 24;  // this+12〔nSkillRec12(推断)〕
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e2 = (*(this + 2) - fld_e1) / 24;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 178956970 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_434730(this);  // sub_434730 —— vector 超长抛 length_error
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
      fld_e22 = (*(this + 2) - fld_e1) / 24;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = (char *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      fld_e232 = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( (fld_e23 - pszArg2) / 24 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v32 = &fld_e23[-24 * uArg3];  // fld_e23=this+8 nSkillRec8
        *(this + 2) = sub_437A50(v32, (int)fld_e23, fld_e23);  // sub_437A50 —— 条目区间拷贝（24 字节）
        sub_4B4930((int)pszArg2, (int)v32, (int)fld_e232);  // sub_4B4930 —— 24 字节记录拷贝转发（·0x4B3BA0）
        sub_4B48F0((int)pszArg2, (int)&pszArg2[24 * uArg3], (int)v24);  // sub_4B48F0 —— 24 字节记录前向拷贝（逐元素置为新值）
      }
      else
      {
        sub_437A50(pszArg2, (int)fld_e23, &pszArg2[24 * uArg3]);  // sub_437A50 —— 条目区间拷贝（24 字节）
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 24;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
        LOBYTE(v31) = 3;
        sub_4B53F0(fld_e25, fld_e24, v24);  // sub_4B53F0 —— 24 字节记录区间填充（返回尾址）
        fld_e26 = 24 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        v31 = 0;
        sub_4B48F0((int)pszArg2, fld_e26 - 24 * uArg3, (int)v24);  // sub_4B48F0 —— 24 字节记录前向拷贝（逐元素置为新值）
      }
    }
    else
    {
      if ( 178956970 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v11 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else
        v11 = 0;
      if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
        fld_e27 = (*(this + 2) - fld_e1) / 24;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v11 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v11 = uArg3 + sub_4FEF30(this);  // 调 pArg2+4〔宿主对象〕
      v34 = 24 * v11;  // 计算 v34 = 24 * v11
      pMem = (char *)operator new(24 * v11);  // 堆分配
      fld_e12 = (void *)*(this + 1);  // this+4〔宿主对象〕
      Block = pMem;
      LOBYTE(v31) = 1;
      v33 = (uint32_t *)sub_437A50(fld_e12, (int)pszArg2, pMem);  // sub_437A50 —— 条目区间拷贝（24 字节）
      sub_4B4FB0(v33, uArg3, v24);  // sub_4B4FB0 —— 24 字节记录区间定值填充
      sub_437A50(pszArg2, *(this + 2), &v33[6 * uArg3]);  // sub_437A50 —— 条目区间拷贝（24 字节）
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )  // fld_e13=this+4 宿主对象
        fld_e13 = (*(this + 2) - fld_e13) / 24;  // this+8〔nSkillRec8(推断)〕
      v15 = fld_e13 + uArg3;  // 计算 v15 = fld_e13 + uArg3
      fld_e14 = (void *)*(this + 1);  // this+4〔宿主对象〕
      if ( fld_e14 != nullptr )  // fld_e14=this+4 宿主对象
      {
        sub_435820(fld_e14, *(this + 2));  // sub_435820 —— 24 字节条目区间析构
        j__free((void *)*(this + 1));  // 释放堆块
      }
      *(this + 3) = (int)&pMem[v34];  // 写字段 this+3 ← (int)&pMem[v34]
      *(this + 2) = (int)&pMem[24 * v15];  // 写字段 this+2 ← (int)&pMem[24 * v15]
      *(this + 1) = (int)pMem;  // 写字段 this+1 ← (int)pMem
    }
  }
  if ( v25 != nullptr )
    j__free(v25);  // 释放堆块
}


// ------------------------------------------------------------
// 0x4B5720 sub_4B5720 —— 16 字节记录区间拷贝转发（·0x4B5060）
//   纯转发 ·0x4B5060，供 ·0x4B5740 重分配路径全量拷贝。
// ------------------------------------------------------------
unsigned int ***/*stdcall*/ sub_4B5720(int nArg1, int nArg2, unsigned int ***uArg3)  // sub_4B5720 —— 16 字节记录区间拷贝转发（·0x4B5060）
{
  return sub_4B5060(nArg1, nArg2, uArg3);  // sub_4B5060 —— 16 字节记录区间拷贝（返回尾址）
}



// ------------------------------------------------------------
// 0x4B5740 sub_4B5740 —— 16 字节记录 vector 赋值（operator=）
//   自赋值直返；源空则 ·0x4B53A0 清空。源条数 ≤ 现容量：·0x4B3B60 拷入 + ·0x4B4950
//   清尾（本条为 thunk ·0x4B48D0 的调用者）；≤ 已分配容量：·0x4B48D0 拷前段 + ·0x4B5060
//   拷尾段并更新尾指针；否则 ·0x4B3420 重分配后 ·0x4B5720 全量拷。
// ------------------------------------------------------------
int */*thiscall*/ sub_4B5740(int *this, int *pDwArg2)  // sub_4B5740 —— 16 字节记录 vector 赋值（operator=）
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
    sub_4B53A0(this);  // sub_4B53A0 —— 152 字节记录 vector 清空析构
    return this;
  }
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( v4 <= fld_e2 )  // fld_e2=this+8 nSkillRec8
  {
    v8 = sub_4B3B60(v3, pDwArg2[2], fld_e1);  // sub_4B3B60 —— 16 字节元素区间拷贝
    sub_4B4950(v8, *(this + 2));  // sub_4B4950 —— 16 字节记录数组析构（逐元素清 +4 向量后 free）
    v9 = pDwArg2[1];
    if ( v9 != 0 )
      fld_e12 = *(this + 1) + 16 * ((pDwArg2[2] - v9) >> 4);  // this+4〔宿主对象〕
    else
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
    *(this + 2) = fld_e12;  // 写字段 this+2 ← fld_e12
    return this;
  }
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e3 = (*(this + 3) - fld_e1) >> 4;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( v4 > fld_e3 )  // fld_e3=this+12 nSkillRec12
  {
    if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    {
      sub_4B5380(fld_e1, *(this + 2));  // sub_4B5380 —— 16 字节记录数组析构转发（·0x4B4950）
      j__free((void *)*(this + 1));  // 释放堆块
    }
    v14 = pDwArg2[1];
    if ( v14 != 0 )
      v15 = (pDwArg2[2] - v14) >> 4;
    else
      v15 = 0;
    if ( sub_4B3420(this, v15) != 0 )  // sub_4B3420 —— 容器预分配（16 字节/元素）
      *(this + 2) = (int)sub_4B5720(pDwArg2[1], pDwArg2[2], (unsigned int ***)*(this + 1));  // sub_4B5720 —— 16 字节记录区间拷贝转发（·0x4B5060）
    return this;
  }
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e22 = (*(this + 2) - fld_e1) >> 4;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
  v13 = pDwArg2[1] + 16 * fld_e22;  // fld_e22=this+8 nSkillRec8
  sub_4B48D0(pDwArg2[1], v13, *(this + 1));  // sub_4B48D0 —— 转发 thunk（·0x4B3B60）
  *(this + 2) = (int)sub_4B5060(v13, pDwArg2[2], (unsigned int ***)*(this + 2));  // sub_4B5060 —— 16 字节记录区间拷贝（返回尾址）
  return this;
}



// ------------------------------------------------------------
// 0x4B58A0 sub_4B58A0 —— 24 字节记录 vector 定点插入（返回插入位）
//   由 pszArg3 现址与 this+4/+8 算下标 v6（24 字节/元素），经 ·0x4B5420 插入 1 条，
//   *uArg2 回写插入位地址。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4B58A0(int *this, uint32_t *uArg2, char *pszArg3, void *pArg4)  // sub_4B58A0 —— 24 字节记录 vector 定点插入（返回插入位）
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )  // fld_e1=this+4 宿主对象
    v6 = (int)&pszArg3[-fld_e1] / 24;  // fld_e1=this+4 宿主对象
  else
    v6 = 0;
  sub_4B5420(this, pszArg3, 1u, pArg4);  // sub_4B5420 —— 152 字节记录 vector 定点插入（_Insert_n 语义）
  *uArg2 = *(this + 1) + 24 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x4B5910 sub_4B5910 —— 24 字节记录 append（尾插一条）
//   容量够则尾位经 ·0x4B4FB0 填 pArg2（尾指针 +24）；否则走 ·0x4B58A0 扩容插入路径。
// ------------------------------------------------------------
void /*thiscall*/ sub_4B5910(int this, void *pArg2)  // sub_4B5910 —— 24 字节记录 append（尾插一条）
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  uint32_t *fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 24;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) / 24 )  // this+12 物品类型号
  {
    fld_82 = *(uint32_t **)(this + 8);  // this+32〔nHeight(推断)〕
    sub_4B4FB0(fld_82, 1, pArg2);  // sub_4B4FB0 —— 24 字节记录区间定值填充
    *(uint32_t *)(this + 8) = fld_82 + 6;  // 写字段 this+8（nSkillRec8） ← fld_82 + 6
  }
  else
  {
    sub_4B58A0((int *)this, &pArg2, *(char **)(this + 8), pArg2);  // sub_4B58A0 —— 24 字节记录 vector 定点插入（返回插入位）
  }
}



// ============================================================
// §I 0x4B59A0-0x4B5FD0  角色动画包装器
// ============================================================
// ------------------------------------------------------------
// 0x4B59A0 sub_4B59A0 —— 角色动画包装器复位（+204 子动画链、sub_493BD0 复位 / sub_494610 帧数组重置）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B59A0(int this, unsigned int uArg2)  // sub_4B59A0 —— 角色动画包装器复位（+204 子动画链、sub_493BD0 复位 / sub_494610 帧数组重置）
{
  uint32_t *pThis_3C; // ecx

  *(uint8_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)this = &off_6C2B88;  // 写 vftable 指针 off_6C2B88
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *(uint8_t *)(this + 12) = 1;  // 写字段 this+12（nSkillRec12） ← 1
  *(uint8_t *)(this + 14) = 0;  // 写字段 this+14 ← 0
  *(uint8_t *)(this + 13) = 0;  // 写字段 this+13 ← 0
  *(uint32_t *)(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(uint32_t *)(this + 20) = 0;  // 写字段 this+20（nPage） ← 0
  *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
  *(uint32_t *)(this + 44) = 0;  // 写字段 this+44（nExpireMs） ← 0
  *(uint32_t *)(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  *(uint32_t *)(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  pThis_3C = (uint32_t *)(this + 60);  // this+60〔nFadeValue60(推断)〕等 2 字段
  pThis_3C[15] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[16] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[17] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[19] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[20] = 0;  // pThis_3C=this+60 nFadeValue60
  pThis_3C[21] = 0;  // pThis_3C=this+60 nFadeValue60
  sub_430B70(pThis_3C);  // sub_430B70 —— 88B 帧条目复位
  *(uint32_t *)(this + 204) = sub_4A2CF0();  // 写字段 this+204（pSubAnim204） ← sub_4A2CF0()
  *(uint32_t *)(this + 208) = 0;  // 写字段 this+208（nField208） ← 0
  sub_493BD0(this);  // sub_493BD0 —— 动画对象复位
  sub_494610((int *)this, uArg2);  // sub_494610 —— 帧数组重置包装（对 +40 偏移的动画子对象）
  return this;
}



// ------------------------------------------------------------
// 0x4B5A50 sub_4B5A50 —— 帧对象数组析构（·0x42AF90 后 228 字节池回收）
//   首槽 + 4 组双槽（步长 2）+ this[9..12] 逐个 ·0x42AF90 析构、·0x657740(…, 228) 池回收，
//   指针清 0。【推断：宿主动画帧对象句柄数组（228 = 帧对象池尺寸）】
// ------------------------------------------------------------
int /*thiscall*/ sub_4B5A50(void ***this)  // sub_4B5A50 —— 帧对象数组析构（·0x42AF90 后 228 字节池回收）
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
    sub_42AF90(*this);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(v2, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  *this = nullptr;
  pThis_5 = this + 5;
  v12 = 4;
  do
  {
    v4 = (int)*(pThis_5 - 4);
    if ( v4 != 0 )
    {
      sub_42AF90(*(pThis_5 - 4));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v4, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    v5 = *pThis_5;
    v6 = *pThis_5 == nullptr;
    *(pThis_5 - 4) = nullptr;
    if ( !v6 )
    {
      sub_42AF90(v5);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v5, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_5++ = nullptr;
    result = v12 - 1;
    v12 = result;
  }
  while ( result != 0 );  // 循环直到 result != 0
  fld_e9 = (int)*(this + 9);  // this+36〔nStateWord36(推断)〕
  if ( fld_e9 != 0 )  // fld_e9=this+36 nStateWord36
  {
    sub_42AF90(*(this + 9));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e9, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_e10 = *(this + 10);  // 读字段 fld_e10 = this+10
  *(this + 9) = nullptr;  // 写字段 this+9 ← nullptr
  if ( fld_e10 != nullptr )  // fld_e10=this+40 物品状态附属标志
  {
    sub_42AF90(fld_e10);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e10, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_e11 = *(this + 11);  // 读字段 fld_e11 = this+11
  *(this + 10) = nullptr;  // 写字段 this+10 ← nullptr
  if ( fld_e11 != nullptr )  // fld_e11=this+44 剩余时间 ms
  {
    sub_42AF90(fld_e11);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e11, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  fld_e12 = *(this + 12);  // 读字段 fld_e12 = this+12（nSkillRec12）
  *(this + 11) = nullptr;  // 写字段 this+11 ← nullptr
  if ( fld_e12 != nullptr )  // fld_e12=this+12 nSkillRec12
  {
    sub_42AF90(fld_e12);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    result = sub_657740(fld_e12, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 12) = nullptr;  // 写字段 this+12（nSkillRec12） ← nullptr
  return result;
}



// ------------------------------------------------------------
// 0x4B5B80 sub_4B5B80 —— 全局动画/特效常量表静态初始化
//   先补两组 uint32 向量（2,3 与 0,1）；再对 unk_9A0330/unk_9A035C、unk_9A0388..byte_9A03E0、
//   unk_9A040C..byte_9A0464 三批表逐条 ·0x4B5910（24 字节记录 append）建表（含周期 300/350/500）；
//   末 ·0x5EEA20/·0x5E50B0/·0x4C5240/·0x5DB3E0 四族常量表装载。
// ------------------------------------------------------------
void sub_4B5B80()  // sub_4B5B80 —— 全局动画/特效常量表静态初始化
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
    *(uint32_t *)dword_9A0318 = 2;  // *dword_9A0318 = 2
    dword_9A03182 = v0 + 4;
    dword_9A0318 = dword_9A03182;
  }
  else
  {
    sub_430C80(dword_9A0318, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
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
    sub_430C80(dword_9A03182, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
  }
  v2 = (char *)dword_9A0328;
  v16[0] = 0;
  if ( dword_9A0324 != 0 && ((int)dword_9A0328 - dword_9A0324) >> 2 < (unsigned int)((dword_9A032C - dword_9A0324) >> 2) )
  {
    *(uint32_t *)dword_9A0328 = 0;  // *dword_9A0328 = 0
    dword_9A03282 = v2 + 4;
    dword_9A0328 = dword_9A03282;
  }
  else
  {
    sub_430C80(dword_9A0328, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
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
    sub_430C80(dword_9A03282, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
  }
  v16[3] = 0;
  Block = nullptr;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 300;
  v16[0] = 5;
  sub_430C80(nullptr, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
  sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
  sub_4C0090(&unk_9A0330);  // unk_9A0330 —— 列表登记与状态判定
  if ( Block != nullptr )
    j__free(Block);  // 释放堆块
  Block = nullptr;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 300;
  v16[0] = 6;
  sub_430C80(nullptr, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
  sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
  sub_4C0090(&unk_9A035C);
  v4 = 0;
  v5 = (char *)&unk_9A0388;
  do
  {
    if ( Block != nullptr )
      j__free(Block);  // 释放堆块
    v16[0] = 3 - (v4 != 0);
    Block = nullptr;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    sub_430C80(nullptr, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
    v13 = 500;
    sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
    sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
    sub_4C0090(v5);
    v5 += 44;
    ++v4;  // 计数自增 v4
  }
  while ( (int)v5 < (int)byte_9A03E0 );
  if ( Block != nullptr )
    j__free(Block);  // 释放堆块
  Block = nullptr;
  v10 = 0;
  v11 = 0;
  v12 = 0;
  v13 = 300;
  v16[0] = 7;
  sub_430C80(nullptr, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
  v13 = 500;
  sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
  v6 = 1;
  v14 = 7;
  v15 = 1;
  v7 = (char *)&unk_9A040C;
  do
  {
    if ( Block != nullptr )
      j__free(Block);  // 释放堆块
    Block = nullptr;
    v10 = 0;
    v16[0] = (v6 != 1) + 2;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    sub_430C80(nullptr, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
    v13 = 350;
    sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
    if ( Block != nullptr )
      j__free(Block);  // 释放堆块
    Block = nullptr;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    sub_430C80(nullptr, 1, (int)&v15);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
    v13 = 350;
    sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
    if ( Block != nullptr )
      j__free(Block);  // 释放堆块
    Block = nullptr;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    v16[0] = 3 - (v6 != 1);
    sub_430C80(nullptr, 1, (int)v16);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
    v13 = 350;
    sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
    if ( Block != nullptr )
      j__free(Block);  // 释放堆块
    Block = nullptr;
    v10 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 300;
    sub_430C80(nullptr, 1, (int)&v14);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
    v13 = 500;
    sub_4B5910(v8);  // sub_4B5910 —— 24 字节记录 append（尾插一条）
    v7 += 44;
    ++v6;  // 计数自增 v6
  }
  while ( (int)v7 < (int)byte_9A0464 );
  sub_5EEA20();
  sub_5E50B0();
  sub_4C5240();
  sub_5DB3E0();  // sub_5DB3E0 —— 全局偏位/相位常量表装载（无 this）：·sub_47E720/·sub_47E9D0 建 5 组表句柄
  if ( Block != nullptr )
    j__free(Block);  // 释放堆块
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
char /*thiscall*/ sub_4B5FD0(uint32_t *this, int ArgList)  // sub_4B5FD0 —— ★.equ 部件记录解析装载
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
  v3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84C0 + 4))(dword_8F84C0, ArgList);  // 虚调用 vt+4（dword_8F84C0）对象赋值/迁移
  v4 = (uint32_t *)v3;
  v99 = (uint32_t *)v3;
  if ( v3 == 0 )
  {
    LOBYTE(v5) = off_77F3FC("CHARACTER CREATE FAIL! FILENAME[%s]", v2);  // off_77F3FC —— 日志打印（printf 风格）
    return v5;
  }
  v6 = (int)pThis;
  sub_4014D0((std::_String_base *)(pThis + 90), v3 + 1640, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  pThis[1787] = *v4;
  *(uint32_t *)(v6 + 316) = v4[36];  // 写字段 v6+316 ← v4[36]
  *(uint32_t *)(v6 + 320) = v4[37];  // 写字段 v6+320 ← v4[37]
  v6 += 328;
  sub_4ED3F0(v6, (int)(v4 + 181));  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
  ArgList = 16;
  sub_431230(v6, &ArgList);  // sub_431230 —— uint32 vector push_back
  if ( sub_40BF00((std::_String_base *)(v4 + 206), 0, v4[211], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 0;
    if ( ArgList != 0 )
    {
      if ( v4[212] < 0x10u )
        LOBYTE(v7) = (uint8_t)v4 + 60;
      else
        v7 = v4[207];
      if ( v4[416] < 0x10u )
        v8 = sub_431920((uint8_t)v4 + 108, v7, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v8 = sub_431920(v4[411], v7, 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    else
    {
      v8 = 0;
    }
    v101 = -1;
    pThis[1540] = v8;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 213), 0, v4[218], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 1;
    if ( ArgList != 0 )
    {
      if ( v4[219] < 0x10u )
        LOBYTE(v9) = (uint8_t)v4 + 88;
      else
        v9 = v4[214];
      if ( v4[416] < 0x10u )
        v10 = sub_431920((uint8_t)v4 + 108, v9, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v10 = sub_431920(v4[411], v9, 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    else
    {
      v10 = 0;
    }
    v101 = -1;
    pThis[1541] = v10;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 220), 0, v4[225], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 2;
    if ( ArgList != 0 )
    {
      if ( v4[226] < 0x10u )
        LOBYTE(v11) = (uint8_t)v4 + 116;
      else
        v11 = v4[221];
      if ( v4[416] < 0x10u )
        v12 = sub_431920((uint8_t)v4 + 108, v11, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v12 = sub_431920(v4[411], v11, 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    else
    {
      v12 = 0;
    }
    v101 = -1;
    pThis[1542] = v12;
  }
  v13 = pThis + 1543;  // 计算 v13 = pThis + 1543
  v14 = v4 + 228;  // 计算 v14 = v4 + 228
  for ( ArgList = 2; ArgList != 0; --ArgList )  // 遍历计次循环（ArgList != 0）
  {
    if ( sub_40BF00((std::_String_base *)(v14 - 1), 0, v14[4], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      v98 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
      v101 = 3;
      if ( v98 != 0 )
      {
        if ( (unsigned int)v14[5] < 0x10 )
          LOBYTE(v15) = (uint8_t)v14;
        else
          v15 = *v14;
        if ( v4[416] < 0x10u )
          v16 = sub_431920((uint8_t)v4 + 108, v15, 1);  // sub_431920 —— 动画件构造（文件名版）
        else
          v16 = sub_431920(v4[411], v15, 1);  // sub_431920 —— 动画件构造（文件名版）
      }
      else
      {
        v16 = 0;
      }
      v101 = -1;
      *v13 = v16;
    }
    ++v13;  // 计数自增 v13
    v14 += 7;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 241), 0, v4[246], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 4;
    if ( ArgList != 0 )
    {
      if ( v4[247] < 0x10u )
        LOBYTE(v17) = (uint8_t)v4 - 56;
      else
        v17 = v4[242];
      if ( v4[416] < 0x10u )
        v18 = sub_431920((uint8_t)v4 + 108, v17, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v18 = sub_431920(v4[411], v17, 1);  // sub_431920 —— 动画件构造（文件名版）
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
  if ( sub_40BF00((std::_String_base *)(v4 + 248), 0, v4[253], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 5;
    if ( ArgList != 0 )
    {
      if ( v4[254] < 0x10u )
        LOBYTE(v20) = (uint8_t)v4 - 28;
      else
        v20 = v4[249];
      if ( v4[416] < 0x10u )
        v21 = sub_431920((uint8_t)v4 + 108, v20, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v21 = sub_431920(v4[411], v20, 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    else
    {
      v21 = 0;
    }
    v101 = -1;
    pThis2[1546] = v21;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 255), 0, v4[260], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 6;
    if ( ArgList != 0 )
    {
      if ( v4[261] < 0x10u )
        LOBYTE(v22) = (uint8_t)v4;
      else
        v22 = v4[256];
      if ( v4[416] < 0x10u )
        v23 = sub_431920((uint8_t)v4 + 108, v22, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v23 = sub_431920(v4[411], v22, 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    else
    {
      v23 = 0;
    }
    v101 = -1;
    pThis2[1547] = v23;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 262), 0, v4[267], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 7;
    if ( ArgList != 0 )
    {
      if ( v4[268] < 0x10u )
        LOBYTE(v24) = (uint8_t)v4 + 28;
      else
        v24 = v4[263];
      if ( v4[416] < 0x10u )
        v25 = sub_431920((uint8_t)v4 + 108, v24, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v25 = sub_431920(v4[411], v24, 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    else
    {
      v25 = 0;
    }
    v101 = -1;
    pThis2[1548] = v25;
  }
  if ( sub_40BF00((std::_String_base *)(v4 + 269), 0, v4[274], szPassword, 0) != 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 8;
    if ( ArgList != 0 )
    {
      if ( v4[275] < 0x10u )
        LOBYTE(v26) = (uint8_t)v4 + 56;
      else
        v26 = v4[270];
      if ( v4[416] < 0x10u )
        v27 = sub_431920((uint8_t)v4 + 108, v26, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v27 = sub_431920(v4[411], v26, 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    else
    {
      v27 = 0;
    }
    v101 = -1;
    pThis2[1803] = v27;
  }
  ArgList = (int)(pThis2 + 1808);
  v28 = v4 + 281;  // 计算 v28 = v4 + 281
  v98 = 4;
  do
  {
    if ( *v28 != 0 )
    {
      v97 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
      v101 = 9;
      if ( v97 != 0 )
      {
        if ( v28[1] < 0x10u )
          LOBYTE(v29) = (uint8_t)v28 - 16;
        else
          v29 = *(v28 - 4);
        if ( v99[416] < 0x10u )
          v30 = sub_431920((uint8_t)v99 + 108, v29, 1);  // sub_431920 —— 动画件构造（文件名版）
        else
          v30 = sub_431920(v99[411], v29, 1);  // sub_431920 —— 动画件构造（文件名版）
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
      v97 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
      v101 = 10;
      if ( v97 != 0 )
      {
        if ( v28[29] < 0x10u )
          LOBYTE(v31) = (uint8_t)v28 + 96;
        else
          v31 = v28[24];
        if ( v99[416] < 0x10u )
          v32 = sub_431920((uint8_t)v99 + 108, v31, 1);  // sub_431920 —— 动画件构造（文件名版）
        else
          v32 = sub_431920(v99[411], v31, 1);  // sub_431920 —— 动画件构造（文件名版）
      }
      else
      {
        v32 = 0;
      }
      v101 = -1;
      *(uint32_t *)ArgList = v32;  // *ArgList = v32
    }
    v28 += 7;
    v33 = v98 == 1;
    ArgList += 4;  // ArgList 前进 4
    --v98;  // 计数自减 v98
  }
  while ( !v33 );
  if ( v99[337] != 0 )
  {
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v34 = v99;
    v101 = 11;
    if ( ArgList != 0 )
    {
      if ( v99[338] < 0x10u )
        LOBYTE(v35) = (uint8_t)v99 + 52;
      else
        v35 = v99[333];
      if ( v99[416] < 0x10u )
        v36 = sub_431920((uint8_t)v99 + 108, v35, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v36 = sub_431920(v99[411], v35, 1);  // sub_431920 —— 动画件构造（文件名版）
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
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 12;
    if ( ArgList != 0 )
    {
      if ( v34[345] < 0x10u )
        LOBYTE(v37) = (uint8_t)v34 + 80;
      else
        v37 = v34[340];
      if ( v34[416] < 0x10u )
        v38 = sub_431920((uint8_t)v34 + 108, v37, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v38 = sub_431920(v34[411], v37, 1);  // sub_431920 —— 动画件构造（文件名版）
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
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 13;
    if ( ArgList != 0 )
    {
      if ( v34[352] < 0x10u )
        LOBYTE(v39) = (uint8_t)v34 + 108;
      else
        v39 = v34[347];
      if ( v34[416] < 0x10u )
        v40 = sub_431920((uint8_t)v34 + 108, v39, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v40 = sub_431920(v34[411], v39, 1);  // sub_431920 —— 动画件构造（文件名版）
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
    ArgList = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v101 = 14;
    if ( ArgList != 0 )
    {
      if ( v34[359] < 0x10u )
        LOBYTE(v41) = (uint8_t)v34 - 120;
      else
        v41 = v34[354];
      if ( v34[416] < 0x10u )
        v42 = sub_431920((uint8_t)v34 + 108, v41, 1);  // sub_431920 —— 动画件构造（文件名版）
      else
        v42 = sub_431920(v34[411], v41, 1);  // sub_431920 —— 动画件构造（文件名版）
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
    v45 = pThis + 1549;  // 计算 v45 = pThis + 1549
    while ( 1 )
    {
      if ( strcmp((const char *)sub_41ACF0(ArgList), szPassword) == 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
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
        v97 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v101 = 15;
        if ( v97 != 0 )
        {
          if ( v99[416] < 0x10u )
            LOBYTE(v46) = (uint8_t)v99 + 108;
          else
            v46 = v99[411];
          v47 = sub_41ACF0(ArgList);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
          v48 = sub_431920(v46, v47, 1);  // sub_431920 —— 动画件构造（文件名版）
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
          sub_42AC90((void *)v45[2], 1, (int)&v98);  // sub_42AC90 —— 调 sub_42AC90
          goto LABEL_182;
        }
        v51 = (int *)v45[2];
        *v51 = v48;
        v45[2] = v51 + 1;
      }
LABEL_182:
      v55 = v99;
      v56 = v99[362];
      ArgList += 4;  // ArgList 前进 4
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
    v57 = pThis + 1553;  // 计算 v57 = pThis + 1553
    while ( 1 )
    {
      if ( strcmp((const char *)sub_41ACF0(ArgList), szPassword) == 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
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
        v97 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v101 = 16;
        if ( v97 != 0 )
        {
          if ( v99[416] < 0x10u )
            LOBYTE(v58) = (uint8_t)v99 + 108;
          else
            v58 = v99[411];
          v59 = sub_41ACF0(ArgList);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
          v60 = sub_431920(v58, v59, 1);  // sub_431920 —— 动画件构造（文件名版）
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
          sub_42AC90((void *)v57[2], 1, (int)&v98);  // sub_42AC90 —— 调 sub_42AC90
          goto LABEL_208;
        }
        v63 = (int *)v57[2];
        *v63 = v60;
        v57[2] = v63 + 1;
      }
LABEL_208:
      v67 = v99;
      v68 = v99[366];
      ArgList += 4;  // ArgList 前进 4
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
      v70 = v99 + 376;  // 计算 v70 = v99 + 376
    else
      v70 = (uint32_t *)v99[376];
    if ( v99[416] < 0x10u )
      v71 = v99 + 411;  // 计算 v71 = v99 + 411
    else
      v71 = (uint32_t *)v99[411];
    v72 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E0 + 12))(dword_8F84E0, "%s%s", v71, v70);  // 虚调用 vt+12（dword_8F84E0 虚表槽）
    sub_4B2970(pThis + 1816, v72);  // sub_4B2970 —— 部件记录拷贝（同 ·0x4B2820）
  }
  else
  {
    v69 = v99;
  }
  if ( v69[373] != 0 )
  {
    if ( v69[374] < 0x10u )
      v73 = v69 + 369;  // 计算 v73 = v69 + 369
    else
      v73 = (uint32_t *)v69[369];
    if ( v69[416] < 0x10u )
      v74 = v69 + 411;  // 计算 v74 = v69 + 411
    else
      v74 = (uint32_t *)v69[411];
    v75 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E0 + 12))(dword_8F84E0, "%s%s", v74, v73);  // 虚调用 vt+12（dword_8F84E0 虚表槽）
    sub_4B2970(pThis + 1579, v75);  // sub_4B2970 —— 部件记录拷贝（同 ·0x4B2820）
  }
  v33 = v69[383] == v69[384];
  ArgList = v69[383];
  if ( !v33 )
  {
    do
    {
      if ( strcmp((const char *)sub_41ACF0(ArgList), szPassword) == 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      {
        v96 = 15;
        v95 = 0;
        LOBYTE(Block) = 0;
        v101 = 17;
        sub_4A3450(v93);  // sub_4A3450 —— attackinfo 默认值（sub_4A3450 @0x4A3450，由 sub_4A3520 构造函数先行调用）：
        v101 = 18;
        sub_4B52F0(v93);  // sub_4B52F0 —— 152 字节记录 append（尾插一条）
        v101 = -1;
        if ( v96 >= 0x10 )
          j__free(Block);  // 释放堆块
        v96 = 15;
        v95 = 0;
        LOBYTE(Block) = 0;
      }
      else
      {
        if ( v69[416] < 0x10u )
          v76 = v69 + 411;  // 计算 v76 = v69 + 411
        else
          v76 = (uint32_t *)v69[411];
        v77 = *(uint32_t *)dword_8F84E0;
        v78 = sub_41ACF0(ArgList);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        v79 = (*(int (**)(int, const char *, ...))(v77 + 12))(dword_8F84E0, "%s%s", v76, v78);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
        sub_4B52F0(v79);  // sub_4B52F0 —— 152 字节记录 append（尾插一条）
      }
      v80 = v69[384];
      ArgList += 4;  // ArgList 前进 4
    }
    while ( ArgList != v80 );  // 循环直到 ArgList != v80
  }
  v33 = v69[387] == v69[388];
  ArgList = v69[387];
  if ( !v33 )
  {
    do
    {
      if ( strcmp((const char *)sub_41ACF0(ArgList), szPassword) == 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      {
        v96 = 15;
        v95 = 0;
        LOBYTE(Block) = 0;
        v101 = 19;
        sub_4A3450(v93);  // sub_4A3450 —— attackinfo 默认值（sub_4A3450 @0x4A3450，由 sub_4A3520 构造函数先行调用）：
        v101 = 20;
        sub_4B52F0(v93);  // sub_4B52F0 —— 152 字节记录 append（尾插一条）
        v101 = -1;
        if ( v96 >= 0x10 )
          j__free(Block);  // 释放堆块
        v96 = 15;
        v95 = 0;
        LOBYTE(Block) = 0;
      }
      else
      {
        if ( v69[416] < 0x10u )
          v81 = v69 + 411;  // 计算 v81 = v69 + 411
        else
          v81 = (uint32_t *)v69[411];
        v82 = *(uint32_t *)dword_8F84E0;
        v83 = sub_41ACF0(ArgList);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        v84 = (*(int (**)(int, const char *, ...))(v82 + 12))(dword_8F84E0, "%s%s", v81, v83);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
        sub_4B52F0(v84);  // sub_4B52F0 —— 152 字节记录 append（尾插一条）
      }
      v85 = v69[388];
      ArgList += 4;  // ArgList 前进 4
    }
    while ( ArgList != v85 );  // 循环直到 ArgList != v85
  }
  pThis3 = pThis;
  sub_4B5740(v69 + 390);  // sub_4B5740 —— 16 字节记录 vector 赋值（operator=）
  sub_4ED3F0((int)(pThis3 + 1907), (int)(v69 + 394));  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
  sub_4ED3F0((int)(pThis3 + 1911), (int)(v69 + 398));  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
  sub_4ED3F0((int)(pThis3 + 1915), (int)(v69 + 402));  // sub_4ED3F0 —— int 向量拷贝赋值（全容量路径）
  sub_480210(v69 + 406);  // sub_480210 —— 4 字节元素容器区间赋值（与 ·0x4800C0 同构）
  sub_41A590((unsigned int)(pThis3 + 408), v87, v69[205]);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
  LOBYTE(v5) = byte_77F280;  // 调试机标志(DebugConfig.txt 校验)
  if ( byte_77F280 != 0 )
  {
    v92 = v69[205];
    *((uint8_t *)v69 + 230) = 100;  // 写字段 v69[230]（宽1字节）
    sub_41A590((unsigned int)(pThis3 + 408), v88, v92);  // sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*pThis3 + 1048))(pThis3, v69 + 38);  // 虚调用 vt+1048（pThis3 虚表槽）
    LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pThis3 + 1056))(pThis3, 1);  // 虚调用 vt+1056（pThis3 虚表槽）
  }
  pThis3[162] |= 2u;
  *((uint8_t *)pThis3 + 6668) = 1;  // 写字段 pThis3[6668]（宽1字节）
  *((uint8_t *)pThis3 + 6681) = 1;  // 写字段 pThis3[6681]（宽1字节）
  *((uint8_t *)pThis3 + 8100) = 0;  // 写字段 pThis3[8100]（宽1字节）
  for ( i = 0; ; ++i )
  {
    v90 = pThis3[83];
    if ( v90 == 0 )
      break;
    v5 = (pThis3[84] - v90) >> 2;
    if ( i >= v5 )
      break;
    LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis3 + 464))(pThis3, *(uint32_t *)(v90 + 4 * i));  // 虚调用 vt+464（pThis3 虚表槽）
  }
  return v5;
}


// ============================================================
// §K 0x4B7110-0x4B89D0  升级/结算演出（LevelNormalizeLibra、PVP_KO）
// ============================================================
// ------------------------------------------------------------
// 0x4B7110 sub_4B7110 —— 角色演出资源释放（宿主 +7428..+8172 大段槽清理）
//   18 槽（+7516 起）+ 单槽 +7592/+7692/+7696/+7800/+7968/+7976/+7980/+7984/+8000/+8068
//   经各自 vt0 位 4 释放（+7692/+7696 另有 ·0x45F1E0 特例）；+7768 三槽、+7784 二槽与
//   +8172 区 2×5 组经 ·0x42AF90 + ·0x657740(228) 回收；末释放 +7428 并清空各槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_4B7110(int this)  // sub_4B7110 —— 角色演出资源释放（宿主 +7428..+8172 大段槽清理）
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
  for ( i = 18; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    pObj = *pThis_1D5C;
    if ( *pThis_1D5C != *(pThis_1D5C - 262) )
    {
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);  // 虚调用 vt+4（pObj）对象赋值/迁移
      *pThis_1D5C = 0;
    }
    ++pThis_1D5C;  // 计数自增 pThis_1D5C
  }
  fld_1DA4 = *(uint32_t *)(this + 7588);  // 读字段 fld_1DA4 = this+7588（uForm7588）
  if ( fld_1DA4 != 0 )  // fld_1DA4=this+7588 uForm7588
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1DA4 + 4))(fld_1DA4, 1);  // 虚调用 vt+4（fld_1DA4）对象赋值/迁移
  pThis_1DA8 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7592);  // this+7592〔nAtkSegSlot7592〕
  *(uint32_t *)(this + 7588) = 0;  // 写字段 this+7588（uForm7588） ← 0
  if ( pThis_1DA8 != nullptr )  // pThis_1DA8=this+7592 nAtkSegSlot7592
    (**pThis_1DA8)(pThis_1DA8, 1);  // 调 pThis_1DA8 的虚函数（vt+0）
  fld_1E0C = *(uint32_t *)(this + 7692);  // 读字段 fld_1E0C = this+7692
  *(uint32_t *)(this + 7592) = 0;  // 写字段 this+7592（nAtkSegSlot7592） ← 0
  if ( fld_1E0C != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_1E0C + 80))(fld_1E0C) != 0 )  // 虚调用 vt+80（fld_1E0C）读 4 字节
  {
    fld_1E0C2 = *(uint32_t *)(this + 7692);  // 读字段 fld_1E0C2 = this+7692
    (*(void (**)(void))(*(uint32_t *)fld_1E0C2 + 80))();  // 虚调用 vt+80（fld_1E0C2）读 4 字节
    sub_45F1E0(fld_1E0C2);  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
  }
  pThis_1E0C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7692);
  if ( pThis_1E0C != nullptr )
    (**pThis_1E0C)(pThis_1E0C, 1);  // 调 pThis_1E0C 的虚函数（vt+0）
  fld_1E10 = *(uint32_t *)(this + 7696);  // 读字段 fld_1E10 = this+7696
  *(uint32_t *)(this + 7692) = 0;  // 写字段 this+7692 ← 0
  if ( fld_1E10 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_1E10 + 80))(fld_1E10) != 0 )  // 虚调用 vt+80（fld_1E10）读 4 字节
  {
    fld_1E102 = *(uint32_t *)(this + 7696);  // 读字段 fld_1E102 = this+7696
    (*(void (**)(void))(*(uint32_t *)fld_1E102 + 80))();  // 虚调用 vt+80（fld_1E102）读 4 字节
    sub_45F1E0(fld_1E102);  // sub_45F1E0 —— 对象注销/退场（递归，含 ELVEN_GATE 检查）
  }
  pThis_1E10 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7696);  // this+7696 getter
  if ( pThis_1E10 != nullptr )
    (**pThis_1E10)(pThis_1E10, 1);  // 调 pThis_1E10 的虚函数（vt+0）
  *(uint32_t *)(this + 7696) = 0;  // 写字段 this+7696 ← 0
  pThis_1E58 = (void ***)(this + 7768);  // this+7768〔pObj7768〕
  for ( j = 3; j != 0; --j )  // 遍历计次循环（j != 0）
  {
    v12 = *pThis_1E58;  // pThis_1E58=this+7768 pObj7768
    if ( *pThis_1E58 != nullptr )  // pThis_1E58=this+7768 pObj7768
    {
      sub_42AF90(*pThis_1E58);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v12, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_1E58++ = nullptr;  // pThis_1E58=this+7768 pObj7768
  }
  pThis_1E68 = (void ***)(this + 7784);
  for ( k = 2; k != 0; --k )  // 遍历计次循环（k != 0）
  {
    v14 = *pThis_1E68;
    if ( *pThis_1E68 != nullptr )
    {
      sub_42AF90(*pThis_1E68);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v14, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *pThis_1E68++ = nullptr;
  }
  fld_1E74 = *(uint32_t *)(this + 7796);  // 读字段 fld_1E74 = this+7796
  if ( fld_1E74 != 0 )
  {
    sub_42AF90(*(void ***)(this + 7796));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_1E74, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_1E78 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7800);
  *(uint32_t *)(this + 7796) = 0;  // 写字段 this+7796 ← 0
  if ( pThis_1E78 != nullptr )
    (**pThis_1E78)(pThis_1E78, 1);  // 调 pThis_1E78 的虚函数（vt+0）
  pThis_1F20 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7968);
  *(uint32_t *)(this + 7800) = 0;  // 写字段 this+7800 ← 0
  if ( pThis_1F20 != nullptr )
    (**pThis_1F20)(pThis_1F20, 1);  // 调 pThis_1F20 的虚函数（vt+0）
  fld_1F24 = *(void ***)(this + 7972);
  *(uint32_t *)(this + 7968) = 0;  // 写字段 this+7968 ← 0
  if ( fld_1F24 != nullptr )
  {
    sub_42AF90(fld_1F24);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_1F24, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_1F28 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7976);
  *(uint32_t *)(this + 7972) = 0;  // 写字段 this+7972 ← 0
  if ( pThis_1F28 != nullptr )
    (**pThis_1F28)(pThis_1F28, 1);  // 调 pThis_1F28 的虚函数（vt+0）
  pThis_1F2C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7980);
  *(uint32_t *)(this + 7976) = 0;  // 写字段 this+7976 ← 0
  if ( pThis_1F2C != nullptr )
    (**pThis_1F2C)(pThis_1F2C, 1);  // 调 pThis_1F2C 的虚函数（vt+0）
  pThis_1F30 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 7984);
  *(uint32_t *)(this + 7980) = 0;  // 写字段 this+7980 ← 0
  if ( pThis_1F30 != nullptr )
    (**pThis_1F30)(pThis_1F30, 1);  // 调 pThis_1F30 的虚函数（vt+0）
  pThis_1F40 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8000);
  *(uint32_t *)(this + 7984) = 0;  // 写字段 this+7984 ← 0
  if ( pThis_1F40 != nullptr )
    (**pThis_1F40)(pThis_1F40, 1);  // 调 pThis_1F40 的虚函数（vt+0）
  pThis_1F84 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8068);
  *(uint32_t *)(this + 8000) = 0;  // 写字段 this+8000 ← 0
  if ( pThis_1F84 != nullptr )
    (**pThis_1F84)(pThis_1F84, 1);  // 调 pThis_1F84 的虚函数（vt+0）
  *(uint32_t *)(this + 8068) = 0;  // 写字段 this+8068 ← 0
  pThis_1F90 = (void (/*thiscall*/ ****)(uint32_t, int))(this + 8080);
  for ( m = 2; m != 0; --m )  // 遍历计次循环（m != 0）
  {
    v26 = *(pThis_1F90 - 2);
    if ( v26 != nullptr )
      (**v26)(v26, 1);  // 调 v26 的虚函数（vt+0）
    v27 = *pThis_1F90;
    v28 = *pThis_1F90 == nullptr;
    *(pThis_1F90 - 2) = nullptr;
    if ( !v28 )
      (**v27)(v27, 1);  // 调 v27 的虚函数（vt+0）
    *pThis_1F90++ = nullptr;
  }
  pThis_1FEC = (void ***)(this + 8172);
  for ( n = 5; n != 0; --n )  // 遍历计次循环（n != 0）
  {
    v39 = 2;
    do
    {
      v30 = (int)*(pThis_1FEC - 10);
      if ( v30 != 0 )
      {
        sub_42AF90(*(pThis_1FEC - 10));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
        sub_657740(v30, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
      }
      v31 = *pThis_1FEC;
      v28 = *pThis_1FEC == nullptr;
      *(pThis_1FEC - 10) = nullptr;
      if ( !v28 )
      {
        sub_42AF90(v31);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
        sub_657740(v31, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
      }
      *pThis_1FEC++ = nullptr;
      result = v39 - 1;
      v39 = result;
    }
    while ( result != 0 );  // 循环直到 result != 0
  }
  fld_1D04 = *(uint32_t *)(this + 7428);  // 读字段 fld_1D04 = this+7428
  if ( fld_1D04 != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1D04 + 4))(fld_1D04, 1);  // 虚调用 vt+4（fld_1D04）对象赋值/迁移
  *(uint32_t *)(this + 7428) = 0;  // 写字段 this+7428 ← 0
  return result;
}


// ------------------------------------------------------------
// 0x4B7430 sub_4B7430 —— 升级演出装配（LevelNormalizeLibra.ani + LevelNormalize.ptl；LEVELING_OFF/FLASH；PVP_KO）
// ------------------------------------------------------------
void /*usercall*/ sub_4B7430(int *pDwArg1@<ecx>, double fArg2@<st0>)  // sub_4B7430 —— 升级演出装配（LevelNormalizeLibra.ani + LevelNormalize.ptl；LEVELING_OFF/FLASH；PVP_KO）
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  sub_58FC30();  // 【IRDActiveObject__vmt14C】
  v3 = pDwArg1[2001];
  if ( v3 != 0 )
  {
    v4 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    if ( v4 == 4 || v4 == 6 )
    {
      if ( v3 == 1 )
      {
        v5 = (void (/*thiscall*/ ***)(uint32_t, int))pDwArg1[2000];
        if ( v5 != nullptr )
          (**v5)(v5, pDwArg1[2001]);  // 调 v5 的虚函数（vt+0）
        v6 = 0;
        pDwArg1[2000] = 0;
        v126 = 0;
        if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
          v6 = sub_431860((char)"Common/Etc/Animation/LevelNormalizeLibra.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
        v7 = (uint32_t *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
        pMem2 = v7;
        v126 = 1;
        if ( v7 != nullptr )
        {
          sub_44E0D0(v6, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
          *v7 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
          v8 = v7;
        }
        else
        {
          v8 = nullptr;
        }
        a1[1999] = (int)v8;
        v9 = *v8;
        v126 = -1;
        (*(void (/*thiscall*/ **)(int *))(v9 + 72))(v8);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4…
        sub_45FE80(a1[29], (int)v7, 2, 0, a1[1999], (int)a1, 0);  // sub_45FE80 —— 对象注册
        v10 = *a1;
        v11 = *(uint32_t *)a1[1999];
        v117 = a1[1999];
        v12 = (*(int (/*thiscall*/ **)(int *))(v10 + 192))(a1);  // 虚函数调用 槽+192
        v13 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);  // 虚调用 vt+128（a1）目标坐标y上界
        v14 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 124))(a1, v13 + v12);  // 虚调用 vt+124（a1）目标坐标y下界
        v15 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 120))(a1, v14);  // 虚调用 vt+120（a1）转发(对象+缓冲)
        (*(void (/*thiscall*/ **)(int, int))(v11 + 112))(v117, v15);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
        (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)a1[1999] + 60))(a1[1999], a1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行…
        sub_4A06D0(2);  // sub_4A06D0 —— 绑定目标对象并记录相对偏移
        v16 = operator new(0x12Cu);  // 堆分配
        v122 = v16;
        v126 = 2;
        if ( v16 != nullptr )
          v17 = sub_428F30(v16, (int)"Common/Etc/Particle/LevelNormalize.ptl", (int)a1);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
        else
          v17 = nullptr;
        a1[2000] = (int)v17;
        v18 = *v17;
        v126 = -1;
        (*(void (/*thiscall*/ **)(int *, int *))(v18 + 112))(v17, a1);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[2000] + 64))(a1[2000], 1);  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
        a1[2001] = 2;
      }
      else
      {
        v19 = a1[1999];
        if ( v19 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 200))(v19) != 0 )  // 虚调用 vt+200（v19）取值比较
        {
          if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[1999] + 200))(a1[1999]) + 148) == 4  // 调虚槽 +200：取动画对象
            && a1[2001] == 2 )
          {
            a1[2001] = 3;
            sub_432EA0("LEVELING_OFF", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
          }
          else if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[1999] + 200))(a1[1999]) + 148) == 20  // 调虚槽 +200：取动画对象
                 && a1[2001] == 3 )
          {
            a1[2001] = 4;
            sub_432EA0("LEVELING_FLASH", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
          }
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1[1999] + 200))(a1[1999]) + 170) != 0 )  // 调虚槽 +200：取动画对象
          {
            v20 = a1[2000];
            if ( v20 != 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v20 + 12))(v20, 0);  // 虚调用 vt+12（v20 虚表槽）
              v111 = sub_4633B0(a1);  // sub_4633B0 —— std::string 取数据指针（SSO 判定）
              v21 = (const char *)sub_422E70(850);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
              sprintf(Buffer, v21, v111);  // 调 格式化到缓冲
              sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -6567706, 0, -1);  // sub_43BEE0 —— 【播报上屏】
              a1[2001] = 0;
            }
          }
        }
      }
    }
  }
  (*(void (/*thiscall*/ **)(int *))(*a1 + 1308))(a1);  // 虚调用 vt+1308（a1 虚表槽）
  if ( *((uint8_t *)a1 + 7764) != 0 && *(uint8_t *)(a1[1942] + 170) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 1232))(a1, 0);  // 虚调用 vt+1232（a1 虚表槽）
  if ( *((uint8_t *)a1 + 7780) != 0 && *(uint8_t *)(a1[1946] + 170) != 0 )
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*a1 + 1240))(a1, 0, 0);  // 虚调用 vt+1240（a1 虚表槽）
  if ( *((uint8_t *)a1 + 7792) != 0 )
  {
    v22 = a1[1949];
    if ( *(uint32_t *)(v22 + 212) != 0 )
      v23 = sub_4910A0();  // sub_4910A0 —— 沿 +212 同步源链上溯，返回链尾对象的累计播放时刻（+32）
    else
      v23 = *(uint32_t *)(v22 + 32);  // 读字段 v23 = v22+32（nHeight）
    v24 = 0;
    if ( v23 >= 540 )
    {
      v34 = *a1;
      if ( v23 >= 1080 )
      {
        (*(void (/*stdcall*/ **)(uint32_t))(v34 + 1248))(0);  // 虚函数调用 槽+1248
      }
      else
      {
        v122 = (void *)((*(int (/*fastcall*/ **)(int *))(v34 + 192))(a1) + 30);  // 虚函数调用 槽+192
        v109 = (float)(int)v122;
        v117 = (*(int (/*thiscall*/ **)(int *))(*a1 + 192))(a1) + 100;  // 虚调用 vt+192（a1）取尺寸/包围盒
        a2 = (double)v117;
        v107 = a2;
        sub_4049F0(v107, v109, v23 - 540, 540, 0);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
        v24 = (uint64_t)a2;
      }
    }
    else
    {
      v25 = (*(int (/*thiscall*/ **)(int *))(*a1 + 192))(a1);  // 虚调用 vt+192（a1）取尺寸/包围盒
      v26 = *a1;
      v117 = v25 + 100;  // 计算 v117 = v25 + 100
      v108 = (float)(v25 + 100);
      v122 = (void *)((*(int (/*thiscall*/ **)(int *))(v26 + 192))(a1) + 30);  // 虚函数调用 槽+192
      a2 = (double)(int)v122;
      v106 = a2;
      sub_4049F0(v106, v108, v23, 540, 1);  // sub_4049F0 —— 二次抛物线缓动变体（按 t 在 [0, tEnd] 上的加速差项计算，pszArg5 控制正反方向）
      v27 = (int *)a1[1950];
      v28 = *v27;
      v117 = (uint64_t)a2;
      v29 = (*(int (/*fastcall*/ **)(int *, uint32_t, int))(*a1 + 124))(a1, (uint64_t)a2 >> 32, v117);  // 虚调用 vt+124（a1）目标坐标y下界
      v30 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 120))(a1, v29 - 1);  // 虚调用 vt+120（a1）转发(对象+缓冲)
      (*(void (/*thiscall*/ **)(int *, int))(v28 + 40))(v27, v30);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1[1950] + 92))(a1[1950], v115);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
      v31 = (void *)a1[29];
      v126 = 3;
      sub_4600B0(v31, 2, 0, (int)v115);  // sub_4600B0 —— 演播层注册(槽号)
      v126 = -1;
      if ( Block != nullptr )
        j__free(Block);  // 释放堆块
      v24 = v117;
    }
    v32 = a1[1951];
    if ( v32 != 0 )
      *(uint32_t *)(v32 + 12) = -v24;  // 写字段 v32+12（nSkillRec12） ← -v24
  }
  v33 = a1[1898];
  if ( v33 != 0 && a1[29] != 0 )
  {
    if ( *((uint8_t *)a1 + 7608) != 0 && (a1[1639] != 0 || *((uint8_t *)a1 + 6752) == 0) )
    {
      *((uint8_t *)a1 + 7609) = 0;  // 写字段 a1[7609]（宽1字节）
    }
    else
    {
      if ( *((uint8_t *)a1 + 7609) == 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v33 + 12))(v33, 0);  // 虚调用 vt+12（v33 虚表槽）
      if ( (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1) != 0 )  // 虚调用 vt+152（a1）取值(参数)
        v35 = a1[1899] + (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1);  // 虚调用 vt+120（a1）转发(对象+缓冲)
      else
        v35 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1) - a1[1899];  // 虚调用 vt+120（a1）转发(对象+缓冲)
      v36 = (int *)a1[1898];
      v37 = *v36;
      v117 = v35;
      v38 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);  // 虚调用 vt+128（a1）目标坐标y上界
      v39 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 124))(a1, a1[1901] + v38);  // 虚调用 vt+124（a1）目标坐标y下界
      (*(void (/*thiscall*/ **)(int *, int, int))(v37 + 40))(v36, v117, a1[1900] + v39);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1[1898] + 92))(a1[1898], v115);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
      v40 = (void *)a1[29];
      v126 = 4;
      sub_4600B0(v40, 2, 0, (int)v115);  // sub_4600B0 —— 演播层注册(槽号)
      v41 = Block;
      v45 = Block == nullptr;
      *((uint8_t *)a1 + 7609) = 1;  // 写字段 a1[7609]（宽1字节）
      v126 = -1;
      if ( !v45 )
        j__free(v41);  // 释放堆块
    }
  }
  v42 = (*(int (/*thiscall*/ **)(int *))(*a1 + 184))(a1);  // 虚调用 vt+184（a1）字符串/朝向写入
  v43 = (*(int (/*thiscall*/ **)(int *))(*a1 + 188))(a1);  // 虚调用 vt+188（a1）取尺寸
  switch ( a1[1639] )  // 按 a1[1639] 分派
  {
    case 0:  // case 0 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
      if ( v42 != 4 && v42 != (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1) )  // 虚调用 vt+152（a1）取值(参数)
        (*(void (/*thiscall*/ **)(int *, int))(*a1 + 144))(a1, v42);  // 虚调用 vt+144（a1 虚表槽）
      if ( *((uint8_t *)a1 + 6752) == 0 || a1[1803] == 0 || a1[50] != 0 )
        goto LABEL_152;
      v44 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
      if ( v44 == 4 )
      {
        v45 = *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 36) == 0;  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
      }
      else
      {
        if ( v44 == 6 )
        {
          v46 = sub_42B530(*(uint32_t *)(dword_8F7A24 + 40));  // sub_42B530 —— 类别判定取反
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
      (*(void (/*thiscall*/ **)(int *, int))(*a1 + 196))(a1, v48);  // 虚调用 vt+196（a1）物件非空判定
      sub_4926A0(a1[30]);  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
      goto LABEL_152;
    case 5:  // case 5 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
      if ( sub_699000((int)(a1 + 1640)) < 1000 && ((sub_699000((int)(a1 + 1640)) / 0xC8u) & 1) != 0 )  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*a1 + 252))(a1, 3, 0);  // 虚调用 vt+252（a1）缓存写入
      else
        (*(void (/*thiscall*/ **)(int *, int, int))(*a1 + 252))(a1, 3, -1);  // 虚调用 vt+252（a1）缓存写入
      if ( sub_699000((int)(a1 + 1640)) >= 1000 && *((uint8_t *)a1 + 7960) == 0 )  // 【clock_now(clk)】
      {
        (*(void (/*thiscall*/ **)(int *))(*a1 + 1224))(a1);  // 虚调用 vt+1224（a1 虚表槽）
        *((uint8_t *)a1 + 7960) = 1;  // 写字段 a1[7960]（宽1字节）
        v49 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        if ( v49 == 4 || v49 == 6 )
        {
          v50 = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04);  // 虚调用 vt+376（dword_8F7C04 虚表槽）
          v51 = *a1;
          v122 = v50;
          v52 = (void *)(*(int (/*thiscall*/ **)(int *))(v51 + 376))(a1);  // 调虚槽 +376：坐标同步包（type 37）
          v53 = v52 != v122 ? -13441486 : -13487386;
          v54 = a1[2012];
          if ( a1[2002] == 273 )
          {
            if ( v54 < 0x10 )
              v55 = a1 + 2007;  // 计算 v55 = a1 + 2007
            else
              v55 = (int *)a1[2007];
            v112 = sub_4633B0(a1);  // sub_4633B0 —— std::string 取数据指针（SSO 判定）
            v56 = (const char *)sub_422E70(851);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
            sprintf(v123, v56, v55, v112);  // 调 格式化到缓冲
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v123, v53, 0, -1);  // sub_43BEE0 —— 【播报上屏】
            if ( a1[2003] == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 48))(dword_8F7C04)  // 虚调用 vt+48（dword_8F7C04）归属坐标x
              && a1[2004] == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04) )  // 虚调用 vt+52（dword_8F7C04）归属坐标y
            {
              v57 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 虚调用 vt+52（dword_8F7C04）归属坐标y
              sub_496010((int)dword_99FD58, v57, 7, 1);  // sub_496010 —— 帧图像重载工厂（事件号 +48 → sub_495DC0 等）
            }
          }
          else
          {
            if ( v54 < 0x10 )
              v58 = a1 + 2007;  // 计算 v58 = a1 + 2007
            else
              v58 = (int *)a1[2007];
            v113 = v58;
            v110 = sub_4633B0(a1);  // sub_4633B0 —— std::string 取数据指针（SSO 判定）
            v59 = (const char *)sub_422E70(852);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
            sprintf(v123, v59, v110, v113);  // 调 格式化到缓冲
            sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)v123, v53, 0, -1);  // sub_43BEE0 —— 【播报上屏】
          }
          sub_432EA0("PVP_KO", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
        }
      }
      goto LABEL_152;
    case 10:  // case 10 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
      v60 = a1[1952];
      if ( v60 == 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0  // 虚调用 vt+308（a1）是否本地玩家
          && a1[1955] != -1
          && sub_699000((int)(a1 + 1640)) >= a1[1955] )  // 【clock_now(clk)】
        {
          v119 = nullptr;
          v120 = 0;
          v121 = 0;
          v126 = 5;
          v122 = (void *)1;  // v122 = 转换(1)
          sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
          (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 10, v118, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
LABEL_103:
          v126 = -1;
          sub_5E5260(v118);  // 调 动画子对象清理临时缓冲
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
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0 )  // 虚调用 vt+308（a1）是否本地玩家
      {
        v63 = sub_484E80(a1[1954]);  // sub_484E80 —— 按类型查找下标（同一匹配规则，未命中 -1）
        v64 = v63;
        if ( v63 == -1
          || (v65 = sub_44A980(v63),  // sub_44A980 —— 结果 = 带界索引 getter
              (v66 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v65 + 44))(v65)) <= (unsigned int)sub_484790(dword_8F852C)) )  // sub_484790 —— 列表项数取回（+20 有效时返回 (end-begin)/4）
        {
          v68 = a1;
        }
        else
        {
          v67 = sub_486B40(v64, a1[1971]);  // sub_486B40 —— 请求 op 47（使用槽对象）
          v68 = a1;
          if ( v67 != 0 )
          {
            (*(void (/*thiscall*/ **)(int *))(*a1 + 1276))(a1);  // 虚调用 vt+1276（a1 虚表槽）
            goto LABEL_117;
          }
        }
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 560))(v68, 0, 0, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
      }
LABEL_117:
      v69 = sub_4CE8A0(a1[1954]);  // sub_4CE8A0 —— 调用 sub_4CE8A0
      v70 = v69;
      if ( v69 != 0 && (unsigned int)sub_41C5A0(v69 + 136) > 1 )  // sub_41C5A0 —— 结果 = vector<T 4B> 大小查询（空返回 0）
      {
        v71 = *(uint32_t *)(v70 + 140) + 4;
        v72 = *a1;
        v73 = sub_41ACF0(v71);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v72 + 212))(a1, v73, -1, 0, 0);  // 调虚槽 +212：播放音效 TAG(→50 声道)
      }
      if ( (uint8_t)sub_423340(a1 + 1964, szPassword) != 0 )  // sub_423340 —— 串首比较判定（不等）
      {
        if ( (unsigned int)a1[1970] < 0x10 )
          v74 = a1 + 1965;  // 计算 v74 = a1 + 1965
        else
          v74 = (int *)a1[1965];
        (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t))(*a1 + 212))(a1, v74, -1, 0, 0);  // 虚调用 vt+212（a1 虚表槽）
      }
      *((uint8_t *)a1 + 7840) = 1;  // 写字段 a1[7840]（宽1字节）
LABEL_126:
      v75 = a1[1953];
      if ( v75 == 2 || v75 == 1 )
      {
        if ( *((uint8_t *)a1 + 7840) != 0 && a1[1956] != -1 && sub_699000((int)(a1 + 1640)) >= a1[1956] )  // 【clock_now(clk)】
          goto LABEL_151;
      }
      else if ( a1[1956] != -1 && sub_699000((int)(a1 + 1640)) >= a1[1956] )  // 【clock_now(clk)】
      {
        if ( (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1) <= 0 )  // 虚调用 vt+128（a1）目标坐标y上界
          goto LABEL_151;
        v119 = nullptr;
        v120 = 0;
        v121 = 0;
        v126 = 6;
        v122 = (void *)1;  // v122 = 转换(1)
        sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
        v122 = nullptr;
        sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
        v122 = nullptr;
        sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
        (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 6, v118, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
        goto LABEL_103;
      }
LABEL_152:
      if ( (int *)dword_8F7C04 == a1 )  // dword_8F7C04（本地玩家对象）
      {
        if ( a1[1639] == 8 && (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 )  // sub_4BFBC0 —— 列表登记与状态判定
        {
          byte_9A0358 = 0;
          (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 1328))(a1, 0);  // 虚调用 vt+1328（a1 虚表槽）
          byte_9A0384 = 0;  // byte_9A0384 —— 局部 byte_9A0384 → 1
        }
        if ( (int *)dword_8F7C04 == a1 && a1[50] != 2 )  // dword_8F7C04（本地玩家对象）
        {
          (*(void (/*thiscall*/ **)(int *))(*a1 + 1324))(a1);  // 虚调用 vt+1324（a1 虚表槽）
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 852))(a1) != 0 )  // 虚调用 vt+852（a1 虚表槽）
          {
            for ( i = 0; i < 9; ++i )  // 遍历计次循环（i < 9）
            {
              if ( (uint8_t)sub_4BF450(i, 1) != 0 )  // sub_4BF450 —— 记录状态查询（记录 16 字节：+12 使能 / +13 副标志）
                break;
            }
            if ( i != 9 )
              (*(void (/*thiscall*/ **)(int *))(*a1 + 860))(a1);  // 虚调用 vt+860（a1 虚表槽）
          }
          switch ( a1[1639] )  // 按 a1[1639] 分派
          {
            case 0:  // case 0 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
              if ( ((uint8_t)sub_4BFBC0(&unk_9A0388, 1) != 0 || (uint8_t)sub_4BFBC0(&unk_9A03B4, 1) != 0)  // sub_4BFBC0 —— 列表登记与状态判定；sub_4BFBC0 —— 列表登记与状态判定
                && a1[1812] != 0 )
              {
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 11, 0, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
              }
              else
              {
                if ( (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 )  // sub_4BFBC0 —— 列表登记与状态判定
                {
                  v119 = nullptr;
                  v120 = 0;
                  v121 = 0;
                  v126 = 9;
                  v122 = nullptr;
                  sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
                  v122 = nullptr;
                  sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
                  v122 = nullptr;
                  sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
                  (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 6, v118, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
                  goto LABEL_171;
                }
                if ( (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 && a1[50] == 0 )  // sub_4BFBC0 —— 列表登记与状态判定
                {
                  if ( a1[1972] == 0 || *(uint16_t *)(dword_8F8538 + 4) != 0xFFFF )  // dword_8F8538 —— 技能施放请求（包 op 19 变体：槽/参数/来源字段序不同）
                  {
                    v119 = nullptr;
                    v120 = 0;
                    v121 = 0;
                    v126 = 10;
                    v122 = nullptr;
                    sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
                    (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 8, v118, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
                    goto LABEL_171;
                  }
                  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 13, 0, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
                }
              }
              break;
            case 6:  // case 6 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
              if ( a1[1723] == 1 && (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 && a1[1724] < a1[1725] )  // sub_4BFBC0 —— 列表登记与状态判定
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 7, 0, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
              break;
            case 8:  // case 8 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
              v91 = sub_41A5E0(a1 + 1757);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
              v92 = a1[1974];
              if ( v92 != 0 && v91 < (a1[1975] - v92) >> 2 )
              {
                v93 = *(uint32_t *)(a1[30] + 148);
                if ( v93 >= *(uint32_t *)(a1[1974] + 4 * sub_41A5E0(a1 + 1757))  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                  && (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0  // sub_4BFBC0 —— 列表登记与状态判定
                  && a1[50] == 0 )
                {
                  v94 = sub_41A5E0(a1 + 1757);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                  if ( v94 + 1 < (unsigned int)sub_41C5A0(a1 + 1549) )  // sub_41C5A0 —— 结果 = vector<T 4B> 大小查询（空返回 0）
                  {
                    v119 = nullptr;
                    v120 = 0;
                    v121 = 0;
                    v126 = 11;
                    v122 = (void *)(sub_41A5E0(a1 + 1757) + 1);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
                    sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
                    (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 8, v118, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
                    goto LABEL_171;
                  }
                }
              }
              break;
            case 11:  // case 11 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
              if ( (uint8_t)sub_4BFBC0(&unk_9A035C, 1) != 0 )  // sub_4BFBC0 —— 列表登记与状态判定
              {
                v119 = nullptr;
                v120 = 0;
                v121 = 0;
                v126 = 12;
                v122 = nullptr;
                sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
                v122 = nullptr;
                sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
                v122 = nullptr;
                sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
                (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 6, v118, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
LABEL_171:
                v126 = -1;
                sub_5E5260(v118);  // 调 动画子对象清理临时缓冲
              }
              else if ( (uint8_t)sub_4BFBC0(&unk_9A0330, 1) != 0 )  // sub_4BFBC0 —— 列表登记与状态判定
              {
                (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 12, 0, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
              }
              break;
            default:
              break;
          }
          v95 = a1[1639];
          if ( (v95 == 0 || v95 == 11 || v95 == 8)  // 判定 v95 == 0 或 v95 == 11 或 v95 == 8
            && sub_4842B0(169, nullptr) != -1  // sub_4842B0 —— 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
            && (*(uint8_t (/*thiscall*/ **)(int *, int))(*a1 + 1312))(a1, 169) != 0 )  // 虚调用 vt+1312（a1 虚表槽）
          {
            v119 = nullptr;
            v120 = 0;
            v121 = 0;
            v126 = 13;
            v122 = (void *)1;  // v122 = 转换(1)
            sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
            v122 = (void *)1;  // v122 = 转换(1)
            sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
            (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*a1 + 1160))(a1, 169, 0);  // 虚调用 vt+1160（a1）读技能表(变体)
            v122 = (void *)sub_47E9D0(v114);  // sub_47E9D0 —— 收招/结束例程
            sub_431230(&v122);  // sub_431230 —— uint32 vector push_back
            v114 = 0;
            (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t))(*a1 + 560))(a1, 6, v118, 0);  // 虚调用 vt+560（a1 虚表槽）
            v126 = -1;
            if ( v119 != nullptr )
              j__free(v119);  // 释放堆块
          }
          v96 = (void **)&unk_791BE0;
          do
          {
            v97 = a1[1639];
            if ( (v97 == 0 || v97 == 11)
              && sub_4842B0((int)*v96, nullptr) != -1  // sub_4842B0 —— 技能槽对象查询与结果收集（+392 二级列表 / 回退全局槽表）
              && (*(uint8_t (/*thiscall*/ **)(int *, void *))(*a1 + 1312))(a1, *v96) != 0 )  // 虚调用 vt+1312（a1 虚表槽）
            {
              v119 = nullptr;
              v120 = 0;
              v121 = 0;
              v122 = *v96;
              v126 = 14;
              sub_430C80(nullptr, 1, (int)&v122);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
              (*(void (/*thiscall*/ **)(int *, int, char *, uint32_t, uint32_t))(*a1 + 560))(a1, 14, v118, 0, 0);  // 虚调用 vt+560（a1 虚表槽）
              v126 = -1;
              if ( v119 != nullptr )
                j__free(v119);  // 释放堆块
              v119 = nullptr;
              v120 = 0;
              v121 = 0;
            }
            ++v96;  // 计数自增 v96
          }
          while ( (int)v96 < (int)&CNImageLoader `RTTI Type Descriptor' );
          if ( pDwArg1[1639] != 5 )
          {
            pObj5 = pDwArg1[1924];
            if ( pObj5 != 0
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 688))(pObj5) != 3  // 虚调用 vt+688（pObj5 虚表槽）
              && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 688))(pDwArg1[1924]) != 4 )  // 调虚槽 +688：附加块基址 this+6160
            {
              if ( (uint8_t)sub_4BFBC0(&unk_9A0438, 0) != 0  // sub_4BFBC0 —— 列表登记与状态判定
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 700))(pDwArg1[1924]) == 0  // 调虚槽 +700：读 +6296 槽
                || (uint8_t)sub_4BFBC0(&unk_9A040C, 0) != 0  // sub_4BFBC0 —— 列表登记与状态判定
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 700))(pDwArg1[1924]) == 0 )  // 调虚槽 +700：读 +6296 槽
              {
                if ( (unsigned int)pDwArg1[1931] < 0x10 )
                  v99 = pDwArg1 + 1926;  // 计算 v99 = pDwArg1 + 1926
                else
                  v99 = (int *)pDwArg1[1926];
                (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, v99, -1, 0, 0, v114);  // 虚调用 vt+212（pDwArg1 虚表槽）
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[1924] + 712))(pDwArg1[1924], 1);  // 调虚槽 +712：表尾插 thunk（+1020 表 → sub_474950）
              }
              else if ( (uint8_t)sub_4BFBC0(&byte_9A03E0, 0) != 0  // sub_4BFBC0 —— 列表登记与状态判定
                     && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 700))(pDwArg1[1924]) == 1  // 调虚槽 +700：读 +6296 槽
                      || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[1924] + 700))(pDwArg1[1924]) == 0) )  // 调虚槽 +700：读 +6296 槽
              {
                if ( (unsigned int)pDwArg1[1931] < 0x10 )
                  v100 = pDwArg1 + 1926;  // 计算 v100 = pDwArg1 + 1926
                else
                  v100 = (int *)pDwArg1[1926];
                (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, v100, -1, 0, 0, v114);  // 虚调用 vt+212（pDwArg1 虚表槽）
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[1924] + 712))(pDwArg1[1924], 0);  // 调虚槽 +712：表尾插 thunk（+1020 表 → sub_474950）
              }
            }
          }
        }
      }
      pObj = pDwArg1[2000];
      if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 68))(pObj) == 0 )  // 虚调用 vt+68（pObj 虚表槽）
        sub_4B2780(pDwArg1);  // sub_4B2780 —— 坐标记录生成（·0x4600B0）
      v102 = pDwArg1 + 1617;  // 计算 v102 = pDwArg1 + 1617
      for ( j = 18; j != 0; --j )  // 遍历计次循环（j != 0）
      {
        if ( *v102 != 0 )
          sub_4EAD30();  // sub_4EAD30 —— 时长到期回调（·this+1336 + ·this+1340 <= clock_now）
        ++v102;  // 计数自增 v102
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
              sub_499770(2, 0);  // sub_499770 —— 双槽设置（+268/+272）
          }
          else
          {
            sub_499770(-2, 0);  // sub_499770 —— 双槽设置（+268/+272）
          }
        }
        else
        {
          sub_499770(0, 0);  // sub_499770 —— 双槽设置（+268/+272）
          *((uint8_t *)pDwArg1 + 8100) = 0;  // 写字段 pDwArg1[8100]（宽1字节）
        }
      }
      return;
    case 11:  // case 11 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
      if ( v42 == 4 )
      {
        if ( v43 != 4 )
          goto LABEL_142;
      }
      else if ( v42 == (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) )  // 虚调用 vt+152（pDwArg1）取值(参数)
      {
        goto LABEL_142;
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);  // 虚调用 vt+560（pDwArg1 虚表槽）
LABEL_142:
      if ( pDwArg1[1772] == 7 && pDwArg1[29] != 0 && (uint8_t)sub_41C6E0(pDwArg1 + 1779) != 0 )  // sub_41C6E0 —— 超时判定（clock_now(clk) >= this+24 截止时刻）
      {
        pObj4 = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 924))(pDwArg1, 2)];  // 虚调用 vt+924（pDwArg1 虚表槽）
        v77 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1) == 0;  // 虚调用 vt+152（pDwArg1）取值(参数)
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 28))(pObj4) + 84) = v77;  // 虚调用 vt+28（pObj4 虚表槽）
        v78 = *(uint32_t *)pObj4;
        v79 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 虚调用 vt+128（pDwArg1）目标坐标y上界
        v80 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v79);  // 虚调用 vt+124（pDwArg1）目标坐标y下界
        v81 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v80);  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
        (*(void (/*thiscall*/ **)(int, int))(v78 + 40))(pObj4, v81);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj4 + 12))(pObj4, 0);  // 虚调用 vt+12（pObj4 虚表槽）
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj4 + 92))(pObj4, v115);  // 虚调用 vt+92（pObj4）读剩余(返回长度)
        v82 = (void *)pDwArg1[29];
        v126 = 7;
        sub_4600B0(v82, 2, 0, (int)v115);  // sub_4600B0 —— 演播层注册(槽号)
        *((uint8_t *)pDwArg1 + 7129) = 0;  // 写字段 pDwArg1[7129]（宽1字节）
        *((uint8_t *)pDwArg1 + 7130) = 0;  // 写字段 pDwArg1[7130]（宽1字节）
        sub_698F90((int)(pDwArg1 + 1779), 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        v126 = -1;
        sub_5E5260(v115);  // 调 动画子对象清理临时缓冲
      }
      goto LABEL_152;
    case 12:  // case 12 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
      goto LABEL_150;
    case 13:  // case 13 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
      if ( *(uint8_t *)(pDwArg1[30] + 170) != 0 )
        goto LABEL_151;
      goto LABEL_152;
    case 14:  // case 14 分派（§K 0x4B7110-0x4B89D0 升级/结算演出（LevelNormalizeLibra、PVP_KO））
      v83 = sub_699000((int)(pDwArg1 + 1640));  // 【clock_now(clk)】
      if ( v83 < sub_491C10(pDwArg1[30]) - 300 )  // sub_491C10 —— 结果 = 遍历帧数组（首+44/尾+48，步长 88）
      {
        v84 = *(uint32_t *)pDwArg1[1992];
        pMem2 = (void *)pDwArg1[1992];
        v85 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 192))(pDwArg1);  // 虚调用 vt+192（pDwArg1）取尺寸/包围盒
        v86 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 虚调用 vt+128（pDwArg1）目标坐标y上界
        v87 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v85 + v86 + 30);  // 虚调用 vt+124（pDwArg1）目标坐标y下界
        v88 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v87);  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
        (*(void (/*thiscall*/ **)(void *, int))(v84 + 40))(pMem2, v88);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pDwArg1[1992] + 92))(pDwArg1[1992], v115);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：42…
        v89 = (void *)pDwArg1[29];
        v126 = 8;
        sub_4600B0(v89, 2, 0, (int)v115);  // sub_4600B0 —— 演播层注册(槽号)
        v126 = -1;
        sub_5E5260(v115);  // 调 动画子对象清理临时缓冲
      }
LABEL_150:
      if ( *(uint8_t *)(pDwArg1[30] + 170) != 0 )
LABEL_151:
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);  // 虚调用 vt+560（pDwArg1 虚表槽）
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
int /*thiscall*/ sub_4B89D0(int *this, int nArg2, int pArg3, float fArg4, float fArg5)  // sub_4B89D0 —— 跑步地面循环 + 蓄气/霸体特效 G_RUN_FLOOR_LOOP/RUN_GRASS/SOIL/STONE_LOOP 按 +212 地形选播
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
  uint64_t fld_e28; // rax  | +0x0070 → 宿主对象指针（IRDActiveObject·基类；va=004D6970）
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
  int fld_e302; // [esp+30h] [ebp+Ch]  | +0x0078 → 动画对象指针（IRDCharacter；va=00499020）
  int fld_e303; // [esp+30h] [ebp+Ch]  | +0x0078 → 动画对象指针（IRDCharacter；va=00499020）

  fld_e1639 = *(this + 1639);  // 读字段 fld_e1639 = this+1639（bMainStateMirror2）
  switch ( fld_e1639 )  // 按 fld_e1639 分派
  {
    case 10:  // case 10 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      if ( *(this + 1952) != 0 )  // this+7808〔风格/分支选择〕
        goto LABEL_12;
      break;
    case 11:  // case 11 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 9);  // 虚调用 vt+216（this）全场广播
      goto LABEL_12;
    case 14:  // case 14 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      if ( nArg2 == 0 && *(this + 1991) != -1 )  // this+1991 nSkillNo
      {
        fld_e1991 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *(this + 1991));  // 虚调用 vt+1160（this）读技能表(变体)
        if ( fld_e1991 != 0 )
        {
          v7 = *this;
          fld_e19912 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 1991));  // 虚调用 vt+1140（this）读技能表
          (*(void (/*thiscall*/ **)(int *, int, int))(v7 + 1300))(this, fld_e1991, fld_e19912);  // 调虚槽 +1300：CNSwordman__vmt514
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(this + 1993));  // 虚调用 vt+208（this）动画件回挂
      break;
    default:
      goto LABEL_12;
  }
  (*(void (/*thiscall*/ **)(int *))(*this + 996))(this);  // 虚调用 vt+996（this 虚表槽）
LABEL_12:
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 5:  // case 5 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      *((uint8_t *)this + 7960) = 0;  // 写字段 this[7960]（宽1字节）
      break;
    case 10:  // case 10 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      v10 = **(uint32_t **)(pArg3 + 4);  // pArg3+4〔宿主对象〕
      *(this + 1952) = v10;  // 写字段 this+1952 ← v10
      if ( v10 != 0 )
      {
        v20 = *this;
        if ( *(this + 1953) == 2 )  // this+7812〔nSubStateA(推断)〕
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v20 + 196))(this, *(this + 1542));  // 调虚槽 +196：动画对象设置（换域 + 播放）
        else
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v20 + 196))(this, *(this + *(this + 1957) + 1808));  // this+7828〔nSubStateD〕
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 888))(  // 虚调用 vt+888（this）帧长标定
          this,
          *(this + 1958),
          *(this + 1958),
          *(this + 1959),
          *(this + 1959));
        *(this + 1956) = 1000 * *(this + 1956) / *(this + 1664);  // 写字段 this+1956 ← 1000 * *(this + 1956) / *(this + 1664)
      }
      else
      {
        *(this + 1953) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4);  // 写字段 this+1953 ← *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 4)
        *(this + 1954) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8);  // 写字段 this+1954 ← *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 8)
        *(this + 1955) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12);  // 写字段 this+1955 ← *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 12)
        *(this + 1956) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 16);  // 写字段 this+1956 ← *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 16)
        *(this + 1957) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 20);  // 写字段 this+1957 ← *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 20)
        v11 = *(uint32_t *)(pArg3 + 4);  // 读字段 v11 = pArg3+4（pHostObj）
        v12 = *(uint32_t *)(v11 + 24);  // 读字段 v12 = v11+24（nPageMax）
        *(this + 1958) = *(uint32_t *)(v11 + 28);  // 写字段 this+1958 ← *(uint32_t *)(v11 + 28)
        v51 = 1000;
        *(this + 1959) = 1000;  // 写字段 this+1959 ← 1000
        if ( (unsigned int)sub_41C5A0(pArg3) > 8 )  // sub_41C5A0 —— 结果 = vector<T 4B> 大小查询（空返回 0）
          v51 = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 32);  // pArg3+4〔宿主对象〕
        if ( (unsigned int)sub_41C5A0(pArg3) > 9 )  // sub_41C5A0 —— 结果 = vector<T 4B> 大小查询（空返回 0）
          *(this + 1959) = *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 36);  // 写字段 this+1959 ← *(uint32_t *)(*(uint32_t *)(pArg3 + 4) + 36)
        v13 = *this;
        if ( *(this + 1953) == 2 )  // this+7812〔nSubStateA(推断)〕
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 196))(this, *(this + 1542));  // 调虚槽 +196：动画对象设置（换域 + 播放）
        else
          (*(void (/*thiscall*/ **)(int *, uint32_t))(v13 + 196))(this, *(this + *(this + 1957) + 1804));  // this+7828〔nSubStateD〕
        (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, v12, v12, v51, v51);  // 虚调用 vt+888（this）帧长标定
        fld_e1955 = 1000 * *(this + 1955) / *(this + 1664);
        *(this + 1955) = fld_e1955;  // 写字段 this+1955 ← fld_e1955
        if ( v12 == 4 )
          (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*this + 992))(this, fld_e1955, 0);  // 虚调用 vt+992（this 虚表槽）
        if ( *(this + 1955) == 0 )  // this+7820〔pInteractSnap(推断)〕
        {
          fld_e30 = (void *)*(this + 30);  // this+120〔pAnimObj〕
          v16 = sub_42FC90(fld_e30);  // sub_42FC90 —— 88B 元素计数（+44 组）
          sub_4AECE0(fld_e30, v16 - 1);  // 调 切武器动画
          *(this + 1955) = 70;  // 写字段 this+1955 ← 70
        }
        fld_e1953 = *(this + 1953);  // 读字段 fld_e1953 = this+1953
        if ( fld_e1953 == 1 || fld_e1953 == 2 )  // 判定 fld_e1953 == 1 或 fld_e1953 == 2
        {
          if ( (int *)dword_8F7C04 == this )  // dword_8F7C04（本地玩家对象）
          {
            fld_e1954 = sub_484E80(*(this + 1954));  // sub_484E80 —— 按类型查找下标（同一匹配规则，未命中 -1）
            if ( fld_e1954 != -1 )
            {
              pObj = sub_44A980(fld_e1954);  // sub_44A980 —— 结果 = 带界索引 getter
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 100))(pObj);  // 虚调用 vt+100（pObj 虚表槽）
            }
          }
          *(this + 1971) = (fld_e1639 == 10) + 1;  // 写字段 this+1971 ← (fld_e1639 == 10) + 1
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 虚调用 vt+876（this）双段位移
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 虚调用 vt+876（this）双段位移
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 虚调用 vt+896（this 虚表槽）
      sub_495890(2, 0);  // sub_495890 —— 模式选择式方位设置（1/2/其他 三分支）
      *((uint8_t *)this + 7840) = 0;  // 写字段 this[7840]（宽1字节）
      break;
    case 11:  // case 11 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      if ( *((uint8_t *)this + 7924) != 0 )
      {
        v21 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 虚调用 vt+672（this）队伍编号取址
        v22 = sub_4B0D20(v21);  // sub_4B0D20 —— 结果 = 双字段乘积取值
        v47 = 0;
        v46 = 0;
        v45 = 9;
        if ( dword_9A012C != 0 )
        {
          (*(void (/*thiscall*/ **)(int *, const char *))(*this + 212))(this, "G_RUN_FLOOR_LOOP");  // 虚调用 vt+212（this 虚表槽）
        }
        else if ( v22 >= 60000 )
        {
          if ( v22 >= 100000 )
            (*(void (/*thiscall*/ **)(int *, const char *))(*this + 212))(this, "RUN_GRASS_LOOP");  // 虚调用 vt+212（this 虚表槽）
          else
            (*(void (/*thiscall*/ **)(int *, const char *))(*this + 212))(this, "RUN_SOIL_LOOP");  // 虚调用 vt+212（this 虚表槽）
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, const char *))(*this + 212))(this, "RUN_STONE_LOOP");  // 虚调用 vt+212（this 虚表槽）
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1812));  // 虚调用 vt+196（this）物件非空判定
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 0, 286, 238, 1, 0, 0);  // 虚调用 vt+876（this）双段位移
      (*(void (/*thiscall*/ **)(int *, int, int, int, int, uint32_t, uint32_t))(*this + 876))(this, 1, 136, 114, 1, 0, 0);  // 虚调用 vt+876（this）双段位移
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 1, 1, 1000, 1000);  // 虚调用 vt+888（this）帧长标定
      sub_495890(2, 0);  // sub_495890 —— 模式选择式方位设置（1/2/其他 三分支）
      break;
    case 12:  // case 12 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      if ( (unsigned int)*(this + 1989) < 0x10 )
        pThis_7C0 = this + 1984;
      else
        pThis_7C0 = (int *)*(this + 1984);
      (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_7C0, -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
      (*(void (/*thiscall*/ **)(int *, int *))(*this + 344))(this, this + 1816);  // 虚调用 vt+344（this）动画件访问(基偏移)
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1813));  // 虚调用 vt+196（this）物件非空判定
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 1, 2, 1000, 1000);  // 虚调用 vt+888（this）帧长标定
      fld_e302 = sub_491C70(*(this + 30), *(this + 1982));  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
      fld_e28 = (uint64_t)fabs(*(float *)(*(this + 28) + 16));  // this+112〔pHostComp112〕
      (*(void (/*fastcall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*this + 876))(  // 虚调用 vt+876（this）双段位移
        this,
        -1000 * (int)fld_e28 % fld_e302,  // fld_e28=this+112 pHostComp112
        0,
        fld_e28,  // fld_e28=this+112 pHostComp112
        fld_e28,  // fld_e28=this+112 pHostComp112
        0,
        -1000 * (int)fld_e28 / fld_e302,  // fld_e28=this+112 pHostComp112
        1);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 虚调用 vt+876（this）双段位移
      v25 = *this;
      v26 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);  // 虚调用 vt+152（this）取值(参数)
      (*(void (/*thiscall*/ **)(int *, int))(v25 + 896))(this, v26);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
      break;
    case 13:  // case 13 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1814));  // 虚调用 vt+196（this）物件非空判定
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 虚调用 vt+876（this）双段位移
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 虚调用 vt+876（this）双段位移
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);  // 虚调用 vt+888（this）帧长标定
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 虚调用 vt+896（this 虚表槽）
      sub_495890(2, 0);  // sub_495890 —— 模式选择式方位设置（1/2/其他 三分支）
      if ( (int *)dword_8F7C04 == this && *(this + 1972) != 0 )  // dword_8F7C04（本地玩家对象）
        sub_486470(*(this + 1972));  // sub_486470 —— 请求 op 46（掉落表现校验后开关槽对象）
      break;
    case 14:  // case 14 分派（§L 0x4B89D0-0x4B9280 跑步地面循环 + 蓄气/霸体特效）
      fld_e1815 = *(this + 1815);  // 读字段 fld_e1815 = this+1815
      v28 = *this;
      *(this + 1991) = **(uint32_t **)(pArg3 + 4);  // 写字段 this+1991 ← **(uint32_t **)(pArg3 + 4)
      (*(void (/*thiscall*/ **)(int *, int))(v28 + 196))(this, fld_e1815);  // 调虚槽 +196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(  // 虚调用 vt+876（this）双段位移
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 虚调用 vt+876（this）双段位移
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);  // 虚调用 vt+896（this 虚表槽）
      sub_495890(2, 0);  // sub_495890 —— 模式选择式方位设置（1/2/其他 三分支）
      fld_e19913 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 1991));  // 虚调用 vt+1140（this）读技能表
      (*(void (/*thiscall*/ **)(int *, uint32_t, int))(*this + 1160))(this, *(this + 1991), fld_e19913);  // 虚调用 vt+1160（this）读技能表(变体)
      v30 = sub_4B1C40(v45);  // sub_4B1C40 —— 14 字节表按 1 基索引取值
      fld_e303 = *(uint32_t *)(*(this + 30) + 36);  // this+120〔pAnimObj〕
      v31 = *this;
      Block = (double)fld_e303 / (double)v30;  // fld_e303=this+120 pAnimObj
      v32 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 虚调用 vt+672（this）队伍编号取址
      v33 = (uint64_t)((double)sub_495540(v32) * Block);  // sub_495540 —— 槽对乘积读取（+872/+886）
      (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, uint32_t, int, uint32_t))(v31 + 888))(  // 调虚槽 +888：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
        this,
        HIDWORD(v33),
        0,
        0,
        1000,
        v33);
      if ( *(this + 1992) == 0 )
      {
        pMem = operator new(0x12Cu);  // 堆分配
        if ( pMem != nullptr )
          v35 = sub_428F30(pMem, (int)"Common/CommonEffect/Particle/BuffChargeParticle.ptl", (int)this);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
        else
          v35 = nullptr;
        *(this + 1992) = (int)v35;  // 写字段 this+1992 ← (int)v35
        (*(void (/*thiscall*/ **)(uint32_t *, int *))(*v35 + 112))(v35, this);  // 虚调用 vt+112（v35）坐标三元组写入
      }
      if ( *(this + 1993) == 0 )
      {
        if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
          v36 = sub_431860((char)"Common/CommonEffect/Animation/BuffChargeGlow.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
        else
          v36 = 0;
        *(this + 1993) = v36;  // 写字段 this+1993 ← v36
      }
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1992) + 12))(*(this + 1992), 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
      v37 = *this;
      v38 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 192))(this, 1, 0);  // 虚调用 vt+192（this）取尺寸/包围盒
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int))(v37 + 204))(this, 1, *(this + 1993), 0, -30 - v38);  // 调虚槽 +204：定时器插入
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
        this,
        "MOON_CURTAIN_LIGHT",  // 资源/动画 TAG MOON_CURTAIN_LIGHT
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, int))(*this + 992))(this, fld_e303, 1);  // 虚调用 vt+992（this 虚表槽）
      break;
    default:
      break;
  }
  sub_58E920(this, nArg2, pArg3, fArg4, fArg5);  // 【IRDActiveObject__vmt1D8】
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 6 )
    {
      if ( *(this + 1723) == 0 && fld_e1639 == 11 )  // fld_e1639=this+1639 bMainStateMirror2
      {
        *(this + 1719) = 286;  // 写字段 this+1719 ← 286
        *(this + 1720) = 238;  // 写字段 this+1720 ← 238
        *(this + 1721) = 136;  // 写字段 this+1721 ← 136
        *(this + 1722) = 114;  // 写字段 this+1722 ← 114
      }
    }
    else if ( nArg2 == 8 && sub_41A5E0((unsigned int)(this + 1757)) > 0 )  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
    {
      fld_e1977 = 0;
      fld_e1978 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, int))(*this + 308))(this, v45, v46, v47) != 0 )  // 虚调用 vt+308（this）是否本地玩家
      {
        v50 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1132))(this, 0);  // 虚调用 vt+1132（this 虚表槽）
        if ( v50 == 4 )
        {
          fld_e1977 = *(this + 1977);  // 读字段 fld_e1977 = this+1977
          fld_e1978 = *(this + 1978);  // 读字段 fld_e1978 = this+1978
        }
        else if ( v50 == (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) )  // 虚调用 vt+152（this）取值(参数)
        {
          fld_e1977 = *(this + 1979);  // 读字段 fld_e1977 = this+1979
          fld_e1978 = *(this + 1980);  // 读字段 fld_e1978 = this+1980
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(this, 0, fld_e1977, fld_e1977, 0, fld_e1978, 1);  // 虚调用 vt+876（this）双段位移
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);  // 虚调用 vt+876（this）双段位移
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);  // 虚调用 vt+888（this）帧长标定
      v41 = *this;
      v42 = (*(int (/*thiscall*/ **)(int *, int))(*this + 152))(this, 4);  // 虚调用 vt+152（this）取值(参数)
      (*(void (/*thiscall*/ **)(int *, int))(v41 + 896))(this, v42);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
    }
  }
  else
  {
    fld_e29 = *(this + 29);  // 读字段 fld_e29 = this+29
    if ( fld_e29 != 0 && *(uint8_t *)(fld_e29 + 152) == 0 )  // fld_e29=this+29 pSessionCtx
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1803));  // 虚调用 vt+196（this）物件非空判定
      sub_4926A0(*(this + 30));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
    }
  }
  return (*(int (/*thiscall*/ **)(int *))(*this + 1316))(this);  // 虚调用 vt+1316（this 虚表槽）
}


// ============================================================
// §M 0x4B9280-0x4BA8A0  奖励演出族（SpUp/Dice/金币/道具/FP_UP/ENERGY_CHARGE）
// ============================================================
// ------------------------------------------------------------
// 0x4B9280 sub_4B9280 —— SP 增加演出（SpUp1/2/3.ani 按档位，挂子链 +204/+208）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B9280(char *this, char pszArg2)  // sub_4B9280 —— SP 增加演出（SpUp1/2/3.ani 按档位，挂子链 +204/+208）
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

  if ( pszArg2 != 0 && *(this + 7764) != 0 )  // this+7764 【推断】计时/对象槽
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 1232))(this, 0);  // 虚调用 vt+1232（this 虚表槽）
  *(this + 7764) = pszArg2;  // 写字段 this+7764（bTimerObj） ← pszArg2
  if ( pszArg2 != 0 )
  {
    pThis_1E58 = this + 7768;  // this+7768〔pObj7768〕
    if ( *((uint32_t *)this + 1942) == 0 )  // this+7768〔pObj7768〕
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v4 = sub_431860((char)"Common/Etc/Animation/SpUp1.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v4 = 0;
      *pThis_1E58 = v4;  // pThis_1E58=this+7768 pObj7768
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v5 = sub_431860((char)"Common/Etc/Animation/SpUp2.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v5 = 0;
      *((uint32_t *)this + 1943) = v5;  // 写字段 this+1943（nDifficulty）
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v6 = sub_431860((char)"Common/Etc/Animation/SpUp3.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v6 = 0;
      *((uint32_t *)this + 1944) = v6;  // 写字段 this[1944]（宽4字节）
    }
    for ( i = 3; i != 0; --i )  // 遍历计次循环（i != 0）
    {
      v7 = *(uint32_t *)this;
      pThis_C0 = (*(int (/*thiscall*/ **)(char *, int, uint32_t))(*(uint32_t *)this + 192))(this, 1, 0);  // 虚调用 vt+192（this）取尺寸/包围盒
      (*(void (/*thiscall*/ **)(char *, int, uint32_t, uint32_t, int))(v7 + 204))(this, 100, *pThis_1E58++, 0, -62 - pThis_C0);  // 调虚槽 +204：定时器插入
      result = i - 1;
    }
  }
  else
  {
    pThis_1E582 = this + 7768;  // this+7768〔pObj7768〕
    for ( j = 3; j != 0; --j )  // 遍历计次循环（j != 0）
      result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 208))(this, *pThis_1E582++);  // 虚调用 vt+208（this）动画件回挂
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B9400 sub_4B9400 —— BonusSpUp 图标/文字演出（BonusSpUpIcon.ani/BonusSpUpText.ani → sub_4924C0 +44）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B9400(int **this, char pszArg2, int nArg3)  // sub_4B9400 —— BonusSpUp 图标/文字演出（BonusSpUpIcon.ani/BonusSpUpText.ani → sub_4924C0 +44）
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
  *((uint8_t *)this + 7780) = pszArg2;  // 写字段 this[7780]（宽1字节）
  if ( pszArg2 != 0 )
  {
    if ( *(this + 1946) == nullptr )
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v4 = (int *)sub_431860((char)"Common/Etc/Animation/BonusSpUpIcon.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v4 = nullptr;
      *(this + 1946) = v4;  // 写字段 this+1946 ← v4
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v5 = (int *)sub_431860((char)"Common/Etc/Animation/BonusSpUpText.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v5 = nullptr;
      *(this + 1947) = v5;  // 写字段 this+1947 ← v5
    }
    v6 = *(uint32_t *)(((int (/*thiscall*/ *)(int **, int))(*this)[290])(this, nArg3) + 380);
    fld_e1946 = (int)*(this + 1946);
    v8 = *(uint32_t *)(fld_e1946 + 44);  // 读字段 v8 = fld_e1946+44（nExpireMs）
    v9 = fld_e1946 + 40;  // 计算 v9 = fld_e1946 + 40
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
      fld_e19462 = (uint32_t *)sub_4924C0(*(this + 1946), i++);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
    pThis_79A = this + 1946;
    for ( j = 2; j != 0; --j )  // 遍历计次循环（j != 0）
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
    for ( k = 2; k != 0; --k )  // 遍历计次循环（k != 0）
      result = ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[52])(this, *pThis_79A2++);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B95B0 sub_4B95B0 —— 金币演出（UseCoin.ani + UseCoinParticle.ptl）
// ------------------------------------------------------------
int */*thiscall*/ sub_4B95B0(int *this, void *Block)  // sub_4B95B0 —— 金币演出（UseCoin.ani + UseCoinParticle.ptl）
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
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 1248))(this, 0);  // 虚调用 vt+1248（this）归属者标记
  *((uint8_t *)this + 7792) = (uint8_t)Block;  // 写字段 this[7792]（宽1字节）
  if ( (uint8_t)Block != 0 )
  {
    if ( *(this + 1949) == 0 )
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v3 = sub_431860((char)"Common/Etc/Animation/UseCoin.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v3 = 0;
      *(this + 1949) = v3;  // 写字段 this+1949 ← v3
      pMem = operator new(0x12Cu);  // 堆分配
      if ( pMem != nullptr )
        v5 = sub_428F30(pMem, (int)"Common/Etc/Particle/UseCoinParticle.ptl", (int)this);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
      else
        v5 = nullptr;
      *(this + 1950) = (int)v5;  // 写字段 this+1950 ← (int)v5
      (*(void (/*thiscall*/ **)(uint32_t *, int *))(*v5 + 112))(v5, this);  // 虚调用 vt+112（v5）坐标三元组写入
    }
    v6 = *this;
    v7 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 192))(this, 1, 0);  // 虚调用 vt+192（this）取尺寸/包围盒
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int))(v6 + 204))(this, 102, *(this + 1949), 0, -30 - v7);  // 调虚槽 +204：定时器插入
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1950) + 12))(*(this + 1950), 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHEN_…
    fld_e32 = (int *)*(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
    result = (int *)*fld_e32;  // fld_e32=this+128 szStatusKeyBuf
    if ( (int *)*fld_e32 != fld_e32 )  // fld_e32=this+128 szStatusKeyBuf
    {
      fld_e1949 = *(this + 1949);  // 读字段 fld_e1949 = this+1949
      do
      {
        if ( result[3] == fld_e1949 )
          *(this + 1951) = (int)(result + 2);  // 写字段 this+1951 ← (int)(result + 2)
        result = (int *)*result;
      }
      while ( result != (int *)*(this + 32) );  // this+128〔szStatusKeyBuf(推断)〕
    }
  }
  else
  {
    v11 = *this;
    fld_e19492 = *(this + 1949);  // 读字段 fld_e19492 = this+1949
    *(this + 1951) = 0;  // 写字段 this+1951 ← 0
    return (int *)(*(int (/*thiscall*/ **)(int *, int))(v11 + 208))(this, fld_e19492);  // 调虚槽 +208：定时器移除
  }
  return result;
}



// ------------------------------------------------------------
// 0x4B9720 sub_4B9720 —— 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/+52 槽；调 sub_4D71B0 命中主处理器【待验证】）
// ------------------------------------------------------------
int /*thiscall*/ sub_4B9720(size_t *this, uint32_t *pArg2, int nArg3, int nArg4)  // sub_4B9720 —— 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/+52 槽；调 sub_4D71B0 命中主处理器【待验证】）
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
  v7 = (*(int (/*thiscall*/ **)(size_t *, int *, uint32_t *))(v6 + 648))(this, &v29, pArg2);  // 调虚槽 +648：写入 100（格挡/减伤基础值槽）
  if ( (*(uint8_t (/*thiscall*/ **)(size_t *))(*this + 308))(this) != 0  // 虚调用 vt+308（this）是否本地玩家
    && (*(uint8_t (/*thiscall*/ **)(size_t *))(*this + 724))(this) == 0 )  // 虚调用 vt+724（this）取值
  {
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 348))(pArg2);  // 虚调用 vt+348（pArg2）渲染数据块指针
    if ( (*(uint8_t *)(v8 + 16) != 0 || *(float *)v8 > 0.0)
      && (uint8_t)nArg4 == 0
      && v29 > 0
      && v7 != 2
      && sub_4AED20((int)this) != 2 )  // 霸体特效（SuperArmorEffect.ani；sub_4920E0 全帧缩放；+40/+52 槽；调 sub_4D71B0 命中主处理器【待验证】）
    {
      for ( i = 0; i < 18; ++i )  // 遍历计次循环（i < 18）
      {
        if ( i != 8 )
          (*(void (/*thiscall*/ **)(size_t *, int))(*this + 1104))(this, i);  // 虚调用 vt+1104（this 虚表槽）
      }
      v10 = *pArg2;
      if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v10 + 40))(pArg2, 529) != 0  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
          || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 576))(pArg2) != 0  // 虚调用 vt+576（pArg2）受击方判定体
          && (pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 576))(pArg2),  // 虚调用 vt+576（pArg2）受击方判定体
              (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0) )  // 虚调用 vt+40（pObj）条件查询(273等)
        {
LABEL_21:
          v13 = (*(int (/*thiscall*/ **)(size_t *))(*this + 52))(this);  // 虚调用 vt+52（this）归属坐标y
          sub_495A70(dword_99FD58, -1, 6, v13);  // sub_495A70 —— 场景对象动画挂接（+1004 门控；v5==4 PVP 分流 aPvp_2 / v5==6 aWarroom，否则普通）
        }
      }
      else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v10 + 40))(pArg2, 273) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      {
        v12 = *(uint32_t *)(dword_8F7A24 + 12);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        if ( v12 == 4 || v12 == 6 )
          goto LABEL_21;
      }
    }
  }
  if ( *((uint8_t *)this + 7992) != 0 )
  {
    v27 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v14 = nullptr;
    v30 = 0;
    if ( v27 != 0 )
      v14 = (uint32_t *)sub_431860((char)"Common/CommonEffect/Animation/SuperArmorEffect.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
    v15 = *this;
    v30 = -1;
    v28 = (double)(*(int (/*thiscall*/ **)(size_t *))(v15 + 192))(this) * 0.0071428572;  // 虚函数调用 槽+192
    sub_4920E0(v14, v28, v28);  // sub_4920E0 —— ★批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
    v16 = (char *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
    v17 = v16;
    v30 = 1;
    if ( v16 != nullptr )
    {
      sub_44E0D0(v16, (int)v14, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)v17 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
    }
    else
    {
      v17 = nullptr;
    }
    fld_e29 = *(this + 29);  // 读字段 fld_e29 = this+29
    v30 = -1;
    sub_45FE80(fld_e29, (int)v17, 2, 0, (int)v17, (int)this, 0);  // sub_45FE80 —— 对象注册
    v19 = *(uint32_t *)v17;
    v20 = (*(int (/*thiscall*/ **)(size_t *))(*this + 152))(this);  // 虚调用 vt+152（this）取值(参数)
    (*(void (/*thiscall*/ **)(char *, int))(v19 + 148))(v17, v20);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
    v21 = *(uint32_t *)v17;
    v22 = (*(int (/*thiscall*/ **)(size_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    v23 = (*(int (/*thiscall*/ **)(size_t *, int))(*this + 124))(this, v22);  // 虚调用 vt+124（this）目标坐标y下界
    v24 = (*(int (/*thiscall*/ **)(size_t *, int))(*this + 120))(this, v23);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(char *, int))(v21 + 112))(v17, v24);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    pArg22 = pArg2;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(size_t *))(*this + 724))(this) == 0 && v29 > 0 && (uint8_t)nArg4 == 0 )  // 虚调用 vt+724（this）取值
  {
    v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 348))(pArg22);  // 虚调用 vt+348（pArg22）渲染数据块指针
    if ( *(uint8_t *)(v25 + 16) != 0 || *(float *)v25 > 0.0 )
      sub_4B2B50(this, pArg22);  // sub_4B2B50 —— 记录目标身份字段（+8008..+8024）
  }
  return sub_4D71B0(this, *(float *)&pArg22, nArg3, nArg4);  // 【命中主处理器 vt+512（§2 全文定案）】
}


// ------------------------------------------------------------
// 0x4B99C0 sub_4B99C0 —— 骰子演出（Dice.ani/DiceGlow.ani；DICE_ROLL/OUT/GET 事件；sub_493D00 变速）
// ------------------------------------------------------------
void */*userpurge*/ sub_4B99C0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, void *pArg3)  // 实现：骰子演出（Dice.ani/DiceGlow.ani；DICE_ROLL/OUT/GET 事件；sub_493D00 变速）
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
    if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
      v5 = (uint32_t *)sub_431860((char)"Common/Etc/Animation/DiceGlow.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
    v28 = v5;
    sub_493D00((int)v5, 20.0);  // sub_493D00 —— ★变速（研究§26）
    sub_4920E0(v5, 0.80000001, 0.80000001);  // sub_4920E0 —— ★批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
    if ( operator new(0x11Cu) != nullptr )  // 堆分配
      pObj = sub_44E0D0(v5, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    else
      pObj = 0;
    Blocka = (void *)pObj;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 72))(pObj, 2);  // 虚调用 vt+72（pObj 虚表槽）
    sub_45FE80(pDwArg1[29], pObj, 2, 0, pObj, (int)pDwArg1, 0);  // sub_45FE80 —— 对象注册
    v7 = *(uint32_t *)pObj;
    v8 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 192))(pDwArg1);  // 虚调用 vt+192（pDwArg1）取尺寸/包围盒
    v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 虚调用 vt+128（pDwArg1）目标坐标y上界
    v10 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, v8 + v9 + 20);  // 虚调用 vt+124（pDwArg1）目标坐标y下界
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v10);  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(void *, int))(v7 + 112))(Blocka, v11);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    (*(void (/*thiscall*/ **)(void *, int *))(*(uint32_t *)Blocka + 60))(Blocka, pDwArg1);  // 虚调用 vt+60（Blocka）对象销毁/释放
    sub_4A06D0(nArg2);  // sub_4A06D0 —— 绑定目标对象并记录相对偏移
    v12 = v28[11];
    if ( v12 != 0 )
      v13 = (v28[12] - v12) / 88;
    else
      v13 = 0;
    v14 = 0;
    for ( Block = (void *)v13; v14 < v13; ++v14 )
    {
      v15 = sub_4924C0(v14);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(uint32_t *)(v15 + 48) = 25;  // 写字段 v15+48（pCmdVecBegin48） ← 25
      *(uint32_t *)(v15 + 32) = -1;  // 写字段 v15+32（nHeight） ← -1
      if ( v14 != 0 )
      {
        switch ( v14 )  // 按 v14 分派
        {
          case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
            *(uint32_t *)(v15 + 16) = -40;  // 写字段 v15+16（nChannelTypeSel） ← -40
            break;
          case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
            *(uint32_t *)(v15 + 16) = -80;  // 写字段 v15+16（nChannelTypeSel） ← -80
            *(uint8_t *)(v15 + 36) = 1;  // 写字段 v15+36（nStateWord36） ← 1
            break;
          case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
            *(uint32_t *)(v15 + 16) = -40;  // 写字段 v15+16（nChannelTypeSel） ← -40
            *(uint8_t *)(v15 + 36) = 1;  // 写字段 v15+36（nStateWord36） ← 1
            break;
          case 4:  // case 4 = ENUM_CMDPACKET_EXIT
            *(uint32_t *)(v15 + 16) = 0;  // 写字段 v15+16（nChannelTypeSel） ← 0
            break;
          case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
            *(uint32_t *)(v15 + 16) = -20;  // 写字段 v15+16（nChannelTypeSel） ← -20
            break;
          case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
            *(uint32_t *)(v15 + 16) = -40;  // 写字段 v15+16（nChannelTypeSel） ← -40
            *(uint8_t *)(v15 + 36) = 1;  // 写字段 v15+36（nStateWord36） ← 1
            break;
          case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
            *(uint32_t *)(v15 + 16) = -20;  // 写字段 v15+16（nChannelTypeSel） ← -20
            *(uint8_t *)(v15 + 36) = 1;  // 写字段 v15+36（nStateWord36） ← 1
            break;
          case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
            *(uint32_t *)(v15 + 16) = 0;  // 写字段 v15+16（nChannelTypeSel） ← 0
            break;
          case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
            *(uint32_t *)(v15 + 16) = 0;  // 写字段 v15+16（nChannelTypeSel） ← 0
            if ( (int *)dword_8F7C04 == pDwArg1 )  // dword_8F7C04（本地玩家对象）
            {
              if ( (uint8_t)pArg3 != 0 )
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DICE_GET", -1, 0, 0);  // 虚调用 vt+212（pDwArg1 虚表槽）
              else
                (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DICE_OUT", -1, 0, 0);  // 虚调用 vt+212（pDwArg1 虚表槽）
            }
            break;
          default:
            break;
        }
      }
      else
      {
        *(uint32_t *)(v15 + 16) = 0;  // 写字段 v15+16（nChannelTypeSel） ← 0
        if ( (int *)dword_8F7C04 == pDwArg1 )  // dword_8F7C04（本地玩家对象）
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "DICE_ROLL", -1, 0, 0);  // 虚调用 vt+212（pDwArg1 虚表槽）
      }
    }
    v16 = sub_42FCB0(228) != 0 ? (uint32_t *)sub_431860((char)"Common/Etc/Animation/Dice.ani", 1) : nullptr;  // sub_42FCB0 —— 结果 = CRT 一次性初始化；sub_431860 —— 动画件构造（资源 id 版）
    sub_493D00((int)v16, 20.0);  // sub_493D00 —— ★变速（研究§26）
    sub_4920E0(v16, 0.80000001, 0.80000001);  // sub_4920E0 —— ★批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
    pMem = operator new(0x11Cu) != nullptr ? sub_44E0D0(v16, 1) : 0;  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    pObj2 = (void *)pMem;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pMem + 72))(pMem, 2);  // 虚调用 vt+72（pMem 虚表槽）
    sub_45FE80(pDwArg1[29], pMem, 2, 0, pMem, (int)pDwArg1, 0);  // sub_45FE80 —— 对象注册
    v18 = *(uint32_t *)pMem;
    v19 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 192))(pDwArg1);  // 虚调用 vt+192（pDwArg1）取尺寸/包围盒
    v24 = v19 + (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1) + 20;  // 虚调用 vt+128（pDwArg1）目标坐标y上界
    v20 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 虚调用 vt+124（pDwArg1）目标坐标y下界
    v21 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v20);  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(void *, int))(v18 + 112))(pObj2, v21);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    (*(void (/*thiscall*/ **)(void *, int *))(*(uint32_t *)pObj2 + 60))(pObj2, pDwArg1);  // 虚调用 vt+60（pObj2）对象销毁/释放
    sub_4A06D0(v24);  // sub_4A06D0 —— 绑定目标对象并记录相对偏移
    result = Block;
    for ( i = 0; i < (int)Block; ++i )
    {
      v23 = sub_4924C0(i);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(uint32_t *)(v23 + 48) = 25;  // 写字段 v23+48（pCmdVecBegin48） ← 25
      *(uint32_t *)(v23 + 32) = -1;  // 写字段 v23+32（nHeight） ← -1
      switch ( i )  // 按 i 分派
      {
        case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          goto LABEL_59;
        case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          *(uint32_t *)(v23 + 16) = -40;  // 写字段 v23+16（nChannelTypeSel） ← -40
          break;
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          *(uint32_t *)(v23 + 16) = -80;  // 写字段 v23+16（nChannelTypeSel） ← -80
          *(uint8_t *)(v23 + 36) = 1;  // 写字段 v23+36（nStateWord36） ← 1
          break;
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          *(uint32_t *)(v23 + 16) = -40;  // 写字段 v23+16（nChannelTypeSel） ← -40
          *(uint8_t *)(v23 + 36) = 1;  // 写字段 v23+36（nStateWord36） ← 1
          break;
        case 4:  // case 4 = ENUM_CMDPACKET_EXIT
          goto LABEL_59;
        case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
          *(uint32_t *)(v23 + 16) = -20;  // 写字段 v23+16（nChannelTypeSel） ← -20
          break;
        case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
          *(uint32_t *)(v23 + 16) = -40;  // 写字段 v23+16（nChannelTypeSel） ← -40
          *(uint8_t *)(v23 + 36) = 1;  // 写字段 v23+36（nStateWord36） ← 1
          break;
        case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
          *(uint32_t *)(v23 + 16) = -20;  // 写字段 v23+16（nChannelTypeSel） ← -20
          *(uint8_t *)(v23 + 36) = 1;  // 写字段 v23+36（nStateWord36） ← 1
          break;
        case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
        case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
LABEL_59:
          *(uint32_t *)(v23 + 16) = 0;  // 写字段 v23+16（nChannelTypeSel） ← 0
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
void /*userpurge*/ sub_4B9DB0(  // sub_4B9DB0 —— GET_GOLD 演出（MoneyUp.img/ExpUp.img → sub_4B59A0 包装 + +48/+40 槽）
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
  v39 = dword_796E50;  // dword_796E50 —— 栈检 cookie
  if ( a1[29] != 0 )
  {
    memset(Buffer, 0, sizeof(Buffer));  // 调 内存按字节填充
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
        sprintf(Buffer, off_6C789C, a4);  // 调 格式化到缓冲
      }
    }
    else
    {
      sub_4015C0("Common/Etc/ExpUp.img", 0x14u);  // 【std::string构造赋值】
      if ( a5 != 0 )
        sprintf(Buffer, "%d+%dE", a4, a5);  // 拼字符串（模板 %d+%dE）
      else
        sprintf(Buffer, "%dE", a4);  // 拼字符串（模板 %dE）
    }
    v11 = strlen(Buffer);  // v11 = 调 strlen
    v12 = 0;
    v13 = (void **)Block[0];
    if ( v38 < 0x10 )
      v13 = Block;
    (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v13);  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
    for ( i = 0; i < v11; ++i )  // 遍历计次循环（i < v11）
    {
      v14 = Buffer[i];
      if ( v14 == 43 )
      {
        v15 = sub_418DD0(11);  // sub_418DD0 —— 资源句柄 (101)
      }
      else if ( v14 == 69 || v14 == 71 )
      {
        v15 = sub_418DD0(10);  // sub_418DD0 —— 资源句柄 (101)
      }
      else
      {
        v15 = sub_418DD0(v14 - 48);  // sub_418DD0 —— 资源句柄 (101)
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
          v17 = sub_418DD0(10);  // sub_418DD0 —— 资源句柄 (101)
        }
        else if ( v16 == 43 )
        {
          v17 = sub_418DD0(11);  // sub_418DD0 —— 资源句柄 (101)
        }
        else
        {
          v17 = sub_418DD0(v16 - 48);  // sub_418DD0 —— 资源句柄 (101)
        }
        v18 = v17;
        v31 = v17;
        v33 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v19 = 0;
        LOBYTE(v40) = 1;
        if ( v33 != 0 )
          v34 = sub_4B59A0(3);  // sub_4B59A0 —— 角色动画包装器复位（+204 子动画链、sub_493BD0 复位 / sub_494610 帧数组重置）
        else
          v34 = 0;
        LOBYTE(v40) = 0;
        do
        {
          v20 = sub_4924C0(v19);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
          *(uint32_t *)v20 = v19 != 0 ? v18 : 0;
          *(uint32_t *)(v20 + 12) = v32;  // 写字段 v20+12（nSkillRec12） ← v32
          if ( v19 != 0 )
          {
            if ( v19 == 1 )
            {
              *(uint32_t *)(v20 + 48) = 300;  // 写字段 v20+48（pCmdVecBegin48） ← 300
              *(uint32_t *)(v20 + 16) = *(uint32_t *)(v18 + 40) / -2;  // 写字段 v20+16（nChannelTypeSel） ← *(uint32_t *)(v18 + 40) / -2
              *(uint8_t *)(v20 + 36) = 1;  // 写字段 v20+36（nStateWord36） ← 1
            }
            else if ( v19 == 2 )
            {
              *(uint32_t *)(v20 + 48) = 600;  // 写字段 v20+48（pCmdVecBegin48） ← 600
              *(uint32_t *)(v20 + 16) = -30 - *(uint32_t *)(v18 + 40) / 2;  // 写字段 v20+16（nChannelTypeSel） ← -30 - *(uint32_t *)(v18 + 40) / 2
            }
          }
          else
          {
            *(uint32_t *)(v20 + 48) = a6;  // 写字段 v20+48（pCmdVecBegin48） ← a6
            *(uint32_t *)(v20 + 16) = *(uint32_t *)(v18 + 40) / -2;  // 写字段 v20+16（nChannelTypeSel） ← *(uint32_t *)(v18 + 40) / -2
          }
          ++v19;  // 计数自增 v19
        }
        while ( v19 < 3 );  // 循环直到 v19 < 3
        v21 = (char *)operator new(0x11Cu);  // 堆分配
        LOBYTE(v40) = 2;
        if ( v21 != nullptr )
          v22 = sub_44E0D0(v21, v34, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        else
          v22 = nullptr;
        v23 = *(uint32_t *)v22;
        LOBYTE(v40) = 0;
        (*(void (/*thiscall*/ **)(char *, int, int))(v23 + 72))(v22, 2, a2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4…
        sub_45FE80(v10[29], v18, 2, 0, (int)v22, (int)v10, 0);  // sub_45FE80 —— 对象注册
        if ( a7 != 0 )
        {
          a2 = a10 + 45;
          (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)v22 + 112))(v22, a8, a9);  // 虚调用 vt+112（v22）坐标三元组写入
        }
        else
        {
          v24 = *(uint32_t *)v22;
          v35 = (*(int (/*thiscall*/ **)(int *))(*v10 + 192))(v10);  // 虚调用 vt+192（v10）取尺寸/包围盒
          v25 = (*(int (/*thiscall*/ **)(int *))(*v10 + 128))(v10);  // 虚调用 vt+128（v10）目标坐标y上界
          v10 = a1;
          a2 = v35 + v25 + 45;
          v28 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1);  // 虚调用 vt+124（a1）目标坐标y下界
          v26 = (*(int (/*thiscall*/ **)(int *))(*v10 + 120))(v10);  // 虚调用 vt+120（v10）转发(对象+缓冲)
          (*(void (/*thiscall*/ **)(char *, int))(v24 + 112))(v22, v26);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
          (*(void (/*thiscall*/ **)(char *, int *))(*(uint32_t *)v22 + 60))(v22, a1);  // 虚调用 vt+60（v22）对象销毁/释放
          sub_4A06D0(v28);  // sub_4A06D0 —— 绑定目标对象并记录相对偏移
          v18 = v31;
        }
        v27 = v42 + 1 < v11;
        v32 += *(uint32_t *)(v18 + 36);
        ++v42;  // 计数自增 v42
      }
      while ( v27 );
    }
    if ( a3 == 0 && (int *)dword_8F7C04 == v10 )  // dword_8F7C04（本地玩家对象）
      sub_432EA0("GET_GOLD", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    if ( v38 >= 0x10 )
      j__free(Block[0]);  // 释放堆块
  }
}


// ------------------------------------------------------------
// 0x4BA130 sub_4BA130 —— FP_UP 演出（Interface/BattleDungeon/battledungeon_result.img；战斗副本结算）
// ------------------------------------------------------------
void /*userpurge*/ sub_4BA130(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, char pszArg5, int nArg6, int nArg7, int nArg8)  // sub_4BA130 —— FP_UP 演出（Interface/BattleDungeon/battledungeon_result.img；战斗副本结算）
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
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v9 = 0;
  if ( pDwArg1[29] != 0 )
  {
    memset(Buffer, 0, sizeof(Buffer));  // 调 内存按字节填充
    v39 = 15;
    Block[4] = nullptr;
    LOBYTE(Block[0]) = 0;
    sub_4015C0(&v37, szPassword, 0);  // 【std::string构造赋值】
    v41 = 0;
    sub_4015C0(&v37, "Interface/BattleDungeon/battledungeon_result.img", 0x30u);  // 【std::string构造赋值】
    sprintf(Buffer, off_6F6564, nArg3);  // 调 格式化到缓冲
    nLen = strlen(Buffer);  // nLen = 调 strlen
    Block2 = (void **)Block[0];
    if ( v39 < 0x10 )
      Block2 = Block;
    v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, Block2);  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
    v31 = v12;
    for ( i = 0; i < nLen; ++i )  // 遍历计次循环（i < nLen）
    {
      v13 = Buffer[i];
      if ( v13 == 102 )
        v9 += *(uint32_t *)(sub_418DD0(v12, 0xCu) + 36);  // sub_418DD0 —— 资源句柄 (101)
      else
        v9 = v9 + *(uint32_t *)(sub_418DD0(v12, v13 - 5) + 36) - 4;  // sub_418DD0 —— 资源句柄 (101)
    }
    v33 = v9 / -2;
    v43 = 0;
    if ( nLen > 0 )
    {
      while ( 1 )
      {
        v14 = Buffer[v43];
        v15 = v14 == 102 ? sub_418DD0(v12, 0xCu) : sub_418DD0(v12, v14 - 5);  // sub_418DD0 —— 资源句柄 (101)；sub_418DD0 —— 资源句柄 (101)
        v16 = v15;
        v32 = v15;
        v17 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v18 = 0;
        LOBYTE(v41) = 1;
        v34 = v17 != 0 ? (int *)sub_4B59A0(v17, 3u) : nullptr;  // sub_4B59A0 —— 角色动画包装器复位（+204 子动画链、sub_493BD0 复位 / sub_494610 帧数组重置）
        LOBYTE(v41) = 0;
        do
        {
          v19 = sub_4924C0(v34, v18);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
          *(uint32_t *)v19 = v18 != 0 ? v16 : 0;
          *(uint32_t *)(v19 + 12) = v33;  // 写字段 v19+12（nSkillRec12） ← v33
          if ( v18 != 0 )
          {
            if ( v18 == 1 )
            {
              *(uint32_t *)(v19 + 48) = 300;  // 写字段 v19+48（pCmdVecBegin48） ← 300
              *(uint32_t *)(v19 + 16) = *(uint32_t *)(v16 + 40) / -2;  // 写字段 v19+16（nChannelTypeSel） ← *(uint32_t *)(v16 + 40) / -2
              *(uint8_t *)(v19 + 36) = 1;  // 写字段 v19+36（nStateWord36） ← 1
            }
            else if ( v18 == 2 )
            {
              *(uint32_t *)(v19 + 48) = 600;  // 写字段 v19+48（pCmdVecBegin48） ← 600
              *(uint32_t *)(v19 + 16) = -50 - *(uint32_t *)(v16 + 40) / 2;  // 写字段 v19+16（nChannelTypeSel） ← -50 - *(uint32_t *)(v16 + 40) / 2
            }
          }
          else
          {
            *(uint32_t *)(v19 + 48) = nArg4;  // 写字段 v19+48（pCmdVecBegin48） ← nArg4
            *(uint32_t *)(v19 + 16) = *(uint32_t *)(v16 + 40) / -2;  // 写字段 v19+16（nChannelTypeSel） ← *(uint32_t *)(v16 + 40) / -2
          }
          ++v18;  // 计数自增 v18
        }
        while ( v18 < 3 );  // 循环直到 v18 < 3
        pMem = (char *)operator new(0x11Cu);  // 堆分配
        LOBYTE(v41) = 2;
        pObj = pMem != nullptr ? sub_44E0D0(pMem, (int)v34, 1) : nullptr;  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        v22 = *(uint32_t *)pObj;
        LOBYTE(v41) = 0;
        (*(void (/*thiscall*/ **)(char *, int, int))(v22 + 72))(pObj, 2, nArg2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4…
        sub_45FE80(pDwArg12[29], v16, 2, 0, (int)pObj, (int)pDwArg12, 0);  // sub_45FE80 —— 对象注册
        if ( pszArg5 != 0 )
        {
          nArg2 = nArg8 + 45;  // 计算 nArg2 = nArg8 + 45
          (*(void (/*thiscall*/ **)(char *, int, int))(*(uint32_t *)pObj + 112))(pObj, nArg6, nArg7);  // 虚调用 vt+112（pObj）坐标三元组写入
        }
        else
        {
          v23 = *(uint32_t *)pObj;
          v35 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 192))(pDwArg12);  // 虚调用 vt+192（pDwArg12）取尺寸/包围盒
          v24 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 128))(pDwArg12);  // 虚调用 vt+128（pDwArg12）目标坐标y上界
          pDwArg12 = pDwArg1;
          nArg2 = v35 + v24 + 45;
          v28 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 虚调用 vt+124（pDwArg1）目标坐标y下界
          v25 = (*(int (/*thiscall*/ **)(int *))(*pDwArg12 + 120))(pDwArg12);  // 虚调用 vt+120（pDwArg12）转发(对象+缓冲)
          (*(void (/*thiscall*/ **)(char *, int))(v23 + 112))(pObj, v25);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
          v26 = (*(int (/*thiscall*/ **)(char *, int *))(*(uint32_t *)pObj + 60))(pObj, pDwArg1);  // 虚调用 vt+60（pObj）对象销毁/释放
          sub_4A06D0(v26, v28);  // sub_4A06D0 —— 绑定目标对象并记录相对偏移
          v16 = v32;
        }
        v27 = v43 + 1 < nLen;
        v33 += *(uint32_t *)(v16 + 36);
        ++v43;  // 计数自增 v43
        if ( !v27 )
          break;
        v12 = v31;
      }
    }
    if ( (int *)dword_8F7C04 == pDwArg12 )  // dword_8F7C04（本地玩家对象）
      sub_432EA0("FP_UP", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    if ( v39 >= 0x10 )
      j__free(Block[0]);  // 释放堆块
  }
}


// ------------------------------------------------------------
// 0x4BA450 sub_4BA450 —— GET_ITEM 演出
// ------------------------------------------------------------
void /*thiscall*/ sub_4BA450(int *this, int nArg2, int nArg3)  // sub_4BA450 —— GET_ITEM 演出
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
  if ( nArg2 != 0 && *(this + 29) != 0 )  // this+29 pSessionCtx
  {
    v6 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    if ( v6 != 0 )
      v17 = (int *)sub_4B59A0(v6, 3u);  // sub_4B59A0 —— 角色动画包装器复位（+204 子动画链、sub_493BD0 复位 / sub_494610 帧数组重置）
    else
      v17 = nullptr;
    v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 16))(nArg2) + 68);  // 虚调用 vt+16（nArg2 虚表槽）
    do
    {
      v8 = sub_4924C0(v17, v4);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(uint32_t *)v8 = v4 != 0 ? v7 : 0;
      *(uint32_t *)(v8 + 12) = *(uint32_t *)(v7 + 36) / -2;  // 写字段 v8+12（nSkillRec12） ← *(uint32_t *)(v7 + 36) / -2
      if ( v4 != 0 )
      {
        if ( v4 == 1 )
        {
          *(uint32_t *)(v8 + 48) = 300;  // 写字段 v8+48（pCmdVecBegin48） ← 300
          *(uint32_t *)(v8 + 16) = *(uint32_t *)(v7 + 40) / -2;  // 写字段 v8+16（nChannelTypeSel） ← *(uint32_t *)(v7 + 40) / -2
          *(uint8_t *)(v8 + 36) = 1;  // 写字段 v8+36（nStateWord36） ← 1
        }
        else if ( v4 == 2 )
        {
          *(uint32_t *)(v8 + 48) = 600;  // 写字段 v8+48（pCmdVecBegin48） ← 600
          *(uint32_t *)(v8 + 16) = -30 - *(uint32_t *)(v7 + 40) / 2;  // 写字段 v8+16（nChannelTypeSel） ← -30 - *(uint32_t *)(v7 + 40) / 2
        }
      }
      else
      {
        *(uint32_t *)(v8 + 48) = nArg3;  // 写字段 v8+48（pCmdVecBegin48） ← nArg3
        *(uint32_t *)(v8 + 16) = *(uint32_t *)(v7 + 40) / -2;  // 写字段 v8+16（nChannelTypeSel） ← *(uint32_t *)(v7 + 40) / -2
      }
      ++v4;  // 计数自增 v4
    }
    while ( v4 < 3 );  // 循环直到 v4 < 3
    pMem = (char *)operator new(0x11Cu);  // 堆分配
    if ( pMem != nullptr )
      pObj = sub_44E0D0(pMem, (int)v17, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    else
      pObj = nullptr;
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 72))(pObj);  // 虚调用 vt+72（pObj 虚表槽）
    sub_45FE80(*(this + 29), v4, 2, 0, (int)pObj, (int)this, 0);  // sub_45FE80 —— 对象注册
    v18 = *(uint32_t *)pObj;
    v11 = (*(int (/*thiscall*/ **)(int *))(*this + 192))(this);  // 虚调用 vt+192（this）取尺寸/包围盒
    v12 = v11 + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + 20;  // 虚调用 vt+128（this）目标坐标y上界
    v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v12);  // 虚调用 vt+124（this）目标坐标y下界
    v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(char *, int))(v18 + 112))(pObj, v14);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
    v15 = (*(int (/*thiscall*/ **)(char *, int *))(*(uint32_t *)pObj + 60))(pObj, this);  // 虚调用 vt+60（pObj）对象销毁/释放
    sub_4A06D0(v15, 2);  // sub_4A06D0 —— 绑定目标对象并记录相对偏移
    if ( (int *)dword_8F7C04 == this && nArg3 == 0 )  // 判定 dword_8F7C04 == this 且 nArg3 == 0
      sub_432EA0("GET_ITEM", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  }
}



// ------------------------------------------------------------
// 0x4BA610 sub_4BA610 —— 魔能充能动画选择（Character/Mage/Effect/Animation/MagicOnCharge%d%d.ani / MagicFullCharge%d%d.ani）
// ------------------------------------------------------------
int /*thiscall*/ sub_4BA610(uint32_t *this, int pArg2)  // sub_4BA610 —— 魔能充能动画选择（Character/Mage/Effect/Animation/MagicOnCharge%d%d.ani / MagicFullCharge%d%d.ani）
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = *(this + 2 * pArg2 + 2033);
  if ( result == 0 )
  {
    v4 = 1;
    pThis_2 = this + 2 * pArg2 + 2043;
    v14 = 2;
    do
    {
      sprintf(Buffer, "Character/Mage/Effect/Animation/MagicOnCharge%d%d.ani", pArg2, v4);  // 拼字符串（模板 Character/Mage/Effect/Animatio…）
      v9 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
      v13 = 0;
      if ( v9 != 0 )
        v6 = sub_431860((char)Buffer, 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v6 = 0;
      v13 = -1;
      *(pThis_2 - 10) = v6;
      sprintf(Buffer, "Character/Mage/Effect/Animation/MagicFullCharge%d%d.ani", pArg2, v4);  // 拼字符串（模板 Character/Mage/Effect/Animatio…）
      v10 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
      v13 = 1;
      if ( v10 != 0 )
        v7 = sub_431860((char)Buffer, 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v7 = 0;
      *pThis_2++ = v7;
      ++v4;  // 计数自增 v4
      result = v14 - 1;
      v8 = v14 == 1;
      v13 = -1;
      --v14;  // 计数自减 v14
    }
    while ( !v8 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BA730 sub_4BA730 —— 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_CHARGE/ENERGY_CHARGE_END）
// ------------------------------------------------------------
int /*thiscall*/ sub_4BA730(uint32_t *this, int nArg2, int pArg3, int nArg4, int nArg5)  // sub_4BA730 —— 魔能充能驱动（+204/+208/+216 槽；sub_493D00 变速；ENERGY_CHARGE/ENERGY_CHARGE_END）
{
  uint32_t *pThis_2; // edi
  int result; // eax
  int *pThis_23; // edi
  int k; // ebx
  int *pThis_22; // edi
  int j; // ebx
  int i; // [esp+Ch] [ebp-4h]

  if ( *(this + 2 * pArg3 + 2033) == 0 )
    sub_4BA610(pArg3);  // sub_4BA610 —— 魔能充能动画选择（Character/Mage/Effect/Animation/MagicOnCharge%d%d.ani / MagicFullCharge%d%d.ani）
  pThis_2 = this + 2 * pArg3 + 2043;
  for ( i = 2; i != 0; --i )  // 遍历计次循环（i != 0）
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(pThis_2 - 10));  // 虚调用 vt+208（this）动画件回挂
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *pThis_2++);  // 虚调用 vt+208（this）动画件回挂
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);  // 虚调用 vt+216（this）全场广播
  result = nArg2;
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
        this,
        1,
        *(this + 2 * pArg3 + 2043),
        nArg4,
        nArg5,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
        this,
        1,
        *(this + 2 * pArg3 + 2044),
        nArg4,
        nArg5,
        0,
        0);
      pThis_22 = this + 2 * pArg3 + 2043;
      for ( j = 2; j != 0; --j )  // 遍历计次循环（j != 0）
        sub_493D00(*pThis_22++, 100.0);  // sub_493D00 —— ★变速（研究§26）
      return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
               this,
               "ENERGY_CHARGE_END",  // 资源/动画 TAG ENERGY_CHARGE_END
               -1,
               0,
               0);
    }
  }
  else
  {
    pThis_23 = this + 2 * pArg3 + 2033;
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int, uint32_t, uint32_t))(*this + 204))(this, 1, *pThis_23, nArg4, nArg5, 0, 0);  // 虚调用 vt+204（this 虚表槽）
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      1,
      *(this + 2 * pArg3 + 2034),
      nArg4,
      nArg5,
      0,
      0);
    for ( k = 2; k != 0; --k )  // 遍历计次循环（k != 0）
      sub_493D00(*pThis_23++, 100.0);  // sub_493D00 —— ★变速（研究§26）
    return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
             this,
             "ENERGY_CHARGE",  // 资源/动画 TAG ENERGY_CHARGE
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
char /*thiscall*/ sub_4BA8A0(uint32_t *this, int ArgList)  // sub_4BA8A0 —— ★角色创建入口
{
  int v2; // edi
  int v4; // eax
  int v6; // [esp+8h] [ebp-4h] BYREF

  v2 = ArgList;
  sub_442D00(&v6, &ArgList);  // sub_442D00 —— 红黑树等键查找（_Find）
  if ( v6 == dword_9B7C40 )
    return off_77F3FC("CHARACTER CREATE FAIL! JOB %d", v2);  // off_77F3FC —— 日志打印（printf 风格）
  v4 = *(uint32_t *)(v6 + 40) < 0x10u ? v6 + 20 : *(uint32_t *)(v6 + 20);
  if ( v4 == 0 )
    return off_77F3FC("CHARACTER CREATE FAIL! JOB %d", v2);  // off_77F3FC —— 日志打印（printf 风格）
  else
    return sub_4B5FD0(this, v4);  // sub_4B5FD0 —— ★.equ 部件记录解析装载
}



// ------------------------------------------------------------
// 0x4BA910 sub_4BA910 —— CNRDEquipment 随从子对象析构（+144/+0 两槽）
//   ·0x4B5A50(this+18) 析构帧对象数组（+144 槽）、·0x4A4940(this+1) 子对象收尾。
// ------------------------------------------------------------
void /*thiscall*/ sub_4BA910(void ***this)  // sub_4BA910 —— CNRDEquipment 随从子对象析构（+144/+0 两槽）
{
  sub_4B5A50(this + 18);  // sub_4B5A50 —— 帧对象数组析构（·0x42AF90 后 228 字节池回收）
  sub_4A4940((int)(this + 1));  // 调 析构 —— ·0x4EF9D0 按动画行数对齐 +1288 行向量
}



// ------------------------------------------------------------
// 0x4BA960 sub_4BA960 —— ·0x4BA910 区间逐条调用（步长 31）
//   对 [uArg1, uArg2) 步长 31 逐条 ·0x4BA910。【推断：248 字节记录数组析构】
// ------------------------------------------------------------
void /*stdcall*/ sub_4BA960(void ***uArg1, void ***uArg2)  // sub_4BA960 —— 0x4BA910 区间逐条调用（步长 31）
{
  void ***i; // esi

  for ( i = uArg1; i != uArg2; i += 31 )
    sub_4BA910(i);  // sub_4BA910 —— CNRDEquipment 随从子对象析构（+144/+0 两槽）
}



// ------------------------------------------------------------
// 0x4BA990 sub_4BA990 —— 248 字节记录 vector 清空析构
//   [this+4, this+8) 步长 31 逐条 ·0x4BA910，再 free 首址并清 +4/+8/+12。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BA990(int this)  // sub_4BA990 —— 248 字节记录 vector 清空析构
{
  void ***fld_4; // esi
  int result; // eax
  void ***i; // edi

  fld_4 = *(void ****)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  result = 0;
  if ( fld_4 != nullptr )  // fld_4=this+16 nChannelTypeSel
  {
    for ( i = *(void ****)(this + 8); fld_4 != i; fld_4 += 31 )  // this+32〔nHeight(推断)〕
      sub_4BA910(fld_4);  // sub_4BA910 —— CNRDEquipment 随从子对象析构（+144/+0 两槽）
    j__free(*(void **)(this + 4));  // 释放堆块
    result = 0;
  }
  *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *(uint32_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  return result;
}



// ------------------------------------------------------------
// 0x4BA9E0 sub_4BA9E0 —— CNRDEquipment 构造（.equ 外观对象公共工厂）
//   ·0x485CC0 基构造后写 CNRDEquipment vftable；this+148 经 ·0x4B3BE0（clong 组合）、
//   this+212 经 ·0x437E70、this+1160 经 ·0x4E9A50（60 字节包体容器）；+1224..1332 铺
//   off_6C2B88 + 十二零 + 1/0/0 内嵌槽，idx318 经 ·0x41BFE0(this+1272, szPassword) 赋串；
//   末 ·0x4E9D70(this) + ·0x4EE580(Block, nArg3, -1, -1) 装载 .equ。与 ·0x5D7E60 同构。
// ------------------------------------------------------------
char */*thiscall*/ sub_4BA9E0(char *this, void *Block, int nArg3)  // sub_4BA9E0 —— 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
{
  sub_485CC0();  // sub_485CC0 —— IRDItem 核心构造（+132 转 clong 子对象）
  *(uint32_t *)this = &CNRDEquipment::`vftable';  // 构造装配 vftable：CNRDEquipment
  sub_4B3BE0(this + 148);  // sub_4B3BE0 —— clong 组合初始化
  sub_437E70(this + 212);  // sub_437E70 —— 配置对象构造（clong/cfloat）
  sub_4E9A50(this + 1160);  // sub_4E9A50 —— 四内联 clong 构造 + 初值（0/0/-1/0）
  *(this + 1224) = 0;  // 写字段 this+1224（field_04C8） ← 0
  *((uint32_t *)this + 305) = &off_6C2B88;  // 写字段 this[305]（宽4字节）
  *((uint32_t *)this + 307) = 0;  // 写字段 this[307]（宽4字节）
  *(this + 1232) = 1;  // 写字段 this+1232（pNameTagCtrl） ← 1
  *(this + 1234) = 0;  // 写字段 this+1234 ← 0
  *(this + 1233) = 0;  // 写字段 this+1233 ← 0
  *((uint32_t *)this + 311) = 0;  // 写字段 this[311]（宽4字节）
  *((uint32_t *)this + 310) = 0;  // 写字段 this[310]（宽4字节）
  *((uint32_t *)this + 309) = 0;  // 写字段 this[309]（宽4字节）
  *((uint32_t *)this + 314) = 0;  // 写字段 this[314]（宽4字节）
  *((uint32_t *)this + 315) = 0;  // 写字段 this[315]（宽4字节）
  *((uint32_t *)this + 316) = 0;  // 写字段 this[316]（宽4字节）
  *((uint32_t *)this + 318) = 0;  // 写字段 this[318]（宽4字节）
  sub_41BFE0(szPassword);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  *((uint32_t *)this + 323) = 0;  // 写字段 this[323]（宽4字节）
  *((uint32_t *)this + 324) = 0;  // 写字段 this+324（nAnchor324）
  *((uint32_t *)this + 325) = 0;  // 写字段 this[325]（宽4字节）
  *((uint32_t *)this + 327) = 0;  // 写字段 this[327]（宽4字节）
  *((uint32_t *)this + 328) = 0;  // 写字段 this[328]（宽4字节）
  *((uint32_t *)this + 329) = 0;  // 写字段 this[329]（宽4字节）
  sub_4E9D70(this);  // sub_4E9D70 —— 对象字段复位（属性/名字/标志组）
  sub_4EE580(Block, nArg3, -1, -1);  // sub_4EE580 —— ★ 物品实例生成（按文件名）
  return this;
}



// ------------------------------------------------------------
// 0x4BAB00 sub_4BAB00 —— 槽位计时器启动（记录起始值与到期毫秒）
//   以 *(this+37)（下标，148 字节处）为槽：起始值 nArg2 写 dword_9B08E8[2*idx]，
//   到期值 nArg2 + ·0x699000(unk_9B0C70 全局时钟) 写 dword_9B08EC[2*idx]。
//   配套读取见 ·0x4BAB40/·0x4BAB50。【推断：技能/装备冷却计时】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAB00(uint32_t *this, int nArg2)  // sub_4BAB00 —— 槽位计时器启动（记录起始值与到期毫秒）
{
  int result; // eax

  dword_9B08E8[2 * *(this + 37)] = nArg2;  // this+148〔fAdd148(推断)〕
  result = nArg2 + sub_699000((int)&unk_9B0C70);  // 【clock_now(clk)】
  dword_9B08EC[2 * *(this + 37)] = result;  // this+148〔fAdd148(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x4BAB40 sub_4BAB40 —— 槽位计时起始值读取（dword_9B08E8）
//   与 ·0x4BAB00 写入配对：返回该槽记录的起始毫秒。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAB40(uint32_t *this)  // sub_4BAB40 —— 槽位计时起始值读取（dword_9B08E8）
{
  return dword_9B08E8[2 * *(this + 37)];  // 返回 取 dword_9B08E8[2 * *(this + 37)]
}



// ------------------------------------------------------------
// 0x4BAB50 sub_4BAB50 —— 槽位计时到期值读取（dword_9B08EC）
//   与 ·0x4BAB00 写入配对：返回 起始值 + ·0x699000 时钟 的到期毫秒。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAB50(uint32_t *this)  // sub_4BAB50 —— 槽位计时到期值读取（dword_9B08EC）
{
  return dword_9B08EC[2 * *(this + 37)];  // 返回 取 dword_9B08EC[2 * *(this + 37)]
}



// ------------------------------------------------------------
// 0x4BAB60 sub_4BAB60 —— 缩放系数应用（+1344 float）
//   *pArg5 *= *(this+336)。nArg2..nArg4 未用；设值侧见 ·0x4BAB80。
//   【推断：装备外观缩放百分比】
// ------------------------------------------------------------
float */*thiscall*/ sub_4BAB60(float *this, int nArg2, int nArg3, int nArg4, float *pArg5)  // sub_4BAB60 —— 缩放系数应用（+1344 float）
{
  *pArg5 = *(this + 336) * *pArg5;
  return pArg5;
}



// ------------------------------------------------------------
// 0x4BAB80 sub_4BAB80 —— 缩放系数设置（+1344 float）
//   写 *(this+336) = nArg2（整型入参按位型存 f32），读取侧见 ·0x4BAB60。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAB80(uint32_t *this, int nArg2)  // sub_4BAB80 —— 缩放系数设置（+1344 float）
{
  *(this + 336) = nArg2;  // 写字段 this+336 ← nArg2
  return nArg2;
}



// ------------------------------------------------------------
// 0x4BAB90 ?GetLocation@VirtualProcessor@details@Concurrency@@QBEABVlocation@3@XZ
// ------------------------------------------------------------
const struct Concurrency::location */*thiscall*/ Concurrency::details::VirtualProcessor::GetLocation(
        Concurrency::details::VirtualProcessor *this)
{
  return (Concurrency::details::VirtualProcessor *)((char *)this + 148);  // this+148〔fAdd148(推断)〕
}



// ------------------------------------------------------------
// 0x4BABA0 sub_4BABA0 —— 子对象引用（this+212 槽）
//   返回 this+212：·0x437E70 构造的 CNRDEquipment 配置子结构（创建时装配）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4BABA0(char *this)  // sub_4BABA0 —— 子对象引用（this+212 槽）
{
  return this + 212;  // 返回内嵌子对象/缓冲指针（this+212）
}



// ------------------------------------------------------------
// 0x4BABB0 sub_4BABB0 —— 子对象引用（this+1160 槽）
//   返回 this+1160：·0x4E9A50 构造的 60 字节包体容器（装备 PO 使用包载荷）。
// ------------------------------------------------------------
char */*thiscall*/ sub_4BABB0(char *this)  // sub_4BABB0 —— 子对象引用（this+1160 槽）
{
  return this + 1160;  // 返回内嵌子对象/缓冲指针（this+1160）
}



// ------------------------------------------------------------
// 0x4BABC0 sub_4BABC0 —— 技能/动画序号归位（this+1192 计数减 1 后 vt+192 应用）
//   读 ·0x41A5E0(this+1192)（防篡改读取）减 1，经 vt+192 写回应用。
//   【推断：技能序号或动画帧索引】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BABC0(void *this)  // sub_4BABC0 —— 技能/动画序号归位（this+1192 计数减 1 后 vt+192 应用）
{
  int pThis_4A8; // eax

  pThis_4A8 = sub_41A5E0((unsigned int)this + 1192);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 192))(this, pThis_4A8 - 1);  // 虚调用 vt+192（this）取尺寸/包围盒
}



// ------------------------------------------------------------
// 0x4BABE0 sub_4BABE0 —— 状态查询（this+166 非零且 this+1192 为零）
//   返回 ·0x41A5E0(this+166) != 0 && ·0x41A5E0(this+1192) == 0。
//   【推断：就绪且无待处理序号】
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4BABE0(void *this)  // sub_4BABE0 —— 状态查询（this+166 非零且 this+1192 为零）
{
  return sub_41A5E0((unsigned int)this + 166) != 0 && sub_41A5E0((unsigned int)this + 1192) == 0;  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）；sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4BAC10 sub_4BAC10 —— 剩余秒数（上限与 +1220 处 CNTimer 相减）
//   *(this+290)（毫秒上限）与 ·0x699000(this+305*4，即 +1220 nengine::CNTimer 基址) 相减，
//   已过期返回 0。【推断：装备 PO 冷却/维持剩余】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAC10(uint32_t *this)  // sub_4BAC10 —— 剩余秒数（上限与 +1220 处 CNTimer 相减）
{
  int pThis_131; // edi

  pThis_131 = (int)(this + 305);  // this+1220〔pLvTagCtrl(推断)〕
  if ( *(this + 290) <= (unsigned int)(sub_699000((int)(this + 305)) / 1000) )  // 【clock_now(clk)】
    return 0;
  else
    return *(this + 290) - sub_699000(pThis_131) / 1000;  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x4BAC70 sub_4BAC70 —— 计数写入（+1284；归零时清 +1276 标志）
//   写 *(this+1284) = nArg2；nArg2 == 0 时同时置 *(this+1276) = 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAC70(int this, int nArg2)  // sub_4BAC70 —— 计数写入（+1284；归零时清 +1276 标志）
{
  int result; // eax

  result = nArg2;
  *(uint32_t *)(this + 1284) = nArg2;  // 写字段 this+1284（nEffectCount1284） ← nArg2
  if ( nArg2 == 0 )
    *(uint8_t *)(this + 1276) = 0;  // 写字段 this+1276（bEffectArmed1276） ← 0
  return result;
}



// ------------------------------------------------------------
// 0x4BACA0 sub_4BACA0 —— 标志写（+1276）
//   设 *(this+1276) = pszArg2 并返回。【推断：可见/启用标志】
// ------------------------------------------------------------
char /*thiscall*/ sub_4BACA0(uint8_t *this, char pszArg2)  // sub_4BACA0 —— 标志写（+1276）
{
  *(this + 1276) = pszArg2;  // 写字段 this+1276（bEffectArmed1276） ← pszArg2
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4BACD0 sub_4BACD0 —— 字符串槽取值（idx318 = this+1272 → ·0x41ACF0）
//   idx318 串槽经 ·0x41ACF0 取值：构造侧由 ·0x41BFE0(this+1272, szPassword) 赋初值。
//   【推断：.equ 口令/名称串】
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_4BACD0(unsigned int **this)  // sub_4BACD0 —— 字符串槽取值（idx318 = this+1272 → ·0x41ACF0）
{
  return sub_41ACF0(this + 318);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
}



// ------------------------------------------------------------
// 0x4BACE0 sub_4BACE0 —— 哨兵判断（this+1280 != -1）
//   返回 *(this+320) != -1；该两槽在构造时声明为 -1（0xFFFFFFFF）作未设置哨兵。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4BACE0(uint32_t *this)  // sub_4BACE0 —— 哨兵判断（this+1280 != -1）
{
  return *(this + 320) != -1;
}



// ------------------------------------------------------------
// 0x4BAD10 sub_4BAD10 —— 标志写（this+1320 处 idx330 字节）
//   设 *(this+1320) = pszArg2 并返回。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BAD10(uint8_t *this, char pszArg2)  // sub_4BAD10 —— 标志写（this+1320 处 idx330 字节）
{
  *(this + 1320) = pszArg2;  // 写字段 this+1320（bAnimBuilt1320） ← pszArg2
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4BAD40 sub_4BAD40 —— 容器非空判断（this+313*4 = +1252）
//   返回 ·0x41C5A0(this+1252) != 0；该容器构造于 ·0x4BA9E0 尾段 ·0x4EE580。
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_4BAD40(uint32_t *this)  // sub_4BAD40 —— 容器非空判断（this+313*4 = +1252）
{
  return sub_41C5A0(this + 313) != 0;  // sub_41C5A0 —— 结果 = vector<T 4B> 大小查询（空返回 0）
}



// ------------------------------------------------------------
// 0x4BAD60 sub_4BAD60 —— 元素取值（this+1308 表，越界返回 0）
//   *(this+327) 表首、*(this+328) 尾：下标 uArg2 越界（按 >>2 长度判定）返回 0，
//   否则返回 *(表首 + 4*uArg2)。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BAD60(uint32_t *this, unsigned int uArg2)  // sub_4BAD60 —— 元素取值（this+1308 表，越界返回 0）
{
  int fld_e327; // edx  | +0x051C → 动画行向量 begin（CNRDEquipment；va=004EF9D0）

  fld_e327 = *(this + 327);  // 读字段 fld_e327 = this+327
  if ( fld_e327 != 0 && (*(this + 328) - fld_e327) >> 2 > uArg2 )  // fld_e327=this+1308 pRowVec1308
    return *(uint32_t *)(*(this + 327) + 4 * uArg2);  // this+1308〔pRowVec1308〕
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4BADA0 sub_4BADA0 —— 标量删除析构（·0x4BADD0 后按标志位 1 释放）
//   转发 ·0x4BADD0（完整析构），pszArg2 位 0 置位时 j__free(Block)。
// ------------------------------------------------------------
void */*thiscall*/ sub_4BADA0(void *Block, char pszArg2)  // sub_4BADA0 —— 标量删除析构（·0x4BADD0 后按标志位 1 释放）
{
  sub_4BADD0();  // sub_4BADD0 —— CNRDEquipment 析构（.equ 外观对象）
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4BADD0 sub_4BADD0 —— CNRDEquipment 析构（.equ 外观对象）
//   重写 vftable → ·0x4EF270 释放 +1268 对象与 +1308 向量 → free +1308 表 →
//   ·0x4BA990(this+1288) 清 248 字节记录数组 → ·0x41B010(this+1272 串) → free +1256 表 →
//   +1220 复位 IObject vftable → ·0x445150(+1160 包体容器) → ·0x4382D0(+212 配置) →
//   ·0x4B3270(+148 clong 组合) → ·0x485920 基类（IRDItem 链）。与构造 ·0x4BA9E0 严格对称。
// ------------------------------------------------------------
void /*thiscall*/ sub_4BADD0(int this)  // sub_4BADD0 —— CNRDEquipment 析构（.equ 外观对象）
{
  *(uint32_t *)this = &CNRDEquipment::`vftable';  // 构造装配 vftable：CNRDEquipment
  sub_4EF270();  // sub_4EF270 —— 实例清理
  if ( *(uint32_t *)(this + 1308) != 0 )  // this+1308〔pRowVec1308〕
    j__free(*(void **)(this + 1308));  // 释放堆块
  *(uint32_t *)(this + 1308) = 0;  // 写字段 this+1308（pRowVec1308） ← 0
  *(uint32_t *)(this + 1312) = 0;  // 写字段 this+1312（pRowVec1312） ← 0
  *(uint32_t *)(this + 1316) = 0;  // 写字段 this+1316（pRowVec1316） ← 0
  sub_4BA990(this + 1288);  // sub_4BA990 —— 248 字节记录 vector 清空析构
  sub_41B010((void **)(this + 1272));  // sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
  if ( *(uint32_t *)(this + 1256) != 0 )  // this+1256〔pCondVec1256〕
    j__free(*(void **)(this + 1256));  // 释放堆块
  *(uint32_t *)(this + 1256) = 0;  // 写字段 this+1256（pCondVec1256） ← 0
  *(uint32_t *)(this + 1260) = 0;  // 写字段 this+1260（pCondVec1260） ← 0
  *(uint32_t *)(this + 1264) = 0;  // 写字段 this+1264 ← 0
  *(uint32_t *)(this + 1220) = &nengine::IObject::`vftable';  // 写字段 this+1220（pLvTagCtrl） ← &nengine::IObject::`vftable
  *(uint8_t *)(this + 1224) = 0;  // 写字段 this+1224（field_04C8） ← 0
  sub_445150(this + 1160);  // sub_445150 —— 装备同步资源清理
  sub_4382D0(this + 212);  // sub_4382D0 —— 配置对象析构
  sub_4B3270((uint32_t *)(this + 148));  // sub_4B3270 —— clong 组合析构
  sub_485920((uint32_t *)this);  // sub_485920 —— IRDItem 析构（删除器与子类共用）
}



// ============================================================
// §O 0x4BAED0-0x4BC900  部件路径/名称解析（sub_4BC700 路径→id）
// ============================================================
// ------------------------------------------------------------
// 0x4BAED0 sub_4BAED0 —— 角色组装（+248/+256 槽；.equ 子块 → sub_4B50F0 职业特效、sub_4B0080 路径、sub_4BA9E0 生命周期）
// ------------------------------------------------------------
char /*thiscall*/ sub_4BAED0(char *this, int nArg2, void *Block)  // sub_4BAED0 —— 角色组装（+248/+256 槽；.equ 子块 → sub_4B50F0 职业特效、sub_4B0080 路径、sub_4BA9E0 生命周期）
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

  pThis_6FC = *((uint32_t *)this + 1788);  // 读字段 pThis_6FC = this[1788]
  if ( pThis_6FC != nArg2 )  // pThis_6FC=this+7152 uChar7152
    goto LABEL_4;
  if ( *(this + 7156) == (uint8_t)Block )  // this+7156 状态扩展字节
    return pThis_6FC;  // pThis_6FC=this+7152 uChar7152
  if ( pThis_6FC != nArg2 )  // pThis_6FC=this+7152 uChar7152
  {
LABEL_4:
    pThis_6FB = sub_4CE8A0(*((uint32_t *)this + 1787));  // sub_4CE8A0 —— 调用 sub_4CE8A0
    if ( pThis_6FB == 0 )
    {
      LOBYTE(pThis_6FC) = off_77F3FC(aCriticalError_11, *((uint32_t *)this + 1787));  // off_77F3FC —— 日志打印（printf 风格）
      return pThis_6FC;  // pThis_6FC=this+7152 uChar7152
    }
    if ( *((int *)this + 1788) > 0 )  // this+7152〔nParam2(推断)〕
    {
      for ( i = 0; ; ++i )
      {
        pThis_6FC2 = 16 * *((uint32_t *)this + 1788) + pThis_6FB;
        v8 = *(uint32_t *)(pThis_6FC2 + 744);  // 读字段 v8 = pThis_6FC2+744
        if ( v8 == 0 || i >= (*(uint32_t *)(pThis_6FC2 + 748) - v8) >> 2 )
          break;
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 460))(  // 虚调用 vt+460（this 虚表槽）
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
        v11 = *(uint32_t *)(v10 + 744);  // 读字段 v11 = v10+744
        if ( v11 == 0 || v9 >= (*(uint32_t *)(v10 + 748) - v11) >> 2 )
          break;
        (*(void (/*thiscall*/ **)(char *, uint32_t, int))(*(uint32_t *)this + 456))(this, *(uint32_t *)(v11 + 4 * v9++), 1);  // 虚调用 vt+456（this 虚表槽）
      }
    }
  }
  if ( *(this + 7156) != 0 )  // this+7156 状态扩展字节
  {
    pThis_76A = *((void (/*thiscall*/ ****)(uint32_t, int))this + 1898);
    if ( pThis_76A != nullptr )
      (**pThis_76A)(pThis_76A, 1);  // 调 pThis_76A 的虚函数（vt+0）
    pThis_769 = *((uint32_t *)this + 1897);  // 读字段 pThis_769 = this[1897]
    *((uint32_t *)this + 1898) = 0;  // 写字段 this[1898]（宽4字节）
    if ( pThis_769 != 0 )  // pThis_769=this+7588 形态槽（0x5B7D60/0x5B3420 置 …
    {
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_769 + 248))(pThis_769);  // 虚调用 vt+248（pThis_769 虚表槽）
      for ( j = *(uint32_t *)(v14 + 4); j != *(uint32_t *)(v14 + 8); j += 124 )  // 读字段 j = v14+4（pHostObj）
      {
        (*(void (/*thiscall*/ **)(char *, char *, int))(*(uint32_t *)this + 696))(this, this + 6160, j + 4);  // 虚调用 vt+696（this 虚表槽）
        (*(void (/*thiscall*/ **)(char *, char *, int))(*(uint32_t *)this + 1076))(this, this + 7212, j + 72);  // 虚调用 vt+1076（this 虚表槽）
      }
      pThis_7692 = *((uint32_t *)this + 1897);  // 读字段 pThis_7692 = this[1897]
      if ( pThis_7692 != 0 )  // pThis_7692=this+7588 形态槽（0x5B7D60/0x5B3420 置 …
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_7692 + 4))(pThis_7692, 1);  // 虚调用 vt+4（pThis_7692）对象赋值/迁移
      *((uint32_t *)this + 1897) = 0;  // 写字段 this[1897]（宽4字节）
    }
  }
  LOBYTE(pThis_6FC) = (uint8_t)Block;  // pThis_6FC=this+7152 uChar7152
  *((uint32_t *)this + 1788) = nArg2;  // 写字段 this[1788]（宽4字节）
  *(this + 7156) = (char)Block;  // 写字段 this+7156（bParam3） ← (char)Block
  if ( (uint8_t)Block != 0 )
  {
    pThis_76B = sub_4B50F0(  // sub_4B50F0 —— 职业代表特效粒子表（格斗 NenMaster / 漫游 Ranger / 元素 ElementalMaster / 鬼泣 SoulBringer .ptl）
            (uint32_t *)this + 1899,
            (uint32_t *)this + 1900,
            (uint32_t *)this + 1901,
            this + 7608,
            *((void **)this + 1787),  // this+1787〔bBehaviorWord〕
            nArg2,
            (int)this);
    pThis_6FB2 = *((uint32_t *)this + 1787);  // 读字段 pThis_6FB2 = this+1787（bBehaviorWord）
    *((uint32_t *)this + 1898) = pThis_76B;  // 写字段 this[1898]（宽4字节）
    pThis_6FC = sub_4B0080(pThis_6FB2, nArg2);  // sub_4B0080 —— ★职业/转职 → .equ 路径表（输出 byte_9A0468）
    v18 = (void *)pThis_6FC;  // pThis_6FC=this+7152 uChar7152
    if ( pThis_6FC != 0 )  // pThis_6FC=this+7152 uChar7152
    {
      pMem = (char *)operator new(0x544u);  // 堆分配
      if ( pMem != nullptr )
        pObj = sub_4BA9E0(pMem, v18, 0);  // sub_4BA9E0 —— 结果 = CNRDEquipment 构造（.equ 外观对象公共工厂）
      else
        pObj = nullptr;
      *((uint32_t *)this + 1897) = pObj;  // 写字段 this[1897]（宽4字节）
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 256))(pObj);  // 虚调用 vt+256（pObj 虚表槽）
      pThis_6FC = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 1897) + 248))(*((uint32_t *)this + 1897));  // this+7588〔uForm7588〕
      v21 = *(uint32_t **)(pThis_6FC + 4);  // pThis_6FC+4〔宿主对象〕
      Blocka = (uint32_t *)pThis_6FC;  // pThis_6FC=this+7588 uForm7588
      if ( v21 != *(uint32_t **)(pThis_6FC + 8) )  // pThis_6FC+8〔nSkillRec8(推断)〕
      {
        v22 = v21 + 18;  // 计算 v22 = v21 + 18
        do
        {
          sub_4B1C80(this + 6160, v22 - 17, this + 7212, v22);  // sub_4B1C80 —— 部位参数组下发（+40/+44/+56 → sub_4B0DF0 重载动画）
          (*(void (/*thiscall*/ **)(char *, uint32_t, char *, uint32_t *))(*(uint32_t *)this + 692))(  // 虚调用 vt+692（this 虚表槽）
            this,
            *v21,
            this + 6160,
            v22 - 17);
          (*(void (/*thiscall*/ **)(char *, uint32_t, char *, uint32_t *))(*(uint32_t *)this + 1072))(  // 虚调用 vt+1072（this 虚表槽）
            this,
            *v21,
            this + 7212,
            v22);
          pThis_6FC = Blocka[2];  // pThis_6FC=this+7588 uForm7588
          v21 += 31;
          v22 += 31;
        }
        while ( v21 != (uint32_t *)pThis_6FC );  // pThis_6FC=this+7588 uForm7588
      }
    }
  }
  return pThis_6FC;  // pThis_6FC=this+7588 uForm7588
}


// ------------------------------------------------------------
// 0x4BB1A0 sub_4BB1A0 —— 虚表位 0 释放 + 参数 1（对象删除转发）
//   非空则 (**uArg1)(uArg1, 1)。【推断：map 值对象的释放包装】
// ------------------------------------------------------------
int /*stdcall*/ sub_4BB1A0(int (/*thiscall*/ ***uArg1)(uint32_t, int))  // sub_4BB1A0 —— 虚表位 0 释放 + 参数 1（对象删除转发）
{
  int result; // eax

  if ( uArg1 != nullptr )
    return (**uArg1)(uArg1, 1);  // 调 uArg1 的虚函数（vt+0）
  return result;
}



// ------------------------------------------------------------
// 0x4BB1C0 sub_4BB1C0 —— RB 树节点递归释放（节点 +21 为红黑/非空判据）
//   先递归右子树（i[2]），再沿 *i 走左链，逐节点 j__free；空判据 +21 字节。
// ------------------------------------------------------------
char /*stdcall*/ sub_4BB1C0(void **Block)  // sub_4BB1C0 —— RB 树节点递归释放（节点 +21 为红黑/非空判据）
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);  // 读字段 result = Block+21（bArmorState）
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4BB1C0(i[2]);  // sub_4BB1C0 —— RB 树节点递归释放（节点 +21 为红黑/非空判据）
    i = (void **)*i;
    j__free(Block2);  // 释放堆块
    result = *((uint8_t *)i + 21);  // 读字段 result = i+21（bArmorState）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BB200 sub_4BB200 —— 28 字节记录串取值（this+344 表，越界返回 0）
//   *(this+86) 表首/尾：下标 uArg2 越界返回 0；命中取记录 +4 串槽（+24 < 16 判 SSO，
//   仓内 +4 或堆指针）。【推断：部件/装备名表】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BB200(uint32_t *this, unsigned int uArg2)  // sub_4BB200 —— 28 字节记录串取值（this+344 表，越界返回 0）
{
  int fld_e86; // eax
  int fld_e862; // edx

  fld_e86 = *(this + 86);  // 读字段 fld_e86 = this+86
  if ( fld_e86 == 0 || (*(this + 87) - fld_e86) / 28 <= uArg2 )  // fld_e86=this+344 预约重连延迟 ms
    return 0;
  fld_e862 = *(this + 86) + 28 * uArg2;  // this+344〔nReservedDelay〕
  if ( *(uint32_t *)(fld_e862 + 24) < 0x10u )  // fld_e862=this+344 nReservedDelay
    return fld_e862 + 4;  // 返回内嵌子对象/缓冲指针（fld_e862+4）
  else
    return *(uint32_t *)(fld_e862 + 4);  // 返回字段 fld_e862+4（pHostObj）
}



// ------------------------------------------------------------
// 0x4BB260 sub_4BB260 —— 部件名表按资源 id 查找（命中回写名称与下标）
//   遍历 *(this+68) 处 map（RB 中序，+45 空判据）：每条目取 *(v5[10]) 处子表，下标
//   0..(v6[14]-v6[13])/12 经 ·0x418DD0(资源句柄) 与 nArg4 比对；命中 strcpy 名称到
//   pszArg2、下标写 *pDwArg3 并返回；未命中 pszArg2 置空。【推断：nArg4 = 资源/图像 id】
// ------------------------------------------------------------
char /*thiscall*/ sub_4BB260(uint32_t *this, char *pszArg2, unsigned int *pDwArg3, int nArg4)  // sub_4BB260 —— 部件名表按资源 id 查找（命中回写名称与下标）
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

  fld_e68 = (uint32_t *)*(this + 68);  // this+68 角色数
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
        if ( sub_418DD0(v6, i) == nArg4 )  // sub_418DD0 —— 资源句柄 (101)
        {
          if ( v5[9] < 0x10u )
            psz = (const char *)(v5 + 4);
          else
            psz = (const char *)v5[4];
          strcpy(pszArg2, psz);  // 调 串拷贝
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
    while ( v5 != (uint32_t *)*(this + 68) );  // this+68 角色数
  }
  *pszArg2 = 0;
  return (char)pszArg2;
}



// ------------------------------------------------------------
// 0x4BB350 sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
//   节点数 ≥ 0x1FFFFFFE 经 ·0x4015C0(std::string) + ·0x401740 抛 length_error
//   （map/set<T> too long）。·0x5648C0 分配节点，按 pszArg3 接在 pArg4 左/右；
//   再自下向上修红黑（·0x433130 左旋 / ·0x4296E0 摘除重连），根着黑，*uArg2 回写新节点。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BB350(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
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

  if ( *(this + 2) >= 0x1FFFFFFEu )  // this+8〔nSkillRec8(推断)〕
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);  // sub_5648C0 —— 商店文本（23 行）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( pArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    *(uint32_t *)*(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == (uint32_t *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
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
            sub_433130(*v10);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_4296E0 —— STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_433130 —— 红黑树左旋（节点 0x18 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;  // 写字段 v14+20（nPage） ← 1
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
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;  // this+4〔宿主对象〕
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4BB500 sub_4BB500 —— RB 树节点删除 + 重平衡（map/set erase）
//   迭代器空判据 +21 时经 ·0x4015C0/·0x401740（invalid map/set<T> iterator）抛 out_of_range。
//   ·0x41C5E0 求后继，双子/单子/叶三路摘除（·0x52E300 极值辅助、·0x542490 展示子窗口
//   辅助），再按节点头色循环再平衡（·0x433130 左旋 / ·0x4296E0 摘连），末节点数 -1 并 free。
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4BB500(uint32_t *this, int ***uArg2, int **pDwArg3)  // sub_4BB500 —— RB 树节点删除 + 重平衡（map/set erase）
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
    sub_401740(v20);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject = &std::out_of_range::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
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
      *(uint32_t *)(v8 + 4) = v4;  // 写字段 v8+4（pHostObj） ← v4
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
        v9 = (int *)sub_52E300(v4);  // sub_52E300 —— v9 = sub_52E300(v4) 最左
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;  // 写字段 v10+8（nSkillRec8） ← = (uint32_t)pDwArg32
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;  // 写字段 v10+8（nSkillRec8） ← v6
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);  // sub_542490 —— 表头+8 = sub_542490(v4) 最右
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
    *(uint32_t *)(v12 + 4) = v5;  // 写字段 v12+4（pHostObj） ← v5
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
  v14 = *((uint8_t *)v5 + 20);  // 读字段 v14 = v5+20（nPage）
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);  // 写字段 v5+20（nPage）
  *((uint8_t *)pDwArg32 + 20) = v14;  // 写字段 pDwArg32+20（nPage）
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
            *((uint8_t *)v16 + 20) = 1;  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 0;  // 写字段 v6+20（nPage）
            sub_433130(v6);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
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
              *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
              sub_4296E0(v16);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 1;  // 写字段 v6+20（nPage）
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 0;  // 写字段 v6+20（nPage）
            sub_4296E0(v6);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
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
              *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
              sub_433130(v16);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 1;  // 写字段 v6+20（nPage）
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;  // 写字段 v4+20（nPage）
  }
  j__free(Block);  // 释放堆块
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4BB7C0 sub_4BB7C0 —— 图像对象创建并设置路径
//   operator new 0x68 经 ·0x419480 构造（+4 为 0 即失败）后 ·0x4015C0 建 std::string
//   并 ·0x419550 设路径；失败经 off_77F3FC 播 IMAGE INIT FAIL 与 ArgList。
//   【推断：图像加载器对象】
// ------------------------------------------------------------
char */*stdcall*/ sub_4BB7C0(char *ArgList, int nArg2)  // sub_4BB7C0 —— 图像对象创建并设置路径
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  pMem = (char *)operator new(0x68u);  // 堆分配
  v11 = 0;
  if ( pMem != nullptr )
    v3 = sub_419480(pMem, dword_79C0A4);  // dword_79C0A4 —— 调 vt+16 槽
  else
    v3 = nullptr;
  v4 = v3[4];
  v11 = -1;
  if ( v4 == 0 )
    off_77F3FC("IMAGE INIT FAIL [%s]", ArgList);  // off_77F3FC —— 日志打印（printf 风格）
  v9 = 15;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(&v6, ArgList, strlen(ArgList));  // 【std::string构造赋值】
  v11 = 1;
  sub_419550((int)v3, &v6, 0);  // sub_419550 —— 执行 Load
  if ( v9 >= 0x10 )
    j__free(Block);  // 释放堆块
  return v3;
}



// ------------------------------------------------------------
// 0x4BB8C0 sub_4BB8C0 —— map 插入（不覆盖已有键；回写位置与新建标志）
//   自根左走（v8 < v6[3] 取左、否则右）定位，命中且键 ≥ 现值直接回写；键小于节点且为
//   首节点左侧 → ·0x4BB350 插左；否则 ·0x4A3B30(前驱) 后按需插入；pArg2+4 标志是否新建。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BB8C0(uint32_t *this, int pArg2, uint32_t *uArg3)  // sub_4BB8C0 —— map 插入（不覆盖已有键；回写位置与新建标志）
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
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v6 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  uArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_4BB350(this, &uArg3, 1, fld_e1, (int)uArg32);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4A3B30(&uArg3);  // 调 取后继再插
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_4BB350(this, &uArg3, v13, fld_e1, (int)uArg32);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4BB980 sub_4BB980 —— map 插入建议位置（hint 重载）
//   pArg3 为建议位置：空树或建议在首/尾外侧直接插；夹在中间时沿前驱/后继判定，
//   命中已有键转 ·0x4BB8C0，否则 ·0x4BB350 带 hint 插入。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BB980(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)  // sub_4BB980 —— map 插入建议位置（hint 重载）
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    sub_4BB350((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4BB350((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    v8 = (uint32_t *)fld_4[2];  // fld_4=this+16 nChannelTypeSel
    if ( v8[3] < *pArg4 )
    {
      sub_4BB350((uint32_t *)this, uArg2, 0, v8, (int)pArg4);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )  // 调 取后继再插
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0((int *)&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4BB8C0((uint32_t *)this, (int)v10, pArg42);  // sub_4BB8C0 —— map 插入（不覆盖已有键；回写位置与新建标志）
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )
      sub_4BB350((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
    else
      sub_4BB350((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )
      sub_4BB350((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
    else
      sub_4BB350((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);  // sub_4BB350 —— RB 树插入重平衡 + 新节点（map/set 键路径）
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4BBAE0 sub_4BBAE0 —— RB 树区间删除 erase(first, last)，返回末位置
//   区间同首尾（整树）则 ·0x4BB1C0 全释放并把 header 自环复位；否则沿中序步进逐节点
//   ·0x4BB500 删（前驱步进沿 pDwArg32[2]/[1] 分支）。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4BBAE0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)  // sub_4BBAE0 —— RB 树区间删除 erase(first, last)，返回末位置
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
  fld_e1 = (int)*(this + 1);  // this+4〔宿主对象〕
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )  // fld_e1=this+4 宿主对象
  {
    sub_4BB1C0(*(void ***)(fld_e1 + 4));  // sub_4BB1C0 —— RB 树节点递归释放（节点 +21 为红黑/非空判据）
    (*(this + 1))[1] = (int *)*(this + 1);  // this+4〔宿主对象〕
    fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
    *(this + 2) = nullptr;  // 写字段 this+2 ← nullptr
    *fld_e12 = fld_e12;  // fld_e12=this+4 宿主对象
    (*(this + 1))[2] = (int *)*(this + 1);  // this+4〔宿主对象〕
    *pDwArg2 = **(this + 1);  // this+4〔宿主对象〕
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
        sub_4BB500(this, (int ***)&pDwArg3, v10);  // sub_4BB500 —— RB 树节点删除 + 重平衡（map/set erase）
      }
      while ( pDwArg32 != pDwArg42 );  // 循环直到 pDwArg32 != pDwArg42
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4BBBA0 sub_4BBBA0 —— uint32 vector 定点插入（_Insert_n 语义）
//   超 0x3FFFFFFF 经 ·0x41D5A0（vector<T> too long）抛。按剩余容量四路：
//   ① 尾部可移——·0x55E7F0 尾搬 + ·0x5DAF70 空位搬移 + ·0x49A9D0 逐元素填值；
//   ② 尾不够——·0x55E7F0 前段搬 + ·0x523700 尾填 + ·0x49A9D0；
//   ③ 容量不足——按 (size*1.5, 需量) 取大 new，memcpy_0 前后段并 ·0x523700 填。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4BBBA0(int this, uint32_t *Src, unsigned int uArg3, int *pDwArg4)  // sub_4BBBA0 —— uint32 vector 定点插入（_Insert_n 语义）
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

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    result = 0;  // result=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_41D5A0(this);  // 【模块切换辅助（map 容器/观察者清理/资源卸载链）】
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( result >= uArg3 + fld_82 )  // result=this+12 nSkillRec12
    {
      fld_83 = *(uint8_t **)(this + 8);  // this+32〔nHeight(推断)〕
      v21 = (fld_83 - (uint8_t *)Src) >> 2;  // fld_83=this+32 nHeight
      v22 = 4 * uArg3;  // 计算 v22 = 4 * uArg3
      v29 = (int)fld_83;  // fld_83=this+32 nHeight
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];  // fld_83=this+32 nHeight
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // sub_55E7F0 —— 商城状态（10 行）
        sub_5DAF70(Src, v24, v29);  // sub_5DAF70 —— 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return (unsigned int)sub_49A9D0(Src, &Srca[(uint32_t)Src], &pDwArg4);  // sub_49A9D0 —— 区间填充（逐 uint32 写同值）
      }
      else
      {
        sub_55E7F0(Src, (int)fld_83, &Src[v22 / 4u]);  // sub_55E7F0 —— 商城状态（10 行）
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - (int)Src) >> 2), &pDwArg4);  // sub_523700 —— 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_84;  // 写字段 this+8（nSkillRec8） ← fld_84
        return (unsigned int)sub_49A9D0(Src, (uint32_t *)(fld_84 - Srca), &pDwArg4);  // sub_49A9D0 —— 区间填充（逐 uint32 写同值）
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // result=this+12 nSkillRec12
        v10 = (result >> 1) + result;  // result=this+12 nSkillRec12
      else
        v10 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_85 = 0;  // fld_85=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_85 )  // fld_85=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_86 = 0;  // fld_86=this+8 nSkillRec8
        v10 = uArg3 + fld_86;  // 计算 v10 = uArg3 + fld_86
      }
      v28 = 4 * v10;  // 计算 v28 = 4 * v10
      pMem = (char *)operator new(4 * v10);  // 堆分配
      Srcb = 4 * (((int)Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+16〔nChannelTypeSel(推断)〕
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // sub_523700 —— 填充补足尾段
      memcpy_0(v15, Src, 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2));  // this+8〔nSkillRec8(推断)〕等 2 字段
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      v18 = fld_87 + uArg3;  // 计算 v18 = fld_87 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &pMem[v28];  // 写字段 this+12（nSkillRec12） ← &pMem[v28]
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // 写字段 this+8（nSkillRec8） ← &pMem[4 * v18]
      *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
      return (unsigned int)pMem;
    }
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x4BBD80 sub_4BBD80 —— 部件路径解析（+44/+45 字符串槽；sub_4429F0/442AC0 分割）
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4BBD80(uint32_t *this, int ***uArg2, int **pDwArg3)  // sub_4BBD80 —— 部件路径解析（+44/+45 字符串槽；sub_4429F0/442AC0 分割）
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
    sub_401740(pExceptionObject, &v22);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::out_of_range::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_40BEA0((int *)&pDwArg3);  // sub_40BEA0 —— 红黑树迭代器自增（后继；哨兵位 +45）
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
      *(uint32_t *)(v8 + 4) = v4;  // 写字段 v8+4（pHostObj） ← v4
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
        v9 = (int *)sub_6600D0(v4);  // sub_6600D0 —— 红黑树最小结点（沿左子下行，哨兵位 +45）
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;  // 写字段 v10+8（nSkillRec8） ← = (uint32_t)pDwArg32
    v26 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 45) != 0 )
        *(uint32_t *)(v10 + 8) = v6;  // 写字段 v10+8（nSkillRec8） ← v6
      else
        *(uint32_t *)(v26 + 8) = sub_4429F0(v4);  // sub_4429F0 —— v25+8 = sub_4429F0(v4)
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
    *(uint32_t *)(v12 + 4) = v5;  // 写字段 v12+4（pHostObj） ← v5
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
  v14 = *((uint8_t *)v5 + 44);  // 读字段 v14 = v5+44（nExpireMs）
  *((uint8_t *)v5 + 44) = *((uint8_t *)pDwArg32 + 44);  // 写字段 v5+44（nExpireMs）
  *((uint8_t *)pDwArg32 + 44) = v14;  // 写字段 pDwArg32+44（nExpireMs）
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
            *((uint8_t *)v17 + 44) = 1;  // 写字段 v17+44（nExpireMs）
            *((uint8_t *)v6 + 44) = 0;  // 写字段 v6+44（nExpireMs）
            sub_442AC0(v6);  // sub_442AC0 —— 调 sub_442AC0
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
              *((uint8_t *)v17 + 44) = 0;  // 写字段 v17+44（nExpireMs）
              sub_433290(v17);  // sub_433290 —— 红黑树右旋（节点 0x30 版）
              v17 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);  // 写字段 v17+44（nExpireMs）
            *((uint8_t *)v6 + 44) = 1;  // 写字段 v6+44（nExpireMs）
            *(uint8_t *)(v17[2] + 44) = 1;
            sub_442AC0(v6);  // sub_442AC0 —— 调 sub_442AC0
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v17 + 44) == 0 )
          {
            *((uint8_t *)v17 + 44) = 1;  // 写字段 v17+44（nExpireMs）
            *((uint8_t *)v6 + 44) = 0;  // 写字段 v6+44（nExpireMs）
            sub_433290(v6);  // sub_433290 —— 红黑树右旋（节点 0x30 版）
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
              *((uint8_t *)v17 + 44) = 0;  // 写字段 v17+44（nExpireMs）
              sub_442AC0(v17);  // sub_442AC0 —— 调 sub_442AC0
              v17 = (uint32_t *)*v6;
            }
            *((uint8_t *)v17 + 44) = *((uint8_t *)v6 + 44);  // 写字段 v17+44（nExpireMs）
            *((uint8_t *)v6 + 44) = 1;  // 写字段 v6+44（nExpireMs）
            *(uint8_t *)(*v17 + 44) = 1;
            sub_433290(v6);  // sub_433290 —— 红黑树右旋（节点 0x30 版）
            break;
          }
        }
        *((uint8_t *)v17 + 44) = 0;  // 写字段 v17+44（nExpireMs）
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    v15 = (void **)Block;
    *((uint8_t *)v4 + 44) = 1;  // 写字段 v4+44（nExpireMs）
  }
  if ( (unsigned int)v15[9] >= 0x10 )
    j__free(v15[4]);  // 释放堆块
  Block2 = Block;
  *((uint32_t *)Block + 9) = 15;  // 写字段 Block[9]（宽4字节）
  Block2[8] = 0;
  *((uint8_t *)Block2 + 16) = 0;  // 写字段 Block2+16（nChannelTypeSel）
  j__free(Block2);  // 释放堆块
  v19 = pThis[2];
  if ( v19 != 0 )
    pThis[2] = v19 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4BC060 sub_4BC060 —— map 查找或插入（返回值槽 +16 地址）
//   自根 lower_bound 走（键 ≥ 取左），命中且键 ≥ 现值返回节点 +16；否则构造 v5 经
//   ·0x4BB980 插入并返回 +16。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC060(uint32_t *this, uint32_t *uArg2)  // sub_4BC060 —— map 查找或插入（返回值槽 +16 地址）
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v3 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *((uint8_t *)v3 + 21) == 0 )  // 当 *((uint8_t *)v3 + 21) == 0 循环
  {
    if ( (unsigned int)v3[3] >= *uArg2 )
    {
      fld_e1 = v3;  // fld_e1=this+4 宿主对象
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  if ( fld_e1 != (uint32_t *)*(this + 1) && *uArg2 >= fld_e1[3] )  // fld_e1=this+4 宿主对象
    return (int)(fld_e1 + 4);  // fld_e1=this+4 宿主对象
  v5[0] = *uArg2;
  v5[1] = 0;
  return *sub_4BB980((int)this, &uArg2, fld_e1, v5) + 16;  // sub_4BB980 —— map 插入建议位置（hint 重载）
}



// ------------------------------------------------------------
// 0x4BC0E0 sub_4BC0E0 —— RB 树节点递归释放（+45 空判据；释放前 ·0x5014C0 清串资源）
//   与 ·0x4BB1C0 同构：先递归 i[2]、再沿 *i 走左链；节点释放前先 ·0x5014C0(Block2)
//   清理 +16 串资源。【推断：0x30 节点 map 版】
// ------------------------------------------------------------
char /*stdcall*/ sub_4BC0E0(void **Block)  // sub_4BC0E0 —— RB 树节点递归释放（+45 空判据；释放前 ·0x5014C0 清串资源）
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 45);  // 读字段 result = Block[45]
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4BC0E0(i[2]);  // sub_4BC0E0 —— RB 树节点递归释放（+45 空判据；释放前 ·0x5014C0 清串资源）
    i = (void **)*i;
    sub_5014C0(Block2);  // sub_5014C0 —— 调 sub_5014C0
    j__free(Block2);  // 释放堆块
    result = *((uint8_t *)i + 45);  // 读字段 result = i[45]
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BC130 sub_4BC130 —— map/set 节点分配（0x30 字节）
//   operator new 0x30 后 ·0x40C300 构造（nArg1 键、nArg2/nArg3 值、pArg4 串、pszArg5 标志）。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4BC130(int nArg1, int nArg2, int nArg3, size_t *pArg4, char pszArg5)  // sub_4BC130 —— map/set 节点分配（0x30 字节）
{
  uint32_t *pMem; // esi
  void *v7[9]; // [esp+0h] [ebp-24h] BYREF

  v7[5] = v7;
  pMem = operator new(0x30u);  // 堆分配
  v7[4] = pMem;
  v7[8] = (void *)1;  // v7[8] = 转换(1)
  v7[3] = pMem;
  if ( pMem != nullptr )
    sub_40C300(pMem, nArg1, nArg2, nArg3, pArg4, pszArg5);  // sub_40C300 —— 树结点值构造（键串 + 坐标三元 + 颜色标记）
  return pMem;
}



// ------------------------------------------------------------
// 0x4BC1C0 sub_4BC1C0 —— 字符槽缓存取值（+288 门控，30 分钟过期）
//   门 *(this+288) 为 0 直返 0；·0x4BB200 取名字命中后经 ·0x4BC060(this+78) 查该名
//   时间戳，timeGetTime() - 记录 ≥ 0x1B7740 即 vt+28(0) 关、vt+60 重生成写 +82 表[v]、
//   vt+28(1) 开；返回 +82 表项。【推断：过期判据为本地毫秒差】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC1C0(int *this, int *pDwArg2)  // sub_4BC1C0 —— 字符槽缓存取值（+288 门控，30 分钟过期）
{
  int result; // eax
  int *pDwArg22; // ebx
  int v5; // edi
  int v6; // edx
  int v7; // eax

  if ( *((uint8_t *)this + 288) == 0 )  // this+288〔pMaster288(推断)〕
    return 0;
  pDwArg22 = pDwArg2;
  result = sub_4BB200(this, (unsigned int)pDwArg2);  // sub_4BB200 —— 28 字节记录串取值（this+344 表，越界返回 0）
  v5 = result;
  if ( result != 0 )
  {
    pDwArg2 = (int *)sub_4BC060(this + 78, &pDwArg2);  // sub_4BC060 —— map 查找或插入（返回值槽 +16 地址）
    if ( timeGetTime() - *pDwArg2 >= 0x1B7740 )  // 调 取系统毫秒时刻
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 28))(this, 0);  // 虚调用 vt+28（this 虚表槽）
      v6 = *this;
      pDwArg2 = (int *)(*(this + 82) + 4 * (uint32_t)pDwArg22);
      v7 = (*(int (/*thiscall*/ **)(int *, int))(v6 + 60))(this, v5);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行…
      *pDwArg2 = v7;
      (*(void (/*thiscall*/ **)(int *, int))(*this + 28))(this, 1);  // 虚调用 vt+28（this 虚表槽）
    }
    return *(uint32_t *)(*(this + 82) + 4 * (uint32_t)pDwArg22);  // 返回 读 this+82
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BC260 sub_4BC260 —— uint32 vector append（尾插一条）
//   容量够则尾位直写 *pDwArg2（尾指针 +4）；否则走 ·0x4BBBA0 扩容插入路径。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4BC260(int **this, int *pDwArg2)  // sub_4BC260 —— uint32 vector append（尾插一条）
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = (int)*(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // fld_e1=this+4 宿主对象
    fld_e2 = ((int)*(this + 2) - fld_e1) >> 2;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e1 == 0 || fld_e2 >= ((int)*(this + 3) - fld_e1) >> 2 )  // fld_e1=this+4 宿主对象
    return sub_4BBBA0((int)this, *(this + 2), 1u, pDwArg2);  // sub_4BBBA0 —— uint32 vector 定点插入（_Insert_n 语义）
  fld_e22 = *(this + 2);  // 读字段 fld_e22 = this+2
  *fld_e22 = *pDwArg2;  // fld_e22=this+8 物品 id
  result = (unsigned int)(fld_e22 + 1);  // fld_e22=this+8 物品 id
  *(this + 2) = (int *)result;  // 写字段 this+2 ← (int *)result
  return result;
}



// ------------------------------------------------------------
// 0x4BC2B0 sub_4BC2B0 —— RB 树插入重平衡 + 新节点（0x30 节点版）
//   与 ·0x4BB350 同构（节点 0x30、节点数 ≥ 0x7FFFFFE 抛 length_error），
//   差异：分配经 ·0x4BC130、旋转用 ·0x442AC0/·0x433290（右旋）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BC2B0(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, size_t *pArg5)  // sub_4BC2B0 —— RB 树插入重平衡 + 新节点（0x30 节点版）
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

  if ( (unsigned int)*(this + 2) >= 0x7FFFFFE )  // this+8〔nSkillRec8(推断)〕
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_4BC130(*(this + 1), (int)pArg4, *(this + 1), pArg5, 0);  // sub_4BC130 —— map/set 节点分配（0x30 字节）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( pArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    *(uint32_t *)*(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == (uint32_t *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
  }
  v10 = fld_e1 + 1;  // 计算 v10 = fld_e1 + 1
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
            sub_442AC0(*v10);  // sub_442AC0 —— 调 sub_442AC0
          }
          *(uint8_t *)(fld_e16[1] + 44) = 1;
          *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
          sub_433290(*(uint32_t *)(fld_e16[1] + 4));  // sub_433290 —— 红黑树右旋（节点 0x30 版）
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 44) != 0 )
      {
        if ( fld_e16 == (uint32_t *)*v12 )
        {
          fld_e16 = (uint32_t *)*v10;
          sub_433290(*v10);  // sub_433290 —— 红黑树右旋（节点 0x30 版）
        }
        *(uint8_t *)(fld_e16[1] + 44) = 1;
        *(uint8_t *)(*(uint32_t *)(fld_e16[1] + 4) + 44) = 0;
        sub_442AC0(*(uint32_t *)(fld_e16[1] + 4));  // sub_442AC0 —— 调 sub_442AC0
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 44) = 1;
      *(uint8_t *)(v14 + 44) = 1;  // 写字段 v14+44（nExpireMs） ← 1
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 44) = 0;
      fld_e16 = *(uint32_t **)(*v10 + 4);
LABEL_21:
      v10 = fld_e16 + 1;  // 计算 v10 = fld_e16 + 1
      if ( *(uint8_t *)(fld_e16[1] + 44) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 44) = 1;  // this+4〔宿主对象〕
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4BC460 sub_4BC460 —— RB 树区间删除（0x30 节点版），返回末位置
//   与 ·0x4BBAE0 同构（+45 判据、节点清理 ·0x4BC0E0、单步删除 ·0x4BBD80）。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4BC460(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)  // sub_4BC460 —— RB 树区间删除（0x30 节点版），返回末位置
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
  fld_e1 = (int)*(this + 1);  // this+4〔宿主对象〕
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )  // fld_e1=this+4 宿主对象
  {
    sub_4BC0E0(*(void ***)(fld_e1 + 4));  // sub_4BC0E0 —— RB 树节点递归释放（+45 空判据；释放前 ·0x5014C0 清串资源）
    (*(this + 1))[1] = (int *)*(this + 1);  // this+4〔宿主对象〕
    fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
    *(this + 2) = nullptr;  // 写字段 this+2 ← nullptr
    *fld_e12 = fld_e12;  // fld_e12=this+4 宿主对象
    (*(this + 1))[2] = (int *)*(this + 1);  // this+4〔宿主对象〕
    *pDwArg2 = **(this + 1);  // this+4〔宿主对象〕
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
        sub_4BBD80(this, (int ***)&pDwArg3, v10);  // sub_4BBD80 —— 部件路径解析（+44/+45 字符串槽；sub_4429F0/442AC0 分割）
      }
      while ( pDwArg32 != pDwArg42 );  // 循环直到 pDwArg32 != pDwArg42
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4BC520 sub_4BC520 —— 0x18 节点 map 整体清空
//   ·0x4BBAE0 全区间删后 free this+4 头，+4/+8 清 0，返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC520(int this)  // sub_4BC520 —— 0x18 节点 map 整体清空
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4BBAE0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));  // sub_4BBAE0 —— RB 树区间删除 erase(first, last)，返回末位置
  j__free(*(void **)(this + 4));  // 释放堆块
  *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x4BC560 sub_4BC560 —— 串键 map 查找（键 +16 串槽，memcmp 比较）
//   自根：比较节点 +16 串（+36 < 16 判 SSO）与 pArg3 串，memcmp 定左右；命中回写插入位
//   与存在标志；未命中按左外侧 ·0x4BC2B0 插入，或 ·0x501430(前驱) 后 ·0x40BF00 比较再插入。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC560(int *this, int pArg2, size_t *pArg3)  // sub_4BC560 —— 串键 map 查找（键 +16 串槽，memcmp 比较）
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

  fld_e1 = *(uint32_t *)(*(this + 1) + 4);  // this+4〔宿主对象〕
  fld_e12 = (size_t *)*(this + 1);  // this+4〔宿主对象〕
  v5 = 1;
  pArg32 = pArg3;
  pThis = this;
  v21 = 1;
  if ( *(uint8_t *)(fld_e1 + 45) == 0 )  // fld_e1=this+4 宿主对象
  {
    for ( i = pArg3[5]; ; i = pArg3[5] )
    {
      v8 = *(uint32_t *)(fld_e1 + 32);  // 读字段 v8 = fld_e1+32（nHeight）
      v19 = (size_t *)fld_e1;  // fld_e1=this+4 宿主对象
      if ( *(uint32_t *)(fld_e1 + 36) < 0x10u )  // fld_e1=this+4 宿主对象
        v9 = (const char *)(fld_e1 + 16);  // fld_e1=this+4 宿主对象
      else
        v9 = *(const char **)(fld_e1 + 16);  // fld_e1=this+4 宿主对象
      v10 = pArg3[5];
      if ( i < v10 )
        v10 = i;
      if ( v10 == 0 )
        goto LABEL_16;
      if ( v10 < v8 )
        v8 = v10;
      v11 = pArg32[6] < 0x10 ? (const char *)(pArg32 + 1) : (const char *)pArg32[1];
      nCmp = memcmp(v11, v9, v8);  // nCmp = 调 memcmp
      v13 = nCmp < 0;
      pArg32 = pArg3;
      if ( nCmp == 0 )
      {
LABEL_16:
        v14 = *(uint32_t *)(fld_e1 + 32);  // 读字段 v14 = fld_e1+32（nHeight）
        if ( v10 >= v14 )
          v15 = v10 != v14;
        else
          v15 = -1;
        v13 = v15 < 0;
      }
      v5 = v13;
      v21 = v13;
      fld_e1 = v13 ? *(uint32_t *)fld_e1 : *(uint32_t *)(fld_e1 + 8);  // fld_e1=this+4 宿主对象
      if ( *(uint8_t *)(fld_e1 + 45) != 0 )  // fld_e1=this+4 宿主对象
        break;
    }
    fld_e12 = v19;  // fld_e12=this+4 宿主对象
    this = pThis;
  }
  fld_e122 = fld_e12;  // fld_e12=this+4 宿主对象
  pArg3 = fld_e12;  // fld_e12=this+4 宿主对象
  if ( v5 != 0 )
  {
    if ( fld_e12 == *(size_t **)*(this + 1) )  // this+4〔宿主对象〕
    {
      *(uint32_t *)pArg2 = *sub_4BC2B0(this, &pArg3, 1, fld_e12, pArg32);  // sub_4BC2B0 —— RB 树插入重平衡 + 新节点（0x30 节点版）
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      return pArg2;
    }
    sub_501430(&pArg3);  // sub_501430 —— 调 sub_501430
    fld_e122 = pArg3;
  }
  if ( pArg32[6] < 0x10 )
    v18 = (const char *)(pArg32 + 1);
  else
    v18 = (const char *)pArg32[1];
  if ( sub_40BF00((std::_String_base *)(fld_e122 + 3), 0, fld_e122[8], v18, pArg32[5]) >= 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    *(uint32_t *)pArg2 = fld_e122;  // *pArg2 = fld_e122
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
  }
  else
  {
    *(uint32_t *)pArg2 = *sub_4BC2B0(pThis, &pArg3, v21, fld_e12, pArg32);  // sub_4BC2B0 —— RB 树插入重平衡 + 新节点（0x30 节点版）
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
  }
  return pArg2;
}



// ------------------------------------------------------------
// 0x4BC6C0 sub_4BC6C0 —— 0x30 节点 map 整体清空
//   与 ·0x4BC520 同构（·0x4BC460 全删 + free 头 + 清槽）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC6C0(int this)  // sub_4BC6C0 —— 0x30 节点 map 整体清空
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4BC460((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));  // sub_4BC460 —— RB 树区间删除（0x30 节点版），返回末位置
  j__free(*(void **)(this + 4));  // 释放堆块
  *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x4BC700 sub_4BC700 —— ★部件路径 → 资源 id
//   sub_698250/sub_4BC560 查表 → sub_4BB8C0/sub_4BC260 提交；anim_parser [IMAGE] 的
//   帧+4 路径资源即由本函数换算。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BC700(uint32_t *this, int pArg2)  // sub_4BC700 —— ★部件路径 → 资源 id
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  pArg22 = pArg2;
  fld_e73 = *(this + 73);  // 读字段 fld_e73 = this+73（szDigitalName）
  if ( *(uint32_t *)(pArg2 + 24) < 0x10u )  // pArg2+24〔nPageMax(推断)〕
    v4 = pArg2 + 4;  // 计算 v4 = pArg2 + 4
  else
    v4 = *(uint32_t *)(pArg2 + 4);  // 读字段 v4 = pArg2+4（pHostObj）
  v5 = (void *)sub_698250(v24, v4);
  sub_4015C0(v5, strlen((const char *)v5));  // 【std::string构造赋值】
  v6 = *(uint32_t *)sub_5014F0(&pArg2, pArg22);
  if ( v6 != *(this + 76) )  // this+304〔pLayer304(推断)〕
    return *(uint32_t *)(v6 + 40);  // 返回字段 v6+40（bStateSub40）
  v14 = 15;
  v13 = 0;
  LOBYTE(v12) = 0;
  sub_4014D0((std::_String_base *)v11, pArg22, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  fld_e732 = *(this + 73);  // 读字段 fld_e732 = this+73（szDigitalName）
  v26 = 0;
  v19 = 15;
  v18 = 0;
  LOBYTE(Block) = 0;
  sub_4014D0((std::_String_base *)v16, v11, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  fld_e7322 = fld_e732;  // fld_e732=this+73 szDigitalName
  LOBYTE(v26) = 1;
  sub_4BC560(&fld_e7332, v16);  // sub_4BC560 —— 串键 map 查找（键 +16 串槽，memcmp 比较）
  if ( v19 >= 0x10 )
    j__free(Block);  // 释放堆块
  v19 = 15;
  v18 = 0;
  LOBYTE(Block) = 0;
  v26 = -1;
  if ( v14 >= 0x10 )
    j__free(v12);  // 释放堆块
  Time = timeGetTime();  // Time = 调 timeGetTime
  fld_e733 = *(this + 73);  // 读字段 fld_e733 = this+73（szDigitalName）
  v23 = Time - 1800000;  // 计算 v23 = Time - 1800000
  fld_e7332 = fld_e733;  // fld_e733=this+73 szDigitalName
  sub_4BB8C0(v10, &fld_e7332);  // sub_4BB8C0 —— map 插入（不覆盖已有键；回写位置与新建标志）
  v23 = 0;
  sub_4BC260(&v23);  // sub_4BC260 —— uint32 vector append（尾插一条）
  sub_416C40(pArg22);  // sub_416C40 —— 尾插一条 28B 记录（满则走插入路径）
  ++*(this + 73);  // this+292〔nOpenMode292(推断)〕
  return fld_e73;  // fld_e73=this+73 szDigitalName
}



// ============================================================
// §P 0x4BC900-0x4BCE50  部件集合管理
// ============================================================
// ------------------------------------------------------------
// 0x4BC900 sub_4BC900 —— CNImageLoader 构造（图像/资源管理器）
//   ·0x438DB0 基类后写 CNImageLoader vftable；+300 经 ·0x433B80 建 0x30 节点 map 头
//   （+45 空判据自环）、+312 经 ·0x433AC0 建 0x18 节点 map 头（+21 自环）；+288 存标志、
//   +292 记 timeGetTime；随后整体清空两 map 与 +344/+328 两数组。
// ------------------------------------------------------------
char */*thiscall*/ sub_4BC900(char *this, int nArg2, char pszArg3, int nArg4)  // sub_4BC900 —— CNImageLoader 构造（图像/资源管理器）
{
  int pThis_12C; // eax
  int pThis_138; // eax
  uint32_t *pThis_4C; // eax
  uint32_t *pThis_4F; // eax
  int pThis_56; // eax

  sub_438DB0(0, nArg2, nArg4);  // sub_438DB0 —— IFileResourceManager 构造
  *(uint32_t *)this = &CNImageLoader::`vftable';  // 构造装配 vftable：CNImageLoader
  pThis_12C = sub_433B80(this + 300);  // sub_433B80 —— map 节点分配（0x30）
  *((uint32_t *)this + 76) = pThis_12C;  // 写字段 this+76（szEmblemPath）
  *(uint8_t *)(pThis_12C + 45) = 1;  // 写字段 pThis_12C+45 ← 1
  *(uint32_t *)(*((uint32_t *)this + 76) + 4) = *((uint32_t *)this + 76);  // this+304〔pLayer304(推断)〕
  **((uint32_t **)this + 76) = *((uint32_t *)this + 76);  // this+304〔pLayer304(推断)〕
  *(uint32_t *)(*((uint32_t *)this + 76) + 8) = *((uint32_t *)this + 76);  // this+304〔pLayer304(推断)〕
  *((uint32_t *)this + 77) = 0;  // 写字段 this+77（bGuildFlagB）
  pThis_138 = sub_433AC0(this + 312);  // sub_433AC0 —— 结果 = map 节点分配（0x18）
  *((uint32_t *)this + 79) = pThis_138;  // 写字段 this[79]（宽4字节）
  *(uint8_t *)(pThis_138 + 21) = 1;  // 写字段 pThis_138+21（bArmorState） ← 1
  *(uint32_t *)(*((uint32_t *)this + 79) + 4) = *((uint32_t *)this + 79);
  **((uint32_t **)this + 79) = *((uint32_t *)this + 79);
  *(uint32_t *)(*((uint32_t *)this + 79) + 8) = *((uint32_t *)this + 79);
  *((uint32_t *)this + 80) = 0;  // 写字段 this+80（nAuraStage）
  *((uint32_t *)this + 82) = 0;  // 写字段 this[82]（宽4字节）
  *((uint32_t *)this + 83) = 0;  // 写字段 this[83]（宽4字节）
  *((uint32_t *)this + 84) = 0;  // 写字段 this+84（pFxObjA）
  *((uint32_t *)this + 86) = 0;  // 写字段 this[86]（宽4字节）
  *((uint32_t *)this + 87) = 0;  // 写字段 this[87]（宽4字节）
  *((uint32_t *)this + 88) = 0;  // 写字段 this+88（pFxObjB）
  *(this + 288) = pszArg3;  // 写字段 this+288（pMaster288） ← pszArg3
  *((uint32_t *)this + 73) = 0;  // 写字段 this+73（szDigitalName）
  *((uint32_t *)this + 74) = timeGetTime();  // 写字段 this+74（field_004A）
  sub_4BC0E0(*(void ***)(*((uint32_t *)this + 76) + 4));  // sub_4BC0E0 —— RB 树节点递归释放（+45 空判据；释放前 ·0x5014C0 清串资源）
  *(uint32_t *)(*((uint32_t *)this + 76) + 4) = *((uint32_t *)this + 76);  // this+304〔pLayer304(推断)〕
  pThis_4C = *((uint32_t **)this + 76);  // this+76〔pBtnActionE〕
  *((uint32_t *)this + 77) = 0;  // 写字段 this+77（bGuildFlagB）
  *pThis_4C = pThis_4C;  // pThis_4C=this+76 pBtnActionE
  *(uint32_t *)(*((uint32_t *)this + 76) + 8) = *((uint32_t *)this + 76);  // this+304〔pLayer304(推断)〕
  sub_4BB1C0(*(void ***)(*((uint32_t *)this + 79) + 4));  // sub_4BB1C0 —— RB 树节点递归释放（节点 +21 为红黑/非空判据）
  *(uint32_t *)(*((uint32_t *)this + 79) + 4) = *((uint32_t *)this + 79);
  pThis_4F = *((uint32_t **)this + 79);
  *((uint32_t *)this + 80) = 0;  // 写字段 this+80（nAuraStage）
  *pThis_4F = pThis_4F;
  *(uint32_t *)(*((uint32_t *)this + 79) + 8) = *((uint32_t *)this + 79);
  pThis_56 = *((uint32_t *)this + 86);  // 读字段 pThis_56 = this[86]
  if ( pThis_56 != 0 )  // pThis_56=this+344 预约重连延迟 ms
  {
    sub_4166A0(pThis_56, *((uint32_t *)this + 87));  // sub_4166A0 —— 析构区间内 28B string 元素
    j__free(*((void **)this + 86));  // 释放堆块
  }
  *((uint32_t *)this + 86) = 0;  // 写字段 this[86]（宽4字节）
  *((uint32_t *)this + 87) = 0;  // 写字段 this[87]（宽4字节）
  *((uint32_t *)this + 88) = 0;  // 写字段 this+88（pFxObjB）
  if ( *((uint32_t *)this + 82) != 0 )
    j__free(*((void **)this + 82));  // 释放堆块
  *((uint32_t *)this + 82) = 0;  // 写字段 this[82]（宽4字节）
  *((uint32_t *)this + 83) = 0;  // 写字段 this[83]（宽4字节）
  *((uint32_t *)this + 84) = 0;  // 写字段 this+84（pFxObjA）
  return this;
}



// ------------------------------------------------------------
// 0x4BCA90 sub_4BCA90 —— CNImageLoader 析构
//   ·0x697BD0 前置后两 map 经 ·0x4BC0E0/·0x4BB1C0 全释放、+344/+328 数组 free；
//   再 ·0x4BBAE0（+312 头）与 ·0x4BC460（+300 头）清节点后 free 两头，
//   末 ·0x438EA0 资源管理器基类析构。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BCA90(void *this)  // sub_4BCA90 —— CNImageLoader 析构
{
  uint32_t *pThis_4C; // eax
  uint32_t *pThis_4F; // ecx
  int pThis_56; // edx
  int pThis_562; // edx
  int *v7; // [esp-8h] [ebp-28h]
  int *pThis_4F2; // [esp-4h] [ebp-24h]
  int *pThis_57; // [esp+10h] [ebp-10h] BYREF
  int v10; // [esp+1Ch] [ebp-4h]

  *(uint32_t *)this = &CNImageLoader::`vftable';  // 构造装配 vftable：CNImageLoader
  v10 = 4;
  sub_697BD0();  // 调 : 转发虚表槽 +20 并返回
  sub_4BC0E0(*(void ***)(*((uint32_t *)this + 76) + 4));  // sub_4BC0E0 —— RB 树节点递归释放（+45 空判据；释放前 ·0x5014C0 清串资源）
  *(uint32_t *)(*((uint32_t *)this + 76) + 4) = *((uint32_t *)this + 76);  // this+304〔pLayer304(推断)〕
  pThis_4C = *((uint32_t **)this + 76);  // this+76〔pBtnActionE〕
  *((uint32_t *)this + 77) = 0;  // 写字段 this+77（bGuildFlagB）
  *pThis_4C = pThis_4C;  // pThis_4C=this+76 pBtnActionE
  *(uint32_t *)(*((uint32_t *)this + 76) + 8) = *((uint32_t *)this + 76);  // this+304〔pLayer304(推断)〕
  sub_4BB1C0(*(void ***)(*((uint32_t *)this + 79) + 4));  // sub_4BB1C0 —— RB 树节点递归释放（节点 +21 为红黑/非空判据）
  *(uint32_t *)(*((uint32_t *)this + 79) + 4) = *((uint32_t *)this + 79);
  pThis_4F = *((uint32_t **)this + 79);
  *((uint32_t *)this + 80) = 0;  // 写字段 this+80（nAuraStage）
  *pThis_4F = pThis_4F;
  *(uint32_t *)(*((uint32_t *)this + 79) + 8) = *((uint32_t *)this + 79);
  pThis_56 = *((uint32_t *)this + 86);  // 读字段 pThis_56 = this[86]
  if ( pThis_56 != 0 )  // pThis_56=this+344 预约重连延迟 ms
  {
    pThis_57 = *((int **)this + 87);  // pThis_57=this+348 参数表指针
    sub_4166A0(pThis_56, (int)pThis_57);  // sub_4166A0 —— 析构区间内 28B string 元素
    j__free(*((void **)this + 86));  // 释放堆块
  }
  *((uint32_t *)this + 86) = 0;  // 写字段 this[86]（宽4字节）
  *((uint32_t *)this + 87) = 0;  // 写字段 this[87]（宽4字节）
  *((uint32_t *)this + 88) = 0;  // 写字段 this+88（pFxObjB）
  if ( *((uint32_t *)this + 82) != 0 )
    j__free(*((void **)this + 82));  // 释放堆块
  *((uint32_t *)this + 82) = 0;  // 写字段 this[82]（宽4字节）
  *((uint32_t *)this + 83) = 0;  // 写字段 this[83]（宽4字节）
  *((uint32_t *)this + 84) = 0;  // 写字段 this+84（pFxObjA）
  pThis_562 = *((uint32_t *)this + 86);  // 读字段 pThis_562 = this[86]
  if ( pThis_562 != 0 )  // pThis_562=this+344 预约重连延迟 ms
  {
    pThis_57 = *((int **)this + 87);  // pThis_57=this+348 参数表指针
    sub_4166A0(pThis_562, (int)pThis_57);  // sub_4166A0 —— 析构区间内 28B string 元素
    j__free(*((void **)this + 86));  // 释放堆块
  }
  *((uint32_t *)this + 86) = 0;  // 写字段 this[86]（宽4字节）
  *((uint32_t *)this + 87) = 0;  // 写字段 this[87]（宽4字节）
  *((uint32_t *)this + 88) = 0;  // 写字段 this+88（pFxObjB）
  if ( *((uint32_t *)this + 82) != 0 )
    j__free(*((void **)this + 82));  // 释放堆块
  *((uint32_t *)this + 82) = 0;  // 写字段 this[82]（宽4字节）
  *((uint32_t *)this + 83) = 0;  // 写字段 this[83]（宽4字节）
  *((uint32_t *)this + 84) = 0;  // 写字段 this+84（pFxObjA）
  pThis_4F2 = *((int **)this + 79);
  v7 = (int *)*pThis_4F2;
  LOBYTE(v10) = 1;
  sub_4BBAE0((int ***)this + 78, &pThis_57, v7, pThis_4F2);  // sub_4BBAE0 —— RB 树区间删除 erase(first, last)，返回末位置
  j__free(*((void **)this + 79));  // 释放堆块
  *((uint32_t *)this + 79) = 0;  // 写字段 this[79]（宽4字节）
  *((uint32_t *)this + 80) = 0;  // 写字段 this+80（nAuraStage）
  LOBYTE(v10) = 0;
  sub_4BC460((int ***)this + 75, &pThis_57, **((int ***)this + 76), *((int **)this + 76));  // sub_4BC460 —— RB 树区间删除（0x30 节点版），返回末位置
  j__free(*((void **)this + 76));  // 释放堆块
  *((uint32_t *)this + 76) = 0;  // 写字段 this+76（szEmblemPath）
  *((uint32_t *)this + 77) = 0;  // 写字段 this+77（bGuildFlagB）
  v10 = -1;
  return sub_438EA0(this);  // sub_438EA0 —— 资源管理器析构
}



// ------------------------------------------------------------
// 0x4BCC70 sub_4BCC70 —— 标量删除析构（·0x4BCA90 后按标志位 1 释放）
//   转发 ·0x4BCA90，pszArg2 位 0 置位时 j__free(Block)。
// ------------------------------------------------------------
void */*thiscall*/ sub_4BCC70(void *Block, char pszArg2)  // sub_4BCC70 —— 标量删除析构（·0x4BCA90 后按标志位 1 释放）
{
  sub_4BCA90(Block);  // sub_4BCA90 —— CNImageLoader 析构
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x4BCCA0 sub_4BCCA0 —— 摆摊驴/物件状态复位（+96 置 66 默认状态）
//   写 +96 = 66（默认状态码）、+284/+285/+286/+304/+340/+341 字节位清 0、+308/+312 = 4、
//   +336/+348 记 timeGetTime、+356/+360/+372/+376 = -1 哨兵；返回 -1。
//   【推断：+96 = 66 为物件默认状态（vmt+96 状态槽）】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BCCA0(int this)  // sub_4BCCA0 —— 摆摊驴/物件状态复位（+96 置 66 默认状态）
{
  *(uint32_t *)(this + 96) = 66;  // 写字段 this+96（nStatusMode） ← 66
  *(uint8_t *)(this + 284) = 0;  // 写字段 this+284（bBindGate284） ← 0
  *(uint8_t *)(this + 285) = 0;  // 写字段 this+285（bField285） ← 0
  *(uint32_t *)(this + 308) = 4;  // 写字段 this+308 ← 4
  *(uint32_t *)(this + 312) = 4;  // 写字段 this+312 ← 4
  *(uint32_t *)(this + 316) = 0;  // 写字段 this+316 ← 0
  *(uint32_t *)(this + 320) = 0;  // 写字段 this+320 ← 0
  *(uint32_t *)(this + 324) = 0;  // 写字段 this+324（nAnchor324） ← 0
  *(uint32_t *)(this + 328) = 0;  // 写字段 this+328 ← 0
  *(uint32_t *)(this + 336) = timeGetTime();  // 写字段 this+336 ← timeGetTime()
  *(uint8_t *)(this + 340) = 0;  // 写字段 this+340（pSlotTbl340） ← 0
  *(uint8_t *)(this + 341) = 0;  // 写字段 this+341 ← 0
  *(uint32_t *)(this + 344) = 0;  // 写字段 this+344（nReservedDelay） ← 0
  *(uint32_t *)(this + 356) = -1;  // 写字段 this+356 ← -1
  *(uint32_t *)(this + 360) = -1;  // 写字段 this+360 ← -1
  *(uint32_t *)(this + 364) = 0;  // 写字段 this+364（pAnimNameStr） ← 0
  *(uint32_t *)(this + 368) = 0;  // 写字段 this+368（nBindPos368） ← 0
  *(uint32_t *)(this + 304) = 0;  // 写字段 this+304（pLayer304） ← 0
  *(uint8_t *)(this + 286) = 0;  // 写字段 this+286 ← 0
  *(uint32_t *)(this + 348) = timeGetTime();  // 写字段 this+348（pParamTbl348） ← timeGetTime()
  *(uint32_t *)(this + 352) = 4;  // 写字段 this+352（uHitCtx352） ← 4
  *(uint32_t *)(this + 372) = -1;  // 写字段 this+372（nBindRef372） ← -1
  *(uint32_t *)(this + 376) = -1;  // 写字段 this+376（nBindRef376） ← -1
  return -1;
}



// ------------------------------------------------------------
// 0x4BCD50 sub_4BCD50 —— 帧句柄数组分配（5 × 4 = 0x14 字节）
//   operator new 0x14 写 *(this+73)，五个句柄清 0，*(this+74) 清 0；返回表首。
//   析构侧见 ·0x4BDC40。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BCD50(uint32_t *this)  // sub_4BCD50 —— 帧句柄数组分配（5 × 4 = 0x14 字节）
{
  uint32_t *pMem; // eax
  int result; // eax

  pMem = operator new(0x14u);  // 堆分配
  *(this + 73) = pMem;  // 写字段 this+73（szDigitalName） ← pMem
  *pMem = 0;
  *(uint32_t *)(*(this + 73) + 4) = 0;  // this+292〔nOpenMode292(推断)〕
  *(uint32_t *)(*(this + 73) + 8) = 0;  // this+292〔nOpenMode292(推断)〕
  result = *(this + 73);  // 读字段 result = this+73（szDigitalName）
  *(uint32_t *)(result + 12) = 0;  // 写字段 result+12（nSkillRec12） ← 0
  *(uint32_t *)(*(this + 73) + 16) = 0;  // this+292〔nOpenMode292(推断)〕
  *(this + 74) = 0;  // 写字段 this+74（field_004A） ← 0
  return result;  // result=this+73 szDigitalName
}



// ------------------------------------------------------------
// 0x4BCDA0 sub_4BCDA0 —— 动画帧驱动 tick（先 vt+80 装配归属再 ·0x498CA0 逐帧驱动）
//   取 *(pArg1+288) 对象的 vt+80 非 0 且 ≠ *(pArg1+116) 时，
//   ·0x45FE80(对象, nArg2, 66, 0, pArg1, 0, 0) 挂入图层/池；末转发 ·0x498CA0
//   （组件逐帧驱动：坐标回写 + 尾帧处理）。
// ------------------------------------------------------------
int /*usercall*/ sub_4BCDA0@<eax>(int pArg1@<ecx>, int nArg2@<edi>)  // 实现：动画帧驱动 tick（先 vt+80 装配归属再 ·0x498CA0 逐帧驱动）
{
  int v3; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 288) + 80))(*(uint32_t *)(pArg1 + 288)) != 0  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 288) + 80))(*(uint32_t *)(pArg1 + 288)) != *(uint32_t *)(pArg1 + 116) )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(pArg1 + 288) + 80))(*(uint32_t *)(pArg1 + 288));  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    sub_45FE80(v3, nArg2, 66, 0, pArg1, 0, 0);  // sub_45FE80 —— 对象注册
  }
  return sub_498CA0((float *)pArg1, nArg2);  // sub_498CA0 —— 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）
}



// ------------------------------------------------------------
// 0x4BCDF0 sub_4BCDF0 —— 当前动画盒同步（句柄 → ·0x498EC0 坐标直写）
//   *(this+72) 非空时经 vt+120/+124/+128 取 动画对象/序号/边界，
//   ·0x498EC0(this, 对象, 序号-1, 边界) 写坐标，再 ·0x498C40 五组虚槽批量重置。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BCDF0(int *this)  // sub_4BCDF0 —— 当前动画盒同步（句柄 → ·0x498EC0 坐标直写）
{
  int result; // eax
  int v3; // edi
  int fld_e72; // ebx  | +0x0120 → 主人绑定对象（CNRDDonkey；va=004BD720）
  int fld_e722; // eax  | +0x0120 → 主人绑定对象（CNRDDonkey；va=004BD720）

  result = *(this + 72);  // 读字段 result = this+72（nSnapshot72）
  if ( result != 0 )  // result=this+72 nSnapshot72
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 120))(result);  // 虚调用 vt+120（result）转发(对象+缓冲)
    fld_e72 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 72) + 124))(*(this + 72));  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    fld_e722 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 72) + 128))(*(this + 72));  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FCB0…
    sub_498EC0(this, v3, fld_e72 - 1, fld_e722);  // sub_498EC0 —— 坐标三分量直写（无有效性判定版）
    return sub_498C40(this);  // sub_498C40 —— 五组虚槽批量重置
  }
  return result;  // result=this+72 nSnapshot72
}



// ============================================================
// §Q 0x4BCE50-0x4BE170  摆摊驴 Donkey 族
// ============================================================
// ------------------------------------------------------------
// 0x4BCE50 sub_4BCE50 —— 摆摊驴部件装载（Character/Common/PrivateStore/Donkey/Store.img → +284 槽）
// ------------------------------------------------------------
char /*thiscall*/ sub_4BCE50(uint32_t *this, int nArg2, int nArg3)  // sub_4BCE50 —— 摆摊驴部件装载（Character/Common/PrivateStore/Donkey/Store.img → +284 槽）
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

  if ( *(this + 29) == 0 )  // this+116〔会话上下文〕
    return 0;
  v18 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8);  // 虚调用 vt+36（this 虚表槽）
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  v6 = sub_45E490(v5, v18);  // sub_45E490 —— 结果 = 屏幕 y → 演出层坐标（减基线）
  v17 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 8);  // 虚调用 vt+36（this 虚表槽）
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
  v8 = sub_45E4D0(v7, v16, v17, 1.0);  // sub_45E4D0 —— 结果 = 带比例的回换算（nArg2 - nArg3*f + 120）
  v19 = v8;
  v20 = 1;
  if ( *((uint8_t *)this + 284) != 0 )  // this+284〔bBindGate284(推断)〕
  {
    if ( (dword_9A056C & 1) != 0 )  // 判定位掩码：dword_9A056C & 1
    {
      dword_9A05682 = dword_9A0568;
    }
    else
    {
      dword_9A056C |= 1u;
      v9 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
                       dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
                       "Character/Common/PrivateStore/Donkey/Store.img");  // 资源路径 Character/Common/PrivateStore/Donkey/Store.img
      dword_9A05682 = sub_418DD0(v9, 0);  // sub_418DD0 —— 资源句柄 (101)
      dword_9A0568 = dword_9A05682;
    }
    nArg22 = nArg2;
    v12 = *(uint32_t *)(dword_9A05682 + 24);  // 读字段 v12 = dword_9A05682+24（nPageMax）
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
    if ( nArg2 >= v6 + 50 )  // 判定 nArg2 >= v6 + 50
      return 0;
    nArg32 = nArg3;
    if ( nArg3 < v8 - 50 )
      return 0;
    v15 = v8 + 10;  // 计算 v15 = v8 + 10
  }
  if ( nArg32 >= v15 )
    return 0;
  return v20;
}



// ------------------------------------------------------------
// 0x4BCFC0 sub_4BCFC0 —— 摆摊驴 Store.img 加载并居中绘制
//   先转发 ·0x49A600（vmt148 玩家脚下光圈渲染钩）；pszArg2 非 0 且 +284 门开时按需
//   载 Character/Common/PrivateStore/Donkey/Store.img（·0x418DD0(资源, 3)）并经 vt+152
//   以 nArg3/nArg4 居中绘制（左减半宽、上减 3 倍高之半）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BCFC0(uint8_t *this, char pszArg2, int nArg3, int nArg4, int nArg5)  // sub_4BCFC0 —— 摆摊驴 Store.img 加载并居中绘制
{
  uint32_t *v6; // eax
  uint32_t *v7; // eax

  sub_49A600(this, pszArg2, nArg3, nArg4, nArg5);  // sub_49A600 —— ★ 玩家脚下光圈渲染钩（101 号资源；150↔255 / 400ms 三角波）
  LOBYTE(v6) = pszArg2;
  if ( pszArg2 != 0 )
  {
    LOBYTE(v6) = *(this + 284);  // this+284 绑定/记录门字节
    if ( (uint8_t)v6 != 0 )
    {
      if ( (dword_9A0574 & 1) != 0 )  // 判定位掩码：dword_9A0574 & 1
      {
        v6 = (uint32_t *)dword_9A0570;
      }
      else
      {
        dword_9A0574 |= 1u;
        v7 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 虚调用 vt+60（dword_8F84B8）对象销毁/释放
                         dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
                         "Character/Common/PrivateStore/Donkey/Store.img");  // 资源路径 Character/Common/PrivateStore/Donkey/Store.img
        v6 = (uint32_t *)sub_418DD0(v7, 3u);  // sub_418DD0 —— 资源句柄 (101)
        dword_9A0570 = (int)v6;
      }
      if ( v6 != nullptr )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(uint32_t *, int, unsigned int, int))(*v6 + 152))(  // 虚调用 vt+152（v6）取值(参数)
                       v6,
                       nArg3 - (v6[5] >> 1),
                       nArg4 - ((unsigned int)(3 * v6[6]) >> 1),
                       dword_79C0B0);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    }
  }
  return (char)v6;
}



// ------------------------------------------------------------
// 0x4BD090 sub_4BD090 —— 摆摊驴随机待机演出（+340 门控；8 至 11 秒随机插曲）
//   +286 门控下，+340 非空且 当前时刻 > +336(上次) + +348(周期 ms) 时重掷：
//   rand 周期 = 1000 * (rand()%4 + 8) 写 +348，·0x422E70(1337) 取串经 vt+64 对象
//   ·0x50EF20(…, 4000) 播报。【推断：驴待机随机动作或文本播报】
// ------------------------------------------------------------
char /*thiscall*/ sub_4BD090(uint8_t *this)  // sub_4BD090 —— 摆摊驴随机待机演出（+340 门控；8 至 11 秒随机插曲）
{
  signed int Time; // eax
  int pThis_40; // eax
  int v5; // [esp-Ch] [ebp-10h]

  LOBYTE(Time) = *(this + 286);
  if ( (uint8_t)Time != 0 )
  {
    Time = timeGetTime();  // Time = 调 timeGetTime
    if ( *(this + 340) != 0 && Time > *((uint32_t *)this + 88) + *((uint32_t *)this + 87) )  // this+352〔uHitCtx352〕
    {
      *((uint32_t *)this + 87) = Time;  // 写字段 this[87]（宽4字节）
      srand(Time);  // 调 设置随机种子
      *((uint32_t *)this + 88) = 1000 * (rand() % 4 + 8);  // 写字段 this+88（pFxObjB）
      v5 = sub_422E70(1337);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      pThis_40 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 64))(this);  // 虚调用 vt+64（this）读游标登记(跳过包头)
      LOBYTE(Time) = sub_50EF20(pThis_40, v5, 0, 4000);  // 气泡文本设置与量算（行数/半高/倒计时）
    }
  }
  return Time;
}



// ------------------------------------------------------------
// 0x4BD120 sub_4BD120 —— 摆摊驴跟随目标选择（±60/180 门限）
//   +288 无主时经 off_77F3FC 播 Donkey 无 owner 提示。比较自身与主人的
//   vt+120/+124 位置：差 ≥ 60 或 > 180 走 +332 = 4 状态分支、记目标 +316/+320，
//   否则贴齐自身位置置 +308/+312 = 4、+332 = 3。【推断：两轴 = x/y 或格座标】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD120(uint32_t *this)  // sub_4BD120 —— 摆摊驴跟随目标选择（±60/180 门限）
{
  int fld_e72; // ecx
  int v3; // edi
  int v4; // ebx
  int result; // eax
  int v6; // ecx
  int fld_e722; // [esp+4h] [ebp-8h]
  int v8; // [esp+8h] [ebp-4h]

  fld_e72 = *(this + 72);  // 读字段 fld_e72 = this+72（nSnapshot72）
  if ( fld_e72 == 0 )  // fld_e72=this+72 nSnapshot72
    return off_77F3FC("Donkey doesn't have owner.");  // off_77F3FC —— 日志打印（printf 风格）
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e72 + 120))(fld_e72);  // 虚调用 vt+120（fld_e72）转发(对象+缓冲)
  fld_e722 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 72) + 124))(*(this + 72));  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
  result = v3 - v4;
  v6 = abs32(v3 - v4);  // v6 = 调 abs32
  if ( v6 >= 60 || (result = abs32(fld_e722 - v8)) >= 60 )
  {
    *(this + 79) = v3;  // 写字段 this+79 ← v3
    *(this + 80) = fld_e722;  // 写字段 this+80（nAuraStage） ← fld_e722
    if ( v6 > 180 )
      *(this + 83) = 4;  // 写字段 this+83 ← 4
  }
  else
  {
    *(this + 80) = v8;  // 写字段 this+80（nAuraStage） ← v8
    result = 4;
    *(this + 79) = v4;  // 写字段 this+79 ← v4
    *(this + 77) = 4;  // 写字段 this+77（bGuildFlagB） ← 4
    *(this + 78) = 4;  // 写字段 this+78（bGuildFlagC） ← 4
    *(this + 83) = 3;  // 写字段 this+83 ← 3
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BD1F0 sub_4BD1F0 —— 摆摊驴朝向状态机与表现速率写入
//   以 +324/+316（当前对目标 x）与 +328/+320（y）双向比较，做 4 态迁移：
//   经 vt+120/+124/+128/+112 读写位置与朝向，再按状态算 v17/v16 写入帧对象
//   +16/+20（浮点表现速率）。【推断：+308/+312 为轴朝向状态】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD1F0(int *this)  // sub_4BD1F0 —— 摆摊驴朝向状态机与表现速率写入
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

  fld_e81 = *(this + 81);  // 读字段 fld_e81 = this+81
  fld_e79 = *(this + 79);  // 读字段 fld_e79 = this+79
  fld_e812 = fld_e81 <= fld_e79;  // fld_e81=this+81 高度提交槽
  if ( fld_e81 < fld_e79 )  // fld_e81=this+81 高度提交槽
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) > fld_e79 && *(this + 77) == 1 )  // 虚调用 vt+120（this）转发(对象+缓冲)
      goto LABEL_4;
    fld_e812 = *(this + 81) <= fld_e79;  // this+324〔nRandPick324〕
  }
  if ( !fld_e812 && (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) < *(this + 79) && *(this + 77) == 0 )  // 虚调用 vt+120（this）转发(对象+缓冲)
  {
LABEL_4:
    v5 = *this;
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    v15 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v6);  // 虚调用 vt+124（this）目标坐标y下界
    fld_e792 = *(this + 79);  // 读字段 fld_e792 = this+79
    (*(void (/*thiscall*/ **)(int *))(v5 + 112))(this);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
LABEL_5:
    *(this + 77) = 4;  // 写字段 this+77（bGuildFlagB） ← 4
    goto LABEL_6;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) >= *(this + 79) )  // 虚调用 vt+120（this）转发(对象+缓冲)
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) <= *(this + 79) )  // 虚调用 vt+120（this）转发(对象+缓冲)
      goto LABEL_5;
    *(this + 77) = 0;  // 写字段 this+77（bGuildFlagB） ← 0
  }
  else
  {
    *(this + 77) = 1;  // 写字段 this+77（bGuildFlagB） ← 1
  }
LABEL_6:
  fld_e80 = *(this + 80);  // 读字段 fld_e80 = this+80（nAuraStage）
  fld_e82 = *(this + 82) <= fld_e80;  // fld_e80=this+80 nAuraStage
  if ( *(this + 82) < fld_e80 )  // fld_e80=this+80 nAuraStage
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) > fld_e80 && *(this + 78) == 3 )  // 虚调用 vt+124（this）目标坐标y下界
      goto LABEL_9;
    fld_e82 = *(this + 82) <= fld_e80;  // fld_e80=this+80 nAuraStage
  }
  if ( !fld_e82 && (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) < *(this + 80) && *(this + 78) == 2 )  // 虚调用 vt+124（this）目标坐标y下界
  {
LABEL_9:
    v9 = *this;
    (*(void (/*thiscall*/ **)(int *, int, int))(*this + 128))(this, fld_e792, v15);  // 虚调用 vt+128（this）目标坐标y上界
    v10 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(int *, int))(v9 + 112))(this, v10);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
LABEL_10:
    *(this + 78) = 4;  // 写字段 this+78（bGuildFlagC） ← 4
    goto LABEL_11;
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) >= *(this + 80) )  // 虚调用 vt+124（this）目标坐标y下界
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) <= *(this + 80) )  // 虚调用 vt+124（this）目标坐标y下界
      goto LABEL_10;
    *(this + 78) = 2;  // 写字段 this+78（bGuildFlagC） ← 2
  }
  else
  {
    *(this + 78) = 3;  // 写字段 this+78（bGuildFlagC） ← 3
  }
LABEL_11:
  fld_e78 = *(this + 78);  // 读字段 fld_e78 = this+78（bGuildFlagC）
  v12 = fld_e78 != 4 ? 112 : 134;  // fld_e78=this+78 bGuildFlagC
  result = *(this + 77);  // 读字段 result = this+77（bGuildFlagB）
  v17 = v12;
  v16 = result != 4 ? 73 : 90;  // result=this+77 bGuildFlagB
  if ( *(this + 83) == 4 )  // this+332〔bReservedConn〕
  {
    v12 = 268;
    v17 = 268;
  }
  if ( result == 4 )  // result=this+77 bGuildFlagB
  {
    v17 = 0;
  }
  else if ( result == 0 )  // result=this+77 bGuildFlagB
  {
    v17 = -v12;
  }
  if ( fld_e78 == 4 )  // fld_e78=this+78 bGuildFlagC
  {
    v16 = 0;
  }
  else if ( fld_e78 == 2 )  // fld_e78=this+78 bGuildFlagC
  {
    v16 = -(result != 4 ? 73 : 90);  // v16 = 调 -
  }
  *(float *)(*(this + 28) + 16) = (float)v17;  // this+112〔pHostComp112〕
  *(float *)(*(this + 28) + 20) = (float)v16;  // this+112〔pHostComp112〕
  return result;  // result=this+77 bGuildFlagB
}


// ------------------------------------------------------------
// 0x4BD440 sub_4BD440 —— 四元组写入（this+356..+368）
//   依次写 *(this+89..+92) = nArg2..nArg5；读取侧见 ·0x4BD470。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD440(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // sub_4BD440 —— 四元组写入（this+356..+368）
{
  *(this + 89) = nArg2;  // 写字段 this+89（nLifetime） ← nArg2
  *(this + 90) = nArg3;  // 写字段 this+90 ← nArg3
  *(this + 91) = nArg4;  // 写字段 this+91 ← nArg4
  *(this + 92) = nArg5;  // 写字段 this+92（pFxObjC） ← nArg5
  return nArg4;
}



// ------------------------------------------------------------
// 0x4BD470 sub_4BD470 —— 四元组读取（this+356..+368）
//   依次回写 *uArg2..*uArg5 = *(this+89..+92)；写入侧见 ·0x4BD440。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD470(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3, uint32_t *uArg4, uint32_t *uArg5)  // sub_4BD470 —— 四元组读取（this+356..+368）
{
  int result; // eax

  *uArg2 = *(this + 89);  // this+89 寿命上限门
  *uArg3 = *(this + 90);
  *uArg4 = *(this + 91);  // this+364〔pAnimNameStr(推断)〕
  result = *(this + 92);  // 读字段 result = this+92（pFxObjC）
  *uArg5 = result;  // result=this+92 pFxObjC
  return result;  // result=this+92 pFxObjC
}



// ------------------------------------------------------------
// 0x4BD4B0 sub_4BD4B0 —— 就位与状态位开启（+284/+285）
//   置 *(this+284) = 1、*(this+285) = 1 并返回 1；两门控被 ·0x4BDCA0/·0x4BCFC0/
//   ·0x4BE040 读取。【推断：驴已创建 与 渲染使能】
// ------------------------------------------------------------
char /*thiscall*/ sub_4BD4B0(uint8_t *this)  // sub_4BD4B0 —— 就位与状态位开启（+284/+285）
{
  *(this + 284) = 1;  // 写字段 this+284（bBindGate284） ← 1
  *(this + 285) = 1;  // 写字段 this+285（bField285） ← 1
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x4BD500 sub_4BD500 —— 标志写（+286）
//   设 *(this+286) = pszArg2 并返回；读侧见 ·0x4BD090（随机演出门控）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BD500(uint8_t *this, char pszArg2)  // sub_4BD500 —— 标志写（+286）
{
  *(this + 286) = pszArg2;  // 写字段 this+286 ← pszArg2
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4BD510 sub_4BD510 —— 动画盒写 + 绑定目标记录（+372/+376/+364/+368）
//   自 dword_8F7A24+20 的 +100/+104 取 v5/v9（无则 -1 哨兵）；·0x498EC0(this, nArg2,
//   nArg3-1, nArg4) 写坐标；+372/+376 记 v5/v9，+284 门开时 +364/+368 记 nArg2/nArg3。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BD510(int this, int nArg2, int nArg3, int nArg4)  // sub_4BD510 —— 动画盒写 + 绑定目标记录（+372/+376/+364/+368）
{
  int v4; // eax
  int v5; // edi
  int *v6; // eax
  char result; // al
  int v9; // [esp+Ch] [ebp-4h]

  v4 = *(uint32_t *)(dword_8F7A24 + 20);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  v5 = *(uint32_t *)(v4 + 100);  // 读字段 v5 = v4+100（bEnchantDone）
  v6 = *(int **)(v4 + 104);
  if ( v6 != nullptr )
    v9 = *v6;
  else
    v9 = -1;
  sub_498EC0((uint32_t *)this, nArg2, nArg3 - 1, nArg4);  // sub_498EC0 —— 坐标三分量直写（无有效性判定版）
  result = *(uint8_t *)(this + 284);  // 读字段 result = this+284（bBindGate284）
  *(uint32_t *)(this + 372) = v5;  // 写字段 this+372（nBindRef372） ← v5
  *(uint32_t *)(this + 376) = v9;  // 写字段 this+376（nBindRef376） ← v9
  if ( result != 0 )  // result=this+284 bBindGate284
  {
    *(uint32_t *)(this + 364) = nArg2;  // 写字段 this+364（pAnimNameStr） ← nArg2
    *(uint32_t *)(this + 368) = nArg3;  // 写字段 this+368（nBindPos368） ← nArg3
    return nArg2;
  }
  return result;  // result=this+284 bBindGate284
}



// ------------------------------------------------------------
// 0x4BD5E0 sub_4BD5E0 —— 主人绑定（this+288；抄主人门标志 +652）
//   *(this+72) = nArg2 后经主人 vt+120/+124/+128 取位置、vt+112 写回自身；
//   再抄 *(主人+652) 到 *(this+286)。【推断：绑定主人并同步位置与门标志】
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD5E0(uint32_t *this, int nArg2)  // sub_4BD5E0 —— 主人绑定（this+288；抄主人门标志 +652）
{
  int v3; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int result; // eax

  v3 = *this;
  *(this + 72) = nArg2;  // 写字段 this+72（nSnapshot72） ← nArg2
  v5 = (*(int (**)(void))(*(uint32_t *)nArg2 + 128))();  // 虚调用 vt+128（nArg2）目标坐标y上界
  v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 124))(nArg2, v5);  // 虚调用 vt+124（nArg2）目标坐标y下界
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v6);  // 虚调用 vt+120（nArg2）转发(对象+缓冲)
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 112))(this, v7);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
  *((uint8_t *)this + 286) = *(uint8_t *)(*(this + 72) + 652);  // 写字段 this[286]（宽1字节）
  return result;
}



// ------------------------------------------------------------
// 0x4BD630 sub_4BD630 —— 主人名字取值（+304 串槽，空返回 szPassword）
//   *(this+76) 为串对象；为空返回 szPassword（全局空串）；否则 +24 < 16 判 SSO
//   返回仓内 +4，否则返回堆指针。
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_4BD630(uint32_t *this)  // sub_4BD630 —— 结果 = 主人名字取值（+304 串槽，空返回 szPassword）
{
  int fld_e76; // eax

  fld_e76 = *(this + 76);  // 读字段 fld_e76 = this+76（szEmblemPath）
  if ( fld_e76 == 0 )  // fld_e76=this+76 szEmblemPath
    return szPassword;
  if ( *(uint32_t *)(fld_e76 + 24) < 0x10u )  // fld_e76=this+76 szEmblemPath
    return (const CHAR *)(fld_e76 + 4);  // fld_e76=this+76 szEmblemPath
  return *(const CHAR **)(fld_e76 + 4);  // fld_e76=this+76 szEmblemPath
}



// ------------------------------------------------------------
// 0x4BD650 sub_4BD650 —— std::string 拷贝构造到 pArg2
//   pArg2 三槽初始化（+20 = 0、+24 = 15、+4 = 0）后 ·0x4014D0(this, pArg2, uArg3, uArg4)
//   按 [uArg3, uArg4) 区间拷贝。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BD650(size_t *this, int pArg2, unsigned int uArg3, unsigned int uArg4)  // sub_4BD650 —— std::string 拷贝构造到 pArg2
{
  *(uint32_t *)(pArg2 + 20) = 0;  // 写字段 pArg2+20（nPage） ← 0
  *(uint32_t *)(pArg2 + 24) = 15;  // 写字段 pArg2+24（nPageMax） ← 15
  *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
  sub_4014D0((size_t *)pArg2, this, uArg3, uArg4);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  return pArg2;
}



// ------------------------------------------------------------
// 0x4BD690 sub_4BD690 —— 主人名字写（+304 串槽，懒建）
//   +304 槽已有串对象时 ·0x4015C0(串, Block, strlen) 赋值；否则 new 0x1C 经 ·0x401710 构造。
//   【推断：与 ·0x4BD630 读取的 +304 槽配对】
// ------------------------------------------------------------
void /*thiscall*/ sub_4BD690(size_t **this, char *Block)  // sub_4BD690 —— 主人名字写（+304 串槽，懒建）
{
  size_t *fld_e76; // ecx
  void *pMem; // eax
  int v5; // eax

  if ( Block != nullptr )
  {
    fld_e76 = *(this + 76);  // 读字段 fld_e76 = this+76（szEmblemPath）
    if ( fld_e76 != nullptr )  // fld_e76=this+76 szEmblemPath
    {
      sub_4015C0(fld_e76, Block, strlen(Block));  // 【std::string构造赋值】
    }
    else
    {
      pMem = operator new(0x1Cu);  // 堆分配
      if ( pMem != nullptr )
        v5 = sub_401710((int)pMem, Block);  // sub_401710 —— std::string 复位并赋值 C 串（+24=15/+20=0/+4=0 → ·sub_4015C0）
      else
        v5 = 0;
      *(this + 76) = (size_t *)v5;  // 写字段 this+76（szEmblemPath） ← (size_t *)v5
    }
  }
}



// ------------------------------------------------------------
// 0x4BD720 sub_4BD720 —— 摆摊驴整体装配（+284/+285/+286/+288 槽；+44 槽 → sub_491530/491630 图层）
// ------------------------------------------------------------
void /*thiscall*/ sub_4BD720(int this, int nArg2, int nArg3, int nArg4, int nArg5)  // sub_4BD720 —— 摆摊驴整体装配（+284/+285/+286/+288 槽；+44 槽 → sub_491530/491630 图层）
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
  int fld_1302; // ecx  | +0x0130 → 图层/子件槽（CNRDDonkey；va=004BD720）
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
  int fld_120; // eax  | +0x0120 → 主人绑定对象（CNRDDonkey；va=004BD720）
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

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  nullsub_2(nArg2, nArg3, nArg4, nArg5);
  if ( (uint8_t)nArg2 == 0 )
    return;
  if ( *(uint8_t *)(this + 284) != 0 )  // this+284〔bBindGate284(推断)〕
  {
    if ( (dword_9A0580 & 1) != 0 )  // 判定位掩码：dword_9A0580 & 1
    {
      v7 = (uint32_t *)dword_9A057C;
    }
    else
    {
      dword_9A0580 |= 1u;
      v6 = *(uint32_t *)dword_8F84B8;  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
      v57 = 0;
      (*(void (/*thiscall*/ **)(int, const char *))(v6 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行…
        dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
        "Character/Common/PrivateStore/Donkey/Store.img");  // 资源路径 Character/Common/PrivateStore/Donkey/Store.img
      v7 = (uint32_t *)sub_418DD0(0);  // sub_418DD0 —— 资源句柄 (101)
      dword_9A057C = (int)v7;
      v57 = -1;
    }
    v8 = nArg4 - 3 * v7[6];
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int, int, uint32_t, int, int, int))(*v7 + 128))(  // 虚调用 vt+128（v7）目标坐标y上界
      v7,
      nArg3 - (v7[5] >> 1),
      v8,
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      1065353216,
      1065353216,
      0,
      2030043135,
      1333788672,
      1333788672);
    v9 = 0;
    if ( *(uint8_t *)(*((uint32_t *)dword_8F8528 + 625) + 44) != 0 )  // dword_8F8528 —— 对象池借出（按池号取可用对象）
      v9 = sub_45E870(pt.x, pt.y, 1);  // sub_45E870 —— 结果 = 光标点选对象（倒序遍历 ·+40 表）
    if ( this == v9 )
    {
      if ( (dword_9A0580 & 2) == 0 )  // 判定位掩码：dword_9A0580 & 2
      {
        dword_9A0580 |= 2u;
        v10 = *(uint32_t *)dword_8F84B8;  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
        v57 = 1;
        (*(void (/*thiscall*/ **)(int, const char *))(v10 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79 行…
          dword_8F84B8,  // dword_8F84B8 —— 字符串 “Common/Etc/MonoLayer.img”
          "Character/Common/PrivateStore/Donkey/Store.img");  // 资源路径 Character/Common/PrivateStore/Donkey/Store.img
        dword_9A0578 = sub_418DD0(1);  // sub_418DD0 —— 资源句柄 (101)
        v57 = -1;
      }
      sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      (*(void (/*stdcall*/ **)(int, int, int))(*(uint32_t *)dword_9A0578 + 152))(  // 虚调用 vt+152（dword_9A0578）取值(参数)
        nArg3 - (*(uint32_t *)(dword_9A0578 + 20) >> 1),
        v8,
        dword_79C0B0);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
    }
    if ( *(uint8_t *)(this + 285) != 0 )  // this+285〔bField285〕
    {
      v11 = (void *)sub_422E70(1335);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      sub_4BD690(v11);  // sub_4BD690 —— 主人名字写（+304 串槽，懒建）
    }
    (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, &byte_77F8FC);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
    fld_130 = *(uint32_t **)(this + 304);  // this+304 图层/子件槽
    v58 = v8 + 10;  // 计算 v58 = v8 + 10
    if ( fld_130 != nullptr )  // fld_130=this+304 pLayer304
    {
      v13 = fld_130[6];  // fld_130=this+304 pLayer304
      if ( fld_130[5] < 0x15u )  // fld_130=this+304 pLayer304
      {
        if ( v13 < 0x10 )
          v14 = fld_130 + 1;  // 计算 v14 = fld_130 + 1
        else
          v14 = (uint32_t *)fld_130[1];  // fld_130=this+304 pLayer304
        nArg32 = nArg3;
        v16 = nArg3 - (sub_4176A0(v14) >> 1);  // sub_4176A0 —— 结果 = 文本像素宽估算（5 × 字符数）
        fld_1302 = *(uint32_t *)(this + 304);  // 读字段 fld_1302 = this+304（pLayer304）
        if ( *(uint32_t *)(fld_1302 + 24) < 0x10u )  // fld_1302=this+304 pLayer304
          v18 = fld_1302 + 4;  // 计算 v18 = fld_1302 + 4
        else
          v18 = *(uint32_t *)(fld_1302 + 4);  // 读字段 v18 = fld_1302+4（pHostObj）
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          v16,
          v8 + 18,
          -16731649,
          v18);
LABEL_36:
        fld_120 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 288) + 52))(*(uint32_t *)(this + 288));  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行…
        v29 = sub_429830(fld_120);  // sub_429830 —— 结果 = 表按键查找（uint16）
        v54 = 0;
        v55 = 0;
        Block[4] = nullptr;
        LOBYTE(Block[0]) = 0;
        v30 = v29;
        Buffer = 0;
        v52 = 15;
        sub_4015C0((void *)"Lv.", 3u);  // 【std::string构造赋值】
        v57 = 4;
        v31 = sub_41A5E0(v30 + 53);  // sub_41A5E0 —— 结果 = crypt4byte 解密校验（·0x41A590 逆运算）
        psz = _itoa(v31, &Buffer, 10);  // psz = 调 _itoa
        sub_4022F0((std::_String_base *)v50, psz, strlen(psz));  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
        sub_4022F0((std::_String_base *)v50, " ", 1);  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
        if ( *(uint32_t *)(v30 + 40) < 0x10u )
          psz2 = (const char *)(v30 + 20);
        else
          psz2 = *(const char **)(v30 + 20);
        sub_4022F0((std::_String_base *)v50, psz2, strlen(psz2));  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
        Block2 = (void **)Block[0];
        if ( v52 < 0x10 )
          Block2 = Block;
        v35 = sub_4176A0(Block2);  // sub_4176A0 —— 结果 = 文本像素宽估算（5 × 字符数）
        Block3 = (void **)Block[0];
        v37 = nArg32 - (v35 >> 1);
        if ( v52 < 0x10 )
          Block3 = Block;
        (*(void (/*cdecl*/ **)(int, int, int, int, void **))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          v37,
          v58 + 32,
          -1,
          Block3);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
        if ( v52 >= 0x10 )
        {
          v38 = Block[0];
LABEL_49:
          j__free(v38);  // 释放堆块
          return;
        }
        return;
      }
      if ( v13 < 0x10 )
        v19 = fld_130 + 1;  // 计算 v19 = fld_130 + 1
      else
        v19 = (uint32_t *)fld_130[1];  // fld_130=this+304 pLayer304
      v20 = sub_5515A0(v19, 20);  // sub_5515A0 —— 任务文本辅助（77 行）
      sub_4BD650(v42, 0, v20);  // sub_4BD650 —— std::string 拷贝构造到 pArg2
      v57 = 2;
      sub_4BD650(v45, v20, -1);  // sub_4BD650 —— std::string 拷贝构造到 pArg2
      v21 = (uint32_t *)v43[0];
      LOBYTE(v57) = 3;
      if ( v44 < 0x10 )
        v21 = v43;
      v22 = sub_4176A0(v21);  // sub_4176A0 —— 结果 = 文本像素宽估算（5 × 字符数）
      v23 = (uint32_t *)v43[0];
      v24 = nArg3 - (v22 >> 1);
      if ( v44 < 0x10 )
        v23 = v43;
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        v24,
        v58,
        -16731649,
        v23);
      v25 = (uint32_t *)v46[0];
      if ( v47 < 0x10 )
        v25 = v46;
      v26 = nArg3 - (sub_4176A0(v25) >> 1);  // sub_4176A0 —— 结果 = 文本像素宽估算（5 × 字符数）
      v27 = (uint32_t *)v46[0];
      if ( v47 < 0x10 )
        v27 = v46;
      (*(void (/*cdecl*/ **)(int, int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        v26,
        v58 + 16,
        -16731649,
        v27);
      sub_501490(v45);  // 调 对象析构后释放堆块
      v57 = -1;
      sub_501490(v42);  // 调 对象析构后释放堆块
    }
    nArg32 = nArg3;
    goto LABEL_36;
  }
  v49 = 15;
  v48[4] = 0;
  LOBYTE(v48[0]) = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  v39 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  v57 = 5;
  (*(void (/*thiscall*/ **)(int, char *))(v39 + 72))(dword_79C0B0, &byte_77F8FC);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  v40 = sub_4176A0(v48);  // sub_4176A0 —— 结果 = 文本像素宽估算（5 × 字符数）
  v41 = (uint32_t *)v48[0];
  if ( v49 < 0x10 )
    v41 = v48;
  (*(void (/*cdecl*/ **)(int, unsigned int, int, int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
    dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    nArg3 - (v40 >> 1),
    nArg4 - 26,
    -6567706,
    v41);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
  if ( v49 >= 0x10 )
  {
    v38 = (void *)v48[0];
    goto LABEL_49;
  }
}


// ------------------------------------------------------------
// 0x4BDC40 sub_4BDC40 —— 帧句柄数组析构（5 × 4 槽）
//   步长 4 遍历 5 槽（i < 20）：逐槽 ·0x42AF90 + ·0x657740(228) 回收后清 0；
//   末 j_j__free 表首（·0x4BCD50 的对称释放）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4BDC40(void **this)  // sub_4BDC40 —— 帧句柄数组析构（5 × 4 槽）
{
  int i; // esi
  int fld_e73; // eax
  int v4; // edi

  for ( i = 0; i < 20; i += 4 )
  {
    fld_e73 = (int)*(this + 73);  // this+292〔nOpenMode292(推断)〕
    v4 = *(uint32_t *)(i + fld_e73);  // fld_e73=this+292 nOpenMode292
    if ( v4 != 0 )
    {
      sub_42AF90(*(void ***)(i + fld_e73));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
      sub_657740(v4, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
    }
    *(uint32_t *)((char *)*(this + 73) + i) = 0;  // this+292〔nOpenMode292(推断)〕
  }
  j_j__free(*(this + 73));  // this+292〔nOpenMode292(推断)〕
}



// ------------------------------------------------------------
// 0x4BDCA0 sub_4BDCA0 —— 摆摊驴动画装配
//   Donkey_Stay/Eat/Bite/Walk/Run.ani → +40 槽 sub_4924C0；
//   失败 "Donkey Ani was not Created"。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BDCA0(int *this)  // sub_4BDCA0 —— 摆摊驴动画装配
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

  LOBYTE(fld_e734) = *((uint8_t *)this + 284);  // this+284〔bBindGate284(推断)〕
  if ( (uint8_t)fld_e734 == 0 )
  {
    fld_e73 = (uint32_t *)*(this + 73);  // this+292〔nOpenMode292(推断)〕
    if ( fld_e73 == nullptr )  // fld_e73=this+292 nOpenMode292
    {
      LOBYTE(fld_e734) = off_77F3FC("Donkey Ani was not Created");  // off_77F3FC —— 日志打印（printf 风格）
      return (char)fld_e734;
    }
    if ( *fld_e73 == 0 )  // fld_e73=this+292 nOpenMode292
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v4 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Stay.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v4 = 0;
      *(uint32_t *)*(this + 73) = v4;  // 写字段 this+73（szDigitalName） ← v4
    }
    if ( *(uint32_t *)(*(this + 73) + 4) == 0 )  // this+292〔nOpenMode292(推断)〕
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v5 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Eat.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v5 = 0;
      *(uint32_t *)(*(this + 73) + 4) = v5;  // this+292〔nOpenMode292(推断)〕
    }
    if ( *(uint32_t *)(*(this + 73) + 8) == 0 )  // this+292〔nOpenMode292(推断)〕
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v6 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Bite.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v6 = 0;
      *(uint32_t *)(*(this + 73) + 8) = v6;  // this+292〔nOpenMode292(推断)〕
    }
    if ( *(uint32_t *)(*(this + 73) + 12) == 0 )  // this+292〔nOpenMode292(推断)〕
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v7 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Walk.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v7 = 0;
      *(uint32_t *)(*(this + 73) + 12) = v7;  // this+292〔nOpenMode292(推断)〕
    }
    if ( *(uint32_t *)(*(this + 73) + 16) == 0 )  // this+292〔nOpenMode292(推断)〕
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v8 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Donkey_Run.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v8 = 0;
      *(uint32_t *)(*(this + 73) + 16) = v8;  // this+292〔nOpenMode292(推断)〕
    }
    if ( *(this + 40) < 0 )  // this+160〔fAdd160(推断)〕
    {
      fld_e732 = (int *)sub_4924C0(*(int **)*(this + 73), 0);  // sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      *(this + 40) = sub_4918E0(fld_e732, 2);  // sub_4918E0 —— 结果 = 动画盒四边界提取（研究 P29 族）
    }
    Time = timeGetTime();  // Time = 调 timeGetTime
    if ( *(this + 77) == 4 && *(this + 78) == 4 )  // this+77 【推断】公会标志字节 B
    {
      if ( *((uint8_t *)this + 340) == 0 )  // this+340〔pSlotTbl340〕
      {
        fld_e733 = (uint32_t *)*(this + 73);  // this+292〔nOpenMode292(推断)〕
        v12 = *this;
        *((uint8_t *)this + 340) = 1;  // 写字段 this+340（pSlotTbl340）
        *(this + 84) = Time;  // 写字段 this+84（pFxObjA） ← Time
        LOBYTE(fld_e734) = (*(int (/*thiscall*/ **)(int *, uint32_t))(v12 + 196))(this, *fld_e733);  // 调虚槽 +196：动画对象设置（换域 + 播放）
        return (char)fld_e734;
      }
      LOBYTE(fld_e734) = *((uint8_t *)this + 341);
      if ( (uint8_t)fld_e734 != 0 )
      {
        fld_e30 = *(this + 30);  // 读字段 fld_e30 = this+30
        fld_e734 = (int *)(sub_42FC90(fld_e30) - 1);  // sub_42FC90 —— 88B 元素计数（+44 组）
        if ( *(int **)(fld_e30 + 148) != fld_e734 )  // fld_e30=this+30 pAnimObj
          return (char)fld_e734;
        fld_e734 = (int *)*(this + 73);  // this+292〔nOpenMode292(推断)〕
        v14 = *fld_e734;  // fld_e734=this+292 nOpenMode292
        if ( fld_e30 == *fld_e734 )  // fld_e30=this+30 pAnimObj
        {
          (*(void (/*thiscall*/ **)(int *, int))(*this + 196))(this, fld_e734[1]);  // 虚调用 vt+196（this）物件非空判定
          fld_e302 = *(this + 30);  // 读字段 fld_e302 = this+30
          goto LABEL_38;
        }
        if ( fld_e30 == fld_e734[1] && *(uint8_t *)(fld_e30 + 170) != 0 )  // fld_e30=this+30 pAnimObj
        {
          (*(void (/*thiscall*/ **)(int *, int))(*this + 196))(this, fld_e734[2]);  // 虚调用 vt+196（this）物件非空判定
          sub_4926A0(*(this + 30));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
          fld_e734 = (int *)(rand() % 4 + 1);  // 调 取伪随机数
          *(this + 86) = (int)fld_e734;  // 写字段 this+86 ← (int)fld_e734
          return (char)fld_e734;  // fld_e734=this+292 nOpenMode292
        }
        if ( fld_e30 == fld_e734[2] )  // fld_e30=this+30 pAnimObj
        {
          LOBYTE(fld_e734) = *(uint8_t *)(fld_e30 + 170);  // fld_e734=this+292 nOpenMode292
          if ( (uint8_t)fld_e734 != 0 )  // fld_e734=this+292 nOpenMode292
          {
            fld_e86 = *(this + 86);  // 读字段 fld_e86 = this+86
            if ( fld_e86 == 0 )  // fld_e86=this+344 预约重连延迟 ms
            {
              (*(void (/*thiscall*/ **)(int *, int))(*this + 196))(this, v14);  // 虚调用 vt+196（this）物件非空判定
              LOBYTE(fld_e734) = sub_4926A0(*(this + 30));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
              *(this + 84) = Time;  // 写字段 this+84（pFxObjA） ← Time
              *((uint8_t *)this + 341) = 0;  // 写字段 this[341]（宽1字节）
              return (char)fld_e734;  // fld_e734=this+292 nOpenMode292
            }
            *(this + 86) = fld_e86 - 1;  // 写字段 this+86 ← fld_e86 - 1
            fld_e302 = fld_e30;  // fld_e302=this+30 pAnimObj
LABEL_38:
            LOBYTE(fld_e734) = sub_4926A0(fld_e302);  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
          }
        }
      }
      else if ( (int)(Time - *(this + 84)) > 6000 )  // this+84 插值起点 X
      {
        *((uint8_t *)this + 341) = 1;  // 写字段 this[341]（宽1字节）
      }
    }
    else
    {
      fld_e735 = *(this + 73);  // 读字段 fld_e735 = this+73（szDigitalName）
      if ( *(this + 83) == 4 )  // this+332〔bReservedConn〕
        v18 = *(uint32_t *)(fld_e735 + 16);  // 读字段 v18 = fld_e735+16（nChannelTypeSel）
      else
        v18 = *(uint32_t *)(fld_e735 + 12);  // 读字段 v18 = fld_e735+12（nSkillRec12）
      LOBYTE(fld_e734) = (*(int (/*thiscall*/ **)(int *, int))(*this + 196))(this, v18);  // 虚调用 vt+196（this）物件非空判定
      *((uint8_t *)this + 340) = 0;  // 写字段 this+340（pSlotTbl340）
    }
  }
  return (char)fld_e734;  // fld_e734=this+292 nOpenMode292
}


// ------------------------------------------------------------
// 0x4BE040 sub_4BE040 —— 摆摊驴 Store.ani 装配（+284）
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE040(uint8_t *this)  // sub_4BE040 —— 摆摊驴 Store.ani 装配（+284）
{
  char result; // al
  int v3; // eax

  result = *(this + 284);  // 读字段 result = this+284（bBindGate284）
  if ( result != 0 )  // result=this+284 bBindGate284
  {
    if ( *((uint32_t *)this + 74) == 0 )  // this+296〔bInitFlag296(推断)〕
    {
      if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
        v3 = sub_431860((char)"Character/Common/PrivateStore/Donkey/Store.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
      else
        v3 = 0;
      *((uint32_t *)this + 74) = v3;  // 写字段 this+74（field_004A）
    }
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 196))(this, *((uint32_t *)this + 74));  // 虚调用 vt+196（this）物件非空判定
  }
  return result;  // result=this+284 bBindGate284
}



// ------------------------------------------------------------
// 0x4BE0D0 sub_4BE0D0 —— 摆摊驴逐帧总更新（坐骑态分支）
//   nullsub_3 占位后：+284 开时 vt+112 定位（+364/+368）并 ·0x4BE040 装 Store.ani；
//   否则按 +308 状态经 vt+148/152 校正，再依序 ·0x4BD120 跟随 → ·0x4BD1F0 朝向 →
//   ·0x4BDCA0 动画 → ·0x4BD090 随机演出，末 vt+120/+124 写 +324/+328 参考位。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE0D0(int *this)  // sub_4BE0D0 —— 摆摊驴逐帧总更新（坐骑态分支）
{
  int v2; // eax
  int fld_e77; // eax
  int fld_e772; // edi
  int v5; // eax
  int v6; // edx

  nullsub_3(this);
  if ( *((uint8_t *)this + 284) != 0 )  // this+284〔bBindGate284(推断)〕
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t))(*this + 112))(this, *(this + 91), *(this + 92), 0);  // 虚调用 vt+112（this）坐标三元组写入
    LOBYTE(v2) = sub_4BE040(this);  // sub_4BE040 —— 摆摊驴 Store.ani 装配（+284）
  }
  else
  {
    fld_e77 = *(this + 77);  // 读字段 fld_e77 = this+77（bGuildFlagB）
    if ( fld_e77 != 4 )  // fld_e77=this+77 bGuildFlagB
    {
      fld_e772 = *(this + 77);  // 读字段 fld_e772 = this+77（bGuildFlagB）
      if ( fld_e77 != (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) )  // 虚调用 vt+152（this）取值(参数)
        (*(void (/*thiscall*/ **)(int *, int))(*this + 148))(this, fld_e772);  // 虚调用 vt+148（this）位置/朝向写入
    }
    sub_4BD120(this);  // sub_4BD120 —— 摆摊驴跟随目标选择（±60/180 门限）
    sub_4BD1F0(this);  // sub_4BD1F0 —— 摆摊驴朝向状态机与表现速率写入
    sub_4BDCA0(this);  // sub_4BDCA0 —— 摆摊驴动画装配
    sub_4BD090(this);  // sub_4BD090 —— 摆摊驴随机待机演出（+340 门控；8 至 11 秒随机插曲）
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
    v6 = *this;
    *(this + 81) = v5;  // 写字段 this+81 ← v5
    v2 = (*(int (/*thiscall*/ **)(int *))(v6 + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
    *(this + 82) = v2;  // 写字段 this+82 ← v2
  }
  return v2;
}



// ============================================================
// §R 0x4BE170-0x4BFFA0  杂项/容器收尾
// ============================================================
// ------------------------------------------------------------
// 0x4BE170 sub_4BE170 —— 全局标志读取（dword_9A0584）
//   返回 dword_9A0584；写入侧见 ·0x4BE180。
// ------------------------------------------------------------
int sub_4BE170()  // sub_4BE170 —— 全局标志读取（dword_9A0584）
{
  return dword_9A0584;  // 返回全局 dword_9A0584
}



// ------------------------------------------------------------
// 0x4BE180 sub_4BE180 —— 全局标志写（dword_9A0584）
//   设 dword_9A0584 = nArg1 并返回；读取侧见 ·0x4BE170。
// ------------------------------------------------------------
int /*cdecl*/ sub_4BE180(int nArg1)  // sub_4BE180 —— 全局标志写（dword_9A0584）
{
  dword_9A0584 = nArg1;
  return nArg1;
}



// ------------------------------------------------------------
// 0x4BE190 sub_4BE190 —— 串槽取值（this+8 串，等于 szPassword 时返回空）
//   ·0x40BF00(this+2*4 串, 0, *(this+7), szPassword, 0) == 0 返回 nullptr；
//   否则按 +24 < 16 判 SSO 返回仓内 +4 或堆指针。
// ------------------------------------------------------------
unsigned int */*thiscall*/ sub_4BE190(unsigned int *this)  // sub_4BE190 —— 串槽取值（this+8 串，等于 szPassword 时返回空）
{
  unsigned int *pThis_2; // esi

  pThis_2 = this + 2;
  if ( sub_40BF00((std::_String_base *)(this + 2), 0, *(this + 7), szPassword, 0) == 0 )  // sub_40BF00 —— std::string 比较（memcmp + 长度序；越界走 _Xran）
    return nullptr;
  if ( pThis_2[6] < 0x10 )
    return pThis_2 + 1;  // 返回内嵌子对象/缓冲指针（pThis_2+1）
  return (unsigned int *)pThis_2[1];
}



// ------------------------------------------------------------
// 0x4BE1C0 sub_4BE1C0 —— 重写虚表（HttpFileCallBack）
//   置 *this = HttpFileCallBack vftable。
// ------------------------------------------------------------
void /*thiscall*/ sub_4BE1C0(uint32_t *this)  // sub_4BE1C0 —— 重写虚表（HttpFileCallBack）
{
  *this = &HttpFileCallBack::`vftable';  // 构造装配 vftable：HttpFileCallBack
}



// ------------------------------------------------------------
// 0x4BE1D0 sub_4BE1D0 —— 标志读取（this+12）
//   返回 *(this+12)；写入侧见 ·0x4BE1E0。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE1D0(uint8_t *this)  // sub_4BE1D0 —— 结果 = 标志读取（this+12）
{
  return *(this + 12);  // 返回字段 this+48（pCmdVecBegin48）
}



// ------------------------------------------------------------
// 0x4BE1E0 sub_4BE1E0 —— 标志字节写侧（this+12）
//   置 this+12 并回传新值，读侧见 ·0x4BE1D0。
//   该字节即 on_receive_guild_info（·0x4BE2B0）写入的公会等级【推断】。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE1E0(uint8_t *this, char pszArg2)  // sub_4BE1E0 —— 标志字节写侧（this+12）
{
  *(this + 12) = pszArg2;  // 写字段 this+12（nSkillRec12） ← pszArg2
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4BE1F0 sub_4BE1F0 —— 下载中止回调（on_stop）
//   仅状态 +4 == 2（下载中）时记 CNRDGuildInfo::on_stop - emblem download failed. guild = %d
//   并把状态拨到 6（失败）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BE1F0(uint32_t *this)  // sub_4BE1F0 —— 下载中止回调（on_stop）
{
  int result; // eax

  if ( *(this + 1) == 2 )  // this+4〔宿主对象〕
  {
    result = off_77F3FC("CNRDGuildInfo::on_stop - emblem download failed. guild = %d", *(this + 2));  // off_77F3FC —— 日志打印（printf 风格）
    *(this + 1) = 6;  // 写字段 this+1 ← 6
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE220 sub_4BE220 —— 发起徽章下载（download_emblem）
//   状态 +4 == 1 时按工会 id（+8）拼 http://guildem.d-fighter.com:8080/guild/%d/%d/%d/%d.img
//   （id 低 5 位、除 251、除 0x1F60 三段分桶），经 ·0x4F4710 下载并置状态 2。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BE220(uint32_t *this)  // sub_4BE220 —— 发起徽章下载（download_emblem）
{
  int result; // eax
  char Buffer[1024]; // [esp+4h] [ebp-404h] BYREF
  int dword_796E502; // [esp+404h] [ebp-4h]

  result = dword_796E50;  // dword_796E50 —— 栈检 cookie
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  if ( *(this + 1) == 1 )  // this+4〔宿主对象〕
  {
    sprintf(  // 调 格式化到缓冲
      Buffer,
      "http://guildem.d-fighter.com:8080/guild/%d/%d/%d/%d.img",
      *(this + 2) & 0x1F,  // this+8 = 技能槽记录首字
      (*(this + 2) >> 5) % 251,  // this+8 = 技能槽记录首字
      *(this + 2) / 0x1F60u,  // this+8 = 技能槽记录首字
      *(this + 2));  // this+8〔nSkillRec8(推断)〕
    off_77F3FC("CNRDGuildInfo::download_emblem - %s", Buffer);  // off_77F3FC —— 日志打印（printf 风格）
    result = sub_4F4710(Buffer, (int)this, 0);  // sub_4F4710 —— HTTP 完成结果回填（弹出作业 → 写结果 → 入完成队列）
    *(this + 1) = 2;  // 写字段 this+1 ← 2
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE2B0 sub_4BE2B0 —— 公会信息到达（on_receive_guild_info）
//   入参为公会等级：> 2 记 CNRDGuildInfo::on_receive_guild_info - guild level is too big 并置失败态 6；
//   等级存 +12，非 0 置状态 1 立即下载（·0x4BE220），为 0 亦置 6。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BE2B0(int this, uint8_t uArg2)  // sub_4BE2B0 —— 公会信息到达（on_receive_guild_info）
{
  int result; // eax

  if ( uArg2 > 2u )
  {
    result = off_77F3FC("CNRDGuildInfo::on_receive_guild_info - guild level is too big. %d", uArg2);  // off_77F3FC —— 日志打印（printf 风格）
    *(uint32_t *)(this + 4) = 6;  // 写字段 this+4（pHostObj） ← 6
  }
  *(uint8_t *)(this + 12) = uArg2;  // 写字段 this+12（nSkillRec12） ← uArg2
  if ( uArg2 != 0 )
  {
    *(uint32_t *)(this + 4) = 1;  // 写字段 this+4（pHostObj） ← 1
    return sub_4BE220((uint32_t *)this);  // sub_4BE220 —— 发起徽章下载（download_emblem）
  }
  else
  {
    *(uint32_t *)(this + 4) = 6;  // 写字段 this+4（pHostObj） ← 6
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE300 sub_4BE300 —— 技能图标装载（+48 槽；sub_419480/419550）
// ------------------------------------------------------------
int /*thiscall*/ sub_4BE300(int this)  // sub_4BE300 —— 技能图标装载（+48 槽；sub_419480/419550）
{
  int v2; // edi
  uint32_t *fld_10; // ecx
  char *pMem; // eax
  char *v5; // eax
  void (/*thiscall*/ ***pThis_10)(uint32_t, int); // ecx
  const CHAR *pThis_50; // eax

  v2 = 0;
  switch ( *(uint32_t *)(this + 4) )  // 按 *(uint32_t *)(this + 4) 分派
  {
    case 3:  // case 3 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
      if ( (unsigned int)sub_699000(this + 20) > 0x7D0 )  // 【clock_now(clk)】
      {
LABEL_22:
        *(uint32_t *)(this + 4) = 1;  // 写字段 this+4（pHostObj） ← 1
        sub_4BE220((uint32_t *)this);  // sub_4BE220 —— 发起徽章下载（download_emblem）
      }
      break;
    case 4:  // case 4 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
      if ( (unsigned int)sub_699000(this + 48) > 0x3E8 )  // 【clock_now(clk)】
      {
        *(uint32_t *)(this + 4) = 5;  // 写字段 this+4（pHostObj） ← 5
        return 0;
      }
      break;
    case 5:  // case 5 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
      fld_10 = *(uint32_t **)(this + 16);  // this+64〔apServerTabBtn(推断)〕
      if ( fld_10 == nullptr )  // fld_10=this+64 apServerTabBtn
      {
        pMem = (char *)operator new(0x68u);  // 堆分配
        if ( pMem != nullptr )
          v5 = sub_419480(pMem, dword_79C0A4);  // dword_79C0A4 —— 调 vt+16 槽
        else
          v5 = nullptr;
        *(uint32_t *)(this + 16) = v5;  // 写字段 this+16（nChannelTypeSel） ← v5
        if ( sub_419550((int)v5, (size_t *)(this + 76), 1u) == 0 )  // sub_419550 —— 执行 Load
        {
          off_77F3FC("CNRDGuildInfo::get_emblem() - emblem load failed");  // off_77F3FC —— 日志打印（printf 风格）
          *(uint32_t *)(this + 4) = 6;  // 写字段 this+4（pHostObj） ← 6
          return 0;
        }
        return v2;
      }
      v2 = sub_418DD0(fld_10, 0);  // sub_418DD0 —— 资源句柄 (101)
      if ( v2 == sub_419F00() )  // sub_419F00 —— 返回占位图像
      {
        if ( *(uint8_t *)(this + 13) >= 2u )  // this+52〔bAuraState(推断)〕
          return 0;
        pThis_10 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 16);  // this+64〔apServerTabBtn(推断)〕
        if ( pThis_10 != nullptr )  // pThis_10=this+64 apServerTabBtn
          (**pThis_10)(pThis_10, 1);  // 调 pThis_10 的虚函数（vt+0）
        *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
        if ( *(uint32_t *)(this + 100) < 0x10u )  // this+100〔bEnchantDone(推断)〕
          pThis_50 = (const CHAR *)(this + 80);  // this+80 关联角色对象
        else
          pThis_50 = *(const CHAR **)(this + 80);  // this+80 关联角色对象
        DeleteFileA(pThis_50);  // pThis_50=this+80 关联角色对象
        ++*(uint8_t *)(this + 13);  // this+52〔bAuraState(推断)〕
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
// 0x4BE470 sub_4BE470 —— 徽章清理与重试重启
//   状态 +4 为 4/5/6 且 +12 非 0 时：虚调释放已载入图像（+16）、DeleteFileA 删已下载文件
//   （+76 串）、清 +33/+34，置状态 3 并复位重试时钟（+20，·0x698F90）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BE470(int this)  // sub_4BE470 —— 徽章清理与重试重启 状态 +4 为 4/5/6 且 +12 非 0 时：虚调释放已载入图像
{
  int fld_4; // eax
  void (/*thiscall*/ ***pThis_10)(uint32_t, int); // ecx
  const CHAR *pThis_50; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 == 5 || fld_4 == 6 || fld_4 == 4 )  // 判定 fld_4 == 5 或 fld_4 == 6 或 fld_4 == 4
  {
    LOBYTE(fld_4) = *(uint8_t *)(this + 12);  // this+12〔nSkillRec12(推断)〕等 2 字段
    if ( (uint8_t)fld_4 != 0 )  // fld_4=this+4 pHostObj
    {
      pThis_10 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 16);  // this+64〔apServerTabBtn(推断)〕
      if ( pThis_10 != nullptr )  // pThis_10=this+64 apServerTabBtn
        (**pThis_10)(pThis_10, 1);  // 调 pThis_10 的虚函数（vt+0）
      *(uint32_t *)(this + 16) = 0;  // 写字段 this+16（nChannelTypeSel） ← 0
      if ( *(uint32_t *)(this + 100) < 0x10u )  // this+100〔bEnchantDone(推断)〕
        pThis_50 = (const CHAR *)(this + 80);  // this+80 关联角色对象
      else
        pThis_50 = *(const CHAR **)(this + 80);  // this+80 关联角色对象
      DeleteFileA(pThis_50);  // pThis_50=this+80 关联角色对象
      *(uint32_t *)(this + 4) = 3;  // 写字段 this+4（pHostObj） ← 3
      *(uint8_t *)(this + 33) = 0;  // 写字段 this+33（bJobVecDirty） ← 0
      *(uint8_t *)(this + 34) = 0;  // 写字段 this+34 ← 0
      LOBYTE(fld_4) = sub_698F90(this + 20, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  return fld_4;  // fld_4=this+4 pHostObj
}



// ------------------------------------------------------------
// 0x4BE4E0 sub_4BE4E0 —— 红黑树整树释放
//   每节点先递归释放右子树（+8）再沿左链（+0）j__free；+21 为 nil 哨兵标志（循环终止）。
// ------------------------------------------------------------
char /*stdcall*/ sub_4BE4E0(void **Block)  // sub_4BE4E0 —— 红黑树整树释放
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);  // 读字段 result = Block+21（bArmorState）
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_4BE4E0(i[2]);  // sub_4BE4E0 —— 红黑树整树释放
    i = (void **)*i;
    j__free(Block2);  // 释放堆块
    result = *((uint8_t *)i + 21);  // 读字段 result = i+21（bArmorState）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BE520 sub_4BE520 —— 映射下界查找（lower_bound）
//   键在节点 +12（值对首元，无符号比较）；回传首个键不小于 *uArg3 的节点，未命中回哨兵头
//   （映射头在 +4，·0x4BF200 分配）。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4BE520(int **this, int **pDwArg2, uint32_t *uArg3)  // sub_4BE520 —— 结果 = 映射下界查找（lower_bound）
{
  int *fld_e1; // edx
  int *v4; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v4 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *((uint8_t *)v4 + 21) == 0 )  // 当 *((uint8_t *)v4 + 21) == 0 循环
  {
    if ( (unsigned int)v4[3] >= *uArg3 )
    {
      fld_e1 = v4;  // fld_e1=this+4 宿主对象
      v4 = (int *)*v4;
    }
    else
    {
      v4 = (int *)v4[2];
    }
  }
  if ( fld_e1 == *(this + 1) || *uArg3 < (unsigned int)fld_e1[3] )  // this+4〔宿主对象〕
  {
    *pDwArg2 = *(this + 1);  // this+4〔宿主对象〕
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = fld_e1;  // fld_e1=this+4 宿主对象
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4BE590 sub_4BE590 —— CNRDGuildInfo 析构
//   置 CNRDGuildInfo 虚表后销毁 +16 徽章图像对象；+76 串容量 >= 16 释放堆缓冲并复位空短串；
//   内嵌子对象（+20/+48）虚表退回 nengine::IObject，本对象再回退到基类 HttpFileCallBack。
// ------------------------------------------------------------
void **/*thiscall*/ sub_4BE590(void *this)  // sub_4BE590 —— CNRDGuildInfo 析构
{
  void (/*thiscall*/ ***pThis_4)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNRDGuildInfo::`vftable';  // 构造装配 vftable：CNRDGuildInfo
  v2 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 4);  // this+4 宿主对象
  if ( v2 != nullptr )
    (**v2)(v2, 1);  // 调 v2 的虚函数（vt+0）
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  if ( *((uint32_t *)this + 25) >= 0x10u )  // this+100〔bEnchantDone(推断)〕
    j__free(*((void **)this + 20));  // 释放堆块
  *((uint32_t *)this + 24) = 0;  // 写字段 this+24（nPageMax）
  *((uint32_t *)this + 25) = 15;  // 写字段 this[25]（宽4字节）
  *((uint8_t *)this + 80) = 0;  // 写字段 this+80（nAuraStage）
  *((uint8_t *)this + 52) = 0;  // 写字段 this+52（bAuraState）
  *((uint32_t *)this + 12) = &nengine::IObject::`vftable';  // 写字段 this+12（nSkillRec12）
  *((uint8_t *)this + 24) = 0;  // 写字段 this+24（nPageMax）
  *((uint32_t *)this + 5) = &nengine::IObject::`vftable';  // 写字段 this[5]（宽4字节）
  *(uint32_t *)this = &HttpFileCallBack::`vftable';  // 构造装配 vftable：HttpFileCallBack
  return &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x4BE620 sub_4BE620 —— 映射整体清空
//   按序遍历释放各值对象（节点 +16，·0x4BE590 析构后 j__free），再沿左链递归释放全部节点
//   （·0x4BE4E0），头哨兵三向自指、计数（+12）清零。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BE620(uint32_t *this)  // sub_4BE620 —— 映射整体清空
{
  int *fld_e2; // ecx
  int v3; // eax
  void *v4; // esi
  uint32_t *fld_e22; // ebx
  uint32_t *pThis_1; // edi
  uint32_t *i; // esi
  uint32_t *result; // eax
  int *v9; // [esp+Ch] [ebp-4h] BYREF

  fld_e2 = (int *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  v3 = *fld_e2;  // fld_e2=this+8 nSkillRec8
  v9 = (int *)*fld_e2;  // fld_e2=this+8 nSkillRec8
  if ( v9 != fld_e2 )  // fld_e2=this+8 nSkillRec8
  {
    do
    {
      v4 = *(void **)(v3 + 16);
      if ( v4 != nullptr )
      {
        sub_4BE590(*(void **)(v3 + 16));  // sub_4BE590 —— CNRDGuildInfo 析构
        j__free(v4);  // 释放堆块
      }
      sub_41C5E0((int *)&v9);  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
      v3 = (int)v9;
    }
    while ( v9 != (int *)*(this + 2) );  // this+8〔nSkillRec8(推断)〕
  }
  fld_e22 = *(uint32_t **)(*(this + 2) + 4);  // this+8〔nSkillRec8(推断)〕
  pThis_1 = this + 1;
  for ( i = fld_e22; *((uint8_t *)i + 21) == 0; fld_e22 = i )  // fld_e22=this+8 nSkillRec8
  {
    sub_4BE4E0((void **)i[2]);  // sub_4BE4E0 —— 红黑树整树释放
    i = (uint32_t *)*i;
    j__free(fld_e22);  // 释放堆块
  }
  *(uint32_t *)(pThis_1[1] + 4) = pThis_1[1];
  result = (uint32_t *)pThis_1[1];
  pThis_1[2] = 0;
  *result = result;
  *(uint32_t *)(pThis_1[1] + 8) = pThis_1[1];
  return result;
}



// ------------------------------------------------------------
// 0x4BE6B0 sub_4BE6B0 —— 模式字节设置（+0）
//   与 +0 现值不同才先整体清空映射（·0x4BE620）再写入新值；用于切换登记集合【推断】。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BE6B0(uint32_t *this, char pszArg2)  // sub_4BE6B0 —— 模式字节设置（+0）
{
  uint32_t *result; // eax

  if ( *(uint8_t *)this != pszArg2 )
    result = sub_4BE620(this);  // sub_4BE620 —— 映射整体清空
  *(uint8_t *)this = pszArg2;  // *this = pszArg2
  return result;
}



// ------------------------------------------------------------
// 0x4BE6D0 sub_4BE6D0 —— 红黑树单节点删除（_Erase）
//   标准摘链 + 双黑重平衡（·0x433130 左旋 / ·0x4296E0 右旋；节点 0x18，色位 +20、nil +21），
//   计数 +8 自减并 j__free；入参为哨兵时抛 out_of_range（invalid map/set<T> iterator）。
// ------------------------------------------------------------
int ***/*thiscall*/ sub_4BE6D0(uint32_t *this, int ***uArg2, int **pDwArg3)  // sub_4BE6D0 —— 红黑树单节点删除（_Erase）
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
    sub_401740(pExceptionObject, (int)v20);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::out_of_range::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0(&pDwArg3);  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
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
      *(uint32_t *)(v8 + 4) = v4;  // 写字段 v8+4（pHostObj） ← v4
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
        v9 = (int *)sub_52E300(v4);  // sub_52E300 —— v9 = sub_52E300(v4) 最左
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;  // 写字段 v10+8（nSkillRec8） ← = (uint32_t)pDwArg32
    v23 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;  // 写字段 v10+8（nSkillRec8） ← v6
      else
        *(uint32_t *)(v23 + 8) = sub_542490(v4);  // sub_542490 —— 表头+8 = sub_542490(v4) 最右
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
    *(uint32_t *)(v12 + 4) = v5;  // 写字段 v12+4（pHostObj） ← v5
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
  v14 = *((uint8_t *)v5 + 20);  // 读字段 v14 = v5+20（nPage）
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);  // 写字段 v5+20（nPage）
  *((uint8_t *)pDwArg32 + 20) = v14;  // 写字段 pDwArg32+20（nPage）
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
            *((uint8_t *)v16 + 20) = 1;  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 0;  // 写字段 v6+20（nPage）
            sub_433130(v6);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
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
              *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
              sub_4296E0(v16);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 1;  // 写字段 v6+20（nPage）
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 0;  // 写字段 v6+20（nPage）
            sub_4296E0(v6);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
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
              *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
              sub_433130(v16);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);  // 写字段 v16+20（nPage）
            *((uint8_t *)v6 + 20) = 1;  // 写字段 v6+20（nPage）
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;  // 写字段 v16+20（nPage）
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;  // 写字段 v4+20（nPage）
  }
  j__free(Block);  // 释放堆块
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x4BE990 sub_4BE990 —— CNRDGuildInfo 构造（构造即发请求）
//   置虚表、两内嵌对象（+20/+48，·off_6C2B88）与 +76 串初值（szPassword），状态 +4 / +12(0xFF) /
//   +13 重试计数归零；随即 ·0x423200(dword_8F7B08, 77) 开局、·0x423290 写 4 字节工会 id、·0x423380 发包。
// ------------------------------------------------------------
char */*thiscall*/ sub_4BE990(char *this, int nArg2)  // sub_4BE990 —— CNRDGuildInfo 构造（构造即发请求）
{
  char *pThis_4C; // ecx
  int nArg22; // edi

  *(uint32_t *)this = &CNRDGuildInfo::`vftable';  // 构造装配 vftable：CNRDGuildInfo
  *(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *((uint32_t *)this + 5) = &off_6C2B88;  // 写字段 this[5]（宽4字节）
  *((uint32_t *)this + 7) = 0;  // 写字段 this+7（uPathTerm）
  *(this + 32) = 1;  // 写字段 this+32（nHeight） ← 1
  *(this + 34) = 0;  // 写字段 this+34 ← 0
  *(this + 33) = 0;  // 写字段 this+33（bJobVecDirty） ← 0
  *((uint32_t *)this + 11) = 0;  // 写字段 this[11]（宽4字节）
  *((uint32_t *)this + 10) = 0;  // 写字段 this[10]（宽4字节）
  *((uint32_t *)this + 9) = 0;  // 写字段 this[9]（宽4字节）
  *(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  *((uint32_t *)this + 12) = &off_6C2B88;  // 写字段 this+12（nSkillRec12）
  *((uint32_t *)this + 14) = 0;  // 写字段 this[14]（宽4字节）
  *(this + 60) = 1;  // 写字段 this+60（nFadeValue60） ← 1
  *(this + 62) = 0;  // 写字段 this+62（bReadyFlagB） ← 0
  *(this + 61) = 0;  // 写字段 this+61（bReadyFlagA） ← 0
  *((uint32_t *)this + 18) = 0;  // 写字段 this+18（bDragChild）
  *((uint32_t *)this + 17) = 0;  // 写字段 this+17（bEnable）
  *((uint32_t *)this + 16) = 0;  // 写字段 this+16（nChannelTypeSel）
  pThis_4C = this + 76;  // this+76〔pBtnActionE〕
  *((uint32_t *)pThis_4C + 6) = 15;  // 写字段 pThis_4C[6]（宽4字节）
  *((uint32_t *)pThis_4C + 5) = 0;  // 写字段 pThis_4C[5]（宽4字节）
  pThis_4C[4] = 0;  // pThis_4C=this+76 pBtnActionE
  nArg22 = nArg2;
  *((uint32_t *)this + 2) = nArg2;  // 写字段 this[2]（宽4字节）
  *((uint32_t *)this + 4) = 0;  // 写字段 this+4（pHostObj）
  sub_4015C0((size_t *)pThis_4C, szPassword, 0);  // 【std::string构造赋值】
  *(this + 12) = -1;  // 写字段 this+12（nSkillRec12） ← -1
  *((uint32_t *)this + 1) = 0;  // 写字段 this[1]（宽4字节）
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  sub_423200(dword_8F7B08, 77);  // 【发送网络包API】
  nArg2 = nArg22;
  sub_423290(&nArg2, 4);  // sub_423290 —— 写 4B 长度
  sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
  return this;
}



// ------------------------------------------------------------
// 0x4BEA70 sub_4BEA70 —— 下载完成回调（on_complete）
//   状态 +4 == 2 时打印文件名并校验：串长 < 4 或末 3 字符不等于 ·off_6F6B58 则置状态 6；
//   通过则存 +76 串、置状态 4、清 +61/+62 并复位加载时钟（+48）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4BEA70(int this, char *Src)  // sub_4BEA70 —— 下载完成回调（on_complete）
{
  int nLen; // eax

  if ( *(uint32_t *)(this + 4) == 2 )  // this+4〔宿主对象〕等 2 字段
  {
    off_77F3FC(  // off_77F3FC —— 日志打印（printf 风格）
      "CNRDGuildInfo::on_complete - emblem download complete.\n\tguild = %d, filename = %s",
      *(uint32_t *)(this + 8),  // this+8 公会 id
      Src);
    nLen = strlen(Src);  // nLen = 调 strlen
    if ( nLen < 4 )
    {
      off_77F3FC("CNRDGuildInfo::on_complete - filename is too short");  // off_77F3FC —— 日志打印（printf 风格）
LABEL_4:
      *(uint32_t *)(this + 4) = 6;  // 写字段 this+4（pHostObj） ← 6
      return;
    }
    if ( strcmp(&Src[nLen - 3], (const char *)&off_6F6B58) != 0 )  // 调 串比较
    {
      off_77F3FC("CNRDGuildInfo::on_complete - invalid file extension");  // off_77F3FC —— 日志打印（printf 风格）
      goto LABEL_4;
    }
    sub_4015C0((size_t *)(this + 76), Src, strlen(Src));  // 【std::string构造赋值】
    *(uint32_t *)(this + 4) = 4;  // 写字段 this+4（pHostObj） ← 4
    *(uint8_t *)(this + 61) = 0;  // 写字段 this+61（bReadyFlagA） ← 0
    *(uint8_t *)(this + 62) = 0;  // 写字段 this+62（bReadyFlagB） ← 0
    sub_698F90(this + 48, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
}



// ------------------------------------------------------------
// 0x4BEB30 sub_4BEB30 —— 红黑树节点插入（_Insert）
//   计数达 0x1FFFFFFE 抛 length_error（map/set<T> too long）；·0x5648C0 建 0x18 节点后
//   按 pszArg3 与键比较挂左/右子并自平衡（·0x433130 / ·0x4296E0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BEB30(uint32_t *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, int nArg5)  // sub_4BEB30 —— 红黑树节点插入（_Insert）
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

  if ( *(this + 2) >= 0x1FFFFFFEu )  // this+8〔nSkillRec8(推断)〕
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  fld_e1 = sub_5648C0(*(this + 1), pArg4, *(this + 1), nArg5, 0);  // sub_5648C0 —— 商店文本（23 行）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( pArg4 == fld_e12 )  // fld_e12=this+4 宿主对象
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    *(uint32_t *)*(this + 1) = fld_e1;  // 写字段 this+1 ← fld_e1
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == (uint32_t *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // 写字段 fld_e14+8（nSkillRec8） ← fld_e1
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
            sub_433130(*v10);  // sub_433130 —— 红黑树左旋（节点 0x18 版）
          }
          *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
          sub_4296E0(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_4296E0 —— STL 内联红黑树节点摘除重连
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 20) != 0 )
      {
        if ( fld_e16 == *v12 )
        {
          fld_e16 = *v10;
          sub_4296E0(*v10);  // sub_4296E0 —— STL 内联红黑树节点摘除重连
        }
        *(uint8_t *)(*(uint32_t *)(fld_e16 + 4) + 20) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4) + 20) = 0;
        sub_433130(*(uint32_t *)(*(uint32_t *)(fld_e16 + 4) + 4));  // sub_433130 —— 红黑树左旋（节点 0x18 版）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 20) = 1;
      *(uint8_t *)(v14 + 20) = 1;  // 写字段 v14+20（nPage） ← 1
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
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 20) = 1;  // this+4〔宿主对象〕
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4BECE0 sub_4BECE0 —— 红黑树区间删除（_Erase(first, last)）
//   区间即全树（首节点与哨兵头）时直接 ·0x4BE4E0 整树释放，否则逐节点迭代推进调 ·0x4BE6D0。
// ------------------------------------------------------------
int **/*thiscall*/ sub_4BECE0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)  // sub_4BECE0 —— 红黑树区间删除（_Erase(first, last)）
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
  fld_e1 = (int)*(this + 1);  // this+4〔宿主对象〕
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )  // fld_e1=this+4 宿主对象
  {
    sub_4BE4E0(*(void ***)(fld_e1 + 4));  // sub_4BE4E0 —— 红黑树整树释放
    (*(this + 1))[1] = (int *)*(this + 1);  // this+4〔宿主对象〕
    fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
    *(this + 2) = nullptr;  // 写字段 this+2 ← nullptr
    *fld_e12 = fld_e12;  // fld_e12=this+4 宿主对象
    (*(this + 1))[2] = (int *)*(this + 1);  // this+4〔宿主对象〕
    *pDwArg2 = **(this + 1);  // this+4〔宿主对象〕
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
        sub_4BE6D0(this, (int ***)&pDwArg3, v10);  // sub_4BE6D0 —— 红黑树单节点删除（_Erase）
      }
      while ( pDwArg32 != pDwArg42 );  // 循环直到 pDwArg32 != pDwArg42
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x4BEDA0 sub_4BEDA0 —— 映射插入（去重 insert）
//   ·0x4BE520 下界定位：命中即回既有节点；未命中经 ·0x4BEB30 建节点，首/末位以 ·0x4A3B30
//   前驱修正；出参 +4 字节回传是否新插入。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BEDA0(uint32_t *this, int pArg2, uint32_t *uArg3)  // sub_4BEDA0 —— 映射插入（去重 insert）
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
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v6 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 21) == 0 )
  {
    v8 = *uArg3;
    do
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 21) == 0 );
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  uArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_4BEB30(this, &uArg3, 1, fld_e1, (int)uArg32);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
      *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_4A3B30(&uArg3);  // 调 取后继再插
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // 写字段 pArg2+4（pHostObj） ← 0
    *(uint32_t *)pArg2 = fld_e12;  // *pArg2 = fld_e12
    return pArg2;
  }
  else
  {
    v12 = *sub_4BEB30(this, &uArg3, v13, fld_e1, (int)uArg32);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // 写字段 pArg2+4（pHostObj） ← 1
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x4BEE60 sub_4BEE60 —— 带提示插入（_Insert_hint）
//   按提示节点 pArg3 与键的关系走头/尾/左/右四种挂接（·0x4A3B30 前驱、·0x41C5E0 迭代步进），
//   提示失效时退化到 ·0x4BEDA0 无提示插入。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BEE60(int this, uint32_t *uArg2, uint32_t *pArg3, uint32_t *pArg4)  // sub_4BEE60 —— 带提示插入（_Insert_hint）
{
  uint32_t *fld_4; // eax
  uint32_t *pArg42; // esi
  uint32_t *v8; // eax
  int v9; // ecx
  uint8_t v10[8]; // [esp+8h] [ebp-8h] BYREF

  if ( *(uint32_t *)(this + 8) == 0 )  // this+8〔nSkillRec8(推断)〕等 2 字段
  {
    sub_4BEB30((uint32_t *)this, uArg2, 1, *(uint32_t **)(this + 4), (int)pArg4);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
    return uArg2;
  }
  fld_4 = *(uint32_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  pArg42 = pArg4;
  if ( pArg3 == (uint32_t *)*fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    if ( *pArg4 < pArg3[3] )
    {
      sub_4BEB30((uint32_t *)this, uArg2, 1, pArg3, (int)pArg4);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( pArg3 == fld_4 )  // fld_4=this+16 nChannelTypeSel
  {
    v8 = (uint32_t *)fld_4[2];  // fld_4=this+16 nChannelTypeSel
    if ( v8[3] < *pArg4 )
    {
      sub_4BEB30((uint32_t *)this, uArg2, 0, v8, (int)pArg4);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
      return uArg2;
    }
    goto LABEL_22;
  }
  if ( *pArg4 >= pArg3[3] || (pArg4 = pArg3, sub_4A3B30(&pArg4), pArg4[3] >= *pArg42) )  // 调 取后继再插
  {
    if ( pArg3[3] >= *pArg42 || (pArg4 = pArg3, sub_41C5E0((int *)&pArg4), pArg4 != *(uint32_t **)(this + 4)) && *pArg42 >= pArg4[3] )  // sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
    {
LABEL_22:
      v9 = *(uint32_t *)sub_4BEDA0((uint32_t *)this, (int)v10, pArg42);  // sub_4BEDA0 —— 映射插入（去重 insert）
      *uArg2 = v9;
      return uArg2;
    }
    if ( *(uint8_t *)(pArg3[2] + 21) != 0 )
      sub_4BEB30((uint32_t *)this, uArg2, 0, pArg3, (int)pArg42);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
    else
      sub_4BEB30((uint32_t *)this, uArg2, 1, pArg4, (int)pArg42);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
    return uArg2;
  }
  else
  {
    if ( *(uint8_t *)(pArg4[2] + 21) != 0 )
      sub_4BEB30((uint32_t *)this, uArg2, 0, pArg4, (int)pArg42);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
    else
      sub_4BEB30((uint32_t *)this, uArg2, 1, pArg3, (int)pArg42);  // sub_4BEB30 —— 红黑树节点插入（_Insert）
    return uArg2;
  }
}



// ------------------------------------------------------------
// 0x4BEFC0 sub_4BEFC0 —— 映射取项（operator[]）
//   键命中回节点 +16 值槽；未命中经 ·0x4BEE60 以初值 {键, 0} 插入后回同槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BEFC0(uint32_t *this, uint32_t *uArg2)  // sub_4BEFC0 —— 映射取项（operator[]）
{
  uint32_t *fld_e1; // edx
  int *v3; // eax
  uint32_t v5[2]; // [esp+Ch] [ebp-8h] BYREF

  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v3 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  while ( *((uint8_t *)v3 + 21) == 0 )  // 当 *((uint8_t *)v3 + 21) == 0 循环
  {
    if ( (unsigned int)v3[3] >= *uArg2 )
    {
      fld_e1 = v3;  // fld_e1=this+4 宿主对象
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  if ( fld_e1 != (uint32_t *)*(this + 1) && *uArg2 >= fld_e1[3] )  // fld_e1=this+4 宿主对象
    return (int)(fld_e1 + 4);  // fld_e1=this+4 宿主对象
  v5[0] = *uArg2;
  v5[1] = 0;
  return *sub_4BEE60((int)this, &uArg2, fld_e1, v5) + 16;  // sub_4BEE60 —— 带提示插入（_Insert_hint）
}



// ------------------------------------------------------------
// 0x4BF040 sub_4BF040 —— 映射对象全清（含头哨兵）
//   ·0x4BECE0 清空全部节点后 j__free 头哨兵（+4）并清零 +4/+8；不析构值对象（见 ·0x4BE620）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BF040(int this)  // sub_4BF040 —— 映射对象全清（含头哨兵）
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_4BECE0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));  // sub_4BECE0 —— 红黑树区间删除（_Erase(first, last)）
  j__free(*(void **)(this + 4));  // 释放堆块
  *(uint32_t *)(this + 4) = 0;  // 写字段 this+4（pHostObj） ← 0
  *(uint32_t *)(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x4BF080 sub_4BF080 —— 管理器映射清空
//   先 ·0x4BE620 释放全部值对象与节点，再补区间删除并 j__free 头哨兵（+8）、清零 +8/+12。
// ------------------------------------------------------------
void /*thiscall*/ sub_4BF080(int *this)  // sub_4BF080 —— 管理器映射清空
{
  int *pThis; // esi
  int *v2; // eax
  int *v3; // [esp-8h] [ebp-1Ch]
  int *pThis2; // [esp+4h] [ebp-10h] BYREF
  int v5; // [esp+10h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  v5 = 0;
  sub_4BE620(this);  // sub_4BE620 —— 映射整体清空
  v2 = (int *)pThis[2];
  ++pThis;  // 计数自增 pThis
  v3 = (int *)*v2;
  v5 = -1;
  sub_4BECE0((int ***)pThis, &pThis2, v3, v2);  // sub_4BECE0 —— 红黑树区间删除（_Erase(first, last)）
  j__free((void *)pThis[1]);  // 释放堆块
  pThis[1] = 0;
  pThis[2] = 0;
}



// ------------------------------------------------------------
// 0x4BF0F0 sub_4BF0F0 —— 取或建工会信息对象（get_or_create）
//   键命中直接回值指针；未命中 new 0x68 字节经 ·0x4BE990 构造（构造即发请求包），再经
//   ·0x4BEDA0 以 {键, 对象指针} 对插入（栈上 v10/v11 相邻）【推断】。
// ------------------------------------------------------------
int */*thiscall*/ sub_4BF0F0(int this, void *Block)  // sub_4BF0F0 —— 结果 = 取或建工会信息对象（get_or_create）
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
  pThis_4 = (uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
  if ( *sub_4BE520((int **)(this + 4), &v11, &Block) != *(int **)(this + 8) )  // sub_4BE520 —— 结果 = 映射下界查找（lower_bound）
    return *(int **)sub_4BEFC0((uint32_t *)(this + 4), &Block);  // sub_4BEFC0 —— 映射取项（operator[]）
  pMem = operator new(0x68u);  // 堆分配
  Block = pMem;
  v12 = 0;
  if ( pMem != nullptr )
    v7 = (int *)sub_4BE990((char *)pMem, v2);  // sub_4BE990 —— CNRDGuildInfo 构造（构造即发请求）
  else
    v7 = nullptr;
  v8 = v7;
  v11 = v7;
  v12 = -1;
  v10 = v2;
  sub_4BEDA0(pThis_4, (int)v9, &v10);  // sub_4BEDA0 —— 映射插入（去重 insert）
  return v8;
}



// ------------------------------------------------------------
// 0x4BF1B0 sub_4BF1B0 —— 按工会 id 查值指针
//   键为 0 或未命中回 0，否则回值槽（节点 +16）所存对象指针。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BF1B0(int **this, int nArg2)  // sub_4BF1B0 —— 按工会 id 查值指针
{
  int *v4; // [esp+4h] [ebp-4h] BYREF

  if ( nArg2 == 0 )
    return 0;
  if ( *sub_4BE520(this + 1, &v4, &nArg2) == *(this + 2) )  // sub_4BE520 —— 结果 = 映射下界查找（lower_bound）
    return 0;
  return *(uint32_t *)sub_4BEFC0(this + 1, &nArg2);  // sub_4BEFC0 —— 映射取项（operator[]）
}



// ------------------------------------------------------------
// 0x4BF200 sub_4BF200 —— 管理器映射初始化
//   ·0x433AC0 分配 0x18 头哨兵并左/父/右三向自指，计数（+12）清零；+0 置 0xFF 表未设模式
//   （与 ·0x4BE6B0 配对）【推断】。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_4BF200(uint8_t *this)  // sub_4BF200 —— 管理器映射初始化
{
  uint8_t *pThis_4; // esi
  int pThis_42; // eax

  pThis_4 = this + 4;  // this+4 宿主对象
  pThis_42 = sub_433AC0(this + 4);  // sub_433AC0 —— 结果 = map 节点分配（0x18）
  *((uint32_t *)pThis_4 + 1) = pThis_42;  // 写字段 pThis_4[1]（宽4字节）
  *(uint8_t *)(pThis_42 + 21) = 1;  // 写字段 pThis_42+21（bArmorState） ← 1
  *(uint32_t *)(*((uint32_t *)pThis_4 + 1) + 4) = *((uint32_t *)pThis_4 + 1);  // pThis_4=this+4 宿主对象
  **((uint32_t **)pThis_4 + 1) = *((uint32_t *)pThis_4 + 1);  // pThis_4=this+4 宿主对象
  *(uint32_t *)(*((uint32_t *)pThis_4 + 1) + 8) = *((uint32_t *)pThis_4 + 1);  // pThis_4=this+4 宿主对象
  *((uint32_t *)pThis_4 + 2) = 0;  // 写字段 pThis_4[2]（宽4字节）
  *this = -1;
  return this;
}



// ------------------------------------------------------------
// 0x4BF240 sub_4BF240 —— 槽标志区复位
//   置 +60 = 10000（0x2710 阈值）与 +64..67 四字节全 1（单槽写侧 ·0x4BF300、查询 ·0x4BF250）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4BF240(uint32_t *this)  // sub_4BF240 —— 槽标志区复位
{
  *(this + 16) = 16843009;  // 写字段 this+16（nChannelTypeSel） ← 16843009
  *(this + 15) = 10000;  // 写字段 this+15 ← 10000
}



// ------------------------------------------------------------
// 0x4BF250 sub_4BF250 —— 槽查询（+64 表）
//   索引 >= 4 记 aCriticalError_12 回 0，槽值为 0 亦回 0；槽 0 转外部查询 dword_79C0B4(vt+20)
//   与 dword_79C0B8(vt+20/+24)，槽 1 读 byte_89D274/275【推断】。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BF250(uint8_t *this, uint32_t *pArg2)  // sub_4BF250 —— 结果 = 槽查询（+64 表）
{
  int v2; // eax
  bool v4; // bl
  char v5; // al
  char byte_89D2742; // al

  v2 = *pArg2;
  if ( (int)*pArg2 >= 4 )
  {
    off_77F3FC(aCriticalError_12, *pArg2);  // off_77F3FC —— 日志打印（printf 风格）
    return 0;
  }
  if ( *(this + v2 + 64) == 0 )
    return 0;
  v4 = false;
  if ( v2 == 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B4 + 20))(dword_79C0B4, pArg2[1]);  // 虚调用 vt+20（dword_79C0B4）条件位掩码测试(273受击/17有血/65机械)
    v4 = v5 != 0;
    if ( dword_79C0B8 == 0 )  // dword_79C0B8 —— 驱动设备 dword_79C0B8 vt+12
      return v4;
    if ( v5 != 0 )
      return v4;
    v4 = (*(uint8_t (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_79C0B8 + 20))(pArg2[1]) != 0;  // 虚调用 vt+20（dword_79C0B8）条件位掩码测试(273受击/17有血/65机械)
    if ( pArg2[1] < 4u )
      return v4;
    byte_89D2742 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_79C0B8 + 24))(dword_79C0B8, pArg2[1]);  // 虚调用 vt+24（dword_79C0B8）（析构，参 1）与 8（Release）释放后 GlobalFree 并 SetWindowLongA 摘除 —— 与 ·0x6528C0 挂载配对。
    goto LABEL_13;
  }
  if ( v2 == 1 )
  {
    byte_89D2742 = byte_89D274;  // byte_89D2742 —— [esp+27h] [ebp-Dh]
    if ( pArg2[1] != 0 )
      byte_89D2742 = byte_89D275;  // byte_89D2742 —— [esp+27h] [ebp-Dh]
LABEL_13:
    if ( byte_89D2742 != 0 )  // byte_89D2742 —— [esp+27h] [ebp-Dh]
      return 1;  // 返回 1(成功)
  }
  return v4;
}



// ------------------------------------------------------------
// 0x4BF300 sub_4BF300 —— 槽写侧（+64 + 索引）
//   置单字节并回传；批量复位见 ·0x4BF240、查询见 ·0x4BF250。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BF300(uint8_t *this, int pArg2, char pszArg3)  // sub_4BF300 —— 槽写侧（+64 + 索引）
{
  *(this + pArg2 + 64) = pszArg3;
  return pszArg3;
}



// ------------------------------------------------------------
// 0x4BF320 sub_4BF320 —— 转发壳
//   纯转 ·0x5043F0（三参内存搬移族，·0x4BFD40 原地收缩路径调用）【推断】。
// ------------------------------------------------------------
int /*cdecl*/ sub_4BF320(int nArg1, int nArg2, int nArg3)  // sub_4BF320 —— 转发壳
{
  return sub_5043F0(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x4BF340 sub_4BF340 —— 16 字节元素填充
//   把 pArg3 的 4 个字写成 uArg2 份、步进 16 字节，返回尾后指针（·0x4BFD40 扩容填值）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4BF340(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // sub_4BF340 —— 16 字节元素填充
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
        result[1] = pArg3[1];  // result[1] = 取 pArg3[1]
        result[2] = pArg3[2];  // result[2] = 取 pArg3[2]
        result[3] = pArg3[3];  // result[3] = 取 pArg3[3]
      }
      result += 4;
      uArg22 = (uint32_t *)((char *)uArg22 - 1);
    }
    while ( uArg22 != nullptr );  // 循环直到 uArg22 != nullptr
  }
  return result;
}



// ------------------------------------------------------------
// 0x4BF380 sub_4BF380 —— 列表状态互斥刷新
//   先调本对象 ·vmt+112，再遍历 +84 哨兵列表逐项 ·vmt+116 刷新；首个状态（记录 +36）为 1
//   或 2 的元素之后，其余项 +36 清零（单选语义）【推断】。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4BF380(uint32_t *this)  // sub_4BF380 —— 列表状态互斥刷新
{
  uint32_t *result; // eax
  uint32_t *v3; // esi
  char v4; // bl

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 112))(this);  // 虚调用 vt+112（this）坐标三元组写入
  result = (uint32_t *)*(this + 21);  // this+84〔pFxObjA(推断)〕
  v3 = (uint32_t *)*result;  // result=this+84 pFxObjA
  v4 = 0;
  if ( (uint32_t *)*result != result )  // result=this+84 pFxObjA
  {
    do
    {
      if ( v4 != 0 )
      {
        *(uint32_t *)(v3[2] + 36) = 0;
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 116))(this, v3[2]);  // 虚调用 vt+116（this）并透传返回值 —— vt+120 槽的缺省参数包装。
        result = *(uint32_t **)(v3[2] + 36);  // result=this+84 pFxObjA
        if ( result == (uint32_t *)1 || result == (uint32_t *)2 )  // result=this+84 pFxObjA
          v4 = 1;
      }
      v3 = (uint32_t *)*v3;
    }
    while ( v3 != (uint32_t *)*(this + 21) );  // this+84〔pFxObjA(推断)〕
  }
  return result;  // result=this+84 pFxObjA
}



// ------------------------------------------------------------
// 0x4BF3D0 sub_4BF3D0 —— 反向查许可记录 id
//   在 +48 起 16 字节记录中自尾向头扫：记录 +12 非 0（使能）且首字段 id 出现在 pArg2 的
//   4 字节 id 向量（+4/+8）中者胜出，回该 id，无命中回 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BF3D0(uint32_t *this, int pArg2)  // sub_4BF3D0 —— 反向查许可记录 id
{
  int fld_e12; // edx
  int fld_e13; // eax
  int v4; // edx
  int i; // esi
  uint32_t *v6; // ecx
  uint32_t *v7; // eax
  int fld_e122; // [esp+0h] [ebp-4h]

  fld_e12 = *(this + 12);  // 读字段 fld_e12 = this+12（nSkillRec12）
  if ( fld_e12 != 0 )  // fld_e12=this+12 nSkillRec12
    fld_e13 = (*(this + 13) - fld_e12) >> 4;  // this+52〔bAuraState(推断)〕
  else
    fld_e13 = 0;  // fld_e13=this+52 bAuraState
  v4 = fld_e13 - 1;  // 计算 v4 = fld_e13 - 1
  if ( fld_e13 - 1 < 0 )  // fld_e13=this+52 bAuraState
    return -1;
  fld_e122 = *(this + 12);  // 读字段 fld_e122 = this+12（nSkillRec12）
  for ( i = fld_e122 + 16 * v4; ; i -= 16 )  // fld_e122=this+12 nSkillRec12
  {
    if ( *(uint8_t *)(i + 12) != 0 )
    {
      v6 = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
      v7 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
      if ( v7 != v6 )
      {
        do
        {
          if ( *v7 == *(uint32_t *)i )
            break;
          ++v7;  // 计数自增 v7
        }
        while ( v7 != v6 );  // 循环直到 v7 != v6
        if ( v7 != v6 )
          break;
      }
    }
    if ( --v4 < 0 )
      return -1;
  }
  return *(uint32_t *)(fld_e122 + 16 * v4);  // fld_e122=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x4BF450 sub_4BF450 —— 记录状态查询（记录 16 字节：+12 使能 / +13 副标志）
//   按 id 自尾向头线性查找：pszArg3 为 0 回 +12，否则回 +12 且 +13（未命中回 0）；
//   与 ·0x4BF4C0 同构（差异：后者回反相判定）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BF450(uint32_t *this, int nArg2, char pszArg3)  // sub_4BF450 —— 记录状态查询（记录 16 字节：+12 使能 / +13 副标志）
{
  int fld_e12; // edx
  int fld_e13; // eax
  int v5; // eax
  int fld_e122; // edx
  uint32_t *i; // ecx
  int v9; // eax

  fld_e12 = *(this + 12);  // 读字段 fld_e12 = this+12（nSkillRec12）
  if ( fld_e12 != 0 )  // fld_e12=this+12 nSkillRec12
    fld_e13 = (*(this + 13) - fld_e12) >> 4;  // this+52〔bAuraState(推断)〕
  else
    fld_e13 = 0;  // fld_e13=this+52 bAuraState
  v5 = fld_e13 - 1;  // 计算 v5 = fld_e13 - 1
  if ( v5 < 0 )
    return 0;
  fld_e122 = *(this + 12);  // 读字段 fld_e122 = this+12（nSkillRec12）
  for ( i = (uint32_t *)(fld_e122 + 16 * v5); *i != nArg2; i -= 4 )  // fld_e122=this+12 nSkillRec12
  {
    if ( --v5 < 0 )
      return 0;
  }
  v9 = fld_e122 + 16 * v5;  // fld_e122=this+12 nSkillRec12
  if ( pszArg3 == 0 )
    return *(uint8_t *)(v9 + 12);  // 返回字段 v9+12（nSkillRec12）
  return *(uint8_t *)(v9 + 12) != 0 && *(uint8_t *)(v9 + 13) != 0;
}



// ------------------------------------------------------------
// 0x4BF4C0 sub_4BF4C0 —— 与 ·0x4BF450 同构（差异：回反相结果；未命中回 pszArg3 == 0）
//   即 pszArg3 为 0 回 +12 == 0、否则回 +12 == 0 且 +13 非 0。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4BF4C0(uint32_t *this, int nArg2, char pszArg3)  // sub_4BF4C0 —— 与 ·0x4BF450 同构（差异：回反相结果；未命中回 pszArg3 == 0）
{
  int fld_e12; // edx
  int fld_e13; // eax
  int v5; // eax
  int fld_e122; // edx
  uint32_t *i; // ecx
  int v9; // eax

  fld_e12 = *(this + 12);  // 读字段 fld_e12 = this+12（nSkillRec12）
  if ( fld_e12 != 0 )  // fld_e12=this+12 nSkillRec12
    fld_e13 = (*(this + 13) - fld_e12) >> 4;  // this+52〔bAuraState(推断)〕
  else
    fld_e13 = 0;  // fld_e13=this+52 bAuraState
  v5 = fld_e13 - 1;  // 计算 v5 = fld_e13 - 1
  if ( v5 < 0 )
    return pszArg3 == 0;
  fld_e122 = *(this + 12);  // 读字段 fld_e122 = this+12（nSkillRec12）
  for ( i = (uint32_t *)(fld_e122 + 16 * v5); *i != nArg2; i -= 4 )  // fld_e122=this+12 nSkillRec12
  {
    if ( --v5 < 0 )
      return pszArg3 == 0;
  }
  v9 = fld_e122 + 16 * v5;  // fld_e122=this+12 nSkillRec12
  if ( pszArg3 == 0 )
    return *(uint8_t *)(v9 + 12) == 0;  // 写字段 v9+12（nSkillRec12） ← = 0
  return *(uint8_t *)(v9 + 12) == 0 && *(uint8_t *)(v9 + 13) != 0;  // 写字段 v9+12（nSkillRec12） ← = 0 && *(uint8_t *)(v9 + 13) != 0
}



// ------------------------------------------------------------
// 0x4BF540 sub_4BF540 —— Buff 槽查询（+40/+44/+52）
// ------------------------------------------------------------
char /*thiscall*/ sub_4BF540(int *this, int pArg2)  // sub_4BF540 —— Buff 槽查询（+40/+44/+52）
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
  if ( *(uint8_t *)(pArg2 + 40) == 0 )  // pArg2+40〔bStateSub40(推断)〕
  {
    pThis_B = *(uint32_t *)(pArg2 + 36);  // 读字段 pThis_B = pArg2+36（nStateWord36）
    if ( pThis_B == 0 )
      return pThis_B;
  }
  pThis_B = *(uint32_t *)(pArg2 + 4);  // 读字段 pThis_B = pArg2+4（pHostObj）
  if ( pThis_B == 0 )
    goto LABEL_78;
  pThis_B = (*(uint32_t *)(pArg2 + 8) - pThis_B) / 24;  // pArg2+8〔nSkillRec8(推断)〕
  if ( pThis_B == 0 )
    goto LABEL_78;
  fld_e12 = *(this + 12);  // 读字段 fld_e12 = this+12（nSkillRec12）
  if ( fld_e12 == 0 || (*(this + 13) - fld_e12) >> 4 == 0 )  // fld_e12=this+12 nSkillRec12
    goto LABEL_78;
  v6 = *(uint32_t *)(pArg2 + 4) + 24 * pThis_B - 24;  // pArg2+4〔宿主对象〕
  v34 = v6;
  fld_e122 = *(this + 12) + 16 * (((*(this + 13) - fld_e12) >> 4) + 0xFFFFFFF);  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  pThis_B = *(uint32_t *)(pArg2 + 36);  // 读字段 pThis_B = pArg2+36（nStateWord36）
  if ( pThis_B != 1 )
  {
    if ( pThis_B == 2 )
    {
      LOBYTE(pThis_B) = *(uint8_t *)(pArg2 + 40);  // pArg2+40〔bStateSub40(推断)〕
      if ( (uint8_t)pThis_B == 0 )
        *(uint32_t *)(pArg2 + 36) = 3;  // 写字段 pArg2+36（nStateWord36） ← 3
    }
    else if ( pThis_B != 3 )
    {
      if ( (uint8_t)sub_484F10(pArg2 + 16) == 0 )  // sub_484F10 —— 32 字节对象列表空判定（+4 为 0 或元素数 0）
      {
        LOBYTE(pThis_B) = (*(int (/*thiscall*/ **)(int *, int))(*this + 52))(this, pArg2 + 16);  // 虚调用 vt+52（this）归属坐标y
        if ( (uint8_t)pThis_B == 0 )
          return pThis_B;
      }
      v10 = *(uint32_t *)(pArg2 + 32);  // 读字段 v10 = pArg2+32（nHeight）
      if ( v10 != 0 )
      {
        switch ( v10 )  // 按 v10 分派
        {
          case 1:  // case 1 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
            LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);  // fld_e122=this+48 pCmdVecBegin48
            if ( (uint8_t)pThis_B == 0 )
              return pThis_B;
            if ( *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 24 * sub_4FEF30(pArg2) - 8) != 0 )  // pArg2+4〔宿主对象〕
              goto LABEL_41;
            break;
          case 2:  // case 2 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
            LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);  // fld_e122=this+48 pCmdVecBegin48
            if ( (uint8_t)pThis_B != 0 )
              return pThis_B;
            goto LABEL_41;
          case 3:  // case 3 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
            LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);  // fld_e122=this+48 pCmdVecBegin48
            if ( (uint8_t)pThis_B != 0 )
              return pThis_B;
            break;
          default:
LABEL_41:
            fld_e12422 = 0;
            v11 = sub_4FEF30(pArg2) - 1;  // 调 pArg2+4〔宿主对象〕
            v26 = v11;
            pThis_B = sub_453C00(this + 11);  // sub_453C00 —— 16 字节元素计数
            v12 = pThis_B - 1;  // 计算 v12 = pThis_B - 1
            v35 = pThis_B - 1;  // 计算 v35 = pThis_B - 1
            if ( v11 < 0 )
            {
LABEL_69:
              *(uint32_t *)(pArg22 + 36) = 1;  // 写字段 pArg22+36（nStateWord36） ← 1
            }
            else
            {
              v13 = 24 * v11;  // 计算 v13 = 24 * v11
              for ( i = v13; ; v13 = i )
              {
                v14 = *(uint32_t *)(pArg22 + 4);  // 读字段 v14 = pArg22+4（pHostObj）
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
                    fld_e123 = (uint32_t *)(*(this + 12) + 16 * v35);  // this+48〔pCmdVecBegin48(推断)〕
                    do
                    {
                      if ( *fld_e123 == *v17 )  // fld_e123=this+48 pCmdVecBegin48
                        break;
                      ++v18;  // 计数自增 v18
                      fld_e123 -= 4;  // fld_e123=this+48 pCmdVecBegin48
                    }
                    while ( v18 < v16 );  // 循环直到 v18 < v16
                    v15 = v27;
                    pThis_B = j;
                    v12 = v35;
                  }
                  if ( v18 == v16 )
                    return pThis_B;
                }
                if ( v15[4] == 0 )
                {
                  pThis_B = *(this + 12);  // 读字段 pThis_B = this+12（nSkillRec12）
                  if ( *(uint32_t *)(16 * v12 + pThis_B + 4) - *(uint32_t *)(16 * (v12 - v16) + pThis_B + 20) > 100 )  // this+4 宿主对象
                    return pThis_B;  // pThis_B=this+12 nSkillRec12
                }
                v20 = 16 * v12;  // 计算 v20 = 16 * v12
                fld_e124 = *(uint32_t *)(*(this + 12) + v20 + 4);  // this+48〔pCmdVecBegin48(推断)〕
                pThis_B = sub_699000((int)(this + 1));  // 【clock_now(clk)】
                if ( v16 > 0 )
                {
                  fld_e125 = (uint32_t *)(*(this + 12) + v20 + 4);  // this+48〔pCmdVecBegin48(推断)〕
                  for ( k = v16; k != 0; --k )  // 遍历计次循环（k != 0）
                  {
                    if ( *fld_e125 + fld_e125[1] < pThis_B )  // fld_e125=this+48 pCmdVecBegin48
                      pThis_B = *fld_e125 + fld_e125[1];  // pThis_B=this+12 nSkillRec12
                    fld_e125 -= 4;  // fld_e125=this+48 pCmdVecBegin48
                  }
                }
                v22 = v15[4];
                if ( v22 <= 0 )
                {
                  fld_e1242 = fld_e124;  // fld_e124=this+48 pCmdVecBegin48
                  if ( fld_e124 + v15[5] < fld_e12422 )  // fld_e124=this+48 pCmdVecBegin48
                    return pThis_B;  // pThis_B=this+12 nSkillRec12
                }
                else
                {
                  if ( pThis_B + v15[5] < fld_e12422 )  // pThis_B=this+12 nSkillRec12
                    return pThis_B;  // pThis_B=this+12 nSkillRec12
                  fld_e1242 = fld_e124;  // fld_e124=this+48 pCmdVecBegin48
                }
                pThis_B -= fld_e1242;
                if ( pThis_B < v22 )  // pThis_B=this+12 nSkillRec12
                  return pThis_B;  // pThis_B=this+12 nSkillRec12
                pArg22 = pArg2;
                LOBYTE(pThis_B) = v26 - 1;  // pThis_B=this+12 nSkillRec12
                v24 = v26 - 1 < 0;
                fld_e12422 = fld_e1242;
                v35 -= v16;
                --v26;  // 计数自减 v26
                i -= 24;
                if ( v24 )
                  goto LABEL_69;
                v12 = v35;
              }
            }
            return pThis_B;  // pThis_B=this+12 nSkillRec12
        }
        LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 13);  // pThis_B=this+12 nSkillRec12
      }
      else
      {
        LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);  // pThis_B=this+12 nSkillRec12
      }
      if ( (uint8_t)pThis_B == 0 )  // pThis_B=this+12 nSkillRec12
        return pThis_B;  // pThis_B=this+12 nSkillRec12
      goto LABEL_41;
    }
    if ( *(uint32_t *)(pArg2 + 32) != 1 )  // pArg2+32〔nHeight(推断)〕
      return pThis_B;  // pThis_B=this+12 nSkillRec12
    v8 = *(uint32_t **)(v6 + 4);
    if ( v8 == *(uint32_t **)(v6 + 8) )
      return pThis_B;  // pThis_B=this+12 nSkillRec12
    do
    {
      LOBYTE(pThis_B) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 44))(this, *v8, 0);  // 虚调用 vt+44（this 虚表槽）
      if ( (uint8_t)pThis_B == 0 )  // pThis_B=this+12 nSkillRec12
        break;
      pThis_B = *(uint32_t *)(v34 + 8);  // 读字段 pThis_B = v34+8（nSkillRec8）
      ++v8;  // 计数自增 v8
    }
    while ( v8 != (uint32_t *)pThis_B );  // pThis_B=this+12 nSkillRec12
    goto LABEL_77;
  }
  pThis_B = *(uint32_t *)(pArg2 + 32);  // 读字段 pThis_B = pArg2+32（nHeight）
  if ( pThis_B != 0 )  // pThis_B=this+12 nSkillRec12
  {
    switch ( pThis_B )  // 按 pThis_B 分派
    {
      case 1:  // case 1 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
        v9 = *(uint32_t **)(v6 + 4);
        if ( v9 != *(uint32_t **)(v6 + 8) )
        {
          do
          {
            LOBYTE(pThis_B) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 44))(this, *v9, 0);  // 虚调用 vt+44（this 虚表槽）
            if ( (uint8_t)pThis_B == 0 )  // pThis_B=this+12 nSkillRec12
              break;
            pThis_B = *(uint32_t *)(v34 + 8);  // 读字段 pThis_B = v34+8（nSkillRec8）
            ++v9;  // 计数自增 v9
          }
          while ( v9 != (uint32_t *)pThis_B );  // pThis_B=this+12 nSkillRec12
          if ( v9 != *(uint32_t **)(v34 + 8) )
            goto LABEL_78;
        }
        *(uint32_t *)(pArg2 + 36) = 3 - (*(uint8_t *)(pArg2 + 40) != 0);  // 写字段 pArg2+36（nStateWord36） ← 3 - (*(uint8_t *)(pArg2 + 40) != 0)
        break;
      case 2:  // case 2 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
        LOBYTE(pThis_B) = *(uint8_t *)(fld_e122 + 12);  // pThis_B=this+12 nSkillRec12
        if ( (uint8_t)pThis_B != 0 )  // pThis_B=this+12 nSkillRec12
          *(uint32_t *)(pArg2 + 36) = 0;  // 写字段 pArg2+36（nStateWord36） ← 0
        break;
      case 3:  // case 3 分派（§R 0x4BE170-0x4BFFA0 杂项/容器收尾）
        *(uint32_t *)(pArg2 + 36) = 0;  // 写字段 pArg2+36（nStateWord36） ← 0
        break;
      default:
        break;
    }
    return pThis_B;  // pThis_B=this+12 nSkillRec12
  }
  v8 = *(uint32_t **)(v6 + 4);
  if ( v8 == *(uint32_t **)(v6 + 8) )
    return pThis_B;  // pThis_B=this+12 nSkillRec12
  do
  {
    LOBYTE(pThis_B) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*this + 44))(this, *v8, 0);  // 虚调用 vt+44（this 虚表槽）
    if ( (uint8_t)pThis_B == 0 )  // pThis_B=this+12 nSkillRec12
      break;
    pThis_B = *(uint32_t *)(v34 + 8);  // 读字段 pThis_B = v34+8（nSkillRec8）
    ++v8;  // 计数自增 v8
  }
  while ( v8 != (uint32_t *)pThis_B );  // pThis_B=this+12 nSkillRec12
LABEL_77:
  if ( v8 != *(uint32_t **)(v34 + 8) )
LABEL_78:
    *(uint32_t *)(pArg2 + 36) = 0;  // 写字段 pArg2+36（nStateWord36） ← 0
  return pThis_B;  // pThis_B=this+12 nSkillRec12
}


// ------------------------------------------------------------
// 0x4BF910 sub_4BF910 —— 记录序列偏序比较
//   双侧各比 24 字节记录向量（元素 +4 内嵌 4 字节 id 向量、+16/+20 字段）与 +20 起 4 字节
//   向量：本侧多回 1、少回 2，id 集不一致回 0（不可比），自尾向头取首个差异【推断】。
// ------------------------------------------------------------
int /*stdcall*/ sub_4BF910(int pArg1, uint32_t *pArg2)  // sub_4BF910 —— 记录序列偏序比较
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
  v3 = *(uint32_t *)(pArg1 + 4);  // 读字段 v3 = pArg1+4（pHostObj）
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg1 + 8) - v3) / 24;  // pArg1+8〔nSkillRec8(推断)〕
  else
    v4 = 0;
  v5 = pArg2[1];
  if ( v5 != 0 )
    v6 = (pArg2[2] - v5) / 24;
  else
    v6 = 0;
  if ( v4 > v6 )
    return 1;  // 返回 1(成功)
  if ( v5 != 0 )
    v8 = (pArg2[2] - v5) / 24;
  else
    v8 = 0;
  if ( v3 != 0 )
    v9 = (*(uint32_t *)(pArg1 + 8) - v3) / 24;  // pArg1+8〔nSkillRec8(推断)〕
  else
    v9 = 0;
  if ( v8 > v9 )
    return 2;
  v10 = 0;
  v11 = 0;
  v42 = 0;
  v41 = 0;
  if ( v3 != 0 )
    v10 = (*(uint32_t *)(pArg1 + 8) - v3) / 24;  // pArg1+8〔nSkillRec8(推断)〕
  v12 = v10 - 1;  // 计算 v12 = v10 - 1
  v40 = v12;
  if ( v12 < 0 )
  {
LABEL_46:
    v30 = *(uint32_t *)(pArg12 + 20);  // 读字段 v30 = pArg12+20（nPage）
    if ( v30 != 0 )
      v31 = (*(uint32_t *)(pArg12 + 24) - v30) >> 2;  // pArg12+24〔nPageMax(推断)〕
    else
      v31 = 0;
    v35 = pArg2[5];
    if ( v35 != 0 )
      v36 = (pArg2[6] - v35) >> 2;
    else
      v36 = 0;
    if ( v31 > v36 )
      return 1;  // 返回 1(成功)
    v37 = *(uint32_t *)(pArg12 + 20);  // 读字段 v37 = pArg12+20（nPage）
    if ( v37 != 0 )
      v38 = (*(uint32_t *)(pArg12 + 24) - v37) >> 2;  // pArg12+24〔nPageMax(推断)〕
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
    v13 = 24 * v12;  // 计算 v13 = 24 * v12
    v14 = v3 + v13 + 4;
    v15 = (uint32_t *)(v5 + v13);
    v44 = v14;
    v43 = v3 - v5;  // 计算 v43 = v3 - v5
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
        v25 = *(uint32_t *)(v14 + 12);  // 读字段 v25 = v14+12（nSkillRec12）
        v26 = v15[4];
        if ( v25 != v26 )
        {
          v14 = v44;
          v42 = (v25 <= v26) + 1;
        }
      }
      if ( v41 == 0 )
      {
        v27 = *(uint32_t *)(v14 + 16);  // 读字段 v27 = v14+16（nChannelTypeSel）
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
      while ( *v22 != *v16 )  // 当 *v22 != *v16 循环
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
      return 1;  // 返回 1(成功)
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
// 0x4BFBC0 sub_4BFBC0 —— 列表登记与状态判定
//   在 +84 列表找载荷（节点 +8）等于 pArg2 的项；未找到且 pszArg3 为 0 时经 ·vmt+116 登记；
//   随后要求记录 +40 非 0 且 +36 == 1 才回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BFBC0(uint32_t *this, int pArg2, char pszArg3)  // sub_4BFBC0 —— 列表登记与状态判定
{
  uint32_t *fld_e21; // edx
  uint32_t *v4; // eax
  char result; // al

  fld_e21 = (uint32_t *)*(this + 21);  // this+84〔pFxObjA(推断)〕
  v4 = (uint32_t *)*fld_e21;  // fld_e21=this+84 pFxObjA
  if ( (uint32_t *)*fld_e21 == fld_e21 )  // fld_e21=this+84 pFxObjA
    goto LABEL_5;
  do
  {
    if ( v4[2] == pArg2 )
      break;
    v4 = (uint32_t *)*v4;
  }
  while ( v4 != fld_e21 );  // 循环直到 v4 != fld_e21
  if ( v4 == fld_e21 )  // fld_e21=this+84 pFxObjA
  {
LABEL_5:
    if ( pszArg3 != 0 )
      return 0;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 116))(this, pArg2);  // 虚调用 vt+116（this）并透传返回值 —— vt+120 槽的缺省参数包装。
  }
  if ( *(uint8_t *)(pArg2 + 40) == 0 )  // pArg2+40〔bStateSub40(推断)〕
    return 0;
  result = 1;
  if ( *(uint32_t *)(pArg2 + 36) != 1 )  // pArg2+36〔nStateWord36(推断)〕
    return 0;
  return result;
}



// ------------------------------------------------------------
// 0x4BFC10 sub_4BFC10 —— 全称判定（8 字节元素表）
//   对 pArg2 的 8 字节元素向量（+4/+8）逐项调 ·vmt+48，全真回 1（空表回 1），否则 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BFC10(void *this, int pArg2)  // sub_4BFC10 —— 全称判定（8 字节元素表）
{
  int v2; // esi

  v2 = *(uint32_t *)(pArg2 + 4);  // 读字段 v2 = pArg2+4（pHostObj）
  if ( v2 != 0 && (*(uint32_t *)(pArg2 + 8) - v2) >> 3 != 0 )
  {
    if ( v2 == *(uint32_t *)(pArg2 + 8) )  // pArg2+8〔nSkillRec8(推断)〕
      return 1;  // 返回 1(成功)
    while ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 48))(this, v2) != 0 )  // 虚调用 vt+48（this）归属坐标x
    {
      v2 += 8;
      if ( v2 == *(uint32_t *)(pArg2 + 8) )  // pArg2+8〔nSkillRec8(推断)〕
        return 1;  // 返回 1(成功)
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4BFC60 sub_4BFC60 —— 与 ·0x4BFC10 同构（差异：元素 4 字节、查询槽 ·vmt+44）
//   对 pArg2 的 4 字节 id 向量（+4/+8）逐项调 ·vmt+44，全真回 1（空表回 1），否则 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_4BFC60(void *this, int pArg2)  // sub_4BFC60 —— 与 ·0x4BFC10 同构（差异：元素 4 字节、查询槽 ·vmt+44）
{
  uint32_t *v2; // esi

  v2 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v2 != nullptr && (*(uint32_t *)(pArg2 + 8) - (int)v2) >> 2 != 0 )
  {
    if ( v2 == *(uint32_t **)(pArg2 + 8) )  // pArg2+8〔nSkillRec8(推断)〕
      return 1;  // 返回 1(成功)
    while ( (*(uint8_t (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 44))(this, *v2, 0) != 0 )  // 虚调用 vt+44（this 虚表槽）
    {
      if ( ++v2 == *(uint32_t **)(pArg2 + 8) )  // pArg2+8〔nSkillRec8(推断)〕
        return 1;  // 返回 1(成功)
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4BFCB0 sub_4BFCB0 —— 列表计数记账（+8）
//   计数累加 uArg2；和超 0x3FFFFFFF 抛 length_error（list<T> too long，·0x4015C0 造串 +
//   ·0x401740 组异常对象）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4BFCB0(uint32_t *this, unsigned int uArg2)  // sub_4BFCB0 —— 列表计数记账（+8）
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )  // fld_e2=this+8 物品 id
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // 写字段 this+2 ← result
  return result;
}



// ------------------------------------------------------------
// 0x4BFD40 sub_4BFD40 —— 向量填装插入（_Insert_n）
//   在 +4/+8/+12（首/尾/容量尾，元素 16 字节）的向量于 pArg2 处插 uArg3 份 Block 值：原地
//   后移或 1.5 倍扩容重建（·0x602460 搬移、·0x4BF340 与 ·0x504650 填值、·0x4BF320 尾补、
//   ·0x453C20 覆盖、·0x434730 超长抛错）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4BFD40(int this, int pArg2, unsigned int uArg3, uint32_t *Block)  // sub_4BFD40 —— 向量填装插入（_Insert_n）
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
  v26[3] = Block[3];  // v26[3] = 取 Block[3]
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  v26[4] = &v25;
  v26[2] = v6;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    result = (*(uint32_t *)(this + 12) - fld_4) >> 4;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    result = 0;  // result=this+12 nSkillRec12
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0xFFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_434730(this);  // sub_434730 —— vector 超长抛 length_error
    if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( result >= uArg3 + fld_82 )  // result=this+12 nSkillRec12
    {
      fld_83 = *(char **)(this + 8);  // this+32〔nHeight(推断)〕
      Blockb = fld_83;  // fld_83=this+32 nHeight
      if ( (int)&fld_83[-pArg2] >> 4 >= uArg3 )  // fld_83=this+32 nHeight
      {
        v21 = &fld_83[-16 * uArg3];  // fld_83=this+32 nHeight
        *(uint32_t *)(this + 8) = sub_602460(v21, fld_83, fld_83);  // sub_602460 —— 16 字节批量拷贝
        sub_4BF320(pArg2, v21, Blockb);  // sub_4BF320 —— 转发壳
        return sub_453C20(pArg2, pArg2 + 16 * uArg3, v26);  // sub_453C20 —— 16 字节元素区间填充
      }
      else
      {
        sub_602460(pArg2, fld_83, pArg2 + 16 * uArg3);  // sub_602460 —— 16 字节批量拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - pArg2) >> 4);  // this+8〔nSkillRec8(推断)〕等 2 字段
        fld_85 = *(uint32_t *)(this + 8);  // 读字段 fld_85 = this+8（nSkillRec8）
        v27 = 2;
        sub_504650(fld_85, fld_84, v26);  // fld_85=this+8 nSkillRec8
        fld_86 = 16 * uArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;  // 写字段 this+8（nSkillRec8） ← fld_86
        return sub_453C20(pArg2, fld_86 - 16 * uArg3, v26);  // sub_453C20 —— 16 字节元素区间填充
      }
    }
    else
    {
      if ( 0xFFFFFFF - (result >> 1) >= result )  // result=this+12 nSkillRec12
        v12 = (result >> 1) + result;  // result=this+12 nSkillRec12
      else
        v12 = 0;
      if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      if ( v12 < uArg3 + fld_87 )  // fld_87=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else
          fld_88 = 0;  // fld_88=this+8 nSkillRec8
        v12 = uArg3 + fld_88;  // 计算 v12 = uArg3 + fld_88
      }
      v28 = 16 * v12;  // 计算 v28 = 16 * v12
      Blocka = (char *)operator new(16 * v12);  // 堆分配
      fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
      v27 = 0;
      v15 = sub_602460(fld_42, pArg2, Blocka);  // sub_602460 —— 16 字节批量拷贝
      sub_4BF340(v15, uArg3, v26);  // sub_4BF340 —— 16 字节元素填充
      sub_602460(pArg2, *(uint32_t *)(this + 8), 16 * uArg3 + v15);  // sub_602460 —— 16 字节批量拷贝
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else
        fld_89 = 0;  // fld_89=this+8 nSkillRec8
      v18 = fld_89 + uArg3;  // 计算 v18 = fld_89 + uArg3
      if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &Blocka[v28];  // 写字段 this+12（nSkillRec12） ← &Blocka[v28]
      *(uint32_t *)(this + 8) = &Blocka[16 * v18];  // 写字段 this+8（nSkillRec8） ← &Blocka[16 * v18]
      *(uint32_t *)(this + 4) = Blocka;  // 写字段 this+4（pHostObj） ← Blocka
      return (unsigned int)Blocka;
    }
  }
  return result;  // result=this+12 nSkillRec12
}


// ------------------------------------------------------------
// 0x4BFFA0 sub_4BFFA0 —— 16 字节条目表扩容分配（内联 vector 分配路径）
// uArg2 超限走 ·sub_434730 抛 length_error；元素 16 字节（·sub_602460 批量拷贝族）
// 与 worldmap 的 ·sub_45F7D0 同型（同源 MSVC 内联 vector 模板）
// ------------------------------------------------------------
char */*thiscall*/ sub_4BFFA0(int this, unsigned int uArg2)  // sub_4BFFA0 —— 16 字节条目表扩容分配（内联 vector 分配路径）
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
    sub_434730(this);  // sub_434730 —— vector 超长抛 length_error
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  fld_82 = 0;
  if ( fld_4 != 0 )  // fld_4=this+4 pHostObj
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 4;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( fld_C < uArg2 )  // fld_C=this+12 nSkillRec12
  {
    v15 = 16 * uArg2;  // 计算 v15 = 16 * uArg2
    pMem = (char *)operator new(v15);  // 堆分配
    fld_8 = *(uint32_t *)(this + 8);  // 读字段 fld_8 = this+8（nSkillRec8）
    fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
    Block = pMem;
    v14 = 0;
    sub_602460(fld_42, fld_8, pMem);  // sub_602460 —— 16 字节批量拷贝
    fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
    if ( fld_43 != 0 )  // fld_43=this+4 pHostObj
    {
      fld_82 = (*(uint32_t *)(this + 8) - fld_43) >> 4;  // this+8〔nSkillRec8(推断)〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放堆块
    }
    *(uint32_t *)(this + 12) = &pMem[v15];  // 写字段 this+12（nSkillRec12） ← &pMem[v15]
    *(uint32_t *)(this + 8) = &pMem[16 * fld_82];  // 写字段 this+8（nSkillRec8） ← &pMem[16 * fld_82]
    *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
    return &pMem[v15];
  }
  return result;
}


