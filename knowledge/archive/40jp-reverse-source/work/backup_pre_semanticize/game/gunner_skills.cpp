// ============================================================
// 【40JP逆向源代码工程】game/gunner_skills.cpp
// 模块: 枪手/地图机关 PassiveObject（0x53 区）
// 来源: work/dump_miscb.txt  区块: 0x530000-0x540000
// 层级: L2 转写层 + L1 锚点精修（函数体保持 Hex-Rays 忠实输出，仅升级注释）
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 244
// ------------------------------------------------------------
// ★ 定性更正：本区主体并非枪手射击技能，而是【陷阱/地图机关/破坏物/精灵 PO 族】
//   （RTTI 原名 CNMineTrap/CNChandelier/CNFairy…）。枪手武器的射击特效 PO 在
//   missing_misc_b.cpp（ViperBulletShell.ptl/G_MACHINEGUNA/WAVE_CREATE/QUICK_TURN/
//   SIZZLE_LOOP 所在）与 combat/passive_object.cpp。本文件技能级 PO 为
//   龙首炮台（FlameThrower.ptl）、荆棘根（AUXO_ROOT_ATK/TRAP_GRASS_HIT）、
//   阳光爆发（SunBurstLayer1-5.ani）、齐柏林飞艇弹（Zepplin/Ani/Bullet*.ani）。
// 资源证据（本文件字符串字面量）：Particle/FlameThrower.ptl、Particle/FlameThrowerVertical.ptl、
//   Particle/steam.ptl、Animation/SunBurstLayer%d.ani、
//   PassiveObject/Monster/Zepplin/Ani/{BulletBlast,BulletSmoke,BulletSmokeL,BulletSmokeR}.ani、
//   ../Trap/Animation/CageBack.ani、音效 TAG：AUXO_ROOT_ATK / TRAP_GRASS_HIT
// 交叉引用：
//   0x53A220 巨函数（size=17574）→ src/combat/bigfunc_53A220_sub_53A220.cpp
//   PO 构造基座 sub_52EA60/sub_52EE30 位于 pvp_ui.cpp；sub_52ED60 位于 missing_misc_b.cpp
//   池化特效生成四件套：sub_42FCB0(228) 特效池 → sub_431860/sub_431920 动画 →
//   sub_44B6C0(284)+sub_44E0D0 池化对象 → sub_45FE80 入演播层 2（P33）
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// ============
// 【分区 1】陷阱/地图机关 PO 族（0x535AD0-0x538D90）
// 每类机关 = 构造器（基座 sub_52EA60/52ED60 → vftbl → sub_62xxxx 数据解析器）
// + vmt0 删除析构壳 + 析构基座 三件套。基座与解析器分驻 0x52 区（pvp_ui.cpp/missing_misc_b.cpp）。
// 类清单：地雷/滚石/陷阱笼/吊灯/摇风机/旋转刺/天空鱼巢/爆炸油桶/幻觉花/沼泽系/地刺/
// 哥布林碉堡/海草/藤蔓/海星卵/任务笼/精灵族(Fairy)/音效地板/喷泉/龙首炮台族等。
// ============

// 0x535AD0 sub_535AD0
// ------------------------------------------------------------
// CNMineTrap 构造器（地雷）：CNRDTrap 基座 + 双 vftbl（+0/+972）+ sub_61FC40/sub_620090 解析

uint32_t */*thiscall*/ sub_535AD0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *(this + 243) = &vftbl_CNRDTrap;
  *(this + 245) = 0;
  *(this + 246) = 0;
  *(this + 247) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  *(this + 247) = 0;
  *this = &vftbl_CNMineTrap;
  *(this + 243) = &CNMineTrap::`vftable';
  sub_61FC40(this);
  sub_620090(a3);
  return this;
}



// ------------------------------------------------------------
// 0x535B80 CNMineTrap__vmt0
// ------------------------------------------------------------
// CNMineTrap__vmt0 删除析构壳

void */*thiscall*/ CNMineTrap__vmt0(void *Block, char a2)
{
  sub_535BB0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535BB0 sub_535BB0
// ------------------------------------------------------------
// CNMineTrap 析构基座：+972 退 CNRDTrap → 释放 +980 → sub_4E2040

int /*thiscall*/ sub_535BB0(int this)
{
  *(uint32_t *)this = &vftbl_CNMineTrap;
  *(uint32_t *)(this + 972) = &CNMineTrap::`vftable';
  nullsub_3();
  *(uint32_t *)(this + 972) = &vftbl_CNRDTrap;
  if ( *(uint32_t *)(this + 980) != 0 )
    j__free(*(void **)(this + 980));
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x535C50 sub_535C50
// ------------------------------------------------------------
// CNRollingStone 构造器（滚石陷阱）：+992/+996 两个 szPassword 字符串槽 + sub_6201B0/620540

int /*thiscall*/ sub_535C50(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &vftbl_CNRollingStone;
  *(uint32_t *)(this + 992) = 0;
  sub_41BFE0((void **)(this + 992), szPassword);
  *(uint32_t *)(this + 996) = 0;
  sub_41BFE0((void **)(this + 996), szPassword);
  sub_6201B0(this);
  sub_620540(a3);
  return this;
}



// ------------------------------------------------------------
// 0x535CF0 CNRollingStone__vmt214
// ------------------------------------------------------------
// CNRollingStone__vmt214 停止钩子：表现对象(+28)速度/角速度清零 → sub_620300(0.0)

int /*thiscall*/ CNRollingStone__vmt214(uint32_t *this, int a2, int a3, int a4)
{
  *(uint32_t *)(*(this + 28) + 16) = 0;
  *(uint32_t *)(*(this + 28) + 28) = 0;
  return sub_620300(0.0);
}



// ------------------------------------------------------------
// 0x535D10 CNRollingStone__vmt0
// ------------------------------------------------------------
// CNRollingStone__vmt0 删除析构壳

