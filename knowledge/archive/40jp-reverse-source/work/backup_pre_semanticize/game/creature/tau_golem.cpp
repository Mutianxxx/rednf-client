// ============================================================
// 【40JP逆向源代码工程】creature/tau_golem.cpp
// 模块: 怪物AI 0x5A —— 牛头兵(Tau)/石魔像(Golem)/人偶师/飞龙/猎人/僵尸
// 来源: work/dump_monster.txt  区块: 0x5A0000-0x5B0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 249
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：0x5A3160×5表 / 0x5A4B20×1 /
//     0x5A8360×6 / 0x5AD0B0×4（虚表农场 0x6CB000-0x6EB000 +512 槽, 纯 Python 直读 PE）
//   · AI 大状态机（this+6556, 研究 15/20）：0x5A0420(vt+560 setState 形拦截, 态 8)、
//     0x5A5610(唐加斯地震 态 8 门)、0x5A6630(C_BERSERK 狂暴)、0x5A9100(人偶浮游 态 14)、
//     0x5AEAB0(僵尸眼 态 14 条件) —— 本文件是五文件中 6556 证据最密集的一块
//   · 0x5AE990 调 sub_4E4430 = HP 受击处理器（研究 31 Boss 终局族）
//   · 语音 TAG 组（R_TAU_*/GOLEM_*/FLYDRAGON_*/HUNTER_*/ZOMBIE_*）经 sub_4015C0
//     写入语音槽, vt+212(sub_499110) 播报（研究 28）；sub_431230=vector 打包 setState 参数
//   · 资源标注：sub_431860/431920=.ani 装载 / sub_64B0F0=光环粒子(.ptl) /
//     sub_4BA9E0=.equ 外观 / sub_4049C0=帧间插值 / sub_406D60=BGM 曲名槽写入
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】哥布林基础与装备变体（0x5A0060-0x5A0780）
// 证据：{acc3,acc4,Hcc2,gcc1-3,tcc1,bcc1}.equ 六件外观（0x5A0530）、
//       0x5A0420 为 vt+560 setState 形拦截（this+6556 态 8 门）

// AI 字段复位（20L）
// ------------------------------------------------------------
// 0x5A0060 sub_5A0060
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A0060(int *this, uint32_t *a2, char *a3, int *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 12 != 0 )
    v6 = (int)&a3[-v5] / 12;
  else
    v6 = 0;
  sub_59FDB0(this, a3, 1u, Block);
  *a2 = *(this + 1) + 12 * v6;
  return a2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A00D0 sub_5A00D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A00D0(int this, int *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  int v5; // edi
  uint32_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 12;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 12 )
    return sub_5A0060((int *)this, &Block, *(char **)(this + 8), Block);
  v5 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_623C10(v5, 1, Block);
  *(uint32_t *)(this + 8) = v5 + 12;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A0150 sub_5A0150
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0150(char *this, int a2)
{
  char *v2; // ecx
  int v3; // esi
  unsigned int v4; // edx
  int *v5; // eax
  int result; // eax

  v2 = this + 972;
  v3 = *((uint32_t *)v2 + 1);
  if ( v3 != 0 )
    v4 = (*((uint32_t *)v2 + 2) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*((uint32_t *)v2 + 3) - v3) >> 2 )
    return sub_45F8A0(*((void **)v2 + 2), 1, (int)&a2);
  v5 = *((int **)v2 + 2);
  *v5 = a2;
  result = (int)(v5 + 1);
  *((uint32_t *)v2 + 2) = result;
  return result;
}



// RTTI cast 目标解算 AI（86L；this+8624 相位）
// ------------------------------------------------------------
// 0x5A01B0 sub_5A01B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A01B0(uint8_t *this)
{
  unsigned int i; // ebx
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  char *v12; // esi
  int v13; // ebx
  int v14; // ebx
  int v15; // ebx
  int v16; // ebx
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int v20; // eax
  unsigned int v21; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    v3 = *((uint32_t *)this + 29);
    v4 = *(uint32_t *)(v3 + 8);
    v21 = i;
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 33) != 0 )
    {
      v8 = *((uint32_t *)this + 29);
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNChandelier `RTTI Type Descriptor', 0);
      v12 = (char *)v11;
      if ( v11 != 0 )
      {
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 120))(v11) - 55;
        if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) >= v13 )
        {
          v14 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v12 + 120))(v12) + 55;
          if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) <= v14 )
          {
            v15 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v12 + 124))(v12);
            if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this) == v15 )
            {
              v16 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v12 + 128))(v12);
              if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this) >= v16 )
              {
                v17 = *(uint32_t *)this;
                v18 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v12 + 128))(v12);
                v19 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)v12 + 124))(v12, v18 + 10);
                v20 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, v19 + 1);
                (*(void (/*thiscall*/ **)(uint8_t *, int))(v17 + 112))(this, v20);
                result = sub_5A0150(v12, (int)this);
                *((uint32_t *)this + 2158) = v12;
                *(this + 8624) = 1;
                return result;
              }
            }
          }
        }
        i = v21;
      }
    }
  }
  *(this + 8624) = 0;
  return result;
}



// RTTI cast 目标解算（61L）
// ------------------------------------------------------------
// 0x5A0300 sub_5A0300
// ------------------------------------------------------------
bool /*thiscall*/ sub_5A0300(uint32_t *this)
{
  unsigned int i; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // eax
  uint64_t v11; // rax
  int v12; // eax
  unsigned int v13; // edx
  bool result; // al
  int Block[4]; // [esp+Ch] [ebp-10h] BYREF

  for ( i = 0; ; ++i )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    v8 = __RTDynamicCast(v7, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    v9 = v8;
    if ( v8 != 0
      && (uint8_t)sub_4E4630(v8) != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, v9) != 0 )
    {
      v10 = *this;
      Block[0] = v9;
      v11 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v10 + 164))(this, v9, 0);
      HIDWORD(v11) = *this;
      Block[1] = v11;
      Block[2] = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(HIDWORD(v11) + 8))(this, v9, 0);
      sub_5A00D0((int)(this + 2171), Block);
    }
  }
  v12 = *(this + 2172);
  result = false;
  if ( v12 != 0 )
  {
    v13 = (int)((uint64_t)(715827883LL * (*(this + 2173) - v12)) >> 32) >> 1;
    Block[3] = (*(this + 2173) - v12) / 12;
    if ( v13 + (v13 >> 31) != 0 )
      return true;
  }
  return result;
}



// AI 字段访问（this+8628）
// ------------------------------------------------------------
// 0x5A0400 sub_5A0400
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0400(int this)
{
  int result; // eax

  sub_4D9760();
  sub_5A01B0((uint8_t *)this);
  result = **(uint32_t **)(this + 6200);
  *(uint32_t *)(this + 8628) = result;
  return result;
}



// 【AI 大状态拦截】vt+560 setState 形参表(this, 状态, 参数, 优先级, 标志)：
//   this+6556==8 进/出态门 —— 清 this+8672/+8612；sub_41A5E0(this+7028) 怪物数据分型 1/2
//   走不同清理（研究 15/20 三层状态; 56L）
// ------------------------------------------------------------
// 0x5A0420 sub_5A0420
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0420(int this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax

  if ( *(uint32_t *)(this + 6556) == 8 && ArgList != 8 )
  {
    if ( sub_41A5E0(this + 7028) == 1 )
    {
      *(uint32_t *)(this + 8672) = -1;
    }
    else if ( sub_41A5E0(this + 7028) == 2 )
    {
      sub_59FD50(this);
    }
    *(uint8_t *)(this + 8612) = 0;
  }
  if ( *(uint32_t *)(this + 8672) != 4
    && ArgList == 8
    && **(uint32_t **)(LODWORD(a3) + 4) == 2
    && !sub_5A0300((uint32_t *)this) )
  {
    **(uint32_t **)(LODWORD(a3) + 4) = 0;
  }
  sub_59F040(this, ArgList, a3, a4, a5);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 && ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 1 )
    {
      *(uint32_t *)(this + 8672) = 3;
      *(uint8_t *)(this + 8676) = 0;
      *(uint32_t *)(this + 8680) = 0;
    }
    else
    {
      result = sub_41A5E0(this + 7028);
      if ( result == 2 )
      {
        result = 4;
        if ( *(uint32_t *)(this + 8672) != 4 )
        {
          *(uint32_t *)(this + 8672) = 4;
          return (int)sub_59F880(this);
        }
      }
    }
  }
  return result;
}



// 哥布林近战装载：Monster/Goblin/{acc3,acc4,Hcc2,gcc1-3,tcc1,bcc1}.equ（92L）
// ------------------------------------------------------------
// 0x5A0530 sub_5A0530
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5A0530(uint32_t *this)
{
  char *v2; // eax
  char *v3; // eax
  int v4; // eax
  char *v5; // eax
  char *v6; // eax
  int v7; // eax
  char *v8; // eax
  char *v9; // eax
  int v10; // eax
  char *v11; // eax
  char *v12; // eax
  int v13; // eax
  char *v14; // eax
  char *v15; // eax
  int v16; // eax
  char *v17; // eax
  char *v18; // eax
  int v19; // eax
  int v20; // edi
  uint32_t *v21; // eax
  uint64_t result; // rax
  float v23; // [esp+3Ch] [ebp-2Ch]
  float v24; // [esp+40h] [ebp-28h]
  void *Block; // [esp+54h] [ebp-14h]
  int v26; // [esp+58h] [ebp-10h]

  v2 = (char *)operator new(0x544u);
  if ( v2 != nullptr )
    v3 = sub_4BA9E0(v2, "Monster/Goblin/acc3.equ", 0);
  else
    v3 = nullptr;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 4))(v4, 1);
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Goblin/acc4.equ", 0);
  else
    v6 = nullptr;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 4))(v7, 1);
  v8 = (char *)operator new(0x544u);
  if ( v8 != nullptr )
    v9 = sub_4BA9E0(v8, "Monster/Goblin/Hcc2.equ", 0);
  else
    v9 = nullptr;
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  v11 = (char *)operator new(0x544u);
  if ( v11 != nullptr )
    v12 = sub_4BA9E0(v11, "Monster/Goblin/gcc1-3.equ", 0);
  else
    v12 = nullptr;
  v13 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);
  if ( v13 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 4))(v13, 1);
  v14 = (char *)operator new(0x544u);
  if ( v14 != nullptr )
    v15 = sub_4BA9E0(v14, "Monster/Goblin/tcc1.equ", 0);
  else
    v15 = nullptr;
  v16 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);
  if ( v16 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 4))(v16, 1);
  v17 = (char *)operator new(0x544u);
  if ( v17 != nullptr )
    v18 = sub_4BA9E0(v17, "Monster/Goblin/bcc1.equ", 0);
  else
    v18 = nullptr;
  v19 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);
  if ( v19 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v19 + 4))(v19, 1);
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v20 = *(this + 1821) - *(this + 1820);
  v21 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v24 = (float)v26;
  v23 = (float)(int)Block;
  result = (uint64_t)sub_4049C0(v23, v24, *v21 - *(this + 1820), v20);
  *(this + 2155) = result;
  return result;
}



// ============================================================
// 【分区 2】天空之城哥布林三型外观（0x5A0780-0x5A0D00）
// 证据：Monster/Goblin/SkyCastle/{BombKagel,SurikenKagel,BullsEye}/ 五件套 +
//       PassiveObject/Common/Particle/RedRock.ptl（靶眼落石）

// 天空之城·炸弹加格尔装载：Monster/Goblin/SkyCastle/BombKagel/{Face,hair,pants,wrist,belt}.equ
// ------------------------------------------------------------
// 0x5A0780 sub_5A0780
// ------------------------------------------------------------
int /*usercall*/ sub_5A0780@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  char *v3; // eax
  char *v4; // eax
  int v5; // eax
  char *v6; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  char *v10; // eax
  int v11; // eax
  char *v12; // eax
  char *v13; // eax
  int v14; // eax
  char *v15; // eax
  char *v16; // eax
  int result; // eax

  v3 = (char *)operator new(0x544u);
  if ( v3 != nullptr )
    v4 = sub_4BA9E0(v3, "Monster/Goblin/SkyCastle/BombKagel/Face.equ", 0);
  else
    v4 = nullptr;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*a1 + 784))(a1, v4, a2);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v7 = sub_4BA9E0(v6, "Monster/Goblin/SkyCastle/BombKagel/hair.equ", 0);
  else
    v7 = nullptr;
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v7);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (char *)operator new(0x544u);
  if ( v9 != nullptr )
    v10 = sub_4BA9E0(v9, "Monster/Goblin/SkyCastle/BombKagel/pants.equ", 0);
  else
    v10 = nullptr;
  v11 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v10);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 4))(v11, 1);
  v12 = (char *)operator new(0x544u);
  if ( v12 != nullptr )
    v13 = sub_4BA9E0(v12, "Monster/Goblin/SkyCastle/BombKagel/wrist.equ", 0);
  else
    v13 = nullptr;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v13);
  if ( v14 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 4))(v14, 1);
  v15 = (char *)operator new(0x544u);
  if ( v15 != nullptr )
    v16 = sub_4BA9E0(v15, "Monster/Goblin/SkyCastle/BombKagel/belt.equ", 0);
  else
    v16 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v16);
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  a1[1666] = 0;
  return result;
}



// 天空之城·手里剑加格尔装载：Monster/Goblin/SkyCastle/SurikenKagel/ 五件套
// ------------------------------------------------------------
// 0x5A0930 sub_5A0930
// ------------------------------------------------------------
int /*usercall*/ sub_5A0930@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  char *v3; // eax
  char *v4; // eax
  int v5; // eax
  char *v6; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  char *v10; // eax
  int v11; // eax
  char *v12; // eax
  char *v13; // eax
  int v14; // eax
  char *v15; // eax
  char *v16; // eax
  int result; // eax

  v3 = (char *)operator new(0x544u);
  if ( v3 != nullptr )
    v4 = sub_4BA9E0(v3, "Monster/Goblin/SkyCastle/SurikenKagel/Face.equ", 0);
  else
    v4 = nullptr;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*a1 + 784))(a1, v4, a2);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v7 = sub_4BA9E0(v6, "Monster/Goblin/SkyCastle/SurikenKagel/hair.equ", 0);
  else
    v7 = nullptr;
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v7);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (char *)operator new(0x544u);
  if ( v9 != nullptr )
    v10 = sub_4BA9E0(v9, "Monster/Goblin/SkyCastle/SurikenKagel/pants.equ", 0);
  else
    v10 = nullptr;
  v11 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v10);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 4))(v11, 1);
  v12 = (char *)operator new(0x544u);
  if ( v12 != nullptr )
    v13 = sub_4BA9E0(v12, "Monster/Goblin/SkyCastle/SurikenKagel/wrist.equ", 0);
  else
    v13 = nullptr;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v13);
  if ( v14 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 4))(v14, 1);
  v15 = (char *)operator new(0x544u);
  if ( v15 != nullptr )
    v16 = sub_4BA9E0(v15, "Monster/Goblin/SkyCastle/SurikenKagel/belt.equ", 0);
  else
    v16 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v16);
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  a1[1666] = 0;
  return result;
}



// 天空之城·靶眼装载：Monster/Goblin/SkyCastle/BullsEye/ 五件套 +
//   PassiveObject/Common/Particle/RedRock.ptl 落石粒子（86L）
// ------------------------------------------------------------
// 0x5A0AE0 sub_5A0AE0
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_5A0AE0@<eax>(int a1@<ecx>, int a2@<edi>)
{
  char *v3; // eax
  char *v4; // eax
  int v5; // eax
  char *v6; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  char *v10; // eax
  int v11; // eax
  char *v12; // eax
  char *v13; // eax
  int v14; // eax
  char *v15; // eax
  char *v16; // eax
  int v17; // eax
  uint32_t *result; // eax

  v3 = (char *)operator new(0x544u);
  if ( v3 != nullptr )
    v4 = sub_4BA9E0(v3, "Monster/Goblin/SkyCastle/BullsEye/Face.equ", 0);
  else
    v4 = nullptr;
  v5 = (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)a1 + 784))(a1, v4, a2);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v7 = sub_4BA9E0(v6, "Monster/Goblin/SkyCastle/BullsEye/hair.equ", 0);
  else
    v7 = nullptr;
  v8 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1 + 784))(a1, v7);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (char *)operator new(0x544u);
  if ( v9 != nullptr )
    v10 = sub_4BA9E0(v9, "Monster/Goblin/SkyCastle/BullsEye/pants.equ", 0);
  else
    v10 = nullptr;
  v11 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1 + 784))(a1, v10);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 4))(v11, 1);
  v12 = (char *)operator new(0x544u);
  if ( v12 != nullptr )
    v13 = sub_4BA9E0(v12, "Monster/Goblin/SkyCastle/BullsEye/wrist.equ", 0);
  else
    v13 = nullptr;
  v14 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1 + 784))(a1, v13);
  if ( v14 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 4))(v14, 1);
  v15 = (char *)operator new(0x544u);
  if ( v15 != nullptr )
    v16 = sub_4BA9E0(v15, "Monster/Goblin/SkyCastle/BullsEye/belt.equ", 0);
  else
    v16 = nullptr;
  v17 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1 + 784))(a1, v16);
  if ( v17 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 4))(v17, 1);
  *(uint32_t *)(a1 + 8672) = -1;
  *(uint32_t *)(a1 + 6664) = 0;
  *(uint8_t *)(a1 + 8676) = 0;
  *(uint32_t *)(a1 + 8680) = 0;
  if ( *(uint32_t *)(a1 + 8688) != 0 )
    j__free(*(void **)(a1 + 8688));
  *(uint32_t *)(a1 + 8688) = 0;
  *(uint32_t *)(a1 + 8692) = 0;
  *(uint32_t *)(a1 + 8696) = 0;
  result = operator new(0x12Cu);
  if ( result != nullptr )
  {
    result = sub_428F30(result, (int)"PassiveObject/Common/Particle/RedRock.ptl", 0);
    *(uint32_t *)(a1 + 8704) = result;
  }
  else
  {
    *(uint32_t *)(a1 + 8704) = 0;
  }
  return result;
}



// ============================================================
// 【分区 3】雷光基诺尔（LightningKinol）（0x5A0D00-0x5A2020）
// 证据：BEFORE_THUNDER 蓄雷播报、THUNDER_STRIKE 落雷 + Animation_LightningKinol/
//       DieThunderbolt.ani、B_KINOL_01 登场曲、Lkinolpants.equ

// AI 字段访问
// ------------------------------------------------------------
// 0x5A0D00 sub_5A0D00
// ------------------------------------------------------------
void /*thiscall*/ sub_5A0D00(uint32_t *this)
{
  *(this + 2153) = 0;
}



// 蓄雷 AI：BEFORE_THUNDER 播报（this+200 主状态门 + 8624 相位, 64L）
// ------------------------------------------------------------
// 0x5A0D10 sub_5A0D10
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0D10(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int result; // eax
  int v8; // ecx
  uint32_t v9[6]; // [esp+8h] [ebp-18h]

  v2 = *this;
  v9[0] = 3;
  v9[1] = 4;
  v9[2] = 5;
  v9[3] = 6;
  v9[4] = 7;
  v9[5] = 8;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(v2 + 200))(this) + 148) == v9[*(this + 2157)]
    && *((uint8_t *)this + 8624) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "BEFORE_THUNDER",
      -1,
      0,
      0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      v3 = *(this + 2155) * (*(this + 2157) + 1);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 )
        v3 = -v3;
      v4 = *this;
      v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 120))(
             this,
             *(this + 2154),
             30070,
             *(this + 2153),
             0,
             4,
             *(this + 1908) != 0 ? 100 : 130,
             1,
             0,
             0);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*this + 120))(this, *(this + 2154), 0, v5 - v3);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 584))(this, v6 - v3);
    }
    *((uint8_t *)this + 8624) = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  v8 = *(this + 2157);
  if ( *(uint32_t *)(result + 148) == v9[v8] + 1 )
  {
    *((uint8_t *)this + 8624) = 0;
    *(this + 2157) = v8 + 1;
  }
  return result;
}



// 蓄雷 AI 扩展：BEFORE_THUNDER（102L；+200/8624 门）
// ------------------------------------------------------------
// 0x5A0E50 sub_5A0E50
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0E50(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // edi
  uint64_t v6; // rax
  int result; // eax
  int v8; // ecx
  int v9; // [esp+Ch] [ebp-94h]
  uint32_t v10[23]; // [esp+10h] [ebp-90h]
  uint32_t v11[12]; // [esp+6Ch] [ebp-34h]
  int v12; // [esp+9Ch] [ebp-4h]

  v10[3] = 135;
  v10[7] = 135;
  v10[1] = 75;
  v10[9] = 75;
  v10[2] = -70;
  v10[10] = -70;
  v10[15] = -135;
  v10[19] = -135;
  v10[22] = -70;
  v2 = *this;
  v11[0] = 2;
  v11[1] = 3;
  v11[2] = 4;
  v11[3] = 5;
  v11[4] = 6;
  v11[5] = 7;
  v11[6] = 8;
  v11[7] = 9;
  v11[8] = 10;
  v11[9] = 11;
  v11[10] = 12;
  v11[11] = 13;
  v9 = 0;
  v10[0] = -85;
  v10[4] = -45;
  v10[5] = 175;
  v10[6] = 0;
  v10[8] = 45;
  v10[11] = 0;
  v10[12] = 85;
  v10[13] = -75;
  v10[14] = 70;
  v10[16] = 45;
  v10[17] = -175;
  v10[18] = 0;
  v10[20] = -45;
  v10[21] = -75;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(v2 + 200))(this) + 148) == v11[*(this + 2157)]
    && *((uint8_t *)this + 8624) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "BEFORE_THUNDER",
      -1,
      0,
      0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      v4 = *(this + 2157);
      v12 = v3;
      v5 = (uint64_t)((double)v3 + (double)v10[2 * v4 - 1] * ((double)(int)*(this + 2158) * 0.0099999998));
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v6 = (uint64_t)((double)v12
                            + (double)(int)v10[2 * *(this + 2157)] * ((double)(int)*(this + 2158) * 0.0099999998));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 584))(
        this,
        v5,
        v6,
        0,
        v5,
        v6,
        30070,
        *(this + 2153),
        0,
        4,
        *(this + 1908) != 0 ? 100 : 130,
        1,
        0,
        0);
    }
    *((uint8_t *)this + 8624) = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  v8 = *(this + 2157);
  if ( *(uint32_t *)(result + 148) == v11[v8] + 1 )
  {
    *((uint8_t *)this + 8624) = 0;
    *(this + 2157) = v8 + 1;
  }
  return result;
}



// 大型 AI（137L；雷光基诺尔走位）
// ------------------------------------------------------------
// 0x5A1070 sub_5A1070
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1070(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // et2
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // ebx
  int v26; // edi
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 && *(this + 1943) == 3 )
  {
    v3 = rand();
    v4 = v3 % 100;
    result = v3 / 100;
    if ( v4 < 75 )
    {
      if ( sub_4E7F30(this, 100, 60, 0) != 0 )
      {
        v5 = *this;
        v6 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
               this,
               30070,
               *(this + 2153),
               0,
               4,
               *(this + 1908) != 0 ? 100 : 130,
               1,
               0,
               0);
        v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);
        v8 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v7 - 50);
        v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
        (*(void (/*thiscall*/ **)(int *, int))(v5 + 584))(this, v9 - 50);
        v10 = *this;
        v11 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
                this,
                30070,
                *(this + 2153),
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,
                1,
                0,
                0);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
        v13 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v12 + 50);
        v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);
        (*(void (/*thiscall*/ **)(int *, int))(v10 + 584))(this, v14 + 50);
        v15 = *this;
        v16 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
                this,
                30070,
                *(this + 2153),
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,
                1,
                0,
                0);
        v17 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v16 - 50);
        v18 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v17);
        v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v18 - 50);
        (*(void (/*thiscall*/ **)(int *, int))(v15 + 584))(this, v19);
        v20 = *this;
        v21 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
                this,
                30070,
                *(this + 2153),
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,
                1,
                0,
                0);
        v22 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v21 + 50);
        v23 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v22);
        v24 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v23 + 50);
        (*(void (/*thiscall*/ **)(int *, int))(v20 + 584))(this, v24);
        sub_49C970(8, 0, 0);
        return sub_49C5F0(9, 0, 0, 1000);
      }
      else
      {
        result = *(this + 1813);
        if ( result != 0 )
        {
          v25 = *this;
          v26 = *(this + 1813);
          v27 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)result + 124))(
                  result,
                  30070,
                  *(this + 2153),
                  0,
                  4,
                  *(this + 1908) != 0 ? 100 : 130,
                  1,
                  0,
                  0);
          v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v26 + 120))(v26, v27);
          v29 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v26 + 124))(v26, 0, v28);
          v30 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v26 + 120))(v26, v29);
          return (*(int (/*thiscall*/ **)(int *, int))(v25 + 584))(this, v30);
        }
      }
    }
  }
  return result;
}


// AI 字段访问（this+8604）
// ------------------------------------------------------------
// 0x5A12C0 sub_5A12C0
// ------------------------------------------------------------
char /*thiscall*/ sub_5A12C0(int this, int a2)
{
  char result; // al

  result = sub_4DBC20(a2);
  if ( a2 == 6 )
  {
    result = *(uint8_t *)(this + 8604);
    if ( result != 0 )
      return sub_64BDF0(this, *(uint32_t *)(this + 7256));
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A1300 sub_5A1300
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1300(int *this, int a2)
{
  int v4; // ebx
  int v5; // esi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // [esp+8h] [ebp-8h]
  int v12; // [esp+Ch] [ebp-4h]
  int v13; // [esp+18h] [ebp+8h]

  if ( a2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2) != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
    v11 = *this;
    v6 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*this + 152))(this, 100, 1, 0, 0);
    v7 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int))(*(uint32_t *)v4 + 124))(v4, 30070, 0, 0, v6);
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 120))(v13, v7);
    v9 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v12 + 124))(v12, 0, v8);
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 120))(v5, v9);
    (*(void (/*thiscall*/ **)(int *, int))(v11 + 584))(this, v10);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A13C0 sub_5A13C0
// ------------------------------------------------------------
char /*thiscall*/ sub_5A13C0(uint32_t *this)
{
  if ( *(this + 1639) == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )
    {
      sub_5A0D10(this);
      return sub_4E1780(this);
    }
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
      sub_5A0E50(this);
  }
  return sub_4E1780(this);
}



// 指挥 AI：GOBLIN_COMMAND（RTTI cast, 56L）
// ------------------------------------------------------------
// 0x5A1410 sub_5A1410
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1410(uint32_t *this)
{
  int result; // eax
  int v3; // ebx
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  uint32_t v9[3]; // [esp+8h] [ebp-1Ch]
  uint16_t v10; // [esp+14h] [ebp-10h] BYREF
  uint16_t v11; // [esp+18h] [ebp-Ch] BYREF
  uint16_t v12; // [esp+1Ch] [ebp-8h] BYREF
  uint16_t v13; // [esp+20h] [ebp-4h] BYREF

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v12);
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v13);
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v10);
    (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v11);
    if ( (uint16_t)v3 == 13 )
    {
      v4 = sub_45EBE0(v12, v13);
      v5 = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &CNGoblinGoblin `RTTI Type Descriptor', 0);
      v6 = sub_45EBE0(v10, v11);
      v7 = __RTDynamicCast(v6, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
      if ( v5 != 0 && v7 != 0 )
      {
        sub_49C510(10, *(this + 1), *(uint32_t *)(v5 + 4), v7, 0);
        sub_4D82D0(0, 0);
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "GOBLIN_COMMAND",
          -1,
          0,
          0);
        v9[0] = 2;
        v9[1] = 3;
        v9[2] = 4;
        v8 = rand();
        sub_4DB200(24, v9[v8 % 3]);
      }
    }
    return v3;
  }
  return result;
}



// AI 相位辅助（96L）
// ------------------------------------------------------------
// 0x5A1550 sub_5A1550
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1550(uint32_t *this)
{
  int result; // eax
  unsigned int i; // esi
  int v4; // ecx
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // esi
  int v14; // ebx
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // [esp+4h] [ebp-Ch]
  int v22; // [esp+8h] [ebp-8h]
  unsigned int v23; // [esp+Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v4 = *(this + 29);
      v5 = *(uint32_t *)(v4 + 8);
      v23 = i;
      result = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(v4 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(v4 + 12) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 17) == 0 )
      {
        v8 = *(this + 29);
        v9 = *(uint32_t *)(v8 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 40))(v10, 545) == 0 )
          continue;
      }
      v11 = *(this + 29);
      v12 = *(uint32_t *)(v11 + 8);
      if ( v12 != 0 && i < (*(uint32_t *)(v11 + 12) - v12) >> 2 )
        v13 = *(uint32_t *)(v12 + 4 * i);
      else
        v13 = 0;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 376))(v13);
      if ( v14 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, v13, 0) <= 300
        && ((*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 40))(v13, 17) == 0
         || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 940))(v13) == 0)
        && rand() % 100 >= 50 )
      {
        v21 = rand() % 50 - 25;
        v15 = rand();
        v16 = *this;
        v22 = v15 % 50 - 25;
        v17 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)v13 + 124))(
                v13,
                30070,
                *(this + 2153),
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,
                1,
                0,
                0);
        v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 120))(v13, v22 + v17);
        v19 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)v13 + 124))(v13, 0, v21 + v18);
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 120))(v13, v22 + v19);
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v16 + 584))(this, v21 + v20);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
      }
      i = v23;
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A1720 sub_5A1720
// ------------------------------------------------------------
int /*usercall*/ sub_5A1720@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  int result; // eax
  int v4; // eax
  int v5; // et2

  sub_4DE3E0();
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    v4 = rand();
    v5 = v4 % 100;
    result = v4 / 100;
    if ( v5 < 30 )
      return sub_59B130(a1, a2, (int)a1, a1[1814]);
  }
  return result;
}



