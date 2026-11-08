// ============================================================
// 【40JP逆向源代码工程】creature/goblin_fox.cpp
// 模块: 怪物AI 0x59 —— 哥布林/狐狸(Lugaru)/魔法师(Soceress)家族
// 来源: work/dump_monster.txt  区块: 0x590000-0x5A0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 252
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：本文件 7 个函数被虚表农场
//     0x6CB000-0x6EB000 的生物子类虚表 +512 槽引用（纯 Python 直读 PE 定位，
//     同 dump_vt_farm.py 法）：0x590AD0×1表 / 0x590E90×1 / 0x591450×1 /
//     0x592920×1 / 0x5970A0×1 / 0x598430×5 / 0x599BD0×21 表（研究 20 §1.2/§14#4）
//   · AI 三层状态：this+200 主状态 / vt+560→this+616 反应态 / this+6556 大状态
//     （研究 15）；本文件未直读 6556，AI 相位以 vt+560 反应态调用为锚
//   · 语音 TAG 三件套（R_XXX_TALK/DMG/DIE）经 sub_4015C0(string assign) 写入
//     语音槽，由 vt+212(sub_499110) 播报（研究 28 音效层）
//   · sub_431230 = std::vector push_back —— 怪物 AI 用它打包 vt+560 setState
//     (sub_4E7A80 反应态写入器) 的参数表；sub_699000 = clock_now（冻结感知时钟）
//   · 资源路径逐函数标注：sub_431860/431920=.ani 动画对象装载 / sub_64B0F0=
//     CNAuraMasterChilling 光环粒子(.ptl) / sub_4BA9E0=CNRDEquipment(.equ 外观) /
//     sub_4049C0=帧间插值(研究 26)；资源 = 识别"这是哪个技能"的最强证据
// -----------------------------------------------------------
// 分区：按怪物种名组织（横幅见各分区头部；本区块实际含 15 个物种小节）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】基础人形怪：SHU / KENSIN 幻影系（0x5908C0-0x5913F0）
// 证据：KENSIN_APPEAR/Disappear 语音、Animation/IllusionDestroy*.ani 幻影消散、
//       SHU_APPEAR/DMG/DIE 语音三件套、FROZEN 冰冻播报；含本文件首个 vmt200 覆写群

// 子类状态复位：this+8600/+8604/+8605 AI 字段清零（子类 AI 数据块起始区）
// ------------------------------------------------------------
// 0x5908C0 sub_5908C0
// ------------------------------------------------------------
int /*thiscall*/ sub_5908C0(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8604) = 0;
  *(uint8_t *)(this + 8605) = 0;
  return 0;
}



// 标志复位：this+8605=0；vt+648(伤害类型槽, 研究 20 §1.2) 掩码读回
// ------------------------------------------------------------
// 0x5908E0 sub_5908E0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5908E0(int this)
{
  unsigned int result; // eax

  result = *(uint32_t *)(this + 648) & 0xFFFFFFFE;
  *(uint8_t *)(this + 8605) = 0;
  *(uint32_t *)(this + 648) = result;
  return result;
}



// AI 触发阈值装载：__RTDynamicCast→CNFighter 后 vt+1160/vt+1140(8) 取计数，
//   sub_47EF20(1,…,11) 读数据表元素(研究 17/20 平衡读数族) → 存 this+2150 供时钟门比较
// ------------------------------------------------------------
// 0x590900 sub_590900
// ------------------------------------------------------------
int /*thiscall*/ sub_590900(uint32_t *this, int nArg2)
{
  int result; // eax
  int pObj; // esi
  int v5; // eax

  sub_4D9F50(nArg2);
  result = __RTDynamicCast(nArg2, 0, &IRDActiveObject `RTTI Type Descriptor', &CNFighter `RTTI Type Descriptor', 0);
  pObj = result;
  if ( result != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 1160))(result, 8);
    v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1140))(pObj, 8);
    result = sub_47EF20(1, v5, -1, -1, 11);
    *(this + 2150) = result;
  }
  return result;
}



// 【AI 相位：出场/近身检查】KENSIN_APPEAR 播报；sub_699000 时钟 >= this+2150 门通过后
//   sub_431230 打包参数表 → vt+560(this,5,…,2) 反应态写入(研究 15 vt+560=sub_4E7A80)
// ------------------------------------------------------------
// 0x590970 sub_590970
// ------------------------------------------------------------
void /*thiscall*/ sub_590970(int *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int fld_e30; // eax
  uint8_t v6[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v8; // [esp+14h] [ebp-18h]
  int v9; // [esp+18h] [ebp-14h]
  int v10; // [esp+1Ch] [ebp-10h] BYREF
  int v11; // [esp+28h] [ebp-4h]

  sub_4E1780(this);
  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(int *, int))(v2 + 136))(this, v4) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 84))(this, 0);
    *((uint8_t *)this + 8605) = 1;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && *(this + 1639) == 0
    && sub_699000((int)(this + 16)) >= *(this + 2150) )  // 【clock_now(clk)】
  {
    Block = nullptr;
    v8 = 0;
    v9 = 0;
    v11 = 0;
    v10 = 0;
    sub_431230((int)v6, &v10);
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 5, v6, 2, 0);
    v11 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v8 = 0;
    v9 = 0;
  }
  if ( *((uint8_t *)this + 8604) == 0 )
  {
    fld_e30 = *(this + 30);
    if ( fld_e30 != 0 && *(uint8_t *)(fld_e30 + 170) != 0 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        1,
        *(uint32_t *)(*(this + 1554) + 8),
        0,
        0,
        0,
        0);
      *((uint8_t *)this + 8604) = 1;
    }
  }
  if ( *((uint8_t *)this + 8605) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "KENSIN_APPEAR", -1, 0, 0);
    *((uint8_t *)this + 8605) = 1;
  }
}



// 【vmt200 命中处理器覆写】受击处理·直接伤害版（虚表 0x6CD0EC +512 槽）：vt+348 attackinfo → vt+648 类型 →
//   vt+628 伤害公式 → vt+736 GetHP 钳制 → sub_41A5E0 防篡读(研究 17) → vt+728 HP setter
//   → sub_4D5330 DNF.trc 日志；霸体门 vt+724 内 vt+560 反应态 5(击倒)；
//   无 50% 预表现/暴击分支 —— 对照基类 0x4D71B0 全流程（研究 20 §2）
// ------------------------------------------------------------
// 0x590AD0 sub_590AD0
// ------------------------------------------------------------
int /*userpurge*/ sub_590AD0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, int nArg4, int nArg5)
{
  int nArg32; // edi
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // ebx
  int v12; // eax
  uint8_t v14[4]; // [esp+8h] [ebp-2Ch] BYREF
  void *Block; // [esp+Ch] [ebp-28h]
  int v16; // [esp+10h] [ebp-24h]
  int v17; // [esp+14h] [ebp-20h]
  int v18; // [esp+18h] [ebp-1Ch]
  int v19; // [esp+1Ch] [ebp-18h]
  int v20; // [esp+20h] [ebp-14h]
  uint32_t v21[4]; // [esp+24h] [ebp-10h] BYREF

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) == 0 || (uint8_t)nArg5 != 0 )
    return -1;
  nArg32 = nArg3;
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 348))(nArg3, nArg2);
  v8 = *pDwArg1;
  v19 = *(uint32_t *)(v7 + 60);
  LOBYTE(v21[0]) = 0;
  nArg5 = 100;
  nArg3 = 0;
  v9 = (*(int (/*thiscall*/ **)(int *, int *, int))(v8 + 648))(pDwArg1, &nArg5, nArg32);
  v10 = *pDwArg1;
  v18 = v9;
  v11 = (*(int (/*thiscall*/ **)(int *, uint32_t *, int *, int, int, int, uint32_t))(v10 + 628))(pDwArg1, v21, &nArg3, nArg5, nArg32, nArg4, 0);
  if ( v11 >= (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1) )
    v20 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 736))(pDwArg1);
  else
    v20 = v11;
  v12 = sub_41A5E0((unsigned int)(pDwArg1 + 1533));
  (*(void (/*thiscall*/ **)(int *, int, uint32_t))(*pDwArg1 + 728))(pDwArg1, v12 - v11, 0);
  if ( v11 != 0 || v19 != 0 )
    sub_4D5330(nArg32, pDwArg1, nArg4, v11, v20, v21[0], nArg3, v18);
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 724))(pDwArg1) != 0 )
  {
    Block = nullptr;
    v16 = 0;
    v17 = 0;
    v21[3] = 0;
    nArg4 = 0;
    sub_431230((int)v14, &nArg4);
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *, int, uint32_t))(*pDwArg1 + 560))(pDwArg1, 5, v14, 2, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
  return v11;
}



// 幻影消散演出：sub_431920 装载 Animation/IllusionDestroyEffect.ani + IllusionDestroy.ani，
//   vt+212 播报 KENSIN_DISAPPEAR
// ------------------------------------------------------------
// 0x590C40 sub_590C40
// ------------------------------------------------------------
int /*thiscall*/ sub_590C40(int *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // ebx
  int fld_e91; // ecx
  char *v9; // eax
  int pObj2; // edi
  int v11; // ebx
  int v12; // eax
  int fld_e912; // ecx
  int v14; // ebx
  char *v15; // eax
  int pObj; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // [esp+24h] [ebp+Ch]
  int v20; // [esp+28h] [ebp+10h]
  int v21; // [esp+2Ch] [ebp+14h]

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  v7 = 0;
  if ( ArgList == 0 )
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
             this,
             1,
             *(uint32_t *)*(this + 1554),
             0,
             0,
             0,
             0);
  if ( ArgList == 5 )
  {
    v19 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v20 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v21 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( sub_42FCB0(228) != 0 )
    {
      if ( (unsigned int)*(this + 96) < 0x10 )
        LOBYTE(fld_e91) = (uint8_t)this + 108;
      else
        fld_e91 = *(this + 91);
      v7 = sub_431920(fld_e91, (char)"Animation/IllusionDestroyEffect.ani", 1);
    }
    v9 = (char *)sub_44B6C0(284);
    pObj2 = (int)v9;
    if ( v9 != nullptr )
    {
      sub_44E0D0(v9, v7, 1);
      *(uint32_t *)pObj2 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v10 = 0;
    }
    sub_45FE80(*(this + 29), v10, 2, 0, v10, (int)this, 0);
    v11 = *(uint32_t *)v10;
    v12 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 148))(v10, v12);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 112))(v10, v19, v20, v21);
    if ( sub_42FCB0(228) != 0 )
    {
      if ( (unsigned int)*(this + 96) < 0x10 )
        LOBYTE(v13) = (uint8_t)this + 108;
      else
        v13 = *(this + 91);
      v14 = sub_431920(v13, (char)"Animation/IllusionDestroy.ani", 1);
    }
    else
    {
      v14 = 0;
    }
    v15 = (char *)sub_44B6C0(284);
    v16 = (int)v15;
    if ( v15 != nullptr )
    {
      sub_44E0D0(v15, v14, 1);
      *(uint32_t *)v16 = &CNRDPooledObject::`vftable';
    }
    else
    {
      pObj = 0;
    }
    sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);
    v17 = *(uint32_t *)pObj;
    v18 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    (*(void (/*thiscall*/ **)(int, int))(v17 + 148))(pObj, v18);
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 112))(pObj, v19, v20, v21);
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "KENSIN_DISAPPEAR",
             -1,
             0,
             0);
  }
  return result;
}



// 小型状态读取
// ------------------------------------------------------------
// 0x590E70 sub_590E70
// ------------------------------------------------------------
int /*thiscall*/ sub_590E70(uint32_t *this)
{
  *(this + 2150) = 0;
  *(this + 2151) = 0;
  *(this + 2152) = 0;
  return 0;
}



// %s冰冻系受击反应（虚表 0x6CD60C +512 槽）：格挡位 a4==0 且 attackinfo(+16 状态/+0 伤害)
//   非空 → vt+212 连播 "FROZEN"+"SHU_DMG"；尾调 sub_4DA3B0 续接基类命中流程【推断】
// ------------------------------------------------------------
// 0x590E90 sub_590E90
// ------------------------------------------------------------
int /*thiscall*/ sub_590E90(void *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // eax

  if ( (uint8_t)nArg4 == 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
    if ( *(uint8_t *)(v5 + 16) != 0 || *(float *)v5 > 0.0 )
    {
      (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "FROZEN",
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "SHU_DMG",
        -1,
        0,
        0);
    }
  }
  return sub_4DA3B0(nArg2, nArg3, nArg4);
}



// 死亡播报：a2==this 时 vt+212 广播 "SHU_DIE"（自灭/死亡确认，研究 31 死亡系统）
// ------------------------------------------------------------
// 0x590F00 sub_590F00
// ------------------------------------------------------------
int /*thiscall*/ sub_590F00(void *this, void *pArg2)
{
  int result; // eax

  result = sub_4D9170(pArg2);
  if ( pArg2 == this )
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "SHU_DIE",
             -1,
             0,
             0);
  return result;
}



// 数据表读数：sub_47EF20 容器元素读取（受击/触发阈值族）
// ------------------------------------------------------------
// 0x590F30 sub_590F30
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_590F30(int *this, int nArg2)
{
  int v3; // eax
  int v4; // edx
  unsigned int result; // eax

  sub_47E720(3, 43);
  *(this + 2150) = sub_47EF20(0, nArg2, -1, -1, 11);
  *(this + 2151) = sub_47EF20(1, nArg2, -1, -1, 11) / 2;
  v3 = sub_47EF20(2, nArg2, -1, -1, 11);
  v4 = *this;
  *(this + 2152) = v3;
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v4 + 204))(
    this,
    1,
    *(uint32_t *)*(this + 1554),
    0,
    0,
    0,
    0);
  result = *(this + 162) & 0xFFFFFFFE;
  *(this + 162) = result;
  return result;
}



// AI 字段访问（this+86xx 区）
// ------------------------------------------------------------
// 0x590FD0 sub_590FD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_590FD0(int **this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  uint32_t *result; // eax

  result = (uint32_t *)sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 0 )
  {
    sub_4926A0(**(this + 1554));
    return sub_4938F0(**(this + 1554));
  }
  return result;
}



// 【AI 相位：反应】sub_431230 参数打包 + sub_699000 时钟门 → vt+560 反应态写入
// ------------------------------------------------------------
// 0x591020 sub_591020
// ------------------------------------------------------------
void /*thiscall*/ sub_591020(uint32_t *this)
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  sub_4E1780(this);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1639) == 0
    && (sub_699000((int)(this + 16)) >= *(this + 2150) || *(this + 2088) == 0) )  // 【clock_now(clk)】
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 0;
    sub_431230((int)v2, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 5, v2, 2, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// AI 字段访问（this+86xx 区）
// ------------------------------------------------------------
// 0x5910D0 sub_5910D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5910D0(uint32_t *this, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  int pThis_1C; // eax

  sub_4B1030();
  *this = &CNRDAuraMaster::`vftable';
  sub_607240(this + 23);
  sub_607280(this + 23);
  pThis_1C = sub_433AC0(this + 28);
  *(this + 29) = pThis_1C;
  *(uint8_t *)(pThis_1C + 21) = 1;
  *(uint32_t *)(*(this + 29) + 4) = *(this + 29);
  *(uint32_t *)*(this + 29) = *(this + 29);
  *(uint32_t *)(*(this + 29) + 8) = *(this + 29);
  *(this + 30) = 0;
  sub_64A150(this);
  sub_64A160(nArg2, nArg3, nArg4, pszArg5);
  return this;
}



// 状态位读取
// ------------------------------------------------------------
// 0x591180 sub_591180
// ------------------------------------------------------------
int /*thiscall*/ sub_591180(void *this)
{
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 76))(this, 0);
}



// AI 相位辅助（35L）
// ------------------------------------------------------------
// 0x591190 sub_591190
// ------------------------------------------------------------
int /*thiscall*/ sub_591190(char *this)
{
  int result; // eax
  int v3; // [esp-8h] [ebp-28h]
  int *pThis_1D; // [esp-4h] [ebp-24h]
  uint8_t v5[4]; // [esp+Ch] [ebp-14h] BYREF
  char *pThis; // [esp+10h] [ebp-10h]
  int v7; // [esp+1Ch] [ebp-4h]

  pThis = this;
  *(uint32_t *)this = &CNRDAuraMaster::`vftable';
  v7 = 2;
  sub_64A7C0();
  v4 = *((int **)this + 29);
  v3 = *v4;
  LOBYTE(v7) = 1;
  sub_52E960(v5, v3, v4);
  j__free(*((void **)this + 29));
  *((uint32_t *)this + 29) = 0;
  *((uint32_t *)this + 30) = 0;
  LOBYTE(v7) = 0;
  nullsub_3(this + 92);
  *(uint32_t *)this = &IRDAppendage::`vftable';
  v7 = 3;
  result = sub_5F6640(this);
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &nengine::IObject::`vftable';
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x591230 sub_591230
// ------------------------------------------------------------
char */*thiscall*/ sub_591230(char *Block, char pszArg2)
{
  sub_591190(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x591260 sub_591260
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_591260(uint32_t *this, int nArg2, int nArg3)
{
  sub_5910D0(this, 0, 18, 250, 1);
  *this = &CNProvocationDollAura::`vftable';
  sub_64A930(this);
  sub_64AD30(nArg2, nArg3);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5912D0 sub_5912D0
// ------------------------------------------------------------
void */*thiscall*/ sub_5912D0(void *Block, char pszArg2)
{
  sub_591300();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x591300 sub_591300
// ------------------------------------------------------------
int /*thiscall*/ sub_591300(char *this)
{
  *(uint32_t *)this = &CNProvocationDollAura::`vftable';
  sub_64AE50();
  return sub_591190(this);
}



// 出场播报：vt+212 广播 "SHU_APPEAR"
// ------------------------------------------------------------
// 0x591350 sub_591350
// ------------------------------------------------------------
int /*thiscall*/ sub_591350(int *this)
{
  uint32_t *pMem; // eax
  uint32_t *fld_e2151; // eax

  sub_4D9760();
  pMem = operator new(0x98u);
  if ( pMem != nullptr )
    fld_e2151 = sub_591260(pMem, *(this + 2151), -*(this + 2152));
  else
    fld_e2151 = nullptr;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*fld_e2151 + 56))(
    fld_e2151,
    this,
    *(this + 2088),
    0,
    0,
    0,
    -1);
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SHU_APPEAR", -1, 0, 0);
}



// ============================================================
// 【分区 2】魔法师·凯拉哈（Soceress Keraha）（0x5913F0-0x5933A0）
// 证据：ChillingAura 冰霜光环(sub_64B0F0)、SHIELD_ICE/WINDSHIELD_LOOP 冰盾、
//       KERA_CAST/KERA_COMMAND/SOR_SPIN、Summon.ani 召唤、Particle/EnergyBall.ptl、
//       B_KERAHA_01 登场曲、R_KERA_ATK/DMG/DIE 语音 + Hair02/Cloth02/Weapon02/Acc02.equ

// 子类扩展字段复位（this+8612..8628）
// ------------------------------------------------------------
// 0x5913F0 sub_5913F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5913F0(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 1;
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint8_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8628) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x591420 sub_591420
// ------------------------------------------------------------
int /*thiscall*/ sub_591420(void *this, void *pArg2)
{
  int result; // eax

  result = sub_4D9170(pArg2);
  if ( this == pArg2 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 7818);
  return result;
}



// %s受击后置（虚表 0x6CDB2C +512 槽）：vt+1104(this,4) 动作切换 +
//   this+2155 = clock_now(this+9) 受击时间戳【推断】；尾调 sub_4DA3B0 续程
// ------------------------------------------------------------
// 0x591450 sub_591450
// ------------------------------------------------------------
int /*thiscall*/ sub_591450(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);
  if ( (uint8_t)nArg4 == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
    *(this + 2155) = sub_699000((int)(this + 9));
  }
  return v5;
}



// 攻击结算反查：vt+672(this,3) 取攻击信息 → 对 a2 vt+124 写回【推断：目标记忆 vt+356 族】
// ------------------------------------------------------------
// 0x5914A0 sub_5914A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5914A0(uint32_t *this, int nArg2)
{
  int result; // eax
  int v4; // ebx
  uint32_t *v5; // eax
  int fld_e2154; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v4 = *this;
    v5 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
    fld_e2154 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 124))(
           nArg2,
           *(this + 2154),
           *v5,
           0,
           4,
           *(this + 1908) != 0 ? 100 : 130,
           1,
           0,
           0);
    v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, fld_e2154);
    v9 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)nArg2 + 124))(nArg2, 0, v8);
    v10 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v9);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v4 + 584))(this, v10);
  }
  return result;
}



// AI 相位门（this+8624）
// ------------------------------------------------------------
// 0x591520 sub_591520
// ------------------------------------------------------------
int /*thiscall*/ sub_591520(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int v5; // edi
  int v6; // eax
  int fld_e2151; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v5 = *this;
    *(this + 2151) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 108) + 112);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 152))(
           this,
           2,
           0,
           0,
           0xFFFF,
           0,
           0,
           0,
           0);
    fld_e2151 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 376))(
           this,
           *(this + 2151),
           *(this + 2160),
           *(this + 2161),
           0,
           v6);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v5 + 592))(this, *(this + 2152), fld_e2151);
    result = *(this + 2157) + 1;
    *((uint8_t *)this + 8624) = 0;
    *(this + 2157) = result;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5915B0 sub_5915B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5915B0(void *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    if ( rand() % 100 < 50 )
      sub_4DC730(this);
    nRand = rand();
    v4 = nRand % 100;
    result = nRand / 100;
    if ( v4 < 10 )
      return (*(int (/*thiscall*/ **)(void *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
               this,
               48013,
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
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x591610 sub_591610
// ------------------------------------------------------------
int /*usercall*/ sub_591610@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // ebx
  int *v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int result; // eax
  int v14; // ecx
  int v15; // [esp-24h] [ebp-44h]
  int v16; // [esp-20h] [ebp-40h]
  uint32_t v18[5]; // [esp+8h] [ebp-18h]
  int v19; // [esp+1Ch] [ebp-4h]

  v3 = *pArg1;
  v18[0] = 3;
  v18[1] = 5;
  v18[2] = 7;
  v18[3] = 9;
  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(v3 + 200))(pArg1);
  v5 = pArg1[2159];
  if ( *(uint32_t *)(v4 + 148) == v18[v5] && pArg1[2158] == 0 )
  {
    v6 = 50 * (v5 - 2);
    if ( (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 152))(pArg1, nArg2) == 1 )
      v6 = -v6;
    v19 = *pArg1;
    v16 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(v19 + 672))(pArg1, 3);
    v7 = (int *)pArg1[1813];
    v8 = *v7;
    v15 = pArg1[2154];
    v18[4] = v7;
    v9 = (*(int (/*stdcall*/ **)(int, int, uint32_t, int, int, int, uint32_t, uint32_t))(v8 + 124))(
           v15,
           v16,
           0,
           4,
           100,
           1,
           0,
           0);
    v10 = (*(int (/*thiscall*/ **)(int *, int))(*v7 + 120))(v7, v9);
    v11 = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(*v7 + 124))(v7, 0, v10 - v6);
    v12 = (*(int (/*thiscall*/ **)(int *, int))(*v7 + 120))(v7, v11);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v19 + 584))(pArg1, v12 - v6);
    pArg1[2158] = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
  v14 = pArg1[2159];
  if ( *(uint32_t *)(result + 148) == v18[v14] + 1 )
  {
    pArg1[2158] = 0;
    pArg1[2159] = v14 + 1;
  }
  return result;
}



// AI 相位辅助（105L）
// ------------------------------------------------------------
// 0x591720 sub_591720
// ------------------------------------------------------------
int /*thiscall*/ sub_591720(uint32_t *this, int nArg2)
{
  int fld_e1813; // esi
  int v4; // ebx
  uint32_t *v5; // eax
  int fld_e2154; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // ebx
  uint32_t *v11; // eax
  int fld_e21542; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  uint32_t *v17; // eax
  int fld_e21543; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  uint32_t *v23; // eax
  int fld_e21544; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int result; // eax

  fld_e1813 = nArg2;
  if ( nArg2 == 0 )
    fld_e1813 = *(this + 1813);
  v4 = *this;
  v5 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  fld_e2154 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)fld_e1813 + 124))(
         fld_e1813,
         *(this + 2154),
         *v5,
         0,
         4,
         100,
         1,
         0,
         0);
  v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, fld_e2154 - 50);
  v8 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 0, v7);
  v9 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v8 - 50);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 584))(this, v9);
  v10 = *this;
  v11 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  fld_e21542 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)fld_e1813 + 124))(
          fld_e1813,
          *(this + 2154),
          *v11,
          0,
          4,
          100,
          1,
          0,
          0);
  v13 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, fld_e21542);
  v14 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 0, v13 - 60);
  v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v14);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v10 + 584))(this, v15 - 60);
  v16 = *this;
  v17 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  fld_e21543 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)fld_e1813 + 124))(
          fld_e1813,
          *(this + 2154),
          *v17,
          0,
          4,
          100,
          1,
          0,
          0);
  v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, fld_e21543 + 50);
  v20 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 0, v19);
  v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v20 + 50);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v16 + 584))(this, v21);
  v22 = *this;
  v23 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  fld_e21544 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)fld_e1813 + 124))(
          fld_e1813,
          *(this + 2154),
          *v23,
          0,
          4,
          100,
          1,
          0,
          0);
  v25 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, fld_e21544);
  v26 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)fld_e1813 + 124))(fld_e1813, 0, v25 + 60);
  v27 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813, v26);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v22 + 584))(this, v27 + 60);
  *(this + 2158) = 1;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x591890 sub_591890
// ------------------------------------------------------------
void /*thiscall*/ sub_591890(uint32_t *this, int nArg2)
{
  int v3; // eax

  if ( nArg2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) != 0 )
  {
    v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
    sub_5914A0(this, v3);
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5918D0 sub_5918D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5918D0(int *this)
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  int result; // eax

  v2 = 75;
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )
    v2 = -75;
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v2;
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  result = sub_499560(this, this + 2160, this + 2161, v3, v4, 3);
  if ( (uint8_t)result != 0 )
    return sub_591520(this, *(this + 2160), *(this + 2161));
  return result;
}



// AI 相位辅助（80L）
// ------------------------------------------------------------
// 0x591930 sub_591930
// ------------------------------------------------------------
char /*usercall*/ sub_591930@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  int v5; // edx
  int v6; // edi
  int v7; // eax
  int v8; // edi

  sub_4E1780(pDwArg1);
  LOBYTE(v3) = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
  if ( (uint8_t)v3 != 0 )
  {
    v3 = pDwArg1[1639];
    if ( v3 != 0 )
    {
      if ( v3 == 8 )
      {
        v3 = pDwArg1[1813];
        if ( v3 != 0 )
        {
          if ( sub_41A5E0((unsigned int)(pDwArg1 + 1757)) == 1 )
          {
            LOBYTE(v3) = sub_591610(pDwArg1, nArg2);
          }
          else
          {
            v3 = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
            if ( v3 == 2 )
            {
              v3 = pDwArg1[2158];
              if ( v3 == 0 )
                LOBYTE(v3) = sub_591720(pDwArg1, 0);
            }
          }
        }
      }
      else if ( v3 == 14 )
      {
        LOBYTE(v3) = *(uint8_t *)(pDwArg1[30] + 170);
        if ( (uint8_t)v3 != 0 )
          LOBYTE(v3) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 0, 0, 0, 0);
      }
    }
    else
    {
      LOBYTE(v3) = *((uint8_t *)pDwArg1 + 6752);
      if ( (uint8_t)v3 == 0 )
      {
        v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
        v5 = *pDwArg1;
        if ( v4 == pDwArg1[1541] )
        {
          v6 = (*(int (/*thiscall*/ **)(int *))(v5 + 184))(pDwArg1);
          v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
          if ( v6 == v3 )
            return v3;
          v7 = *(uint32_t *)pDwArg1[1554];
        }
        else
        {
          v8 = (*(int (/*thiscall*/ **)(int *))(v5 + 184))(pDwArg1);
          v3 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
          if ( v8 != v3 )
            return v3;
          v7 = pDwArg1[1541];
        }
        (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 196))(pDwArg1, v7);
        LOBYTE(v3) = sub_4926A0(pDwArg1[30]);
      }
    }
  }
  return v3;
}



// 动画/位移插值：sub_4049C0 帧间 lerp（研究 26）驱动的移动 AI
// ------------------------------------------------------------
// 0x591A40 sub_591A40
// ------------------------------------------------------------
int /*thiscall*/ sub_591A40(uint32_t *this)
{
  int result; // eax
  unsigned int i; // ebx
  int fld_e29; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v10; // edx
  void *pObj2; // edi
  int v12; // eax
  int v13; // ebx
  int nRand; // ebx
  int nRand2; // eax
  uint32_t *v16; // eax
  int fld_e2154; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int nRand3; // edi
  int nRand4; // eax
  int v23; // ebx
  uint32_t *v24; // eax
  int fld_e21542; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // [esp+4h] [ebp-8h]
  unsigned int v30; // [esp+8h] [ebp-4h]
  int v31; // [esp+8h] [ebp-4h]
  int v32; // [esp+8h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);
      v5 = *(uint32_t *)(fld_e29 + 8);
      v30 = i;
      v6 = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;
      if ( (int)i >= v6 )
        break;
      v7 = *(uint32_t *)(fld_e29 + 8);
      if ( v7 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v7) >> 2 )
        pObj = *(uint32_t *)(v7 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
      {
        fld_e292 = *(this + 29);
        v10 = *(uint32_t *)(fld_e292 + 8);
        if ( v10 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v10) >> 2 )
          pObj2 = *(void **)(v10 + 4 * i);
        else
          pObj2 = nullptr;
        if ( sub_4E4630(this, (int)pObj2)
          && sub_4E5CA0(pObj2) == 0
          && (*(int (/*thiscall*/ **)(uint32_t *, void *, uint32_t))(*this + 8))(this, pObj2, 0) <= 300
          && ((*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
           || (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)pObj2 + 940))(pObj2) == 0) )
        {
          v12 = (*(int (/*thiscall*/ **)(uint32_t *, void *, uint32_t))(*this + 8))(this, pObj2, 0);
          v13 = (uint64_t)sub_4049C0(0.0, 100.0, v12 - 1, 299);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
          if ( rand() % 100 >= v13 )
          {
            nRand = rand() % 60 - 30;
            nRand2 = rand();
            v31 = *this;
            v29 = nRand2 % 60 - 30;
            v16 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
            fld_e2154 = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj2 + 124))(
                    pObj2,
                    *(this + 2154),
                    *v16,
                    0,
                    4,
                    *(this + 1908) != 0 ? 100 : 130,
                    1,
                    0,
                    0);
            v18 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)pObj2 + 120))(pObj2, v29 + fld_e2154);
            v19 = (*(int (/*thiscall*/ **)(void *, uint32_t, int))(*(uint32_t *)pObj2 + 124))(pObj2, 0, nRand + v18);
            v20 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)pObj2 + 120))(pObj2, v29 + v19);
            return (*(int (/*thiscall*/ **)(uint32_t *, int))(v31 + 584))(this, nRand + v20);
          }
          i = v30;
        }
      }
    }
    nRand3 = rand() % 200 - 100;
    nRand4 = rand();
    v32 = *this;
    v23 = nRand4 % 200 - 100;
    v24 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
    fld_e21542 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 124))(
            this,
            *(this + 2154),
            *v24,
            0,
            4,
            *(this + 1908) != 0 ? 100 : 130,
            1,
            0,
            0);
    v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v23 + fld_e21542);
    v27 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 124))(this, 0, nRand3 + v26);
    v28 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v23 + v27);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v32 + 584))(this, nRand3 + v28);
  }
  return result;
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x591C90 sub_591C90
// ------------------------------------------------------------
int /*thiscall*/ sub_591C90(uint32_t *this, int nArg2)
{
  uint32_t *pThis; // ebx
  unsigned int v3; // edi
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj2; // ecx
  int v9; // ecx
  int v10; // edx
  int pObj; // esi
  int v12; // eax
  int v14; // [esp+Ch] [ebp-Ch]
  int v16; // [esp+14h] [ebp-4h]

  pThis = this;
  v3 = 0;
  v16 = 0;
  while ( 1 )
  {
    v4 = pThis[29];
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v5 != 0 ? (*(uint32_t *)(v4 + 12) - v5) >> 2 : 0;
    if ( (int)v3 >= v6 )
      break;
    v7 = *(uint32_t *)(v4 + 8);
    if ( v7 != 0 && v3 < (*(uint32_t *)(v4 + 12) - v7) >> 2 )
      pObj2 = *(uint32_t *)(v7 + 4 * v3);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )
    {
      v9 = pThis[29];
      v10 = *(uint32_t *)(v9 + 8);
      if ( v10 != 0 && v3 < (*(uint32_t *)(v9 + 12) - v10) >> 2 )
        pObj = *(uint32_t *)(v10 + 4 * v3);
      else
        pObj = 0;
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);
      pThis = this;
      if ( v14 == v12 && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj, 0) < nArg2 )
        ++v16;
    }
    ++v3;
  }
  return v16;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x591D60 sub_591D60
// ------------------------------------------------------------
int /*thiscall*/ sub_591D60(uint32_t *this, int nArg2, int nArg3)
{
  uint64_t v4; // rax
  unsigned int v5; // edi
  int v6; // edx
  int v8; // [esp+14h] [ebp+Ch]

  if ( nArg3 == 0 || (LODWORD(v4) = nArg3 - 2, nArg3 == 2) && (LODWORD(v4) = nArg2, nArg2 == 0) )
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.5;
    sub_41A590(v5, v6, v8);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.5;
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.5;
    v4 = (uint64_t)((double)dword_795468 * 0.33333334);
    dword_795468 = v4;
  }
  return v4;
}



// 冰盾技能：sub_64B0F0 发射 Monster/Soceress/Animation_Keraha/ChillingAura 光环粒子；
//   vt+212 播报 SHIELD_ICE + WINDSHIELD_LOOP（Keraha 冰盾，对应 Aura 家族）
// ------------------------------------------------------------
// 0x591E10 sub_591E10
// ------------------------------------------------------------
int /*thiscall*/ sub_591E10(uint32_t *this, int nArg2, char *Block)
{
  char *pThis_1D73; // ecx
  uint64_t v5; // rax
  int pObj; // eax
  int v7; // edx
  unsigned int v8; // edi
  int v9; // edx
  int Blocka; // [esp+24h] [ebp+Ch]

  *((uint8_t *)this + 7558) = 0;
  *((uint8_t *)this + 7557) = 0;
  *((uint8_t *)this + 7556) = 0;
  *((uint8_t *)this + 7534) = 0;
  *((uint8_t *)this + 7533) = 0;
  *((uint8_t *)this + 7532) = 0;
  *((uint8_t *)this + 7531) = 0;
  *(uint32_t *)((char *)this + 7535) = 0;
  pThis_1D73 = (char *)this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *(this + 1893) = 0;
  *(this + 1892) = 0;
  *(this + 1891) = 0;
  *(this + 1897) = 0;
  *(this + 1896) = 0;
  *(this + 1895) = 0;
  *(this + 1894) = 0;
  *(this + 1899) = 0;
  *((uint8_t *)this + 7534) = 1;
  if ( Block == nullptr )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 700))(this);
    sub_53F6A0(this);
    if ( operator new(0x8Cu) != nullptr )
      pObj = sub_64B0F0(0, 0x40000000, 10, "Monster/Soceress/Animation_Keraha/ChillingAura");
    else
      pObj = 0;
    (*(void (/*thiscall*/ **)(int, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
      pObj,
      this,
      this,
      0,
      0,
      0,
      -1);
    sub_4DB130(24, 2);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SHIELD_ICE", -1, 0, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 7818);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "WINDSHIELD_LOOP",
      7818,
      0,
      0);
    goto LABEL_9;
  }
  LODWORD(v5) = Block - 2;
  if ( Block == (char *)2 && nArg2 == 0 )
  {
LABEL_9:
    v7 = *this;
    *(this + 1899) = 50;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v7 + 672))(this, 0) + 830;
    *(float *)&Blocka = COERCE_FLOAT(sub_41A5E0(v8)) + 0.5;
    sub_41A590(v8, v9, Blocka);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) + *(float *)(*(this + 1905) + 36);
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) + *(float *)(*(this + 1905) + 68);
    v5 = (uint64_t)((double)dword_795468 * 3.0);
    dword_795468 = v5;
  }
  return v5;
}



// AI 相位辅助（69L）
// ------------------------------------------------------------
// 0x592000 sub_592000
// ------------------------------------------------------------
int /*thiscall*/ sub_592000(uint32_t *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj3; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj2; // ebx
  int v11; // edi
  int pObj; // eax
  uint32_t *v13; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  unsigned int v15; // [esp+10h] [ebp-10h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj3 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 17) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        pObj2 = *(uint32_t *)(v9 + 4 * i);
      else
        pObj2 = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0) <= 300 )
      {
        Block = operator new(0x84u);
        pObj = 0;
        if ( Block != nullptr )
        {
          v13 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
          pObj = sub_4DF1B0(*v13 - 5, 1, 0, -1);
        }
        (*(void (/*thiscall*/ **)(int, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
          pObj,
          pObj2,
          this,
          1,
          0,
          0,
          -1);
      }
      i = v15;
    }
  }
  return result;
}



// 施法 AI：vt+212 播报 KERA_CAST / SOR_SPIN（凯拉哈旋身施法）
// ------------------------------------------------------------
// 0x592130 sub_592130
// ------------------------------------------------------------
int /*thiscall*/ sub_592130(int *this, char ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_e1639; // eax
  int fld_e2153; // eax
  int nRand; // eax
  int result; // eax
  uint32_t v10[2]; // [esp+4h] [ebp-8h]

  fld_e1639 = *(this + 1639);
  if ( fld_e1639 == 5 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 7818);
  }
  else if ( fld_e1639 == 14 )
  {
    fld_e2153 = *(this + 2153);
    switch ( fld_e2153 )
    {
      case 2:
        v10[0] = 0;
        v10[1] = 1;
        nRand = rand() % 2;
        sub_4DB200(24, v10[nRand]);
        sub_591A40(this);
        break;
      case 1:
        sub_4DB200(24, 3);
        sub_5918D0(this);
        break;
      case 0:
        sub_592000(this);
        break;
      default:
        break;
    }
  }
  sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  result = *(this + 1639);
  if ( result == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                 this,
                 "KERA_CAST",
                 -1,
                 0,
                 0);
      *(this + 2158) = 0;
      *(this + 2159) = 0;
    }
    else
    {
      return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SOR_SPIN", -1, 0, 0);
    }
  }
  else if ( result == 14 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      0,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
    sub_4926A0(*(this + 30));
    return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);
  }
  return result;
}



// 召唤物生成：sub_431860 装载 Monster/Soceress/Effect/Summon.ani（召唤特效, 44L）
// ------------------------------------------------------------
// 0x5922B0 sub_5922B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5922B0(int *this)
{
  int v2; // ebx
  char *v3; // eax
  int pObj; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v11; // [esp-4h] [ebp-20h]

  v2 = 0;
  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Monster/Soceress/Effect/Summon.ani", 1);
  v3 = (char *)sub_44B6C0(284);
  pObj = (int)v3;
  if ( v3 != nullptr )
  {
    sub_44E0D0(v3, v2, 1);
    *(uint32_t *)pObj = &CNRDPooledObject::`vftable';
  }
  else
  {
    pObj = 0;
  }
  sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);
  v5 = *(uint32_t *)pObj;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 112))(pObj, v7);
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);
  sub_4A06D0(v11);
  v8 = *(uint32_t *)pObj;
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  return (*(int (/*thiscall*/ **)(int, int))(v8 + 148))(pObj, v9);
}



