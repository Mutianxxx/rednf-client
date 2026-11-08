// ============================================================
// 【40JP逆向源代码工程】game/anim_parser.cpp
// 模块: .ani 动画帧解析器 + 帧时间引擎 + 状态演出/对话脚本族
// 来源: work/dump_misca.txt  区块: 0x490000-0x4A0000
// 层级: L2 转写层 → L1 精修层（会话精修：帧结构字段映射 + 解析器标签清单 + 功能族分区）
// 函数数: 325
//
// ★ 数据基座（研究 20 §11 定案）：.ani 逐帧 88 字节，帧数组 = 动画对象+44 处 vector
//   （首 +44 / 尾 +48，元素 22×uint32）。帧内偏移：
//     +0 图像句柄   +4 路径资源id  +8 资源id          [IMAGE]
//     +12/+16 位置x/y                                  [IMAGE POS]
//     +20/+24 缩放x/y(float)                           [IMAGE RATE]
//     +28 旋转(float)                                  [IMAGE ROTATE]
//     +32 RGBA(打包uint32)                             [RGBA]
//     +36 插值开关                                     [INTERPOLATION]
//     +40 特效枚举 0=NONE 1=DODGE 2=LINEARDODGE 3=DARK 4=? 5=MONOCHROME
//     +44 MONOCHROME 参数色                            [GRAPHIC EFFECT]
//     +48 ★本帧驻留时长 ms                             [DELAY]
//     +52 ★伤害类型 0=NORMAL 1=SUPERARMOR(霸体) 2=UNBREAKABLE(不可打断) [DAMAGE TYPE]
//     +56..71 攻击盒vector  +72..87 受击盒vector        [ATTACK BOX]/[DAMAGE BOX]（各6float，可多组）
//   动画对象关键字段：+32 累计播放ms · +148 当前帧索引 · +152/+156 帧首/帧尾时刻 ·
//   +160 [LOOP] · +161 [SHADOW] · +164 播放速率(默认100.0f) · +169/170 暂停/播完 ·
//   +204 子动画链(list) · +212 同步源引用【推断】
//   帧尾公式 = 帧首 + DELAY×100/速率（sub_491C70）；帧间位置/缩放/旋转/RGBA 线性插值
//   （sub_4919D0 → sub_4049C0）；变速按新旧速率比换算累计时长（sub_493D00，研究 20 §26）。
//
// ★ 解析器标签清单：
//   - sub_494680 .ani 主解析器：[LOOP][SHADOW][FRAME MAX][FRAME000][IMAGE][IMAGE POS]
//     [IMAGE RATE][IMAGE ROTATE][RGBA][INTERPOLATION][GRAPHIC EFFECT](NONE/DODGE/
//     LINEARDODGE/DARK/?(off_6CAF88)/MONOCHROME)[DELAY][DAMAGE TYPE](NORMAL/SUPERARMOR/
//     UNBREAKABLE)[ATTACK BOX][DAMAGE BOX]
//   - sub_49B930 对话脚本解析器：[talk name][commands]+off_790B94 命令表(12 条)+
//     [pass next command][img]（命令节点 0x14/0x38 字节，其 +48/+52 是节点字段≠帧结构）
//
// 分区（按 VA 升序）：
//   §A 0x4900E0-0x490880  角色对象联动族（槽位切换 @@SET HOST / LADDER_DOWN）
//   §B 0x490880-0x491130  动画对象状态基座（+212 同步源 / +216..232 状态位）
//   §C 0x491130-0x4919D0  帧渲染/图层属性族（sub_4049C0 插值、图层 +40..+56）
//   §D 0x4919D0-0x492530  ★ 帧插值与帧时间换算（sub_4919D0/sub_491C70）
//   §E 0x492530-0x493400  攻击盒/受击盒容器族（元素 24B=6float）
//   §F 0x493400-0x493DB0  ★ 帧数组容器(88B) + 帧推进/变速引擎（sub_493840/sub_493D00）
//   §G 0x493DB0-0x494680  帧数组批量操作 + 加载准备
//   §H 0x494680-0x494E40  ★★★ .ani 主解析器 sub_494680
//   §I 0x494E40-0x496540  动画/粒子创建工厂（ANIMATION CREATE FAIL）
//   §J 0x496540-0x497EA0  异常状态演出表（Common/ActiveStatus/*.ani|ptl）
//   §K 0x497EA0-0x499C70  状态应用与播放驱动（sub_4985E0 加载/sub_498B70 快照）
//   §L 0x499C70-0x49B860  主播放驱动 + 组件属性访问器族（对象 +40..+59 字段）
//   §M 0x49B860-0x49BE70  对话脚本解析器 sub_49B930 + COUNT_DOWN
//   §N 0x49BE70-0x49CA80  UI/窗口联动（CLICK_BUTTON2）
//   §O 0x49CA80-0x49E930  结算演出族（M_RESULT / RESULT_FLASH）
//   §P 0x49E930-0x49FFC0  列表子项管理 + 收尾
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// §A 0x4900E0-0x490880  角色对象联动族（槽位切换 @@SET HOST / LADDER_DOWN）
// ============================================================
// ------------------------------------------------------------
// 0x4900E0 sub_4900E0 —— 角色槽位/物件状态切换总入口
//   @@SET HOST 宿主转移、LADDER_DOWN 音效、新对象 vtable+372 广播(模式 0..2)、
//   尾调 sub_49CA80(dword_8F8528[9]) 刷新。
// ------------------------------------------------------------
int /*thiscall*/ sub_4900E0(uint32_t *this, int ArgList, int nArg3, int nArg4)
{
  int result; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // ebx
  uint32_t *pThis_A; // eax
  int v11; // ebx
  int v12; // ecx
  int pThis_1; // eax
  int pObj; // ecx
  int ArgLista; // [esp+14h] [ebp+8h]
  int ArgListb; // [esp+14h] [ebp+8h]
  char ArgListc; // [esp+14h] [ebp+8h]

  ArgLista = *(this + ArgList + 10);
  result = ArgLista;
  if ( ArgLista != nArg3 || (result = *(this + ArgList + 2)) != nArg4 )
  {
    *(this + ArgList + 10) = nArg3;
    *(this + ArgList + 2) = nArg4;
    if ( (uint32_t *)dword_99FF08 == this )
    {
      *(this + ArgList + 20) = 0;
      *(this + ArgList + 28) = 0;
      *((uint8_t *)this + ArgList + 144) = 0;
      sub_4632D0(*((uint32_t *)dword_8F8528 + 4));
      if ( ArgLista != nArg3 )
      {
        if ( nArg3 == 0xFFFF )
        {
          v7 = sub_429830(ArgLista);
          v8 = v7;
          ArgListb = v7;
          if ( v7 != 0 && *(uint32_t *)(v7 + 196) != 0 )
            sub_4B05C0(0);
          if ( *(uint32_t *)(sub_656710() + 40) == ArgList )
          {
            v9 = 0;
            pThis_A = this + 10;
            while ( v9 == ArgList || *pThis_A == 0xFFFF )
            {
              ++v9;
              ++pThis_A;
              if ( v9 >= 8 )
                goto LABEL_16;
            }
            *(uint32_t *)(sub_656710() + 40) = v9;
            off_77F3FC("@@SET HOST %d", v9);
LABEL_16:
            v8 = ArgListb;
          }
          sub_42B580(*(uint32_t *)(dword_8F7A24 + 40), ArgList, v8);
        }
        else
        {
          v11 = sub_429830(nArg3);
          sub_42E120(ArgList, v11, 1);
          v12 = *(uint32_t *)(v11 + 196);
          if ( v12 != 0 )
            sub_4B05B0(v12);
          sub_432EA0("LADDER_DOWN", -1, 0, 0);
        }
      }
      pThis_1 = sub_48F660(this + 1, ArgList);
      if ( pThis_1 != 0 )
      {
        pObj = *(uint32_t *)(pThis_1 + 196);
        if ( pObj != 0 )
        {
          ArgListc = 0;
          switch ( nArg4 )
          {
            case 0:
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, ArgList + 3);
              break;
            case 1:
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 372))(pObj, 0);
              break;
            case 2:
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 1);
              break;
            case 3:
            case 4:
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 2);
              ArgListc = 1;
              break;
            default:
              break;
          }
          sub_4B12B0(ArgListc);
        }
      }
      return sub_49CA80(*((uint32_t *)dword_8F8528 + 9));
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4902A0 sub_4902A0
// ------------------------------------------------------------
bool /*thiscall*/ sub_4902A0(uint32_t *this)
{
  int fld_e18; // eax

  fld_e18 = *(this + 18);
  return fld_e18 != -1 && (fld_e18 == 2 || fld_e18 == 3 || fld_e18 == 4);
}



// ------------------------------------------------------------
// 0x4902C0 sub_4902C0 —— 动画状态复位（+204..232 清零、+216=1、+232=-1）
// ------------------------------------------------------------
int /*thiscall*/ sub_4902C0(int this)
{
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint8_t *)(this + 216) = 1;
  *(uint8_t *)(this + 217) = 0;
  *(uint32_t *)(this + 232) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x4902F0 sub_4902F0 —— 粒子创建包装（"%s%s" 拼路径；失败 PARTICLE CREATER CREATE FAIL!）
// ------------------------------------------------------------
int /*thiscall*/ sub_4902F0(void *this, const char *ArgList, const char *pArg3)
{
  int v4; // eax

  v4 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, "%s%s", ArgList, pArg3);
  if ( v4 != 0 )
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 8))(this, v4);
  else
    return off_77F3FC("PARTICLE CREATER CREATE FAIL! FILENAME[%s%s]", ArgList, pArg3);
}



// ------------------------------------------------------------
// 0x490340 sub_490340
// ------------------------------------------------------------
int /*thiscall*/ sub_490340(void *this, int pArg2)
{
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 24))(this, pArg2);
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, pArg2 + 100);
}



// ------------------------------------------------------------
// 0x490370 sub_490370 —— 子动画挂接初始化（+204=子链、+220..228 快照本对象 +4/+8/+12、+232=-1）
// ------------------------------------------------------------
int /*thiscall*/ sub_490370(int this, int nArg2)
{
  int fld_8; // edx
  int result; // eax

  *(uint8_t *)(this + 189) = 0;
  *(uint8_t *)(this + 190) = 0;
  *(uint32_t *)(this + 204) = nArg2;
  *(uint32_t *)(this + 208) = 0;
  *(uint32_t *)(this + 212) = 0;
  *(uint8_t *)(this + 216) = 0;
  fld_8 = *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 220) = *(uint32_t *)(this + 4);
  result = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 224) = fld_8;
  *(uint32_t *)(this + 228) = result;
  *(uint32_t *)(this + 232) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x4903D0 sub_4903D0 —— +176 色调对象启停（开关位 +217）
// ------------------------------------------------------------
char /*thiscall*/ sub_4903D0(uint8_t *this, char pszArg2)
{
  int pThis_B0; // ecx
  char result; // al

  pThis_B0 = (int)(this + 176);
  if ( pszArg2 != 0 )
  {
    result = sub_699030(pThis_B0);  // 【clock_freeze(clk)】
    *(this + 217) = pszArg2;
  }
  else
  {
    result = sub_698FE0(pThis_B0);  // 【clock_unfreeze(clk)】
    *(this + 217) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x490410 sub_490410
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_490410(uint32_t *uArg1, int nArg2, int nArg3, uint32_t *uArg4)
{
  int nArg22; // esi
  int v5; // ecx
  int v6; // eax

  nArg22 = nArg2;
  v5 = (nArg3 - nArg2) >> 2;
  while ( v5 > 0 )
  {
    v6 = v5 / 2;
    if ( *(uint32_t *)(nArg22 + 4 * (v5 / 2)) >= *uArg4 )
    {
      v5 /= 2;
    }
    else
    {
      nArg22 += 4 * v6 + 4;
      v5 += -1 - v6;
    }
  }
  *uArg1 = nArg22;
  return uArg1;
}



// ------------------------------------------------------------
// 0x490460 sub_490460
// ------------------------------------------------------------
int /*cdecl*/ sub_490460(int nArg1, int pArg2, uint32_t *pArg3)
{
  int pObj; // esi
  int v4; // eax
  uint32_t *pArg32; // ebx
  uint32_t *v6; // edi
  int *v7; // eax
  int v8; // esi
  int v9; // ecx
  int nRand; // ecx
  int i; // esi
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int nRand2; // edx
  int v16; // eax
  int v17; // esi
  int v18; // eax
  int nRand42; // esi
  double v20; // st7
  double v21; // st7
  int result; // eax
  int nRand5; // edx
  int v24; // eax
  int *v25; // esi
  char v26; // al
  int v27; // ebx
  int nRand6; // ebx
  int v29; // ecx
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  bool v33; // zf
  int v34; // esi
  int nRand7; // edx
  int v36; // ebx
  float v37; // [esp+Ch] [ebp-18h] BYREF
  char v38[4]; // [esp+10h] [ebp-14h] BYREF
  char v39[4]; // [esp+14h] [ebp-10h] BYREF
  int nRand3; // [esp+18h] [ebp-Ch] BYREF
  int v41; // [esp+1Ch] [ebp-8h] BYREF
  int nRand4; // [esp+20h] [ebp-4h]

  pObj = nArg1;
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 12))(nArg1, pArg2);
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);
  pArg32 = pArg3;
  v6 = (uint32_t *)v4;
  v7 = pArg3 + 3;
  v8 = 0;
  nRand4 = (int)(pArg3 + 3);
  do
  {
    if ( *v7 <= 0 )
    {
      *(float *)&v38[4 * v8 - 4] = 0.0;
    }
    else
    {
      v9 = *v7;
      nRand = rand() % (v9 + 1) - v9 / 2;
      v7 = (int *)nRand4;
      nArg1 = nRand;
      *(float *)&v38[4 * v8 - 4] = (float)nRand;
    }
    ++v8;
    nRand4 = (int)++v7;
  }
  while ( v8 < 3 );
  sub_52A1A0(v39, v38, pArg32[8]);
  sub_52A1A0(&v37, v39, pArg32[7]);
  sub_52A1A0(&v37, v38, pArg32[6]);
  for ( i = 0; i < 3; ++i )
  {
    if ( *(uint8_t *)(pArg2 + 84) == 0 || i != 0 )
      v6[i] += (int)(dword_7930D0[i] * (uint64_t)*(float *)&v38[4 * i - 4]) / 100;
    else
      *v6 += (int)(dword_7930D0[0] * (uint64_t)v37) / -100;
  }
  v12 = pArg32[9];
  if ( v12 != 0 )
  {
    if ( v12 == 1 )
    {
      sub_432FA0();
      nRand2 = rand() % 360;
      v6[20] = 90 - nRand2;
      v16 = pArg32[10];
      nRand4 = nRand2;
      if ( v16 != 0 )
      {
        v17 = v16 / 2;
        nRand3 = rand();
        nArg1 = dword_9A011C + 4 * v17;
        v18 = sub_4D33A0(&nRand3);
        nArg1 = v18 % (*(uint32_t *)nArg1 + 1);
        sub_490410(&v41, dword_9A011C, dword_9A011C + 4 * v17, &nArg1);
        nRand42 = nRand4;
        nArg1 = (v41 - dword_9A011C) >> 2;
        *(float *)&nArg1 = (float)nArg1;
        v20 = sub_405400(nRand4);
        v6[18] += (uint64_t)(v20 * *(float *)&nArg1);
        v21 = sub_4053E0(nRand42);
        v6[19] += (uint64_t)(v21 * *(float *)&nArg1);
      }
    }
  }
  else
  {
    v13 = pArg32[10];
    if ( v13 != 0 )
    {
      v6[18] += v13 / -2;
      v6[18] += rand() % (pArg32[10] + 1);
    }
    v14 = pArg32[11];
    if ( v14 != 0 )
    {
      v6[19] += v14 / -2;
      v6[19] += rand() % (pArg32[11] + 1);
    }
  }
  result = pArg32[12];
  if ( result != 0 )
  {
    nRand4 = rand() % (10 * pArg32[12] + 1) - 5 * pArg32[12];
    nRand5 = rand() % (10 * pArg32[12] + 1);
    v24 = 5 * pArg32[12];
    nArg1 = (int)(v6 + 3);
    v25 = (uint32_t *)((char *)v6 + 15);
    nRand3 = 3;
    v41 = nRand5 - v24;
    do
    {
      v26 = *(uint8_t *)nArg1;
      if ( *(uint8_t *)nArg1 == 1 )
      {
        v27 = pArg32[12];
        nRand6 = rand() % (10 * v27 + 1) - 5 * v27 + 1000;
        *v25 = nRand6 * *v25 / 1000;
        v29 = nRand6 * v25[1];
        pArg32 = pArg3;
        v25[1] = v29 / 1000;
      }
      else if ( v26 == 2 || v26 == 3 )
      {
        v30 = v41 + 1000;
        *v25 = (nRand4 + 1000) * *v25 / 1000;
        v31 = v25[1];
        v25[6] = v30 * v25[6] / 1000;
        v32 = v41 + 1000;
        v25[1] = (nRand4 + 1000) * v31 / 1000;
        v25[7] = v32 * v25[7] / 1000;
      }
      v25 += 2;
      v33 = nRand3 == 1;
      ++nArg1;
      --nRand3;
    }
    while ( !v33 );
    v34 = pArg32[12];
    nRand7 = (uint64_t)(274877907LL * *(uint32_t *)((char *)v6 + 63) * (5 * (200 - v34) + rand() % (10 * v34 + 1))) >> 32;
    result = *(uint32_t *)((char *)v6 + 85);
    *(uint32_t *)((char *)v6 + 63) = (nRand7 >> 6) + ((unsigned int)nRand7 >> 31);
    if ( result != 0 )
    {
      v36 = pArg32[12];
      result = *(uint32_t *)((char *)v6 + 85) * (5 * (200 - v36) + rand() % (10 * v36 + 1)) / 1000;
      *(uint32_t *)((char *)v6 + 85) = result;
      if ( result <= 0 )
        *(uint32_t *)((char *)v6 + 85) = 1;
    }
  }
  return result;
}


// ============================================================
// §B 0x490880-0x491130  动画对象状态基座（+212 同步源 / +216..232 状态位）
// ============================================================
// ------------------------------------------------------------
// 0x490880 sub_490880
// ------------------------------------------------------------
void /*noreturn*/ sub_490880()
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
// 0x4908F0 sub_4908F0
// ------------------------------------------------------------
char /*thiscall*/ sub_4908F0(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x3FFFFFFF )
    sub_490880(this);
  pMem = (char *)operator new(4 * uArg2);
  *(this + 3) = &pMem[4 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x490950 sub_490950
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_490950(int this, int Src, unsigned int uArg3, int *pDwArg4)
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
      sub_490880(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);
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
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
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
// 0x490B30 sub_490B30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_490B30(uint32_t *this, int pArg2)
{
  int v3; // ecx
  unsigned int v4; // eax
  int v6; // [esp-14h] [ebp-34h]
  int v7; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(pArg2 + 4);
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( sub_4908F0(this, v4) != 0 )
  {
    fld_e1 = *(this + 1);
    v7 = *(uint32_t *)(pArg2 + 8);
    v6 = *(uint32_t *)(pArg2 + 4);
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x490BD0 sub_490BD0
// ------------------------------------------------------------
int /*thiscall*/ sub_490BD0(uint32_t *this)
{
  uint32_t *pThis; // esi
  char *v2; // edx
  int v3; // eax
  int v4; // ebx
  int *v5; // esi
  uint64_t v6; // rax
  char *v7; // edi
  uint32_t *dword_9A01202; // edx
  int v11; // [esp+8h] [ebp-4h] BYREF

  pThis = this;
  *(this + 55) = -1;
  *(this + 56) = -1;
  *(this + 57) = -1;
  if ( byte_9A0110 == 0 )
  {
    v2 = (char *)dword_9A0120;
    v11 = 0;
    if ( dword_9A011C != 0
      && ((int)dword_9A0120 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )
    {
      *(uint32_t *)dword_9A0120 = 0;
      dword_9A0120 = v2 + 4;
    }
    else
    {
      sub_430C80(dword_9A0120, 1, (int)&v11);
    }
    v3 = 0;
    do
    {
      v4 = v3 + 1;
      v5 = (int *)(dword_9A011C + 4 * v3);
      v6 = (uint64_t)(sub_4053E0(v3 + 1) * 1000.0 + (double)*v5);
      v7 = (char *)dword_9A0120;
      v11 = v6;
      if ( dword_9A011C != 0
        && ((int)dword_9A0120 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )
      {
        dword_9A01202 = (char *)dword_9A0120 + 4;
        *(uint32_t *)dword_9A0120 = v6;
        dword_9A0120 = v7 + 4;
      }
      else
      {
        sub_430C80(dword_9A0120, 1, (int)&v11);
        dword_9A01202 = dword_9A0120;
      }
      v3 = v4;
    }
    while ( v4 < 180 );
    v11 = 0;
    if ( dword_9A011C != 0 && ((int)dword_9A01202 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )
    {
      *dword_9A01202 = 0;
      dword_9A0120 = dword_9A01202 + 1;
    }
    else
    {
      sub_430C80(dword_9A01202, 1, (int)&v11);
    }
    pThis = this;
    byte_9A0110 = 1;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*pThis + 88))(pThis, 1);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis + 12))(pThis, 0);
}



// ------------------------------------------------------------
// 0x490D40 sub_490D40
// ------------------------------------------------------------
int /*thiscall*/ sub_490D40(uint32_t *this, int nArg2, int nArg3)
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 4))(this, nArg2, nArg3);
  return sub_490BD0(this);
}



// ------------------------------------------------------------
// 0x490D70 sub_490D70 —— 按时间步(1000ms)批量生成对象
//   速率因子 = 浮点字段 +26（-1.0f=0xBF800000 哨兵=不限）；+55..57 目标 ←
//   sub_4049C0(旧值+1..3, 新值, 步进) 逐格插值；+53 记录已完成步数。
// ------------------------------------------------------------
int /*thiscall*/ sub_490D70(uint32_t *this, int nArg2)
{
  int pThis_2C; // edi
  int fld_e51; // ecx
  void *v5; // edi
  char pThis_D8; // al
  int v7; // eax
  int v8; // eax
  int fld_e28; // eax
  int pThis_1A; // ecx
  int fld_e272; // eax
  int fld_e53; // ebx
  double pThis_1A2; // st7
  int pObj; // edi
  int v15; // eax
  double v16; // st7
  int pThis_59; // eax
  int v18; // eax
  int v19; // eax
  int *pThis_37; // eax
  int v21; // edx
  bool v22; // zf
  int fld_e532; // eax
  int v24; // ebx
  int v25; // eax
  int v26; // ecx
  char *v27; // eax
  int fld_e2; // ecx
  int fld_e3; // edx
  int nArg22; // esi
  float v32; // [esp+Ch] [ebp-60h]
  float v33; // [esp+10h] [ebp-5Ch]
  int fld_e27; // [esp+18h] [ebp-54h]
  int fld_e26; // [esp+18h] [ebp-54h]
  int fld_e46; // [esp+18h] [ebp-54h]
  int fld_e533; // [esp+18h] [ebp-54h]
  char v38[4]; // [esp+28h] [ebp-44h] BYREF
  uint8_t *v39; // [esp+2Ch] [ebp-40h]
  void *Src; // [esp+30h] [ebp-3Ch]
  int v41; // [esp+34h] [ebp-38h]
  int pObj2; // [esp+38h] [ebp-34h] BYREF
  int v43; // [esp+3Ch] [ebp-30h]
  int v44; // [esp+40h] [ebp-2Ch]
  int v45; // [esp+44h] [ebp-28h]
  int fld_e534; // [esp+48h] [ebp-24h]
  int v47; // [esp+4Ch] [ebp-20h]
  int *pThis_372; // [esp+50h] [ebp-1Ch]
  int fld_e512; // [esp+54h] [ebp-18h]
  int v50; // [esp+58h] [ebp-14h]
  int fld_e52; // [esp+5Ch] [ebp-10h]
  int v52; // [esp+68h] [ebp-4h]

  pThis_2C = (int)(this + 44);
  pObj2 = 0;
  sub_698F90((int)(this + 44), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_e51 = sub_699000(pThis_2C) + *(this + 51);  // 【clock_now(clk)】
  v5 = nullptr;
  *(this + 52) = fld_e51;
  v39 = nullptr;
  Src = nullptr;
  v41 = 0;
  pThis_D8 = *((uint8_t *)this + 216);
  v52 = 0;
  if ( pThis_D8 != 0 )
    goto LABEL_39;
  if ( *(this + 58) == -1 )
    *(this + 58) = dword_9A0114;
  if ( *((float *)this + 26) == 0.0 || *(this + *(this + 58) + 40) == 0 )
  {
    *((uint8_t *)this + 216) = 1;
LABEL_39:
    nArg22 = nArg2;
    sub_490B30(v38);
    return nArg22;
  }
  if ( *(this + 26) == -1082130432 )
  {
    v7 = *this;
    fld_e27 = *(this + 27);
    *((uint8_t *)this + 216) = 1;
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 84))(this, fld_e27);
  }
  else
  {
    fld_e28 = *(this + 28);
    fld_e512 = fld_e51;
    if ( fld_e28 > 0 && fld_e51 >= fld_e28 )
    {
      *((uint8_t *)this + 216) = 1;
      fld_e512 = fld_e28;
    }
    pThis_1A = 1 - (uint64_t)((double)fld_e512 * *((float *)this + 26) * -0.001);
    fld_e272 = *(this + 27);
    if ( fld_e272 != 0 && pThis_1A >= fld_e272 )
    {
      *((uint8_t *)this + 216) = 1;
      pThis_1A = fld_e272;
    }
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 84))(this, pThis_1A);
  }
  fld_e53 = *(this + 53);
  v50 = v8;
  fld_e534 = fld_e53;
  if ( fld_e53 < v8 )
  {
    fld_e512 = 1000 * fld_e53;
    do
    {
      pThis_1A2 = *((float *)this + 26);
      pObj = 0;
      fld_e52 = 0;
      if ( pThis_1A2 <= 0.0 )
      {
        if ( *(this + 26) == -1082130432 )
          fld_e52 = *(this + 52);
      }
      else
      {
        v15 = *this;
        fld_e26 = *(this + 26);
        *(float *)&v47 = (float)fld_e512;
        v16 = ((double (/*thiscall*/ *)(uint32_t *, int))*(uint32_t *)(v15 + 80))(this, fld_e26);
        fld_e52 = *(this + 52) - (uint64_t)(*(float *)&v47 / v16);
      }
      pThis_59 = *(uint32_t *)((char *)this + 89);
      if ( pThis_59 == 0 || pThis_59 > fld_e52 )
      {
        v18 = sub_445D00(156);
        pObj2 = v18;
        LOBYTE(v52) = 1;
        if ( v18 != 0 )
          pObj = sub_445B90(v18);
        v19 = *(uint32_t *)pObj;
        fld_e46 = *(this + 46);
        LOBYTE(v52) = 0;
        pObj2 = pObj;
        (*(void (/*thiscall*/ **)(int, int))(v19 + 68))(pObj, fld_e46);
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 20))(this, pObj);
        if ( *((uint8_t *)this + 156) != 0 )
        {
          pThis_37 = this + 55;
          pThis_372 = this + 55;
          v43 = -220 - (uint32_t)this;
          v47 = 3;
          do
          {
            v21 = *pThis_37;
            v22 = *pThis_37 == *(pThis_37 - 54);
            v45 = *(pThis_37 - 54);
            if ( !v22 )
            {
              fld_e532 = fld_e53 - *(this + 53) + 1;
              fld_e533 = v50 - *(this + 53);
              v44 = v21;
              v33 = (float)v45;
              v32 = (float)v21;
              v24 = (uint64_t)sub_4049C0(v32, v33, fld_e532, fld_e533);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
              v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);
              v26 = v43 + v25;
              pThis_37 = pThis_372;
              *(int *)((char *)pThis_372 + v26) = v24;
              fld_e53 = fld_e534;
            }
            ++pThis_37;
            v22 = v47 == 1;
            pThis_372 = pThis_37;
            --v47;
          }
          while ( !v22 );
        }
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, fld_e52);
        if ( v39 != nullptr && ((uint8_t *)Src - v39) >> 2 < (unsigned int)((v41 - (int)v39) >> 2) )
        {
          v27 = (char *)Src;
          *(uint32_t *)Src = pObj;
          Src = v27 + 4;
        }
        else
        {
          sub_490950(Src, 1, (int)&pObj2);
        }
      }
      v8 = v50;
      fld_e534 = ++fld_e53;
      fld_e512 += 1000;
    }
    while ( fld_e53 < v50 );
    v5 = v39;
  }
  *(this + 53) = v8;
  fld_e2 = *(this + 2);
  fld_e3 = *(this + 3);
  *(this + 55) = *(this + 1);
  *(this + 56) = fld_e2;
  *(this + 57) = fld_e3;
  nArg22 = nArg2;
  sub_490B30(v38);
  if ( v5 != nullptr )
    j__free(v5);
  return nArg22;
}


// ------------------------------------------------------------
// 0x4910A0 sub_4910A0
// ------------------------------------------------------------
int /*fastcall*/ sub_4910A0(int pArg1)
{
  int pArg12; // eax

  do
  {
    pArg12 = pArg1;
    pArg1 = *(uint32_t *)(pArg1 + 212);
  }
  while ( pArg1 != 0 );
  return *(uint32_t *)(pArg12 + 32);
}



// ------------------------------------------------------------
// 0x4910C0 sub_4910C0
// ------------------------------------------------------------
char /*fastcall*/ sub_4910C0(int pArg1)
{
  int pArg12; // eax

  do
  {
    pArg12 = pArg1;
    pArg1 = *(uint32_t *)(pArg1 + 212);
  }
  while ( pArg1 != 0 );
  return *(uint8_t *)(pArg12 + 169);
}



// ------------------------------------------------------------
// 0x4910E0 sub_4910E0
// ------------------------------------------------------------
char /*thiscall*/ sub_4910E0(int this)
{
  int fld_D4; // ecx
  char fld_A9; // al
  int fld_1C; // eax

  *(uint8_t *)(this + 168) = 1;
  sub_698F90(this, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_D4 = *(uint32_t *)(this + 212);
  if ( fld_D4 != 0 )
    fld_A9 = sub_4910C0(fld_D4);
  else
    fld_A9 = *(uint8_t *)(this + 169);
  if ( fld_A9 != 0 )
    return 0;
  fld_1C = *(uint32_t *)(this + 28) + sub_699000(this);  // 【clock_now(clk)】
  if ( fld_1C == *(uint32_t *)(this + 32) )
    return 0;
  *(uint32_t *)(this + 32) = fld_1C;
  return 1;
}



// ============================================================
// §C 0x491130-0x4919D0  帧渲染/图层属性族（sub_4049C0 插值、图层 +40..+56）
// ============================================================
// ------------------------------------------------------------
// 0x491130 sub_491130
// ------------------------------------------------------------
char /*cdecl*/ sub_491130(float *pArg1, float *pArg2, float *pArg3)
{
  double v4; // st7
  double v5; // st6
  double v6; // st7
  double v7; // st6
  double v8; // st7
  double v9; // st6
  float v11; // [esp+8h] [ebp+8h]
  float v12; // [esp+8h] [ebp+8h]
  float v13; // [esp+8h] [ebp+8h]

  if ( pArg1[3] == 0.0
    || pArg1[4] == 0.0
    || pArg1[5] == 0.0
    || pArg2[3] == 0.0
    || pArg2[4] == 0.0
    || pArg2[5] == 0.0
    || *pArg1 + pArg1[3] < *pArg2
    || *pArg2 + pArg2[3] < *pArg1
    || pArg1[4] + pArg1[1] < pArg2[1]
    || pArg2[4] + pArg2[1] < pArg1[1]
    || pArg1[2] + pArg1[5] < pArg2[2]
    || pArg2[2] + pArg2[5] < pArg1[2] )
  {
    return 0;
  }
  if ( pArg3 != nullptr )
  {
    if ( *pArg1 <= (double)*pArg2 )
      v4 = *pArg2;
    else
      v4 = *pArg1;
    *pArg3 = v4;
    v5 = *pArg1 + pArg1[3];
    v11 = *pArg2 + pArg2[3];
    if ( v5 >= v11 )
      v5 = v11;
    pArg3[3] = v5 - v4;
    if ( pArg1[1] <= (double)pArg2[1] )
      v6 = pArg2[1];
    else
      v6 = pArg1[1];
    pArg3[1] = v6;
    v7 = pArg1[4] + pArg1[1];
    v12 = pArg2[4] + pArg2[1];
    if ( v7 >= v12 )
      v7 = v12;
    pArg3[4] = v7 - v6;
    if ( pArg1[2] <= (double)pArg2[2] )
      v8 = pArg2[2];
    else
      v8 = pArg1[2];
    pArg3[2] = v8;
    v9 = pArg1[2] + pArg1[5];
    v13 = pArg2[2] + pArg2[5];
    if ( v9 >= v13 )
      v9 = v13;
    pArg3[5] = v9 - v8;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x491300 sub_491300 —— 帧图像绘制
//   帧(a6)：+0 句柄 /+4 路径id /+8 资源id /+12,+16 位置 /+20,+24 缩放 /+28 旋转 /+35 A通道。
//   a10 ms 内 alpha 0→帧+35 淡入（sub_4049C0）；+161 阴影分支；a8 翻转；a9 纵向缩放。
// ------------------------------------------------------------
void /*thiscall*/ sub_491300(uint8_t *this, int nArg2, int nArg3, int nArg4, float fArg5, int pArg6, int nArg7, float fArg8, float fArg9, int nArg10)
{
  int v10; // eax
  uint64_t v12; // rax
  double v13; // st7
  int v14; // edi
  int v15; // ebx
  float v16; // ecx
  double v17; // st7
  uint8_t v18; // al
  double v19; // st7
  int v20; // ebx
  double v21; // st7
  int v22; // [esp+4h] [ebp-20h]
  float v23; // [esp+8h] [ebp-1Ch]
  float v24; // [esp+8h] [ebp-1Ch]
  float v25; // [esp+Ch] [ebp-18h]
  int v26; // [esp+Ch] [ebp-18h]
  float v27; // [esp+10h] [ebp-14h]
  float v28; // [esp+10h] [ebp-14h]
  float v29; // [esp+14h] [ebp-10h]
  float v30; // [esp+14h] [ebp-10h]
  int v31; // [esp+18h] [ebp-Ch]
  float v32; // [esp+38h] [ebp+14h]
  float v33; // [esp+38h] [ebp+14h]
  float v34; // [esp+38h] [ebp+14h]
  float v35; // [esp+44h] [ebp+20h]
  float v36; // [esp+44h] [ebp+20h]

  v10 = *(uint32_t *)(pArg6 + 4);
  if ( v10 != -1 )
  {
    v31 = *(uint32_t *)(pArg6 + 8);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v10);
    *(uint32_t *)pArg6 = sub_418DD0(v31);
  }
  if ( byte_790AD0 != 0 && *(this + 161) != 0 && *(uint32_t *)pArg6 != 0 )
  {
    v25 = (float)nArg10;
    v12 = (uint64_t)sub_4049C0(0.0, v25, *(uint8_t *)(pArg6 + 35), 255);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    if ( dword_9A012C == 0 )
    {
      if ( LOBYTE(fArg5) != 0 )
      {
        v32 = *(float *)(pArg6 + 28) - fArg8;
        v35 = -*(float *)(pArg6 + 20);
      }
      else
      {
        v13 = fArg8 + *(float *)(pArg6 + 28);
        v35 = *(float *)(pArg6 + 20);
        v32 = v13;
      }
      v14 = *(uint32_t *)(pArg6 + 16);
      v15 = *(uint32_t *)(pArg6 + 12);
      v29 = (float)-v14;
      v27 = (float)-v15;
      v26 = (uint8_t)v12 << 24;
      v23 = v32;
      v16 = v35;
LABEL_21:
      *(float *)&v22 = fArg9 * *(float *)(pArg6 + 24);
      sub_424760(  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
        dword_79C0B0,
        nArg3 + v15,
        nArg4 + v14 - (uint64_t)((double)nArg7 * 0.1),
        *(uint32_t *)pArg6,
        v16,
        v22,
        v23,
        v26,
        v27,
        v29);
      return;
    }
    if ( dword_9A012C != 1 )
    {
      if ( dword_9A012C != 2 )
        return;
      if ( LOBYTE(fArg5) != 0 )
      {
        v34 = *(float *)(pArg6 + 28) - fArg8;
        v36 = -*(float *)(pArg6 + 20);
      }
      else
      {
        v21 = fArg8 + *(float *)(pArg6 + 28);
        v36 = *(float *)(pArg6 + 20);
        v34 = v21;
      }
      v14 = *(uint32_t *)(pArg6 + 16);
      v15 = *(uint32_t *)(pArg6 + 12);
      v29 = (float)-v14;
      v27 = (float)-v15;
      v26 = -16777216;
      v23 = v34;
      v16 = v36;
      goto LABEL_21;
    }
    v17 = *(float *)(pArg6 + 28);
    v18 = (v12 - 50) & (((int)v12 - 50 < 0) - 1);
    if ( LOBYTE(fArg5) != 0 )
    {
      v19 = v17 - 3.14;
      v33 = *(float *)(pArg6 + 20);
    }
    else
    {
      v19 = v17 + 3.14;
      v33 = -*(float *)(pArg6 + 20);
    }
    v20 = *(uint32_t *)(pArg6 + 12);
    v30 = (float)-*(uint32_t *)(pArg6 + 16);
    v28 = (float)-v20;
    v24 = v19;
    sub_424760(  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      dword_79C0B0,
      nArg3 + v20,
      nArg4 + *(uint32_t *)(pArg6 + 16) - (uint64_t)((double)nArg7 * -0.1),
      *(uint32_t *)pArg6,
      v33,
      *(uint32_t *)(pArg6 + 24),
      v24,
      (v18 << 24) | 0xFFFFFF,
      v28,
      v30);
  }
}


// ------------------------------------------------------------
// 0x491530 sub_491530
// ------------------------------------------------------------
int /*cdecl*/ sub_491530(int nArg1, int nArg2)
{
  int result; // eax

  result = nArg1 - 1;
  switch ( nArg1 )
  {
    case 1:
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 9);
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 5);
      break;
    case 2:
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 5);
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 2);
      break;
    case 3:
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 4);
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 6);
      break;
    case 4:
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 10);
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 1);
      break;
    case 5:
      (*(void (/*thiscall*/ **)(int, int, unsigned int))(*(uint32_t *)dword_79C0A4 + 28))(
        dword_79C0A4,
        60,
        nArg2 & 0xFF00FF00 | ((uint8_t)nArg2 << 16) | BYTE2(nArg2));
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 3);
      result = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 3);
      break;
    default:
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x491630 sub_491630
// ------------------------------------------------------------
int /*cdecl*/ sub_491630(int nArg1)
{
  int result; // eax

  result = nArg1;
  if ( nArg1 > 0 )
  {
    if ( nArg1 <= 4 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 5);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 6);
    }
    else if ( nArg1 == 5 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 1);
      return (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 4);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x491690 sub_491690
// ------------------------------------------------------------
char /*thiscall*/ sub_491690(int this, char pszArg2, int nArg3, char pszArg4, int nArg5, int nArg6, char pszArg7)
{
  char result; // al

  result = pszArg2;
  *(uint8_t *)(this + 176) = pszArg2;
  if ( pszArg2 != 0 )
  {
    *(uint32_t *)(this + 180) = nArg3;
    *(uint8_t *)(this + 184) = pszArg4;
    *(uint32_t *)(this + 188) = nArg5;
    *(uint32_t *)(this + 192) = nArg6;
    *(uint8_t *)(this + 196) = pszArg7;
    return pszArg7;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4916E0 sub_4916E0 —— 图层属性下发（帧 +40 特效/+44 参数色 → 渲染态，sub_424760 提交）
// ------------------------------------------------------------
int /*stdcall*/ sub_4916E0(int nArg1, int nArg2, int nArg3, float fArg4, int pArg5)
{
  int result; // eax
  int v6; // ecx
  float v7; // [esp+4h] [ebp-Ch]
  int v8; // [esp+8h] [ebp-8h]
  float v9; // [esp+8h] [ebp-8h]
  float v10; // [esp+24h] [ebp+14h]

  result = *(uint32_t *)(pArg5 + 4);
  if ( result != -1 )
  {
    v8 = *(uint32_t *)(pArg5 + 8);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, result);
    result = sub_418DD0(v8);
    *(uint32_t *)pArg5 = result;
  }
  if ( *(uint32_t *)pArg5 != 0 )
  {
    sub_491530(*(uint32_t *)(pArg5 + 40), *(uint32_t *)(pArg5 + 44));
    if ( LOBYTE(fArg4) != 0 )
      v10 = -*(float *)(pArg5 + 20);
    else
      v10 = *(float *)(pArg5 + 20);
    v6 = *(uint32_t *)(pArg5 + 12);
    v9 = (float)-*(uint32_t *)(pArg5 + 16);
    v7 = (float)-v6;
    sub_424760(  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      dword_79C0B0,
      nArg2 + v6,
      nArg3 + *(uint32_t *)(pArg5 + 16),
      *(uint32_t *)pArg5,
      v10,
      *(uint32_t *)(pArg5 + 24),
      *(float *)(pArg5 + 28),
      *(uint32_t *)(pArg5 + 32),
      v7,
      v9);
    return sub_491630(*(uint32_t *)(pArg5 + 40));
  }
  return result;
}



// ------------------------------------------------------------
// 0x4917A0 sub_4917A0 —— 图层属性下发·STENCIL 分支（dword_79C0A4 vtable+28/+36；RGBA 重排）
// ------------------------------------------------------------
char /*stdcall*/ sub_4917A0(int nArg1, int nArg2, int nArg3, float fArg4, int pArg5, int nArg6, char pszArg7, int nArg8, int nArg9)
{
  int v9; // eax
  int nArg62; // edi
  int v11; // ecx
  float v13; // [esp+24h] [ebp-10h]
  float v14; // [esp+28h] [ebp-Ch]
  int v15; // [esp+2Ch] [ebp-8h]
  float v16; // [esp+48h] [ebp+14h]

  v9 = *(uint32_t *)(pArg5 + 4);
  if ( v9 != -1 )
  {
    v15 = *(uint32_t *)(pArg5 + 8);
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v9);
    v9 = sub_418DD0(v15);
    *(uint32_t *)pArg5 = v9;
  }
  if ( *(uint32_t *)pArg5 != 0 )
  {
    nArg62 = nArg6;
    if ( nArg6 != 0 )
      sub_491530(nArg6, 0);
    if ( pszArg7 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, unsigned int))(*(uint32_t *)dword_79C0A4 + 28))(
        dword_79C0A4,
        60,
        nArg8 & 0xFF00FF00 | ((uint8_t)nArg8 << 16) | BYTE2(nArg8));
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 3);
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 3);
      nArg62 = nArg6;
    }
    if ( LOBYTE(fArg4) != 0 )
      v16 = -*(float *)(pArg5 + 20);
    else
      v16 = *(float *)(pArg5 + 20);
    v11 = *(uint32_t *)(pArg5 + 12);
    v14 = (float)-*(uint32_t *)(pArg5 + 16);
    v13 = (float)-v11;
    sub_424760(  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      dword_79C0B0,
      nArg2 + v11,
      nArg3 + *(uint32_t *)(pArg5 + 16),
      *(uint32_t *)pArg5,
      v16,
      *(uint32_t *)(pArg5 + 24),
      *(float *)(pArg5 + 28),
      nArg9,
      v13,
      v14);
    if ( nArg62 != 0 )
      sub_491630(nArg62);
    LOBYTE(v9) = pszArg7;
    if ( pszArg7 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 1);
      LOBYTE(v9) = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 4);
    }
  }
  return v9;
}



// ------------------------------------------------------------
// 0x4918E0 sub_4918E0
// ------------------------------------------------------------
int /*cdecl*/ sub_4918E0(int *pDwArg1, int nArg2)
{
  int v2; // eax
  uint32_t *v3; // eax
  uint64_t v4; // rax
  unsigned int v6; // [esp-4h] [ebp-8h]

  if ( pDwArg1 != nullptr && *pDwArg1 != 0 )
  {
    v2 = pDwArg1[1];
    if ( v2 != -1 )
    {
      v6 = pDwArg1[2];
      v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v2);
      *pDwArg1 = sub_418DD0(v3, v6);
    }
    LODWORD(v4) = 0;
    switch ( nArg2 )
    {
      case 0:
        LODWORD(v4) = -(pDwArg1[3] + *(uint32_t *)(*pDwArg1 + 28));
        goto LABEL_7;
      case 1:
        LODWORD(v4) = pDwArg1[3] + *(uint32_t *)(*pDwArg1 + 20) + *(uint32_t *)(*pDwArg1 + 28);
LABEL_7:
        if ( pDwArg1[5] != 1065353216 )
          return (uint64_t)((double)(int)v4 * *((float *)pDwArg1 + 5));
        return v4;
      case 2:
        LODWORD(v4) = -(pDwArg1[4] + *(uint32_t *)(*pDwArg1 + 32));
        goto LABEL_12;
      case 3:
        LODWORD(v4) = pDwArg1[4] + *(uint32_t *)(*pDwArg1 + 24) + *(uint32_t *)(*pDwArg1 + 32);
LABEL_12:
        if ( pDwArg1[6] != 1065353216 )
          v4 = (uint64_t)((double)(int)v4 * *((float *)pDwArg1 + 6));
        break;
      default:
        return v4;
    }
  }
  else
  {
    LODWORD(v4) = 0;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x4919B0 sub_4919B0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4919B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  return sub_48C4B0(uArg1, uArg2, uArg3);
}



// ============================================================
// §D 0x4919D0-0x492530  ★ 帧插值与帧时间换算（研究§11/§26）
// ============================================================
// ------------------------------------------------------------
// 0x4919D0 sub_4919D0 —— ★帧间插值核心（研究§11/§26）
//   当前帧(+148) → 下一帧：+12/+16 位置、+20/+24 缩放、+28 旋转、+32..35 RGBA 逐通道
//   sub_4049C0 线性插值，写入渲染态 +72..+92；进度 = (当前时刻-帧首+152)/(帧尾+156-帧首)。
//   帧数 = (帧数组尾+48 - 首+44)/88；尾帧且无 [LOOP](+160) 则保持当前值。
// ------------------------------------------------------------
char /*thiscall*/ sub_4919D0(int this)
{
  int fld_94; // eax
  int fld_2C; // eax
  int fld_30; // ecx
  int fld_2C2; // ecx
  int fld_2C22; // ebx
  int v7; // eax
  int fld_D4; // ecx
  int fld_20; // eax
  int fld_98; // ecx
  int fld_9C; // esi
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  uint16_t v18; // cx
  float v20; // [esp+0h] [ebp-38h]
  float v21; // [esp+0h] [ebp-38h]
  float v22; // [esp+0h] [ebp-38h]
  float v23; // [esp+0h] [ebp-38h]
  float v24; // [esp+0h] [ebp-38h]
  float v25; // [esp+0h] [ebp-38h]
  float v26; // [esp+4h] [ebp-34h]
  float v27; // [esp+4h] [ebp-34h]
  float v28; // [esp+4h] [ebp-34h]
  float v29; // [esp+4h] [ebp-34h]
  float v30; // [esp+4h] [ebp-34h]
  float v31; // [esp+4h] [ebp-34h]
  int v32; // [esp+1Ch] [ebp-1Ch]
  int v33; // [esp+20h] [ebp-18h]
  int v34; // [esp+24h] [ebp-14h]
  int v35; // [esp+30h] [ebp-8h]
  int v36; // [esp+34h] [ebp-4h]

  LOBYTE(fld_94) = *(uint8_t *)(this + 96);
  if ( (uint8_t)fld_94 != 0 )
  {
    fld_2C = *(uint32_t *)(this + 44);
    if ( fld_2C != 0 )
      fld_30 = (*(uint32_t *)(this + 48) - fld_2C) / 88;  // 帧数 = (帧数组尾+48 - 首+44)/88
    else
      fld_30 = 0;
    fld_94 = *(uint32_t *)(this + 148);  // 当前帧索引
    if ( fld_94 == fld_30 - 1 )
    {
      if ( *(uint8_t *)(this + 160) == 0 )  // 尾帧无[LOOP]则停住
        return fld_94;
      fld_2C2 = *(uint32_t *)(this + 44);
      fld_2C22 = fld_2C2;
    }
    else
    {
      fld_2C2 = *(uint32_t *)(this + 44);
      fld_2C22 = fld_2C2 + 88 * (fld_94 + 1);  // 下一帧（步长88）
    }
    v7 = fld_2C2 + 88 * fld_94;
    fld_D4 = *(uint32_t *)(this + 212);
    v36 = v7;
    if ( fld_D4 != 0 )
      fld_20 = sub_4910A0(fld_D4);
    else
      fld_20 = *(uint32_t *)(this + 32);
    fld_98 = *(uint32_t *)(this + 152);
    fld_9C = *(uint32_t *)(this + 156) - fld_98;  // 本帧跨度 = 帧尾(+156)-帧首(+152)
    v26 = (float)*(int *)(fld_2C22 + 12);
    v12 = (double)*(int *)(v36 + 12);
    v35 = fld_20 - fld_98;
    v20 = v12;
    sub_4049C0(v20, v26, fld_20 - fld_98, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(uint32_t *)(this + 72) = (uint64_t)v12;  // 渲染态：位置x
    v27 = (float)*(int *)(fld_2C22 + 16);
    v13 = (double)*(int *)(v36 + 16);
    v21 = v13;
    sub_4049C0(v21, v27, v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(uint32_t *)(this + 76) = (uint64_t)v13;
    sub_4049C0(*(float *)(v36 + 20), *(float *)(fld_2C22 + 20), v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(float *)(this + 80) = v13;
    sub_4049C0(*(float *)(v36 + 24), *(float *)(fld_2C22 + 24), v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(float *)(this + 84) = v13;
    sub_4049C0(*(float *)(v36 + 28), *(float *)(fld_2C22 + 28), v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(float *)(this + 88) = v13;
    v28 = (float)*(uint8_t *)(fld_2C22 + 32);
    v14 = (double)*(uint8_t *)(v36 + 32);
    v22 = v14;
    sub_4049C0(v22, v28, v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v32 = (uint64_t)v14;
    v29 = (float)*(uint8_t *)(fld_2C22 + 33);
    v15 = (double)*(uint8_t *)(v36 + 33);
    v23 = v15;
    sub_4049C0(v23, v29, v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v33 = (uint64_t)v15;
    v30 = (float)*(uint8_t *)(fld_2C22 + 34);
    v16 = (double)*(uint8_t *)(v36 + 34);
    v24 = v16;
    sub_4049C0(v24, v30, v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    v34 = (uint64_t)v16;
    v31 = (float)*(uint8_t *)(fld_2C22 + 35);
    v17 = (double)*(uint8_t *)(v36 + 35);
    v25 = v17;
    sub_4049C0(v25, v31, v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    HIBYTE(v18) = (uint64_t)v17;
    LOBYTE(v18) = v34;
    *(uint32_t *)(this + 92) = (uint8_t)v32 | (((uint8_t)v33 | (v18 << 8)) << 8);  // 渲染态：RGBA
    LOBYTE(fld_94) = v32;
  }
  return fld_94;
}


// ------------------------------------------------------------
// 0x491C10 sub_491C10 —— 遍历帧数组（首+44/尾+48，步长 88）
// ------------------------------------------------------------
int /*thiscall*/ sub_491C10(int this)
{
  int fld_2C; // eax
  int v2; // ebx
  int *fld_2C2; // esi
  int i; // edi

  fld_2C = *(uint32_t *)(this + 44);
  v2 = 0;
  if ( fld_2C != 0 )
    fld_2C = (*(uint32_t *)(this + 48) - fld_2C) / 88;
  if ( fld_2C > 0 )
  {
    fld_2C2 = (int *)(*(uint32_t *)(this + 44) + 48);
    for ( i = fld_2C; i != 0; --i )
    {
      v2 += (uint64_t)((double)*fld_2C2 * (1.0 / *(float *)(this + 164)) * 100.0);
      fld_2C2 += 22;
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x491C70 sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
// ------------------------------------------------------------
int /*thiscall*/ sub_491C70(int this, int nArg2)
{
  int fld_2C; // eax
  int v4; // ebx
  int v5; // edi
  int fld_2C2; // ecx
  int fld_30; // [esp+Ch] [ebp-8h]
  int fld_2C22; // [esp+10h] [ebp-4h]

  fld_2C = *(uint32_t *)(this + 44);
  v4 = 0;
  fld_2C22 = 0;
  if ( fld_2C != 0 )
    fld_30 = (*(uint32_t *)(this + 48) - fld_2C) / 88;
  else
    fld_30 = 0;
  v5 = 0;
  if ( nArg2 <= 0 )
    return 0;
  do
  {
    if ( v5 >= fld_30 )
      break;
    fld_2C2 = (uint64_t)((double)*(int *)(*(uint32_t *)(this + 44) + v4 + 48) / *(float *)(this + 164) * 100.0) + fld_2C22;  // Σ 帧+48(DELAY)×100/速率(+164)（研究§26 帧尾公式）
    ++v5;
    v4 += 88;
    fld_2C22 = fld_2C2;
  }
  while ( v5 < nArg2 );
  return fld_2C22;
}



// ------------------------------------------------------------
// 0x491D00 sub_491D00
// ------------------------------------------------------------
char /*thiscall*/ sub_491D00(int this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  uint32_t *fld_CC; // eax
  uint32_t *v7; // esi
  char result; // al

  fld_CC = *(uint32_t **)(this + 204);
  v7 = (uint32_t *)*fld_CC;
  if ( (uint32_t *)*fld_CC != fld_CC )
  {
    do
    {
      if ( (int)v7[2] >= 0 )
        break;
      sub_491D00(nArg2, nArg3, nArg4, fArg5);
      v7 = (uint32_t *)*v7;
    }
    while ( v7 != *(uint32_t **)(this + 204) );
  }
  sub_4916E0(nArg2, nArg3, nArg4, fArg5, this + 60);
  result = *(uint8_t *)(this + 176);
  if ( result != 0 )
  {
    sub_4917A0(
      nArg2,
      nArg3,
      nArg4,
      fArg5,
      this + 60,
      *(uint32_t *)(this + 180),
      *(uint8_t *)(this + 184),
      *(uint32_t *)(this + 188),
      *(uint32_t *)(this + 192));
    result = *(uint8_t *)(this + 196);
    if ( result != 0 )
      *(uint8_t *)(this + 176) = 0;
  }
  for ( ; v7 != *(uint32_t **)(this + 204); v7 = (uint32_t *)*v7 )
    result = sub_491D00(nArg2, nArg3, nArg4, fArg5);
  return result;
}



// ------------------------------------------------------------
// 0x491DE0 sub_491DE0
// ------------------------------------------------------------
char /*thiscall*/ sub_491DE0(uint32_t *this, int nArg2, int nArg3, int nArg4, float fArg5, int nArg6, char pszArg7, int nArg8, int nArg9)
{
  uint32_t *fld_e51; // eax
  uint32_t *v11; // esi
  char result; // al

  fld_e51 = (uint32_t *)*(this + 51);
  v11 = (uint32_t *)*fld_e51;
  if ( (uint32_t *)*fld_e51 != fld_e51 )
  {
    do
    {
      if ( (int)v11[2] >= 0 )
        break;
      sub_491DE0(nArg2, nArg3, nArg4, fArg5, nArg6, pszArg7, nArg8, nArg9);
      v11 = (uint32_t *)*v11;
    }
    while ( v11 != (uint32_t *)*(this + 51) );
  }
  for ( result = sub_4917A0(nArg2, nArg3, nArg4, fArg5, (int)(this + 15), nArg6, pszArg7, nArg8, nArg9);
        v11 != (uint32_t *)*(this + 51);
        v11 = (uint32_t *)*v11 )
  {
    result = sub_491DE0(nArg2, nArg3, nArg4, fArg5, nArg6, pszArg7, nArg8, nArg9);
  }
  return result;
}



// ------------------------------------------------------------
// 0x491EA0 sub_491EA0
// ------------------------------------------------------------
void /*thiscall*/ sub_491EA0(int this, int nArg2, int nArg3, int nArg4, float fArg5, int nArg6, float fArg7, float fArg8, int nArg9)
{
  uint32_t *fld_CC; // eax
  uint32_t *v11; // esi

  if ( byte_790AD0 != 0 && *(uint8_t *)(this + 161) != 0 )
  {
    fld_CC = *(uint32_t **)(this + 204);
    v11 = (uint32_t *)*fld_CC;
    if ( (uint32_t *)*fld_CC != fld_CC )
    {
      do
      {
        if ( (int)v11[2] >= 0 )
          break;
        sub_491EA0(nArg2, nArg3, nArg4, fArg5, nArg6, fArg7, fArg8, nArg9);
        v11 = (uint32_t *)*v11;
      }
      while ( v11 != *(uint32_t **)(this + 204) );
    }
    sub_491300((uint8_t *)this, nArg2, nArg3, nArg4, fArg5, this + 60, nArg6, fArg7, fArg8, nArg9);
    for ( ; v11 != *(uint32_t **)(this + 204); v11 = (uint32_t *)*v11 )
      sub_491EA0(nArg2, nArg3, nArg4, fArg5, nArg6, fArg7, fArg8, nArg9);
  }
}



// ------------------------------------------------------------
// 0x491F80 sub_491F80 —— RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
// ------------------------------------------------------------
char /*thiscall*/ sub_491F80(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int fld_5C; // ebx
  uint32_t **fld_CC; // eax
  uint16_t v9; // cx
  uint32_t *v10; // esi

  fld_5C = nArg2;
  LOBYTE(fld_CC) = -1;
  if ( nArg2 == -1 )
  {
    if ( nArg3 == -1 && nArg4 == -1 && nArg5 == -1 )
      return (char)fld_CC;
    fld_5C = *(uint8_t *)(this + 92);
  }
  if ( nArg3 == -1 )
    nArg3 = *(uint8_t *)(this + 93);
  if ( nArg4 == -1 )
    nArg4 = *(uint8_t *)(this + 94);
  if ( nArg5 == -1 )
    nArg5 = *(uint8_t *)(this + 95);
  HIBYTE(v9) = nArg5;
  LOBYTE(v9) = nArg4;
  LOBYTE(fld_CC) = nArg6;
  *(uint32_t *)(this + 92) = (uint8_t)fld_5C | (((uint8_t)nArg3 | (v9 << 8)) << 8);
  if ( (uint8_t)nArg6 != 0 )
  {
    fld_CC = *(uint32_t ***)(this + 204);
    v10 = *fld_CC;
    if ( *fld_CC != fld_CC )
    {
      do
      {
        LOBYTE(fld_CC) = sub_491F80(fld_5C, nArg3, nArg4, nArg5, nArg6);
        v10 = (uint32_t *)*v10;
      }
      while ( v10 != *(uint32_t **)(this + 204) );
    }
  }
  return (char)fld_CC;
}



// ------------------------------------------------------------
// 0x492030 sub_492030
// ------------------------------------------------------------
char /*thiscall*/ sub_492030(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  uint32_t **fld_e51; // eax
  uint32_t *v6; // esi

  *(this + 26) = nArg3;
  LOBYTE(fld_e51) = nArg4;
  *(this + 25) = nArg2;
  if ( (uint8_t)nArg4 != 0 )
  {
    fld_e51 = (uint32_t **)*(this + 51);
    v6 = *fld_e51;
    if ( *fld_e51 != fld_e51 )
    {
      do
      {
        LOBYTE(fld_e51) = sub_492030(nArg2, nArg3, nArg4);
        v6 = (uint32_t *)*v6;
      }
      while ( v6 != (uint32_t *)*(this + 51) );
    }
  }
  return (char)fld_e51;
}



// ------------------------------------------------------------
// 0x492080 sub_492080
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_492080(int this, float fArg2)
{
  double fld_AC; // st7
  uint32_t *result; // eax
  uint32_t *v5; // esi

  if ( *(float *)(this + 172) != fArg2 )
  {
    fld_AC = fArg2 - *(float *)(this + 172);
    *(float *)(this + 172) = fArg2;
    *(float *)(this + 88) = fld_AC + *(float *)(this + 88);
  }
  result = *(uint32_t **)(this + 204);
  v5 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_492080(fArg2);
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != *(uint32_t **)(this + 204) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4920E0 sub_4920E0 —— ★批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4920E0(uint32_t *this, float fArg2, float fArg3)
{
  int fld_e11; // eax
  int fld_e12; // ecx
  int v6; // edi
  int v7; // eax
  unsigned int v8; // edx
  int v9; // eax
  int v10; // ecx
  uint32_t *result; // eax
  uint32_t *v12; // edi

  fld_e11 = *(this + 11);
  if ( fld_e11 != 0 )
    fld_e12 = (*(this + 12) - fld_e11) / 88;
  else
    fld_e12 = 0;
  v6 = 0;
  if ( fld_e12 >= 4 )
  {
    v7 = 0;
    v8 = ((unsigned int)(fld_e12 - 4) >> 2) + 1;
    v6 = 4 * v8;
    do
    {
      *(float *)(*(this + 11) + v7 + 20) = fArg2;  // 帧+20 缩放x（sub_4920E0 批量改写，研究§11）
      v7 += 352;
      --v8;
      *(float *)(*(this + 11) + v7 - 328) = fArg3;  // 帧+24 缩放y（展开循环）
      *(float *)(*(this + 11) + v7 - 244) = fArg2;
      *(float *)(*(this + 11) + v7 - 240) = fArg3;
      *(float *)(*(this + 11) + v7 - 156) = fArg2;
      *(float *)(*(this + 11) + v7 - 152) = fArg3;
      *(float *)(*(this + 11) + v7 - 68) = fArg2;
      *(float *)(*(this + 11) + v7 - 64) = fArg3;
    }
    while ( v8 != 0 );
  }
  if ( v6 < fld_e12 )
  {
    v9 = 88 * v6;
    v10 = fld_e12 - v6;
    do
    {
      *(float *)(*(this + 11) + v9 + 20) = fArg2;
      v9 += 88;
      --v10;
      *(float *)(*(this + 11) + v9 - 64) = fArg3;
    }
    while ( v10 != 0 );
  }
  result = (uint32_t *)*(this + 51);
  v12 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_4920E0(fArg2, fArg3);
      v12 = (uint32_t *)*v12;
    }
    while ( v12 != (uint32_t *)*(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4921E0 sub_4921E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4921E0(int *this, float fArg2)
{
  int fld_e11; // eax
  int fld_e112; // ecx
  int v5; // edx
  int i; // edi
  int v7; // eax
  int j; // eax
  uint32_t *result; // eax
  uint32_t *v10; // edi

  fld_e11 = *(this + 11);
  if ( fld_e11 != 0 )
    fld_e11 = (*(this + 12) - fld_e11) / 88;
  if ( fld_e11 > 0 )
  {
    fld_e112 = *(this + 11);
    v5 = 0;
    for ( i = fld_e11; i != 0; --i )
    {
      v7 = *(uint32_t *)(v5 + fld_e112 + 60);
      if ( v7 != *(uint32_t *)(v5 + fld_e112 + 64) )
      {
        do
        {
          v7 += 24;
          *(float *)(v7 - 24) = fArg2 * *(float *)(v7 - 24);
          *(float *)(v7 - 20) = fArg2 * *(float *)(v7 - 20);
          *(float *)(v7 - 16) = fArg2 * *(float *)(v7 - 16);
          *(float *)(v7 - 12) = fArg2 * *(float *)(v7 - 12);
          *(float *)(v7 - 8) = fArg2 * *(float *)(v7 - 8);
          *(float *)(v7 - 4) = fArg2 * *(float *)(v7 - 4);
        }
        while ( v7 != *(uint32_t *)(*(this + 11) + v5 + 64) );
      }
      fld_e112 = *(this + 11);
      for ( j = *(uint32_t *)(v5 + fld_e112 + 76); j != *(uint32_t *)(v5 + fld_e112 + 80); fld_e112 = *(this + 11) )
      {
        j += 24;
        *(float *)(j - 24) = fArg2 * *(float *)(j - 24);
        *(float *)(j - 20) = fArg2 * *(float *)(j - 20);
        *(float *)(j - 16) = fArg2 * *(float *)(j - 16);
        *(float *)(j - 12) = fArg2 * *(float *)(j - 12);
        *(float *)(j - 8) = fArg2 * *(float *)(j - 8);
        *(float *)(j - 4) = fArg2 * *(float *)(j - 4);
      }
      v5 += 88;
    }
  }
  result = (uint32_t *)*(this + 51);
  v10 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_4921E0(fArg2);
      v10 = (uint32_t *)*v10;
    }
    while ( v10 != (uint32_t *)*(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4922F0 sub_4922F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4922F0(uint32_t *this, float fArg2)
{
  int fld_e11; // edx
  int i; // ecx
  int j; // eax
  int k; // eax

  fld_e11 = *(this + 11);
  for ( i = *(this + 12); fld_e11 != i; fld_e11 += 88 )
  {
    *(float *)(fld_e11 + 20) = fArg2 * *(float *)(fld_e11 + 20);
    *(float *)(fld_e11 + 24) = fArg2 * *(float *)(fld_e11 + 24);
    for ( j = *(uint32_t *)(fld_e11 + 60); j != *(uint32_t *)(fld_e11 + 64); *(float *)(j - 4) = fArg2 * *(float *)(j - 4) )
    {
      j += 24;
      *(float *)(j - 24) = fArg2 * *(float *)(j - 24);
      *(float *)(j - 20) = fArg2 * *(float *)(j - 20);
      *(float *)(j - 16) = fArg2 * *(float *)(j - 16);
      *(float *)(j - 12) = fArg2 * *(float *)(j - 12);
      *(float *)(j - 8) = fArg2 * *(float *)(j - 8);
    }
    for ( k = *(uint32_t *)(fld_e11 + 76); k != *(uint32_t *)(fld_e11 + 80); *(float *)(k - 4) = fArg2 * *(float *)(k - 4) )
    {
      k += 24;
      *(float *)(k - 24) = fArg2 * *(float *)(k - 24);
      *(float *)(k - 20) = fArg2 * *(float *)(k - 20);
      *(float *)(k - 16) = fArg2 * *(float *)(k - 16);
      *(float *)(k - 12) = fArg2 * *(float *)(k - 12);
      *(float *)(k - 8) = fArg2 * *(float *)(k - 8);
    }
  }
}



// ------------------------------------------------------------
// 0x4923C0 sub_4923C0 —— 全帧缩放统一设值（+20/+24）
// ------------------------------------------------------------
int /*thiscall*/ sub_4923C0(uint32_t *this, int nArg2)
{
  int result; // eax
  int i; // ecx

  result = *(this + 11);
  for ( i = *(this + 12); result != i; result += 88 )
  {
    *(uint32_t *)(result + 20) = nArg2;
    *(uint32_t *)(result + 24) = nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4923F0 sub_4923F0
// ------------------------------------------------------------
void /*thiscall*/ sub_4923F0(uint32_t *this, float fArg2)
{
  int fld_e11; // edx
  int fld_e12; // ecx
  double v4; // st7
  int i; // eax
  int j; // eax

  fld_e11 = *(this + 11);
  fld_e12 = *(this + 12);
  if ( fld_e11 != fld_e12 )
  {
    v4 = 1.0 / fArg2;
    do
    {
      *(float *)(fld_e11 + 20) = v4 * *(float *)(fld_e11 + 20);
      *(float *)(fld_e11 + 24) = v4 * *(float *)(fld_e11 + 24);
      for ( i = *(uint32_t *)(fld_e11 + 60); i != *(uint32_t *)(fld_e11 + 64); *(float *)(i - 4) = v4 * *(float *)(i - 4) )
      {
        i += 24;
        *(float *)(i - 24) = v4 * *(float *)(i - 24);
        *(float *)(i - 20) = v4 * *(float *)(i - 20);
        *(float *)(i - 16) = v4 * *(float *)(i - 16);
        *(float *)(i - 12) = v4 * *(float *)(i - 12);
        *(float *)(i - 8) = v4 * *(float *)(i - 8);
      }
      for ( j = *(uint32_t *)(fld_e11 + 76); j != *(uint32_t *)(fld_e11 + 80); *(float *)(j - 4) = v4 * *(float *)(j - 4) )
      {
        j += 24;
        *(float *)(j - 24) = v4 * *(float *)(j - 24);
        *(float *)(j - 20) = v4 * *(float *)(j - 20);
        *(float *)(j - 16) = v4 * *(float *)(j - 16);
        *(float *)(j - 12) = v4 * *(float *)(j - 12);
        *(float *)(j - 8) = v4 * *(float *)(j - 8);
      }
      fld_e11 += 88;
    }
    while ( fld_e11 != fld_e12 );
  }
}



// ------------------------------------------------------------
// 0x4924C0 sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4924C0(int *this, int nArg2)
{
  int fld_e11; // eax
  int *fld_e112; // ebx
  int v5; // eax
  uint32_t *v6; // eax
  unsigned int v8; // [esp-8h] [ebp-10h]

  fld_e11 = *(this + 11);
  if ( fld_e11 != 0 )
    fld_e11 = (*(this + 12) - fld_e11) / 88;
  if ( nArg2 >= fld_e11 )
    return 0;
  fld_e112 = (int *)(*(this + 11) + 88 * nArg2);
  v5 = fld_e112[1];
  if ( v5 != -1 )
  {
    v8 = fld_e112[2];
    v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v5);
    *fld_e112 = sub_418DD0(v6, v8);
  }
  return 88 * nArg2 + *(this + 11);
}



// ============================================================
// §E 0x492530-0x493400  攻击盒/受击盒容器族（元素 24B = 6×float）
// ============================================================
// ------------------------------------------------------------
// 0x492530 sub_492530
// ------------------------------------------------------------
int /*stdcall*/ sub_492530(int nArg1, int nArg2, int nArg3)
{
  return sub_4FF050(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x492550 sub_492550
// ------------------------------------------------------------
char /*thiscall*/ sub_492550(int this, int nArg2, int nArg3, int nArg4, float fArg5, int nArg6)
{
  uint32_t *fld_CC; // eax
  uint32_t *v9; // edi
  int fld_2C; // eax
  int v11; // eax
  int fld_2C2; // edx
  uint32_t *v13; // eax
  int fld_2C3; // ecx
  char result; // al
  int v16; // eax
  int fld_B4; // [esp-10h] [ebp-20h]
  char fld_B8; // [esp-Ch] [ebp-1Ch]
  int fld_BC; // [esp-8h] [ebp-18h]
  unsigned int v20; // [esp-4h] [ebp-14h]
  int fld_C0; // [esp-4h] [ebp-14h]
  int *v22; // [esp+20h] [ebp+10h]

  fld_CC = *(uint32_t **)(this + 204);
  v9 = (uint32_t *)*fld_CC;
  if ( (uint32_t *)*fld_CC != fld_CC )
  {
    do
    {
      if ( (int)v9[2] >= 0 )
        break;
      sub_492550(nArg2, nArg3, nArg4, fArg5, nArg6);
      v9 = (uint32_t *)*v9;
    }
    while ( v9 != *(uint32_t **)(this + 204) );
  }
  fld_2C = *(uint32_t *)(this + 44);
  if ( fld_2C != 0 )
    fld_2C = (*(uint32_t *)(this + 48) - fld_2C) / 88;
  if ( nArg6 >= fld_2C )
  {
    fld_2C3 = 0;
  }
  else
  {
    v11 = 88 * nArg6;
    fld_2C2 = 88 * nArg6 + *(uint32_t *)(this + 44);
    v22 = (int *)fld_2C2;
    if ( *(uint32_t *)(fld_2C2 + 4) != -1 )
    {
      v20 = *(uint32_t *)(fld_2C2 + 8);
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F84BC + 56))(
                        dword_8F84BC,
                        *(uint32_t *)(fld_2C2 + 4));
      *v22 = sub_418DD0(v13, v20);
      v11 = 88 * nArg6;
    }
    fld_2C3 = v11 + *(uint32_t *)(this + 44);
  }
  sub_4916E0(nArg2, nArg3, nArg4, fArg5, fld_2C3);
  result = *(uint8_t *)(this + 176);
  if ( result != 0 )
  {
    fld_C0 = *(uint32_t *)(this + 192);
    fld_BC = *(uint32_t *)(this + 188);
    fld_B8 = *(uint8_t *)(this + 184);
    fld_B4 = *(uint32_t *)(this + 180);
    v16 = sub_4924C0((int *)this, nArg6);
    sub_4917A0(nArg2, nArg3, nArg4, fArg5, v16, fld_B4, fld_B8, fld_BC, fld_C0);
    result = *(uint8_t *)(this + 196);
    if ( result != 0 )
      *(uint8_t *)(this + 176) = 0;
  }
  for ( ; v9 != *(uint32_t **)(this + 204); v9 = (uint32_t *)*v9 )
    result = sub_492550(nArg2, nArg3, nArg4, fArg5, nArg6);
  return result;
}



// ------------------------------------------------------------
// 0x4926A0 sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
// ------------------------------------------------------------
int /*thiscall*/ sub_4926A0(int this)
{
  int v2; // ebx
  uint32_t *fld_CC; // eax
  uint32_t *v4; // edi
  int i; // edi
  int result; // eax

  v2 = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint8_t *)(this + 14) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint8_t *)(this + 168) = 0;
  *(uint8_t *)(this + 169) = 0;
  *(uint8_t *)(this + 170) = 0;
  sub_430B70(this + 60);
  fld_CC = *(uint32_t **)(this + 204);
  *(uint32_t *)(this + 148) = -1;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  v4 = (uint32_t *)*fld_CC;
  if ( (uint32_t *)*fld_CC != fld_CC )
  {
    do
    {
      sub_4926A0(v4[3]);
      v4 = (uint32_t *)*v4;
    }
    while ( v4 != *(uint32_t **)(this + 204) );
  }
  *(uint32_t *)(this + 36) = 0;
  for ( i = 0; ; i += 88 )
  {
    result = *(uint32_t *)(this + 44);
    if ( result != 0 )
      result = (*(uint32_t *)(this + 48) - result) / 88;
    if ( v2 >= result )
      break;
    ++v2;
    *(uint32_t *)(this + 36) += *(uint32_t *)(i + *(uint32_t *)(this + 44) + 48);
  }
  return result;
}



// ------------------------------------------------------------
// 0x492750 sub_492750
// ------------------------------------------------------------
int /*thiscall*/ sub_492750(int this, size_t *pArg2, uint32_t *uArg3)
{
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
  sub_4014D0((size_t *)this, pArg2, 0, 0xFFFFFFFF);
  *(uint32_t *)(this + 28) = *uArg3;
  return this;
}



// ------------------------------------------------------------
// 0x492780 sub_492780
// ------------------------------------------------------------
int /*thiscall*/ sub_492780(uint32_t *this, unsigned int uArg2)
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
  if ( 0x1FFFFFFF - fld_e2 < uArg2 )
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
// 0x492810 sub_492810
// ------------------------------------------------------------
void /*noreturn*/ sub_492810()
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
// 0x492880 sub_492880
// ------------------------------------------------------------
size_t */*cdecl*/ sub_492880(size_t *pArg1, size_t *pArg2, size_t *pArg3)
{
  size_t *pArg22; // esi
  size_t *pArg32; // edi

  pArg22 = pArg2;
  if ( pArg1 == pArg2 )
    return pArg3;
  pArg32 = pArg3;
  do
  {
    pArg22 -= 8;
    pArg32 -= 8;
    sub_4014D0(pArg32, pArg22, 0, 0xFFFFFFFF);
    pArg32[7] = pArg22[7];
  }
  while ( pArg22 != pArg1 );
  return pArg32;
}



// ------------------------------------------------------------
// 0x4928C0 sub_4928C0
// ------------------------------------------------------------
int /*cdecl*/ sub_4928C0(size_t *pArg1, size_t *pArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != pArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)(nArg32 + 24) = 15;
      *(uint32_t *)(nArg32 + 20) = 0;
      *(uint8_t *)(nArg32 + 4) = 0;
      sub_4014D0((size_t *)nArg32, pArg1, 0, 0xFFFFFFFF);
      *(uint32_t *)(nArg32 + 28) = pArg1[7];
    }
    nArg32 += 32;
    LOBYTE(v7) = 0;
    pArg1 += 8;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x492980 sub_492980
// ------------------------------------------------------------
void **/*thiscall*/ sub_492980(void ***this, void *pArg2)
{
  void **fld_e51; // ecx
  void **result; // eax
  uint32_t *v5; // ecx

  fld_e51 = *(this + 51);
  result = (void **)*fld_e51;
  if ( *fld_e51 != fld_e51 )
  {
    while ( result[3] != pArg2 )
    {
      result = (void **)*result;
      if ( result == fld_e51 )
        return result;
    }
    v5 = result[3];
    if ( v5 != nullptr )
      v5[53] = 0;
    if ( result != *(this + 51) )
    {
      *(uint32_t *)result[1] = *result;
      *((uint32_t *)*result + 1) = result[1];
      j__free(result);
      result = (void **)((char *)*(this + 52) - 1);
      *(this + 52) = result;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4929F0 sub_4929F0 —— 盒 vector 插入（元素 24B = 6×float）
// ------------------------------------------------------------
int /*thiscall*/ sub_4929F0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)
{
  int result; // eax
  int v6; // edx
  int fld_e1; // ebx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v16; // ecx
  int fld_e27; // eax
  int v18; // ebx
  int fld_e13; // eax
  unsigned int v20; // edi
  void *fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-4Ch]
  int fld_e25; // [esp-Ch] [ebp-40h]
  unsigned int fld_e24; // [esp-8h] [ebp-3Ch]
  int v27; // [esp+0h] [ebp-34h] BYREF
  uint32_t v28[7]; // [esp+Ch] [ebp-28h] BYREF
  int v29; // [esp+30h] [ebp-4h]
  int v30; // [esp+3Ch] [ebp+8h]
  int v31; // [esp+40h] [ebp+Ch]
  char *Blocka; // [esp+44h] [ebp+10h]
  void *Blockb; // [esp+44h] [ebp+10h]

  result = (int)Block;
  v6 = Block[1];
  fld_e1 = *(this + 1);
  v28[0] = *Block;
  v8 = Block[2];
  v28[1] = v6;
  v9 = Block[3];
  v28[2] = v8;
  v10 = Block[4];
  v28[3] = v9;
  v11 = Block[5];
  v28[6] = &v27;
  v28[4] = v10;
  v28[5] = v11;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 24;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 24;
    else
      fld_e2 = 0;
    if ( 178956970 - fld_e2 < uArg3 )
      sub_430A90(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 24;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 24 >= uArg3 )
      {
        v30 = (int)fld_e23 - 24 * uArg3;
        *(this + 2) = sub_4FF050(v30, fld_e23, fld_e23);
        sub_504430(pArg2, v30, Blockb);
        return sub_4FEF50(pArg2, pArg2 + 24 * uArg3, v28);
      }
      else
      {
        sub_4FF050(pArg2, fld_e23, pArg2 + 24 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 24;
        fld_e25 = *(this + 2);
        v29 = 2;
        sub_504620(fld_e25, fld_e24, v28);
        fld_e26 = 24 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return sub_4FEF50(pArg2, fld_e26 - 24 * uArg3, v28);
      }
    }
    else
    {
      if ( 178956970 - (fld_e3 >> 1) >= fld_e3 )
        v16 = (fld_e3 >> 1) + fld_e3;
      else
        v16 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 24;
      else
        fld_e27 = 0;
      if ( v16 < uArg3 + fld_e27 )
        v16 = uArg3 + sub_4FEF30(this);
      v18 = 24 * v16;
      Blocka = (char *)operator new(24 * v16);
      fld_e12 = *(this + 1);
      v29 = 0;
      v31 = sub_4FF050(fld_e12, pArg2, Blocka);
      sub_5044B0(v31, uArg3, v28);
      sub_4FF050(pArg2, *(this + 2), v31 + 24 * uArg3);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 24;
      v20 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v18];
      *(this + 2) = (int)&Blocka[24 * v20];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x492CC0 sub_492CC0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_492CC0(uint32_t *this, int pArg2)
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )
    v2 = (*(uint32_t *)(pArg2 + 8) - v2) / 24;
  if ( (uint8_t)sub_430BE0(v2) != 0 )
  {
    fld_e1 = *(this + 1);
    v6 = *(uint32_t *)(pArg2 + 8);
    v5 = *(uint32_t *)(pArg2 + 4);
    v11 = 0;
    *(this + 2) = sub_4FF050(v5, v6, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x492D60 sub_492D60
// ------------------------------------------------------------
size_t /*cdecl*/ sub_492D60(size_t *pArg1, size_t *pArg2, size_t *pArg3)
{
  size_t *i; // esi
  size_t result; // eax

  for ( i = pArg1; i != pArg2; i += 8 )
  {
    sub_4014D0(i, pArg3, 0, 0xFFFFFFFF);
    result = pArg3[7];
    i[7] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x492DA0 sub_492DA0
// ------------------------------------------------------------
size_t */*cdecl*/ sub_492DA0(size_t *pArg1, size_t *pArg2, size_t *pArg3)
{
  return sub_492880(pArg1, pArg2, pArg3);
}



// ------------------------------------------------------------
// 0x492DC0 sub_492DC0
// ------------------------------------------------------------
size_t /*cdecl*/ sub_492DC0(int nArg1, int nArg2, size_t *pArg3)
{
  int nArg12; // esi
  size_t result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v5[5] = v5;
  v5[4] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )
  {
    v5[3] = nArg12;
    LOBYTE(v6) = 1;
    if ( nArg12 != 0 )
    {
      *(uint32_t *)(nArg12 + 24) = 15;
      *(uint32_t *)(nArg12 + 20) = 0;
      *(uint8_t *)(nArg12 + 4) = 0;
      sub_4014D0((size_t *)nArg12, pArg3, 0, 0xFFFFFFFF);
      result = pArg3[7];
      *(uint32_t *)(nArg12 + 28) = result;
    }
    nArg12 += 32;
    LOBYTE(v6) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x492E80 sub_492E80
// ------------------------------------------------------------
int /*thiscall*/ sub_492E80(int this, int pArg2)
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *fld_4; // edi
  unsigned int fld_8; // eax
  int v9; // eax
  unsigned int fld_C; // eax
  int v11; // eax
  uint32_t *v12; // [esp+10h] [ebp+8h]

  if ( this == pArg2 )
    return this;
  v4 = *(uint32_t *)(pArg2 + 4);
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 24) == 0 )
  {
    if ( *(uint32_t *)(this + 4) != 0 )
      j__free(*(void **)(this + 4));
    *(uint32_t *)(this + 4) = 0;
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 0;
    return this;
  }
  fld_4 = *(uint32_t **)(this + 4);
  if ( fld_4 != nullptr )
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 24;
  else
    fld_8 = 0;
  if ( v5 > fld_8 )
  {
    if ( fld_4 != nullptr )
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 24;
    else
      fld_C = 0;
    if ( v5 <= fld_C )
    {
      v12 = (uint32_t *)(*(uint32_t *)(pArg2 + 4) + 24 * sub_4FEF30(this));
      sub_4919B0(*(uint32_t **)(pArg2 + 4), v12, fld_4);
      *(uint32_t *)(this + 8) = sub_4FF050(v12, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8));
      return this;
    }
    if ( fld_4 != nullptr )
      j__free(*(void **)(this + 4));
    v11 = sub_4FEF30(pArg2);
    if ( (uint8_t)sub_430BE0(v11) != 0 )
      *(uint32_t *)(this + 8) = sub_492530(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  sub_48C4B0(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), fld_4);
  v9 = *(uint32_t *)(pArg2 + 4);
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 24 * ((*(uint32_t *)(pArg2 + 8) - v9) / 24);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x493000 sub_493000
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493000(int *this, uint32_t *uArg2, int nArg3, uint32_t *Block)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )
    v6 = (nArg3 - fld_e1) / 24;
  else
    v6 = 0;
  sub_4929F0(this, nArg3, 1u, Block);
  *uArg2 = *(this + 1) + 24 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x493070 sub_493070 —— ★88 字节帧拷贝构造（全字段 +0..+87；+56..71 攻击盒/+72..87 受击盒 vector 深拷贝）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493070(uint32_t *this, int pArg2)
{
  *this = *(uint32_t *)pArg2;
  *(this + 1) = *(uint32_t *)(pArg2 + 4);
  *(this + 2) = *(uint32_t *)(pArg2 + 8);
  *(this + 3) = *(uint32_t *)(pArg2 + 12);
  *(this + 4) = *(uint32_t *)(pArg2 + 16);
  *(this + 5) = *(uint32_t *)(pArg2 + 20);
  *(this + 6) = *(uint32_t *)(pArg2 + 24);
  *(this + 7) = *(uint32_t *)(pArg2 + 28);
  *(this + 8) = *(uint32_t *)(pArg2 + 32);
  *((uint8_t *)this + 36) = *(uint8_t *)(pArg2 + 36);
  *(this + 10) = *(uint32_t *)(pArg2 + 40);
  *(this + 11) = *(uint32_t *)(pArg2 + 44);
  *(this + 12) = *(uint32_t *)(pArg2 + 48);  // +48 DELAY
  *(this + 13) = *(uint32_t *)(pArg2 + 52);  // +52 DAMAGE TYPE
  sub_492CC0(this + 14, pArg2 + 56);  // +56..71 攻击盒vector 深拷贝
  sub_492CC0(this + 18, pArg2 + 72);  // +72..87 受击盒vector 深拷贝
  return this;
}



// ------------------------------------------------------------
// 0x493120 sub_493120 —— ★88 字节帧拷贝·析构变体（+56/+72 盒 vector 先 sub_492E80 析构再覆盖）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493120(uint32_t *this, int pArg2)
{
  *this = *(uint32_t *)pArg2;
  *(this + 1) = *(uint32_t *)(pArg2 + 4);
  *(this + 2) = *(uint32_t *)(pArg2 + 8);
  *(this + 3) = *(uint32_t *)(pArg2 + 12);
  *(this + 4) = *(uint32_t *)(pArg2 + 16);
  *(this + 5) = *(uint32_t *)(pArg2 + 20);
  *(this + 6) = *(uint32_t *)(pArg2 + 24);
  *(this + 7) = *(uint32_t *)(pArg2 + 28);
  *(this + 8) = *(uint32_t *)(pArg2 + 32);
  *((uint8_t *)this + 36) = *(uint8_t *)(pArg2 + 36);
  *(this + 10) = *(uint32_t *)(pArg2 + 40);
  *(this + 11) = *(uint32_t *)(pArg2 + 44);
  *(this + 12) = *(uint32_t *)(pArg2 + 48);  // +48 DELAY
  *(this + 13) = *(uint32_t *)(pArg2 + 52);  // +52 DAMAGE TYPE
  sub_492E80(pArg2 + 56);  // +56..71 攻击盒vector 析构
  sub_492E80(pArg2 + 72);  // +72..87 受击盒vector 析构
  return this;
}



// ------------------------------------------------------------
// 0x4931A0 sub_4931A0 —— 盒 vector 追加一组（6 float=24B；容量不足走 sub_493000 扩容）
// ------------------------------------------------------------
int /*thiscall*/ sub_4931A0(int *this, void *Block)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 24;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 24 )
    return sub_493000((int)&Block, *(this + 2), Block);
  fld_e22 = *(this + 2);
  result = sub_5044B0(fld_e22, 1, Block);
  *(this + 2) = fld_e22 + 24;
  return result;
}



// ------------------------------------------------------------
// 0x493230 sub_493230
// ------------------------------------------------------------
int /*stdcall*/ sub_493230(int nArg1, int nArg2, size_t *pArg3)
{
  sub_492DC0(nArg1, nArg2, pArg3);
  return nArg1 + 32 * nArg2;
}



// ------------------------------------------------------------
// 0x493260 sub_493260
// ------------------------------------------------------------
void /*stdcall*/ sub_493260(char *pszArg1, char *pszArg2)
{
  char *i; // esi

  for ( i = pszArg1; i != pszArg2; i += 32 )
    sub_501490(i);
}



// ------------------------------------------------------------
// 0x493290 sub_493290
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493290(uint32_t *uArg1, uint32_t *uArg2, int nArg3)
{
  uint32_t *i; // esi
  uint32_t *result; // eax

  for ( i = uArg1; i != uArg2; i += 22 )
    result = sub_493120(i, nArg3);
  return result;
}



// ------------------------------------------------------------
// 0x4932C0 sub_4932C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4932C0(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg12; // esi
  uint32_t *uArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    sub_493120(uArg32, nArg12);
    nArg12 += 88;
    uArg32 += 22;
  }
  while ( nArg12 != nArg2 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x493300 sub_493300
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493300(int nArg1, int nArg2, uint32_t *uArg3)
{
  int nArg22; // esi
  uint32_t *uArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return uArg3;
  uArg32 = uArg3;
  do
  {
    nArg22 -= 88;
    uArg32 -= 22;
    sub_493120(uArg32, nArg22);
  }
  while ( nArg22 != nArg1 );
  return uArg32;
}



// ------------------------------------------------------------
// 0x493340 sub_493340
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493340(int nArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // esi
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
      sub_493070(uArg32, nArg1);
    uArg32 += 22;
    LOBYTE(v7) = 0;
    nArg1 += 88;
  }
  return uArg32;
}



// ============================================================
// §F 0x493400-0x493DB0  ★ 帧数组容器(88B/帧) + 帧推进/变速引擎
// ============================================================
// ------------------------------------------------------------
// 0x493400 sub_493400 —— 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
// ------------------------------------------------------------
void /*thiscall*/ sub_493400(int this, int nArg2)
{
  int fld_2C; // eax
  int fld_9C; // edi

  if ( nArg2 != *(uint32_t *)(this + 148) )
  {
    fld_2C = *(uint32_t *)(this + 44);
    *(uint32_t *)(this + 148) = nArg2;
    fld_9C = *(uint32_t *)(this + 156);
    *(uint32_t *)(this + 152) = fld_9C;
    *(uint32_t *)(this + 156) = fld_9C
                            - (uint64_t)((double)*(int *)(88 * nArg2 + fld_2C + 48) / *(float *)(this + 164) * -100.0);
    sub_430B70(this + 60);
    sub_493120(88 * nArg2 + *(uint32_t *)(this + 44));
    *(uint32_t *)(this + 172) = 0;
  }
}



// ------------------------------------------------------------
// 0x493480 sub_493480 —— 帧数组 vector<frame88> 模板实现（assign/erase 族）
// ------------------------------------------------------------
void /*thiscall*/ sub_493480(int *this, int pArg2, unsigned int uArg3, int pArg4)
{
  int fld_e1; // ecx
  unsigned int fld_e3; // eax
  int fld_e2; // edx
  int fld_e22; // edx
  unsigned int v10; // eax
  int fld_e27; // edx
  int fld_e28; // eax
  char *pMem; // ebx
  void *fld_e13; // ecx
  int fld_e210; // eax
  unsigned int v16; // edi
  void *fld_e23; // eax
  int fld_e26; // edi
  int v19; // edi
  int v20; // eax
  int fld_e12; // [esp-18h] [ebp-64h]
  void *Block2; // [esp-18h] [ebp-64h]
  int fld_e29; // [esp-10h] [ebp-5Ch]
  int fld_e25; // [esp-Ch] [ebp-58h]
  unsigned int fld_e24; // [esp-8h] [ebp-54h]
  uint32_t v26[4]; // [esp+0h] [ebp-4Ch] BYREF
  void *Block; // [esp+10h] [ebp-3Ch]
  char *pMem2; // [esp+14h] [ebp-38h]
  char v29[4]; // [esp+18h] [ebp-34h] BYREF
  void *v30; // [esp+1Ch] [ebp-30h]
  int v31; // [esp+2Ch] [ebp-20h]
  unsigned int v32; // [esp+30h] [ebp-1Ch]
  int v33; // [esp+34h] [ebp-18h]
  int dword_796E502; // [esp+38h] [ebp-14h]
  uint32_t *v35; // [esp+3Ch] [ebp-10h]
  int v36; // [esp+48h] [ebp-4h]
  int v37; // [esp+58h] [ebp+Ch]

  v35 = v26;
  dword_796E502 = dword_796E50;
  v26[3] = this;
  v32 = 15;
  v31 = 0;
  LOBYTE(v30) = 0;
  sub_4014D0((std::_String_base *)v29, pArg4, 0, -1);
  v33 = *(uint32_t *)(pArg4 + 28);
  fld_e1 = *(this + 1);
  v36 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) >> 5;
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) >> 5;
    else
      fld_e2 = 0;
    if ( 0x7FFFFFF - fld_e2 < uArg3 )
      sub_492810(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) >> 5;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Block = fld_e23;
      if ( ((int)fld_e23 - pArg2) >> 5 >= uArg3 )
      {
        v19 = (int)fld_e23 - 32 * uArg3;
        v20 = sub_4928C0(v19, (int)fld_e23, (int)fld_e23);
        Block2 = Block;
        *(this + 2) = v20;
        sub_492DA0(pArg2, v19, Block2);
        sub_492D60(pArg2, pArg2 + 32 * uArg3, v29);
      }
      else
      {
        sub_4928C0(pArg2, (int)fld_e23, pArg2 + 32 * uArg3);
        fld_e24 = uArg3 - ((*(this + 2) - pArg2) >> 5);
        fld_e25 = *(this + 2);
        LOBYTE(v36) = 3;
        sub_493230(fld_e25, fld_e24, v29);
        fld_e26 = 32 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v36 = 0;
        sub_492D60(pArg2, fld_e26 - 32 * uArg3, v29);
      }
    }
    else
    {
      if ( 0x7FFFFFF - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) >> 5;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
      {
        if ( fld_e1 != 0 )
          fld_e28 = (*(this + 2) - fld_e1) >> 5;
        else
          fld_e28 = 0;
        v10 = uArg3 + fld_e28;
      }
      v37 = 32 * v10;
      pMem = (char *)operator new(32 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;
      pMem2 = (char *)sub_4928C0(fld_e12, pArg2, (int)pMem);
      sub_492DC0((int)pMem2, uArg3, (int)v29);
      fld_e29 = *(this + 2);
      pMem2 += 32 * uArg3;
      sub_4928C0(pArg2, fld_e29, (int)pMem2);
      fld_e13 = (void *)*(this + 1);
      if ( fld_e13 != nullptr )
        fld_e210 = (*(this + 2) - (int)fld_e13) >> 5;
      else
        fld_e210 = 0;
      v16 = fld_e210 + uArg3;
      if ( fld_e13 != nullptr )
      {
        sub_493260(fld_e13, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v37];
      *(this + 2) = (int)&pMem[32 * v16];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v32 >= 0x10 )
    j__free(v30);
}


// ------------------------------------------------------------
// 0x493740 sub_493740
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493740(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_4932C0(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x493760 sub_493760
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493760(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_493300(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x493780 sub_493780
// ------------------------------------------------------------
void /*cdecl*/ sub_493780(uint32_t *uArg1, int nArg2, int nArg3)
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
      sub_493070(uArg12, nArg3);
    --nArg2;
    uArg12 += 22;
    LOBYTE(v6) = 0;
  }
}



// ------------------------------------------------------------
// 0x493840 sub_493840 —— ★帧推进（研究§26）
//   当前时刻(+32，或经 +212 同步源取) ≥ 帧尾(+156) 则切下一帧（+148 递增，sub_493400 应用）；
//   尾帧且无 [LOOP](+160) → 置 +170=1 播完停走。
// ------------------------------------------------------------
char /*thiscall*/ sub_493840(int this)
{
  int fld_D4; // ecx
  int fld_20; // ebx
  unsigned int fld_2C2; // eax
  int fld_94; // edi
  int fld_2C; // eax

  fld_D4 = *(uint32_t *)(this + 212);
  if ( fld_D4 != 0 )
    fld_20 = sub_4910A0(fld_D4);
  else
    fld_20 = *(uint32_t *)(this + 32);
  LOBYTE(fld_2C2) = *(uint8_t *)(this + 170);
  fld_94 = *(uint32_t *)(this + 148);
  if ( (uint8_t)fld_2C2 == 0 )
  {
    while ( fld_20 >= *(uint32_t *)(this + 156) )  // 累计时刻 ≥ 帧尾(+156) → 切帧
    {
      fld_2C = *(uint32_t *)(this + 44);
      if ( fld_2C != 0 )
        fld_2C = (*(uint32_t *)(this + 48) - fld_2C) / 88;
      if ( fld_94 == fld_2C - 1 )
      {
        LOBYTE(fld_2C2) = *(uint8_t *)(this + 160);
        if ( (uint8_t)fld_2C2 == 0 )
        {
          *(uint8_t *)(this + 170) = 1;  // 播完标志（无[LOOP]到尾帧）
          return fld_2C2;
        }
        fld_2C2 = *(uint32_t *)(this + 44);
        if ( fld_2C2 == 0 )
          return fld_2C2;
        fld_2C2 = (int)(*(uint32_t *)(this + 48) - fld_2C2) / 88;
        if ( fld_2C2 <= 1 )
          return fld_2C2;
        fld_94 = 0;
      }
      else
      {
        ++fld_94;
      }
      sub_493400(this, fld_94);
      LOBYTE(fld_2C2) = *(uint8_t *)(this + 170);
      if ( (uint8_t)fld_2C2 != 0 )
        return fld_2C2;
    }
  }
  return fld_2C2;
}



// ------------------------------------------------------------
// 0x4938F0 sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4938F0(int this)
{
  int fld_D4; // ecx
  char fld_A9; // al
  uint32_t *result; // eax
  uint32_t *v5; // esi

  fld_D4 = *(uint32_t *)(this + 212);
  if ( fld_D4 != 0 )
    fld_A9 = sub_4910C0(fld_D4);
  else
    fld_A9 = *(uint8_t *)(this + 169);
  if ( fld_A9 == 0 && sub_4910E0(this) != 0 || *(uint32_t *)(this + 148) == -1 )
  {
    sub_493840(this);
    sub_4919D0(this);
  }
  result = *(uint32_t **)(this + 204);
  v5 = (uint32_t *)*result;
  if ( (uint32_t *)*result != result )
  {
    do
    {
      result = (uint32_t *)sub_4938F0(v5[3]);
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != *(uint32_t **)(this + 204) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x493960 sub_493960
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493960(int *this, uint32_t *uArg2, uint32_t *uArg3, int nArg4)
{
  uint32_t *uArg32; // ecx
  uint32_t *fld_e2; // eax
  uint32_t *fld_e22; // ebx
  uint32_t *fld_e23; // edi
  uint32_t *i; // esi
  int *pThis; // [esp+4h] [ebp-4h]

  uArg32 = uArg3;
  pThis = this;
  if ( uArg3 != (uint32_t *)nArg4 )
  {
    fld_e2 = sub_4932C0(nArg4, *(this + 2), uArg3);
    fld_e22 = (uint32_t *)*(this + 2);
    fld_e23 = fld_e2;
    for ( i = fld_e2; i != fld_e22; i += 22 )
      sub_42AA10(i);
    uArg32 = uArg3;
    pThis[2] = (int)fld_e23;
  }
  *uArg2 = uArg32;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4939C0 sub_4939C0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4939C0(int nArg1, int nArg2, uint32_t *uArg3)
{
  return sub_493340(nArg1, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x4939E0 sub_4939E0 —— 播放/暂停级联（递归子链 +204）
// ------------------------------------------------------------
char /*thiscall*/ sub_4939E0(int this, char pszArg2)
{
  char result; // al
  char fld_A9; // bl
  int fld_20; // edi

  result = pszArg2;
  fld_A9 = *(uint8_t *)(this + 169);
  if ( pszArg2 != fld_A9 )
  {
    if ( pszArg2 != 0 )
    {
      result = sub_4938F0(this);
      *(uint8_t *)(this + 169) = pszArg2;
    }
    else
    {
      if ( *(uint32_t *)(this + 212) != 0 )
        fld_20 = sub_4910A0();
      else
        fld_20 = *(uint32_t *)(this + 32);
      sub_4926A0(this);
      *(uint32_t *)(this + 28) = fld_20;
      sub_4910E0(this);
      result = sub_4939E0(fld_A9);
      *(uint8_t *)(this + 169) = 0;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x493A60 sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
// ------------------------------------------------------------
char /*thiscall*/ sub_493A60(int this, int nArg2)
{
  int fld_D4; // ecx
  char fld_A92; // al
  int fld_1C; // eax
  char fld_A9; // [esp+4h] [ebp-4h]

  fld_A9 = *(uint8_t *)(this + 169);
  sub_4926A0(this);
  *(uint32_t *)(this + 28) = nArg2;
  *(uint8_t *)(this + 168) = 1;
  sub_698F90(this, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_D4 = *(uint32_t *)(this + 212);
  if ( fld_D4 != 0 )
    fld_A92 = sub_4910C0(fld_D4);
  else
    fld_A92 = *(uint8_t *)(this + 169);
  if ( fld_A92 == 0 )
  {
    fld_1C = *(uint32_t *)(this + 28) + sub_699000(this);  // 【clock_now(clk)】
    if ( fld_1C != *(uint32_t *)(this + 32) )
      *(uint32_t *)(this + 32) = fld_1C;
  }
  return sub_4939E0(this, fld_A9);
}



// ------------------------------------------------------------
// 0x493AD0 sub_493AD0
// ------------------------------------------------------------
void /*thiscall*/ sub_493AD0(int this, size_t *pArg2)
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;
  else
    fld_8 = 0;
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 5 )
  {
    fld_82 = *(uint32_t *)(this + 8);
    sub_492DC0(fld_82, 1, pArg2);
    *(uint32_t *)(this + 8) = fld_82 + 32;
  }
  else
  {
    sub_493480(this, *(size_t **)(this + 8), 1u, pArg2);
  }
}



// ------------------------------------------------------------
// 0x493B40 sub_493B40
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_493B40(uint32_t *pArg1, int nArg2, int nArg3)
{
  sub_493780(pArg1, nArg2, nArg3);
  return &pArg1[22 * nArg2];
}



// ------------------------------------------------------------
// 0x493B70 sub_493B70 —— 同步源模式下重算累计时间（sub_493A60 链）
// ------------------------------------------------------------
char /*thiscall*/ sub_493B70(int this)
{
  int fld_D4; // ecx
  char fld_A9; // al
  int fld_1C; // eax

  *(uint8_t *)(this + 168) = 1;
  sub_698F90(this, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_D4 = *(uint32_t *)(this + 212);
  if ( fld_D4 != 0 )
    fld_A9 = sub_4910C0(fld_D4);
  else
    fld_A9 = *(uint8_t *)(this + 169);
  if ( fld_A9 == 0 )
  {
    fld_1C = *(uint32_t *)(this + 28) + sub_699000(this);  // 【clock_now(clk)】
    if ( fld_1C != *(uint32_t *)(this + 32) )
      *(uint32_t *)(this + 32) = fld_1C;
  }
  return sub_493A60(this, *(uint32_t *)(this + 32));
}



// ------------------------------------------------------------
// 0x493BD0 sub_493BD0 —— 动画对象复位
//   +148=-1 帧索引、+160=0 [LOOP]、+161=1 [SHADOW] 默认开、
//   +164=1120403456(100.0f) 播放速率默认 100、+200 list 初始化（子动画链）、+212=0。
// ------------------------------------------------------------
int /*thiscall*/ sub_493BD0(int this)
{
  int result; // eax

  sub_699070(1);  // 【clock_bind_domain(clk, newDomainId)】
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 32) = -1;
  sub_42AF40(this + 40);
  sub_430B70(this + 60);
  *(uint32_t *)(this + 148) = -1;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 0;
  *(uint8_t *)(this + 160) = 0;  // [LOOP] 默认关
  *(uint8_t *)(this + 161) = 1;  // [SHADOW] 默认开
  *(uint32_t *)(this + 164) = 1120403456;  // 播放速率=100.0f（0x42C80000）
  *(uint8_t *)(this + 168) = 0;
  *(uint8_t *)(this + 169) = 0;
  *(uint8_t *)(this + 170) = 0;
  *(uint8_t *)(this + 56) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint8_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = 0;
  *(uint8_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = -1;
  *(uint8_t *)(this + 196) = 0;
  result = sub_6569D0(this + 200);
  *(uint32_t *)(this + 212) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x493C80 sub_493C80 —— 析构（帧数组 +40..55、子链 list +200..211 释放）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_493C80(void ****this)
{
  void ***fld_e53; // ecx
  void ****fld_e51; // ecx
  void ***v4; // eax
  void ****fld_e512; // ecx
  void ***result; // eax
  bool fld_e513; // zf
  void ***v8; // edi

  sub_42AF40(this + 10);
  sub_430B70(this + 15);
  fld_e53 = *(this + 53);
  if ( fld_e53 != nullptr )
    sub_492980(fld_e53, this);
  fld_e51 = (void ****)*(this + 51);
  v4 = *fld_e51;
  if ( *fld_e51 != (void ***)fld_e51 )
  {
    do
    {
      v4[3][53] = nullptr;
      v4 = (void ***)*v4;
    }
    while ( v4 != *(this + 51) );
  }
  fld_e512 = (void ****)*(this + 51);
  result = *fld_e512;
  *fld_e512 = (void ***)fld_e512;
  (*(this + 51))[1] = (void **)*(this + 51);
  fld_e513 = result == *(this + 51);
  *(this + 52) = nullptr;
  if ( !fld_e513 )
  {
    do
    {
      v8 = (void ***)*result;
      j__free(result);
      result = v8;
    }
    while ( v8 != *(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x493D00 sub_493D00 —— ★变速（研究§26）
//   新速率写 +164；累计时长(+32)按 旧/新 速率比换算（sub_493A60），同步源(+212)模式走
//   sub_493B70；随后递归子链(+204)同速、sub_4938F0 重推帧。速率 0 视为 1。
// ------------------------------------------------------------
void /*thiscall*/ sub_493D00(int this, float fArg2)
{
  double fld_A4; // st7
  uint32_t **fld_CC; // eax
  uint32_t *v5; // esi

  if ( fArg2 == 0.0 )
    fArg2 = 1.0;
  if ( fArg2 != *(float *)(this + 164) )  // 速率槽 +164
  {
    fld_A4 = *(float *)(this + 164);
    *(float *)(this + 164) = fArg2;
    if ( *(uint32_t *)(this + 212) != 0 )
      sub_493B70(this);
    else
      sub_493A60(this, (uint64_t)((double)*(int *)(this + 32) / fArg2 * fld_A4));  // 累计时长(+32)按 旧/新 速率比换算，不跳帧
    fld_CC = *(uint32_t ***)(this + 204);  // 子动画链 +204
    v5 = *fld_CC;
    if ( *fld_CC != fld_CC )
    {
      do
      {
        sub_493D00(fArg2);
        v5 = (uint32_t *)*v5;
      }
      while ( v5 != *(uint32_t **)(this + 204) );
    }
    sub_4938F0(this);
  }
}



// ============================================================
// §G 0x493DB0-0x494680  帧数组批量操作 + 加载准备
// ============================================================
// ------------------------------------------------------------
// 0x493DB0 sub_493DB0 —— 帧数组 assign（源 a2 的 +44..+48 区间，元素 88B，含盒 vector 深拷贝）
// ------------------------------------------------------------
int /*thiscall*/ sub_493DB0(int this, int pArg2)
{
  int v3; // eax
  unsigned int v4; // ecx
  uint32_t *fld_4; // ebx
  unsigned int fld_8; // eax
  uint32_t *v8; // eax
  int v9; // eax
  unsigned int fld_C; // eax
  int v11; // edi
  int v12; // eax

  if ( this == pArg2 )
    return this;
  v3 = *(uint32_t *)(pArg2 + 4);
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) / 88) == 0 )
  {
    sub_42AF40(this);
    return this;
  }
  fld_4 = *(uint32_t **)(this + 4);
  if ( fld_4 != nullptr )
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 88;
  else
    fld_8 = 0;
  if ( v4 > fld_8 )
  {
    if ( fld_4 != nullptr )
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 88;
    else
      fld_C = 0;
    if ( v4 <= fld_C )
    {
      v11 = *(uint32_t *)(pArg2 + 4) + 88 * sub_42FC70(this);
      sub_493740(*(uint32_t *)(pArg2 + 4), v11, fld_4);
      *(uint32_t *)(this + 8) = sub_493340(v11, *(uint32_t *)(pArg2 + 8), *(uint32_t **)(this + 8));
      return this;
    }
    if ( fld_4 != nullptr )
    {
      sub_42AF10(fld_4, *(uint32_t *)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v12 = sub_42FC70(pArg2);
    if ( (uint8_t)sub_430C30(v12) != 0 )
      *(uint32_t *)(this + 8) = sub_4939C0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t **)(this + 4));
    return this;
  }
  v8 = sub_4932C0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), fld_4);
  sub_42AF10(v8, *(uint32_t *)(this + 8));
  v9 = *(uint32_t *)(pArg2 + 4);
  if ( v9 != 0 )
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 88 * ((*(uint32_t *)(pArg2 + 8) - v9) / 88);
  else
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);
  return this;
}



// ------------------------------------------------------------
// 0x493F30 sub_493F30 —— 帧数组批量构造（sub_493070/493120/493340 复制族 + 尾部裁剪）
// ------------------------------------------------------------
void /*thiscall*/ sub_493F30(int *this, int pArg2, unsigned int uArg3, int nArg4)
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
  int fld_e12; // [esp-18h] [ebp-94h]
  int fld_e25; // [esp-Ch] [ebp-88h]
  unsigned int fld_e24; // [esp-8h] [ebp-84h]
  int v22; // [esp+0h] [ebp-7Ch] BYREF
  uint8_t v23[60]; // [esp+Ch] [ebp-70h] BYREF
  void *v24; // [esp+48h] [ebp-34h]
  void *v25; // [esp+58h] [ebp-24h]
  int v26; // [esp+5Ch] [ebp-20h]
  int v27; // [esp+60h] [ebp-1Ch]
  void *Block; // [esp+64h] [ebp-18h]
  int *pThis; // [esp+68h] [ebp-14h]
  int *v30; // [esp+6Ch] [ebp-10h]
  int v31; // [esp+78h] [ebp-4h]
  int v32; // [esp+84h] [ebp+8h]
  int v33; // [esp+88h] [ebp+Ch]
  int v34; // [esp+8Ch] [ebp+10h]
  int fld_e232; // [esp+8Ch] [ebp+10h]

  v30 = &v22;
  pThis = this;
  sub_493070(nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 88;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 88;
    else
      fld_e2 = 0;
    if ( 48806446 - fld_e2 < uArg3 )
      sub_430A90(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 88;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = *(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pArg2) / 88 >= uArg3 )
      {
        v32 = fld_e23 - 88 * uArg3;
        *(this + 2) = sub_493340(v32, fld_e23, fld_e23);
        sub_493760(pArg2, v32, fld_e232);
        sub_493290(pArg2, pArg2 + 88 * uArg3, v23);
      }
      else
      {
        sub_493340(pArg2, fld_e23, pArg2 + 88 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 88;
        fld_e25 = *(this + 2);
        LOBYTE(v31) = 3;
        sub_493B40(fld_e25, fld_e24, v23);
        fld_e26 = 88 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v31 = 0;
        sub_493290(pArg2, fld_e26 - 88 * uArg3, v23);
      }
    }
    else
    {
      if ( 48806446 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 88;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_42FC70(this);
      v34 = 88 * v10;
      pMem = (char *)operator new(88 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      LOBYTE(v31) = 1;
      v33 = sub_493340(fld_e12, pArg2, pMem);
      sub_493780(v33, uArg3, v23);
      sub_493340(pArg2, *(this + 2), 88 * uArg3 + v33);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 88;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_42AF10(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v34];
      *(this + 2) = (int)&pMem[88 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v25 != nullptr )
    j__free(v25);
  v25 = nullptr;
  v26 = 0;
  v27 = 0;
  if ( v24 != nullptr )
    j__free(v24);
}


// ------------------------------------------------------------
// 0x494240 sub_494240 —— 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
// ------------------------------------------------------------
void /*thiscall*/ sub_494240(int this, int nArg2, int pArg3)
{
  uint32_t *fld_CC; // eax
  uint32_t *v5; // esi
  bool v6; // zf
  int v7; // edi
  uint32_t v8[2]; // [esp+4h] [ebp-8h] BYREF

  if ( pArg3 != 0 )
  {
    v8[1] = pArg3;
    fld_CC = *(uint32_t **)(this + 204);
    v5 = (uint32_t *)*fld_CC;
    v6 = *fld_CC == (uint32_t)fld_CC;
    v8[0] = nArg2;
    if ( !v6 )
    {
      do
      {
        if ( v5[2] > nArg2 )
          break;
        v5 = (uint32_t *)*v5;
      }
      while ( v5 != fld_CC );
    }
    v7 = sub_52DAA0(v5, v5[1], v8);
    sub_492780(1);
    v5[1] = v7;
    **(uint32_t **)(v7 + 4) = v7;
    *(uint32_t *)(pArg3 + 212) = this;
    sub_4926A0(pArg3);
    sub_493D00(pArg3, *(float *)(this + 164));
  }
}



// ------------------------------------------------------------
// 0x4942D0 sub_4942D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4942D0(uint32_t *this)
{
  uint32_t *fld_e51; // eax
  uint32_t *v3; // esi
  int v4; // ebx
  uint32_t **fld_e512; // ecx
  uint32_t *result; // eax
  bool fld_e513; // zf
  uint32_t *v8; // esi

  fld_e51 = (uint32_t *)*(this + 51);
  v3 = (uint32_t *)*fld_e51;
  if ( (uint32_t *)*fld_e51 != fld_e51 )
  {
    do
    {
      *(uint32_t *)(v3[3] + 212) = 0;
      v4 = v3[3];
      if ( v4 != 0 )
      {
        sub_42AF90((void **)v3[3]);
        sub_657740(v4, 228);
      }
      v3[3] = 0;
      v3 = (uint32_t *)*v3;
    }
    while ( v3 != (uint32_t *)*(this + 51) );
  }
  fld_e512 = (uint32_t **)*(this + 51);
  result = *fld_e512;
  *fld_e512 = fld_e512;
  *(uint32_t *)(*(this + 51) + 4) = *(this + 51);
  fld_e513 = result == (uint32_t *)*(this + 51);
  *(this + 52) = 0;
  if ( !fld_e513 )
  {
    do
    {
      v8 = (uint32_t *)*result;
      j__free(result);
      result = v8;
    }
    while ( v8 != (uint32_t *)*(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x494370 sub_494370 —— 装载帧数组副本并重取图像句柄（帧+4 → sub_418DD0 刷新帧+0）
// ------------------------------------------------------------
void /*thiscall*/ sub_494370(int this, int pArg2)
{
  int pThis_28; // edi
  unsigned int v3; // ebx
  int v4; // eax
  int *fld_2C; // esi
  uint32_t *v6; // eax
  unsigned int v7; // [esp-Ch] [ebp-14h]
  int i; // [esp+10h] [ebp+8h]

  if ( pArg2 != 0 )
  {
    *(uint8_t *)(this + 160) = *(uint8_t *)(pArg2 + 160);
    pThis_28 = this + 40;
    *(uint8_t *)(this + 161) = *(uint8_t *)(pArg2 + 161);
    sub_42AF40(this + 40);
    sub_493DB0(pThis_28, pArg2 + 40);
    v3 = 0;
    for ( i = 0; ; i += 88 )
    {
      v4 = *(uint32_t *)(pThis_28 + 4);
      if ( v4 == 0 || v3 >= (*(uint32_t *)(pThis_28 + 8) - v4) / 88 )
        break;
      fld_2C = (int *)(*(uint32_t *)(this + 44) + i);
      if ( fld_2C[1] != -1 )
      {
        v7 = fld_2C[2];
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, fld_2C[1]);
        *fld_2C = sub_418DD0(v6, v7);
      }
      ++v3;
    }
  }
}



// ------------------------------------------------------------
// 0x494420 sub_494420 —— 帧数组构建（每帧 22×uint32=88B；sub_493960/493F30）
// ------------------------------------------------------------
void /*thiscall*/ sub_494420(
        int *this,
        unsigned int a2,
        char a3,
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
        int a15,
        int a16,
        int a17,
        void *a18,
        int a19,
        int a20,
        int a21,
        void *Block,
        int a23,
        int a24)
{
  int v24; // edi
  unsigned int v25; // eax
  int v26; // eax

  v24 = *(this + 1);
  if ( v24 != 0 )
    v25 = (*(this + 2) - v24) / 88;
  else
    v25 = 0;
  if ( v25 >= a2 )
  {
    if ( v24 != 0 && a2 < (*(this + 2) - v24) / 88 )
      sub_493960(this, &a2, (uint32_t *)(v24 + 88 * a2), *(this + 2));
  }
  else
  {
    if ( v24 != 0 )
      v26 = (*(this + 2) - v24) / 88;
    else
      v26 = 0;
    sub_493F30(this, (char *)*(this + 2), a2 - v26, (int)&a3);
  }
  if ( Block != nullptr )
    j__free(Block);
  if ( a18 != nullptr )
    j__free(a18);
}



// ------------------------------------------------------------
// 0x494500 sub_494500
// ------------------------------------------------------------
int /*thiscall*/ sub_494500(int *this, int nArg2)
{
  int result; // eax
  uint32_t *v4; // esi
  int v5; // edi
  uint32_t *v6; // edi

  result = *(this + 51);
  v4 = *(uint32_t **)result;
  if ( *(uint32_t *)result != result )
  {
    do
    {
      result = v4[2];
      if ( result == nArg2 )
      {
        result = v4[3];
        *(uint32_t *)(result + 212) = 0;
        v5 = v4[3];
        if ( v5 != 0 )
        {
          sub_42AF90((void **)v4[3]);
          result = sub_657740(v5, 228);
        }
        v4[3] = 0;
        v6 = (uint32_t *)*v4;
        if ( v4 != (uint32_t *)*(this + 51) )
        {
          *(uint32_t *)v4[1] = v6;
          *(uint32_t *)(*v4 + 4) = v4[1];
          j__free(v4);
          result = *(this + 52) - 1;
          *(this + 52) = result;
        }
        v4 = v6;
      }
      else
      {
        if ( result > nArg2 )
          return result;
        v4 = (uint32_t *)*v4;
      }
    }
    while ( v4 != (uint32_t *)*(this + 51) );
  }
  return result;
}



// ------------------------------------------------------------
// 0x4945A0 sub_4945A0 —— 按帧数 n 初始化帧数组（转发 sub_494420）
// ------------------------------------------------------------
void /*thiscall*/ sub_4945A0(int *this, unsigned int uArg2)
{
  int v3[15]; // [esp-58h] [ebp-70h] BYREF
  void *v4; // [esp-1Ch] [ebp-34h]
  int v5; // [esp-18h] [ebp-30h]
  int v6; // [esp-14h] [ebp-2Ch]
  int v7; // [esp-10h] [ebp-28h]
  void *v8; // [esp-Ch] [ebp-24h]
  int v9; // [esp-8h] [ebp-20h]
  int v10; // [esp-4h] [ebp-1Ch]
  int *v11; // [esp+8h] [ebp-10h]
  int v12; // [esp+14h] [ebp-4h]

  v11 = v3;
  v4 = nullptr;
  v5 = 0;
  v6 = 0;
  v8 = nullptr;
  v9 = 0;
  v10 = 0;
  sub_430B70(v3);
  v12 = -1;
  sub_494420(
    this,
    uArg2,
    v3[0],
    v3[1],
    v3[2],
    v3[3],
    v3[4],
    v3[5],
    v3[6],
    v3[7],
    v3[8],
    v3[9],
    v3[10],
    v3[11],
    v3[12],
    v3[13],
    v3[14],
    v4,
    v5,
    v6,
    v7,
    v8,
    v9,
    v10);
}



// ------------------------------------------------------------
// 0x494610 sub_494610 —— 帧数组重置包装（对 +40 偏移的动画子对象）
// ------------------------------------------------------------
int /*thiscall*/ sub_494610(int *this, unsigned int uArg2)
{
  sub_4945A0(this + 10, uArg2);
  return sub_4926A0((int)this);
}



// ------------------------------------------------------------
// 0x494630 sub_494630 —— 单帧占位初始化：帧+0 句柄槽；帧+12/+16 = 尺寸(a2+20/+24)/2 取负 → 居中锚点
// ------------------------------------------------------------
int /*thiscall*/ sub_494630(int this, int pArg2)
{
  sub_4945A0((int *)(this + 40), 1u);
  **(uint32_t **)(this + 44) = pArg2;
  *(uint32_t *)(*(uint32_t *)(this + 44) + 12) = *(uint32_t *)(pArg2 + 20) / -2;
  *(uint32_t *)(*(uint32_t *)(this + 44) + 16) = *(uint32_t *)(pArg2 + 24) / -2;
  return sub_4926A0(this);
}



// ============================================================
// §H 0x494680-0x494E40  ★★★ .ani 主解析器 sub_494680
// ============================================================
// ------------------------------------------------------------
// 0x494680 sub_494680 —— ★★★ .ani 主解析器（标签清单见文件头）
//   流程：sub_442A10 打开 → [LOOP]→对象+160 → [SHADOW]→+161 → [FRAME MAX]→帧数并
//   sub_4945A0 分配 → 逐帧（基址 = 对象+44 vector 首，步进 88）读 [IMAGE][IMAGE POS]
//   [IMAGE RATE][IMAGE ROTATE][RGBA][INTERPOLATION][GRAPHIC EFFECT][DELAY]
//   [DAMAGE TYPE][ATTACK BOX]/[DAMAGE BOX](多组) → 任一步缺标签即失败返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_494680(uint8_t *this, char ArgList, int nArg3, char pszArg4, int nArg5, int nArg6, int nArg7)
{
  uint8_t *pThis; // esi
  char result; // al
  int v9; // edi
  int v10; // esi
  int v11; // edi
  int v12; // eax
  void **Block3; // eax
  void **Block2; // eax
  int v15; // eax
  uint8_t v16; // bl
  uint16_t v17; // dx
  uint8_t v18; // bl
  bool v19; // cc
  char v20[32]; // [esp+4h] [ebp-290h] BYREF
  float v21[6]; // [esp+24h] [ebp-270h] BYREF
  uint8_t *pThis2; // [esp+3Ch] [ebp-258h]
  int v23; // [esp+40h] [ebp-254h]
  int v24; // [esp+44h] [ebp-250h]
  int v25; // [esp+48h] [ebp-24Ch]
  char Buffer[256]; // [esp+4Ch] [ebp-248h] BYREF
  char Src[256]; // [esp+14Ch] [ebp-148h] BYREF
  char v28[4]; // [esp+24Ch] [ebp-48h] BYREF
  void *Block[4]; // [esp+250h] [ebp-44h] BYREF
  int v30; // [esp+260h] [ebp-34h]
  unsigned int v31; // [esp+264h] [ebp-30h]
  char v32[4]; // [esp+268h] [ebp-2Ch] BYREF
  void *v33; // [esp+26Ch] [ebp-28h]
  unsigned int v34; // [esp+27Ch] [ebp-18h]
  unsigned int v35; // [esp+280h] [ebp-14h]
  int dword_796E502; // [esp+284h] [ebp-10h]
  int v37; // [esp+290h] [ebp-4h]
  int ArgLista; // [esp+29Ch] [ebp+8h]

  dword_796E502 = dword_796E50;
  pThis = this;
  pThis2 = this;
  result = sub_442A10(ArgList, nArg3);
  if ( result == 0 )
    return result;
  v35 = 15;
  v34 = 0;
  LOBYTE(v33) = 0;
  v37 = 1;
  v31 = 15;
  v30 = 0;
  LOBYTE(Block[0]) = 0;
  if ( (uint8_t)sub_443430(v32) == 0 || sub_40BF00((std::_String_base *)v32, 0, v34, "[LOOP]", 6u) != 0 )
  {
    v31 = 15;
    v30 = 0;
    LOBYTE(Block[0]) = 0;
    if ( v35 >= 0x10 )
      j__free(v33);
    return 0;
  }
  pThis[160] = sub_4423D0(0) != 0;  // [LOOP] → 动画对象+160
  if ( (uint8_t)sub_443430(v32) == 0
    || (uint8_t)sub_423340(v32, "[SHADOW]") != 0
    || (pThis[161] = sub_4423D0(0) != 0, (uint8_t)sub_443430(v32) == 0)  // [SHADOW] → 对象+161
    || (uint8_t)sub_423340(v32, "[FRAME MAX]") != 0
    || (v9 = sub_4423D0(0), v24 = v9, sub_4945A0(v9), (uint8_t)sub_443430(v32) == 0)  // [FRAME MAX] → 帧数 v24；sub_4945A0 按 88B/帧分配
    || (uint8_t)sub_423340(v32, "[FRAME000]") != 0 )
  {
LABEL_66:
    sub_501490(v28);
    sub_501490(v32);
    return 0;
  }
  v25 = 0;
  if ( v9 > 0 )
  {
    ArgLista = 0;
    while ( 1 )
    {
      v10 = ArgLista + *((uint32_t *)pThis + 11);  // 帧基址 = 对象+44(vector首) + 88×帧序【研究§11】
      sub_430B70(v10);
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[IMAGE]") != 0 )
        goto LABEL_66;
      sub_443370();
      v11 = sub_4423D0(0);
      nArg3 = v11;
      if ( (uint8_t)sub_423340(v28, szPassword) != 0 )
      {
        if ( pszArg4 == 0 )
        {
          v15 = sub_4BC700(v28);
LABEL_25:
          *(uint32_t *)(v10 + 8) = v11;  // 帧+8 资源id
          *(uint32_t *)(v10 + 4) = v15;  // 帧+4 路径资源（sub_4BC700 路径→id）
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v15);
          *(uint32_t *)v10 = sub_418DD0(v11);  // 帧+0 图像句柄
          goto LABEL_26;
        }
        if ( nArg5 == 0 )
        {
          Block2 = (void **)Block[0];
          if ( v31 < 0x10 )
            Block2 = Block;
          sprintf(Src, (const char *const)Block2, nArg6, nArg7);
          sub_406D60(Src);
          v15 = sub_4BC700(v28);
          goto LABEL_25;
        }
        *(uint32_t *)v10 = 0;
        v12 = sub_492750(v28, &nArg3);
        LOBYTE(v37) = 2;
        sub_493AD0(v12);
        LOBYTE(v37) = 1;
        sub_501490(v20);
        Block3 = (void **)Block[0];
        if ( v31 < 0x10 )
          Block3 = Block;
        sprintf(Buffer, (const char *const)Block3, nArg6, nArg7);
        sub_406D60(Buffer);
        *(uint32_t *)(v10 + 4) = sub_4BC700(v28);  // 帧+4 路径资源
        *(uint32_t *)(v10 + 8) = v11;  // 帧+8 资源id
      }
LABEL_26:
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE POS]") != 0 )
        goto LABEL_66;
      *(uint32_t *)(v10 + 12) = sub_4423D0(0);  // 帧+12 位置x [IMAGE POS]
      *(uint32_t *)(v10 + 16) = sub_4423D0(0);  // 帧+16 位置y
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE RATE]") != 0 )
        goto LABEL_66;
      *(float *)(v10 + 20) = sub_442480(0);  // 帧+20 缩放x [IMAGE RATE]
      *(float *)(v10 + 24) = sub_442480(0);  // 帧+24 缩放y
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE ROTATE]") != 0 )
        goto LABEL_66;
      *(float *)(v10 + 28) = sub_442480(0);  // 帧+28 旋转 [IMAGE ROTATE]
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[RGBA]") != 0 )
        goto LABEL_66;
      v16 = sub_4423D0(0);
      nArg3 = sub_4423D0(0);
      v23 = sub_4423D0(0);
      HIBYTE(v17) = sub_4423D0(0);
      LOBYTE(v17) = v23;
      *(uint32_t *)(v10 + 32) = v16 | (((uint8_t)nArg3 | (v17 << 8)) << 8);  // 帧+32 [RGBA] 打包
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[INTERPOLATION]") != 0 )
        goto LABEL_66;
      *(uint8_t *)(v10 + 36) = sub_4423D0(0) != 0;  // 帧+36 [INTERPOLATION] 插值开关
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[GRAPHIC EFFECT]") != 0 )
        goto LABEL_66;
      sub_443370();
      if ( (uint8_t)sub_423300(v28, "NONE") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 0;  // 帧+40 特效=NONE
      }
      else if ( (uint8_t)sub_423300(v28, "DODGE") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 1;  // 帧+40 特效=DODGE
      }
      else if ( (uint8_t)sub_423300(v28, "LINEARDODGE") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 2;  // 帧+40 特效=LINEARDODGE
      }
      else if ( (uint8_t)sub_423300(v28, "DARK") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 3;  // 帧+40 特效=DARK
      }
      else if ( (uint8_t)sub_423300(v28, &off_6CAF88) != 0 )
      {
        *(uint32_t *)(v10 + 40) = 4;  // 帧+40 特效=4（off_6CAF88 指向的标签，研究§11 之"+4"）
      }
      else if ( (uint8_t)sub_423300(v28, "MONOCHROME") != 0 )
      {
        *(uint32_t *)(v10 + 40) = 5;  // 帧+40 特效=MONOCHROME
        v18 = sub_4423D0(0);
        nArg3 = sub_4423D0(0);
        *(uint32_t *)(v10 + 44) = v18 | (((uint8_t)nArg3 | ((sub_4423D0(0) | 0xFFFFFF00) << 8)) << 8);  // 帧+44 MONOCHROME 参数色
      }
      if ( (uint8_t)sub_443430(v32) == 0 )
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[DELAY]") != 0 )
        goto LABEL_66;
      *(uint32_t *)(v10 + 48) = sub_4423D0(0);  // ★帧+48 [DELAY] 本帧驻留ms（研究§11）
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[DAMAGE TYPE]") != 0 )
        goto LABEL_66;
      sub_443370();
      if ( (uint8_t)sub_423300(v28, "NORMAL") != 0 )
      {
        *(uint32_t *)(v10 + 52) = 0;  // ★帧+52 [DAMAGE TYPE] 0=NORMAL
      }
      else if ( (uint8_t)sub_423300(v28, "SUPERARMOR") != 0 )
      {
        *(uint32_t *)(v10 + 52) = 1;  // ★帧+52 [DAMAGE TYPE] 1=SUPERARMOR 霸体
      }
      else if ( (uint8_t)sub_423300(v28, "UNBREAKABLE") != 0 )
      {
        *(uint32_t *)(v10 + 52) = 2;  // ★帧+52 [DAMAGE TYPE] 2=UNBREAKABLE 不可打断
      }
      while ( (uint8_t)sub_443430(v32) != 0 )
      {
        if ( (uint8_t)sub_423340(v32, "[ATTACK BOX]") != 0
          && (uint8_t)sub_423340(v32, "[DAMAGE BOX]") != 0 )
        {
          break;
        }
        nArg3 = sub_4423D0(0);
        v21[0] = (float)nArg3;  // 盒参数 6×float（[ATTACK BOX]/[DAMAGE BOX] 多组循环）
        nArg3 = sub_4423D0(0);
        v21[1] = (float)nArg3;
        nArg3 = sub_4423D0(0);
        v21[2] = (float)nArg3;
        nArg3 = sub_4423D0(0);
        v21[3] = (float)nArg3;
        nArg3 = sub_4423D0(0);
        v21[4] = (float)nArg3;
        nArg3 = sub_4423D0(0);
        v21[5] = (float)nArg3;
        sub_423300(v32, "[ATTACK BOX]");
        sub_4931A0(v21);  // ecx=帧+56 盒vector【推断】追加一组 6float
      }
      v19 = ++v25 < v24;  // 帧序 < [FRAME MAX]
      ArgLista += 88;  // ★下一帧：帧结构步长 88 字节（研究§11）
      if ( !v19 )
        break;
      pThis = pThis2;
    }
  }
  sub_501490(v28);
  sub_501490(v32);
  return 1;
}


// ============================================================
// §I 0x494E40-0x496540  动画/粒子创建工厂（ANIMATION CREATE FAIL）
// ============================================================
// ------------------------------------------------------------
// 0x494E40 sub_494E40 —— 动画创建入口
//   a4 非空时 strcmp(a2,szPassword) 分流 sub_4F3BA0/sub_4F3D60 建空动画 → sub_494370 →
//   sub_494680 解析 .ani；失败 ANIMATION CREATE FAIL1/2!。
// ------------------------------------------------------------
int /*thiscall*/ sub_494E40(uint8_t *this, const char *pArg2, const char *ArgList, char pszArg4, int nArg5, int nArg6, int nArg7, int nArg8)
{
  int pThis; // esi
  int v9; // eax

  pThis = (int)this;
  if ( (uint8_t)nArg5 != 0 && (nArg7 == -1 || nArg8 == -1) )
    LOBYTE(nArg5) = 0;
  if ( pszArg4 != 0 )
  {
    if ( strcmp(pArg2, szPassword) == 0 )
      v9 = sub_4F3BA0(ArgList, nArg5, nArg7, nArg8);
    else
      v9 = sub_4F3D60((char)pArg2, (int)ArgList, nArg5, nArg7, nArg8);
    if ( v9 == 0 )
      return off_77F3FC("ANIMATION CREATE FAIL1! FILENAME[%s]", ArgList);
    pThis = (int)this;
    sub_494370(v9);
  }
  else if ( sub_494680(this, (char)pArg2, (int)ArgList, nArg5, nArg6, nArg7, nArg8) == 0 )
  {
    return off_77F3FC("ANIMATION CREATE FAIL2! FILENAME[%s]", ArgList);
  }
  return sub_4926A0(pThis);
}



// ------------------------------------------------------------
// 0x494F20 sub_494F20
// ------------------------------------------------------------
void /*thiscall*/ sub_494F20(float *this, int pArg2, float fArg3)
{
  float v4; // ecx

  v4 = *this;
  if ( v4 != 0.0
    && (*(uint8_t (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 308))(COERCE_FLOAT(LODWORD(v4))) != 0
    && *(this + pArg2 + 4) != fArg3 )
  {
    *(this + pArg2 + 4) = fArg3;
    *((uint8_t *)this + 196) = 1;
  }
}



// ------------------------------------------------------------
// 0x494F60 sub_494F60
// ------------------------------------------------------------
void /*thiscall*/ sub_494F60(uint32_t *this, int pArg2, int nArg3)
{
  int pObj; // ecx

  pObj = *this;
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 && *(this + pArg2 + 10) != nArg3 )
  {
    *(this + pArg2 + 10) = nArg3;
    *((uint8_t *)this + 196) = 1;
  }
}



// ------------------------------------------------------------
// 0x494FA0 sub_494FA0
// ------------------------------------------------------------
int /*thiscall*/ sub_494FA0(int *this, int nArg2, int nArg3)
{
  int result; // eax
  char v5; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 50);
    if ( result == 0 )
    {
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16);
      if ( (uint8_t)result == 0 )
      {
        v5 = 1;
        if ( nArg2 == 4 || nArg3 == 4 )
          v5 = 0;
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, char))(*this + 892))(this, 0, nArg2, v5);
        return (*(int (/*thiscall*/ **)(int *, int, int, char))(*this + 892))(this, 1, nArg3, v5);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495010 sub_495010
// ------------------------------------------------------------
void /*userpurge*/ sub_495010(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)
{
  int nArg42; // edi
  int v6; // eax
  int v7; // eax
  int *v8; // ebx
  int v9; // eax
  int v10; // edx
  int *v11; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edi
  int v16; // edx
  bool v17; // cc
  int v18; // ebx
  int v19; // edx
  int v20; // eax
  int v23; // [esp+4h] [ebp-1Ch] BYREF
  int v24; // [esp+8h] [ebp-18h] BYREF
  int v25; // [esp+Ch] [ebp-14h]
  int v26; // [esp+10h] [ebp-10h]
  int v27; // [esp+14h] [ebp-Ch]
  int v28; // [esp+18h] [ebp-8h]
  int v29; // [esp+1Ch] [ebp-4h]

  if ( pArg1[1674] == -1 )
  {
    nArg42 = nArg4;
    if ( nArg4 != 0 )
    {
      if ( nArg4 != 1 )
        return;
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 188))(pArg1);
    }
    else
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 184))(pArg1);
    }
    v29 = v6;
    if ( v6 != 4 )
    {
      v7 = nArg4 != 0
         ? (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 184))(pArg1)
         : (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 188))(pArg1);
      v28 = v7;
      if ( v7 == 4 )
      {
        v27 = 0;
        v25 = 4 * (nArg4 != 0) + 13;
        if ( 4 * (nArg4 != 0) != -13 )
        {
          v8 = &v24 - nArg4;
          v26 = 0;
          while ( 1 )
          {
            v9 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 120))(pArg1, nArg2, nArg3);
            v10 = *pArg1;
            v23 = v9;
            v24 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 124))(pArg1);
            if ( v29 == 0 || v29 == 2 )
            {
              v11 = &v23 + nArg42;
              v12 = *v11 - 1;
            }
            else
            {
              v11 = &v23 + nArg42;
              v12 = *v11 + 1;
            }
            v13 = *pArg1;
            *v11 = v12;
            v14 = v27 + 1 + *v8;
            *v8 = v14;
            nArg3 = 0;
            v15 = v14;
            nArg2 = v24;
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v13 + 136))(pArg1, v23) != 0 )
            {
              v28 = 2 * (nArg4 == 0) + 1;
              goto LABEL_23;
            }
            v16 = *pArg1;
            *v8 = v15 - v26 - 2;
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v16 + 136))(pArg1, v23, v24, 0) != 0 )
              break;
            nArg42 = nArg4;
            v17 = ++v27 < v25;
            v26 += 2;
            if ( !v17 )
              goto LABEL_24;
          }
          v28 = nArg4 != 0 ? 0 : 2;
LABEL_23:
          nArg42 = nArg4;
        }
LABEL_24:
        v18 = v28;
        v19 = v29;
        pArg1[1674] = 1 - nArg42;
        pArg1[1675] = v18;
        pArg1[1676] = v19;
        if ( nArg42 != 0 )
          v20 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 124))(pArg1, nArg2, nArg3);
        else
          v20 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 120))(pArg1, nArg2, nArg3);
        pArg1[1677] = v20;
        if ( nArg42 != 0 )
          (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 896))(pArg1);
        else
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 896))(pArg1, v29, v18);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x4951F0 sub_4951F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4951F0(int *this)
{
  int result; // eax

  result = *(this + 1674);
  if ( result != -1 )
  {
    result = result != 0
           ? (*(int (/*thiscall*/ **)(int *))(*this + 184))(this)
           : (*(int (/*thiscall*/ **)(int *))(*this + 188))(this);
    if ( *(this + 1676) != result
      || (*(this + 1674) != 0
        ? (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this))
        : (result = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this)),
          *(this + 1677) != result) )
    {
      *(this + 1674) = -1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495250 sub_495250
// ------------------------------------------------------------
char /*thiscall*/ sub_495250(uint8_t *this, unsigned int uArg2, int nArg3, int nArg4)
{
  char result; // al

  result = *(this + 6634);
  if ( result != 0 )
  {
    result = *(this + 6635);
    if ( result != 0 && *((uint32_t *)this + 1674) == -1 )
    {
      result = uArg2;
      if ( uArg2 <= 1 )
        return (*(int (/*thiscall*/ **)(uint8_t *, unsigned int))(*(uint32_t *)this + 968))(this, uArg2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495290 sub_495290
// ------------------------------------------------------------
int /*thiscall*/ sub_495290(uint32_t *this, int pArg2, int nArg3, int nArg4, int nArg5, int nArg6, char pszArg7)
{
  *(this + pArg2 + 1652) = nArg3;
  *(this + pArg2 + 1654) = nArg4;
  *((uint8_t *)this + pArg2 + 6634) = nArg5;
  *(this + pArg2 + 1656) = nArg6;
  *((uint8_t *)this + pArg2 + 6632) = pszArg7;
  if ( nArg6 != 0 )
    *((uint8_t *)this + pArg2 + 6634) = 0;
  LOBYTE(nArg5) = 1;
  if ( *(this + 1659) == 4 || *(this + 1660) == 4 )
    LOBYTE(nArg5) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 892))(this, pArg2, *(this + pArg2 + 1659), nArg5);
}



// ------------------------------------------------------------
// 0x495310 sub_495310
// ------------------------------------------------------------
int /*thiscall*/ sub_495310(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int nArg42; // ebx
  int nArg52; // edi

  *(this + 1661) = nArg2;
  *(this + 1662) = nArg3;
  if ( nArg2 != 0 )
    nArg42 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 976))(this, nArg2);
  else
    nArg42 = nArg4;
  if ( nArg3 != 0 )
    nArg52 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 976))(this, nArg3);
  else
    nArg52 = nArg5;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 980))(this, nArg42);
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 984))(this, nArg52);
}



// ------------------------------------------------------------
// 0x495380 sub_495380
// ------------------------------------------------------------
int /*thiscall*/ sub_495380(int *this, int nArg2)
{
  int v2; // edx

  v2 = *this;
  *(this + 1663) = nArg2;
  return (*(int (/*stdcall*/ **)(uint32_t, uint32_t))(v2 + 896))(*(this + 1659), *(this + 1660));
}



// ------------------------------------------------------------
// 0x4953B0 sub_4953B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4953B0(uint32_t *this)
{
  int result; // eax
  int fld_e1686; // eax
  int v4; // et2
  int v5; // edi
  int v6; // eax
  int v7; // edi
  int v8; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 852))(this);
  if ( (uint8_t)result != 0 )
  {
    fld_e1686 = *(this + 1686) + 1;
    *(this + 1686) = fld_e1686;
    v4 = fld_e1686 % 3;
    result = fld_e1686 / 3;
    if ( v4 == 0 )
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 33, 2);
      v5 = *(uint32_t *)dword_8F8520;
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);
      (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);
      v7 = *(uint32_t *)dword_8F8520;
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);
      (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
      return (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495430 sub_495430
// ------------------------------------------------------------
double /*cdecl*/ sub_495430(int nArg1, int nArg2, int nArg3)
{
  return (double)(4000 * nArg1) / ((double)(100 * nArg2 / nArg3 - 10000) * 0.0121 + 2100.0);
}



// ------------------------------------------------------------
// 0x495470 sub_495470
// ------------------------------------------------------------
char /*thiscall*/ sub_495470(int this, int nArg2)
{
  char result; // al

  result = *(uint8_t *)(this + 6668);
  if ( result != 0 )
  {
    *(uint32_t *)(this + 6672) = nArg2;
    return nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x495490 sub_495490
// ------------------------------------------------------------
char /*thiscall*/ sub_495490(int this, int nArg2)
{
  char result; // al

  result = *(uint8_t *)(this + 6681);
  if ( result != 0 )
  {
    result = *(uint8_t *)(this + 6682);
    if ( result != 0 )
    {
      *(uint32_t *)(this + 6684) = nArg2;
      return nArg2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4954C0 sub_4954C0
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4954C0(void *this)
{
  int pThis_330; // [esp+8h] [ebp-4h]

  pThis_330 = sub_41A5E0((unsigned int)this + 816);
  return (uint64_t)((double)pThis_330 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 830)));
}



// ------------------------------------------------------------
// 0x495500 sub_495500
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495500(void *this)
{
  int pThis_34C; // [esp+8h] [ebp-4h]

  pThis_34C = sub_41A5E0((unsigned int)this + 844);
  return (uint64_t)((double)pThis_34C * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 858)));
}



// ------------------------------------------------------------
// 0x495540 sub_495540
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495540(void *this)
{
  int pThis_368; // [esp+8h] [ebp-4h]

  pThis_368 = sub_41A5E0((unsigned int)this + 872);
  return (uint64_t)((double)pThis_368 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 886)));
}



// ------------------------------------------------------------
// 0x495580 sub_495580
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495580(void *this)
{
  int pThis_3BC; // [esp+8h] [ebp-4h]

  pThis_3BC = sub_41A5E0((unsigned int)this + 956);
  return (uint64_t)((double)pThis_3BC * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 970)));
}



// ------------------------------------------------------------
// 0x4955C0 sub_4955C0
// ------------------------------------------------------------
void /*thiscall*/ sub_4955C0(int *this, int pArg2, int nArg3)
{
  int pObj; // ecx

  pObj = *this;
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 && *(this + pArg2 + 7) != nArg3 )
  {
    *(this + pArg2 + 7) = nArg3;
    *((uint8_t *)this + 196) = 1;
    sub_494F60(this, pArg2, -1);
  }
}



// ------------------------------------------------------------
// 0x495600 sub_495600
// ------------------------------------------------------------
char /*thiscall*/ sub_495600(uint32_t *this, int pArg2, int nArg3, char pszArg4)
{
  uint8_t *fld_e28; // ebx
  uint32_t *fld_e282; // ebx
  char result; // al
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+18h] [ebp+8h]
  float v11; // [esp+18h] [ebp+8h]
  float fld_e1663; // [esp+20h] [ebp+10h]
  int v13; // [esp+20h] [ebp+10h]

  if ( pszArg4 != 0 )
    v10 = *(this + pArg2 + 1654);
  else
    v10 = *(this + pArg2 + 1652);
  v9 = *(this + pArg2 + 1656);
  fld_e1663 = 0.0;
  if ( nArg3 == 0 || nArg3 == 2 )
  {
    fld_e1663 = -1.0;
  }
  else if ( nArg3 == 1 || nArg3 == 3 )
  {
    fld_e1663 = 1.0;
  }
  if ( *(this + 1663) != 1000 )
    fld_e1663 = (double)(int)*(this + 1663) * fld_e1663 * 0.001;
  fld_e28 = (uint8_t *)*(this + 28);
  v11 = (double)v10 * fld_e1663;
  if ( *(uint32_t *)fld_e28 != 0
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)fld_e28 + 308))(*(uint32_t *)fld_e28) != 0
    && *(float *)&fld_e28[4 * pArg2 + 16] != v11 )
  {
    *(float *)&fld_e28[4 * pArg2 + 16] = v11;
    fld_e28[196] = 1;
  }
  fld_e282 = (uint32_t *)*(this + 28);
  v13 = (uint64_t)((double)v9 * fld_e1663);
  if ( *fld_e282 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e282 + 308))(*fld_e282) != 0 && fld_e282[pArg2 + 7] != v13 )
  {
    fld_e282[pArg2 + 7] = v13;
    *((uint8_t *)fld_e282 + 196) = 1;
    sub_494F60(fld_e282, pArg2, -1);
  }
  result = *((uint8_t *)this + pArg2 + 6632);
  if ( result != 0 )
  {
    sub_4A0600(pArg2);
    result = nArg3;
  }
  *(this + pArg2 + 1659) = nArg3;
  return result;
}



// ------------------------------------------------------------
// 0x495740 sub_495740
// ------------------------------------------------------------
int /*thiscall*/ sub_495740(void *this, int nArg2)
{
  int pThis_2A0; // esi
  int v3; // eax
  unsigned int v4; // ecx
  int pThis_2A02; // esi
  int64_t v6; // rax
  void *pThis_2A03; // eax

  switch ( nArg2 )
  {
    case 1:
      pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
      v3 = sub_41A5E0(pThis_2A0 + 816);
      v4 = pThis_2A0 + 830;
      return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0(v4)));
    case 2:
      pThis_2A02 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
      v3 = sub_41A5E0(pThis_2A02 + 844);
      v4 = pThis_2A02 + 858;
      return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0(v4)));
    case 3:
      LODWORD(v6) = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 900))(this, 3);
      break;
    case 4:
      pThis_2A03 = (void *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);
      LODWORD(v6) = sub_495540(pThis_2A03);
      break;
    default:
      LODWORD(v6) = 1000;
      break;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x4957F0 sub_4957F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4957F0(int *this, char pszArg2)
{
  int fld_e1666; // edi
  int fld_e29; // eax
  int v4; // eax
  int v6; // esi
  int v7; // [esp+14h] [ebp+8h]

  if ( pszArg2 != 0 )
  {
    fld_e1666 = -1500;
  }
  else
  {
    fld_e1666 = *(this + 1666);
    if ( fld_e1666 == 0 )
      goto LABEL_9;
  }
  fld_e29 = *(this + 29);
  if ( fld_e29 != 0 )
  {
    v4 = *(uint32_t *)(fld_e29 + 132);
    if ( v4 != 0 )
      fld_e1666 += *(this + 1669) + *(uint32_t *)(v4 + 1324);
  }
  if ( pszArg2 != 0 )
    return fld_e1666;
LABEL_9:
  v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);
  v7 = sub_41A5E0(v6 + 956);
  return (int)(fld_e1666 * (uint64_t)((double)v7 * COERCE_FLOAT(sub_41A5E0(v6 + 970)))) / 100;
}



// ------------------------------------------------------------
// 0x495890 sub_495890
// ------------------------------------------------------------
void /*thiscall*/ sub_495890(int *this, int nArg2, int nArg3)
{
  int fld_e29; // eax
  int fld_e1669; // edi
  int v6; // eax
  uint32_t *fld_e28; // esi

  *(this + 1665) = nArg2;
  if ( nArg2 == 1 )
  {
    fld_e29 = *(this + 29);
    fld_e1669 = -1500;
    if ( fld_e29 != 0 )
    {
      v6 = *(uint32_t *)(fld_e29 + 132);
      if ( v6 != 0 )
        fld_e1669 = *(uint32_t *)(v6 + 1324) + *(this + 1669) - 1500;
    }
  }
  else if ( nArg2 == 2 )
  {
    fld_e1669 = sub_4957F0(this, 0);
  }
  else
  {
    fld_e1669 = nArg3;
  }
  fld_e28 = (uint32_t *)*(this + 28);
  if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[9] != fld_e1669 )
  {
    fld_e28[9] = fld_e1669;
    *((uint8_t *)fld_e28 + 196) = 1;
    sub_494F60(fld_e28, 2, -1);
  }
}



// ------------------------------------------------------------
// 0x495920 sub_495920
// ------------------------------------------------------------
void /*thiscall*/ sub_495920(uint32_t *this)
{
  int fld_e1639; // eax
  int v3; // edi
  double v4; // st7
  int fld_e1665; // eax
  float fld_e1668; // [esp+4h] [ebp-8h]

  if ( *((uint8_t *)this + 6668) != 0 )
  {
    fld_e1639 = *(this + 1639);
    v3 = 0;
    if ( fld_e1639 == 4 || fld_e1639 == 9 || (int)*(this + 81) <= 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > 0 )
    {
      fld_e1668 = (double)(int)*(this + 1668) * 100.0;
      v4 = fld_e1668 / (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this);
      if ( v4 > 20.0 )
        v3 = (uint64_t)((v4 - 20.0) * -300.0);
      *((uint8_t *)this + 6680) = 1;
    }
    else if ( *((uint8_t *)this + 6680) != 0 )
    {
      if ( *((uint8_t *)this + 6668) != 0 )
        *(this + 1668) = 0;
      *((uint8_t *)this + 6680) = 0;
    }
    if ( *(this + 1669) != v3 )
    {
      fld_e1665 = *(this + 1665);
      *(this + 1669) = v3;
      if ( fld_e1665 == 1 || fld_e1665 == 2 )
        sub_495890(this, fld_e1665, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x495A10 sub_495A10
// ------------------------------------------------------------
void /*thiscall*/ sub_495A10(int *this, int nArg2)
{
  int fld_e30; // ecx
  uint32_t *fld_e32; // eax
  uint32_t *v5; // esi
  float v6; // [esp+0h] [ebp-Ch]
  float fld_e1664; // [esp+0h] [ebp-Ch]

  fld_e30 = *(this + 30);
  *(this + 1664) = nArg2;
  if ( fld_e30 != 0 )
  {
    v6 = (double)nArg2 * 0.1;
    sub_493D00(fld_e30, v6);
  }
  fld_e32 = (uint32_t *)*(this + 32);
  v5 = (uint32_t *)*fld_e32;
  if ( (uint32_t *)*fld_e32 != fld_e32 )
  {
    do
    {
      fld_e1664 = (double)*(this + 1664) * 0.1;
      sub_493D00(v5[3], fld_e1664);
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != (uint32_t *)*(this + 32) );
  }
}



// ------------------------------------------------------------
// 0x495A70 sub_495A70 —— 场景对象动画挂接（+1004 门控；v5==4 PVP 分流 aPvp_2 / v5==6 aWarroom，否则普通）
// ------------------------------------------------------------
char /*thiscall*/ sub_495A70(uint8_t *this, int nArg2, int ArgList, int nArg4)
{
  char result; // al
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax

  result = *(this + 1004);
  if ( result != 0 )
  {
    v5 = *(uint32_t *)(dword_8F7A24 + 12);
    if ( v5 == 4 )
    {
      if ( sub_48F5E0(nArg4) == -1 )
      {
        return off_77F3FC(aPvp_2, ArgList);
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg4);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg2);
        v6 = *(uint32_t *)dword_8F8520;
        v7 = sub_48F5E0(nArg4);
        return (*(int (/*thiscall*/ **)(int, int, int))(v6 + 60))(dword_8F8520, 1, v7);
      }
    }
    else if ( v5 == 6 )
    {
      if ( sub_48FCE0(nArg4) == -1 )
      {
        return off_77F3FC(aWarroom, ArgList);
      }
      else
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 0);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg4);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg2);
        v8 = *(uint32_t *)dword_8F8520;
        v9 = sub_48FCE0(nArg4);
        return (*(int (/*thiscall*/ **)(int, int, int))(v8 + 60))(dword_8F8520, 1, v9);
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 2);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg4);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg2);
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495C00 sub_495C00
// ------------------------------------------------------------
char /*thiscall*/ sub_495C00(uint8_t *this, int nArg2)
{
  char result; // al
  int pThis_360; // eax
  int v5; // edx
  int v6; // edx
  int v7; // edx

  result = *(this + 1004);
  if ( result != 0 )
  {
    result = dword_8F7A24;
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 4 )
    {
      pThis_360 = sub_41A5E0((unsigned int)(this + 864));
      sub_41A590((unsigned int)(this + 864), v5, nArg2 + pThis_360);
      sub_41A590((unsigned int)(this + 990), 1124859904, 1124859904);
      sub_41A590((unsigned int)(this + 892), v6, 1116471296);
      return sub_41A590((unsigned int)(this + 920), v7, 1116471296);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495C80 sub_495C80
// ------------------------------------------------------------
int /*thiscall*/ sub_495C80(char *this)
{
  void *pThis_3D0; // esi

  pThis_3D0 = this + 976;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)(this + 976))) >= 105.0 )
    return 105;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)pThis_3D0)) >= 95.0 )
    return 95;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)pThis_3D0)) >= 85.0 )
    return 85;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)pThis_3D0)) >= 70.0 )
    return 70;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)pThis_3D0)) >= 55.0 )
    return 55;
  if ( sub_43B5A0(pThis_3D0) >= 45.0 )
    return 45;
  if ( sub_43B5A0(pThis_3D0) >= 40.0 )
    return 40;
  if ( sub_43B5A0(pThis_3D0) < 35.0 )
    return 0;
  return 35;
}



// ------------------------------------------------------------
// 0x495DA0 sub_495DA0
// ------------------------------------------------------------
char */*thiscall*/ sub_495DA0(char *this, int nArg2)
{
  char *result; // eax

  result = this + 96 * nArg2;
  *((uint32_t *)result + 6) = 0;
  *((uint32_t *)result + 18) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x495DC0 sub_495DC0
// ------------------------------------------------------------
int /*thiscall*/ sub_495DC0(float *this)
{
  int i; // edi
  int pThis_D8; // eax
  uint32_t *pThis_D82; // ecx
  int v5; // edx
  int v6; // eax
  int pThis_D83; // eax
  double v8; // st7
  float *pThis_122; // ebx
  bool v10; // zf
  double v11; // st6
  uint32_t *pThis_D84; // ecx
  int v13; // edx
  int v14; // eax
  double v15; // st7
  float *v16; // ebx
  double v17; // st6
  int result; // eax
  bool v19; // cc
  uint32_t v20[3]; // [esp+Ch] [ebp-38h] BYREF
  uint32_t v21[3]; // [esp+1Ah] [ebp-2Ah] BYREF
  int v22; // [esp+28h] [ebp-1Ch]
  int v23; // [esp+2Ch] [ebp-18h]
  float *pThis_12; // [esp+30h] [ebp-14h]
  int v25; // [esp+34h] [ebp-10h]
  int v26; // [esp+40h] [ebp-4h]

  v25 = 0;
  memset(this + 192, 0, 0x60u);
  v23 = 12;
  pThis_12 = this + 18;
  do
  {
    for ( i = 0; i < 12; ++i )
    {
      pThis_D8 = sub_41A5E0((unsigned int)(this + 216));
      if ( i == 6 )
      {
        if ( pThis_D8 <= 1 )
        {
          sub_41A630((unsigned int)v21);
          v26 = 0;
          v21[0] = &clong::`vftable';
          sub_41A590((unsigned int)v21, v5, 1);
          v4 = v21;
          v26 = 1;
          v25 |= 1u;
        }
        else
        {
          v4 = this + 216;
        }
        v22 = sub_41A5E0((unsigned int)v4);
        v6 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v6 == 4 || v6 == 6 )
        {
          v8 = flt_790B4C;
        }
        else
        {
          v7 = sub_41A5E0((unsigned int)(this + 216));
          v8 = flt_790AEC;
          if ( v7 <= 10 )
            v8 = v8 * 0.33333334;
        }
        v9 = v24;
        v10 = (v25 & 1) == 0;
        v11 = *v24 / (double)v22;
        v26 = -1;
        *(this + 198) = v11 * v8 + *(this + 198);
        if ( !v10 )
        {
          v25 &= ~1u;
          sub_41A580(v21);
        }
        *(this + 210) = *(this + 210) + *v9;
      }
      else
      {
        if ( v3 <= 1 )
        {
          sub_41A630((unsigned int)v20);
          v26 = 2;
          v20[0] = &clong::`vftable';
          sub_41A590((unsigned int)v20, v13, 1);
          pThis_D84 = v20;
          v26 = 3;
          v25 |= 2u;
        }
        else
        {
          pThis_D84 = this + 216;
        }
        v22 = sub_41A5E0((unsigned int)pThis_D84);
        v14 = *(uint32_t *)(dword_8F7A24 + 12);
        if ( v14 == 4 || v14 == 6 )
          v15 = flt_790B34[i];
        else
          v15 = flt_790AD4[i];
        v16 = this + i + v23;
        v17 = flt_790B04[i] / (double)v22;
        v10 = (v25 & 2) == 0;
        v26 = -1;
        *(this + i + 192) = v17 * *v16 * v15 + *(this + i + 192);
        if ( !v10 )
        {
          v25 &= ~2u;
          sub_41A580(v20);
        }
        *(this + i + 204) = *(this + i + 204) + *v16;
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *(this + i + 192) > (double)flt_790B04[i] )
          *(this + i + 192) = flt_790B04[i];
      }
    }
    result = v23 + 24;
    v19 = v23 + 24 < 204;
    pThis_12 += 24;
    v23 += 24;
  }
  while ( v19 );
  return result;
}


// ------------------------------------------------------------
// 0x496010 sub_496010 —— 帧图像重载工厂（事件号 +48 → sub_495DC0 等）
// ------------------------------------------------------------
int /*thiscall*/ sub_496010(int this, int nArg2, int pArg3, int nArg4)
{
  int v4; // eax
  int result; // eax
  int v7; // eax
  int v8; // eax
  int fld_3CC; // eax
  int v10; // eax
  uint64_t pThis_38A3; // rax
  int v12; // eax
  int v13; // eax
  float fld_32C2; // [esp-8h] [ebp-18h]
  int pThis_38A32; // [esp-8h] [ebp-18h]
  int pThis_36E3; // [esp-8h] [ebp-18h]
  float pThis_36E2; // [esp+8h] [ebp-8h]
  float pThis_38A; // [esp+8h] [ebp-8h]
  float pThis_38A2; // [esp+Ch] [ebp-4h]
  float pThis_36E; // [esp+Ch] [ebp-4h]
  int v21; // [esp+18h] [ebp+8h]
  float fld_308; // [esp+20h] [ebp+10h]
  float fld_314; // [esp+20h] [ebp+10h]
  float pThis_3A6; // [esp+20h] [ebp+10h]
  float fld_32C; // [esp+20h] [ebp+10h]

  v4 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v4 == 4 )
  {
    result = dword_99FEC0;
    if ( dword_99FEC0 == 0 )
      return result;
    v7 = sub_48F5E0(nArg2);
  }
  else if ( v4 == 6 )
  {
    result = dword_99FF08;
    if ( dword_99FF08 == 0 )
      return result;
    v7 = sub_48FCE0(nArg2);
  }
  else
  {
    result = sub_429830(nArg2);
    if ( result == 0 )
      return result;
    result = sub_429830(nArg2);
    if ( *(uint32_t *)(result + 196) == 0 )
      return result;
    v8 = sub_429830(nArg2);
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 196) + 1216))(*(uint32_t *)(v8 + 196));
  }
  v21 = v7;
  *(float *)(this + 4 * (pArg3 + 24 * v7) + 48) = (double)nArg4 + *(float *)(this + 4 * (pArg3 + 24 * v7) + 48);
  sub_495DC0(this);
  fld_308 = *(float *)(this + 776) + *(float *)(this + 772) + *(float *)(this + 768);
  sub_41A590(LODWORD(fld_308));
  fld_314 = *(float *)(this + 788) + *(float *)(this + 784) + *(float *)(this + 780);
  sub_41A590(LODWORD(fld_314));
  sub_41A590(*(uint32_t *)(this + 792));
  sub_41A590(*(uint32_t *)(this + 840));
  if ( *(uint32_t *)(this + 964) != -956156672 )
    sub_41A590(*(uint32_t *)(this + 964));
  if ( *(uint32_t *)(this + 968) != -956156672 )
    sub_41A590(*(uint32_t *)(this + 968));
  fld_3CC = *(uint32_t *)(this + 972);
  if ( fld_3CC != -956156672 )
    sub_41A590(fld_3CC);
  v10 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v10 == 4 || v10 == 6 )
  {
    pThis_36E = COERCE_FLOAT(sub_41A5E0(this + 878));
    pThis_38A = COERCE_FLOAT(sub_41A5E0(this + 906));
    fld_32C = *(float *)(this + 812)
        + *(float *)(this + 808)
        + *(float *)(this + 804)
        + *(float *)(this + 800)
        + *(float *)(this + 796)
        + COERCE_FLOAT(sub_41A5E0(this + 934))
        + pThis_38A
        + pThis_36E;
    fld_32C2 = fld_32C;
  }
  else
  {
    pThis_36E2 = COERCE_FLOAT(sub_41A5E0(this + 878));
    pThis_38A2 = COERCE_FLOAT(sub_41A5E0(this + 906));
    pThis_3A6 = COERCE_FLOAT(sub_41A5E0(this + 934)) + pThis_38A2 + pThis_36E2;
    fld_32C2 = pThis_3A6;
  }
  sub_41A590(LODWORD(fld_32C2));
  if ( COERCE_FLOAT(sub_41A5E0(this + 976)) < 0.0 )
    sub_41A590(0);
  result = dword_8F8500;
  if ( dword_8F8500 != 0 )
  {
    result = sub_456420(dword_8F850C);
    if ( result == v21 && dword_8F8520 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
      if ( result != 0 )
      {
        result = pArg3;
        switch ( pArg3 )
        {
          case 0:
          case 1:
          case 2:
            pThis_36E3 = (uint64_t)sub_43B5A0(this + 878);
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
            result = sub_426820(v13, 6, pThis_36E3);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
            break;
          case 3:
          case 4:
          case 5:
            pThis_38A3 = (uint64_t)sub_43B5A0(this + 906);
            pThis_38A32 = pThis_38A3;
            v12 = (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520, HIDWORD(pThis_38A3));
            result = sub_426820(v12, 7, pThis_38A32);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
            break;
          default:
            return result;
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x496320 sub_496320
// ------------------------------------------------------------
int /*thiscall*/ sub_496320(void *this)
{
  int v3; // [esp+4h] [ebp-Ch] BYREF
  uint16_t v4[3]; // [esp+8h] [ebp-8h] BYREF
  uint8_t v5; // [esp+Fh] [ebp-1h] BYREF

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, v4);
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v5);
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v3);
  if ( v4[0] == (uint16_t)word_77F804
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104) != 0 )
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    if ( (uint8_t)sub_45E680(dword_8F7C04) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 1208))(dword_8F7C04, v5, v3);
  }
  return sub_496010((int)this, v4[0], v5, v3);
}



// ------------------------------------------------------------
// 0x4963E0 sub_4963E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4963E0(uint32_t *this)
{
  uint32_t *pThis_3; // ecx
  unsigned int v3; // edx
  uint32_t *v4; // edi
  uint32_t *v5; // ebx
  uint32_t v7[5]; // [esp+Ch] [ebp-14h] BYREF

  pThis_3 = this + 3;
  pThis_3[6] = 15;
  pThis_3[5] = 0;
  v7[1] = this;
  *((uint8_t *)pThis_3 + 4) = 0;
  *this = -1;
  *(this + 1) = -1;
  *(this + 2) = 0;
  v3 = pThis_3[6];
  v7[4] = 0;
  v4 = pThis_3 + 1;
  if ( v3 < 0x10 )
    v5 = pThis_3 + 1;
  else
    v5 = (uint32_t *)*v4;
  if ( v3 >= 0x10 )
    v4 = (uint32_t *)*v4;
  sub_406D00(pThis_3, v7, (int)v4, (unsigned int)v5 + pThis_3[5]);
  return this;
}



// ------------------------------------------------------------
// 0x496470 sub_496470
// ------------------------------------------------------------
int /*cdecl*/ sub_496470(int nArg1, int nArg2, int nArg3)
{
  int nArg12; // esi
  int result; // eax
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  nArg12 = nArg1;
  v6[4] = v6;
  v6[3] = nArg1;
  v6[7] = 0;
  while ( nArg2 != 0 )
  {
    result = sub_459690(nArg12, nArg3);
    --nArg2;
    nArg12 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x496510 sub_496510
// ------------------------------------------------------------
int /*stdcall*/ sub_496510(int nArg1, int nArg2, int nArg3)
{
  sub_496470(nArg1, nArg2, nArg3);
  return nArg1 + 40 * nArg2;
}



// ============================================================
// §J 0x496540-0x497EA0  异常状态演出表（Common/ActiveStatus/*.ani|ptl）
// ============================================================
// ------------------------------------------------------------
// 0x496540 sub_496540
// ------------------------------------------------------------
void /*thiscall*/ sub_496540(int *this, char *pszArg2, unsigned int uArg3, int *pDwArg4)
{
  int v4; // edx
  int v6; // ecx
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v12; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  uint32_t *fld_e28; // ecx
  int fld_e13; // eax
  unsigned int v17; // edi
  void *fld_e14; // eax
  char *fld_e23; // ecx
  int fld_e26; // edi
  uint32_t *fld_e12; // [esp-18h] [ebp-6Ch]
  int fld_e25; // [esp-Ch] [ebp-60h]
  unsigned int fld_e24; // [esp-8h] [ebp-5Ch]
  int v25; // [esp+0h] [ebp-54h] BYREF
  void *Block; // [esp+Ch] [ebp-48h]
  int *pThis; // [esp+10h] [ebp-44h]
  char *pMem2; // [esp+14h] [ebp-40h]
  uint32_t v29[3]; // [esp+18h] [ebp-3Ch] BYREF
  char v30[4]; // [esp+24h] [ebp-30h] BYREF
  void *v31; // [esp+28h] [ebp-2Ch]
  int v32; // [esp+38h] [ebp-1Ch]
  unsigned int v33; // [esp+3Ch] [ebp-18h]
  int dword_796E502; // [esp+40h] [ebp-14h]
  int *v35; // [esp+44h] [ebp-10h]
  int v36; // [esp+50h] [ebp-4h]
  char *v37; // [esp+5Ch] [ebp+8h]
  int v38; // [esp+60h] [ebp+Ch]
  char *fld_e232; // [esp+64h] [ebp+10h]

  dword_796E502 = dword_796E50;
  v4 = pDwArg4[1];
  v6 = *pDwArg4;
  v35 = &v25;
  v29[0] = v6;
  v29[2] = pDwArg4[2];
  pThis = this;
  v29[1] = v4;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0((std::_String_base *)v30, pDwArg4 + 3, 0, -1);
  fld_e1 = *(this + 1);
  v36 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 40;
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 40;
    else
      fld_e2 = 0;
    if ( 107374182 - fld_e2 < uArg3 )
      sub_434730(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 40;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (char *)*(this + 2);
      fld_e232 = fld_e23;
      if ( (fld_e23 - pszArg2) / 40 >= uArg3 )
      {
        v37 = &fld_e23[-40 * uArg3];
        *(this + 2) = sub_459860(v37, fld_e23, (int)fld_e23);
        sub_572550(pszArg2, v37, fld_e232);
        sub_570610(pszArg2, &pszArg2[40 * uArg3], v29);
      }
      else
      {
        sub_459860(pszArg2, fld_e23, (int)&pszArg2[40 * uArg3]);
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 40;
        fld_e25 = *(this + 2);
        LOBYTE(v36) = 3;
        sub_496510(fld_e25, fld_e24, v29);
        fld_e26 = 40 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v36 = 0;
        sub_570610(pszArg2, fld_e26 - 40 * uArg3, v29);
      }
    }
    else
    {
      if ( 107374182 - (fld_e3 >> 1) >= fld_e3 )
        v12 = (fld_e3 >> 1) + fld_e3;
      else
        v12 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 40;
      else
        fld_e27 = 0;
      if ( v12 < uArg3 + fld_e27 )
        v12 = uArg3 + sub_5721D0(this);
      v38 = 40 * v12;
      pMem = (char *)operator new(40 * v12);
      fld_e12 = (uint32_t *)*(this + 1);
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;
      pMem2 = (char *)sub_459860(fld_e12, pszArg2, (int)pMem);
      sub_496470((int)pMem2, uArg3, v29);
      fld_e28 = (uint32_t *)*(this + 2);
      pMem2 += 40 * uArg3;
      sub_459860(pszArg2, fld_e28, (int)pMem2);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 40;
      v17 = fld_e13 + uArg3;
      fld_e14 = (void *)*(this + 1);
      if ( fld_e14 != nullptr )
      {
        sub_55A010(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v38];
      *(this + 2) = (int)&pMem[40 * v17];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v33 >= 0x10 )
    j__free(v31);
}


// ------------------------------------------------------------
// 0x496870 sub_496870
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_496870(int *this, uint32_t *uArg2, int nArg3, uint32_t *uArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 40 != 0 )
    v6 = (nArg3 - fld_e1) / 40;
  else
    v6 = 0;
  sub_496540(this, nArg3, 1u, uArg4);
  *uArg2 = *(this + 1) + 40 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4968E0 sub_4968E0
// ------------------------------------------------------------
int /*fastcall*/ sub_4968E0(int pArg1, int nArg2)
{
  int v3; // eax
  int v4; // edx
  int v5; // edx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx
  char *v15; // edi
  char *i; // ebx
  char *v17; // edi
  char *j; // ebx

  memset((void *)pArg1, 0, 0x300u);
  memset((void *)(pArg1 + 768), 0, 0x60u);
  v3 = *(uint32_t *)(dword_8F7A24 + 12);
  if ( v3 == 4 || v3 == 6 )
  {
    sub_41A590(pArg1 + 976, nArg2, 0);
    sub_41A590(pArg1 + 864, v9, 0);
    sub_41A590(pArg1 + 934, v10, 0);
    sub_41A590(pArg1 + 906, 0, 0);
    sub_41A590(pArg1 + 878, v11, 0);
    sub_41A590(pArg1 + 892, v12, -1082130432);
    sub_41A590(pArg1 + 920, -1082130432, -1082130432);
    sub_41A590(pArg1 + 990, v13, -1082130432);
    sub_41A590(pArg1 + 948, v14, 0);
  }
  else
  {
    sub_41A590(pArg1 + 990, nArg2, 0);
    sub_41A590(pArg1 + 920, 0, 0);
    sub_41A590(pArg1 + 892, v4, 0);
    sub_41A590(pArg1 + 976, v5, 0);
    sub_41A590(pArg1 + 864, v6, 0);
    sub_41A590(pArg1 + 934, 0, 0);
    sub_41A590(pArg1 + 906, v7, 0);
    sub_41A590(pArg1 + 878, v8, 0);
    sub_41A590(pArg1 + 948, 0, 0);
  }
  v15 = *(char **)(pArg1 + 1012);
  if ( v15 != nullptr )
  {
    for ( i = *(char **)(pArg1 + 1016); v15 != i; v15 += 40 )
      sub_5014C0(v15);
    j__free(*(void **)(pArg1 + 1012));
  }
  *(uint32_t *)(pArg1 + 1012) = 0;
  *(uint32_t *)(pArg1 + 1016) = 0;
  *(uint32_t *)(pArg1 + 1020) = 0;
  v17 = *(char **)(pArg1 + 1028);
  if ( v17 != nullptr )
  {
    for ( j = *(char **)(pArg1 + 1032); v17 != j; v17 += 40 )
      sub_5014C0(v17);
    j__free(*(void **)(pArg1 + 1028));
  }
  *(uint32_t *)(pArg1 + 1028) = 0;
  *(uint32_t *)(pArg1 + 1032) = 0;
  *(uint32_t *)(pArg1 + 1036) = 0;
  *(uint32_t *)(pArg1 + 964) = -956156672;
  *(uint32_t *)(pArg1 + 968) = -956156672;
  *(uint32_t *)(pArg1 + 972) = -956156672;
  return -956156672;
}



// ------------------------------------------------------------
// 0x496B40 sub_496B40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_496B40(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 40;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 40 )
    return sub_496870(this, &uArg2, *(this + 2), uArg2);
  fld_e22 = *(this + 2);
  result = (uint32_t *)sub_496470(fld_e22, 1, (int)uArg2);
  *(this + 2) = fld_e22 + 40;
  return result;
}



// ------------------------------------------------------------
// 0x496BD0 sub_496BD0
// ------------------------------------------------------------
void /*thiscall*/ sub_496BD0(int *this, uint32_t *pArg2)
{
  int v3; // ebx
  int v4; // eax
  int v5; // eax
  int v6; // edx
  uint32_t *v7; // eax
  int v8; // edx
  int v9; // eax
  int v10; // esi
  uint32_t v11[3]; // [esp+Ch] [ebp-38h] BYREF
  size_t v12[6]; // [esp+18h] [ebp-2Ch] BYREF
  unsigned int v13; // [esp+30h] [ebp-14h]
  int dword_796E502; // [esp+34h] [ebp-10h]
  int v15; // [esp+40h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 376))(pArg2);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != v3 )
  {
    sub_4963E0(v11);
    v4 = *pArg2;
    v15 = 0;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 1032))(pArg2);
    v6 = *pArg2;
    v11[2] = *(uint32_t *)(v5 + 68);
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(v6 + 340))(pArg2);
    v8 = *pArg2;
    v11[1] = *v7;
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 340))(pArg2);
    sub_4014D0(v12, (size_t *)(v9 + 4), 0, 0xFFFFFFFF);
    v11[0] = pArg2[1943];
    if ( v11[0] == 3 )
    {
      sub_496B40(this + 252, v11);
    }
    else
    {
      v10 = pArg2[1943];
      if ( v10 != 1 && v10 != 2 )
      {
        if ( v13 < 0x10 )
          return;
        goto LABEL_10;
      }
      sub_496B40(this + 256, v11);
    }
    if ( v13 < 0x10 )
      return;
LABEL_10:
    j__free((void *)v12[1]);
  }
}



// ------------------------------------------------------------
// 0x496CE0 sub_496CE0 —— 播放状态对象复位（+104=4、+104..120 连续 5 格 1065353216=1.0f）
// ------------------------------------------------------------
int /*thiscall*/ sub_496CE0(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 17;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 56) = 0;
  sub_699070(1);  // 【clock_bind_domain(clk, newDomainId)】
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint8_t *)(this + 96) = 0;
  *(uint8_t *)(this + 97) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;
  *(uint8_t *)(this + 204) = 0;
  *(uint32_t *)(this + 100) = 4;
  *(uint32_t *)(this + 104) = 1065353216;
  *(uint32_t *)(this + 108) = 1065353216;
  *(uint32_t *)(this + 112) = 1065353216;
  *(uint32_t *)(this + 116) = 1065353216;
  *(uint32_t *)(this + 120) = 1065353216;
  return 1065353216;
}



// ------------------------------------------------------------
// 0x496DA0 sub_496DA0
// ------------------------------------------------------------
char /*thiscall*/ sub_496DA0(uint32_t *this, int nArg2)
{
  int pThis_F; // esi

  pThis_F = (int)(this + 15);
  sub_698FE0((int)(this + 15));  // 【clock_unfreeze(clk)】
  *(uint8_t *)(pThis_F + 13) = 0;
  *(uint8_t *)(pThis_F + 14) = 0;
  *(this + 23) = nArg2;
  return sub_698F90(pThis_F, nArg2, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x496DD0 sub_496DD0
// ------------------------------------------------------------
void /*cdecl*/ sub_496DD0(char pszArg1)
{
  int dword_8F7C042; // esi
  uint32_t *v2; // ebx
  int v3; // ebx
  int v4; // edi
  int v5; // edi
  int v6; // ebx
  int pObj2; // ecx
  int v8; // esi
  int v9; // ecx
  int v10; // edi
  int pObj; // edx
  int v12; // eax
  int v13; // [esp+4h] [ebp-Ch]
  unsigned int v14; // [esp+8h] [ebp-8h]
  int v15; // [esp+Ch] [ebp-4h]

  dword_8F7C042 = dword_8F7C04;
  if ( dword_8F7C04 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 80))(dword_8F7C04) != 0 )
  {
    if ( dword_9A0130[0] == 0 )
    {
      v2 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(
                       dword_8F84B8,
                       "Common/ActiveStatus/Blind1.img");
      dword_9A0130[0] = sub_418DD0(v2, 0);
      dword_9A0134 = sub_418DD0(v2, 1u);
      dword_9A0138 = sub_418DD0(v2, 2u);
    }
    v3 = sub_4239A0(dword_8F7C042);
    if ( pszArg1 != 0 )
      v4 = sub_4239D0(dword_8F7C042, 0.0);
    else
      v4 = sub_4239D0(dword_8F7C042, 1.0);
    v5 = v4 - 345;
    v6 = v3 - 245;
    v15 = v5;
    pObj2 = dword_9A0130[pszArg1 == 0];
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v6, v5, dword_79C0B0);
    v8 = v6;
    v14 = v6;
    v9 = v5;
    if ( v6 > 0 )
    {
      v14 = v6 - 50 * ((v6 - 1) / 0x32u + 1);
      v8 = v14;
    }
    if ( v5 > 0 )
      v9 = v5 - 50 * ((v5 - 1) / 0x32u + 1);
    v10 = v9;
    if ( v9 < 480 )
    {
      pObj = dword_9A0138;
      v13 = v9;
      do
      {
        v12 = v8;
        if ( v8 < 640 )
        {
          do
          {
            if ( (v12 < v6 || v12 >= v6 + 500 || v10 < v15 || v10 >= v15 + 500) && pObj != 0 )
            {
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(dword_9A0138, v12, v10, dword_79C0B0);
              pObj = dword_9A0138;
            }
            v8 += 50;
            v12 = v8;
          }
          while ( v8 < 640 );
          v8 = v14;
          v9 = v13;
        }
        v9 += 50;
        v13 = v9;
        v10 = v9;
      }
      while ( v9 < 480 );
    }
  }
}



// ------------------------------------------------------------
// 0x496F80 sub_496F80
// ------------------------------------------------------------
int /*cdecl*/ sub_496F80(int nArg1)
{
  int result; // eax

  switch ( nArg1 )
  {
    case 0:
      result = 0;
      break;
    case 1:
      result = 1;
      break;
    case 2:
      result = 2;
      break;
    case 3:
      result = 3;
      break;
    case 4:
      result = 4;
      break;
    case 5:
      result = 5;
      break;
    case 6:
      result = 6;
      break;
    case 7:
      result = 7;
      break;
    case 8:
      result = 8;
      break;
    case 9:
      result = 9;
      break;
    case 10:
      result = 10;
      break;
    case 11:
      result = 11;
      break;
    case 15:
      result = 14;
      break;
    case 16:
      result = 15;
      break;
    default:
      result = 16;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x497040 sub_497040
// ------------------------------------------------------------
int /*cdecl*/ sub_497040(int nArg1)
{
  int result; // eax

  switch ( nArg1 )
  {
    case 0:
      result = 0;
      break;
    case 1:
      result = 1;
      break;
    case 2:
      result = 2;
      break;
    case 3:
      result = 3;
      break;
    case 4:
      result = 4;
      break;
    case 5:
      result = 5;
      break;
    case 6:
      result = 6;
      break;
    case 7:
      result = 7;
      break;
    case 8:
      result = 8;
      break;
    case 9:
      result = 9;
      break;
    case 10:
      result = 10;
      break;
    case 11:
      result = 11;
      break;
    case 14:
      result = 15;
      break;
    case 15:
      result = 16;
      break;
    default:
      result = 17;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x497100 ?_Get_future_error_what@std@@YAPBDH@Z_0
// ------------------------------------------------------------
const char */*cdecl*/ std::_Get_future_error_what(int nArg1)
{
  return (const char *)dword_9A0140[nArg1];
}



// ------------------------------------------------------------
// 0x497110 sub_497110
// ------------------------------------------------------------
int /*thiscall*/ sub_497110(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 84))(this);
}



// ------------------------------------------------------------
// 0x497120 sub_497120
// ------------------------------------------------------------
int /*cdecl*/ sub_497120(int pArg1, int nArg2)
{
  return sub_4049C0(*(&flt_6CB268 + 2 * pArg1), flt_6CB26C[2 * pArg1], nArg2 - 1, 39);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
}



// ------------------------------------------------------------
// 0x497150 sub_497150
// ------------------------------------------------------------
void /*cdecl*/ sub_497150(int pArg1, int nArg2)
{
  sub_4049C0(*(&flt_6CB2F0 + 2 * pArg1), flt_6CB2F4[2 * pArg1], nArg2 - 1, 39);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
}



// ------------------------------------------------------------
// 0x497190 sub_497190
// ------------------------------------------------------------
char /*thiscall*/ sub_497190(int *this)
{
  return sub_4939E0(*(this + 5), sub_497180 != nullptr);
}



// ------------------------------------------------------------
// 0x4971B0 sub_4971B0
// ------------------------------------------------------------
int /*cdecl*/ sub_4971B0(int pArg1, int nArg2, int nArg3)
{
  int v3; // edi
  unsigned int v4; // eax
  int v5; // ebx
  int v6; // esi
  float v8; // [esp+4h] [ebp-Ch]
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+Ch] [ebp-4h]
  int v11; // [esp+18h] [ebp+8h]

  v3 = 0;
  v10 = 0;
  switch ( pArg1 )
  {
    case 0:
    case 2:
    case 4:
    case 6:
    case 9:
    case 11:
    case 12:
    case 13:
      v3 = 1000 * dword_6CB220[pArg1];
      goto LABEL_5;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 15:
    case 16:
      v3 = (uint64_t)(sub_4049C0(*(&flt_6CB268 + 2 * pArg1), flt_6CB26C[2 * pArg1], nArg2 - 1, 39) * 1000.0);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      goto LABEL_5;
    case 10:
    case 14:
      v3 = 0;
LABEL_5:
      v10 = v3;
      break;
    default:
      break;
  }
  if ( nArg3 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 529) != 0 )
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 684))(nArg3);
    sub_41A5E0(v4);
    v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 672))(nArg3, 3);
    v9 = sub_41A5E0(v5 + 4);
    v8 = COERCE_FLOAT(sub_41A5E0(v5 + 18));
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 672))(nArg3, 3);
    v11 = sub_41A5E0(v6 + 4);
    v3 -= (uint64_t)((double)((int)(uint64_t)((double)v11 * COERCE_FLOAT(sub_41A5E0(v6 + 18)))
                                    / 2
                                    / (int)(uint64_t)((double)v9 * v8))
                           * (double)v10);
  }
  if ( v3 >= 0 )
    return v3;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x497300 sub_497300
// ------------------------------------------------------------
int /*thiscall*/ sub_497300(int *this, int ArgList, int nArg3)
{
  int fld_e3; // ebx
  unsigned int fld_e23; // edi
  int v7; // edi
  int fld_e2; // eax
  int v9; // ecx

  fld_e3 = *(this + 3);
  *(this + 3) = ArgList;
  if ( ArgList > 40 )
  {
    off_77F3FC((char *)&byte_6CB378, ArgList, 40);
    *(this + 3) = 40;
  }
  *(this + 4) = nArg3;
  if ( ArgList > 0 )
  {
    v7 = *this;
    fld_e2 = sub_4971B0(*(this + 2), *(this + 3), *(this + 1));
    (*(void (/*thiscall*/ **)(int *, int))(v7 + 84))(this, fld_e2);
    LOBYTE(v9) = fld_e3 == 0;
    (*(void (/*thiscall*/ **)(int *, int))(*this + 60))(this, v9);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 676))(*(this + 1), 1);
  }
  else
  {
    fld_e23 = *(this + 23);
    if ( fld_e23 > sub_699000((int)(this + 15)) && *(this + 2) == 7 )  // 【clock_now(clk)】
      *(this + 22) = fld_e23;
    (*(void (/*thiscall*/ **)(int *))(*this + 64))(this);
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 676))(*(this + 1), 1);
  }
}



// ------------------------------------------------------------
// 0x4973B0 sub_4973B0
// ------------------------------------------------------------
void /*thiscall*/ sub_4973B0(int this, char pszArg2)
{
  int pThis_3C; // ecx
  int *pThis_14; // esi
  int i; // edi
  int *pThis_142; // esi
  int j; // edi
  int *pThis_143; // esi
  int k; // edi

  if ( *(uint8_t *)(this + 96) != pszArg2 )
  {
    *(uint8_t *)(this + 96) = pszArg2;
    pThis_3C = this + 60;
    if ( pszArg2 != 0 )
      sub_699030(pThis_3C);  // 【clock_freeze(clk)】
    else
      sub_698FE0(pThis_3C);  // 【clock_unfreeze(clk)】
    switch ( *(uint32_t *)(this + 8) )
    {
      case 0:
        sub_4939E0(*(uint32_t *)(this + 20), 1);
        break;
      case 1:
        pThis_14 = (int *)(this + 20);
        for ( i = 3; i != 0; --i )
          sub_4939E0(*pThis_14++, pszArg2);
        break;
      case 3:
        pThis_142 = (int *)(this + 20);
        for ( j = 2; j != 0; --j )
          sub_4939E0(*pThis_142++, pszArg2);
        break;
      case 5:
        pThis_143 = (int *)(this + 20);
        for ( k = 2; k != 0; --k )
          sub_4939E0(*pThis_143++, pszArg2);
        break;
      case 6:
      case 8:
      case 0xC:
        sub_4939E0(*(uint32_t *)(this + 20), pszArg2);
        break;
      case 7:
        sub_497190(this);
        break;
      case 0xF:
        sub_4939E0(*(uint32_t *)(this + 20), pszArg2);
        sub_4939E0(*(uint32_t *)(this + 24), pszArg2);
        break;
      case 0x10:
        sub_4939E0(*(uint32_t *)(this + 20), pszArg2);
        sub_4939E0(*(uint32_t *)(this + 24), pszArg2);
        sub_4939E0(*(uint32_t *)(this + 28), pszArg2);
        break;
      default:
        return;
    }
  }
}



// ------------------------------------------------------------
// 0x497500 sub_497500
// ------------------------------------------------------------
int /*thiscall*/ sub_497500(char *this)
{
  int (/*thiscall*/ ****pThis_28)(uint32_t, int); // esi
  int i; // ebx
  int v3; // edi
  int result; // eax
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  bool v6; // zf

  pThis_28 = (int (/*thiscall*/ ****)(uint32_t, int))(this + 40);
  for ( i = 5; i != 0; --i )
  {
    v3 = (int)*(pThis_28 - 5);
    if ( v3 != 0 )
    {
      sub_42AF90((void **)*(pThis_28 - 5));
      result = sub_657740(v3, 228);
    }
    v5 = *pThis_28;
    v6 = *pThis_28 == nullptr;
    *(pThis_28 - 5) = nullptr;
    if ( !v6 )
      result = (**v5)(v5, 1);
    *pThis_28++ = nullptr;
  }
  return result;
}



// ------------------------------------------------------------
// 0x497560 sub_497560 —— 石化状态演出装配（StoneCurse.ani + StoneCursing/StoneCurseDestroy.ptl 挂帧 +40/+44）
// ------------------------------------------------------------
float */*thiscall*/ sub_497560(int this)
{
  int v2; // eax
  int fld_4; // ecx
  float *result; // eax
  int fld_42; // eax
  double v6; // st7
  float fld_74; // eax
  uint32_t *fld_14; // ecx
  uint32_t *pMem; // eax
  uint32_t *v10; // eax
  uint32_t *pMem2; // eax
  float Block; // [esp+4h] [ebp-10h]

  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/StoneCurse.ani", 1);
  else
    v2 = 0;
  fld_4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 20) = v2;
  result = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 688))(fld_4);
  if ( *((uint32_t *)result + 3) != 0 )
  {
    result = (float *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));
    if ( *((uint32_t *)result + 3) != 0 )
    {
      fld_42 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));
      result = (float *)sub_4924C0(*(int **)(fld_42 + 12), 0);
      if ( result != nullptr && *(uint32_t *)result != 0 )
      {
        *(float *)(this + 116) = (double)*(unsigned int *)(*(uint32_t *)result + 20) * result[5] * 0.016666668;
        v6 = (double)*(unsigned int *)(*(uint32_t *)result + 24) * result[6];
        fld_74 = *(float *)(this + 116);
        fld_14 = *(uint32_t **)(this + 20);
        Block = v6 * 0.016666668;
        *(float *)(this + 120) = Block;
        sub_4920E0(fld_14, fld_74, Block);
        pMem = operator new(0x12Cu);
        if ( pMem != nullptr )
          v10 = sub_428F30(pMem, (int)"Common/ActiveStatus/Particle/StoneCursing.ptl", 0);
        else
          v10 = nullptr;
        *(uint32_t *)(this + 40) = v10;
        pMem2 = operator new(0x12Cu);
        if ( pMem2 != nullptr )
        {
          result = (float *)sub_428F30(pMem2, (int)"Common/ActiveStatus/Particle/StoneCurseDestroy.ptl", 0);
          *(uint32_t *)(this + 44) = result;
        }
        else
        {
          *(uint32_t *)(this + 44) = 0;
          return nullptr;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4976E0 sub_4976E0 —— 冰冻状态演出装配（Freeze1/2/3.ani 按强度分档）
// ------------------------------------------------------------
float */*thiscall*/ sub_4976E0(int this)
{
  int v2; // eax
  uint32_t **pThis_14; // edi
  int v4; // eax
  int v5; // eax
  int fld_4; // ecx
  float *result; // eax
  int fld_42; // eax
  int v9; // ebx

  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze1.ani", 1);
  else
    v2 = 0;
  pThis_14 = (uint32_t **)(this + 20);
  *(uint32_t *)(this + 20) = v2;
  if ( sub_42FCB0(228) != 0 )
    v4 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze2.ani", 1);
  else
    v4 = 0;
  *(uint32_t *)(this + 24) = v4;
  if ( sub_42FCB0(228) != 0 )
    v5 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze3.ani", 1);
  else
    v5 = 0;
  fld_4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(this + 28) = v5;
  result = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 688))(fld_4);
  if ( *((uint32_t *)result + 3) != 0 )
  {
    fld_42 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));
    result = (float *)sub_4924C0(*(int **)(fld_42 + 12), 0);
    if ( result != nullptr && *(uint32_t *)result != 0 )
    {
      *(float *)(this + 108) = (double)*(unsigned int *)(*(uint32_t *)result + 20) * result[5] * 0.0076923077;
      v9 = 3;
      *(float *)(this + 112) = (double)*(unsigned int *)(*(uint32_t *)result + 24) * result[6] * 0.0071428572;
      do
      {
        result = (float *)sub_4920E0(*pThis_14++, *(float *)(this + 108), *(float *)(this + 112));
        --v9;
      }
      while ( v9 != 0 );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x497840 sub_497840 —— ★异常状态→动画/粒子 装配总表
//   Slow→Stun1/2→Curse→Blind1/2→Lightning→Sleep→Burn→Bleeding(+12Age)→Haste→
//   Bless1/2→Confuse(+Glow)→Hold；+244 状态槽；共用 sub_42FCB0/431860 图像创建。
// ------------------------------------------------------------
void /*thiscall*/ sub_497840(int *this, void *Block, int nArg3)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int fld_e5; // ecx
  int v10; // edi
  int nRand; // eax
  int fld_e6; // edi
  int nRand2; // eax
  int fld_e7; // edi
  int nRand3; // eax
  uint32_t *pMem; // eax
  int v17; // eax
  uint32_t *pMem2; // eax
  uint32_t *fld_e1; // eax
  int fld_e12; // ecx
  int v21; // eax
  uint32_t *pMem3; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // ecx
  uint32_t *pMem4; // eax
  uint32_t *fld_e15; // eax
  int fld_e16; // ecx

  *(this + 2) = (int)Block;
  *(this + 1) = nArg3;
  switch ( (unsigned int)Block )
  {
    case 0u:
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Slow.ani", 1);
      goto LABEL_62;
    case 1u:
      sub_4976E0(this);
      return;
    case 2u:
      pMem = operator new(0x12Cu);
      if ( pMem != nullptr )
        *(this + 10) = (int)sub_428F30(pMem, (int)"Common/ActiveStatus/Particle/PoisonParticle.ptl", *(this + 1));
      else
        *(this + 10) = 0;
      return;
    case 3u:
      if ( sub_42FCB0(228) != 0 )
        v17 = sub_431860((char)"Common/ActiveStatus/Animation/Stun1.ani", 1);
      else
        v17 = 0;
      *(this + 5) = v17;
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_44;
      *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/Stun2.ani", 1);
      return;
    case 4u:
      pMem2 = operator new(0x12Cu);
      if ( pMem2 != nullptr )
        fld_e1 = sub_428F30(pMem2, (int)"Common/ActiveStatus/Particle/CurseParticle.ptl", *(this + 1));
      else
        fld_e1 = nullptr;
      fld_e12 = *(this + 1);
      *(this + 10) = (int)fld_e1;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e1 + 112))(fld_e1, fld_e12);
      return;
    case 5u:
      if ( sub_42FCB0(228) != 0 )
        v21 = sub_431860((char)"Common/ActiveStatus/Animation/Blind1.ani", 1);
      else
        v21 = 0;
      *(this + 5) = v21;
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_44;
      *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/Blind2.ani", 1);
      return;
    case 6u:
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Lightning.ani", 1);
      goto LABEL_62;
    case 7u:
      sub_497560(this);
      return;
    case 8u:
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Sleep.ani", 1);
      goto LABEL_62;
    case 9u:
      if ( sub_42FCB0(228) != 0 )
        v5 = sub_431860((char)"Common/ActiveStatus/Animation/ActiveStatus_BurnDamage_Effect.ani", 1);
      else
        v5 = 0;
      *(this + 25) = 0;
      goto LABEL_62;
    case 0xBu:
      if ( *(uint32_t *)(dword_8F7A24 + 244) == 1 )
      {
        if ( sub_42FCB0(228) != 0 )
        {
          v5 = sub_431860((char)"Common/ActiveStatus/Animation/Bleeding.ani", 1);
          goto LABEL_62;
        }
      }
      else if ( sub_42FCB0(228) != 0 )
      {
        v5 = sub_431860((char)"Common/ActiveStatus/Animation/Bleeding12Age.ani", 1);
        goto LABEL_62;
      }
LABEL_61:
      v5 = 0;
LABEL_62:
      *(this + 5) = v5;
      return;
    case 0xCu:
      if ( sub_42FCB0(228) == 0 )
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Haste.ani", 1);
      goto LABEL_62;
    case 0xDu:
      pMem3 = operator new(0x12Cu);
      if ( pMem3 != nullptr )
        fld_e13 = sub_428F30(pMem3, (int)"Common/ActiveStatus/Particle/BlessParticle1.ptl", *(this + 1));
      else
        fld_e13 = nullptr;
      fld_e14 = *(this + 1);
      *(this + 10) = (int)fld_e13;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e13 + 112))(fld_e13, fld_e14);
      pMem4 = operator new(0x12Cu);
      if ( pMem4 != nullptr )
        fld_e15 = sub_428F30(pMem4, (int)"Common/ActiveStatus/Particle/BlessParticle2.ptl", *(this + 1));
      else
        fld_e15 = nullptr;
      fld_e16 = *(this + 1);
      *(this + 11) = (int)fld_e15;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e15 + 112))(fld_e15, fld_e16);
      return;
    case 0xFu:
      if ( sub_42FCB0(228) != 0 )
        v4 = sub_431860((char)"Common/ActiveStatus/Animation/Confuse.ani", 1);
      else
        v4 = 0;
      *(this + 5) = v4;
      if ( sub_42FCB0(228) != 0 )
        *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/ConfuseGlow.ani", 1);
      else
LABEL_44:
        *(this + 6) = 0;
      return;
    case 0x10u:
      if ( sub_42FCB0(228) != 0 )
        v6 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);
      else
        v6 = 0;
      *(this + 5) = v6;
      if ( sub_42FCB0(228) != 0 )
        v7 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);
      else
        v7 = 0;
      *(this + 6) = v7;
      if ( sub_42FCB0(228) != 0 )
        v8 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);
      else
        v8 = 0;
      fld_e5 = *(this + 5);
      *(this + 7) = v8;
      v10 = sub_42FC90(fld_e5);
      nRand = rand();
      sub_493400(*(this + 5), nRand % v10);
      fld_e6 = sub_42FC90(*(this + 6));
      nRand2 = rand();
      sub_493400(*(this + 6), nRand2 % fld_e6);
      fld_e7 = sub_42FC90(*(this + 7));
      nRand3 = rand();
      sub_493400(*(this + 7), nRand3 % fld_e7);
      return;
    default:
      return;
  }
}


// ------------------------------------------------------------
// 0x497E40 sub_497E40
// ------------------------------------------------------------
int /*thiscall*/ sub_497E40(void *this, int nArg2, int nArg3, int nArg4)
{
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 96))(this, nArg4);
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 4))(this, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x497E70 sub_497E70
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_497E70(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; ++result )
  {
    if ( result != nullptr )
      *result = *uArg12;
    ++uArg12;
  }
  return result;
}



// ============================================================
// §K 0x497EA0-0x499C70  状态应用与播放驱动
// ============================================================
// ------------------------------------------------------------
// 0x497EA0 sub_497EA0 —— 帧事件回调分发（+48/+52/+40 帧、sub_460230/sub_529A80；调试 off_77F3FC）
// ------------------------------------------------------------
void /*usercall*/ sub_497EA0(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int pObj3; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // esi
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int pObj; // eax
  int v11; // eax
  int pObj2; // eax
  int v13; // eax
  int v14; // esi
  int nRand; // eax
  int v16; // ebx
  int v17; // eax
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int v21; // ebx
  int v22; // eax
  void (/*thiscall*/ ***v23)(uint32_t, int); // ecx
  int v25; // [esp-4h] [ebp-34h]
  int v26; // [esp+0h] [ebp-30h]
  uint8_t v27[4]; // [esp+8h] [ebp-28h] BYREF
  void *Block; // [esp+Ch] [ebp-24h]
  int v29; // [esp+10h] [ebp-20h]
  int v30; // [esp+18h] [ebp-18h] BYREF
  int v31; // [esp+1Ch] [ebp-14h]
  int v32; // [esp+20h] [ebp-10h]
  int v33; // [esp+2Ch] [ebp-4h]

  pObj3 = pArg1[59];
  if ( pObj3 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)pObj3 + 308))() != 0 && pArg1[61] == 33 )
  {
    v4 = pArg1[63];
    if ( v4 != 0 && (v31 = (pArg1[64] - v4) >> 5, v5 = v31, v31 != 0) )
    {
      sub_490D70(pArg1, (int)v27);
      v33 = 0;
      if ( Block != nullptr )
        v32 = (v29 - (int)Block) >> 2;
      else
        v32 = 0;
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 21, 2, nArg2);
      v6 = *(uint32_t *)dword_8F8520;
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[59] + 48))(pArg1[59]);
      (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);
      v8 = *(uint32_t *)dword_8F8520;
      v9 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[59] + 52))(pArg1[59]);
      (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);
      pObj = pArg1[67];
      if ( pObj != 0 )
        v11 = (*(int (**)(void))(*(uint32_t *)pObj + 48))();
      else
        v11 = 0xFFFF;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v11);
      pObj2 = pArg1[67];
      if ( pObj2 != 0 )
        v13 = (*(int (**)(void))(*(uint32_t *)pObj2 + 52))();
      else
        v13 = 0xFFFF;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v13);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v32);
      v14 = 0;
      if ( v32 > 0 )
      {
        while ( 1 )
        {
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 36))(pArg1) + 68) != 0 )
          {
            nRand = rand() % v5;
          }
          else
          {
            nRand = v14;
            if ( v14 >= v5 )
              nRand = v5;
          }
          v25 = *(uint16_t *)(pArg1[63] + 32 * nRand + 28);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);
          v16 = *(uint32_t *)dword_8F8520;
          v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);
          (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
          v19 = *(uint32_t *)dword_8F8520;
          v20 = sub_460230(*(uint32_t *)(v18 + 104));
          (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);
          (*(void (/*thiscall*/ **)(uint32_t, void *, int *))(**((uint32_t **)Block + v14) + 16))(
            *((uint32_t *)Block + v14),
            &unk_9A0188,
            &v30);
          v26 = sub_529A80(v25, v26);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520);
          (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &unk_9A0188, v30);
          v21 = *(uint32_t *)dword_8F8520;
          v22 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v14) + 44))(*((uint32_t *)Block + v14));
          (*(void (/*thiscall*/ **)(int, int))(v21 + 40))(dword_8F8520, v22);
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_8F8520 + 52))(dword_8F8520, 0, 0);
          v23 = *((void (/*thiscall*/ ****)(uint32_t, int))Block + v14);
          if ( v23 != nullptr )
            (**v23)(v23, 1);
          if ( ++v14 >= v32 )
            break;
          v5 = v31;
        }
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);
      if ( Block != nullptr )
        j__free(Block);
    }
    else
    {
      off_77F3FC((char *)&byte_6CB800);
    }
  }
}


// ------------------------------------------------------------
// 0x498150 sub_498150
// ------------------------------------------------------------
size_t */*cdecl*/ sub_498150(size_t *pArg1, size_t *pArg2, size_t *pArg3)
{
  size_t *pArg12; // esi
  size_t *pArg32; // edi

  pArg12 = pArg1;
  if ( pArg1 == pArg2 )
    return pArg3;
  pArg32 = pArg3;
  do
  {
    sub_4014D0(pArg32, pArg12, 0, 0xFFFFFFFF);
    pArg32[7] = pArg12[7];
    pArg12 += 8;
    pArg32 += 8;
  }
  while ( pArg12 != pArg2 );
  return pArg32;
}



// ------------------------------------------------------------
// 0x498190 sub_498190
// ------------------------------------------------------------
size_t */*thiscall*/ sub_498190(size_t *this)
{
  *(this + 59) = 0;
  *(this + 60) = 4;
  *(this + 61) = 2;
  *(this + 66) = 1;
  *(this + 67) = 0;
  return sub_4015C0(this + 68, szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4981D0 sub_4981D0
// ------------------------------------------------------------
size_t */*cdecl*/ sub_4981D0(size_t *pArg1, size_t *pArg2, size_t *pArg3)
{
  return sub_498150(pArg1, pArg2, pArg3);
}



// ------------------------------------------------------------
// 0x4981F0 sub_4981F0
// ------------------------------------------------------------
int /*cdecl*/ sub_4981F0(size_t *pArg1, size_t *pArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != pArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)(nArg32 + 24) = 15;
      *(uint32_t *)(nArg32 + 20) = 0;
      *(uint8_t *)(nArg32 + 4) = 0;
      sub_4014D0((size_t *)nArg32, pArg1, 0, 0xFFFFFFFF);
      *(uint32_t *)(nArg32 + 28) = pArg1[7];
    }
    nArg32 += 32;
    LOBYTE(v7) = 0;
    pArg1 += 8;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x4982B0 sub_4982B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4982B0(uint32_t *this, int pArg2)
{
  int v3; // ecx
  int v4; // eax
  uint32_t *v6; // [esp-14h] [ebp-34h]
  uint32_t *v7; // [esp-10h] [ebp-30h]
  uint32_t *fld_e1; // [esp-Ch] [ebp-2Ch]
  int v9; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+1Ch] [ebp-4h]

  v3 = *(uint32_t *)(pArg2 + 4);
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( (uint8_t)sub_42CFD0(v4) != 0 )
  {
    fld_e1 = (uint32_t *)*(this + 1);
    v7 = *(uint32_t **)(pArg2 + 8);
    v6 = *(uint32_t **)(pArg2 + 4);
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);
  }
  return this;
}



// ------------------------------------------------------------
// 0x498350 sub_498350
// ------------------------------------------------------------
int /*stdcall*/ sub_498350(size_t *pArg1, size_t *pArg2, int nArg3)
{
  return sub_4981F0(pArg1, pArg2, nArg3);
}



// ------------------------------------------------------------
// 0x498370 sub_498370
// ------------------------------------------------------------
int /*thiscall*/ sub_498370(int this, int pArg2)
{
  size_t *v3; // ebx
  unsigned int v4; // eax
  size_t *fld_4; // ecx
  unsigned int fld_8; // edx
  char *v8; // eax
  int v9; // eax
  int fld_42; // edi
  unsigned int fld_C; // edx
  int fld_82; // eax
  size_t *v13; // ebx
  int v14; // ecx
  int v15; // eax

  if ( this == pArg2 )
    return this;
  v3 = *(size_t **)(pArg2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(pArg2 + 8) - (int)v3) >> 5) == 0 )
  {
    sub_428480(this);
    return this;
  }
  fld_4 = *(size_t **)(this + 4);
  if ( fld_4 != nullptr )
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 5;
  else
    fld_8 = 0;
  if ( v4 <= fld_8 )
  {
    v8 = (char *)sub_498150(v3, *(size_t **)(pArg2 + 8), fld_4);
    sub_493260(v8, *(char **)(this + 8));
    v9 = *(uint32_t *)(pArg2 + 4);
    if ( v9 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 32 * ((*(uint32_t *)(pArg2 + 8) - v9) >> 5);
    else
      fld_42 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = fld_42;
    return this;
  }
  if ( fld_4 != nullptr )
    fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) >> 5;
  else
    fld_C = 0;
  if ( v4 > fld_C )
  {
    if ( fld_4 != nullptr )
    {
      sub_493260((char *)fld_4, *(char **)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v14 = *(uint32_t *)(pArg2 + 4);
    if ( v14 != 0 )
      v15 = (*(uint32_t *)(pArg2 + 8) - v14) >> 5;
    else
      v15 = 0;
    if ( (uint8_t)sub_4281D0(v15) != 0 )
      *(uint32_t *)(this + 8) = sub_498350(*(size_t **)(pArg2 + 4), *(size_t **)(pArg2 + 8), *(uint32_t *)(this + 4));
    return this;
  }
  if ( fld_4 != nullptr )
    fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 5;
  else
    fld_82 = 0;
  v13 = (size_t *)(*(uint32_t *)(pArg2 + 4) + 32 * fld_82);
  sub_4981D0(*(size_t **)(pArg2 + 4), v13, *(size_t **)(this + 4));
  *(uint32_t *)(this + 8) = sub_4981F0(v13, *(size_t **)(pArg2 + 8), *(uint32_t *)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x4984D0 sub_4984D0
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4984D0(size_t *this, uint32_t *pArg2)
{
  sub_490340(this, (int)pArg2);
  *(this + 61) = pArg2[43];
  sub_498370((int)(this + 62), (int)(pArg2 + 45));
  *(this + 66) = pArg2[44];
  return sub_4014D0(this + 68, pArg2 + 49, 0, 0xFFFFFFFF);
}



// ------------------------------------------------------------
// 0x498530 sub_498530
// ------------------------------------------------------------
char */*thiscall*/ sub_498530(char *this, int nArg2)
{
  uint32_t *pThis_3C; // ecx

  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C2B88;
  *((uint32_t *)this + 2) = 0;
  *(this + 12) = 1;
  *(this + 14) = 0;
  *(this + 13) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 13) = 0;
  pThis_3C = this + 60;
  pThis_3C[15] = 0;
  pThis_3C[16] = 0;
  pThis_3C[17] = 0;
  pThis_3C[19] = 0;
  pThis_3C[20] = 0;
  pThis_3C[21] = 0;
  sub_430B70(pThis_3C);
  *((uint32_t *)this + 51) = sub_4A2CF0(this + 200);
  *((uint32_t *)this + 52) = 0;
  sub_493BD0((int)this);
  sub_494630((int)this, nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x4985E0 sub_4985E0 —— 状态加载大函数（+216 同步、+59/+236/+217、sub_490D70 批量生成、sub_498530 单帧、+46 事件）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4985E0(uint32_t *this, uint32_t *uArg2)
{
  int v2; // edi
  char pThis_D8; // al
  uint32_t *uArg22; // esi
  int fld_e59; // ecx
  int v7; // eax
  char pThis_D9; // cl
  int fld_e60; // eax
  int fld_e592; // ecx
  int fld_e63; // eax
  int fld_e642; // esi
  uint32_t *nRand; // esi
  char *pObj2; // esi
  char *v15; // edi
  char *pThis_14; // eax
  uint32_t *v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  uint32_t *Block2; // eax
  void (/*thiscall*/ ***v22)(uint32_t, int); // ecx
  int pObj; // ecx
  int v24; // edi
  int v25; // eax
  int v27; // [esp-4h] [ebp-50h]
  int fld_e46; // [esp-4h] [ebp-50h]
  int fld_e67; // [esp-4h] [ebp-50h]
  char v30[4]; // [esp+Ch] [ebp-40h] BYREF
  void *v31; // [esp+10h] [ebp-3Ch]
  int v32; // [esp+14h] [ebp-38h]
  int v33; // [esp+18h] [ebp-34h]
  char v34[4]; // [esp+1Ch] [ebp-30h] BYREF
  void *Block; // [esp+20h] [ebp-2Ch]
  int v36; // [esp+24h] [ebp-28h]
  int v37; // [esp+28h] [ebp-24h]
  int v38; // [esp+2Ch] [ebp-20h]
  int fld_e64; // [esp+30h] [ebp-1Ch]
  int v40; // [esp+34h] [ebp-18h]
  char *pObj22; // [esp+38h] [ebp-14h] BYREF
  int v42; // [esp+3Ch] [ebp-10h]
  int v43; // [esp+48h] [ebp-4h]

  v2 = 0;
  fld_e64 = 0;
  v31 = nullptr;
  v32 = 0;
  v33 = 0;
  pThis_D8 = *((uint8_t *)this + 216);
  v43 = 0;
  if ( pThis_D8 != 0 )
  {
    uArg22 = uArg2;
    sub_4982B0(uArg2, (int)v30);
    return uArg22;
  }
  fld_e59 = *(this + 59);
  if ( fld_e59 != 0 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e59 + 236))(fld_e59);
    pThis_D9 = *((uint8_t *)this + 217);
    LOBYTE(v40) = v7 == 2;
    if ( (v7 == 2) != pThis_D9 )
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 72))(this, v40);
  }
  fld_e60 = *(this + 60);
  if ( fld_e60 != 0 )
  {
    if ( fld_e60 == 1 )
    {
      *((uint8_t *)this + 88) = 0;
    }
    else
    {
      fld_e592 = *(this + 59);
      if ( fld_e592 != 0 )
        *((uint8_t *)this + 88) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e592 + 152))(fld_e592) == 0;
    }
  }
  else
  {
    *((uint8_t *)this + 88) = 1;
  }
  if ( *(this + 59) != 0 && *(this + 61) == 33 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    uArg22 = uArg2;
    sub_4982B0(uArg2, (int)v30);
    return uArg22;
  }
  fld_e63 = *(this + 63);
  if ( fld_e63 == 0 || (fld_e64 = (*(this + 64) - fld_e63) >> 5, fld_e642 = fld_e64, fld_e64 == 0) )
  {
    off_77F3FC(aFail_1);
    uArg22 = uArg2;
    sub_4982B0(uArg2, (int)v30);
    return uArg22;
  }
  sub_490D70(this, (int)v34);
  LOBYTE(v43) = 1;
  if ( Block != nullptr )
    v40 = (v36 - (int)Block) >> 2;
  else
    v40 = 0;
  v42 = 0;
  if ( v40 > 0 )
  {
    while ( 1 )
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 68) != 0 )
      {
        nRand = (uint32_t *)(*(this + 63) + 32 * (rand() % fld_e642));
      }
      else
      {
        if ( v2 < fld_e642 )
          fld_e642 = v2;
        nRand = (uint32_t *)(*(this + 63) + 32 * fld_e642);
      }
      if ( *(this + 61) == 2 )
        break;
      if ( *(this + 61) != 33 )
        goto LABEL_54;
      pObj2 = (char *)sub_53A220(nRand[7], nullptr);  // 【巨函数（size=17574）→ src/combat/bigfunc_53A220…】
      pObj22 = pObj2;
LABEL_53:
      if ( pObj2 != nullptr )
      {
        fld_e46 = *(this + 46);
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 72))(pObj2);
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj2 + 60))(pObj2, *((uint32_t *)Block + v2));
        sub_4A0B60(fld_e46);
        fld_e67 = *(this + 67);
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 60))(pObj2);
        sub_4A06D0(fld_e67);
        pObj = *((uint32_t *)Block + v2);
        v24 = *(uint32_t *)pObj2;
        v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);
        (*(void (/*thiscall*/ **)(char *, bool))(v24 + 148))(pObj2, *(uint8_t *)(v25 + 84) == 0);
        *((uint32_t *)Block + v42) = 0;
        sub_45FC10(&pObj22);
        v2 = v42;
        goto LABEL_58;
      }
LABEL_54:
      Block2 = Block;
      v22 = *((void (/*thiscall*/ ****)(uint32_t, int))Block + v2);
      if ( v22 != nullptr )
      {
        (**v22)(v22, 1);
        Block2 = Block;
      }
      Block2[v2] = 0;
LABEL_58:
      v42 = ++v2;
      if ( v2 >= v40 )
        goto LABEL_59;
      fld_e642 = fld_e64;
    }
    if ( nRand[7] == -1 )
    {
      v15 = (char *)sub_44B6C0(284);
      pObj22 = v15;
      LOBYTE(v43) = 2;
      if ( v15 != nullptr )
      {
        v38 = sub_42FCB0(228);
        LOBYTE(v43) = 3;
        if ( v38 != 0 )
        {
          if ( nRand[6] < 0x10u )
            LOBYTE(nRand) = (uint8_t)nRand + 4;
          else
            nRand = (uint32_t *)nRand[1];
          if ( *(this + 74) < 0x10u )
            pThis_14 = (char *)sub_431920((uint8_t)this + 20, (char)nRand, 1);
          else
            pThis_14 = (char *)sub_431920(*(this + 69), (char)nRand, 1);
        }
        else
        {
          pThis_14 = nullptr;
        }
        LOBYTE(v43) = 2;
        goto LABEL_43;
      }
    }
    else
    {
      v15 = (char *)sub_44B6C0(284);
      v38 = (int)v15;
      LOBYTE(v43) = 4;
      if ( v15 != nullptr )
      {
        pObj22 = (char *)sub_42FCB0(228);
        LOBYTE(v43) = 5;
        if ( pObj22 != nullptr )
        {
          if ( nRand[6] < 0x10u )
            v17 = nRand + 1;
          else
            v17 = (uint32_t *)nRand[1];
          v27 = nRand[7];
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v17);
          v18 = sub_418DD0(v27);
          pThis_14 = sub_498530(pObj22, v18);
          LOBYTE(v43) = 4;
        }
        else
        {
          pThis_14 = nullptr;
          LOBYTE(v43) = 4;
        }
LABEL_43:
        sub_44E0D0(v15, (int)pThis_14, 0);
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';
LABEL_52:
        pObj2 = v15;
        v19 = *(uint32_t *)v15;
        LOBYTE(v43) = 1;
        pObj22 = v15;
        v20 = (*(int (/*thiscall*/ **)(char *))(v19 + 36))(v15);
        v2 = v42;
        *(uint32_t *)(v20 + 8) = *(this + 66);
        goto LABEL_53;
      }
    }
    v15 = nullptr;
    goto LABEL_52;
  }
LABEL_59:
  uArg22 = uArg2;
  sub_4982B0(uArg2, (int)v30);
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  v36 = 0;
  v37 = 0;
  if ( v31 != nullptr )
    j__free(v31);
  return uArg22;
}


// ------------------------------------------------------------
// 0x4989B0 sub_4989B0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4989B0(void *this)
{
  void *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  return sub_407EA0(&dword_9A02B4, &pThis);
}



// ------------------------------------------------------------
// 0x4989D0 sub_4989D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4989D0(void **this)
{
  sub_6569D0(this);
  sub_6569D0(this);
  j__free(*(this + 1));
  *(this + 1) = nullptr;
}



// ------------------------------------------------------------
// 0x498A00 sub_498A00
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_498A00(uint32_t *this)
{
  *(this + 1) = sub_425940(this);
  *(this + 2) = 0;
  sub_6569D0(this);
  return this;
}



// ------------------------------------------------------------
// 0x498A20 sub_498A20
// ------------------------------------------------------------
int /*thiscall*/ sub_498A20(uint32_t *this, unsigned int uArg2)
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
// 0x498AB0 sub_498AB0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_498AB0(uint32_t *this)
{
  int v1; // edx
  int v2; // esi
  int v3; // edx
  uint32_t *v4; // edi
  uint32_t *result; // eax
  uint32_t *pThis; // [esp+8h] [ebp-4h] BYREF

  v1 = dword_9A02A8++;
  *(this + 1) = v1;
  v2 = *(uint32_t *)dword_9A02B8;
  v3 = *(uint32_t *)(*(uint32_t *)dword_9A02B8 + 4);
  pThis = this;
  v4 = sub_40C0F0(v2, v3, &pThis);
  sub_498A20(&dword_9A02B4, 1u);
  *(uint32_t *)(v2 + 4) = v4;
  result = (uint32_t *)v4[1];
  *result = v4;
  return result;
}



// ------------------------------------------------------------
// 0x498B00 sub_498B00
// ------------------------------------------------------------
void /*thiscall*/ sub_498B00(float *this, int pArg2, int nArg3)
{
  int pObj; // ecx
  double v5; // st7

  pObj = *(uint32_t *)this;
  *((uint8_t *)this + 124) = 1;
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )
  {
    v5 = (double)nArg3;
    if ( *(this + pArg2 + 1) != v5 )
    {
      *(this + pArg2 + 1) = v5;
      *((uint8_t *)this + 196) = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x498B50 sub_498B50
// ------------------------------------------------------------
int /*cdecl*/ sub_498B50(int nArg1, int nArg2)
{
  return sub_657740(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x498B70 sub_498B70 —— 对象字段快照复位（+200..+276 全量默认值；+280 = timeGetTime() 时间戳）
// ------------------------------------------------------------
DWORD /*thiscall*/ sub_498B70(int this)
{
  DWORD result; // eax

  *(uint32_t *)(this + 92) = 1;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint8_t *)(this + 156) = 1;
  *(uint8_t *)(this + 157) = 0;
  *(uint32_t *)(this + 160) = -1;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint8_t *)(this + 172) = 1;
  *(uint32_t *)(this + 200) = 0;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 0;
  *(uint8_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = -1;
  *(uint32_t *)(this + 220) = -1;
  *(uint32_t *)(this + 224) = -1;
  *(uint32_t *)(this + 228) = -1;
  *(uint8_t *)(this + 232) = 0;
  *(uint32_t *)(this + 236) = 0;
  *(uint32_t *)(this + 240) = 0;
  *(uint32_t *)(this + 244) = 0;
  *(uint8_t *)(this + 248) = 0;
  *(uint32_t *)(this + 252) = 0;
  *(uint8_t *)(this + 256) = 1;
  *(uint32_t *)(this + 260) = 2;
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint8_t *)(this + 276) = 1;
  *(uint8_t *)(this + 277) = 0;
  result = timeGetTime();
  *(uint32_t *)(this + 280) = result;
  return result;
}



// ------------------------------------------------------------
// 0x498C40 sub_498C40
// ------------------------------------------------------------
int /*thiscall*/ sub_498C40(void *this)
{
  int i; // edi

  (*(void (/*thiscall*/ **)(void *, uint32_t, int, uint32_t))(*(uint32_t *)this + 228))(this, 0, -1, 0);
  for ( i = 0; i < 4; ++i )
    (*(void (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 252))(this, i, -1);
  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 260))(this, 0, 0, 0);
  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 272))(this, 0, 0);
  return (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 284))(this, 0, 0, 1, 2);
}



// ------------------------------------------------------------
// 0x498CA0 sub_498CA0
// ------------------------------------------------------------
int /*usercall*/ sub_498CA0@<eax>(float *pArg1@<ecx>, int nArg2@<edi>)
{
  int pObj; // ecx
  int v4; // eax
  int v5; // ecx
  int result; // eax
  float v7; // [esp+4h] [ebp-Ch]
  float v8; // [esp+8h] [ebp-8h]
  int v9; // [esp+Ch] [ebp-4h]

  if ( *((uint32_t *)pArg1 + 50) != 0
    && *((uint32_t *)pArg1 + 51) != -1
    && sub_699000((int)(pArg1 + 2)) >= *((uint32_t *)pArg1 + 51) + *((uint32_t *)pArg1 + 52) )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 232))(pArg1);
  }
  sub_4A0790(*((uint32_t *)pArg1 + 28));
  v7 = (float)(*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 128))(pArg1);
  v8 = (float)(*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 124))(pArg1);
  v9 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 120))(pArg1);
  pArg1[45] = v8;
  pArg1[46] = v7;
  pArg1[44] = (float)v9;
  if ( (*(uint8_t (/*thiscall*/ **)(float *, int))(*(uint32_t *)pArg1 + 40))(pArg1, 2) != 0 )
  {
    pObj = *(uint32_t *)(*((uint32_t *)pArg1 + 28) + 104);
    if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj) == 0 )
      (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 84))(pArg1, 0);
    if ( *((uint8_t *)pArg1 + 157) != 0 )
    {
      v4 = *((uint32_t *)pArg1 + 30);
      if ( v4 != 0 && *(uint8_t *)(v4 + 170) != 0 )
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 84))(pArg1, 0);
    }
  }
  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 332))(pArg1);
  if ( *((uint32_t *)pArg1 + 41) != 0 )
    sub_50EB10();
  if ( *((uint32_t *)pArg1 + 42) != 0 )
    sub_50E9B0();
  v5 = *((uint32_t *)pArg1 + 28);
  if ( *(uint8_t *)(v5 + 196) != 0 )
    sub_49FFC0((uint32_t *)v5, nArg2, (int)pArg1, 0, 0);
  result = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)pArg1 + 40))(pArg1, 1);
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 564))(pArg1);
  return result;
}



// ------------------------------------------------------------
// 0x498DE0 sub_498DE0
// ------------------------------------------------------------
bool /*thiscall*/ sub_498DE0(uint32_t *this, int nArg2)
{
  return (nArg2 & *(this + 24)) == nArg2;
}



// ------------------------------------------------------------
// 0x498E00 sub_498E00
// ------------------------------------------------------------
void /*thiscall*/ sub_498E00(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int *fld_e28; // esi
  int pObj3; // ecx
  bool v7; // zf
  double v8; // st7
  int *fld_e282; // esi
  int pObj2; // ecx
  double v11; // st7
  int *fld_e283; // esi
  int pObj; // ecx
  double v14; // st7

  fld_e28 = (int *)*(this + 28);
  pObj3 = *fld_e28;
  v7 = *fld_e28 == 0;
  *((uint8_t *)fld_e28 + 124) = 1;
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 308))(pObj3) != 0 )
  {
    v8 = (double)nArg2;
    if ( *((float *)fld_e28 + 1) != v8 )
    {
      *((float *)fld_e28 + 1) = v8;
      *((uint8_t *)fld_e28 + 196) = 1;
    }
  }
  fld_e282 = (int *)*(this + 28);
  pObj2 = *fld_e282;
  v7 = *fld_e282 == 0;
  *((uint8_t *)fld_e282 + 124) = 1;
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 308))(pObj2) != 0 )
  {
    v11 = (double)nArg3;
    if ( *((float *)fld_e282 + 2) != v11 )
    {
      *((float *)fld_e282 + 2) = v11;
      *((uint8_t *)fld_e282 + 196) = 1;
    }
  }
  fld_e283 = (int *)*(this + 28);
  pObj = *fld_e283;
  v7 = *fld_e283 == 0;
  *((uint8_t *)fld_e283 + 124) = 1;
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )
  {
    v14 = (double)nArg4;
    if ( *((float *)fld_e283 + 3) != v14 )
    {
      *((float *)fld_e283 + 3) = v14;
      *((uint8_t *)fld_e283 + 196) = 1;
    }
  }
}



// ------------------------------------------------------------
// 0x498EC0 sub_498EC0
// ------------------------------------------------------------
int /*thiscall*/ sub_498EC0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int fld_e28; // eax
  int result; // eax
  int fld_e282; // ecx

  fld_e28 = *(this + 28);
  *(uint8_t *)(fld_e28 + 124) = 1;
  *(float *)(fld_e28 + 4) = (float)nArg2;
  result = *(this + 28);
  *(uint8_t *)(result + 124) = 1;
  *(float *)(result + 8) = (float)nArg3;
  fld_e282 = *(this + 28);
  *(uint8_t *)(fld_e282 + 124) = 1;
  *(float *)(fld_e282 + 12) = (float)nArg4;
  return result;
}



// ------------------------------------------------------------
// 0x498F00 sub_498F00
// ------------------------------------------------------------
int /*thiscall*/ sub_498F00(int *this, int nArg2)
{
  int result; // eax
  uint8_t *fld_e28; // esi

  result = *(this + 50);
  if ( result == 0 )
  {
    fld_e28 = (uint8_t *)*(this + 28);
    if ( *(uint32_t *)fld_e28 != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)fld_e28 + 308))(*(uint32_t *)fld_e28);
      if ( (uint8_t)result != 0 )
      {
        result = nArg2;
        if ( (char)fld_e28[52] != nArg2 )
        {
          fld_e28[52] = nArg2;
          fld_e28[196] = 1;
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x498F40 sub_498F40
// ------------------------------------------------------------
int /*thiscall*/ sub_498F40(uint32_t *this, char pszArg2)
{
  int result; // eax

  result = *(this + 50);
  if ( result == 0 )
  {
    result = *(this + 28);
    *(uint8_t *)(result + 52) = pszArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x498F70 sub_498F70
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_498F70(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 304))(this) != 0
      && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 304))(this) == dword_8F7C04;
}



// ------------------------------------------------------------
// 0x498FA0 sub_498FA0
// ------------------------------------------------------------
char /*thiscall*/ sub_498FA0(int *this, int pArg2, int nArg3)
{
  char result; // al
  int fld_e30; // edi

  if ( *(this + pArg2 + 54) == -1 )
  {
    *(this + pArg2 + 54) = nArg3;
  }
  else
  {
    result = nArg3;
    if ( nArg3 == -1 )
    {
      fld_e30 = *(this + 30);
      if ( fld_e30 != 0 )
      {
        sub_4910E0(*(this + 30));
        result = sub_493A60(fld_e30, *(uint32_t *)(fld_e30 + 32));
        *(this + pArg2 + 54) = -1;
      }
      else
      {
        *(this + pArg2 + 54) = -1;
      }
    }
    else
    {
      *(this + pArg2 + 54) = nArg3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x499020 sub_499020
// ------------------------------------------------------------
char /*thiscall*/ sub_499020(int this, char pszArg2, int nArg3, int nArg4)
{
  char result; // al
  int fld_78; // edi

  result = *(uint8_t *)(this + 232);
  if ( result != 0 && pszArg2 == 0 )
  {
    fld_78 = *(uint32_t *)(this + 120);
    if ( fld_78 != 0 )
    {
      sub_4910E0(*(uint32_t *)(this + 120));
      result = sub_493A60(fld_78, *(uint32_t *)(fld_78 + 32));
    }
  }
  *(uint8_t *)(this + 232) = pszArg2;
  *(uint32_t *)(this + 236) = nArg3;
  *(uint32_t *)(this + 240) = nArg4;
  return result;
}



// ------------------------------------------------------------
// 0x499080 sub_499080
// ------------------------------------------------------------
void /*thiscall*/ sub_499080(int this, char pszArg2, float fArg3)
{
  double fArg32; // st7
  int fld_78; // esi

  if ( pszArg2 != 0 )
  {
    fArg32 = fArg3;
  }
  else
  {
    fArg32 = 0.0;
    fArg3 = 0.0;
  }
  if ( *(float *)(this + 244) == 0.0 || fArg32 != 0.0 )
  {
    *(float *)(this + 244) = fArg32;
  }
  else
  {
    fld_78 = *(uint32_t *)(this + 120);
    if ( fld_78 != 0 )
    {
      sub_4910E0(*(uint32_t *)(this + 120));
      sub_493A60(fld_78, *(uint32_t *)(fld_78 + 32));
      *(float *)(this + 244) = fArg3;
    }
    else
    {
      *(float *)(this + 244) = fArg32;
    }
  }
}



// ------------------------------------------------------------
// 0x499110 sub_499110
// ------------------------------------------------------------
char /*thiscall*/ sub_499110(uint8_t *this, void *Src, int nArg3, int nArg4, int nArg5)
{
  char result; // al
  int pThis_38; // eax

  result = 0;
  if ( strcmp((const char *)Src, szPassword) != 0 )
  {
    result = *(this + 172);
    if ( result != 0 )
    {
      pThis_38 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 56))(this);
      return sub_65FE10(Src, (int)(this + 176), nArg4, nArg5, 0, pThis_38, nArg3);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x499170 sub_499170
// ------------------------------------------------------------
int /*thiscall*/ sub_499170(void *this, int nArg2)
{
  int pThis_38; // eax

  pThis_38 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);
  return sub_65DE30(pThis_38, nArg2);
}



// ------------------------------------------------------------
// 0x499190 sub_499190
// ------------------------------------------------------------
int /*thiscall*/ sub_499190(uint32_t *this, int nArg2)
{
  int result; // eax

  result = nArg2;
  if ( *(uint32_t *)(*(this + 28) + 128) == nArg2 && nArg2 != 0 )
  {
    sub_4A06D0(0);
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 2);
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 84))(this, 0);
  }
  return result;
}



// ------------------------------------------------------------
// 0x4991D0 sub_4991D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4991D0(uint32_t *this)
{
  void *pMem; // eax
  void *pMem2; // esi

  if ( *(this + 42) == 0 )
  {
    pMem = operator new(0x10u);
    pMem2 = pMem;
    if ( pMem != nullptr )
    {
      sub_50E730(pMem);
      sub_50E8D0(this);
    }
    else
    {
      pMem2 = nullptr;
    }
    *(this + 42) = pMem2;
  }
  return *(this + 42);
}



// ------------------------------------------------------------
// 0x499240 sub_499240
// ------------------------------------------------------------
uint64_t /*cdecl*/ sub_499240(int nArg1, int nArg2, int pArg3, int nArg4, char pszArg5)
{
  int v5; // eax

  v5 = nArg2 - nArg4;
  if ( pszArg5 == 0 )
    v5 = 100 * v5 / dword_7930D4[0];
  return (uint64_t)sqrt((double)((nArg1 - pArg3) * (nArg1 - pArg3) + v5 * v5));
}



// ------------------------------------------------------------
// 0x499280 sub_499280
// ------------------------------------------------------------
double /*thiscall*/ sub_499280(void *this, int nArg2, char pszArg3)
{
  int v4; // ebx
  int pThis_78; // ebx
  int v6; // edi
  int pThis_7C; // edi
  double result; // st7
  int pThis_7C2; // [esp+18h] [ebp+8h]

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
  pThis_78 = v4 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);
  pThis_7C = v6 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  pThis_7C2 = pThis_7C;
  if ( pszArg3 == 0 )
  {
    pThis_7C = 100 * pThis_7C / dword_7930D4[0];
    pThis_7C2 = pThis_7C;
  }
  if ( pThis_78 != 0 )
  {
    result = atan2((double)pThis_7C2 / (double)pThis_78, 1.0) * 57.29577951308232;
    if ( pThis_78 >= 0 )
    {
      if ( pThis_7C < 0 )
        return result + 360.0;
    }
    else
    {
      return result + 180.0;
    }
  }
  else if ( pThis_7C < 0 )
  {
    return 270.0;
  }
  else
  {
    return 90.0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x499330 sub_499330
// ------------------------------------------------------------
long double /*thiscall*/ sub_499330(void *this, int nArg2, int nArg3)
{
  int v4; // esi
  signed int pThis_78; // esi
  int v6; // ebx
  int pThis_80; // ebx

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);
  pThis_78 = abs32(v4 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this));
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2);
  pThis_80 = v6 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this);
  if ( pThis_78 != 0 )
    return atan2((double)(pThis_80 / pThis_78), 1.0) * 57.29577951308232;
  if ( pThis_80 < 0 )
    return -90.0;
  return 90.0;
}



// ------------------------------------------------------------
// 0x4993B0 sub_4993B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4993B0(void *this, int *pDwArg2, int *pDwArg3, int nArg4, int nArg5, int nArg6, char pszArg7, int nArg8)
{
  int v8; // esi
  int v9; // ecx
  int v10; // ebx
  int v11; // edi
  int v12; // esi
  int v14; // ecx
  int v15; // ebx
  int v16; // edi
  int v17; // esi
  int v19; // [esp+10h] [ebp-4h]
  int v20; // [esp+30h] [ebp+1Ch]
  int v21; // [esp+30h] [ebp+1Ch]

  v8 = 0;
  v19 = 0;
  if ( pszArg7 != 0 )
  {
    v9 = nArg8 + 2 * nArg6;
    v20 = v9;
    if ( v9 > 0 )
    {
      while ( 1 )
      {
        v10 = v8 % 2 != 0 ? nArg5 - (v8 + 1) / 2 : nArg5 + v8 / 2;
        v11 = 0;
        if ( v9 > 0 )
          break;
LABEL_13:
        v8 += nArg8;
        v19 = v8;
        if ( v8 >= v9 )
          return 0;
      }
      while ( 1 )
      {
        v12 = v11 % 2 != 0 ? nArg4 - (v11 + 1) / 2 : nArg4 + v11 / 2;
        if ( (*(uint8_t (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v12, v10, 0) != 0 )
          break;
        v11 += nArg8;
        if ( v11 >= v20 )
        {
          v8 = v19;
          v9 = v20;
          goto LABEL_13;
        }
      }
      *pDwArg2 = v12;
      *pDwArg3 = v10;
      return 1;
    }
    return 0;
  }
  v14 = nArg8 + 2 * nArg6;
  v21 = v14;
  if ( v14 <= 0 )
    return 0;
  while ( 1 )
  {
    v15 = v8 % 2 != 0 ? nArg4 - (v8 + 1) / 2 : nArg4 + v8 / 2;
    v16 = 0;
    if ( v14 > 0 )
      break;
LABEL_27:
    v8 += nArg8;
    v19 = v8;
    if ( v8 >= v14 )
      return 0;
  }
  while ( 1 )
  {
    v17 = v16 % 2 != 0 ? nArg5 - (v16 + 1) / 2 : nArg5 + v16 / 2;
    if ( (*(uint8_t (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v15, v17, 0) != 0 )
      break;
    v16 += nArg8;
    if ( v16 >= v21 )
    {
      v8 = v19;
      v14 = v21;
      goto LABEL_27;
    }
  }
  *pDwArg2 = v15;
  *pDwArg3 = v17;
  return 1;
}



// ------------------------------------------------------------
// 0x499560 sub_499560
// ------------------------------------------------------------
char /*cdecl*/ sub_499560(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  int v6; // edi
  int v8; // [esp+Ch] [ebp-4h]

  v8 = 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int, int, int, int, int))(*(uint32_t *)nArg1 + 140))(
         nArg1,
         nArg2,
         nArg3,
         nArg4,
         nArg5,
         30,
         1,
         1) != 0 )
    return 1;
  v6 = 30;
  while ( 1 )
  {
    v6 += 10;
    if ( ++v8 >= nArg6 )
      break;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int, int, int, int, int))(*(uint32_t *)nArg1 + 140))(
           nArg1,
           nArg2,
           nArg3,
           nArg4,
           nArg5,
           v6,
           1,
           1) != 0 )
      return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4995F0 sub_4995F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4995F0(void *this, uint32_t *uArg2, uint32_t *uArg3, int nArg4, int nArg5)
{
  int v6; // ebx
  double pThis_8; // st7
  int result; // eax
  int pThis_7C; // [esp+Ch] [ebp-Ch]
  int v10; // [esp+10h] [ebp-8h]
  int pThis_78; // [esp+14h] [ebp-4h]
  float v12; // [esp+2Ch] [ebp+14h]

  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 120))(nArg4);
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 124))(nArg4);
  pThis_78 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);
  pThis_7C = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);
  v12 = (float)nArg5;
  pThis_8 = 1.0 - v12 / (double)(*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 8))(this, nArg4, 1);
  *uArg2 = pThis_78 + (uint64_t)((double)(v6 - pThis_78) * pThis_8);
  result = pThis_7C + (uint64_t)((double)(v10 - pThis_7C) * pThis_8);
  *uArg3 = result;
  return result;
}



// ------------------------------------------------------------
// 0x499690 sub_499690
// ------------------------------------------------------------
void /*cdecl*/ sub_499690(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        float a6,
        int a7,
        float a8,
        int a9,
        float a10,
        int a11,
        float a12,
        float a13)
{
  int v13; // eax
  float v14; // [esp+1Ch] [ebp+1Ch]

  if ( LOBYTE(a6) != 0 )
  {
    v14 = -a8;
    v13 = a2 - a4;
  }
  else
  {
    v14 = a8;
    v13 = a2 + a4;
  }
  sub_424760(a1, v13, a5 + a3, a7, v14, a9, a10, a11, a12, a13);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
}



// ------------------------------------------------------------
// 0x4996F0 sub_4996F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4996F0(uint32_t *this)
{
  double fld_e28; // st7

  fld_e28 = *(float *)(*(this + 28) + 16);
  if ( fld_e28 > 5.0 )
    return 1;
  if ( fld_e28 >= -5.0 )
    return _RTC_NumErrors();
  return 0;
}



// ------------------------------------------------------------
// 0x49971B __RTC_NumErrors
// ------------------------------------------------------------
int /*cdecl*/ _RTC_NumErrors()
{
  return 4;
}



// ------------------------------------------------------------
// 0x499730 sub_499730
// ------------------------------------------------------------
int /*thiscall*/ sub_499730(uint32_t *this)
{
  double fld_e28; // st7
  int result; // eax

  fld_e28 = *(float *)(*(this + 28) + 20);
  if ( fld_e28 > 5.0 )
    return 3;
  result = 2;
  if ( fld_e28 >= -5.0 )
    return 4;
  return result;
}



// ------------------------------------------------------------
// 0x499770 sub_499770
// ------------------------------------------------------------
int /*thiscall*/ sub_499770(uint32_t *this, int nArg2, int nArg3)
{
  *(this + 67) = nArg2;
  *(this + 68) = nArg3;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4997A0 sub_4997A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4997A0(int this, int nArg2)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = -1;
  *(uint32_t *)(this + 44) = -1;
  *(uint32_t *)(this + 48) = -1;
  *(uint8_t *)(this + 52) = 1;
  *(uint32_t *)(this + 53) = 0;
  *(uint32_t *)(this + 65) = 0;
  *(uint32_t *)(this + 77) = 0;
  *(uint32_t *)(this + 89) = -1;
  *(uint32_t *)(this + 57) = 0;
  *(uint32_t *)(this + 69) = 0;
  *(uint32_t *)(this + 81) = 0;
  *(uint32_t *)(this + 93) = -1;
  *(uint32_t *)(this + 61) = 0;
  *(uint32_t *)(this + 73) = 0;
  *(uint32_t *)(this + 85) = 0;
  *(uint32_t *)(this + 97) = -1;
  *(uint8_t *)(this + 101) = 1;
  *(uint8_t *)(this + 148) = 0;
  *(uint32_t *)(this + 144) = &off_6C2B88;
  *(uint32_t *)(this + 152) = 0;
  *(uint8_t *)(this + 156) = 1;
  *(uint8_t *)(this + 158) = 0;
  *(uint8_t *)(this + 157) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 160) = 0;
  sub_49FC60(this);
  sub_4A0770(nArg2);
  return this;
}



// ------------------------------------------------------------
// 0x499880 sub_499880
// ------------------------------------------------------------
int /*thiscall*/ sub_499880(int this)
{
  int result; // eax

  result = sub_649170();  // 【CNDarkDamageFromCurseAura__vmt78】
  *(uint32_t *)(this + 144) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 148) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4998D0 sub_4998D0
// ------------------------------------------------------------
int /*cdecl*/ sub_4998D0(int nArg1)
{
  if ( dword_9A0268 == 0 )
  {
    if ( (dword_9A024C & 1) == 0 )
    {
      dword_9A024C |= 1u;
      sub_657800(nArg1, 256);
      atexit(sub_6BF9D0);
    }
    dword_9A0268 = (int)&unk_9A022C;
  }
  return sub_6578B0(nArg1);
}



// ------------------------------------------------------------
// 0x499960 sub_499960
// ------------------------------------------------------------
int /*thiscall*/ sub_499960(int this, void *Block, int nArg3, int nArg4)
{
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 4) = &off_6C2B88;
  *(uint32_t *)(this + 12) = 0;
  *(uint8_t *)(this + 16) = 1;
  *(uint8_t *)(this + 18) = 0;
  *(uint8_t *)(this + 17) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 20) = 0;
  sub_50EAD0();
  sub_50F1C0(Block, nArg3, nArg4);
  return this;
}



// ------------------------------------------------------------
// 0x4999D0 sub_4999D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4999D0(int this)
{
  int result; // eax

  result = sub_50EAF0();
  *(uint32_t *)(this + 4) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x499A20 sub_499A20
// ------------------------------------------------------------
int /*thiscall*/ sub_499A20(uint32_t *this, int nArg2, char pszArg3)
{
  int v4; // eax
  int v5; // eax
  int result; // eax

  sub_698F90((int)(this + 2), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  sub_698F90((int)(this + 9), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  sub_698F90((int)(this + 16), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( sub_4998D0(204) != 0 )
    v4 = sub_4997A0(this);
  else
    v4 = 0;
  *(this + 28) = v4;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 92))(this, nArg2);
  v5 = *this;
  *(this + 24) = 2;
  *((uint8_t *)this + 157) = pszArg3;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 72))(this, 1);
  *((uint8_t *)this + 264) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x499AD0 sub_499AD0
// ------------------------------------------------------------
int /*thiscall*/ sub_499AD0(void *Block)
{
  void *pMem; // eax
  int v3; // eax

  if ( *((uint32_t *)Block + 41) == 0 )
  {
    pMem = operator new(0x44u);
    if ( pMem != nullptr )
      v3 = sub_499960((int)pMem, Block, 120, 0);
    else
      v3 = 0;
    *((uint32_t *)Block + 41) = v3;
  }
  return *((uint32_t *)Block + 41);
}



// ------------------------------------------------------------
// 0x499B40 sub_499B40
// ------------------------------------------------------------
int /*thiscall*/ sub_499B40(uint32_t *this)
{
  return sub_499A20(this, 0, 0);
}



// ------------------------------------------------------------
// 0x499B50 sub_499B50
// ------------------------------------------------------------
char /*thiscall*/ sub_499B50(char *this, char pszArg2)
{
  char result; // al
  int v4; // edi
  int pThis_30; // eax
  int v6; // edi
  int pThis_34; // eax
  int v8; // edx
  char *pThis_124; // edi
  int pThis_342; // eax

  result = pszArg2;
  if ( (pszArg2 != 0 || (result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this)) != 0) && *(this + 264) != 1 )
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 23, 2);
    v4 = *(uint32_t *)dword_8F8520;
    pThis_30 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 48))(this);
    (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, pThis_30);
    v6 = *(uint32_t *)dword_8F8520;
    pThis_34 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);
    (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, pThis_34);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
    v8 = *(uint32_t *)this;
    *(this + 264) = 1;
    result = (*(int (/*thiscall*/ **)(char *, int))(v8 + 40))(this, 529);
    if ( result != 0 )
    {
      if ( *((uint32_t *)this + 78) < 0x10u )
        pThis_124 = this + 292;
      else
        pThis_124 = *((char **)this + 73);
      pThis_342 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);
      return off_77F3FC((char *)&byte_6CB870, pThis_124, pThis_342);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x499C20 sub_499C20
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_499C20(int nArg1, int nArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);
  if ( result != nullptr )
  {
    *result = nArg1;
    result[1] = nArg2;
    result[2] = *pArg3;
    result[3] = pArg3[1];
    result[4] = pArg3[2];
    result[5] = pArg3[3];
    result[6] = pArg3[4];
  }
  return result;
}



// ============================================================
// §L 0x499C70-0x49B860  主播放驱动 + 组件属性访问器族
// ============================================================
// ------------------------------------------------------------
// 0x499C70 sub_499C70 —— ★主播放驱动
//   帧索引 +57 推进、+54/+55/+56 时刻窗、+232 状态位、+248/+256 事件参数；
//   子链下发 sub_491D00/491DE0/492030；+41/+42 → sub_50EB40/50E750 通道提交。
// ------------------------------------------------------------
int /*thiscall*/ sub_499C70(uint8_t *this)
{
  int pThis_1E; // ecx
  int pThis_1C; // ecx
  int pThis_39; // edi
  int pThis_78; // eax
  int v6; // ebx
  int pThis_7C; // eax
  uint32_t *pThis_20; // eax
  uint32_t *v9; // edi
  int v10; // edx
  int v11; // eax
  int nRand; // eax
  int nRand2; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int result; // eax
  int pThis_80; // [esp-Ch] [ebp-28h]
  int pThis_82; // [esp-8h] [ebp-24h]
  int pThis_8; // [esp-4h] [ebp-20h]
  int v21; // [esp+Ch] [ebp-10h]
  int v22; // [esp+10h] [ebp-Ch]
  int v23; // [esp+10h] [ebp-Ch]
  int pThis_392; // [esp+14h] [ebp-8h]
  int v25; // [esp+14h] [ebp-8h]
  float v26; // [esp+18h] [ebp-4h]

  pThis_1E = *((uint32_t *)this + 30);
  if ( pThis_1E != 0 )
  {
    sub_4938F0(pThis_1E);
    pThis_1C = *(uint32_t *)(*((uint32_t *)this + 28) + 104);
    pThis_39 = *((uint32_t *)this + 57);
    pThis_392 = pThis_39;
    if ( pThis_1C != 0 && 100.0 != ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)pThis_1C + 64))(pThis_1C) )
    {
      if ( pThis_39 == -1 )
        pThis_392 = 255;
      pThis_39 = (uint64_t)(((double (/*thiscall*/ *)(uint32_t))*(uint32_t *)(**(uint32_t **)(*((uint32_t *)this + 28) + 104)
                                                                        + 64))(*(uint32_t *)(*((uint32_t *)this + 28) + 104))
                            * (double)pThis_392
                            * 0.0099999998);
    }
    sub_491F80(*((uint32_t *)this + 54), *((uint32_t *)this + 55), *((uint32_t *)this + 56), pThis_39, 1);
    if ( *(this + 232) != 0 )
      sub_492030(*((uint32_t *)this + 59), *((uint32_t *)this + 60), 1);
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 276))(this) != 0 )
      sub_492080(*((float *)this + 61));
  }
  pThis_8 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this) + 8);
  pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this);
  v6 = sub_45E490(pThis_78, pThis_8);
  v21 = v6;
  pThis_82 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this) + 8);
  pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
  pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);
  v25 = sub_45E4D0(pThis_7C, pThis_80, pThis_82, 1.0);
  LOBYTE(v26) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) != 1;
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, int, int, uint8_t))(*(uint32_t *)this + 324))(
    this,
    0,
    v6,
    v25,
    LOBYTE(v26));
  pThis_20 = *((uint32_t **)this + 32);
  v9 = (uint32_t *)*pThis_20;
  if ( (uint32_t *)*pThis_20 != pThis_20 )
  {
    do
    {
      if ( (int)v9[2] >= 0 )
        break;
      if ( *((uint8_t *)v9 + 25) == 0 )
      {
        sub_4938F0(v9[3]);
        if ( LOBYTE(v26) != 0 )
          v11 = v6 - v9[4];
        else
          v11 = v6 + v9[4];
        LOBYTE(v10) = (*((uint8_t *)v9 + 24) != 0) - 1;
        sub_491D00(dword_79C0B0, v11, v25 + v9[5], COERCE_FLOAT(LODWORD(v26) & v10));
      }
      v9 = (uint32_t *)*v9;
    }
    while ( v9 != *((uint32_t **)this + 32) );
  }
  if ( *((uint32_t *)this + 30) != 0 )
  {
    if ( *(this + 248) != 0 )
    {
      if ( *(this + 256) != 0 )
      {
        nRand = rand();
        v22 = nRand % 3 - 1;
        if ( nRand % 3 == 1 )
          nRand2 = rand() % 2 != 0 ? 2 : 0;
        else
          nRand2 = rand() % 3;
        sub_491DE0(
          dword_79C0B0,
          v6 + v22 * *((uint32_t *)this + 65),
          v25 + (nRand2 - 1) * *((uint32_t *)this + 65),
          v26,
          0,
          1,
          *((uint32_t *)this + 63),
          -1761607681);
      }
      else
      {
        v14 = 0;
        v23 = 0;
        do
        {
          if ( v14 != 4 )
          {
            v6 = v21;
            sub_491DE0(
              dword_79C0B0,
              v21 + *((uint32_t *)this + 65) * (v14 / 3u - 1),
              v25 + *((uint32_t *)this + 65) * (v14 % 3u - 1),
              v26,
              0,
              1,
              *((uint32_t *)this + 63),
              (*(this + 255) << 24) | 0xFFFFFF);
            v14 = v23;
          }
          v23 = ++v14;
        }
        while ( v14 < 9 );
      }
    }
    sub_491D00(dword_79C0B0, v6 + *((uint32_t *)this + 67), v25 + *((uint32_t *)this + 68), v26);
  }
  for ( ; v9 != *((uint32_t **)this + 32); v9 = (uint32_t *)*v9 )
  {
    if ( *((uint8_t *)v9 + 25) == 0 )
    {
      sub_4938F0(v9[3]);
      if ( LOBYTE(v26) != 0 )
      {
        v15 = v9[4];
        v16 = v6 - v15;
      }
      else
      {
        v16 = v6 + v9[4];
      }
      LOBYTE(v15) = (*((uint8_t *)v9 + 24) != 0) - 1;
      sub_491D00(dword_79C0B0, v16, v25 + v9[5], COERCE_FLOAT(LODWORD(v26) & v15));
    }
  }
  result = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int, uint8_t))(*(uint32_t *)this + 324))(
             this,
             1,
             v6,
             v25,
             LOBYTE(v26));
  if ( *((uint32_t *)this + 41) != 0 )
    result = sub_50EB40(v6, v25, 255);
  if ( *((uint32_t *)this + 42) != 0 )
    return sub_50E750(v6, v25);
  return result;
}


// ------------------------------------------------------------
// 0x499FF0 sub_499FF0 —— 主播放驱动·usercall 变体（ecx/ebx 传参；+44 尾帧事件）
// ------------------------------------------------------------
int /*usercall*/ sub_499FF0@<eax>(float *pArg1@<ecx>, float fArg2@<ebx>)
{
  int v3; // ecx
  int pObj; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  uint32_t *v10; // eax
  uint32_t *v11; // edi
  int v12; // edx
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int result; // eax
  int v22; // esi
  int v23; // [esp-Ch] [ebp-20h]
  int v24; // [esp-8h] [ebp-1Ch]
  int v25; // [esp+8h] [ebp-Ch]
  int v26; // [esp+8h] [ebp-Ch]
  int v27; // [esp+Ch] [ebp-8h]
  float v28; // [esp+10h] [ebp-4h]

  v3 = *((uint32_t *)pArg1 + 30);
  if ( v3 != 0 )
  {
    sub_4938F0(v3);
    pObj = *(uint32_t *)(*((uint32_t *)pArg1 + 28) + 104);
    v5 = *((uint32_t *)pArg1 + 57);
    v25 = v5;
    if ( pObj != 0 && 100.0 != ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)pObj + 64))(pObj) )
    {
      if ( v5 == -1 )
        v25 = 255;
      v5 = (uint64_t)(((double (/*thiscall*/ *)(uint32_t))*(uint32_t *)(**(uint32_t **)(*((uint32_t *)pArg1 + 28) + 104) + 64))(*(uint32_t *)(*((uint32_t *)pArg1 + 28) + 104))
                            * (double)v25
                            * 0.0099999998);
    }
    sub_491F80(*((uint32_t *)pArg1 + 30), *((uint32_t *)pArg1 + 54), *((uint32_t *)pArg1 + 55), *((uint32_t *)pArg1 + 56), v5, 1);
    if ( (*(uint8_t (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 276))(pArg1) != 0 )
      sub_492080(*((uint32_t *)pArg1 + 30), pArg1[61]);
  }
  v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 36))(pArg1) + 8);
  v6 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 120))(pArg1);
  v27 = sub_45E490(v6, v24);
  v23 = *(uint32_t *)((*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 36))(pArg1) + 8);
  v7 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 128))(pArg1);
  v8 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)pArg1 + 124))(pArg1, v7);
  v9 = sub_45E4D0(v8, v23, 0, fArg2);
  v26 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 128))(pArg1);
  LOBYTE(v28) = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 152))(pArg1) != 1;
  (*(void (/*thiscall*/ **)(float *, uint32_t, int, int, uint8_t))(*(uint32_t *)pArg1 + 328))(
    pArg1,
    0,
    v27 + *((uint32_t *)pArg1 + 67),
    v9 + *((uint32_t *)pArg1 + 68),
    LOBYTE(v28));
  v10 = *((uint32_t **)pArg1 + 32);
  v11 = (uint32_t *)*v10;
  if ( (uint32_t *)*v10 != v10 )
  {
    do
    {
      if ( (int)v11[2] >= 0 )
        break;
      sub_4938F0(v11[3]);
      if ( *((uint8_t *)v11 + 25) != 0 )
      {
        v14 = LOBYTE(v28) != 0 ? v27 - v11[4] : v27 + v11[4];
        LOBYTE(v13) = (*((uint8_t *)v11 + 24) != 0) - 1;
        sub_491D00(v11[3], dword_79C0B0, v14, v9 + v11[5], COERCE_FLOAT(LODWORD(v28) & v13));
      }
      else
      {
        v15 = LOBYTE(v28) != 0 ? v27 - v11[4] : v27 + v11[4];
        LOBYTE(v12) = (*((uint8_t *)v11 + 24) != 0) - 1;
        sub_491EA0(
          v11[3],
          dword_79C0B0,
          v15,
          v9 + v11[5],
          COERCE_FLOAT(LODWORD(v28) & v12),
          v26,
          0.40000001,
          0.30000001,
          100);
      }
      v11 = (uint32_t *)*v11;
    }
    while ( v11 != *((uint32_t **)pArg1 + 32) );
  }
  v16 = *((uint32_t *)pArg1 + 30);
  if ( v16 != 0 )
    sub_491EA0(v16, dword_79C0B0, v27, v9, v28, v26, 0.40000001, 0.30000001, 100);
  for ( ; v11 != *((uint32_t **)pArg1 + 32); v11 = (uint32_t *)*v11 )
  {
    sub_4938F0(v11[3]);
    if ( *((uint8_t *)v11 + 25) != 0 )
    {
      if ( LOBYTE(v28) != 0 )
        v19 = v27 - v11[4];
      else
        v19 = v27 + v11[4];
      LOBYTE(v18) = (*((uint8_t *)v11 + 24) != 0) - 1;
      sub_491D00(v11[3], dword_79C0B0, v19, v9 + v11[5], COERCE_FLOAT(LODWORD(v28) & v18));
    }
    else
    {
      if ( LOBYTE(v28) != 0 )
        v20 = v27 - v11[4];
      else
        v20 = v27 + v11[4];
      LOBYTE(v17) = (*((uint8_t *)v11 + 24) != 0) - 1;
      sub_491EA0(
        v11[3],
        dword_79C0B0,
        v20,
        v9 + v11[5],
        COERCE_FLOAT(LODWORD(v28) & v17),
        v26,
        0.40000001,
        0.30000001,
        100);
    }
  }
  (*(void (/*thiscall*/ **)(float *, int, int, int))(*(uint32_t *)pArg1 + 328))(pArg1, 1, v27, v9);
  result = dword_8F7A24;
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    if ( *(uint32_t *)(result + 44) != 0 )
    {
      result = *((uint32_t *)pArg1 + 24);
      if ( result == 273 || result == 529 )
      {
        v22 = *((uint32_t *)pArg1 + 30);
        if ( v22 != 0 )
          *(uint8_t *)(v22 + 161) = 1;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x49A320 sub_49A320 —— 播放状态切换（+50/+51/+52 位组、子链级联、特效槽 +40）
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_49A320(uint32_t *this, int nArg2, uint32_t **uArg3, int nArg4)
{
  uint32_t **result; // eax
  int nArg22; // ebx
  int fld_e50; // edi
  int fld_e30; // edi
  int v9; // eax
  uint32_t *v10; // edi
  int v11; // eax
  uint32_t *v12; // edi
  int j; // edi
  int pObj; // eax
  int i; // edi
  int pObj2; // eax
  int fld_e502; // [esp+14h] [ebp+8h]

  result = uArg3;
  nArg22 = nArg2;
  if ( nArg2 != 0 && uArg3 == nullptr )
    nArg22 = 0;
  fld_e50 = *(this + 50);
  fld_e502 = fld_e50;
  *(this + 50) = nArg22;
  if ( nArg22 != 0 )
  {
    *(this + 51) = uArg3;
    result = (uint32_t **)(nArg4 + sub_699000(this + 2));  // 【clock_now(clk)】
    *(this + 52) = result;
  }
  if ( fld_e50 != nArg22 )
  {
    if ( fld_e50 < 1 )
    {
      if ( nArg22 >= 1 )
      {
        fld_e30 = *(this + 30);
        if ( fld_e30 != 0 )
        {
          if ( *(uint32_t *)(fld_e30 + 212) != 0 )
            *((uint8_t *)this + 212) = sub_4910C0();
          else
            *((uint8_t *)this + 212) = *(uint8_t *)(fld_e30 + 169);
          sub_4939E0(1);
        }
        else
        {
          *((uint8_t *)this + 212) = 0;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )
        {
          v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 844))(this);
        }
        else
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 65) == 0 )
            goto LABEL_20;
          v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
        }
        sub_699030(v9);  // 【clock_freeze(clk)】
LABEL_20:
        sub_4A0680(1);
        sub_699030(this + 9);  // 【clock_freeze(clk)】
        result = (uint32_t **)*(this + 32);
        v10 = *result;
        if ( *result != result )
        {
          do
          {
            result = (uint32_t **)sub_4939E0(1);
            v10 = (uint32_t *)*v10;
          }
          while ( v10 != (uint32_t *)*(this + 32) );
        }
      }
LABEL_34:
      if ( fld_e502 >= 2 )
      {
        if ( nArg22 < 2 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *))(*this + 700))(this);
            sub_53F720(0);
            for ( i = 0; i < 17; ++i )
            {
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, i) != 0 )
              {
                pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 772))(this, i);
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 36))(pObj2, 0);
              }
            }
          }
          return (uint32_t **)sub_698FE0(this + 16);  // 【clock_unfreeze(clk)】
        }
      }
      else if ( nArg22 >= 2 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 700))(this);
          sub_53F720(1);
          for ( j = 0; j < 17; ++j )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, j) != 0 )
            {
              pObj = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 772))(this, j);
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 36))(pObj, 1);
            }
          }
        }
        return (uint32_t **)sub_699030(this + 16);  // 【clock_freeze(clk)】
      }
      return result;
    }
    if ( nArg22 >= 1 )
      goto LABEL_34;
    if ( *((uint8_t *)this + 212) == 0 && *(this + 30) != 0 )
      sub_4939E0(0);
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )
    {
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 844))(this);
    }
    else
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 65) == 0 )
        goto LABEL_32;
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);
    }
    sub_698FE0(v11);  // 【clock_unfreeze(clk)】
LABEL_32:
    sub_4A0680(0);
    sub_698FE0(this + 9);  // 【clock_unfreeze(clk)】
    result = (uint32_t **)*(this + 32);
    v12 = *result;
    if ( *result != result )
    {
      do
      {
        result = (uint32_t **)sub_4939E0(0);
        v12 = (uint32_t *)*v12;
      }
      while ( v12 != (uint32_t *)*(this + 32) );
    }
    goto LABEL_34;
  }
  return result;
}


// ------------------------------------------------------------
// 0x49A590 sub_49A590
// ------------------------------------------------------------
int /*thiscall*/ sub_49A590(uint32_t *this, int nArg2)
{
  uint32_t **fld_e32; // eax
  uint32_t *v4; // esi

  *(this + 23) = nArg2;
  sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  if ( *(this + 30) != 0 )
    sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  fld_e32 = (uint32_t **)*(this + 32);
  v4 = *fld_e32;
  if ( *fld_e32 != fld_e32 )
  {
    do
    {
      sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
      v4 = (uint32_t *)*v4;
    }
    while ( v4 != (uint32_t *)*(this + 32) );
  }
  return sub_4A0740(nArg2);
}



// ------------------------------------------------------------
// 0x49A600 sub_49A600
// ------------------------------------------------------------
char /*thiscall*/ sub_49A600(void *this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  char result; // al
  int pThis_40; // eax
  uint8_t v7; // bl
  int v8; // eax

  result = pszArg2;
  if ( pszArg2 == 0 && ((void *)dword_8F7C08 == this || (void *)dword_8F7C04 == this) )
  {
    pThis_40 = sub_699000((int)this + 64);  // 【clock_now(clk)】
    v7 = sub_42B420(150, 255, pThis_40, 400);
    sub_491530(2, 0);
    v8 = sub_418DD0(101);
    sub_424760(dword_79C0B0, nArg3 - 63, nArg4 - 21, v8, 1.0, 1065353216, 0.0, (v7 << 24) | 0xFFFFFF, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
    return sub_491630(2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49A6B0 sub_49A6B0
// ------------------------------------------------------------
void /*thiscall*/ sub_49A6B0(void ***this, void *pArg2)
{
  void **fld_e32; // ecx
  void **v4; // eax

  if ( pArg2 != nullptr )
  {
    fld_e32 = *(this + 32);
    v4 = (void **)*fld_e32;
    if ( *fld_e32 != fld_e32 )
    {
      while ( v4[3] != pArg2 )
      {
        v4 = (void **)*v4;
        if ( v4 == fld_e32 )
          return;
      }
      if ( v4 != *(this + 32) )
      {
        *(uint32_t *)v4[1] = *v4;
        *((uint32_t *)*v4 + 1) = v4[1];
        j__free(v4);
        *(this + 33) = (void **)((char *)*(this + 33) - 1);
      }
    }
  }
}



// ------------------------------------------------------------
// 0x49A720 sub_49A720
// ------------------------------------------------------------
int /*thiscall*/ sub_49A720(uint32_t *this, unsigned int uArg2)
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
  if ( 214748364 - fld_e2 < uArg2 )
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
// 0x49A7B0 sub_49A7B0
// ------------------------------------------------------------
void /*thiscall*/ sub_49A7B0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, char pszArg7)
{
  uint32_t **fld_e32; // eax
  uint32_t *v9; // esi
  bool v10; // zf
  uint32_t *v11; // eax
  uint32_t *pThis_1F; // ecx
  uint32_t *v13; // edi
  uint32_t v14[4]; // [esp+8h] [ebp-14h] BYREF
  char pszArg62; // [esp+18h] [ebp-4h]
  char pszArg72; // [esp+19h] [ebp-3h]

  if ( nArg3 != 0 )
  {
    sub_699070(*(this + 23));  // 【clock_bind_domain(clk, newDomainId)】
    v14[3] = nArg5;
    pszArg72 = pszArg7;
    fld_e32 = (uint32_t **)*(this + 32);
    v14[1] = nArg3;
    v9 = *fld_e32;
    v10 = *fld_e32 == fld_e32;
    v14[2] = nArg4;
    v14[0] = nArg2;
    pszArg62 = pszArg6;
    if ( !v10 )
    {
      do
      {
        if ( v9[2] > nArg2 )
          break;
        v9 = (uint32_t *)*v9;
      }
      while ( v9 != fld_e32 );
    }
    v11 = sub_499C20((int)v9, v9[1], v14);
    pThis_1F = this + 31;
    v13 = v11;
    sub_49A720(pThis_1F, 1u);
    v9[1] = v13;
    *(uint32_t *)v13[1] = v13;
    sub_4926A0(nArg3);
  }
}



// ------------------------------------------------------------
// 0x49A850 sub_49A850
// ------------------------------------------------------------
void /*thiscall*/ sub_49A850(void *this)
{
  int pThis_38; // eax
  int pThis_1C; // ebx
  void **pThis_22; // ebx
  unsigned int i; // ebx
  int pThis_24; // ecx
  int v7; // edi
  void **v8; // ecx
  void *pThis_29; // ebx
  void *pThis_2A; // ebx
  void **v11; // [esp+Ch] [ebp-4h]

  if ( lpCriticalSection != nullptr )
  {
    pThis_38 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);
    sub_65DF60(pThis_38);
  }
  if ( *((uint32_t *)this + 29) != 0 )
    sub_45F1E0(this);
  pThis_1C = *((uint32_t *)this + 28);
  if ( pThis_1C != 0 )
  {
    sub_499880(*((uint32_t *)this + 28));
    sub_657740(pThis_1C, 204);
  }
  pThis_22 = *((void ***)this + 34);
  *((uint32_t *)this + 28) = 0;
  if ( pThis_22 != nullptr )
  {
    sub_42AF90(pThis_22);
    sub_657740(pThis_22, 228);
  }
  *((uint32_t *)this + 34) = 0;
  for ( i = 0; ; ++i )
  {
    pThis_24 = *((uint32_t *)this + 36);
    if ( pThis_24 == 0 || i >= (*((uint32_t *)this + 37) - pThis_24) >> 2 )
      break;
    v7 = 4 * i;
    v8 = *(void ***)(pThis_24 + 4 * i);
    if ( v8 != nullptr )
    {
      v11 = v8;
      sub_42AF90(v8);
      sub_657740(v11, 228);
    }
    *(uint32_t *)(v7 + *((uint32_t *)this + 36)) = 0;
  }
  if ( *((uint32_t *)this + 36) != 0 )
    j__free(*((void **)this + 36));
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  pThis_29 = *((void **)this + 41);
  if ( pThis_29 != nullptr )
  {
    sub_4999D0(*((uint32_t *)this + 41));
    j__free(pThis_29);
  }
  pThis_2A = *((void **)this + 42);
  *((uint32_t *)this + 41) = 0;
  if ( pThis_2A != nullptr )
  {
    sub_50E950(pThis_2A);
    j__free(pThis_2A);
  }
  *((uint32_t *)this + 42) = 0;
}



// ------------------------------------------------------------
// 0x49A9A0 sub_49A9A0
// ------------------------------------------------------------
char /*thiscall*/ sub_49A9A0(int this)
{
  *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint8_t *)(this + 73) = 0;
  *(uint8_t *)(this + 74) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x49A9D0 sub_49A9D0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_49A9D0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)
{
  uint32_t *result; // eax

  for ( result = uArg1; result != uArg2; ++result )
    *result = *uArg3;
  return result;
}



// ------------------------------------------------------------
// 0x49A9F0 sub_49A9F0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49A9F0(uint32_t *this)
{
  unsigned int i; // edx
  int fld_e9; // esi
  unsigned int result; // eax

  *(this + 7) = 0;
  for ( i = 0; ; ++i )
  {
    fld_e9 = *(this + 9);
    if ( fld_e9 == 0 )
      break;
    result = (*(this + 10) - fld_e9) >> 2;
    if ( i >= result )
      break;
    result = *(uint32_t *)(fld_e9 + 4 * i);
    *(uint32_t *)(result + 12) = 0;
    *(uint8_t *)(result + 16) = 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49AA30 sub_49AA30
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49AA30(uint32_t *this, int nArg2, char pszArg3)
{
  unsigned int i; // edi
  int fld_e12; // edx
  int v5; // esi
  unsigned int result; // eax

  for ( i = 0; ; ++i )
  {
    fld_e12 = *(this + 12) + 4 * *(this + 10);
    v5 = *(uint32_t *)(*(uint32_t *)fld_e12 + 36);
    result = *(uint32_t *)fld_e12 + 32;
    if ( v5 == 0 )
      break;
    result = (*(uint32_t *)(*(uint32_t *)fld_e12 + 40) - v5) >> 2;
    if ( i >= result )
      break;
    if ( **(int16_t **)(4 * i + *(uint32_t *)(*(uint32_t *)fld_e12 + 36)) == nArg2 )
      *(uint8_t *)(*(uint32_t *)(4 * i + *(uint32_t *)(*(uint32_t *)fld_e12 + 36)) + 16) = pszArg3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49AA90 sub_49AA90 —— 字符串参数 setter（保存于 +48/+52；未匹配走 off_77F3FC）
// ------------------------------------------------------------
char /*thiscall*/ sub_49AA90(int this, const char *pArg2)
{
  unsigned int i; // edi
  int fld_30; // ecx
  int fld_302; // edx
  int pThis_10; // esi

  for ( i = 0; ; ++i )
  {
    fld_30 = *(uint32_t *)(this + 48);
    if ( fld_30 == 0 || i >= (*(uint32_t *)(this + 52) - fld_30) >> 2 )
      break;
    if ( sub_40BF00(*(std::_String_base **)(fld_30 + 4 * i), 0, *(uint32_t *)(*(uint32_t *)(fld_30 + 4 * i) + 20), pArg2, strlen(pArg2)) == 0 )
    {
      *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 1;
      *(uint8_t *)(this + 8) = 1;
      *(uint8_t *)(this + 73) = 0;
      *(uint8_t *)(this + 74) = 0;
      sub_698F90(this + 60, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      fld_302 = *(uint32_t *)(this + 48);
      *(uint32_t *)(this + 40) = i;
      sub_49A9F0(*(uint32_t **)(fld_302 + 4 * i));
      return 1;
    }
  }
  if ( *(uint32_t *)(this + 36) < 0x10u )
    pThis_10 = this + 16;
  else
    pThis_10 = *(uint32_t *)(this + 16);
  off_77F3FC(aErrorS, pThis_10, pArg2);
  return 0;
}



// ------------------------------------------------------------
// 0x49AB50 sub_49AB50
// ------------------------------------------------------------
int /*thiscall*/ sub_49AB50(uint32_t *this)
{
  uint32_t *fld_e12; // edx
  uint32_t *fld_e122; // eax
  int v3; // esi
  int v4; // edi
  unsigned int v5; // edx
  unsigned int v6; // esi

  fld_e12 = *(uint32_t **)(*(this + 12) + 4 * *(this + 10));
  fld_e122 = fld_e12;
  v3 = fld_e12[9];
  v4 = fld_e12[7];
  if ( v3 != 0 )
    v5 = (fld_e12[10] - v3) >> 2;
  else
    v5 = 0;
  v6 = fld_e122[7] + 1;
  if ( v6 < v5 )
    fld_e122[7] = v6;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 12))(
           this,
           v4,
           *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28));
}



// ------------------------------------------------------------
// 0x49ABA0 sub_49ABA0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49ABA0(uint32_t *this, int nArg2)
{
  int fld_e12; // ecx
  int fld_e10; // eax
  int v5; // edx
  unsigned int result; // eax
  int v7; // esi

  fld_e12 = *(this + 12);
  fld_e10 = *(this + 10);
  v5 = *(uint32_t *)(fld_e12 + 4 * fld_e10);
  result = fld_e12 + 4 * fld_e10;
  if ( nArg2 == *(uint32_t *)(v5 + 28) )
  {
    v7 = *(uint32_t *)(*(uint32_t *)(v5 + 36) + 4 * nArg2);
    result = sub_699000((int)(this + 15)) - *(uint32_t *)(v7 + 12);  // 【clock_now(clk)】
    if ( result >= *(uint32_t *)(v7 + 8) )
      return sub_49AB50(this);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49ABF0 sub_49ABF0
// ------------------------------------------------------------
char /*thiscall*/ sub_49ABF0(uint32_t *this, int nArg2)
{
  int v2; // esi
  int fld_e12; // eax
  int v4; // eax
  uint32_t *v5; // eax

  fld_e12 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * nArg2;
  v2 = *(uint32_t *)fld_e12;
  LOBYTE(fld_e12) = *(uint8_t *)(*(uint32_t *)fld_e12 + 20);
  if ( (uint8_t)fld_e12 == 0 )
  {
    if ( *(uint32_t *)(v2 + 52) < 0x10u )
      v4 = v2 + 32;
    else
      v4 = *(uint32_t *)(v2 + 32);
    v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v4);
    fld_e12 = sub_418DD0(v5, *(uint32_t *)(v2 + 24));
    if ( fld_e12 != 0 )
      LOBYTE(fld_e12) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e12 + 152))(
                     fld_e12,
                     dword_6CB988[*(int16_t *)(v2 + 22)],
                     dword_6CB990[*(int16_t *)(v2 + 22)],
                     dword_79C0B0);
  }
  return fld_e12;
}



// ------------------------------------------------------------
// 0x49AC70 sub_49AC70
// ------------------------------------------------------------
int /*thiscall*/ sub_49AC70(uint32_t *this, int nArg2)
{
  int fld_e12; // eax
  int v4; // esi
  int v5; // eax
  uint32_t *v6; // edi
  int pThis_F; // ebx
  int pObj; // eax
  int result; // eax
  float v10; // [esp+4h] [ebp-34h]
  float v11; // [esp+8h] [ebp-30h]
  int v13; // [esp+28h] [ebp-10h]
  int v14; // [esp+2Ch] [ebp-Ch]
  int v15; // [esp+2Ch] [ebp-Ch]
  int v16; // [esp+30h] [ebp-8h]
  int v17; // [esp+34h] [ebp-4h]

  fld_e12 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * nArg2;
  v4 = *(uint32_t *)fld_e12;
  if ( *(uint32_t *)(*(uint32_t *)fld_e12 + 44) < 0x10u )
    v5 = v4 + 24;
  else
    v5 = *(uint32_t *)(v4 + 24);
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);
  v14 = *(uint32_t *)(sub_418DD0(v6, *(uint32_t *)(v4 + 48)) + 20);
  v16 = 0;
  v17 = 0;
  v13 = 480 - *(uint32_t *)(sub_418DD0(v6, *(uint32_t *)(v4 + 48)) + 24);
  pThis_F = sub_699000((int)(this + 15)) - *(uint32_t *)(v4 + 12);  // 【clock_now(clk)】
  switch ( *(uint32_t *)(v4 + 4) )
  {
    case 3:
      v16 = -v14;
      v17 = 0;
      break;
    case 4:
      v16 = 0;
      v17 = -v14;
      break;
    case 5:
      v16 = 640;
      v17 = 640 - v14;
      break;
    case 6:
      v16 = 640 - v14;
      v17 = 640;
      break;
    default:
      break;
  }
  v11 = (float)v17;
  v10 = (float)v16;
  v15 = (uint64_t)sub_4049F0(v10, v11, pThis_F, 300, 1);
  pObj = sub_418DD0(v6, *(uint32_t *)(v4 + 48));
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v15, v13, dword_79C0B0);
  result = nArg2;
  if ( *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28) == nArg2 && (*(uint8_t *)(v4 + 52) == 1 || pThis_F >= 300) )
    return sub_49AB50(this);
  return result;
}



// ------------------------------------------------------------
// 0x49ADF0 sub_49ADF0
// ------------------------------------------------------------
int /*thiscall*/ sub_49ADF0(uint32_t *this, int nArg2)
{
  int fld_e12; // eax
  int v4; // esi
  int v5; // eax
  int pThis_F; // edi
  int pObj; // eax
  int fld_e10; // edx
  int fld_e122; // eax
  int v10; // ecx
  int result; // eax
  float v12; // [esp+4h] [ebp-28h]
  float v13; // [esp+8h] [ebp-24h]
  uint32_t *v14; // [esp+20h] [ebp-Ch]
  int v15; // [esp+24h] [ebp-8h]
  int v16; // [esp+24h] [ebp-8h]
  int v17; // [esp+28h] [ebp-4h]

  fld_e12 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * nArg2;
  v4 = *(uint32_t *)fld_e12;
  if ( *(uint32_t *)(*(uint32_t *)fld_e12 + 44) < 0x10u )
    v5 = v4 + 24;
  else
    v5 = *(uint32_t *)(v4 + 24);
  v14 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);
  v15 = 0;
  v17 = 0;
  pThis_F = sub_699000((int)(this + 15)) - *(uint32_t *)(v4 + 12);  // 【clock_now(clk)】
  if ( *(uint32_t *)(v4 + 4) == 7 )
  {
    v15 = 0;
    v17 = 255;
  }
  else if ( *(uint32_t *)(v4 + 4) == 8 )
  {
    v15 = 255;
    v17 = 0;
  }
  v13 = (float)v17;
  v12 = (float)v15;
  v16 = (uint64_t)sub_4049C0(v12, v13, pThis_F, 300);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  pObj = sub_418DD0(v14, *(uint32_t *)(v4 + 48));
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
      pObj,
      0,
      397,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      ((uint8_t)v16 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  fld_e10 = *(this + 10);
  fld_e122 = *(this + 12);
  v10 = *(uint32_t *)(fld_e122 + 4 * fld_e10);
  result = fld_e122 + 4 * fld_e10;
  if ( *(uint32_t *)(v10 + 28) == nArg2 && (*(uint8_t *)(v4 + 52) == 1 || pThis_F >= 300) )
    return sub_49AB50(this);
  return result;
}



// ------------------------------------------------------------
// 0x49AF20 sub_49AF20
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49AF20(uint32_t *this)
{
  uint32_t *pThis; // ebx
  unsigned int v2; // esi
  int pObj4; // ecx
  int v4; // edx
  unsigned int result; // eax
  int v6; // edi
  int v7; // eax
  uint32_t *v8; // esi
  int v9; // eax
  int pObj3; // eax
  int pObj2; // eax
  int pObj; // eax
  unsigned int v14; // [esp+10h] [ebp-4h]

  pThis = this;
  v2 = 0;
  v14 = 0;
  do
  {
    pObj4 = pThis[12] + 4 * pThis[10];
    v4 = *(uint32_t *)(*(uint32_t *)pObj4 + 36);
    result = *(uint32_t *)pObj4 + 32;
    if ( v4 == 0 )
      break;
    result = (*(uint32_t *)(*(uint32_t *)pObj4 + 40) - v4) >> 2;
    if ( v2 >= result )
      break;
    if ( *(uint8_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)pObj4 + 36)) + 16) != 0
      && *(uint32_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)pObj4 + 36)) + 4) == 9 )
    {
      v6 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)pObj4 + 36) + 4 * v2);
      if ( *(uint16_t *)(v6 + 22) == 0 && (int)pThis[22] > -1 )
      {
        if ( *(uint32_t *)(v6 + 52) < 0x10u )
          v7 = v6 + 32;
        else
          v7 = *(uint32_t *)(v6 + 32);
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v7);
        v9 = pThis[22];
        if ( v9 >= 10 )
        {
          pObj2 = sub_418DD0(v8, v9 % 10 + 2);
          if ( pObj2 != 0 )
          {
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(
              pObj2,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 43,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);
            pThis = this;
          }
          pObj = sub_418DD0(v8, pThis[22] / 10 + 2);
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(
              pObj,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 31,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);
        }
        else
        {
          pObj3 = sub_418DD0(v8, v9 + 2);
          if ( pObj3 != 0 )
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(
              pObj3,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 43,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);
        }
      }
    }
    result = *(uint32_t *)(*(uint32_t *)(pThis[12] + 4 * pThis[10]) + 28);
    v2 = ++v14;
  }
  while ( v14 <= result );
  return result;
}



// ------------------------------------------------------------
// 0x49B0C0 sub_49B0C0
// ------------------------------------------------------------
void /*thiscall*/ sub_49B0C0(int this)
{
  unsigned int i; // ebx
  int fld_24; // ecx
  int v4; // edi
  void *v5; // ecx

  for ( i = 0; ; ++i )
  {
    fld_24 = *(uint32_t *)(this + 36);
    if ( fld_24 == 0 || i >= (*(uint32_t *)(this + 40) - fld_24) >> 2 )
      break;
    v4 = 4 * i;
    v5 = *(void **)(fld_24 + 4 * i);
    if ( v5 != nullptr )
      j__free(v5);
    *(uint32_t *)(v4 + *(uint32_t *)(this + 36)) = 0;
  }
  if ( *(uint32_t *)(this + 36) != 0 )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  if ( *(uint32_t *)(this + 24) >= 0x10u )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x49B150 sub_49B150
// ------------------------------------------------------------
int /*thiscall*/ sub_49B150(uint32_t *this)
{
  uint8_t *pMem; // eax
  uint8_t *v3; // eax
  int result; // eax

  pMem = operator new(0x68u);
  if ( pMem != nullptr )
    v3 = sub_426BD0(pMem);
  else
    v3 = nullptr;
  *(this + 1) = v3;
  *((uint32_t *)v3 + 7) = 0;
  *((uint32_t *)v3 + 8) = 0;
  sub_69A5F0((uint32_t *)*(this + 1), 0, 0);
  result = *(this + 1);
  *(uint32_t *)(result + 68) = this;
  return result;
}



// ------------------------------------------------------------
// 0x49B1D0 sub_49B1D0 —— 图层属性四连（sub_49ABA0/49AC70/49ADF0/49ABF0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B1D0(uint32_t *this)
{
  unsigned int v2; // edi
  int fld_e12; // ecx
  int v4; // edx
  unsigned int result; // eax

  v2 = 0;
  do
  {
    fld_e12 = *(this + 12) + 4 * *(this + 10);
    v4 = *(uint32_t *)(*(uint32_t *)fld_e12 + 36);
    result = *(uint32_t *)fld_e12 + 32;
    if ( v4 == 0 )
      break;
    result = (*(uint32_t *)(*(uint32_t *)fld_e12 + 40) - v4) >> 2;
    if ( v2 >= result )
      break;
    if ( *(uint8_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)fld_e12 + 36)) + 16) != 0 )
    {
      switch ( *(uint32_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)fld_e12 + 36)) + 4) )
      {
        case 2:
          sub_49ABA0(this, v2);
          break;
        case 3:
        case 4:
        case 5:
        case 6:
          sub_49AC70(this, v2);
          break;
        case 7:
        case 8:
          sub_49ADF0(this, v2);
          break;
        case 9:
          sub_49ABF0(this, v2);
          break;
        default:
          break;
      }
    }
    result = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28);
    ++v2;
  }
  while ( v2 <= result );
  return result;
}



// ------------------------------------------------------------
// 0x49B290 sub_49B290
// ------------------------------------------------------------
char /*thiscall*/ sub_49B290(int this, int nArg2, int nArg3)
{
  int pThis_3C; // ebx
  uint32_t *fld_30; // edi
  int v6; // eax

  pThis_3C = this + 60;
  fld_30 = *(uint32_t **)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 48) + 4 * *(uint32_t *)(this + 40)) + 36) + 4 * nArg3);
  fld_30[3] = sub_699000(this + 60);  // 【clock_now(clk)】
  v6 = fld_30[1];
  switch ( v6 )
  {
    case 0:
    case 9:
      goto LABEL_5;
    case 1:
      *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 0;
      *(uint8_t *)(this + 8) = 0;
      *(uint8_t *)(pThis_3C + 13) = 0;
      *(uint8_t *)(pThis_3C + 14) = 0;
      LOBYTE(v6) = 0;
      return v6;
    case 10:
      sub_49AA30((uint32_t *)this, fld_30[2], 0);
      goto LABEL_5;
    case 11:
      sub_49AA30((uint32_t *)this, fld_30[2], 1);
LABEL_5:
      LOBYTE(v6) = sub_49AB50((uint32_t *)this);
      break;
    default:
      return v6;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x49B330 sub_49B330
// ------------------------------------------------------------
char /*thiscall*/ sub_49B330(uint32_t *this, int nArg2, int nArg3)
{
  char result; // al
  int fld_e12; // eax
  int v6; // edx

  result = sub_49B290((int)this, nArg2, nArg3);
  if ( *(this + 10) == 1 )
  {
    fld_e12 = *(this + 12);
    v6 = *(uint32_t *)(fld_e12 + 4);
    result = fld_e12 + 4;
    if ( *(uint32_t *)(v6 + 28) == 9 )
      *(this + 22) = -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49B370 sub_49B370
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B370(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  unsigned int v3; // ebx
  unsigned int result; // eax
  int fld_e12; // ecx
  int v6; // ecx
  void *Block; // [esp+Ch] [ebp-4h]

  fld_e1 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);
  v3 = 0;
  if ( fld_e1 != nullptr )
    result = (**fld_e1)(fld_e1, 1);
  *(this + 1) = 0;
  while ( 1 )
  {
    fld_e12 = *(this + 12);
    if ( fld_e12 == 0 )
      break;
    result = (*(this + 13) - fld_e12) >> 2;
    if ( v3 >= result )
      break;
    v6 = *(uint32_t *)(4 * v3 + fld_e12);
    if ( v6 != 0 )
    {
      Block = (void *)v6;
      sub_49B0C0(v6);
      j__free(Block);
    }
    result = 4 * v3 + *(this + 12);
    *(uint32_t *)result = 0;
    ++v3;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49B3F0 sub_49B3F0
// ------------------------------------------------------------
char /*thiscall*/ sub_49B3F0(int this, int nArg2)
{
  char result; // al

  result = nArg2;
  if ( nArg2 == *(uint32_t *)(this + 4) )
  {
    result = *(uint8_t *)(this + 8);
    if ( result != 0 )
    {
      sub_49B1D0((uint32_t *)this);
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 8))(this);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49B420 sub_49B420
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49B420(uint32_t *this, int nArg2, int nArg3)
{
  char *pThis_7; // ecx

  *(this + 1) = nArg3;
  pThis_7 = (char *)(this + 7);
  *(uint16_t *)this = -1;
  *(this + 2) = -1;
  *(this + 3) = 0;
  *((uint8_t *)this + 16) = 1;
  *((uint32_t *)pThis_7 + 6) = 15;
  *((uint32_t *)pThis_7 + 5) = 0;
  pThis_7[4] = 0;
  *((uint8_t *)this + 20) = -1;
  *((uint16_t *)this + 11) = 0;
  *(this + 6) = 0;
  sub_4015C0((size_t *)pThis_7, szPassword, 0);  // 【std::string构造赋值】
  return this;
}



// ------------------------------------------------------------
// 0x49B4A0 sub_49B4A0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49B4A0(uint32_t *this, int nArg2, int nArg3)
{
  char *pThis_5; // ecx

  pThis_5 = (char *)(this + 5);
  *(uint16_t *)this = -1;
  *(this + 1) = nArg3;
  *(this + 2) = -1;
  *(this + 3) = 0;
  *((uint8_t *)this + 16) = 1;
  *((uint32_t *)pThis_5 + 6) = 15;
  *((uint32_t *)pThis_5 + 5) = 0;
  pThis_5[4] = 0;
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 12) = 0;
  *((uint8_t *)this + 52) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x49B520 sub_49B520 —— 帧字段读组（+40/+48/+52/+56 → 打包返回）
// ------------------------------------------------------------
size_t */*thiscall*/ sub_49B520(int this)
{
  *(uint32_t *)(this + 4) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 40) = -1;
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 73) = 0;
  *(uint8_t *)(this + 74) = 0;
  return sub_4015C0((size_t *)(this + 12), szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x49B570 sub_49B570 —— 帧字段读组·变体（+48/+52 + 盒 +56 + 特效 +40）
// ------------------------------------------------------------
size_t */*thiscall*/ sub_49B570(int this)
{
  unsigned int i; // ebx
  int fld_30; // ecx
  int v4; // ecx
  void *Block; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    fld_30 = *(uint32_t *)(this + 48);
    if ( fld_30 == 0 || i >= (*(uint32_t *)(this + 52) - fld_30) >> 2 )
      break;
    v4 = *(uint32_t *)(fld_30 + 4 * i);
    if ( v4 != 0 )
    {
      Block = (void *)v4;
      sub_49B0C0(v4);
      j__free(Block);
    }
    *(uint32_t *)(4 * i + *(uint32_t *)(this + 48)) = 0;
  }
  if ( *(uint32_t *)(this + 48) != 0 )
    j__free(*(void **)(this + 48));
  *(uint32_t *)(this + 48) = 0;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint8_t *)(this + 8) = 0;
  *(uint32_t *)(this + 40) = -1;
  *(uint8_t *)(this + 73) = 0;
  *(uint8_t *)(this + 74) = 0;
  return sub_4015C0((size_t *)(this + 12), szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x49B610 sub_49B610
// ------------------------------------------------------------
void /*noreturn*/ sub_49B610()
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
// 0x49B680 sub_49B680
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B680(int this, uint32_t *Src, unsigned int uArg3, int *pDwArg4)
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
      sub_49B610(this);
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



// ============================================================
// §M 0x49B860-0x49BE70  对话脚本解析器 sub_49B930 + COUNT_DOWN
// ============================================================
// ------------------------------------------------------------
// 0x49B860 sub_49B860
// ------------------------------------------------------------
int /*thiscall*/ sub_49B860(int this)
{
  *(uint32_t *)(this + 24) = 15;
  *(uint32_t *)(this + 20) = 0;
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  sub_4015C0((size_t *)this, szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 28) = 0;
  if ( *(uint32_t *)(this + 36) != 0 )
    j__free(*(void **)(this + 36));
  *(uint32_t *)(this + 36) = 0;
  *(uint32_t *)(this + 40) = 0;
  *(uint32_t *)(this + 44) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x49B8E0 sub_49B8E0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B8E0(int **this, int *pDwArg2)
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
    return sub_49B680((int)this, *(this + 2), 1u, pDwArg2);
  fld_e22 = *(this + 2);
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = (int *)result;
  return result;
}



// ------------------------------------------------------------
// 0x49B930 sub_49B930 —— ★对话脚本解析器
//   [talk name]→说话人条目(0x30B 节点+字符串)；[commands]→命令序列：off_790B94 命令表
//   12 条，0/1→0x14B 节点；2/10/11→0x14B+参数；3..8→0x38B 节点(+48 参数、+52
//   [pass next command] 标志)；9→[img] 图像节点(+20/+22/+24)。
//   注意：节点 +48/+52 是对话命令字段，与 88B 帧结构的 DELAY/DAMAGE TYPE 无关。
// ------------------------------------------------------------
char /*thiscall*/ sub_49B930(uint32_t *this, void *ArgList)
{
  void *v2; // esi
  void *pMem4; // eax
  void *v6; // ecx
  void *p_Src; // esi
  int fld_e12; // eax
  int j; // edi
  uint32_t *pMem; // eax
  int v11; // esi
  uint32_t *pMem2; // eax
  int v13; // esi
  int i; // [esp+8h] [ebp-78h]
  void *fld_e13; // [esp+14h] [ebp-6Ch] BYREF
  void *pMem3; // [esp+18h] [ebp-68h] BYREF
  uint8_t v18[4]; // [esp+1Ch] [ebp-64h] BYREF
  void *v19; // [esp+20h] [ebp-60h]
  unsigned int v20; // [esp+30h] [ebp-50h]
  unsigned int v21; // [esp+34h] [ebp-4Ch]
  uint8_t v22[4]; // [esp+38h] [ebp-48h] BYREF
  void *Block; // [esp+3Ch] [ebp-44h]
  unsigned int v24; // [esp+4Ch] [ebp-34h]
  unsigned int v25; // [esp+50h] [ebp-30h]
  uint8_t v26[4]; // [esp+54h] [ebp-2Ch] BYREF
  void *Src; // [esp+58h] [ebp-28h] BYREF
  unsigned int v28; // [esp+68h] [ebp-18h]
  unsigned int v29; // [esp+6Ch] [ebp-14h]
  int dword_796E502; // [esp+70h] [ebp-10h]
  int v31; // [esp+7Ch] [ebp-4h]

  v2 = ArgList;
  dword_796E502 = dword_796E50;
  if ( (uint8_t)sub_442A10((char)szPassword, (int)ArgList) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 4))(this);
    sub_4015C0(v2, strlen((const char *)v2));  // 【std::string构造赋值】
    v21 = 15;
    v20 = 0;
    LOBYTE(v19) = 0;
    v31 = 2;
    v29 = 15;
    v28 = 0;
    LOBYTE(Src) = 0;
    v25 = 15;
    v24 = 0;
    LOBYTE(Block) = 0;
    fld_e13 = nullptr;
    while ( (uint8_t)sub_443430(v18) != 0 )
    {
      sub_442BC0(v18);
      if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[talk name]", 0xBu) != 0 )
      {
        if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[commands]", 0xAu) == 0 )
        {
          HIBYTE(ArgList) = 0;
          for ( i = sub_4423D0((uint8_t *)&ArgList + 3); HIBYTE(ArgList) != 0; i = sub_4423D0((uint8_t *)&ArgList + 3) )
          {
            sub_443370();
            for ( j = 0; j < 12; ++j )
            {
              if ( sub_40BF00((std::_String_base *)v26, 0, v28, off_790B94[j], strlen(off_790B94[j])) == 0 )
              {
                switch ( j )
                {
                  case 0:
                  case 1:
                    pMem = operator new(0x14u);
                    if ( pMem != nullptr )
                    {
                      *(uint16_t *)pMem = -1;
                      pMem[1] = j;
                      pMem[2] = -1;
                      pMem[3] = 0;
                      *((uint8_t *)pMem + 16) = 1;
                      pMem3 = pMem;
                    }
                    else
                    {
                      pMem3 = nullptr;
                    }
                    goto LABEL_33;
                  case 2:
                  case 10:
                  case 11:
                    v11 = sub_4423D0(nullptr);
                    pMem2 = operator new(0x14u);
                    if ( pMem2 != nullptr )
                    {
                      *(uint16_t *)pMem2 = -1;
                      pMem2[1] = j;
                      pMem2[2] = v11;
                      pMem2[3] = 0;
                      *((uint8_t *)pMem2 + 16) = 1;
                      pMem3 = pMem2;
                    }
                    else
                    {
                      pMem3 = nullptr;
                    }
                    goto LABEL_33;
                  case 3:
                  case 4:
                  case 5:
                  case 6:
                  case 7:
                  case 8:
                    pMem3 = operator new(0x38u);
                    LOBYTE(v31) = 4;
                    if ( pMem3 != nullptr )
                      v13 = sub_49B4A0(i, j);
                    else
                      v13 = 0;
                    LOBYTE(v31) = 2;
                    *(uint32_t *)(v13 + 48) = sub_4423D0(nullptr);
                    sub_443370();
                    sub_443370();
                    *(uint8_t *)(v13 + 52) = sub_40BF00((std::_String_base *)v22, 0, v24, "[pass next command]", 0x13u) == 0;
                    goto LABEL_32;
                  case 9:
                    pMem3 = operator new(0x38u);
                    LOBYTE(v31) = 5;
                    if ( pMem3 != nullptr )
                      v13 = sub_49B420(i, 9);
                    else
                      v13 = 0;
                    LOBYTE(v31) = 2;
                    sub_443370();
                    *(uint8_t *)(v13 + 20) = sub_40BF00((std::_String_base *)v22, 0, v24, "[img]", 5u) != 0;
                    *(uint16_t *)(v13 + 22) = sub_4423D0(nullptr);
                    *(uint32_t *)(v13 + 24) = sub_4423D0(nullptr);
                    sub_443370();
LABEL_32:
                    pMem3 = (void *)v13;
LABEL_33:
                    sub_49B8E0(&pMem3);
                    break;
                  default:
                    continue;
                }
              }
            }
          }
        }
      }
      else
      {
        sub_443370();
        pMem4 = operator new(0x30u);
        fld_e13 = pMem4;
        LOBYTE(v31) = 3;
        if ( pMem4 != nullptr )
          v6 = (void *)sub_49B860(pMem4);
        else
          v6 = nullptr;
        p_Src = Src;
        LOBYTE(v31) = 2;
        fld_e13 = v6;
        if ( v29 < 0x10 )
          p_Src = &Src;
        sub_4015C0(p_Src, strlen((const char *)p_Src));  // 【std::string构造赋值】
        sub_5660C0(&fld_e13);
        fld_e12 = *(this + 12);
        if ( fld_e12 != 0 )
          fld_e13 = (void *)(((*(this + 13) - fld_e12) >> 2) - 1);
        else
          fld_e13 = (void *)-1;
      }
    }
    if ( v25 >= 0x10 )
      j__free(Block);
    v25 = 15;
    v24 = 0;
    LOBYTE(Block) = 0;
    if ( v29 >= 0x10 )
      j__free(Src);
    v28 = 0;
    LOBYTE(Src) = 0;
    v29 = 15;
    if ( v21 >= 0x10 )
      j__free(v19);
    return 1;
  }
  else
  {
    off_77F3FC(aErrorS_0, v2);
    return 0;
  }
}


// ------------------------------------------------------------
// 0x49BD60 sub_49BD60
// ------------------------------------------------------------
int /*thiscall*/ sub_49BD60(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 25) = 0;
  *(this + 26) = -1;
  return 0;
}



// ------------------------------------------------------------
// 0x49BD80 sub_49BD80
// ------------------------------------------------------------
int /*thiscall*/ sub_49BD80(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx

  fld_e2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);
  if ( fld_e2 != nullptr )
    result = (**fld_e2)(fld_e2, 1);
  fld_e4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);
  *(this + 2) = 0;
  if ( fld_e4 != nullptr )
    result = (**fld_e4)(fld_e4, 1);
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x49BDB0 sub_49BDB0
// ------------------------------------------------------------
char /*thiscall*/ sub_49BDB0(uint32_t *this, int nArg2)
{
  int pThis_12; // ecx
  int fld_e2; // eax

  pThis_12 = (int)(this + 18);
  *(this + 25) = nArg2;
  *(uint8_t *)(pThis_12 + 13) = 0;
  *(uint8_t *)(pThis_12 + 14) = 0;
  LOBYTE(fld_e2) = sub_698F90(pThis_12, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( nArg2 != 0 )
  {
    *(uint8_t *)(*(this + 2) + 16) = 1;
  }
  else
  {
    fld_e2 = *(this + 2);
    *(uint8_t *)(fld_e2 + 16) = 0;
  }
  *(this + 26) = -1;
  return fld_e2;
}



// ------------------------------------------------------------
// 0x49BE00 sub_49BE00
// ------------------------------------------------------------
int sub_49BE00()
{
  int result; // eax
  int v1; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  if ( result != 0 )
  {
    v1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
    return sub_41A5E0(v1 + 134);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49BE30 sub_49BE30
// ------------------------------------------------------------
int sub_49BE30()
{
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) != 0 )
  {
    return *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108)
                     + 108);
  }
  else
  {
    return -1;
  }
}



// ============================================================
// §N 0x49BE70-0x49CA80  UI/窗口联动（CLICK_BUTTON2）
// ============================================================
// ------------------------------------------------------------
// 0x49BE70 sub_49BE70
// ------------------------------------------------------------
bool sub_49BE70()
{
  int v0; // esi
  int v2; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) == 0 )
    return false;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) == 0 )
    return false;
  v0 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) + 108);
  if ( v0 == -1 )
    return false;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) == 0 )
    return v0 <= 0;
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);
  return sub_41A5E0(v2 + 134) >= v0;
}



// ------------------------------------------------------------
// 0x49BEF0 sub_49BEF0 —— COUNT_DOWN 事件（+44 图像、+208 状态、sub_48FD80）
// ------------------------------------------------------------
char /*thiscall*/ sub_49BEF0(int this, int nArg2)
{
  int fld_64; // eax
  int v4; // edi
  int fld_C; // eax
  int fld_C2; // eax
  int v7; // eax
  int fld_C3; // eax
  int fld_C4; // eax
  int v10; // eax
  int fld_C5; // eax
  int v12; // eax
  int fld_C6; // eax
  int fld_C7; // eax
  int v15; // ecx
  int fld_C8; // eax
  int fld_C9; // eax
  int v18; // eax
  int fld_C10; // eax
  int v20; // eax
  int fld_C11; // eax
  int pThis_48; // edi
  int fld_C12; // eax
  int v24; // eax
  int v25; // eax
  uint32_t *fld_C13; // ecx
  unsigned int v28; // [esp-8h] [ebp-Ch]

  LOBYTE(fld_64) = nArg2;
  if ( nArg2 != *(uint32_t *)(this + 8) )
    return fld_64;
  fld_64 = *(uint32_t *)(this + 100);
  if ( fld_64 == 1 || fld_64 == 2 )
  {
    fld_64 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));
    if ( fld_64 != 0 )
    {
      v4 = sub_49BE30();
      if ( v4 == -1 )
      {
        fld_C = sub_418DD0(*(uint32_t **)(this + 12), 0);
        if ( fld_C != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_C + 152))(fld_C, 213, 236, dword_79C0B0);
        if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )  // 【clock_now(clk)】
        {
          fld_C2 = sub_418DD0(*(uint32_t **)(this + 12), 1u);
          sub_40FC80((void *)dword_79C0B0, 215, 238, fld_C2);
        }
        v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));
        LOBYTE(fld_64) = sub_69A110(338, 276, v7, -1);
        goto LABEL_24;
      }
      LOBYTE(fld_64) = sub_49BE70();
      if ( (uint8_t)fld_64 == 0 )
      {
        LOBYTE(fld_64) = *(uint8_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520)
                                          + 108)
                              + 464);
        if ( (uint8_t)fld_64 != 0 )
        {
          fld_C3 = sub_418DD0(*(uint32_t **)(this + 12), 0x26u);
          sub_40FC80((void *)dword_79C0B0, 209, 206, fld_C3);
          if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )  // 【clock_now(clk)】
          {
            fld_C4 = sub_418DD0(*(uint32_t **)(this + 12), 0x27u);
            sub_40FC80((void *)dword_79C0B0, 213, 248, fld_C4);
          }
          v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));
          sub_69A110(338, 267, v10, -1);
          fld_C5 = sub_418DD0(*(uint32_t **)(this + 12), 0x18u);
          sub_40FC80((void *)dword_79C0B0, 365 - (*(uint32_t *)(fld_C5 + 20) >> 1), 310 - (*(uint32_t *)(fld_C5 + 24) >> 1), fld_C5);
          v12 = sub_49BE00();
          fld_C6 = sub_418DD0(*(uint32_t **)(this + 12), v4 - v12 + 25);
          sub_40FC80((void *)dword_79C0B0, 352 - (*(uint32_t *)(fld_C6 + 20) >> 1), 310 - (*(uint32_t *)(fld_C6 + 24) >> 1), fld_C6);
          fld_C7 = sub_418DD0(*(uint32_t **)(this + 12), v4 + 25);
          v15 = 310;
        }
        else
        {
          if ( *(uint32_t *)(dword_8F7A24 + 12) != 6 )
            goto LABEL_24;
          fld_C8 = sub_418DD0(*(uint32_t **)(this + 12), 0x28u);
          sub_40FC80((void *)dword_79C0B0, 211, 237, fld_C8);
          if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )  // 【clock_now(clk)】
          {
            fld_C9 = sub_418DD0(*(uint32_t **)(this + 12), 0x29u);
            sub_40FC80((void *)dword_79C0B0, 213, 239, fld_C9);
          }
          v18 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));
          sub_69A110(338, 267, v18, -1);
          fld_C10 = sub_418DD0(*(uint32_t **)(this + 12), 0x18u);
          sub_40FC80((void *)dword_79C0B0, 363 - (*(uint32_t *)(fld_C10 + 20) >> 1), 311 - (*(uint32_t *)(fld_C10 + 24) >> 1), fld_C10);
          v20 = sub_49BE00();
          fld_C11 = sub_418DD0(*(uint32_t **)(this + 12), v4 - v20 + 25);
          sub_40FC80((void *)dword_79C0B0, 347 - (*(uint32_t *)(fld_C11 + 20) >> 1), 311 - (*(uint32_t *)(fld_C11 + 24) >> 1), fld_C11);
          fld_C7 = sub_418DD0(*(uint32_t **)(this + 12), v4 + 25);
          v15 = 311;
        }
        LOBYTE(fld_64) = sub_40FC80(
                       (void *)dword_79C0B0,
                       378 - (*(uint32_t *)(fld_C7 + 20) >> 1),
                       v15 - (*(uint32_t *)(fld_C7 + 24) >> 1),
                       fld_C7);
      }
    }
  }
LABEL_24:
  if ( *(uint32_t *)(this + 100) == 2 )
  {
    if ( (9999 - sub_699000(this + 72)) / 1000 <= 0 )  // 【clock_now(clk)】
      pThis_48 = 0;
    else
      pThis_48 = (9999 - sub_699000(this + 72)) / 1000;  // 【clock_now(clk)】
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 && dword_99FF08 != 0 && sub_48FD80((uint8_t *)dword_99FF08) == 0 )
    {
      fld_C12 = sub_418DD0(*(uint32_t **)(this + 12), pThis_48 + 2);
      sub_40FC80((void *)dword_79C0B0, 271, 105, fld_C12);
      v24 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 208), 0x4Cu);
      LOBYTE(fld_64) = sub_40FC80((void *)dword_79C0B0, 115, 194, v24);
    }
    else
    {
      v25 = sub_49BE30();
      fld_C13 = *(uint32_t **)(this + 12);
      v28 = pThis_48 + 2;
      if ( v25 == -1 )
      {
        fld_64 = sub_418DD0(fld_C13, v28);
        if ( fld_64 != 0 )
          LOBYTE(fld_64) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_64 + 152))(fld_64, 282, 121, dword_79C0B0);
      }
      else
      {
        fld_64 = sub_418DD0(fld_C13, v28);
        if ( fld_64 != 0 )
          LOBYTE(fld_64) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_64 + 152))(fld_64, 282, 116, dword_79C0B0);
      }
    }
    if ( *(uint32_t *)(this + 104) != pThis_48 )
    {
      LOBYTE(fld_64) = (uint8_t)sub_432EA0("COUNT_DOWN", -1, 0, 0);
      *(uint32_t *)(this + 104) = pThis_48;
    }
  }
  return fld_64;
}


// ------------------------------------------------------------
// 0x49C380 sub_49C380 —— 帧字段组读取（+40/+44/+48/+52/+56）
// ------------------------------------------------------------
int /*thiscall*/ sub_49C380(int this, void *Block)
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  int fld_C; // eax
  int result; // eax

  *(uint32_t *)(this + 4) = Block;
  *(uint32_t *)(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 68);
  pMem = operator new(0x68u);
  if ( pMem != nullptr )
    v4 = sub_426BD0(pMem);
  else
    v4 = nullptr;
  *(uint32_t *)(this + 8) = v4;
  *((uint32_t *)v4 + 17) = this;
  if ( operator new(0x2Cu) != nullptr )
    fld_C = sub_423B30(dword_79C0B0, *(uint32_t *)(this + 12), 13, 4);
  else
    fld_C = 0;
  *(uint32_t *)(this + 16) = fld_C;
  *(uint8_t *)(this + 20) = 0;
  *(uint8_t *)(this + 21) = 0;
  *(uint8_t *)(this + 22) = 0;
  *(uint8_t *)(this + 23) = 0;
  *(uint32_t *)(this + 32) = 0;
  *(uint32_t *)(this + 36) = 6;
  *(uint32_t *)(this + 40) = 12;
  *(uint32_t *)(this + 44) = 0;
  *(uint32_t *)(this + 48) = 1600;
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint32_t *)(this + 64) = 0;
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 68) = dword_99FCCC;
  *(uint32_t *)(this + 24) = -16777216;
  *(uint32_t *)(this + 100) = 0;
  *(uint8_t *)(this + 85) = 0;
  *(uint8_t *)(this + 86) = 0;
  sub_698F90(this + 72, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  result = *(uint32_t *)(this + 8);
  *(uint8_t *)(result + 16) = 0;
  *(uint32_t *)(this + 104) = -1;
  return result;
}



// ------------------------------------------------------------
// 0x49C4A0 sub_49C4A0
// ------------------------------------------------------------
int /*thiscall*/ sub_49C4A0(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7)
{
  int pThis_14; // eax

  sub_58B2A0(nArg2);
  pThis_14 = sub_699000((int)this + 20);  // 【clock_now(clk)】
  sub_58B2A0(pThis_14);
  sub_58B2A0(nArg3);
  sub_58B2A0(4);
  sub_58B2A0(nArg4);
  sub_58B2A0(nArg5);
  sub_58B2A0(nArg6);
  return sub_58B2A0(nArg7);
}



// ------------------------------------------------------------
// 0x49C510 sub_49C510
// ------------------------------------------------------------
int /*cdecl*/ sub_49C510(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5)
{
  if ( (dword_9A0264 & 1) == 0 )
  {
    dword_9A0264 |= 1u;
    dword_9A0250 = 0;
    dword_9A0254 = 0;
    dword_9A0258 = 0;
    dword_9A025C = 0;
    dword_9A0260 = 0;
    atexit(nullsub_4);
  }
  dword_9A0254 = nArg2;
  dword_9A0250 = nArg1;
  dword_9A0260 = nArg5;
  dword_9A0258 = nArg3;
  dword_9A025C = nArg4;
  return sub_4AEA30(&dword_9A0250);
}



// ------------------------------------------------------------
// 0x49C5A0 sub_49C5A0
// ------------------------------------------------------------
int sub_49C5A0()
{
  int v0; // edx
  int v1; // esi
  int v2; // edi
  int v4; // [esp-4h] [ebp-Ch]

  v0 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v1 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v2 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v4 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  return sub_49C510(v1, 0, v0, v2, v4);
}



// ------------------------------------------------------------
// 0x49C5F0 sub_49C5F0
// ------------------------------------------------------------
int /*thiscall*/ sub_49C5F0(int *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  return sub_49C4A0(&dword_9A02C0, (int)sub_49C5A0, nArg5, *(this + 1), nArg2, nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x49C620 sub_49C620
// ------------------------------------------------------------
int /*thiscall*/ sub_49C620(int *this, int nArg2, int nArg3, int nArg4)
{
  return sub_49C510(nArg2, *(this + 1), *(this + 1), nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x49C640 sub_49C640
// ------------------------------------------------------------
void /*noreturn*/ sub_49C640()
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
  sub_4015C0(&v1, "deque<T> too long", 0x11u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x49C6B0 sub_49C6B0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49C6B0(int this, unsigned int uArg2)
{
  unsigned int uArg22; // edx
  unsigned int fld_8; // eax
  unsigned int v5; // ecx
  unsigned int fld_C; // edi
  int v7; // esi
  char *fld_4; // eax
  const void *fld_42; // ecx
  char *v10; // eax
  char *pBuf3; // edx
  unsigned int pBuf; // ecx
  char *pBuf2; // edi
  size_t v14; // esi
  char *fld_43; // eax
  unsigned int result; // eax
  size_t fld_82; // [esp+8h] [ebp-Ch]
  char *pMem; // [esp+10h] [ebp-4h]

  uArg22 = uArg2;
  fld_8 = *(uint32_t *)(this + 8);
  if ( 0xFFFFFFF - fld_8 < uArg2 )
    sub_49C640(this);
  v5 = fld_8 >> 1;
  if ( fld_8 >> 1 < 8 )
    v5 = 8;
  if ( uArg2 < v5 && fld_8 <= 0xFFFFFFF - v5 )
  {
    uArg2 = v5;
    uArg22 = v5;
  }
  fld_C = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * fld_C;
  pMem = (char *)operator new(4 * (uArg22 + fld_8));
  fld_82 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * fld_C) >> 2);
  fld_4 = (char *)memcpy_0(&pMem[4 * fld_C], (const void *)(4 * fld_C + *(uint32_t *)(this + 4)), fld_82);
  fld_42 = *(const void **)(this + 4);
  v10 = &fld_4[fld_82];
  if ( fld_C > uArg2 )
  {
    memcpy_0(v10, fld_42, 4 * ((int)(4 * uArg2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * uArg2) >> 2);
    fld_43 = (char *)memcpy_0(pMem, (const void *)(4 * uArg2 + *(uint32_t *)(this + 4)), v14);
    pBuf = uArg2;
    pBuf2 = &fld_43[v14];
    if ( uArg2 == 0 )
      goto LABEL_15;
    goto LABEL_14;
  }
  pBuf3 = (char *)memcpy_0(v10, fld_42, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( uArg2 != fld_C )
    memset(pBuf3, 0, 4 * (uArg2 - fld_C));
  if ( fld_C != 0 )
  {
    pBuf = fld_C;
    pBuf2 = pMem;
LABEL_14:
    memset(pBuf2, 0, 4 * pBuf);
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  result = uArg2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = pMem;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x49C800 sub_49C800
// ------------------------------------------------------------
int /*thiscall*/ sub_49C800(int this, uint32_t *uArg2)
{
  int fld_10; // eax
  unsigned int fld_8; // eax
  unsigned int fld_102; // edi
  unsigned int v6; // ebx
  uint32_t *fld_4; // edi
  int result; // eax

  fld_10 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)fld_10 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(fld_10 + 4) >> 2 )
    sub_49C6B0(this, 1u);
  fld_8 = *(uint32_t *)(this + 8);
  fld_102 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = fld_102 >> 2;
  if ( fld_8 <= fld_102 >> 2 )
    v6 -= fld_8;
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);
  fld_4 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (fld_102 & 3));
  if ( fld_4 != nullptr )
    *fld_4 = *uArg2;
  result = *(uint32_t *)(this + 16) + 1;
  *(uint32_t *)(this + 16) = result;
  return result;
}



// ------------------------------------------------------------
// 0x49C880 sub_49C880
// ------------------------------------------------------------
void */*thiscall*/ sub_49C880(size_t *this, size_t Size)
{
  void *result; // eax
  int i; // edi
  size_t *pThis_1; // ecx
  unsigned int fld_e4; // edx
  unsigned int v7; // eax
  size_t *pThis_12; // esi
  unsigned int v9; // edx
  unsigned int v10; // edi
  size_t v11; // edx
  size_t v12; // edx

  if ( Size != *this )
    return operator new(Size);
  if ( *(this + 5) == 0 )
  {
    for ( i = 512; i != 0; --i )
    {
      Size = (size_t)operator new(*this);
      sub_49C800((int)(this + 1), &Size);
    }
  }
  pThis_1 = this + 1;
  fld_e4 = *(this + 4) + *(this + 5) - 1;
  v7 = fld_e4 >> 2;
  pThis_12 = this + 1;
  v9 = fld_e4 - 4 * (fld_e4 >> 2);
  v10 = pThis_12[2];
  if ( v10 <= v7 )
    v7 -= v10;
  result = *(void **)(*(uint32_t *)(pThis_12[1] + 4 * v7) + 4 * v9);
  v11 = pThis_1[4];
  if ( v11 != 0 )
  {
    v12 = v11 - 1;
    pThis_1[4] = v12;
    if ( v12 == 0 )
      pThis_1[3] = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49C920 sub_49C920
// ------------------------------------------------------------
int /*cdecl*/ sub_49C920(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5)
{
  uint32_t *v5; // ecx
  uint32_t *nArg12; // eax
  uint32_t *nArg122; // [esp+0h] [ebp-4h] BYREF

  nArg122 = v5;
  nArg12 = sub_49C880(&dword_9B930C, 0x14u);
  if ( nArg12 != nullptr )
  {
    *nArg12 = nArg1;
    nArg12[1] = nArg2;
    nArg12[2] = nArg3;
    nArg12[3] = nArg4;
    nArg12[4] = nArg5;
  }
  else
  {
    nArg12 = nullptr;
  }
  nArg122 = nArg12;
  return sub_49C800((int)&unk_9A02F0, &nArg122);
}



// ------------------------------------------------------------
// 0x49C970 sub_49C970
// ------------------------------------------------------------
int /*thiscall*/ sub_49C970(int *this, int nArg2, int nArg3, int nArg4)
{
  return sub_49C920(nArg2, *(this + 1), *(this + 1), nArg3, nArg4);
}



// ------------------------------------------------------------
// 0x49C990 sub_49C990
// ------------------------------------------------------------
int /*thiscall*/ sub_49C990(uint32_t *this)
{
  uint32_t *pThis_3A; // ecx

  *(this + 1) = 0;
  *(this + 6) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  pThis_3A = this + 58;
  *pThis_3A = -1;
  pThis_3A[1] = -1;
  pThis_3A[2] = -1;
  pThis_3A[3] = -1;
  pThis_3A[4] = -1;
  pThis_3A[5] = -1;
  pThis_3A[6] = -1;
  pThis_3A[7] = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x49C9E0 sub_49C9E0
// ------------------------------------------------------------
int /*thiscall*/ sub_49C9E0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e6)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e9)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e10)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e11)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  int (/*thiscall*/ ***fld_e14)(uint32_t, int); // ecx
  uint32_t *pThis_F; // edi
  int i; // ebx
  int (/*thiscall*/ ***fld_e18)(uint32_t, int); // ecx

  fld_e6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 6);
  if ( fld_e6 != nullptr )
    result = (**fld_e6)(fld_e6, 1);
  fld_e9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);
  *(this + 6) = 0;
  if ( fld_e9 != nullptr )
    result = (**fld_e9)(fld_e9, 1);
  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);
  *(this + 9) = 0;
  if ( fld_e10 != nullptr )
    result = (**fld_e10)(fld_e10, 1);
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);
  *(this + 10) = 0;
  if ( fld_e11 != nullptr )
    result = (**fld_e11)(fld_e11, 1);
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 11) = 0;
  if ( fld_e13 != nullptr )
    result = (**fld_e13)(fld_e13, 1);
  fld_e14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);
  *(this + 13) = 0;
  if ( fld_e14 != nullptr )
    result = (**fld_e14)(fld_e14, 1);
  *(this + 14) = 0;
  pThis_F = this + 15;
  for ( i = 3; i != 0; --i )
  {
    if ( *pThis_F != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_F)(*pThis_F, 1);
    *pThis_F++ = 0;
  }
  fld_e18 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 18);
  if ( fld_e18 != nullptr )
    result = (**fld_e18)(fld_e18, 1);
  *(this + 18) = 0;
  return result;
}



// ============================================================
// §O 0x49CA80-0x49E930  结算演出族（M_RESULT / RESULT_FLASH）
// ============================================================
// ------------------------------------------------------------
// 0x49CA80 sub_49CA80 —— 窗口状态查询（+58/+59 → sub_48FCA0/sub_578E80）
// ------------------------------------------------------------
int /*thiscall*/ sub_49CA80(int *this)
{
  int dword_99FF082; // ecx
  int v3; // esi
  int v4; // ebx
  uint32_t *v5; // ecx
  int v6; // eax
  int pObj; // eax
  int v8; // ebx
  bool v9; // zf
  int result; // eax
  uint32_t *v11; // [esp+10h] [ebp-Ch]
  int v12; // [esp+14h] [ebp-8h]
  int *pThis_3A; // [esp+18h] [ebp-4h]

  dword_99FF082 = dword_99FF08;
  *(this + 58) = -1;
  *(this + 59) = -1;
  *(this + 60) = -1;
  *(this + 61) = -1;
  *(this + 62) = -1;
  *(this + 63) = -1;
  *(this + 64) = -1;
  *(this + 65) = -1;
  v3 = 0;
  v4 = 1;
  v5 = (uint32_t *)(dword_99FF082 + 8);
  v12 = 1;
  pThis_3A = this + 58;
  v11 = v5;
  do
  {
    if ( *v5 != 255 )
    {
      if ( v3 == sub_48FCA0() )
      {
        *pThis_3A = 0;
      }
      else
      {
        v6 = sub_578E80(v3);
        if ( v6 != 0 )
        {
          pObj = *(uint32_t *)(v6 + 196);
          if ( pObj != 0 )
          {
            v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) == v8;
            v4 = v12;
            if ( v9 )
            {
              *pThis_3A = v12;
              v4 = ++v12;
            }
          }
        }
      }
    }
    ++v3;
    v5 = ++v11;
    ++pThis_3A;
  }
  while ( v3 < 8 );
  result = -1;
  if ( *(this + 58) == -1 )
    *(this + 58) = v4++;
  if ( *(this + 59) == -1 )
    *(this + 59) = v4++;
  if ( *(this + 60) == -1 )
    *(this + 60) = v4++;
  if ( *(this + 61) == -1 )
    *(this + 61) = v4++;
  if ( *(this + 62) == -1 )
    *(this + 62) = v4++;
  if ( *(this + 63) == -1 )
    *(this + 63) = v4++;
  if ( *(this + 64) == -1 )
    *(this + 64) = v4++;
  if ( *(this + 65) == -1 )
    *(this + 65) = v4;
  return result;
}



// ------------------------------------------------------------
// 0x49CBD0 sub_49CBD0 —— CLICK_BUTTON2 事件分发（音效 sub_432EA0、sub_48FCA0/48FC30）
// ------------------------------------------------------------
int /*thiscall*/ sub_49CBD0(int *this)
{
  int result; // eax
  uint32_t *fld_e1; // edi
  int v4; // ecx
  int fld_e11; // eax
  int fld_e3; // edx
  uint32_t *v7; // edi
  int v8; // eax
  int fld_e10; // eax
  int v10; // eax
  int fld_e14; // eax
  int v12; // edi
  int v13; // eax
  uint32_t v14[3]; // [esp+4h] [ebp-Ch]

  result = *(this + 6);
  if ( *(uint8_t *)(result + 16) != 0 )
  {
    result = dword_99FF08;
    if ( dword_99FF08 != 0 )
    {
      fld_e1 = (uint32_t *)*(this + 1);
      v4 = fld_e1[202];
      if ( v4 == 0 || (result = (fld_e1[203] - v4) >> 2) == 0 )
      {
        fld_e11 = *(this + 11);
        if ( *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e11 + 12) )
        {
          fld_e3 = *(this + 3);
          if ( fld_e3 != 0 && (*(this + 4) - fld_e3) >> 2 != 0 )
          {
            sub_44E8D0((char *)dword_8F8528, (void *)0x2A, (int)(this + 2), 0);
          }
          else
          {
            v7 = (uint32_t *)fld_e1[7];
            v8 = sub_422E70(448);
            sub_43BEE0(v7, v8, -6567706, 0, -1);
          }
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
        fld_e10 = *(this + 10);
        if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )
        {
          v10 = sub_48FCA0();
          if ( v10 != -1 )
            sub_48FC30(v10, 255);
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
        fld_e14 = *(this + 14);
        if ( *(uint8_t *)(fld_e14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e14 + 12) )
        {
          *(uint8_t *)(*(this + 13) + 16) = *(uint8_t *)(*(this + 13) + 16) == 0;
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
        }
        v12 = 0;
        v14[0] = 1;
        v14[1] = 2;
        v14[2] = 0;
        while ( 1 )
        {
          result = *(this + v14[v12] + 15);
          if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )
            break;
          if ( ++v12 >= 3 )
            return result;
        }
        *(uint8_t *)(*(this + 13) + 16) = 0;
        v13 = sub_48FCA0();
        if ( v13 != -1 )
          sub_48FC30(v13, v14[v12]);
        return (int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49CD70 sub_49CD70
// ------------------------------------------------------------
int /*thiscall*/ sub_49CD70(uint32_t *this, char pszArg2)
{
  int result; // eax
  int v4; // edi

  result = *(this + 6);
  if ( *(uint8_t *)(result + 16) != pszArg2 )
  {
    *(uint8_t *)(result + 16) = pszArg2;
    if ( pszArg2 != 0 )
    {
      if ( sub_48FCA0() != -1 )
      {
        *(uint8_t *)(*(this + 14) + 16) = 1;
        *(uint8_t *)(*(this + 13) + 16) = 0;
      }
      v4 = 22 * sub_48FCA0();
      sub_69A5F0((uint32_t *)*(this + 14), 603, v4 + 150);
      sub_69A5F0((uint32_t *)*(this + 13), 577, v4 + 164);
      *(uint8_t *)(*(this + 13) + 16) = 0;
      *(uint8_t *)(*(this + 14) + 16) = 0;
      *(uint8_t *)(*(this + 9) + 16) = 1;
      result = *(this + 11);
      *(uint8_t *)(result + 16) = 1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49CE00 sub_49CE00
// ------------------------------------------------------------
int /*thiscall*/ sub_49CE00(uint32_t **this)
{
  int v2; // esi
  int fld_e8; // eax
  uint32_t *v4; // edi
  int v5; // ebx
  int v6; // esi
  int pObj5; // eax
  int pObj4; // eax
  int pObj; // eax
  int pObj3; // eax
  int pObj2; // eax
  int result; // eax
  int v13; // [esp+Ch] [ebp-4h]

  v2 = 30000 - sub_699000(*(uint32_t *)(dword_8F7A24 + 40) + 36);  // 【clock_now(clk)】
  fld_e8 = sub_418DD0(*(this + 8), 0x35u);
  if ( fld_e8 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e8 + 152))(fld_e8, 424, 111, dword_79C0B0);
  v4 = *(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 208);
  v13 = v2 % 1000;
  v5 = v2 / 1000 % 60;
  v6 = v2 / 60000;
  if ( v6 > 0 )
  {
    if ( v6 > 10 )
    {
      pObj5 = sub_418DD0(v4, v6 / 10 + 43);
      if ( pObj5 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, 456, 118, dword_79C0B0);
    }
    pObj4 = sub_418DD0(v4, v6 % 10 + 43);
    if ( pObj4 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 470, 118, dword_79C0B0);
LABEL_11:
    pObj = sub_418DD0(v4, v5 / 10 + 43);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 504, 118, dword_79C0B0);
    goto LABEL_13;
  }
  if ( v5 > 0 )
  {
    if ( v5 >= 10 )
      goto LABEL_11;
LABEL_13:
    pObj3 = sub_418DD0(v4, v5 % 10 + 43);
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, 518, 118, dword_79C0B0);
  }
  pObj2 = sub_418DD0(v4, v13 / 100 + 43);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 544, 118, dword_79C0B0);
  result = sub_418DD0(v4, v13 / 10 % 10 + 43);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, 558, 118, dword_79C0B0);
  return result;
}



// ------------------------------------------------------------
// 0x49CFF0 sub_49CFF0 —— 窗口对象装配（+52 → sub_69C780/69C7B0；+40..228 字段组初始化）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49CFF0(int this, void *Block)
{
  uint8_t *pMem; // eax
  uint8_t *fld_20; // eax
  uint8_t *pMem2; // eax
  uint8_t *v6; // eax
  uint8_t *pMem3; // eax
  uint8_t *fld_1C; // eax
  uint8_t *pMem4; // edi
  uint32_t *pMem42; // ecx
  bool v11; // cc
  uint8_t *pMem5; // eax
  uint32_t *pMem52; // edi
  uint8_t *pMem6; // eax
  uint32_t *pMem62; // edi
  uint8_t *pMem7; // eax
  uint32_t *pMem72; // edi
  uint32_t *pMem722; // ecx
  uint8_t *pMem8; // eax
  uint8_t *v20; // eax
  uint32_t *fld_18; // ecx
  uint32_t *result; // eax
  int fld_182; // esi
  int fld_1C2; // [esp+Ch] [ebp-24h]
  int v25; // [esp+10h] [ebp-20h]
  int v26; // [esp+14h] [ebp-1Ch]
  int v27; // [esp+18h] [ebp-18h]
  uint32_t *pThis_3C; // [esp+1Ch] [ebp-14h]
  int v29; // [esp+20h] [ebp-10h]
  int *Blocka; // [esp+38h] [ebp+8h]
  void *Blockb; // [esp+38h] [ebp+8h]
  void *Blockc; // [esp+38h] [ebp+8h]
  void *Blockd; // [esp+38h] [ebp+8h]

  *(uint32_t *)(this + 4) = Block;
  *(uint32_t *)(this + 28) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 100);
  *(uint32_t *)(this + 32) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196);
  pMem = operator new(0x6Cu);
  if ( pMem != nullptr )
    fld_20 = sub_43C250(pMem, *(uint32_t *)(this + 32), 45);
  else
    fld_20 = nullptr;
  *(uint32_t *)(this + 24) = fld_20;
  *((uint32_t *)fld_20 + 17) = this;
  pMem2 = operator new(0x68u);
  if ( pMem2 != nullptr )
    v6 = sub_426BD0(pMem2);
  else
    v6 = nullptr;
  *(uint32_t *)(this + 36) = v6;
  sub_69A840(v6);
  pMem3 = operator new(0x6Cu);
  if ( pMem3 != nullptr )
    fld_1C = sub_43C250(pMem3, *(uint32_t *)(this + 28), 75);
  else
    fld_1C = nullptr;
  *(uint32_t *)(this + 52) = fld_1C;
  sub_69A840(fld_1C);
  v29 = 2;
  Blocka = (int *)&unk_6CBA30;
  pThis_3C = (uint32_t *)(this + 60);
  do
  {
    pMem4 = operator new(0x84u);
    if ( pMem4 != nullptr )
    {
      v27 = *Blocka;
      fld_1C2 = *(uint32_t *)(this + 28);
      v26 = Blocka[2];
      v25 = Blocka[1];
      sub_426BD0(pMem4);
      *(uint32_t *)pMem4 = &nengine::CNButton::`vftable';
      sub_69C780(v9);
      sub_69C7B0(v24, v27, v25, v26, v27, 0, 0);
      v10 = v9;
    }
    else
    {
      v10 = nullptr;
    }
    *v28 = v10;
    sub_69A5F0(v10, 2, v29);
    sub_69A840(*v28);
    v11 = (int)(Blocka + 3) < (int)&unk_6CBA54;
    ++v28;
    Blocka += 3;
    v29 += 13;
  }
  while ( v11 );
  v12 = operator new(0x84u);
  v13 = v12;
  if ( v12 != nullptr )
  {
    Blockb = *(void **)(this + 28);
    sub_426BD0(v12);
    *v13 = &nengine::CNButton::`vftable';
    sub_69C780(pMem52);
    sub_69C7B0(Blockb, 4, 5, 6, 4, 0, 0);
  }
  else
  {
    pMem52 = nullptr;
  }
  *(uint32_t *)(this + 56) = pMem52;
  sub_69A840(pMem52);
  pMem6 = operator new(0x84u);
  pMem62 = pMem6;
  if ( pMem6 != nullptr )
  {
    Blockc = *(void **)(this + 32);
    sub_426BD0(pMem6);
    *pMem62 = &nengine::CNButton::`vftable';
    sub_69C780(v15);
    sub_69C7B0(Blockc, 46, 47, 48, 46, 0, 0);
  }
  else
  {
    v15 = nullptr;
  }
  *(uint32_t *)(this + 40) = v15;
  v15[17] = this;
  sub_69A5F0(*(uint32_t **)(this + 40), 86, 388);
  sub_69A840(*(uint32_t *)(this + 40));
  v16 = operator new(0x84u);
  v17 = v16;
  if ( v16 != nullptr )
  {
    Blockd = *(void **)(this + 28);
    sub_426BD0(v16);
    *v17 = &nengine::CNButton::`vftable';
    sub_69C780(pMem72);
    sub_69C7B0(Blockd, 46, 47, 48, 46, 0, 0);
    pMem722 = pMem72;
  }
  else
  {
    pMem722 = nullptr;
  }
  *(uint32_t *)(this + 44) = pMem722;
  sub_69A5F0(pMem722, 110, 332);
  sub_69A840(*(uint32_t *)(this + 44));
  pMem8 = operator new(0x68u);
  if ( pMem8 != nullptr )
    v20 = sub_426BD0(pMem8);
  else
    v20 = nullptr;
  *(uint32_t *)(this + 72) = v20;
  *((uint32_t *)v20 + 17) = this;
  sub_69A840(*(uint32_t *)(this + 72));
  *(uint8_t *)(this + 76) = 0;
  *(uint8_t *)(this + 77) = 0;
  *(uint8_t *)(this + 78) = 0;
  *(uint8_t *)(this + 79) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 92) = 6;
  *(uint32_t *)(this + 96) = 12;
  *(uint32_t *)(this + 104) = 1600;
  *(uint32_t *)(this + 124) = dword_99FCCC;
  *(uint32_t *)(this + 80) = -16777216;
  *(uint8_t *)(this + 128) = 0;
  *(uint8_t *)(this + 129) = 0;
  *(uint8_t *)(this + 130) = 0;
  *(uint8_t *)(this + 131) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 6;
  *(uint32_t *)(this + 148) = 12;
  *(uint32_t *)(this + 152) = 0;
  *(uint32_t *)(this + 156) = 1600;
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  *(uint32_t *)(this + 172) = 0;
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 176) = dword_99FCCC;
  *(uint32_t *)(this + 156) = 72;
  *(uint32_t *)(this + 140) = 1;
  *(uint8_t *)(this + 180) = 0;
  *(uint8_t *)(this + 181) = 0;
  *(uint8_t *)(this + 182) = 0;
  *(uint8_t *)(this + 183) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint32_t *)(this + 196) = 6;
  *(uint32_t *)(this + 200) = 12;
  *(uint32_t *)(this + 204) = 0;
  *(uint32_t *)(this + 208) = 1600;
  *(uint32_t *)(this + 212) = 0;
  *(uint32_t *)(this + 216) = 0;
  *(uint32_t *)(this + 220) = 0;
  *(uint32_t *)(this + 224) = 0;
  *(uint32_t *)(this + 228) = 0;
  fld_18 = *(uint32_t **)(this + 24);
  *(uint32_t *)(this + 228) = dword_99FCCC;
  *(uint32_t *)(this + 208) = 156;
  *(uint32_t *)(this + 192) = 1;
  *(uint8_t *)(this + 182) = 1;
  *(uint32_t *)(this + 184) = -16777216;
  result = sub_69A5F0(fld_18, 365, 0);
  fld_182 = *(uint32_t *)(this + 24);
  if ( *(uint8_t *)(fld_182 + 16) != 0 )
    *(uint8_t *)(fld_182 + 16) = 0;
  return result;
}


// ------------------------------------------------------------
// 0x49D4B0 sub_49D4B0 —— 窗口动画驱动（+45 部件、sub_49CE00 图像、sub_578E80）
// ------------------------------------------------------------
void /*userpurge*/ sub_49D4B0(uint32_t *pArg1@<ecx>, uint32_t *uArg2@<esi>, int nArg3)
{
  int dword_99FF082; // edi
  uint32_t *pArg12; // ebx
  int v5; // edx
  int v6; // esi
  int pObj4; // eax
  int pObj6; // eax
  int pObj2; // eax
  int v10; // eax
  int v11; // edi
  int v12; // edx
  uint32_t *v13; // ecx
  int v14; // esi
  int v15; // eax
  int v16; // edi
  int pObj; // eax
  int v18; // eax
  int pObj7; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // edi
  int v23; // eax
  int pObj5; // eax
  int dword_8F85202; // esi
  int pObj3; // eax
  bool v27; // cc
  int v28; // eax
  int v29; // esi
  int v30; // edi
  int v31; // eax
  int v32; // eax
  char v33; // al
  int v34; // ebx
  int v35; // esi
  int v36; // ebx
  int v37; // eax
  int v38; // eax
  char *v40; // [esp+8h] [ebp-1Ch]
  int v41; // [esp+Ch] [ebp-18h]
  int v42; // [esp+14h] [ebp-10h]
  int v43; // [esp+18h] [ebp-Ch]
  int *v44; // [esp+1Ch] [ebp-8h]
  int v46; // [esp+2Ch] [ebp+8h]
  int v47; // [esp+2Ch] [ebp+8h]

  dword_99FF082 = dword_99FF08;
  pArg12 = pArg1;
  if ( dword_99FF08 != 0 )
  {
    v5 = *(uint32_t *)(pArg1[1] + 4);
    if ( nArg3 == pArg1[6] )
    {
      if ( v5 == 0 )
      {
        v6 = dword_99FF08 + 4;
        pObj4 = sub_418DD0(41);
        if ( pObj4 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 383, 57, dword_79C0B0);
        pObj6 = sub_418DD0(54);
        if ( pObj6 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, 387, 83, dword_79C0B0);
        pObj2 = sub_418DD0(35);
        if ( pObj2 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 394, 84, dword_79C0B0);
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg12 + 45);
        v46 = *(uint32_t *)dword_79C0B0;
        v10 = sub_48FE30(dword_99FF082);
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v46 + 80))(dword_79C0B0, 424, 27, -1, v10);
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
        if ( *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32) == 1 )
          sub_49CE00(pArg12);
        v47 = *(uint32_t *)(pArg12[6] + 20) + 30;
        v11 = 0;
        v12 = 1048644 - v6;
        v13 = (uint32_t *)(v6 + 4);
        v43 = 0;
        v44 = (int *)(v6 + 4);
        v42 = 1048644 - v6;
        v41 = -4 - v6;
        while ( 1 )
        {
          v40 = (char *)v13 + v12;
          v14 = dword_790BC8 + dword_790BCC * *(uint32_t *)((char *)pArg12 + (uint32_t)v13 + v12 - 1048416);
          if ( *v13 != 255 )
          {
            v15 = sub_578E80(v11);
            v16 = v15;
            if ( v15 != 0 )
            {
              pObj = sub_42B340(v15);
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t *))(*(uint32_t *)pObj + 384))(
                pObj,
                v47,
                v14,
                16,
                16,
                1065353216,
                uArg2);
              v18 = *v44;
              if ( *v44 == 1 || v18 == 2 )
              {
                pObj7 = sub_418DD0(v18 + 73);
                if ( pObj7 != 0 )
                  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v47, v14, dword_79C0B0);
              }
              uArg2 = pArg12 + 32;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);
              if ( *(uint32_t *)(v16 + 40) < 0x10u )
                v20 = v16 + 20;
              else
                v20 = *(uint32_t *)(v16 + 20);
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
                dword_79C0B0,
                v47 + 55,
                v14 + 4,
                -9795152,
                v20);
              if ( *(uint32_t *)(v16 + 40) < 0x10u )
                v21 = v16 + 20;
              else
                v21 = *(uint32_t *)(v16 + 20);
              v22 = v14 + 3;
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(
                dword_79C0B0,
                v47 + 55,
                v14 + 3,
                -16179413,
                v21);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);
              v23 = *v44;
              if ( *v44 == 1 || v23 == 2 )
                pObj5 = sub_418DD0(v23 + 99);
              else
                pObj5 = sub_418DD0(112);
              if ( pObj5 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(
                  pObj5,
                  v47 + 180,
                  v14 + 2,
                  dword_79C0B0);
              dword_8F85202 = dword_8F8520;
              if ( *(uint32_t *)((char *)sub_656710() + (uint32_t)v44 + v41) != -1 && *(uint32_t *)&v40[dword_8F85202] != 0 )
              {
                pObj3 = sub_418DD0(44);
                if ( pObj3 != 0 )
                  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v47 + 130, v22, dword_79C0B0);
              }
              pArg12 = pArg1;
            }
          }
          v11 = v43 + 1;
          v13 = v44 + 1;
          v27 = ++v43 < 8;
          ++v44;
          if ( !v27 )
            break;
          v12 = v42;
        }
      }
    }
    else
    {
      v28 = pArg1[10];
      if ( nArg3 != v28 || v5 != 0 )
      {
        if ( nArg3 == pArg1[18] && v5 == 0 )
        {
          if ( (uint8_t)sub_43BCB0(pArg1[11]) != 0 )
          {
            v32 = sub_422E70(449);
            sub_4649B0(510, 321, -1, -16777216, 2, v32, 0, 0, 1600, 0);
          }
          else if ( (uint8_t)sub_43BCB0(pArg12[14]) != 0 )
          {
            v33 = sub_48FD20(dword_99FF082);
            v34 = pArg12[14];
            v35 = *(uint32_t *)(v34 + 24);
            v36 = *(uint32_t *)(v34 + 20);
            if ( v33 != 0 )
              v37 = sub_422E70(452);
            else
              v37 = sub_422E70(453);
            sub_4649B0(v36 - 10, v35, -1, -16777216, 2, v37, 0, 0, 1600, 0);
          }
          else if ( (uint8_t)sub_43BCB0(pArg12[17]) != 0 )
          {
            v38 = sub_422E70(455);
            sub_4649B0(505, 202, -1, -16777216, 2, v38, 0, 0, 1600, 0);
          }
        }
      }
      else if ( *(uint8_t *)(v28 + 17) != 0 && dword_79BE3C == *(uint32_t *)(v28 + 12) )
      {
        v29 = *(uint32_t *)(v28 + 24);
        v30 = *(uint32_t *)(v28 + 20);
        v31 = sub_418DD0(87);
        sub_40FC80(v30 + 24, v29 - 33, v31);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x49D920 sub_49D920
// ------------------------------------------------------------
void /*thiscall*/ sub_49D920(uint32_t *this)
{
  void *fld_e3; // eax
  uint32_t *pThis_2; // esi
  uint32_t *v3; // ecx
  int **v4; // eax
  int *v5; // edi
  int **v6; // edx
  bool v7; // zf
  int v8; // eax
  int v9; // eax
  uint32_t *v10; // esi
  signed int i; // eax
  int v12; // ebx
  int **v13; // eax
  int *k; // eax
  int *j; // eax
  uint32_t *v16; // ebx
  int v17; // ecx
  unsigned int v18; // edx
  uint32_t *v19; // eax
  uint32_t *v20; // eax
  uint32_t *v21; // esi
  int v22; // [esp-14h] [ebp-44h]
  uint8_t v23[4]; // [esp+0h] [ebp-30h] BYREF
  uint32_t *v24; // [esp+4h] [ebp-2Ch]
  int v25; // [esp+8h] [ebp-28h]
  uint32_t v26[2]; // [esp+Ch] [ebp-24h] BYREF
  uint32_t *pThis_22; // [esp+14h] [ebp-1Ch]
  int v28; // [esp+18h] [ebp-18h]
  int v29; // [esp+1Ch] [ebp-14h]
  int v30; // [esp+20h] [ebp-10h]
  int v31; // [esp+2Ch] [ebp-4h]

  if ( *(uint8_t *)(*(this + 6) + 16) != 0 )
  {
    fld_e3 = (void *)*(this + 3);
    pThis_2 = this + 2;
    pThis_22 = this + 2;
    if ( fld_e3 != nullptr )
      j__free(fld_e3);
    pThis_2[1] = 0;
    pThis_2[2] = 0;
    pThis_2[3] = 0;
    v30 = sub_429830((uint16_t)word_77F804);
    v29 = sub_41A5E0(v30 + 53);
    v3 = (uint32_t *)sub_4A2CF0(v23);
    v24 = v3;
    v25 = 0;
    v4 = *(int ***)(dword_8F8500 + 8);
    v5 = *v4;
    v6 = (int **)(dword_8F8500 + 8);
    v7 = *v4 == (int *)v4;
    v31 = 0;
    v28 = dword_8F8500 + 8;
    if ( !v7 )
    {
      do
      {
        v8 = v5[4];
        if ( *(uint32_t *)(v8 + 68) == 0 && v8 != v30 )
        {
          v9 = sub_41A5E0(v8 + 53);
          v10 = (uint32_t *)*v24;
          for ( i = abs32(v29 - v9); v10 != v24; v10 = (uint32_t *)*v10 )
          {
            if ( v10[2] >= i )
              break;
          }
          v26[0] = i;
          v22 = v10[1];
          v26[1] = *(uint16_t *)(v5[4] + 4);
          v12 = sub_52DAA0(v10, v22, v26);
          sub_468240(1);
          v6 = (int **)v28;
          v10[1] = v12;
          pThis_2 = pThis_22;
          **(uint32_t **)(v12 + 4) = v12;
          v3 = v24;
        }
        if ( *((uint8_t *)v5 + 21) == 0 )
        {
          v13 = (int **)v5[2];
          if ( *((uint8_t *)v13 + 21) != 0 )
          {
            for ( j = (int *)v5[1]; *((uint8_t *)j + 21) == 0; j = (int *)j[1] )
            {
              if ( v5 != (int *)j[2] )
                break;
              v5 = j;
            }
            v5 = j;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( k = *v13; *((uint8_t *)k + 21) == 0; k = (int *)*k )
              v5 = k;
          }
        }
      }
      while ( v5 != *v6 );
    }
    v16 = (uint32_t *)*v3;
    if ( (uint32_t *)*v3 != v3 )
    {
      do
      {
        v17 = pThis_2[1];
        if ( v17 != 0 )
          v18 = (pThis_2[2] - v17) >> 2;
        else
          v18 = 0;
        if ( v17 != 0 && v18 < (pThis_2[3] - v17) >> 2 )
        {
          v19 = (uint32_t *)pThis_2[2];
          *v19 = v16[3];
          pThis_2[2] = v19 + 1;
        }
        else
        {
          sub_430C80((void *)pThis_2[2], 1, (int)(v16 + 3));
        }
        v16 = (uint32_t *)*v16;
      }
      while ( v16 != v24 );
      v3 = v24;
    }
    v20 = (uint32_t *)*v3;
    v7 = *v3 == (uint32_t)v3;
    *v3 = v3;
    v3[1] = v3;
    if ( !v7 )
    {
      do
      {
        v21 = (uint32_t *)*v20;
        j__free(v20);
        v3 = v24;
        v20 = v21;
      }
      while ( v21 != v24 );
    }
    j__free(v3);
  }
}


// ------------------------------------------------------------
// 0x49DB10 sub_49DB10
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB10(uint32_t *this)
{
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 12) = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 1) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x49DB30 sub_49DB30
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB30(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  uint32_t *pThis_9; // esi
  int i; // edi

  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);
  if ( fld_e12 != nullptr )
    result = (**fld_e12)(fld_e12, 1);
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);
  *(this + 12) = 0;
  if ( fld_e13 != nullptr )
    result = (**fld_e13)(fld_e13, 1);
  *(this + 13) = 0;
  pThis_9 = this + 9;
  for ( i = 3; i != 0; --i )
  {
    if ( *pThis_9 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_9)(*pThis_9, 1);
    *pThis_9++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49DB80 sub_49DB80
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB80(uint32_t **this, int nArg2)
{
  uint8_t nArg22; // bl
  int fld_e14; // eax
  int result; // eax

  nArg22 = nArg2;
  if ( nArg2 >= 220 )
    nArg22 = -36;
  fld_e14 = sub_418DD0(*(this + 14), 0);
  if ( fld_e14 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_e14 + 128))(
      fld_e14,
      0,
      0,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (nArg22 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  result = sub_418DD0(*(this + 14), 3u);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             264,
             12,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             ((uint8_t)nArg2 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x49DC30 sub_49DC30 —— M_RESULT 事件处理（sub_432EE0/sub_65DC70 → sub_49DCF0）
// ------------------------------------------------------------
int /*thiscall*/ sub_49DC30(uint32_t *this)
{
  int64_t pThis_2; // rax
  int v3; // edi
  int pObj; // eax

  pThis_2 = 1717986919LL * (sub_699000((int)(this + 2)) % 640);  // 【clock_now(clk)】
  v3 = (SHIDWORD(pThis_2) >> 5) + (HIDWORD(pThis_2) >> 31);
  if ( v3 < 8 )
  {
    sub_491530(2, 0);
    pObj = sub_418DD0(v3 + 15);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 43, 328, dword_79C0B0);
    LODWORD(pThis_2) = sub_491630(2);
    if ( v3 == 0 )
    {
      LODWORD(pThis_2) = *(this + 37);
      if ( (uint32_t)pThis_2 == 0 )
      {
        *(this + 37) = *(this + 32) + *(this + 33) + *(this + 34) + *(this + 35) + *(this + 36);
        LODWORD(pThis_2) = sub_432EA0("RESULT_FLASH", -1, 0, 0);
      }
    }
  }
  return pThis_2;
}



// ------------------------------------------------------------
// 0x49DCF0 sub_49DCF0
// ------------------------------------------------------------
char /*thiscall*/ sub_49DCF0(int this)
{
  uint32_t *pThis_80; // edi
  char result; // al

  pThis_80 = (uint32_t *)(this + 128);
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  sub_432FA0();
  *(uint32_t *)(this + 144) = 0;
  *pThis_80 = 0;
  pThis_80[1] = 0;
  pThis_80[2] = 0;
  pThis_80[3] = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 152) = 255;
  *(uint8_t *)(this + 73) = 0;
  *(uint8_t *)(this + 74) = 0;
  result = sub_698F90(this + 60, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *pThis_80 = 5000;
  *(uint32_t *)(this + 144) = 30000;
  *(uint32_t *)(this + 132) = 3000;
  *(uint32_t *)(this + 136) = 2000;
  *(uint32_t *)(this + 140) = 1000;
  *(uint32_t *)(this + 124) = 254;
  return result;
}



// ------------------------------------------------------------
// 0x49DD80 sub_49DD80
// ------------------------------------------------------------
int /*thiscall*/ sub_49DD80(int this, int nArg2)
{
  int fld_98; // edi
  uint32_t *fld_38; // ecx
  int v5; // edi
  int pObj; // eax
  int pObj2; // eax
  int fld_982; // edi
  int result; // eax
  unsigned int v10; // [esp-4h] [ebp-Ch]

  fld_98 = *(uint8_t *)(this + 152);
  fld_38 = *(uint32_t **)(this + 56);
  v5 = (fld_98 << 24) | 0xFFFFFF;
  if ( nArg2 >= 80 )
  {
    pObj2 = sub_418DD0(fld_38, 0xEu);
    if ( pObj2 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(
        pObj2,
        304,
        108,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v5,
        1333788672,
        1333788672);
    v10 = 13;
  }
  else
  {
    pObj = sub_418DD0(fld_38, 0xDu);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
        pObj,
        304,
        108,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        v5,
        1333788672,
        1333788672);
    v10 = 14;
  }
  fld_982 = (*(uint8_t *)(this + 152) << 24) | 0xFFFFFF;
  result = sub_418DD0(*(uint32_t **)(this + 56), v10);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             315,
             108,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             fld_982,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x49DE70 sub_49DE70
// ------------------------------------------------------------
int /*thiscall*/ sub_49DE70(void *this, int nArg2)
{
  int v2; // esi
  int i; // edi
  uint8_t nArg22; // bl
  int pObj; // eax
  int pObj3; // eax
  uint8_t nArg23; // bl
  int pObj2; // eax
  int result; // eax
  uint32_t v10[5]; // [esp+Ch] [ebp-14h]

  v2 = 0;
  v10[4] = this;
  v10[0] = 6;
  v10[1] = 7;
  v10[2] = 8;
  v10[3] = 9;
  for ( i = 0; i < 4; ++i )
  {
    sub_491530(2, 0);
    nArg22 = nArg2;
    if ( nArg2 >= 150 )
      nArg22 = -106;
    pObj = sub_418DD0(4);
    if ( pObj != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
        pObj,
        166,
        v2 + 160,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        (nArg22 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);
    pObj3 = sub_418DD0(v10[i]);
    if ( pObj3 != 0 )
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(
        pObj3,
        180,
        v2 + 166,
        dword_79C0B0,
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v2 += 46;
  }
  sub_491530(2, 0);
  nArg23 = nArg2;
  if ( nArg2 >= 150 )
    nArg23 = -106;
  pObj2 = sub_418DD0(5);
  if ( pObj2 != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(
      pObj2,
      113,
      349,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      (nArg23 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  sub_491630(2);
  result = sub_418DD0(10);
  if ( result != 0 )
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(
             result,
             180,
             v2 + 170,
             dword_79C0B0,
             1065353216,
             1065353216,
             0,
             ((uint8_t)nArg2 << 24) | 0xFFFFFF,
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x49E050 sub_49E050 —— M_RESULT 演出（结算上下文 sub_65DC70、音效 sub_432EA0）
// ------------------------------------------------------------
int /*thiscall*/ sub_49E050(uint32_t *this, int nArg2)
{
  int pThis_2; // ecx
  int result; // eax
  int i; // esi

  pThis_2 = (int)(this + 2);
  *(this + 1) = nArg2;
  *(uint8_t *)(pThis_2 + 13) = 0;
  *(uint8_t *)(pThis_2 + 14) = 0;
  sub_698F90(pThis_2, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( *(this + 1) != 0 )
  {
    if ( nArg2 == 1 )
    {
      *(uint8_t *)(*(this + 12) + 16) = 0;
      for ( i = 0; i < 4; ++i )
        result = sub_432EE0(i);
    }
    else
    {
      if ( *(uint8_t *)(*(this + 12) + 16) == 0 )
      {
        sub_65DC70(lpCriticalSection);
        sub_432EA0("M_RESULT", -1, 0, 0);
      }
      result = *(this + 12);
      *(uint8_t *)(result + 16) = 1;
    }
  }
  else
  {
    sub_49DCF0((int)this);
    result = *(this + 12);
    *(uint8_t *)(result + 16) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49E0E0 sub_49E0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_49E0E0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 && --result == 0 )
  {
    result = sub_699000((int)(this + 2));  // 【clock_now(clk)】
    if ( result >= 4000 )
      return sub_49E050(this, *(this + 1) + 1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49E110 sub_49E110
// ------------------------------------------------------------
int /*thiscall*/ sub_49E110(int *this, int Value, int nArg3)
{
  int pThis_98; // esi
  int pObj; // eax

  sub_69A110(284, 102, Value, *(this + 38));
  pThis_98 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;
  pObj = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 64), 0xACu);
  if ( pObj != 0 )
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
      pObj,
      339,
      103,
      dword_79C0B0,
      1065353216,
      1065353216,
      0,
      pThis_98,
      1333788672,
      1333788672);
  return sub_69A110(359, 99, nArg3, *(this + 38));
}



// ------------------------------------------------------------
// 0x49E1B0 sub_49E1B0
// ------------------------------------------------------------
int /*thiscall*/ sub_49E1B0(int *this, int nArg2)
{
  int result; // eax
  int v4; // ebx
  bool v5; // zf
  bool v6; // cc
  int pThis_98; // esi
  int pObj; // eax
  int pThis_982; // esi
  int pObj2; // eax
  int v11; // [esp+4h] [ebp-8h]
  int *pThis_20; // [esp+8h] [ebp-4h]

  result = nArg2;
  v11 = 0;
  if ( nArg2 >= 0 )
  {
    v4 = 161;
    pThis_20 = this + 32;
    v5 = nArg2 == 0;
    v6 = nArg2 > 0;
    do
    {
      if ( v6 )
      {
        pThis_98 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;
        pObj = sub_418DD0(172);
        if ( pObj != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(
            pObj,
            279,
            v4 + 3,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            pThis_98,
            1333788672,
            1333788672);
        sub_69A110(301, v4, *pThis_20, *(this + 38));
      }
      else
      {
        if ( !v5 || result == 4 )
          goto LABEL_16;
        if ( sub_699000((int)(this + 22)) < 100 )  // 【clock_now(clk)】
          sub_491530(5, -1);
        pThis_982 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;
        pObj2 = sub_418DD0(172);
        if ( pObj2 != 0 )
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(
            pObj2,
            279,
            v4 + 3,
            dword_79C0B0,
            1065353216,
            1065353216,
            0,
            pThis_982,
            1333788672,
            1333788672);
        sub_69A110(301, v4, *pThis_20, *(this + 38));
        if ( sub_699000((int)(this + 22)) < 100 )  // 【clock_now(clk)】
          sub_491630(5);
      }
      result = nArg2;
LABEL_16:
      v4 += 46;
      v5 = v11 + 1 == result;
      v6 = ++v11 < result;
      ++pThis_20;
    }
    while ( v6 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x49E340 sub_49E340 —— 结算动画装配（+56 图像、+48/+52 帧字段、M_RESULT 事件）
// ------------------------------------------------------------
char /*thiscall*/ sub_49E340(int this, void *Block, int nArg3)
{
  uint8_t *pMem; // eax
  int v5; // edi
  uint8_t *v6; // eax
  uint8_t *pMem2; // eax
  uint8_t *v8; // eax
  int v9; // edx
  uint8_t *pMem3; // eax
  uint8_t *pMem32; // esi
  int v12; // ecx
  int v13; // edx
  int fld_30; // eax
  int fld_34; // [esp-8h] [ebp-50h]
  uint32_t v17[3]; // [esp+8h] [ebp-40h]
  uint32_t v18[3]; // [esp+14h] [ebp-34h]
  uint32_t v19[3]; // [esp+20h] [ebp-28h]
  void *v20[4]; // [esp+2Ch] [ebp-1Ch]
  int v21; // [esp+44h] [ebp-4h]
  char *Blocka; // [esp+50h] [ebp+8h]
  int dword_79C0B02; // [esp+54h] [ebp+Ch]

  *(uint32_t *)(this + 116) = Block;
  *(uint32_t *)(this + 120) = nArg3;
  *(uint32_t *)(this + 56) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 208);
  pMem = operator new(0x68u);
  v5 = 0;
  v21 = 0;
  if ( pMem != nullptr )
    v6 = sub_426BD0(pMem);
  else
    v6 = nullptr;
  *(uint32_t *)(this + 48) = v6;
  *((uint32_t *)v6 + 7) = 640;
  *((uint32_t *)v6 + 8) = 480;
  *(uint32_t *)(*(uint32_t *)(this + 48) + 68) = this;
  pMem2 = operator new(0x68u);
  v21 = 1;
  if ( pMem2 != nullptr )
    v8 = sub_426BD0(pMem2);
  else
    v8 = nullptr;
  *(uint32_t *)(this + 52) = v8;
  *((uint32_t *)v8 + 17) = this;
  fld_34 = *(uint32_t *)(this + 52);
  v21 = -1;
  sub_69A840(fld_34);
  v9 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 64);
  v18[0] = -5;
  v18[1] = -5;
  v18[2] = -5;
  v19[0] = *(uint32_t *)(this + 56);
  v19[2] = v19[0];
  v20[0] = (void *)22;
  v20[1] = (void *)36;
  v20[2] = (void *)32;
  v17[0] = 0;
  v17[1] = 0;
  v17[2] = 2;
  v19[1] = v9;
  Blocka = (char *)(this + 36);
  do
  {
    pMem3 = operator new(0x2Cu);
    pMem32 = pMem3;
    v20[3] = pMem3;
    v21 = 2;
    if ( pMem3 != nullptr )
    {
      dword_79C0B02 = dword_79C0B0;
      pMem3[4] = 0;
      LOBYTE(v21) = 3;
      *(uint32_t *)pMem3 = &nengine::CNNumberSet::`vftable';
      sub_699E20(pMem3);
      sub_699E40(dword_79C0B02, v19[v5], v20[v5], 9);
    }
    else
    {
      pMem32 = nullptr;
    }
    v12 = v18[v5];
    *(uint32_t *)Blocka = pMem32;
    *((uint32_t *)pMem32 + 10) = v12;
    *(uint32_t *)(*(uint32_t *)Blocka + 36) = v17[v5];
    v13 = *(uint32_t *)Blocka;
    ++v5;
    v21 = -1;
    *(uint8_t *)(v13 + 24) = 0;
    Blocka += 4;
  }
  while ( v5 < 3 );
  sub_698F90(this + 60, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 4) = 0;
  *(uint8_t *)(this + 21) = 0;
  *(uint8_t *)(this + 22) = 0;
  sub_698F90(this + 8, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( *(uint32_t *)(this + 4) != 0 )
  {
    LOBYTE(fld_30) = *(uint8_t *)(*(uint32_t *)(this + 48) + 16);
    if ( (uint8_t)fld_30 == 0 )
    {
      sub_65DC70(lpCriticalSection);
      LOBYTE(fld_30) = (uint8_t)sub_432EA0("M_RESULT", -1, 0, 0);
    }
    *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 1;
  }
  else
  {
    sub_49DCF0(this);
    fld_30 = *(uint32_t *)(this + 48);
    *(uint8_t *)(fld_30 + 16) = 0;
  }
  return fld_30;
}


// ------------------------------------------------------------
// 0x49E560 sub_49E560 —— RESULT_FLASH 演出驱动（+48 亮度 sub_4049C0 插值 → sub_491530/491630 图层）
// ------------------------------------------------------------
int /*thiscall*/ sub_49E560(int this, int nArg2)
{
  uint64_t v2; // rax
  int fld_4; // eax
  int fld_98; // edi
  int pThis_8; // eax
  uint8_t fld_982; // bl
  int pObj; // eax
  uint8_t fld_983; // bl
  int pObj2; // eax
  int fld_42; // eax
  int fld_43; // eax
  int pThis_82; // eax
  int v14; // ebx
  int pThis_83; // eax
  double v16; // st7
  int fld_44; // eax
  int v18; // edi
  int pThis_85; // eax
  float fld_7C; // [esp+48h] [ebp-1Ch]
  float fld_90; // [esp+4Ch] [ebp-18h]
  int pThis_84; // [esp+54h] [ebp-10h]
  float pThis_3C; // [esp+6Ch] [ebp+8h]

  LODWORD(v2) = nArg2;
  if ( nArg2 == *(uint32_t *)(this + 48) )
  {
    fld_4 = *(uint32_t *)(this + 4);
    if ( fld_4 >= 2 )
    {
      fld_98 = 255;
      if ( fld_4 == 2 )
      {
        pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
        fld_98 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_8, 800);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      }
      else if ( fld_4 == 12 )
      {
        fld_98 = *(uint32_t *)(this + 152);
      }
      sub_49DB80(fld_98);
      pThis_3C = (double)sub_699000(this + 60) * 0.000033333334;  // 【clock_now(clk)】
      sub_491530(2, 0);
      fld_982 = fld_98;
      if ( fld_98 >= 120 )
        fld_982 = 120;
      pObj = sub_418DD0(1);
      if ( pObj != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)pObj + 128))(
          pObj,
          111,
          31,
          dword_79C0B0,
          1065353216,
          1065353216,
          COERCE_FLOAT(LODWORD(pThis_3C)),
          (fld_982 << 24) | 0xFFFFFF,
          1129447424,
          1129447424);
      sub_491630(2);
      fld_983 = fld_98;
      if ( fld_98 >= 220 )
        fld_983 = -36;
      pObj2 = sub_418DD0(2);
      if ( pObj2 != 0 )
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(
          pObj2,
          122,
          71,
          dword_79C0B0,
          1065353216,
          1065353216,
          0,
          (fld_983 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_49DE70((void *)this, fld_98);
      if ( *(uint32_t *)(this + 4) == 2 && sub_699000(this + 8) >= 800 )  // 【clock_now(clk)】
        goto LABEL_41;
    }
    fld_42 = *(uint32_t *)(this + 4);
    if ( fld_42 >= 3 )
    {
      if ( fld_42 == 3 )
      {
        sub_49E110(*(uint32_t *)(this + 124), 0);
        sub_49DD80(0);
      }
      sub_69A110(273, 352, *(uint32_t *)(this + 148), *(uint32_t *)(this + 152));
      if ( *(uint32_t *)(this + 4) == 3 && sub_699000(this + 8) >= 1000 )  // 【clock_now(clk)】
        goto LABEL_41;
    }
    fld_43 = *(uint32_t *)(this + 4);
    if ( fld_43 >= 4 )
    {
      if ( fld_43 == 4 )
      {
        pThis_82 = sub_699000(this + 8);  // 【clock_now(clk)】
        fld_7C = (float)*(int *)(this + 124);
        v14 = (uint64_t)sub_4049C0(fld_7C, 0.0, pThis_82, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        pThis_83 = sub_699000(this + 8);  // 【clock_now(clk)】
        fld_90 = (float)*(int *)(this + 144);
        v16 = sub_4049C0(0.0, fld_90, pThis_83, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        sub_49E110(v14, (uint64_t)v16);
        pThis_84 = sub_699000(this + 8) % 160;  // 【clock_now(clk)】
        sub_49DD80(pThis_84);
      }
      else
      {
        sub_49E110(*(uint32_t *)(this + 124), *(uint32_t *)(this + 144));
        sub_49DD80(0);
      }
      if ( *(uint32_t *)(this + 4) == 4 && (double)sub_699000(this + 8) >= 1100.0 )  // 【clock_now(clk)】
      {
        *(uint32_t *)(this + 124) = 0;
        *(uint8_t *)(this + 101) = 0;
        *(uint8_t *)(this + 102) = 0;
        sub_698F90(this + 88, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
LABEL_41:
        LODWORD(v2) = sub_49E050(*(uint32_t *)(this + 4) + 1);
        return v2;
      }
    }
    fld_44 = *(uint32_t *)(this + 4);
    if ( fld_44 == 5 || fld_44 == 6 || fld_44 == 7 || fld_44 == 8 )
    {
      v18 = fld_44 - 5;
      sub_49E1B0((int *)this, fld_44 - 5);
      if ( *(uint32_t *)(this + 4) == v18 + 5 && sub_699000(this + 8) >= 1000 )  // 【clock_now(clk)】
      {
        *(uint8_t *)(this + 101) = 0;
        *(uint8_t *)(this + 102) = 0;
        sub_698F90(this + 88, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        goto LABEL_41;
      }
    }
    if ( *(int *)(this + 4) >= 9 )
    {
      sub_49E1B0((int *)this, 4);
      if ( *(uint32_t *)(this + 4) == 9 && sub_699000(this + 8) >= 1000 )  // 【clock_now(clk)】
        goto LABEL_41;
    }
    if ( *(uint32_t *)(this + 4) == 10 )
    {
      sub_49DC30((uint32_t *)this);
      if ( sub_699000(this + 8) >= 560 )  // 【clock_now(clk)】
        goto LABEL_41;
    }
    if ( *(uint32_t *)(this + 4) == 11 && sub_699000(this + 8) >= 3000 )  // 【clock_now(clk)】
      goto LABEL_41;
    LODWORD(v2) = *(uint32_t *)(this + 4);
    if ( (int)v2 >= 12 )
    {
      pThis_85 = sub_699000(this + 8);  // 【clock_now(clk)】
      v2 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_85, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      *(uint32_t *)(this + 152) = v2;
      if ( *(uint32_t *)(this + 4) == 12 )
      {
        LODWORD(v2) = sub_699000(this + 8);  // 【clock_now(clk)】
        if ( (int)v2 >= 1000 )
          LODWORD(v2) = sub_49E050(0);
      }
    }
  }
  return v2;
}


// ============================================================
// §P 0x49E930-0x49FFC0  列表子项管理 + 收尾
// ============================================================
// ------------------------------------------------------------
// 0x49E930 sub_49E930
// ------------------------------------------------------------
int /*thiscall*/ sub_49E930(int this)
{
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = -1;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 112) = 0;
  *(uint32_t *)(this + 116) = 0;
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 124) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)(this + 132) = 0;
  *(uint32_t *)(this + 136) = 0;
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint8_t *)(this + 148) = -1;
  return -1;
}



// ------------------------------------------------------------
// 0x49E990 sub_49E990
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49E990(uint32_t *this)
{
  *this = 0;
  *(this + 1) = 255;
  *(this + 2) = 255;
  *(this + 3) = 255;
  *(this + 4) = 255;
  *(this + 5) = 255;
  *(this + 6) = 255;
  *(this + 7) = 255;
  *(this + 8) = 255;
  *(this + 9) = 0xFFFF;
  *(this + 10) = 0xFFFF;
  *(this + 11) = 0xFFFF;
  *(this + 12) = 0xFFFF;
  *(this + 13) = 0xFFFF;
  *(this + 14) = 0xFFFF;
  *(this + 15) = 0xFFFF;
  *(this + 16) = 0xFFFF;
  sub_49E930((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x49E9E0 sub_49E9E0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49E9E0(uint32_t *Block, char pszArg2)
{
  *Block = &CNWarRoom::`vftable';
  nullsub_3(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x49EA10 sub_49EA10
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA10(uint32_t *this)
{
  *(this + 1) = 0;
  *(this + 2) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x49EA20 sub_49EA20
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA20(uint32_t *this)
{
  uint32_t *pThis_1; // ecx

  pThis_1 = this + 1;
  *pThis_1 = &CNWarRoom::`vftable';
  return nullsub_3(pThis_1);
}



// ------------------------------------------------------------
// 0x49EA30 sub_49EA30
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA30(uint32_t *this, int nArg2)
{
  return *(this + 1) + 12 * nArg2;
}



// ------------------------------------------------------------
// 0x49EA50 sub_49EA50
// ------------------------------------------------------------
int /*cdecl*/ sub_49EA50(int pArg1)
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 173) == 0; i = *(uint32_t *)(i + 8) )
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x49EA80 sub_49EA80
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_49EA80(uint32_t *pArg1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 173) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 173) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EAB0 sub_49EAB0
// ------------------------------------------------------------
int /*thiscall*/ sub_49EAB0(uint32_t *this, uint32_t *pArg2)
{
  int result; // eax
  int v3; // esi
  int fld_e1; // ecx
  uint32_t *v5; // ecx

  result = *pArg2;
  *pArg2 = *(uint32_t *)(*pArg2 + 8);
  v3 = *(uint32_t *)(result + 8);
  if ( *(uint8_t *)(v3 + 173) == 0 )
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
// 0x49EB20 sub_49EB20
// ------------------------------------------------------------
int /*thiscall*/ sub_49EB20(void *this)
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 173) != 0 )
  {
    result = v1[2];
    *(uint32_t *)this = result;
  }
  else
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 173) != 0 )
    {
      result = v1[1];
      if ( *(uint8_t *)(result + 173) == 0 )
      {
        do
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 173) == 0 );
        if ( *(uint8_t *)(result + 173) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 173) == 0; result = *(uint32_t *)(result + 8) )
        v3 = result;
      *(uint32_t *)this = v3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EBA0 sub_49EBA0
// ------------------------------------------------------------
int */*thiscall*/ sub_49EBA0(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 173) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 173) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 173) == 0; result = (int *)result[1] )
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
      if ( *(uint8_t *)(*v2 + 173) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 173) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EC10 sub_49EC10
// ------------------------------------------------------------
int /*thiscall*/ sub_49EC10(int *this)
{
  int fld_e2; // edx
  int result; // eax
  uint32_t *fld_e1; // ecx

  fld_e2 = *(this + 2);
  result = 0;
  if ( fld_e2 > 0 )
  {
    fld_e1 = (uint32_t *)(*(this + 1) + 8);
    do
    {
      result += *fld_e1;
      fld_e1 += 3;
      --fld_e2;
    }
    while ( fld_e2 != 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EC30 sub_49EC30
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49EC30(uint32_t *this, int pArg2)
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);
  *(uint32_t *)(pArg2 + 8) = *result;
  if ( *(uint8_t *)(*result + 173) == 0 )
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
// 0x49EC90 sub_49EC90
// ------------------------------------------------------------
int */*thiscall*/ sub_49EC90(uint32_t *this, uint32_t *uArg2)
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);
  v3 = (int *)result[1];
  while ( *((uint8_t *)v3 + 173) == 0 )
  {
    if ( v3[3] >= *uArg2 )
    {
      result = v3;
      v3 = (int *)*v3;
    }
    else
    {
      v3 = (int *)v3[2];
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49ECD0 sub_49ECD0
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_49ECD0(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)
{
  uint32_t *result; // eax

  result = operator new(0xB0u);
  if ( result != nullptr )
  {
    *result = nArg1;
    result[2] = nArg3;
    result[1] = nArg2;
    result[3] = *pArg4;
    result[4] = &CNWarRoom::`vftable';
    qmemcpy(result + 5, pArg4 + 2, 0x98u);
    *((uint8_t *)result + 172) = pszArg5;
    *((uint8_t *)result + 173) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49ED30 sub_49ED30
// ------------------------------------------------------------
uint32_t *sub_49ED30()
{
  uint32_t *result; // eax

  result = operator new(0xB0u);
  if ( result != nullptr )
    *result = 0;
  if ( result != (uint32_t *)-4 )
    result[1] = 0;
  if ( result != (uint32_t *)-8 )
    result[2] = 0;
  *((uint8_t *)result + 172) = 1;
  *((uint8_t *)result + 173) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x49ED70 sub_49ED70
// ------------------------------------------------------------
int **/*thiscall*/ sub_49ED70(int **this, int **pDwArg2, uint32_t *uArg3)
{
  int *v5; // eax
  int *fld_e1; // esi
  int *v8; // [esp+18h] [ebp+Ch]

  v5 = sub_49EC90(this, uArg3);
  fld_e1 = *(this + 1);
  v8 = v5;
  if ( v5 == fld_e1 || *uArg3 < v5[3] )
  {
    *pDwArg2 = fld_e1;
    return pDwArg2;
  }
  else
  {
    *pDwArg2 = v8;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x49EDC0 sub_49EDC0
// ------------------------------------------------------------
int /*thiscall*/ sub_49EDC0(int *this, int nArg2, int *pDwArg3)
{
  int fld_e2; // ebx
  int v4; // esi
  int fld_e1; // edx
  int nArg22; // edi
  int v7; // ecx
  int *v8; // eax
  int *v9; // eax
  int *v10; // eax
  int v11; // eax
  uint32_t *fld_e12; // esi
  int *v14; // eax
  int *v15; // ecx
  int *v16; // eax
  int v17; // eax

  if ( pDwArg3 == (int *)-1 )
  {
    fld_e2 = *(this + 2);
    v4 = 0;
    if ( fld_e2 <= 0 )
    {
      return 0;
    }
    else
    {
      fld_e1 = *(this + 1);
      nArg22 = nArg2;
      while ( 1 )
      {
        v7 = *(uint32_t *)(fld_e1 + 4);
        v8 = *(int **)(v7 + 4);
        while ( *((uint8_t *)v8 + 173) == 0 )
        {
          if ( v8[3] >= nArg22 )
          {
            v7 = (int)v8;
            v8 = (int *)*v8;
          }
          else
          {
            v8 = (int *)v8[2];
          }
        }
        v9 = *(int **)(fld_e1 + 4);
        nArg2 = v7;
        if ( (int *)v7 == v9 || nArg22 < *(uint32_t *)(v7 + 12) )
        {
          pDwArg3 = v9;
          v10 = (int *)&pDwArg3;
        }
        else
        {
          v10 = &nArg2;
        }
        v11 = *v10;
        if ( v11 != *(uint32_t *)(fld_e1 + 4) )
          break;
        ++v4;
        fld_e1 += 12;
        if ( v4 >= fld_e2 )
          return 0;
      }
      return v11 + 16;
    }
  }
  else
  {
    fld_e12 = (uint32_t *)(*(this + 1) + 12 * (uint32_t)pDwArg3);
    v14 = sub_49EC90(fld_e12, &nArg2);
    v15 = (int *)fld_e12[1];
    pDwArg3 = v14;
    if ( v14 == v15 || nArg2 < v14[3] )
    {
      nArg2 = (int)v15;
      v16 = &nArg2;
    }
    else
    {
      v16 = (int *)&pDwArg3;
    }
    v17 = *v16;
    if ( v17 == fld_e12[1] )
      return 0;
    else
      return v17 + 16;
  }
}



// ------------------------------------------------------------
// 0x49EE90 sub_49EE90
// ------------------------------------------------------------
int /*thiscall*/ sub_49EE90(uint32_t *this, uint32_t *uArg2)
{
  int v3; // esi
  uint32_t *fld_e1; // ecx
  uint32_t *uArg22; // eax
  int v6; // ebx

  v3 = 12 * (uint32_t)uArg2;
  fld_e1 = *(uint32_t **)(12 * (uint32_t)uArg2 + *(this + 1) + 4);
  uArg22 = (uint32_t *)*fld_e1;
  v6 = 0;
  uArg2 = (uint32_t *)*fld_e1;
  if ( uArg2 != fld_e1 )
  {
    do
    {
      if ( sub_48FD50(uArg22 + 4) )
        ++v6;
      sub_49EBA0((int *)&uArg2);
      uArg22 = uArg2;
    }
    while ( uArg2 != *(uint32_t **)(v3 + *(this + 1) + 4) );
  }
  return v6;
}



// ------------------------------------------------------------
// 0x49EEE0 sub_49EEE0
// ------------------------------------------------------------
int /*thiscall*/ sub_49EEE0(uint32_t *this, int nArg2)
{
  int v3; // esi
  int *fld_e1; // ecx
  int nArg22; // eax
  bool v6; // zf
  uint32_t *v7; // ebx
  int v9; // [esp+8h] [ebp-4h]

  v3 = 12 * nArg2;
  fld_e1 = *(int **)(12 * nArg2 + *(this + 1) + 4);
  nArg22 = *fld_e1;
  v6 = *fld_e1 == (uint32_t)fld_e1;
  v9 = 0;
  nArg2 = *fld_e1;
  if ( v6 )
    return 0;
  do
  {
    v7 = (uint32_t *)(nArg22 + 16);
    if ( sub_48FD50((uint32_t *)(nArg22 + 16)) )
      v9 += sub_48FBB0(v7);
    sub_49EBA0(&nArg2);
    nArg22 = nArg2;
  }
  while ( nArg2 != *(uint32_t *)(v3 + *(this + 1) + 4) );
  return v9;
}



// ------------------------------------------------------------
// 0x49EF60 sub_49EF60
// ------------------------------------------------------------
int /*thiscall*/ sub_49EF60(uint32_t *this, int nArg2)
{
  int v3; // esi
  int *fld_e1; // ecx
  int nArg22; // eax
  bool v6; // zf
  uint32_t *v7; // ebx
  int v9; // [esp+8h] [ebp-4h]

  v3 = 12 * nArg2;
  fld_e1 = *(int **)(12 * nArg2 + *(this + 1) + 4);
  nArg22 = *fld_e1;
  v6 = *fld_e1 == (uint32_t)fld_e1;
  v9 = 0;
  nArg2 = *fld_e1;
  if ( v6 )
    return 0;
  do
  {
    v7 = (uint32_t *)(nArg22 + 16);
    if ( sub_48FD50((uint32_t *)(nArg22 + 16)) )
      v9 += sub_48F4C0(v7);
    sub_49EBA0(&nArg2);
    nArg22 = nArg2;
  }
  while ( nArg2 != *(uint32_t *)(v3 + *(this + 1) + 4) );
  return v9;
}



// ------------------------------------------------------------
// 0x49EFE0 sub_49EFE0
// ------------------------------------------------------------
char /*thiscall*/ sub_49EFE0(int *this, int nArg2, uint32_t *uArg3, uint32_t *uArg4, uint32_t *uArg5)
{
  int fld_e2; // ecx
  int *fld_e1; // eax
  int v8; // esi
  bool fld_e22; // cc
  int *v11; // [esp+Ch] [ebp-Ch] BYREF
  int v12; // [esp+10h] [ebp-8h]
  int v13; // [esp+14h] [ebp-4h]

  fld_e2 = *(this + 2);
  v12 = 0;
  if ( fld_e2 <= 0 )
    return 0;
  v13 = 0;
  while ( 1 )
  {
    fld_e1 = *(int **)(v13 + *(this + 1) + 4);
    v8 = *fld_e1;
    v11 = (int *)*fld_e1;
    if ( v11 != fld_e1 )
      break;
LABEL_6:
    fld_e22 = ++v12 < *(this + 2);
    v13 += 12;
    if ( !fld_e22 )
      return 0;
  }
  while ( sub_48FB60((uint32_t *)(v8 + 16), nArg2, nullptr) == 0 )
  {
    sub_49EBA0((int *)&v11);
    v8 = (int)v11;
    if ( v11 == *(int **)(v13 + *(this + 1) + 4) )
      goto LABEL_6;
  }
  if ( uArg4 != nullptr )
    *uArg4 = *(uint32_t *)(v8 + 12);
  if ( uArg5 != nullptr )
    *uArg5 = v12;
  if ( uArg3 != nullptr )
    *uArg3 = v8 + 16;
  return 1;
}



// ------------------------------------------------------------
// 0x49F090 sub_49F090
// ------------------------------------------------------------
char /*stdcall*/ sub_49F090(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 173);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_49F090(i[2]);
    i = (void **)*i;
    sub_49EC00(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 173);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49F0E0 sub_49F0E0
// ------------------------------------------------------------
int /*thiscall*/ sub_49F0E0(uint32_t *this)
{
  int v2; // ebx
  int fld_e1; // esi
  int v4; // eax
  int v5; // esi
  uint32_t *v6; // eax
  int v8; // [esp+8h] [ebp-4h]

  v2 = 0;
  if ( (int)*(this + 2) > 0 )
  {
    v8 = 0;
    do
    {
      fld_e1 = *(this + 1);
      v4 = *(uint32_t *)(fld_e1 + v8 + 4);
      v5 = v8 + fld_e1;
      sub_49F090(*(void ***)(v4 + 4));
      *(uint32_t *)(*(uint32_t *)(v5 + 4) + 4) = *(uint32_t *)(v5 + 4);
      v6 = *(uint32_t **)(v5 + 4);
      *(uint32_t *)(v5 + 8) = 0;
      *v6 = v6;
      *(uint32_t *)(*(uint32_t *)(v5 + 4) + 8) = *(uint32_t *)(v5 + 4);
      ++v2;
      v8 += 12;
    }
    while ( v2 < *(this + 2) );
  }
  return sub_48FE80(0);
}



// ------------------------------------------------------------
// 0x49F150 sub_49F150
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49F150(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, uint32_t *uArg5)
{
  uint32_t *fld_e1; // ecx
  uint32_t *fld_e12; // eax
  uint32_t *fld_e13; // eax
  int fld_e14; // eax
  int *v10; // eax
  int v11; // esi
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

  if ( (unsigned int)*(this + 2) >= 0x1999998 )
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
  fld_e1 = sub_49ECD0(*(this + 1), (int)pArg4, *(this + 1), uArg5, 0);
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
  v11 = (int)fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 172) == 0 )
  {
    while ( 1 )
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];
        if ( *(uint8_t *)(v14 + 172) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_49EC30(this, *v10);
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 172) = 0;
          sub_49EAB0(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 172) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_49EAB0(this, (uint32_t *)*v10);
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 172) = 0;
        sub_49EC30(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 172) = 1;
      *(uint8_t *)(v14 + 172) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 172) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) != 0 )
      {
        fld_e1 = fld_e15;
        break;
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 172) = 1;
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x49F330 sub_49F330
// ------------------------------------------------------------
int /*thiscall*/ sub_49F330(int *this, int pArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // ebx
  uint32_t *fld_e1; // esi
  int *v6; // eax
  bool v7; // cl
  int v8; // edx
  uint32_t *fld_e12; // edx
  int v10; // edx
  int v12; // ecx
  char v13; // [esp+Ch] [ebp-4h]

  uArg32 = uArg3;
  fld_e1 = (uint32_t *)*(this + 1);
  v6 = (int *)fld_e1[1];
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 173) == 0 )
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
    while ( *((uint8_t *)v6 + 173) == 0 );
  }
  fld_e12 = fld_e1;
  uArg3 = fld_e1;
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )
    {
      v10 = *sub_49F150(this, &uArg3, 1, fld_e1, uArg32);
      *(uint8_t *)(pArg2 + 4) = 1;
      *(uint32_t *)pArg2 = v10;
      return pArg2;
    }
    sub_49EB20(&uArg3);
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
    v12 = *sub_49F150(this, &uArg3, v13, fld_e1, uArg32);
    *(uint32_t *)pArg2 = v12;
    *(uint8_t *)(pArg2 + 4) = 1;
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x49F3F0 sub_49F3F0
// ------------------------------------------------------------
int */*thiscall*/ sub_49F3F0(uint32_t *this, int *pDwArg2, int pArg3)
{
  int *v3; // ebx
  int pArg3222; // edi
  int pArg32; // ecx
  int pArg322; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  uint32_t *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int *pArg323; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint8_t *pObj; // eax
  char *v17; // ecx
  int v18; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v21; // [esp+34h] [ebp-34h] BYREF
  char v22; // [esp+38h] [ebp-30h]
  int v23; // [esp+48h] [ebp-20h]
  int v24; // [esp+4Ch] [ebp-1Ch]
  int v25; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v28; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *(uint8_t *)(pArg3 + 173) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22 = 0;
    sub_4015C0(&v21, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v28 = 0;
    sub_401740(pExceptionObject, &v21);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = (int *)a3;
  Block = (void *)a3;
  sub_49EBA0(&a3);
  if ( *(uint8_t *)(*v3 + 173) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *(uint8_t *)(v4 + 173) == 0 )
      *(uint32_t *)(v4 + 4) = v6;
    v7 = v27;
    v8 = v27[1];
    if ( *(int **)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( *(int **)v6 == v3 )
    {
      *(uint32_t *)v6 = v4;
    }
    else
    {
      *(uint32_t *)(v6 + 8) = v4;
    }
    if ( *(int **)v7[1] == v3 )
    {
      if ( *(uint8_t *)(v4 + 173) != 0 )
      {
        v9 = (uint32_t *)v6;
      }
      else
      {
        v9 = sub_49EA80((uint32_t *)v4);
        v7 = v27;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v25 = v10;
    if ( v11 )
    {
      if ( *(uint8_t *)(v4 + 173) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v25 + 8) = sub_49EA50(v4);
    }
    goto LABEL_35;
  }
  if ( *(uint8_t *)(v3[2] + 173) != 0 )
  {
    v4 = *v3;
    goto LABEL_8;
  }
  v5 = a3;
  v4 = *(uint32_t *)(a3 + 8);
  if ( (int *)a3 == v3 )
    goto LABEL_8;
  *(uint32_t *)(*v3 + 4) = a3;
  *(uint32_t *)v5 = *v3;
  if ( v5 == v3[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = *(uint32_t *)(v5 + 4);
    if ( *(uint8_t *)(v4 + 173) == 0 )
      *(uint32_t *)(v4 + 4) = v6;
    *(uint32_t *)v6 = v4;
    *(uint32_t *)(v5 + 8) = v3[2];
    *(uint32_t *)(v3[2] + 4) = v5;
  }
  v12 = v27[1];
  if ( *(int **)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int *)v3[1];
    if ( (int *)*v13 == v3 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  *(uint32_t *)(v5 + 4) = v3[1];
  v14 = *(uint8_t *)(v5 + 172);
  *(uint8_t *)(v5 + 172) = *((uint8_t *)v3 + 172);
  *((uint8_t *)v3 + 172) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 172) == 1 )
  {
    v15 = v27;
    if ( v4 != *(uint32_t *)(v27[1] + 4) )
    {
      do
      {
        if ( *(uint8_t *)(v4 + 172) != 1 )
          break;
        v16 = *(uint8_t **)v6;
        if ( v4 == *(uint32_t *)v6 )
        {
          v16 = *(uint8_t **)(v6 + 8);
          if ( v16[172] == 0 )
          {
            v16[172] = 1;
            *(uint8_t *)(v6 + 172) = 0;
            sub_49EC30(v15, v6);
            v16 = *(uint8_t **)(v6 + 8);
            v15 = v27;
          }
          if ( v16[173] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)v16 + 172) != 1 || *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) != 1 )
          {
            if ( *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)v16 + 172) = 1;
              v16[172] = 0;
              sub_49EAB0(v15, v16);
              v16 = *(uint8_t **)(v6 + 8);
              v15 = v27;
            }
            v16[172] = *(uint8_t *)(v6 + 172);
            *(uint8_t *)(v6 + 172) = 1;
            *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) = 1;
            sub_49EC30(v15, v6);
            break;
          }
        }
        else
        {
          if ( v16[172] == 0 )
          {
            v16[172] = 1;
            *(uint8_t *)(v6 + 172) = 0;
            sub_49EAB0(v15, (uint32_t *)v6);
            v16 = *(uint8_t **)v6;
            v15 = v27;
          }
          if ( v16[173] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) != 1 || *(uint8_t *)(*(uint32_t *)v16 + 172) != 1 )
          {
            if ( *(uint8_t *)(*(uint32_t *)v16 + 172) == 1 )
            {
              *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) = 1;
              v16[172] = 0;
              sub_49EC30(v15, (int)v16);
              v16 = *(uint8_t **)v6;
              v15 = v27;
            }
            v16[172] = *(uint8_t *)(v6 + 172);
            *(uint8_t *)(v6 + 172) = 1;
            *(uint8_t *)(*(uint32_t *)v16 + 172) = 1;
            sub_49EAB0(v15, (uint32_t *)v6);
            break;
          }
        }
        v16[172] = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(uint32_t *)(v15[1] + 4);
        v6 = *(uint32_t *)(v6 + 4);
      }
      while ( !v11 );
    }
    *(uint8_t *)(v4 + 172) = 1;
  }
  v17 = (char *)Block + 16;
  *((uint32_t *)Block + 4) = &CNWarRoom::`vftable';
  nullsub_3(v17);
  j__free(Block);
  v18 = pThis[2];
  if ( v18 != 0 )
    pThis[2] = v18 - 1;
  *pDwArg2 = pArg3;
  return pDwArg2;
}


// ------------------------------------------------------------
// 0x49F750 sub_49F750
// ------------------------------------------------------------
int */*thiscall*/ sub_49F750(int **this, int *pDwArg2, int nArg3, int nArg4)
{
  int nArg42; // ebx
  int fld_e1; // eax
  int nArg32; // ecx
  uint32_t *fld_e12; // eax
  int nArg322; // edi

  nArg42 = nArg4;
  fld_e1 = (int)*(this + 1);
  nArg32 = nArg3;
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )
  {
    sub_49F090(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( nArg3 != nArg4 )
    {
      do
      {
        nArg322 = nArg32;
        sub_49EBA0(&nArg3);
        sub_49F3F0(this, &nArg4, nArg322);
        nArg32 = nArg3;
      }
      while ( nArg3 != nArg42 );
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x49F7D0 sub_49F7D0
// ------------------------------------------------------------
int /*thiscall*/ sub_49F7D0(int *this, int nArg2, int *pDwArg3)
{
  int nArg22; // esi
  int result; // eax
  uint32_t *pMem; // eax
  uint32_t *pMem2; // ebx
  int *pDwArg32; // eax
  int *pThis2; // edi
  int v9; // esi
  int *v10; // ecx
  uint32_t *v11; // edi
  int *v12; // eax
  int *v13; // edi
  int **v14; // eax
  int nArg222; // [esp+4h] [ebp-B8h] BYREF
  uint32_t v16[39]; // [esp+8h] [ebp-B4h] BYREF
  char v17[4]; // [esp+A4h] [ebp-18h] BYREF
  void *Block; // [esp+A8h] [ebp-14h]
  int *pThis; // [esp+ACh] [ebp-10h]
  int v20; // [esp+B8h] [ebp-4h]

  nArg22 = nArg2;
  pThis = this;
  result = sub_49EDC0(this, nArg2, pDwArg3);
  if ( result == 0 )
  {
    pMem = operator new(0x9Cu);
    pMem2 = pMem;
    Block = pMem;
    v20 = 0;
    if ( pMem != nullptr )
    {
      *pMem = &CNWarRoom::`vftable';
      sub_49E990(v5 + 1);
      nullsub_3(v6);
      unknown_libname_7(v3);
    }
    else
    {
      v6 = nullptr;
    }
    v7 = a3;
    v15 = v3;
    *((uint8_t *)v6 + 152) = (uint8_t)a3;
    v16[0] = &CNWarRoom::`vftable';
    qmemcpy(&v16[1], pMem2 + 1, 0x98u);
    pThis2 = pThis;
    v9 = 12 * (uint32_t)pDwArg32;
    v10 = (int *)(12 * (uint32_t)pDwArg32 + pThis[1]);
    v20 = 1;
    sub_49F330(v10, (int)v17, &nArg222);
    v20 = -1;
    v16[0] = &CNWarRoom::`vftable';
    nullsub_3(v16);
    (*(void (/*thiscall*/ **)(uint32_t *, int))*pMem2)(pMem2, 1);
    v11 = (uint32_t *)(v9 + pThis2[1]);
    v12 = sub_49EC90(v11, &nArg2);
    v13 = (int *)v11[1];
    pDwArg3 = v12;
    if ( v12 == v13 || nArg2 < v12[3] )
    {
      nArg2 = (int)v13;
      v14 = (int **)&nArg2;
    }
    else
    {
      v14 = &pDwArg3;
    }
    return (int)(*v14 + 4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49F900 sub_49F900
// ------------------------------------------------------------
void /*thiscall*/ sub_49F900(int **this)
{
  int v2; // [esp+4h] [ebp-4h] BYREF

  sub_49F750(this, &v2, **(this + 1), (int)*(this + 1));
  j__free(*(this + 1));
  *(this + 1) = nullptr;
  *(this + 2) = nullptr;
}



// ------------------------------------------------------------
// 0x49F940 sub_49F940
// ------------------------------------------------------------
void /*thiscall*/ sub_49F940(uint32_t *this)
{
  uint32_t *v2; // eax

  v2 = sub_49ED30();
  *(this + 1) = v2;
  *((uint8_t *)v2 + 173) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
}



// ------------------------------------------------------------
// 0x49F970 sub_49F970
// ------------------------------------------------------------
int /*thiscall*/ sub_49F970(uint32_t *this, int Block)
{
  int *pMem; // eax
  uint32_t *v4; // edi

  *(this + 2) = Block;
  pMem = (int *)operator new(12 * Block + 4);
  v4 = nullptr;
  if ( pMem != nullptr )
  {
    v4 = pMem + 1;
    *pMem = Block;
    `eh vector constructor iterator'(
      pMem + 1,
      0xCu,
      Block,
      (void (/*thiscall*/ *)(void *))sub_49F940,
      (void (/*thiscall*/ *)(void *))sub_49F900);
  }
  *(this + 1) = v4;
  return sub_49F0E0(this);
}



// ------------------------------------------------------------
// 0x49F9F0 sub_49F9F0
// ------------------------------------------------------------
void /*thiscall*/ sub_49F9F0(uint32_t *this)
{
  char *fld_e1; // eax
  char *v2; // esi

  fld_e1 = (char *)*(this + 1);
  if ( fld_e1 != nullptr )
  {
    v2 = fld_e1 - 4;
    `eh vector destructor iterator'(fld_e1, 0xCu, *((uint32_t *)fld_e1 - 1), (void (/*thiscall*/ *)(void *))sub_49F900);
    j_j__free(v2);
  }
}



// ------------------------------------------------------------
// 0x49FA20 sub_49FA20 —— 三字段组写（+40/+44/+48）
// ------------------------------------------------------------
int /*thiscall*/ sub_49FA20(int this, uint32_t *pArg2, uint32_t *uArg3, uint32_t *uArg4)
{
  int v4; // ebx
  int v5; // edi
  float *pThis; // esi
  int v7; // ebx
  int v8; // edi
  float *pThis_C; // esi
  int fld_18; // ecx
  int v11; // eax
  uint32_t *uArg42; // ecx
  uint32_t *uArg32; // edx
  int fld_1C; // esi
  int fld_20; // esi
  int v16; // esi
  int fld_24; // eax
  int v18; // esi
  int fld_28; // eax
  int fld_2C; // eax
  char *v23; // [esp+10h] [ebp-Ch]
  int v24; // [esp+14h] [ebp-8h]
  int v25; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]
  int v27; // [esp+18h] [ebp-4h]
  int v28; // [esp+18h] [ebp-4h]

  *uArg4 = 0;
  v4 = 0;
  v5 = 0;
  pThis = (float *)this;
  v23 = (char *)pArg2 - this;
  do
  {
    v24 = (uint64_t)(*pThis * 10.0);
    if ( v24 != 0 )
    {
      if ( (unsigned int)(uint64_t)(*(float *)&v23[(uint32_t)pThis] * 10.0) == v24 )
      {
        v4 |= 2 << v5;
      }
      else
      {
        *uArg3++ = *(uint32_t *)pThis;
        *uArg4 += 4;
      }
    }
    else
    {
      v4 |= 1 << v5;
    }
    v5 += 2;
    ++pThis;
  }
  while ( v5 < 6 );
  v26 = v4 << 26;
  v7 = 0;
  v8 = 0;
  pThis_C = (float *)(this + 12);
  do
  {
    v25 = (uint64_t)(*pThis_C * 10.0);
    if ( v25 != 0 )
    {
      if ( (unsigned int)(uint64_t)(*(float *)&v23[(uint32_t)pThis_C] * 10.0) == v25 )
      {
        v7 |= 2 << v8;
      }
      else
      {
        *uArg3++ = *(uint32_t *)pThis_C;
        *uArg4 += 4;
      }
    }
    else
    {
      v7 |= 1 << v8;
    }
    v8 += 2;
    ++pThis_C;
  }
  while ( v8 < 6 );
  fld_18 = *(uint32_t *)(this + 24);
  v11 = 0;
  v27 = (v7 << 20) | v26;
  if ( fld_18 != 0 )
  {
    uArg32 = uArg3;
    if ( pArg2[6] == fld_18 )
    {
      uArg42 = uArg4;
      v11 = 2;
    }
    else
    {
      *uArg3 = fld_18;
      uArg42 = uArg4;
      uArg32 = uArg3 + 1;
      *uArg4 += 4;
    }
  }
  else
  {
    uArg42 = uArg4;
    uArg32 = uArg3;
    v11 = 1;
  }
  fld_1C = *(uint32_t *)(this + 28);
  if ( fld_1C != 0 )
  {
    if ( pArg2[7] == fld_1C )
    {
      v11 |= 8u;
    }
    else
    {
      *uArg32++ = fld_1C;
      *uArg42 += 4;
    }
  }
  else
  {
    v11 |= 4u;
  }
  fld_20 = *(uint32_t *)(this + 32);
  if ( fld_20 != 0 )
  {
    if ( pArg2[8] == fld_20 )
    {
      v11 |= 0x20u;
    }
    else
    {
      *uArg32++ = fld_20;
      *uArg42 += 4;
    }
  }
  else
  {
    v11 |= 0x10u;
  }
  v16 = (v11 << 14) | v27;
  fld_24 = *(uint32_t *)(this + 36);
  v28 = v16;
  v18 = 0;
  if ( fld_24 != 0 )
  {
    if ( pArg2[9] == fld_24 )
    {
      v18 = 2;
    }
    else if ( fld_24 == -1 )
    {
      v18 = 3;
    }
    else
    {
      *uArg32++ = fld_24;
      *uArg42 += 4;
    }
  }
  else
  {
    v18 = 1;
  }
  fld_28 = *(uint32_t *)(this + 40);
  if ( fld_28 != 0 )
  {
    if ( pArg2[10] == fld_28 )
    {
      v18 |= 8u;
    }
    else if ( fld_28 == -1 )
    {
      v18 |= 0xCu;
    }
    else
    {
      *uArg32++ = fld_28;
      *uArg42 += 4;
    }
  }
  else
  {
    v18 |= 4u;
  }
  fld_2C = *(uint32_t *)(this + 44);
  if ( fld_2C != 0 )
  {
    if ( pArg2[11] == fld_2C )
    {
      v18 |= 0x20u;
    }
    else if ( fld_2C == -1 )
    {
      v18 |= 0x30u;
    }
    else
    {
      *uArg32 = fld_2C;
      *uArg42 += 4;
    }
  }
  else
  {
    v18 |= 0x10u;
  }
  return v28 | (32 * ((8 * v18) | *(uint8_t *)(this + 48) & 7));
}


// ------------------------------------------------------------
// 0x49FC60 sub_49FC60 —— 七字段访问器（+44..+57 全量下发）
// ------------------------------------------------------------
int /*thiscall*/ sub_49FC60(char *this)
{
  *(uint32_t *)this = 0;
  *((uint32_t *)this + 26) = 0;
  *(this + 108) = 1;
  *((uint32_t *)this + 28) = 0;
  *(this + 116) = 0;
  *(uint16_t *)(this + 117) = 0;
  *(this + 119) = 0;
  *((uint32_t *)this + 30) = 0;
  *((uint32_t *)this + 32) = 0;
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 0;
  *((uint32_t *)this + 35) = 0;
  *(this + 172) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 45) = 0;
  *((uint32_t *)this + 46) = 0;
  *((uint32_t *)this + 47) = 0;
  *((uint32_t *)this + 48) = 0;
  *(this + 196) = 0;
  *((uint32_t *)this + 50) = 0;
  *(this + 124) = 0;
  *((uint32_t *)this + 1) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 2) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = -1;
  *((uint32_t *)this + 11) = -1;
  *((uint32_t *)this + 12) = -1;
  *(this + 52) = 1;
  *(uint32_t *)(this + 53) = 0;
  *(uint32_t *)(this + 65) = 0;
  *(uint32_t *)(this + 77) = 0;
  *(uint32_t *)(this + 89) = -1;
  *(uint32_t *)(this + 57) = 0;
  *(uint32_t *)(this + 69) = 0;
  *(uint32_t *)(this + 81) = 0;
  *(uint32_t *)(this + 93) = -1;
  *(uint32_t *)(this + 61) = 0;
  *(uint32_t *)(this + 73) = 0;
  *(uint32_t *)(this + 85) = 0;
  *(uint32_t *)(this + 97) = -1;
  *(this + 101) = 1;
  return 0;
}



// ------------------------------------------------------------
// 0x49FD20 sub_49FD20 —— +200 状态位（sub_698F90 复位）
// ------------------------------------------------------------
char /*thiscall*/ sub_49FD20(int this)
{
  int fld_68; // ecx
  char result; // al
  int fld_C8; // ecx

  fld_68 = *(uint32_t *)(this + 104);
  if ( fld_68 != 0 )
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_68 + 4))(fld_68, 0);
  *(uint8_t *)(this + 157) = 0;
  *(uint8_t *)(this + 158) = 0;
  result = sub_698F90(this + 144, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_C8 = *(uint32_t *)(this + 200);
  *(uint32_t *)(this + 176) = 0;
  *(uint32_t *)(this + 180) = -fld_C8;
  *(uint32_t *)(this + 184) = 0;
  *(uint32_t *)(this + 188) = 0;
  *(uint32_t *)(this + 192) = 0;
  *(uint8_t *)(this + 196) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x49FD80 sub_49FD80 —— 渲染参数（+40 → sub_432F40）
// ------------------------------------------------------------
int /*thiscall*/ sub_49FD80(float *this, int pArg2, float *pArg3)
{
  int result; // eax
  int v6; // eax
  double v7; // st7
  int v8; // edx
  float *pArg32; // ecx
  double v10; // st6
  double v11; // st6
  int v12; // ebx
  int v13; // eax
  float *pArg33; // ecx
  int v15; // ebx
  int v16; // eax
  int *v17; // ecx
  int v18; // eax
  char v19; // al
  float *pArg34; // eax
  double v21; // st7
  float v22; // [esp+0h] [ebp-20h]
  int v23; // [esp+10h] [ebp-10h]
  int v24; // [esp+14h] [ebp-Ch]
  int v25; // [esp+18h] [ebp-8h]
  int v26; // [esp+1Ch] [ebp-4h]
  int v27; // [esp+28h] [ebp+8h]
  float v28; // [esp+28h] [ebp+8h]

  if ( *(this + pArg2 + 4) == 0.0 && *((uint32_t *)this + pArg2 + 7) == 0 )
    return 0;
  v6 = *((uint32_t *)this + pArg2 + 7);
  v7 = *(this + pArg2 + 4);
  v8 = *((uint32_t *)this + pArg2 + 10);
  v26 = v8;
  if ( v6 != 0 )
  {
    pArg32 = pArg3;
    if ( v8 == -1 || v8 >= (int)pArg3 )
    {
      v11 = (double)((int)pArg3 * v6) * 0.001 + *(this + pArg2 + 4);
      *(this + pArg2 + 4) = v11;
      v7 = (v7 + v11) * 0.5;
      if ( v8 != -1 )
      {
        *((uint32_t *)this + pArg2 + 10) = v8 - (uint32_t)pArg32;
        if ( (float *)v8 == pArg32 )
          *(this + pArg2 + 7) = 0.0;
      }
    }
    else
    {
      v27 = (int)pArg3 - v8;
      *(this + pArg2 + 10) = 0.0;
      *(this + pArg2 + 7) = 0.0;
      v10 = (double)(v6 * v8) * 0.001 + *(this + pArg2 + 4);
      *(this + pArg2 + 4) = v10;
      v7 = ((v7 + v10) * 0.5 * (double)v26 + (double)v27 * v10) / (double)(int)pArg3;
    }
  }
  v12 = 0;
  v28 = (double)(int)pArg3 * v7 * 0.001;
  if ( *((uint32_t *)this + 26) != 0 && *((uint8_t *)this + 108) != 0 )
    goto LABEL_25;
  if ( *(uint32_t *)this == 0 )
    goto LABEL_25;
  v23 = 0;
  v24 = 0;
  v25 = 0;
  pArg3 = this + 1;
  do
  {
    v13 = sub_432F40(*pArg3);
    pArg33 = pArg3;
    *(&v23 + v12++) = v13;
    pArg3 = pArg33 + 1;
  }
  while ( v12 < 3 );
  v22 = v28 + *(this + pArg2 + 1);
  v15 = sub_432F40(v22);
  if ( *(&v23 + pArg2) == v15 )
  {
LABEL_25:
    v21 = v28 + *(this + pArg2 + 1);
    pArg3 = *((float **)this + pArg2 + 7);
    pArg34 = pArg3;
    *(this + pArg2 + 1) = v21;
    if ( pArg34 != nullptr )
    {
      result = 1;
      if ( (double)(int)pArg3 * *(this + pArg2 + 4) >= 0.0 )
        return 3;
    }
    else if ( *(this + pArg2 + 4) == 0.0 )
    {
      return 0;
    }
    else
    {
      return 2;
    }
  }
  else
  {
    while ( 1 )
    {
      v26 = *(&v23 + pArg2);
      v16 = v26 >= v15 ? v26 - 1 : v26 + 1;
      v17 = *(int **)this;
      *(&v23 + pArg2) = v16;
      pArg3 = nullptr;
      v18 = *v17;
      v19 = pArg2 == 2
          ? (*(int (/*stdcall*/ **)(int))(v18 + 132))(v25)
          : (*(unsigned int (/*stdcall*/ **)(int, int, float **))(v18 + 136))(v23, v24, &pArg3);
      if ( v19 == 0 )
        break;
      if ( *(&v23 + pArg2) == v15 )
        goto LABEL_25;
    }
    *(this + pArg2 + 1) = (float)v26;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)this + 40))(*(uint32_t *)this, 1) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, float *))(**(uint32_t **)this + 532))(
        *(uint32_t *)this,
        pArg2,
        *((uint32_t *)this + pArg2 + 4),
        pArg3);
    return 4;
  }
  return result;
}


// ------------------------------------------------------------
// 0x49FFC0 sub_49FFC0 —— 播放尾帧处理（+48/+52/+40 → sub_49FA20 收尾）
// ------------------------------------------------------------
void /*userpurge*/ sub_49FFC0(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>, int nArg4, char pszArg5)
{
  int pObj; // ecx
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int v13; // esi
  int v14; // eax
  int v15; // eax
  int v16; // eax
  const void *v17; // esi
  void *v18; // edi
  int v19; // eax

  pObj = *pArg1;
  if ( pObj != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0
    && (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 80))(*pArg1) != 0
    && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 80))(*pArg1) + 132) != 0 )
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 4, 1, nArg2, nArg3);
    v7 = *(uint32_t *)dword_8F8520;
    v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 48))(*pArg1);
    (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
    v9 = *(uint32_t *)dword_8F8520;
    v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 52))(*pArg1);
    (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
    v11 = *(uint32_t *)dword_8F8520;
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 48))(dword_8F7C04);
    (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
    v13 = *(uint32_t *)dword_8F8520;
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
    (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);
    v15 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 80))(*pArg1);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(
      dword_8F8520,
      *(uint8_t *)(*(uint32_t *)(v15 + 132) + 112));
    v16 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 80))(*pArg1);
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(
      dword_8F8520,
      *(uint8_t *)(*(uint32_t *)(v16 + 132) + 116));
    if ( (uint8_t)nArg4 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 16);
      v17 = pArg1 + 1;
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, pArg1 + 1, 49);
      if ( pszArg5 == 1 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);
      else
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);
      v18 = (char *)pArg1 + 53;
    }
    else
    {
      v18 = (char *)pArg1 + 53;
      v17 = pArg1 + 1;
      v19 = sub_49FA20((char *)pArg1 + 53, &unk_9A026C, &nArg4);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v19);
      (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &unk_9A026C, nArg4);
      if ( pszArg5 == 1 )
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);
      else
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);
    }
    qmemcpy(v18, v17, 0x31u);
    pArg1[45] = sub_699000((int)(pArg1 + 36));  // 【clock_now(clk)】
    *((uint8_t *)pArg1 + 196) = 0;
  }
}