// 参数打包 AI（sub_431230, 53L）
// ------------------------------------------------------------
// 0x5A1760 sub_5A1760
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1760(int **this)
{
  int v2; // ebx
  int v3; // eax
  int *v4; // ecx
  int v5; // eax
  int v6; // edx
  int *v7; // ebx
  int v8; // eax
  uint8_t v10[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v12; // [esp+Ch] [ebp-1Ch]
  int v13; // [esp+10h] [ebp-18h]
  int v14; // [esp+14h] [ebp-14h] BYREF
  uint32_t v15[4]; // [esp+18h] [ebp-10h] BYREF

  if ( ((uint8_t (/*thiscall*/ *)(int **))(*this)[77])(this) != 0 && *(this + 1813) != nullptr )
  {
    v15[0] = 100;
    do
    {
      v2 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1813) + 124))(*(this + 1813));
      v3 = rand();
      v4 = *(this + 1813);
      v5 = v2 + v3 % 100 - 50;
      v6 = *v4;
      v7 = *this;
      v14 = v5;
      v8 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(v6 + 120))(v4, v5, 0);
      if ( ((uint8_t (/*thiscall*/ *)(int **, int))v7[34])(this, v8) != 0 )
        break;
    }
    while ( v15[0]-- > 0 );
    Block = nullptr;
    v12 = 0;
    v13 = 0;
    v15[3] = 0;
    v15[0] = 1;
    sub_431230((int)v10, v15);
    sub_431230((int)v10, &v14);
    v14 = rand() % 50 + 25;
    sub_431230((int)v10, &v14);
    ((void (/*thiscall*/ *)(int **, int, uint8_t *, uint32_t, uint32_t))(*this)[140])(this, 8, v10, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 参数打包 AI（sub_431230, 29L）
// ------------------------------------------------------------
// 0x5A1880 sub_5A1880
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1880(uint32_t *this)
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && *(this + 1813) != 0 )
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 2;
    sub_431230((int)v2, v6);
    v6[0] = 10 * (rand() % 5 + 5);
    sub_431230((int)v2, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 登场曲：sub_406D60 写 "B_KINOL_01"（雷光基诺尔曲目槽, 71L）
// ------------------------------------------------------------
// 0x5A1930 sub_5A1930
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1930(int **this)
{
  sub_4E0120();
  switch ( (unsigned int)*(this + 1787) )
  {
    case 0u:
      ((void (/*thiscall*/ *)(int **))(*this)[321])(this);
      if ( *(this + 1943) == (int *)3 )
        sub_406D60("B_KINOL_01");
      return;
    case 4u:
      if ( *(this + 1813) == nullptr )
        goto LABEL_10;
      if ( rand() % 100 >= 5 )
        goto LABEL_12;
      goto LABEL_8;
    case 5u:
      if ( *(this + 1813) != nullptr )
      {
        if ( rand() % 100 < 5 )
        {
LABEL_8:
          ((void (/*thiscall*/ *)(int **))(*this)[264])(this);
        }
        else
        {
LABEL_12:
          if ( rand() % 100 >= 15 )
          {
            if ( rand() % 100 >= 8 )
            {
              if ( rand() % 100 < 8 )
                sub_5A1760(this);
            }
            else
            {
              sub_5A1880(this);
            }
          }
          else
          {
            sub_5A1550(this);
          }
        }
      }
      else
      {
LABEL_10:
        ((void (/*thiscall*/ *)(int **, int))(*this)[276])(this, 13);
      }
      return;
    case 0xDu:
      if ( *(this + 1813) != nullptr )
        goto LABEL_19;
      return;
    case 0xEu:
    case 0xFu:
      if ( *(this + 1813) != nullptr )
LABEL_19:
        ((void (/*thiscall*/ *)(int **, int))(*this)[276])(this, 4);
      break;
    default:
      return;
  }
}



// 落雷技能：THUNDER_STRIKE 播报 + Animation_LightningKinol/DieThunderbolt.ani
//   死亡落雷特效（61L）
// ------------------------------------------------------------
// 0x5A1A90 sub_5A1A90
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1A90(int *this)
{
  int result; // eax
  int v3; // ebx
  int v4; // edx
  char *v5; // eax
  char *v6; // edi
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int i; // [esp+4h] [ebp-14h]
  char *v13; // [esp+8h] [ebp-10h]

  *(this + 1942) += 300;
  (*(void (/*thiscall*/ **)(int *, int, int, int))(*this + 260))(this, 1, 5, -16777216);
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "THUNDER_STRIKE", -1, 0, 0);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    for ( i = 8; i != 0; --i )
    {
      v3 = 0;
      if ( sub_42FCB0(228) != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(v4) = (uint8_t)this + 108;
        else
          v4 = *(this + 91);
        v3 = sub_431920(v4, (char)"Animation_LightningKinol/DieThunderbolt.ani", 1);
      }
      v5 = (char *)sub_44B6C0(284);
      v6 = v5;
      if ( v5 != nullptr )
      {
        sub_44E0D0(v5, v3, 1);
        *(uint32_t *)v6 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v6 = nullptr;
      }
      v13 = v6;
      sub_45FE80(*(this + 29), (int)v6, 2, 0, (int)v6, (int)this, 0);
      v7 = *(uint32_t *)v6;
      v8 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
      v9 = rand();
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8 + v9 % 30 - 15);
      v11 = rand();
      result = (*(int (/*thiscall*/ **)(char *, int))(v7 + 112))(v13, v10 + v11 % 70 - 35);
    }
  }
  return result;
}



// 蓄雷 AI：BEFORE_THUNDER（52L；8624 相位）
// ------------------------------------------------------------
// 0x5A1BF0 sub_5A1BF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1BF0(int *this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax
  uint32_t *v7; // eax

  if ( ArgList == 14 )
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "BEFORE_THUNDER",
             -1,
             0,
             0);
  if ( *(this + 1639) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )
  {
    if ( ArgList == 8 )
      goto LABEL_9;
    *((uint8_t *)this + 8624) = 0;
    *(this + 2157) = 0;
  }
  if ( ArgList == 8 )
  {
LABEL_9:
    v7 = *(uint32_t **)(LODWORD(a3) + 4);
    if ( *v7 == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BEFORE_THUNDER", -1, 0, 0);
      *(this + 2154) = *(uint32_t *)(*(uint32_t *)(LODWORD(a3) + 4) + 4);
      *(this + 2155) = *(uint32_t *)(*(uint32_t *)(LODWORD(a3) + 4) + 8);
    }
    else if ( *v7 == 2 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BEFORE_THUNDER", -1, 0, 0);
      *(this + 2158) = *(uint32_t *)(*(uint32_t *)(LODWORD(a3) + 4) + 4);
    }
  }
  sub_4E33D0(ArgList, a3, a4, a5);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result == 5 )
  {
    if ( rand() % 100 < 50 )
      sub_64BDF0(this, *(this + 1814));
    return sub_5A1A90(this);
  }
  return result;
}



// 基诺尔装载：R_GOBLIN_TALK/DMG/DIE 语音 + Monster/Goblin/{hcc1,Lkinolpants,Weapon03-2,acc1}.equ
//   （115L；8624 相位）
// ------------------------------------------------------------
// 0x5A1D20 sub_5A1D20
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5A1D20(float *this)
{
  char *v2; // eax
  char *v3; // eax
  int v4; // eax
  char *v5; // eax
  char *v6; // eax
  int v7; // eax
  char *v8; // eax
  char *v9; // eax
  int v10; // eax
  char *v11; // eax
  char *v12; // eax
  int v13; // eax
  uint32_t *v14; // eax
  double v15; // st7
  int v16; // eax
  int v17; // edi
  uint32_t *v18; // eax
  uint64_t v19; // rax
  int v20; // eax
  int v21; // edi
  uint32_t *v22; // eax
  uint64_t result; // rax
  float v24; // [esp+44h] [ebp-2Ch]
  float v25; // [esp+44h] [ebp-2Ch]
  float v26; // [esp+44h] [ebp-2Ch]
  float v27; // [esp+48h] [ebp-28h]
  float v28; // [esp+48h] [ebp-28h]
  float v29; // [esp+48h] [ebp-28h]
  void *Block; // [esp+5Ch] [ebp-14h]
  void *Blocka; // [esp+5Ch] [ebp-14h]
  void *Blockb; // [esp+5Ch] [ebp-14h]
  int v33; // [esp+60h] [ebp-10h]
  int v34; // [esp+60h] [ebp-10h]
  int v35; // [esp+60h] [ebp-10h]

  *((uint32_t *)this + 1698) = 2;
  *((uint32_t *)this + 1699) = 2;
  *((uint32_t *)this + 1700) = 2;
  *((uint32_t *)this + 1701) = 3;
  *((uint32_t *)this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);
  sub_4015C0("R_GOBLIN_DMG", 0xCu);
  sub_4015C0("R_GOBLIN_DIE", 0xCu);
  v2 = (char *)operator new(0x544u);
  if ( v2 != nullptr )
    v3 = sub_4BA9E0(v2, "Monster/Goblin/hcc1.equ", 0);
  else
    v3 = nullptr;
  v4 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 4))(v4, 1);
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Goblin/Lkinolpants.equ", 0);
  else
    v6 = nullptr;
  v7 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 4))(v7, 1);
  v8 = (char *)operator new(0x544u);
  if ( v8 != nullptr )
    v9 = sub_4BA9E0(v8, "Monster/Goblin/Weapon03-2.equ", 0);
  else
    v9 = nullptr;
  v10 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v9);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  v11 = (char *)operator new(0x544u);
  if ( v11 != nullptr )
    v12 = sub_4BA9E0(v11, "Monster/Goblin/acc1.equ", 0);
  else
    v12 = nullptr;
  v13 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v12);
  if ( v13 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 4))(v13, 1);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v33 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v14 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v27 = (float)v33;
  v24 = (float)(int)Block;
  v15 = sub_4049C0(v24, v27, *v14 - *((uint32_t *)this + 1820), *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820));
  v16 = *(uint32_t *)this;
  *(this + 106) = v15;
  v34 = (*(int (/*thiscall*/ **)(float *, int))(v16 + 384))(this, 2);
  Blocka = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v17 = *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820);
  v18 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v28 = (float)(int)Blocka;
  v25 = (float)v34;
  v19 = (uint64_t)sub_4049C0(v25, v28, *v18 - *((uint32_t *)this + 1820), v17);
  *((float *)&v19 + 1) = *this;
  *((uint32_t *)this + 109) = v19;
  v35 = (*(int (/*thiscall*/ **)(float *, int))(HIDWORD(v19) + 384))(this, 4);
  v20 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);
  v21 = *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820);
  Blockb = (void *)v20;
  v22 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v29 = (float)(int)Blockb;
  v26 = (float)v35;
  result = (uint64_t)sub_4049C0(v26, v29, *v22 - *((uint32_t *)this + 1820), v21);
  *((uint32_t *)this + 2153) = result;
  *((uint8_t *)this + 8624) = 0;
  *(this + 2157) = 0.0;
  *((uint32_t *)this + 2120) = 10;
  *((uint32_t *)this + 2121) = 2000;
  return result;
}



// ============================================================
// 【分区 4】胆小鬼哥布林（CowardGoblin）（0x5A2020-0x5A2E30）
// 证据：Goblin/CowardGoblin.mob 引用、POWER_UP/POWER_DOWN 强化弱化、
//       MonsterPowerUp/MonsterPowerDown.ptl、B_CWGBN_01 登场曲、CwGobSantaBeard.equ

// 子类扩展字段复位（this+8612..8644, 29L）
// ------------------------------------------------------------
// 0x5A2020 sub_5A2020
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2020(int this)
{
  if ( dword_9B9328 == 0 )
  {
    dword_9B9328 = sub_422E70(875);
    dword_9B932C = sub_422E70(876);
  }
  if ( dword_9B9330 == 0 )
  {
    dword_9B9330 = sub_422E70(877);
    dword_9B9334 = sub_422E70(878);
  }
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8612) = -1;
  *(uint32_t *)(this + 8624) = 1065353216;
  *(uint32_t *)(this + 8628) = 0;
  *(uint32_t *)(this + 8632) = 0;
  *(uint32_t *)(this + 8636) = 0;
  *(uint32_t *)(this + 8640) = 0;
  *(uint8_t *)(this + 8644) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A20C0 sub_5A20C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A20C0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2154);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2155);
  *(this + 2154) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 2155) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A2100 sub_5A2100
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2100(uint32_t *this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax
  int v7; // eax
  int v8; // et2

  result = sub_4E33D0(ArgList, a3, a4, a5);
  if ( ArgList == 5 )
  {
    v7 = rand();
    v8 = v7 % 100;
    result = v7 / 100;
    if ( v8 < 50 )
      return sub_64BDF0(this, *(this + 1814));
  }
  return result;
}



// mob 引用：Goblin/CowardGoblin.mob（胆小鬼哥布林数据文件, 34L）
// ------------------------------------------------------------
// 0x5A2150 sub_5A2150
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2150(int *this, int a2)
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v8; // [esp+Ch] [ebp-4h]
  bool v9; // [esp+1Bh] [ebp+Bh]

  v9 = *(uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3) > a2;
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);
  (*(void (/*thiscall*/ **)(int *, int, const char *))(*this + 1024))(this, a2, "Goblin/CowardGoblin.mob");
  v5 = *this;
  if ( !v9 )
  {
    v4 += (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this) - v8;
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 740))(this) < v4 )
      goto LABEL_3;
LABEL_5:
    v6 = v4;
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 732))(this, v6, 0, 1);
  }
  if ( v4 < (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this) )
    goto LABEL_5;
LABEL_3:
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 732))(this, v6, 0, 1);
}



// AI 相位辅助（67L）
// ------------------------------------------------------------
// 0x5A2200 sub_5A2200
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2200(int this, int a2, int a3)
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
  if ( a3 != 0 )
  {
    if ( a3 != 2 )
      return result;
    if ( a2 != 0 )
    {
      if ( a2 != 1 )
      {
        if ( a2 != 2 )
          return result;
        goto LABEL_6;
      }
    }
    else
    {
      *(uint32_t *)(this + 7596) = 50;
    }
    *(uint32_t *)(this + 7572) = 2;
    *(uint32_t *)(this + 7568) = 1;
    return result;
  }
  if ( a2 == 0 )
  {
LABEL_6:
    *(uint32_t *)(this + 7596) = -100;
    return result;
  }
  if ( (unsigned int)(a2 - 1) <= 1 )
  {
    *(uint32_t *)(this + 7596) = -20;
    *(uint32_t *)(this + 7568) = 1;
    *(uint32_t *)(this + 7572) = 2;
  }
  return result;
}



// AI 相位辅助（60L）
// ------------------------------------------------------------
// 0x5A2300 sub_5A2300
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2300(uint32_t *this)
{
  int v1; // ebx
  unsigned int i; // esi
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  uint32_t *v11; // edx
  uint32_t *v12; // ecx
  uint32_t *v13; // eax

  v1 = 0;
  for ( i = 0; ; ++i )
  {
    v4 = *(this + 29);
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
    if ( (int)i >= v6 )
      break;
    v7 = *(uint32_t *)(v4 + 8);
    if ( v7 != 0 && i < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
      v8 = *(uint32_t *)(v7 + 4 * i);
    else
      v8 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 40))(v8, 529) != 0 )
    {
      v9 = *(this + 29);
      v10 = *(uint32_t *)(v9 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(v9 + 12) - v10) >> 2 )
        v11 = *(uint32_t **)(v10 + 4 * i);
      else
        v11 = nullptr;
      v12 = (uint32_t *)v11[84];
      v13 = (uint32_t *)v11[83];
      if ( v13 != v12 )
      {
        do
        {
          if ( *v13 == 19 )
            break;
          ++v13;
        }
        while ( v13 != v12 );
        if ( v13 != v12 && this != v11 )
          ++v1;
      }
    }
  }
  return v1;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A23C0 sub_5A23C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A23C0(float *this, int a2)
{
  double v3; // st7
  int v4; // edx
  float v5; // ebx
  uint32_t *v6; // edi
  float v7; // [esp-Ch] [ebp-1Ch]
  uint32_t v8[3]; // [esp+4h] [ebp-Ch]
  int i; // [esp+18h] [ebp+8h]

  v3 = *(this + 2156);
  v8[0] = 1036831949;
  v8[1] = -1110651699;
  if ( v3 > 1.0 && *(this + 2156) < 1.5 )
  {
    v4 = *(uint32_t *)this;
    v5 = *(this + 2156);
    *(this + 2156) = *(float *)&v8[a2] + v5;
    *(float *)&v8[2] = v5;
    (*(void (/*thiscall*/ **)(float *))(v4 + 688))(this);
    sub_4EB4B0(v5);
    v7 = *(this + 2156);
    (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 688))(this);
    sub_4EB2C0(v7);
    v6 = this + 2157;
    for ( i = 4; i != 0; --i )
    {
      if ( *v6 != 0 )
      {
        sub_4EB6E0(v5);
        sub_4EB6A0(*(this + 2156));
      }
      ++v6;
    }
  }
}



// 强化状态：POWER_UP 播报（46L）
// ------------------------------------------------------------
// 0x5A2490 sub_5A2490
// ------------------------------------------------------------
void /*thiscall*/ sub_5A2490(int *this, int a2)
{
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0
    && (uint8_t)sub_4DAB60(19) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
    if ( v3 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) )
    {
      v4 = 2 * sub_5A2300(this);
      if ( v4 > 1 )
      {
        if ( v4 >= 29 )
          v4 = 29;
      }
      else
      {
        v4 = 1;
      }
      sub_5A2150(this, v4);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 192))(this) > 0 )
      {
        v5 = rand() % 2;
        v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 64))(this, dword_9B9328[v5]);
        sub_50EF20(v6, 0, -1);
        v7 = *(this + 2154);
        *(this + 2153) = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v7 + 12))(v7, 0);
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "POWER_UP", -1, 0, 0);
      }
      sub_5A23C0((float *)this, 0);
    }
  }
}



// 弱化状态：POWER_DOWN 播报（103L；RTTI cast 目标解算）
// ------------------------------------------------------------
// 0x5A2590 sub_5A2590
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2590(int *this, int a2)
{
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  unsigned int i; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  const char *v19; // eax
  int v21; // [esp-8h] [ebp-214h]
  int v22; // [esp-4h] [ebp-210h]
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int v24; // [esp+208h] [ebp-4h]

  v24 = dword_796E50;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0
    && (uint8_t)sub_4DAB60(19) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
    if ( v3 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) )
    {
      v4 = 2 * (sub_5A2300(this) - 1);
      if ( v4 > 1 )
      {
        if ( v4 >= 29 )
          v4 = 29;
      }
      else
      {
        v4 = 1;
      }
      sub_5A2150(this, v4);
      v5 = rand() % 2;
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 64))(this, dword_9B9330[v5]);
      sub_50EF20(v6, 0, -1);
      v7 = *(this + 2155);
      *(this + 2153) = 1;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v7 + 12))(v7, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "POWER_DOWN", -1, 0, 0);
      sub_5A23C0((float *)this, 1);
      for ( i = 0; ; ++i )
      {
        v9 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
        v10 = *(uint32_t *)(v9 + 120);
        v11 = v9 + 116;
        v12 = v10 != 0 ? (*(uint32_t *)(v11 + 8) - v10) >> 2 : 0;
        if ( (int)i >= v12 )
          break;
        v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 80))(this, v22);
        v14 = *(uint32_t *)(v13 + 120);
        if ( v14 != 0 && i < (*(uint32_t *)(v13 + 124) - v14) >> 2 )
          v15 = *(uint32_t *)(v14 + 4 * i);
        else
          v15 = 0;
        v22 = 529;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 40))(v15) != 0 )
        {
          v16 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
          v17 = *(uint32_t *)(v16 + 120);
          if ( v17 != 0 && i < (*(uint32_t *)(v16 + 124) - v17) >> 2 )
            v18 = *(uint32_t *)(v17 + 4 * i);
          else
            v18 = 0;
          if ( __RTDynamicCast(
                 v18,
                 0,
                 &IRDCollisionObject `RTTI Type Descriptor',
                 &CNCowardGoblin `RTTI Type Descriptor',
                 0) != 0 )
          {
            (*(void (/*thiscall*/ **)(int *))(*this + 80))(this);
            if ( this == (int *)sub_425A00(i) )
            {
              v21 = sub_4633B0(this);
              v19 = (const char *)sub_422E70(879);
              sprintf(Buffer, v19, v21);
              sub_43BEE0(*((uint32_t **)dword_8F8528 + 7), (int)Buffer, -10158236, 0, -1);
            }
            return sub_4D9170(a2);
          }
        }
      }
    }
  }
  return sub_4D9170(a2);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A27A0 sub_5A27A0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A27A0(uint32_t *this)
{
  int v2; // edi
  int v3; // edx
  void *v4; // eax
  int v5; // [esp-Ch] [ebp-30h]
  int v6; // [esp-8h] [ebp-2Ch]
  int v7; // [esp-4h] [ebp-28h]
  uint8_t v8[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v10; // [esp+20h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2154) + 68))(*(this + 2154)) != 0 )
    *(this + 2153) = -1;
  v2 = *(uint32_t *)*(this + 2154);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  (*(void (/*thiscall*/ **)(uint32_t))(v2 + 40))(*(this + 2154));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2154) + 92))(*(this + 2154), v8);
  v3 = *this;
  v10 = 0;
  v4 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint8_t *))(v3 + 80))(this, 2, 0, v8);
  sub_4600B0(v4, v5, v6, v7);
  if ( Block != nullptr )
    j__free(Block);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A2850 sub_5A2850
// ------------------------------------------------------------
void /*thiscall*/ sub_5A2850(uint32_t *this)
{
  int v2; // edi
  int v3; // edx
  void *v4; // eax
  int v5; // [esp-Ch] [ebp-30h]
  int v6; // [esp-8h] [ebp-2Ch]
  int v7; // [esp-4h] [ebp-28h]
  uint8_t v8[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v10; // [esp+20h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2155) + 68))(*(this + 2155)) != 0 )
    *(this + 2153) = -1;
  v2 = *(uint32_t *)*(this + 2155);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  (*(void (/*thiscall*/ **)(uint32_t))(v2 + 40))(*(this + 2155));
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2155) + 92))(*(this + 2155), v8);
  v3 = *this;
  v10 = 0;
  v4 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint8_t *))(v3 + 80))(this, 2, 0, v8);
  sub_4600B0(v4, v5, v6, v7);
  if ( Block != nullptr )
    j__free(Block);
}



// 登场曲：sub_406D60 写 "B_CWGBN_01"（胆小鬼哥布林曲目槽, 47L）
// ------------------------------------------------------------
// 0x5A2900 sub_5A2900
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2900(int *this)
{
  int result; // eax

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        result = sub_406D60("B_CWGBN_01");
      break;
    case 4:
      result = *(this + 1813);
      if ( result == 0 )
        goto LABEL_7;
      break;
    case 5:
      result = *(this + 1813);
      if ( result == 0 )
LABEL_7:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    case 13:
      result = *(this + 1813);
      if ( result != 0 )
        goto LABEL_11;
      break;
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



// AI 相位门（this+8612/8644）
// ------------------------------------------------------------
// 0x5A29E0 sub_5A29E0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A29E0(int this)
{
  int v2; // eax
  int v3; // eax

  sub_4E1780((uint32_t *)this);
  if ( *(uint8_t *)(this + 8644) == 0 )
  {
    v2 = 2 * sub_5A2300((uint32_t *)this);
    if ( v2 > 1 )
    {
      if ( v2 >= 29 )
        v2 = 29;
    }
    else
    {
      v2 = 1;
    }
    sub_5A2150((int *)this, v2);
    sub_5A23C0((float *)this, 0);
    *(uint8_t *)(this + 8644) = 1;
  }
  v3 = *(uint32_t *)(this + 8612);
  if ( v3 != 0 )
  {
    if ( v3 == 1 )
      sub_5A2850((uint32_t *)this);
  }
  else
  {
    sub_5A27A0((uint32_t *)this);
  }
}



// 胆小鬼装载：R_GOBLIN_* 语音 + {gcc1,Weapon01,CwGobSantaBeard}.equ +
//   Common/CommonEffect/Particle/{MonsterPowerUp,MonsterPowerDown}.ptl（65L）
// ------------------------------------------------------------
// 0x5A2A50 sub_5A2A50
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2A50(uint32_t *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // eax
  char *v5; // edi
  char *v6; // eax
  char *v7; // edi
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);
  sub_4015C0("R_GOBLIN_DMG", 0xCu);
  sub_4015C0("R_GOBLIN_DIE", 0xCu);
  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v3 = sub_4BA9E0(v2, "Monster/Goblin/gcc1.equ", 0);
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  *(this + 2157) = v3;
  v4 = (char *)operator new(0x544u);
  if ( v4 != nullptr )
    v5 = sub_4BA9E0(v4, "Monster/Goblin/Weapon01.equ", 0);
  else
    v5 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v5);
  *(this + 2158) = v5;
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v7 = sub_4BA9E0(v6, "Monster/Goblin/CwGobSantaBeard.equ", 0);
  else
    v7 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v7);
  *(this + 2159) = v7;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 570;
  v8 = operator new(0x12Cu);
  if ( v8 != nullptr )
    v9 = sub_428F30(v8, (int)"Common/CommonEffect/Particle/MonsterPowerUp.ptl", (int)this);
  else
    v9 = nullptr;
  *(this + 2154) = v9;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v9 + 112))(v9, this);
  v10 = operator new(0x12Cu);
  if ( v10 != nullptr )
    v11 = sub_428F30(v10, (int)"Common/CommonEffect/Particle/MonsterPowerDown.ptl", (int)this);
  else
    v11 = nullptr;
  *(this + 2155) = v11;
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v11 + 112))(v11, this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A2C50 sub_5A2C50
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2C50(uint32_t *this, uint32_t *a2)
{
  int result; // eax
  int v4; // edx

  sub_4D90A0(a2);
  if ( *a2 == 10 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
  result = *a2 - 11;
  if ( *a2 == 11 )
  {
    sub_4D84F0(0, 0);
    v4 = *this;
    *(this + 1813) = a2[3];
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 1104))(this, 20);
    return sub_49C5F0(10, 0, 0, 500);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A2CC0 sub_5A2CC0
// ------------------------------------------------------------
// attributes: thunk
char /*thiscall*/ sub_5A2CC0(uint32_t *this)
{
  return sub_4E1780(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A2CD0 sub_5A2CD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2CD0(uint32_t *this, int a2, int a3)
{
  bool v4; // zf
  int result; // eax
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+Ch] [ebp+8h]

  if ( a2 != 0 )
  {
    if ( a2 <= 0 || a2 > 2 )
      goto LABEL_8;
    v4 = a3 == 0;
  }
  else
  {
    v4 = a3 == 2;
  }
  if ( v4 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.76923078;
LABEL_8:
  if ( a3 != 0 )
  {
    result = a3 - 2;
    if ( a3 == 2 )
      *(this + 1892) = 0;
  }
  else
  {
    v6 = *this;
    *((uint8_t *)this + 7556) = 0;
    *(this + 1899) = 30;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 830;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;
    sub_41A590(v7, v8, v9);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A2D80 sub_5A2D80
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2D80(uint32_t *this, int a2, int a3)
{
  bool v4; // zf
  int result; // eax
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+Ch] [ebp+8h]

  if ( a2 != 0 )
  {
    if ( a2 <= 0 || a2 > 2 )
      goto LABEL_8;
    v4 = a3 == 0;
  }
  else
  {
    v4 = a3 == 2;
  }
  if ( v4 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 1.3;
LABEL_8:
  if ( a3 != 0 )
  {
    result = a3 - 2;
    if ( a3 == 2 )
      *(this + 1892) = 2;
  }
  else
  {
    v6 = *this;
    *((uint8_t *)this + 7556) = 1;
    *(this + 1899) = 30;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 830;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;
    sub_41A590(v7, v8, v9);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// ============================================================
// 【分区 5】牛头兵 Tau（0x5A2E30-0x5A5180）
// 证据：B_TAUARMY_01 登场曲、R_TAU_TALK/DMG + TAU_DIE 语音、TAU_BREATH/TAU_GROUND_HIT、
//       STATEMACHINE:TACKLESTART 冲撞状态机、TAU_RUSH_LOOP、TAU_COMMAND、
//       AURA_DEFEND + TAU_ROAR、GuardSpark 格挡 = vmt200 覆写（0x5A4B20）

// 登场曲：sub_406D60 写 "B_TAUARMY_01"（牛头军曲目槽, 60L）
// ------------------------------------------------------------
// 0x5A2E30 sub_5A2E30
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2E30(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // et2
  int v5; // eax
  int v6; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        result = sub_406D60("B_TAUARMY_01");
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_5;
      v3 = rand();
      v4 = v3 % 100;
      result = v3 / 100;
      if ( v4 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        v5 = rand();
        v6 = v5 % 100;
        result = v5 / 100;
        if ( v6 < 1 )
          goto LABEL_12;
      }
      else
      {
LABEL_5:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_12:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// 牛头兵装载：R_TAU_TALK / R_TAU_DMG / TAU_DIE 语音 + Monster/Tau/{Weapon01,Horn01}.equ（49L）
// ------------------------------------------------------------
// 0x5A2F30 sub_5A2F30
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2F30(uint32_t *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // ebx
  int v5; // eax
  char *v6; // eax
  int v7; // eax
  int result; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);
  sub_4015C0("R_TAU_DMG", 9u);
  sub_4015C0("TAU_DIE", 7u);
  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v4 = sub_4BA9E0(v2, "Monster/Tau/Weapon01.equ", 0);
  else
    v4 = nullptr;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v4);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v3 = sub_4BA9E0(v6, "Monster/Tau/Horn01.equ", 0);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 4))(v7, 1);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
  sub_4EB2C0(0.80000001);
  sub_4EB6A0(0.80000001);
  result = sub_4EB6A0(0.80000001);
  *(this + 1830) = 30;
  *(this + 1839) = -30;
  *(this + 1831) = 300;
  *((uint8_t *)this + 7542) = 1;
  return result;
}



// 语音播报：R_TAU_TALK（this+8608 相位）
// ------------------------------------------------------------
// 0x5A30B0 sub_5A30B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A30B0(uint8_t *this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax

  result = sub_4E33D0(ArgList, a3, a4, a5);
  if ( ArgList == 8 )
  {
    *(this + 8608) = 0;
    result = sub_41A5E0((unsigned int)(this + 7028));
    if ( result == 2 )
      return (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "R_TAU_TALK",
               -1,
               0,
               0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A3110 sub_5A3110
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3110(int *this, uint32_t *a2)
{
  int result; // eax
  int v4; // edx

  result = sub_4D90A0(a2);
  if ( *a2 == 6 )
  {
    sub_4D84F0(0, 0);
    v4 = *this;
    *(this + 1813) = a2[3];
    (*(void (/*thiscall*/ **)(int *, int))(v4 + 1104))(this, 20);
    return sub_49C5F0(4, 0, 0, 500);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A3160 sub_5A3160
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3160(void (/*thiscall*/ ***this)(int, void *, uint32_t), int a2, int a3, int a4)
{
  int v5; // edi

  v5 = sub_4DA3B0(a2, a3, a4);
  if ( ((uint8_t (/*thiscall*/ *)(void (/*thiscall*/ ***)(int, void *, uint32_t)))(*this)[77])(this) != 0
    && rand() % 100 < 10 )
  {
    (**(this + 2150))((int)(this + 2150), this, *(this + 1814));
  }
  return v5;
}



// 技能播报：TAU_BREATH（牛头喷息）
// ------------------------------------------------------------
// 0x5A31C0 sub_5A31C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A31C0(void *this)
{
  int result; // eax
  int v3; // eax
  int v4; // et2

  sub_4DA1D0();
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  if ( result == 0 )
  {
    v3 = rand();
    v4 = v3 % 100;
    result = v3 / 100;
    if ( v4 < 20 )
      return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "TAU_BREATH",
               -1,
               0,
               0);
  }
  return result;
}



// 技能播报：TAU_GROUND_HIT（牛头砸地, 72L）
// ------------------------------------------------------------
// 0x5A3200 sub_5A3200
// ------------------------------------------------------------
char /*usercall*/ sub_5A3200@<al>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // eax
  int v5; // eax
  int v6; // edx
  uint32_t *v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v14; // [esp-18h] [ebp-1Ch]
  int v15; // [esp-10h] [ebp-14h]

  sub_4E1780(a1);
  v4 = (*(int (/*thiscall*/ **)(int *))(*a1 + 840))(a1);
  if ( v4 == 8 )
  {
    if ( sub_41A5E0((unsigned int)(a1 + 1757)) == 2 )
    {
      LOBYTE(v4) = *((uint8_t *)a1 + 8608);
      if ( (uint8_t)v4 != 1 )
      {
        v4 = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
        if ( *(uint32_t *)(v4 + 148) == 1 )
        {
          v5 = a1[29];
          v6 = *a1;
          *((uint8_t *)a1 + 8608) = 1;
          v7 = *(uint32_t **)(v5 + 132);
          v8 = (*(int (/*thiscall*/ **)(int *))(v6 + 200))(a1);
          v9 = sub_491C10(v8);
          LOBYTE(v4) = sub_424120(v7, 5, v9);
        }
      }
    }
    else
    {
      v4 = sub_41A5E0((unsigned int)(a1 + 1757));
      if ( v4 == 0 )
      {
        LOBYTE(v4) = *((uint8_t *)a1 + 8608);
        if ( (uint8_t)v4 != 1 )
        {
          v4 = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
          if ( *(uint32_t *)(v4 + 148) == 4 )
          {
            v10 = (*(int (/*thiscall*/ **)(int *, int, int))(*a1 + 152))(a1, a3, a2) != 0 ? 110 : -110;
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0 )
            {
              v15 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);
              v14 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1);
              v11 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1);
              sub_4E4A50(a1, 30022, 0, v10 + v11, v14, 0, v15, 0, 0, 0);
            }
            v12 = a1[29];
            *((uint8_t *)a1 + 8608) = 1;
            sub_424120(*(uint32_t **)(v12 + 132), 2, 500);
            LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *, const char *, int))(*a1 + 212))(a1, "TAU_GROUND_HIT", -1);
          }
        }
      }
    }
  }
  return v4;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3350 sub_5A3350
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3350(uint32_t *this, int a2, int a3)
{
  int result; // eax
  bool v5; // zf
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+10h] [ebp+Ch]

  if ( a3 != 0 )
  {
    result = a3 - 2;
    if ( a3 != 2 )
      return result;
    result = a2;
    v5 = a2 == 0;
  }
  else
  {
    v6 = *this;
    *(this + 1899) = 0;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 858;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;
    sub_41A590(v7, v8, v9);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    result = a2;
    v5 = a2 == 1;
  }
  if ( v5 )
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.76923078;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A33E0 sub_5A33E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A33E0(uint32_t *this, int a2, int a3)
{
  int result; // eax
  bool v5; // zf
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+10h] [ebp+Ch]

  if ( a3 != 0 )
  {
    result = a3 - 2;
    if ( a3 != 2 )
      return result;
    result = a2;
    v5 = a2 == 0;
  }
  else
  {
    v6 = *this;
    *(this + 1899) = 30;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 858;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;
    sub_41A590(v7, v8, v9);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    result = a2;
    v5 = a2 == 1;
  }
  if ( v5 )
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 1.3;
  return result;
}



// 登场曲：sub_406D60 写 "B_TAUBEAST_01"（牛头兽曲目槽）
// ------------------------------------------------------------
// 0x5A3470 sub_5A3470
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3470(int *this)
{
  int result; // eax

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        result = sub_406D60("B_TAUBEAST_01");
      break;
    case 4:
      result = *(this + 1813);
      if ( result == 0 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// 牛头兽装载：R_TAU_TALK/DMG + TAU_DIE 语音 + Monster/Tau/{Hair-Beast,Horn-Beast}.equ（70L）
// ------------------------------------------------------------
// 0x5A3510 sub_5A3510
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3510(uint32_t *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // ebx
  int v5; // eax
  char *v6; // eax
  int v7; // eax
  int v8; // eax
  void *v9; // eax
  int v10; // eax
  int result; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);
  sub_4015C0("R_TAU_DMG", 9u);
  sub_4015C0("TAU_DIE", 7u);
  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v4 = sub_4BA9E0(v2, "Monster/Tau/Hair-Beast.equ", 0);
  else
    v4 = nullptr;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v4);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v3 = sub_4BA9E0(v6, "Monster/Tau/Horn-Beast.equ", 0);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 4))(v7, 1);
  v8 = *this;
  *(this + 1830) = 30;
  *(this + 1839) = -30;
  *(this + 1831) = 300;
  (*(void (/*thiscall*/ **)(uint32_t *))(v8 + 688))(this);
  sub_4EB2C0(1.55);
  sub_4EB6A0(1.55);
  sub_4EB6A0(1.55);
  v9 = operator new(0x64u);
  if ( v9 != nullptr )
    v10 = sub_51A7D0(v9);
  else
    v10 = 0;
  *(this + 2151) = v10;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 64))(v10) + 36) = 0;
  result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2151)
                                                                                          + 56))(
             *(this + 2151),
             this,
             this,
             0,
             0,
             0,
             -1);
  *((uint8_t *)this + 8608) = 0;
  *((uint8_t *)this + 7531) = 1;
  return result;
}



