// ============================================================
// 【40JP逆向源代码工程】game/po_effects.cpp
// 模块: PassiveObject 通用特效/装备效果 PO（0x51 区）
// 来源: work/dump_miscb.txt  区块: 0x510000-0x520000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 逐行精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 353
// ------------------------------------------------------------
// ★ 本文件已按《21_打击感公式算法速查》P24/P29/P32/P33/P36 与 docs/15 定案锚点升级注释：
//   0x513B40/0x513E00 幸运金币 PO（FortuneCoinGood/Bad.ani、COIN_BOUND/TURN、
//                     Thunderbolt.ani + THUNDER_STRIKE、HP_RECOVERED —— P32 TAG 音效/P33 演播层）
//   0x5140A0 装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs/15 vmt328 UDP type=10）
//   0x5146B0 受击召唤装备 vmt8C（vt+592 召唤链 + P29 盒取位）
//   0x5149F0 DragonicSkin HP 门限状态维持 vmt12C（P24 防篡改读 sub_41C5A0）
//   0x514B80-0x51B9F0 具名装备 PO 族（vmt88 攻击触发 / vmt8C 受击触发 /
//                     vmt90/A4 伤害修正 / vmt12C/13C 周期 tick / vmt130 条件查询）
//   装备加成槽 +1492/+1422/+373 写入走 P24 防篡改写侧（sub_41A590/sub_41C150）
// ------------------------------------------------------------
// 交叉引用（0x51 区巨函数不在本文件，见 src/combat/ 专项文件）：
//   0x510F30 护符/珠子 PO 大调度（CHARM_FIRE/ICE/MOON/SUN_USE 注册，0x510350 元素抗性 PO 的
//            最大用户）→ src/combat/bigfunc_510F30_sub_510F30.cpp
//   0x51BA00 0x51 区尾部巨函数（size=25733）→ src/combat/bigfunc_51BA00_sub_51BA00.cpp
// 术语约定（全文件通用，函数注释不再重复）：
//   vt+212 播 TAG 音效链（P32）/ vt+308 存活查询（P29）/ vt+40(cond) 条件码位掩码（P25，
//   17=0b10001 玩家门）/ vt+628 伤害公式（P14）/ sub_4E5B50 暴击判定门（P12）/
//   sub_41A5E0 防篡改读、sub_41A590/sub_41C150 防篡改写（P24）/ vt+592 召唤怪物/
//   sub_4E4A50 异常状态·事件施加器 / attackinfo+20 伤害属性（0物理/1魔法/2无视）
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============
// 【分区 1】消耗品/Stackable 物品 PO 族（0x510000-0x510EE0）
// 区域放置(CNItemAreaStackable)/武器属性变更(CNChangeWeaponElement)/状态变更(CNChangeStatus)/
// 激活属性(CNChangeActiveProperty)/元素抗性(CNChangeElementTolerance)/召唤怪物/投掷/配方/抽奖/
// 防冻药水 + 六个消耗品状态初始化器（构造 CNChangeStatus 参数包，浮点即 IEEE754 原值）。
// 使用触发统一走 vmt88：CNRDStackable__vmt88 基调 → 宿主可用性门 → 效果施加。
// ============

// 0x510000 sub_510000
// ------------------------------------------------------------
// CNItemAreaStackable 构造器（区域放置型消耗品）：+41=状态参数a3、+298=数据长度a5、本体数据 qmemcpy 至 +42

uint32_t */*thiscall*/ sub_510000(uint32_t *this, char pszArg2, int nArg3, const void *pArg4, unsigned int uArg5)
{
  sub_50F740(pszArg2);
  *(this + 41) = nArg3;
  *(this + 298) = uArg5;
  *this = &vftbl_CNItemAreaStackable;
  qmemcpy(this + 42, pArg4, uArg5);
  return this;
}



// ------------------------------------------------------------
// 0x510050 CNItemAreaStackable__vmt88
// ------------------------------------------------------------
// CNItemAreaStackable__vmt88 使用触发：基调 CNRDStackable__vmt88 → 宿主 vt+308 可用 →
// vt+132(0,0,4,0,+298,数据) 生成区域对象 → vt+16 位移 → vt+580(+41 状态ID, 结果+4) —— 脚下放置区域效果

int /*thiscall*/ CNItemAreaStackable__vmt88(uint32_t *this, int *pDwArg2, int nArg3, int nArg4)
{
  int result; // eax
  int fld_e298; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax

  CNRDStackable__vmt88(pDwArg2, nArg3, nArg4);
  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 308))(pDwArg2);
  if ( (uint8_t)result != 0 )
  {
    fld_e298 = *(this + 298);
    v7 = *pDwArg2;
    if ( fld_e298 != 0 )
    {
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int, uint32_t, int, uint32_t *))(*this + 132))(
             this,
             0,
             0,
             4,
             0,
             fld_e298,
             this + 42);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t))(*this + 16))(this, 0, 0, *(uint32_t *)(v9 + 8));
    }
    else
    {
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 16))(
             this,
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
    return (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(v7 + 580))(pDwArg2, *(this + 41), *(uint32_t *)(v8 + 4));
  }
  return result;
}



// ------------------------------------------------------------
// 0x510100 CNItemAreaStackable__vmt4
// ------------------------------------------------------------
// CNItemAreaStackable__vmt4 删除析构壳（a2&1 → free，标准 MSVC 形态）

void */*thiscall*/ CNItemAreaStackable__vmt4(void *Block, char pszArg2)
{
  sub_510130();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x510130 sub_510130
// ------------------------------------------------------------
// CNItemAreaStackable 析构基座：复位 vftbl → sub_485B50 基类析构

int /*thiscall*/ sub_510130(uint32_t *this)
{
  *this = &vftbl_CNItemAreaStackable;
  return sub_485B50();
}



// ------------------------------------------------------------
// 0x510140 sub_510140
// ------------------------------------------------------------
// CNChangeWeaponElement 构造器（武器属性变更 PO）：sub_4DF1B0(a2,a3,a4,-1) 属性参数包

uint32_t */*thiscall*/ sub_510140(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_4DF1B0(nArg2, nArg3, nArg4, -1);
  *this = &vftbl_CNChangeWeaponElement;
  return this;
}



// ------------------------------------------------------------
// 0x510170 CNChangeWeaponElement__vmt0
// ------------------------------------------------------------
// CNChangeWeaponElement__vmt0 删除析构壳

void */*thiscall*/ CNChangeWeaponElement__vmt0(void *Block, char pszArg2)
{
  sub_5101A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5101A0 sub_5101A0
// ------------------------------------------------------------
// CNChangeWeaponElement 析构基座 → sub_4DF250

int /*thiscall*/ sub_5101A0(uint32_t *this)
{
  *this = &vftbl_CNChangeWeaponElement;
  return sub_4DF250();
}



// ------------------------------------------------------------
// 0x5101B0 sub_5101B0
// ------------------------------------------------------------
// CNChangeStatus 构造器（状态变更 PO，0x7C 字节）：+21..30 清零，sub_5F76F0/5F7750 装参数包 a2..a5；
// 被 0x510960 族状态初始化器与 0x51 区大量装备 PO 实例化

uint32_t */*thiscall*/ sub_5101B0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  sub_4B1030();
  *this = &vftbl_CNChangeStatus;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  sub_5F76F0(this);
  sub_5F7750(nArg2, nArg3, nArg4, nArg5);
  return this;
}



// ------------------------------------------------------------
// 0x510230 sub_510230
// ------------------------------------------------------------
// CNChangeActiveProperty 构造器（激活属性变更 PO）：nullsub_3 + sub_6038D0(a2,a3,a4)

uint32_t */*thiscall*/ sub_510230(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_4B1030();
  *this = &vftbl_CNChangeActiveProperty;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  nullsub_3();
  sub_6038D0(nArg2, nArg3, nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x5102A0 CNChangeActiveProperty__vmt0
// ------------------------------------------------------------
// CNChangeActiveProperty__vmt0 删除析构壳

void */*thiscall*/ CNChangeActiveProperty__vmt0(void *Block, char pszArg2)
{
  sub_5102D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5102D0 sub_5102D0
// ------------------------------------------------------------
// CNChangeActiveProperty 析构基座：释放 +21 向量 → 退回 IRDAppendage/nengine__IObject 基类链

int /*thiscall*/ sub_5102D0(void **this)
{
  int result; // eax

  *this = &vftbl_CNChangeActiveProperty;
  nullsub_3();
  if ( *(this + 21) != nullptr )
    j__free(*(this + 21));
  *(this + 21) = nullptr;
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *((uint8_t *)this + 12) = 0;
  *(this + 2) = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x510350 sub_510350
// ------------------------------------------------------------
// CNChangeElementTolerance 构造器（元素抗性变更 PO）：a6=标签串存 +27 字符串（+32=容量15）；
// bigfunc_510F30 护符 PO 以 (2,0,10,60000,1,"CHARM_FIRE_USE") 等四系调用它注册属性珠

uint32_t */*thiscall*/ sub_510350(uint32_t *this, int nArg2, char pszArg3, int nArg4, int nArg5, char pszArg6, void *Src)
{
  sub_4B1030();
  *this = &vftbl_CNChangeElementTolerance;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 32) = 15;
  *(this + 31) = 0;
  *((uint8_t *)this + 108) = 0;
  sub_603900(this);
  sub_603A90(nArg2, pszArg3, nArg4, nArg5, pszArg6, Src);
  return this;
}



// ------------------------------------------------------------
// 0x5103E0 CNChangeElementTolerance__vmt0
// ------------------------------------------------------------
// CNChangeElementTolerance__vmt0 删除析构壳

void */*thiscall*/ CNChangeElementTolerance__vmt0(void *Block, char pszArg2)
{
  sub_510410();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x510410 sub_510410
// ------------------------------------------------------------
// CNChangeElementTolerance 析构基座：释放 +27 字符串(+32>=0x10 堆模式) 与 +22 向量 → 退基类链

int /*thiscall*/ sub_510410(void **this)
{
  int result; // eax

  *this = &vftbl_CNChangeElementTolerance;
  sub_603910();
  if ( (unsigned int)*(this + 32) >= 0x10 )
    j__free(*(this + 27));
  *(this + 32) = (void *)15;
  *(this + 31) = nullptr;
  *((uint8_t *)this + 108) = 0;
  if ( *(this + 22) != nullptr )
    j__free(*(this + 22));
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *((uint8_t *)this + 12) = 0;
  *(this + 2) = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x5104B0 sub_5104B0
// ------------------------------------------------------------
// CNSummonMonsterStackable 构造器（召唤怪物消耗品）：+41=怪物ID、+42/+43=数量区间

uint32_t */*thiscall*/ sub_5104B0(uint32_t *this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  sub_50F740(pszArg2);
  *(this + 43) = nArg5;
  *this = &vftbl_CNSummonMonsterStackable;
  *(this + 41) = nArg3;
  *(this + 42) = nArg4;
  return this;
}



// ------------------------------------------------------------
// 0x5104F0 CNSummonMonsterStackable__vmt88
// ------------------------------------------------------------
// CNSummonMonsterStackable__vmt88 使用触发：srand(Seed) → 按宿主朝向偏移 ±75 →
// sub_4049C0(+42..+43, rand%99,100) 区间 lerp（P30 同款插值）→ vt+152(2,…,0xFFFF)→vt+128→vt+124→vt+376 定位 → vt+592(+41) 召唤

int /*thiscall*/ CNSummonMonsterStackable__vmt88(uint32_t *this, int *pDwArg2, int nArg3, unsigned int Seed)
{
  int result; // eax
  int v6; // eax
  int nRand; // eax
  uint64_t v8; // rax
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  float fld_e42; // [esp+0h] [ebp-24h]
  float fld_e43; // [esp+4h] [ebp-20h]
  uint8_t v16[3]; // [esp+1Ch] [ebp-8h] BYREF
  int v17; // [esp+1Fh] [ebp-5h]
  int v18; // [esp+30h] [ebp+Ch]
  unsigned int Seeda; // [esp+34h] [ebp+10h]

  CNRDStackable__vmt88(pDwArg2, nArg3, Seed);
  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 308))(pDwArg2);
  if ( (uint8_t)result != 0 )
  {
    v16[2] = 0;
    v17 = 0;
    v16[0] = 1;
    v16[1] = 2;
    srand(Seed);
    if ( (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 152))(pDwArg2) != 0 )
      v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2) + 75;
    else
      v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2) - 75;
    Seeda = v6;
    nRand = rand();
    fld_e43 = (float)(int)*(this + 43);
    fld_e42 = (float)(int)*(this + 42);
    v8 = (uint64_t)sub_4049C0(fld_e42, fld_e43, nRand % 99, 100);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v9 = *pDwArg2;
    v18 = v8;
    v10 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint8_t *, uint32_t))(*pDwArg2 + 152))(
            pDwArg2,
            2,
            0,
            0,
            0xFFFF,
            0,
            0,
            v16,
            0);
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg2 + 128))(pDwArg2, v10);
    v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg2 + 124))(pDwArg2, v11);
    v13 = (*(int (/*thiscall*/ **)(int *, int, unsigned int, int))(*pDwArg2 + 376))(pDwArg2, v18, Seeda, v12);
    return (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v9 + 592))(pDwArg2, *(this + 41), v13);
  }
  return result;
}



// ------------------------------------------------------------
// 0x510600 CNSummonMonsterStackable__vmt4
// ------------------------------------------------------------
// CNSummonMonsterStackable__vmt4 删除析构壳

void */*thiscall*/ CNSummonMonsterStackable__vmt4(void *Block, char pszArg2)
{
  sub_510630();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x510630 sub_510630
// ------------------------------------------------------------
// CNSummonMonsterStackable 析构基座 → sub_485B50

int /*thiscall*/ sub_510630(uint32_t *this)
{
  *this = &vftbl_CNSummonMonsterStackable;
  return sub_485B50();
}



// ------------------------------------------------------------
// 0x510640 sub_510640
// ------------------------------------------------------------
// CNActiveStatusStackable 构造器（主动状态消耗品）：sub_602430/602440 装参数

uint32_t */*thiscall*/ sub_510640(uint32_t *this, char pszArg2, int nArg3, char pszArg4)
{
  sub_50F740(pszArg2);
  *this = &vftbl_CNActiveStatusStackable;
  *(this + 42) = 0;
  *(this + 43) = 0;
  *(this + 44) = 0;
  sub_602430(this);
  sub_602440(nArg3, pszArg4);
  return this;
}



// ------------------------------------------------------------
// 0x5106C0 sub_5106C0
// ------------------------------------------------------------
// CNThrowStackable 构造器（投掷消耗品）

uint32_t */*thiscall*/ sub_5106C0(uint32_t *this, char pszArg2)
{
  sub_50F740(pszArg2);
  *this = &vftbl_CNThrowStackable;
  nullsub_3();
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x510720 CNThrowStackable__vmt4
// ------------------------------------------------------------
// CNThrowStackable__vmt4 删除析构壳

void */*thiscall*/ CNThrowStackable__vmt4(void *Block, char pszArg2)
{
  sub_510750();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x510750 sub_510750
// ------------------------------------------------------------
// CNThrowStackable 析构基座 → sub_485B50

int /*thiscall*/ sub_510750(uint32_t *this)
{
  *this = &vftbl_CNThrowStackable;
  nullsub_3();
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x5107A0 sub_5107A0
// ------------------------------------------------------------
// CNRecipeStackable 构造器（配方卷轴）：sub_603EE0/603F30

uint32_t */*thiscall*/ sub_5107A0(uint32_t *this, char pszArg2)
{
  sub_50F740(pszArg2);
  *this = &vftbl_CNRecipeStackable;
  sub_603EE0(this);
  sub_603F30(this);
  return this;
}



// ------------------------------------------------------------
// 0x510800 CNRecipeStackable__vmt4
// ------------------------------------------------------------
// CNRecipeStackable__vmt4 删除析构壳

void */*thiscall*/ CNRecipeStackable__vmt4(void *Block, char pszArg2)
{
  sub_510830();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x510830 sub_510830
// ------------------------------------------------------------
// CNRecipeStackable 析构基座 → sub_485B50

int /*thiscall*/ sub_510830(uint32_t *this)
{
  *this = &vftbl_CNRecipeStackable;
  nullsub_3();
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x510880 sub_510880
// ------------------------------------------------------------
// CNLotteryStackable 构造器（抽奖券）

uint32_t */*thiscall*/ sub_510880(uint32_t *this, char pszArg2)
{
  sub_50F740(pszArg2);
  *this = &vftbl_CNLotteryStackable;
  nullsub_3();
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x5108E0 CNLotteryStackable__vmt4
// ------------------------------------------------------------
// CNLotteryStackable__vmt4 删除析构壳

void */*thiscall*/ CNLotteryStackable__vmt4(void *Block, char pszArg2)
{
  sub_510910();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x510910 sub_510910
// ------------------------------------------------------------
// CNLotteryStackable 析构基座 → sub_485B50

int /*thiscall*/ sub_510910(uint32_t *this)
{
  *this = &vftbl_CNLotteryStackable;
  nullsub_3();
  return sub_485B50(this);
}



// ------------------------------------------------------------
// 0x510960 sub_510960
// ------------------------------------------------------------
// 状态初始化器 A：new(0x7C) CNChangeStatus(2 参数，IEEE754 原值 1103626240=26.0f/25/26.0f) 存 +337；
// +335=500ms 延迟；+334=宿主时钟读数（vt+212 → sub_699000(容器+36)，P30 时钟族）。DragonicSkin 构造时调用

int /*thiscall*/ sub_510960(uint32_t *this)
{
  uint32_t *pMem; // eax
  int *v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int result; // eax
  int v8; // [esp+4h] [ebp-28h] BYREF
  char v9; // [esp+8h] [ebp-24h]
  int v10; // [esp+Ch] [ebp-20h]
  int v11; // [esp+10h] [ebp-1Ch]
  char v12; // [esp+14h] [ebp-18h]
  int v13; // [esp+18h] [ebp-14h]
  uint32_t *pMem2; // [esp+1Ch] [ebp-10h]
  int v15; // [esp+28h] [ebp-4h]

  v8 = 4;
  v9 = 1;
  v10 = 1103626240;
  v11 = 25;
  v12 = 1;
  v13 = 1103626240;
  pMem = operator new(0x7Cu);
  pMem2 = pMem;
  v15 = 0;
  if ( pMem != nullptr )
    v3 = sub_5101B0(pMem, (int)&v8, 2, 0, 1);
  else
    v3 = nullptr;
  *(this + 337) = v3;
  v4 = *v3;
  v15 = -1;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v4 + 64))(v3) + 36) = 0;
  v5 = *this;
  *(this + 335) = 500;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 212))(this) != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
    result = sub_699000(v6 + 36);  // 【clock_now(clk)】
  }
  else
  {
    result = 0;
  }
  *(this + 334) = result;
  return result;
}



// ------------------------------------------------------------
// 0x510A30 sub_510A30
// ------------------------------------------------------------
// 状态初始化器 B：CNChangeStatus(3 参数，40.0f/8/30.0f/5/-32.0f)。HatefulBeastCoat vmt94 转发到这里

int /*thiscall*/ sub_510A30(uint32_t *this)
{
  uint32_t *pMem; // eax
  int *v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int result; // eax
  int v8; // [esp+8h] [ebp-34h] BYREF
  char v9; // [esp+Ch] [ebp-30h]
  int v10; // [esp+10h] [ebp-2Ch]
  int v11; // [esp+14h] [ebp-28h]
  char v12; // [esp+18h] [ebp-24h]
  int v13; // [esp+1Ch] [ebp-20h]
  int v14; // [esp+20h] [ebp-1Ch]
  char v15; // [esp+24h] [ebp-18h]
  int v16; // [esp+28h] [ebp-14h]
  uint32_t *pMem2; // [esp+2Ch] [ebp-10h]
  int v18; // [esp+38h] [ebp-4h]

  v8 = 4;
  v9 = 1;
  v10 = 1109393408;
  v11 = 8;
  v12 = 0;
  v13 = 1106247680;
  v14 = 5;
  v15 = 1;
  v16 = -1041235968;
  pMem = operator new(0x7Cu);
  pMem2 = pMem;
  v18 = 0;
  if ( pMem != nullptr )
    v3 = sub_5101B0(pMem, (int)&v8, 3, 0, 1);
  else
    v3 = nullptr;
  *(this + 371) = v3;
  v4 = *v3;
  v18 = -1;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v4 + 64))(v3) + 36) = 0;
  v5 = *this;
  *(this + 335) = 500;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 212))(this) != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
    result = sub_699000(v6 + 36);  // 【clock_now(clk)】
  }
  else
  {
    result = 0;
  }
  *((uint8_t *)this + 1488) = 0;
  *(this + 334) = result;
  *((uint8_t *)this + 1469) = 0;
  *((uint8_t *)this + 1470) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x510B20 sub_510B20
// ------------------------------------------------------------
// 状态初始化器 C：CNChangeStatus(1 参数，15.0f)。LalaMisYong vmt94 转发到这里

int /*thiscall*/ sub_510B20(uint32_t *this)
{
  uint32_t *pMem; // eax
  int *v3; // eax
  int v4; // edx
  int v5; // eax
  int v6; // eax
  int result; // eax
  int v8; // [esp+8h] [ebp-1Ch] BYREF
  char v9; // [esp+Ch] [ebp-18h]
  int v10; // [esp+10h] [ebp-14h]
  uint32_t *pMem2; // [esp+14h] [ebp-10h]
  int v12; // [esp+20h] [ebp-4h]

  v8 = 1;
  v9 = 1;
  v10 = 1097859072;
  pMem = operator new(0x7Cu);
  pMem2 = pMem;
  v12 = 0;
  if ( pMem != nullptr )
    v3 = sub_5101B0(pMem, (int)&v8, 1, 0, 1);
  else
    v3 = nullptr;
  *(this + 364) = v3;
  v4 = *v3;
  v12 = -1;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v4 + 64))(v3) + 36) = 0;
  v5 = *this;
  *(this + 335) = 500;
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 212))(this) != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
    result = sub_699000(v6 + 36);  // 【clock_now(clk)】
  }
  else
  {
    result = 0;
  }
  *((uint8_t *)this + 1488) = 0;
  *(this + 334) = result;
  *((uint8_t *)this + 1473) = 0;
  *((uint8_t *)this + 1474) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x510BF0 sub_510BF0
// ------------------------------------------------------------
// 状态初始化器 D：CNChangeStatus(2 参数，30.0f/2/30.0f)。CrisisScepter 构造时调用

