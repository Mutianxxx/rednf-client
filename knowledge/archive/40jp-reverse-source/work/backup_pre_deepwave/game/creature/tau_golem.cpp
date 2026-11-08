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
uint32_t */*thiscall*/ sub_5A0060(int *this, uint32_t *uArg2, char *pszArg3, int *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 12;
  else
    v6 = 0;
  sub_59FDB0(this, pszArg3, 1u, Block);
  *uArg2 = *(this + 1) + 12 * v6;
  return uArg2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A00D0 sub_5A00D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A00D0(int this, int *Block)
{
  int fld_4; // edi
  unsigned int fld_8; // ecx
  int fld_82; // edi
  uint32_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 12;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 12 )
    return sub_5A0060((int *)this, &Block, *(char **)(this + 8), Block);
  fld_82 = *(uint32_t *)(this + 8);
  result = (uint32_t *)sub_623C10(fld_82, 1, Block);
  *(uint32_t *)(this + 8) = fld_82 + 12;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A0150 sub_5A0150
// ------------------------------------------------------------
int /*thiscall*/ sub_5A0150(char *this, int nArg2)
{
  char *pThis_3CC; // ecx
  int v3; // esi
  unsigned int v4; // edx
  int *nArg22; // eax
  int result; // eax

  pThis_3CC = this + 972;
  v3 = *((uint32_t *)pThis_3CC + 1);
  if ( v3 != 0 )
    v4 = (*((uint32_t *)pThis_3CC + 2) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*((uint32_t *)pThis_3CC + 3) - v3) >> 2 )
    return sub_45F8A0(*((void **)pThis_3CC + 2), 1, (int)&nArg2);
  nArg22 = *((int **)pThis_3CC + 2);
  *nArg22 = nArg2;
  result = (int)(nArg22 + 1);
  *((uint32_t *)pThis_3CC + 2) = result;
  return result;
}