// 状态机字符串证据："STATEMACHINE:TACKLESTART"（冲撞起始态, 35L；.ani/mob 状态机指令）
// ------------------------------------------------------------
// 0x5A36F0 sub_5A36F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A36F0(int *this, int ArgList, float a3, int a4, int a5)
{
  int v6; // edi
  int result; // eax

  v6 = *(this + 1639);
  result = sub_4E33D0(ArgList, a3, a4, a5);
  if ( v6 != 8 )
    goto LABEL_5;
  if ( ArgList != 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 1 )
      result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 216))(this, 0);
LABEL_5:
    if ( ArgList != 8 )
      return result;
  }
  result = sub_41A5E0((unsigned int)(this + 1757));
  if ( result == 1 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 19);
    off_77F3FC("STATEMACHINE:TACKLESTART");
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
    sub_4926A0(*(this + 30));
    return sub_49C5F0(10, 0, 0, 500);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A37A0 sub_5A37A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A37A0(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  unsigned int v5; // edi
  int v6; // edx
  int result; // eax
  int v8; // [esp+10h] [ebp+Ch]

  if ( a3 != 0 )
  {
    if ( a3 == 2 )
      *(this + 1895) = 0;
  }
  else
  {
    v4 = *this;
    *((uint8_t *)this + 7556) = 0;
    *(this + 1899) = 0;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 672))(this, 0) + 830;
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;
    sub_41A590(v5, v6, v8);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.76923078;
  }
  result = a2;
  if ( a2 == 0 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.76923078;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3850 sub_5A3850
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3850(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  unsigned int v5; // edi
  int v6; // edx
  int result; // eax
  int v8; // [esp+10h] [ebp+Ch]

  if ( a3 != 0 )
  {
    if ( a3 == 2 )
      *(this + 1895) = 2;
  }
  else
  {
    v4 = *this;
    *((uint8_t *)this + 7556) = 1;
    *(this + 1899) = 30;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v4 + 672))(this, 0) + 830;
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) + 0.30000001;
    sub_41A590(v5, v6, v8);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 1.3;
  }
  result = a2;
  if ( a2 == 0 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 1.3;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3900 sub_5A3900
// ------------------------------------------------------------
char /*thiscall*/ sub_5A3900(int *this)
{
  int v2; // ecx
  int v3; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && *(this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 1 )
  {
    v2 = *(this + 30);
    if ( *(uint8_t *)(v2 + 170) != 0 )
    {
      v3 = *(this + 1554);
      if ( v2 == *(uint32_t *)(v3 + 4) )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(v3 + 4));
        sub_4926A0(*(this + 30));
      }
    }
  }
  return sub_4E1780(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3960 sub_5A3960
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3960(int *this, int a2, float a3, int a4, int a5)
{
  int result; // eax
  int v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // edi
  int v11; // eax

  result = sub_5A36F0(this, a2, a3, a4, a5);
  if ( a2 == 8 && **(uint32_t **)(LODWORD(a3) + 4) == 2 )
  {
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 ? 70 : -70;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v9 = *this;
    v10 = v8 + v7;
    v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
    result = (*(int (/*thiscall*/ **)(int *, int, int))(v9 + 136))(this, v10, v11);
    if ( (uint8_t)result == 0 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
  }
  return result;
}



// 登场/技能播报：ROCKMOUDE_01（岩石虫/岩鼠曲, 49L）
// ------------------------------------------------------------
// 0x5A39E0 sub_5A39E0
// ------------------------------------------------------------
char /*thiscall*/ sub_5A39E0(int *this)
{
  int v2; // eax
  int v3; // eax

  sub_5A3900(this);
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( v2 == 8 )
  {
    v2 = sub_41A5E0((unsigned int)(this + 1757));
    if ( v2 == 2 )
    {
      LOBYTE(v2) = *(uint8_t *)(*(this + 30) + 170);
      if ( (uint8_t)v2 != 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
        {
          v3 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
            this,
            (v3 != 0) + 1018,
            0,
            0,
            0,
            70,
            0,
            0,
            4,
            0,
            0,
            0);
        }
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                       this,
                       "ROCKMOUDE_01",
                       -1,
                       0,
                       0);
      }
    }
  }
  return v2;
}



// 冲刺 AI：TAU_RUSH_LOOP 播报（74L；sub_431230 参数打包）
// ------------------------------------------------------------
// 0x5A3A70 sub_5A3A70
// ------------------------------------------------------------
void /*thiscall*/ sub_5A3A70(uint32_t *this, int a2)
{
  uint32_t *v2; // edi
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  void *v8[7]; // [esp+8h] [ebp-1Ch] BYREF

  v2 = (uint32_t *)a2;
  sub_4D90A0(a2);
  switch ( *v2 )
  {
    case 6:
      sub_4D84F0(0, 0);
      v4 = *this;
      *(this + 1813) = v2[3];
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 1104))(this, 20);
      sub_49C5F0(4, 0, 0, 500);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 768))(this, 12, 3, 0);
      *(this + 1881) = 10000;
      break;
    case 0xA:
      if ( *(this + 30) == *(uint32_t *)*(this + 1554) )
      {
        v5 = *this;
        v6 = sub_498F60(this);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v5 + 896))(this, v6, 4);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          *(this + 2151),
          *(this + 2151),
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
        v7 = rand();
        sub_49C5F0(11, 0, 0, v7 % 300 + 300);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(
          this,
          "TAU_RUSH_LOOP",
          0,
          0,
          0);
      }
      break;
    case 0xB:
      if ( *(this + 30) == *(uint32_t *)(*(this + 1554) + 4) )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);
      break;
    case 0xC:
      if ( *(this + 1639) == 0 )
      {
        *(this + 1813) = v2[3];
        memset(&v8[1], 0, 12);
        v8[6] = nullptr;
        a2 = 1;
        sub_431230((int)v8, &a2);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, v8, 0, 0);
        sub_5E5260(v8);
      }
      break;
    default:
      return;
  }
}



// 牛头装载 2：R_TAU_* 语音 + Monster/Tau/{wrap02,Horn02}.equ（63L）
// ------------------------------------------------------------
// 0x5A3C80 sub_5A3C80
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3C80(uint32_t *this)
{
  char *v2; // eax
  int v3; // eax
  char *v4; // eax
  char *v5; // ebx
  int v6; // eax
  int v7; // edi
  uint32_t *v8; // eax
  uint64_t v9; // rax
  int result; // eax
  float v11; // [esp+18h] [ebp-38h]
  float v12; // [esp+1Ch] [ebp-34h]
  void *Block; // [esp+38h] [ebp-18h]
  int v14; // [esp+3Ch] [ebp-14h]
  char *v15; // [esp+40h] [ebp-10h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);
  sub_4015C0("R_TAU_DMG", 9u);
  sub_4015C0("TAU_DIE", 7u);
  v2 = (char *)operator new(0x544u);
  if ( v2 != nullptr )
    v15 = sub_4BA9E0(v2, "Monster/Tau/wrap02.equ", 0);
  else
    v15 = nullptr;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);
  if ( v3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 4))(v3, 1);
  v4 = (char *)operator new(0x544u);
  if ( v4 != nullptr )
    v5 = sub_4BA9E0(v4, "Monster/Tau/Horn02.equ", 0);
  else
    v5 = nullptr;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v5);
  if ( v6 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 4))(v6, 1);
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v7 = *(this + 1821) - *(this + 1820);
  v8 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v12 = (float)v14;
  v11 = (float)(int)Block;
  v9 = (uint64_t)sub_4049C0(v11, v12, *v8 - *(this + 1820), v7);
  HIDWORD(v9) = *this;
  *(this + 2151) = v9;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(HIDWORD(v9) + 688))(this, 1064514355);
  sub_4EB2C0(0.0);
  sub_4EB6A0(0.94999999);
  result = sub_4EB6A0(0.94999999);
  *((uint8_t *)this + 7542) = 1;
  return result;
}



// 子类扩展字段复位（this+8604..8612）
// ------------------------------------------------------------
// 0x5A3E50 sub_5A3E50
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3E50(int this)
{
  *(uint8_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint8_t *)(this + 8612) = 0;
  return 0;
}



// AI 字段访问（this+8604）
// ------------------------------------------------------------
// 0x5A3E70 sub_5A3E70
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3E70(uint8_t *this, int *a2, int a3)
{
  int result; // eax
  int v5; // ebx

  result = sub_4DC390(a2, a3);
  v5 = result;
  if ( result != 3 )
  {
    if ( *(this + 8604) != 0 )
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3) + 12) == 1 )
      {
        *a2 = (uint64_t)((double)*a2 * 0.5);
        return 2;
      }
      else
      {
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3) + 124) == 0 )
          *a2 = (uint64_t)((double)*a2 * 0.34999999);
        if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3) + 124) == 1 )
          *a2 = (uint64_t)((double)*a2 * 0.25);
        return 2;
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this) <= 0 )
    {
      return v5;
    }
    else
    {
      *a2 = (uint64_t)((double)*a2 + (double)*a2);
      return 0;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A40F0 sub_5A40F0
// ------------------------------------------------------------
int /*usercall*/ sub_5A40F0@<eax>(uint32_t *a1@<ecx>, int a2@<edi>)
{
  int v2; // edi
  int v3; // edx
  int result; // eax

  sub_4E1780(a1);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1) == 15
    && (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) != 0
    && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 170) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 0, 0, 0, 0);
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 840))(a1);
      if ( result == 0 && a1[1787] != 22 )
      {
        result = a1[1813];
        if ( result != 0 )
        {
          result = (*(int (/*cdecl*/ **)(int))(*(uint32_t *)result + 40))(17);
          if ( (uint8_t)result != 0 )
          {
            v2 = a1[1813];
            if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 840))(v2, a2) == 8
              || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 840))(v2) == 7
              || (uint8_t)(result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 40))(v2, 273)) != 0
              && (result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 840))(v2)) == 12 )
            {
              result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*a1 + 8))(a1, v2, 0);
              if ( result < 100 )
              {
                v3 = rand() % 100;
                result = a1[1909] != 0 ? 20 : 50;
                if ( v3 < result )
                  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 1104))(a1, 22);
              }
            }
          }
        }
      }
    }
  }
  return result;
}



// 指挥 AI：TAU_COMMAND（RTTI cast, 67L）
// ------------------------------------------------------------
// 0x5A4170 sub_5A4170
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4170(uint32_t *this)
{
  unsigned int i; // esi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // esi
  int v11; // ebx
  int v12; // eax
  unsigned int v13; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 8);
    v13 = i;
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 17) != 0 )
    {
      v8 = *(this + 29);
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 376))(v10);
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      {
        v12 = __RTDynamicCast(
                v10,
                0,
                &IRDActiveObject `RTTI Type Descriptor',
                &CNTauAssaulter `RTTI Type Descriptor',
                0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )
        {
          sub_49C620(12, *(this + 1813), 0);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "TAU_COMMAND",
            -1,
            0,
            0);
        }
      }
      i = v13;
    }
  }
  return result;
}



// RTTI cast 目标解算（54L）
// ------------------------------------------------------------
// 0x5A4270 sub_5A4270
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4270(uint32_t *this)
{
  unsigned int i; // esi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // esi
  int v11; // ebx
  int v12; // eax
  unsigned int v13; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 8);
    v13 = i;
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 17) != 0 )
    {
      v8 = *(this + 29);
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 376))(v10);
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      {
        v12 = __RTDynamicCast(v10, 0, &IRDActiveObject `RTTI Type Descriptor', &CNTauArmy `RTTI Type Descriptor', 0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )
          sub_49C620(11, *(this + 1813), 0);
      }
      i = v13;
    }
  }
  return result;
}



// AI 相位辅助（72L）
// ------------------------------------------------------------
// 0x5A4360 sub_5A4360
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4360(uint32_t *this)
{
  uint32_t *v1; // ebx
  int result; // eax
  unsigned int i; // edi
  int v4; // ecx
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  uint32_t *v10; // esi
  int v11; // eax
  uint32_t *v12; // ecx
  uint32_t *v13; // eax
  int v14; // [esp+4h] [ebp-8h]

  v1 = this;
  result = *(this + 1814);
  if ( result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v4 = v1[29];
      v5 = *(uint32_t *)(v4 + 8);
      result = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(v4 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(v4 + 12) - v6) >> 2 )
        v7 = *(uint32_t *)(v6 + 4 * i);
      else
        v7 = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
      {
        v8 = v1[29];
        v9 = *(uint32_t *)(v8 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
          v10 = *(uint32_t **)(v9 + 4 * i);
        else
          v10 = nullptr;
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*v10 + 376))(v10);
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*v1 + 376))(v1);
        v1 = this;
        if ( v14 == v11 && v10 != this )
        {
          v12 = (uint32_t *)v10[84];
          v13 = (uint32_t *)v10[83];
          if ( v13 != v12 )
          {
            do
            {
              if ( *v13 == 20 )
                break;
              ++v13;
            }
            while ( v13 != v12 );
            if ( v13 != v12 )
              sub_49C620(6, *(this + 1814), 0);
          }
        }
      }
    }
  }
  return result;
}



// 防御光环 AI：AURA_DEFEND + TAU_ROAR 吼叫播报（109L）
// ------------------------------------------------------------
// 0x5A4460 sub_5A4460
// ------------------------------------------------------------
void /*userpurge*/ sub_5A4460(uint32_t *a1@<ecx>, int a2@<ebx>, double a3@<st0>, int ArgList, int a5, int a6, int a7)
{
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // edi
  uint32_t *v12; // eax
  int *v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // eax
  int v17; // [esp-10h] [ebp-28h]
  int v18; // [esp-Ch] [ebp-24h]
  int v19; // [esp-4h] [ebp-1Ch]
  int v20; // [esp+4h] [ebp-14h]
  void *Block; // [esp+8h] [ebp-10h]
  int v22; // [esp+14h] [ebp-4h]

  if ( a1[1639] == 14 && ArgList != 14 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 288))(a1) == 1 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*a1 + 284))(a1, 0, 0, 1, 2);
  switch ( ArgList )
  {
    case 5:
      a3 = sub_5A4360(a1);
      break;
    case 14:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[1554] + 8));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 876))(
        a1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 876))(a1, 1, 0, 0, 0, 0, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 288))(a1) == 0
        || (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 292))(a1) != -14803201 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int))(*a1 + 284))(a1, 1, -14803201, 0, 1);
      }
      break;
    case 15:
      v8 = a1[1554];
      *((uint8_t *)a1 + 8612) = 1;
      sub_4926A0(*(uint32_t *)(v8 + 12));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[1554] + 12));
      v9 = *(uint32_t **)(a5 + 4);
      if ( *v9 != 0xFFFF )
      {
        v19 = a2;
        v10 = 0;
        do
        {
          v18 = v9[v10 + 1];
          v17 = v9[v10];
          (*(void (/*thiscall*/ **)(uint32_t *))(*a1 + 80))(a1);
          v11 = sub_45EBE0(v17, v18);
          if ( v11 != 0 )
          {
            v12 = operator new(0x7Cu);
            Block = v12;
            v22 = 0;
            if ( v12 != nullptr )
              v13 = sub_4B3DF0(v12, 3, 1, 1124204544, 30000, 1);
            else
              v13 = nullptr;
            v14 = *v13;
            v22 = -1;
            (*(void (/*thiscall*/ **)(int *, int, uint32_t *, int, uint32_t, int, int))(v14 + 56))(v13, v11, a1, 1, 0, 38, -1);
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(
              a1,
              "AURA_DEFEND",
              -1,
              0,
              0);
          }
          v9 = *(uint32_t **)(a5 + 4);
          v15 = v9[v10 + 2];
          v10 += 2;
        }
        while ( v15 != 0xFFFF );
        a2 = v19;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 876))(
        a1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 876))(a1, 1, 0, 0, 0, 0, 0);
      v20 = 0;
      Block = (void *)1;
      v16 = rand() % 2;
      sub_4DB200(a1, 24, *(&v20 + v16));
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(a1, "TAU_ROAR", -1, 0, 0);
      break;
    default:
      break;
  }
  sub_4E33D0((int)a1, a2, a3, ArgList, a5, *(float *)&a6, *(float *)&a7);
}


// AI 相位辅助（99L；sub_431230+sub_699000 时钟门, 8608/8612 相位）
// ------------------------------------------------------------
// 0x5A46C0 sub_5A46C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A46C0(int this)
{
  uint32_t *v1; // ebx
  bool v2; // zf
  int v3; // esi
  unsigned int i; // edi
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // esi
  int v13; // eax
  int v14; // edx
  int v15; // eax
  void *v16; // ecx
  uint8_t v17[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v19; // [esp+Ch] [ebp-1Ch]
  int v20; // [esp+10h] [ebp-18h]
  int v21; // [esp+14h] [ebp-14h] BYREF
  uint32_t *v22; // [esp+18h] [ebp-10h]
  int v23; // [esp+24h] [ebp-4h]

  v1 = (uint32_t *)this;
  v2 = *(uint8_t *)(this + 8612) == 1;
  v22 = (uint32_t *)this;
  if ( !v2 && *(uint32_t *)(this + 8608) + 30000 <= (unsigned int)sub_699000(this + 36) )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*v1 + 308))(v1) != 0 )
    {
      v3 = 0;
      Block = nullptr;
      v19 = 0;
      v20 = 0;
      v23 = 0;
      for ( i = 0; ; ++i )
      {
        v5 = v1[29];
        v6 = *(uint32_t *)(v5 + 120);
        v7 = v6 != 0 ? (*(uint32_t *)(v5 + 124) - v6) >> 2 : 0;
        if ( (int)i >= v7 )
          break;
        v8 = *(uint32_t *)(v5 + 120);
        if ( v8 != 0 && i < (*(uint32_t *)(v5 + 124) - v8) >> 2 )
          v9 = *(uint32_t *)(v8 + 4 * i);
        else
          v9 = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 40))(v9, 529) != 0 )
        {
          v10 = v1[29];
          v11 = *(uint32_t *)(v10 + 120);
          if ( v11 != 0 && i < (*(uint32_t *)(v10 + 124) - v11) >> 2 )
            v12 = *(uint32_t *)(v11 + 4 * i);
          else
            v12 = 0;
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 376))(v12);
          v14 = *v1;
          v21 = v13;
          v15 = (*(int (/*thiscall*/ **)(uint32_t *))(v14 + 376))(v1);
          v1 = v22;
          if ( v21 == v15
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v22 + 1244))(v22, v12) != 0
            && (uint8_t)sub_4DAB60(20) != 0 )
          {
            v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 48))(v12);
            sub_431230((int)v17, &v21);
            v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 52))(v12);
            sub_431230((int)v17, &v21);
          }
        }
        v3 = v19;
      }
      v16 = Block;
      if ( Block != nullptr && (v3 - (int)Block) >> 2 != 0 )
      {
        v21 = 0xFFFF;
        sub_431230((int)v17, &v21);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*v1 + 560))(v1, 15, v17, 0, 0);
        v16 = Block;
      }
      v23 = -1;
      if ( v16 != nullptr )
        j__free(v16);
      Block = nullptr;
      v19 = 0;
      v20 = 0;
    }
    v1[2152] = sub_699000((int)(v1 + 9));
  }
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5A4890 sub_5A4890
// ------------------------------------------------------------
void /*thiscall*/ sub_5A4890(uint32_t *this)
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
    v6[0] = 0;
    sub_431230((int)v2, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// AI 相位辅助（84L）
// ------------------------------------------------------------
// 0x5A4940 sub_5A4940
// ------------------------------------------------------------
void /*thiscall*/ sub_5A4940(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  int v4; // edi
  int v5; // edi

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_20;
      if ( rand() % 100 >= 1 )
      {
        if ( rand() % 100 >= 1 )
        {
          v2 = *(this + 1908);
          if ( v2 == 2 && *(this + 1909) == 1 || v2 == 0 && (int)*(this + 1909) >= 1 )
            sub_5A46C0((int)this);
        }
        else
        {
          sub_5A4170(this);
        }
      }
      else
      {
        sub_5A4270(this);
      }
      break;
    case 0xD:
      if ( *(this + 1813) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      break;
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      break;
    case 0x16:
      if ( *(this + 1813) != 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 )
      {
        v3 = *(this + 1813);
        if ( v3 != 0 )
        {
          v4 = (*(int (**)(void))(*(uint32_t *)v3 + 120))();
          if ( ((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= v4
             || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0)
            && ((v5 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                 (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < v5)
             || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 1) )
          {
            if ( rand() % 100 < 20 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
              sub_5A4890(this);
            }
          }
          else
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
          }
        }
      }
      else
      {
LABEL_20:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      }
      break;
    default:
      return;
  }
}



// 【vmt200 命中处理器覆写】格挡反应 handler（虚表 0x6D8AD4 +512 槽, 135L）：
//   Character/Swordman/Effect/Animation/{GuardSpark,GuardCircle}.ani + 播报 SWD_GUARDED +
//   R_TAU_DMG —— 对照研究 20 §3 vt+644 格挡特效族（GuardSpark 家族）的牛头子类实现
// ------------------------------------------------------------
// 0x5A4B20 sub_5A4B20
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4B20(unsigned int *this, int a2, float *a3, int a4)
{
  float *v5; // ebx
  unsigned int v6; // edi
  int v7; // edi
  int v8; // eax
  unsigned int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // edi
  int v20; // ebx
  int v21; // eax
  int v22; // edi
  unsigned int v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+10h] [ebp-18h]
  int v26; // [esp+14h] [ebp-14h]
  int v27; // [esp+18h] [ebp-10h]

  v5 = a3;
  if ( (*(int (/*thiscall*/ **)(unsigned int *))(*this + 840))(this) != 14 || (uint8_t)a4 != 0 )
    goto LABEL_27;
  if ( *((uint8_t *)this + 642) != 0 )
  {
    v6 = *(this + 161);
    goto LABEL_9;
  }
  v7 = *(this + 30);
  if ( v7 != 0 )
  {
    if ( *(uint32_t *)(v7 + 148) == -1 )
      sub_4938F0(*(this + 30));
    v6 = *(uint32_t *)(v7 + 112);
LABEL_9:
    if ( v6 > 1 )
      goto LABEL_27;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 12) != 0
    || (v24 = *this,
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2),
        (*(uint8_t (/*thiscall*/ **)(unsigned int *, int))(v24 + 180))(this, v8) != 0) )
  {
    (*(void (/*thiscall*/ **)(unsigned int *, int))(*this + 1104))(this, 13);
  }
  else
  {
    *((uint8_t *)this + 8604) = 1;
  }
  if ( *((uint8_t *)this + 8604) != 0 )
  {
    (*(void (/*thiscall*/ **)(unsigned int *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(
      this,
      0,
      300,
      300,
      0,
      -3000,
      1);
    (*(void (/*thiscall*/ **)(unsigned int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(unsigned int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
    v9 = *this;
    v10 = (*(int (/*thiscall*/ **)(unsigned int *, int))(*this + 152))(this, 4);
    v11 = sub_432E50(v10);
    (*(void (/*thiscall*/ **)(unsigned int *, int))(v9 + 896))(this, v11);
    v25 = (uint64_t)(a3[3] * 0.5 + *a3);
    v26 = (*(int (/*fastcall*/ **)(unsigned int *, uint32_t))(*this + 124))(
            this,
            (uint64_t)(a3[3] * 0.5 + *a3) >> 32);
    v27 = (uint64_t)(a3[5] * 0.5 + a3[2]);
    v12 = sub_42FCB0(228);
    v13 = 0;
    if ( v12 != 0 )
      v13 = sub_431860(v12, "Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
    if ( sub_44B6C0(284) != 0 )
      v14 = sub_44E1F0(v13, 1);
    else
      v14 = 0;
    sub_45FE80(*(this + 29), v14, 2, 0, v14, (int)this, 0);
    v15 = *(uint32_t *)v14;
    v16 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int, int))(v15 + 148))(v14, v16);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v14 + 112))(v14, v25, v26, v27);
    v17 = sub_42FCB0(228);
    if ( v17 != 0 )
      v18 = sub_431860(v17, "Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
    else
      v18 = 0;
    if ( sub_44B6C0(284) != 0 )
      v19 = sub_44E1F0(v18, 1);
    else
      v19 = 0;
    sub_45FE80(*(this + 29), v19, 2, 0, v19, (int)this, 0);
    v20 = *(uint32_t *)v19;
    v21 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int, int))(v20 + 148))(v19, v21);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v19 + 112))(v19, v25, v26, v27);
    (*(void (/*thiscall*/ **)(unsigned int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "SWD_GUARDED",
      -1,
      0,
      0);
    sub_4015C0((void *)szPassword, 0);
    v5 = a3;
  }
LABEL_27:
  v22 = sub_4DA3B0(a2, v5, a4);
  *((uint8_t *)this + 8604) = 0;
  sub_4015C0("R_TAU_DMG", 9u);
  if ( (*(int (/*thiscall*/ **)(unsigned int *))(*this + 840))(this) != 14
    && (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 308))(this) != 0
    && rand() % 100 < 10 )
  {
    (*(void (/*thiscall*/ **)(unsigned int *, unsigned int *, uint32_t))*(this + 2150))(this + 2150, this, *(this + 1814));
  }
  return v22;
}


// 牛头装载 3：R_TAU_TALK/DMG + TAU_DIE 语音 + Monster/Tau/{wrap01,armlet01,tattoo01,
//   Hair02,Horn01,Weapon01}.equ 六件（97L）
// ------------------------------------------------------------
// 0x5A4E70 sub_5A4E70
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4E70(uint32_t *this)
{
  char *v2; // eax
  char *v3; // edi
  int v4; // eax
  char *v5; // eax
  int v6; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  int v10; // eax
  char *v11; // eax
  char *v12; // ebx
  int v13; // eax
  char *v14; // eax
  int v15; // eax
  int result; // eax
  char *Block; // [esp+10h] [ebp-1Ch]
  char *v18; // [esp+14h] [ebp-18h]
  char *v19; // [esp+18h] [ebp-14h]
  char *v20; // [esp+1Ch] [ebp-10h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);
  sub_4015C0("R_TAU_DMG", 9u);
  sub_4015C0("TAU_DIE", 7u);
  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v20 = sub_4BA9E0(v2, "Monster/Tau/wrap01.equ", 0);
  else
    v20 = nullptr;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v20);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 4))(v4, 1);
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v19 = sub_4BA9E0(v5, "Monster/Tau/armlet01.equ", 0);
  else
    v19 = nullptr;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v19);
  if ( v6 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 4))(v6, 1);
  v7 = (char *)operator new(0x544u);
  if ( v7 != nullptr )
    v18 = sub_4BA9E0(v7, "Monster/Tau/tattoo01.equ", 0);
  else
    v18 = nullptr;
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (char *)operator new(0x544u);
  if ( v9 != nullptr )
    Block = sub_4BA9E0(v9, "Monster/Tau/Hair02.equ", 0);
  else
    Block = nullptr;
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, Block);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  v11 = (char *)operator new(0x544u);
  if ( v11 != nullptr )
    v12 = sub_4BA9E0(v11, "Monster/Tau/Horn01.equ", 0);
  else
    v12 = nullptr;
  v13 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);
  if ( v13 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v13 + 4))(v13, 1);
  v14 = (char *)operator new(0x544u);
  if ( v14 != nullptr )
    v3 = sub_4BA9E0(v14, "Monster/Tau/Weapon01.equ", 0);
  v15 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( v15 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v15 + 4))(v15, 1);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
  sub_4EB2C0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  result = sub_699000((int)(this + 9)) + 15000;
  *(this + 2152) = result;
  *(this + 1894) = 2;
  *((uint8_t *)this + 7542) = 1;
  return result;
}



// ============================================================
// 【分区 6】牛头·唐加斯（Tangas）（0x5A5180-0x5A5BB0）
// 证据：TAU_EQUAKE_CAST/TAU_AXE_SWING、TangasAnimation/EF_EarthQuake{,Strong}.ani、
//       TangasAxeAfterImage.ani 残影、B_SHAUTA_01 登场曲、tangasHair01/tangasAcc01

// 技能播报：TAU_EQUAKE_CAST（地震施法）+ TAU_AXE_SWING（巨斧横扫）（this+8604/8605 相位）
// ------------------------------------------------------------
// 0x5A5180 sub_5A5180
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5180(void *this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax
  uint32_t *v7; // edx

  result = sub_4E33D0(ArgList, a3, a4, a5);
  if ( ArgList == 8 )
  {
    if ( sub_41A5E0((unsigned int)this + 7028) != 0 )
    {
      if ( sub_41A5E0((unsigned int)this + 7028) == 1 )
      {
        (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1104))(this, 19);
        (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));
        sub_4926A0(*((uint32_t *)this + 30));
        return sub_49C5F0(10, 0, 0, 250);
      }
      else if ( sub_41A5E0((unsigned int)this + 7028) == 2 || (result = sub_41A5E0((unsigned int)this + 7028)) == 3 )
      {
        v7 = *(uint32_t **)this;
        *((uint8_t *)this + 8605) = 0;
        *((uint8_t *)this + 8604) = 0;
        return ((int (/*thiscall*/ *)(void *, const char *, int, uint32_t, uint32_t))v7[53])(
                 this,
                 "TAU_EQUAKE_CAST",
                 -1,
                 0,
                 0);
      }
    }
    else
    {
      return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "TAU_AXE_SWING",
               -1,
               0,
               0);
    }
  }
  return result;
}