int /*thiscall*/ sub_510BF0(uint32_t *this)
{
  uint32_t *pMem; // eax
  int *v3; // eax
  int v4; // edx
  int v5; // eax
  int result; // eax
  int v7; // eax
  int v8; // [esp+8h] [ebp-28h] BYREF
  char v9; // [esp+Ch] [ebp-24h]
  int v10; // [esp+10h] [ebp-20h]
  int v11; // [esp+14h] [ebp-1Ch]
  char v12; // [esp+18h] [ebp-18h]
  int v13; // [esp+1Ch] [ebp-14h]
  uint32_t *pMem2; // [esp+20h] [ebp-10h]
  int v15; // [esp+2Ch] [ebp-4h]

  v8 = 1;
  v9 = 0;
  v10 = 1106247680;
  v11 = 2;
  v12 = 0;
  v13 = 1106247680;
  pMem = operator new(0x7Cu);
  pMem2 = pMem;
  v15 = 0;
  if ( pMem != nullptr )
    v3 = sub_5101B0(pMem, (int)&v8, 2, 0, 1);
  else
    v3 = nullptr;
  *(this + 364) = v3;
  v4 = *v3;
  v15 = -1;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v4 + 64))(v3) + 36) = 0;
  v5 = *this;
  *(this + 335) = 500;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 212))(this);
  if ( result != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
    result = sub_699000(v7 + 36);  // 【clock_now(clk)】
    *(this + 334) = result;
  }
  else
  {
    *(this + 334) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x510CD0 sub_510CD0
// ------------------------------------------------------------
// 状态初始化器 E：CNChangeStatus(2 参数，1140457472=496.0f/0/30.0f)。AceAdventCoat 构造时调用

int /*thiscall*/ sub_510CD0(uint32_t *this)
{
  uint32_t *pMem; // eax
  int *v3; // eax
  int v4; // edx
  int v5; // eax
  int result; // eax
  int v7; // eax
  int v8; // [esp+8h] [ebp-28h] BYREF
  char v9; // [esp+Ch] [ebp-24h]
  int v10; // [esp+10h] [ebp-20h]
  int v11; // [esp+14h] [ebp-1Ch]
  char v12; // [esp+18h] [ebp-18h]
  int v13; // [esp+1Ch] [ebp-14h]
  uint32_t *pMem2; // [esp+20h] [ebp-10h]
  int v15; // [esp+2Ch] [ebp-4h]

  v8 = 5;
  v9 = 0;
  v10 = 1140457472;
  v11 = 0;
  v12 = 0;
  v13 = 1106247680;
  pMem = operator new(0x7Cu);
  pMem2 = pMem;
  v15 = 0;
  if ( pMem != nullptr )
    v3 = sub_5101B0(pMem, (int)&v8, 2, 0, 1);
  else
    v3 = nullptr;
  *(this + 364) = v3;
  v4 = *v3;
  v15 = -1;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v4 + 64))(v3) + 36) = 0;
  v5 = *this;
  *(this + 335) = 500;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 212))(this);
  if ( result != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
    result = sub_699000(v7 + 36);  // 【clock_now(clk)】
    *(this + 334) = result;
  }
  else
  {
    *(this + 334) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x510DB0 sub_510DB0
// ------------------------------------------------------------
// 状态初始化器 F：CNChangeStatus(2 参数，30.0f/3/30.0f)。CurseArmorTodpursResist 构造时调用

int /*thiscall*/ sub_510DB0(uint32_t *this)
{
  uint32_t *pMem; // eax
  int *v3; // eax
  int v4; // edx
  int result; // eax
  int v6; // [esp+8h] [ebp-28h] BYREF
  char v7; // [esp+Ch] [ebp-24h]
  int v8; // [esp+10h] [ebp-20h]
  int v9; // [esp+14h] [ebp-1Ch]
  char v10; // [esp+18h] [ebp-18h]
  int v11; // [esp+1Ch] [ebp-14h]
  uint32_t *pMem2; // [esp+20h] [ebp-10h]
  int v13; // [esp+2Ch] [ebp-4h]

  v6 = 0;
  v7 = 0;
  v8 = 1106247680;
  v9 = 3;
  v10 = 0;
  v11 = 1106247680;
  pMem = operator new(0x7Cu);
  pMem2 = pMem;
  v13 = 0;
  if ( pMem != nullptr )
    v3 = sub_5101B0(pMem, (int)&v6, 2, 0, 1);
  else
    v3 = nullptr;
  *(this + 364) = v3;
  v4 = *v3;
  v13 = -1;
  result = (*(int (/*thiscall*/ **)(int *))(v4 + 64))(v3);
  *(uint8_t *)(result + 36) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x510E40 sub_510E40
// ------------------------------------------------------------
// CNAntiFreezePotion 构造器（防冻药水）：CNActiveStatusStackable 基类 + sub_602430/602440

uint32_t */*thiscall*/ sub_510E40(uint32_t *this, char pszArg2, int nArg3, char pszArg4)
{
  sub_510640(this, pszArg2, nArg3, pszArg4);
  *this = &vftbl_CNAntiFreezePotion;
  sub_602430(this);
  sub_602440(nArg3, pszArg4);
  return this;
}



// ------------------------------------------------------------
// 0x510EB0 CNAntiFreezePotion__vmt4
// ------------------------------------------------------------
// CNAntiFreezePotion__vmt4 删除析构壳

void */*thiscall*/ CNAntiFreezePotion__vmt4(void *Block, char pszArg2)
{
  sub_510EE0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x510EE0 sub_510EE0
// ------------------------------------------------------------
// CNAntiFreezePotion 析构基座 → sub_50F690

int /*thiscall*/ sub_510EE0(uint32_t *this)
{
  *this = &vftbl_CNAntiFreezePotion;
  nullsub_3();
  return sub_50F690(this);
}



// ------------------------------------------------------------
// ============
// 【分区 2】幸运金币 PO 族（0x513AA0-0x514320）
// CNCoinOfFortune（幸运硬币消耗品，FortuneCoinGood/Bad.ani 二选一）→
// CNCoinOfFortuneAppendage（延时结算附身：吉=回血 HP_RECOVERED / 凶=扣血+雷击
// Thunderbolt.ani+THUNDER_STRIKE+飘字 P39）。资源证据均为本文件字符串字面量。
// ============

// 0x513AA0 sub_513AA0
// ------------------------------------------------------------
// vector 追加器：+1/+2/+3=首/尾/容（8B 元素）；满则 sub_50F440 扩容 → sub_63A7C0 拷贝。金币事件队列底座

int /*thiscall*/ sub_513AA0(uint32_t *this, int nArg2)
{
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 3;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 3 )
    return sub_50F440(*(this + 2), 1, nArg2);
  fld_e22 = *(this + 2);
  result = sub_63A7C0(fld_e22, 1, nArg2);
  *(this + 2) = fld_e22 + 8;
  return result;
}



// ------------------------------------------------------------
// 0x513B10 sub_513B10
// ------------------------------------------------------------
// 金币事件对 (a2,a3) 压入 +337 事件 vector

int /*thiscall*/ sub_513B10(uint32_t *this, int nArg2, int nArg3)
{
  uint32_t v4[2]; // [esp+0h] [ebp-8h] BYREF

  v4[0] = nArg2;
  v4[1] = nArg3;
  return sub_513AA0(this + 337, (int)v4);
}



// ------------------------------------------------------------
// 0x513B40 CNCoinOfFortune__vmt88
// ------------------------------------------------------------
// ★ CNCoinOfFortune__vmt88 使用触发（幸运硬币消耗品）【资源全字符串实证】：
// srand(Seed) → rand()%2 抽吉/凶 → "Common/Etc/Animation/FortuneCoinGood.ani"/"FortuneCoinBad.ani"
// 池化动画（sub_42FCB0(228) 特效池 + sub_431860 + sub_44E0D0 → P33 池化单例）→ sub_45FE80 入演播层 2 →
// 位置=宿主 vt+120/124(+层) 高度 vt+192()×1.2 → sub_4A06D0(高度) → sub_491C10 动画计时长 →
// new(0x54) CNDelayedProc → CNCoinOfFortuneAppendage（+80=吉凶标志）挂宿主 → 播 "COIN_BOUND"（P32 TAG）

int /*thiscall*/ CNCoinOfFortune__vmt88(uint32_t *this, int nArg2, int nArg3, unsigned int Seed)
{
  int nRand; // ebx
  int v7; // eax
  const char *v8; // ecx
  char *v9; // eax
  char *v10; // ebx
  char *v11; // eax
  int v12; // eax
  int fld_e41; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // ebx
  uint32_t *pMem; // eax
  uint32_t *pMem2; // edi
  int v20; // [esp-Ch] [ebp-28h]
  int v21; // [esp-4h] [ebp-20h]
  int nRand2; // [esp+Ch] [ebp-10h]
  float v23; // [esp+24h] [ebp+8h]
  unsigned int Seeda; // [esp+2Ch] [ebp+10h]

  CNRDStackable__vmt88(nArg2, nArg3, Seed);
  srand(Seed);
  nRand = rand() % 2;
  nRand2 = nRand;
  v7 = sub_42FCB0(228);
  if ( v7 != 0 )
  {
    v8 = "Common/Etc/Animation/FortuneCoinGood.ani";
    if ( nRand == 0 )
      v8 = "Common/Etc/Animation/FortuneCoinBad.ani";
    Seeda = sub_431860(v7, v8, 1);
  }
  else
  {
    Seeda = 0;
  }
  v9 = (char *)sub_44B6C0(284);
  v10 = v9;
  if ( v9 != nullptr )
  {
    sub_44E0D0(v9, Seeda, 1);
    *(uint32_t *)v10 = &vftbl_CNRDPooledObject;
    v11 = v10;
  }
  else
  {
    v11 = nullptr;
  }
  v20 = (int)v11;
  *(this + 41) = v11;
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 80))(nArg2);
  sub_45FE80(v12, (int)this, 2, 0, v20, nArg2, 0);
  fld_e41 = *(uint32_t *)*(this + 41);
  v23 = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 192))(nArg2) * 1.2;
  v21 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2) + v23);
  v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
  v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 120))(nArg2, v14 + 1);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e41 + 112))(*(this + 41), v15);
  (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 41) + 60))(*(this + 41), nArg2);
  sub_4A06D0(v21);
  v16 = sub_491C10(Seeda);
  pMem = operator new(0x54u);
  pMem2 = pMem;
  if ( pMem != nullptr )
  {
    sub_4B1030(pMem);
    *pMem2 = &vftbl_CNDelayedProc;
    sub_5F6610(pMem2);
    sub_5F66A0(1);
    pMem2[18] = v16;
    *pMem2 = &vftbl_CNCoinOfFortuneAppendage;
    *((uint8_t *)pMem2 + 80) = nRand2 == 1;
  }
  else
  {
    pMem2 = nullptr;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, int))(*pMem2 + 56))(pMem2, nArg2, nArg2, 0, 0, 0, -1);
  return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)nArg2 + 212))(
           nArg2,
           "COIN_BOUND",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x513D30 CNDelayedProc__vmt0
// ------------------------------------------------------------
// CNDelayedProc__vmt0 删除析构壳（延时过程基类，IRDAppendage 链）

void */*thiscall*/ CNDelayedProc__vmt0(void *Block, char pszArg2)
{
  sub_513D60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x513D60 sub_513D60
// ------------------------------------------------------------
// CNDelayedProc 析构基座：vftbl 复位 ×2 → sub_5F6640 → nengine__IObject

int /*thiscall*/ sub_513D60(uint32_t *this)
{
  int result; // eax

  *this = &vftbl_CNDelayedProc;
  sub_5F6640(this);
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *(this + 2) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x513DC0 CNCoinOfFortuneAppendage__vmt0
// ------------------------------------------------------------
// CNCoinOfFortuneAppendage__vmt0 删除析构壳

void */*thiscall*/ CNCoinOfFortuneAppendage__vmt0(void *Block, char pszArg2)
{
  sub_513DF0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x513DF0 sub_513DF0
// ------------------------------------------------------------
// CNCoinOfFortuneAppendage 析构基座 → CNDelayedProc 析构

int /*thiscall*/ sub_513DF0(uint32_t *this)
{
  *this = &vftbl_CNCoinOfFortuneAppendage;
  return sub_513D60(this);
}



// ------------------------------------------------------------
// 0x513E00 CNCoinOfFortuneAppendage__vmt68
// ------------------------------------------------------------
// ★ CNCoinOfFortuneAppendage__vmt68 延时结算（金币附身到期，吉凶分支）【全字符串实证】：
// 先播 "COIN_TURN" → 吉(+80!=0)：回血 = vt+740()×0.2，sub_4D6810 建状态对象回挂 + 播 "HP_RECOVERED"
// → 凶：扣血 = HP 容器(vt+184/182) × 0.15000001 → sub_4D7960 飘字（P39 逐位字体）
// → "PassiveObject/Common/Animation/Thunderbolt.ani" 池化动画入演播层 → vt+472(3,[4,100,rand%2],1,1) 状态包
// → 播 "THUNDER_STRIKE" → 自毁 vt+76(0)

int /*thiscall*/ sub_513E00(void *this)  // 【CNCoinOfFortuneAppendage__vmt68】
{
  int pThis_1; // edx
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  int v5; // edi
  void **pThis_13; // edi
  int v7; // eax
  int pThis_14; // edi
  int v9; // eax
  int v10; // edi
  uint32_t *v11; // eax
  uint32_t *v12; // ebx
  int pThis_15; // edx
  int v14; // eax
  int pThis_17; // edi
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v20; // [esp+8h] [ebp-48h]
  int pThis_12; // [esp+Ch] [ebp-44h]
  int v22; // [esp+10h] [ebp-40h]
  int pThis_16; // [esp+18h] [ebp-38h]
  int v24; // [esp+20h] [ebp-30h]
  uint8_t v25[4]; // [esp+2Ch] [ebp-24h] BYREF
  void *Block; // [esp+30h] [ebp-20h]
  int v27; // [esp+34h] [ebp-1Ch]
  int v28; // [esp+38h] [ebp-18h]
  void *nRand; // [esp+3Ch] [ebp-14h] BYREF
  uint32_t *v30; // [esp+40h] [ebp-10h]
  int v31; // [esp+4Ch] [ebp-4h]

  (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**((uint32_t **)this + 1) + 212))(
    *((uint32_t *)this + 1),
    "COIN_TURN",
    -1,
    0,
    0);
  pThis_1 = **((uint32_t **)this + 1);
  if ( *((uint8_t *)this + 80) != 0 )
  {
    v30 = (uint32_t *)(uint64_t)((double)(*(int (**)(void))(pThis_1 + 740))() * 0.2);
    pMem = operator new(0x80u);
    nRand = pMem;
    v31 = 0;
    if ( pMem != nullptr )
    {
      *(float *)&v22 = (float)(int)v30;
      v4 = sub_4D6810(pMem, v22, 100, 0, 1);
    }
    else
    {
      v4 = nullptr;
    }
    v5 = *(uint32_t *)v4;
    pThis_12 = *((uint32_t *)this + 1);
    v31 = -1;
    (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t, uint32_t, int))(v5 + 56))(v4, pThis_12, pThis_12, 0, 0, 0, -1);
    (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**((uint32_t **)this + 1) + 212))(
      *((uint32_t *)this + 1),
      "HP_RECOVERED",
      -1,
      0,
      0);
  }
  else
  {
    v30 = (uint32_t *)(*(int (**)(void))(pThis_1 + 740))();
    pThis_13 = *((void ***)this + 1);
    v30 = (uint32_t *)(uint64_t)((double)(int)v30 * 0.15000001);
    nRand = *pThis_13;
    v7 = (*((int (/*thiscall*/ **)(void **, int, uint32_t))nRand + 184))(pThis_13, 1, 0);
    (*((void (/*thiscall*/ **)(void **, int))nRand + 182))(pThis_13, v7 - (uint32_t)v30);
    pThis_14 = *((uint32_t *)this + 1);
    nRand = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_14 + 192))(pThis_14);
    v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_14 + 124))(pThis_14) + 1;
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_14 + 120))(pThis_14);
    sub_4D7960((int)v30, pThis_14, (int)this, v9, v20, (uint64_t)((double)(int)nRand * 0.89999998), (int)v30, 0, 0, 0);  // 【飘字咽喉（§1.1 case 0x14；第 14/39 轮 5 层精灵）】
    v31 = 1;
    if ( sub_42FCB0(228) != 0 )
      v10 = sub_431860((char)"PassiveObject/Common/Animation/Thunderbolt.ani", 1);
    else
      v10 = 0;
    v11 = (uint32_t *)sub_44B6C0(284);
    v12 = v11;
    nRand = v11;
    v31 = 2;
    if ( v11 != nullptr )
    {
      sub_44E0D0((char *)v11, v10, 1);
      *v12 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v12 = nullptr;
    }
    pThis_15 = **((uint32_t **)this + 1);
    pThis_16 = *((uint32_t *)this + 1);
    v30 = v12;
    v31 = -1;
    v14 = (*(int (/*stdcall*/ **)(int))(pThis_15 + 80))(2);
    sub_45FE80(v14, v10, 0, (int)v12, pThis_16, 0, v24);
    pThis_17 = *((uint32_t *)this + 1);
    v16 = *v12;
    v17 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pThis_17 + 124))(pThis_17, 0);
    v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_17 + 120))(pThis_17, v17);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v16 + 112))(v30, v18);
    Block = nullptr;
    v27 = 0;
    v28 = 0;
    v31 = 3;
    nRand = (void *)4;
    sub_431230((int)v25, &nRand);
    nRand = (void *)100;
    sub_431230((int)v25, &nRand);
    nRand = (void *)(rand() % 2);
    sub_431230((int)v25, &nRand);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, int, int))(**((uint32_t **)this + 1) + 472))(
      *((uint32_t *)this + 1),
      3,
      v25,
      1,
      1);
    (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**((uint32_t **)this + 1) + 212))(
      *((uint32_t *)this + 1),
      "THUNDER_STRIKE",
      -1,
      0,
      0);
    v31 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v27 = 0;
    v28 = 0;
  }
  return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 76))(this, 0);
}


// ------------------------------------------------------------
// ============
// 【分区 3】装备 PO 基类（0x5140A0-0x514B80）
// CNRDEquipment 构造基座 + 四个可复用基类：CNSpecificEnemyEquipment（对特定敌人）、
// CNSpecificStateEquipment（特定状态下生效）、CNEventEquipment（事件触发）、
// CNEquipmentSummonOnDamage（受击召唤）、CNEquipmentDragonicSkin（HP 门限状态维持）。
// 装备 PO 挂载/卸载协议见 docs/15（宿主 vmt310/314，18 观察者槽）。
// ============

// 0x5140A0 sub_5140A0
// ------------------------------------------------------------
// ★ 0x5140A0 CNRDEquipment 构造基座（装备 PO 本体，>=1.3KB）：+148 容器 sub_4B3BE0、+212 区 sub_437E70、
// +1160 包体容器 sub_4E9A50（docs/15 vmt328 UDP type=10 物品使用包载荷）、+1228 nengine__CNTimer、
// +1272 szPassword 字符串槽 → sub_4E9D70 + sub_4EEB70(解析参数)

char */*thiscall*/ sub_5140A0(char *this, char ArgList, int nArg3)  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
{
  sub_485CC0();
  *(uint32_t *)this = &vftbl_CNRDEquipment;
  sub_4B3BE0(this + 148);
  sub_437E70((uint32_t *)this + 53);
  sub_4E9A50(this + 1160);
  *(this + 1224) = 0;
  *((uint32_t *)this + 305) = &vftbl_nengine__CNTimer;
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
  sub_41BFE0((void **)this + 318, szPassword);
  *((uint32_t *)this + 323) = 0;
  *((uint32_t *)this + 324) = 0;
  *((uint32_t *)this + 325) = 0;
  *((uint32_t *)this + 327) = 0;
  *((uint32_t *)this + 328) = 0;
  *((uint32_t *)this + 329) = 0;
  sub_4E9D70(this);
  sub_4EEB70(ArgList, nArg3);
  return this;
}



// ------------------------------------------------------------
// 0x5141B0 sub_5141B0
// ------------------------------------------------------------
// CNSpecificEnemyEquipment 构造器（对特定敌人装备基类）：+1352..1376 计数区 + +1380/+2328 双容器；
// a4/a5 = 目标敌我标志（下游子类以 (1,0)/(0,1) 区分对敌/对己）

int /*thiscall*/ sub_5141B0(int this, char ArgList, int nArg3, char pszArg4, char pszArg5)
{
  sub_5140A0((char *)this, ArgList, nArg3);  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
  *(uint32_t *)this = &vftbl_CNSpecificEnemyEquipment;
  *(uint32_t *)(this + 1352) = 0;
  *(uint32_t *)(this + 1356) = 0;
  *(uint32_t *)(this + 1360) = 0;
  *(uint32_t *)(this + 1368) = 0;
  *(uint32_t *)(this + 1372) = 0;
  *(uint32_t *)(this + 1376) = 0;
  sub_437E70((uint32_t *)(this + 1380));
  sub_437E70((uint32_t *)(this + 2328));
  sub_604310(this);
  sub_604330(pszArg4, pszArg5);
  return this;
}



// ------------------------------------------------------------
// 0x514260 sub_514260
// ------------------------------------------------------------
// CNSpecificEnemyEquipment 析构基座：nullsub_3 + sub_4382D0 ×2 + 释放 +342/+338 两向量 → sub_4BADD0

int /*thiscall*/ sub_514260(void *this)
{
  *(uint32_t *)this = &vftbl_CNSpecificEnemyEquipment;
  nullsub_3();
  sub_4382D0((int *)this + 582);
  sub_4382D0((int *)this + 345);
  if ( *((uint32_t *)this + 342) != 0 )
    j__free(*((void **)this + 342));
  *((uint32_t *)this + 342) = 0;
  *((uint32_t *)this + 343) = 0;
  *((uint32_t *)this + 344) = 0;
  if ( *((uint32_t *)this + 338) != 0 )
    j__free(*((void **)this + 338));
  *((uint32_t *)this + 338) = 0;
  *((uint32_t *)this + 339) = 0;
  *((uint32_t *)this + 340) = 0;
  return sub_4BADD0(this);
}



// ------------------------------------------------------------
// 0x514320 CNSpecificEnemyEquipment__vmt4
// ------------------------------------------------------------
// CNSpecificEnemyEquipment__vmt4 删除析构壳

void */*thiscall*/ CNSpecificEnemyEquipment__vmt4(void *Block, char pszArg2)
{
  sub_514260(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x514350 sub_514350
// ------------------------------------------------------------
// CNSpecificStateEquipment 构造器（特定状态下生效装备基类）：+1364 容器

int /*thiscall*/ sub_514350(int this, char ArgList, int nArg3, int nArg4, int nArg5)
{
  sub_5140A0((char *)this, ArgList, nArg3);  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
  *(uint32_t *)this = &vftbl_CNSpecificStateEquipment;
  *(uint32_t *)(this + 1352) = 0;
  *(uint32_t *)(this + 1356) = 0;
  *(uint32_t *)(this + 1360) = 0;
  sub_437E70((uint32_t *)(this + 1364));
  sub_604660(this);
  sub_604770(nArg4, nArg5);
  return this;
}



// ------------------------------------------------------------
// 0x5143E0 sub_5143E0
// ------------------------------------------------------------
// CNSpecificStateEquipment 析构基座

int /*thiscall*/ sub_5143E0(void *this)
{
  *(uint32_t *)this = &vftbl_CNSpecificStateEquipment;
  nullsub_3();
  sub_4382D0((int *)this + 341);
  if ( *((uint32_t *)this + 338) != 0 )
    j__free(*((void **)this + 338));
  *((uint32_t *)this + 338) = 0;
  *((uint32_t *)this + 339) = 0;
  *((uint32_t *)this + 340) = 0;
  return sub_4BADD0(this);
}



// ------------------------------------------------------------
// 0x514470 CNSpecificStateEquipment__vmt4
// ------------------------------------------------------------
// CNSpecificStateEquipment__vmt4 删除析构壳

void */*thiscall*/ CNSpecificStateEquipment__vmt4(void *Block, char pszArg2)
{
  sub_5143E0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5144A0 sub_5144A0
// ------------------------------------------------------------
// CNEventEquipment 构造器（事件触发装备基类）：+340/+361 双 vector

uint32_t */*thiscall*/ sub_5144A0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5140A0(ArgList, nArg3);  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
  *this = &vftbl_CNEventEquipment;
  *(this + 340) = 0;
  *(this + 341) = 0;
  *(this + 342) = 0;
  *(this + 361) = 0;
  *(this + 362) = 0;
  *(this + 363) = 0;
  sub_50F3D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x514520 sub_514520
// ------------------------------------------------------------
// CNEventEquipment 构造器重载：+1440 额外数组 sub_4ED3F0(a4)

int /*thiscall*/ sub_514520(int this, char ArgList, int nArg3, int nArg4)
{
  sub_5140A0((char *)this, ArgList, nArg3);  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
  *(uint32_t *)this = &vftbl_CNEventEquipment;
  *(uint32_t *)(this + 1360) = 0;
  *(uint32_t *)(this + 1364) = 0;
  *(uint32_t *)(this + 1368) = 0;
  *(uint32_t *)(this + 1444) = 0;
  *(uint32_t *)(this + 1448) = 0;
  *(uint32_t *)(this + 1452) = 0;
  sub_50F3D0(this);
  sub_4ED3F0(this + 1440, nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x5145B0 sub_5145B0
// ------------------------------------------------------------
// CNEventEquipment 析构基座：释放 +361/+340 双向量 → sub_4BADD0

int /*thiscall*/ sub_5145B0(void **this)
{
  *this = &vftbl_CNEventEquipment;
  nullsub_3();
  if ( *(this + 361) != nullptr )
    j__free(*(this + 361));
  *(this + 361) = nullptr;
  *(this + 362) = nullptr;
  *(this + 363) = nullptr;
  if ( *(this + 340) != nullptr )
    j__free(*(this + 340));
  *(this + 340) = nullptr;
  *(this + 341) = nullptr;
  *(this + 342) = nullptr;
  return sub_4BADD0(this);
}



// ------------------------------------------------------------
// 0x514650 CNEventEquipment__vmt4
// ------------------------------------------------------------
// CNEventEquipment__vmt4 删除析构壳

void **/*thiscall*/ CNEventEquipment__vmt4(void **Block, char pszArg2)
{
  sub_5145B0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x514680 sub_514680
// ------------------------------------------------------------
// CNEquipmentSummonOnDamage 构造器（受击召唤装备）

char */*thiscall*/ sub_514680(char *this, char ArgList, int nArg3)
{
  sub_5140A0(this, ArgList, nArg3);  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
  *(uint32_t *)this = &vftbl_CNEquipmentSummonOnDamage;
  return this;
}



// ------------------------------------------------------------
// 0x5146B0 CNEquipmentSummonOnDamage__vmt8C
// ------------------------------------------------------------
// ★ CNEquipmentSummonOnDamage__vmt8C 受击召唤【召唤机制样本】：
// vt+16()+92 = 装备参数四元组（召唤ID v32/概率% v10/门限 v11 等）→ 宿主存活(vt+308) && rand()%100<概率
// → 攻击有伤害(attackinfo+16/+0) && 攻击者==自身宿主(vt+576) && a5==0 && 门限分支
// → 攻击盒随机偏移(u16 ±100..300/±50..150/40..100, v28=3-rand%2 方向) → vt+152(1,盒,8,0xFFFF)
// → vt+192()/2 → vt+124 → vt+120 → vt+376(召唤ID) 定位 → vt+592(v32) 召唤（P29 盒取位 + vt+592 召唤链）

void /*thiscall*/ CNEquipmentSummonOnDamage__vmt8C(int *this, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int pThis_5C; // edi
  int v11; // ebx
  int pObj4; // eax
  int v13; // eax
  int *v14; // edi
  int pObj6; // ebx
  int v16; // eax
  int v17; // edx
  int *v18; // esi
  int v19; // edx
  int v20; // eax
  int v21; // edi
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  uint16_t v26[3]; // [esp+Ch] [ebp-24h] BYREF
  bool nRand; // [esp+12h] [ebp-1Eh]
  char nRand2; // [esp+13h] [ebp-1Dh]
  uint8_t v29[3]; // [esp+14h] [ebp-1Ch] BYREF
  int v30; // [esp+17h] [ebp-19h]
  int v31; // [esp+1Ch] [ebp-14h]
  int v32; // [esp+20h] [ebp-10h]
  int pObj; // [esp+24h] [ebp-Ch]
  int v34; // [esp+28h] [ebp-8h]
  int pObj2; // [esp+2Ch] [ebp-4h]
  int pObj5; // [esp+38h] [ebp+8h]
  int pObj3; // [esp+44h] [ebp+14h]

  v6 = (*(int (/*thiscall*/ **)(int *))(*this + 16))(this);
  v7 = *this;
  v32 = **(uint32_t **)(v6 + 92);
  v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 16))(this);
  v9 = *this;
  v34 = *(uint32_t *)(*(uint32_t *)(v8 + 92) + 4);
  pThis_5C = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v9 + 16))(this) + 92) + 8);
  v11 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 16))(this) + 92) + 12);
  sub_432FA0();
  pObj4 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 308))(pObj4) != 0 && rand() % 100 < pThis_5C )
  {
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
    if ( (*(uint8_t *)(v13 + 16) != 0 || *(float *)v13 > 0.0)
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) == nArg2
      && pszArg5 == 0
      && (v11 != 1 || (*(uint8_t (/*thiscall*/ **)(int *))(*this + 224))(this) != 0) )
    {
      v26[0] = rand() % 200 + 100;
      v26[1] = rand() % 100 + 50;
      nRand = rand() % 2 == 0;
      nRand2 = 3 - (rand() % 2 != 0);
      v29[2] = 0;
      v30 = 0;
      v29[0] = 1;
      v29[1] = 2;
      v26[2] = rand() % 60 + 40;
      v14 = (int *)(*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj6 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj3 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj2 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v16 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v17 = *this;
      pObj = v16;
      v18 = (int *)(*(int (/*thiscall*/ **)(int *))(v17 + 212))(this);
      v19 = *v14;
      v31 = *v18;
      v20 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, int, uint8_t *, uint32_t))(v19 + 152))(
              v14,
              1,
              v26,
              8,
              0xFFFF,
              0,
              1,
              v29,
              0);
      v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 192))(pObj3, v20) / 2;
      v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 128))(pObj6);
      v23 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 124))(pObj5, v22 + v21);
      v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 120))(pObj2, v23 - 1);
      v25 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 376))(pObj, v34, v24);
      (*(void (/*thiscall*/ **)(int *, int, int))(v31 + 592))(v18, v32, v25);
    }
  }
}



// ------------------------------------------------------------
// 0x514900 CNEquipmentSummonOnDamage__vmt4
// ------------------------------------------------------------
// CNEquipmentSummonOnDamage__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentSummonOnDamage__vmt4(void *Block, char pszArg2)
{
  sub_514930();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x514930 sub_514930
// ------------------------------------------------------------
// CNEquipmentSummonOnDamage 析构基座 → sub_4BADD0

int /*thiscall*/ sub_514930(uint32_t *this)
{
  *this = &vftbl_CNEquipmentSummonOnDamage;
  return sub_4BADD0(this);
}



// ------------------------------------------------------------
// 0x514940 sub_514940
// ------------------------------------------------------------
// CNEquipmentDragonicSkin 构造器（HP 门限状态维持装备）：调 0x510960 装状态初始化器 A

char */*thiscall*/ sub_514940(char *this, char ArgList, int nArg3)
{
  sub_5140A0(this, ArgList, nArg3);  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
  *(uint32_t *)this = &vftbl_CNEquipmentDragonicSkin;
  sub_510960(this);
  return this;
}



// ------------------------------------------------------------
// 0x5149B0 sub_5149B0
// ------------------------------------------------------------
// 状态卸载（DragonicSkin 系）：+337 状态对象 vt+0(1) 销毁 + +334/335 清零

int /*thiscall*/ sub_5149B0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e337)(uint32_t, int); // ecx
  int result; // eax

  fld_e337 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 337);
  if ( fld_e337 != nullptr )
    result = (**fld_e337)(fld_e337, 1);
  *(this + 337) = 0;
  *(this + 335) = 0;
  *(this + 334) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5149F0 CNEquipmentDragonicSkin__vmt12C
// ------------------------------------------------------------
// ★ CNEquipmentDragonicSkin__vmt12C 周期 tick（HP 门限状态维持）：sub_41C5A0(+313) 防篡改冷却门
// → HP(vt+736) <= vt+740()×0.25 → 状态已激活(vt+80()) 则解除(+76(0))；HP 充足 && 未激活 → 施加（迟滞回环）

int /*thiscall*/ CNEquipmentDragonicSkin__vmt12C(uint32_t **this)
{
  int result; // eax
  int pObj2; // edi
  int pObj; // ebx
  int v5; // eax
  int fld_e337; // edx
  int fld_e3372; // edi
  int v8; // eax
  int v9; // eax
  float v10; // [esp+4h] [ebp-8h]

  if ( sub_41C5A0(this + 313) == 0 || (uint8_t)(result = ((int (/*thiscall*/ *)(uint32_t **))(*this)[56])(this)) != 0 )
  {
    pObj2 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
    pObj = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
    v10 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 736))(pObj2);
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 740))(pObj);
    fld_e337 = **(this + 337);
    if ( (double)v5 * 0.25 <= v10 )
    {
      result = (*(int (**)(void))(fld_e337 + 80))();
      if ( (uint8_t)result == 1 )
        return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 337) + 76))(*(this + 337), 0);
    }
    else
    {
      result = (*(int (**)(void))(fld_e337 + 80))();
      if ( (uint8_t)result == 0 )
      {
        fld_e3372 = **(this + 337);
        v8 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, int))(*this)[53])(this, 0, 0, 0, -1);
        v9 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[53])(this, v8);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e3372 + 56))(*(this + 337), v9);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x514AE0 CNEquipmentDragonicSkin__vmt4
// ------------------------------------------------------------
// CNEquipmentDragonicSkin__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentDragonicSkin__vmt4(void *Block, char pszArg2)
{
  sub_514B10();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x514B10 sub_514B10
// ------------------------------------------------------------
// CNEquipmentDragonicSkin 析构基座：+337 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_514B10(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e337)(uint32_t, int); // ecx

  *this = &vftbl_CNEquipmentDragonicSkin;
  fld_e337 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 337);
  if ( fld_e337 != nullptr )
    (**fld_e337)(fld_e337, 1);
  *(this + 337) = 0;
  *(this + 335) = 0;
  *(this + 334) = 0;
  return sub_4BADD0(this);
}



// ------------------------------------------------------------
// ============
// 【分区 4】具名装备 PO 族（0x514B80-0x51B9F0）
// 每件特效/套装装备一个类。触发槽约定（虚表槽号 = 触发时机，宿主装备观察者槽分发）：
//   vmt88 攻击命中触发（攻方）/ vmt8C 受击触发（受方）/ vmt90·vmtA4 伤害量修正钩子 /
//   vmt12C·vmt13C 周期 tick（冷却计时·状态维持）/ vmt130 受击 stats 修正或条件查询 /
//   vmt94·vmt98 附加槽（多转发到分区 1 的状态初始化器）。
// 概率掷统一形态：srand 种子化（部分用屏幕坐标混熵）→ rand()%100 < N。
// ============

// 0x514B80 sub_514B80
// ------------------------------------------------------------
// CNEquipmentSchwarzKreisCoat 构造器（黑圈外套，CNSpecificStateEquipment 系）

uint32_t */*thiscall*/ sub_514B80(uint32_t *this, char ArgList, int nArg3, int nArg4, int nArg5)
{
  sub_514350((int)this, ArgList, nArg3, nArg4, nArg5);
  *this = &vftbl_CNEquipmentSchwarzKreisCoat;
  return this;
}



// ------------------------------------------------------------
// 0x514BB0 CNEquipmentSchwarzKreisCoat__vmt9C
// ------------------------------------------------------------
// CNEquipmentSchwarzKreisCoat__vmt9C 受击触发：防篡改 +1252 门 → RTDynamicCast 宿主→CNSwordman（剑士限定）
// && 宿主+8272==2（剑士子状态）→ 委托 CNSpecificStateEquipment__vmt9C 基类效果