// RTTI cast 目标解算 AI（86L；this+8624 相位）
// ------------------------------------------------------------
// 0x5A01B0 sub_5A01B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A01B0(uint8_t *this)
{
  unsigned int i; // ebx
  int pThis_1D; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj3; // ecx
  int pThis_1D2; // ecx
  int v9; // edx
  int v10; // eax
  int pObj2; // eax
  char *pObj; // esi
  int v13; // ebx
  int v14; // ebx
  int v15; // ebx
  int v16; // ebx
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  int pThis_78; // eax
  unsigned int v21; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    pThis_1D = *((uint32_t *)this + 29);
    v4 = *(uint32_t *)(pThis_1D + 8);
    v21 = i;
    result = v4 != 0 ? (*(uint32_t *)(pThis_1D + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(pThis_1D + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(pThis_1D + 12) - v6) >> 2 )
      pObj3 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 33) != 0 )
    {
      pThis_1D2 = *((uint32_t *)this + 29);
      v9 = *(uint32_t *)(pThis_1D2 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(pThis_1D2 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      pObj2 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNChandelier `RTTI Type Descriptor', 0);
      pObj = (char *)pObj2;
      if ( pObj2 != 0 )
      {
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) - 55;
        if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) >= v13 )
        {
          v14 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 120))(pObj) + 55;
          if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) <= v14 )
          {
            v15 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 124))(pObj);
            if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this) == v15 )
            {
              v16 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 128))(pObj);
              if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this) >= v16 )
              {
                v17 = *(uint32_t *)this;
                v18 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 128))(pObj);
                v19 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)pObj + 124))(pObj, v18 + 10);
                pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, v19 + 1);
                (*(void (/*thiscall*/ **)(uint8_t *, int))(v17 + 112))(this, pThis_78);
                result = sub_5A0150(pObj, (int)this);
                *((uint32_t *)this + 2158) = pObj;
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
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // eax
  uint64_t v11; // rax
  int fld_e2172; // eax
  unsigned int fld_e2173; // edx
  bool result; // al
  int Block[4]; // [esp+Ch] [ebp-10h] BYREF

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
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
  fld_e2172 = *(this + 2172);
  result = false;
  if ( fld_e2172 != 0 )
  {
    fld_e2173 = (int)((uint64_t)(715827883LL * (*(this + 2173) - fld_e2172)) >> 32) >> 1;
    Block[3] = (*(this + 2173) - fld_e2172) / 12;
    if ( fld_e2173 + (fld_e2173 >> 31) != 0 )
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
int /*thiscall*/ sub_5A0420(int this, int ArgList, float fArg3, int nArg4, int nArg5)  // 【为 vt+560 setState 形拦截（this+6556 态 8 门）】
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
    && **(uint32_t **)(LODWORD(fArg3) + 4) == 2
    && !sub_5A0300((uint32_t *)this) )
  {
    **(uint32_t **)(LODWORD(fArg3) + 4) = 0;
  }
  sub_59F040(this, ArgList, fArg3, nArg4, nArg5);
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
  char *pMem; // eax
  char *v3; // eax
  int pObj; // eax
  char *pMem2; // eax
  char *v6; // eax
  int pObj2; // eax
  char *pMem3; // eax
  char *v9; // eax
  int pObj4; // eax
  char *pMem4; // eax
  char *v12; // eax
  int pObj3; // eax
  char *pMem5; // eax
  char *v15; // eax
  int pObj5; // eax
  char *pMem6; // eax
  char *v18; // eax
  int pObj6; // eax
  int fld_e1821; // edi
  uint32_t *v21; // eax
  uint64_t result; // rax
  float v23; // [esp+3Ch] [ebp-2Ch]
  float v24; // [esp+40h] [ebp-28h]
  void *Block; // [esp+54h] [ebp-14h]
  int v26; // [esp+58h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/acc3.equ", 0);
  else
    v3 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/acc4.equ", 0);
  else
    v6 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/Hcc2.equ", 0);
  else
    v9 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/gcc1-3.equ", 0);
  else
    v12 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v15 = sub_4BA9E0(pMem5, "Monster/Goblin/tcc1.equ", 0);
  else
    v15 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);
  pMem6 = (char *)operator new(0x544u);
  if ( pMem6 != nullptr )
    v18 = sub_4BA9E0(pMem6, "Monster/Goblin/bcc1.equ", 0);
  else
    v18 = nullptr;
  pObj6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);
  if ( pObj6 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 4))(pObj6, 1);
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v21 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v24 = (float)v26;
  v23 = (float)(int)Block;
  result = (uint64_t)sub_4049C0(v23, v24, *v21 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
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
int /*usercall*/ sub_5A0780@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  char *pMem; // eax
  char *v4; // eax
  int pObj; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj3; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj2; // eax
  char *pMem4; // eax
  char *v13; // eax
  int pObj4; // eax
  char *pMem5; // eax
  char *v16; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Goblin/SkyCastle/BombKagel/Face.equ", 0);
  else
    v4 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, v4, nArg2);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/Goblin/SkyCastle/BombKagel/hair.equ", 0);
  else
    v7 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v7);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v10 = sub_4BA9E0(pMem3, "Monster/Goblin/SkyCastle/BombKagel/pants.equ", 0);
  else
    v10 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v10);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v13 = sub_4BA9E0(pMem4, "Monster/Goblin/SkyCastle/BombKagel/wrist.equ", 0);
  else
    v13 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v13);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v16 = sub_4BA9E0(pMem5, "Monster/Goblin/SkyCastle/BombKagel/belt.equ", 0);
  else
    v16 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v16);
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  pArg1[1666] = 0;
  return result;
}



// 天空之城·手里剑加格尔装载：Monster/Goblin/SkyCastle/SurikenKagel/ 五件套
// ------------------------------------------------------------
// 0x5A0930 sub_5A0930
// ------------------------------------------------------------
int /*usercall*/ sub_5A0930@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  char *pMem; // eax
  char *v4; // eax
  int pObj; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj3; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj2; // eax
  char *pMem4; // eax
  char *v13; // eax
  int pObj4; // eax
  char *pMem5; // eax
  char *v16; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Goblin/SkyCastle/SurikenKagel/Face.equ", 0);
  else
    v4 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, v4, nArg2);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/Goblin/SkyCastle/SurikenKagel/hair.equ", 0);
  else
    v7 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v7);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v10 = sub_4BA9E0(pMem3, "Monster/Goblin/SkyCastle/SurikenKagel/pants.equ", 0);
  else
    v10 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v10);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v13 = sub_4BA9E0(pMem4, "Monster/Goblin/SkyCastle/SurikenKagel/wrist.equ", 0);
  else
    v13 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v13);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v16 = sub_4BA9E0(pMem5, "Monster/Goblin/SkyCastle/SurikenKagel/belt.equ", 0);
  else
    v16 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v16);
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  pArg1[1666] = 0;
  return result;
}



// 天空之城·靶眼装载：Monster/Goblin/SkyCastle/BullsEye/ 五件套 +
//   PassiveObject/Common/Particle/RedRock.ptl 落石粒子（86L）
// ------------------------------------------------------------
// 0x5A0AE0 sub_5A0AE0
// ------------------------------------------------------------
uint32_t */*usercall*/ sub_5A0AE0@<eax>(int pArg1@<ecx>, int nArg2@<edi>)
{
  char *pMem; // eax
  char *v4; // eax
  int pObj2; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj4; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj3; // eax
  char *pMem4; // eax
  char *v13; // eax
  int pObj5; // eax
  char *pMem5; // eax
  char *v16; // eax
  int pObj; // eax
  uint32_t *result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Goblin/SkyCastle/BullsEye/Face.equ", 0);
  else
    v4 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)pArg1 + 784))(pArg1, v4, nArg2);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/Goblin/SkyCastle/BullsEye/hair.equ", 0);
  else
    v7 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v7);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v10 = sub_4BA9E0(pMem3, "Monster/Goblin/SkyCastle/BullsEye/pants.equ", 0);
  else
    v10 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v10);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v13 = sub_4BA9E0(pMem4, "Monster/Goblin/SkyCastle/BullsEye/wrist.equ", 0);
  else
    v13 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v13);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v16 = sub_4BA9E0(pMem5, "Monster/Goblin/SkyCastle/BullsEye/belt.equ", 0);
  else
    v16 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v16);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  *(uint32_t *)(pArg1 + 8672) = -1;
  *(uint32_t *)(pArg1 + 6664) = 0;
  *(uint8_t *)(pArg1 + 8676) = 0;
  *(uint32_t *)(pArg1 + 8680) = 0;
  if ( *(uint32_t *)(pArg1 + 8688) != 0 )
    j__free(*(void **)(pArg1 + 8688));
  *(uint32_t *)(pArg1 + 8688) = 0;
  *(uint32_t *)(pArg1 + 8692) = 0;
  *(uint32_t *)(pArg1 + 8696) = 0;
  result = operator new(0x12Cu);
  if ( result != nullptr )
  {
    result = sub_428F30(result, (int)"PassiveObject/Common/Particle/RedRock.ptl", 0);
    *(uint32_t *)(pArg1 + 8704) = result;
  }
  else
  {
    *(uint32_t *)(pArg1 + 8704) = 0;
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
  int fld_e2155; // edi
  int v4; // ebx
  int fld_e2154; // eax
  int fld_e21542; // eax
  int result; // eax
  int fld_e2157; // ecx
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
      fld_e2155 = *(this + 2155) * (*(this + 2157) + 1);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 )
        fld_e2155 = -fld_e2155;
      v4 = *this;
      fld_e2154 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 120))(
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
      fld_e21542 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*this + 120))(this, *(this + 2154), 0, fld_e2154 - fld_e2155);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 584))(this, fld_e21542 - fld_e2155);
    }
    *((uint8_t *)this + 8624) = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  fld_e2157 = *(this + 2157);
  if ( *(uint32_t *)(result + 148) == v9[fld_e2157] + 1 )
  {
    *((uint8_t *)this + 8624) = 0;
    *(this + 2157) = fld_e2157 + 1;
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
  int fld_e2157; // ecx
  int fld_e2158; // edi
  uint64_t fld_e21572; // rax
  int result; // eax
  int fld_e21573; // ecx
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
      fld_e2157 = *(this + 2157);
      v12 = v3;
      fld_e2158 = (uint64_t)((double)v3 + (double)v10[2 * fld_e2157 - 1] * ((double)(int)*(this + 2158) * 0.0099999998));
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      fld_e21572 = (uint64_t)((double)v12
                            + (double)(int)v10[2 * *(this + 2157)] * ((double)(int)*(this + 2158) * 0.0099999998));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 584))(
        this,
        fld_e2158,
        fld_e21572,
        0,
        fld_e2158,
        fld_e21572,
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
  fld_e21573 = *(this + 2157);
  if ( *(uint32_t *)(result + 148) == v11[fld_e21573] + 1 )
  {
    *((uint8_t *)this + 8624) = 0;
    *(this + 2157) = fld_e21573 + 1;
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
  int nRand; // eax
  int v4; // et2
  int v5; // edi
  int fld_e2153; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int fld_e21532; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int fld_e21533; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // edi
  int fld_e21534; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // ebx
  int fld_e1813; // edi
  int fld_e21535; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 && *(this + 1943) == 3 )
  {
    nRand = rand();
    v4 = nRand % 100;
    result = nRand / 100;
    if ( v4 < 75 )
    {
      if ( sub_4E7F30(this, 100, 60, 0) != 0 )
      {
        v5 = *this;
        fld_e2153 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
               this,
               30070,
               *(this + 2153),
               0,
               4,
               *(this + 1908) != 0 ? 100 : 130,
               1,
               0,
               0);
        v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e2153);
        v8 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v7 - 50);
        v9 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8);
        (*(void (/*thiscall*/ **)(int *, int))(v5 + 584))(this, v9 - 50);
        v10 = *this;
        fld_e21532 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
                this,
                30070,
                *(this + 2153),
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,
                1,
                0,
                0);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e21532);
        v13 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v12 + 50);
        v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);
        (*(void (/*thiscall*/ **)(int *, int))(v10 + 584))(this, v14 + 50);
        v15 = *this;
        fld_e21533 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
                this,
                30070,
                *(this + 2153),
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,
                1,
                0,
                0);
        v17 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e21533 - 50);
        v18 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*this + 124))(this, 0, v17);
        v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v18 - 50);
        (*(void (/*thiscall*/ **)(int *, int))(v15 + 584))(this, v19);
        v20 = *this;
        fld_e21534 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
                this,
                30070,
                *(this + 2153),
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,
                1,
                0,
                0);
        v22 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, fld_e21534 + 50);
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
          fld_e1813 = *(this + 1813);
          fld_e21535 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)result + 124))(
                  result,
                  30070,
                  *(this + 2153),
                  0,
                  4,
                  *(this + 1908) != 0 ? 100 : 130,
                  1,
                  0,
                  0);
          v28 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, fld_e21535);
          v29 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 0, v28);
          v30 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v29);
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
char /*thiscall*/ sub_5A12C0(int this, int nArg2)
{
  char result; // al

  result = sub_4DBC20(nArg2);
  if ( nArg2 == 6 )
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
void /*thiscall*/ sub_5A1300(int *this, int nArg2)
{
  int pObj3; // ebx
  int pObj2; // esi
  int v6; // eax
  int v7; // eax
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
    v6 = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(*this + 152))(this, 100, 1, 0, 0);
    v7 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj3 + 124))(pObj3, 30070, 0, 0, v6);
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 120))(pObj4, v7);
    v9 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, 0, v8);
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v9);
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
  int nRand; // eax
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
        nRand = rand();
        sub_4DB200(24, v9[nRand % 3]);
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
  int fld_e29; // ecx
  int v5; // edx
  int v6; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj3; // ecx
  int fld_e293; // ecx
  int v12; // edx
  int pObj2; // esi
  int v14; // ebx
  int nRand2; // eax
  int v16; // ebx
  int fld_e2153; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int nRand; // [esp+4h] [ebp-Ch]
  int v22; // [esp+8h] [ebp-8h]
  unsigned int v23; // [esp+Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);
      v5 = *(uint32_t *)(fld_e29 + 8);
      v23 = i;
      result = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(fld_e29 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
        pObj = *(uint32_t *)(v6 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) == 0 )
      {
        fld_e292 = *(this + 29);
        v9 = *(uint32_t *)(fld_e292 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
          pObj3 = *(uint32_t *)(v9 + 4 * i);
        else
          pObj3 = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 545) == 0 )
          continue;
      }
      fld_e293 = *(this + 29);
      v12 = *(uint32_t *)(fld_e293 + 8);
      if ( v12 != 0 && i < (*(uint32_t *)(fld_e293 + 12) - v12) >> 2 )
        pObj2 = *(uint32_t *)(v12 + 4 * i);
      else
        pObj2 = 0;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);
      if ( v14 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0) <= 300
        && ((*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
         || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 940))(pObj2) == 0)
        && rand() % 100 >= 50 )
      {
        nRand = rand() % 50 - 25;
        nRand2 = rand();
        v16 = *this;
        v22 = nRand2 % 50 - 25;
        fld_e2153 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 124))(
                pObj2,
                30070,
                *(this + 2153),
                0,
                4,
                *(this + 1908) != 0 ? 100 : 130,
                1,
                0,
                0);
        v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v22 + fld_e2153);
        v19 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj2 + 124))(pObj2, 0, nRand + v18);
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v22 + v19);
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v16 + 584))(this, nRand + v20);
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
int /*usercall*/ sub_5A1720@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int result; // eax
  int nRand; // eax
  int v5; // et2

  sub_4DE3E0();
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v5 = nRand % 100;
    result = nRand / 100;
    if ( v5 < 30 )
      return sub_59B130(pArg1, nArg2, (int)pArg1, pArg1[1814]);
  }
  return result;
}



// 参数打包 AI（sub_431230, 53L）
// ------------------------------------------------------------
// 0x5A1760 sub_5A1760
// ------------------------------------------------------------
void /*thiscall*/ sub_5A1760(int **this)
{
  int fld_e1813; // ebx
  int nRand; // eax
  int *fld_e18132; // ecx
  int v5; // eax
  int v6; // edx
  int *v7; // ebx
  int v8; // eax
  uint8_t v10[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v12; // [esp+Ch] [ebp-1Ch]
  int v13; // [esp+10h] [ebp-18h]
  int nRand2; // [esp+14h] [ebp-14h] BYREF
  uint32_t v15[4]; // [esp+18h] [ebp-10h] BYREF

  if ( ((uint8_t (/*thiscall*/ *)(int **))(*this)[77])(this) != 0 && *(this + 1813) != nullptr )
  {
    v15[0] = 100;
    do
    {
      fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1813) + 124))(*(this + 1813));
      nRand = rand();
      fld_e18132 = *(this + 1813);
      v5 = fld_e1813 + nRand % 100 - 50;
      v6 = *fld_e18132;
      v7 = *this;
      nRand2 = v5;
      v8 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(v6 + 120))(fld_e18132, v5, 0);
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
    sub_431230((int)v10, &nRand2);
    nRand2 = rand() % 50 + 25;
    sub_431230((int)v10, &nRand2);
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
  int fld_e91; // edx
  char *v5; // eax
  char *v6; // edi
  int v7; // edi
  int v8; // ebx
  int nRand; // eax
  int v10; // ebx
  int nRand2; // eax
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
          LOBYTE(fld_e91) = (uint8_t)this + 108;
        else
          fld_e91 = *(this + 91);
        v3 = sub_431920(fld_e91, (char)"Animation_LightningKinol/DieThunderbolt.ani", 1);
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
      nRand = rand();
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v8 + nRand % 30 - 15);
      nRand2 = rand();
      result = (*(int (/*thiscall*/ **)(char *, int))(v7 + 112))(v13, v10 + nRand2 % 70 - 35);
    }
  }
  return result;
}



// 蓄雷 AI：BEFORE_THUNDER（52L；8624 相位）
// ------------------------------------------------------------
// 0x5A1BF0 sub_5A1BF0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A1BF0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
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
    v7 = *(uint32_t **)(LODWORD(fArg3) + 4);
    if ( *v7 == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BEFORE_THUNDER", -1, 0, 0);
      *(this + 2154) = *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4);
      *(this + 2155) = *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 8);
    }
    else if ( *v7 == 2 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BEFORE_THUNDER", -1, 0, 0);
      *(this + 2158) = *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4);
    }
  }
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
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
  char *pMem; // eax
  char *v3; // eax
  int pThis_310; // eax
  char *pMem2; // eax
  char *v6; // eax
  int pThis_3102; // eax
  char *pMem3; // eax
  char *v9; // eax
  int pThis_3103; // eax
  char *pMem4; // eax
  char *v12; // eax
  int pThis_3104; // eax
  uint32_t *pThis_2A0; // eax
  double pThis_71C; // st7
  int v16; // eax
  int pThis_71D; // edi
  uint32_t *pThis_2A02; // eax
  uint64_t pThis_71C2; // rax
  int pThis_1802; // eax
  int pThis_71D2; // edi
  uint32_t *pThis_2A03; // eax
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
  int pThis_180; // [esp+60h] [ebp-10h]
  int v34; // [esp+60h] [ebp-10h]
  int v35; // [esp+60h] [ebp-10h]

  *((uint32_t *)this + 1698) = 2;
  *((uint32_t *)this + 1699) = 2;
  *((uint32_t *)this + 1700) = 2;
  *((uint32_t *)this + 1701) = 3;
  *((uint32_t *)this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/hcc1.equ", 0);
  else
    v3 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/Lkinolpants.equ", 0);
  else
    v6 = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/Weapon03-2.equ", 0);
  else
    v9 = nullptr;
  pThis_3103 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v9);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/acc1.equ", 0);
  else
    v12 = nullptr;
  pThis_3104 = (*(int (/*thiscall*/ **)(float *, char *))(*(uint32_t *)this + 784))(this, v12);
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);
  Block = (void *)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  pThis_180 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  pThis_2A0 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v27 = (float)pThis_180;
  v24 = (float)(int)Block;
  pThis_71C = sub_4049C0(v24, v27, *pThis_2A0 - *((uint32_t *)this + 1820), *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820));  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v16 = *(uint32_t *)this;
  *(this + 106) = pThis_71C;
  v34 = (*(int (/*thiscall*/ **)(float *, int))(v16 + 384))(this, 2);
  Blocka = (void *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  pThis_71D = *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820);
  pThis_2A02 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v28 = (float)(int)Blocka;
  v25 = (float)v34;
  pThis_71C2 = (uint64_t)sub_4049C0(v25, v28, *pThis_2A02 - *((uint32_t *)this + 1820), pThis_71D);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *((float *)&pThis_71C2 + 1) = *this;
  *((uint32_t *)this + 109) = pThis_71C2;
  v35 = (*(int (/*thiscall*/ **)(float *, int))(HIDWORD(pThis_71C2) + 384))(this, 4);
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);
  pThis_71D2 = *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820);
  Blockb = (void *)pThis_1802;
  pThis_2A03 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v29 = (float)(int)Blockb;
  v26 = (float)v35;
  result = (uint64_t)sub_4049C0(v26, v29, *pThis_2A03 - *((uint32_t *)this + 1820), pThis_71D2);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
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
  int (/*thiscall*/ ***fld_e2154)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2155)(uint32_t, int); // ecx

  fld_e2154 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2154);
  if ( fld_e2154 != nullptr )
    result = (**fld_e2154)(fld_e2154, 1);
  fld_e2155 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2155);
  *(this + 2154) = 0;
  if ( fld_e2155 != nullptr )
    result = (**fld_e2155)(fld_e2155, 1);
  *(this + 2155) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A2100 sub_5A2100
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2100(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int nRand; // eax
  int v8; // et2

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 5 )
  {
    nRand = rand();
    v8 = nRand % 100;
    result = nRand / 100;
    if ( v8 < 50 )
      return sub_64BDF0(this, *(this + 1814));
  }
  return result;
}



// mob 引用：Goblin/CowardGoblin.mob（胆小鬼哥布林数据文件, 34L）
// ------------------------------------------------------------
// 0x5A2150 sub_5A2150
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2150(int *this, int nArg2)
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v8; // [esp+Ch] [ebp-4h]
  bool v9; // [esp+1Bh] [ebp+Bh]

  v9 = *(uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3) > nArg2;
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);
  (*(void (/*thiscall*/ **)(int *, int, const char *))(*this + 1024))(this, nArg2, "Goblin/CowardGoblin.mob");
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
int /*thiscall*/ sub_5A2200(int this, int nArg2, int nArg3)
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
  if ( nArg3 != 0 )
  {
    if ( nArg3 != 2 )
      return result;
    if ( nArg2 != 0 )
    {
      if ( nArg2 != 1 )
      {
        if ( nArg2 != 2 )
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
  if ( nArg2 == 0 )
  {
LABEL_6:
    *(uint32_t *)(this + 7596) = -100;
    return result;
  }
  if ( (unsigned int)(nArg2 - 1) <= 1 )
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
  int fld_e29; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v10; // edx
  uint32_t *v11; // edx
  uint32_t *v12; // ecx
  uint32_t *v13; // eax

  v1 = 0;
  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v5 = *(uint32_t *)(fld_e29 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;
    if ( (int)i >= v6 )
      break;
    v7 = *(uint32_t *)(fld_e29 + 8);
    if ( v7 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v7) >> 2 )
      pObj = *(uint32_t *)(v7 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
    {
      fld_e292 = *(this + 29);
      v10 = *(uint32_t *)(fld_e292 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v10) >> 2 )
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
void /*thiscall*/ sub_5A23C0(float *this, int nArg2)
{
  double fld_e2156; // st7
  int v4; // edx
  float fld_e21562; // ebx
  uint32_t *pThis_86D; // edi
  float fld_e21563; // [esp-Ch] [ebp-1Ch]
  uint32_t v8[3]; // [esp+4h] [ebp-Ch]
  int i; // [esp+18h] [ebp+8h]

  fld_e2156 = *(this + 2156);
  v8[0] = 1036831949;
  v8[1] = -1110651699;
  if ( fld_e2156 > 1.0 && *(this + 2156) < 1.5 )
  {
    v4 = *(uint32_t *)this;
    fld_e21562 = *(this + 2156);
    *(this + 2156) = *(float *)&v8[nArg2] + fld_e21562;
    *(float *)&v8[2] = fld_e21562;
    (*(void (/*thiscall*/ **)(float *))(v4 + 688))(this);
    sub_4EB4B0(fld_e21562);
    fld_e21563 = *(this + 2156);
    (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 688))(this);
    sub_4EB2C0(fld_e21563);
    pThis_86D = this + 2157;
    for ( i = 4; i != 0; --i )
    {
      if ( *pThis_86D != 0 )
      {
        sub_4EB6E0(fld_e21562);
        sub_4EB6A0(*(this + 2156));
      }
      ++pThis_86D;
    }
  }
}



// 强化状态：POWER_UP 播报（46L）
// ------------------------------------------------------------
// 0x5A2490 sub_5A2490
// ------------------------------------------------------------
void /*thiscall*/ sub_5A2490(int *this, int nArg2)
{
  int v3; // edi
  int v4; // eax
  int nRand; // eax
  int v6; // eax
  int fld_e2154; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0
    && (uint8_t)sub_4DAB60(19) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);
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
        nRand = rand() % 2;
        v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 64))(this, dword_9B9328[nRand]);
        sub_50EF20(v6, 0, -1);
        fld_e2154 = *(this + 2154);
        *(this + 2153) = 0;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2154 + 12))(fld_e2154, 0);
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
int /*thiscall*/ sub_5A2590(int *this, int nArg2)
{
  int v3; // edi
  int v4; // eax
  int nRand; // eax
  int v6; // eax
  int fld_e2155; // ecx
  unsigned int i; // edi
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edx
  int pObj; // ecx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  const char *v19; // eax
  int v21; // [esp-8h] [ebp-214h]
  int v22; // [esp-4h] [ebp-210h]
  char Buffer[512]; // [esp+8h] [ebp-204h] BYREF
  int dword_796E502; // [esp+208h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 724))(this) == 0
    && (uint8_t)sub_4DAB60(19) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);
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
      nRand = rand() % 2;
      v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 64))(this, dword_9B9330[nRand]);
      sub_50EF20(v6, 0, -1);
      fld_e2155 = *(this + 2155);
      *(this + 2153) = 1;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2155 + 12))(fld_e2155, 0);
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
          pObj = *(uint32_t *)(v14 + 4 * i);
        else
          pObj = 0;
        v22 = 529;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 40))(pObj) != 0 )
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
            return sub_4D9170(nArg2);
          }
        }
      }
    }
  }
  return sub_4D9170(nArg2);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A27A0 sub_5A27A0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A27A0(uint32_t *this)
{
  int fld_e2154; // edi
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
  fld_e2154 = *(uint32_t *)*(this + 2154);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e2154 + 40))(*(this + 2154));
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
  int fld_e2155; // edi
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
  fld_e2155 = *(uint32_t *)*(this + 2155);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  (*(void (/*thiscall*/ **)(uint32_t))(fld_e2155 + 40))(*(this + 2155));
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
  int fld_21A4; // eax

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
  fld_21A4 = *(uint32_t *)(this + 8612);
  if ( fld_21A4 != 0 )
  {
    if ( fld_21A4 == 1 )
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
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *v5; // edi
  char *pMem3; // eax
  char *v7; // edi
  uint32_t *pMem4; // eax
  uint32_t *v9; // eax
  uint32_t *pMem5; // eax
  uint32_t *v11; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/gcc1.equ", 0);
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  *(this + 2157) = v3;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v5 = sub_4BA9E0(pMem2, "Monster/Goblin/Weapon01.equ", 0);
  else
    v5 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v5);
  *(this + 2158) = v5;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v7 = sub_4BA9E0(pMem3, "Monster/Goblin/CwGobSantaBeard.equ", 0);
  else
    v7 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v7);
  *(this + 2159) = v7;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 570;
  pMem4 = operator new(0x12Cu);
  if ( pMem4 != nullptr )
    v9 = sub_428F30(pMem4, (int)"Common/CommonEffect/Particle/MonsterPowerUp.ptl", (int)this);
  else
    v9 = nullptr;
  *(this + 2154) = v9;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v9 + 112))(v9, this);
  pMem5 = operator new(0x12Cu);
  if ( pMem5 != nullptr )
    v11 = sub_428F30(pMem5, (int)"Common/CommonEffect/Particle/MonsterPowerDown.ptl", (int)this);
  else
    v11 = nullptr;
  *(this + 2155) = v11;
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *))(*v11 + 112))(v11, this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A2C50 sub_5A2C50
// ------------------------------------------------------------
int /*thiscall*/ sub_5A2C50(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v4; // edx

  sub_4D90A0(pArg2);
  if ( *pArg2 == 10 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
  result = *pArg2 - 11;
  if ( *pArg2 == 11 )
  {
    sub_4D84F0(0, 0);
    v4 = *this;
    *(this + 1813) = pArg2[3];
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
int /*thiscall*/ sub_5A2CD0(uint32_t *this, int nArg2, int nArg3)
{
  bool v4; // zf
  int result; // eax
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+Ch] [ebp+8h]

  if ( nArg2 != 0 )
  {
    if ( nArg2 <= 0 || nArg2 > 2 )
      goto LABEL_8;
    v4 = nArg3 == 0;
  }
  else
  {
    v4 = nArg3 == 2;
  }
  if ( v4 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.76923078;
LABEL_8:
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
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
int /*thiscall*/ sub_5A2D80(uint32_t *this, int nArg2, int nArg3)
{
  bool v4; // zf
  int result; // eax
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+Ch] [ebp+8h]

  if ( nArg2 != 0 )
  {
    if ( nArg2 <= 0 || nArg2 > 2 )
      goto LABEL_8;
    v4 = nArg3 == 0;
  }
  else
  {
    v4 = nArg3 == 2;
  }
  if ( v4 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 1.3;
LABEL_8:
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
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
  int nRand; // eax
  int v4; // et2
  int nRand2; // eax
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
      nRand = rand();
      v4 = nRand % 100;
      result = nRand / 100;
      if ( v4 < 10 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 5);
      break;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        nRand2 = rand();
        v6 = nRand2 % 100;
        result = nRand2 / 100;
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
  char *pMem; // eax
  char *v3; // edi
  char *v4; // ebx
  int pObj; // eax
  char *pMem2; // eax
  int pObj2; // eax
  int result; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Tau/Weapon01.equ", 0);
  else
    v4 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v4);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v3 = sub_4BA9E0(pMem2, "Monster/Tau/Horn01.equ", 0);
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
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
int /*thiscall*/ sub_5A30B0(uint8_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
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
int /*thiscall*/ sub_5A3110(int *this, uint32_t *pArg2)
{
  int result; // eax
  int v4; // edx

  result = sub_4D90A0(pArg2);
  if ( *pArg2 == 6 )
  {
    sub_4D84F0(0, 0);
    v4 = *this;
    *(this + 1813) = pArg2[3];
    (*(void (/*thiscall*/ **)(int *, int))(v4 + 1104))(this, 20);
    return sub_49C5F0(4, 0, 0, 500);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A3160 sub_5A3160
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3160(void (/*thiscall*/ ***this)(int, void *, uint32_t), int nArg2, int nArg3, int nArg4)
{
  int v5; // edi

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);
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
  int nRand; // eax
  int v4; // et2

  sub_4DA1D0();
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  if ( result == 0 )
  {
    nRand = rand();
    v4 = nRand % 100;
    result = nRand / 100;
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
char /*usercall*/ sub_5A3200@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
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

  sub_4E1780(pDwArg1);
  v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1);
  if ( v4 == 8 )
  {
    if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 2 )
    {
      LOBYTE(v4) = *((uint8_t *)pDwArg1 + 8608);
      if ( (uint8_t)v4 != 1 )
      {
        v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
        if ( *(uint32_t *)(v4 + 148) == 1 )
        {
          v5 = pDwArg1[29];
          v6 = *pDwArg1;
          *((uint8_t *)pDwArg1 + 8608) = 1;
          v7 = *(uint32_t **)(v5 + 132);
          v8 = (*(int (/*thiscall*/ **)(int *))(v6 + 200))(pDwArg1);
          v9 = sub_491C10(v8);
          LOBYTE(v4) = sub_424120(v7, 5, v9);
        }
      }
    }
    else
    {
      v4 = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
      if ( v4 == 0 )
      {
        LOBYTE(v4) = *((uint8_t *)pDwArg1 + 8608);
        if ( (uint8_t)v4 != 1 )
        {
          v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
          if ( *(uint32_t *)(v4 + 148) == 4 )
          {
            v10 = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 152))(pDwArg1, nArg3, nArg2) != 0 ? 110 : -110;
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
            {
              v15 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
              v14 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
              v11 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);
              sub_4E4A50(pDwArg1, 30022, 0, v10 + v11, v14, 0, v15, 0, 0, 0);
            }
            v12 = pDwArg1[29];
            *((uint8_t *)pDwArg1 + 8608) = 1;
            sub_424120(*(uint32_t **)(v12 + 132), 2, 500);
            LOBYTE(v4) = (*(int (/*thiscall*/ **)(int *, const char *, int))(*pDwArg1 + 212))(pDwArg1, "TAU_GROUND_HIT", -1);
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
int /*thiscall*/ sub_5A3350(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  bool v5; // zf
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )
      return result;
    result = nArg2;
    v5 = nArg2 == 0;
  }
  else
  {
    v6 = *this;
    *(this + 1899) = 0;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 858;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;
    sub_41A590(v7, v8, v9);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    result = nArg2;
    v5 = nArg2 == 1;
  }
  if ( v5 )
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.76923078;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A33E0 sub_5A33E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A33E0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  bool v5; // zf
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 != 2 )
      return result;
    result = nArg2;
    v5 = nArg2 == 0;
  }
  else
  {
    v6 = *this;
    *(this + 1899) = 30;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v6 + 672))(this, 0) + 858;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;
    sub_41A590(v7, v8, v9);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    result = nArg2;
    v5 = nArg2 == 1;
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
  char *pMem; // eax
  char *v3; // edi
  char *v4; // ebx
  int pObj; // eax
  char *pMem2; // eax
  int pObj3; // eax
  int v8; // eax
  void *pMem3; // eax
  int pObj2; // eax
  int result; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Tau/Hair-Beast.equ", 0);
  else
    v4 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v4);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v3 = sub_4BA9E0(pMem2, "Monster/Tau/Horn-Beast.equ", 0);
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  v8 = *this;
  *(this + 1830) = 30;
  *(this + 1839) = -30;
  *(this + 1831) = 300;
  (*(void (/*thiscall*/ **)(uint32_t *))(v8 + 688))(this);
  sub_4EB2C0(1.55);
  sub_4EB6A0(1.55);
  sub_4EB6A0(1.55);
  pMem3 = operator new(0x64u);
  if ( pMem3 != nullptr )
    pObj2 = sub_51A7D0(pMem3);
  else
    pObj2 = 0;
  *(this + 2151) = pObj2;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;
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
int /*thiscall*/ sub_5A36F0(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1639; // edi
  int result; // eax

  fld_e1639 = *(this + 1639);
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( fld_e1639 != 8 )
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
int /*thiscall*/ sub_5A37A0(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // eax
  unsigned int v5; // edi
  int v6; // edx
  int result; // eax
  int v8; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    if ( nArg3 == 2 )
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
  result = nArg2;
  if ( nArg2 == 0 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.76923078;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3850 sub_5A3850
// ------------------------------------------------------------
int /*thiscall*/ sub_5A3850(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // eax
  unsigned int v5; // edi
  int v6; // edx
  int result; // eax
  int v8; // [esp+10h] [ebp+Ch]

  if ( nArg3 != 0 )
  {
    if ( nArg3 == 2 )
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
  result = nArg2;
  if ( nArg2 == 0 )
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 1.3;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A3900 sub_5A3900
// ------------------------------------------------------------
char /*thiscall*/ sub_5A3900(int *this)
{
  int fld_e30; // ecx
  int fld_e1554; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && *(this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 1 )
  {
    fld_e30 = *(this + 30);
    if ( *(uint8_t *)(fld_e30 + 170) != 0 )
    {
      fld_e1554 = *(this + 1554);
      if ( fld_e30 == *(uint32_t *)(fld_e1554 + 4) )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(fld_e1554 + 4));
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
int /*thiscall*/ sub_5A3960(int *this, int nArg2, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // edi
  int v8; // eax
  int v9; // ebx
  int v10; // edi
  int v11; // eax

  result = sub_5A36F0(this, nArg2, fArg3, nArg4, nArg5);
  if ( nArg2 == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 2 )
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
  int pThis_6DD; // eax
  int v3; // eax

  sub_5A3900(this);
  pThis_6DD = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( pThis_6DD == 8 )
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
    if ( pThis_6DD == 2 )
    {
      LOBYTE(pThis_6DD) = *(uint8_t *)(*(this + 30) + 170);
      if ( (uint8_t)pThis_6DD != 0 )
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
        LOBYTE(pThis_6DD) = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                       this,
                       "ROCKMOUDE_01",
                       -1,
                       0,
                       0);
      }
    }
  }
  return pThis_6DD;
}



// 冲刺 AI：TAU_RUSH_LOOP 播报（74L；sub_431230 参数打包）
// ------------------------------------------------------------
// 0x5A3A70 sub_5A3A70
// ------------------------------------------------------------
void /*thiscall*/ sub_5A3A70(uint32_t *this, int nArg2)
{
  uint32_t *v2; // edi
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int nRand; // eax
  void *pBuf[7]; // [esp+8h] [ebp-1Ch] BYREF

  v2 = (uint32_t *)nArg2;
  sub_4D90A0(nArg2);
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
        nRand = rand();
        sub_49C5F0(11, 0, 0, nRand % 300 + 300);
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
        memset(&pBuf[1], 0, 12);
        pBuf[6] = nullptr;
        nArg2 = 1;
        sub_431230((int)pBuf, &nArg2);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
        sub_5E5260(pBuf);
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
  char *pMem; // eax
  int pObj2; // eax
  char *pMem2; // eax
  char *v5; // ebx
  int pObj; // eax
  int fld_e1821; // edi
  uint32_t *v8; // eax
  uint64_t fld_e1820; // rax
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
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v15 = sub_4BA9E0(pMem, "Monster/Tau/wrap02.equ", 0);
  else
    v15 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v5 = sub_4BA9E0(pMem2, "Monster/Tau/Horn02.equ", 0);
  else
    v5 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v5);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v8 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v12 = (float)v14;
  v11 = (float)(int)Block;
  fld_e1820 = (uint64_t)sub_4049C0(v11, v12, *v8 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1820) = *this;
  *(this + 2151) = fld_e1820;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(HIDWORD(fld_e1820) + 688))(this, 1064514355);
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
int /*thiscall*/ sub_5A3E70(uint8_t *this, int *pDwArg2, int nArg3)
{
  int result; // eax
  int v5; // ebx

  result = sub_4DC390(pDwArg2, nArg3);
  v5 = result;
  if ( result != 3 )
  {
    if ( *(this + 8604) != 0 )
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
    else if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this) <= 0 )
    {
      return v5;
    }
    else
    {
      *pDwArg2 = (uint64_t)((double)*pDwArg2 + (double)*pDwArg2);
      return 0;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A40F0 sub_5A40F0
// ------------------------------------------------------------
int /*usercall*/ sub_5A40F0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int pObj; // edi
  int nRand; // edx
  int result; // eax

  sub_4E1780(pArg1);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 15
    && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) != 0
    && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
  }
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
                result = pArg1[1909] != 0 ? 20 : 50;
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



// 指挥 AI：TAU_COMMAND（RTTI cast, 67L）
// ------------------------------------------------------------
// 0x5A4170 sub_5A4170
// ------------------------------------------------------------
int /*thiscall*/ sub_5A4170(uint32_t *this)
{
  unsigned int i; // esi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // ebx
  int v12; // eax
  unsigned int v13; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v13 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        pObj = *(uint32_t *)(v9 + 4 * i);
      else
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      {
        v12 = __RTDynamicCast(
                pObj,
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
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // ebx
  int v12; // eax
  unsigned int v13; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v13 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        pObj = *(uint32_t *)(v9 + 4 * i);
      else
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this) )
      {
        v12 = __RTDynamicCast(pObj, 0, &IRDActiveObject `RTTI Type Descriptor', &CNTauArmy `RTTI Type Descriptor', 0);
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
  uint32_t *pThis; // ebx
  int result; // eax
  unsigned int i; // edi
  int v4; // ecx
  int v5; // edx
  int v6; // edx
  int pObj; // ecx
  int v8; // ecx
  int v9; // edx
  uint32_t *v10; // esi
  int v11; // eax
  uint32_t *v12; // ecx
  uint32_t *v13; // eax
  int v14; // [esp+4h] [ebp-8h]

  pThis = this;
  result = *(this + 1814);
  if ( result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v4 = pThis[29];
      v5 = *(uint32_t *)(v4 + 8);
      result = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(v4 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(v4 + 12) - v6) >> 2 )
        pObj = *(uint32_t *)(v6 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
      {
        v8 = pThis[29];
        v9 = *(uint32_t *)(v8 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
          v10 = *(uint32_t **)(v9 + 4 * i);
        else
          v10 = nullptr;
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*v10 + 376))(v10);
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);
        pThis = this;
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
void /*userpurge*/ sub_5A4460(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, double fArg3@<st0>, int ArgList, int pArg5, int nArg6, int nArg7)
{
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // ebx
  int v11; // edi
  uint32_t *pMem; // eax
  int *v13; // eax
  int v14; // edx
  int v15; // ecx
  int nRand; // eax
  int v17; // [esp-10h] [ebp-28h]
  int v18; // [esp-Ch] [ebp-24h]
  int nArg22; // [esp-4h] [ebp-1Ch]
  int v20; // [esp+4h] [ebp-14h]
  void *Block; // [esp+8h] [ebp-10h]
  int v22; // [esp+14h] [ebp-4h]

  if ( pArg1[1639] == 14 && ArgList != 14 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 288))(pArg1) == 1 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*pArg1 + 284))(pArg1, 0, 0, 1, 2);
  switch ( ArgList )
  {
    case 5:
      fArg3 = sub_5A4360(pArg1);
      break;
    case 14:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 288))(pArg1) == 0
        || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 292))(pArg1) != -14803201 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int))(*pArg1 + 284))(pArg1, 1, -14803201, 0, 1);
      }
      break;
    case 15:
      v8 = pArg1[1554];
      *((uint8_t *)pArg1 + 8612) = 1;
      sub_4926A0(*(uint32_t *)(v8 + 12));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 12));
      v9 = *(uint32_t **)(pArg5 + 4);
      if ( *v9 != 0xFFFF )
      {
        nArg22 = nArg2;
        v10 = 0;
        do
        {
          v18 = v9[v10 + 1];
          v17 = v9[v10];
          (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1);
          v11 = sub_45EBE0(v17, v18);
          if ( v11 != 0 )
          {
            pMem = operator new(0x7Cu);
            Block = pMem;
            v22 = 0;
            if ( pMem != nullptr )
              v13 = sub_4B3DF0(pMem, 3, 1, 1124204544, 30000, 1);
            else
              v13 = nullptr;
            v14 = *v13;
            v22 = -1;
            (*(void (/*thiscall*/ **)(int *, int, uint32_t *, int, uint32_t, int, int))(v14 + 56))(v13, v11, pArg1, 1, 0, 38, -1);
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(
              pArg1,
              "AURA_DEFEND",
              -1,
              0,
              0);
          }
          v9 = *(uint32_t **)(pArg5 + 4);
          v15 = v9[v10 + 2];
          v10 += 2;
        }
        while ( v15 != 0xFFFF );
        nArg2 = nArg22;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(pArg1, 1, 0, 0, 0, 0, 0);
      v20 = 0;
      Block = (void *)1;
      nRand = rand() % 2;
      sub_4DB200(pArg1, 24, *(&v20 + nRand));
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "TAU_ROAR", -1, 0, 0);
      break;
    default:
      break;
  }
  sub_4E33D0((int)pArg1, nArg2, fArg3, ArgList, pArg5, *(float *)&nArg6, *(float *)&nArg7);
}


