// ============================================================
// 【40JP逆向源代码工程】combat/breakable_map.cpp
// 模块: 0x62 可破坏地图物件（PassiveObject/MapObject/BreakableObject/ 体系）
// 来源: work/dump_skills.txt  区块: 0x620000-0x630000
// 层级: L1 精修层 —— 在 L2 转写体上升级文件头/分区横幅/函数头注释；
//       函数体保持 Hex-Rays 忠实输出，零改动（仅整行注释插入与注释行替换）
// 函数数: 321
// ------------------------------------------------------------
// ★ L1 精修要点：
//   1. 按物件类型分区（分区 1-19）：滚石/铁笼/吊灯/风扇旋涡/海底生态/沼泽/地刺/
//      掩体/植物/海星卵/钟与落石/龙头炮台/观察者水晶/灯泡月神/骸骨箱笼/
//      格伦掩体/妖精/氛围物件/块尾 UI 窗口杂项
//   2. 音效 TAG 与 .ani/.ptl 资源逐函数标注（证据直接引自本文件反编译体字符串）
//   3. 交叉引用（研究 21《打击感公式算法速查》）：粒子移动三类型 §P40、
//      速率链（rate=raw*0.1，100=常速）§P38、过场演出=大状态 tick case §P41
//   4. 块尾 0x62E640 起为 CNRDWarRoomListWindow/CNRDCompoundItemWindow 等
//      CNRD 窗口类 —— 与可破坏物无关，系 dump 区块相邻导致的归属，见分区 19
// ------------------------------------------------------------
// ★ 区块资源证据速查：
//   滚石/落石: TRAP_STONE_ROLLING_LOOP / TRAP_STONE_BREAK / TAU_EQUAKE
//   铁笼:     JAIL_BREAK / JAIL_CRASH + PassiveObject/MapObject/Trap/Animation/CageBack.ani
//   吊灯:     SIZZLE_LOOP / CHANDELIER_CUT / CHANDELIER_BROKEN
//   风扇旋涡: FAN_ROTATE_LOOP / FAN_WIND_BLOW_LOOP / IRON_HIT / SPINNER_ON / SPINNER_LOOP
//             / SPINNER_BREAK + Trap/Particle/SpinerMovePath.ptl / SpinerBubble.ptl
//   掩体:     BUNKER_HIT / BUNKER_BREAK / BUNKER_OPEN / GBN_FRIGHT + Heal.ani（哥布林/格伦各一套）
//   植物:     BURN_VINE / TIE_VINE / WALK_VINE_LOOP / TWIST_AMB_LOOP / TWIST_SPIN
//   海星卵:   WRIGGLE_SLOW_LOOP / WRIGGLE_FAST_LOOP / HATCH_EGG；莲花: LOTUS_SWEEP_LOOP
//   钟/重力:  HIT_BELL / BREAK_BELL / BEHEMOTH_CRY / ZOOM_UP / BEHEMOTH_SCREAM / SUDDEN_DROP
//   生态:     SWAMP_BUBBLE_LOOP / R_WALK_SWAMP_LOOP / BISHOP_EYE / CROSS_CRASH
//   妖精:     TINGKERBELL_FLOAT_LOOP / _MP_ABSORB / _HP_ABSORB / _ALL_ABSORB
//   氛围:     FOUNTAIN_FLOW_LOOP / CAMPFIRE_LOOP / NEN_BEGIN / FireBallStart.ani
//   粒子:     BreakableObject/Particle/SeaGrassBubble.ptl、FastThrowStone / IceMissile /
//             FireMissile / AimingBomb.ptl（属性投掷四选一）、DragonHeadEnergyBall(Vertical).ptl、
//             light.ptl、GhoulThrowerSkull.ptl、PoisonBug.ptl
// ============================================================


#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】滚石族（CNRollingStone + 触发辅助 0x620090-0x620BC0）
// 物件: 会滚动的巨石陷阱；音效证据 TRAP_STONE_ROLLING_LOOP（滚动循环）
// 结构: 构造/析构 + tick + 碰撞 + 音效循环驱动；落石破碎见 0x628960（分区 11）
// ============================================================

// ------------------------------------------------------------
// 0x620090 sub_620090
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_620090(int this, int a2)
{
  unsigned int result; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // eax
  int v8; // ebx
  int v9; // edx
  unsigned int v10; // edi
  int *v11; // eax
  int v12; // [esp+4h] [ebp-Ch] BYREF
  int i; // [esp+8h] [ebp-8h]
  unsigned int v14; // [esp+Ch] [ebp-4h]

  result = sub_699000(this + 36);
  *(uint32_t *)(this + 996) = result;
  v4 = *(uint32_t *)(this + 348);
  if ( v4 != 0 )
  {
    result = (*(uint32_t *)(this + 352) - v4) >> 2;
    if ( result > 3 )
    {
      result = *(uint32_t *)(this + 348);
      if ( *(uint32_t *)(v4 + 12) != 0 )
      {
        *(uint8_t *)(this + 1000) = 1;
        result = *(uint32_t *)(result + 12) - 1;
        *(uint32_t *)(this + 1004) = result;
      }
    }
  }
  v5 = *(uint32_t *)(this + 348);
  if ( v5 != 0 )
  {
    result = (*(uint32_t *)(this + 352) - v5) >> 2;
    if ( result > 7 )
    {
      v14 = 0;
      for ( i = 28; ; i += 4 )
      {
        v6 = *(uint32_t *)(this + 348);
        v7 = v6 != 0 ? (*(uint32_t *)(this + 352) - v6) >> 2 : 0;
        result = v7 - 7;
        if ( v14 >= result )
          break;
        v8 = *(uint32_t *)(i + *(uint32_t *)(this + 348));
        v9 = *(uint32_t *)(this + 980);
        v12 = v8;
        if ( v9 != 0 )
          v10 = (*(uint32_t *)(this + 984) - v9) >> 2;
        else
          v10 = 0;
        if ( v9 != 0 && v10 < (*(uint32_t *)(this + 988) - v9) >> 2 )
        {
          v11 = *(int **)(this + 984);
          *v11 = v8;
          *(uint32_t *)(this + 984) = v11 + 1;
        }
        else
        {
          sub_430C80(this + 976, *(uint32_t *)(this + 984), 1u, &v12);
        }
        ++v14;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6201B0 sub_6201B0
// ------------------------------------------------------------
int /*thiscall*/ sub_6201B0(int this)
{
  int v2; // edi
  int result; // eax

  v2 = this + 992;
  *(uint8_t *)(this + 972) = 1;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  sub_41BFE0((void **)(this + 992), nullptr);
  result = sub_41B0D0(v2);
  *(uint32_t *)(this + 1000) = 0;
  *(uint32_t *)(this + 1008) = 0;
  *(uint32_t *)(this + 1004) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x620210 sub_620210
// ------------------------------------------------------------
int /*thiscall*/ sub_620210(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 247);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 247) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x620230 CNRollingStone__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNRollingStone__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);
  if ( *(this + 250) == a2 )
    *(this + 250) = 0;
}



// ------------------------------------------------------------
// 0x620270 sub_620270
// ------------------------------------------------------------
int /*thiscall*/ sub_620270(uint32_t *this)
{
  int result; // eax
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // [esp-8h] [ebp-18h]
  int v8; // [esp-4h] [ebp-14h]
  int v9; // [esp+8h] [ebp-8h] BYREF
  int v10; // [esp+Ch] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  if ( *(uint32_t *)(result + 44) != 0 )
  {
    v3 = *this;
    v10 = 0;
    v9 = 0;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v3 + 124))(this);
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    sub_48C070(&v10, &v9, v4, v8);
    result = v10;
    if ( v10 != *(this + 251) || v9 != *(this + 252) )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
      result = sub_48DA40(v5, v7, 0);
      v6 = v9;
      *(this + 251) = v10;
      *(this + 252) = v6;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x620300 sub_620300
// ------------------------------------------------------------
int /*thiscall*/ sub_620300(float **this, float a2)
{
  int result; // eax
  float *v4; // esi
  uint32_t *v5; // esi

  result = (*((int (/*thiscall*/ **)(float **))*this + 77))(this);
  if ( (uint8_t)result != 0 )
  {
    if ( fabs(a2) >= 5.0 )
    {
      if ( a2 >= -1000.0 )
      {
        if ( a2 > 1000.0 )
          a2 = 1000.0;
      }
      else
      {
        a2 = -1000.0;
      }
    }
    else
    {
      a2 = 0.0;
    }
    v4 = *(this + 28);
    if ( *(uint32_t *)v4 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)v4 + 308))(*(uint32_t *)v4) != 0
      && v4[4] != a2 )
    {
      v4[4] = a2;
      *((uint8_t *)v4 + 196) = 1;
    }
    if ( a2 <= 0.0 )
    {
      if ( a2 >= 0.0 )
        sub_4955C0(0, 0);
      else
        sub_4955C0(0, 20);
    }
    else
    {
      v5 = *(this + 28);
      if ( *v5 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v5 + 308))(*v5) != 0 && v5[7] != -20 )
      {
        v5[7] = -20;
        *((uint8_t *)v5 + 196) = 1;
        sub_494F60(0, -1);
        return sub_4A0600(0);
      }
    }
    return sub_4A0600(0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x620420 CNRollingStone__vmt140
// ------------------------------------------------------------
char /*thiscall*/ CNRollingStone__vmt140(int *this)
{
  int v2; // eax
  int v3; // edi
  int *v4; // eax
  double v5; // st7
  float v6; // eax
  int v7; // eax
  double v8; // st7
  int v9; // eax
  uint64_t v10; // rax
  float v12; // [esp+4h] [ebp-24h]
  float v13; // [esp+4h] [ebp-24h]
  float v14; // [esp+4h] [ebp-24h]
  float v15; // [esp+8h] [ebp-20h]
  float v16; // [esp+8h] [ebp-20h]
  float v17; // [esp+8h] [ebp-20h]

  if ( *((uint8_t *)this + 276) != 0 )
  {
    v2 = 0;
    switch ( *(uint32_t *)(dword_8F7A24 + 12) )
    {
      case 3:
        v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);
        break;
      case 4:
        v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);
        break;
      case 6:
        v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);
        break;
      default:
        break;
    }
    v3 = *(uint32_t *)(v2 + 112);
    v4 = (int *)*(this + 87);
    --v3;
    v15 = (float)v4[1];
    v12 = (float)*v4;
    v5 = sub_4049C0(v12, v15, v3, 98);
    v6 = *(float *)this;
    *((float *)this + 181) = v5;
    (*(void (/*thiscall*/ **)(int *, int *))(LODWORD(v6) + 344))(this, this + 181);
    v7 = *(this + 87);
    v16 = (float)*(int *)(v7 + 12);
    v13 = (float)*(int *)(v7 + 8);
    v8 = sub_4049C0(v13, v16, v3, 98);
    v9 = *(this + 87);
    *((float *)this + 245) = v8;
    v17 = (float)*(int *)(v9 + 24);
    v14 = (float)*(int *)(v9 + 20);
    v10 = (uint64_t)sub_4049C0(v14, v17, v3, 98);
    *(this + 170) = v10;
    *(this + 171) = v10;
  }
  return CNRDPassiveObject__vmt140(this);
}



// ------------------------------------------------------------
// 0x620540 sub_620540
// ------------------------------------------------------------
int /*thiscall*/ sub_620540(int this, int a2)
{
  int *v2; // eax
  float v4; // [esp+8h] [ebp-4h]

  v2 = (int *)(*(uint32_t *)(this + 348) + 28);
  *(uint8_t *)(this + 700) = 0;
  *(uint32_t *)(this + 96) = 545;
  v4 = (double)*v2 * 0.0099999998;
  sub_4922F0(v4);
  return sub_4922F0(v4);
}



// ------------------------------------------------------------
// 0x620590 CNRollingStone__vmt160
// ------------------------------------------------------------
int /*thiscall*/ CNRollingStone__vmt160(int *this)
{
  int result; // eax

  IRDCollisionObject__vmt160(this);
  result = *(this + 250);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 356))(this, *(this + 250));
  return result;
}



// ------------------------------------------------------------
// 0x6205B0 sub_6205B0
// ------------------------------------------------------------
void /*thiscall*/ sub_6205B0(int **this, int a2)
{
  int *v3; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  int *v8; // edi
  int v9; // eax
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+24h] [ebp-4h]

  if ( ((uint8_t (/*thiscall*/ *)(int **))(*this)[77])(this) != 0 )
    ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  v3 = *(this + 247);
  v4 = *v3;
  v5 = ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[31])(this, 0);
  v6 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v5);
  (*(void (/*thiscall*/ **)(int *, int))(v4 + 40))(v3, v6);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 247) + 12))(*(this + 247), 0);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 247) + 92))(*(this + 247), v10);
  v7 = *(this + 29);
  v12 = 0;
  sub_4600B0(v7, 2, 0, (int)v10);
  v8 = *this;
  v9 = sub_41ACF0(this + 249);
  ((void (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t))v8[53])(this, v9, -1, 0, 0);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x620680 CNRollingStone__vmt14C
//   【滚石】TRAP_STONE_ROLLING_LOOP —— 滚动循环音/滚动状态驱动
// ------------------------------------------------------------
void /*thiscall*/ sub_620680(void *this)
{
  int v2; // ecx
  int v3; // ecx
  long double v4; // st7
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // ebx
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  float v18; // [esp+8h] [ebp-8h]
  float v19; // [esp+Ch] [ebp-4h]

  sub_600890();
  if ( *((uint8_t *)this + 984) == 0 )
  {
    v2 = *((uint32_t *)this + 87);
    if ( v2 != 0 && (unsigned int)((*((uint32_t *)this + 88) - v2) >> 2) > 4 )
    {
      v3 = *(uint32_t *)(v2 + 16);
      if ( v3 != 0 )
      {
        if ( v3 == 1 )
          sub_620300(-200.0);
        else
          sub_620300(200.0);
      }
    }
    *((uint8_t *)this + 984) = 1;
  }
  v19 = *(float *)(*((uint32_t *)this + 28) + 16);
  v4 = fabs(v19);
  v18 = v4;
  if ( v4 >= 5.0 )
  {
    v9 = *((uint32_t **)this + 30);
    if ( v19 >= 0.0 )
    {
      if ( v19 <= 0.0 )
      {
LABEL_23:
        if ( *((uint8_t *)this + 972) != 0 )
        {
          v13 = *((uint32_t *)this + 30);
          *((uint8_t *)this + 972) = 0;
          sub_4939E0(v13, 0);
          (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 596))(this, 1);
          (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);
          (*(void (/*thiscall*/ **)(void *, const char *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "TRAP_STONE_ROLLING_LOOP",
            0,
            0,
            0);
        }
        sub_493D00(*((uint32_t *)this + 30), v18);
        if ( sub_699000((int)this + 36) >= *((uint32_t *)this + 244) + 1500 )
        {
          (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 352))(this);
          *((uint32_t *)this + 244) = sub_699000((int)this + 36);
        }
        goto LABEL_27;
      }
      v10 = **((uint32_t **)this + 36);
    }
    else
    {
      v10 = *((uint32_t *)this + 34);
    }
    if ( v9 != (uint32_t *)v10 )
    {
      v11 = v9[11];
      if ( v11 != 0 )
        v11 = (v9[12] - v11) / 88;
      v12 = sub_491C70(v10, v11 - v9[37] - 1);
      sub_493A60(v10, v12);
      (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 196))(this, v10);
    }
    goto LABEL_23;
  }
  if ( *((uint8_t *)this + 972) != 0 )
    goto LABEL_28;
  v5 = *((uint32_t *)this + 30);
  *((uint8_t *)this + 972) = 1;
  sub_4939E0(v5, 1);
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 596))(this, 0);
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 676))(this, 2);
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 216))(this, 0);
  *((uint32_t *)this + 250) = 0;
  sub_62D810(this);
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this) != 0 )
  {
    v6 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this);
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v6 + 40))(v6, 529) != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this);
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 340))(v7) == 50002 )
      {
        v8 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 304))(this);
        sub_6205B0(v8);
      }
    }
  }
LABEL_27:
  sub_620270(this);
LABEL_28:
  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 444))(this) < 0
      || ((v14 = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 29) + 132) + 44),
           v15 = *(uint32_t *)(v14 + 364),
           v16 = v14 + 360,
           v15 != 0)
        ? (v17 = (*(uint32_t *)(v16 + 8) - v15) >> 5)
        : (v17 = 0),
          (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 440))(this) > 224 * v17) )
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    }
    if ( v18 < 5.0 && v19 != 0.0 )
      sub_620300(0.0);
  }
}


// ------------------------------------------------------------
// 0x620960 CNRollingStone__vmt2B4
// ------------------------------------------------------------
int /*thiscall*/ CNRollingStone__vmt2B4(int this, int a2, int a3, int a4, int a5, int a6)
{
  double v8; // st7
  float *v9; // edi
  int v10; // eax
  float v12; // [esp+4h] [ebp-Ch]
  float v13; // [esp+18h] [ebp+8h]

  if ( *(int *)(this + 680) > 0 )
  {
    if ( a2 != 0 )
    {
      v13 = (double)a3 / *(float *)(this + 980) * 100.0;
      if ( v13 != 0.0 )
      {
        if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 660))(a2, this) != 0 )
          v8 = *(float *)(*(uint32_t *)(this + 112) + 16) - v13;
        else
          v8 = v13 + *(float *)(*(uint32_t *)(this + 112) + 16);
        v12 = v8;
        sub_620300((float **)this, v12);
        *(uint32_t *)(this + 1000) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 576))(a2);
      }
    }
  }
  else
  {
    sub_6205B0((int **)this, a2);
  }
  v9 = *(float **)this;
  v10 = sub_41ACF0(this + 992);
  return (*((int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))v9 + 53))(this, v10, -1, 0, 0);
}



// ------------------------------------------------------------
// 0x620A10 CNRollingStone__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNRollingStone__vmtC(int this)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // eax

  CNRDPassiveObject__vmtC((int *)this);
  sub_49FD20(*(uint32_t *)(this + 112));
  *(uint32_t *)(*(uint32_t *)(this + 112) + 16) = 0;
  *(uint32_t *)(*(uint32_t *)(this + 112) + 28) = 0;
  v2 = *(uint32_t *)(this + 120);
  *(uint8_t *)(this + 972) = 1;
  sub_4939E0(v2, 1);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 596))(this, 0);
  *(uint32_t *)(this + 688) = 2;
  *(uint8_t *)(this + 984) = 0;
  if ( operator new(0x12Cu) != nullptr )
  {
    v3 = *(uint32_t *)(this + 712);
    if ( *(uint32_t *)(this + 384) < 0x10u )
    {
      v7 = sub_41ACF0(v3);
      v6 = sub_4C3640(this + 364, v7, this);
    }
    else
    {
      v4 = *(uint32_t *)(this + 364);
      v5 = sub_41ACF0(v3);
      v6 = sub_4C3640(v4, v5, this);
    }
  }
  else
  {
    v6 = 0;
  }
  *(uint32_t *)(this + 988) = v6;
  sub_41B0D0(*(uint32_t *)(this + 712) + 4);
  return sub_41B0D0(*(uint32_t *)(this + 712) + 8);
}



// ------------------------------------------------------------
// 0x620B20 sub_620B20
// ------------------------------------------------------------
int /*thiscall*/ sub_620B20(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x620B50 sub_620B50
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_620B50(int a1)
{
  unsigned int i; // edx
  unsigned int result; // eax

  for ( i = 0; dword_9B9424 != 0; ++i )
  {
    result = (dword_9B9428 - dword_9B9424) >> 2;
    if ( i >= result )
      break;
    if ( *(uint32_t *)(dword_9B9424 + 4 * i) == a1 )
    {
      *(uint32_t *)(4 * i + dword_9B9424) = 0;
      memcpy_0(
        (void *)(dword_9B9424 + 4 * i),
        (const void *)(dword_9B9424 + 4 * i + 4),
        4 * ((int)(dword_9B9428 - (dword_9B9424 + 4 * i + 4)) >> 2));
      result = dword_9B9428 - 4;
      dword_9B9428 -= 4;
      return result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x620BC0 sub_620BC0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_620BC0(int *this)
{
  return sub_620B50(*(this + 244));
}



// ============================================================
// 【分区 2】铁笼/监狱（CNTrapCage，0x620BD0-0x620E40）
// 证据: JAIL_BREAK（笼碎切换）/ JAIL_CRASH（笼碎撞裂）+
//       PassiveObject/MapObject/Trap/Animation/CageBack.ani（笼背板动画）
// ============================================================

// ------------------------------------------------------------
// 0x620BD0 CNTrapCage__vmt12C
//   【铁笼】JAIL_BREAK —— 笼体破碎切换入口
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNTrapCage__vmt12C(uint32_t *this, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // edx
  unsigned int result; // eax

  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
  {
    v3 = *(this + 244);
    if ( v3 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v3 + 308))(v3) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 244) + 108))(
        *(this + 244),
        *(this + 245),
        *(this + 246),
        0);
    v4 = *(this + 247);
    if ( v4 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v4 + 84))(v4, 0);
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "JAIL_BREAK", -1, 0, 0);
  }
  if ( a2 == *(this + 247) )
    *(this + 247) = 0;
  if ( a2 == *(this + 244) )
  {
    v5 = *this;
    *(this + 244) = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v5 + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17);
  if ( (uint8_t)result != 0 )
    return sub_620B50(a2);
  return result;
}



// ------------------------------------------------------------
// 0x620CA0 sub_620CA0
//   【铁笼】JAIL_CRASH —— 笼碎撞裂音（笼破坏回调内触发）
// ------------------------------------------------------------
int /*thiscall*/ sub_620CA0(void *this, int a2)
{
  int v3; // eax
  int v4; // ecx
  int *v5; // eax
  uint64_t v6; // rax
  float v8; // [esp+0h] [ebp-1Ch]
  float v9; // [esp+4h] [ebp-18h]

  v3 = 0;
  switch ( *(uint32_t *)(dword_8F7A24 + 12) )
  {
    case 3:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);
      break;
    case 4:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);
      break;
    case 6:
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);
      break;
    default:
      break;
  }
  v4 = *(uint32_t *)(v3 + 112);
  v5 = *((int **)this + 87);
  v9 = (float)v5[1];
  v8 = (float)*v5;
  v6 = (uint64_t)sub_4049C0(v8, v9, v4 - 1, 98);
  HIDWORD(v6) = *(uint32_t *)this;
  *((uint32_t *)this + 170) = v6;
  *((uint32_t *)this + 171) = v6;
  (*(void (/*thiscall*/ **)(void *, int))(HIDWORD(v6) + 596))(this, 1);
  *((uint32_t *)this + 172) = 0;
  *((uint8_t *)this + 700) = 0;
  return sub_4015C0("JAIL_CRASH", 0xAu);
}



// ------------------------------------------------------------
// 0x620D60 CNTrapCage__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNTrapCage__vmt1F4(int *this, int a2, float *a3, char a4)
{
  uint32_t *v5; // edi
  int v6; // eax
  int v7; // ecx
  int *v8; // ecx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax

  v5 = (uint32_t *)a2;
  if ( *(this + 244) == 0
    && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 44))(a2) == 273
     || (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 44))(v5) == 529) )
  {
    *(this + 244) = (int)v5;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 120))(v5);
    v7 = *(this + 244);
    *(this + 245) = v6;
    *(this + 246) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
    a2 = *(this + 244);
    if ( a2 != 0 )
    {
      sub_620B50(a2);
      sub_428430(&dword_9B9420, &a2);
    }
    v8 = (int *)*(this + 244);
    v9 = *v8;
    v10 = (*(int (/*thiscall*/ **)(int *))(*v8 + 128))(v8);
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);
    v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11 - 1);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v9 + 108))(*(this + 244), v12);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 676))(this, 2);
  }
  return CNRDPassiveObject__vmt1F4(this, v5, a3, a4);
}



// ------------------------------------------------------------
// 0x620E40 CNTrapCage__vmt14C
//   【铁笼】tick：挂载 Trap/Animation/CageBack.ani 背板动画
// ------------------------------------------------------------
int /*thiscall*/ CNTrapCage__vmt14C(int *this)
{
  int v2; // eax
  int v3; // ebx
  char *v4; // eax
  char *v5; // edi
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // eax
  int v10; // eax
  int result; // eax
  int *v12; // eax
  int *v13; // ecx
  int v14; // ecx
  int v15; // edi
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // [esp-8h] [ebp-20h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) == 0 )
  {
    v2 = sub_42FCB0(228);
    v3 = 0;
    if ( v2 != 0 )
      v3 = sub_431860(v2, "PassiveObject/MapObject/Trap/Animation/CageBack.ani", 1);
    v4 = (char *)sub_44B6C0(284);
    v5 = v4;
    if ( v4 != nullptr )
    {
      sub_44E0D0(v4, v3, 0);
      *(uint32_t *)v5 = &vftbl_CNRDPooledObject;
      v6 = (int)v5;
    }
    else
    {
      v6 = 0;
    }
    v7 = *(this + 29);
    *(this + 247) = v6;
    sub_45FE80(v7, (int)v5, 2, 0, v6, 0, 0);
    v8 = *(uint32_t *)*(this + 247);
    v20 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) - 2;
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v9 - 2);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v8 + 112))(*(this + 247), v10);
    (*(void (/*thiscall*/ **)(uint32_t, int *))(*(uint32_t *)*(this + 247) + 60))(*(this + 247), this);
    sub_4A06D0(v20);
    *((uint8_t *)this + 972) = 1;
  }
  result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
  if ( result == 0 )
  {
    v12 = (int *)*(this + 244);
    v13 = this;
    if ( v12 == nullptr )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    goto LABEL_14;
  }
  v14 = *(this + 244);
  if ( v14 != 0 )
  {
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 128))(v14);
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    if ( v15 > result )
    {
      v12 = (int *)*(this + 244);
      v13 = this;
LABEL_14:
      v16 = *v12;
      v17 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(v13);
      v18 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v17);
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v18 - 1);
      return (*(int (/*thiscall*/ **)(uint32_t, int))(v16 + 112))(*(this + 244), v19);
    }
  }
  return result;
}



// ============================================================
// 【分区 3】吊灯（CNChandelier，0x620FE0-0x6214D0）
// 证据: SIZZLE_LOOP（燃烧滋滋循环）/ CHANDELIER_CUT（坠落切断）/ CHANDELIER_BROKEN（破碎切换）
// ============================================================

// ------------------------------------------------------------
// 0x620FE0 CNChandelier__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNChandelier__vmtC(int *this)
{
  CNRDPassiveObject__vmtC(this);
  return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);
}



// ------------------------------------------------------------
// 0x621000 sub_621000
// ------------------------------------------------------------
int /*thiscall*/ sub_621000(uint32_t *this)
{
  uint32_t *v2; // edi

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v2 = (uint32_t *)*(this + 28);
    if ( *v2 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v2 + 308))(*v2) != 0 && v2[9] != -1500 )
    {
      v2[9] = -1500;
      *((uint8_t *)v2 + 196) = 1;
      sub_494F60(2, -1);
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 596))(this, 1);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 200);
}



// ------------------------------------------------------------
// 0x621070 CNChandelier__vmt14C
//   【吊灯】SIZZLE_LOOP —— 燃烧滋滋循环音
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNChandelier__vmt14C(uint32_t *this)
{
  unsigned int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 993) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "SIZZLE_LOOP",
      10000,
      0,
      0);
    *((uint8_t *)this + 993) = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) == 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  result = *(this + 247);
  if ( result != 0 )
  {
    result = sub_699000((int)(this + 9));
    if ( result > *(this + 247) )
    {
      result = sub_621000(this);
      *(this + 247) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x621100 sub_621100
// ------------------------------------------------------------
void /*thiscall*/ sub_621100(int this)
{
  if ( *(uint32_t *)(this + 976) != 0 )
    j__free(*(void **)(this + 976));
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint32_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint8_t *)(this + 992) = 0;
}



// ------------------------------------------------------------
// 0x621140 sub_621140
// ------------------------------------------------------------
int /*thiscall*/ sub_621140(uint32_t *this, int a2)
{
  int v3; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(uint32_t *)(*(this + 36) + 4),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -200,
    *(uint32_t *)*(this + 36),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    100,
    *(uint32_t *)(*(this + 36) + 20),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    100,
    *(uint32_t *)(*(this + 36) + 24),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    100,
    *(uint32_t *)(*(this + 36) + 28),
    0,
    0,
    0,
    0);
  *(uint32_t *)(*(this + 28) + 36) = 0;
  v3 = *this;
  *(this + 172) = 0;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 372))(this, 200);
  *((uint8_t *)this + 992) = 0;
  *((uint8_t *)this + 993) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x621200 sub_621200
//   【吊灯】CHANDELIER_CUT —— 坠落切断触发
// ------------------------------------------------------------
int /*thiscall*/ sub_621200(uint32_t *this)
{
  int v2; // eax
  int v3; // edx

  v2 = sub_699000((int)(this + 9));
  v3 = *this;
  *(this + 247) = v2 + 700;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 208))(this, *(uint32_t *)(*(this + 36) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 20));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 24));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 28));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 12));
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -100,
    *(uint32_t *)(*(this + 36) + 8),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    -200,
    *(uint32_t *)(*(this + 36) + 16),
    0,
    0,
    0,
    0);
  *(uint8_t *)(*(uint32_t *)(*(this + 36) + 8) + 161) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
           this,
           "CHANDELIER_CUT",
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x621310 CNChandelier__vmt12C
//   【吊灯】CHANDELIER_BROKEN —— 吊灯破碎切换
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNChandelier__vmt12C(uint32_t *this, int a2)
{
  unsigned int result; // eax
  unsigned int i; // edi
  int v5; // ecx
  int v6; // ecx

  CNRDPassiveObject__vmt12C(this, a2);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 44))(a2);
  if ( result == 529 )
  {
    for ( i = 0; ; ++i )
    {
      v5 = *(this + 244);
      if ( v5 == 0 )
        break;
      result = (*(this + 245) - v5) >> 2;
      if ( i >= result )
        break;
      result = *(this + 244) + 4 * i;
      if ( a2 == *(uint32_t *)result )
      {
        *(uint32_t *)result = 0;
        memcpy_0(
          (void *)(4 * i + *(this + 244)),
          (const void *)(4 * i + *(this + 244) + 4),
          4 * ((int)(*(this + 245) - (4 * i + *(this + 244) + 4)) >> 2));
        *(this + 245) -= 4;
        v6 = *(this + 244);
        if ( v6 == 0 || (result = (*(this + 245) - v6) >> 2) == 0 )
          result = sub_621200(this);
      }
    }
  }
  if ( (uint32_t *)a2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10000);
    return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "CHANDELIER_BROKEN",
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6213F0 CNChandelier__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNChandelier__vmt200(int this, int a2, float *a3, char a4)
{
  int v5; // eax
  int v6; // ecx
  int v7; // edi

  v5 = CNRDPassiveObject__vmt200((int *)this, a2, a3, a4);
  v6 = *(uint32_t *)(this + 976);
  v7 = v5;
  if ( v6 == 0 || (*(uint32_t *)(this + 980) - v6) >> 2 == 0 )
    sub_621200((uint32_t *)this);
  *(uint8_t *)(this + 992) = 1;
  return v7;
}



// ------------------------------------------------------------
// 0x621440 sub_621440
// ------------------------------------------------------------
char /*thiscall*/ sub_621440(void *this, int a2)
{
  int v3; // ebx
  int v4; // ebx
  int v5; // edi
  int v7; // edi

  v3 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this) - 30;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) >= v3 )
  {
    v4 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this) + 70;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2) <= v4 )
    {
      if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 1 )
      {
        v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
        if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) < v5 )
          return 1;
      }
      else if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 0 )
      {
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
        if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) > v7 )
          return 1;
      }
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x6214D0 sub_6214D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6214D0(uint32_t *this, int a2, int a3)
{
  sub_4B1030(this);
  *this = &vftbl_CNWindSimulation;
  sub_6524C0(a2, a3);
  return this;
}



// ============================================================
// 【分区 4】风扇/旋涡（CNWindSimulation/CNWindShaker/CNSpiner，0x621530-0x622E10）
// 证据: FAN_ROTATE_LOOP + FAN_WIND_BLOW_LOOP（风扇双循环音）、IRON_HIT / SPINNER_ON /
//       SPINNER_LOOP / SPINNER_BREAK（旋涡）、Trap/Particle/SpinerMovePath.ptl +
//       SpinerBubble.ptl（旋涡移动路径与气泡粒子）
// ============================================================

// ------------------------------------------------------------
// 0x621530 CNWindSimulation__vmt4
// ------------------------------------------------------------
int /*thiscall*/ CNWindSimulation__vmt4(int *this)
{
  int result; // eax
  int v3; // eax

  IRDAppendage__vmt4(this);
  result = sub_699000((int)(this + 2));
  if ( result >= 30 )
  {
    v3 = sub_699000((int)(this + 2));
    return sub_652500(v3);
  }
  return result;
}



// ------------------------------------------------------------
// 0x621560 CNWindSimulation__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNWindSimulation__vmt0(void *Block, char a2)
{
  sub_621590();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x621590 sub_621590
// ------------------------------------------------------------
int /*thiscall*/ sub_621590(int this)
{
  int result; // eax

  *(uint32_t *)this = &vftbl_IRDAppendage;
  result = sub_5F6640((uint32_t *)this);
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;
  *(uint8_t *)(this + 12) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6215E0 sub_6215E0
// ------------------------------------------------------------
char /*thiscall*/ sub_6215E0(uint32_t *this, int a2)
{
  int v2; // esi
  unsigned int i; // edx

  v2 = *(this + 249);
  for ( i = 0; v2 != 0 && i < (*(this + 250) - v2) >> 2; ++i )
  {
    if ( *(uint32_t *)(*(this + 249) + 4 * i) == a2 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x621630 sub_621630
// ------------------------------------------------------------
int /*thiscall*/ sub_621630(int **this, int a2)
{
  int *v3; // eax
  int *v4; // eax
  int result; // eax

  ((void (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    4,
    (*(this + 36))[2],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    3,
    (*(this + 36))[3],
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(int **, int))(*this)[151])(this, 1);
  *(this + 247) = (int *)sub_699000((int)(this + 9));
  v3 = *(this + 87);
  *((uint8_t *)this + 984) = 0;
  *((uint8_t *)this + 973) = 1;
  *((uint8_t *)this + 972) = 1;
  v4 = (int *)*v3;
  *(this + 245) = v4;
  *(this + 244) = v4;
  *(this + 170) = (int *)999999999;
  *(this + 171) = (int *)999999999;
  ((void (/*thiscall*/ *)(int **, int))(*this)[93])(this, 100);
  if ( (*(this + 87))[3] != 0 )
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[15])(this);
    *(uint8_t *)(result + 52) = 0;
  }
  else
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[15])(this);
    *(uint8_t *)(result + 52) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x621EF0 CNWindShaker__vmt14C
//   【风扇】FAN_ROTATE_LOOP + FAN_WIND_BLOW_LOOP —— 旋转/吹风双循环音
// ------------------------------------------------------------
char /*thiscall*/ CNWindShaker__vmt14C(uint32_t *this)
{
  unsigned int v2; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) != 0 || (LOBYTE(v2) = *((uint8_t *)this + 973), (uint8_t)v2 != 0) )
  {
    v2 = sub_699000((int)(this + 9));
    if ( *(this + 247) + 250 < v2 )
    {
      *(this + 247) = sub_699000((int)(this + 9));
      LOBYTE(v2) = sub_621DC0(this);
      if ( (uint8_t)v2 != *((uint8_t *)this + 984) )
      {
        *((uint8_t *)this + 984) = v2;
        if ( (uint8_t)v2 != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t *))(*this + 204))(
            this,
            1,
            *(uint32_t *)*(this + 36),
            0,
            0,
            0,
            0,
            this);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
            this,
            100,
            *(uint32_t *)(*(this + 36) + 4),
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "FAN_ROTATE_LOOP",
            12345,
            0,
            0);
          LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
                         this,
                         "FAN_WIND_BLOW_LOOP",
                         12346,
                         0,
                         0);
        }
        else
        {
          LOBYTE(v2) = sub_621770(this);
        }
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x621F20 sub_621F20
// ------------------------------------------------------------
int /*thiscall*/ sub_621F20(uint32_t *this)
{
  *(this + 245) = 0;
  *(this + 246) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x621F30 sub_621F30
// ------------------------------------------------------------
int /*thiscall*/ sub_621F30(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 245);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 246);
  *(this + 245) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 246) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x621F70 CNSpiner__vmt12C
//   【旋涡】复用 CHANDELIER_BROKEN 作破碎音
// ------------------------------------------------------------
void /*thiscall*/ CNSpiner__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "CHANDELIER_BROKEN",
      -1,
      0,
      0);
}



// ------------------------------------------------------------
// 0x621FA0 CNSpiner__vmt2B4
//   【旋涡】IRON_HIT（受击铁音）/ SPINNER_BREAK（旋涡破碎）
// ------------------------------------------------------------
int /*thiscall*/ CNSpiner__vmt2B4(int *this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax

  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "IRON_HIT", -1, 0, 0);
  if ( *(this + 170) > 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 3, 0, 0, 0);
  }
  else
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(
             this,
             "SPINNER_BREAK",
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x622020 sub_622020
// ------------------------------------------------------------
int /*thiscall*/ sub_622020(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  const void *v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // esi
  int v9; // esi
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // [esp+4h] [ebp-70h] BYREF
  int v14; // [esp+8h] [ebp-6Ch] BYREF
  uint32_t v15[26]; // [esp+Ch] [ebp-68h] BYREF

  v15[25] = dword_796E50;
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
    if ( (uint8_t)result != 0 && *(this + 240) != 2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);
      sub_423A20((int)v15);
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);
      v4 = (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v3 + 104) + 16))(*(uint32_t *)(v3 + 104));
      v5 = *this;
      qmemcpy(v15, v4, 0x62u);
      *(uint32_t *)((char *)&v15[3] + 3) = 0;
      *(uint32_t *)((char *)&v15[4] + 3) = 0;
      v13 = (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 120))(this);
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
      v7 = *this;
      v14 = v6;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 128))(this);
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 136))(this, v13, v14, 0) != 0
        || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *, int, int, int, int, int))(*this + 140))(
                              this,
                              &v13,
                              &v14,
                              v13,
                              v14,
                              100,
                              1,
                              1)) != 0 )
      {
        v15[1] = v14;
        v15[0] = v13;
        v15[2] = v8;
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
        v9 = *(uint32_t *)dword_8F8520;
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
        (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
        v11 = *(uint32_t *)dword_8F8520;
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v15, 98);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
        return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6221A0 sub_6221A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6221A0(uint32_t *this, int a2)
{
  int result; // eax
  uint32_t *v4; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));
  if ( a2 == 2 )
  {
    v4 = (uint32_t *)(*(this + 36) + 8);
  }
  else if ( a2 == 3 )
  {
    v4 = (uint32_t *)(*(this + 36) + 12);
  }
  else
  {
    result = a2 - 4;
    if ( a2 != 4 )
      return result;
    v4 = (uint32_t *)(*(this + 36) + 16);
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *v4,
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x622230 CNSpiner__vmt1D8
//   【旋涡】SPINNER_ON（启动）/ SPINNER_LOOP（循环）
// ------------------------------------------------------------
int /*thiscall*/ CNSpiner__vmt1D8(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int result; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  uint32_t *v10; // eax
  int v11; // eax

  if ( *(this + 240) == 4 )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 14530);
  CNRDPassiveObject__vmt1D8(this, a2, a3, a2, a3, a4, a5);
  if ( a2 == 2 )
  {
    sub_4926A0(*(this + 34));
    v11 = *(this + 34);
    goto LABEL_18;
  }
  if ( a2 == 3 )
  {
    sub_4926A0(*(uint32_t *)*(this + 36));
    v11 = *(uint32_t *)*(this + 36);
LABEL_18:
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 196))(this, v11);
    goto LABEL_19;
  }
  result = a2 - 4;
  if ( a2 != 4 )
    return result;
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SPINNER_ON", -1, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SPINNER_LOOP", 14530, 0, 0);
  sub_4926A0(*(uint32_t *)(*(this + 36) + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
  v7 = **(uint32_t **)(a3 + 4);
  if ( v7 > 180 )
  {
    v8 = v7 - 225;
    if ( v8 == 0 )
      goto LABEL_13;
    v9 = v8 - 45;
    if ( v9 == 0 )
    {
LABEL_14:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));
      v10 = (uint32_t *)(*(this + 36) + 16);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
               this,
               100,
               *v10,
               0,
               0,
               0,
               0);
    }
    if ( v9 == 45 )
    {
LABEL_13:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));
      v10 = (uint32_t *)(*(this + 36) + 12);
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
               this,
               100,
               *v10,
               0,
               0,
               0,
               0);
    }
LABEL_19:
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));
  }
  if ( v7 != 180 )
  {
    switch ( v7 )
    {
      case 0:
        return sub_6221A0(this, 2);
      case 45:
      case 135:
        goto LABEL_13;
      case 90:
        goto LABEL_14;
      default:
        goto LABEL_19;
    }
  }
  return sub_6221A0(this, 2);
}



// ------------------------------------------------------------
// 0x6224F0 sub_6224F0
// ------------------------------------------------------------
bool /*thiscall*/ sub_6224F0(uint32_t *this)
{
  bool v1; // bl
  uint8_t v3[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  int v6; // [esp+14h] [ebp-10h]
  int v7; // [esp+20h] [ebp-4h]

  Block = nullptr;
  v5 = 0;
  v6 = 0;
  v7 = 0;
  v1 = sub_4E7F30(this, 200, 200, (int)v3) != 0;
  if ( Block != nullptr )
    j__free(Block);
  return v1;
}



// ------------------------------------------------------------
// 0x622560 sub_622560
// ------------------------------------------------------------
void /*usercall*/ sub_622560(int *a1@<ecx>, int a2@<edi>, int a3@<esi>)
{
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // edi
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // [esp+4h] [ebp-ACh]
  int v14; // [esp+8h] [ebp-A8h]
  int v15; // [esp+Ch] [ebp-A4h]
  int v16; // [esp+10h] [ebp-A0h]
  int v17; // [esp+14h] [ebp-9Ch]
  int v18; // [esp+18h] [ebp-98h]
  int v19; // [esp+1Ch] [ebp-94h]
  int v20; // [esp+20h] [ebp-90h]
  uint8_t v21[4]; // [esp+24h] [ebp-8Ch] BYREF
  void *Block; // [esp+28h] [ebp-88h]
  int v23; // [esp+2Ch] [ebp-84h]
  int v24; // [esp+30h] [ebp-80h]
  int v25; // [esp+34h] [ebp-7Ch] BYREF
  int v26; // [esp+38h] [ebp-78h] BYREF
  uint32_t v27[29]; // [esp+3Ch] [ebp-74h] BYREF

  v27[25] = dword_796E50;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 308))(a1) != 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 88))(a1) != 0 )
  {
    sub_432FA0();
    sub_423A20((int)v27);
    v4 = (*(int (/*thiscall*/ **)(int *, int, int))(*a1 + 60))(a1, a2, a3);
    qmemcpy(
      v27,
      (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + 104) + 16))(*(uint32_t *)(v4 + 104)),
      0x62u);
    v13 = 0;
    v14 = 45;
    v15 = 90;
    v16 = 135;
    v17 = 180;
    v18 = 225;
    v19 = 270;
    v20 = 315;
    v5 = (*(&v13 + rand() % 4) + v27[18] + 90) % 360;
    *(uint32_t *)((char *)&v27[3] + 3) = 100;
    *(uint32_t *)((char *)&v27[4] + 3) = 100;
    v27[18] = v5;
    v25 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1);
    v6 = (*(int (/*thiscall*/ **)(int *, int, int, int, int, int, int, int, int))(*a1 + 124))(
           a1,
           v13,
           v14,
           v15,
           v16,
           v17,
           v18,
           v19,
           v20);
    v7 = *a1;
    v26 = v6;
    v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 128))(a1);
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*a1 + 136))(a1, v25, v26, 0) != 0
      || (*(uint8_t (/*thiscall*/ **)(int *, int *, int *, int, int, int, int, int))(*a1 + 140))(
           a1,
           &v25,
           &v26,
           v25,
           v26,
           100,
           1,
           1) != 0 )
    {
      v27[1] = v26;
      v27[0] = v25;
      v27[2] = v8;
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);
      v9 = *(uint32_t *)dword_8F8520;
      v10 = (*(int (/*thiscall*/ **)(int *))(*a1 + 48))(a1);
      (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
      v11 = *(uint32_t *)dword_8F8520;
      v12 = (*(int (/*thiscall*/ **)(int *))(*a1 + 52))(a1);
      (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v27, 98);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
      Block = nullptr;
      v23 = 0;
      v24 = 0;
      v27[28] = 0;
      sub_431230((int)v21, &v27[18]);
      (*(void (/*thiscall*/ **)(int *, int, uint8_t *, uint32_t, uint32_t))(*a1 + 560))(a1, 4, v21, 0, 0);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x6227A0 CNSpiner__vmt214
// ------------------------------------------------------------
char /*userpurge*/ CNSpiner__vmt214@<al>(int *a1@<ecx>, int a2@<edi>, int a3, int a4, int a5)
{
  sub_622560(a1, a2, (int)a1);
  return CNRDPassiveObject__vmt214(a1, a3, a4, a5);
}



// ------------------------------------------------------------
// 0x6227D0 sub_6227D0
//   【旋涡】Trap/Particle/SpinerMovePath.ptl（移动路径）+ SpinerBubble.ptl（气泡）
// ------------------------------------------------------------
int /*thiscall*/ sub_6227D0(uint32_t *this, int a2)
{
  char *v3; // edi
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // eax
  uint32_t *v10; // eax
  uint32_t *v11; // esi
  char *v12; // eax
  const void *v13; // esi
  uint32_t *v14; // edi
  int v15; // edi
  int v16; // edi
  uint32_t *v17; // eax
  uint32_t *v18; // eax
  int v19; // eax
  double v20; // st7
  int v21; // edi
  int v22; // eax
  int v23; // eax
  uint32_t *v24; // eax
  uint32_t *v25; // eax
  int v26; // eax
  int v27; // edx
  int v28; // eax
  int v29; // esi
  int v30; // eax
  int v31; // eax
  int v33; // [esp+0h] [ebp-24h]
  float Block; // [esp+Ch] [ebp-18h]
  int (/*thiscall*/ ***v35)(uint32_t, int); // [esp+10h] [ebp-14h]
  char *v36; // [esp+14h] [ebp-10h]

  v3 = nullptr;
  *(uint32_t *)(*(this + 28) + 36) = 0;
  v4 = *this;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v5);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v6);
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 112))(this, v7);
  v8 = *this;
  *((uint8_t *)this + 700) = 0;
  *((uint8_t *)this + 701) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v8 + 372))(this, 100);
  v9 = *(uint32_t *)*(this + 87);
  *(this + 170) = v9;
  *(this + 171) = v9;
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int))(*this + 472))(this, 2, 0, 1, 1);
  *(this + 247) = sub_699000((int)(this + 9));
  *(this + 248) = sub_699000((int)(this + 9));
  *(this + 249) = sub_699000((int)(this + 9));
  v10 = operator new(0x12Cu);
  if ( v10 != nullptr )
  {
    v11 = sub_428F30(v10, (int)"PassiveObject/MapObject/Trap/Particle/SpinerMovePath.ptl", 0);
    v35 = (int (/*thiscall*/ ***)(uint32_t, int))v11;
  }
  else
  {
    v35 = nullptr;
    v11 = nullptr;
  }
  v12 = (char *)sub_445D00(156);
  if ( v12 != nullptr )
  {
    v3 = sub_445B90(v12);
    v36 = v3;
  }
  else
  {
    v36 = nullptr;
  }
  v13 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *))(*v11 + 28))(v11);
  qmemcpy((void *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v3 + 16))(v3), v13, 0x62u);
  v14 = (uint32_t *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v36 + 16))(v36);
  *v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v36 + 16))(v36) + 4) = v15;
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)v36 + 16))(v36) + 8) = v16;
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 60))(this, v36);
  sub_4A0B60(v33);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)v36 + 4))(v36, 0);
  v17 = operator new(0x12Cu);
  if ( v17 != nullptr )
    v18 = sub_428F30(v17, (int)"PassiveObject/MapObject/Trap/Particle/SpinerBubble.ptl", 0);
  else
    v18 = nullptr;
  *(this + 245) = v18;
  if ( v18 != nullptr )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) != 0 )
    {
      v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
      Block = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v19 + 192))(v19) * 0.5;
      v20 = (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + Block;
    }
    else
    {
      v20 = (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    }
    v21 = *(uint32_t *)*(this + 245);
    v22 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)v20);
    v23 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v22);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v21 + 40))(*(this + 245), v23);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 245) + 12))(*(this + 245), 0);
  }
  v24 = operator new(0x12Cu);
  if ( v24 != nullptr )
    v25 = sub_428F30(v24, (int)"PassiveObject/MapObject/BreakableObject/Particle/SeaGrassBubble.ptl", 0);
  else
    v25 = nullptr;
  *(this + 246) = v25;
  if ( v25 != nullptr )
  {
    v26 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    v27 = *this;
    if ( v26 != 0 )
    {
      v28 = (*(int (/*thiscall*/ **)(uint32_t *))(v27 + 684))(this);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v28 + 192))(v28);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(v27 + 128))(this);
    }
    v29 = *(uint32_t *)*(this + 246);
    v30 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);
    v31 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v30);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v29 + 40))(*(this + 246), v31);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 246) + 12))(*(this + 246), 0);
  }
  return (**v35)(v35, 1);
}


// ------------------------------------------------------------
// 0x622AE0 CNSpiner__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ sub_622AE0(int *this)
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  uint32_t *v7; // edi
  int *v8; // eax
  int v9; // edx
  int v10; // eax
  int *v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  void *v15; // ecx
  void *v16; // eax
  int v17; // eax
  int v18; // edx
  int *v19; // eax
  int v20; // ecx
  int v21; // eax
  int *v22; // eax
  int v23; // edi
  int v24; // eax
  int v25; // eax
  void *v26; // ecx
  void *v27[4]; // [esp+8h] [ebp-34h] BYREF
  void *v28[5]; // [esp+18h] [ebp-24h] BYREF
  int v29; // [esp+2Ch] [ebp-10h]
  int v30; // [esp+38h] [ebp-4h]

  sub_600890();
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < v2 )
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v4);
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
    (*(void (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v6);
    v7 = (uint32_t *)*(this + 28);
    if ( *v7 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v7 + 308))(*v7) != 0 && v7[9] != 0 )
    {
      v7[9] = 0;
      *((uint8_t *)v7 + 196) = 1;
      sub_494F60(2, -1);
    }
  }
  if ( *(this + 240) == 2 && *(this + 249) + 500 < (unsigned int)sub_699000((int)(this + 9)) )
  {
    *(this + 249) = sub_699000((int)(this + 9));
    if ( (uint8_t)sub_6224F0(this) == 0 )
    {
LABEL_20:
      v16 = (void *)*(this + 171);
      v29 = *(this + 170);
      v28[4] = v16;
      if ( (double)v29 / (double)(int)v16 <= 0.30000001 )
      {
        sub_622560(this);
        *(this + 248) = *(this + 249);
      }
      goto LABEL_22;
    }
    sub_622560(this);
    *(this + 248) = *(this + 249);
    v8 = nullptr;
    switch ( *(uint32_t *)(dword_8F7A24 + 12) )
    {
      case 3:
        v9 = *(uint32_t *)(dword_8F7A24 + 28);
        break;
      case 4:
        v9 = *(uint32_t *)(dword_8F7A24 + 32);
        break;
      case 6:
        v9 = *(uint32_t *)(dword_8F7A24 + 40);
        break;
      default:
LABEL_16:
        v10 = *v8;
        if ( v10 >= 15 && v10 <= 16 )
        {
          v11 = (int *)*(this + 246);
          if ( v11 != nullptr )
          {
            v12 = *v11;
            v13 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
            v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);
            (*(void (/*thiscall*/ **)(uint32_t, int))(v12 + 40))(*(this + 246), v14);
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 246) + 12))(*(this + 246), 0);
            (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 246) + 92))(*(this + 246), v28);
            v15 = (void *)*(this + 29);
            v30 = 0;
            sub_4600B0(v15, 2, 0, (int)v28);
            v30 = -1;
            sub_5E5260(v28);
          }
        }
        goto LABEL_20;
    }
    v8 = *(int **)(*(uint32_t *)(v9 + 16) + 108);
    goto LABEL_16;
  }
LABEL_22:
  if ( *(this + 240) == 4 && *(this + 248) + 5000 < (unsigned int)sub_699000((int)(this + 9)) )
    sub_622020(this);
  if ( *(this + 240) == 3
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) == 1
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    sub_622560(this);
    *(this + 248) = sub_699000((int)(this + 9));
  }
  if ( *(this + 247) + 750 < (unsigned int)sub_699000((int)(this + 9)) )
  {
    v17 = sub_699000((int)(this + 9));
    v18 = *this;
    *(this + 247) = v17;
    (*(void (/*thiscall*/ **)(int *))(v18 + 352))(this);
  }
  if ( *(this + 240) == 4 && *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 0 )
  {
    v19 = nullptr;
    switch ( *(uint32_t *)(dword_8F7A24 + 12) )
    {
      case 3:
        v20 = *(uint32_t *)(dword_8F7A24 + 28);
        break;
      case 4:
        v20 = *(uint32_t *)(dword_8F7A24 + 32);
        break;
      case 6:
        v20 = *(uint32_t *)(dword_8F7A24 + 40);
        break;
      default:
LABEL_40:
        v21 = *v19;
        if ( v21 >= 15 && v21 <= 16 )
        {
          v22 = (int *)*(this + 245);
          if ( v22 != nullptr )
          {
            v23 = *v22;
            v24 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);
            v25 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v24);
            (*(void (/*thiscall*/ **)(uint32_t, int))(v23 + 40))(*(this + 245), v25);
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 245) + 12))(*(this + 245), 0);
            (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 245) + 92))(*(this + 245), v27);
            v26 = (void *)*(this + 29);
            v30 = 1;
            sub_4600B0(v26, 2, 0, (int)v27);
            sub_5E5260(v27);
          }
        }
        return;
    }
    v19 = *(int **)(*(uint32_t *)(v20 + 16) + 108);
    goto LABEL_40;
  }
}


// ------------------------------------------------------------
// 0x622E10 sub_622E10
// ------------------------------------------------------------
int /*thiscall*/ sub_622E10(int *this)
{
  int result; // eax
  int v3; // edx
  int v4; // ebx
  uint32_t *v5; // eax
  int v6; // eax
  int v7; // edx
  int v8; // edi
  int v9; // eax
  int v10; // edx
  int v11; // eax
  int v12; // [esp-2Ch] [ebp-48h]
  int v13; // [esp-1Ch] [ebp-38h]
  int v14[4]; // [esp+4h] [ebp-18h]
  int v15; // [esp+14h] [ebp-8h]
  int v16; // [esp+18h] [ebp-4h]

  *(this + 279) = GetTickCount();
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();
    v3 = *this;
    v14[0] = 220;
    v14[1] = 220;
    v14[2] = 220;
    v14[3] = 221;
    v4 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v3 + 80))(this) + 132) + 108) + 112);
    v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
    *(this + 280) = sub_460230(v5);
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v7 = *this;
    v15 = v6;
    v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 124))(this) + 1;
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v10 = *this;
    v13 = *(this + 280);
    v16 = v9;
    v12 = (*(int (/*thiscall*/ **)(int *))(v10 + 152))(this);
    v11 = rand() % 4;
    IRDCollisionObject__vmt250(
      this,
      v4,
      (int)this,
      v14[v11],
      100,
      v4,
      v15,
      v8,
      v16,
      v12,
      0,
      nullptr,
      0,
      v13,
      0,
      0,
      0,
      0);
    result = *(this + 281) + 1;
    *(this + 281) = result;
  }
  return result;
}



// ============================================================
// 【分区 5】海底生态：鱼巢/爆炸油/幻觉花（0x622F00-0x6239E0）
// 物件: CNSpaceFishLair（太空鱼巢）/ CNExplosiveOil+CNOlreksExplosiveOil（爆炸油桶）/
//       CNHallucinationFlower（幻觉花）；油桶受击引爆链见 vmt2C4/vmt288
// ============================================================

// ------------------------------------------------------------
// 0x622F00 CNSpaceFishLair__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNSpaceFishLair__vmt14C(int *this)
{
  unsigned int TickCount; // eax
  int v3; // ecx

  LOBYTE(TickCount) = CNMapObject__vmt14C(this);
  v3 = *(this + 276);
  if ( (v3 == 0 || (TickCount = (*(this + 277) - v3) >> 2) < 2) && *(this + 281) < 5 )
  {
    TickCount = GetTickCount();
    if ( *(this + 279) + 7500 < TickCount )
      LOBYTE(TickCount) = sub_622E10(this);
  }
  return TickCount;
}



// ------------------------------------------------------------
// 0x622F50 CNSpaceFishLair__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNSpaceFishLair__vmt2F4(void **this, int a2)
{
  int result; // eax

  if ( *(this + 276) != nullptr )
    j__free(*(this + 276));
  *(this + 276) = nullptr;
  *(this + 277) = nullptr;
  *(this + 278) = nullptr;
  *(this + 280) = (void *)0xFFFF;
  *(this + 281) = nullptr;
  *(this + 279) = (void *)(GetTickCount() + 7500);
  result = (*((int (/*thiscall*/ **)(void **, int))*this + 93))(this, 100);
  *(this + 169) = (void *)1;
  return result;
}



// ------------------------------------------------------------
// 0x622FC0 CNSpaceFishLair__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNSpaceFishLair__vmt12C(uint32_t *this, int a2)
{
  int v3; // edx
  unsigned int i; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529) != 0 )
  {
    v3 = *(this + 276);
    for ( i = 0; v3 != 0 && i < (*(this + 277) - v3) >> 2; ++i )
    {
      if ( *(uint32_t *)(*(this + 276) + 4 * i) == a2 )
      {
        memcpy_0(
          (void *)(*(this + 276) + 4 * i),
          (const void *)(*(this + 276) + 4 * i + 4),
          4 * ((int)(*(this + 277) - (*(this + 276) + 4 * i + 4)) >> 2));
        *(this + 277) -= 4;
        return CNMapObject__vmt12C(this, a2);
      }
    }
  }
  return CNMapObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x623050 sub_623050
// ------------------------------------------------------------
int /*thiscall*/ sub_623050(int this, uint32_t *a2)
{
  int v2; // esi
  unsigned int v3; // edx
  uint32_t *v4; // eax
  int result; // eax

  v2 = *(uint32_t *)(this + 4);
  if ( v2 != 0 )
    v3 = (*(uint32_t *)(this + 8) - v2) >> 2;
  else
    v3 = 0;
  if ( v2 == 0 || v3 >= (*(uint32_t *)(this + 12) - v2) >> 2 )
    return sub_5CC5A0(*(void **)(this + 8), 1, (int)a2);
  v4 = *(uint32_t **)(this + 8);
  *v4 = *a2;
  result = (int)(v4 + 1);
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6230A0 CNSpaceFishLair__vmt128
// ------------------------------------------------------------
int /*thiscall*/ CNSpaceFishLair__vmt128(uint32_t *this, int a2)
{
  int v2; // esi
  int result; // eax

  v2 = a2;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v2 + 52))(v2);
    if ( result == *(this + 280) )
    {
      sub_4E7E40(v2);
      a2 = v2;
      return sub_623050((int)(this + 275), &a2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6230F0 CNExplosiveOil__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNExplosiveOil__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( a2 == *(this + 251) )
    *(this + 251) = 0;
}



// ------------------------------------------------------------
// 0x623120 CNExplosiveOil__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNExplosiveOil__vmt200(int this, int a2, float *a3, char a4)
{
  int v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  int v14; // ebx
  int v15; // edi
  int v16; // eax
  int v18; // [esp-1Ch] [ebp-3Ch]
  uint32_t v19[3]; // [esp+8h] [ebp-18h]
  uint32_t v20[3]; // [esp+14h] [ebp-Ch]
  int v21; // [esp+2Ch] [ebp+Ch]
  int i; // [esp+30h] [ebp+10h]

  v5 = CNRDPassiveObject__vmt200((int *)this, a2, a3, a4);
  v21 = v5;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 && *(uint8_t *)(this + 972) == 0 )
  {
    v6 = *(uint32_t *)(this + 1004);
    if ( v6 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 680))(this, v6);
      v7 = *(uint32_t *)this;
      v8 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 1004) + 376))(*(uint32_t *)(this + 1004));
      (*(void (/*thiscall*/ **)(int, int))(v7 + 372))(this, v8);
    }
    sub_432FA0();
    v9 = *(uint32_t *)(this + 988);
    v10 = *(uint32_t *)(this + 992);
    v11 = *(uint32_t *)(this + 996);
    v19[0] = 40002;
    v19[1] = 40003;
    v19[2] = 40006;
    v20[0] = v9;
    v20[1] = v10;
    v20[2] = v11;
    v12 = *(uint32_t *)(this + 980) + rand() % (*(uint32_t *)(this + 984) - 1);
    if ( v12 > 0 )
    {
      for ( i = v12; i != 0; --i )
      {
        v13 = rand();
        v14 = *(uint32_t *)this;
        v15 = v13 % 3;
        v18 = rand() % 60 - 30;
        v16 = rand();
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(v14 + 580))(
          this,
          v19[v15],
          v20[v15],
          0,
          0,
          v16 % 80 - 40,
          v18,
          0,
          4,
          0,
          0,
          0);
      }
      v5 = v21;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  *(uint8_t *)(this + 972) = 1;
  return v5;
}



// ------------------------------------------------------------
// 0x623270 CNExplosiveOil__vmt288
// ------------------------------------------------------------
int /*stdcall*/ CNExplosiveOil__vmt288(uint32_t *a1, int a2)
{
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 20) != 0 )
    return 3;
  *a1 = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6232A0 CNExplosiveOil__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNExplosiveOil__vmt14C(uint8_t *this)
{
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 973) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 708))(this);
    *(this + 973) = 1;
  }
  result = *(uint8_t *)(*((uint32_t *)this + 244) + 170);
  if ( result != 0 )
  {
    result = *(this + 264);
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6232F0 CNExplosiveOil__vmt148
// ------------------------------------------------------------
int /*thiscall*/ CNExplosiveOil__vmt148(int *this, int a2, int a3, int a4, float a5)
{
  int v5; // ecx
  int result; // eax

  v5 = *(this + 244);
  if ( v5 != 0 )
  {
    sub_4938F0(v5);
    return sub_491D00(dword_79C0B0, a3, a4, a5);
  }
  return result;
}



// ------------------------------------------------------------
// 0x623330 sub_623330
// ------------------------------------------------------------
int /*thiscall*/ sub_623330(int this)
{
  uint32_t *v1; // eax
  int result; // eax

  *(uint32_t *)(this + 1004) = 0;
  *(uint8_t *)(this + 972) = 0;
  *(uint8_t *)(this + 973) = 0;
  *(uint32_t *)(this + 976) = 0;
  v1 = *(uint32_t **)(this + 348);
  *(uint32_t *)(this + 1000) = -1;
  *(uint32_t *)(this + 980) = *v1;
  *(uint32_t *)(this + 984) = v1[1];
  *(uint32_t *)(this + 988) = v1[2];
  *(uint32_t *)(this + 992) = v1[3];
  result = v1[4];
  *(uint32_t *)(this + 996) = result;
  return result;
}



// ------------------------------------------------------------
// 0x623390 CNExplosiveOil__vmt2C4
// ------------------------------------------------------------
int /*thiscall*/ CNExplosiveOil__vmt2C4(char *this)
{
  int v2; // ebx
  const char *v3; // edi
  const char *v4; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 372))(this, 201);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 680))(this, 0);
  v2 = sub_42FCB0(228);
  if ( v2 != 0 )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      v3 = this + 364;
    else
      v3 = *((const char **)this + 91);
    v4 = (const char *)sub_41ACF0(*((uint32_t *)this + 178));
    result = sub_431920(v2, v3, v4, 1);
  }
  else
  {
    result = 0;
  }
  *((uint32_t *)this + 244) = result;
  return result;
}



// ------------------------------------------------------------
// 0x623430 CNOlreksExplosiveOil__vmt2C4
// ------------------------------------------------------------
int /*thiscall*/ CNOlreksExplosiveOil__vmt2C4(char *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edi
  const char *v6; // ebx
  const char *v7; // eax
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 684))(this);
  v3 = *(uint32_t *)this;
  *((uint32_t *)this + 251) = v2;
  v4 = (*(int (/*thiscall*/ **)(char *))(v3 + 684))(this);
  *((uint32_t *)this + 250) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 376))(v4);
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 372))(this, 201);
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 680))(this, 0);
  v5 = sub_42FCB0(228);
  if ( v5 != 0 )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )
      v6 = this + 364;
    else
      v6 = *((const char **)this + 91);
    v7 = (const char *)sub_41ACF0(*((uint32_t *)this + 178));
    result = sub_431920(v5, v6, v7, 1);
  }
  else
  {
    result = 0;
  }
  *((uint32_t *)this + 244) = result;
  return result;
}



// ------------------------------------------------------------
// 0x623500 sub_623500
// ------------------------------------------------------------
int /*thiscall*/ sub_623500(int this)
{
  *(uint32_t *)(this + 984) = 0;
  *(uint8_t *)(this + 976) = 0;
  *(uint32_t *)(this + 972) = 0;
  *(uint32_t *)(this + 980) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6239E0 CNHallucinationFlower__vmt14C
// ------------------------------------------------------------
char /*usercall*/ CNHallucinationFlower__vmt14C@<al>(int a1@<ecx>, int a2@<edi>)
{
  int v2; // edi
  int v3; // eax
  int v5; // eax

  CNRDPassiveObject__vmt14C(a1);
  if ( *(uint8_t *)(a1 + 988) == 0 )
  {
    if ( **(uint32_t **)(a1 + 348) != 0 )
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 148))(a1, 1);
    else
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 148))(a1, 0);
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 684))(a1) != 0 )
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)a1 + 472))(a1, 4, 0, 1, 1);
    else
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)a1 + 472))(a1, 2, 0, 1, 1);
    *(uint8_t *)(a1 + 988) = 1;
  }
  if ( *(uint32_t *)(a1 + 960) == 2 )
  {
    LOBYTE(v5) = sub_623730(a1);
  }
  else if ( *(uint32_t *)(a1 + 960) == 3 )
  {
    v5 = *(uint32_t *)(a1 + 984);
    if ( v5 != 0 )
    {
      LOBYTE(v5) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 308))(a1);
      if ( (uint8_t)v5 != 0 )
      {
        if ( *(uint8_t *)(a1 + 976) != 0 || *(uint32_t *)(*(uint32_t *)(a1 + 984) + 148) != 5 )
        {
          LOBYTE(v5) = *(uint8_t *)(*(uint32_t *)(a1 + 984) + 170);
          if ( (uint8_t)v5 != 0 )
            LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 2, 0, 0, 0);
        }
        else
        {
          *(uint8_t *)(a1 + 976) = 1;
          v2 = *(uint32_t *)a1;
          v3 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)a1 + 192))(a1, 4, 0, 0, 0, a2);
          LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, int, int))(v2 + 580))(
                         a1,
                         48021,
                         10,
                         0,
                         0,
                         70,
                         1,
                         v3);
        }
      }
    }
  }
  else
  {
    v5 = *(uint32_t *)(a1 + 960) - 4;
    if ( *(uint32_t *)(a1 + 960) == 4 )
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 200))(a1);
      if ( *(uint8_t *)(v5 + 170) != 0 )
        LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)a1 + 472))(a1, 2, 0, 1, 1);
    }
  }
  return v5;
}



// ============================================================
// 【分区 6】沼泽与跳跃限制（CNSwamp/CNMagmaSwamp/CNSlowAndLowJump，0x623AA0-0x624CD0）
// 证据: SWAMP_BUBBLE_LOOP（沼泽气泡循环）/ R_WALK_SWAMP_LOOP（沼地行走循环）；
//       SlowAndLowJump = 限制角色跳跃高度的沼面判定
// ============================================================

// ------------------------------------------------------------
// 0x623AA0 CNSwamp__vmt2F0
// ------------------------------------------------------------
bool /*stdcall*/ CNSwamp__vmt2F0(int a1)
{
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 40))(a1, 17) != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1) >= 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 436))(a1) == 0;
}



// ------------------------------------------------------------
// 0x623AE0 sub_623AE0
// ------------------------------------------------------------
int /*thiscall*/ sub_623AE0(uint8_t *this, int a2, int a3)
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 372))(this, 100);
  *(this + 1121) = 0;
  *(this + 1122) = 0;
  *((uint32_t *)this + 284) = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 7);
  result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 8);
  *((uint32_t *)this + 285) = result;
  return result;
}



// ------------------------------------------------------------
// 0x623B30 CNSlowAndLowJump__vmt20
// ------------------------------------------------------------
char /*thiscall*/ CNSlowAndLowJump__vmt20(uint32_t **this, char a2)
{
  char result; // al

  result = a2;
  if ( a2 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 1) + 216))(*(this + 1), 20881);
  return result;
}



// ------------------------------------------------------------
// 0x623B50 CNStarFishEggRequid__vmt2F4
// ------------------------------------------------------------
bool /*stdcall*/ CNStarFishEggRequid__vmt2F4(int a1)
{
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 40))(a1, 529) != 0
      && __RTDynamicCast(a1, 0, &IRDActiveObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0) != 0;
}



// ------------------------------------------------------------
// 0x623B90 CNMagmaSwamp__vmt2F4
// ------------------------------------------------------------
bool /*stdcall*/ CNMagmaSwamp__vmt2F4(int a1)
{
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 40))(a1, 529) != 0
      && __RTDynamicCast(a1, 0, &IRDActiveObject `RTTI Type Descriptor', &CNBurningHela `RTTI Type Descriptor', 0) != 0;
}



// ------------------------------------------------------------
// 0x623BD0 sub_623BD0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_623BD0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // ecx
  uint32_t *result; // eax

  v3 = a2;
  for ( result = a3; v3 != a1; result[2] = v3[2] )
  {
    v3 -= 3;
    result -= 3;
    *result = *v3;
    result[1] = v3[1];
  }
  return result;
}



// ------------------------------------------------------------
// 0x623C10 sub_623C10
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_623C10(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *v4; // ecx

  result = a2;
  if ( a2 != nullptr )
  {
    v4 = a2;
    result = a1;
    do
    {
      if ( result != nullptr )
      {
        *result = *a3;
        result[1] = a3[1];
        result[2] = a3[2];
      }
      result += 3;
      v4 = (uint32_t *)((char *)v4 - 1);
    }
    while ( v4 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x623C50 CNSwamp__vmt2F4
// ------------------------------------------------------------
bool /*stdcall*/ CNSwamp__vmt2F4(int a1)
{
  uint32_t *v1; // ecx
  uint32_t *v2; // eax
  bool v3; // zf

  v1 = *(uint32_t **)(a1 + 336);
  v2 = *(uint32_t **)(a1 + 332);
  v3 = v2 == v1;
  if ( v2 != v1 )
  {
    do
    {
      if ( *v2 == 21 )
        break;
      ++v2;
    }
    while ( v2 != v1 );
    v3 = v2 == v1;
  }
  return !v3;
}



// ------------------------------------------------------------
// 0x623C80 CNSlowAndLowJump__vmt4
//   【沼泽】R_WALK_SWAMP_LOOP —— 沼地行走循环音
// ------------------------------------------------------------
void /*thiscall*/ CNSlowAndLowJump__vmt4(int **this)
{
  int *v2; // edi
  int v3; // ebx
  int v4; // eax
  bool v5; // zf
  signed int v6; // eax
  int v7; // edi
  int v8; // eax
  uint32_t *v9; // ecx
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int *v13; // ecx
  int v14; // eax
  void *v15; // eax
  int v16; // [esp-Ch] [ebp-3Ch]
  void *v17[4]; // [esp+Ch] [ebp-24h] BYREF
  uint32_t *v18; // [esp+1Ch] [ebp-14h]
  bool v19; // [esp+23h] [ebp-Dh]
  int v20; // [esp+2Ch] [ebp-4h]

  CNChangeStatus__vmt4((int)this);
  if ( *(this + 33) != (int *)-1
    && (*(this + 9) == nullptr || (uint8_t)sub_4E4630(*(this + 1)) != 0)
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(this + 1) + 308))(*(this + 1)) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 1) + 776))(*(this + 1), *(this + 33)) == 0
    && (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 128))(*(this + 1)) == 0 )
  {
    v2 = *(this + 1);
    v3 = *v2;
    v4 = ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[16])(this, 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t))(v3 + 760))(
      v2,
      *(this + 33),
      1120403456,
      *(this + 34),
      *(uint32_t *)(v4 + 32));
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 184))(*(this + 1)) == 4
    && (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 188))(*(this + 1)) == 4 )
  {
    if ( *((uint8_t *)this + 124) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(this + 1) + 216))(*(this + 1), 20881);
      *((uint8_t *)this + 124) = 0;
    }
  }
  else
  {
    if ( *((uint8_t *)this + 124) == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(this + 1) + 212))(
        *(this + 1),
        "R_WALK_SWAMP_LOOP",
        20881,
        0,
        0);
      *((uint8_t *)this + 124) = 1;
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 200))(*(this + 1)) == 0 )
      goto LABEL_21;
    v6 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 200))(*(this + 1)) + 148) & 0x80000001;
    v5 = v6 == 0;
    if ( v6 < 0 )
      v5 = (((uint8_t)v6 - 1) | 0xFFFFFFFE) == -1;
    if ( v5 )
    {
LABEL_21:
      *((uint8_t *)this + 125) = 0;
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 128))(*(this + 1)) == 0 && *((uint8_t *)this + 125) == 0 )
    {
      v7 = dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 924))(*(this + 1))];
      v8 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 152))(*(this + 1));
      v9 = *(this + 1);
      v10 = *(uint32_t *)v7;
      v19 = v8 == 0;
      v11 = *v9;
      v18 = v9;
      v16 = (*(int (**)(void))(v11 + 124))() + 1;
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*v18 + 120))(v18);
      (*(void (/*thiscall*/ **)(int, int))(v10 + 40))(v7, v12);
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 28))(v7) + 84) = v19;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v7 + 12))(v7, 0);
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)v7 + 92))(v7, v17);
      v13 = *(this + 1);
      v14 = *v13;
      v20 = 0;
      v15 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v14 + 80))(v13, 2, 0, v17);
      sub_4600B0(v15, v16, 0, 2);
      *((uint8_t *)this + 125) = 1;
      sub_5E5260(v17);
    }
  }
}



// ------------------------------------------------------------
// 0x623EB0 sub_623EB0
// ------------------------------------------------------------
char /*cdecl*/ sub_623EB0(int a1)
{
  int *v1; // eax
  int v2; // ecx
  int v3; // esi
  int v5; // edx
  int *v6; // ecx
  int *v7; // edi
  int v8; // esi

  v1 = (int *)dword_9B9434;
  v2 = dword_9B9438;
  if ( dword_9B9434 == dword_9B9438 )
    return 0;
  while ( 1 )
  {
    v3 = *v1;
    v1 += 3;
    if ( v3 == a1 )
      break;
    if ( v1 == (int *)dword_9B9438 )
      return 0;
  }
  v5 = dword_9B9438;
  if ( v1 != (int *)dword_9B9438 )
  {
    v6 = v1 - 3;
    do
    {
      v7 = v6;
      *v6 = *v1;
      v6[1] = v1[1];
      v8 = v1[2];
      v1 += 3;
      v6 += 3;
      v7[2] = v8;
    }
    while ( v1 != (int *)v5 );
    v2 = dword_9B9438;
  }
  dword_9B9438 = v2 - 12;
  return 1;
}



// ------------------------------------------------------------
// 0x623F20 sub_623F20
// ------------------------------------------------------------
void /*noreturn*/ sub_623F20()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x623F90 sub_623F90
// ------------------------------------------------------------
int /*thiscall*/ sub_623F90(int *this, int a2, unsigned int a3, int *Block)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ebx
  int result; // eax
  unsigned int v9; // ecx
  int v11; // eax
  int v12; // eax
  unsigned int v13; // ecx
  int v14; // eax
  int v15; // ebx
  int v16; // eax
  unsigned int v17; // edi
  void *v18; // ecx
  int v20; // edi
  int v21; // [esp-18h] [ebp-40h]
  int v22; // [esp-Ch] [ebp-34h]
  unsigned int v23; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  int v27; // [esp+30h] [ebp+8h]
  int v28; // [esp+34h] [ebp+Ch]
  char *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  v7 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( v7 != 0 )
  {
    result = 715827883 * (*(this + 3) - v7);
    v9 = (*(this + 3) - v7) / 12;
  }
  else
  {
    v9 = 0;
  }
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v11 = (*(this + 2) - v7) / 12;
    else
      v11 = 0;
    if ( 357913941 - v11 < a3 )
      sub_623F20(this);
    if ( v7 != 0 )
      v12 = (*(this + 2) - v7) / 12;
    else
      v12 = 0;
    if ( v9 >= a3 + v12 )
    {
      v18 = (void *)*(this + 2);
      Blockb = v18;
      if ( ((int)v18 - a2) / 12 >= a3 )
      {
        v27 = (int)v18 - 12 * a3;
        *(this + 2) = sub_59EE30(v27, v18, v18);
        sub_504450(a2, v27, Blockb);
        return sub_5043B0(a2, a2 + 12 * a3, v25);
      }
      else
      {
        sub_59EE30(a2, v18, a2 + 12 * a3);
        v23 = a3 - (*(this + 2) - a2) / 12;
        v22 = *(this + 2);
        v26 = 2;
        sub_5E51C0(v22, v23, v25);
        v20 = 12 * a3 + *(this + 2);
        *(this + 2) = v20;
        return sub_5043B0(a2, v20 - 12 * a3, v25);
      }
    }
    else
    {
      if ( 357913941 - (v9 >> 1) >= v9 )
        v13 = (v9 >> 1) + v9;
      else
        v13 = 0;
      if ( v7 != 0 )
        v14 = (*(this + 2) - v7) / 12;
      else
        v14 = 0;
      if ( v13 < a3 + v14 )
        v13 = a3 + sub_4DA030(this);
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      v21 = *(this + 1);
      v26 = 0;
      v28 = sub_59EE30(v21, a2, Blocka);
      sub_623C10(v28, a3, v25);
      sub_59EE30(a2, *(this + 2), v28 + 12 * a3);
      v16 = *(this + 1);
      if ( v16 != 0 )
        v16 = (*(this + 2) - v16) / 12;
      v17 = v16 + a3;
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


// ------------------------------------------------------------
// 0x624240 sub_624240
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_624240(int *this, uint32_t *a2, int a3, int *Block)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 12 != 0 )
    v6 = (a3 - v5) / 12;
  else
    v6 = 0;
  sub_623F90(this, a3, 1u, Block);
  *a2 = *(this + 1) + 12 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x6242B0 CNSlowAndLowJump__vmt80
// ------------------------------------------------------------
bool /*thiscall*/ CNSlowAndLowJump__vmt80(uint32_t **this)
{
  return (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 128))(*(this + 1)) > 0;
}



// ------------------------------------------------------------
// 0x6242D0 CNSlowAndLowJump__vmt0
// ------------------------------------------------------------
void */*thiscall*/ CNSlowAndLowJump__vmt0(void *Block, char a2)
{
  sub_624300();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x624300 sub_624300
// ------------------------------------------------------------
int /*thiscall*/ sub_624300(uint32_t *this)
{
  *this = &vftbl_CNSlowAndLowJump;
  return sub_4B3D50();
}



// ------------------------------------------------------------
// 0x624310 sub_624310
// ------------------------------------------------------------
int /*thiscall*/ sub_624310(int *this, void *Block)
{
  int v3; // eax
  int result; // eax
  int *v5; // esi
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // [esp+8h] [ebp-24h] BYREF
  char v10; // [esp+Ch] [ebp-20h]
  float v11; // [esp+10h] [ebp-1Ch]
  int v12; // [esp+14h] [ebp-18h]
  char v13; // [esp+18h] [ebp-14h]
  float v14; // [esp+1Ch] [ebp-10h]
  int v15; // [esp+28h] [ebp-4h]

  v10 = 1;
  v13 = 1;
  v3 = *this;
  v9 = 8;
  v11 = -40.0;
  v12 = 6;
  v14 = -40.0;
  result = (*(int (/*thiscall*/ **)(int *, void *))(v3 + 756))(this, Block);
  if ( (uint8_t)result == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529) != 0 )
    {
      v11 = v11 * 0.5;
      v14 = v14 * 0.5;
    }
    v5 = (int *)operator new(0x8Cu);
    v15 = 0;
    if ( v5 != nullptr )
    {
      sub_5101B0(v5, (int)&v9, 2, 0, 0);
      *v5 = (int)&vftbl_CNSlowAndLowJump;
    }
    else
    {
      v5 = nullptr;
    }
    v6 = *v5;
    v15 = -1;
    (*(void (/*thiscall*/ **)(int *, void *, int *, uint32_t, uint32_t, int, int))(v6 + 56))(v5, Block, this, 0, 0, 55, -1);
    v7 = *(this + 285);
    v8 = v5[1];
    v5[33] = *(this + 284);
    v5[34] = v7;
    result = *(this + 276);
    *(uint32_t *)(v8 + 7088) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x624420 sub_624420
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_624420(int *this, int *Block)
{
  int v3; // edi
  unsigned int v4; // ecx
  uint32_t *v5; // edi
  uint32_t *result; // eax

  v3 = *(this + 1);
  if ( v3 != 0 )
    v4 = (*(this + 2) - v3) / 12;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(this + 3) - v3) / 12 )
    return sub_624240(this, &Block, *(this + 2), Block);
  v5 = (uint32_t *)*(this + 2);
  result = sub_623C10(v5, (uint32_t *)1, Block);
  *(this + 2) = (int)(v5 + 3);
  return result;
}



// ------------------------------------------------------------
// 0x6244A0 CNSwamp__vmt14C
//   【沼泽】SWAMP_BUBBLE_LOOP —— 沼泽气泡循环音
// ------------------------------------------------------------
int /*usercall*/ sub_6244A0@<eax>(int *a1@<ecx>, int a2@<edi>)
{
  int result; // eax
  int v4; // edi
  unsigned int i; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // edx
  unsigned int j; // esi
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // eax
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // edx
  uint32_t *v28; // edi
  unsigned int k; // esi
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // edx
  int v36; // ecx
  int v37; // eax
  int v38; // edx
  int v39; // eax
  int v40; // eax
  int v41; // edx
  int v42; // edi
  void **v43; // eax
  void *v44; // esi
  int v45; // eax
  uint32_t *v46; // eax
  int v47; // ecx
  unsigned int m; // esi
  int v49; // eax
  int v50; // ecx
  int v51; // eax
  int v52; // eax
  int v53; // ecx
  int v54; // ecx
  int v55; // eax
  int v56; // ecx
  int v57; // ecx
  int v58; // eax
  uint32_t *v59; // eax
  uint32_t v61[3]; // [esp+4h] [ebp-14h] BYREF
  unsigned int v62; // [esp+10h] [ebp-8h]
  void *Block; // [esp+14h] [ebp-4h]

  sub_60B6B0();
  if ( *((uint8_t *)a1 + 1100) == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*a1 + 212))(
               a1,
               "SWAMP_BUBBLE_LOOP",
               20880,
               0,
               0);
    *((uint8_t *)a1 + 1100) = 1;
    return result;
  }
  v4 = a1[283];
  result = sub_699000((int)(a1 + 277));
  if ( result >= v4 )
  {
    *((uint8_t *)a1 + 1121) = 0;
    *((uint8_t *)a1 + 1122) = 0;
    sub_698F90((int)(a1 + 277), 50, 0);
    for ( i = 0; ; ++i )
    {
      v6 = (*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1);
      v7 = *(uint32_t *)(v6 + 120);
      v8 = v6 + 116;
      if ( v7 != 0 )
        v9 = (*(uint32_t *)(v8 + 8) - v7) >> 2;
      else
        v9 = 0;
      if ( (int)i >= v9 )
        goto LABEL_25;
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 80))(a1, a2);
      v11 = *(uint32_t *)(v10 + 120);
      if ( v11 != 0 && i < (*(uint32_t *)(v10 + 124) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * i);
      else
        v12 = 0;
      a2 = 33;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 40))(v12) != 0 )
      {
        v13 = (*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1);
        v14 = *(uint32_t *)(v13 + 120);
        if ( v14 != 0 && i < (*(uint32_t *)(v13 + 124) - v14) >> 2 )
          v15 = *(uint32_t *)(v14 + 4 * i);
        else
          v15 = 0;
        if ( __RTDynamicCast(v15, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwamp `RTTI Type Descriptor', 0) != 0 )
          break;
      }
    }
    v16 = (*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1);
    v17 = *(uint32_t *)(v16 + 120);
    if ( v17 != 0 && i < (*(uint32_t *)(v16 + 124) - v17) >> 2 )
      result = *(uint32_t *)(v17 + 4 * i);
    else
      result = 0;
    if ( a1 == (int *)result )
    {
LABEL_25:
      for ( j = 0; ; j = v62 + 1 )
      {
LABEL_26:
        v19 = *a1;
        v62 = j;
        v20 = (*(int (/*thiscall*/ **)(int *))(v19 + 80))(a1);
        v21 = *(uint32_t *)(v20 + 120);
        v22 = v20 + 116;
        if ( v21 != 0 )
          result = (*(uint32_t *)(v22 + 8) - v21) >> 2;
        else
          result = 0;
        if ( (int)j >= result )
          return result;
        v23 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 80))(a1, a2);
        v24 = *(uint32_t *)(v23 + 120);
        if ( v24 != 0 && j < (*(uint32_t *)(v23 + 124) - v24) >> 2 )
          v25 = *(uint32_t *)(v24 + 4 * j);
        else
          v25 = 0;
        a2 = v25;
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*a1 + 752))(a1) == 0 )
          continue;
        v26 = (*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1);
        v27 = *(uint32_t *)(v26 + 120);
        if ( v27 != 0 && j < (*(uint32_t *)(v26 + 124) - v27) >> 2 )
          v28 = *(uint32_t **)(v27 + 4 * j);
        else
          v28 = nullptr;
        Block = v28;
        for ( k = 0; ; ++k )
        {
          v30 = (*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1);
          v31 = *(uint32_t *)(v30 + 120);
          v32 = v30 + 116;
          if ( v31 != 0 )
            v33 = (*(uint32_t *)(v32 + 8) - v31) >> 2;
          else
            v33 = 0;
          if ( (int)k >= v33 )
          {
            v46 = (uint32_t *)dword_9B9434;
            v47 = dword_9B9438;
            if ( dword_9B9434 != dword_9B9438 )
            {
              while ( (uint32_t *)*v46 != v28 )
              {
                v46 += 3;
                if ( v46 == (uint32_t *)dword_9B9438 )
                {
                  j = v62 + 1;
                  goto LABEL_26;
                }
              }
              if ( v28 != nullptr )
              {
                for ( m = 0; ; ++m )
                {
                  v49 = (*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 700))(v28);
                  v50 = *(uint32_t *)(v49 + 4);
                  v51 = v50 != 0 ? (*(uint32_t *)(v49 + 8) - v50) >> 2 : 0;
                  if ( (int)m >= v51 )
                    break;
                  v52 = (*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 700))(v28);
                  v53 = *(uint32_t *)(v52 + 4);
                  if ( v53 != 0 && m < (*(uint32_t *)(v52 + 8) - v53) >> 2 )
                    v54 = *(uint32_t *)(v53 + 4 * m);
                  else
                    v54 = 0;
                  if ( *(uint32_t **)(v54 + 4) == v28 )
                  {
                    v55 = (*(int (/*thiscall*/ **)(uint32_t *))(*v28 + 700))(v28);
                    v56 = *(uint32_t *)(v55 + 4);
                    if ( v56 != 0 && m < (*(uint32_t *)(v55 + 8) - v56) >> 2 )
                      v57 = *(uint32_t *)(v56 + 4 * m);
                    else
                      v57 = 0;
                    v58 = __RTDynamicCast(
                            v57,
                            0,
                            &IRDAppendage `RTTI Type Descriptor',
                            &CNSlowAndLowJump `RTTI Type Descriptor',
                            0);
                    if ( v58 != 0 )
                    {
                      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v58 + 76))(v58, 0);
                      break;
                    }
                  }
                }
                v47 = dword_9B9438;
              }
              v59 = (uint32_t *)dword_9B9434;
              if ( dword_9B9434 == v47 )
              {
LABEL_91:
                v59 = nullptr;
              }
              else
              {
                while ( (uint32_t *)*v59 != v28 )
                {
                  v59 += 3;
                  if ( v59 == (uint32_t *)v47 )
                    goto LABEL_91;
                }
              }
              v28[1772] = v59[2];
              sub_623EB0(v28);
            }
            goto LABEL_93;
          }
          v34 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 80))(a1, a2);
          v35 = *(uint32_t *)(v34 + 120);
          if ( v35 != 0 && k < (*(uint32_t *)(v34 + 124) - v35) >> 2 )
            v36 = *(uint32_t *)(v35 + 4 * k);
          else
            v36 = 0;
          a2 = 33;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v36 + 40))(v36) != 0 )
          {
            v37 = (*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1);
            v38 = *(uint32_t *)(v37 + 120);
            if ( v38 != 0 && k < (*(uint32_t *)(v37 + 124) - v38) >> 2 )
              v39 = *(uint32_t *)(v38 + 4 * k);
            else
              v39 = 0;
            if ( __RTDynamicCast(v39, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwamp `RTTI Type Descriptor', 0) != 0 )
              break;
          }
LABEL_60:
          ;
        }
        v40 = (*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1);
        v41 = *(uint32_t *)(v40 + 120);
        if ( v41 != 0 && k < (*(uint32_t *)(v40 + 124) - v41) >> 2 )
          v42 = *(uint32_t *)(v41 + 4 * k);
        else
          v42 = 0;
        if ( (uint8_t)sub_60A7D0(Block) == 0 )
          break;
        v43 = (void **)dword_9B9434;
        if ( dword_9B9434 == dword_9B9438 )
        {
LABEL_64:
          v44 = Block;
          v45 = *((uint32_t *)Block + 1772);
          v61[0] = Block;
          v61[1] = v42;
          v61[2] = v45;
          sub_624420(v61);
          sub_624310(v44);
          j = v62 + 1;
          goto LABEL_26;
        }
        while ( *v43 != Block )
        {
          v43 += 3;
          if ( v43 == (void **)dword_9B9438 )
            goto LABEL_64;
        }
LABEL_93:
        ;
      }
      v28 = Block;
      goto LABEL_60;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6248A0 sub_6248A0
// ------------------------------------------------------------
void /*thiscall*/ sub_6248A0(void *this)
{
  uint8_t *v1; // edx
  char *v2; // ebx
  int *v3; // edi
  int v4; // ecx
  uint32_t *v5; // esi
  unsigned int j; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ecx
  uint32_t *v15; // ecx
  uint8_t *v16; // eax
  uint32_t *v17; // eax
  uint32_t *v18; // eax
  unsigned int v19; // esi
  char v20[4]; // [esp+Ch] [ebp-28h] BYREF
  uint8_t *v21; // [esp+10h] [ebp-24h]
  char *v22; // [esp+14h] [ebp-20h]
  int v23; // [esp+18h] [ebp-1Ch]
  int v24; // [esp+1Ch] [ebp-18h] BYREF
  void *v25; // [esp+20h] [ebp-14h]
  int i; // [esp+24h] [ebp-10h]
  int v27; // [esp+30h] [ebp-4h]

  v1 = nullptr;
  v2 = nullptr;
  v25 = this;
  v21 = nullptr;
  v22 = nullptr;
  v23 = 0;
  v3 = (int *)dword_9B9434;
  v4 = dword_9B9438;
  v27 = 0;
  for ( i = dword_9B9434; v3 != (int *)v4; i = (int)v3 )
  {
    if ( (void *)v3[1] == v25 )
    {
      v5 = (uint32_t *)*v3;
      v24 = *v3;
      if ( v24 != 0 )
      {
        for ( j = 0; ; ++j )
        {
          v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 700))(v5);
          v8 = *(uint32_t *)(v7 + 4);
          v9 = v8 != 0 ? (*(uint32_t *)(v7 + 8) - v8) >> 2 : 0;
          if ( (int)j >= v9 )
            break;
          v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 700))(v5);
          v11 = *(uint32_t *)(v10 + 4);
          if ( v11 != 0 && j < (*(uint32_t *)(v10 + 8) - v11) >> 2 )
            v12 = *(uint32_t *)(v11 + 4 * j);
          else
            v12 = 0;
          if ( *(uint32_t **)(v12 + 4) == v5 )
          {
            v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 700))(v5);
            v14 = *(uint32_t *)(v13 + 4);
            if ( v14 != 0 && j < (*(uint32_t *)(v13 + 8) - v14) >> 2 )
              v15 = *(uint32_t **)(v14 + 4 * j);
            else
              v15 = nullptr;
            v16 = __RTDynamicCast(
                    v15,
                    0,
                    &IRDAppendage `RTTI Type Descriptor',
                    &CNSlowAndLowJump `RTTI Type Descriptor',
                    0);
            if ( v16 != nullptr )
            {
              (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)v16 + 76))(v16, 0);
              break;
            }
          }
        }
        v4 = dword_9B9438;
        v3 = (int *)i;
        v1 = v21;
      }
      v17 = (uint32_t *)dword_9B9434;
      if ( dword_9B9434 != v4 )
      {
        while ( (uint32_t *)*v17 != v5 )
        {
          v17 += 3;
          if ( v17 == (uint32_t *)v4 )
            goto LABEL_31;
        }
        v18 = (uint32_t *)dword_9B9434;
        if ( dword_9B9434 == v4 )
        {
LABEL_29:
          v18 = nullptr;
        }
        else
        {
          while ( (uint32_t *)*v18 != v5 )
          {
            v18 += 3;
            if ( v18 == (uint32_t *)v4 )
              goto LABEL_29;
          }
        }
        v5[1772] = v18[2];
      }
LABEL_31:
      if ( v1 != nullptr && (v2 - v1) >> 2 < (unsigned int)((v23 - (int)v1) >> 2) )
      {
        *(uint32_t *)v2 = v5;
        v2 += 4;
        v22 = v2;
      }
      else
      {
        sub_4E75F0((int)v20, (int)v2, 1u, &v24);
        v2 = v22;
        v3 = (int *)i;
        v1 = v21;
      }
      v4 = dword_9B9438;
    }
    v3 += 3;
  }
  v19 = 0;
  while ( v1 != nullptr )
  {
    if ( v19 >= (v2 - v1) >> 2 )
    {
      j__free(v1);
      return;
    }
    sub_623EB0(*(uint32_t *)&v1[4 * v19]);
    v1 = v21;
    ++v19;
  }
}


// ------------------------------------------------------------
// 0x624A80 CNStarFishEggRequid__vmt14C
// ------------------------------------------------------------
void /*usercall*/ CNStarFishEggRequid__vmt14C(uint32_t *a1@<ecx>, int a2@<edi>)
{
  uint32_t *v3; // edi
  uint32_t *v4; // edi

  CNSwamp__vmt14C((int)a1, a2);
  v3 = (uint32_t *)(a1[36] + 8);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) == *v3
    || *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 170) == 0 )
  {
    v4 = (uint32_t *)(a1[36] + 8);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) == *v4
      && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1) + 170) != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1) != 0
      && *((uint8_t *)a1 + 264) == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[36] + 8));
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 340))(a1) + 32) = 0;
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 340))(a1) + 36) = 0;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 216))(a1, 20880);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*a1 + 216))(a1, 20881);
    sub_6248A0(a1);
  }
}



// ------------------------------------------------------------
// 0x624B70 CNSwamp__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNSwamp__vmt12C(uint32_t *this, uint32_t *a2)
{
  uint32_t *v3; // eax
  unsigned int i; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // ecx

  CNMapObject__vmt12C(this, (int)a2);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) != 0 )
  {
    v3 = (uint32_t *)dword_9B9434;
    if ( dword_9B9434 != dword_9B9438 )
    {
      while ( (uint32_t *)*v3 != a2 )
      {
        v3 += 3;
        if ( v3 == (uint32_t *)dword_9B9438 )
          goto LABEL_33;
      }
      for ( i = 0; ; ++i )
      {
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 700))(a2);
        v6 = *(uint32_t *)(v5 + 4);
        v7 = v6 != 0 ? (*(uint32_t *)(v5 + 8) - v6) >> 2 : 0;
        if ( (int)i >= v7 )
          break;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 700))(a2);
        v9 = *(uint32_t *)(v8 + 4);
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        if ( *(uint32_t **)(v10 + 4) == a2 )
        {
          v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 700))(a2);
          v12 = *(uint32_t *)(v11 + 4);
          if ( v12 != 0 && i < (*(uint32_t *)(v11 + 8) - v12) >> 2 )
            v13 = *(uint32_t *)(v12 + 4 * i);
          else
            v13 = 0;
          v14 = __RTDynamicCast(
                  v13,
                  0,
                  &IRDAppendage `RTTI Type Descriptor',
                  &CNSlowAndLowJump `RTTI Type Descriptor',
                  0);
          if ( v14 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v14 + 76))(v14, 0);
            break;
          }
        }
      }
      v15 = (uint32_t *)dword_9B9434;
      v16 = (uint32_t *)dword_9B9434;
      if ( dword_9B9434 != dword_9B9438 )
      {
        while ( (uint32_t *)*v16 != a2 )
        {
          v16 += 3;
          if ( v16 == (uint32_t *)dword_9B9438 )
            goto LABEL_32;
        }
        if ( dword_9B9434 == dword_9B9438 )
        {
LABEL_30:
          v15 = nullptr;
        }
        else
        {
          while ( (uint32_t *)*v15 != a2 )
          {
            v15 += 3;
            if ( v15 == (uint32_t *)dword_9B9438 )
              goto LABEL_30;
          }
        }
        a2[1772] = v15[2];
      }
LABEL_32:
      sub_623EB0((int)a2);
    }
  }
LABEL_33:
  if ( a2 == this )
    sub_6248A0(this);
}



// ------------------------------------------------------------
// 0x624CC0 sub_624CC0
// ------------------------------------------------------------
int /*thiscall*/ sub_624CC0(void *this, int a2)
{
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 372))(this, 100);
}



// ------------------------------------------------------------
// 0x624CD0 sub_624CD0
// ------------------------------------------------------------
char /*cdecl*/ sub_624CD0(int a1)
{
  int *v1; // eax
  int v2; // ecx
  int v3; // esi
  int v5; // edx
  int *v6; // ecx

  v1 = (int *)dword_9B9444;
  v2 = dword_9B9448;
  if ( dword_9B9444 != dword_9B9448 )
  {
    while ( 1 )
    {
      v3 = *v1;
      v1 += 2;
      if ( v3 == a1 )
        break;
      if ( v1 == (int *)dword_9B9448 )
        return 1;
    }
    v5 = dword_9B9448;
    if ( v1 != (int *)dword_9B9448 )
    {
      v6 = v1 - 2;
      do
      {
        *v6 = *v1;
        v6[1] = v1[1];
        v1 += 2;
        v6 += 2;
      }
      while ( v1 != (int *)v5 );
      v2 = dword_9B9448;
    }
    dword_9B9448 = v2 - 8;
  }
  return 1;
}



// ============================================================
// 【分区 7】地刺（CNFloorNiddle，0x624D30-0x6251B0）
// 物件: 地板刺陷阱（伸缩刺）；含碰撞回调与周期驱动
// ============================================================

// ------------------------------------------------------------
// 0x624D30 CNFloorNiddle__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNFloorNiddle__vmt12C(uint32_t *this, int a2)
{
  char result; // al

  CNRDPassiveObject__vmt12C(this, a2);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17);
  if ( result != 0 )
    return sub_624CD0(a2);
  return result;
}



// ------------------------------------------------------------
// 0x624D60 sub_624D60
// ------------------------------------------------------------
void /*noreturn*/ sub_624D60()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x624DD0 sub_624DD0
// ------------------------------------------------------------
void /*thiscall*/ sub_624DD0(int this, uint32_t *a2, unsigned int a3, int a4)
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
      sub_624D60(this);
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
// 0x625020 sub_625020
// ------------------------------------------------------------
void /*thiscall*/ sub_625020(int this, int a2)
{
  int v3; // edx
  unsigned int v4; // ecx
  int v5; // edi

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) >> 3;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(this + 12) - v3) >> 3 )
  {
    v5 = *(uint32_t *)(this + 8);
    sub_63A7C0(v5, 1, a2);
    *(uint32_t *)(this + 8) = v5 + 8;
  }
  else
  {
    sub_624DD0(this, *(char **)(this + 8), 1u, a2);
  }
}



// ------------------------------------------------------------
// 0x625090 sub_625090
// ------------------------------------------------------------
char /*cdecl*/ sub_625090(int a1)
{
  uint32_t *v1; // eax
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v1 = (uint32_t *)dword_9B9444;
  if ( dword_9B9444 == dword_9B9448 )
  {
LABEL_4:
    v3[0] = a1;
    v3[1] = sub_699000(a1 + 36);
    sub_625020((int)&unk_9B9440, (int)v3);
    return 1;
  }
  else
  {
    while ( *v1 != a1 )
    {
      v1 += 2;
      if ( v1 == (uint32_t *)dword_9B9448 )
        goto LABEL_4;
    }
    return 0;
  }
}



// ------------------------------------------------------------
// 0x6250E0 sub_6250E0
// ------------------------------------------------------------
char /*cdecl*/ sub_6250E0(int a1)
{
  uint32_t *v1; // esi
  uint32_t v3[2]; // [esp+4h] [ebp-8h] BYREF

  v1 = (uint32_t *)dword_9B9444;
  if ( dword_9B9444 == dword_9B9448 )
  {
LABEL_4:
    v3[0] = a1;
    v3[1] = sub_699000(a1 + 36);
    sub_625020((int)&unk_9B9440, (int)v3);
    return 1;
  }
  else
  {
    while ( *v1 != a1 )
    {
      v1 += 2;
      if ( v1 == (uint32_t *)dword_9B9448 )
        goto LABEL_4;
    }
    if ( v1[1] + 3000 >= (unsigned int)sub_699000(a1 + 36) )
    {
      return 0;
    }
    else
    {
      v1[1] = sub_699000(a1 + 36);
      return 1;
    }
  }
}



// ------------------------------------------------------------
// 0x625160 CNFloorNiddle__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNFloorNiddle__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int v5; // edi

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) != 0 )
    sub_625090((int)a2);
  v5 = CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
  (*(void (/*thiscall*/ **)(int *))(*this + 352))(this);
  return v5;
}



// ------------------------------------------------------------
// 0x6251B0 CNFloorNiddle__vmt1E0
// ------------------------------------------------------------
char /*thiscall*/ CNFloorNiddle__vmt1E0(int *this, int *a2, int a3)
{
  char result; // al
  char v5; // bl

  result = (*(int (/*thiscall*/ **)(int *, int))(*a2 + 40))(a2, 17);
  if ( result != 0 )
  {
    v5 = IRDCollisionObject__vmt1E0(this, a2, a3);
    if ( v5 == 0 )
      return v5;
    result = sub_6250E0((int)a2);
    if ( result != 0 )
      return v5;
  }
  return result;
}



// ============================================================
// 【分区 8】哥布林掩体（CNGoblinBunker，0x625200-0x626220）
// 证据: BUNKER_HIT / BUNKER_BREAK / BUNKER_OPEN + GBN_FRIGHT（哥布林惊叫）+
//       Common/CommonEffect/Animation/Heal.ani（掩体内医疗治疗演出）；
//       0x6252D0 = 属性投掷粒子选择器（石/冰/火/弹四选一，双子箱 0x62B360 复用）
// ============================================================

// ------------------------------------------------------------
// 0x625200 CNGoblinBunker__vmt140
// ------------------------------------------------------------
char /*thiscall*/ CNGoblinBunker__vmt140(uint8_t *this)
{
  int v2; // eax
  uint64_t v3; // rax
  float v5; // [esp+8h] [ebp-1Ch]
  float v6; // [esp+Ch] [ebp-18h]
  int v7; // [esp+1Ch] [ebp-8h]
  int v8; // [esp+20h] [ebp-4h]

  if ( *(this + 276) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 656))(this);
    v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 7);
    v8 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 8);
    v2 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);
    v6 = (float)v8;
    v5 = (float)v7;
    v3 = (uint64_t)sub_4049C0(v5, v6, *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v2 + 132) + 108) + 92), 99);
    HIDWORD(v3) = *(uint32_t *)this;
    *((uint32_t *)this + 170) = v3;
    *((uint32_t *)this + 171) = v3;
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, int, int))(HIDWORD(v3) + 472))(this, 0, 0, 1, 1);
  }
  return CNRDPassiveObject__vmt140(this);
}



// ------------------------------------------------------------
// 0x6252A0 CNGoblinBunker__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNGoblinBunker__vmt12C(unsigned int *this, unsigned int *a2)
{
  if ( a2 == this && (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 308))(this) != 0 )
    sub_60ABE0(this);
  return CNMapObject__vmt12C(this, (int)a2);
}



// ------------------------------------------------------------
// 0x6252D0 sub_6252D0
//   【掩体辅助】属性投掷粒子四选一: Particle/FastThrowStone.ptl（石）/ IceMissile.ptl（冰）/
//             FireMissile.ptl（火）/ AimingBomb.ptl（弹）
// ------------------------------------------------------------
int /*userpurge*/ sub_6252D0@<eax>(uint32_t *a1@<ecx>, int a2@<esi>, int a3)
{
  int result; // eax
  int v5; // esi
  const void *v6; // esi
  int v7; // eax
  const void *v8; // esi
  int v9; // eax
  uint64_t v10; // rax
  int v11; // ecx
  const void *v12; // esi
  int v13; // eax
  int v14; // esi
  uint32_t v16[11]; // [esp+8h] [ebp-98h] BYREF
  int v17; // [esp+34h] [ebp-6Ch]
  uint32_t v18[26]; // [esp+38h] [ebp-68h] BYREF

  v18[25] = dword_796E50;
  result = a3;
  if ( a3 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
    if ( (uint8_t)result != 0 )
    {
      sub_432FA0();
      v16[4] = 1;
      v16[5] = 1;
      v16[6] = 1;
      memset(v16, 0, 16);
      v16[7] = 2;
      v16[8] = 2;
      v16[9] = 3;
      v5 = rand() % 10;
      sub_423A20(v18);
      result = v16[v5];
      switch ( result )
      {
        case 0:
          v6 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*a1 + 588))(
                               a1,
                               "Particle/FastThrowStone.ptl",
                               a2);
          v7 = *a1;
          qmemcpy(v18, v6, 0x62u);
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v7 + 164))(a1, a3, 0);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 580))(
                     a1,
                     1048,
                     0,
                     v18,
                     0,
                     0,
                     10,
                     50,
                     1,
                     0,
                     0);
          break;
        case 1:
          v8 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*a1 + 588))(
                               a1,
                               "Particle/IceMissile.ptl",
                               a2);
          v9 = *a1;
          qmemcpy(v18, v8, 0x62u);
          v10 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v9 + 164))(a1, a3, 0);
          v18[18] = v10;
          v11 = 1;
          if ( (int)v10 >= 90 && (int)v10 < 270 )
          {
            v11 = 0;
            v18[18] = 180 - v10;
          }
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 580))(
                     a1,
                     42001,
                     *(uint32_t *)(a1[87] + 36),
                     v18,
                     0,
                     0,
                     10,
                     50,
                     v11,
                     0,
                     0);
          break;
        case 2:
          v12 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*a1 + 588))(
                                a1,
                                "Particle/FireMissile.ptl",
                                a2);
          v13 = *a1;
          qmemcpy(v18, v12, 0x62u);
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v13 + 164))(a1, a3, 0);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 580))(
                     a1,
                     40001,
                     *(uint32_t *)(a1[87] + 40),
                     v18,
                     0,
                     0,
                     10,
                     50,
                     1,
                     0,
                     0);
          break;
        case 3:
          if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*a1 + 8))(a1, a3, 0, a2) >= 250 )
            v17 = 250;
          else
            v17 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*a1 + 8))(a1, a3, 0);
          qmemcpy(
            v18,
            (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*a1 + 588))(a1, "Particle/AimingBomb.ptl"),
            0x62u);
          v16[10] = 2 * *(uint32_t *)((char *)&v18[7] + 3);
          v14 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v18[7] + 3)) / (double)v18[17] * 1000.0);
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(*a1 + 164))(a1, a3, 0);
          BYTE1(v18[22]) = 3;
          *(uint32_t *)((char *)&v18[3] + 3) = 1000 * v17 / v14;
          *(uint32_t *)((char *)&v18[4] + 3) = *(uint32_t *)((char *)&v18[3] + 3);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 580))(
                     a1,
                     30021,
                     0,
                     v18,
                     0,
                     0,
                     10,
                     50,
                     1,
                     0,
                     0);
          break;
        default:
          return result;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x625580 sub_625580
// ------------------------------------------------------------
int /*thiscall*/ sub_625580(uint32_t *this)
{
  int i; // esi
  int result; // eax

  for ( i = 8; i < 72; i += 4 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(i + *(this + 36)));
    result = sub_4926A0(*(uint32_t *)(*(this + 36) + i));
  }
  return result;
}



// ------------------------------------------------------------
// 0x6255C0 sub_6255C0
// ------------------------------------------------------------
void /*thiscall*/ sub_6255C0(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  void *v5; // ecx
  uint8_t v6[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v8; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  sub_625580((uint32_t *)this);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 16));
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    100,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 40),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    100,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 56),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    100,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 64),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 1108) + 12))(*(uint32_t *)(this + 1108), 0);
  v2 = **(uint32_t **)(this + 1108);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 192))(this);
  v3 = (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 124))(
         this,
         (uint64_t)((double)v8 * 0.69999999) >> 32,
         (uint64_t)((double)v8 * 0.69999999));
  v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v3 + 2);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v2 + 40))(*(uint32_t *)(this + 1108), v4);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 1108) + 92))(*(uint32_t *)(this + 1108), v6);
  v5 = *(void **)(this + 116);
  v9 = 0;
  sub_4600B0(v5, 2, 0, (int)v6);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x6256F0 sub_6256F0
// ------------------------------------------------------------
int /*thiscall*/ sub_6256F0(int *this)
{
  int v2; // edx
  int v3; // eax
  uint32_t *v4; // eax

  sub_625580(this);
  v2 = *this;
  v3 = *(this + 36);
  if ( *((uint8_t *)this + 1100) == 1 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 20));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 44),
      0,
      0,
      0,
      0);
    v4 = (uint32_t *)(*(this + 36) + 60);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 12));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 32),
      0,
      0,
      0,
      0);
    v4 = (uint32_t *)(*(this + 36) + 52);
  }
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 100, *v4, 0, 0, 0, 0);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *(uint32_t *)(*(this + 36) + 68),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x6257C0 sub_6257C0
// ------------------------------------------------------------
int /*thiscall*/ sub_6257C0(int *this)
{
  int v2; // edx
  int v3; // eax
  uint32_t *v4; // eax

  sub_625580(this);
  v2 = *this;
  v3 = *(this + 36);
  if ( *((uint8_t *)this + 1100) == 1 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 16));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 40),
      0,
      0,
      0,
      0);
    v4 = (uint32_t *)(*(this + 36) + 56);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 8));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 28),
      0,
      0,
      0,
      0);
    v4 = (uint32_t *)(*(this + 36) + 48);
  }
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 100, *v4, 0, 0, 0, 0);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *(uint32_t *)(*(this + 36) + 64),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x625890 sub_625890
// ------------------------------------------------------------
int /*thiscall*/ sub_625890(int *this)
{
  int v2; // edx
  int v3; // eax
  uint32_t *v4; // eax

  sub_625580(this);
  v2 = *this;
  v3 = *(this + 36);
  if ( *((uint8_t *)this + 1100) == 1 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 16));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 36),
      0,
      0,
      0,
      0);
    v4 = (uint32_t *)(*(this + 36) + 56);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 8));
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 24),
      0,
      0,
      0,
      0);
    v4 = (uint32_t *)(*(this + 36) + 48);
  }
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 100, *v4, 0, 0, 0, 0);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *(uint32_t *)(*(this + 36) + 64),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x625960 CNGoblinBunker__vmt2B4
//   【掩体】BUNKER_HIT（受击）/ BUNKER_BREAK（破碎）/ GBN_FRIGHT（哥布林惊叫）
// ------------------------------------------------------------
int /*thiscall*/ CNGoblinBunker__vmt2B4(int this, int a2, int a3, int a4, int a5, int a6)
{
  int v7; // ecx
  int result; // eax

  (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "BUNKER_HIT", -1, 0, 0);
  v7 = *(uint32_t *)(this + 680);
  if ( v7 > 0 )
  {
    if ( *(uint8_t *)(this + 1100) == 0 && v7 < *(uint32_t *)(this + 684) / 2 )
    {
      sub_6255C0(this);
      *(uint8_t *)(this + 1100) = 1;
    }
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)result != 0 )
      result = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 3, 0, 0, 0);
  }
  else
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "BUNKER_BREAK",
      -1,
      0,
      0);
    result = *(uint32_t *)(this + 1080);
    if ( result != 0 )
    {
      result = (*(uint32_t *)(this + 1084) - result) / 12;
      if ( result != 0 )
        result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                   this,
                   "GBN_FRIGHT",
                   -1,
                   0,
                   0);
    }
  }
  if ( *(uint8_t *)(this + 1100) == 1 )
  {
    result = *(uint32_t *)(this + 684) / 2;
    if ( *(uint32_t *)(this + 680) >= result )
    {
      *(uint8_t *)(this + 1100) = 0;
      return sub_6257C0((int *)this);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x625A70 sub_625A70
// ------------------------------------------------------------
void /*thiscall*/ sub_625A70(uint32_t *this)
{
  int v2; // esi
  int v3; // eax
  int v4; // edx
  int v5; // esi
  bool v6; // bl
  unsigned int i; // esi
  uint8_t v8[4]; // [esp+8h] [ebp-30h] BYREF
  void *v9; // [esp+Ch] [ebp-2Ch]
  int v10; // [esp+10h] [ebp-28h]
  int v11; // [esp+14h] [ebp-24h]
  uint8_t v12[4]; // [esp+18h] [ebp-20h] BYREF
  void *Block; // [esp+1Ch] [ebp-1Ch]
  int v14; // [esp+20h] [ebp-18h]
  int v15; // [esp+24h] [ebp-14h]
  int v16; // [esp+28h] [ebp-10h] BYREF
  int v17; // [esp+34h] [ebp-4h]

  v2 = (int)(this + 9);
  if ( *(this + 276) + 1000 <= (unsigned int)sub_699000((int)(this + 9)) )
  {
    v3 = sub_699000(v2);
    v4 = *this;
    *(this + 276) = v3;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v4 + 308))(this) != 0 )
    {
      sub_432FA0();
      if ( rand() % 100 <= 30 )
      {
        v9 = nullptr;
        v10 = 0;
        v11 = 0;
        v17 = 0;
        v5 = sub_4E7F30(this, 250, 75, (int)v8);
        if ( v5 != 0 )
        {
          v6 = rand() % 100 > 10;
          Block = nullptr;
          v14 = 0;
          v15 = 0;
          LOBYTE(v17) = 1;
          if ( v6 )
          {
            v16 = 1;
            sub_431230((int)v12, &v16);
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 48))(v5);
            sub_431230((int)v12, &v16);
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 52))(v5);
            sub_431230((int)v12, &v16);
          }
          else
          {
            if ( v9 != nullptr )
              v16 = (v10 - (int)v9) >> 2;
            else
              v16 = 0;
            sub_431230((int)v12, &v16);
            for ( i = 0; v9 != nullptr && i < (v10 - (int)v9) >> 2; ++i )
            {
              v16 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v9 + i) + 48))(*((uint32_t *)v9 + i));
              sub_431230((int)v12, &v16);
              v16 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v9 + i) + 52))(*((uint32_t *)v9 + i));
              sub_431230((int)v12, &v16);
            }
          }
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 2, v12, 0, 0);
          if ( Block != nullptr )
            j__free(Block);
        }
        if ( v9 != nullptr )
          j__free(v9);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x625C40 CNGoblinBunker__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNGoblinBunker__vmt2E4(int this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // edx

  *(uint32_t *)(this + 676) = 1;
  *(uint32_t *)(this + 96) = 545;
  *(uint8_t *)(this + 1100) = 0;
  *(uint32_t *)(this + 1104) = sub_699000(this + 36);
  sub_6257C0((int *)this);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    200,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 72),
    0,
    0,
    0,
    0);
  if ( operator new(0x12Cu) != nullptr )
  {
    v2 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 672))(this) + 32) + 24;
    if ( *(uint32_t *)(this + 384) < 0x10u )
      v3 = this + 364;
    else
      v3 = *(uint32_t *)(this + 364);
    v4 = sub_41ACF0(v2);
    v5 = sub_4C3640(v3, v4, this);
  }
  else
  {
    v5 = 0;
  }
  *(uint32_t *)(this + 1108) = v5;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 372))(this, 100);
  if ( *(uint32_t *)(this + 1120) != 0 )
    j__free(*(void **)(this + 1120));
  *(uint32_t *)(this + 1120) = 0;
  *(uint32_t *)(this + 1124) = 0;
  *(uint32_t *)(this + 1128) = 0;
  v6 = *(uint32_t *)this;
  *(uint32_t *)(this + 1112) = 0;
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(v6 + 472))(this, 6, 0, 1, 1);
}



// ------------------------------------------------------------
// 0x625D70 CNGoblinBunker__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNGoblinBunker__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  char v4; // cl
  int i; // edi
  int v6; // eax

  v2 = *(this + 240);
  if ( v2 != 0 )
  {
    v3 = v2 - 2;
    if ( v3 != 0 )
    {
      if ( v3 == 1
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
        && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      }
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
           && ((v4 = *((uint8_t *)this + 1100)) == 1 && *(int *)(*(uint32_t *)(*(this + 36) + 36) + 148) >= 1
            || v4 == 0 && *(int *)(*(uint32_t *)(*(this + 36) + 24) + 148) >= 1) )
    {
      for ( i = 0; i < *(this + 278); ++i )
      {
        v6 = sub_45EBE0(
               (uint32_t *)*(this + 29),
               *(uint32_t *)(*(this + 280) + 8 * i),
               *(uint32_t *)(*(this + 280) + 8 * i + 4));
        sub_6252D0(this, (int)this, v6);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
    }
  }
  else
  {
    sub_625A70(this);
  }
}



// ------------------------------------------------------------
// 0x625E70 sub_625E70
//   【掩体】Common/CommonEffect/Animation/Heal.ani —— 掩体医疗治疗演出
// ------------------------------------------------------------
int /*thiscall*/ sub_625E70(int *this)
{
  int v2; // edi
  int v3; // edx
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  char *v9; // eax
  char *v10; // edi
  int v11; // edx
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v16; // [esp-8h] [ebp-34h]
  int v17; // [esp+0h] [ebp-2Ch]
  int v18; // [esp+4h] [ebp-28h]
  uint8_t v19[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v21; // [esp+14h] [ebp-18h]
  int v22; // [esp+18h] [ebp-14h]
  int v23; // [esp+1Ch] [ebp-10h]
  int v24; // [esp+28h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v23 = *(this + 171);
    v2 = (uint64_t)((double)v23 * 0.2);
    Block = nullptr;
    v21 = 0;
    v22 = 0;
    v3 = *this;
    v4 = *(this + 170);
    v24 = 0;
    v23 = (*(int (/*thiscall*/ **)(int *))(v3 + 192))(this);
    v5 = (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(*this + 124))(
           this,
           (uint64_t)((double)v23 * 0.75) >> 32,
           (uint64_t)((double)v23 * 0.75));
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
    v16 = v2 + v4;
    v7 = 0;
    sub_600920((int)v19, 0, v2, v16, v6, v17, v18);
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *))(*this + 560))(this, 1, v19);
    v24 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v21 = 0;
    v22 = 0;
  }
  else
  {
    v7 = 0;
  }
  v8 = sub_42FCB0(228);
  v23 = v8;
  v24 = 1;
  if ( v8 != 0 )
    v7 = sub_431860(v8, "Common/CommonEffect/Animation/Heal.ani", 1);
  v24 = -1;
  v9 = (char *)sub_44B6C0(284);
  v10 = v9;
  v23 = (int)v9;
  v24 = 2;
  if ( v9 != nullptr )
  {
    sub_44E0D0(v9, v7, 1);
    *(uint32_t *)v10 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v10 = nullptr;
  }
  v11 = *(uint32_t *)v10;
  v24 = -1;
  (*(void (/*thiscall*/ **)(char *, int))(v11 + 72))(v10, 2);
  sub_45FE80(*(this + 29), (int)v10, 2, 0, (int)v10, (int)this, 0);
  v12 = *(uint32_t *)v10;
  v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, 40);
  v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13 + 1);
  return (*(int (/*thiscall*/ **)(char *, int))(v12 + 112))(v10, v14);
}



// ------------------------------------------------------------
// 0x625FF0 CNGoblinBunker__vmt1D8
//   【掩体】BUNKER_OPEN —— 掩体开门
// ------------------------------------------------------------
int /*thiscall*/ CNGoblinBunker__vmt1D8(int this, int a2, int a3, int a4, int a5)
{
  int result; // eax
  int v7; // edi
  int v8; // ecx
  int v9; // eax

  result = CNRDPassiveObject__vmt1D8((uint32_t *)this, a2, a3, a2, a3, a4, a5);
  switch ( a2 )
  {
    case 0:
      result = sub_6257C0((int *)this);
      break;
    case 2:
      sub_625890((int *)this);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "BUNKER_OPEN",
        -1,
        0,
        0);
      sub_5E5260((void **)(this + 1116));
      *(uint32_t *)(this + 1112) = 0;
      result = **(uint32_t **)(a3 + 4);
      v7 = 0;
      for ( *(uint32_t *)(this + 1112) = result; v7 < result; ++v7 )
      {
        v8 = *(uint32_t *)(a3 + 4);
        v9 = *(uint32_t *)(v8 + 8 * v7 + 8);
        a5 = *(uint32_t *)(v8 + 8 * v7 + 4);
        a4 = v9;
        sub_431230(this + 1116, &a5);
        sub_431230(this + 1116, &a4);
        result = *(uint32_t *)(this + 1112);
      }
      break;
    case 3:
      result = sub_6256F0((int *)this);
      break;
    case 4:
      sub_625E70((int *)this);
      result = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x626100 sub_626100
// ------------------------------------------------------------
int /*thiscall*/ sub_626100(int this)
{
  int result; // eax
  int v3; // esi
  int v4; // eax
  int v5; // esi
  int v6; // eax
  uint32_t *v7; // ecx
  int v8; // ebx
  int v9; // [esp+4h] [ebp-8h]
  int v10; // [esp+8h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 988) + 308))(*(uint32_t *)(this + 988));
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();
    v3 = rand() % 2;
    v4 = rand() % 2;
    (*(void (/*thiscall*/ **)(uint32_t, bool, int))(**(uint32_t **)(this + 988) + 896))(
      *(uint32_t *)(this + 988),
      v3 == 0,
      3 - (v4 != 0));
    v5 = rand() % 500 + 250;
    v6 = rand();
    v7 = *(uint32_t **)(this + 988);
    v10 = v7[1655];
    v9 = v7[1653];
    v8 = v6 % 500 + 250;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*v7 + 876))(
      v7,
      0,
      v5 + v7[1652],
      v5 + v7[1654],
      0,
      -1000,
      1);
    result = (*(int (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, int, int))(**(uint32_t **)(this + 988) + 876))(
               *(uint32_t *)(this + 988),
               1,
               v8 + v9,
               v8 + v10,
               0,
               -1000,
               1);
  }
  *(uint32_t *)(this + 992) = *(uint32_t *)(this + 988);
  return result;
}



// ------------------------------------------------------------
// 0x626220 sub_626220
// ------------------------------------------------------------
int /*thiscall*/ sub_626220(uint32_t *this)
{
  int v1; // eax

  *(this + 247) = 0;
  *(this + 248) = 0;
  *((uint8_t *)this + 972) = 0;
  *((uint8_t *)this + 973) = 0;
  *(this + 249) = 0;
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  *((uint8_t *)this + 974) = 0;
  v1 = *(uint32_t *)*(this + 87);
  *(this + 170) = v1;
  *(this + 171) = v1;
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 200);
}



// ============================================================
// 【分区 9】植物系：绞藤/扭草踏台/海草（0x626280-0x627900）
// 证据: TWIST_AMB_LOOP / TWIST_SPIN（扭草踏台）、BURN_VINE（点燃）/ TIE_VINE（缠绕定身）/
//       WALK_VINE_LOOP（藤上行走）+ BreakableObject/Particle/SeaGrassBubble.ptl（海草气泡）
// ============================================================

// ------------------------------------------------------------
// 0x626280 CNTwistFootHold__vmt2B4
// ------------------------------------------------------------
char /*thiscall*/ CNTwistFootHold__vmt2B4(uint32_t *this, int a2, int a3, int a4, int a5, int a6)
{
  int v7; // eax
  int v8; // eax
  int v9; // edx

  v7 = *(this + 170);
  if ( v7 <= 0 )
  {
    LOBYTE(v7) = *((uint8_t *)this + 974);
    if ( (uint8_t)v7 == 0 )
    {
      v8 = *(this + 36);
      v9 = *this;
      *((uint8_t *)this + 974) = 1;
      (*(void (/*stdcall*/ **)(uint32_t))(v9 + 196))(*(uint32_t *)(v8 + 24));
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
      LOBYTE(v7) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);
    }
  }
  return v7;
}



// ------------------------------------------------------------
// 0x6262D0 sub_6262D0
// ------------------------------------------------------------
int /*thiscall*/ sub_6262D0(uint32_t *this, int a2)
{
  int v3; // edi
  int v4; // eax
  int v5; // edx
  int v6; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int *v10; // edi
  int v11; // ebx
  uint64_t v12; // rax
  int *v13; // edi
  int v14; // ebx
  uint64_t v15; // rax
  int *v16; // edi
  int v17; // ebx
  uint64_t v18; // rax
  int *v19; // edi
  int v20; // ebx
  uint64_t v21; // rax
  int *v22; // edi
  int v23; // ebx
  uint64_t v24; // rax
  int v25; // edi
  int *v26; // esi
  int v27; // ebx
  uint64_t v28; // rax
  uint32_t *v30; // [esp+Ch] [ebp-4h]
  uint32_t *v31; // [esp+Ch] [ebp-4h]
  uint32_t *v32; // [esp+Ch] [ebp-4h]
  uint32_t *v33; // [esp+Ch] [ebp-4h]
  uint32_t *v34; // [esp+Ch] [ebp-4h]

  v3 = (int)(this + 9);
  *(this + 247) = a2;
  *(this + 244) = sub_699000((int)(this + 9));
  v4 = sub_699000(v3);
  v5 = *this;
  *(this + 245) = v4;
  *((uint8_t *)this + 972) = 1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v5 + 596))(this, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);
  v6 = *(uint32_t *)*(this + 247);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
  v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v6 + 112))(*(this + 247), v9);
  v10 = (int *)*(this + 247);
  v11 = *v10;
  v30 = (uint32_t *)*(this + 36);
  v12 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v10 + 192))(v10, 0, 0) * -0.69999999);
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v11 + 204))(
    v10,
    HIDWORD(v12),
    -9999,
    *v30,
    0,
    v12);
  v13 = (int *)*(this + 247);
  v14 = *v13;
  v31 = (uint32_t *)(*(this + 36) + 4);
  v15 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v13 + 192))(v13, 0, 0) * -0.69999999);
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v14 + 204))(
    v13,
    HIDWORD(v15),
    9999,
    *v31,
    0,
    v15);
  v16 = (int *)*(this + 247);
  v17 = *v16;
  v32 = (uint32_t *)(*(this + 36) + 8);
  v18 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v16 + 192))(v16, 0, 0) * -0.40000001);
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v17 + 204))(
    v16,
    HIDWORD(v18),
    -9999,
    *v32,
    0,
    v18);
  v19 = (int *)*(this + 247);
  v20 = *v19;
  v33 = (uint32_t *)(*(this + 36) + 12);
  v21 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v19 + 192))(v19, 0, 0) * -0.40000001);
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v20 + 204))(
    v19,
    HIDWORD(v21),
    9999,
    *v33,
    0,
    v21);
  v22 = (int *)*(this + 247);
  v23 = *v22;
  v34 = (uint32_t *)(*(this + 36) + 16);
  v24 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v22 + 192))(v22, 0, 0) * -0.1);
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v23 + 204))(
    v22,
    HIDWORD(v24),
    -9999,
    *v34,
    0,
    v24);
  v25 = *(this + 36);
  v26 = (int *)*(this + 247);
  v27 = *v26;
  v28 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*v26 + 192))(v26, 0, 0) * -0.1);
  return (*(int (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v27 + 204))(
           v26,
           HIDWORD(v28),
           9999,
           *(uint32_t *)(v25 + 20),
           0,
           v28);
}


// ------------------------------------------------------------
// 0x626500 sub_626500
// ------------------------------------------------------------
int /*thiscall*/ sub_626500(uint32_t *this)
{
  bool v2; // cc
  int v3; // edx

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 24));
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(*(this + 247), *(uint32_t *)*(this + 36));
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(
    *(this + 247),
    *(uint32_t *)(*(this + 36) + 4));
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(
    *(this + 247),
    *(uint32_t *)(*(this + 36) + 8));
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(
    *(this + 247),
    *(uint32_t *)(*(this + 36) + 12));
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(
    *(this + 247),
    *(uint32_t *)(*(this + 36) + 16));
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(
    *(this + 247),
    *(uint32_t *)(*(this + 36) + 20));
  *(this + 247) = 0;
  *(this + 244) = 0;
  *(this + 246) = sub_699000((int)(this + 9));
  v2 = *(this + 249) < 5;
  *(this + 245) = 0;
  *((uint8_t *)this + 972) = 0;
  if ( v2 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 604))(this, 1);
  v3 = *this;
  *((uint8_t *)this + 974) = 1;
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 604))(this, 0);
}



// ------------------------------------------------------------
// 0x626610 IRDCollisionObject__vmt168
// ------------------------------------------------------------
int /*thiscall*/ IRDCollisionObject__vmt168(uint32_t *this, int a2)
{
  int *v3; // esi
  int v4; // edi
  int v5; // eax
  uint8_t v7[4]; // [esp+4h] [ebp-4h] BYREF

  if ( (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 380))(this) == this )
  {
    a2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 380))(a2);
    return *(uint32_t *)sub_4BE520(v7, &a2) != *(this + 136);
  }
  else
  {
    v3 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 380))(this);
    v4 = *v3;
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 380))(a2);
    return (*(int (/*thiscall*/ **)(int *, int))(v4 + 360))(v3, v5);
  }
}



// ------------------------------------------------------------
// 0x626690 CNTwistFootHold__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNTwistFootHold__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( *(this + 247) == a2 )
    sub_626500(this);
  if ( *(this + 248) == a2 )
    *(this + 248) = 0;
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 7810);
}



// ------------------------------------------------------------
// 0x6266E0 CNTwistFootHold__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNTwistFootHold__vmt1F4(uint32_t *this, int a2, int a3, int a4)
{
  if ( *(this + 247) != 0 )
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17) != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 724))(a2) == 0
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 840))(a2) != 9
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 840))(a2) != 4 )
  {
    ++*(this + 249);
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)a2 + 472))(a2, 9, 0, 1, 1);
    sub_6262D0(this, a2);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x626770 CNTwistFootHold__vmt14C
//   【扭草踏台】TWIST_AMB_LOOP（环境循环）/ TWIST_SPIN（旋转）
// ------------------------------------------------------------
char /*thiscall*/ CNTwistFootHold__vmt14C(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int *v6; // ecx
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  unsigned int v11; // eax
  int v12; // ecx
  int v13; // eax
  uint32_t *v14; // edi

  CNRDPassiveObject__vmt14C(this);
  if ( *(uint8_t *)(this + 973) == 0 )
  {
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "TWIST_AMB_LOOP",
      7810,
      0,
      0);
    *(uint8_t *)(this + 973) = 1;
  }
  if ( *(uint8_t *)(this + 972) == 0 )
    goto LABEL_12;
  v2 = **(uint32_t **)(this + 988);
  v3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
  v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v3);
  v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v4);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v2 + 112))(*(uint32_t *)(this + 988), v5);
  if ( *(uint32_t *)(this + 980) + 100 < (unsigned int)sub_699000(this + 36) )
  {
    v6 = *(int **)(this + 988);
    v7 = *v6;
    v8 = (*(int (/*thiscall*/ **)(int *))(*v6 + 152))(v6);
    (*(void (/*thiscall*/ **)(uint32_t, bool))(v7 + 148))(*(uint32_t *)(this + 988), v8 == 0);
    v9 = sub_699000(this + 36);
    v10 = *(uint32_t *)(this + 988);
    *(uint32_t *)(this + 980) = v9;
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 152))(v10) == 0 )
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "TWIST_SPIN",
        -1,
        0,
        0);
  }
  if ( ((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 988) + 840))(*(uint32_t *)(this + 988)) == 9
     || *(uint32_t *)(this + 992) != 0)
    && (*(uint32_t *)(this + 976) + 2000 >= (unsigned int)sub_699000(this + 36) || *(uint32_t *)(this + 992) != 0) )
  {
LABEL_12:
    v12 = *(uint32_t *)(this + 992);
    if ( v12 != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v12 + 184))(v12) == 4
      && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 992) + 188))(*(uint32_t *)(this + 992)) == 4 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 992) + 308))(*(uint32_t *)(this + 992)) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 992) + 724))(*(uint32_t *)(this + 992)) == 0
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 992) + 840))(*(uint32_t *)(this + 992)) == 9 )
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 992) + 560))(
          *(uint32_t *)(this + 992),
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int, uint32_t))(**(uint32_t **)(this + 992) + 760))(
          *(uint32_t *)(this + 992),
          15,
          1106247680,
          10,
          this,
          0);
      }
      v13 = *(uint32_t *)this;
      *(uint32_t *)(this + 992) = 0;
      (*(void (/*thiscall*/ **)(int))(v13 + 352))(this);
    }
    v14 = (uint32_t *)(*(uint32_t *)(this + 144) + 24);
    v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
    if ( v11 == *v14 )
    {
      LOBYTE(v11) = *(uint8_t *)(this + 974);
      if ( (uint8_t)v11 == 0 )
      {
        v11 = sub_699000(this + 36);
        if ( *(uint32_t *)(this + 984) + 5000 < v11 )
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(this + 136));
          LOBYTE(v11) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 596))(this, 1);
        }
      }
    }
  }
  else
  {
    sub_626100(this);
    LOBYTE(v11) = sub_626500((uint32_t *)this);
  }
  return v11;
}



// ------------------------------------------------------------
// 0x6269A0 sub_6269A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6269A0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 244);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 245);
  *(this + 244) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  *(this + 245) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x6269E0 CNSeaGrass__vmt288
// ------------------------------------------------------------
int /*stdcall*/ CNSeaGrass__vmt288(uint32_t *a1, int a2)
{
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2) + 128) == 0 )
    return 3;
  *a1 = 100;
  return 0;
}



// ------------------------------------------------------------
// 0x626A20 CNSeaGrass__vmt200
// ------------------------------------------------------------
int /*userpurge*/ sub_626A20@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int a4, int a5, int a6)
{
  int v8; // eax
  uint32_t *v9; // edi
  uint8_t *v10; // eax
  uint8_t *v11; // eax
  int v12; // edx
  int *v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  void *v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edi
  const CHAR *v24; // eax
  int v25; // eax
  int v26; // eax
  double v27; // st7
  int v28; // edi
  int v29; // eax
  int v30; // eax
  void *v31; // ecx
  int v32; // [esp+Ch] [ebp-48h]
  uint8_t v33[4]; // [esp+20h] [ebp-34h] BYREF
  void *Block; // [esp+24h] [ebp-30h]
  uint8_t v35[4]; // [esp+30h] [ebp-24h] BYREF
  void *v36; // [esp+34h] [ebp-20h]
  int v37; // [esp+38h] [ebp-1Ch]
  int v38; // [esp+3Ch] [ebp-18h]
  void *v39; // [esp+40h] [ebp-14h]
  int v40; // [esp+44h] [ebp-10h]
  int v41; // [esp+50h] [ebp-4h]

  if ( a1[243] == 3 )
    return sub_600AF0(a4, a5, a6);
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)a4 + 40))(a4, 529, a3, a2) != 0
    && (v8 = __RTDynamicCast(
               a4,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &CNSpaceFishHead `RTTI Type Descriptor',
               0),
        v9 = (uint32_t *)v8,
        v8 != 0) )
  {
    v40 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v8 + 740))(v8) * 0.25);
    v10 = operator new(0x80u);
    v39 = v10;
    v41 = 0;
    if ( v10 != nullptr )
    {
      *(float *)&v32 = (float)v40;
      v11 = sub_4D6810(v10, v32, 250, 1, 1);
    }
    else
    {
      v11 = nullptr;
    }
    v12 = *(uint32_t *)v11;
    v41 = -1;
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v12 + 56))(
      v11,
      v9,
      a1,
      0,
      0,
      0,
      -1);
    nullsub_3();
    sub_4DB130(v9, 24, 0);
  }
  else
  {
    v13 = (int *)a1[244];
    if ( v13 != nullptr )
    {
      v14 = *v13;
      v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 124))(a1, 60);
      v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v15);
      (*(void (/*thiscall*/ **)(uint32_t, int))(v14 + 40))(a1[244], v16);
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)a1[244] + 12))(a1[244], 0);
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)a1[244] + 92))(a1[244], v33);
      v17 = (void *)a1[29];
      v41 = 1;
      sub_4600B0(v17, 2, 0, (int)v33);
      v41 = -1;
      if ( Block != nullptr )
        j__free(Block);
    }
  }
  v18 = a1[243];
  v19 = a1[36];
  a1[243] = v18 + 1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(v19 + 4 * v18));
  v20 = a1[243];
  v21 = *a1;
  if ( v20 == 3 )
  {
    v22 = a1[36];
    a1[24] = 33;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v21 + 208))(a1, *(uint32_t *)(v22 + 20));
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v21 + 208))(a1, *(uint32_t *)(a1[36] + 4 * v20 + 8));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*a1 + 204))(
      a1,
      100,
      *(uint32_t *)(a1[36] + 4 * (a1[243] + 3)),
      0,
      0,
      0,
      0);
  }
  v23 = *a1;
  v24 = sub_41ACF0((unsigned int **)(a1[178] + 4));
  (*(void (/*thiscall*/ **)(uint32_t *, const CHAR *, int))(v23 + 212))(a1, v24, -1);
  if ( a1[245] != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*a1 + 684))(a1, 0, 0) != 0 )
    {
      v25 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 684))(a1);
      v40 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v25 + 192))(v25);
      v26 = *a1;
      *(float *)&v39 = (double)v40 * 0.5;
      v40 = (*(int (/*thiscall*/ **)(uint32_t *))(v26 + 128))(a1);
      v27 = (double)v40 + *(float *)&v39;
    }
    else
    {
      *(float *)&v39 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 128))(a1));
      v27 = (double)(int)v39;
    }
    v28 = *(uint32_t *)a1[245];
    v29 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 124))(a1, (uint64_t)v27);
    v30 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*a1 + 120))(a1, v29);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v28 + 40))(a1[245], v30);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)a1[245] + 12))(a1[245], 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)a1[245] + 92))(a1[245], v35);
    v31 = (void *)a1[29];
    v41 = 2;
    sub_4600B0(v31, 2, 0, (int)v35);
    v41 = -1;
    if ( v36 != nullptr )
      j__free(v36);
    v36 = nullptr;
    v37 = 0;
    v38 = 0;
  }
  return sub_600AF0(a4, a5, a6);
}


// ------------------------------------------------------------
// 0x626D30 sub_626D30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_626D30(int *this)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // eax
  uint32_t *v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  uint32_t *v9; // eax
  uint32_t *result; // eax
  int v11; // eax
  double v12; // st7
  int *v13; // edi
  int v14; // ebx
  int v15; // eax
  int v16; // eax
  float Block; // [esp+Ch] [ebp-14h]

  *(this + 24) = 545;
  *(this + 243) = 0;
  if ( operator new(0x12Cu) != nullptr )
  {
    v2 = *(this + 178);
    if ( (unsigned int)*(this + 96) < 0x10 )
    {
      v6 = sub_41ACF0(v2);
      v5 = (uint32_t *)sub_4C3640(this + 91, v6, this);
    }
    else
    {
      v3 = *(this + 91);
      v4 = sub_41ACF0(v2);
      v5 = (uint32_t *)sub_4C3640(v3, v4, this);
    }
  }
  else
  {
    v5 = nullptr;
  }
  v7 = *(this + 36);
  v8 = *this;
  *(this + 244) = (int)v5;
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v8 + 204))(
    this,
    100,
    *(uint32_t *)(v7 + 4 * (*(this + 243) + 3)),
    0,
    0,
    0,
    0);
  v9 = operator new(0x12Cu);
  if ( v9 != nullptr )
    result = sub_428F30(v9, (int)"PassiveObject/MapObject/BreakableObject/Particle/SeaGrassBubble.ptl", 0);
  else
    result = nullptr;
  *(this + 245) = (int)result;
  if ( result != nullptr )
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 684))(this) != 0 )
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);
      Block = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 192))(v11) * 0.5;
      v12 = (double)(*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + Block;
    }
    else
    {
      v12 = (double)(*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    }
    v13 = (int *)*(this + 245);
    v14 = *v13;
    v15 = (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(*this + 124))(
            this,
            (uint64_t)v12 >> 32,
            (uint64_t)v12);
    v16 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v15);
    (*(void (/*thiscall*/ **)(int *, int))(v14 + 40))(v13, v16);
    return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 245) + 12))(*(this + 245), 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x626EC0 CNEntangleVineTrigger__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNEntangleVineTrigger__vmtC(int this)
{
  int v2; // eax
  int v3; // edx

  CNRDPassiveObject__vmtC((int *)this);
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this);
  v3 = *(uint32_t *)this;
  if ( v2 != 0 )
  {
    *(uint8_t *)(this + 1008) = 0;
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(v3 + 472))(this, 2, 0, 1);
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 372))(this, 200);
  }
  else
  {
    *(uint8_t *)(this + 1008) = 1;
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(v3 + 472))(this, 3, 0, 1);
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 372))(this, 100);
  }
}



// ------------------------------------------------------------
// 0x626F20 sub_626F20
// ------------------------------------------------------------
char /*thiscall*/ sub_626F20(int this)
{
  int v1; // ecx

  *(uint32_t *)(this + 976) = **(uint32_t **)(this + 348);
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 1008) = 0;
  v1 = this + 980;
  *(uint8_t *)(v1 + 13) = 0;
  *(uint8_t *)(v1 + 14) = 0;
  return sub_698F90(v1, 0, 0);
}



// ------------------------------------------------------------
// 0x626F50 CNEntangleVineTrigger__vmt200
//   【绞藤】BURN_VINE —— 藤蔓点燃触发
// ------------------------------------------------------------
int /*thiscall*/ CNEntangleVineTrigger__vmt200(int *this, int a2, float *a3, char a4)
{
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BURN_VINE", -1, 0, 0);
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 && *((uint8_t *)this + 264) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
      this,
      40006,
      *(uint32_t *)(*(this + 87) + 4),
      0,
      0,
      0,
      0,
      0,
      4,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return CNRDPassiveObject__vmt200(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x626FE0 CNEntangleVineTrigger__vmt1D8
// ------------------------------------------------------------
int /*userpurge*/ CNEntangleVineTrigger__vmt1D8@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3, int a4, int a5, int a6)
{
  int result; // eax
  int v8; // edi
  int v9; // eax

  CNRDPassiveObject__vmt1D8(a1, a2, a3, a3, a4, a5, a6);
  if ( a3 == 2 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)a1[36]);
  if ( a3 == 3 )
  {
    v8 = *a1;
    v9 = (*(int (/*thiscall*/ **)(int *))(*a1 + 96))(a1);
    return (*(int (/*thiscall*/ **)(int *, int))(v8 + 196))(a1, v9);
  }
  else
  {
    result = a3 - 4;
    if ( a3 == 4 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[36] + 4));
  }
  return result;
}



// ------------------------------------------------------------
// 0x627060 sub_627060
// ------------------------------------------------------------
char /*thiscall*/ sub_627060(uint32_t *this, int a2)
{
  int v3; // edx
  unsigned int i; // ecx

  v3 = *(this + 254);
  for ( i = 0; v3 != 0 && i < (*(this + 255) - v3) >> 2; ++i )
  {
    if ( a2 == *(uint32_t *)(*(this + 254) + 4 * i) )
    {
      memcpy_0(
        (void *)(*(this + 254) + 4 * i),
        (const void *)(*(this + 254) + 4 * i + 4),
        4 * ((int)(*(this + 255) - (*(this + 254) + 4 * i + 4)) >> 2));
      *(this + 255) -= 4;
      return 1;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x6270E0 CNEntangleVineTrigger__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNEntangleVineTrigger__vmt12C(uint32_t *this, int a2)
{
  char result; // al

  CNRDPassiveObject__vmt12C(this, a2);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 17);
  if ( result != 0 )
  {
    result = sub_627060(this, a2);
    if ( result != 0 )
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 216))(a2, 10000);
  }
  return result;
}



// ------------------------------------------------------------
// 0x627120 CNEntangleVine__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNEntangleVine__vmt14C(uint32_t *this)
{
  int v2; // ecx
  int v3; // edi
  uint32_t *v4; // edi
  unsigned int v5; // eax
  int v6; // ecx
  unsigned int i; // ebx
  int v8; // ecx
  int v9; // edi
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *(this + 246);
  if ( v2 != 0 && (*(this + 247) - v2) >> 2 != 0 )
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0 )
LABEL_7:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
  }
  else
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
    if ( v3 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 96))(this)
      && *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 4 )
    {
      goto LABEL_7;
    }
  }
  v4 = (uint32_t *)*(this + 36);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) == *v4
    && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    LOBYTE(v5) = *((uint8_t *)this + 264);
    if ( (uint8_t)v5 != 0 )
      return v5;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
  }
  LOBYTE(v5) = *((uint8_t *)this + 264);
  if ( (uint8_t)v5 == 0 )
  {
    v6 = *(this + 246);
    if ( v6 != 0 )
    {
      v5 = (*(this + 247) - v6) >> 2;
      if ( v5 != 0 )
      {
        for ( i = 0; ; ++i )
        {
          v8 = *(this + 246);
          if ( v8 == 0 )
            break;
          v5 = (*(this + 247) - v8) >> 2;
          if ( i >= v5 )
            break;
          v9 = 4 * i;
          LOBYTE(v5) = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(4 * i + v8) + 776))(
                         *(uint32_t *)(4 * i + v8),
                         16);
          if ( (uint8_t)v5 == 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t *))(**(uint32_t **)(v9 + *(this + 246)) + 768))(
              *(uint32_t *)(v9 + *(this + 246)),
              16,
              40,
              this);
            v10 = *(uint32_t *)(v9 + *(this + 246));
            v11 = *(uint32_t *)(v10 + 312);
            v12 = v10 + 288;
            if ( v11 < 0x10 )
              v13 = v12 + 4;
            else
              v13 = *(uint32_t *)(v12 + 4);
            LOBYTE(v5) = off_77F3FC((char *)&byte_73DA88, v13);
          }
        }
      }
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x6272B0 CNEntangleVine__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNEntangleVine__vmt12C(uint32_t *this, int a2)
{
  int v2; // ebx
  unsigned int v4; // edx
  int v5; // ecx
  int v6; // edi
  bool v7; // zf
  int v8; // eax
  int v9; // eax
  int v10; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  unsigned int v15; // ecx
  int v16; // eax
  int v17; // eax
  uint32_t *v18; // edi
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  uint32_t *v22; // edx
  unsigned int i; // [esp+Ch] [ebp-4h]

  v2 = a2;
  if ( (uint32_t *)a2 == this )
  {
    v4 = 0;
    for ( i = 0; ; v4 = i )
    {
      v5 = *(this + 246);
      if ( v5 == 0 || v4 >= (*(this + 247) - v5) >> 2 )
        break;
      v6 = 4 * v4;
      v7 = (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(4 * v4 + v5) + 776))(
             *(uint32_t *)(4 * v4 + v5),
             16) == 0;
      v8 = *(this + 246);
      if ( v7 )
      {
        v14 = *(uint32_t *)(v6 + v8);
        v15 = *(uint32_t *)(v14 + 312);
        v16 = v14 + 288;
        if ( v15 < 0x10 )
          v17 = v16 + 4;
        else
          v17 = *(uint32_t *)(v16 + 4);
        off_77F3FC((char *)&byte_73DAA0, v17);
      }
      else
      {
        v9 = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v6 + v8) + 772))(*(uint32_t *)(v6 + v8), 16);
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t *))(*(uint32_t *)v9 + 4))(v9, 0, this);
        v10 = *(uint32_t *)(v6 + *(this + 246));
        v11 = *(uint32_t *)(v10 + 312);
        v12 = v10 + 288;
        if ( v11 < 0x10 )
          v13 = v12 + 4;
        else
          v13 = *(uint32_t *)(v12 + 4);
        off_77F3FC(byte_73DAC0, v13);
      }
      ++i;
    }
    v2 = a2;
    goto LABEL_28;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) == a2 )
  {
    v18 = (uint32_t *)*(this + 36);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) != *v18 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));
      CNRDPassiveObject__vmt12C(this, a2);
      return;
    }
    goto LABEL_28;
  }
  v19 = *(this + 246);
  if ( v19 != 0 )
    v20 = (*(this + 247) - v19) >> 2;
  else
    v20 = 0;
  v21 = 0;
  if ( v20 <= 0 )
  {
LABEL_28:
    CNRDPassiveObject__vmt12C(this, v2);
    return;
  }
  v22 = (uint32_t *)*(this + 246);
  while ( a2 != *v22 )
  {
    ++v21;
    ++v22;
    if ( v21 >= v20 )
      goto LABEL_28;
  }
  memcpy_0(
    (void *)(*(this + 246) + 4 * v21),
    (const void *)(*(this + 246) + 4 * v21 + 4),
    4 * ((*(this + 247) - (*(this + 246) + 4 * v21 + 4)) >> 2));
  *(this + 247) -= 4;
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x627480 sub_627480
// ------------------------------------------------------------
char /*thiscall*/ sub_627480(uint32_t *this, int a2)
{
  int v3; // esi
  uint32_t *v4; // ecx
  unsigned int i; // edx
  int v7; // esi
  unsigned int v8; // edx
  int *v9; // eax

  v3 = *(this + 254);
  v4 = this + 253;
  for ( i = 0; v3 != 0 && i < (v4[2] - v3) >> 2; ++i )
  {
    if ( a2 == *(uint32_t *)(*(this + 254) + 4 * i) )
      return 0;
  }
  v7 = v4[1];
  if ( v7 != 0 )
    v8 = (v4[2] - v7) >> 2;
  else
    v8 = 0;
  if ( v7 != 0 && v8 < (v4[3] - v7) >> 2 )
  {
    v9 = (int *)v4[2];
    *v9 = a2;
    v4[2] = v9 + 1;
    return 1;
  }
  else
  {
    sub_4E75F0((int)v4, v4[2], 1u, &a2);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x627520 CNEntangleVine__vmt1F4
//   【绞藤】TIE_VINE —— 缠绕定身触发
// ------------------------------------------------------------
int /*thiscall*/ CNEntangleVine__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  uint32_t *v4; // esi
  uint32_t *v6; // eax

  v4 = a2;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 17) == 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 128))(v4) != 0
    || (*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 840))(v4) == 6
    || (*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 840))(v4) == 7 )
  {
    return 0;
  }
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "TIE_VINE", -1, 0, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int *))(*v4 + 768))(v4, 16, 40, this);
  a2 = v4;
  sub_4E7BA0(&a2);
  if ( v4[78] < 0x10u )
    v6 = v4 + 73;
  else
    v6 = (uint32_t *)v4[73];
  off_77F3FC((char *)&byte_73DAE0, v6);
  return CNRDPassiveObject__vmt1F4(this, v4, a3, a4);
}



// ------------------------------------------------------------
// 0x6275F0 sub_6275F0
//   【绞藤】WALK_VINE_LOOP —— 藤上行走循环音
// ------------------------------------------------------------
void /*thiscall*/ sub_6275F0(uint32_t *this)
{
  unsigned int i; // ebx
  int v3; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // edi
  int v11; // ebx
  signed int v12; // ebx
  int v13; // ebx
  signed int v14; // ebx
  unsigned int v15; // ecx
  int v16; // edx
  int v17; // edi
  int v18; // eax
  unsigned int j; // ebx
  int v20; // ecx
  int v21; // ecx
  int v22; // [esp-18h] [ebp-4Ch]
  int v23; // [esp-10h] [ebp-44h]
  int v24; // [esp+1Ch] [ebp-18h] BYREF
  unsigned int k; // [esp+20h] [ebp-14h]
  char v26; // [esp+27h] [ebp-Dh]
  int v27; // [esp+30h] [ebp-4h]

  v26 = 0;
  v27 = 0;
  for ( i = 0; ; ++i )
  {
    v3 = *(this + 29);
    v4 = *(uint32_t *)(v3 + 120);
    k = i;
    v5 = v4 != 0 ? (*(uint32_t *)(v3 + 124) - v4) >> 2 : 0;
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(v3 + 120);
    if ( v6 != 0 && i < (*(uint32_t *)(v3 + 124) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * i);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 17) != 0 )
    {
      v8 = *(this + 29);
      v9 = *(uint32_t *)(v8 + 120);
      if ( v9 != 0 && i < (*(uint32_t *)(v8 + 124) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v24 = v10;
      if ( (uint8_t)sub_4E4630(v10) != 0
        && (uint8_t)sub_4E5CA0(v10) == 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 724))(v10) == 0
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 776))(v10, 16) != 1 )
      {
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 120))(v10);
        v12 = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v11);
        if ( v12 <= *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 32) )
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 124))(v10);
          v14 = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - v13);
          if ( v14 <= *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 36)
            && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 128))(v10) <= 0 )
          {
            v26 = 1;
            if ( (uint8_t)sub_627480(v10) != 0 )
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v10 + 212))(
                v10,
                "WALK_VINE_LOOP",
                10000,
                0,
                0);
            sub_4E7BA0(&v24);
          }
        }
        i = k;
      }
    }
  }
  if ( v26 != 0 )
  {
    for ( j = 0; ; ++j )
    {
      v20 = *(this + 254);
      if ( v20 == 0 || j >= (*(this + 255) - v20) >> 2 )
        break;
      v21 = *(uint32_t *)(4 * j + *(this + 254));
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v21 + 216))(v21, 10000);
      sub_627060(*(uint32_t *)(4 * j + *(this + 254)));
    }
  }
  else
  {
    *(this + 243) = sub_699000((int)(this + 9));
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
    && *(this + 243) + *(this + 244) < (unsigned int)sub_699000((int)(this + 9)) )
  {
    v15 = 0;
    for ( k = 0; ; v15 = k )
    {
      v16 = *(this + 254);
      if ( v16 == 0 || v15 >= (*(this + 255) - v16) >> 2 )
        break;
      v17 = *(uint32_t *)(v16 + 4 * v15);
      v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
      v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 124))(v17);
      v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 120))(v17);
      sub_4E4A50(this, 1030, 0, v18, v22, 0, v23, 0, 0, 0);
      ++k;
    }
    *(this + 243) = sub_699000((int)(this + 9));
  }
}


// ------------------------------------------------------------
// 0x627900 CNEntangleVineTrigger__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNEntangleVineTrigger__vmt14C(int this)
{
  int v2; // eax

  CNRDPassiveObject__vmt14C(this);
  v2 = *(uint32_t *)(this + 960);
  switch ( v2 )
  {
    case 3:
      if ( *(uint8_t *)(this + 1008) == 0
        && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 4, 0, 0, 0);
      }
      v2 = sub_699000(this + 980);
      if ( v2 > 300 )
      {
        sub_6275F0((uint32_t *)this);
        *(uint8_t *)(this + 993) = 0;
        *(uint8_t *)(this + 994) = 0;
        LOBYTE(v2) = sub_698F90(this + 980, 0, 0);
      }
      break;
    case 2:
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
      if ( *(uint8_t *)(v2 + 170) != 0 )
      {
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
        if ( (uint8_t)v2 != 0 )
          LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(
                         this,
                         3,
                         0,
                         0,
                         0);
      }
      break;
    case 4:
      v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);
      if ( *(uint8_t *)(v2 + 170) != 0 )
      {
        LOBYTE(v2) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
        if ( (uint8_t)v2 != 0 )
        {
          LOBYTE(v2) = *(uint8_t *)(this + 264);
          if ( (uint8_t)v2 == 0 )
            LOBYTE(v2) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
        }
      }
      break;
    default:
      break;
  }
  return v2;
}



// ============================================================
// 【分区 10】海星卵/莲花/被动触发器（0x627A00-0x6282A0）
// 证据: WRIGGLE_SLOW_LOOP / WRIGGLE_FAST_LOOP / HATCH_EGG（海星卵蠕动与孵化）、
//       LOTUS_SWEEP_LOOP（莲花横扫）；CNPassiveObjectTrigger = 被动物件触发基座
// ============================================================

// ------------------------------------------------------------
// 0x627A00 CNStarfishEgg__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNStarfishEgg__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10000);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10001);
  }
}



// ------------------------------------------------------------
// 0x627A40 sub_627A40
// ------------------------------------------------------------
int /*usercall*/ sub_627A40@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int result; // eax
  int v5; // edi
  int v6; // ebx
  int v7; // edi
  int v8; // eax
  int v9; // edx
  int v11; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // [esp-Ch] [ebp-34h]
  uint32_t v19[3]; // [esp+4h] [ebp-24h]
  uint16_t v20[3]; // [esp+10h] [ebp-18h] BYREF
  bool v21; // [esp+16h] [ebp-12h]
  char v22; // [esp+17h] [ebp-11h]
  int v23; // [esp+18h] [ebp-10h]
  int v24; // [esp+1Ch] [ebp-Ch]
  int i; // [esp+20h] [ebp-8h]
  int v26; // [esp+24h] [ebp-4h]

  sub_432FA0();
  result = rand() % 2 + 1;
  if ( result > 0 )
  {
    v19[0] = 250;
    v19[1] = 252;
    v19[2] = 253;
    for ( i = result; i != 0; --i )
    {
      v23 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *, int, int))(*a1 + 80))(a1, a3, a2) + 132)
                                  + 108)
                      + 112);
      v26 = 100;
      do
      {
        v5 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1);
        v6 = v5 + rand() % 40 - 20;
        v7 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1);
        v8 = rand();
        v9 = *a1;
        v24 = v7 + v8 % 20 - 10;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(v9 + 136))(a1, v6, v24, 0) != 0 )
          break;
      }
      while ( v26-- > 0 );
      v20[0] = rand() % 200 + 100;
      v20[1] = rand() % 100 + 50;
      v21 = rand() % 2 == 0;
      v22 = 3 - (rand() % 2 != 0);
      v11 = rand();
      v12 = *a1;
      a2 = 0;
      a3 = 0;
      v20[2] = v11 % 60 + 40;
      v13 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, uint32_t))(v12 + 152))(
              a1,
              1,
              v20,
              8,
              0xFFFF,
              0,
              0);
      v14 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 128))(a1, v13);
      v16 = (*(int (/*thiscall*/ **)(int *, int, int, int, int))(*a1 + 376))(a1, v23, v6, v24, v14 + 10);
      v15 = rand();
      result = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v12 + 592))(a1, v19[v15 % 3], v16);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x627BE0 sub_627BE0
// ------------------------------------------------------------
int /*thiscall*/ sub_627BE0(uint32_t **this)
{
  uint32_t *v2; // eax
  int v3; // edi
  int result; // eax

  v2 = (uint32_t *)**(this + 87);
  v3 = (int)(this + 243);
  *(this + 170) = v2;
  *(this + 171) = v2;
  *((uint8_t *)this + 985) = 0;
  *((uint8_t *)this + 986) = 0;
  sub_698F90((int)(this + 243), 5000, 0);
  sub_699030(v3);
  result = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[93])(this, 100);
  *((uint8_t *)this + 1001) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x627C40 CNStarfishEgg__vmt2B4
// ------------------------------------------------------------
int /*thiscall*/ CNStarfishEgg__vmt2B4(int *this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax
  uint32_t *v8; // edi

  result = *(this + 170);
  if ( result <= 0 )
  {
    v8 = (uint32_t *)(*(this + 36) + 4);
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
    if ( result != *v8 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
  }
  return result;
}



// ------------------------------------------------------------
// 0x627C80 CNStarfishEgg__vmt14C
//   【海星卵】WRIGGLE_SLOW_LOOP / WRIGGLE_FAST_LOOP（蠕动双速）/ HATCH_EGG（孵化）
// ------------------------------------------------------------
char /*usercall*/ CNStarfishEgg__vmt14C@<al>(uint32_t **a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // edi
  int v5; // edi
  uint32_t *v6; // edi
  uint32_t *v7; // edi
  int v8; // eax
  bool v9; // zf
  int v10; // edi
  int v11; // eax

  CNRDPassiveObject__vmt14C((int)a1);
  if ( *((uint8_t *)a1 + 1000) == 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*a1)[53])(a1, "WRIGGLE_SLOW_LOOP", 10000, 0, 0);
    *((uint8_t *)a1 + 1000) = 1;
  }
  v4 = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[50])(a1);
  if ( v4 == ((int (/*thiscall*/ *)(uint32_t **))(*a1)[24])(a1) && sub_4E7F30(a1, 100, 70, 0) != 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*a1)[49])(a1, *a1[36]);
    ((void (/*thiscall*/ *)(uint32_t **, int))(*a1)[54])(a1, 10000);
    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*a1)[53])(a1, "WRIGGLE_FAST_LOOP", 10001, 0, 0);
    sub_698FE0((int)(a1 + 243));
  }
  if ( *((uint8_t *)a1 + 986) == 0 )
  {
    v5 = (int)a1[249];
    if ( sub_699000((int)(a1 + 243)) >= v5 )
    {
      v6 = a1[36] + 1;
      if ( ((int (/*thiscall*/ *)(uint32_t **))(*a1)[50])(a1) != *v6 )
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*a1)[49])(a1, a1[36][1]);
    }
  }
  v7 = a1[36] + 1;
  v8 = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[50])(a1);
  v9 = v8 == *v7;
  v10 = a3;
  if ( v9 )
  {
    if ( *(int *)(((int (/*thiscall*/ *)(uint32_t **))(*a1)[50])(a1) + 148) >= 6 && *((uint8_t *)a1 + 1001) == 0 )
    {
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*a1)[53])(a1, "HATCH_EGG", -1, 0, 0);
      v11 = (int)*a1;
      *((uint8_t *)a1 + 1001) = 1;
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t **))(v11 + 308))(a1) != 0 && (int)a1[170] > 0 )
      {
        sub_627A40((int *)a1, a2, v10);
        a1[170] = nullptr;
      }
    }
    v8 = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[50])(a1);
    if ( *(int *)(v8 + 148) >= 9 )
    {
      LOBYTE(v8) = ((int (/*thiscall*/ *)(uint32_t **))(*a1)[77])(a1);
      if ( (uint8_t)v8 != 0 )
      {
        LOBYTE(v8) = *((uint8_t *)a1 + 264);
        if ( (uint8_t)v8 == 0 )
        {
          ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*a1)[145])(
            a1,
            1031,
            0,
            0,
            0,
            0,
            0,
            0,
            4,
            0,
            0,
            0);
          LOBYTE(v8) = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*a1)[78])(a1, 0);
        }
      }
    }
  }
  return v8;
}



// ------------------------------------------------------------
// 0x627E50 CNSweepingLegOfLotus__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNSweepingLegOfLotus__vmt12C(uint32_t *this, int a2)
{
  int v3; // eax

  if ( (uint32_t *)a2 == this )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    if ( __RTDynamicCast(
           v3,
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &CNPassiveObjectTrigger `RTTI Type Descriptor',
           0) != 0 )
      byte_795D3B = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10000);
  }
  CNLegOfLotus__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x627EB0 sub_627EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_627EB0(uint32_t *this)
{
  *(this + 243) = sub_699000((int)(this + 9));
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);
}



// ------------------------------------------------------------
// 0x627ED0 CNPassiveObjectTrigger__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNPassiveObjectTrigger__vmt14C(uint8_t *this)
{
  unsigned int v2; // eax

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(v2) = *(this + 264);
  if ( (uint8_t)v2 == 0 )
  {
    v2 = sub_699000((int)(this + 36));
    if ( *((uint32_t *)this + 243) + 3000 < v2 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 352))(this);
      v2 = sub_699000((int)(this + 36));
      *((uint32_t *)this + 243) = v2;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x627F20 sub_627F20
// ------------------------------------------------------------
bool /*thiscall*/ sub_627F20(void *this)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // esi
  bool result; // al

  result = false;
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) >= 100 )
  {
    v2 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this) + 132) + 44);
    v3 = *(uint32_t *)(v2 + 364);
    v4 = v2 + 360;
    v5 = v3 != 0 ? (*(uint32_t *)(v4 + 8) - v3) >> 5 : 0;
    if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) <= 224 * v5 + 100 )
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x627F80 CNSweepingLegOfLotus__vmt14C
//   【莲花】LOTUS_SWEEP_LOOP —— 横扫循环音
// ------------------------------------------------------------
char /*usercall*/ CNSweepingLegOfLotus__vmt14C@<al>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3@<edi>)
{
  int v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  bool v18; // zf
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax

  CNRDPassiveObject__vmt14C((int)a1);
  if ( *((uint8_t *)a1 + 984) == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*a1 + 124))(a1, a3, a2);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1) != 0 )
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 152))(a1) == 1 )
      {
        *(uint32_t *)(a1[28] + 16) = 1140457472;
        if ( v4 != 0 )
        {
          (*(void (/*stdcall*/ **)(int, int, uint32_t))(*a1 + 112))(-50, v4, 0);
        }
        else
        {
          v14 = (*(int (/*fastcall*/ **)(uint32_t *))(*a1 + 684))(a1);
          v15 = *a1;
          v16 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v14 + 124))(v14, 0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v15 + 112))(a1, -50, v16);
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
      }
    }
    else
    {
      v5 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 80))(a1) + 132) + 44);
      v6 = *(uint32_t *)(v5 + 364);
      v7 = v5 + 360;
      if ( v6 != 0 )
        v8 = (*(uint32_t *)(v7 + 8) - v6) >> 5;
      else
        v8 = 0;
      v9 = 224 * v8 + 50;
      *(uint32_t *)(a1[28] + 16) = -1007026176;
      v10 = *a1;
      if ( v4 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v10 + 112))(a1, v9, v4, 0);
      }
      else
      {
        v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 684))(a1);
        v12 = *a1;
        v13 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v11 + 124))(v11, 0);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v12 + 112))(a1, v9, v13);
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int))(*a1 + 212))(a1, "LOTUS_SWEEP_LOOP", 10000);
    *((uint8_t *)a1 + 984) = 1;
  }
  LOBYTE(v17) = *((uint8_t *)a1 + 264);
  if ( (uint8_t)v17 == 0 )
  {
    v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1);
    if ( *(uint8_t *)(v17 + 170) != 0 )
    {
      v18 = !sub_627F20(a1);
      v19 = *a1;
      if ( v18 )
      {
        v22 = (*(int (/*thiscall*/ **)(uint32_t *))(v19 + 80))(a1);
        sub_424120(*(uint32_t **)(v22 + 132), 0, 0);
        LOBYTE(v17) = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
        if ( (uint8_t)v17 != 0 )
          LOBYTE(v17) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 312))(a1, 0);
      }
      else
      {
        v20 = (*(int (/*thiscall*/ **)(uint32_t *))(v19 + 80))(a1);
        sub_424120(*(uint32_t **)(v20 + 132), 2, 1000);
        v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 200))(a1);
        LOBYTE(v17) = sub_4926A0(v21);
      }
    }
  }
  return v17;
}



// ------------------------------------------------------------
// 0x628110 CNPassiveObjectTrigger__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNPassiveObjectTrigger__vmt1F4(int **this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // ebx
  int v7; // ebx
  DWORD Time; // eax
  int *v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v17; // [esp-20h] [ebp-28h]
  int v18; // [esp-18h] [ebp-20h]
  int v19; // [esp+4h] [ebp-4h]

  if ( byte_795D3B == 1 && ((uint8_t (/*thiscall*/ *)(int **))(*this)[77])(this) != 0 )
  {
    v5 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(((int (/*thiscall*/ *)(int **))(*this)[20])(this) + 132) + 108) + 492);
    v6 = ((int (/*thiscall*/ *)(int **))(*this)[31])(this);
    v7 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this) + v6;
    v19 = v5 + ((int (/*thiscall*/ *)(int **))(*this)[13])(this);
    Time = timeGetTime();
    srand(v7 + v19 + Time);
    v9 = *(this + 87);
    v10 = *v9;
    v11 = v9[1];
    if ( v11 == 1025 )
    {
      if ( rand() % 100 < v10 )
      {
        v13 = ((int (/*thiscall*/ *)(int **))(*this)[20])(this);
        v14 = sub_425050(*(uint32_t **)(*(uint32_t *)(v13 + 132) + 44)) / 2;
        v15 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this);
        sub_4E4A50(this, 1025, 0xFFFF, 0, 0, 1000, v15 <= v14, 0, 0, 0);
        byte_795D3B = 0;
      }
    }
    else if ( v11 == 30028 )
    {
      v18 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 124))(a2);
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 120))(a2);
      sub_4E4A50(this, 30028, 0xFFFF, v12, v17, 500, v18, 0, 0, 0);
    }
    if ( *((uint8_t *)this + 264) == 0 )
      ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x628260 sub_628260
// ------------------------------------------------------------
int /*thiscall*/ sub_628260(uint32_t *this, int a2)
{
  uint32_t *v3; // eax
  int v4; // edx

  v3 = (uint32_t *)*(this + 36);
  v4 = *this;
  *((uint8_t *)this + 984) = 0;
  (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v4 + 204))(100, *v3, 0, 0, 0, 0);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);
}



// ------------------------------------------------------------
// 0x6282A0 sub_6282A0
// ------------------------------------------------------------
int /*thiscall*/ sub_6282A0(uint32_t *this)
{
  uint32_t *v1; // ebx
  unsigned int v2; // edi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // esi
  int v11; // [esp+Ch] [ebp-8h]

  v1 = this;
  v2 = 0;
  while ( 1 )
  {
    v3 = v1[29];
    v4 = *(uint32_t *)(v3 + 8);
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;
    if ( (int)v2 >= result )
      return result;
    v6 = *(uint32_t *)(v3 + 8);
    if ( v6 != 0 && v2 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * v2);
    else
      v7 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v7 + 40))(v7, 529) != 0 )
    {
      v8 = v1[29];
      v9 = *(uint32_t *)(v8 + 8);
      if ( v9 != 0 && v2 < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * v2);
      else
        v10 = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 376))(v10);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*v1 + 376))(v1) != v11
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v10 + 724))(v10) != 0 )
      {
        v1 = this;
        goto LABEL_20;
      }
      v1 = this;
      if ( __RTDynamicCast(v10, 0, &IRDMonster `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0) == 0 )
        goto LABEL_20;
      sub_5B7940(this);
      ++v2;
    }
    else
    {
LABEL_20:
      ++v2;
    }
  }
}



// ============================================================
// 【分区 11】钟/重力反转/落石/旗帜（0x628390-0x628E90）
// 证据: HIT_BELL / BREAK_BELL（狂信者钟）、BEHEMOTH_CRY / ZOOM_UP / BEHEMOTH_SCREAM /
//       SUDDEN_DROP（重力反转四段演出：吼叫→镜头拉升→吼叫→坠落）、
//       TRAP_STONE_BREAK / TAU_EQUAKE（落石与牛头地震触发）
// ============================================================

// ------------------------------------------------------------
// 0x628390 CNBellForZealots__vmt200
//   【钟】HIT_BELL —— 敲击音
// ------------------------------------------------------------
int /*thiscall*/ CNBellForZealots__vmt200(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // eax
  uint32_t *v6; // edi
  uint32_t *v7; // edi
  uint32_t *v8; // ebx
  int v9; // eax

  if ( *(this + 276) >= *(this + 275) )
    return 0;
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 348))(a2);
  if ( *(uint8_t *)(v5 + 16) == 0 && *(float *)v5 <= 0.0 )
    return 0;
  v6 = (uint32_t *)(*(this + 36) + 12);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) != *v6 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HIT_BELL", -1, 0, 0);
    sub_4926A0(*(uint32_t *)(*(this + 36) + 12));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 12));
    sub_4926A0(*(uint32_t *)(*(this + 36) + 16));
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      100,
      *(uint32_t *)(*(this + 36) + 16),
      0,
      0,
      0,
      0);
    sub_6282A0(this);
    v7 = (uint32_t *)(*(this + 36) + 12);
    v8 = *(uint32_t **)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 80))(this) + 132);
    v9 = sub_491C10(*v7);
    sub_424120(v8, 1, v9);
    ++*(this + 276);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x6284C0 CNBellForZealots__vmt14C
//   【钟】BREAK_BELL —— 破碎音
// ------------------------------------------------------------
void /*thiscall*/ CNBellForZealots__vmt14C(int this)
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  int v8; // eax
  int v9; // edi
  int v10; // eax
  uint8_t v11[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v13; // [esp+20h] [ebp-4h]

  CNMapObject__vmt14C((int *)this);
  v2 = *(uint32_t *)(this + 144);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *(uint32_t *)(v2 + 12)
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )
  {
    if ( *(uint32_t *)(this + 1104) < *(uint32_t *)(this + 1100) )
    {
      v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 96))(this);
      sub_4926A0(v8);
      v9 = *(uint32_t *)this;
      v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 96))(this);
      (*(void (/*thiscall*/ **)(int, int))(v9 + 196))(this, v10);
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 1108) + 12))(*(uint32_t *)(this + 1108), 0);
      v3 = **(uint32_t **)(this + 1108);
      v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
      v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v4);
      v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v5 + 1);
      (*(void (/*thiscall*/ **)(uint32_t, int))(v3 + 40))(*(uint32_t *)(this + 1108), v6);
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 1108) + 92))(*(uint32_t *)(this + 1108), v11);
      v7 = *(void **)(this + 116);
      v13 = 0;
      sub_4600B0(v7, 2, 0, (int)v11);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 20));
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "BREAK_BELL",
        -1,
        0,
        0);
      sub_60B710((int *)this);
      if ( Block != nullptr )
        j__free(Block);
    }
  }
}



// ------------------------------------------------------------
// 0x628610 CNBellForZealots__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNBellForZealots__vmt2E4(uint32_t *this)
{
  int v2; // edx
  int v3; // eax
  uint32_t *v4; // ebx
  int v5; // eax
  int result; // eax

  v2 = *this;
  *(this + 275) = *(uint32_t *)(*(this + 87) + 28);
  *(this + 276) = 0;
  (*(void (/*stdcall*/ **)(int))(v2 + 372))(100);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    0,
    *(uint32_t *)(*(this + 36) + 8),
    0,
    0,
    0,
    0);
  if ( operator new(0x12Cu) != nullptr )
  {
    v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this) + 32) + 24;
    if ( *(this + 96) < 0x10u )
      v4 = this + 91;
    else
      v4 = (uint32_t *)*(this + 91);
    v5 = sub_41ACF0(v3);
    result = sub_4C3640(v4, v5, this);
  }
  else
  {
    result = 0;
  }
  *(this + 277) = result;
  return result;
}



// ------------------------------------------------------------
// 0x6286E0 CNGravityChanger__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNGravityChanger__vmt14C(uint32_t *this)
{
  int v2; // eax

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *(uint32_t *)(*(this + 29) + 132);
  if ( v2 == 0 || *(uint32_t *)(v2 + 1324) != 0 )
  {
    LOBYTE(v2) = 0;
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 596))(this, v2);
  }
  else
  {
    LOBYTE(v2) = 1;
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 596))(this, v2);
  }
}



// ------------------------------------------------------------
// 0x628720 CNGravityChanger__vmt1D8
//   【重力反转】BEHEMOTH_CRY / ZOOM_UP / BEHEMOTH_SCREAM / SUDDEN_DROP 四段演出
// ------------------------------------------------------------
int */*thiscall*/ CNGravityChanger__vmt1D8(uint32_t *this, int a2, int a3, int a4, int a5)
{
  int *result; // eax
  int v7; // edx
  int v8; // ecx
  uint32_t *v9; // ecx

  CNRDPassiveObject__vmt1D8(this, a2, (int)this, a2, a3, a4, a5);
  result = *(int **)(a3 + 4);
  v7 = *result;
  if ( a2 == 2 )
    v7 = -v7;
  v8 = *(this + 29);
  if ( v8 != 0 )
  {
    v9 = *(uint32_t **)(v8 + 132);
    if ( v9 != nullptr )
    {
      sub_426B10(v9, v7, result[1]);
      if ( a2 == 2 )
      {
        sub_432EA0("BEHEMOTH_CRY", -1, 0, 0);
        return (int *)sub_432EA0("ZOOM_UP", -1, 0, 0);
      }
      else
      {
        sub_432EA0("BEHEMOTH_SCREAM", -1, 0, 0);
        return (int *)sub_432EA0("SUDDEN_DROP", -1, 0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6287C0 CNGravityChanger__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNGravityChanger__vmt1F4(int this, uint32_t *a2, float *a3, int a4)
{
  uint32_t *v4; // edi
  int v6; // eax
  int v7; // edx
  int v8; // ebx
  int v9; // edi
  int v10; // ebx
  int v11; // ebx
  int v12; // edi
  void *v14[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v15; // [esp+24h] [ebp-4h]

  v4 = a2;
  v6 = CNRDPassiveObject__vmt1F4((int *)this, a2, a3, a4);
  v7 = *(uint32_t *)this;
  v8 = v6;
  a4 = v6;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(v7 + 308))(this) != 0 )
  {
    sub_432FA0();
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*v4 + 40))(v4, 273) != 0 )
    {
      v9 = *(uint32_t *)(*(uint32_t *)(this + 116) + 132);
      if ( v9 != 0 && *(uint32_t *)(v9 + 1324) == 0 )
      {
        v10 = *(uint32_t *)(this + 348);
        if ( rand() % 100 < *(uint32_t *)(v10 + 16) )
        {
          v11 = (*(int *)(v9 + 1320) < 0) + 2;
          v12 = rand() % 100;
          a3 = (float *)sub_423A80(**(uint32_t **)(this + 348), *(uint32_t *)(*(uint32_t *)(this + 348) + 4), v12, 99);
          a2 = (uint32_t *)sub_423A80(
                           *(uint32_t *)(*(uint32_t *)(this + 348) + 8),
                           *(uint32_t *)(*(uint32_t *)(this + 348) + 12),
                           v12,
                           99);
          memset(&v14[1], 0, 12);
          v15 = 0;
          sub_431230((int)v14, &a3);
          sub_431230((int)v14, &a2);
          (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, v11, v14, 0, 0);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 564))(this);
          v15 = -1;
          sub_5E5260(v14);
        }
        v8 = a4;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    }
  }
  return v8;
}



// ------------------------------------------------------------
// 0x628930 sub_628930
// ------------------------------------------------------------
int /*thiscall*/ sub_628930(uint32_t *this)
{
  int v2; // edi

  v2 = (int)(this + 9);
  *(this + 243) = sub_699000((int)(this + 9));
  *(this + 244) = sub_699000(v2);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);
}



// ------------------------------------------------------------
// 0x628960 CNDroppingRock__vmt12C
//   【落石】TRAP_STONE_BREAK —— 落石破碎
// ------------------------------------------------------------
void /*thiscall*/ CNDroppingRock__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
      this,
      "TRAP_STONE_BREAK",
      -1,
      0,
      0);
}



// ------------------------------------------------------------
// 0x628990 sub_628990
// ------------------------------------------------------------
void /*thiscall*/ sub_628990(void *this)
{
  int v1; // eax
  int v2; // ecx
  int v3; // eax
  int v4; // esi
  int v5; // edi
  int v6; // edx
  int v7; // ebx
  int v8; // esi
  int v9; // edi
  int v10; // eax
  int v11; // [esp+8h] [ebp-18h]
  int v12; // [esp+Ch] [ebp-14h]
  int i; // [esp+10h] [ebp-10h]
  int v14; // [esp+14h] [ebp-Ch]
  int v16; // [esp+1Ch] [ebp-4h]

  v1 = *(uint32_t *)(*(uint32_t *)((*(int (/*fastcall*/ **)(void *))(*(uint32_t *)this + 80))(this) + 132) + 44);
  v2 = *(uint32_t *)(v1 + 364);
  v3 = v1 + 360;
  v4 = 0;
  if ( v2 != 0 )
  {
    v14 = (*(uint32_t *)(v3 + 8) - v2) >> 5;
    v5 = v14;
  }
  else
  {
    v5 = 0;
    v14 = 0;
  }
  sub_432FA0();
  v12 = 0;
  if ( v5 > 0 )
  {
    v16 = 0;
    do
    {
      if ( v16 != 0 && v4 != v5 - 1 )
      {
        v6 = rand() % 3 + 1;
        if ( v6 > 0 )
        {
          for ( i = v6; i != 0; --i )
          {
            v7 = rand() % 8;
            v8 = v16 + rand() % 224;
            v9 = rand() % 200 + 100;
            v11 = rand() % 200 + 500;
            if ( (*(uint8_t (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v8, v9, 0) != 0 )
            {
              if ( v7 < 5 )
                sub_4E4A50(this, 48012, 1, v8, v9, 0, 0, 0, 0, 0);
              v10 = rand() % 2;
              sub_4E4A50(this, 1029, v7, v8, v9, v11, v10 != 0, 0, 0, 0);
            }
          }
          v4 = v12;
          v5 = v14;
        }
      }
      v12 = ++v4;
      v16 += 224;
    }
    while ( v4 < v5 );
  }
}



// ------------------------------------------------------------
// 0x628B00 CNDroppingRockTrigger__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNDroppingRockTrigger__vmt14C(uint32_t *this)
{
  unsigned int v2; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( byte_9B9450 == 1 )
  {
    v2 = sub_699000((int)(this + 9));
    if ( *(this + 243) + 2000 >= v2 )
    {
      LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)v2 != 0 )
      {
        LOBYTE(v2) = *((uint8_t *)this + 264);
        if ( (uint8_t)v2 == 0 )
        {
          byte_9B9450 = 0;
          sub_628990(this);
          LOBYTE(v2) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
        }
      }
    }
  }
  else
  {
    v2 = sub_699000((int)(this + 9));
    if ( *(this + 244) + 3000 < v2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);
      v2 = sub_699000((int)(this + 9));
      *(this + 244) = v2;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x628BA0 CNDroppingRockTrigger__vmt1F4
//   【落石】TAU_EQUAKE —— 牛头地震触发音
// ------------------------------------------------------------
int /*thiscall*/ CNDroppingRockTrigger__vmt1F4(int **this, int a2, int a3, int a4)
{
  int v5; // edi
  int v6; // eax

  if ( byte_9B9450 == 0 )
  {
    v5 = **(this + 87);
    if ( sub_445870((uint32_t *)dword_8F8520, 37712, 100) < v5 )
    {
      byte_9B9450 = 1;
      *(this + 243) = (int *)sub_699000((int)(this + 9));
      v6 = ((int (/*thiscall*/ *)(int **))(*this)[20])(this);
      sub_424120(*(uint32_t **)(v6 + 132), 4, 2000);
      ((void (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "TAU_EQUAKE", -1, 0, 0);
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x628C20 CNDroppingRock__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNDroppingRock__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  int *v5; // edi
  int v6; // eax
  int v7; // eax
  float *v8; // eax

  v5 = (int *)(*(this + 87) + 4 * *(this + 243));
  *(float *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this) = (float)*v5;
  if ( *(float *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this) == 0.0 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 348))(this);
LABEL_10:
    *(uint32_t *)(v6 + 60) = 0;
    return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a2 + 40))(a2, 529) != 0 )
  {
    v7 = a2[1943];
    if ( v7 == 3 || v7 == 1 || v7 == 2 )
    {
      *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this) = 0;
      v6 = (*(int (/*thiscall*/ **)(int *))(*this + 348))(this);
      goto LABEL_10;
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*a2 + 376))(a2) == 100 )
    {
      v8 = (float *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this);
      *v8 = *v8 * 0.1;
    }
  }
  return CNRDPassiveObject__vmt1F4(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x628CF0 sub_628CF0
// ------------------------------------------------------------
int /*thiscall*/ sub_628CF0(uint32_t *this, int a2)
{
  void **v3; // edi
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  const char *v7; // eax
  int v8; // eax
  int v9; // edx
  int result; // eax
  int (/*thiscall*/ ***v11)(uint32_t, int); // ecx

  v3 = (void **)*(this + 34);
  *(this + 243) = a2;
  if ( v3 != nullptr )
  {
    sub_42AF90(v3);
    sub_657740(v3, 228);
  }
  *(this + 34) = 0;
  v4 = sub_42FCB0(228);
  if ( v4 != 0 )
  {
    v5 = *(this + 243);
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this);
    v7 = (const char *)sub_41ACF0(*(uint32_t *)(v6 + 32) + 4 * v5);
    v8 = sub_431860(v4, v7, 1);
  }
  else
  {
    v8 = 0;
  }
  v9 = *this;
  *(this + 34) = v8;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 196))(this, v8);
  result = *(this + 28);
  *(uint32_t *)(result + 36) = -1200;
  if ( (int)*(this + 243) >= 4 )
  {
    v11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 219);
    if ( v11 != nullptr )
      result = (**v11)(v11, 1);
    *(this + 219) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x628DE0 CNFlappingBanner__vmt14C
// ------------------------------------------------------------
int /*thiscall*/ CNFlappingBanner__vmt14C(uint32_t *this)
{
  int v2; // edi
  unsigned int i; // edx
  uint8_t *v4; // ecx
  int v5; // eax
  int v6; // edx
  int v8; // [esp+0h] [ebp-8h]

  CNRDPassiveObject__vmt14C((int)this);
  v2 = *(this + 244);
  for ( i = 0; ; ++i )
  {
    if ( v2 == 0 || i >= (*(this + 245) - v2) >> 2 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(this + 34));
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, 4);
    }
    v4 = *(uint8_t **)(*(this + 244) + 4 * i);
    if ( v4[984] != 0 )
      break;
  }
  v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)v4 + 152))(v4);
  v6 = *this;
  v8 = *(uint32_t *)*(this + 36);
  if ( v5 == 1 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v6 + 196))(this, v8);
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 148))(this, 0);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v6 + 196))(this, v8);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, 1);
  }
}



// ------------------------------------------------------------
// 0x628E90 CNFlappingBanner__vmt140
// ------------------------------------------------------------
int /*thiscall*/ CNFlappingBanner__vmt140(int *this)
{
  unsigned int v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // edx
  int v13; // ebx
  int v14; // edx
  unsigned int v15; // ecx
  int *v16; // eax
  unsigned int v17; // ebx
  int v18; // [esp+Ch] [ebp-8h] BYREF
  unsigned int v19; // [esp+10h] [ebp-4h]

  CNRDPassiveObject__vmt140(this);
  v2 = 0;
  if ( *(this + 244) != 0 )
    j__free((void *)*(this + 244));
  *(this + 244) = 0;
  *(this + 245) = 0;
  *(this + 246) = 0;
  while ( 1 )
  {
    v3 = *this;
    v19 = v2;
    v4 = (*(int (/*thiscall*/ **)(int *))(v3 + 80))(this);
    v5 = *(uint32_t *)(v4 + 120);
    v6 = v4 + 116;
    result = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;
    if ( (int)v2 >= result )
      return result;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
    v9 = *(uint32_t *)(v8 + 120);
    if ( v9 != 0 && v2 < (*(uint32_t *)(v8 + 124) - v9) >> 2 )
      v10 = *(uint32_t *)(v9 + 4 * v2);
    else
      v10 = 0;
    if ( __RTDynamicCast(v10, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNWindShaker `RTTI Type Descriptor', 0) != 0 )
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
      v12 = *(uint32_t *)(v11 + 120);
      if ( v12 != 0 && v2 < (*(uint32_t *)(v11 + 124) - v12) >> 2 )
        v13 = *(uint32_t *)(v12 + 4 * v2);
      else
        v13 = 0;
      v14 = *(this + 244);
      v18 = v13;
      if ( v14 != 0 )
        v15 = (*(this + 245) - v14) >> 2;
      else
        v15 = 0;
      if ( v14 == 0 || v15 >= (*(this + 246) - v14) >> 2 )
      {
        sub_428220((int)(this + 243), *(this + 245), 1u, &v18);
        v2 = v19;
        goto LABEL_24;
      }
      v16 = (int *)*(this + 245);
      *v16 = v13;
      v17 = v19;
      *(this + 245) = (int)(v16 + 1);
      v2 = v17 + 1;
    }
    else
    {
LABEL_24:
      ++v2;
    }
  }
}



// ============================================================
// 【分区 12】龙头炮台（CNDragonHeadSide 家族，0x628FB0-0x6299C0）
// 证据: Particle/DragonHeadEnergyBall.ptl（侧向）/ DragonHeadEnergyBallVertical.ptl（纵向）；
//       变体: SideFlame（喷火）/ SideNentan（能量球）/ SideGas（毒气）/ FrontNentan
// ============================================================

// ------------------------------------------------------------
// 0x628FB0 CNDragonHeadSide__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSide__vmt2E4(uint32_t *this)
{
  int result; // eax

  *(this + 275) = 0;
  *((uint8_t *)this + 1108) = 0;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);
  *((uint8_t *)this + 1109) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x628FE0 CNDragonHeadSide__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNDragonHeadSide__vmt12C(uint32_t *this, int a2)
{
  if ( this == (uint32_t *)a2 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  return CNMapObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x629010 sub_629010
// ------------------------------------------------------------
int /*thiscall*/ sub_629010(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 280);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 280) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x629030 CNDragonHeadSideFlame__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNDragonHeadSideFlame__vmt12C(uint32_t *this, int a2)
{
  if ( this == (uint32_t *)a2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  }
  return CNMapObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x629060 CNDragonHeadSideNentan__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSideNentan__vmt2E4(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);
  v3 = *this;
  *(this + 278) = v2;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 10);
  *(this + 279) = result;
  return result;
}



// ------------------------------------------------------------
// 0x629090 CNDragonHeadSideNentan__vmt14C
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNDragonHeadSideNentan__vmt14C(int *this)
{
  unsigned int result; // eax

  CNMapObject__vmt14C(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
    if ( result == *(this + 34) )
    {
      result = sub_699000((int)(this + 9));
      if ( *(this + 275) + 5000 < result )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 756))(this) != 0 && rand() % 100 < 50 )
          (*(void (/*thiscall*/ **)(int *))(*this + 760))(this);
        result = sub_699000((int)(this + 9));
        *(this + 275) = result;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x629110 CNDragonHeadSideNentan__vmt2F8
//   【龙头】Particle/DragonHeadEnergyBall.ptl —— 侧向能量球
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSideNentan__vmt2F8(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  uint16_t *v4; // esi
  int v5; // eax
  int v7; // [esp-1Ch] [ebp-94h]
  int v8; // [esp+Ch] [ebp-6Ch]
  uint16_t v9[50]; // [esp+10h] [ebp-68h] BYREF
  int v10; // [esp+74h] [ebp-4h]

  v10 = dword_796E50;
  sub_423A20((int)v9);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/DragonHeadEnergyBall.ptl");
  v3 = *(this + 279);
  v4 = (uint16_t *)v2;
  v5 = *this;
  qmemcpy(v9, v4, 0x60u);
  v7 = *(this + 278);
  v9[48] = v4[48];
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint16_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v5 + 580))(
           this,
           30082,
           0,
           v9,
           0,
           v7,
           0,
           v3,
           v8,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x6291A0 CNDragonHeadSideGas__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSideGas__vmt2E4(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);
  v3 = *this;
  *(this + 278) = v2;
  *(this + 279) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 10);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 11);
  v5 = *this;
  *(this + 280) = v4;
  *(this + 281) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 12);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 13);
  *(this + 282) = result;
  return result;
}



// ------------------------------------------------------------
// 0x629200 CNDragonHeadSideGas__vmt14C
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNDragonHeadSideGas__vmt14C(int *this)
{
  unsigned int result; // eax

  CNMapObject__vmt14C(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
    if ( result == *(this + 34) )
    {
      result = sub_699000((int)(this + 9));
      if ( *(this + 275) + 5000 < result )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 756))(this) != 0 && rand() % 100 < 50 )
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
            this,
            *(this + 282),
            *(this + 278),
            0,
            0,
            *(this + 279),
            *(this + 280),
            *(this + 281),
            4,
            0,
            0,
            0);
        result = sub_699000((int)(this + 9));
        *(this + 275) = result;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6292C0 CNDragonHeadFrontNentan__vmt2F8
//   【龙头】Particle/DragonHeadEnergyBallVertical.ptl —— 纵向能量球
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadFrontNentan__vmt2F8(uint32_t *this)
{
  uint16_t *v2; // eax
  int v3; // edx
  int result; // eax
  int v5; // [esp-1Ch] [ebp-90h]
  int v6; // [esp-14h] [ebp-88h]
  uint16_t v7[50]; // [esp+Ch] [ebp-68h] BYREF
  int v8; // [esp+70h] [ebp-4h]

  v8 = dword_796E50;
  sub_423A20((int)v7);
  v2 = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(
                  this,
                  "Particle/DragonHeadEnergyBallVertical.ptl");
  v3 = *this;
  v6 = *(this + 279);
  qmemcpy(v7, v2, 0x60u);
  v5 = *(this + 278);
  v7[48] = v2[48];
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint16_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v3 + 580))(
             this,
             30083,
             0,
             v7,
             0,
             v5,
             0,
             v6,
             1,
             0,
             0,
             0);
  *(this + 280) = result;
  return result;
}



// ------------------------------------------------------------
// 0x629340 CNDragonHeadFrontNentan__vmt128
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadFrontNentan__vmt128(uint32_t *this, int a2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 33);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2);
    if ( result == *(this + 280) )
      return sub_4E7E40(a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x629380 CNDragonHeadSide__vmtC
// ------------------------------------------------------------
char /*thiscall*/ CNDragonHeadSide__vmtC(int *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  unsigned int v6; // eax
  int v7; // eax

  CNMapObject__vmtC(this);
  v2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 7);
  v3 = *this;
  *(this + 170) = v2;
  *(this + 171) = v2;
  *(this + 276) = (*(int (/*thiscall*/ **)(int *, int))(v3 + 384))(this, 8);
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);
  v5 = *(uint32_t *)(v4 + 32);
  v6 = v4 + 28;
  if ( v5 != 0 )
  {
    v6 = (*(uint32_t *)(v6 + 8) - v5) >> 2;
    if ( v6 >= 7 )
    {
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);
      LOBYTE(v6) = sub_43BCF0((void *)(*(uint32_t *)(v7 + 32) + 24), "Left");
      if ( (uint8_t)v6 != 0 )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 148))(this, 0);
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x629410 CNDragonHeadSideFlame__vmt1D8
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSideFlame__vmt1D8(int *this, int a2, int a3, int a4, int a5)
{
  int v6; // ebx
  int result; // eax
  int *v8; // eax
  int v9; // ecx
  int v10; // edx

  v6 = *(this + 240);
  CNRDPassiveObject__vmt1D8(this, v6, a2, a2, a3, a4, a5);
  if ( a2 != 0 )
  {
    result = a2 - 2;
    if ( a2 == 2 )
    {
      v8 = (int *)(*(this + 36) + 4);
      *((uint8_t *)this + 1116) = 1;
      sub_4926A0(*v8);
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 280) + 12))(*(this + 280), 0);
      result = sub_699000((int)(this + 9));
      *(this + 278) = result;
    }
  }
  else
  {
    v9 = *(this + 280);
    *((uint8_t *)this + 1116) = 0;
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v9 + 64))(v9, 1);
    if ( v6 == 2 )
    {
      v10 = *this;
      if ( *((uint8_t *)this + 1108) != 0 )
        return (*(int (/*thiscall*/ **)(int *, uint32_t))(v10 + 196))(this, *(uint32_t *)*(this + 36));
      else
        return (*(int (/*thiscall*/ **)(int *, uint32_t))(v10 + 196))(this, *(this + 34));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6294F0 sub_6294F0
// ------------------------------------------------------------
void /*thiscall*/ sub_6294F0(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  uint8_t v8[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  float v10; // [esp+14h] [ebp-14h]
  int v11; // [esp+18h] [ebp-10h]
  int v12; // [esp+24h] [ebp-4h]

  v2 = *(this + 219);
  if ( v2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v2 + 12))(v2, 0);
    v3 = *(uint32_t *)*(this + 219);
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 192))(this);
    v4 = *this;
    v10 = (double)v11 * 0.80000001;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)((double)v11 + v10));
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v3 + 40))(*(this + 219), v6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v8);
    v7 = (void *)*(this + 29);
    v12 = 0;
    sub_4600B0(v7, 2, 0, (int)v8);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x6295C0 CNDragonHeadSideFlame__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNDragonHeadSideFlame__vmt14C(int this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // edi
  int v6; // ebx
  int v7; // edx
  void *v8; // eax
  int v9; // [esp-10h] [ebp-34h]
  int v10; // [esp-Ch] [ebp-30h]
  int v11; // [esp-8h] [ebp-2Ch]
  void *v12[7]; // [esp+8h] [ebp-1Ch] BYREF

  CNMapObject__vmt14C((int *)this);
  v2 = *(uint32_t *)(this + 960);
  if ( v2 != 0 )
  {
    if ( v2 == 2 )
    {
      v3 = *(uint32_t *)(this + 144);
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *(uint32_t *)(v3 + 4) )
      {
        if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
        }
        else if ( *(int *)(this + 680) > 0 )
        {
          v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
          v5 = *(uint32_t *)(this + 1124);
          if ( v4 != 1 )
            v5 = -v5;
          v6 = **(uint32_t **)(this + 1120);
          v11 = *(uint32_t *)(this + 1128) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
          v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this) + 1;
          v9 = v5 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);
          (*(void (/*thiscall*/ **)(uint32_t))(v6 + 40))(*(uint32_t *)(this + 1120));
          (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(this + 1120) + 92))(*(uint32_t *)(this + 1120), v12);
          v7 = *(uint32_t *)this;
          v12[6] = nullptr;
          v8 = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, void **))(v7 + 80))(this, 2, 0, v12);
          sub_4600B0(v8, v9, v10, v11);
          if ( *(uint32_t *)(this + 1112) + 500 < (unsigned int)sub_699000(this + 36) )
          {
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
            *(uint32_t *)(this + 1112) = sub_699000(this + 36);
          }
          sub_5E5260(v12);
        }
      }
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *(uint32_t *)(this + 136)
         && *(uint32_t *)(this + 1100) + 5000 < (unsigned int)sub_699000(this + 36) )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 756))(this) != 0
      && rand() % 100 < 50
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 2, 0, 0, 0);
    }
    *(uint32_t *)(this + 1100) = sub_699000(this + 36);
  }
}



// ------------------------------------------------------------
// 0x6297C0 CNDragonHeadSide__vmt2B4
// ------------------------------------------------------------
void /*thiscall*/ CNDragonHeadSide__vmt2B4(uint32_t **this, int a2, int a3, int a4, int a5, int a6)
{
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v10; // eax

  if ( (int)*(this + 170) <= (int)*(this + 276) && *((uint8_t *)this + 1108) == 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 36));
    sub_6294F0(this);
    *((uint8_t *)this + 1108) = 1;
    if ( sub_41ACF0(this + 260) != 0 )
    {
      v7 = (int)*this;
      v8 = sub_41ACF0(this + 260);
      (*(void (/*thiscall*/ **)(uint32_t **, int, int, uint32_t, uint32_t))(v7 + 212))(this, v8, -1, 0, 0);
    }
  }
  if ( (int)*(this + 170) <= 0 )
  {
    if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
    {
      if ( sub_41ACF0(this + 260) != 0 )
      {
        v9 = (int)*this;
        v10 = sub_41ACF0(this + 260);
        (*(void (/*thiscall*/ **)(uint32_t **, int, int, uint32_t, uint32_t))(v9 + 212))(this, v10, -1, 0, 0);
      }
      ((void (/*thiscall*/ *)(uint32_t **))(*this)[186])(this);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[78])(this, 0);
    }
    sub_6294F0(this);
  }
  if ( *(this + 240) == (uint32_t *)2 && ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[140])(this, 0, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x6298C0 sub_6298C0
// ------------------------------------------------------------
char /*thiscall*/ sub_6298C0(uint32_t *this, signed int a2, signed int a3, char a4)
{
  int v5; // eax
  int *v6; // edi
  int v7; // ecx
  int v8; // ebx
  int v10; // ebx
  uint8_t v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int *v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]
  int v16; // [esp+34h] [ebp+Ch]

  Block = nullptr;
  v13 = nullptr;
  v14 = 0;
  v15 = 0;
  sub_4E7F30(this, a2, a3, (int)v11);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v6 = (int *)Block;
  v16 = v5;
  if ( Block != v13 )
  {
    while ( 1 )
    {
      v7 = *v6;
      if ( a4 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 120))(v7);
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
        {
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 && v8 >= v16 )
          {
LABEL_5:
            if ( Block != nullptr )
              j__free(Block);
            return 1;
          }
        }
        else if ( v8 <= v16 )
        {
          goto LABEL_5;
        }
      }
      else
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) < v10 )
          goto LABEL_5;
      }
      if ( ++v6 == v13 )
      {
        v6 = (int *)Block;
        break;
      }
    }
  }
  if ( v6 != nullptr )
    j__free(v6);
  return 0;
}



// ------------------------------------------------------------
// 0x6299C0 CNDragonHeadSide__vmt2F4
// ------------------------------------------------------------
char /*thiscall*/ CNDragonHeadSide__vmt2F4(int this)
{
  if ( *(uint8_t *)(this + 1109) != 0 )
    return sub_6298C0((uint32_t *)this, 200, 50, 1);
  else
    return sub_6298C0((uint32_t *)this, 100, 200, 0);
}



// ============================================================
// 【分区 13】观察者之眼与水晶柱（0x6299F0-0x62A100）
// 证据: BISHOP_EYE（主教之眼启动音）；CNCystalPillar（水晶柱）/ CNEyeofObserver /
//       CNActiveObserver（固定/主动观察者，视野触发体）
// ============================================================

// ------------------------------------------------------------
// 0x6299F0 CNCystalPillar__vmt2B4
// ------------------------------------------------------------
int /*thiscall*/ CNCystalPillar__vmt2B4(int *this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax
  int v8; // ebx
  int v9; // eax

  CNMapObject__vmt2B4(this, a2, a3, a4, a5, a6);
  result = sub_41ACF0(this + 260);
  if ( result != 0 )
  {
    v8 = *this;
    v9 = sub_41ACF0(this + 260);
    return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v8 + 212))(this, v9, -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x629A50 CNCystalPillar__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNCystalPillar__vmt2E4(uint32_t *this)
{
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *(uint32_t *)(*(this + 36) + 4),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x629A70 CNCystalPillar__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNCystalPillar__vmt200(int *this, int a2, float *a3, char a4)
{
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));
  return CNRDPassiveObject__vmt200(this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x629AB0 sub_629AB0
// ------------------------------------------------------------
int /*thiscall*/ sub_629AB0(uint32_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);
  *(this + 243) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x629AD0 CNEyeofObserver__vmt1D8
// ------------------------------------------------------------
int /*userpurge*/ CNEyeofObserver__vmt1D8@<eax>(uint32_t *a1@<ecx>, int a2@<ebx>, int a3, int a4, int a5, int a6)
{
  int result; // eax

  CNRDPassiveObject__vmt1D8(a1, a2, a3, a3, a4, a5, a6);
  if ( a3 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*a1 + 196))(a1, a1[34]);
  result = a3 - 2;
  if ( a3 == 2 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*a1 + 580))(
             a1,
             1051,
             0,
             0,
             0,
             0,
             0,
             0,
             4,
             0,
             0,
             0);
  return result;
}



// ------------------------------------------------------------
// 0x629B40 CNEyeofObserver__vmt14C
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNEyeofObserver__vmt14C(unsigned int *this)
{
  unsigned int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  result = *(this + 240);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 200))(this);
    if ( result == *(this + 34) )
    {
      result = sub_699000((int)(this + 9));
      if ( *(this + 243) + 1000 < result )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 708))(this) != 0
          && (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 308))(this) != 0 )
        {
          (*(void (/*thiscall*/ **)(unsigned int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);
        }
        result = sub_699000((int)(this + 9));
        *(this + 243) = result;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x629BC0 CNEyeofObserver__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNEyeofObserver__vmt12C(uint32_t *this, int a2)
{
  if ( this == (uint32_t *)a2 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  CNRDPassiveObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x629BF0 sub_629BF0
// ------------------------------------------------------------
int /*thiscall*/ sub_629BF0(uint32_t *this)
{
  int v2; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);
  v2 = *this;
  *(this + 246) = 0;
  *((uint8_t *)this + 972) = 0;
  *((uint8_t *)this + 973) = 0;
  *(this + 245) = 0;
  *(this + 244) = 0;
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v2 + 384))(this, 0);
  *(this + 170) = result;
  *(this + 171) = result;
  return result;
}



// ------------------------------------------------------------
// 0x629C40 sub_629C40
// ------------------------------------------------------------
int /*thiscall*/ sub_629C40(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 246);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 246) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x629C60 CNActiveObserver__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNActiveObserver__vmtC(int *this)
{
  CNRDPassiveObject__vmtC(this);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x629C80 CNActiveObserver__vmt1D8
//   【观察者】BISHOP_EYE —— 主教之眼启动音
// ------------------------------------------------------------
void */*userpurge*/ CNActiveObserver__vmt1D8@<eax>(int a1@<ecx>, int a2@<ebx>, int a3, int a4, int a5, int a6)
{
  void *result; // eax

  CNRDPassiveObject__vmt1D8((uint32_t *)a1, a2, a3, a3, a4, a5, a6);
  if ( a3 == 0 )
    return (void *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 196))(a1, *(uint32_t *)(a1 + 136));
  result = (void *)(a3 - 2);
  if ( a3 == 2 )
  {
    sub_4926A0(**(uint32_t **)(a1 + 144));
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 196))(a1, **(uint32_t **)(a1 + 144));
    return sub_432EA0("BISHOP_EYE", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x629D00 sub_629D00
// ------------------------------------------------------------
void /*thiscall*/ sub_629D00(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  uint8_t v8[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  float v10; // [esp+14h] [ebp-14h]
  int v11; // [esp+18h] [ebp-10h]
  int v12; // [esp+24h] [ebp-4h]

  v2 = *(this + 219);
  if ( v2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v2 + 12))(v2, 0);
    v3 = *(uint32_t *)*(this + 219);
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 192))(this);
    v4 = *this;
    v10 = (double)v11 * 0.80000001;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)((double)v11 + v10));
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v3 + 40))(*(this + 219), v6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v8);
    v7 = (void *)*(this + 29);
    v12 = 0;
    sub_4600B0(v7, 2, 0, (int)v8);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x629DD0 CNActiveObserver__vmt2B4
// ------------------------------------------------------------
void /*thiscall*/ CNActiveObserver__vmt2B4(uint32_t *this, int a2, int a3, int a4, int a5, int a6)
{
  if ( (int)*(this + 170) <= 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    sub_629D00(this);
  }
}



// ------------------------------------------------------------
// 0x629E00 sub_629E00
// ------------------------------------------------------------
char /*thiscall*/ sub_629E00(uint32_t *this, signed int a2, signed int a3)
{
  int v5; // eax
  uint32_t *v6; // edi
  int v7; // esi
  int v8; // eax
  uint8_t v10[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  uint32_t *v12; // [esp+14h] [ebp-1Ch]
  int v13; // [esp+18h] [ebp-18h]
  int v14; // [esp+1Ch] [ebp-14h]
  int v15; // [esp+20h] [ebp-10h]
  int v16; // [esp+2Ch] [ebp-4h]
  int v17; // [esp+3Ch] [ebp+Ch]

  Block = nullptr;
  v12 = nullptr;
  v13 = 0;
  v16 = 0;
  sub_4E7F30(this, a2, a3, (int)v10);
  v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v6 = Block;
  v14 = v5;
  if ( Block == v12 )
  {
LABEL_9:
    if ( v6 != nullptr )
      j__free(v6);
    return 0;
  }
  else
  {
    v15 = v17 - a2;
    while ( 1 )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 120))(*v6);
      v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 124))(*v6);
      if ( v7 >= v15 && v7 <= a2 + v17 && v8 >= v14 - a3 && v8 <= a3 + v14 )
        break;
      if ( ++v6 == v12 )
      {
        v6 = Block;
        goto LABEL_9;
      }
    }
    if ( Block != nullptr )
      j__free(Block);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x629EF0 sub_629EF0
// ------------------------------------------------------------
void /*thiscall*/ sub_629EF0(uint32_t *this)
{
  uint32_t *v2; // edi
  int v3; // ebx
  uint8_t v4[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  uint32_t *v6; // [esp+14h] [ebp-14h]
  int v7; // [esp+18h] [ebp-10h]
  int v8; // [esp+24h] [ebp-4h]

  Block = nullptr;
  v6 = nullptr;
  v7 = 0;
  v8 = 0;
  sub_4E7F30(this, 320, 120, (int)v4);
  v2 = Block;
  if ( Block != v6 )
  {
    do
    {
      v3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v2 + 120))(*v2);
      if ( v3 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 148))(this, 0);
      else
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, 1);
      ++v2;
    }
    while ( v2 != v6 );
    v2 = Block;
  }
  if ( v2 != nullptr )
    j__free(v2);
}



// ------------------------------------------------------------
// 0x629F90 sub_629F90
// ------------------------------------------------------------
char /*thiscall*/ sub_629F90(uint32_t *this, signed int a2, signed int a3, int a4)
{
  int v5; // eax
  int v6; // edx
  int v7; // eax
  uint32_t *v8; // ebx
  int v10; // edi
  int v11; // ebx
  char v12[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  uint32_t *v14; // [esp+14h] [ebp-20h]
  int v15; // [esp+18h] [ebp-1Ch]
  int v16; // [esp+1Ch] [ebp-18h]
  int v17; // [esp+20h] [ebp-14h]
  uint32_t *v18; // [esp+24h] [ebp-10h]
  int v19; // [esp+30h] [ebp-4h]

  Block = nullptr;
  v14 = nullptr;
  v15 = 0;
  v19 = 0;
  sub_4E7F30(this, a2, a3, (int)v12);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v6 = *this;
  v17 = v5;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 124))(this);
  v8 = Block;
  v16 = v7;
  v18 = Block;
  if ( Block == v14 )
  {
LABEL_2:
    if ( v8 != nullptr )
      j__free(v8);
    return 0;
  }
  else
  {
    while ( 1 )
    {
      v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v8 + 120))(*v8);
      v11 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v8 + 124))(*v8);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0
        && v10 >= v17 - a2
        && v10 < v17
        && v11 >= v16 - a3
        && v11 <= a3 + v16 )
      {
        break;
      }
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1
        && v10 <= v17 + a2
        && v10 > v17
        && v11 >= v16 - a3
        && v11 <= a3 + v16 )
      {
        break;
      }
      if ( ++v18 == v14 )
      {
        v8 = Block;
        goto LABEL_2;
      }
      v8 = v18;
    }
    if ( Block != nullptr )
      j__free(Block);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x62A0E0 CNEyeofObserver__vmt2C4
// ------------------------------------------------------------
char /*thiscall*/ CNEyeofObserver__vmt2C4(uint32_t *this)
{
  return sub_629E00(this, 320, 120);
}



// ------------------------------------------------------------
// 0x62A0F0 CNActiveObserver__vmt2C4
// ------------------------------------------------------------
char /*thiscall*/ CNActiveObserver__vmt2C4(uint32_t *this)
{
  return sub_629F90(this, 320, 120, 1);
}



// ------------------------------------------------------------
// 0x62A100 CNActiveObserver__vmt14C
// ------------------------------------------------------------
char /*usercall*/ sub_62A100@<al>(uint8_t *a1@<ecx>, int a2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  unsigned int v5; // eax
  uint32_t *v6; // edi
  int v7; // edi
  int *v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int i; // ebx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int v18; // edi
  int v19; // eax
  int v20; // edx
  int v21; // eax
  int v22; // edi
  int *v23; // edi
  int v24; // eax
  int v25; // ebx
  int v26; // eax
  int v27; // eax
  int v29; // [esp-8h] [ebp-20h]
  int v30; // [esp-4h] [ebp-1Ch]
  int v31; // [esp-4h] [ebp-1Ch]
  int v32; // [esp+8h] [ebp-10h]

  sub_600890();
  if ( a1[973] == 0 )
  {
    sub_629EF0(a1);
    a1[973] = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 128))(a1) > 50 )
  {
    v30 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 128))(a1) - 10;
    v29 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 124))(a1);
    v3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 120))(a1);
    sub_498E00(v3, v29, v30);
  }
  v4 = *((uint32_t *)a1 + 240);
  if ( v4 != 0 )
  {
    v5 = v4 - 2;
    if ( v5 == 0 )
    {
      v6 = *((uint32_t **)a1 + 36);
      v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 200))(a1);
      if ( v5 == *v6 )
      {
        v31 = a2;
        if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 200))(a1) + 170) != 0
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1) != 0 )
        {
          v7 = 0;
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)a1 + 560))(
            a1,
            0,
            0,
            0,
            0,
            a2);
          a1[972] = 0;
          if ( sub_42FCB0(228) != 0 )
            v7 = sub_431860(
                   (char)"PassiveObject/MapObject/Trap/EyeofObserver/Animation/UNDERFOOT_DarkCircleEffect.ani",
                   1);
          if ( sub_44B6C0(284) != 0 )
            v8 = (int *)sub_44E1F0(v7, 1);
          else
            v8 = nullptr;
          sub_45FE80(*((uint32_t *)a1 + 29), (int)v8, 2, 0, (int)v8, (int)a1, 0);
          v9 = *v8;
          v31 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 128))(a1);
          v10 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 124))(a1);
          v11 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 120))(a1, v10);
          (*(void (/*thiscall*/ **)(int *, int))(v9 + 112))(v8, v11);
          if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 708))(a1) != 0 )
          {
            for ( i = 0; ; ++i )
            {
              v13 = *((uint32_t *)a1 + 29);
              v14 = *(uint32_t *)(v13 + 120);
              v15 = v13 + 116;
              v16 = v14 != 0 ? (*(uint32_t *)(v15 + 8) - v14) >> 2 : 0;
              if ( i >= v16 )
                break;
              (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 80))(a1, i);
              v17 = sub_425A00(v31);
              v31 = 273;
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 40))(v17) != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int, uint8_t *, int))(*(uint32_t *)v17 + 760))(
                  v17,
                  5,
                  1120403456,
                  5,
                  a1,
                  1);
            }
          }
        }
        v18 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 200))(a1) + 148);
        v19 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 200))(a1);
        v20 = *(uint32_t *)(v19 + 44);
        if ( v20 != 0 )
          v21 = (*(uint32_t *)(v19 + 48) - v20) / 88;
        else
          v21 = 0;
        v5 = v21 - 2;
        if ( v18 == v5 )
        {
          LOBYTE(v5) = a1[972];
          if ( (uint8_t)v5 == 0 )
          {
            if ( sub_42FCB0(228) != 0 )
              v22 = sub_431860(
                      (char)"PassiveObject/MapObject/Trap/EyeofObserver/Animation/UNDERFOOT_EyeShineEffect.ani",
                      1);
            else
              v22 = 0;
            if ( sub_44B6C0(284) != 0 )
              v23 = (int *)sub_44E1F0(v22, 1);
            else
              v23 = nullptr;
            sub_45FE80(*((uint32_t *)a1 + 29), (int)v23, 2, 0, (int)v23, (int)a1, 0);
            if ( (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 152))(a1, v31) != 0 )
              v24 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 120))(a1) + 20;
            else
              v24 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 120))(a1) - 20;
            v25 = *v23;
            v32 = v24;
            v26 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 128))(a1);
            v27 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 124))(a1, v26);
            LOBYTE(v5) = (*(int (/*thiscall*/ **)(int *, int, int))(v25 + 112))(v23, v32, v27);
            a1[972] = 1;
          }
        }
      }
    }
  }
  else
  {
    v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 200))(a1);
    if ( v5 == *((uint32_t *)a1 + 34) )
    {
      v5 = sub_699000((int)(a1 + 36));
      if ( *((uint32_t *)a1 + 245) + 5000 < v5 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 708))(a1) != 0
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 308))(a1) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)a1 + 560))(a1, 2, 0, 0, 0);
        }
        v5 = sub_699000((int)(a1 + 36));
        *((uint32_t *)a1 + 245) = v5;
      }
    }
  }
  return v5;
}


// ============================================================
// 【分区 14】灯泡/露滴/冻结月神（0x62A470-0x62A8B0）
// 证据: Particle/light.ptl（灯泡发光粒子）；CNWaterDrop（水滴）/ CNFreezingLuna（冻结月神）
// ============================================================

// ------------------------------------------------------------
// 0x62A470 CNLightBulb__vmt140
// ------------------------------------------------------------
void /*thiscall*/ CNLightBulb__vmt140(int *this)
{
  int v2; // edi
  int v3; // edx
  void *v4; // eax
  int v5; // [esp-10h] [ebp-30h]
  int v6; // [esp-Ch] [ebp-2Ch]
  int v7; // [esp-8h] [ebp-28h]
  uint8_t v8[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v10; // [esp+1Ch] [ebp-4h]

  CNRDPassiveObject__vmt140(this);
  if ( *((uint8_t *)this + 276) != 0 )
  {
    v2 = *(uint32_t *)*(this + 243);
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    (*(void (/*thiscall*/ **)(uint32_t))(v2 + 40))(*(this + 243));
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v8);
    v3 = *this;
    v10 = 0;
    v4 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v3 + 80))(this, 2, 0, v8);
    sub_4600B0(v4, v5, v6, v7);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x62A520 sub_62A520
//   【灯泡】Particle/light.ptl —— 灯光粒子
// ------------------------------------------------------------
int /*thiscall*/ sub_62A520(uint32_t *this)
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/light.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/light.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 243) = result;
  return result;
}



// ------------------------------------------------------------
// 0x62A5B0 sub_62A5B0
// ------------------------------------------------------------
int /*thiscall*/ sub_62A5B0(uint32_t *this)
{
  int v2; // eax
  int v4; // et2
  int v5; // [esp+4h] [ebp-4h] BYREF

  v5 = rand();
  v2 = sub_4D33A0(&v5);
  v4 = v2 % 30;
  *(this + 244) = 0;
  *(this + 243) = 200 * (v4 + 5);
  return v2 / 30;
}



// ------------------------------------------------------------
// 0x62A600 CNWaterDrop__vmt14C
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNWaterDrop__vmt14C(uint32_t *this)
{
  unsigned int result; // eax
  int v3; // eax

  CNRDPassiveObject__vmt14C((int)this);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = sub_699000((int)(this + 9));
    if ( *(this + 244) + *(this + 243) < result )
    {
      *(this + 244) = 200 * (rand() % 30 + 5);
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
      sub_4926A0(v3);
      result = sub_699000((int)(this + 9));
      *(this + 243) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62A680 CNFreezingLuna__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNFreezingLuna__vmtC(int *this)
{
  int result; // eax

  CNMapObject__vmtC(this);
  result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0);
  *(this + 170) = result;
  *(this + 171) = result;
  return result;
}



// ------------------------------------------------------------
// 0x62A6B0 sub_62A6B0
// ------------------------------------------------------------
int /*thiscall*/ sub_62A6B0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 282);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(this + 282) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x62A6D0 sub_62A6D0
// ------------------------------------------------------------
int /*thiscall*/ sub_62A6D0(int *this)
{
  int result; // eax
  int v3; // ebx
  uint32_t *v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // [esp-1Ch] [ebp-28h]
  int v9; // [esp+4h] [ebp-8h]
  int v10; // [esp+8h] [ebp-4h]

  *(this + 279) = sub_699000((int)(this + 9));
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 80))(this) + 132) + 108) + 112);
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
    *(this + 280) = sub_460230(v4);
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + 1;
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v8 = *(this + 280);
    v10 = v6;
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
    IRDCollisionObject__vmt250(this, v3, (int)this, 600, 100, v3, v9, v5, v10, v7, 0, nullptr, 0, v8, 0, 0, 0, 0);
    result = *(this + 281) + 1;
    *(this + 281) = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62A790 CNFreezingLuna__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNFreezingLuna__vmt14C(int *this)
{
  unsigned int v2; // eax
  int v3; // ecx

  LOBYTE(v2) = CNMapObject__vmt14C(this);
  v3 = *(this + 276);
  if ( (v3 == 0 || (v2 = (*(this + 277) - v3) >> 2) < 2) && *(this + 281) < 4 )
  {
    v2 = sub_699000((int)(this + 9));
    if ( *(this + 279) + 6000 < v2 )
      LOBYTE(v2) = sub_62A6D0(this);
  }
  return v2;
}



// ------------------------------------------------------------
// 0x62A7E0 CNFreezingLuna__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNFreezingLuna__vmt2F4(void **this, int a2)
{
  int (/*thiscall*/ **v3)(void **, int); // eax
  int result; // eax

  if ( *(this + 276) != nullptr )
    j__free(*(this + 276));
  *(this + 276) = nullptr;
  *(this + 277) = nullptr;
  *(this + 278) = nullptr;
  v3 = (int (/*thiscall*/ **)(void **, int))*this;
  *(this + 280) = (void *)0xFFFF;
  *(this + 281) = nullptr;
  *(this + 279) = nullptr;
  result = v3[93](this, 100);
  *(this + 169) = (void *)1;
  return result;
}



// ------------------------------------------------------------
// 0x62A840 CNFreezingLuna__vmt140
// ------------------------------------------------------------
int /*thiscall*/ CNFreezingLuna__vmt140(int this)
{
  CNRDPassiveObject__vmt140((uint8_t *)this);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, **(uint32_t **)(this + 144));
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
           this,
           100,
           **(uint32_t **)(this + 144),
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x62A880 sub_62A880
// ------------------------------------------------------------
int /*thiscall*/ sub_62A880(uint32_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  *(this + 170) = result;
  *(this + 171) = result;
  return result;
}



// ------------------------------------------------------------
// 0x62A8B0 sub_62A8B0
// ------------------------------------------------------------
void /*thiscall*/ sub_62A8B0(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  uint8_t v8[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  float v10; // [esp+14h] [ebp-14h]
  int v11; // [esp+18h] [ebp-10h]
  int v12; // [esp+24h] [ebp-4h]

  v2 = *(this + 219);
  if ( v2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v2 + 12))(v2, 0);
    v3 = *(uint32_t *)*(this + 219);
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 192))(this);
    v4 = *this;
    v10 = (double)v11 * 0.80000001;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)((double)v11 + v10));
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v3 + 40))(*(this + 219), v6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v8);
    v7 = (void *)*(this + 29);
    v12 = 0;
    sub_4600B0(v7, 2, 0, (int)v8);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ============================================================
// 【分区 15】十字架/骸骨堆/蜘蛛卵/双子箱（0x62A980-0x62B820）
// 证据: CROSS_CRASH（十字架碎裂）、Monster/Ghoul/Particle/GhoulThrowerSkull.ptl（掷颅）、
//       0x62B360 = 属性投掷粒子选择器（FastThrowStone/IceMissile/FireMissile/AimingBomb.ptl，
//       与哥布林掩体 0x6252D0 同构复用）
// ============================================================

// ------------------------------------------------------------
// 0x62A980 CNTreeCross__vmt2B4
//   【十字架】CROSS_CRASH —— 十字架碎裂
// ------------------------------------------------------------
int /*thiscall*/ CNTreeCross__vmt2B4(int this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax

  result = *(uint32_t *)(this + 680);
  if ( result <= 0 )
  {
    sub_62A8B0((uint32_t *)this);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 676))(this, 0);
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
             this,
             "CROSS_CRASH",
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62A9D0 CNSkeletonPile__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNSkeletonPile__vmt2E4(int *this)
{
  int v2; // eax
  int result; // eax

  v2 = *this;
  *(this + 24) = 545;
  result = (*(int (/*stdcall*/ **)(int))(v2 + 372))(100);
  *(this + 275) = 5;
  return result;
}



// ------------------------------------------------------------
// 0x62A9F0 sub_62A9F0
//   【骸骨堆】Monster/Ghoul/Particle/GhoulThrowerSkull.ptl —— 食尸鬼掷颅粒子
// ------------------------------------------------------------
int /*thiscall*/ sub_62A9F0(int *this)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  uint32_t v5[26]; // [esp+4h] [ebp-68h] BYREF

  v5[25] = dword_796E50;
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 275);
    if ( result > 0 )
    {
      sub_423A20((int)v5);
      qmemcpy(
        v5,
        (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(
                        this,
                        "../../../Monster/Ghoul/Particle/GhoulThrowerSkull.ptl"),
        0x62u);
      v5[18] = 0;
      v3 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);
      v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v3 + 196) + 152))(*(uint32_t *)(v3 + 196));
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
               this,
               30095,
               0,
               v5,
               0,
               4,
               0,
               40,
               v4,
               0,
               0,
               0);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62AAA0 CNSkeletonPile__vmt12C
// ------------------------------------------------------------
char /*thiscall*/ CNSkeletonPile__vmt12C(uint32_t *this, int a2)
{
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  return CNMapObject__vmt12C(this, a2);
}



// ------------------------------------------------------------
// 0x62AAD0 CNSkeletonPile__vmt200
// ------------------------------------------------------------
int /*thiscall*/ CNSkeletonPile__vmt200(int this, int a2, float *a3, char a4)
{
  int v5; // eax

  sub_62A9F0((int *)this);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
  {
    v5 = *(uint32_t *)(this + 1100);
    if ( v5 <= 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    }
    else
    {
      if ( v5 == 1 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, **(uint32_t **)(this + 144));
      --*(uint32_t *)(this + 1100);
    }
  }
  return CNRDPassiveObject__vmt200((int *)this, a2, a3, a4);
}



// ------------------------------------------------------------
// 0x62AB40 CNSkeletonPile__vmt140
// ------------------------------------------------------------
char /*thiscall*/ CNSkeletonPile__vmt140(uint8_t *this)
{
  if ( *(this + 276) != 0 )
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
      this,
      100,
      **((uint32_t **)this + 36),
      -4,
      -40,
      0,
      0);
  return CNRDPassiveObject__vmt140(this);
}



// ------------------------------------------------------------
// 0x62AB70 CNSpiderSpawn__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNSpiderSpawn__vmt2E4(uint32_t *this)
{
  int v2; // eax
  int result; // eax

  v2 = *this;
  *(this + 24) = 545;
  result = (*(int (/*stdcall*/ **)(int))(v2 + 372))(100);
  *((uint8_t *)this + 1112) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x62AB90 CNSpiderSpawn__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNSpiderSpawn__vmtC(uint32_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 6);
  *(this + 170) = result;
  *(this + 171) = result;
  return result;
}



// ------------------------------------------------------------
// 0x62ABB0 CNSpaceFishBug__vmt2B4
// ------------------------------------------------------------
int /*thiscall*/ CNSpaceFishBug__vmt2B4(int *this, int a2, int a3, int a4, int a5, int a6)
{
  int result; // eax

  result = *(this + 170);
  if ( result <= 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62ABF0 CNSpiderSpawn__vmt128
// ------------------------------------------------------------
int /*thiscall*/ CNSpiderSpawn__vmt128(int *this, int a2)
{
  int v2; // edi
  int *v3; // ebx
  int result; // eax

  v2 = 0;
  v3 = this + 279;
  do
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)a2 + 40))(a2, 529);
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2);
      if ( result == *(v3 - 4) )
      {
        result = __RTDynamicCast(a2, 0, &CNRDObject `RTTI Type Descriptor', &CNYoungSpider `RTTI Type Descriptor', 0);
        if ( result != 0 )
        {
          *v3 = result;
          *(uint32_t *)(result + 8636) = v2;
        }
      }
    }
    ++v2;
    ++v3;
  }
  while ( v2 < 3 );
  return result;
}



// ------------------------------------------------------------
// 0x62AC50 sub_62AC50
// ------------------------------------------------------------
int /*userpurge*/ sub_62AC50@<eax>(int *a1@<ecx>, int a2@<edi>, int a3)
{
  int result; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // edx
  unsigned int i; // ebx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // edi
  int v19; // edi
  int *v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // [esp-1Ch] [ebp-40h]
  int v25; // [esp+4h] [ebp-20h]
  int v26; // [esp+8h] [ebp-1Ch]
  int v27; // [esp+Ch] [ebp-18h]
  int v28; // [esp+10h] [ebp-14h]
  int v29; // [esp+14h] [ebp-10h]
  int v30; // [esp+18h] [ebp-Ch]
  int v31; // [esp+1Ch] [ebp-8h]
  int v32; // [esp+20h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*a1 + 308))(a1);
  if ( (uint8_t)result == 0 )
    return result;
  v31 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1) + 132) + 108) + 112);
  if ( a3 == 2 )
  {
    for ( i = 0; ; ++i )
    {
      while ( 1 )
      {
        v12 = a1[29];
        v13 = *(uint32_t *)(v12 + 120);
        v14 = v12 + 116;
        if ( v13 != 0 )
          v15 = (*(uint32_t *)(v14 + 8) - v13) >> 2;
        else
          v15 = 0;
        if ( (int)i >= v15 )
        {
          v25 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1) - 25;
          v26 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1) + 25;
          goto LABEL_20;
        }
        v16 = (*(int (/*thiscall*/ **)(int *, int))(*a1 + 80))(a1, a2);
        v17 = *(uint32_t *)(v16 + 120);
        if ( v17 != 0 && i < (*(uint32_t *)(v16 + 124) - v17) >> 2 )
          v18 = *(uint32_t *)(v17 + 4 * i);
        else
          v18 = 0;
        a2 = 273;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 40))(v18) != 0 )
          break;
LABEL_18:
        ++i;
      }
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v18 + 152))(v18) != 0 )
      {
        v29 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1) + 25;
        v28 = v29;
        goto LABEL_18;
      }
      v29 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1) - 25;
      v28 = v29;
    }
  }
  if ( a3 == 3 )
  {
    v5 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1);
    v6 = *a1;
    v28 = v5 - 25;
    v29 = (*(int (/*thiscall*/ **)(int *))(v6 + 120))(a1);
    v7 = (*(int (/*thiscall*/ **)(int *))(*a1 + 120))(a1);
    v8 = *a1;
    v30 = v7 + 25;
    v25 = (*(int (/*thiscall*/ **)(int *))(v8 + 124))(a1) + 25;
    v9 = (*(int (/*thiscall*/ **)(int *))(*a1 + 124))(a1);
    v10 = *a1;
    v26 = v9 - 25;
    v27 = (*(int (/*thiscall*/ **)(int *))(v10 + 124))(a1) + 25;
  }
LABEL_20:
  v32 = (*(int (/*thiscall*/ **)(int *))(*a1 + 128))(a1);
  result = a3;
  v19 = 0;
  if ( a3 > 0 )
  {
    v20 = a1 + 275;
    do
    {
      v21 = (*(int (/*thiscall*/ **)(int *))(*a1 + 80))(a1);
      v23 = sub_460230(v21);
      *v20 = v23;
      v22 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);
      sub_4E5030(
        a1,
        (int)v20,
        (int)a1,
        430,
        100,
        v31,
        *(&v28 + v19),
        *(&v25 + v19),
        v32,
        v22,
        0,
        nullptr,
        0,
        v23,
        0,
        0,
        0,
        0);
      result = a3;
      ++v19;
      ++v20;
    }
    while ( v19 < a3 );
  }
  return result;
}


// ------------------------------------------------------------
// 0x62AE00 CNSpiderSpawn__vmt200
// ------------------------------------------------------------
int /*userpurge*/ CNSpiderSpawn__vmt200@<eax>(int *a1@<ecx>, int a2@<edi>, int a3, float *a4, char a5)
{
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*a1 + 196))(a1, *(uint32_t *)(a1[36] + 4));
  if ( *((uint8_t *)a1 + 1112) == 0 )
  {
    sub_62AC50(a1, a2, 2);
    *((uint8_t *)a1 + 1112) = 1;
  }
  return CNRDPassiveObject__vmt200(a1, a3, a4, a5);
}



// ------------------------------------------------------------
// 0x62AE50 sub_62AE50
// ------------------------------------------------------------
char /*thiscall*/ sub_62AE50(uint32_t *this, signed int a2, signed int a3)
{
  int v5; // eax
  uint32_t *v6; // edi
  int v7; // esi
  int v8; // eax
  uint8_t v10[4]; // [esp+Ch] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-20h]
  uint32_t *v12; // [esp+14h] [ebp-1Ch]
  int v13; // [esp+18h] [ebp-18h]
  int v14; // [esp+1Ch] [ebp-14h]
  int v15; // [esp+20h] [ebp-10h]
  int v16; // [esp+2Ch] [ebp-4h]
  int v17; // [esp+3Ch] [ebp+Ch]

  Block = nullptr;
  v12 = nullptr;
  v13 = 0;
  v16 = 0;
  sub_4E7F30(this, a2, a3, (int)v10);
  v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
  v6 = Block;
  v14 = v5;
  if ( Block == v12 )
  {
LABEL_9:
    if ( v6 != nullptr )
      j__free(v6);
    return 0;
  }
  else
  {
    v15 = v17 - a2;
    while ( 1 )
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 120))(*v6);
      v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*v6 + 124))(*v6);
      if ( v7 >= v15 && v7 <= a2 + v17 && v8 >= v14 - a3 && v8 <= a3 + v14 )
        break;
      if ( ++v6 == v12 )
      {
        v6 = Block;
        goto LABEL_9;
      }
    }
    if ( Block != nullptr )
      j__free(Block);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x62AF40 CNSpiderSpawn__vmt14C
// ------------------------------------------------------------
char /*usercall*/ CNSpiderSpawn__vmt14C@<al>(int a1@<ecx>, int a2@<edi>)
{
  if ( sub_62AE50((uint32_t *)a1, 300, 300) == 1 && *(uint8_t *)(a1 + 1112) == 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)a1 + 196))(a1, *(uint32_t *)(*(uint32_t *)(a1 + 144) + 4));
    *(uint8_t *)(a1 + 1112) = 1;
    sub_62AC50((int *)a1, a2, 3);
  }
  return CNMapObject__vmt14C((int *)a1);
}



// ------------------------------------------------------------
// 0x62AF90 CN2StoryBox__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CN2StoryBox__vmt2E4(uint8_t *this)
{
  int v2; // eax
  int result; // eax

  v2 = *(uint32_t *)this;
  *(this + 1104) = 0;
  result = (*(int (/*stdcall*/ **)(int))(v2 + 372))(100);
  *(this + 1105) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x62AFD0 CN2StoryBox__vmtC
// ------------------------------------------------------------
char /*thiscall*/ CN2StoryBox__vmtC(int *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  unsigned int v6; // eax
  int v7; // eax

  CNMapObject__vmtC(this);
  v2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 7);
  v3 = *this;
  *(this + 170) = v2;
  *(this + 171) = v2;
  *(this + 275) = (*(int (/*thiscall*/ **)(int *, int))(v3 + 384))(this, 8);
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);
  v5 = *(uint32_t *)(v4 + 32);
  v6 = v4 + 28;
  if ( v5 != 0 )
  {
    v6 = (*(uint32_t *)(v6 + 8) - v5) >> 2;
    if ( v6 >= 7 )
    {
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);
      LOBYTE(v6) = sub_43BCF0((void *)(*(uint32_t *)(v7 + 32) + 24), "Left");
      if ( (uint8_t)v6 != 0 )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 148))(this, 0);
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x62B060 sub_62B060
// ------------------------------------------------------------
void /*thiscall*/ sub_62B060(uint32_t *this)
{
  int v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *v7; // ecx
  uint8_t v8[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  float v10; // [esp+14h] [ebp-14h]
  int v11; // [esp+18h] [ebp-10h]
  int v12; // [esp+24h] [ebp-4h]

  v2 = *(this + 219);
  if ( v2 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v2 + 12))(v2, 0);
    v3 = *(uint32_t *)*(this + 219);
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 192))(this);
    v4 = *this;
    v10 = (double)v11 * 0.80000001;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 128))(this);
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)((double)v11 + v10));
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v3 + 40))(*(this + 219), v6);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v8);
    v7 = (void *)*(this + 29);
    v12 = 0;
    sub_4600B0(v7, 2, 0, (int)v8);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// ------------------------------------------------------------
// 0x62B130 CN2StoryBox__vmt2B4
// ------------------------------------------------------------
void /*thiscall*/ CN2StoryBox__vmt2B4(uint32_t **this, int a2, int a3, int a4, int a5, int a6)
{
  int v7; // ebx
  int v8; // eax
  int v9; // ebx
  int v10; // eax

  if ( (int)*(this + 170) <= (int)*(this + 275) && *((uint8_t *)this + 1104) == 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 36));
    sub_62B060(this);
    *((uint8_t *)this + 1104) = 1;
    if ( sub_41ACF0(this + 260) != 0 )
    {
      v7 = (int)*this;
      v8 = sub_41ACF0(this + 260);
      (*(void (/*thiscall*/ **)(uint32_t **, int, int, uint32_t, uint32_t))(v7 + 212))(this, v8, -1, 0, 0);
    }
  }
  if ( (int)*(this + 170) <= 0 )
  {
    if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
    {
      if ( sub_41ACF0(this + 260) != 0 )
      {
        v9 = (int)*this;
        v10 = sub_41ACF0(this + 260);
        (*(void (/*thiscall*/ **)(uint32_t **, int, int, uint32_t, uint32_t))(v9 + 212))(this, v10, -1, 0, 0);
      }
      ((void (/*thiscall*/ *)(uint32_t **))(*this)[186])(this);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[78])(this, 0);
    }
    sub_62B060(this);
  }
  if ( *(this + 240) == (uint32_t *)2 && ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[140])(this, 0, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x62B230 sub_62B230
// ------------------------------------------------------------
char /*thiscall*/ sub_62B230(uint32_t *this, signed int a2, signed int a3, char a4)
{
  int v5; // eax
  int *v6; // edi
  int v7; // ecx
  int v8; // ebx
  int v10; // ebx
  uint8_t v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int *v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]
  int v16; // [esp+34h] [ebp+Ch]

  Block = nullptr;
  v13 = nullptr;
  v14 = 0;
  v15 = 0;
  sub_4E7F30(this, a2, a3, (int)v11);
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
  v6 = (int *)Block;
  v16 = v5;
  if ( Block != v13 )
  {
    while ( 1 )
    {
      v7 = *v6;
      if ( a4 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 120))(v7);
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
        {
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 && v8 >= v16 )
          {
LABEL_5:
            if ( Block != nullptr )
              j__free(Block);
            return 1;
          }
        }
        else if ( v8 <= v16 )
        {
          goto LABEL_5;
        }
      }
      else
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 124))(v7);
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) < v10 )
          goto LABEL_5;
      }
      if ( ++v6 == v13 )
      {
        v6 = (int *)Block;
        break;
      }
    }
  }
  if ( v6 != nullptr )
    j__free(v6);
  return 0;
}



// ------------------------------------------------------------
// 0x62B330 CN2StoryBox__vmt2F4
// ------------------------------------------------------------
char /*thiscall*/ CN2StoryBox__vmt2F4(int this)
{
  if ( *(uint8_t *)(this + 1105) != 0 )
    return sub_62B230((uint32_t *)this, 200, 50, 1);
  else
    return sub_62B230((uint32_t *)this, 100, 200, 0);
}



// ------------------------------------------------------------
// 0x62B360 sub_62B360
//   【双子箱】属性投掷粒子四选一（同 0x6252D0）：FastThrowStone/IceMissile/FireMissile/AimingBomb
// ------------------------------------------------------------
int /*userpurge*/ sub_62B360@<eax>(uint32_t *a1@<ecx>, int a2@<esi>, int a3)
{
  int result; // eax
  int v5; // esi
  const void *v6; // esi
  int v7; // eax
  const void *v8; // esi
  int v9; // eax
  uint64_t v10; // rax
  int v11; // ecx
  const void *v12; // esi
  int v13; // eax
  int v14; // esi
  uint32_t v16[11]; // [esp+8h] [ebp-98h] BYREF
  int v17; // [esp+34h] [ebp-6Ch]
  uint32_t v18[26]; // [esp+38h] [ebp-68h] BYREF

  v18[25] = dword_796E50;
  result = a3;
  if ( a3 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*a1 + 308))(a1);
    if ( (uint8_t)result != 0 )
    {
      v16[4] = 1;
      v16[5] = 1;
      v16[6] = 1;
      memset(v16, 0, 16);
      v16[7] = 2;
      v16[8] = 2;
      v16[9] = 3;
      v5 = rand() % 10;
      sub_423A20(v18);
      result = v16[v5];
      switch ( result )
      {
        case 0:
          v6 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*a1 + 588))(
                               a1,
                               "Particle/FastThrowStone.ptl",
                               a2);
          v7 = *a1;
          qmemcpy(v18, v6, 0x62u);
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v7 + 164))(a1, a3, 0);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 580))(
                     a1,
                     1048,
                     0,
                     v18,
                     0,
                     0,
                     10,
                     50,
                     1,
                     0,
                     0);
          break;
        case 1:
          v8 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*a1 + 588))(
                               a1,
                               "Particle/IceMissile.ptl",
                               a2);
          v9 = *a1;
          qmemcpy(v18, v8, 0x62u);
          v10 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v9 + 164))(a1, a3, 0);
          v18[18] = v10;
          v11 = 1;
          if ( (int)v10 >= 90 && (int)v10 < 270 )
          {
            v11 = 0;
            v18[18] = 180 - v10;
          }
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 580))(
                     a1,
                     42001,
                     *(uint32_t *)(a1[87] + 36),
                     v18,
                     0,
                     0,
                     10,
                     50,
                     v11,
                     0,
                     0);
          break;
        case 2:
          v12 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*a1 + 588))(
                                a1,
                                "Particle/FireMissile.ptl",
                                a2);
          v13 = *a1;
          qmemcpy(v18, v12, 0x62u);
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v13 + 164))(a1, a3, 0);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 580))(
                     a1,
                     40001,
                     *(uint32_t *)(a1[87] + 40),
                     v18,
                     0,
                     0,
                     10,
                     50,
                     1,
                     0,
                     0);
          break;
        case 3:
          if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*a1 + 8))(a1, a3, 0, a2) >= 250 )
            v17 = 250;
          else
            v17 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*a1 + 8))(a1, a3, 0);
          qmemcpy(
            v18,
            (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*a1 + 588))(a1, "Particle/AimingBomb.ptl"),
            0x62u);
          v16[10] = 2 * *(uint32_t *)((char *)&v18[7] + 3);
          v14 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v18[7] + 3)) / (double)v18[17] * 1000.0);
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(*a1 + 164))(a1, a3, 0);
          BYTE1(v18[22]) = 3;
          *(uint32_t *)((char *)&v18[3] + 3) = 1000 * v17 / v14;
          *(uint32_t *)((char *)&v18[4] + 3) = *(uint32_t *)((char *)&v18[3] + 3);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*a1 + 580))(
                     a1,
                     30021,
                     0,
                     v18,
                     0,
                     0,
                     10,
                     50,
                     1,
                     0,
                     0);
          break;
        default:
          return result;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x62B610 sub_62B610
// ------------------------------------------------------------
int /*thiscall*/ sub_62B610(uint32_t *this)
{
  int i; // esi
  int result; // eax

  for ( i = 8; i < 48; i += 4 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(i + *(this + 36)));
    result = sub_4926A0(*(uint32_t *)(*(this + 36) + i));
  }
  return result;
}



// ------------------------------------------------------------
// 0x62B650 sub_62B650
// ------------------------------------------------------------
void /*thiscall*/ sub_62B650(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  void *v5; // ecx
  uint8_t v6[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int v8; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  sub_62B610((uint32_t *)this);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 16));
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
    this,
    100,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 40),
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 1108) + 12))(*(uint32_t *)(this + 1108), 0);
  v2 = **(uint32_t **)(this + 1108);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 192))(this);
  v3 = (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 124))(
         this,
         (uint64_t)((double)v8 * 0.69999999) >> 32,
         (uint64_t)((double)v8 * 0.69999999));
  v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v3 + 2);
  (*(void (/*thiscall*/ **)(uint32_t, int))(v2 + 40))(*(uint32_t *)(this + 1108), v4);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 1108) + 92))(*(uint32_t *)(this + 1108), v6);
  v5 = *(void **)(this + 116);
  v9 = 0;
  sub_4600B0(v5, 2, 0, (int)v6);
  if ( Block != nullptr )
    j__free(Block);
}



// ------------------------------------------------------------
// 0x62B740 sub_62B740
// ------------------------------------------------------------
int /*thiscall*/ sub_62B740(int *this)
{
  int v2; // edx
  int v3; // eax
  uint32_t *v4; // eax

  sub_62B610(this);
  v2 = *this;
  v3 = *(this + 36);
  if ( *((uint8_t *)this + 1100) == 1 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 20));
    v4 = (uint32_t *)(*(this + 36) + 44);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 12));
    v4 = (uint32_t *)(*(this + 36) + 32);
  }
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *v4,
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x62B7B0 sub_62B7B0
// ------------------------------------------------------------
int /*thiscall*/ sub_62B7B0(int *this)
{
  int v2; // edx
  int v3; // eax
  uint32_t *v4; // eax

  sub_62B610(this);
  v2 = *this;
  v3 = *(this + 36);
  if ( *((uint8_t *)this + 1100) == 1 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 16));
    v4 = (uint32_t *)(*(this + 36) + 40);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 8));
    v4 = (uint32_t *)(*(this + 36) + 28);
  }
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *v4,
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x62B820 sub_62B820
// ------------------------------------------------------------
int /*thiscall*/ sub_62B820(int *this)
{
  int v2; // edx
  int v3; // eax
  uint32_t *v4; // eax

  sub_62B610(this);
  v2 = *this;
  v3 = *(this + 36);
  if ( *((uint8_t *)this + 1100) == 1 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 16));
    v4 = (uint32_t *)(*(this + 36) + 36);
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(v3 + 8));
    v4 = (uint32_t *)(*(this + 36) + 24);
  }
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
           this,
           100,
           *v4,
           0,
           0,
           0,
           0);
}



// ============================================================
// 【分区 16】格伦塞洛斯掩体（CNGrenselosBunker，0x62B890-0x62C120）
// 证据: BUNKER_HIT / BUNKER_BREAK / BUNKER_OPEN + GBN_FRIGHT + Heal.ani
//       （与分区 8 哥布林掩体同一套 TAG，不同贴图/对象类）
// ============================================================

// ------------------------------------------------------------
// 0x62B890 CNGrenselosBunker__vmt2B4
//   【掩体·格伦】BUNKER_HIT / BUNKER_BREAK / GBN_FRIGHT（与哥布林掩体同 TAG）
// ------------------------------------------------------------
int /*thiscall*/ CNGrenselosBunker__vmt2B4(int this, int a2, int a3, int a4, int a5, int a6)
{
  int v7; // ecx
  int result; // eax

  (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "BUNKER_HIT", -1, 0, 0);
  v7 = *(uint32_t *)(this + 680);
  if ( v7 > 0 )
  {
    if ( *(uint8_t *)(this + 1100) == 0 && v7 < *(uint32_t *)(this + 684) / 2 )
    {
      sub_62B650(this);
      *(uint8_t *)(this + 1100) = 1;
    }
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);
    if ( (uint8_t)result != 0 )
      result = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 3, 0, 0, 0);
  }
  else
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
      this,
      "BUNKER_BREAK",
      -1,
      0,
      0);
    result = *(uint32_t *)(this + 1080);
    if ( result != 0 )
    {
      result = (*(uint32_t *)(this + 1084) - result) / 12;
      if ( result != 0 )
        result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
                   this,
                   "GBN_FRIGHT",
                   -1,
                   0,
                   0);
    }
  }
  if ( *(uint8_t *)(this + 1100) == 1 )
  {
    result = *(uint32_t *)(this + 684) / 2;
    if ( *(uint32_t *)(this + 680) >= result )
    {
      *(uint8_t *)(this + 1100) = 0;
      return sub_62B7B0((int *)this);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62B9A0 sub_62B9A0
// ------------------------------------------------------------
void /*thiscall*/ sub_62B9A0(uint32_t *this)
{
  int v2; // esi
  int v3; // eax
  int v4; // edx
  int v5; // esi
  bool v6; // bl
  unsigned int i; // esi
  uint8_t v8[4]; // [esp+8h] [ebp-30h] BYREF
  void *v9; // [esp+Ch] [ebp-2Ch]
  int v10; // [esp+10h] [ebp-28h]
  int v11; // [esp+14h] [ebp-24h]
  uint8_t v12[4]; // [esp+18h] [ebp-20h] BYREF
  void *Block; // [esp+1Ch] [ebp-1Ch]
  int v14; // [esp+20h] [ebp-18h]
  int v15; // [esp+24h] [ebp-14h]
  int v16; // [esp+28h] [ebp-10h] BYREF
  int v17; // [esp+34h] [ebp-4h]

  v2 = (int)(this + 9);
  if ( *(this + 276) + 1000 <= (unsigned int)sub_699000((int)(this + 9)) )
  {
    v3 = sub_699000(v2);
    v4 = *this;
    *(this + 276) = v3;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v4 + 308))(this) != 0 && rand() % 100 <= 30 )
    {
      v9 = nullptr;
      v10 = 0;
      v11 = 0;
      v17 = 0;
      v5 = sub_4E7F30(this, 250, 75, (int)v8);
      if ( v5 != 0 )
      {
        v6 = rand() % 100 > 10;
        Block = nullptr;
        v14 = 0;
        v15 = 0;
        LOBYTE(v17) = 1;
        if ( v6 )
        {
          v16 = 1;
          sub_431230((int)v12, &v16);
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 48))(v5);
          sub_431230((int)v12, &v16);
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v5 + 52))(v5);
          sub_431230((int)v12, &v16);
        }
        else
        {
          if ( v9 != nullptr )
            v16 = (v10 - (int)v9) >> 2;
          else
            v16 = 0;
          sub_431230((int)v12, &v16);
          for ( i = 0; v9 != nullptr && i < (v10 - (int)v9) >> 2; ++i )
          {
            v16 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v9 + i) + 48))(*((uint32_t *)v9 + i));
            sub_431230((int)v12, &v16);
            v16 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v9 + i) + 52))(*((uint32_t *)v9 + i));
            sub_431230((int)v12, &v16);
          }
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 2, v12, 0, 0);
        if ( Block != nullptr )
          j__free(Block);
      }
      if ( v9 != nullptr )
        j__free(v9);
    }
  }
}



// ------------------------------------------------------------
// 0x62BB60 CNGrenselosBunker__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNGrenselosBunker__vmt2E4(int this)
{
  int v2; // ecx
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax

  *(uint32_t *)(this + 676) = 1;
  *(uint32_t *)(this + 96) = 545;
  *(uint8_t *)(this + 1100) = 0;
  *(uint32_t *)(this + 1104) = sub_699000(this + 36);
  sub_62B7B0((int *)this);
  if ( operator new(0x12Cu) != nullptr )
  {
    v2 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 672))(this) + 32) + 24;
    if ( *(uint32_t *)(this + 384) < 0x10u )
      v3 = this + 364;
    else
      v3 = *(uint32_t *)(this + 364);
    v4 = sub_41ACF0(v2);
    v5 = sub_4C3640(v3, v4, this);
  }
  else
  {
    v5 = 0;
  }
  v6 = *(uint32_t *)this;
  *(uint32_t *)(this + 1108) = v5;
  (*(void (/*thiscall*/ **)(int, int))(v6 + 372))(this, 100);
  if ( *(uint32_t *)(this + 1120) != 0 )
    j__free(*(void **)(this + 1120));
  *(uint32_t *)(this + 1120) = 0;
  *(uint32_t *)(this + 1124) = 0;
  *(uint32_t *)(this + 1128) = 0;
  v7 = *(uint32_t *)this;
  *(uint32_t *)(this + 1112) = 0;
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(v7 + 472))(this, 6, 0, 1, 1);
}



// ------------------------------------------------------------
// 0x62BC70 CNGrenselosBunker__vmt14C
// ------------------------------------------------------------
void /*thiscall*/ CNGrenselosBunker__vmt14C(uint32_t *this)
{
  int v2; // eax
  int v3; // eax
  char v4; // cl
  int i; // edi
  int v6; // eax

  v2 = *(this + 240);
  if ( v2 != 0 )
  {
    v3 = v2 - 2;
    if ( v3 != 0 )
    {
      if ( v3 == 1
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
        && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      }
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
           && ((v4 = *((uint8_t *)this + 1100)) == 1 && *(int *)(*(uint32_t *)(*(this + 36) + 36) + 148) >= 1
            || v4 == 0 && *(int *)(*(uint32_t *)(*(this + 36) + 24) + 148) >= 1) )
    {
      for ( i = 0; i < *(this + 278); ++i )
      {
        v6 = sub_45EBE0(
               (uint32_t *)*(this + 29),
               *(uint32_t *)(*(this + 280) + 8 * i),
               *(uint32_t *)(*(this + 280) + 8 * i + 4));
        sub_62B360(this, (int)this, v6);
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
    }
  }
  else
  {
    sub_62B9A0(this);
  }
}



// ------------------------------------------------------------
// 0x62BD70 sub_62BD70
//   【掩体·格伦】Common/CommonEffect/Animation/Heal.ani —— 治疗演出
// ------------------------------------------------------------
int /*thiscall*/ sub_62BD70(int *this)
{
  int v2; // edi
  int v3; // edx
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  char *v9; // eax
  char *v10; // edi
  int v11; // edx
  int v12; // ebx
  int v13; // eax
  int v14; // eax
  int v16; // [esp-8h] [ebp-34h]
  int v17; // [esp+0h] [ebp-2Ch]
  int v18; // [esp+4h] [ebp-28h]
  uint8_t v19[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v21; // [esp+14h] [ebp-18h]
  int v22; // [esp+18h] [ebp-14h]
  int v23; // [esp+1Ch] [ebp-10h]
  int v24; // [esp+28h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    v23 = *(this + 171);
    v2 = (uint64_t)((double)v23 * 0.2);
    Block = nullptr;
    v21 = 0;
    v22 = 0;
    v3 = *this;
    v4 = *(this + 170);
    v24 = 0;
    v23 = (*(int (/*thiscall*/ **)(int *))(v3 + 192))(this);
    v5 = (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(*this + 124))(
           this,
           (uint64_t)((double)v23 * 0.75) >> 32,
           (uint64_t)((double)v23 * 0.75));
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);
    v16 = v2 + v4;
    v7 = 0;
    sub_600920((int)v19, 0, v2, v16, v6, v17, v18);
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *))(*this + 560))(this, 1, v19);
    v24 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v21 = 0;
    v22 = 0;
  }
  else
  {
    v7 = 0;
  }
  v8 = sub_42FCB0(228);
  v23 = v8;
  v24 = 1;
  if ( v8 != 0 )
    v7 = sub_431860(v8, "Common/CommonEffect/Animation/Heal.ani", 1);
  v24 = -1;
  v9 = (char *)sub_44B6C0(284);
  v10 = v9;
  v23 = (int)v9;
  v24 = 2;
  if ( v9 != nullptr )
  {
    sub_44E0D0(v9, v7, 1);
    *(uint32_t *)v10 = &vftbl_CNRDPooledObject;
  }
  else
  {
    v10 = nullptr;
  }
  v11 = *(uint32_t *)v10;
  v24 = -1;
  (*(void (/*thiscall*/ **)(char *, int))(v11 + 72))(v10, 2);
  sub_45FE80(*(this + 29), (int)v10, 2, 0, (int)v10, (int)this, 0);
  v12 = *(uint32_t *)v10;
  v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, 40);
  v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13 + 1);
  return (*(int (/*thiscall*/ **)(char *, int))(v12 + 112))(v10, v14);
}



// ------------------------------------------------------------
// 0x62BEF0 CNGrenselosBunker__vmt1D8
//   【掩体·格伦】BUNKER_OPEN —— 开门
// ------------------------------------------------------------
int /*thiscall*/ CNGrenselosBunker__vmt1D8(int this, int a2, int a3, int a4, int a5)
{
  int result; // eax
  int v7; // edi
  int v8; // ecx
  int v9; // eax

  result = CNRDPassiveObject__vmt1D8((uint32_t *)this, a2, a3, a2, a3, a4, a5);
  switch ( a2 )
  {
    case 0:
      result = sub_62B7B0((int *)this);
      break;
    case 2:
      sub_62B820((int *)this);
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
        this,
        "BUNKER_OPEN",
        -1,
        0,
        0);
      sub_5E5260((void **)(this + 1116));
      *(uint32_t *)(this + 1112) = 0;
      result = **(uint32_t **)(a3 + 4);
      v7 = 0;
      for ( *(uint32_t *)(this + 1112) = result; v7 < result; ++v7 )
      {
        v8 = *(uint32_t *)(a3 + 4);
        v9 = *(uint32_t *)(v8 + 8 * v7 + 8);
        a5 = *(uint32_t *)(v8 + 8 * v7 + 4);
        a4 = v9;
        sub_431230(this + 1116, &a5);
        sub_431230(this + 1116, &a4);
        result = *(uint32_t *)(this + 1112);
      }
      break;
    case 3:
      result = sub_62B740((int *)this);
      break;
    case 4:
      sub_62BD70((int *)this);
      result = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62C000 sub_62C000
// ------------------------------------------------------------
int /*thiscall*/ sub_62C000(uint32_t *this, int a2, int *a3, uint32_t *a4)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int result; // eax
  int v9; // edi

  v4 = *(this + 275);
  if ( v4 != 0 )
  {
    v5 = v4 - 1;
    if ( v5 == 0 )
    {
      *a3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2) / 2;
      *a4 = 1000;
      goto LABEL_8;
    }
    if ( v5 != 1 )
      goto LABEL_8;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2);
  }
  else
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2) / 3;
  }
  *a3 = v6;
  *a4 = 1000;
LABEL_8:
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 736))(a2);
  v9 = v7 - result;
  if ( *a3 > v9 )
    *a3 = v9;
  return result;
}



// ------------------------------------------------------------
// 0x62C090 sub_62C090
// ------------------------------------------------------------
int /*thiscall*/ sub_62C090(uint32_t *this, int a2, int *a3, uint32_t *a4)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int result; // eax
  int v9; // edi

  v4 = *(this + 275);
  if ( v4 != 0 )
  {
    v5 = v4 - 1;
    if ( v5 == 0 )
    {
      *a3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2) / 2;
      *a4 = 1000;
      goto LABEL_8;
    }
    if ( v5 != 1 )
      goto LABEL_8;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2);
  }
  else
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2) / 3;
  }
  *a3 = v6;
  *a4 = 1000;
LABEL_8:
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 752))(a2);
  v9 = v7 - result;
  if ( *a3 > v9 )
    *a3 = v9;
  return result;
}



// ------------------------------------------------------------
// 0x62C120 sub_62C120
// ------------------------------------------------------------
int /*thiscall*/ sub_62C120(uint32_t *this, int a2, int *a3, int *a4, uint32_t *a5)
{
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int result; // eax
  int v11; // edi
  int v12; // [esp+20h] [ebp+14h]

  v5 = *(this + 275);
  if ( v5 == 0 )
  {
    *a3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2) / 3;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2) / 3;
    goto LABEL_7;
  }
  v6 = v5 - 1;
  if ( v6 == 0 )
  {
    *a3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2) / 2;
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2) / 2;
LABEL_7:
    *a4 = v7;
    *a5 = 1000;
    goto LABEL_8;
  }
  if ( v6 == 1 )
  {
    *a3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2);
    *a4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2);
    *a5 = 1000;
  }
LABEL_8:
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 740))(a2);
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 736))(a2);
  if ( *a3 > v12 - v8 )
    *a3 = v12 - v8;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 756))(a2);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 752))(a2);
  v11 = v9 - result;
  if ( *a4 > v11 )
    *a4 = v11;
  return result;
}



// ============================================================
// 【分区 17】妖精族（CNFairy 工厂族，0x62C220-0x62D0B0）
// 证据: TINGKERBELL_FLOAT_LOOP（漂浮）+ TINGKERBELL_MP_ABSORB / HP_ABSORB / ALL_ABSORB；
//       变体按吸收类型分派: Haste/Bless/Invinsible/HP/MP/HPMP/SuperArmorFairy + CNFairyFactory
// ============================================================

// ------------------------------------------------------------
// 0x62C220 CNHasteFairy__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNHasteFairy__vmt2F4(uint32_t *this, int a2)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax

  v2 = *(this + 275);
  v3 = 0;
  if ( v2 != 0 )
  {
    v4 = v2 - 1;
    if ( v4 != 0 )
    {
      if ( v4 == 1 )
        v3 = 20;
    }
    else
    {
      v3 = 15;
    }
  }
  else
  {
    v3 = 5;
  }
  return (*(int (/*thiscall*/ **)(int, int, int, uint32_t *))(*(uint32_t *)a2 + 768))(a2, 12, v3, this);
}



// ------------------------------------------------------------
// 0x62C260 CNBlessFairy__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNBlessFairy__vmt2F4(uint32_t *this, int a2)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax

  v2 = *(this + 275);
  v3 = 0;
  if ( v2 != 0 )
  {
    v4 = v2 - 1;
    if ( v4 != 0 )
    {
      if ( v4 == 1 )
        v3 = 20;
    }
    else
    {
      v3 = 15;
    }
  }
  else
  {
    v3 = 5;
  }
  return (*(int (/*thiscall*/ **)(int, int, int, uint32_t *))(*(uint32_t *)a2 + 768))(a2, 13, v3, this);
}



// ------------------------------------------------------------
// 0x62C2A0 CNInvinsibleFairy__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNInvinsibleFairy__vmt2F4(uint32_t *this, int a2)
{
  int v2; // eax
  int v3; // esi
  int v4; // eax

  v2 = *(this + 275);
  v3 = 0;
  if ( v2 != 0 )
  {
    v4 = v2 - 1;
    if ( v4 != 0 )
    {
      if ( v4 == 1 )
        v3 = 30000;
    }
    else
    {
      v3 = 15000;
    }
  }
  else
  {
    v3 = 7000;
  }
  sub_49C620(1, 1, 0);
  return sub_49C5F0(1, 0, 0, v3);
}



// ------------------------------------------------------------
// 0x62C2F0 CNHPFairy__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNHPFairy__vmt2F4(uint32_t *this, void *Block)
{
  int *v4; // eax
  int v5; // edx
  float v7; // [esp+0h] [ebp-2Ch]
  int v8; // [esp+18h] [ebp-14h] BYREF
  int v9; // [esp+1Ch] [ebp-10h] BYREF
  int v10; // [esp+28h] [ebp-4h]
  void *Blocka; // [esp+34h] [ebp+8h]

  v8 = 0;
  v9 = 0;
  sub_62C000(this, (int)Block, &v8, &v9);
  Blocka = operator new(0x80u);
  v10 = 0;
  if ( Blocka != nullptr )
  {
    v7 = (float)v8;
    v4 = (int *)sub_4D6810(LODWORD(v7), v9, 1, 1);
  }
  else
  {
    v4 = nullptr;
  }
  v5 = *v4;
  v10 = -1;
  return (*(int (/*thiscall*/ **)(int *, void *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v5 + 56))(
           v4,
           Block,
           this,
           0,
           0,
           0,
           -1);
}



// ------------------------------------------------------------
// 0x62C390 CNMPFairy__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNMPFairy__vmt2F4(uint32_t *this, int a2)
{
  int *v4; // eax
  int v5; // edx
  int v7; // [esp+8h] [ebp-14h] BYREF
  int v8; // [esp+Ch] [ebp-10h] BYREF
  int v9; // [esp+18h] [ebp-4h]
  void *v10; // [esp+24h] [ebp+8h]

  v7 = 0;
  v8 = 0;
  sub_62C090(this, a2, &v7, &v8);
  v10 = operator new(0x64u);
  v9 = 0;
  if ( v10 != nullptr )
    v4 = (int *)sub_50F270(v7, v8);
  else
    v4 = nullptr;
  v5 = *v4;
  v9 = -1;
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v5 + 56))(v4, a2, this, 0, 0, 0, -1);
}



// ------------------------------------------------------------
// 0x62C430 CNHPMPFairy__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNHPMPFairy__vmt2F4(uint32_t *this, void *Block)
{
  int *v4; // eax
  int v5; // edx
  int *v6; // eax
  int v7; // edx
  float v9; // [esp+0h] [ebp-34h]
  int v10; // [esp+1Ch] [ebp-18h] BYREF
  int v11; // [esp+20h] [ebp-14h] BYREF
  int v12; // [esp+24h] [ebp-10h] BYREF
  int v13; // [esp+30h] [ebp-4h]
  void *Blocka; // [esp+3Ch] [ebp+8h]
  void *Blockb; // [esp+3Ch] [ebp+8h]

  v11 = 0;
  v10 = 0;
  v12 = 0;
  sub_62C120(this, (int)Block, &v11, &v10, &v12);
  Blocka = operator new(0x80u);
  v13 = 0;
  if ( Blocka != nullptr )
  {
    v9 = (float)v11;
    v4 = (int *)sub_4D6810(LODWORD(v9), v12, 1, 1);
  }
  else
  {
    v4 = nullptr;
  }
  v5 = *v4;
  v13 = -1;
  (*(void (/*thiscall*/ **)(int *, void *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v5 + 56))(v4, Block, this, 0, 0, 0, -1);
  Blockb = operator new(0x64u);
  v13 = 1;
  if ( Blockb != nullptr )
    v6 = (int *)sub_50F270(v10, v12);
  else
    v6 = nullptr;
  v7 = *v6;
  v13 = -1;
  return (*(int (/*thiscall*/ **)(int *, void *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v7 + 56))(
           v6,
           Block,
           this,
           0,
           0,
           0,
           -1);
}



// ------------------------------------------------------------
// 0x62C510 CNFairy__vmt14C
//   【妖精】TINGKERBELL_FLOAT_LOOP —— 漂浮循环音
// ------------------------------------------------------------
int /*thiscall*/ CNFairy__vmt14C(int this)
{
  int v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int result; // eax
  int v8; // edi
  int v9; // eax
  int v10; // [esp-8h] [ebp-18h]
  int v11; // [esp+Ch] [ebp-4h]

  CNMapObject__vmt14C((int *)this);
  if ( *(uint8_t *)(this + 1105) == 0 )
  {
    v2 = *(uint32_t *)this;
    v3 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 124))(this, *(uint32_t *)(this + 324));
    v4 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, v3);
    (*(void (/*thiscall*/ **)(int, int))(v2 + 112))(this, v4);
    v5 = *(uint32_t *)this;
    v6 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 52))(this, 0, 0);
    (*(void (/*thiscall*/ **)(int, const char *, int))(v5 + 212))(this, "TINGKERBELL_FLOAT_LOOP", v6 + 39210);
    *(uint8_t *)(this + 1105) = 1;
    *(uint8_t *)(this + 1121) = 0;
    *(uint8_t *)(this + 1122) = 0;
    sub_698F90(this + 1108, 1000, 0);
  }
  v11 = *(uint32_t *)(this + 1132);
  result = sub_699000(this + 1108);
  if ( result >= v11 )
  {
    *(uint8_t *)(this + 1121) = 0;
    *(uint8_t *)(this + 1122) = 0;
    sub_698F90(this + 1108, 10000, 0);
    v8 = sub_41ACF0(*(uint32_t *)(this + 712) + 4 * *(uint32_t *)(this + 1100) + 32);
    v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 64))(this);
    return sub_50EF20(v9, v8, v10, 3000);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62C5F0 sub_62C5F0
// ------------------------------------------------------------
int /*thiscall*/ sub_62C5F0(uint32_t **this, int a2)
{
  uint32_t *v3; // edx
  unsigned int v4; // kr00_4
  unsigned int v5; // kr04_4
  int v6; // ecx
  int v7; // ecx
  int result; // eax
  float v9; // [esp+8h] [ebp-1Ch]
  int v10; // [esp+Ch] [ebp-18h]
  int v11; // [esp+10h] [ebp-14h]
  char Buffer[12]; // [esp+14h] [ebp-10h] BYREF
  int v13; // [esp+20h] [ebp-4h]

  v3 = *this;
  v13 = dword_796E50;
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))v3[51])(
    this,
    100,
    **(this + 36),
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[93])(this, 100);
  *((uint8_t *)this + 1105) = 0;
  sprintf(Buffer, "%d", a2);
  v4 = strlen(Buffer);
  switch ( Buffer[v4 - 1] )
  {
    case '0':
      *(this + 275) = nullptr;
      break;
    case '1':
      *(this + 275) = (uint32_t *)1;
      break;
    case '2':
      *(this + 275) = (uint32_t *)2;
      break;
    default:
      break;
  }
  v5 = strlen(Buffer);
  if ( Buffer[v5 - 2] == 48 )
  {
    *((uint8_t *)this + 1104) = 0;
  }
  else if ( Buffer[v5 - 2] == 49 )
  {
    *((uint8_t *)this + 1104) = 1;
  }
  if ( *((uint8_t *)this + 1104) != 0 )
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      200,
      (*(this + 36))[1],
      0,
      0,
      0,
      0);
  v6 = (int)*(this + 275);
  v9 = 0.69999999;
  v10 = 1065353216;
  v11 = 1067869798;
  sub_4922F0(*(&v9 + v6));
  v7 = (int)*(this + 275);
  v9 = 0.69999999;
  v10 = 1065353216;
  v11 = 1067869798;
  result = sub_4922F0(*(&v9 + v7));
  *((uint8_t *)this + 1106) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x62C740 sub_62C740
// ------------------------------------------------------------
int /*thiscall*/ sub_62C740(uint32_t *this, int a2)
{
  uint32_t *v2; // ebx
  unsigned int i; // edi
  int v4; // ecx
  int v5; // edx
  int result; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // esi
  int v12; // ebx
  bool v13; // zf

  v2 = this;
  for ( i = 0; ; ++i )
  {
    v4 = v2[29];
    v5 = *(uint32_t *)(v4 + 120);
    result = v5 != 0 ? (*(uint32_t *)(v4 + 124) - v5) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v7 = *(uint32_t *)(v4 + 120);
    if ( v7 != 0 && i < (*(uint32_t *)(v4 + 124) - v7) >> 2 )
      v8 = *(uint32_t *)(v7 + 4 * i);
    else
      v8 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v8 + 40))(v8, 273) != 0 )
    {
      v9 = v2[29];
      v10 = *(uint32_t *)(v9 + 120);
      if ( v10 != 0 && i < (*(uint32_t *)(v9 + 124) - v10) >> 2 )
      {
        v11 = *(uint32_t *)(v10 + 4 * i);
        if ( v11 != 0 )
        {
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)v11 + 376))(v11);
          v13 = v12 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 376))(a2);
          v2 = this;
          if ( v13 )
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 756))(this, v11);
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62C800 CNMPFairy__vmt1F4
//   【妖精·MP】TINGKERBELL_MP_ABSORB
// ------------------------------------------------------------
int /*userpurge*/ CNMPFairy__vmt1F4@<eax>(uint8_t *a1@<ecx>, int a2@<edi>, uint32_t *a3, int a4, int a5)
{
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v12; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a3 + 40))(a3, 273) == 1 && a1[264] == 0 && a1[1106] == 0 )
  {
    v6 = *(uint32_t *)a1;
    a1[1106] = 1;
    v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(v6 + 52))(a1, a2);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v6 + 216))(a1, v7 + 39210);
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
      a1,
      "TINGKERBELL_MP_ABSORB",
      -1,
      0,
      0);
    v12 = __RTDynamicCast(
            (int)a3,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDCharacter `RTTI Type Descriptor',
            0);
    if ( a1[1104] != 0 )
      sub_62C740(a1, v12);
    else
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 756))(a1, v12);
    if ( a3[78] < 0x10u )
      v8 = a3 + 73;
    else
      v8 = (uint32_t *)a3[73];
    v9 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)a1 + 52))(a1, v8);
    off_77F3FC((char *)&byte_73DD1C, v9);
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)a1 + 736))(a1, a3);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x62C8F0 CNHPMPFairy__vmt1F4
//   【妖精·HP+MP】TINGKERBELL_ALL_ABSORB
// ------------------------------------------------------------
int /*userpurge*/ CNHPMPFairy__vmt1F4@<eax>(uint8_t *a1@<ecx>, int a2@<edi>, uint32_t *a3, int a4, int a5)
{
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v12; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a3 + 40))(a3, 273) == 1 && a1[264] == 0 && a1[1106] == 0 )
  {
    v6 = *(uint32_t *)a1;
    a1[1106] = 1;
    v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(v6 + 52))(a1, a2);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v6 + 216))(a1, v7 + 39210);
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
      a1,
      "TINGKERBELL_ALL_ABSORB",
      -1,
      0,
      0);
    v12 = __RTDynamicCast(
            (int)a3,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDCharacter `RTTI Type Descriptor',
            0);
    if ( a1[1104] != 0 )
      sub_62C740(a1, v12);
    else
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 756))(a1, v12);
    if ( a3[78] < 0x10u )
      v8 = a3 + 73;
    else
      v8 = (uint32_t *)a3[73];
    v9 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)a1 + 52))(a1, v8);
    off_77F3FC((char *)&byte_73DD1C, v9);
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)a1 + 736))(a1, a3);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x62C9E0 CNHPFairy__vmt1F4
//   【妖精·HP】TINGKERBELL_HP_ABSORB
// ------------------------------------------------------------
int /*userpurge*/ CNHPFairy__vmt1F4@<eax>(uint8_t *a1@<ecx>, int a2@<edi>, uint32_t *a3, int a4, int a5)
{
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v12; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*a3 + 40))(a3, 273) == 1 && a1[264] == 0 && a1[1106] == 0 )
  {
    v6 = *(uint32_t *)a1;
    a1[1106] = 1;
    v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(v6 + 52))(a1, a2);
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v6 + 216))(a1, v7 + 39210);
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)a1 + 212))(
      a1,
      "TINGKERBELL_HP_ABSORB",
      -1,
      0,
      0);
    v12 = __RTDynamicCast(
            (int)a3,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDCharacter `RTTI Type Descriptor',
            0);
    if ( a1[1104] != 0 )
      sub_62C740(a1, v12);
    else
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)a1 + 756))(a1, v12);
    if ( a3[78] < 0x10u )
      v8 = a3 + 73;
    else
      v8 = (uint32_t *)a3[73];
    v9 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)a1 + 52))(a1, v8);
    off_77F3FC((char *)&byte_73DD1C, v9);
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)a1 + 736))(a1, a3);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x62CAD0 CNSuperArmorFairy__vmt2F4
// ------------------------------------------------------------
int /*thiscall*/ CNSuperArmorFairy__vmt2F4(uint32_t *this, int a2)
{
  int v3; // eax
  uint32_t *v4; // esi
  int v5; // edi
  int v6; // eax
  uint32_t *v7; // eax

  v3 = *(this + 275);
  v4 = nullptr;
  v5 = 0;
  if ( v3 != 0 )
  {
    v6 = v3 - 1;
    if ( v6 != 0 )
    {
      if ( v6 == 1 )
        v5 = 30000;
    }
    else
    {
      v5 = 15000;
    }
  }
  else
  {
    v5 = 7000;
  }
  v7 = operator new(0x64u);
  if ( v7 != nullptr )
    v4 = sub_51A7D0(v7);
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 64))(v4) + 40) = v5;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*v4 + 56))(
           v4,
           a2,
           this,
           0,
           0,
           0,
           -1);
}



// ------------------------------------------------------------
// 0x62CB70 CNFairy__vmt2E0
// ------------------------------------------------------------
int /*thiscall*/ sub_62CB70(uint32_t *this, int a2)
{
  int v3; // ebx
  int v4; // ebx
  char v5; // al
  int v6; // eax
  char *v7; // eax
  char *v8; // edi
  int v9; // edx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  char v16; // al
  int v17; // ebx
  char *v18; // eax
  char *v19; // edi
  int v20; // edx
  int v21; // eax
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // ebx
  int v27; // eax
  int v28; // eax
  float v30; // [esp-4h] [ebp-2Ch]
  float v31[3]; // [esp+Ch] [ebp-1Ch]
  int v32; // [esp+18h] [ebp-10h]
  int v33; // [esp+24h] [ebp-4h]

  v32 = sub_42FCB0(228);
  v3 = 0;
  v33 = 0;
  if ( v32 != 0 )
  {
    if ( *(this + 96) < 0x10u )
      LOBYTE(v4) = (uint8_t)this + 108;
    else
      v4 = *(this + 91);
    v5 = sub_41ACF0(*(this + 178) + 24);
    v3 = sub_431920(v4, v5, 1);
  }
  v6 = *(this + 275);
  v31[0] = 0.69999999;
  v31[1] = 1.0;
  v31[2] = 1.3;
  v30 = v31[v6];
  v33 = -1;
  sub_4922F0(v30);
  v7 = (char *)sub_44B6C0(284);
  v8 = v7;
  v32 = (int)v7;
  v33 = 1;
  if ( v7 != nullptr )
  {
    sub_44E0D0(v7, v3, 1);
    *(uint32_t *)v8 = &CNRDPooledObject::`vftable';
  }
  else
  {
    v8 = nullptr;
  }
  v9 = *this;
  v33 = -1;
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 80))(this);
  sub_45FE80(v10, (int)v8, 2, 0, (int)v8, (int)this, 0);
  v11 = *(uint32_t *)v8;
  v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
  v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v12);
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v13);
  (*(void (/*thiscall*/ **)(char *, int))(v11 + 112))(v8, v14);
  if ( *((uint8_t *)this + 1104) != 0 )
  {
    v32 = sub_42FCB0(228);
    v33 = 2;
    if ( v32 != 0 )
    {
      if ( *(this + 96) < 0x10u )
        LOBYTE(v15) = (uint8_t)this + 108;
      else
        v15 = *(this + 91);
      v16 = sub_41ACF0(*(this + 178) + 28);
      v17 = sub_431920(v15, v16, 1);
    }
    else
    {
      v17 = 0;
    }
    v33 = -1;
    v18 = (char *)sub_44B6C0(284);
    v19 = v18;
    v32 = (int)v18;
    v33 = 3;
    if ( v18 != nullptr )
    {
      sub_44E0D0(v18, v17, 1);
      *(uint32_t *)v19 = &CNRDPooledObject::`vftable';
    }
    else
    {
      v19 = nullptr;
    }
    v20 = *this;
    v33 = -1;
    v21 = (*(int (/*thiscall*/ **)(uint32_t *))(v20 + 80))(this);
    sub_45FE80(v21, (int)v19, 2, 0, (int)v19, (int)this, 0);
    v22 = *(uint32_t *)v19;
    v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v23);
    v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v24);
    (*(void (/*thiscall*/ **)(char *, int))(v22 + 112))(v19, v25);
  }
  if ( sub_41ACF0(this + 260) != 0 )
  {
    v26 = *this;
    v27 = sub_41ACF0(this + 260);
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(v26 + 212))(this, v27, -1, 0, 0);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);
    v28 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
    off_77F3FC((char *)&byte_73DD84, v28);
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);
}


// ------------------------------------------------------------
// 0x62CDD0 CNFairyFactory__vmt14C
// ------------------------------------------------------------
char /*thiscall*/ CNFairyFactory__vmt14C(unsigned int *this)
{
  unsigned int v2; // eax
  int v3; // eax
  int v4; // ebx
  DWORD TickCount; // eax
  unsigned int v6; // eax
  uint32_t v8[42]; // [esp+4h] [ebp-A8h]

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(v2) = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 308))(this);
  if ( (uint8_t)v2 != 0 )
  {
    v2 = *(this + 245);
    if ( v2 == 0 )
    {
      v2 = sub_699000((int)(this + 9));
      if ( v2 >= *(this + 246) )
      {
        v3 = *(this + 243);
        v8[0] = 2000;
        v8[1] = 2001;
        v8[2] = 2002;
        v8[3] = 2010;
        v8[4] = 2011;
        v8[5] = 2012;
        v8[6] = 2100;
        v8[7] = 2101;
        v8[8] = 2102;
        v8[9] = 2110;
        v8[10] = 2111;
        v8[11] = 2112;
        v8[12] = 2200;
        v8[13] = 2201;
        v8[14] = 2202;
        v8[15] = 2210;
        v8[16] = 2211;
        v8[17] = 2212;
        v8[18] = 2300;
        v8[19] = 2301;
        v8[20] = 2302;
        v8[21] = 2310;
        v8[22] = 2311;
        v8[23] = 2312;
        v8[24] = 2400;
        v8[25] = 2401;
        v8[26] = 2402;
        v8[27] = 2410;
        v8[28] = 2411;
        v8[29] = 2412;
        v8[30] = 2500;
        v8[31] = 2501;
        v8[32] = 2502;
        v8[33] = 2510;
        v8[34] = 2511;
        v8[35] = 2512;
        v8[36] = 2600;
        v8[37] = 2601;
        v8[38] = 2602;
        v8[39] = 2610;
        v8[40] = 2611;
        v8[41] = 2612;
        if ( v3 == -1 )
        {
          v4 = *this;
          TickCount = GetTickCount();
          v6 = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(
                 this,
                 v8[TickCount % 0x2A],
                 0,
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
        else
        {
          v6 = (*(int (/*thiscall*/ **)(unsigned int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
                 this,
                 v3,
                 0,
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
        *(this + 244) = v6;
        *((uint8_t *)this + 49) = 0;
        *((uint8_t *)this + 50) = 0;
        sub_698F90((int)(this + 9), 0, 0);
        LOBYTE(v2) = sub_699030((int)(this + 9));
      }
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x62CFF0 CNFairyFactory__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNFairyFactory__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( a2 == *(this + 245) )
  {
    *(this + 245) = 0;
    sub_698FE0((int)(this + 9));
    *(this + 244) = 0xFFFF;
  }
}



// ------------------------------------------------------------
// 0x62D030 CNFairyFactory__vmt128
// ------------------------------------------------------------
int /*thiscall*/ CNFairyFactory__vmt128(int *this, int a2)
{
  int result; // eax

  result = __RTDynamicCast(a2, 0, &CNRDObject `RTTI Type Descriptor', &CNFairy `RTTI Type Descriptor', 0);
  if ( result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 52))(a2);
    if ( result == *(this + 244) )
    {
      result = *(this + 245);
      if ( result == 0 )
        *(this + 245) = a2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D080 CNFairyFactory__vmt140
// ------------------------------------------------------------
char /*thiscall*/ CNFairyFactory__vmt140(uint8_t *this)
{
  if ( *(this + 276) != 0 )
  {
    *(this + 49) = 0;
    *(this + 50) = 0;
    sub_698F90((int)(this + 36), 0, 0);
  }
  return CNRDPassiveObject__vmt140(this);
}



// ------------------------------------------------------------
// 0x62D0B0 sub_62D0B0
// ------------------------------------------------------------
int /*thiscall*/ sub_62D0B0(int this, int a2)
{
  int result; // eax

  if ( a2 == 4613 )
    *(uint32_t *)(this + 972) = -1;
  else
    *(uint32_t *)(this + 972) = a2 - 2000;
  result = **(uint32_t **)(this + 348);
  *(uint32_t *)(this + 984) = result;
  *(uint32_t *)(this + 976) = 0xFFFF;
  *(uint32_t *)(this + 980) = 0;
  return result;
}



// ============================================================
// 【分区 18】氛围物件：音效地板/喷泉/重力还原/营火/毒虫/火球（0x62D110-0x62E460）
// 证据: FOUNTAIN_FLOW_LOOP（喷泉）/ CAMPFIRE_LOOP（EPLP 营火）/ NEN_BEGIN（念气起始）/
//       Animation/FireBallStart.ani + MonsterFlower/Particle/PoisonBug.ptl（毒虫）
// ============================================================

// ------------------------------------------------------------
// 0x62D110 CNSoundFloor__vmt2C8
// ------------------------------------------------------------
char /*thiscall*/ CNSoundFloor__vmt2C8(uint8_t *this, int a2)
{
  char result; // al
  int v4; // edi
  int v5; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 184))(a2) == 4
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a2 + 188))(a2) == 4 )
  {
    result = *(this + 1104);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 20801);
      *(this + 1104) = 0;
    }
  }
  else
  {
    result = *(this + 1104);
    if ( result == 0 )
    {
      v4 = *(uint32_t *)this;
      v5 = sub_41ACF0(this + 1100);
      result = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(v4 + 212))(this, v5, 20801, 0, 0);
      *(this + 1104) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D1A0 CNSoundFloor__vmt2C4
// ------------------------------------------------------------
int /*thiscall*/ CNSoundFloor__vmt2C4(char *this, int a2)
{
  int v3; // edi
  int v4; // eax
  int result; // eax

  v3 = *(uint32_t *)this;
  v4 = sub_41ACF0(this + 1100);
  result = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(v3 + 212))(this, v4, 20801, 0, 0);
  *(this + 1104) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x62D1D0 CNSoundFloor__vmt2CC
// ------------------------------------------------------------
int /*thiscall*/ CNSoundFloor__vmt2CC(uint8_t *this, int a2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 20801);
  *(this + 1104) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x62D1F0 CNSoundFloor__vmt2F0
// ------------------------------------------------------------
bool /*stdcall*/ CNSoundFloor__vmt2F0(int a1)
{
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)a1 + 40))(a1, 17) != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)a1 + 128))(a1) == 0;
}



// ------------------------------------------------------------
// 0x62D220 sub_62D220
// ------------------------------------------------------------
void /*thiscall*/ sub_62D220(int this, int a2, int a3)
{
  void *v4; // eax
  int v5; // edi
  int v6; // eax
  void **v7; // ecx
  int v8; // eax
  bool v9; // cf
  int v10; // [esp-4h] [ebp-240h]
  char Buffer[512]; // [esp+10h] [ebp-22Ch] BYREF
  uint8_t v12[4]; // [esp+210h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+214h] [ebp-28h] BYREF
  unsigned int v14; // [esp+228h] [ebp-14h]
  int v15; // [esp+22Ch] [ebp-10h]
  int v16; // [esp+238h] [ebp-4h]

  v15 = dword_796E50;
  v4 = (void *)sub_41ACF0(*(uint32_t *)(this + 712) + 4 * a2 + 24);
  v14 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;
  sub_4015C0(v4, strlen((const char *)v4));
  v16 = 0;
  sprintf(Buffer, "%d.ani", a3);
  sub_4022F0((std::_String_base *)v12, Buffer, strlen(Buffer));
  v5 = *(uint32_t *)(this + 136);
  if ( v5 != 0 )
  {
    sub_42AF90(*(void ***)(this + 136));
    sub_657740(v5, 228);
  }
  *(uint32_t *)(this + 136) = 0;
  v6 = sub_42FCB0(228);
  LOBYTE(v16) = 1;
  if ( v6 != 0 )
  {
    v7 = (void **)Block[0];
    if ( v14 < 0x10 )
      v7 = Block;
    v8 = sub_431860(v6, (const char *)v7, 1);
  }
  else
  {
    v8 = 0;
  }
  v10 = *(uint32_t *)(this + 712) + 44;
  LOBYTE(v16) = 0;
  *(uint32_t *)(this + 136) = v8;
  sub_41B0D0(v10);
  v9 = v14 < 0x10;
  *(uint8_t *)(this + 1104) = 0;
  if ( !v9 )
    j__free(Block[0]);
}



// ------------------------------------------------------------
// 0x62D380 CNFountain__vmt14C
//   【喷泉】FOUNTAIN_FLOW_LOOP —— 流水循环音
// ------------------------------------------------------------
char /*thiscall*/ CNFountain__vmt14C(int this)
{
  char result; // al

  CNMapObject__vmt14C((int *)this);
  result = *(uint8_t *)(this + 1100);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
               this,
               "FOUNTAIN_FLOW_LOOP",
               7811,
               0,
               0);
    *(uint8_t *)(this + 1100) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D3C0 CNFountain__vmt2E4
// ------------------------------------------------------------
int /*thiscall*/ CNFountain__vmt2E4(uint32_t *this)
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
    this,
    100,
    *(uint32_t *)(*(this + 36) + 8),
    0,
    0,
    0,
    0);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
             this,
             200,
             *(uint32_t *)(*(this + 36) + 12),
             0,
             0,
             0,
             0);
  *((uint8_t *)this + 1100) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x62D410 CNFountain__vmt2E8
// ------------------------------------------------------------
int /*thiscall*/ CNFountain__vmt2E8(int this)
{
  int v2; // ebx
  int v3; // eax

  CNMapObject__vmt2E8((int *)this);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 8));
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 12));
  *(uint8_t *)(this + 945) = 1;
  if ( sub_41ACF0(this + 1040) != 0 )
  {
    v2 = *(uint32_t *)this;
    v3 = sub_41ACF0(this + 1040);
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(v2 + 212))(this, v3, -1, 0, 0);
  }
  return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 7811);
}



// ------------------------------------------------------------
// 0x62D490 sub_62D490
// ------------------------------------------------------------
int /*thiscall*/ sub_62D490(int this)
{
  *(uint8_t *)(this + 972) = 0;
  *(uint32_t *)(this + 976) = 0;
  *(uint32_t *)(this + 980) = 0;
  *(uint8_t *)(this + 984) = 0;
  *(uint32_t *)(this + 988) = 0;
  *(uint32_t *)(this + 992) = 0;
  *(uint32_t *)(this + 996) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x62D4C0 sub_62D4C0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_62D4C0(int *this)
{
  int v2; // esi
  int v4; // [esp+8h] [ebp-4h]

  v2 = sub_699000((int)(this + 16)) - *(this + 249);
  v4 = sub_42B420(
         (uint64_t)((double)*(this + 245) * 0.0099999998),
         (uint64_t)(0.079999998 * (double)*(this + 245)),
         v2,
         20000);
  return (uint64_t)((1.0 - sub_405400(360 * v2 / 5000 % 360)) * (double)v4 * 0.5);
}



// ------------------------------------------------------------
// 0x62D550 sub_62D550
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_62D550(uint32_t *this)
{
  unsigned int result; // eax
  unsigned int i; // ecx
  int v4; // edx
  unsigned int v5; // edi

  result = *(uint32_t *)(*(this + 87) + 4);
  *(this + 245) = result;
  for ( i = 0; ; i = v5 )
  {
    v4 = *(this + 36);
    if ( v4 == 0 )
      break;
    result = (*(this + 37) - v4) >> 2;
    if ( i >= result )
      break;
    v5 = i + 1;
    result = (*(int (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
               this,
               i + 1,
               *(uint32_t *)(v4 + 4 * i),
               0,
               0,
               0,
               0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D5B0 CNGravityChangeBack__vmt10
// ------------------------------------------------------------
int /*thiscall*/ sub_62D5B0(int **this)
{
  int *v2; // eax
  int v3; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  unsigned int v9; // eax
  int v10; // edx
  unsigned int v11; // edi
  int result; // eax
  int *v13; // edi
  char v14; // al
  int v15; // ecx
  int v16; // ebx
  int v17; // eax
  int *v18; // edi
  int v19; // eax
  int v20; // eax
  float v21; // [esp+18h] [ebp-24h]
  float v22; // [esp+1Ch] [ebp-20h]
  int v23; // [esp+34h] [ebp-8h]
  int v24; // [esp+38h] [ebp-4h]

  sub_600880();
  if ( *((uint8_t *)this + 972) == 0 )
  {
    *(this + 244) = (int *)((int (/*thiscall*/ *)(int **))(*this)[32])(this);
    v2 = *(this + 87);
    if ( *v2 != 0 )
    {
      v3 = *v2;
      v4 = *(uint32_t *)((*(this + 29))[33] + 44);
      v5 = *(uint32_t *)(v4 + 364);
      v6 = v4 + 360;
      v24 = v3;
      v7 = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 5 : 0;
      v8 = v3;
      v23 = 224 * v7 + 2 * v3;
      if ( v3 < v23 )
      {
        do
        {
          ((void (/*thiscall*/ *)(int **, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this)[51])(
            this,
            0,
            *(this + 34),
            v8,
            0,
            0,
            0);
          v9 = 0;
          while ( 1 )
          {
            v10 = (int)*(this + 36);
            if ( v10 == 0 || v9 >= ((int)*(this + 37) - v10) >> 2 )
              break;
            v11 = v9 + 1;
            ((void (/*thiscall*/ *)(int **, unsigned int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              v9 + 1,
              *(uint32_t *)(v10 + 4 * v9),
              v8,
              0,
              0,
              0);
            v9 = v11;
            v3 = v24;
          }
          v8 += v3;
        }
        while ( v8 < v23 );
      }
    }
    *((uint8_t *)this + 972) = 1;
  }
  result = (int)*(this + 29);
  if ( result != 0 )
  {
    v13 = *(int **)(result + 132);
    if ( v13 != nullptr )
    {
      v14 = *((uint8_t *)this + 984);
      if ( v13[331] != 0 )
      {
        if ( v14 == 0 )
        {
          *(this + 247) = (int *)((int (/*thiscall*/ *)(int **))(*this)[32])(this);
          if ( v13[331] >= 0 )
            *(this + 248) = (int *)((char *)*(this + 245) + (uint32_t)*(this + 244));
          else
            *(this + 248) = *(this + 244);
          *((uint8_t *)this + 984) = 1;
        }
        v16 = v13[338];
        v17 = sub_699000((int)(v13 + 332));
        v22 = (float)(int)*(this + 248);
        v21 = (float)(int)*(this + 247);
        v15 = (uint64_t)sub_4049C0(v21, v22, v17, v16);
      }
      else
      {
        if ( v14 != 0 )
        {
          *(this + 249) = (int *)sub_699000((int)(this + 16));
          *((uint8_t *)this + 984) = 0;
        }
        if ( v13[330] >= 0 )
          v15 = (int)*(this + 245) + (uint32_t)*(this + 244) - sub_62D4C0(this);
        else
          v15 = (int)*(this + 244) + sub_62D4C0(this);
      }
      v18 = *this;
      v19 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, v15);
      v20 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v19);
      return ((int (/*thiscall*/ *)(int **, int))v18[28])(this, v20);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x62D7C0 sub_62D7C0
// ------------------------------------------------------------
void /*thiscall*/ sub_62D7C0(uint32_t *this)
{
  *(this + 243) = -1;
  *(this + 244) = 0;
}



// ------------------------------------------------------------
// 0x62D7E0 CNEPLPCampFire__vmt12C
// ------------------------------------------------------------
void /*thiscall*/ CNEPLPCampFire__vmt12C(uint32_t *this, int a2)
{
  CNRDPassiveObject__vmt12C(this, a2);
  if ( (uint32_t *)a2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 19879);
}



// ------------------------------------------------------------
// 0x62D810 sub_62D810
// ------------------------------------------------------------
int /*thiscall*/ sub_62D810(int *this)
{
  unsigned int i; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax
  int v8; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int *v13; // edi
  int j; // eax
  int v15; // ebx
  int v16; // eax
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  int v20; // [esp+Ch] [ebp-10h] BYREF
  int v21; // [esp+10h] [ebp-Ch] BYREF
  int v22; // [esp+14h] [ebp-8h]
  unsigned int v23; // [esp+18h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    v3 = *this;
    v23 = i;
    v4 = (*(int (/*thiscall*/ **)(int *))(v3 + 80))(this);
    v5 = *(uint32_t *)(v4 + 8);
    v6 = v4 + 4;
    result = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
    v9 = *(uint32_t *)(v8 + 8);
    if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )
      v10 = *(uint32_t *)(v9 + 4 * i);
    else
      v10 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)v10 + 40))(v10, 17) != 0 )
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);
      v12 = *(uint32_t *)(v11 + 8);
      if ( v12 != 0 && i < (*(uint32_t *)(v11 + 12) - v12) >> 2 )
        v13 = *(int **)(v12 + 4 * i);
      else
        v13 = nullptr;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int *))(*v13 + 488))(v13, this) == 1 )
      {
        for ( j = 100; ; j = v22 + 100 )
        {
          v22 = j;
          if ( j > 300 )
            break;
          v15 = *v13;
          v16 = (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 124))(this, j, 1, 1);
          v17 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v16);
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int *, int *, int))(v15 + 140))(v13, &v20, &v21, v17) != 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*v13 + 308))(v13) != 0 )
            {
              v18 = *v13;
              v19 = (*(int (/*thiscall*/ **)(int *))(*v13 + 128))(v13);
              (*(void (/*thiscall*/ **)(int *, int, int, int))(v18 + 108))(v13, v20, v21, v19);
            }
            i = v23;
            break;
          }
          i = v23;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D930 sub_62D930
// ------------------------------------------------------------
int /*thiscall*/ sub_62D930(int *this, int a2)
{
  int result; // eax

  if ( a2 != 0 )
  {
    result = a2 - 1;
    if ( a2 == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        100,
        *(uint32_t *)(*(this + 36) + 8),
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
        this,
        200,
        *(uint32_t *)(*(this + 36) + 12),
        0,
        0,
        0,
        0);
      result = sub_62D810(this);
      *(this + 243) = 1;
      return result;
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
               this,
               100,
               *(uint32_t *)*(this + 36),
               0,
               0,
               0,
               0);
  }
  *(this + 243) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x62DA00 CNEPLPCampFire__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNEPLPCampFire__vmtC(int this)
{
  int result; // eax

  CNRDPassiveObject__vmtC((int *)this);
  result = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(
             this,
             100,
             **(uint32_t **)(this + 144),
             0,
             0,
             0,
             0);
  *(uint32_t *)(this + 972) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x62DA40 CNEPLPCampFire__vmt14C
//   【营火】CAMPFIRE_LOOP —— 营火循环音
// ------------------------------------------------------------
int /*thiscall*/ CNEPLPCampFire__vmt14C(int *this)
{
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 244) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CAMPFIRE_LOOP", 19879, 0, 0);
    *(this + 244) = 1;
  }
  result = *(this + 243);
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
    if ( *(uint8_t *)(result + 170) != 0 )
      return sub_62D930(this, 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62DAA0 sub_62DAA0
// ------------------------------------------------------------
int /*thiscall*/ sub_62DAA0(int this)
{
  *(uint32_t *)(this + 972) = 0;
  *(uint8_t *)(this + 989) = 0;
  *(uint8_t *)(this + 990) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x62DAC0 CNPoisonBug__vmt14C
// ------------------------------------------------------------
int */*thiscall*/ CNPoisonBug__vmt14C(int *this)
{
  int v2; // ebx
  int v3; // edi
  int v4; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  void *v8; // ecx
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+14h] [ebp-14h]
  int v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+24h] [ebp-4h]

  v2 = *(this + 250);
  v3 = (int)(this + 244);
  if ( sub_699000((int)(this + 244)) >= v2 )
  {
    *(uint8_t *)(v3 + 13) = 0;
    *(uint8_t *)(v3 + 14) = 0;
    sub_698F90(v3, 50, 0);
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 243) + 12))(*(this + 243), 0);
    v4 = *(uint32_t *)*(this + 243);
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v5);
    v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);
    (*(void (/*thiscall*/ **)(uint32_t, int))(v4 + 40))(*(this + 243), v7);
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v10);
    v8 = (void *)*(this + 29);
    v14 = 0;
    sub_4600B0(v8, 2, 0, (int)v10);
    v14 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v12 = 0;
    v13 = 0;
  }
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x62DBA0 sub_62DBA0
//   【毒虫】PassiveObject/Monster/MonsterFlower/Particle/PoisonBug.ptl —— 毒虫粒子
// ------------------------------------------------------------
int /*thiscall*/ sub_62DBA0(uint32_t *this, int a2)
{
  int v3; // ecx
  uint32_t *v4; // eax
  uint32_t *v5; // eax

  v3 = (int)(this + 244);
  *(uint8_t *)(v3 + 13) = 0;
  *(uint8_t *)(v3 + 14) = 0;
  sub_698F90(v3, 50, 0);
  v4 = operator new(0x12Cu);
  if ( v4 != nullptr )
    v5 = sub_428F30(v4, (int)"PassiveObject/Monster/MonsterFlower/Particle/PoisonBug.ptl", 0);
  else
    v5 = nullptr;
  *(this + 243) = v5;
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*v5 + 104))(v5, a2);
}



// ------------------------------------------------------------
// 0x62DC30 sub_62DC30
// ------------------------------------------------------------
char /*thiscall*/ sub_62DC30(uint8_t *this)
{
  *(this + 972) = 0;
  *(this + 973) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x62DC40 CNFireBallCommon__vmt1F4
// ------------------------------------------------------------
int /*thiscall*/ CNFireBallCommon__vmt1F4(int *this, uint32_t *a2, float *a3, char a4)
{
  uint32_t *v4; // edi
  int v5; // eax
  int v7; // ebx
  int *v8; // edi
  int v9; // eax
  int v11; // [esp-1Ch] [ebp-28h]
  int v12; // [esp-18h] [ebp-24h]
  int v13; // [esp-14h] [ebp-20h]
  int v14; // [esp+8h] [ebp-4h] BYREF

  v4 = a2;
  v5 = *a2;
  v14 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v5 + 648))(a2, &v14, this);
  if ( a4 == 0 && v14 > 0 && *((uint8_t *)this + 972) == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*a2 + 308))(a2) != 0 )
    {
      v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 2);
      v8 = this;
      if ( *(this + 173) != 0 )
        v8 = (int *)*(this + 173);
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
      v12 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      sub_4E4A50(v8, v7, *(this + 176), v9, v11, v12, v13, 0, 0, 0);
      v4 = a2;
    }
    *((uint8_t *)this + 972) = 1;
  }
  return CNRDPassiveObject__vmt1F4(this, v4, a3, a4);
}



// ------------------------------------------------------------
// 0x62DD10 sub_62DD10
//   【火球】NEN_BEGIN —— 念气起始事件派发
// ------------------------------------------------------------
int /*thiscall*/ sub_62DD10(float *this, int a2)
{
  float v4; // [esp+8h] [ebp-1Ch]
  float v5; // [esp+Ch] [ebp-18h]
  int v6; // [esp+1Ch] [ebp-8h]
  float v7; // [esp+2Ch] [ebp+8h]

  v6 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v5 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v4 = (float)v6;
  v7 = (double)(int)(uint64_t)sub_4049C0(v4, v5, a2, 25) * 0.0099999998;
  *(this + 244) = v7;
  sub_4922F0(v7);
  return sub_4015C0("NEN_BEGIN", 9u);
}



// ------------------------------------------------------------
// 0x62DDA0 CNFireBallCommon__vmt14C
//   【火球】Animation/FireBallStart.ani —— 起燃动画
// ------------------------------------------------------------
int */*thiscall*/ CNFireBallCommon__vmt14C(uint8_t *this)
{
  int v2; // eax
  int v3; // ebx
  const char *v4; // ecx
  char *v5; // eax
  char *v6; // edi
  int v7; // ecx
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  int v13; // eax

  if ( *(this + 973) == 0 )
  {
    *(this + 973) = 1;
    v2 = sub_42FCB0(228);
    v3 = 0;
    if ( v2 != 0 )
    {
      if ( *((uint32_t *)this + 96) < 0x10u )
        v4 = this + 364;
      else
        v4 = *((const char **)this + 91);
      v3 = sub_431920(v2, v4, "Animation/FireBallStart.ani", 1);
    }
    sub_4922F0(*((float *)this + 244));
    v5 = (char *)sub_44B6C0(284);
    v6 = v5;
    if ( v5 != nullptr )
    {
      sub_44E0D0(v5, v3, 1);
      *(uint32_t *)v6 = &vftbl_CNRDPooledObject;
    }
    else
    {
      v6 = nullptr;
    }
    v7 = *((uint32_t *)this + 29);
    if ( v7 != 0 )
    {
      sub_45FE80(v7, (int)v6, 2, 0, (int)v6, 0, 0);
      v8 = *(uint32_t *)v6;
      v9 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
      v10 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, v9);
      v11 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, v10);
      (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(v6, v11);
      v12 = *(uint32_t *)v6;
      v13 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this);
      (*(void (/*thiscall*/ **)(char *, int))(v12 + 148))(v6, v13);
    }
  }
  return CNRDPassiveObject__vmt14C((int)this);
}



// ------------------------------------------------------------
// 0x62DED0 sub_62DED0
// ------------------------------------------------------------
int /*thiscall*/ sub_62DED0(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  *(this + 11) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 12) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  *(this + 14) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x62DF30 sub_62DF30
// ------------------------------------------------------------
int /*thiscall*/ sub_62DF30(int this, int a2)
{
  qmemcpy((void *)(this + 4), (const void *)(a2 + 4), 0x98u);
  return this;
}



// ------------------------------------------------------------
// 0x62DF70 sub_62DF70
// ------------------------------------------------------------
int /*thiscall*/ sub_62DF70(uint32_t *this)
{
  int v1; // eax
  LONG v2; // ecx
  LONG v3; // edx
  int result; // eax
  LONG i; // esi

  v1 = *(this + 2);
  v2 = *(uint32_t *)(v1 + 24) + 108;
  v3 = *(uint32_t *)(v1 + 20) + 8;
  result = 0;
  for ( i = v2 + 20; pt.x < v3 || pt.x >= v3 + 242 || pt.y < v2 || pt.y >= i; i += 24 )
  {
    ++result;
    v2 += 24;
    if ( result >= 6 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62DFD0 sub_62DFD0
// ------------------------------------------------------------
int /*thiscall*/ sub_62DFD0(uint32_t *this, char a2)
{
  int result; // eax

  result = *(this + 11);
  *(uint8_t *)(result + 17) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x62DFE0 sub_62DFE0
// ------------------------------------------------------------
void */*thiscall*/ sub_62DFE0(void **this, int *a2, int a3)
{
  char v3; // al
  uint32_t *v4; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)a2 + 173);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    v4 = (uint32_t *)sub_49ECD0(*(this + 1), a3, *(this + 1), a2 + 3, *((uint8_t *)a2 + 172));
    if ( *((uint8_t *)Block + 173) != 0 )
      Block = v4;
    v6 = *a2;
    v10 = 0;
    *v4 = sub_62DFE0(v6, v4);
    v4[2] = sub_62DFE0(a2[2], v4);
  }
  return Block;
}



// ------------------------------------------------------------
// 0x62E0A0 sub_62E0A0
// ------------------------------------------------------------
int /*thiscall*/ sub_62E0A0(uint32_t *this)
{
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint8_t *v10; // eax
  uint8_t *v11; // eax
  int v12; // ecx

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);
  v2 = operator new(0x84u);
  if ( v2 != nullptr )
    v3 = sub_43C410(v2, *(this + 9), 23, 24, 25, 23, 0, 0);
  else
    v3 = nullptr;
  *(this + 10) = v3;
  sub_69A5F0(v3, 230, 11);
  sub_69A840(*(this + 10));
  v4 = operator new(0x84u);
  if ( v4 != nullptr )
    v5 = sub_43C410(v4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196), 49, 50, 51, 49, 0, 0);
  else
    v5 = nullptr;
  *(this + 11) = v5;
  sub_69A5F0(v5, 86, 275);
  sub_69A840(*(this + 11));
  v6 = operator new(0x84u);
  if ( v6 != nullptr )
    v7 = sub_43C410(v6, *(this + 9), 76, 77, 78, 76, 0, 0);
  else
    v7 = nullptr;
  *(this + 12) = v7;
  sub_69A5F0(v7, 100, 257);
  sub_69A840(*(this + 12));
  v8 = operator new(0x84u);
  if ( v8 != nullptr )
    v9 = sub_43C410(v8, *(this + 9), 79, 80, 81, 79, 0, 0);
  else
    v9 = nullptr;
  *(this + 13) = v9;
  sub_69A5F0(v9, 150, 257);
  sub_69A840(*(this + 13));
  v10 = operator new(0x2Cu);
  if ( v10 != nullptr )
    v11 = sub_423B30(v10, dword_79C0B0, *(this + 9), 51, 3);
  else
    v11 = nullptr;
  *(this + 14) = v11;
  v11[24] = 1;
  *((uint8_t *)this + 60) = 0;
  *((uint8_t *)this + 61) = 0;
  *((uint8_t *)this + 62) = 0;
  *((uint8_t *)this + 63) = 0;
  *(this + 18) = 0;
  *(this + 21) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 20) = 12;
  *(this + 22) = 1600;
  *(this + 19) = 6;
  *(this + 27) = dword_99FCCC;
  *(this + 22) = 100;
  *(this + 18) = 1;
  *(this + 23) = 1;
  *(this + 16) = -16777216;
  *(this + 35) = 1600;
  *((uint8_t *)this + 112) = 0;
  *((uint8_t *)this + 113) = 0;
  *((uint8_t *)this + 114) = 0;
  *((uint8_t *)this + 115) = 0;
  *(this + 31) = 0;
  *(this + 32) = 6;
  *(this + 33) = 12;
  *(this + 34) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *(this + 40) = 0;
  v12 = dword_99FCCC;
  *(this + 29) = -16777216;
  *(this + 40) = v12;
  *(this + 35) = 144;
  *(this + 31) = 1;
  *(this + 36) = 1;
  *((uint8_t *)this + 213) = 0;
  *((uint8_t *)this + 214) = 0;
  sub_698F90((int)(this + 50), 500, 0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 23);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);
}



// ------------------------------------------------------------
// 0x62E370 sub_62E370
// ------------------------------------------------------------
int */*thiscall*/ sub_62E370(int this, int a2)
{
  int v3; // edi
  int **v4; // edx
  int *result; // eax
  int *v6; // ecx
  int v7; // esi
  int **v8; // ecx

  v3 = *(uint32_t *)(this + 4);
  *(uint32_t *)(v3 + 4) = sub_62DFE0((void **)this, *(int **)(*(uint32_t *)(a2 + 4) + 4), v3);
  *(uint32_t *)(this + 8) = *(uint32_t *)(a2 + 8);
  v4 = *(int ***)(this + 4);
  result = v4[1];
  if ( *((uint8_t *)result + 173) != 0 )
  {
    *v4 = (int *)v4;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 173) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 173) == 0 );
    }
    *v4 = result;
    v7 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(v7 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 173) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(v7 + 8) = v8;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62E400 sub_62E400
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_62E400(uint32_t *this)
{
  uint32_t *v2; // edi
  uint32_t *result; // eax

  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 45) = 0;
  *(this + 46) = 0;
  v2 = this + 47;
  sub_49F090(*(void **)(*(this + 48) + 4));
  *(uint32_t *)(v2[1] + 4) = v2[1];
  result = (uint32_t *)v2[1];
  v2[2] = 0;
  *result = result;
  *(uint32_t *)(v2[1] + 8) = v2[1];
  *(this + 57) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x62E460 sub_62E460
// ------------------------------------------------------------
int /*thiscall*/ sub_62E460(int this, uint32_t *a2)
{
  int v3; // ebx
  int result; // eax
  int v5; // esi
  int v6; // ebx
  int v7; // edi
  int v8; // ebx
  uint32_t *v9; // ecx
  uint32_t *v10; // eax
  int v11; // edi
  int v12; // edx
  unsigned int v13; // ecx
  int *v14; // eax
  uint32_t *v15; // ecx
  uint32_t *v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // eax
  bool v20; // cc
  int v21; // [esp+Ch] [ebp-4h] BYREF

  v21 = this;
  if ( (uint8_t)a2 == 0 )
  {
    v3 = *(uint32_t *)(this + 224);
    result = sub_699000(this + 200);
    if ( result < v3 )
      return result;
    *(uint8_t *)(this + 213) = 0;
    *(uint8_t *)(this + 214) = 0;
    sub_698F90(this + 200, 500, 0);
  }
  v5 = this + 164;
  if ( *(uint32_t *)(this + 168) != 0 )
    j__free(*(void **)(this + 168));
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  v6 = sub_49EA30(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76));
  v7 = this + 188;
  if ( v7 != v6 )
  {
    sub_49F750(&a2, **(uint32_t **)(v7 + 4), *(uint32_t *)(v7 + 4));
    sub_62E370(v6);
  }
  v8 = v21;
  v9 = *(uint32_t **)(v21 + 192);
  v10 = (uint32_t *)*v9;
  a2 = (uint32_t *)*v9;
  if ( a2 != v9 )
  {
    do
    {
      v11 = v10[3];
      v21 = v11;
      if ( (uint8_t)sub_48FD50(v10 + 4) == 1 )
      {
        v12 = *(uint32_t *)(v5 + 4);
        if ( v12 != 0 )
          v13 = (*(uint32_t *)(v5 + 8) - v12) >> 2;
        else
          v13 = 0;
        if ( v12 != 0 && v13 < (*(uint32_t *)(v5 + 12) - v12) >> 2 )
        {
          v14 = *(int **)(v5 + 8);
          *v14 = v11;
          *(uint32_t *)(v5 + 8) = v14 + 1;
        }
        else
        {
          sub_430C80(*(void **)(v5 + 8), 1, (int)&v21);
        }
      }
      sub_49EBA0(&a2);
      v10 = a2;
    }
    while ( a2 != *(uint32_t **)(v8 + 192) );
  }
  if ( dword_795D44 != -1 )
  {
    v15 = *(uint32_t **)(v8 + 172);
    v16 = *(uint32_t **)(v8 + 168);
    if ( v16 == v15 )
      goto LABEL_23;
    do
    {
      if ( *v16 == dword_795D44 )
        break;
      ++v16;
    }
    while ( v16 != v15 );
    if ( v16 == v15 )
LABEL_23:
      sub_44E850(*(uint32_t **)(v8 + 16), 63);
  }
  v17 = *(uint32_t *)(v5 + 4);
  if ( v17 != 0 )
    v18 = (*(uint32_t *)(v5 + 8) - v17) >> 2;
  else
    v18 = 0;
  if ( (v18 - 1) / 6 <= 0 )
  {
    result = 0;
  }
  else
  {
    v19 = *(uint32_t *)(v5 + 4);
    if ( v19 != 0 )
      result = (((*(uint32_t *)(v5 + 8) - v19) >> 2) - 1) / 6;
    else
      result = 0;
  }
  v20 = *(uint32_t *)(v8 + 180) <= result;
  *(uint32_t *)(v8 + 184) = result;
  if ( !v20 )
    *(uint32_t *)(v8 + 180) = result;
  return result;
}


// ============================================================
// 【分区 19】块尾 UI 窗口杂项（0x62E640-0x62FFF0）【非可破坏物】
// 物件: CNRDWarRoomListWindow（战争房间列表）/ CNRDCompoundItemWindow（合成窗口）
// 证据: CLICK_BUTTON2 / RECIPE_COMBINE / RECIPE_NOTICE；归属 0x62 区块系 dump 相邻，
//       RTTI 与逻辑均属 CNRD 窗口体系（对照 src/game/ui/）
// ============================================================

// ------------------------------------------------------------
// 0x62E640 CNRDWarRoomListWindow__vmt8
//   【块尾 UI】CLICK_BUTTON2 —— 战争房间列表窗口按钮音（非可破坏物）
// ------------------------------------------------------------
uint8_t */*thiscall*/ CNRDWarRoomListWindow__vmt8(int this)
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
  uint8_t *result; // eax
  int v16; // [esp+4h] [ebp-Ch] BYREF
  int v17; // [esp+8h] [ebp-8h] BYREF
  char v18[4]; // [esp+Ch] [ebp-4h] BYREF

  sub_69A650(*(uint32_t *)(this + 8));
  v2 = *(uint32_t *)(this + 8);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    v3 = sub_62DF70((uint32_t *)this);
    if ( v3 != -1 )
    {
      v4 = *(uint32_t *)(this + 168);
      v5 = v4 != 0 ? (*(uint32_t *)(this + 172) - v4) >> 2 : 0;
      v6 = v3 + 6 * *(uint32_t *)(this + 180);
      if ( v6 < v5 )
      {
        v7 = *(uint32_t *)(*(uint32_t *)(this + 168) + 4 * v6);
        v17 = v7;
        sub_49ED70(&v16, &v17);
        v8 = v16;
        if ( v16 != *(uint32_t *)(this + 192) )
        {
          v9 = sub_49EDC0(v7, -1);
          if ( v9 != 0 )
          {
            sub_62DF30(v8 + 16, v9);
            sub_44E8D0(*(char **)(this + 16), (void *)0x3F, 0, v7);
            sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
          }
        }
      }
    }
  }
  v10 = *(uint32_t *)(this + 48);
  if ( *(uint8_t *)(v10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v10 + 12) )
  {
    v11 = *(uint32_t *)(this + 180);
    if ( v11 > 0 )
    {
      *(uint32_t *)(this + 180) = v11 - 1;
      sub_62E460(this, (uint32_t *)1);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  v12 = *(uint32_t *)(this + 52);
  if ( *(uint8_t *)(v12 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v12 + 12) )
  {
    v13 = *(uint32_t *)(this + 180);
    if ( v13 < *(uint32_t *)(this + 184) )
    {
      *(uint32_t *)(this + 180) = v13 + 1;
      sub_62E460(this, (uint32_t *)1);
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    }
  }
  v14 = *(uint32_t *)(this + 40);
  if ( *(uint8_t *)(v14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v14 + 12) )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 32))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  result = *(uint8_t **)(this + 44);
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )
  {
    sub_423200(dword_8F7B08, 101);
    v18[0] = 1;
    sub_423290(dword_8F7B08, (int)v18, 1);
    sub_423380(dword_8F7B08);
    *(uint8_t *)(*(uint32_t *)(this + 44) + 17) = 0;
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62E830 CNRDWarRoomListWindow__vmtC
// ------------------------------------------------------------
int /*thiscall*/ CNRDWarRoomListWindow__vmtC(int this, int a2, int a3)
{
  dword_9B9454 = this;
  *(uint32_t *)(this + 228) = a3;
  sub_62E460(this, (uint32_t *)1);
  sub_69A5F0(*(uint32_t **)(this + 8), 191, 92);
  *(uint32_t *)(this + 180) = 0;
  *(uint32_t *)(this + 184) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x62E870 CNRDWarRoomListWindow__vmt0
// ------------------------------------------------------------
int /*userpurge*/ sub_62E870@<eax>(uint32_t *a1@<ecx>, uint32_t *a2@<ebx>, int a3)
{
  int result; // eax
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // edi
  unsigned int v12; // ebx
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  bool v21; // cc
  unsigned int v22; // edi
  const char *v23; // eax
  const char *future_error_what; // [esp-4h] [ebp-F4h]
  int v26; // [esp+8h] [ebp-E8h]
  int v27; // [esp+Ch] [ebp-E4h]
  int v28; // [esp+10h] [ebp-E0h]
  int v29; // [esp+10h] [ebp-E0h]
  unsigned int v30; // [esp+14h] [ebp-DCh]
  int v31; // [esp+18h] [ebp-D8h]
  int v32; // [esp+1Ch] [ebp-D4h]
  int v33; // [esp+20h] [ebp-D0h]
  char Buffer[200]; // [esp+24h] [ebp-CCh] BYREF
  int v35; // [esp+ECh] [ebp-4h]
  int v36; // [esp+F8h] [ebp+8h]

  v35 = dword_796E50;
  result = sub_554930(a3);
  if ( a3 == a1[2] )
  {
    sub_62E460(0);
    v5 = *(uint32_t *)(a3 + 20);
    v6 = *(uint32_t *)(a3 + 24);
    v33 = v5;
    v27 = v6;
    v7 = sub_418DD0(1);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5 + 6, v6 + 6, dword_79C0B0);
    v8 = a1[57];
    if ( v8 != -1 )
    {
      v9 = sub_418DD0(dword_73DE2C[v8]);
      if ( v9 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v9 + 152))(v9, v5 + 8, v6 + 35, dword_79C0B0);
    }
    v10 = a1[2];
    v11 = v6 + 108;
    v12 = 6 * a1[45];
    v32 = v11;
    v30 = v12;
    if ( *(uint8_t *)(v10 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(v10 + 12)
       || dword_79BE34 == *(uint32_t *)(v10 + 12)
       || dword_79BE38 == *(uint32_t *)(v10 + 12)) )
    {
      v26 = sub_62DF70(a1);
    }
    else
    {
      v26 = -1;
    }
    v31 = 0;
    v36 = v11 + 1;
    do
    {
      v13 = sub_418DD0(21);
      if ( v13 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v13 + 128))(
          v13,
          v33 + 8,
          v11,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          -1929379841,
          1333788672,
          1333788672);
      v14 = a1[42];
      if ( v14 != 0 && v12 < (a1[43] - v14) >> 2 )
      {
        v15 = sub_49EDC0(*(uint32_t *)(a1[42] + 4 * v12), -1);
        v16 = v15;
        if ( v15 != 0 )
        {
          sub_69A110(v33 + 13, v36 + 3, *(uint32_t *)(v15 + 4), -1);
          (*(void (/*thiscall*/ **)(int, uint32_t *, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 28, a2);
          v28 = *(uint32_t *)dword_79C0B0;
          v17 = sub_48FE30(v16);
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(v28 + 80))(dword_79C0B0, v33 + 53, v36 + 4, -4928551, v17);
          if ( (uint8_t)sub_4902A0(v16) != 0 )
            v18 = sub_418DD0(75);
          else
            v18 = sub_418DD0(74);
          if ( v18 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v18 + 152))(v18, v33 + 231, v36, dword_79C0B0);
          a2 = a1 + 15;
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0);
          v29 = *(uint32_t *)dword_79C0B0;
          v19 = sub_48FBB0(v16, 8);
          (*(void (/*cdecl*/ **)(int, int, int, int, const char *, int))(v29 + 80))(
            dword_79C0B0,
            v33 + 156,
            v36 + 4,
            -3750202,
            "%2d/%2d",
            v19);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
          if ( v31 == v26 || *(uint32_t *)(v16 + 4) == dword_795D44 )
          {
            sub_491530(2, 0);
            v20 = sub_418DD0(46);
            if ( v20 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v20 + 152))(v20, v33 + 8, v32, dword_79C0B0);
            sub_491630(2);
          }
          v12 = v30;
        }
      }
      ++v12;
      v11 = v32 + 24;
      v21 = ++v31 < 6;
      v30 = v12;
      v32 += 24;
      v36 += 24;
    }
    while ( v21 );
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 15);
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
      dword_79C0B0,
      v33 + 83,
      v27 + 258,
      -3750202,
      "%d/%d",
      a1[45] + 1,
      a1[46] + 1);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    result = a1[2];
    if ( *(uint8_t *)(result + 17) != 0 && dword_79BE3C == *(uint32_t *)(result + 12) )
    {
      result = sub_62DF70(a1);
      v22 = result;
      if ( result != -1 )
      {
        result = a1[42];
        if ( result != 0 && v22 < (a1[43] - result) >> 2 )
        {
          future_error_what = std::_Get_future_error_what(dword_77F888 + *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76));
          v23 = (const char *)sub_422E70(1904);
          sprintf(Buffer, v23, future_error_what);
          return sub_4649B0(v33 + 128, v27 + 24 * v22 + 103, -1, -16777216, 2, Buffer, 0, 0, 1600, 0);
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x62ED00 sub_62ED00
// ------------------------------------------------------------
int /*thiscall*/ sub_62ED00(uint32_t *this)
{
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 12) = 0xFFFF;
  *(this + 13) = 4;
  *(this + 14) = 0;
  *(this + 51) = 0;
  *(this + 52) = 0;
  *(this + 53) = 0;
  *(this + 54) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x62ED40 sub_62ED40
// ------------------------------------------------------------
int /*thiscall*/ sub_62ED40(uint32_t *this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***v4)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v6)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v7)(uint32_t, int); // ecx
  int (/*thiscall*/ ***v8)(uint32_t, int); // ecx

  v2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  v4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( v4 != nullptr )
    result = (**v4)(v4, 1);
  v5 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 51);
  *(this + 10) = 0;
  if ( v5 != nullptr )
    result = (**v5)(v5, 1);
  v6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 52);
  *(this + 51) = 0;
  if ( v6 != nullptr )
    result = (**v6)(v6, 1);
  v7 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 53);
  *(this + 52) = 0;
  if ( v7 != nullptr )
    result = (**v7)(v7, 1);
  v8 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 54);
  *(this + 53) = 0;
  if ( v8 != nullptr )
    result = (**v8)(v8, 1);
  *(this + 54) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x62EDD0 CNRDCompoundItemWindow__vmt8
//   【块尾 UI】CLICK_BUTTON2 + RECIPE_COMBINE —— 合成窗口
// ------------------------------------------------------------
int /*thiscall*/ CNRDCompoundItemWindow__vmt8(int *this)
{
  int v2; // eax
  int result; // eax

  sub_69A650(*(this + 2));
  v2 = *(this + 9);
  if ( *(uint8_t *)(v2 + 17) != 0 && dword_79BE34 == *(uint32_t *)(v2 + 12) )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    sub_432EA0("RECIPE_COMBINE", -1, 0, 0);
  }
  result = *(this + 10);
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62EE50 CNRDCompoundItemWindow__vmt10
// ------------------------------------------------------------
int /*thiscall*/ CNRDCompoundItemWindow__vmt10(int *this)
{
  int result; // eax
  int v2; // ecx

  result = *(this + 4);
  v2 = *(uint32_t *)(result + 116);
  if ( *(uint32_t *)(v2 + 40) == 5 )
    return sub_540960(v2);
  return result;
}



// ------------------------------------------------------------
// 0x62EE70 sub_62EE70
// ------------------------------------------------------------
int /*cdecl*/ sub_62EE70(uint32_t *a1)
{
  uint32_t *v1; // esi
  uint32_t *v2; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // ecx
  int v6; // esi
  int v7; // eax
  int v9; // [esp+Ch] [ebp-Ch]
  int v10; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  v1 = (uint32_t *)a1[5];
  for ( i = 255; v1 != (uint32_t *)a1[6]; v1 += 2 )
  {
    if ( sub_4F2D40(*v1) == 2 )
      i = 1;
  }
  v2 = (uint32_t *)a1[1];
  if ( v2 == (uint32_t *)a1[2] )
    return i;
  while ( 1 )
  {
    v3 = *v2;
    v9 = v2[1];
    v4 = sub_484E00(*v2);
    v5 = dword_8F7C04;
    v10 = v4;
    if ( dword_8F7C04 != 0 )
    {
      v6 = 0;
      while ( 1 )
      {
        v7 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)v5 + 792))(v5, v6);
        if ( v7 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 16))(v7) + 4) == v3 )
          ++v10;
        if ( ++v6 >= 18 )
          break;
        v5 = dword_8F7C04;
      }
    }
    if ( v10 / v9 == 0 )
      break;
    if ( v10 / v9 < i )
      i = v10 / v9;
    v2 += 2;
    if ( v2 == (uint32_t *)a1[2] )
      return i;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x62EF50 CNRDCompoundItemWindow__vmt0
// ------------------------------------------------------------
char /*userpurge*/ sub_62EF50@<al>(int a1@<ecx>, int a2@<ebx>, int a3)
{
  char result; // al
  int v5; // ebx
  int v6; // edi
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // edi
  int v15; // edi
  int v16; // eax
  bool v17; // zf
  int v18; // eax
  int v19; // eax
  int v20; // edi
  int v21; // eax
  int v22; // eax
  unsigned int v23; // edi
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  unsigned int v27; // ecx
  uint32_t *v28; // eax
  int v29; // edi
  int v30; // eax
  int v31; // edi
  int v32; // eax
  int v33; // eax
  int v34; // edi
  int v35; // eax
  int v36; // edi
  int v37; // eax
  int v38; // ebx
  int v39; // eax
  unsigned int v40; // ecx
  uint32_t *v41; // eax
  int v42; // ecx
  int v43; // edi
  uint32_t *v44; // esi
  int v45; // edi
  int v46; // ebx
  unsigned int v47; // esi
  const char *v48; // eax
  int v50; // [esp+8h] [ebp-14h]
  uint32_t *v51; // [esp+Ch] [ebp-10h]
  int v52; // [esp+10h] [ebp-Ch]
  int v53; // [esp+10h] [ebp-Ch]
  int v54; // [esp+14h] [ebp-8h]
  int v55; // [esp+18h] [ebp-4h]
  int v56; // [esp+18h] [ebp-4h]
  int v57; // [esp+24h] [ebp+8h]
  int v58; // [esp+24h] [ebp+8h]
  int v59; // [esp+24h] [ebp+8h]
  int v60; // [esp+24h] [ebp+8h]

  result = sub_554930(a3);
  if ( a3 == *(uint32_t *)(a1 + 8) )
  {
    v5 = *(uint32_t *)(a3 + 20);
    v6 = *(uint32_t *)(a3 + 24);
    v54 = v5;
    v55 = v6;
    v7 = sub_418DD0(*(uint32_t **)(a1 + 44), *(uint32_t *)(a1 + 52) + 8);
    if ( v7 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v7 + 152))(v7, v5 + 7, v6 + 6, dword_79C0B0);
    v8 = *(uint32_t *)(a1 + 60);
    if ( v8 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v8 + 152))(
        v8,
        v5 + *(uint32_t *)(a1 + 56),
        v6 + 18,
        dword_79C0B0);
    v9 = sub_418DD0(*(uint32_t **)(a1 + 44), 5u);
    if ( v9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v9 + 128))(
        v9,
        v5 + 7,
        v6 + 67,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        1694498815,
        1333788672,
        1333788672);
    v10 = *(uint32_t *)(a1 + 136);
    if ( v10 != 0 && (unsigned int)((*(uint32_t *)(a1 + 140) - v10) / 44) >= 6 )
    {
      v12 = 6;
    }
    else
    {
      v11 = *(uint32_t *)(a1 + 136);
      if ( v11 != 0 )
        v12 = (*(uint32_t *)(a1 + 140) - v11) / 44;
      else
        v12 = 0;
    }
    v13 = *(uint32_t *)(a1 + 120);
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(a1 + 124) - v13) / 44;
    else
      v14 = 0;
    v15 = v12 + ((unsigned int)(v14 + 1) >> 1);
    if ( v15 > 0 )
    {
      v57 = v55 + 97;
      v52 = v15;
      do
      {
        v16 = sub_418DD0(*(uint32_t **)(a1 + 44), 6u);
        if ( v16 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v16 + 128))(
            v16,
            v5 + 7,
            v57,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            1694498815,
            1333788672,
            1333788672);
        v17 = v52 == 1;
        v57 += 39;
        --v52;
      }
      while ( !v17 );
    }
    v18 = sub_418DD0(*(uint32_t **)(a1 + 44), 7u);
    if ( v18 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v18 + 128))(
        v18,
        v5 + 7,
        39 * v15 + v55 + 97,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        1694498815,
        1333788672,
        1333788672);
    v58 = v55 + 71;
    v19 = sub_418DD0(*(uint32_t **)(a1 + 44), 4u);
    if ( v19 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v19 + 128))(
        v19,
        v5 + 10,
        v55 + 71,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        603979775,
        1333788672,
        1333788672);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 148, a2);
    v20 = *(uint32_t *)dword_79C0B0;
    v21 = sub_422E70(926);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v20 + 80))(dword_79C0B0, v5 + 19, v55 + 74, -1, v21);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    v22 = *(uint32_t *)(a1 + 120);
    v23 = 0;
    if ( v22 != 0 )
      v56 = (*(uint32_t *)(a1 + 124) - v22) / 44;
    else
      v56 = 0;
    if ( v56 > 0 )
    {
      v24 = 0;
      do
      {
        v25 = *(uint32_t *)(v24 + *(uint32_t *)(a1 + 120));
        if ( v25 != 0 )
          (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)v25 + 152))(
            v25,
            101 * (v23 % 2) + v54 + 18,
            39 * (v23 / 2) + v58 + 26,
            dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 148);
        v26 = *(uint32_t *)(a1 + 120);
        v27 = *(uint32_t *)(v26 + v24 + 28);
        v28 = (uint32_t *)(v24 + v26);
        if ( v27 < 0x10 )
          (*(void (**)(int, unsigned int, unsigned int, uint32_t, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            101 * (v23 % 2) + v54 + 54,
            39 * (v23 / 2) + v58 + 30,
            v28[10],
            "%s\nLv.%d",
            v28 + 2,
            v28[9]);
        else
          (*(void (**)(int, unsigned int, unsigned int, uint32_t, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
            dword_79C0B0,
            101 * (v23 % 2) + v54 + 54,
            39 * (v23 / 2) + v58 + 30,
            v28[10],
            "%s\nLv.%d",
            v28[2],
            v28[9]);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        ++v23;
        v24 += 44;
      }
      while ( (int)v23 < v56 );
      v5 = v54;
    }
    v29 = v58 + 39 * ((v56 + 1) / 2) + 26;
    v59 = v29;
    v30 = sub_418DD0(*(uint32_t **)(a1 + 44), 4u);
    if ( v30 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)v30 + 128))(
        v30,
        v5 + 10,
        v29,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        603979775,
        1333788672,
        1333788672);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 148);
    v31 = *(uint32_t *)dword_79C0B0;
    v32 = sub_422E70(927);
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v31 + 80))(dword_79C0B0, v5 + 19, v59 + 3, -1, v32);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
    v33 = *(uint32_t *)(a1 + 136);
    v34 = 0;
    if ( v33 != 0 )
      v50 = (*(uint32_t *)(a1 + 140) - v33) / 44;
    else
      v50 = 0;
    v53 = 0;
    v60 = v59 + 26;
    do
    {
      v35 = v34 + sub_69C690(*(uint32_t *)(a1 + 216));
      if ( v35 < v50 )
      {
        v36 = 44 * v35;
        v37 = *(uint32_t *)(44 * v35 + *(uint32_t *)(a1 + 136));
        v38 = v5 + 18;
        if ( v37 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v37 + 152))(v37, v38, v60, dword_79C0B0);
        if ( *(uint32_t *)(v36 + *(uint32_t *)(a1 + 136) + 32) < *(uint32_t *)(v36 + *(uint32_t *)(a1 + 136) + 36)
          && dword_9B0C5C != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C5C + 128))(
            dword_9B0C5C,
            v38,
            v60,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            1308622847,
            1333788672,
            1333788672);
        }
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, a1 + 148);
        v39 = *(uint32_t *)(a1 + 136);
        v40 = *(uint32_t *)(v39 + v36 + 28);
        v41 = (uint32_t *)(v36 + v39);
        if ( v40 < 0x10 )
          v51 = v41 + 2;
        else
          v51 = (uint32_t *)v41[2];
        (*(void (**)(int, int, int, uint32_t, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(
          dword_79C0B0,
          v38 + 36,
          v60 + 4,
          v41[10],
          "%s\n(%d/%d)",
          v51,
          v41[8],
          v41[9]);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        v5 = v54;
        v34 = v53;
      }
      v53 = ++v34;
      v60 += 39;
    }
    while ( v34 < 6 );
    v42 = *(uint32_t *)(a1 + 36);
    result = *(uint8_t *)(v42 + 17);
    if ( result != 0 )
    {
      v43 = *(uint32_t *)(v42 + 12);
      if ( dword_79BE3C == v43 || dword_79BE34 == v43 || (result = dword_79BE38, dword_79BE38 == v43) )
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
        {
          v44 = *(uint32_t **)(a1 + 36);
          v45 = v44[6];
          v46 = v44[5];
          v47 = v44[7];
          v48 = (const char *)sub_422E70(928);
          return sub_4649B0(v46 + (v47 >> 1), v45, -1, -16777216, 2, v48, 0, 0, 1600, 0);
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x62F530 sub_62F530
// ------------------------------------------------------------
int /*thiscall*/ sub_62F530(int this, int a2)
{
  int v3; // ecx
  int result; // eax
  int v5; // eax
  char v6; // bl
  char *v7; // eax
  int v8; // edi
  char *v9; // eax

  v3 = *((uint32_t *)dword_8F852C + 5);
  if ( v3 == 0 || (result = (*((uint32_t *)dword_8F852C + 6) - v3) >> 2) <= 0 )
  {
    v5 = sub_62EE70((uint32_t *)(this + 64));
    v6 = a2;
    if ( v5 < a2 )
    {
      v7 = sub_422E70(929);
      return sub_44E8D0(*(char **)(this + 16), (void *)0x1B, (int)v7, 0);
    }
    if ( *(uint8_t *)(this + 200) != 0 )
    {
      v8 = *(uint32_t *)(this + 48);
    }
    else
    {
      v8 = sub_484E80(*(uint32_t *)(this + 48));
      if ( v8 == -1 )
      {
        v9 = sub_422E70(930);
        return sub_44E8D0(*(char **)(this + 16), (void *)0x1B, (int)v9, 0);
      }
    }
    sub_423200(dword_8F7B08, 27);
    a2 = v8;
    sub_423290(dword_8F7B08, (int)&a2, 2);
    HIBYTE(a2) = *(uint8_t *)(this + 200) != 0;
    sub_423290(dword_8F7B08, (int)&a2 + 3, 1);
    HIBYTE(a2) = v6;
    sub_423290(dword_8F7B08, (int)&a2 + 3, 1);
    HIBYTE(a2) = 0;
    sub_423290(dword_8F7B08, (int)&a2 + 3, 1);
    HIBYTE(a2) = 1;
    sub_423290(dword_8F7B08, (int)&a2 + 3, 1);
    result = sub_423380(dword_8F7B08);
    dword_795D48 = *(uint32_t *)(this + 52);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62F670 CNRDCompoundItemWindow__vmt14
//   【块尾 UI】RECIPE_NOTICE —— 合成提示
// ------------------------------------------------------------
char /*thiscall*/ CNRDCompoundItemWindow__vmt14(char **this)
{
  char *v3; // eax

  if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )
  {
    v3 = sub_422E70(933);
    sub_44E8D0(*(this + 4), (void *)0x1B, (int)v3, 0);
    sub_432EA0("RECIPE_NOTICE", -1, 0, 0);
    (*((void (/*thiscall*/ **)(char **))*this + 8))(this);
  }
  else if ( (*(this + 9))[17] != 0 )
  {
    if ( *((uint8_t *)this + 200) != 0 )
    {
      sub_540DE0(5, 7, 0, 7, 0, *(this + 12), 0);
    }
    else
    {
      sub_62F530((int)this, 1);
      (*((void (/*thiscall*/ **)(char **))*this + 8))(this);
    }
    return 1;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x62F700 sub_62F700
// ------------------------------------------------------------
int /*thiscall*/ sub_62F700(uint32_t *this)
{
  int v2; // edx
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  uint32_t *v5; // eax
  uint32_t *v6; // eax
  uint32_t *v7; // eax
  uint32_t *v8; // eax
  uint32_t *v9; // eax
  uint32_t *v10; // eax
  uint8_t *v11; // edi
  uint8_t *v12; // eax
  uint8_t *v13; // eax
  uint8_t *v14; // eax

  v2 = *this;
  *(this + 11) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 96);
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(126, 2048);
  sub_69C460(1);
  sub_69C480(-16777216);
  sub_69C420(2);
  v3 = operator new(0x84u);
  if ( v3 != nullptr )
    v4 = sub_43C410(v3, *(this + 11), 0, 1, 2, 3, 0, 0);
  else
    v4 = nullptr;
  *(this + 9) = v4;
  sub_69A840(v4);
  v5 = operator new(0x84u);
  if ( v5 != nullptr )
    v6 = sub_43C410(v5, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);
  else
    v6 = nullptr;
  *(this + 10) = v6;
  sub_69A840(v6);
  *((uint8_t *)this + 148) = 0;
  *((uint8_t *)this + 149) = 0;
  *((uint8_t *)this + 150) = 0;
  *((uint8_t *)this + 151) = 0;
  *(this + 40) = 0;
  *(this + 41) = 6;
  *(this + 42) = 12;
  *(this + 43) = 0;
  *(this + 44) = 1600;
  *(this + 45) = 0;
  *(this + 46) = 0;
  *(this + 47) = 0;
  *(this + 48) = 0;
  *(this + 49) = 0;
  *(this + 49) = dword_99FCCC;
  *(this + 38) = -16777216;
  v7 = operator new(0x84u);
  if ( v7 != nullptr )
    v8 = sub_43C410(v7, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 4, 4, 5, 4, 0, 0);
  else
    v8 = nullptr;
  *(this + 51) = v8;
  *((uint8_t *)v8 + 16) = 1;
  v9 = operator new(0x84u);
  if ( v9 != nullptr )
    v10 = sub_43C410(v9, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 6, 6, 7, 6, 0, 0);
  else
    v10 = nullptr;
  *(this + 52) = v10;
  *((uint8_t *)v10 + 16) = 1;
  v11 = operator new(0x88u);
  if ( v11 != nullptr )
  {
    sub_43C4D0(v11, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 219, 88);
    *(uint32_t *)v11 = &vftbl_nengine__CNVSlider;
    v12 = v11;
  }
  else
  {
    v12 = nullptr;
  }
  *(this + 53) = v12;
  v13 = operator new(0x74u);
  if ( v13 != nullptr )
    v14 = sub_43C630(v13, *(this + 51), *(this + 52), *(this + 53));
  else
    v14 = nullptr;
  *(this + 54) = v14;
  return sub_69A840(v14);
}



// ------------------------------------------------------------
// 0x62F9A0 sub_62F9A0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_62F9A0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t *v4; // edi
  int v5; // eax

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v5 = *(v3 - 11);
    v3 -= 11;
    v4 -= 11;
    *v4 = v5;
    sub_4014D0((std::_String_base *)(v4 + 1), v3 + 1, 0, -1);
    v4[8] = v3[8];
    v4[9] = v3[9];
    v4[10] = v3[10];
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x62FA00 sub_62FA00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_62FA00(uint32_t *this)
{
  uint32_t *v2; // ecx

  v2 = this + 1;
  v2[6] = 15;
  v2[5] = 0;
  *((uint8_t *)v2 + 4) = 0;
  *this = 0;
  sub_4015C0((void *)szPassword, 0);
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x62FA60 sub_62FA60
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_62FA60(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = a2;
  for ( i = a1; i != a2; i += 11 )
  {
    *i = *a3;
    sub_4014D0((std::_String_base *)(i + 1), a3 + 1, 0, -1);
    i[8] = a3[8];
    i[9] = a3[9];
    i[10] = a3[10];
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62FAB0 sub_62FAB0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_62FAB0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  return sub_62F9A0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x62FAD0 sub_62FAD0
// ------------------------------------------------------------
int /*cdecl*/ sub_62FAD0(uint32_t *a1, uint32_t *a2, int a3)
{
  int v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)v3 = *a1;
      *(uint32_t *)(v3 + 28) = 15;
      *(uint32_t *)(v3 + 24) = 0;
      *(uint8_t *)(v3 + 8) = 0;
      sub_4014D0((std::_String_base *)(v3 + 4), a1 + 1, 0, -1);
      *(uint32_t *)(v3 + 32) = a1[8];
      *(uint32_t *)(v3 + 36) = a1[9];
      *(uint32_t *)(v3 + 40) = a1[10];
    }
    v3 += 44;
    LOBYTE(v7) = 0;
    a1 += 11;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x62FBB0 sub_62FBB0
// ------------------------------------------------------------
int /*cdecl*/ sub_62FBB0(int a1, int a2, uint32_t *a3)
{
  int v3; // esi
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  v3 = a1;
  v5[5] = v5;
  v5[4] = a1;
  v6 = 0;
  while ( a2 != 0 )
  {
    v5[3] = v3;
    LOBYTE(v6) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)v3 = *a3;
      *(uint32_t *)(v3 + 28) = 15;
      *(uint32_t *)(v3 + 24) = 0;
      *(uint8_t *)(v3 + 8) = 0;
      sub_4014D0((std::_String_base *)(v3 + 4), a3 + 1, 0, -1);
      result = a3[8];
      *(uint32_t *)(v3 + 32) = result;
      *(uint32_t *)(v3 + 36) = a3[9];
      *(uint32_t *)(v3 + 40) = a3[10];
    }
    v3 += 44;
    LOBYTE(v6) = 0;
    --a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62FC90 sub_62FC90
// ------------------------------------------------------------
int /*stdcall*/ sub_62FC90(int a1, int a2, uint32_t *a3)
{
  sub_62FBB0(a1, a2, a3);
  return a1 + 44 * a2;
}



// ------------------------------------------------------------
// 0x62FCC0 sub_62FCC0
// ------------------------------------------------------------
void /*thiscall*/ sub_62FCC0(int *this, int a2, unsigned int a3, int *a4)
{
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  unsigned int v9; // ecx
  int v11; // eax
  int v12; // eax
  unsigned int v13; // ecx
  int v14; // eax
  char *v15; // ebx
  int v16; // eax
  unsigned int v17; // edi
  int v18; // eax
  int v19; // ecx
  int v21; // edi
  int v22; // [esp-18h] [ebp-70h]
  int v23; // [esp-10h] [ebp-68h]
  int v24; // [esp-Ch] [ebp-64h]
  unsigned int v25; // [esp-8h] [ebp-60h]
  int v26; // [esp+0h] [ebp-58h] BYREF
  void *Block; // [esp+Ch] [ebp-4Ch]
  int *v28; // [esp+10h] [ebp-48h]
  char *v29; // [esp+14h] [ebp-44h]
  int v30; // [esp+18h] [ebp-40h] BYREF
  char v31[4]; // [esp+1Ch] [ebp-3Ch] BYREF
  void *v32; // [esp+20h] [ebp-38h]
  int v33; // [esp+30h] [ebp-28h]
  unsigned int v34; // [esp+34h] [ebp-24h]
  int v35; // [esp+38h] [ebp-20h]
  int v36; // [esp+3Ch] [ebp-1Ch]
  int v37; // [esp+40h] [ebp-18h]
  int v38; // [esp+44h] [ebp-14h]
  int *v39; // [esp+48h] [ebp-10h]
  int v40; // [esp+54h] [ebp-4h]
  int v41; // [esp+60h] [ebp+8h]
  int v42; // [esp+64h] [ebp+Ch]
  int v43; // [esp+68h] [ebp+10h]

  v39 = &v26;
  v38 = dword_796E50;
  v5 = *a4;
  v28 = this;
  v30 = v5;
  v34 = 15;
  v33 = 0;
  LOBYTE(v32) = 0;
  sub_4014D0((std::_String_base *)v31, a4 + 1, 0, -1);
  v6 = a4[9];
  v7 = a4[10];
  v35 = a4[8];
  v36 = v6;
  v37 = v7;
  v8 = *(this + 1);
  v40 = 0;
  if ( v8 != 0 )
    v9 = (*(this + 3) - v8) / 44;
  else
    v9 = 0;
  if ( a3 != 0 )
  {
    if ( v8 != 0 )
      v11 = (*(this + 2) - v8) / 44;
    else
      v11 = 0;
    if ( 97612893 - v11 < a3 )
      sub_558090(this);
    if ( v8 != 0 )
      v12 = (*(this + 2) - v8) / 44;
    else
      v12 = 0;
    if ( v9 >= a3 + v12 )
    {
      v19 = *(this + 2);
      v43 = v19;
      if ( (v19 - a2) / 44 >= a3 )
      {
        v41 = v19 - 44 * a3;
        *(this + 2) = sub_62FAD0(v41, v19, v19);
        sub_62FAB0(a2, v41, v43);
        sub_62FA60(a2, a2 + 44 * a3, &v30);
      }
      else
      {
        sub_62FAD0(a2, v19, a2 + 44 * a3);
        v25 = a3 - (*(this + 2) - a2) / 44;
        v24 = *(this + 2);
        LOBYTE(v40) = 3;
        sub_62FC90(v24, v25, &v30);
        v21 = 44 * a3 + *(this + 2);
        *(this + 2) = v21;
        v40 = 0;
        sub_62FA60(a2, v21 - 44 * a3, &v30);
      }
    }
    else
    {
      if ( 97612893 - (v9 >> 1) >= v9 )
        v13 = (v9 >> 1) + v9;
      else
        v13 = 0;
      if ( v8 != 0 )
        v14 = (*(this + 2) - v8) / 44;
      else
        v14 = 0;
      if ( v13 < a3 + v14 )
        v13 = a3 + sub_527B90(this);
      v42 = 44 * v13;
      v15 = (char *)operator new(44 * v13);
      v22 = *(this + 1);
      Block = v15;
      v29 = v15;
      LOBYTE(v40) = 1;
      v29 = (char *)sub_62FAD0(v22, a2, v15);
      sub_62FBB0(v29, a3, &v30);
      v23 = *(this + 2);
      v29 += 44 * a3;
      sub_62FAD0(a2, v23, v29);
      v16 = *(this + 1);
      if ( v16 != 0 )
        v16 = (*(this + 2) - v16) / 44;
      v17 = v16 + a3;
      v18 = *(this + 1);
      if ( v18 != 0 )
      {
        sub_528410(v18, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v15[v42];
      *(this + 2) = (int)&v15[44 * v17];
      *(this + 1) = (int)v15;
    }
  }
  if ( v34 >= 0x10 )
    j__free(v32);
}


// ------------------------------------------------------------
// 0x62FFF0 sub_62FFF0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_62FFF0(int *this, uint32_t *a2, char *a3, int *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 44 != 0 )
    v6 = (int)&a3[-v5] / 44;
  else
    v6 = 0;
  sub_62FCC0(this, a3, 1u, a4);
  *a2 = *(this + 1) + 44 * v6;
  return a2;
}