int /*thiscall*/ CNEquipmentSchwarzKreisCoat__vmt9C(char *this, int nArg2)
{
  int result; // eax
  int pThis_D4; // eax

  if ( sub_41C5A0(this + 1252) == 0
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this)) != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    result = __RTDynamicCast(pThis_D4, 0, &IRDActiveObject `RTTI Type Descriptor', &CNSwordman `RTTI Type Descriptor', 0);
    if ( result != 0 && *(uint32_t *)(result + 8272) == 2 )
      return CNSpecificStateEquipment__vmt9C(nArg2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x514C20 CNEquipmentSchwarzKreisCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentSchwarzKreisCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentSchwarzKreisCoat__vmt4(void *Block, char pszArg2)
{
  sub_514C50();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x514C50 sub_514C50
// ------------------------------------------------------------
// CNEquipmentSchwarzKreisCoat 析构基座 → CNSpecificStateEquipment 析构

int /*thiscall*/ sub_514C50(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentSchwarzKreisCoat;
  return sub_5143E0(this);
}



// ------------------------------------------------------------
// 0x514C60 sub_514C60
// ------------------------------------------------------------
// CNEquipmentJetBlackBertesCoat 构造器（漆黑贝尔特斯外套）

uint32_t */*thiscall*/ sub_514C60(uint32_t *this, char ArgList, int nArg3, int nArg4, int nArg5)
{
  sub_514350((int)this, ArgList, nArg3, nArg4, nArg5);
  *this = &vftbl_CNEquipmentJetBlackBertesCoat;
  return this;
}



// ------------------------------------------------------------
// 0x514C90 CNEquipmentJetBlackBertesCoat__vmt8C
// ------------------------------------------------------------
// CNEquipmentJetBlackBertesCoat__vmt8C 受击触发：存活 → srand((屏幕+116/112 混合+宿主坐标)混熵) rand%100<2（2%）
// → attackinfo+20==2（暗属性伤害）→ sub_49C620(1,1,0) + sub_49C5F0(1,0,0,10000)【自机状态施加，语义待验证】

int /*thiscall*/ CNEquipmentJetBlackBertesCoat__vmt8C(char *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_D4; // eax
  int result; // eax
  int v8; // edi
  int v9; // ebx
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pThis_D44; // eax
  int v13; // eax
  int nRand; // eax
  int v15; // et2
  int v16; // [esp+4h] [ebp-8h]
  int v17; // [esp+8h] [ebp-4h]

  pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
    v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
    pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 120))(pThis_D42);
    pThis_D43 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 124))(pThis_D43);
    pThis_D44 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 52))(pThis_D44);
    srand((v9 + v16) * (v8 + v17 + v13));
    nRand = rand();
    v15 = nRand % 100;
    result = nRand / 100;
    if ( v15 < 2
      && (sub_41C5A0(this + 1252) == 0
       || (uint8_t)(result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this)) != 0) )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
      if ( *(uint32_t *)(result + 20) == 2 )
      {
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        sub_49C620(1, 1, 0);
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        return sub_49C5F0(1, 0, 0, 10000);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x514DA0 CNEquipmentJetBlackBertesCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentJetBlackBertesCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentJetBlackBertesCoat__vmt4(void *Block, char pszArg2)
{
  sub_514DD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x514DD0 sub_514DD0
// ------------------------------------------------------------
// CNEquipmentJetBlackBertesCoat 析构基座

int /*thiscall*/ sub_514DD0(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentJetBlackBertesCoat;
  return sub_5143E0(this);
}



// ------------------------------------------------------------
// 0x514DE0 sub_514DE0
// ------------------------------------------------------------
// CNEquipmentBasaltMarkCoat 构造器（玄武纹外套，CNEventEquipment 系）

uint32_t */*thiscall*/ sub_514DE0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentBasaltMarkCoat;
  return this;
}



// ------------------------------------------------------------
// 0x514E10 CNEquipmentBasaltMarkCoat__vmt8C
// ------------------------------------------------------------
// CNEquipmentBasaltMarkCoat__vmt8C 受击触发：防篡改+1252 门 → attackinfo+20==0（物理）&& 存活
// && rand%100<10（10%）→ vt+580(48001,10,0,…,4,0,0,0) 施加状态 48001（级 10）【状态语义待验证】

int /*thiscall*/ CNEquipmentBasaltMarkCoat__vmt8C(char *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int pThis_D4; // eax
  int nRand; // eax
  int v9; // et2
  int pThis_D42; // eax

  if ( sub_41C5A0(this + 1252) == 0
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this)) != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
    if ( *(uint32_t *)(result + 20) == 0 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
      if ( (uint8_t)result != 0 )
      {
        nRand = rand();
        v9 = nRand % 100;
        result = nRand / 100;
        if ( v9 < 10 )
        {
          pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          return (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pThis_D42 + 580))(
                   pThis_D42,
                   48001,
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
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x514EB0 CNEquipmentBasaltMarkCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentBasaltMarkCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentBasaltMarkCoat__vmt4(void *Block, char pszArg2)
{
  sub_514EE0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x514EE0 sub_514EE0
// ------------------------------------------------------------
// CNEquipmentBasaltMarkCoat 析构基座

int /*thiscall*/ sub_514EE0(void **this)
{
  *this = &vftbl_CNEquipmentBasaltMarkCoat;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x514EF0 sub_514EF0
// ------------------------------------------------------------
// CNEquipmentDualBowGun 构造器（双弩枪）

uint32_t */*thiscall*/ sub_514EF0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentDualBowGun;
  return this;
}



// ------------------------------------------------------------
// 0x514F20 CNEquipmentDualBowGun__vmt88
// ------------------------------------------------------------
// CNEquipmentDualBowGun__vmt88 攻击触发：条件码 vt+40(17)（P25 玩家门）→ 存活 && rand%100<1（1%）
// → rand()%100 与 50 比较选 42003/42004 → 命中盒中心 ±rand()%60-30 三轴抖动 → sub_605840 包装 →
// sub_4E4A50(宿主, 42003|42004, 20, x,y,z,1,0,对象,组)（追加投掷物事件）

int /*thiscall*/ CNEquipmentDualBowGun__vmt88(void *this, int nArg2, int pArg3, int nArg4, int nArg5, int nArg6)
{
  int pObj; // esi
  int result; // eax
  int pThis_D4; // eax
  int nRand; // eax
  int v11; // et2
  int nRand2; // eax
  bool v13; // sf
  bool v14; // of
  float v15; // ecx
  float v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // ebx
  int pThis_D42; // eax
  int v22; // [esp-20h] [ebp-40h]
  int v23; // [esp-1Ch] [ebp-3Ch]
  int v24; // [esp-18h] [ebp-38h]
  int nArg22; // [esp-Ch] [ebp-2Ch]
  int v26; // [esp-8h] [ebp-28h]
  float v27; // [esp+8h] [ebp-18h] BYREF
  float v28; // [esp+Ch] [ebp-14h]
  float v29; // [esp+10h] [ebp-10h]
  int v30; // [esp+14h] [ebp-Ch]
  int v31; // [esp+18h] [ebp-8h]
  int v32; // [esp+1Ch] [ebp-4h]

  pObj = nArg2;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
    if ( (uint8_t)result != 0 )
    {
      sub_432FA0();
      nRand = rand();
      v11 = nRand % 100;
      result = nRand / 100;
      if ( v11 < 1 )
      {
        nRand2 = rand();
        nArg2 = 0;
        v14 = __OFSUB__(nRand2 % 100, 50);
        v13 = nRand2 % 100 - 50 < 0;
        v15 = *(float *)(pArg3 + 4);
        v27 = *(float *)pArg3;
        v16 = *(float *)(pArg3 + 8);
        v28 = v15;
        v17 = *(uint32_t *)(pArg3 + 12);
        v29 = v16;
        v18 = *(uint32_t *)(pArg3 + 16);
        v30 = v17;
        v19 = *(uint32_t *)(pArg3 + 20);
        v20 = (v13 ^ v14) + 42003;
        v31 = v18;
        v32 = v19;
        pArg3 = rand() % 60 - 30;
        v27 = (double)pArg3 + v27;
        pArg3 = rand() % 60 - 30;
        v28 = (double)pArg3 + v28;
        pArg3 = rand() % 60 - 30;
        v29 = (double)pArg3 + v29;
        v26 = sub_605840(&nArg2, pObj, &v27, 1);
        nArg22 = nArg2;
        v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
        v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        return sub_4E4A50(pThis_D42, v20, 20, v22, v23, v24, 1, 0, nArg22, v26);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x515070 CNEquipmentDualBowGun__vmt4
// ------------------------------------------------------------
// CNEquipmentDualBowGun__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentDualBowGun__vmt4(void *Block, char pszArg2)
{
  sub_5150A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5150A0 sub_5150A0
// ------------------------------------------------------------
// CNEquipmentDualBowGun 析构基座

int /*thiscall*/ sub_5150A0(void **this)
{
  *this = &vftbl_CNEquipmentDualBowGun;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x5150B0 sub_5150B0
// ------------------------------------------------------------
// CNEquipmentThunderGhostSlashMuske 构造器（雷鬼斩肩甲）

uint32_t */*thiscall*/ sub_5150B0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentThunderGhostSlashMuske;
  return this;
}



// ------------------------------------------------------------
// 0x5150E0 CNEquipmentThunderGhostSlashMuske__vmt88
// ------------------------------------------------------------
// CNEquipmentThunderGhostSlashMuske__vmt88 攻击触发：存活 && rand%100<1（1%）→ 条件码 vt+40(17)
// → sub_4E4A50(宿主, 46001, 5, x,y,z,1,0,0,0)（状态 46001 强度 5【感电类，待验证】）

int /*thiscall*/ CNEquipmentThunderGhostSlashMuske__vmt88(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int pThis_D4; // eax
  int result; // eax
  int nRand; // eax
  int v10; // et2
  int pThis_D42; // eax
  int v12; // [esp-20h] [ebp-24h]
  int v13; // [esp-1Ch] [ebp-20h]
  int v14; // [esp-18h] [ebp-1Ch]

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v10 = nRand % 100;
    result = nRand / 100;
    if ( v10 < 1 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2);
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
        pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        return sub_4E4A50(pThis_D42, 46001, 5, v12, v13, v14, 1, 0, 0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x515170 CNEquipmentThunderGhostSlashMuske__vmt4
// ------------------------------------------------------------
// CNEquipmentThunderGhostSlashMuske__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentThunderGhostSlashMuske__vmt4(void *Block, char pszArg2)
{
  sub_5151A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5151A0 sub_5151A0
// ------------------------------------------------------------
// CNEquipmentThunderGhostSlashMuske 析构基座

int /*thiscall*/ sub_5151A0(void **this)
{
  *this = &vftbl_CNEquipmentThunderGhostSlashMuske;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x5151B0 sub_5151B0
// ------------------------------------------------------------
// CNEquipmentKnuckleofChiefSign 构造器（首领之证拳套）

uint32_t */*thiscall*/ sub_5151B0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentKnuckleofChiefSign;
  return this;
}



// ------------------------------------------------------------
// 0x5151E0 CNEquipmentKnuckleofChiefSign__vmt8C
// ------------------------------------------------------------
// CNEquipmentKnuckleofChiefSign__vmt8C 受击召唤：存活 && rand%100<5（5%）→ 攻击有伤害 && a5==0
// → 怪物ID = rand()%6+5（5..10 随机）→ 与 0x5146B0 同构召唤链（盒随机偏移 → vt+376 → vt+592(1)）

void /*thiscall*/ CNEquipmentKnuckleofChiefSign__vmt8C(int *this, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  int pObj6; // eax
  int pObj5; // eax
  int v8; // eax
  int nRand; // edi
  int *v10; // ebx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // edx
  uint32_t *v17; // eax
  int v18; // esi
  int v19; // edx
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  uint16_t v26[3]; // [esp+4h] [ebp-24h] BYREF
  bool nRand2; // [esp+Ah] [ebp-1Eh]
  char nRand3; // [esp+Bh] [ebp-1Dh]
  uint8_t v29[3]; // [esp+Ch] [ebp-1Ch] BYREF
  int v30; // [esp+Fh] [ebp-19h]
  uint32_t *v31; // [esp+14h] [ebp-14h]
  int pObj2; // [esp+18h] [ebp-10h]
  int pObj3; // [esp+1Ch] [ebp-Ch]
  int pObj; // [esp+20h] [ebp-8h]
  int pObj4; // [esp+24h] [ebp-4h]
  int pObj7; // [esp+3Ch] [ebp+14h]

  pObj6 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj6 + 308))(pObj6) != 0 )
  {
    sub_432FA0();
    if ( rand() % 100 < 5 )
    {
      pObj5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 348))(pObj5);
      if ( (*(uint8_t *)(v8 + 16) != 0 || *(float *)v8 > 0.0) && pszArg5 == 0 )
      {
        nRand = rand() % 6 + 5;
        v26[0] = rand() % 200 + 100;
        v26[1] = rand() % 100 + 50;
        nRand2 = rand() % 2 == 0;
        nRand3 = 3 - (rand() % 2 != 0);
        v29[2] = 0;
        v30 = 0;
        v29[0] = 1;
        v29[1] = 2;
        v26[2] = rand() % 60 + 40;
        v10 = (int *)(*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        v11 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        v12 = *this;
        pObj4 = v11;
        pObj7 = (*(int (/*thiscall*/ **)(int *))(v12 + 212))(this);
        v13 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        v14 = *this;
        pObj = v13;
        pObj3 = (*(int (/*thiscall*/ **)(int *))(v14 + 212))(this);
        v15 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        v16 = *this;
        pObj2 = v15;
        v17 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(v16 + 212))(this);
        v18 = *v17;
        v19 = *v10;
        v31 = v17;
        v20 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, int, uint8_t *, uint32_t))(v19 + 152))(
                v10,
                1,
                v26,
                8,
                0xFFFF,
                0,
                1,
                v29,
                0);
        v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj7 + 192))(pObj7, v20) / 2;
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 128))(pObj4);
        v23 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, v22 + v21);
        v24 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 120))(pObj3, v23 - 1);
        v25 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 376))(pObj2, nRand, v24);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v18 + 592))(v31, 1, v25);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x5153D0 CNEquipmentKnuckleofChiefSign__vmt4
// ------------------------------------------------------------
// CNEquipmentKnuckleofChiefSign__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentKnuckleofChiefSign__vmt4(void *Block, char pszArg2)
{
  sub_515400();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x515400 sub_515400
// ------------------------------------------------------------
// CNEquipmentKnuckleofChiefSign 析构基座

int /*thiscall*/ sub_515400(void **this)
{
  *this = &vftbl_CNEquipmentKnuckleofChiefSign;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x515410 sub_515410
// ------------------------------------------------------------
// CNEquipmentVestofScreamGlass 构造器（惊叫玻璃衣）

uint32_t */*thiscall*/ sub_515410(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentVestofScreamGlass;
  return this;
}



// ------------------------------------------------------------
// 0x515440 CNEquipmentVestofScreamGlass__vmt8C
// ------------------------------------------------------------
// CNEquipmentVestofScreamGlass__vmt8C 受击触发：存活 && rand%100<10（10%）→ 条件码 vt+40(17)
// → sub_4E4A50(宿主, 261, 0, x, y, 0, 1,0,0,0)（状态 261【待验证】）

int /*thiscall*/ CNEquipmentVestofScreamGlass__vmt8C(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_D4; // eax
  int result; // eax
  int nRand; // eax
  int v9; // et2
  int pThis_D42; // edi
  int pThis_D43; // ebx
  int pThis_D44; // eax
  int v13; // [esp-24h] [ebp-28h]
  int v14; // [esp-20h] [ebp-24h]

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v9 = nRand % 100;
    result = nRand / 100;
    if ( v9 < 10 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        pThis_D43 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 124))(pThis_D42);
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 120))(pThis_D43);
        pThis_D44 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        return sub_4E4A50(pThis_D44, 261, 0, v13, v14, 0, 1, 0, 0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5154E0 CNEquipmentVestofScreamGlass__vmt4
// ------------------------------------------------------------
// CNEquipmentVestofScreamGlass__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentVestofScreamGlass__vmt4(void *Block, char pszArg2)
{
  sub_515510();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x515510 sub_515510
// ------------------------------------------------------------
// CNEquipmentVestofScreamGlass 析构基座

int /*thiscall*/ sub_515510(void **this)
{
  *this = &vftbl_CNEquipmentVestofScreamGlass;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x515520 sub_515520
// ------------------------------------------------------------
// CNEquipmentBabyBlue 构造器（淡蓝，CNSpecificEnemyEquipment(1,0) 系）

uint32_t */*thiscall*/ sub_515520(uint32_t *this, char ArgList, int nArg3)
{
  sub_5141B0((int)this, ArgList, nArg3, 1, 0);
  *this = &vftbl_CNEquipmentBabyBlue;
  return this;
}



// ------------------------------------------------------------
// 0x515550 CNEquipmentBabyBlue__vmt130
// ------------------------------------------------------------
// CNEquipmentBabyBlue__vmt130 受击 stats 修正：条件码 vt+40(17) && RTDynamicCast→IRDActiveObject
// && sub_4E5B50 暴击判定门（P12）→ 观察者槽 8（vt+792(8)，docs/15 十八槽）→ 防篡读 stats+112/+42 ×0.2
// → 防篡写 sub_41A590（P24 写侧）入装备加成槽 +1492/+1422

char /*thiscall*/ CNEquipmentBabyBlue__vmt130(void *this, int nArg2)
{
  int v3; // edi
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pObj2; // eax
  int v8; // eax
  uint64_t v9; // rax
  int pThis_D44; // eax
  int pObj; // eax
  int v12; // eax
  uint64_t v13; // rax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 0 )
    return 0;
  v3 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  if ( v3 == 0 )
    return 0;
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  if ( !sub_4E5B50(v3, pThis_D4) )
    return 0;
  pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D42 + 792))(pThis_D42, 8) != 0 )
  {
    pThis_D43 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D43 + 792))(pThis_D43, 8);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 176))(pObj2);
    v9 = (uint64_t)((double)sub_41A5E0(v8 + 112) * 0.2);
    sub_41A590((unsigned int)this + 1492, SHIDWORD(v9), v9);
    pThis_D44 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D44 + 792))(pThis_D44, 8);
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);
    v13 = (uint64_t)((double)sub_41A5E0(v12 + 42) * 0.2);
    sub_41A590((unsigned int)this + 1422, SHIDWORD(v13), v13);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x515670 CNEquipmentBabyBlue__vmt4
// ------------------------------------------------------------
// CNEquipmentBabyBlue__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentBabyBlue__vmt4(void *Block, char pszArg2)
{
  sub_5156A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5156A0 sub_5156A0
// ------------------------------------------------------------
// CNEquipmentBabyBlue 析构基座

int /*thiscall*/ sub_5156A0(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentBabyBlue;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x5156B0 sub_5156B0
// ------------------------------------------------------------
// CNEquipmentMesseQuadratCoat 构造器（梅西二次方外套）

uint32_t */*thiscall*/ sub_5156B0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5141B0((int)this, ArgList, nArg3, 1, 0);
  *this = &vftbl_CNEquipmentMesseQuadratCoat;
  return this;
}



// ------------------------------------------------------------
// 0x5156E0 CNEquipmentMesseQuadratCoat__vmt130
// ------------------------------------------------------------
// CNEquipmentMesseQuadratCoat__vmt130 同 BabyBlue 受击 stats 修正但 ×0.5，写侧为 sub_41C150（P24 写侧包装）

char /*thiscall*/ CNEquipmentMesseQuadratCoat__vmt130(char *this, int nArg2)
{
  int v3; // edi
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pObj2; // eax
  int v8; // eax
  uint64_t v9; // rax
  int pThis_D44; // eax
  int pObj; // eax
  int v12; // eax
  uint64_t v13; // rax

  if ( sub_41C5A0(this + 1252) == 0 || (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this) == 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 0 )
    return 0;
  v3 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  if ( v3 == 0 )
    return 0;
  (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
  pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
  if ( !sub_4E5B50(v3, pThis_D4) )
    return 0;
  pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D42 + 792))(pThis_D42, 8) != 0 )
  {
    pThis_D43 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D43 + 792))(pThis_D43, 8);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 176))(pObj2);
    v9 = (uint64_t)((double)sub_41A5E0(v8 + 112) * 0.5);
    sub_41C150((unsigned int)(this + 1492), SHIDWORD(v9), v9);
    pThis_D44 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D44 + 792))(pThis_D44, 8);
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);
    v13 = (uint64_t)((double)sub_41A5E0(v12 + 42) * 0.5);
    sub_41C150((unsigned int)(this + 1422), SHIDWORD(v13), v13);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x515830 CNEquipmentMesseQuadratCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentMesseQuadratCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentMesseQuadratCoat__vmt4(void *Block, char pszArg2)
{
  sub_515860();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x515860 sub_515860
// ------------------------------------------------------------
// CNEquipmentMesseQuadratCoat 析构基座

int /*thiscall*/ sub_515860(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentMesseQuadratCoat;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x515870 sub_515870
// ------------------------------------------------------------
// CNEquipmentUltraAlloyGoratusCoat 构造器（超合金哥拉图斯外套）

uint32_t */*thiscall*/ sub_515870(uint32_t *this, char ArgList, int nArg3)
{
  sub_5141B0((int)this, ArgList, nArg3, 0, 1);
  *this = &vftbl_CNEquipmentUltraAlloyGoratusCoat;
  return this;
}



// ------------------------------------------------------------
// 0x5158A0 CNEquipmentUltraAlloyGoratusCoat__vmtA4
// ------------------------------------------------------------
// CNEquipmentUltraAlloyGoratusCoat__vmtA4 伤害修正：sub_4E5B50 暴击门 或 a4（背击标志）→ +313 有值
// && vt+224 → 伤害 ×0.5；最终 ×(this+336) 装备系数（重伤减半）

char /*thiscall*/ CNEquipmentUltraAlloyGoratusCoat__vmtA4(float *this, int nArg2, int nArg3, char pszArg4, float *pArg5)
{
  int pThis_D4; // eax
  int pThis_139; // eax

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 212))(this);
  pThis_D4 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 212))(this);
  LOBYTE(pThis_139) = sub_4E5B50(pThis_D4, nArg2);
  if ( pszArg4 != 0 || (uint8_t)pThis_139 != 0 )
  {
    pThis_139 = sub_41C5A0(this + 313);
    if ( pThis_139 != 0 )
    {
      LOBYTE(pThis_139) = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 224))(this);
      if ( (uint8_t)pThis_139 != 0 )
        *pArg5 = *pArg5 * 0.5;
    }
  }
  *pArg5 = *(this + 336) * *pArg5;
  return pThis_139;
}



// ------------------------------------------------------------
// 0x515910 CNEquipmentUltraAlloyGoratusCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentUltraAlloyGoratusCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentUltraAlloyGoratusCoat__vmt4(void *Block, char pszArg2)
{
  sub_515940();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x515940 sub_515940
// ------------------------------------------------------------
// CNEquipmentUltraAlloyGoratusCoat 析构基座

int /*thiscall*/ sub_515940(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentUltraAlloyGoratusCoat;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x515950 sub_515950
// ------------------------------------------------------------
// CNEquipmentBeinenFluchCoat 构造器（拜嫩诅咒外套）

uint32_t */*thiscall*/ sub_515950(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentBeinenFluchCoat;
  return this;
}



// ------------------------------------------------------------
// 0x515980 CNEquipmentBeinenFluchCoat__vmt13C
// ------------------------------------------------------------
// CNEquipmentBeinenFluchCoat__vmt13C 周期 tick：防篡改+1252 && vt+224 → vt+776(4)==1（状态 4 激活）
// → attackinfo+76 [stuck]（P17 硬直率字段）×0.94999999 写回（受击硬直率 -5%）

int /*thiscall*/ CNEquipmentBeinenFluchCoat__vmt13C(char *this, int nArg2, int nArg3, int nArg4)
{
  int result; // eax
  int pThis_D4; // eax
  int pThis_D42; // edi
  int pThis_D43; // esi
  float v9; // [esp+4h] [ebp-4h]

  result = sub_41C5A0(this + 1252);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this);
    if ( (uint8_t)result != 0 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D4 + 776))(pThis_D4, 4);
      if ( (uint8_t)result == 1 )
      {
        pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        pThis_D43 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        v9 = *(float *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 348))(pThis_D42) + 76) * 0.94999999;
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 348))(pThis_D43);
        *(float *)(result + 76) = v9;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x515A10 CNEquipmentBeinenFluchCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentBeinenFluchCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentBeinenFluchCoat__vmt4(void *Block, char pszArg2)
{
  sub_515A40();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x515A40 sub_515A40
// ------------------------------------------------------------
// CNEquipmentBeinenFluchCoat 析构基座

int /*thiscall*/ sub_515A40(void **this)
{
  *this = &vftbl_CNEquipmentBeinenFluchCoat;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x515A50 sub_515A50
// ------------------------------------------------------------
// CNEquipmentGoblinBoneMedal 构造器（哥布林骨勋章）

uint32_t */*thiscall*/ sub_515A50(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentGoblinBoneMedal;
  return this;
}



// ------------------------------------------------------------
// 0x515A80 CNEquipmentGoblinBoneMedal__vmt88
// ------------------------------------------------------------
// CNEquipmentGoblinBoneMedal__vmt88 攻击召唤：sub_432FA0 rand 种子 → 存活 && rand%100<1（1%）
// → 攻击有伤害 && a5==0 → 盒随机偏移 → vt+376(10)（怪物 ID 10）→ vt+592(1) 召唤

void /*thiscall*/ CNEquipmentGoblinBoneMedal__vmt88(int *this, int nArg2, int nArg3, int nArg4, char pszArg5, int nArg6)
{
  int pObj3; // eax
  int pObj5; // eax
  int v9; // eax
  int *v10; // edi
  int pObj7; // ebx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int *v16; // esi
  int v17; // edx
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  uint16_t v24[3]; // [esp+4h] [ebp-20h] BYREF
  bool nRand; // [esp+Ah] [ebp-1Ah]
  char nRand2; // [esp+Bh] [ebp-19h]
  uint8_t v27[3]; // [esp+Ch] [ebp-18h] BYREF
  int v28; // [esp+Fh] [ebp-15h]
  int v29; // [esp+14h] [ebp-10h]
  int pObj6; // [esp+18h] [ebp-Ch]
  int pObj4; // [esp+1Ch] [ebp-8h]
  int pObj; // [esp+20h] [ebp-4h]
  int pObj2; // [esp+38h] [ebp+14h]

  sub_432FA0();
  pObj3 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 308))(pObj3) != 0 && rand() % 100 < 1 )
  {
    pObj5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 348))(pObj5);
    if ( (*(uint8_t *)(v9 + 16) != 0 || *(float *)v9 > 0.0) && pszArg5 == 0 )
    {
      v24[0] = rand() % 200 + 100;
      v24[1] = rand() % 100 + 50;
      nRand = rand() % 2 == 0;
      nRand2 = 3 - (rand() % 2 != 0);
      v27[2] = 0;
      v28 = 0;
      v27[0] = 1;
      v27[1] = 2;
      v24[2] = rand() % 60 + 40;
      v10 = (int *)(*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj7 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj2 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v12 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v13 = *this;
      pObj = v12;
      pObj4 = (*(int (/*thiscall*/ **)(int *))(v13 + 212))(this);
      v14 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v15 = *this;
      pObj6 = v14;
      v16 = (int *)(*(int (/*thiscall*/ **)(int *))(v15 + 212))(this);
      v17 = *v10;
      v29 = *v16;
      v18 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, int, uint8_t *, uint32_t))(v17 + 152))(
              v10,
              1,
              v24,
              8,
              0xFFFF,
              0,
              1,
              v27,
              0);
      v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 192))(pObj2, v18) / 2;
      v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj7 + 128))(pObj7);
      v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 124))(pObj, v20 + v19);
      v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj4 + 120))(pObj4, v21 - 1);
      v23 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj6 + 376))(pObj6, 10, v22);
      (*(void (/*thiscall*/ **)(int *, int, int))(v29 + 592))(v16, 1, v23);
    }
  }
}



// ------------------------------------------------------------
// 0x515C60 CNEquipmentGoblinBoneMedal__vmt4
// ------------------------------------------------------------
// CNEquipmentGoblinBoneMedal__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentGoblinBoneMedal__vmt4(void *Block, char pszArg2)
{
  sub_515C90();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x515C90 sub_515C90
// ------------------------------------------------------------
// CNEquipmentGoblinBoneMedal 析构基座

int /*thiscall*/ sub_515C90(void **this)
{
  *this = &vftbl_CNEquipmentGoblinBoneMedal;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x515CA0 sub_515CA0
// ------------------------------------------------------------
// CNEquipmentGileimo 构造器（吉莱莫）

uint32_t */*thiscall*/ sub_515CA0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentGileimo;
  return this;
}



// ------------------------------------------------------------
// 0x515CD0 CNEquipmentGileimo__vmt8C
// ------------------------------------------------------------
// CNEquipmentGileimo__vmt8C 受击反伤：存活 && rand%100<5（5%）&& 条件码 vt+40(17)
// → vt+628（P14 伤害公式，基准 100）重算 → ×0.1 → 命中盒 ±30 抖动 → sub_4E4A50(宿主, 48011, 反伤值, …)【48011 反伤类，待验证】

int /*thiscall*/ CNEquipmentGileimo__vmt8C(int *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int v6; // eax
  int pObj; // eax
  int result; // eax
  int nRand; // eax
  int v10; // et2
  int pObj3; // esi
  int pObj2; // eax
  float *v13; // edi
  float v14; // edx
  float v15; // ecx
  float v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // [esp-28h] [ebp-50h]
  int v22; // [esp-24h] [ebp-4Ch]
  int v23; // [esp-20h] [ebp-48h]
  int v24; // [esp-1Ch] [ebp-44h]
  int nArg22; // [esp-10h] [ebp-38h]
  int v26; // [esp-Ch] [ebp-34h]
  float v27; // [esp+4h] [ebp-24h] BYREF
  float v28; // [esp+8h] [ebp-20h]
  float v29; // [esp+Ch] [ebp-1Ch]
  int v30; // [esp+10h] [ebp-18h]
  int v31; // [esp+14h] [ebp-14h]
  int v32; // [esp+18h] [ebp-10h]
  int v33; // [esp+1Ch] [ebp-Ch]
  int v34; // [esp+20h] [ebp-8h] BYREF
  char v35; // [esp+27h] [ebp-1h] BYREF

  v6 = *this;
  v34 = 0;
  pObj = (*(int (/*thiscall*/ **)(int *))(v6 + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();
    nRand = rand();
    v10 = nRand % 100;
    result = nRand / 100;
    if ( v10 < 5 )
    {
      pObj3 = nArg2;
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        pObj2 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        v13 = (float *)nArg3;
        nArg2 = (*(int (/*thiscall*/ **)(int, char *, int *, int, int, int, uint32_t))(*(uint32_t *)pObj2 + 628))(
               pObj2,
               &v35,
               &v34,
               100,
               pObj3,
               nArg3,
               0);
        v14 = *v13;
        v15 = v13[2];
        v33 = (uint64_t)((double)nArg2 * 0.1);
        v16 = v13[1];
        v27 = v14;
        v17 = *((uint32_t *)v13 + 3);
        v28 = v16;
        v18 = *((uint32_t *)v13 + 4);
        v29 = v15;
        v19 = *((uint32_t *)v13 + 5);
        nArg2 = 0;
        v30 = v17;
        v31 = v18;
        v32 = v19;
        nArg3 = rand() % 60 - 30;
        v27 = (double)nArg3 + v27;
        nArg3 = rand() % 60 - 30;
        v28 = (double)nArg3 + v28;
        nArg3 = rand() % 60 - 30;
        v29 = (double)nArg3 + v29;
        v26 = sub_605840(&nArg2, pObj3, &v27, 1);
        nArg22 = nArg2;
        v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 128))(pObj3);
        v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);
        v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 120))(pObj3);
        v21 = v33;
        v20 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        return sub_4E4A50(v20, 48011, v21, v22, v23, v24, 1, 0, nArg22, v26);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x515E40 CNEquipmentGileimo__vmt4