// 冲刺 AI：TAU_RUSH_LOOP（105L）
// ------------------------------------------------------------
// 0x5A5260 sub_5A5260
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A5260(uint32_t *this, uint32_t *a2)
{
  uint32_t *result; // eax
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edx

  sub_4D90A0(a2);
  result = (uint32_t *)(*a2 - 6);
  switch ( *a2 )
  {
    case 6:
      sub_4D84F0(0, 0);
      v4 = *this;
      *(this + 1813) = a2[3];
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 1104))(this, 20);
      sub_49C5F0(4, 0, 0, 500);
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 768))(this, 12, 8, 0);
      *(this + 1881) = 10000;
      break;
    case 0xA:
      result = (uint32_t *)*(this + 1554);
      if ( *(this + 30) == *result )
      {
        v5 = *this;
        v6 = sub_498F60(this);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v5 + 896))(this, v6, 4);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(
          this,
          0,
          600,
          600,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
        v7 = rand();
        sub_49C5F0(11, 0, 0, v7 % 300 + 300);
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
        result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, uint32_t, uint32_t))(*this + 212))(
                             this,
                             "TAU_RUSH_LOOP",
                             0,
                             0,
                             0);
      }
      break;
    case 0xB:
      v8 = *(this + 1554);
      v9 = *(uint32_t *)(v8 + 4);
      result = (uint32_t *)(v8 + 4);
      if ( *(this + 30) == v9 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);
        result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
      }
      break;
    case 0xC:
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
        result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
                             this,
                             30053,
                             1,
                             0,
                             0,
                             180,
                             0,
                             0,
                             4,
                             0,
                             0,
                             0);
      break;
    case 0xD:
      result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
        result = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
                             this,
                             30054,
                             2,
                             0,
                             0,
                             180,
                             0,
                             0,
                             4,
                             0,
                             0,
                             0);
      break;
    default:
      return result;
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_SHAUTA_01"（牛头曲, 52L）
// ------------------------------------------------------------
// 0x5A5450 sub_5A5450
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5450(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        result = sub_406D60("B_SHAUTA_01");
      break;
    case 4:
      if ( *(this + 1813) != 0 )
      {
        v3 = rand();
        v4 = v3 % 100;
        result = v3 / 100;
        if ( v4 < 30 )
          goto LABEL_5;
      }
      else
      {
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
      result = *(this + 1813);
      if ( result != 0 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_5:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    default:
      return result;
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5A5530 sub_5A5530
// ------------------------------------------------------------
void /*thiscall*/ sub_5A5530(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  void *v6[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v7[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1943) == 3
    && rand() % 100 < 50 )
  {
    v2 = sub_4E7F30(this, 150, 80, 0);
    if ( v2 != 0 )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, bool))(v3 + 144))(this, v5 < v4);
      memset(&v6[1], 0, 12);
      v7[3] = 0;
      v7[0] = 1;
      sub_431230((int)v6, v7);
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, v6, 0, 0);
      sub_5E5260(v6);
    }
  }
}



// 唐加斯地震技能：TangasAnimation/EF_EarthQuake.ani + EF_EarthQuakeStrong.ani +
//   Monster/Tau/TangasAnimation/TangasAxeAfterImage.ani 残影（124L；
//   this+6556==8 大状态门 + vt+308 本地玩家门, 研究 20 §1.2）
// ------------------------------------------------------------
// 0x5A5610 sub_5A5610
// ------------------------------------------------------------
char /*usercall*/ sub_5A5610@<al>(int a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int *v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // edi
  int *v17; // edi
  int v18; // ebx
  int v19; // eax
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v25; // [esp+8h] [ebp-10h]
  int v26; // [esp+8h] [ebp-10h]

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) == 0 || *(uint32_t *)(a1 + 6556) != 8 )
    return sub_4E1780((uint32_t *)a1);
  if ( sub_41A5E0(a1 + 7028) == 1 )
  {
    v4 = *(uint32_t *)(a1 + 120);
    if ( *(uint8_t *)(v4 + 170) != 0 )
    {
      v5 = *(uint32_t *)(a1 + 6216);
      if ( v4 == *(uint32_t *)(v5 + 4) )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 196))(a1, *(uint32_t *)(v5 + 4));
        sub_4926A0(*(uint32_t *)(a1 + 120));
      }
    }
    return sub_4E1780((uint32_t *)a1);
  }
  if ( sub_41A5E0(a1 + 7028) != 2 && sub_41A5E0(a1 + 7028) != 3 )
    return sub_4E1780((uint32_t *)a1);
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1) + 148) == 2 && *(uint8_t *)(a1 + 8605) == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 152))(a1, a2, a3) != 0 )
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 55;
    else
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 55;
    v25 = v6;
    if ( sub_41A5E0(a1 + 7028) == 2 )
    {
      if ( sub_42FCB0(228) != 0 )
      {
        if ( *(uint32_t *)(a1 + 384) < 0x10u )
          v7 = sub_431920(a1 + 108, (char)"TangasAnimation/EF_EarthQuake.ani", 1);
        else
          v7 = sub_431920(*(uint32_t *)(a1 + 364), (char)"TangasAnimation/EF_EarthQuake.ani", 1);
        goto LABEL_24;
      }
    }
    else if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(a1 + 384) < 0x10u )
        v7 = sub_431920(a1 + 108, (char)"TangasAnimation/EF_EarthQuakeStrong.ani", 1);
      else
        v7 = sub_431920(*(uint32_t *)(a1 + 364), (char)"TangasAnimation/EF_EarthQuakeStrong.ani", 1);
LABEL_24:
      v8 = v7;
      if ( sub_44B6C0(284) != 0 )
        v9 = (int *)sub_44E1F0(v8, 1);
      else
        v9 = nullptr;
      sub_45FE80(*(uint32_t *)(a1 + 116), (int)v9, 2, 0, (int)v9, a1, 0);
      v10 = *v9;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v11 + 195);
      (*(void (/*thiscall*/ **)(int *, int, int))(v10 + 112))(v9, v25, v12);
      v13 = *v9;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
      (*(void (/*thiscall*/ **)(int *, int))(v13 + 148))(v9, v14);
      *(uint8_t *)(a1 + 8605) = 1;
      return sub_4E1780((uint32_t *)a1);
    }
    v7 = 0;
    goto LABEL_24;
  }
  if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1) + 148) >= 4 && *(uint8_t *)(a1 + 8604) == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)a1 + 152))(a1, a2, a3) != 0 )
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) + 196;
    else
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 120))(a1) - 196;
    v26 = v15;
    if ( sub_42FCB0(228) != 0 )
      v16 = sub_431860((char)"Monster/Tau/TangasAnimation/TangasAxeAfterImage.ani", 1);
    else
      v16 = 0;
    if ( sub_44B6C0(284) != 0 )
      v17 = (int *)sub_44E1F0(v16, 1);
    else
      v17 = nullptr;
    sub_45FE80(*(uint32_t *)(a1 + 116), (int)v17, 2, 0, (int)v17, a1, 0);
    v18 = *v17;
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1);
    v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 124))(a1, v19 + 21);
    (*(void (/*thiscall*/ **)(int *, int, int))(v18 + 112))(v17, v26, v20);
    v21 = *v17;
    v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 152))(a1);
    v23 = sub_432E50(v22);
    (*(void (/*thiscall*/ **)(int *, int))(v21 + 148))(v17, v23);
    *(uint8_t *)(a1 + 8604) = 1;
    if ( sub_41A5E0(a1 + 7028) == 2 )
      sub_49C5F0(12, v26, 0, 100);
    else
      sub_49C5F0(13, v26, 0, 100);
  }
  return sub_4E1780((uint32_t *)a1);
}


// 唐加斯装载：R_TAU_* 语音 + Monster/Tau/{wrap01,tattoo01,tangasHair01,tangasAcc01,weapon03}.equ（78L）
// ------------------------------------------------------------
// 0x5A5990 sub_5A5990
// ------------------------------------------------------------
int */*usercall*/ sub_5A5990@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  char *v3; // eax
  char *v4; // eax
  int v5; // eax
  char *v6; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  char *v10; // eax
  int v11; // eax
  char *v12; // eax
  char *v13; // eax
  int v14; // eax
  char *v15; // eax
  char *v16; // eax
  int v17; // eax
  int *result; // eax

  a1[1698] = 2;
  a1[1699] = 2;
  a1[1700] = 2;
  a1[1701] = 3;
  a1[1702] = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);
  sub_4015C0("R_TAU_DMG", 9u);
  sub_4015C0("TAU_DIE", 7u);
  v3 = (char *)operator new(0x544u);
  if ( v3 != nullptr )
    v4 = sub_4BA9E0(v3, "Monster/Tau/wrap01.equ", 0);
  else
    v4 = nullptr;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*a1 + 784))(a1, v4, a2);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v7 = sub_4BA9E0(v6, "Monster/Tau/tattoo01.equ", 0);
  else
    v7 = nullptr;
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v7);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (char *)operator new(0x544u);
  if ( v9 != nullptr )
    v10 = sub_4BA9E0(v9, "Monster/Tau/tangasHair01.equ", 0);
  else
    v10 = nullptr;
  v11 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v10);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 4))(v11, 1);
  v12 = (char *)operator new(0x544u);
  if ( v12 != nullptr )
    v13 = sub_4BA9E0(v12, "Monster/Tau/tangasAcc01.equ", 0);
  else
    v13 = nullptr;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v13);
  if ( v14 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v14 + 4))(v14, 1);
  v15 = (char *)operator new(0x544u);
  if ( v15 != nullptr )
    v16 = sub_4BA9E0(v15, "Monster/Tau/weapon03.equ", 0);
  else
    v16 = nullptr;
  v17 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*a1 + 784))(a1, v16);
  if ( v17 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 4))(v17, 1);
  result = (int *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 672))(a1, 3);
  if ( *result > 14 )
    return (int *)(*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 612))(a1, 1, 1);
  return result;
}



// ============================================================
// 【分区 7】石魔像 Golem（0x5A5BB0-0x5A73E0）
// 证据：Particle/StoneLaser.ptl + STONE_LASER_FIRE/READY、Particle/StoneBlade.ptl、
//       SWING_LONG、GOLEM_02、C_BERSERK 狂暴(+6556)、RAIZO_01、GOLEM_DOWN/FIND/DMG/DIE、
//       R_GOLEM_AMB、B_FLATANY_01、STGolemFireSmoke.ani

// 子类扩展字段复位（this+8600..8672, 20L）
// ------------------------------------------------------------
// 0x5A5BB0 sub_5A5BB0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5BB0(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8652) = 0;
  *(uint32_t *)(this + 8656) = 0;
  *(uint32_t *)(this + 8660) = 0;
  *(uint32_t *)(this + 8664) = 0;
  *(uint32_t *)(this + 8668) = 0;
  *(uint32_t *)(this + 8672) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A5BF0 sub_5A5BF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5BF0(uint32_t *this)
{
  uint32_t *v2; // esi
  int i; // edi
  int result; // eax
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx

  v2 = this + 2166;
  for ( i = 2; i != 0; --i )
  {
    if ( *v2 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*v2)(*v2, 1);
    *v2++ = 0;
  }
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2168);
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  *(this + 2168) = 0;
  return result;
}



// 行走 AI：GOLEM_WALK 播报（this+200 主状态门 + 8640 相位）
// ------------------------------------------------------------
// 0x5A5C40 sub_5A5C40
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5C40(uint8_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
    if ( result == *((uint32_t *)this + 1541) )
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148) != 3 || *(this + 8640) != 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
        if ( *(uint32_t *)(result + 148) != 3 && *(this + 8640) == 1 )
          *(this + 8640) = 0;
      }
      else
      {
        result = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                   this,
                   "GOLEM_WALK",
                   -1,
                   0,
                   0);
        *(this + 8640) = 1;
      }
    }
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5A5CD0 sub_5A5CD0
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5CD0(int *a1, int a2)
{
  int result; // eax
  int v3; // esi
  int v4; // eax

  result = sub_4DC390(a1, a2);
  v3 = result;
  if ( result != 3 )
  {
    v4 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);
    if ( v4 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 840))(v4) == 19 )
    {
      *a1 = (uint64_t)((double)*a1 * 1.5);
      return 0;
    }
    else
    {
      return v3;
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A5D40 sub_5A5D40
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5D40(void *this, int a2)
{
  int result; // eax
  unsigned int v4; // edi
  int v5; // edx
  int v6; // [esp+10h] [ebp+8h]

  result = sub_4DBA80(a2);
  if ( a2 == 9 )
  {
    v4 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;
    *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(v4)) + 0.2;
    sub_41A590(v4, v5, v6);
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A5DA0 sub_5A5DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5DA0(void *this, int a2)
{
  int result; // eax
  unsigned int v4; // edi
  int v5; // edx
  int v6; // [esp+10h] [ebp+8h]

  result = sub_4DBC20(a2);
  if ( a2 == 9 )
  {
    v4 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;
    *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(v4)) - 0.2;
    sub_41A590(v4, v5, v6);
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// 石激光技能：Particle/StoneLaser.ptl + STONE_LASER_FIRE 播报（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5A5E00 sub_5A5E00
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5E00(uint32_t *this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edx

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = sub_699000((int)(this + 1640));
    if ( *(this + 2169) + 200 < result )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(uint32_t *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(
             this,
             "Particle/StoneLaser.ptl",
             0,
             90,
             0,
             60,
             4,
             0,
             0,
             0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v3 + 580))(this, 30027, 0, v4);
      v5 = sub_699000((int)(this + 1640));
      v6 = *this;
      *(this + 2169) = v5;
      return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v6 + 212))(
               this,
               "STONE_LASER_FIRE",
               -1,
               0,
               0);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5E90 sub_5A5E90
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5E90(int this, int a2, int a3)
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
  *(uint32_t *)(this + 7580) = 1;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5F20 sub_5A5F20
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5F20(int *a1, int a2)
{
  int result; // eax
  int v3; // edi

  result = sub_5A5CD0(a1, a2);
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 12) != 0
      || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 128) == 0 )
    {
      return v3;
    }
    else
    {
      *a1 = (uint64_t)((double)*a1 * 0.5);
      return 2;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5F90 sub_5A5F90
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5F90(int *a1, int a2)
{
  int result; // eax
  int v3; // esi

  result = sub_5A5CD0(a1, a2);
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 12) != 0 )
    {
      return v3;
    }
    else
    {
      *a1 = (uint64_t)((double)*a1 * 0.60000002);
      return 0;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5FF0 sub_5A5FF0
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5FF0(int *a1, int a2)
{
  int result; // eax
  int v3; // esi

  result = sub_5A5CD0(a1, a2);
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 12) != 0 )
    {
      return v3;
    }
    else
    {
      *a1 = (uint64_t)((double)*a1 * 0.69999999);
      return 0;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6050 sub_5A6050
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6050(int **this)
{
  int *v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // ebx
  int *v6; // edi
  int v7; // edx
  int v8; // eax
  int result; // eax
  int v10; // ecx
  int v11; // [esp-1Ch] [ebp-38h]
  uint32_t v12[5]; // [esp+8h] [ebp-14h]

  v2 = *this;
  v12[0] = 2;
  v12[1] = 3;
  v12[2] = 4;
  v12[3] = 5;
  v3 = ((int (/*thiscall*/ *)(int **))v2[50])(this);
  v4 = (int)*(this + 2170);
  if ( *(uint32_t *)(v3 + 148) == v12[v4] && *(this + 2169) == nullptr )
  {
    v5 = 8 * (5 * v4 - 10);
    if ( ((int (/*thiscall*/ *)(int **))(*this)[38])(this) == 1 )
      v5 = -v5;
    v6 = *(this + 1813);
    v7 = *v6;
    v12[4] = v6;
    v11 = (*(int (**)(void))(v7 + 124))();
    v8 = (*(int (/*thiscall*/ **)(int *))(*v6 + 120))(v6);
    sub_4E4A50(this, 30068, 10, v8 - v5, v11, 0, 4, 0, 0, 0);
    *(this + 2169) = (int *)1;
  }
  result = ((int (/*thiscall*/ *)(int **))(*this)[50])(this);
  v10 = (int)*(this + 2170);
  if ( *(uint32_t *)(result + 148) == v12[v10] + 1 )
  {
    *(this + 2169) = nullptr;
    *(this + 2170) = (int *)(v10 + 1);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6130 sub_5A6130
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6130(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // [esp-20h] [ebp-28h]
  int v13; // [esp-20h] [ebp-28h]
  int v14; // [esp-20h] [ebp-28h]

  result = *(this + 2169);
  if ( result == 0 )
  {
    v3 = *this;
    *(this + 2169) = 1;
    v4 = (*(int (**)(void))(v3 + 152))();
    v5 = *(this + 1813);
    v6 = v4 != 0 ? -30 : 30;
    v12 = (*(int (**)(void))(*(uint32_t *)v5 + 124))() - 30;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 120))(v5);
    sub_4E4A50(this, 30068, 10, v6 + v7, v12, 0, 4, 0, 0, 0);
    v8 = *(this + 1813);
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 124))(v8);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 120))(v8);
    sub_4E4A50(this, 30068, 10, v9, v13, 0, 4, 0, 0, 0);
    v10 = *(this + 1813);
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 124))(v10) + 30;
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 120))(v10);
    return sub_4E4A50(this, 30068, 10, v6 + v11, v14, 0, 4, 0, 0, 0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6210 sub_5A6210
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6210(void *this, int a2)
{
  int v3; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0
    || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 12) != 0
    || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 8
    || (v3 = sub_41A5E0((unsigned int)this + 7028)) != 1 )
  {
    LOBYTE(v3) = 0;
  }
  return v3;
}



// 石刃技能：引用 Particle/StoneBlade.ptl
// ------------------------------------------------------------
// 0x5A6270 sub_5A6270
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6270(int *this)
{
  int v2; // edi
  int v3; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(int *, const char *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 588))(
         this,
         "Particle/StoneBlade.ptl",
         0,
         50,
         0,
         135,
         4,
         0,
         0,
         0);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(v2 + 580))(this, 30026, 0, v3);
}



// 挥击技能：SWING_LONG 播报（this+200/+204 主状态硬直 + 8640/8641 相位）
// ------------------------------------------------------------
// 0x5A62B0 sub_5A62B0
// ------------------------------------------------------------
char /*thiscall*/ sub_5A62B0(int this)
{
  int *v2; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this) == 0 )
    sub_5A5C40((uint8_t *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8
    && (sub_41A5E0(this + 7028) == 0 || sub_41A5E0(this + 7028) == 2) )
  {
    if ( *(uint8_t *)(this + 8640) != 0
      || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) != 2 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) > 2 )
        *(uint8_t *)(this + 8640) = 0;
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "SWING_LONG",
        -1,
        0,
        0);
      *(uint8_t *)(this + 8640) = 1;
    }
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8
    && sub_41A5E0(this + 7028) == 2
    && *(uint8_t *)(this + 8641) == 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 1 )
  {
    v2 = *(int **)(this + 6216);
    if ( v2 != nullptr && (*(uint32_t *)(this + 6220) - (int)v2) >> 2 != 0 )
    {
      sub_4926A0(*v2);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, int, uint32_t))(*(uint32_t *)this + 204))(
        this,
        1000,
        **(uint32_t **)(this + 6216),
        -55,
        -150,
        1,
        0);
      *(uint8_t *)(this + 8641) = 1;
    }
  }
  return sub_4E1780((uint32_t *)this);
}



// 技能播报：GOLEM_02（魔像二段动作, this+208/8641）
// ------------------------------------------------------------
// 0x5A63E0 sub_5A63E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A63E0(uint32_t *this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax
  uint32_t *v7; // ecx
  int v8; // [esp+8h] [ebp-4h]

  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  result = sub_4E33D0(ArgList, a3, a4, a5);
  if ( ArgList == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
      *((uint8_t *)this + 8641) = 0;
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result != 1 )
      result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "GOLEM_02",
                 -1,
                 0,
                 0);
  }
  if ( v8 == 8 && ArgList != 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 2 )
    {
      v7 = (uint32_t *)*(this + 1554);
      if ( v7 != nullptr )
      {
        result = (*(this + 1555) - (int)v7) >> 2;
        if ( result != 0 )
          return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *v7);
      }
    }
  }
  return result;
}



// 石激光开火：STONE_LASER_FIRE 播报（this+208/8604 相位）
// ------------------------------------------------------------
// 0x5A64A0 sub_5A64A0
// ------------------------------------------------------------
char /*thiscall*/ sub_5A64A0(uint32_t *this)
{
  int v2; // eax
  int v3; // edx

  v2 = *(this + 30);
  if ( *(int *)(v2 + 148) >= 3 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      sub_5A5E00(this);
    LOBYTE(v2) = *((uint8_t *)this + 8604);
    if ( (uint8_t)v2 == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
      v3 = *this;
      *((uint8_t *)this + 8604) = 1;
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v3 + 212))(
                     this,
                     "STONE_LASER_FIRE",
                     -1,
                     0,
                     0);
    }
  }
  return v2;
}



// 石激光蓄力：STONE_LASER_READY 播报（this+204/+208/8604 相位, 66L）
// ------------------------------------------------------------
// 0x5A6520 sub_5A6520
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6520(int *this, int ArgList, float a3, int a4, int a5)
{
  int v6; // ebx
  int result; // eax
  int v8; // edx
  int *v9; // ecx
  uint32_t *v10; // ecx

  v6 = *(this + 1639);
  result = sub_5A63E0(this, ArgList, a3, a4, a5);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
      v8 = *this;
      *((uint8_t *)this + 8604) = 0;
      *(this + 2169) = 0;
      result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(
                 this,
                 "STONE_LASER_READY",
                 -1,
                 0,
                 0);
      v9 = (int *)*(this + 1554);
      if ( v9 != nullptr )
      {
        result = (*(this + 1555) - (int)v9) >> 2;
        if ( result != 0 )
        {
          sub_4926A0(*v9);
          result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int, int, uint32_t))(*this + 204))(
                     this,
                     1000,
                     *(uint32_t *)*(this + 1554),
                     70,
                     -55,
                     1,
                     0);
        }
      }
    }
  }
  if ( v6 == 8 && ArgList != 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 1 )
    {
      v10 = (uint32_t *)*(this + 1554);
      if ( v10 != nullptr )
      {
        result = (*(this + 1555) - (int)v10) >> 2;
        if ( result != 0 )
          return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *v10);
      }
    }
  }
  return result;
}



// 狂暴 AI：C_BERSERK 播报（62L；读 this+6556 大状态 → 狂暴条件门【推断：濒死/血线触发】）
// ------------------------------------------------------------
// 0x5A6630 sub_5A6630
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6630(int this, int ArgList, float a3, int a4, int a5)
{
  int v6; // ebx
  int result; // eax
  int *v8; // ecx
  uint32_t *v9; // ecx

  v6 = *(uint32_t *)(this + 6556);
  result = sub_5A63E0((uint32_t *)this, ArgList, a3, a4, a5);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 1 )
    {
      *(uint8_t *)(this + 8604) = 0;
      v8 = *(int **)(this + 6216);
      if ( v8 != nullptr )
      {
        result = (*(uint32_t *)(this + 6220) - (int)v8) >> 2;
        if ( result != 0 )
        {
          sub_4926A0(*v8);
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, int, uint32_t))(*(uint32_t *)this + 204))(
            this,
            1000,
            **(uint32_t **)(this + 6216),
            85,
            -55,
            1,
            0);
          result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                     this,
                     "C_BERSERK",
                     -1,
                     0,
                     0);
        }
      }
    }
  }
  if ( v6 == 8 && ArgList != 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 1 )
    {
      v9 = *(uint32_t **)(this + 6216);
      if ( v9 != nullptr )
      {
        result = (*(uint32_t *)(this + 6220) - (int)v9) >> 2;
        if ( result != 0 )
          return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *v9);
      }
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6710 sub_5A6710
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6710(uint32_t *this)
{
  if ( *(this + 1639) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 1 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);
  return sub_5A62B0((int)this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6740 sub_5A6740
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6740(uint32_t *this, int a2, int a3)
{
  int result; // eax
  int v4; // eax
  double v5; // st7

  result = a3;
  if ( a3 == 0 )
  {
    v4 = *(this + 1905);
    v5 = *(float *)(v4 + 68);
    result = v4 + 64;
    *(float *)(result + 4) = v5 * 0.76923078;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6770 sub_5A6770
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6770(int this, int a2, int a3)
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
  *(uint8_t *)(this + 7534) = 1;
  if ( a3 == 0 )
    *(float *)(*(uint32_t *)(this + 7620) + 68) = *(float *)(*(uint32_t *)(this + 7620) + 68) * 1.3;
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5A6820 sub_5A6820
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6820(uint32_t *this, int ArgList, float a3, int a4, int a5)
{
  int v6; // ecx
  int v7; // ebx
  int result; // eax

  if ( ArgList == 8 && *(int *)(*(uint32_t *)(LODWORD(a3) + 4) + 4) >= 1 )
  {
    v6 = *(this + 1813);
    if ( v6 != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 120))(v6);
      if ( (signed int)abs32(v7 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) < *(uint32_t *)(*(this + 1905) + 16) )
        *(uint32_t *)(*(uint32_t *)(LODWORD(a3) + 4) + 4) = 0;
    }
  }
  result = sub_4E33D0(ArgList, a3, a4, a5);
  if ( ArgList == 8 )
  {
    *(this + 2169) = 0;
    *(this + 2170) = 0;
    result = sub_699000((int)(this + 1910));
    *(this + 2171) = result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A68C0 sub_5A68C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A68C0(uint32_t *this, int a2, int a3)
{
  int result; // eax
  bool v5; // cc
  unsigned int v6; // edi
  int v7; // edx
  unsigned int v8; // edi
  int v9; // edx
  int v10; // eax
  double v11; // st7
  int v12; // [esp+10h] [ebp+Ch]
  int v13; // [esp+10h] [ebp+Ch]

  if ( a3 == 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 102;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v6)) - 1.0;
    sub_41A590(v6, v7, v12);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 158;
    *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(v8)) - 1.0;
    sub_41A590(v8, v9, v13);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    result = a2;
    if ( a2 == 0 )
    {
      *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.5;
      return result;
    }
    if ( a2 <= 0 )
      return result;
    v5 = a2 <= 2;
    goto LABEL_8;
  }
  result = a3 - 2;
  if ( a3 == 2 )
  {
    result = a2;
    if ( a2 >= 0 )
    {
      v5 = a2 <= 1;
LABEL_8:
      if ( v5 )
      {
        v10 = *(this + 1905);
        v11 = *(float *)(v10 + 68);
        result = v10 + 64;
        *(float *)(result + 4) = v11 * 0.5;
        *(float *)(*(this + 1905) + 100) = *(float *)(*(this + 1905) + 100) * 0.5;
      }
    }
  }
  return result;
}



// AI 相位辅助（94L）
// ------------------------------------------------------------
// 0x5A69C0 sub_5A69C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A69C0(char *this, int a2, int a3)
{
  char *v4; // ecx
  int result; // eax
  int v6; // eax
  double v7; // st7
  int v8; // edx
  unsigned int v9; // edi
  int v10; // edx
  unsigned int v11; // edi
  int v12; // edx
  int v13; // eax
  double v14; // st7
  int v15; // [esp+14h] [ebp+Ch]
  int v16; // [esp+14h] [ebp+Ch]

  *(this + 7558) = 0;
  *(this + 7557) = 0;
  *(this + 7556) = 0;
  *(this + 7534) = 0;
  *(this + 7533) = 0;
  *(this + 7532) = 0;
  *(this + 7531) = 0;
  *(uint32_t *)(this + 7535) = 0;
  v4 = this + 7539;
  *(uint32_t *)v4 = 0;
  *((uint32_t *)v4 + 1) = 0;
  *((uint32_t *)v4 + 2) = 0;
  *((uint32_t *)v4 + 3) = 0;
  v4[16] = 0;
  *((uint32_t *)this + 1893) = 0;
  *((uint32_t *)this + 1892) = 0;
  *((uint32_t *)this + 1891) = 0;
  *((uint32_t *)this + 1897) = 0;
  *((uint32_t *)this + 1896) = 0;
  *((uint32_t *)this + 1895) = 0;
  *((uint32_t *)this + 1894) = 0;
  *((uint32_t *)this + 1899) = 0;
  *((uint32_t *)this + 1895) = 1;
  if ( a3 != 0 )
  {
    result = a3 - 2;
    if ( a3 == 2 )
    {
      result = a2;
      if ( (unsigned int)a2 <= 1 )
      {
        v6 = *((uint32_t *)this + 1905);
        v7 = *(float *)(v6 + 68);
        result = v6 + 64;
        *(float *)(result + 4) = v7 + v7;
        *(float *)(*((uint32_t *)this + 1905) + 100) = *(float *)(*((uint32_t *)this + 1905) + 100)
                                                   + *(float *)(*((uint32_t *)this + 1905) + 100);
      }
    }
  }
  else
  {
    v8 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;
    v9 = (*(int (/*thiscall*/ **)(char *, uint32_t))(v8 + 672))(this, 0) + 102;
    *(float *)&v15 = COERCE_FLOAT(sub_41A5E0(v9)) + 1.0;
    sub_41A590(v9, v10, v15);
    v11 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(v11)) + 1.0;
    sub_41A590(v11, v12, v16);
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    result = a2;
    if ( a2 != 0 )
    {
      if ( a2 > 0 && a2 <= 2 )
      {
        v13 = *((uint32_t *)this + 1905);
        v14 = *(float *)(v13 + 68);
        result = v13 + 64;
        *(float *)(result + 4) = v14 + v14;
        *(float *)(*((uint32_t *)this + 1905) + 100) = *(float *)(*((uint32_t *)this + 1905) + 100)
                                                   + *(float *)(*((uint32_t *)this + 1905) + 100);
      }
    }
    else
    {
      *(float *)(*((uint32_t *)this + 1905) + 36) = *(float *)(*((uint32_t *)this + 1905) + 36)
                                                + *(float *)(*((uint32_t *)this + 1905) + 36);
    }
  }
  return result;
}



// AI 字段访问（this+8680）
// ------------------------------------------------------------
// 0x5A6B60 sub_5A6B60
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6B60(uint32_t **this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax
  int *v7; // eax

  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 3 )
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 1554));
  result = sub_5A6520((int *)this, ArgList, a3, a4, a5);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 3 )
    {
      v7 = *(this + 1554);
      *((uint8_t *)this + 8680) = 0;
      sub_4926A0(*v7);
      return ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, int, int, int, uint32_t))(*this)[51])(
               this,
               1000,
               **(this + 1554),
               70,
               -55,
               1,
               0);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6C00 sub_5A6C00
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6C00(uint32_t *this)
{
  int v2; // eax

  sub_5A62B0((int)this);
  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( v2 == 8 )
  {
    v2 = sub_41A5E0((unsigned int)(this + 1757));
    if ( v2 == 1 )
      LOBYTE(v2) = sub_5A64A0(this);
  }
  return v2;
}



// AI 主状态门（this+200, 76L）
// ------------------------------------------------------------
// 0x5A6C40 sub_5A6C40
// ------------------------------------------------------------
void /*thiscall*/ sub_5A6C40(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // edi
  uint32_t *v14; // edi
  void *v15; // ecx
  int v16; // [esp-8h] [ebp-34h]
  char v17[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  uint32_t *v19; // [esp+18h] [ebp-14h]
  bool v20; // [esp+1Fh] [ebp-Dh]
  int v21; // [esp+28h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 2169) == 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) == 4 )
  {
    v2 = *this;
    *(this + 2169) = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(v2 + 876))(this, 0, 1800, 1800, 0, -300, 1);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v3 + 896))(this, v4);
  }
  if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 4
    && *(this + 2171) + 25 < (unsigned int)sub_699000((int)(this + 1910)) )
  {
    v5 = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 924))(this, 42)];
    v6 = *this;
    v19 = v5;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 152))(this);
    v8 = *this;
    v9 = *v5;
    v20 = v7 == 0;
    v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 128))(this);
    v11 = rand();
    v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v11 % 40 + v10);
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, v12 + 10) != 0 ? -30 : 30;
    v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v13;
    v14 = v19;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 40))(v19, v16);
    *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v19 + 28))(v19) + 84) = v20;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v14 + 12))(v14, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, char *))(*v14 + 92))(v14, v17);
    v15 = (void *)*(this + 29);
    v21 = 0;
    sub_4600B0(v15, 2, 0, (int)v17);
    *(this + 2171) = sub_699000((int)(this + 1910));
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 登场/技能播报：RAIZO_01（曲/语音槽, this+8680）
// ------------------------------------------------------------
// 0x5A6E00 sub_5A6E00
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6E00(int this)
{
  int v2; // eax

  sub_5A62B0(this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 1 )
    sub_5A64A0((uint32_t *)this);
  LOBYTE(v2) = *(uint8_t *)(this + 8680);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( v2 == 8 )
    {
      v2 = sub_41A5E0(this + 7028);
      if ( v2 == 3 )
      {
        v2 = *(uint32_t *)(this + 120);
        if ( v2 != 0 && *(int *)(v2 + 148) >= 4 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            sub_5A6270((int *)this);
          LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                         this,
                         "RAIZO_01",
                         -1,
                         0,
                         0);
          *(uint8_t *)(this + 8680) = 1;
        }
      }
    }
  }
  return v2;
}