// 凯拉哈主攻 AI：sub_406D60 写 B_KERAHA_01 登场曲槽 + vt+212 KERA_CAST/KERA_COMMAND；
//   this+8624 相位门 + sub_699000 时钟门
// ------------------------------------------------------------
// 0x5923A0 sub_5923A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5923A0(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  int v5; // eax
  int nRand; // eax
  int v7; // et2
  int v8; // eax

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 16);
      if ( *(this + 1943) == 3 )
        return sub_406D60("B_KERAHA_01");
      return result;
    case 4:
    case 16:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
      if ( result == 14 )
        return result;
      if ( sub_699000((int)(this + 9)) > (unsigned int)(dword_795468 + *(this + 2155)) )  // 【clock_now(clk)】
      {
        if ( *(this + 1908) == 0 && *(this + 1787) == 4 )
          sub_591720(this, (int)this);
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 16);
      }
      if ( rand() % 100 < 10 )
      {
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
        *(this + 2153) = 2;
        if ( rand() % 100 < 30 )
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "KERA_CAST", -1, 0, 0);
      }
      if ( *(this + 1813) == 0 || *((uint8_t *)this + 8624) != 0 || *(this + 2157) >= 5 || rand() % 300 >= 5 )
        goto LABEL_25;
      result = *(this + 1908);
      if ( result == 2 && *(this + 1909) == 0 || result == 0 )
      {
        v3 = sub_4D8FE0(this);
        result = sub_591C90(this, 2 * v3);
        if ( result < 2 )
        {
          v4 = (*(int (/*thiscall*/ **)(int *))(*this + 740))(this) / 10;
          result = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
          if ( result >= v4 )
          {
            (*(void (/*thiscall*/ **)(int *))(*this + 152))(this);
            (*(void (/*thiscall*/ **)(int *))(*this + 120))(this);
            (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
            sub_5922B0(this);
            v5 = *this;
            *(this + 2153) = 1;
            (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v5 + 212))(
              this,
              "KERA_COMMAND",
              -1,
              0,
              0);
            *((uint8_t *)this + 8624) = 1;
LABEL_25:
            nRand = rand();
            v7 = nRand % 100;
            result = nRand / 100;
            if ( v7 < 1 )
            {
              (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
              v8 = *this;
              *(this + 2153) = 0;
              return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(
                       this,
                       "KERA_CAST",
                       -1,
                       0,
                       0);
            }
          }
        }
      }
      return result;
    case 5:
      result = *(this + 1813);
      if ( result == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
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



// 凯拉哈资源装载：sub_4015C0 注册 R_KERA_ATK/DMG/DIE + SOR_APPEAR 语音槽；
//   sub_4BA9E0 装载 Monster/Soceress/{Hair02,Cloth02,Weapon02,Acc02}.equ 四件外观
// ------------------------------------------------------------
// 0x592650 sub_592650
// ------------------------------------------------------------
int /*thiscall*/ sub_592650(uint32_t *this)
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
  int v14; // eax
  int fld_e1821; // edi
  uint32_t *v16; // eax
  uint64_t fld_e1820; // rax
  int result; // eax
  float v19; // [esp+2Ch] [ebp-30h]
  float v20; // [esp+30h] [ebp-2Ch]
  void *Block; // [esp+48h] [ebp-14h]
  int v22; // [esp+4Ch] [ebp-10h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_KERA_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_KERA_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_KERA_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SOR_APPEAR", 0xAu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Soceress/Hair02.equ", 0);
  else
    v3 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Soceress/Cloth02.equ", 0);
  else
    v6 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Soceress/Weapon02.equ", 0);
  else
    v9 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v12 = sub_4BA9E0(pMem4, "Monster/Soceress/Acc02.equ", 0);
  else
    v12 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  v14 = *this;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 570;
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v14 + 384))(this, 0);
  v22 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v16 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v20 = (float)v22;
  v19 = (float)(int)Block;
  fld_e1820 = (uint64_t)sub_4049C0(v19, v20, *v16 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1820) = *this;
  *(this + 2150) = fld_e1820;
  *(this + 2152) = (*(int (/*thiscall*/ **)(uint32_t *, int))(HIDWORD(fld_e1820) + 384))(this, 2);
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2155) = result;
  *(this + 2120) = 10;
  *(this + 2121) = 2000;
  *(this + 2154) = 30059;
  return result;
}



// 子类扩展字段复位（this+8600..8660）
// ------------------------------------------------------------
// 0x5928E0 sub_5928E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5928E0(int this)
{
  *(uint32_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 1;
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint8_t *)(this + 8644) = 0;
  *(uint32_t *)(this + 8648) = 0;
  *(uint8_t *)(this + 8660) = 0;
  return 0;
}



// 【vmt200 命中处理器覆写】小型时钟门版（虚表 0x6CE04C +512 槽）：sub_699000 时钟读 + this+86xx 门控
// ------------------------------------------------------------
// 0x592920 sub_592920
// ------------------------------------------------------------
int /*thiscall*/ sub_592920(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);
  if ( (uint8_t)nArg4 == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
    *(this + 2159) = sub_699000((int)(this + 9));
  }
  return v5;
}



// AI 相位门（this+8644）
// ------------------------------------------------------------
// 0x592970 sub_592970
// ------------------------------------------------------------
int /*thiscall*/ sub_592970(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int v5; // edi
  int v6; // eax
  int fld_e2151; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v5 = *this;
    *(this + 2151) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 108) + 112);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(v5 + 152))(
           this,
           2,
           0,
           0,
           0xFFFF,
           0,
           0,
           0,
           0);
    fld_e2151 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*this + 376))(
           this,
           *(this + 2151),
           *(this + 2163),
           *(this + 2164),
           0,
           v6);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(v5 + 592))(this, *(this + 2152), fld_e2151);
    result = *(this + 2162) + 1;
    *((uint8_t *)this + 8644) = 0;
    *(this + 2162) = result;
  }
  return result;
}



// 主状态门（this+200, 研究 15 第一层状态）
// ------------------------------------------------------------
// 0x592A00 sub_592A00
// ------------------------------------------------------------
int /*thiscall*/ sub_592A00(uint32_t *this)
{
  int v2; // eax
  int fld_e2157; // edi
  int fld_e21572; // ebx
  int v5; // eax
  int v6; // edx
  int v7; // ebx
  int v8; // eax
  int v9; // ecx
  int v10; // eax
  int fld_e21573; // ecx
  int result; // eax
  int v13; // [esp+Ch] [ebp-44h]
  uint32_t v14[7]; // [esp+10h] [ebp-40h]
  uint32_t v15[4]; // [esp+2Ch] [ebp-24h]
  uint32_t v16[4]; // [esp+3Ch] [ebp-14h]
  int v17; // [esp+4Ch] [ebp-4h]

  v16[0] = 3;
  v16[1] = 3;
  v16[2] = 6;
  v16[3] = 6;
  v15[0] = 1;
  v15[3] = 1;
  v2 = *this;
  v13 = 100;
  v14[0] = 0;
  v14[1] = 0;
  v14[2] = 50;
  v14[3] = -100;
  v14[4] = 0;
  v14[5] = 0;
  v14[6] = -50;
  v15[1] = 0;
  v15[2] = 0;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(v2 + 200))(this) + 148) == v16[*(this + 2157)]
    && *((uint8_t *)this + 8624) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
    {
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F82C8 + 28))(dword_8F82C8);
      fld_e2157 = v14[2 * *(this + 2157) - 1] + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      fld_e21572 = *(this + 2157);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v6 = v14[2 * fld_e21572];
      v7 = v15[fld_e21572];
      v8 = v6 + v5;
      v9 = fld_e2157 + 500;
      if ( v7 != 0 )
        v9 = fld_e2157 - 500;
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int, int, int, uint32_t, uint32_t, int, int, int, int, uint32_t, uint32_t))(*this + 584))(
        this,
        v9,
        v8,
        400,
        fld_e2157,
        v8,
        *(this + 2154),
        *(this + 2150),
        v17,
        v7,
        100,
        2,
        0,
        0);
    }
    *((uint8_t *)this + 8624) = 1;
  }
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  fld_e21573 = *(this + 2157);
  if ( *(uint32_t *)(v10 + 148) == v16[fld_e21573] + 1 )
  {
    *((uint8_t *)this + 8624) = 0;
    *(this + 2157) = fld_e21573 + 2;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 16, 0, 2, 0);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x592B90 sub_592B90
// ------------------------------------------------------------
int /*thiscall*/ sub_592B90(void *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    if ( rand() % 100 < 50 )
      sub_4DC730(this);
    nRand = rand();
    v4 = nRand % 100;
    result = nRand / 100;
    if ( v4 < 15 )
      return (*(int (/*thiscall*/ **)(void *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
               this,
               48013,
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
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x592C00 sub_592C00
// ------------------------------------------------------------
int /*thiscall*/ sub_592C00(uint32_t *this, int nArg2)
{
  if ( nArg2 == *(this + 1815) && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 316))(this) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  return sub_4D9170(nArg2);
}



// 能量球技能：引用 Particle/EnergyBall.ptl（118L，凯拉哈能量弹）
// ------------------------------------------------------------
// 0x592C40 sub_592C40
// ------------------------------------------------------------
char /*usercall*/ sub_592C40@<al>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // ebx
  int v10; // eax
  int *v11; // eax
  int v12; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // edx
  int v16; // ebx
  int v17; // eax
  void *v18; // eax
  int v19; // edi
  int v20; // eax
  int v23; // [esp+4h] [ebp-28h] BYREF
  char v24; // [esp+8h] [ebp-24h]
  float v25; // [esp+Ch] [ebp-20h]
  int v26; // [esp+10h] [ebp-1Ch] BYREF
  char v27; // [esp+14h] [ebp-18h]
  float v28; // [esp+18h] [ebp-14h]
  void *Block; // [esp+1Ch] [ebp-10h]
  int v30; // [esp+28h] [ebp-4h]

  if ( *((uint32_t *)pArg1 + 2090) != 0 && pArg1[8609] == 0 )
  {
    v4 = *(uint32_t *)pArg1;
    pArg1[8609] = 1;
    (*(void (**)(void))(v4 + 1312))();
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 840))(pArg1) == 8 )
  {
    v5 = *(uint32_t *)(*((uint32_t *)pArg1 + 30) + 148);
    v6 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 908))(pArg1) - 2;
    if ( v6 != 0 )
    {
      v7 = v6 - 1;
      if ( v7 != 0 )
      {
        if ( v7 == 1
          && v5 >= 3
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0
          && pArg1[8600] != 0 )
        {
          v8 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 4, nArg3, nArg2);
          v9 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 5);
          v10 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 6);
          pArg1[8600] = 0;
          v28 = (float)v10;
          v26 = 23;
          v27 = 0;
          Block = operator new(0x1D0u);
          v30 = 1;
          if ( Block != nullptr )
          {
            v11 = (int *)sub_64B6C0(v8, &v26, 1, v9, 1, 1);
LABEL_19:
            v15 = *v11;
            v30 = -1;
            (*(void (/*thiscall*/ **)(int *, uint8_t *, uint8_t *, uint32_t, uint32_t))(v15 + 56))(v11, pArg1, pArg1, 0, 0);
            return sub_4E1780(pArg1);
          }
          goto LABEL_18;
        }
      }
      else if ( v5 >= 3 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8600] != 0 )
      {
        v12 = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 1, nArg3, nArg2);
        v13 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 2);
        v14 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 3);
        pArg1[8600] = 0;
        v25 = (float)v14;
        v23 = 1;
        v24 = 0;
        Block = operator new(0x1D0u);
        v30 = 0;
        if ( Block != nullptr )
        {
          v11 = (int *)sub_64B6C0(v12, &v23, 1, v13, 1, 1);
          goto LABEL_19;
        }
LABEL_18:
        v11 = nullptr;
        goto LABEL_19;
      }
    }
    else if ( v5 >= 3 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8600] != 0 )
    {
      v16 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pArg1 + 384))(pArg1, 0);
      v17 = *(uint32_t *)pArg1;
      pArg1[8600] = 0;
      v18 = (void *)(*(int (/*thiscall*/ **)(uint8_t *, const char *))(v17 + 588))(pArg1, "Particle/EnergyBall.ptl");
      v19 = *(uint32_t *)pArg1;
      Block = v18;
      v20 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t))(v19 + 152))(pArg1, 0, 0, 0);
      (*(void (/*thiscall*/ **)(uint8_t *, int, int, void *, uint32_t, int, uint32_t, int, int))(v19 + 580))(
        pArg1,
        30360,
        v16,
        Block,
        0,
        70,
        0,
        63,
        v20);
    }
  }
  return sub_4E1780(pArg1);
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x592EB0 sub_592EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_592EB0(int *this)
{
  int result; // eax
  int *pThis; // ecx

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      pThis = this;
      if ( *(this + 1813) != 0 )
        goto LABEL_9;
      goto LABEL_4;
    case 5:
      result = *(this + 1813);
      if ( result == 0 )
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
      {
        pThis = this;
LABEL_9:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(pThis, 5);
      }
      break;
    default:
      return result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x592F50 sub_592F50
// ------------------------------------------------------------
int /*thiscall*/ sub_592F50(int *this)
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  int result; // eax

  v2 = 75;
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 0 )
    v2 = -75;
  v3 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this) + v2;
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  result = sub_499560(this, this + 2163, this + 2164, v3, v4, 3);
  if ( (uint8_t)result != 0 )
    return sub_592970(this, *(this + 2163), *(this + 2164));
  return result;
}



// AI 相位辅助（63L）
// ------------------------------------------------------------
// 0x592FB0 sub_592FB0
// ------------------------------------------------------------
int /*usercall*/ sub_592FB0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>)
{
  int result; // eax
  unsigned int i; // ebx
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int pObj; // esi
  int v10; // ebx
  BOOL v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v19; // [esp+4h] [ebp-8h]
  int v20; // [esp+8h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      v6 = pArg1[29];
      v7 = *(uint32_t *)(v6 + 120);
      result = v7 != 0 ? (*(uint32_t *)(v6 + 124) - v7) >> 2 : 0;
      if ( (int)i >= result )
        break;
      v8 = *(uint32_t *)(v6 + 120);
      if ( v8 != 0 && i < (*(uint32_t *)(v6 + 124) - v8) >> 2 )
        pObj = *(uint32_t *)(v8 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0
        && (uint8_t)sub_4E4630(pObj) != 0
        && (uint8_t)sub_4E5CA0(pObj) == 0
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pObj, 0) <= 300
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 940))(pObj) == 0 )
      {
        v10 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 120))(pObj, nArg3, nArg2);
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) < v10;
        if ( v11 )
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) - 500;
        else
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) + 500;
        v20 = v12;
        v19 = *pArg1;
        v13 = (*(int (/*thiscall*/ **)(int, BOOL, int, int))(*(uint32_t *)dword_8F82C8 + 28))(dword_8F82C8, v11, 100, 2);
        v14 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, pArg1[2154], pArg1[2150], v13);
        v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v14);
        v16 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 124))(pObj, 400, v15);
        return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v19 + 584))(pArg1, v20, v16);
      }
    }
  }
  return result;
}



// AI 相位门（this+8624）
// ------------------------------------------------------------
// 0x5930F0 sub_5930F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5930F0(int *this, int nArg2, int nArg3)
{
  int v4; // edx
  int fld_e81; // edi
  uint32_t *fld_e28; // edi
  unsigned int result; // eax
  unsigned int v8; // ecx
  int i; // edx
  int fld_e1905; // edi

  v4 = *this;
  *(this + 81) = nArg2;
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v4 + 876))(0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 8));
  sub_4926A0(*(this + 30));
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, int))(*this + 888))(this, 1, 0, 1000, 1000);
  fld_e81 = *(this + 81) - (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  if ( fld_e81 != 0 )
  {
    sub_495890(0, fld_e81 <= 0 ? 1000 : -1000);
    sub_4A0550(fld_e81);
    result = sub_4A0600(2);
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
    result = sub_495890(2, 0);
  }
  *(this + 2157) = nArg3;
  v8 = 0;
  *((uint8_t *)this + 8624) = 0;
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
// 0x593230 sub_593230
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_593230(unsigned int *this)
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
      result = *(this + 2155);
      *(this + 81) = result;
      return result;
    }
    result = (int)(*(this + 1906) - fld_e1905) >> 5;
    if ( v1 >= result )
      break;
    ++v1;
    *(uint8_t *)(i + fld_e1905) = 1;
  }
  *(this + 81) = *(this + 2155);
  return result;
}



// 位移/动画插值：sub_4049C0（研究 26）
// ------------------------------------------------------------
// 0x593280 sub_593280
// ------------------------------------------------------------
int /*thiscall*/ sub_593280(uint32_t *this)
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
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 10);
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);
  sub_4EB4B0(COERCE_FLOAT(11));
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
// 0x593340 sub_593340
// ------------------------------------------------------------
int /*thiscall*/ sub_593340(int *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 1172))(this);
  if ( result > 0 )
  {
    if ( result > 5 )
    {
      if ( result > 10 )
      {
        if ( result > 15 )
          return result;
        goto LABEL_5;
      }
    }
    else
    {
      *(uint8_t *)(*(this + 1905) + 64) = 0;
    }
    *(uint8_t *)(*(this + 1905) + 96) = 0;
LABEL_5:
    result = *(this + 1905);
    *(uint8_t *)(result + 128) = 0;
  }
  return result;
}



// ============================================================
// 【分区 3】魔法师·薇诺 & 路易丝（Vino & Luis）（0x5933A0-0x594370）
// 证据：VINO/R_LUIS_*/R_VINO_* 语音、AURA_FURY 狂气光环、VINO_CAST/VINO_COMMAND、
//       Monster/Soceress/Hair01-Cloth01-Weapon01-Acc01.equ 与 Luis_* 五件套

// AI 相位辅助（77L）
// ------------------------------------------------------------
// 0x5933A0 sub_5933A0
// ------------------------------------------------------------
int /*userpurge*/ sub_5933A0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>, int nArg4)
{
  int result; // eax
  unsigned int v6; // ebx
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int pObj; // esi
  int v11; // ebx
  BOOL v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v20; // [esp+4h] [ebp-14h]
  int v21; // [esp+8h] [ebp-10h]
  unsigned int v22; // [esp+Ch] [ebp-Ch]
  int v23; // [esp+10h] [ebp-8h]
  int v24; // [esp+14h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    v6 = 0;
    v23 = 0;
    v21 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 384))(pArg1, 9);
    while ( 1 )
    {
      v7 = pArg1[29];
      v8 = *(uint32_t *)(v7 + 120);
      v22 = v6;
      result = v8 != 0 ? (*(uint32_t *)(v7 + 124) - v8) >> 2 : 0;
      if ( (int)v6 >= result )
        break;
      v9 = *(uint32_t *)(v7 + 120);
      if ( v9 != 0 && v6 < (*(uint32_t *)(v7 + 124) - v9) >> 2 )
        pObj = *(uint32_t *)(v9 + 4 * v6);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0
        && (uint8_t)sub_4E4630(pObj) != 0
        && (uint8_t)sub_4E5CA0(pObj) == 0
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, pObj, 0) <= 300
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 940))(pObj) == 0 )
      {
        v11 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 120))(pObj, nArg3, nArg2);
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) < v11;
        if ( v12 )
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) - 500;
        else
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj) + 500;
        nArg2 = 0;
        nArg3 = 0;
        v24 = v13;
        v20 = *pArg1;
        v14 = (*(int (/*thiscall*/ **)(int, BOOL, int, int))(*(uint32_t *)dword_8F82C8 + 28))(dword_8F82C8, v12, 100, 2);
        v15 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 124))(pObj, 30362, v21, v14);
        v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v15);
        v17 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 124))(pObj, 400, v16);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v20 + 584))(pArg1, v24, v17);
        result = ++v23;
        if ( v23 >= nArg4 )
          return result;
        v6 = v22;
      }
      ++v6;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x593510 sub_593510
// ------------------------------------------------------------
int /*userpurge*/ sub_593510@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  char v7; // di
  int v8; // eax
  int v9; // ebx
  int pObj; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax

  if ( *(uint32_t *)(pArg1 + 8604) == 0 )
  {
    sub_593340((int *)pArg1);
    *(uint32_t *)(pArg1 + 8604) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1172))(pArg1);
  }
  v7 = ArgList;
  if ( ArgList != 8 )
  {
    if ( ArgList == 13 )
    {
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 7);
    }
    else
    {
      if ( ArgList != 5 )
        return sub_4E33D0(v7, fArg4, nArg5, nArg6);
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 8);
    }
    sub_5933A0((uint32_t *)pArg1, nArg2, pArg1, v15);
    return sub_4E33D0(v7, fArg4, nArg5, nArg6);
  }
  v8 = **(uint32_t **)(LODWORD(fArg4) + 4);
  if ( v8 == 1 )
  {
    if ( *(uint32_t *)(pArg1 + 7252) != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )
    {
      v9 = *(uint32_t *)pArg1;
      pObj = *(uint32_t *)(pArg1 + 7252);
      v11 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 124))(
              pObj,
              30364,
              0,
              0,
              4,
              *(uint32_t *)(pArg1 + 7632) != 0 ? 100 : 130,
              1,
              0,
              0);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v11);
      v13 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, 0, v12);
      v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v13);
      (*(void (/*thiscall*/ **)(int, int))(v9 + 584))(pArg1, v14);
      v7 = 8;
    }
  }
  else if ( v8 > 1 && v8 <= 4 )
  {
    *(uint8_t *)(pArg1 + 8600) = 1;
  }
  return sub_4E33D0(v7, fArg4, nArg5, nArg6);
}



// 语音注册：sub_4015C0 写 "VINO" 槽 + sub_699000 时钟门
// ------------------------------------------------------------
// 0x593640 sub_593640
// ------------------------------------------------------------
int /*thiscall*/ sub_593640(uint32_t *this)
{
  int result; // eax

  sub_4D9760();
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 16);
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  *(this + 2160) = result;
  if ( *(this + 1943) == 3 )
    return sub_4015C0("VINO", 4u);  // 【std::string构造赋值】
  return result;
}



// 语音注册：R_LUIS_ATK/DMG/DIE + SOR_APPEAR（sub_4015C0 → 语音槽, 研究 28）
// ------------------------------------------------------------
// 0x593680 sub_593680
// ------------------------------------------------------------
int /*thiscall*/ sub_593680(uint32_t *this)
{
  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_LUIS_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_LUIS_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_LUIS_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("SOR_APPEAR", 0xAu);  // 【std::string构造赋值】
  *(this + 2151) = 0;
  *((uint8_t *)this + 8609) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x593710 sub_593710
// ------------------------------------------------------------
int /*thiscall*/ sub_593710(uint32_t *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj3; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj2; // ebx
  int v11; // edi
  int pObj; // eax
  uint32_t *v13; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  unsigned int v15; // [esp+10h] [ebp-10h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj3 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 17) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        pObj2 = *(uint32_t *)(v9 + 4 * i);
      else
        pObj2 = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 376))(pObj2);
      if ( v11 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 376))(this)
        && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0) <= 300 )
      {
        Block = operator new(0x84u);
        pObj = 0;
        if ( Block != nullptr )
        {
          v13 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
          pObj = sub_4DF1B0(*v13 - 5, 0, 0, -1);
        }
        (*(void (/*thiscall*/ **)(int, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
          pObj,
          pObj2,
          this,
          1,
          0,
          0,
          -1);
      }
      i = v15;
    }
  }
  return result;
}



// 狂气光环 AI：vt+212 播报 AURA_FURY + SOR_SPIN（130L；薇诺狂气化演出）
// ------------------------------------------------------------
// 0x593840 sub_593840
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_593840(int this, void *Block, float fArg3, int nArg4, int nArg5)
{
  void *Block2; // ebx
  int fld_199C; // edi
  int fld_21A4; // eax
  int nRand; // eax
  unsigned int result; // eax
  int *v11; // eax
  int v12; // edx
  uint32_t v13[2]; // [esp+Ch] [ebp-14h]
  int v14; // [esp+1Ch] [ebp-4h]
  void *Blocka; // [esp+28h] [ebp+8h]

  Block2 = Block;
  fld_199C = *(uint32_t *)(this + 6556);
  if ( Block == (void *)16 )
  {
    sub_593230((unsigned int *)this);
    Block2 = nullptr;
  }
  if ( fld_199C == 15 )
  {
    if ( Block2 != (void *)16 )
      sub_593230((unsigned int *)this);
  }
  else if ( fld_199C == 14 )
  {
    fld_21A4 = *(uint32_t *)(this + 8612);
    switch ( fld_21A4 )
    {
      case 2:
        v13[0] = 0;
        v13[1] = 1;
        nRand = rand() % 2;
        sub_4DB200(24, v13[nRand]);
        sub_592FB0((uint32_t *)this, (int)Block2, this);
        break;
      case 1:
        sub_4DB200(24, 3);
        sub_592F50((int *)this);
        break;
      case 0:
        sub_593710((uint32_t *)this);
        break;
      default:
        break;
    }
  }
  sub_4E33D0((char)Block2, fArg3, nArg4, nArg5);
  result = *(uint32_t *)(this + 6556);
  switch ( result )
  {
    case 0u:
      result = *(uint32_t *)(this + 7632);
      if ( result == 0 )
      {
        result = *(uint8_t *)(this + 8660);
        if ( (uint8_t)result == 0 )
        {
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
          sub_53F6A0(this);
          Blocka = operator new(0x8Cu);
          v14 = 0;
          if ( Blocka != nullptr )
            v11 = (int *)sub_64BBF0(180, 3000, 25);
          else
            v11 = nullptr;
          v12 = *v11;
          v14 = -1;
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, int))(v12 + 56))(
            v11,
            this,
            this,
            0,
            0,
            0,
            -1);
          sub_4DB200(24, 2);
          result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                     this,
                     "AURA_FURY",
                     -1,
                     0,
                     0);
          *(uint8_t *)(this + 8660) = 1;
        }
      }
      break;
    case 8u:
      result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                 this,
                 "SOR_SPIN",
                 -1,
                 0,
                 0);
      break;
    case 0xEu:
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
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
      sub_4926A0(*(uint32_t *)(this + 120));
      result = (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 1, 0, 1000, 1000);
      break;
    case 0xFu:
      result = sub_5930F0((int *)this, **(uint32_t **)(LODWORD(fArg3) + 4), *(uint32_t *)(*(uint32_t *)(LODWORD(fArg3) + 4) + 4));
      break;
    default:
      return result;
  }
  return result;
}


// AI 相位辅助（sub_431230/sub_699000）
// ------------------------------------------------------------
// 0x593AC0 sub_593AC0
// ------------------------------------------------------------
void /*thiscall*/ sub_593AC0(uint32_t *this)
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
  if ( sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2160) + 18000) )  // 【clock_now(clk)】
  {
    v3 = sub_699000(pThis_9);  // 【clock_now(clk)】
    v4 = *this;
    *(this + 2160) = v3;
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 840))(this) == 0 && *(this + 1813) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
      v9[0] = 200;
      Block = nullptr;
      v7 = 0;
      v8 = 0;
      v9[3] = 0;
      sub_431230((int)v5, v9);
      v9[0] = rand() % 2;
      sub_431230((int)v5, v9);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 15, v5, 0, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x593BA0 sub_593BA0
// ------------------------------------------------------------
void /*thiscall*/ sub_593BA0(int this)
{
  int fld_199C; // eax
  int v3; // eax
  int pThis_B8; // edi
  int fld_1848; // eax
  int pThis_B82; // edi

  sub_4E1780((uint32_t *)this);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
  {
    fld_199C = *(uint32_t *)(this + 6556);
    if ( fld_199C != 0 )
    {
      v3 = fld_199C - 14;
      if ( v3 != 0 )
      {
        if ( v3 == 1 )
        {
          sub_592A00((uint32_t *)this);
          sub_593AC0((uint32_t *)this);
          return;
        }
      }
      else if ( *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 564))(this);
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
        sub_593AC0((uint32_t *)this);
        return;
      }
      goto LABEL_15;
    }
    if ( *(uint8_t *)(this + 6752) == 0 )
    {
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *(uint32_t *)(this + 6164) )
      {
        pThis_B8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this);
        if ( pThis_B8 != (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) )
        {
          fld_1848 = **(uint32_t **)(this + 6216);
LABEL_14:
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 196))(this, fld_1848);
          sub_4926A0(*(uint32_t *)(this + 120));
        }
      }
      else
      {
        pThis_B82 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 184))(this);
        if ( pThis_B82 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) )
        {
          fld_1848 = *(uint32_t *)(this + 6164);
          goto LABEL_14;
        }
      }
    }
LABEL_15:
    sub_593AC0((uint32_t *)this);
  }
}