// ------------------------------------------------------------
// CNEquipmentGileimo__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentGileimo__vmt4(void *Block, char pszArg2)
{
  sub_515E70();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x515E70 sub_515E70
// ------------------------------------------------------------
// CNEquipmentGileimo 析构基座

int /*thiscall*/ sub_515E70(void **this)
{
  *this = &vftbl_CNEquipmentGileimo;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x515E80 sub_515E80
// ------------------------------------------------------------
// CNEquipmentSteelListguard 构造器（钢制利斯特护具）

uint32_t */*thiscall*/ sub_515E80(uint32_t *this, char ArgList, int nArg3, char pszArg4, char pszArg5)
{
  sub_5141B0((int)this, ArgList, nArg3, pszArg4, pszArg5);
  *this = &vftbl_CNEquipmentSteelListguard;
  return this;
}



// ------------------------------------------------------------
// 0x515EB0 CNEquipmentSteelListguard__vmtA4
// ------------------------------------------------------------
// CNEquipmentSteelListguard__vmtA4 伤害修正：a4（背击标志）→ ×0.69999999（背刺减伤 30%）；×(this+336) 装备系数

float */*thiscall*/ CNEquipmentSteelListguard__vmtA4(float *this, int nArg2, int nArg3, char pszArg4, float *pArg5)
{
  float *result; // eax

  result = pArg5;
  if ( pszArg4 != 0 )
    *pArg5 = *pArg5 * 0.69999999;
  *pArg5 = *(this + 336) * *pArg5;
  return result;
}



// ------------------------------------------------------------
// 0x515EE0 CNEquipmentSteelListguard__vmt4
// ------------------------------------------------------------
// CNEquipmentSteelListguard__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentSteelListguard__vmt4(void *Block, char pszArg2)
{
  sub_515F10();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x515F10 sub_515F10
// ------------------------------------------------------------
// CNEquipmentSteelListguard 析构基座

int /*thiscall*/ sub_515F10(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentSteelListguard;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x515F20 sub_515F20
// ------------------------------------------------------------
// CNEquipmentHalgisBoneRing 构造器（哈尔吉斯骨戒）

uint32_t */*thiscall*/ sub_515F20(uint32_t *this, char ArgList, int nArg3)
{
  sub_5141B0((int)this, ArgList, nArg3, 1, 0);
  *this = &vftbl_CNEquipmentHalgisBoneRing;
  return this;
}



// ------------------------------------------------------------
// 0x515F50 CNEquipmentHalgisBoneRing__vmt130
// ------------------------------------------------------------
// CNEquipmentHalgisBoneRing__vmt130 受击 stats 修正（同 BabyBlue ×0.2 族，观察者槽 8 + 防篡读写 P24）

char /*thiscall*/ CNEquipmentHalgisBoneRing__vmt130(void *this, int nArg2)
{
  int v3; // edi
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pObj2; // eax
  int v8; // eax
  uint64_t v9; // rax
  int pThis_D44; // eax
  int pObj; // eax
  int v12; // eax
  uint64_t v13; // rax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 0 )
    return 0;
  v3 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  if ( v3 == 0 )
    return 0;
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  if ( !sub_4E5B50(v3, pThis_D4) )
    return 0;
  pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D42 + 792))(pThis_D42, 8) != 0 )
  {
    pThis_D43 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D43 + 792))(pThis_D43, 8);
    v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 176))(pObj2);
    v9 = (uint64_t)((double)sub_41A5E0(v8 + 112) * 0.5);
    sub_41A590((unsigned int)this + 1492, SHIDWORD(v9), v9);
    pThis_D44 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D44 + 792))(pThis_D44, 8);
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);
    v13 = (uint64_t)((double)sub_41A5E0(v12 + 42) * 0.5);
    sub_41A590((unsigned int)this + 1422, SHIDWORD(v13), v13);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x516070 CNEquipmentHalgisBoneRing__vmt4
// ------------------------------------------------------------
// CNEquipmentHalgisBoneRing__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentHalgisBoneRing__vmt4(void *Block, char pszArg2)
{
  sub_5160A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5160A0 sub_5160A0
// ------------------------------------------------------------
// CNEquipmentHalgisBoneRing 析构基座

int /*thiscall*/ sub_5160A0(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentHalgisBoneRing;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x5160B0 sub_5160B0
// ------------------------------------------------------------
// CNEquipmentVestofTauMane 构造器（牛头王鬃毛衣）

uint32_t */*thiscall*/ sub_5160B0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentVestofTauMane;
  return this;
}



// ------------------------------------------------------------
// 0x5160E0 CNEquipmentVestofTauMane__vmt8C
// ------------------------------------------------------------
// CNEquipmentVestofTauMane__vmt8C 受击触发（74 行：概率掷 → 效果施加，族模式同 0x5146B0/0x5151E0）

void /*thiscall*/ CNEquipmentVestofTauMane__vmt8C(int *this, int nArg2, int nArg3, int nArg4, char pszArg5)
{
  int pObj4; // eax
  int v7; // eax
  int *v8; // edi
  int pObj; // ebx
  int v10; // eax
  int v11; // edx
  int *v12; // esi
  int v13; // edx
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  uint16_t v20[3]; // [esp+4h] [ebp-1Ch] BYREF
  bool nRand; // [esp+Ah] [ebp-16h]
  char nRand2; // [esp+Bh] [ebp-15h]
  uint8_t v23[3]; // [esp+Ch] [ebp-14h] BYREF
  int v24; // [esp+Fh] [ebp-11h]
  int v25; // [esp+14h] [ebp-Ch]
  int pObj2; // [esp+18h] [ebp-8h]
  int pObj3; // [esp+1Ch] [ebp-4h]
  int pObj6; // [esp+28h] [ebp+8h]
  int pObj5; // [esp+34h] [ebp+14h]

  sub_432FA0();
  pObj4 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 308))(pObj4) != 0 && rand() % 100 < 5 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
    if ( (*(uint8_t *)(v7 + 16) != 0 || *(float *)v7 > 0.0)
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2) == nArg2
      && pszArg5 == 0 )
    {
      v20[0] = rand() % 200 + 100;
      v20[1] = rand() % 100 + 50;
      nRand = rand() % 2 == 0;
      nRand2 = 3 - (rand() % 2 != 0);
      v23[2] = 0;
      v24 = 0;
      v23[0] = 1;
      v23[1] = 2;
      v20[2] = rand() % 60 + 40;
      v8 = (int *)(*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj6 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      pObj3 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v10 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      v11 = *this;
      pObj2 = v10;
      v12 = (int *)(*(int (/*thiscall*/ **)(int *))(v11 + 212))(this);
      v13 = *v8;
      v25 = *v12;
      v14 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, int, uint8_t *, uint32_t))(v13 + 152))(
              v8,
              1,
              v20,
              8,
              0xFFFF,
              0,
              1,
              v23,
              0);
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 192))(pObj5, v14) / 2;
      v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
      v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj6 + 124))(pObj6, v16 + v15);
      v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 120))(pObj3, v17 - 1);
      v19 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj2 + 376))(pObj2, 15, v18);
      (*(void (/*thiscall*/ **)(int *, int, int))(v25 + 592))(v12, 14, v19);
    }
  }
}



// ------------------------------------------------------------
// 0x5162C0 CNEquipmentVestofTauMane__vmt4
// ------------------------------------------------------------
// CNEquipmentVestofTauMane__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentVestofTauMane__vmt4(void *Block, char pszArg2)
{
  sub_5162F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5162F0 sub_5162F0
// ------------------------------------------------------------
// CNEquipmentVestofTauMane 析构基座

int /*thiscall*/ sub_5162F0(void **this)
{
  *this = &vftbl_CNEquipmentVestofTauMane;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x516300 sub_516300
// ------------------------------------------------------------
// CNEquipmentEmbossingShoulderPad 构造器（压纹肩垫）

uint32_t */*thiscall*/ sub_516300(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentEmbossingShoulderPad;
  return this;
}



// ------------------------------------------------------------
// 0x516330 CNEquipmentEmbossingShoulderPad__vmtA4
// ------------------------------------------------------------
// CNEquipmentEmbossingShoulderPad__vmtA4 伤害修正：a2 vt+368()==0 反向门 → 系数修正（×this+336）

float */*thiscall*/ CNEquipmentEmbossingShoulderPad__vmtA4(float *this, int nArg2, int nArg3, int nArg4, float *pArg5)
{
  bool v6; // zf
  float *result; // eax

  v6 = (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 368))(nArg2) == 0;
  result = pArg5;
  if ( !v6 )
    *pArg5 = *pArg5 * 0.69999999;
  *pArg5 = *(this + 336) * *pArg5;
  return result;
}



// ------------------------------------------------------------
// 0x516370 CNEquipmentEmbossingShoulderPad__vmt4
// ------------------------------------------------------------
// CNEquipmentEmbossingShoulderPad__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentEmbossingShoulderPad__vmt4(void *Block, char pszArg2)
{
  sub_5163A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5163A0 sub_5163A0
// ------------------------------------------------------------
// CNEquipmentEmbossingShoulderPad 析构基座

int /*thiscall*/ sub_5163A0(void **this)
{
  *this = &vftbl_CNEquipmentEmbossingShoulderPad;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x5163B0 sub_5163B0
// ------------------------------------------------------------
// CNEquipmentHeavyResponsibility 构造器（沉重责任）：+364 状态槽清零

uint32_t */*thiscall*/ sub_5163B0(uint32_t *this, char ArgList, int nArg3)
{
  int v4; // eax
  int v5; // eax

  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentHeavyResponsibility;
  *(this + 364) = 0;
  *(this + 335) = 500;
  if ( CNRDEquipment__vmtD4(this) != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
    v5 = sub_699000(v4 + 36);  // 【clock_now(clk)】
  }
  else
  {
    v5 = 0;
  }
  *(this + 334) = v5;
  return this;
}



// ------------------------------------------------------------
// 0x516440 CNEquipmentHeavyResponsibility__vmt12C
// ------------------------------------------------------------
// CNEquipmentHeavyResponsibility__vmt12C 周期 tick（47 行：冷却计时 + 状态维持）

int /*thiscall*/ CNEquipmentHeavyResponsibility__vmt12C(uint32_t *this)
{
  int result; // eax
  int fld_e364; // ecx
  int pObj; // eax
  int fld_e3642; // edi
  int fld_e3643; // edi
  int v7; // eax
  int v8; // eax
  float v9; // [esp+0h] [ebp-1Ch]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
  if ( result != 0 )
  {
    result = sub_456390((char *)dword_8F850C, 0);
    fld_e364 = *(this + 364);
    if ( result <= 1 )
    {
      if ( fld_e364 != 0 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 80))(fld_e364);
        if ( (uint8_t)result != 0 )
          return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 364) + 76))(*(this + 364), 0);
      }
    }
    else if ( fld_e364 == 0 || (uint8_t)(result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 80))(fld_e364)) == 0 )
    {
      if ( *(this + 364) == 0 )
      {
        if ( operator new(0x7Cu) != nullptr )
          pObj = sub_4B3C90(0, 1);
        else
          pObj = 0;
        *(this + 364) = pObj;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
      }
      (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 364) + 124))(*(this + 364));
      fld_e3642 = *(uint32_t *)*(this + 364);
      v9 = (float)(10 * sub_456390((char *)dword_8F850C, 0) - 10);
      (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t))(fld_e3642 + 120))(*(this + 364), 5, 1, LODWORD(v9));
      fld_e3643 = *(uint32_t *)*(this + 364);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int))(*this + 212))(this, 0, 0, 0, -1);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 212))(this, v7);
      return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e3643 + 56))(*(this + 364), v8);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x516590 CNEquipmentHeavyResponsibility__vmt4
// ------------------------------------------------------------
// CNEquipmentHeavyResponsibility__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentHeavyResponsibility__vmt4(void *Block, char pszArg2)
{
  sub_5165C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5165C0 sub_5165C0
// ------------------------------------------------------------
// CNEquipmentHeavyResponsibility 析构基座（连带 CNEquipmentPureGuardian__vmt13C 卸状态）

int /*thiscall*/ sub_5165C0(void **this)
{
  *this = &vftbl_CNEquipmentHeavyResponsibility;
  CNEquipmentPureGuardian__vmt13C();
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x516610 sub_516610
// ------------------------------------------------------------
// CNEquipmentSnakeArmlet 构造器（蛇手镯）

uint32_t */*thiscall*/ sub_516610(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentSnakeArmlet;
  return this;
}



// ------------------------------------------------------------
// 0x516640 CNEquipmentSnakeArmlet__vmt120
// ------------------------------------------------------------
// CNEquipmentSnakeArmlet__vmt120 事件处理：按 a2-2 分支（20 行）

int /*thiscall*/ CNEquipmentSnakeArmlet__vmt120(void *this, int nArg2, int nArg3)
{
  int result; // eax
  int pThis_D4; // eax
  int pObj; // esi
  uint64_t v6; // rax

  result = nArg2 - 2;
  if ( nArg2 == 2 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D4 + 772))(pThis_D4, 2);
    pObj = result;
    if ( result != 0 )
    {
      v6 = (uint64_t)((double)*(unsigned int *)(result + 92) * 0.5);
      return (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pObj + 84))(pObj, HIDWORD(v6), v6);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x516690 CNEquipmentSnakeArmlet__vmt4
// ------------------------------------------------------------
// CNEquipmentSnakeArmlet__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentSnakeArmlet__vmt4(void *Block, char pszArg2)
{
  sub_5166C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5166C0 sub_5166C0
// ------------------------------------------------------------
// CNEquipmentSnakeArmlet 析构基座

int /*thiscall*/ sub_5166C0(void **this)
{
  *this = &vftbl_CNEquipmentSnakeArmlet;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x5166D0 sub_5166D0
// ------------------------------------------------------------
// CNEquipmentDressofEternalFlame 构造器（永恒之焰长裙）

uint32_t */*thiscall*/ sub_5166D0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentDressofEternalFlame;
  return this;
}



// ------------------------------------------------------------
// 0x516700 CNEquipmentDressofEternalFlame__vmt8C
// ------------------------------------------------------------
// CNEquipmentDressofEternalFlame__vmt8C 受击触发（39 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentDressofEternalFlame__vmt8C(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_D4; // eax
  int result; // eax
  int nRand; // eax
  int v9; // et2
  int pObj; // esi
  int pThis_D42; // eax
  int v12; // [esp-20h] [ebp-24h]
  int v13; // [esp-1Ch] [ebp-20h]
  int v14; // [esp-18h] [ebp-1Ch]
  int nArg22; // [esp-Ch] [ebp-10h]
  int v16; // [esp-8h] [ebp-Ch]

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v9 = nRand % 100;
    result = nRand / 100;
    if ( v9 < 10 )
    {
      pObj = nArg2;
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        nArg2 = 0;
        v16 = sub_605840(&nArg2, pObj, nArg3, 1);
        nArg22 = nArg2;
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        return sub_4E4A50(pThis_D42, 40002, 1, v12, v13, v14, 1, 0, nArg22, v16);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5167A0 CNEquipmentDressofEternalFlame__vmt4
// ------------------------------------------------------------
// CNEquipmentDressofEternalFlame__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentDressofEternalFlame__vmt4(void *Block, char pszArg2)
{
  sub_5167D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5167D0 sub_5167D0
// ------------------------------------------------------------
// CNEquipmentDressofEternalFlame 析构基座

int /*thiscall*/ sub_5167D0(void **this)
{
  *this = &vftbl_CNEquipmentDressofEternalFlame;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x5167E0 sub_5167E0
// ------------------------------------------------------------
// CNEquipmentFlammSkulder 构造器（弗拉姆肩甲）

uint32_t */*thiscall*/ sub_5167E0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentFlammSkulder;
  return this;
}



// ------------------------------------------------------------
// 0x516810 CNEquipmentFlammSkulder__vmt8C
// ------------------------------------------------------------
// CNEquipmentFlammSkulder__vmt8C 受击触发（68 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentFlammSkulder__vmt8C(void *this, int nArg2, int pArg3, int nArg4, int nArg5)
{
  int pThis_D4; // eax
  int result; // eax
  int nRand; // eax
  int v9; // et2
  int pObj; // esi
  float v11; // edx
  float v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int pThis_D42; // eax
  int v17; // [esp-20h] [ebp-3Ch]
  int v18; // [esp-1Ch] [ebp-38h]
  int v19; // [esp-18h] [ebp-34h]
  int nArg22; // [esp-Ch] [ebp-28h]
  int v21; // [esp-8h] [ebp-24h]
  float v22; // [esp+4h] [ebp-18h] BYREF
  float v23; // [esp+8h] [ebp-14h]
  float v24; // [esp+Ch] [ebp-10h]
  int v25; // [esp+10h] [ebp-Ch]
  int v26; // [esp+14h] [ebp-8h]
  int v27; // [esp+18h] [ebp-4h]

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();
    nRand = rand();
    v9 = nRand % 100;
    result = nRand / 100;
    if ( v9 < 8 )
    {
      pObj = nArg2;
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        v11 = *(float *)(pArg3 + 4);
        v22 = *(float *)pArg3;
        v12 = *(float *)(pArg3 + 8);
        v23 = v11;
        v13 = *(uint32_t *)(pArg3 + 12);
        v24 = v12;
        v14 = *(uint32_t *)(pArg3 + 16);
        v25 = v13;
        v15 = *(uint32_t *)(pArg3 + 20);
        nArg2 = 0;
        v26 = v14;
        v27 = v15;
        pArg3 = rand() % 60 - 30;
        v22 = (double)pArg3 + v22;
        pArg3 = rand() % 60 - 30;
        v23 = (double)pArg3 + v23;
        pArg3 = rand() % 60 - 30;
        v24 = (double)pArg3 + v24;
        v21 = sub_605840(&nArg2, pObj, &v22, 1);
        nArg22 = nArg2;
        v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        return sub_4E4A50(pThis_D42, 42004, 50, v17, v18, v19, 1, 0, nArg22, v21);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x516940 CNEquipmentFlammSkulder__vmt4
// ------------------------------------------------------------
// CNEquipmentFlammSkulder__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentFlammSkulder__vmt4(void *Block, char pszArg2)
{
  sub_516970();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x516970 sub_516970
// ------------------------------------------------------------
// CNEquipmentFlammSkulder 析构基座

int /*thiscall*/ sub_516970(void **this)
{
  *this = &vftbl_CNEquipmentFlammSkulder;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x516980 sub_516980
// ------------------------------------------------------------
// CNEquipmentKaloaSnake 构造器（卡洛亚之蛇）

uint32_t */*thiscall*/ sub_516980(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentKaloaSnake;
  return this;
}



// ------------------------------------------------------------
// 0x5169B0 CNEquipmentKaloaSnake__vmt8C
// ------------------------------------------------------------
// CNEquipmentKaloaSnake__vmt8C 受击触发（35 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentKaloaSnake__vmt8C(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_D4; // eax
  int result; // eax
  int nRand; // eax
  int v9; // et2
  int pThis_D42; // eax
  int v11; // [esp-20h] [ebp-24h]
  int v12; // [esp-1Ch] [ebp-20h]
  int v13; // [esp-18h] [ebp-1Ch]
  int v14; // [esp-14h] [ebp-18h]

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v9 = nRand % 100;
    result = nRand / 100;
    if ( v9 < 5 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 152))(nArg2);
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2);
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
        pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        return sub_4E4A50(pThis_D42, 48003, 10, v11, v12, v13, v14, 0, 0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x516A50 CNEquipmentKaloaSnake__vmt4
// ------------------------------------------------------------
// CNEquipmentKaloaSnake__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentKaloaSnake__vmt4(void *Block, char pszArg2)
{
  sub_516A80();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x516A80 sub_516A80
// ------------------------------------------------------------
// CNEquipmentKaloaSnake 析构基座

int /*thiscall*/ sub_516A80(void **this)
{
  *this = &vftbl_CNEquipmentKaloaSnake;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x516A90 sub_516A90
// ------------------------------------------------------------
// CNEquipmentHatefulBeastCoat 构造器（憎恨兽外套）：+1456 nengine__CNTimer + +1460 状态位

int /*thiscall*/ sub_516A90(int this, char ArgList, int nArg3)
{
  sub_5144A0((uint32_t *)this, ArgList, nArg3);
  *(uint32_t *)this = &vftbl_CNEquipmentHatefulBeastCoat;
  *(uint8_t *)(this + 1460) = 0;
  *(uint32_t *)(this + 1456) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 1464) = 0;
  *(uint8_t *)(this + 1468) = 1;
  *(uint8_t *)(this + 1470) = 0;
  *(uint8_t *)(this + 1469) = 0;
  *(uint32_t *)(this + 1480) = 0;
  *(uint32_t *)(this + 1476) = 0;
  *(uint32_t *)(this + 1472) = 0;
  sub_510A30((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x516B30 CNEquipmentHatefulBeastCoat__vmt98
// ------------------------------------------------------------
// CNEquipmentHatefulBeastCoat__vmt98 附加槽：转发 sub_516B40（+371 状态销毁）

// attributes: thunk
int CNEquipmentHatefulBeastCoat__vmt98()
{
  return sub_516B40();
}



// ------------------------------------------------------------
// 0x516B40 sub_516B40
// ------------------------------------------------------------
// 状态卸载（HatefulBeastCoat）：+371 状态对象 vt+0(1) 销毁

int /*thiscall*/ sub_516B40(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e371)(uint32_t, int); // ecx
  int result; // eax

  fld_e371 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 371);
  if ( fld_e371 != nullptr )
    result = (**fld_e371)(fld_e371, 1);
  *(this + 371) = 0;
  *(this + 335) = 0;
  *(this + 334) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x516B80 CNEquipmentHatefulBeastCoat__vmt12C
// ------------------------------------------------------------
// CNEquipmentHatefulBeastCoat__vmt12C 周期 tick（41 行：冷却计时 + 状态维持）

char /*thiscall*/ CNEquipmentHatefulBeastCoat__vmt12C(uint32_t *this)
{
  char result; // al
  int fld_e370; // edi
  int pThis_16C; // eax
  int fld_e371; // edx
  int fld_e3712; // edi
  int v7; // eax
  int v8; // eax

  if ( sub_41C5A0(this + 313) == 0 || (result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 224))(this)) != 0 )
  {
    result = *((uint8_t *)this + 1488);
    if ( result != 0 )
    {
      fld_e370 = *(this + 370);
      pThis_16C = sub_699000((int)(this + 364));  // 【clock_now(clk)】
      fld_e371 = *(uint32_t *)*(this + 371);
      if ( pThis_16C >= fld_e370 )
      {
        result = (*(int (**)(void))(fld_e371 + 80))();
        if ( result == 1 )
        {
          result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 371) + 76))(*(this + 371), 0);
          *((uint8_t *)this + 1488) = 0;
        }
      }
      else
      {
        result = (*(int (**)(void))(fld_e371 + 80))();
        if ( result == 0 )
        {
          fld_e3712 = *(uint32_t *)*(this + 371);
          v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int))(*this + 212))(this, 0, 0, 0, -1);
          v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 212))(this, v7);
          return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e3712 + 56))(*(this + 371), v8);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x516C20 CNEquipmentHatefulBeastCoat__vmt88
// ------------------------------------------------------------
// CNEquipmentHatefulBeastCoat__vmt88 攻击触发（48 行：概率掷 → 效果施加）

char /*thiscall*/ CNEquipmentHatefulBeastCoat__vmt88(uint8_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int pThis_D4; // eax
  int v9; // edi
  int v10; // ebx
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pThis_D44; // eax
  int v14; // eax
  int nRand; // eax
  int v16; // et2
  int v18; // [esp+4h] [ebp-4h]
  int v19; // [esp+10h] [ebp+8h]

  if ( sub_41C5A0(this + 1252) == 0
    || (LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 224))(this), (uint8_t)v7 != 0) )
  {
    LOBYTE(v7) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
    if ( (uint8_t)v7 == 1 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
      LOBYTE(v7) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
      if ( (uint8_t)v7 != 0 )
      {
        v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
        v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
        pThis_D42 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
        v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 120))(pThis_D42);
        pThis_D43 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 124))(pThis_D43);
        pThis_D44 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 52))(pThis_D44);
        srand((v10 + v18) * (v9 + v19 + v14));
        nRand = rand();
        v16 = nRand % 100;
        v7 = nRand / 100;
        if ( v16 < 1 )
        {
          *(this + 1488) = 1;
          *(this + 1469) = 0;
          *(this + 1470) = 0;
          LOBYTE(v7) = sub_698F90((int)(this + 1456), 20000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        }
      }
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x516D20 CNEquipmentHatefulBeastCoat__vmt94
// ------------------------------------------------------------
// CNEquipmentHatefulBeastCoat__vmt94 附加槽：转发 sub_510A30（状态初始化器 B）

// attributes: thunk
int /*thiscall*/ CNEquipmentHatefulBeastCoat__vmt94(uint32_t *this)
{
  return sub_510A30(this);
}



// ------------------------------------------------------------
// 0x516D30 CNEquipmentHatefulBeastCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentHatefulBeastCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentHatefulBeastCoat__vmt4(void *Block, char pszArg2)
{
  sub_516D60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x516D60 sub_516D60
// ------------------------------------------------------------
// CNEquipmentHatefulBeastCoat 析构基座：+1484 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_516D60(int this)
{
  void (/*thiscall*/ ***pThis_5CC)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentHatefulBeastCoat;
  pThis_5CC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1484);
  if ( pThis_5CC != nullptr )
    (**pThis_5CC)(pThis_5CC, 1);
  *(uint32_t *)(this + 1484) = 0;
  *(uint32_t *)(this + 1340) = 0;
  *(uint32_t *)(this + 1336) = 0;
  *(uint32_t *)(this + 1456) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1460) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x516DE0 sub_516DE0
// ------------------------------------------------------------
// CNEquipmentMadeInHeaven 构造器（天堂制造）

uint32_t */*thiscall*/ sub_516DE0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentMadeInHeaven;
  return this;
}



// ------------------------------------------------------------
// 0x516E10 CNEquipmentMadeInHeaven__vmt8C
// ------------------------------------------------------------
// CNEquipmentMadeInHeaven__vmt8C 受击触发（56 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentMadeInHeaven__vmt8C(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int pThis_D4; // eax
  int nRand; // eax
  int v9; // et2
  int pThis_D42; // eax
  int v11; // eax
  int *v12; // esi
  int v13; // ebx
  int pThis_D43; // eax
  int v15; // [esp+4h] [ebp-4h]
  int v16; // [esp+10h] [ebp+8h]

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
    if ( (uint8_t)result != 0 )
    {
      nRand = rand();
      v9 = nRand % 100;
      result = nRand / 100;
      if ( v9 < 10 )
      {
        pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 308))(pThis_D42);
        if ( (uint8_t)result != 0 )
        {
          v15 = 0;
          result = sub_456390((char *)dword_8F850C, 0);
          if ( result > 0 )
          {
            v16 = 16;
            do
            {
              v11 = *(uint32_t *)(v16 + dword_8F850C);
              if ( v11 != 0 )
              {
                v12 = *(int **)(v11 + 196);
                v13 = *v12;
                pThis_D43 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 212))(this, 1);
                (*(void (/*thiscall*/ **)(int *, int, int, int))(v13 + 764))(v12, 12, 10, pThis_D43);
              }
              ++v15;
              v16 += 4;
              result = sub_456390((char *)dword_8F850C, 0);
            }
            while ( v15 < result );
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x516EF0 CNEquipmentMadeInHeaven__vmt4
// ------------------------------------------------------------
// CNEquipmentMadeInHeaven__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentMadeInHeaven__vmt4(void *Block, char pszArg2)
{
  sub_516F20();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x516F20 sub_516F20
// ------------------------------------------------------------
// CNEquipmentMadeInHeaven 析构基座

int /*thiscall*/ sub_516F20(void **this)
{
  *this = &vftbl_CNEquipmentMadeInHeaven;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x516F30 sub_516F30
// ------------------------------------------------------------
// CNEquipmentLalaMisYong 构造器（啦啦咪勇）：+1460 nengine__CNTimer

int /*thiscall*/ sub_516F30(int this, char ArgList, int nArg3)
{
  sub_5144A0((uint32_t *)this, ArgList, nArg3);
  *(uint32_t *)this = &vftbl_CNEquipmentLalaMisYong;
  *(uint8_t *)(this + 1464) = 0;
  *(uint32_t *)(this + 1460) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 1468) = 0;
  *(uint8_t *)(this + 1472) = 1;
  *(uint8_t *)(this + 1474) = 0;
  *(uint8_t *)(this + 1473) = 0;
  *(uint32_t *)(this + 1484) = 0;
  *(uint32_t *)(this + 1480) = 0;
  *(uint32_t *)(this + 1476) = 0;
  sub_510B20((uint32_t *)this);
  return this;
}



// ------------------------------------------------------------
// 0x516FD0 CNEquipmentLalaMisYong__vmt98
// ------------------------------------------------------------
// CNEquipmentLalaMisYong__vmt98 附加槽：转发 CNEquipmentPureGuardian__vmt13C（卸状态）

// attributes: thunk
int CNEquipmentLalaMisYong__vmt98()
{
  return CNEquipmentPureGuardian__vmt13C();
}



// ------------------------------------------------------------
// 0x516FE0 CNEquipmentLalaMisYong__vmt88
// ------------------------------------------------------------
// CNEquipmentLalaMisYong__vmt88 攻击触发（44 行：概率掷 → 效果施加）

char /*thiscall*/ CNEquipmentLalaMisYong__vmt88(uint8_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int pThis_D4; // eax
  int v9; // edi
  int v10; // ebx
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pThis_D44; // eax
  int v14; // eax
  int nRand; // eax
  int v16; // et2
  int v18; // [esp+4h] [ebp-4h]
  int v19; // [esp+10h] [ebp+8h]

  LOBYTE(v7) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)v7 == 1 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    LOBYTE(v7) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
    if ( (uint8_t)v7 != 0 )
    {
      v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
      v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
      pThis_D42 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
      v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 120))(pThis_D42);
      pThis_D43 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
      v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 124))(pThis_D43);
      pThis_D44 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
      v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 52))(pThis_D44);
      srand((v10 + v18) * (v9 + v19 + v14));
      nRand = rand();
      v16 = nRand % 100;
      v7 = nRand / 100;
      if ( v16 < 3 )
      {
        *(this + 1488) = 1;
        *(this + 1473) = 0;
        *(this + 1474) = 0;
        LOBYTE(v7) = sub_698F90((int)(this + 1460), 30000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x5170C0 CNEquipmentLalaMisYong__vmt12C
// ------------------------------------------------------------
// CNEquipmentLalaMisYong__vmt12C 周期 tick（30 行）

void /*thiscall*/ CNEquipmentLalaMisYong__vmt12C(uint32_t *this)
{
  int fld_e371; // edi
  int pThis_16D; // eax
  int fld_e364; // ecx
  int fld_e3642; // edi
  int v6; // eax
  int v7; // eax

  if ( *((uint8_t *)this + 1488) == 1 )
  {
    fld_e371 = *(this + 371);
    pThis_16D = sub_699000((int)(this + 365));  // 【clock_now(clk)】
    fld_e364 = *(this + 364);
    if ( pThis_16D >= fld_e371 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 80))(fld_e364) == 1 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 364) + 76))(*(this + 364), 0);
        *((uint8_t *)this + 1488) = 0;
      }
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 80))(fld_e364) == 0 )
    {
      fld_e3642 = *(uint32_t *)*(this + 364);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int))(*this + 212))(this, 0, 0, 0, -1);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 212))(this, v6);
      (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e3642 + 56))(*(this + 364), v7);
    }
  }
}