// 埋伏魔像语音组：GOLEM_DOWN/GOLEM_FIND/GOLEM_DMG/GOLEM_DIE + R_GOLEM_AMB（伏击埋地）
// ------------------------------------------------------------
// 0x5A6EA0 sub_5A6EA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6EA0(int this)
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

  v11 = 10;
  v10 = (int)"GOLEM_DOWN";
  *(uint32_t *)(this + 6792) = 1;
  *(uint32_t *)(this + 6796) = 2;
  *(uint32_t *)(this + 6800) = 3;
  *(uint32_t *)(this + 6804) = 3;
  *(uint32_t *)(this + 6808) = 4;
  sub_4015C0((void *)v10, v11);
  sub_4015C0("GOLEM_FIND", 0xAu);
  sub_4015C0("GOLEM_DMG", 9u);
  sub_4015C0("GOLEM_DIE", 9u);
  v11 = 10000;
  v10 = 5000;
  v12 = &v3;
  *(uint32_t *)(this + 7324) = 300;
  *(uint8_t *)(this + 8640) = 0;
  v9 = 15;
  v8 = 0;
  LOBYTE(v4) = 0;
  sub_4015C0("R_GOLEM_AMB", 0xBu);
  return sub_4DE5E0(v3, v4, v5, v6, v7, v8, v9, v10, v11);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6F70 sub_5A6F70
// ------------------------------------------------------------
void /*thiscall*/ sub_5A6F70(int *this)
{
  int v2; // eax
  int v3; // eax

  sub_5A62B0((int)this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8 )
  {
    v2 = sub_41A5E0((unsigned int)(this + 1757)) - 1;
    if ( v2 != 0 )
    {
      v3 = v2 - 1;
      if ( v3 != 0 )
      {
        if ( v3 == 1 && *(this + 1813) != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
          sub_5A6130(this);
      }
      else if ( *(this + 1813) != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
      {
        sub_5A6050((int **)this);
      }
    }
    else
    {
      sub_5A6C40(this);
    }
  }
}



// 登场曲：sub_406D60 写 "B_FLATANY_01"（77L）
// ------------------------------------------------------------
// 0x5A6FF0 sub_5A6FF0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A6FF0(uint32_t *this)
{
  uint32_t *v2; // ecx
  void *v3; // eax
  int v4; // eax
  int v5; // ecx
  float Block; // [esp+4h] [ebp-18h]
  float v7; // [esp+8h] [ebp-14h]

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        sub_406D60("B_FLATANY_01");
      break;
    case 4:
      v2 = this;
      if ( *(this + 1813) != 0 )
        goto LABEL_10;
      goto LABEL_5;
    case 5:
      if ( *(this + 1813) == 0 )
LABEL_5:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      break;
    case 0xD:
    case 0xE:
    case 0xF:
      if ( *(this + 1813) != 0 )
      {
        v2 = this;
LABEL_10:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(v2, 5);
      }
      break;
    default:
      break;
  }
  v7 = (double)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0) * 0.0099999998;
  Block = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * v7 < Block )
  {
    v5 = *(this + 2168);
    if ( v5 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 80))(v5) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2168) + 76))(*(this + 2168), 0);
  }
  else
  {
    if ( *(this + 2168) == 0 )
    {
      v3 = operator new(0x64u);
      if ( v3 != nullptr )
        v4 = sub_51A7D0(v3);
      else
        v4 = 0;
      *(this + 2168) = v4;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 64))(v4) + 36) = 0;
    }
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2168) + 80))(*(this + 2168)) == 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2168) + 56))(
        *(this + 2168),
        this,
        this,
        1,
        0,
        0,
        -1);
  }
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5A71B0 sub_5A71B0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A71B0(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // [esp-18h] [ebp-3Ch]
  int v8; // [esp-10h] [ebp-34h]
  void *v9[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v10[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && *(this + 1943) == 3 )
  {
    if ( rand() % 100 >= 50 )
    {
      if ( rand() % 100 < 25 )
      {
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
        v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
        sub_4E4A50(this, 30022, 0, v6, v7, 0, v8, 0, 0, 0);
      }
    }
    else
    {
      v2 = sub_4E7F30(this, 200, 75, 0);
      if ( v2 != 0 )
      {
        v3 = *this;
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 120))(v2);
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
        (*(void (/*thiscall*/ **)(uint32_t *, bool))(v3 + 144))(this, v5 < v4);
        memset(&v9[1], 0, 12);
        v10[3] = 0;
        v10[0] = 1;
        sub_431230((int)v9, v10);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, v9, 0, 0);
        sub_5E5260(v9);
      }
    }
  }
}



// 格挡特效：Character/Swordman/Effect/Animation/GuardSpark.ani + SWD_GUARDED 播报
//   （43L；与 0x5A4B20 vmt200 覆写同族, 此为普通槽位版本）
// ------------------------------------------------------------
// 0x5A72E0 sub_5A72E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A72E0(int *this, int a2, float *a3)
{
  int v4; // ebx
  char *v5; // eax
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v11; // [esp-4h] [ebp-20h]

  v4 = 0;
  if ( sub_42FCB0(228) != 0 )
    v4 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
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
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(char *, int))(v7 + 148))(v6, v8);
  v9 = *(uint32_t *)v6;
  v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, (uint64_t)a3[2]) - 1;
  (*(void (/*fastcall*/ **)(char *, uint32_t, uint32_t, int))(v9 + 112))(
    v6,
    (uint64_t)*a3 >> 32,
    (uint64_t)*a3,
    v11);
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SWD_GUARDED", -1, 0, 0);
}



// ============================================================
// 【分区 8】石魔像·五色兵装（SG/ST/CL/GD/BR/PT）（0x5A73E0-0x5A82B0）
// 证据：Monster/Golem/{SG,ST,CL,GD,BR}/ST*.equ 分色部件 + GD/PT* 头/角件、
//       Particle/STGolemBullet.ptl / STGolemFire.ptl / STGolemHikari.ptl / BRGolemBullet.ptl

// 烟火特效装载：Monster/Golem/Particle/ani/STGolemFireSmoke.ani（102L；sub_431860）
// ------------------------------------------------------------
// 0x5A73E0 sub_5A73E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A73E0(uint32_t *this)
{
  int v2; // edi
  int v3; // edi
  int **v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  void *v8; // ecx
  bool v9; // zf
  int v10; // edi
  int v11; // edi
  char *v12; // eax
  char *v13; // edi
  int v14; // ecx
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
    v3 = v2 + 95;
  else
    v3 = v2 - 95;
  v27 = v3;
  v4 = (int **)(this + 2166);
  v26 = 2;
  do
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(**v4 + 12))(*v4, 0);
    v5 = **v4;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v6 + 65);
    (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 40))(*v4, v27, v7);
    (*(void (/*thiscall*/ **)(int *, char *))(**v4 + 92))(*v4, v21);
    v8 = (void *)*(this + 29);
    v28 = 0;
    sub_4600B0(v8, 2, 0, (int)v21);
    v28 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++v4;
    v9 = v26 == 1;
    Block = nullptr;
    v23 = 0;
    v24 = 0;
    --v26;
  }
  while ( !v9 );
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
    v11 = v10 + 95;
  else
    v11 = v10 - 95;
  v27 = v11;
  v26 = sub_42FCB0(228);
  v28 = 1;
  if ( v26 != 0 )
    v26 = sub_431860((char)"Monster/Golem/Particle/ani/STGolemFireSmoke.ani", 1);
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
  v14 = *(this + 29);
  v28 = -1;
  sub_45FE80(v14, (int)v13, 2, 0, (int)v13, (int)this, 0);
  v15 = *(uint32_t *)v13;
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(char *, int))(v15 + 148))(v13, v16);
  v17 = *(uint32_t *)v13;
  v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v18 + 110);
  return (*(int (/*thiscall*/ **)(char *, int, int))(v17 + 112))(v13, v27, v19);
}



// 埋地/起立 AI：GOLEM_DOWN 播报（this+8604 相位）
// ------------------------------------------------------------
// 0x5A7590 sub_5A7590
// ------------------------------------------------------------
char /*thiscall*/ sub_5A7590(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // edi
  int v5; // eax

  LOBYTE(v2) = *((uint8_t *)this + 8604);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = *(this + 30);
    if ( *(uint32_t *)(v2 + 148) == 2 )
    {
      v3 = *this;
      *((uint8_t *)this + 8604) = 1;
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v3 + 308))(this) != 0 )
      {
        v4 = *this;
        v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 128))(this, 4, 0, 0, 0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int))(v4 + 580))(
          this,
          30009,
          0,
          *(this + 2161),
          0,
          85,
          0,
          v5 + 55);
      }
      sub_5A73E0(this);
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                     this,
                     "GOLEM_DOWN",
                     -1,
                     0,
                     0);
    }
  }
  return v2;
}



// 埋地/起立 AI：GOLEM_DOWN 播报（this+8604 相位, 68L）
// ------------------------------------------------------------
// 0x5A7610 sub_5A7610
// ------------------------------------------------------------
char /*thiscall*/ sub_5A7610(uint32_t **this)
{
  uint32_t **v1; // ebx
  int v2; // eax
  const void **v3; // ebx
  double v4; // st7
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax
  int v9; // [esp+8h] [ebp-70h]
  uint8_t v11[98]; // [esp+10h] [ebp-68h]

  v1 = this;
  LOBYTE(v2) = *((uint8_t *)this + 8604);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = (int)*(this + 30);
    if ( *(uint32_t *)(v2 + 148) == 3 )
    {
      if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
      {
        v3 = (const void **)(v1 + 2161);
        v9 = 5;
        do
        {
          qmemcpy(v11, *v3, sizeof(v11));
          v4 = (double)(100 - rand() % 20) * 0.0099999998;
          *(uint32_t *)((char *)*v3 + 15) = (uint64_t)((double)*(int *)((char *)*v3 + 15) * v4);
          *(uint32_t *)((char *)*v3 + 19) = (uint64_t)((double)*(int *)((char *)*v3 + 19) * v4);
          *(uint32_t *)((char *)*v3 + 63) = *(uint32_t *)((char *)*v3 + 19) - *(uint32_t *)((char *)*v3 + 15);
          *((uint32_t *)*v3 + 18) = rand() % 71 - 35;
          v5 = *this;
          v6 = ((int (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t))(*this)[32])(this, 4, 0, 0, 0);
          ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, const void *, uint32_t, int, uint32_t, int))v5[145])(
            this,
            30002,
            0,
            *v3,
            0,
            85,
            0,
            v6 + 55);
          v7 = v9;
          qmemcpy((void *)*v3++, v11, 98);
          --v9;
        }
        while ( v7 != 1 );
        v1 = this;
      }
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*v1)[52])(v1, *v1[1554]);
      sub_5A73E0(v1);
      LOBYTE(v2) = ((int (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*v1)[53])(
                     v1,
                     "GOLEM_DOWN",
                     -1,
                     0,
                     0);
      *((uint8_t *)v1 + 8604) = 1;
    }
  }
  return v2;
}



// SG 魔像装载：Monster/Golem/SG/{STHead,STLeftArm,STRightArm,STLeg}.equ 四部件
// ------------------------------------------------------------
// 0x5A7770 sub_5A7770
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7770(void *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // eax
  char *v5; // eax
  char *v6; // ebx
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int result; // eax
  char *Block; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    Block = sub_4BA9E0(v2, "Monster/Golem/SG/STHead.equ", 0);
  else
    Block = nullptr;
  v4 = (char *)operator new(0x544u);
  if ( v4 != nullptr )
    v13 = sub_4BA9E0(v4, "Monster/Golem/SG/STLeftArm.equ", 0);
  else
    v13 = nullptr;
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Golem/SG/STRightArm.equ", 0);
  else
    v6 = nullptr;
  v7 = (char *)operator new(0x544u);
  if ( v7 != nullptr )
    v3 = sub_4BA9E0(v7, "Monster/Golem/SG/STLeg.equ", 0);
  v8 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 4))(v9, 1);
  v10 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// ST 魔像装载：Monster/Golem/ST/ST*.equ 四部件 + Particle/{STGolemBullet,STGolemFire,
//   STGolemHikari}.ptl 三粒子（99L）
// ------------------------------------------------------------
// 0x5A78E0 sub_5A78E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A78E0(uint32_t *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // eax
  char *v5; // eax
  char *v6; // ebx
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  uint32_t *v12; // edi
  int i; // ebx
  void (/*thiscall*/ ***v14)(uint32_t, int); // ecx
  int v15; // eax
  void (/*thiscall*/ ***v16)(uint32_t, int); // ecx
  int result; // eax
  char *Block; // [esp+10h] [ebp-14h]
  char *v19; // [esp+14h] [ebp-10h]

  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    Block = sub_4BA9E0(v2, "Monster/Golem/ST/STHead.equ", 0);
  else
    Block = nullptr;
  v4 = (char *)operator new(0x544u);
  if ( v4 != nullptr )
    v19 = sub_4BA9E0(v4, "Monster/Golem/ST/STLeftArm.equ", 0);
  else
    v19 = nullptr;
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Golem/ST/STRightArm.equ", 0);
  else
    v6 = nullptr;
  v7 = (char *)operator new(0x544u);
  if ( v7 != nullptr )
    v3 = sub_4BA9E0(v7, "Monster/Golem/ST/STLeg.equ", 0);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 4))(v9, 1);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v19);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  v11 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, Block);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 4))(v11, 1);
  v12 = this + 2161;
  for ( i = 5; i != 0; --i )
    *v12++ = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/STGolemBullet.ptl");
  v14 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2166);
  if ( v14 != nullptr )
  {
    (**v14)(v14, 1);
    *(this + 2166) = 0;
  }
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v15 = sub_4C3640(this + 91, "Particle/STGolemFire.ptl", this);
    else
      v15 = sub_4C3640(*(this + 91), "Particle/STGolemFire.ptl", this);
  }
  else
  {
    v15 = 0;
  }
  v16 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);
  *(this + 2166) = v15;
  if ( v16 != nullptr )
  {
    (**v16)(v16, 1);
    *(this + 2167) = 0;
  }
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/STGolemHikari.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/STGolemHikari.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 2167) = result;
  return result;
}



// CL 魔像装载：Monster/Golem/CL/ST*.equ 四部件
// ------------------------------------------------------------
// 0x5A7B50 sub_5A7B50
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7B50(void *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // eax
  char *v5; // eax
  char *v6; // ebx
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int result; // eax
  char *v12; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v12 = sub_4BA9E0(v2, "Monster/Golem/CL/STHead.equ", 0);
  else
    v12 = nullptr;
  v4 = (char *)operator new(0x544u);
  if ( v4 != nullptr )
    v13 = sub_4BA9E0(v4, "Monster/Golem/CL/STLeftArm.equ", 0);
  else
    v13 = nullptr;
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Golem/CL/STRightArm.equ", 0);
  else
    v6 = nullptr;
  v7 = (char *)operator new(0x544u);
  if ( v7 != nullptr )
    v3 = sub_4BA9E0(v7, "Monster/Golem/CL/STLeg.equ", 0);
  v8 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 4))(v9, 1);
  v10 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v12);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// GD 魔像装载：Monster/Golem/GD/ST*.equ 四部件
// ------------------------------------------------------------
// 0x5A7CC0 sub_5A7CC0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7CC0(void *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // eax
  char *v5; // eax
  char *v6; // ebx
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int result; // eax
  char *v12; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v12 = sub_4BA9E0(v2, "Monster/Golem/GD/STHead.equ", 0);
  else
    v12 = nullptr;
  v4 = (char *)operator new(0x544u);
  if ( v4 != nullptr )
    v13 = sub_4BA9E0(v4, "Monster/Golem/GD/STLeftArm.equ", 0);
  else
    v13 = nullptr;
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Golem/GD/STRightArm.equ", 0);
  else
    v6 = nullptr;
  v7 = (char *)operator new(0x544u);
  if ( v7 != nullptr )
    v3 = sub_4BA9E0(v7, "Monster/Golem/GD/STLeg.equ", 0);
  v8 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 4))(v9, 1);
  v10 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v12);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// BR 魔像装载：Monster/Golem/BR/ST*.equ 四部件 + Particle/{BRGolemBullet,STGolemFire,
//   STGolemHikari}.ptl（97L）
// ------------------------------------------------------------
// 0x5A7E30 sub_5A7E30
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7E30(uint32_t *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // eax
  char *v5; // eax
  char *v6; // ebx
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  void (/*thiscall*/ ***v13)(uint32_t, int); // ecx
  int v14; // eax
  void (/*thiscall*/ ***v15)(uint32_t, int); // ecx
  int result; // eax
  char *v17; // [esp+10h] [ebp-14h]
  char *v18; // [esp+14h] [ebp-10h]

  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    v17 = sub_4BA9E0(v2, "Monster/Golem/BR/STHead.equ", 0);
  else
    v17 = nullptr;
  v4 = (char *)operator new(0x544u);
  if ( v4 != nullptr )
    v18 = sub_4BA9E0(v4, "Monster/Golem/BR/STLeftArm.equ", 0);
  else
    v18 = nullptr;
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Golem/BR/STRightArm.equ", 0);
  else
    v6 = nullptr;
  v7 = (char *)operator new(0x544u);
  if ( v7 != nullptr )
    v3 = sub_4BA9E0(v7, "Monster/Golem/BR/STLeg.equ", 0);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 4))(v9, 1);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  v11 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v17);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 4))(v11, 1);
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BRGolemBullet.ptl");
  v13 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2166);
  *(this + 2161) = v12;
  if ( v13 != nullptr )
  {
    (**v13)(v13, 1);
    *(this + 2166) = 0;
  }
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v14 = sub_4C3640(this + 91, "Particle/STGolemFire.ptl", this);
    else
      v14 = sub_4C3640(*(this + 91), "Particle/STGolemFire.ptl", this);
  }
  else
  {
    v14 = 0;
  }
  v15 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);
  *(this + 2166) = v14;
  if ( v15 != nullptr )
  {
    (**v15)(v15, 1);
    *(this + 2167) = 0;
  }
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/STGolemHikari.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/STGolemHikari.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 2167) = result;
  return result;
}



// GD/PT 魔像装载：Monster/Golem/GD/{PTHead,PTLeftArm,PTRightArm,PTLeg,PTHorn}.equ 五部件（71L）
// ------------------------------------------------------------
// 0x5A80A0 sub_5A80A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A80A0(void *this)
{
  char *v2; // eax
  char *v3; // edi
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  char *Block; // [esp+10h] [ebp-1Ch]
  char *v15; // [esp+14h] [ebp-18h]
  char *v16; // [esp+18h] [ebp-14h]
  char *v17; // [esp+1Ch] [ebp-10h]

  v2 = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( v2 != nullptr )
    Block = sub_4BA9E0(v2, "Monster/Golem/GD/PTHead.equ", 0);
  else
    Block = nullptr;
  v4 = (char *)operator new(0x544u);
  if ( v4 != nullptr )
    v15 = sub_4BA9E0(v4, "Monster/Golem/GD/PTLeftArm.equ", 0);
  else
    v15 = nullptr;
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v17 = sub_4BA9E0(v5, "Monster/Golem/GD/PTRightArm.equ", 0);
  else
    v17 = nullptr;
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v16 = sub_4BA9E0(v6, "Monster/Golem/GD/PTLeg.equ", 0);
  else
    v16 = nullptr;
  v7 = (char *)operator new(0x544u);
  if ( v7 != nullptr )
    v3 = sub_4BA9E0(v7, "Monster/Golem/GD/PTHorn.equ", 0);
  v8 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v17);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);
  if ( v9 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 4))(v9, 1);
  v10 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);
  if ( v10 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 4))(v10, 1);
  v11 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 4))(v11, 1);
  v12 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( v12 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v12 + 4))(v12, 1);
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 688))(this);
  sub_4EB2C0(1.5);
  sub_4EB6A0(1.5);
  sub_4EB6A0(1.5);
  sub_4EB6A0(1.5);
  sub_4EB6A0(1.5);
  return sub_4EB6A0(1.5);
}



// ============================================================
// 【分区 9】人偶师 DollMaster（0x5A82B0-0x5AC1F0）
// 证据：DOLL_SUMMON/COMMAND/FLOAT_LOOP/CAST/DMG/DIE、Monster/DollMaster/DollMaster.equ、
//       R_DOLL_AMB、Particle/StoneBubble.ptl 石泡、JEWEL_HIT/SWING_SHORT/STONE_DMG、
//       STONE_SET、B_MASTERDOGRY_01 登场曲、+6556 态 14 门（0x5A9100）

// 子类扩展字段复位（this+8600..8668, 21L）
// ------------------------------------------------------------
// 0x5A82B0 sub_5A82B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A82B0(int this)
{
  *(uint8_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8636) = -1;
  *(uint32_t *)(this + 8640) = 0;
  *(uint8_t *)(this + 8656) = 0;
  *(uint32_t *)(this + 8668) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8300 sub_5A8300
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8300(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2163);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 2163) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8320 sub_5A8320
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8320(uint32_t *this, uint32_t *a2)
{
  int result; // eax

  result = sub_4D9170(a2);
  if ( a2 == (uint32_t *)*(this + 2156) )
    *(this + 2156) = 0;
  if ( a2 == this )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 19804);
  return result;
}



// 【vmt200 命中处理器覆写】人偶系小型覆写（17L；虚表 0x6DBE6C/0x6DC394/0x6DC8BC/0x6DCDE4/0x6DD30C/0x6DD834
//   六张 +512 槽共享）
// ------------------------------------------------------------
// 0x5A8360 sub_5A8360
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8360(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // eax

  v5 = sub_4DA3B0(a2, a3, a4);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )
  {
    v6 = *(this + 2156);
    if ( v6 != 0
      && *(uint32_t *)(v6 + 7148) != 9
      && *(this + 1814) != 0
      && sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2151) + *(this + 2157)) )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1056))(this);
    }
  }
  if ( *(this + 1908) == 0 && *(this + 1909) != 0 && rand() % 100 < 50 )
    sub_4DC730(this);
  return v5;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8400 sub_5A8400
// ------------------------------------------------------------
void /*thiscall*/ sub_5A8400(void *this, int a2)
{
  if ( a2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2) != 0 )
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1308))(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8430 sub_5A8430
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8430(uint32_t *this, int a2, int a3)
{
  int v4; // edi
  uint32_t *v5; // ebx
  int v6; // eax
  int v7; // eax

  v4 = *this;
  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(v4 + 152))(
         this,
         2,
         0,
         0,
         0xFFFF,
         0,
         0,
         0,
         0);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int))(*this + 376))(this, *v5, a2, a3, 0, v6);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v4 + 592))(this, *(this + 2152), v7);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8490 sub_5A8490
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8490(uint32_t *this, int a2)
{
  if ( *(this + 2156) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, a2, 0);
  else
    return sub_4D8FE0(this) + 100;
}



// AI 相位辅助（48L）
// ------------------------------------------------------------
// 0x5A84C0 sub_5A84C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A84C0(uint32_t **this)
{
  int result; // eax
  int v3; // edi
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  int v14; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 304))(*(this + 2156));
  if ( result != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
    v3 = *(uint32_t *)dword_8F8520;
    v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 48))(*(this + 2156));
    (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, v4);
    v5 = *(uint32_t *)dword_8F8520;
    v6 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 52))(*(this + 2156));
    (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 304))(*(this + 2156));
    v8 = *(uint32_t *)dword_8F8520;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 52))(v7);
    (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 11);
    v10 = *(uint32_t *)dword_8F8520;
    v11 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1814) + 48))(*(this + 1814));
    (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, v11);
    v12 = (int)*(this + 1814);
    v13 = *(uint32_t *)dword_8F8520;
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 52))(v12);
    (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
    return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
  }
  return result;
}



// 技能播报：STONE_SET（石块放置, 37L）
// ------------------------------------------------------------
// 0x5A85B0 sub_5A85B0
// ------------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int /*usercall*/ sub_5A85B0@<eax>(int *a1@<ecx>, int a2@<edi>)
{
  int v3; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  int v8; // edx
  int v10; // [esp+4h] [ebp-8h] BYREF
  int v11; // [esp+8h] [ebp-4h] BYREF
  int savedregs; // [esp+Ch] [ebp+0h]

  if ( a1[1813] != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[1813] + 120))(a1[1813], a2);
    v4 = rand();
    v5 = a1[1813];
    v11 = v3 + v4 % 180 - 90;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 124))(v5);
    v7 = rand();
    savedregs = 10;
    v11 = 0;
    v10 = 300;
    v8 = *a1;
    v10 = v6 + v7 % 180 - 90;
    (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, int))(v8 + 140))(a1, &v11, &v10, 0, v10);
    sub_4E4A50(a1, 30069, a1[2161], v11, v10, 0, 4, 0, 0, 0);
  }
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(a1, "STONE_SET", -1, 0, 0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8680 sub_5A8680
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8680(uint32_t *this)
{
  uint64_t v2; // rax
  float v4; // [esp+4h] [ebp-8h]

  LODWORD(v2) = *(this + 1813);
  if ( (uint32_t)v2 != 0 )
  {
    v4 = (float)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, v2, 0);
    v2 = (uint64_t)(v4 / (double)sub_4D8FE0(this) * 100.0);
    if ( (int)v2 > 10 )
      *(this + 2167) = ((int)v2 > 50) + 1;
    else
      *(this + 2167) = 0;
  }
  else
  {
    *(this + 2167) = 2;
  }
  return v2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8700 sub_5A8700
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8700(int this, int a2, int a3)
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
  *(uint32_t *)(this + 7580) = 2;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8790 sub_5A8790
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8790(int this, int a2, int a3)
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
  *(uint32_t *)(this + 7576) = 2;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8820 sub_5A8820
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8820(int *this)
{
  int result; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax

  result = *(this + 1813);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      v3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
      v4 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
      v5 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      return sub_4E4A50(this, 30025, 1, v3, v4, 0, v5, 0, 0, 0);
    }
  }
  return result;
}



// 召唤 AI：DOLL_SUMMON 播报（人偶召唤, 33L）
// ------------------------------------------------------------
// 0x5A8880 sub_5A8880
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8880(uint32_t *this)
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  int result; // eax
  int v6; // [esp+8h] [ebp-8h] BYREF
  int v7; // [esp+Ch] [ebp-4h] BYREF

  v2 = 75;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0 )
    v2 = -75;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v2;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  result = sub_499560(this, &v6, &v7, v3, v4, 3);
  if ( (uint8_t)result != 0 )
  {
    sub_5A8430(this, v6, v7);
    return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "DOLL_SUMMON",
             -1,
             0,
             0);
  }
  return result;
}



// 指挥 AI：DOLL_COMMAND 播报（sub_699000 时钟门, this+8628 相位）
// ------------------------------------------------------------
// 0x5A8900 sub_5A8900
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8900(int this)
{
  int v2; // eax
  uint32_t *v3; // edx

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
    sub_5A84C0((uint32_t **)this);
  sub_4D82D0(0, 0);
  v2 = sub_699000(this + 36);
  v3 = *(uint32_t **)this;
  *(uint32_t *)(this + 8628) = v2;
  *(uint32_t *)(this + 7256) = 0;
  return ((int (/*thiscall*/ *)(int, const char *, int, uint32_t, uint32_t))v3[53])(this, "DOLL_COMMAND", -1, 0, 0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8950 sub_5A8950
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A8950(uint32_t *this, char a2, int a3, int a4, int a5, char a6)
{
  sub_4B1030();
  *this = &CNChangeDamageBonusRate::`vftable';
  sub_64C9F0(this);
  sub_64CA10(a2, a3, a4, a5, a6);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A89C0 sub_5A89C0
// ------------------------------------------------------------
void */*thiscall*/ sub_5A89C0(void *Block, char a2)
{
  sub_5A89F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A89F0 sub_5A89F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A89F0(uint32_t *this)
{
  int result; // eax

  *this = &CNChangeDamageBonusRate::`vftable';
  sub_64CA40();
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// RTTI cast 大型 AI（101L）
// ------------------------------------------------------------
// 0x5A8A50 sub_5A8A50
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8A50(void *this)
{
  int result; // eax
  int v3; // ebx
  int v4; // eax
  int v5; // esi
  int *v6; // eax
  int v7; // edx
  int v8; // ebx
  int v9; // eax
  int v10; // esi
  int *v11; // eax
  int v12; // edx
  float v13; // [esp+Ch] [ebp-48h]
  void *Block; // [esp+28h] [ebp-2Ch] BYREF
  void *v15; // [esp+2Ch] [ebp-28h] BYREF
  uint16_t v16; // [esp+32h] [ebp-22h] BYREF
  uint16_t v17; // [esp+34h] [ebp-20h] BYREF
  uint16_t v18; // [esp+38h] [ebp-1Ch] BYREF
  int v19; // [esp+3Ch] [ebp-18h] BYREF
  uint16_t v20; // [esp+40h] [ebp-14h] BYREF
  uint16_t v21; // [esp+44h] [ebp-10h] BYREF
  int v22; // [esp+50h] [ebp-4h]

  result = sub_4DC630();
  v3 = result;
  v19 = result;
  if ( result == -1 )
    return result;
  if ( result != 3 )
  {
    if ( result == 2 )
    {
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v21);
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v16);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &Block);
      v8 = 0;
      if ( v21 != 0 )
      {
        do
        {
          (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v17);
          (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v18);
          v9 = sub_45EBE0(v17, v18);
          v10 = __RTDynamicCast(v9, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
          if ( v10 != 0 )
          {
            v15 = operator new(0x64u);
            v22 = 1;
            if ( v15 != nullptr )
              v11 = (int *)sub_5A8950(1, 3, v16, Block, 1);
            else
              v11 = nullptr;
            v12 = *v11;
            v22 = -1;
            (*(void (/*thiscall*/ **)(int *, int, void *, int, uint32_t, uint32_t, int))(v12 + 56))(
              v11,
              v10,
              this,
              1,
              0,
              0,
              -1);
          }
          ++v8;
        }
        while ( v8 < v21 );
      }
      return v19;
    }
    return v3;
  }
  (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, (char *)&v19 + 2);
  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v20);
  (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v15);
  v4 = sub_45EBE0(HIWORD(v19), v20);
  v5 = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  if ( v5 == 0 )
    return v3;
  Block = operator new(0x80u);
  v22 = 0;
  if ( Block != nullptr )
  {
    v13 = (float)(unsigned int)v15;
    v6 = (int *)sub_4D6810(LODWORD(v13), 500, 1, 1);
  }
  else
  {
    v6 = nullptr;
  }
  v7 = *v6;
  v22 = -1;
  (*(void (/*thiscall*/ **)(int *, int, void *, uint32_t, uint32_t, uint32_t, int))(v7 + 56))(v6, v5, this, 0, 0, 0, -1);
  return 3;
}



// RTTI cast + 时钟门 AI（80L）
// ------------------------------------------------------------
// 0x5A8C70 sub_5A8C70
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8C70(uint32_t *this)
{
  int v2; // esi
  int result; // eax
  unsigned int i; // ebx
  int v5; // ecx
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // eax
  int v13; // esi
  int v14; // ebx
  unsigned int v15; // [esp+8h] [ebp-4h]

  v2 = (int)(this + 9);
  result = sub_699000((int)(this + 9));
  if ( *(this + 2165) + 500 > (unsigned int)result )
    return result;
  *(this + 2165) = sub_699000(v2);
  for ( i = 0; ; ++i )
  {
    v5 = *(this + 29);
    v6 = *(uint32_t *)(v5 + 8);
    v15 = i;
    if ( v6 != 0 )
      result = (*(uint32_t *)(v5 + 12) - v6) >> 2;
    else
      result = 0;
    if ( (int)i >= result )
    {
      *(this + 2156) = 0;
      return result;
    }
    v7 = *(uint32_t *)(v5 + 8);
    if ( v7 != 0 && i < (*(uint32_t *)(v5 + 12) - v7) >> 2 )
      v8 = *(uint32_t *)(v7 + 4 * i);
    else
      v8 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 40))(v8, 529) != 0 )
    {
      v9 = *(this + 29);
      v10 = *(uint32_t *)(v9 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(v9 + 12) - v10) >> 2 )
        v11 = *(uint32_t *)(v10 + 4 * i);
      else
        v11 = 0;
      v12 = __RTDynamicCast(v11, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      v13 = v12;
      if ( v12 != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 340))(v12) >= 31
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 340))(v13) <= 35
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 340))(v13) == 3001) )
      {
        break;
      }
    }