// 召唤物生成：Monster/Soceress/Effect/Summon.ani（薇诺版召唤特效）
// ------------------------------------------------------------
// 0x593CA0 sub_593CA0
// ------------------------------------------------------------
int /*thiscall*/ sub_593CA0(int *this)
{
  int v2; // ebx
  char *v3; // eax
  int pObj; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v11; // [esp-4h] [ebp-20h]

  v2 = 0;
  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Monster/Soceress/Effect/Summon.ani", 1);
  v3 = (char *)sub_44B6C0(284);
  pObj = (int)v3;
  if ( v3 != nullptr )
  {
    sub_44E0D0(v3, v2, 1);
    *(uint32_t *)pObj = &CNRDPooledObject::`vftable';
  }
  else
  {
    pObj = 0;
  }
  sub_45FE80(*(this + 29), pObj, 2, 0, pObj, (int)this, 0);
  v5 = *(uint32_t *)pObj;
  v11 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
  v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);
  (*(void (/*thiscall*/ **)(int, int))(v5 + 112))(pObj, v7);
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)pObj + 60))(pObj, this);
  sub_4A06D0(v11);
  v8 = *(uint32_t *)pObj;
  v9 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
  return (*(int (/*thiscall*/ **)(int, int))(v8 + 148))(pObj, v9);
}



// 薇诺主攻 AI：vt+212 VINO_CAST + VINO_COMMAND（101L；this+8644 相位门）
// ------------------------------------------------------------
// 0x593D90 sub_593D90
// ------------------------------------------------------------
int /*thiscall*/ sub_593D90(uint32_t *this)
{
  int result; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edi
  int v6; // edx
  int nRand; // eax
  int v8; // et2
  int v9; // edx

  sub_4E0120();
  result = *(this + 1787) - 4;
  switch ( *(this + 1787) )
  {
    case 4:
    case 0x10:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
      if ( result == 14 )
        return result;
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
      if ( result == 15 )
        return result;
      if ( sub_699000((int)(this + 9)) > (unsigned int)(*(this + 2159) + 10000) )  // 【clock_now(clk)】
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 16);
      if ( rand() % 100 < 12 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
        v3 = *this;
        *(this + 2153) = 2;
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v3 + 212))(this, "VINO_CAST", -1, 0, 0);
      }
      if ( *(this + 1813) == 0 || *((uint8_t *)this + 8644) != 0 || (int)*(this + 2162) >= 5 || rand() % 300 >= 5 )
        goto LABEL_17;
      v4 = sub_4D8FE0(this);
      result = sub_591C90(this, 2 * v4);
      if ( result < 2 )
      {
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this) / 10;
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this);
        if ( result >= v5 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
          sub_593CA0(this);
          v6 = *this;
          *(this + 2153) = 1;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v6 + 212))(
            this,
            "VINO_COMMAND",
            -1,
            0,
            0);
          *((uint8_t *)this + 8644) = 1;
LABEL_17:
          nRand = rand();
          v8 = nRand % 100;
          result = nRand / 100;
          if ( v8 < 3 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
            (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
            v9 = *this;
            *(this + 2153) = 0;
            return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(v9 + 212))(
                     this,
                     "VINO_CAST",
                     -1,
                     0,
                     0);
          }
        }
      }
      return result;
    case 5:
      result = *(this + 1813);
      if ( result == 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      return result;
    case 0xD:
    case 0xE:
    case 0xF:
      result = *(this + 1813);
      if ( result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
      return result;
    default:
      return result;
  }
}



// 薇诺资源装载：R_VINO_ATK/DMG/DIE + SOR_APPEAR 语音；
//   Monster/Soceress/{Hair01,Cloth01,Weapon01,Acc01}.equ 四件外观（123L）
// ------------------------------------------------------------
// 0x593FF0 sub_593FF0
// ------------------------------------------------------------
int /*thiscall*/ sub_593FF0(int *this)
{
  void *pMem; // eax
  char *v3; // eax
  int v4; // edx
  int pObj4; // eax
  void *pMem2; // eax
  char *v7; // eax
  int v8; // edx
  int pObj2; // eax
  void *pMem3; // eax
  char *v11; // eax
  int v12; // edx
  int pObj3; // eax
  void *pMem4; // eax
  char *v15; // eax
  int v16; // edx
  int pObj; // eax
  int v18; // eax
  void *v19; // eax
  int v20; // edx
  int v21; // eax
  int fld_e1821; // edi
  int fld_e1820; // edx
  int v24; // edi
  uint32_t *v25; // eax
  uint64_t fld_e18202; // rax
  int result; // eax
  float v28; // [esp+2Ch] [ebp-34h]
  float v29; // [esp+30h] [ebp-30h]
  int v30; // [esp+48h] [ebp-18h] BYREF
  void *Block; // [esp+4Ch] [ebp-14h]
  int v32; // [esp+50h] [ebp-10h]
  int v33; // [esp+5Ch] [ebp-4h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0((size_t *)this + 1761, "R_VINO_ATK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 1691, "R_VINO_DMG", 0xAu);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 1709, "R_VINO_DIE", 0xAu);  // 【std::string构造赋值】
  sub_4015C0((size_t *)this + 1934, "SOR_APPEAR", 0xAu);  // 【std::string构造赋值】
  pMem = operator new(0x544u);
  Block = pMem;
  v33 = 0;
  if ( pMem != nullptr )
    v3 = sub_4BA9E0((char *)pMem, "Monster/Soceress/Hair01.equ", 0);
  else
    v3 = nullptr;
  v4 = *this;
  v33 = -1;
  pObj4 = (*(int (/*thiscall*/ **)(int *, char *))(v4 + 784))(this, v3);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem2 = operator new(0x544u);
  Block = pMem2;
  v33 = 1;
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0((char *)pMem2, "Monster/Soceress/Cloth01.equ", 0);
  else
    v7 = nullptr;
  v8 = *this;
  v33 = -1;
  pObj2 = (*(int (/*thiscall*/ **)(int *, char *))(v8 + 784))(this, v7);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = operator new(0x544u);
  Block = pMem3;
  v33 = 2;
  if ( pMem3 != nullptr )
    v11 = sub_4BA9E0((char *)pMem3, "Monster/Soceress/Weapon01.equ", 0);
  else
    v11 = nullptr;
  v12 = *this;
  v33 = -1;
  pObj3 = (*(int (/*thiscall*/ **)(int *, char *))(v12 + 784))(this, v11);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem4 = operator new(0x544u);
  Block = pMem4;
  v33 = 3;
  if ( pMem4 != nullptr )
    v15 = sub_4BA9E0((char *)pMem4, "Monster/Soceress/Acc01.equ", 0);
  else
    v15 = nullptr;
  v16 = *this;
  v33 = -1;
  pObj = (*(int (/*thiscall*/ **)(int *, char *))(v16 + 784))(this, v15);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  v18 = *this;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 570;
  v19 = (void *)(*(int (/*thiscall*/ **)(int *, uint32_t))(v18 + 384))(this, 0);
  v20 = *this;
  Block = v19;
  v21 = (*(int (/*thiscall*/ **)(int *, int))(v20 + 384))(this, 1);
  fld_e1821 = *(this + 1821);
  fld_e1820 = *(this + 1820);
  v32 = v21;
  v24 = fld_e1821 - fld_e1820;
  v25 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
  v29 = (float)v32;
  v28 = (float)(int)Block;
  fld_e18202 = (uint64_t)sub_4049C0(v28, v29, *v25 - *(this + 1820), v24);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e18202) = *this;
  *(this + 2150) = fld_e18202;
  *(this + 2152) = (*(int (/*thiscall*/ **)(int *, int))(HIDWORD(fld_e18202) + 384))(this, 2);
  *(this + 2159) = sub_699000((int)(this + 9));
  *(this + 2155) = *(this + 81);
  v30 = 100000;
  result = sub_4E1390(this, (uint32_t *)0x30004, &v30);
  *(this + 2154) = 30066;
  return result;
}


// 路易丝外观装载：Monster/Soceress/Luis_{Hair01,Cloth01,Weapon01,Acc01,Weapon02}.equ 五件
// ------------------------------------------------------------
// 0x594290 sub_594290
// ------------------------------------------------------------
int /*thiscall*/ sub_594290(int *this)
{
  int i; // edi
  void *pMem; // eax
  char *v4; // eax
  int v5; // edx
  int result; // eax
  void *v7[6]; // [esp+8h] [ebp-24h]
  int v8; // [esp+28h] [ebp-4h]

  v7[0] = "Monster/Soceress/Luis_Hair01.equ";
  v7[1] = "Monster/Soceress/Luis_Cloth01.equ";
  v7[2] = "Monster/Soceress/Luis_Weapon01.equ";
  v7[3] = "Monster/Soceress/Luis_Acc01.equ";
  v7[4] = "Monster/Soceress/Luis_Weapon02.equ";
  for ( i = 0; i < 5; ++i )
  {
    pMem = operator new(0x544u);
    v7[5] = pMem;
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



// 子类扩展字段复位（this+8600..8620）
// ------------------------------------------------------------
// 0x594340 sub_594340
// ------------------------------------------------------------
int /*thiscall*/ sub_594340(int this)
{
  uint32_t *pThis_21AC; // ecx

  *(uint8_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8601) = 0;
  *(uint8_t *)(this + 8602) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  pThis_21AC = (uint32_t *)(this + 8620);
  *pThis_21AC = 0;
  pThis_21AC[1] = 0;
  pThis_21AC[2] = 0;
  return 0;
}



// ============================================================
// 【分区 4】魔法师基类公共逻辑（0x594370-0x594B10）
// 证据：vt+212 "HOLD" 蓄力播报（0x5947A0）、子类 AI 字段(this+86xx)复位群

// AI 相位辅助
// ------------------------------------------------------------
// 0x594370 sub_594370
// ------------------------------------------------------------
int /*thiscall*/ sub_594370(int *this)
{
  int result; // eax

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
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



// AI 字段访问（this+8602）
// ------------------------------------------------------------
// 0x5943F0 sub_5943F0
// ------------------------------------------------------------
char /*thiscall*/ sub_5943F0(uint32_t *this)
{
  int fld_e30; // edi
  int v3; // eax
  char result; // al

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(uint32_t *)(*(this + 28) + 192) == 4
    && *((uint8_t *)this + 8602) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(
      this,
      0,
      0,
      0,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 896))(this, 4, 4);
  }
  if ( *(uint32_t *)(*(this + 28) + 192) == 4 && *((uint8_t *)this + 8602) == 0 )
  {
    fld_e30 = *(this + 30);
    v3 = sub_491C70(fld_e30, 1);
    sub_493A60(fld_e30, v3);
    *((uint8_t *)this + 8602) = 1;
  }
  result = *(uint8_t *)(*(this + 30) + 170);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
  return result;
}



// 子类扩展字段复位（105L）
// ------------------------------------------------------------
// 0x594490 sub_594490
// ------------------------------------------------------------
void /*thiscall*/ sub_594490(int this)
{
  double v2; // st7
  int v3; // ebx
  int *fld_78; // ecx

  sub_4E1780((uint32_t *)this);
  if ( *(uint32_t *)(this + 6556) != 8 )
  {
    if ( *(uint32_t *)(this + 6556) == 14 )
    {
      sub_595E50(this);
    }
    else if ( *(uint32_t *)(this + 6556) == 15 )
    {
      sub_5943F0((uint32_t *)this);
    }
    return;
  }
  if ( sub_41A5E0(this + 7028) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 && *(uint8_t *)(this + 8600) == 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
    *(uint8_t *)(this + 8600) = 1;
  }
  if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 || sub_41A5E0(this + 7028) == 3 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) == 0 )
    {
LABEL_28:
      if ( *(uint8_t *)(this + 8601) != 0
        && *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4
        && *(uint8_t *)(this + 8602) == 0 )
      {
        v3 = 0;
        if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 )
        {
          v3 = 6;
        }
        else if ( sub_41A5E0(this + 7028) == 3 )
        {
          v3 = 2;
        }
        sub_4AECE0(*(void **)(this + 120), v3);
        *(uint8_t *)(this + 8602) = 1;
      }
      goto LABEL_37;
    }
    if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 1 )
    {
      if ( *(uint8_t *)(this + 8601) != 0 )
      {
LABEL_25:
        if ( *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4 && *(uint8_t *)(this + 8602) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
        }
        goto LABEL_28;
      }
      if ( sub_41A5E0(this + 7028) == 1 )
      {
        sub_596030(1000);
        sub_4A0550(120);
      }
      else if ( sub_41A5E0(this + 7028) == 2 )
      {
        v2 = (double)sub_5985E0(400.0);
        if ( v2 < 300.0 )
          v2 = 300.0;
        sub_4A05C0((uint64_t)(v2 * 0.5));
      }
      else if ( sub_41A5E0(this + 7028) == 3 )
      {
        sub_596030(1000);
        sub_4A0550(90);
      }
    }
    if ( *(uint8_t *)(this + 8601) == 0 )
    {
LABEL_37:
      if ( *(float *)(*(uint32_t *)(this + 112) + 24) > 0.0 && *(uint8_t *)(this + 8601) == 0 )
      {
        fld_78 = *(int **)(this + 120);
        if ( fld_78[37] < 1 )
          sub_4AECE0(fld_78, 1);
        *(uint8_t *)(this + 8601) = 1;
      }
      return;
    }
    goto LABEL_25;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5946D0 sub_5946D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5946D0(uint32_t *this, int nArg2)
{
  int result; // eax
  int fld_e1554; // eax
  int fld_e2154; // edx
  int fld_e2151; // edi
  int fld_e21512; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2151) )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
    if ( result == 14 && (int)*(this + 2153) > 1 )
    {
      fld_e1554 = sub_491C10(*(uint32_t *)*(this + 1554));
      fld_e2154 = *(this + 2154) + 1;
      *(this + 2154) = fld_e2154;
      if ( fld_e2154 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2153);
        *(this + 2154) = 0;
      }
      fld_e2151 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 120))(*(this + 2151));
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 916))(*(this + 2151));
      fld_e21512 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 120))(*(this + 2151));
      v8 = *this;
      v9 = fld_e2151 - fld_e21512;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v11);
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 112))(this, v12 - v9);
    }
  }
  return result;
}



// 蓄力技能：vt+212 广播 "HOLD"（104L；sub_4049C0 插值控制蓄力表现）
// ------------------------------------------------------------
// 0x5947A0 sub_5947A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5947A0(int *this, int pArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2151; // ecx
  int v6; // eax
  int fld_e21512; // ecx
  int v8; // eax
  int fld_e21513; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int fld_e21514; // ecx
  int v14; // eax
  int v15; // ebx
  int fld_e21515; // edi
  int v17; // edx
  int v18; // eax
  int v19; // eax
  uint32_t *fld_e28; // edi
  int v21; // eax
  int fld_e1821; // edi
  uint32_t *v23; // eax
  int nRand; // eax
  float v26; // [esp+70h] [ebp-24h]
  float v27; // [esp+74h] [ebp-20h]
  int v28; // [esp+8Ch] [ebp-8h]
  int fld_e215152; // [esp+90h] [ebp-4h]
  int v30; // [esp+9Ch] [ebp+8h]
  int v31; // [esp+9Ch] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
    || (*(this + 2151) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2151) = 0;
  }
  fld_e2151 = *(this + 2151);
  if ( fld_e2151 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2151 + 120))(fld_e2151);
    fld_e21512 = *(this + 2151);
    *(this + 2155) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512);
    fld_e21513 = *(this + 2151);
    *(this + 2156) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21513 + 128))(fld_e21513);
    v11 = *this;
    *(this + 2157) = v10;
    v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 152))(this);
    fld_e21514 = *(this + 2151);
    if ( v12 != 0 )
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) - 30;
    else
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) + 30;
    v15 = *this;
    v30 = v14;
    fld_e21515 = *(this + 2151);
    v17 = *(uint32_t *)fld_e21515;
    fld_e215152 = fld_e21515;
    v18 = (*(int (/*thiscall*/ **)(int))(v17 + 128))(fld_e21515);
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21515 + 124))(fld_e21515, v18 + 40);
    (*(void (/*thiscall*/ **)(int *, int, int))(v15 + 112))(this, v30, v19 + 1);
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2151) + 848))(*(this + 2151), 1);
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  fld_e215152 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0);
  v21 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v31 = v21;
  v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
  v27 = (float)v31;
  v26 = (float)fld_e215152;
  *(this + 2153) = (uint64_t)sub_4049C0(v26, v27, *v23 - *(this + 1820), fld_e1821);
  *(this + 2152) = 0;
  *(this + 2154) = 0;
  v28 = 0;
  fld_e215152 = 1;
  nRand = rand() % 2;
  sub_4DB200(24, *(&v28 + nRand));
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5949F0 sub_5949F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5949F0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e1905; // eax
  double v5; // st7

  result = nArg3;
  if ( nArg3 == 0 )
  {
    result = nArg2;
    if ( nArg2 == 2 || nArg2 == 1 )
    {
      fld_e1905 = *(this + 1905);
      v5 = *(float *)(fld_e1905 + 100);
      result = fld_e1905 + 96;
      *(float *)(result + 4) = v5 * 0.76923078;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x594A20 sub_594A20
// ------------------------------------------------------------
int /*thiscall*/ sub_594A20(int this, int nArg2, int nArg3)
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
    if ( nArg3 == 2 )
      *(uint8_t *)(this + 7534) = 1;
  }
  else if ( nArg2 == 2 || nArg2 == 1 )
  {
    *(uint32_t *)(this + 7596) = -30;
    *(uint32_t *)(this + 7568) = 1;
    *(float *)(*(uint32_t *)(this + 7620) + 100) = *(float *)(*(uint32_t *)(this + 7620) + 100) * 1.3;
  }
  else if ( nArg2 == 0 )
  {
    *(uint32_t *)(this + 7568) = 1;
    *(uint32_t *)(this + 7596) = -30;
  }
  return result;
}



// ============================================================
// 【分区 5】狐狸系·本体与黑足（Lugaru / Kurogaru）（0x594B10-0x5968D0）
// 证据：R_FOX_TALK/DMG + FOX_DIE 语音、FOX_ATK/FOX_BITE_LOOP 攻击、
//       Monster/Lugaru/Teeth.equ 牙齿外观、B_KUROGARU_01 登场曲

// 语音注册：R_FOX_TALK(0xA) / R_FOX_DMG(9) / FOX_DIE(7) 狐狸三件套（权重参数随 TAG 不同）
// ------------------------------------------------------------
// 0x594B10 sub_594B10
// ------------------------------------------------------------
int /*thiscall*/ sub_594B10(uint32_t *this)
{
  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  return sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x594B80 sub_594B80
// ------------------------------------------------------------
int /*thiscall*/ sub_594B80(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 3
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
// 0x594C80 sub_594C80
// ------------------------------------------------------------
void /*usercall*/ sub_594C80(int *pDwArg1@<ecx>, int nArg2@<ebx>)
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

  pObj3 = pDwArg1[2151];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(
           pDwArg1[2151],
           pDwArg1[2155],
           pDwArg1[2156],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2155], pDwArg1[2156], pDwArg1[2157]);
    }
    else
    {
      pObj = pDwArg1[2151];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2155, pDwArg1 + 2156, v7);
      pObj2 = pDwArg1[2151];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2155], pDwArg1[2156], pDwArg1[2157]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2157]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )
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
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x594E80 sub_594E80
// ------------------------------------------------------------
int /*userpurge*/ sub_594E80@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2151] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
      sub_594C80(pDwArg1, nArg2);
    pDwArg1[2151] = 0;
  }
  if ( pDwArg3 == pDwArg1 )
  {
    if ( pDwArg1[2151] != 0 )
    {
      sub_594C80(pDwArg1, nArg2);
      pDwArg1[2151] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  return sub_4D9170(pDwArg3);
}



// 攻击 AI：vt+212 播报 FOX_ATK（狐狸扑击）
// ------------------------------------------------------------
// 0x594EF0 sub_594EF0
// ------------------------------------------------------------
int /*userpurge*/ sub_594EF0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int v8; // edx

  v7 = pDwArg1[1639];
  if ( v7 == 15 )
  {
    if ( ArgList != 15 )
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  else if ( v7 == 14 )
  {
    sub_594C80(pDwArg1, nArg2);
  }
  switch ( ArgList )
  {
    case 8:
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);
      break;
    case 14:
      sub_5947A0(pDwArg1, nArg4);
      break;
    case 15:
      sub_597890(pDwArg1);
      break;
    default:
      break;
  }
  return sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);
}



// 子类扩展字段复位（this+8600..8624）
// ------------------------------------------------------------
// 0x594F90 sub_594F90
// ------------------------------------------------------------
int /*thiscall*/ sub_594F90(int this)
{
  uint32_t *pThis_21B0; // ecx

  *(uint8_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8601) = 0;
  *(uint8_t *)(this + 8602) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8612) = 0;
  *(uint8_t *)(this + 8608) = 0;
  pThis_21B0 = (uint32_t *)(this + 8624);
  *pThis_21B0 = 0;
  pThis_21B0[1] = 0;
  pThis_21B0[2] = 0;
  return 0;
}



// AI 字段访问（this+8608）
// ------------------------------------------------------------
// 0x594FD0 sub_594FD0
// ------------------------------------------------------------
char /*thiscall*/ sub_594FD0(uint8_t *this)
{
  char result; // al

  result = *(this + 8608);
  if ( result == 0 )
    return sub_4E1BE0();
  return result;
}



// AI 字段访问（this+8608）
// ------------------------------------------------------------
// 0x594FE0 sub_594FE0
// ------------------------------------------------------------
char /*thiscall*/ sub_594FE0(uint8_t *this)
{
  char result; // al
  unsigned int pThis_2A0; // edi
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // edx
  int v13; // edx
  int pObj; // eax
  int v15; // [esp+4h] [ebp-4h]
  int v16; // [esp+4h] [ebp-4h]

  result = *(this + 8608);
  if ( result != 0 )
  {
    pThis_2A0 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 672))(this, 0);
    *(float *)&v15 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 830)) - 0.30000001;
    sub_41A590(pThis_2A0 + 830, v4, v15);
    *(float *)&v16 = COERCE_FLOAT(sub_41A5E0(pThis_2A0 + 858)) - 0.2;
    sub_41A590(pThis_2A0 + 858, v16, v16);
    v5 = sub_41A5E0(pThis_2A0 + 928);
    sub_41A590(pThis_2A0 + 928, v6, v5 - 200);
    v7 = sub_41A5E0(pThis_2A0 + 144);
    sub_41A590(pThis_2A0 + 144, v8, v7 - 25);
    v9 = sub_41A5E0(pThis_2A0 + 60);
    sub_41A590(pThis_2A0 + 60, v10, v9 - 25);
    pThis_2A0 += 88;
    v11 = sub_41A5E0(pThis_2A0);
    sub_41A590(pThis_2A0, v12, v11 - 25);
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    v13 = *(uint32_t *)this;
    *(this + 8608) = 0;
    pObj = (*(int (/*thiscall*/ **)(uint8_t *, int))(v13 + 788))(this, 7);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
    return sub_4DB200(24, 4);
  }
  return result;
}



// 子类扩展字段复位（105L）
// ------------------------------------------------------------
// 0x5950F0 sub_5950F0
// ------------------------------------------------------------
void /*thiscall*/ sub_5950F0(int this)
{
  double v2; // st7
  int v3; // ebx
  int *fld_78; // ecx

  sub_4E1780((uint32_t *)this);
  if ( *(uint32_t *)(this + 6556) != 8 )
  {
    if ( *(uint32_t *)(this + 6556) == 14 )
    {
      sub_597120(this);
    }
    else if ( *(uint32_t *)(this + 6556) == 15 )
    {
      sub_5943F0((uint32_t *)this);
    }
    return;
  }
  if ( sub_41A5E0(this + 7028) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 && *(uint8_t *)(this + 8600) == 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
    *(uint8_t *)(this + 8600) = 1;
  }
  if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 || sub_41A5E0(this + 7028) == 3 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) == 0 )
    {
LABEL_28:
      if ( *(uint8_t *)(this + 8601) != 0
        && *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4
        && *(uint8_t *)(this + 8602) == 0 )
      {
        v3 = 0;
        if ( sub_41A5E0(this + 7028) == 1 || sub_41A5E0(this + 7028) == 2 )
        {
          v3 = 6;
        }
        else if ( sub_41A5E0(this + 7028) == 3 )
        {
          v3 = 2;
        }
        sub_4AECE0(*(void **)(this + 120), v3);
        *(uint8_t *)(this + 8602) = 1;
      }
      goto LABEL_37;
    }
    if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 1 )
    {
      if ( *(uint8_t *)(this + 8601) != 0 )
      {
LABEL_25:
        if ( *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4 && *(uint8_t *)(this + 8602) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
            this,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 896))(this, 4, 4);
        }
        goto LABEL_28;
      }
      if ( sub_41A5E0(this + 7028) == 1 )
      {
        sub_596030(1000);
        sub_4A0550(120);
      }
      else if ( sub_41A5E0(this + 7028) == 2 )
      {
        v2 = (double)sub_5985E0(400.0);
        if ( v2 < 300.0 )
          v2 = 300.0;
        sub_4A05C0((uint64_t)(v2 * 0.5));
      }
      else if ( sub_41A5E0(this + 7028) == 3 )
      {
        sub_596030(1000);
        sub_4A0550(90);
      }
    }
    if ( *(uint8_t *)(this + 8601) == 0 )
    {
LABEL_37:
      if ( *(float *)(*(uint32_t *)(this + 112) + 24) > 0.0 && *(uint8_t *)(this + 8601) == 0 )
      {
        fld_78 = *(int **)(this + 120);
        if ( fld_78[37] < 1 )
          sub_4AECE0(fld_78, 1);
        *(uint8_t *)(this + 8601) = 1;
      }
      return;
    }
    goto LABEL_25;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x595330 sub_595330
// ------------------------------------------------------------
int /*thiscall*/ sub_595330(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e1905; // eax
  double v5; // st7

  if ( nArg3 == 0 || (result = nArg3 - 2, nArg3 == 2) && (result = nArg2, nArg2 == 0) )
  {
    *(float *)(*(this + 1905) + 100) = *(float *)(*(this + 1905) + 100) * 0.76923078;
    fld_e1905 = *(this + 1905);
    v5 = *(float *)(fld_e1905 + 68);
    result = fld_e1905 + 64;
    *(float *)(result + 4) = v5 * 0.76923078;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x595380 sub_595380
// ------------------------------------------------------------
int /*thiscall*/ sub_595380(int this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_1DC4; // eax
  double v5; // st7

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
  if ( nArg3 == 0 )
    goto LABEL_7;
  if ( nArg3 == 2 )
  {
    if ( nArg2 == 2 || nArg2 == 1 )
    {
      *(uint8_t *)(this + 7537) = 1;
      return result;
    }
    if ( nArg2 == 0 )
    {
      *(uint8_t *)(this + 7537) = 1;
LABEL_7:
      fld_1DC4 = *(uint32_t *)(this + 7620);
      *(uint32_t *)(this + 7596) = 50;
      *(uint32_t *)(this + 7568) = 2;
      v5 = *(float *)(fld_1DC4 + 100) * 1.3;
      result = fld_1DC4 + 96;
      *(float *)(result + 4) = v5;
      *(float *)(*(uint32_t *)(this + 7620) + 68) = *(float *)(*(uint32_t *)(this + 7620) + 68) * 1.3;
    }
  }
  return result;
}



// 语音注册：R_FOX_TALK/DMG + FOX_DIE（第二只狐狸实例, sub_4049C0 插值）
// ------------------------------------------------------------
// 0x595470 sub_595470
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_595470(float *this)
{
  uint32_t *pThis_2A0; // eax
  double pThis_71C; // st7
  int v4; // eax
  int pThis_71D; // edi
  uint32_t *pThis_2A02; // eax
  uint64_t result; // rax
  float v8; // [esp+18h] [ebp-20h]
  float v9; // [esp+18h] [ebp-20h]
  float v10; // [esp+1Ch] [ebp-1Ch]
  float v11; // [esp+1Ch] [ebp-1Ch]
  int pThis_180; // [esp+30h] [ebp-8h]
  int pThis_1803; // [esp+30h] [ebp-8h]
  int pThis_1802; // [esp+34h] [ebp-4h]
  int v15; // [esp+34h] [ebp-4h]

  *((uint32_t *)this + 1698) = 2;
  *((uint32_t *)this + 1699) = 2;
  *((uint32_t *)this + 1700) = 2;
  *((uint32_t *)this + 1701) = 3;
  *((uint32_t *)this + 1702) = 4;
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
  pThis_180 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 2);
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  pThis_2A0 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v10 = (float)pThis_1802;
  v8 = (float)pThis_180;
  pThis_71C = sub_4049C0(v8, v10, *pThis_2A0 - *((uint32_t *)this + 1820), *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820));  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  v4 = *(uint32_t *)this;
  *(this + 106) = pThis_71C;
  v15 = (*(int (/*thiscall*/ **)(float *, int))(v4 + 384))(this, 4);
  pThis_1803 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);
  pThis_71D = *((uint32_t *)this + 1821) - *((uint32_t *)this + 1820);
  pThis_2A02 = (uint32_t *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3);
  v11 = (float)pThis_1803;
  v9 = (float)v15;
  result = (uint64_t)sub_4049C0(v9, v11, *pThis_2A02 - *((uint32_t *)this + 1820), pThis_71D);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *((uint32_t *)this + 109) = result;
  return result;
}



// 登场曲：sub_406D60 写 "B_KUROGARU_01"（黑足 Kurogaru 曲目槽）
// ------------------------------------------------------------
// 0x5955B0 sub_5955B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5955B0(int *this)
{
  int result; // eax

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        result = sub_406D60("B_KUROGARU_01");
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



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x595650 sub_595650
// ------------------------------------------------------------
int /*thiscall*/ sub_595650(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 3
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



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x595750 sub_595750
// ------------------------------------------------------------
void /*thiscall*/ sub_595750(uint32_t *this)
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
    pObj = sub_4E7F30(this, 100, 80, 0);
    if ( pObj != 0 )
    {
      v3 = *this;
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, bool))(v3 + 144))(this, v5 < v4);
      memset(&pBuf[1], 0, 12);
      v7[3] = 0;
      v7[0] = 2;
      sub_431230((int)pBuf, v7);
      (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
      sub_5E5260(pBuf);
    }
  }
}



// 参数打包 AI（89L sub_431230）
// ------------------------------------------------------------
// 0x595820 sub_595820
// ------------------------------------------------------------
void /*usercall*/ sub_595820(int *pDwArg1@<ecx>, int nArg2@<ebx>)
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

  pObj3 = pDwArg1[2151];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(
           pDwArg1[2151],
           pDwArg1[2156],
           pDwArg1[2157],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);
    }
    else
    {
      pObj = pDwArg1[2151];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2156, pDwArg1 + 2157, v7);
      pObj2 = pDwArg1[2151];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2158]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )
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
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x595A20 sub_595A20
// ------------------------------------------------------------
int /*userpurge*/ sub_595A20@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3)
{
  if ( *(uint8_t *)(pArg1 + 8608) != 0 && nArg3 == *(uint32_t *)(pArg1 + 7252) )
    sub_594FE0((uint8_t *)pArg1);
  if ( nArg3 == *(uint32_t *)(pArg1 + 8604) )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 14 )
      sub_595820((int *)pArg1, nArg2);
    *(uint32_t *)(pArg1 + 8604) = 0;
  }
  if ( nArg3 == pArg1 )
  {
    if ( *(uint32_t *)(pArg1 + 8604) != 0 )
    {
      sub_595820((int *)pArg1, nArg2);
      *(uint32_t *)(pArg1 + 8604) = 0;
    }
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 216))(pArg1, 33);
  }
  return sub_4D9170(nArg3);
}



// 外观装载：Monster/Lugaru/Teeth.equ（獠牙/牙齿部件, sub_4BA9E0）
// ------------------------------------------------------------
// 0x595AB0 sub_595AB0
// ------------------------------------------------------------
char /*usercall*/ sub_595AB0@<al>(uint8_t *pArg1@<ecx>, int nArg2@<esi>)
{
  char result; // al
  unsigned int v4; // esi
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  void *pMem; // eax
  char *v15; // eax
  int v16; // edx
  int pObj; // eax
  int nRand; // eax
  int v19; // [esp+4h] [ebp-14h]
  void *Block; // [esp+8h] [ebp-10h]
  int v21; // [esp+14h] [ebp-4h]

  result = pArg1[8608];
  if ( result == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, int))(*(uint32_t *)pArg1 + 672))(pArg1, 0, nArg2);
    *(float *)&Block = COERCE_FLOAT(sub_41A5E0(v4 + 830)) + 0.30000001;
    sub_41A590(v4 + 830, v5, (int)Block);
    *(float *)&Block = COERCE_FLOAT(sub_41A5E0(v4 + 858)) + 0.2;
    sub_41A590(v4 + 858, (int)Block, (int)Block);
    v6 = sub_41A5E0(v4 + 928);
    sub_41A590(v4 + 928, v7, v6 + 200);
    v8 = sub_41A5E0(v4 + 144);
    sub_41A590(v4 + 144, v9, v8 + 25);
    v10 = sub_41A5E0(v4 + 60);
    sub_41A590(v4 + 60, v11, v10 + 25);
    v4 += 88;
    v12 = sub_41A5E0(v4);
    sub_41A590(v4, v13, v12 + 25);
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pArg1 + 676))(pArg1, 0);
    pArg1[8608] = 1;
    pMem = operator new(0x544u);
    Block = pMem;
    v21 = 0;
    if ( pMem != nullptr )
      v15 = sub_4BA9E0((char *)pMem, "Monster/Lugaru/Teeth.equ", 0);
    else
      v15 = nullptr;
    v16 = *(uint32_t *)pArg1;
    v21 = -1;
    pObj = (*(int (/*thiscall*/ **)(uint8_t *, char *))(v16 + 784))(pArg1, v15);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
    v19 = 2;
    Block = (void *)3;
    nRand = rand() % 2;
    return sub_4DB200(24, *(&v19 + nRand));
  }
  return result;
}



// AI 相位门（this+8602/8604/8612）
// ------------------------------------------------------------
// 0x595C40 sub_595C40
// ------------------------------------------------------------
int /*thiscall*/ sub_595C40(int this)
{
  int v2; // edi
  int pThis_7C; // eax
  int pThis_78; // eax
  int pThis_80; // edi
  int v6; // eax
  int fld_219C; // eax
  int fld_219C2; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int pThis_98; // eax
  int v15; // eax
  int result; // eax

  if ( *(int *)(this + 8612) > 0 )
    sub_595AB0((uint8_t *)this, this);
  v2 = *(uint32_t *)this;
  pThis_7C = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 124))(this, 0);
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(v2 + 136))(this, pThis_78) == 0
    || (pThis_80 = *(uint32_t *)this,
        v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this),
        (*(uint8_t (/*thiscall*/ **)(int, int))(pThis_80 + 132))(this, v6) == 0) )
  {
    fld_219C = *(uint32_t *)(this + 8604);
    if ( fld_219C != 0 )
    {
      fld_219C2 = *(uint32_t *)(this + 8604);
      v9 = *(uint32_t *)this;
      v10 = (*(int (**)(void))(*(uint32_t *)fld_219C + 128))();
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_219C2 + 124))(fld_219C2, v10 + 40);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_219C2 + 120))(fld_219C2, v11);
      (*(void (/*thiscall*/ **)(int, int))(v9 + 112))(this, v12);
    }
  }
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 6216) + 4));
  (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
    this,
    0,
    200,
    200,
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
  (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);
  v13 = *(uint32_t *)this;
  pThis_98 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, 4);
  v15 = sub_432E50(pThis_98);
  (*(void (/*thiscall*/ **)(int, int))(v13 + 896))(this, v15);
  sub_495890(2, 0);
  result = sub_4A0550(10);
  *(uint8_t *)(this + 8602) = 0;
  return result;
}



// 攻击 AI：vt+212 播报 FOX_ATK
// ------------------------------------------------------------
// 0x595D70 sub_595D70
// ------------------------------------------------------------
int /*userpurge*/ sub_595D70@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int v8; // edx

  v7 = pDwArg1[1639];
  if ( v7 == 15 )
  {
    if ( ArgList != 15 )
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  else if ( v7 == 14 )
  {
    sub_595820(pDwArg1, nArg2);
  }
  switch ( ArgList )
  {
    case 8:
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);
      break;
    case 14:
      sub_597640(LODWORD(fArg4));
      break;
    case 15:
      sub_595C40((int)pDwArg1);
      break;
    default:
      break;
  }
  return sub_4E33D0(ArgList, fArg4, nArg5, nArg6);
}



// 子类扩展字段复位（this+8600..8628）
// ------------------------------------------------------------
// 0x595E10 sub_595E10
// ------------------------------------------------------------
int /*thiscall*/ sub_595E10(int this)
{
  uint32_t *pThis_21B4; // ecx

  *(uint8_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8601) = 0;
  *(uint8_t *)(this + 8602) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8608) = 0;
  *(uint32_t *)(this + 8624) = 0;
  pThis_21B4 = (uint32_t *)(this + 8628);
  *pThis_21B4 = 0;
  pThis_21B4[1] = 0;
  pThis_21B4[2] = 0;
  return 0;
}



// 撕咬连击 AI：vt+212 播报 FOX_BITE_LOOP（33ms 延迟参数, 100L）
// ------------------------------------------------------------
// 0x595E50 sub_595E50
// ------------------------------------------------------------
int /*usercall*/ sub_595E50@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
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

  pObj = pArg1[2151];
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
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 15;
        else
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 15;
        v23 = v5;
        v6 = (double)v5;
        v7 = *pArg1;
        v17 = v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 124))(pArg1);
        v9 = *pArg1;
        v23 = v8;
        v18 = (float)v8;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(pArg1);
        v11 = pArg1[2151];
        v23 = v10 + 45;
        v19 = (float)(v10 + 45);
        sub_4E5F70(nArg2, (int)pArg1, v11, &v17, 1, 1);
      }
      v12 = pArg1[2153];
      v13 = pArg1[2152] + 1;
      pArg1[2152] = v13;
      if ( v13 >= v12
        || (v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 684))(pArg1[2151]), sub_41A5E0(v14) <= 0) )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
      }
      else
      {
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
        sub_4926A0(v15);
      }
      if ( pArg1[2152] == 1 )
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "FOX_BITE_LOOP", 33, 0, 0);
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2151] + 604))(pArg1[2151], 0);
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2151] + 612))(pArg1[2151], 1, 1);
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 840))(pArg1[2151]);
    if ( result != 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 308))(pArg1[2151]);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2151] + 560))(
                 pArg1[2151],
                 9,
                 0,
                 0,
                 0);
    }
  }
  return result;
}



// AI 相位辅助（71L）
// ------------------------------------------------------------
// 0x596030 sub_596030
// ------------------------------------------------------------
int /*userpurge*/ sub_596030@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)
{
  int result; // eax
  int v6; // edi
  int v7; // edi
  long double v8; // st7
  double v10; // st6
  uint8_t v11; // c0
  uint8_t v12; // c2
  double v13; // st6
  int v14; // ebx
  float v15; // [esp+4h] [ebp-8h]
  float v16; // [esp+8h] [ebp-4h]
  float v17; // [esp+14h] [ebp+8h]

  result = pArg1[1813];
  if ( result != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)result + 120))(result, nArg3, nArg2);
    v16 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - v6) * 1.2;
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);
    v8 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1) - v7) * 1.2;
    v10 = v16;
    if ( (v11 | v12) != 0 )
    {
      if ( v10 <= -200.0 )
        v16 = -200.0;
    }
    else if ( v10 >= 200.0 )
    {
      v16 = 200.0;
    }
    if ( v8 >= 0.0 )
    {
      if ( v8 >= 100.0 )
        v8 = 100.0;
    }
    else if ( v8 <= -100.0 )
    {
      v8 = -100.0;
    }
    v13 = (double)nArg4;
    v17 = fabs(v16) / v13 * 1000.0;
    v15 = fabs(v8) / v13 * 1000.0;
    v14 = 3;
    if ( v8 >= 0.0 )
      v14 = 2;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
      pArg1,
      0,
      (uint64_t)v17,
      (uint64_t)v17,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
      pArg1,
      1,
      (uint64_t)v15,
      (uint64_t)v15,
      0,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t *, bool, int))(*pArg1 + 896))(pArg1, v16 < 0.0, v14);
  }
  return result;
}



// AI 相位辅助（107L）
// ------------------------------------------------------------
// 0x5961B0 sub_5961B0
// ------------------------------------------------------------
void /*usercall*/ sub_5961B0(int pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // edi
  double v4; // st7
  int v5; // ebx
  int *v6; // ecx

  sub_4E1780((uint32_t *)pArg1);
  if ( *(uint32_t *)(pArg1 + 6556) != 8 )
  {
    if ( *(uint32_t *)(pArg1 + 6556) == 14 )
    {
      sub_595E50((uint32_t *)pArg1, nArg2);
    }
    else if ( *(uint32_t *)(pArg1 + 6556) == 15 )
    {
      sub_5943F0((uint32_t *)pArg1);
    }
    return;
  }
  v3 = pArg1 + 7028;
  if ( sub_41A5E0(pArg1 + 7028) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 && *(uint8_t *)(pArg1 + 8600) == 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);
    *(uint8_t *)(pArg1 + 8600) = 1;
  }
  if ( sub_41A5E0(pArg1 + 7028) >= 1 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 )
    {
LABEL_27:
      if ( *(uint8_t *)(pArg1 + 8601) != 0 && *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )
      {
        v5 = 0;
        if ( sub_41A5E0(pArg1 + 7028) == 1 || sub_41A5E0(pArg1 + 7028) == 2 )
          v5 = 6;
        if ( sub_41A5E0(pArg1 + 7028) == 4 )
        {
          v5 = 9;
        }
        else if ( sub_41A5E0(pArg1 + 7028) == 3 )
        {
          v5 = 2;
        }
        sub_4AECE0(*(void **)(pArg1 + 120), v5);
        *(uint8_t *)(pArg1 + 8602) = 1;
      }
      goto LABEL_38;
    }
    if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )
    {
      if ( *(uint8_t *)(pArg1 + 8601) != 0 )
      {
LABEL_24:
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 896))(pArg1, 4, 4);
        }
        goto LABEL_27;
      }
      if ( sub_41A5E0(pArg1 + 7028) == 1 || sub_41A5E0(pArg1 + 7028) == 4 )
      {
        sub_596030((uint32_t *)pArg1, nArg2, v3, 1000);
        sub_4A0550(120);
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 2 )
      {
        v4 = (double)sub_5985E0(400.0);
        if ( v4 < 300.0 )
          v4 = 300.0;
        sub_4A05C0((uint64_t)(v4 * 0.5));
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 3 )
      {
        sub_596030((uint32_t *)pArg1, nArg2, v3, 1000);
        sub_4A0550(90);
      }
    }
    if ( *(uint8_t *)(pArg1 + 8601) == 0 )
    {
LABEL_38:
      if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) > 0.0 && *(uint8_t *)(pArg1 + 8601) == 0 )
      {
        v6 = *(int **)(pArg1 + 120);
        if ( v6[37] < 1 )
          sub_4AECE0(v6, 1);
        *(uint8_t *)(pArg1 + 8601) = 1;
      }
      return;
    }
    goto LABEL_24;
  }
}



// 治愈技能：vt+212 播报 FOX_CURE（110L；治愈狐治疗演出, sub_4049C0 插值）
// ------------------------------------------------------------
// 0x596400 sub_596400
// ------------------------------------------------------------
int /*thiscall*/ sub_596400(int *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int *v10; // edi
  int v11; // ebx
  int v12; // ebx
  uint64_t v13; // rax
  int v14; // ebx
  int v15; // ebx
  int v16; // eax
  int pObj; // eax
  float v18; // [esp+10h] [ebp-34h]
  float fld_e2155; // [esp+10h] [ebp-34h]
  float v20; // [esp+14h] [ebp-30h]
  void *Block; // [esp+2Ch] [ebp-18h]
  int v22; // [esp+30h] [ebp-14h]
  unsigned int v23; // [esp+34h] [ebp-10h]
  uint32_t *v24; // [esp+34h] [ebp-10h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v23 = i;
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
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
        v10 = *(int **)(v9 + 4 * i);
      else
        v10 = nullptr;
      v11 = (*(int (/*thiscall*/ **)(int *))(*v10 + 376))(v10);
      if ( v11 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this)
        && (*(int (/*thiscall*/ **)(int *, int *, uint32_t))(*this + 8))(this, v10, 0) <= 300
        && (*(this + 1908) != 2 || this != v10) )
      {
        v12 = (*(int (/*thiscall*/ **)(int *))(*v10 + 740))(v10) / 2;
        if ( (*(int (/*thiscall*/ **)(int *))(*v10 + 736))(v10) < v12
          && (*(int (/*thiscall*/ **)(int *))(*v10 + 736))(v10) > 0
          && rand() % 100 >= 70 )
        {
          result = *(this + 2156);
          *(this + 2156) = result - 1;
          if ( result > 0 )
          {
            Block = (void *)(uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*v10 + 740))(v10) * 0.25);
            v13 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*v10 + 740))(v10) * 0.5);
            v22 = v13;
            v14 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*this + 1032))(this, HIDWORD(v13));
            v15 = *(uint32_t *)(v14 + 52) - *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 1032))(this) + 48);
            v24 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
            v16 = (*(int (/*thiscall*/ **)(int *))(*this + 1032))(this);
            v20 = (float)v22;
            v18 = (float)(int)Block;
            *(this + 2155) = (uint64_t)sub_4049C0(v18, v20, *v24 - *(uint32_t *)(v16 + 48), v15);
            if ( operator new(0x80u) != nullptr )
            {
              fld_e2155 = (float)*(this + 2155);
              pObj = sub_4D6810(LODWORD(fld_e2155), 500, 1, 1);
            }
            else
            {
              pObj = 0;
            }
            (*(void (/*thiscall*/ **)(int, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
              pObj,
              v10,
              this,
              0,
              0,
              0,
              -1);
            sub_4DB200(24, 2);
            return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                     this,
                     "FOX_CURE",
                     -1,
                     0,
                     0);
          }
          return result;
        }
      }
      i = v23;
    }
  }
  return result;
}



// 蓄力技能：vt+212 "HOLD"（104L）
// ------------------------------------------------------------
// 0x596650 sub_596650
// ------------------------------------------------------------
int /*thiscall*/ sub_596650(int *this, int pArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2151; // ecx
  int v6; // eax
  int fld_e21512; // ecx
  int v8; // eax
  int fld_e21513; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int fld_e21514; // ecx
  int v14; // eax
  int v15; // ebx
  int fld_e21515; // edi
  int v17; // edx
  int v18; // eax
  int v19; // eax
  uint32_t *fld_e28; // edi
  int v21; // eax
  int fld_e1821; // edi
  uint32_t *v23; // eax
  int nRand; // eax
  float v26; // [esp+70h] [ebp-24h]
  float v27; // [esp+74h] [ebp-20h]
  int v28; // [esp+8Ch] [ebp-8h]
  int fld_e215152; // [esp+90h] [ebp-4h]
  int v30; // [esp+9Ch] [ebp+8h]
  int v31; // [esp+9Ch] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
    || (*(this + 2151) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2151) = 0;
  }
  fld_e2151 = *(this + 2151);
  if ( fld_e2151 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2151 + 120))(fld_e2151);
    fld_e21512 = *(this + 2151);
    *(this + 2157) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512);
    fld_e21513 = *(this + 2151);
    *(this + 2158) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21513 + 128))(fld_e21513);
    v11 = *this;
    *(this + 2159) = v10;
    v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 152))(this);
    fld_e21514 = *(this + 2151);
    if ( v12 != 0 )
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) - 30;
    else
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) + 30;
    v15 = *this;
    v30 = v14;
    fld_e21515 = *(this + 2151);
    v17 = *(uint32_t *)fld_e21515;
    fld_e215152 = fld_e21515;
    v18 = (*(int (/*thiscall*/ **)(int))(v17 + 128))(fld_e21515);
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21515 + 124))(fld_e21515, v18 + 40);
    (*(void (/*thiscall*/ **)(int *, int, int))(v15 + 112))(this, v30, v19 + 1);
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2151) + 848))(*(this + 2151), 1);
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  fld_e215152 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0);
  v21 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v31 = v21;
  v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
  v27 = (float)v31;
  v26 = (float)fld_e215152;
  *(this + 2153) = (uint64_t)sub_4049C0(v26, v27, *v23 - *(this + 1820), fld_e1821);
  *(this + 2152) = 0;
  *(this + 2154) = 0;
  v28 = 0;
  fld_e215152 = 1;
  nRand = rand() % 2;
  sub_4DB200(24, *(&v28 + nRand));
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5968A0 sub_5968A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5968A0(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e1905; // eax
  double v5; // st7

  result = nArg2;
  if ( nArg2 == 0 )
  {
    fld_e1905 = *(this + 1905);
    v5 = *(float *)(fld_e1905 + 100);
    result = fld_e1905 + 96;
    *(float *)(result + 4) = v5 * 0.76923078;
  }
  return result;
}



// ============================================================
// 【分区 6】狐狸系·变种（治愈狐 FOX_CURE / Penril）（0x5968D0-0x598790）
// 证据：FOX_CURE 治愈播报（0x596400）、B_PENRIL_01 登场曲（0x597CA0）、HOLD 蓄力群

// AI 相位辅助
// ------------------------------------------------------------
// 0x5968D0 sub_5968D0
// ------------------------------------------------------------
int /*thiscall*/ sub_5968D0(int this, int nArg2, int nArg3)
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
  if ( nArg2 != 0 )
  {
    if ( nArg2 > 0 && nArg2 <= 2 )
      *(uint8_t *)(this + 7538) = 1;
  }
  else
  {
    *(uint32_t *)(this + 7596) = -30;
    *(float *)(*(uint32_t *)(this + 7620) + 100) = *(float *)(*(uint32_t *)(this + 7620) + 100) * 1.3;
  }
  return result;
}



// 语音注册：R_FOX_TALK/DMG + FOX_DIE（第三只狐狸实例）
// ------------------------------------------------------------
// 0x596990 sub_596990
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_596990(uint32_t *this)
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
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 2);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v3 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v6 = (float)v8;
  v5 = (float)v7;
  result = (uint64_t)sub_4049C0(v5, v6, *v3 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 2155) = result;
  *(this + 2156) = 3;
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x596A70 sub_596A70
// ------------------------------------------------------------
int /*thiscall*/ sub_596A70(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 3
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



// 参数打包 AI（75L）
// ------------------------------------------------------------
// 0x596B70 sub_596B70
// ------------------------------------------------------------
void /*thiscall*/ sub_596B70(int *this)
{
  int fld_e1813; // eax
  int fld_e18132; // edi
  int v4; // ebx
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      if ( *(this + 1813) != 0 )
      {
        if ( rand() % 100 >= 50 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
            && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 )
          {
            fld_e1813 = *(this + 1813);
            if ( fld_e1813 != 0 && (*(uint8_t (/*stdcall*/ **)(int))(*(uint32_t *)fld_e1813 + 40))(17) != 0 )
            {
              fld_e18132 = *(this + 1813);
              if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 128))(fld_e18132) > 60 )
              {
                v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 120))(fld_e18132);
                if ( (int)abs32(v4 - (*(int (/*thiscall*/ **)(int *))(*this + 120))(this)) < 100
                  && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 6
                   || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 7)
                  && rand() % 100 < (*(this + 1909) != 0 ? 15 : 30) )
                {
                  memset(&pBuf[1], 0, 12);
                  v6[3] = 0;
                  v6[0] = 4;
                  sub_431230((int)pBuf, v6);
                  (*(void (/*thiscall*/ **)(int *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
                  sub_5E5260(pBuf);
                }
              }
            }
          }
        }
        else
        {
          sub_596400(this);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
      if ( *(this + 1813) != 0 )
        goto LABEL_21;
      break;
    case 14:
    case 15:
      if ( *(this + 1813) != 0 )
LABEL_21:
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    default:
      return;
  }
}



// 参数打包 AI（89L）
// ------------------------------------------------------------
// 0x596D90 sub_596D90
// ------------------------------------------------------------
void /*usercall*/ sub_596D90(int *pDwArg1@<ecx>, int nArg2@<ebx>)
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

  pObj3 = pDwArg1[2151];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(
           pDwArg1[2151],
           pDwArg1[2157],
           pDwArg1[2158],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2157], pDwArg1[2158], pDwArg1[2159]);
    }
    else
    {
      pObj = pDwArg1[2151];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2157, pDwArg1 + 2158, v7);
      pObj2 = pDwArg1[2151];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2157], pDwArg1[2158], pDwArg1[2159]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2159]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )
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
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x596F90 sub_596F90
// ------------------------------------------------------------
int /*userpurge*/ sub_596F90@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2151] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
      sub_596D90(pDwArg1, nArg2);
    pDwArg1[2151] = 0;
  }
  if ( pDwArg3 == pDwArg1 )
  {
    if ( pDwArg1[2151] != 0 )
    {
      sub_596D90(pDwArg1, nArg2);
      pDwArg1[2151] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  return sub_4D9170(pDwArg3);
}



// 攻击 AI：vt+212 播报 FOX_ATK
// ------------------------------------------------------------
// 0x597000 sub_597000
// ------------------------------------------------------------
int /*userpurge*/ sub_597000@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int v8; // edx

  v7 = pDwArg1[1639];
  if ( v7 == 15 )
  {
    if ( ArgList != 15 )
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  else if ( v7 == 14 )
  {
    sub_596D90(pDwArg1, nArg2);
  }
  switch ( ArgList )
  {
    case 8:
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);
      break;
    case 14:
      sub_596650(pDwArg1, nArg4);
      break;
    case 15:
      sub_597890(pDwArg1);
      break;
    default:
      break;
  }
  return sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);
}



// 【vmt200 命中处理器覆写】（虚表 0x6CFF24 +512 槽，狐狸系子类）
// ------------------------------------------------------------
// 0x5970A0 sub_5970A0
// ------------------------------------------------------------
int /*thiscall*/ sub_5970A0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( rand() % 100 < (*(this + 1908) != 0 ? 5 : 10)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
      this,
      48003,
      *(this + 2152),
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
  return sub_4DA3B0(nArg2, nArg3, nArg4);
}



// 撕咬连击 AI：FOX_BITE_LOOP（100L）
// ------------------------------------------------------------
// 0x597120 sub_597120
// ------------------------------------------------------------
int /*usercall*/ sub_597120@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
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

  pObj = pArg1[2151];
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
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) + 15;
        else
          v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - 15;
        v23 = v5;
        v6 = (double)v5;
        v7 = *pArg1;
        v17 = v6;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 124))(pArg1);
        v9 = *pArg1;
        v23 = v8;
        v18 = (float)v8;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 128))(pArg1);
        v11 = pArg1[2151];
        v23 = v10 + 45;
        v19 = (float)(v10 + 45);
        sub_4E5F70(nArg2, (int)pArg1, v11, &v17, 1, 1);
      }
      v12 = pArg1[2154];
      v13 = pArg1[2153] + 1;
      pArg1[2153] = v13;
      if ( v13 >= v12
        || (v14 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 684))(pArg1[2151]), sub_41A5E0(v14) <= 0) )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 15, 0, 0, 0);
      }
      else
      {
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);
        sub_4926A0(v15);
      }
      if ( pArg1[2153] == 1 )
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "FOX_BITE_LOOP", 33, 0, 0);
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[2151] + 604))(pArg1[2151], 0);
    return (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[2151] + 612))(pArg1[2151], 1, 1);
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 840))(pArg1[2151]);
    if ( result != 5 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[2151] + 308))(pArg1[2151]);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1[2151] + 560))(
                 pArg1[2151],
                 9,
                 0,
                 0,
                 0);
    }
  }
  return result;
}



// AI 相位辅助（108L）
// ------------------------------------------------------------
// 0x597300 sub_597300
// ------------------------------------------------------------
void /*usercall*/ sub_597300(int pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // edi
  double v4; // st7
  int v5; // ebx
  int *v6; // ecx

  sub_4E1780((uint32_t *)pArg1);
  if ( *(uint32_t *)(pArg1 + 6556) != 8 )
  {
    if ( *(uint32_t *)(pArg1 + 6556) == 14 )
    {
      sub_597120((uint32_t *)pArg1, nArg2);
    }
    else if ( *(uint32_t *)(pArg1 + 6556) == 15 )
    {
      sub_5943F0((uint32_t *)pArg1);
    }
    return;
  }
  v3 = pArg1 + 7028;
  if ( sub_41A5E0(pArg1 + 7028) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 && *(uint8_t *)(pArg1 + 8600) == 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);
    *(uint8_t *)(pArg1 + 8600) = 1;
  }
  if ( sub_41A5E0(pArg1 + 7028) == 1
    || sub_41A5E0(pArg1 + 7028) == 2
    || sub_41A5E0(pArg1 + 7028) == 3
    || sub_41A5E0(pArg1 + 7028) == 4 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 )
    {
LABEL_30:
      if ( *(uint8_t *)(pArg1 + 8601) != 0 && *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )
      {
        v5 = 0;
        if ( sub_41A5E0(pArg1 + 7028) == 1 || sub_41A5E0(pArg1 + 7028) == 2 )
        {
          v5 = 6;
        }
        else if ( sub_41A5E0(pArg1 + 7028) == 3 || sub_41A5E0(pArg1 + 7028) == 4 )
        {
          v5 = 2;
        }
        sub_4AECE0(*(void **)(pArg1 + 120), v5);
        *(uint8_t *)(pArg1 + 8602) = 1;
      }
      goto LABEL_40;
    }
    if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )
    {
      if ( *(uint8_t *)(pArg1 + 8601) != 0 )
      {
LABEL_27:
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 896))(pArg1, 4, 4);
        }
        goto LABEL_30;
      }
      if ( sub_41A5E0(pArg1 + 7028) == 1 )
      {
        sub_596030((uint32_t *)pArg1, nArg2, v3, 1000);
        sub_4A0550(120);
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 2 || sub_41A5E0(pArg1 + 7028) == 4 )
      {
        v4 = (double)sub_5985E0(400.0);
        if ( v4 < 300.0 )
          v4 = 300.0;
        sub_4A05C0((uint64_t)(v4 * 0.5));
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 3 )
      {
        sub_596030((uint32_t *)pArg1, nArg2, v3, 1000);
        sub_4A0550(90);
      }
    }
    if ( *(uint8_t *)(pArg1 + 8601) == 0 )
    {
LABEL_40:
      if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) > 0.0 && *(uint8_t *)(pArg1 + 8601) == 0 )
      {
        v6 = *(int **)(pArg1 + 120);
        if ( v6[37] < 1 )
          sub_4AECE0(v6, 1);
        *(uint8_t *)(pArg1 + 8601) = 1;
      }
      return;
    }
    goto LABEL_27;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x597570 sub_597570
// ------------------------------------------------------------
int /*thiscall*/ sub_597570(uint32_t *this, int nArg2)
{
  int result; // eax
  int fld_e1554; // eax
  int fld_e2155; // edx
  int fld_e2151; // edi
  int fld_e21512; // eax
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = nArg2;
  if ( nArg2 == *(this + 2151) )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
    if ( result == 14 && (int)*(this + 2154) > 1 )
    {
      fld_e1554 = sub_491C10(*(uint32_t *)*(this + 1554));
      fld_e2155 = *(this + 2155) + 1;
      *(this + 2155) = fld_e2155;
      if ( fld_e2155 >= 5 * fld_e1554 / 1000 )
      {
        --*(this + 2154);
        *(this + 2155) = 0;
      }
      fld_e2151 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 120))(*(this + 2151));
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 916))(*(this + 2151));
      fld_e21512 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2151) + 120))(*(this + 2151));
      v8 = *this;
      v9 = fld_e2151 - fld_e21512;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v10);
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v11);
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(v8 + 112))(this, v12 - v9);
    }
  }
  return result;
}



// 蓄力技能：vt+212 "HOLD"（104L）
// ------------------------------------------------------------
// 0x597640 sub_597640
// ------------------------------------------------------------
int /*thiscall*/ sub_597640(int *this, int pArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int fld_e2151; // ecx
  int v6; // eax
  int fld_e21512; // ecx
  int v8; // eax
  int fld_e21513; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int fld_e21514; // ecx
  int v14; // eax
  int v15; // ebx
  int fld_e21515; // edi
  int v17; // edx
  int v18; // eax
  int v19; // eax
  uint32_t *fld_e28; // edi
  int v21; // eax
  int fld_e1821; // edi
  uint32_t *v23; // eax
  int nRand; // eax
  float v26; // [esp+70h] [ebp-24h]
  float v27; // [esp+74h] [ebp-20h]
  int v28; // [esp+8Ch] [ebp-8h]
  int fld_e215152; // [esp+90h] [ebp-4h]
  int v30; // [esp+9Ch] [ebp+8h]
  int v31; // [esp+9Ch] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
    || (*(this + 2151) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2151) = 0;
  }
  fld_e2151 = *(this + 2151);
  if ( fld_e2151 != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2151 + 120))(fld_e2151);
    fld_e21512 = *(this + 2151);
    *(this + 2156) = v6;
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512);
    fld_e21513 = *(this + 2151);
    *(this + 2157) = v8;
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21513 + 128))(fld_e21513);
    v11 = *this;
    *(this + 2158) = v10;
    v12 = (*(int (/*thiscall*/ **)(int *))(v11 + 152))(this);
    fld_e21514 = *(this + 2151);
    if ( v12 != 0 )
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) - 30;
    else
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) + 30;
    v15 = *this;
    v30 = v14;
    fld_e21515 = *(this + 2151);
    v17 = *(uint32_t *)fld_e21515;
    fld_e215152 = fld_e21515;
    v18 = (*(int (/*thiscall*/ **)(int))(v17 + 128))(fld_e21515);
    v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21515 + 124))(fld_e21515, v18 + 40);
    (*(void (/*thiscall*/ **)(int *, int, int))(v15 + 112))(this, v30, v19 + 1);
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2151) + 848))(*(this + 2151), 1);
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  fld_e215152 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0);
  v21 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v31 = v21;
  v23 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
  v27 = (float)v31;
  v26 = (float)fld_e215152;
  *(this + 2154) = (uint64_t)sub_4049C0(v26, v27, *v23 - *(this + 1820), fld_e1821);
  *(this + 2153) = 0;
  *(this + 2155) = 0;
  v28 = 0;
  fld_e215152 = 1;
  nRand = rand() % 2;
  sub_4DB200(24, *(&v28 + nRand));
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
}



// AI 字段访问（this+8602）
// ------------------------------------------------------------
// 0x597890 sub_597890
// ------------------------------------------------------------
int /*thiscall*/ sub_597890(uint32_t *this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int fld_e2151; // eax
  int fld_e21512; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int result; // eax

  v2 = *this;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v3);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v2 + 136))(this, v4) == 0
    || (v5 = *this,
        v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this),
        (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v5 + 132))(this, v6) == 0) )
  {
    fld_e2151 = *(this + 2151);
    if ( fld_e2151 != 0 )
    {
      fld_e21512 = *(this + 2151);
      v9 = *this;
      v10 = (*(int (**)(void))(*(uint32_t *)fld_e2151 + 128))();
      v11 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512, v10 + 40);
      v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21512 + 120))(fld_e21512, v11);
      (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 112))(this, v12);
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 200, 200, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
  v13 = *this;
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 152))(this, 4);
  v15 = sub_432E50(v14);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v13 + 896))(this, v15);
  sub_495890(2, 0);
  result = sub_4A0550(10);
  *((uint8_t *)this + 8602) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5979B0 sub_5979B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5979B0(uint32_t *this, int nArg2, int nArg3)
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
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) * 0.76923078;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 672))(this, 0, 1050253722);
      sub_4E99C0(v7);
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    }
  }
  else
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v8 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;
    sub_41A590(v5, v6, v8);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    result = nArg2;
    if ( nArg2 == 0 )
    {
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) * 0.76923078;
      return result;
    }
  }
  if ( --result == 0 )
    *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 0.76923078;
  return result;
}



// AI 相位辅助（101L）
// ------------------------------------------------------------
// 0x597AB0 sub_597AB0
// ------------------------------------------------------------
int /*thiscall*/ sub_597AB0(uint32_t *this, int nArg2, int nArg3)
{
  char *pThis_1D73; // ecx
  int result; // eax
  int fld_e1905; // eax
  unsigned int v7; // edi
  int v8; // edx
  float v9; // [esp+0h] [ebp-8h]
  int v10; // [esp+14h] [ebp+Ch]

  *((uint8_t *)this + 7558) = 0;
  *((uint8_t *)this + 7557) = 0;
  *((uint8_t *)this + 7556) = 0;
  *((uint8_t *)this + 7534) = 0;
  *((uint8_t *)this + 7533) = 0;
  *((uint8_t *)this + 7532) = 0;
  *((uint8_t *)this + 7531) = 0;
  *(uint32_t *)((char *)this + 7535) = 0;
  pThis_1D73 = (char *)this + 7539;
  *(uint32_t *)pThis_1D73 = 0;
  *((uint32_t *)pThis_1D73 + 1) = 0;
  *((uint32_t *)pThis_1D73 + 2) = 0;
  *((uint32_t *)pThis_1D73 + 3) = 0;
  pThis_1D73[16] = 0;
  *(this + 1893) = 0;
  *(this + 1892) = 0;
  *(this + 1891) = 0;
  *(this + 1897) = 0;
  *(this + 1896) = 0;
  *(this + 1895) = 0;
  *(this + 1894) = 0;
  *(this + 1899) = 0;
  if ( nArg3 != 0 )
  {
    result = nArg3 - 2;
    if ( nArg3 == 2 )
    {
      if ( nArg2 != 0 )
      {
        result = nArg2 - 1;
        if ( nArg2 == 1 )
        {
          *(this + 1892) = 1;
          *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 1.3;
        }
        else
        {
          result = nArg2 - 2;
          if ( nArg2 == 2 )
            *(this + 1892) = 1;
        }
      }
      else
      {
        fld_e1905 = *(this + 1905) + 128;
        *(this + 1892) = 1;
        *(this + 1899) = 50;
        *(float *)(fld_e1905 + 4) = *(float *)(fld_e1905 + 4) * 1.3;
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*this + 672))(this, 0, 1050253722);
        sub_4AED60(v9);
        return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
      }
    }
  }
  else
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;
    sub_41A590(v7, v8, v10);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
    result = nArg2;
    if ( nArg2 != 0 )
    {
      result = nArg2 - 1;
      if ( nArg2 == 1 )
      {
        *(this + 1891) = 1;
        *(float *)(*(this + 1905) + 68) = *(float *)(*(this + 1905) + 68) * 1.3;
      }
      else
      {
        result = nArg2 - 2;
        if ( nArg2 == 2 )
          *(this + 1891) = 1;
      }
    }
    else
    {
      *(this + 1892) = 1;
      *(this + 1899) = 50;
      *(float *)(*(this + 1905) + 132) = *(float *)(*(this + 1905) + 132) * 1.3;
    }
  }
  return result;
}



// 登场曲：sub_406D60 写 "B_PENRIL_01"（Penril 曲目槽）+ sub_699000 时钟门
// ------------------------------------------------------------
// 0x597CA0 sub_597CA0
// ------------------------------------------------------------
int /*thiscall*/ sub_597CA0(int *this)
{
  int result; // eax

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      if ( *(this + 1943) == 3 )
        result = sub_406D60("B_PENRIL_01");
      break;
    case 4:
      result = *(this + 1813);
      if ( result == 0 )
        goto LABEL_5;
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    case 21:
      result = sub_699000((int)(this + 9)) - *(this + 1926);  // 【clock_now(clk)】
      if ( result > 1000 )
LABEL_5:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    default:
      return result;
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x597D70 sub_597D70
// ------------------------------------------------------------
int /*thiscall*/ sub_597D70(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8
    && (uint8_t)nArg4 == 0
    && (sub_41A5E0((unsigned int)(this + 1757)) == 3 || sub_41A5E0((unsigned int)(this + 1757)) == 4)
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



// 参数打包 AI（89L）
// ------------------------------------------------------------
// 0x597E80 sub_597E80
// ------------------------------------------------------------
void /*usercall*/ sub_597E80(int *pDwArg1@<ecx>, int nArg2@<ebx>)
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

  pObj3 = pDwArg1[2151];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(
           pDwArg1[2151],
           pDwArg1[2156],
           pDwArg1[2157],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);
    }
    else
    {
      pObj = pDwArg1[2151];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2156, pDwArg1 + 2157, v7);
      pObj2 = pDwArg1[2151];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2158]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )
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
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x598080 sub_598080
// ------------------------------------------------------------
int /*userpurge*/ sub_598080@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2151] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
      sub_597E80(pDwArg1, nArg2);
    pDwArg1[2151] = 0;
  }
  if ( pDwArg3 == pDwArg1 )
  {
    if ( pDwArg1[2151] != 0 )
    {
      sub_597E80(pDwArg1, nArg2);
      pDwArg1[2151] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  return sub_4D9170(pDwArg3);
}



// 攻击 AI：vt+212 播报 FOX_ATK（58L）
// ------------------------------------------------------------
// 0x5980F0 sub_5980F0
// ------------------------------------------------------------
int /*userpurge*/ sub_5980F0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int v8; // edx
  int result; // eax
  int v10; // edi
  int v11; // eax

  v7 = pDwArg1[1639];
  if ( v7 == 15 )
  {
    if ( ArgList != 15 )
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  else if ( v7 == 14 )
  {
    sub_597E80(pDwArg1, nArg2);
  }
  switch ( ArgList )
  {
    case 8:
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);
      break;
    case 14:
      sub_597640(pDwArg1, nArg4);
      break;
    case 15:
      sub_597890(pDwArg1);
      break;
    default:
      break;
  }
  result = sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
    if ( result == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 700, 700, 0, -2000, 1);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*pDwArg1 + 888))(pDwArg1, 2, 2, 1000, 1000);
      v10 = *pDwArg1;
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
      return (*(int (/*thiscall*/ **)(int *, int))(v10 + 896))(pDwArg1, v11);
    }
  }
  return result;
}



// 狐狸资源装载：R_FOX_TALK/DMG + FOX_DIE 语音 + Monster/Lugaru/Teeth.equ（46L）
// ------------------------------------------------------------
// 0x598200 sub_598200
// ------------------------------------------------------------
int /*thiscall*/ sub_598200(uint32_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  int pObj; // eax
  int fld_e1821; // edi
  uint32_t *v6; // eax
  int result; // eax
  float v8; // [esp+14h] [ebp-30h]
  float v9; // [esp+18h] [ebp-2Ch]
  void *Block; // [esp+30h] [ebp-14h]
  int v11; // [esp+34h] [ebp-10h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Lugaru/Teeth.equ", 0);
  else
    v3 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v9 = (float)v11;
  v8 = (float)(int)Block;
  *(this + 2152) = (uint64_t)sub_4049C0(v8, v9, *v6 - *(this + 1820), fld_e1821);
  result = *(this + 162) | 2;
  *(this + 162) = result;
  return result;
}



// 子类扩展字段复位（this+8600..8624）
// ------------------------------------------------------------
// 0x598350 sub_598350
// ------------------------------------------------------------
int /*thiscall*/ sub_598350(int this)
{
  uint32_t *pThis_21B0; // ecx

  *(uint8_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8601) = 0;
  *(uint8_t *)(this + 8602) = 0;
  *(uint32_t *)(this + 8604) = 0;
  pThis_21B0 = (uint32_t *)(this + 8624);
  *pThis_21B0 = 0;
  pThis_21B0[1] = 0;
  pThis_21B0[2] = 0;
  return 0;
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x598380 sub_598380
// ------------------------------------------------------------
int /*thiscall*/ sub_598380(int *this)
{
  int result; // eax

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(int *))(*this + 1284))(this);
      break;
    case 4:
      result = *(this + 1813);
      if ( result == 0 )
        goto LABEL_4;
      break;
    case 13:
    case 14:
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 4);
      break;
    case 21:
      result = sub_699000((int)(this + 9)) - *(this + 1926);  // 【clock_now(clk)】
      if ( result > 1000 )
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      break;
    default:
      return result;
  }
  return result;
}



// AI 相位辅助（81L）
// ------------------------------------------------------------
// 0x598440 sub_598440
// ------------------------------------------------------------
int /*userpurge*/ sub_598440@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, char pszArg5)
{
  int result; // eax
  bool v8; // zf
  int v9; // edi
  int v10; // edi
  long double v11; // st7
  double v13; // st6
  uint8_t v14; // c0
  uint8_t v15; // c2
  double v16; // st6
  int v17; // ebx
  float v19; // [esp+4h] [ebp-8h]
  float v20; // [esp+8h] [ebp-4h]
  float v21; // [esp+14h] [ebp+8h]
  float v22; // [esp+18h] [ebp+Ch]
  float v23; // [esp+18h] [ebp+Ch]

  result = pArg1[1813];
  if ( result != 0 )
  {
    v8 = pszArg5 == 0;
    v22 = 1.6;
    if ( v8 )
      v22 = 1.2;
    v9 = (*(int (/*thiscall*/ **)(uint32_t, int, int))(*(uint32_t *)pArg1[1813] + 120))(pArg1[1813], nArg3, nArg2);
    v20 = 1.6;
    v23 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - v9) * v22;
    if ( pszArg5 == 0 )
      v20 = 1.2;
    v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);
    v11 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1) - v10) * v20;
    v13 = v23;
    if ( (v14 | v15) != 0 )
    {
      if ( v13 <= -200.0 )
        v23 = -200.0;
    }
    else if ( v13 >= 200.0 )
    {
      v23 = 200.0;
    }
    if ( v11 >= 0.0 )
    {
      if ( v11 >= 100.0 )
        v11 = 100.0;
    }
    else if ( v11 <= -100.0 )
    {
      v11 = -100.0;
    }
    v16 = (double)nArg4;
    v21 = fabs(v23) / v16 * 1000.0;
    v19 = fabs(v11) / v16 * 1000.0;
    v17 = 3;
    if ( v11 >= 0.0 )
      v17 = 2;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
      pArg1,
      0,
      (uint64_t)v21,
      (uint64_t)v21,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
      pArg1,
      1,
      (uint64_t)v19,
      (uint64_t)v19,
      0,
      0,
      0);
    return (*(int (/*thiscall*/ **)(uint32_t *, bool, int))(*pArg1 + 896))(pArg1, v23 < 0.0, v17);
  }
  return result;
}



// AI 相位辅助（79L）
// ------------------------------------------------------------
// 0x5985E0 sub_5985E0
// ------------------------------------------------------------
int /*userpurge*/ sub_5985E0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, float fArg4)
{
  int pObj; // eax
  int v6; // edi
  int v7; // edi
  long double v8; // st7
  double v10; // st6
  uint8_t v11; // c0
  uint8_t v12; // c2
  double v13; // st6
  int v14; // ebx
  int64_t v15; // rax
  float v17; // [esp+4h] [ebp-Ch]
  float v18; // [esp+8h] [ebp-8h]
  float v19; // [esp+Ch] [ebp-4h]
  float v20; // [esp+18h] [ebp+8h]

  pObj = pArg1[1813];
  if ( pObj != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 120))(pObj, nArg3, nArg2);
    v19 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1) - v6) * 1.2;
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);
    v8 = (double)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1) - v7) * 1.2;
    v10 = v19;
    if ( (v11 | v12) != 0 )
    {
      if ( v10 <= -200.0 )
        v19 = -200.0;
    }
    else if ( v10 >= 200.0 )
    {
      v19 = 200.0;
    }
    if ( v8 >= 0.0 )
    {
      if ( v8 >= 100.0 )
        v8 = 100.0;
    }
    else if ( v8 <= -100.0 )
    {
      v8 = -100.0;
    }
    v20 = sqrt(v8 * v8 + v19 * v19) / fArg4 * 1000.0;
    v13 = 1.0 / v20;
    v18 = fabs(v19) * v13 * 1000.0;
    v17 = fabs(v8) * v13 * 1000.0;
    v14 = 3;
    if ( v8 >= 0.0 )
      v14 = 2;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
      pArg1,
      0,
      (uint64_t)v18,
      (uint64_t)v18,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 876))(
      pArg1,
      1,
      (uint64_t)v17,
      (uint64_t)v17,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(uint32_t *, bool, int))(*pArg1 + 896))(pArg1, v19 < 0.0, v14);
    return (uint64_t)v20;
  }
  else
  {
    LODWORD(v15) = 0;
  }
  return v15;
}



// ============================================================
// 【分区 7】狐狸系·牙齿装备型 + 投石哥布林（0x598790-0x599AE0）
// 证据：Teeth.equ 装载（0x598200/0x5993F0）、投石哥布林 R_GOBLIN_* 语音 +
//       Monster/Goblin/tcc2-acc2-hcc3-gcc1.equ + Particle/ThrowStone.ptl + THROW_STONE

// AI 字段访问（this+200/+8636）
// ------------------------------------------------------------
// 0x598790 sub_598790
// ------------------------------------------------------------
int /*thiscall*/ sub_598790(uint8_t *this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  int result; // eax
  int dword_79C0B02; // [esp-20h] [ebp-2Ch]
  int nRand2; // [esp-1Ch] [ebp-28h]
  int nRand; // [esp-18h] [ebp-24h]

  result = sub_4D8F90(nArg2, nArg3, nArg4, LODWORD(fArg5));
  if ( (uint8_t)nArg2 != 1 && *(this + 8636) == 1 )
  {
    nRand = rand() % 8 + nArg4 - 4;
    nRand2 = rand() % 8 + nArg3 - 4;
    dword_79C0B02 = dword_79C0B0;
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this);
    return sub_491DE0(dword_79C0B02, nRand2, nRand, fArg5, 2, 1, -16776961, -922746881);
  }
  return result;
}



// AI 字段访问（this+8636）
// ------------------------------------------------------------
// 0x598820 sub_598820
// ------------------------------------------------------------
int /*thiscall*/ sub_598820(uint8_t *this, int nArg2, int nArg3)
{
  int result; // eax

  result = 1;
  if ( *(this + 8636) != 1 )
    return sub_4DC390(nArg2, nArg3);
  return result;
}



// 蓄力技能：vt+212 "HOLD"（144L；this+8636 相位门）
// ------------------------------------------------------------
// 0x598840 sub_598840
// ------------------------------------------------------------
int /*thiscall*/ sub_598840(int *this, int pArg2)
{
  int pObj2; // eax
  int pObj; // edi
  int v5; // edx
  unsigned int v6; // edi
  int v7; // edx
  int v8; // edx
  unsigned int v9; // edi
  int v10; // edx
  int v11; // edx
  unsigned int v12; // edi
  int v13; // edx
  int v14; // edx
  unsigned int v15; // edi
  int v16; // edx
  int fld_e2151; // ecx
  int v18; // eax
  int fld_e21512; // ecx
  int v20; // eax
  int fld_e21513; // ecx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int fld_e21514; // ecx
  int v26; // eax
  int v27; // ebx
  int fld_e21515; // edi
  int v29; // edx
  int v30; // eax
  int v31; // eax
  uint32_t *fld_e28; // edi
  int v33; // eax
  int fld_e1821; // edi
  uint32_t *v35; // eax
  int nRand; // eax
  float v38; // [esp+84h] [ebp-24h]
  float v39; // [esp+88h] [ebp-20h]
  int v40; // [esp+A0h] [ebp-8h]
  int fld_e2170; // [esp+A4h] [ebp-4h]
  int v42; // [esp+B0h] [ebp+8h]
  int v43; // [esp+B0h] [ebp+8h]
  int v44; // [esp+B0h] [ebp+8h]
  int v45; // [esp+B0h] [ebp+8h]
  int v46; // [esp+B0h] [ebp+8h]
  int v47; // [esp+B0h] [ebp+8h]

  pObj2 = sub_45EBE0(**(uint32_t **)(pArg2 + 4), *(uint32_t *)(*(uint32_t *)(pArg2 + 4) + 4));
  pObj = pObj2;
  if ( pObj2 == 0
    || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) == 0
    || (*(this + 2151) = pObj, (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) > 0) )
  {
    *(this + 2151) = 0;
  }
  if ( *((uint8_t *)this + 8636) == 0 )
  {
    v5 = *this;
    fld_e2170 = *(this + 2170);
    v6 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v5 + 672))(this, 0) + 830;
    *(float *)&v42 = COERCE_FLOAT(sub_41A5E0(v6)) + *(float *)&fld_e2170;
    sub_41A590(v6, v7, v42);
    v8 = *this;
    fld_e2170 = *(this + 2170);
    v9 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v8 + 672))(this, 0) + 858;
    *(float *)&v43 = COERCE_FLOAT(sub_41A5E0(v9)) + *(float *)&fld_e2170;
    sub_41A590(v9, v10, v43);
    v11 = *this;
    fld_e2170 = *(this + 2170);
    v12 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v11 + 672))(this, 0) + 102;
    *(float *)&v44 = COERCE_FLOAT(sub_41A5E0(v12)) + *(float *)&fld_e2170;
    sub_41A590(v12, v13, v44);
    v14 = *this;
    fld_e2170 = *(this + 2170);
    v15 = (*(int (/*thiscall*/ **)(int *, uint32_t))(v14 + 672))(this, 0) + 158;
    *(float *)&v45 = COERCE_FLOAT(sub_41A5E0(v15)) + *(float *)&fld_e2170;
    sub_41A590(v15, v16, v45);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 676))(this, 0);
    *((uint8_t *)this + 8636) = 1;
  }
  fld_e2151 = *(this + 2151);
  if ( fld_e2151 != 0 )
  {
    v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2151 + 120))(fld_e2151);
    fld_e21512 = *(this + 2151);
    *(this + 2156) = v18;
    v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21512 + 124))(fld_e21512);
    fld_e21513 = *(this + 2151);
    *(this + 2157) = v20;
    v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21513 + 128))(fld_e21513);
    v23 = *this;
    *(this + 2158) = v22;
    v24 = (*(int (/*thiscall*/ **)(int *))(v23 + 152))(this);
    fld_e21514 = *(this + 2151);
    if ( v24 != 0 )
      v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) - 30;
    else
      v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21514 + 120))(fld_e21514) + 30;
    v27 = *this;
    v46 = v26;
    fld_e21515 = *(this + 2151);
    v29 = *(uint32_t *)fld_e21515;
    fld_e2170 = fld_e21515;
    v30 = (*(int (/*thiscall*/ **)(int))(v29 + 128))(fld_e21515);
    v31 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e21515 + 124))(fld_e21515, v30 + 40);
    (*(void (/*thiscall*/ **)(int *, int, int))(v27 + 112))(this, v46, v31 + 1);
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 2151) + 848))(*(this + 2151), 1);
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 1554));
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 0, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 876))(this, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, int))(*this + 888))(this, 0, 2, 1000, 1000);
  (*(void (/*thiscall*/ **)(int *, int, int))(*this + 896))(this, 4, 4);
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 344))(this, *(this + 139));
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0
    && *((float *)fld_e28 + 6) != 0.0 )
  {
    fld_e28[6] = 0;
    *((uint8_t *)fld_e28 + 196) = 1;
  }
  sub_495890(0, 0);
  *(float *)&fld_e2170 = COERCE_FLOAT((*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0));
  v33 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v47 = v33;
  v35 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
  v39 = (float)v47;
  v38 = (float)fld_e2170;
  *(this + 2154) = (uint64_t)sub_4049C0(v38, v39, *v35 - *(this + 1820), fld_e1821);
  *(this + 2153) = 0;
  *(this + 2155) = 0;
  v40 = 0;
  fld_e2170 = 1;
  nRand = rand() % 2;
  sub_4DB200(24, *(&v40 + nRand));
  return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HOLD", -1, 0, 0);
}


// 大型 AI（161L；sub_699000 时钟门驱动）
// ------------------------------------------------------------
// 0x598BA0 sub_598BA0
// ------------------------------------------------------------
void /*usercall*/ sub_598BA0(int pArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // edi
  double v4; // st7
  int v5; // ebx
  int *v6; // ecx
  int v7; // edi
  int pObj; // edi
  int v9; // edx
  uint32_t *v10; // ebx
  int nRand; // et2
  uint64_t v12; // rax
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  void *v16; // eax
  int v17; // [esp-Ch] [ebp-48h]
  int v18; // [esp-8h] [ebp-44h]
  void *v19[4]; // [esp+Ch] [ebp-30h] BYREF
  void *pBuf[4]; // [esp+1Ch] [ebp-20h] BYREF
  int v21; // [esp+2Ch] [ebp-10h]
  int v22; // [esp+38h] [ebp-4h]

  sub_4E1780((uint32_t *)pArg1);
  if ( *(uint32_t *)(pArg1 + 6556) != 8 )
  {
    if ( *(uint32_t *)(pArg1 + 6556) == 14 )
    {
      sub_597120((uint32_t *)pArg1, nArg2);
    }
    else if ( *(uint32_t *)(pArg1 + 6556) == 15 )
    {
      sub_5943F0((uint32_t *)pArg1);
    }
    goto LABEL_45;
  }
  v3 = pArg1 + 7028;
  if ( sub_41A5E0(pArg1 + 7028) == 0 && *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 3 && *(uint8_t *)(pArg1 + 8600) == 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 352))(pArg1);
    *(uint8_t *)(pArg1 + 8600) = 1;
  }
  if ( sub_41A5E0(pArg1 + 7028) == 1
    || sub_41A5E0(pArg1 + 7028) == 2
    || sub_41A5E0(pArg1 + 7028) == 3
    || sub_41A5E0(pArg1 + 7028) == 4 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 0 )
    {
LABEL_30:
      if ( *(uint8_t *)(pArg1 + 8601) != 0 && *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )
      {
        v5 = 0;
        if ( sub_41A5E0(pArg1 + 7028) == 1 || sub_41A5E0(pArg1 + 7028) == 2 )
        {
          v5 = 6;
        }
        else if ( sub_41A5E0(pArg1 + 7028) == 3 || sub_41A5E0(pArg1 + 7028) == 4 )
        {
          v5 = 2;
        }
        sub_4AECE0(*(void **)(pArg1 + 120), v5);
        *(uint8_t *)(pArg1 + 8602) = 1;
      }
      goto LABEL_40;
    }
    if ( *(int *)(*(uint32_t *)(pArg1 + 120) + 148) >= 1 )
    {
      if ( *(uint8_t *)(pArg1 + 8601) != 0 )
      {
LABEL_27:
        if ( *(uint32_t *)(*(uint32_t *)(pArg1 + 112) + 192) == 4 && *(uint8_t *)(pArg1 + 8602) == 0 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(
            pArg1,
            0,
            0,
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 896))(pArg1, 4, 4);
        }
        goto LABEL_30;
      }
      if ( sub_41A5E0(pArg1 + 7028) == 1 )
      {
        sub_598440((uint32_t *)pArg1, nArg2, v3, 1000, 0);
        sub_4A0550(120);
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 2 || sub_41A5E0(pArg1 + 7028) == 4 )
      {
        v21 = sub_5985E0((uint32_t *)pArg1, nArg2, v3, 400.0);
        v4 = (double)v21;
        if ( v4 < 300.0 )
          v4 = 300.0;
        sub_4A05C0((uint64_t)(v4 * 0.5));
      }
      else if ( sub_41A5E0(pArg1 + 7028) == 3 )
      {
        sub_598440((uint32_t *)pArg1, nArg2, v3, 1000, 1);
        sub_4A0550(90);
      }
    }
    if ( *(uint8_t *)(pArg1 + 8601) == 0 )
    {
LABEL_40:
      if ( *(float *)(*(uint32_t *)(pArg1 + 112) + 24) > 0.0 && *(uint8_t *)(pArg1 + 8601) == 0 )
      {
        v6 = *(int **)(pArg1 + 120);
        if ( v6[37] < 1 )
          sub_4AECE0(v6, 1);
        *(uint8_t *)(pArg1 + 8601) = 1;
      }
      goto LABEL_45;
    }
    goto LABEL_27;
  }
LABEL_45:
  if ( *(uint8_t *)(pArg1 + 8636) == 1 && *(uint8_t *)(pArg1 + 8637) == 1 )
  {
    v7 = *(uint32_t *)(pArg1 + 8676);
    if ( sub_699000(pArg1 + 8652) >= v7 && rand() % 100 < *(uint32_t *)(pArg1 + 8648) )  // 【clock_now(clk)】
    {
      pObj = dword_8F82CC;
      memset(&pBuf[1], 0, 12);
      v9 = *(uint32_t *)dword_8F82CC;
      v22 = 0;
      v10 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(v9 + 36))(dword_8F82CC);
      nRand = rand() % (*(uint32_t *)(pArg1 + 8644) + 1);
      v10[3] = 30;
      v10[4] = 50;
      v10[1] = nRand;
      v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 192))(pArg1);
      v12 = (uint64_t)((double)v21 * 0.69999999);
      v10[5] = v12;
      (*(void (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, HIDWORD(v12));
      v13 = *(uint32_t *)pObj;
      v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 128))(pArg1);
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 124))(pArg1);
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1);
      (*(void (/*thiscall*/ **)(int, int))(v13 + 40))(pObj, v14);
      v15 = (*(int (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj + 92))(pObj, v19);
      LOBYTE(v22) = 1;
      sub_4E77D0((int)pBuf, v15);
      LOBYTE(v22) = 0;
      sub_5E5260(v19);
      v16 = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, void **))(*(uint32_t *)pArg1 + 80))(pArg1, 2, 0, pBuf);
      sub_4600B0(v16, v17, v18, 0);
      *(uint8_t *)(pArg1 + 8665) = 0;
      *(uint8_t *)(pArg1 + 8666) = 0;
      sub_698F90(pArg1 + 8652, *(uint32_t *)(pArg1 + 8640), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      sub_5E5260(pBuf);
    }
  }
}


// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x598F60 sub_598F60
// ------------------------------------------------------------
int /*thiscall*/ sub_598F60(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int pObj; // edi
  int v6; // edx
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v9; // [esp+20h] [ebp-4h]

  pObj = nArg2;
  if ( *(this + 1639) == 8
    && (uint8_t)nArg4 == 0
    && (sub_41A5E0((unsigned int)(this + 1757)) == 3 || sub_41A5E0((unsigned int)(this + 1757)) == 4)
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



// 参数打包 AI（89L）
// ------------------------------------------------------------
// 0x599070 sub_599070
// ------------------------------------------------------------
void /*usercall*/ sub_599070(int *pDwArg1@<ecx>, int nArg2@<ebx>)
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

  pObj3 = pDwArg1[2151];
  if ( pObj3 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj3 + 604))(pObj3, 1, nArg2);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 612))(pDwArg1[2151], 0, 0);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 136))(
           pDwArg1[2151],
           pDwArg1[2156],
           pDwArg1[2157],
           0) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pDwArg1[2151] + 112))(pDwArg1[2151], pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);
    }
    else
    {
      pObj = pDwArg1[2151];
      v5 = *(uint32_t *)pObj;
      pObj4 = pObj;
      pObj4 = *pDwArg1;
      v6 = (*(int (/*thiscall*/ **)(int, int, int, int))(v5 + 124))(pObj, 300, 1, 1);
      v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v6);
      v8 = (*(int (/*thiscall*/ **)(int *, int *, int *, int))(pObj4 + 140))(pDwArg1, pDwArg1 + 2156, pDwArg1 + 2157, v7);
      pObj2 = pDwArg1[2151];
      if ( v8 != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, pDwArg1[2156], pDwArg1[2157], pDwArg1[2158]);
      }
      else
      {
        v10 = *(uint32_t *)pObj2;
        v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 124))(pDwArg1, pDwArg1[2158]);
        v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 120))(pDwArg1, v11);
        (*(void (/*thiscall*/ **)(int, int))(v10 + 112))(pDwArg1[2151], v12);
      }
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 308))(pDwArg1[2151]) != 0 )
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
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)pDwArg1[2151] + 560))(pDwArg1[2151], 4, v13, 0, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pDwArg1[2151] + 564))(pDwArg1[2151]);
      v18 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v15 = 0;
      v16 = 0;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pDwArg1[2151] + 848))(pDwArg1[2151], 0);
    pDwArg1[2151] = 0;
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x599270 sub_599270
// ------------------------------------------------------------
int /*userpurge*/ sub_599270@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int *pDwArg3)
{
  if ( pDwArg3 == (int *)pDwArg1[2151] )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 840))(pDwArg1) == 14 )
      sub_599070(pDwArg1, nArg2);
    pDwArg1[2151] = 0;
  }
  if ( pDwArg3 == pDwArg1 )
  {
    if ( pDwArg1[2151] != 0 )
    {
      sub_599070(pDwArg1, nArg2);
      pDwArg1[2151] = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  return sub_4D9170(pDwArg3);
}



// 攻击 AI：vt+212 播报 FOX_ATK
// ------------------------------------------------------------
// 0x5992E0 sub_5992E0
// ------------------------------------------------------------
int /*userpurge*/ sub_5992E0@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int ArgList, int nArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int v8; // edx
  int result; // eax
  int v10; // edi
  int v11; // eax

  v7 = pDwArg1[1639];
  if ( v7 == 15 )
  {
    if ( ArgList != 15 )
      (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 216))(pDwArg1, 33);
  }
  else if ( v7 == 14 )
  {
    sub_599070(pDwArg1, nArg2);
  }
  switch ( ArgList )
  {
    case 8:
      v8 = *pDwArg1;
      *((uint8_t *)pDwArg1 + 8600) = 0;
      *((uint8_t *)pDwArg1 + 8601) = 0;
      *((uint8_t *)pDwArg1 + 8602) = 0;
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(v8 + 212))(pDwArg1, "FOX_ATK", -1, 0, 0);
      break;
    case 14:
      sub_598840(pDwArg1, nArg4);
      break;
    case 15:
      sub_597890(pDwArg1);
      break;
    default:
      break;
  }
  result = sub_4E33D0(ArgList, *(float *)&nArg4, nArg5, nArg6);
  if ( ArgList == 8 )
  {
    result = sub_41A5E0((unsigned int)(pDwArg1 + 1757));
    if ( result == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 700, 700, 0, -2000, 1);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
      (*(void (/*thiscall*/ **)(int *, int, int, int, int))(*pDwArg1 + 888))(pDwArg1, 2, 2, 1000, 1000);
      v10 = *pDwArg1;
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
      return (*(int (/*thiscall*/ **)(int *, int))(v10 + 896))(pDwArg1, v11);
    }
  }
  return result;
}



// 狐狸资源装载 2：R_FOX_* 语音 + Teeth.equ（this+8636/8637/8665/8666 相位字段）
// ------------------------------------------------------------
// 0x5993F0 sub_5993F0
// ------------------------------------------------------------
int /*thiscall*/ sub_5993F0(uint32_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  int pObj; // eax
  int fld_e1821; // edi
  uint32_t *v6; // eax
  uint64_t fld_e1820; // rax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int result; // eax
  float v13; // [esp+14h] [ebp-30h]
  float v14; // [esp+18h] [ebp-2Ch]
  void *Block; // [esp+30h] [ebp-14h]
  int v16; // [esp+34h] [ebp-10h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_FOX_TALK", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("R_FOX_DMG", 9u);  // 【std::string构造赋值】
  sub_4015C0("FOX_DIE", 7u);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Lugaru/Teeth.equ", 0);
  else
    v3 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v14 = (float)v16;
  v13 = (float)(int)Block;
  fld_e1820 = (uint64_t)sub_4049C0(v13, v14, *v6 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1820) = *this;
  *(this + 2152) = fld_e1820;
  *(this + 162) |= 2u;
  *((uint8_t *)this + 8636) = 0;
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(HIDWORD(fld_e1820) + 384))(this, 2);
  v9 = *this;
  *((uint8_t *)this + 8637) = v8 != 0;
  *(this + 2160) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v9 + 384))(this, 3);
  *((uint8_t *)this + 8665) = 0;
  *((uint8_t *)this + 8666) = 0;
  sub_698F90((int)(this + 2163), *(this + 2160), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(this + 2161) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 4);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);
  v11 = *this;
  *(this + 2162) = v10;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v11 + 384))(this, 6);
  *((float *)this + 2170) = (double)result * 0.0099999998;
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x5997B0 sub_5997B0
// ------------------------------------------------------------
int /*thiscall*/ sub_5997B0(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  if ( ArgList == 5 )
  {
    if ( rand() % 100 < 50 )
      sub_64BDF0(this, *(uint32_t *)(this + 7256));
  }
  else if ( ArgList == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 0 )
  {
    *(uint8_t *)(this + 8612) = 0;
  }
  return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x599820 sub_599820
// ------------------------------------------------------------
void /*userpurge*/ sub_599820(uint32_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint8_t v5[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  sub_4D90A0(uArg3);
  if ( *uArg32 == 7 && pArg1[1639] == 0 )
  {
    sub_4D84F0(0, 0);
    if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg2) >= uArg32[3] )
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 148))(pArg1, 1);
    else
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 148))(pArg1, 0);
    Block = nullptr;
    v7 = 0;
    v8 = 0;
    v9 = 0;
    uArg3 = nullptr;
    sub_431230((int)v5, &uArg3);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t))(*pArg1 + 560))(pArg1, 8, v5, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 投石哥布林装载：R_GOBLIN_TALK/DMG/DIE 语音 + Monster/Goblin/{tcc2,acc2,hcc3,gcc1}.equ
//   + Particle/ThrowStone.ptl 石弹粒子 + THROW_STONE 播报（69L）
// ------------------------------------------------------------
// 0x5998E0 sub_5998E0
// ------------------------------------------------------------
int /*thiscall*/ sub_5998E0(uint32_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  int pObj; // eax
  char *pMem2; // eax
  char *v6; // eax
  int pObj4; // eax
  char *pMem3; // eax
  char *v9; // eax
  int pObj3; // eax
  char *pMem4; // eax
  char *v12; // eax
  int pObj2; // eax
  int result; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/tcc2.equ", 0);
  else
    v3 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/acc2.equ", 0);
  else
    v6 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/hcc3.equ", 0);
  else
    v9 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/gcc1.equ", 0);
  else
    v12 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  *(this + 2154) = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/ThrowStone.ptl");
  *(this + 2155) = 30001;
  *(this + 2156) = 0;
  result = sub_4015C0("THROW_STONE", 0xBu);  // 【std::string构造赋值】
  *(this + 1829) = 500;
  return result;
}



// ============================================================
// 【分区 8】哥布林系·投弹与自杀兵（0x599AE0-0x59B000）
// 证据：Particle/AimingBomb.ptl 瞄准炸弹、GOBLIN_SUICIDAL/GOBLIN_SCARED 自杀与恐惧、
//       acc9 族六件外观（0x59ABD0）、BKWALKER_01 登场曲（0x59AF40）

// AI 字段访问
// ------------------------------------------------------------
// 0x599AE0 sub_599AE0
// ------------------------------------------------------------
int /*thiscall*/ sub_599AE0(uint32_t *this)
{
  *(this + 2155) = 0;
  *(this + 2154) = 0;
  return 0;
}



// 插值+时钟门 AI（sub_4049C0/sub_699000）
// ------------------------------------------------------------
// 0x599AF0 sub_599AF0
// ------------------------------------------------------------
int /*thiscall*/ sub_599AF0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  unsigned int fld_e2155; // eax
  uint64_t v8; // rax

  result = sub_4D8F90(nArg2, nArg3, nArg4, nArg5);
  if ( (uint8_t)nArg2 == 0 )
  {
    if ( *(this + 1787) == 7 && *(this + 30) != 0 )
    {
      fld_e2155 = sub_699000((int)(this + 9)) - *(this + 2155);  // 【clock_now(clk)】
      if ( fld_e2155 >= 0x2BC )
        LOBYTE(v8) = -36;
      else
        v8 = (uint64_t)sub_4049C0(100.0, 220.0, fld_e2155, 700);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      sub_491690(1, 2, 1, -16776961, ((uint8_t)v8 << 24) | 0xFFFFFF, 1);
    }
    return sub_4D8F90(0, nArg3, nArg4, nArg5);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x599BA0 sub_599BA0
// ------------------------------------------------------------
int /*thiscall*/ sub_599BA0(uint32_t *this)
{
  if ( *(this + 1787) != 6 || (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 )
    return sub_498F60(this);
  else
    return sub_498F60(this) == 0;
}



// %s哥布林通用受击处理（被 21 张子类虚表 +512 槽共享：0x6D096C..0x6D70E4）
//   —— 哥布林一族共用的伤害落地/反应入口（研究 20 §1.2 行为差异=数据+子类定制）
// ------------------------------------------------------------
// 0x599BD0 sub_599BD0
// ------------------------------------------------------------
int /*thiscall*/ sub_599BD0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // edi

  v5 = sub_4DA3B0(nArg2, nArg3, nArg4);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 && rand() % 100 < 10 )
    sub_64BDF0(this, *(this + 1814));
  return v5;
}



// AI 相位辅助（74L）
// ------------------------------------------------------------
// 0x599C30 sub_599C30
// ------------------------------------------------------------
int /*thiscall*/ sub_599C30(int this, int nArg2, int nArg3)
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
      if ( nArg2 == 1 )
      {
        *(uint32_t *)(this + 7596) = 50;
      }
      else if ( nArg2 != 2 )
      {
        return result;
      }
      *(uint32_t *)(this + 7572) = 2;
      *(uint32_t *)(this + 7568) = 1;
    }
    else
    {
      *(uint32_t *)(this + 7568) = 1;
      *(uint32_t *)(this + 7572) = 0;
    }
  }
  else if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      *(uint32_t *)(this + 7568) = 1;
      *(uint32_t *)(this + 7572) = 2;
    }
    else if ( nArg2 == 2 )
    {
      *(uint8_t *)(this + 7556) = 1;
      *(uint32_t *)(this + 7572) = 2;
    }
  }
  else
  {
    *(uint32_t *)(this + 7596) = -50;
  }
  return result;
}



// 子类扩展字段复位（this+8612..8700）
// ------------------------------------------------------------
// 0x599D50 sub_599D50
// ------------------------------------------------------------
int /*thiscall*/ sub_599D50(int this)
{
  *(uint8_t *)(this + 8680) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint8_t *)(this + 8700) = 0;
  *(uint8_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x599D80 sub_599D80
// ------------------------------------------------------------
int /*thiscall*/ sub_599D80(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 1308))(this);
}



// 瞄准炸弹技能：引用 Particle/AimingBomb.ptl（72L；投弹兵瞄准线粒子）
// ------------------------------------------------------------
// 0x599D90 sub_599D90
// ------------------------------------------------------------
int /*usercall*/ sub_599D90@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)
{
  int result; // eax
  uint64_t v5; // rax
  int v6; // esi
  uint64_t v7; // rax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // [esp+8h] [ebp-6Ch]
  uint32_t v13[26]; // [esp+Ch] [ebp-68h] BYREF

  v13[25] = dword_796E50;
  result = pArg1[1813];
  v12 = result;
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1244))(pArg1, result);
    if ( (uint8_t)result != 0 )
    {
      qmemcpy(
        v13,
        (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int, int))(*pArg1 + 588))(
                        pArg1,
                        "Particle/AimingBomb.ptl",
                        nArg2,
                        nArg3),
        0x62u);
      v5 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v13[7] + 3)) / (double)v13[17] * 1000.0);
      v6 = 2 * v5;
      v7 = (uint64_t)((double (/*fastcall*/ *)(uint32_t *, uint32_t, int, uint32_t))*(uint32_t *)(*pArg1 + 164))(
                               pArg1,
                               HIDWORD(v5),
                               v12,
                               0);
      HIDWORD(v7) = *pArg1;
      v13[18] = v7;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(HIDWORD(v7) + 8))(pArg1, v12, 0);
      *(uint32_t *)((char *)&v13[3] + 3) = 1000 * v8 / v6;
      v9 = 1000 * (*(int (/*fastcall*/ **)(uint32_t *, int, int, uint32_t))(*pArg1 + 8))(pArg1, 1000 * v8 % v6, v12, 0) / v6;
      *(uint32_t *)((char *)&v13[4] + 3) = v9;
      if ( *(uint32_t *)((char *)&v13[3] + 3) > 180 )
        *(uint32_t *)((char *)&v13[3] + 3) = 180;
      if ( v9 > 180 )
        *(uint32_t *)((char *)&v13[4] + 3) = 180;
      v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 8))(pArg1);
      v11 = *pArg1;
      *(uint32_t *)((char *)&v13[7] + 3) = v10 > 200 ? 400 : 200;
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v11 + 580))(
               pArg1,
               30370,
               0,
               v13,
               0,
               20,
               0,
               60,
               1,
               0,
               0,
               0);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x599EC0 sub_599EC0
// ------------------------------------------------------------
int /*stdcall*/ sub_599EC0(int nArg1)
{
  return sub_4D90A0(nArg1);
}



// 时钟门 AI（sub_699000, 68L）
// ------------------------------------------------------------
// 0x599ED0 sub_599ED0
// ------------------------------------------------------------
int /*thiscall*/ sub_599ED0(int *this, uint32_t *pArg2)
{
  int result; // eax
  uint32_t *pThis_874; // eax
  int nRand; // eax
  int v6; // edx
  uint32_t v7[2]; // [esp+8h] [ebp-8h]

  sub_4D90A0(pArg2);
  if ( *pArg2 == 10 )
  {
    v6 = *this;
    *(this + 1813) = pArg2[3];
    (*(void (/*thiscall*/ **)(int *, int))(v6 + 1104))(this, 20);
    sub_4D84F0(0, 0);
    return sub_49C5F0(12, 0, 0, 500);
  }
  else if ( *pArg2 == 11 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
    {
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        30055,
        0,
        0,
        0,
        0,
        0,
        50,
        4,
        0,
        0,
        0);
      return (*(int (/*thiscall*/ **)(int *))(*this + 1256))(this);
    }
  }
  else
  {
    result = *pArg2 - 12;
    if ( *pArg2 == 12 )
    {
      result = *(this + 1943);
      if ( result != 3 && result != 1 && result != 2 )
      {
        (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 7);
        *(this + 2155) = sub_699000((int)(this + 9));
        if ( (unsigned int)*(this + 2169) < 0x10 )
          pThis_874 = this + 2164;
        else
          pThis_874 = (uint32_t *)*(this + 2164);
        (*(void (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_874, -1, 0, 0);
        v7[0] = 2;
        v7[1] = 3;
        nRand = rand() % 2;
        return sub_4DB200(24, v7[nRand]);
      }
    }
  }
  return result;
}



// AI 字段访问（this+8604）
// ------------------------------------------------------------
// 0x59A020 sub_59A020
// ------------------------------------------------------------
char /*thiscall*/ sub_59A020(int this, int nArg2)
{
  uint8_t *fld_1DC4; // eax

  sub_4DBC20(nArg2);
  if ( nArg2 == 6 )
  {
    LOBYTE(fld_1DC4) = *(uint8_t *)(this + 8604);
    if ( (uint8_t)fld_1DC4 != 0 )
      LOBYTE(fld_1DC4) = sub_64BDF0(this, *(uint32_t *)(this + 7256));
  }
  else
  {
    LOBYTE(fld_1DC4) = nArg2 - 7;
    if ( nArg2 == 7 )
    {
      fld_1DC4 = *(uint8_t **)(this + 7620);
      *fld_1DC4 = 1;
      *(uint8_t *)(*(uint32_t *)(this + 7620) + 32) = 0;
    }
  }
  return (char)fld_1DC4;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59A080 sub_59A080
// ------------------------------------------------------------
int /*thiscall*/ sub_59A080(uint32_t *this)
{
  int nRand; // eax
  int result; // eax
  int v4; // et2

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
  *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 1.5;
  *((uint8_t *)this + 8612) = 1;
  nRand = rand();
  v4 = nRand % 100;
  result = nRand / 100;
  if ( v4 < 30 )
  {
    if ( *(this + 2162) < 0x10u )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, this + 2157, -1, 0, 0);
    else
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t))(*this + 212))(
               this,
               *(this + 2157),
               -1,
               0,
               0);
  }
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59A100 sub_59A100
// ------------------------------------------------------------
int /*thiscall*/ sub_59A100(uint32_t *this)
{
  int result; // eax

  if ( *(this + 1813) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1140))(this, -1, -1);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
  }
  result = *(this + 1905);
  *(float *)(result + 4) = *(float *)(result + 4) * 0.66666669;
  *((uint8_t *)this + 8612) = 0;
  return result;
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x59A160 sub_59A160
// ------------------------------------------------------------
int /*thiscall*/ sub_59A160(uint32_t *this)
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
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);
  sub_4EB4B0(COERCE_FLOAT(4));
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
// 0x59A220 sub_59A220
// ------------------------------------------------------------
int /*thiscall*/ sub_59A220(int *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 1172))(this);
  if ( result > 0 )
  {
    if ( result > 5 )
    {
      if ( result > 10 )
      {
        if ( result > 15 )
        {
          if ( result > 20 )
            return result;
          goto LABEL_6;
        }
LABEL_5:
        *(uint8_t *)(*(this + 1905) + 96) = 0;
LABEL_6:
        result = *(this + 1905);
        *(uint8_t *)(result + 128) = 0;
        return result;
      }
    }
    else
    {
      *(uint8_t *)(*(this + 1905) + 32) = 0;
    }
    *(uint8_t *)(*(this + 1905) + 64) = 0;
    goto LABEL_5;
  }
  return result;
}



// 时钟门 AI（this+8612, 77L）
// ------------------------------------------------------------
// 0x59A290 sub_59A290
// ------------------------------------------------------------
int /*thiscall*/ sub_59A290(uint32_t *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  if ( *(this + 1787) == 7 )
    return sub_4E0120();
  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
      goto LABEL_15;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_6;
      if ( rand() % 100 < *(this + 2154) )
        sub_59A080(this);
      goto LABEL_15;
    case 5:
      if ( *(this + 1813) != 0 )
      {
        if ( *((uint8_t *)this + 8612) == 1 && sub_699000((int)(this + 1910)) - *(this + 1926) > 3000 )  // 【clock_now(clk)】
          sub_59A100(this);
      }
      else
      {
LABEL_6:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
      }
      goto LABEL_15;
    case 0xD:
    case 0xE:
    case 0xF:
      result = *(this + 1813);
      if ( result == 0 )
        return result;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 4);
LABEL_15:
      result = *(this + 1813);
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
        if ( result == 0 )
        {
          result = *(this + 1908);
          if ( result == 0 )
          {
            result = *(this + 1909);
            if ( result == 0 )
            {
              nRand = rand();
              v4 = nRand % 100;
              result = nRand / 100;
              if ( v4 < 1 )
              {
                (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 20);
                sub_4D84F0(0, 0);
                result = sub_49C5F0(12, 0, 0, 500);
              }
            }
          }
        }
      }
      break;
    default:
      goto LABEL_15;
  }
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59A3F0 sub_59A3F0
// ------------------------------------------------------------
int /*thiscall*/ sub_59A3F0(int this, int ArgList, float fArg3, int nArg4, int nArg5)
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
      return sub_64BDF0(this, *(uint32_t *)(this + 7256));
  }
  else if ( ArgList == 8 )
  {
    result = sub_41A5E0(this + 7028);
    if ( result == 1 )
    {
      return sub_49C5F0(11, 0, 0, 400);
    }
    else if ( *(uint8_t *)(this + 8612) == 1 )
    {
      return sub_59A100((uint32_t *)this);
    }
  }
  return result;
}



// 硬直字段群（this+204/+208 主状态硬直, 研究 15；86xx 相位）
// ------------------------------------------------------------
// 0x59A490 sub_59A490
// ------------------------------------------------------------
int /*thiscall*/ sub_59A490(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  if ( *(uint32_t *)(this + 8696) == 0 )
  {
    sub_59A220((int *)this);
    *(uint32_t *)(this + 8696) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1172))(this);
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0(this + 7028) == 4 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, **(uint32_t **)(this + 6216));
  if ( ArgList == 8 )
  {
    switch ( **(uint32_t **)(LODWORD(fArg3) + 4) )
    {
      case 1:
      case 2:
        goto LABEL_10;
      case 3:
        *(uint32_t *)(this + 8684) = 2;
        *(uint32_t *)(this + 8688) = 6;
        *(uint32_t *)(this + 8692) = 10;
        goto LABEL_10;
      case 4:
        sub_4926A0(**(uint32_t **)(this + 6216));
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
          this,
          100,
          **(uint32_t **)(this + 6216),
          0,
          0,
          0,
          0);
LABEL_10:
        *(uint8_t *)(this + 8680) = 1;
        break;
      default:
        return sub_59A3F0(this, ArgList, fArg3, nArg4, nArg5);
    }
  }
  return sub_59A3F0(this, ArgList, fArg3, nArg4, nArg5);
}



// 投石主技能：Particle/ThrowStone.ptl + THROW_STONE（230L；RTTI cast→CNFighter 目标解算）
// ------------------------------------------------------------
// 0x59A580 sub_59A580
// ------------------------------------------------------------
char /*thiscall*/ sub_59A580(uint8_t *this)
{
  int v2; // eax
  int v3; // ebx
  unsigned int i; // edi
  int pThis_2BC; // eax
  int v6; // ecx
  int v7; // eax
  int pThis_2BC2; // eax
  int v9; // ecx
  int v10; // ecx
  int pThis_2BC3; // eax
  int v12; // ecx
  int v13; // ecx
  int pThis_1E; // ebx
  uint32_t *v15; // ebx
  int v16; // edi
  uint32_t *pThis_2BC4; // eax
  int v18; // eax
  int pObj; // eax
  uint32_t *pThis_2BC5; // eax
  int v21; // edx
  int pThis_1802; // edi
  uint32_t *pMem; // eax
  uint32_t *pMem2; // eax
  uint32_t *v25; // edi
  int pThis_24C; // eax
  int v27; // edi
  int *j; // ecx
  int pThis_24C2; // eax
  uint32_t *pThis_612; // eax
  int v31; // edx
  int v33; // [esp+10h] [ebp-30h]
  int v34; // [esp+10h] [ebp-30h]
  int pThis_180; // [esp+2Ch] [ebp-14h]
  int v36; // [esp+30h] [ebp-10h]

  if ( *((uint32_t *)this + 2090) != 0 && *(this + 8700) == 0 )
  {
    v2 = *(uint32_t *)this;
    *(this + 8700) = 1;
    (*(void (**)(void))(v2 + 1312))();
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1172))(this) > 5 )
  {
    v3 = 0;
    for ( i = 0; ; ++i )
    {
      pThis_2BC = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
      v6 = *(uint32_t *)(pThis_2BC + 4);
      v7 = v6 != 0 ? (*(uint32_t *)(pThis_2BC + 8) - v6) >> 2 : 0;
      if ( (int)i >= v7 )
        break;
      pThis_2BC2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
      v9 = *(uint32_t *)(pThis_2BC2 + 4);
      if ( v9 != 0 && i < (*(uint32_t *)(pThis_2BC2 + 8) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      if ( *(uint8_t **)(v10 + 4) == this )
      {
        pThis_2BC3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
        v12 = *(uint32_t *)(pThis_2BC3 + 4);
        if ( v12 != 0 && i < (*(uint32_t *)(pThis_2BC3 + 8) - v12) >> 2 )
          v13 = *(uint32_t *)(v12 + 4 * i);
        else
          v13 = 0;
        v3 = __RTDynamicCast(v13, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeStatus `RTTI Type Descriptor', 0);
      }
    }
    *(uint8_t *)(*((uint32_t *)this + 1905) + 32) = v3 == 0;
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 8 )
  {
    pThis_1E = *(uint32_t *)(*((uint32_t *)this + 30) + 148);
    switch ( sub_41A5E0((unsigned int)(this + 7028)) )
    {
      case 1:
        if ( pThis_1E >= 2
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
          && *(this + 8680) != 0 )
        {
          v15 = nullptr;
          v16 = 0;
          pThis_2BC4 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
          if ( sub_41C5A0(pThis_2BC4) > 0 )
          {
            do
            {
              (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
              if ( *(uint8_t **)(sub_517740(v16) + 4) == this )
              {
                (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
                v18 = sub_517740(v16);
                pObj = __RTDynamicCast(
                        v18,
                        0,
                        &IRDAppendage `RTTI Type Descriptor',
                        &CNChangeStatus `RTTI Type Descriptor',
                        0);
                if ( pObj != 0 )
                  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);
              }
              ++v16;
              pThis_2BC5 = (uint32_t *)(*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 700))(this);
            }
            while ( v16 < sub_41C5A0(pThis_2BC5) );
          }
          v21 = *(uint32_t *)this;
          *(this + 8680) = 0;
          v36 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(v21 + 384))(this, 0);
          pThis_180 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 1);
          pThis_1802 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 2);
          pMem = operator new(0x7Cu);
          if ( pMem != nullptr )
          {
            *(float *)&v33 = (float)v36;
            v15 = sub_4B3DF0(pMem, 8, 0, v33, pThis_1802, 1);
          }
          pMem2 = operator new(0x7Cu);
          if ( pMem2 != nullptr )
          {
            *(float *)&v34 = (float)pThis_180;
            v25 = sub_4B3DF0(pMem2, 7, 0, v34, pThis_1802, 1);
          }
          else
          {
            v25 = nullptr;
          }
          (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *, uint8_t *, int, uint32_t, int, int))(*v15 + 56))(
            v15,
            this,
            this,
            1,
            0,
            34,
            -1);
          (*(void (/*thiscall*/ **)(uint32_t *, uint8_t *, uint8_t *, int, uint32_t, int, int))(*v25 + 56))(
            v25,
            this,
            this,
            1,
            0,
            35,
            -1);
        }
        break;
      case 2:
        if ( pThis_1E >= 2
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
          && *(this + 8680) != 0 )
        {
          pThis_24C = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)this + 588))(this, "Particle/ThrowStone.ptl");
          (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
            this,
            30372,
            0,
            pThis_24C,
            0,
            20,
            0,
            60,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "THROW_STONE",
            -1,
            0,
            0);
          *(this + 8680) = 0;
        }
        break;
      case 3:
        if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0 )
        {
          v27 = 0;
          for ( j = (int *)(this + 8684); pThis_1E < *j || *j <= 0; ++j )
          {
            if ( ++v27 >= 3 )
              return sub_4E1780(this);
          }
          pThis_24C2 = (*(int (/*thiscall*/ **)(uint8_t *, const char *))(*(uint32_t *)this + 588))(this, "Particle/ThrowStone.ptl");
          (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
            this,
            30372,
            0,
            pThis_24C2,
            0,
            20,
            0,
            60,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "THROW_STONE",
            -1,
            0,
            0);
          *((uint32_t *)this + v27 + 2171) = -1;
        }
        break;
      case 4:
        if ( pThis_1E >= 2
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
          && *(this + 8680) != 0 )
        {
          sub_599D90(this);
          pThis_612 = *((uint32_t **)this + 1554);
          v31 = *(uint32_t *)this;
          *(this + 8680) = 0;
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(v31 + 208))(this, *pThis_612);
        }
        break;
      default:
        return sub_4E1780(this);
    }
  }
  return sub_4E1780(this);
}