// ------------------------------------------------------------
// 0x517140 CNEquipmentLalaMisYong__vmt94
// ------------------------------------------------------------
// CNEquipmentLalaMisYong__vmt94 附加槽：转发 sub_510B20（状态初始化器 C）

// attributes: thunk
int /*thiscall*/ CNEquipmentLalaMisYong__vmt94(uint32_t *this)
{
  return sub_510B20(this);
}



// ------------------------------------------------------------
// 0x517150 CNEquipmentLalaMisYong__vmt4
// ------------------------------------------------------------
// CNEquipmentLalaMisYong__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentLalaMisYong__vmt4(void *Block, char pszArg2)
{
  sub_517180();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x517180 sub_517180
// ------------------------------------------------------------
// CNEquipmentLalaMisYong 析构基座：+1456 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_517180(int this)
{
  void (/*thiscall*/ ***pThis_5B0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentLalaMisYong;
  pThis_5B0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1456);
  if ( pThis_5B0 != nullptr )
    (**pThis_5B0)(pThis_5B0, 1);
  *(uint32_t *)(this + 1456) = 0;
  *(uint32_t *)(this + 1340) = 0;
  *(uint32_t *)(this + 1336) = 0;
  *(uint32_t *)(this + 1460) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1464) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x517200 sub_517200
// ------------------------------------------------------------
// CNEquipmentAntiGravityLifter 构造器（反重力升降装置，CNSpecificEnemyEquipment(1,0) 系）

uint32_t */*thiscall*/ sub_517200(uint32_t *this, char ArgList, int nArg3)
{
  sub_5141B0((int)this, ArgList, nArg3, 1, 0);
  *this = &vftbl_CNEquipmentAntiGravityLifter;
  return this;
}



// ------------------------------------------------------------
// 0x517230 CNEquipmentAntiGravityLifter__vmt130
// ------------------------------------------------------------
// CNEquipmentAntiGravityLifter__vmt130 受击 stats 修正（31 行，BabyBlue 族模式）

char /*thiscall*/ CNEquipmentAntiGravityLifter__vmt130(void *this, int nArg2)
{
  int pObj2; // eax
  int pObj; // esi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  double v8; // st7
  int pThis_B0; // eax
  uint64_t v10; // rax
  float v12; // [esp+8h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 0 )
    return 0;
  pObj2 = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
  pObj = pObj2;
  if ( pObj2 == 0 )
    return 0;
  v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 672))(pObj2, 3);
  if ( sub_4B0D20(v5) < 80000 )
    return 0;
  v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 672))(pObj, 3);
  v7 = sub_4B0D20(v6);
  v8 = (double)(int)(uint64_t)sub_4049C0(15.0, 30.0, v7, 200000) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  if ( v8 < 0.15 )
    return 0;
  pThis_B0 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 176))(this);
  v12 = v8;
  v10 = (uint64_t)((double)sub_41A5E0(pThis_B0 + 112) * v12);
  sub_41A590((unsigned int)this + 1492, SHIDWORD(v10), v10);
  return 1;
}



// ------------------------------------------------------------
// 0x517320 CNEquipmentAntiGravityLifter__vmt4
// ------------------------------------------------------------
// CNEquipmentAntiGravityLifter__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentAntiGravityLifter__vmt4(void *Block, char pszArg2)
{
  sub_517350();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x517350 sub_517350
// ------------------------------------------------------------
// CNEquipmentAntiGravityLifter 析构基座

int /*thiscall*/ sub_517350(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentAntiGravityLifter;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x517360 sub_517360
// ------------------------------------------------------------
// CNEquipmentAssaultAttackerCoat 构造器（突击攻击者外套）

uint32_t */*thiscall*/ sub_517360(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentAssaultAttackerCoat;
  return this;
}



// ------------------------------------------------------------
// 0x517390 CNEquipmentAssaultAttackerCoat__vmt8C
// ------------------------------------------------------------
// CNEquipmentAssaultAttackerCoat__vmt8C 受击触发（96 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentAssaultAttackerCoat__vmt8C(char *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // edx
  int pObj; // eax
  int nRand; // eax
  int v10; // et2
  int pObj2; // esi
  int pThis_D4; // eax
  float *v13; // edi
  float v14; // edx
  float v15; // ecx
  float v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  int v20; // edi
  int pThis_D42; // eax
  int v22; // [esp-28h] [ebp-50h]
  int v23; // [esp-24h] [ebp-4Ch]
  int v24; // [esp-20h] [ebp-48h]
  int v25; // [esp-1Ch] [ebp-44h]
  int nArg22; // [esp-10h] [ebp-38h]
  float v27; // [esp+4h] [ebp-24h] BYREF
  float v28; // [esp+8h] [ebp-20h]
  float v29; // [esp+Ch] [ebp-1Ch]
  int v30; // [esp+10h] [ebp-18h]
  int v31; // [esp+14h] [ebp-14h]
  int v32; // [esp+18h] [ebp-10h]
  int v33; // [esp+1Ch] [ebp-Ch]
  int v34; // [esp+20h] [ebp-8h] BYREF
  char v35; // [esp+27h] [ebp-1h] BYREF

  if ( sub_41C5A0(this + 1252) == 0
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this)) != 0 )
  {
    v7 = *(uint32_t *)this;
    v34 = 0;
    pObj = (*(int (/*thiscall*/ **)(char *))(v7 + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);
    if ( (uint8_t)result != 0 )
    {
      sub_432FA0();
      nRand = rand();
      v10 = nRand % 100;
      result = nRand / 100;
      if ( v10 < 4 )
      {
        pObj2 = nArg2;
        result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
        if ( (uint8_t)result != 0 )
        {
          pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          v13 = (float *)nArg3;
          nArg2 = (*(int (/*thiscall*/ **)(int, char *, int *, int, int, int, uint32_t))(*(uint32_t *)pThis_D4 + 628))(
                 pThis_D4,
                 &v35,
                 &v34,
                 100,
                 pObj2,
                 nArg3,
                 0);
          v14 = *v13;
          v15 = v13[2];
          v33 = (uint64_t)((double)nArg2 * 0.1);
          v16 = v13[1];
          v27 = v14;
          v17 = *((uint32_t *)v13 + 3);
          v28 = v16;
          v18 = *((uint32_t *)v13 + 4);
          v29 = v15;
          v19 = *((uint32_t *)v13 + 5);
          nArg2 = 0;
          v30 = v17;
          v31 = v18;
          v32 = v19;
          nArg3 = rand() % 60 - 30;
          v27 = (double)nArg3 + v27;
          nArg3 = rand() % 60 - 30;
          v28 = (double)nArg3 + v28;
          nArg3 = rand() % 60 - 30;
          v29 = (double)nArg3 + v29;
          v20 = sub_605840(&nArg2, pObj2, &v27, 1);
          (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          nArg22 = nArg2;
          v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 128))(pObj2);
          v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 124))(pObj2);
          v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);
          v22 = v33;
          pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          return sub_4E4A50(pThis_D42, 48011, v22, v23, v24, v25, 1, 0, nArg22, v20);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x517530 CNEquipmentAssaultAttackerCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentAssaultAttackerCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentAssaultAttackerCoat__vmt4(void *Block, char pszArg2)
{
  sub_517560();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x517560 sub_517560
// ------------------------------------------------------------
// CNEquipmentAssaultAttackerCoat 析构基座

int /*thiscall*/ sub_517560(void **this)
{
  *this = &vftbl_CNEquipmentAssaultAttackerCoat;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x517570 sub_517570
// ------------------------------------------------------------
// CNEquipmentMagistrate 构造器（行政官）

uint32_t */*thiscall*/ sub_517570(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentMagistrate;
  return this;
}



// ------------------------------------------------------------
// 0x5175A0 CNEquipmentMagistrate__vmt88
// ------------------------------------------------------------
// CNEquipmentMagistrate__vmt88 攻击触发（111 行：概率掷 + 0x517740 表取值 → 效果施加）

int /*thiscall*/ sub_5175A0(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 【CNEquipmentMagistrate__vmt88】
{
  int result; // eax
  int pThis_D4; // eax
  int v9; // edi
  int v10; // ebx
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pThis_D44; // eax
  int v14; // eax
  int nRand; // eax
  int v16; // et2
  int v17; // edi
  int pObj3; // ebx
  int *v19; // edi
  int v20; // ebx
  int pThis_D45; // eax
  int v22; // ecx
  int v23; // esi
  int pObj; // eax
  int pObj4; // eax
  int v26; // [esp+8h] [ebp-8h]
  int v27; // [esp+Ch] [ebp-4h]
  int v28; // [esp+Ch] [ebp-4h]
  int v29; // [esp+Ch] [ebp-4h]
  int pObj2; // [esp+18h] [ebp+8h]
  int v31; // [esp+18h] [ebp+8h]

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    result = __RTDynamicCast(
               nArg2,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
    pObj2 = result;
    if ( result != 0 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
      if ( (uint8_t)result != 0 )
      {
        v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
        v10 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
        pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 120))(pThis_D42);
        pThis_D43 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        v26 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 124))(pThis_D43);
        pThis_D44 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 52))(pThis_D44);
        srand((v10 + v26) * (v9 + v27 + v14));
        nRand = rand();
        v16 = nRand % 100;
        result = nRand / 100;
        if ( v16 < 1 )
        {
          v17 = 0;
          v28 = 0;
          do
          {
            pObj3 = pObj2;
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 776))(pObj2, v17) != 0 )
            {
              v19 = (int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 772))(pObj2, v17);
              v20 = *v19;
              pThis_D45 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
              (*(void (/*thiscall*/ **)(int *, uint32_t, int))(v20 + 4))(v19, 0, pThis_D45);
              pObj3 = pObj2;
              v17 = v28;
            }
            v28 = ++v17;
          }
          while ( v17 < 17 );
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 700))(pObj3);
          v22 = *(uint32_t *)(result + 4);
          v23 = 0;
          if ( v22 != 0 )
          {
            result = (*(uint32_t *)(result + 8) - v22) >> 2;
            v31 = result;
          }
          else
          {
            v31 = 0;
          }
          v29 = 0;
          if ( v31 > 0 )
          {
            do
            {
              pObj = sub_517740(v23);
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 92))(pObj) != 0 )
              {
                pObj4 = sub_517740(v23);
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj4 + 76))(pObj4, 0);
                ++v29;
              }
              ++v23;
            }
            while ( v23 < v31 );
            result = v29;
            if ( v29 > 0 )
              return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 956))(pObj3);
          }
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x517740 sub_517740
// ------------------------------------------------------------
// 表读取器：+1/+2/+3 vector 按 a2 索引取 dword（越界返 0）—— Magistrate 触发表

int /*thiscall*/ sub_517740(uint32_t *this, unsigned int uArg2)
{
  int fld_e1; // edx

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && uArg2 < (*(this + 2) - fld_e1) >> 2 )
    return *(uint32_t *)(fld_e1 + 4 * uArg2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x517770 CNEquipmentMagistrate__vmt4
// ------------------------------------------------------------
// CNEquipmentMagistrate__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentMagistrate__vmt4(void *Block, char pszArg2)
{
  sub_5177A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5177A0 sub_5177A0
// ------------------------------------------------------------
// CNEquipmentMagistrate 析构基座

int /*thiscall*/ sub_5177A0(void **this)
{
  *this = &vftbl_CNEquipmentMagistrate;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x5177B0 sub_5177B0
// ------------------------------------------------------------
// CNEquipmentShootingStarDrop 构造器（流星坠落）

uint32_t */*thiscall*/ sub_5177B0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentShootingStarDrop;
  return this;
}



// ------------------------------------------------------------
// 0x5177E0 CNEquipmentShootingStarDrop__vmt88
// ------------------------------------------------------------
// CNEquipmentShootingStarDrop__vmt88 攻击触发（73 行 userpurge：ecx/esi 寄存器传参，概率掷 → 效果施加）

int /*userpurge*/ CNEquipmentShootingStarDrop__vmt88@<eax>(
        int a1@<ecx>,
        int a2@<esi>,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7)
{
  int result; // eax
  int v10; // esi
  int v11; // eax
  int v12; // eax
  int v13; // et2
  int v14; // eax
  int v15; // eax
  BOOL v16; // ebx
  int v17; // eax
  uint32_t *v18; // eax
  uint32_t *v19; // edi
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v25; // [esp+8h] [ebp-4h]
  int savedregs; // [esp+Ch] [ebp+0h]
  int v27; // [esp+14h] [ebp+8h]
  int v28; // [esp+14h] [ebp+8h]

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a3 + 40))(a3, 17);
  if ( (uint8_t)result != 0 )
  {
    result = __RTDynamicCast(
               a3,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
    v10 = result;
    if ( result != 0 )
    {
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 212))(a1);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 308))(v11);
      if ( (uint8_t)result != 0 )
      {
        v12 = rand();
        v13 = v12 % 100;
        result = v12 / 100;
        if ( v13 < 2 )
        {
          v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 212))(a1, a2);
          v27 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 120))(v14);
          v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a3 + 120))(a3);
          v16 = v27 < v15;
          if ( v27 < v15 )
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 120))(v10) - 500;
          else
            v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 120))(v10) + 500;
          v28 = v17;
          v18 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 212))(a1);
          savedregs = 0;
          v19 = v18;
          v25 = *v18;
          v20 = (*(int (/*thiscall*/ **)(int, BOOL, int, int))(*(uint32_t *)dword_8F82C8 + 28))(dword_8F82C8, v16, 100, 2);
          v21 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v10 + 124))(v10, 48030, 25, v20);
          v22 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 120))(v10, v21);
          v23 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v10 + 124))(v10, 400, v22);
          return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(v25 + 584))(v19, v28, v23);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x517900 CNEquipmentShootingStarDrop__vmt4
// ------------------------------------------------------------
// CNEquipmentShootingStarDrop__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentShootingStarDrop__vmt4(void *Block, char pszArg2)
{
  sub_517930();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x517930 sub_517930
// ------------------------------------------------------------
// CNEquipmentShootingStarDrop 析构基座

int /*thiscall*/ sub_517930(void **this)
{
  *this = &vftbl_CNEquipmentShootingStarDrop;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x517940 sub_517940
// ------------------------------------------------------------
// CNEquipmentFrostbringer 构造器（冰霜使者）

uint32_t */*thiscall*/ sub_517940(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentFrostbringer;
  return this;
}



// ------------------------------------------------------------
// 0x517970 CNEquipmentFrostbringer__vmt88
// ------------------------------------------------------------
// CNEquipmentFrostbringer__vmt88 攻击触发（43 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentFrostbringer__vmt88(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int result; // eax
  int pObj; // esi
  int pThis_D4; // eax
  int nRand; // eax
  int v11; // et2
  int pThis_D42; // eax
  int v13; // [esp-1Ch] [ebp-24h]
  int v14; // [esp-18h] [ebp-20h]
  int v15; // [esp-10h] [ebp-18h]

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    result = __RTDynamicCast(
               nArg2,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
    pObj = result;
    if ( result != 0 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
      if ( (uint8_t)result != 0 )
      {
        nRand = rand();
        v11 = nRand % 100;
        result = nRand / 100;
        if ( v11 < 3 )
        {
          v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 152))(pObj);
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
          pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
          return sub_4E4A50(pThis_D42, 48032, 0, v13, v14, 0, v15, 0, 0, 0);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x517A20 CNEquipmentFrostbringer__vmt4
// ------------------------------------------------------------
// CNEquipmentFrostbringer__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentFrostbringer__vmt4(void *Block, char pszArg2)
{
  sub_517A50();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x517A50 sub_517A50
// ------------------------------------------------------------
// CNEquipmentFrostbringer 析构基座

int /*thiscall*/ sub_517A50(void **this)
{
  *this = &vftbl_CNEquipmentFrostbringer;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x517A60 sub_517A60
// ------------------------------------------------------------
// CNEquipmentBloodsoul 构造器（血魂）

uint32_t */*thiscall*/ sub_517A60(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentBloodsoul;
  return this;
}



// ------------------------------------------------------------
// 0x517A90 CNEquipmentBloodsoul__vmt88
// ------------------------------------------------------------
// CNEquipmentBloodsoul__vmt88 攻击触发（63 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentBloodsoul__vmt88(void *this, void *Block, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int result; // eax
  int v8; // edi
  int pThis_D4; // eax
  int nRand; // eax
  int v11; // et2
  int pThis_D42; // eax
  int pThis_D43; // eax
  int *v14; // edi
  int v15; // ebx
  int pThis_D44; // eax
  int pThis_D45; // eax

  result = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 17);
  if ( (uint8_t)result != 0 )
  {
    result = __RTDynamicCast(
               (int)Block,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
    v8 = result;
    if ( result != 0 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
      if ( (uint8_t)result != 0 )
      {
        nRand = rand();
        v11 = nRand % 100;
        result = nRand / 100;
        if ( v11 < 2 )
        {
          pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 840))(pThis_D42);
          if ( result == 8 || result == 7 || result == 12 )
          {
            pThis_D43 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
            result = (*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pThis_D43 + 8))(pThis_D43, v8, 0);
            if ( result < 128 )
            {
              if ( operator new(0x80u) != nullptr )
                v14 = (int *)sub_4D6810(1112014848, 1000, 1, 1);
              else
                v14 = nullptr;
              v15 = *v14;
              pThis_D44 = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 212))(
                      this,
                      0,
                      0,
                      0,
                      -1);
              pThis_D45 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 212))(this, pThis_D44);
              return (*(int (/*thiscall*/ **)(int *, int))(v15 + 56))(v14, pThis_D45);
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x517BD0 CNEquipmentBloodsoul__vmt4
// ------------------------------------------------------------
// CNEquipmentBloodsoul__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentBloodsoul__vmt4(void *Block, char pszArg2)
{
  sub_517C00();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x517C00 sub_517C00
// ------------------------------------------------------------
// CNEquipmentBloodsoul 析构基座

int /*thiscall*/ sub_517C00(void **this)
{
  *this = &vftbl_CNEquipmentBloodsoul;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x517C10 sub_517C10
// ------------------------------------------------------------
// CNEquipmentNovaCraft 构造器（新星工艺，CNEventEquipment 重载系）

uint32_t */*thiscall*/ sub_517C10(uint32_t *this, char ArgList, int nArg3, int nArg4)
{
  sub_514520((int)this, ArgList, nArg3, nArg4);
  *this = &vftbl_CNEquipmentNovaCraft;
  return this;
}



// ------------------------------------------------------------
// 0x517C40 CNEquipmentNovaCraft__vmt90
// ------------------------------------------------------------
// CNEquipmentNovaCraft__vmt90 伤害修正（51 行）

int /*thiscall*/ CNEquipmentNovaCraft__vmt90(void *this, uint32_t *uArg2, int nArg3)
{
  int result; // eax
  int v5; // edi
  int v6; // ebx
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_D43; // eax
  int v10; // eax
  int pThis_D44; // eax
  int nRand; // eax
  int v13; // et2
  int pThis_D45; // eax
  int pObj; // esi
  int v16; // [esp+4h] [ebp-4h]
  int v17; // [esp+10h] [ebp+8h]

  result = sub_604D00(*uArg2);
  if ( (uint8_t)result != 0 )
  {
    v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
    v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
    pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 120))(pThis_D4);
    pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 124))(pThis_D42);
    pThis_D43 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 52))(pThis_D43);
    srand((v6 + v16) * (v5 + v17 + v10));
    pThis_D44 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 308))(pThis_D44);
    if ( (uint8_t)result != 0 )
    {
      nRand = rand();
      v13 = nRand % 100;
      result = nRand / 100;
      if ( v13 < 2 )
      {
        pThis_D45 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
        result = __RTDynamicCast(pThis_D45, 0, &IRDActiveObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
        pObj = result;
        if ( result != 0 )
        {
          result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 1160))(result, 41);
          if ( result != 0 )
            return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 1300))(pObj, result, 2);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x517D50 CNEquipmentNovaCraft__vmt4
// ------------------------------------------------------------
// CNEquipmentNovaCraft__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentNovaCraft__vmt4(void *Block, char pszArg2)
{
  sub_517D80();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x517D80 sub_517D80
// ------------------------------------------------------------
// CNEquipmentNovaCraft 析构基座

int /*thiscall*/ sub_517D80(void **this)
{
  *this = &vftbl_CNEquipmentNovaCraft;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x517D90 sub_517D90
// ------------------------------------------------------------
// CNEquipmentSpiritCall 构造器（精灵召唤）：Block 非空则 sub_4ED3F0 装数组

uint32_t */*thiscall*/ sub_517D90(uint32_t *this, char ArgList, int nArg3, int nArg4, void *Block, int nArg6, int nArg7)
{
  void *Block2; // eax
  bool v9; // zf

  sub_514520((int)this, ArgList, nArg3, (int)&nArg4);
  Block2 = Block;
  v9 = Block == nullptr;
  *this = &vftbl_CNEquipmentSpiritCall;
  if ( !v9 )
    j__free(Block2);
  return this;
}



// ------------------------------------------------------------
// 0x517DF0 CNEquipmentSpiritCall__vmt90
// ------------------------------------------------------------
// CNEquipmentSpiritCall__vmt90 伤害修正（92 行）

int /*thiscall*/ CNEquipmentSpiritCall__vmt90(int *this, uint32_t *uArg2, int nArg3)
{
  int result; // eax
  int v5; // eax
  int pObj5; // eax
  int nRand; // eax
  int v8; // et2
  int *v9; // edi
  int pObj4; // ebx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // edx
  int *v15; // esi
  int v16; // edx
  int v17; // eax
  int v18; // edi
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  uint16_t v23[3]; // [esp+4h] [ebp-20h] BYREF
  bool nRand2; // [esp+Ah] [ebp-1Ah]
  char nRand3; // [esp+Bh] [ebp-19h]
  uint8_t v26[3]; // [esp+Ch] [ebp-18h] BYREF
  int v27; // [esp+Fh] [ebp-15h]
  int v28; // [esp+14h] [ebp-10h]
  int pObj6; // [esp+18h] [ebp-Ch]
  int pObj3; // [esp+1Ch] [ebp-8h]
  int pObj2; // [esp+20h] [ebp-4h]
  int pObj; // [esp+2Ch] [ebp+8h]

  result = sub_604D00(*uArg2);
  if ( (uint8_t)result != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
    result = __RTDynamicCast(v5, 0, &IRDActiveObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0);
    if ( result != 0 )
    {
      pObj5 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 308))(pObj5);
      if ( (uint8_t)result != 0 )
      {
        sub_432FA0();
        nRand = rand();
        v8 = nRand % 100;
        result = nRand / 100;
        if ( v8 < 5 )
        {
          v23[0] = rand() % 200 + 100;
          v23[1] = rand() % 100 + 50;
          nRand2 = rand() % 2 == 0;
          nRand3 = 3 - (rand() % 2 != 0);
          v26[2] = 0;
          v27 = 0;
          v26[0] = 1;
          v26[1] = 2;
          v23[2] = rand() % 60 + 40;
          v9 = (int *)(*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
          pObj4 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
          pObj = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
          v11 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
          v12 = *this;
          pObj2 = v11;
          pObj3 = (*(int (/*thiscall*/ **)(int *))(v12 + 212))(this);
          v13 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
          v14 = *this;
          pObj6 = v13;
          v15 = (int *)(*(int (/*thiscall*/ **)(int *))(v14 + 212))(this);
          v16 = *v9;
          v28 = *v15;
          v17 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, int, uint8_t *, uint32_t))(v16 + 152))(
                  v9,
                  1,
                  v23,
                  8,
                  0xFFFF,
                  0,
                  1,
                  v26,
                  0);
          v18 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 192))(pObj, v17) / 2;
          v19 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 128))(pObj4);
          v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 124))(pObj2, v19 + v18);
          v21 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 120))(pObj3, v20 - 1);
          v22 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj6 + 376))(pObj6, 15, v21);
          return (*(int (/*thiscall*/ **)(int *, int, int))(v28 + 592))(v15, 14, v22);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x517FD0 CNEquipmentSpiritCall__vmt4
// ------------------------------------------------------------
// CNEquipmentSpiritCall__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentSpiritCall__vmt4(void *Block, char pszArg2)
{
  sub_518000();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x518000 sub_518000
// ------------------------------------------------------------
// CNEquipmentSpiritCall 析构基座

int /*thiscall*/ sub_518000(void **this)
{
  *this = &vftbl_CNEquipmentSpiritCall;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x518010 sub_518010
// ------------------------------------------------------------
// CNEquipmentCoatofStarRocker 构造器（星辰摇滚衣）

uint32_t */*thiscall*/ sub_518010(uint32_t *this, char ArgList, int nArg3, int nArg4, void *Block, int nArg6, int nArg7)
{
  void *Block2; // eax
  bool v9; // zf

  sub_514520((int)this, ArgList, nArg3, (int)&nArg4);
  Block2 = Block;
  v9 = Block == nullptr;
  *this = &vftbl_CNEquipmentCoatofStarRocker;
  if ( !v9 )
    j__free(Block2);
  return this;
}



// ------------------------------------------------------------
// 0x518070 CNEquipmentCoatofStarRocker__vmt90
// ------------------------------------------------------------
// CNEquipmentCoatofStarRocker__vmt90 伤害修正（25 行：sub_604D00 门 → 系数修正）

int /*thiscall*/ CNEquipmentCoatofStarRocker__vmt90(void *this, uint32_t *uArg2, uint32_t *uArg3)
{
  int result; // eax
  int pThis_D4; // eax
  int nRand; // eax
  int v7; // et2

  result = sub_604D00(*uArg2);
  if ( (uint8_t)result != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
    if ( (uint8_t)result != 0 )
    {
      nRand = rand();
      v7 = nRand % 100;
      result = nRand / 100;
      if ( v7 < 2 )
      {
        ++*uArg3;
        return (int)uArg3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5180C0 CNEquipmentCoatofStarRocker__vmt4
// ------------------------------------------------------------
// CNEquipmentCoatofStarRocker__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentCoatofStarRocker__vmt4(void *Block, char pszArg2)
{
  sub_5180F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5180F0 sub_5180F0
// ------------------------------------------------------------
// CNEquipmentCoatofStarRocker 析构基座

int /*thiscall*/ sub_5180F0(void **this)
{
  *this = &vftbl_CNEquipmentCoatofStarRocker;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x518100 sub_518100
// ------------------------------------------------------------
// CNEquipmentQuattroMephist 构造器（四重梅菲斯特）

uint32_t */*thiscall*/ sub_518100(uint32_t *this, char ArgList, int nArg3, int nArg4, void *Block, int nArg6, int nArg7)
{
  void *Block2; // eax
  bool v9; // zf

  sub_514520((int)this, ArgList, nArg3, (int)&nArg4);
  Block2 = Block;
  v9 = Block == nullptr;
  *this = &vftbl_CNEquipmentQuattroMephist;
  if ( !v9 )
    j__free(Block2);
  return this;
}



// ------------------------------------------------------------
// 0x518160 CNEquipmentQuattroMephist__vmt90
// ------------------------------------------------------------
// CNEquipmentQuattroMephist__vmt90 伤害修正（86 行）

int /*thiscall*/ CNEquipmentQuattroMephist__vmt90(int *this, uint32_t *uArg2, int nArg3)
{
  int result; // eax
  int pObj4; // eax
  int nRand; // eax
  int v7; // et2
  int *v8; // edi
  int pObj; // ebx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int *v14; // esi
  int v15; // edx
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  uint16_t v22[3]; // [esp+4h] [ebp-20h] BYREF
  bool nRand2; // [esp+Ah] [ebp-1Ah]
  char nRand3; // [esp+Bh] [ebp-19h]
  uint8_t v25[3]; // [esp+Ch] [ebp-18h] BYREF
  int v26; // [esp+Fh] [ebp-15h]
  int v27; // [esp+14h] [ebp-10h]
  int pObj6; // [esp+18h] [ebp-Ch]
  int pObj5; // [esp+1Ch] [ebp-8h]
  int pObj3; // [esp+20h] [ebp-4h]
  int pObj2; // [esp+2Ch] [ebp+8h]

  result = sub_604D00(*uArg2);
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();
    pObj4 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 308))(pObj4);
    if ( (uint8_t)result != 0 )
    {
      nRand = rand();
      v7 = nRand % 100;
      result = nRand / 100;
      if ( v7 < 6 )
      {
        v22[0] = rand() % 200 + 100;
        v22[1] = rand() % 100 + 50;
        nRand2 = rand() % 2 == 0;
        nRand3 = 3 - (rand() % 2 != 0);
        v25[2] = 0;
        v26 = 0;
        v25[0] = 1;
        v25[1] = 2;
        v22[2] = rand() % 60 + 40;
        v8 = (int *)(*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        pObj = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        pObj2 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        v10 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        v11 = *this;
        pObj3 = v10;
        pObj5 = (*(int (/*thiscall*/ **)(int *))(v11 + 212))(this);
        v12 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
        v13 = *this;
        pObj6 = v12;
        v14 = (int *)(*(int (/*thiscall*/ **)(int *))(v13 + 212))(this);
        v15 = *v8;
        v27 = *v14;
        v16 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, int, uint8_t *, uint32_t))(v15 + 152))(
                v8,
                1,
                v22,
                8,
                0xFFFF,
                0,
                1,
                v25,
                0);
        v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 192))(pObj2, v16) / 2;
        v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
        v19 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 124))(pObj3, v18 + v17);
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj5 + 120))(pObj5, v19 - 1);
        v21 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj6 + 376))(pObj6, 30, v20);
        return (*(int (/*thiscall*/ **)(int *, int, int))(v27 + 592))(v14, 602, v21);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x518320 CNEquipmentQuattroMephist__vmt4