LABEL_23:
    ;
  }
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 376))(v13);
  if ( v14 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, v13)) == 0 )
  {
    i = v15;
    goto LABEL_23;
  }
  if ( *(this + 2156) != v13 )
    result = sub_4D83E0(0, 0);
  *(this + 2156) = v13;
  return result;
}



// 硬直字段（this+204, 研究 15）
// ------------------------------------------------------------
// 0x5A8DD0 sub_5A8DD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8DD0(uint32_t *this)
{
  int v2; // eax

  v2 = *(this + 2159);
  if ( v2 == 4 || v2 == 5 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      1,
      *(uint32_t *)(*(this + 1554) + 12),
      0,
      0,
      0,
      0);
    return sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      1,
      *(uint32_t *)(*(this + 1554) + 4),
      0,
      0,
      0,
      0);
    sub_4926A0(*(uint32_t *)(*(this + 1554) + 4));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      3,
      *(uint32_t *)(*(this + 1554) + 8),
      0,
      0,
      0,
      0);
    return sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));
  }
}



// 硬直字段（this+208）
// ------------------------------------------------------------
// 0x5A8E80 sub_5A8E80
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8E80(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 8));
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));
}



// RTTI cast 目标解算（65L）
// ------------------------------------------------------------
// 0x5A8ED0 sub_5A8ED0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8ED0(uint32_t *this)
{
  uint32_t *v1; // ebx
  unsigned int i; // edi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int v14; // [esp+Ch] [ebp-8h]

  v1 = this;
  for ( i = 0; ; ++i )
  {
    v3 = v1[29];
    v4 = *(uint32_t *)(v3 + 8);
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
    {
      v8 = v1[29];
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      v12 = v11;
      if ( v11 != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 340))(v11) >= 31
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 340))(v12) <= 35
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 340))(v12) == 3001) )
      {
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 376))(v12);
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*v1 + 376))(v1);
        v1 = this;
        if ( v14 == v13 && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, v12) != 0 )
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 736))(v12);
          if ( result > 0 )
            break;
        }
      }
    }
  }
  return result;
}



// AI 相位辅助（48L）
// ------------------------------------------------------------
// 0x5A8FF0 sub_5A8FF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8FF0(void *this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // eax
  int v7; // edi
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  unsigned int i; // edi
  int v14; // edx

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
  v5 = *(uint32_t *)dword_8F8520;
  v6 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
  v7 = *(uint32_t *)dword_8F8520;
  v8 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
  v9 = *(uint32_t *)dword_8F8520;
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 2);
  v11 = *(uint32_t *)(a2 + 4);
  if ( v11 != 0 )
    v12 = (*(uint32_t *)(a2 + 8) - v11) >> 3;
  else
    v12 = 0;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v12);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a3);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, a4);
  for ( i = 0; ; ++i )
  {
    v14 = *(uint32_t *)(a2 + 4);
    if ( v14 == 0 || i >= (*(uint32_t *)(a2 + 8) - v14) >> 3 )
      break;
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 36))(*(uint16_t *)(8 * i + v14));
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 36))(*(uint16_t *)(8 * i + *(uint32_t *)(a2 + 4) + 4));
  }
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// 人偶浮游 AI：DOLL_FLOAT_LOOP + DOLL_CAST 播报（75L；
//   this+6556==14 大状态门 + 8620..8664 相位字段）
// ------------------------------------------------------------
// 0x5A9100 sub_5A9100
// ------------------------------------------------------------
int /*thiscall*/ sub_5A9100(int this, int ArgList, float a3, int a4, int a5)
{
  int result; // eax

  if ( *(uint32_t *)(this + 6556) == 14 && ArgList != 14 )
  {
    sub_5A8E80((uint32_t *)this);
    if ( *(uint32_t *)(this + 8636) == 0 )
      sub_4D93D0(this);
  }
  sub_4E33D0(ArgList, a3, a4, a5);
  result = *(uint32_t *)(this + 6556);
  switch ( result )
  {
    case 0:
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 19804);
      result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                 this,
                 "DOLL_FLOAT_LOOP",
                 19804,
                 0,
                 0);
      break;
    case 4:
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 19804);
      break;
    case 8:
      *(uint8_t *)(this + 8664) = 0;
      break;
    case 14:
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 6216));
      sub_4926A0(*(uint32_t *)(this + 120));
      *(uint32_t *)(this + 8636) = **(uint32_t **)(LODWORD(a3) + 4);
      *(uint32_t *)(this + 8640) = 0;
      sub_5A8DD0((uint32_t *)this);
      if ( *(uint32_t *)(this + 8636) == 0 )
      {
        sub_4D9360(this);
        *(uint8_t *)(this + 8620) = 1;
      }
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "DOLL_CAST",
        -1,
        0,
        0);
      result = (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 1, 0, 1000, 1000);
      break;
    default:
      return result;
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_MASTERDOGRY_01"（人偶师曲目槽, 82L）
// ------------------------------------------------------------
// 0x5A9290 sub_5A9290
// ------------------------------------------------------------
int /*thiscall*/ sub_5A9290(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // [esp+4h] [ebp-8h] BYREF
  int v11; // [esp+8h] [ebp-4h] BYREF

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        sub_406D60("B_MASTERDOGRY_01");
      break;
    case 4:
    case 5:
      if ( *(this + 1813) == 0 )
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    case 13:
    case 14:
    case 15:
      if ( *(this + 1813) != 0 )
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      break;
  }
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    sub_5A8680(this);
    if ( *(this + 1813) != 0 )
      (*(void (/*thiscall*/ **)(int *))(*this + 1312))(this);
    result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( result == 0 )
    {
      v3 = *(this + 2156);
      if ( v3 != 0 )
      {
        v4 = sub_5A8490(this, v3);
        if ( v4 > sub_4D8FE0(this) )
          *(this + 2156) = 0;
      }
      else
      {
        sub_5A8C70(this);
      }
      result = *(this + 2156);
      if ( result != 0 )
      {
        v5 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(*this + 8))(this, result, 0);
        result = sub_4D8FE0(this) - 30;
        if ( v5 > result )
        {
          v6 = (*(int (/*thiscall*/ **)(int *))(*this + 184))(this);
          v7 = *this;
          v10 = v6;
          v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 188))(this);
          v9 = *(this + 2156);
          v11 = v8;
          sub_4DC130(v9, &v10, &v11);
          return (*(int (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, v10, v11);
        }
      }
    }
  }
  return result;
}



// RTTI cast + 时钟门 AI（84L）
// ------------------------------------------------------------
// 0x5A9410 sub_5A9410
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9410(int *this)
{
  int *v1; // ebx
  unsigned int i; // edi
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // esi
  int v13; // eax
  int v14; // edx
  int v15; // eax
  uint8_t v16[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h]
  int v18; // [esp+14h] [ebp-24h]
  int v19; // [esp+18h] [ebp-20h]
  uint32_t v20[2]; // [esp+1Ch] [ebp-1Ch] BYREF
  int v21; // [esp+24h] [ebp-14h]
  int *v22; // [esp+28h] [ebp-10h]
  int v23; // [esp+34h] [ebp-4h]

  v1 = this;
  v22 = this;
  Block = nullptr;
  v18 = 0;
  v19 = 0;
  v23 = 0;
  for ( i = 0; ; ++i )
  {
    v3 = v1[29];
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
    {
      v8 = v1[29];
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      v12 = v11;
      if ( v11 != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 340))(v11) >= 31
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 340))(v12) <= 35
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 340))(v12) == 3001) )
      {
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 376))(v12);
        v14 = *v1;
        v21 = v13;
        v15 = (*(int (/*thiscall*/ **)(int *))(v14 + 376))(v1);
        v1 = v22;
        if ( v21 == v15 && (*(uint8_t (/*thiscall*/ **)(int *, int))(*v22 + 1244))(v22, v12) != 0 )
        {
          v20[0] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 48))(v12);
          v20[1] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 52))(v12);
          sub_474950(v20);
        }
      }
    }
  }
  sub_5A8FF0(v1, (int)v16, 50, 5000);
  v1[2158] = sub_699000((int)(v1 + 9));
  if ( Block != nullptr )
    j__free(Block);
}



// 人偶字段群（this+8600/8620/8648/8668）
// ------------------------------------------------------------
// 0x5A95A0 sub_5A95A0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A95A0(void *this, int a2)
{
  uint8_t v3[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  int v6; // [esp+14h] [ebp-10h]
  int v7; // [esp+20h] [ebp-4h]

  Block = nullptr;
  v5 = 0;
  v6 = 0;
  v7 = 0;
  sub_430C80(nullptr, 1, (int)&a2);
  (*(void (/*thiscall*/ **)(void *, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, v3, 0, 0);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x5A9620 sub_5A9620
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9620(int this)
{
  unsigned int v2; // eax
  int v3; // ecx

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(v2) > *(uint32_t *)(this + 8600)) )
    {
      if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 2 )
      {
        sub_5A95A0((void *)this, 1);
      }
      else if ( *(uint32_t *)(this + 8668) == 1 )
      {
        v3 = *(uint32_t *)(this + 7252);
        if ( v3 != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 776))(v3, 7) == 0
          && rand() % 100 < 10 )
        {
          sub_5A95A0((void *)this, 4);
          *(uint32_t *)(this + 8648) = (uint64_t)((double (/*thiscall*/ *)(int, uint32_t, uint32_t))*(uint32_t *)(*(uint32_t *)this + 164))(
                                                         this,
                                                         *(uint32_t *)(this + 7252),
                                                         0);
        }
      }
    }
    else
    {
      sub_5A95A0((void *)this, 0);
    }
  }
}



// 人偶字段群（sub_699000 时钟门）
// ------------------------------------------------------------
// 0x5A96F0 sub_5A96F0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A96F0(int this)
{
  unsigned int v2; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(v2) > *(uint32_t *)(this + 8600)) )
    {
      if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 2 )
      {
        sub_5A95A0((void *)this, 1);
      }
      else if ( *(uint32_t *)(this + 8624) != 0
             && rand() % 100 < 15
             && *(uint32_t *)(this + 8632) + 5000 < (unsigned int)sub_699000(this + 36) )
      {
        sub_5A95A0((void *)this, 2);
      }
    }
    else
    {
      sub_5A95A0((void *)this, 0);
    }
  }
}



// 人偶字段群
// ------------------------------------------------------------
// 0x5A97A0 sub_5A97A0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A97A0(int this)
{
  unsigned int v2; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(v2) > *(uint32_t *)(this + 8600)) )
    {
      if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 2 )
      {
        sub_5A95A0((void *)this, 1);
      }
      else if ( *(uint32_t *)(this + 8668) == 1 && *(uint32_t *)(this + 7252) != 0 && rand() % 100 < 10 )
      {
        sub_5A95A0((void *)this, 5);
        *(uint32_t *)(this + 8648) = (uint64_t)((double (/*thiscall*/ *)(int, uint32_t, uint32_t))*(uint32_t *)(*(uint32_t *)this + 164))(
                                                       this,
                                                       *(uint32_t *)(this + 7252),
                                                       0);
      }
    }
    else
    {
      sub_5A95A0((void *)this, 0);
    }
  }
}



// 人偶字段群
// ------------------------------------------------------------
// 0x5A9860 sub_5A9860
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9860(int this)
{
  unsigned int v2; // eax
  int v3; // ecx

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(v2) > *(uint32_t *)(this + 8600)) )
    {
      if ( rand() % 100 < 10 && *(uint32_t *)(this + 8624) != 0 )
      {
        sub_5A95A0((void *)this, 3);
      }
      else if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 15 )
      {
        sub_5A95A0((void *)this, 1);
      }
      else if ( *(uint32_t *)(this + 8668) == 1 )
      {
        v3 = *(uint32_t *)(this + 7252);
        if ( v3 != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 776))(v3, 7) == 0
          && rand() % 100 < 10 )
        {
          sub_5A95A0((void *)this, 4);
          *(uint32_t *)(this + 8648) = (uint64_t)((double (/*thiscall*/ *)(int, uint32_t, uint32_t))*(uint32_t *)(*(uint32_t *)this + 164))(
                                                         this,
                                                         *(uint32_t *)(this + 7252),
                                                         0);
        }
      }
    }
    else
    {
      sub_5A95A0((void *)this, 0);
    }
  }
}



// 人偶字段群
// ------------------------------------------------------------
// 0x5A9950 sub_5A9950
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9950(int this)
{
  unsigned int v2; // eax
  int v3; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(v2) > *(uint32_t *)(this + 8600)) )
    {
      v3 = *(uint32_t *)(this + 8668);
      if ( (v3 == 2 || v3 == 1) && rand() % 100 < 20 )
        sub_5A95A0((void *)this, 1);
    }
    else
    {
      sub_5A95A0((void *)this, 0);
    }
  }
}



// 石泡技能：引用 PassiveObject/Common/Particle/StoneBubble.ptl（54L）
// ------------------------------------------------------------
// 0x5A99C0 sub_5A99C0
// ------------------------------------------------------------
int /*usercall*/ sub_5A99C0@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int result; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  int v7; // eax
  int v8; // edi
  uint64_t v9; // rax
  int v10; // edi
  int v11; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    if ( a1[2163] == 0 )
    {
      v5 = operator new(0x12Cu);
      if ( v5 != nullptr )
        v6 = sub_428F30(v5, (int)"PassiveObject/Common/Particle/StoneBubble.ptl", 0);
      else
        v6 = nullptr;
      a1[2163] = v6;
    }
    v7 = a1[1813];
    if ( v7 != 0 )
    {
      v8 = a1[2163];
      v9 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t, int))*(uint32_t *)(*a1 + 164))(a1, v7, 0, a2);
      *(uint32_t *)((*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)v8 + 28))(v8, HIDWORD(v9)) + 72) = v9;
    }
    else
    {
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)a1[2163] + 28))(a1[2163], a3) + 72) = a1[2162];
    }
    v10 = *a1;
    v11 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)a1[2163] + 28))(
            a1[2163],
            0,
            15,
            0,
            55,
            1,
            0,
            0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v10 + 580))(a1, 48010, 0, v11);
  }
  return result;
}



// 石泡技能 2：PassiveObject/Common/Particle/StoneBubble.ptl（54L）
// ------------------------------------------------------------
// 0x5A9AC0 sub_5A9AC0
// ------------------------------------------------------------
int /*usercall*/ sub_5A9AC0@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int result; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  int v7; // eax
  int v8; // edi
  uint64_t v9; // rax
  int v10; // edi
  int v11; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
  if ( (uint8_t)result != 0 )
  {
    if ( a1[2163] == 0 )
    {
      v5 = operator new(0x12Cu);
      if ( v5 != nullptr )
        v6 = sub_428F30(v5, (int)"PassiveObject/Common/Particle/StoneBubble.ptl", 0);
      else
        v6 = nullptr;
      a1[2163] = v6;
    }
    v7 = a1[1813];
    if ( v7 != 0 )
    {
      v8 = a1[2163];
      v9 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t, int))*(uint32_t *)(*a1 + 164))(a1, v7, 0, a2);
      *(uint32_t *)((*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)v8 + 28))(v8, HIDWORD(v9)) + 72) = v9;
    }
    else
    {
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)a1[2163] + 28))(a1[2163], a3) + 72) = a1[2162];
    }
    v10 = *a1;
    v11 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)a1[2163] + 28))(
            a1[2163],
            0,
            15,
            0,
            55,
            1,
            0,
            0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v10 + 580))(a1, 48014, 0, v11);
  }
  return result;
}



// AI 相位辅助（52L）
// ------------------------------------------------------------
// 0x5A9BC0 sub_5A9BC0
// ------------------------------------------------------------
int /*usercall*/ sub_5A9BC0@<eax>(int *a1@<ecx>, int a2@<ebx>)
{
  int result; // eax
  uint32_t *v4; // edi

  result = (*(int (/*thiscall*/ **)(int *))(*a1 + 840))(a1);
  if ( result == 14 )
  {
    v4 = (uint32_t *)a1[1554];
    result = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
    if ( result == *v4 )
    {
      if ( a1[2160] == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1) + 148) == 6 )
      {
        switch ( a1[2159] )
        {
          case 0:
            sub_5A8880(a1);
            break;
          case 1:
            (*(void (/*thiscall*/ **)(int *))(*a1 + 1308))(a1);
            break;
          case 2:
            sub_5A9410(a1);
            break;
          case 3:
            sub_5A8ED0(a1);
            break;
          case 4:
            sub_5A99C0(a1, a2, (int)v4);
            break;
          case 5:
            sub_5A9AC0(a1, a2, (int)v4);
            break;
          default:
            break;
        }
        a1[2160] = 1;
      }
      result = (*(int (/*thiscall*/ **)(int *))(*a1 + 200))(a1);
      if ( *(uint8_t *)(result + 170) != 0 )
        return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 0, 0, 0, 0);
    }
  }
  return result;
}



// 技能播报：JEWEL_HIT（宝石命中）+ SWING_SHORT + STONE_DMG（65L）
// ------------------------------------------------------------
// 0x5A9CA0 sub_5A9CA0
// ------------------------------------------------------------
char /*usercall*/ sub_5A9CA0@<al>(int a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax

  sub_4E1780((uint32_t *)a1);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1) != 0 )
    sub_5A9BC0((int *)a1, a2);
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 840))(a1);
  if ( v3 == 8 )
  {
    if ( sub_41A5E0(a1 + 7028) != 0 )
    {
      v3 = sub_41A5E0(a1 + 7028);
      if ( v3 == 1 )
      {
        v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1);
        if ( *(uint32_t *)(v3 + 148) == 3 )
        {
          LOBYTE(v3) = *(uint8_t *)(a1 + 8664);
          if ( (uint8_t)v3 == 0 )
          {
            LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
                           a1,
                           "JEWEL_HIT",
                           -1,
                           0,
                           0);
            *(uint8_t *)(a1 + 8664) = 1;
          }
        }
      }
    }
    else
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1) + 148) == 1 && *(uint8_t *)(a1 + 8664) == 0 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
          a1,
          "SWING_SHORT",
          -1,
          0,
          0);
        *(uint8_t *)(a1 + 8664) = 1;
      }
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1);
      if ( *(uint32_t *)(v3 + 148) == 6 && *(uint8_t *)(a1 + 8664) == 1 )
      {
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
                       a1,
                       "STONE_DMG",
                       -1,
                       0,
                       0);
        *(uint8_t *)(a1 + 8664) = 0;
      }
    }
  }
  return v3;
}



// 人偶师装载：DOLL_DMG/DOLL_DIE 播报 + Monster/DollMaster/DollMaster.equ +
//   R_DOLL_AMB 语音（109L）
// ------------------------------------------------------------
// 0x5A9DA0 sub_5A9DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A9DA0(uint32_t *this)
{
  void *v2; // eax
  char *v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edx
  uint64_t v9; // rax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  void *v16; // eax
  int v17; // edi
  int v18; // edi
  int v19; // eax
  char v21[4]; // [esp+14h] [ebp-44h] BYREF
  void *v22; // [esp+18h] [ebp-40h]
  int v23; // [esp+1Ch] [ebp-3Ch]
  int v24; // [esp+20h] [ebp-38h]
  int v25; // [esp+24h] [ebp-34h]
  float v26; // [esp+28h] [ebp-30h]
  int v27; // [esp+2Ch] [ebp-2Ch]
  int v28; // [esp+30h] [ebp-28h]
  size_t v29; // [esp+34h] [ebp-24h]
  void *Block; // [esp+44h] [ebp-14h]
  int v31; // [esp+48h] [ebp-10h]
  int v32; // [esp+54h] [ebp-4h]

  v29 = 8;
  v28 = (int)"DOLL_DMG";
  *(this + 1698) = 1;
  *(this + 1699) = 2;
  *(this + 1700) = 3;
  *(this + 1701) = 2;
  *(this + 1702) = 4;
  sub_4015C0((void *)v28, v29);
  sub_4015C0("DOLL_DIE", 8u);
  v2 = operator new(0x544u);
  Block = v2;
  v32 = 0;
  if ( v2 != nullptr )
    v3 = sub_4BA9E0((char *)v2, "Monster/DollMaster/DollMaster.equ", 0);
  else
    v3 = nullptr;
  v4 = *this;
  v32 = -1;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(v4 + 784))(this, v3);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
  v6 = *this;
  v29 = 0;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 570;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, size_t))(v6 + 384))(this, v29);
  v8 = *this;
  v31 = v7;
  *(float *)&Block = (double)v7 * 0.01;
  v31 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 740))(this);
  v9 = (uint64_t)((double)v31 * *(float *)&Block);
  *(this + 2150) = v9;
  v10 = (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, int))(*this + 384))(this, HIDWORD(v9), 1);
  v11 = *this;
  v29 = 2;
  *(this + 2151) = v10;
  *(this + 2152) = (*(int (/*thiscall*/ **)(uint32_t *, size_t))(v11 + 384))(this, v29);
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v13 = *this;
  v29 = 4;
  *(this + 2153) = v12;
  *(this + 2154) = (*(int (/*thiscall*/ **)(uint32_t *, size_t))(v13 + 384))(this, v29);
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);
  v15 = *this;
  v31 = v14;
  v16 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, int))(v15 + 384))(this, 6);
  v17 = *(this + 1821);
  Block = v16;
  v18 = v17 - *(this + 1820);
  v19 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3) - *(this + 1820);
  *(float *)&v27 = (float)(int)Block;
  v26 = (float)v31;
  *(this + 2161) = (uint64_t)sub_4049C0(v26, *(float *)&v27, v19, v18);
  *((uint8_t *)this + 8620) = 0;
  *(this + 2157) = sub_699000((int)(this + 9));
  *(this + 2158) = sub_699000((int)(this + 9));
  *(this + 2163) = 0;
  v29 = 10000;
  v28 = 5000;
  *(float *)&Block = COERCE_FLOAT(v21);
  *(this + 2165) = sub_699000((int)(this + 9));
  *(this + 2120) = 20;
  *(this + 2121) = 2000;
  v27 = 15;
  v26 = 0.0;
  LOBYTE(v22) = 0;
  sub_4015C0("R_DOLL_AMB", 0xAu);
  return sub_4DE5E0(v21[0], v22, v23, v24, v25, SLODWORD(v26), v27, v28, v29);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A9FF0 sub_5A9FF0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9FF0(uint32_t *this)
{
  *(this + 2150) = 0;
  *(this + 2174) = 1000;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AA010 sub_5AA010
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA010(uint32_t *this)
{
  int v2; // edi
  uint32_t *v3; // edi

  v2 = *(this + 81) - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( v2 != 0 )
  {
    sub_495890(0, v2 <= 0 ? 1000 : -1000);
    sub_4A0550(v2);
    return sub_4A0600(2);
  }
  else
  {
    v3 = (uint32_t *)*(this + 28);
    if ( *v3 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v3 + 308))(*v3) != 0
      && *((float *)v3 + 6) != 0.0 )
    {
      v3[6] = 0;
      *((uint8_t *)v3 + 196) = 1;
    }
    return sub_495890(2, 0);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AA0A0 sub_5AA0A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA0A0(void *this, int a2)
{
  int v3; // edi
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // esi
  int v8; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
  v3 = *(uint32_t *)dword_8F8520;
  v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, v4);
  v5 = *(uint32_t *)dword_8F8520;
  v6 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
  v7 = *(uint32_t *)dword_8F8520;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a2);
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// AI 字段访问（this+8700/8701）
// ------------------------------------------------------------
// 0x5AA130 sub_5AA130
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA130(uint8_t *this, int a2, int a3, int a4)
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) != 14 || *(this + 8700) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 16 && *(this + 8701) == 0 )
      *(this + 8701) = 1;
  }
  else
  {
    *(this + 8700) = 1;
  }
  return sub_4DB480(a2, a3, a4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AA190 sub_5AA190
// ------------------------------------------------------------
char /*thiscall*/ sub_5AA190(uint32_t *this, signed int a2, char a3)
{
  int v4; // eax
  int v5; // edi

  v4 = *(this + 1813);
  if ( v4 == 0 )
    return 0;
  v5 = (*(int (**)(void))(*(uint32_t *)v4 + 120))();
  if ( (int)abs32(v5 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) > a2 )
    return 0;
  if ( a3 != 0 && (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) <= 1 )
  {
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  }
  return 1;
}



// RTTI cast 目标解算（this+8608）
// ------------------------------------------------------------
// 0x5AA200 sub_5AA200
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA200(uint8_t *this, int a2, int a3, int a4)
{
  int v7; // eax
  float v9; // [esp+0h] [ebp-1Ch]
  float v10; // [esp+24h] [ebp+8h]
  int v11; // [esp+2Ch] [ebp+10h]

  if ( (uint8_t)a4 == 0 && *(this + 8608) == 1 )
  {
    v10 = (float)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 736))(this);
    v11 = 15;
    if ( (double)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 740))(this) * 0.5 <= v10 )
      v11 = 5;
    v7 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    if ( v7 != 0 )
    {
      v9 = (float)v11;
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, uint32_t))(*(uint32_t *)v7 + 760))(v7, 1, LODWORD(v9), 3, a2, 0);
    }
  }
  return sub_5AA130(this, a2, a3, a4);
}



// ============================================================
// 【分区 10】飞龙 Flydragon（0x5AC1F0-0x5ACF40）
// 证据：FLYDRAGON_MAD/FIRE/HIT/DMG/DIE/CRY/FLAP 全套播报、FLAMETHROWER_LOOP、
//       Particle/FireBreath.ptl 火息、FDRG_DIE、B_SELLION_01 登场曲

// AI 主状态门（this+200, sub_699000）
// ------------------------------------------------------------
// 0x5AC1F0 sub_5AC1F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5AC1F0(uint32_t *this)
{
  unsigned int result; // eax
  int v2; // edx

  sub_5AB9B0();
  if ( *(this + 2195) == *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) )
  {
    if ( *(this + 2194) == 0 )
      *(this + 2194) = sub_699000((int)(this + 9));
    result = sub_699000((int)(this + 9)) - *(this + 2194);
    if ( result > 0x2710 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result == 1 )
        return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1256))(this);
    }
  }
  else
  {
    v2 = *this;
    *(this + 2194) = 0;
    result = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(v2 + 200))(this) + 148);
    *(this + 2195) = result;
  }
  return result;
}



// 狂暴 AI：FLYDRAGON_MAD 播报（90L；飞龙狂暴化）
// ------------------------------------------------------------
// 0x5AC200 sub_5AC200
// ------------------------------------------------------------
int /*thiscall*/ sub_5AC200(uint32_t *this, int ArgList, float a3, int a4, int a5)
{
  int v7; // edi
  int result; // eax
  int v9; // eax
  int v10; // et2
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // [esp+18h] [ebp+Ch]

  if ( *(this + 1639) == 8
    && (sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 45230);
  }
  if ( ArgList == 8 && *(uint32_t *)(*(uint32_t *)(LODWORD(a3) + 4) + 4) == 1 )
  {
    v7 = *(this + 1813);
    if ( v7 != 0 )
    {
      v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      if ( (signed int)abs32((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 120))(v7) - v21) < *(uint32_t *)(*(this + 1905) + 16) )
        *(uint32_t *)(*(uint32_t *)(LODWORD(a3) + 4) + 4) = 0;
    }
  }
  result = sub_4E33D0(ArgList, a3, a4, a5);
  if ( ArgList == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 || sub_41A5E0((unsigned int)(this + 1757)) == 2 )
    {
      sub_5AB5B0(this);
      *(this + 2152) = sub_699000((int)(this + 1910));
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 2 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
          this,
          "FLYDRAGON_MAD",
          -1,
          0,
          0);
        return sub_4DB130(24, 0);
      }
    }
    else
    {
      result = sub_41A5E0((unsigned int)(this + 1757));
      if ( result == 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
        if ( (uint8_t)result != 0 )
        {
          v9 = rand();
          v10 = v9 % 100;
          result = v9 / 100;
          if ( v10 < 10 )
          {
            v11 = *this;
            v12 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 672))(this, 3, 0);
            v13 = sub_4954C0(v12);
            v14 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 672))(this, 3, 0, -v13);
            v15 = sub_4954C0(v14);
            v16 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 672))(this, 3, v15);
            v17 = sub_4954C0(v16);
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v11 + 876))(this, 0, v17);
            v18 = *this;
            v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 188))(this);
            v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, v19);
            return (*(int (/*thiscall*/ **)(uint32_t *, int))(v18 + 896))(this, v20);
          }
        }
      }
    }
  }
  return result;
}



// 火焰喷射：FLYDRAGON_FIRE + FLAMETHROWER_LOOP 播报（this+8625/8626 相位, 49L）
// ------------------------------------------------------------
// 0x5AC3D0 sub_5AC3D0
// ------------------------------------------------------------
void /*thiscall*/ sub_5AC3D0(uint32_t **this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // edx
  void *v5; // eax
  int v6; // [esp-Ch] [ebp-34h]
  int v7; // [esp-8h] [ebp-30h]
  int v8; // [esp-4h] [ebp-2Ch]
  uint8_t v9[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v11; // [esp+24h] [ebp-4h]

  if ( *(uint8_t *)(**(this + 1554) + 170) != 0 )
  {
    v2 = **(this + 2151);
    v8 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) + 43;
    v7 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);
    v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 1 ? -47 : 47;
    v6 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + v3;
    (*(void (/*thiscall*/ **)(uint32_t))(v2 + 40))(*(this + 2151));
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 2151) + 92))(*(this + 2151), v9);
    v4 = (int)*this;
    v11 = 0;
    v5 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int, uint32_t, uint8_t *))(v4 + 80))(this, 2, 0, v9);
    sub_4600B0(v5, v6, v7, v8);
    if ( Block != nullptr )
      j__free(Block);
  }
  else if ( sub_699000((int)(this + 2153)) > 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 2151) + 12))(*(this + 2151), 0);
    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "FLYDRAGON_FIRE", -1, 0, 0);
    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*this)[53])(
      this,
      "FLAMETHROWER_LOOP",
      45230,
      0,
      0);
    *((uint8_t *)this + 8625) = 0;
    *((uint8_t *)this + 8626) = 0;
  }
}



// 飞龙语音装载：FLYDRAGON_HIT/DMG/DIE + FLYDRAGON_CRY 龙吟（this+8608/8692 相位）
// ------------------------------------------------------------
// 0x5AC500 sub_5AC500
// ------------------------------------------------------------
int /*thiscall*/ sub_5AC500(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  char v6; // [esp-24h] [ebp-34h] BYREF
  void *v7; // [esp-20h] [ebp-30h]
  int v8; // [esp-1Ch] [ebp-2Ch]
  int v9; // [esp-18h] [ebp-28h]
  int v10; // [esp-14h] [ebp-24h]
  int v11; // [esp-10h] [ebp-20h]
  int v12; // [esp-Ch] [ebp-1Ch]
  int v13; // [esp-8h] [ebp-18h]
  size_t v14; // [esp-4h] [ebp-14h]
  char *v15; // [esp+Ch] [ebp-4h]

  v14 = 13;
  v13 = (int)"FLYDRAGON_HIT";
  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0((void *)v13, v14);
  sub_4015C0("FLYDRAGON_DMG", 0xDu);
  sub_4015C0("FLYDRAGON_DIE", 0xDu);
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v3 = *this;
  v14 = 1;
  *(this + 2150) = v2;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, size_t))(v3 + 384))(this, v14);
  v14 = 10000;
  v13 = 5000;
  v15 = &v6;
  *(this + 1933) = v4;
  *((uint8_t *)this + 8608) = 0;
  *(this + 2154) = 2;
  *(this + 2153) = 2;
  *((uint8_t *)this + 8692) = 0;
  v12 = 15;
  v11 = 0;
  LOBYTE(v7) = 0;
  sub_4015C0("FLYDRAGON_CRY", 0xDu);
  return sub_4DE5E0(v6, v7, v8, v9, v10, v11, v12, v13, v14);
}