// 自杀哥布林装载：R_GOBLIN_* 语音 + GOBLIN_SUICIDAL/GOBLIN_SCARED 播报 +
//   Monster/Goblin/{gcc1,Weapon01}.equ（92L）
// ------------------------------------------------------------
// 0x59A990 sub_59A990
// ------------------------------------------------------------
uint16_t */*thiscall*/ sub_59A990(uint32_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  int pObj; // eax
  char *pMem2; // eax
  char *v6; // eax
  int pObj2; // eax
  int v8; // eax
  uint32_t *v9; // eax
  int fld_e1820; // ecx
  int v11; // edx
  uint32_t *v12; // eax
  uint64_t fld_e1821; // rax
  uint16_t *result; // eax
  int i; // ecx
  float v16; // [esp+20h] [ebp-28h]
  float v17; // [esp+24h] [ebp-24h]
  void *Block; // [esp+34h] [ebp-14h]
  int v19; // [esp+38h] [ebp-10h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("GOBLIN_SUICIDAL", 0xFu);  // 【std::string构造赋值】
  sub_4015C0("GOBLIN_SCARED", 0xDu);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/gcc1.equ", 0);
  else
    v3 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/Weapon01.equ", 0);
  else
    v6 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  *(this + 1832) = 500;
  *(this + 1833) = 500;
  v8 = *this;
  *(this + 1830) = 100;
  *(this + 1839) = -30;
  *(this + 1831) = 350;
  *((uint8_t *)this + 8612) = 0;
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v8 + 384))(this, 0);
  v19 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v9 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  fld_e1820 = *(this + 1820);
  if ( *v9 - fld_e1820 >= 1 )
  {
    v12 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
    fld_e1820 = *(this + 1820);
    v11 = *v12 - fld_e1820;
  }
  else
  {
    v11 = 1;
  }
  v17 = (float)v19;
  v16 = (float)(int)Block;
  fld_e1821 = (uint64_t)sub_4049C0(v16, v17, v11, *(this + 1821) - fld_e1820);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(fld_e1821) = *this;
  *(this + 2154) = fld_e1821;
  result = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t *))(HIDWORD(fld_e1821) + 340))(this);
  if ( *(uint32_t *)result == 1 )
  {
    result = (uint16_t *)this + 4185;
    for ( i = 26; i != 0; --i )
    {
      *result = 50;
      result += 2;
    }
  }
  return result;
}