// AI 相位辅助（99L；sub_431230+sub_699000 时钟门, 8608/8612 相位）
// ------------------------------------------------------------
// 0x5A46C0 sub_5A46C0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A46C0(int this)
{
  uint32_t *pThis; // ebx
  bool fld_21A4; // zf
  int v3; // esi
  unsigned int i; // edi
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int pObj; // ecx
  int v10; // ecx
  int v11; // edx
  int pObj2; // esi
  int v13; // eax
  int v14; // edx
  int v15; // eax
  void *Block2; // ecx
  uint8_t v17[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  int v19; // [esp+Ch] [ebp-1Ch]
  int v20; // [esp+10h] [ebp-18h]
  int v21; // [esp+14h] [ebp-14h] BYREF
  uint32_t *pThis2; // [esp+18h] [ebp-10h]
  int v23; // [esp+24h] [ebp-4h]

  pThis = (uint32_t *)this;
  fld_21A4 = *(uint8_t *)(this + 8612) == 1;
  pThis2 = (uint32_t *)this;
  if ( !fld_21A4 && *(uint32_t *)(this + 8608) + 30000 <= (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pThis + 308))(pThis) != 0 )
    {
      v3 = 0;
      Block = nullptr;
      v19 = 0;
      v20 = 0;
      v23 = 0;
      for ( i = 0; ; ++i )
      {
        v5 = pThis[29];
        v6 = *(uint32_t *)(v5 + 120);
        v7 = v6 != 0 ? (*(uint32_t *)(v5 + 124) - v6) >> 2 : 0;
        if ( (int)i >= v7 )
          break;
        v8 = *(uint32_t *)(v5 + 120);
        if ( v8 != 0 && i < (*(uint32_t *)(v5 + 124) - v8) >> 2 )
          pObj = *(uint32_t *)(v8 + 4 * i);
        else
          pObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
        {
          v10 = pThis[29];
          v11 = *(uint32_t *)(v10 + 120);
          if ( v11 != 0 && i < (*(uint32_t *)(v10 + 124) - v11) >> 2 )
            pObj2 = *(uint32_t *)(v11 + 4 * i);
          else
            pObj2 = 0;
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);
          v14 = *pThis;
          v21 = v13;
          v15 = (*(int (/*thiscall*/ **)(uint32_t *))(v14 + 376))(pThis);
          pThis = pThis2;
          if ( v21 == v15
            && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pThis2 + 1244))(pThis2, pObj2) != 0
            && (uint8_t)sub_4DAB60(20) != 0 )
          {
            v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);
            sub_431230((int)v17, &v21);
            v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);
            sub_431230((int)v17, &v21);
          }
        }
        v3 = v19;
      }
      Block2 = Block;
      if ( Block != nullptr && (v3 - (int)Block) >> 2 != 0 )
      {
        v21 = 0xFFFF;
        sub_431230((int)v17, &v21);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*pThis + 560))(pThis, 15, v17, 0, 0);
        Block2 = Block;
      }
      v23 = -1;
      if ( Block2 != nullptr )
        j__free(Block2);
      Block = nullptr;
      v19 = 0;
      v20 = 0;
    }
    pThis[2152] = sub_699000((int)(pThis + 9));  // 【clock_now(clk)】
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
  int fld_e1908; // eax
  int fld_e1813; // eax
  int v4; // edi
  int fld_e18132; // edi

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
          fld_e1908 = *(this + 1908);
          if ( fld_e1908 == 2 && *(this + 1909) == 1 || fld_e1908 == 0 && (int)*(this + 1909) >= 1 )
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
        fld_e1813 = *(this + 1813);
        if ( fld_e1813 != 0 )
        {
          v4 = (*(int (**)(void))(*(uint32_t *)fld_e1813 + 120))();
          if ( ((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) >= v4
             || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0)
            && ((fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                 (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < fld_e18132)
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
int /*thiscall*/ sub_5A4B20(unsigned int *this, int nArg2, float *pArg3, int nArg4)
{
  float *pArg32; // ebx
  unsigned int fld_e161; // edi
  int fld_e30; // edi
  int v8; // eax
  unsigned int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int pObj; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // edi
  int pObj2; // edi
  int v20; // ebx
  int v21; // eax
  int v22; // edi
  unsigned int v24; // [esp+10h] [ebp-18h]
  int v25; // [esp+10h] [ebp-18h]
  int v26; // [esp+14h] [ebp-14h]
  int v27; // [esp+18h] [ebp-10h]

  pArg32 = pArg3;
  if ( (*(int (/*thiscall*/ **)(unsigned int *))(*this + 840))(this) != 14 || (uint8_t)nArg4 != 0 )
    goto LABEL_27;
  if ( *((uint8_t *)this + 642) != 0 )
  {
    fld_e161 = *(this + 161);
    goto LABEL_9;
  }
  fld_e30 = *(this + 30);
  if ( fld_e30 != 0 )
  {
    if ( *(uint32_t *)(fld_e30 + 148) == -1 )
      sub_4938F0(*(this + 30));
    fld_e161 = *(uint32_t *)(fld_e30 + 112);
LABEL_9:
    if ( fld_e161 > 1 )
      goto LABEL_27;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0
    || (v24 = *this,
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2),
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
    v25 = (uint64_t)(pArg3[3] * 0.5 + *pArg3);
    v26 = (*(int (/*fastcall*/ **)(unsigned int *, uint32_t))(*this + 124))(
            this,
            (uint64_t)(pArg3[3] * 0.5 + *pArg3) >> 32);
    v27 = (uint64_t)(pArg3[5] * 0.5 + pArg3[2]);
    v12 = sub_42FCB0(228);
    v13 = 0;
    if ( v12 != 0 )
      v13 = sub_431860(v12, "Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
    if ( sub_44B6C0(284) != 0 )
      pObj = sub_44E1F0(v13, 1);
    else
      pObj = 0;
    sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);
    v15 = *(uint32_t *)pObj;
    v16 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int, int))(v15 + 148))(pObj, v16);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 112))(pObj, v25, v26, v27);
    v17 = sub_42FCB0(228);
    if ( v17 != 0 )
      v18 = sub_431860(v17, "Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
    else
      v18 = 0;
    if ( sub_44B6C0(284) != 0 )
      pObj2 = sub_44E1F0(v18, 1);
    else
      pObj2 = 0;
    sub_45FE80(*(this + 29), pObj2, 2, 0, pObj2, (int)this, 0);
    v20 = *(uint32_t *)pObj2;
    v21 = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int, int))(v20 + 148))(pObj2, v21);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, v25, v26, v27);
    (*(void (/*thiscall*/ **)(unsigned int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "SWD_GUARDED",
      -1,
      0,
      0);
    sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
    pArg32 = pArg3;
  }
LABEL_27:
  v22 = sub_4DA3B0(nArg2, pArg32, nArg4);
  *((uint8_t *)this + 8604) = 0;
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
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
  char *pMem; // eax
  char *v3; // edi
  int pObj; // eax
  char *pMem2; // eax
  int pObj6; // eax
  char *pMem3; // eax
  int pObj5; // eax
  char *pMem4; // eax
  int pObj3; // eax
  char *pMem5; // eax
  char *v12; // ebx
  int pObj2; // eax
  char *pMem6; // eax
  int pObj4; // eax
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
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v20 = sub_4BA9E0(pMem, "Monster/Tau/wrap01.equ", 0);
  else
    v20 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v20);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v19 = sub_4BA9E0(pMem2, "Monster/Tau/armlet01.equ", 0);
  else
    v19 = nullptr;
  pObj6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v19);
  if ( pObj6 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 4))(pObj6, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v18 = sub_4BA9E0(pMem3, "Monster/Tau/tattoo01.equ", 0);
  else
    v18 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    Block = sub_4BA9E0(pMem4, "Monster/Tau/Hair02.equ", 0);
  else
    Block = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, Block);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v12 = sub_4BA9E0(pMem5, "Monster/Tau/Horn01.equ", 0);
  else
    v12 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem6 = (char *)operator new(0x544u);
  if ( pMem6 != nullptr )
    v3 = sub_4BA9E0(pMem6, "Monster/Tau/Weapon01.equ", 0);
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
  sub_4EB2C0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  sub_4EB6A0(0.80000001);
  result = sub_699000((int)(this + 9)) + 15000;  // 【clock_now(clk)】
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
int /*thiscall*/ sub_5A5180(void *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  uint32_t *v7; // edx

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
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
uint32_t */*thiscall*/ sub_5A5260(uint32_t *this, uint32_t *pArg2)
{
  uint32_t *result; // eax
  int v4; // edx
  int v5; // edi
  int v6; // eax
  int nRand; // eax
  int fld_e1554; // eax
  int v9; // edx

  sub_4D90A0(pArg2);
  result = (uint32_t *)(*pArg2 - 6);
  switch ( *pArg2 )
  {
    case 6:
      sub_4D84F0(0, 0);
      v4 = *this;
      *(this + 1813) = pArg2[3];
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
        nRand = rand();
        sub_49C5F0(11, 0, 0, nRand % 300 + 300);
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
      fld_e1554 = *(this + 1554);
      v9 = *(uint32_t *)(fld_e1554 + 4);
      result = (uint32_t *)(fld_e1554 + 4);
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
  int nRand; // eax
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
        nRand = rand();
        v4 = nRand % 100;
        result = nRand / 100;
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
  int pObj; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v7[4]; // [esp+14h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1943) == 3
    && rand() % 100 < 50 )
  {
    pObj = sub_4E7F30(this, 150, 80, 0);
    if ( pObj != 0 )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, bool))(v3 + 144))(this, v5 < v4);
      memset(&pBuf[1], 0, 12);
      v7[3] = 0;
      v7[0] = 1;
      sub_431230((int)pBuf, v7);
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
      sub_5E5260(pBuf);
    }
  }
}