// ------------------------------------------------------------
// CNEquipmentQuattroMephist__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentQuattroMephist__vmt4(void *Block, char pszArg2)
{
  sub_518350();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x518350 sub_518350
// ------------------------------------------------------------
// CNEquipmentQuattroMephist 析构基座

int /*thiscall*/ sub_518350(void **this)
{
  *this = &vftbl_CNEquipmentQuattroMephist;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x518360 sub_518360
// ------------------------------------------------------------
// CNEquipmentPureGuardian 构造器（纯粹守护者，62 行大构造）

uint8_t */*thiscall*/ sub_518360(uint8_t *this, char ArgList, void *pArg3, int nArg4, void *Block, int nArg6, int nArg7)
{
  uint32_t *pMem; // eax
  int *v9; // eax
  int v10; // edx
  int v11; // eax
  int pThis_D4; // eax
  int v13; // eax
  void *Block2; // eax
  bool v15; // zf
  int v17; // [esp+8h] [ebp-1Ch] BYREF
  char v18; // [esp+Ch] [ebp-18h]
  int v19; // [esp+10h] [ebp-14h]
  uint8_t *pThis; // [esp+14h] [ebp-10h]
  int v21; // [esp+20h] [ebp-4h]

  pThis = this;
  v21 = 0;
  sub_514520((int)this, ArgList, (int)pArg3, (int)&nArg4);
  *(uint32_t *)this = &vftbl_CNEquipmentPureGuardian;
  *(this + 1468) = 0;
  *((uint32_t *)this + 366) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 368) = 0;
  *(this + 1476) = 1;
  *(this + 1478) = 0;
  *(this + 1477) = 0;
  *((uint32_t *)this + 372) = 0;
  *((uint32_t *)this + 371) = 0;
  *((uint32_t *)this + 370) = 0;
  v17 = 5;
  v18 = 0;
  v19 = 1142292480;
  pMem = operator new(0x7Cu);
  LOBYTE(v21) = 3;
  if ( pMem != nullptr )
    v9 = sub_5101B0(pMem, (int)&v17, 1, 0, 1);
  else
    v9 = nullptr;
  *((uint32_t *)this + 364) = v9;
  v10 = *v9;
  LOBYTE(v21) = 2;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v10 + 64))(v9) + 36) = 0;
  v11 = *(uint32_t *)this;
  *((uint32_t *)this + 335) = 500;
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(v11 + 212))(this) != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v13 = sub_699000(pThis_D4 + 36);  // 【clock_now(clk)】
  }
  else
  {
    v13 = 0;
  }
  *((uint32_t *)this + 334) = v13;
  Block2 = Block;
  v15 = Block == nullptr;
  *(this + 1460) = 0;
  *(this + 1477) = 0;
  *(this + 1478) = 0;
  if ( !v15 )
    j__free(Block2);
  return this;
}



// ------------------------------------------------------------
// 0x5184A0 CNEquipmentPureGuardian__vmt90
// ------------------------------------------------------------
// CNEquipmentPureGuardian__vmt90 伤害修正（44 行）

char /*thiscall*/ CNEquipmentPureGuardian__vmt90(uint8_t *this, uint32_t *uArg2, int nArg3)
{
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_D43; // eax
  int v10; // eax
  int pThis_D44; // eax
  int nRand; // eax
  int v13; // et2
  int v15; // [esp+4h] [ebp-4h]
  int v16; // [esp+10h] [ebp+8h]

  LOBYTE(v4) = sub_604D00(*uArg2);
  if ( (uint8_t)v4 != 0 )
  {
    v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
    v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
    pThis_D4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 120))(pThis_D4);
    pThis_D42 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 124))(pThis_D42);
    pThis_D43 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 52))(pThis_D43);
    srand((v6 + v15) * (v5 + v16 + v10));
    pThis_D44 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    LOBYTE(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 308))(pThis_D44);
    if ( (uint8_t)v4 != 0 )
    {
      nRand = rand();
      v13 = nRand % 100;
      v4 = nRand / 100;
      if ( v13 < 8 )
      {
        *(this + 1460) = 1;
        *(this + 1477) = 0;
        *(this + 1478) = 0;
        LOBYTE(v4) = sub_698F90((int)(this + 1464), 45000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x518580 CNEquipmentPureGuardian__vmt12C
// ------------------------------------------------------------
// CNEquipmentPureGuardian__vmt12C 周期 tick（38 行）

char /*thiscall*/ CNEquipmentPureGuardian__vmt12C(uint32_t *this)
{
  char result; // al
  int fld_e372; // edi
  int pThis_16E; // eax
  int fld_e364; // ecx
  int fld_e3642; // edi
  int v7; // eax
  int v8; // eax

  result = *((uint8_t *)this + 1460);
  if ( result != 0 )
  {
    fld_e372 = *(this + 372);
    pThis_16E = sub_699000((int)(this + 366));  // 【clock_now(clk)】
    fld_e364 = *(this + 364);
    if ( pThis_16E >= fld_e372 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 80))(fld_e364);
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 364) + 76))(*(this + 364), 0);
        *((uint8_t *)this + 1460) = 0;
      }
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 80))(fld_e364);
      if ( result == 0 )
      {
        fld_e3642 = *(uint32_t *)*(this + 364);
        v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int))(*this + 212))(this, 0, 0, 0, -1);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 212))(this, v7);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e3642 + 56))(*(this + 364), v8);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x518610 CNEquipmentPureGuardian__vmt4
// ------------------------------------------------------------
// CNEquipmentPureGuardian__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentPureGuardian__vmt4(void *Block, char pszArg2)
{
  sub_518640();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x518640 sub_518640
// ------------------------------------------------------------
// CNEquipmentPureGuardian 析构基座：+1456 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_518640(int this)
{
  void (/*thiscall*/ ***pThis_5B0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentPureGuardian;
  pThis_5B0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1456);
  if ( pThis_5B0 != nullptr )
    (**pThis_5B0)(pThis_5B0, 1);
  *(uint32_t *)(this + 1456) = 0;
  *(uint32_t *)(this + 1340) = 0;
  *(uint32_t *)(this + 1336) = 0;
  *(uint32_t *)(this + 1464) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1468) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x5186C0 sub_5186C0
// ------------------------------------------------------------
// CNEquipmentDarkPrayer 构造器（暗黑祈祷，81 行大构造）

uint8_t */*thiscall*/ sub_5186C0(uint8_t *this, char ArgList, void *pArg3, int nArg4, void *Block, int nArg6, int nArg7)
{
  uint32_t *pMem; // eax
  int *v9; // eax
  int v10; // edx
  uint32_t *pMem2; // eax
  int *v12; // eax
  int v13; // edx
  int v14; // eax
  int pThis_D4; // eax
  int v16; // eax
  void *Block2; // eax
  bool v18; // zf
  int v20; // [esp+8h] [ebp-28h] BYREF
  char v21; // [esp+Ch] [ebp-24h]
  int v22; // [esp+10h] [ebp-20h]
  int v23; // [esp+14h] [ebp-1Ch] BYREF
  char v24; // [esp+18h] [ebp-18h]
  int v25; // [esp+1Ch] [ebp-14h]
  uint8_t *pThis; // [esp+20h] [ebp-10h]
  int v27; // [esp+2Ch] [ebp-4h]

  pThis = this;
  v27 = 0;
  sub_514520((int)this, ArgList, (int)pArg3, (int)&nArg4);
  *(uint32_t *)this = &vftbl_CNEquipmentDarkPrayer;
  *(this + 1464) = 0;
  *((uint32_t *)this + 365) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 367) = 0;
  *(this + 1472) = 1;
  *(this + 1474) = 0;
  *(this + 1473) = 0;
  *((uint32_t *)this + 371) = 0;
  *((uint32_t *)this + 370) = 0;
  *((uint32_t *)this + 369) = 0;
  v23 = 18;
  v24 = 0;
  v25 = 1097859072;
  v20 = 1;
  v21 = 0;
  v22 = 1117782016;
  pMem = operator new(0x7Cu);
  LOBYTE(v27) = 3;
  if ( pMem != nullptr )
    v9 = sub_5101B0(pMem, (int)&v23, 1, 0, 1);
  else
    v9 = nullptr;
  *((uint32_t *)this + 372) = v9;
  v10 = *v9;
  LOBYTE(v27) = 2;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v10 + 64))(v9) + 36) = 0;
  pMem2 = operator new(0x7Cu);
  LOBYTE(v27) = 4;
  if ( pMem2 != nullptr )
    v12 = sub_5101B0(pMem2, (int)&v20, 1, 0, 1);
  else
    v12 = nullptr;
  *((uint32_t *)this + 373) = v12;
  v13 = *v12;
  LOBYTE(v27) = 2;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v13 + 64))(v12) + 36) = 0;
  v14 = *(uint32_t *)this;
  *((uint32_t *)this + 335) = 500;
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(v14 + 212))(this) != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v16 = sub_699000(pThis_D4 + 36);  // 【clock_now(clk)】
  }
  else
  {
    v16 = 0;
  }
  *((uint32_t *)this + 334) = v16;
  Block2 = Block;
  v18 = Block == nullptr;
  *(this + 1456) = 0;
  *(this + 1473) = 0;
  *(this + 1474) = 0;
  if ( !v18 )
    j__free(Block2);
  return this;
}



// ------------------------------------------------------------
// 0x518850 CNEquipmentDarkPrayer__vmt13C
// ------------------------------------------------------------
// CNEquipmentDarkPrayer__vmt13C 卸状态：+372 状态对象销毁

int /*thiscall*/ CNEquipmentDarkPrayer__vmt13C(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e372)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e373)(uint32_t, int); // ecx

  fld_e372 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 372);
  if ( fld_e372 != nullptr )
    result = (**fld_e372)(fld_e372, 1);
  fld_e373 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 373);
  *(this + 372) = 0;
  if ( fld_e373 != nullptr )
    result = (**fld_e373)(fld_e373, 1);
  *(this + 373) = 0;
  *(this + 335) = 0;
  *(this + 334) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x5188A0 CNEquipmentDarkPrayer__vmt90
// ------------------------------------------------------------
// CNEquipmentDarkPrayer__vmt90 伤害修正（44 行）

char /*thiscall*/ CNEquipmentDarkPrayer__vmt90(uint8_t *this, uint32_t *uArg2, int nArg3)
{
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_D43; // eax
  int v10; // eax
  int pThis_D44; // eax
  int nRand; // eax
  int v13; // et2
  int v15; // [esp+4h] [ebp-4h]
  int v16; // [esp+10h] [ebp+8h]

  LOBYTE(v4) = sub_604D00(*uArg2);
  if ( (uint8_t)v4 != 0 )
  {
    v5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
    v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
    pThis_D4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 120))(pThis_D4);
    pThis_D42 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 124))(pThis_D42);
    pThis_D43 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 52))(pThis_D43);
    srand((v6 + v15) * (v5 + v16 + v10));
    pThis_D44 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    LOBYTE(v4) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 308))(pThis_D44);
    if ( (uint8_t)v4 != 0 )
    {
      nRand = rand();
      v13 = nRand % 100;
      v4 = nRand / 100;
      if ( v13 < 3 )
      {
        *(this + 1456) = 1;
        *(this + 1473) = 0;
        *(this + 1474) = 0;
        LOBYTE(v4) = sub_698F90((int)(this + 1460), 30000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
    }
  }
  return v4;
}



// ------------------------------------------------------------
// 0x518980 CNEquipmentDarkPrayer__vmt12C
// ------------------------------------------------------------
// CNEquipmentDarkPrayer__vmt12C 周期 tick（46 行）

char /*thiscall*/ CNEquipmentDarkPrayer__vmt12C(uint8_t *this)
{
  char result; // al
  int pThis_173; // edi
  int pThis_5B4; // eax
  int pThis_174; // ecx
  int pThis_1742; // edi
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_175; // edi
  int pThis_D43; // eax
  int pThis_D44; // eax

  result = *(this + 1456);
  if ( result != 0 )
  {
    pThis_173 = *((uint32_t *)this + 371);
    pThis_5B4 = sub_699000((int)(this + 1460));  // 【clock_now(clk)】
    pThis_174 = *((uint32_t *)this + 372);
    if ( pThis_5B4 >= pThis_173 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_174 + 80))(pThis_174);
      if ( result != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 372) + 76))(*((uint32_t *)this + 372), 0);
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 373) + 76))(*((uint32_t *)this + 373), 0);
        *(this + 1456) = 0;
      }
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_174 + 80))(pThis_174);
      if ( result == 0 )
      {
        pThis_1742 = **((uint32_t **)this + 372);
        pThis_D4 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 212))(this, 0, 0, 0, -1);
        pThis_D42 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 212))(this, pThis_D4);
        (*(void (/*thiscall*/ **)(uint32_t, int))(pThis_1742 + 56))(*((uint32_t *)this + 372), pThis_D42);
        pThis_175 = **((uint32_t **)this + 373);
        pThis_D43 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 212))(this, 0, 0, 0, -1);
        pThis_D44 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 212))(this, pThis_D43);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(pThis_175 + 56))(*((uint32_t *)this + 373), pThis_D44);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x518A50 CNEquipmentDarkPrayer__vmt4
// ------------------------------------------------------------
// CNEquipmentDarkPrayer__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentDarkPrayer__vmt4(void *Block, char pszArg2)
{
  sub_518A80();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x518A80 sub_518A80
// ------------------------------------------------------------
// CNEquipmentDarkPrayer 析构基座：+1488/+1460 双状态销毁 → sub_4BADD0

int /*thiscall*/ sub_518A80(int this)
{
  void (/*thiscall*/ ***pThis_5D0)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_5D4)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentDarkPrayer;
  pThis_5D0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1488);
  if ( pThis_5D0 != nullptr )
    (**pThis_5D0)(pThis_5D0, 1);
  pThis_5D4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1492);
  *(uint32_t *)(this + 1488) = 0;
  if ( pThis_5D4 != nullptr )
    (**pThis_5D4)(pThis_5D4, 1);
  *(uint32_t *)(this + 1492) = 0;
  *(uint32_t *)(this + 1340) = 0;
  *(uint32_t *)(this + 1336) = 0;
  *(uint32_t *)(this + 1460) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1464) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x518B20 sub_518B20
// ------------------------------------------------------------
// CNEquipmentTeachingofGoraBoldness 构造器（戈拉的勇气教导，58 行）

uint8_t */*thiscall*/ sub_518B20(uint8_t *this, char ArgList, void *pArg3, int nArg4, void *Block, int nArg6, int nArg7)
{
  uint32_t *pMem; // eax
  int *v9; // eax
  int v10; // edx
  int v11; // eax
  int pThis_D4; // eax
  int v13; // eax
  int v15; // [esp+8h] [ebp-1Ch] BYREF
  char v16; // [esp+Ch] [ebp-18h]
  int v17; // [esp+10h] [ebp-14h]
  uint8_t *pThis; // [esp+14h] [ebp-10h]
  int v19; // [esp+20h] [ebp-4h]

  pThis = this;
  v19 = 0;
  sub_514520((int)this, ArgList, (int)pArg3, (int)&nArg4);
  *(uint32_t *)this = &vftbl_CNEquipmentTeachingofGoraBoldness;
  *(this + 1464) = 0;
  *((uint32_t *)this + 365) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 367) = 0;
  *(this + 1472) = 1;
  *(this + 1474) = 0;
  *(this + 1473) = 0;
  *((uint32_t *)this + 371) = 0;
  *((uint32_t *)this + 370) = 0;
  *((uint32_t *)this + 369) = 0;
  v15 = 0;
  v16 = 0;
  v17 = 1117782016;
  pMem = operator new(0x7Cu);
  LOBYTE(v19) = 3;
  if ( pMem != nullptr )
    v9 = sub_5101B0(pMem, (int)&v15, 1, 0, 1);
  else
    v9 = nullptr;
  *((uint32_t *)this + 372) = v9;
  v10 = *v9;
  LOBYTE(v19) = 2;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(v10 + 64))(v9) + 36) = 0;
  *(this + 1456) = 0;
  *(this + 1473) = 0;
  *(this + 1474) = 0;
  v11 = *(uint32_t *)this;
  *((uint32_t *)this + 335) = 500;
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(v11 + 212))(this) != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 212))(this);
    v13 = sub_699000(pThis_D4 + 36);  // 【clock_now(clk)】
  }
  else
  {
    v13 = 0;
  }
  *((uint32_t *)this + 334) = v13;
  if ( Block != nullptr )
    j__free(Block);
  return this;
}



// ------------------------------------------------------------
// 0x518C60 CNEquipmentTeachingofGoraBoldness__vmt13C
// ------------------------------------------------------------
// CNEquipmentTeachingofGoraBoldness__vmt13C 卸状态：+372 状态对象销毁

int /*thiscall*/ CNEquipmentTeachingofGoraBoldness__vmt13C(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e372)(uint32_t, int); // ecx
  int result; // eax

  fld_e372 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 372);
  if ( fld_e372 != nullptr )
    result = (**fld_e372)(fld_e372, 1);
  *(this + 372) = 0;
  *(this + 335) = 0;
  *(this + 334) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x518CA0 CNEquipmentTeachingofGoraBoldness__vmt12C
// ------------------------------------------------------------
// CNEquipmentTeachingofGoraBoldness__vmt12C 周期 tick（38 行）

char /*thiscall*/ CNEquipmentTeachingofGoraBoldness__vmt12C(uint32_t *this)
{
  char result; // al
  int fld_e371; // edi
  int pThis_16D; // eax
  int fld_e372; // ecx
  int fld_e3722; // edi
  int v7; // eax
  int v8; // eax

  result = *((uint8_t *)this + 1456);
  if ( result != 0 )
  {
    fld_e371 = *(this + 371);
    pThis_16D = sub_699000((int)(this + 365));  // 【clock_now(clk)】
    fld_e372 = *(this + 372);
    if ( pThis_16D >= fld_e371 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e372 + 80))(fld_e372);
      if ( result != 0 )
      {
        result = (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 372) + 76))(*(this + 372), 0);
        *((uint8_t *)this + 1456) = 0;
      }
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e372 + 80))(fld_e372);
      if ( result == 0 )
      {
        fld_e3722 = *(uint32_t *)*(this + 372);
        v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int))(*this + 212))(this, 0, 0, 0, -1);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 212))(this, v7);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e3722 + 56))(*(this + 372), v8);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x518D30 CNEquipmentTeachingofGoraBoldness__vmt4
// ------------------------------------------------------------
// CNEquipmentTeachingofGoraBoldness__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentTeachingofGoraBoldness__vmt4(void *Block, char pszArg2)
{
  sub_518D60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x518D60 sub_518D60
// ------------------------------------------------------------
// CNEquipmentTeachingofGoraBoldness 析构基座：+1488 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_518D60(int this)
{
  void (/*thiscall*/ ***pThis_5D0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentTeachingofGoraBoldness;
  pThis_5D0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1488);
  if ( pThis_5D0 != nullptr )
    (**pThis_5D0)(pThis_5D0, 1);
  *(uint32_t *)(this + 1488) = 0;
  *(uint32_t *)(this + 1340) = 0;
  *(uint32_t *)(this + 1336) = 0;
  *(uint32_t *)(this + 1460) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 1464) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x518DE0 sub_518DE0
// ------------------------------------------------------------
// CNEquipmentDispellizer 构造器（驱散者）

uint32_t */*thiscall*/ sub_518DE0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentDispellizer;
  return this;
}



// ------------------------------------------------------------
// 0x518E10 CNEquipmentDispellizer__vmt88
// ------------------------------------------------------------
// CNEquipmentDispellizer__vmt88 攻击触发（96 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentDispellizer__vmt88(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  void *pThis; // ebx
  int result; // eax
  int pObj3; // esi
  int pObj; // eax
  int nRand; // eax
  int v11; // et2
  int i; // edi
  int *v13; // esi
  int v14; // eax
  int v15; // edi
  unsigned int v16; // esi
  int v17; // ebx
  int v18; // ecx
  int pObj5; // ecx
  int v20; // ecx
  int pObj2; // ecx
  int pObj4; // [esp+Ch] [ebp-4h]
  int v24; // [esp+18h] [ebp+8h]
  int v25; // [esp+18h] [ebp+8h]

  pThis = this;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    result = __RTDynamicCast(
               nArg2,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
    pObj3 = result;
    pObj4 = result;
    if ( result != 0 )
    {
      pObj = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pThis + 212))(pThis);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);
      if ( (uint8_t)result != 0 )
      {
        nRand = rand();
        v11 = nRand % 100;
        result = nRand / 100;
        if ( v11 < 8 )
        {
          for ( i = 0; i < 17; ++i )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 776))(pObj3, i) != 0 )
            {
              v13 = (int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 772))(pObj3, i);
              v24 = *v13;
              v14 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)pThis + 212))(pThis);
              (*(void (/*thiscall*/ **)(int *, uint32_t, int))(v24 + 4))(v13, 0, v14);
              pThis = this;
              pObj3 = pObj4;
            }
          }
          v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 700))(pObj3);
          result = *(uint32_t *)(v15 + 4);
          v16 = 0;
          if ( result != 0 )
            v17 = (*(uint32_t *)(v15 + 8) - result) >> 2;
          else
            v17 = 0;
          v25 = 0;
          if ( v17 > 0 )
          {
            do
            {
              v18 = *(uint32_t *)(v15 + 4);
              if ( v18 != 0 && v16 < (*(uint32_t *)(v15 + 8) - v18) >> 2 )
                pObj5 = *(uint32_t *)(v18 + 4 * v16);
              else
                pObj5 = 0;
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj5 + 92))(pObj5) != 0 )
              {
                v20 = *(uint32_t *)(v15 + 4);
                if ( v20 != 0 && v16 < (*(uint32_t *)(v15 + 8) - v20) >> 2 )
                  pObj2 = *(uint32_t *)(v20 + 4 * v16);
                else
                  pObj2 = 0;
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 76))(pObj2, 0);
                ++v25;
              }
              ++v16;
            }
            while ( (int)v16 < v17 );
            result = v25;
            if ( v25 > 0 )
              return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 956))(pObj4);
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x518F70 CNEquipmentDispellizer__vmt4
// ------------------------------------------------------------
// CNEquipmentDispellizer__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentDispellizer__vmt4(void *Block, char pszArg2)
{
  sub_518FA0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x518FA0 sub_518FA0
// ------------------------------------------------------------
// CNEquipmentDispellizer 析构基座

int /*thiscall*/ sub_518FA0(void **this)
{
  *this = &vftbl_CNEquipmentDispellizer;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x518FB0 sub_518FB0
// ------------------------------------------------------------
// CNEquipmentMirageWand 构造器（幻影魔杖）

uint32_t */*thiscall*/ sub_518FB0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentMirageWand;
  return this;
}



// ------------------------------------------------------------
// 0x518FE0 CNEquipmentMirageWand__vmt8C
// ------------------------------------------------------------
// CNEquipmentMirageWand__vmt8C 受击触发（24 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentMirageWand__vmt8C(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_D4; // eax
  int result; // eax
  int nRand; // eax
  int v9; // et2
  int pThis_D42; // eax

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    nRand = rand();
    v9 = nRand % 100;
    result = nRand / 100;
    if ( v9 < 3 )
    {
      pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      result = __RTDynamicCast(pThis_D42, 0, &IRDActiveObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
      if ( result != 0 )
        return sub_5DCA10(3);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x519040 CNEquipmentMirageWand__vmt4
// ------------------------------------------------------------
// CNEquipmentMirageWand__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentMirageWand__vmt4(void *Block, char pszArg2)
{
  sub_519070();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519070 sub_519070
// ------------------------------------------------------------
// CNEquipmentMirageWand 析构基座

int /*thiscall*/ sub_519070(void **this)
{
  *this = &vftbl_CNEquipmentMirageWand;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x519080 sub_519080
// ------------------------------------------------------------
// CNEquipmentManaholickerCoat 构造器（玛那嗜者外套）

uint32_t */*thiscall*/ sub_519080(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentManaholickerCoat;
  return this;
}



// ------------------------------------------------------------
// 0x5190B0 CNEquipmentManaholickerCoat__vmt8C
// ------------------------------------------------------------
// CNEquipmentManaholickerCoat__vmt8C 受击触发（34 行）

int /*thiscall*/ CNEquipmentManaholickerCoat__vmt8C(char *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int pThis_D4; // eax
  int nRand; // eax
  int v9; // et2
  int pThis_D42; // eax
  int pObj; // esi

  if ( sub_41C5A0(this + 1252) == 0
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this)) != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
    if ( (uint8_t)result != 0 )
    {
      nRand = rand();
      v9 = nRand % 100;
      result = nRand / 100;
      if ( v9 < 4 )
      {
        pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        result = __RTDynamicCast(pThis_D42, 0, &IRDActiveObject `RTTI Type Descriptor', &CNMage `RTTI Type Descriptor', 0);
        pObj = result;
        if ( result != 0 )
        {
          result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)result + 1160))(result, 41);
          if ( result != 0 )
            return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 1300))(pObj, result, 3);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x519150 CNEquipmentManaholickerCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentManaholickerCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentManaholickerCoat__vmt4(void *Block, char pszArg2)
{
  sub_519180();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519180 sub_519180
// ------------------------------------------------------------
// CNEquipmentManaholickerCoat 析构基座

int /*thiscall*/ sub_519180(void **this)
{
  *this = &vftbl_CNEquipmentManaholickerCoat;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x519190 sub_519190
// ------------------------------------------------------------
// CNEquipmentShadowVeilCoat 构造器（暗影面纱外套）

uint32_t */*thiscall*/ sub_519190(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentShadowVeilCoat;
  return this;
}



// ------------------------------------------------------------
// 0x5191C0 CNEquipmentShadowVeilCoat__vmt8C
// ------------------------------------------------------------
// CNEquipmentShadowVeilCoat__vmt8C 受击触发（48 行）

int /*thiscall*/ CNEquipmentShadowVeilCoat__vmt8C(char *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // edi
  int v8; // ebx
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_D43; // eax
  int v12; // eax
  int pThis_D44; // eax
  int nRand; // eax
  int v15; // et2
  int v16; // [esp+4h] [ebp-8h]
  int v17; // [esp+8h] [ebp-4h]

  if ( sub_41C5A0(this + 1252) == 0
    || (uint8_t)(result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this)) != 0 )
  {
    v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
    v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
    pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 120))(pThis_D4);
    pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 124))(pThis_D42);
    pThis_D43 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 52))(pThis_D43);
    srand((v8 + v16) * (v7 + v17 + v12));
    pThis_D44 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 308))(pThis_D44);
    if ( (uint8_t)result != 0 )
    {
      nRand = rand();
      v15 = nRand % 100;
      result = nRand / 100;
      if ( v15 < 2 )
      {
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
        if ( *(uint32_t *)(result + 20) == 2 )
        {
          (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          sub_49C620(1, 1, 0);
          (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          return sub_49C5F0(1, 0, 0, 10000);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5192D0 CNEquipmentShadowVeilCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentShadowVeilCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentShadowVeilCoat__vmt4(void *Block, char pszArg2)
{
  sub_519300();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519300 sub_519300
// ------------------------------------------------------------
// CNEquipmentShadowVeilCoat 析构基座

int /*thiscall*/ sub_519300(void **this)
{
  *this = &vftbl_CNEquipmentShadowVeilCoat;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x519310 sub_519310
// ------------------------------------------------------------
// CNEquipmentLightKingsGuard 构造器（光之王护卫）

uint32_t */*thiscall*/ sub_519310(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentLightKingsGuard;
  return this;
}



// ------------------------------------------------------------
// 0x519340 CNEquipmentLightKingsGuard__vmt88
// ------------------------------------------------------------
// CNEquipmentLightKingsGuard__vmt88 攻击触发（56 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentLightKingsGuard__vmt88(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int result; // eax
  int pObj; // esi
  int pThis_D4; // eax
  int nRand; // eax
  int v11; // et2
  int *pThis_D42; // edi
  int v13; // ebx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    result = __RTDynamicCast(
               nArg2,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
    pObj = result;
    if ( result != 0 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
      if ( (uint8_t)result != 0 )
      {
        nRand = rand();
        v11 = nRand % 100;
        result = nRand / 100;
        if ( v11 < 2 )
        {
          pThis_D42 = (int *)(*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
          v13 = *pThis_D42;
          v14 = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)pObj + 124))(
                  pObj,
                  30070,
                  10,
                  0,
                  4,
                  100,
                  1,
                  0,
                  0);
          v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v14);
          v16 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pObj + 124))(pObj, 0, v15);
          v17 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 120))(pObj, v16);
          return (*(int (/*thiscall*/ **)(int *, int))(v13 + 584))(pThis_D42, v17);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x519400 CNEquipmentLightKingsGuard__vmt4
// ------------------------------------------------------------
// CNEquipmentLightKingsGuard__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentLightKingsGuard__vmt4(void *Block, char pszArg2)
{
  sub_519430();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519430 sub_519430
// ------------------------------------------------------------
// CNEquipmentLightKingsGuard 析构基座

int /*thiscall*/ sub_519430(void **this)
{
  *this = &vftbl_CNEquipmentLightKingsGuard;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x519440 sub_519440
// ------------------------------------------------------------
// CNEquipmentIceKingsGuard 构造器（冰之王护卫）

uint32_t */*thiscall*/ sub_519440(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentIceKingsGuard;
  return this;
}



// ------------------------------------------------------------
// 0x519470 CNEquipmentIceKingsGuard__vmt88
// ------------------------------------------------------------
// CNEquipmentIceKingsGuard__vmt88 攻击触发（44 行：概率掷 → 效果施加）

int /*thiscall*/ CNEquipmentIceKingsGuard__vmt88(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int result; // eax
  int pObj; // esi
  int pThis_D4; // eax
  int nRand; // eax
  int v11; // et2
  int pThis_D42; // eax
  int v13; // [esp-1Ch] [ebp-24h]
  int v14; // [esp-18h] [ebp-20h]
  int v15; // [esp-10h] [ebp-18h]

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    result = __RTDynamicCast(
               nArg2,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
    pObj = result;
    if ( result != 0 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
      if ( (uint8_t)result != 0 )
      {
        nRand = rand();
        v11 = nRand % 100;
        result = nRand / 100;
        if ( v11 < 2 )
        {
          (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
          v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 152))(pObj);
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
          pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
          return sub_4E4A50(pThis_D42, 48032, 1, v13, v14, 0, v15, 0, 0, 0);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x519520 CNEquipmentIceKingsGuard__vmt4
// ------------------------------------------------------------
// CNEquipmentIceKingsGuard__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentIceKingsGuard__vmt4(void *Block, char pszArg2)
{
  sub_519550();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519550 sub_519550
// ------------------------------------------------------------
// CNEquipmentIceKingsGuard 析构基座

int /*thiscall*/ sub_519550(void **this)
{
  *this = &vftbl_CNEquipmentIceKingsGuard;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x519560 sub_519560
// ------------------------------------------------------------
// CNEquipmentCrisisScepter 构造器（危机权杖）：调 sub_510BF0 装状态初始化器 D

uint32_t */*thiscall*/ sub_519560(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentCrisisScepter;
  sub_510BF0(this);
  return this;
}



// ------------------------------------------------------------
// 0x5195C0 CNEquipmentPureGuardian__vmt13C
// ------------------------------------------------------------
// CNEquipmentPureGuardian__vmt13C 卸状态（复用实现）：+364 状态对象销毁

int /*thiscall*/ CNEquipmentPureGuardian__vmt13C(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e364)(uint32_t, int); // ecx
  int result; // eax

  fld_e364 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 364);
  if ( fld_e364 != nullptr )
    result = (**fld_e364)(fld_e364, 1);
  *(this + 364) = 0;
  *(this + 335) = 0;
  *(this + 334) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x519600 CNEquipmentCrisisScepter__vmt12C
// ------------------------------------------------------------
// CNEquipmentCrisisScepter__vmt12C 周期 tick（35 行：冷却计时 + 状态维持）

int /*thiscall*/ CNEquipmentCrisisScepter__vmt12C(uint32_t *this)
{
  int pObj; // edi
  int pObj2; // ebx
  int v4; // eax
  int fld_e364; // ecx
  int result; // eax
  int fld_e3642; // edi
  int v8; // eax
  int v9; // eax
  float v10; // [esp+Ch] [ebp-8h]

  pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
  pObj2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
  v10 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 736))(pObj);
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 740))(pObj2);
  fld_e364 = *(this + 364);
  if ( (double)v4 * 0.15000001 < v10 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 80))(fld_e364);
    if ( (uint8_t)result == 1 )
      return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 364) + 76))(*(this + 364), 0);
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 80))(fld_e364);
    if ( (uint8_t)result == 0 )
    {
      fld_e3642 = *(uint32_t *)*(this + 364);
      v8 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, int))(*this + 212))(this, 0, 0, 0, -1);
      v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 212))(this, v8);
      return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e3642 + 56))(*(this + 364), v9);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5196D0 CNEquipmentCrisisScepter__vmt4