// 外观变体装载：Monster/Goblin/{acc9,acc9-2,acc9-3,bcc9,hcc9,weapon9}.equ 六件
// ------------------------------------------------------------
// 0x59ABD0 sub_59ABD0
// ------------------------------------------------------------
int /*thiscall*/ sub_59ABD0(int *this)
{
  int i; // edi
  void *pMem; // eax
  char *v4; // eax
  int v5; // edx
  int result; // eax
  void *v7[7]; // [esp+8h] [ebp-28h]
  int v8; // [esp+2Ch] [ebp-4h]

  v7[0] = "Monster/Goblin/acc9.equ";
  v7[1] = "Monster/Goblin/acc9-2.equ";
  v7[2] = "Monster/Goblin/acc9-3.equ";
  v7[3] = "Monster/Goblin/bcc9.equ";
  v7[4] = "Monster/Goblin/hcc9.equ";
  v7[5] = "Monster/Goblin/weapon9.equ";
  for ( i = 0; i < 6; ++i )
  {
    pMem = operator new(0x544u);
    v7[6] = pMem;
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



// AI 相位辅助（41L）
// ------------------------------------------------------------
// 0x59AC90 sub_59AC90
// ------------------------------------------------------------
int /*thiscall*/ sub_59AC90(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int v5; // edi
  int v6; // edx
  unsigned int v7; // edi
  int v8; // edx
  int v9; // [esp+Ch] [ebp+8h]
  int v10; // [esp+Ch] [ebp+8h]

  if ( nArg2 != 0 )
  {
    result = nArg2 - 2;
    if ( nArg2 == 2 )
    {
      result = nArg3;
      if ( nArg3 == 0 )
      {
        result = *(this + 2168) / 2;
        *(this + 2168) = result;
      }
    }
  }
  else
  {
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 830;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.30000001;
    sub_41A590(v5, v6, v9);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;
    *(float *)&v10 = COERCE_FLOAT(sub_41A5E0(v7)) - 0.30000001;
    sub_41A590(v7, v8, v10);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// AI 相位辅助（75L）
// ------------------------------------------------------------
// 0x59AD50 sub_59AD50
// ------------------------------------------------------------
int /*thiscall*/ sub_59AD50(char *this, int nArg2, int nArg3)
{
  char *pThis_1D73; // ecx
  int result; // eax
  int v6; // eax
  unsigned int v7; // edi
  int v8; // edx
  unsigned int pThis_2A0; // edi
  int v10; // edx
  int v11; // [esp+10h] [ebp+8h]
  int v12; // [esp+10h] [ebp+8h]

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
  if ( nArg2 != 0 )
  {
    result = nArg2 - 1;
    if ( nArg2 == 1 )
    {
      *((uint32_t *)this + 1891) = 1;
      *((uint32_t *)this + 1893) = 2;
    }
    else
    {
      result = nArg2 - 2;
      if ( nArg2 == 2 )
      {
        *((uint32_t *)this + 1899) = 50;
        *((uint32_t *)this + 1891) = 1;
        *((uint32_t *)this + 1893) = 2;
        if ( nArg3 == 0 )
          *((uint32_t *)this + 2168) *= 2;
      }
    }
  }
  else
  {
    v6 = *(uint32_t *)this;
    *((uint32_t *)this + 1899) = 50;
    v7 = (*(int (/*thiscall*/ **)(char *, uint32_t))(v6 + 672))(this, 0) + 830;
    *(float *)&v11 = COERCE_FLOAT(sub_41A5E0(v7)) + 0.30000001;
    sub_41A590(v7, v8, v11);
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.30000001;
    sub_41A590(pThis_2A0, v10, v12);
    return (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59AEC0 sub_59AEC0
// ------------------------------------------------------------
int /*thiscall*/ sub_59AEC0(uint32_t *this, int nArg2)
{
  int result; // eax
  int v4; // eax
  int v5; // edx

  result = sub_4D9170(nArg2);
  if ( nArg2 == *(this + 2170) )
  {
    v4 = *this;
    *(this + 2170) = 0;
    result = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 840))(this);
    if ( result == 14 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
        result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
    }
  }
  if ( nArg2 == *(this + 2171) )
  {
    v5 = *this;
    *(this + 2171) = 0;
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 1104))(this, 13);
  }
  return result;
}



// 登场曲：sub_406D60 写 "BKWALKER_01"（骨头行者 BKWalker 曲目槽）
// ------------------------------------------------------------
// 0x59AF40 sub_59AF40
// ------------------------------------------------------------
int /*thiscall*/ sub_59AF40(void *this, int nArg2)
{
  int result; // eax

  result = sub_4DBA80(nArg2);
  if ( nArg2 == 6 )
    return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "BKWALKER_01",
             -1,
             0,
             0);
  return result;
}



// AI 字段访问（this+8604/8684）
// ------------------------------------------------------------
// 0x59AF70 sub_59AF70
// ------------------------------------------------------------
char /*thiscall*/ sub_59AF70(int this, int nArg2)
{
  char result; // al

  result = sub_4DBC20(nArg2);
  if ( nArg2 == 6 )
  {
    result = *(uint8_t *)(this + 8604);
    if ( result != 0 )
      result = sub_64BDF0(this, *(uint32_t *)(this + 7256));
    *(uint32_t *)(this + 8684) = 0;
  }
  return result;
}



// 主状态门（this+200）
// ------------------------------------------------------------
// 0x59AFC0 sub_59AFC0
// ------------------------------------------------------------
int /*thiscall*/ sub_59AFC0(uint32_t *this)
{
  int result; // eax

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 14 )
    return sub_4D8750(this);
  if ( *(this + 2170) == 0 )
    return sub_4D8750(this);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  if ( result == 0 )
    return sub_4D8750(this);
  return result;
}



// ============================================================
// 【分区 9】哥布林系·指挥官与恐惧（0x59B000-0x59B960）
// 证据：GOBLIN_COMMAND 命令广播（RTTI cast 到友军）、REPAIR_OBJECT 修复、
//       GOBLIN_SCARED 恐惧 AI（sub_699000 时钟门）

// 指挥 AI：vt+212 GOBLIN_COMMAND（RTTI cast 寻友军广播, 56L）
// ------------------------------------------------------------
// 0x59B000 sub_59B000
// ------------------------------------------------------------
int /*thiscall*/ sub_59B000(uint32_t *this)
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
    if ( (uint16_t)result == 13 )
    {
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v12);
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v13);
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v10);
      (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, &v11);
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