// 唐加斯地震技能：TangasAnimation/EF_EarthQuake.ani + EF_EarthQuakeStrong.ani +
//   Monster/Tau/TangasAnimation/TangasAxeAfterImage.ani 残影（124L；
//   this+6556==8 大状态门 + vt+308 本地玩家门, 研究 20 §1.2）
// ------------------------------------------------------------
// 0x5A5610 sub_5A5610
// ------------------------------------------------------------
char /*usercall*/ sub_5A5610@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
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

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 || *(uint32_t *)(pArg1 + 6556) != 8 )
    return sub_4E1780((uint32_t *)pArg1);
  if ( sub_41A5E0(pArg1 + 7028) == 1 )
  {
    v4 = *(uint32_t *)(pArg1 + 120);
    if ( *(uint8_t *)(v4 + 170) != 0 )
    {
      v5 = *(uint32_t *)(pArg1 + 6216);
      if ( v4 == *(uint32_t *)(v5 + 4) )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(v5 + 4));
        sub_4926A0(*(uint32_t *)(pArg1 + 120));
      }
    }
    return sub_4E1780((uint32_t *)pArg1);
  }
  if ( sub_41A5E0(pArg1 + 7028) != 2 && sub_41A5E0(pArg1 + 7028) != 3 )
    return sub_4E1780((uint32_t *)pArg1);
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 2 && *(uint8_t *)(pArg1 + 8605) == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 152))(pArg1, nArg2, nArg3) != 0 )
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 55;
    else
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 55;
    v25 = v6;
    if ( sub_41A5E0(pArg1 + 7028) == 2 )
    {
      if ( sub_42FCB0(228) != 0 )
      {
        if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
          v7 = sub_431920(pArg1 + 108, (char)"TangasAnimation/EF_EarthQuake.ani", 1);
        else
          v7 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)"TangasAnimation/EF_EarthQuake.ani", 1);
        goto LABEL_24;
      }
    }
    else if ( sub_42FCB0(228) != 0 )
    {
      if ( *(uint32_t *)(pArg1 + 384) < 0x10u )
        v7 = sub_431920(pArg1 + 108, (char)"TangasAnimation/EF_EarthQuakeStrong.ani", 1);
      else
        v7 = sub_431920(*(uint32_t *)(pArg1 + 364), (char)"TangasAnimation/EF_EarthQuakeStrong.ani", 1);
LABEL_24:
      v8 = v7;
      if ( sub_44B6C0(284) != 0 )
        v9 = (int *)sub_44E1F0(v8, 1);
      else
        v9 = nullptr;
      sub_45FE80(*(uint32_t *)(pArg1 + 116), (int)v9, 2, 0, (int)v9, pArg1, 0);
      v10 = *v9;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v11 + 195);
      (*(void (/*thiscall*/ **)(int *, int, int))(v10 + 112))(v9, v25, v12);
      v13 = *v9;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);
      (*(void (/*thiscall*/ **)(int *, int))(v13 + 148))(v9, v14);
      *(uint8_t *)(pArg1 + 8605) = 1;
      return sub_4E1780((uint32_t *)pArg1);
    }
    v7 = 0;
    goto LABEL_24;
  }
  if ( *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) >= 4 && *(uint8_t *)(pArg1 + 8604) == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 152))(pArg1, nArg2, nArg3) != 0 )
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) + 196;
    else
      v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) - 196;
    v26 = v15;
    if ( sub_42FCB0(228) != 0 )
      v16 = sub_431860((char)"Monster/Tau/TangasAnimation/TangasAxeAfterImage.ani", 1);
    else
      v16 = 0;
    if ( sub_44B6C0(284) != 0 )
      v17 = (int *)sub_44E1F0(v16, 1);
    else
      v17 = nullptr;
    sub_45FE80(*(uint32_t *)(pArg1 + 116), (int)v17, 2, 0, (int)v17, pArg1, 0);
    v18 = *v17;
    v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
    v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 124))(pArg1, v19 + 21);
    (*(void (/*thiscall*/ **)(int *, int, int))(v18 + 112))(v17, v26, v20);
    v21 = *v17;
    v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 152))(pArg1);
    v23 = sub_432E50(v22);
    (*(void (/*thiscall*/ **)(int *, int))(v21 + 148))(v17, v23);
    *(uint8_t *)(pArg1 + 8604) = 1;
    if ( sub_41A5E0(pArg1 + 7028) == 2 )
      sub_49C5F0(12, v26, 0, 100);
    else
      sub_49C5F0(13, v26, 0, 100);
  }
  return sub_4E1780((uint32_t *)pArg1);
}


// 唐加斯装载：R_TAU_* 语音 + Monster/Tau/{wrap01,tattoo01,tangasHair01,tangasAcc01,weapon03}.equ（78L）
// ------------------------------------------------------------
// 0x5A5990 sub_5A5990
// ------------------------------------------------------------
int */*usercall*/ sub_5A5990@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  char *pMem; // eax
  char *v4; // eax
  int pObj2; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj4; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj3; // eax
  char *pMem4; // eax
  char *v13; // eax
  int pObj5; // eax
  char *pMem5; // eax
  char *v16; // eax
  int pObj; // eax
  int *result; // eax

  pArg1[1698] = 2;
  pArg1[1699] = 2;
  pArg1[1700] = 2;
  pArg1[1701] = 3;
  pArg1[1702] = 4;
  sub_4015C0("R_TAU_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_TAU_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("TAU_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Tau/wrap01.equ", 0);
  else
    v4 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, v4, nArg2);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/Tau/tattoo01.equ", 0);
  else
    v7 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v7);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v10 = sub_4BA9E0(pMem3, "Monster/Tau/tangasHair01.equ", 0);
  else
    v10 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v10);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v13 = sub_4BA9E0(pMem4, "Monster/Tau/tangasAcc01.equ", 0);
  else
    v13 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v13);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v16 = sub_4BA9E0(pMem5, "Monster/Tau/weapon03.equ", 0);
  else
    v16 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v16);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  result = (int *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 672))(pArg1, 3);
  if ( *result > 14 )
    return (int *)(*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 612))(pArg1, 1, 1);
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
  uint32_t *pThis_876; // esi
  int i; // edi
  int result; // eax
  int (/*thiscall*/ ***fld_e2168)(uint32_t, int); // ecx

  pThis_876 = this + 2166;
  for ( i = 2; i != 0; --i )
  {
    if ( *pThis_876 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_876)(*pThis_876, 1);
    *pThis_876++ = 0;
  }
  fld_e2168 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2168);
  if ( fld_e2168 != nullptr )
    result = (**fld_e2168)(fld_e2168, 1);
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
int /*stdcall*/ sub_5A5CD0(int *pDwArg1, int nArg2)
{
  int result; // eax
  int v3; // esi
  int pObj; // eax

  result = sub_4DC390(pDwArg1, nArg2);
  v3 = result;
  if ( result != 3 )
  {
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);
    if ( pObj != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 19 )
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 1.5);
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
int /*thiscall*/ sub_5A5D40(void *this, int nArg2)
{
  int result; // eax
  unsigned int pThis_2A0; // edi
  int v5; // edx
  int v6; // [esp+10h] [ebp+8h]

  result = sub_4DBA80(nArg2);
  if ( nArg2 == 9 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;
    *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.2;
    sub_41A590(pThis_2A0, v5, v6);
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A5DA0 sub_5A5DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A5DA0(void *this, int nArg2)
{
  int result; // eax
  unsigned int pThis_2A0; // edi
  int v5; // edx
  int v6; // [esp+10h] [ebp+8h]

  result = sub_4DBC20(nArg2);
  if ( nArg2 == 9 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 102;
    *(float *)&v6 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - 0.2;
    sub_41A590(pThis_2A0, v5, v6);
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
  int pThis_668; // eax
  int v6; // edx

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
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
      pThis_668 = sub_699000((int)(this + 1640));  // 【clock_now(clk)】
      v6 = *this;
      *(this + 2169) = pThis_668;
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
int /*thiscall*/ sub_5A5E90(int this, int nArg2, int nArg3)
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
int /*stdcall*/ sub_5A5F20(int *pDwArg1, int nArg2)
{
  int result; // eax
  int v3; // edi

  result = sub_5A5CD0(pDwArg1, nArg2);
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0
      || *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128) == 0 )
    {
      return v3;
    }
    else
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.5);
      return 2;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5F90 sub_5A5F90
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5F90(int *pDwArg1, int nArg2)
{
  int result; // eax
  int v3; // esi

  result = sub_5A5CD0(pDwArg1, nArg2);
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0 )
    {
      return v3;
    }
    else
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.60000002);
      return 0;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A5FF0 sub_5A5FF0
// ------------------------------------------------------------
int /*stdcall*/ sub_5A5FF0(int *pDwArg1, int nArg2)
{
  int result; // eax
  int v3; // esi

  result = sub_5A5CD0(pDwArg1, nArg2);
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0 )
    {
      return v3;
    }
    else
    {
      *pDwArg1 = (uint64_t)((double)*pDwArg1 * 0.69999999);
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
  int fld_e2170; // ecx
  int v5; // ebx
  int *fld_e1813; // edi
  int v7; // edx
  int v8; // eax
  int result; // eax
  int fld_e21702; // ecx
  int v11; // [esp-1Ch] [ebp-38h]
  uint32_t v12[5]; // [esp+8h] [ebp-14h]

  v2 = *this;
  v12[0] = 2;
  v12[1] = 3;
  v12[2] = 4;
  v12[3] = 5;
  v3 = ((int (/*thiscall*/ *)(int **))v2[50])(this);
  fld_e2170 = (int)*(this + 2170);
  if ( *(uint32_t *)(v3 + 148) == v12[fld_e2170] && *(this + 2169) == nullptr )
  {
    v5 = 8 * (5 * fld_e2170 - 10);
    if ( ((int (/*thiscall*/ *)(int **))(*this)[38])(this) == 1 )
      v5 = -v5;
    fld_e1813 = *(this + 1813);
    v7 = *fld_e1813;
    v12[4] = fld_e1813;
    v11 = (*(int (**)(void))(v7 + 124))();
    v8 = (*(int (/*thiscall*/ **)(int *))(*fld_e1813 + 120))(fld_e1813);
    sub_4E4A50(this, 30068, 10, v8 - v5, v11, 0, 4, 0, 0, 0);
    *(this + 2169) = (int *)1;
  }
  result = ((int (/*thiscall*/ *)(int **))(*this)[50])(this);
  fld_e21702 = (int)*(this + 2170);
  if ( *(uint32_t *)(result + 148) == v12[fld_e21702] + 1 )
  {
    *(this + 2169) = nullptr;
    *(this + 2170) = (int *)(fld_e21702 + 1);
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
  int fld_e1813; // ebx
  int v6; // edi
  int v7; // eax
  int fld_e18132; // ebx
  int v9; // eax
  int fld_e18133; // ebx
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
    fld_e1813 = *(this + 1813);
    v6 = v4 != 0 ? -30 : 30;
    v12 = (*(int (**)(void))(*(uint32_t *)fld_e1813 + 124))() - 30;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
    sub_4E4A50(this, 30068, 10, v6 + v7, v12, 0, 4, 0, 0, 0);
    fld_e18132 = *(this + 1813);
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 124))(fld_e18132);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 120))(fld_e18132);
    sub_4E4A50(this, 30068, 10, v9, v13, 0, 4, 0, 0, 0);
    fld_e18133 = *(this + 1813);
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18133 + 124))(fld_e18133) + 30;
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18133 + 120))(fld_e18133);
    return sub_4E4A50(this, 30068, 10, v6 + v11, v14, 0, 4, 0, 0, 0);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A6210 sub_5A6210
// ------------------------------------------------------------
char /*thiscall*/ sub_5A6210(void *this, int nArg2)
{
  int pThis_1B74; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0
    || *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 12) != 0
    || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 8
    || (pThis_1B74 = sub_41A5E0((unsigned int)this + 7028)) != 1 )
  {
    LOBYTE(pThis_1B74) = 0;
  }
  return pThis_1B74;
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
  int *fld_1848; // ecx

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
    fld_1848 = *(int **)(this + 6216);
    if ( fld_1848 != nullptr && (*(uint32_t *)(this + 6220) - (int)fld_1848) >> 2 != 0 )
    {
      sub_4926A0(*fld_1848);
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
int /*thiscall*/ sub_5A63E0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  uint32_t *fld_e1554; // ecx
  int v8; // [esp+8h] [ebp-4h]

  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
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
      fld_e1554 = (uint32_t *)*(this + 1554);
      if ( fld_e1554 != nullptr )
      {
        result = (*(this + 1555) - (int)fld_e1554) >> 2;
        if ( result != 0 )
          return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *fld_e1554);
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
  int fld_e30; // eax
  int v3; // edx

  fld_e30 = *(this + 30);
  if ( *(int *)(fld_e30 + 148) >= 3 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int))(*this + 888))(this, 2, 2, 1000, 1000);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      sub_5A5E00(this);
    LOBYTE(fld_e30) = *((uint8_t *)this + 8604);
    if ( (uint8_t)fld_e30 == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
      v3 = *this;
      *((uint8_t *)this + 8604) = 1;
      LOBYTE(fld_e30) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v3 + 212))(
                     this,
                     "STONE_LASER_FIRE",
                     -1,
                     0,
                     0);
    }
  }
  return fld_e30;
}



// 石激光蓄力：STONE_LASER_READY 播报（this+204/+208/8604 相位, 66L）
// ------------------------------------------------------------
// 0x5A6520 sub_5A6520
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6520(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1639; // ebx
  int result; // eax
  int v8; // edx
  int *fld_e1554; // ecx
  uint32_t *fld_e15542; // ecx

  fld_e1639 = *(this + 1639);
  result = sub_5A63E0(this, ArgList, fArg3, nArg4, nArg5);
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
      fld_e1554 = (int *)*(this + 1554);
      if ( fld_e1554 != nullptr )
      {
        result = (*(this + 1555) - (int)fld_e1554) >> 2;
        if ( result != 0 )
        {
          sub_4926A0(*fld_e1554);
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
  if ( fld_e1639 == 8 && ArgList != 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 1 )
    {
      fld_e15542 = (uint32_t *)*(this + 1554);
      if ( fld_e15542 != nullptr )
      {
        result = (*(this + 1555) - (int)fld_e15542) >> 2;
        if ( result != 0 )
          return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *fld_e15542);
      }
    }
  }
  return result;
}



// 狂暴 AI：C_BERSERK 播报（62L；读 this+6556 大状态 → 狂暴条件门【推断：濒死/血线触发】）
// ------------------------------------------------------------
// 0x5A6630 sub_5A6630
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6630(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_199C; // ebx
  int result; // eax
  int *fld_1848; // ecx
  uint32_t *fld_18482; // ecx

  fld_199C = *(uint32_t *)(this + 6556);
  result = sub_5A63E0((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 1 )
    {
      *(uint8_t *)(this + 8604) = 0;
      fld_1848 = *(int **)(this + 6216);
      if ( fld_1848 != nullptr )
      {
        result = (*(uint32_t *)(this + 6220) - (int)fld_1848) >> 2;
        if ( result != 0 )
        {
          sub_4926A0(*fld_1848);
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
  if ( fld_199C == 8 && ArgList != 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 1 )
    {
      fld_18482 = *(uint32_t **)(this + 6216);
      if ( fld_18482 != nullptr )
      {
        result = (*(uint32_t *)(this + 6220) - (int)fld_18482) >> 2;
        if ( result != 0 )
          return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *fld_18482);
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
int /*thiscall*/ sub_5A6740(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e1905; // eax
  double v5; // st7

  result = nArg3;
  if ( nArg3 == 0 )
  {
    fld_e1905 = *(this + 1905);
    v5 = *(float *)(fld_e1905 + 68);
    result = fld_e1905 + 64;
    *(float *)(result + 4) = v5 * 0.76923078;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6770 sub_5A6770
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6770(int this, int nArg2, int nArg3)
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
  if ( nArg3 == 0 )
    *(float *)(*(uint32_t *)(this + 7620) + 68) = *(float *)(*(uint32_t *)(this + 7620) + 68) * 1.3;
  return result;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5A6820 sub_5A6820
// ------------------------------------------------------------
int /*thiscall*/ sub_5A6820(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1813; // ecx
  int v7; // ebx
  int result; // eax

  if ( ArgList == 8 && *(int *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) >= 1 )
  {
    fld_e1813 = *(this + 1813);
    if ( fld_e1813 != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
      if ( (signed int)abs32(v7 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) < *(uint32_t *)(*(this + 1905) + 16) )
        *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) = 0;
    }
  }
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    *(this + 2169) = 0;
    *(this + 2170) = 0;
    result = sub_699000((int)(this + 1910));  // 【clock_now(clk)】
    *(this + 2171) = result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A68C0 sub_5A68C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A68C0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  bool v5; // cc
  unsigned int v6; // edi
  int v7; // edx
  unsigned int v8; // edi
  int v9; // edx
  int fld_e1905; // eax
  double v11; // st7
  int v12; // [esp+10h] [ebp+Ch]
  int v13; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 102;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v6)) - 1.0;
    sub_41A590(v6, v7, v12);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 158;
    *(float *)&v13 = COERCE_FLOAT(sub_41A5E0(v8)) - 1.0;
    sub_41A590(v8, v9, v13);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    result = nArg2;
    if ( nArg2 == 0 )
    {
      *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.5;
      return result;
    }
    if ( nArg2 <= 0 )
      return result;
    v5 = nArg2 <= 2;
    goto LABEL_8;
  }
  result = nArg3 - 2;
  if ( nArg3 == 2 )
  {
    result = nArg2;
    if ( nArg2 >= 0 )
    {
      v5 = nArg2 <= 1;
LABEL_8:
      if ( v5 )
      {
        fld_e1905 = *(this + 1905);
        v11 = *(float *)(fld_e1905 + 68);
        result = fld_e1905 + 64;
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
int /*thiscall*/ sub_5A69C0(char *this, int nArg2, int nArg3)
{
  char *pThis_1D73; // ecx
  int result; // eax
  int pThis_771; // eax
  double v7; // st7
  int v8; // edx
  unsigned int v9; // edi
  int v10; // edx
  unsigned int pThis_2A0; // edi
  int v12; // edx
  int pThis_7712; // eax
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
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
    {
      result = nArg2;
      if ( (unsigned int)nArg2 <= 1 )
      {
        pThis_771 = *((uint32_t *)this + 1905);
        v7 = *(float *)(pThis_771 + 68);
        result = pThis_771 + 64;
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
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 158;
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 1.0;
    sub_41A590(pThis_2A0, v12, v16);
    (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    result = nArg2;
    if ( nArg2 != 0 )
    {
      if ( nArg2 > 0 && nArg2 <= 2 )
      {
        pThis_7712 = *((uint32_t *)this + 1905);
        v14 = *(float *)(pThis_7712 + 68);
        result = pThis_7712 + 64;
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
int /*thiscall*/ sub_5A6B60(uint32_t **this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int *fld_e1554; // eax

  if ( ((int (/*thiscall*/ *)(uint32_t **))(*this)[210])(this) == 8 && sub_41A5E0((unsigned int)(this + 1757)) == 3 )
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[52])(this, **(this + 1554));
  result = sub_5A6520((int *)this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(this + 1757));
    if ( result == 3 )
    {
      fld_e1554 = *(this + 1554);
      *((uint8_t *)this + 8680) = 0;
      sub_4926A0(*fld_e1554);
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
  int pThis_6DD; // eax

  sub_5A62B0((int)this);
  pThis_6DD = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( pThis_6DD == 8 )
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757));
    if ( pThis_6DD == 1 )
      LOBYTE(pThis_6DD) = sub_5A64A0(this);
  }
  return pThis_6DD;
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
  int nRand; // eax
  int v12; // eax
  int v13; // edi
  uint32_t *v14; // edi
  void *fld_e29; // ecx
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
    && *(this + 2171) + 25 < (unsigned int)sub_699000((int)(this + 1910)) )  // 【clock_now(clk)】
  {
    v5 = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 924))(this, 42)];
    v6 = *this;
    v19 = v5;
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 152))(this);
    v8 = *this;
    v9 = *v5;
    v20 = v7 == 0;
    v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 128))(this);
    nRand = rand();
    v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, nRand % 40 + v10);
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, v12 + 10) != 0 ? -30 : 30;
    v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v13;
    v14 = v19;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 40))(v19, v16);
    *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v19 + 28))(v19) + 84) = v20;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*v14 + 12))(v14, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, char *))(*v14 + 92))(v14, v17);
    fld_e29 = (void *)*(this + 29);
    v21 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v17);
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
  int pThis_348; // eax

  sub_5A62B0(this);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 1 )
    sub_5A64A0((uint32_t *)this);
  LOBYTE(pThis_348) = *(uint8_t *)(this + 8680);
  if ( (uint8_t)pThis_348 == 0 )
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( pThis_348 == 8 )
    {
      pThis_348 = sub_41A5E0(this + 7028);
      if ( pThis_348 == 3 )
      {
        pThis_348 = *(uint32_t *)(this + 120);
        if ( pThis_348 != 0 && *(int *)(pThis_348 + 148) >= 4 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            sub_5A6270((int *)this);
          LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
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
  return pThis_348;
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
  sub_4015C0((void *)v10, v11);  // 【std::string构造赋值】
  sub_4015C0("GOLEM_FIND", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("GOLEM_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("GOLEM_DIE", 9u);  // 【std::string构造赋值】
  v11 = 10000;
  v10 = 5000;
  v12 = &v3;
  *(uint32_t *)(this + 7324) = 300;
  *(uint8_t *)(this + 8640) = 0;
  v9 = 15;
  v8 = 0;
  LOBYTE(v4) = 0;
  sub_4015C0("R_GOLEM_AMB", 0xBu);  // 【std::string构造赋值】
  return sub_4DE5E0(v3, v4, v5, v6, v7, v8, v9, v10, v11);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A6F70 sub_5A6F70
// ------------------------------------------------------------
void /*thiscall*/ sub_5A6F70(int *this)
{
  int pThis_6DD; // eax
  int v3; // eax

  sub_5A62B0((int)this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8 )
  {
    pThis_6DD = sub_41A5E0((unsigned int)(this + 1757)) - 1;
    if ( pThis_6DD != 0 )
    {
      v3 = pThis_6DD - 1;
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
  uint32_t *pThis; // ecx
  void *pMem; // eax
  int pObj; // eax
  int fld_e2168; // ecx
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
      pThis = this;
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
        pThis = this;
LABEL_10:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(pThis, 5);
      }
      break;
    default:
      break;
  }
  v7 = (double)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0) * 0.0099999998;
  Block = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
  if ( (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) * v7 < Block )
  {
    fld_e2168 = *(this + 2168);
    if ( fld_e2168 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2168 + 80))(fld_e2168) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2168) + 76))(*(this + 2168), 0);
  }
  else
  {
    if ( *(this + 2168) == 0 )
    {
      pMem = operator new(0x64u);
      if ( pMem != nullptr )
        pObj = sub_51A7D0(pMem);
      else
        pObj = 0;
      *(this + 2168) = pObj;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
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
  int pObj; // eax
  int v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // [esp-18h] [ebp-3Ch]
  int v8; // [esp-10h] [ebp-34h]
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
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
      pObj = sub_4E7F30(this, 200, 75, 0);
      if ( pObj != 0 )
      {
        v3 = *this;
        v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
        (*(void (/*thiscall*/ **)(uint32_t *, bool))(v3 + 144))(this, v5 < v4);
        memset(&pBuf[1], 0, 12);
        v10[3] = 0;
        v10[0] = 1;
        sub_431230((int)pBuf, v10);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
        sub_5E5260(pBuf);
      }
    }
  }
}



