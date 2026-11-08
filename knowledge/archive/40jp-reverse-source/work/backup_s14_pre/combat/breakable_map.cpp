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
// 0x620090 sub_620090 —— 滚石滚动状态采样
//    刷新时钟戳(+996)；关键帧表(+348)元素[3]非空则置滚动标志(+1000)与序号(+1004)；表长>7 时把第 7 项起顺序号追加进 +976 队列（满走 sub_430C80 扩容）。
//    本区无调用点，【推断】由虚 14C 分帧消费。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_620090(int this, int nArg2)  // sub_620090 —— 滚石滚动状态采样
{
  unsigned int result; // eax
  int fld_15C; // ecx
  int fld_15C2; // ecx
  int fld_15C3; // ecx
  int fld_160; // eax
  int fld_15C4; // ebx
  int fld_3D4; // edx
  unsigned int fld_3D8; // edi
  int *fld_3D82; // eax
  int fld_15C42; // [esp+4h] [ebp-Ch] BYREF
  int i; // [esp+8h] [ebp-8h]
  unsigned int v14; // [esp+Ch] [ebp-4h]

  result = sub_699000(this + 36);  // 【clock_now(clk)】
  *(uint32_t *)(this + 996) = result;  // 写字段 this+996（bCfgC996） ← result
  fld_15C = *(uint32_t *)(this + 348);  // 读字段 fld_15C = this+348（pParamTbl348）
  if ( fld_15C != 0 )
  {
    result = (*(uint32_t *)(this + 352) - fld_15C) >> 2;  // this+352 【推断】命中/关系上下文槽
    if ( result > 3 )
    {
      result = *(uint32_t *)(this + 348);  // 读字段 result = this+348（pParamTbl348）
      if ( *(uint32_t *)(fld_15C + 12) != 0 )
      {
        *(uint8_t *)(this + 1000) = 1;  // 写字段 this+1000（bGrassFilter1000） ← 1
        result = *(uint32_t *)(result + 12) - 1;
        *(uint32_t *)(this + 1004) = result;  // 写字段 this+1004（nOilValD1004） ← result
      }
    }
  }
  fld_15C2 = *(uint32_t *)(this + 348);  // 读字段 fld_15C2 = this+348（pParamTbl348）
  if ( fld_15C2 != 0 )
  {
    result = (*(uint32_t *)(this + 352) - fld_15C2) >> 2;  // this+352 【推断】命中/关系上下文槽
    if ( result > 7 )
    {
      v14 = 0;
      for ( i = 28; ; i += 4 )
      {
        fld_15C3 = *(uint32_t *)(this + 348);  // 读字段 fld_15C3 = this+348（pParamTbl348）
        fld_160 = fld_15C3 != 0 ? (*(uint32_t *)(this + 352) - fld_15C3) >> 2 : 0;  // this+352 【推断】命中/关系上下文槽
        result = fld_160 - 7;
        if ( v14 >= result )
          break;
        fld_15C4 = *(uint32_t *)(i + *(uint32_t *)(this + 348));  // this+348 参数表指针
        fld_3D4 = *(uint32_t *)(this + 980);  // 读字段 fld_3D4 = this+980（uCfgF980）
        fld_15C42 = fld_15C4;
        if ( fld_3D4 != 0 )
          fld_3D8 = (*(uint32_t *)(this + 984) - fld_3D4) >> 2;  // this+984 状态块起址
        else
          fld_3D8 = 0;
        if ( fld_3D4 != 0 && fld_3D8 < (*(uint32_t *)(this + 988) - fld_3D4) >> 2 )  // this+988 【推断】状态/配置表项 A
        {
          fld_3D82 = *(int **)(this + 984);  // this+984 状态块起址
          *fld_3D82 = fld_15C4;
          *(uint32_t *)(this + 984) = fld_3D82 + 1;  // 写字段 this+984（aStateBlk984） ← fld_3D82 + 1
        }
        else
        {
          sub_430C80(this + 976, *(uint32_t *)(this + 984), 1u, &fld_15C42);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
        }
        ++v14;  // 计数自增 v14
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6201B0 sub_6201B0 —— 滚石状态复位
//    置滚动中标志(+972)，清 +976..+1008 的计时/队列/引用，并把 +992 挂件解绑（sub_41BFE0 nullptr + sub_41B0D0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_6201B0(int this)  // sub_6201B0 —— 滚石状态复位
{
  int pThis_3E0; // edi
  int result; // eax

  pThis_3E0 = this + 992;  // this+992 【推断】状态/配置表项 B
  *(uint8_t *)(this + 972) = 1;  // 写字段 this+972（uCfgD972） ← 1
  *(uint32_t *)(this + 976) = 0;  // 写字段 this+976（uCfgE976） ← 0
  *(uint32_t *)(this + 980) = 0;  // 写字段 this+980（uCfgF980） ← 0
  *(uint8_t *)(this + 984) = 0;  // 写字段 this+984（aStateBlk984） ← 0
  *(uint32_t *)(this + 988) = 0;  // 写字段 this+988（uCfgA988） ← 0
  sub_41BFE0((void **)(this + 992), nullptr);  // sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
  result = sub_41B0D0(pThis_3E0);  // sub_41B0D0 —— 驻留句柄赋值（旧引用释放 + 新引用 ++）
  *(uint32_t *)(this + 1000) = 0;  // 写字段 this+1000（bGrassFilter1000） ← 0
  *(uint32_t *)(this + 1008) = 0;  // 写字段 this+1008（bVineDone1008） ← 0
  *(uint32_t *)(this + 1004) = 0;  // 写字段 this+1004（nOilValD1004） ← 0
  return result;
}



// ------------------------------------------------------------
// 0x620210 sub_620210 —— 释放 +988 挂件
//    对 +988 对象走虚槽 0（析构，参数 1）后置空；供滚石销毁/重置回收攻击体挂件。
// ------------------------------------------------------------
int /*thiscall*/ sub_620210(uint32_t *this)  // sub_620210 —— 释放 +988 挂件
{
  int (/*thiscall*/ ***fld_e247)(uint32_t, int); // ecx
  int result; // eax

  fld_e247 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 247);  // this+988〔uCfgA988(推断)〕
  if ( fld_e247 != nullptr )  // 若 fld_e247 有效（非空）
    result = (**fld_e247)(fld_e247, 1);  // 调 fld_e247 的虚函数（vt+0）
  *(this + 247) = 0;  // 写字段 this+247 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x620230 CNRollingStone__vmt12C —— 滚石卸载回调 vmt12C
//    基类处理后：卸载对象即自身时经虚 216 复位状态；+1000 引用命中则清零（挂件解绑）。
// ------------------------------------------------------------
void /*thiscall*/ CNRollingStone__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 滚石卸载回调 vmt12C
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 216))(this, 0);  // 虚调用 vt+216（this）全场广播
  if ( *(this + 250) == nArg2 )  // this+1000〔pAttacker1000〕
    *(this + 250) = 0;  // 写字段 this+250 ← 0
}



// ------------------------------------------------------------
// 0x620270 sub_620270 —— 滚石落点刷新地图掩码
//    取全局地图(dword_8F8520 虚 120)校正后，以虚 120/124 取 x/y 经 sub_48C070 换算格子行列；
//    与缓存(+1004/+1008)不同则以虚 48/52 取区间调 sub_48DA40 刷新阻挡掩码并回写缓存。
// ------------------------------------------------------------
int /*thiscall*/ sub_620270(uint32_t *this)  // sub_620270 —— 滚石落点刷新地图掩码
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

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 虚调用 vt+120（dword_8F8520）转发(对象+缓冲)
  if ( *(uint32_t *)(result + 44) != 0 )
  {
    v3 = *this;
    v10 = 0;
    v9 = 0;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v3 + 124))(this);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
    sub_48C070(&v10, &v9, v4, v8);  // sub_48C070 —— 像素坐标 → 格子行列换算
    result = v10;
    if ( v10 != *(this + 251) || v9 != *(this + 252) )  // this+1004〔nOilValD1004(推断)〕等 2 字段
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 虚调用 vt+52（this）归属坐标y
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);  // 虚调用 vt+48（this）归属坐标x
      result = sub_48DA40(v5, v7, 0);  // sub_48DA40 —— 地图阻挡掩码刷新（快照 → 活缓冲，再叠记录矩形）
      v6 = v9;
      *(this + 251) = v10;  // 写字段 this+251 ← v10
      *(this + 252) = v6;  // 写字段 this+252（nParamSlotB） ← v6
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x620300 sub_620300 —— 滚石滚动速度设置
//    死区 |v|<5 归零、|v|>1000 夹紧；写挂件(+112)速度位[4]与脏位(196)，并按正负压 20/-20 朝向值：
//    负速→sub_4955C0(0,0 或 20)；正速→[7]=-20 且经 sub_494F60(0,-1) 写属性槽，末尾 sub_4A0600(0) 收尾。
// ------------------------------------------------------------
int /*thiscall*/ sub_620300(float **this, float fArg2)  // sub_620300 —— 滚石滚动速度设置
{
  int result; // eax
  float *fld_e28; // esi
  uint32_t *fld_e282; // esi

  result = (*((int (/*thiscall*/ **)(float **))*this + 77))(this);  // 虚调用 vt+77（this 虚表槽）
  if ( (uint8_t)result != 0 )
  {
    if ( fabs(fArg2) >= 5.0 )  // 调 浮点绝对值
    {
      if ( fArg2 >= -1000.0 )
      {
        if ( fArg2 > 1000.0 )
          fArg2 = 1000.0;  // 浮点常量 fArg2 ← 1000.0
      }
      else
      {
        fArg2 = -1000.0;  // 浮点常量 fArg2 ← -1000.0
      }
    }
    else
    {
      fArg2 = 0.0;  // 浮点常量 fArg2 ← 0.0
    }
    fld_e28 = *(this + 28);  // 读字段 fld_e28 = this+28（pPanelVec）
    if ( *(uint32_t *)fld_e28 != 0
      && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)fld_e28 + 308))(*(uint32_t *)fld_e28) != 0  // 虚函数调用 槽+308
      && fld_e28[4] != fArg2 )
    {
      fld_e28[4] = fArg2;
      *((uint8_t *)fld_e28 + 196) = 1;  // 写字段 fld_e28[196]（宽1字节）
    }
    if ( fArg2 <= 0.0 )
    {
      if ( fArg2 >= 0.0 )
        sub_4955C0(0, 0);  // sub_4955C0 —— 属性槽条件写入（变化才落 + 触发广播）
      else
        sub_4955C0(0, 20);  // sub_4955C0 —— 属性槽条件写入（变化才落 + 触发广播）
    }
    else
    {
      fld_e282 = *(this + 28);  // 读字段 fld_e282 = this+28（pPanelVec）
      if ( *fld_e282 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e282 + 308))(*fld_e282) != 0 && fld_e282[7] != -20 )  // 虚调用 vt+308（fld_e282）是否本地玩家
      {
        fld_e282[7] = -20;
        *((uint8_t *)fld_e282 + 196) = 1;  // 写字段 fld_e282[196]（宽1字节）
        sub_494F60(0, -1);  // sub_494F60 —— 属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
        return sub_4A0600(0);  // sub_4A0600 —— 转调 sub_4A0600
      }
    }
    return sub_4A0600(0);  // sub_4A0600 —— 转调 sub_4A0600
  }
  return result;
}



// ------------------------------------------------------------
// 0x620420 CNRollingStone__vmt140 —— 滚石帧同步（坐标/缩放插值）vmt140
//    按全局难度(dword_8F7A24+12 为 3/4/6)取关卡帧数-1，用 sub_4049C0 在 +348 表上插值：写 +724 与 +980，
//    并把元素[5]/[6]的双精度结果落 +680:+684；末尾走基类 CNRDPassiveObject__vmt140。
// ------------------------------------------------------------
char /*thiscall*/ CNRollingStone__vmt140(int *this)  // 函数定义: 滚石帧同步
{
  int v2; // eax
  int v3; // edi
  int *fld_e87; // eax
  double v5; // st7
  float v6; // eax
  int fld_e872; // eax
  double v8; // st7
  int fld_e873; // eax
  uint64_t v10; // rax
  float v12; // [esp+4h] [ebp-24h]
  float v13; // [esp+4h] [ebp-24h]
  float v14; // [esp+4h] [ebp-24h]
  float v15; // [esp+8h] [ebp-20h]
  float v16; // [esp+8h] [ebp-20h]
  float v17; // [esp+8h] [ebp-20h]

  if ( *((uint8_t *)this + 276) != 0 )  // this+276 地图条目指针
  {
    v2 = 0;
    switch ( *(uint32_t *)(dword_8F7A24 + 12) )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    {
      case 3:  // case 3 分派（滚石族（CNRollingStone + 触发辅助 0x620090-0x620BC0））
        v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      case 4:  // case 4 分派（滚石族（CNRollingStone + 触发辅助 0x620090-0x620BC0））
        v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      case 6:  // case 6 分派（滚石族（CNRollingStone + 触发辅助 0x620090-0x620BC0））
        v2 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      default:
        break;
    }
    v3 = *(uint32_t *)(v2 + 112);  // 读字段 v3 = v2+112（pHostComp）
    fld_e87 = (int *)*(this + 87);  // this+348〔pParamTbl348〕
    --v3;  // 计数自减 v3
    v15 = (float)fld_e87[1];
    v12 = (float)*fld_e87;
    v5 = sub_4049C0(v12, v15, v3, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v6 = *(float *)this;
    *((float *)this + 181) = v5;  // this+724〔fVal724(推断)〕
    (*(void (/*thiscall*/ **)(int *, int *))(LODWORD(v6) + 344))(this, this + 181);  // 虚函数调用 槽+344：交互槽（45E490/45E4D0/525CE0）
    fld_e872 = *(this + 87);  // 读字段 fld_e872 = this+87
    v16 = (float)*(int *)(fld_e872 + 12);
    v13 = (float)*(int *)(fld_e872 + 8);
    v8 = sub_4049C0(v13, v16, v3, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    fld_e873 = *(this + 87);  // 读字段 fld_e873 = this+87
    *((float *)this + 245) = v8;  // this+980〔fSpeed980〕
    v17 = (float)*(int *)(fld_e873 + 24);
    v14 = (float)*(int *)(fld_e873 + 20);
    v10 = (uint64_t)sub_4049C0(v14, v17, v3, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(this + 170) = v10;  // 写字段 this+170 ← v10
    *(this + 171) = v10;  // 写字段 this+171 ← v10
  }
  return CNRDPassiveObject__vmt140(this);  // 返回 调 CNRDPassiveObject__vmt140
}



// ------------------------------------------------------------
// 0x620540 sub_620540 —— 滚石帧率/缩放重置
//    置 +700=0 与 +96=545（单位/动画标识），取 +348 表首项*0.01 为比例，sub_4922F0 两次分别统设全帧与盒缩放（nArg2 未用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_620540(int this, int nArg2)  // sub_620540 —— 滚石帧率/缩放重置
{
  int *fld_15C; // eax
  float v4; // [esp+8h] [ebp-4h]

  fld_15C = (int *)(*(uint32_t *)(this + 348) + 28);  // this+348 参数表指针
  *(uint8_t *)(this + 700) = 0;  // 写字段 this+700（bSnapshot700） ← 0
  *(uint32_t *)(this + 96) = 545;  // 写字段 this+96（nStatusMode） ← 545
  v4 = (double)*fld_15C * 0.0099999998;  // ×0.01f（百分数转比例）
  sub_4922F0(v4);  // sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
  return sub_4922F0(v4);  // sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
}



// ------------------------------------------------------------
// 0x620590 CNRollingStone__vmt160 —— 滚石碰撞目标回调 vmt160
//    基类 IRDCollisionObject__vmt160 后，若 +1000 挂载目标存在则经虚 356 回调（【推断】碰撞引发的状态回驱）。
// ------------------------------------------------------------
int /*thiscall*/ CNRollingStone__vmt160(int *this)  // 函数定义: 滚石碰撞目标回调 vmt160
{
  int result; // eax

  IRDCollisionObject__vmt160(this);
  result = *(this + 250);  // 读字段 result = this+250
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 356))(this, *(this + 250));  // 虚调用 vt+356（this 虚表槽）
  return result;
}



// ------------------------------------------------------------
// 0x6205B0 sub_6205B0 —— 滚石转攻击体
//    先经虚 77/78 复位；取 +988 投掷件按虚 30/31 对齐己方坐标后调虚 12/92 取变换包，交 sub_4600B0(this+116,2,0,包) 广播（破坏时投射碎片），
//    再以 +996 句柄(sub_41ACF0)走虚 53 生成派生。
// ------------------------------------------------------------
void /*thiscall*/ sub_6205B0(int **this, int nArg2)  // sub_6205B0 —— 滚石转攻击体
{
  int *fld_e247; // edi
  int v4; // ebx
  int v5; // eax
  int v6; // eax
  void *fld_e29; // ecx
  int *v8; // edi
  int pThis_F9; // eax
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+24h] [ebp-4h]

  if ( ((uint8_t (/*thiscall*/ *)(int **))(*this)[77])(this) != 0 )
    ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  fld_e247 = *(this + 247);  // 读字段 fld_e247 = this+247
  v4 = *fld_e247;
  v5 = ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[31])(this, 0);
  v6 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v5);
  (*(void (/*thiscall*/ **)(int *, int))(v4 + 40))(fld_e247, v6);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 247) + 12))(*(this + 247), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(this + 247) + 92))(*(this + 247), v10);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
  fld_e29 = *(this + 29);  // 读字段 fld_e29 = this+29
  v12 = 0;
  sub_4600B0(fld_e29, 2, 0, (int)v10);  // sub_4600B0 —— 演播层注册(槽号)
  v8 = *this;
  pThis_F9 = sub_41ACF0(this + 249);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  ((void (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t))v8[53])(this, pThis_F9, -1, 0, 0);
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 释放堆块
}



// ------------------------------------------------------------
// 0x620680 CNRollingStone__vmt14C
//   【滚石】TRAP_STONE_ROLLING_LOOP —— 滚动循环音/滚动状态驱动
// ------------------------------------------------------------
void /*thiscall*/ sub_620680(void *this)  // 【CNRollingStone__vmt14C】
{
  int pThis_57; // ecx
  int v3; // ecx
  long double v4; // st7
  int pThis_1E3; // ecx
  int pThis_2AC; // eax
  int pThis_2AC2; // eax
  int pThis_130; // eax
  uint32_t *pThis_1E; // ebx
  int pThis_24; // edi
  int v11; // eax
  int v12; // eax
  int pThis_1E2; // ecx
  int pThis_1D; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // edi
  float v18; // [esp+8h] [ebp-8h]
  float pThis_1C; // [esp+Ch] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( *((uint8_t *)this + 984) == 0 )  // this+984 状态字节
  {
    pThis_57 = *((uint32_t *)this + 87);  // 读字段 pThis_57 = this[87]
    if ( pThis_57 != 0 && (unsigned int)((*((uint32_t *)this + 88) - pThis_57) >> 2) > 4 )  // this+88 插值起点 Y
    {
      v3 = *(uint32_t *)(pThis_57 + 16);  // 读字段 v3 = pThis_57+16（nChannelTypeSel）
      if ( v3 != 0 )
      {
        if ( v3 == 1 )
          sub_620300(-200.0);  // sub_620300 —— 滚石滚动速度设置
        else
          sub_620300(200.0);  // sub_620300 —— 滚石滚动速度设置
      }
    }
    *((uint8_t *)this + 984) = 1;  // 写字段 this+984（aStateBlk984）
  }
  pThis_1C = *(float *)(*((uint32_t *)this + 28) + 16);  // this+28 【推断】逐帧驱动对象
  v4 = fabs(pThis_1C);  // 调 浮点绝对值
  v18 = v4;
  if ( v4 >= 5.0 )
  {
    pThis_1E = *((uint32_t **)this + 30);
    if ( pThis_1C >= 0.0 )
    {
      if ( pThis_1C <= 0.0 )
      {
LABEL_23:
        if ( *((uint8_t *)this + 972) != 0 )  // this+972 激活位
        {
          pThis_1E2 = *((uint32_t *)this + 30);  // 读字段 pThis_1E2 = this[30]
          *((uint8_t *)this + 972) = 0;  // 写字段 this+972（uCfgD972）
          sub_4939E0(pThis_1E2, 0);  // sub_4939E0 —— 播放/暂停级联（递归子链 +204）
          (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 596))(this, 1);  // 虚调用 vt+596（this 虚表槽）
          (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 虚调用 vt+676（this）队伍编号刷新
          (*(void (/*thiscall*/ **)(void *, const char *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
            this,
            "TRAP_STONE_ROLLING_LOOP",  // 资源/动画 TAG TRAP_STONE_ROLLING_LOOP
            0,
            0,
            0);
        }
        sub_493D00(*((uint32_t *)this + 30), v18);  // sub_493D00 —— ★变速（研究§26）
        if ( sub_699000((int)this + 36) >= *((uint32_t *)this + 244) + 1500 )  // 【clock_now(clk)】
        {
          (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 352))(this);  // 虚调用 vt+352（this 虚表槽）
          *((uint32_t *)this + 244) = sub_699000((int)this + 36);  // sub_699000 —— 【clock_now(clk)】
        }
        goto LABEL_27;
      }
      pThis_24 = **((uint32_t **)this + 36);  // this+36 物品状态字
    }
    else
    {
      pThis_24 = *((uint32_t *)this + 34);  // 读字段 pThis_24 = this[34]
    }
    if ( pThis_1E != (uint32_t *)pThis_24 )
    {
      v11 = pThis_1E[11];
      if ( v11 != 0 )
        v11 = (pThis_1E[12] - v11) / 88;
      v12 = sub_491C70(pThis_24, v11 - pThis_1E[37] - 1);  // sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
      sub_493A60(pThis_24, v12);  // sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
      (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 196))(this, pThis_24);  // 虚调用 vt+196（this）物件非空判定
    }
    goto LABEL_23;
  }
  if ( *((uint8_t *)this + 972) != 0 )  // this+972 激活位
    goto LABEL_28;
  pThis_1E3 = *((uint32_t *)this + 30);  // 读字段 pThis_1E3 = this[30]
  *((uint8_t *)this + 972) = 1;  // 写字段 this+972（uCfgD972）
  sub_4939E0(pThis_1E3, 1);  // sub_4939E0 —— 播放/暂停级联（递归子链 +204）
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 596))(this, 0);  // 虚调用 vt+596（this 虚表槽）
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 676))(this, 2);  // 虚调用 vt+676（this）队伍编号刷新
  (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 216))(this, 0);  // 虚调用 vt+216（this）全场广播
  *((uint32_t *)this + 250) = 0;  // 写字段 this[250]（宽4字节）
  sub_62D810(this);  // sub_62D810 —— 类别 17 物件贴位探测
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this) != 0 )  // 虚调用 vt+684（this 虚表槽）
  {
    pThis_2AC = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this);  // 虚调用 vt+684（this 虚表槽）
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pThis_2AC + 40))(pThis_2AC, 529) != 0 )  // 虚调用 vt+40（pThis_2AC）条件查询(273等)
    {
      pThis_2AC2 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 684))(this);  // 虚调用 vt+684（this 虚表槽）
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_2AC2 + 340))(pThis_2AC2) == 50002 )  // 虚调用 vt+340（pThis_2AC2 虚表槽）
      {
        pThis_130 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 304))(this);  // 虚调用 vt+304（this）归属对象(本地/全局)
        sub_6205B0(pThis_130);  // sub_6205B0 —— 滚石转攻击体
      }
    }
  }
LABEL_27:
  sub_620270(this);  // sub_620270 —— 滚石落点刷新地图掩码
LABEL_28:
  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 444))(this) < 0  // 虚调用 vt+444（this 虚表槽）
      || ((pThis_1D = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 29) + 132) + 44),  // this+116〔会话上下文〕
           v15 = *(uint32_t *)(pThis_1D + 364),  // this+364 动画件名缓冲 SSO 内联首址
           v16 = pThis_1D + 360,
           v15 != 0)
        ? (v17 = (*(uint32_t *)(v16 + 8) - v15) >> 5)
        : (v17 = 0),
          (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 440))(this) > 224 * v17) )  // 虚调用 vt+440（this 虚表槽）
    {
      (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    }
    if ( v18 < 5.0 && pThis_1C != 0.0 )  // 若 v18 < 5 与/或 pThis_1C != 0
      sub_620300(0.0);  // sub_620300 —— 滚石滚动速度设置
  }
}


// ------------------------------------------------------------
// 0x620960 CNRollingStone__vmt2B4 —— 滚石受击 vmt2B4
//    血量(+680)>0 时按 nArg3 与 +980 参考值折算推力：攻击者虚 660 判定推离/推向，经 sub_620300 改滚动速度并记 +1000=攻击者虚 576；
//    血量≤0 转 sub_6205B0 破坏流程；末尾以 +992 句柄走虚 53 生成派生。
// ------------------------------------------------------------
int /*thiscall*/ CNRollingStone__vmt2B4(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 滚石受击 vmt2B4
{
  double pHostComp; // st7  | +0x0070 → 宿主组件指针（620A10 vmtC 尾调 sub_49FD20(*(+112))）（证据 va=00620A10）（CNRollingStone；va=00620A10）
  float *v9; // edi
  int pThis_3E0; // eax
  float fld_702; // [esp+4h] [ebp-Ch]
  float fSpeed980; // [esp+18h] [ebp+8h]  | +0x03D4 → 速率/HP 比浮点（CNRollingStone；va=00620960）

  if ( *(int *)(this + 680) > 0 )  // this+680 当前 HP
  {
    if ( nArg2 != 0 )
    {
      fSpeed980 = (double)nArg3 / *(float *)(this + 980) * 100.0;  // this+980 速率/HP 比浮点
      if ( fSpeed980 != 0.0 )
      {
        if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 660))(nArg2, this) != 0 )  // 虚调用 vt+660（nArg2 虚表槽）
          pHostComp = *(float *)(*(uint32_t *)(this + 112) + 16) - fSpeed980;  // this+112 宿主组件指针
        else
          pHostComp = fSpeed980 + *(float *)(*(uint32_t *)(this + 112) + 16);  // this+112 宿主组件指针
        fld_702 = pHostComp;
        sub_620300((float **)this, fld_702);  // sub_620300 —— 滚石滚动速度设置
        *(uint32_t *)(this + 1000) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);  // 虚调用 vt+576（nArg2）受击方判定体
      }
    }
  }
  else
  {
    sub_6205B0((int **)this, nArg2);  // sub_6205B0 —— 滚石转攻击体
  }
  v9 = *(float **)this;
  pThis_3E0 = sub_41ACF0(this + 992);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  return (*((int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))v9 + 53))(this, pThis_3E0, -1, 0, 0);  // 虚函数调用 槽+53
}



// ------------------------------------------------------------
// 0x620A10 CNRollingStone__vmtC —— 滚石构造初始化 vmtC
//    基类后清 +200 状态位(sub_49FD20)与 +112 坐标，置滚动标志并 sub_4939E0 停播；
//    再 new(0x12C) 由 +712 字符串句柄(sub_41ACF0)经 sub_4C3640 构造 +988 挂件，释放临时句柄(+4/+8)。
// ------------------------------------------------------------
int /*thiscall*/ CNRollingStone__vmtC(int this)  // 函数定义: 滚石构造初始化 vmtC
{
  int pAnimObj; // ecx  | +0x0078 → 动画对象指针（CNRollingStone；va=00620A10）
  int pResTbl712; // ecx  | +0x02C8 → 资源/动画句柄表基指针（620A10 读 *(+712)）（证据 va=00620A10）（CNRollingStone；va=00620A10）
  int fld_16C; // ebx  | +0x016C → 动画件名缓冲 SSO 内联首址（CNRollingStone；va=00620A10）
  int v5; // eax
  int pThis_16C; // eax
  int v7; // eax

  CNRDPassiveObject__vmtC((int *)this);
  sub_49FD20(*(uint32_t *)(this + 112));  // 调 +200 状态位（sub_698F90 复位）
  *(uint32_t *)(*(uint32_t *)(this + 112) + 16) = 0;  // this+112 宿主组件指针
  *(uint32_t *)(*(uint32_t *)(this + 112) + 28) = 0;  // this+112 宿主组件指针
  pAnimObj = *(uint32_t *)(this + 120);  // 读字段 fld_78 = this+120（pAnimObj）
  *(uint8_t *)(this + 972) = 1;  // 写字段 this+972（uCfgD972） ← 1
  sub_4939E0(pAnimObj, 1);  // sub_4939E0 —— 播放/暂停级联（递归子链 +204）
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 596))(this, 0);  // 虚调用 vt+596（this 虚表槽）
  *(uint32_t *)(this + 688) = 2;  // 写字段 this+688（nSnapshot688） ← 2
  *(uint8_t *)(this + 984) = 0;  // 写字段 this+984（aStateBlk984） ← 0
  if ( operator new(0x12Cu) != nullptr )  // 堆分配
  {
    pResTbl712 = *(uint32_t *)(this + 712);  // 读字段 fld_2C8 = this+712（pResTbl712）
    if ( *(uint32_t *)(this + 384) < 0x10u )  // this+384 动画件名 SSO 容量判据
    {
      v7 = sub_41ACF0(pResTbl712);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      pThis_16C = sub_4C3640(this + 364, v7, this);  // this+364 动画件名缓冲 SSO 内联首址
    }
    else
    {
      fld_16C = *(uint32_t *)(this + 364);  // 读字段 fld_16C = this+364（pAnimNameStr）
      v5 = sub_41ACF0(pResTbl712);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      pThis_16C = sub_4C3640(fld_16C, v5, this);  // 调 构造 +988 挂件
    }
  }
  else
  {
    pThis_16C = 0;
  }
  *(uint32_t *)(this + 988) = pThis_16C;  // 写字段 this+988（uCfgA988） ← pThis_16C
  sub_41B0D0(*(uint32_t *)(this + 712) + 4);  // sub_41B0D0 —— 驻留句柄赋值（旧引用释放 + 新引用 ++）
  return sub_41B0D0(*(uint32_t *)(this + 712) + 8);  // sub_41B0D0 —— 驻留句柄赋值（旧引用释放 + 新引用 ++）
}



// ------------------------------------------------------------
// 0x620B20 sub_620B20 —— 滚石引用清零
//    清 +972..+988 五项（滚动标志/计时/攻击体/队列），供复位路径调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_620B20(int this)  // sub_620B20 —— 滚石引用清零
{
  *(uint8_t *)(this + 972) = 0;  // 写字段 this+972（uCfgD972） ← 0
  *(uint32_t *)(this + 976) = 0;  // 写字段 this+976（uCfgE976） ← 0
  *(uint32_t *)(this + 988) = 0;  // 写字段 this+988（uCfgA988） ← 0
  *(uint32_t *)(this + 980) = 0;  // 写字段 this+980（uCfgF980） ← 0
  *(uint32_t *)(this + 984) = 0;  // 写字段 this+984（aStateBlk984） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x620B50 sub_620B50 —— 全局表按值删除
//    在 dword_9B9424 指针表线性查找 nArg1，命中则以 memcpy 前移覆盖并收缩尾指针（返回新尾）；滚石登记回收共用。
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_620B50(int nArg1)  // sub_620B50 —— 全局表按值删除
{
  unsigned int i; // edx
  unsigned int result; // eax

  for ( i = 0; dword_9B9424 != 0; ++i )
  {
    result = (dword_9B9428 - dword_9B9424) >> 2;  // 向量元素数 = (end−begin)/4
    if ( i >= result )
      break;
    if ( *(uint32_t *)(dword_9B9424 + 4 * i) == nArg1 )
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
// 0x620BC0 sub_620BC0 —— 滚石摘除登记（thunk）
//    以 +976 持有的对象调 sub_620B50 从全局表 dword_9B9424 删除。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_620BC0(int *this)  // sub_620BC0 —— 滚石摘除登记（thunk）
{
  return sub_620B50(*(this + 244));  // sub_620B50 —— 全局表按值删除
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
unsigned int /*thiscall*/ CNTrapCage__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  int uCfgE976; // ecx
  int uCfgA988; // ecx
  int v5; // edx
  unsigned int result; // eax

  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
  {
    uCfgE976 = *(this + 244);  // 读字段 fld_e244 = this+244（fSyncValue）
    if ( uCfgE976 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)uCfgE976 + 308))(uCfgE976) != 0 )  // 虚调用 vt+308（fld_e244）是否本地玩家
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*(this + 244) + 108))(  // this+244 动画同步浮点参数
        *(this + 244),  // this+244 动画同步浮点参数
        *(this + 245),  // this+980〔uCfgF980(推断)〕
        *(this + 246),  // this+984〔aStateBlk984(推断)〕
        0);
    uCfgA988 = *(this + 247);  // 读字段 fld_e247 = this+247
    if ( uCfgA988 != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)uCfgA988 + 84))(uCfgA988, 0);  // 虚调用 vt+84（fld_e247）退出可视/停止
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "JAIL_BREAK", -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
  }
  if ( nArg2 == *(this + 247) )  // this+988〔uCfgA988(推断)〕
    *(this + 247) = 0;  // 写字段 this+247 ← 0
  if ( nArg2 == *(this + 244) )  // this+244 动画同步浮点参数
  {
    v5 = *this;
    *(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v5 + 308))(this) != 0 )  // 虚函数调用 槽+308
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
  }
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);  // 虚调用 vt+40（nArg2）条件查询(273等)
  if ( (uint8_t)result != 0 )
    return sub_620B50(nArg2);  // sub_620B50 —— 全局表按值删除
  return result;
}



// ------------------------------------------------------------
// 0x620CA0 sub_620CA0
//   【铁笼】JAIL_CRASH —— 笼碎撞裂音（笼破坏回调内触发）
// ------------------------------------------------------------
int /*thiscall*/ sub_620CA0(void *this, int nArg2)  // 实现：(铁笼)JAIL_CRASH —— 笼碎撞裂音（笼破坏回调内触发）
{
  int v3; // eax
  int v4; // ecx
  int *pThis_57; // eax
  uint64_t v6; // rax
  float v8; // [esp+0h] [ebp-1Ch]
  float v9; // [esp+4h] [ebp-18h]

  v3 = 0;
  switch ( *(uint32_t *)(dword_8F7A24 + 12) )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  {
    case 3:  // case 3 分派（铁笼/监狱（CNTrapCage，0x620BD0-0x620E40））
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 28) + 16) + 108);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
      break;
    case 4:  // case 4 分派（铁笼/监狱（CNTrapCage，0x620BD0-0x620E40））
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 32) + 16) + 108);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
      break;
    case 6:  // case 6 分派（铁笼/监狱（CNTrapCage，0x620BD0-0x620E40））
      v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 16) + 108);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
      break;
    default:
      break;
  }
  v4 = *(uint32_t *)(v3 + 112);  // 读字段 v4 = v3+112（pHostComp）
  pThis_57 = *((int **)this + 87);
  v9 = (float)pThis_57[1];
  v8 = (float)*pThis_57;
  v6 = (uint64_t)sub_4049C0(v8, v9, v4 - 1, 98);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  HIDWORD(v6) = *(uint32_t *)this;  // 调 取 64 位值高 32 位
  *((uint32_t *)this + 170) = v6;  // 写字段 this[170]（宽4字节）
  *((uint32_t *)this + 171) = v6;  // 写字段 this[171]（宽4字节）
  (*(void (/*thiscall*/ **)(void *, int))(HIDWORD(v6) + 596))(this, 1);  // 虚函数调用 槽+596：[RTTI: IRDCollisionObject__vmt254…
  *((uint32_t *)this + 172) = 0;  // 写字段 this+172（pAppendVecEnd）
  *((uint8_t *)this + 700) = 0;  // 写字段 this+700（bSnapshot700）
  return sub_4015C0("JAIL_CRASH", 0xAu);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x620D60 CNTrapCage__vmt1F4 —— 铁笼收笼装载 vmt1F4
//     +976 空且来客类别(虚 44)为 273 或 529 时记为笼内目标：存坐标(虚 120/124)，sub_620B50 摘旧登记后 sub_428430 入 dword_9B9420 表，
//    对齐笼位（虚 128/124/120 换算）并虚 596(0)/676(2) 置开合态；末尾走基类 vmt1F4。
// ------------------------------------------------------------
int /*thiscall*/ CNTrapCage__vmt1F4(int *this, int nArg2, float *pArg3, char pszArg4)  // 函数定义: 铁笼收笼装载 vmt1F4
{
  uint32_t *v5; // edi
  int v6; // eax
  int uCfgE976; // ecx  | +0x03D0 → uCfgE976〔族字典〕（族字典）
  int *uCfgE976_; // ecx
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax

  v5 = (uint32_t *)nArg2;
  if ( *(this + 244) == 0  // this+244 动画同步浮点参数
    && ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 44))(nArg2) == 273  // 虚调用 vt+44（nArg2 虚表槽）
     || (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 44))(v5) == 529) )  // 虚调用 vt+44（v5 虚表槽）
  {
    *(this + 244) = (int)v5;  // 写字段 this+244（fSyncValue） ← (int)v5
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 120))(v5);  // 虚调用 vt+120（v5）转发(对象+缓冲)
    uCfgE976 = *(this + 244);  // 读字段 fld_e244 = this+244（fSyncValue）
    *(this + 245) = v6;  // 写字段 this+245 ← v6
    *(this + 246) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uCfgE976 + 124))(uCfgE976);  // 虚调用 vt+124（fld_e244）目标坐标y下界
    nArg2 = *(this + 244);  // 读字段 nArg2 = this+244（fSyncValue）
    if ( nArg2 != 0 )
    {
      sub_620B50(nArg2);  // sub_620B50 —— 全局表按值删除
      sub_428430(&dword_9B9420, &nArg2);  // sub_428430 —— STL 内联 vector push_back（4B 元素）
    }
    uCfgE976_ = (int *)*(this + 244);  // this+244 动画同步浮点参数
    v9 = *uCfgE976_;
    v10 = (*(int (/*thiscall*/ **)(int *))(*uCfgE976_ + 128))(uCfgE976_);  // 虚调用 vt+128（fld_e2442）目标坐标y上界
    v11 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v10);  // 虚调用 vt+124（this）目标坐标y下界
    v12 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v11 - 1);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(v9 + 108))(*(this + 244), v12);  // this+244 动画同步浮点参数
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);  // 虚调用 vt+596（this 虚表槽）
    (*(void (/*thiscall*/ **)(int *, int))(*this + 676))(this, 2);  // 虚调用 vt+676（this）队伍编号刷新
  }
  return CNRDPassiveObject__vmt1F4(this, v5, pArg3, pszArg4);  // 返回 调 CNRDPassiveObject__vmt1F4
}



// ------------------------------------------------------------
// 0x620E40 CNTrapCage__vmt14C
//   【铁笼】tick：挂载 Trap/Animation/CageBack.ani 背板动画
// ------------------------------------------------------------
int /*thiscall*/ CNTrapCage__vmt14C(int *this)  // 函数定义: 位置采样
{
  int v2; // eax
  int v3; // ebx
  char *v4; // eax
  char *v5; // edi
  int v6; // eax
  int fld_e29; // ecx
  int fld_e247; // edi  | +0x03DC → uCfgA988〔族字典〕（族字典）
  int v9; // eax
  int v10; // eax
  int result; // eax
  int *uCfgE976; // eax
  int *pThis; // ecx
  int uCfgE976_; // ecx  | +0x03D0 → uCfgE976〔族字典〕（族字典）
  int v15; // edi
  int v16; // edi
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // [esp-8h] [ebp-20h]

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) == 0 )  // this+972 叉子缩放计数
  {
    v2 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v3 = 0;
    if ( v2 != 0 )
      v3 = sub_431860(v2, "PassiveObject/MapObject/Trap/Animation/CageBack.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
    v4 = (char *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
    v5 = v4;
    if ( v4 != nullptr )  // 若 v4 有效（非空）
    {
      sub_44E0D0(v4, v3, 0);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)v5 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
      v6 = (int)v5;
    }
    else
    {
      v6 = 0;
    }
    fld_e29 = *(this + 29);  // 读字段 fld_e29 = this+29
    *(this + 247) = v6;  // 写字段 this+247 ← v6
    sub_45FE80(fld_e29, (int)v5, 2, 0, v6, 0, 0);  // sub_45FE80 —— 对象注册
    fld_e247 = *(uint32_t *)*(this + 247);  // this+988〔uCfgA988(推断)〕
    v20 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) - 2;  // 虚调用 vt+128（this）目标坐标y上界
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
    v10 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v9 - 2);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e247 + 112))(*(this + 247), v10);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    (*(void (/*thiscall*/ **)(uint32_t, int *))(*(uint32_t *)*(this + 247) + 60))(*(this + 247), this);  // 虚函数调用 槽+60：取消动作槽（79 行：4BE520 + 48
    sub_4A06D0(v20);  // sub_4A06D0 —— 绑定目标对象并记录相对偏移
    *((uint8_t *)this + 972) = 1;  // 写字段 this+972（uCfgD972）
  }
  result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
  if ( result == 0 )
  {
    uCfgE976 = (int *)*(this + 244);  // this+244 动画同步浮点参数
    pThis = this;
    if ( uCfgE976 == nullptr )  // 若 fld_e244 为空
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    goto LABEL_14;
  }
  uCfgE976_ = *(this + 244);  // 读字段 fld_e2442 = this+244（fSyncValue）
  if ( uCfgE976_ != 0 )
  {
    v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)uCfgE976_ + 128))(uCfgE976_);  // 虚调用 vt+128（fld_e2442）目标坐标y上界
    result = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    if ( v15 > result )
    {
      uCfgE976 = (int *)*(this + 244);  // this+244 动画同步浮点参数
      pThis = this;
LABEL_14:
      v16 = *uCfgE976;
      v17 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(pThis);  // 虚调用 vt+128（this）目标坐标y上界
      v18 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v17);  // 虚调用 vt+124（this）目标坐标y下界
      v19 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v18 - 1);  // 虚调用 vt+120（this）转发(对象+缓冲)
      return (*(int (/*thiscall*/ **)(uint32_t, int))(v16 + 112))(*(this + 244), v19);  // this+244 动画同步浮点参数
    }
  }
  return result;
}



// ============================================================
// 【分区 3】吊灯（CNChandelier，0x620FE0-0x6214D0）
// 证据: SIZZLE_LOOP（燃烧滋滋循环）/ CHANDELIER_CUT（坠落切断）/ CHANDELIER_BROKEN（破碎切换）
// ============================================================

// ------------------------------------------------------------
// 0x620FE0 CNChandelier__vmtC —— 吊灯构造初始化 vmtC
//    基类后经虚 596(this,0) 停用动画层 0（悬挂静止）。
// ------------------------------------------------------------
int /*thiscall*/ CNChandelier__vmtC(int *this)  // 函数定义: 吊灯构造初始化 vmtC
{
  CNRDPassiveObject__vmtC(this);
  return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 596))(this, 0);  // 虚调用 vt+596（this 虚表槽）
}



// ------------------------------------------------------------
// 0x621000 sub_621000 —— 吊灯坠落触发
//    存活时把挂点件(+112)偏移[9]置 -1500 并标脏，经 sub_494F60(2,-1) 写属性槽 2；随后虚 604(0) 停摆、596(1) 启用、372(200) 切坠落状态。
// ------------------------------------------------------------
int /*thiscall*/ sub_621000(uint32_t *this)  // sub_621000 —— 吊灯坠落触发
{
  uint32_t *fld_e28; // edi

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    fld_e28 = (uint32_t *)*(this + 28);  // this+28 【推断】逐帧驱动对象
    if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[9] != -1500 )  // 虚调用 vt+308（fld_e28）是否本地玩家
    {
      fld_e28[9] = -1500;
      *((uint8_t *)fld_e28 + 196) = 1;  // 写字段 fld_e28[196]（宽1字节）
      sub_494F60(2, -1);  // sub_494F60 —— 属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);  // 虚调用 vt+604（this）收招例程
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 596))(this, 1);  // 虚调用 vt+596（this 虚表槽）
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 200);  // 虚调用 vt+372（this）数值写入
}



// ------------------------------------------------------------
// 0x621070 CNChandelier__vmt14C
//   【吊灯】SIZZLE_LOOP —— 燃烧滋滋循环音
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNChandelier__vmt14C(uint32_t *this)  // 函数定义: 位置采样
{
  unsigned int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 993) == 0 )  // this+993 【推断】状态块字 C
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
      this,
      "SIZZLE_LOOP",  // 资源/动画 TAG SIZZLE_LOOP
      10000,
      0,
      0);
    *((uint8_t *)this + 993) = 1;  // 写字段 this+993（uStateC993）
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) == 0  // 虚调用 vt+128（this）目标坐标y上界
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
  }
  result = *(this + 247);  // 读字段 result = this+247
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( result > *(this + 247) )  // this+988〔uCfgA988(推断)〕
    {
      result = sub_621000(this);  // sub_621000 —— 吊灯坠落触发
      *(this + 247) = 0;  // 写字段 this+247 ← 0
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x621100 sub_621100 —— 吊灯缓冲释放
//    free +976 处对象数组并清零 +976..+988 与 +992 标志；【推断】析构清扫路径（本区无直接调用点）。
// ------------------------------------------------------------
void /*thiscall*/ sub_621100(int this)  // sub_621100 —— 吊灯缓冲释放
{
  if ( *(uint32_t *)(this + 976) != 0 )  // this+976 首帧门字节
    j__free(*(void **)(this + 976));  // 释放堆块
  *(uint32_t *)(this + 976) = 0;  // 写字段 this+976（uCfgE976） ← 0
  *(uint32_t *)(this + 980) = 0;  // 写字段 this+980（uCfgF980） ← 0
  *(uint32_t *)(this + 984) = 0;  // 写字段 this+984（aStateBlk984） ← 0
  *(uint32_t *)(this + 988) = 0;  // 写字段 this+988（uCfgA988） ← 0
  *(uint8_t *)(this + 992) = 0;  // 写字段 this+992（uCfgB992） ← 0
}



// ------------------------------------------------------------
// 0x621140 sub_621140 —— 吊灯落体复位
//    对 +144 键帧表五段撤销：虚 204 依次 (-100,表+4)(-200,表+0)(100,表+20)(100,表+24)(100,表+28)，清 +112 的 +36 与 +688；
//    随后虚 372(200) 回状态并清 +992/+993 燃烧标志。
// ------------------------------------------------------------
int /*thiscall*/ sub_621140(uint32_t *this, int nArg2)  // sub_621140 —— 吊灯落体复位
{
  int v3; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    -100,
    *(uint32_t *)(*(this + 36) + 4),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    -200,
    *(uint32_t *)*(this + 36),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    100,
    *(uint32_t *)(*(this + 36) + 20),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    100,
    *(uint32_t *)(*(this + 36) + 24),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    100,
    *(uint32_t *)(*(this + 36) + 28),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  *(uint32_t *)(*(this + 28) + 36) = 0;  // this+28 【推断】逐帧驱动对象
  v3 = *this;
  *(this + 172) = 0;  // 写字段 this+172（pAppendVecEnd） ← 0
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 372))(this, 200);  // 虚函数调用 槽+372：目标点写入
  *((uint8_t *)this + 992) = 0;  // 写字段 this+992（uCfgB992）
  *((uint8_t *)this + 993) = 0;  // 写字段 this+993（uStateC993）
  return result;
}



// ------------------------------------------------------------
// 0x621200 sub_621200
//   【吊灯】CHANDELIER_CUT —— 坠落切断触发
// ------------------------------------------------------------
int /*thiscall*/ sub_621200(uint32_t *this)  // 函数定义: 触发切断坠落
{
  int pThis_9; // eax
  int v3; // edx

  pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  v3 = *this;
  *(this + 247) = pThis_9 + 700;  // 写字段 this+247 ← pThis_9 + 700
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 208))(this, *(uint32_t *)(*(this + 36) + 4));  // this+36 物品状态字
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));  // 虚调用 vt+208（this）动画件回挂
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 20));  // 虚调用 vt+208（this）动画件回挂
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 24));  // 虚调用 vt+208（this）动画件回挂
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 28));  // 虚调用 vt+208（this）动画件回挂
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 12));  // 虚调用 vt+196（this）物件非空判定
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    -100,
    *(uint32_t *)(*(this + 36) + 8),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    -200,
    *(uint32_t *)(*(this + 36) + 16),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  *(uint8_t *)(*(uint32_t *)(*(this + 36) + 8) + 161) = 0;  // this+36 物品状态字
  return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
           this,
           "CHANDELIER_CUT",  // 资源/动画 TAG CHANDELIER_CUT
           -1,
           0,
           0);
}



// ------------------------------------------------------------
// 0x621310 CNChandelier__vmt12C
//   【吊灯】CHANDELIER_BROKEN —— 吊灯破碎切换
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNChandelier__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  unsigned int result; // eax
  unsigned int i; // edi
  int pRopeObj976; // ecx  | +0x03D0 → 吊索对象（6213F0 受击回调：fld_3D0 = *(+976)）（证据 va=006213F0）（CNChandelier；va=006213F0）
  int pRopeObj976_; // ecx  | +0x03D0 → 吊索对象（6213F0 受击回调：fld_3D0 = *(+976)）（证据 va=006213F0）（CNChandelier；va=006213F0）

  CNRDPassiveObject__vmt12C(this, nArg2);
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 44))(nArg2);  // 虚调用 vt+44（nArg2 虚表槽）
  if ( result == 529 )
  {
    for ( i = 0; ; ++i )
    {
      pRopeObj976 = *(this + 244);  // 读字段 fld_e244 = this+244（fSyncValue）
      if ( pRopeObj976 == 0 )
        break;
      result = (*(this + 245) - pRopeObj976) >> 2;  // this+980〔nRopeCnt980〕
      if ( i >= result )
        break;
      result = *(this + 244) + 4 * i;  // this+244 熄灯相关时刻/状态
      if ( nArg2 == *(uint32_t *)result )
      {
        *(uint32_t *)result = 0;
        memcpy_0(
          (void *)(4 * i + *(this + 244)),  // this+244 熄灯相关时刻/状态
          (const void *)(4 * i + *(this + 244) + 4),  // this+244 熄灯相关时刻/状态
          4 * ((int)(*(this + 245) - (4 * i + *(this + 244) + 4)) >> 2));  // this+980〔nRopeCnt980〕
        *(this + 245) -= 4;  // this+980〔nRopeCnt980〕
        pRopeObj976_ = *(this + 244);  // 读字段 fld_e2442 = this+244（fSyncValue）
        if ( pRopeObj976_ == 0 || (result = (*(this + 245) - pRopeObj976_) >> 2) == 0 )  // this+980〔nRopeCnt980〕
          result = sub_621200(this);  // 调 触发切断坠落
      }
    }
  }
  if ( (uint32_t *)nArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10000);  // 虚调用 vt+216（this）全场广播
    return (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
             this,
             "CHANDELIER_BROKEN",  // 资源/动画 TAG CHANDELIER_BROKEN
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x6213F0 CNChandelier__vmt200 —— 吊灯受击回调 vmt200
//    先走基类，若挂链件数组(+976/+980)为空则调 sub_621200 触发切断坠落，并置 +992 挂链状态位。
// ------------------------------------------------------------
int /*thiscall*/ CNChandelier__vmt200(int this, int nArg2, float *pArg3, char pszArg4)  // 函数定义: 吊灯受击回调 vmt200
{
  int v5; // eax
  int pRopeObj976; // ecx  | +0x03D0 → 吊索对象（6213F0 受击回调：fld_3D0 = *(+976)）（证据 va=006213F0）（CNChandelier；va=006213F0）
  int v7; // edi

  v5 = CNRDPassiveObject__vmt200((int *)this, nArg2, pArg3, pszArg4);  // v5 = 调 CNRDPassiveObject__vmt200
  pRopeObj976 = *(uint32_t *)(this + 976);  // 读字段 fld_3D0 = this+976（uCfgE976）
  v7 = v5;
  if ( pRopeObj976 == 0 || (*(uint32_t *)(this + 980) - pRopeObj976) >> 2 == 0 )  // this+980 吊索计数
    sub_621200((uint32_t *)this);  // 调 触发切断坠落
  *(uint8_t *)(this + 992) = 1;  // 写字段 this+992（uCfgB992） ← 1
  return v7;
}



// ------------------------------------------------------------
// 0x621440 sub_621440 —— 吊灯砸击范围判定
//    nArg2 与自身的 Y(虚 124) 差须在 [-30,+70]；再按朝向(虚 152 为 1/0)比较双方 X(虚 120) 前后，命中返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_621440(void *this, int nArg2)  // sub_621440 —— 吊灯砸击范围判定
{
  int pThis_7C; // ebx
  int pThis_46; // ebx
  int v5; // edi
  int v7; // edi

  pThis_7C = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this) - 30;  // 虚调用 vt+124（this）目标坐标y下界
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) >= pThis_7C )  // 虚调用 vt+124（nArg2）目标坐标y下界
  {
    pThis_46 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this) + 70;  // 虚调用 vt+124（this）目标坐标y下界
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2) <= pThis_46 )  // 虚调用 vt+124（nArg2）目标坐标y下界
    {
      if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 1 )  // 虚调用 vt+152（this）取值(参数)
      {
        v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 虚调用 vt+120（nArg2）转发(对象+缓冲)
        if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) < v5 )  // 虚调用 vt+120（this）转发(对象+缓冲)
          return 1;  // 返回 1(成功)
      }
      else if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 152))(this) == 0 )  // 虚调用 vt+152（this）取值(参数)
      {
        v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 虚调用 vt+120（nArg2）转发(对象+缓冲)
        if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) > v7 )  // 虚调用 vt+120（this）转发(对象+缓冲)
          return 1;  // 返回 1(成功)
      }
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x6214D0 sub_6214D0 —— CNWindSimulation 构造
//    sub_4B1030 挂 IRDAppendage 基类后改写虚表为 vftbl_CNWindSimulation，再 sub_6524C0 初始化风场参数(nArg2/nArg3)。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_6214D0(uint32_t *this, int nArg2, int nArg3)  // sub_6214D0 —— 结果 = CNWindSimulation 构造
{
  sub_4B1030(this);  // sub_4B1030 —— IRDAppendage 基类构造
  *this = &vftbl_CNWindSimulation;  // 装虚表/取地址：← vftbl_CNWindSimulation
  sub_6524C0(nArg2, nArg3);  // sub_6524C0 —— 风场参数初始化（CNWindSimulation）
  return this;
}



// ============================================================
// 【分区 4】风扇/旋涡（CNWindSimulation/CNWindShaker/CNSpiner，0x621530-0x622E10）
// 证据: FAN_ROTATE_LOOP + FAN_WIND_BLOW_LOOP（风扇双循环音）、IRON_HIT / SPINNER_ON /
//       SPINNER_LOOP / SPINNER_BREAK（旋涡）、Trap/Particle/SpinerMovePath.ptl +
//       SpinerBubble.ptl（旋涡移动路径与气泡粒子）
// ============================================================

// ------------------------------------------------------------
// 0x621530 CNWindSimulation__vmt4 —— 风场周期更新 vmt4
//    基类后以 +8 时钟判定：自上次起满 30 单位才 sub_652500 重算风场（供风机附近角色受力）。
// ------------------------------------------------------------
int /*thiscall*/ CNWindSimulation__vmt4(int *this)  // 函数定义: 风场周期更新 vmt4
{
  int result; // eax
  int pThis_2; // eax

  IRDAppendage__vmt4(this);
  result = sub_699000((int)(this + 2));  // 【clock_now(clk)】
  if ( result >= 30 )
  {
    pThis_2 = sub_699000((int)(this + 2));  // 【clock_now(clk)】
    return sub_652500(pThis_2);  // sub_652500 —— 风场重算（位移 + 可通行判定 + 时钟复位）
  }
  return result;
}



// ------------------------------------------------------------
// 0x621560 CNWindSimulation__vmt0 —— 风场删除析构 vmt0
//    sub_621590 反初始化后按 pszArg2 位 0 决定 j__free（标量删除特征）。
// ------------------------------------------------------------
void */*thiscall*/ CNWindSimulation__vmt0(void *Block, char pszArg2)  // 函数定义: 风场删除析构 vmt0
{
  sub_621590();  // sub_621590 —— 风场反初始化
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x621590 sub_621590 —— 风场反初始化
//    虚表回退 vftbl_IRDAppendage 并走 sub_5F6640 释放，再换 vftbl_nengine__IObject（+8 换表、+12 清零）。
// ------------------------------------------------------------
int /*thiscall*/ sub_621590(int this)  // sub_621590 —— 风场反初始化
{
  int result; // eax

  *(uint32_t *)this = &vftbl_IRDAppendage;  // 构造装配 vftable：IRDAppendage
  result = sub_5F6640((uint32_t *)this);  // 调 基类析构
  *(uint32_t *)(this + 8) = &vftbl_nengine__IObject;  // 写字段 this+8（nSkillRec8） ← &vftbl_nengine__IObject
  *(uint8_t *)(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  return result;
}



// ------------------------------------------------------------
// 0x6215E0 sub_6215E0 —— 旋涡成员存在性查询
//    在 +996 起的对象表中线性查找 nArg2，命中返回 1（旋涡对已登记目标的判定）。
// ------------------------------------------------------------
char /*thiscall*/ sub_6215E0(uint32_t *this, int nArg2)  // sub_6215E0 —— 旋涡成员存在性查询
{
  int fld_e249; // esi
  unsigned int i; // edx

  fld_e249 = *(this + 249);  // 读字段 fld_e249 = this+249
  for ( i = 0; fld_e249 != 0 && i < (*(this + 250) - fld_e249) >> 2; ++i )  // this+1000〔bGrassFilter1000(推断)〕
  {
    if ( *(uint32_t *)(*(this + 249) + 4 * i) == nArg2 )  // this+996〔bCfgC996(推断)〕
      return 1;  // 返回 1(成功)
  }
  return 0;
}



// ------------------------------------------------------------
// 0x621630 sub_621630 —— 风扇启动
//    经虚 51 分派 4 号与 3 号两路音效(表+8/+12)并调虚 151(this,1)；登记时钟(+988)后置 +972/+973 运行标志、+980=+984 帧源指针、
//    坐标对 +680:+684 设 999999999 锁定值，虚 93(100) 后按表[3] 决定 +52 标志。
// ------------------------------------------------------------
int /*thiscall*/ sub_621630(int **this, int nArg2)  // sub_621630 —— 风扇启动
{
  int *fld_e87; // eax
  int *v4; // eax
  int result; // eax

  ((void (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    4,
    (*(this + 36))[2],  // this+36 物品状态字
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(int **, int, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
    this,
    3,
    (*(this + 36))[3],  // this+36 物品状态字
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(int **, int))(*this)[151])(this, 1);
  *(this + 247) = (int *)sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  fld_e87 = *(this + 87);  // 读字段 fld_e87 = this+87
  *((uint8_t *)this + 984) = 0;  // 写字段 this+984（aStateBlk984）
  *((uint8_t *)this + 973) = 1;  // 写字段 this+973（bLanded973）
  *((uint8_t *)this + 972) = 1;  // 写字段 this+972（uCfgD972）
  v4 = (int *)*fld_e87;
  *(this + 245) = v4;  // 写字段 this+245 ← v4
  *(this + 244) = v4;  // 写字段 this+244（fSyncValue） ← v4
  *(this + 170) = (int *)999999999;  // 写字段 this+170 ← (int *)999999999
  *(this + 171) = (int *)999999999;  // 写字段 this+171 ← (int *)999999999
  ((void (/*thiscall*/ *)(int **, int))(*this)[93])(this, 100);
  if ( (*(this + 87))[3] != 0 )  // this+348〔pParamTbl348〕
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[15])(this);
    *(uint8_t *)(result + 52) = 0;  // 写字段 result+52（bAuraState） ← 0
  }
  else
  {
    result = ((int (/*thiscall*/ *)(int **))(*this)[15])(this);
    *(uint8_t *)(result + 52) = 1;  // 写字段 result+52（bAuraState） ← 1
  }
  return result;
}



// ------------------------------------------------------------
// 0x621EF0 CNWindShaker__vmt14C
//   【风扇】FAN_ROTATE_LOOP + FAN_WIND_BLOW_LOOP —— 旋转/吹风双循环音
// ------------------------------------------------------------
char /*thiscall*/ CNWindShaker__vmt14C(uint32_t *this)  // 函数定义: 位置采样
{
  unsigned int pThis_9; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *((uint8_t *)this + 972) != 0 || (LOBYTE(pThis_9) = *((uint8_t *)this + 973), (uint8_t)pThis_9 != 0) )  // this+972 叉子缩放计数
  {
    pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( *(this + 247) + 250 < pThis_9 )  // this+988〔uCfgA988(推断)〕
    {
      *(this + 247) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
      LOBYTE(pThis_9) = sub_621DC0(this);  // 调 取 16 位值低 8 位
      if ( (uint8_t)pThis_9 != *((uint8_t *)this + 984) )  // this+984 状态块起址
      {
        *((uint8_t *)this + 984) = pThis_9;  // 写字段 this+984（aStateBlk984）
        if ( (uint8_t)pThis_9 != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t *))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
            this,
            1,
            *(uint32_t *)*(this + 36),  // this+36 物品状态字
            0,
            0,
            0,
            0,
            this);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
            this,
            100,
            *(uint32_t *)(*(this + 36) + 4),  // this+36 物品状态字
            0,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
            this,
            "FAN_ROTATE_LOOP",  // 资源/动画 TAG FAN_ROTATE_LOOP
            12345,
            0,
            0);
          LOBYTE(pThis_9) = (*(int (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
                         this,
                         "FAN_WIND_BLOW_LOOP",  // 资源/动画 TAG FAN_WIND_BLOW_LOOP
                         12346,
                         0,
                         0);
        }
        else
        {
          LOBYTE(pThis_9) = sub_621770(this);  // 调 取 16 位值低 8 位
        }
      }
    }
  }
  return pThis_9;
}



// ------------------------------------------------------------
// 0x621F20 sub_621F20 —— 旋涡气泡粒子引用清零
//     +980/+984 两个粒子件指针置空（不动资源）。
// ------------------------------------------------------------
int /*thiscall*/ sub_621F20(uint32_t *this)  // sub_621F20 —— 旋涡气泡粒子引用清零
{
  *(this + 245) = 0;  // 写字段 this+245 ← 0
  *(this + 246) = 0;  // 写字段 this+246 ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x621F30 sub_621F30 —— 旋涡气泡粒子释放
//    与 sub_620210 同构（差异：成对释放 +980 与 +984 两件，各走虚槽 0 后置空）。
// ------------------------------------------------------------
int /*thiscall*/ sub_621F30(uint32_t *this)  // sub_621F30 —— 旋涡气泡粒子释放
{
  int (/*thiscall*/ ***fld_e245)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e246)(uint32_t, int); // ecx

  fld_e245 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 245);  // this+980〔uCfgF980(推断)〕
  if ( fld_e245 != nullptr )  // 若 fld_e245 有效（非空）
    result = (**fld_e245)(fld_e245, 1);  // 调 fld_e245 的虚函数（vt+0）
  fld_e246 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 246);  // this+984〔aStateBlk984(推断)〕
  *(this + 245) = 0;  // 写字段 this+245 ← 0
  if ( fld_e246 != nullptr )  // 若 fld_e246 有效（非空）
    result = (**fld_e246)(fld_e246, 1);  // 调 fld_e246 的虚函数（vt+0）
  *(this + 246) = 0;  // 写字段 this+246 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x621F70 CNSpiner__vmt12C
//   【旋涡】复用 CHANDELIER_BROKEN 作破碎音
// ------------------------------------------------------------
void /*thiscall*/ CNSpiner__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
      this,
      "CHANDELIER_BROKEN",  // 资源/动画 TAG CHANDELIER_BROKEN
      -1,
      0,
      0);
}



// ------------------------------------------------------------
// 0x621FA0 CNSpiner__vmt2B4
//   【旋涡】IRON_HIT（受击铁音）/ SPINNER_BREAK（旋涡破碎）
// ------------------------------------------------------------
int /*thiscall*/ CNSpiner__vmt2B4(int *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int result; // eax

  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "IRON_HIT", -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
  if ( *(this + 170) > 0 )  // this+680〔nSnapshot680〕
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 3, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
  }
  else
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    return (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
             this,
             "SPINNER_BREAK",  // 资源/动画 TAG SPINNER_BREAK
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x622020 sub_622020 —— 旋涡引爆（范围伤害）
//    存活且未处于状态 2 时切虚 560 状态 2；由虚 60 取位置块拷入 0x62 字节碰撞包，以虚 136/140 做地图命中查询后，
//    经全局命中管理器 dword_8F8520 链（8/36/32/48/40/60）以 98 号参数提交。
// ------------------------------------------------------------
int /*thiscall*/ sub_622020(uint32_t *this)  // sub_622020 —— 旋涡引爆（范围伤害）
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

  v15[25] = dword_796E50;  // dword_796E50 —— 栈检 cookie
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);  // 虚调用 vt+88（this 虚表槽）
    if ( (uint8_t)result != 0 && *(this + 240) != 2 )  // this+240 动画同步参数 B
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
      sub_423A20((int)v15);  // sub_423A20 —— 小结构初始化（0-100 刻度）
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 60))(this);  // 虚调用 vt+60（this）对象销毁/释放
      v4 = (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v3 + 104) + 16))(*(uint32_t *)(v3 + 104));  // 虚函数调用 槽+16：状态切换槽：对象状态 17→18（44ABE0/44E850 + d
      v5 = *this;
      qmemcpy(v15, v4, 0x62u);  // 调 内存块拷贝(内联展开)
      *(uint32_t *)((char *)&v15[3] + 3) = 0;
      *(uint32_t *)((char *)&v15[4] + 3) = 0;
      v13 = (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 120))(this);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
      v7 = *this;
      v14 = v6;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(v7 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 136))(this, v13, v14, 0) != 0  // 虚调用 vt+136（this）目标挂接
        || (uint8_t)(result = (*(int (/*thiscall*/ **)(uint32_t *, int *, int *, int, int, int, int, int))(*this + 140))(  // 虚调用 vt+140（this）日志(变参 printf)
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
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);  // 虚调用 vt+8（dword_8F8520 虚表槽）
        v9 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
        v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);  // 虚调用 vt+48（this）归属坐标x
        (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);  // dword_8F8520 —— 虚表 +120 调用
        v11 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 虚调用 vt+52（this）归属坐标y
        (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);  // dword_8F8520 —— 虚表 +120 调用
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);  // 虚调用 vt+32（dword_8F8520 虚表槽）
        (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v15, 98);  // 虚调用 vt+48（dword_8F8520）归属坐标x
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);  // 虚调用 vt+40（dword_8F8520）条件查询(273等)
        return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6221A0 sub_6221A0 —— 旋涡方位复位
//    先经虚 208 归还表 +8/+12/+16 三点，再按朝向号 2/3/4 取表对应项以虚 204(100,...) 重设，其他值直接返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_6221A0(uint32_t *this, int nArg2)  // sub_6221A0 —— 旋涡方位复位
{
  int result; // eax
  uint32_t *fld_e36; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));  // 虚调用 vt+208（this）动画件回挂
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));  // 虚调用 vt+208（this）动画件回挂
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));  // 虚调用 vt+208（this）动画件回挂
  if ( nArg2 == 2 )
  {
    fld_e36 = (uint32_t *)(*(this + 36) + 8);  // this+36 物品状态字
  }
  else if ( nArg2 == 3 )
  {
    fld_e36 = (uint32_t *)(*(this + 36) + 12);  // this+36 物品状态字
  }
  else
  {
    result = nArg2 - 4;
    if ( nArg2 != 4 )
      return result;
    fld_e36 = (uint32_t *)(*(this + 36) + 16);  // this+36 物品状态字
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           *fld_e36,
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x622230 CNSpiner__vmt1D8
//   【旋涡】SPINNER_ON（启动）/ SPINNER_LOOP（循环）
// ------------------------------------------------------------
int /*thiscall*/ CNSpiner__vmt1D8(uint32_t *this, int nArg2, int pArg3, int nArg4, int nArg5)  // 实现：(旋涡)SPINNER_ON（启动）/ SPINNER_LOOP（循环）
{
  int result; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  uint32_t *fld_e36; // eax
  int fld_e34; // eax

  if ( *(this + 240) == 4 )  // this+240 动画同步参数 B
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 14530);  // 虚调用 vt+216（this）全场广播
  CNRDPassiveObject__vmt1D8(this, nArg2, pArg3, nArg2, pArg3, nArg4, nArg5);
  if ( nArg2 == 2 )
  {
    sub_4926A0(*(this + 34));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
    fld_e34 = *(this + 34);  // 读字段 fld_e34 = this+34
    goto LABEL_18;
  }
  if ( nArg2 == 3 )
  {
    sub_4926A0(*(uint32_t *)*(this + 36));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
    fld_e34 = *(uint32_t *)*(this + 36);  // this+36 物品状态字
LABEL_18:
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 196))(this, fld_e34);  // 虚调用 vt+196（this）物件非空判定
    goto LABEL_19;
  }
  result = nArg2 - 4;
  if ( nArg2 != 4 )
    return result;
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SPINNER_ON", -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
  (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "SPINNER_LOOP", 14530, 0, 0);  // 虚调用 vt+212（this 虚表槽）
  sub_4926A0(*(uint32_t *)(*(this + 36) + 4));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));  // 虚调用 vt+196（this）物件非空判定
  v7 = **(uint32_t **)(pArg3 + 4);  // pArg3+4〔宿主对象〕
  if ( v7 > 180 )
  {
    v8 = v7 - 225;  // 计算 v8 = v7 - 225
    if ( v8 == 0 )
      goto LABEL_13;
    v9 = v8 - 45;  // 计算 v9 = v8 - 45
    if ( v9 == 0 )
    {
LABEL_14:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));  // 虚调用 vt+208（this）动画件回挂
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));  // 虚调用 vt+208（this）动画件回挂
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));  // 虚调用 vt+208（this）动画件回挂
      fld_e36 = (uint32_t *)(*(this + 36) + 16);  // this+36 物品状态字
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
               this,
               100,
               *fld_e36,
               0,
               0,
               0,
               0);
    }
    if ( v9 == 45 )
    {
LABEL_13:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));  // 虚调用 vt+208（this）动画件回挂
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));  // 虚调用 vt+208（this）动画件回挂
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));  // 虚调用 vt+208（this）动画件回挂
      fld_e36 = (uint32_t *)(*(this + 36) + 12);  // this+36 物品状态字
      return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
               this,
               100,
               *fld_e36,
               0,
               0,
               0,
               0);
    }
LABEL_19:
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 12));  // 虚调用 vt+208（this）动画件回挂
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));  // 虚调用 vt+208（this）动画件回挂
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 8));  // 虚调用 vt+208（this）动画件回挂
  }
  if ( v7 != 180 )
  {
    switch ( v7 )  // 按 v7 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        return sub_6221A0(this, 2);  // sub_6221A0 —— 旋涡方位复位
      case 45:  // case 45 = ENUM_CMDPACKET_USE_COIN
      case 135:
        goto LABEL_13;
      case 90:  // case 90 = ENUM_CMDPACKET_REMOVE_PRIVATE_STORE
        goto LABEL_14;
      default:
        goto LABEL_19;
    }
  }
  return sub_6221A0(this, 2);  // sub_6221A0 —— 旋涡方位复位
}



// ------------------------------------------------------------
// 0x6224F0 sub_6224F0 —— 旋涡范围探测
//    以 sub_4E7F30(this,200,200,buf) 查询 200x200 内是否有可选目标，命中即真；结果缓冲用后释放。
// ------------------------------------------------------------
bool /*thiscall*/ sub_6224F0(uint32_t *this)  // sub_6224F0 —— 旋涡范围探测
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
  v1 = sub_4E7F30(this, 200, 200, (int)v3) != 0;  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 释放堆块
  return v1;
}



// ------------------------------------------------------------
// 0x622560 sub_622560 —— 旋涡随机抛射
//    存活且可动时 sub_432FA0 播种并初始化 0x62 字节包；方向取 0/45/90/135 之一加基准 +90 后取模 360，半径 100/100；
//    经虚 136/140 命中查询后由 dword_8F8520 以 98 提交，再由 sub_431230 打包方向并虚 560(this,4,...) 生成投射物。
// ------------------------------------------------------------
void /*usercall*/ sub_622560(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>)  // sub_622560 —— 旋涡随机抛射
{
  int v4; // eax
  int nRand; // edx
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

  v27[25] = dword_796E50;  // dword_796E50 —— 栈检 cookie
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0  // 虚调用 vt+308（pDwArg1）是否本地玩家
    && (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 88))(pDwArg1) != 0 )  // 虚调用 vt+88（pDwArg1 虚表槽）
  {
    sub_432FA0();  // sub_432FA0 —— srand 播种
    sub_423A20((int)v27);  // sub_423A20 —— 小结构初始化（0-100 刻度）
    v4 = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 60))(pDwArg1, nArg2, nArg3);  // 虚调用 vt+60（pDwArg1）对象销毁/释放
    qmemcpy(  // 调 内存块拷贝(内联展开)
      v27,
      (const void *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v4 + 104) + 16))(*(uint32_t *)(v4 + 104)),  // 虚函数调用 槽+16：状态切换槽：对象状态 17→18（44ABE0/44E850 + d
      0x62u);
    v13 = 0;
    v14 = 45;
    v15 = 90;
    v16 = 135;
    v17 = 180;
    v18 = 225;
    v19 = 270;
    v20 = 315;
    nRand = (*(&v13 + rand() % 4) + v27[18] + 90) % 360;  // 调 取伪随机数
    *(uint32_t *)((char *)&v27[3] + 3) = 100;
    *(uint32_t *)((char *)&v27[4] + 3) = 100;
    v27[18] = nRand;
    v25 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
    v6 = (*(int (/*thiscall*/ **)(int *, int, int, int, int, int, int, int, int))(*pDwArg1 + 124))(  // 虚调用 vt+124（pDwArg1）目标坐标y下界
           pDwArg1,
           v13,
           v14,
           v15,
           v16,
           v17,
           v18,
           v19,
           v20);
    v7 = *pDwArg1;
    v26 = v6;
    v8 = (*(int (/*thiscall*/ **)(int *))(v7 + 128))(pDwArg1);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*pDwArg1 + 136))(pDwArg1, v25, v26, 0) != 0  // 虚调用 vt+136（pDwArg1）目标挂接
      || (*(uint8_t (/*thiscall*/ **)(int *, int *, int *, int, int, int, int, int))(*pDwArg1 + 140))(  // 虚调用 vt+140（pDwArg1）日志(变参 printf)
           pDwArg1,
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
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 9, 2);  // 虚调用 vt+8（dword_8F8520 虚表槽）
      v9 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
      v10 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 48))(pDwArg1);  // 虚调用 vt+48（pDwArg1）归属坐标x
      (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);  // dword_8F8520 —— 虚表 +120 调用
      v11 = *(uint32_t *)dword_8F8520;  // dword_8F8520 —— 虚表 +120 调用
      v12 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 52))(pDwArg1);  // 虚调用 vt+52（pDwArg1）归属坐标y
      (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);  // dword_8F8520 —— 虚表 +120 调用
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);  // 虚调用 vt+32（dword_8F8520 虚表槽）
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, v27, 98);  // 虚调用 vt+48（dword_8F8520）归属坐标x
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);  // 虚调用 vt+40（dword_8F8520）条件查询(273等)
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 虚调用 vt+60（dword_8F8520）对象销毁/释放
      Block = nullptr;
      v23 = 0;
      v24 = 0;
      v27[28] = 0;
      sub_431230((int)v21, &v27[18]);  // sub_431230 —— uint32 vector push_back
      (*(void (/*thiscall*/ **)(int *, int, uint8_t *, uint32_t, uint32_t))(*pDwArg1 + 560))(pDwArg1, 4, v21, 0, 0);  // 虚调用 vt+560（pDwArg1 虚表槽）
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 释放堆块
    }
  }
}



// ------------------------------------------------------------
// 0x6227A0 CNSpiner__vmt214 —— 旋涡抛射钩子 vmt214
//    先调 sub_622560（第三参传自身）触发抛射，再走基类 vmt214（方向/目标修正回调）。
// ------------------------------------------------------------
char /*userpurge*/ CNSpiner__vmt214@<al>(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, int nArg5)  // 实现：旋涡抛射钩子 vmt214
{
  sub_622560(pDwArg1, nArg2, (int)pDwArg1);  // sub_622560 —— 旋涡随机抛射
  return CNRDPassiveObject__vmt214(pDwArg1, nArg3, nArg4, nArg5);  // 返回 调 CNRDPassiveObject__vmt214
}



// ------------------------------------------------------------
// 0x6227D0 sub_6227D0
//   【旋涡】Trap/Particle/SpinerMovePath.ptl（移动路径）+ SpinerBubble.ptl（气泡）
// ------------------------------------------------------------
int /*thiscall*/ sub_6227D0(uint32_t *this, int nArg2)  // 实现：(旋涡)Trap/Particle/SpinerMovePath.ptl（移动路径）+ SpinerBubble.ptl（气泡）
{
  char *pObj2; // edi
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int fld_e87; // eax
  uint32_t *pMem; // eax
  uint32_t *v11; // esi
  char *v12; // eax
  const void *v13; // esi
  uint32_t *v14; // edi
  int v15; // edi
  int v16; // edi
  uint32_t *pMem2; // eax
  uint32_t *v18; // eax
  int pObj3; // eax
  double v20; // st7
  int fld_e245; // edi
  int v22; // eax
  int v23; // eax
  uint32_t *pMem3; // eax
  uint32_t *v25; // eax
  int v26; // eax
  int v27; // edx
  int pObj4; // eax
  int fld_e246; // esi
  int v30; // eax
  int v31; // eax
  int v33; // [esp+0h] [ebp-24h]
  float Block; // [esp+Ch] [ebp-18h]
  int (/*thiscall*/ ***v35)(uint32_t, int); // [esp+10h] [ebp-14h]
  char *pObj; // [esp+14h] [ebp-10h]

  pObj2 = nullptr;
  *(uint32_t *)(*(this + 28) + 36) = 0;  // this+28 【推断】逐帧驱动对象
  v4 = *this;
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 436))(this);  // 虚调用 vt+436（this）取值
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v5);  // 虚调用 vt+124（this）目标坐标y下界
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v6);  // 虚调用 vt+120（this）转发(对象+缓冲)
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v4 + 112))(this, v7);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  v8 = *this;
  *((uint8_t *)this + 700) = 0;  // 写字段 this+700（bSnapshot700）
  *((uint8_t *)this + 701) = 1;  // 写字段 this+701（bSnapshot701）
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v8 + 372))(this, 100);  // 虚函数调用 槽+372：目标点写入
  fld_e87 = *(uint32_t *)*(this + 87);  // this+348〔pParamTbl348〕
  *(this + 170) = fld_e87;  // 写字段 this+170 ← fld_e87
  *(this + 171) = fld_e87;  // 写字段 this+171 ← fld_e87
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, int))(*this + 472))(this, 2, 0, 1, 1);  // 虚调用 vt+472（this 虚表槽）
  *(this + 247) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  *(this + 248) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  *(this + 249) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  pMem = operator new(0x12Cu);  // 堆分配
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
  {
    v11 = sub_428F30(pMem, (int)"PassiveObject/MapObject/Trap/Particle/SpinerMovePath.ptl", 0);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
    v35 = (int (/*thiscall*/ ***)(uint32_t, int))v11;
  }
  else
  {
    v35 = nullptr;
    v11 = nullptr;
  }
  v12 = (char *)sub_445D00(156);  // sub_445D00 —— v71 = sub_445D00 · CRT 一次性池初始化
  if ( v12 != nullptr )  // 若 v12 有效（非空）
  {
    pObj2 = sub_445B90(v12);  // sub_445B90 —— v72 = sub_445B90 · CNRDParticle 构造
    pObj = pObj2;
  }
  else
  {
    pObj = nullptr;
  }
  v13 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *))(*v11 + 28))(v11);  // 虚调用 vt+28（v11 虚表槽）
  qmemcpy((void *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 16))(pObj2), v13, 0x62u);  // 虚调用 vt+16（pObj2 虚表槽）
  v14 = (uint32_t *)(*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 16))(pObj);  // 虚调用 vt+16（pObj 虚表槽）
  *v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 16))(pObj) + 4) = v15;  // 虚调用 vt+16（pObj 虚表槽）
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
  *(uint32_t *)((*(int (/*thiscall*/ **)(char *))(*(uint32_t *)pObj + 16))(pObj) + 8) = v16;  // 虚调用 vt+16（pObj 虚表槽）
  (*(void (/*thiscall*/ **)(uint32_t *, char *))(*this + 60))(this, pObj);  // 虚调用 vt+60（this）对象销毁/释放
  sub_4A0B60(v33);  // sub_4A0B60 —— 控制对象换绑
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj + 4))(pObj, 0);  // 虚调用 vt+4（pObj）对象赋值/迁移
  pMem2 = operator new(0x12Cu);  // 堆分配
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v18 = sub_428F30(pMem2, (int)"PassiveObject/MapObject/Trap/Particle/SpinerBubble.ptl", 0);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
  else
    v18 = nullptr;
  *(this + 245) = v18;  // 写字段 this+245 ← v18
  if ( v18 != nullptr )  // 若 v18 有效（非空）
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) != 0 )  // 虚调用 vt+684（this 虚表槽）
    {
      pObj3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);  // 虚调用 vt+684（this 虚表槽）
      Block = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 192))(pObj3) * 0.5;  // 虚调用 vt+192（pObj3）取尺寸/包围盒
      v20 = (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + Block;  // 虚调用 vt+128（this）目标坐标y上界
    }
    else
    {
      v20 = (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    }
    fld_e245 = *(uint32_t *)*(this + 245);  // this+980〔uCfgF980(推断)〕
    v22 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)v20);  // 虚调用 vt+124（this）目标坐标y下界
    v23 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v22);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e245 + 40))(*(this + 245), v23);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 245) + 12))(*(this + 245), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
  }
  pMem3 = operator new(0x12Cu);  // 堆分配
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v25 = sub_428F30(pMem3, (int)"PassiveObject/MapObject/BreakableObject/Particle/SeaGrassBubble.ptl", 0);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
  else
    v25 = nullptr;
  *(this + 246) = v25;  // 写字段 this+246 ← v25
  if ( v25 != nullptr )  // 若 v25 有效（非空）
  {
    v26 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);  // 虚调用 vt+684（this 虚表槽）
    v27 = *this;
    if ( v26 != 0 )
    {
      pObj4 = (*(int (/*thiscall*/ **)(uint32_t *))(v27 + 684))(this);  // 虚函数调用 槽+684：属性块基址（this+6132，HP 读处）
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 192))(pObj4);  // 虚调用 vt+192（pObj4）取尺寸/包围盒
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(v27 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    }
    fld_e246 = *(uint32_t *)*(this + 246);  // this+984〔aStateBlk984(推断)〕
    v30 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, 0);  // 虚调用 vt+124（this）目标坐标y下界
    v31 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v30);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e246 + 40))(*(this + 246), v31);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 246) + 12))(*(this + 246), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
  }
  return (**v35)(v35, 1);  // 调 v35 的虚函数（vt+0）
}


// ------------------------------------------------------------
// 0x622AE0 CNSpiner__vmt14C —— 旋涡主 tick（状态机）vmt14C
//    状态 2 每 500ms：sub_6224F0 无目标则按血量比 ≤0.3 直接抛射，有目标时 sub_622560 并查当前玩家(dword_8F7A24 三支)以 sub_4600B0 发 SpinerBubble；
//    状态 4 超 5000ms 引爆(sub_622020)；状态 3 于目标倒地时虚 560(2)；750ms 周期经虚 352 重设；状态 4 且 +148 空时发 SeaGrassBubble。
// ------------------------------------------------------------
void /*thiscall*/ sub_622AE0(int *this)  // 【CNSpiner__vmt14C】
{
  int v2; // edi
  int v3; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  uint32_t *pHostComp; // edi
  int *v8; // eax
  int v9; // edx
  int v10; // eax
  int *fld_e246; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  void *fld_e29; // ecx
  void *nSnapshot684; // eax
  int pThis_9; // eax
  int v18; // edx
  int *v19; // eax
  int v20; // ecx
  int v21; // eax
  int *fld_e245; // eax
  int v23; // edi
  int v24; // eax
  int v25; // eax
  void *fld_e292; // ecx
  void *v27[4]; // [esp+8h] [ebp-34h] BYREF
  void *v28[5]; // [esp+18h] [ebp-24h] BYREF
  int nSnapshot680; // [esp+2Ch] [ebp-10h]  | +0x02A8 → 表现/名字快照[0]（CNSpiner；va=004E1FE0）
  int v30; // [esp+38h] [ebp-4h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);  // 虚调用 vt+436（this）取值
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) < v2 )  // 虚调用 vt+128（this）目标坐标y上界
  {
    v3 = *this;
    v4 = (*(int (/*thiscall*/ **)(int *))(*this + 436))(this);  // 虚调用 vt+436（this）取值
    v5 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v4);  // 虚调用 vt+124（this）目标坐标y下界
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(int *, int))(v3 + 112))(this, v6);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    pHostComp = (uint32_t *)*(this + 28);  // this+28 【推断】逐帧驱动对象
    if ( *pHostComp != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pHostComp + 308))(*pHostComp) != 0 && pHostComp[9] != 0 )  // 虚调用 vt+308（fld_e28）是否本地玩家
    {
      pHostComp[9] = 0;
      *((uint8_t *)pHostComp + 196) = 1;  // 写字段 fld_e28[196]（宽1字节）
      sub_494F60(2, -1);  // sub_494F60 —— 属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
    }
  }
  if ( *(this + 240) == 2 && *(this + 249) + 500 < (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
  {
    *(this + 249) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
    if ( (uint8_t)sub_6224F0(this) == 0 )  // sub_6224F0 —— 旋涡范围探测
    {
LABEL_20:
      nSnapshot684 = (void *)*(this + 171);  // this+684〔nSnapshot684〕
      nSnapshot680 = *(this + 170);  // 读字段 fld_e170 = this+170
      v28[4] = nSnapshot684;
      if ( (double)nSnapshot680 / (double)(int)nSnapshot684 <= 0.30000001 )
      {
        sub_622560(this);  // sub_622560 —— 旋涡随机抛射
        *(this + 248) = *(this + 249);  // 写字段 this+248（bParamSlotA） ← *(this + 249)
      }
      goto LABEL_22;
    }
    sub_622560(this);  // sub_622560 —— 旋涡随机抛射
    *(this + 248) = *(this + 249);  // 写字段 this+248（bParamSlotA） ← *(this + 249)
    v8 = nullptr;
    switch ( *(uint32_t *)(dword_8F7A24 + 12) )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    {
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        v9 = *(uint32_t *)(dword_8F7A24 + 28);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        v9 = *(uint32_t *)(dword_8F7A24 + 32);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
        v9 = *(uint32_t *)(dword_8F7A24 + 40);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      default:
LABEL_16:
        v10 = *v8;
        if ( v10 >= 15 && v10 <= 16 )  // 若 v10 >= 15 与/或 v10 <= 16
        {
          fld_e246 = (int *)*(this + 246);  // this+984〔aStateBlk984(推断)〕
          if ( fld_e246 != nullptr )  // 若 fld_e246 有效（非空）
          {
            v12 = *fld_e246;
            v13 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);  // 虚调用 vt+124（this）目标坐标y下界
            v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13);  // 虚调用 vt+120（this）转发(对象+缓冲)
            (*(void (/*thiscall*/ **)(uint32_t, int))(v12 + 40))(*(this + 246), v14);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 246) + 12))(*(this + 246), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
            (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 246) + 92))(*(this + 246), v28);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
            fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
            v30 = 0;
            sub_4600B0(fld_e29, 2, 0, (int)v28);  // sub_4600B0 —— 演播层注册(槽号)
            v30 = -1;
            sub_5E5260(v28);  // 调 动画子对象清理临时缓冲
          }
        }
        goto LABEL_20;
    }
    v8 = *(int **)(*(uint32_t *)(v9 + 16) + 108);
    goto LABEL_16;
  }
LABEL_22:
  if ( *(this + 240) == 4 && *(this + 248) + 5000 < (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
    sub_622020(this);  // sub_622020 —— 旋涡引爆（范围伤害）
  if ( *(this + 240) == 3  // this+240 动画同步参数 B
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) == 1  // 虚调用 vt+200（this）取值比较
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    sub_622560(this);  // sub_622560 —— 旋涡随机抛射
    *(this + 248) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  }
  if ( *(this + 247) + 750 < (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
  {
    pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    v18 = *this;
    *(this + 247) = pThis_9;  // 写字段 this+247 ← pThis_9
    (*(void (/*thiscall*/ **)(int *))(v18 + 352))(this);  // 虚函数调用 槽+352：命中列表双链表清空
  }
  if ( *(this + 240) == 4 && *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 148) == 0 )  // 虚调用 vt+200（this）取值比较
  {
    v19 = nullptr;
    switch ( *(uint32_t *)(dword_8F7A24 + 12) )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
    {
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        v20 = *(uint32_t *)(dword_8F7A24 + 28);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        v20 = *(uint32_t *)(dword_8F7A24 + 32);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
        v20 = *(uint32_t *)(dword_8F7A24 + 40);  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        break;
      default:
LABEL_40:
        v21 = *v19;
        if ( v21 >= 15 && v21 <= 16 )  // 若 v21 >= 15 与/或 v21 <= 16
        {
          fld_e245 = (int *)*(this + 245);  // this+980〔uCfgF980(推断)〕
          if ( fld_e245 != nullptr )  // 若 fld_e245 有效（非空）
          {
            v23 = *fld_e245;
            v24 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 124))(this, 0);  // 虚调用 vt+124（this）目标坐标y下界
            v25 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v24);  // 虚调用 vt+120（this）转发(对象+缓冲)
            (*(void (/*thiscall*/ **)(uint32_t, int))(v23 + 40))(*(this + 245), v25);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
            (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 245) + 12))(*(this + 245), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
            (*(void (/*thiscall*/ **)(uint32_t, void **))(*(uint32_t *)*(this + 245) + 92))(*(this + 245), v27);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
            fld_e292 = (void *)*(this + 29);  // this+116〔会话上下文〕
            v30 = 1;
            sub_4600B0(fld_e292, 2, 0, (int)v27);  // sub_4600B0 —— 演播层注册(槽号)
            sub_5E5260(v27);  // 调 动画子对象清理临时缓冲
          }
        }
        return;
    }
    v19 = *(int **)(*(uint32_t *)(v20 + 16) + 108);
    goto LABEL_40;
  }
}


// ------------------------------------------------------------
// 0x622E10 sub_622E10 —— 鱼巢刷鱼
//    记录 GetTickCount(+1116) 后播种，rand()%4 从表 220/220/220/221 选鱼种，经虚 250 在巢坐标生成（己方 id 由虚 80 链取得存 +1120），计数 +1124 递增。
// ------------------------------------------------------------
int /*thiscall*/ sub_622E10(int *this)  // sub_622E10 —— 鱼巢刷鱼
{
  int result; // eax
  int v3; // edx
  int pThis_84; // ebx
  uint32_t *v5; // eax
  int v6; // eax
  int v7; // edx
  int pThis_1; // edi
  int v9; // eax
  int v10; // edx
  int nRand; // eax
  int v12; // [esp-2Ch] [ebp-48h]
  int fld_e280; // [esp-1Ch] [ebp-38h]
  int v14[4]; // [esp+4h] [ebp-18h]
  int v15; // [esp+14h] [ebp-8h]
  int v16; // [esp+18h] [ebp-4h]

  *(this + 279) = GetTickCount();  // 写字段 this+279 ← GetTickCount()
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();  // sub_432FA0 —— srand 播种
    v3 = *this;
    v14[0] = 220;
    v14[1] = 220;
    v14[2] = 220;
    v14[3] = 221;
    pThis_84 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(v3 + 80))(this) + 132) + 108) + 112);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 虚调用 vt+80（this）读 4 字节
    *(this + 280) = sub_460230(v5);  // sub_460230 —— 图标槽随机 id 分配（线性探测）
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
    v7 = *this;
    v15 = v6;
    pThis_1 = (*(int (/*thiscall*/ **)(int *))(v7 + 124))(this) + 1;  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    v10 = *this;
    fld_e280 = *(this + 280);  // 读字段 fld_e280 = this+280（pMapEntryVecEnd）
    v16 = v9;
    v12 = (*(int (/*thiscall*/ **)(int *))(v10 + 152))(this);  // 虚函数调用 槽+152：效果通道 3
    nRand = rand() % 4;  // 调 取伪随机数
    IRDCollisionObject__vmt250(
      this,
      pThis_84,
      (int)this,
      v14[nRand],
      100,
      pThis_84,
      v15,
      pThis_1,
      v16,
      v12,
      0,
      nullptr,
      0,
      fld_e280,
      0,
      0,
      0,
      0);
    result = *(this + 281) + 1;  // this+1124〔nListCnt1124(推断)〕
    *(this + 281) = result;  // 写字段 this+281 ← result
  }
  return result;
}



// ============================================================
// 【分区 5】海底生态：鱼巢/爆炸油/幻觉花（0x622F00-0x6239E0）
// 物件: CNSpaceFishLair（太空鱼巢）/ CNExplosiveOil+CNOlreksExplosiveOil（爆炸油桶）/
//       CNHallucinationFlower（幻觉花）；油桶受击引爆链见 vmt2C4/vmt288
// ============================================================

// ------------------------------------------------------------
// 0x622F00 CNSpaceFishLair__vmt14C —— 鱼巢 tick vmt14C
//    基类后：存活鱼数(<2)且累计 <5 时，距上次 +1116 满 7500ms 才调 sub_622E10 刷鱼。
// ------------------------------------------------------------
char /*thiscall*/ CNSpaceFishLair__vmt14C(int *this)  // 函数定义: 鱼巢 tick vmt14C
{
  unsigned int TickCount; // eax
  int fld_e276; // ecx

  LOBYTE(TickCount) = CNMapObject__vmt14C(this);  // 调 取 16 位值低 8 位
  fld_e276 = *(this + 276);  // 读字段 fld_e276 = this+276（pMapEntry）
  if ( (fld_e276 == 0 || (TickCount = (*(this + 277) - fld_e276) >> 2) < 2) && *(this + 281) < 5 )  // this+1108〔pAttach1108(推断)〕等 2 字段
  {
    TickCount = GetTickCount();  // 调 取系统运行毫秒数
    if ( *(this + 279) + 7500 < TickCount )
      LOBYTE(TickCount) = sub_622E10(this);  // sub_622E10 —— 鱼巢刷鱼
  }
  return TickCount;
}



// ------------------------------------------------------------
// 0x622F50 CNSpaceFishLair__vmt2F4 —— 鱼巢复位 vmt2F4
//    释放 +1104 鱼群数组，+1120 置 0xFFFF 哨兵、计数清零、下次刷鱼时刻=GetTickCount+7500；虚 93(100) 与 +676=1 收尾。
// ------------------------------------------------------------
int /*thiscall*/ CNSpaceFishLair__vmt2F4(void **this, int nArg2)  // 函数定义: 鱼巢复位 vmt2F4
{
  int result; // eax

  if ( *(this + 276) != nullptr )  // this+276 地图条目指针
    j__free(*(this + 276));  // 释放堆块
  *(this + 276) = nullptr;  // 写字段 this+276（pMapEntry） ← nullptr
  *(this + 277) = nullptr;  // 写字段 this+277 ← nullptr
  *(this + 278) = nullptr;  // 写字段 this+278 ← nullptr
  *(this + 280) = (void *)0xFFFF;  // 写字段 this+280（pMapEntryVecEnd） ← (void *)0xFFFF
  *(this + 281) = nullptr;  // 写字段 this+281 ← nullptr
  *(this + 279) = (void *)(GetTickCount() + 7500);  // 写字段 this+279 ← (void *)(GetTickCount() + 7500)
  result = (*((int (/*thiscall*/ **)(void **, int))*this + 93))(this, 100);  // 虚调用 vt+93（this 虚表槽）
  *(this + 169) = (void *)1;  // 写字段 this+169 ← (void *)1
  return result;
}



// ------------------------------------------------------------
// 0x622FC0 CNSpaceFishLair__vmt12C —— 鱼巢卸载 vmt12C
//    来客类别(虚 40,529)命中则从 +1104 鱼群数组按 memcpy 前移摘除；随后统一走基类 CNMapObject__vmt12C。
// ------------------------------------------------------------
char /*thiscall*/ CNSpaceFishLair__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 鱼巢卸载 vmt12C
{
  int fld_e276; // edx
  unsigned int i; // ecx

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0 )  // 虚调用 vt+40（nArg2）条件查询(273等)
  {
    fld_e276 = *(this + 276);  // 读字段 fld_e276 = this+276（pMapEntry）
    for ( i = 0; fld_e276 != 0 && i < (*(this + 277) - fld_e276) >> 2; ++i )  // this+1108〔pAttach1108(推断)〕
    {
      if ( *(uint32_t *)(*(this + 276) + 4 * i) == nArg2 )  // this+276 地图条目指针
      {
        memcpy_0(
          (void *)(*(this + 276) + 4 * i),  // this+276 地图条目指针
          (const void *)(*(this + 276) + 4 * i + 4),  // this+276 地图条目指针
          4 * ((int)(*(this + 277) - (*(this + 276) + 4 * i + 4)) >> 2));  // this+1108〔pAttach1108(推断)〕等 2 字段
        *(this + 277) -= 4;  // this+1108〔pAttach1108(推断)〕
        return CNMapObject__vmt12C(this, nArg2);  // 返回 调 CNMapObject__vmt12C
      }
    }
  }
  return CNMapObject__vmt12C(this, nArg2);  // 返回 调 CNMapObject__vmt12C
}



// ------------------------------------------------------------
// 0x623050 sub_623050 —— 4 字节元素 vector 追加
//    容量足则就地写入 *uArg2 并推进尾指针，否则调 sub_5CC5A0 重分配插入（this+4/+8/+12 三段布局）。
// ------------------------------------------------------------
int /*thiscall*/ sub_623050(int this, uint32_t *uArg2)  // sub_623050 —— 4 字节元素 vector 追加
{
  int fld_4; // esi
  unsigned int fld_8; // edx
  uint32_t *fld_82; // eax
  int result; // eax

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8 物品 id
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) >> 2 )  // this+12 物品类型号
    return sub_5CC5A0(*(void **)(this + 8), 1, (int)uArg2);  // sub_5CC5A0 —— 向量插入重分配
  fld_82 = *(uint32_t **)(this + 8);  // this+8 物品 id
  *fld_82 = *uArg2;
  result = (int)(fld_82 + 1);
  *(uint32_t *)(this + 8) = result;  // 写字段 this+8（nSkillRec8） ← result
  return result;
}



// ------------------------------------------------------------
// 0x6230A0 CNSpaceFishLair__vmt128 —— 鱼巢归巢收编 vmt128
//    来客为 529 类且其归属(虚 52)等于 +1120 时，sub_4E7E40 清理后经 sub_623050 追加进 +1100 表。
// ------------------------------------------------------------
int /*thiscall*/ CNSpaceFishLair__vmt128(uint32_t *this, int nArg2)  // 函数定义: 鱼巢归巢收编 vmt128
{
  int pObj; // esi
  int result; // eax

  pObj = nArg2;
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529);  // 虚调用 vt+40（nArg2）条件查询(273等)
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 虚调用 vt+52（pObj）归属坐标y
    if ( result == *(this + 280) )  // this+280 地图条目数组 end
    {
      sub_4E7E40(pObj);  // sub_4E7E40 —— this+652 vector push_back（容量不足 → ·sub_428220）
      nArg2 = pObj;
      return sub_623050((int)(this + 275), &nArg2);  // sub_623050 —— 4 字节元素 vector 追加
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6230F0 CNExplosiveOil__vmt12C —— 油桶卸载回调 vmt12C
//    基类后若卸载对象恰为 +1004 所存引用则清零（投放者/目标引用解除）。
// ------------------------------------------------------------
void /*thiscall*/ CNExplosiveOil__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 油桶卸载回调 vmt12C
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( nArg2 == *(this + 251) )  // this+1004〔nOilValD1004〕
    *(this + 251) = 0;  // 写字段 this+251 ← 0
}



// ------------------------------------------------------------
// 0x623120 CNExplosiveOil__vmt200 —— 油桶爆炸抛洒 vmt200
//    存活且未炸过(+972=0)时先重置 +1004 目标(虚 680/372)，srand 后在 +980 基数与 +984 上限内取随机抛洒次数，
//    每次以虚 580 生成 40002/40003/40006 三型碎片（配 +988/+992/+996 帧源、横向 ±40 纵向 ±30 随机偏移、参数 4），末以虚 604/312 停摆并置炸过标志。
// ------------------------------------------------------------
int /*thiscall*/ CNExplosiveOil__vmt200(int this, int nArg2, float *pArg3, char pszArg4)  // 函数定义: 油桶爆炸抛洒 vmt200
{
  int v5; // edi
  int nOilValD1004; // eax  | +0x03EC → 数值槽 D（CNExplosiveOil；va=00623120）
  int v7; // ebx
  int fld_3EC2; // eax  | +0x03EC → 数值槽 D（CNExplosiveOil；va=00623120）
  int nOilValA988; // ecx  | +0x03DC → 数值槽 A（623120：fld_3DC = *(+988)）【推断】（证据 va=00623120）（CNExplosiveOil；va=00623120）
  int nOilValB992; // edx  | +0x03E0 → 数值槽 B（623120：fld_3E0 = *(+992)）【推断】（证据 va=00623120）（CNExplosiveOil；va=00623120）
  int nOilValC996; // eax  | +0x03E4 → 数值槽 C（623120：fld_3E4 = *(+996)）【推断】（证据 va=00623120）（CNExplosiveOil；va=00623120）
  int nRand; // edx
  int nRand2; // eax
  int v14; // ebx
  int v15; // edi
  int nRand4; // eax
  int nRand3; // [esp-1Ch] [ebp-3Ch]
  uint32_t v19[3]; // [esp+8h] [ebp-18h]
  uint32_t v20[3]; // [esp+14h] [ebp-Ch]
  int v21; // [esp+2Ch] [ebp+Ch]
  int i; // [esp+30h] [ebp+10h]

  v5 = CNRDPassiveObject__vmt200((int *)this, nArg2, pArg3, pszArg4);  // v5 = 调 CNRDPassiveObject__vmt200
  v21 = v5;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 && *(uint8_t *)(this + 972) == 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    nOilValD1004 = *(uint32_t *)(this + 1004);  // 读字段 fld_3EC = this+1004（nOilValD1004）
    if ( nOilValD1004 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 680))(this, nOilValD1004);  // 虚调用 vt+680（this）目标碰撞体绑定
      v7 = *(uint32_t *)this;
      fld_3EC2 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 1004) + 376))(*(uint32_t *)(this + 1004));  // this+1004 数值槽 D
      (*(void (/*thiscall*/ **)(int, int))(v7 + 372))(this, fld_3EC2);  // 虚函数调用 槽+372：目标点写入
    }
    sub_432FA0();  // sub_432FA0 —— srand 播种
    nOilValA988 = *(uint32_t *)(this + 988);  // 读字段 fld_3DC = this+988（uCfgA988）
    nOilValB992 = *(uint32_t *)(this + 992);  // 读字段 fld_3E0 = this+992（uCfgB992）
    nOilValC996 = *(uint32_t *)(this + 996);  // 读字段 fld_3E4 = this+996（bCfgC996）
    v19[0] = 40002;
    v19[1] = 40003;
    v19[2] = 40006;
    v20[0] = nOilValA988;
    v20[1] = nOilValB992;
    v20[2] = nOilValC996;
    nRand = *(uint32_t *)(this + 980) + rand() % (*(uint32_t *)(this + 984) - 1);  // this+980 随机下限
    if ( nRand > 0 )
    {
      for ( i = nRand; i != 0; --i )  // 遍历计次循环（i != 0）
      {
        nRand2 = rand();  // 调 取伪随机数
        v14 = *(uint32_t *)this;
        v15 = nRand2 % 3;
        nRand3 = rand() % 60 - 30;  // 调 取伪随机数
        nRand4 = rand();  // 调 取伪随机数
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, int, int, uint32_t, int, uint32_t, uint32_t, uint32_t))(v14 + 580))(  // 虚函数调用 槽+580：位置化动作发布（会话 3 定案：位置化动作）
          this,
          v19[v15],
          v20[v15],
          0,
          0,
          nRand4 % 80 - 40,
          nRand3,
          0,
          4,
          0,
          0,
          0);
      }
      v5 = v21;
    }
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 604))(this, 0);  // 虚调用 vt+604（this）收招例程
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
  }
  *(uint8_t *)(this + 972) = 1;  // 写字段 this+972（uCfgD972） ← 1
  return v5;
}



// ------------------------------------------------------------
// 0x623270 CNExplosiveOil__vmt288 —— 油桶可用性查询 vmt288
//    目标件(虚 348)+20 处非空则返回 3（不可用）；否则输出 *uArg1=0 并返回 0。
// ------------------------------------------------------------
int /*stdcall*/ CNExplosiveOil__vmt288(uint32_t *uArg1, int nArg2)  // 函数定义: 油桶可用性查询 vmt288
{
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 20) != 0 )  // 虚调用 vt+348（nArg2）渲染数据块指针
    return 3;
  *uArg1 = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x6232A0 CNExplosiveOil__vmt14C —— 油桶 tick vmt14C
//    首次经虚 708 一次性初始化(+973 置位)；若 +976 件倒地位(+170)置起且自身未销毁(+264=0)则虚 312 停用。
// ------------------------------------------------------------
char /*thiscall*/ CNExplosiveOil__vmt14C(uint8_t *this)  // 函数定义: 油桶 tick vmt14C
{
  char result; // al

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 973) == 0 )  // this+973 落地一次性门
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 708))(this);  // 虚调用 vt+708（this 虚表槽）
    *(this + 973) = 1;  // 写字段 this+973（bLanded973） ← 1
  }
  result = *(uint8_t *)(*((uint32_t *)this + 244) + 170);  // this+244 爆炸目标引用
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = *(this + 264);  // 读字段 result = this+264（nAnimHandle）
    if ( result == 0 )
      return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
  }
  return result;
}



// ------------------------------------------------------------
// 0x6232F0 CNExplosiveOil__vmt148 —— 油桶渲染层回调 vmt148
//     +976 件存在时经 sub_4938F0 走播放驱动总入口，再以 sub_491D00(dword_79C0B0,...) 下发图层属性。
// ------------------------------------------------------------
int /*thiscall*/ CNExplosiveOil__vmt148(int *this, int nArg2, int nArg3, int nArg4, float fArg5)  // 函数定义: 油桶渲染层回调 vmt148
{
  int uCfgE976; // ecx
  int result; // eax

  uCfgE976 = *(this + 244);  // 读字段 fld_e244 = this+244（fSyncValue）
  if ( uCfgE976 != 0 )
  {
    sub_4938F0(uCfgE976);  // sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    return sub_491D00(dword_79C0B0, nArg3, nArg4, fArg5);  // sub_491D00 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  }
  return result;
}



// ------------------------------------------------------------
// 0x623330 sub_623330 —— 油桶参数装载
//    清 +1004/+972/+973/+976 并置 +1000=-1，再从 +348 参数表拷出 5 个整型到 +980..+996（抛洒次数区间与三型碎片帧号）。
// ------------------------------------------------------------
int /*thiscall*/ sub_623330(int this)  // sub_623330 —— 油桶参数装载
{
  uint32_t *fld_15C; // eax
  int result; // eax

  *(uint32_t *)(this + 1004) = 0;  // 写字段 this+1004（nOilValD1004） ← 0
  *(uint8_t *)(this + 972) = 0;  // 写字段 this+972（uCfgD972） ← 0
  *(uint8_t *)(this + 973) = 0;  // 写字段 this+973（bLanded973） ← 0
  *(uint32_t *)(this + 976) = 0;  // 写字段 this+976（uCfgE976） ← 0
  fld_15C = *(uint32_t **)(this + 348);  // this+348 参数表指针
  *(uint32_t *)(this + 1000) = -1;  // 写字段 this+1000（bGrassFilter1000） ← -1
  *(uint32_t *)(this + 980) = *fld_15C;  // 写字段 this+980（uCfgF980） ← *fld_15C
  *(uint32_t *)(this + 984) = fld_15C[1];  // 写字段 this+984（aStateBlk984） ← fld_15C[1]
  *(uint32_t *)(this + 988) = fld_15C[2];  // 写字段 this+988（uCfgA988） ← fld_15C[2]
  *(uint32_t *)(this + 992) = fld_15C[3];  // 写字段 this+992（uCfgB992） ← fld_15C[3]
  result = fld_15C[4];
  *(uint32_t *)(this + 996) = result;  // 写字段 this+996（bCfgC996） ← result
  return result;
}



// ------------------------------------------------------------
// 0x623390 CNExplosiveOil__vmt2C4 —— 油桶构造 vmt2C4
//    虚 372(201)、680(0) 清目标后 new(228)：以自身名（SSO +364 或 +364 指针）与 +712 句柄(sub_41ACF0)经 sub_431920 建动画件存 +976。
// ------------------------------------------------------------
int /*thiscall*/ CNExplosiveOil__vmt2C4(char *this)  // 函数定义: 油桶构造 vmt2C4
{
  int v2; // ebx
  const char *pThis_16C; // edi
  const char *pThis_B2; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 372))(this, 201);  // 虚调用 vt+372（this）数值写入
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 680))(this, 0);  // 虚调用 vt+680（this）目标碰撞体绑定
  v2 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
  if ( v2 != 0 )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
      pThis_16C = this + 364;  // this+364 动画件名缓冲 SSO 内联首址
    else
      pThis_16C = *((const char **)this + 91);
    pThis_B2 = (const char *)sub_41ACF0(*((uint32_t *)this + 178));  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    result = sub_431920(v2, pThis_16C, pThis_B2, 1);  // sub_431920 —— 动画件构造（文件名版）
  }
  else
  {
    result = 0;
  }
  *((uint32_t *)this + 244) = result;  // 写字段 this+244（fSyncValue）
  return result;
}



// ------------------------------------------------------------
// 0x623430 CNOlreksExplosiveOil__vmt2C4 —— CMOlreks 油桶构造 vmt2C4
//    与 sub_623390 同构（差异：先记 +1004=拥有者(虚 684)与 +1000=其虚 376 结果）。
// ------------------------------------------------------------
int /*thiscall*/ CNOlreksExplosiveOil__vmt2C4(char *this)  // 函数定义: CMOlreks 油桶构造 vmt2C4
{
  int pThis_2AC; // eax
  int v3; // edx
  int pObj; // eax
  int v5; // edi
  const char *pThis_16C; // ebx
  const char *pThis_B2; // eax
  int result; // eax

  pThis_2AC = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 684))(this);  // 虚调用 vt+684（this 虚表槽）
  v3 = *(uint32_t *)this;
  *((uint32_t *)this + 251) = pThis_2AC;  // 写字段 this[251]（宽4字节）
  pObj = (*(int (/*thiscall*/ **)(char *))(v3 + 684))(this);  // 虚函数调用 槽+684：属性块基址（this+6132，HP 读处）
  *((uint32_t *)this + 250) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 虚调用 vt+376（pObj 虚表槽）
  (*(void (/*thiscall*/ **)(char *, int))(*(uint32_t *)this + 372))(this, 201);  // 虚调用 vt+372（this）数值写入
  (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)this + 680))(this, 0);  // 虚调用 vt+680（this）目标碰撞体绑定
  v5 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
  if ( v5 != 0 )
  {
    if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
      pThis_16C = this + 364;  // this+364 动画件名缓冲 SSO 内联首址
    else
      pThis_16C = *((const char **)this + 91);
    pThis_B2 = (const char *)sub_41ACF0(*((uint32_t *)this + 178));  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    result = sub_431920(v5, pThis_16C, pThis_B2, 1);  // sub_431920 —— 动画件构造（文件名版）
  }
  else
  {
    result = 0;
  }
  *((uint32_t *)this + 244) = result;  // 写字段 this+244（fSyncValue）
  return result;
}



// ------------------------------------------------------------
// 0x623500 sub_623500 —— 油桶状态清零
//     +972/+976/+980/+984 四项归零（爆炸后/复位时用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_623500(int this)  // sub_623500 —— 油桶状态清零
{
  *(uint32_t *)(this + 984) = 0;  // 写字段 this+984（aStateBlk984） ← 0
  *(uint8_t *)(this + 976) = 0;  // 写字段 this+976（uCfgE976） ← 0
  *(uint32_t *)(this + 972) = 0;  // 写字段 this+972（uCfgD972） ← 0
  *(uint32_t *)(this + 980) = 0;  // 写字段 this+980（uCfgF980） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x6239E0 CNHallucinationFlower__vmt14C —— 幻觉花主 tick vmt14C
//    首帧按 +348 表首项决定虚 148 显隐，并按有无主件走虚 472(4/2)；状态 2 走 sub_623730，
//    状态 3 于目标 +148 为 5 且未触发过(+976)时经虚 580 生成 48021 号(10 个、参数 70)并置 +976，否则目标 +170 置起时虚 560(2)；状态 4 且主件 +170 置起时虚 472(2)。
// ------------------------------------------------------------
char /*usercall*/ CNHallucinationFlower__vmt14C@<al>(int pArg1@<ecx>, int nArg2@<edi>)  // 实现：幻觉花主 tick vmt14C
{
  int v2; // edi
  int v3; // eax
  int v5; // eax

  CNRDPassiveObject__vmt14C(pArg1);
  if ( *(uint8_t *)(pArg1 + 988) == 0 )  // pArg1+988〔uCfgA988(推断)〕
  {
    if ( **(uint32_t **)(pArg1 + 348) != 0 )  // pArg1+348〔pParamTbl348(推断)〕
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 148))(pArg1, 1);  // 虚调用 vt+148（pArg1）位置/朝向写入
    else
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 148))(pArg1, 0);  // 虚调用 vt+148（pArg1）位置/朝向写入
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 684))(pArg1) != 0 )  // 虚调用 vt+684（pArg1 虚表槽）
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)pArg1 + 472))(pArg1, 4, 0, 1, 1);  // 虚调用 vt+472（pArg1 虚表槽）
    else
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)pArg1 + 472))(pArg1, 2, 0, 1, 1);  // 虚调用 vt+472（pArg1 虚表槽）
    *(uint8_t *)(pArg1 + 988) = 1;  // 写字段 pArg1+988（uCfgA988） ← 1
  }
  if ( *(uint32_t *)(pArg1 + 960) == 2 )  // pArg1+960〔nBigStateMirror960(推断)〕
  {
    LOBYTE(v5) = sub_623730(pArg1);  // 调 取 16 位值低 8 位
  }
  else if ( *(uint32_t *)(pArg1 + 960) == 3 )  // pArg1+960〔nBigStateMirror960(推断)〕
  {
    v5 = *(uint32_t *)(pArg1 + 984);  // 读字段 v5 = pArg1+984（aStateBlk984）
    if ( v5 != 0 )
    {
      LOBYTE(v5) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1);  // 虚调用 vt+308（pArg1）是否本地玩家
      if ( (uint8_t)v5 != 0 )
      {
        if ( *(uint8_t *)(pArg1 + 976) != 0 || *(uint32_t *)(*(uint32_t *)(pArg1 + 984) + 148) != 5 )  // pArg1+984〔aStateBlk984(推断)〕
        {
          LOBYTE(v5) = *(uint8_t *)(*(uint32_t *)(pArg1 + 984) + 170);  // 调 取 16 位值低 8 位
          if ( (uint8_t)v5 != 0 )
            LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 2, 0, 0, 0);  // 虚调用 vt+560（pArg1 虚表槽）
        }
        else
        {
          *(uint8_t *)(pArg1 + 976) = 1;  // 写字段 pArg1+976（uCfgE976） ← 1
          v2 = *(uint32_t *)pArg1;
          v3 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pArg1 + 192))(pArg1, 4, 0, 0, 0, nArg2);  // 虚调用 vt+192（pArg1）取尺寸/包围盒
          LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t, int, int, int))(v2 + 580))(  // 虚函数调用 槽+580：位置化动作发布（会话 3 定案：位置化动作）
                         pArg1,
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
    v5 = *(uint32_t *)(pArg1 + 960) - 4;  // pArg1+960〔nBigStateMirror960(推断)〕
    if ( *(uint32_t *)(pArg1 + 960) == 4 )  // pArg1+960〔nBigStateMirror960(推断)〕
    {
      v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 200))(pArg1);  // 虚调用 vt+200（pArg1）取值比较
      if ( *(uint8_t *)(v5 + 170) != 0 )
        LOBYTE(v5) = (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)pArg1 + 472))(pArg1, 2, 0, 1, 1);  // 虚调用 vt+472（pArg1 虚表槽）
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
// 0x623AA0 CNSwamp__vmt2F0 —— 沼泽踏板判定 vmt2F0
//    类别(虚 40,17)命中、+128 非负且 +436 为 0 时成立（【推断】贴地且无高度偏移才可站上沼面）。
// ------------------------------------------------------------
bool /*stdcall*/ CNSwamp__vmt2F0(int nArg1)  // 函数定义: 沼泽踏板判定 vmt2F0
{
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 40))(nArg1, 17) != 0  // 虚调用 vt+40（nArg1）条件查询(273等)
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 128))(nArg1) >= 0  // 虚调用 vt+128（nArg1）目标坐标y上界
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 436))(nArg1) == 0;  // 虚调用 vt+436（nArg1）取值
}



// ------------------------------------------------------------
// 0x623AE0 sub_623AE0 —— 沼泽走行阈值装载
//    置虚 372(100)，清 +1121/+1122，并从 .equ 表经虚 384 取 7/8 项写入 +1136/+1140（走行播放与伤害计时阈值）。
// ------------------------------------------------------------
int /*thiscall*/ sub_623AE0(uint8_t *this, int nArg2, int nArg3)  // sub_623AE0 —— 沼泽走行阈值装载
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
  *(this + 1121) = 0;  // 写字段 this+1121（bCycleRstA） ← 0
  *(this + 1122) = 0;  // 写字段 this+1122（bCycleRstB） ← 0
  *((uint32_t *)this + 284) = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 7);  // 虚调用 vt+384（this 虚表槽）
  result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 8);  // 虚调用 vt+384（this 虚表槽）
  *((uint32_t *)this + 285) = result;  // 写字段 this+285（bField285）
  return result;
}



// ------------------------------------------------------------
// 0x623B30 CNSlowAndLowJump__vmt20 —— 限制件开关回调 vmt20
//    参数为 0（关闭）时对宿主(*(this+1))虚 216 停用 20881 号（沼地行走循环音）。
// ------------------------------------------------------------
char /*thiscall*/ CNSlowAndLowJump__vmt20(uint32_t **this, char pszArg2)  // 函数定义: 限制件开关回调 vmt20
{
  char result; // al

  result = pszArg2;
  if ( pszArg2 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t, int))(**(this + 1) + 216))(*(this + 1), 20881);  // 虚函数调用 槽+216：音效 TAG 查询
  return result;
}



// ------------------------------------------------------------
// 0x623B50 CNStarFishEggRequid__vmt2F4 —— 海星卵适配判定 vmt2F4
//    类别(虚 40,529)命中且经 __RTDynamicCast 确认是 CNStarFish 时成立。
// ------------------------------------------------------------
bool /*stdcall*/ CNStarFishEggRequid__vmt2F4(int nArg1)  // 函数定义: 海星卵适配判定 vmt2F4
{
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 40))(nArg1, 529) != 0  // 虚调用 vt+40（nArg1）条件查询(273等)
      && __RTDynamicCast(nArg1, 0, &IRDActiveObject `RTTI Type Descriptor', &CNStarFish `RTTI Type Descriptor', 0) != 0;  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
}



// ------------------------------------------------------------
// 0x623B90 CNMagmaSwamp__vmt2F4 —— 岩浆沼泽适配判定 vmt2F4
//    与 sub_623B50 同构（差异：RTTI 目标换成 CNBurningHela）。
// ------------------------------------------------------------
bool /*stdcall*/ CNMagmaSwamp__vmt2F4(int nArg1)  // 函数定义: 岩浆沼泽适配判定 vmt2F4
{
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 40))(nArg1, 529) != 0  // 虚调用 vt+40（nArg1）条件查询(273等)
      && __RTDynamicCast(nArg1, 0, &IRDActiveObject `RTTI Type Descriptor', &CNBurningHela `RTTI Type Descriptor', 0) != 0;  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
}



// ------------------------------------------------------------
// 0x623BD0 sub_623BD0 —— 12 字节元素反向搬移
//    STL 搬移辅助：从 uArg2 起逆向把 3 字一组拷到 uArg3 区（覆盖插入后段用）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_623BD0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // sub_623BD0 —— 12 字节元素反向搬移
{
  uint32_t *uArg22; // ecx
  uint32_t *result; // eax

  uArg22 = uArg2;
  for ( result = uArg3; uArg22 != uArg1; result[2] = uArg22[2] )
  {
    uArg22 -= 3;
    result -= 3;
    *result = *uArg22;
    result[1] = uArg22[1];
  }
  return result;
}



// ------------------------------------------------------------
// 0x623C10 sub_623C10 —— 12 字节元素区间填充
//    以 *pArg3 三字段填充 uArg1 起 uArg2 个元素，供插入与追加复用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_623C10(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // sub_623C10 —— 就地构造（拷贝构造 1 个）
{
  uint32_t *result; // eax
  uint32_t *uArg22; // ecx

  result = uArg2;
  if ( uArg2 != nullptr )  // 若 uArg2 有效（非空）
  {
    uArg22 = uArg2;
    result = uArg1;
    do
    {
      if ( result != nullptr )  // 若 result 有效（非空）
      {
        *result = *pArg3;
        result[1] = pArg3[1];
        result[2] = pArg3[2];
      }
      result += 3;
      uArg22 = (uint32_t *)((char *)uArg22 - 1);
    }
    while ( uArg22 != nullptr );  // 循环直到 uArg22 != nullptr
  }
  return result;
}



// ------------------------------------------------------------
// 0x623C50 CNSwamp__vmt2F4 —— 沼泽功效判定 vmt2F4
//    在 +332..+336 的效果号数组中查 21 号（【推断】湿身/减速类状态），命中返回真。
// ------------------------------------------------------------
bool /*stdcall*/ CNSwamp__vmt2F4(int pArg1)  // 函数定义: 沼泽功效判定 vmt2F4
{
  uint32_t *v1; // ecx
  uint32_t *v2; // eax
  bool v3; // zf

  v1 = *(uint32_t **)(pArg1 + 336);
  v2 = *(uint32_t **)(pArg1 + 332);  // pArg1+332〔bReservedConn(推断)〕
  v3 = v2 == v1;
  if ( v2 != v1 )
  {
    do
    {
      if ( *v2 == 21 )
        break;
      ++v2;  // 计数自增 v2
    }
    while ( v2 != v1 );  // 循环直到 v2 != v1
    v3 = v2 == v1;
  }
  return !v3;
}



// ------------------------------------------------------------
// 0x623C80 CNSlowAndLowJump__vmt4
//   【沼泽】R_WALK_SWAMP_LOOP —— 沼地行走循环音
// ------------------------------------------------------------
void /*thiscall*/ CNSlowAndLowJump__vmt4(int **this)  // 实现：(沼泽)R_WALK_SWAMP_LOOP —— 沼地行走循环音
{
  int *pHostObj; // edi
  int v3; // ebx
  int v4; // eax
  bool v5; // zf
  signed int fld_e12; // eax  | +0x0004 → 宿主对象指针（CNSlowAndLowJump；va=005F8080）
  int fld_e13; // edi  | +0x0004 → 宿主对象指针（CNSlowAndLowJump；va=005F8080）
  int fld_e14; // eax  | +0x0004 → 宿主对象指针（CNSlowAndLowJump；va=005F8080）
  uint32_t *pHostObj_; // ecx
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  int *pHostObj_2; // ecx
  int v14; // eax
  void *v15; // eax
  int v16; // [esp-Ch] [ebp-3Ch]
  void *v17[4]; // [esp+Ch] [ebp-24h] BYREF
  uint32_t *fld_e152; // [esp+1Ch] [ebp-14h]
  bool v19; // [esp+23h] [ebp-Dh]
  int v20; // [esp+2Ch] [ebp-4h]

  CNChangeStatus__vmt4((int)this);
  if ( *(this + 33) != (int *)-1  // this+33 【推断】职业数据脏位
    && (*(this + 9) == nullptr || (uint8_t)sub_4E4630(*(this + 1)) != 0)  // sub_4E4630 —— ★ 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(this + 1) + 308))(*(this + 1)) != 0  // 虚函数调用 槽+308
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, uint32_t))(**(this + 1) + 776))(*(this + 1), *(this + 33)) == 0  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
    && (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 128))(*(this + 1)) == 0 )  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
  {
    pHostObj = *(this + 1);  // 读字段 fld_e1 = this+1
    v3 = *pHostObj;
    v4 = ((int (/*thiscall*/ *)(int **, uint32_t))(*this)[16])(this, 0);
    (*(void (/*thiscall*/ **)(int *, uint32_t, int, uint32_t, uint32_t))(v3 + 760))(  // 虚函数调用 槽+760
      pHostObj,
      *(this + 33),  // this+33 【推断】职业数据脏位
      1120403456,  // 浮点常量 100.0f
      *(this + 34),  // this+136〔nCtx136(推断)〕
      *(uint32_t *)(v4 + 32));
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 184))(*(this + 1)) == 4  // 虚函数调用 槽+184：动画对象 z 倾斜转状态码
    && (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 188))(*(this + 1)) == 4 )  // 虚函数调用 槽+188：动画对象 z 倾斜转状态码
  {
    if ( *((uint8_t *)this + 124) != 0 )  // this+124 第 2 组·+858/+1292 增量
    {
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(this + 1) + 216))(*(this + 1), 20881);  // 虚函数调用 槽+216：音效 TAG 查询
      *((uint8_t *)this + 124) = 0;  // 写字段 this+124（pAuraAnim）
    }
  }
  else
  {
    if ( *((uint8_t *)this + 124) == 0 )  // this+124 第 2 组·+858/+1292 增量
    {
      (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(**(this + 1) + 212))(  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
        *(this + 1),  // this+4〔pHostObj〕
        "R_WALK_SWAMP_LOOP",  // 资源/动画 TAG R_WALK_SWAMP_LOOP
        20881,
        0,
        0);
      *((uint8_t *)this + 124) = 1;  // 写字段 this+124（pAuraAnim）
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 200))(*(this + 1)) == 0 )  // 虚函数调用 槽+200：取动画对象
      goto LABEL_21;
    fld_e12 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 200))(*(this + 1)) + 148) & 0x80000001;  // 虚函数调用 槽+200：取动画对象
    v5 = fld_e12 == 0;
    if ( fld_e12 < 0 )
      v5 = (((uint8_t)fld_e12 - 1) | 0xFFFFFFFE) == -1;
    if ( v5 )
    {
LABEL_21:
      *((uint8_t *)this + 125) = 0;  // 写字段 this+125（field_007D）
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 128))(*(this + 1)) == 0 && *((uint8_t *)this + 125) == 0 )  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    {
      fld_e13 = dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 924))(*(this + 1))];  // dword_8F8270 —— 虚调用 vt+924（取返回值）
      fld_e14 = (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 152))(*(this + 1));  // 虚函数调用 槽+152：效果通道 3
      pHostObj_ = *(this + 1);  // 读字段 fld_e15 = this+1
      v10 = *(uint32_t *)fld_e13;
      v19 = fld_e14 == 0;
      v11 = *pHostObj_;
      fld_e152 = pHostObj_;
      v16 = (*(int (**)(void))(v11 + 124))() + 1;  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*fld_e152 + 120))(fld_e152);  // 虚调用 vt+120（fld_e152）转发(对象+缓冲)
      (*(void (/*thiscall*/ **)(int, int))(v10 + 40))(fld_e13, v12);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e13 + 28))(fld_e13) + 84) = v19;  // 虚调用 vt+28（fld_e13 虚表槽）
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e13 + 12))(fld_e13, 0);  // 虚调用 vt+12（fld_e13 虚表槽）
      (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)fld_e13 + 92))(fld_e13, v17);  // 虚调用 vt+92（fld_e13）读剩余(返回长度)
      pHostObj_2 = *(this + 1);  // 读字段 fld_e16 = this+1
      v14 = *pHostObj_2;
      v20 = 0;
      v15 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, void **))(v14 + 80))(pHostObj_2, 2, 0, v17);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
      sub_4600B0(v15, v16, 0, 2);  // sub_4600B0 —— 演播层注册(槽号)
      *((uint8_t *)this + 125) = 1;  // 写字段 this+125（field_007D）
      sub_5E5260(v17);  // 调 动画子对象清理临时缓冲
    }
  }
}



// ------------------------------------------------------------
// 0x623EB0 sub_623EB0 —— 全局登记表按项删除
//    在 dword_9B9434（12 字节记录：对象/持有者/第三字段）按首字段查 nArg1，命中则前移覆盖并收缩尾指针；返回是否命中。
// ------------------------------------------------------------
char /*cdecl*/ sub_623EB0(int nArg1)  // sub_623EB0 —— 全局登记表按项删除
{
  int *v1; // eax
  int dword_9B94382; // ecx
  int v3; // esi
  int dword_9B94383; // edx
  int *v6; // ecx
  int *v7; // edi
  int v8; // esi

  v1 = (int *)dword_9B9434;
  dword_9B94382 = dword_9B9438;
  if ( dword_9B9434 == dword_9B9438 )
    return 0;
  while ( 1 )  // 无限循环
  {
    v3 = *v1;
    v1 += 3;
    if ( v3 == nArg1 )
      break;
    if ( v1 == (int *)dword_9B9438 )
      return 0;
  }
  dword_9B94383 = dword_9B9438;
  if ( v1 != (int *)dword_9B9438 )
  {
    v6 = v1 - 3;  // 计算 v6 = v1 - 3
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
    while ( v1 != (int *)dword_9B94383 );
    dword_9B94382 = dword_9B9438;
  }
  dword_9B9438 = dword_9B94382 - 12;
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x623F20 sub_623F20 —— vector 超长抛错
//    以 sub_4015C0 构造字符串 vector<T> too long 后抛 std::length_error（12 字节元素系共用）。
// ------------------------------------------------------------
void /*noreturn*/ sub_623F20()  // sub_623F20 —— vector 超长抛错
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x623F90 sub_623F90 —— 12 字节元素 vector 区间插入
//     _Insert_n 展开：容量足时分前后两段前移(sub_504450/5043B0)并填入 Block；
//    不足则按 1.5 倍扩容(sub_4DA030 兜底)后经 sub_59EE30/623C10 重排。
// ------------------------------------------------------------
int /*thiscall*/ sub_623F90(int *this, int pArg2, unsigned int uArg3, int *Block)  // sub_623F90 —— 12 字节元素 vector 区间插入
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
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;  // this+12〔nSkillRec12(推断)〕
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_623F20(this);  // sub_623F20 —— vector 超长抛错
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 12 >= uArg3 )
      {
        v27 = (int)fld_e23 - 12 * uArg3;
        *(this + 2) = sub_59EE30(v27, fld_e23, fld_e23);  // sub_59EE30 —— 三元组块搬移辅助
        sub_504450(pArg2, v27, Blockb);  // sub_504450 —— 搬移插入位后元素
        return sub_5043B0(pArg2, pArg2 + 12 * uArg3, v25);  // sub_5043B0 —— 在插入位填 n 条
      }
      else
      {
        sub_59EE30(pArg2, fld_e23, pArg2 + 12 * uArg3);  // sub_59EE30 —— 三元组块搬移辅助
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);  // sub_5E51C0 —— 填充补足尾段
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        return sub_5043B0(pArg2, fld_e26 - 12 * uArg3, v25);  // sub_5043B0 —— 在插入位填 n 条
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);  // sub_4DA030 —— v13 = 插入数 + sub_4DA030（当前数）
      v15 = 12 * v13;  // 计算 v15 = 12 * v13
      Blocka = (char *)operator new(12 * v13);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pArg2, Blocka);  // sub_59EE30 —— 三元组块搬移辅助
      sub_623C10(v28, uArg3, v25);  // sub_623C10 —— 就地构造（拷贝构造 1 个）
      sub_59EE30(pArg2, *(this + 2), v28 + 12 * uArg3);  // sub_59EE30 —— 三元组块搬移辅助
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;  // this+8〔nSkillRec8(推断)〕
      v17 = fld_e13 + uArg3;  // 计算 v17 = fld_e13 + uArg3
      if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
        j__free((void *)*(this + 1));  // 释放堆块
      *(this + 3) = (int)&Blocka[v15];  // 写字段 this+3 ← (int)&Blocka[v15]
      *(this + 2) = (int)&Blocka[12 * v17];  // 写字段 this+2 ← (int)&Blocka[12 * v17]
      *(this + 1) = (int)Blocka;  // 写字段 this+1 ← (int)Blocka
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x624240 sub_624240 —— 12 字节元素尾部追加
//    先记元素序号，调 sub_623F90(this,nArg3,1,Block) 插入 1 份，回传 *uArg2=begin+12*序号。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_624240(int *this, uint32_t *uArg2, int nArg3, int *Block)  // sub_624240 —— 12 字节元素尾部追加
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 12 != 0 )  // this+8〔nSkillRec8(推断)〕
    v6 = (nArg3 - fld_e1) / 12;
  else
    v6 = 0;
  sub_623F90(this, nArg3, 1u, Block);  // sub_623F90 —— 12 字节元素 vector 区间插入
  *uArg2 = *(this + 1) + 12 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x6242B0 CNSlowAndLowJump__vmt80 —— 限制件宿主离地查询 vmt80
//    返回宿主(*(this+1))虚 128 是否 >0（离地判定，供低跳限制切换）。
// ------------------------------------------------------------
bool /*thiscall*/ CNSlowAndLowJump__vmt80(uint32_t **this)  // 函数定义: 限制件宿主离地查询 vmt80
{
  return (*(int (/*thiscall*/ **)(uint32_t))(**(this + 1) + 128))(*(this + 1)) > 0;  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
}



// ------------------------------------------------------------
// 0x6242D0 CNSlowAndLowJump__vmt0 —— 限制件删除析构 vmt0
//    sub_624300 反初始化后按 pszArg2 位 0 决定 j__free。
// ------------------------------------------------------------
void */*thiscall*/ CNSlowAndLowJump__vmt0(void *Block, char pszArg2)  // 函数定义: 限制件删除析构 vmt0
{
  sub_624300();  // sub_624300 —— 限制件反初始化
  if ( (pszArg2 & 1) != 0 )  // 判定位掩码：pszArg2 & 1
    j__free(Block);  // 释放堆块
  return Block;
}



// ------------------------------------------------------------
// 0x624300 sub_624300 —— 限制件反初始化
//    改写虚表为 vftbl_CNSlowAndLowJump 后走 sub_4B3D50（CNChangeStatus 析构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_624300(uint32_t *this)  // sub_624300 —— 限制件反初始化
{
  *this = &vftbl_CNSlowAndLowJump;  // 装虚表/取地址：← vftbl_CNSlowAndLowJump
  return sub_4B3D50();  // sub_4B3D50 —— CNChangeStatus 析构
}



// ------------------------------------------------------------
// 0x624310 sub_624310 —— 挂低速/低跳限制件
//    参数块 v9=8/6、Y 偏移 -40/-40（529 类减半）；虚 756 防重复后 new(0x8C) 以 sub_5101B0 构造 CNChangeStatus 并虚 56 附着(参数 55/-1)，
//    随即继承 .equ 7/8 阈值到新件 +132/+136、把 +1104 掩码写到附着对象 +7088。
// ------------------------------------------------------------
int /*thiscall*/ sub_624310(int *this, void *Block)  // sub_624310 —— 挂低速/低跳限制件
{
  int v3; // eax
  int result; // eax
  int *pMem; // esi
  int v6; // edx
  int fld_e285; // eax
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
  v11 = -40.0;  // 浮点常量 v11 ← -40.0
  v12 = 6;
  v14 = -40.0;  // 浮点常量 v14 ← -40.0
  result = (*(int (/*thiscall*/ **)(int *, void *))(v3 + 756))(this, Block);  // 虚函数调用 槽+756：海星卵适配判定 vmt2F4
  if ( (uint8_t)result == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529) != 0 )  // 虚调用 vt+40（Block）条件查询(273等)
    {
      v11 = v11 * 0.5;
      v14 = v14 * 0.5;
    }
    pMem = (int *)operator new(0x8Cu);  // 堆分配
    v15 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      sub_5101B0(pMem, (int)&v9, 2, 0, 0);  // sub_5101B0 —— v87 = sub_5101B0 · CNChangeStatus 构造器
      *pMem = (int)&vftbl_CNSlowAndLowJump;  // 构造装配 vftable：CNSlowAndLowJump
    }
    else
    {
      pMem = nullptr;
    }
    v6 = *pMem;
    v15 = -1;
    (*(void (/*thiscall*/ **)(int *, void *, int *, uint32_t, uint32_t, int, int))(v6 + 56))(pMem, Block, this, 0, 0, 55, -1);  // 虚函数调用 槽+56：确认动作：+84 标志时 4
    fld_e285 = *(this + 285);  // 读字段 fld_e285 = this+285（bField285）
    v8 = pMem[1];
    pMem[33] = *(this + 284);  // this+284 绑定/记录门字节
    pMem[34] = fld_e285;
    result = *(this + 276);  // 读字段 result = this+276（pMapEntry）
    *(uint32_t *)(v8 + 7088) = result;  // 写字段 v8+7088 ← result
  }
  return result;
}



// ------------------------------------------------------------
// 0x624420 sub_624420 —— 12 字节元素追加（容量探测版）
//    容量足则在尾位经 sub_623C10 填充 1 份并推进尾指针，否则转 sub_624240 扩容插入。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_624420(int *this, int *Block)  // sub_624420 —— 12 字节元素追加（容量探测版）
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  uint32_t *fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 12;  // this+8〔nSkillRec8(推断)〕
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 12 )  // this+12〔nSkillRec12(推断)〕
    return sub_624240(this, &Block, *(this + 2), Block);  // sub_624240 —— 12 字节元素尾部追加
  fld_e22 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = sub_623C10(fld_e22, (uint32_t *)1, Block);  // sub_623C10 —— 就地构造（拷贝构造 1 个）
  *(this + 2) = (int)(fld_e22 + 3);  // 写字段 this+2 ← (int)(fld_e22 + 3)
  return result;
}



// ------------------------------------------------------------
// 0x6244A0 CNSwamp__vmt14C
//   【沼泽】SWAMP_BUBBLE_LOOP —— 沼泽气泡循环音
// ------------------------------------------------------------
int /*usercall*/ sub_6244A0@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>)  // 实现：(沼泽)SWAMP_BUBBLE_LOOP —— 沼泽气泡循环音
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
  int pObj2; // ecx
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
  uint32_t *Block3; // edi
  unsigned int k; // esi
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // edx
  int pObj3; // ecx
  int v37; // eax
  int v38; // edx
  int v39; // eax
  int v40; // eax
  int v41; // edx
  int v42; // edi
  void **v43; // eax
  void *Block2; // esi
  int v45; // eax
  uint32_t *v46; // eax
  int dword_9B94382; // ecx
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
  int pObj; // eax
  uint32_t *v59; // eax
  uint32_t v61[3]; // [esp+4h] [ebp-14h] BYREF
  unsigned int v62; // [esp+10h] [ebp-8h]
  void *Block; // [esp+14h] [ebp-4h]

  sub_60B6B0();  // 【CNMapObject__vmt14C】
  if ( *((uint8_t *)pDwArg1 + 1100) == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(  // 虚调用 vt+212（pDwArg1 虚表槽）
               pDwArg1,
               "SWAMP_BUBBLE_LOOP",  // 资源/动画 TAG SWAMP_BUBBLE_LOOP
               20880,
               0,
               0);
    *((uint8_t *)pDwArg1 + 1100) = 1;  // 写字段 pDwArg1+1100（nFairyGrade）
    return result;
  }
  v4 = pDwArg1[283];
  result = sub_699000((int)(pDwArg1 + 277));  // 【clock_now(clk)】
  if ( result >= v4 )
  {
    *((uint8_t *)pDwArg1 + 1121) = 0;  // 写字段 pDwArg1+1121（bCycleRstA）
    *((uint8_t *)pDwArg1 + 1122) = 0;  // 写字段 pDwArg1+1122（bCycleRstB）
    sub_698F90((int)(pDwArg1 + 277), 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    for ( i = 0; ; ++i )
    {
      v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 虚调用 vt+80（pDwArg1）读 4 字节
      v7 = *(uint32_t *)(v6 + 120);  // 读字段 v7 = v6+120（pAnimObj）
      v8 = v6 + 116;  // 计算 v8 = v6 + 116
      if ( v7 != 0 )
        v9 = (*(uint32_t *)(v8 + 8) - v7) >> 2;  // 向量元素数 = (end−begin)/4
      else
        v9 = 0;
      if ( (int)i >= v9 )
        goto LABEL_25;
      v10 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 80))(pDwArg1, nArg2);  // 虚调用 vt+80（pDwArg1）读 4 字节
      v11 = *(uint32_t *)(v10 + 120);  // 读字段 v11 = v10+120（pAnimObj）
      if ( v11 != 0 && i < (*(uint32_t *)(v10 + 124) - v11) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj2 = *(uint32_t *)(v11 + 4 * i);
      else
        pObj2 = 0;
      nArg2 = 33;
      if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 40))(pObj2) != 0 )  // 虚调用 vt+40（pObj2）条件查询(273等)
      {
        v13 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 虚调用 vt+80（pDwArg1）读 4 字节
        v14 = *(uint32_t *)(v13 + 120);  // 读字段 v14 = v13+120（pAnimObj）
        if ( v14 != 0 && i < (*(uint32_t *)(v13 + 124) - v14) >> 2 )  // 向量元素数 = (end−begin)/4
          v15 = *(uint32_t *)(v14 + 4 * i);
        else
          v15 = 0;
        if ( __RTDynamicCast(v15, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwamp `RTTI Type Descriptor', 0) != 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
          break;
      }
    }
    v16 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 虚调用 vt+80（pDwArg1）读 4 字节
    v17 = *(uint32_t *)(v16 + 120);  // 读字段 v17 = v16+120（pAnimObj）
    if ( v17 != 0 && i < (*(uint32_t *)(v16 + 124) - v17) >> 2 )  // 向量元素数 = (end−begin)/4
      result = *(uint32_t *)(v17 + 4 * i);
    else
      result = 0;
    if ( pDwArg1 == (int *)result )
    {
LABEL_25:
      for ( j = 0; ; j = v62 + 1 )
      {
LABEL_26:
        v19 = *pDwArg1;
        v62 = j;
        v20 = (*(int (/*thiscall*/ **)(int *))(v19 + 80))(pDwArg1);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        v21 = *(uint32_t *)(v20 + 120);  // 读字段 v21 = v20+120（pAnimObj）
        v22 = v20 + 116;  // 计算 v22 = v20 + 116
        if ( v21 != 0 )
          result = (*(uint32_t *)(v22 + 8) - v21) >> 2;  // 向量元素数 = (end−begin)/4
        else
          result = 0;
        if ( (int)j >= result )
          return result;
        v23 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 80))(pDwArg1, nArg2);  // 虚调用 vt+80（pDwArg1）读 4 字节
        v24 = *(uint32_t *)(v23 + 120);  // 读字段 v24 = v23+120（pAnimObj）
        if ( v24 != 0 && j < (*(uint32_t *)(v23 + 124) - v24) >> 2 )  // 向量元素数 = (end−begin)/4
          v25 = *(uint32_t *)(v24 + 4 * j);
        else
          v25 = 0;
        nArg2 = v25;
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 752))(pDwArg1) == 0 )  // 虚调用 vt+752（pDwArg1 虚表槽）
          continue;
        v26 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 虚调用 vt+80（pDwArg1）读 4 字节
        v27 = *(uint32_t *)(v26 + 120);  // 读字段 v27 = v26+120（pAnimObj）
        if ( v27 != 0 && j < (*(uint32_t *)(v26 + 124) - v27) >> 2 )  // 向量元素数 = (end−begin)/4
          Block3 = *(uint32_t **)(v27 + 4 * j);
        else
          Block3 = nullptr;
        Block = Block3;
        for ( k = 0; ; ++k )
        {
          v30 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 虚调用 vt+80（pDwArg1）读 4 字节
          v31 = *(uint32_t *)(v30 + 120);  // 读字段 v31 = v30+120（pAnimObj）
          v32 = v30 + 116;  // 计算 v32 = v30 + 116
          if ( v31 != 0 )
            v33 = (*(uint32_t *)(v32 + 8) - v31) >> 2;  // 向量元素数 = (end−begin)/4
          else
            v33 = 0;
          if ( (int)k >= v33 )
          {
            v46 = (uint32_t *)dword_9B9434;
            dword_9B94382 = dword_9B9438;
            if ( dword_9B9434 != dword_9B9438 )
            {
              while ( (uint32_t *)*v46 != Block3 )  // 循环直到 v46 != Block3
              {
                v46 += 3;
                if ( v46 == (uint32_t *)dword_9B9438 )
                {
                  j = v62 + 1;
                  goto LABEL_26;
                }
              }
              if ( Block3 != nullptr )  // 若 Block3 有效（非空）
              {
                for ( m = 0; ; ++m )
                {
                  v49 = (*(int (/*thiscall*/ **)(uint32_t *))(*Block3 + 700))(Block3);  // 虚调用 vt+700（Block3）提交交互
                  v50 = *(uint32_t *)(v49 + 4);  // 读字段 v50 = v49+4（pHostObj）
                  v51 = v50 != 0 ? (*(uint32_t *)(v49 + 8) - v50) >> 2 : 0;  // 向量元素数 = (end−begin)/4
                  if ( (int)m >= v51 )
                    break;
                  v52 = (*(int (/*thiscall*/ **)(uint32_t *))(*Block3 + 700))(Block3);  // 虚调用 vt+700（Block3）提交交互
                  v53 = *(uint32_t *)(v52 + 4);  // 读字段 v53 = v52+4（pHostObj）
                  if ( v53 != 0 && m < (*(uint32_t *)(v52 + 8) - v53) >> 2 )  // 向量元素数 = (end−begin)/4
                    v54 = *(uint32_t *)(v53 + 4 * m);
                  else
                    v54 = 0;
                  if ( *(uint32_t **)(v54 + 4) == Block3 )
                  {
                    v55 = (*(int (/*thiscall*/ **)(uint32_t *))(*Block3 + 700))(Block3);  // 虚调用 vt+700（Block3）提交交互
                    v56 = *(uint32_t *)(v55 + 4);  // 读字段 v56 = v55+4（pHostObj）
                    if ( v56 != 0 && m < (*(uint32_t *)(v55 + 8) - v56) >> 2 )  // 向量元素数 = (end−begin)/4
                      v57 = *(uint32_t *)(v56 + 4 * m);
                    else
                      v57 = 0;
                    pObj = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                            v57,
                            0,
                            &IRDAppendage `RTTI Type Descriptor',
                            &CNSlowAndLowJump `RTTI Type Descriptor',
                            0);
                    if ( pObj != 0 )
                    {
                      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 虚调用 vt+76（pObj 虚表槽）
                      break;
                    }
                  }
                }
                dword_9B94382 = dword_9B9438;
              }
              v59 = (uint32_t *)dword_9B9434;
              if ( dword_9B9434 == dword_9B94382 )
              {
LABEL_91:
                v59 = nullptr;
              }
              else
              {
                while ( (uint32_t *)*v59 != Block3 )  // 循环直到 v59 != Block3
                {
                  v59 += 3;
                  if ( v59 == (uint32_t *)dword_9B94382 )
                    goto LABEL_91;
                }
              }
              Block3[1772] = v59[2];
              sub_623EB0(Block3);  // sub_623EB0 —— 全局登记表按项删除
            }
            goto LABEL_93;
          }
          v34 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 80))(pDwArg1, nArg2);  // 虚调用 vt+80（pDwArg1）读 4 字节
          v35 = *(uint32_t *)(v34 + 120);  // 读字段 v35 = v34+120（pAnimObj）
          if ( v35 != 0 && k < (*(uint32_t *)(v34 + 124) - v35) >> 2 )  // 向量元素数 = (end−begin)/4
            pObj3 = *(uint32_t *)(v35 + 4 * k);
          else
            pObj3 = 0;
          nArg2 = 33;
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 40))(pObj3) != 0 )  // 虚调用 vt+40（pObj3）条件查询(273等)
          {
            v37 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 虚调用 vt+80（pDwArg1）读 4 字节
            v38 = *(uint32_t *)(v37 + 120);  // 读字段 v38 = v37+120（pAnimObj）
            if ( v38 != 0 && k < (*(uint32_t *)(v37 + 124) - v38) >> 2 )  // 向量元素数 = (end−begin)/4
              v39 = *(uint32_t *)(v38 + 4 * k);
            else
              v39 = 0;
            if ( __RTDynamicCast(v39, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNSwamp `RTTI Type Descriptor', 0) != 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
              break;
          }
LABEL_60:
          ;
        }
        v40 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 虚调用 vt+80（pDwArg1）读 4 字节
        v41 = *(uint32_t *)(v40 + 120);  // 读字段 v41 = v40+120（pAnimObj）
        if ( v41 != 0 && k < (*(uint32_t *)(v40 + 124) - v41) >> 2 )  // 向量元素数 = (end−begin)/4
          v42 = *(uint32_t *)(v41 + 4 * k);
        else
          v42 = 0;
        if ( (uint8_t)sub_60A7D0(Block) == 0 )  // sub_60A7D0 —— 关系门包装（vt+488）
          break;
        v43 = (void **)dword_9B9434;
        if ( dword_9B9434 == dword_9B9438 )
        {
LABEL_64:
          Block2 = Block;
          v45 = *((uint32_t *)Block + 1772);  // 读字段 v45 = Block[1772]
          v61[0] = Block;
          v61[1] = v42;
          v61[2] = v45;
          sub_624420(v61);  // sub_624420 —— 12 字节元素追加（容量探测版）
          sub_624310(Block2);  // sub_624310 —— 挂低速/低跳限制件
          j = v62 + 1;
          goto LABEL_26;
        }
        while ( *v43 != Block )  // 循环直到 v43 != Block
        {
          v43 += 3;
          if ( v43 == (void **)dword_9B9438 )
            goto LABEL_64;
        }
LABEL_93:
        ;
      }
      Block3 = Block;
      goto LABEL_60;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x6248A0 sub_6248A0 —— 宿主限制件全解挂
//    遍历 dword_9B9434 中持有者为入参的记录，对宿主子件表(虚 700)逐项 RTTI 判定 CNSlowAndLowJump 并虚 76 解挂，回填记录第三字段；
//    收集对象后逐个 sub_623EB0 摘除登记并释放临时数组。
// ------------------------------------------------------------
void /*thiscall*/ sub_6248A0(void *this)  // sub_6248A0 —— 宿主限制件全解挂
{
  uint8_t *v1; // edx
  char *v2; // ebx
  int *v3; // edi
  int dword_9B94382; // ecx
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
  uint8_t *pObj; // eax
  uint32_t *v17; // eax
  uint32_t *v18; // eax
  unsigned int v19; // esi
  char v20[4]; // [esp+Ch] [ebp-28h] BYREF
  uint8_t *v21; // [esp+10h] [ebp-24h]
  char *v22; // [esp+14h] [ebp-20h]
  int v23; // [esp+18h] [ebp-1Ch]
  int v24; // [esp+1Ch] [ebp-18h] BYREF
  void *pThis; // [esp+20h] [ebp-14h]
  int i; // [esp+24h] [ebp-10h]
  int v27; // [esp+30h] [ebp-4h]

  v1 = nullptr;
  v2 = nullptr;
  pThis = this;
  v21 = nullptr;
  v22 = nullptr;
  v23 = 0;
  v3 = (int *)dword_9B9434;
  dword_9B94382 = dword_9B9438;
  v27 = 0;
  for ( i = dword_9B9434; v3 != (int *)dword_9B94382; i = (int)v3 )
  {
    if ( (void *)v3[1] == pThis )
    {
      v5 = (uint32_t *)*v3;
      v24 = *v3;
      if ( v24 != 0 )
      {
        for ( j = 0; ; ++j )
        {
          v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 700))(v5);  // 虚调用 vt+700（v5）提交交互
          v8 = *(uint32_t *)(v7 + 4);  // 读字段 v8 = v7+4（pHostObj）
          v9 = v8 != 0 ? (*(uint32_t *)(v7 + 8) - v8) >> 2 : 0;  // 向量元素数 = (end−begin)/4
          if ( (int)j >= v9 )
            break;
          v10 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 700))(v5);  // 虚调用 vt+700（v5）提交交互
          v11 = *(uint32_t *)(v10 + 4);  // 读字段 v11 = v10+4（pHostObj）
          if ( v11 != 0 && j < (*(uint32_t *)(v10 + 8) - v11) >> 2 )  // 向量元素数 = (end−begin)/4
            v12 = *(uint32_t *)(v11 + 4 * j);
          else
            v12 = 0;
          if ( *(uint32_t **)(v12 + 4) == v5 )
          {
            v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*v5 + 700))(v5);  // 虚调用 vt+700（v5）提交交互
            v14 = *(uint32_t *)(v13 + 4);  // 读字段 v14 = v13+4（pHostObj）
            if ( v14 != 0 && j < (*(uint32_t *)(v13 + 8) - v14) >> 2 )  // 向量元素数 = (end−begin)/4
              v15 = *(uint32_t **)(v14 + 4 * j);
            else
              v15 = nullptr;
            pObj = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                    v15,
                    0,
                    &IRDAppendage `RTTI Type Descriptor',
                    &CNSlowAndLowJump `RTTI Type Descriptor',
                    0);
            if ( pObj != nullptr )  // 若 pObj 有效（非空）
            {
              (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 虚调用 vt+76（pObj 虚表槽）
              break;
            }
          }
        }
        dword_9B94382 = dword_9B9438;
        v3 = (int *)i;
        v1 = v21;
      }
      v17 = (uint32_t *)dword_9B9434;
      if ( dword_9B9434 != dword_9B94382 )
      {
        while ( (uint32_t *)*v17 != v5 )  // 循环直到 v17 != v5
        {
          v17 += 3;
          if ( v17 == (uint32_t *)dword_9B94382 )
            goto LABEL_31;
        }
        v18 = (uint32_t *)dword_9B9434;
        if ( dword_9B9434 == dword_9B94382 )
        {
LABEL_29:
          v18 = nullptr;
        }
        else
        {
          while ( (uint32_t *)*v18 != v5 )  // 循环直到 v18 != v5
          {
            v18 += 3;
            if ( v18 == (uint32_t *)dword_9B94382 )
              goto LABEL_29;
          }
        }
        v5[1772] = v18[2];
      }
LABEL_31:
      if ( v1 != nullptr && (v2 - v1) >> 2 < (unsigned int)((v23 - (int)v1) >> 2) )  // 向量元素数 = (end−begin)/4
      {
        *(uint32_t *)v2 = v5;
        v2 += 4;
        v22 = v2;
      }
      else
      {
        sub_4E75F0((int)v20, (int)v2, 1u, &v24);  // sub_4E75F0 —— uint32 vector 区间插入（容量 1.5 倍增长 + 三段搬运）
        v2 = v22;
        v3 = (int *)i;
        v1 = v21;
      }
      dword_9B94382 = dword_9B9438;
    }
    v3 += 3;
  }
  v19 = 0;
  while ( v1 != nullptr )  // 循环直到 v1 != nullptr
  {
    if ( v19 >= (v2 - v1) >> 2 )  // 向量元素数 = (end−begin)/4
    {
      j__free(v1);  // 释放堆块
      return;
    }
    sub_623EB0(*(uint32_t *)&v1[4 * v19]);  // sub_623EB0 —— 全局登记表按项删除
    v1 = v21;
    ++v19;  // 计数自增 v19
  }
}


// ------------------------------------------------------------
// 0x624A80 CNStarFishEggRequid__vmt14C —— 海星卵 tick vmt14C
//    基类后：目标(表项 2)命中或已失效(+170=0)时，若为自身且存活且未销毁则虚 312 停用；否则虚 196 吸附目标、清目标 +32/+36，
//    停 20880/20881 两条音效后 sub_6248A0 全解挂。
// ------------------------------------------------------------
void /*usercall*/ CNStarFishEggRequid__vmt14C(uint32_t *pArg1@<ecx>, int nArg2@<edi>)  // 函数定义: 海星卵 tick vmt14C
{
  uint32_t *v3; // edi
  uint32_t *v4; // edi

  CNSwamp__vmt14C((int)pArg1, nArg2);
  v3 = (uint32_t *)(pArg1[36] + 8);
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) == *v3  // 虚调用 vt+200（pArg1）取值比较
    || *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) == 0 )  // 虚调用 vt+200（pArg1）取值比较
  {
    v4 = (uint32_t *)(pArg1[36] + 8);
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) == *v4  // 虚调用 vt+200（pArg1）取值比较
      && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0  // 虚调用 vt+200（pArg1）取值比较
      && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0  // 虚调用 vt+308（pArg1）是否本地玩家
      && *((uint8_t *)pArg1 + 264) == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);  // 虚调用 vt+312（pArg1 虚表槽）
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[36] + 8));  // 虚调用 vt+196（pArg1）物件非空判定
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 340))(pArg1) + 32) = 0;  // 虚调用 vt+340（pArg1 虚表槽）
    *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 340))(pArg1) + 36) = 0;  // 虚调用 vt+340（pArg1 虚表槽）
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 216))(pArg1, 20880);  // 虚调用 vt+216（pArg1）全场广播
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 216))(pArg1, 20881);  // 虚调用 vt+216（pArg1）全场广播
    sub_6248A0(pArg1);  // sub_6248A0 —— 宿主限制件全解挂
  }
}



// ------------------------------------------------------------
// 0x624B70 CNSwamp__vmt12C —— 沼泽卸载 vmt12C
//    来客类别 17 时：在子件表 RTTI 找 CNSlowAndLowJump 虚 76 解挂，回填记录第三字段到 +7088 后 sub_623EB0 摘除登记；自身卸载则 sub_6248A0 清全部。
// ------------------------------------------------------------
void /*thiscall*/ CNSwamp__vmt12C(uint32_t *this, uint32_t *pArg2)  // 函数定义: 沼泽卸载 vmt12C
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
  int pObj; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // ecx

  CNMapObject__vmt12C(this, (int)pArg2);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0 )  // 虚调用 vt+40（pArg2）条件查询(273等)
  {
    v3 = (uint32_t *)dword_9B9434;
    if ( dword_9B9434 != dword_9B9438 )
    {
      while ( (uint32_t *)*v3 != pArg2 )  // 循环直到 v3 != pArg2
      {
        v3 += 3;
        if ( v3 == (uint32_t *)dword_9B9438 )
          goto LABEL_33;
      }
      for ( i = 0; ; ++i )
      {
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 700))(pArg2);  // 虚调用 vt+700（pArg2）提交交互
        v6 = *(uint32_t *)(v5 + 4);  // 读字段 v6 = v5+4（pHostObj）
        v7 = v6 != 0 ? (*(uint32_t *)(v5 + 8) - v6) >> 2 : 0;  // 向量元素数 = (end−begin)/4
        if ( (int)i >= v7 )
          break;
        v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 700))(pArg2);  // 虚调用 vt+700（pArg2）提交交互
        v9 = *(uint32_t *)(v8 + 4);  // 读字段 v9 = v8+4（pHostObj）
        if ( v9 != 0 && i < (*(uint32_t *)(v8 + 8) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        if ( *(uint32_t **)(v10 + 4) == pArg2 )
        {
          v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 700))(pArg2);  // 虚调用 vt+700（pArg2）提交交互
          v12 = *(uint32_t *)(v11 + 4);  // 读字段 v12 = v11+4（pHostObj）
          if ( v12 != 0 && i < (*(uint32_t *)(v11 + 8) - v12) >> 2 )  // 向量元素数 = (end−begin)/4
            v13 = *(uint32_t *)(v12 + 4 * i);
          else
            v13 = 0;
          pObj = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
                  v13,
                  0,
                  &IRDAppendage `RTTI Type Descriptor',
                  &CNSlowAndLowJump `RTTI Type Descriptor',
                  0);
          if ( pObj != 0 )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);  // 虚调用 vt+76（pObj 虚表槽）
            break;
          }
        }
      }
      v15 = (uint32_t *)dword_9B9434;
      v16 = (uint32_t *)dword_9B9434;
      if ( dword_9B9434 != dword_9B9438 )
      {
        while ( (uint32_t *)*v16 != pArg2 )  // 循环直到 v16 != pArg2
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
          while ( (uint32_t *)*v15 != pArg2 )  // 循环直到 v15 != pArg2
          {
            v15 += 3;
            if ( v15 == (uint32_t *)dword_9B9438 )
              goto LABEL_30;
          }
        }
        pArg2[1772] = v15[2];
      }
LABEL_32:
      sub_623EB0((int)pArg2);  // sub_623EB0 —— 全局登记表按项删除
    }
  }
LABEL_33:
  if ( pArg2 == this )
    sub_6248A0(this);  // sub_6248A0 —— 宿主限制件全解挂
}



// ------------------------------------------------------------
// 0x624CC0 sub_624CC0 —— 地刺状态重置（thunk）
//    直接虚 372(this,100)，用于弹回/重设刺出状态。
// ------------------------------------------------------------
int /*thiscall*/ sub_624CC0(void *this, int nArg2)  // sub_624CC0 —— 地刺状态重置（thunk）
{
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
}



// ------------------------------------------------------------
// 0x624CD0 sub_624CD0 —— 地刺登记表删除
//    在 dword_9B9444（8 字节记录）按首字段查 nArg1 并前移覆盖收缩尾指针；两个返回分支都恒返回 1。
// ------------------------------------------------------------
char /*cdecl*/ sub_624CD0(int nArg1)  // sub_624CD0 —— 地刺登记表删除
{
  int *v1; // eax
  int dword_9B94482; // ecx
  int v3; // esi
  int dword_9B94483; // edx
  int *v6; // ecx

  v1 = (int *)dword_9B9444;
  dword_9B94482 = dword_9B9448;
  if ( dword_9B9444 != dword_9B9448 )
  {
    while ( 1 )  // 无限循环
    {
      v3 = *v1;
      v1 += 2;
      if ( v3 == nArg1 )
        break;
      if ( v1 == (int *)dword_9B9448 )
        return 1;  // 返回 1(成功)
    }
    dword_9B94483 = dword_9B9448;
    if ( v1 != (int *)dword_9B9448 )
    {
      v6 = v1 - 2;  // 计算 v6 = v1 - 2
      do
      {
        *v6 = *v1;
        v6[1] = v1[1];
        v1 += 2;
        v6 += 2;
      }
      while ( v1 != (int *)dword_9B94483 );
      dword_9B94482 = dword_9B9448;
    }
    dword_9B9448 = dword_9B94482 - 8;
  }
  return 1;  // 返回 1(成功)
}



// ============================================================
// 【分区 7】地刺（CNFloorNiddle，0x624D30-0x6251B0）
// 物件: 地板刺陷阱（伸缩刺）；含碰撞回调与周期驱动
// ============================================================

// ------------------------------------------------------------
// 0x624D30 CNFloorNiddle__vmt12C —— 地刺卸载 vmt12C
//    基类后，来客类别 17 时调 sub_624CD0 从登记表摘除。
// ------------------------------------------------------------
char /*thiscall*/ CNFloorNiddle__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 地刺卸载 vmt12C
{
  char result; // al

  CNRDPassiveObject__vmt12C(this, nArg2);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);  // 虚调用 vt+40（nArg2）条件查询(273等)
  if ( result != 0 )  // 若结果非 0（成功）
    return sub_624CD0(nArg2);  // sub_624CD0 —— 地刺登记表删除
  return result;
}



// ------------------------------------------------------------
// 0x624D60 sub_624D60 —— vector 超长抛错（8 字节系）
//    与 sub_623F20 同构（差异：服务于 8 字节元素 vector）。
// ------------------------------------------------------------
void /*noreturn*/ sub_624D60()  // sub_624D60 —— vector 超长抛错（8 字节系）
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0((void *)"vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);  // sub_401740 —— std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject = &std::length_error::`vftable';  // 写 vftable 指针（对象重定位/复位）
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);  // 抛出 C++ 异常（越界/长度非法）
}



// ------------------------------------------------------------
// 0x624DD0 sub_624DD0 —— 8 字节元素 vector 区间插入
//     _Insert_n 展开：容量足则以 sub_44BD30 前移后段、sub_63A7C0 构造 uArg3 份副本、sub_44BD00 回搬尾段；
//    不足则按 1.5 倍扩容后 operator new 重建，sub_5E51F0 收尾。
// ------------------------------------------------------------
void /*thiscall*/ sub_624DD0(int this, uint32_t *uArg2, unsigned int uArg3, int pArg4)  // sub_624DD0 —— 8 字节元素 vector 区间插入
{
  void *v4; // edx
  int fld_4; // ecx
  unsigned int fld_C; // eax
  int fld_8; // edx
  int fld_82; // edx
  unsigned int v11; // eax
  int fld_87; // edx
  int fld_88; // eax
  char *pMem; // edi
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v17; // ebx
  int fld_83; // eax
  bool v20; // cf
  int v21; // ecx
  int fld_86; // ebx
  int v23; // ebx
  int fld_42; // [esp-18h] [ebp-40h]
  int fld_85; // [esp-Ch] [ebp-34h]
  unsigned int fld_84; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int fld_832; // [esp+38h] [ebp+10h]

  v4 = *(void **)(pArg4 + 4);  // pArg4+4〔宿主对象〕
  v28[0] = *(void **)pArg4;
  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;  // this+12 物品类型号
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_624D60(this);  // sub_624D60 —— vector 超长抛错（8 字节系）
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);  // 读字段 fld_83 = this+8（nSkillRec8）
      v20 = (fld_83 - (int)uArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;  // 计算 v21 = 8 * uArg3
      v30 = 8 * uArg3;  // 计算 v30 = 8 * uArg3
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_44BD30(uArg2, fld_83, &uArg2[v21 / 4u]);  // sub_44BD30 —— 8 字节元素正向拷贝
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - (int)uArg2) >> 3);  // this+8 物品 id
        fld_85 = *(uint32_t *)(this + 8);  // 读字段 fld_85 = this+8（nSkillRec8）
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);  // sub_5E51F0 —— 填充补足尾段
        fld_86 = v30 + *(uint32_t *)(this + 8);  // this+8 物品 id
        *(uint32_t *)(this + 8) = fld_86;  // 写字段 this+8（nSkillRec8） ← fld_86
        sub_41FEB0(uArg2, (uint32_t *)(fld_86 - v30), v28);  // sub_41FEB0 —— 8B 元素区间拷贝
      }
      else
      {
        v23 = fld_83 - v21;  // 计算 v23 = fld_83 - v21
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);  // sub_44BD30 —— 8 字节元素正向拷贝
        sub_44BD00(uArg2, v23, fld_832);  // sub_44BD00 —— 8 字节元素反向拷贝
        sub_41FEB0(uArg2, &uArg2[v30 / 4u], v28);  // sub_41FEB0 —— 8B 元素区间拷贝
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;  // 计算 v11 = uArg3 + fld_88
      }
      v31 = 8 * v11;  // 计算 v31 = 8 * v11
      pMem = (char *)operator new(8 * v11);  // 堆分配
      fld_42 = *(uint32_t *)(this + 4);  // 读字段 fld_42 = this+4（pHostObj）
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, uArg2, pMem);  // sub_44BD30 —— 8 字节元素正向拷贝
      sub_63A7C0(v32, uArg3, v28);  // sub_63A7C0 —— 强化结果公共件（30 行）
      sub_44BD30(uArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);  // sub_44BD30 —— 8 字节元素正向拷贝
      fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;  // this+8 物品 id
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;  // 计算 v17 = fld_89 + uArg3
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));  // 释放堆块
      *(uint32_t *)(this + 12) = &pMem[v31];  // 写字段 this+12（nSkillRec12） ← &pMem[v31]
      *(uint32_t *)(this + 8) = &pMem[8 * v17];  // 写字段 this+8（nSkillRec8） ← &pMem[8 * v17]
      *(uint32_t *)(this + 4) = pMem;  // 写字段 this+4（pHostObj） ← pMem
    }
  }
}


// ------------------------------------------------------------
// 0x625020 sub_625020 —— 8 字节元素尾部追加
//    容量足则在尾位调 sub_63A7C0(尾,1,nArg2) 构造 1 份并尾指针 +8，否则转 sub_624DD0 扩容。
// ------------------------------------------------------------
void /*thiscall*/ sub_625020(int this, int nArg2)  // sub_625020 —— 8 字节元素尾部追加
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;  // this+8 物品 id
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 3 )  // this+12 物品类型号
  {
    fld_82 = *(uint32_t *)(this + 8);  // 读字段 fld_82 = this+8（nSkillRec8）
    sub_63A7C0(fld_82, 1, nArg2);  // sub_63A7C0 —— 强化结果公共件（30 行）
    *(uint32_t *)(this + 8) = fld_82 + 8;  // 写字段 this+8（nSkillRec8） ← fld_82 + 8
  }
  else
  {
    sub_624DD0(this, *(char **)(this + 8), 1u, nArg2);  // sub_624DD0 —— 8 字节元素 vector 区间插入
  }
}



// ------------------------------------------------------------
// 0x625090 sub_625090 —— 地刺范围登记
//    在 dword_9B9444 查 pArg1：未登记则以 {pArg1, clock_now(+36)} 追加进 unk_9B9440 并返回 1，已存在返回 0。
// ------------------------------------------------------------
char /*cdecl*/ sub_625090(int pArg1)  // sub_625090 —— 地刺范围登记
{
  uint32_t *v1; // eax
  uint32_t v3[2]; // [esp+0h] [ebp-8h] BYREF

  v1 = (uint32_t *)dword_9B9444;
  if ( dword_9B9444 == dword_9B9448 )
  {
LABEL_4:
    v3[0] = pArg1;
    v3[1] = sub_699000(pArg1 + 36);  // 【clock_now(clk)】
    sub_625020((int)&unk_9B9440, (int)v3);  // sub_625020 —— 8 字节元素尾部追加
    return 1;  // 返回 1(成功)
  }
  else
  {
    while ( *v1 != pArg1 )  // 循环直到 v1 != pArg1
    {
      v1 += 2;
      if ( v1 == (uint32_t *)dword_9B9448 )
        goto LABEL_4;
    }
    return 0;
  }
}



// ------------------------------------------------------------
// 0x6250E0 sub_6250E0 —— 地刺冷却登记
//    与 sub_625090 同构（差异：已登记且时间戳 +3000 未过返回 0，否则刷新时间戳返回 1）。
// ------------------------------------------------------------
char /*cdecl*/ sub_6250E0(int pArg1)  // sub_6250E0 —— 地刺冷却登记
{
  uint32_t *v1; // esi
  uint32_t v3[2]; // [esp+4h] [ebp-8h] BYREF

  v1 = (uint32_t *)dword_9B9444;
  if ( dword_9B9444 == dword_9B9448 )
  {
LABEL_4:
    v3[0] = pArg1;
    v3[1] = sub_699000(pArg1 + 36);  // 【clock_now(clk)】
    sub_625020((int)&unk_9B9440, (int)v3);  // sub_625020 —— 8 字节元素尾部追加
    return 1;  // 返回 1(成功)
  }
  else
  {
    while ( *v1 != pArg1 )  // 循环直到 v1 != pArg1
    {
      v1 += 2;
      if ( v1 == (uint32_t *)dword_9B9448 )
        goto LABEL_4;
    }
    if ( v1[1] + 3000 >= (unsigned int)sub_699000(pArg1 + 36) )  // 【clock_now(clk)】
    {
      return 0;
    }
    else
    {
      v1[1] = sub_699000(pArg1 + 36);  // 【clock_now(clk)】
      return 1;  // 返回 1(成功)
    }
  }
}



// ------------------------------------------------------------
// 0x625160 CNFloorNiddle__vmt1F4 —— 地刺触发回调 vmt1F4
//    来客类别 17 时先 sub_625090 登记，再走基类 vmt1F4，末尾虚 352 重设地刺周期。
// ------------------------------------------------------------
int /*thiscall*/ CNFloorNiddle__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)  // 函数定义: 地刺触发回调 vmt1F4
{
  int v5; // edi

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) != 0 )  // 虚调用 vt+40（pArg2）条件查询(273等)
    sub_625090((int)pArg2);  // sub_625090 —— 地刺范围登记
  v5 = CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);  // v5 = 调 CNRDPassiveObject__vmt1F4
  (*(void (/*thiscall*/ **)(int *))(*this + 352))(this);  // 虚调用 vt+352（this 虚表槽）
  return v5;
}



// ------------------------------------------------------------
// 0x6251B0 CNFloorNiddle__vmt1E0 —— 地刺接触判定 vmt1E0
//    类别 17 时先走基类 vmt1E0，为真再经 sub_6250E0 冷却登记放行；否则原样返回。
// ------------------------------------------------------------
char /*thiscall*/ CNFloorNiddle__vmt1E0(int *this, int *pDwArg2, int nArg3)  // 函数定义: 地刺接触判定 vmt1E0
{
  char result; // al
  char v5; // bl

  result = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg2 + 40))(pDwArg2, 17);  // 虚调用 vt+40（pDwArg2）条件查询(273等)
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v5 = IRDCollisionObject__vmt1E0(this, pDwArg2, nArg3);  // v5 = 调 IRDCollisionObject__vmt1E0
    if ( v5 == 0 )
      return v5;
    result = sub_6250E0((int)pDwArg2);  // sub_6250E0 —— 地刺冷却登记
    if ( result != 0 )  // 若结果非 0（成功）
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
// 0x625200 CNGoblinBunker__vmt140 —— 掩体开合插值 vmt140
//    开门位(+276)置起时经虚 656 驱动，取 .equ 7/8 项在 sub_4049C0 上插值(总长 99)落 +680:+684，并虚 472(0,0,1,1) 复位朝向。
// ------------------------------------------------------------
char /*thiscall*/ CNGoblinBunker__vmt140(uint8_t *this)  // 函数定义: 掩体开合插值 vmt140
{
  int pThis_50; // eax
  uint64_t v3; // rax
  float v5; // [esp+8h] [ebp-1Ch]
  float v6; // [esp+Ch] [ebp-18h]
  int pThis_180; // [esp+1Ch] [ebp-8h]
  int pThis_1802; // [esp+20h] [ebp-4h]

  if ( *(this + 276) != 0 )  // this+276 地图条目指针
  {
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 656))(this);  // 虚调用 vt+656（this 虚表槽）
    pThis_180 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 7);  // 虚调用 vt+384（this 虚表槽）
    pThis_1802 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 384))(this, 8);  // 虚调用 vt+384（this 虚表槽）
    pThis_50 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 80))(this);  // 虚调用 vt+80（this）读 4 字节
    v6 = (float)pThis_1802;
    v5 = (float)pThis_180;
    v3 = (uint64_t)sub_4049C0(v5, v6, *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(pThis_50 + 132) + 108) + 92), 99);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    HIDWORD(v3) = *(uint32_t *)this;  // 调 取 64 位值高 32 位
    *((uint32_t *)this + 170) = v3;  // 写字段 this[170]（宽4字节）
    *((uint32_t *)this + 171) = v3;  // 写字段 this[171]（宽4字节）
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, int, int))(HIDWORD(v3) + 472))(this, 0, 0, 1, 1);  // 虚函数调用 槽+472：主状态机（874 行）：CONDITION_STUN/DOWN_HEAV
  }
  return CNRDPassiveObject__vmt140(this);  // 返回 调 CNRDPassiveObject__vmt140
}



// ------------------------------------------------------------
// 0x6252A0 CNGoblinBunker__vmt12C —— 掩体卸载 vmt12C
//    自身卸载且存活时先 sub_60ABE0 清地图块登记，再走基类 CNMapObject__vmt12C。
// ------------------------------------------------------------
char /*thiscall*/ CNGoblinBunker__vmt12C(unsigned int *this, unsigned int *pDwArg2)  // 函数定义: 掩体卸载 vmt12C
{
  if ( pDwArg2 == this && (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
    sub_60ABE0(this);  // 调 清地图块登记
  return CNMapObject__vmt12C(this, (int)pDwArg2);  // 返回 调 CNMapObject__vmt12C
}



// ------------------------------------------------------------
// 0x6252D0 sub_6252D0
//   【掩体辅助】属性投掷粒子四选一: Particle/FastThrowStone.ptl（石）/ IceMissile.ptl（冰）/
//             FireMissile.ptl（火）/ AimingBomb.ptl（弹）
// ------------------------------------------------------------
int /*userpurge*/ sub_6252D0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<esi>, int nArg3)  // 函数 sub_6252D0：= 属性投掷粒子选择器（石/冰/火/弹四选一，双子箱 0x62B360 复用）
{
  int result; // eax
  int nRand; // esi
  const void *v6; // esi
  int v7; // eax
  const void *v8; // esi
  int v9; // eax
  uint64_t v10; // rax
  int v11; // ecx
  const void *v12; // esi
  int v13; // eax
  int v14; // esi
  uint32_t pBuf[11]; // [esp+8h] [ebp-98h] BYREF
  int v17; // [esp+34h] [ebp-6Ch]
  uint32_t v18[26]; // [esp+38h] [ebp-68h] BYREF

  v18[25] = dword_796E50;  // dword_796E50 —— 栈检 cookie
  result = nArg3;
  if ( nArg3 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 虚调用 vt+308（pArg1）是否本地玩家
    if ( (uint8_t)result != 0 )
    {
      sub_432FA0();  // sub_432FA0 —— srand 播种
      pBuf[4] = 1;
      pBuf[5] = 1;
      pBuf[6] = 1;
      memset(pBuf, 0, 16);  // 清零 pBuf 起 16 字节
      pBuf[7] = 2;
      pBuf[8] = 2;
      pBuf[9] = 3;
      nRand = rand() % 10;  // 调 取伪随机数
      sub_423A20(v18);  // sub_423A20 —— 小结构初始化（0-100 刻度）
      result = pBuf[nRand];
      switch ( result )  // 按 result 分派
      {
        case 0:  // case 0 分派（哥布林掩体（CNGoblinBunker，0x625200-0x626220））
          v6 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 588))(  // 虚调用 vt+588（pArg1 虚表槽）
                               pArg1,
                               "Particle/FastThrowStone.ptl",  // 资源路径 Particle/FastThrowStone.ptl
                               nArg2);
          v7 = *pArg1;
          qmemcpy(v18, v6, 0x62u);  // 调 内存块拷贝(内联展开)
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v7 + 164))(pArg1, nArg3, 0);  // 虚函数调用 槽+164
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
                     pArg1,
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
        case 1:  // case 1 分派（哥布林掩体（CNGoblinBunker，0x625200-0x626220））
          v8 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 588))(  // 虚调用 vt+588（pArg1 虚表槽）
                               pArg1,
                               "Particle/IceMissile.ptl",  // 资源路径 Particle/IceMissile.ptl
                               nArg2);
          v9 = *pArg1;
          qmemcpy(v18, v8, 0x62u);  // 调 内存块拷贝(内联展开)
          v10 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v9 + 164))(pArg1, nArg3, 0);  // 虚函数调用 槽+164
          v18[18] = v10;
          v11 = 1;
          if ( (int)v10 >= 90 && (int)v10 < 270 )
          {
            v11 = 0;
            v18[18] = 180 - v10;
          }
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
                     pArg1,
                     42001,
                     *(uint32_t *)(pArg1[87] + 36),
                     v18,
                     0,
                     0,
                     10,
                     50,
                     v11,
                     0,
                     0);
          break;
        case 2:  // case 2 分派（哥布林掩体（CNGoblinBunker，0x625200-0x626220））
          v12 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 588))(  // 虚调用 vt+588（pArg1 虚表槽）
                                pArg1,
                                "Particle/FireMissile.ptl",  // 资源路径 Particle/FireMissile.ptl
                                nArg2);
          v13 = *pArg1;
          qmemcpy(v18, v12, 0x62u);  // 调 内存块拷贝(内联展开)
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v13 + 164))(pArg1, nArg3, 0);  // 虚函数调用 槽+164
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
                     pArg1,
                     40001,
                     *(uint32_t *)(pArg1[87] + 40),
                     v18,
                     0,
                     0,
                     10,
                     50,
                     1,
                     0,
                     0);
          break;
        case 3:  // case 3 分派（哥布林掩体（CNGoblinBunker，0x625200-0x626220））
          if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*pArg1 + 8))(pArg1, nArg3, 0, nArg2) >= 250 )  // 虚调用 vt+8（pArg1 虚表槽）
            v17 = 250;
          else
            v17 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, nArg3, 0);  // 虚调用 vt+8（pArg1 虚表槽）
          qmemcpy(  // 调 内存块拷贝(内联展开)
            v18,
            (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*pArg1 + 588))(pArg1, "Particle/AimingBomb.ptl"),  // 虚调用 vt+588（pArg1 虚表槽）
            0x62u);
          pBuf[10] = 2 * *(uint32_t *)((char *)&v18[7] + 3);
          v14 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v18[7] + 3)) / (double)v18[17] * 1000.0);
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(*pArg1 + 164))(pArg1, nArg3, 0);  // 虚函数调用 槽+164
          BYTE1(v18[22]) = 3;  // 调 取 32 位值的第 2 字节
          *(uint32_t *)((char *)&v18[3] + 3) = 1000 * v17 / v14;
          *(uint32_t *)((char *)&v18[4] + 3) = *(uint32_t *)((char *)&v18[3] + 3);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
                     pArg1,
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
// 0x625580 sub_625580 —— 掩体动画件批量停播
//    对 +144 键帧表偏移 8..68 的 16 项：虚 208 归还并 sub_4926A0 复位帧游标（开关门演出前的统一清理）。
// ------------------------------------------------------------
int /*thiscall*/ sub_625580(uint32_t *this)  // sub_625580 —— 掩体动画件批量停播
{
  int i; // esi
  int result; // eax

  for ( i = 8; i < 72; i += 4 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(i + *(this + 36)));  // 虚调用 vt+208（this）动画件回挂
    result = sub_4926A0(*(uint32_t *)(*(this + 36) + i));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
  }
  return result;
}



// ------------------------------------------------------------
// 0x6255C0 sub_6255C0 —— 掩体开盖演出
//    停全部件后以虚 196 与三段虚 204(100,表+40/+56/+64) 重设层次；再把 +1108 粒子件对齐到掩体上方 0.7 倍高度(虚 192*0.7+2)，
//    经 sub_4600B0(this+116,2,0,包) 播发。
// ------------------------------------------------------------
void /*thiscall*/ sub_6255C0(int this)  // sub_6255C0 —— 掩体开盖演出
{
  int fld_454; // edi
  int pThis_7C; // eax
  int pThis_78; // eax
  void *fld_74; // ecx
  uint8_t v6[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int pThis_C0; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  sub_625580((uint32_t *)this);  // sub_625580 —— 掩体动画件批量停播
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 16));  // 虚调用 vt+196（this）物件非空判定
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    100,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 40),  // this+144 第 4 组·+1040 增量子倍率
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    100,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 56),  // this+144 第 4 组·+1040 增量子倍率
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    100,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 64),  // this+144 第 4 组·+1040 增量子倍率
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 1108) + 12))(*(uint32_t *)(this + 1108), 0);  // this+1108 子对象槽
  fld_454 = **(uint32_t **)(this + 1108);  // this+1108 子对象槽
  pThis_C0 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 192))(this);  // 虚调用 vt+192（this）取尺寸/包围盒
  pThis_7C = (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 124))(  // 虚调用 vt+124（this）目标坐标y下界
         this,
         (uint64_t)((double)pThis_C0 * 0.69999999) >> 32,
         (uint64_t)((double)pThis_C0 * 0.69999999));
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C + 2);  // 虚调用 vt+120（this）转发(对象+缓冲)
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_454 + 40))(*(uint32_t *)(this + 1108), pThis_78);  // this+1108 子对象槽
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 1108) + 92))(*(uint32_t *)(this + 1108), v6);  // this+1108 子对象槽
  fld_74 = *(void **)(this + 116);  // this+116 观察者 vector 尾针
  v9 = 0;
  sub_4600B0(fld_74, 2, 0, (int)v6);  // sub_4600B0 —— 演播层注册(槽号)
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 释放堆块
}



// ------------------------------------------------------------
// 0x6256F0 sub_6256F0 —— 掩体状态 3 演出
//    停全部件后按开门位 +1100 二选一：1 取虚 196(表+20)+204(100,表+44)，0 取虚 196(表+12)+204(100,表+32)；收尾 204(100,表+60 或表+52) 与 204(100,表+68)。
// ------------------------------------------------------------
int /*thiscall*/ sub_6256F0(int *this)  // sub_6256F0 —— 掩体状态 3 演出
{
  int v2; // edx
  int fld_e36; // eax
  uint32_t *fld_e362; // eax

  sub_625580(this);  // sub_625580 —— 掩体动画件批量停播
  v2 = *this;
  fld_e36 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
  if ( *((uint8_t *)this + 1100) == 1 )  // this+1100 时钟槽
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 20));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      100,
      *(uint32_t *)(*(this + 36) + 44),  // this+36 物品状态字
      0,
      0,
      0,
      0);
    fld_e362 = (uint32_t *)(*(this + 36) + 60);  // this+36 物品状态字
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 12));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      100,
      *(uint32_t *)(*(this + 36) + 32),  // this+36 物品状态字
      0,
      0,
      0,
      0);
    fld_e362 = (uint32_t *)(*(this + 36) + 52);  // this+36 物品状态字
  }
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 100, *fld_e362, 0, 0, 0, 0);  // 虚调用 vt+204（this 虚表槽）
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           *(uint32_t *)(*(this + 36) + 68),  // this+36 物品状态字
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x6257C0 sub_6257C0 —— 掩体状态 2 演出
//    与 sub_6256F0 同构（差异：开门分支取表 +16/+40/+56，关门取表 +8/+28/+48，尾段统一表 +64）。
// ------------------------------------------------------------
int /*thiscall*/ sub_6257C0(int *this)  // sub_6257C0 —— 掩体状态 2 演出
{
  int v2; // edx
  int fld_e36; // eax
  uint32_t *fld_e362; // eax

  sub_625580(this);  // sub_625580 —— 掩体动画件批量停播
  v2 = *this;
  fld_e36 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
  if ( *((uint8_t *)this + 1100) == 1 )  // this+1100 时钟槽
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 16));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      100,
      *(uint32_t *)(*(this + 36) + 40),  // this+36 物品状态字
      0,
      0,
      0,
      0);
    fld_e362 = (uint32_t *)(*(this + 36) + 56);  // this+36 物品状态字
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 8));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      100,
      *(uint32_t *)(*(this + 36) + 28),  // this+36 物品状态字
      0,
      0,
      0,
      0);
    fld_e362 = (uint32_t *)(*(this + 36) + 48);  // this+36 物品状态字
  }
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 100, *fld_e362, 0, 0, 0, 0);  // 虚调用 vt+204（this 虚表槽）
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           *(uint32_t *)(*(this + 36) + 64),  // this+36 物品状态字
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x625890 sub_625890 —— 掩体 BUNKER_OPEN 演出
//    与 sub_6257C0 同构（差异：取表 +16/+36/+56 与 +8/+24/+48）。
// ------------------------------------------------------------
int /*thiscall*/ sub_625890(int *this)  // sub_625890 —— 掩体 BUNKER_OPEN 演出
{
  int v2; // edx
  int fld_e36; // eax
  uint32_t *fld_e362; // eax

  sub_625580(this);  // sub_625580 —— 掩体动画件批量停播
  v2 = *this;
  fld_e36 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
  if ( *((uint8_t *)this + 1100) == 1 )  // this+1100 时钟槽
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 16));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      100,
      *(uint32_t *)(*(this + 36) + 36),  // this+36 物品状态字
      0,
      0,
      0,
      0);
    fld_e362 = (uint32_t *)(*(this + 36) + 56);  // this+36 物品状态字
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 8));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      100,
      *(uint32_t *)(*(this + 36) + 24),  // this+36 物品状态字
      0,
      0,
      0,
      0);
    fld_e362 = (uint32_t *)(*(this + 36) + 48);  // this+36 物品状态字
  }
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(this, 100, *fld_e362, 0, 0, 0, 0);  // 虚调用 vt+204（this 虚表槽）
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           *(uint32_t *)(*(this + 36) + 64),  // this+36 物品状态字
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x625960 CNGoblinBunker__vmt2B4
//   【掩体】BUNKER_HIT（受击）/ BUNKER_BREAK（破碎）/ GBN_FRIGHT（哥布林惊叫）
// ------------------------------------------------------------
int /*thiscall*/ CNGoblinBunker__vmt2B4(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int nHpCur680; // ecx  | +0x02A8 → 当前 HP（625960 受击比对：< +684/2 触发半血演出）（证据 va=004E1FE0）（CNGoblinBunker；va=004E1FE0）
  int result; // eax

  (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "BUNKER_HIT", -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
  nHpCur680 = *(uint32_t *)(this + 680);  // 读字段 fld_2A8 = this+680（nSnapshot680）
  if ( nHpCur680 > 0 )
  {
    if ( *(uint8_t *)(this + 1100) == 0 && nHpCur680 < *(uint32_t *)(this + 684) / 2 )  // this+1100 开门位
    {
      sub_6255C0(this);  // sub_6255C0 —— 掩体开盖演出
      *(uint8_t *)(this + 1100) = 1;  // 写字段 this+1100（nFairyGrade） ← 1
    }
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
    if ( (uint8_t)result != 0 )
      result = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 3, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
  }
  else
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
      this,
      "BUNKER_BREAK",  // 资源/动画 TAG BUNKER_BREAK
      -1,
      0,
      0);
    result = *(uint32_t *)(this + 1080);  // 读字段 result = this+1080（nAnimIdx1080）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = (*(uint32_t *)(this + 1084) - result) / 12;  // this+1084 开合插值结束帧号
      if ( result != 0 )  // 若结果非 0（成功）
        result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
                   this,
                   "GBN_FRIGHT",  // 资源/动画 TAG GBN_FRIGHT
                   -1,
                   0,
                   0);
    }
  }
  if ( *(uint8_t *)(this + 1100) == 1 )  // this+1100 开门位
  {
    result = *(uint32_t *)(this + 684) / 2;  // this+684 最大 HP
    if ( *(uint32_t *)(this + 680) >= result )  // this+680 当前 HP
    {
      *(uint8_t *)(this + 1100) = 0;  // 写字段 this+1100（nFairyGrade） ← 0
      return sub_6257C0((int *)this);  // sub_6257C0 —— 掩体状态 2 演出
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x625A70 sub_625A70 —— 掩体自动开门
//    每 1000ms 至多 1 次：存活时播种后以 30% 概率经 sub_4E7F30(this,250,75) 探人；命中再按 10% 分支：
//    90% 只打包自身(1,虚 48,虚 52)，10% 逐个打包所有目标坐标，经虚 560(this,2,...) 触发开门。
// ------------------------------------------------------------
void /*thiscall*/ sub_625A70(uint32_t *this)  // sub_625A70 —— 掩体自动开门
{
  int pThis_9; // esi
  int v3; // eax
  int v4; // edx
  int pObj; // esi
  bool nRand; // bl
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

  pThis_9 = (int)(this + 9);  // this+36〔nStateWord36(推断)〕
  if ( *(this + 276) + 1000 <= (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
  {
    v3 = sub_699000(pThis_9);  // 【clock_now(clk)】
    v4 = *this;
    *(this + 276) = v3;  // 写字段 this+276（pMapEntry） ← v3
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v4 + 308))(this) != 0 )  // 虚函数调用 槽+308
    {
      sub_432FA0();  // sub_432FA0 —— srand 播种
      if ( rand() % 100 <= 30 )  // 调 取伪随机数
      {
        v9 = nullptr;
        v10 = 0;
        v11 = 0;
        v17 = 0;
        pObj = sub_4E7F30(this, 250, 75, (int)v8);  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
        if ( pObj != 0 )
        {
          nRand = rand() % 100 > 10;  // 调 取伪随机数
          Block = nullptr;
          v14 = 0;
          v15 = 0;
          LOBYTE(v17) = 1;  // 调 取 16 位值低 8 位
          if ( nRand )
          {
            v16 = 1;
            sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);  // 虚调用 vt+48（pObj）归属坐标x
            sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 虚调用 vt+52（pObj）归属坐标y
            sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
          }
          else
          {
            if ( v9 != nullptr )  // 若 v9 有效（非空）
              v16 = (v10 - (int)v9) >> 2;
            else
              v16 = 0;
            sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
            for ( i = 0; v9 != nullptr && i < (v10 - (int)v9) >> 2; ++i )
            {
              v16 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v9 + i) + 48))(*((uint32_t *)v9 + i));  // 虚函数调用 槽+48：更新槽（64A5A0 + 41C5E0/52E4D0）
              sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
              v16 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v9 + i) + 52))(*((uint32_t *)v9 + i));  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
              sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
            }
          }
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 2, v12, 0, 0);  // 虚调用 vt+560（this 虚表槽）
          if ( Block != nullptr )  // 若 Block 有效（非空）
            j__free(Block);  // 释放堆块
        }
        if ( v9 != nullptr )  // 若 v9 有效（非空）
          j__free(v9);  // 释放堆块
      }
    }
  }
}



// ------------------------------------------------------------
// 0x625C40 CNGoblinBunker__vmt2E4 —— 掩体重置 vmt2E4
//    置 +676=1、+96=545 标识、开门位与 +1104 时钟清零，重放状态 2 演出与 204(200,表+72)；new(0x12C) 由虚 672 链取串经 sub_4C3640 重建 +1108 挂件；
//    虚 372(100) 后清 +1112/+1120 列表并虚 472(6,0,1,1)。
// ------------------------------------------------------------
int /*thiscall*/ CNGoblinBunker__vmt2E4(int this)  // 函数定义: 掩体重置 vmt2E4
{
  int pThis_20; // ecx
  int pThis_16C; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // edx

  *(uint32_t *)(this + 676) = 1;  // 写字段 this+676（nResetFlag676） ← 1
  *(uint32_t *)(this + 96) = 545;  // 写字段 this+96（nStatusMode） ← 545
  *(uint8_t *)(this + 1100) = 0;  // 写字段 this+1100（nFairyGrade） ← 0
  *(uint32_t *)(this + 1104) = sub_699000(this + 36);  // sub_699000 —— 【clock_now(clk)】
  sub_6257C0((int *)this);  // sub_6257C0 —— 掩体状态 2 演出
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    200,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 72),  // this+144 帧件列表基址
    0,
    0,
    0,
    0);
  if ( operator new(0x12Cu) != nullptr )  // 堆分配
  {
    pThis_20 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 672))(this) + 32) + 24;  // 虚调用 vt+672（this）队伍编号取址
    if ( *(uint32_t *)(this + 384) < 0x10u )  // this+384 动画件名 SSO 容量判据
      pThis_16C = this + 364;  // this+364 动画件名 SSO 内联首址
    else
      pThis_16C = *(uint32_t *)(this + 364);  // 读字段 pThis_16C = this+364（pAnimNameStr）
    v4 = sub_41ACF0(pThis_20);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    v5 = sub_4C3640(pThis_16C, v4, this);  // 调 构造 +988 挂件
  }
  else
  {
    v5 = 0;
  }
  *(uint32_t *)(this + 1108) = v5;  // 写字段 this+1108（pAttach1108） ← v5
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
  if ( *(uint32_t *)(this + 1120) != 0 )  // this+1120 投掷名单缓冲
    j__free(*(void **)(this + 1120));  // 释放堆块
  *(uint32_t *)(this + 1120) = 0;  // 写字段 this+1120（pList1120） ← 0
  *(uint32_t *)(this + 1124) = 0;  // 写字段 this+1124（nListCnt1124） ← 0
  *(uint32_t *)(this + 1128) = 0;  // 写字段 this+1128（nListCap1128） ← 0
  v6 = *(uint32_t *)this;
  *(uint32_t *)(this + 1112) = 0;  // 写字段 this+1112（nTick1112） ← 0
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(v6 + 472))(this, 6, 0, 1, 1);  // 虚函数调用 槽+472：主状态机（874 行）：CONDITION_STUN/DOWN_HEAV
}



// ------------------------------------------------------------
// 0x625D70 CNGoblinBunker__vmt14C —— 掩体主 tick vmt14C
//    状态 0 走自动开门(sub_625A70)；状态 2 且存活时按开门位取表 +36/+24 动画项(148>=1)激活，则对 +1120 名单逐个 sub_6252D0 投掷再虚 560(0) 收束；
//    状态 3 于目标倒地时同样虚 560(0)。
// ------------------------------------------------------------
void /*thiscall*/ CNGoblinBunker__vmt14C(uint32_t *this)  // 函数定义: 掩体主 tick vmt14C
{
  int fld_e240; // eax
  int v3; // eax
  char pFrameList144; // cl  | +0x0090 → 帧件列表基址（625C40 取 *(+144)+72 作帧表项）（证据 va=00625C40）（CNGoblinBunker；va=00625C40）
  int i; // edi
  int fld_e29; // eax

  fld_e240 = *(this + 240);  // 读字段 fld_e240 = this+240（nSyncArgB）
  if ( fld_e240 != 0 )
  {
    v3 = fld_e240 - 2;  // 计算 v3 = fld_e240 - 2
    if ( v3 != 0 )
    {
      if ( v3 == 1
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308（this）是否本地玩家
        && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0 )  // 虚调用 vt+200（this）取值比较
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
      }
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308（this）是否本地玩家
           && ((pFrameList144 = *((uint8_t *)this + 1100)) == 1 && *(int *)(*(uint32_t *)(*(this + 36) + 36) + 148) >= 1  // this+1100 开门位
            || pFrameList144 == 0 && *(int *)(*(uint32_t *)(*(this + 36) + 24) + 148) >= 1) )  // this+36 物品状态字
    {
      for ( i = 0; i < *(this + 278); ++i )  // this+1112〔nThrowTick1112〕
      {
        fld_e29 = sub_45EBE0(  // sub_45EBE0 —— 存 id 对 → 对象查找
               (uint32_t *)*(this + 29),  // this+116〔会话上下文〕
               *(uint32_t *)(*(this + 280) + 8 * i),  // this+280 地图条目数组 end
               *(uint32_t *)(*(this + 280) + 8 * i + 4));  // this+280 地图条目数组 end
        sub_6252D0(this, (int)this, fld_e29);  // 调 投掷再虚 560(0) 收束
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
    }
  }
  else
  {
    sub_625A70(this);  // sub_625A70 —— 掩体自动开门
  }
}



// ------------------------------------------------------------
// 0x625E70 sub_625E70
//   【掩体】Common/CommonEffect/Animation/Heal.ani —— 掩体医疗治疗演出
// ------------------------------------------------------------
int /*thiscall*/ sub_625E70(int *this)  // 实现：(掩体)Common/CommonEffect/Animation/Heal.ani —— 掩体医疗治疗演出
{
  int v2; // edi
  int v3; // edx
  int fld_e170; // ebx
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
  int fld_e171; // [esp+1Ch] [ebp-10h]
  int v24; // [esp+28h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    fld_e171 = *(this + 171);  // 读字段 fld_e171 = this+171
    v2 = (uint64_t)((double)fld_e171 * 0.2);
    Block = nullptr;
    v21 = 0;
    v22 = 0;
    v3 = *this;
    fld_e170 = *(this + 170);  // 读字段 fld_e170 = this+170
    v24 = 0;
    fld_e171 = (*(int (/*thiscall*/ **)(int *))(v3 + 192))(this);  // 虚函数调用 槽+192
    v5 = (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(*this + 124))(  // 虚调用 vt+124（this）目标坐标y下界
           this,
           (uint64_t)((double)fld_e171 * 0.75) >> 32,
           (uint64_t)((double)fld_e171 * 0.75));
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);  // 虚调用 vt+120（this）转发(对象+缓冲)
    v16 = v2 + fld_e170;  // 计算 v16 = v2 + fld_e170
    v7 = 0;
    sub_600920((int)v19, 0, v2, v16, v6, v17, v18);
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *))(*this + 560))(this, 1, v19);  // 虚调用 vt+560（this 虚表槽）
    v24 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
    Block = nullptr;
    v21 = 0;
    v22 = 0;
  }
  else
  {
    v7 = 0;
  }
  v8 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
  fld_e171 = v8;
  v24 = 1;
  if ( v8 != 0 )
    v7 = sub_431860(v8, "Common/CommonEffect/Animation/Heal.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
  v24 = -1;
  v9 = (char *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  v10 = v9;
  fld_e171 = (int)v9;
  v24 = 2;
  if ( v9 != nullptr )  // 若 v9 有效（非空）
  {
    sub_44E0D0(v9, v7, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v10 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    v10 = nullptr;
  }
  v11 = *(uint32_t *)v10;
  v24 = -1;
  (*(void (/*thiscall*/ **)(char *, int))(v11 + 72))(v10, 2);  // 虚函数调用 槽+72：槽（4BE520/4F2D40 + 4848
  sub_45FE80(*(this + 29), (int)v10, 2, 0, (int)v10, (int)this, 0);  // sub_45FE80 —— 对象注册
  v12 = *(uint32_t *)v10;
  v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, 40);  // 虚调用 vt+124（this）目标坐标y下界
  v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13 + 1);  // 虚调用 vt+120（this）转发(对象+缓冲)
  return (*(int (/*thiscall*/ **)(char *, int))(v12 + 112))(v10, v14);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
}



// ------------------------------------------------------------
// 0x625FF0 CNGoblinBunker__vmt1D8
//   【掩体】BUNKER_OPEN —— 掩体开门
// ------------------------------------------------------------
int /*thiscall*/ CNGoblinBunker__vmt1D8(int this, int nArg2, int pArg3, int nArg4, int nArg5)  // 实现：(掩体)BUNKER_OPEN —— 掩体开门
{
  int result; // eax
  int v7; // edi
  int v8; // ecx
  int v9; // eax

  result = CNRDPassiveObject__vmt1D8((uint32_t *)this, nArg2, pArg3, nArg2, pArg3, nArg4, nArg5);  // result = 调 CNRDPassiveObject__vmt1D8
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 0:  // case 0 分派（哥布林掩体（CNGoblinBunker，0x625200-0x626220））
      result = sub_6257C0((int *)this);  // sub_6257C0 —— 掩体状态 2 演出
      break;
    case 2:  // case 2 分派（哥布林掩体（CNGoblinBunker，0x625200-0x626220））
      sub_625890((int *)this);  // sub_625890 —— 掩体 BUNKER_OPEN 演出
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
        this,
        "BUNKER_OPEN",  // 资源/动画 TAG BUNKER_OPEN
        -1,
        0,
        0);
      sub_5E5260((void **)(this + 1116));  // 调 动画子对象清理临时缓冲
      *(uint32_t *)(this + 1112) = 0;  // 写字段 this+1112（nTick1112） ← 0
      result = **(uint32_t **)(pArg3 + 4);  // pArg3+4〔宿主对象〕
      v7 = 0;
      for ( *(uint32_t *)(this + 1112) = result; v7 < result; ++v7 )  // this+1112 投掷节拍计数
      {
        v8 = *(uint32_t *)(pArg3 + 4);  // 读字段 v8 = pArg3+4（pHostObj）
        v9 = *(uint32_t *)(v8 + 8 * v7 + 8);
        nArg5 = *(uint32_t *)(v8 + 8 * v7 + 4);
        nArg4 = v9;
        sub_431230(this + 1116, &nArg5);  // sub_431230 —— uint32 vector push_back
        sub_431230(this + 1116, &nArg4);  // sub_431230 —— uint32 vector push_back
        result = *(uint32_t *)(this + 1112);  // 读字段 result = this+1112（nTick1112）
      }
      break;
    case 3:  // case 3 分派（哥布林掩体（CNGoblinBunker，0x625200-0x626220））
      result = sub_6256F0((int *)this);  // sub_6256F0 —— 掩体状态 3 演出
      break;
    case 4:  // case 4 分派（哥布林掩体（CNGoblinBunker，0x625200-0x626220））
      sub_625E70((int *)this);
      result = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);  // 虚调用 vt+472（this 虚表槽）
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x626100 sub_626100 —— 踏台随机摆动
//     +988 踩踏者存活时播种：虚 896 随机定朝向，虚 876 以 250~750 随机量对自身 6608/6612 与 6616/6620 坐标字段施加 -1000 Z 的位移冲击，并置 +992 活动标志。
// ------------------------------------------------------------
int /*thiscall*/ sub_626100(int this)  // sub_626100 —— 踏台随机摆动
{
  int result; // eax
  int nRand; // esi
  int nRand2; // eax
  int nRand3; // esi
  int nRand4; // eax
  uint32_t *fld_3DC; // ecx
  int v8; // ebx
  int v9; // [esp+4h] [ebp-8h]
  int v10; // [esp+8h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 988) + 308))(*(uint32_t *)(this + 988));  // this+988 【推断】状态/配置表项 A
  if ( (uint8_t)result != 0 )
  {
    sub_432FA0();  // sub_432FA0 —— srand 播种
    nRand = rand() % 2;  // 调 取伪随机数
    nRand2 = rand() % 2;  // 调 取伪随机数
    (*(void (/*thiscall*/ **)(uint32_t, bool, int))(**(uint32_t **)(this + 988) + 896))(  // this+988 【推断】状态/配置表项 A
      *(uint32_t *)(this + 988),  // this+988 【推断】状态/配置表项 A
      nRand == 0,
      3 - (nRand2 != 0));
    nRand3 = rand() % 500 + 250;  // 调 取伪随机数
    nRand4 = rand();  // 调 取伪随机数
    fld_3DC = *(uint32_t **)(this + 988);  // this+988 【推断】状态/配置表项 A
    v10 = fld_3DC[1655];
    v9 = fld_3DC[1653];
    v8 = nRand4 % 500 + 250;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*fld_3DC + 876))(  // 虚调用 vt+876（fld_3DC）双段位移
      fld_3DC,
      0,
      nRand3 + fld_3DC[1652],
      nRand3 + fld_3DC[1654],
      0,
      -1000,
      1);
    result = (*(int (/*thiscall*/ **)(uint32_t, int, int, int, uint32_t, int, int))(**(uint32_t **)(this + 988) + 876))(  // this+988 【推断】状态/配置表项 A
               *(uint32_t *)(this + 988),  // this+988 【推断】状态/配置表项 A
               1,
               v8 + v9,
               v8 + v10,
               0,
               -1000,
               1);
  }
  *(uint32_t *)(this + 992) = *(uint32_t *)(this + 988);  // 写字段 this+992（uCfgB992） ← *(uint32_t *)(this + 988)
  return result;
}



// ------------------------------------------------------------
// 0x626220 sub_626220 —— 踏台状态复位
//    清 +972..+996 的状态与引用，坐标对 +680:+684 重置为 +348 表首项，虚 372(200) 收尾。
// ------------------------------------------------------------
int /*thiscall*/ sub_626220(uint32_t *this)  // sub_626220 —— 踏台状态复位
{
  int fld_e87; // eax

  *(this + 247) = 0;  // 写字段 this+247 ← 0
  *(this + 248) = 0;  // 写字段 this+248（bParamSlotA） ← 0
  *((uint8_t *)this + 972) = 0;  // 写字段 this+972（uCfgD972）
  *((uint8_t *)this + 973) = 0;  // 写字段 this+973（bLanded973）
  *(this + 249) = 0;  // 写字段 this+249 ← 0
  *(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
  *(this + 245) = 0;  // 写字段 this+245 ← 0
  *(this + 246) = 0;  // 写字段 this+246 ← 0
  *((uint8_t *)this + 974) = 0;  // 写字段 this+974（bLatch974）
  fld_e87 = *(uint32_t *)*(this + 87);  // this+348〔pParamTbl348〕
  *(this + 170) = fld_e87;  // 写字段 this+170 ← fld_e87
  *(this + 171) = fld_e87;  // 写字段 this+171 ← fld_e87
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 200);  // 虚调用 vt+372（this）数值写入
}



// ============================================================
// 【分区 9】植物系：绞藤/扭草踏台/海草（0x626280-0x627900）
// 证据: TWIST_AMB_LOOP / TWIST_SPIN（扭草踏台）、BURN_VINE（点燃）/ TIE_VINE（缠绕定身）/
//       WALK_VINE_LOOP（藤上行走）+ BreakableObject/Particle/SeaGrassBubble.ptl（海草气泡）
// ============================================================

// ------------------------------------------------------------
// 0x626280 CNTwistFootHold__vmt2B4 —— 踏台受击耗尽 vmt2B4
//     +680 血量 ≤0 且 +974 未触发时一次性置位：取 +144 表偏移 24 的对象施以虚 196 重设，并虚 596/604(this,0) 停用停摆。
// ------------------------------------------------------------
char /*thiscall*/ CNTwistFootHold__vmt2B4(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 踏台受击耗尽 vmt2B4
{
  int fld_e170; // eax  | +0x02A8 → 表现/名字快照[0]（4E1FE0 由 28 字节源块直拷）（证据 va=004E1FE0）（CNTwistFootHold；va=004E1FE0）
  int pFrameList144; // eax  | +0x0090 → 帧件列表基址（626770：*(*(+144)+24) 作帧表项）（证据 va=00626770）（CNTwistFootHold；va=00626770）
  int v9; // edx

  fld_e170 = *(this + 170);  // 读字段 fld_e170 = this+170
  if ( fld_e170 <= 0 )
  {
    LOBYTE(fld_e170) = *((uint8_t *)this + 974);  // this+974 一次性锁存位 2
    if ( (uint8_t)fld_e170 == 0 )
    {
      pFrameList144 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
      v9 = *this;
      *((uint8_t *)this + 974) = 1;  // 写字段 this+974（bLatch974）
      (*(void (/*stdcall*/ **)(uint32_t))(v9 + 196))(*(uint32_t *)(pFrameList144 + 24));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);  // 虚调用 vt+596（this 虚表槽）
      LOBYTE(fld_e170) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);  // 虚调用 vt+604（this）收招例程
    }
  }
  return fld_e170;  // +0x02A8 → 表现/名字快照[0]（4E1FE0 由 28 字节源块直拷）（证据 va=004E1FE0）（CNTwistFootHold；va=004E1FE0）
}



// ------------------------------------------------------------
// 0x6262D0 sub_6262D0 —— 【扭草踏台】踩踏者绑定与五站位吸附
//    记目标(+988)、起止时刻(+976/+980) 并置绑定标志(+972)；对目标虚 596/604(0) 停用其动作，
//    再按目标高度(虚 192) 取 -0.7/-0.4/-0.1 三档比例，配 ±9999 两侧共六次虚 204，逐项吃帧表(+144) [0..5] 排定站位。
// ------------------------------------------------------------
int /*thiscall*/ sub_6262D0(uint32_t *this, int nArg2)  // sub_6262D0 —— 【扭草踏台】踩踏者绑定与五站位吸附
{
  int pThis_9; // edi
  int v4; // eax
  int v5; // edx
  int fld_e247; // edi
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int *fld_e2472; // edi
  int v11; // ebx
  uint64_t v12; // rax
  int *fld_e2473; // edi
  int v14; // ebx
  uint64_t v15; // rax
  int *fld_e2474; // edi
  int v17; // ebx
  uint64_t v18; // rax
  int *fld_e2475; // edi
  int v20; // ebx
  uint64_t v21; // rax
  int *fld_e2476; // edi
  int v23; // ebx
  uint64_t v24; // rax
  int fld_e366; // edi
  int *fld_e2477; // esi
  int v27; // ebx
  uint64_t v28; // rax
  uint32_t *fld_e36; // [esp+Ch] [ebp-4h]
  uint32_t *fld_e362; // [esp+Ch] [ebp-4h]
  uint32_t *fld_e363; // [esp+Ch] [ebp-4h]
  uint32_t *fld_e364; // [esp+Ch] [ebp-4h]
  uint32_t *fld_e365; // [esp+Ch] [ebp-4h]

  pThis_9 = (int)(this + 9);  // this+36〔nStateWord36(推断)〕
  *(this + 247) = nArg2;  // 写字段 this+247 ← nArg2
  *(this + 244) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  v4 = sub_699000(pThis_9);  // 【clock_now(clk)】
  v5 = *this;
  *(this + 245) = v4;  // 写字段 this+245 ← v4
  *((uint8_t *)this + 972) = 1;  // 写字段 this+972（uCfgD972）
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v5 + 596))(this, 0);  // 虚函数调用 槽+596：[RTTI: IRDCollisionObject__vmt254…
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 604))(this, 0);  // 虚调用 vt+604（this）收招例程
  fld_e247 = *(uint32_t *)*(this + 247);  // this+988〔uCfgA988(推断)〕
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);  // 虚调用 vt+124（this）目标坐标y下界
  v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);  // 虚调用 vt+120（this）转发(对象+缓冲)
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e247 + 112))(*(this + 247), v9);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  fld_e2472 = (int *)*(this + 247);  // this+988〔uCfgA988(推断)〕
  v11 = *fld_e2472;
  fld_e36 = (uint32_t *)*(this + 36);  // this+36 物品状态字
  v12 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*fld_e2472 + 192))(fld_e2472, 0, 0) * -0.69999999);  // 虚调用 vt+192（fld_e2472）取尺寸/包围盒
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v11 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
    fld_e2472,
    HIDWORD(v12),  // 调 取 64 位值高 32 位
    -9999,
    *fld_e36,
    0,
    v12);
  fld_e2473 = (int *)*(this + 247);  // this+988〔uCfgA988(推断)〕
  v14 = *fld_e2473;
  fld_e362 = (uint32_t *)(*(this + 36) + 4);  // this+36 物品状态字
  v15 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*fld_e2473 + 192))(fld_e2473, 0, 0) * -0.69999999);  // 虚调用 vt+192（fld_e2473）取尺寸/包围盒
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v14 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
    fld_e2473,
    HIDWORD(v15),  // 调 取 64 位值高 32 位
    9999,
    *fld_e362,
    0,
    v15);
  fld_e2474 = (int *)*(this + 247);  // this+988〔uCfgA988(推断)〕
  v17 = *fld_e2474;
  fld_e363 = (uint32_t *)(*(this + 36) + 8);  // this+36 物品状态字
  v18 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*fld_e2474 + 192))(fld_e2474, 0, 0) * -0.40000001);  // 虚调用 vt+192（fld_e2474）取尺寸/包围盒
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v17 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
    fld_e2474,
    HIDWORD(v18),  // 调 取 64 位值高 32 位
    -9999,
    *fld_e363,
    0,
    v18);
  fld_e2475 = (int *)*(this + 247);  // this+988〔uCfgA988(推断)〕
  v20 = *fld_e2475;
  fld_e364 = (uint32_t *)(*(this + 36) + 12);  // this+36 物品状态字
  v21 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*fld_e2475 + 192))(fld_e2475, 0, 0) * -0.40000001);  // 虚调用 vt+192（fld_e2475）取尺寸/包围盒
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v20 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
    fld_e2475,
    HIDWORD(v21),  // 调 取 64 位值高 32 位
    9999,
    *fld_e364,
    0,
    v21);
  fld_e2476 = (int *)*(this + 247);  // this+988〔uCfgA988(推断)〕
  v23 = *fld_e2476;
  fld_e365 = (uint32_t *)(*(this + 36) + 16);  // this+36 物品状态字
  v24 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*fld_e2476 + 192))(fld_e2476, 0, 0) * -0.1);  // 虚调用 vt+192（fld_e2476）取尺寸/包围盒
  (*(void (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v23 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
    fld_e2476,
    HIDWORD(v24),  // 调 取 64 位值高 32 位
    -9999,
    *fld_e365,
    0,
    v24);
  fld_e366 = *(this + 36);  // 读字段 fld_e366 = this+36（nStateWord36）
  fld_e2477 = (int *)*(this + 247);  // this+988〔uCfgA988(推断)〕
  v27 = *fld_e2477;
  v28 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t))(*fld_e2477 + 192))(fld_e2477, 0, 0) * -0.1);  // 虚调用 vt+192（fld_e2477）取尺寸/包围盒
  return (*(int (/*fastcall*/ **)(int *, uint32_t, int, uint32_t, uint32_t, uint32_t))(v27 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
           fld_e2477,
           HIDWORD(v28),  // 调 取 64 位值高 32 位
           9999,
           *(uint32_t *)(fld_e366 + 20),
           0,
           v28);
}


// ------------------------------------------------------------
// 0x626500 sub_626500 —— 踩踏者解绑与计数收尾
//    先虚 196 应用帧表[6]，再对表[0..5] 六站位逐一经目标虚 208 摘除挂点；清 +988/+976 与标志(+972)并刷新 +984 时刻；
//    累计次数(+996)<5 走虚 604(1) 继续，否则置 +974 一次性标志并虚 604(0) 结束（与 sub_6262D0 成对）。
// ------------------------------------------------------------
int /*thiscall*/ sub_626500(uint32_t *this)  // sub_626500 —— 踩踏者解绑与计数收尾
{
  bool fld_e249; // cc
  int v3; // edx

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 24));  // 虚调用 vt+196（this）物件非空判定
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(*(this + 247), *(uint32_t *)*(this + 36));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    *(this + 247),  // this+988〔uCfgA988(推断)〕
    *(uint32_t *)(*(this + 36) + 4));  // this+36 物品状态字
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    *(this + 247),  // this+988〔uCfgA988(推断)〕
    *(uint32_t *)(*(this + 36) + 8));  // this+36 物品状态字
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    *(this + 247),  // this+988〔uCfgA988(推断)〕
    *(uint32_t *)(*(this + 36) + 12));  // this+36 物品状态字
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    *(this + 247),  // this+988〔uCfgA988(推断)〕
    *(uint32_t *)(*(this + 36) + 16));  // this+36 物品状态字
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 247) + 208))(  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    *(this + 247),  // this+988〔uCfgA988(推断)〕
    *(uint32_t *)(*(this + 36) + 20));  // this+36 物品状态字
  *(this + 247) = 0;  // 写字段 this+247 ← 0
  *(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
  *(this + 246) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  fld_e249 = *(this + 249) < 5;  // this+996〔bCfgC996(推断)〕
  *(this + 245) = 0;  // 写字段 this+245 ← 0
  *((uint8_t *)this + 972) = 0;  // 写字段 this+972（uCfgD972）
  if ( fld_e249 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 604))(this, 1);  // 虚调用 vt+604（this）收招例程
  v3 = *this;
  *((uint8_t *)this + 974) = 1;  // 写字段 this+974（bLatch974）
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 604))(this, 0);  // 虚函数调用 槽+604：受击盒使能 setter（+641）+ 附属物 vt+604 广播
}



// ------------------------------------------------------------
// 0x626610 IRDCollisionObject__vmt168 —— 敌我关系判定（vmt168 槽覆写，研究已定案）
//    双方各经虚 380 取宿主：同宿主时直接比对自身 +136 与对方经 sub_4BE520(lower_bound) 查表的结果；
//    异宿主时改走宿主虚 360 重判。
// ------------------------------------------------------------
int /*thiscall*/ IRDCollisionObject__vmt168(uint32_t *this, int nArg2)  // 函数定义: 敌我关系判定
{
  int *v3; // esi
  int v4; // edi
  int v5; // eax
  uint8_t v7[4]; // [esp+4h] [ebp-4h] BYREF

  if ( (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 380))(this) == this )  // 虚调用 vt+380（this）判定体获取
  {
    nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 380))(nArg2);  // 虚调用 vt+380（nArg2）判定体获取
    return *(uint32_t *)sub_4BE520(v7, &nArg2) != *(this + 136);  // sub_4BE520 —— 结果 = 映射下界查找（lower_bound）
  }
  else
  {
    v3 = (int *)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 380))(this);  // 虚调用 vt+380（this）判定体获取
    v4 = *v3;
    v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 380))(nArg2);  // 虚调用 vt+380（nArg2）判定体获取
    return (*(int (/*thiscall*/ **)(int *, int))(v4 + 360))(v3, v5);  // 虚函数调用 槽+360：敌我关系判定（vmt168 槽覆写，研究已定案）
  }
}



// ------------------------------------------------------------
// 0x626690 CNTwistFootHold__vmt12C —— 注销解引用（基类后）
//    +988 命中则走 sub_626500 解绑；+992 命中则清零；nArg2 为自身时虚 216 停 7810 号 TAG（TWIST_AMB_LOOP 循环音）。
// ------------------------------------------------------------
void /*thiscall*/ CNTwistFootHold__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 注销解引用
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( *(this + 247) == nArg2 )  // this+988〔pFrameObj988〕
    sub_626500(this);  // sub_626500 —— 踩踏者解绑与计数收尾
  if ( *(this + 248) == nArg2 )  // this+248 自身对象 id 槽
    *(this + 248) = 0;  // 写字段 this+248（bParamSlotA） ← 0
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 7810);  // 虚调用 vt+216（this）全场广播
}



// ------------------------------------------------------------
// 0x6266E0 CNTwistFootHold__vmt1F4 —— 踩踏判定（vmt1F4 碰撞族）
//    来客类别(虚 40)为 17 且非霸体(ハイパーアーマー，虚 724=0)、其状态(虚 840)不为 9/4 时：累计次数(+996)自增，
//    经虚 472 施加状态 9 后走 sub_6262D0 捕获站位。
// ------------------------------------------------------------
int /*thiscall*/ CNTwistFootHold__vmt1F4(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 函数定义: 踩踏判定
{
  if ( *(this + 247) != 0 )  // this+988〔pFrameObj988〕
    return 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0  // 虚调用 vt+40（nArg2）条件查询(273等)
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 724))(nArg2) == 0  // 虚调用 vt+724（nArg2）取值
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 840))(nArg2) != 9  // 虚调用 vt+840（nArg2 虚表槽）
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 840))(nArg2) != 4 )  // 虚调用 vt+840（nArg2 虚表槽）
  {
    ++*(this + 249);  // this+996〔bCfgC996(推断)〕
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int, int))(*(uint32_t *)nArg2 + 472))(nArg2, 9, 0, 1, 1);  // 虚调用 vt+472（nArg2 虚表槽）
    sub_6262D0(this, nArg2);  // sub_6262D0 —— 【扭草踏台】踩踏者绑定与五站位吸附
  }
  return 0;
}



// ------------------------------------------------------------
// 0x626770 CNTwistFootHold__vmt14C
//   【扭草踏台】TWIST_AMB_LOOP（环境循环）/ TWIST_SPIN（旋转）
// ------------------------------------------------------------
char /*thiscall*/ CNTwistFootHold__vmt14C(int this)  // 函数定义: 位置采样
{
  int pFrameObj988; // edi  | +0x03DC → 当前帧件对象（626770 取 *(+988)；对帧件 vt+760 调用）（证据 va=00626770）（CNTwistFootHold；va=00626770）
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int *pFrameObj988_; // ecx
  int v7; // edi
  int v8; // eax
  int pThis_24; // eax
  int pFrameObj988_2; // ecx  | +0x03DC → 当前帧件对象（626770 取 *(+988)；对帧件 vt+760 调用）（证据 va=00626770）（CNTwistFootHold；va=00626770）
  unsigned int pThis_C8; // eax
  int nClockCtx992; // ecx  | +0x03E0 → 时钟/帧件上下文（626770 判 *(+992)!=0 分流）【推断】（证据 va=00626770）（CNTwistFootHold；va=00626770）
  int v13; // eax
  uint32_t *fld_90; // edi

  CNRDPassiveObject__vmt14C(this);
  if ( *(uint8_t *)(this + 973) == 0 )  // this+973 一次性锁存位
  {
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
      this,
      "TWIST_AMB_LOOP",  // 资源/动画 TAG TWIST_AMB_LOOP
      7810,
      0,
      0);
    *(uint8_t *)(this + 973) = 1;  // 写字段 this+973（bLanded973） ← 1
  }
  if ( *(uint8_t *)(this + 972) == 0 )  // this+972 激活位
    goto LABEL_12;
  pFrameObj988 = **(uint32_t **)(this + 988);  // this+988 当前帧件对象
  pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
  pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_80);  // 虚调用 vt+124（this）目标坐标y下界
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);  // 虚调用 vt+120（this）转发(对象+缓冲)
  (*(void (/*thiscall*/ **)(uint32_t, int))(pFrameObj988 + 112))(*(uint32_t *)(this + 988), pThis_78);  // this+988 当前帧件对象
  if ( *(uint32_t *)(this + 980) + 100 < (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
  {
    pFrameObj988_ = *(int **)(this + 988);  // this+988 当前帧件对象
    v7 = *pFrameObj988_;
    v8 = (*(int (/*thiscall*/ **)(int *))(*pFrameObj988_ + 152))(pFrameObj988_);  // 虚调用 vt+152（fld_3DC2）取值(参数)
    (*(void (/*thiscall*/ **)(uint32_t, bool))(v7 + 148))(*(uint32_t *)(this + 988), v8 == 0);  // this+988 当前帧件对象
    pThis_24 = sub_699000(this + 36);  // 【clock_now(clk)】
    pFrameObj988_2 = *(uint32_t *)(this + 988);  // 读字段 fld_3DC3 = this+988（uCfgA988）
    *(uint32_t *)(this + 980) = pThis_24;  // 写字段 this+980（uCfgF980） ← pThis_24
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pFrameObj988_2 + 152))(pFrameObj988_2) == 0 )  // 虚调用 vt+152（fld_3DC3）取值(参数)
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
        this,
        "TWIST_SPIN",  // 资源/动画 TAG TWIST_SPIN
        -1,
        0,
        0);
  }
  if ( ((*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 988) + 840))(*(uint32_t *)(this + 988)) == 9  // this+988 当前帧件对象
     || *(uint32_t *)(this + 992) != 0)  // this+992 时钟/帧件上下文
    && (*(uint32_t *)(this + 976) + 2000 >= (unsigned int)sub_699000(this + 36) || *(uint32_t *)(this + 992) != 0) )  // 【clock_now(clk)】
  {
LABEL_12:
    nClockCtx992 = *(uint32_t *)(this + 992);  // 读字段 fld_3E0 = this+992（uCfgB992）
    if ( nClockCtx992 != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nClockCtx992 + 184))(nClockCtx992) == 4  // 虚调用 vt+184（nClockCtx992）字符串/朝向写入
      && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 992) + 188))(*(uint32_t *)(this + 992)) == 4 )  // this+992 时钟/帧件上下文
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 992) + 308))(*(uint32_t *)(this + 992)) != 0  // this+992 时钟/帧件上下文
        && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 992) + 724))(*(uint32_t *)(this + 992)) == 0  // this+992 时钟/帧件上下文
        && (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 992) + 840))(*(uint32_t *)(this + 992)) == 9 )  // this+992 时钟/帧件上下文
      {
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(**(uint32_t **)(this + 992) + 560))(  // this+992 时钟/帧件上下文
          *(uint32_t *)(this + 992),  // this+992 时钟/帧件上下文
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int, uint32_t))(**(uint32_t **)(this + 992) + 760))(  // this+992 时钟/帧件上下文
          *(uint32_t *)(this + 992),  // this+992 时钟/帧件上下文
          15,
          1106247680,  // 浮点常量 30.0f
          10,
          this,
          0);
      }
      v13 = *(uint32_t *)this;
      *(uint32_t *)(this + 992) = 0;  // 写字段 this+992（uCfgB992） ← 0
      (*(void (/*thiscall*/ **)(int))(v13 + 352))(this);  // 虚函数调用 槽+352：命中列表双链表清空
    }
    fld_90 = (uint32_t *)(*(uint32_t *)(this + 144) + 24);  // this+144 帧件列表基址
    pThis_C8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 虚调用 vt+200（this）取值比较
    if ( pThis_C8 == *fld_90 )
    {
      LOBYTE(pThis_C8) = *(uint8_t *)(this + 974);  // this+974 一次性锁存位 2
      if ( (uint8_t)pThis_C8 == 0 )
      {
        pThis_C8 = sub_699000(this + 36);  // 【clock_now(clk)】
        if ( *(uint32_t *)(this + 984) + 5000 < pThis_C8 )  // this+984 截止时刻槽
        {
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(this + 136));  // 虚调用 vt+196（this）物件非空判定
          LOBYTE(pThis_C8) = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 596))(this, 1);  // 虚调用 vt+596（this 虚表槽）
        }
      }
    }
  }
  else
  {
    sub_626100(this);  // sub_626100 —— 踏台随机摆动
    LOBYTE(pThis_C8) = sub_626500((uint32_t *)this);  // sub_626500 —— 踩踏者解绑与计数收尾
  }
  return pThis_C8;
}



// ------------------------------------------------------------
// 0x6269A0 sub_6269A0 —— 释放两枚子件
//    对 +976/+980 两枚句柄各走虚 0 析构(参数 1) 并清零（句柄回收样板，同 sub_629010 一族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_6269A0(uint32_t *this)  // sub_6269A0 —— 释放两枚子件
{
  int (/*thiscall*/ ***fld_e244)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e245)(uint32_t, int); // ecx

  fld_e244 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 244);  // this+244 动画同步浮点参数
  if ( fld_e244 != nullptr )  // 若 fld_e244 有效（非空）
    result = (**fld_e244)(fld_e244, 1);  // 调 fld_e244 的虚函数（vt+0）
  fld_e245 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 245);  // this+980〔uCfgF980(推断)〕
  *(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
  if ( fld_e245 != nullptr )  // 若 fld_e245 有效（非空）
    result = (**fld_e245)(fld_e245, 1);  // 调 fld_e245 的虚函数（vt+0）
  *(this + 245) = 0;  // 写字段 this+245 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x6269E0 CNSeaGrass__vmt288 —— 速率槽覆写（vmt288；同族槽实测置 *a1=100）
//    取 nArg2 的虚 348 属性块，其 +128 无效标志为 0 时返回 3（【推断】不可用），否则回填 *uArg1=100 并返回 0。
// ------------------------------------------------------------
int /*stdcall*/ CNSeaGrass__vmt288(uint32_t *uArg1, int nArg2)  // 函数定义: 速率槽覆写
{
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 虚调用 vt+348（nArg2）渲染数据块指针
  if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 128) == 0 )  // 虚调用 vt+348（nArg2）渲染数据块指针
    return 3;
  *uArg1 = 100;
  return 0;
}



// ------------------------------------------------------------
// 0x626A20 CNSeaGrass__vmt200 —— 【海草】受击阶段推进与反击 vmt200
//    阶段(+972)自增后经虚 196 应用帧表(+144) 第 i 项(旧阶段值)；新阶段<3 时虚 208 应用表[新+2]、虚 204(100, 表[新+3])，新阶段==3 时置 +96=33 并仅虚 208 应用表[5]，
//    再以虚 212 播 +712 句柄名。来客为 529 类且 RTTI 认作 CNSpaceFishHead(空骨鱼头部) 时：以其虚 740 取值×0.25 造 CNChangeHp(sub_4D6810) 经虚 56 附着并 sub_4DB130(24) 播表现；
//    否则把 +976 件按虚 120/124/128 定位后经 sub_4600B0 播演；末尾统一走基类 sub_600AF0。
// ------------------------------------------------------------
int /*userpurge*/ sub_626A20@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4, int nArg5, int nArg6)  // 实现：(海草)受击阶段推进与反击 vmt200
{
  int pObj; // eax
  uint32_t *v9; // edi
  uint8_t *pMem; // eax
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
  int pObj2; // eax
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
  void *pMem2; // [esp+40h] [ebp-14h]
  int v40; // [esp+44h] [ebp-10h]
  int v41; // [esp+50h] [ebp-4h]

  if ( pArg1[243] == 3 )
    return sub_600AF0(nArg4, nArg5, nArg6);  // 【CNRDPassiveObject__vmt200】
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)nArg4 + 40))(nArg4, 529, nArg3, nArg2) != 0  // 虚调用 vt+40（nArg4）条件查询(273等)
    && (pObj = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
               nArg4,
               0,
               &IRDCollisionObject `RTTI Type Descriptor',
               &CNSpaceFishHead `RTTI Type Descriptor',
               0),
        v9 = (uint32_t *)pObj,
        pObj != 0) )
  {
    v40 = (uint64_t)((double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 740))(pObj) * 0.25);  // 虚调用 vt+740（pObj 虚表槽）
    pMem = operator new(0x80u);  // 堆分配
    pMem2 = pMem;
    v41 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      *(float *)&v32 = (float)v40;
      v11 = sub_4D6810(pMem, v32, 250, 1, 1);  // sub_4D6810 —— 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
    }
    else
    {
      v11 = nullptr;
    }
    v12 = *(uint32_t *)v11;
    v41 = -1;
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v12 + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
      v11,
      v9,
      pArg1,
      0,
      0,
      0,
      -1);
    nullsub_3();  // 空桩函数（无操作）
    sub_4DB130(v9, 24, 0);  // sub_4DB130 —— 随机文案/语音触发（淘汰·胜负表现族，见 0x4DA980 头注）
  }
  else
  {
    v13 = (int *)pArg1[244];
    if ( v13 != nullptr )  // 若 v13 有效（非空）
    {
      v14 = *v13;
      v15 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, 60);  // 虚调用 vt+124（pArg1）目标坐标y下界
      v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v15);  // 虚调用 vt+120（pArg1）转发(对象+缓冲)
      (*(void (/*thiscall*/ **)(uint32_t, int))(v14 + 40))(pArg1[244], v16);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[244] + 12))(pArg1[244], 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)pArg1[244] + 92))(pArg1[244], v33);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
      v17 = (void *)pArg1[29];
      v41 = 1;
      sub_4600B0(v17, 2, 0, (int)v33);  // sub_4600B0 —— 演播层注册(槽号)
      v41 = -1;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 释放堆块
    }
  }
  v18 = pArg1[243];
  v19 = pArg1[36];
  pArg1[243] = v18 + 1;
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(v19 + 4 * v18));  // 虚调用 vt+196（pArg1）物件非空判定
  v20 = pArg1[243];
  v21 = *pArg1;
  if ( v20 == 3 )
  {
    v22 = pArg1[36];
    pArg1[24] = 33;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v21 + 208))(pArg1, *(uint32_t *)(v22 + 20));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v21 + 208))(pArg1, *(uint32_t *)(pArg1[36] + 4 * v20 + 8));  // 虚函数调用 槽+208：定时器移除（链表摘除 + 释放）
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 204))(  // 虚调用 vt+204（pArg1 虚表槽）
      pArg1,
      100,
      *(uint32_t *)(pArg1[36] + 4 * (pArg1[243] + 3)),
      0,
      0,
      0,
      0);
  }
  v23 = *pArg1;
  v24 = sub_41ACF0((unsigned int **)(pArg1[178] + 4));  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  (*(void (/*thiscall*/ **)(uint32_t *, const CHAR *, int))(v23 + 212))(pArg1, v24, -1);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
  if ( pArg1[245] != 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*pArg1 + 684))(pArg1, 0, 0) != 0 )  // 虚调用 vt+684（pArg1 虚表槽）
    {
      pObj2 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 684))(pArg1);  // 虚调用 vt+684（pArg1 虚表槽）
      v40 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 192))(pObj2);  // 虚调用 vt+192（pObj2）取尺寸/包围盒
      v26 = *pArg1;
      *(float *)&pMem2 = (double)v40 * 0.5;
      v40 = (*(int (/*thiscall*/ **)(uint32_t *))(v26 + 128))(pArg1);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
      v27 = (double)v40 + *(float *)&pMem2;
    }
    else
    {
      *(float *)&pMem2 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1));  // 虚调用 vt+128（pArg1）目标坐标y上界
      v27 = (double)(int)pMem2;
    }
    v28 = *(uint32_t *)pArg1[245];
    v29 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 124))(pArg1, (uint64_t)v27);  // 虚调用 vt+124（pArg1）目标坐标y下界
    v30 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v29);  // 虚调用 vt+120（pArg1）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(v28 + 40))(pArg1[245], v30);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)pArg1[245] + 12))(pArg1[245], 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)pArg1[245] + 92))(pArg1[245], v35);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    v31 = (void *)pArg1[29];
    v41 = 2;
    sub_4600B0(v31, 2, 0, (int)v35);  // sub_4600B0 —— 演播层注册(槽号)
    v41 = -1;
    if ( v36 != nullptr )  // 若 v36 有效（非空）
      j__free(v36);  // 释放堆块
    v36 = nullptr;
    v37 = 0;
    v38 = 0;
  }
  return sub_600AF0(nArg4, nArg5, nArg6);  // 【CNRDPassiveObject__vmt200】
}


// ------------------------------------------------------------
// 0x626D30 sub_626D30 —— 【海草】子件与冒泡粒子建立
//    置 +96=545 与阶段 0，经 sub_41ACF0 取 +712 句柄名、以 SSO 串(+364) 走 sub_4C3640 建 +976 挂件并虚 204(100, 表[3]) 设层帧；
//    再 new(0x12C) 由 sub_428F30 载 BreakableObject/Particle/SeaGrassBubble.ptl 存 +980，坐标按自身高(虚 192)×0.5 与虚 128 对齐后经虚 40/12 应用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_626D30(int *this)  // sub_626D30 —— 【海草】子件与冒泡粒子建立
{
  int fld_e178; // ecx
  int fld_e91; // ebx
  int v4; // eax
  uint32_t *pThis_5B; // eax
  int v6; // eax
  int fld_e36; // ecx
  int v8; // edx
  uint32_t *pMem; // eax
  uint32_t *result; // eax
  int pObj; // eax
  double v12; // st7
  int *fld_e245; // edi
  int v14; // ebx
  int v15; // eax
  int v16; // eax
  float Block; // [esp+Ch] [ebp-14h]

  *(this + 24) = 545;  // 写字段 this+24（nPageMax） ← 545
  *(this + 243) = 0;  // 写字段 this+243 ← 0
  if ( operator new(0x12Cu) != nullptr )  // 堆分配
  {
    fld_e178 = *(this + 178);  // 读字段 fld_e178 = this+178
    if ( (unsigned int)*(this + 96) < 0x10 )  // this+96 插值终点 X / 落点偏移
    {
      v6 = sub_41ACF0(fld_e178);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      pThis_5B = (uint32_t *)sub_4C3640(this + 91, v6, this);  // 调 构造 +988 挂件
    }
    else
    {
      fld_e91 = *(this + 91);  // 读字段 fld_e91 = this+91
      v4 = sub_41ACF0(fld_e178);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      pThis_5B = (uint32_t *)sub_4C3640(fld_e91, v4, this);  // 调 构造 +988 挂件
    }
  }
  else
  {
    pThis_5B = nullptr;
  }
  fld_e36 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
  v8 = *this;
  *(this + 244) = (int)pThis_5B;  // 写字段 this+244（fSyncValue） ← (int)pThis_5B
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v8 + 204))(  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
    this,
    100,
    *(uint32_t *)(fld_e36 + 4 * (*(this + 243) + 3)),  // this+972〔uCfgD972(推断)〕
    0,
    0,
    0,
    0);
  pMem = operator new(0x12Cu);  // 堆分配
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    result = sub_428F30(pMem, (int)"PassiveObject/MapObject/BreakableObject/Particle/SeaGrassBubble.ptl", 0);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
  else
    result = nullptr;
  *(this + 245) = (int)result;  // 写字段 this+245 ← (int)result
  if ( result != nullptr )  // 若 result 有效（非空）
  {
    if ( (*(int (/*thiscall*/ **)(int *))(*this + 684))(this) != 0 )  // 虚调用 vt+684（this 虚表槽）
    {
      pObj = (*(int (/*thiscall*/ **)(int *))(*this + 684))(this);  // 虚调用 vt+684（this 虚表槽）
      Block = (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 192))(pObj) * 0.5;  // 虚调用 vt+192（pObj）取尺寸/包围盒
      v12 = (double)(*(int (/*thiscall*/ **)(int *))(*this + 128))(this) + Block;  // 虚调用 vt+128（this）目标坐标y上界
    }
    else
    {
      v12 = (double)(*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    }
    fld_e245 = (int *)*(this + 245);  // this+980〔uCfgF980(推断)〕
    v14 = *fld_e245;
    v15 = (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(*this + 124))(  // 虚调用 vt+124（this）目标坐标y下界
            this,
            (uint64_t)v12 >> 32,
            (uint64_t)v12);
    v16 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v15);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(int *, int))(v14 + 40))(fld_e245, v16);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    return (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 245) + 12))(*(this + 245), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
  }
  return result;
}



// ------------------------------------------------------------
// 0x626EC0 CNEntangleVineTrigger__vmtC —— 【绞藤触发】构造初始化 vmtC
//    基类后按宿主(虚 684)有无二选一：有 → 清 +1008 并虚 472(2,0,1)、虚 372(200)；无 → 置 +1008=1、虚 472(3,0,1)、虚 372(100)。
// ------------------------------------------------------------
int /*thiscall*/ CNEntangleVineTrigger__vmtC(int this)  // 实现：(绞藤触发)构造初始化 vmtC
{
  int pThis_2AC; // eax
  int v3; // edx

  CNRDPassiveObject__vmtC((int *)this);
  pThis_2AC = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 684))(this);  // 虚调用 vt+684（this 虚表槽）
  v3 = *(uint32_t *)this;
  if ( pThis_2AC != 0 )
  {
    *(uint8_t *)(this + 1008) = 0;  // 写字段 this+1008（bVineDone1008） ← 0
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(v3 + 472))(this, 2, 0, 1);  // 虚函数调用 槽+472：主状态机（874 行）：CONDITION_STUN/DOWN_HEAV
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 372))(this, 200);  // 虚调用 vt+372（this）数值写入
  }
  else
  {
    *(uint8_t *)(this + 1008) = 1;  // 写字段 this+1008（bVineDone1008） ← 1
    (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(v3 + 472))(this, 3, 0, 1);  // 虚函数调用 槽+472：主状态机（874 行）：CONDITION_STUN/DOWN_HEAV
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
  }
}



// ------------------------------------------------------------
// 0x626F20 sub_626F20 —— 【绞藤触发】状态复位
//    把参数表(+348) 首项写入 +976，清 +972/+1008 与定时槽内 +993/+994 标志，末以 sub_698F90(clk,0,0) 停表。
// ------------------------------------------------------------
char /*thiscall*/ sub_626F20(int this)  // sub_626F20 —— 【绞藤触发】状态复位
{
  int pThis_3D4; // ecx

  *(uint32_t *)(this + 976) = **(uint32_t **)(this + 348);  // 写字段 this+976（uCfgE976） ← **(uint32_t **)(this + 348)
  *(uint32_t *)(this + 972) = 0;  // 写字段 this+972（uCfgD972） ← 0
  *(uint8_t *)(this + 1008) = 0;  // 写字段 this+1008（bVineDone1008） ← 0
  pThis_3D4 = this + 980;  // this+980 【推断】状态/配置表项 F
  *(uint8_t *)(pThis_3D4 + 13) = 0;  // 写字段 pThis_3D4+13 ← 0
  *(uint8_t *)(pThis_3D4 + 14) = 0;  // 写字段 pThis_3D4+14 ← 0
  return sub_698F90(pThis_3D4, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x626F50 CNEntangleVineTrigger__vmt200
//   【绞藤】BURN_VINE —— 藤蔓点燃触发
// ------------------------------------------------------------
int /*thiscall*/ CNEntangleVineTrigger__vmt200(int *this, int nArg2, float *pArg3, char pszArg4)  // 实现：(绞藤)BURN_VINE —— 藤蔓点燃触发
{
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "BURN_VINE", -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 && *((uint8_t *)this + 264) == 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 虚调用 vt+580（this）音效/技能播放(12参)
      this,
      40006,
      *(uint32_t *)(*(this + 87) + 4),  // this+348〔pParamTbl348〕
      0,
      0,
      0,
      0,
      0,
      4,
      0,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
  }
  return CNRDPassiveObject__vmt200(this, nArg2, pArg3, pszArg4);  // 返回 调 CNRDPassiveObject__vmt200
}



// ------------------------------------------------------------
// 0x626FE0 CNEntangleVineTrigger__vmt1D8 —— 【绞藤触发】按状态切件 vmt1D8
//    基类后按 nArg3 三选一：2 → 虚 196 取帧表[0]；3 → 虚 196 取虚 96 件（【推断】待机件）；4 → 虚 196 取帧表[1]。
// ------------------------------------------------------------
int /*userpurge*/ CNEntangleVineTrigger__vmt1D8@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：(绞藤触发)按状态切件 vmt1D8
{
  int result; // eax
  int v8; // edi
  int v9; // eax

  CNRDPassiveObject__vmt1D8(pDwArg1, nArg2, nArg3, nArg3, nArg4, nArg5, nArg6);
  if ( nArg3 == 2 )
    return (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)pDwArg1[36]);  // 虚调用 vt+196（pDwArg1）物件非空判定
  if ( nArg3 == 3 )
  {
    v8 = *pDwArg1;
    v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 96))(pDwArg1);  // 虚调用 vt+96（pDwArg1 虚表槽）
    return (*(int (/*thiscall*/ **)(int *, int))(v8 + 196))(pDwArg1, v9);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
  }
  else
  {
    result = nArg3 - 4;
    if ( nArg3 == 4 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[36] + 4));  // 虚调用 vt+196（pDwArg1）物件非空判定
  }
  return result;
}



// ------------------------------------------------------------
// 0x627060 sub_627060 —— 登记表按值删除
//    在 +1016..+1020 的 4 字节元素表中线性查 nArg2，命中则 memcpy 前移覆盖、表尾自减 4 并返回 1；未命中返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_627060(uint32_t *this, int nArg2)  // sub_627060 —— 登记表按值删除
{
  int fld_e254; // edx
  unsigned int i; // ecx

  fld_e254 = *(this + 254);  // 读字段 fld_e254 = this+254（field_00FE）
  for ( i = 0; fld_e254 != 0 && i < (*(this + 255) - fld_e254) >> 2; ++i )  // this+1020〔pAnimHandleArr(推断)〕
  {
    if ( nArg2 == *(uint32_t *)(*(this + 254) + 4 * i) )  // this+254 复位组字节
    {
      memcpy_0(
        (void *)(*(this + 254) + 4 * i),  // this+254 复位组字节
        (const void *)(*(this + 254) + 4 * i + 4),  // this+254 复位组字节
        4 * ((int)(*(this + 255) - (*(this + 254) + 4 * i + 4)) >> 2));  // this+1020〔pAnimHandleArr(推断)〕等 2 字段
      *(this + 255) -= 4;  // this+1020〔pAnimHandleArr(推断)〕
      return 1;  // 返回 1(成功)
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x6270E0 CNEntangleVineTrigger__vmt12C —— 来客注销时解绑
//    基类后，来客类别(虚 40)为 17 且 sub_627060 摘除登记成功时，对来客虚 216 停 10000 号 TAG（缠绕表现）。
// ------------------------------------------------------------
char /*thiscall*/ CNEntangleVineTrigger__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 来客注销时解绑
{
  char result; // al

  CNRDPassiveObject__vmt12C(this, nArg2);
  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);  // 虚调用 vt+40（nArg2）条件查询(273等)
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = sub_627060(this, nArg2);  // sub_627060 —— 登记表按值删除
    if ( result != 0 )  // 若结果非 0（成功）
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 216))(nArg2, 10000);  // 虚调用 vt+216（nArg2）全场广播
  }
  return result;
}



// ------------------------------------------------------------
// 0x627120 CNEntangleVine__vmt14C —— 【绞藤】主循环 vmt14C
//    基类后：登记表(+984) 为空或当前件(虚 200)已变时虚 196 回帧表[0]；
//    存活(虚 308)且 +264=0 时遍历登记表，对状态 16 查询(虚 776)为假者经虚 768(16,40,this) 施加缠绕，并以 off_77F3FC 记 byte_73DA88 日志。
// ------------------------------------------------------------
char /*thiscall*/ CNEntangleVine__vmt14C(uint32_t *this)  // 函数定义: 位置采样
{
  int fld_e246; // ecx
  int v3; // edi
  uint32_t *fld_e36; // edi
  unsigned int fld_e247; // eax
  int fld_e2462; // ecx
  unsigned int i; // ebx
  int fld_e2463; // ecx
  int v9; // edi
  int fld_e2464; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax

  CNRDPassiveObject__vmt14C((int)this);
  fld_e246 = *(this + 246);  // 读字段 fld_e246 = this+246
  if ( fld_e246 != 0 && (*(this + 247) - fld_e246) >> 2 != 0 )  // this+988〔uCfgA988(推断)〕
  {
    if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0 )  // 虚调用 vt+200（this）取值比较
LABEL_7:
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));  // 虚调用 vt+196（this）物件非空判定
  }
  else
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 虚调用 vt+200（this）取值比较
    if ( v3 == (*(int (/*thiscall*/ **)(uint32_t *))(*this + 96))(this)  // 虚调用 vt+96（this 虚表槽）
      && *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 4 )  // 虚调用 vt+200（this）取值比较
    {
      goto LABEL_7;
    }
  }
  fld_e36 = (uint32_t *)*(this + 36);  // this+36 物品状态字
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) == *fld_e36  // 虚调用 vt+200（this）取值比较
    && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0  // 虚调用 vt+200（this）取值比较
    && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    LOBYTE(fld_e247) = *((uint8_t *)this + 264);  // this+264 动画句柄
    if ( (uint8_t)fld_e247 != 0 )
      return fld_e247;
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
  }
  LOBYTE(fld_e247) = *((uint8_t *)this + 264);  // this+264 动画句柄
  if ( (uint8_t)fld_e247 == 0 )
  {
    fld_e2462 = *(this + 246);  // 读字段 fld_e2462 = this+246
    if ( fld_e2462 != 0 )
    {
      fld_e247 = (*(this + 247) - fld_e2462) >> 2;  // this+988〔uCfgA988(推断)〕
      if ( fld_e247 != 0 )
      {
        for ( i = 0; ; ++i )
        {
          fld_e2463 = *(this + 246);  // 读字段 fld_e2463 = this+246
          if ( fld_e2463 == 0 )
            break;
          fld_e247 = (*(this + 247) - fld_e2463) >> 2;  // this+988〔uCfgA988(推断)〕
          if ( i >= fld_e247 )
            break;
          v9 = 4 * i;  // 计算 v9 = 4 * i
          LOBYTE(fld_e247) = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(4 * i + fld_e2463) + 776))(  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
                         *(uint32_t *)(4 * i + fld_e2463),
                         16);
          if ( (uint8_t)fld_e247 == 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t, int, int, uint32_t *))(**(uint32_t **)(v9 + *(this + 246)) + 768))(  // 虚函数调用 槽+768：状态施加入口（17 状态槽懒创建 + 转发）
              *(uint32_t *)(v9 + *(this + 246)),  // this+984〔aStateBlk984(推断)〕
              16,
              40,
              this);
            fld_e2464 = *(uint32_t *)(v9 + *(this + 246));  // this+984〔aStateBlk984(推断)〕
            v11 = *(uint32_t *)(fld_e2464 + 312);  // 读字段 v11 = fld_e2464+312
            v12 = fld_e2464 + 288;  // 计算 v12 = fld_e2464 + 288
            if ( v11 < 0x10 )
              v13 = v12 + 4;  // 计算 v13 = v12 + 4
            else
              v13 = *(uint32_t *)(v12 + 4);  // 读字段 v13 = v12+4（pHostObj）
            LOBYTE(fld_e247) = off_77F3FC((char *)&byte_73DA88, v13);  // off_77F3FC —— 日志打印（printf 风格）
          }
        }
      }
    }
  }
  return fld_e247;
}



// ------------------------------------------------------------
// 0x6272B0 CNEntangleVine__vmt12C —— 【绞藤】注销解绑三路 vmt12C
//    自身注销：遍历 +984 表，状态 16 查询(虚 776)为真者经虚 772 取实例并虚 4(0,this) 解挂后记 byte_73DAC0，为假者直接记 byte_73DAA0；
//    宿主(虚 684)注销：虚 196 回帧表[0]；来客注销：从 +984 表 memcpy 摘项；三路统一收尾走基类 CNRDPassiveObject__vmt12C。
// ------------------------------------------------------------
void /*thiscall*/ CNEntangleVine__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  int nArg22; // ebx
  unsigned int v4; // edx
  int fld_e246; // ecx
  int v6; // edi
  bool v7; // zf
  int fld_e2462; // eax
  int pObj; // eax
  int fld_e2463; // eax
  unsigned int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  unsigned int v15; // ecx
  int v16; // eax
  int v17; // eax
  uint32_t *fld_e36; // edi
  int fld_e2464; // ecx
  int fld_e247; // eax
  int v21; // ecx
  uint32_t *fld_e2465; // edx
  unsigned int i; // [esp+Ch] [ebp-4h]

  nArg22 = nArg2;
  if ( (uint32_t *)nArg2 == this )
  {
    v4 = 0;
    for ( i = 0; ; v4 = i )
    {
      fld_e246 = *(this + 246);  // 读字段 fld_e246 = this+246
      if ( fld_e246 == 0 || v4 >= (*(this + 247) - fld_e246) >> 2 )  // this+988〔uCfgA988(推断)〕
        break;
      v6 = 4 * v4;  // 计算 v6 = 4 * v4
      v7 = (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(4 * v4 + fld_e246) + 776))(  // 虚函数调用 槽+776：异常状态激活查询 vt+776（研究 20 §1.2/§10 定案）
             *(uint32_t *)(4 * v4 + fld_e246),
             16) == 0;
      fld_e2462 = *(this + 246);  // 读字段 fld_e2462 = this+246
      if ( v7 )
      {
        v14 = *(uint32_t *)(v6 + fld_e2462);
        v15 = *(uint32_t *)(v14 + 312);  // 读字段 v15 = v14+312
        v16 = v14 + 288;  // 计算 v16 = v14 + 288
        if ( v15 < 0x10 )
          v17 = v16 + 4;  // 计算 v17 = v16 + 4
        else
          v17 = *(uint32_t *)(v16 + 4);  // 读字段 v17 = v16+4（pHostObj）
        off_77F3FC((char *)&byte_73DAA0, v17);  // off_77F3FC —— 日志打印（printf 风格）
      }
      else
      {
        pObj = (*(int (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(v6 + fld_e2462) + 772))(*(uint32_t *)(v6 + fld_e2462), 16);  // 虚函数调用 槽+772：17 状态槽数组访问（+6228+4*a2）
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t *))(*(uint32_t *)pObj + 4))(pObj, 0, this);  // 虚调用 vt+4（pObj）对象赋值/迁移
        fld_e2463 = *(uint32_t *)(v6 + *(this + 246));  // this+984〔aStateBlk984(推断)〕
        v11 = *(uint32_t *)(fld_e2463 + 312);  // 读字段 v11 = fld_e2463+312
        v12 = fld_e2463 + 288;  // 计算 v12 = fld_e2463 + 288
        if ( v11 < 0x10 )
          v13 = v12 + 4;  // 计算 v13 = v12 + 4
        else
          v13 = *(uint32_t *)(v12 + 4);  // 读字段 v13 = v12+4（pHostObj）
        off_77F3FC(byte_73DAC0, v13);  // off_77F3FC —— 日志打印（printf 风格）
      }
      ++i;  // 计数自增 i
    }
    nArg22 = nArg2;
    goto LABEL_28;
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this) == nArg2 )  // 虚调用 vt+684（this 虚表槽）
  {
    fld_e36 = (uint32_t *)*(this + 36);  // this+36 物品状态字
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) != *fld_e36 )  // 虚调用 vt+200（this）取值比较
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)*(this + 36));  // 虚调用 vt+196（this）物件非空判定
      CNRDPassiveObject__vmt12C(this, nArg2);
      return;
    }
    goto LABEL_28;
  }
  fld_e2464 = *(this + 246);  // 读字段 fld_e2464 = this+246
  if ( fld_e2464 != 0 )
    fld_e247 = (*(this + 247) - fld_e2464) >> 2;  // this+988〔uCfgA988(推断)〕
  else
    fld_e247 = 0;
  v21 = 0;
  if ( fld_e247 <= 0 )
  {
LABEL_28:
    CNRDPassiveObject__vmt12C(this, nArg22);
    return;
  }
  fld_e2465 = (uint32_t *)*(this + 246);  // this+984〔aStateBlk984(推断)〕
  while ( nArg2 != *fld_e2465 )  // 当 nArg2 != *fld_e2465 循环
  {
    ++v21;  // 计数自增 v21
    ++fld_e2465;  // 计数自增 fld_e2465
    if ( v21 >= fld_e247 )
      goto LABEL_28;
  }
  memcpy_0(
    (void *)(*(this + 246) + 4 * v21),  // this+984〔aStateBlk984(推断)〕
    (const void *)(*(this + 246) + 4 * v21 + 4),  // this+984〔aStateBlk984(推断)〕
    4 * ((*(this + 247) - (*(this + 246) + 4 * v21 + 4)) >> 2));  // this+988〔uCfgA988(推断)〕等 2 字段
  *(this + 247) -= 4;  // this+988〔uCfgA988(推断)〕
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x627480 sub_627480 —— 登记表去重追加
//    在 +1016 表查 nArg2，已存在返回 0；否则写表尾并前移 +1020，容量不足时走 sub_4E75F0 扩容，成功返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_627480(uint32_t *this, int nArg2)  // sub_627480 —— 登记表去重追加
{
  int fld_e254; // esi
  uint32_t *pThis_FD; // ecx
  unsigned int i; // edx
  int v7; // esi
  unsigned int v8; // edx
  int *nArg22; // eax

  fld_e254 = *(this + 254);  // 读字段 fld_e254 = this+254（field_00FE）
  pThis_FD = this + 253;  // this+253 复位组字节
  for ( i = 0; fld_e254 != 0 && i < (pThis_FD[2] - fld_e254) >> 2; ++i )  // 向量元素数 = (end−begin)/4
  {
    if ( nArg2 == *(uint32_t *)(*(this + 254) + 4 * i) )  // this+254 复位组字节
      return 0;
  }
  v7 = pThis_FD[1];
  if ( v7 != 0 )
    v8 = (pThis_FD[2] - v7) >> 2;  // 向量元素数 = (end−begin)/4
  else
    v8 = 0;
  if ( v7 != 0 && v8 < (pThis_FD[3] - v7) >> 2 )  // 向量元素数 = (end−begin)/4
  {
    nArg22 = (int *)pThis_FD[2];
    *nArg22 = nArg2;
    pThis_FD[2] = nArg22 + 1;
    return 1;  // 返回 1(成功)
  }
  else
  {
    sub_4E75F0((int)pThis_FD, pThis_FD[2], 1u, &nArg2);  // sub_4E75F0 —— uint32 vector 区间插入（容量 1.5 倍增长 + 三段搬运）
    return 1;  // 返回 1(成功)
  }
}



// ------------------------------------------------------------
// 0x627520 CNEntangleVine__vmt1F4
//   【绞藤】TIE_VINE —— 缠绕定身触发
// ------------------------------------------------------------
int /*thiscall*/ CNEntangleVine__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)  // 实现：(绞藤)TIE_VINE —— 缠绕定身触发
{
  uint32_t *pArg22; // esi
  uint32_t *v6; // eax

  pArg22 = pArg2;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 17) == 0  // 虚调用 vt+40（pArg2）条件查询(273等)
    || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 128))(pArg22) != 0  // 虚调用 vt+128（pArg22）目标坐标y上界
    || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 840))(pArg22) == 6  // 虚调用 vt+840（pArg22 虚表槽）
    || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg22 + 840))(pArg22) == 7 )  // 虚调用 vt+840（pArg22 虚表槽）
  {
    return 0;
  }
  (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "TIE_VINE", -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
  (*(void (/*thiscall*/ **)(uint32_t *, int, int, int *))(*pArg22 + 768))(pArg22, 16, 40, this);  // 虚调用 vt+768（pArg22 虚表槽）
  pArg2 = pArg22;
  sub_4E7BA0(&pArg2);  // sub_4E7BA0 —— 4 字节 vector push_back（容量不足 → ·sub_4E75F0 增 1）
  if ( pArg22[78] < 0x10u )
    v6 = pArg22 + 73;  // 计算 v6 = pArg22 + 73
  else
    v6 = (uint32_t *)pArg22[73];
  off_77F3FC((char *)&byte_73DAE0, v6);  // off_77F3FC —— 日志打印（printf 风格）
  return CNRDPassiveObject__vmt1F4(this, pArg22, pArg3, pszArg4);  // 返回 调 CNRDPassiveObject__vmt1F4
}



// ------------------------------------------------------------
// 0x6275F0 sub_6275F0
//   【绞藤】WALK_VINE_LOOP —— 藤上行走循环音
// ------------------------------------------------------------
void /*thiscall*/ sub_6275F0(uint32_t *this)  // 实现：(绞藤)WALK_VINE_LOOP —— 藤上行走循环音
{
  unsigned int i; // ebx
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj3; // edi
  int v11; // ebx
  signed int v12; // ebx
  int v13; // ebx
  signed int v14; // ebx
  unsigned int v15; // ecx
  int fld_e2543; // edx
  int pObj; // edi
  int v18; // eax
  unsigned int j; // ebx
  int fld_e254; // ecx
  int fld_e2542; // ecx
  int v22; // [esp-18h] [ebp-4Ch]
  int v23; // [esp-10h] [ebp-44h]
  int pObj32; // [esp+1Ch] [ebp-18h] BYREF
  unsigned int k; // [esp+20h] [ebp-14h]
  char v26; // [esp+27h] [ebp-Dh]
  int v27; // [esp+30h] [ebp-4h]

  v26 = 0;
  v27 = 0;
  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);  // 读字段 fld_e29 = this+29
    v4 = *(uint32_t *)(fld_e29 + 120);  // 读字段 v4 = fld_e29+120（pAnimObj）
    k = i;
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 120);  // 读字段 v6 = fld_e29+120（pAnimObj）
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 124) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v6 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )  // 虚调用 vt+40（pObj2）条件查询(273等)
    {
      fld_e292 = *(this + 29);  // 读字段 fld_e292 = this+29
      v9 = *(uint32_t *)(fld_e292 + 120);  // 读字段 v9 = fld_e292+120（pAnimObj）
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 124) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj3 = *(uint32_t *)(v9 + 4 * i);
      else
        pObj3 = 0;
      pObj32 = pObj3;
      if ( (uint8_t)sub_4E4630(pObj3) != 0  // sub_4E4630 —— ★ 敌我关系判定辅助（研究 §8 攻方冻结豁免门的组成件）
        && (uint8_t)sub_4E5CA0(pObj3) == 0  // sub_4E5CA0 —— 阵营号 200..204 判定（200 起逐个比较）
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 724))(pObj3) == 0  // 虚调用 vt+724（pObj3）取值
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 776))(pObj3, 16) != 1 )  // 虚调用 vt+776（pObj3 虚表槽）
      {
        v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 120))(pObj3);  // 虚调用 vt+120（pObj3）转发(对象+缓冲)
        v12 = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - v11);  // 虚调用 vt+120（this）转发(对象+缓冲)
        if ( v12 <= *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 32) )  // 虚调用 vt+340（this 虚表槽）
        {
          v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 124))(pObj3);  // 虚调用 vt+124（pObj3）目标坐标y下界
          v14 = abs32((*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) - v13);  // 虚调用 vt+124（this）目标坐标y下界
          if ( v14 <= *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 340))(this) + 36)  // 虚调用 vt+340（this 虚表槽）
            && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 128))(pObj3) <= 0 )  // 虚调用 vt+128（pObj3）目标坐标y上界
          {
            v26 = 1;
            if ( (uint8_t)sub_627480(pObj3) != 0 )  // sub_627480 —— 登记表去重追加
              (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pObj3 + 212))(  // 虚调用 vt+212（pObj3 虚表槽）
                pObj3,
                "WALK_VINE_LOOP",  // 资源/动画 TAG WALK_VINE_LOOP
                10000,
                0,
                0);
            sub_4E7BA0(&pObj32);  // sub_4E7BA0 —— 4 字节 vector push_back（容量不足 → ·sub_4E75F0 增 1）
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
      fld_e254 = *(this + 254);  // 读字段 fld_e254 = this+254（field_00FE）
      if ( fld_e254 == 0 || j >= (*(this + 255) - fld_e254) >> 2 )  // this+1020〔pAnimHandleArr(推断)〕
        break;
      fld_e2542 = *(uint32_t *)(4 * j + *(this + 254));  // this+254 复位组字节
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e2542 + 216))(fld_e2542, 10000);  // 虚调用 vt+216（fld_e2542）全场广播
      sub_627060(*(uint32_t *)(4 * j + *(this + 254)));  // sub_627060 —— 登记表按值删除
    }
  }
  else
  {
    *(this + 243) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308（this）是否本地玩家
    && *(this + 243) + *(this + 244) < (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
  {
    v15 = 0;
    for ( k = 0; ; v15 = k )
    {
      fld_e2543 = *(this + 254);  // 读字段 fld_e2543 = this+254（field_00FE）
      if ( fld_e2543 == 0 || v15 >= (*(this + 255) - fld_e2543) >> 2 )  // this+1020〔pAnimHandleArr(推断)〕
        break;
      pObj = *(uint32_t *)(fld_e2543 + 4 * v15);
      v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 虚调用 vt+152（this）取值(参数)
      v22 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 虚调用 vt+124（pObj）目标坐标y下界
      v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚调用 vt+120（pObj）转发(对象+缓冲)
      sub_4E4A50(this, 1030, 0, v18, v22, 0, v23, 0, 0, 0);  // sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      ++k;  // 计数自增 k
    }
    *(this + 243) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  }
}


// ------------------------------------------------------------
// 0x627900 CNEntangleVineTrigger__vmt14C —— 【绞藤触发】状态机主循环
//    基类后按状态(+960)分派：3 → 目标有效(+170)且存活时虚 560(4,0,0,0)，定时槽(+980)读数超 300 后走 sub_6275F0 并清 +993/+994 停表；
//    2 → 目标有效且存活时虚 560(3,0,0,0)；4 → 未触发(+264=0) 时虚 312(0) 停用。
// ------------------------------------------------------------
char /*thiscall*/ CNEntangleVineTrigger__vmt14C(int this)  // 函数定义: 位置采样
{
  int fld_3C0; // eax  | +0x03C0 → 状态槽（627900：fld_3C0 = *(+960)）（证据 va=00627900）（CNEntangleVineTrigger；va=00627900）

  CNRDPassiveObject__vmt14C(this);
  fld_3C0 = *(uint32_t *)(this + 960);  // 读字段 fld_3C0 = this+960（nBigStateMirror960）
  switch ( fld_3C0 )  // 按 fld_3C0 分派
  {
    case 3:  // case 3 分派（植物系：绞藤/扭草踏台/海草（0x626280-0x627900））
      if ( *(uint8_t *)(this + 1008) == 0  // this+1008 完成门字节
        && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0  // 虚调用 vt+200（this）取值比较
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 4, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
      }
      fld_3C0 = sub_699000(this + 980);  // 【clock_now(clk)】
      if ( fld_3C0 > 300 )
      {
        sub_6275F0((uint32_t *)this);  // 调 并清 +993/+994 停表
        *(uint8_t *)(this + 993) = 0;  // 写字段 this+993（uStateC993） ← 0
        *(uint8_t *)(this + 994) = 0;  // 写字段 this+994（bVineLatch994） ← 0
        LOBYTE(fld_3C0) = sub_698F90(this + 980, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      }
      break;
    case 2:  // case 2 分派（植物系：绞藤/扭草踏台/海草（0x626280-0x627900））
      fld_3C0 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 虚调用 vt+200（this）取值比较
      if ( *(uint8_t *)(fld_3C0 + 170) != 0 )
      {
        LOBYTE(fld_3C0) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
        if ( (uint8_t)fld_3C0 != 0 )
          LOBYTE(fld_3C0) = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(  // 虚调用 vt+560（this 虚表槽）
                         this,
                         3,
                         0,
                         0,
                         0);
      }
      break;
    case 4:  // case 4 分派（植物系：绞藤/扭草踏台/海草（0x626280-0x627900））
      fld_3C0 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this);  // 虚调用 vt+200（this）取值比较
      if ( *(uint8_t *)(fld_3C0 + 170) != 0 )
      {
        LOBYTE(fld_3C0) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
        if ( (uint8_t)fld_3C0 != 0 )
        {
          LOBYTE(fld_3C0) = *(uint8_t *)(this + 264);  // this+264 一次性门字节
          if ( (uint8_t)fld_3C0 == 0 )
            LOBYTE(fld_3C0) = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
        }
      }
      break;
    default:
      break;
  }
  return fld_3C0;  // +0x03C0 → 状态槽（627900：fld_3C0 = *(+960)）（证据 va=00627900）（CNEntangleVineTrigger；va=00627900）
}



// ============================================================
// 【分区 10】海星卵/莲花/被动触发器（0x627A00-0x6282A0）
// 证据: WRIGGLE_SLOW_LOOP / WRIGGLE_FAST_LOOP / HATCH_EGG（海星卵蠕动与孵化）、
//       LOTUS_SWEEP_LOOP（莲花横扫）；CNPassiveObjectTrigger = 被动物件触发基座
// ============================================================

// ------------------------------------------------------------
// 0x627A00 CNStarfishEgg__vmt12C —— 【空骨鱼卵】注销停循环音
//    自身注销时对自身虚 216 停 10000 与 10001 号 TAG（WRIGGLE_SLOW_LOOP / WRIGGLE_FAST_LOOP），随后走基类 CNRDPassiveObject__vmt12C。
// ------------------------------------------------------------
void /*thiscall*/ CNStarfishEgg__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10000);  // 虚调用 vt+216（this）全场广播
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10001);  // 虚调用 vt+216（this）全场广播
  }
}



// ------------------------------------------------------------
// 0x627A40 sub_627A40 —— 【空骨鱼卵】孵化放怪
//    sub_432FA0 播种后掷 rand%2+1 次：以虚 120/124 ± (20/10) 抖动经虚 136 寻空位（最多 100 次），虚 152 取候选序列(参数 8)、虚 376 把落点抬高 10，
//    末经虚 592 投出 250/252/253 三型之一（随机 100~300 / 50~150 / 40~100 参数）。
// ------------------------------------------------------------
int /*usercall*/ sub_627A40@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：(空骨鱼卵)孵化放怪
{
  int result; // eax
  int v5; // edi
  int nRand; // ebx
  int v7; // edi
  int nRand2; // eax
  int v9; // edx
  int nRand5; // eax
  int v12; // edi
  int v13; // eax
  int v14; // eax
  int nRand6; // eax
  int v16; // [esp-Ch] [ebp-34h]
  uint32_t v19[3]; // [esp+4h] [ebp-24h]
  uint16_t v20[3]; // [esp+10h] [ebp-18h] BYREF
  bool nRand3; // [esp+16h] [ebp-12h]
  char nRand4; // [esp+17h] [ebp-11h]
  int v23; // [esp+18h] [ebp-10h]
  int v24; // [esp+1Ch] [ebp-Ch]
  int i; // [esp+20h] [ebp-8h]
  int v26; // [esp+24h] [ebp-4h]

  sub_432FA0();  // sub_432FA0 —— srand 播种
  result = rand() % 2 + 1;  // 调 取伪随机数
  if ( result > 0 )
  {
    v19[0] = 250;
    v19[1] = 252;
    v19[2] = 253;
    for ( i = result; i != 0; --i )  // 遍历计次循环（i != 0）
    {
      v23 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 80))(pDwArg1, nArg3, nArg2) + 132)  // 虚调用 vt+80（pDwArg1）读 4 字节
                                  + 108)
                      + 112);
      v26 = 100;
      do
      {
        v5 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
        nRand = v5 + rand() % 40 - 20;  // 调 取伪随机数
        v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 虚调用 vt+124（pDwArg1）目标坐标y下界
        nRand2 = rand();  // 调 取伪随机数
        v9 = *pDwArg1;
        v24 = v7 + nRand2 % 20 - 10;
        if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(v9 + 136))(pDwArg1, nRand, v24, 0) != 0 )  // 虚函数调用 槽+136：槽（10 行）
          break;
      }
      while ( v26-- > 0 );
      v20[0] = rand() % 200 + 100;  // 调 取伪随机数
      v20[1] = rand() % 100 + 50;  // 调 取伪随机数
      nRand3 = rand() % 2 == 0;  // 调 取伪随机数
      nRand4 = 3 - (rand() % 2 != 0);  // 调 取伪随机数
      nRand5 = rand();  // 调 取伪随机数
      v12 = *pDwArg1;
      nArg2 = 0;
      nArg3 = 0;
      v20[2] = nRand5 % 60 + 40;
      v13 = (*(int (/*thiscall*/ **)(int *, int, uint16_t *, int, int, uint32_t, uint32_t))(v12 + 152))(  // 虚函数调用 槽+152：效果通道 3
              pDwArg1,
              1,
              v20,
              8,
              0xFFFF,
              0,
              0);
      v14 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 128))(pDwArg1, v13);  // 虚调用 vt+128（pDwArg1）目标坐标y上界
      v16 = (*(int (/*thiscall*/ **)(int *, int, int, int, int))(*pDwArg1 + 376))(pDwArg1, v23, nRand, v24, v14 + 10);  // 虚调用 vt+376（pDwArg1 虚表槽）
      nRand6 = rand();  // 调 取伪随机数
      result = (*(int (/*thiscall*/ **)(int *, uint32_t, int))(v12 + 592))(pDwArg1, v19[nRand6 % 3], v16);  // 虚函数调用 槽+592：位置/状态同步包发布（短版 48024 / 长版 type 22）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x627BE0 sub_627BE0 —— 【空骨鱼卵】孵化计时初始化
//    参数表首项写入 +680/+684（血量），清 +985/+986/+1001；对 +972 起定时槽 sub_698F90(5000,0) 设 5 秒表后 sub_699030 立即冻结，虚 372(100) 回待机。
// ------------------------------------------------------------
int /*thiscall*/ sub_627BE0(uint32_t **this)  // sub_627BE0 —— 【空骨鱼卵】孵化计时初始化
{
  uint32_t *fld_e87; // eax
  int pThis_F3; // edi
  int result; // eax

  fld_e87 = (uint32_t *)**(this + 87);  // this+348〔pParamTbl348〕
  pThis_F3 = (int)(this + 243);  // this+972〔uCfgD972(推断)〕
  *(this + 170) = fld_e87;  // 写字段 this+170 ← fld_e87
  *(this + 171) = fld_e87;  // 写字段 this+171 ← fld_e87
  *((uint8_t *)this + 985) = 0;  // 写字段 this+985（bGrabLatch985）
  *((uint8_t *)this + 986) = 0;  // 写字段 this[986]（宽1字节）
  sub_698F90((int)(this + 243), 5000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  sub_699030(pThis_F3);  // 【clock_freeze(clk)】
  result = ((int (/*thiscall*/ *)(uint32_t **, int))(*this)[93])(this, 100);
  *((uint8_t *)this + 1001) = 0;  // 写字段 this+1001（uStateE1001）
  return result;
}



// ------------------------------------------------------------
// 0x627C40 CNStarfishEgg__vmt2B4 —— 【空骨鱼卵】破壳切件 vmt2B4
//    +680(HP)≤0 且当前件(虚 200)非帧表[1] 时，虚 196 切至表[1]（破壳态）。
// ------------------------------------------------------------
int /*thiscall*/ CNStarfishEgg__vmt2B4(int *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int result; // eax
  uint32_t *fld_e36; // edi

  result = *(this + 170);  // 读字段 result = this+170
  if ( result <= 0 )
  {
    fld_e36 = (uint32_t *)(*(this + 36) + 4);  // this+36 物品状态字
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 虚调用 vt+200（this）取值比较
    if ( result != *fld_e36 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));  // 虚调用 vt+196（this）物件非空判定
  }
  return result;
}



// ------------------------------------------------------------
// 0x627C80 CNStarfishEgg__vmt14C
//   【海星卵】WRIGGLE_SLOW_LOOP / WRIGGLE_FAST_LOOP（蠕动双速）/ HATCH_EGG（孵化）
// ------------------------------------------------------------
char /*usercall*/ CNStarfishEgg__vmt14C@<al>(uint32_t **pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：(海星卵)WRIGGLE_SLOW_LOOP / WRIGGLE_FAST_LOOP（蠕动双速）/ HATCH_EGG（孵化）
{
  int v4; // edi
  int v5; // edi
  uint32_t *v6; // edi
  uint32_t *v7; // edi
  int v8; // eax
  bool v9; // zf
  int nArg32; // edi
  int v11; // eax

  CNRDPassiveObject__vmt14C((int)pArg1);
  if ( *((uint8_t *)pArg1 + 1000) == 0 )
  {
    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*pArg1)[53])(pArg1, "WRIGGLE_SLOW_LOOP", 10000, 0, 0);  // 资源/动画 TAG WRIGGLE_SLOW_LOOP
    *((uint8_t *)pArg1 + 1000) = 1;  // 写字段 pArg1+1000（bGrassFilter1000）
  }
  v4 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1);
  if ( v4 == ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[24])(pArg1) && sub_4E7F30(pArg1, 100, 70, 0) != 0 )  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
  {
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*pArg1)[49])(pArg1, *pArg1[36]);
    ((void (/*thiscall*/ *)(uint32_t **, int))(*pArg1)[54])(pArg1, 10000);
    ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*pArg1)[53])(pArg1, "WRIGGLE_FAST_LOOP", 10001, 0, 0);  // 资源/动画 TAG WRIGGLE_FAST_LOOP
    sub_698FE0((int)(pArg1 + 243));  // 【clock_unfreeze(clk)】
  }
  if ( *((uint8_t *)pArg1 + 986) == 0 )
  {
    v5 = (int)pArg1[249];
    if ( sub_699000((int)(pArg1 + 243)) >= v5 )  // 【clock_now(clk)】
    {
      v6 = pArg1[36] + 1;
      if ( ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1) != *v6 )
        ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*pArg1)[49])(pArg1, pArg1[36][1]);
    }
  }
  v7 = pArg1[36] + 1;
  v8 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1);
  v9 = v8 == *v7;
  nArg32 = nArg3;
  if ( v9 )
  {
    if ( *(int *)(((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1) + 148) >= 6 && *((uint8_t *)pArg1 + 1001) == 0 )
    {
      ((void (/*thiscall*/ *)(uint32_t **, const char *, int, uint32_t, uint32_t))(*pArg1)[53])(pArg1, "HATCH_EGG", -1, 0, 0);  // 资源/动画 TAG HATCH_EGG
      v11 = (int)*pArg1;
      *((uint8_t *)pArg1 + 1001) = 1;  // 写字段 pArg1+1001（uStateE1001）
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t **))(v11 + 308))(pArg1) != 0 && (int)pArg1[170] > 0 )  // 虚函数调用 槽+308
      {
        sub_627A40((int *)pArg1, nArg2, nArg32);  // sub_627A40 —— 【空骨鱼卵】孵化放怪
        pArg1[170] = nullptr;
      }
    }
    v8 = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[50])(pArg1);
    if ( *(int *)(v8 + 148) >= 9 )
    {
      LOBYTE(v8) = ((int (/*thiscall*/ *)(uint32_t **))(*pArg1)[77])(pArg1);  // 调 取 16 位值低 8 位
      if ( (uint8_t)v8 != 0 )
      {
        LOBYTE(v8) = *((uint8_t *)pArg1 + 264);  // 调 取 16 位值低 8 位
        if ( (uint8_t)v8 == 0 )
        {
          ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*pArg1)[145])(
            pArg1,
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
          LOBYTE(v8) = ((int (/*thiscall*/ *)(uint32_t **, uint32_t))(*pArg1)[78])(pArg1, 0);  // 调 取 16 位值低 8 位
        }
      }
    }
  }
  return v8;
}



// ------------------------------------------------------------
// 0x627E50 CNSweepingLegOfLotus__vmt12C —— 【莲花藤足】注销联动
//    自身注销时若宿主(虚 684) 经 RTTI 认作 CNPassiveObjectTrigger，则置全局 byte_795D3B=1（供 CNPassiveObjectTrigger__vmt1F4 消费）；
//    并对自身虚 216 停 10000 号 TAG，末走基类 CNLegOfLotus__vmt12C。
// ------------------------------------------------------------
void /*thiscall*/ CNSweepingLegOfLotus__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  int v3; // eax

  if ( (uint32_t *)nArg2 == this )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);  // 虚调用 vt+684（this 虚表槽）
    if ( __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
           v3,
           0,
           &IRDCollisionObject `RTTI Type Descriptor',
           &CNPassiveObjectTrigger `RTTI Type Descriptor',
           0) != 0 )
      byte_795D3B = 1;
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10000);  // 虚调用 vt+216（this）全场广播
  }
  CNLegOfLotus__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x627EB0 sub_627EB0 —— 计时刷新
//    记录 clock_now 到 +972 后虚 372(100) 回待机；【推断】为莲花族重置周期（同 sub_628930 结构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_627EB0(uint32_t *this)  // sub_627EB0 —— 计时刷新
{
  *(this + 243) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
}



// ------------------------------------------------------------
// 0x627ED0 CNPassiveObjectTrigger__vmt14C —— 被动触发基座节流
//    +264 未触发时以 clock_now 与 +972+3000 比较，超时则虚 352 触发并刷新 +972 时刻（3 秒周期）。
// ------------------------------------------------------------
char /*thiscall*/ CNPassiveObjectTrigger__vmt14C(uint8_t *this)  // 函数定义: 被动触发基座节流
{
  unsigned int pThis_24; // eax

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(pThis_24) = *(this + 264);  // this+264 动画句柄
  if ( (uint8_t)pThis_24 == 0 )
  {
    pThis_24 = sub_699000((int)(this + 36));  // 【clock_now(clk)】
    if ( *((uint32_t *)this + 243) + 3000 < pThis_24 )  // this+972〔uCfgD972(推断)〕
    {
      (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 352))(this);  // 虚调用 vt+352（this 虚表槽）
      pThis_24 = sub_699000((int)(this + 36));  // 【clock_now(clk)】
      *((uint32_t *)this + 243) = pThis_24;  // 写字段 this[243]（宽4字节）
    }
  }
  return pThis_24;
}



// ------------------------------------------------------------
// 0x627F20 sub_627F20 —— 横扫位置区间判定
//    取虚 80→+132→+44 区域表的元素数 v5，判自身坐标(虚 120) 是否 ≥100 且 ≤ 224×v5+100；【推断】供莲花横扫族判定是否在场地内。
// ------------------------------------------------------------
bool /*thiscall*/ sub_627F20(void *this)  // sub_627F20 —— 横扫位置区间判定
{
  int pThis_84; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // esi
  bool result; // al

  result = false;
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) >= 100 )  // 虚调用 vt+120（this）转发(对象+缓冲)
  {
    pThis_84 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 80))(this) + 132) + 44);  // 虚调用 vt+80（this）读 4 字节
    v3 = *(uint32_t *)(pThis_84 + 364);  // 读字段 v3 = pThis_84+364（pAnimNameStr）
    v4 = pThis_84 + 360;  // 计算 v4 = pThis_84 + 360
    v5 = v3 != 0 ? (*(uint32_t *)(v4 + 8) - v3) >> 5 : 0;
    if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this) <= 224 * v5 + 100 )  // 虚调用 vt+120（this）转发(对象+缓冲)
      return true;
  }
  return result;
}



// ------------------------------------------------------------
// 0x627F80 CNSweepingLegOfLotus__vmt14C
//   【莲花】LOTUS_SWEEP_LOOP —— 横扫循环音
// ------------------------------------------------------------
char /*usercall*/ CNSweepingLegOfLotus__vmt14C@<al>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)  // 实现：(莲花)LOTUS_SWEEP_LOOP —— 横扫循环音
{
  int v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int pObj2; // eax
  int v12; // ebx
  int v13; // eax
  int pObj; // eax
  int v15; // edi
  int v16; // eax
  int v17; // eax
  bool v18; // zf
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax

  CNRDPassiveObject__vmt14C((int)pArg1);
  if ( *((uint8_t *)pArg1 + 984) == 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 124))(pArg1, nArg3, nArg2);  // 虚调用 vt+124（pArg1）目标坐标y下界
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1) != 0 )  // 虚调用 vt+152（pArg1）取值(参数)
    {
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1) == 1 )  // 虚调用 vt+152（pArg1）取值(参数)
      {
        *(uint32_t *)(pArg1[28] + 16) = 1140457472;  // 浮点常量 500.0f
        if ( v4 != 0 )
        {
          (*(void (/*stdcall*/ **)(int, int, uint32_t))(*pArg1 + 112))(-50, v4, 0);  // 虚调用 vt+112（pArg1）坐标三元组写入
        }
        else
        {
          pObj = (*(int (/*fastcall*/ **)(uint32_t *))(*pArg1 + 684))(pArg1);  // 虚调用 vt+684（pArg1 虚表槽）
          v15 = *pArg1;
          v16 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 124))(pObj, 0);  // 虚调用 vt+124（pObj）目标坐标y下界
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v15 + 112))(pArg1, -50, v16);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
        }
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);  // 虚调用 vt+312（pArg1 虚表槽）
      }
    }
    else
    {
      v5 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 80))(pArg1) + 132) + 44);  // 虚调用 vt+80（pArg1）读 4 字节
      v6 = *(uint32_t *)(v5 + 364);  // 读字段 v6 = v5+364（pAnimNameStr）
      v7 = v5 + 360;  // 计算 v7 = v5 + 360
      if ( v6 != 0 )
        v8 = (*(uint32_t *)(v7 + 8) - v6) >> 5;
      else
        v8 = 0;
      v9 = 224 * v8 + 50;
      *(uint32_t *)(pArg1[28] + 16) = -1007026176;
      v10 = *pArg1;
      if ( v4 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v10 + 112))(pArg1, v9, v4, 0);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      }
      else
      {
        pObj2 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 684))(pArg1);  // 虚函数调用 槽+684：属性块基址（this+6132，HP 读处）
        v12 = *pArg1;
        v13 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 124))(pObj2, 0);  // 虚调用 vt+124（pObj2）目标坐标y下界
        (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v12 + 112))(pArg1, v9, v13);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 212))(pArg1, "LOTUS_SWEEP_LOOP", 10000);  // 虚调用 vt+212（pArg1 虚表槽）
    *((uint8_t *)pArg1 + 984) = 1;  // 写字段 pArg1+984（aStateBlk984）
  }
  LOBYTE(v17) = *((uint8_t *)pArg1 + 264);  // 调 取 16 位值低 8 位
  if ( (uint8_t)v17 == 0 )
  {
    v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 虚调用 vt+200（pArg1）取值比较
    if ( *(uint8_t *)(v17 + 170) != 0 )
    {
      v18 = !sub_627F20(pArg1);  // sub_627F20 —— 横扫位置区间判定
      v19 = *pArg1;
      if ( v18 )
      {
        v22 = (*(int (/*thiscall*/ **)(uint32_t *))(v19 + 80))(pArg1);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        sub_424120(*(uint32_t **)(v22 + 132), 0, 0);  // sub_424120 —— [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
        LOBYTE(v17) = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 虚调用 vt+308（pArg1）是否本地玩家
        if ( (uint8_t)v17 != 0 )
          LOBYTE(v17) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 312))(pArg1, 0);  // 虚调用 vt+312（pArg1 虚表槽）
      }
      else
      {
        v20 = (*(int (/*thiscall*/ **)(uint32_t *))(v19 + 80))(pArg1);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
        sub_424120(*(uint32_t **)(v20 + 132), 2, 1000);  // sub_424120 —— [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
        v21 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1);  // 虚调用 vt+200（pArg1）取值比较
        LOBYTE(v17) = sub_4926A0(v21);  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
      }
    }
  }
  return v17;
}



// ------------------------------------------------------------
// 0x628110 CNPassiveObjectTrigger__vmt1F4 —— 被动触发命中响应 vmt1F4
//    全局 byte_795D3B=1 且自身存活(虚 308)时，以 timeGetTime + 坐标 + 虚 120/124 播种 srand；按参数表(+348) 第二项分支：
//    1025 → rand%100 小于首项时按场景总宽/2(sub_425050) 判左右经 sub_4E4A50 生成并清全局位；30028 → 以目标虚 120/124 直接生成；末尾虚 312(0) 停用。
// ------------------------------------------------------------
int /*thiscall*/ CNPassiveObjectTrigger__vmt1F4(int **this, int nArg2, int nArg3, int nArg4)  // 函数定义: 被动触发命中响应 vmt1F4
{
  int v5; // edi
  int v6; // ebx
  int v7; // ebx
  DWORD Time; // eax
  int *fld_e87; // eax
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
    Time = timeGetTime();  // 调 取系统毫秒时刻
    srand(v7 + v19 + Time);  // 调 设置随机种子
    fld_e87 = *(this + 87);  // 读字段 fld_e87 = this+87
    v10 = *fld_e87;
    v11 = fld_e87[1];
    if ( v11 == 1025 )
    {
      if ( rand() % 100 < v10 )  // 调 取伪随机数
      {
        v13 = ((int (/*thiscall*/ *)(int **))(*this)[20])(this);
        v14 = sub_425050(*(uint32_t **)(*(uint32_t *)(v13 + 132) + 44)) / 2;  // sub_425050 —— 结果 = 总宽换算
        v15 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this);
        sub_4E4A50(this, 1025, 0xFFFF, 0, 0, 1000, v15 <= v14, 0, 0, 0);  // sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
        byte_795D3B = 0;
      }
    }
    else if ( v11 == 30028 )
    {
      v18 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
      v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);  // 虚调用 vt+124（nArg2）目标坐标y下界
      v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 虚调用 vt+120（nArg2）转发(对象+缓冲)
      sub_4E4A50(this, 30028, 0xFFFF, v12, v17, 500, v18, 0, 0, 0);  // sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
    }
    if ( *((uint8_t *)this + 264) == 0 )  // this+264 动画句柄
      ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[78])(this, 0);
  }
  return 0;
}



// ------------------------------------------------------------
// 0x628260 sub_628260 —— 待机复位
//    清 +984 后虚 204(100, 帧表[0]) 重设层帧，末尾虚 372(100) 回待机。
// ------------------------------------------------------------
int /*thiscall*/ sub_628260(uint32_t *this, int nArg2)  // sub_628260 —— 待机复位
{
  uint32_t *fld_e36; // eax
  int v4; // edx

  fld_e36 = (uint32_t *)*(this + 36);  // this+36 物品状态字
  v4 = *this;
  *((uint8_t *)this + 984) = 0;  // 写字段 this+984（aStateBlk984）
  (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v4 + 204))(100, *fld_e36, 0, 0, 0, 0);  // 虚函数调用 槽+204：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
}



// ------------------------------------------------------------
// 0x6282A0 sub_6282A0 —— 狂信者落点同步
//    遍历场景件(虚 80) 取类别(虚 40)=529 且归属(虚 376)与自身相同、非霸体(虚 724=0)、RTTI 为 CNZealot 者，
//    调 sub_5B7940 做目标落点继承（vt+1144 + 帧标记清 0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_6282A0(uint32_t *this)  // sub_6282A0 —— 狂信者落点同步
{
  uint32_t *pThis; // ebx
  unsigned int v2; // edi
  int v3; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj2; // ecx
  int v8; // ecx
  int v9; // edx
  int pObj; // esi
  int v11; // [esp+Ch] [ebp-8h]

  pThis = this;
  v2 = 0;
  while ( 1 )  // 无限循环
  {
    v3 = pThis[29];
    v4 = *(uint32_t *)(v3 + 8);  // 读字段 v4 = v3+8（nSkillRec8）
    result = v4 != 0 ? (*(uint32_t *)(v3 + 12) - v4) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)v2 >= result )
      return result;
    v6 = *(uint32_t *)(v3 + 8);  // 读字段 v6 = v3+8（nSkillRec8）
    if ( v6 != 0 && v2 < (*(uint32_t *)(v3 + 12) - v6) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v6 + 4 * v2);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )  // 虚调用 vt+40（pObj2）条件查询(273等)
    {
      v8 = pThis[29];
      v9 = *(uint32_t *)(v8 + 8);  // 读字段 v9 = v8+8（nSkillRec8）
      if ( v9 != 0 && v2 < (*(uint32_t *)(v8 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
        pObj = *(uint32_t *)(v9 + 4 * v2);
      else
        pObj = 0;
      v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 虚调用 vt+376（pObj 虚表槽）
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pThis + 376))(pThis) != v11  // 虚调用 vt+376（pThis 虚表槽）
        || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) != 0 )  // 虚调用 vt+724（pObj）取值
      {
        pThis = this;
        goto LABEL_20;
      }
      pThis = this;
      if ( __RTDynamicCast(pObj, 0, &IRDMonster `RTTI Type Descriptor', &CNZealot `RTTI Type Descriptor', 0) == 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
        goto LABEL_20;
      sub_5B7940(this);  // sub_5B7940 —— 目标落点继承（vt+1144 + 帧标记清 0）
      ++v2;  // 计数自增 v2
    }
    else
    {
LABEL_20:
      ++v2;  // 计数自增 v2
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
int /*thiscall*/ CNBellForZealots__vmt200(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：(钟)HIT_BELL —— 敲击音
{
  int v5; // eax
  uint32_t *fld_e36; // edi
  uint32_t *fld_e362; // edi
  uint32_t *v8; // ebx
  int v9; // eax

  if ( *(this + 276) >= *(this + 275) )  // this+276 地图条目指针
    return 0;
  v5 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);  // 虚调用 vt+348（nArg2）渲染数据块指针
  if ( *(uint8_t *)(v5 + 16) == 0 && *(float *)v5 <= 0.0 )
    return 0;
  fld_e36 = (uint32_t *)(*(this + 36) + 12);  // this+36 物品状态字
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) != *fld_e36 )  // 虚调用 vt+200（this）取值比较
  {
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "HIT_BELL", -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
    sub_4926A0(*(uint32_t *)(*(this + 36) + 12));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 12));  // 虚调用 vt+196（this）物件非空判定
    sub_4926A0(*(uint32_t *)(*(this + 36) + 16));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 16));  // 虚调用 vt+208（this）动画件回挂
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      100,
      *(uint32_t *)(*(this + 36) + 16),  // this+36 物品状态字
      0,
      0,
      0,
      0);
    sub_6282A0(this);  // sub_6282A0 —— 狂信者落点同步
    fld_e362 = (uint32_t *)(*(this + 36) + 12);  // this+36 物品状态字
    v8 = *(uint32_t **)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 80))(this) + 132);  // 虚调用 vt+80（this）读 4 字节
    v9 = sub_491C10(*fld_e362);  // sub_491C10 —— 结果 = 遍历帧数组（首+44/尾+48，步长 88）
    sub_424120(v8, 1, v9);  // sub_424120 —— [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
    ++*(this + 276);  // this+276 地图条目指针
  }
  return 0;
}



// ------------------------------------------------------------
// 0x6284C0 CNBellForZealots__vmt14C
//   【钟】BREAK_BELL —— 破碎音
// ------------------------------------------------------------
void /*thiscall*/ CNBellForZealots__vmt14C(int this)  // 函数定义: 位置采样
{
  int pFrameList144; // edi  | +0x0090 → 帧件列表基址（6284C0 vmt14C：fld_90 = *(+144)）（证据 va=006284C0）（CNBellForZealots；va=006284C0）
  int pBellObj1108; // edi  | +0x0454 → 子对象槽（6284C0：*(*(+1108)+12) 虚调停止）（证据 va=006284C0）（CNBellForZealots；va=006284C0）
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  void *fld_74; // ecx
  int pThis_60; // eax
  int v9; // edi
  int pThis_602; // eax
  uint8_t v11[4]; // [esp+8h] [ebp-1Ch] BYREF
  void *Block; // [esp+Ch] [ebp-18h]
  int v13; // [esp+20h] [ebp-4h]

  CNMapObject__vmt14C((int *)this);
  pFrameList144 = *(uint32_t *)(this + 144);  // 读字段 fld_90 = this+144（pFrameList144）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *(uint32_t *)(pFrameList144 + 12)  // 虚调用 vt+200（this）取值比较
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )  // 虚调用 vt+200（this）取值比较
  {
    if ( *(uint32_t *)(this + 1104) < *(uint32_t *)(this + 1100) )  // this+1104 时钟槽 B
    {
      pThis_60 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 96))(this);  // 虚调用 vt+96（this 虚表槽）
      sub_4926A0(pThis_60);  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
      v9 = *(uint32_t *)this;
      pThis_602 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 96))(this);  // 虚调用 vt+96（this 虚表槽）
      (*(void (/*thiscall*/ **)(int, int))(v9 + 196))(this, pThis_602);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 1108) + 12))(*(uint32_t *)(this + 1108), 0);  // this+1108 子对象槽
      pBellObj1108 = **(uint32_t **)(this + 1108);  // this+1108 子对象槽
      pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
      pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_80);  // 虚调用 vt+124（this）目标坐标y下界
      pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C + 1);  // 虚调用 vt+120（this）转发(对象+缓冲)
      (*(void (/*thiscall*/ **)(uint32_t, int))(pBellObj1108 + 40))(*(uint32_t *)(this + 1108), pThis_78);  // this+1108 子对象槽
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 1108) + 92))(*(uint32_t *)(this + 1108), v11);  // this+1108 子对象槽
      fld_74 = *(void **)(this + 116);  // this+116 观察者 vector 尾针
      v13 = 0;
      sub_4600B0(fld_74, 2, 0, (int)v11);  // sub_4600B0 —— 演播层注册(槽号)
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 20));  // 虚调用 vt+196（this）物件非空判定
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
        this,
        "BREAK_BELL",  // 资源/动画 TAG BREAK_BELL
        -1,
        0,
        0);
      sub_60B710((int *)this);
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 释放堆块
    }
  }
}



// ------------------------------------------------------------
// 0x628610 CNBellForZealots__vmt2E4 —— 【狂信者之钟】初始化 vmt2E4
//    参数表第 7 项写入 +1100（敲击上限）、清 +1104 计数，虚 372(100) 与虚 204(0, 帧表[2]) 设层帧；
//    再 new(0x12C) 以虚 672 参数表第 6 项（sub_41ACF0 取串）经 sub_4C3640 建 +1108 挂件。
// ------------------------------------------------------------
int /*thiscall*/ CNBellForZealots__vmt2E4(uint32_t *this)  // 实现：(狂信者之钟)初始化 vmt2E4
{
  int v2; // edx
  int v3; // eax
  uint32_t *pThis_5B; // ebx
  int v5; // eax
  int result; // eax

  v2 = *this;
  *(this + 275) = *(uint32_t *)(*(this + 87) + 28);  // 写字段 this+275 ← *(uint32_t *)(*(this + 87) + 28)
  *(this + 276) = 0;  // 写字段 this+276（pMapEntry） ← 0
  (*(void (/*stdcall*/ **)(int))(v2 + 372))(100);  // 虚函数调用 槽+372：目标点写入
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    0,
    *(uint32_t *)(*(this + 36) + 8),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  if ( operator new(0x12Cu) != nullptr )  // 堆分配
  {
    v3 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this) + 32) + 24;  // 虚调用 vt+672（this）队伍编号取址
    if ( *(this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
      pThis_5B = this + 91;
    else
      pThis_5B = (uint32_t *)*(this + 91);  // this+364〔pAnimNameStr(推断)〕
    v5 = sub_41ACF0(v3);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    result = sub_4C3640(pThis_5B, v5, this);  // 调 构造 +988 挂件
  }
  else
  {
    result = 0;
  }
  *(this + 277) = result;  // 写字段 this+277 ← result
  return result;
}



// ------------------------------------------------------------
// 0x6286E0 CNGravityChanger__vmt14C —— 【重力反转】状态跟随
//    每帧取场景节点(+116→+132) 的 +1324 重力标志：节点缺失或标志非 0 时虚 596(0)，否则虚 596(1)。
// ------------------------------------------------------------
int /*thiscall*/ CNGravityChanger__vmt14C(uint32_t *this)  // 函数定义: 位置采样
{
  int fld_74; // eax  | +0x0074 → 宿主链对象（CNGravityChanger；va=006287C0）

  CNRDPassiveObject__vmt14C((int)this);
  fld_74 = *(uint32_t *)(*(this + 29) + 132);  // this+116〔pHostLink〕
  if ( fld_74 == 0 || *(uint32_t *)(fld_74 + 1324) != 0 )
  {
    LOBYTE(fld_74) = 0;  // 调 取 16 位值低 8 位
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 596))(this, fld_74);  // 虚调用 vt+596（this 虚表槽）
  }
  else
  {
    LOBYTE(fld_74) = 1;  // 调 取 16 位值低 8 位
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 596))(this, fld_74);  // 虚调用 vt+596（this 虚表槽）
  }
}



// ------------------------------------------------------------
// 0x628720 CNGravityChanger__vmt1D8
//   【重力反转】BEHEMOTH_CRY / ZOOM_UP / BEHEMOTH_SCREAM / SUDDEN_DROP 四段演出
// ------------------------------------------------------------
int */*thiscall*/ CNGravityChanger__vmt1D8(uint32_t *this, int nArg2, int pArg3, int nArg4, int nArg5)  // 实现：(重力反转)BEHEMOTH_CRY / ZOOM_UP / BEHEMOTH_SCREAM / SUDDEN_DROP 四段演出
{
  int *result; // eax
  int v7; // edx
  int fld_74; // ecx  | +0x0074 → 宿主链对象（CNGravityChanger；va=006287C0）
  uint32_t *v9; // ecx

  CNRDPassiveObject__vmt1D8(this, nArg2, (int)this, nArg2, pArg3, nArg4, nArg5);
  result = *(int **)(pArg3 + 4);  // pArg3+4〔宿主对象〕
  v7 = *result;
  if ( nArg2 == 2 )
    v7 = -v7;
  fld_74 = *(this + 29);  // 读字段 fld_e29 = this+29
  if ( fld_74 != 0 )
  {
    v9 = *(uint32_t **)(fld_74 + 132);
    if ( v9 != nullptr )  // 若 v9 有效（非空）
    {
      sub_426B10(v9, v7, result[1]);
      if ( nArg2 == 2 )
      {
        sub_432EA0("BEHEMOTH_CRY", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
        return (int *)sub_432EA0("ZOOM_UP", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
      }
      else
      {
        sub_432EA0("BEHEMOTH_SCREAM", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
        return (int *)sub_432EA0("SUDDEN_DROP", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6287C0 CNGravityChanger__vmt1F4 —— 【重力反转】命中校验与施加 vmt1F4
//    基类后若存活(虚 308) 且来客类别(虚 40)=273、自身宿主链(+116→+132) 的 +1324 重力标志为 0：以参数表[4] 为概率掷投，
//    按重力方向(+1320<0) 选 2/3 号状态，表[0..3] 经 sub_423A80 区间取样两次装 vector 后虚 560 施加、虚 564 提交，末虚 312(0) 停用。
// ------------------------------------------------------------
int /*thiscall*/ CNGravityChanger__vmt1F4(int this, uint32_t *uArg2, float *pArg3, int nArg4)  // 实现：(重力反转)命中校验与施加 vmt1F4
{
  uint32_t *uArg22; // edi
  int v6; // eax
  int v7; // edx
  int nArg42; // ebx
  int fld_74; // edi  | +0x0074 → 宿主链对象（CNGravityChanger；va=006287C0）
  int pParamTbl348; // ebx  | +0x015C → 参数表指针（CNGravityChanger；va=006287C0）
  int v11; // ebx
  int nRand; // edi
  void *pBuf[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v15; // [esp+24h] [ebp-4h]

  uArg22 = uArg2;
  v6 = CNRDPassiveObject__vmt1F4((int *)this, uArg2, pArg3, nArg4);  // v6 = 调 CNRDPassiveObject__vmt1F4
  v7 = *(uint32_t *)this;
  nArg42 = v6;
  nArg4 = v6;
  if ( (*(uint8_t (/*thiscall*/ **)(int))(v7 + 308))(this) != 0 )  // 虚函数调用 槽+308
  {
    sub_432FA0();  // sub_432FA0 —— srand 播种
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*uArg22 + 40))(uArg22, 273) != 0 )  // 虚调用 vt+40（uArg22）条件查询(273等)
    {
      fld_74 = *(uint32_t *)(*(uint32_t *)(this + 116) + 132);  // this+116 宿主链对象
      if ( fld_74 != 0 && *(uint32_t *)(fld_74 + 1324) == 0 )
      {
        pParamTbl348 = *(uint32_t *)(this + 348);  // 读字段 fld_15C = this+348（pParamTbl348）
        if ( rand() % 100 < *(uint32_t *)(pParamTbl348 + 16) )  // 调 取伪随机数
        {
          v11 = (*(int *)(fld_74 + 1320) < 0) + 2;
          nRand = rand() % 100;  // 调 取伪随机数
          pArg3 = (float *)sub_423A80(**(uint32_t **)(this + 348), *(uint32_t *)(*(uint32_t *)(this + 348) + 4), nRand, 99);  // sub_423A80 —— 同上 int 版（FTOL 截断）
          uArg2 = (uint32_t *)sub_423A80(  // sub_423A80 —— 同上 int 版（FTOL 截断）
                           *(uint32_t *)(*(uint32_t *)(this + 348) + 8),  // this+348 参数表指针
                           *(uint32_t *)(*(uint32_t *)(this + 348) + 12),  // this+348 参数表指针
                           nRand,
                           99);
          memset(&pBuf[1], 0, 12);  // 调 内存按字节填充
          v15 = 0;
          sub_431230((int)pBuf, &pArg3);  // sub_431230 —— uint32 vector push_back
          sub_431230((int)pBuf, &uArg2);  // sub_431230 —— uint32 vector push_back
          (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, v11, pBuf, 0, 0);  // 虚调用 vt+560（this 虚表槽）
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 564))(this);  // 虚调用 vt+564（this 虚表槽）
          v15 = -1;
          sub_5E5260(pBuf);  // 调 动画子对象清理临时缓冲
        }
        nArg42 = nArg4;
      }
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    }
  }
  return nArg42;
}



// ------------------------------------------------------------
// 0x628930 sub_628930 —— 双时刻刷新
//    把 clock_now 同时写入 +972 与 +976 后虚 372(100)；【推断】为落石触发器双周期基准（同 sub_627EB0 结构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_628930(uint32_t *this)  // sub_628930 —— 双时刻刷新
{
  int pThis_9; // edi

  pThis_9 = (int)(this + 9);  // this+36〔nStateWord36(推断)〕
  *(this + 243) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  *(this + 244) = sub_699000(pThis_9);  // sub_699000 —— 【clock_now(clk)】
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
}



// ------------------------------------------------------------
// 0x628960 CNDroppingRock__vmt12C
//   【落石】TRAP_STONE_BREAK —— 落石破碎
// ------------------------------------------------------------
void /*thiscall*/ CNDroppingRock__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(  // 虚调用 vt+212（this 虚表槽）
      this,
      "TRAP_STONE_BREAK",  // 资源/动画 TAG TRAP_STONE_BREAK
      -1,
      0,
      0);
}



// ------------------------------------------------------------
// 0x628990 sub_628990 —— 落石雨撒落（TRAP_STONE 族）
//    以场景件(虚 80)→+132→+44 区域表按列(+224 步长、跳过首末列) srand，每列取 1~3 次：x=列基+rand%224、y=rand%200+100、时长=rand%200+500，
//    虚 136 判落点有效后经 sub_4E4A50 撒 48012 号（rand%8<5 的小碎石）与 1029 号主落石（末参 rand%2）。
// ------------------------------------------------------------
void /*thiscall*/ sub_628990(void *this)  // sub_628990 —— 落石雨撒落（TRAP_STONE 族）
{
  int pThis_84; // eax
  int v2; // ecx
  int v3; // eax
  int v4; // esi
  int v5; // edi
  int nRand; // edx
  int nRand2; // ebx
  int nRand3; // esi
  int nRand4; // edi
  int nRand6; // eax
  int nRand5; // [esp+8h] [ebp-18h]
  int v12; // [esp+Ch] [ebp-14h]
  int i; // [esp+10h] [ebp-10h]
  int v14; // [esp+14h] [ebp-Ch]
  int v16; // [esp+1Ch] [ebp-4h]

  pThis_84 = *(uint32_t *)(*(uint32_t *)((*(int (/*fastcall*/ **)(void *))(*(uint32_t *)this + 80))(this) + 132) + 44);  // 虚调用 vt+80（this）读 4 字节
  v2 = *(uint32_t *)(pThis_84 + 364);  // 读字段 v2 = pThis_84+364（pAnimNameStr）
  v3 = pThis_84 + 360;  // 计算 v3 = pThis_84 + 360
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
  sub_432FA0();  // sub_432FA0 —— srand 播种
  v12 = 0;
  if ( v5 > 0 )
  {
    v16 = 0;
    do
    {
      if ( v16 != 0 && v4 != v5 - 1 )  // 若 v16 != 0 与/或 v4 != v5
      {
        nRand = rand() % 3 + 1;  // 调 取伪随机数
        if ( nRand > 0 )
        {
          for ( i = nRand; i != 0; --i )  // 遍历计次循环（i != 0）
          {
            nRand2 = rand() % 8;  // 调 取伪随机数
            nRand3 = v16 + rand() % 224;  // 调 取伪随机数
            nRand4 = rand() % 200 + 100;  // 调 取伪随机数
            nRand5 = rand() % 200 + 500;  // 调 取伪随机数
            if ( (*(uint8_t (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, nRand3, nRand4, 0) != 0 )  // 虚调用 vt+136（this）目标挂接
            {
              if ( nRand2 < 5 )
                sub_4E4A50(this, 48012, 1, nRand3, nRand4, 0, 0, 0, 0, 0);  // sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
              nRand6 = rand() % 2;  // 调 取伪随机数
              sub_4E4A50(this, 1029, nRand2, nRand3, nRand4, nRand5, nRand6 != 0, 0, 0, 0);  // sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
            }
          }
          v4 = v12;
          v5 = v14;
        }
      }
      v12 = ++v4;
      v16 += 224;
    }
    while ( v4 < v5 );  // 循环直到 v4 < v5
  }
}



// ------------------------------------------------------------
// 0x628B00 CNDroppingRockTrigger__vmt14C —— 【落石触发】双模主循环
//    byte_9B9450=1（地震进行中）时：clock_now ≤ +972+2000 且存活且未触发(+264=0) 则清全局位、sub_628990 撒落石、虚 312(0)；
//    空闲态则以 clock_now > +976+3000 节流虚 352 触发并刷新 +976。
// ------------------------------------------------------------
char /*thiscall*/ CNDroppingRockTrigger__vmt14C(uint32_t *this)  // 函数定义: 位置采样
{
  unsigned int pThis_9; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( byte_9B9450 == 1 )
  {
    pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( *(this + 243) + 2000 >= pThis_9 )  // this+972〔uCfgD972(推断)〕
    {
      LOBYTE(pThis_9) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
      if ( (uint8_t)pThis_9 != 0 )
      {
        LOBYTE(pThis_9) = *((uint8_t *)this + 264);  // this+264 动画句柄
        if ( (uint8_t)pThis_9 == 0 )
        {
          byte_9B9450 = 0;
          sub_628990(this);  // sub_628990 —— 落石雨撒落（TRAP_STONE 族）
          LOBYTE(pThis_9) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
        }
      }
    }
  }
  else
  {
    pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( *(this + 244) + 3000 < pThis_9 )  // this+244 动画同步浮点参数
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 352))(this);  // 虚调用 vt+352（this 虚表槽）
      pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      *(this + 244) = pThis_9;  // 写字段 this+244（fSyncValue） ← pThis_9
    }
  }
  return pThis_9;
}



// ------------------------------------------------------------
// 0x628BA0 CNDroppingRockTrigger__vmt1F4
//   【落石】TAU_EQUAKE —— 牛头地震触发音
// ------------------------------------------------------------
int /*thiscall*/ CNDroppingRockTrigger__vmt1F4(int **this, int nArg2, int nArg3, int nArg4)  // 实现：(落石)TAU_EQUAKE —— 牛头地震触发音
{
  int fld_e87; // edi
  int v6; // eax

  if ( byte_9B9450 == 0 )
  {
    fld_e87 = **(this + 87);  // this+348〔pParamTbl348〕
    if ( sub_445870((uint32_t *)dword_8F8520, 37712, 100) < fld_e87 )  // sub_445870 —— 结果 = 槽表随机数
    {
      byte_9B9450 = 1;
      *(this + 243) = (int *)sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
      v6 = ((int (/*thiscall*/ *)(int **))(*this)[20])(this);
      sub_424120(*(uint32_t **)(v6 + 132), 4, 2000);  // sub_424120 —— [shake screen] 标签入口（解析器 sub_502F00 调用，全库 36 调用者）。
      ((void (/*thiscall*/ *)(int **, const char *, int, uint32_t, uint32_t))(*this)[53])(this, "TAU_EQUAKE", -1, 0, 0);  // 资源/动画 TAG TAU_EQUAKE
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x628C20 CNDroppingRock__vmt1F4 —— 【落石】参数装载与削弱 vmt1F4
//    取参数表[+972] 写入虚 348 属性块[0]；值为 0 或来客为 529 类且其 +7772 属 1/2/3 时归零并清该块 +60；
//    若来客归属(虚 376)=100 则以 0.1 系数削弱当前值，末走基类 CNRDPassiveObject__vmt1F4。
// ------------------------------------------------------------
int /*thiscall*/ CNDroppingRock__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)  // 实现：(落石)参数装载与削弱 vmt1F4
{
  int *fld_e87; // edi
  int v6; // eax
  int v7; // eax
  float *v8; // eax

  fld_e87 = (int *)(*(this + 87) + 4 * *(this + 243));  // this+348〔pParamTbl348〕
  *(float *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this) = (float)*fld_e87;  // 虚调用 vt+348（this）渲染数据块指针
  if ( *(float *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this) == 0.0 )  // 虚调用 vt+348（this）渲染数据块指针
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 348))(this);  // 虚调用 vt+348（this）渲染数据块指针
LABEL_10:
    *(uint32_t *)(v6 + 60) = 0;  // 写字段 v6+60（nFadeValue60） ← 0
    return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);  // 返回 调 CNRDPassiveObject__vmt1F4
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg2 + 40))(pArg2, 529) != 0 )  // 虚调用 vt+40（pArg2）条件查询(273等)
  {
    v7 = pArg2[1943];
    if ( v7 == 3 || v7 == 1 || v7 == 2 )  // 若 v7 == 3 与/或 v7 == 1 与/或 v7 == 2
    {
      *(uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this) = 0;  // 虚调用 vt+348（this）渲染数据块指针
      v6 = (*(int (/*thiscall*/ **)(int *))(*this + 348))(this);  // 虚调用 vt+348（this）渲染数据块指针
      goto LABEL_10;
    }
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 376))(pArg2) == 100 )  // 虚调用 vt+376（pArg2 虚表槽）
    {
      v8 = (float *)(*(int (/*thiscall*/ **)(int *))(*this + 348))(this);  // 虚调用 vt+348（this）渲染数据块指针
      *v8 = *v8 * 0.1;
    }
  }
  return CNRDPassiveObject__vmt1F4(this, pArg2, pArg3, pszArg4);  // 返回 调 CNRDPassiveObject__vmt1F4
}



// ------------------------------------------------------------
// 0x628CF0 sub_628CF0 —— 【旗帜】按序号换件
//    旧 +136 件经 sub_42AF90 析构 + sub_657740 池回收后，以 sub_42FCB0(228)+sub_431860 按虚 672 表[nArg2] 名重建并虚 196 应用；
//    把 +112 挂点件的 +36 置 -1200，序号 ≥4 时对 +876 句柄走虚 0 析构并清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_628CF0(uint32_t *this, int nArg2)  // sub_628CF0 —— 【旗帜】按序号换件
{
  void **fld_e34; // edi
  int v4; // edi
  int fld_e243; // ebx
  int v6; // eax
  const char *v7; // eax
  int v8; // eax
  int v9; // edx
  int result; // eax
  int (/*thiscall*/ ***fld_e219)(uint32_t, int); // ecx

  fld_e34 = (void **)*(this + 34);  // this+136〔nCtx136(推断)〕
  *(this + 243) = nArg2;  // 写字段 this+243 ← nArg2
  if ( fld_e34 != nullptr )  // 若 fld_e34 有效（非空）
  {
    sub_42AF90(fld_e34);  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_e34, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  *(this + 34) = 0;  // 写字段 this+34 ← 0
  v4 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
  if ( v4 != 0 )
  {
    fld_e243 = *(this + 243);  // 读字段 fld_e243 = this+243
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 672))(this);  // 虚调用 vt+672（this）队伍编号取址
    v7 = (const char *)sub_41ACF0(*(uint32_t *)(v6 + 32) + 4 * fld_e243);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    v8 = sub_431860(v4, v7, 1);  // sub_431860 —— 动画件构造（资源 id 版）
  }
  else
  {
    v8 = 0;
  }
  v9 = *this;
  *(this + 34) = v8;  // 写字段 this+34 ← v8
  (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 196))(this, v8);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
  result = *(this + 28);  // 读字段 result = this+28（pPanelVec）
  *(uint32_t *)(result + 36) = -1200;  // 写字段 result+36（nStateWord36） ← -1200
  if ( (int)*(this + 243) >= 4 )  // this+972〔uCfgD972(推断)〕
  {
    fld_e219 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 219);  // this+876〔句柄走虚〕
    if ( fld_e219 != nullptr )  // 若 fld_e219 有效（非空）
      result = (**fld_e219)(fld_e219, 1);  // 调 fld_e219 的虚函数（vt+0）
    *(this + 219) = 0;  // 写字段 this+219 ← 0
  }
  return result;
}



// ------------------------------------------------------------
// 0x628DE0 CNFlappingBanner__vmt14C —— 【旗帜】联动主循环 vmt14C
//    基类后遍历 +976 起向量(+980 为尾) 找 984 偏移处标志非 0 的子件：未找到 → 虚 196 应用 +136 待机件并虚 148(4)；
//    找到 → 虚 196 应用帧表[0]，并按该子件朝向(虚 152=1) 走虚 148(0) 或虚 148(1)。
// ------------------------------------------------------------
int /*thiscall*/ CNFlappingBanner__vmt14C(uint32_t *this)  // 函数定义: 位置采样
{
  int uCfgE976; // edi
  unsigned int i; // edx
  uint8_t *fld_e2442; // ecx
  int v5; // eax
  int v6; // edx
  int fld_e36; // [esp+0h] [ebp-8h]

  CNRDPassiveObject__vmt14C((int)this);
  uCfgE976 = *(this + 244);  // 读字段 fld_e244 = this+244（fSyncValue）
  for ( i = 0; ; ++i )
  {
    if ( uCfgE976 == 0 || i >= (*(this + 245) - uCfgE976) >> 2 )  // this+980〔uCfgF980(推断)〕
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(this + 34));  // 虚调用 vt+196（this）物件非空判定
      return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, 4);  // 虚调用 vt+148（this）位置/朝向写入
    }
    fld_e2442 = *(uint8_t **)(*(this + 244) + 4 * i);  // this+244 动画同步浮点参数
    if ( fld_e2442[984] != 0 )
      break;
  }
  v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)fld_e2442 + 152))(fld_e2442);  // 虚调用 vt+152（fld_e2442）取值(参数)
  v6 = *this;
  fld_e36 = *(uint32_t *)*(this + 36);  // this+36 物品状态字
  if ( v5 == 1 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v6 + 196))(this, fld_e36);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 148))(this, 0);  // 虚调用 vt+148（this）位置/朝向写入
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v6 + 196))(this, fld_e36);  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, 1);  // 虚调用 vt+148（this）位置/朝向写入
  }
}



// ------------------------------------------------------------
// 0x628E90 CNFlappingBanner__vmt140 —— 【旗帜】采集受风体 vmt140
//    基类后释放 +976 起的向量并遍历场景件，对 RTTI 为 CNWindShaker 的对象去重追加（写尾 +980，满则经 sub_428220 扩容）。
// ------------------------------------------------------------
int /*thiscall*/ CNFlappingBanner__vmt140(int *this)  // 实现：(旗帜)采集受风体 vmt140
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
  int uCfgE976; // edx
  unsigned int fld_e245; // ecx
  int *fld_e245; // eax
  unsigned int v17; // ebx
  int v18; // [esp+Ch] [ebp-8h] BYREF
  unsigned int v19; // [esp+10h] [ebp-4h]

  CNRDPassiveObject__vmt140(this);
  v2 = 0;
  if ( *(this + 244) != 0 )  // this+244 动画同步浮点参数
    j__free((void *)*(this + 244));  // 释放堆块
  *(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
  *(this + 245) = 0;  // 写字段 this+245 ← 0
  *(this + 246) = 0;  // 写字段 this+246 ← 0
  while ( 1 )  // 无限循环
  {
    v3 = *this;
    v19 = v2;
    v4 = (*(int (/*thiscall*/ **)(int *))(v3 + 80))(this);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    v5 = *(uint32_t *)(v4 + 120);  // 读字段 v5 = v4+120（pAnimObj）
    v6 = v4 + 116;  // 计算 v6 = v4 + 116
    result = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)v2 >= result )
      return result;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 虚调用 vt+80（this）读 4 字节
    v9 = *(uint32_t *)(v8 + 120);  // 读字段 v9 = v8+120（pAnimObj）
    if ( v9 != 0 && v2 < (*(uint32_t *)(v8 + 124) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
      v10 = *(uint32_t *)(v9 + 4 * v2);
    else
      v10 = 0;
    if ( __RTDynamicCast(v10, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNWindShaker `RTTI Type Descriptor', 0) != 0 )  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 虚调用 vt+80（this）读 4 字节
      v12 = *(uint32_t *)(v11 + 120);  // 读字段 v12 = v11+120（pAnimObj）
      if ( v12 != 0 && v2 < (*(uint32_t *)(v11 + 124) - v12) >> 2 )  // 向量元素数 = (end−begin)/4
        v13 = *(uint32_t *)(v12 + 4 * v2);
      else
        v13 = 0;
      uCfgE976 = *(this + 244);  // 读字段 fld_e244 = this+244（fSyncValue）
      v18 = v13;
      if ( uCfgE976 != 0 )
        fld_e245 = (*(this + 245) - uCfgE976) >> 2;  // this+980〔uCfgF980(推断)〕
      else
        fld_e245 = 0;
      if ( uCfgE976 == 0 || fld_e245 >= (*(this + 246) - uCfgE976) >> 2 )  // this+984〔aStateBlk984(推断)〕
      {
        sub_428220((int)(this + 243), *(this + 245), 1u, &v18);  // sub_428220 —— STL 内联 vector 插入（4B 元素）
        v2 = v19;
        goto LABEL_24;
      }
      fld_e245 = (int *)*(this + 245);  // this+980〔uCfgF980(推断)〕
      *fld_e245 = v13;
      v17 = v19;
      *(this + 245) = (int)(fld_e245 + 1);  // 写字段 this+245 ← (int)(fld_e2452 + 1)
      v2 = v17 + 1;  // 计算 v2 = v17 + 1
    }
    else
    {
LABEL_24:
      ++v2;  // 计数自增 v2
    }
  }
}



// ============================================================
// 【分区 12】龙头炮台（CNDragonHeadSide 家族，0x628FB0-0x6299C0）
// 证据: Particle/DragonHeadEnergyBall.ptl（侧向）/ DragonHeadEnergyBallVertical.ptl（纵向）；
//       变体: SideFlame（喷火）/ SideNentan（能量球）/ SideGas（毒气）/ FrontNentan
// ============================================================

// ------------------------------------------------------------
// 0x628FB0 CNDragonHeadSide__vmt2E4 —— 【龙头炮台】初始化 vmt2E4
//    清 +1100 计数与 +1108 标志，虚 372(100) 回待机并置 +1109=1（首轮扫描标志）。
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSide__vmt2E4(uint32_t *this)  // 实现：(龙头炮台)初始化 vmt2E4
{
  int result; // eax

  *(this + 275) = 0;  // 写字段 this+275 ← 0
  *((uint8_t *)this + 1108) = 0;  // 写字段 this+1108（pAttach1108）
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
  *((uint8_t *)this + 1109) = 1;  // 写字段 this+1109（bScanRound1109）
  return result;
}



// ------------------------------------------------------------
// 0x628FE0 CNDragonHeadSide__vmt12C —— 注销（自身时虚 308）
//    nArg2 为自身时虚 308 停用，末尾走基类 CNMapObject__vmt12C。
// ------------------------------------------------------------
char /*thiscall*/ CNDragonHeadSide__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 注销
{
  if ( this == (uint32_t *)nArg2 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  return CNMapObject__vmt12C(this, nArg2);  // 返回 调 CNMapObject__vmt12C
}



// ------------------------------------------------------------
// 0x629010 sub_629010 —— 释放 +1120 句柄
//    对 +1120 句柄走虚 0 析构(参数 1) 并清零（句柄回收样板，同 sub_6269A0 / sub_629C40 / sub_62A6B0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_629010(uint32_t *this)  // sub_629010 —— 释放 +1120 句柄
{
  int (/*thiscall*/ ***fld_e280)(uint32_t, int); // ecx
  int result; // eax

  fld_e280 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 280);  // this+280 地图条目数组 end
  if ( fld_e280 != nullptr )  // 若 fld_e280 有效（非空）
    result = (**fld_e280)(fld_e280, 1);  // 调 fld_e280 的虚函数（vt+0）
  *(this + 280) = 0;  // 写字段 this+280（pMapEntryVecEnd） ← 0
  return result;
}



// ------------------------------------------------------------
// 0x629030 CNDragonHeadSideFlame__vmt12C —— 【龙头·喷火】注销
//    nArg2 为自身时连续两次虚 308（与 CNDragonHeadSide__vmt12C 同构，多一次调用），末走基类 CNMapObject__vmt12C。
// ------------------------------------------------------------
char /*thiscall*/ CNDragonHeadSideFlame__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  if ( this == (uint32_t *)nArg2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  }
  return CNMapObject__vmt12C(this, nArg2);  // 返回 调 CNMapObject__vmt12C
}



// ------------------------------------------------------------
// 0x629060 CNDragonHeadSideNentan__vmt2E4 —— 【龙头·能量球】初始化 vmt2E4
//    经虚 384 取参数表第 9/10 项写入 +1112/+1116（能量球生成参数，供同族 vmt2F8 使用）。
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSideNentan__vmt2E4(uint32_t *this)  // 实现：(龙头·能量球)初始化 vmt2E4
{
  int v2; // eax
  int v3; // edx
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);  // 虚调用 vt+384（this 虚表槽）
  v3 = *this;
  *(this + 278) = v2;  // 写字段 this+278 ← v2
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 10);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  *(this + 279) = result;  // 写字段 this+279 ← result
  return result;
}



// ------------------------------------------------------------
// 0x629090 CNDragonHeadSideNentan__vmt14C —— 【龙头·能量球】发射节流
//    基类后存活(虚 308) 且当前件(虚 200)为 +136 时，以 +1100+5000 节流：虚 756 允许且 rand%100<50 时虚 760 发射，并刷新 +1100。
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNDragonHeadSideNentan__vmt14C(int *this)  // 函数定义: 位置采样
{
  unsigned int result; // eax

  CNMapObject__vmt14C(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 虚调用 vt+200（this）取值比较
    if ( result == *(this + 34) )  // this+136〔nCtx136(推断)〕
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( *(this + 275) + 5000 < result )  // this+1100〔nFairyGrade(推断)〕
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 756))(this) != 0 && rand() % 100 < 50 )  // 虚调用 vt+756（this 虚表槽）
          (*(void (/*thiscall*/ **)(int *))(*this + 760))(this);  // 虚调用 vt+760（this 虚表槽）
        result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        *(this + 275) = result;  // 写字段 this+275 ← result
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x629110 CNDragonHeadSideNentan__vmt2F8
//   【龙头】Particle/DragonHeadEnergyBall.ptl —— 侧向能量球
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSideNentan__vmt2F8(uint32_t *this)  // 实现：(龙头)Particle/DragonHeadEnergyBall.ptl —— 侧向能量球
{
  int v2; // eax
  int fld_e279; // edx
  uint16_t *v4; // esi
  int v5; // eax
  int fld_e278; // [esp-1Ch] [ebp-94h]
  int v8; // [esp+Ch] [ebp-6Ch]
  uint16_t v9[50]; // [esp+10h] [ebp-68h] BYREF
  int dword_796E502; // [esp+74h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  sub_423A20((int)v9);  // sub_423A20 —— 小结构初始化（0-100 刻度）
  v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);  // 虚调用 vt+152（this）取值(参数)
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(this, "Particle/DragonHeadEnergyBall.ptl");  // 虚调用 vt+588（this 虚表槽）
  fld_e279 = *(this + 279);  // 读字段 fld_e279 = this+279
  v4 = (uint16_t *)v2;
  v5 = *this;
  qmemcpy(v9, v4, 0x60u);  // 调 内存块拷贝(内联展开)
  fld_e278 = *(this + 278);  // 读字段 fld_e278 = this+278
  v9[48] = v4[48];
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint16_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v5 + 580))(  // 虚函数调用 槽+580：位置化动作发布（会话 3 定案：位置化动作）
           this,
           30082,
           0,
           v9,
           0,
           fld_e278,
           0,
           fld_e279,
           v8,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x6291A0 CNDragonHeadSideGas__vmt2E4 —— 【龙头·毒气】初始化 vmt2E4
//    经虚 384 取参数表第 9..13 项写入 +1112..+1128（毒气分段生成参数）。
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSideGas__vmt2E4(uint32_t *this)  // 实现：(龙头·毒气)初始化 vmt2E4
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int result; // eax

  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);  // 虚调用 vt+384（this 虚表槽）
  v3 = *this;
  *(this + 278) = v2;  // 写字段 this+278 ← v2
  *(this + 279) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 10);  // 写字段 this+279 ← (*(int (·thiscall· **)(uint32_t *, int))(v3 + 384))(this, 10)
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 11);  // 虚调用 vt+384（this 虚表槽）
  v5 = *this;
  *(this + 280) = v4;  // 写字段 this+280（pMapEntryVecEnd） ← v4
  *(this + 281) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 12);  // 写字段 this+281 ← (*(int (·thiscall· **)(uint32_t *, int))(v5 + 384))(this, 12)
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 13);  // 虚调用 vt+384（this 虚表槽）
  *(this + 282) = result;  // 写字段 this+282 ← result
  return result;
}



// ------------------------------------------------------------
// 0x629200 CNDragonHeadSideGas__vmt14C —— 【龙头·毒气】喷发节流 vmt14C
//    基类后存活且当前件为 +136 时，以 +1100+5000 节流；虚 756 允许且 rand%100<50 时虚 580 以 +1128 号生成（参数取 +1112/+1116..+1124，末参 4）。
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNDragonHeadSideGas__vmt14C(int *this)  // 函数定义: 位置采样
{
  unsigned int result; // eax

  CNMapObject__vmt14C(this);
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 虚调用 vt+200（this）取值比较
    if ( result == *(this + 34) )  // this+136〔nCtx136(推断)〕
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( *(this + 275) + 5000 < result )  // this+1100〔nFairyGrade(推断)〕
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 756))(this) != 0 && rand() % 100 < 50 )  // 虚调用 vt+756（this 虚表槽）
          (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 虚调用 vt+580（this）音效/技能播放(12参)
            this,
            *(this + 282),  // this+1128〔nListCap1128(推断)〕
            *(this + 278),  // this+1112〔nTick1112(推断)〕
            0,
            0,
            *(this + 279),
            *(this + 280),  // this+280 地图条目数组 end
            *(this + 281),  // this+1124〔nListCnt1124(推断)〕
            4,
            0,
            0,
            0);
        result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        *(this + 275) = result;  // 写字段 this+275 ← result
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6292C0 CNDragonHeadFrontNentan__vmt2F8
//   【龙头】Particle/DragonHeadEnergyBallVertical.ptl —— 纵向能量球
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadFrontNentan__vmt2F8(uint32_t *this)  // 实现：(龙头)Particle/DragonHeadEnergyBallVertical.ptl —— 纵向能量球
{
  uint16_t *v2; // eax
  int v3; // edx
  int result; // eax
  int fld_e278; // [esp-1Ch] [ebp-90h]
  int fld_e279; // [esp-14h] [ebp-88h]
  uint16_t v7[50]; // [esp+Ch] [ebp-68h] BYREF
  int dword_796E502; // [esp+70h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  sub_423A20((int)v7);  // sub_423A20 —— 小结构初始化（0-100 刻度）
  v2 = (uint16_t *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*this + 588))(  // 虚调用 vt+588（this 虚表槽）
                  this,
                  "Particle/DragonHeadEnergyBallVertical.ptl");  // 资源路径 Particle/DragonHeadEnergyBallVertical.ptl
  v3 = *this;
  fld_e279 = *(this + 279);  // 读字段 fld_e279 = this+279
  qmemcpy(v7, v2, 0x60u);  // 调 内存块拷贝(内联展开)
  fld_e278 = *(this + 278);  // 读字段 fld_e278 = this+278
  v7[48] = v2[48];
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint16_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v3 + 580))(  // 虚函数调用 槽+580：位置化动作发布（会话 3 定案：位置化动作）
             this,
             30083,
             0,
             v7,
             0,
             fld_e278,
             0,
             fld_e279,
             1,
             0,
             0,
             0);
  *(this + 280) = result;  // 写字段 this+280（pMapEntryVecEnd） ← result
  return result;
}



// ------------------------------------------------------------
// 0x629340 CNDragonHeadFrontNentan__vmt128 —— 【龙头·纵向能量球】目标登记 vmt128
//    来客类别(虚 40)=33 且其虚 52 与 +1120（同族 vmt2F8 的生成结果）相符时，sub_4E7E40 把其挂入自身表。
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadFrontNentan__vmt128(uint32_t *this, int nArg2)  // 实现：(龙头·纵向能量球)目标登记 vmt128
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 33);  // 虚调用 vt+40（nArg2）条件查询(273等)
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);  // 虚调用 vt+52（nArg2）归属坐标y
    if ( result == *(this + 280) )  // this+280 地图条目数组 end
      return sub_4E7E40(nArg2);  // sub_4E7E40 —— this+652 vector push_back（容量不足 → ·sub_428220）
  }
  return result;
}



// ------------------------------------------------------------
// 0x629380 CNDragonHeadSide__vmtC —— 【龙头炮台】构造初始化 vmtC
//    虚 384 取参数表第 7 项写 +680/+684（血量）、第 8 项写 +1104；场景参数表长度 ≥7 且第 7 项名匹配 Left 时虚 148(0) 定朝向。
// ------------------------------------------------------------
char /*thiscall*/ CNDragonHeadSide__vmtC(int *this)  // 实现：(龙头炮台)构造初始化 vmtC
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  unsigned int v6; // eax
  int v7; // eax

  CNMapObject__vmtC(this);
  v2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 7);  // 虚调用 vt+384（this 虚表槽）
  v3 = *this;
  *(this + 170) = v2;  // 写字段 this+170 ← v2
  *(this + 171) = v2;  // 写字段 this+171 ← v2
  *(this + 276) = (*(int (/*thiscall*/ **)(int *, int))(v3 + 384))(this, 8);  // 写字段 this+276（pMapEntry） ← (*(int (·thiscall· **)(int *, int))(v3 + 384))(this, 8)
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);  // 虚调用 vt+672（this）队伍编号取址
  v5 = *(uint32_t *)(v4 + 32);  // 读字段 v5 = v4+32（nHeight）
  v6 = v4 + 28;  // 计算 v6 = v4 + 28
  if ( v5 != 0 )
  {
    v6 = (*(uint32_t *)(v6 + 8) - v5) >> 2;  // 向量元素数 = (end−begin)/4
    if ( v6 >= 7 )
    {
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);  // 虚调用 vt+672（this）队伍编号取址
      LOBYTE(v6) = sub_43BCF0((void *)(*(uint32_t *)(v7 + 32) + 24), "Left");  // sub_43BCF0 —— 字符串 “[free]”
      if ( (uint8_t)v6 != 0 )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 148))(this, 0);  // 虚调用 vt+148（this）位置/朝向写入
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x629410 CNDragonHeadSideFlame__vmt1D8 —— 【龙头·喷火】点火熄火切换 vmt1D8
//    nArg2==2（点火）：置 +1116、虚 196 切帧表[1]、+1120 件虚 12 复位并记 clock_now 入 +1112；
//    nArg2==0（熄火）：清 +1116、+1120 件虚 64(1) 启播，若原态(+960)为 2 则按 +1108 虚 196 回帧表[0] 或 +136。
// ------------------------------------------------------------
int /*thiscall*/ CNDragonHeadSideFlame__vmt1D8(int *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：(龙头·喷火)点火熄火切换 vmt1D8
{
  int nBigStateMirror960; // ebx  | +0x03C0 → 大状态镜像/状态槽（CNDragonHeadSideFlame；va=006295C0）
  int result; // eax
  int *fld_e36; // eax
  int pList1120; // ecx  | +0x0460 → 名单/缓冲起点（CNDragonHeadSideFlame；va=006295C0）
  int v10; // edx

  nBigStateMirror960 = *(this + 240);  // 读字段 fld_e240 = this+240（nSyncArgB）
  CNRDPassiveObject__vmt1D8(this, nBigStateMirror960, nArg2, nArg2, nArg3, nArg4, nArg5);
  if ( nArg2 != 0 )
  {
    result = nArg2 - 2;
    if ( nArg2 == 2 )
    {
      fld_e36 = (int *)(*(this + 36) + 4);  // this+36 物品状态字
      *((uint8_t *)this + 1116) = 1;  // 写字段 this[1116]（宽1字节）
      sub_4926A0(*fld_e36);  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));  // 虚调用 vt+196（this）物件非空判定
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 280) + 12))(*(this + 280), 0);  // this+280 地图条目数组 end
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      *(this + 278) = result;  // 写字段 this+278 ← result
    }
  }
  else
  {
    pList1120 = *(this + 280);  // 读字段 fld_e280 = this+280（pMapEntryVecEnd）
    *((uint8_t *)this + 1116) = 0;  // 写字段 this[1116]（宽1字节）
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pList1120 + 64))(pList1120, 1);  // 虚调用 vt+64（pList1120）读游标登记(跳过包头)
    if ( nBigStateMirror960 == 2 )
    {
      v10 = *this;
      if ( *((uint8_t *)this + 1108) != 0 )  // this+1108 子对象槽
        return (*(int (/*thiscall*/ **)(int *, uint32_t))(v10 + 196))(this, *(uint32_t *)*(this + 36));  // this+36 物品状态字
      else
        return (*(int (/*thiscall*/ **)(int *, uint32_t))(v10 + 196))(this, *(this + 34));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x6294F0 sub_6294F0 —— 【龙头·喷火】火焰粒子定位演播
//    取 +876 粒子件虚 12 复位后，以自身高(虚 192)×0.8 + 虚 128 求点经虚 40 定位、虚 92 取坐标，sub_4600B0 播演并释放临时串。
// ------------------------------------------------------------
void /*thiscall*/ sub_6294F0(uint32_t *this)  // sub_6294F0 —— 【龙头·喷火】火焰粒子定位演播
{
  int fld_e219; // eax
  int fld_e2192; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *fld_e29; // ecx
  uint8_t v8[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  float v10; // [esp+14h] [ebp-14h]
  int v11; // [esp+18h] [ebp-10h]
  int v12; // [esp+24h] [ebp-4h]

  fld_e219 = *(this + 219);  // 读字段 fld_e219 = this+219
  if ( fld_e219 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e219 + 12))(fld_e219, 0);  // 虚调用 vt+12（fld_e219 虚表槽）
    fld_e2192 = *(uint32_t *)*(this + 219);  // this+876〔粒子件虚〕
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 192))(this);  // 虚调用 vt+192（this）取尺寸/包围盒
    v4 = *this;
    v10 = (double)v11 * 0.80000001;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)((double)v11 + v10));  // 虚调用 vt+124（this）目标坐标y下界
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2192 + 40))(*(this + 219), v6);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v8);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v12 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v8);  // sub_4600B0 —— 演播层注册(槽号)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
  }
}



// ------------------------------------------------------------
// 0x6295C0 CNDragonHeadSideFlame__vmt14C —— 【龙头·喷火】状态机主循环 vmt14C
//    状态(+960)=2：当前件为帧表[1] 时，其 +170 有效则虚 560(0,0,0,0) 熄火；否则 +680(HP)>0 时按朝向(虚 152) 取 ±1124 横偏与 +1128 高度，
//    经 +1120 粒子件虚 40/92 定位后 sub_4600B0 播焰并以 +1112+500 节流虚 352；状态=0：当前件为 +136 且 5 秒节流下虚 756 与 rand%100<50 成立时虚 560(2,0,0,0) 点火。
// ------------------------------------------------------------
void /*thiscall*/ CNDragonHeadSideFlame__vmt14C(int this)  // 函数定义: 位置采样
{
  int nBigStateMirror960; // eax  | +0x03C0 → 大状态镜像/状态槽（CNDragonHeadSideFlame；va=006295C0）
  int pFrameList144; // edi  | +0x0090 → 帧件/子对象列表基址（CNDragonHeadSideFlame；va=006295C0）
  int pThis_98; // eax
  int nListCnt1124; // edi  | +0x0464 → 名单计数（625C40 清 0）【推断】（证据 va=006295C0）（CNDragonHeadSideFlame；va=006295C0）
  int pList1120; // ebx  | +0x0460 → 名单/缓冲起点（CNDragonHeadSideFlame；va=006295C0）
  int v7; // edx
  void *v8; // eax
  int pThis_78; // [esp-10h] [ebp-34h]
  int pThis_1; // [esp-Ch] [ebp-30h]
  int nListCap1128; // [esp-8h] [ebp-2Ch]  | +0x0468 → 名单容量（625C40 清 0）【推断】（证据 va=006295C0）（CNDragonHeadSideFlame；va=006295C0）
  void *v12[7]; // [esp+8h] [ebp-1Ch] BYREF

  CNMapObject__vmt14C((int *)this);
  nBigStateMirror960 = *(uint32_t *)(this + 960);  // 读字段 fld_3C0 = this+960（nBigStateMirror960）
  if ( nBigStateMirror960 != 0 )
  {
    if ( nBigStateMirror960 == 2 )
    {
      pFrameList144 = *(uint32_t *)(this + 144);  // 读字段 fld_90 = this+144（pFrameList144）
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *(uint32_t *)(pFrameList144 + 4) )  // 虚调用 vt+200（this）取值比较
      {
        if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) != 0 )  // 虚调用 vt+200（this）取值比较
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
            (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
        }
        else if ( *(int *)(this + 680) > 0 )  // this+680 表现/名字快照[0]
        {
          pThis_98 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 虚调用 vt+152（this）取值(参数)
          nListCnt1124 = *(uint32_t *)(this + 1124);  // 读字段 fld_464 = this+1124（nListCnt1124）
          if ( pThis_98 != 1 )
            nListCnt1124 = -nListCnt1124;
          pList1120 = **(uint32_t **)(this + 1120);  // this+1120 名单/缓冲起点
          nListCap1128 = *(uint32_t *)(this + 1128) + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
          pThis_1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 124))(this) + 1;  // 虚调用 vt+124（this）目标坐标y下界
          pThis_78 = nListCnt1124 + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
          (*(void (/*thiscall*/ **)(uint32_t))(pList1120 + 40))(*(uint32_t *)(this + 1120));  // this+1120 名单/缓冲起点
          (*(void (/*thiscall*/ **)(uint32_t, void **))(**(uint32_t **)(this + 1120) + 92))(*(uint32_t *)(this + 1120), v12);  // this+1120 名单/缓冲起点
          v7 = *(uint32_t *)this;
          v12[6] = nullptr;
          v8 = (void *)(*(int (/*thiscall*/ **)(int, int, uint32_t, void **))(v7 + 80))(this, 2, 0, v12);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
          sub_4600B0(v8, pThis_78, pThis_1, nListCap1128);  // sub_4600B0 —— 演播层注册(槽号)
          if ( *(uint32_t *)(this + 1112) + 500 < (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
          {
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);  // 虚调用 vt+352（this 虚表槽）
            *(uint32_t *)(this + 1112) = sub_699000(this + 36);  // sub_699000 —— 【clock_now(clk)】
          }
          sub_5E5260(v12);  // 调 动画子对象清理临时缓冲
        }
      }
    }
  }
  else if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) == *(uint32_t *)(this + 136)  // 虚调用 vt+200（this）取值比较
         && *(uint32_t *)(this + 1100) + 5000 < (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 756))(this) != 0  // 虚调用 vt+756（this 虚表槽）
      && rand() % 100 < 50  // 调 取伪随机数
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
    {
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 2, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
    }
    *(uint32_t *)(this + 1100) = sub_699000(this + 36);  // sub_699000 —— 【clock_now(clk)】
  }
}



// ------------------------------------------------------------
// 0x6297C0 CNDragonHeadSide__vmt2B4 —— 【龙头炮台】击破收尾 vmt2B4
//    +680(HP) ≤ +1104 且 +1108=0 时：虚 196 回帧表[0]、sub_6294F0 撒焰、置 +1108 并按 +1040 名经虚 212 播音；
//    HP≤0 时存活则虚 212 播 +1040 名、经虚 744 与虚 312 收尾后再 sub_6294F0；末若原态(+960)=2 且存活则虚 560(0,0,0,0) 熄火。
// ------------------------------------------------------------
void /*thiscall*/ CNDragonHeadSide__vmt2B4(uint32_t **this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int v7; // ebx
  int pThis_104; // eax
  int v9; // ebx
  int pThis_1042; // eax

  if ( (int)*(this + 170) <= (int)*(this + 276) && *((uint8_t *)this + 1108) == 0 )  // this+1108〔pAttach1108(推断)〕等 3 字段
  {
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 36));  // this+36 物品状态字
    sub_6294F0(this);  // sub_6294F0 —— 【龙头·喷火】火焰粒子定位演播
    *((uint8_t *)this + 1108) = 1;  // 写字段 this+1108（pAttach1108）
    if ( sub_41ACF0(this + 260) != 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    {
      v7 = (int)*this;
      pThis_104 = sub_41ACF0(this + 260);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      (*(void (/*thiscall*/ **)(uint32_t **, int, int, uint32_t, uint32_t))(v7 + 212))(this, pThis_104, -1, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
    }
  }
  if ( (int)*(this + 170) <= 0 )  // this+680〔nSnapshot680〕
  {
    if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
    {
      if ( sub_41ACF0(this + 260) != 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      {
        v9 = (int)*this;
        pThis_1042 = sub_41ACF0(this + 260);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        (*(void (/*thiscall*/ **)(uint32_t **, int, int, uint32_t, uint32_t))(v9 + 212))(this, pThis_1042, -1, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
      }
      ((void (/*thiscall*/ *)(uint32_t **))(*this)[186])(this);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[78])(this, 0);
    }
    sub_6294F0(this);  // sub_6294F0 —— 【龙头·喷火】火焰粒子定位演播
  }
  if ( *(this + 240) == (uint32_t *)2 && ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // this+240 动画同步参数 B
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[140])(this, 0, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x6298C0 sub_6298C0 —— 目标扫描判定（带朝向）
//    以 sub_4E7F30(this, nArg2, nArg3) 收集候选后逐个比较：pszArg4 非 0 时按朝向(虚 152) 判 x 越界（≥ 或 ≤ 自身虚 120），
//    pszArg4 为 0 时判 y 越界（自身虚 124 < 目标虚 124），命中即释放列表返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_6298C0(uint32_t *this, signed int nArg2, signed int nArg3, char pszArg4)  // sub_6298C0 —— 目标扫描判定（带朝向）
{
  int v5; // eax
  int *v6; // edi
  int pObj; // ecx
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
  sub_4E7F30(this, nArg2, nArg3, (int)v11);  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  v6 = (int *)Block;
  v16 = v5;
  if ( Block != v13 )
  {
    while ( 1 )  // 无限循环
    {
      pObj = *v6;
      if ( pszArg4 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚调用 vt+120（pObj）转发(对象+缓冲)
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 虚调用 vt+152（this）取值(参数)
        {
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 && v8 >= v16 )  // 虚调用 vt+152（this）取值(参数)
          {
LABEL_5:
            if ( Block != nullptr )  // 若 Block 有效（非空）
              j__free(Block);  // 释放堆块
            return 1;  // 返回 1(成功)
          }
        }
        else if ( v8 <= v16 )
        {
          goto LABEL_5;
        }
      }
      else
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 虚调用 vt+124（pObj）目标坐标y下界
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) < v10 )  // 虚调用 vt+124（this）目标坐标y下界
          goto LABEL_5;
      }
      if ( ++v6 == v13 )
      {
        v6 = (int *)Block;
        break;
      }
    }
  }
  if ( v6 != nullptr )  // 若 v6 有效（非空）
    j__free(v6);  // 释放堆块
  return 0;
}



// ------------------------------------------------------------
// 0x6299C0 CNDragonHeadSide__vmt2F4 —— 【龙头】双段扫描开关 vmt2F4
//    +1109（首轮标志）为真走 sub_6298C0(200,50,1)，否则走 sub_6298C0(100,200,0)——横/纵扫描参数切换。
// ------------------------------------------------------------
char /*thiscall*/ CNDragonHeadSide__vmt2F4(int this)  // 实现：(龙头)双段扫描开关 vmt2F4
{
  if ( *(uint8_t *)(this + 1109) != 0 )  // this+1109 双段扫描首轮标志
    return sub_6298C0((uint32_t *)this, 200, 50, 1);  // sub_6298C0 —— 目标扫描判定（带朝向）
  else
    return sub_6298C0((uint32_t *)this, 100, 200, 0);  // sub_6298C0 —— 目标扫描判定（带朝向）
}



// ============================================================
// 【分区 13】观察者之眼与水晶柱（0x6299F0-0x62A100）
// 证据: BISHOP_EYE（主教之眼启动音）；CNCystalPillar（水晶柱）/ CNEyeofObserver /
//       CNActiveObserver（固定/主动观察者，视野触发体）
// ============================================================

// ------------------------------------------------------------
// 0x6299F0 CNCystalPillar__vmt2B4 —— 【水晶柱】击破播音 vmt2B4
//    基类 CNMapObject__vmt2B4 后，若 +1040 名（sub_41ACF0 取串）非空则经虚 212 播放该 TAG。
// ------------------------------------------------------------
int /*thiscall*/ CNCystalPillar__vmt2B4(int *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int result; // eax
  int v8; // ebx
  int pThis_104; // eax

  CNMapObject__vmt2B4(this, nArg2, nArg3, nArg4, nArg5, nArg6);
  result = sub_41ACF0(this + 260);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v8 = *this;
    pThis_104 = sub_41ACF0(this + 260);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    return (*(int (/*thiscall*/ **)(int *, int, int, uint32_t, uint32_t))(v8 + 212))(this, pThis_104, -1, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
  }
  return result;
}



// ------------------------------------------------------------
// 0x629A50 CNCystalPillar__vmt2E4 —— 【水晶柱】待机层帧 vmt2E4
//    直接虚 204(100, 帧表[1]) 设层帧（无其他初始化动作）。
// ------------------------------------------------------------
int /*thiscall*/ CNCystalPillar__vmt2E4(uint32_t *this)  // 实现：(水晶柱)待机层帧 vmt2E4
{
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           *(uint32_t *)(*(this + 36) + 4),  // this+36 物品状态字
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x629A70 CNCystalPillar__vmt200 —— 【水晶柱】受击摘件 vmt200
//    先经虚 208 摘除帧表[1] 件，再走基类 CNRDPassiveObject__vmt200。
// ------------------------------------------------------------
int /*thiscall*/ CNCystalPillar__vmt200(int *this, int nArg2, float *pArg3, char pszArg4)  // 实现：(水晶柱)受击摘件 vmt200
{
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 36) + 4));  // 虚调用 vt+208（this）动画件回挂
  return CNRDPassiveObject__vmt200(this, nArg2, pArg3, pszArg4);  // 返回 调 CNRDPassiveObject__vmt200
}



// ------------------------------------------------------------
// 0x629AB0 sub_629AB0 —— 复位
//    虚 372(100) 回待机并清 +972（观察者族计数器）。
// ------------------------------------------------------------
int /*thiscall*/ sub_629AB0(uint32_t *this)  // sub_629AB0 —— 复位
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
  *(this + 243) = 0;  // 写字段 this+243 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x629AD0 CNEyeofObserver__vmt1D8 —— 【观察者之眼】状态切换 vmt1D8
//    基类后 nArg3==0 → 虚 196 应用 +136 件；nArg3==2 → 虚 580 生成 1051 号演出（末参 4）。
// ------------------------------------------------------------
int /*userpurge*/ CNEyeofObserver__vmt1D8@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：(观察者之眼)状态切换 vmt1D8
{
  int result; // eax

  CNRDPassiveObject__vmt1D8(pArg1, nArg2, nArg3, nArg3, nArg4, nArg5, nArg6);
  if ( nArg3 == 0 )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, pArg1[34]);  // 虚调用 vt+196（pArg1）物件非空判定
  result = nArg3 - 2;
  if ( nArg3 == 2 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
             pArg1,
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
// 0x629B40 CNEyeofObserver__vmt14C —— 【观察者之眼】待机扫描 vmt14C
//    基类后状态(+960)=0、当前件(虚 200)为 +136 时，以 +972+1000 节流；虚 708 与虚 308 均真则虚 560(2,0,0,0) 启动并刷新 +972。
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNEyeofObserver__vmt14C(unsigned int *this)  // 函数定义: 位置采样
{
  unsigned int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  result = *(this + 240);  // 读字段 result = this+240（nSyncArgB）
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 200))(this);  // 虚调用 vt+200（this）取值比较
    if ( result == *(this + 34) )  // this+136〔nCtx136(推断)〕
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( *(this + 243) + 1000 < result )  // this+972〔uCfgD972(推断)〕
      {
        if ( (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 708))(this) != 0  // 虚调用 vt+708（this 虚表槽）
          && (*(uint8_t (/*thiscall*/ **)(unsigned int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
        {
          (*(void (/*thiscall*/ **)(unsigned int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
        }
        result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        *(this + 243) = result;  // 写字段 this+243 ← result
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x629BC0 CNEyeofObserver__vmt12C —— 注销（自身时虚 308）
//    nArg2 为自身时虚 308 停用，末走基类 CNRDPassiveObject__vmt12C（同 CNDragonHeadSide__vmt12C 结构）。
// ------------------------------------------------------------
void /*thiscall*/ CNEyeofObserver__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 注销
{
  if ( this == (uint32_t *)nArg2 )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  CNRDPassiveObject__vmt12C(this, nArg2);
}



// ------------------------------------------------------------
// 0x629BF0 sub_629BF0 —— 【观察者】全面复位
//    虚 372(100) 后清 +984/+972/+973/+980/+976，并经虚 384 取参数表第 0 项写入 +680/+684（重置血量）。
// ------------------------------------------------------------
int /*thiscall*/ sub_629BF0(uint32_t *this)  // sub_629BF0 —— 【观察者】全面复位
{
  int v2; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 372))(this, 100);  // 虚调用 vt+372（this）数值写入
  v2 = *this;
  *(this + 246) = 0;  // 写字段 this+246 ← 0
  *((uint8_t *)this + 972) = 0;  // 写字段 this+972（uCfgD972）
  *((uint8_t *)this + 973) = 0;  // 写字段 this+973（bLanded973）
  *(this + 245) = 0;  // 写字段 this+245 ← 0
  *(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v2 + 384))(this, 0);  // 虚函数调用 槽+384：槽数组 getter（+348 起，越界返回 0）
  *(this + 170) = result;  // 写字段 this+170 ← result
  *(this + 171) = result;  // 写字段 this+171 ← result
  return result;
}



// ------------------------------------------------------------
// 0x629C40 sub_629C40 —— 释放 +984 句柄
//    对 +984 句柄走虚 0 析构(参数 1) 并清零（句柄回收样板，同 sub_629010）。
// ------------------------------------------------------------
int /*thiscall*/ sub_629C40(uint32_t *this)  // sub_629C40 —— 释放 +984 句柄
{
  int (/*thiscall*/ ***fld_e246)(uint32_t, int); // ecx
  int result; // eax

  fld_e246 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 246);  // this+984〔aStateBlk984(推断)〕
  if ( fld_e246 != nullptr )  // 若 fld_e246 有效（非空）
    result = (**fld_e246)(fld_e246, 1);  // 调 fld_e246 的虚函数（vt+0）
  *(this + 246) = 0;  // 写字段 this+246 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x629C60 CNActiveObserver__vmtC —— 【主动观察者】构造 vmtC
//    基类 CNRDPassiveObject__vmtC 后直接虚 560(2,0,0,0) 进入状态 2（主动扫描）。
// ------------------------------------------------------------
int /*thiscall*/ CNActiveObserver__vmtC(int *this)  // 实现：(主动观察者)构造 vmtC
{
  CNRDPassiveObject__vmtC(this);
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 2, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
}



// ------------------------------------------------------------
// 0x629C80 CNActiveObserver__vmt1D8
//   【观察者】BISHOP_EYE —— 主教之眼启动音
// ------------------------------------------------------------
void */*userpurge*/ CNActiveObserver__vmt1D8@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：(观察者)BISHOP_EYE —— 主教之眼启动音
{
  void *result; // eax

  CNRDPassiveObject__vmt1D8((uint32_t *)pArg1, nArg2, nArg3, nArg3, nArg4, nArg5, nArg6);
  if ( nArg3 == 0 )
    return (void *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(pArg1 + 136));  // 虚调用 vt+196（pArg1）物件非空判定
  result = (void *)(nArg3 - 2);
  if ( nArg3 == 2 )
  {
    sub_4926A0(**(uint32_t **)(pArg1 + 144));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, **(uint32_t **)(pArg1 + 144));  // 虚调用 vt+196（pArg1）物件非空判定
    return sub_432EA0("BISHOP_EYE", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  }
  return result;
}



// ------------------------------------------------------------
// 0x629D00 sub_629D00 —— 【观察者】准星粒子定位演播
//    —— 与 ·sub_6294F0 同构（差异：仅对象类不同）；取 +876 件虚 12 复位后按自身高(虚 192)×0.8 + 虚 128 定位，sub_4600B0 播演。
// ------------------------------------------------------------
void /*thiscall*/ sub_629D00(uint32_t *this)  // sub_629D00 —— 【观察者】准星粒子定位演播
{
  int fld_e219; // eax
  int fld_e2192; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *fld_e29; // ecx
  uint8_t v8[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  float v10; // [esp+14h] [ebp-14h]
  int v11; // [esp+18h] [ebp-10h]
  int v12; // [esp+24h] [ebp-4h]

  fld_e219 = *(this + 219);  // 读字段 fld_e219 = this+219
  if ( fld_e219 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e219 + 12))(fld_e219, 0);  // 虚调用 vt+12（fld_e219 虚表槽）
    fld_e2192 = *(uint32_t *)*(this + 219);  // this+876〔件虚〕
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 192))(this);  // 虚调用 vt+192（this）取尺寸/包围盒
    v4 = *this;
    v10 = (double)v11 * 0.80000001;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)((double)v11 + v10));  // 虚调用 vt+124（this）目标坐标y下界
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2192 + 40))(*(this + 219), v6);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v8);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v12 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v8);  // sub_4600B0 —— 演播层注册(槽号)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
  }
}



// ------------------------------------------------------------
// 0x629DD0 CNActiveObserver__vmt2B4 —— 【主动观察者】击破收尾 vmt2B4
//    +680(HP)≤0 时若存活则虚 312(0) 停用，随后 sub_629D00 做准星粒子定位。
// ------------------------------------------------------------
void /*thiscall*/ CNActiveObserver__vmt2B4(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  if ( (int)*(this + 170) <= 0 )  // this+680〔nSnapshot680〕
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    sub_629D00(this);  // sub_629D00 —— 【观察者】准星粒子定位演播
  }
}



// ------------------------------------------------------------
// 0x629E00 sub_629E00 —— 对称矩形范围判定
//    以 sub_4E7F30(this, nArg2, nArg3) 收集候选，逐个判 (x±nArg2, y±nArg3) 是否落在以自身(虚 120/124) 为中心的矩形内，命中释放列表返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_629E00(uint32_t *this, signed int nArg2, signed int nArg3)  // sub_629E00 —— 对称矩形范围判定
{
  int v5; // eax
  uint32_t *Block2; // edi
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
  sub_4E7F30(this, nArg2, nArg3, (int)v10);  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
  v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
  Block2 = Block;
  v14 = v5;
  if ( Block == v12 )
  {
LABEL_9:
    if ( Block2 != nullptr )  // 若 Block2 有效（非空）
      j__free(Block2);  // 释放堆块
    return 0;
  }
  else
  {
    v15 = v17 - nArg2;  // 计算 v15 = v17 - nArg2
    while ( 1 )  // 无限循环
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 120))(*Block2);  // 虚调用 vt+120（Block2）转发(对象+缓冲)
      v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 124))(*Block2);  // 虚调用 vt+124（Block2）目标坐标y下界
      if ( v7 >= v15 && v7 <= nArg2 + v17 && v8 >= v14 - nArg3 && v8 <= nArg3 + v14 )  // 判定 v7 >= v15 且 v7 <= nArg2 且 v8 >= v14
        break;
      if ( ++Block2 == v12 )
      {
        Block2 = Block;
        goto LABEL_9;
      }
    }
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
    return 1;  // 返回 1(成功)
  }
}



// ------------------------------------------------------------
// 0x629EF0 sub_629EF0 —— 静态朝向扫描
//    以 sub_4E7F30(this, 320, 120) 收集后逐个比较目标虚 120 与自身虚 120：偏左虚 148(0)、偏右虚 148(1)。
// ------------------------------------------------------------
void /*thiscall*/ sub_629EF0(uint32_t *this)  // sub_629EF0 —— 静态朝向扫描
{
  uint32_t *Block2; // edi
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
  sub_4E7F30(this, 320, 120, (int)v4);  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
  Block2 = Block;
  if ( Block != v6 )
  {
    do
    {
      v3 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 120))(*Block2);  // 虚调用 vt+120（Block2）转发(对象+缓冲)
      if ( v3 < (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) )  // 虚调用 vt+120（this）转发(对象+缓冲)
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 148))(this, 0);  // 虚调用 vt+148（this）位置/朝向写入
      else
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 148))(this, 1);  // 虚调用 vt+148（this）位置/朝向写入
      ++Block2;  // 计数自增 Block2
    }
    while ( Block2 != v6 );  // 循环直到 Block2 != v6
    Block2 = Block;
  }
  if ( Block2 != nullptr )  // 若 Block2 有效（非空）
    j__free(Block2);  // 释放堆块
}



// ------------------------------------------------------------
// 0x629F90 sub_629F90 —— 斜向半开区间范围判定
//    sub_4E7F30(this, nArg2, nArg3) 收集后：朝向(虚 152)=0 取 x∈[自身x-nArg2, 自身x) 且 y∈[y-nArg3, y+nArg3]；
//    =1 取 x∈(自身x, 自身x+nArg2] 同 y 区间；命中释放列表返回 1（nArg4 未使用）。
// ------------------------------------------------------------
char /*thiscall*/ sub_629F90(uint32_t *this, signed int nArg2, signed int nArg3, int nArg4)  // sub_629F90 —— 斜向半开区间范围判定
{
  int v5; // eax
  int v6; // edx
  int v7; // eax
  uint32_t *Block2; // ebx
  int v10; // edi
  int v11; // ebx
  char v12[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  uint32_t *v14; // [esp+14h] [ebp-20h]
  int v15; // [esp+18h] [ebp-1Ch]
  int v16; // [esp+1Ch] [ebp-18h]
  int v17; // [esp+20h] [ebp-14h]
  uint32_t *Block3; // [esp+24h] [ebp-10h]
  int v19; // [esp+30h] [ebp-4h]

  Block = nullptr;
  v14 = nullptr;
  v15 = 0;
  v19 = 0;
  sub_4E7F30(this, nArg2, nArg3, (int)v12);  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  v6 = *this;
  v17 = v5;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *))(v6 + 124))(this);  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  Block2 = Block;
  v16 = v7;
  Block3 = Block;
  if ( Block == v14 )
  {
LABEL_2:
    if ( Block2 != nullptr )  // 若 Block2 有效（非空）
      j__free(Block2);  // 释放堆块
    return 0;
  }
  else
  {
    while ( 1 )  // 无限循环
    {
      v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 120))(*Block2);  // 虚调用 vt+120（Block2）转发(对象+缓冲)
      v11 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 124))(*Block2);  // 虚调用 vt+124（Block2）目标坐标y下界
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0  // 虚调用 vt+152（this）取值(参数)
        && v10 >= v17 - nArg2
        && v10 < v17
        && v11 >= v16 - nArg3
        && v11 <= nArg3 + v16 )
      {
        break;
      }
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1  // 虚调用 vt+152（this）取值(参数)
        && v10 <= v17 + nArg2
        && v10 > v17
        && v11 >= v16 - nArg3
        && v11 <= nArg3 + v16 )
      {
        break;
      }
      if ( ++Block3 == v14 )
      {
        Block2 = Block;
        goto LABEL_2;
      }
      Block2 = Block3;
    }
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
    return 1;  // 返回 1(成功)
  }
}



// ------------------------------------------------------------
// 0x62A0E0 CNEyeofObserver__vmt2C4 —— 【观察者之眼】范围测试转发 vmt2C4
//    直接转发 sub_629E00(this, 320, 120)（对称矩形 320×120）。
// ------------------------------------------------------------
char /*thiscall*/ CNEyeofObserver__vmt2C4(uint32_t *this)  // 实现：(观察者之眼)范围测试转发 vmt2C4
{
  return sub_629E00(this, 320, 120);  // sub_629E00 —— 对称矩形范围判定
}



// ------------------------------------------------------------
// 0x62A0F0 CNActiveObserver__vmt2C4 —— 【主动观察者】范围测试转发 vmt2C4
//    直接转发 sub_629F90(this, 320, 120, 1)（带朝向的半开矩形）。
// ------------------------------------------------------------
char /*thiscall*/ CNActiveObserver__vmt2C4(uint32_t *this)  // 实现：(主动观察者)范围测试转发 vmt2C4
{
  return sub_629F90(this, 320, 120, 1);  // sub_629F90 —— 斜向半开区间范围判定
}



// ------------------------------------------------------------
// 0x62A100 CNActiveObserver__vmt14C —— 【观察者之眼】主循环与 UNDERFOOT 演出
//    基类 sub_600890(CNRDPassiveObject__vmt14C) 后：首轮(+973=0) 走 sub_629EF0 定朝向，虚 128>50 时 sub_498E00 抬高 10；状态(+960)=2 且当前件为帧表[0] 时虚 560(0,0,0,0) 关灯并清 +972，
//    经 sub_42FCB0(228)+sub_431860 载 …/Trap/EyeofObserver/Animation/UNDERFOOT_DarkCircleEffect.ani（sub_44B6C0(284)+sub_44E1F0 池化、sub_45FE80 挂载）并对场景表中命中者虚 760(5,1120403456,5,pArg1,1) 施压；
//    当前件帧号达总帧-2 时同法载 UNDERFOOT_EyeShineEffect.ani、按朝向 ±20 定位并置 +972=1；状态非 2 时以 +980+5000 节流虚 560(2,0,0,0)。
// ------------------------------------------------------------
char /*usercall*/ sub_62A100@<al>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：(观察者之眼)主循环与 UNDERFOOT 演出
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
  int pObj; // edi
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
  int nArg22; // [esp-4h] [ebp-1Ch]
  int v32; // [esp+8h] [ebp-10h]

  sub_600890();  // 【CNRDPassiveObject__vmt14C】
  if ( pArg1[973] == 0 )
  {
    sub_629EF0(pArg1);  // sub_629EF0 —— 静态朝向扫描
    pArg1[973] = 1;
  }
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 128))(pArg1) > 50 )  // 虚调用 vt+128（pArg1）目标坐标y上界
  {
    v30 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 128))(pArg1) - 10;  // 虚调用 vt+128（pArg1）目标坐标y上界
    v29 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 124))(pArg1);  // 虚调用 vt+124（pArg1）目标坐标y下界
    v3 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 120))(pArg1);  // 虚调用 vt+120（pArg1）转发(对象+缓冲)
    sub_498E00(v3, v29, v30);  // sub_498E00 —— 坐标三分量设置（+4/+8/+12，带有效性与等值判定）
  }
  v4 = *((uint32_t *)pArg1 + 240);  // 读字段 v4 = pArg1+240（nSyncArgB）
  if ( v4 != 0 )
  {
    v5 = v4 - 2;  // 计算 v5 = v4 - 2
    if ( v5 == 0 )
    {
      v6 = *((uint32_t **)pArg1 + 36);
      v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1);  // 虚调用 vt+200（pArg1）取值比较
      if ( v5 == *v6 )
      {
        nArg22 = nArg2;
        if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 170) != 0  // 虚调用 vt+200（pArg1）取值比较
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308（pArg1）是否本地玩家
        {
          v7 = 0;
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pArg1 + 560))(  // 虚调用 vt+560（pArg1 虚表槽）
            pArg1,
            0,
            0,
            0,
            0,
            nArg2);
          pArg1[972] = 0;
          if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
            v7 = sub_431860(  // sub_431860 —— 动画件构造（资源 id 版）
                   (char)"PassiveObject/MapObject/Trap/EyeofObserver/Animation/UNDERFOOT_DarkCircleEffect.ani",  // 动画 .ani PassiveObject/MapObject/Trap/EyeofObserver/Animation/UND…
                   1);
          if ( sub_44B6C0(284) != 0 )  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
            v8 = (int *)sub_44E1F0(v7, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
          else
            v8 = nullptr;
          sub_45FE80(*((uint32_t *)pArg1 + 29), (int)v8, 2, 0, (int)v8, (int)pArg1, 0);  // sub_45FE80 —— 对象注册
          v9 = *v8;
          nArg22 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚调用 vt+128（pArg1）目标坐标y上界
          v10 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 124))(pArg1);  // 虚调用 vt+124（pArg1）目标坐标y下界
          v11 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 120))(pArg1, v10);  // 虚调用 vt+120（pArg1）转发(对象+缓冲)
          (*(void (/*thiscall*/ **)(int *, int))(v9 + 112))(v8, v11);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
          if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 708))(pArg1) != 0 )  // 虚调用 vt+708（pArg1 虚表槽）
          {
            for ( i = 0; ; ++i )
            {
              v13 = *((uint32_t *)pArg1 + 29);  // 读字段 v13 = pArg1[29]
              v14 = *(uint32_t *)(v13 + 120);  // 读字段 v14 = v13+120（pAnimObj）
              v15 = v13 + 116;  // 计算 v15 = v13 + 116
              v16 = v14 != 0 ? (*(uint32_t *)(v15 + 8) - v14) >> 2 : 0;  // 向量元素数 = (end−begin)/4
              if ( i >= v16 )
                break;
              (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 80))(pArg1, i);  // 虚调用 vt+80（pArg1）读 4 字节
              pObj = sub_425A00(nArg22);  // sub_425A00 —— 元素取值（+30 组）
              nArg22 = 273;
              if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 40))(pObj) != 0 )  // 虚调用 vt+40（pObj）条件查询(273等)
                (*(void (/*thiscall*/ **)(int, int, int, int, uint8_t *, int))(*(uint32_t *)pObj + 760))(  // 虚调用 vt+760（pObj 虚表槽）
                  pObj,
                  5,
                  1120403456,  // 浮点常量 100.0f
                  5,
                  pArg1,
                  1);
            }
          }
        }
        v18 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1) + 148);  // 虚调用 vt+200（pArg1）取值比较
        v19 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1);  // 虚调用 vt+200（pArg1）取值比较
        v20 = *(uint32_t *)(v19 + 44);  // 读字段 v20 = v19+44（nExpireMs）
        if ( v20 != 0 )
          v21 = (*(uint32_t *)(v19 + 48) - v20) / 88;
        else
          v21 = 0;
        v5 = v21 - 2;  // 计算 v5 = v21 - 2
        if ( v18 == v5 )
        {
          LOBYTE(v5) = pArg1[972];  // 调 取 16 位值低 8 位
          if ( (uint8_t)v5 == 0 )
          {
            if ( sub_42FCB0(228) != 0 )  // sub_42FCB0 —— 结果 = CRT 一次性初始化
              v22 = sub_431860(  // sub_431860 —— 动画件构造（资源 id 版）
                      (char)"PassiveObject/MapObject/Trap/EyeofObserver/Animation/UNDERFOOT_EyeShineEffect.ani",  // 动画 .ani PassiveObject/MapObject/Trap/EyeofObserver/Animation/UND…
                      1);
            else
              v22 = 0;
            if ( sub_44B6C0(284) != 0 )  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
              v23 = (int *)sub_44E1F0(v22, 1);  // sub_44E1F0 —— CNRDPooledObject 构造（虚表覆盖壳）
            else
              v23 = nullptr;
            sub_45FE80(*((uint32_t *)pArg1 + 29), (int)v23, 2, 0, (int)v23, (int)pArg1, 0);  // sub_45FE80 —— 对象注册
            if ( (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 152))(pArg1, nArg22) != 0 )  // 虚调用 vt+152（pArg1）取值(参数)
              v24 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 120))(pArg1) + 20;  // 虚调用 vt+120（pArg1）转发(对象+缓冲)
            else
              v24 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 120))(pArg1) - 20;  // 虚调用 vt+120（pArg1）转发(对象+缓冲)
            v25 = *v23;
            v32 = v24;
            v26 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 128))(pArg1);  // 虚调用 vt+128（pArg1）目标坐标y上界
            v27 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 124))(pArg1, v26);  // 虚调用 vt+124（pArg1）目标坐标y下界
            LOBYTE(v5) = (*(int (/*thiscall*/ **)(int *, int, int))(v25 + 112))(v23, v32, v27);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
            pArg1[972] = 1;
          }
        }
      }
    }
  }
  else
  {
    v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 200))(pArg1);  // 虚调用 vt+200（pArg1）取值比较
    if ( v5 == *((uint32_t *)pArg1 + 34) )
    {
      v5 = sub_699000((int)(pArg1 + 36));  // 【clock_now(clk)】
      if ( *((uint32_t *)pArg1 + 245) + 5000 < v5 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 708))(pArg1) != 0  // 虚调用 vt+708（pArg1 虚表槽）
          && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 )  // 虚调用 vt+308（pArg1）是否本地玩家
        {
          (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 2, 0, 0, 0);  // 虚调用 vt+560（pArg1 虚表槽）
        }
        v5 = sub_699000((int)(pArg1 + 36));  // 【clock_now(clk)】
        *((uint32_t *)pArg1 + 245) = v5;  // 写字段 pArg1[245]（宽4字节）
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
// 0x62A470 CNLightBulb__vmt140 —— 【灯泡】发光粒子定位演播 vmt140
//    +1104 标志非 0 时，取 +972 粒子件以自身坐标(虚 120/124/128) 经虚 40 定位、虚 92 取值，再由虚 80 走 sub_4600B0 播演。
// ------------------------------------------------------------
void /*thiscall*/ CNLightBulb__vmt140(int *this)  // 实现：(灯泡)发光粒子定位演播 vmt140
{
  int fld_e243; // edi
  int v3; // edx
  void *v4; // eax
  int v5; // [esp-10h] [ebp-30h]
  int v6; // [esp-Ch] [ebp-2Ch]
  int v7; // [esp-8h] [ebp-28h]
  uint8_t v8[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v10; // [esp+1Ch] [ebp-4h]

  CNRDPassiveObject__vmt140(this);
  if ( *((uint8_t *)this + 276) != 0 )  // this+276 地图条目指针
  {
    fld_e243 = *(uint32_t *)*(this + 243);  // this+972〔uCfgD972(推断)〕
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t))(fld_e243 + 40))(*(this + 243));  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v8);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    v3 = *this;
    v10 = 0;
    v4 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, uint8_t *))(v3 + 80))(this, 2, 0, v8);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    sub_4600B0(v4, v5, v6, v7);  // sub_4600B0 —— 演播层注册(槽号)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
  }
}



// ------------------------------------------------------------
// 0x62A520 sub_62A520
//   【灯泡】Particle/light.ptl —— 灯光粒子
// ------------------------------------------------------------
int /*thiscall*/ sub_62A520(uint32_t *this)  // 实现：(灯泡)Particle/light.ptl —— 灯光粒子
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )  // 堆分配
  {
    if ( *(this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
      result = sub_4C3640(this + 91, "Particle/light.ptl", this);  // 资源路径 Particle/light.ptl
    else
      result = sub_4C3640(*(this + 91), "Particle/light.ptl", this);  // 资源路径 Particle/light.ptl
  }
  else
  {
    result = 0;
  }
  *(this + 243) = result;  // 写字段 this+243 ← result
  return result;
}



// ------------------------------------------------------------
// 0x62A5B0 sub_62A5B0 —— 【露滴】随机周期抽取
//    以 rand() 经 sub_4D33A0(LCG) 得 v：写 +976=0、+972=200×(v%30+5)（即 5~34 拍），并返回 v/30（【推断】另作他用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62A5B0(uint32_t *this)  // sub_62A5B0 —— 【露滴】随机周期抽取
{
  int v2; // eax
  int v4; // et2
  int nRand; // [esp+4h] [ebp-4h] BYREF

  nRand = rand();  // 调 取伪随机数
  v2 = sub_4D33A0(&nRand);  // sub_4D33A0 —— 掷 0..9999
  v4 = v2 % 30;
  *(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
  *(this + 243) = 200 * (v4 + 5);  // 写字段 this+243 ← 200 * (v4 + 5)
  return v2 / 30;  // 返回 v2 / 30
}



// ------------------------------------------------------------
// 0x62A600 CNWaterDrop__vmt14C —— 【露滴】滴落节流 vmt14C
//    基类后目标有效(+170) 时，若 clock_now > +972+976（时刻+周期）则重掷周期 200×(rand%30+5)、sub_4926A0 复位目标帧游标并刷新 +972 时刻。
// ------------------------------------------------------------
unsigned int /*thiscall*/ CNWaterDrop__vmt14C(uint32_t *this)  // 函数定义: 位置采样
{
  unsigned int result; // eax
  int v3; // eax

  CNRDPassiveObject__vmt14C((int)this);
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 虚调用 vt+200（this）取值比较
  if ( *(uint8_t *)(result + 170) != 0 )
  {
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( *(this + 244) + *(this + 243) < result )  // this+244 动画同步浮点参数
    {
      *(this + 244) = 200 * (rand() % 30 + 5);  // 写字段 this+244（fSyncValue） ← 200 * (rand() % 30 + 5)
      v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);  // 虚调用 vt+200（this）取值比较
      sub_4926A0(v3);  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      *(this + 243) = result;  // 写字段 this+243 ← result
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62A680 CNFreezingLuna__vmtC —— 【冻结月神】构造 vmtC
//    基类 CNMapObject__vmtC 后经虚 384 取参数表第 0 项写入 +680/+684（血量初始化）。
// ------------------------------------------------------------
int /*thiscall*/ CNFreezingLuna__vmtC(int *this)  // 实现：(冻结月神)构造 vmtC
{
  int result; // eax

  CNMapObject__vmtC(this);
  result = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 384))(this, 0);  // 虚调用 vt+384（this 虚表槽）
  *(this + 170) = result;  // 写字段 this+170 ← result
  *(this + 171) = result;  // 写字段 this+171 ← result
  return result;
}



// ------------------------------------------------------------
// 0x62A6B0 sub_62A6B0 —— 释放 +1128 句柄
//    对 +1128 句柄走虚 0 析构(参数 1) 并清零（句柄回收样板）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62A6B0(uint32_t *this)  // sub_62A6B0 —— 释放 +1128 句柄
{
  int (/*thiscall*/ ***fld_e282)(uint32_t, int); // ecx
  int result; // eax

  fld_e282 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 282);  // this+1128〔nListCap1128(推断)〕
  if ( fld_e282 != nullptr )  // 若 fld_e282 有效（非空）
    result = (**fld_e282)(fld_e282, 1);  // 调 fld_e282 的虚函数（vt+0）
  *(this + 282) = 0;  // 写字段 this+282 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x62A6D0 sub_62A6D0 —— 【冻结月神】周期生成冰锥
//    记 clock_now 入 +1116；存活(虚 308)时取场景进度字段（场景件+132→+108→+112），经 sub_460230 随机取点存 +1120，
//    再走 IRDCollisionObject__vmt250 以 (600,100) 参数与自身坐标/朝向生成物件，并自增 +1124 计数。
// ------------------------------------------------------------
int /*thiscall*/ sub_62A6D0(int *this)  // sub_62A6D0 —— 【冻结月神】周期生成冰锥
{
  int result; // eax
  int v3; // ebx
  uint32_t *v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int fld_e280; // [esp-1Ch] [ebp-28h]
  int v9; // [esp+4h] [ebp-8h]
  int v10; // [esp+8h] [ebp-4h]

  *(this + 279) = sub_699000((int)(this + 9));  // sub_699000 —— 【clock_now(clk)】
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    v3 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*this + 80))(this) + 132) + 108) + 112);  // 虚调用 vt+80（this）读 4 字节
    v4 = (uint32_t *)(*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 虚调用 vt+80（this）读 4 字节
    *(this + 280) = sub_460230(v4);  // sub_460230 —— 图标槽随机 id 分配（线性探测）
    v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + 1;  // 虚调用 vt+124（this）目标坐标y下界
    v6 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    fld_e280 = *(this + 280);  // 读字段 fld_e280 = this+280（pMapEntryVecEnd）
    v10 = v6;
    v7 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 虚调用 vt+152（this）取值(参数)
    IRDCollisionObject__vmt250(this, v3, (int)this, 600, 100, v3, v9, v5, v10, v7, 0, nullptr, 0, fld_e280, 0, 0, 0, 0);
    result = *(this + 281) + 1;  // this+1124〔nListCnt1124(推断)〕
    *(this + 281) = result;  // 写字段 this+281 ← result
  }
  return result;
}



// ------------------------------------------------------------
// 0x62A790 CNFreezingLuna__vmt14C —— 【冻结月神】生成节流 vmt14C
//    基类后若 +1104 件表元素 <2 且生成计数(+1124) <4，且 clock_now > +1116+6000（6 秒）时走 sub_62A6D0 生成。
// ------------------------------------------------------------
char /*thiscall*/ CNFreezingLuna__vmt14C(int *this)  // 函数定义: 位置采样
{
  unsigned int fld_e277; // eax
  int fld_e276; // ecx

  LOBYTE(fld_e277) = CNMapObject__vmt14C(this);  // 调 取 16 位值低 8 位
  fld_e276 = *(this + 276);  // 读字段 fld_e276 = this+276（pMapEntry）
  if ( (fld_e276 == 0 || (fld_e277 = (*(this + 277) - fld_e276) >> 2) < 2) && *(this + 281) < 4 )  // this+1108〔pAttach1108(推断)〕等 2 字段
  {
    fld_e277 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    if ( *(this + 279) + 6000 < fld_e277 )
      LOBYTE(fld_e277) = sub_62A6D0(this);  // sub_62A6D0 —— 【冻结月神】周期生成冰锥
  }
  return fld_e277;
}



// ------------------------------------------------------------
// 0x62A7E0 CNFreezingLuna__vmt2F4 —— 【冻结月神】重置 vmt2F4
//    释放 +1104 件表并清 +1108/+1112/+1116/+1120/+1124（其中 +1120 置 0xFFFF），虚 372(100) 后置 +676=1。
// ------------------------------------------------------------
int /*thiscall*/ CNFreezingLuna__vmt2F4(void **this, int nArg2)  // 实现：(冻结月神)重置 vmt2F4
{
  int (/*thiscall*/ **v3)(void **, int); // eax
  int result; // eax

  if ( *(this + 276) != nullptr )  // this+276 地图条目指针
    j__free(*(this + 276));  // 释放堆块
  *(this + 276) = nullptr;  // 写字段 this+276（pMapEntry） ← nullptr
  *(this + 277) = nullptr;  // 写字段 this+277 ← nullptr
  *(this + 278) = nullptr;  // 写字段 this+278 ← nullptr
  v3 = (int (/*thiscall*/ **)(void **, int))*this;
  *(this + 280) = (void *)0xFFFF;  // 写字段 this+280（pMapEntryVecEnd） ← (void *)0xFFFF
  *(this + 281) = nullptr;  // 写字段 this+281 ← nullptr
  *(this + 279) = nullptr;  // 写字段 this+279 ← nullptr
  result = v3[93](this, 100);
  *(this + 169) = (void *)1;  // 写字段 this+169 ← (void *)1
  return result;
}



// ------------------------------------------------------------
// 0x62A840 CNFreezingLuna__vmt140 —— 【冻结月神】切件 vmt140
//    基类 CNRDPassiveObject__vmt140 后虚 208 摘除帧表[0] 件，再虚 204(100, 帧表[0]) 重设层帧。
// ------------------------------------------------------------
int /*thiscall*/ CNFreezingLuna__vmt140(int this)  // 实现：(冻结月神)切件 vmt140
{
  CNRDPassiveObject__vmt140((uint8_t *)this);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, **(uint32_t **)(this + 144));  // 虚调用 vt+208（this）动画件回挂
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           **(uint32_t **)(this + 144),  // this+144 第 4 组·+1040 增量子倍率
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x62A880 sub_62A880 —— 血量重取（构造链残件）
//    经虚 384 取参数表第 0 项写入 +680/+684（与 sub_62A680 同构，无构造链）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62A880(uint32_t *this)  // sub_62A880 —— 血量重取（构造链残件）
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);  // 虚调用 vt+384（this 虚表槽）
  *(this + 170) = result;  // 写字段 this+170 ← result
  *(this + 171) = result;  // 写字段 this+171 ← result
  return result;
}



// ------------------------------------------------------------
// 0x62A8B0 sub_62A8B0 —— 【十字架】碎裂粒子定位演播
//    —— 与 ·sub_6294F0 同构（差异：仅对象类不同）；取 +876 件虚 12 复位后按自身高(虚 192)×0.8 + 虚 128 定位，sub_4600B0 播演。
// ------------------------------------------------------------
void /*thiscall*/ sub_62A8B0(uint32_t *this)  // sub_62A8B0 —— 【十字架】碎裂粒子定位演播
{
  int fld_e219; // eax
  int fld_e2192; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *fld_e29; // ecx
  uint8_t v8[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  float v10; // [esp+14h] [ebp-14h]
  int v11; // [esp+18h] [ebp-10h]
  int v12; // [esp+24h] [ebp-4h]

  fld_e219 = *(this + 219);  // 读字段 fld_e219 = this+219
  if ( fld_e219 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e219 + 12))(fld_e219, 0);  // 虚调用 vt+12（fld_e219 虚表槽）
    fld_e2192 = *(uint32_t *)*(this + 219);  // this+876〔件虚〕
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 192))(this);  // 虚调用 vt+192（this）取尺寸/包围盒
    v4 = *this;
    v10 = (double)v11 * 0.80000001;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)((double)v11 + v10));  // 虚调用 vt+124（this）目标坐标y下界
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2192 + 40))(*(this + 219), v6);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v8);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v12 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v8);  // sub_4600B0 —— 演播层注册(槽号)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
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
int /*thiscall*/ CNTreeCross__vmt2B4(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int result; // eax

  result = *(uint32_t *)(this + 680);  // 读字段 result = this+680（nSnapshot680）
  if ( result <= 0 )
  {
    sub_62A8B0((uint32_t *)this);  // sub_62A8B0 —— 【十字架】碎裂粒子定位演播
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, **(uint32_t **)(this + 144));  // 虚调用 vt+196（this）物件非空判定
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 676))(this, 0);  // 虚调用 vt+676（this）队伍编号刷新
    return (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
             this,
             "CROSS_CRASH",  // 资源/动画 TAG CROSS_CRASH
             -1,
             0,
             0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62A9D0 CNSkeletonPile__vmt2E4 —— 【骸骨堆】初始化 vmt2E4
//    置 +96=545（动画/单位标识），虚 372(100) 回待机，并置 +1100=5（可掷颅次数）。
// ------------------------------------------------------------
int /*thiscall*/ CNSkeletonPile__vmt2E4(int *this)  // 实现：(骸骨堆)初始化 vmt2E4
{
  int v2; // eax
  int result; // eax

  v2 = *this;
  *(this + 24) = 545;  // 写字段 this+24（nPageMax） ← 545
  result = (*(int (/*stdcall*/ **)(int))(v2 + 372))(100);  // 虚函数调用 槽+372：目标点写入
  *(this + 275) = 5;  // 写字段 this+275 ← 5
  return result;
}



// ------------------------------------------------------------
// 0x62A9F0 sub_62A9F0
//   【骸骨堆】Monster/Ghoul/Particle/GhoulThrowerSkull.ptl —— 食尸鬼掷颅粒子
// ------------------------------------------------------------
int /*thiscall*/ sub_62A9F0(int *this)  // 实现：(骸骨堆)Monster/Ghoul/Particle/GhoulThrowerSkull.ptl —— 食尸鬼掷颅粒子
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  uint32_t v5[26]; // [esp+4h] [ebp-68h] BYREF

  v5[25] = dword_796E50;  // dword_796E50 —— 栈检 cookie
  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 275);  // 读字段 result = this+275
    if ( result > 0 )
    {
      sub_423A20((int)v5);  // sub_423A20 —— 小结构初始化（0-100 刻度）
      qmemcpy(  // 调 内存块拷贝(内联展开)
        v5,
        (const void *)(*(int (/*thiscall*/ **)(int *, const char *))(*this + 588))(  // 虚调用 vt+588（this 虚表槽）
                        this,
                        "../../../Monster/Ghoul/Particle/GhoulThrowerSkull.ptl"),
        0x62u);
      v5[18] = 0;
      v3 = sub_429830((uint32_t *)dword_8F8500, (uint16_t)word_77F804);  // sub_429830 —— 结果 = 表按键查找（uint16）
      v4 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v3 + 196) + 152))(*(uint32_t *)(v3 + 196));  // 虚函数调用 槽+152：效果通道 3
      return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t *, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 虚调用 vt+580（this）音效/技能播放(12参)
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
// 0x62AAA0 CNSkeletonPile__vmt12C —— 注销（自身时虚 308）
//    nArg2 为自身时虚 308 停用，末走基类 CNMapObject__vmt12C。
// ------------------------------------------------------------
char /*thiscall*/ CNSkeletonPile__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 注销
{
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  return CNMapObject__vmt12C(this, nArg2);  // 返回 调 CNMapObject__vmt12C
}



// ------------------------------------------------------------
// 0x62AAD0 CNSkeletonPile__vmt200 —— 【骸骨堆】受击掷颅 vmt200
//    先 sub_62A9F0 出掷颅粒子（Monster/Ghoul/Particle/GhoulThrowerSkull.ptl），再按剩余次数(+1100)：≤0 虚 312(0) 停用；=1 虚 208 摘帧表[0]；其余自减。
// ------------------------------------------------------------
int /*thiscall*/ CNSkeletonPile__vmt200(int this, int nArg2, float *pArg3, char pszArg4)  // 实现：(骸骨堆)受击掷颅 vmt200
{
  int nThrowLeft1100; // eax  | +0x044C → 剩余掷颅次数（CNSkeletonPile；va=0062AAD0）

  sub_62A9F0((int *)this);
  if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    nThrowLeft1100 = *(uint32_t *)(this + 1100);  // 读字段 fld_44C = this+1100（nFairyGrade）
    if ( nThrowLeft1100 <= 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    }
    else
    {
      if ( nThrowLeft1100 == 1 )
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, **(uint32_t **)(this + 144));  // 虚调用 vt+208（this）动画件回挂
      --*(uint32_t *)(this + 1100);  // this+1100 剩余掷颅次数
    }
  }
  return CNRDPassiveObject__vmt200((int *)this, nArg2, pArg3, pszArg4);  // 返回 调 CNRDPassiveObject__vmt200
}



// ------------------------------------------------------------
// 0x62AB40 CNSkeletonPile__vmt140 —— 【骸骨堆】摆位 vmt140
//    +1104 非 0 时虚 204(100, 帧表[0], -4, -40, 0, 0) 带偏移摆位，末走基类 CNRDPassiveObject__vmt140。
// ------------------------------------------------------------
char /*thiscall*/ CNSkeletonPile__vmt140(uint8_t *this)  // 实现：(骸骨堆)摆位 vmt140
{
  if ( *(this + 276) != 0 )  // this+276 地图条目指针
    (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, int, int, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚调用 vt+204（this 虚表槽）
      this,
      100,
      **((uint32_t **)this + 36),  // this+36 物品状态字
      -4,
      -40,
      0,
      0);
  return CNRDPassiveObject__vmt140(this);  // 返回 调 CNRDPassiveObject__vmt140
}



// ------------------------------------------------------------
// 0x62AB70 CNSpiderSpawn__vmt2E4 —— 【蜘蛛巢】初始化 vmt2E4
//    置 +96=545 与虚 372(100)，清 +1112（已放怪标志，供同族 vmt200 判只放一次）。
// ------------------------------------------------------------
int /*thiscall*/ CNSpiderSpawn__vmt2E4(uint32_t *this)  // 实现：(蜘蛛巢)初始化 vmt2E4
{
  int v2; // eax
  int result; // eax

  v2 = *this;
  *(this + 24) = 545;  // 写字段 this+24（nPageMax） ← 545
  result = (*(int (/*stdcall*/ **)(int))(v2 + 372))(100);  // 虚函数调用 槽+372：目标点写入
  *((uint8_t *)this + 1112) = 0;  // 写字段 this+1112（nTick1112）
  return result;
}



// ------------------------------------------------------------
// 0x62AB90 CNSpiderSpawn__vmtC —— 【蜘蛛巢】构造 vmtC
//    经虚 384 取参数表第 6 项写入 +680/+684（血量初始化）。
// ------------------------------------------------------------
int /*thiscall*/ CNSpiderSpawn__vmtC(uint32_t *this)  // 实现：(蜘蛛巢)构造 vmtC
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 6);  // 虚调用 vt+384（this 虚表槽）
  *(this + 170) = result;  // 写字段 this+170 ← result
  *(this + 171) = result;  // 写字段 this+171 ← result
  return result;
}



// ------------------------------------------------------------
// 0x62ABB0 CNSpaceFishBug__vmt2B4 —— 【空骨鱼虫】击破停用 vmt2B4
//    +680(HP)≤0 且自身存活(虚 308) 时虚 312(0) 停用。
// ------------------------------------------------------------
int /*thiscall*/ CNSpaceFishBug__vmt2B4(int *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int result; // eax

  result = *(this + 170);  // 读字段 result = this+170
  if ( result <= 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
  }
  return result;
}



// ------------------------------------------------------------
// 0x62ABF0 CNSpiderSpawn__vmt128 —— 【蜘蛛巢】小蜘蛛登记 vmt128
//    来客类别(虚 40)=529 且其虚 52 命中 +1112 起三槽的预设 id 时，RTTI 认作 CNYoungSpider(小型蜘蛛) 后写入 +1116 起三槽指针，
//    并把该蜘蛛的 +8636 记为槽序 0/1/2。
// ------------------------------------------------------------
int /*thiscall*/ CNSpiderSpawn__vmt128(int *this, int nArg2)  // 实现：(蜘蛛巢)小蜘蛛登记 vmt128
{
  int v2; // edi
  int *pThis_117; // ebx
  int result; // eax

  v2 = 0;
  pThis_117 = this + 279;
  do
  {
    result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529);  // 虚调用 vt+40（nArg2）条件查询(273等)
    if ( (uint8_t)result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);  // 虚调用 vt+52（nArg2）归属坐标y
      if ( result == *(pThis_117 - 4) )
      {
        result = __RTDynamicCast(nArg2, 0, &CNRDObject `RTTI Type Descriptor', &CNYoungSpider `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
        if ( result != 0 )  // 若结果非 0（成功）
        {
          *pThis_117 = result;
          *(uint32_t *)(result + 8636) = v2;  // 写字段 result+8636（pDollTarget） ← v2
        }
      }
    }
    ++v2;  // 计数自增 v2
    ++pThis_117;  // 计数自增 pThis_117
  }
  while ( v2 < 3 );  // 循环直到 v2 < 3
  return result;
}



// ------------------------------------------------------------
// 0x62AC50 sub_62AC50 —— 【蜘蛛巢】放怪编排
//    存活(虚 308)后按 nArg3 定落点：2 → 遍历场景件按目标朝向(虚 152) 取 x±25 与 y±25；3 → 固定取自身 x±25 / y±25；
//    随后循环 nArg3 次，对 +1100 起槽逐个经 sub_460230 取随机点，以 sub_4E5030(430,100,..) 生成（末段参数含场景进度字段与朝向）。
// ------------------------------------------------------------
int /*userpurge*/ sub_62AC50@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3)  // 实现：(蜘蛛巢)放怪编排
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
  int pObj; // edi
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

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);  // 虚调用 vt+308（pDwArg1）是否本地玩家
  if ( (uint8_t)result == 0 )
    return result;
  v31 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1) + 132) + 108) + 112);  // 虚调用 vt+80（pDwArg1）读 4 字节
  if ( nArg3 == 2 )
  {
    for ( i = 0; ; ++i )
    {
      while ( 1 )  // 无限循环
      {
        v12 = pDwArg1[29];
        v13 = *(uint32_t *)(v12 + 120);  // 读字段 v13 = v12+120（pAnimObj）
        v14 = v12 + 116;  // 计算 v14 = v12 + 116
        if ( v13 != 0 )
          v15 = (*(uint32_t *)(v14 + 8) - v13) >> 2;  // 向量元素数 = (end−begin)/4
        else
          v15 = 0;
        if ( (int)i >= v15 )
        {
          v25 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1) - 25;  // 虚调用 vt+124（pDwArg1）目标坐标y下界
          v26 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1) + 25;  // 虚调用 vt+124（pDwArg1）目标坐标y下界
          goto LABEL_20;
        }
        v16 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 80))(pDwArg1, nArg2);  // 虚调用 vt+80（pDwArg1）读 4 字节
        v17 = *(uint32_t *)(v16 + 120);  // 读字段 v17 = v16+120（pAnimObj）
        if ( v17 != 0 && i < (*(uint32_t *)(v16 + 124) - v17) >> 2 )  // 向量元素数 = (end−begin)/4
          pObj = *(uint32_t *)(v17 + 4 * i);
        else
          pObj = 0;
        nArg2 = 273;
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 40))(pObj) != 0 )  // 虚调用 vt+40（pObj）条件查询(273等)
          break;
LABEL_18:
        ++i;  // 计数自增 i
      }
      if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 152))(pObj) != 0 )  // 虚调用 vt+152（pObj）取值(参数)
      {
        v29 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) + 25;  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
        v28 = v29;
        goto LABEL_18;
      }
      v29 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1) - 25;  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
      v28 = v29;
    }
  }
  if ( nArg3 == 3 )
  {
    v5 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
    v6 = *pDwArg1;
    v28 = v5 - 25;  // 计算 v28 = v5 - 25
    v29 = (*(int (/*thiscall*/ **)(int *))(v6 + 120))(pDwArg1);  // 虚函数调用 槽+120：光环生效：AURA_POWER_SET 事件（76 行转发
    v7 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 120))(pDwArg1);  // 虚调用 vt+120（pDwArg1）转发(对象+缓冲)
    v8 = *pDwArg1;
    v30 = v7 + 25;  // 计算 v30 = v7 + 25
    v25 = (*(int (/*thiscall*/ **)(int *))(v8 + 124))(pDwArg1) + 25;  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
    v9 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);  // 虚调用 vt+124（pDwArg1）目标坐标y下界
    v10 = *pDwArg1;
    v26 = v9 - 25;  // 计算 v26 = v9 - 25
    v27 = (*(int (/*thiscall*/ **)(int *))(v10 + 124))(pDwArg1) + 25;  // 虚函数调用 槽+124：状态变化（5F8000，69 行）
  }
LABEL_20:
  v32 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 128))(pDwArg1);  // 虚调用 vt+128（pDwArg1）目标坐标y上界
  result = nArg3;
  v19 = 0;
  if ( nArg3 > 0 )
  {
    v20 = pDwArg1 + 275;  // 计算 v20 = pDwArg1 + 275
    do
    {
      v21 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 80))(pDwArg1);  // 虚调用 vt+80（pDwArg1）读 4 字节
      v23 = sub_460230(v21);  // sub_460230 —— 图标槽随机 id 分配（线性探测）
      *v20 = v23;
      v22 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);  // 虚调用 vt+152（pDwArg1）取值(参数)
      sub_4E5030(  // sub_4E5030 —— 位置/状态同步包发布（短版 48024 / 长版 type 22）
        pDwArg1,
        (int)v20,
        (int)pDwArg1,
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
      result = nArg3;
      ++v19;  // 计数自增 v19
      ++v20;  // 计数自增 v20
    }
    while ( v19 < nArg3 );  // 循环直到 v19 < nArg3
  }
  return result;
}


// ------------------------------------------------------------
// 0x62AE00 CNSpiderSpawn__vmt200 —— 【蜘蛛巢】受击放怪 vmt200
//    虚 196 切帧表[1]；若 +1112=0 则 sub_62AC50(.., 2) 放怪后置 1（只放一次），末走基类 CNRDPassiveObject__vmt200。
// ------------------------------------------------------------
int /*userpurge*/ CNSpiderSpawn__vmt200@<eax>(int *pDwArg1@<ecx>, int nArg2@<edi>, int nArg3, float *pArg4, char pszArg5)  // 实现：(蜘蛛巢)受击放怪 vmt200
{
  (*(void (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 196))(pDwArg1, *(uint32_t *)(pDwArg1[36] + 4));  // 虚调用 vt+196（pDwArg1）物件非空判定
  if ( *((uint8_t *)pDwArg1 + 1112) == 0 )
  {
    sub_62AC50(pDwArg1, nArg2, 2);  // sub_62AC50 —— 【蜘蛛巢】放怪编排
    *((uint8_t *)pDwArg1 + 1112) = 1;  // 写字段 pDwArg1+1112（nTick1112）
  }
  return CNRDPassiveObject__vmt200(pDwArg1, nArg3, pArg4, pszArg5);  // 返回 调 CNRDPassiveObject__vmt200
}



// ------------------------------------------------------------
// 0x62AE50 sub_62AE50 —— 对称矩形范围判定（蜘蛛巢用）
//    —— 与 ·sub_629E00 同构（差异：无）；以 sub_4E7F30(this, nArg2, nArg3) 收集后判 (x±nArg2, y±nArg3)。
// ------------------------------------------------------------
char /*thiscall*/ sub_62AE50(uint32_t *this, signed int nArg2, signed int nArg3)  // sub_62AE50 —— 对称矩形范围判定（蜘蛛巢用）
{
  int v5; // eax
  uint32_t *Block2; // edi
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
  sub_4E7F30(this, nArg2, nArg3, (int)v10);  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
  v17 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
  Block2 = Block;
  v14 = v5;
  if ( Block == v12 )
  {
LABEL_9:
    if ( Block2 != nullptr )  // 若 Block2 有效（非空）
      j__free(Block2);  // 释放堆块
    return 0;
  }
  else
  {
    v15 = v17 - nArg2;  // 计算 v15 = v17 - nArg2
    while ( 1 )  // 无限循环
    {
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 120))(*Block2);  // 虚调用 vt+120（Block2）转发(对象+缓冲)
      v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 124))(*Block2);  // 虚调用 vt+124（Block2）目标坐标y下界
      if ( v7 >= v15 && v7 <= nArg2 + v17 && v8 >= v14 - nArg3 && v8 <= nArg3 + v14 )  // 判定 v7 >= v15 且 v7 <= nArg2 且 v8 >= v14
        break;
      if ( ++Block2 == v12 )
      {
        Block2 = Block;
        goto LABEL_9;
      }
    }
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
    return 1;  // 返回 1(成功)
  }
}



// ------------------------------------------------------------
// 0x62AF40 CNSpiderSpawn__vmt14C —— 蜘蛛巢判定放怪 vmt14C
//    sub_62AE50(this,300,300) 命中且 +1112=0 时：虚 196 应用帧表[1]，置 +1112=1 并 sub_62AC50(..,nArg2,3) 放怪（仅一次）；末走基类 CNMapObject__vmt14C。
// ------------------------------------------------------------
char /*usercall*/ CNSpiderSpawn__vmt14C@<al>(int pArg1@<ecx>, int nArg2@<edi>)  // 实现：蜘蛛巢判定放怪 vmt14C
{
  if ( sub_62AE50((uint32_t *)pArg1, 300, 300) == 1 && *(uint8_t *)(pArg1 + 1112) == 0 )  // sub_62AE50 —— 对称矩形范围判定（蜘蛛巢用）
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 144) + 4));  // 虚调用 vt+196（pArg1）物件非空判定
    *(uint8_t *)(pArg1 + 1112) = 1;  // 写字段 pArg1+1112（nTick1112） ← 1
    sub_62AC50((int *)pArg1, nArg2, 3);  // sub_62AC50 —— 【蜘蛛巢】放怪编排
  }
  return CNMapObject__vmt14C((int *)pArg1);  // 返回 调 CNMapObject__vmt14C
}



// ------------------------------------------------------------
// 0x62AF90 CN2StoryBox__vmt2E4 —— 【双子箱】初始化 vmt2E4
//    清 +1104 后虚 372(100) 回待机，置 +1105=1（已初始化标志），返回值为该虚调用结果。
// ------------------------------------------------------------
int /*thiscall*/ CN2StoryBox__vmt2E4(uint8_t *this)  // 实现：(双子箱)初始化 vmt2E4
{
  int v2; // eax
  int result; // eax

  v2 = *(uint32_t *)this;
  *(this + 1104) = 0;  // 写字段 this+1104（nResetClock1104） ← 0
  result = (*(int (/*stdcall*/ **)(int))(v2 + 372))(100);  // 虚函数调用 槽+372：目标点写入
  *(this + 1105) = 1;  // 写字段 this+1105（bFloatLoopLatch） ← 1
  return result;
}



// ------------------------------------------------------------
// 0x62AFD0 CN2StoryBox__vmtC —— 【双子箱】构造 vmtC
//    基类后经虚 384 取参数 7/8 写入 +680 与 +1100；虚 672 名字表长度达 7 时以 sub_43BCF0 判表[6] 串是否 Left，命中则虚 148(0)。
// ------------------------------------------------------------
char /*thiscall*/ CN2StoryBox__vmtC(int *this)  // 实现：(双子箱)构造 vmtC
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  unsigned int v6; // eax
  int v7; // eax

  CNMapObject__vmtC(this);
  v2 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 7);  // 虚调用 vt+384（this 虚表槽）
  v3 = *this;
  *(this + 170) = v2;  // 写字段 this+170 ← v2
  *(this + 171) = v2;  // 写字段 this+171 ← v2
  *(this + 275) = (*(int (/*thiscall*/ **)(int *, int))(v3 + 384))(this, 8);  // 写字段 this+275 ← (*(int (·thiscall· **)(int *, int))(v3 + 384))(this, 8)
  v4 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);  // 虚调用 vt+672（this）队伍编号取址
  v5 = *(uint32_t *)(v4 + 32);  // 读字段 v5 = v4+32（nHeight）
  v6 = v4 + 28;  // 计算 v6 = v4 + 28
  if ( v5 != 0 )
  {
    v6 = (*(uint32_t *)(v6 + 8) - v5) >> 2;  // 向量元素数 = (end−begin)/4
    if ( v6 >= 7 )
    {
      v7 = (*(int (/*thiscall*/ **)(int *))(*this + 672))(this);  // 虚调用 vt+672（this）队伍编号取址
      LOBYTE(v6) = sub_43BCF0((void *)(*(uint32_t *)(v7 + 32) + 24), "Left");  // sub_43BCF0 —— 字符串 “[free]”
      if ( (uint8_t)v6 != 0 )
        LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 148))(this, 0);  // 虚调用 vt+148（this）位置/朝向写入
    }
  }
  return v6;
}



// ------------------------------------------------------------
// 0x62B060 sub_62B060 —— 双子箱碎片播发
//    取 +876 挂件：虚 12 复位后按虚 192×0.8 与虚 128/124/120 链换算坐标，挂件虚 40 摆位、虚 92 取变换包，交 sub_4600B0(this+116,2,0,包) 播发。
// ------------------------------------------------------------
void /*thiscall*/ sub_62B060(uint32_t *this)  // sub_62B060 —— 双子箱碎片播发
{
  int fld_e219; // eax
  int fld_e2192; // edi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  void *fld_e29; // ecx
  uint8_t v8[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  float v10; // [esp+14h] [ebp-14h]
  int v11; // [esp+18h] [ebp-10h]
  int v12; // [esp+24h] [ebp-4h]

  fld_e219 = *(this + 219);  // 读字段 fld_e219 = this+219
  if ( fld_e219 != 0 )
  {
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_e219 + 12))(fld_e219, 0);  // 虚调用 vt+12（fld_e219 虚表槽）
    fld_e2192 = *(uint32_t *)*(this + 219);
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 192))(this);  // 虚调用 vt+192（this）取尺寸/包围盒
    v4 = *this;
    v10 = (double)v11 * 0.80000001;
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 128))(this);  // 虚函数调用 槽+128：受击槽（42AF90/657740 + 42FCB0/431860）
    v5 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 124))(this, (uint64_t)((double)v11 + v10));  // 虚调用 vt+124（this）目标坐标y下界
    v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v5);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e2192 + 40))(*(this + 219), v6);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 219) + 92))(*(this + 219), v8);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v12 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v8);  // sub_4600B0 —— 演播层注册(槽号)
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
  }
}



// ------------------------------------------------------------
// 0x62B130 CN2StoryBox__vmt2B4 —— 【双子箱】受击 vmt2B4
//    +680 ≤ +1100（虚 384 参数 7/8）且 +1104=0 时：虚 196 应用帧表[0]、sub_62B060 播碎片并置 +1104=1，+1040 句柄名有效则虚 212 播报；
//    +680 ≤ 0 且虚 308 存活时：同播报后虚 744 与虚 312(0) 收尾、再 sub_62B060；此后 +960=2 且存活时虚 560(0,0,0,0)。
// ------------------------------------------------------------
void /*thiscall*/ CN2StoryBox__vmt2B4(uint32_t **this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int v7; // ebx
  int pThis_104; // eax
  int v9; // ebx
  int pThis_1042; // eax

  if ( (int)*(this + 170) <= (int)*(this + 275) && *((uint8_t *)this + 1104) == 0 )  // this+1104〔nResetClock1104(推断)〕等 3 字段
  {
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[49])(this, **(this + 36));  // this+36 物品状态字
    sub_62B060(this);  // sub_62B060 —— 双子箱碎片播发
    *((uint8_t *)this + 1104) = 1;  // 写字段 this+1104（nResetClock1104）
    if ( sub_41ACF0(this + 260) != 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    {
      v7 = (int)*this;
      pThis_104 = sub_41ACF0(this + 260);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      (*(void (/*thiscall*/ **)(uint32_t **, int, int, uint32_t, uint32_t))(v7 + 212))(this, pThis_104, -1, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
    }
  }
  if ( (int)*(this + 170) <= 0 )  // this+680〔nSnapshot680〕
  {
    if ( ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )
    {
      if ( sub_41ACF0(this + 260) != 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      {
        v9 = (int)*this;
        pThis_1042 = sub_41ACF0(this + 260);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
        (*(void (/*thiscall*/ **)(uint32_t **, int, int, uint32_t, uint32_t))(v9 + 212))(this, pThis_1042, -1, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
      }
      ((void (/*thiscall*/ *)(uint32_t **))(*this)[186])(this);
      ((void (/*thiscall*/ *)(uint32_t **, uint32_t))(*this)[78])(this, 0);
    }
    sub_62B060(this);  // sub_62B060 —— 双子箱碎片播发
  }
  if ( *(this + 240) == (uint32_t *)2 && ((uint8_t (/*thiscall*/ *)(uint32_t **))(*this)[77])(this) != 0 )  // this+240 动画同步参数 B
    ((void (/*thiscall*/ *)(uint32_t **, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[140])(this, 0, 0, 0, 0);
}



// ------------------------------------------------------------
// 0x62B230 sub_62B230 —— 双子箱方向性范围判定
//    以 sub_4E7F30(this,nArg2,nArg3) 取矩形内目标后逐个比较：pszArg4 非 0 时按朝向（虚 152=1 取 x 大者、0 取 x 小者，虚 120）判定，否则判自身 y(虚 124) 小于目标者；命中返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_62B230(uint32_t *this, signed int nArg2, signed int nArg3, char pszArg4)  // sub_62B230 —— 双子箱方向性范围判定
{
  int v5; // eax
  int *v6; // edi
  int pObj; // ecx
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
  sub_4E7F30(this, nArg2, nArg3, (int)v11);  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
  v6 = (int *)Block;
  v16 = v5;
  if ( Block != v13 )
  {
    while ( 1 )  // 无限循环
    {
      pObj = *v6;
      if ( pszArg4 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);  // 虚调用 vt+120（pObj）转发(对象+缓冲)
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )  // 虚调用 vt+152（this）取值(参数)
        {
          if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 1 && v8 >= v16 )  // 虚调用 vt+152（this）取值(参数)
          {
LABEL_5:
            if ( Block != nullptr )  // 若 Block 有效（非空）
              j__free(Block);  // 释放堆块
            return 1;  // 返回 1(成功)
          }
        }
        else if ( v8 <= v16 )
        {
          goto LABEL_5;
        }
      }
      else
      {
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);  // 虚调用 vt+124（pObj）目标坐标y下界
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this) < v10 )  // 虚调用 vt+124（this）目标坐标y下界
          goto LABEL_5;
      }
      if ( ++v6 == v13 )
      {
        v6 = (int *)Block;
        break;
      }
    }
  }
  if ( v6 != nullptr )  // 若 v6 有效（非空）
    j__free(v6);  // 释放堆块
  return 0;
}



// ------------------------------------------------------------
// 0x62B330 CN2StoryBox__vmt2F4 —— 【双子箱】适配判定 vmt2F4
//    +1105 非 0 时查 200x50 并按朝向判 x，否则查 100x200 判 y（转调 sub_62B230）。
// ------------------------------------------------------------
char /*thiscall*/ CN2StoryBox__vmt2F4(int this)  // 实现：(双子箱)适配判定 vmt2F4
{
  if ( *(uint8_t *)(this + 1105) != 0 )  // this+1105 适配判定标志
    return sub_62B230((uint32_t *)this, 200, 50, 1);  // sub_62B230 —— 双子箱方向性范围判定
  else
    return sub_62B230((uint32_t *)this, 100, 200, 0);  // sub_62B230 —— 双子箱方向性范围判定
}



// ------------------------------------------------------------
// 0x62B360 sub_62B360
//   【双子箱】属性投掷粒子四选一（同 0x6252D0）：FastThrowStone/IceMissile/FireMissile/AimingBomb
// ------------------------------------------------------------
int /*userpurge*/ sub_62B360@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<esi>, int nArg3)  // 函数 sub_62B360：= 属性投掷粒子选择器（FastThrowStone/IceMissile/FireMissile/AimingBomb.p…
{
  int result; // eax
  int nRand; // esi
  const void *v6; // esi
  int v7; // eax
  const void *v8; // esi
  int v9; // eax
  uint64_t v10; // rax
  int v11; // ecx
  const void *v12; // esi
  int v13; // eax
  int v14; // esi
  uint32_t pBuf[11]; // [esp+8h] [ebp-98h] BYREF
  int v17; // [esp+34h] [ebp-6Ch]
  uint32_t v18[26]; // [esp+38h] [ebp-68h] BYREF

  v18[25] = dword_796E50;  // dword_796E50 —— 栈检 cookie
  result = nArg3;
  if ( nArg3 != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);  // 虚调用 vt+308（pArg1）是否本地玩家
    if ( (uint8_t)result != 0 )
    {
      pBuf[4] = 1;
      pBuf[5] = 1;
      pBuf[6] = 1;
      memset(pBuf, 0, 16);  // 清零 pBuf 起 16 字节
      pBuf[7] = 2;
      pBuf[8] = 2;
      pBuf[9] = 3;
      nRand = rand() % 10;  // 调 取伪随机数
      sub_423A20(v18);  // sub_423A20 —— 小结构初始化（0-100 刻度）
      result = pBuf[nRand];
      switch ( result )  // 按 result 分派
      {
        case 0:  // case 0 分派（十字架/骸骨堆/蜘蛛卵/双子箱（0x62A980-0x62B820））
          v6 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 588))(  // 虚调用 vt+588（pArg1 虚表槽）
                               pArg1,
                               "Particle/FastThrowStone.ptl",  // 资源路径 Particle/FastThrowStone.ptl
                               nArg2);
          v7 = *pArg1;
          qmemcpy(v18, v6, 0x62u);  // 调 内存块拷贝(内联展开)
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v7 + 164))(pArg1, nArg3, 0);  // 虚函数调用 槽+164
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
                     pArg1,
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
        case 1:  // case 1 分派（十字架/骸骨堆/蜘蛛卵/双子箱（0x62A980-0x62B820））
          v8 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 588))(  // 虚调用 vt+588（pArg1 虚表槽）
                               pArg1,
                               "Particle/IceMissile.ptl",  // 资源路径 Particle/IceMissile.ptl
                               nArg2);
          v9 = *pArg1;
          qmemcpy(v18, v8, 0x62u);  // 调 内存块拷贝(内联展开)
          v10 = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v9 + 164))(pArg1, nArg3, 0);  // 虚函数调用 槽+164
          v18[18] = v10;
          v11 = 1;
          if ( (int)v10 >= 90 && (int)v10 < 270 )
          {
            v11 = 0;
            v18[18] = 180 - v10;
          }
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
                     pArg1,
                     42001,
                     *(uint32_t *)(pArg1[87] + 36),
                     v18,
                     0,
                     0,
                     10,
                     50,
                     v11,
                     0,
                     0);
          break;
        case 2:  // case 2 分派（十字架/骸骨堆/蜘蛛卵/双子箱（0x62A980-0x62B820））
          v12 = (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 588))(  // 虚调用 vt+588（pArg1 虚表槽）
                                pArg1,
                                "Particle/FireMissile.ptl",  // 资源路径 Particle/FireMissile.ptl
                                nArg2);
          v13 = *pArg1;
          qmemcpy(v18, v12, 0x62u);  // 调 内存块拷贝(内联展开)
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(v13 + 164))(pArg1, nArg3, 0);  // 虚函数调用 槽+164
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
                     pArg1,
                     40001,
                     *(uint32_t *)(pArg1[87] + 40),
                     v18,
                     0,
                     0,
                     10,
                     50,
                     1,
                     0,
                     0);
          break;
        case 3:  // case 3 分派（十字架/骸骨堆/蜘蛛卵/双子箱（0x62A980-0x62B820））
          if ( (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*pArg1 + 8))(pArg1, nArg3, 0, nArg2) >= 250 )  // 虚调用 vt+8（pArg1 虚表槽）
            v17 = 250;
          else
            v17 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*pArg1 + 8))(pArg1, nArg3, 0);  // 虚调用 vt+8（pArg1 虚表槽）
          qmemcpy(  // 调 内存块拷贝(内联展开)
            v18,
            (const void *)(*(int (/*thiscall*/ **)(uint32_t *, const char *))(*pArg1 + 588))(pArg1, "Particle/AimingBomb.ptl"),  // 虚调用 vt+588（pArg1 虚表槽）
            0x62u);
          pBuf[10] = 2 * *(uint32_t *)((char *)&v18[7] + 3);
          v14 = (uint64_t)((double)(2 * *(uint32_t *)((char *)&v18[7] + 3)) / (double)v18[17] * 1000.0);
          v18[18] = (uint64_t)((double (/*thiscall*/ *)(uint32_t *, int, uint32_t))*(uint32_t *)(*pArg1 + 164))(pArg1, nArg3, 0);  // 虚函数调用 槽+164
          BYTE1(v18[22]) = 3;  // 调 取 32 位值的第 2 字节
          *(uint32_t *)((char *)&v18[3] + 3) = 1000 * v17 / v14;
          *(uint32_t *)((char *)&v18[4] + 3) = *(uint32_t *)((char *)&v18[3] + 3);
          result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t *, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 580))(  // 虚调用 vt+580（pArg1）音效/技能播放(12参)
                     pArg1,
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
// 0x62B610 sub_62B610 —— 格伦掩体动画件批量停播
//    对 +144 键帧表偏移 8..44 的 10 项：虚 208 归还并 sub_4926A0 复位帧游标（与 ·sub_625580 同构，范围由 16 项改 10 项）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62B610(uint32_t *this)  // sub_62B610 —— 格伦掩体动画件批量停播
{
  int i; // esi
  int result; // eax

  for ( i = 8; i < 48; i += 4 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 208))(this, *(uint32_t *)(i + *(this + 36)));  // 虚调用 vt+208（this）动画件回挂
    result = sub_4926A0(*(uint32_t *)(*(this + 36) + i));  // sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
  }
  return result;
}



// ------------------------------------------------------------
// 0x62B650 sub_62B650 —— 格伦掩体半血演出
//    停全部件后虚 196 应用帧表[4]、虚 204(100,表+40) 设层；再把 +1108 件按虚 192×0.7 经虚 124(末 +2)/虚 120 换算对齐后挂件虚 40 摆位，经 sub_4600B0(this+116,2,0,包) 播发（与 ·sub_6255C0 同构）。
// ------------------------------------------------------------
void /*thiscall*/ sub_62B650(int this)  // sub_62B650 —— 格伦掩体半血演出
{
  int fld_454; // edi
  int pThis_7C; // eax
  int pThis_78; // eax
  void *fld_74; // ecx
  uint8_t v6[4]; // [esp+8h] [ebp-20h] BYREF
  void *Block; // [esp+Ch] [ebp-1Ch]
  int pThis_C0; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  sub_62B610((uint32_t *)this);  // sub_62B610 —— 格伦掩体动画件批量停播
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 16));  // 虚调用 vt+196（this）物件非空判定
  (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    100,
    *(uint32_t *)(*(uint32_t *)(this + 144) + 40),  // this+144 第 4 组·+1040 增量子倍率
    0,
    0,
    0,
    0);
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 1108) + 12))(*(uint32_t *)(this + 1108), 0);  // this+1108 子对象槽
  fld_454 = **(uint32_t **)(this + 1108);  // this+1108 子对象槽
  pThis_C0 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 192))(this);  // 虚调用 vt+192（this）取尺寸/包围盒
  pThis_7C = (*(int (/*fastcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 124))(  // 虚调用 vt+124（this）目标坐标y下界
         this,
         (uint64_t)((double)pThis_C0 * 0.69999999) >> 32,
         (uint64_t)((double)pThis_C0 * 0.69999999));
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C + 2);  // 虚调用 vt+120（this）转发(对象+缓冲)
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_454 + 40))(*(uint32_t *)(this + 1108), pThis_78);  // this+1108 子对象槽
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 1108) + 92))(*(uint32_t *)(this + 1108), v6);  // this+1108 子对象槽
  fld_74 = *(void **)(this + 116);  // this+116 观察者 vector 尾针
  v9 = 0;
  sub_4600B0(fld_74, 2, 0, (int)v6);  // sub_4600B0 —— 演播层注册(槽号)
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 释放堆块
}



// ------------------------------------------------------------
// 0x62B740 sub_62B740 —— 格伦掩体状态 1 演出
//    停件后按开门位 +1100 二选一：1 取虚 196(表+20)+204(100,表+44)，0 取虚 196(表+12)+204(100,表+32)（与 ·sub_6256F0 前段同构）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62B740(int *this)  // sub_62B740 —— 格伦掩体状态 1 演出
{
  int v2; // edx
  int fld_e36; // eax
  uint32_t *fld_e362; // eax

  sub_62B610(this);  // sub_62B610 —— 格伦掩体动画件批量停播
  v2 = *this;
  fld_e36 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
  if ( *((uint8_t *)this + 1100) == 1 )  // this+1100 时钟槽
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 20));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    fld_e362 = (uint32_t *)(*(this + 36) + 44);  // this+36 物品状态字
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 12));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    fld_e362 = (uint32_t *)(*(this + 36) + 32);  // this+36 物品状态字
  }
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           *fld_e362,
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x62B7B0 sub_62B7B0 —— 格伦掩体状态 2 演出
//    与 ·sub_62B740 同构（差异：开门分支取表 +16/+40，关门取表 +8/+28）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62B7B0(int *this)  // sub_62B7B0 —— 格伦掩体状态 2 演出
{
  int v2; // edx
  int fld_e36; // eax
  uint32_t *fld_e362; // eax

  sub_62B610(this);  // sub_62B610 —— 格伦掩体动画件批量停播
  v2 = *this;
  fld_e36 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
  if ( *((uint8_t *)this + 1100) == 1 )  // this+1100 时钟槽
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 16));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    fld_e362 = (uint32_t *)(*(this + 36) + 40);  // this+36 物品状态字
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 8));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    fld_e362 = (uint32_t *)(*(this + 36) + 28);  // this+36 物品状态字
  }
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           *fld_e362,
           0,
           0,
           0,
           0);
}



// ------------------------------------------------------------
// 0x62B820 sub_62B820 —— 格伦掩体状态 3 演出
//    与 ·sub_62B740 同构（差异：开门分支取表 +16/+36，关门取表 +8/+24）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62B820(int *this)  // sub_62B820 —— 格伦掩体状态 3 演出
{
  int v2; // edx
  int fld_e36; // eax
  uint32_t *fld_e362; // eax

  sub_62B610(this);  // sub_62B610 —— 格伦掩体动画件批量停播
  v2 = *this;
  fld_e36 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
  if ( *((uint8_t *)this + 1100) == 1 )  // this+1100 时钟槽
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 16));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    fld_e362 = (uint32_t *)(*(this + 36) + 36);  // this+36 物品状态字
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t))(v2 + 196))(this, *(uint32_t *)(fld_e36 + 8));  // 虚函数调用 槽+196：动画对象设置（换域 + 播放）
    fld_e362 = (uint32_t *)(*(this + 36) + 24);  // this+36 物品状态字
  }
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
           this,
           100,
           *fld_e362,
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
int /*thiscall*/ CNGrenselosBunker__vmt2B4(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 函数定义: 观察者组件逐槽挂载
{
  int nHpCur680; // ecx  | +0x02A8 → 当前 HP（62B890 受击比对：< +684/2 触发半血演出）（证据 va=004E1FE0）（CNGrenselosBunker；va=004E1FE0）
  int result; // eax

  (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(this, "BUNKER_HIT", -1, 0, 0);  // 虚调用 vt+212（this 虚表槽）
  nHpCur680 = *(uint32_t *)(this + 680);  // 读字段 fld_2A8 = this+680（nSnapshot680）
  if ( nHpCur680 > 0 )
  {
    if ( *(uint8_t *)(this + 1100) == 0 && nHpCur680 < *(uint32_t *)(this + 684) / 2 )  // this+1100 开门位
    {
      sub_62B650(this);  // sub_62B650 —— 格伦掩体半血演出
      *(uint8_t *)(this + 1100) = 1;  // 写字段 this+1100（nFairyGrade） ← 1
    }
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
    if ( (uint8_t)result != 0 )
      result = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 3, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
  }
  else
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
      this,
      "BUNKER_BREAK",  // 资源/动画 TAG BUNKER_BREAK
      -1,
      0,
      0);
    result = *(uint32_t *)(this + 1080);  // 读字段 result = this+1080（nAnimIdx1080）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = (*(uint32_t *)(this + 1084) - result) / 12;  // this+1084 开合插值结束帧号
      if ( result != 0 )  // 若结果非 0（成功）
        result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
                   this,
                   "GBN_FRIGHT",  // 资源/动画 TAG GBN_FRIGHT
                   -1,
                   0,
                   0);
    }
  }
  if ( *(uint8_t *)(this + 1100) == 1 )  // this+1100 开门位
  {
    result = *(uint32_t *)(this + 684) / 2;  // this+684 最大 HP
    if ( *(uint32_t *)(this + 680) >= result )  // this+680 当前 HP
    {
      *(uint8_t *)(this + 1100) = 0;  // 写字段 this+1100（nFairyGrade） ← 0
      return sub_62B7B0((int *)this);  // sub_62B7B0 —— 格伦掩体状态 2 演出
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62B9A0 sub_62B9A0 —— 格伦掩体自动发射
//    以 +1104+1000ms 节流；存活(虚 308) 且 rand%100≤30 时由 sub_4E7F30(this,250,75) 取目标：rand%100>10 打包 1 与目标虚 48/虚 52，否则打包目标数后逐项取虚 48/52，经 sub_431230 入 v12，虚 560(this,2,记录包,0,0) 发射。
// ------------------------------------------------------------
void /*thiscall*/ sub_62B9A0(uint32_t *this)  // sub_62B9A0 —— 格伦掩体自动发射
{
  int pThis_9; // esi
  int v3; // eax
  int v4; // edx
  int pObj; // esi
  bool nRand; // bl
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

  pThis_9 = (int)(this + 9);  // this+36〔nStateWord36(推断)〕
  if ( *(this + 276) + 1000 <= (unsigned int)sub_699000((int)(this + 9)) )  // 【clock_now(clk)】
  {
    v3 = sub_699000(pThis_9);  // 【clock_now(clk)】
    v4 = *this;
    *(this + 276) = v3;  // 写字段 this+276（pMapEntry） ← v3
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(v4 + 308))(this) != 0 && rand() % 100 <= 30 )  // 虚函数调用 槽+308
    {
      v9 = nullptr;
      v10 = 0;
      v11 = 0;
      v17 = 0;
      pObj = sub_4E7F30(this, 250, 75, (int)v8);  // sub_4E7F30 —— 结果 = 半径内敌方查找（|Δx| <= a2 且 |Δy| <= a3）
      if ( pObj != 0 )
      {
        nRand = rand() % 100 > 10;  // 调 取伪随机数
        Block = nullptr;
        v14 = 0;
        v15 = 0;
        LOBYTE(v17) = 1;  // 调 取 16 位值低 8 位
        if ( nRand )
        {
          v16 = 1;
          sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);  // 虚调用 vt+48（pObj）归属坐标x
          sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
          v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);  // 虚调用 vt+52（pObj）归属坐标y
          sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
        }
        else
        {
          if ( v9 != nullptr )  // 若 v9 有效（非空）
            v16 = (v10 - (int)v9) >> 2;
          else
            v16 = 0;
          sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
          for ( i = 0; v9 != nullptr && i < (v10 - (int)v9) >> 2; ++i )
          {
            v16 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v9 + i) + 48))(*((uint32_t *)v9 + i));  // 虚函数调用 槽+48：更新槽（64A5A0 + 41C5E0/52E4D0）
            sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
            v16 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)v9 + i) + 52))(*((uint32_t *)v9 + i));  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
            sub_431230((int)v12, &v16);  // sub_431230 —— uint32 vector push_back
          }
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 2, v12, 0, 0);  // 虚调用 vt+560（this 虚表槽）
        if ( Block != nullptr )  // 若 Block 有效（非空）
          j__free(Block);  // 释放堆块
      }
      if ( v9 != nullptr )  // 若 v9 有效（非空）
        j__free(v9);  // 释放堆块
    }
  }
}



// ------------------------------------------------------------
// 0x62BB60 CNGrenselosBunker__vmt2E4 —— 【掩体·格伦】重置 vmt2E4
//    置 +676=1 与 +96=545（单位/动画标识）、清 +1100，记 clock_now 入 +1104 并 sub_62B7B0 重放状态 2；new(0x12C)：由虚 672 链取 +32 表 +24 句柄(sub_41ACF0)与自身名（SSO +364 或指针）经 sub_4C3640 建 +1108 挂件；
//    再虚 372(100)、释放 +1120 队列并清 +1112 与 +1120..+1128，末虚 472(6,0,1,1)。
// ------------------------------------------------------------
int /*thiscall*/ CNGrenselosBunker__vmt2E4(int this)  // 实现：(掩体·格伦)重置 vmt2E4
{
  int pThis_20; // ecx
  int pThis_16C; // edi
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax

  *(uint32_t *)(this + 676) = 1;  // 写字段 this+676（nResetFlag676） ← 1
  *(uint32_t *)(this + 96) = 545;  // 写字段 this+96（nStatusMode） ← 545
  *(uint8_t *)(this + 1100) = 0;  // 写字段 this+1100（nFairyGrade） ← 0
  *(uint32_t *)(this + 1104) = sub_699000(this + 36);  // sub_699000 —— 【clock_now(clk)】
  sub_62B7B0((int *)this);  // sub_62B7B0 —— 格伦掩体状态 2 演出
  if ( operator new(0x12Cu) != nullptr )  // 堆分配
  {
    pThis_20 = *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 672))(this) + 32) + 24;  // 虚调用 vt+672（this）队伍编号取址
    if ( *(uint32_t *)(this + 384) < 0x10u )  // this+384 动画件名 SSO 容量判据
      pThis_16C = this + 364;  // this+364 动画件名 SSO 内联首址
    else
      pThis_16C = *(uint32_t *)(this + 364);  // 读字段 pThis_16C = this+364（pAnimNameStr）
    v4 = sub_41ACF0(pThis_20);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    v5 = sub_4C3640(pThis_16C, v4, this);  // 调 构造 +988 挂件
  }
  else
  {
    v5 = 0;
  }
  v6 = *(uint32_t *)this;
  *(uint32_t *)(this + 1108) = v5;  // 写字段 this+1108（pAttach1108） ← v5
  (*(void (/*thiscall*/ **)(int, int))(v6 + 372))(this, 100);  // 虚函数调用 槽+372：目标点写入
  if ( *(uint32_t *)(this + 1120) != 0 )  // this+1120 投掷名单缓冲
    j__free(*(void **)(this + 1120));  // 释放堆块
  *(uint32_t *)(this + 1120) = 0;  // 写字段 this+1120（pList1120） ← 0
  *(uint32_t *)(this + 1124) = 0;  // 写字段 this+1124（nListCnt1124） ← 0
  *(uint32_t *)(this + 1128) = 0;  // 写字段 this+1128（nListCap1128） ← 0
  v7 = *(uint32_t *)this;
  *(uint32_t *)(this + 1112) = 0;  // 写字段 this+1112（nTick1112） ← 0
  return (*(int (/*thiscall*/ **)(int, int, uint32_t, int, int))(v7 + 472))(this, 6, 0, 1, 1);  // 虚函数调用 槽+472：主状态机（874 行）：CONDITION_STUN/DOWN_HEAV
}



// ------------------------------------------------------------
// 0x62BC70 CNGrenselosBunker__vmt14C —— 【掩体·格伦】主 tick vmt14C
//    状态(+960)=0 走 sub_62B9A0 自动发射；=2 且存活、对应帧件（开门位 +1100 取表 +36 或 +24）的 +148≥1 时，按 +1112 计数遍历 +1120 成对记录经 sub_45EBE0 取点、sub_62B360 出投掷粒子，末虚 560(0,0,0,0)；
//    =3 且存活、虚 200 当前件 +170 非 0 时同样虚 560(0,0,0,0)。
// ------------------------------------------------------------
void /*thiscall*/ CNGrenselosBunker__vmt14C(uint32_t *this)  // 函数定义: 位置采样
{
  int fld_e240; // eax
  int v3; // eax
  char fld_e36; // cl
  int i; // edi
  int fld_e29; // eax

  fld_e240 = *(this + 240);  // 读字段 fld_e240 = this+240（nSyncArgB）
  if ( fld_e240 != 0 )
  {
    v3 = fld_e240 - 2;  // 计算 v3 = fld_e240 - 2
    if ( v3 != 0 )
    {
      if ( v3 == 1
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308（this）是否本地玩家
        && *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 170) != 0 )  // 虚调用 vt+200（this）取值比较
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
      }
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0  // 虚调用 vt+308（this）是否本地玩家
           && ((fld_e36 = *((uint8_t *)this + 1100)) == 1 && *(int *)(*(uint32_t *)(*(this + 36) + 36) + 148) >= 1  // this+1100 开门位
            || fld_e36 == 0 && *(int *)(*(uint32_t *)(*(this + 36) + 24) + 148) >= 1) )  // this+36 物品状态字
    {
      for ( i = 0; i < *(this + 278); ++i )  // this+1112〔nThrowTick1112〕
      {
        fld_e29 = sub_45EBE0(  // sub_45EBE0 —— 存 id 对 → 对象查找
               (uint32_t *)*(this + 29),  // this+116〔会话上下文〕
               *(uint32_t *)(*(this + 280) + 8 * i),  // this+280 地图条目数组 end
               *(uint32_t *)(*(this + 280) + 8 * i + 4));  // this+280 地图条目数组 end
        sub_62B360(this, (int)this, fld_e29);  // 【= 属性投掷粒子选择器（FastThrowStone/IceMissile/Fire…】
      }
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);  // 虚调用 vt+560（this 虚表槽）
    }
  }
  else
  {
    sub_62B9A0(this);  // sub_62B9A0 —— 格伦掩体自动发射
  }
}



// ------------------------------------------------------------
// 0x62BD70 sub_62BD70
//   【掩体·格伦】Common/CommonEffect/Animation/Heal.ani —— 治疗演出
// ------------------------------------------------------------
int /*thiscall*/ sub_62BD70(int *this)  // 实现：(掩体·格伦)Common/CommonEffect/Animation/Heal.ani —— 治疗演出
{
  int v2; // edi
  int v3; // edx
  int fld_e170; // ebx
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
  int fld_e171; // [esp+1Ch] [ebp-10h]
  int v24; // [esp+28h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    fld_e171 = *(this + 171);  // 读字段 fld_e171 = this+171
    v2 = (uint64_t)((double)fld_e171 * 0.2);
    Block = nullptr;
    v21 = 0;
    v22 = 0;
    v3 = *this;
    fld_e170 = *(this + 170);  // 读字段 fld_e170 = this+170
    v24 = 0;
    fld_e171 = (*(int (/*thiscall*/ **)(int *))(v3 + 192))(this);  // 虚函数调用 槽+192
    v5 = (*(int (/*fastcall*/ **)(int *, uint32_t, uint32_t))(*this + 124))(  // 虚调用 vt+124（this）目标坐标y下界
           this,
           (uint64_t)((double)fld_e171 * 0.75) >> 32,
           (uint64_t)((double)fld_e171 * 0.75));
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v5);  // 虚调用 vt+120（this）转发(对象+缓冲)
    v16 = v2 + fld_e170;  // 计算 v16 = v2 + fld_e170
    v7 = 0;
    sub_600920((int)v19, 0, v2, v16, v6, v17, v18);
    (*(void (/*thiscall*/ **)(int *, int, uint8_t *))(*this + 560))(this, 1, v19);  // 虚调用 vt+560（this 虚表槽）
    v24 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
    Block = nullptr;
    v21 = 0;
    v22 = 0;
  }
  else
  {
    v7 = 0;
  }
  v8 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
  fld_e171 = v8;
  v24 = 1;
  if ( v8 != 0 )
    v7 = sub_431860(v8, "Common/CommonEffect/Animation/Heal.ani", 1);  // sub_431860 —— 动画件构造（资源 id 版）
  v24 = -1;
  v9 = (char *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  v10 = v9;
  fld_e171 = (int)v9;
  v24 = 2;
  if ( v9 != nullptr )  // 若 v9 有效（非空）
  {
    sub_44E0D0(v9, v7, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v10 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
  }
  else
  {
    v10 = nullptr;
  }
  v11 = *(uint32_t *)v10;
  v24 = -1;
  (*(void (/*thiscall*/ **)(char *, int))(v11 + 72))(v10, 2);  // 虚函数调用 槽+72：槽（4BE520/4F2D40 + 4848
  sub_45FE80(*(this + 29), (int)v10, 2, 0, (int)v10, (int)this, 0);  // sub_45FE80 —— 对象注册
  v12 = *(uint32_t *)v10;
  v13 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, 40);  // 虚调用 vt+124（this）目标坐标y下界
  v14 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v13 + 1);  // 虚调用 vt+120（this）转发(对象+缓冲)
  return (*(int (/*thiscall*/ **)(char *, int))(v12 + 112))(v10, v14);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
}



// ------------------------------------------------------------
// 0x62BEF0 CNGrenselosBunker__vmt1D8
//   【掩体·格伦】BUNKER_OPEN —— 开门
// ------------------------------------------------------------
int /*thiscall*/ CNGrenselosBunker__vmt1D8(int this, int nArg2, int pArg3, int nArg4, int nArg5)  // 实现：(掩体·格伦)BUNKER_OPEN —— 开门
{
  int result; // eax
  int v7; // edi
  int v8; // ecx
  int v9; // eax

  result = CNRDPassiveObject__vmt1D8((uint32_t *)this, nArg2, pArg3, nArg2, pArg3, nArg4, nArg5);  // result = 调 CNRDPassiveObject__vmt1D8
  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 0:  // case 0 分派（格伦塞洛斯掩体（CNGrenselosBunker，0x62B890-0x62C120））
      result = sub_62B7B0((int *)this);  // sub_62B7B0 —— 格伦掩体状态 2 演出
      break;
    case 2:  // case 2 分派（格伦塞洛斯掩体（CNGrenselosBunker，0x62B890-0x62C120））
      sub_62B820((int *)this);  // sub_62B820 —— 格伦掩体状态 3 演出
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
        this,
        "BUNKER_OPEN",  // 资源/动画 TAG BUNKER_OPEN
        -1,
        0,
        0);
      sub_5E5260((void **)(this + 1116));  // 调 动画子对象清理临时缓冲
      *(uint32_t *)(this + 1112) = 0;  // 写字段 this+1112（nTick1112） ← 0
      result = **(uint32_t **)(pArg3 + 4);  // pArg3+4〔宿主对象〕
      v7 = 0;
      for ( *(uint32_t *)(this + 1112) = result; v7 < result; ++v7 )  // this+1112 投掷节拍计数
      {
        v8 = *(uint32_t *)(pArg3 + 4);  // 读字段 v8 = pArg3+4（pHostObj）
        v9 = *(uint32_t *)(v8 + 8 * v7 + 8);
        nArg5 = *(uint32_t *)(v8 + 8 * v7 + 4);
        nArg4 = v9;
        sub_431230(this + 1116, &nArg5);  // sub_431230 —— uint32 vector push_back
        sub_431230(this + 1116, &nArg4);  // sub_431230 —— uint32 vector push_back
        result = *(uint32_t *)(this + 1112);  // 读字段 result = this+1112（nTick1112）
      }
      break;
    case 3:  // case 3 分派（格伦塞洛斯掩体（CNGrenselosBunker，0x62B890-0x62C120））
      result = sub_62B740((int *)this);  // sub_62B740 —— 格伦掩体状态 1 演出
      break;
    case 4:  // case 4 分派（格伦塞洛斯掩体（CNGrenselosBunker，0x62B890-0x62C120））
      sub_62BD70((int *)this);
      result = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 472))(this, 0, 0, 1, 1);  // 虚调用 vt+472（this 虚表槽）
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62C000 sub_62C000 —— HP 吸取量计算（档位 1/3、1/2、全量）
//    按 +1100 档位(0/1/2) 取目标虚 740 的 1/3、1/2 或全量写入 *pDwArg3 与 *uArg4=1000（时长），再以虚 740-虚 736 封顶（供 CNChangeHp）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62C000(uint32_t *this, int nArg2, int *pDwArg3, uint32_t *uArg4)  // sub_62C000 —— HP 吸取量计算（档位 1/3、1/2、全量）
{
  int fld_e275; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int result; // eax
  int v9; // edi

  fld_e275 = *(this + 275);  // 读字段 fld_e275 = this+275
  if ( fld_e275 != 0 )
  {
    v5 = fld_e275 - 1;  // 计算 v5 = fld_e275 - 1
    if ( v5 == 0 )
    {
      *pDwArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2) / 2;  // 虚调用 vt+740（nArg2 虚表槽）
      *uArg4 = 1000;
      goto LABEL_8;
    }
    if ( v5 != 1 )
      goto LABEL_8;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2);  // 虚调用 vt+740（nArg2 虚表槽）
  }
  else
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2) / 3;  // 虚调用 vt+740（nArg2 虚表槽）
  }
  *pDwArg3 = v6;
  *uArg4 = 1000;
LABEL_8:
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2);  // 虚调用 vt+740（nArg2 虚表槽）
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 736))(nArg2);  // 虚调用 vt+736（nArg2 虚表槽）
  v9 = v7 - result;  // 计算 v9 = v7 - result
  if ( *pDwArg3 > v9 )
    *pDwArg3 = v9;
  return result;
}



// ------------------------------------------------------------
// 0x62C090 sub_62C090 —— MP 吸取量计算
//    与 ·sub_62C000 同构（差异：改读虚 756/752，即 MP 档位量）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62C090(uint32_t *this, int nArg2, int *pDwArg3, uint32_t *uArg4)  // sub_62C090 —— MP 吸取量计算
{
  int fld_e275; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi
  int result; // eax
  int v9; // edi

  fld_e275 = *(this + 275);  // 读字段 fld_e275 = this+275
  if ( fld_e275 != 0 )
  {
    v5 = fld_e275 - 1;  // 计算 v5 = fld_e275 - 1
    if ( v5 == 0 )
    {
      *pDwArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2) / 2;  // 虚调用 vt+756（nArg2 虚表槽）
      *uArg4 = 1000;
      goto LABEL_8;
    }
    if ( v5 != 1 )
      goto LABEL_8;
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2);  // 虚调用 vt+756（nArg2 虚表槽）
  }
  else
  {
    v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2) / 3;  // 虚调用 vt+756（nArg2 虚表槽）
  }
  *pDwArg3 = v6;
  *uArg4 = 1000;
LABEL_8:
  v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2);  // 虚调用 vt+756（nArg2 虚表槽）
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 752))(nArg2);  // 虚调用 vt+752（nArg2 虚表槽）
  v9 = v7 - result;  // 计算 v9 = v7 - result
  if ( *pDwArg3 > v9 )
    *pDwArg3 = v9;
  return result;
}



// ------------------------------------------------------------
// 0x62C120 sub_62C120 —— HP+MP 双吸取量计算
//    与 ·sub_62C000 同构（差异：HP(虚 740/736) 与 MP(虚 756/752) 双出参，各按档位取量并分别封顶）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62C120(uint32_t *this, int nArg2, int *pDwArg3, int *pDwArg4, uint32_t *uArg5)  // sub_62C120 —— HP+MP 双吸取量计算
{
  int fld_e275; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // edi
  int result; // eax
  int v11; // edi
  int v12; // [esp+20h] [ebp+14h]

  fld_e275 = *(this + 275);  // 读字段 fld_e275 = this+275
  if ( fld_e275 == 0 )
  {
    *pDwArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2) / 3;  // 虚调用 vt+740（nArg2 虚表槽）
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2) / 3;  // 虚调用 vt+756（nArg2 虚表槽）
    goto LABEL_7;
  }
  v6 = fld_e275 - 1;  // 计算 v6 = fld_e275 - 1
  if ( v6 == 0 )
  {
    *pDwArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2) / 2;  // 虚调用 vt+740（nArg2 虚表槽）
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2) / 2;  // 虚调用 vt+756（nArg2 虚表槽）
LABEL_7:
    *pDwArg4 = v7;
    *uArg5 = 1000;
    goto LABEL_8;
  }
  if ( v6 == 1 )
  {
    *pDwArg3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2);  // 虚调用 vt+740（nArg2 虚表槽）
    *pDwArg4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2);  // 虚调用 vt+756（nArg2 虚表槽）
    *uArg5 = 1000;
  }
LABEL_8:
  v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 740))(nArg2);  // 虚调用 vt+740（nArg2 虚表槽）
  v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 736))(nArg2);  // 虚调用 vt+736（nArg2 虚表槽）
  if ( *pDwArg3 > v12 - v8 )
    *pDwArg3 = v12 - v8;
  v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 756))(nArg2);  // 虚调用 vt+756（nArg2 虚表槽）
  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 752))(nArg2);  // 虚调用 vt+752（nArg2 虚表槽）
  v11 = v9 - result;  // 计算 v11 = v9 - result
  if ( *pDwArg4 > v11 )
    *pDwArg4 = v11;
  return result;
}



// ============================================================
// 【分区 17】妖精族（CNFairy 工厂族，0x62C220-0x62D0B0）
// 证据: TINGKERBELL_FLOAT_LOOP（漂浮）+ TINGKERBELL_MP_ABSORB / HP_ABSORB / ALL_ABSORB；
//       变体按吸收类型分派: Haste/Bless/Invinsible/HP/MP/HPMP/SuperArmorFairy + CNFairyFactory
// ============================================================

// ------------------------------------------------------------
// 0x62C220 CNHasteFairy__vmt2F4 —— 【妖精·加速】施加 vmt2F4
//    按 +1100 档位取 5/15/20，虚 768(nArg2,12,v3,this) 施加状态 12（加速；v3 随档位，【推断】为持续或强度值）。
// ------------------------------------------------------------
int /*thiscall*/ CNHasteFairy__vmt2F4(uint32_t *this, int nArg2)  // 实现：(妖精·加速)施加 vmt2F4
{
  int nFairyGrade; // eax  | +0x044C → 【推断】妖精档位/缩放档（编号末位 0/1/2）〔62C5F0 解析末位写入（CNHasteFairy；va=0062C510）
  int v3; // edx
  int v4; // eax

  nFairyGrade = *(this + 275);  // 读字段 fld_e275 = this+275
  v3 = 0;
  if ( nFairyGrade != 0 )
  {
    v4 = nFairyGrade - 1;  // 计算 v4 = fld_e275 - 1
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
  return (*(int (/*thiscall*/ **)(int, int, int, uint32_t *))(*(uint32_t *)nArg2 + 768))(nArg2, 12, v3, this);  // 虚调用 vt+768（nArg2 虚表槽）
}



// ------------------------------------------------------------
// 0x62C260 CNBlessFairy__vmt2F4 —— 【妖精·祝福】施加 vmt2F4
//    与 CNHasteFairy__vmt2F4 同构（差异：状态号 13）。
// ------------------------------------------------------------
int /*thiscall*/ CNBlessFairy__vmt2F4(uint32_t *this, int nArg2)  // 实现：(妖精·祝福)施加 vmt2F4
{
  int nGrade1100; // eax  | +0x044C → 物件档位/编号末位解析槽（CNBlessFairy；va=0062C510）
  int v3; // edx
  int v4; // eax

  nGrade1100 = *(this + 275);  // 读字段 fld_e275 = this+275
  v3 = 0;
  if ( nGrade1100 != 0 )
  {
    v4 = nGrade1100 - 1;  // 计算 v4 = fld_e275 - 1
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
  return (*(int (/*thiscall*/ **)(int, int, int, uint32_t *))(*(uint32_t *)nArg2 + 768))(nArg2, 13, v3, this);  // 虚调用 vt+768（nArg2 虚表槽）
}



// ------------------------------------------------------------
// 0x62C2A0 CNInvinsibleFairy__vmt2F4 —— 【妖精·无敌】施放 vmt2F4
//    按 +1100 档位取 7000/15000/30000，先 sub_49C620(1,1,0) 下命令包，再 sub_49C5F0(1,0,0,v3) 写命令记录。
// ------------------------------------------------------------
int /*thiscall*/ CNInvinsibleFairy__vmt2F4(uint32_t *this, int nArg2)  // 实现：(妖精·无敌)施放 vmt2F4
{
  int nFairyGrade; // eax  | +0x044C → 【推断】妖精档位/缩放档（编号末位 0/1/2）〔62C5F0 解析末位写入（CNInvinsibleFairy；va=0062C510）
  int v3; // esi
  int v4; // eax

  nFairyGrade = *(this + 275);  // 读字段 fld_e275 = this+275
  v3 = 0;
  if ( nFairyGrade != 0 )
  {
    v4 = nFairyGrade - 1;  // 计算 v4 = fld_e275 - 1
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
  sub_49C620(1, 1, 0);  // sub_49C620 —— 命令下发包装（组 id = this+4，值重复两遍）
  return sub_49C5F0(1, 0, 0, v3);  // sub_49C5F0 —— 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
}



// ------------------------------------------------------------
// 0x62C2F0 CNHPFairy__vmt2F4 —— 【妖精·HP】施加 vmt2F4
//    sub_62C000 取 HP 吸取量(v8)与时长(v9)，new(0x80) 经 sub_4D6810 造 CNChangeHp 后虚 56 附着到来客（延后结算）。
// ------------------------------------------------------------
int /*thiscall*/ CNHPFairy__vmt2F4(uint32_t *this, void *Block)  // 实现：(妖精·HP)施加 vmt2F4
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
  sub_62C000(this, (int)Block, &v8, &v9);  // sub_62C000 —— HP 吸取量计算（档位 1/3、1/2、全量）
  Blocka = operator new(0x80u);  // 堆分配
  v10 = 0;
  if ( Blocka != nullptr )  // 若 Blocka 有效（非空）
  {
    v7 = (float)v8;
    v4 = (int *)sub_4D6810(LODWORD(v7), v9, 1, 1);  // sub_4D6810 —— 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
  }
  else
  {
    v4 = nullptr;
  }
  v5 = *v4;
  v10 = -1;
  return (*(int (/*thiscall*/ **)(int *, void *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v5 + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
           v4,
           Block,
           this,
           0,
           0,
           0,
           -1);
}



// ------------------------------------------------------------
// 0x62C390 CNMPFairy__vmt2F4 —— 【妖精·MP】施加 vmt2F4
//    与 CNHPFairy__vmt2F4 同构（差异：sub_62C090 取 MP 量、sub_50F270 造 CNChangeMp）。
// ------------------------------------------------------------
int /*thiscall*/ CNMPFairy__vmt2F4(uint32_t *this, int nArg2)  // 实现：(妖精·MP)施加 vmt2F4
{
  int *v4; // eax
  int v5; // edx
  int v7; // [esp+8h] [ebp-14h] BYREF
  int v8; // [esp+Ch] [ebp-10h] BYREF
  int v9; // [esp+18h] [ebp-4h]
  void *pMem; // [esp+24h] [ebp+8h]

  v7 = 0;
  v8 = 0;
  sub_62C090(this, nArg2, &v7, &v8);  // sub_62C090 —— MP 吸取量计算
  pMem = operator new(0x64u);  // 堆分配
  v9 = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = (int *)sub_50F270(v7, v8);  // sub_50F270 —— CNChangeMp 构造（vftbl_CNChangeMp + sub_602070 基类 + sub_602380 初值）
  else
    v4 = nullptr;
  v5 = *v4;
  v9 = -1;
  return (*(int (/*thiscall*/ **)(int *, int, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v5 + 56))(v4, nArg2, this, 0, 0, 0, -1);  // 虚函数调用 槽+56：确认动作：+84 标志时 4
}



// ------------------------------------------------------------
// 0x62C430 CNHPMPFairy__vmt2F4 —— 【妖精·HP+MP】施加 vmt2F4
//    sub_62C120 取 HP(v11)/MP(v10) 两份量与时长效 v12，先后以 sub_4D6810 造 CNChangeHp、sub_50F270 造 CNChangeMp，各虚 56 附着（双吸取延后结算）。
// ------------------------------------------------------------
int /*thiscall*/ CNHPMPFairy__vmt2F4(uint32_t *this, void *Block)  // 实现：(妖精·HP+MP)施加 vmt2F4
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
  sub_62C120(this, (int)Block, &v11, &v10, &v12);  // sub_62C120 —— HP+MP 双吸取量计算
  Blocka = operator new(0x80u);  // 堆分配
  v13 = 0;
  if ( Blocka != nullptr )  // 若 Blocka 有效（非空）
  {
    v9 = (float)v11;
    v4 = (int *)sub_4D6810(LODWORD(v9), v12, 1, 1);  // sub_4D6810 —— 存 CNChangeHp 回血(伤害值=550.0f, 时长=1000ms)
  }
  else
  {
    v4 = nullptr;
  }
  v5 = *v4;
  v13 = -1;
  (*(void (/*thiscall*/ **)(int *, void *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v5 + 56))(v4, Block, this, 0, 0, 0, -1);  // 虚函数调用 槽+56：确认动作：+84 标志时 4
  Blockb = operator new(0x64u);  // 堆分配
  v13 = 1;
  if ( Blockb != nullptr )  // 若 Blockb 有效（非空）
    v6 = (int *)sub_50F270(v10, v12);  // sub_50F270 —— CNChangeMp 构造（vftbl_CNChangeMp + sub_602070 基类 + sub_602380 初值）
  else
    v6 = nullptr;
  v7 = *v6;
  v13 = -1;
  return (*(int (/*thiscall*/ **)(int *, void *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v7 + 56))(  // 虚函数调用 槽+56：确认动作：+84 标志时 4
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
int /*thiscall*/ CNFairy__vmt14C(int this)  // 函数定义: 位置采样
{
  int v2; // edi
  int nAnchor324; // eax  | +0x0144 → 【推断】帧/层参数槽〔62C510：作 vt+124 第二参换出坐标链 vt+124→vt+120→vt+112（CNFairy；va=0062C510）
  int pThis_78; // eax
  int v5; // edi
  int pThis_34; // eax
  int result; // eax
  int pResTbl712; // edi  | +0x02C8 → 【推断】资源/动画句柄表基指针〔60B3D0 逐 4 字节取子句柄交 sub_41ACF0（CNFairy；va=0062C510）
  int pThis_40; // eax
  int pThis_98; // [esp-8h] [ebp-18h]
  int nCycleDeadline; // [esp+Ch] [ebp-4h]  | +0x046C → 【推断】漂浮循环周期截止时刻〔62C510: clock_now（CNFairy；va=0062C510）

  CNMapObject__vmt14C((int *)this);
  if ( *(uint8_t *)(this + 1105) == 0 )  // this+1105 漂浮音一次性门
  {
    v2 = *(uint32_t *)this;
    nAnchor324 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 124))(this, *(uint32_t *)(this + 324));  // 虚调用 vt+124（this）目标坐标y下界
    pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, nAnchor324);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(int, int))(v2 + 112))(this, pThis_78);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
    v5 = *(uint32_t *)this;
    pThis_34 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)this + 52))(this, 0, 0);  // 虚调用 vt+52（this）归属坐标y
    (*(void (/*thiscall*/ **)(int, const char *, int))(v5 + 212))(this, "TINGKERBELL_FLOAT_LOOP", pThis_34 + 39210);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
    *(uint8_t *)(this + 1105) = 1;  // 写字段 this+1105（bFloatLoopLatch） ← 1
    *(uint8_t *)(this + 1121) = 0;  // 写字段 this+1121（bCycleRstA） ← 0
    *(uint8_t *)(this + 1122) = 0;  // 写字段 this+1122（bCycleRstB） ← 0
    sub_698F90(this + 1108, 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  nCycleDeadline = *(uint32_t *)(this + 1132);  // 读字段 fld_46C = this+1132（nCycleDeadline）
  result = sub_699000(this + 1108);  // 【clock_now(clk)】
  if ( result >= nCycleDeadline )
  {
    *(uint8_t *)(this + 1121) = 0;  // 写字段 this+1121（bCycleRstA） ← 0
    *(uint8_t *)(this + 1122) = 0;  // 写字段 this+1122（bCycleRstB） ← 0
    sub_698F90(this + 1108, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    pResTbl712 = sub_41ACF0(*(uint32_t *)(this + 712) + 4 * *(uint32_t *)(this + 1100) + 32);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    pThis_98 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);  // 虚调用 vt+152（this）取值(参数)
    pThis_40 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 64))(this);  // 虚调用 vt+64（this）读游标登记(跳过包头)
    return sub_50EF20(pThis_40, pResTbl712, pThis_98, 3000);  // 气泡文本设置与量算（行数/半高/倒计时）
  }
  return result;
}



// ------------------------------------------------------------
// 0x62C5F0 sub_62C5F0 —— 妖精工厂参数装载（数位解析）
//    先虚 204(100,表[0])+虚 372(100) 复位、清 +1105；把 nArg2 十进制串末位(0/1/2) 写 +1100 作缩放档、十位(0/1) 写 +1104，后者非 0 时再虚 204(200,表[1]) 加第二件；
//    按档取 0.7/1.0/1.3 经 sub_4922F0 两次统设全帧与盒缩放，末清 +1106。
// ------------------------------------------------------------
int /*thiscall*/ sub_62C5F0(uint32_t **this, int nArg2)  // sub_62C5F0 —— 妖精工厂参数装载（数位解析）
{
  uint32_t *v3; // edx
  unsigned int nLen; // kr00_4
  unsigned int nLen2; // kr04_4
  int fld_e275; // ecx
  int fld_e2752; // ecx
  int result; // eax
  float v9; // [esp+8h] [ebp-1Ch]
  int v10; // [esp+Ch] [ebp-18h]
  int v11; // [esp+10h] [ebp-14h]
  char Buffer[12]; // [esp+14h] [ebp-10h] BYREF
  int dword_796E502; // [esp+20h] [ebp-4h]

  v3 = *this;
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))v3[51])(
    this,
    100,
    **(this + 36),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  ((void (/*thiscall*/ *)(uint32_t **, int))(*this)[93])(this, 100);
  *((uint8_t *)this + 1105) = 0;  // 写字段 this+1105（bFloatLoopLatch）
  sprintf(Buffer, "%d", nArg2);  // 调 格式化到缓冲
  nLen = strlen(Buffer);  // 调 求串长
  switch ( Buffer[nLen - 1] )  // 按 Buffer[nLen - 1] 分派
  {
    case '0':
      *(this + 275) = nullptr;  // 写字段 this+275 ← nullptr
      break;
    case '1':
      *(this + 275) = (uint32_t *)1;  // 写字段 this+275 ← (uint32_t *)1
      break;
    case '2':
      *(this + 275) = (uint32_t *)2;  // 写字段 this+275 ← (uint32_t *)2
      break;
    default:
      break;
  }
  nLen2 = strlen(Buffer);  // 调 求串长
  if ( Buffer[nLen2 - 2] == 48 )
  {
    *((uint8_t *)this + 1104) = 0;  // 写字段 this+1104（nResetClock1104）
  }
  else if ( Buffer[nLen2 - 2] == 49 )
  {
    *((uint8_t *)this + 1104) = 1;  // 写字段 this+1104（nResetClock1104）
  }
  if ( *((uint8_t *)this + 1104) != 0 )  // this+1104 时钟槽 B
    ((void (/*thiscall*/ *)(uint32_t **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[51])(
      this,
      200,
      (*(this + 36))[1],  // this+36 物品状态字
      0,
      0,
      0,
      0);
  fld_e275 = (int)*(this + 275);  // this+1100〔nFairyGrade(推断)〕
  v9 = 0.69999999;  // 浮点常量 v9 ← 0.69999999
  v10 = 1065353216;  // 常量 1.0f
  v11 = 1067869798;  // 浮点常量 1.3f
  sub_4922F0(*(&v9 + fld_e275));  // sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
  fld_e2752 = (int)*(this + 275);  // this+1100〔nFairyGrade(推断)〕
  v9 = 0.69999999;  // 浮点常量 v9 ← 0.69999999
  v10 = 1065353216;  // 常量 1.0f
  v11 = 1067869798;  // 浮点常量 1.3f
  result = sub_4922F0(*(&v9 + fld_e2752));  // sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
  *((uint8_t *)this + 1106) = 0;  // 写字段 this[1106]（宽1字节）
  return result;
}



// ------------------------------------------------------------
// 0x62C740 sub_62C740 —— 妖精多目标吸取绑定
//    遍历 +116 件对象数组(+120/+124) 中类别(虚 40)=273 者：其归属(虚 376) 与 nArg2 相同时虚 756(this,该对象) 逐个施加（+1104 决定走本函数或单目标虚 756）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62C740(uint32_t *this, int nArg2)  // sub_62C740 —— 妖精多目标吸取绑定
{
  uint32_t *pThis; // ebx
  unsigned int i; // edi
  int v4; // ecx
  int v5; // edx
  int result; // eax
  int v7; // edx
  int pObj2; // ecx
  int v9; // ecx
  int v10; // edx
  int pObj; // esi
  int v12; // ebx
  bool v13; // zf

  pThis = this;
  for ( i = 0; ; ++i )
  {
    v4 = pThis[29];
    v5 = *(uint32_t *)(v4 + 120);  // 读字段 v5 = v4+120（pAnimObj）
    result = v5 != 0 ? (*(uint32_t *)(v4 + 124) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    v7 = *(uint32_t *)(v4 + 120);  // 读字段 v7 = v4+120（pAnimObj）
    if ( v7 != 0 && i < (*(uint32_t *)(v4 + 124) - v7) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj2 = *(uint32_t *)(v7 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 273) != 0 )  // 虚调用 vt+40（pObj2）条件查询(273等)
    {
      v9 = pThis[29];
      v10 = *(uint32_t *)(v9 + 120);  // 读字段 v10 = v9+120（pAnimObj）
      if ( v10 != 0 && i < (*(uint32_t *)(v9 + 124) - v10) >> 2 )  // 向量元素数 = (end−begin)/4
      {
        pObj = *(uint32_t *)(v10 + 4 * i);
        if ( pObj != 0 )
        {
          v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 虚调用 vt+376（pObj 虚表槽）
          v13 = v12 == (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);  // 虚调用 vt+376（nArg2 虚表槽）
          pThis = this;
          if ( v13 )
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 756))(this, pObj);  // 虚调用 vt+756（this 虚表槽）
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
int /*userpurge*/ CNMPFairy__vmt1F4@<eax>(uint8_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *pArg3, int nArg4, int nArg5)  // 实现：(妖精·MP)TINGKERBELL_MP_ABSORB
{
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v12; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 40))(pArg3, 273) == 1 && pArg1[264] == 0 && pArg1[1106] == 0 )  // 虚调用 vt+40（pArg3）条件查询(273等)
  {
    v6 = *(uint32_t *)pArg1;
    pArg1[1106] = 1;
    v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(v6 + 52))(pArg1, nArg2);  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v6 + 216))(pArg1, v7 + 39210);  // 虚函数调用 槽+216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212（pArg1 虚表槽）
      pArg1,
      "TINGKERBELL_MP_ABSORB",  // 资源/动画 TAG TINGKERBELL_MP_ABSORB
      -1,
      0,
      0);
    v12 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
            (int)pArg3,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDCharacter `RTTI Type Descriptor',
            0);
    if ( pArg1[1104] != 0 )
      sub_62C740(pArg1, v12);  // sub_62C740 —— 妖精多目标吸取绑定
    else
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 756))(pArg1, v12);  // 虚调用 vt+756（pArg1 虚表槽）
    if ( pArg3[78] < 0x10u )
      v8 = pArg3 + 73;  // 计算 v8 = pArg3 + 73
    else
      v8 = (uint32_t *)pArg3[73];
    v9 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)pArg1 + 52))(pArg1, v8);  // 虚调用 vt+52（pArg1）归属坐标y
    off_77F3FC((char *)&byte_73DD1C, v9);  // off_77F3FC —— 日志打印（printf 风格）
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)pArg1 + 736))(pArg1, pArg3);  // 虚调用 vt+736（pArg1 虚表槽）
  }
  return 0;
}



// ------------------------------------------------------------
// 0x62C8F0 CNHPMPFairy__vmt1F4
//   【妖精·HP+MP】TINGKERBELL_ALL_ABSORB
// ------------------------------------------------------------
int /*userpurge*/ CNHPMPFairy__vmt1F4@<eax>(uint8_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *pArg3, int nArg4, int nArg5)  // 实现：(妖精·HP+MP)TINGKERBELL_ALL_ABSORB
{
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v12; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 40))(pArg3, 273) == 1 && pArg1[264] == 0 && pArg1[1106] == 0 )  // 虚调用 vt+40（pArg3）条件查询(273等)
  {
    v6 = *(uint32_t *)pArg1;
    pArg1[1106] = 1;
    v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(v6 + 52))(pArg1, nArg2);  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v6 + 216))(pArg1, v7 + 39210);  // 虚函数调用 槽+216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212（pArg1 虚表槽）
      pArg1,
      "TINGKERBELL_ALL_ABSORB",  // 资源/动画 TAG TINGKERBELL_ALL_ABSORB
      -1,
      0,
      0);
    v12 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
            (int)pArg3,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDCharacter `RTTI Type Descriptor',
            0);
    if ( pArg1[1104] != 0 )
      sub_62C740(pArg1, v12);  // sub_62C740 —— 妖精多目标吸取绑定
    else
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 756))(pArg1, v12);  // 虚调用 vt+756（pArg1 虚表槽）
    if ( pArg3[78] < 0x10u )
      v8 = pArg3 + 73;  // 计算 v8 = pArg3 + 73
    else
      v8 = (uint32_t *)pArg3[73];
    v9 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)pArg1 + 52))(pArg1, v8);  // 虚调用 vt+52（pArg1）归属坐标y
    off_77F3FC((char *)&byte_73DD1C, v9);  // off_77F3FC —— 日志打印（printf 风格）
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)pArg1 + 736))(pArg1, pArg3);  // 虚调用 vt+736（pArg1 虚表槽）
  }
  return 0;
}



// ------------------------------------------------------------
// 0x62C9E0 CNHPFairy__vmt1F4
//   【妖精·HP】TINGKERBELL_HP_ABSORB
// ------------------------------------------------------------
int /*userpurge*/ CNHPFairy__vmt1F4@<eax>(uint8_t *pArg1@<ecx>, int nArg2@<edi>, uint32_t *pArg3, int nArg4, int nArg5)  // 实现：(妖精·HP)TINGKERBELL_HP_ABSORB
{
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // eax
  int v9; // eax
  int v12; // [esp-4h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg3 + 40))(pArg3, 273) == 1 && pArg1[264] == 0 && pArg1[1106] == 0 )  // 虚调用 vt+40（pArg3）条件查询(273等)
  {
    v6 = *(uint32_t *)pArg1;
    pArg1[1106] = 1;
    v7 = (*(int (/*thiscall*/ **)(uint8_t *, int))(v6 + 52))(pArg1, nArg2);  // 虚函数调用 槽+52：播 AURA_SHIELD_LOOP（第二挂点，15 行）
    (*(void (/*thiscall*/ **)(uint8_t *, int))(v6 + 216))(pArg1, v7 + 39210);  // 虚函数调用 槽+216：音效 TAG 查询
    (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(  // 虚调用 vt+212（pArg1 虚表槽）
      pArg1,
      "TINGKERBELL_HP_ABSORB",  // 资源/动画 TAG TINGKERBELL_HP_ABSORB
      -1,
      0,
      0);
    v12 = __RTDynamicCast(  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
            (int)pArg3,
            0,
            &IRDCollisionObject `RTTI Type Descriptor',
            &IRDCharacter `RTTI Type Descriptor',
            0);
    if ( pArg1[1104] != 0 )
      sub_62C740(pArg1, v12);  // sub_62C740 —— 妖精多目标吸取绑定
    else
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 756))(pArg1, v12);  // 虚调用 vt+756（pArg1 虚表槽）
    if ( pArg3[78] < 0x10u )
      v8 = pArg3 + 73;  // 计算 v8 = pArg3 + 73
    else
      v8 = (uint32_t *)pArg3[73];
    v9 = (*(int (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)pArg1 + 52))(pArg1, v8);  // 虚调用 vt+52（pArg1）归属坐标y
    off_77F3FC((char *)&byte_73DD1C, v9);  // off_77F3FC —— 日志打印（printf 风格）
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *))(*(uint32_t *)pArg1 + 736))(pArg1, pArg3);  // 虚调用 vt+736（pArg1 虚表槽）
  }
  return 0;
}



// ------------------------------------------------------------
// 0x62CAD0 CNSuperArmorFairy__vmt2F4 —— 【妖精·霸体】施加 vmt2F4
//    按 +1100 档位取 7000/15000/30000，new(0x64) 经 sub_51A7D0 构造后把时长写入虚 64 结果 +40，末虚 56 附着到来客。
// ------------------------------------------------------------
int /*thiscall*/ CNSuperArmorFairy__vmt2F4(uint32_t *this, int nArg2)  // 实现：(妖精·霸体)施加 vmt2F4
{
  int nFairyGrade; // eax  | +0x044C → 【推断】妖精档位/缩放档（编号末位 0/1/2）〔62C5F0 解析末位写入（CNSuperArmorFairy；va=0062C510）
  uint32_t *v4; // esi
  int v5; // edi
  int v6; // eax
  uint32_t *pMem; // eax

  nFairyGrade = *(this + 275);  // 读字段 fld_e275 = this+275
  v4 = nullptr;
  v5 = 0;
  if ( nFairyGrade != 0 )
  {
    v6 = nFairyGrade - 1;  // 计算 v6 = fld_e275 - 1
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
  pMem = operator new(0x64u);  // 堆分配
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_51A7D0(pMem);  // 调 构造后把时长写入虚 64 结果 +40
  *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 64))(v4) + 40) = v5;  // 虚调用 vt+64（v4）读游标登记(跳过包头)
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*v4 + 56))(  // 虚调用 vt+56（v4 虚表槽）
           v4,
           nArg2,
           this,
           0,
           0,
           0,
           -1);
}



// ------------------------------------------------------------
// 0x62CB70 CNFairy__vmt2E0 —— 【妖精】双件动画构建 vmt2E0
//    new(228) 以自身名（SSO 或指针）与 +712 表(+24) 句柄(sub_41ACF0)经 sub_431920 建首件动画件（+1104 非 0 时再以表(+28) 建第二件），两件各以 sub_44B6C0(284)+sub_44E0D0 池化、经 sub_45FE80 挂到虚 80 场景并按虚 120/124/128 链定位；
//    按 +1100 档取 0.7/1.0/1.3 经 sub_4922F0 统设缩放；再虚 212 播 +1040 名；存活(虚 308) 时虚 312(0) 停用并以 off_77F3FC 记 byte_73DD84；末虚 596(0)。
// ------------------------------------------------------------
int /*thiscall*/ sub_62CB70(uint32_t *this, int nArg2)  // 【CNFairy__vmt2E0】
{
  int v3; // ebx
  int fld_16C; // ebx  | +0x016C → 动画件名缓冲 SSO 内联首址〔60B3D0：+384<0x10 时取 this+364 名交 sub_4C3640（CNFairy；va=0060B3D0）
  char pResTbl712; // al  | +0x02C8 → 【推断】资源/动画句柄表基指针〔60B3D0 逐 4 字节取子句柄交 sub_41ACF0（CNFairy；va=0062C510）
  int nFairyGrade; // eax  | +0x044C → 【推断】妖精档位/缩放档（编号末位 0/1/2）〔62C5F0 解析末位写入（CNFairy；va=0062C510）
  char *v7; // eax
  char *v8; // edi
  int v9; // edx
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int fld_e912; // edi
  char fld_e1782; // al
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
  int pThis_104; // eax
  int v28; // eax
  float v30; // [esp-4h] [ebp-2Ch]
  float v31[3]; // [esp+Ch] [ebp-1Ch]
  int v32; // [esp+18h] [ebp-10h]
  int v33; // [esp+24h] [ebp-4h]

  v32 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
  v3 = 0;
  v33 = 0;
  if ( v32 != 0 )
  {
    if ( *(this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
      LOBYTE(fld_16C) = (uint8_t)this + 108;  // this+108 第 1 组·宿主属性 +886 增量
    else
      fld_16C = *(this + 91);  // 读字段 fld_e91 = this+91
    pResTbl712 = sub_41ACF0(*(this + 178) + 24);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    v3 = sub_431920(fld_16C, pResTbl712, 1);  // sub_431920 —— 动画件构造（文件名版）
  }
  nFairyGrade = *(this + 275);  // 读字段 fld_e275 = this+275
  v31[0] = 0.69999999;
  v31[1] = 1.0;
  v31[2] = 1.3;
  v30 = v31[nFairyGrade];
  v33 = -1;
  sub_4922F0(v30);  // sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
  v7 = (char *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
  v8 = v7;
  v32 = (int)v7;
  v33 = 1;
  if ( v7 != nullptr )  // 若 v7 有效（非空）
  {
    sub_44E0D0(v7, v3, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
    *(uint32_t *)v8 = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
  }
  else
  {
    v8 = nullptr;
  }
  v9 = *this;
  v33 = -1;
  v10 = (*(int (/*thiscall*/ **)(uint32_t *))(v9 + 80))(this);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
  sub_45FE80(v10, (int)v8, 2, 0, (int)v8, (int)this, 0);  // sub_45FE80 —— 对象注册
  v11 = *(uint32_t *)v8;
  v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
  v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v12);  // 虚调用 vt+124（this）目标坐标y下界
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v13);  // 虚调用 vt+120（this）转发(对象+缓冲)
  (*(void (/*thiscall*/ **)(char *, int))(v11 + 112))(v8, v14);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  if ( *((uint8_t *)this + 1104) != 0 )  // this+1104 时钟槽 B
  {
    v32 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v33 = 2;
    if ( v32 != 0 )
    {
      if ( *(this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
        LOBYTE(v15) = (uint8_t)this + 108;  // this+108 第 1 组·宿主属性 +886 增量
      else
        v15 = *(this + 91);  // 读字段 v15 = this+91
      v16 = sub_41ACF0(*(this + 178) + 28);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      v17 = sub_431920(v15, v16, 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    else
    {
      v17 = 0;
    }
    v33 = -1;
    v18 = (char *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
    v19 = v18;
    v32 = (int)v18;
    v33 = 3;
    if ( v18 != nullptr )  // 若 v18 有效（非空）
    {
      sub_44E0D0(v18, v17, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)v19 = &CNRDPooledObject::`vftable';  // 写 vftable 指针（对象重定位/复位）
    }
    else
    {
      v19 = nullptr;
    }
    v20 = *this;
    v33 = -1;
    v21 = (*(int (/*thiscall*/ **)(uint32_t *))(v20 + 80))(this);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    sub_45FE80(v21, (int)v19, 2, 0, (int)v19, (int)this, 0);  // sub_45FE80 —— 对象注册
    v22 = *(uint32_t *)v19;
    v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v23);  // 虚调用 vt+124（this）目标坐标y下界
    v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v24);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(char *, int))(v22 + 112))(v19, v25);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
  }
  if ( sub_41ACF0(this + 260) != 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  {
    v26 = *this;
    pThis_104 = sub_41ACF0(this + 260);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(v26 + 212))(this, pThis_104, -1, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
  }
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )  // 虚调用 vt+308（this）是否本地玩家
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 312))(this, 0);  // 虚调用 vt+312（this 虚表槽）
    v28 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 虚调用 vt+52（this）归属坐标y
    off_77F3FC((char *)&byte_73DD84, v28);  // off_77F3FC —— 日志打印（printf 风格）
  }
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 596))(this, 0);  // 虚调用 vt+596（this 虚表槽）
}


// ------------------------------------------------------------
// 0x62CDD0 CNFairyFactory__vmt14C —— 【妖精工厂】产出 vmt14C
//    存活(虚 308) 且 +980=0（无在生妖精）且 clock_now(this+36) ≥ +984（产出间隔）时：+972 为指定 id，-1 则以 GetTickCount()%42 从 2000..2612 表随机取，虚 580(..,4,..) 生成并记 +976；
//    随后清字节 +49/+50，sub_698F90(this+36,0,0) 倒计时归零并 sub_699030 冻结时钟。
// ------------------------------------------------------------
char /*thiscall*/ CNFairyFactory__vmt14C(unsigned int *this)  // 函数定义: 位置采样
{
  unsigned int fld_e245; // eax
  int fld_e243; // eax
  int v4; // ebx
  DWORD TickCount; // eax
  unsigned int v6; // eax
  uint32_t v8[42]; // [esp+4h] [ebp-A8h]

  CNRDPassiveObject__vmt14C((int)this);
  LOBYTE(fld_e245) = (*(int (/*thiscall*/ **)(unsigned int *))(*this + 308))(this);  // 虚调用 vt+308（this）是否本地玩家
  if ( (uint8_t)fld_e245 != 0 )
  {
    fld_e245 = *(this + 245);  // 读字段 fld_e245 = this+245
    if ( fld_e245 == 0 )
    {
      fld_e245 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      if ( fld_e245 >= *(this + 246) )  // this+984〔aStateBlk984(推断)〕
      {
        fld_e243 = *(this + 243);  // 读字段 fld_e243 = this+243
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
        if ( fld_e243 == -1 )
        {
          v4 = *this;
          TickCount = GetTickCount();  // 调 取系统运行毫秒数
          v6 = (*(int (/*thiscall*/ **)(unsigned int *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(v4 + 580))(  // 虚函数调用 槽+580：位置化动作发布（会话 3 定案：位置化动作）
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
          v6 = (*(int (/*thiscall*/ **)(unsigned int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(  // 虚调用 vt+580（this）音效/技能播放(12参)
                 this,
                 fld_e243,
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
        *(this + 244) = v6;  // 写字段 this+244（fSyncValue） ← v6
        *((uint8_t *)this + 49) = 0;  // 写字段 this+49（bUdpReported）
        *((uint8_t *)this + 50) = 0;  // 写字段 this+50（bCharSelSent）
        sub_698F90((int)(this + 9), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        LOBYTE(fld_e245) = sub_699030((int)(this + 9));  // 【clock_freeze(clk)】
      }
    }
  }
  return fld_e245;
}



// ------------------------------------------------------------
// 0x62CFF0 CNFairyFactory__vmt12C —— 【妖精工厂】卸载 vmt12C
//    基类后，卸载对象等于 +980（在生妖精）时清 +980、sub_698FE0 解冻时钟并把 +976 复 0xFFFF。
// ------------------------------------------------------------
void /*thiscall*/ CNFairyFactory__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( nArg2 == *(this + 245) )  // this+980〔uCfgF980(推断)〕
  {
    *(this + 245) = 0;  // 写字段 this+245 ← 0
    sub_698FE0((int)(this + 9));  // 【clock_unfreeze(clk)】
    *(this + 244) = 0xFFFF;  // 写字段 this+244（fSyncValue） ← 0xFFFF
  }
}



// ------------------------------------------------------------
// 0x62D030 CNFairyFactory__vmt128 —— 【妖精工厂】归巢登记 vmt128
//    对来客做 CNFairy RTTI 判定：其编号(虚 52) 等于 +976（本次应产 id）且 +980 为 0 时把该妖精登记进 +980。
// ------------------------------------------------------------
int /*thiscall*/ CNFairyFactory__vmt128(int *this, int nArg2)  // 实现：(妖精工厂)归巢登记 vmt128
{
  int result; // eax

  result = __RTDynamicCast(nArg2, 0, &CNRDObject `RTTI Type Descriptor', &CNFairy `RTTI Type Descriptor', 0);  // 调 C++ RTTI 动态转换（失败抛 bad_cast）
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 52))(nArg2);  // 虚调用 vt+52（nArg2）归属坐标y
    if ( result == *(this + 244) )  // this+244 动画同步浮点参数
    {
      result = *(this + 245);  // 读字段 result = this+245
      if ( result == 0 )
        *(this + 245) = nArg2;  // 写字段 this+245 ← nArg2
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D080 CNFairyFactory__vmt140 —— 【妖精工厂】摆位 vmt140
//    +276 非 0 时清字节 +49/+50 并 sub_698F90(this+36,0,0) 倒计时归零，末走基类 CNRDPassiveObject__vmt140。
// ------------------------------------------------------------
char /*thiscall*/ CNFairyFactory__vmt140(uint8_t *this)  // 实现：(妖精工厂)摆位 vmt140
{
  if ( *(this + 276) != 0 )  // this+276 地图条目指针
  {
    *(this + 49) = 0;  // 写字段 this+49（bUdpReported） ← 0
    *(this + 50) = 0;  // 写字段 this+50（bCharSelSent） ← 0
    sub_698F90((int)(this + 36), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return CNRDPassiveObject__vmt140(this);  // 返回 调 CNRDPassiveObject__vmt140
}



// ------------------------------------------------------------
// 0x62D0B0 sub_62D0B0 —— 妖精工厂参数装载（4613 为随机）
//    nArg2=4613 记 +972=-1（随机），否则记 nArg2-2000；再取 +348 表[0] 入 +984（产出间隔）并把 +976 复 0xFFFF、+980 清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_62D0B0(int this, int nArg2)  // sub_62D0B0 —— 妖精工厂参数装载（4613 为随机）
{
  int result; // eax

  if ( nArg2 == 4613 )
    *(uint32_t *)(this + 972) = -1;  // 写字段 this+972（uCfgD972） ← -1
  else
    *(uint32_t *)(this + 972) = nArg2 - 2000;  // 写字段 this+972（uCfgD972） ← nArg2 - 2000
  result = **(uint32_t **)(this + 348);  // this+348 参数表指针
  *(uint32_t *)(this + 984) = result;  // 写字段 this+984（aStateBlk984） ← result
  *(uint32_t *)(this + 976) = 0xFFFF;  // 写字段 this+976（uCfgE976） ← 0xFFFF
  *(uint32_t *)(this + 980) = 0;  // 写字段 this+980（uCfgF980） ← 0
  return result;
}



// ============================================================
// 【分区 18】氛围物件：音效地板/喷泉/重力还原/营火/毒虫/火球（0x62D110-0x62E460）
// 证据: FOUNTAIN_FLOW_LOOP（喷泉）/ CAMPFIRE_LOOP（EPLP 营火）/ NEN_BEGIN（念气起始）/
//       Animation/FireBallStart.ani + MonsterFlower/Particle/PoisonBug.ptl（毒虫）
// ============================================================

// ------------------------------------------------------------
// 0x62D110 CNSoundFloor__vmt2C8 —— 音效地板开合 vmt2C8
//    来客虚 184/虚 188 均为 4 时按 +1104 标志虚 216 停 20801 并清位；否则 +1104=0 时以 +1100 句柄名虚 212 起播 20801 并置位。
// ------------------------------------------------------------
char /*thiscall*/ CNSoundFloor__vmt2C8(uint8_t *this, int nArg2)  // 函数定义: 音效地板开合 vmt2C8
{
  char result; // al
  int v4; // edi
  int pThis_44C; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 184))(nArg2) == 4  // 虚调用 vt+184（nArg2）字符串/朝向写入
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 188))(nArg2) == 4 )  // 虚调用 vt+188（nArg2）取尺寸
  {
    result = *(this + 1104);  // 读字段 result = this+1104（nResetClock1104）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 20801);  // 虚调用 vt+216（this）全场广播
      *(this + 1104) = 0;  // 写字段 this+1104（nResetClock1104） ← 0
    }
  }
  else
  {
    result = *(this + 1104);  // 读字段 result = this+1104（nResetClock1104）
    if ( result == 0 )
    {
      v4 = *(uint32_t *)this;
      pThis_44C = sub_41ACF0(this + 1100);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
      result = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(v4 + 212))(this, pThis_44C, 20801, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
      *(this + 1104) = 1;  // 写字段 this+1104（nResetClock1104） ← 1
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D1A0 CNSoundFloor__vmt2C4 —— 音效地板起播 vmt2C4
//    以 +1100 句柄名虚 212 起播 20801 并置 +1104=1（与 CNSoundFloor__vmt2C8 后半同构）。
// ------------------------------------------------------------
int /*thiscall*/ CNSoundFloor__vmt2C4(char *this, int nArg2)  // 函数定义: 音效地板起播 vmt2C4
{
  int v3; // edi
  int pThis_44C; // eax
  int result; // eax

  v3 = *(uint32_t *)this;
  pThis_44C = sub_41ACF0(this + 1100);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  result = (*(int (/*thiscall*/ **)(char *, int, int, uint32_t, uint32_t))(v3 + 212))(this, pThis_44C, 20801, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
  *(this + 1104) = 1;  // 写字段 this+1104（nResetClock1104） ← 1
  return result;
}



// ------------------------------------------------------------
// 0x62D1D0 CNSoundFloor__vmt2CC —— 音效地板停播 vmt2CC
//    虚 216 停 20801 并清 +1104（与 CNSoundFloor__vmt2C8 前半同构）。
// ------------------------------------------------------------
int /*thiscall*/ CNSoundFloor__vmt2CC(uint8_t *this, int nArg2)  // 函数定义: 音效地板停播 vmt2CC
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 20801);  // 虚调用 vt+216（this）全场广播
  *(this + 1104) = 0;  // 写字段 this+1104（nResetClock1104） ← 0
  return result;
}



// ------------------------------------------------------------
// 0x62D1F0 CNSoundFloor__vmt2F0 —— 音效地板适配判定 vmt2F0
//    来客类别(虚 40)=17 且高度(虚 128)=0 时返真。
// ------------------------------------------------------------
bool /*stdcall*/ CNSoundFloor__vmt2F0(int nArg1)  // 函数定义: 音效地板适配判定 vmt2F0
{
  return (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 40))(nArg1, 17) != 0  // 虚调用 vt+40（nArg1）条件查询(273等)
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg1 + 128))(nArg1) == 0;  // 虚调用 vt+128（nArg1）目标坐标y上界
}



// ------------------------------------------------------------
// 0x62D220 sub_62D220 —— 音效地板动画件重建
//    取 +712 表 4×nArg2+24 处串，sprintf 拼 %d.ani（nArg3 编号）后 new(228) 经 sub_431860 重建 +136 动画件（旧件 sub_42AF90 析构 + sub_657740 池回收），末清 +1104。
// ------------------------------------------------------------
void /*thiscall*/ sub_62D220(int this, int nArg2, int nArg3)  // sub_62D220 —— 音效地板动画件重建
{
  void *fld_2C8; // eax
  int fld_88; // edi
  int v6; // eax
  void **Block2; // ecx
  int v8; // eax
  bool v9; // cf
  int fld_2C82; // [esp-4h] [ebp-240h]
  char Buffer[512]; // [esp+10h] [ebp-22Ch] BYREF
  uint8_t v12[4]; // [esp+210h] [ebp-2Ch] BYREF
  void *Block[5]; // [esp+214h] [ebp-28h] BYREF
  unsigned int v14; // [esp+228h] [ebp-14h]
  int dword_796E502; // [esp+22Ch] [ebp-10h]
  int v16; // [esp+238h] [ebp-4h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  fld_2C8 = (void *)sub_41ACF0(*(uint32_t *)(this + 712) + 4 * nArg2 + 24);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  v14 = 15;
  Block[4] = nullptr;
  LOBYTE(Block[0]) = 0;  // 调 取 16 位值低 8 位
  sub_4015C0(fld_2C8, strlen((const char *)fld_2C8));  // 【std::string构造赋值】
  v16 = 0;
  sprintf(Buffer, "%d.ani", nArg3);  // 调 格式化到缓冲
  sub_4022F0((std::_String_base *)v12, Buffer, strlen(Buffer));  // sub_4022F0 —— std::string::insert(pos, s, n) 模板实例（指定位置插入，qmemcpy 两段搬移）
  fld_88 = *(uint32_t *)(this + 136);  // 读字段 fld_88 = this+136（nCtx136）
  if ( fld_88 != 0 )
  {
    sub_42AF90(*(void ***)(this + 136));  // sub_42AF90 —— 帧对象析构（帧数组 + 元素数组）
    sub_657740(fld_88, 228);  // sub_657740 —— 池化结点弹出（写魔术标记后挂入链头）
  }
  *(uint32_t *)(this + 136) = 0;  // 写字段 this+136（nCtx136） ← 0
  v6 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
  LOBYTE(v16) = 1;  // 调 取 16 位值低 8 位
  if ( v6 != 0 )
  {
    Block2 = (void **)Block[0];
    if ( v14 < 0x10 )
      Block2 = Block;
    v8 = sub_431860(v6, (const char *)Block2, 1);  // sub_431860 —— 动画件构造（资源 id 版）
  }
  else
  {
    v8 = 0;
  }
  fld_2C82 = *(uint32_t *)(this + 712) + 44;  // this+712 【推断】资源/动画句柄表基指针
  LOBYTE(v16) = 0;  // 调 取 16 位值低 8 位
  *(uint32_t *)(this + 136) = v8;  // 写字段 this+136（nCtx136） ← v8
  sub_41B0D0(fld_2C82);  // sub_41B0D0 —— 驻留句柄赋值（旧引用释放 + 新引用 ++）
  v9 = v14 < 0x10;
  *(uint8_t *)(this + 1104) = 0;  // 写字段 this+1104（nResetClock1104） ← 0
  if ( !v9 )
    j__free(Block[0]);  // 释放堆块
}



// ------------------------------------------------------------
// 0x62D380 CNFountain__vmt14C
//   【喷泉】FOUNTAIN_FLOW_LOOP —— 流水循环音
// ------------------------------------------------------------
char /*thiscall*/ CNFountain__vmt14C(int this)  // 函数定义: 位置采样
{
  char result; // al

  CNMapObject__vmt14C((int *)this);
  result = *(uint8_t *)(this + 1100);  // 读字段 result = this+1100（nFairyGrade）
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(  // 虚调用 vt+212（this 虚表槽）
               this,
               "FOUNTAIN_FLOW_LOOP",  // 资源/动画 TAG FOUNTAIN_FLOW_LOOP
               7811,
               0,
               0);
    *(uint8_t *)(this + 1100) = 1;  // 写字段 this+1100（nFairyGrade） ← 1
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D3C0 CNFountain__vmt2E4 —— 【喷泉】初始化 vmt2E4
//    虚 204(100,表+8) 与 204(200,表+12) 双段设层，并清 +1100（起播音标记，与 CNFountain__vmt14C 互斥复位）。
// ------------------------------------------------------------
int /*thiscall*/ CNFountain__vmt2E4(uint32_t *this)  // 实现：(喷泉)初始化 vmt2E4
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
    this,
    100,
    *(uint32_t *)(*(this + 36) + 8),  // this+36 物品状态字
    0,
    0,
    0,
    0);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
             this,
             200,
             *(uint32_t *)(*(this + 36) + 12),  // this+36 物品状态字
             0,
             0,
             0,
             0);
  *((uint8_t *)this + 1100) = 0;  // 写字段 this+1100（nFairyGrade）
  return result;
}



// ------------------------------------------------------------
// 0x62D410 CNFountain__vmt2E8 —— 【喷泉】拆除 vmt2E8
//    基类后虚 208 归还表 +8/+12 两件、置 +945=1；+1040 句柄名有效则虚 212 播报，末虚 216 停 7811（对应 CNFountain__vmt14C 的 FOUNTAIN_FLOW_LOOP）。
// ------------------------------------------------------------
int /*thiscall*/ CNFountain__vmt2E8(int this)  // 实现：(喷泉)拆除 vmt2E8
{
  int v2; // ebx
  int pThis_410; // eax

  CNMapObject__vmt2E8((int *)this);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 8));  // 虚调用 vt+208（this）动画件回挂
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 208))(this, *(uint32_t *)(*(uint32_t *)(this + 144) + 12));  // 虚调用 vt+208（this）动画件回挂
  *(uint8_t *)(this + 945) = 1;  // 写字段 this+945（bBoomDone945） ← 1
  if ( sub_41ACF0(this + 1040) != 0 )  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
  {
    v2 = *(uint32_t *)this;
    pThis_410 = sub_41ACF0(this + 1040);  // sub_41ACF0 —— 结果 = 驻留串句柄 → 字符串指针
    (*(void (/*thiscall*/ **)(int, int, int, uint32_t, uint32_t))(v2 + 212))(this, pThis_410, -1, 0, 0);  // 虚函数调用 槽+212：音效标签播放（szPassword 去重 → sub_65FE10 分发到…
  }
  return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 7811);  // 虚调用 vt+216（this）全场广播
}



// ------------------------------------------------------------
// 0x62D490 sub_62D490 —— 重力件缓冲复位
//    零清 +972、+976、+980、+984、+988、+992、+996 七字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_62D490(int this)  // sub_62D490 —— 重力件缓冲复位
{
  *(uint8_t *)(this + 972) = 0;  // 写字段 this+972（uCfgD972） ← 0
  *(uint32_t *)(this + 976) = 0;  // 写字段 this+976（uCfgE976） ← 0
  *(uint32_t *)(this + 980) = 0;  // 写字段 this+980（uCfgF980） ← 0
  *(uint8_t *)(this + 984) = 0;  // 写字段 this+984（aStateBlk984） ← 0
  *(uint32_t *)(this + 988) = 0;  // 写字段 this+988（uCfgA988） ← 0
  *(uint32_t *)(this + 992) = 0;  // 写字段 this+992（uCfgB992） ← 0
  *(uint32_t *)(this + 996) = 0;  // 写字段 this+996（bCfgC996） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x62D4C0 sub_62D4C0 —— 重力件摇晃偏移
//    自 +996 记录起计时 t，sub_42B420 以 +980×0.01 与 ×0.08 为界作 20000ms 往返插值得 a，返回 (1-sub_405400(360×t/5000%360))×a×0.5。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_62D4C0(int *this)  // sub_62D4C0 —— 重力件摇晃偏移
{
  int fld_e249; // esi
  int fld_e245; // [esp+8h] [ebp-4h]

  fld_e249 = sub_699000((int)(this + 16)) - *(this + 249);  // 【clock_now(clk)】
  fld_e245 = sub_42B420(  // sub_42B420 —— 结果 = 往返插值（三角波）
         (uint64_t)((double)*(this + 245) * 0.0099999998),  // ×0.01f（百分数转比例）
         (uint64_t)(0.079999998 * (double)*(this + 245)),  // this+980〔uCfgF980(推断)〕
         fld_e249,
         20000);
  return (uint64_t)((1.0 - sub_405400(360 * fld_e249 / 5000 % 360)) * (double)fld_e245 * 0.5);  // sub_405400 —— cos 查表（dword_79D154 表，角度 %360 归一含负角修正）
}



// ------------------------------------------------------------
// 0x62D550 sub_62D550 —— 重力件幅度与层设
//    取 +348 表[1] 记入 +980 作插值幅度；再把 +144 键帧表逐项虚 204(i+1,表[i]) 设层。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_62D550(uint32_t *this)  // sub_62D550 —— 重力件幅度与层设
{
  unsigned int result; // eax
  unsigned int i; // ecx
  int fld_e36; // edx
  unsigned int v5; // edi

  result = *(uint32_t *)(*(this + 87) + 4);  // this+348〔pParamTbl348〕
  *(this + 245) = result;  // 写字段 this+245 ← result
  for ( i = 0; ; i = v5 )
  {
    fld_e36 = *(this + 36);  // 读字段 fld_e36 = this+36（nStateWord36）
    if ( fld_e36 == 0 )
      break;
    result = (*(this + 37) - fld_e36) >> 2;  // this+37 【推断】淡入收尾标志 A
    if ( i >= result )
      break;
    v5 = i + 1;  // 计算 v5 = i + 1
    result = (*(int (/*thiscall*/ **)(uint32_t *, unsigned int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
               this,
               i + 1,
               *(uint32_t *)(fld_e36 + 4 * i),
               0,
               0,
               0,
               0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x62D5B0 CNGravityChangeBack__vmt10 —— 重力还原主 tick vmt10
//    +972=0 时先取虚 128 基准写 +976；再以 +348 表[0] 为步长、224×(场景件 +116→+132→+44→+360 的 32 字节元素数)+2×表[0] 为上界复排帧链（外层虚 204(0,+136 件,v8)、内层逐项虚 204(i+1,表[i],v8)），置 +972=1。
//    随后按场景件 +1324 分两路：非 0 时记 +988=虚 128 基准、+992=+976 或 +976++980（按 +1324 符号）并以 sub_4049C0 按 +1352 时长插值；为 0 时以 sub_62D4C0 三角波在 +976(+980) 上来回（符号按 +1320）并记 +996；结果经虚 124/120/112 链落位。
// ------------------------------------------------------------
int /*thiscall*/ sub_62D5B0(int **this)  // 【CNGravityChangeBack__vmt10】
{
  int *fld_e87; // eax
  int v3; // edi
  int fld_e29; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  unsigned int v9; // eax
  int fld_e36; // edx
  unsigned int v11; // edi
  int result; // eax
  int *v13; // edi
  char pThis_3D8; // al
  int fld_e245; // ecx
  int v16; // ebx
  int v17; // eax
  int *v18; // edi
  int v19; // eax
  int v20; // eax
  float uCfgA988; // [esp+18h] [ebp-24h]
  float uCfgB992; // [esp+1Ch] [ebp-20h]
  int v23; // [esp+34h] [ebp-8h]
  int v24; // [esp+38h] [ebp-4h]

  sub_600880();  // 【CNRDPassiveObject__vmt10】
  if ( *((uint8_t *)this + 972) == 0 )  // this+972 叉子缩放计数
  {
    *(this + 244) = (int *)((int (/*thiscall*/ *)(int **))(*this)[32])(this);  // 写字段 this+244（fSyncValue） ← (int *)((int (·thiscall· *)(int **))(*this)[32])(this)
    fld_e87 = *(this + 87);  // 读字段 fld_e87 = this+87
    if ( *fld_e87 != 0 )
    {
      v3 = *fld_e87;
      fld_e29 = *(uint32_t *)((*(this + 29))[33] + 44);  // this+116〔会话上下文〕
      v5 = *(uint32_t *)(fld_e29 + 364);  // 读字段 v5 = fld_e29+364（pAnimNameStr）
      v6 = fld_e29 + 360;  // 计算 v6 = fld_e29 + 360
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
            *(this + 34),  // this+136〔nCtx136(推断)〕
            v8,
            0,
            0,
            0);
          v9 = 0;
          while ( 1 )  // 无限循环
          {
            fld_e36 = (int)*(this + 36);  // this+36 物品状态字
            if ( fld_e36 == 0 || v9 >= ((int)*(this + 37) - fld_e36) >> 2 )  // this+37 【推断】淡入收尾标志 A
              break;
            v11 = v9 + 1;  // 计算 v11 = v9 + 1
            ((void (/*thiscall*/ *)(int **, unsigned int, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this)[51])(
              this,
              v9 + 1,
              *(uint32_t *)(fld_e36 + 4 * v9),
              v8,
              0,
              0,
              0);
            v9 = v11;
            v3 = v24;
          }
          v8 += v3;
        }
        while ( v8 < v23 );  // 循环直到 v8 < v23
      }
    }
    *((uint8_t *)this + 972) = 1;  // 写字段 this+972（uCfgD972）
  }
  result = (int)*(this + 29);  // this+116〔会话上下文〕
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v13 = *(int **)(result + 132);
    if ( v13 != nullptr )  // 若 v13 有效（非空）
    {
      pThis_3D8 = *((uint8_t *)this + 984);  // 读字段 pThis_3D8 = this+984（aStateBlk984）
      if ( v13[331] != 0 )
      {
        if ( pThis_3D8 == 0 )
        {
          *(this + 247) = (int *)((int (/*thiscall*/ *)(int **))(*this)[32])(this);  // 写字段 this+247 ← (int *)((int (·thiscall· *)(int **))(*this)[32])(this)
          if ( v13[331] >= 0 )
            *(this + 248) = (int *)((char *)*(this + 245) + (uint32_t)*(this + 244));  // 写字段 this+248（bParamSlotA） ← (int *)((char *)*(this + 245) + (uint32_t)*(this + 244))
          else
            *(this + 248) = *(this + 244);  // 写字段 this+248（bParamSlotA） ← *(this + 244)
          *((uint8_t *)this + 984) = 1;  // 写字段 this+984（aStateBlk984）
        }
        v16 = v13[338];
        v17 = sub_699000((int)(v13 + 332));  // 【clock_now(clk)】
        uCfgB992 = (float)(int)*(this + 248);  // this+248 重力对象指针
        uCfgA988 = (float)(int)*(this + 247);  // this+988〔uCfgA988(推断)〕
        fld_e245 = (uint64_t)sub_4049C0(uCfgA988, uCfgB992, v17, v16);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      }
      else
      {
        if ( pThis_3D8 != 0 )
        {
          *(this + 249) = (int *)sub_699000((int)(this + 16));  // sub_699000 —— 【clock_now(clk)】
          *((uint8_t *)this + 984) = 0;  // 写字段 this+984（aStateBlk984）
        }
        if ( v13[330] >= 0 )
          fld_e245 = (int)*(this + 245) + (uint32_t)*(this + 244) - sub_62D4C0(this);  // sub_62D4C0 —— 重力件摇晃偏移
        else
          fld_e245 = (int)*(this + 244) + sub_62D4C0(this);  // sub_62D4C0 —— 重力件摇晃偏移
      }
      v18 = *this;
      v19 = ((int (/*thiscall*/ *)(int **, int))(*this)[31])(this, fld_e245);
      v20 = ((int (/*thiscall*/ *)(int **, int))(*this)[30])(this, v19);
      return ((int (/*thiscall*/ *)(int **, int))v18[28])(this, v20);
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x62D7C0 sub_62D7C0 —— 重力件标记复位
//    置 +972=-1 与 +976=0（重力件未初始化标记）。
// ------------------------------------------------------------
void /*thiscall*/ sub_62D7C0(uint32_t *this)  // sub_62D7C0 —— 重力件标记复位
{
  *(this + 243) = -1;  // 写字段 this+243 ← -1
  *(this + 244) = 0;  // 写字段 this+244（fSyncValue） ← 0
}



// ------------------------------------------------------------
// 0x62D7E0 CNEPLPCampFire__vmt12C —— 【营火】卸载 vmt12C
//    基类后，卸载对象即自身时虚 216 停 19879（对应 CNEPLPCampFire__vmt14C 的 CAMPFIRE_LOOP）。
// ------------------------------------------------------------
void /*thiscall*/ CNEPLPCampFire__vmt12C(uint32_t *this, int nArg2)  // 函数定义: 目标移除联动
{
  CNRDPassiveObject__vmt12C(this, nArg2);
  if ( (uint32_t *)nArg2 == this )
    (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 19879);  // 虚调用 vt+216（this）全场广播
}



// ------------------------------------------------------------
// 0x62D810 sub_62D810 —— 类别 17 物件贴位探测
//    遍历虚 80 容器（+8/+12）中类别(虚 40)=17 的物件，对其虚 488 判定为 1 者以自身坐标向外逐 100 步（100..300）经虚 140 命中探测，命中且存活(虚 308) 者虚 108 贴到探得坐标（【推断】推挤或贴位类旁路）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62D810(int *this)  // sub_62D810 —— 类别 17 物件贴位探测
{
  unsigned int i; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int result; // eax
  int v8; // eax
  int v9; // edx
  int pObj; // ecx
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
    v4 = (*(int (/*thiscall*/ **)(int *))(v3 + 80))(this);  // 虚函数调用 槽+80：槽（参数写入 3 转发）
    v5 = *(uint32_t *)(v4 + 8);  // 读字段 v5 = v4+8（nSkillRec8）
    v6 = v4 + 4;  // 计算 v6 = v4 + 4
    result = v5 != 0 ? (*(uint32_t *)(v6 + 8) - v5) >> 2 : 0;  // 向量元素数 = (end−begin)/4
    if ( (int)i >= result )
      break;
    v8 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 虚调用 vt+80（this）读 4 字节
    v9 = *(uint32_t *)(v8 + 8);  // 读字段 v9 = v8+8（nSkillRec8）
    if ( v9 != 0 && i < (*(uint32_t *)(v8 + 12) - v9) >> 2 )  // 向量元素数 = (end−begin)/4
      pObj = *(uint32_t *)(v9 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )  // 虚调用 vt+40（pObj）条件查询(273等)
    {
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 80))(this);  // 虚调用 vt+80（this）读 4 字节
      v12 = *(uint32_t *)(v11 + 8);  // 读字段 v12 = v11+8（nSkillRec8）
      if ( v12 != 0 && i < (*(uint32_t *)(v11 + 12) - v12) >> 2 )  // 向量元素数 = (end−begin)/4
        v13 = *(int **)(v12 + 4 * i);
      else
        v13 = nullptr;
      if ( (*(uint8_t (/*thiscall*/ **)(int *, int *))(*v13 + 488))(v13, this) == 1 )  // 虚调用 vt+488（v13 虚表槽）
      {
        for ( j = 100; ; j = v22 + 100 )
        {
          v22 = j;
          if ( j > 300 )
            break;
          v15 = *v13;
          v16 = (*(int (/*thiscall*/ **)(int *, int, int, int))(*this + 124))(this, j, 1, 1);  // 虚调用 vt+124（this）目标坐标y下界
          v17 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v16);  // 虚调用 vt+120（this）转发(对象+缓冲)
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int *, int *, int))(v15 + 140))(v13, &v20, &v21, v17) != 0 )  // 虚函数调用 槽+140：槽（17 行）
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int *))(*v13 + 308))(v13) != 0 )  // 虚调用 vt+308（v13）是否本地玩家
            {
              v18 = *v13;
              v19 = (*(int (/*thiscall*/ **)(int *))(*v13 + 128))(v13);  // 虚调用 vt+128（v13）目标坐标y上界
              (*(void (/*thiscall*/ **)(int *, int, int, int))(v18 + 108))(v13, v20, v21, v19);  // 虚函数调用 槽+108：槽（10 行）
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
// 0x62D930 sub_62D930 —— 营火状态切换
//    nArg2=1：虚 208 归还表[0]、虚 196(表[1]) 换帧、204(100,表+8)+204(200,表+12) 设层，再 sub_62D810 贴位；nArg2=0：仅 204(100,表[0])；末统一 +972=nArg2。
// ------------------------------------------------------------
int /*thiscall*/ sub_62D930(int *this, int nArg2)  // sub_62D930 —— 营火状态切换
{
  int result; // eax

  if ( nArg2 != 0 )
  {
    result = nArg2 - 1;
    if ( nArg2 == 1 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)*(this + 36));  // 虚调用 vt+208（this）动画件回挂
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 36) + 4));  // 虚调用 vt+196（this）物件非空判定
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
        this,
        100,
        *(uint32_t *)(*(this + 36) + 8),  // this+36 物品状态字
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
        this,
        200,
        *(uint32_t *)(*(this + 36) + 12),  // this+36 物品状态字
        0,
        0,
        0,
        0);
      result = sub_62D810(this);  // sub_62D810 —— 类别 17 物件贴位探测
      *(this + 243) = 1;  // 写字段 this+243 ← 1
      return result;
    }
  }
  else
  {
    result = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(  // 虚调用 vt+204（this 虚表槽）
               this,
               100,
               *(uint32_t *)*(this + 36),  // this+36 物品状态字
               0,
               0,
               0,
               0);
  }
  *(this + 243) = nArg2;  // 写字段 this+243 ← nArg2
  return result;
}



// ------------------------------------------------------------
// 0x62DA00 CNEPLPCampFire__vmtC —— 【营火】构造 vmtC
//    基类后虚 204(100,表[0]) 设首帧层并清 +972。
// ------------------------------------------------------------
int /*thiscall*/ CNEPLPCampFire__vmtC(int this)  // 实现：(营火)构造 vmtC
{
  int result; // eax

  CNRDPassiveObject__vmtC((int *)this);
  result = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 204))(  // 虚调用 vt+204（this 虚表槽）
             this,
             100,
             **(uint32_t **)(this + 144),  // this+144 第 4 组·+1040 增量子倍率
             0,
             0,
             0,
             0);
  *(uint32_t *)(this + 972) = 0;  // 写字段 this+972（uCfgD972） ← 0
  return result;
}



// ------------------------------------------------------------
// 0x62DA40 CNEPLPCampFire__vmt14C
//   【营火】CAMPFIRE_LOOP —— 营火循环音
// ------------------------------------------------------------
int /*thiscall*/ CNEPLPCampFire__vmt14C(int *this)  // 函数定义: 位置采样
{
  int result; // eax

  CNRDPassiveObject__vmt14C((int)this);
  if ( *(this + 244) == 0 )  // this+244 动画同步浮点参数
  {
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CAMPFIRE_LOOP", 19879, 0, 0);  // 虚调用 vt+212（this 虚表槽）
    *(this + 244) = 1;  // 写字段 this+244（fSyncValue） ← 1
  }
  result = *(this + 243);  // 读字段 result = this+243
  if ( result == 0 )
  {
    result = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);  // 虚调用 vt+200（this）取值比较
    if ( *(uint8_t *)(result + 170) != 0 )
      return sub_62D930(this, 1);  // sub_62D930 —— 营火状态切换
  }
  return result;
}



// ------------------------------------------------------------
// 0x62DAA0 sub_62DAA0 —— 毒虫件状态复位
//    清 +972 与字节 +989/+990。
// ------------------------------------------------------------
int /*thiscall*/ sub_62DAA0(int this)  // sub_62DAA0 —— 毒虫件状态复位
{
  *(uint32_t *)(this + 972) = 0;  // 写字段 this+972（uCfgD972） ← 0
  *(uint8_t *)(this + 989) = 0;  // 写字段 this+989（uStateB989） ← 0
  *(uint8_t *)(this + 990) = 0;  // 写字段 this+990（nTargetX990） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x62DAC0 CNPoisonBug__vmt14C —— 【毒虫】粒子重播 vmt14C
//    +1000 到期时清字节 +989/+990、sub_698F90(+976 时钟,50ms)；取 +972 粒子件虚 12 复位后按虚 128/124/120 链摆位、虚 92 取变换包，sub_4600B0(this+116,2,0,包) 播发；末走基类 CNRDPassiveObject__vmt14C。
// ------------------------------------------------------------
int */*thiscall*/ CNPoisonBug__vmt14C(int *this)  // 函数定义: 位置采样
{
  int fld_e250; // ebx
  int pThis_F4; // edi
  int fld_e243; // edi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  void *fld_e29; // ecx
  uint8_t v10[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v12; // [esp+14h] [ebp-14h]
  int v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+24h] [ebp-4h]

  fld_e250 = *(this + 250);  // 读字段 fld_e250 = this+250
  pThis_F4 = (int)(this + 244);  // this+244 动画同步浮点参数
  if ( sub_699000((int)(this + 244)) >= fld_e250 )  // 【clock_now(clk)】
  {
    *(uint8_t *)(pThis_F4 + 13) = 0;  // 写字段 pThis_F4+13 ← 0
    *(uint8_t *)(pThis_F4 + 14) = 0;  // 写字段 pThis_F4+14 ← 0
    sub_698F90(pThis_F4, 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 243) + 12))(*(this + 243), 0);  // 虚函数调用 槽+12：播放强化结果：STRENGTHEN_SUCCESS/STRE
    fld_e243 = *(uint32_t *)*(this + 243);  // this+972〔uCfgD972(推断)〕
    v5 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
    v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v5);  // 虚调用 vt+124（this）目标坐标y下界
    v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v6);  // 虚调用 vt+120（this）转发(对象+缓冲)
    (*(void (/*thiscall*/ **)(uint32_t, int))(fld_e243 + 40))(*(this + 243), v7);  // 虚函数调用 槽+40：槽（548E20/4872A0/549000/4868
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 243) + 92))(*(this + 243), v10);  // 虚函数调用 槽+92：槽（102 行：423200/423290/
    fld_e29 = (void *)*(this + 29);  // this+116〔会话上下文〕
    v14 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v10);  // sub_4600B0 —— 演播层注册(槽号)
    v14 = -1;
    if ( Block != nullptr )  // 若 Block 有效（非空）
      j__free(Block);  // 释放堆块
    Block = nullptr;
    v12 = 0;
    v13 = 0;
  }
  return CNRDPassiveObject__vmt14C((int)this);  // 返回 调 CNRDPassiveObject__vmt14C
}



// ------------------------------------------------------------
// 0x62DBA0 sub_62DBA0
//   【毒虫】PassiveObject/Monster/MonsterFlower/Particle/PoisonBug.ptl —— 毒虫粒子
// ------------------------------------------------------------
int /*thiscall*/ sub_62DBA0(uint32_t *this, int nArg2)  // 实现：(毒虫)PassiveObject/Monster/MonsterFlower/Particle/PoisonBug.ptl —— …
{
  int pThis_F4; // ecx
  uint32_t *pMem; // eax
  uint32_t *v5; // eax

  pThis_F4 = (int)(this + 244);  // this+244 动画同步浮点参数
  *(uint8_t *)(pThis_F4 + 13) = 0;  // 写字段 pThis_F4+13 ← 0
  *(uint8_t *)(pThis_F4 + 14) = 0;  // 写字段 pThis_F4+14 ← 0
  sub_698F90(pThis_F4, 50, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  pMem = operator new(0x12Cu);  // 堆分配
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v5 = sub_428F30(pMem, (int)"PassiveObject/Monster/MonsterFlower/Particle/PoisonBug.ptl", 0);  // sub_428F30 —— 字符串 “Common/CommonEffect/Particle/AttackPowerUp.p”
  else
    v5 = nullptr;
  *(this + 243) = v5;  // 写字段 this+243 ← v5
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*v5 + 104))(v5, nArg2);  // 虚调用 vt+104（v5）并日志
}



// ------------------------------------------------------------
// 0x62DC30 sub_62DC30 —— 火球状态复位
//    清 +972 与 +973（命中发布与起燃动画的首次标志复位）。
// ------------------------------------------------------------
char /*thiscall*/ sub_62DC30(uint8_t *this)  // sub_62DC30 —— 火球状态复位
{
  *(this + 972) = 0;  // 写字段 this+972（uCfgD972） ← 0
  *(this + 973) = 0;  // 写字段 this+973（bLanded973） ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x62DC40 CNFireBallCommon__vmt1F4 —— 【火球】命中发布 vmt1F4
//    先虚 648(pArg2,&v14,this) 做受击判定；pszArg4=0、v14>0、+972=0 且目标存活(虚 308) 时，取虚 384(this,2)、+692 宿主(或自身)、+704 与虚 120/124/128/152 经 sub_4E4A50 发布（发包 type 21），置 +972=1；末走基类 CNRDPassiveObject__vmt1F4。
// ------------------------------------------------------------
int /*thiscall*/ CNFireBallCommon__vmt1F4(int *this, uint32_t *pArg2, float *pArg3, char pszArg4)  // 实现：(火球)命中发布 vmt1F4
{
  uint32_t *pArg22; // edi
  int v5; // eax
  int v7; // ebx
  int *pThis; // edi
  int v9; // eax
  int v11; // [esp-1Ch] [ebp-28h]
  int v12; // [esp-18h] [ebp-24h]
  int v13; // [esp-14h] [ebp-20h]
  int v14; // [esp+8h] [ebp-4h] BYREF

  pArg22 = pArg2;
  v5 = *pArg2;
  v14 = 100;
  (*(void (/*thiscall*/ **)(uint32_t *, int *, int *))(v5 + 648))(pArg2, &v14, this);  // 虚函数调用 槽+648：写入 100（格挡/减伤基础值槽）
  if ( pszArg4 == 0 && v14 > 0 && *((uint8_t *)this + 972) == 0 )  // this+972 叉子缩放计数
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg2 + 308))(pArg2) != 0 )  // 虚调用 vt+308（pArg2）是否本地玩家
    {
      v7 = (*(int (/*thiscall*/ **)(int *, int))(*this + 384))(this, 2);  // 虚调用 vt+384（this 虚表槽）
      pThis = this;
      if ( *(this + 173) != 0 )  // this+173 动画辅助标志
        pThis = (int *)*(this + 173);  // this+173 动画辅助标志
      v13 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);  // 虚调用 vt+152（this）取值(参数)
      v12 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
      v11 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this);  // 虚调用 vt+124（this）目标坐标y下界
      v9 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);  // 虚调用 vt+120（this）转发(对象+缓冲)
      sub_4E4A50(pThis, v7, *(this + 176), v9, v11, v12, v13, 0, 0, 0);  // sub_4E4A50 —— 动作/技能发布打包（发包 type 21，双实体 id 对 + 动作 id）
      pArg22 = pArg2;
    }
    *((uint8_t *)this + 972) = 1;  // 写字段 this+972（uCfgD972）
  }
  return CNRDPassiveObject__vmt1F4(this, pArg22, pArg3, pszArg4);  // 返回 调 CNRDPassiveObject__vmt1F4
}



// ------------------------------------------------------------
// 0x62DD10 sub_62DD10
//   【火球】NEN_BEGIN —— 念气起始事件派发
// ------------------------------------------------------------
int /*thiscall*/ sub_62DD10(float *this, int nArg2)  // 实现：(火球)NEN_BEGIN —— 念气起始事件派发
{
  float v4; // [esp+8h] [ebp-1Ch]
  float pThis_1802; // [esp+Ch] [ebp-18h]
  int pThis_180; // [esp+1Ch] [ebp-8h]
  float v7; // [esp+2Ch] [ebp+8h]

  pThis_180 = (*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);  // 虚调用 vt+384（this 虚表槽）
  pThis_1802 = (float)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);  // 虚调用 vt+384（this 虚表槽）
  v4 = (float)pThis_180;
  v7 = (double)(int)(uint64_t)sub_4049C0(v4, pThis_1802, nArg2, 25) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(this + 244) = v7;  // 写字段 this+244（fSyncValue） ← v7
  sub_4922F0(v7);  // sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
  return sub_4015C0("NEN_BEGIN", 9u);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x62DDA0 CNFireBallCommon__vmt14C
//   【火球】Animation/FireBallStart.ani —— 起燃动画
// ------------------------------------------------------------
int */*thiscall*/ CNFireBallCommon__vmt14C(uint8_t *this)  // 函数定义: 位置采样
{
  int v2; // eax
  int v3; // ebx
  const char *pThis_16C; // ecx
  char *v5; // eax
  char *v6; // edi
  int pThis_1D; // ecx
  int v8; // ebx
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  int v12; // ebx
  int pThis_98; // eax

  if ( *(this + 973) == 0 )  // this+973 落地一次性门
  {
    *(this + 973) = 1;  // 写字段 this+973（bLanded973） ← 1
    v2 = sub_42FCB0(228);  // sub_42FCB0 —— 结果 = CRT 一次性初始化
    v3 = 0;
    if ( v2 != 0 )
    {
      if ( *((uint32_t *)this + 96) < 0x10u )  // this+96 插值终点 X / 落点偏移
        pThis_16C = this + 364;  // this+364 动画件名缓冲 SSO 内联首址
      else
        pThis_16C = *((const char **)this + 91);
      v3 = sub_431920(v2, pThis_16C, "Animation/FireBallStart.ani", 1);  // sub_431920 —— 动画件构造（文件名版）
    }
    sub_4922F0(*((float *)this + 244));  // sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
    v5 = (char *)sub_44B6C0(284);  // sub_44B6C0 —— 结果 = CRT 一次性池初始化 2（池 &unk_98B6F8）
    v6 = v5;
    if ( v5 != nullptr )  // 若 v5 有效（非空）
    {
      sub_44E0D0(v5, v3, 1);  // sub_44E0D0 —— CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
      *(uint32_t *)v6 = &vftbl_CNRDPooledObject;  // 构造装配 vftable：CNRDPooledObject
    }
    else
    {
      v6 = nullptr;
    }
    pThis_1D = *((uint32_t *)this + 29);  // 读字段 pThis_1D = this[29]
    if ( pThis_1D != 0 )
    {
      sub_45FE80(pThis_1D, (int)v6, 2, 0, (int)v6, 0, 0);  // sub_45FE80 —— 对象注册
      v8 = *(uint32_t *)v6;
      pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);  // 虚调用 vt+128（this）目标坐标y上界
      pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, pThis_80);  // 虚调用 vt+124（this）目标坐标y下界
      pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, pThis_7C);  // 虚调用 vt+120（this）转发(对象+缓冲)
      (*(void (/*thiscall*/ **)(char *, int))(v8 + 112))(v6, pThis_78);  // 虚函数调用 槽+112：槽位（699000 时钟 + 4B44E0）
      v12 = *(uint32_t *)v6;
      pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this);  // 虚调用 vt+152（this）取值(参数)
      (*(void (/*thiscall*/ **)(char *, int))(v12 + 148))(v6, pThis_98);  // 虚函数调用 槽+148：槽（12 行）
    }
  }
  return CNRDPassiveObject__vmt14C((int)this);  // 返回 调 CNRDPassiveObject__vmt14C
}



// ------------------------------------------------------------
// 0x62DED0 sub_62DED0 —— 窗口接口件批量释放
//    对 +40、+44、+48、+52、+56 五个接口指针逐个经其虚槽 0（参数 1）释放并置空。
// ------------------------------------------------------------
int /*thiscall*/ sub_62DED0(uint32_t *this)  // sub_62DED0 —— 窗口接口件批量释放
{
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx

  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40〔bStateSub40(推断)〕
  if ( fld_e10 != nullptr )  // 若 fld_e10 有效（非空）
    result = (**fld_e10)(fld_e10, 1);  // 调 fld_e10 的虚函数（vt+0）
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);  // this+44〔nExpireMs(推断)〕
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  if ( fld_e11 != nullptr )  // 若 fld_e11 有效（非空）
    result = (**fld_e11)(fld_e11, 1);  // 调 fld_e11 的虚函数（vt+0）
  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);  // this+12 物品类型号
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  if ( fld_e12 != nullptr )  // 若 fld_e12 有效（非空）
    result = (**fld_e12)(fld_e12, 1);  // 调 fld_e12 的虚函数（vt+0）
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);  // this+52〔bAuraState(推断)〕
  *(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  if ( fld_e13 != nullptr )  // 若 fld_e13 有效（非空）
    result = (**fld_e13)(fld_e13, 1);  // 调 fld_e13 的虚函数（vt+0）
  fld_e14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);  // this+56〔pCmdVecCap56(推断)〕
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  if ( fld_e14 != nullptr )  // 若 fld_e14 有效（非空）
    result = (**fld_e14)(fld_e14, 1);  // 调 fld_e14 的虚函数（vt+0）
  *(this + 14) = 0;  // 写字段 this+14 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x62DF30 sub_62DF30 —— 窗口条目数据拷贝
//    从 pArg2+4 起整块拷 0x98 字节到 this+4（列表行条目数据复制，列表窗口 vmt8 命中行时调用）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62DF30(int this, int pArg2)  // sub_62DF30 —— 窗口条目数据拷贝
{
  qmemcpy((void *)(this + 4), (const void *)(pArg2 + 4), 0x98u);  // this+4 宿主对象
  return this;
}



// ------------------------------------------------------------
// 0x62DF70 sub_62DF70 —— 列表行命中（6 行 × 242 宽）
//    以全局光标 pt 对 6 行（宽 242、行高 20、行距 24；首行由 +8 件 +24→+108 的 y 与 +20→+8 的 x 定）逐行命中，返回行号；全不中返 -1。
// ------------------------------------------------------------
int /*thiscall*/ sub_62DF70(uint32_t *this)  // sub_62DF70 —— 列表行命中（6 行 × 242 宽）
{
  int fld_e2; // eax
  LONG v2; // ecx
  LONG v3; // edx
  int result; // eax
  LONG i; // esi

  fld_e2 = *(this + 2);  // 读字段 fld_e2 = this+2
  v2 = *(uint32_t *)(fld_e2 + 24) + 108;
  v3 = *(uint32_t *)(fld_e2 + 20) + 8;
  result = 0;
  for ( i = v2 + 20; pt.x < v3 || pt.x >= v3 + 242 || pt.y < v2 || pt.y >= i; i += 24 )
  {
    ++result;  // 计数自增 result
    v2 += 24;
    if ( result >= 6 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62DFD0 sub_62DFD0 —— 按钮按下标志写入
//    把字节 pszArg2 写入 +44 件偏移 17（按钮按下标志）。
// ------------------------------------------------------------
int /*thiscall*/ sub_62DFD0(uint32_t *this, char pszArg2)  // sub_62DFD0 —— 按钮按下标志写入
{
  int result; // eax

  result = *(this + 11);  // 读字段 result = this+11
  *(uint8_t *)(result + 17) = pszArg2;  // 写字段 result+17（bEnable） ← pszArg2
  return result;
}



// ------------------------------------------------------------
// 0x62DFE0 sub_62DFE0 —— 红黑树节点克隆
//    pDwArg2 的 +173=0（非哨兵）时以 sub_49ECD0 按键(+3)与色(+172) 分配节点，再对左右链接(*pDwArg2 与 pDwArg2[2]) 递归克隆整树。
// ------------------------------------------------------------
void */*thiscall*/ sub_62DFE0(void **this, int *pDwArg2, int nArg3)  // sub_62DFE0 —— 红黑树节点克隆
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);  // 读字段 Block = this+1
  v3 = *((uint8_t *)pDwArg2 + 173);  // 读字段 v3 = pDwArg2[173]
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    fld_e1 = (uint32_t *)sub_49ECD0(*(this + 1), nArg3, *(this + 1), pDwArg2 + 3, *((uint8_t *)pDwArg2 + 172));  // sub_49ECD0 —— 红黑树节点分配（0xB0 字节：指针三件 + 键 + 载荷 0x98 拷贝）
    if ( *((uint8_t *)Block + 173) != 0 )
      Block = fld_e1;
    v6 = *pDwArg2;
    v10 = 0;
    *fld_e1 = sub_62DFE0(v6, fld_e1);  // sub_62DFE0 —— 红黑树节点克隆
    fld_e1[2] = sub_62DFE0(pDwArg2[2], fld_e1);  // sub_62DFE0 —— 红黑树节点克隆
  }
  return Block;
}



// ------------------------------------------------------------
// 0x62E0A0 sub_62E0A0 —— 列表窗口控件构建（4 按钮 + 数字集）
//    以全局 UI 件(dword_99FCC8+20) 的 +116/+196 字段经 sub_43C410 建 4 个 CNButton（贴图组 23/24/25、49/50/51、76/77/78、79/80/81）存 +40/+44/+48/+52，各 sub_69A5F0 设位、sub_69A840 登记；再 sub_423B30 建 CNNumberSet 存 +56 并置 +24=1。
//    随后整批初始化颜色与布局字段（黑 -16777216、字号 6/12/1600 等），+200 时钟设 500ms，末虚 24(this,20,23) 与虚 28(this,2)。
// ------------------------------------------------------------
int /*thiscall*/ sub_62E0A0(uint32_t *this)  // sub_62E0A0 —— 列表窗口控件构建（4 按钮 + 数字集）
{
  uint32_t *pMem; // eax
  uint32_t *fld_e9; // eax
  uint32_t *pMem2; // eax
  uint32_t *v5; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e92; // eax
  uint32_t *pMem4; // eax
  uint32_t *fld_e93; // eax
  uint8_t *pMem5; // eax
  uint8_t *fld_e94; // eax
  int dword_99FCCC2; // ecx

  *(this + 9) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 116);  // dword_99FCC8 —— nengine::CNSlider 构造
  pMem = operator new(0x84u);  // 堆分配
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    fld_e9 = sub_43C410(pMem, *(this + 9), 23, 24, 25, 23, 0, 0);  // sub_43C410 —— 结果 = nengine::CNButton 构造
  else
    fld_e9 = nullptr;
  *(this + 10) = fld_e9;  // 写字段 this+10 ← fld_e9
  sub_69A5F0(fld_e9, 230, 11);  // 调 设位、sub_69A840 登记
  sub_69A840(*(this + 10));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem2 = operator new(0x84u);  // 堆分配
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v5 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196), 49, 50, 51, 49, 0, 0);  // sub_43C410 —— 结果 = nengine::CNButton 构造
  else
    v5 = nullptr;
  *(this + 11) = v5;  // 写字段 this+11 ← v5
  sub_69A5F0(v5, 86, 275);  // 调 设位、sub_69A840 登记
  sub_69A840(*(this + 11));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem3 = operator new(0x84u);  // 堆分配
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    fld_e92 = sub_43C410(pMem3, *(this + 9), 76, 77, 78, 76, 0, 0);  // sub_43C410 —— 结果 = nengine::CNButton 构造
  else
    fld_e92 = nullptr;
  *(this + 12) = fld_e92;  // 写字段 this+12（nSkillRec12） ← fld_e92
  sub_69A5F0(fld_e92, 100, 257);  // 调 设位、sub_69A840 登记
  sub_69A840(*(this + 12));  // this+12 物品类型号
  pMem4 = operator new(0x84u);  // 堆分配
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    fld_e93 = sub_43C410(pMem4, *(this + 9), 79, 80, 81, 79, 0, 0);  // sub_43C410 —— 结果 = nengine::CNButton 构造
  else
    fld_e93 = nullptr;
  *(this + 13) = fld_e93;  // 写字段 this+13 ← fld_e93
  sub_69A5F0(fld_e93, 150, 257);  // 调 设位、sub_69A840 登记
  sub_69A840(*(this + 13));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem5 = operator new(0x2Cu);  // 堆分配
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
    fld_e94 = sub_423B30(pMem5, dword_79C0B0, *(this + 9), 51, 3);  // sub_423B30 —— 结果 = CNNumberSet 构造
  else
    fld_e94 = nullptr;
  *(this + 14) = fld_e94;  // 写字段 this+14 ← fld_e94
  fld_e94[24] = 1;
  *((uint8_t *)this + 60) = 0;  // 写字段 this+60（nFadeValue60）
  *((uint8_t *)this + 61) = 0;  // 写字段 this+61（bReadyFlagA）
  *((uint8_t *)this + 62) = 0;  // 写字段 this+62（bReadyFlagB）
  *((uint8_t *)this + 63) = 0;  // 写字段 this[63]（宽1字节）
  *(this + 18) = 0;  // 写字段 this+18（bDragChild） ← 0
  *(this + 21) = 0;  // 写字段 this+21（bArmorState） ← 0
  *(this + 23) = 0;  // 写字段 this+23 ← 0
  *(this + 24) = 0;  // 写字段 this+24（nPageMax） ← 0
  *(this + 25) = 0;  // 写字段 this+25 ← 0
  *(this + 26) = 0;  // 写字段 this+26 ← 0
  *(this + 27) = 0;  // 写字段 this+27 ← 0
  *(this + 20) = 12;  // 写字段 this+20（nPage） ← 12
  *(this + 22) = 1600;  // 写字段 this+22 ← 1600
  *(this + 19) = 6;  // 写字段 this+19 ← 6
  *(this + 27) = dword_99FCCC;  // 写字段 this+27 ← dword_99FCCC
  *(this + 22) = 100;  // 写字段 this+22 ← 100
  *(this + 18) = 1;  // 写字段 this+18（bDragChild） ← 1
  *(this + 23) = 1;  // 写字段 this+23 ← 1
  *(this + 16) = -16777216;  // 写字段 this+16（nChannelTypeSel） ← -16777216
  *(this + 35) = 1600;  // 写字段 this+35 ← 1600
  *((uint8_t *)this + 112) = 0;  // 写字段 this+112（pHostComp）
  *((uint8_t *)this + 113) = 0;  // 写字段 this[113]（宽1字节）
  *((uint8_t *)this + 114) = 0;  // 写字段 this[114]（宽1字节）
  *((uint8_t *)this + 115) = 0;  // 写字段 this[115]（宽1字节）
  *(this + 31) = 0;  // 写字段 this+31 ← 0
  *(this + 32) = 6;  // 写字段 this+32（nHeight） ← 6
  *(this + 33) = 12;  // 写字段 this+33（bJobVecDirty） ← 12
  *(this + 34) = 0;  // 写字段 this+34 ← 0
  *(this + 36) = 0;  // 写字段 this+36（nStateWord36） ← 0
  *(this + 37) = 0;  // 写字段 this+37（bFadeFlag37） ← 0
  *(this + 38) = 0;  // 写字段 this+38（bFadeFlag38） ← 0
  *(this + 39) = 0;  // 写字段 this+39 ← 0
  *(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  dword_99FCCC2 = dword_99FCCC;  // dword_99FCCC2 —— [esp+38h] [ebp-38h]
  *(this + 29) = -16777216;  // 写字段 this+29 ← -16777216
  *(this + 40) = dword_99FCCC2;  // dword_99FCCC2 —— [esp+38h] [ebp-38h]
  *(this + 35) = 144;  // 写字段 this+35 ← 144
  *(this + 31) = 1;  // 写字段 this+31 ← 1
  *(this + 36) = 1;  // 写字段 this+36（nStateWord36） ← 1
  *((uint8_t *)this + 213) = 0;  // 写字段 this[213]（宽1字节）
  *((uint8_t *)this + 214) = 0;  // 写字段 this[214]（宽1字节）
  sub_698F90((int)(this + 50), 500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 24))(this, 20, 23);  // 虚调用 vt+24（this）（析构，参 1）与 8（Release）释放后 GlobalFree 并 SetWindowLongA 摘除 —— 与 ·0x6528C0 挂载配对。
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 28))(this, 2);  // 虚调用 vt+28（this 虚表槽）
}



// ------------------------------------------------------------
// 0x62E370 sub_62E370 —— 列表树整树复制
//    以 sub_62DFE0 从 pArg2 的 +4 节点克隆挂到 this+4 处节点，拷 +8 计数，并按 +173 哨兵位重算头结点 +0/+8 的最左与最右指针。
// ------------------------------------------------------------
int */*thiscall*/ sub_62E370(int this, int pArg2)  // sub_62E370 —— 列表树整树复制
{
  int fld_4; // edi
  int **fld_42; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_43; // esi
  int **v8; // ecx

  fld_4 = *(uint32_t *)(this + 4);  // 读字段 fld_4 = this+4（pHostObj）
  *(uint32_t *)(fld_4 + 4) = sub_62DFE0((void **)this, *(int **)(*(uint32_t *)(pArg2 + 4) + 4), fld_4);  // sub_62DFE0 —— 红黑树节点克隆
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);  // 写字段 this+8（nSkillRec8） ← *(uint32_t *)(pArg2 + 8)
  fld_42 = *(int ***)(this + 4);  // this+4 宿主对象
  result = fld_42[1];
  if ( *((uint8_t *)result + 173) != 0 )
  {
    *fld_42 = (int *)fld_42;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);  // this+4 宿主对象
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
    *fld_42 = result;
    fld_43 = *(uint32_t *)(this + 4);  // 读字段 fld_43 = this+4（pHostObj）
    v8 = *(int ***)(fld_43 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 173) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(fld_43 + 8) = v8;  // 写字段 fld_43+8（nSkillRec8） ← v8
  }
  return result;
}



// ------------------------------------------------------------
// 0x62E400 sub_62E400 —— 列表窗口树容器清空
//    清 +36..+56 与 +180/+184；以 sub_49F090 经 +192 哨兵递归释放 +188 树后把哨兵三指针自指，末置 +228=-1。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_62E400(uint32_t *this)  // sub_62E400 —— 列表窗口树容器清空
{
  uint32_t *pThis_2F; // edi
  uint32_t *result; // eax

  *(this + 9) = 0;  // 写字段 this+9 ← 0
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  *(this + 12) = 0;  // 写字段 this+12（nSkillRec12） ← 0
  *(this + 13) = 0;  // 写字段 this+13 ← 0
  *(this + 14) = 0;  // 写字段 this+14 ← 0
  *(this + 45) = 0;  // 写字段 this+45 ← 0
  *(this + 46) = 0;  // 写字段 this+46 ← 0
  pThis_2F = this + 47;
  sub_49F090(*(void **)(*(this + 48) + 4));  // sub_49F090 —— 红黑树整树递归释放（先子树后本体的后序）
  *(uint32_t *)(pThis_2F[1] + 4) = pThis_2F[1];
  result = (uint32_t *)pThis_2F[1];
  pThis_2F[2] = 0;
  *result = result;
  *(uint32_t *)(pThis_2F[1] + 8) = pThis_2F[1];
  *(this + 57) = -1;  // 写字段 this+57 ← -1
  return result;
}



// ------------------------------------------------------------
// 0x62E460 sub_62E460 —— 列表刷新（重建行缓与分页）
//    uArg2=0 时按 +224+500ms 节流并复位字节 +213/+214；以 sub_49EA30 取场景槽，槽变则 sub_49F750 删旧树、sub_62E370 克隆。
//    遍历 +192 树，状态位(sub_48FD50(node+16))=1 者的 node+12 值经 sub_430C80 追加进 +168 队列；按 6 行/页算页数写 +184、页面 +180 越界回退，并在 +168 队列不含 dword_795D44 时 sub_44E850(+16 件,63)。
// ------------------------------------------------------------
int /*thiscall*/ sub_62E460(int this, uint32_t *uArg2)  // sub_62E460 —— 列表刷新（重建行缓与分页）
{
  int fld_E0; // ebx
  int result; // eax
  int pThis_A4; // esi
  int v6; // ebx
  int pThis_BC; // edi
  int pThis2; // ebx
  uint32_t *v9; // ecx
  uint32_t *uArg22; // eax
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
  int pThis; // [esp+Ch] [ebp-4h] BYREF

  pThis = this;
  if ( (uint8_t)uArg2 == 0 )
  {
    fld_E0 = *(uint32_t *)(this + 224);  // 读字段 fld_E0 = this+224（nSnapDst224）
    result = sub_699000(this + 200);  // 【clock_now(clk)】
    if ( result < fld_E0 )
      return result;
    *(uint8_t *)(this + 213) = 0;  // 写字段 this+213 ← 0
    *(uint8_t *)(this + 214) = 0;  // 写字段 this+214 ← 0
    sub_698F90(this + 200, 500, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  pThis_A4 = this + 164;  // this+164 第 5 组·+88 增量子倍率
  if ( *(uint32_t *)(this + 168) != 0 )  // this+168 附属对象向量 begin
    j__free(*(void **)(this + 168));  // 释放堆块
  *(uint32_t *)(this + 168) = 0;  // 写字段 this+168（pAppendVec） ← 0
  *(uint32_t *)(this + 172) = 0;  // 写字段 this+172（pAppendVecEnd） ← 0
  *(uint32_t *)(this + 176) = 0;  // 写字段 this+176（pAppendVecCap） ← 0
  v6 = sub_49EA30(*(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76));  // sub_49EA30 —— 红黑树槽基址计算（*(this+4) + 12 × 序号）
  pThis_BC = this + 188;  // this+188 状态槽索引
  if ( pThis_BC != v6 )
  {
    sub_49F750(&uArg2, **(uint32_t **)(pThis_BC + 4), *(uint32_t *)(pThis_BC + 4));  // sub_49F750 —— 红黑树区间删除（first..last 逐节点 ·sub_49F3F0）
    sub_62E370(v6);  // sub_62E370 —— 列表树整树复制
  }
  pThis2 = pThis;
  v9 = *(uint32_t **)(pThis + 192);  // this+192 对话 id
  uArg22 = (uint32_t *)*v9;
  uArg2 = (uint32_t *)*v9;
  if ( uArg2 != v9 )
  {
    do
    {
      v11 = uArg22[3];
      pThis = v11;
      if ( (uint8_t)sub_48FD50(uArg22 + 4) == 1 )  // sub_48FD50 —— 状态位查询（+72 不等于 -1）
      {
        v12 = *(uint32_t *)(pThis_A4 + 4);  // 读字段 v12 = pThis_A4+4（pHostObj）
        if ( v12 != 0 )
          v13 = (*(uint32_t *)(pThis_A4 + 8) - v12) >> 2;  // this+8 物品 id
        else
          v13 = 0;
        if ( v12 != 0 && v13 < (*(uint32_t *)(pThis_A4 + 12) - v12) >> 2 )  // this+12 物品类型号
        {
          v14 = *(int **)(pThis_A4 + 8);  // this+8 物品 id
          *v14 = v11;
          *(uint32_t *)(pThis_A4 + 8) = v14 + 1;  // 写字段 pThis_A4+8（nSkillRec8） ← v14 + 1
        }
        else
        {
          sub_430C80(*(void **)(pThis_A4 + 8), 1, (int)&pThis);  // sub_430C80 —— uint32 vector 区间插入（同值填充）
        }
      }
      sub_49EBA0(&uArg2);  // sub_49EBA0 —— 红黑树迭代器自减（--，中序上一节点）
      uArg22 = uArg2;
    }
    while ( uArg2 != *(uint32_t **)(pThis2 + 192) );  // this+192 对话 id
  }
  if ( dword_795D44 != -1 )
  {
    v15 = *(uint32_t **)(pThis2 + 172);  // this+172 附属对象向量 end
    v16 = *(uint32_t **)(pThis2 + 168);  // this+168 附属对象向量 begin
    if ( v16 == v15 )
      goto LABEL_23;
    do
    {
      if ( *v16 == dword_795D44 )
        break;
      ++v16;  // 计数自增 v16
    }
    while ( v16 != v15 );  // 循环直到 v16 != v15
    if ( v16 == v15 )
LABEL_23:
      sub_44E850(*(uint32_t **)(pThis2 + 16), 63);  // sub_44E850 —— 按池号批量回收活动对象 pArg2=71 时对 0..70 全池递归；否则遍历该池活动表逐项
  }
  v17 = *(uint32_t *)(pThis_A4 + 4);  // 读字段 v17 = pThis_A4+4（pHostObj）
  if ( v17 != 0 )
    v18 = (*(uint32_t *)(pThis_A4 + 8) - v17) >> 2;  // this+8 物品 id
  else
    v18 = 0;
  if ( (v18 - 1) / 6 <= 0 )
  {
    result = 0;
  }
  else
  {
    v19 = *(uint32_t *)(pThis_A4 + 4);  // 读字段 v19 = pThis_A4+4（pHostObj）
    if ( v19 != 0 )
      result = (((*(uint32_t *)(pThis_A4 + 8) - v19) >> 2) - 1) / 6;  // this+8 物品 id
    else
      result = 0;
  }
  v20 = *(uint32_t *)(pThis2 + 180) <= result;  // this+180 半径/计数
  *(uint32_t *)(pThis2 + 184) = result;  // 写字段 pThis2+184（bSingleTarget） ← result
  if ( !v20 )
    *(uint32_t *)(pThis2 + 180) = result;  // 写字段 pThis2+180（nRadius） ← result
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
uint8_t */*thiscall*/ CNRDWarRoomListWindow__vmt8(int this)  // 实现：(块尾 UI)CLICK_BUTTON2 —— 战争房间列表窗口按钮音（非可破坏物）
{
  int fld_8; // eax  | +0x0008 → ★ 列表控件（CNRDWarRoomListWindow；va=0062E640）
  int v3; // eax
  int fld_A8; // edx  | +0x00A8 → ★ 行数组 begin（CNRDWarRoomListWindow；va=0062E640）
  unsigned int fld_AC; // ecx  | +0x00AC → ★ 行数（0x62E640: (*(this+172) - fld_A8) >> 2）（CNRDWarRoomListWindow；va=0062E640）
  unsigned int fld_B4; // eax  | +0x00B4 → ★ 当前行（0x62E640: 6 * *(this+180) 换算控件槽，页容量 6 行；--/+1）（CNRDWarRoomListWindow；va=0062E640）
  int fld_A82; // edi  | +0x00A8 → ★ 行数组 begin（CNRDWarRoomListWindow；va=0062E640）
  int v8; // ebx
  int v9; // eax
  int fld_30; // eax  | +0x0030 → 行控件 A（0x62E640: fld_30 = *(this+48)，每行 6 个控件槽）【推断】（CNRDWarRoomListWindow；va=0062E640）
  int fld_B42; // eax  | +0x00B4 → ★ 当前行（0x62E640: 6 * *(this+180) 换算控件槽，页容量 6 行；--/+1）（CNRDWarRoomListWindow；va=0062E640）
  int fld_34; // eax  | +0x0034 → 行控件 B（0x62E640: fld_34 = *(this+52)）【推断】（CNRDWarRoomListWindow；va=0062E640）
  int fld_B43; // eax  | +0x00B4 → ★ 当前行（0x62E640: 6 * *(this+180) 换算控件槽，页容量 6 行；--/+1）（CNRDWarRoomListWindow；va=0062E640）
  int fld_28; // eax  | +0x0028 → 滚动条控件（0x62E640: fld_28 = *(this+40)）【推断】（CNRDWarRoomListWindow；va=0062E640）
  uint8_t *result; // eax
  int v16; // [esp+4h] [ebp-Ch] BYREF
  int fld_A822; // [esp+8h] [ebp-8h] BYREF
  char v18[4]; // [esp+Ch] [ebp-4h] BYREF

  sub_69A650(*(uint32_t *)(this + 8));  // this+8 物品 id
  fld_8 = *(uint32_t *)(this + 8);  // 读字段 fld_8 = this+8（nSkillRec8）
  if ( *(uint8_t *)(fld_8 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_8 + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    v3 = sub_62DF70((uint32_t *)this);  // sub_62DF70 —— 列表行命中（6 行 × 242 宽）
    if ( v3 != -1 )
    {
      fld_A8 = *(uint32_t *)(this + 168);  // 读字段 fld_A8 = this+168（pAppendVec）
      fld_AC = fld_A8 != 0 ? (*(uint32_t *)(this + 172) - fld_A8) >> 2 : 0;  // this+172 附属对象向量 end
      fld_B4 = v3 + 6 * *(uint32_t *)(this + 180);  // this+180 半径/计数
      if ( fld_B4 < fld_AC )
      {
        fld_A82 = *(uint32_t *)(*(uint32_t *)(this + 168) + 4 * fld_B4);  // this+168 附属对象向量 begin
        fld_A822 = fld_A82;
        sub_49ED70(&v16, &fld_A822);  // sub_49ED70 —— 红黑树槽查找并回填迭代器（越界则取 header）
        v8 = v16;
        if ( v16 != *(uint32_t *)(this + 192) )  // this+192 对话 id
        {
          v9 = sub_49EDC0(fld_A82, -1);  // sub_49EDC0 —— 红黑树多槽查表（槽内 lower_bound，命中返回条目 +16）
          if ( v9 != 0 )
          {
            sub_62DF30(v8 + 16, v9);  // sub_62DF30 —— 窗口条目数据拷贝
            sub_44E8D0(*(char **)(this + 16), (void *)0x3F, 0, fld_A82);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
            sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
          }
        }
      }
    }
  }
  fld_30 = *(uint32_t *)(this + 48);  // 读字段 fld_30 = this+48（pCmdVecBegin48）
  if ( *(uint8_t *)(fld_30 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_30 + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    fld_B42 = *(uint32_t *)(this + 180);  // 读字段 fld_B42 = this+180（nRadius）
    if ( fld_B42 > 0 )
    {
      *(uint32_t *)(this + 180) = fld_B42 - 1;  // 写字段 this+180（nRadius） ← fld_B42 - 1
      sub_62E460(this, (uint32_t *)1);  // sub_62E460 —— 列表刷新（重建行缓与分页）
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    }
  }
  fld_34 = *(uint32_t *)(this + 52);  // 读字段 fld_34 = this+52（bAuraState）
  if ( *(uint8_t *)(fld_34 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_34 + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    fld_B43 = *(uint32_t *)(this + 180);  // 读字段 fld_B43 = this+180（nRadius）
    if ( fld_B43 < *(uint32_t *)(this + 184) )  // this+184 单目标标志
    {
      *(uint32_t *)(this + 180) = fld_B43 + 1;  // 写字段 this+180（nRadius） ← fld_B43 + 1
      sub_62E460(this, (uint32_t *)1);  // sub_62E460 —— 列表刷新（重建行缓与分页）
      sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    }
  }
  fld_28 = *(uint32_t *)(this + 40);  // 读字段 fld_28 = this+40（bStateSub40）
  if ( *(uint8_t *)(fld_28 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_28 + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 32))(this);  // 虚调用 vt+32（this 虚表槽）
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  }
  result = *(uint8_t **)(this + 44);  // this+44 剩余时间 ms
  if ( result[17] != 0 && dword_79BE34 == *((uint32_t *)result + 3) )  // 当前动画对象指针(帧同步比对基准)
  {
    sub_423200(dword_8F7B08, 101);  // 【发送网络包API】
    v18[0] = 1;
    sub_423290(dword_8F7B08, (int)v18, 1);  // sub_423290 —— 写 4B 长度
    sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
    *(uint8_t *)(*(uint32_t *)(this + 44) + 17) = 0;  // this+44 剩余时间 ms
    return sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  }
  return result;
}



// ------------------------------------------------------------
// 0x62E830 CNRDWarRoomListWindow__vmtC —— 【块尾 UI】列表窗口初始化 vmtC
//    把自身记入 dword_9B9454、+228=nArg3，经 sub_62E460(this,1) 强制刷新行缓后 sub_69A5F0(+8 列表件,191,92) 设位，清页号 +180 与页数 +184。
// ------------------------------------------------------------
int /*thiscall*/ CNRDWarRoomListWindow__vmtC(int this, int nArg2, int nArg3)  // 实现：(块尾 UI)列表窗口初始化 vmtC
{
  dword_9B9454 = this;  // dword_9B9454 —— dword_9B9454 不等于 0
  *(uint32_t *)(this + 228) = nArg3;  // 写字段 this+228（nSnapDst228） ← nArg3
  sub_62E460(this, (uint32_t *)1);  // sub_62E460 —— 列表刷新（重建行缓与分页）
  sub_69A5F0(*(uint32_t **)(this + 8), 191, 92);  // 调 设位、sub_69A840 登记
  *(uint32_t *)(this + 180) = 0;  // 写字段 this+180（nRadius） ← 0
  *(uint32_t *)(this + 184) = 0;  // 写字段 this+184（bSingleTarget） ← 0
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x62E870 CNRDWarRoomListWindow__vmt0 —— 【块尾 UI】列表窗口绘制 vmt0
//    基类 IRDPopupWindow__vmt0 后取画布 dword_79C0B0：sub_418DD0(21) 每 24px 画 6 行底，sub_49EDC0 查表项经 sub_69A110 与 sub_48FE30 出串表文案，图标 74/75（sub_4902A0 分支）与选中框 46（sub_491530(2,0)/sub_491630(2) 成对包裹）。
//    页脚以 %d/%d 出 +180/+184 页号、%2d/%2d 出 sub_48FBB0 项 8 的人数比；悬停行(sub_62DF70) 另以 sub_422E70(1904) 与全局 dword_77F888 表格式化后 sub_4649B0 出提示条。
// ------------------------------------------------------------
int /*userpurge*/ sub_62E870@<eax>(uint32_t *pArg1@<ecx>, uint32_t *uArg2@<ebx>, int pArg3)  // 实现：(块尾 UI)列表窗口绘制 vmt0
{
  int result; // eax
  int v5; // ebx
  int v6; // edi
  int pObj2; // eax
  int v8; // ecx
  int pObj; // eax
  int v10; // ecx
  int v11; // edi
  unsigned int v12; // ebx
  int pObj3; // eax
  int v14; // ecx
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int pObj4; // eax
  int v19; // eax
  int pObj5; // eax
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
  int dword_796E502; // [esp+ECh] [ebp-4h]
  int v36; // [esp+F8h] [ebp+8h]

  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  result = sub_554930(pArg3);  // 【IRDPopupWindow__vmt0】
  if ( pArg3 == pArg1[2] )
  {
    sub_62E460(0);  // sub_62E460 —— 列表刷新（重建行缓与分页）
    v5 = *(uint32_t *)(pArg3 + 20);  // 读字段 v5 = pArg3+20（nPage）
    v6 = *(uint32_t *)(pArg3 + 24);  // 读字段 v6 = pArg3+24（nPageMax）
    v33 = v5;
    v27 = v6;
    pObj2 = sub_418DD0(1);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v5 + 6, v6 + 6, dword_79C0B0);  // 虚调用 vt+152（pObj2）取值(参数)
    v8 = pArg1[57];
    if ( v8 != -1 )
    {
      pObj = sub_418DD0(dword_73DE2C[v8]);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v5 + 8, v6 + 35, dword_79C0B0);  // 虚调用 vt+152（pObj）取值(参数)
    }
    v10 = pArg1[2];
    v11 = v6 + 108;  // 计算 v11 = v6 + 108
    v12 = 6 * pArg1[45];
    v32 = v11;
    v30 = v12;
    if ( *(uint8_t *)(v10 + 17) != 0
      && (dword_79BE3C == *(uint32_t *)(v10 + 12)  // 动画对象指针(帧同步比对基准 C)
       || dword_79BE34 == *(uint32_t *)(v10 + 12)  // 当前动画对象指针(帧同步比对基准)
       || dword_79BE38 == *(uint32_t *)(v10 + 12)) )  // 动画对象指针(帧同步比对基准 B)
    {
      v26 = sub_62DF70(pArg1);  // sub_62DF70 —— 列表行命中（6 行 × 242 宽）
    }
    else
    {
      v26 = -1;
    }
    v31 = 0;
    v36 = v11 + 1;  // 计算 v36 = v11 + 1
    do
    {
      pObj3 = sub_418DD0(21);  // sub_418DD0 —— 资源句柄 (101)
      if ( pObj3 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 虚调用 vt+128（pObj3）目标坐标y上界
          pObj3,
          v33 + 8,
          v11,
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          1065353216,  // 浮点常量 1.0f
          1065353216,  // 浮点常量 1.0f
          0,
          -1929379841,
          1333788672,
          1333788672);
      v14 = pArg1[42];
      if ( v14 != 0 && v12 < (pArg1[43] - v14) >> 2 )  // 向量元素数 = (end−begin)/4
      {
        v15 = sub_49EDC0(*(uint32_t *)(pArg1[42] + 4 * v12), -1);  // sub_49EDC0 —— 红黑树多槽查表（槽内 lower_bound，命中返回条目 +16）
        v16 = v15;
        if ( v15 != 0 )
        {
          sub_69A110(v33 + 13, v36 + 3, *(uint32_t *)(v15 + 4), -1);
          (*(void (/*thiscall*/ **)(int, uint32_t *, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 28, uArg2);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
          v28 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          v17 = sub_48FE30(v16);  // sub_48FE30 —— 组装显示串（串表名 + 表项串 #编号）
          (*(void (/*cdecl*/ **)(int, int, int, int, int))(v28 + 80))(dword_79C0B0, v33 + 53, v36 + 4, -4928551, v17);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          if ( (uint8_t)sub_4902A0(v16) != 0 )  // sub_4902A0 —— 动画播放态判定（帧态 2/3/4 为进行中，-1 视为起始）
            pObj4 = sub_418DD0(75);  // sub_418DD0 —— 资源句柄 (101)
          else
            pObj4 = sub_418DD0(74);  // sub_418DD0 —— 资源句柄 (101)
          if ( pObj4 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, v33 + 231, v36, dword_79C0B0);  // 虚调用 vt+152（pObj4）取值(参数)
          uArg2 = pArg1 + 15;
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 68))(dword_79C0B0);  // 虚调用 vt+68（dword_79C0B0 虚表槽）
          v29 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          v19 = sub_48FBB0(v16, 8);  // sub_48FBB0 —— 结果 = 槽表计数（+40..+68 中不等于 0xFFFF 的字段数）
          (*(void (/*cdecl*/ **)(int, int, int, int, const char *, int))(v29 + 80))(  // 虚函数调用 槽+80：槽（参数写入 3 转发）
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            v33 + 156,
            v36 + 4,
            -3750202,
            "%2d/%2d",
            v19);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
          if ( v31 == v26 || *(uint32_t *)(v16 + 4) == dword_795D44 )
          {
            sub_491530(2, 0);  // sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
            pObj5 = sub_418DD0(46);  // sub_418DD0 —— 资源句柄 (101)
            if ( pObj5 != 0 )
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, v33 + 8, v32, dword_79C0B0);  // 虚调用 vt+152（pObj5）取值(参数)
            sub_491630(2);  // sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
          }
          v12 = v30;
        }
      }
      ++v12;  // 计数自增 v12
      v11 = v32 + 24;  // 计算 v11 = v32 + 24
      v21 = ++v31 < 6;
      v30 = v12;
      v32 += 24;
      v36 += 24;
    }
    while ( v21 );
    (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 15);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
    (*(void (**)(int, int, int, int, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
      dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      v33 + 83,
      v27 + 258,
      -3750202,
      "%d/%d",
      pArg1[45] + 1,
      pArg1[46] + 1);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
    result = pArg1[2];
    if ( *(uint8_t *)(result + 17) != 0 && dword_79BE3C == *(uint32_t *)(result + 12) )  // 动画对象指针(帧同步比对基准 C)
    {
      result = sub_62DF70(pArg1);  // sub_62DF70 —— 列表行命中（6 行 × 242 宽）
      v22 = result;
      if ( result != -1 )
      {
        result = pArg1[42];
        if ( result != 0 && v22 < (pArg1[43] - result) >> 2 )  // 向量元素数 = (end−begin)/4
        {
          future_error_what = std::_Get_future_error_what(dword_77F888 + *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 76));  // dword_77F888 —— 字节提取赋值
          v23 = (const char *)sub_422E70(1904);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
          sprintf(Buffer, v23, future_error_what);  // 调 格式化到缓冲
          return sub_4649B0(v33 + 128, v27 + 24 * v22 + 103, -1, -16777216, 2, Buffer, 0, 0, 1600, 0);  // sub_4649B0 —— 带框文本上屏（静态一次性初始化）
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x62ED00 sub_62ED00 —— 合成窗口字段初始化
//    置 +36/+40/+44 为 0、+48=0xFFFF、+52=4、+56 与 +204..+216 清零。
// ------------------------------------------------------------
int /*thiscall*/ sub_62ED00(uint32_t *this)  // sub_62ED00 —— 合成窗口字段初始化
{
  *(this + 9) = 0;  // 写字段 this+9 ← 0
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  *(this + 11) = 0;  // 写字段 this+11 ← 0
  *(this + 12) = 0xFFFF;  // 写字段 this+12（nSkillRec12） ← 0xFFFF
  *(this + 13) = 4;  // 写字段 this+13 ← 4
  *(this + 14) = 0;  // 写字段 this+14 ← 0
  *(this + 51) = 0;  // 写字段 this+51 ← 0
  *(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  *(this + 53) = 0;  // 写字段 this+53 ← 0
  *(this + 54) = 0;  // 写字段 this+54 ← 0
  return 0;
}



// ------------------------------------------------------------
// 0x62ED40 sub_62ED40 —— 合成窗口接口件释放
//    对 +36、+40、+204、+208、+212、+216 六个接口指针逐个经其虚槽 0（参数 1）释放并置空。
// ------------------------------------------------------------
int /*thiscall*/ sub_62ED40(uint32_t *this)  // sub_62ED40 —— 合成窗口接口件释放
{
  int (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e51)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e52)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e53)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e54)(uint32_t, int); // ecx

  fld_e9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);  // this+36〔nStateWord36(推断)〕
  if ( fld_e9 != nullptr )  // 若 fld_e9 有效（非空）
    result = (**fld_e9)(fld_e9, 1);  // 调 fld_e9 的虚函数（vt+0）
  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40〔bStateSub40(推断)〕
  *(this + 9) = 0;  // 写字段 this+9 ← 0
  if ( fld_e10 != nullptr )  // 若 fld_e10 有效（非空）
    result = (**fld_e10)(fld_e10, 1);  // 调 fld_e10 的虚函数（vt+0）
  fld_e51 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 51);  // this+204〔pSubAnim204(推断)〕
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  if ( fld_e51 != nullptr )  // 若 fld_e51 有效（非空）
    result = (**fld_e51)(fld_e51, 1);  // 调 fld_e51 的虚函数（vt+0）
  fld_e52 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 52);  // this+52 光环状态字节
  *(this + 51) = 0;  // 写字段 this+51 ← 0
  if ( fld_e52 != nullptr )  // 若 fld_e52 有效（非空）
    result = (**fld_e52)(fld_e52, 1);  // 调 fld_e52 的虚函数（vt+0）
  fld_e53 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 53);  // this+212〔nField212(推断)〕
  *(this + 52) = 0;  // 写字段 this+52（bAuraState） ← 0
  if ( fld_e53 != nullptr )  // 若 fld_e53 有效（非空）
    result = (**fld_e53)(fld_e53, 1);  // 调 fld_e53 的虚函数（vt+0）
  fld_e54 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 54);  // this+216〔bField216(推断)〕
  *(this + 53) = 0;  // 写字段 this+53 ← 0
  if ( fld_e54 != nullptr )  // 若 fld_e54 有效（非空）
    result = (**fld_e54)(fld_e54, 1);  // 调 fld_e54 的虚函数（vt+0）
  *(this + 54) = 0;  // 写字段 this+54 ← 0
  return result;
}



// ------------------------------------------------------------
// 0x62EDD0 CNRDCompoundItemWindow__vmt8
//   【块尾 UI】CLICK_BUTTON2 + RECIPE_COMBINE —— 合成窗口
// ------------------------------------------------------------
int /*thiscall*/ CNRDCompoundItemWindow__vmt8(int *this)  // 实现：(块尾 UI)CLICK_BUTTON2 + RECIPE_COMBINE —— 合成窗口
{
  int fld_e9; // eax
  int result; // eax

  sub_69A650(*(this + 2));  // this+8〔nSkillRec8(推断)〕
  fld_e9 = *(this + 9);  // 读字段 fld_e9 = this+9
  if ( *(uint8_t *)(fld_e9 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e9 + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);  // 虚调用 vt+20（this）条件位掩码测试(273受击/17有血/65机械)
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    sub_432EA0("RECIPE_COMBINE", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
  }
  result = *(this + 10);  // 读字段 result = this+10
  if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 当前动画对象指针(帧同步比对基准)
  {
    sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    return (*(int (/*thiscall*/ **)(int *))(*this + 32))(this);  // 虚调用 vt+32（this 虚表槽）
  }
  return result;
}



// ------------------------------------------------------------
// 0x62EE50 CNRDCompoundItemWindow__vmt10 —— 【块尾 UI】合成窗口数量框刷新 vmt10
//    取 +16 件的 +116 子件，其 +40 状态为 5 时交 sub_540960（数量输入框刷新），否则原样返回。
// ------------------------------------------------------------
int /*thiscall*/ CNRDCompoundItemWindow__vmt10(int *this)  // 实现：(块尾 UI)合成窗口数量框刷新 vmt10
{
  int result; // eax
  int v2; // ecx

  result = *(this + 4);  // 读字段 result = this+4（pHostObj）
  v2 = *(uint32_t *)(result + 116);  // 读字段 v2 = result+116（pSessionCtx）
  if ( *(uint32_t *)(v2 + 40) == 5 )
    return sub_540960(v2);  // sub_540960 —— 数量输入框刷新（24 行）
  return result;
}



// ------------------------------------------------------------
// 0x62EE70 sub_62EE70 —— 可合成次数上限计算
//    先扫 +20/+24 的 8 字节元素表，类型(sub_4F2D40)=2 时上限取 1（否则 255）；再对 +4/+8 材料表逐项：sub_484E00 取基础量、对背包(dword_8F7C04 18 格) 编号匹配格逐格 +1，除以每件需求(v2[1]) 求份数，全表取最小；任一材料库存不足一份即返 0。
// ------------------------------------------------------------
int /*cdecl*/ sub_62EE70(uint32_t *pArg1)  // sub_62EE70 —— 结果 = 可合成次数上限计算
{
  uint32_t *v1; // esi
  uint32_t *v2; // ebx
  int v3; // edi
  int v4; // eax
  int pObj; // ecx
  int v6; // esi
  int pObj2; // eax
  int v9; // [esp+Ch] [ebp-Ch]
  int v10; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  v1 = (uint32_t *)pArg1[5];
  for ( i = 255; v1 != (uint32_t *)pArg1[6]; v1 += 2 )
  {
    if ( sub_4F2D40(*v1) == 2 )  // 调 条件判定
      i = 1;
  }
  v2 = (uint32_t *)pArg1[1];
  if ( v2 == (uint32_t *)pArg1[2] )
    return i;
  while ( 1 )  // 无限循环
  {
    v3 = *v2;
    v9 = v2[1];
    v4 = sub_484E00(*v2);  // sub_484E00 —— 按类型查找并取数值（虚表 +16/+4 匹配）
    pObj = dword_8F7C04;  // 读 dword_8F7C04（本地玩家对象）
    v10 = v4;
    if ( dword_8F7C04 != 0 )  // 写 dword_8F7C04（本地玩家对象）
    {
      v6 = 0;
      while ( 1 )  // 无限循环
      {
        pObj2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 792))(pObj, v6);  // 虚调用 vt+792（pObj）角色槽物品取
        if ( pObj2 != 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 16))(pObj2) + 4) == v3 )  // 虚调用 vt+16（pObj2 虚表槽）
          ++v10;  // 计数自增 v10
        if ( ++v6 >= 18 )
          break;
        pObj = dword_8F7C04;  // 读 dword_8F7C04（本地玩家对象）
      }
    }
    if ( v10 / v9 == 0 )
      break;
    if ( v10 / v9 < i )
      i = v10 / v9;
    v2 += 2;
    if ( v2 == (uint32_t *)pArg1[2] )
      return i;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x62EF50 CNRDCompoundItemWindow__vmt0 —— 【块尾 UI】合成窗口绘制 vmt0
//    基类 IRDPopupWindow__vmt0 后以画布 dword_79C0B0 绘制：sub_418DD0 取 5/6/7/4 号框排材料区与结果区（+136 表最多 6 行、行高 39、双列 101px）。
//    +120 表（44 字节/件）以 %s\nLv.%d 出名称与等级，+136 表以 %s\n(%d/%d) 出数量；滚动取 sub_69C690(+216)，文案 sub_422E70(926/927)；末段 +36 件鼠标命中且 dword_8F7A24+12 ≠ 1 时以 sub_422E70(928) 经 sub_4649B0 出提示条。
// ------------------------------------------------------------
char /*userpurge*/ sub_62EF50@<al>(int pArg1@<ecx>, int nArg2@<ebx>, int pArg3)  // 实现：(块尾 UI)合成窗口绘制 vmt0
{
  char result; // al
  int v5; // ebx
  int v6; // edi
  int pObj2; // eax
  int pObj4; // ecx
  int pObj; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // edi
  int v15; // edi
  int pObj8; // eax
  bool v17; // zf
  int pObj6; // eax
  int pObj9; // eax
  int v20; // edi
  int v21; // eax
  int v22; // eax
  unsigned int v23; // edi
  int v24; // ebx
  int pObj7; // eax
  int v26; // eax
  unsigned int v27; // ecx
  uint32_t *v28; // eax
  int v29; // edi
  int pObj5; // eax
  int v31; // edi
  int v32; // eax
  int v33; // eax
  int v34; // edi
  int v35; // eax
  int v36; // edi
  int pObj3; // eax
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

  result = sub_554930(pArg3);  // 【IRDPopupWindow__vmt0】
  if ( pArg3 == *(uint32_t *)(pArg1 + 8) )  // pArg1+8〔nSkillRec8(推断)〕
  {
    v5 = *(uint32_t *)(pArg3 + 20);  // 读字段 v5 = pArg3+20（nPage）
    v6 = *(uint32_t *)(pArg3 + 24);  // 读字段 v6 = pArg3+24（nPageMax）
    v54 = v5;
    v55 = v6;
    pObj2 = sub_418DD0(*(uint32_t **)(pArg1 + 44), *(uint32_t *)(pArg1 + 52) + 8);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v5 + 7, v6 + 6, dword_79C0B0);  // 虚调用 vt+152（pObj2）取值(参数)
    pObj4 = *(uint32_t *)(pArg1 + 60);  // 读字段 pObj4 = pArg1+60（nFadeValue60）
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(  // 虚调用 vt+152（pObj4）取值(参数)
        pObj4,
        v5 + *(uint32_t *)(pArg1 + 56),
        v6 + 18,
        dword_79C0B0);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    pObj = sub_418DD0(*(uint32_t **)(pArg1 + 44), 5u);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 虚调用 vt+128（pObj）目标坐标y上界
        pObj,
        v5 + 7,
        v6 + 67,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,  // 浮点常量 1.0f
        1065353216,  // 浮点常量 1.0f
        0,
        1694498815,
        1333788672,
        1333788672);
    v10 = *(uint32_t *)(pArg1 + 136);  // 读字段 v10 = pArg1+136（nCtx136）
    if ( v10 != 0 && (unsigned int)((*(uint32_t *)(pArg1 + 140) - v10) / 44) >= 6 )  // pArg1+140〔nAdd140(推断)〕
    {
      v12 = 6;
    }
    else
    {
      v11 = *(uint32_t *)(pArg1 + 136);  // 读字段 v11 = pArg1+136（nCtx136）
      if ( v11 != 0 )
        v12 = (*(uint32_t *)(pArg1 + 140) - v11) / 44;  // pArg1+140〔nAdd140(推断)〕
      else
        v12 = 0;
    }
    v13 = *(uint32_t *)(pArg1 + 120);  // 读字段 v13 = pArg1+120（pAnimObj）
    if ( v13 != 0 )
      v14 = (*(uint32_t *)(pArg1 + 124) - v13) / 44;  // pArg1+124〔pAuraAnim(推断)〕
    else
      v14 = 0;
    v15 = v12 + ((unsigned int)(v14 + 1) >> 1);
    if ( v15 > 0 )
    {
      v57 = v55 + 97;  // 计算 v57 = v55 + 97
      v52 = v15;
      do
      {
        pObj8 = sub_418DD0(*(uint32_t **)(pArg1 + 44), 6u);  // sub_418DD0 —— 资源句柄 (101)
        if ( pObj8 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj8 + 128))(  // 虚调用 vt+128（pObj8）目标坐标y上界
            pObj8,
            v5 + 7,
            v57,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,  // 浮点常量 1.0f
            1065353216,  // 浮点常量 1.0f
            0,
            1694498815,
            1333788672,
            1333788672);
        v17 = v52 == 1;
        v57 += 39;
        --v52;  // 计数自减 v52
      }
      while ( !v17 );
    }
    pObj6 = sub_418DD0(*(uint32_t **)(pArg1 + 44), 7u);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj6 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj6 + 128))(  // 虚调用 vt+128（pObj6）目标坐标y上界
        pObj6,
        v5 + 7,
        39 * v15 + v55 + 97,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,  // 浮点常量 1.0f
        1065353216,  // 浮点常量 1.0f
        0,
        1694498815,
        1333788672,
        1333788672);
    v58 = v55 + 71;  // 计算 v58 = v55 + 71
    pObj9 = sub_418DD0(*(uint32_t **)(pArg1 + 44), 4u);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj9 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj9 + 128))(  // 虚调用 vt+128（pObj9）目标坐标y上界
        pObj9,
        v5 + 10,
        v55 + 71,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,  // 浮点常量 1.0f
        1065353216,  // 浮点常量 1.0f
        0,
        603979775,
        1333788672,
        1333788672);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 148, nArg2);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
    v20 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    v21 = sub_422E70(926);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v20 + 80))(dword_79C0B0, v5 + 19, v55 + 74, -1, v21);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
    v22 = *(uint32_t *)(pArg1 + 120);  // 读字段 v22 = pArg1+120（pAnimObj）
    v23 = 0;
    if ( v22 != 0 )
      v56 = (*(uint32_t *)(pArg1 + 124) - v22) / 44;  // pArg1+124〔pAuraAnim(推断)〕
    else
      v56 = 0;
    if ( v56 > 0 )
    {
      v24 = 0;
      do
      {
        pObj7 = *(uint32_t *)(v24 + *(uint32_t *)(pArg1 + 120));  // pArg1+120〔pAnimObj〕
        if ( pObj7 != 0 )
          (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)pObj7 + 152))(  // 虚调用 vt+152（pObj7）取值(参数)
            pObj7,
            101 * (v23 % 2) + v54 + 18,
            39 * (v23 / 2) + v58 + 26,
            dword_79C0B0);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 148);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
        v26 = *(uint32_t *)(pArg1 + 120);  // 读字段 v26 = pArg1+120（pAnimObj）
        v27 = *(uint32_t *)(v26 + v24 + 28);
        v28 = (uint32_t *)(v24 + v26);
        if ( v27 < 0x10 )
          (*(void (**)(int, unsigned int, unsigned int, uint32_t, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            101 * (v23 % 2) + v54 + 54,
            39 * (v23 / 2) + v58 + 30,
            v28[10],
            "%s\nLv.%d",
            v28 + 2,
            v28[9]);
        else
          (*(void (**)(int, unsigned int, unsigned int, uint32_t, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            101 * (v23 % 2) + v54 + 54,
            39 * (v23 / 2) + v58 + 30,
            v28[10],
            "%s\nLv.%d",
            v28[2],
            v28[9]);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
        ++v23;  // 计数自增 v23
        v24 += 44;
      }
      while ( (int)v23 < v56 );  // 循环直到 v23 < v56
      v5 = v54;
    }
    v29 = v58 + 39 * ((v56 + 1) / 2) + 26;
    v59 = v29;
    pObj5 = sub_418DD0(*(uint32_t **)(pArg1 + 44), 4u);  // sub_418DD0 —— 资源句柄 (101)
    if ( pObj5 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj5 + 128))(  // 虚调用 vt+128（pObj5）目标坐标y上界
        pObj5,
        v5 + 10,
        v29,
        dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
        1065353216,  // 浮点常量 1.0f
        1065353216,  // 浮点常量 1.0f
        0,
        603979775,
        1333788672,
        1333788672);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 148);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
    v31 = *(uint32_t *)dword_79C0B0;  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    v32 = sub_422E70(927);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    (*(void (/*cdecl*/ **)(int, int, int, int, int))(v31 + 80))(dword_79C0B0, v5 + 19, v59 + 3, -1, v32);  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
    v33 = *(uint32_t *)(pArg1 + 136);  // 读字段 v33 = pArg1+136（nCtx136）
    v34 = 0;
    if ( v33 != 0 )
      v50 = (*(uint32_t *)(pArg1 + 140) - v33) / 44;  // pArg1+140〔nAdd140(推断)〕
    else
      v50 = 0;
    v53 = 0;
    v60 = v59 + 26;  // 计算 v60 = v59 + 26
    do
    {
      v35 = v34 + sub_69C690(*(uint32_t *)(pArg1 + 216));  // sub_69C690 —— 结果 = 取设备对象 +112 字段（类型或句柄）
      if ( v35 < v50 )
      {
        v36 = 44 * v35;  // 计算 v36 = 44 * v35
        pObj3 = *(uint32_t *)(44 * v35 + *(uint32_t *)(pArg1 + 136));  // pArg1+136〔nCtx136(推断)〕
        v38 = v5 + 18;  // 计算 v38 = v5 + 18
        if ( pObj3 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v38, v60, dword_79C0B0);  // 虚调用 vt+152（pObj3）取值(参数)
        if ( *(uint32_t *)(v36 + *(uint32_t *)(pArg1 + 136) + 32) < *(uint32_t *)(v36 + *(uint32_t *)(pArg1 + 136) + 36)  // pArg1+136〔nCtx136(推断)〕
          && dword_9B0C5C != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)dword_9B0C5C + 128))(  // 虚调用 vt+128（dword_9B0C5C）目标坐标y上界
            dword_9B0C5C,
            v38,
            v60,
            dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
            1065353216,  // 浮点常量 1.0f
            1065353216,  // 浮点常量 1.0f
            0,
            1308622847,
            1333788672,
            1333788672);
        }
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg1 + 148);  // 虚调用 vt+72（dword_79C0B0 虚表槽）
        v39 = *(uint32_t *)(pArg1 + 136);  // 读字段 v39 = pArg1+136（nCtx136）
        v40 = *(uint32_t *)(v39 + v36 + 28);
        v41 = (uint32_t *)(v36 + v39);
        if ( v40 < 0x10 )
          v51 = v41 + 2;  // 计算 v51 = v41 + 2
        else
          v51 = (uint32_t *)v41[2];
        (*(void (**)(int, int, int, uint32_t, const char *, ...))(*(uint32_t *)dword_79C0B0 + 80))(  // 虚调用 vt+80（dword_79C0B0）读 4 字节
          dword_79C0B0,  // dword_79C0B0 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
          v38 + 36,
          v60 + 4,
          v41[10],
          "%s\n(%d/%d)",
          v51,
          v41[8],
          v41[9]);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 虚调用 vt+76（dword_79C0B0 虚表槽）
        v5 = v54;
        v34 = v53;
      }
      v53 = ++v34;
      v60 += 39;
    }
    while ( v34 < 6 );  // 循环直到 v34 < 6
    v42 = *(uint32_t *)(pArg1 + 36);  // 读字段 v42 = pArg1+36（nStateWord36）
    result = *(uint8_t *)(v42 + 17);  // 读字段 result = v42+17（bEnable）
    if ( result != 0 )  // 若结果非 0（成功）
    {
      v43 = *(uint32_t *)(v42 + 12);  // 读字段 v43 = v42+12（nSkillRec12）
      if ( dword_79BE3C == v43 || dword_79BE34 == v43 || (result = dword_79BE38, dword_79BE38 == v43) )  // 判定 dword_79BE3C == v43 或 dword_79BE34 == v43 或 dword_79BE38 == v43
      {
        if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
        {
          v44 = *(uint32_t **)(pArg1 + 36);  // pArg1+36〔nStateWord36(推断)〕
          v45 = v44[6];
          v46 = v44[5];
          v47 = v44[7];
          v48 = (const char *)sub_422E70(928);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
          return sub_4649B0(v46 + (v47 >> 1), v45, -1, -16777216, 2, v48, 0, 0, 1600, 0);  // sub_4649B0 —— 带框文本上屏（静态一次性初始化）
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x62F530 sub_62F530 —— 合成请求发包（27 号包）
//    全局表(dword_8F852C+20/+24) 为空时才执行：sub_62EE70(this+64) 小于 nArg2 时以 sub_422E70(929) 文案交 sub_44E8D0(+16 件,27,文案,0) 提示；否则按 +200 取原下标或 sub_484E80 换算，未命中出 930 提示。
//    通过后经 sub_423200(dword_8F7B08,27) 起包、sub_423290 依次写下标(2B)、+200 标志、次数、0、1，sub_423380 提交并记 dword_795D48=+52。
// ------------------------------------------------------------
int /*thiscall*/ sub_62F530(int this, int nArg2)  // sub_62F530 —— 合成请求发包（27 号包）
{
  int v3; // ecx
  int result; // eax
  int pThis_40; // eax
  char nArg22; // bl
  char *v7; // eax
  int fld_30; // edi
  char *v9; // eax

  v3 = *((uint32_t *)dword_8F852C + 5);  // 读字段 v3 = dword_8F852C[5]
  if ( v3 == 0 || (result = (*((uint32_t *)dword_8F852C + 6) - v3) >> 2) <= 0 )  // 读 dword_8F852C（UI 管理器全局）
  {
    pThis_40 = sub_62EE70((uint32_t *)(this + 64));  // sub_62EE70 —— 结果 = 可合成次数上限计算
    nArg22 = nArg2;
    if ( pThis_40 < nArg2 )
    {
      v7 = sub_422E70(929);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
      return sub_44E8D0(*(char **)(this + 16), (void *)0x1B, (int)v7, 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
    }
    if ( *(uint8_t *)(this + 200) != 0 )  // this+200 主状态
    {
      fld_30 = *(uint32_t *)(this + 48);  // 读字段 fld_30 = this+48（pCmdVecBegin48）
    }
    else
    {
      fld_30 = sub_484E80(*(uint32_t *)(this + 48));  // sub_484E80 —— 按类型查找下标（同一匹配规则，未命中 -1）
      if ( fld_30 == -1 )
      {
        v9 = sub_422E70(930);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
        return sub_44E8D0(*(char **)(this + 16), (void *)0x1B, (int)v9, 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
      }
    }
    sub_423200(dword_8F7B08, 27);  // 【发送网络包API】
    nArg2 = fld_30;
    sub_423290(dword_8F7B08, (int)&nArg2, 2);  // sub_423290 —— 写 4B 长度
    HIBYTE(nArg2) = *(uint8_t *)(this + 200) != 0;  // this+200 主状态
    sub_423290(dword_8F7B08, (int)&nArg2 + 3, 1);  // sub_423290 —— 写 4B 长度
    HIBYTE(nArg2) = nArg22;  // 调 取 16 位值高 8 位
    sub_423290(dword_8F7B08, (int)&nArg2 + 3, 1);  // sub_423290 —— 写 4B 长度
    HIBYTE(nArg2) = 0;  // 调 取 16 位值高 8 位
    sub_423290(dword_8F7B08, (int)&nArg2 + 3, 1);  // sub_423290 —— 写 4B 长度
    HIBYTE(nArg2) = 1;  // 调 取 16 位值高 8 位
    sub_423290(dword_8F7B08, (int)&nArg2 + 3, 1);  // sub_423290 —— 写 4B 长度
    result = sub_423380(dword_8F7B08);  // sub_423380 —— 发包提交：Commit()
    dword_795D48 = *(uint32_t *)(this + 52);  // 读字段 dword_795D48 = this+52（bAuraState）
  }
  return result;
}



// ------------------------------------------------------------
// 0x62F670 CNRDCompoundItemWindow__vmt14
//   【块尾 UI】RECIPE_NOTICE —— 合成提示
// ------------------------------------------------------------
char /*thiscall*/ CNRDCompoundItemWindow__vmt14(char **this)  // 实现：(块尾 UI)RECIPE_NOTICE —— 合成提示
{
  char *v3; // eax

  if ( *(uint32_t *)(dword_8F7A24 + 12) != 1 )  // dword_8F7A24 —— 取当前模块类型(1主城/2选图/4PVP/6WARROOM)
  {
    v3 = sub_422E70(933);  // sub_422E70 —— 存 CStringManager::getStr 取本地化串
    sub_44E8D0(*(this + 4), (void *)0x1B, (int)v3, 0);  // sub_44E8D0 —— 向消息池投递文案（0x1B = 消息窗类型）
    sub_432EA0("RECIPE_NOTICE", -1, 0, 0);  // sub_432EA0 —— 字符串 “CLICK_BUTTON2”
    (*((void (/*thiscall*/ **)(char **))*this + 8))(this);  // 虚调用 vt+8（this 虚表槽）
  }
  else if ( (*(this + 9))[17] != 0 )  // this+36〔nStateWord36(推断)〕
  {
    if ( *((uint8_t *)this + 200) != 0 )  // this+200 主状态
    {
      sub_540DE0(5, 7, 0, 7, 0, *(this + 12), 0);  // sub_540DE0 —— 摊位列表构建（203 行：540A10/62EE70/540A50/541A30/542AB0 + 484FA0/48FCA0/48FD70 窗口件）
    }
    else
    {
      sub_62F530((int)this, 1);  // sub_62F530 —— 合成请求发包（27 号包）
      (*((void (/*thiscall*/ **)(char **))*this + 8))(this);  // 虚调用 vt+8（this 虚表槽）
    }
    return 1;  // 返回 1(成功)
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x62F700 sub_62F700 —— 合成窗口控件构建
//    以全局 UI 件(dword_99FCC8+20) 的 +96/+60/+44 字段经 sub_43C410 建 4 个 CNButton（贴图组 0/1/2/3、12/13/14、4/4/5、6/6/7）存 +36/+40/+204/+208；sub_43C4D0 建 CNSlider 存 +212，sub_43C630 建 CNVScroll（含 +204/+208/+212 三件）存 +216。
//    经虚 44(126,2048) 设标志，sub_69C460(1)/sub_69C480(-16777216)/sub_69C420(2) 设全局文本，末初始化字节 +148..+151 与 +160..+199 布局字段。
// ------------------------------------------------------------
int /*thiscall*/ sub_62F700(uint32_t *this)  // sub_62F700 —— 合成窗口控件构建
{
  int v2; // edx
  uint32_t *pMem; // eax
  uint32_t *fld_e11; // eax
  uint32_t *pMem2; // eax
  uint32_t *v6; // eax
  uint32_t *pMem3; // eax
  uint32_t *v8; // eax
  uint32_t *pMem4; // eax
  uint32_t *v10; // eax
  uint8_t *pMem5; // edi
  uint8_t *pMem52; // eax
  uint8_t *pMem6; // eax
  uint8_t *fld_e51; // eax

  v2 = *this;
  *(this + 11) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 96);  // dword_99FCC8 —— nengine::CNSlider 构造
  (*(void (/*stdcall*/ **)(int, int))(v2 + 44))(126, 2048);  // 虚函数调用 槽+44：定位槽（43C330/69C4C0/69C420 + 69A5F0/69A8
  sub_69C460(1);
  sub_69C480(-16777216);
  sub_69C420(2);
  pMem = operator new(0x84u);  // 堆分配
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    fld_e11 = sub_43C410(pMem, *(this + 11), 0, 1, 2, 3, 0, 0);  // sub_43C410 —— 结果 = nengine::CNButton 构造
  else
    fld_e11 = nullptr;
  *(this + 9) = fld_e11;  // 写字段 this+9 ← fld_e11
  sub_69A840(fld_e11);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem2 = operator new(0x84u);  // 堆分配
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_43C410(pMem2, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 12, 13, 14, 12, 0, 0);  // sub_43C410 —— 结果 = nengine::CNButton 构造
  else
    v6 = nullptr;
  *(this + 10) = v6;  // 写字段 this+10 ← v6
  sub_69A840(v6);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  *((uint8_t *)this + 148) = 0;  // 写字段 this+148（fAdd148）
  *((uint8_t *)this + 149) = 0;  // 写字段 this[149]（宽1字节）
  *((uint8_t *)this + 150) = 0;  // 写字段 this[150]（宽1字节）
  *((uint8_t *)this + 151) = 0;  // 写字段 this[151]（宽1字节）
  *(this + 40) = 0;  // 写字段 this+40（bStateSub40） ← 0
  *(this + 41) = 6;  // 写字段 this+41 ← 6
  *(this + 42) = 12;  // 写字段 this+42 ← 12
  *(this + 43) = 0;  // 写字段 this+43 ← 0
  *(this + 44) = 1600;  // 写字段 this+44（nExpireMs） ← 1600
  *(this + 45) = 0;  // 写字段 this+45 ← 0
  *(this + 46) = 0;  // 写字段 this+46 ← 0
  *(this + 47) = 0;  // 写字段 this+47 ← 0
  *(this + 48) = 0;  // 写字段 this+48（pCmdVecBegin48） ← 0
  *(this + 49) = 0;  // 写字段 this+49（bUdpReported） ← 0
  *(this + 49) = dword_99FCCC;  // 写字段 this+49（bUdpReported） ← dword_99FCCC
  *(this + 38) = -16777216;  // 写字段 this+38（bFadeFlag38） ← -16777216
  pMem3 = operator new(0x84u);  // 堆分配
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    v8 = sub_43C410(pMem3, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 4, 4, 5, 4, 0, 0);  // sub_43C410 —— 结果 = nengine::CNButton 构造
  else
    v8 = nullptr;
  *(this + 51) = v8;  // 写字段 this+51 ← v8
  *((uint8_t *)v8 + 16) = 1;  // 写字段 v8+16（nChannelTypeSel）
  pMem4 = operator new(0x84u);  // 堆分配
  if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    v10 = sub_43C410(pMem4, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 44), 6, 6, 7, 6, 0, 0);  // sub_43C410 —— 结果 = nengine::CNButton 构造
  else
    v10 = nullptr;
  *(this + 52) = v10;  // 写字段 this+52（bAuraState） ← v10
  *((uint8_t *)v10 + 16) = 1;  // 写字段 v10+16（nChannelTypeSel）
  pMem5 = operator new(0x88u);  // 堆分配
  if ( pMem5 != nullptr )  // 若 pMem5 有效（非空）
  {
    sub_43C4D0(pMem5, *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 60), 219, 88);  // sub_43C4D0 —— nengine::CNSlider 构造
    *(uint32_t *)pMem5 = &vftbl_nengine__CNVSlider;  // 构造装配 vftable：nengine__CNVSlider
    pMem52 = pMem5;
  }
  else
  {
    pMem52 = nullptr;
  }
  *(this + 53) = pMem52;  // 写字段 this+53 ← pMem52
  pMem6 = operator new(0x74u);  // 堆分配
  if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
    fld_e51 = sub_43C630(pMem6, *(this + 51), *(this + 52), *(this + 53));  // sub_43C630 —— 结果 = nengine::CNVScroll 构造
  else
    fld_e51 = nullptr;
  *(this + 54) = fld_e51;  // 写字段 this+54 ← fld_e51
  return sub_69A840(fld_e51);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
}



// ------------------------------------------------------------
// 0x62F9A0 sub_62F9A0 —— 合成表元素倒序搬移
//    44 字节元素自 uArg2 向 uArg1 倒序逐个复制到 uArg3 之前（string 子块经 sub_4014D0 赋值，下标 8/9/10 直拷），返回新起点。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_62F9A0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // sub_62F9A0 —— 合成表元素倒序搬移
{
  uint32_t *uArg22; // esi
  uint32_t *uArg32; // edi
  int v5; // eax

  uArg22 = uArg2;
  if ( uArg1 == uArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    v5 = *(uArg22 - 11);
    uArg22 -= 11;
    uArg32 -= 11;
    *uArg32 = v5;
    sub_4014D0((std::_String_base *)(uArg32 + 1), uArg22 + 1, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    uArg32[8] = uArg22[8];
    uArg32[9] = uArg22[9];
    uArg32[10] = uArg22[10];
  }
  while ( uArg22 != uArg1 );  // 循环直到 uArg22 != uArg1
  return uArg32;
}



// ------------------------------------------------------------
// 0x62FA00 sub_62FA00 —— 合成表元素构造
//    初始化 44 字节元素：首字段 0，string 子块置空串（容量 15、长度 0），尾三字段 +32/+36/+40 清零。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_62FA00(uint32_t *this)  // sub_62FA00 —— 合成表元素构造
{
  uint32_t *pThis_1; // ecx

  pThis_1 = this + 1;
  pThis_1[6] = 15;
  pThis_1[5] = 0;
  *((uint8_t *)pThis_1 + 4) = 0;  // 写字段 pThis_1+4（pHostObj）
  *this = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 8) = 0;  // 写字段 this+8（nSkillRec8） ← 0
  *(this + 9) = 0;  // 写字段 this+9 ← 0
  *(this + 10) = 0;  // 写字段 this+10 ← 0
  return this;
}



// ------------------------------------------------------------
// 0x62FA60 sub_62FA60 —— 合成表元素区间填充
//    把 pArg3 元素（string 经 sub_4014D0 赋值与下标 8/9/10）正向重复填充 [uArg1,uArg2)，返回 uArg2。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_62FA60(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)  // sub_62FA60 —— 合成表元素区间填充
{
  uint32_t *result; // eax
  uint32_t *i; // esi

  result = uArg2;
  for ( i = uArg1; i != uArg2; i += 11 )
  {
    *i = *pArg3;
    sub_4014D0((std::_String_base *)(i + 1), pArg3 + 1, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    i[8] = pArg3[8];
    i[9] = pArg3[9];
    i[10] = pArg3[10];
    result = uArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x62FAB0 sub_62FAB0 —— 倒序搬移转发 thunk
//    直接转发 sub_62F9A0（倒序搬移 thunk）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_62FAB0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // sub_62FAB0 —— 倒序搬移转发 thunk
{
  return sub_62F9A0(uArg1, uArg2, uArg3);  // sub_62F9A0 —— 合成表元素倒序搬移
}



// ------------------------------------------------------------
// 0x62FAD0 sub_62FAD0 —— 合成表元素正向复制
//    把 [pArg1,uArg2) 的 44 字节元素逐项正向复制到 nArg3 起（string 经 sub_4014D0 深拷），返回末尾指针。
// ------------------------------------------------------------
int /*cdecl*/ sub_62FAD0(uint32_t *pArg1, uint32_t *uArg2, int nArg3)  // sub_62FAD0 —— 合成表元素正向复制
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != uArg2 )  // 循环直到 pArg1 != uArg2
  {
    LOBYTE(v7) = 1;  // 调 取 16 位值低 8 位
    if ( nArg32 != 0 )
    {
      *(uint32_t *)nArg32 = *pArg1;
      *(uint32_t *)(nArg32 + 28) = 15;  // 写字段 nArg32+28（pPanelVec） ← 15
      *(uint32_t *)(nArg32 + 24) = 0;  // 写字段 nArg32+24（nPageMax） ← 0
      *(uint8_t *)(nArg32 + 8) = 0;  // 写字段 nArg32+8（nSkillRec8） ← 0
      sub_4014D0((std::_String_base *)(nArg32 + 4), pArg1 + 1, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      *(uint32_t *)(nArg32 + 32) = pArg1[8];  // 写字段 nArg32+32（nHeight） ← pArg1[8]
      *(uint32_t *)(nArg32 + 36) = pArg1[9];  // 写字段 nArg32+36（nStateWord36） ← pArg1[9]
      *(uint32_t *)(nArg32 + 40) = pArg1[10];  // 写字段 nArg32+40（bStateSub40） ← pArg1[10]
    }
    nArg32 += 44;
    LOBYTE(v7) = 0;  // 调 取 16 位值低 8 位
    pArg1 += 11;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x62FBB0 sub_62FBB0 —— 合成表元素重复填充
//    把 pArg3 的 44 字节元素重复复制 nArg2 份到 nArg1 起（string 经 sub_4014D0），返回末次复制的元素 +32 字段。
// ------------------------------------------------------------
int /*cdecl*/ sub_62FBB0(int nArg1, int nArg2, uint32_t *pArg3)  // sub_62FBB0 —— 合成表元素重复填充
{
  int nArg12; // esi
  int result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v5[5] = v5;
  v5[4] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 循环直到 nArg2 != 0
  {
    v5[3] = nArg12;
    LOBYTE(v6) = 1;  // 调 取 16 位值低 8 位
    if ( nArg12 != 0 )
    {
      *(uint32_t *)nArg12 = *pArg3;
      *(uint32_t *)(nArg12 + 28) = 15;  // 写字段 nArg12+28（pPanelVec） ← 15
      *(uint32_t *)(nArg12 + 24) = 0;  // 写字段 nArg12+24（nPageMax） ← 0
      *(uint8_t *)(nArg12 + 8) = 0;  // 写字段 nArg12+8（nSkillRec8） ← 0
      sub_4014D0((std::_String_base *)(nArg12 + 4), pArg3 + 1, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      result = pArg3[8];
      *(uint32_t *)(nArg12 + 32) = result;  // 写字段 nArg12+32（nHeight） ← result
      *(uint32_t *)(nArg12 + 36) = pArg3[9];  // 写字段 nArg12+36（nStateWord36） ← pArg3[9]
      *(uint32_t *)(nArg12 + 40) = pArg3[10];  // 写字段 nArg12+40（bStateSub40） ← pArg3[10]
    }
    nArg12 += 44;
    LOBYTE(v6) = 0;  // 调 取 16 位值低 8 位
    --nArg2;  // 计数自减 nArg2
  }
  return result;
}



// ------------------------------------------------------------
// 0x62FC90 sub_62FC90 —— 重复填充并返回尾部
//    调用 sub_62FBB0 重复填充后返回末元素之后指针（nArg1 + 44×nArg2）。
// ------------------------------------------------------------
int /*stdcall*/ sub_62FC90(int nArg1, int nArg2, uint32_t *uArg3)  // sub_62FC90 —— 重复填充并返回尾部
{
  sub_62FBB0(nArg1, nArg2, uArg3);  // sub_62FBB0 —— 合成表元素重复填充
  return nArg1 + 44 * nArg2;
}



// ------------------------------------------------------------
// 0x62FCC0 sub_62FCC0 —— 合成表元素插入（含扩容）
//    在 44 字节元素表(+4/+8/+12) 处插入 uArg3 个 pDwArg4 副本：先把模板拷入局部（string 经 sub_4014D0），元素数超 97612893 时走 sub_558090（【推断】长度异常路径）。
//    容量够时原地 sub_62FAD0 出尾、sub_62FAB0（转发 sub_62F9A0）倒序后移中段、sub_62FA60 填空；不足则按 1.5 倍容量（仍不足取 uArg3+sub_527B90(this)）new 新缓冲、sub_62FAD0 前后段搬运与 sub_62FBB0 填充，sub_528410 释放旧区并更新 +4/+8/+12。
// ------------------------------------------------------------
void /*thiscall*/ sub_62FCC0(int *this, int pArg2, unsigned int uArg3, int *pDwArg4)  // sub_62FCC0 —— 合成表元素插入（含扩容）
{
  int v5; // eax
  int v6; // eax
  int v7; // ecx
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v13; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v17; // edi
  int fld_e14; // eax
  int fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-70h]
  int fld_e28; // [esp-10h] [ebp-68h]
  int fld_e25; // [esp-Ch] [ebp-64h]
  unsigned int fld_e24; // [esp-8h] [ebp-60h]
  int v26; // [esp+0h] [ebp-58h] BYREF
  void *Block; // [esp+Ch] [ebp-4Ch]
  int *pThis; // [esp+10h] [ebp-48h]
  char *pMem2; // [esp+14h] [ebp-44h]
  int v30; // [esp+18h] [ebp-40h] BYREF
  char v31[4]; // [esp+1Ch] [ebp-3Ch] BYREF
  void *v32; // [esp+20h] [ebp-38h]
  int v33; // [esp+30h] [ebp-28h]
  unsigned int v34; // [esp+34h] [ebp-24h]
  int v35; // [esp+38h] [ebp-20h]
  int v36; // [esp+3Ch] [ebp-1Ch]
  int v37; // [esp+40h] [ebp-18h]
  int dword_796E502; // [esp+44h] [ebp-14h]
  int *v39; // [esp+48h] [ebp-10h]
  int v40; // [esp+54h] [ebp-4h]
  int v41; // [esp+60h] [ebp+8h]
  int v42; // [esp+64h] [ebp+Ch]
  int fld_e232; // [esp+68h] [ebp+10h]

  v39 = &v26;
  dword_796E502 = dword_796E50;  // dword_796E502 —— 栈检 cookie
  v5 = *pDwArg4;
  pThis = this;
  v30 = v5;
  v34 = 15;
  v33 = 0;
  LOBYTE(v32) = 0;  // 调 取 16 位值低 8 位
  sub_4014D0((std::_String_base *)v31, pDwArg4 + 1, 0, -1);  // sub_4014D0 —— std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  v6 = pDwArg4[9];
  v7 = pDwArg4[10];
  v35 = pDwArg4[8];
  v36 = v6;
  v37 = v7;
  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  v40 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 44;  // this+12〔nSkillRec12(推断)〕
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 44;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e2 = 0;
    if ( 97612893 - fld_e2 < uArg3 )
      sub_558090(this);  // sub_558090 —— 分隔符文本组装（4015C0/401740——信息窗共用）
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 44;  // this+8〔nSkillRec8(推断)〕
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = *(this + 2);  // 读字段 fld_e23 = this+2
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 44 >= uArg3 )
      {
        v41 = fld_e23 - 44 * uArg3;
        *(this + 2) = sub_62FAD0(v41, fld_e23, fld_e23);  // sub_62FAD0 —— 合成表元素正向复制
        sub_62FAB0(pArg2, v41, fld_e232);  // sub_62FAB0 —— 倒序搬移转发 thunk
        sub_62FA60(pArg2, pArg2 + 44 * uArg3, &v30);  // sub_62FA60 —— 合成表元素区间填充
      }
      else
      {
        sub_62FAD0(pArg2, fld_e23, pArg2 + 44 * uArg3);  // sub_62FAD0 —— 合成表元素正向复制
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 44;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // 读字段 fld_e25 = this+2
        LOBYTE(v40) = 3;  // 调 取 16 位值低 8 位
        sub_62FC90(fld_e25, fld_e24, &v30);  // sub_62FC90 —— 重复填充并返回尾部
        fld_e26 = 44 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // 写字段 this+2 ← fld_e26
        v40 = 0;
        sub_62FA60(pArg2, fld_e26 - 44 * uArg3, &v30);  // sub_62FA60 —— 合成表元素区间填充
      }
    }
    else
    {
      if ( 97612893 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 44;  // this+8〔nSkillRec8(推断)〕
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_527B90(this);  // 调 取 size
      v42 = 44 * v13;  // 计算 v42 = 44 * v13
      pMem = (char *)operator new(44 * v13);  // 堆分配
      fld_e12 = *(this + 1);  // 读字段 fld_e12 = this+1
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v40) = 1;  // 调 取 16 位值低 8 位
      pMem2 = (char *)sub_62FAD0(fld_e12, pArg2, pMem);  // sub_62FAD0 —— 合成表元素正向复制
      sub_62FBB0(pMem2, uArg3, &v30);  // sub_62FBB0 —— 合成表元素重复填充
      fld_e28 = *(this + 2);  // 读字段 fld_e28 = this+2
      pMem2 += 44 * uArg3;
      sub_62FAD0(pArg2, fld_e28, pMem2);  // sub_62FAD0 —— 合成表元素正向复制
      fld_e13 = *(this + 1);  // 读字段 fld_e13 = this+1
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 44;  // this+8〔nSkillRec8(推断)〕
      v17 = fld_e13 + uArg3;  // 计算 v17 = fld_e13 + uArg3
      fld_e14 = *(this + 1);  // 读字段 fld_e14 = this+1
      if ( fld_e14 != 0 )
      {
        sub_528410(fld_e14, *(this + 2));  // 调 释放旧区并更新 +4/+8/+12
        j__free((void *)*(this + 1));  // 释放堆块
      }
      *(this + 3) = (int)&pMem[v42];  // 写字段 this+3 ← (int)&pMem[v42]
      *(this + 2) = (int)&pMem[44 * v17];  // 写字段 this+2 ← (int)&pMem[44 * v17]
      *(this + 1) = (int)pMem;  // 写字段 this+1 ← (int)pMem
    }
  }
  if ( v34 >= 0x10 )
    j__free(v32);  // 释放堆块
}


// ------------------------------------------------------------
// 0x62FFF0 sub_62FFF0 —— 合成表插入并回传位置
//    先算出 pszArg3 相对表首 +4 的下标（空表取 0），再 sub_62FCC0 插入 1 个 pDwArg4 副本，*uArg2 回传插入位置指针。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_62FFF0(int *this, uint32_t *uArg2, char *pszArg3, int *pDwArg4)  // sub_62FFF0 —— 合成表插入并回传位置
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // 读字段 fld_e1 = this+1
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 44 != 0 )  // this+8〔nSkillRec8(推断)〕
    v6 = (int)&pszArg3[-fld_e1] / 44;
  else
    v6 = 0;
  sub_62FCC0(this, pszArg3, 1u, pDwArg4);  // sub_62FCC0 —— 合成表元素插入（含扩容）
  *uArg2 = *(this + 1) + 44 * v6;  // this+4〔宿主对象〕
  return uArg2;
}