// 指挥 AI 扩展（118L；RTTI cast 目标解算）
// ------------------------------------------------------------
// 0x59B130 sub_59B130
// ------------------------------------------------------------
int /*userpurge*/ sub_59B130@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<esi>, int nArg4)
{
  int result; // eax
  unsigned int i; // esi
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int pObj2; // ecx
  int v11; // ecx
  int v12; // edx
  int pObj; // esi
  int v14; // ebx
  int v15; // eax
  int pObj4; // esi
  int v17; // ebx
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int pObj3; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // ebx
  int v27; // eax
  int v28; // esi
  int v29; // eax
  int v30; // esi
  int v31; // eax
  unsigned int v34; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = pArg1[1813];
    if ( result != 0 )
    {
      for ( i = 0; ; ++i )
      {
        v7 = pArg1[29];
        v8 = *(uint32_t *)(v7 + 8);
        v34 = i;
        result = v8 != 0 ? (*(uint32_t *)(v7 + 12) - v8) >> 2 : 0;
        if ( (int)i >= result )
          break;
        v9 = *(uint32_t *)(v7 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(v7 + 12) - v9) >> 2 )
          pObj2 = *(uint32_t *)(v9 + 4 * i);
        else
          pObj2 = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )
        {
          v11 = pArg1[29];
          v12 = *(uint32_t *)(v11 + 8);
          if ( v12 != 0 && i < (*(uint32_t *)(v11 + 12) - v12) >> 2 )
            pObj = *(uint32_t *)(v12 + 4 * i);
          else
            pObj = 0;
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
          if ( v14 == (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 376))(pArg1) )
          {
            v15 = __RTDynamicCast(
                    pObj,
                    0,
                    &IRDActiveObject `RTTI Type Descriptor',
                    &CNGoblinGoblin `RTTI Type Descriptor',
                    0);
            pObj4 = v15;
            if ( v15 != 0
              && *(uint32_t *)(v15 + 7148) != 7
              && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1244))(pArg1, v15) != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(
                dword_8F8520,
                29,
                2,
                nArg2,
                nArg3);
              v17 = *(uint32_t *)dword_8F8520;
              v18 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 48))(pArg1);
              (*(void (/*thiscall*/ **)(int, int))(v17 + 36))(dword_8F8520, v18);
              v19 = *(uint32_t *)dword_8F8520;
              v20 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 52))(pArg1);
              (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);
              v21 = *(uint32_t *)dword_8F8520;
              v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
              (*(void (/*thiscall*/ **)(int, int))(v21 + 36))(dword_8F8520, v22);
              pObj3 = pArg1[1813];
              if ( nArg4 != 0 )
                pObj3 = nArg4;
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 13);
              v24 = *(uint32_t *)dword_8F8520;
              v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 48))(pObj4);
              (*(void (/*thiscall*/ **)(int, int))(v24 + 36))(dword_8F8520, v25);
              v26 = *(uint32_t *)dword_8F8520;
              v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 52))(pObj4);
              (*(void (/*thiscall*/ **)(int, int))(v26 + 36))(dword_8F8520, v27);
              v28 = *(uint32_t *)dword_8F8520;
              v29 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 48))(pObj3);
              (*(void (/*thiscall*/ **)(int, int))(v28 + 36))(dword_8F8520, v29);
              v30 = *(uint32_t *)dword_8F8520;
              v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 52))(pObj3);
              (*(void (/*thiscall*/ **)(int, int))(v30 + 36))(dword_8F8520, v31);
              return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
            }
          }
          i = v34;
        }
      }
    }
  }
  return result;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x59B310 sub_59B310
// ------------------------------------------------------------
int /*usercall*/ sub_59B310@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
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
    if ( v5 < pArg1[2168] )
      return sub_59B130(pArg1, nArg2, (int)pArg1, pArg1[1814]);
  }
  return result;
}



// AI 字段访问（this+8668）
// ------------------------------------------------------------
// 0x59B350 sub_59B350
// ------------------------------------------------------------
int /*thiscall*/ sub_59B350(uint32_t *this)
{
  int nRand; // eax
  int result; // eax
  int v4; // et2

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 5);
  *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 1.5;
  *((uint8_t *)this + 8668) = 1;
  nRand = rand();
  v4 = nRand % 100;
  result = nRand / 100;
  if ( v4 < 30 )
  {
    if ( *(this + 2159) < 0x10u )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, this + 2154, -1, 0, 0);
    else
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, uint32_t, uint32_t))(*this + 212))(
               this,
               *(this + 2154),
               -1,
               0,
               0);
  }
  return result;
}



// AI 字段访问（this+8668）
// ------------------------------------------------------------
// 0x59B3D0 sub_59B3D0
// ------------------------------------------------------------
int /*thiscall*/ sub_59B3D0(uint32_t *this)
{
  int result; // eax

  if ( *(this + 1813) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) != 0 )
  {
    sub_4DB200(24, 8);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1140))(this, -1, -1);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
  }
  result = *(this + 1905);
  *(float *)(result + 4) = *(float *)(result + 4) * 0.66666669;
  *((uint8_t *)this + 8668) = 0;
  return result;
}



// 指挥 AI 扩展（71L；RTTI cast）
// ------------------------------------------------------------
// 0x59B430 sub_59B430
// ------------------------------------------------------------
int /*thiscall*/ sub_59B430(uint32_t *this)
{
  uint32_t *pThis; // ebx
  unsigned int i; // edi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int pObj; // eax
  int *v12; // esi
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int v17; // [esp+Ch] [ebp-8h]

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
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 33) != 0 )
    {
      v8 = pThis[29];
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      pObj = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &CNGoblinBunker `RTTI Type Descriptor', 0);
      v12 = (int *)pObj;
      if ( pObj != 0 )
      {
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis);
        pThis = this;
        if ( v17 == v13
          && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int *))(*this + 1244))(this, v12) != 0
          && (double)v12[170] / (double)v12[171] * 100.0 <= 65.0 )
        {
          v14 = *this;
          v15 = (*(int (/*thiscall*/ **)(int *))(*v12 + 124))(v12);
          v16 = (*(int (/*thiscall*/ **)(int *, int))(*v12 + 120))(v12, v15);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v14 + 1140))(this, v16);
          if ( (uint8_t)result != 0 )
            *(this + 2171) = v12;
          return result;
        }
      }
    }
  }
  return result;
}



// 时钟门 AI（sub_699000, 64L）
// ------------------------------------------------------------
// 0x59B550 sub_59B550
// ------------------------------------------------------------
int /*usercall*/ sub_59B550@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int result; // eax
  int nRand; // eax
  int v5; // et2

  sub_4E0120();
  result = pArg1[1787];
  switch ( result )
  {
    case 0:
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1284))(pArg1);
      break;
    case 4:
      if ( pArg1[1813] == 0 )
        goto LABEL_6;
      if ( rand() % 100 < pArg1[2168] / 2 )
        sub_59B130(pArg1, nArg2, (int)pArg1, 0);
      nRand = rand();
      v5 = nRand % 100;
      result = nRand / 100;
      if ( v5 < 10 )
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1312))(pArg1);
      break;
    case 5:
      result = pArg1[1813];
      if ( result != 0 )
      {
        if ( *((uint8_t *)pArg1 + 8668) == 1 )
        {
          result = sub_699000((int)(pArg1 + 1910)) - pArg1[1926];  // 【clock_now(clk)】
          if ( result > 3000 )
            result = sub_59B3D0(pArg1);
        }
      }
      else
      {
LABEL_6:
        result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 13);
      }
      break;
    case 13:
      result = pArg1[1813];
      if ( result != 0 )
        goto LABEL_16;
      break;
    case 14:
    case 15:
      result = pArg1[1813];
      if ( result != 0 )
LABEL_16:
        result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1104))(pArg1, 4);
      break;
    default:
      return result;
  }
  return result;
}



// AI 字段访问（this+8668）
// ------------------------------------------------------------
// 0x59B680 sub_59B680
// ------------------------------------------------------------
int /*thiscall*/ sub_59B680(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int nRand; // eax
  int v8; // et2
  int nRand2; // eax
  uint32_t v10[2]; // [esp+8h] [ebp-8h]

  result = sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 5 )
  {
    nRand = rand();
    v8 = nRand % 100;
    result = nRand / 100;
    if ( v8 < 50 )
    {
      sub_64BDF0(this, *(uint32_t *)(this + 7256));
      v10[0] = 5;
      v10[1] = 6;
      nRand2 = rand() % 2;
      return sub_4DB200(24, v10[nRand2]);
    }
  }
  else if ( ArgList == 8 && *(uint8_t *)(this + 8668) == 1 )
  {
    sub_4DB200(24, 7);
    return sub_59B3D0((uint32_t *)this);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59B730 sub_59B730
// ------------------------------------------------------------
int /*usercall*/ sub_59B730@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int result; // eax

  sub_59B550(pArg1, nArg2);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);
    if ( result == 0 && pArg1[1787] != 6 )
    {
      result = pArg1[2171];
      if ( result == 0 )
        return sub_59B430(pArg1);
    }
  }
  return result;
}



// 修复技能：vt+212 播报 REPAIR_OBJECT（66L；工程哥布林修复演出）
// ------------------------------------------------------------
// 0x59B780 sub_59B780
// ------------------------------------------------------------
int /*thiscall*/ sub_59B780(void *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int *v7; // eax
  int v8; // eax
  int v9; // [esp-8h] [ebp-14h]
  int v10; // [esp-4h] [ebp-10h]

  result = sub_59B680((int)this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 14 )
  {
    v7 = *(int **)(LODWORD(fArg3) + 4);
    v10 = v7[1];
    v9 = *v7;
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this);
    v8 = sub_45EBE0(v9, v10);
    *((uint32_t *)this + 2170) = v8;
    *((uint32_t *)this + 2171) = 0;
    if ( v8 != 0 )
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 888))(this, 0, 0, 1000, 1000);
      sub_4926A0(**((uint32_t **)this + 1554));
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 196))(this, **((uint32_t **)this + 1554));
      (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
        this,
        1,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1104))(this, 13);
      return (*(int (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "REPAIR_OBJECT",
               -1,
               0,
               0);
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
      if ( (uint8_t)result != 0 )
        return (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
  }
  else
  {
    *((uint32_t *)this + 2170) = 0;
  }
  return result;
}



// 恐惧 AI：R_GOBLIN_* 语音 + GOBLIN_SCARED 播报（sub_699000 时钟门, 8668-8676 相位）
// ------------------------------------------------------------
// 0x59B8A0 sub_59B8A0
// ------------------------------------------------------------
int /*thiscall*/ sub_59B8A0(int this)
{
  int result; // eax

  *(uint32_t *)(this + 6792) = 2;
  *(uint32_t *)(this + 6796) = 2;
  *(uint32_t *)(this + 6800) = 2;
  *(uint32_t *)(this + 6804) = 3;
  *(uint32_t *)(this + 6808) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("GOBLIN_SCARED", 0xDu);  // 【std::string构造赋值】
  *(uint32_t *)(this + 7320) = 100;
  *(uint32_t *)(this + 7356) = -30;
  *(uint32_t *)(this + 7324) = 350;
  *(uint32_t *)(this + 7328) = 500;
  *(uint8_t *)(this + 8668) = 0;
  result = sub_699000(this + 36);  // 【clock_now(clk)】
  *(uint32_t *)(this + 8676) = result;
  *(uint32_t *)(this + 8672) = 10;
  return result;
}



// ============================================================
// 【分区 10】哥布林系·狼牙棒/加洛克/圣装（0x59B960-0x59C290）
// 证据：MorningStar.equ 狼牙棒、GalokArmor.equ 加洛克护甲、CwGobSantaBeard.equ 圣诞胡装、
//       Weapon03/acc1/hcc1/gcc1 标准四件套

// AI 相位辅助
// ------------------------------------------------------------
// 0x59B960 sub_59B960
// ------------------------------------------------------------
void /*thiscall*/ sub_59B960(void *this, int nArg2)
{
  int pObj; // esi
  uint8_t v3[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  void *Src; // [esp+14h] [ebp-18h]
  int v6; // [esp+18h] [ebp-14h]
  void *pThis; // [esp+1Ch] [ebp-10h]
  int v8; // [esp+28h] [ebp-4h]

  pThis = this;
  Block = nullptr;
  Src = nullptr;
  v6 = 0;
  pObj = nArg2;
  v8 = 0;
  nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 48))(nArg2);
  sub_430C80(nullptr, 1, (int)&nArg2);
  nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
  sub_430C80(nullptr, 1, (int)&nArg2);
  (*(void (/*thiscall*/ **)(void *, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pThis + 560))(pThis, 14, v3, 0, 0);
  if ( Block != nullptr )
    j__free(Block);
}



// 主状态门（this+200, 57L）
// ------------------------------------------------------------
// 0x59BA50 sub_59BA50
// ------------------------------------------------------------
void /*thiscall*/ sub_59BA50(int *this)
{
  int fld_e2171; // eax
  int v3; // edi
  int fld_e21713; // ebx
  int fld_e21714; // edi
  signed int fld_e21712; // [esp+4h] [ebp-4h]

  sub_4E1780(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 && *(this + 1787) == 6 )
  {
    fld_e2171 = *(this + 2171);
    if ( fld_e2171 != 0 )
    {
      v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2171 + 340))(fld_e2171) + 32) / 2 + 30;
      fld_e21712 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2171) + 340))(*(this + 2171)) + 36);
      fld_e21713 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2171) + 120))(*(this + 2171));
      if ( (int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e21713) < v3 )
      {
        fld_e21714 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2171) + 124))(*(this + 2171));
        if ( (int)abs32((*(int (/*thiscall*/ **)(int *))(*this + 124))(this) - fld_e21714) < fld_e21712 )
          sub_59B960(this, *(this + 2171));
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 14
    && *(this + 2170) != 0
    && (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != 0
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) != 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2170) + 308))(*(this + 2170)) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 2170) + 560))(
        *(this + 2170),
        4,
        0,
        0,
        0);
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      if ( (double)*(int *)(*(this + 2170) + 680) / (double)*(int *)(*(this + 2170) + 684) * 100.0 >= 65.0
        || rand() % 100 >= 30 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      }
      else
      {
        sub_59B960(this, *(this + 2170));
      }
    }
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59BBF0 sub_59BBF0
// ------------------------------------------------------------
void */*thiscall*/ sub_59BBF0(void *Block, char pszArg2)
{
  sub_59BC20();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59BC20 sub_59BC20
// ------------------------------------------------------------
int /*thiscall*/ sub_59BC20(char *this)
{
  *(uint32_t *)this = &CNAuraMasterBattle::`vftable';
  return sub_591190(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59BC30 sub_59BC30
// ------------------------------------------------------------
void */*thiscall*/ sub_59BC30(void *Block, char pszArg2)
{
  sub_59BC60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59BC60 sub_59BC60
// ------------------------------------------------------------
int /*thiscall*/ sub_59BC60(char *this)
{
  *(uint32_t *)this = &CNAuraMasterATDFSPEEDUp::`vftable';
  return sub_591190(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59BC70 sub_59BC70
// ------------------------------------------------------------
int /*thiscall*/ sub_59BC70(void *this)
{
  uint32_t *pMem; // edi
  uint32_t *pMem2; // ecx

  sub_4DE410();
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 700))(this);
  sub_53F6A0(this);
  pMem = operator new(0x84u);
  if ( pMem != nullptr )
  {
    sub_64C2C0(300, 50);
    *pMem = &CNAuraMasterBattleGoblinKinol::`vftable';
    pMem2 = pMem;
  }
  else
  {
    pMem2 = nullptr;
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, void *, void *, uint32_t, uint32_t, uint32_t, int))(*pMem2 + 56))(
           pMem2,
           this,
           this,
           0,
           0,
           0,
           -1);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59BD10 sub_59BD10
// ------------------------------------------------------------
char /*usercall*/ sub_59BD10@<al>(int pArg1@<ecx>, int nArg2@<edi>)
{
  char result; // al
  uint32_t *pMem; // edi
  uint32_t *pMem2; // ecx
  float v6; // [esp+8h] [ebp-1Ch]
  float v7; // [esp+Ch] [ebp-18h]
  float v8; // [esp+10h] [ebp-14h]
  float v9; // [esp+14h] [ebp-10h]

  sub_4E1780((uint32_t *)pArg1);
  result = *(uint8_t *)(pArg1 + 8680);
  if ( result == 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1308))(pArg1);
    v6 = (double)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 384))(pArg1, 0) * 0.0099999998;
    v7 = (double)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 1) * 0.0099999998;
    v8 = (double)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 2) * 0.0099999998;
    v9 = (double)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 3) * 0.0099999998;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 700))(pArg1, pArg1);
    sub_53F6A0(nArg2);
    pMem = operator new(0x90u);
    if ( pMem != nullptr )
    {
      sub_64C710(300, LODWORD(v6), LODWORD(v7), LODWORD(v8), LODWORD(v9));
      *pMem = &CNAuraMasterATDFSPEEDUp_KingGalok::`vftable';
      pMem2 = pMem;
    }
    else
    {
      pMem2 = nullptr;
    }
    result = (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t))(*pMem2 + 56))(pMem2, pArg1, pArg1, 0, 0, 0);
    *(uint8_t *)(pArg1 + 8680) = 1;
  }
  return result;
}



// 狼牙棒哥布林装载：Monster/Goblin/{hcc1,gcc1,Weapon03,acc1}.equ（55L）
// ------------------------------------------------------------
// 0x59BE40 sub_59BE40
// ------------------------------------------------------------
int /*thiscall*/ sub_59BE40(void *this)
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
  int result; // eax

  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/hcc1.equ", 0);
  else
    v3 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/gcc1.equ", 0);
  else
    v6 = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v6);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/Weapon03.equ", 0);
  else
    v9 = nullptr;
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v9);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/acc1.equ", 0);
  else
    v12 = nullptr;
  result = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v12);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// 圣诞外观：Monster/Goblin/CwGobSantaBeard.equ（CwGob=圣诞哥布林换装）
// ------------------------------------------------------------
// 0x59BF90 sub_59BF90
// ------------------------------------------------------------
int /*thiscall*/ sub_59BF90(uint32_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  int result; // eax

  *(this + 2170) = 0;
  *(this + 2171) = 0;
  *((uint8_t *)this + 8605) = 0;
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/CwGobSantaBeard.equ", 0);
  else
    v3 = nullptr;
  result = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 4))(result, 1);
  return result;
}



// 加洛克装甲装载：{hcc1,gcc1,MorningStar,acc1}.equ + GalokArmor.equ + acc4.equ（83L）
// ------------------------------------------------------------
// 0x59C020 sub_59C020
// ------------------------------------------------------------
int /*thiscall*/ sub_59C020(void *this)
{
  char *pMem; // eax
  char *v3; // edi
  int pThis_310; // eax
  char *pMem2; // eax
  int pThis_3102; // eax
  char *pMem3; // eax
  int pThis_3103; // eax
  char *pMem4; // eax
  int pThis_3104; // eax
  char *pMem5; // eax
  char *v12; // ebx
  int pThis_3105; // eax
  char *pMem6; // eax
  int pThis_3106; // eax
  char *Block; // [esp+10h] [ebp-1Ch]
  char *v18; // [esp+14h] [ebp-18h]
  char *v19; // [esp+18h] [ebp-14h]
  char *v20; // [esp+1Ch] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v20 = sub_4BA9E0(pMem, "Monster/Goblin/hcc1.equ", 0);
  else
    v20 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v20);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v19 = sub_4BA9E0(pMem2, "Monster/Goblin/gcc1.equ", 0);
  else
    v19 = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v19);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v18 = sub_4BA9E0(pMem3, "Monster/Goblin/MorningStar.equ", 0);
  else
    v18 = nullptr;
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v18);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    Block = sub_4BA9E0(pMem4, "Monster/Goblin/acc1.equ", 0);
  else
    Block = nullptr;
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v12 = sub_4BA9E0(pMem5, "Monster/Goblin/GalokArmor.equ", 0);
  else
    v12 = nullptr;
  pThis_3105 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v12);
  if ( pThis_3105 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3105 + 4))(pThis_3105, 1);
  pMem6 = (char *)operator new(0x544u);
  if ( pMem6 != nullptr )
    v3 = sub_4BA9E0(pMem6, "Monster/Goblin/acc4.equ", 0);
  pThis_3106 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3106 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3106 + 4))(pThis_3106, 1);
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 688))(this);
  sub_4EB2C0(1.2);
  sub_4EB6A0(1.2);
  sub_4EB6A0(1.2);
  sub_4EB6A0(1.2);
  sub_4EB6A0(1.2);
  sub_4EB6A0(1.2);
  return sub_4EB6A0(1.2);
}



// ============================================================
// 【分区 11】哥布林系·炸弹兵与 PRAG（0x59C290-0x59CEC0）
// 证据：Particle/AimingBomb.ptl + Bomb.ptl 投弹双粒子（0x59C5C0/0x59C810）、
//       GOBLIN_COMMAND 指挥、PRAG_01 登场曲（0x59C9E0）

// 狼牙棒装载 2：{hcc1,gcc1,MorningStar,acc1}.equ（59L）
// ------------------------------------------------------------
// 0x59C290 sub_59C290
// ------------------------------------------------------------
int /*thiscall*/ sub_59C290(void *this)
{
  char *pMem; // eax
  char *v3; // edi
  int pThis_310; // eax
  char *pMem2; // eax
  int pThis_3102; // eax
  char *pMem3; // eax
  char *v8; // ebx
  int pThis_3103; // eax
  char *pMem4; // eax
  int pThis_3104; // eax
  char *Block; // [esp+10h] [ebp-14h]
  char *v14; // [esp+14h] [ebp-10h]

  pMem = (char *)operator new(0x544u);
  v3 = nullptr;
  if ( pMem != nullptr )
    v14 = sub_4BA9E0(pMem, "Monster/Goblin/hcc1.equ", 0);
  else
    v14 = nullptr;
  pThis_310 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v14);
  if ( pThis_310 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_310 + 4))(pThis_310, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    Block = sub_4BA9E0(pMem2, "Monster/Goblin/gcc1.equ", 0);
  else
    Block = nullptr;
  pThis_3102 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, Block);
  if ( pThis_3102 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3102 + 4))(pThis_3102, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v8 = sub_4BA9E0(pMem3, "Monster/Goblin/MorningStar.equ", 0);
  else
    v8 = nullptr;
  pThis_3103 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v8);
  if ( pThis_3103 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3103 + 4))(pThis_3103, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v3 = sub_4BA9E0(pMem4, "Monster/Goblin/acc1.equ", 0);
  pThis_3104 = (*(int (/*thiscall*/ **)(void *, char *))(*(uint32_t *)this + 784))(this, v3);
  if ( pThis_3104 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_3104 + 4))(pThis_3104, 1);
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 688))(this);
  sub_4EB2C0(1.1);
  sub_4EB6A0(1.1);
  sub_4EB6A0(1.1);
  sub_4EB6A0(1.1);
  return sub_4EB6A0(1.1);
}



// 子类扩展字段复位（this+8612..8656）
// ------------------------------------------------------------
// 0x59C440 sub_59C440
// ------------------------------------------------------------
int /*thiscall*/ sub_59C440(int this)
{
  *(uint8_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0xFFFF;
  *(uint32_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8656) = 3;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59C470 sub_59C470
// ------------------------------------------------------------
int /*thiscall*/ sub_59C470(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax

  if ( nArg2 == 0 )
  {
    *(this + 1899) = 0;
LABEL_6:
    result = *(this + 2165) / 2;
    *(this + 2165) = result;
    return result;
  }
  result = nArg2 - 1;
  if ( nArg2 == 1 )
  {
    result = *(this + 2166) / 2;
    *(this + 2166) = result;
    if ( nArg3 == 2 )
      goto LABEL_6;
  }
  return result;
}



// AI 相位门（this+8660/8664）
// ------------------------------------------------------------
// 0x59C4C0 sub_59C4C0
// ------------------------------------------------------------
int /*thiscall*/ sub_59C4C0(int this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_21D4; // edx

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
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 )
    {
      result = 2;
      *(uint32_t *)(this + 8664) *= 2;
      *(uint32_t *)(this + 7580) = 1;
      *(uint32_t *)(this + 7572) = 2;
      if ( nArg3 == 2 )
      {
        result = 2 * *(uint32_t *)(this + 8660);
        *(uint32_t *)(this + 8660) = result;
      }
    }
    else if ( nArg2 == 2 )
    {
      *(uint32_t *)(this + 7580) = 1;
      *(uint32_t *)(this + 7572) = 2;
    }
  }
  else
  {
    fld_21D4 = 2 * *(uint32_t *)(this + 8660);
    *(uint32_t *)(this + 7596) = -100;
    *(uint32_t *)(this + 8660) = fld_21D4;
  }
  return result;
}



// 投弹技能：Particle/AimingBomb.ptl 瞄准 + Particle/Bomb.ptl 落点（73L）
// ------------------------------------------------------------
// 0x59C5C0 sub_59C5C0
// ------------------------------------------------------------
int /*thiscall*/ sub_59C5C0(uint32_t *this)
{
  int v2; // esi
  uint64_t fld_e1813; // rax
  int fld_e18132; // eax
  int v5; // edx
  int fld_e2167; // eax
  uint32_t v8[26]; // [esp+10h] [ebp-68h] BYREF

  v8[25] = dword_796E50;
  sub_423A20(v8);
  if ( *(this + 1813) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1244))(this, *(this + 1813)) != 0 )
  {
    qmemcpy(
      v8,
      (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/AimingBomb.ptl"),
      0x62u);
    v2 = (uint64_t)((double)(int)(uint64_t)((double)(2 * *(uint32_t *)((char *)&v8[7] + 3))
                                                          / (double)v8[17]
                                                          * 1000.0)
                          * 1.7);
    fld_e1813 = (uint64_t)((double (/*fastcall*/ *)(uint32_t *, uint32_t, uint32_t, uint32_t))*(uint32_t *)(*this + 164))(
                             this,
                             (uint64_t)((double)(int)(uint64_t)((double)(2
                                                                                       * *(uint32_t *)((char *)&v8[7] + 3))
                                                                              / (double)v8[17]
                                                                              * 1000.0)
                                              * 1.7) >> 32,
                             *(this + 1813),
                             0);
    HIDWORD(fld_e1813) = *this;
    v8[18] = fld_e1813;
    fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(HIDWORD(fld_e1813) + 8))(this, *(this + 1813), 0);
    v5 = *this;
    *(uint32_t *)((char *)&v8[3] + 3) = 1000 * fld_e18132 / v2;
    *(uint32_t *)((char *)&v8[4] + 3) = 1000
                                    * (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(v5 + 8))(
                                        this,
                                        *(this + 1813),
                                        0)
                                    / v2;
  }
  else
  {
    qmemcpy(
      v8,
      (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/Bomb.ptl"),
      0x62u);
  }
  fld_e2167 = *(this + 2167);
  if ( fld_e2167 == 30021 )
    BYTE1(v8[22]) = 3;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
           this,
           fld_e2167,
           0,
           v8,
           0,
           0,
           0,
           60,
           1,
           0,
           0,
           0);
}



// 指挥 AI：GOBLIN_COMMAND（RTTI cast, 67L）
// ------------------------------------------------------------
// 0x59C700 sub_59C700
// ------------------------------------------------------------
int /*thiscall*/ sub_59C700(uint32_t *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // edi
  int v11; // ebx
  int v12; // eax
  int fld_e1813; // eax
  int v14; // [esp+0h] [ebp-10h]
  unsigned int v15; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
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
                &CNGoblinStoner `RTTI Type Descriptor',
                0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813), 0);
          sub_49C620(7, fld_e1813, v14);
          sub_4D82D0(0, 0);
          v14 = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*this + 212))(this, "GOBLIN_COMMAND", -1, 0);
        }
      }
      i = v15;
    }
  }
  return result;
}