// ------------------------------------------------------------
// CNEquipmentCrisisScepter__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentCrisisScepter__vmt4(void *Block, char pszArg2)
{
  sub_519700();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519700 sub_519700
// ------------------------------------------------------------
// CNEquipmentCrisisScepter 析构基座：+1456 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_519700(int this)
{
  void (/*thiscall*/ ***pThis_5B0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentCrisisScepter;
  pThis_5B0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1456);
  if ( pThis_5B0 != nullptr )
    (**pThis_5B0)(pThis_5B0, 1);
  *(uint32_t *)(this + 1456) = 0;
  *(uint32_t *)(this + 1340) = 0;
  *(uint32_t *)(this + 1336) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x519770 sub_519770
// ------------------------------------------------------------
// CNEquipmentMusingRegaliaRob 构造器（沉思法衣）

uint32_t */*thiscall*/ sub_519770(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentMusingRegaliaRob;
  return this;
}



// ------------------------------------------------------------
// 0x5197A0 CNEquipmentMusingRegaliaRob__vmt88
// ------------------------------------------------------------
// CNEquipmentMusingRegaliaRob__vmt88 攻击触发【字符串实证】：防篡改+1252 && vt+224 ==1 → 存活
// && rand%100<1（1%）→ new(0x84) + sub_4DF1B0(5,3,1,宿主vt+388) 建 CNChangeWeaponElement
// → dword_8F84B8->vt+60("Common/CommonEffect/BuffIcon.img") 装图标资源 + sub_418DD0(2) → 挂宿主

int /*thiscall*/ CNEquipmentMusingRegaliaRob__vmt88(char *this, int nArg2, int nArg3, int nArg4, int nArg5, uint32_t *Block)
{
  int result; // eax
  int pThis_D4; // eax
  int nRand; // eax
  int v10; // et2
  int pThis_D42; // eax
  int v12; // eax
  int *v13; // edi
  int v14; // ebx
  int pThis_D43; // eax
  int pThis_D44; // eax

  result = (int)Block;
  if ( Block[3] == 0 )
  {
    result = sub_41C5A0(this + 1252);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this);
      if ( (uint8_t)result == 1 )
      {
        pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
        if ( (uint8_t)result != 0 )
        {
          nRand = rand();
          v10 = nRand % 100;
          result = nRand / 100;
          if ( v10 < 1 )
          {
            if ( operator new(0x84u) != nullptr )
            {
              pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
              v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 388))(pThis_D42);
              v13 = (int *)sub_4DF1B0(5, 3, 1, v12);
            }
            else
            {
              v13 = nullptr;
            }
            (*(void (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
              dword_8F84B8,
              "Common/CommonEffect/BuffIcon.img");
            result = sub_418DD0(2);
            if ( v13 != nullptr )
            {
              v14 = *v13;
              pThis_D43 = (*(int (/*thiscall*/ **)(char *, int, int, int, int))(*(uint32_t *)this + 212))(this, 1, result, 1, -1);
              pThis_D44 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 212))(this, pThis_D43);
              return (*(int (/*thiscall*/ **)(int *, int))(v14 + 56))(v13, pThis_D44);
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x5198D0 CNEquipmentMusingRegaliaRob__vmt4
// ------------------------------------------------------------
// CNEquipmentMusingRegaliaRob__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentMusingRegaliaRob__vmt4(void *Block, char pszArg2)
{
  sub_519900();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519900 sub_519900
// ------------------------------------------------------------
// CNEquipmentMusingRegaliaRob 析构基座

int /*thiscall*/ sub_519900(void **this)
{
  *this = &vftbl_CNEquipmentMusingRegaliaRob;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x519910 sub_519910
// ------------------------------------------------------------
// CNEquipmentZiegGarbCoat 构造器（齐格外套）：+364 状态槽清零

uint32_t */*thiscall*/ sub_519910(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentZiegGarbCoat;
  *(this + 364) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x519950 CNEquipmentZiegGarbCoat__vmt88
// ------------------------------------------------------------
// ★ CNEquipmentZiegGarbCoat__vmt88 攻击触发【鬼影步衣，全字符串实证】：attackinfo+12==0（物理）
// → +313 && vt+224 → 存活 && rand%100<1（1%）→ RTDynamicCast 宿主→CNSwordman（剑士限定）
// → 懒建 +364 状态对象；等级 = max(vt+1140(18), 2)（鬼影步技能等级）→ sub_47EF20(容器,0x12,0,等级,-1,-1)
// 取 stat 写状态+40 → "Common/CommonEffect/BuffIcon.img" 图标 → sub_49C620/49C5F0(20,0,-1,11) 施加
// → 播 "G_GHOSTSTEP_DISAPPEAR"（P32 TAG）

int /*thiscall*/ CNEquipmentZiegGarbCoat__vmt88(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int pArg6)
{
  int result; // eax
  int pObj; // eax
  int nRand; // eax
  int v10; // et2
  int v11; // eax
  int pObj2; // ebx
  void *pMem; // eax
  int pObj4; // eax
  int v15; // eax
  int fld_e364; // edi
  uint32_t *v17; // eax
  int v18; // ebx
  int fld_e3642; // edi
  int v20; // eax
  int fld_e3643; // eax
  int pObj3; // eax
  int v23; // [esp-1Ch] [ebp-34h]
  int v24; // [esp-14h] [ebp-2Ch]
  int v25; // [esp-10h] [ebp-28h]

  result = pArg6;
  if ( *(uint32_t *)(pArg6 + 12) == 0 )
  {
    result = sub_41C5A0(this + 313);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 224))(this);
      if ( (uint8_t)result != 0 )
      {
        pObj = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
        result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);
        if ( (uint8_t)result != 0 )
        {
          nRand = rand();
          v10 = nRand % 100;
          result = nRand / 100;
          if ( v10 < 1 )
          {
            v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
            result = __RTDynamicCast(
                       v11,
                       0,
                       &IRDActiveObject `RTTI Type Descriptor',
                       &CNSwordman `RTTI Type Descriptor',
                       0);
            pObj2 = result;
            if ( result != 0 )
            {
              if ( *(this + 364) == 0 )
              {
                pMem = operator new(0x50u);
                if ( pMem != nullptr )
                  pObj4 = sub_4B1030(pMem);
                else
                  pObj4 = 0;
                *(this + 364) = pObj4;
                *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 64))(pObj4) + 36) = 0;
              }
              if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1140))(pObj2, 18) >= 2 )
                v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 1140))(pObj2, 18);
              else
                v15 = 2;
              fld_e364 = *(this + 364);
              v25 = v15;
              v17 = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1160))(pObj2);
              v18 = sub_47EF20(v17, 0x12u, 0, v25, -1, -1);
              *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e364 + 64))(fld_e364) + 40) = v18;
              fld_e3642 = *(uint32_t *)*(this + 364);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8);
              v24 = sub_418DD0("Common/CommonEffect/BuffIcon.img");
              v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
              v20 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
              (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e3642 + 56))(*(this + 364), v20);
              (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 212))(this, 1, 1, 0);
              sub_49C620(v23, 1, v24);
              fld_e3643 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 364) + 64))(*(this + 364));
              (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 212))(
                this,
                1,
                0,
                0,
                *(uint32_t *)(fld_e3643 + 40));
              sub_49C5F0(20, 0, -1, 11);
              pObj3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 212))(this);
              return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pObj3 + 212))(
                       pObj3,
                       "G_GHOSTSTEP_DISAPPEAR",
                       -1,
                       0,
                       0);
            }
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x519B50 CNEquipmentZiegGarbCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentZiegGarbCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentZiegGarbCoat__vmt4(void *Block, char pszArg2)
{
  sub_519B80();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519B80 sub_519B80
// ------------------------------------------------------------
// CNEquipmentZiegGarbCoat 析构基座：+1456 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_519B80(int this)
{
  void (/*thiscall*/ ***pThis_5B0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentZiegGarbCoat;
  pThis_5B0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1456);
  if ( pThis_5B0 != nullptr )
    (**pThis_5B0)(pThis_5B0, 1);
  *(uint32_t *)(this + 1456) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x519BF0 sub_519BF0
// ------------------------------------------------------------
// CNEquipmentSilentFreyjaRobe 构造器（寂静弗雷娅法袍）：+sub_50F3D0

uint32_t */*thiscall*/ sub_519BF0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentSilentFreyjaRobe;
  sub_50F3D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x519C20 CNEquipmentSilentFreyjaRobe__vmt8C
// ------------------------------------------------------------
// CNEquipmentSilentFreyjaRobe__vmt8C 受击触发（41 行）

int /*thiscall*/ CNEquipmentSilentFreyjaRobe__vmt8C(char *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int nRand; // eax
  int v8; // et2
  int v9; // esi
  int v10; // ebx
  int pThis_D4; // eax

  result = sub_41C5A0(this + 1252);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this);
    if ( (uint8_t)result != 0 )
    {
      nRand = rand();
      v8 = nRand % 100;
      result = nRand / 100;
      if ( v8 < 2 )
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
          v9 = result;
          if ( result != 0 )
          {
            v10 = *(uint32_t *)result;
            pThis_D4 = (*(int (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 212))(this, 0);
            return (*(int (/*thiscall*/ **)(int, int, int, int))(v10 + 764))(v9, 6, 15, pThis_D4);
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x519CB0 CNEquipmentSilentFreyjaRobe__vmt4
// ------------------------------------------------------------
// CNEquipmentSilentFreyjaRobe__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentSilentFreyjaRobe__vmt4(void *Block, char pszArg2)
{
  sub_519CE0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519CE0 sub_519CE0
// ------------------------------------------------------------
// CNEquipmentSilentFreyjaRobe 析构基座（nullsub_3 + 0x5145B0）

int /*thiscall*/ sub_519CE0(void **this)
{
  *this = &vftbl_CNEquipmentSilentFreyjaRobe;
  nullsub_3();
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x519D30 sub_519D30
// ------------------------------------------------------------
// CNEquipmentAirVintageCoat 构造器（复古空气外套）：+sub_50F3D0

uint32_t */*thiscall*/ sub_519D30(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentAirVintageCoat;
  sub_50F3D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x519D60 CNEquipmentAirVintageCoat__vmt8C
// ------------------------------------------------------------
// CNEquipmentAirVintageCoat__vmt8C 受击触发（48 行）

int /*thiscall*/ CNEquipmentAirVintageCoat__vmt8C(char *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int pThis_D4; // eax
  int v8; // edi
  int v9; // ebx
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pThis_D44; // eax
  int v13; // eax
  int nRand; // eax
  int v15; // et2
  int v16; // [esp+4h] [ebp-8h]
  int v17; // [esp+8h] [ebp-4h]

  result = sub_41C5A0(this + 1252);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this);
    if ( (uint8_t)result != 0 )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
      if ( (uint8_t)result != 0 )
      {
        v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
        v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
        pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 120))(pThis_D42);
        pThis_D43 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 124))(pThis_D43);
        pThis_D44 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 52))(pThis_D44);
        srand((v9 + v16) * (v8 + v17 + v13));
        nRand = rand();
        v15 = nRand % 100;
        result = nRand / 100;
        if ( v15 < 1 )
        {
          (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          sub_49C620(1, 1, 0);
          (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          return sub_49C5F0(1, 0, 0, 8000);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x519E70 CNEquipmentAirVintageCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentAirVintageCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentAirVintageCoat__vmt4(void *Block, char pszArg2)
{
  sub_519EA0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x519EA0 sub_519EA0
// ------------------------------------------------------------
// CNEquipmentAirVintageCoat 析构基座

int /*thiscall*/ sub_519EA0(void **this)
{
  *this = &vftbl_CNEquipmentAirVintageCoat;
  nullsub_3();
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x519EF0 sub_519EF0
// ------------------------------------------------------------
// CNEquipmentManaLamellaRobe 构造器（玛那薄片法袍）

uint32_t */*thiscall*/ sub_519EF0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentManaLamellaRobe;
  return this;
}



// ------------------------------------------------------------
// 0x519F20 CNEquipmentManaLamellaRobe__vmt8C
// ------------------------------------------------------------
// CNEquipmentManaLamellaRobe__vmt8C 受击触发（65 行）

int /*thiscall*/ CNEquipmentManaLamellaRobe__vmt8C(char *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // edi
  int v8; // ebx
  int pThis_D4; // eax
  int pThis_D42; // eax
  int pThis_D43; // eax
  int v12; // eax
  int nRand; // eax
  int v14; // et2
  int pThis_D44; // eax
  int *v16; // edi
  int v17; // ebx
  int pThis_D45; // eax
  int pThis_D46; // eax
  int v20; // [esp+4h] [ebp-10h]
  int v21; // [esp+1Ch] [ebp+8h]

  result = sub_41C5A0(this + 1252);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
      if ( (uint8_t)result != 0 )
      {
        v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
        v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
        pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 120))(pThis_D4);
        pThis_D42 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        v20 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 124))(pThis_D42);
        pThis_D43 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 52))(pThis_D43);
        srand((v8 + v20) * (v7 + v21 + v12));
        nRand = rand();
        v14 = nRand % 100;
        result = nRand / 100;
        if ( v14 < 2 )
        {
          pThis_D44 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 308))(pThis_D44);
          if ( (uint8_t)result != 0 )
          {
            if ( operator new(0x64u) != nullptr )
              v16 = (int *)sub_50F270(200, 1000);
            else
              v16 = nullptr;
            v17 = *v16;
            pThis_D45 = (*(int (/*thiscall*/ **)(char *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 212))(
                    this,
                    0,
                    0,
                    0,
                    -1);
            pThis_D46 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 212))(this, pThis_D45);
            return (*(int (/*thiscall*/ **)(int *, int))(v17 + 56))(v16, pThis_D46);
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x51A080 CNEquipmentManaLamellaRobe__vmt4
// ------------------------------------------------------------
// CNEquipmentManaLamellaRobe__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentManaLamellaRobe__vmt4(void *Block, char pszArg2)
{
  sub_51A0B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51A0B0 sub_51A0B0
// ------------------------------------------------------------
// CNEquipmentManaLamellaRobe 析构基座

int /*thiscall*/ sub_51A0B0(void **this)
{
  *this = &vftbl_CNEquipmentManaLamellaRobe;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x51A0C0 sub_51A0C0
// ------------------------------------------------------------
// CNEquipmentBlackLunaTunic 构造器（黑色月神束衣）

uint32_t */*thiscall*/ sub_51A0C0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentBlackLunaTunic;
  return this;
}



// ------------------------------------------------------------
// 0x51A0F0 sub_51A0F0
// ------------------------------------------------------------
// 状态卸载（BlackLunaTunic）：+364 状态对象销毁

int /*thiscall*/ sub_51A0F0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e364)(uint32_t, int); // ecx
  int result; // eax

  fld_e364 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 364);
  if ( fld_e364 != nullptr )
    result = (**fld_e364)(fld_e364, 1);
  *(this + 364) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x51A110 CNEquipmentBlackLunaTunic__vmt8C
// ------------------------------------------------------------
// CNEquipmentBlackLunaTunic__vmt8C 受击触发（56 行）

int /*thiscall*/ CNEquipmentBlackLunaTunic__vmt8C(uint32_t **this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int v6; // edi
  int v7; // ebx
  int pObj2; // eax
  int pObj; // eax
  int pObj3; // eax
  int v11; // eax
  int result; // eax
  int nRand; // eax
  int v14; // et2
  int fld_e364; // edi
  int v16; // eax
  int v17; // eax
  int v18; // [esp+0h] [ebp-14h]
  int v19; // [esp+4h] [ebp-10h]
  int v20; // [esp+8h] [ebp-Ch]
  int v21; // [esp+Ch] [ebp-8h]
  int v22; // [esp+10h] [ebp-4h]

  v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
  v7 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
  pObj2 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
  v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);
  pObj = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
  v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
  pObj3 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
  v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 52))(pObj3);
  srand((v7 + v21) * (v6 + v22 + v11));
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
  if ( *(uint32_t *)(result + 20) == 2 )
  {
    result = sub_41C5A0(this + 313);
    if ( result != 0 )
    {
      result = ((int (/*thiscall*/ *)(uint32_t **))(*this)[56])(this);
      if ( (uint8_t)result != 0 )
      {
        nRand = rand();
        v14 = nRand % 100;
        result = nRand / 100;
        if ( v14 < 3 )
        {
          ((void (/*thiscall*/ *)(uint32_t **, int, int, uint32_t))(*this)[53])(this, 1, 1, 0);
          sub_49C620(v18, v19, v20);
          ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[53])(this, 1);
          sub_49C5F0(0, 0, 15000, v21);
          fld_e364 = **(this + 364);
          v16 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, int))(*this)[53])(this, 0, 0, 0, -1);
          v17 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[53])(this, v16);
          return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e364 + 56))(*(this + 364), v17);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x51A250 sub_51A250
// ------------------------------------------------------------
// BlackLunaTunic 辅助构造（34 行：装参数包并挂效果）

int /*thiscall*/ sub_51A250(uint32_t *this)
{
  uint32_t *pMem; // eax
  int *v3; // eax
  int v4; // edx
  int result; // eax
  int v6; // [esp+8h] [ebp-28h] BYREF
  char v7; // [esp+Ch] [ebp-24h]
  int v8; // [esp+10h] [ebp-20h]
  int v9; // [esp+14h] [ebp-1Ch]
  char v10; // [esp+18h] [ebp-18h]
  int v11; // [esp+1Ch] [ebp-14h]
  uint32_t *pMem2; // [esp+20h] [ebp-10h]
  int v13; // [esp+2Ch] [ebp-4h]

  v6 = 0;
  v7 = 0;
  v8 = 1112014848;
  v9 = 1;
  v10 = 0;
  v11 = 1112014848;
  pMem = operator new(0x7Cu);
  pMem2 = pMem;
  v13 = 0;
  if ( pMem != nullptr )
    v3 = sub_5101B0(pMem, (int)&v6, 2, 15000, 1);
  else
    v3 = nullptr;
  *(this + 364) = v3;
  v4 = *v3;
  v13 = -1;
  result = (*(int (/*thiscall*/ **)(int *))(v4 + 64))(v3);
  *(uint8_t *)(result + 36) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x51A2F0 CNEquipmentBlackLunaTunic__vmt4
// ------------------------------------------------------------
// CNEquipmentBlackLunaTunic__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentBlackLunaTunic__vmt4(void *Block, char pszArg2)
{
  sub_51A320();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51A320 sub_51A320
// ------------------------------------------------------------
// CNEquipmentBlackLunaTunic 析构基座

int /*thiscall*/ sub_51A320(void **this)
{
  *this = &vftbl_CNEquipmentBlackLunaTunic;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x51A330 sub_51A330
// ------------------------------------------------------------
// CNEquipmentAceAdventCoat 构造器（王牌降临外套）：调 sub_510CD0 装状态初始化器 E

uint32_t */*thiscall*/ sub_51A330(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentAceAdventCoat;
  sub_510CD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x51A390 CNEquipmentAceAdventCoat__vmt12C
// ------------------------------------------------------------
// CNEquipmentAceAdventCoat__vmt12C 周期 tick（38 行）

int /*thiscall*/ CNEquipmentAceAdventCoat__vmt12C(uint32_t **this)
{
  int result; // eax
  int pObj2; // edi
  int pObj; // ebx
  int v5; // eax
  int fld_e364; // edx
  int fld_e3642; // edi
  int v8; // eax
  int v9; // eax
  float v10; // [esp+4h] [ebp-8h]

  if ( sub_41C5A0(this + 313) == 0 || (uint8_t)(result = ((int (/*thiscall*/ *)(uint32_t **))(*this)[56])(this)) != 0 )
  {
    pObj2 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
    pObj = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
    v10 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 736))(pObj2);
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 740))(pObj);
    fld_e364 = **(this + 364);
    if ( (double)v5 * 0.15000001 <= v10 )
    {
      result = (*(int (**)(void))(fld_e364 + 80))();
      if ( (uint8_t)result == 1 )
        return (*(int (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 364) + 76))(*(this + 364), 0);
    }
    else
    {
      result = (*(int (**)(void))(fld_e364 + 80))();
      if ( (uint8_t)result == 0 )
      {
        fld_e3642 = **(this + 364);
        v8 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, int))(*this)[53])(this, 0, 0, 0, -1);
        v9 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[53])(this, v8);
        return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e3642 + 56))(*(this + 364), v9);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x51A480 CNEquipmentAceAdventCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentAceAdventCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentAceAdventCoat__vmt4(void *Block, char pszArg2)
{
  sub_51A4B0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51A4B0 sub_51A4B0
// ------------------------------------------------------------
// CNEquipmentAceAdventCoat 析构基座：+1456 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_51A4B0(int this)
{
  void (/*thiscall*/ ***pThis_5B0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentAceAdventCoat;
  pThis_5B0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1456);
  if ( pThis_5B0 != nullptr )
    (**pThis_5B0)(pThis_5B0, 1);
  *(uint32_t *)(this + 1456) = 0;
  *(uint32_t *)(this + 1340) = 0;
  *(uint32_t *)(this + 1336) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x51A520 sub_51A520
// ------------------------------------------------------------
// CNEquipmentTheEightyMasters 构造器（八十大师）

uint32_t */*thiscall*/ sub_51A520(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentTheEightyMasters;
  return this;
}



// ------------------------------------------------------------
// 0x51A550 CNEquipmentTheEightyMasters__vmt8C
// ------------------------------------------------------------
// CNEquipmentTheEightyMasters__vmt8C 受击触发（40 行）

int /*thiscall*/ CNEquipmentTheEightyMasters__vmt8C(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_D4; // eax
  int result; // eax
  int v8; // edi
  int v9; // ebx
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pThis_D44; // eax
  int v13; // eax
  int nRand; // eax
  int v15; // et2
  int v16; // [esp+4h] [ebp-8h]
  int v17; // [esp+8h] [ebp-4h]

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
    v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
    pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 120))(pThis_D42);
    pThis_D43 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 124))(pThis_D43);
    pThis_D44 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 52))(pThis_D44);
    srand((v9 + v16) * (v8 + v17 + v13));
    nRand = rand();
    v15 = nRand % 100;
    result = nRand / 100;
    if ( v15 < 1 )
    {
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      sub_49C620(1, 1, 0);
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      return sub_49C5F0(1, 0, 0, 8000);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x51A630 CNEquipmentTheEightyMasters__vmt4
// ------------------------------------------------------------
// CNEquipmentTheEightyMasters__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentTheEightyMasters__vmt4(void *Block, char pszArg2)
{
  sub_51A660();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51A660 sub_51A660
// ------------------------------------------------------------
// CNEquipmentTheEightyMasters 析构基座

int /*thiscall*/ sub_51A660(void **this)
{
  *this = &vftbl_CNEquipmentTheEightyMasters;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x51A670 sub_51A670
// ------------------------------------------------------------
// CNEquipmentNobleDignity 构造器（贵族威严）

uint32_t */*thiscall*/ sub_51A670(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentNobleDignity;
  return this;
}



// ------------------------------------------------------------
// 0x51A6A0 CNEquipmentNobleDignity__vmt8C
// ------------------------------------------------------------
// CNEquipmentNobleDignity__vmt8C 受击触发（51 行：效果含 CNSuperArmor 霸体 PO，见 0x51A7D0）

int /*thiscall*/ CNEquipmentNobleDignity__vmt8C(void *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int pThis_D4; // eax
  int result; // eax
  int v8; // edi
  int v9; // ebx
  int pThis_D42; // eax
  int pThis_D43; // eax
  int pThis_D44; // eax
  int v13; // eax
  int nRand; // eax
  int v15; // et2
  void *pMem; // eax
  int pObj; // edi
  int v18; // ebx
  int pThis_D45; // eax
  int pThis_D46; // eax
  void *Block; // [esp+4h] [ebp-14h]
  int v22; // [esp+8h] [ebp-10h]

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
  if ( (uint8_t)result != 0 )
  {
    v8 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 112);
    v9 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 116);
    pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D42 + 120))(pThis_D42);
    pThis_D43 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    Block = (void *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D43 + 124))(pThis_D43);
    pThis_D44 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D44 + 52))(pThis_D44);
    srand(((uint32_t)Block + v9) * (v8 + v22 + v13));
    nRand = rand();
    v15 = nRand % 100;
    result = nRand / 100;
    if ( v15 < 2 )
    {
      pMem = operator new(0x64u);
      if ( pMem != nullptr )
        pObj = sub_51A7D0(pMem);
      else
        pObj = 0;
      *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 40) = 15000;
      v18 = *(uint32_t *)pObj;
      pThis_D45 = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 212))(this, 0, 0, 0, -1);
      pThis_D46 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 212))(this, pThis_D45);
      return (*(int (/*thiscall*/ **)(int, int))(v18 + 56))(pObj, pThis_D46);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x51A7D0 sub_51A7D0
// ------------------------------------------------------------
// CNSuperArmor 构造器（霸体状态 PO）：+22 区向量/字符串初始化（P37 [DAMAGE TYPE]=SUPERARMOR 的运行时对应物）

uint32_t */*thiscall*/ sub_51A7D0(uint32_t *this)
{
  sub_4B1030(this);
  *this = &vftbl_CNSuperArmor;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  sub_605910(this);
  sub_605AC0(this);
  return this;
}



// ------------------------------------------------------------
// 0x51A830 CNSuperArmor__vmt0
// ------------------------------------------------------------
// CNSuperArmor__vmt0 删除析构壳

void */*thiscall*/ CNSuperArmor__vmt0(void *Block, char pszArg2)
{
  sub_51A860();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51A860 sub_51A860
// ------------------------------------------------------------
// CNSuperArmor 析构基座：sub_605B30 + 释放 +22 → 基类链

int /*thiscall*/ sub_51A860(void **this)
{
  int result; // eax

  *this = &vftbl_CNSuperArmor;
  sub_605B30();
  if ( *(this + 22) != nullptr )
    j__free(*(this + 22));
  *(this + 22) = nullptr;
  *(this + 23) = nullptr;
  *(this + 24) = nullptr;
  *this = &vftbl_IRDAppendage;
  result = sub_5F6640(this);
  *((uint8_t *)this + 12) = 0;
  *(this + 2) = &vftbl_nengine__IObject;
  return result;
}



// ------------------------------------------------------------
// 0x51A8E0 CNEquipmentNobleDignity__vmt4
// ------------------------------------------------------------
// CNEquipmentNobleDignity__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentNobleDignity__vmt4(void *Block, char pszArg2)
{
  sub_51A910();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51A910 sub_51A910
// ------------------------------------------------------------
// CNEquipmentNobleDignity 析构基座

int /*thiscall*/ sub_51A910(void **this)
{
  *this = &vftbl_CNEquipmentNobleDignity;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x51A920 sub_51A920
// ------------------------------------------------------------
// CNEquipmentArtiMarpissaCoat 构造器（阿蒂马皮萨外套）

uint32_t */*thiscall*/ sub_51A920(uint32_t *this, char ArgList, int nArg3, int nArg4, int nArg5)
{
  sub_514350((int)this, ArgList, nArg3, nArg4, nArg5);
  *this = &vftbl_CNEquipmentArtiMarpissaCoat;
  return this;
}



// ------------------------------------------------------------
// 0x51A950 CNEquipmentArtiMarpissaCoat__vmt9C
// ------------------------------------------------------------
// CNEquipmentArtiMarpissaCoat__vmt9C 受击触发（21 行：防篡改+1252 门 → 效果）

int /*thiscall*/ CNEquipmentArtiMarpissaCoat__vmt9C(char *this, int nArg2)
{
  int pThis_D4; // eax
  int pObj; // eax
  int v5; // eax
  uint64_t v6; // rax

  if ( sub_41C5A0(this + 1252) != 0
    && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this) != 0
    && nArg2 == 7 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D4 + 792))(pThis_D4, 8);
    if ( pObj != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);
      v6 = (uint64_t)((double)sub_41A5E0(v5 + 112) * 0.2);
      sub_41A590((unsigned int)(this + 1476), SHIDWORD(v6), v6);
    }
  }
  return CNSpecificStateEquipment__vmt9C(nArg2);
}