void */*thiscall*/ CNRollingStone__vmt0(void *Block, char a2)
{
  sub_535D40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535D40 sub_535D40
// ------------------------------------------------------------
// CNRollingStone 析构基座：sub_620210 + 释放 +249/+248 → sub_4E2040

int /*thiscall*/ sub_535D40(void **this)
{
  *this = &vftbl_CNRollingStone;
  sub_620210();
  sub_41B010(this + 249);
  sub_41B010(this + 248);
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x535DB0 sub_535DB0
// ------------------------------------------------------------
// CNTrapCage 构造器（陷阱笼）

uint32_t */*thiscall*/ sub_535DB0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNTrapCage;
  sub_620B20(this);
  sub_620CA0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x535E10 CNTrapCage__vmt0
// ------------------------------------------------------------
// CNTrapCage__vmt0 删除析构壳

void */*thiscall*/ CNTrapCage__vmt0(void *Block, char a2)
{
  sub_535E40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535E40 sub_535E40
// ------------------------------------------------------------
// CNTrapCage 析构基座

int /*thiscall*/ sub_535E40(void **this)
{
  *this = &vftbl_CNTrapCage;
  sub_620BC0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x535E90 sub_535E90
// ------------------------------------------------------------
// CNChandelier 构造器（吊灯，可击落破坏物）：+244..246 清零

uint32_t */*thiscall*/ sub_535E90(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNChandelier;
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  sub_621100(this);
  sub_621140(a3);
  return this;
}



// ------------------------------------------------------------
// 0x535F10 CNChandelier__vmt0
// ------------------------------------------------------------
// CNChandelier__vmt0 删除析构壳

void */*thiscall*/ CNChandelier__vmt0(void *Block, char a2)
{
  sub_535F40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x535F40 sub_535F40
// ------------------------------------------------------------
// CNChandelier 析构基座：释放 +976

int /*thiscall*/ sub_535F40(int this)
{
  *(uint32_t *)this = &vftbl_CNChandelier;
  nullsub_3();
  if ( *(uint32_t *)(this + 976) != 0 )
    j__free(*(void **)(this + 976));
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x535FC0 sub_535FC0
// ------------------------------------------------------------
// CNWindShaker 构造器（摇风机/风扇机关）

uint32_t */*thiscall*/ sub_535FC0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNWindShaker;
  *(this + 249) = 0;
  *(this + 250) = 0;
  *(this + 251) = 0;
  nullsub_3();
  sub_621630(a3);
  return this;
}



// ------------------------------------------------------------
// 0x536040 CNWindShaker__vmt0
// ------------------------------------------------------------
// CNWindShaker__vmt0 删除析构壳

void */*thiscall*/ CNWindShaker__vmt0(void *Block, char a2)
{
  sub_536070();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536070 sub_536070
// ------------------------------------------------------------
// CNWindShaker 析构基座：释放 +996

int /*thiscall*/ sub_536070(int this)
{
  *(uint32_t *)this = &vftbl_CNWindShaker;
  nullsub_3();
  if ( *(uint32_t *)(this + 996) != 0 )
    j__free(*(void **)(this + 996));
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1004) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x5360F0 sub_5360F0
// ------------------------------------------------------------
// CNSpiner 构造器（旋转刺/转盘机关）

uint32_t */*thiscall*/ sub_5360F0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNSpiner;
  sub_621F20(this);
  sub_6227D0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x536150 CNSpiner__vmt0
// ------------------------------------------------------------
// CNSpiner__vmt0 删除析构壳

void */*thiscall*/ CNSpiner__vmt0(void *Block, char a2)
{
  sub_536180();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536180 sub_536180
// ------------------------------------------------------------
// CNSpiner 析构基座

int /*thiscall*/ sub_536180(void **this)
{
  *this = &vftbl_CNSpiner;
  sub_621F30();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5361D0 sub_5361D0
// ------------------------------------------------------------
// CNSpaceFishLair 构造器（天空鱼巢，spawn 点）：+276 清零 + vmt2F4 装附属

uint32_t */*thiscall*/ sub_5361D0(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNSpaceFishLair;
  *(this + 276) = 0;
  *(this + 277) = 0;
  *(this + 278) = 0;
  CNSpaceFishLair__vmt2F4(a3);
  return this;
}



// ------------------------------------------------------------
// 0x536240 CNSpaceFishLair__vmt0
// ------------------------------------------------------------
// CNSpaceFishLair__vmt0 删除析构壳

void */*thiscall*/ CNSpaceFishLair__vmt0(void *Block, char a2)
{
  sub_536270();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536270 sub_536270
// ------------------------------------------------------------
// CNSpaceFishLair 析构基座：sub_60A950 + 释放 +276 → sub_52EE30

int /*thiscall*/ sub_536270(void **this)
{
  *this = &vftbl_CNSpaceFishLair;
  sub_60A950();
  if ( *(this + 276) != nullptr )
    j__free(*(this + 276));
  *(this + 276) = nullptr;
  *(this + 277) = nullptr;
  *(this + 278) = nullptr;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x5362F0 sub_5362F0
// ------------------------------------------------------------
// CNExplosiveOil 构造器（爆炸油桶，可引爆破坏物）

uint32_t */*thiscall*/ sub_5362F0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNExplosiveOil;
  sub_623330(this);
  return this;
}



// ------------------------------------------------------------
// 0x536350 sub_536350
// ------------------------------------------------------------
// CNHallucinationFlower 构造器（幻觉花）

uint32_t */*thiscall*/ sub_536350(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNHallucinationFlower;
  sub_623500(this);
  sub_6235F0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5363B0 CNHallucinationFlower__vmt0
// ------------------------------------------------------------
// CNHallucinationFlower__vmt0 删除析构壳

void */*thiscall*/ CNHallucinationFlower__vmt0(void *Block, char a2)
{
  sub_5363E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5363E0 sub_5363E0
// ------------------------------------------------------------
// CNHallucinationFlower 析构基座

int /*thiscall*/ sub_5363E0(void **this)
{
  *this = &vftbl_CNHallucinationFlower;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536430 sub_536430
// ------------------------------------------------------------
// CNSwamp 构造器（沼泽，减速/束缚地面）：+1112 计时位、+1108 CNTimer、+1096 标志、+276=a5 类型

uint8_t */*thiscall*/ sub_536430(uint8_t *this, int a2, int a3, int a4, int a5)
{
  sub_52ED60(a2, a3);
  *(uint32_t *)this = &vftbl_CNSwamp;
  *(this + 1112) = 0;
  *((uint32_t *)this + 277) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 279) = 0;
  *(this + 1120) = 1;
  *(this + 1122) = 0;
  *(this + 1121) = 0;
  *((uint32_t *)this + 283) = 0;
  *((uint32_t *)this + 282) = 0;
  *((uint32_t *)this + 281) = 0;
  *(this + 1096) = 1;
  *((uint32_t *)this + 276) = a5;
  sub_623AE0(a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x5364E0 sub_5364E0
// ------------------------------------------------------------
// CNStarFishEggRequid 构造器（海星卵-鱿鱼变体）：CNSwamp(17,2) 参数化

uint8_t */*thiscall*/ sub_5364E0(uint8_t *this, int a2, int a3)
{
  sub_536430(this, a2, a3, 17, 2);
  *(uint32_t *)this = &vftbl_CNStarFishEggRequid;
  return this;
}



// ------------------------------------------------------------
// 0x536510 sub_536510
// ------------------------------------------------------------
// CNMagmaSwamp 构造器（岩浆沼泽）：CNSwamp 全参透传

uint8_t */*thiscall*/ sub_536510(uint8_t *this, int a2, int a3, int a4, int a5)
{
  sub_536430(this, a2, a3, a4, a5);
  *(uint32_t *)this = &vftbl_CNMagmaSwamp;
  return this;
}



// ------------------------------------------------------------
// 0x536540 CNSwamp__vmt0
// ------------------------------------------------------------
// CNSwamp__vmt0 删除析构壳

void */*thiscall*/ CNSwamp__vmt0(void *Block, char a2)
{
  sub_536570();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536570 sub_536570
// ------------------------------------------------------------
// CNSwamp 析构基座：+277 退 nengine__IObject

int /*thiscall*/ sub_536570(uint32_t *this)
{
  *this = &vftbl_CNSwamp;
  *(this + 277) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 1112) = 0;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x536590 sub_536590
// ------------------------------------------------------------
// CNFloorNiddle 构造器（地刺机关）

uint32_t */*thiscall*/ sub_536590(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNFloorNiddle;
  sub_624CC0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5365F0 CNFloorNiddle__vmt0
// ------------------------------------------------------------
// CNFloorNiddle__vmt0 删除析构壳

void */*thiscall*/ CNFloorNiddle__vmt0(void *Block, char a2)
{
  sub_536620();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536620 sub_536620
// ------------------------------------------------------------
// CNFloorNiddle 析构基座

int /*thiscall*/ sub_536620(void **this)
{
  *this = &vftbl_CNFloorNiddle;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536630 sub_536630
// ------------------------------------------------------------
// CNGoblinBunker 构造器（哥布林碉堡）：+280 清零 + vmt2E4 附属

uint32_t */*thiscall*/ sub_536630(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNGoblinBunker;
  *(this + 280) = 0;
  *(this + 281) = 0;
  *(this + 282) = 0;
  CNGoblinBunker__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x5366A0 CNGoblinBunker__vmt0
// ------------------------------------------------------------
// CNGoblinBunker__vmt0 删除析构壳

void */*thiscall*/ CNGoblinBunker__vmt0(void *Block, char a2)
{
  sub_5366D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5366D0 sub_5366D0
// ------------------------------------------------------------
// CNGoblinBunker 析构基座：+536750 卸状态 + 释放 +280

int /*thiscall*/ sub_5366D0(void **this)
{
  *this = &vftbl_CNGoblinBunker;
  sub_536750();
  if ( *(this + 280) != nullptr )
    j__free(*(this + 280));
  *(this + 280) = nullptr;
  *(this + 281) = nullptr;
  *(this + 282) = nullptr;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x536750 sub_536750
// ------------------------------------------------------------
// 附属状态卸载：+277 对象 vt+0(1) 销毁（Bunker 系复用）

int /*thiscall*/ sub_536750(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 277);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 277) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x536770 sub_536770
// ------------------------------------------------------------
// CNTwistFootHold 构造器（扭转立足点）

uint32_t */*thiscall*/ sub_536770(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNTwistFootHold;
  nullsub_3();
  sub_626220(this);
  return this;
}



// ------------------------------------------------------------
// 0x5367D0 CNTwistFootHold__vmt0
// ------------------------------------------------------------
// CNTwistFootHold__vmt0 删除析构壳

void */*thiscall*/ CNTwistFootHold__vmt0(void *Block, char a2)
{
  sub_536800();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536800 sub_536800
// ------------------------------------------------------------
// CNTwistFootHold 析构基座

int /*thiscall*/ sub_536800(void **this)
{
  *this = &vftbl_CNTwistFootHold;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536850 sub_536850
// ------------------------------------------------------------
// CNSeaGrass 构造器（海草，缠绕系）

uint32_t */*thiscall*/ sub_536850(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNSeaGrass;
  sub_626D30(this);
  return this;
}



// ------------------------------------------------------------
// 0x5368B0 CNSeaGrass__vmt0
// ------------------------------------------------------------
// CNSeaGrass__vmt0 删除析构壳

void */*thiscall*/ CNSeaGrass__vmt0(void *Block, char a2)
{
  sub_5368E0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5368E0 sub_5368E0
// ------------------------------------------------------------
// CNSeaGrass 析构基座

int /*thiscall*/ sub_5368E0(void **this)
{
  *this = &vftbl_CNSeaGrass;
  sub_6269A0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536930 sub_536930
// ------------------------------------------------------------
// CNEntangleVineTrigger 构造器（藤蔓触发器）：+980 CNTimer、+992 使能、+996..1024 参数区

int /*thiscall*/ sub_536930(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &vftbl_CNEntangleVineTrigger;
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 980) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 988) = 0;
  *(uint8_t *)(this + 992) = 1;
  *(uint8_t *)(this + 994) = 0;
  *(uint8_t *)(this + 993) = 0;
  *(uint32_t *)(this + 1004) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 1016) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  sub_626F20(this);
  return this;
}



// ------------------------------------------------------------
// 0x5369E0 CNEntangleVineTrigger__vmt0
// ------------------------------------------------------------
// CNEntangleVineTrigger__vmt0 删除析构壳

void */*thiscall*/ CNEntangleVineTrigger__vmt0(void *Block, char a2)
{
  sub_536A10();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536A10 sub_536A10
// ------------------------------------------------------------
// CNEntangleVineTrigger 析构基座：释放 +1016 → +980 退 IObject

int /*thiscall*/ sub_536A10(int this)
{
  *(uint32_t *)this = &vftbl_CNEntangleVineTrigger;
  if ( *(uint32_t *)(this + 1016) != 0 )
    j__free(*(void **)(this + 1016));
  *(uint32_t *)(this + 1016) = 0;
  *(uint32_t *)(this + 1020) = 0;
  *(uint32_t *)(this + 1024) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 980) = &vftbl_nengine__IObject;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x536A60 sub_536A60
// ------------------------------------------------------------
// CNEntangleVine 构造器（缠绕藤蔓本体）：+246 清零

uint32_t */*thiscall*/ sub_536A60(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNEntangleVine;
  *(this + 246) = 0;
  *(this + 247) = 0;
  *(this + 248) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x536AC0 CNEntangleVine__vmt0
// ------------------------------------------------------------
// CNEntangleVine__vmt0 删除析构壳

void */*thiscall*/ CNEntangleVine__vmt0(void *Block, char a2)
{
  sub_536AF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536AF0 sub_536AF0
// ------------------------------------------------------------
// CNEntangleVine 析构基座：释放 +984

int /*thiscall*/ sub_536AF0(int this)
{
  *(uint32_t *)this = &vftbl_CNEntangleVine;
  if ( *(uint32_t *)(this + 984) != 0 )
    j__free(*(void **)(this + 984));
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x536B40 sub_536B40
// ------------------------------------------------------------
// CNStarfishEgg 构造器（海星卵，孵化巢）：+972 CNTimer、+984 使能

int /*thiscall*/ sub_536B40(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &vftbl_CNStarfishEgg;
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 972) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 980) = 0;
  *(uint8_t *)(this + 984) = 1;
  *(uint8_t *)(this + 986) = 0;
  *(uint8_t *)(this + 985) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 988) = 0;
  sub_627BE0((uint32_t **)this);
  return this;
}



// ------------------------------------------------------------
// 0x536BE0 CNStarfishEgg__vmt0
// ------------------------------------------------------------
// CNStarfishEgg__vmt0 删除析构壳

void */*thiscall*/ CNStarfishEgg__vmt0(void *Block, char a2)
{
  sub_536C10();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536C10 sub_536C10
// ------------------------------------------------------------
// CNStarfishEgg 析构基座：+243 退 IObject

int /*thiscall*/ sub_536C10(void **this)
{
  *this = &vftbl_CNStarfishEgg;
  *(this + 243) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 976) = 0;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536C30 sub_536C30
// ------------------------------------------------------------
// CNSweepingLegOfLotus 构造器（横扫莲花腿）：基座 sub_534E50 + sub_628260

uint32_t */*thiscall*/ sub_536C30(uint32_t *this, int a2, int a3)
{
  sub_534E50(a2, a3);
  *this = &vftbl_CNSweepingLegOfLotus;
  sub_628260(a3);
  return this;
}



// ------------------------------------------------------------
// 0x536C90 CNLegOfLotus__vmt0
// ------------------------------------------------------------
// CNSweepingLegOfLotus__vmt0 删除析构壳（标记沿用 RTTI 名 CNLegOfLotus）

void */*thiscall*/ CNLegOfLotus__vmt0(void *Block, char a2)
{
  sub_534F10();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536CC0 sub_536CC0
// ------------------------------------------------------------
// CNPassiveObjectTrigger 构造器（通用 PO 触发器）

uint32_t */*thiscall*/ sub_536CC0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNPassiveObjectTrigger;
  sub_627EB0(this);
  return this;
}



// ------------------------------------------------------------
// 0x536D20 CNPassiveObjectTrigger__vmt0
// ------------------------------------------------------------
// CNPassiveObjectTrigger__vmt0 删除析构壳

void */*thiscall*/ CNPassiveObjectTrigger__vmt0(void *Block, char a2)
{
  sub_536D50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536D50 sub_536D50
// ------------------------------------------------------------
// CNPassiveObjectTrigger 析构基座

int /*thiscall*/ sub_536D50(void **this)
{
  *this = &vftbl_CNPassiveObjectTrigger;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536D60 sub_536D60
// ------------------------------------------------------------
// CNBellForZealots 构造器（狂信者之钟）：vmt2E4 附属

uint32_t */*thiscall*/ sub_536D60(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNBellForZealots;
  CNBellForZealots__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x536DC0 CNBellForZealots__vmt0
// ------------------------------------------------------------
// CNBellForZealots__vmt0 删除析构壳

void */*thiscall*/ CNBellForZealots__vmt0(void *Block, char a2)
{
  sub_536DF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536DF0 sub_536DF0
// ------------------------------------------------------------
// CNBellForZealots 析构基座

int /*thiscall*/ sub_536DF0(uint32_t *this)
{
  *this = &vftbl_CNBellForZealots;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x536E00 sub_536E00
// ------------------------------------------------------------
// CNGravityChanger 构造器（重力反转区域）

uint32_t */*thiscall*/ sub_536E00(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNGravityChanger;
  nullsub_3();
  nullsub_1(a3);
  return this;
}



// ------------------------------------------------------------
// 0x536E60 CNGravityChanger__vmt0
// ------------------------------------------------------------
// CNGravityChanger__vmt0 删除析构壳

void */*thiscall*/ CNGravityChanger__vmt0(void *Block, char a2)
{
  sub_536E90();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536E90 sub_536E90
// ------------------------------------------------------------
// CNGravityChanger 析构基座

int /*thiscall*/ sub_536E90(void **this)
{
  *this = &vftbl_CNGravityChanger;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536EE0 sub_536EE0
// ------------------------------------------------------------
// CNDroppingRockTrigger 构造器（落石触发器）

uint32_t */*thiscall*/ sub_536EE0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNDroppingRockTrigger;
  sub_628930(this);
  return this;
}



// ------------------------------------------------------------
// 0x536F40 CNDroppingRockTrigger__vmt0
// ------------------------------------------------------------
// CNDroppingRockTrigger__vmt0 删除析构壳

void */*thiscall*/ CNDroppingRockTrigger__vmt0(void *Block, char a2)
{
  sub_536F70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x536F70 sub_536F70
// ------------------------------------------------------------
// CNDroppingRockTrigger 析构基座

int /*thiscall*/ sub_536F70(void **this)
{
  *this = &vftbl_CNDroppingRockTrigger;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536F80 sub_536F80
// ------------------------------------------------------------
// CNDroppingRock 构造器（落石本体）

uint32_t */*thiscall*/ sub_536F80(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNDroppingRock;
  sub_628CF0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x536FE0 CNDroppingRock__vmt0
// ------------------------------------------------------------
// CNDroppingRock__vmt0 删除析构壳

void */*thiscall*/ CNDroppingRock__vmt0(void *Block, char a2)
{
  sub_537010();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537010 sub_537010
// ------------------------------------------------------------
// CNDroppingRock 析构基座

int /*thiscall*/ sub_537010(void **this)
{
  *this = &vftbl_CNDroppingRock;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537020 sub_537020
// ------------------------------------------------------------
// CNFlappingBanner 构造器（飘扬旗帜，装饰破坏物）

uint32_t */*thiscall*/ sub_537020(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNFlappingBanner;
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x537080 CNFlappingBanner__vmt0
// ------------------------------------------------------------
// CNFlappingBanner__vmt0 删除析构壳

void */*thiscall*/ CNFlappingBanner__vmt0(void *Block, char a2)
{
  sub_5370B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5370B0 sub_5370B0
// ------------------------------------------------------------
// CNFlappingBanner 析构基座：sub_5FF980 + 释放 +976

int /*thiscall*/ sub_5370B0(int this)
{
  *(uint32_t *)this = &vftbl_CNFlappingBanner;
  sub_5FF980();
  if ( *(uint32_t *)(this + 976) != 0 )
    j__free(*(void **)(this + 976));
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x537130 sub_537130
// ------------------------------------------------------------
// CNBehemothHelipad 构造器（贝希摩斯停机坪）：CNRDObject__vmtCC(100, 图像ID, 0,0,0,0) 设定显示

uint32_t */*thiscall*/ sub_537130(uint32_t *this, char a2, int a3)
{
  int *v4; // eax

  sub_52EA60(this, a2, a3);
  v4 = (int *)*(this + 36);
  *this = &vftbl_CNBehemothHelipad;
  CNRDObject__vmtCC(this, 100, *v4, 0, 0, 0, 0);
  return this;
}



// ------------------------------------------------------------
// 0x5371A0 CNBehemothHelipad__vmt0
// ------------------------------------------------------------
// CNBehemothHelipad__vmt0 删除析构壳

void */*thiscall*/ CNBehemothHelipad__vmt0(void *Block, char a2)
{
  sub_5371D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5371D0 sub_5371D0
// ------------------------------------------------------------
// CNBehemothHelipad 析构基座

int /*thiscall*/ sub_5371D0(void **this)
{
  *this = &vftbl_CNBehemothHelipad;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5371E0 sub_5371E0
// ------------------------------------------------------------
// CNDragonHeadSide 构造器（侧面龙首炮台基类）：vmt2E4 附属

uint32_t */*thiscall*/ sub_5371E0(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNDragonHeadSide;
  CNDragonHeadSide__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x537240 sub_537240
// ------------------------------------------------------------
// CNDragonHeadSide 析构基座

int /*thiscall*/ sub_537240(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadSide;
  nullsub_3();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537290 CNDragonHeadSide__vmt0
// ------------------------------------------------------------
// CNDragonHeadSide__vmt0 删除析构壳

uint32_t */*thiscall*/ CNDragonHeadSide__vmt0(uint32_t *Block, char a2)
{
  sub_537240(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5372C0 sub_5372C0
// ------------------------------------------------------------
// ★ CNDragonHeadSideFlame 构造器（侧龙首-火焰）【资源实证】：new(0x12C) 粒子发射器 →
// sub_4C3640("Particle/FlameThrower.ptl", this)（P36 发射器挂接）→ +280 存发射器、+281=80、+282=50 参数

uint32_t */*thiscall*/ sub_5372C0(uint32_t *this, int a2, void *Block)
{
  int v4; // eax

  sub_5371E0(this, a2, (int)Block);
  *this = &vftbl_CNDragonHeadSideFlame;
  nullsub_3();
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v4 = sub_4C3640(this + 91, "Particle/FlameThrower.ptl", this);
    else
      v4 = sub_4C3640(*(this + 91), "Particle/FlameThrower.ptl", this);
  }
  else
  {
    v4 = 0;
  }
  *(this + 280) = v4;
  *(this + 281) = 80;
  *(this + 282) = 50;
  return this;
}



// ------------------------------------------------------------
// 0x537380 sub_537380
// ------------------------------------------------------------
// CNDragonHeadSideFlame 析构基座：sub_629010 → 退基类

int /*thiscall*/ sub_537380(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadSideFlame;
  sub_629010();
  return sub_537240(this);
}



// ------------------------------------------------------------
// 0x5373D0 CNDragonHeadSideFlame__vmt0
// ------------------------------------------------------------
// CNDragonHeadSideFlame__vmt0 删除析构壳

uint32_t */*thiscall*/ CNDragonHeadSideFlame__vmt0(uint32_t *Block, char a2)
{
  sub_537380(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537400 sub_537400
// ------------------------------------------------------------
// CNDragonHeadSideNentan 构造器（侧龙首-燃烧弹 Nentan）

uint32_t */*thiscall*/ sub_537400(uint32_t *this, int a2, int a3)
{
  sub_5371E0(this, a2, a3);
  *this = &vftbl_CNDragonHeadSideNentan;
  CNDragonHeadSideNentan__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x537460 sub_537460
// ------------------------------------------------------------
// CNDragonHeadSideNentan 析构基座

int /*thiscall*/ sub_537460(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadSideNentan;
  nullsub_3();
  return sub_537240(this);
}



// ------------------------------------------------------------
// 0x5374B0 CNDragonHeadSideNentan__vmt0
// ------------------------------------------------------------
// CNDragonHeadSideNentan__vmt0 删除析构壳

uint32_t */*thiscall*/ CNDragonHeadSideNentan__vmt0(uint32_t *Block, char a2)
{
  sub_537460(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5374E0 sub_5374E0
// ------------------------------------------------------------
// CNDragonHeadSideGas 构造器（侧龙首-毒瓦斯）

uint32_t */*thiscall*/ sub_5374E0(uint32_t *this, int a2, int a3)
{
  sub_5371E0(this, a2, a3);
  *this = &vftbl_CNDragonHeadSideGas;
  CNDragonHeadSideGas__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x537540 sub_537540
// ------------------------------------------------------------
// CNDragonHeadSideGas 析构基座

int /*thiscall*/ sub_537540(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadSideGas;
  nullsub_3();
  return sub_537240(this);
}



// ------------------------------------------------------------
// 0x537590 CNDragonHeadSideGas__vmt0
// ------------------------------------------------------------
// CNDragonHeadSideGas__vmt0 删除析构壳

uint32_t */*thiscall*/ CNDragonHeadSideGas__vmt0(uint32_t *Block, char a2)
{
  sub_537540(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5375C0 sub_5375C0
// ------------------------------------------------------------
// ★ CNDragonHeadFrontFlame 构造器（正面龙首-火焰）【资源实证】：sub_4C3640(
// "Particle/FlameThrowerVertical.ptl")（垂直喷射粒子）→ +1120 存发射器、+1124=42、+1128=55

int /*thiscall*/ sub_5375C0(int this, int a2, void *Block)
{
  int v4; // eax

  sub_5372C0((uint32_t *)this, a2, Block);
  *(uint32_t *)this = &vftbl_CNDragonHeadFrontFlame;
  *(uint8_t *)(this + 1109) = 0;
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      v4 = sub_4C3640(this + 364, "Particle/FlameThrowerVertical.ptl", this);
    else
      v4 = sub_4C3640(*(uint32_t *)(this + 364), "Particle/FlameThrowerVertical.ptl", this);
  }
  else
  {
    v4 = 0;
  }
  *(uint32_t *)(this + 1120) = v4;
  *(uint32_t *)(this + 1124) = 42;
  *(uint32_t *)(this + 1128) = 55;
  return this;
}



// ------------------------------------------------------------
// 0x537680 CNDragonHeadFrontFlame__vmt0
// ------------------------------------------------------------
// CNDragonHeadFrontFlame__vmt0 删除析构壳

void */*thiscall*/ CNDragonHeadFrontFlame__vmt0(void *Block, char a2)
{
  sub_5376B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5376B0 sub_5376B0
// ------------------------------------------------------------
// CNDragonHeadFrontFlame 析构基座 → 退 SideFlame

int /*thiscall*/ sub_5376B0(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadFrontFlame;
  return sub_537380(this);
}



// ------------------------------------------------------------
// 0x5376C0 sub_5376C0
// ------------------------------------------------------------
// CNDragonHeadFrontNentan 构造器（正面龙首-燃烧弹）

int /*thiscall*/ sub_5376C0(int this, int a2, int a3)
{
  sub_537400((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &vftbl_CNDragonHeadFrontNentan;
  *(uint8_t *)(this + 1109) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x5376F0 CNDragonHeadFrontNentan__vmt0
// ------------------------------------------------------------
// CNDragonHeadFrontNentan__vmt0 删除析构壳

void */*thiscall*/ CNDragonHeadFrontNentan__vmt0(void *Block, char a2)
{
  sub_537720();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537720 sub_537720
// ------------------------------------------------------------
// CNDragonHeadFrontNentan 析构基座

int /*thiscall*/ sub_537720(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadFrontNentan;
  return sub_537460(this);
}



// ------------------------------------------------------------
// 0x537730 sub_537730
// ------------------------------------------------------------
// CNDragonHeadFrontGas 构造器（正面龙首-毒瓦斯）

int /*thiscall*/ sub_537730(int this, int a2, int a3)
{
  sub_5374E0((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &vftbl_CNDragonHeadFrontGas;
  *(uint8_t *)(this + 1109) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x537760 CNDragonHeadFrontGas__vmt0
// ------------------------------------------------------------
// CNDragonHeadFrontGas__vmt0 删除析构壳

void */*thiscall*/ CNDragonHeadFrontGas__vmt0(void *Block, char a2)
{
  sub_537790();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537790 sub_537790
// ------------------------------------------------------------
// CNDragonHeadFrontGas 析构基座

int /*thiscall*/ sub_537790(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadFrontGas;
  return sub_537540(this);
}



// ------------------------------------------------------------
// 0x5377A0 sub_5377A0
// ------------------------------------------------------------
// CNCystalPillar 构造器（水晶柱，RTTI 原名拼写 Cystal）

uint32_t */*thiscall*/ sub_5377A0(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNCystalPillar;
  nullsub_3();
  CNCystalPillar__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x537800 CNCystalPillar__vmt0
// ------------------------------------------------------------
// CNCystalPillar__vmt0 删除析构壳

void */*thiscall*/ CNCystalPillar__vmt0(void *Block, char a2)
{
  sub_537830();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537830 sub_537830
// ------------------------------------------------------------
// CNCystalPillar 析构基座

int /*thiscall*/ sub_537830(uint32_t *this)
{
  *this = &vftbl_CNCystalPillar;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537840 sub_537840
// ------------------------------------------------------------
// CNEyeofObserver 构造器（观察者之眼，巨型雕像炮台）

uint32_t */*thiscall*/ sub_537840(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNEyeofObserver;
  sub_629AB0(this);
  return this;
}



// ------------------------------------------------------------
// 0x5378A0 CNEyeofObserver__vmt0
// ------------------------------------------------------------
// CNEyeofObserver__vmt0 删除析构壳

void */*thiscall*/ CNEyeofObserver__vmt0(void *Block, char a2)
{
  sub_5378D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5378D0 sub_5378D0
// ------------------------------------------------------------
// CNEyeofObserver 析构基座

int /*thiscall*/ sub_5378D0(void **this)
{
  *this = &vftbl_CNEyeofObserver;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537920 sub_537920
// ------------------------------------------------------------
// CNActiveObserver 构造器（活动观察者，可动炮台）

uint32_t */*thiscall*/ sub_537920(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNActiveObserver;
  sub_629BF0(this);
  return this;
}



// ------------------------------------------------------------
// 0x537980 CNActiveObserver__vmt0
// ------------------------------------------------------------
// CNActiveObserver__vmt0 删除析构壳

void */*thiscall*/ CNActiveObserver__vmt0(void *Block, char a2)
{
  sub_5379B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5379B0 sub_5379B0
// ------------------------------------------------------------
// CNActiveObserver 析构基座

int /*thiscall*/ sub_5379B0(void **this)
{
  *this = &vftbl_CNActiveObserver;
  sub_629C40();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537A00 sub_537A00
// ------------------------------------------------------------
// CNLightBulb 构造器（灯泡破坏物）

uint32_t */*thiscall*/ sub_537A00(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNLightBulb;
  sub_62A520(this);
  return this;
}



// ------------------------------------------------------------
// 0x537A60 CNLightBulb__vmt0
// ------------------------------------------------------------
// CNLightBulb__vmt0 删除析构壳

void */*thiscall*/ CNLightBulb__vmt0(void *Block, char a2)
{
  sub_537A90();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537A90 sub_537A90
// ------------------------------------------------------------
// CNLightBulb 析构基座

int /*thiscall*/ sub_537A90(void **this)
{
  *this = &vftbl_CNLightBulb;
  sub_60C870();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537AE0 sub_537AE0
// ------------------------------------------------------------
// CNWaterDrop 构造器（水滴机关）

uint32_t */*thiscall*/ sub_537AE0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNWaterDrop;
  sub_62A5B0(this);
  return this;
}



// ------------------------------------------------------------
// 0x537B40 CNWaterDrop__vmt0
// ------------------------------------------------------------
// CNWaterDrop__vmt0 删除析构壳

void */*thiscall*/ CNWaterDrop__vmt0(void *Block, char a2)
{
  sub_537B70();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537B70 sub_537B70
// ------------------------------------------------------------
// CNWaterDrop 析构基座

int /*thiscall*/ sub_537B70(void **this)
{
  *this = &vftbl_CNWaterDrop;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537BC0 sub_537BC0
// ------------------------------------------------------------
// ★ CNFreezingLuna 构造器（冰冻露娜，冰属性地面）【资源实证】：vmt2F4 附属 +
// sub_4C3640("Particle/steam.ptl")（蒸汽粒子发射器）→ +282 存储

uint32_t */*thiscall*/ sub_537BC0(uint32_t *this, int a2, void *Block)
{
  uint32_t *v4; // ecx

  sub_52ED60(a2, Block);
  *this = &vftbl_CNFreezingLuna;
  *(this + 276) = 0;
  *(this + 277) = 0;
  *(this + 278) = 0;
  CNFreezingLuna__vmt2F4(Block);
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      v4 = this + 91;
    else
      v4 = (uint32_t *)*(this + 91);
    *(this + 282) = sub_4C3640(v4, "Particle/steam.ptl", this);
  }
  else
  {
    *(this + 282) = 0;
  }
  return this;
}



// ------------------------------------------------------------
// 0x537C80 CNFreezingLuna__vmt0
// ------------------------------------------------------------
// CNFreezingLuna__vmt0 删除析构壳

void */*thiscall*/ CNFreezingLuna__vmt0(void *Block, char a2)
{
  sub_537CB0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537CB0 sub_537CB0
// ------------------------------------------------------------
// CNFreezingLuna 析构基座：sub_62A6B0 + 释放 +276

int /*thiscall*/ sub_537CB0(void **this)
{
  *this = &vftbl_CNFreezingLuna;
  sub_62A6B0();
  if ( *(this + 276) != nullptr )
    j__free(*(this + 276));
  *(this + 276) = nullptr;
  *(this + 277) = nullptr;
  *(this + 278) = nullptr;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537D30 sub_537D30
// ------------------------------------------------------------
// CNTreeCross 构造器（十字树/路标）

uint32_t */*thiscall*/ sub_537D30(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNTreeCross;
  sub_62A880(this);
  return this;
}



// ------------------------------------------------------------
// 0x537D90 CNTreeCross__vmt0
// ------------------------------------------------------------
// CNTreeCross__vmt0 删除析构壳

void */*thiscall*/ CNTreeCross__vmt0(void *Block, char a2)
{
  sub_537DC0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537DC0 sub_537DC0
// ------------------------------------------------------------
// CNTreeCross 析构基座

int /*thiscall*/ sub_537DC0(void **this)
{
  *this = &vftbl_CNTreeCross;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537E10 sub_537E10
// ------------------------------------------------------------
// CNSkeletonPile 构造器（骸骨堆破坏物）

uint32_t */*thiscall*/ sub_537E10(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNSkeletonPile;
  CNSkeletonPile__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x537E70 CNSkeletonPile__vmt0
// ------------------------------------------------------------
// CNSkeletonPile__vmt0 删除析构壳

void */*thiscall*/ CNSkeletonPile__vmt0(void *Block, char a2)
{
  sub_537EA0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537EA0 sub_537EA0
// ------------------------------------------------------------
// CNSkeletonPile 析构基座

int /*thiscall*/ sub_537EA0(uint32_t *this)
{
  *this = &vftbl_CNSkeletonPile;
  sub_60A950();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537EF0 sub_537EF0
// ------------------------------------------------------------
// CNSpiderSpawn 构造器（蜘蛛卵/蜘蛛巢）

uint32_t */*thiscall*/ sub_537EF0(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNSpiderSpawn;
  CNSpiderSpawn__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x537F50 CNSpiderSpawn__vmt0
// ------------------------------------------------------------
// CNSpiderSpawn__vmt0 删除析构壳

void */*thiscall*/ CNSpiderSpawn__vmt0(void *Block, char a2)
{
  sub_537F80();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x537F80 sub_537F80
// ------------------------------------------------------------
// CNSpiderSpawn 析构基座

int /*thiscall*/ sub_537F80(uint32_t *this)
{
  *this = &vftbl_CNSpiderSpawn;
  sub_60A950();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537FD0 sub_537FD0
// ------------------------------------------------------------
// CN2StoryBox 构造器（双层箱破坏物）

uint32_t */*thiscall*/ sub_537FD0(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CN2StoryBox;
  CN2StoryBox__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x538030 CN2StoryBox__vmt0
// ------------------------------------------------------------
// CN2StoryBox__vmt0 删除析构壳

void */*thiscall*/ CN2StoryBox__vmt0(void *Block, char a2)
{
  sub_538060();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538060 sub_538060
// ------------------------------------------------------------
// CN2StoryBox 析构基座

int /*thiscall*/ sub_538060(uint32_t *this)
{
  *this = &vftbl_CN2StoryBox;
  nullsub_3();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x5380B0 sub_5380B0
// ------------------------------------------------------------
// CNGrenselosBunker 构造器（格伦塞洛斯碉堡）：+280 清零

uint32_t */*thiscall*/ sub_5380B0(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNGrenselosBunker;
  *(this + 280) = 0;
  *(this + 281) = 0;
  *(this + 282) = 0;
  CNGrenselosBunker__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x538120 CNGrenselosBunker__vmt0
// ------------------------------------------------------------
// CNGrenselosBunker__vmt0 删除析构壳

void */*thiscall*/ CNGrenselosBunker__vmt0(void *Block, char a2)
{
  sub_538150();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538150 sub_538150
// ------------------------------------------------------------
// CNGrenselosBunker 析构基座：+536750 卸状态 + 释放 +1120

int /*thiscall*/ sub_538150(int this)
{
  *(uint32_t *)this = &vftbl_CNGrenselosBunker;
  sub_536750((uint32_t *)this);
  if ( *(uint32_t *)(this + 1120) != 0 )
    j__free(*(void **)(this + 1120));
  *(uint32_t *)(this + 1120) = 0;
  *(uint32_t *)(this + 1124) = 0;
  *(uint32_t *)(this + 1128) = 0;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x5381D0 sub_5381D0
// ------------------------------------------------------------
// CNQuestCage 构造器（任务笼）：+1100 演出未播位、+276 背景板槽清零

uint8_t */*thiscall*/ sub_5381D0(uint8_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *(this + 1100) = 0;
  *((uint32_t *)this + 276) = 0;
  *(uint32_t *)this = &vftbl_CNQuestCage;
  return this;
}



// ------------------------------------------------------------
// 0x538200 CNQuestCage__vmt12C
// ------------------------------------------------------------
// CNQuestCage__vmt12C 周期 tick：自身+169==1 时扫容器内对象（条件码 529/34 位检查，P25）
// → 全部就绪则 vt+604(1) 开笼；自身为事件源时对条件 34 对象 sub_50EF20(30000) 延时 + 背景板 vt+84(0)

int /*thiscall*/ CNQuestCage__vmt12C(uint32_t *this, uint32_t *a2)
{
  signed int i; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // edx
  uint32_t *v9; // eax
  int v10; // eax
  uint32_t *v11; // eax
  int v12; // eax
  int v13; // ebx
  signed int j; // ebx
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  uint32_t *v19; // eax
  int v20; // eax
  uint32_t *v21; // eax
  int v22; // edi
  int v23; // eax
  int v25; // [esp-Ch] [ebp-18h]
  unsigned int v26; // [esp+0h] [ebp-Ch]

  if ( *(this + 169) == 1 )
  {
    for ( i = 0; ; ++i )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);
      v5 = *(uint32_t *)(v4 + 8);
      v6 = v4 + 4;
      v7 = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;
      v8 = *this;
      if ( i >= v7 )
        break;
      v9 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, signed int))(v8 + 80))(this, i);
      v10 = sub_4259D0(v9, v26);
      v26 = 529;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 40))(v10) != 0 )
      {
        v11 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);
        v12 = sub_4259D0(v11, i);
        v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 376))(v12);
        if ( v13 != (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) )
          goto LABEL_11;
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v8 + 604))(this, 1);
  }
LABEL_11:
  if ( a2 == this )
  {
    for ( j = 0; ; ++j )
    {
      v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);
      v16 = *(uint32_t *)(v15 + 8);
      v17 = v15 + 4;
      v18 = v16 != 0 ? (*(uint32_t *)(v17 + 8) - v16) >> 2 : 0;
      if ( j >= v18 )
        break;
      v19 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, signed int))(*this + 80))(this, j);
      v20 = sub_4259D0(v19, v26);
      v26 = 34;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v20 + 40))(v20) != 0 )
      {
        v21 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 80))(this);
        v22 = sub_4259D0(v21, j);
        v25 = sub_41ACF0(*(this + 178) + 24);
        v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v22 + 64))(v22);
        sub_50EF20(v23, v25, 0, 30000);
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 276) + 84))(*(this + 276), 0);
  }
  return CNMapObject__vmt12C(a2);
}



// ------------------------------------------------------------
// 0x538330 CNQuestCage__vmt0
// ------------------------------------------------------------
// CNQuestCage__vmt0 删除析构壳

void */*thiscall*/ CNQuestCage__vmt0(void *Block, char a2)
{
  sub_538360();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538360 sub_538360
// ------------------------------------------------------------
// CNQuestCage 析构基座：背景板 vt+84(0) → sub_52EE30

int /*thiscall*/ sub_538360(uint32_t *this)
{
  int v2; // ecx

  *this = &vftbl_CNQuestCage;
  v2 = *(this + 276);
  if ( v2 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v2 + 84))(v2, 0);
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x5383C0 sub_5383C0
// ------------------------------------------------------------
// CNFairy 构造器（地精精灵基类，吃豆式增益精灵）：+1108 CNTimer、+1112 计时位、+1120 使能

uint8_t */*thiscall*/ sub_5383C0(uint8_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *(uint32_t *)this = &vftbl_CNFairy;
  *(this + 1112) = 0;
  *((uint32_t *)this + 277) = &vftbl_nengine__CNTimer;
  *((uint32_t *)this + 279) = 0;
  *(this + 1120) = 1;
  *(this + 1122) = 0;
  *(this + 1121) = 0;
  *((uint32_t *)this + 283) = 0;
  *((uint32_t *)this + 282) = 0;
  *((uint32_t *)this + 281) = 0;
  sub_60AA00(this);
  sub_62C5F0(a2);
  return this;
}



// ------------------------------------------------------------
// 0x538460 sub_538460
// ------------------------------------------------------------
// CNFairy 析构基座：sub_60A950 → +277 退 IObject

int /*thiscall*/ sub_538460(uint32_t *this)
{
  *this = &vftbl_CNFairy;
  sub_60A950();
  *(this + 277) = &vftbl_nengine__IObject;
  *((uint8_t *)this + 1112) = 0;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x5384C0 CNFairy__vmt0
// ------------------------------------------------------------
// CNFairy__vmt0 删除析构壳

uint32_t */*thiscall*/ CNFairy__vmt0(uint32_t *Block, char a2)
{
  sub_538460(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5384F0 sub_5384F0
// ------------------------------------------------------------
// CNHPFairy 构造器（HP 精灵）

uint8_t */*thiscall*/ sub_5384F0(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNHPFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538520 CNHPFairy__vmt0
// ------------------------------------------------------------
// CNHPFairy__vmt0 删除析构壳

void */*thiscall*/ CNHPFairy__vmt0(void *Block, char a2)
{
  sub_538550();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538550 sub_538550
// ------------------------------------------------------------
// CNHPFairy 析构基座

int /*thiscall*/ sub_538550(uint32_t *this)
{
  *this = &vftbl_CNHPFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x5385A0 sub_5385A0
// ------------------------------------------------------------
// CNMPFairy 构造器（MP 精灵）

uint8_t */*thiscall*/ sub_5385A0(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNMPFairy;
  return this;
}



// ------------------------------------------------------------
// 0x5385D0 CNMPFairy__vmt0
// ------------------------------------------------------------
// CNMPFairy__vmt0 删除析构壳

void */*thiscall*/ CNMPFairy__vmt0(void *Block, char a2)
{
  sub_538600();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538600 sub_538600
// ------------------------------------------------------------
// CNMPFairy 析构基座

int /*thiscall*/ sub_538600(uint32_t *this)
{
  *this = &vftbl_CNMPFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x538650 sub_538650
// ------------------------------------------------------------
// CNHPMPFairy 构造器（HP/MP 双回复精灵）

uint8_t */*thiscall*/ sub_538650(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNHPMPFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538680 CNHPMPFairy__vmt0
// ------------------------------------------------------------
// CNHPMPFairy__vmt0 删除析构壳

void */*thiscall*/ CNHPMPFairy__vmt0(void *Block, char a2)
{
  sub_5386B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5386B0 sub_5386B0
// ------------------------------------------------------------
// CNHPMPFairy 析构基座

int /*thiscall*/ sub_5386B0(uint32_t *this)
{
  *this = &vftbl_CNHPMPFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x538700 sub_538700
// ------------------------------------------------------------
// CNSuperArmorFairy 构造器（霸体精灵）

uint8_t */*thiscall*/ sub_538700(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNSuperArmorFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538730 CNSuperArmorFairy__vmt0
// ------------------------------------------------------------
// CNSuperArmorFairy__vmt0 删除析构壳

void */*thiscall*/ CNSuperArmorFairy__vmt0(void *Block, char a2)
{
  sub_538760();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538760 sub_538760
// ------------------------------------------------------------
// CNSuperArmorFairy 析构基座

int /*thiscall*/ sub_538760(uint32_t *this)
{
  *this = &vftbl_CNSuperArmorFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x5387B0 sub_5387B0
// ------------------------------------------------------------
// CNHasteFairy 构造器（加速精灵）

uint8_t */*thiscall*/ sub_5387B0(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNHasteFairy;
  return this;
}



// ------------------------------------------------------------
// 0x5387E0 CNHasteFairy__vmt0
// ------------------------------------------------------------
// CNHasteFairy__vmt0 删除析构壳

void */*thiscall*/ CNHasteFairy__vmt0(void *Block, char a2)
{
  sub_538810();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538810 sub_538810
// ------------------------------------------------------------
// CNHasteFairy 析构基座

int /*thiscall*/ sub_538810(uint32_t *this)
{
  *this = &vftbl_CNHasteFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x538860 sub_538860
// ------------------------------------------------------------
// CNBlessFairy 构造器（祝福精灵）

uint8_t */*thiscall*/ sub_538860(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNBlessFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538890 CNBlessFairy__vmt0
// ------------------------------------------------------------
// CNBlessFairy__vmt0 删除析构壳

void */*thiscall*/ CNBlessFairy__vmt0(void *Block, char a2)
{
  sub_5388C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5388C0 sub_5388C0
// ------------------------------------------------------------
// CNBlessFairy 析构基座

int /*thiscall*/ sub_5388C0(uint32_t *this)
{
  *this = &vftbl_CNBlessFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x538910 sub_538910
// ------------------------------------------------------------
// CNInvinsibleFairy 构造器（无敌精灵，RTTI 原名拼写 Invinsible）

uint8_t */*thiscall*/ sub_538910(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNInvinsibleFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538940 CNInvinsibleFairy__vmt0
// ------------------------------------------------------------
// CNInvinsibleFairy__vmt0 删除析构壳

void */*thiscall*/ CNInvinsibleFairy__vmt0(void *Block, char a2)
{
  sub_538970();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538970 sub_538970
// ------------------------------------------------------------
// CNInvinsibleFairy 析构基座

int /*thiscall*/ sub_538970(uint32_t *this)
{
  *this = &vftbl_CNInvinsibleFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x5389C0 sub_5389C0
// ------------------------------------------------------------
// CNFairyFactory 构造器（精灵工厂，按表刷精灵）

uint32_t */*thiscall*/ sub_5389C0(uint32_t *this, int a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNFairyFactory;
  sub_5FF8E0(this);
  sub_62D0B0(a2);
  return this;
}



// ------------------------------------------------------------
// 0x538A20 CNFairyFactory__vmt0
// ------------------------------------------------------------
// CNFairyFactory__vmt0 删除析构壳

void */*thiscall*/ CNFairyFactory__vmt0(void *Block, char a2)
{
  sub_538A50();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538A50 sub_538A50
// ------------------------------------------------------------
// CNFairyFactory 析构基座

int /*thiscall*/ sub_538A50(void **this)
{
  *this = &vftbl_CNFairyFactory;
  sub_5FF980();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x538AA0 sub_538AA0
// ------------------------------------------------------------
// CNActionTree 构造器（剧情互动树，CNMapObject 系）

uint32_t */*thiscall*/ sub_538AA0(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNActionTree;
  sub_60AA00(this);
  CNMapObject__vmt2E4(this);
  nullsub_3();
  return this;
}



// ------------------------------------------------------------
// 0x538B10 CNActionTree__vmt0
// ------------------------------------------------------------
// CNActionTree__vmt0 删除析构壳

void */*thiscall*/ CNActionTree__vmt0(void *Block, char a2)
{
  sub_538B40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538B40 sub_538B40
// ------------------------------------------------------------
// CNActionTree 析构基座

int /*thiscall*/ sub_538B40(uint32_t *this)
{
  *this = &vftbl_CNActionTree;
  sub_60A950();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x538B90 sub_538B90
// ------------------------------------------------------------
// CNSoundFloor 构造器（音效地板/踩踏发声板）：+1100 szPassword 字符串槽（音名?）、+1096 使能

void */*thiscall*/ sub_538B90(void *this, int a2, int a3, int a4)
{
  sub_52ED60(a2, a3);
  *(uint32_t *)this = &vftbl_CNSoundFloor;
  *((uint32_t *)this + 275) = 0;
  sub_41BFE0((void **)this + 275, szPassword);
  *((uint8_t *)this + 1096) = 1;
  sub_62D220(a3, a4);
  return this;
}



// ------------------------------------------------------------
// 0x538C10 CNSoundFloor__vmt0
// ------------------------------------------------------------
// CNSoundFloor__vmt0 删除析构壳

void */*thiscall*/ CNSoundFloor__vmt0(void *Block, char a2)
{
  sub_538C40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538C40 sub_538C40
// ------------------------------------------------------------
// CNSoundFloor 析构基座：释放 +1100

int /*thiscall*/ sub_538C40(void **this)
{
  *this = &vftbl_CNSoundFloor;
  sub_41B010(this + 275);
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x538CA0 sub_538CA0
// ------------------------------------------------------------
// CNFountain 构造器（喷泉装饰）

uint32_t */*thiscall*/ sub_538CA0(uint32_t *this, int a2, int a3)
{
  sub_52ED60(a2, a3);
  *this = &vftbl_CNFountain;
  sub_60AA00(this);
  CNMapObject__vmt2E4(this);
  CNFountain__vmt2E4(this);
  return this;
}



// ------------------------------------------------------------
// 0x538D10 CNFountain__vmt0
// ------------------------------------------------------------
// CNFountain__vmt0 删除析构壳

void */*thiscall*/ CNFountain__vmt0(void *Block, char a2)
{
  sub_538D40();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538D40 sub_538D40
// ------------------------------------------------------------
// CNFountain 析构基座

int /*thiscall*/ sub_538D40(uint32_t *this)
{
  *this = &vftbl_CNFountain;
  sub_60A950();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// ============
// 【分区 2】附魔光圈附件族（0x538D90-0x539140）
// CNCircleAppendage*：光环(Aura)附件按槽位生成效果对象。vmt2C4 = 产出效果对象
// （ENCHANTWEAPON→sub_4DF1B0 武器附魔 / CHANGE_WEAPON_ELEMENT→CNChangeWeaponElement /
//   CHANGESTATE→sub_4B3DF0 CNChangeStatus / DISENCHANT→固定 600），vmt2C8/vmt2BC 供参数回读。
// ============

// 0x538D90 sub_538D90
// ------------------------------------------------------------
// CNCircleAppendageENCHANTWEAPON 构造器（武器附魔光圈附件）：+248 清零

uint32_t */*thiscall*/ sub_538D90(uint32_t *this, int a2, int a3, int a4)
{
  sub_530710(a2, a3, a4);
  *this = &vftbl_CNCircleAppendageENCHANTWEAPON;
  *(this + 248) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x538DC0 CNCircleAppendageENCHANTWEAPON__vmt2C8
// ------------------------------------------------------------
// ENCHANTWEAPON__vmt2C8 参数回读：*a2 = vt+120()（附魔值）、*a3 = 0

int /*thiscall*/ CNCircleAppendageENCHANTWEAPON__vmt2C8(void *this, int *a2, uint32_t *a3)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
  *a2 = result;
  *a3 = 0;
  return result;
}



// ------------------------------------------------------------
// 0x538DE0 CNCircleAppendageENCHANTWEAPON__vmt2C4
// ------------------------------------------------------------
// ★ ENCHANTWEAPON__vmt2C4 产出效果对象：operator new(0x84) → sub_4DF1B0(+246,+247,0,-1)
// （CNChangeStatus 系武器附魔，P37 [DAMAGE TYPE] 无关——此为属性附魔 PO）

int /*thiscall*/ CNCircleAppendageENCHANTWEAPON__vmt2C4(uint32_t *this, uint32_t *a2, uint32_t *Block)
{
  int result; // eax

  *Block = *(this + 248);
  if ( operator new(0x84u) != nullptr )
  {
    result = sub_4DF1B0(*(this + 246), *(this + 247), 0, -1);
    *a2 = result;
  }
  else
  {
    *a2 = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x538E70 sub_538E70
// ------------------------------------------------------------
// ENCHANTWEAPON 析构基座 → sub_530780

int /*thiscall*/ sub_538E70(uint32_t *this)
{
  *this = &vftbl_CNCircleAppendageENCHANTWEAPON;
  return sub_530780();
}



// ------------------------------------------------------------
// 0x538E80 CNCircleAppendageENCHANTWEAPON__vmt0
// ------------------------------------------------------------
// CNCircleAppendageENCHANTWEAPON__vmt0 删除析构壳

uint32_t */*thiscall*/ CNCircleAppendageENCHANTWEAPON__vmt0(uint32_t *Block, char a2)
{
  sub_538E70(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x538EB0 sub_538EB0
// ------------------------------------------------------------
// CNCircleAppendageCHANGE_WEAPON_ELEMENT 构造器（武器属性变更附件）

uint32_t */*thiscall*/ sub_538EB0(uint32_t *this, int a2, int a3, int a4)
{
  sub_530710(a2, a3, a4);
  *(this + 248) = 0;
  *this = &vftbl_CNCircleAppendageCHANGE_WEAPON_ELEMENT;
  return this;
}



// ------------------------------------------------------------
// 0x538EE0 CNCircleAppendageCHANGE_WEAPON_ELEMENT__vmt2C4
// ------------------------------------------------------------
// ★ CHANGE_WEAPON_ELEMENT__vmt2C4：new(0x84) → sub_4DF1B0(+246,+247,3,-1)
// → vftbl_CNChangeWeaponElement（0x51 区属性变更 PO，po_effects.cpp 分区 1）

int /*thiscall*/ CNCircleAppendageCHANGE_WEAPON_ELEMENT__vmt2C4(uint32_t *this, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v4; // esi
  int result; // eax

  *a3 = *(this + 248);
  v4 = operator new(0x84u);
  result = 0;
  if ( v4 != nullptr )
  {
    result = sub_4DF1B0(*(this + 246), *(this + 247), 3, -1);
    *v4 = &vftbl_CNChangeWeaponElement;
    *a2 = v4;
  }
  else
  {
    *a2 = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x538F70 sub_538F70
// ------------------------------------------------------------
// CNCircleAppendageCHANGESTATE 构造器（状态变更附件）：+1001 清零

uint32_t */*thiscall*/ sub_538F70(uint32_t *this, int a2, int a3, int a4)
{
  sub_530710(a2, a3, a4);
  *this = &vftbl_CNCircleAppendageCHANGESTATE;
  *(uint32_t *)((char *)this + 1001) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x538FA0 CNCircleAppendageENCHANTWEAPON__vmt2BC
// ------------------------------------------------------------
// ENCHANTWEAPON__vmt2BC 参数写入：qmemcpy 到 +984（状态参数包 8B 载入）

unsigned int /*thiscall*/ CNCircleAppendageENCHANTWEAPON__vmt2BC(int this, const void *a2, unsigned int a3)
{
  qmemcpy((void *)(this + 984), a2, a3);
  return a3;
}



// ------------------------------------------------------------
// 0x538FD0 CNCircleAppendageCHANGESTATE__vmt2C4
// ------------------------------------------------------------
// ★ CHANGESTATE__vmt2C4：new(0x7C) → sub_4B3DF0(+984 状态类型,+988,+989,+993,+997)
// （CNChangeStatus 0x7C 构造，参数块与 0x5101B0 同构）

uint32_t */*thiscall*/ CNCircleAppendageCHANGESTATE__vmt2C4(int this, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v4; // eax
  uint32_t *result; // eax

  *a3 = *(uint32_t *)(this + 1001);
  v4 = operator new(0x7Cu);
  if ( v4 != nullptr )
  {
    result = sub_4B3DF0(
               v4,
               *(uint32_t *)(this + 984),
               *(uint8_t *)(this + 988),
               *(uint32_t *)(this + 989),
               *(uint32_t *)(this + 993),
               *(uint32_t *)(this + 997));
    *a2 = result;
  }
  else
  {
    *a2 = 0;
    return nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x539070 CNCircleAppendageCHANGESTATE__vmt0
// ------------------------------------------------------------
// CNCircleAppendageCHANGESTATE__vmt0 删除析构壳

void */*thiscall*/ CNCircleAppendageCHANGESTATE__vmt0(void *Block, char a2)
{
  sub_5390A0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5390A0 sub_5390A0
// ------------------------------------------------------------
// CHANGESTATE 析构基座

int /*thiscall*/ sub_5390A0(uint32_t *this)
{
  *this = &vftbl_CNCircleAppendageCHANGESTATE;
  return sub_530780();
}



// ------------------------------------------------------------
// 0x5390B0 sub_5390B0
// ------------------------------------------------------------
// CNCircleAppendageDISENCHANT 构造器（解除附魔附件）

uint32_t */*thiscall*/ sub_5390B0(uint32_t *this, int a2, int a3, int a4)
{
  sub_530710(a2, a3, a4);
  *this = &vftbl_CNCircleAppendageDISENCHANT;
  return this;
}



// ------------------------------------------------------------
// 0x5390E0 CNCircleAppendageDISENCHANT__vmt2C8
// ------------------------------------------------------------
// ★ DISENCHANT__vmt2C8 参数回读：固定 *a1=600、*a2=1（解除附魔硬编码参数）

uint32_t */*stdcall*/ CNCircleAppendageDISENCHANT__vmt2C8(uint32_t *a1, uint32_t *a2)
{
  *a1 = 600;
  *a2 = 1;
  return a1;
}



// ------------------------------------------------------------
// 0x539100 CNCircleAppendageDISENCHANT__vmt0
// ------------------------------------------------------------
// CNCircleAppendageDISENCHANT__vmt0 删除析构壳

void */*thiscall*/ CNCircleAppendageDISENCHANT__vmt0(void *Block, char a2)
{
  sub_539130();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x539130 sub_539130
// ------------------------------------------------------------
// DISENCHANT 析构基座

int /*thiscall*/ sub_539130(uint32_t *this)
{
  *this = &vftbl_CNCircleAppendageDISENCHANT;
  return sub_530780();
}



// ------------------------------------------------------------
// ============
// 【分区 3】杂项机关 + 破坏物演出 PO（0x539140-0x53A210）
// 重力反转/仓储鸟/宝箱/罐子（vmt2E0 破坏演出）/毒虫/荆棘根（音效 TAG 实证）/
// 通用火球/池化 PO 基类/阳光爆发（五层动画叠放）/齐柏林飞艇弹（四张烟雾·爆裂动画）。
// 破坏演出统一走池化四件套（见文件头）+ 演播层 2。
// ============

// 0x539140 sub_539140
// ------------------------------------------------------------
// CNGravityChangeBack 构造器（重力恢复区域，与 GravityChanger 配对）

uint32_t */*thiscall*/ sub_539140(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNGravityChangeBack;
  sub_62D490(this);
  sub_62D550(this);
  return this;
}



// ------------------------------------------------------------
// 0x5391A0 CNGravityChangeBack__vmt0
// ------------------------------------------------------------
// CNGravityChangeBack__vmt0 删除析构壳

void */*thiscall*/ CNGravityChangeBack__vmt0(void *Block, char a2)
{
  sub_5391D0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5391D0 sub_5391D0
// ------------------------------------------------------------
// CNGravityChangeBack 析构基座

int /*thiscall*/ sub_5391D0(void **this)
{
  *this = &vftbl_CNGravityChangeBack;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x539220 sub_539220
// ------------------------------------------------------------
// CNStorageBird 构造器（仓储鸟，搬运/储物机关）

uint32_t */*thiscall*/ sub_539220(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNStorageBird;
  sub_601A50(this);
  sub_601B70(a3);
  return this;
}



// ------------------------------------------------------------
// 0x539280 CNStorageBird__vmt0
// ------------------------------------------------------------
// CNStorageBird__vmt0 删除析构壳

void */*thiscall*/ CNStorageBird__vmt0(void *Block, char a2)
{
  sub_5392B0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5392B0 sub_5392B0
// ------------------------------------------------------------
// CNStorageBird 析构基座

int /*thiscall*/ sub_5392B0(void **this)
{
  *this = &vftbl_CNStorageBird;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x539300 sub_539300
// ------------------------------------------------------------
// CNFallingStorage 构造器（坠落仓储）

uint32_t */*thiscall*/ sub_539300(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNFallingStorage;
  sub_616D80(this);
  sub_601BE0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x539360 CNFallingStorage__vmt0
// ------------------------------------------------------------
// CNFallingStorage__vmt0 删除析构壳

void */*thiscall*/ CNFallingStorage__vmt0(void *Block, char a2)
{
  sub_539390();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x539390 sub_539390
// ------------------------------------------------------------
// CNFallingStorage 析构基座

int /*thiscall*/ sub_539390(void **this)
{
  *this = &vftbl_CNFallingStorage;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5393E0 sub_5393E0
// ------------------------------------------------------------
// CNStorageSub 构造器（仓储子体）

uint32_t */*thiscall*/ sub_5393E0(uint32_t *this, int a2, int a3)
{
  sub_5348A0(a2, a3);
  *this = &vftbl_CNStorageSub;
  sub_601B60(a3);
  return this;
}



// ------------------------------------------------------------
// 0x539440 CNStorageSub__vmt0
// ------------------------------------------------------------
// CNStorageSub__vmt0 删除析构壳

void */*thiscall*/ CNStorageSub__vmt0(void *Block, char a2)
{
  sub_539470();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x539470 sub_539470
// ------------------------------------------------------------
// CNStorageSub 析构基座 → sub_534900

int /*thiscall*/ sub_539470(uint32_t *this)
{
  *this = &vftbl_CNStorageSub;
  return sub_534900();
}



// ------------------------------------------------------------
// 0x539480 sub_539480
// ------------------------------------------------------------
// CNEPLPCampFire 构造器（EPLP 营火，回复点装饰）

uint32_t */*thiscall*/ sub_539480(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNEPLPCampFire;
  sub_62D7C0(this);
  return this;
}



// ------------------------------------------------------------
// 0x5394E0 CNEPLPCampFire__vmt0
// ------------------------------------------------------------
// CNEPLPCampFire__vmt0 删除析构壳

void */*thiscall*/ CNEPLPCampFire__vmt0(void *Block, char a2)
{
  sub_539510();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x539510 sub_539510
// ------------------------------------------------------------
// CNEPLPCampFire 析构基座

int /*thiscall*/ sub_539510(void **this)
{
  *this = &vftbl_CNEPLPCampFire;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x539520 sub_539520
// ------------------------------------------------------------
// CNPoisonBug 构造器（毒虫机关）：+976 CNTimer、+988 使能、+992..1000 参数区

int /*thiscall*/ sub_539520(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &vftbl_CNPoisonBug;
  *(uint8_t *)(this + 980) = 0;
  *(uint32_t *)(this + 976) = &vftbl_nengine__CNTimer;
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 988) = 1;
  *(uint8_t *)(this + 990) = 0;
  *(uint8_t *)(this + 989) = 0;
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 996) = 0;
  *(uint32_t *)(this + 992) = 0;
  sub_62DAA0(this);
  sub_62DBA0(a3);
  return this;
}



// ------------------------------------------------------------
// 0x5395C0 CNPoisonBug__vmt0
// ------------------------------------------------------------
// CNPoisonBug__vmt0 删除析构壳

void */*thiscall*/ CNPoisonBug__vmt0(void *Block, char a2)
{
  sub_5395F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x5395F0 sub_5395F0
// ------------------------------------------------------------
// CNPoisonBug 析构基座：+976 退 IObject

int /*thiscall*/ sub_5395F0(int this)
{
  *(uint32_t *)this = &vftbl_CNPoisonBug;
  sub_60C870();
  *(uint32_t *)(this + 976) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 980) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x539650 sub_539650
// ------------------------------------------------------------
// CNAuxoRoot 构造器（荆棘根/藤蔓攻击体）

int /*thiscall*/ sub_539650(int this, char a2, int a3)
{
  sub_52EA60((uint32_t *)this, a2, a3);
  *(uint32_t *)this = &vftbl_CNAuxoRoot;
  *(uint8_t *)(this + 972) = 0;
  sub_5FF8E0(this);
  return this;
}



// ------------------------------------------------------------
// 0x5396B0 CNAuxoRoot__vmt14C
// ------------------------------------------------------------
// ★ CNAuxoRoot__vmt14C 周期 tick【音效 TAG 实证】：+972 未播 && 动画帧(+148)<=1
// → 播 "AUXO_ROOT_ATK"（P32 TAG）置已播；帧 >=2 → vt+84(0) 自杀

int /*thiscall*/ CNAuxoRoot__vmt14C(void *this)
{
  int result; // eax

  if ( *((uint8_t *)this + 972) == 0 && *(int *)(*((uint32_t *)this + 30) + 148) <= 1 )
  {
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "AUXO_ROOT_ATK",
      -1,
      0,
      0);
    *((uint8_t *)this + 972) = 1;
  }
  result = *((uint32_t *)this + 30);
  if ( *(int *)(result + 148) >= 2 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 84))(this, 0);
  return result;
}



// ------------------------------------------------------------
// 0x539700 CNAuxoRoot__vmt1F4
// ------------------------------------------------------------
// ★ CNAuxoRoot__vmt1F4 受击钩子【音效 TAG 实证】：a4==0 → 播 "TRAP_GRASS_HIT"
// → 委托 CNRDPassiveObject__vmt1F4

int /*thiscall*/ CNAuxoRoot__vmt1F4(void *this, int a2, int a3, int a4)
{
  if ( (uint8_t)a4 == 0 )
    (*(void (/*thiscall*/ **)(void *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TRAP_GRASS_HIT",
      -1,
      0,
      0);
  return CNRDPassiveObject__vmt1F4(a2, a3, a4);
}



// ------------------------------------------------------------
// 0x539740 CNAuxoRoot__vmt0
// ------------------------------------------------------------
// CNAuxoRoot__vmt0 删除析构壳

void */*thiscall*/ CNAuxoRoot__vmt0(void *Block, char a2)
{
  sub_539770();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x539770 sub_539770
// ------------------------------------------------------------
// CNAuxoRoot 析构基座：sub_5FF980 → sub_4E2040

int /*thiscall*/ sub_539770(void **this)
{
  *this = &vftbl_CNAuxoRoot;
  sub_5FF980();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5397C0 sub_5397C0
// ------------------------------------------------------------
// CNFireBallCommon 构造器（通用火球投射体）

uint32_t */*thiscall*/ sub_5397C0(uint32_t *this, char a2, int a3)
{
  sub_52EA60(this, a2, a3);
  *this = &vftbl_CNFireBallCommon;
  sub_62DC30(this);
  sub_62DD10(*(float *)&a3);
  return this;
}



// ------------------------------------------------------------
// 0x539820 CNFireBallCommon__vmt0
// ------------------------------------------------------------
// CNFireBallCommon__vmt0 删除析构壳

void */*thiscall*/ CNFireBallCommon__vmt0(void *Block, char a2)
{
  sub_539850();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x539850 sub_539850
// ------------------------------------------------------------
// CNFireBallCommon 析构基座

int /*thiscall*/ sub_539850(void **this)
{
  *this = &vftbl_CNFireBallCommon;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5398A0 CNRDPooledPassiveObject__vmt0
// ------------------------------------------------------------
// CNRDPooledPassiveObject__vmt0 删除析构壳：a2&1 → sub_657740(this,972) 归还池

void **/*thiscall*/ CNRDPooledPassiveObject__vmt0(void **this, char a2)
{
  sub_5398D0(this);
  if ( (a2 & 1) != 0 )
    sub_657740(this, 972);
  return this;
}



// ------------------------------------------------------------
// 0x5398E0 CNTreasureBox__vmt2E0
// ------------------------------------------------------------
// ★ CNTreasureBox__vmt2E0 破坏演出（宝箱）：池化四件套（P33）
// 动画名 = +364/+91 字符串 + sub_41ACF0(+178→+24)（图集 id）→ sub_431920 生成 →
// 入演播层 2 → 位置 = vt+128/124/120 自身坐标 → 委托 CNMapObject__vmt2E0

int /*thiscall*/ CNTreasureBox__vmt2E0(char *this, int a2)
{
  int v3; // edi
  int v4; // ebx
  const char *v5; // ebx
  const char *v6; // eax
  char *v7; // eax
  char *v8; // edi
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax

  v3 = sub_42FCB0(228);
  v4 = 0;
  if ( v3 != 0 )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      v5 = this + 364;
    else
      v5 = *((const char **)this + 91);
    v6 = (const char *)sub_41ACF0(*((uint32_t *)this + 178) + 24);
    v4 = sub_431920(v3, v5, v6, 1);
  }
  v7 = (char *)sub_44B6C0(284);
  v8 = v7;
  if ( v7 != nullptr )
  {
    sub_44E0D0(v7, v4, 1);
    *(uint32_t *)v8 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v8 = nullptr;
  }
  v9 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 80))(this);
  sub_45FE80(v9, (int)v8, 2, 0, (int)v8, (int)this, 0);
  v10 = *(uint32_t *)v8;
  v11 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
  v12 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, v11);
  v13 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, v12);
  (*(void (/*thiscall*/ **)(char *, int))(v10 + 112))(v8, v13);
  return CNMapObject__vmt2E0(a2);
}



// ------------------------------------------------------------
// 0x5399E0 CNUrn__vmt2E0
// ------------------------------------------------------------
// ★ CNUrn__vmt2E0 破坏演出（罐/瓮）：与宝箱同构，图集 id 取 +178→+8 → 委托 CNMapObject__vmt2E0

int /*thiscall*/ CNUrn__vmt2E0(char *this, int a2)
{
  int v3; // edi
  int v4; // ebx
  const char *v5; // ebx
  const char *v6; // eax
  char *v7; // eax
  char *v8; // edi
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int v13; // eax

  v3 = sub_42FCB0(228);
  v4 = 0;
  if ( v3 != 0 )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      v5 = this + 364;
    else
      v5 = *((const char **)this + 91);
    v6 = (const char *)sub_41ACF0(*((uint32_t *)this + 178) + 8);
    v4 = sub_431920(v3, v5, v6, 1);
  }
  v7 = (char *)sub_44B6C0(284);
  v8 = v7;
  if ( v7 != nullptr )
  {
    sub_44E0D0(v7, v4, 1);
    *(uint32_t *)v8 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v8 = nullptr;
  }
  v9 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 80))(this);
  sub_45FE80(v9, (int)v8, 2, 0, (int)v8, (int)this, 0);
  v10 = *(uint32_t *)v8;
  v11 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 128))(this);
  v12 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 124))(this, v11);
  v13 = (*(int (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 120))(this, v12);
  (*(void (/*thiscall*/ **)(char *, int))(v10 + 112))(v8, v13);
  return CNMapObject__vmt2E0(a2);
}



// ------------------------------------------------------------
// 0x539AE0 CNSunBurst__vmt14C
// ------------------------------------------------------------
// ★ CNSunBurst__vmt14C 周期 tick（阳光爆发，usercall ecx/ebx/edi）【资源实证】：
// 首次(+972==0) 循环 5 层 sprintf("Animation/SunBurstLayer%d.ani", 1..5) 池化动画 →
// 第 1/3 层建池化对象挂宿主(sub_45FE80 层 2 + vt+112 定位 + vt+148 镜像 + vt+60 挂接) + sub_4A06D0 高度
// → 存活时 RTDynamicCast 目标→CNMage && vt+840()==10 && vt+1288==1 && vt+1284==31 才保持，否则 vt+312(0) 关闭

char /*usercall*/ sub_539AE0@<al>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // edi
  int v5; // ebx
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  char *v10; // edi
  char *v11; // ecx
  int v12; // edi
  int v13; // edx
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // edi
  int v20; // eax
  int v21; // edi
  int v22; // eax
  char *v23; // edi
  char *v24; // ecx
  int v25; // edi
  int v26; // edx
  int *v27; // ecx
  int v28; // eax
  int v29; // edi
  int v30; // eax
  int v31; // edi
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // edi
  int v36; // eax
  int v37; // edi
  int v38; // eax
  uint8_t *v39; // eax
  uint8_t *v40; // edi
  char result; // al
  int v42; // [esp-Ch] [ebp-13Ch]
  int v45[4]; // [esp+4h] [ebp-12Ch]
  int v46; // [esp+14h] [ebp-11Ch]
  int v47; // [esp+18h] [ebp-118h]
  int v48; // [esp+1Ch] [ebp-114h]
  char Buffer[256]; // [esp+20h] [ebp-110h] BYREF
  int v50; // [esp+120h] [ebp-10h]
  int v51; // [esp+12Ch] [ebp-4h]

  v50 = dword_796E50;
  sub_600890();
  if ( a1[50] == 1 )
    (*(void (/*thiscall*/ **)(int *))(*a1 + 232))(a1);
  if ( *((uint8_t *)a1 + 972) == 0 )
  {
    v4 = 0;
    do
    {
      v47 = v4 + 1;
      sprintf(Buffer, "Animation/SunBurstLayer%d.ani", v4 + 1);
      v48 = sub_42FCB0(228);
      v5 = 0;
      v51 = 0;
      if ( v48 != 0 )
      {
        if ( (unsigned int)a1[96] < 0x10 )
          LOBYTE(v6) = (uint8_t)a1 + 108;
        else
          v6 = a1[91];
        v5 = sub_431920(v6, (char)Buffer, 1);
      }
      v7 = a1[30];
      v8 = *(uint32_t *)(v7 + 212);
      v51 = -1;
      v45[v4] = v5;
      if ( v8 != 0 )
        v9 = sub_4910A0(v8);
      else
        v9 = *(uint32_t *)(v7 + 32);
      sub_493A60(v5, v9);
      v4 = v47;
    }
    while ( v47 < 5 );
    v10 = (char *)sub_44B6C0(284);
    v48 = (int)v10;
    v51 = 1;
    if ( v10 != nullptr )
    {
      sub_44E0D0(v10, v45[0], 1);
      *(uint32_t *)v10 = &CNRDPooledObject::`vftable';
      v11 = v10;
    }
    else
    {
      v11 = nullptr;
    }
    v12 = v45[1];
    a1[244] = (int)v11;
    v13 = *(uint32_t *)v11;
    v51 = -1;
    (*(void (/*thiscall*/ **)(char *, int))(v13 + 100))(v11, v12);
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1[244] + 204))(
      a1[244],
      1,
      v12,
      0,
      0,
      0,
      0);
    v14 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 684))(a1, 1);
    sub_45FE80(a1[29], v12, 2, 0, a1[244], v14, a2);
    v15 = *(uint32_t *)a1[244];
    v16 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);
    v17 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 124))(a1, v16);
    v18 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 120))(a1, v17);
    (*(void (/*thiscall*/ **)(int, int))(v15 + 112))(a1[244], v18);
    v19 = *(uint32_t *)a1[244];
    v20 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);
    (*(void (/*thiscall*/ **)(int, int))(v19 + 148))(a1[244], v20);
    v21 = a1[244];
    v22 = (*(int (/*thiscall*/ **)(int *))(*a1 + 684))(a1);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 60))(v21, v22);
    sub_4A06D0(a3);
    v23 = (char *)sub_44B6C0(284);
    v48 = (int)v23;
    v51 = 2;
    if ( v23 != nullptr )
    {
      sub_44E0D0(v23, v45[2], 1);
      *(uint32_t *)v23 = &CNRDPooledObject::`vftable';
      v24 = v23;
    }
    else
    {
      v24 = nullptr;
    }
    v25 = v45[3];
    a1[245] = (int)v24;
    v26 = *(uint32_t *)v24;
    v51 = -1;
    (*(void (/*thiscall*/ **)(char *, int))(v26 + 100))(v24, v25);
    v27 = (int *)a1[245];
    v28 = *v27;
    v45[0] = 0;
    v42 = v25;
    (*(void (/*thiscall*/ **)(int *))(v28 + 204))(v27);
    v29 = v46;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1[245] + 100))(a1[245], v46);
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1[245] + 204))(
      a1[245],
      2,
      v29,
      0,
      0,
      0,
      0);
    v30 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*a1 + 684))(a1, 0);
    sub_45FE80(a1[29], v29, 2, 0, a1[245], v30, 1);
    v31 = *(uint32_t *)a1[245];
    v32 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);
    v33 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 124))(a1, v32);
    v34 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 120))(a1, v33);
    (*(void (/*thiscall*/ **)(int, int))(v31 + 112))(a1[245], v34);
    v35 = *(uint32_t *)a1[245];
    v36 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);
    (*(void (/*thiscall*/ **)(int, int))(v35 + 148))(a1[245], v36);
    v37 = a1[245];
    v38 = (*(int (/*thiscall*/ **)(int *))(*a1 + 684))(a1);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v37 + 60))(v37, v38);
    sub_4A06D0(v42);
    *((uint8_t *)a1 + 972) = 1;
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0 )
  {
    v39 = __RTDynamicCast(
            (uint32_t *)a1[173],
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &CNMage `RTTI Type Descriptor',
            0);
    v40 = v39;
    if ( v39 == nullptr
      || (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v39 + 840))(v39) != 10
      || (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v40 + 1288))(v40) != 1
      || (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v40 + 1284))(v40) != 31 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 312))(a1, 0);
    }
  }
  result = *(uint8_t *)(a1[30] + 170);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*a1 + 312))(a1, 0);
  return result;
}


// ------------------------------------------------------------
// 0x539E90 CNZepplinBullet__vmt12C
// ------------------------------------------------------------
// ★ CNZepplinBullet__vmt12C 周期 tick（齐柏林飞艇弹，self==a2 分支）【资源实证】：
// 落点 vt+128()>0（空中）→ 按 vt+152 朝向取 BulletSmokeR/L.ani；落地 → BulletBlast.ani 爆裂 +
// BulletSmoke.ani 烟雾 → 全部池化四件套入演播层 2 + vt+112/vt+148 定位镜像

int /*thiscall*/ sub_539E90(int *this, int *a2)
{
  int result; // eax
  int v4; // ebx
  char *v5; // eax
  char *v6; // edi
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  char *v13; // eax
  char *v14; // edi
  int v15; // ebx
  int v16; // eax
  int v17; // ebx
  int v18; // eax
  int v19; // eax
  bool v20; // zf
  const char *v21; // eax
  int v22; // ebx
  char *v23; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int v27; // eax

  result = sub_600790(a2);
  if ( a2 == this )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) > 0 )
    {
      if ( sub_42FCB0(228) != 0 )
      {
        v20 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) == 1;
        v21 = "PassiveObject/Monster/Zepplin/Ani/BulletSmokeR.ani";
        if ( !v20 )
          v21 = "PassiveObject/Monster/Zepplin/Ani/BulletSmokeL.ani";
        v22 = sub_431860((char)v21, 1);
      }
      else
      {
        v22 = 0;
      }
      v23 = (char *)sub_44B6C0(284);
      v14 = v23;
      if ( v23 != nullptr )
      {
        sub_44E0D0(v23, v22, 1);
        *(uint32_t *)v14 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v14 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v14, 2, 0, (int)v14, 0, 0);
      v24 = *(uint32_t *)v14;
      v25 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v24 + 148))(v14, v25);
      v17 = *(uint32_t *)v14;
      v26 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v27 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v26);
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v27);
    }
    else
    {
      v4 = 0;
      if ( sub_42FCB0(228) != 0 )
        v4 = sub_431860((char)"PassiveObject/Monster/Zepplin/Ani/BulletBlast.ani", 1);
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
      sub_45FE80(*(this + 29), (int)v6, 2, 0, (int)v6, 0, 0);
      v7 = *(uint32_t *)v6;
      v8 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v7 + 148))(v6, v8);
      v9 = *(uint32_t *)v6;
      v10 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
      v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v10);
      (*(void (/*thiscall*/ **)(char *, int))(v9 + 112))(v6, v11);
      if ( sub_42FCB0(228) != 0 )
        v12 = sub_431860((char)"PassiveObject/Monster/Zepplin/Ani/BulletSmoke.ani", 1);
      else
        v12 = 0;
      v13 = (char *)sub_44B6C0(284);
      v14 = v13;
      if ( v13 != nullptr )
      {
        sub_44E0D0(v13, v12, 1);
        *(uint32_t *)v14 = &CNRDPooledObject::`vftable';
      }
      else
      {
        v14 = nullptr;
      }
      sub_45FE80(*(this + 29), (int)v14, 2, 0, (int)v14, 0, 0);
      v15 = *(uint32_t *)v14;
      v16 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v15 + 148))(v14, v16);
      v17 = *(uint32_t *)v14;
      v18 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v18);
    }
    return (*(int (/*thiscall*/ **)(char *, int))(v17 + 112))(v14, v19);
  }
  return result;
}


// ------------------------------------------------------------
// 0x53A100 sub_53A100
// ------------------------------------------------------------
// CNExplosiveOil 析构基座：+976 发射器 sub_42AF90 + 归还池 sub_657740(228) → sub_4E2040

int /*thiscall*/ sub_53A100(int this)
{
  void **v2; // edi

  *(uint32_t *)this = &vftbl_CNExplosiveOil;
  v2 = *(void ***)(this + 976);
  if ( v2 != nullptr )
  {
    sub_42AF90(v2);
    sub_657740(v2, 228);
  }
  *(uint32_t *)(this + 976) = 0;
  return sub_4E2040((void **)this);
}



// ------------------------------------------------------------
// 0x53A180 CNExplosiveOil__vmt0
// ------------------------------------------------------------
// CNExplosiveOil__vmt0 删除析构壳

void */*thiscall*/ CNExplosiveOil__vmt0(void *Block, char a2)
{
  sub_53A100((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x53A1B0 sub_53A1B0
// ------------------------------------------------------------
// CNOlreksExplosiveOil 构造器（奥尔克爆炸油桶，CNExplosiveOil 派生）

uint32_t */*thiscall*/ sub_53A1B0(uint32_t *this, char a2, int a3)
{
  sub_5362F0(this, a2, a3);
  *this = &vftbl_CNOlreksExplosiveOil;
  return this;
}



// ------------------------------------------------------------
// 0x53A1E0 CNOlreksExplosiveOil__vmt0
// ------------------------------------------------------------
// CNOlreksExplosiveOil__vmt0 删除析构壳

void */*thiscall*/ CNOlreksExplosiveOil__vmt0(void *Block, char a2)
{
  sub_53A210();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x53A210 sub_53A210
// ------------------------------------------------------------
// CNOlreksExplosiveOil 析构基座 → CNExplosiveOil 析构

int /*thiscall*/ sub_53A210(int this)
{
  *(uint32_t *)this = &vftbl_CNOlreksExplosiveOil;
  return sub_53A100(this);
}



// ------------------------------------------------------------
// ============
// 【分区 4】QuestCage 补全 + 附属容器批量广播辅助族（0x53F510-0x53FFC0）
// CNQuestCage__vmt14C（首帧 CageBack.ani 背景板）+ 一组「对 +1/+2/+3 附属 vector
// 逐元素按虚表槽位转发」的模板化广播器（53F660-53FF00，槽位见各行注释）
// + 0x53FFC0 = std::vector 中段插入器（MSVC 编译器实例化体）。
// ============

// 0x53F510 CNQuestCage__vmt14C
// ------------------------------------------------------------
// CNQuestCage__vmt14C 首帧钩子：+1100==0 → sub_53F540 生成背景板并置已播（一次性）

char /*thiscall*/ CNQuestCage__vmt14C(uint8_t *this)
{
  char result; // al

  CNMapObject__vmt14C();
  result = *(this + 1100);
  if ( result == 0 )
  {
    result = sub_53F540(this);
    *(this + 1100) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x53F540 sub_53F540
// ------------------------------------------------------------
// ★ QuestCage 背景板生成【资源实证】：池化四件套 sub_431920(池, 图集, "../Trap/Animation/CageBack.ani")
// → sub_45FE80 层 2 → 定位 (vt+128-1, vt+124-1) → vt+372(100)/vt+596(0)/vt+604(0)

int /*thiscall*/ sub_53F540(uint32_t *this)
{
  int v2; // eax
  int v3; // ebx
  const char *v4; // ecx
  char *v5; // eax
  char *v6; // edi
  int v7; // ecx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int v11; // eax

  v2 = sub_42FCB0(228);
  v3 = 0;
  if ( v2 != 0 )
  {
    if ( *(this + 96) < 0x10u )
      v4 = (const char *)(this + 91);
    else
      v4 = (const char *)*(this + 91);
    v3 = sub_431920(v2, v4, "../Trap/Animation/CageBack.ani", 1);
  }
  v5 = (char *)sub_44B6C0(284);
  v6 = v5;
  if ( v5 != nullptr )
  {
    sub_44E0D0(v5, v3, 0);
    *(uint32_t *)v6 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v6 = nullptr;
  }
  v7 = *(this + 29);
  *(this + 276) = v6;
  sub_45FE80(v7, (int)v6, 2, 0, (int)v6, (int)this, 0);
  v8 = *(uint32_t *)*(this + 276);
  v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v9 - 1);
  v11 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v10 - 1);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 112))(*(this + 276), v11);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);
}



// ------------------------------------------------------------
// 0x53F660 sub_53F660
// ------------------------------------------------------------
// 附属 vector 线性查找：+1/+2 首/尾，命中 *p==a2 返回 1

char /*thiscall*/ sub_53F660(uint32_t *this, int a2)
{
  uint32_t *v2; // edx
  int v3; // eax
  int v4; // ecx

  v2 = (uint32_t *)*(this + 1);
  if ( v2 != nullptr )
    v3 = (*(this + 2) - (int)v2) >> 2;
  else
    v3 = 0;
  v4 = 0;
  if ( v3 <= 0 )
    return 0;
  while ( *v2 != a2 )
  {
    ++v4;
    ++v2;
    if ( v4 >= v3 )
      return 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x53F6A0 sub_53F6A0
// ------------------------------------------------------------
// 附属查找并卸载：元素+4==a2 → RTDynamicCast→CNRDAuraMaster（光环主人）→ vt+76(0) 解除

char /*thiscall*/ sub_53F6A0(uint32_t *this, int a2)
{
  unsigned int i; // edi
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v7; // esi

  for ( i = 0; ; ++i )
  {
    v4 = *(this + 1);
    if ( v4 == 0 || i >= (*(this + 2) - v4) >> 2 )
      break;
    v5 = *(uint32_t *)(v4 + 4 * i);
    if ( *(uint32_t *)(v5 + 4) == a2 )
    {
      v6 = __RTDynamicCast(v5, 0, &IRDAppendage `RTTI Type Descriptor', &CNRDAuraMaster `RTTI Type Descriptor', 0);
      v7 = v6;
      if ( v6 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v6 + 80))(v6) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v7 + 76))(v7, 0);
        return 1;
      }
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x53F720 sub_53F720
// ------------------------------------------------------------
// 批量广播器 vt+84 槽：遍历 +1..+2 vector，vt+80() 活跃者调 vt+84(a2)

void /*thiscall*/ sub_53F720(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // ebx
  int v5; // ecx
  int v6; // [esp+8h] [ebp-4h]

  v3 = *(this + 1);
  v4 = 0;
  if ( v3 != 0 )
    v6 = (*(this + 2) - v3) >> 2;
  else
    v6 = 0;
  if ( v6 > 0 )
  {
    do
    {
      v5 = *(uint32_t *)(*(this + 1) + 4 * v4);
      if ( v5 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 80))(v5) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(4 * v4 + *(this + 1)) + 84))(
          *(uint32_t *)(4 * v4 + *(this + 1)),
          a2);
      ++v4;
    }
    while ( v4 < v6 );
  }
}



// ------------------------------------------------------------
// 0x53F7A0 sub_53F7A0
// ------------------------------------------------------------
// 批量广播器 vt+8 槽（同上模式）

void /*thiscall*/ sub_53F7A0(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // ebx
  int v5; // ecx
  int v6; // [esp+8h] [ebp-4h]

  v3 = *(this + 1);
  v4 = 0;
  if ( v3 != 0 )
    v6 = (*(this + 2) - v3) >> 2;
  else
    v6 = 0;
  if ( v6 > 0 )
  {
    do
    {
      v5 = *(uint32_t *)(*(this + 1) + 4 * v4);
      if ( v5 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 80))(v5) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(4 * v4 + *(this + 1)) + 8))(
          *(uint32_t *)(4 * v4 + *(this + 1)),
          a2);
      ++v4;
    }
    while ( v4 < v6 );
  }
}



// ------------------------------------------------------------
// 0x53F820 sub_53F820
// ------------------------------------------------------------
// 批量广播器 vt+12 槽

void /*thiscall*/ sub_53F820(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // ebx
  int v5; // ecx
  int v6; // [esp+8h] [ebp-4h]

  v3 = *(this + 1);
  v4 = 0;
  if ( v3 != 0 )
    v6 = (*(this + 2) - v3) >> 2;
  else
    v6 = 0;
  if ( v6 > 0 )
  {
    do
    {
      v5 = *(uint32_t *)(*(this + 1) + 4 * v4);
      if ( v5 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 80))(v5) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(4 * v4 + *(this + 1)) + 12))(
          *(uint32_t *)(4 * v4 + *(this + 1)),
          a2);
      ++v4;
    }
    while ( v4 < v6 );
  }
}



// ------------------------------------------------------------
// 0x53F8A0 sub_53F8A0
// ------------------------------------------------------------
// 批量广播器 vt+48 槽（带返回值，取最后一个）

int /*thiscall*/ sub_53F8A0(int *this, int a2)
{
  int result; // eax
  int v4; // edi
  int i; // esi
  int v6; // eax
  int v7; // ecx

  result = *(this + 1);
  if ( result != 0 )
    v4 = (*(this + 2) - result) >> 2;
  else
    v4 = 0;
  for ( i = 0; i < v4; ++i )
  {
    v6 = *(this + 1);
    v7 = *(uint32_t *)(v6 + 4 * i);
    result = v6 + 4 * i;
    if ( v7 != 0 )
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 48))(v7, a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x53F8F0 sub_53F8F0
// ------------------------------------------------------------
// 批量广播器 vt+52 槽（无参）

void /*thiscall*/ sub_53F8F0(uint32_t *this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // ecx
  int v5; // [esp+8h] [ebp-4h]

  v2 = *(this + 1);
  v3 = 0;
  if ( v2 != 0 )
    v5 = (*(this + 2) - v2) >> 2;
  else
    v5 = 0;
  if ( v5 > 0 )
  {
    do
    {
      v4 = *(uint32_t *)(*(this + 1) + 4 * v3);
      if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 80))(v4) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(4 * v3 + *(this + 1)) + 52))(*(uint32_t *)(4 * v3 + *(this + 1)));
      ++v3;
    }
    while ( v3 < v5 );
  }
}



// ------------------------------------------------------------
// 0x53F960 sub_53F960
// ------------------------------------------------------------
// 批量广播器 vt+16 槽（无参）

void /*thiscall*/ sub_53F960(uint32_t *this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // ecx
  int v5; // [esp+8h] [ebp-4h]

  v2 = *(this + 1);
  v3 = 0;
  if ( v2 != 0 )
    v5 = (*(this + 2) - v2) >> 2;
  else
    v5 = 0;
  if ( v5 > 0 )
  {
    do
    {
      v4 = *(uint32_t *)(*(this + 1) + 4 * v3);
      if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 80))(v4) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(4 * v3 + *(this + 1)) + 16))(*(uint32_t *)(4 * v3 + *(this + 1)));
      ++v3;
    }
    while ( v3 < v5 );
  }
}



// ------------------------------------------------------------
// 0x53F9D0 sub_53F9D0
// ------------------------------------------------------------
// 批量广播器 vt+20 槽：a2 非 0 正向遍历，否则反向且首参固定 0

char /*thiscall*/ sub_53F9D0(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v6; // ecx
  int v7; // ebx
  int v8; // eax
  int v9; // edi
  int v10; // ecx
  int v11; // ecx
  int v13; // [esp+Ch] [ebp-4h]
  int i; // [esp+18h] [ebp+8h]

  v6 = *(this + 1);
  v7 = 0;
  if ( v6 != 0 )
    v13 = (*(this + 2) - v6) >> 2;
  else
    v13 = 0;
  LOBYTE(v8) = a2;
  if ( (uint8_t)a2 != 0 )
  {
    if ( v13 > 0 )
    {
      do
      {
        v11 = *(uint32_t *)(4 * v7 + *(this + 1));
        if ( v11 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 80))(v11) != 0 )
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(**(uint32_t **)(4 * v7 + *(this + 1)) + 20))(
            *(uint32_t *)(4 * v7 + *(this + 1)),
            a2,
            a3,
            a4,
            a5);
        LOBYTE(v8) = v13;
        ++v7;
      }
      while ( v7 < v13 );
    }
  }
  else
  {
    v8 = v13 - 1;
    for ( i = v13 - 1; i >= 0; --i )
    {
      v9 = 4 * v8;
      v10 = *(uint32_t *)(*(this + 1) + 4 * v8);
      if ( v10 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 80))(v10) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, int))(**(uint32_t **)(v9 + *(this + 1)) + 20))(
          *(uint32_t *)(v9 + *(this + 1)),
          0,
          a3,
          a4,
          a5);
      v8 = i - 1;
    }
  }
  return v8;
}



// ------------------------------------------------------------
// 0x53FAB0 sub_53FAB0
// ------------------------------------------------------------
// 批量广播器 vt+24 槽（同 53F9D0 正/反向模式）

char /*thiscall*/ sub_53FAB0(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v6; // ecx
  int v7; // ebx
  int v8; // eax
  int v9; // edi
  int v10; // ecx
  int v11; // ecx
  int v13; // [esp+Ch] [ebp-4h]
  int i; // [esp+18h] [ebp+8h]

  v6 = *(this + 1);
  v7 = 0;
  if ( v6 != 0 )
    v13 = (*(this + 2) - v6) >> 2;
  else
    v13 = 0;
  LOBYTE(v8) = a2;
  if ( (uint8_t)a2 != 0 )
  {
    if ( v13 > 0 )
    {
      do
      {
        v11 = *(uint32_t *)(4 * v7 + *(this + 1));
        if ( v11 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 80))(v11) != 0 )
          (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(**(uint32_t **)(4 * v7 + *(this + 1)) + 24))(
            *(uint32_t *)(4 * v7 + *(this + 1)),
            a2,
            a3,
            a4,
            a5);
        LOBYTE(v8) = v13;
        ++v7;
      }
      while ( v7 < v13 );
    }
  }
  else
  {
    v8 = v13 - 1;
    for ( i = v13 - 1; i >= 0; --i )
    {
      v9 = 4 * v8;
      v10 = *(uint32_t *)(*(this + 1) + 4 * v8);
      if ( v10 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 80))(v10) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, int, int, int))(**(uint32_t **)(v9 + *(this + 1)) + 24))(
          *(uint32_t *)(v9 + *(this + 1)),
          0,
          a3,
          a4,
          a5);
      v8 = i - 1;
    }
  }
  return v8;
}



// ------------------------------------------------------------
// 0x53FB90 sub_53FB90
// ------------------------------------------------------------
// 批量广播器 vt+36 槽

void /*thiscall*/ sub_53FB90(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // ecx
  int v6; // ebx
  int v7; // ecx
  int v8; // [esp+8h] [ebp-4h]

  v5 = *(this + 1);
  v6 = 0;
  if ( v5 != 0 )
    v8 = (*(this + 2) - v5) >> 2;
  else
    v8 = 0;
  if ( v8 > 0 )
  {
    do
    {
      v7 = *(uint32_t *)(*(this + 1) + 4 * v6);
      if ( v7 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 80))(v7) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(**(uint32_t **)(4 * v6 + *(this + 1)) + 36))(
          *(uint32_t *)(4 * v6 + *(this + 1)),
          a2,
          a3,
          a4);
      ++v6;
    }
    while ( v6 < v8 );
  }
}



// ------------------------------------------------------------
// 0x53FC10 sub_53FC10
// ------------------------------------------------------------
// 批量广播器 vt+40 槽

void /*thiscall*/ sub_53FC10(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int v6; // ecx
  int v7; // ebx
  int v8; // ecx
  int v9; // [esp+8h] [ebp-4h]

  v6 = *(this + 1);
  v7 = 0;
  if ( v6 != 0 )
    v9 = (*(this + 2) - v6) >> 2;
  else
    v9 = 0;
  if ( v9 > 0 )
  {
    do
    {
      v8 = *(uint32_t *)(*(this + 1) + 4 * v7);
      if ( v8 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 80))(v8) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(**(uint32_t **)(4 * v7 + *(this + 1)) + 40))(
          *(uint32_t *)(4 * v7 + *(this + 1)),
          a2,
          a3,
          a4,
          a5);
      ++v7;
    }
    while ( v7 < v9 );
  }
}



// ------------------------------------------------------------
// 0x53FC90 sub_53FC90
// ------------------------------------------------------------
// 批量广播器 vt+44 槽（无参）

void /*thiscall*/ sub_53FC90(uint32_t *this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // ecx
  int v5; // [esp+8h] [ebp-4h]

  v2 = *(this + 1);
  v3 = 0;
  if ( v2 != 0 )
    v5 = (*(this + 2) - v2) >> 2;
  else
    v5 = 0;
  if ( v5 > 0 )
  {
    do
    {
      v4 = *(uint32_t *)(*(this + 1) + 4 * v3);
      if ( v4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 80))(v4) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(4 * v3 + *(this + 1)) + 44))(*(uint32_t *)(4 * v3 + *(this + 1)));
      ++v3;
    }
    while ( v3 < v5 );
  }
}



// ------------------------------------------------------------
// 0x53FD00 sub_53FD00
// ------------------------------------------------------------
// 附属查找：元素+4==a2 && vt+92() 活跃 → 1

char /*thiscall*/ sub_53FD00(uint32_t *this, int a2)
{
  unsigned int i; // esi
  int v4; // ecx
  uint32_t *v5; // eax

  for ( i = 0; ; ++i )
  {
    v4 = *(this + 1);
    if ( v4 == 0 || i >= (*(this + 2) - v4) >> 2 )
      break;
    v5 = *(uint32_t **)(v4 + 4 * i);
    if ( v5[1] == a2 && (*(uint8_t (**)(void))(*v5 + 92))() != 0 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x53FD50 sub_53FD50
// ------------------------------------------------------------
// 逐个拆除（vt+32(1) 显隐 + vt+76/vt+68 解绑 + 池析构判定）→ vector 弹出

uint32_t */*thiscall*/ sub_53FD50(int this)
{
  uint32_t *result; // eax
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  while ( 1 )
  {
    result = *(uint32_t **)(this + 4);
    if ( result == nullptr || (*(uint32_t *)(this + 8) - (int)result) >> 2 == 0 )
      break;
    (*(void (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*result + 32))(*result, 1);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***(uint32_t ***)(this + 4) + 76))(**(uint32_t **)(this + 4), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***(uint32_t ***)(this + 4) + 68))(**(uint32_t **)(this + 4), 0);
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(***(uint32_t ***)(this + 4) + 64))(**(uint32_t **)(this + 4)) + 36) != 0 )
    {
      v3 = **(void (/*thiscall*/ *****)(uint32_t, int))(this + 4);
      if ( v3 != nullptr )
        (**v3)(v3, 1);
    }
    memcpy_0(
      *(void **)(this + 4),
      (const void *)(*(uint32_t *)(this + 4) + 4),
      4 * ((*(uint32_t *)(this + 8) - (*(uint32_t *)(this + 4) + 4)) >> 2));
    *(uint32_t *)(this + 8) -= 4;
  }
  return result;
}



// ------------------------------------------------------------
// 0x53FDD0 sub_53FDD0
// ------------------------------------------------------------
// 同上拆除（vt+32(0) 隐藏路径）

void /*thiscall*/ sub_53FDD0(int this)
{
  uint32_t *v2; // ecx
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx

  while ( 1 )
  {
    v2 = *(uint32_t **)(this + 4);
    if ( v2 == nullptr || (*(uint32_t *)(this + 8) - (int)v2) >> 2 == 0 )
      break;
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v2 + 32))(*v2, 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***(uint32_t ***)(this + 4) + 76))(**(uint32_t **)(this + 4), 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(***(uint32_t ***)(this + 4) + 68))(**(uint32_t **)(this + 4), 0);
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(***(uint32_t ***)(this + 4) + 64))(**(uint32_t **)(this + 4)) + 36) != 0 )
    {
      v3 = **(void (/*thiscall*/ *****)(uint32_t, int))(this + 4);
      if ( v3 != nullptr )
        (**v3)(v3, 1);
    }
    memcpy_0(
      *(void **)(this + 4),
      (const void *)(*(uint32_t *)(this + 4) + 4),
      4 * ((*(uint32_t *)(this + 8) - (*(uint32_t *)(this + 4) + 4)) >> 2));
    *(uint32_t *)(this + 8) -= 4;
  }
}



// ------------------------------------------------------------
// 0x53FE50 sub_53FE50
// ------------------------------------------------------------
// 按指针移除：找到 a2 → vt+32(0) → memmove 收缩 → vt+76/vt+68(0)

int /*thiscall*/ sub_53FE50(uint32_t *this, int a2)
{
  uint32_t *v3; // ecx
  int result; // eax
  int v5; // ebx

  v3 = (uint32_t *)*(this + 1);
  if ( v3 != nullptr )
    result = (*(this + 2) - (int)v3) >> 2;
  else
    result = 0;
  v5 = 0;
  if ( result > 0 )
  {
    while ( *v3 != a2 )
    {
      ++v5;
      ++v3;
      if ( v5 >= result )
        return result;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 32))(a2, 0);
    memcpy_0(
      (void *)(*(this + 1) + 4 * v5),
      (const void *)(*(this + 1) + 4 * v5 + 4),
      4 * ((*(this + 2) - (*(this + 1) + 4 * v5 + 4)) >> 2));
    *(this + 2) -= 4;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 76))(a2, 0);
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a2 + 68))(a2, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x53FEE0 sub_53FEE0
// ------------------------------------------------------------
// 移除并析构：sub_53FE50 + a2 非 0 则 vt+0(1)

int /*thiscall*/ sub_53FEE0(uint32_t *this, int (/*thiscall*/ ***a2)(uint32_t, int))
{
  int result; // eax

  result = sub_53FE50(this, (int)a2);
  if ( a2 != nullptr )
    return (**a2)(a2, 1);
  return result;
}



// ------------------------------------------------------------
// 0x53FF00 sub_53FF00
// ------------------------------------------------------------
// 全体 tick：遍历调 vt+4()，vt+80()==0 失活者按 +36 池标志决定析构并移除（倒序收缩）

int /*thiscall*/ sub_53FF00(int *this)
{
  int result; // eax
  int v3; // ebx
  int v4; // edi
  int v5; // ecx
  char v6; // cl
  int *v7; // eax
  void (/*thiscall*/ ***v8)(uint32_t, int); // edi
  int v9; // [esp+8h] [ebp-4h]

  result = *(this + 1);
  v3 = 0;
  if ( result != 0 )
    v9 = (*(this + 2) - result) >> 2;
  else
    v9 = 0;
  if ( v9 > 0 )
  {
    do
    {
      v4 = 4 * v3;
      v5 = *(uint32_t *)(4 * v3 + *(this + 1));
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 80))(v5) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + *(this + 1)) + 4))(*(uint32_t *)(v4 + *(this + 1)));
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + *(this + 1)) + 80))(*(uint32_t *)(v4 + *(this + 1))) == 0 )
      {
        v6 = *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + *(this + 1)) + 64))(*(uint32_t *)(v4 + *(this + 1)))
                      + 36);
        v7 = (int *)(v4 + *(this + 1));
        if ( v6 != 0 )
        {
          v8 = (void (/*thiscall*/ ***)(uint32_t, int))*v7;
          sub_53FE50(this, *v7);
          if ( v8 != nullptr )
            (**v8)(v8, 1);
        }
        else
        {
          sub_53FE50(this, *v7);
        }
        --v9;
        --v3;
      }
      result = v9;
      ++v3;
    }
    while ( v3 < v9 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x53FFC0 sub_53FFC0
// ------------------------------------------------------------
// std::vector<T>::insert 编译器实例化体：+4/+8/+12 首/尾/容，0x3FFFFFFF 容量上限，
// 扩容 1.5×（result+result>>1），sub_55E7F0/sub_5DAF70/sub_523700/sub_49A9D0 为 MSVC 辅助

unsigned int /*thiscall*/ sub_53FFC0(int this, int Src, unsigned int a3, int *a4)
{
  int v5; // edx
  unsigned int result; // eax
  int v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v14; // eax
  void *v15; // eax
  int v16; // eax
  int v17; // ecx
  unsigned int v18; // edi
  uint8_t *v19; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *v23; // edi
  int v24; // edi
  char *v25; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  v5 = *(uint32_t *)(this + 4);
  a4 = (int *)*a4;
  if ( v5 != 0 )
    result = (*(uint32_t *)(this + 12) - v5) >> 2;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v8 = 0;
    if ( 0x3FFFFFFF - v8 < a3 )
      sub_4D7080(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( result >= a3 + v9 )
    {
      v19 = *(uint8_t **)(this + 8);
      v21 = (int)&v19[-Src] >> 2;
      v22 = 4 * a3;
      v29 = (int)v19;
      Srca = (char *)(4 * a3);
      if ( v21 >= a3 )
      {
        v24 = (int)&v19[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&v19[-v22], (int)v19, v19);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &a4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)v19, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), a3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &a4);
        v23 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = v23;
        return sub_49A9D0(Src, v23 - Srca, &a4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 2;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 2;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v28 = 4 * v10;
      v25 = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      v14 = (char *)memcpy_0(v25, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&v14[Srcb], a3, &a4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 2;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v25[v28];
      *(uint32_t *)(this + 8) = &v25[4 * v18];
      *(uint32_t *)(this + 4) = v25;
      return (unsigned int)v25;
    }
  }
  return result;
}