// 格挡特效：Character/Swordman/Effect/Animation/GuardSpark.ani + SWD_GUARDED 播报
//   （43L；与 0x5A4B20 vmt200 覆写同族, 此为普通槽位版本）
// ------------------------------------------------------------
// 0x5A72E0 sub_5A72E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A72E0(int *this, int nArg2, float *pArg3)
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
  v11 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, (uint64_t)pArg3[2]) - 1;
  (*(void (/*fastcall*/ **)(char *, uint32_t, uint32_t, int))(v9 + 112))(
    v6,
    (uint64_t)*pArg3 >> 32,
    (uint64_t)*pArg3,
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
  int **pThis_876; // edi
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
    v3 = v2 + 95;
  else
    v3 = v2 - 95;
  v27 = v3;
  pThis_876 = (int **)(this + 2166);
  v26 = 2;
  do
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(**pThis_876 + 12))(*pThis_876, 0);
    v5 = **pThis_876;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v6 + 65);
    (*(void (/*thiscall*/ **)(int *, int, int))(v5 + 40))(*pThis_876, v27, v7);
    (*(void (/*thiscall*/ **)(int *, char *))(**pThis_876 + 92))(*pThis_876, v21);
    fld_e29 = (void *)*(this + 29);
    v28 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v21);
    v28 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++pThis_876;
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
  fld_e292 = *(this + 29);
  v28 = -1;
  sub_45FE80(fld_e292, (int)v13, 2, 0, (int)v13, (int)this, 0);
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
  int fld_e30; // eax
  int v3; // edx
  int v4; // edi
  int v5; // eax

  LOBYTE(fld_e30) = *((uint8_t *)this + 8604);
  if ( (uint8_t)fld_e30 == 0 )
  {
    fld_e30 = *(this + 30);
    if ( *(uint32_t *)(fld_e30 + 148) == 2 )
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
      LOBYTE(fld_e30) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                     this,
                     "GOLEM_DOWN",
                     -1,
                     0,
                     0);
    }
  }
  return fld_e30;
}



// 埋地/起立 AI：GOLEM_DOWN 播报（this+8604 相位, 68L）
// ------------------------------------------------------------
// 0x5A7610 sub_5A7610
// ------------------------------------------------------------
char /*thiscall*/ sub_5A7610(uint32_t **this)
{
  uint32_t **pThis; // ebx
  int fld_e30; // eax
  const void **v3; // ebx
  double nRand; // st7
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // eax
  int v9; // [esp+8h] [ebp-70h]
  uint8_t v11[98]; // [esp+10h] [ebp-68h]

  pThis = this;
  LOBYTE(fld_e30) = *((uint8_t *)this + 8604);
  if ( (uint8_t)fld_e30 == 0 )
  {
    fld_e30 = (int)*(this + 30);
    if ( *(uint32_t *)(fld_e30 + 148) == 3 )
    {
      if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
      {
        v3 = (const void **)(pThis + 2161);
        v9 = 5;
        do
        {
          qmemcpy(v11, *v3, sizeof(v11));
          nRand = (double)(100 - rand() % 20) * 0.0099999998;
          *(uint32_t *)((char *)*v3 + 15) = (uint64_t)((double)*(int *)((char *)*v3 + 15) * nRand);
          *(uint32_t *)((char *)*v3 + 19) = (uint64_t)((double)*(int *)((char *)*v3 + 19) * nRand);
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
        pThis = this;
      }
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*pThis)[52])(pThis, *pThis[1554]);
      sub_5A73E0(pThis);
      LOBYTE(fld_e30) = ((int (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*pThis)[53])(
                     pThis,
                     "GOLEM_DOWN",
                     -1,
                     0,
                     0);
      *((uint8_t *)pThis + 8604) = 1;
    }
  }
  return fld_e30;
}



// SG 魔像装载：Monster/Golem/SG/{STHead,STLeftArm,STRightArm,STLeg}.equ 四部件
// ------------------------------------------------------------
// 0x5A7770 sub_5A7770
// ------------------------------------------------------------
int /*thiscall*/ sub_5A7770(void *this)
{
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int result; // eax
  char *Block; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    Block = sub_4BA9E0(pMem, "Monster/Golem/SG/STHead.equ", 0);
  else
    Block = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v13 = sub_4BA9E0(pMem2, "Monster/Golem/SG/STLeftArm.equ", 0);
  else
    v13 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/SG/STRightArm.equ", 0);
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/SG/STLeg.equ", 0);
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
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
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pObj4; // eax
  int pObj; // eax
  int pObj3; // eax
  int pObj2; // eax
  uint32_t *pThis_871; // edi
  int i; // ebx
  void (/*thiscall*/ ***fld_e2166)(uint32_t, int); // ecx
  int pThis_5B; // eax
  void (/*thiscall*/ ***fld_e2167)(uint32_t, int); // ecx
  int result; // eax
  char *Block; // [esp+10h] [ebp-14h]
  char *v19; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    Block = sub_4BA9E0(pMem, "Monster/Golem/ST/STHead.equ", 0);
  else
    Block = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v19 = sub_4BA9E0(pMem2, "Monster/Golem/ST/STLeftArm.equ", 0);
  else
    v19 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/ST/STRightArm.equ", 0);
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/ST/STLeg.equ", 0);
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v19);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, Block);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pThis_871 = this + 2161;
  for ( i = 5; i != 0; --i )
    *pThis_871++ = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/STGolemBullet.ptl");
  fld_e2166 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2166);
  if ( fld_e2166 != nullptr )
  {
    (**fld_e2166)(fld_e2166, 1);
    *(this + 2166) = 0;
  }
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      pThis_5B = sub_4C3640(this + 91, "Particle/STGolemFire.ptl", this);
    else
      pThis_5B = sub_4C3640(*(this + 91), "Particle/STGolemFire.ptl", this);
  }
  else
  {
    pThis_5B = 0;
  }
  fld_e2167 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);
  *(this + 2166) = pThis_5B;
  if ( fld_e2167 != nullptr )
  {
    (**fld_e2167)(fld_e2167, 1);
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
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int result; // eax
  char *v12; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v12 = sub_4BA9E0(pMem, "Monster/Golem/CL/STHead.equ", 0);
  else
    v12 = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v13 = sub_4BA9E0(pMem2, "Monster/Golem/CL/STLeftArm.equ", 0);
  else
    v13 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/CL/STRightArm.equ", 0);
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/CL/STLeg.equ", 0);
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
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
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int result; // eax
  char *v12; // [esp+Ch] [ebp-14h]
  char *v13; // [esp+10h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v12 = sub_4BA9E0(pMem, "Monster/Golem/GD/STHead.equ", 0);
  else
    v12 = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v13 = sub_4BA9E0(pMem2, "Monster/Golem/GD/STLeftArm.equ", 0);
  else
    v13 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/GD/STRightArm.equ", 0);
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/GD/STLeg.equ", 0);
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v13);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
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
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *v6; // ebx
  char *pMem4; // eax
  int pObj4; // eax
  int pObj; // eax
  int pObj3; // eax
  int pObj2; // eax
  int v12; // eax
  void (/*thiscall*/ ***fld_e2166)(uint32_t, int); // ecx
  int pThis_5B; // eax
  void (/*thiscall*/ ***fld_e2167)(uint32_t, int); // ecx
  int result; // eax
  char *v17; // [esp+10h] [ebp-14h]
  char *v18; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v17 = sub_4BA9E0(pMem, "Monster/Golem/BR/STHead.equ", 0);
  else
    v17 = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v18 = sub_4BA9E0(pMem2, "Monster/Golem/BR/STLeftArm.equ", 0);
  else
    v18 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v6 = sub_4BA9E0(pMem3, "Monster/Golem/BR/STRightArm.equ", 0);
  else
    v6 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Golem/BR/STLeg.equ", 0);
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v17);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/BRGolemBullet.ptl");
  fld_e2166 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2166);
  *(this + 2161) = v12;
  if ( fld_e2166 != nullptr )
  {
    (**fld_e2166)(fld_e2166, 1);
    *(this + 2166) = 0;
  }
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      pThis_5B = sub_4C3640(this + 91, "Particle/STGolemFire.ptl", this);
    else
      pThis_5B = sub_4C3640(*(this + 91), "Particle/STGolemFire.ptl", this);
  }
  else
  {
    pThis_5B = 0;
  }
  fld_e2167 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2167);
  *(this + 2166) = pThis_5B;
  if ( fld_e2167 != nullptr )
  {
    (**fld_e2167)(fld_e2167, 1);
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
  char *pMem; // eax
  char *v3; // edi
  char *pMem2; // eax
  char *pMem3; // eax
  char *pMem4; // eax
  char *pMem5; // eax
  int pThis_310; // eax
  int pThis_3102; // eax
  int pThis_3103; // eax
  int pThis_3104; // eax
  int pThis_3105; // eax
  char *Block; // [esp+10h] [ebp-1Ch]
  char *v15; // [esp+14h] [ebp-18h]
  char *v16; // [esp+18h] [ebp-14h]
  char *v17; // [esp+1Ch] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    Block = sub_4BA9E0(pMem, "Monster/Golem/GD/PTHead.equ", 0);
  else
    Block = nullptr;
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v15 = sub_4BA9E0(pMem2, "Monster/Golem/GD/PTLeftArm.equ", 0);
  else
    v15 = nullptr;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v17 = sub_4BA9E0(pMem3, "Monster/Golem/GD/PTRightArm.equ", 0);
  else
    v17 = nullptr;
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v16 = sub_4BA9E0(pMem4, "Monster/Golem/GD/PTLeg.equ", 0);
  else
    v16 = nullptr;
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v3 = sub_4BA9E0(pMem5, "Monster/Golem/GD/PTHorn.equ", 0);
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v17);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v16);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v15);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);
  pThis_3105 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3105 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3105 + 4))(pThis_3105, 1);
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
  int (/*thiscall*/ ***fld_e2163)(uint32_t, int); // ecx
  int result; // eax

  fld_e2163 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2163);
  if ( fld_e2163 != nullptr )
    result = (**fld_e2163)(fld_e2163, 1);
  *(this + 2163) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8320 sub_5A8320
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8320(uint32_t *this, uint32_t *uArg2)
{
  int result; // eax

  result = sub_4D9170(uArg2);
  if ( uArg2 == (uint32_t *)*(this + 2156) )
    *(this + 2156) = 0;
  if ( uArg2 == this )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 19804);
  return result;
}