// 振翅 AI：FLYDRAGON_FLAP 播报（this+200/8600/8604/8608 相位, 57L）
// ------------------------------------------------------------
// 0x5AC5E0 sub_5AC5E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AC5E0(int this)
{
  int result; // eax

  sub_4E1780((uint32_t *)this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
  {
    if ( sub_41A5E0(this + 7028) == 1 )
    {
      sub_5AC3D0((uint32_t **)this);
    }
    else if ( sub_41A5E0(this + 7028) == 2 )
    {
      sub_5AC3D0((uint32_t **)this);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 8604) + 68))(*(uint32_t *)(this + 8604)) != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
      }
      if ( *(uint32_t *)(this + 8608) + 1000 <= (unsigned int)sub_699000(this + 7640) )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
          sub_5AA420(this);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
        *(uint32_t *)(this + 8608) = sub_699000(this + 7640);
      }
    }
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
  if ( result == *(uint32_t *)(this + 6164) )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) != 3
      || *(uint8_t *)(this + 8600) != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
      if ( *(uint32_t *)(result + 148) == 0 )
        *(uint8_t *)(this + 8600) = 0;
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                 this,
                 "FLYDRAGON_FLAP",
                 -1,
                 0,
                 0);
      *(uint8_t *)(this + 8600) = 1;
    }
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_SELLION_01"（飞龙曲目槽, 75L）
// ------------------------------------------------------------
// 0x5AC710 sub_5AC710
// ------------------------------------------------------------
int /*thiscall*/ sub_5AC710(int *this)
{
  int result; // eax
  bool v3; // zf
  int v4; // eax
  int v5; // et2
  int v6; // eax
  int v7; // et2

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        result = sub_406D60("B_SELLION_01");
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_11;
      v6 = rand();
      v7 = v6 % 100;
      result = v6 / 100;
      if ( v7 < 10 )
      {
        result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
        if ( (uint8_t)result != 0 )
          result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      }
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        v4 = rand();
        v5 = v4 % 100;
        result = v4 / 100;
        if ( v5 < 30 )
        {
          result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
          v3 = (uint8_t)result == 0;
          goto LABEL_5;
        }
      }
      else
      {
LABEL_11:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
      result = *(this + 1813);
      if ( result != 0 )
        goto LABEL_16;
      break;
    case 14:
    case 15:
      result = *(this + 1813);
      v3 = result == 0;
LABEL_5:
      if ( !v3 )
LABEL_16:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return result;
  }
  return result;
}



// AI 相位辅助（100L；this+8608）
// ------------------------------------------------------------
// 0x5AC830 sub_5AC830
// ------------------------------------------------------------
char /*thiscall*/ sub_5AC830(uint32_t *this)
{
  uint32_t *v2; // ecx
  int v3; // eax
  unsigned int v4; // ebx
  int *v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edi
  int *v10; // edi
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // edi
  int v15; // edi
  void *v17; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v19; // [esp+14h] [ebp-18h]
  int v20; // [esp+18h] [ebp-14h]
  int v21; // [esp+1Ch] [ebp-10h]
  int v22; // [esp+28h] [ebp-4h]

  if ( *(this + 2153) == 2
    && *((uint8_t *)this + 8608) == 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) == 15 )
  {
    Block = nullptr;
    v19 = 0;
    v20 = 0;
    v22 = 0;
    sub_4E0CD0(17, 0, &v17, 300);
    v2 = Block;
    if ( Block != nullptr )
    {
      v3 = v19;
      if ( (v19 - (int)Block) >> 2 != 0 )
      {
        v4 = 0;
        while ( v2 != nullptr )
        {
          if ( v4 >= (v3 - (int)v2) >> 2 )
            goto LABEL_21;
          v5 = (int *)v2[v4];
          v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
          v7 = *v5;
          v21 = v6;
          v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 124))(v5);
          if ( (int)abs32(v21 - v8) < 40 )
          {
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0 )
            {
              v9 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v4) + 120))(*((uint32_t *)Block + v4));
              if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v9 < 300 )
              {
                v10 = *((int **)Block + v4);
                v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
                v12 = *v10;
                v21 = v11;
                v13 = (*(int (/*thiscall*/ **)(int *))(v12 + 120))(v10);
                if ( v21 - v13 > 50 && rand() % 100 < 20 )
                  goto LABEL_19;
              }
            }
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 )
            {
              v14 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v4) + 120))(*((uint32_t *)Block + v4));
              if ( v14 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < 300 )
              {
                v15 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v4) + 120))(*((uint32_t *)Block + v4));
                if ( v15 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) > 50 && rand() % 100 < 20 )
                {
LABEL_19:
                  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 16, 0, 0, 0);
                  sub_5E5260(&v17);
                  return 1;
                }
              }
            }
          }
          v3 = v19;
          v2 = Block;
          ++v4;
        }
      }
      else
      {
LABEL_21:
        j__free(v2);
      }
    }
  }
  return 0;
}



// AI 相位辅助（79L；this+8608）
// ------------------------------------------------------------
// 0x5ACA40 sub_5ACA40
// ------------------------------------------------------------
char /*thiscall*/ sub_5ACA40(uint32_t *this)
{
  int v2; // ecx
  int v3; // eax
  unsigned int i; // ebx
  int *v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edi
  int v10; // edi
  int v11; // edi
  int v12; // edi
  void *v14; // [esp+Ch] [ebp-20h] BYREF
  int v15; // [esp+10h] [ebp-1Ch]
  int v16; // [esp+14h] [ebp-18h]
  int v17; // [esp+18h] [ebp-14h]
  int v18; // [esp+1Ch] [ebp-10h]
  int v19; // [esp+28h] [ebp-4h]

  if ( *(this + 2154) == 2
    && *(this + 2153) == 2
    && *((uint8_t *)this + 8608) == 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
    && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) >= *(this + 81) )
  {
    v15 = 0;
    v16 = 0;
    v17 = 0;
    v19 = 0;
    sub_4E0CD0(17, 0, &v14, 300);
    v2 = v15;
    if ( v15 != 0 )
    {
      v3 = v16;
      if ( (v16 - v15) >> 2 != 0 )
      {
        for ( i = 0; v2 != 0 && i < (v3 - v2) >> 2; ++i )
        {
          v5 = *(int **)(v2 + 4 * i);
          v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
          v7 = *v5;
          v18 = v6;
          v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 124))(v5);
          if ( (int)abs32(v18 - v8) < 40 )
          {
            if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0
              && (v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)),
                  (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v9 < 300)
              && (v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)),
                  (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v10 > 50)
              && rand() % 100 < 20
              || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1
              && (v11 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)))
               - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < 300
              && (v12 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)))
               - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) > 50
              && rand() % 100 < 20 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
              sub_5E5260(&v14);
              return 1;
            }
          }
          v3 = v16;
          v2 = v15;
        }
      }
    }
    sub_5E5260(&v14);
  }
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5ACC70 sub_5ACC70
// ------------------------------------------------------------
char /*thiscall*/ sub_5ACC70(uint32_t *this)
{
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) == 15 )
    return sub_5AC830(this);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) < 130 )
    return 0;
  return sub_5ACA40(this);
}



// AI 复合（sub_431230+sub_699000+RTTI cast, 55L）
// ------------------------------------------------------------
// 0x5ACCB0 sub_5ACCB0
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACCB0(uint32_t *this, int a2, int a3, int a4)
{
  int v4; // edi
  int v6; // eax
  void *v8[4]; // [esp+8h] [ebp-20h] BYREF
  int v9; // [esp+18h] [ebp-10h] BYREF
  int v10; // [esp+24h] [ebp-4h]

  v4 = a2;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) == 1
    && (uint8_t)a4 == 0
    && sub_41A5E0((unsigned int)(this + 1757)) == 1 )
  {
    v6 = __RTDynamicCast(a2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    if ( v6 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t *, uint32_t))(*(uint32_t *)v6 + 760))(
        v6,
        3,
        1120403456,
        2,
        this,
        0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t *, uint32_t))(*this + 764))(this, 3, 2, this, 0);
        *(this + 2151) = sub_699000((int)(this + 9)) + 10000;
        memset(&v8[1], 0, 12);
        v10 = 0;
        v9 = 4;
        sub_431230((int)v8, &v9);
        v9 = 0;
        sub_431230((int)v8, &v9);
        v9 = 1;
        sub_431230((int)v8, &v9);
        v9 = 200;
        sub_431230((int)v8, &v9);
        v9 = 200;
        sub_431230((int)v8, &v9);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 4, v8, 0, 0);
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
        v10 = -1;
        sub_5E5260(v8);
        v4 = a2;
      }
    }
  }
  return sub_5AA130(this, v4, a3, a4);
}



// 飞龙装载 2：FLYDRAGON_HIT/DMG + FDRG_DIE 语音 + Particle/FireBreath.ptl 火息粒子（41L）
// ------------------------------------------------------------
// 0x5ACE30 sub_5ACE30
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACE30(char *this)
{
  int v2; // eax
  int *v3; // eax
  int v4; // edx
  int v6; // [esp+8h] [ebp-10h] BYREF
  int v7; // [esp+14h] [ebp-4h]

  sub_4015C0("FLYDRAGON_HIT", 0xDu);
  sub_4015C0("FLYDRAGON_DMG", 0xDu);
  sub_4015C0("FDRG_DIE", 8u);
  v2 = *(uint32_t *)this;
  *(this + 8600) = 0;
  (*(void (/*thiscall*/ **)(char *))(v2 + 688))(this);
  sub_4EB2C0(1.5);
  v7 = 0;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      v3 = (int *)sub_4C3640(this + 364, "Particle/FireBreath.ptl", this);
    else
      v3 = (int *)sub_4C3640(*((uint32_t *)this + 91), "Particle/FireBreath.ptl", this);
  }
  else
  {
    v3 = nullptr;
  }
  *((uint32_t *)this + 2151) = v3;
  v4 = *v3;
  v7 = -1;
  (*(void (/*thiscall*/ **)(int *, char *))(v4 + 112))(v3, this);
  *((uint32_t *)this + 2152) = sub_699000((int)(this + 7640));
  v6 = 100000;
  return sub_4E1390(196612, &v6);
}



// ============================================================
// 【分区 11】猎人 Hunter（HH/HM/HA 三型）（0x5ACF40-0x5AE3C0）
// 证据：HUNTER_SPIT/READY/SCREAM/FIND/DMG/DIE/ATK、HUNT_BREATH_LOOP/HUNT_HARD_BREATH_LOOP、
//       HUNT_JUMP、Particle/HunterSpittle.ptl 酸液、Monster/Hunter/{HH,HM,HA}/*.equ

// AI 字段访问
// ------------------------------------------------------------
// 0x5ACF40 sub_5ACF40
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACF40(void *this)
{
  sub_4D9760();
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1284))(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5ACF60 sub_5ACF60
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACF60(void *this, void *a2)
{
  int result; // eax

  result = sub_4D9170(a2);
  if ( this == a2 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 9);
  return result;
}



// AI 相位辅助（63L）
// ------------------------------------------------------------
// 0x5ACF90 sub_5ACF90
// ------------------------------------------------------------
int /*usercall*/ sub_5ACF90@<eax>(uint32_t **a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int result; // eax
  int v5; // edi
  int v6; // eax
  uint32_t *v7; // ebx
  int v8; // edi
  int64_t v9; // rax
  int v10; // ebx
  int v11; // edi
  int v12; // edi
  int v13; // [esp+4h] [ebp-8h]
  int v14; // [esp+4h] [ebp-8h]
  int v15; // [esp+8h] [ebp-4h]

  result = sub_4E0120();
  if ( a1[1787] != (uint32_t *)16 )
  {
    if ( a1[1813] != nullptr )
    {
      ((void (/*thiscall*/ *)(uint32_t **, int))(*a1)[276])(a1, 5);
      result = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[77])(a1);
      if ( (uint8_t)result != 0 )
      {
        result = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[210])(a1);
        if ( result == 6 )
        {
          v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1[1813] + 120))(a1[1813], a3, a2);
          v6 = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[30])(a1);
          v7 = a1[1813];
          v8 = abs32(v6 - v5);
          v13 = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[31])(a1);
          v9 = v13 - (*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 124))(v7);
          v10 = (HIDWORD(v9) ^ v9) - HIDWORD(v9);
          v14 = 4;
          v15 = 4;
          if ( v8 > 100 )
          {
            v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1[1813] + 120))(a1[1813]);
            v14 = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[30])(a1) < v11;
          }
          if ( v10 > 100 )
          {
            v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1[1813] + 124))(a1[1813]);
            v15 = (((int (/*thiscall*/ *)(uint32_t **))(*a1)[31])(a1) < v12) + 2;
          }
          return ((int (/*thiscall*/ *)(uint32_t **, int, int))(*a1)[224])(a1, v14, v15);
        }
      }
    }
    else
    {
      return ((int (/*thiscall*/ *)(uint32_t **, int))(*a1)[276])(a1, 13);
    }
  }
  return result;
}



// 【vmt200 命中处理器覆写】猎人系小型覆写（13L；虚表 0x6DF754/0x6DFC7C/0x6E01A4/0x6E06CC 四张 +512 槽）
// ------------------------------------------------------------
// 0x5AD0B0 sub_5AD0B0
// ------------------------------------------------------------
int /*stdcall*/ sub_5AD0B0(int a1, int a2, int a3)
{
  if ( (uint8_t)a3 == 1 )
    return 0;
  else
    return sub_4DA3B0(a1, a2, a3);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AD0E0 sub_5AD0E0
// ------------------------------------------------------------
// attributes: thunk
int sub_5AD0E0()
{
  return sub_4E1BE0();
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AD0F0 sub_5AD0F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD0F0(uint32_t *this)
{
  sub_424120(*(uint32_t **)(*(this + 29) + 132), 3, 100);
  sub_49C620(8, 0, 0);
  return sub_49C5F0(9, 0, 0, 400);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD130 sub_5AD130
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD130(void *this, int a2)
{
  int v3; // edi
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
  v3 = *(uint32_t *)dword_8F8520;
  v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, v4);
  v5 = *(uint32_t *)dword_8F8520;
  v6 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
  v7 = *(uint32_t *)dword_8F8520;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a2);
  if ( (uint16_t)a2 >= 0xEu && (uint16_t)a2 <= 0xFu )
  {
    v9 = *(uint32_t *)dword_8F8520;
    v10 = rand();
    (*(void (/*thiscall*/ **)(int, int))(v9 + 40))(dword_8F8520, v10);
  }
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// 技能播报：HUNTER_SPIT（吐酸）
// ------------------------------------------------------------
// 0x5AD1E0 sub_5AD1E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD1E0(int *this, int a2)
{
  int v3; // eax
  int v4; // ebx
  int v5; // edi
  int v6; // eax

  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  v4 = *this;
  v5 = v3 != 0 ? 80 : 70;
  v6 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 128))(this, 4, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t, int, uint32_t, int))(v4 + 580))(
    this,
    30003,
    0,
    a2,
    0,
    v5,
    0,
    v6 + 50);
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HUNTER_SPIT", -1, 0, 0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD250 sub_5AD250
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD250(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  int v4; // et2
  int v5; // eax
  int v6; // et2

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v3 = rand();
    v4 = v3 % 100;
    result = v3 / 100;
    if ( v4 >= 10 )
    {
      if ( *(this + 1943) == 3 )
      {
        v5 = rand();
        v6 = v5 % 100;
        result = v5 / 100;
        if ( v6 < 50 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
            this,
            48001,
            2,
            0,
            0,
            0,
            0,
            0,
            4,
            0,
            0,
            0);
          sub_49C970(8, 0, 0);
          return sub_49C5F0(9, 0, 0, 1000);
        }
      }
    }
    else
    {
      return sub_5AD130(this, 16);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD2E0 sub_5AD2E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD2E0(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  int v4; // [esp-18h] [ebp-1Ch]
  int v5; // [esp-10h] [ebp-14h]

  sub_424120(*(uint32_t **)(*(this + 29) + 132), 3, 100);
  sub_49C620(8, 0, 0);
  sub_49C5F0(9, 0, 0, 400);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    return sub_4E4A50(this, 30064, 0, v3, v4, 0, v5, 0, 0, 0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD360 sub_5AD360
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD360(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  int v4; // [esp-18h] [ebp-1Ch]
  int v5; // [esp-10h] [ebp-14h]

  sub_424120(*(uint32_t **)(*(this + 29) + 132), 3, 100);
  sub_49C620(8, 0, 0);
  sub_49C5F0(9, 0, 0, 400);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    return sub_4E4A50(this, 30022, 0, v3, v4, 0, v5, 0, 0, 0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD3E0 sub_5AD3E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD3E0(uint32_t *this, int a2, int a3)
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( a3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = a2;
  if ( a2 == 0 )
    *(this + 1899) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD450 sub_5AD450
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD450(uint32_t *this, int a2, int a3)
{
  unsigned int v4; // esi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( a3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = a2;
  if ( a2 == 0 )
    *(this + 1899) = 50;
  return result;
}



// 瞄准 AI：HUNTER_READY 播报（this+200/8604-8606 相位, 28L）
// ------------------------------------------------------------
// 0x5AD4C0 sub_5AD4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD4C0(uint32_t *this, int a2, int a3)
{
  int v4; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1550) + 4 * ((a3 != 14) + 2)));
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  sub_4926A0(v4);
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "HUNTER_READY",
             -1,
             0,
             0);
  *(this + 2154) = a3;
  *((uint8_t *)this + 8604) = 1;
  *((uint8_t *)this + 8606) = 0;
  *((uint8_t *)this + 8605) = 0;
  *(this + 2152) = 0;
  *(this + 2153) = a2;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AD550 sub_5AD550
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD550(int **this)
{
  ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[52])(this, **(this + 1554));
  sub_4926A0(**(this + 1554));
  return ((int (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
           this,
           1000,
           **(this + 1554),
           0,
           0,
           0,
           0);
}



// 酸液弹：引用 Particle/HunterSpittle.ptl（this+200/8605/8606）
// ------------------------------------------------------------
// 0x5AD5A0 sub_5AD5A0
// ------------------------------------------------------------
char /*thiscall*/ sub_5AD5A0(int this)
{
  int v2; // eax
  int v3; // eax

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 6
    && *(uint8_t *)(this + 8605) == 0 )
  {
    sub_5AD550((int **)this);
    *(uint8_t *)(this + 8605) = 1;
  }
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
  if ( *(uint32_t *)(v2 + 148) == 6 )
  {
    LOBYTE(v2) = *(uint8_t *)(this + 8606);
    if ( (uint8_t)v2 == 0 )
    {
      v3 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(this, "Particle/HunterSpittle.ptl");
      LOBYTE(v2) = sub_5AD1E0((int *)this, v3);
      *(uint8_t *)(this + 8606) = 1;
    }
  }
  return v2;
}



// 酸液弹 2：Particle/HunterSpittle.ptl（67L；this+200/8605/8606/8608）
// ------------------------------------------------------------
// 0x5AD610 sub_5AD610
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD610(int this)
{
  int *v2; // eax
  uint16_t *v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // ecx
  int v7; // esi
  int result; // eax
  int v9; // esi
  uint32_t v10[3]; // [esp+8h] [ebp-80h]
  uint32_t v11[3]; // [esp+14h] [ebp-74h]
  uint32_t v12[26]; // [esp+20h] [ebp-68h] BYREF

  v12[25] = dword_796E50;
  v2 = *(int **)this;
  v11[0] = 8;
  v11[1] = 10;
  v11[2] = 12;
  v10[0] = 0;
  v10[1] = 45;
  v10[2] = 320;
  if ( *(uint32_t *)(((int (/*thiscall*/ *)(int))v2[50])(this) + 148) == 8 && *(uint8_t *)(this + 8605) == 0 )
  {
    sub_5AD550((int **)this);
    *(uint8_t *)(this + 8605) = 1;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == v11[*(uint32_t *)(this + 8608)]
    && *(uint8_t *)(this + 8606) == 0 )
  {
    v3 = (uint16_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(this, "Particle/HunterSpittle.ptl");
    qmemcpy(v12, v3, 0x60u);
    v4 = v10[*(uint32_t *)(this + 8608)];
    LOWORD(v12[24]) = v3[48];
    v12[18] = v4;
    sub_5AD1E0((int *)this, (int)v12);
    *(uint8_t *)(this + 8606) = 1;
  }
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
  v6 = *(uint32_t *)(this + 8608);
  if ( *(uint32_t *)(v5 + 148) == v11[v6] + 1 )
  {
    *(uint8_t *)(this + 8606) = 0;
    *(uint32_t *)(this + 8608) = v6 + 1;
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) == 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < v7 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 144))(this, 1);
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
  if ( result == 1 )
  {
    v9 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
    if ( result >= v9 )
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 144))(this, 0);
  }
  return result;
}



// AI 字段访问（this+8621）
// ------------------------------------------------------------
// 0x5AD780 sub_5AD780
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5AD780(uint32_t *this)
{
  unsigned int result; // eax
  int v3; // edi

  result = *(this + 1813);
  *(uint8_t *)(*(this + 1905) + 32) = result != 0
                                 && *((uint8_t *)this + 8621) == 1
                                 && (v3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                                     (signed int)(result = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v3)) < *(this + 2150));
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD7E0 sub_5AD7E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD7E0(uint32_t *this, int a2, int a3)
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( a3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(uint8_t *)(*(this + 1905) + 96) = 0;
  }
  result = a2;
  if ( a2 == 0 )
    *(this + 1899) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD850 sub_5AD850
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD850(uint32_t *this, int a2, int a3)
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( a3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(uint8_t *)(*(this + 1905) + 96) = 1;
  }
  result = a2;
  if ( a2 == 0 )
    *(this + 1899) = 50;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD8C0 sub_5AD8C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD8C0(uint32_t *this, int a2, int a3)
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( a3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = a2;
  if ( a2 != 0 )
  {
    if ( a2 > 0 && a2 <= 2 )
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) * 0.5;
  }
  else
  {
    *(this + 1899) = 0;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD950 sub_5AD950
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD950(uint32_t *this, int a2, int a3)
{
  unsigned int v4; // esi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( a3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = a2;
  if ( a2 != 0 )
  {
    if ( a2 > 0 && a2 <= 2 )
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) + *(float *)(*(this + 1905) + 132);
  }
  else
  {
    *(this + 1899) = 50;
  }
  return result;
}



// AI 复合字段（this+200/8604/8616..8648, 62L）
// ------------------------------------------------------------
// 0x5AD9E0 sub_5AD9E0
// ------------------------------------------------------------
char /*thiscall*/ sub_5AD9E0(int this)
{
  int v2; // eax
  int v3; // eax

  sub_4E1780((uint32_t *)this);
  if ( *(uint8_t *)(this + 8604) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) != 0 )
  {
    if ( *(uint32_t *)(this + 7252) != 0 )
    {
      if ( *(uint32_t *)(this + 8616) == 14 )
        sub_5AD5A0(this);
      else
        sub_5AD610(this);
    }
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )
      *(uint8_t *)(this + 8604) = 0;
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 6 )
  {
    if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 3 && *(uint8_t *)(this + 8620) == 0 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
      *(uint8_t *)(this + 8620) = 1;
    }
  }
  else
  {
    sub_5AD780((uint32_t *)this);
  }
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( v2 != 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this) == 4
    && (v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 188))(this)) == 4 )
  {
    if ( *(uint8_t *)(this + 8622) == 1 )
    {
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 9);
      *(uint8_t *)(this + 8622) = 0;
    }
  }
  else
  {
    LOBYTE(v2) = *(uint8_t *)(this + 8622);
    if ( (uint8_t)v2 == 0 )
    {
      if ( *(uint32_t *)(this + 8648) < 0x10u )
        v3 = this + 8628;
      else
        v3 = *(uint32_t *)(this + 8628);
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, v3, 9, 0, 0);
      *(uint8_t *)(this + 8622) = 1;
    }
  }
  return v2;
}



// 猎人语音装载：HUNTER_FIND/DMG/DIE/ATK + HUNT_BREATH_LOOP 呼吸循环（27L）
// ------------------------------------------------------------
// 0x5ADB10 sub_5ADB10
// ------------------------------------------------------------
int /*thiscall*/ sub_5ADB10(int this)
{
  int result; // eax

  *(uint32_t *)(this + 6792) = 1;
  *(uint32_t *)(this + 6864) = 1;
  *(uint32_t *)(this + 6796) = 2;
  *(uint32_t *)(this + 6800) = 3;
  *(uint32_t *)(this + 6804) = 3;
  *(uint32_t *)(this + 6808) = 4;
  *(uint32_t *)(this + 6868) = 3;
  *(uint32_t *)(this + 6872) = 5;
  sub_4015C0("HUNTER_FIND", 0xBu);
  sub_4015C0("HUNTER_DMG", 0xAu);
  sub_4015C0("HUNTER_DIE", 0xAu);
  sub_4015C0("HUNTER_ATK", 0xAu);
  *(uint8_t *)(this + 8622) = 0;
  result = sub_4015C0("HUNT_BREATH_LOOP", 0x10u);
  *(uint8_t *)(this + 8604) = 0;
  return result;
}



// 语音播报：HUNT_HARD_BREATH_LOOP（重呼吸/暴走前兆, 12L）
// ------------------------------------------------------------
// 0x5ADBD0 sub_5ADBD0
// ------------------------------------------------------------
char /*thiscall*/ sub_5ADBD0(uint32_t *this)
{
  if ( *(this + 1908) == 0 )
    sub_4015C0("HUNT_HARD_BREATH_LOOP", 0x15u);
  return sub_5AD9E0((int)this);
}



// 扑跳 AI：HUNT_JUMP 播报（43L；sub_431230 参数打包）
// ------------------------------------------------------------
// 0x5ADC00 sub_5ADC00
// ------------------------------------------------------------
void /*thiscall*/ sub_5ADC00(uint8_t *this)
{
  int v2; // edi
  float v3; // eax
  uint8_t v4[4]; // [esp+8h] [ebp-24h] BYREF
  void *Block; // [esp+Ch] [ebp-20h]
  int v6; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-18h]
  int v8; // [esp+18h] [ebp-14h] BYREF
  uint32_t v9[4]; // [esp+1Ch] [ebp-10h] BYREF

  (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
    this,
    "HUNT_JUMP",
    -1,
    0,
    0);
  if ( *(this + 8621) != 0 )
  {
    Block = nullptr;
    v6 = 0;
    v7 = 0;
    v9[3] = 0;
    v9[0] = 0;
    sub_431230((int)v4, v9);
    v9[0] = 0;
    sub_431230((int)v4, v9);
    v2 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 672))(this, 3);
    v9[0] = sub_41A5E0(v2 + 928);
    v3 = COERCE_FLOAT(sub_41A5E0(v2 + 942));
    v8 = (uint64_t)((double)v9[0] * v3);
    sub_431230((int)v4, &v8);
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint8_t *, int, int))(*(uint32_t *)this + 472))(this, 6, v4, 1, 1);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 尖啸 AI：HUNTER_SCREAM 播报（70L；this+208/8620 相位）
// ------------------------------------------------------------
// 0x5ADCF0 sub_5ADCF0
// ------------------------------------------------------------
void /*thiscall*/ sub_5ADCF0(uint32_t *this, int ArgList, float a3, int a4, int a5)
{
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  BOOL v9; // edi
  int v10; // ebx
  int v11; // eax

  v6 = *(this + 1639);
  if ( v6 == 6 )
  {
    if ( ArgList == 0 )
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);
  }
  else if ( v6 == 8 && (sub_41A5E0((unsigned int)(this + 1757)) == 2 || sub_41A5E0((unsigned int)(this + 1757)) == 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
  }
  sub_4E33D0(ArgList, a3, a4, a5);
  if ( ArgList == 6 )
  {
    v7 = *(this + 1813);
    if ( v7 != 0 )
    {
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 120))(v7);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < v8;
      v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, BOOL, int))(*this + 896))(this, v9, (v11 < v10) + 2);
      *((uint8_t *)this + 8620) = 0;
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 472))(this, 0, 0, 1, 1);
    }
  }
  else if ( ArgList == 8 && sub_41A5E0((unsigned int)(this + 1757)) != 0 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 1 )
    {
      sub_5ADC00(this);
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        sub_5AD130(this, 14);
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 3 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        sub_5AD130(this, 15);
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 4 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
        this,
        "HUNTER_SCREAM",
        -1,
        0,
        0);
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5ADEA0 sub_5ADEA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5ADEA0(uint32_t *this)
{
  int result; // eax
  int v3; // esi
  int v4; // [esp+8h] [ebp-4h] BYREF

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v4);
    if ( (uint16_t)v3 >= 0xEu )
    {
      if ( (uint16_t)v3 <= 0xFu )
      {
        sub_5AD4C0(this, v4, (uint16_t)v3);
      }
      else if ( (uint16_t)v3 == 16 )
      {
        sub_5ADC00(this);
        return v3;
      }
    }
    return v3;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5ADF00 sub_5ADF00
// ------------------------------------------------------------
void /*thiscall*/ sub_5ADF00(uint32_t *this, int ArgList, float a3, int a4, int a5)
{
  int v6; // edi
  uint64_t v7; // rax
  int v8; // edi
  int v9; // eax
  int v10; // [esp+1Ch] [ebp+14h]

  sub_5ADCF0(this, ArgList, a3, a4, a5);
  if ( ArgList == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
    v10 = sub_41A5E0(v6 + 816);
    v7 = (uint64_t)((double)v10 * COERCE_FLOAT(sub_41A5E0(v6 + 830)));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(
      this,
      0,
      (int)v7 / 2,
      (int)v7 / 2,
      0,
      -2 * ((int)v7 / 2),
      1);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      1,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);
    v8 = *this;
    v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v8 + 896))(this, v9);
    --*(this + 2163);
  }
}



// HH 猎人装载：Monster/Hunter/HH/{horn,hair,clothes,claws}.equ（59L）
// ------------------------------------------------------------
// 0x5ADFE0 sub_5ADFE0
// ------------------------------------------------------------
int /*usercall*/ sub_5ADFE0@<eax>(int a1@<ecx>, int a2@<ebx>)
{
  char *v3; // eax
  char *v4; // eax
  int v5; // eax
  char *v6; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  char *v10; // eax
  int v11; // eax
  char *v12; // eax
  char *v13; // eax
  int result; // eax

  v3 = (char *)operator new(0x544u);
  if ( v3 != nullptr )
    v4 = sub_4BA9E0(v3, "Monster/Hunter/HH/horn.equ", 0);
  else
    v4 = nullptr;
  v5 = (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)a1 + 784))(a1, v4, a2);
  if ( v5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 4))(v5, 1);
  v6 = (char *)operator new(0x544u);
  if ( v6 != nullptr )
    v7 = sub_4BA9E0(v6, "Monster/Hunter/HH/hair.equ", 0);
  else
    v7 = nullptr;
  v8 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1 + 784))(a1, v7);
  if ( v8 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 4))(v8, 1);
  v9 = (char *)operator new(0x544u);
  if ( v9 != nullptr )
    v10 = sub_4BA9E0(v9, "Monster/Hunter/HH/clothes.equ", 0);
  else
    v10 = nullptr;
  v11 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1 + 784))(a1, v10);
  if ( v11 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v11 + 4))(v11, 1);
  v12 = (char *)operator new(0x544u);
  if ( v12 != nullptr )
    v13 = sub_4BA9E0(v12, "Monster/Hunter/HH/claws.equ", 0);
  else
    v13 = nullptr;
  result = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)a1 + 784))(a1, v13);
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  *(uint32_t *)(a1 + 8652) = 0;
  *(uint8_t *)(a1 + 8621) = 1;
  *(uint32_t *)(a1 + 8600) = 150;
  *(uint32_t *)(a1 + 7576) = 2;
  return result;
}