// 投弹技能 2：AimingBomb.ptl + Bomb.ptl（94L）
// ------------------------------------------------------------
// 0x59C810 sub_59C810
// ------------------------------------------------------------
char /*usercall*/ sub_59C810@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  char v3; // al
  int v4; // edx
  int v5; // esi
  uint64_t v6; // rax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  uint8_t v11[4]; // [esp+8h] [ebp-88h] BYREF
  void *Block; // [esp+Ch] [ebp-84h]
  int v13; // [esp+10h] [ebp-80h]
  int v14; // [esp+14h] [ebp-7Ch]
  int v15; // [esp+18h] [ebp-78h]
  uint32_t v16[29]; // [esp+1Ch] [ebp-74h] BYREF

  v16[25] = dword_796E50;
  Block = nullptr;
  v13 = 0;
  v14 = 0;
  v16[28] = 0;
  if ( (int)sub_4E0CD0(17, 0, v11, -1) < 2
    || (*(int (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t))(**(uint32_t **)Block + 8))(
         *(uint32_t *)Block,
         *((uint32_t *)Block + 1),
         0) >= 200 )
  {
    if ( Block != nullptr )
      j__free(Block);
    return 0;
  }
  else
  {
    sub_423A20(v16);
    v3 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int))(*pArg1 + 1244))(pArg1, *(uint32_t *)Block, nArg2);
    v4 = *pArg1;
    if ( v3 != 0 )
    {
      qmemcpy(
        v16,
        (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(v4 + 588))(pArg1, "Particle/AimingBomb.ptl"),
        0x62u);
      v15 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v16[7] + 3)) / (double)v16[17] * 1000.0);
      v5 = (uint64_t)((double)v15 * 1.7);
      v6 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, uint32_t, uint32_t))*(uint32_t *)(*pArg1 + 164))(
                               pArg1,
                               *(uint32_t *)Block,
                               0);
      HIDWORD(v6) = *pArg1;
      v16[18] = v6;
      v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(HIDWORD(v6) + 8))(pArg1, *(uint32_t *)Block, 0);
      v8 = *pArg1;
      *(uint32_t *)((char *)&v16[3] + 3) = 1000 * v7 / v5;
      *(uint32_t *)((char *)&v16[4] + 3) = 1000
                                       * (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(v8 + 8))(
                                           pArg1,
                                           *(uint32_t *)Block,
                                           0)
                                       / v5;
    }
    else
    {
      qmemcpy(
        v16,
        (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(v4 + 588))(pArg1, "Particle/Bomb.ptl"),
        0x62u);
    }
    v9 = pArg1[2167];
    if ( v9 == 30021 )
      BYTE1(v16[22]) = 3;
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
      pArg1,
      v9,
      0,
      v16,
      0,
      0,
      0,
      60,
      1,
      0,
      0,
      0);
    if ( Block != nullptr )
      j__free(Block);
    return 1;
  }
}



// 登场曲：sub_406D60 写 "PRAG_01"（普拉格曲目槽, 71L）
// ------------------------------------------------------------
// 0x59C9E0 sub_59C9E0
// ------------------------------------------------------------
char /*usercall*/ sub_59C9E0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // edi
  uint32_t *v5; // eax

  if ( pArg1[1639] == 8 )
  {
    v3 = (int)(pArg1 + 1757);
    if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 4 && *(uint8_t *)(pArg1[30] + 170) != 0 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg2) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
          pArg1,
          30043,
          0,
          0,
          0,
          30,
          0,
          0,
          4,
          0,
          0,
          0);
      nArg2 = 0;
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*pArg1 + 212))(pArg1, "PRAG_01", -1, 0);
    }
    if ( *((uint8_t *)pArg1 + 8612) == 0 && *(int *)(pArg1[30] + 148) > 2 )
    {
      if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 3 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 && sub_59C810(pArg1, v3) == 0 )
        {
          sub_59C5C0(pArg1);
          *((uint8_t *)pArg1 + 8612) = 1;
          return sub_4E1780(pArg1);
        }
      }
      else if ( sub_41A5E0((unsigned int)(pArg1 + 1757)) == 0 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 308))(pArg1, nArg2) != 0 )
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
            pArg1,
            pArg1[2155],
            pArg1[2156],
            pArg1[2154],
            0,
            20,
            0,
            60,
            4,
            0,
            0,
            0);
        if ( pArg1[2163] < 0x10u )
          v5 = pArg1 + 2158;
        else
          v5 = (uint32_t *)pArg1[2158];
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t))(*pArg1 + 212))(pArg1, v5, -1, 0);
      }
      *((uint8_t *)pArg1 + 8612) = 1;
    }
  }
  return sub_4E1780(pArg1);
}



// 参数打包 AI（90L sub_431230）
// ------------------------------------------------------------
// 0x59CB40 sub_59CB40
// ------------------------------------------------------------
void /*thiscall*/ sub_59CB40(uint32_t *this)
{
  int v2; // edx
  int fld_e29; // edi
  int fld_e1813; // ebx
  int v5; // ebx
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  uint32_t v7[4]; // [esp+14h] [ebp-10h] BYREF

  sub_4E0120();
  switch ( *(this + 1787) )
  {
    case 0:
      goto LABEL_9;
    case 1:
      if ( *(this + 1813) != 0 )
      {
        if ( rand() % 100 >= *(this + 2166) )
        {
          if ( rand() % 100 >= *(this + 2165) )
          {
            if ( rand() % 100 >= 20 * ((*(this + 1909) == 0) + 1) )
            {
              if ( rand() % 100 < 5 )
              {
                fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
                fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
                if ( (int)abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - fld_e1813) <= 60
                  && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) > 40 )
                {
                  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
                  if ( v5 < sub_425050(fld_e29) - 40 )
                    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 3);
                }
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 2);
            }
          }
          else
          {
            v2 = *this;
            *(this + 2164) = 3;
            (*(void (/*thiscall*/ **)(uint32_t *, int))(v2 + 1104))(this, 18);
          }
        }
        else
        {
          sub_59C700(this);
        }
      }
      else
      {
LABEL_9:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);
      }
      return;
    case 0xD:
      goto LABEL_21;
    case 0xF:
      if ( *(this + 1813) != 0 )
LABEL_21:
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 1);
      break;
    case 0x12:
      if ( *(this + 1639) == 0 )
      {
        --*(this + 2164);
        memset(&pBuf[1], 0, 12);
        v7[3] = 0;
        v7[0] = 0;
        sub_431230((int)pBuf, v7);
        (*(void (/*thiscall*/ **)(uint32_t *, int, void **, uint32_t, uint32_t))(*this + 560))(this, 8, pBuf, 0, 0);
        if ( *(this + 2164) == 0 )
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 1);
        sub_5E5260(pBuf);
      }
      break;
    default:
      return;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59CDB0 sub_59CDB0
// ------------------------------------------------------------
char /*usercall*/ sub_59CDB0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  uint32_t *v4; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0
    && pArg1[1639] == 8
    && sub_41A5E0((unsigned int)(pArg1 + 1757)) == 0
    && *((uint8_t *)pArg1 + 8612) == 0
    && *(int *)(pArg1[30] + 148) > 2 )
  {
    if ( pArg1[1787] == 18 || pArg1[1908] != 0 || pArg1[1909] != 0 || rand() % 100 >= 20 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
        pArg1,
        pArg1[2155],
        pArg1[2156],
        pArg1[2154],
        0,
        20,
        0,
        60,
        4,
        0,
        0,
        0);
      if ( pArg1[2163] < 0x10u )
        v4 = pArg1 + 2158;
      else
        v4 = (uint32_t *)pArg1[2158];
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, v4, -1, 0, 0);
    }
    else if ( sub_59C810(pArg1, nArg2) == 0 )
    {
      sub_59C5C0(pArg1);
      *((uint8_t *)pArg1 + 8612) = 1;
      return sub_4E1780(pArg1);
    }
    *((uint8_t *)pArg1 + 8612) = 1;
  }
  return sub_4E1780(pArg1);
}



// ============================================================
// 【分区 12】哥布林系·速投/火冰导弹/狂气光环（0x59CEC0-0x59E230）
// 证据：Particle/FastThrowStone.ptl 速投、PassiveObject/Common/Particle/
//       FireMissile.ptl 与 IceMissile.ptl 属性导弹、AURA_FURY 狂气光环（0x59DEE0）

// 速投哥布林装载：R_GOBLIN_* 语音 + {tcc2-3,acc2,hcc3-3,gcc1,acc1,bcc1-2}.equ
//   + Particle/FastThrowStone.ptl 速投粒子（98L）
// ------------------------------------------------------------
// 0x59CEC0 sub_59CEC0
// ------------------------------------------------------------
int /*thiscall*/ sub_59CEC0(uint32_t *this)
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
  int v20; // edx
  int result; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/tcc2-3.equ", 0);
  else
    v3 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/acc2.equ", 0);
  else
    v6 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/hcc3-3.equ", 0);
  else
    v9 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/gcc1.equ", 0);
  else
    v12 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v15 = sub_4BA9E0(pMem5, "Monster/Goblin/acc1.equ", 0);
  else
    v15 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);
  pMem6 = (char *)operator new(0x544u);
  if ( pMem6 != nullptr )
    v18 = sub_4BA9E0(pMem6, "Monster/Goblin/bcc1-2.equ", 0);
  else
    v18 = nullptr;
  pObj6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);
  if ( pObj6 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 4))(pObj6, 1);
  *(this + 2154) = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/FastThrowStone.ptl");
  *(this + 2155) = 30075;
  *(this + 2156) = 0;
  sub_4015C0("THROW_STONE", 0xBu);  // 【std::string构造赋值】
  v20 = *this;
  *(this + 1829) = 500;
  *(this + 1870) = 500;
  *(this + 2165) = 10;
  *(this + 2166) = 5;
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v20 + 384))(this, 0);
  *(this + 2167) = result;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59D180 sub_59D180
// ------------------------------------------------------------
int /*thiscall*/ sub_59D180(int this, int nArg2, int nArg3)
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
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 || nArg2 == 2 )
    {
      *(uint32_t *)(this + 7588) = 1;
      *(uint32_t *)(this + 7572) = 2;
    }
  }
  else
  {
    *(uint32_t *)(this + 7596) = -50;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59D230 sub_59D230
// ------------------------------------------------------------
int /*thiscall*/ sub_59D230(int *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int fld_e29; // edi
  int fld_e1813; // ebx
  int v7; // edi

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
    case 1:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
      if ( rand() % 100 < 3 * ((*(this + 1909) == 0) + 1) )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 2);
      nRand = rand();
      v4 = nRand % 100;
      result = nRand / 100;
      if ( v4 < 10 )
      {
        fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
        fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
        result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e1813);
        if ( result <= 60 )
        {
          result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
          if ( result > 40 )
          {
            v7 = sub_425050(fld_e29) - 40;
            result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
            if ( result < v7 )
              return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 3);
          }
        }
      }
      return result;
    case 13:
      goto LABEL_4;
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 1);
      break;
    default:
      return result;
  }
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59D360 sub_59D360
// ------------------------------------------------------------
char /*thiscall*/ sub_59D360(uint32_t *this)
{
  uint32_t *pThis_86E; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 1757)) == 0
    && *((uint8_t *)this + 8612) == 0
    && *(int *)(*(this + 30) + 148) > 2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
      this,
      *(this + 2155),
      *(this + 2156),
      *(this + 2154),
      0,
      20,
      0,
      60,
      4,
      0,
      0,
      0);
    if ( *(this + 2163) < 0x10u )
      pThis_86E = this + 2158;
    else
      pThis_86E = (uint32_t *)*(this + 2158);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_86E, -1, 0, 0);
    *((uint8_t *)this + 8612) = 1;
  }
  return sub_4E1780(this);
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x59D410 sub_59D410
// ------------------------------------------------------------
void /*userpurge*/ sub_59D410(uint32_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint8_t v5[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  sub_4D90A0(uArg3);
  if ( *uArg32 == 7 && pArg1[1639] == 0 )
  {
    sub_4D84F0(0, 0);
    if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg2) >= uArg32[3] )
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 148))(pArg1, 1);
    else
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 148))(pArg1, 0);
    Block = nullptr;
    v7 = 0;
    v8 = 0;
    v9 = 0;
    uArg3 = nullptr;
    sub_431230((int)v5, &uArg3);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t))(*pArg1 + 560))(pArg1, 8, v5, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 火导弹哥布林装载：R_GOBLIN_* 语音 + {acc4-2,Hcc2-2,gcc1-3,tcc1-2,bcc1-2}.equ
//   + PassiveObject/Common/Particle/FireMissile.ptl（98L）
// ------------------------------------------------------------
// 0x59D4D0 sub_59D4D0
// ------------------------------------------------------------
uint64_t /*usercall*/ sub_59D4D0@<edx:eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  char *pMem; // eax
  char *v4; // eax
  int pObj3; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj2; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj5; // eax
  char *pMem4; // eax
  char *v13; // eax
  int pObj4; // eax
  char *pMem5; // eax
  char *v16; // eax
  int pObj; // eax
  int v18; // eax
  int v19; // edx
  int v20; // edi
  uint32_t *v21; // eax
  uint64_t result; // rax
  float v23; // [esp+38h] [ebp-2Ch]
  float v24; // [esp+3Ch] [ebp-28h]
  void *Block; // [esp+50h] [ebp-14h]
  int v26; // [esp+54h] [ebp-10h]

  pArg1[1698] = 2;
  pArg1[1699] = 2;
  pArg1[1700] = 2;
  pArg1[1701] = 3;
  pArg1[1702] = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Goblin/acc4-2.equ", 0);
  else
    v4 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, v4, nArg2);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/Goblin/Hcc2-2.equ", 0);
  else
    v7 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v7);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v10 = sub_4BA9E0(pMem3, "Monster/Goblin/gcc1-3.equ", 0);
  else
    v10 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v10);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v13 = sub_4BA9E0(pMem4, "Monster/Goblin/tcc1-2.equ", 0);
  else
    v13 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v13);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v16 = sub_4BA9E0(pMem5, "Monster/Goblin/bcc1-2.equ", 0);
  else
    v16 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v16);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  v18 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
          dword_8F84E4,
          "PassiveObject/Common/Particle/FireMissile.ptl");
  v19 = *pArg1;
  pArg1[2154] = v18;
  pArg1[2155] = 30047;
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v19 + 384))(pArg1, 0);
  v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 384))(pArg1, 1);
  v20 = pArg1[1821] - pArg1[1820];
  v21 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 672))(pArg1, 3);
  v24 = (float)v26;
  v23 = (float)(int)Block;
  result = (uint64_t)sub_4049C0(v23, v24, *v21 - pArg1[1820], v20);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pArg1[2156] = result;
  pArg1[1829] = 500;
  return result;
}



// 子类扩展字段复位（this+8612..8624）
// ------------------------------------------------------------
// 0x59D760 sub_59D760
// ------------------------------------------------------------
int /*thiscall*/ sub_59D760(int this)
{
  *(uint8_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0xFFFF;
  *(uint32_t *)(this + 8624) = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59D780 sub_59D780
// ------------------------------------------------------------
int /*thiscall*/ sub_59D780(int this, int nArg2, int nArg3)
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
  if ( nArg2 != 0 )
  {
    if ( nArg2 == 1 || nArg2 == 2 )
    {
      *(uint8_t *)(this + 7534) = 1;
      *(uint32_t *)(this + 7572) = 2;
    }
  }
  else
  {
    *(uint32_t *)(this + 7596) = -50;
  }
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x59D830 sub_59D830
// ------------------------------------------------------------
void /*userpurge*/ sub_59D830(uint32_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint8_t v5[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+20h] [ebp-4h]

  uArg32 = uArg3;
  sub_4D90A0(uArg3);
  if ( *uArg32 == 7 && pArg1[1639] == 0 )
  {
    sub_4D84F0(0, 0);
    if ( (unsigned int)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, nArg2) >= uArg32[3] )
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 148))(pArg1, 1);
    else
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 148))(pArg1, 0);
    Block = nullptr;
    v7 = 0;
    v8 = 0;
    v9 = 0;
    uArg3 = nullptr;
    sub_431230((int)v5, &uArg3);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t))(*pArg1 + 560))(pArg1, 8, v5, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 冰导弹哥布林装载：R_GOBLIN_* 语音 + {acc4,Hcc2,gcc1-3,tcc1-2,bcc1-2}.equ
//   + PassiveObject/Common/Particle/IceMissile.ptl（98L）
// ------------------------------------------------------------
// 0x59D8F0 sub_59D8F0
// ------------------------------------------------------------
uint64_t /*usercall*/ sub_59D8F0@<edx:eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  char *pMem; // eax
  char *v4; // eax
  int pObj3; // eax
  char *pMem2; // eax
  char *v7; // eax
  int pObj2; // eax
  char *pMem3; // eax
  char *v10; // eax
  int pObj5; // eax
  char *pMem4; // eax
  char *v13; // eax
  int pObj4; // eax
  char *pMem5; // eax
  char *v16; // eax
  int pObj; // eax
  int v18; // eax
  int v19; // edx
  int v20; // edi
  uint32_t *v21; // eax
  uint64_t result; // rax
  float v23; // [esp+38h] [ebp-2Ch]
  float v24; // [esp+3Ch] [ebp-28h]
  void *Block; // [esp+50h] [ebp-14h]
  int v26; // [esp+54h] [ebp-10h]

  pArg1[1698] = 2;
  pArg1[1699] = 2;
  pArg1[1700] = 2;
  pArg1[1701] = 3;
  pArg1[1702] = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v4 = sub_4BA9E0(pMem, "Monster/Goblin/acc4.equ", 0);
  else
    v4 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *, int))(*pArg1 + 784))(pArg1, v4, nArg2);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v7 = sub_4BA9E0(pMem2, "Monster/Goblin/Hcc2.equ", 0);
  else
    v7 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v7);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v10 = sub_4BA9E0(pMem3, "Monster/Goblin/gcc1-3.equ", 0);
  else
    v10 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v10);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v13 = sub_4BA9E0(pMem4, "Monster/Goblin/tcc1-2.equ", 0);
  else
    v13 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v13);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v16 = sub_4BA9E0(pMem5, "Monster/Goblin/bcc1-2.equ", 0);
  else
    v16 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*pArg1 + 784))(pArg1, v16);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  v18 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
          dword_8F84E4,
          "PassiveObject/Common/Particle/IceMissile.ptl");
  v19 = *pArg1;
  pArg1[2154] = v18;
  pArg1[2155] = 30057;
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v19 + 384))(pArg1, 0);
  v26 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 384))(pArg1, 1);
  v20 = pArg1[1821] - pArg1[1820];
  v21 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 672))(pArg1, 3);
  v24 = (float)v26;
  v23 = (float)(int)Block;
  result = (uint64_t)sub_4049C0(v23, v24, *v21 - pArg1[1820], v20);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pArg1[2156] = result;
  pArg1[1829] = 500;
  return result;
}



// 子类扩展字段复位（this+8612..8632）
// ------------------------------------------------------------
// 0x59DB80 sub_59DB80
// ------------------------------------------------------------
int /*thiscall*/ sub_59DB80(int this)
{
  *(uint8_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint32_t *)(this + 8624) = 0;
  *(uint32_t *)(this + 8628) = 0xFFFF;
  *(uint32_t *)(this + 8632) = 0;
  return 0;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59DBB0 sub_59DBB0
// ------------------------------------------------------------
int /*thiscall*/ sub_59DBB0(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  if ( ArgList == 5 )
  {
    if ( rand() % 100 < 50 )
      sub_64BDF0(this, *(uint32_t *)(this + 7256));
  }
  else if ( ArgList == 8 )
  {
    *(uint8_t *)(this + 8612) = 0;
  }
  return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
}



// 子类扩展字段复位（77L）
// ------------------------------------------------------------
// 0x59DC10 sub_59DC10
// ------------------------------------------------------------
char /*thiscall*/ sub_59DC10(int this)
{
  int fld_21A8; // eax
  int pThis_21C0; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) == 0
    || *(uint32_t *)(this + 6556) != 8
    || *(uint8_t *)(this + 8612) != 0
    || *(int *)(*(uint32_t *)(this + 120) + 148) <= 2 )
  {
    return sub_4E1780((uint32_t *)this);
  }
  if ( sub_41A5E0(this + 7028) == 0 )
  {
    fld_21A8 = *(uint32_t *)(this + 8616);
LABEL_9:
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
      this,
      *(uint32_t *)(this + 8628),
      *(uint32_t *)(this + 8632),
      fld_21A8,
      0,
      20,
      0,
      60,
      4,
      0,
      0,
      0);
    goto LABEL_10;
  }
  if ( sub_41A5E0(this + 7028) == 1 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
      this,
      *(uint32_t *)(this + 8628),
      *(uint32_t *)(this + 8632),
      *(uint32_t *)(this + 8616),
      0,
      20,
      0,
      60,
      4,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 580))(
      this,
      *(uint32_t *)(this + 8628),
      *(uint32_t *)(this + 8632),
      *(uint32_t *)(this + 8620),
      0,
      20,
      0,
      60,
      4,
      0,
      0,
      0);
    fld_21A8 = *(uint32_t *)(this + 8624);
    goto LABEL_9;
  }
LABEL_10:
  if ( *(uint32_t *)(this + 8660) < 0x10u )
    pThis_21C0 = this + 8640;
  else
    pThis_21C0 = *(uint32_t *)(this + 8640);
  (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, pThis_21C0, -1, 0, 0);
  *(uint8_t *)(this + 8612) = 1;
  return sub_4E1780((uint32_t *)this);
}



