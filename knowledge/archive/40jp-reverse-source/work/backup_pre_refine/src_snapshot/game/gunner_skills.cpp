// ============================================================
// 【40JP逆向源代码工程】game/gunner_skills.cpp
// 模块: 枪手技能 PassiveObject
// 来源: work/dump_miscb.txt  区块: 0x530000-0x540000
// 层级: L2 转写层 —— 反编译输出的规范化重排(类型名清洗/VA标记/分模块),
//        语义与 IDA Hex-Rays 逐字对应; 精修层(L1)见 src/nengine|cnrd 与 docs/10-15
// 函数数: 244
// ============================================================

#include "../../common/arad_types.h"

// ------------------------------------------------------------
// 0x535AD0 sub_535AD0
// ------------------------------------------------------------
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
int /*thiscall*/ CNRollingStone__vmt214(uint32_t *this, int a2, int a3, int a4)
{
  *(uint32_t *)(*(this + 28) + 16) = 0;
  *(uint32_t *)(*(this + 28) + 28) = 0;
  return sub_620300(0.0);
}



// ------------------------------------------------------------
// 0x535D10 CNRollingStone__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_535E40(void **this)
{
  *this = &vftbl_CNTrapCage;
  sub_620BC0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x535E90 sub_535E90
// ------------------------------------------------------------
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
int /*thiscall*/ sub_536180(void **this)
{
  *this = &vftbl_CNSpiner;
  sub_621F30();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5361D0 sub_5361D0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5363E0(void **this)
{
  *this = &vftbl_CNHallucinationFlower;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536430 sub_536430
// ------------------------------------------------------------
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
uint8_t */*thiscall*/ sub_5364E0(uint8_t *this, int a2, int a3)
{
  sub_536430(this, a2, a3, 17, 2);
  *(uint32_t *)this = &vftbl_CNStarFishEggRequid;
  return this;
}



// ------------------------------------------------------------
// 0x536510 sub_536510
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_536510(uint8_t *this, int a2, int a3, int a4, int a5)
{
  sub_536430(this, a2, a3, a4, a5);
  *(uint32_t *)this = &vftbl_CNMagmaSwamp;
  return this;
}



// ------------------------------------------------------------
// 0x536540 CNSwamp__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_536620(void **this)
{
  *this = &vftbl_CNFloorNiddle;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536630 sub_536630
// ------------------------------------------------------------
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
int /*thiscall*/ sub_536800(void **this)
{
  *this = &vftbl_CNTwistFootHold;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536850 sub_536850
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5368E0(void **this)
{
  *this = &vftbl_CNSeaGrass;
  sub_6269A0();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536930 sub_536930
// ------------------------------------------------------------
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
int /*thiscall*/ sub_536D50(void **this)
{
  *this = &vftbl_CNPassiveObjectTrigger;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536D60 sub_536D60
// ------------------------------------------------------------
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
int /*thiscall*/ sub_536DF0(uint32_t *this)
{
  *this = &vftbl_CNBellForZealots;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x536E00 sub_536E00
// ------------------------------------------------------------
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
int /*thiscall*/ sub_536E90(void **this)
{
  *this = &vftbl_CNGravityChanger;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536EE0 sub_536EE0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_536F70(void **this)
{
  *this = &vftbl_CNDroppingRockTrigger;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x536F80 sub_536F80
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537010(void **this)
{
  *this = &vftbl_CNDroppingRock;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537020 sub_537020
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5371D0(void **this)
{
  *this = &vftbl_CNBehemothHelipad;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5371E0 sub_5371E0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537240(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadSide;
  nullsub_3();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537290 CNDragonHeadSide__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537380(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadSideFlame;
  sub_629010();
  return sub_537240(this);
}



// ------------------------------------------------------------
// 0x5373D0 CNDragonHeadSideFlame__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537460(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadSideNentan;
  nullsub_3();
  return sub_537240(this);
}



// ------------------------------------------------------------
// 0x5374B0 CNDragonHeadSideNentan__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537540(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadSideGas;
  nullsub_3();
  return sub_537240(this);
}



// ------------------------------------------------------------
// 0x537590 CNDragonHeadSideGas__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5376B0(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadFrontFlame;
  return sub_537380(this);
}



// ------------------------------------------------------------
// 0x5376C0 sub_5376C0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537720(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadFrontNentan;
  return sub_537460(this);
}



// ------------------------------------------------------------
// 0x537730 sub_537730
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537790(uint32_t *this)
{
  *this = &vftbl_CNDragonHeadFrontGas;
  return sub_537540(this);
}



// ------------------------------------------------------------
// 0x5377A0 sub_5377A0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537830(uint32_t *this)
{
  *this = &vftbl_CNCystalPillar;
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537840 sub_537840
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5378D0(void **this)
{
  *this = &vftbl_CNEyeofObserver;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537920 sub_537920
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5379B0(void **this)
{
  *this = &vftbl_CNActiveObserver;
  sub_629C40();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537A00 sub_537A00
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537A90(void **this)
{
  *this = &vftbl_CNLightBulb;
  sub_60C870();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537AE0 sub_537AE0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537B70(void **this)
{
  *this = &vftbl_CNWaterDrop;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537BC0 sub_537BC0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537DC0(void **this)
{
  *this = &vftbl_CNTreeCross;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x537E10 sub_537E10
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537EA0(uint32_t *this)
{
  *this = &vftbl_CNSkeletonPile;
  sub_60A950();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537EF0 sub_537EF0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_537F80(uint32_t *this)
{
  *this = &vftbl_CNSpiderSpawn;
  sub_60A950();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x537FD0 sub_537FD0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538060(uint32_t *this)
{
  *this = &vftbl_CN2StoryBox;
  nullsub_3();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x5380B0 sub_5380B0
// ------------------------------------------------------------
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
uint8_t */*thiscall*/ sub_5384F0(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNHPFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538520 CNHPFairy__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538550(uint32_t *this)
{
  *this = &vftbl_CNHPFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x5385A0 sub_5385A0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5385A0(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNMPFairy;
  return this;
}



// ------------------------------------------------------------
// 0x5385D0 CNMPFairy__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538600(uint32_t *this)
{
  *this = &vftbl_CNMPFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x538650 sub_538650
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_538650(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNHPMPFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538680 CNHPMPFairy__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5386B0(uint32_t *this)
{
  *this = &vftbl_CNHPMPFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x538700 sub_538700
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_538700(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNSuperArmorFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538730 CNSuperArmorFairy__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538760(uint32_t *this)
{
  *this = &vftbl_CNSuperArmorFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x5387B0 sub_5387B0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5387B0(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNHasteFairy;
  return this;
}



// ------------------------------------------------------------
// 0x5387E0 CNHasteFairy__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538810(uint32_t *this)
{
  *this = &vftbl_CNHasteFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x538860 sub_538860
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_538860(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNBlessFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538890 CNBlessFairy__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5388C0(uint32_t *this)
{
  *this = &vftbl_CNBlessFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x538910 sub_538910
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_538910(uint8_t *this, int a2, int a3)
{
  sub_5383C0(this, a2, a3);
  *(uint32_t *)this = &vftbl_CNInvinsibleFairy;
  return this;
}



// ------------------------------------------------------------
// 0x538940 CNInvinsibleFairy__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538970(uint32_t *this)
{
  *this = &vftbl_CNInvinsibleFairy;
  sub_60A950();
  return sub_538460(this);
}



// ------------------------------------------------------------
// 0x5389C0 sub_5389C0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538A50(void **this)
{
  *this = &vftbl_CNFairyFactory;
  sub_5FF980();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x538AA0 sub_538AA0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538B40(uint32_t *this)
{
  *this = &vftbl_CNActionTree;
  sub_60A950();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x538B90 sub_538B90
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538C40(void **this)
{
  *this = &vftbl_CNSoundFloor;
  sub_41B010(this + 275);
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x538CA0 sub_538CA0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538D40(uint32_t *this)
{
  *this = &vftbl_CNFountain;
  sub_60A950();
  return sub_52EE30(this);
}



// ------------------------------------------------------------
// 0x538D90 sub_538D90
// ------------------------------------------------------------
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
int /*thiscall*/ sub_538E70(uint32_t *this)
{
  *this = &vftbl_CNCircleAppendageENCHANTWEAPON;
  return sub_530780();
}



// ------------------------------------------------------------
// 0x538E80 CNCircleAppendageENCHANTWEAPON__vmt0
// ------------------------------------------------------------
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
unsigned int /*thiscall*/ CNCircleAppendageENCHANTWEAPON__vmt2BC(int this, const void *a2, unsigned int a3)
{
  qmemcpy((void *)(this + 984), a2, a3);
  return a3;
}



// ------------------------------------------------------------
// 0x538FD0 CNCircleAppendageCHANGESTATE__vmt2C4
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5390A0(uint32_t *this)
{
  *this = &vftbl_CNCircleAppendageCHANGESTATE;
  return sub_530780();
}



// ------------------------------------------------------------
// 0x5390B0 sub_5390B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5390B0(uint32_t *this, int a2, int a3, int a4)
{
  sub_530710(a2, a3, a4);
  *this = &vftbl_CNCircleAppendageDISENCHANT;
  return this;
}



// ------------------------------------------------------------
// 0x5390E0 CNCircleAppendageDISENCHANT__vmt2C8
// ------------------------------------------------------------
uint32_t */*stdcall*/ CNCircleAppendageDISENCHANT__vmt2C8(uint32_t *a1, uint32_t *a2)
{
  *a1 = 600;
  *a2 = 1;
  return a1;
}



// ------------------------------------------------------------
// 0x539100 CNCircleAppendageDISENCHANT__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_539130(uint32_t *this)
{
  *this = &vftbl_CNCircleAppendageDISENCHANT;
  return sub_530780();
}



// ------------------------------------------------------------
// 0x539140 sub_539140
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5391D0(void **this)
{
  *this = &vftbl_CNGravityChangeBack;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x539220 sub_539220
// ------------------------------------------------------------
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
int /*thiscall*/ sub_5392B0(void **this)
{
  *this = &vftbl_CNStorageBird;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x539300 sub_539300
// ------------------------------------------------------------
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
int /*thiscall*/ sub_539390(void **this)
{
  *this = &vftbl_CNFallingStorage;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5393E0 sub_5393E0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_539470(uint32_t *this)
{
  *this = &vftbl_CNStorageSub;
  return sub_534900();
}



// ------------------------------------------------------------
// 0x539480 sub_539480
// ------------------------------------------------------------
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
int /*thiscall*/ sub_539510(void **this)
{
  *this = &vftbl_CNEPLPCampFire;
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x539520 sub_539520
// ------------------------------------------------------------
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
int /*thiscall*/ sub_539770(void **this)
{
  *this = &vftbl_CNAuxoRoot;
  sub_5FF980();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5397C0 sub_5397C0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_539850(void **this)
{
  *this = &vftbl_CNFireBallCommon;
  nullsub_3();
  return sub_4E2040(this);
}



// ------------------------------------------------------------
// 0x5398A0 CNRDPooledPassiveObject__vmt0
// ------------------------------------------------------------
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
uint32_t */*thiscall*/ sub_53A1B0(uint32_t *this, char a2, int a3)
{
  sub_5362F0(this, a2, a3);
  *this = &vftbl_CNOlreksExplosiveOil;
  return this;
}



// ------------------------------------------------------------
// 0x53A1E0 CNOlreksExplosiveOil__vmt0
// ------------------------------------------------------------
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
int /*thiscall*/ sub_53A210(int this)
{
  *(uint32_t *)this = &vftbl_CNOlreksExplosiveOil;
  return sub_53A100(this);
}



// ------------------------------------------------------------
// 0x53F510 CNQuestCage__vmt14C
// ------------------------------------------------------------
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