// HM 猎人装载：Monster/Hunter/HM/{horn,hair,clothes}.equ（this+8621 相位）
// ------------------------------------------------------------
// 0x5AE160 sub_5AE160
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE160(uint8_t *this)
{
  char *v2; // eax
  char *v3; // eax
  int v4; // eax
  char *v5; // eax
  char *v6; // eax
  int v7; // eax
  char *v8; // eax
  char *v9; // eax
  int result; // eax

  v2 = (char *)operator new(0x544u);
  if ( v2 != nullptr )
    v3 = sub_4BA9E0(v2, "Monster/Hunter/HM/horn.equ", 0);
  else
    v3 = nullptr;
  v4 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 4))(v4, 1);
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Hunter/HM/hair.equ", 0);
  else
    v6 = nullptr;
  v7 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 4))(v7, 1);
  v8 = (char *)operator new(0x544u);
  if ( v8 != nullptr )
    v9 = sub_4BA9E0(v8, "Monster/Hunter/HM/clothes.equ", 0);
  else
    v9 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v9);
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  *(this + 8621) = 1;
  *((uint32_t *)this + 2150) = 150;
  *(this + 7537) = 1;
  return result;
}



// HA 猎人装载：Monster/Hunter/HA/{horn,clothes,blindfold}.equ（蒙眼布, this+8621）
// ------------------------------------------------------------
// 0x5AE290 sub_5AE290
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE290(uint8_t *this)
{
  char *v2; // eax
  char *v3; // eax
  int v4; // eax
  char *v5; // eax
  char *v6; // eax
  int v7; // eax
  char *v8; // eax
  char *v9; // eax
  int result; // eax

  v2 = (char *)operator new(0x544u);
  if ( v2 != nullptr )
    v3 = sub_4BA9E0(v2, "Monster/Hunter/HA/horn.equ", 0);
  else
    v3 = nullptr;
  v4 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( v4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 4))(v4, 1);
  v5 = (char *)operator new(0x544u);
  if ( v5 != nullptr )
    v6 = sub_4BA9E0(v5, "Monster/Hunter/HA/clothes.equ", 0);
  else
    v6 = nullptr;
  v7 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( v7 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 4))(v7, 1);
  v8 = (char *)operator new(0x544u);
  if ( v8 != nullptr )
    v9 = sub_4BA9E0(v8, "Monster/Hunter/HA/blindfold.equ", 0);
  else
    v9 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v9);
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  *(this + 8621) = 0;
  *((uint32_t *)this + 2150) = 0;
  *((uint32_t *)this + 1895) = 1;
  return result;
}



// ============================================================
// 【分区 12】僵尸 & 卡尔卡扎克（Zombie / Kalkazak）（0x5AE3C0-0x5AFAB0）
// 证据：ZOMBIE_EYEPULL/BITE/FIND/DMG/DIE/ATK、zombie/Kalkazak.mob、Particle/ZombieEye.ptl、
//       KALKAZAK_01 + ENLARGE 巨大化、0x5AE990 调 sub_4E4430（HP 受击处理器/Boss 终局族）

// AI 字段访问
// ------------------------------------------------------------
// 0x5AE3C0 sub_5AE3C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE3C0(uint32_t *this, int a2)
{
  int v2; // eax

  v2 = *(this + a2 + 4);
  if ( v2 != 0 )
    return *(uint32_t *)(v2 + 196);
  else
    return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AE3E0 sub_5AE3E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE3E0(uint32_t *this)
{
  uint32_t *v2; // ecx

  *(this + 2150) = 0;
  *(this + 2151) = 0;
  *(this + 2158) = 0;
  v2 = this + 2160;
  *v2 = 0;
  v2[1] = 0;
  v2[2] = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE410 sub_5AE410
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE410(void *this, int a2)
{
  int v3; // edi
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
  v3 = *(uint32_t *)dword_8F8520;
  v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, v4);
  v5 = *(uint32_t *)dword_8F8520;
  v6 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
  v7 = *(uint32_t *)dword_8F8520;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, a2);
  v9 = *(uint32_t *)dword_8F8520;
  v10 = rand();
  (*(void (/*thiscall*/ **)(int, int))(v9 + 40))(dword_8F8520, v10);
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// 技能播报：ZOMBIE_EYEPULL（抠眼, 31L）
// ------------------------------------------------------------
// 0x5AE4B0 sub_5AE4B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE4B0(uint32_t *this, int a2)
{
  int v3; // eax

  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
    this,
    30004,
    *(this + 2157),
    a2,
    0,
    v3 != 0 ? 40 : 30,
    0,
    50,
    4,
    0,
    0,
    0);
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "ZOMBIE_EYEPULL",
           -1,
           0,
           0);
}



// 撕咬 AI：ZOMBIE_BITE 播报（99L）
// ------------------------------------------------------------
// 0x5AE510 sub_5AE510
// ------------------------------------------------------------
int /*usercall*/ sub_5AE510@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>)
{
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  double v6; // st7
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  unsigned int v14; // eax
  int v15; // eax
  int result; // eax
  float v17; // [esp+4h] [ebp-1Ch] BYREF
  float v18; // [esp+8h] [ebp-18h]
  float v19; // [esp+Ch] [ebp-14h]
  int v20; // [esp+10h] [ebp-10h]
  int v21; // [esp+14h] [ebp-Ch]
  int v22; // [esp+18h] [ebp-8h]
  int v23; // [esp+1Ch] [ebp-4h]

  v3 = a1[2150];
  if ( v3 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 15, 0, 0, 0);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 840))(v3) == 9 )
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 170) != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1) != 0 )
      {
        v4 = *a1;
        v17 = 0.0;
        v18 = 0.0;
        v19 = 0.0;
        v20 = 0;
        v21 = 0;
        v22 = 0;
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 152))(a1) != 0 )
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1) + 40;
        else
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 120))(a1) - 40;
        v23 = v5;
        v6 = (double)v5;
        v7 = *a1;
        v17 = v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 124))(a1);
        v9 = *a1;
        v23 = v8;
        v18 = (float)v8;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(a1);
        v11 = a1[2150];
        v23 = v10;
        v19 = (float)v10;
        sub_4E5F70(a2, (int)a1, v11, &v17, 1, 1);
      }
      v12 = a1[2152];
      v13 = a1[2151] + 1;
      a1[2151] = v13;
      if ( v13 >= v12
        || (v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[2150] + 684))(a1[2150]), sub_41A5E0(v14) <= 0) )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*a1 + 560))(a1, 15, 0, 0, 0);
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(a1, "ZOMBIE_BITE", -1, 0, 0);
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1);
        sub_4926A0(v15);
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)a1[2150] + 604))(a1[2150], 0);
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)a1[2150] + 612))(a1[2150], 1, 1);
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[2150] + 840))(a1[2150]);
    if ( result != 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)a1[2150] + 308))(a1[2150]);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1[2150] + 560))(
                 a1[2150],
                 9,
                 0,
                 0,
                 0);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE6E0 sub_5AE6E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE6E0(int this, int a2, int a3)
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
  *(uint32_t *)(this + 7568) = 2;
  *(uint8_t *)(this + 7550) = 1;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE770 sub_5AE770
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE770(void *this)
{
  int v2; // edi
  int v3; // ebx
  int v4; // eax
  int v6; // [esp+0h] [ebp-20h]
  int v7; // [esp+10h] [ebp-10h]

  sub_4DE410();
  (*(void (/*thiscall*/ **)(void *, void *))(*(uint32_t *)this + 700))(this, this);
  sub_53F6A0(v6);
  v2 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 2);
  v3 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 3);
  v7 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 4);
  if ( operator new(0x88u) != nullptr )
    v4 = sub_649CF0(v3, v7, v2);
  else
    v4 = 0;
  return (*(int (/*thiscall*/ **)(int, void *, void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)v4 + 56))(
           v4,
           this,
           this,
           0,
           0,
           0,
           -1);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AE830 sub_5AE830
// ------------------------------------------------------------
int sub_5AE830()
{
  int v1; // [esp+0h] [ebp-4h] BYREF

  v1 = 100000;
  return sub_4E1390(196613, &v1);
}



// mob 引用：zombie/Kalkazak.mob（卡尔卡扎克数据文件, 34L）
// ------------------------------------------------------------
// 0x5AE850 sub_5AE850
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE850(int *this, int a2)
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v8; // [esp+Ch] [ebp-4h]
  bool v9; // [esp+1Bh] [ebp+Bh]

  v9 = *(uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3) > a2;
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);
  (*(void (/*thiscall*/ **)(int *, int, const char *))(*this + 1024))(this, a2, "zombie/Kalkazak.mob");
  v5 = *this;
  if ( !v9 )
  {
    v4 += (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this) - v8;
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 740))(this) < v4 )
      goto LABEL_3;
LABEL_5:
    v6 = v4;
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 732))(this, v6, 0, 1);
  }
  if ( v4 < (*(int (/*thiscall*/ **)(int *))(v5 + 740))(this) )
    goto LABEL_5;
LABEL_3:
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(*this + 732))(this, v6, 0, 1);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AE900 sub_5AE900
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE900(void *this)
{
  int v2; // eax

  sub_4D9760();
  (*(void (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 768))(this, 9, 10, 0);
  v2 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 772))(this, 9, 999999999);
  return sub_497110(v2);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE940 sub_5AE940
// ------------------------------------------------------------
int /*stdcall*/ sub_5AE940(uint32_t *a1, int a2)
{
  int result; // eax
  int v3; // esi

  result = sub_4DC390(a1, a2);
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 20) != 0 )
    {
      return v3;
    }
    else
    {
      *a1 = 0;
      return 2;
    }
  }
  return result;
}



// 死亡/终局钩：调 sub_4E4430 = HP 受击处理器（研究 31 Boss 终局长震/R_STAGE_FINALE 族；
//   this+8652 相位, 30L）
// ------------------------------------------------------------
// 0x5AE990 sub_5AE990
// ------------------------------------------------------------
void /*thiscall*/ sub_5AE990(char *this, int a2, int a3, char a4)
{
  int v5; // edx
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+Ch] [ebp+8h]
  float v9; // [esp+14h] [ebp+10h]

  sub_4E4430(this, a2, a3, a4);
  if ( *(this + 8652) == 0 )
  {
    v9 = (float)a2;
    if ( (double)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 740))(this) * 0.25 >= v9 )
    {
      v5 = *(uint32_t *)this;
      *(this + 8652) = 1;
      v6 = (*(int (/*thiscall*/ **)(char *, int))(v5 + 672))(this, 3) + 830;
      *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v6)) + 1.0;
      sub_41A590(v6, v7, v8);
      (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
      sub_4DB200(24, 1);
    }
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AEA40 sub_5AEA40
// ------------------------------------------------------------
int /*thiscall*/ sub_5AEA40(int *this)
{
  int v1; // eax
  int result; // eax
  int v3; // et2

  sub_594370(this);
  v1 = rand();
  v3 = v1 % 100;
  result = v1 / 100;
  if ( v3 < 2 )
    return sub_4DB200(24, 0);
  return result;
}



// 硬直字段（this+208/8616）
// ------------------------------------------------------------
// 0x5AEA70 sub_5AEA70
// ------------------------------------------------------------
int /*thiscall*/ sub_5AEA70(uint32_t *this)
{
  int v2; // eax
  int v3; // edx

  v2 = *(this + 1554);
  v3 = *this;
  *((uint8_t *)this + 8616) = 0;
  (*(void (/*stdcall*/ **)(uint32_t))(v3 + 208))(*(uint32_t *)(v2 + 8));
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));
}



// 僵尸眼技能：引用 Particle/ZombieEye.ptl（44L；this+6556==14 与 -15 派生条件
//   【推断：卡尔卡扎克巨大化/分身态判定】）
// ------------------------------------------------------------
// 0x5AEAB0 sub_5AEAB0
// ------------------------------------------------------------
int /*usercall*/ sub_5AEAB0@<eax>(int a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  int result; // eax

  sub_4E1780((uint32_t *)a1);
  if ( *(uint8_t *)(a1 + 8616) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1) + 148) == 6 && *(uint8_t *)(a1 + 8617) == 0 )
    {
      v3 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)a1 + 588))(a1, "Particle/ZombieEye.ptl");
      sub_5AE4B0((uint32_t *)a1, v3);
      *(uint8_t *)(a1 + 8617) = 1;
    }
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1);
      if ( *(uint8_t *)(result + 170) != 0 )
        return sub_5AEA70((uint32_t *)a1);
    }
  }
  else if ( *(uint32_t *)(a1 + 6556) == 14 )
  {
    return sub_5AE510((uint32_t *)a1, a2);
  }
  else
  {
    result = *(uint32_t *)(a1 + 6556) - 15;
    if ( *(uint32_t *)(a1 + 6556) == 15 )
    {
      result = *(uint32_t *)(a1 + 120);
      if ( *(uint8_t *)(result + 170) != 0 )
        return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 0, 0, 0, 0);
    }
  }
  return result;
}



// AI 相位辅助（53L）
// ------------------------------------------------------------
// 0x5AEB60 sub_5AEB60
// ------------------------------------------------------------
void /*thiscall*/ sub_5AEB60(float *this)
{
  int v2; // ecx
  bool v3; // zf
  int v4; // eax
  int v5; // eax
  double v6; // st7
  float v7; // [esp+0h] [ebp-Ch]
  uint32_t v8[2]; // [esp+4h] [ebp-8h]

  v2 = *((uint32_t *)this + 1813);
  if ( v2 != 0 )
  {
    v3 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v2 + 776))(v2, 11) == 0;
    v4 = *((uint32_t *)this + 2158);
    if ( v3 )
    {
      if ( v4 == 1 )
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t, int))(*(uint32_t *)this + 672))(this, 0, 1050253722);
        sub_4E99C0(v7);
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
        v6 = *(this + 2159) * 1.3;
        *(this + 2158) = 0.0;
        *(this + 2159) = v6;
        *(float *)(*((uint32_t *)this + 1905) + 36) = *(float *)(*((uint32_t *)this + 1905) + 36) * 0.76923078;
      }
    }
    else
    {
      if ( v4 == 0 )
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t, int))(*(uint32_t *)this + 672))(this, 0, 1050253722);
        sub_4AED60(v7);
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
        *(this + 2159) = *(this + 2159) * 0.76923078;
        *((uint32_t *)this + 2158) = 1;
        sub_4D82D0(0, 0);
        *(float *)(*((uint32_t *)this + 1905) + 36) = *(float *)(*((uint32_t *)this + 1905) + 36) * 1.3;
      }
      v8[0] = 0;
      v8[1] = 1;
      v5 = rand() % 2;
      sub_4DB200(24, v8[v5]);
    }
  }
}



// 硬直字段（this+204）
// ------------------------------------------------------------
// 0x5AECA0 sub_5AECA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AECA0(uint32_t *this)
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    1,
    *(uint32_t *)(*(this + 1554) + 8),
    0,
    0,
    0,
    0);
  sub_4926A0(*(uint32_t *)(*(this + 1554) + 8));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    3,
    *(uint32_t *)(*(this + 1554) + 12),
    0,
    0,
    0,
    0);
  return sub_4926A0(*(uint32_t *)(*(this + 1554) + 12));
}



// AI 相位辅助（46L）
// ------------------------------------------------------------
// 0x5AED10 sub_5AED10
// ------------------------------------------------------------
int /*thiscall*/ sub_5AED10(uint32_t *this, int a2)
{
  int result; // eax
  int v4; // eax
  int v5; // edx
  int v6; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = a2;
  if ( a2 == *(this + 2150) )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
    if ( result == 14 && (int)*(this + 2152) > 1 )
    {
      v4 = sub_491C10(*(uint32_t *)*(this + 1554));
      v5 = *(this + 2153) + 1;
      *(this + 2153) = v5;
      if ( v5 >= 5 * v4 / 1000 )
      {
        --*(this + 2152);
        *(this + 2153) = 0;
      }
      v6 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 120))(*(this + 2150));
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 916))(*(this + 2150));
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 120))(*(this + 2150));
      v8 = *this;
      v9 = v6 - v7;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v11);
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 112))(this, v12 - v9);
    }
  }
  return result;
}



// 蓄力技能：vt+212 "HOLD"（111L；sub_4049C0 插值）
// ------------------------------------------------------------
// 0x5AEDE0 sub_5AEDE0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AEDE0(uint32_t *this, int a2)
{
  int v3; // eax
  int v4; // edi
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ebx
  int v16; // edi
  int v17; // eax
  int v18; // eax
  uint32_t *v19; // edi
  int v20; // eax
  int v21; // edi
  uint32_t *v22; // eax
  uint64_t v23; // rax
  float v25; // [esp+70h] [ebp-20h]
  float v26; // [esp+74h] [ebp-1Ch]
  int v27; // [esp+8Ch] [ebp-4h]
  int v28; // [esp+98h] [ebp+8h]
  int v29; // [esp+98h] [ebp+8h]

  v3 = sub_45EBE0(**(uint32_t **)(a2 + 4), *(uint32_t *)(*(uint32_t *)(a2 + 4) + 4));
  v4 = v3;
  if ( v3 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v3 + 40))(v3, 17) == 0
    || (*(this + 2150) = v4, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 128))(v4) > 0) )
  {
    *(this + 2150) = 0;
  }
  v5 = *(this + 2150);
  if ( v5 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 120))(v5);
    v7 = *(this + 2150);
    *(this + 2160) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
    v9 = *(this + 2150);
    *(this + 2161) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v9 + 128))(v9);
    v11 = *this;
    *(this + 2162) = v10;
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v11 + 152))(this);
    v13 = *(this + 2150);
    if ( v12 != 0 )
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 120))(v13) - 40;
    else
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v13 + 120))(v13) + 40;
    v15 = *this;
    v28 = v14;
    v16 = *(this + 2150);
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v16 + 128))(v16);
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 124))(v16, v17);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v15 + 112))(this, v28, v18 + 1);
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2150) + 848))(*(this + 2150), 1);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
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
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 344))(this, *(this + 139));
  v19 = (uint32_t *)*(this + 28);
  if ( *v19 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v19 + 308))(*v19) != 0
    && *((float *)v19 + 6) != 0.0 )
  {
    v19[6] = 0;
    *((uint8_t *)v19 + 196) = 1;
  }
  sub_495890(0, 0);
  v27 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v21 = *(this + 1821) - *(this + 1820);
  v29 = v20;
  v22 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v26 = (float)v29;
  v25 = (float)v27;
  v23 = (uint64_t)sub_4049C0(v25, v26, *v22 - *(this + 1820), v21);
  *(this + 2152) = v23;
  LODWORD(v23) = *this;
  *(this + 2151) = 0;
  *(this + 2153) = 0;
  return (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, const char *, int, uint32_t, uint32_t))(v23 + 212))(
           this,
           HIDWORD(v23),
           "HOLD",
           -1,
           0,
           0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF000 sub_5AF000
// ------------------------------------------------------------
void /*thiscall*/ sub_5AF000(int this, int a2)
{
  int v3; // ebx

  v3 = *(uint32_t *)(this + 7252);
  sub_4D97E0(a2);
  if ( v3 != a2 && a2 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) != 0 )
    sub_5AEB60((float *)this);
}



// 登场/巨大化播报：KALKAZAK_01 + ENLARGE（87L）
// ------------------------------------------------------------
// 0x5AF040 sub_5AF040
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF040(int *this)
{
  int result; // eax
  int v3; // eax
  unsigned int v4; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // edi
  uint32_t *v12; // eax
  float v13; // [esp+4h] [ebp-14h]
  int i; // [esp+Ch] [ebp-Ch]
  float v15; // [esp+Ch] [ebp-Ch]
  int v16; // [esp+10h] [ebp-8h]
  float v17; // [esp+10h] [ebp-8h]
  int v18; // [esp+14h] [ebp-4h]

  result = 16;
  v16 = 0;
  for ( i = 16; i < 32; i += 4 )
  {
    v3 = *(uint32_t *)(result + dword_8F850C);
    v4 = 0;
    if ( v3 != 0 )
      v5 = *(uint32_t *)(v3 + 196);
    else
      v5 = 0;
    if ( v5 != 0 )
    {
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 700))(v5);
      v7 = *(uint32_t *)(v6 + 4);
      v18 = v7 != 0 ? (*(uint32_t *)(v6 + 8) - v7) >> 2 : 0;
      if ( v18 > 0 )
      {
        do
        {
          v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 700))(v5);
          v9 = *(uint32_t *)(v8 + 4);
          if ( v9 != 0 && v4 < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
            v10 = *(uint32_t *)(v9 + 4 * v4);
          else
            v10 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 92))(v10) != 0 )
            ++v16;
          ++v4;
        }
        while ( (int)v4 < v18 );
      }
    }
    result = i + 4;
  }
  v11 = v16;
  if ( *(this + 2164) < v16 )
  {
    result = *(this + 2163);
    if ( result < 5 )
    {
      v17 = (double)(10 * result) * 0.0099999998 + 1.0;
      v15 = (double)(10 * result + 10) * 0.0099999998 + 1.0;
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 688))(this, LODWORD(v17));
      sub_4EB4B0(v13);
      (*(void (/*thiscall*/ **)(int *))(*this + 688))(this);
      sub_4EB2C0(v15);
      ++*(this + 2163);
      v12 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
      sub_5AE850(this, *v12 + 1);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "KALKAZAK_01", -1, 0, 0);
      result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "ENLARGE",
                 -1,
                 0,
                 0);
    }
  }
  *(this + 2164) = v11;
  return result;
}



// 主状态门（this+200/8616/8617）
// ------------------------------------------------------------
// 0x5AF1C0 sub_5AF1C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF1C0(uint32_t *this, int a2, int a3)
{
  int v4; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1550) + 8));
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  sub_4926A0(v4);
  sub_5AECA0(this);
  *((uint8_t *)this + 8616) = 1;
  *((uint8_t *)this + 8617) = 0;
  *(this + 2156) = a2;
  return a2;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF210 sub_5AF210
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF210(int *this)
{
  sub_594370(this);
  return sub_5AF040(this);
}



// 僵尸语音装载：ZOMBIE_FIND/DMG/DIE/ATK 四件套（sub_4015C0, this+8616 相位）
// ------------------------------------------------------------
// 0x5AF220 sub_5AF220
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_5AF220(uint32_t *this)
{
  int v2; // edi
  uint32_t *v3; // eax
  uint64_t result; // rax
  float v5; // [esp+Ch] [ebp-20h]
  float v6; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+24h] [ebp-8h]
  int v8; // [esp+28h] [ebp-4h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("ZOMBIE_FIND", 0xBu);
  sub_4015C0("ZOMBIE_DMG", 0xAu);
  sub_4015C0("ZOMBIE_DIE", 0xAu);
  sub_4015C0("ZOMBIE_ATK", 0xAu);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 2);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v2 = *(this + 1821) - *(this + 1820);
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v6 = (float)v8;
  v5 = (float)v7;
  result = (uint64_t)sub_4049C0(v5, v6, *v3 - *(this + 1820), v2);
  *(this + 2157) = result;
  *((uint8_t *)this + 8616) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AF310 sub_5AF310
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF310(uint32_t *this)
{
  int result; // eax
  int v3; // esi
  int v4; // [esp+8h] [ebp-4h] BYREF

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v4);
    if ( (uint16_t)v3 == 14 )
      sub_5AF1C0(this, v4, 14);
    return v3;
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5AF360 sub_5AF360
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF360(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // edx
  void *v8[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  v5 = a2;
  if ( *(this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 1
    && (uint8_t)a4 == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 40))(v5, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 948))(v5) != 0
    && *(this + 154) != 14 )
  {
    memset(&v8[1], 0, 12);
    v6 = *(uint32_t *)v5;
    v9 = 0;
    a2 = (*(int (/*thiscall*/ **)(int))(v6 + 48))(v5);
    sub_431230((int)v8, &a2);
    a2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 52))(v5);
    sub_431230((int)v8, &a2);
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, v8, 0, 0);
    v9 = -1;
    sub_5E5260(v8);
  }
  return sub_4DB480(v5, a3, a4);
}



// 参数打包 AI（89L sub_431230）
// ------------------------------------------------------------
// 0x5AF460 sub_5AF460
// ------------------------------------------------------------
void /*usercall*/ sub_5AF460(int *a1@<ecx>, int a2@<ebx>)
{
  int v3; // ecx
  int v4; // edi
  int v5; // edx
  int v6; // eax
  int v7; // eax
  char v8; // al
  int v9; // ecx
  int v10; // edi
  int v11; // eax
  int v12; // eax
  char v13[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v15; // [esp+10h] [ebp-18h]
  int v16; // [esp+14h] [ebp-14h]
  int v17; // [esp+18h] [ebp-10h] BYREF
  int v18; // [esp+24h] [ebp-4h]

  v3 = a1[2150];
  if ( v3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v3 + 604))(v3, 1, a2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)a1[2150] + 612))(a1[2150], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)a1[2150] + 136))(
           a1[2150],
           a1[2160],
           a1[2161],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a1[2150] + 112))(a1[2150], a1[2160], a1[2161], a1[2162]);
    }
    else
    {
      v4 = a1[2150];
      v5 = *(uint32_t *)v4;
      v17 = v4;
      v17 = *a1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(v4, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v4 + 120))(v4, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(v17 + 140))(a1, a1 + 2160, a1 + 2161, v7);
      v9 = a1[2150];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 112))(v9, a1[2160], a1[2161], a1[2162]);
      }
      else
      {
        v10 = *(uint32_t *)v9;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 124))(a1, a1[2162]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 120))(a1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(a1[2150], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a1[2150] + 308))(a1[2150]) != 0 )
    {
      Block = nullptr;
      v15 = 0;
      v16 = 0;
      v18 = 0;
      v17 = 4;
      sub_431230((int)v13, &v17);
      v17 = 0;
      sub_431230((int)v13, &v17);
      v17 = 1;
      sub_431230((int)v13, &v17);
      v17 = 200;
      sub_431230((int)v13, &v17);
      v17 = 200;
      sub_431230((int)v13, &v17);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)a1[2150] + 560))(a1[2150], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a1[2150] + 564))(a1[2150]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1[2150] + 848))(a1[2150], 0);
    a1[2150] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF660 sub_5AF660
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF660(uint32_t *this, int a2, float *a3, int a4)
{
  int v5; // ebx
  int v6; // eax
  int v8; // [esp-10h] [ebp-1Ch]

  v5 = sub_5AF360(this, a2, (int)a3, a4);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 25 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this);
    if ( (*(uint8_t *)(v6 + 16) != 0 || *(float *)v6 > 0.0) && (uint8_t)a4 == 0 )
    {
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
      sub_4E4A50(this, 30320, 0, (uint64_t)*a3, (uint64_t)a3[1], (uint64_t)a3[2], v8, 0, 0, 0);
    }
  }
  return v5;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF710 sub_5AF710
// ------------------------------------------------------------
int /*userpurge*/ sub_5AF710@<eax>(int *a1@<ecx>, int a2@<ebx>, int *a3)
{
  if ( a3 == (int *)a1[2150] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*a1 + 840))(a1) == 14 )
      sub_5AF460(a1, a2);
    a1[2150] = 0;
  }
  if ( a3 == a1 && a1[2150] != 0 )
  {
    sub_5AF460(a1, a2);
    a1[2150] = 0;
  }
  return sub_4D9170(a3);
}



// AI 相位辅助（102L）
// ------------------------------------------------------------
// 0x5AF770 sub_5AF770
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF770(int *this, int ArgList, int a3, int a4, int a5)
{
  int v5; // ebx
  int v7; // eax
  int v8; // edi
  BOOL v9; // edi
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // [esp+Ch] [ebp-4h]

  v5 = ArgList;
  v7 = *(this + 1639);
  if ( v7 != 8 )
  {
    if ( v7 == 14 )
      sub_5AF460(this, ArgList);
LABEL_7:
    if ( ArgList != 8 )
      goto LABEL_10;
    goto LABEL_8;
  }
  if ( sub_41A5E0((unsigned int)(this + 1757)) != 2 )
    goto LABEL_7;
  if ( ArgList != 8 )
  {
    sub_5AEA70(this);
    goto LABEL_7;
  }
LABEL_8:
  if ( *(this + 1813) != 0 )
  {
    v8 = *(this + 1813);
    v22 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v9 = v22 < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 120))(v8);
    (*(void (/*thiscall*/ **)(int *, BOOL))(*this + 148))(this, v9);
    (*(void (/*thiscall*/ **)(int *, BOOL))(*this + 144))(this, v9);
  }
LABEL_10:
  switch ( ArgList )
  {
    case 5:
      sub_4DB200(24, 2);
      break;
    case 14:
      sub_5AEDE0(this, a3);
      break;
    case 15:
      v10 = *this;
      v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
      v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11);
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v10 + 136))(this, v12) == 0
        || (v13 = *this,
            v14 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this),
            (*(uint8_t (/*thiscall*/ **)(int *, int))(v13 + 132))(this, v14) == 0) )
      {
        v15 = *(this + 2150);
        if ( v15 != 0 )
        {
          v16 = *this;
          v17 = *(this + 2150);
          v18 = (*(int (**)(void))(*(uint32_t *)v15 + 128))();
          v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 124))(v17, v18);
          v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 120))(v17, v19);
          (*(void (/*thiscall*/ **)(int *, int))(v16 + 112))(this, v20);
          v5 = ArgList;
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
      break;
    default:
      break;
  }
  result = sub_4E33D0(v5, *(float *)&a3, a4, a5);
  if ( v5 == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 2 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
        return sub_5AE410(this, 14);
    }
  }
  return result;
}



// 子类扩展字段复位（this+8600..8636）
// ------------------------------------------------------------
// 0x5AF910 sub_5AF910
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF910(int this)
{
  *(uint8_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8601) = 0;
  *(uint8_t *)(this + 8614) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint16_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8636) = 0;
  *(uint8_t *)(this + 8612) = 0;
  *(uint8_t *)(this + 8613) = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AF950 sub_5AF950
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF950(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int v4; // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2151);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = *(this + 2154);
  *(this + 2151) = 0;
  if ( v4 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v4 + 84))(v4, 0);
    *(this + 2154) = 0;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AF990 sub_5AF990
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF990(uint32_t *this, uint32_t *a2)
{
  int result; // eax

  sub_4D9170(a2);
  if ( this == a2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);
  }
  result = 0;
  if ( (uint32_t *)*(this + 2159) == a2 )
    *(this + 2159) = 0;
  if ( (uint32_t *)*(this + 2154) == a2 )
    *(this + 2154) = 0;
  return result;
}



// AI 字段访问（this+8600）
// ------------------------------------------------------------
// 0x5AFA00 sub_5AFA00
// ------------------------------------------------------------
int /*thiscall*/ sub_5AFA00(uint8_t *this, int *a2, int a3)
{
  int result; // eax

  result = sub_4DC390(a2, a3);
  if ( result != 3 && *(this + 8600) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3) + 12) == 1 )
    {
      *a2 = (uint64_t)((double)*a2 * 0.5);
      return 2;
    }
    else
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3) + 124) == 0 )
        *a2 = (uint64_t)((double)*a2 * 0.34999999);
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 348))(a3) + 124) == 1 )
        *a2 = (uint64_t)((double)*a2 * 0.25);
      return 2;
    }
  }
  return result;
}



// ============================================================
// 【分区 13】龙人静态桥接（0x5AFAB0-0x5B0000）
// 证据：DRAGONMAN_STATIC 播报 —— 龙人（Draconian）类在本区块的收尾函数，主体见 dragonman.cpp

// 静态播报：DRAGONMAN_STATIC（this+200/8601 门；龙人系首函数, 主体在 0x5B 区 dragonman.cpp）
// ------------------------------------------------------------
// 0x5AFAB0 sub_5AFAB0
// ------------------------------------------------------------
char /*thiscall*/ sub_5AFAB0(uint8_t *this)
{
  int v2; // eax

  v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint32_t *)(v2 + 148) == 1 )
  {
    LOBYTE(v2) = *(this + 8601);
    if ( (uint8_t)v2 == 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 11);
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                     this,
                     "DRAGONMAN_STATIC",
                     -1,
                     0,
                     0);
      *(this + 8601) = 1;
    }
  }
  return v2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AFB00 sub_5AFB00
// ------------------------------------------------------------
int /*thiscall*/ sub_5AFB00(void *this, int a2, int a3, int a4)
{
  int v5; // ebx
  int v6; // edi

  sub_4DB480(a2, a3, a4);
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 8
    || sub_41A5E0((unsigned int)this + 7028) != 1
    || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) == 0
    || (uint8_t)a4 != 0 )
  {
    return 0;
  }
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 736))(a2) / 3;
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 736))(a2) - v5;
  (*(void (/*thiscall*/ **)(int, int, uint32_t, void *))(*(uint32_t *)a2 + 728))(a2, v5, 0, this);
  if ( v6 != 0 )
    sub_4D5330(this, a2, a3, v6, v6, 1, 0, 0);
  return v6;
}