// 【vmt200 命中处理器覆写】人偶系小型覆写（17L；虚表 0x6DBE6C/0x6DC394/0x6DC8BC/0x6DCDE4/0x6DD30C/0x6DD834
//   六张 +512 槽共享）
// ------------------------------------------------------------
// 0x5A8360 sub_5A8360
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8360(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi
  int fld_e2156; // eax

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 724))(this) == 0 )
  {
    fld_e2156 = *(this + 2156);
    if ( fld_e2156 != 0
      && *(uint32_t *)(fld_e2156 + 7148) != 9
      && *(this + 1814) != 0
      && sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2151) + *(this + 2157)) )  // 【clock_now(clk)】
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
void /*thiscall*/ sub_5A8400(void *this, int nArg2)
{
  if ( nArg2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1308))(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5A8430 sub_5A8430
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8430(uint32_t *this, int nArg2, int nArg3)
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
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int))(*this + 376))(this, *v5, nArg2, nArg3, 0, v6);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v4 + 592))(this, *(this + 2152), v7);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8490 sub_5A8490
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8490(uint32_t *this, int nArg2)
{
  if ( *(this + 2156) != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, nArg2, 0);
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
  int fld_e2156; // eax
  int v5; // edi
  int fld_e21562; // eax
  int fld_e21563; // eax
  int v8; // edi
  int v9; // eax
  int v10; // edi
  int fld_e1814; // eax
  int fld_e18142; // ecx
  int v13; // esi
  int v14; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 304))(*(this + 2156));
  if ( result != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
    v3 = *(uint32_t *)dword_8F8520;
    fld_e2156 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 48))(*(this + 2156));
    (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, fld_e2156);
    v5 = *(uint32_t *)dword_8F8520;
    fld_e21562 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 52))(*(this + 2156));
    (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, fld_e21562);
    fld_e21563 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 2156) + 304))(*(this + 2156));
    v8 = *(uint32_t *)dword_8F8520;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21563 + 52))(fld_e21563);
    (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 11);
    v10 = *(uint32_t *)dword_8F8520;
    fld_e1814 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1814) + 48))(*(this + 1814));
    (*(void (/*thiscall*/ **)(int, int))(v10 + 36))(dword_8F8520, fld_e1814);
    fld_e18142 = (int)*(this + 1814);
    v13 = *(uint32_t *)dword_8F8520;
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18142 + 52))(fld_e18142);
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
int /*usercall*/ sub_5A85B0@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // edi
  int nRand; // eax
  int pObj; // ecx
  int v6; // edi
  int nRand2; // eax
  int v8; // edx
  int v10; // [esp+4h] [ebp-8h] BYREF
  int v11; // [esp+8h] [ebp-4h] BYREF
  int savedregs; // [esp+Ch] [ebp+0h]

  if ( pDwArg1[1813] != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pDwArg1[1813] + 120))(pDwArg1[1813], nArg2);
    nRand = rand();
    pObj = pDwArg1[1813];
    v11 = v3 + nRand % 180 - 90;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
    nRand2 = rand();
    savedregs = 10;
    v11 = 0;
    v10 = 300;
    v8 = *pDwArg1;
    v10 = v6 + nRand2 % 180 - 90;
    (*(void (/*thiscall*/ **)(int *, int *, int *, uint32_t, int))(v8 + 140))(pDwArg1, &v11, &v10, 0, v10);
    sub_4E4A50(pDwArg1, 30069, pDwArg1[2161], v11, v10, 0, 4, 0, 0, 0);
  }
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "STONE_SET", -1, 0, 0);
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
int /*thiscall*/ sub_5A8700(int this, int nArg2, int nArg3)
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
int /*thiscall*/ sub_5A8790(int this, int nArg2, int nArg3)
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
  int fld_e1813; // edi
  int fld_e18132; // ebx
  int v5; // eax

  result = *(this + 1813);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
      fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
      v5 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      return sub_4E4A50(this, 30025, 1, fld_e1813, fld_e18132, 0, v5, 0, 0, 0);
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
  int pThis_24; // eax
  uint32_t *v3; // edx

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
    sub_5A84C0((uint32_t **)this);
  sub_4D82D0(0, 0);
  pThis_24 = sub_699000(this + 36);  // 【clock_now(clk)】
  v3 = *(uint32_t **)this;
  *(uint32_t *)(this + 8628) = pThis_24;
  *(uint32_t *)(this + 7256) = 0;
  return ((int (/*thiscall*/ *)(int, const char *, int, uint32_t, uint32_t))v3[53])(this, "DOLL_COMMAND", -1, 0, 0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A8950 sub_5A8950
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5A8950(uint32_t *this, char pszArg2, int nArg3, int nArg4, int nArg5, char pszArg6)
{
  sub_4B1030();
  *this = &CNChangeDamageBonusRate::`vftable';
  sub_64C9F0(this);
  sub_64CA10(pszArg2, nArg3, nArg4, nArg5, pszArg6);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5A89C0 sub_5A89C0
// ------------------------------------------------------------
void */*thiscall*/ sub_5A89C0(void *Block, char pszArg2)
{
  sub_5A89F0();
  if ( (pszArg2 & 1) != 0 )
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
  void *pMem; // [esp+2Ch] [ebp-28h] BYREF
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
            pMem = operator new(0x64u);
            v22 = 1;
            if ( pMem != nullptr )
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
  (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &pMem);
  v4 = sub_45EBE0(HIWORD(v19), v20);
  v5 = __RTDynamicCast(v4, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  if ( v5 == 0 )
    return v3;
  Block = operator new(0x80u);
  v22 = 0;
  if ( Block != nullptr )
  {
    v13 = (float)(unsigned int)pMem;
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
  int pThis_9; // esi
  int result; // eax
  unsigned int i; // ebx
  int fld_e29; // ecx
  int v6; // edx
  int v7; // edx
  int pObj3; // ecx
  int fld_e292; // ecx
  int v10; // edx
  int v11; // eax
  int pObj; // eax
  int pObj2; // esi
  int v14; // ebx
  unsigned int v15; // [esp+8h] [ebp-4h]

  pThis_9 = (int)(this + 9);
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( *(this + 2165) + 500 > (unsigned int)result )
    return result;
  *(this + 2165) = sub_699000(pThis_9);
  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v6 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
    if ( v6 != 0 )
      result = (*(uint32_t *)(fld_e29 + 12) - v6) >> 2;
    else
      result = 0;
    if ( (int)i >= result )
    {
      *(this + 2156) = 0;
      return result;
    }
    v7 = *(uint32_t *)(fld_e29 + 8);
    if ( v7 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v7) >> 2 )
      pObj3 = *(uint32_t *)(v7 + 4 * i);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 529) != 0 )
    {
      fld_e292 = *(this + 29);
      v10 = *(uint32_t *)(fld_e292 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v10) >> 2 )
        v11 = *(uint32_t *)(v10 + 4 * i);
      else
        v11 = 0;
      pObj = __RTDynamicCast(v11, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      pObj2 = pObj;
      if ( pObj != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) >= 31
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) <= 35
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 3001) )
      {
        break;
      }
    }
LABEL_23:
    ;
  }
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);
  if ( v14 != (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj2)) == 0 )
  {
    i = v15;
    goto LABEL_23;
  }
  if ( *(this + 2156) != pObj2 )
    result = sub_4D83E0(0, 0);
  *(this + 2156) = pObj2;
  return result;
}



// 硬直字段（this+204, 研究 15）
// ------------------------------------------------------------
// 0x5A8DD0 sub_5A8DD0
// ------------------------------------------------------------
int /*thiscall*/ sub_5A8DD0(uint32_t *this)
{
  int fld_e2159; // eax

  fld_e2159 = *(this + 2159);
  if ( fld_e2159 == 4 || fld_e2159 == 5 )
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
  uint32_t *pThis; // ebx
  unsigned int i; // edi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj3; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int pObj2; // eax
  int pObj; // esi
  int v13; // eax
  int v14; // [esp+Ch] [ebp-8h]

  pThis = this;
  for ( i = 0; ; ++i )
  {
    v3 = pThis[29];
    v4 = *(uint32_t *)(v3 + 8);
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      pObj3 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 529) != 0 )
    {
      v8 = pThis[29];
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      pObj2 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      pObj = pObj2;
      if ( pObj2 != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) >= 31
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) <= 35
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 3001) )
      {
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);
        pThis = this;
        if ( v14 == v13 && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 1244))(this, pObj) != 0 )
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 736))(pObj);
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
int /*thiscall*/ sub_5A8FF0(void *this, int pArg2, int nArg3, int nArg4)
{
  int v5; // edi
  int pThis_30; // eax
  int v7; // edi
  int pThis_34; // eax
  int v9; // esi
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  unsigned int i; // edi
  int v14; // edx

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
  v5 = *(uint32_t *)dword_8F8520;
  pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_30);
  v7 = *(uint32_t *)dword_8F8520;
  pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, pThis_34);
  v9 = *(uint32_t *)dword_8F8520;
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 2);
  v11 = *(uint32_t *)(pArg2 + 4);
  if ( v11 != 0 )
    v12 = (*(uint32_t *)(pArg2 + 8) - v11) >> 3;
  else
    v12 = 0;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v12);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg3);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg4);
  for ( i = 0; ; ++i )
  {
    v14 = *(uint32_t *)(pArg2 + 4);
    if ( v14 == 0 || i >= (*(uint32_t *)(pArg2 + 8) - v14) >> 3 )
      break;
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 36))(*(uint16_t *)(8 * i + v14));
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)dword_8F8520 + 36))(*(uint16_t *)(8 * i + *(uint32_t *)(pArg2 + 4) + 4));
  }
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// 人偶浮游 AI：DOLL_FLOAT_LOOP + DOLL_CAST 播报（75L；
//   this+6556==14 大状态门 + 8620..8664 相位字段）
// ------------------------------------------------------------
// 0x5A9100 sub_5A9100
// ------------------------------------------------------------
int /*thiscall*/ sub_5A9100(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  if ( *(uint32_t *)(this + 6556) == 14 && ArgList != 14 )
  {
    sub_5A8E80((uint32_t *)this);
    if ( *(uint32_t *)(this + 8636) == 0 )
      sub_4D93D0(this);
  }
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
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
      *(uint32_t *)(this + 8636) = **(uint32_t **)(LODWORD(fArg3) + 4);
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
  int fld_e2156; // eax
  int v4; // edi
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int fld_e21562; // edx
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
      fld_e2156 = *(this + 2156);
      if ( fld_e2156 != 0 )
      {
        v4 = sub_5A8490(this, fld_e2156);
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
          fld_e21562 = *(this + 2156);
          v11 = v8;
          sub_4DC130(fld_e21562, &v10, &v11);
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
  int *pThis; // ebx
  unsigned int i; // edi
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int pObj3; // eax
  int pObj2; // esi
  int v13; // eax
  int v14; // edx
  int v15; // eax
  uint8_t v16[4]; // [esp+Ch] [ebp-2Ch] BYREF
  void *Block; // [esp+10h] [ebp-28h]
  int v18; // [esp+14h] [ebp-24h]
  int v19; // [esp+18h] [ebp-20h]
  uint32_t v20[2]; // [esp+1Ch] [ebp-1Ch] BYREF
  int v21; // [esp+24h] [ebp-14h]
  int *pThis2; // [esp+28h] [ebp-10h]
  int v23; // [esp+34h] [ebp-4h]

  pThis = this;
  pThis2 = this;
  Block = nullptr;
  v18 = 0;
  v19 = 0;
  v23 = 0;
  for ( i = 0; ; ++i )
  {
    v3 = pThis[29];
    v4 = *(uint32_t *)(v3 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      pObj = *(uint32_t *)(v6 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
    {
      v8 = pThis[29];
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      pObj3 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      pObj2 = pObj3;
      if ( pObj3 != 0
        && (*(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 340))(pObj3) >= 31
         && *(int *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) <= 35
         || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 340))(pObj2) == 3001) )
      {
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);
        v14 = *pThis;
        v21 = v13;
        v15 = (*(int (/*thiscall*/ **)(int *))(v14 + 376))(pThis);
        pThis = pThis2;
        if ( v21 == v15 && (*(uint8_t (/*thiscall*/ **)(int *, int))(*pThis2 + 1244))(pThis2, pObj2) != 0 )
        {
          v20[0] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 48))(pObj2);
          v20[1] = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 52))(pObj2);
          sub_474950(v20);
        }
      }
    }
  }
  sub_5A8FF0(pThis, (int)v16, 50, 5000);
  pThis[2158] = sub_699000((int)(pThis + 9));  // 【clock_now(clk)】
  if ( Block != nullptr )
    j__free(Block);
}



// 人偶字段群（this+8600/8620/8648/8668）
// ------------------------------------------------------------
// 0x5A95A0 sub_5A95A0
// ------------------------------------------------------------
void /*thiscall*/ sub_5A95A0(void *this, int nArg2)
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
  sub_430C80(nullptr, 1, (int)&nArg2);
  (*(void (/*thiscall*/ **)(void *, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, v3, 0, 0);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x5A9620 sub_5A9620
// ------------------------------------------------------------
void /*thiscall*/ sub_5A9620(int this)
{
  unsigned int fld_2198; // eax
  int fld_1C54; // ecx

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (fld_2198 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(fld_2198) > *(uint32_t *)(this + 8600)) )
    {
      if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 2 )
      {
        sub_5A95A0((void *)this, 1);
      }
      else if ( *(uint32_t *)(this + 8668) == 1 )
      {
        fld_1C54 = *(uint32_t *)(this + 7252);
        if ( fld_1C54 != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1C54 + 776))(fld_1C54, 7) == 0
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
  unsigned int fld_2198; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (fld_2198 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(fld_2198) > *(uint32_t *)(this + 8600)) )
    {
      if ( *(uint32_t *)(this + 8668) == 2 && rand() % 100 < 2 )
      {
        sub_5A95A0((void *)this, 1);
      }
      else if ( *(uint32_t *)(this + 8624) != 0
             && rand() % 100 < 15
             && *(uint32_t *)(this + 8632) + 5000 < (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
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
  unsigned int fld_2198; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (fld_2198 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(fld_2198) > *(uint32_t *)(this + 8600)) )
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
  unsigned int fld_2198; // eax
  int fld_1C54; // ecx

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (fld_2198 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(fld_2198) > *(uint32_t *)(this + 8600)) )
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
        fld_1C54 = *(uint32_t *)(this + 7252);
        if ( fld_1C54 != 0
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_1C54 + 776))(fld_1C54, 7) == 0
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
  unsigned int fld_2198; // eax
  int fld_21DC; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 0 )
  {
    if ( *(uint8_t *)(this + 8620) != 0
      || (fld_2198 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this), sub_41A5E0(fld_2198) > *(uint32_t *)(this + 8600)) )
    {
      fld_21DC = *(uint32_t *)(this + 8668);
      if ( (fld_21DC == 2 || fld_21DC == 1) && rand() % 100 < 20 )
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
int /*usercall*/ sub_5A99C0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *v6; // eax
  int v7; // eax
  int pObj; // edi
  uint64_t v9; // rax
  int v10; // edi
  int v11; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    if ( pArg1[2163] == 0 )
    {
      pMem = operator new(0x12Cu);
      if ( pMem != nullptr )
        v6 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/StoneBubble.ptl", 0);
      else
        v6 = nullptr;
      pArg1[2163] = v6;
    }
    v7 = pArg1[1813];
    if ( v7 != 0 )
    {
      pObj = pArg1[2163];
      v9 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t, int))*(uint32_t *)(*pArg1 + 164))(pArg1, v7, 0, nArg2);
      *(uint32_t *)((*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 28))(pObj, HIDWORD(v9)) + 72) = v9;
    }
    else
    {
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pArg1[2163] + 28))(pArg1[2163], nArg3) + 72) = pArg1[2162];
    }
    v10 = *pArg1;
    v11 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1[2163] + 28))(
            pArg1[2163],
            0,
            15,
            0,
            55,
            1,
            0,
            0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v10 + 580))(pArg1, 48010, 0, v11);
  }
  return result;
}



// 石泡技能 2：PassiveObject/Common/Particle/StoneBubble.ptl（54L）
// ------------------------------------------------------------
// 0x5A9AC0 sub_5A9AC0
// ------------------------------------------------------------
int /*usercall*/ sub_5A9AC0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *v6; // eax
  int v7; // eax
  int pObj; // edi
  uint64_t v9; // rax
  int v10; // edi
  int v11; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    if ( pArg1[2163] == 0 )
    {
      pMem = operator new(0x12Cu);
      if ( pMem != nullptr )
        v6 = sub_428F30(pMem, (int)"PassiveObject/Common/Particle/StoneBubble.ptl", 0);
      else
        v6 = nullptr;
      pArg1[2163] = v6;
    }
    v7 = pArg1[1813];
    if ( v7 != 0 )
    {
      pObj = pArg1[2163];
      v9 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t, int))*(uint32_t *)(*pArg1 + 164))(pArg1, v7, 0, nArg2);
      *(uint32_t *)((*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 28))(pObj, HIDWORD(v9)) + 72) = v9;
    }
    else
    {
      *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)pArg1[2163] + 28))(pArg1[2163], nArg3) + 72) = pArg1[2162];
    }
    v10 = *pArg1;
    v11 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)pArg1[2163] + 28))(
            pArg1[2163],
            0,
            15,
            0,
            55,
            1,
            0,
            0);
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(v10 + 580))(pArg1, 48014, 0, v11);
  }
  return result;
}



// AI 相位辅助（52L）
// ------------------------------------------------------------
// 0x5A9BC0 sub_5A9BC0
// ------------------------------------------------------------
int /*usercall*/ sub_5A9BC0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>)
{
  int result; // eax
  uint32_t *v4; // edi

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1);
  if ( result == 14 )
  {
    v4 = (uint32_t *)pDwArg1[1554];
    result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
    if ( result == *v4 )
    {
      if ( pDwArg1[2160] == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148) == 6 )
      {
        switch ( pDwArg1[2159] )
        {
          case 0:
            sub_5A8880(pDwArg1);
            break;
          case 1:
            (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 1308))(pDwArg1);
            break;
          case 2:
            sub_5A9410(pDwArg1);
            break;
          case 3:
            sub_5A8ED0(pDwArg1);
            break;
          case 4:
            sub_5A99C0(pDwArg1, nArg2, (int)v4);
            break;
          case 5:
            sub_5A9AC0(pDwArg1, nArg2, (int)v4);
            break;
          default:
            break;
        }
        pDwArg1[2160] = 1;
      }
      result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
      if ( *(uint8_t *)(result + 170) != 0 )
        return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);
    }
  }
  return result;
}



// 技能播报：JEWEL_HIT（宝石命中）+ SWING_SHORT + STONE_DMG（65L）
// ------------------------------------------------------------
// 0x5A9CA0 sub_5A9CA0
// ------------------------------------------------------------
char /*usercall*/ sub_5A9CA0@<al>(int pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax

  sub_4E1780((uint32_t *)pArg1);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )
    sub_5A9BC0((int *)pArg1, nArg2);
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);
  if ( v3 == 8 )
  {
    if ( sub_41A5E0(pArg1 + 7028) != 0 )
    {
      v3 = sub_41A5E0(pArg1 + 7028);
      if ( v3 == 1 )
      {
        v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);
        if ( *(uint32_t *)(v3 + 148) == 3 )
        {
          LOBYTE(v3) = *(uint8_t *)(pArg1 + 8664);
          if ( (uint8_t)v3 == 0 )
          {
            LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
                           pArg1,
                           "JEWEL_HIT",
                           -1,
                           0,
                           0);
            *(uint8_t *)(pArg1 + 8664) = 1;
          }
        }
      }
    }
    else
    {
      if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 1 && *(uint8_t *)(pArg1 + 8664) == 0 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "SWING_SHORT",
          -1,
          0,
          0);
        *(uint8_t *)(pArg1 + 8664) = 1;
      }
      v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);
      if ( *(uint32_t *)(v3 + 148) == 6 && *(uint8_t *)(pArg1 + 8664) == 1 )
      {
        LOBYTE(v3) = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
                       pArg1,
                       "STONE_DMG",
                       -1,
                       0,
                       0);
        *(uint8_t *)(pArg1 + 8664) = 0;
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
  void *pMem; // eax
  char *v3; // eax
  int v4; // edx
  int pObj; // eax
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
  int fld_e1821; // edi
  int fld_e1820; // edi
  int fld_e18202; // eax
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
  sub_4015C0((void *)v28, v29);  // 【std::string构造赋值】
  sub_4015C0("DOLL_DIE", 8u);  // 【std::string构造赋值】
  pMem = operator new(0x544u);
  Block = pMem;
  v32 = 0;
  if ( pMem != nullptr )
    v3 = sub_4BA9E0((char *)pMem, "Monster/DollMaster/DollMaster.equ", 0);
  else
    v3 = nullptr;
  v4 = *this;
  v32 = -1;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(v4 + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
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
  fld_e1821 = *(this + 1821);
  Block = v16;
  fld_e1820 = fld_e1821 - *(this + 1820);
  fld_e18202 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3) - *(this + 1820);
  *(float *)&v27 = (float)(int)Block;
  v26 = (float)v31;
  *(this + 2161) = (uint64_t)sub_4049C0(v26, *(float *)&v27, fld_e18202, fld_e1820);
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
  sub_4015C0("R_DOLL_AMB", 0xAu);  // 【std::string构造赋值】
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
  int fld_e81; // edi
  uint32_t *fld_e28; // edi

  fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  if ( fld_e81 != 0 )
  {
    sub_495890(0, fld_e81 <= 0 ? 1000 : -1000);
    sub_4A0550(fld_e81);
    return sub_4A0600(2);
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
    return sub_495890(2, 0);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AA0A0 sub_5AA0A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA0A0(void *this, int nArg2)
{
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax
  int v7; // esi
  int v8; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
  v3 = *(uint32_t *)dword_8F8520;
  pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);
  v5 = *(uint32_t *)dword_8F8520;
  pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);
  v7 = *(uint32_t *)dword_8F8520;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg2);
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// AI 字段访问（this+8700/8701）
// ------------------------------------------------------------
// 0x5AA130 sub_5AA130
// ------------------------------------------------------------
int /*thiscall*/ sub_5AA130(uint8_t *this, int nArg2, int nArg3, int nArg4)
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
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AA190 sub_5AA190
// ------------------------------------------------------------
char /*thiscall*/ sub_5AA190(uint32_t *this, signed int nArg2, char pszArg3)
{
  int fld_e1813; // eax
  int v5; // edi

  fld_e1813 = *(this + 1813);
  if ( fld_e1813 == 0 )
    return 0;
  v5 = (*(int (**)(void))(*(uint32_t *)fld_e1813 + 120))();
  if ( (int)abs32(v5 - (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this)) > nArg2 )
    return 0;
  if ( pszArg3 != 0 && (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) <= 1 )
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
int /*thiscall*/ sub_5AA200(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // eax
  float v9; // [esp+0h] [ebp-1Ch]
  float pThis_2E0; // [esp+24h] [ebp+8h]
  int v11; // [esp+2Ch] [ebp+10h]

  if ( (uint8_t)nArg4 == 0 && *(this + 8608) == 1 )
  {
    pThis_2E0 = (float)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 736))(this);
    v11 = 15;
    if ( (double)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 740))(this) * 0.5 <= pThis_2E0 )
      v11 = 5;
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    if ( pObj != 0 )
    {
      v9 = (float)v11;
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int, uint32_t))(*(uint32_t *)pObj + 760))(pObj, 1, LODWORD(v9), 3, nArg2, 0);
    }
  }
  return sub_5AA130(this, nArg2, nArg3, nArg4);
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
    result = sub_699000((int)(this + 9)) - *(this + 2194);  // 【clock_now(clk)】
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
int /*thiscall*/ sub_5AC200(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1813; // edi
  int result; // eax
  int nRand; // eax
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
  if ( ArgList == 8 && *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) == 1 )
  {
    fld_e1813 = *(this + 1813);
    if ( fld_e1813 != 0 )
    {
      v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      if ( (signed int)abs32((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813) - v21) < *(uint32_t *)(*(this + 1905) + 16) )
        *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4) = 0;
    }
  }
  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
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
          nRand = rand();
          v10 = nRand % 100;
          result = nRand / 100;
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
  int fld_e2151; // edi
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
    fld_e2151 = **(this + 2151);
    v8 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[32])(this) + 43;
    v7 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[31])(this);
    v3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[38])(this) != 1 ? -47 : 47;
    v6 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[30])(this) + v3;
    (*(void (/*thiscall*/ **)(uint32_t))(fld_e2151 + 40))(*(this + 2151));
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 2151) + 92))(*(this + 2151), v9);
    v4 = (int)*this;
    v11 = 0;
    v5 = (void *)(*(int (/*thiscall*/ **)(uint32_t **, int, uint32_t, uint8_t *))(v4 + 80))(this, 2, 0, v9);
    sub_4600B0(v5, v6, v7, v8);
    if ( Block != nullptr )
      j__free(Block);
  }
  else if ( sub_699000((int)(this + 2153)) > 0 )  // 【clock_now(clk)】
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
  sub_4015C0((void *)v13, v14);  // 【std::string构造赋值】
  sub_4015C0("FLYDRAGON_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("FLYDRAGON_DIE", 0xDu);  // 【std::string构造赋值】
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
  sub_4015C0("FLYDRAGON_CRY", 0xDu);  // 【std::string构造赋值】
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
      if ( *(uint32_t *)(this + 8608) + 1000 <= (unsigned int)sub_699000(this + 7640) )  // 【clock_now(clk)】
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
  int nRand2; // eax
  int v5; // et2
  int nRand; // eax
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
      nRand = rand();
      v7 = nRand % 100;
      result = nRand / 100;
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
        nRand2 = rand();
        v5 = nRand2 % 100;
        result = nRand2 / 100;
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
  uint32_t *Block2; // ecx
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
    Block2 = Block;
    if ( Block != nullptr )
    {
      v3 = v19;
      if ( (v19 - (int)Block) >> 2 != 0 )
      {
        v4 = 0;
        while ( Block2 != nullptr )
        {
          if ( v4 >= (v3 - (int)Block2) >> 2 )
            goto LABEL_21;
          v5 = (int *)Block2[v4];
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
          Block2 = Block;
          ++v4;
        }
      }
      else
      {
LABEL_21:
        j__free(Block2);
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
  int nRand; // edi
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
              && (nRand = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v15 + 4 * i) + 120))(*(uint32_t *)(v15 + 4 * i)),
                  (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - nRand < 300)
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
int /*thiscall*/ sub_5ACCB0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int nArg22; // edi
  int pObj; // eax
  void *pBuf[4]; // [esp+8h] [ebp-20h] BYREF
  int v9; // [esp+18h] [ebp-10h] BYREF
  int v10; // [esp+24h] [ebp-4h]

  nArg22 = nArg2;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 1
    && (uint8_t)nArg4 == 0
    && sub_41A5E0((unsigned int)(this + 1757)) == 1 )
  {
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    if ( pObj != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int, uint32_t *, uint32_t))(*(uint32_t *)pObj + 760))(
        pObj,
        3,
        1120403456,
        2,
        this,
        0);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t *, uint32_t))(*this + 764))(this, 3, 2, this, 0);
        *(this + 2151) = sub_699000((int)(this + 9)) + 10000;
        memset(&pBuf[1], 0, 12);
        v10 = 0;
        v9 = 4;
        sub_431230((int)pBuf, &v9);
        v9 = 0;
        sub_431230((int)pBuf, &v9);
        v9 = 1;
        sub_431230((int)pBuf, &v9);
        v9 = 200;
        sub_431230((int)pBuf, &v9);
        v9 = 200;
        sub_431230((int)pBuf, &v9);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 4, pBuf, 0, 0);
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
        v10 = -1;
        sub_5E5260(pBuf);
        nArg22 = nArg2;
      }
    }
  }
  return sub_5AA130(this, nArg22, nArg3, nArg4);
}



// 飞龙装载 2：FLYDRAGON_HIT/DMG + FDRG_DIE 语音 + Particle/FireBreath.ptl 火息粒子（41L）
// ------------------------------------------------------------
// 0x5ACE30 sub_5ACE30
// ------------------------------------------------------------
int /*thiscall*/ sub_5ACE30(char *this)
{
  int v2; // eax
  int *pThis_16C; // eax
  int v4; // edx
  int v6; // [esp+8h] [ebp-10h] BYREF
  int v7; // [esp+14h] [ebp-4h]

  sub_4015C0("FLYDRAGON_HIT", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("FLYDRAGON_DMG", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("FDRG_DIE", 8u);  // 【std::string构造赋值】
  v2 = *(uint32_t *)this;
  *(this + 8600) = 0;
  (*(void (/*thiscall*/ **)(char *))(v2 + 688))(this);
  sub_4EB2C0(1.5);
  v7 = 0;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      pThis_16C = (int *)sub_4C3640(this + 364, "Particle/FireBreath.ptl", this);
    else
      pThis_16C = (int *)sub_4C3640(*((uint32_t *)this + 91), "Particle/FireBreath.ptl", this);
  }
  else
  {
    pThis_16C = nullptr;
  }
  *((uint32_t *)this + 2151) = pThis_16C;
  v4 = *pThis_16C;
  v7 = -1;
  (*(void (/*thiscall*/ **)(int *, char *))(v4 + 112))(pThis_16C, this);
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
int /*thiscall*/ sub_5ACF60(void *this, void *pArg2)
{
  int result; // eax

  result = sub_4D9170(pArg2);
  if ( this == pArg2 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 9);
  return result;
}



// AI 相位辅助（63L）
// ------------------------------------------------------------
// 0x5ACF90 sub_5ACF90
// ------------------------------------------------------------
int /*usercall*/ sub_5ACF90@<eax>(uint32_t **pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
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
  if ( pArg1[1787] != (uint32_t *)16 )
  {
    if ( pArg1[1813] != nullptr )
    {
      ((void (/*thiscall*/ *)(uint32_t **, int))(*pArg1)[276])(pArg1, 5);
      result = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[77])(pArg1);
      if ( (uint8_t)result != 0 )
      {
        result = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[210])(pArg1);
        if ( result == 6 )
        {
          v5 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1[1813] + 120))(pArg1[1813], nArg3, nArg2);
          v6 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[30])(pArg1);
          v7 = pArg1[1813];
          v8 = abs32(v6 - v5);
          v13 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[31])(pArg1);
          v9 = v13 - (*(int (/*thiscall*/ **)(uint32_t *))(*v7 + 124))(v7);
          v10 = (HIDWORD(v9) ^ v9) - HIDWORD(v9);
          v14 = 4;
          v15 = 4;
          if ( v8 > 100 )
          {
            v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1[1813] + 120))(pArg1[1813]);
            v14 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[30])(pArg1) < v11;
          }
          if ( v10 > 100 )
          {
            v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1[1813] + 124))(pArg1[1813]);
            v15 = (((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[31])(pArg1) < v12) + 2;
          }
          return ((int (/*thiscall*/ *)(uint32_t **, int, int))(*pArg1)[224])(pArg1, v14, v15);
        }
      }
    }
    else
    {
      return ((int (/*thiscall*/ *)(uint32_t **, int))(*pArg1)[276])(pArg1, 13);
    }
  }
  return result;
}



// 【vmt200 命中处理器覆写】猎人系小型覆写（13L；虚表 0x6DF754/0x6DFC7C/0x6E01A4/0x6E06CC 四张 +512 槽）
// ------------------------------------------------------------
// 0x5AD0B0 sub_5AD0B0
// ------------------------------------------------------------
int /*stdcall*/ sub_5AD0B0(int nArg1, int nArg2, int nArg3)
{
  if ( (uint8_t)nArg3 == 1 )
    return 0;
  else
    return sub_4DA3B0(nArg1, nArg2, nArg3);
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
int /*thiscall*/ sub_5AD130(void *this, int nArg2)
{
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int nRand; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
  v3 = *(uint32_t *)dword_8F8520;
  pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);
  v5 = *(uint32_t *)dword_8F8520;
  pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);
  v7 = *(uint32_t *)dword_8F8520;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg2);
  if ( (uint16_t)nArg2 >= 0xEu && (uint16_t)nArg2 <= 0xFu )
  {
    v9 = *(uint32_t *)dword_8F8520;
    nRand = rand();
    (*(void (/*thiscall*/ **)(int, int))(v9 + 40))(dword_8F8520, nRand);
  }
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// 技能播报：HUNTER_SPIT（吐酸）
// ------------------------------------------------------------
// 0x5AD1E0 sub_5AD1E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD1E0(int *this, int nArg2)
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
    nArg2,
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
  int nRand; // eax
  int v4; // et2
  int nRand2; // eax
  int v6; // et2

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v4 = nRand % 100;
    result = nRand / 100;
    if ( v4 >= 10 )
    {
      if ( *(this + 1943) == 3 )
      {
        nRand2 = rand();
        v6 = nRand2 % 100;
        result = nRand2 / 100;
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
int /*thiscall*/ sub_5AD3E0(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(this + 1899) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD450 sub_5AD450
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD450(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int v4; // esi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(this + 1899) = 50;
  return result;
}



// 瞄准 AI：HUNTER_READY 播报（this+200/8604-8606 相位, 28L）
// ------------------------------------------------------------
// 0x5AD4C0 sub_5AD4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD4C0(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1550) + 4 * ((nArg3 != 14) + 2)));
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  sub_4926A0(v4);
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "HUNTER_READY",
             -1,
             0,
             0);
  *(this + 2154) = nArg3;
  *((uint8_t *)this + 8604) = 1;
  *((uint8_t *)this + 8606) = 0;
  *((uint8_t *)this + 8605) = 0;
  *(this + 2152) = 0;
  *(this + 2153) = nArg2;
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
  int pThis_C8; // eax
  int pThis_24C; // eax

  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) == 6
    && *(uint8_t *)(this + 8605) == 0 )
  {
    sub_5AD550((int **)this);
    *(uint8_t *)(this + 8605) = 1;
  }
  pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
  if ( *(uint32_t *)(pThis_C8 + 148) == 6 )
  {
    LOBYTE(pThis_C8) = *(uint8_t *)(this + 8606);
    if ( (uint8_t)pThis_C8 == 0 )
    {
      pThis_24C = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(this, "Particle/HunterSpittle.ptl");
      LOBYTE(pThis_C8) = sub_5AD1E0((int *)this, pThis_24C);
      *(uint8_t *)(this + 8606) = 1;
    }
  }
  return pThis_C8;
}



// 酸液弹 2：Particle/HunterSpittle.ptl（67L；this+200/8605/8606/8608）
// ------------------------------------------------------------
// 0x5AD610 sub_5AD610
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD610(int this)
{
  int *v2; // eax
  uint16_t *pThis_24C; // eax
  int fld_21A0; // edx
  int pThis_C8; // eax
  int fld_21A02; // ecx
  int fld_1C54; // esi
  int result; // eax
  int fld_1C542; // esi
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
    pThis_24C = (uint16_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)this + 588))(this, "Particle/HunterSpittle.ptl");
    qmemcpy(v12, pThis_24C, 0x60u);
    fld_21A0 = v10[*(uint32_t *)(this + 8608)];
    LOWORD(v12[24]) = pThis_24C[48];
    v12[18] = fld_21A0;
    sub_5AD1E0((int *)this, (int)v12);
    *(uint8_t *)(this + 8606) = 1;
  }
  pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
  fld_21A02 = *(uint32_t *)(this + 8608);
  if ( *(uint32_t *)(pThis_C8 + 148) == v11[fld_21A02] + 1 )
  {
    *(uint8_t *)(this + 8606) = 0;
    *(uint32_t *)(this + 8608) = fld_21A02 + 1;
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) == 0 )
  {
    fld_1C54 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < fld_1C54 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 144))(this, 1);
  }
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
  if ( result == 1 )
  {
    fld_1C542 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
    if ( result >= fld_1C542 )
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
  int fld_e1813; // edi

  result = *(this + 1813);
  *(uint8_t *)(*(this + 1905) + 32) = result != 0
                                 && *((uint8_t *)this + 8621) == 1
                                 && (fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813)),
                                     (signed int)(result = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - fld_e1813)) < *(this + 2150));
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD7E0 sub_5AD7E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD7E0(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(uint8_t *)(*(this + 1905) + 96) = 0;
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(this + 1899) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD850 sub_5AD850
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD850(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(uint8_t *)(*(this + 1905) + 96) = 1;
  }
  result = nArg2;
  if ( nArg2 == 0 )
    *(this + 1899) = 50;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AD8C0 sub_5AD8C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AD8C0(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int v4; // edi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) - 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = nArg2;
  if ( nArg2 != 0 )
  {
    if ( nArg2 > 0 && nArg2 <= 2 )
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
int /*thiscall*/ sub_5AD950(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int v4; // esi
  int v5; // edx
  int result; // eax
  int v7; // [esp+10h] [ebp+Ch]

  if ( nArg3 == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v4)) + 1.0;
    sub_41A590(v4, v5, v7);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  result = nArg2;
  if ( nArg2 != 0 )
  {
    if ( nArg2 > 0 && nArg2 <= 2 )
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
  int pThis_348; // eax
  int pThis_21B4; // eax

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
  pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( pThis_348 != 0
    || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this) == 4
    && (pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 188))(this)) == 4 )
  {
    if ( *(uint8_t *)(this + 8622) == 1 )
    {
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 9);
      *(uint8_t *)(this + 8622) = 0;
    }
  }
  else
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8622);
    if ( (uint8_t)pThis_348 == 0 )
    {
      if ( *(uint32_t *)(this + 8648) < 0x10u )
        pThis_21B4 = this + 8628;
      else
        pThis_21B4 = *(uint32_t *)(this + 8628);
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, pThis_21B4, 9, 0, 0);
      *(uint8_t *)(this + 8622) = 1;
    }
  }
  return pThis_348;
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
  sub_4015C0("HUNTER_FIND", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("HUNTER_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("HUNTER_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("HUNTER_ATK", 0xAu);  // 【std::string构造赋值】
  *(uint8_t *)(this + 8622) = 0;
  result = sub_4015C0("HUNT_BREATH_LOOP", 0x10u);  // 【std::string构造赋值】
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
    sub_4015C0("HUNT_HARD_BREATH_LOOP", 0x15u);  // 【std::string构造赋值】
  return sub_5AD9E0((int)this);
}



// 扑跳 AI：HUNT_JUMP 播报（43L；sub_431230 参数打包）
// ------------------------------------------------------------
// 0x5ADC00 sub_5ADC00
// ------------------------------------------------------------
void /*thiscall*/ sub_5ADC00(uint8_t *this)
{
  int pThis_2A0; // edi
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
    pThis_2A0 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 672))(this, 3);
    v9[0] = sub_41A5E0(pThis_2A0 + 928);
    v3 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 942));
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
void /*thiscall*/ sub_5ADCF0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1639; // eax
  int fld_e1813; // ecx
  int v8; // edi
  BOOL v9; // edi
  int fld_e18132; // ebx
  int v11; // eax

  fld_e1639 = *(this + 1639);
  if ( fld_e1639 == 6 )
  {
    if ( ArgList == 0 )
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1312))(this);
  }
  else if ( fld_e1639 == 8 && (sub_41A5E0((unsigned int)(this + 1757)) == 2 || sub_41A5E0((unsigned int)(this + 1757)) == 3) )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
  }
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 6 )
  {
    fld_e1813 = *(this + 1813);
    if ( fld_e1813 != 0 )
    {
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) < v8;
      fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, BOOL, int))(*this + 896))(this, v9, (v11 < fld_e18132) + 2);
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
void /*thiscall*/ sub_5ADF00(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v6; // edi
  uint64_t v7; // rax
  int v8; // edi
  int v9; // eax
  int v10; // [esp+1Ch] [ebp+14h]

  sub_5ADCF0(this, ArgList, fArg3, nArg4, nArg5);
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
int /*usercall*/ sub_5ADFE0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>)
{
  char *pMem; // eax
  char *v4; // eax
  int pObj; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj3; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj2; // eax
  char *pMem4; // eax
  char *v13; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Hunter/HH/horn.equ", 0);
  else
    v4 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(int, char *, int))(*(uint32_t *)pArg1 + 784))(pArg1, v4, nArg2);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/Hunter/HH/hair.equ", 0);
  else
    v7 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v7);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v10 = sub_4BA9E0(pMem3, "Monster/Hunter/HH/clothes.equ", 0);
  else
    v10 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v10);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v13 = sub_4BA9E0(pMem4, "Monster/Hunter/HH/claws.equ", 0);
  else
    v13 = nullptr;
  result = (*(int (/*thiscall*/ **)(int, char *))(*(uint32_t *)pArg1 + 784))(pArg1, v13);
  if ( result != 0 )
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  *(uint32_t *)(pArg1 + 8652) = 0;
  *(uint8_t *)(pArg1 + 8621) = 1;
  *(uint32_t *)(pArg1 + 8600) = 150;
  *(uint32_t *)(pArg1 + 7576) = 2;
  return result;
}



// HM 猎人装载：Monster/Hunter/HM/{horn,hair,clothes}.equ（this+8621 相位）
// ------------------------------------------------------------
// 0x5AE160 sub_5AE160
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE160(uint8_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  int pThis_310; // eax
  char *pMem2; // eax
  char *v6; // eax
  int pThis_3102; // eax
  char *pMem3; // eax
  char *v9; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Hunter/HM/horn.equ", 0);
  else
    v3 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Hunter/HM/hair.equ", 0);
  else
    v6 = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Hunter/HM/clothes.equ", 0);
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
  char *pMem; // eax
  char *v3; // eax
  int pThis_310; // eax
  char *pMem2; // eax
  char *v6; // eax
  int pThis_3102; // eax
  char *pMem3; // eax
  char *v9; // eax
  int result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Hunter/HA/horn.equ", 0);
  else
    v3 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Hunter/HA/clothes.equ", 0);
  else
    v6 = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(uint8_t *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Hunter/HA/blindfold.equ", 0);
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
int /*thiscall*/ sub_5AE3C0(uint32_t *this, int pArg2)
{
  int v2; // eax

  v2 = *(this + pArg2 + 4);
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
  uint32_t *pThis_870; // ecx

  *(this + 2150) = 0;
  *(this + 2151) = 0;
  *(this + 2158) = 0;
  pThis_870 = this + 2160;
  *pThis_870 = 0;
  pThis_870[1] = 0;
  pThis_870[2] = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE410 sub_5AE410
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE410(void *this, int nArg2)
{
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int nRand; // eax

  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
  v3 = *(uint32_t *)dword_8F8520;
  pThis_30 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
  (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);
  v5 = *(uint32_t *)dword_8F8520;
  pThis_34 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 52))(this);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);
  v7 = *(uint32_t *)dword_8F8520;
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
  (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg2);
  v9 = *(uint32_t *)dword_8F8520;
  nRand = rand();
  (*(void (/*thiscall*/ **)(int, int))(v9 + 40))(dword_8F8520, nRand);
  return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
}



// 技能播报：ZOMBIE_EYEPULL（抠眼, 31L）
// ------------------------------------------------------------
// 0x5AE4B0 sub_5AE4B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5AE4B0(uint32_t *this, int nArg2)
{
  int v3; // eax

  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
    this,
    30004,
    *(this + 2157),
    nArg2,
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
int /*usercall*/ sub_5AE510@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int pObj; // ecx
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

  pObj = pArg1[2150];
  if ( pObj == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj) == 9 )
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )
      {
        v4 = *pArg1;
        v17 = 0.0;
        v18 = 0.0;
        v19 = 0.0;
        v20 = 0;
        v21 = 0;
        v22 = 0;
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 152))(pArg1) != 0 )
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 40;
        else
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 40;
        v23 = v5;
        v6 = (double)v5;
        v7 = *pArg1;
        v17 = v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 124))(pArg1);
        v9 = *pArg1;
        v23 = v8;
        v18 = (float)v8;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(pArg1);
        v11 = pArg1[2150];
        v23 = v10;
        v19 = (float)v10;
        sub_4E5F70(nArg2, (int)pArg1, v11, &v17, 1, 1);
      }
      v12 = pArg1[2152];
      v13 = pArg1[2151] + 1;
      pArg1[2151] = v13;
      if ( v13 >= v12
        || (v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2150] + 684))(pArg1[2150]), sub_41A5E0(v14) <= 0) )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "ZOMBIE_BITE", -1, 0, 0);
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
        sub_4926A0(v15);
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2150] + 604))(pArg1[2150], 0);
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2150] + 612))(pArg1[2150], 1, 1);
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2150] + 840))(pArg1[2150]);
    if ( result != 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2150] + 308))(pArg1[2150]);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2150] + 560))(
                 pArg1[2150],
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
int /*thiscall*/ sub_5AE6E0(int this, int nArg2, int nArg3)
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
  int pThis_180; // edi
  int pThis_1802; // ebx
  int pObj; // eax
  int v6; // [esp+0h] [ebp-20h]
  int pThis_1803; // [esp+10h] [ebp-10h]

  sub_4DE410();
  (*(void (/*thiscall*/ **)(void *, void *))(*(uint32_t *)this + 700))(this, this);
  sub_53F6A0(v6);
  pThis_180 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 2);
  pThis_1802 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 3);
  pThis_1803 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 384))(this, 4);
  if ( operator new(0x88u) != nullptr )
    pObj = sub_649CF0(pThis_1802, pThis_1803, pThis_180);
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
int /*thiscall*/ sub_5AE850(int *this, int nArg2)
{
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v8; // [esp+Ch] [ebp-4h]
  bool v9; // [esp+1Bh] [ebp+Bh]

  v9 = *(uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3) > nArg2;
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
  v8 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this);
  (*(void (/*thiscall*/ **)(int *, int, const char *))(*this + 1024))(this, nArg2, "zombie/Kalkazak.mob");
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
  int pThis_304; // eax

  sub_4D9760();
  (*(void (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 768))(this, 9, 10, 0);
  pThis_304 = (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 772))(this, 9, 999999999);
  return sub_497110(pThis_304);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AE940 sub_5AE940
// ------------------------------------------------------------
int /*stdcall*/ sub_5AE940(uint32_t *uArg1, int nArg2)
{
  int result; // eax
  int v3; // esi

  result = sub_4DC390(uArg1, nArg2);
  v3 = result;
  if ( result != 3 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 20) != 0 )
    {
      return v3;
    }
    else
    {
      *uArg1 = 0;
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
void /*thiscall*/ sub_5AE990(char *this, int nArg2, int nArg3, char pszArg4)
{
  int v5; // edx
  unsigned int v6; // edi
  int v7; // edx
  int v8; // [esp+Ch] [ebp+8h]
  float v9; // [esp+14h] [ebp+10h]

  sub_4E4430(this, nArg2, nArg3, pszArg4);  // 【HP 受击处理器含 Boss 终局（研究 P35 第 31 轮）】
  if ( *(this + 8652) == 0 )
  {
    v9 = (float)nArg2;
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
  int nRand; // eax
  int result; // eax
  int v3; // et2

  sub_594370(this);
  nRand = rand();
  v3 = nRand % 100;
  result = nRand / 100;
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
  int fld_e1554; // eax
  int v3; // edx

  fld_e1554 = *(this + 1554);
  v3 = *this;
  *((uint8_t *)this + 8616) = 0;
  (*(void (/*stdcall*/ **)(uint32_t))(v3 + 208))(*(uint32_t *)(fld_e1554 + 8));
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));
}



// 僵尸眼技能：引用 Particle/ZombieEye.ptl（44L；this+6556==14 与 -15 派生条件
//   【推断：卡尔卡扎克巨大化/分身态判定】）
// ------------------------------------------------------------
// 0x5AEAB0 sub_5AEAB0
// ------------------------------------------------------------
int /*usercall*/ sub_5AEAB0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int result; // eax

  sub_4E1780((uint32_t *)pArg1);
  if ( *(uint8_t *)(pArg1 + 8616) != 0 )
  {
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1) + 148) == 6 && *(uint8_t *)(pArg1 + 8617) == 0 )
    {
      v3 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)pArg1 + 588))(pArg1, "Particle/ZombieEye.ptl");
      sub_5AE4B0((uint32_t *)pArg1, v3);
      *(uint8_t *)(pArg1 + 8617) = 1;
    }
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);
      if ( *(uint8_t *)(result + 170) != 0 )
        return sub_5AEA70((uint32_t *)pArg1);
    }
  }
  else if ( *(uint32_t *)(pArg1 + 6556) == 14 )
  {
    return sub_5AE510((uint32_t *)pArg1, nArg2);
  }
  else
  {
    result = *(uint32_t *)(pArg1 + 6556) - 15;
    if ( *(uint32_t *)(pArg1 + 6556) == 15 )
    {
      result = *(uint32_t *)(pArg1 + 120);
      if ( *(uint8_t *)(result + 170) != 0 )
        return (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 0, 0, 0, 0);
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
  int pThis_715; // ecx
  bool v3; // zf
  int pThis_86E; // eax
  int nRand; // eax
  double fld_e2159; // st7
  float v7; // [esp+0h] [ebp-Ch]
  uint32_t v8[2]; // [esp+4h] [ebp-8h]

  pThis_715 = *((uint32_t *)this + 1813);
  if ( pThis_715 != 0 )
  {
    v3 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_715 + 776))(pThis_715, 11) == 0;
    pThis_86E = *((uint32_t *)this + 2158);
    if ( v3 )
    {
      if ( pThis_86E == 1 )
      {
        (*(void (/*thiscall*/ **)(float *, uint32_t, int))(*(uint32_t *)this + 672))(this, 0, 1050253722);
        sub_4E99C0(v7);
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
        fld_e2159 = *(this + 2159) * 1.3;
        *(this + 2158) = 0.0;
        *(this + 2159) = fld_e2159;
        *(float *)(*((uint32_t *)this + 1905) + 36) = *(float *)(*((uint32_t *)this + 1905) + 36) * 0.76923078;
      }
    }
    else
    {
      if ( pThis_86E == 0 )
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
      nRand = rand() % 2;
      sub_4DB200(24, v8[nRand]);
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
int /*thiscall*/ sub_5AED10(uint32_t *this, int nArg2)
{
  int result; // eax
  int fld_e1554; // eax
  int fld_e2153; // edx
  int fld_e2150; // edi
  int fld_e21502; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2150) )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
    if ( result == 14 && (int)*(this + 2152) > 1 )
    {
      fld_e1554 = sub_491C10(*(uint32_t *)*(this + 1554));
      fld_e2153 = *(this + 2153) + 1;
      *(this + 2153) = fld_e2153;
      if ( fld_e2153 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2152);
        *(this + 2153) = 0;
      }
      fld_e2150 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 120))(*(this + 2150));
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 916))(*(this + 2150));
      fld_e21502 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2150) + 120))(*(this + 2150));
      v8 = *this;
      v9 = fld_e2150 - fld_e21502;
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
int /*thiscall*/ sub_5AEDE0(uint32_t *this, int pArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2150; // ecx
  int v6; // eax
  int fld_e21502; // ecx
  int v8; // eax
  int fld_e21503; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int fld_e21504; // ecx
  int v14; // eax
  int v15; // ebx
  int fld_e21505; // edi
  int v17; // eax
  int v18; // eax
  uint32_t *fld_e28; // edi
  int v20; // eax
  int fld_e1821; // edi
  uint32_t *v22; // eax
  uint64_t fld_e1820; // rax
  float v25; // [esp+70h] [ebp-20h]
  float v26; // [esp+74h] [ebp-1Ch]
  int v27; // [esp+8Ch] [ebp-4h]
  int v28; // [esp+98h] [ebp+8h]
  int v29; // [esp+98h] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
    || (*(this + 2150) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2150) = 0;
  }
  fld_e2150 = *(this + 2150);
  if ( fld_e2150 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2150 + 120))(fld_e2150);
    fld_e21502 = *(this + 2150);
    *(this + 2160) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21502 + 124))(fld_e21502);
    fld_e21503 = *(this + 2150);
    *(this + 2161) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21503 + 128))(fld_e21503);
    v11 = *this;
    *(this + 2162) = v10;
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v11 + 152))(this);
    fld_e21504 = *(this + 2150);
    if ( v12 != 0 )
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21504 + 120))(fld_e21504) - 40;
    else
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21504 + 120))(fld_e21504) + 40;
    v15 = *this;
    v28 = v14;
    fld_e21505 = *(this + 2150);
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21505 + 128))(fld_e21505);
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21505 + 124))(fld_e21505, v17);
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
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  v27 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v29 = v20;
  v22 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v26 = (float)v29;
  v25 = (float)v27;
  fld_e1820 = (uint64_t)sub_4049C0(v25, v26, *v22 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2152) = fld_e1820;
  LODWORD(fld_e1820) = *this;
  *(this + 2151) = 0;
  *(this + 2153) = 0;
  return (*(int (/*fastcall*/ **)(uint32_t *, uint32_t, const char *, int, uint32_t, uint32_t))(fld_e1820 + 212))(
           this,
           HIDWORD(fld_e1820),
           "HOLD",
           -1,
           0,
           0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF000 sub_5AF000
// ------------------------------------------------------------
void /*thiscall*/ sub_5AF000(int this, int nArg2)
{
  int fld_1C54; // ebx

  fld_1C54 = *(uint32_t *)(this + 7252);
  sub_4D97E0(nArg2);
  if ( fld_1C54 != nArg2 && nArg2 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0 )
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
  int pObj; // ebx
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int pObj2; // ecx
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
      pObj = *(uint32_t *)(v3 + 196);
    else
      pObj = 0;
    if ( pObj != 0 )
    {
      v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
      v7 = *(uint32_t *)(v6 + 4);
      v18 = v7 != 0 ? (*(uint32_t *)(v6 + 8) - v7) >> 2 : 0;
      if ( v18 > 0 )
      {
        do
        {
          v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
          v9 = *(uint32_t *)(v8 + 4);
          if ( v9 != 0 && v4 < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
            pObj2 = *(uint32_t *)(v9 + 4 * v4);
          else
            pObj2 = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 92))(pObj2) != 0 )
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
int /*thiscall*/ sub_5AF1C0(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1550) + 8));
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  sub_4926A0(v4);
  sub_5AECA0(this);
  *((uint8_t *)this + 8616) = 1;
  *((uint8_t *)this + 8617) = 0;
  *(this + 2156) = nArg2;
  return nArg2;
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
  int fld_e1821; // edi
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
  sub_4015C0("ZOMBIE_FIND", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("ZOMBIE_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("ZOMBIE_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("ZOMBIE_ATK", 0xAu);  // 【std::string构造赋值】
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 2);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v6 = (float)v8;
  v5 = (float)v7;
  result = (uint64_t)sub_4049C0(v5, v6, *v3 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
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
int /*thiscall*/ sub_5AF360(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 1
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
    (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 14, pBuf, 0, 0);
    v9 = -1;
    sub_5E5260(pBuf);
  }
  return sub_4DB480(pObj, nArg3, nArg4);
}



// 参数打包 AI（89L sub_431230）
// ------------------------------------------------------------
// 0x5AF460 sub_5AF460
// ------------------------------------------------------------
void /*usercall*/ sub_5AF460(int *pDwArg1@<ecx>, int nArg2@<ebx>)
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

  pObj3 = pDwArg1[2150];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2150] + 612))(pDwArg1[2150], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2150] + 136))(
           pDwArg1[2150],
           pDwArg1[2160],
           pDwArg1[2161],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2150] + 112))(pDwArg1[2150], pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);
    }
    else
    {
      pObj = pDwArg1[2150];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2160, pDwArg1 + 2161, v7);
      pObj2 = pDwArg1[2150];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2160], pDwArg1[2161], pDwArg1[2162]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2162]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2150], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2150] + 308))(pDwArg1[2150]) != 0 )
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
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2150] + 560))(pDwArg1[2150], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2150] + 564))(pDwArg1[2150]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2150] + 848))(pDwArg1[2150], 0);
    pDwArg1[2150] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF660 sub_5AF660
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF660(uint32_t *this, int nArg2, float *pArg3, int nArg4)
{
  int v5; // ebx
  int v6; // eax
  int v8; // [esp-10h] [ebp-1Ch]

  v5 = sub_5AF360(this, nArg2, (int)pArg3, nArg4);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 25 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 348))(this);
    if ( (*(uint8_t *)(v6 + 16) != 0 || *(float *)v6 > 0.0) && (uint8_t)nArg4 == 0 )
    {
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
      sub_4E4A50(this, 30320, 0, (uint64_t)*pArg3, (uint64_t)pArg3[1], (uint64_t)pArg3[2], v8, 0, 0, 0);
    }
  }
  return v5;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5AF710 sub_5AF710
// ------------------------------------------------------------
int /*userpurge*/ sub_5AF710@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2150] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
      sub_5AF460(pDwArg1, nArg2);
    pDwArg1[2150] = 0;
  }
  if ( pDwArg3 == pDwArg1 && pDwArg1[2150] != 0 )
  {
    sub_5AF460(pDwArg1, nArg2);
    pDwArg1[2150] = 0;
  }
  return sub_4D9170(pDwArg3);
}



// AI 相位辅助（102L）
// ------------------------------------------------------------
// 0x5AF770 sub_5AF770
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF770(int *this, int ArgList, int nArg3, int nArg4, int nArg5)
{
  int v5; // ebx
  int fld_e1639; // eax
  int fld_e1813; // edi
  BOOL v9; // edi
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int fld_e2150; // eax
  int v16; // ebx
  int fld_e21502; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // [esp+Ch] [ebp-4h]

  v5 = ArgList;
  fld_e1639 = *(this + 1639);
  if ( fld_e1639 != 8 )
  {
    if ( fld_e1639 == 14 )
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
    fld_e1813 = *(this + 1813);
    v22 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v9 = v22 < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
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
      sub_5AEDE0(this, nArg3);
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
        fld_e2150 = *(this + 2150);
        if ( fld_e2150 != 0 )
        {
          v16 = *this;
          fld_e21502 = *(this + 2150);
          v18 = (*(int (**)(void))(*(uint32_t *)fld_e2150 + 128))();
          v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21502 + 124))(fld_e21502, v18);
          v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21502 + 120))(fld_e21502, v19);
          (*(void (/*thiscall*/ **)(int *, int))(v16 + 112))(this, v20);
          v5 = ArgList;
        }
      }
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
      break;
    default:
      break;
  }
  result = sub_4E33D0(v5, *(float *)&nArg3, nArg4, nArg5);
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
  int (/*thiscall*/ ***fld_e2151)(uint32_t, int); // ecx
  int result; // eax
  int fld_e2154; // ecx

  fld_e2151 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2151);
  if ( fld_e2151 != nullptr )
    result = (**fld_e2151)(fld_e2151, 1);
  fld_e2154 = *(this + 2154);
  *(this + 2151) = 0;
  if ( fld_e2154 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e2154 + 84))(fld_e2154, 0);
    *(this + 2154) = 0;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AF990 sub_5AF990
// ------------------------------------------------------------
int /*thiscall*/ sub_5AF990(uint32_t *this, uint32_t *uArg2)
{
  int result; // eax

  sub_4D9170(uArg2);
  if ( this == uArg2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 9);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 12);
  }
  result = 0;
  if ( (uint32_t *)*(this + 2159) == uArg2 )
    *(this + 2159) = 0;
  if ( (uint32_t *)*(this + 2154) == uArg2 )
    *(this + 2154) = 0;
  return result;
}



// AI 字段访问（this+8600）
// ------------------------------------------------------------
// 0x5AFA00 sub_5AFA00
// ------------------------------------------------------------
int /*thiscall*/ sub_5AFA00(uint8_t *this, int *pDwArg2, int nArg3)
{
  int result; // eax

  result = sub_4DC390(pDwArg2, nArg3);
  if ( result != 3 && *(this + 8600) != 0 )
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
  int pThis_C8; // eax

  pThis_C8 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
  if ( *(uint32_t *)(pThis_C8 + 148) == 1 )
  {
    LOBYTE(pThis_C8) = *(this + 8601);
    if ( (uint8_t)pThis_C8 == 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 11);
      LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                     this,
                     "DRAGONMAN_STATIC",
                     -1,
                     0,
                     0);
      *(this + 8601) = 1;
    }
  }
  return pThis_C8;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5AFB00 sub_5AFB00
// ------------------------------------------------------------
int /*thiscall*/ sub_5AFB00(void *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // ebx
  int v6; // edi

  sub_4DB480(nArg2, nArg3, nArg4);
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 8
    || sub_41A5E0((unsigned int)this + 7028) != 1
    || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 0
    || (uint8_t)nArg4 != 0 )
  {
    return 0;
  }
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 736))(nArg2) / 3;
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 736))(nArg2) - v5;
  (*(void (/*thiscall*/ **)(int, int, uint32_t, void *))(*(uint32_t *)nArg2 + 728))(nArg2, v5, 0, this);
  if ( v6 != 0 )
    sub_4D5330(this, nArg2, nArg3, v6, v6, 1, 0, 0);
  return v6;
}