// ------------------------------------------------------------
// 0x51A9E0 CNEquipmentArtiMarpissaCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentArtiMarpissaCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentArtiMarpissaCoat__vmt4(void *Block, char pszArg2)
{
  sub_51AA10();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51AA10 sub_51AA10
// ------------------------------------------------------------
// CNEquipmentArtiMarpissaCoat 析构基座

int /*thiscall*/ sub_51AA10(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentArtiMarpissaCoat;
  return sub_5143E0(this);
}



// ------------------------------------------------------------
// 0x51AA20 sub_51AA20
// ------------------------------------------------------------
// CNEquipmentPlatanicCombatantCoat 构造器（普拉坦战士外套）

uint32_t */*thiscall*/ sub_51AA20(uint32_t *this, char ArgList, int nArg3, int nArg4, int nArg5)
{
  sub_514350((int)this, ArgList, nArg3, nArg4, nArg5);
  *this = &vftbl_CNEquipmentPlatanicCombatantCoat;
  return this;
}



// ------------------------------------------------------------
// 0x51AA50 CNEquipmentPlatanicCombatantCoat__vmt9C
// ------------------------------------------------------------
// CNEquipmentPlatanicCombatantCoat__vmt9C 受击触发（21 行）

int /*thiscall*/ CNEquipmentPlatanicCombatantCoat__vmt9C(char *this, int nArg2)
{
  int pThis_D4; // eax
  int pObj; // eax
  int v5; // eax
  uint64_t v6; // rax

  if ( sub_41C5A0(this + 1252) != 0
    && (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this) != 0
    && nArg2 == 12 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
    pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D4 + 792))(pThis_D4, 8);
    if ( pObj != 0 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);
      v6 = (uint64_t)((double)sub_41A5E0(v5 + 112) * 0.15000001);
      sub_41A590((unsigned int)(this + 1476), SHIDWORD(v6), v6);
    }
  }
  return CNSpecificStateEquipment__vmt9C(nArg2);
}



// ------------------------------------------------------------
// 0x51AAE0 CNEquipmentPlatanicCombatantCoat__vmt4
// ------------------------------------------------------------
// CNEquipmentPlatanicCombatantCoat__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentPlatanicCombatantCoat__vmt4(void *Block, char pszArg2)
{
  sub_51AB10();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51AB10 sub_51AB10
// ------------------------------------------------------------
// CNEquipmentPlatanicCombatantCoat 析构基座

int /*thiscall*/ sub_51AB10(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentPlatanicCombatantCoat;
  return sub_5143E0(this);
}



// ------------------------------------------------------------
// 0x51AB20 sub_51AB20
// ------------------------------------------------------------
// CNEquipmentCurseArmorTodpursResist 构造器（诅咒铠甲-托德普斯抗性）：调 sub_510DB0 装状态初始化器 F

uint32_t */*thiscall*/ sub_51AB20(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentCurseArmorTodpursResist;
  sub_510DB0(this);
  return this;
}



// ------------------------------------------------------------
// 0x51AB90 CNEquipmentCurseArmorTodpursResist__vmt88
// ------------------------------------------------------------
// CNEquipmentCurseArmorTodpursResist__vmt88 攻击触发（45 行）

char /*thiscall*/ CNEquipmentCurseArmorTodpursResist__vmt88(uint32_t **this, int nArg2, int nArg3, char pszArg4, int nArg5, int nArg6)
{
  int pThis_139; // eax
  int nRand; // eax
  int v9; // et2
  int pObj; // eax
  int pObj2; // eax
  int fld_e364; // edi
  int v13; // eax
  int v14; // eax

  LOBYTE(pThis_139) = pszArg4;
  if ( pszArg4 == 0 )
  {
    pThis_139 = sub_41C5A0(this + 313);
    if ( pThis_139 != 0 )
    {
      LOBYTE(pThis_139) = ((int (/*thiscall*/ *)(uint32_t **))(*this)[56])(this);
      if ( (uint8_t)pThis_139 != 0 )
      {
        nRand = rand();
        v9 = nRand % 100;
        pThis_139 = nRand / 100;
        if ( v9 < 2 )
        {
          pObj = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
          pThis_139 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 840))(pObj);
          if ( pThis_139 == 8 || pThis_139 == 7 || pThis_139 == 12 )
          {
            pObj2 = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
            pThis_139 = (*(int (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)pObj2 + 8))(pObj2, nArg2, 0);
            if ( pThis_139 < 128 )
            {
              *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(this + 364) + 64))(*(this + 364)) + 40) = 30000;
              fld_e364 = **(this + 364);
              v13 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, int))(*this)[53])(this, 0, 0, 0, -1);
              v14 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[53])(this, v13);
              LOBYTE(pThis_139) = (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e364 + 56))(*(this + 364), v14);
            }
          }
        }
      }
    }
  }
  return pThis_139;
}



// ------------------------------------------------------------
// 0x51AC80 CNEquipmentCurseArmorTodpursResist__vmt4
// ------------------------------------------------------------
// CNEquipmentCurseArmorTodpursResist__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentCurseArmorTodpursResist__vmt4(void *Block, char pszArg2)
{
  sub_51ACB0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51ACB0 sub_51ACB0
// ------------------------------------------------------------
// CNEquipmentCurseArmorTodpursResist 析构基座：+1456 状态销毁 → sub_4BADD0

int /*thiscall*/ sub_51ACB0(int this)
{
  void (/*thiscall*/ ***pThis_5B0)(uint32_t, int); // ecx

  *(uint32_t *)this = &vftbl_CNEquipmentCurseArmorTodpursResist;
  pThis_5B0 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 1456);
  if ( pThis_5B0 != nullptr )
    (**pThis_5B0)(pThis_5B0, 1);
  *(uint32_t *)(this + 1456) = 0;
  return sub_5145B0((void **)this);
}



// ------------------------------------------------------------
// 0x51AD20 sub_51AD20
// ------------------------------------------------------------
// CNEquipmentHyperJammer 构造器（超级干扰器）

char */*thiscall*/ sub_51AD20(char *this, char ArgList, int nArg3)
{
  sub_5140A0(this, ArgList, nArg3);  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
  *(uint32_t *)this = &vftbl_CNEquipmentHyperJammer;
  return this;
}



// ------------------------------------------------------------
// 0x51AD50 CNEquipmentHyperJammer__vmt120
// ------------------------------------------------------------
// CNEquipmentHyperJammer__vmt120 事件处理：a2 ∈ {3,8,15} → 防篡改读写修正（16 行）

void /*thiscall*/ CNEquipmentHyperJammer__vmt120(void *this, int nArg2, int nArg3)
{
  int pThis_D4; // eax
  unsigned int *v4; // esi
  uint64_t v5; // rax

  if ( nArg2 == 3 || nArg2 == 8 || nArg2 == 15 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    v4 = (unsigned int *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D4 + 772))(pThis_D4, nArg2);
    if ( v4 != nullptr )
    {
      v5 = (uint64_t)((double)v4[23] * 0.85000002);
      (*(void (/*fastcall*/ **)(unsigned int *, uint32_t, uint32_t))(*v4 + 84))(v4, HIDWORD(v5), v5);
    }
  }
}



// ------------------------------------------------------------
// 0x51ADB0 CNEquipmentHyperJammer__vmt4
// ------------------------------------------------------------
// CNEquipmentHyperJammer__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentHyperJammer__vmt4(void *Block, char pszArg2)
{
  sub_51ADE0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51ADE0 sub_51ADE0
// ------------------------------------------------------------
// CNEquipmentHyperJammer 析构基座 → sub_4BADD0

int /*thiscall*/ sub_51ADE0(uint32_t *this)
{
  *this = &vftbl_CNEquipmentHyperJammer;
  return sub_4BADD0(this);
}



// ------------------------------------------------------------
// 0x51ADF0 sub_51ADF0
// ------------------------------------------------------------
// CNEquipmentDestroyHeart 构造器（毁灭之心）

uint32_t */*thiscall*/ sub_51ADF0(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentDestroyHeart;
  return this;
}



// ------------------------------------------------------------
// 0x51AE20 CNEquipmentDestroyHeart__vmt88
// ------------------------------------------------------------
// CNEquipmentDestroyHeart__vmt88 攻击触发（45 行）

int /*thiscall*/ CNEquipmentDestroyHeart__vmt88(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int result; // eax
  int pThis_D4; // eax
  int nRand; // eax
  int v10; // et2
  int *v11; // esi
  int v12; // ebx
  int pThis_D42; // eax
  int v14; // [esp+10h] [ebp+8h]

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 308))(pThis_D4);
    if ( (uint8_t)result != 0 )
    {
      nRand = rand();
      v10 = nRand % 100;
      result = nRand / 100;
      if ( v10 < 2 )
      {
        result = __RTDynamicCast(
                   nArg2,
                   0,
                   &IRDCollisionObject `RTTI Type Descriptor',
                   &IRDActiveObject `RTTI Type Descriptor',
                   0);
        v11 = (int *)result;
        if ( result != 0 )
        {
          result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)result + 736))(result);
          if ( result > 0 )
          {
            v12 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *))(*v11 + 736))(v11) * 0.80000001);
            v14 = *v11;
            pThis_D42 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
            return (*(int (/*thiscall*/ **)(int *, int, uint32_t, int))(v14 + 728))(v11, v12, 0, pThis_D42);
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x51AEE0 CNEquipmentDestroyHeart__vmt4
// ------------------------------------------------------------
// CNEquipmentDestroyHeart__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentDestroyHeart__vmt4(void *Block, char pszArg2)
{
  sub_51AF10();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51AF10 sub_51AF10
// ------------------------------------------------------------
// CNEquipmentDestroyHeart 析构基座

int /*thiscall*/ sub_51AF10(void **this)
{
  *this = &vftbl_CNEquipmentDestroyHeart;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x51AF20 sub_51AF20
// ------------------------------------------------------------
// CNEquipmentDevilByPassImpact 构造器（恶魔贯穿冲击）

uint32_t */*thiscall*/ sub_51AF20(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentDevilByPassImpact;
  return this;
}



// ------------------------------------------------------------
// 0x51AF50 CNEquipmentDevilByPassImpact__vmt134
// ------------------------------------------------------------
// CNEquipmentDevilByPassImpact__vmt134 受击处理（33 行）

char /*thiscall*/ CNEquipmentDevilByPassImpact__vmt134(void *this, int nArg2, void *Block)
{
  char result; // al
  uint32_t *pMem; // edi
  int pThis_D4; // eax
  int pObj; // eax
  int v8; // eax
  int *v9; // edi
  int v10; // ebx
  int pThis_D42; // eax
  int pThis_D43; // eax

  result = (char)Block;
  if ( (uint8_t)Block != 0 )
  {
    pMem = operator new(0x7Cu);
    if ( pMem != nullptr )
    {
      pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
      pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_D4 + 772))(pThis_D4);
      v8 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 32))(pObj, 0);
      v9 = sub_4B3DF0(pMem, 5, 1, -1046478848, v8, 12);
    }
    else
    {
      v9 = nullptr;
    }
    v10 = *v9;
    pThis_D42 = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)this + 212))(this, 0, 0, 0, -1);
    pThis_D43 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 212))(this, pThis_D42);
    return (*(int (/*thiscall*/ **)(int *, int))(v10 + 56))(v9, pThis_D43);
  }
  return result;
}



// ------------------------------------------------------------
// 0x51B010 CNEquipmentDevilByPassImpact__vmt4
// ------------------------------------------------------------
// CNEquipmentDevilByPassImpact__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentDevilByPassImpact__vmt4(void *Block, char pszArg2)
{
  sub_51B040();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51B040 sub_51B040
// ------------------------------------------------------------
// CNEquipmentDevilByPassImpact 析构基座

int /*thiscall*/ sub_51B040(void **this)
{
  *this = &vftbl_CNEquipmentDevilByPassImpact;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x51B050 sub_51B050
// ------------------------------------------------------------
// CNEquipmentSleepySpring 构造器（嗜睡之泉）：operator new(0x80) → sub_4D6810(1120403456=100.0f,1000,1,1) 状态对象

int /*thiscall*/ sub_51B050(int this, char ArgList, void *Block)
{
  int pObj; // eax

  sub_5140A0((char *)this, ArgList, (int)Block);  // 【装备 PO 构造基座 CNRDEquipment（+1160 包体容器 = docs…】
  *(uint32_t *)this = &vftbl_CNEquipmentSleepySpring;
  if ( operator new(0x80u) != nullptr )
    pObj = sub_4D6810(1120403456, 1000, 1, 1);
  else
    pObj = 0;
  *(uint32_t *)(this + 1348) = pObj;
  *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x51B0F0 CNEquipmentSleepySpring__vmt88
// ------------------------------------------------------------
// CNEquipmentSleepySpring__vmt88 攻击触发（54 行：概率掷 → 状态施加）

int /*thiscall*/ CNEquipmentSleepySpring__vmt88(uint32_t **this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int result; // eax
  int *v8; // edi
  int pObj; // eax
  int v10; // ebx
  int *v11; // edi
  int v12; // ebx
  int v13; // eax
  int fld_e337; // edi
  int v15; // eax
  int v16; // eax
  int v17; // [esp-8h] [ebp-10h]

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)result != 0 )
  {
    result = __RTDynamicCast(
               nArg2,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &IRDActiveObject `RTTI Type Descriptor',
               0);
    v8 = (int *)result;
    if ( result != 0 )
    {
      pObj = ((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);
      if ( (uint8_t)result != 0 )
      {
        result = sub_4D6750(8, 2.0, 0);
        if ( (uint8_t)result != 0 )
        {
          v10 = *v8;
          v17 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[53])(this, 1);
          (*(void (/*thiscall*/ **)(int *))(v10 + 764))(v8);
          ((void (/*thiscall*/ *)(uint32_t **, int, int, uint32_t))(*this)[53])(this, 8, 1084227584, 0);
          result = sub_4D6750(8, COERCE_FLOAT(1), v17);
          if ( (uint8_t)result != 0 )
          {
            v11 = (int *)((int (/*thiscall*/ *)(uint32_t **))(*this)[53])(this);
            v12 = *v11;
            v13 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[53])(this, 1);
            (*(void (/*thiscall*/ **)(int *, int, int, int))(v12 + 764))(v11, 8, 1, v13);
            fld_e337 = **(this + 337);
            v15 = ((int (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, int))(*this)[53])(this, 0, 0, 0, -1);
            v16 = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[53])(this, v15);
            return (*(int (/*thiscall*/ **)(uint32_t, int))(fld_e337 + 56))(*(this + 337), v16);
          }
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x51B200 CNEquipmentSleepySpring__vmt4
// ------------------------------------------------------------
// CNEquipmentSleepySpring__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentSleepySpring__vmt4(void *Block, char pszArg2)
{
  sub_51B230();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51B230 sub_51B230
// ------------------------------------------------------------
// CNEquipmentSleepySpring 析构基座：sub_51B280 卸状态 → sub_4BADD0

int /*thiscall*/ sub_51B230(uint32_t *this)
{
  *this = &vftbl_CNEquipmentSleepySpring;
  sub_51B280();
  return sub_4BADD0(this);
}



// ------------------------------------------------------------
// 0x51B280 sub_51B280
// ------------------------------------------------------------
// 状态卸载（SleepySpring）：+337 状态对象销毁

int /*thiscall*/ sub_51B280(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e337)(uint32_t, int); // ecx
  int result; // eax

  fld_e337 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 337);
  if ( fld_e337 != nullptr )
    result = (**fld_e337)(fld_e337, 1);
  *(this + 337) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x51B2A0 sub_51B2A0
// ------------------------------------------------------------
// CNEquipmentSilverKnifeOfEmily 构造器（艾米莉银刀）：防篡读(this+81)×0.5 → 防篡写 this+373（P24）

uint32_t */*thiscall*/ sub_51B2A0(uint32_t *this, char ArgList, int nArg3)
{
  uint64_t pThis_51; // rax

  sub_5141B0((int)this, ArgList, nArg3, 1, 0);
  *this = &vftbl_CNEquipmentSilverKnifeOfEmily;
  pThis_51 = (uint64_t)((double)sub_41A5E0((unsigned int)(this + 81)) * 0.5);
  sub_41A590((unsigned int)(this + 373), SHIDWORD(pThis_51), pThis_51);
  return this;
}



// ------------------------------------------------------------
// 0x51B320 CNEquipmentSilverKnifeOfEmily__vmt130
// ------------------------------------------------------------
// CNEquipmentSilverKnifeOfEmily__vmt130 条件查询：sub_4DAB60(6) 目标类型 6 检查（P16 类型门同款【类型语义待验证】）

bool /*stdcall*/ CNEquipmentSilverKnifeOfEmily__vmt130(int nArg1)
{
  return (uint8_t)sub_4DAB60(6) != 0;
}



// ------------------------------------------------------------
// 0x51B340 CNEquipmentSilverKnifeOfEmily__vmt4
// ------------------------------------------------------------
// CNEquipmentSilverKnifeOfEmily__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentSilverKnifeOfEmily__vmt4(void *Block, char pszArg2)
{
  sub_51B370();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51B370 sub_51B370
// ------------------------------------------------------------
// CNEquipmentSilverKnifeOfEmily 析构基座

int /*thiscall*/ sub_51B370(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentSilverKnifeOfEmily;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x51B380 sub_51B380
// ------------------------------------------------------------
// CNEquipmentCurseOfKhazan 构造器（哈赞诅咒）：同上 ×0.5 → this+373

uint32_t */*thiscall*/ sub_51B380(uint32_t *this, char ArgList, int nArg3)
{
  uint64_t pThis_51; // rax

  sub_5141B0((int)this, ArgList, nArg3, 1, 0);
  *this = &vftbl_CNEquipmentCurseOfKhazan;
  pThis_51 = (uint64_t)((double)sub_41A5E0((unsigned int)(this + 81)) * 0.5);
  sub_41A590((unsigned int)(this + 373), SHIDWORD(pThis_51), pThis_51);
  return this;
}



// ------------------------------------------------------------
// 0x51B400 CNEquipmentCurseOfKhazan__vmt130
// ------------------------------------------------------------
// CNEquipmentCurseOfKhazan__vmt130 条件查询：宿主 vt+776(11)（状态 11 激活查询）

bool /*thiscall*/ CNEquipmentCurseOfKhazan__vmt130(void *this, int nArg2)
{
  int pThis_D4; // eax

  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D4 + 776))(pThis_D4, 11) != 0;
}



// ------------------------------------------------------------
// 0x51B420 CNEquipmentCurseOfKhazan__vmt4
// ------------------------------------------------------------
// CNEquipmentCurseOfKhazan__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentCurseOfKhazan__vmt4(void *Block, char pszArg2)
{
  sub_51B450();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51B450 sub_51B450
// ------------------------------------------------------------
// CNEquipmentCurseOfKhazan 析构基座

int /*thiscall*/ sub_51B450(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentCurseOfKhazan;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x51B460 sub_51B460
// ------------------------------------------------------------
// CNEquipmentVermote 构造器（维尔莫特）：防篡读 ×0.2 → this+373

uint32_t */*thiscall*/ sub_51B460(uint32_t *this, char ArgList, int nArg3)
{
  uint64_t pThis_51; // rax

  sub_5141B0((int)this, ArgList, nArg3, 1, 0);
  *this = &vftbl_CNEquipmentVermote;
  pThis_51 = (uint64_t)((double)sub_41A5E0((unsigned int)(this + 81)) * 0.2);
  sub_41A590((unsigned int)(this + 373), SHIDWORD(pThis_51), pThis_51);
  return this;
}



// ------------------------------------------------------------
// 0x51B4E0 CNEquipmentVermote__vmt130
// ------------------------------------------------------------
// CNEquipmentVermote__vmt130 条件查询：a1 vt+128() > 0（资源/HP 正值门）

bool /*stdcall*/ CNEquipmentVermote__vmt130(int nArg1)
{
  return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 128))(nArg1) > 0;
}



// ------------------------------------------------------------
// 0x51B500 CNEquipmentVermote__vmt4
// ------------------------------------------------------------
// CNEquipmentVermote__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentVermote__vmt4(void *Block, char pszArg2)
{
  sub_51B530();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51B530 sub_51B530
// ------------------------------------------------------------
// CNEquipmentVermote 析构基座

int /*thiscall*/ sub_51B530(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentVermote;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x51B540 sub_51B540
// ------------------------------------------------------------
// CNEquipmentBreathOfSelion 构造器（塞里昂之息）

uint32_t */*thiscall*/ sub_51B540(uint32_t *this, char ArgList, int nArg3)
{
  sub_5144A0(this, ArgList, nArg3);
  *this = &vftbl_CNEquipmentBreathOfSelion;
  return this;
}



// ------------------------------------------------------------
// 0x51B570 CNEquipmentBreathOfSelion__vmt88
// ------------------------------------------------------------
// CNEquipmentBreathOfSelion__vmt88 攻击触发（67 行：概率掷 → 效果施加）

char /*thiscall*/ CNEquipmentBreathOfSelion__vmt88(int *this, int *pDwArg2, int nArg3, int nArg4, int nArg5, int pArg6)
{
  int v6; // eax
  int nRand; // eax
  int v9; // et2
  int v10; // edx
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v15; // [esp-20h] [ebp-44h]
  int v16; // [esp-1Ch] [ebp-40h]
  int v17; // [esp-18h] [ebp-3Ch]
  int nArg52; // [esp-Ch] [ebp-30h]
  int v19; // [esp-8h] [ebp-2Ch]
  void *pBuf[4]; // [esp+8h] [ebp-1Ch] BYREF
  int v21; // [esp+20h] [ebp-4h]

  LOBYTE(v6) = nArg5;
  if ( (uint8_t)nArg5 == 0 )
  {
    LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg2 + 40))(pDwArg2, 17);
    if ( (uint8_t)v6 != 0 )
    {
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 308))(pDwArg2);
      if ( (uint8_t)v6 != 0 )
      {
        nRand = rand();
        v9 = nRand % 100;
        v6 = nRand / 100;
        if ( v9 < 5 )
        {
          if ( *(uint32_t *)(pArg6 + 60) == 1 && (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 128))(pDwArg2) <= 0 )
          {
            memset(&pBuf[1], 0, 12);
            v10 = *this;
            v21 = 0;
            v11 = *pDwArg2;
            v12 = (*(int (/*thiscall*/ **)(int *))(v10 + 212))(this);
            nArg5 = (*(int (/*thiscall*/ **)(int *, int))(v11 + 660))(pDwArg2, v12);
            sub_431230((int)pBuf, &nArg5);
            nArg5 = -1;
            sub_431230((int)pBuf, &nArg5);
            nArg5 = 0;
            sub_431230((int)pBuf, &nArg5);
            nArg5 = *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 348))(pDwArg2) + 124);
            sub_431230((int)pBuf, &nArg5);
            (*(void (/*thiscall*/ **)(int *, int, void **, int, uint32_t))(*pDwArg2 + 560))(pDwArg2, 3, pBuf, 2, 0);
            v21 = -1;
            sub_5E5260(pBuf);
          }
          LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg2 + 40))(pDwArg2, 17);
          if ( (uint8_t)v6 != 0 )
          {
            nArg5 = 0;
            v19 = sub_605840(&nArg5, pDwArg2, nArg3, 1);
            nArg52 = nArg5;
            v17 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 128))(pDwArg2);
            v16 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 124))(pDwArg2);
            v15 = (*(int (/*thiscall*/ **)(int *))(*pDwArg2 + 120))(pDwArg2);
            v13 = (*(int (/*thiscall*/ **)(int *))(*this + 212))(this);
            LOBYTE(v6) = sub_4E4A50(v13, 42004, 1, v15, v16, v17, 1, 0, nArg52, v19);
          }
        }
      }
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x51B700 CNEquipmentBreathOfSelion__vmt4
// ------------------------------------------------------------
// CNEquipmentBreathOfSelion__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentBreathOfSelion__vmt4(void *Block, char pszArg2)
{
  sub_51B730();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51B730 sub_51B730
// ------------------------------------------------------------
// CNEquipmentBreathOfSelion 析构基座

int /*thiscall*/ sub_51B730(void **this)
{
  *this = &vftbl_CNEquipmentBreathOfSelion;
  return sub_5145B0(this);
}



// ------------------------------------------------------------
// 0x51B740 sub_51B740
// ------------------------------------------------------------
// CNEquipmentHwakEyes 构造器（鹰眼，RTTI 原名拼写）：防篡读 ×0.2 → this+373

uint32_t */*thiscall*/ sub_51B740(uint32_t *this, char ArgList, int nArg3)
{
  uint64_t pThis_51; // rax

  sub_5141B0((int)this, ArgList, nArg3, 0, 1);
  *this = &vftbl_CNEquipmentHwakEyes;
  pThis_51 = (uint64_t)((double)sub_41A5E0((unsigned int)(this + 81)) * 0.2);
  sub_41A590((unsigned int)(this + 373), SHIDWORD(pThis_51), pThis_51);
  return this;
}



// ------------------------------------------------------------
// 0x51B7C0 CNEquipmentHwakEyes__vmt130
// ------------------------------------------------------------
// CNEquipmentHwakEyes__vmt130 条件查询：vt+40(17) && RTDynamicCast→IRDActiveObject（12 行）

bool /*thiscall*/ CNEquipmentHwakEyes__vmt130(void *this, int nArg2)
{
  int pThis_D4; // eax

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) == 0
    || __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0) == 0 )
  {
    return false;
  }
  (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
  return sub_4E5B50(nArg2, pThis_D4);
}



// ------------------------------------------------------------
// 0x51B830 CNEquipmentHwakEyes__vmt88
// ------------------------------------------------------------
// CNEquipmentHwakEyes__vmt88 攻击触发（36 行）

char /*thiscall*/ CNEquipmentHwakEyes__vmt88(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int pObj; // eax
  int pThis_D4; // eax
  int *v9; // esi
  int v10; // ebx
  int pThis_D42; // eax

  LOBYTE(pObj) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( (uint8_t)pObj != 0 )
  {
    (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    pThis_D4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 212))(this);
    LOBYTE(pObj) = sub_4E5B50(nArg2, pThis_D4);
    if ( (uint8_t)pObj != 0 )
    {
      pObj = __RTDynamicCast(
             nArg2,
             0,
             &IRDCollisionObject `RTTI Type Descriptor',
             &IRDActiveObject `RTTI Type Descriptor',
             0);
      v9 = (int *)pObj;
      if ( pObj != 0 )
      {
        LOBYTE(pObj) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj);
        if ( (uint8_t)pObj != 0 )
        {
          v10 = *v9;
          pThis_D42 = (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 212))(this, 0);
          LOBYTE(pObj) = (*(int (/*thiscall*/ **)(int *, int, int, int, int))(v10 + 760))(v9, 3, 1106247680, 6, pThis_D42);
        }
      }
    }
  }
  return pObj;
}



// ------------------------------------------------------------
// 0x51B8C0 CNEquipmentHwakEyes__vmt4
// ------------------------------------------------------------
// CNEquipmentHwakEyes__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentHwakEyes__vmt4(void *Block, char pszArg2)
{
  sub_51B8F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51B8F0 sub_51B8F0
// ------------------------------------------------------------
// CNEquipmentHwakEyes 析构基座

int /*thiscall*/ sub_51B8F0(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentHwakEyes;
  return sub_514260(this);
}



// ------------------------------------------------------------
// 0x51B900 sub_51B900
// ------------------------------------------------------------
// CNEquipmentQuicksilverSolJacket 构造器（水银索尔夹克）

uint32_t */*thiscall*/ sub_51B900(uint32_t *this, char ArgList, int nArg3)
{
  sub_5141B0((int)this, ArgList, nArg3, 1, 0);
  *this = &vftbl_CNEquipmentQuicksilverSolJacket;
  return this;
}



// ------------------------------------------------------------
// 0x51B930 CNEquipmentQuicksilverSolJacket__vmt130
// ------------------------------------------------------------
// CNEquipmentQuicksilverSolJacket__vmt130 受击 stats 修正（22 行，BabyBlue 族模式）

char /*thiscall*/ CNEquipmentQuicksilverSolJacket__vmt130(char *this, int nArg2)
{
  int pThis_D4; // eax
  int pObj; // eax
  int v5; // eax
  uint64_t v6; // rax

  if ( sub_41C5A0(this + 1252) == 0
    || (*(uint8_t (/*thiscall*/ **)(char *))(*(uint32_t *)this + 224))(this) == 0
    || (uint8_t)sub_4DAB60(6) == 0 )
  {
    return 0;
  }
  pThis_D4 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 212))(this);
  pObj = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_D4 + 792))(pThis_D4, 8);
  if ( pObj != 0 )
  {
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 176))(pObj);
    v6 = (uint64_t)((double)sub_41A5E0(v5 + 112) * 0.5);
    sub_41A590((unsigned int)(this + 1492), SHIDWORD(v6), v6);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x51B9C0 CNEquipmentQuicksilverSolJacket__vmt4
// ------------------------------------------------------------
// CNEquipmentQuicksilverSolJacket__vmt4 删除析构壳

void */*thiscall*/ CNEquipmentQuicksilverSolJacket__vmt4(void *Block, char pszArg2)
{
  sub_51B9F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x51B9F0 sub_51B9F0
// ------------------------------------------------------------
// CNEquipmentQuicksilverSolJacket 析构基座

int /*thiscall*/ sub_51B9F0(void *this)
{
  *(uint32_t *)this = &vftbl_CNEquipmentQuicksilverSolJacket;
  return sub_514260(this);
}