// 指挥 AI：GOBLIN_COMMAND（RTTI cast, 67L）
// ------------------------------------------------------------
// 0x59DD40 sub_59DD40
// ------------------------------------------------------------
int /*thiscall*/ sub_59DD40(uint32_t *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // edi
  int v11; // ebx
  int v12; // eax
  int fld_e1813; // eax
  int v14; // [esp+0h] [ebp-10h]
  unsigned int v15; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
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
                &CNGoblinMountainGab `RTTI Type Descriptor',
                0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813), 0);
          sub_49C620(7, fld_e1813, v14);
          sub_4D82D0(0, 0);
          v14 = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*this + 212))(this, "GOBLIN_COMMAND", -1, 0);
        }
      }
      i = v15;
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59DE50 sub_59DE50
// ------------------------------------------------------------
int /*thiscall*/ sub_59DE50(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int v5; // edi
  int v6; // edx
  int v7; // [esp+Ch] [ebp+8h]

  if ( nArg2 != 0 )
  {
    result = nArg2 - 1;
    if ( nArg2 == 1 )
      *(float *)(*(this + 1905) + 36) = *(float *)(*(this + 1905) + 36) * 0.83333331;
  }
  else
  {
    *(float *)(*(this + 1905) + 4) = *(float *)(*(this + 1905) + 4) * 0.83333331;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;
    *(float *)&v7 = COERCE_FLOAT(sub_41A5E0(v5)) - 0.2;
    sub_41A590(v5, v6, v7);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// 狂气光环 AI：vt+212 播报 AURA_FURY（97L；狂暴化演出, 与 0x593840 薇诺版同族）
// ------------------------------------------------------------
// 0x59DEE0 sub_59DEE0
// ------------------------------------------------------------
int /*thiscall*/ sub_59DEE0(char *this, void *Block, int nArg3)
{
  char *pThis_1D73; // ecx
  int result; // eax
  int pThis_771; // eax
  double v7; // st7
  unsigned int pThis_2A0; // edi
  int v9; // edx
  int *v10; // eax
  int v11; // edx
  int nRand; // eax
  uint32_t v13[2]; // [esp+8h] [ebp-14h]
  int v14; // [esp+18h] [ebp-4h]
  int Blocka; // [esp+24h] [ebp+8h]

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
  if ( Block != nullptr )
  {
    if ( Block == (void *)1 )
    {
      pThis_771 = *((uint32_t *)this + 1905);
      v7 = *(float *)(pThis_771 + 36);
      result = pThis_771 + 32;
      *(float *)(result + 4) = v7 * 1.2;
      *((uint32_t *)this + 1897) = 1;
      *((uint32_t *)this + 1893) = 2;
    }
    else
    {
      result = (int)Block - 2;
      if ( Block == (void *)2 )
      {
        *((uint32_t *)this + 1897) = 1;
        *((uint32_t *)this + 1893) = 2;
      }
    }
  }
  else
  {
    *(float *)(*((uint32_t *)this + 1905) + 4) = *(float *)(*((uint32_t *)this + 1905) + 4) * 1.2;
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;
    *(float *)&Blocka = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.2;
    sub_41A590(pThis_2A0, v9, Blocka);
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    if ( nArg3 == 0 )
    {
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 700))(this);
      sub_53F6A0(this);
      v14 = 0;
      if ( operator new(0x8Cu) != nullptr )
        v10 = (int *)sub_64BBF0(150, 3000, 25);
      else
        v10 = nullptr;
      v11 = *v10;
      v14 = -1;
      (*(void (/*thiscall*/ **)(int *, char *, char *, int, uint32_t, uint32_t, int))(v11 + 56))(v10, this, this, 1, 0, 0, -1);
      v13[0] = 2;
      v13[1] = 3;
      nRand = rand() % 2;
      sub_4DB200(24, v13[nRand]);
      return (*(int (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "AURA_FURY",
               -1,
               0,
               0);
    }
  }
  return result;
}



// AI 相位辅助（62L）
// ------------------------------------------------------------
// 0x59E0F0 sub_59E0F0
// ------------------------------------------------------------
int /*thiscall*/ sub_59E0F0(int *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int fld_e29; // edi
  int fld_e1813; // ebx
  int v7; // edi

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
    case 1:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
      if ( rand() % 100 < 3 )
        return sub_59DD40(this);
      if ( rand() % 100 < 5 * ((*(this + 1909) == 0) + 1) )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 2);
      nRand = rand();
      v4 = nRand % 100;
      result = nRand / 100;
      if ( v4 < 10 )
      {
        fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
        fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
        result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e1813);
        if ( result <= 60 )
        {
          result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
          if ( result > 40 )
          {
            v7 = sub_425050(fld_e29) - 40;
            result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
            if ( result < v7 )
              return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 3);
          }
        }
      }
      return result;
    case 13:
      goto LABEL_4;
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 1);
      break;
    default:
      return result;
  }
  return result;
}



// ============================================================
// 【分区 13】哥布林系·卢佩特三向喷吐（Lupete）（0x59E230-0x59E6F0）
// 证据：LupetePants/Shoulder/Foot.equ 三件外观 + FireMissileGero{Center,Left,Right}.ptl
//       三向喷吐粒子（0x59E230）

// 卢佩特装载：R_GOBLIN_* 语音 + Lupete{Pants,Shoulder,Foot}.equ +
//   FireMissileGero{Center,Left,Right}.ptl 三向喷吐粒子（123L）
// ------------------------------------------------------------
// 0x59E230 sub_59E230
// ------------------------------------------------------------
int /*thiscall*/ sub_59E230(uint32_t *this)
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
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int fld_e1821; // edi
  uint32_t *v24; // eax
  uint64_t fld_e1820; // rax
  int fld_e18202; // edi
  uint32_t *v27; // eax
  int result; // eax
  float v29; // [esp+48h] [ebp-30h]
  float v30; // [esp+4Ch] [ebp-2Ch]
  void *Block; // [esp+64h] [ebp-14h]
  int v32; // [esp+68h] [ebp-10h]

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  pMem = (char *)operator new(0x544u);
  if ( pMem != nullptr )
    v3 = sub_4BA9E0(pMem, "Monster/Goblin/acc3-2.equ", 0);
  else
    v3 = nullptr;
  pObj = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v3);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_4BA9E0(pMem2, "Monster/Goblin/acc4-2.equ", 0);
  else
    v6 = nullptr;
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v6);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 4))(pObj2, 1);
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    v9 = sub_4BA9E0(pMem3, "Monster/Goblin/Hcc2-2.equ", 0);
  else
    v9 = nullptr;
  pObj4 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v9);
  if ( pObj4 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 4))(pObj4, 1);
  pMem4 = (char *)operator new(0x544u);
  if ( pMem4 != nullptr )
    v12 = sub_4BA9E0(pMem4, "Monster/Goblin/LupetePants.equ", 0);
  else
    v12 = nullptr;
  pObj3 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v12);
  if ( pObj3 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 4))(pObj3, 1);
  pMem5 = (char *)operator new(0x544u);
  if ( pMem5 != nullptr )
    v15 = sub_4BA9E0(pMem5, "Monster/Goblin/LupeteShoulder.equ", 0);
  else
    v15 = nullptr;
  pObj5 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v15);
  if ( pObj5 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 4))(pObj5, 1);
  pMem6 = (char *)operator new(0x544u);
  if ( pMem6 != nullptr )
    v18 = sub_4BA9E0(pMem6, "Monster/Goblin/LupeteFoot.equ", 0);
  else
    v18 = nullptr;
  pObj6 = (*(int (/*thiscall*/ **)(uint32_t *, char *))(*this + 784))(this, v18);
  if ( pObj6 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 4))(pObj6, 1);
  *(this + 2154) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Common/Particle/FireMissileGeroCenter.ptl");
  *(this + 2155) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Common/Particle/FireMissileGeroLeft.ptl");
  v20 = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
          dword_8F84E4,
          "PassiveObject/Common/Particle/FireMissileGeroRight.ptl");
  v21 = *this;
  *(this + 2156) = v20;
  *(this + 2157) = 30049;
  Block = (void *)(*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v21 + 384))(this, 0);
  v22 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  fld_e1821 = *(this + 1821) - *(this + 1820);
  v32 = v22;
  v24 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v30 = (float)v32;
  v29 = (float)(int)Block;
  fld_e1820 = (uint64_t)sub_4049C0(v29, v30, *v24 - *(this + 1820), fld_e1821);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  fld_e18202 = fld_e1820;
  LODWORD(fld_e1820) = *this;
  *(this + 2158) = fld_e18202;
  v27 = (uint32_t *)(*(int (/*fastcall*/ **)(uint32_t *, uint32_t, int))(fld_e1820 + 672))(this, HIDWORD(fld_e1820), 3);
  result = off_77F3FC((char *)&byte_72E098, *v27, fld_e18202);
  *(this + 1829) = 500;
  return result;
}


// 子类扩展字段复位（this+8612..8620）
// ------------------------------------------------------------
// 0x59E550 sub_59E550
// ------------------------------------------------------------
int /*thiscall*/ sub_59E550(int this)
{
  *(uint8_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0;
  return 0;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59E570 sub_59E570
// ------------------------------------------------------------
char /*thiscall*/ sub_59E570(uint8_t *this)
{
  if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 308))(this) != 0
    && *((uint32_t *)this + 1639) == 8
    && sub_41A5E0((unsigned int)(this + 7028)) == 0
    && *(this + 8612) == 0
    && *(int *)(*((uint32_t *)this + 30) + 148) > 2 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1312))(this);
    *(this + 8612) = 1;
  }
  return sub_4E1780(this);
}



// AI 字段访问（this+8624）
// ------------------------------------------------------------
// 0x59E5D0 sub_59E5D0
// ------------------------------------------------------------
char /*thiscall*/ sub_59E5D0(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( *(this + 8624) != 0 )
    return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 5;
  else
    return sub_4D9210(nArg2, nArg3, nArg4);
}



// AI 字段访问（this+8624）
// ------------------------------------------------------------
// 0x59E600 sub_59E600
// ------------------------------------------------------------
char /*thiscall*/ sub_59E600(uint8_t *this, int nArg2)
{
  if ( *(this + 8624) != 0 )
    return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 5;
  else
    return sub_4D9200(nArg2);
}



// AI 相位门（this+8632/8636）
// ------------------------------------------------------------
// 0x59E630 sub_59E630
// ------------------------------------------------------------
int /*thiscall*/ sub_59E630(int this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
  if ( result == 0 )
  {
    result = *(uint8_t *)(this + 8636);
    if ( (uint8_t)result == 0 )
    {
      result = *(uint32_t *)(this + 8632);
      if ( result != 0 )
      {
        nRand = rand();
        v4 = nRand % 100;
        result = nRand / 100;
        if ( v4 < 5 )
        {
          result = sub_4E7F30((uint32_t *)this, 50, 30, 0);
          if ( result != 0 )
          {
            result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
            if ( (uint8_t)result != 0
              && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) == 60
               || *(uint32_t *)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this)) == 61) )
            {
              result = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(
                         this,
                         14,
                         0,
                         0,
                         0);
              *(uint8_t *)(this + 8636) = 1;
            }
          }
        }
      }
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59E6C0 sub_59E6C0
// ------------------------------------------------------------
int /*thiscall*/ sub_59E6C0(uint32_t *this, int nArg2)
{
  int result; // eax

  sub_4D9170(nArg2);
  result = *(this + 2158);
  if ( result != 0 && nArg2 == result )
    *(this + 2158) = 0;
  return result;
}



// ============================================================
// 【分区 14】哥布林系·冰导弹与手里剑兵（0x59E6F0-0x59F150）
// 证据：PassiveObject/Common/Particle/IceMissile.ptl、Particle/Suriken.ptl +
//       THROW_SHURIKEN 手里剑（0x59E950-0x59EC60 四连函数）

// 冰导弹技能：引用 PassiveObject/Common/Particle/IceMissile.ptl
// ------------------------------------------------------------
// 0x59E6F0 sub_59E6F0
// ------------------------------------------------------------
int /*thiscall*/ sub_59E6F0(uint32_t *this)
{
  int result; // eax

  if ( *(this + 2154) == 0 )
    *(this + 2154) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                       dword_8F84E4,
                       "PassiveObject/Common/Particle/IceMissile.ptl");
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
             this,
             30058,
             *(this + 2155),
             *(this + 2154),
             0,
             20,
             0,
             60,
             4,
             0,
             0,
             0);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59E750 sub_59E750
// ------------------------------------------------------------
int /*thiscall*/ sub_59E750(void *this, void *pArg2)
{
  int result; // eax

  result = sub_4D9170(pArg2);
  if ( this == pArg2 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 216))(this, 3510);
  return result;
}



// 瞄准炸弹 AI：Particle/AimingBomb.ptl（98L）
// ------------------------------------------------------------
// 0x59E790 sub_59E790
// ------------------------------------------------------------
int /*usercall*/ sub_59E790@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)
{
  int result; // eax
  uint64_t v5; // rax
  int v6; // esi
  uint64_t v7; // rax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // edx
  bool v13; // zf
  int v14; // esi
  uint32_t v15[26]; // [esp+8h] [ebp-68h] BYREF

  v15[25] = dword_796E50;
  sub_423A20(v15);
  result = pArg1[1813];
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 1244))(pArg1, pArg1[1813]);
    if ( (uint8_t)result != 0 )
    {
      qmemcpy(
        v15,
        (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int, int))(*pArg1 + 588))(
                        pArg1,
                        "Particle/AimingBomb.ptl",
                        nArg2,
                        nArg3),
        0x62u);
      v5 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v15[7] + 3)) / (double)v15[17] * 1000.0);
      v6 = 2 * v5;
      v7 = (uint64_t)((double (/*fastcall*/ *)(uint32_t *, uint32_t, uint32_t, uint32_t))*(uint32_t *)(*pArg1 + 164))(
                               pArg1,
                               HIDWORD(v5),
                               pArg1[1813],
                               0);
      HIDWORD(v7) = *pArg1;
      v15[18] = v7;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(HIDWORD(v7) + 8))(pArg1, pArg1[1813], 0);
      v9 = *pArg1;
      *(uint32_t *)((char *)&v15[3] + 3) = 1000 * v8 / v6;
      v10 = 1000 * (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(v9 + 8))(pArg1, pArg1[1813], 0) / v6;
      *(uint32_t *)((char *)&v15[4] + 3) = v10;
      if ( *(uint32_t *)((char *)&v15[3] + 3) > 180 )
        *(uint32_t *)((char *)&v15[3] + 3) = 180;
      if ( v10 > 180 )
        *(uint32_t *)((char *)&v15[4] + 3) = 180;
      v11 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*pArg1 + 8))(pArg1, pArg1[1813], 0);
      v12 = *pArg1;
      *(uint32_t *)((char *)&v15[7] + 3) = v11 > 200 ? 400 : 200;
      result = (*(int (/*thiscall*/ **)(uint32_t *))(v12 + 308))(pArg1);
      if ( (uint8_t)result != 0 )
      {
        if ( rand() % 100 < 10 )
        {
          v13 = pArg1[2160] == 0;
          *(uint32_t *)((char *)&v15[3] + 3) = 0;
          *(uint32_t *)((char *)&v15[4] + 3) = 0;
          *(uint32_t *)((char *)&v15[5] + 3) = 300;
          *(uint32_t *)((char *)&v15[7] + 3) = 50;
          if ( v13 )
          {
            pArg1[2160] = 1;
            *((uint8_t *)pArg1 + 8657) = 0;
            *((uint8_t *)pArg1 + 8658) = 0;
            sub_698F90((int)(pArg1 + 2161), 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
            v14 = pArg1[81];
            pArg1[81] = 0;
            sub_4D8600(0, 0);
            pArg1[81] = v14;
          }
        }
        return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
                 pArg1,
                 30006,
                 pArg1[2155],
                 v15,
                 0,
                 20,
                 0,
                 60,
                 1,
                 0,
                 0,
                 0);
      }
    }
  }
  return result;
}



// 手里剑技能：Particle/Suriken.ptl + THROW_SHURIKEN 播报（63L；8657/8658 相位）
// ------------------------------------------------------------
// 0x59E950 sub_59E950
// ------------------------------------------------------------
int /*thiscall*/ sub_59E950(int *this)
{
  int result; // eax
  int nRand; // eax
  bool nRand2; // bl
  int fld_e1813; // eax
  int fld_e81; // edi

  result = *(this + 1813);
  if ( result != 0 )
  {
    if ( *(this + 2154) == 0 )
      *(this + 2154) = (*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/Suriken.ptl");
    sub_432FA0();
    nRand = rand();
    *(uint32_t *)(*(this + 2154) + 31) = dword_72E1D8[2 * (nRand % 3)];
    *(uint32_t *)(*(this + 2154) + 35) = dword_72E1DC[2 * (nRand % 3)];
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    {
      nRand2 = rand() % 100 < 10;
      fld_e1813 = -1;
      if ( !nRand2 )
        fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 52))(*(this + 1813));
      (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        30080,
        fld_e1813,
        0,
        0,
        0,
        0,
        32,
        4,
        0,
        0,
        0);
      if ( nRand2 && *(this + 2160) == 0 )
      {
        *(this + 2160) = 1;
        *((uint8_t *)this + 8657) = 0;
        *((uint8_t *)this + 8658) = 0;
        sub_698F90((int)(this + 2161), 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        fld_e81 = *(this + 81);
        *(this + 81) = 0;
        sub_4D8600(0, 0);
        *(this + 81) = fld_e81;
      }
    }
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "THROW_SHURIKEN",
             -1,
             0,
             0);
  }
  return result;
}



// 手里剑结算：Suriken.ptl 命中处理（this+200 主状态门, 61L）
// ------------------------------------------------------------
// 0x59EA80 sub_59EA80
// ------------------------------------------------------------
int /*thiscall*/ sub_59EA80(uint32_t *this)
{
  int v2; // eax
  int i; // esi
  int v4; // eax
  int result; // eax
  int fld_e2170; // ecx
  uint32_t v7[6]; // [esp+8h] [ebp-80h]
  uint32_t v8[26]; // [esp+20h] [ebp-68h] BYREF

  v8[25] = dword_796E50;
  v2 = *this;
  v7[0] = 3;
  v7[1] = 5;
  v7[2] = 7;
  v7[3] = 9;
  v7[4] = 11;
  v7[5] = 13;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(v2 + 200))(this) + 148) == v7[*(this + 2170)]
    && *((uint8_t *)this + 8676) == 0 )
  {
    qmemcpy(
      v8,
      (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/Suriken.ptl"),
      0x62u);
    for ( i = 0; i < 4; ++i )
    {
      v4 = *this;
      v8[18] = 15 * (i + 4 * *(this + 2170));
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
        this,
        30079,
        *(this + 2155),
        v8,
        0,
        20,
        0,
        60,
        4,
        0,
        0,
        0);
    }
    *((uint8_t *)this + 8676) = 1;
    *((uint8_t *)this + 8612) = 1;
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  fld_e2170 = *(this + 2170);
  if ( *(uint32_t *)(result + 148) == v7[fld_e2170] + 1 )
  {
    *((uint8_t *)this + 8676) = 0;
    *(this + 2170) = fld_e2170 + 1;
  }
  return result;
}



// 手里剑技能变体：Suriken.ptl + THROW_SHURIKEN
// ------------------------------------------------------------
// 0x59EB90 sub_59EB90
// ------------------------------------------------------------
int /*thiscall*/ sub_59EB90(uint32_t *this)
{
  int i; // esi
  int v3; // edx
  int result; // eax
  uint32_t v5[4]; // [esp+Ch] [ebp-78h]
  uint32_t v6[26]; // [esp+1Ch] [ebp-68h] BYREF

  v6[25] = dword_796E50;
  qmemcpy(
    v6,
    (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/Suriken.ptl"),
    0x62u);
  v5[0] = 0;
  v5[1] = 90;
  v5[2] = 180;
  v5[3] = 270;
  for ( i = 0; i < 4; ++i )
  {
    v3 = *this;
    v6[18] = v5[i];
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v3 + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        30079,
        *(this + 2155),
        v6,
        0,
        20,
        0,
        60,
        4,
        0,
        0,
        0);
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "THROW_SHURIKEN",
             -1,
             0,
             0);
  *(this + 2168) = -1;
  return result;
}



// 手里剑技能变体：Suriken.ptl + THROW_SHURIKEN
// ------------------------------------------------------------
// 0x59EC60 sub_59EC60
// ------------------------------------------------------------
int /*thiscall*/ sub_59EC60(uint32_t *this)
{
  int i; // esi
  int v3; // edx
  int result; // eax
  uint32_t v5[4]; // [esp+Ch] [ebp-78h]
  uint32_t v6[26]; // [esp+1Ch] [ebp-68h] BYREF

  v6[25] = dword_796E50;
  qmemcpy(
    v6,
    (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/Suriken.ptl"),
    0x62u);
  v5[0] = 45;
  v5[1] = 135;
  v5[2] = 225;
  v5[3] = 315;
  for ( i = 0; i < 4; ++i )
  {
    v3 = *this;
    v6[18] = v5[i];
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v3 + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        30079,
        *(this + 2155),
        v6,
        0,
        20,
        0,
        60,
        4,
        0,
        0,
        0);
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "THROW_SHURIKEN",
             -1,
             0,
             0);
  *(this + 2168) = -1;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59ED30 sub_59ED30
// ------------------------------------------------------------
int /*thiscall*/ sub_59ED30(int *this)
{
  int fld_e2176; // ecx
  int i; // esi
  int v4; // edx
  int result; // eax
  uint32_t v6[4]; // [esp+Ch] [ebp-78h]
  uint32_t v7[26]; // [esp+1Ch] [ebp-68h] BYREF

  fld_e2176 = *(this + 2176);
  v7[25] = dword_796E50;
  qmemcpy(v7, (const void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2176 + 28))(fld_e2176), 0x62u);
  v6[0] = 310;
  v6[1] = 340;
  v6[2] = 20;
  v6[3] = 50;
  for ( i = 0; i < 4; ++i )
  {
    v4 = *this;
    v7[18] = v6[i];
    result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
               this,
               30065,
               *(this + 2155),
               v7,
               0,
               20,
               0,
               50,
               4,
               0,
               0,
               0);
  }
  *(this + 2168) = -1;
  return result;
}



// AI 相位门（this+8612/8672）
// ------------------------------------------------------------
// 0x59EDD0 sub_59EDD0
// ------------------------------------------------------------
int /*thiscall*/ sub_59EDD0(int this)
{
  int nRand; // eax
  int v3; // eax
  int result; // eax

  nRand = rand() % 3;
  *(uint32_t *)(this + 8672) = nRand;
  if ( nRand != 0 )
  {
    v3 = nRand - 1;
    if ( v3 == 0 )
    {
      result = sub_59EC60((uint32_t *)this);
      *(uint8_t *)(this + 8612) = 1;
      return result;
    }
    result = v3 - 1;
    if ( result == 0 )
    {
      result = sub_59ED30((int *)this);
      *(uint8_t *)(this + 8612) = 1;
      return result;
    }
  }
  else
  {
    result = sub_59EB90((uint32_t *)this);
  }
  *(uint8_t *)(this + 8612) = 1;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59EE30 sub_59EE30
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_59EE30(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; result += 3 )
  {
    if ( result != nullptr )
    {
      *result = *uArg12;
      result[1] = uArg12[1];
      result[2] = uArg12[2];
    }
    uArg12 += 3;
  }
  return result;
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59EE70 sub_59EE70
// ------------------------------------------------------------
int /*thiscall*/ sub_59EE70(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  if ( ArgList == 5 )
  {
    if ( rand() % 100 < 50 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      sub_64BDF0(this, *(this + 1814));
  }
  else if ( ArgList == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 0 )
  {
    *((uint8_t *)this + 8612) = 0;
  }
  return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59EEF0 sub_59EEF0
// ------------------------------------------------------------
int /*thiscall*/ sub_59EEF0(uint32_t *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  result = sub_59EE70(this, ArgList, fArg3, nArg4, nArg5);
  if ( *(this + 1639) == 5 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 3510);
  return result;
}



// 指挥 AI：GOBLIN_COMMAND（RTTI cast, 67L）
// ------------------------------------------------------------
// 0x59EF30 sub_59EF30
// ------------------------------------------------------------
int /*thiscall*/ sub_59EF30(uint32_t *this)
{
  unsigned int i; // edi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // edi
  int v11; // ebx
  int v12; // eax
  int fld_e1813; // eax
  int v14; // [esp+0h] [ebp-10h]
  unsigned int v15; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v15 = i;
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
                &CNGoblinIslandGab `RTTI Type Descriptor',
                0);
        if ( v12 != 0 && (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 156))(this, v12) <= 300 )
        {
          fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813), 0);
          sub_49C620(7, fld_e1813, v14);
          sub_4D82D0(0, 0);
          v14 = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t))(*this + 212))(this, "GOBLIN_COMMAND", -1, 0);
        }
      }
      i = v15;
    }
  }
  return result;
}



// 子类扩展字段复位（this+8624..8632）
// ------------------------------------------------------------
// 0x59F040 sub_59F040
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_59F040(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int fld_21B8; // eax
  uint32_t *result; // eax
  int fld_21B82; // ecx

  sub_59EE70((uint32_t *)this, ArgList, fArg3, nArg4, nArg5);
  if ( ArgList == 14 )
  {
    sub_4926A0(*(uint32_t *)(this + 8628));
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(this + 8628));
    *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) + 40) = 0;
  }
  fld_21B8 = *(uint32_t *)(this + 8632);
  if ( (fld_21B8 != 0 && *(uint8_t *)(fld_21B8 + 992) != 0
     || (result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this)) == (uint32_t *)14)
    && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) == 60
     || *(result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this)) == 61) )
  {
    result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( result != (uint32_t *)9 )
    {
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 736))(this);
      if ( (int)result > 0 )
      {
        fld_21B82 = *(uint32_t *)(this + 8632);
        *(uint32_t *)(this + 6556) = 4;
        *(uint8_t *)(this + 8624) = 0;
        if ( fld_21B82 != 0 )
          sub_621200();
        *(uint32_t *)(this + 324) = 0;
        *(uint32_t *)(this + 6664) = -1500;
        sub_495890(2, 0);
        result = *(uint32_t **)(this + 6180);
        if ( result == nullptr )
        {
          result = *(uint32_t **)(this + 6216);
          *(uint32_t *)(this + 6180) = *result;
        }
      }
    }
  }
  return result;
}



// ============================================================
// 【分区 15】天空之城岛哥布林（IslandGoblin / BullsEye）（0x59F150-0x5A0000）
// 证据：Monster/Goblin/Animation_IslandGoblin/ChillingAura 冰盾、B_BULLSEYE_01 登场曲、
//       R_GOBLIN_* 语音（0x59FC80）、0x59F150 大型主状态机（+200 主状态门）

// 岛哥布林大型主状态机（118L）：this+200 主状态 + sub_699000 时钟门 +
//   this+8300/8624..8668 多相位字段【推断：待机/追击/投弹三相】
// ------------------------------------------------------------
// 0x59F150 sub_59F150
// ------------------------------------------------------------
char /*thiscall*/ sub_59F150(int this)
{
  int v2; // edi
  int fld_21B8; // eax
  int pThis_80; // eax
  int v5; // eax
  int pThis_78; // eax
  int pThis_782; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  int *pThis_206C; // ebx
  int fld_21DC; // edi
  int fld_144; // edi
  int v15; // [esp-8h] [ebp-1Ch]
  int v16; // [esp+Ch] [ebp-8h] BYREF
  int pThis_7822; // [esp+10h] [ebp-4h] BYREF

  sub_59E570();
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )
  {
    v2 = 0;
    if ( *(uint32_t *)(this + 8632) != 0 && *(uint8_t *)(this + 8624) == 1 )
    {
      *(uint8_t *)(this + 8624) = 0;
      sub_621200();
      *(uint32_t *)(this + 324) = 0;
      *(uint32_t *)(this + 6664) = -1500;
      sub_495890((int *)this, 2, 0);
    }
  }
  else
  {
    v2 = 0;
  }
  fld_21B8 = *(uint32_t *)(this + 8632);
  if ( fld_21B8 != 0
    && *(uint8_t *)(fld_21B8 + 992) != 0
    && *(uint8_t *)(this + 8636) == 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0
    && (*(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) == 60
     || *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 340))(this) == 61) )
  {
    (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, 0, 0, 0);
    *(uint8_t *)(this + 8636) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 && *(uint8_t *)(this + 8624) == 0 )
  {
    if ( *(uint32_t *)(this + 6180) == 0 )
      *(uint32_t *)(this + 6180) = *(uint32_t *)(*(uint32_t *)(this + 6216) + 4);
    *(uint32_t *)(this + 7252) = 0;
    *(uint32_t *)(this + 6556) = 4;
    *(uint32_t *)(this + 6664) = -1500;
    sub_495890((int *)this, 2, 0);
  }
  pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
  if ( pThis_80 <= 0 && *(uint32_t *)(this + 6664) == -1500 )
  {
    v5 = *(uint32_t *)this;
    *(uint32_t *)(this + 6556) = 0;
    *(uint32_t *)(this + 6664) = 0;
    *(uint8_t *)(this + 6740) = 1;
    v15 = (*(int (/*thiscall*/ **)(int))(v5 + 124))(this);
    pThis_78 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
    pThis_80 = sub_58AD30(pThis_78, v15, 0);
    if ( pThis_80 == 0 )
    {
      pThis_782 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
      v8 = *(uint32_t *)this;
      pThis_7822 = pThis_782;
      v9 = (*(int (/*thiscall*/ **)(int))(v8 + 124))(this);
      v10 = *(uint32_t *)this;
      v16 = v9;
      (*(void (/*thiscall*/ **)(int, int *, int *, int, int, int, int, int))(v10 + 140))(
        this,
        &pThis_7822,
        &v16,
        pThis_7822,
        v9,
        240,
        1,
        1);
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 108))(this, pThis_7822, v16, 0);
      pThis_206C = (int *)(this + 8300);
      do
      {
        pThis_80 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 116))(this, v2);
        *pThis_206C = pThis_80;
        ++v2;
        ++pThis_206C;
      }
      while ( v2 < 3 );
    }
  }
  if ( *(uint32_t *)(this + 8640) != 0 )
  {
    fld_21DC = *(uint32_t *)(this + 8668);
    pThis_80 = sub_699000(this + 8644);  // 【clock_now(clk)】
    if ( pThis_80 >= fld_21DC )
    {
      fld_144 = *(uint32_t *)(this + 324);
      *(uint32_t *)(this + 8640) = 0;
      *(uint32_t *)(this + 324) = 0;
      sub_4D83E0((int *)this, 0, 0);
      *(uint32_t *)(this + 324) = fld_144;
      *(uint8_t *)(this + 8657) = 0;
      *(uint8_t *)(this + 8658) = 0;
      LOBYTE(pThis_80) = sub_698F90(this + 8644, 1500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  return pThis_80;
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x59F390 sub_59F390
// ------------------------------------------------------------
int /*thiscall*/ sub_59F390(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  unsigned int v5; // edx
  int i; // edi
  int fld_e1905; // ecx
  int v8; // eax
  double v9; // st7
  unsigned int v10; // edi
  int v11; // edx
  int v12; // [esp+Ch] [ebp+8h]

  result = nArg2;
  if ( nArg2 == 0 )
  {
    v5 = 0;
    for ( i = 0; ; i += 32 )
    {
      fld_e1905 = *(this + 1905);
      if ( fld_e1905 == 0 || v5 >= (*(this + 1906) - fld_e1905) >> 5 )
        break;
      v8 = i + fld_e1905;
      v9 = *(float *)(fld_e1905 + i + 4) * 0.83333331;
      ++v5;
      *(float *)(v8 + 4) = v9;
    }
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 672))(this, 0) + 858;
    *(float *)&v12 = COERCE_FLOAT(sub_41A5E0(v10)) - 0.2;
    sub_41A590(v10, v11, v12);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 676))(this, 0);
  }
  return result;
}



// 冰盾技能（岛哥布林版）：sub_64B0F0 发射 Monster/Goblin/Animation_IslandGoblin/
//   ChillingAura 光环粒子 + vt+212 SHIELD_ICE + WINDSHIELD_LOOP（102L）
// ------------------------------------------------------------
// 0x59F420 sub_59F420
// ------------------------------------------------------------
int /*thiscall*/ sub_59F420(char *this, void *Block, int nArg3)
{
  char *pThis_1D73; // ecx
  int result; // eax
  unsigned int v6; // edx
  int i; // edi
  int pThis_771; // ecx
  int v9; // eax
  double v10; // st7
  unsigned int pThis_2A0; // edi
  int v12; // edx
  int pObj; // eax
  int Blocka; // [esp+20h] [ebp+8h]

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
  if ( Block != nullptr )
  {
    result = (int)Block - 1;
    if ( Block == (void *)1 || (result = (int)Block - 2, Block == (void *)2) )
    {
      *(this + 7534) = 1;
      *((uint32_t *)this + 1893) = 2;
    }
  }
  else
  {
    v6 = 0;
    for ( i = 0; ; i += 32 )
    {
      pThis_771 = *((uint32_t *)this + 1905);
      if ( pThis_771 == 0 || v6 >= (*((uint32_t *)this + 1906) - pThis_771) >> 5 )
        break;
      v9 = i + pThis_771;
      v10 = *(float *)(pThis_771 + i + 4) * 1.2;
      ++v6;
      *(float *)(v9 + 4) = v10;
    }
    pThis_2A0 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 672))(this, 0) + 858;
    *(float *)&Blocka = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) + 0.2;
    sub_41A590(pThis_2A0, v12, Blocka);
    result = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    if ( dword_9A05D4 <= 2 )
    {
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 700))(this);
      sub_53F6A0(this);
      if ( operator new(0x8Cu) != nullptr )
        pObj = sub_64B0F0(0, 0x40000000, 7, "Monster/Goblin/Animation_IslandGoblin/ChillingAura");
      else
        pObj = 0;
      (*(void (/*thiscall*/ **)(int, char *, char *, int, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
        pObj,
        this,
        this,
        1,
        0,
        0,
        -1);
      sub_4DB200(24, 2);
      (*(void (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "SHIELD_ICE",
        -1,
        0,
        0);
      (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 216))(this, 3510);
      return (*(int (/*thiscall*/ **)(char *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "WINDSHIELD_LOOP",
               3510,
               0,
               0);
    }
  }
  return result;
}



// 硬直/相位字段（this+208/+8612/+8624）
// ------------------------------------------------------------
// 0x59F620 sub_59F620
// ------------------------------------------------------------
char /*thiscall*/ sub_59F620(int *this)
{
  int fld_e1639; // eax
  int fld_e1554; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    fld_e1639 = *(this + 1639);
    if ( fld_e1639 != 0 )
    {
      if ( fld_e1639 == 8
        && sub_41A5E0((unsigned int)(this + 1757)) == 0
        && *((uint8_t *)this + 8612) == 0
        && *(int *)(*(this + 30) + 148) > 2 )
      {
        (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 1554));
        (*(void (/*thiscall*/ **)(int *))(*this + 1312))(this);
        *((uint8_t *)this + 8612) = 1;
      }
    }
    else if ( *((uint8_t *)this + 8624) == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(this + 1540));
    }
  }
  if ( *(this + 1639) != 8 )
  {
    fld_e1554 = *(uint32_t *)*(this + 1554);
    if ( fld_e1554 != 0 )
      (*(void (/*thiscall*/ **)(int *, int))(*this + 208))(this, fld_e1554);
  }
  return sub_59F150(this);
}



// AI 字段访问（this+8612）
// ------------------------------------------------------------
// 0x59F6D0 sub_59F6D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_59F6D0(int **this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  if ( ArgList == 5 )
  {
    if ( rand() % 100 < 50 && ((uint8_t (/*thiscall*/ *)(int **))(*this)[77])(this) != 0 )
      sub_64BDF0(this, *(this + 1814));
  }
  else if ( ArgList == 8 && **(uint32_t **)(LODWORD(fArg3) + 4) == 0 )
  {
    sub_4926A0(**(this + 1554));
    ((void (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      100,
      **(this + 1554),
      0,
      0,
      0,
      0);
    *((uint8_t *)this + 8612) = 0;
  }
  return sub_59F040((int)this, ArgList, fArg3, nArg4, nArg5);
}



// 硬直/相位字段（this+208/+8612）
// ------------------------------------------------------------
// 0x59F770 sub_59F770
// ------------------------------------------------------------
char /*thiscall*/ sub_59F770(int this)
{
  int fld_1848; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) == 0 )
    goto LABEL_7;
  if ( *(uint32_t *)(this + 6556) == 8 )
  {
    if ( sub_41A5E0(this + 7028) == 0 && *(uint8_t *)(this + 8612) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) > 2 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, **(uint32_t **)(this + 6216));
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);
      *(uint8_t *)(this + 8612) = 1;
    }
LABEL_7:
    if ( *(uint32_t *)(this + 6556) == 8 )
      return sub_59F150((int *)this);
  }
  fld_1848 = **(uint32_t **)(this + 6216);
  if ( fld_1848 != 0 )
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 208))(this, fld_1848);
  return sub_59F150((int *)this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x59F800 sub_59F800
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_59F800(unsigned int *this, int nArg2)
{
  int fld_e2158; // eax
  int v4; // ebx
  unsigned int i; // edi
  unsigned int result; // eax
  int fld_e2172; // eax
  int v8; // edx
  uint32_t *v9; // eax

  sub_4D9170(nArg2);
  fld_e2158 = *(this + 2158);
  v4 = 0;
  if ( fld_e2158 != 0 && nArg2 == fld_e2158 )
    *(this + 2158) = 0;
  for ( i = 0; ; ++i )
  {
    result = *(this + 2172);
    if ( result == 0 )
      break;
    result = (int)(*(this + 2173) - result) / 12;
    if ( i >= result )
      break;
    fld_e2172 = *(this + 2172);
    v8 = *(uint32_t *)(fld_e2172 + v4);
    v9 = (uint32_t *)(v4 + fld_e2172);
    if ( v8 == nArg2 )
      *v9 = 0;
    v4 += 12;
  }
  return result;
}



// AI 字段访问（this+8700）
// ------------------------------------------------------------
// 0x59F880 sub_59F880
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_59F880(int this)
{
  uint8_t *result; // eax

  **(uint8_t **)(this + 7620) = 0;
  *(uint8_t *)(*(uint32_t *)(this + 7620) + 32) = 0;
  result = (uint8_t *)(*(uint32_t *)(this + 7620) + 64);
  *result = 0;
  *(uint32_t *)(this + 8700) = 0;
  return result;
}



// 瞄准炸弹 AI：Particle/AimingBomb.ptl（74L）
// ------------------------------------------------------------
// 0x59F8B0 sub_59F8B0
// ------------------------------------------------------------
int /*thiscall*/ sub_59F8B0(int *this)
{
  uint64_t v2; // rax
  int fld_e2175; // edi
  int v4; // esi
  int fld_e2172; // edi
  uint64_t v6; // rax
  int v7; // eax
  int v8; // eax
  int fld_e21722; // ecx
  int fld_e2155; // ecx
  int v11; // edx
  uint32_t v13[26]; // [esp+10h] [ebp-68h] BYREF

  v13[25] = dword_796E50;
  qmemcpy(
    v13,
    (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(this, "Particle/AimingBomb.ptl"),
    0x62u);
  v2 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v13[7] + 3)) / (double)v13[17] * 1000.0);
  fld_e2175 = *(this + 2175);
  v4 = 2 * v2;
  if ( fld_e2175 >= 0 )
  {
    LODWORD(v2) = *(this + 2172);
    if ( (uint32_t)v2 != 0 )
      LODWORD(v2) = (*(this + 2173) - (int)v2) / 12;
    if ( fld_e2175 < (unsigned int)v2 )
    {
      fld_e2172 = *(uint32_t *)(*(this + 2172) + 12 * fld_e2175);
      if ( fld_e2172 != 0 && (*(uint8_t (/*thiscall*/ **)(int *, int))(*this + 1244))(this, fld_e2172) != 0 )
      {
        v6 = (uint64_t)((double (/*thiscall*/ *)(int *, int, uint32_t))*(uint32_t *)(*this + 164))(this, fld_e2172, 0);
        HIDWORD(v6) = *this;
        v13[18] = v6;
        v7 = (*(int (/*thiscall*/ **)(int *, int, uint32_t))(HIDWORD(v6) + 8))(this, fld_e2172, 0);
        *(uint32_t *)((char *)&v13[3] + 3) = 1000 * v7 / v4;
        v8 = (*(int (/*fastcall*/ **)(int *, int, int, uint32_t))(*this + 8))(this, 1000 * v7 % v4, fld_e2172, 0);
      }
      else
      {
        fld_e21722 = *(this + 2172) + 12 * *(this + 2175);
        v13[18] = *(uint32_t *)(fld_e21722 + 4);
        *(uint32_t *)((char *)&v13[3] + 3) = 1000 * *(uint32_t *)(fld_e21722 + 8) / v4;
        v8 = *(uint32_t *)(fld_e21722 + 8);
      }
      fld_e2155 = *(this + 2155);
      v11 = *this;
      *(uint32_t *)((char *)&v13[4] + 3) = 1000 * v8 / v4;
      LODWORD(v2) = (*(int (/*thiscall*/ **)(int *, int, int, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v11 + 580))(
                      this,
                      30077,
                      fld_e2155,
                      v13,
                      0,
                      20,
                      0,
                      60,
                      1,
                      0,
                      0,
                      0);
      ++*(this + 2175);
    }
  }
  *((uint8_t *)this + 8612) = 1;
  return v2;
}



// AI 相位辅助（76L）
// ------------------------------------------------------------
// 0x59FA10 sub_59FA10
// ------------------------------------------------------------
int /*thiscall*/ sub_59FA10(int *this)
{
  int result; // eax
  int nRand; // eax
  int v4; // et2
  int fld_e29; // edi
  int fld_e1813; // ebx
  int v7; // edi

  sub_4E0120();
  result = *(this + 1787);
  switch ( result )
  {
    case 0:
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
    case 1:
      if ( *(this + 1813) == 0 )
        return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
      result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
      {
        if ( rand() % 100 >= 3 )
        {
          if ( rand() % 100 >= 5 * ((*(this + 1909) == 0) + 1) )
          {
            nRand = rand();
            v4 = nRand % 100;
            result = nRand / 100;
            if ( v4 < 10 )
            {
              fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
              fld_e1813 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 120))(*(this + 1813));
              result = abs32((*(int (/*thiscall*/ **)(int *))(*this + 120))(this) - fld_e1813);
              if ( result <= 60 )
              {
                result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
                if ( result > 40 )
                {
                  v7 = sub_425050(fld_e29) - 40;
                  result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
                  if ( result < v7 )
                    return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 3);
                }
              }
            }
          }
          else
          {
            return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 2);
          }
        }
        else
        {
          return sub_59EF30(this);
        }
      }
      return result;
    case 13:
      goto LABEL_4;
    case 15:
      result = *(this + 1813);
      if ( result != 0 )
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 1);
      break;
    default:
      return result;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59FB70 sub_59FB70
// ------------------------------------------------------------
int /*thiscall*/ sub_59FB70(int *this)
{
  int result; // eax

  sub_59FA10(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
    return sub_59E630((int)this);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x59FB90 sub_59FB90
// ------------------------------------------------------------
int /*thiscall*/ sub_59FB90(int *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
  if ( result != 14 )
  {
    sub_59FA10(this);
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
      sub_59E630((int)this);
    result = *(this + 1787);
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 16);
  }
  return result;
}



// 主状态门（this+200; 8612/8672 相位）
// ------------------------------------------------------------
// 0x59FBE0 sub_59FBE0
// ------------------------------------------------------------
char /*thiscall*/ sub_59FBE0(int this)
{
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
  {
    if ( *(uint32_t *)(this + 8672) == 3 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) != 0 )
    {
      sub_59EA80((uint32_t *)this);
      return sub_59F150((int *)this);
    }
    if ( *(uint32_t *)(this + 6556) == 8 && *(uint8_t *)(this + 8612) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) > 2 )
    {
      if ( sub_41A5E0(this + 7028) == 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1312))(this);
        return sub_59F150((int *)this);
      }
      if ( sub_41A5E0(this + 7028) == 2 )
        sub_59F8B0((int *)this);
    }
  }
  return sub_59F150((int *)this);
}



// 语音注册：R_GOBLIN_TALK/DMG/DIE（岛哥布林三件套, sub_4015C0）
// ------------------------------------------------------------
// 0x59FC80 sub_59FC80
// ------------------------------------------------------------
int /*thiscall*/ sub_59FC80(uint32_t *this)
{
  int result; // eax

  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  sub_4015C0("R_GOBLIN_TALK", 0xDu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DMG", 0xCu);  // 【std::string构造赋值】
  sub_4015C0("R_GOBLIN_DIE", 0xCu);  // 【std::string构造赋值】
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  *(this + 1829) = 500;
  return result;
}



// 登场曲：sub_406D60 写 "B_BULLSEYE_01"（靶眼 BullsEye 曲目槽）
// ------------------------------------------------------------
// 0x59FD00 sub_59FD00
// ------------------------------------------------------------
int /*thiscall*/ sub_59FD00(int *this)
{
  int result; // eax

  sub_59FA10(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
    sub_59E630((int)this);
  result = *(this + 1787);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 16);
    if ( *(this + 1943) == 3 )
      return sub_4015C0("B_BULLSEYE_01", 0xDu);  // 【std::string构造赋值】
  }
  return result;
}



// 相位门（this+8612/8672/8688..8696）
// ------------------------------------------------------------
// 0x59FD50 sub_59FD50
// ------------------------------------------------------------
void /*thiscall*/ sub_59FD50(int this)
{
  **(uint8_t **)(this + 7620) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 7620) + 32) = 1;
  *(uint8_t *)(*(uint32_t *)(this + 7620) + 64) = 1;
  *(uint32_t *)(this + 8672) = -1;
  if ( *(uint32_t *)(this + 8688) != 0 )
    j__free(*(void **)(this + 8688));
  *(uint32_t *)(this + 8688) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint8_t *)(this + 8612) = 0;
}



// 大型 AI（116L；岛哥布林投弹/走位）
// ------------------------------------------------------------
// 0x59FDB0 sub_59FDB0
// ------------------------------------------------------------
int /*thiscall*/ sub_59FDB0(int *this, int pArg2, unsigned int uArg3, int *Block)
{
  int v5; // ecx
  int v6; // edx
  int fld_e1; // ebx
  int result; // eax
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v13; // ecx
  int fld_e27; // eax
  int v15; // ebx
  int fld_e13; // eax
  unsigned int v17; // edi
  void *fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-40h]
  int fld_e25; // [esp-Ch] [ebp-34h]
  unsigned int fld_e24; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  int v27; // [esp+30h] [ebp+8h]
  int v28; // [esp+34h] [ebp+Ch]
  char *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  fld_e1 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_4A30C0();
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 12 >= uArg3 )
      {
        v27 = (int)fld_e23 - 12 * uArg3;
        *(this + 2) = sub_59EE30(v27, fld_e23, fld_e23);
        sub_504450(pArg2, v27, Blockb);
        return sub_5043B0(pArg2, pArg2 + 12 * uArg3, v25);
      }
      else
      {
        sub_59EE30(pArg2, fld_e23, pArg2 + 12 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;
        fld_e25 = *(this + 2);
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return sub_5043B0(pArg2, fld_e26 - 12 * uArg3, v25);
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      fld_e12 = *(this + 1);
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pArg2, Blocka);
      sub_623C10(v28, uArg3, v25);
      sub_59EE30(pArg2, *(this + 2), v28 + 12 * uArg3);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v15];
      *(this + 2) = (int)&Blocka[12 * v17];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}

