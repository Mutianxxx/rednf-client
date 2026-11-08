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
int /*thiscall*/ sub_4900E0(uint32_t *this, int ArgList, int nArg3, int nArg4)  // 实现：角色槽位/物件状态切换总入口
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
  if ( ArgLista != nArg3 || (result = *(this + ArgList + 2)) != nArg4 )  // 若 ArgLista != nArg3
  {
    *(this + ArgList + 10) = nArg3;
    *(this + ArgList + 2) = nArg4;
    if ( (uint32_t *)dword_99FF08 == this )
    {
      *(this + ArgList + 20) = 0;
      *(this + ArgList + 28) = 0;
      *((uint8_t *)this + ArgList + 144) = 0;
      sub_4632D0(*((uint32_t *)dword_8F8528 + 4));  // 席位表快照与排序
      if ( ArgLista != nArg3 )  // 若 ArgLista != nArg3
      {
        if ( nArg3 == 0xFFFF )  // 若 nArg3 == 0xFFFF
        {
          v7 = sub_429830(ArgLista);  // 表按键查找（uint16）
          v8 = v7;
          ArgListb = v7;
          if ( v7 != 0 && *(uint32_t *)(v7 + 196) != 0 )  // 若 v7 != 0
            sub_4B05C0(0);  // 置隐藏/屏蔽位 +8052
          if ( *(uint32_t *)(sub_656710() + 40) == ArgList )  // 取全局单例地址（返回 unk_9BD5D0）
          {
            v9 = 0;
            pThis_A = this + 10;
            while ( v9 == ArgList || *pThis_A == 0xFFFF )  // 条件循环
            {
              ++v9;
              ++pThis_A;
              if ( v9 >= 8 )  // 若 v9 >= 8
                goto LABEL_16;
            }
            *(uint32_t *)(sub_656710() + 40) = v9;  // 取全局单例地址（返回 unk_9BD5D0）
            off_77F3FC("@@SET HOST %d", v9);  // 引擎日志输出函数(printf 风格)
LABEL_16:  // 标签 LABEL_16（跳转合流点）
            v8 = ArgListb;
          }
          sub_42B580(*(uint32_t *)(dword_8F7A24 + 40), ArgList, v8);  // 移除 WARROOM 成员
        }
        else  // 否则分支
        {
          v11 = sub_429830(nArg3);  // 表按键查找（uint16）
          sub_42E120(ArgList, v11, 1);  // 观战对象换装演出（273 层）
          v12 = *(uint32_t *)(v11 + 196);
          if ( v12 != 0 )  // 若 v12 非 0
            sub_4B05B0(v12);  // 置状态标志 +8004
          sub_432EA0("LADDER_DOWN", -1, 0, 0);  // 音效播放包装（非空判定）
        }
      }
      pThis_1 = sub_48F660(this + 1, ArgList);  // 槽 id 解析（·sub_429830 查对象）
      if ( pThis_1 != 0 )  // 若 pThis_1 非 0
      {
        pObj = *(uint32_t *)(pThis_1 + 196);
        if ( pObj != 0 )  // 若 pObj 非 0
        {
          ArgListc = 0;
          switch ( nArg4 )  // 按 nArg4 分派
          {
            case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, ArgList + 3);  // 调虚槽 +372：目标点写入
              break;  // 跳出循环/分支
            case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 372))(pObj, 0);  // 调虚槽 +372：目标点写入
              break;  // 跳出循环/分支
            case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 1);  // 调虚槽 +372：目标点写入
              break;  // 跳出循环/分支
            case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
            case 4:  // case 4 = ENUM_CMDPACKET_EXIT
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 372))(pObj, 2);  // 调虚槽 +372：目标点写入
              ArgListc = 1;
              break;  // 跳出循环/分支
            default:  // 默认分支
              break;  // 跳出循环/分支
          }
          sub_4B12B0(ArgListc);  // 事件分发（音效 sub_422E70/43BEE0、sub_4BF300）
        }
      }
      return sub_49CA80(*((uint32_t *)dword_8F8528 + 9));  // 窗口状态查询（+58/+59 → sub_48FCA0/sub_578E80）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4902A0 sub_4902A0 —— 动画播放态判定（帧态 2/3/4 为进行中，-1 视为起始）
//   this+72：被调方 ·0x49EDC0 查出的状态槽值，-1=未开始；2/3/4 已确证为进行中态
//   【推断 2/3/4 依次对应 播放中/收招中/循环中】。breakable_map 用它选 74/75 号图像，
//   window_party 用它兜掉结算态。
// ------------------------------------------------------------
bool /*thiscall*/ sub_4902A0(uint32_t *this)  // 实现：动画播放态判定（帧态 2/3/4 为进行中，-1 视为起始）
{
  int fld_e18; // eax

  fld_e18 = *(this + 18);  // this+72〔nSnapshot72(推断)〕
  return fld_e18 != -1 && (fld_e18 == 2 || fld_e18 == 3 || fld_e18 == 4);  // fld_e18=this+72 nSnapshot72
}



// ------------------------------------------------------------
// 0x4902C0 sub_4902C0 —— 动画状态复位（+204..232 清零、+216=1、+232=-1）
// ------------------------------------------------------------
int /*thiscall*/ sub_4902C0(int this)  // 实现：动画状态复位（+204..232 清零、+216=1、+232=-1）
{
  *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint8_t *)(this + 216) = 1;  // this+216〔bField216(推断)〕
  *(uint8_t *)(this + 217) = 0;
  *(uint32_t *)(this + 232) = -1;  // this+232〔bSyncFlag〕
  return 0;
}



// ------------------------------------------------------------
// 0x4902F0 sub_4902F0 —— 粒子创建包装（"%s%s" 拼路径；失败 PARTICLE CREATER CREATE FAIL!）
// ------------------------------------------------------------
int /*thiscall*/ sub_4902F0(void *this, const char *ArgList, const char *pArg3)  // 实现：粒子创建包装（%s%s 拼路径；失败 PARTICLE CREATER CREATE FAIL!）
{
  int v4; // eax

  v4 = (*(int (**)(int, const char *, ...))(*(uint32_t *)dword_8F84E4 + 12))(dword_8F84E4, "%s%s", ArgList, pArg3);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
  if ( v4 != 0 )  // 若 v4 非 0
    return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 8))(this, v4);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
  else  // 否则分支
    return off_77F3FC("PARTICLE CREATER CREATE FAIL! FILENAME[%s%s]", ArgList, pArg3);  // 返回 调 off_77F3FC
}



// ------------------------------------------------------------
// 0x490340 sub_490340 —— 双层转发（本对象 vt+24，内嵌 +100 子对象 vt+32）
// 两个入参同源 pArg2，第二跳把基址 +100 后转给子对象，属动画/粒子对象的固定委派序。
// ------------------------------------------------------------
int /*thiscall*/ sub_490340(void *this, int pArg2)  // 实现：双层转发（本对象 vt+24，内嵌 +100 子对象 vt+32）
{
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 24))(this, pArg2);  // 调虚槽 +24：CNRDSkillInventoryWindow__vmt18 页签动作（41A5E0 + …
  return (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 32))(this, pArg2 + 100);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
}



// ------------------------------------------------------------
// 0x490370 sub_490370 —— 子动画挂接初始化（+204=子链、+220..228 快照本对象 +4/+8/+12、+232=-1）
// ------------------------------------------------------------
int /*thiscall*/ sub_490370(int this, int nArg2)  // 实现：子动画挂接初始化（+204=子链、+220..228 快照本对象 +4/+8/+12、+232=-1）
{
  int fld_8; // edx  | +0x0008 → 快照源值 B（0x490370：写入 +224）（证据: va=00490370）（CNRDParticleCreater；va=00490370）
  int result; // eax

  *(uint8_t *)(this + 189) = 0;  // this+189〔bFlag189〕
  *(uint8_t *)(this + 190) = 0;  // this+190〔bFlag190〕
  *(uint32_t *)(this + 204) = nArg2;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint8_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = 读 this+8
  *(uint32_t *)(this + 220) = *(uint32_t *)(this + 4);  // this+220〔nSnapDst220(推断)〕等 3 字段
  result = *(uint32_t *)(this + 12);  // result = 读 this+12
  *(uint32_t *)(this + 224) = fld_8;  // this+224〔nSnapDst224(推断)〕
  *(uint32_t *)(this + 228) = result;  // this+228〔nSnapDst228(推断)〕
  *(uint32_t *)(this + 232) = -1;  // this+232〔bSyncFlag〕
  return result;  // result=this+12 nSnapSrc12
}



// ------------------------------------------------------------
// 0x4903D0 sub_4903D0 —— +176 色调对象启停（开关位 +217）
// ------------------------------------------------------------
char /*thiscall*/ sub_4903D0(uint8_t *this, char pszArg2)  // 实现：+176 色调对象启停（开关位 +217）
{
  int pThis_B0; // ecx
  char result; // al

  pThis_B0 = (int)(this + 176);  // this+704〔nSnapshot704〕
  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
  {
    result = sub_699030(pThis_B0);  // 【clock_freeze(clk)】
    *(this + 217) = pszArg2;
  }
  else  // 否则分支
  {
    result = sub_698FE0(pThis_B0);  // 【clock_unfreeze(clk)】
    *(this + 217) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x490410 sub_490410 —— 有序数组二分下界（lower_bound，元素 uint32）
// 区间 [nArg2,nArg3) 与目标 *uArg4：命中 >= 收右界，否则推左界；落点经 *uArg1 输出。
// 用于 dword_9A011C 三角函数表的区间检索。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_490410(uint32_t *uArg1, int nArg2, int nArg3, uint32_t *uArg4)  // 实现：有序数组二分下界（lower_bound，元素 uint32）
{
  int nArg22; // esi
  int v5; // ecx
  int v6; // eax

  nArg22 = nArg2;
  v5 = (nArg3 - nArg2) >> 2;
  while ( v5 > 0 )  // 条件循环
  {
    v6 = v5 / 2;
    if ( *(uint32_t *)(nArg22 + 4 * (v5 / 2)) >= *uArg4 )
    {
      v5 /= 2;
    }
    else  // 否则分支
    {
      nArg22 += 4 * v6 + 4;
      v5 += -1 - v6;
    }
  }
  *uArg1 = nArg22;
  return uArg1;
}



// ------------------------------------------------------------
// 0x490460 sub_490460 —— ★粒子发射随机化（被 CNRDParticleCreater__vmt14 转发，broadcast_debug）
//   先 vt+12 传入配置、vt+16 取发射器基址 v6，然后：
//   · pArg3[3..5] 三轴散布幅值 → rand()%(v+1)-v/2 得对称随机，再经 sub_52A1A0 表取角度分量
//     写 v6[18]/v6[19]/v6[20]（发射器 +72/+76/+80 位置）；pArg3[9]==1 时用 sub_405400/
//     sub_4053E0 单位圆表按角度分解速度（v6[18]/v6[19]）；
//   · pArg3[10]/[11] 直接给 x/y 抖动（±半幅 + rand）；pArg3[12] 非 0 时按 ±5%×幅度 对
//     v6+12..17 三通道及 +63/+85 做百分比随机缩放（+85 下限 1）。参数块来自粒子配置表。
// ------------------------------------------------------------
int /*cdecl*/ sub_490460(int nArg1, int pArg2, uint32_t *pArg3)  // 实现：粒子发射随机化（被 CNRDParticleCreater__vmt14 转发，broadcast_debug）
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
  (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg1 + 12))(nArg1, pArg2);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
  pArg32 = pArg3;
  v6 = (uint32_t *)v4;
  v7 = pArg3 + 3;
  v8 = 0;
  nRand4 = (int)(pArg3 + 3);
  do  // do-while 循环体起点
  {
    if ( *v7 <= 0 )
    {
      *(float *)&v38[4 * v8 - 4] = 0.0;
    }
    else  // 否则分支
    {
      v9 = *v7;
      nRand = rand() % (v9 + 1) - v9 / 2;  // nRand = 调 rand
      v7 = (int *)nRand4;
      nArg1 = nRand;
      *(float *)&v38[4 * v8 - 4] = (float)nRand;
    }
    ++v8;
    nRand4 = (int)++v7;
  }
  while ( v8 < 3 );  // 条件循环
  sub_52A1A0(v39, v38, pArg32[8]);  // 调 表取角度分量
  sub_52A1A0(&v37, v39, pArg32[7]);  // 调 表取角度分量
  sub_52A1A0(&v37, v38, pArg32[6]);  // 调 表取角度分量
  for ( i = 0; i < 3; ++i )  // 循环：i 从 0 递增到 3
  {
    if ( *(uint8_t *)(pArg2 + 84) == 0 || i != 0 )  // 若 i != 0
      v6[i] += (int)(dword_7930D0[i] * (uint64_t)*(float *)&v38[4 * i - 4]) / 100;
    else  // 否则分支
      *v6 += (int)(dword_7930D0[0] * (uint64_t)v37) / -100;
  }
  v12 = pArg32[9];  // v12 = 取 pArg32[9]
  if ( v12 != 0 )  // 若 v12 非 0
  {
    if ( v12 == 1 )  // 若 v12 == 1
    {
      sub_432FA0();  // srand 播种
      nRand2 = rand() % 360;  // nRand2 = 调 rand
      v6[20] = 90 - nRand2;
      v16 = pArg32[10];  // v16 = 取 pArg32[10]
      nRand4 = nRand2;
      if ( v16 != 0 )  // 若 v16 非 0
      {
        v17 = v16 / 2;
        nRand3 = rand();  // nRand3 = 调 rand
        nArg1 = dword_9A011C + 4 * v17;
        v18 = sub_4D33A0(&nRand3);  // v18 = 调 sub_4D33A0 返回值
        nArg1 = v18 % (*(uint32_t *)nArg1 + 1);
        sub_490410(&v41, dword_9A011C, dword_9A011C + 4 * v17, &nArg1);  // 有序数组二分下界（lower_bound，元素 uint32）
        nRand42 = nRand4;
        nArg1 = (v41 - dword_9A011C) >> 2;
        *(float *)&nArg1 = (float)nArg1;
        v20 = sub_405400(nRand4);  // cos 查表（dword_79D154 表，角度 %360 归一含负角修正）
        v6[18] += (uint64_t)(v20 * *(float *)&nArg1);
        v21 = sub_4053E0(nRand42);  // sin 查表（dword_79D150 表，角度 %360 归一含负角修正）
        v6[19] += (uint64_t)(v21 * *(float *)&nArg1);
      }
    }
  }
  else  // 否则分支
  {
    v13 = pArg32[10];  // v13 = 取 pArg32[10]
    if ( v13 != 0 )  // 若 v13 非 0
    {
      v6[18] += v13 / -2;
      v6[18] += rand() % (pArg32[10] + 1);  // 调 rand（取伪随机数）
    }
    v14 = pArg32[11];  // v14 = 取 pArg32[11]
    if ( v14 != 0 )  // 若 v14 非 0
    {
      v6[19] += v14 / -2;
      v6[19] += rand() % (pArg32[11] + 1);  // 调 rand（取伪随机数）
    }
  }
  result = pArg32[12];  // result = 取 pArg32[12]
  if ( result != 0 )  // 若结果非 0（成功）
  {
    nRand4 = rand() % (10 * pArg32[12] + 1) - 5 * pArg32[12];  // nRand4 = 调 rand
    nRand5 = rand() % (10 * pArg32[12] + 1);  // nRand5 = 调 rand
    v24 = 5 * pArg32[12];
    nArg1 = (int)(v6 + 3);
    v25 = (uint32_t *)((char *)v6 + 15);
    nRand3 = 3;
    v41 = nRand5 - v24;
    do  // do-while 循环体起点
    {
      v26 = *(uint8_t *)nArg1;
      if ( *(uint8_t *)nArg1 == 1 )
      {
        v27 = pArg32[12];  // v27 = 取 pArg32[12]
        nRand6 = rand() % (10 * v27 + 1) - 5 * v27 + 1000;  // nRand6 = 调 rand
        *v25 = nRand6 * *v25 / 1000;
        v29 = nRand6 * v25[1];
        pArg32 = pArg3;
        v25[1] = v29 / 1000;
      }
      else if ( v26 == 2 || v26 == 3 )
      {
        v30 = v41 + 1000;
        *v25 = (nRand4 + 1000) * *v25 / 1000;
        v31 = v25[1];  // v31 = 取 v25[1]
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
    while ( !v33 );  // 条件循环
    v34 = pArg32[12];  // v34 = 取 pArg32[12]
    nRand7 = (uint64_t)(274877907LL * *(uint32_t *)((char *)v6 + 63) * (5 * (200 - v34) + rand() % (10 * v34 + 1))) >> 32;  // 调 rand（取伪随机数）
    result = *(uint32_t *)((char *)v6 + 85);
    *(uint32_t *)((char *)v6 + 63) = (nRand7 >> 6) + ((unsigned int)nRand7 >> 31);
    if ( result != 0 )  // 若结果非 0（成功）
    {
      v36 = pArg32[12];  // v36 = 取 pArg32[12]
      result = *(uint32_t *)((char *)v6 + 85) * (5 * (200 - v36) + rand() % (10 * v36 + 1)) / 1000;  // 调 rand（取伪随机数）
      *(uint32_t *)((char *)v6 + 85) = result;
      if ( result <= 0 )  // 若 result <= 0
        *(uint32_t *)((char *)v6 + 85) = 1;
    }
  }
  return result;
}


// ============================================================
// §B 0x490880-0x491130  动画对象状态基座（+212 同步源 / +216..232 状态位）
// ============================================================
// ------------------------------------------------------------
// 0x490880 sub_490880 —— vector<uint32> 长度溢出兜底（throw std::length_error）
//   字符串证据 vector<T> too long：sub_4015C0 构造 std::string → sub_401740 建异常体 →
//   覆写 vftable 为 std::length_error → _CxxThrowException。noreturn。
// ------------------------------------------------------------
void /*noreturn*/ sub_490880()  // 实现：vector<uint32> 长度溢出兜底（throw std::length_error）
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
  sub_401740(pExceptionObject, &v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x4908F0 sub_4908F0 —— vector<uint32> 内存分配（按元素数 uArg2）
// 0 元素返回 0；>0x3FFFFFFF 走 ·0x490880 抛长度异常；否则 operator new(4*uArg2) 后
//   填 +4 首/+8 尾/+12 容量尾（this 即 3 字段 vector 基址）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4908F0(uint32_t *this, unsigned int uArg2)  // 实现：vector<uint32> 内存分配（按元素数 uArg2）
{
  char *pMem; // eax

  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  if ( uArg2 == 0 )  // 若 uArg2 为 0
    return 0;
  if ( uArg2 > 0x3FFFFFFF )  // 若 uArg2 > 0x3FFFFFFF
    sub_490880(this);  // vector<uint32> 长度溢出兜底（throw std::length_error）
  pMem = (char *)operator new(4 * uArg2);
  *(this + 3) = &pMem[4 * uArg2];  // this+12〔nSkillRec12(推断)〕
  *(this + 1) = pMem;  // this+4〔宿主对象〕
  *(this + 2) = pMem;  // this+8〔nSkillRec8(推断)〕
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x490950 sub_490950 —— vector<uint32> 区间插入（含容量决策三支）
//   被 ·0x490D70（按 1000ms 时间步批量生成对象）在容量不足时调入，插入 1 个对象指针。
//   容量够且尾段可自重叠：sub_55E7F0 右移腾位 + sub_5DAF70 搬尾 + sub_49A9D0 拷入；
//   容量够但尾段不够：sub_55E7F0 平移 + sub_523700 补尾 + sub_49A9D0 回填；
//   容量不足：增长至 max(1.5×, 需用) 后整块换堆。返回插入前 size。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_490950(int this, int Src, unsigned int uArg3, int *pDwArg4)  // 实现：vector<uint32> 区间插入（含容量决策三支）
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

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    result = 0;  // result=this+12 nSkillRec12
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_490880(this);  // vector<uint32> 长度溢出兜底（throw std::length_error）
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( result >= uArg3 + fld_82 )  // result=this+12 nSkillRec12
    {
      fld_83 = *(uint8_t **)(this + 8);  // fld_83 = 读 this+8
      v21 = (int)&fld_83[-Src] >> 2;  // fld_83=this+8 物品 id
      v22 = 4 * uArg3;
      v29 = (int)fld_83;  // fld_83=this+8 物品 id
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )  // 若 v21 >= uArg3
      {
        v24 = (int)&fld_83[-v22];  // fld_83=this+8 物品 id
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 商城状态（10 行）
        sub_5DAF70((void *)Src, v24, v29);  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
      else  // 否则分支
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));  // 商城状态（10 行）
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);  // 调 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_84;  // this+8〔nSkillRec8(推断)〕等 2 字段
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
    }
    else  // 否则分支
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // result=this+12 nSkillRec12
        v10 = (result >> 1) + result;  // result=this+12 nSkillRec12
      else  // 否则分支
        v10 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 非 0
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_85 = 0;  // fld_85=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_85 )  // fld_85=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // 若 fld_4 非 0
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else  // 否则分支
          fld_86 = 0;  // fld_86=this+8 nSkillRec8
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+16〔nChannelTypeSel(推断)〕
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // v15 = 调 sub_523700 返回值
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));  // this+8〔nSkillRec8(推断)〕等 2 字段
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = 读 this+4
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v28];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
      return (unsigned int)pMem;
    }
  }
  return result;  // result=this+12 nSkillRec12
}



// ------------------------------------------------------------
// 0x490B30 sub_490B30 —— vector<uint32> 拷贝构造（源 pArg2 为同构 3 字段 vector）
// size=(+8-+4)>>2，经 ·0x4908F0 分配后 sub_497E70 逐元素搬入，this 即新容器。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_490B30(uint32_t *this, int pArg2)  // 实现：vector<uint32> 拷贝构造（源 pArg2 为同构 3 字段 vector）
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

  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )  // 若 v3 非 0
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
  else  // 否则分支
    v4 = 0;
  if ( sub_4908F0(this, v4) != 0 )  // vector<uint32> 内存分配（按元素数 uArg2）
  {
    fld_e1 = *(this + 1);  // this+4〔宿主对象〕
    v7 = *(uint32_t *)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v6 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);  // uint32 区间逐元素拷贝
  }
  return this;
}



// ------------------------------------------------------------
// 0x490BD0 sub_490BD0 —— ★动画对象重置 + 全局随机刻度表惰性初始化（byte_9A0110 单次）
//   ① this+220/224/228 三槽置 -1（+55..57 索引快照）；
//   ② 首调时构建 dword_9A011C 表：压 0，再对 i=1..180 压 (uint)(sub_4053E0(i)*1000+表[i])
//      —— 三角函数表的毫秒化累积表（容量不足走 sub_430C80 push_back 兜底），末补 0；
//   ③ 尾调自身 vt+88(1) / vt+12(0) 把动画复位到第 0 帧。被 ·0x490D40 与 broadcast_debug 构造链调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_490BD0(uint32_t *this)  // 实现：动画对象重置 + 全局随机刻度表惰性初始化（byte_9A0110 单次）
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
  *(this + 55) = -1;  // this+220〔nSnapDst220(推断)〕
  *(this + 56) = -1;  // this+224〔nSnapDst224(推断)〕
  *(this + 57) = -1;  // this+228〔nSnapDst228(推断)〕
  if ( byte_9A0110 == 0 )  // 若 byte_9A0110 为 0
  {
    v2 = (char *)dword_9A0120;
    v11 = 0;
    if ( dword_9A011C != 0  // 若 dword_9A011C 非 0
      && ((int)dword_9A0120 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )  // ★动画对象重置 + 全局随机刻度表惰性初始化（byte_9A0110 单次）
    {
      *(uint32_t *)dword_9A0120 = 0;
      dword_9A0120 = v2 + 4;
    }
    else  // 否则分支
    {
      sub_430C80(dword_9A0120, 1, (int)&v11);  // uint32 vector 区间插入（同值填充）
    }
    v3 = 0;
    do  // do-while 循环体起点
    {
      v4 = v3 + 1;
      v5 = (int *)(dword_9A011C + 4 * v3);
      v6 = (uint64_t)(sub_4053E0(v3 + 1) * 1000.0 + (double)*v5);  // sin 查表（dword_79D150 表，角度 %360 归一含负角修正）
      v7 = (char *)dword_9A0120;
      v11 = v6;
      if ( dword_9A011C != 0  // 若 dword_9A011C 非 0
        && ((int)dword_9A0120 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )
      {
        dword_9A01202 = (char *)dword_9A0120 + 4;
        *(uint32_t *)dword_9A0120 = v6;
        dword_9A0120 = v7 + 4;
      }
      else  // 否则分支
      {
        sub_430C80(dword_9A0120, 1, (int)&v11);  // uint32 vector 区间插入（同值填充）
        dword_9A01202 = dword_9A0120;
      }
      v3 = v4;
    }
    while ( v4 < 180 );  // 条件循环
    v11 = 0;
    if ( dword_9A011C != 0 && ((int)dword_9A01202 - dword_9A011C) >> 2 < (unsigned int)((dword_9A0124 - dword_9A011C) >> 2) )  // 若 dword_9A011C != 0
    {
      *dword_9A01202 = 0;
      dword_9A0120 = dword_9A01202 + 1;
    }
    else  // 否则分支
    {
      sub_430C80(dword_9A01202, 1, (int)&v11);  // uint32 vector 区间插入（同值填充）
    }
    pThis = this;
    byte_9A0110 = 1;
  }
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*pThis + 88))(pThis, 1);  // 调虚槽 +88：CNRDPrivateStoreWindow__vmt58 槽（16 行）
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis + 12))(pThis, 0);  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
}



// ------------------------------------------------------------
// 0x490D40 sub_490D40 —— 重置包装：先 vt+4(nArg2,nArg3) 配置，再 ·0x490BD0 复位
// 与 ·0x4902C0 状态清零族同构，额外带一次 vtable 配置下发。
// ------------------------------------------------------------
int /*thiscall*/ sub_490D40(uint32_t *this, int nArg2, int nArg3)  // 实现：重置包装：先 vt+4(nArg2,nArg3) 配置，再 ·0x490BD0 复位
{
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 4))(this, nArg2, nArg3);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  return sub_490BD0(this);  // 动画对象重置 + 全局随机刻度表惰性初始化（byte_9A0110 单次）
}



// ------------------------------------------------------------
// 0x490D70 sub_490D70 —— 按时间步(1000ms)批量生成对象
//   速率因子 = 浮点字段 +26（-1.0f=0xBF800000 哨兵=不限）；+55..57 目标 ←
//   sub_4049C0(旧值+1..3, 新值, 步进) 逐格插值；+53 记录已完成步数。
// ------------------------------------------------------------
int /*thiscall*/ sub_490D70(uint32_t *this, int nArg2)  // 实现：按时间步(1000ms)批量生成对象
{
  int pThis_2C; // edi
  int fld_e51; // ecx  | +0x00CC → 子动画链指针（0x490370：*(this+204) = nArg2 子链挂接）（证据: va=00490370）（CNRDParticleCreater；va=00490370）
  void *v5; // edi
  char pThis_D8; // al
  int v7; // eax
  int v8; // eax
  int fld_e28; // eax
  int pThis_1A; // ecx
  int fld_e272; // eax
  int fld_e53; // ebx  | +0x00D4 → 子链状态槽（0x490370 清 0）【推断】（证据: va=00490370）（CNRDParticleCreater；va=00490370）
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
  int fld_e532; // eax  | +0x00D4 → 子链状态槽（0x490370 清 0）【推断】（证据: va=00490370）（CNRDParticleCreater；va=00490370）
  int v24; // ebx
  int v25; // eax
  int v26; // ecx
  char *v27; // eax
  int fld_e2; // ecx  | +0x0008 → 快照源值 B（0x490370：写入 +224）（证据: va=00490370）（CNRDParticleCreater；va=00490370）
  int fld_e3; // edx  | +0x000C → 快照源值 C（0x490370：写入 +228）（证据: va=00490370）（CNRDParticleCreater；va=00490370）
  int nArg22; // esi
  float v32; // [esp+Ch] [ebp-60h]
  float v33; // [esp+10h] [ebp-5Ch]
  int fld_e27; // [esp+18h] [ebp-54h]
  int fld_e26; // [esp+18h] [ebp-54h]  | +0x0068 → 参数块起址（CNRDParticleCreater；va=00425230）
  int fld_e46; // [esp+18h] [ebp-54h]
  int fld_e533; // [esp+18h] [ebp-54h]  | +0x00D4 → 子链状态槽（0x490370 清 0）【推断】（证据: va=00490370）（CNRDParticleCreater；va=00490370）
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
  int fld_e52; // [esp+5Ch] [ebp-10h]  | +0x00D0 → 子链状态槽（0x490370 清 0）【推断】（证据: va=00490370）（CNRDParticleCreater；va=00490370）
  int v52; // [esp+68h] [ebp-4h]

  pThis_2C = (int)(this + 44);  // this+176〔pAppendVecCap(推断)〕
  pObj2 = 0;
  sub_698F90((int)(this + 44), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_e51 = sub_699000(pThis_2C) + *(this + 51);  // 【clock_now(clk)】
  v5 = nullptr;  // v5 = 空指针
  *(this + 52) = fld_e51;  // this+208〔nField208(推断)〕
  v39 = nullptr;  // v39 = 空指针
  Src = nullptr;  // Src = 空指针
  v41 = 0;
  pThis_D8 = *((uint8_t *)this + 216);  // this+216〔bField216(推断)〕
  v52 = 0;
  if ( pThis_D8 != 0 )  // 若 pThis_D8 非 0
    goto LABEL_39;
  if ( *(this + 58) == -1 )  // this+232〔bSyncFlag〕
    *(this + 58) = dword_9A0114;  // this+232〔bSyncFlag〕
  if ( *((float *)this + 26) == 0.0 || *(this + *(this + 58) + 40) == 0 )  // 复合条件判定（与/或）
  {
    *((uint8_t *)this + 216) = 1;  // this[216] = 1
LABEL_39:  // 标签 LABEL_39（跳转合流点）
    nArg22 = nArg2;
    sub_490B30(v38);  // vector<uint32> 拷贝构造（源 pArg2 为同构 3 字段 vector）
    return nArg22;
  }
  if ( *(this + 26) == -1082130432 )  // this+104〔nTimerEnd(推断)〕
  {
    v7 = *this;
    fld_e27 = *(this + 27);  // this+108〔nAdd108(推断)〕
    *((uint8_t *)this + 216) = 1;  // this[216] = 1
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 84))(this, fld_e27);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
  }
  else  // 否则分支
  {
    fld_e28 = *(this + 28);  // this+112〔pHostComp112〕
    fld_e512 = fld_e51;
    if ( fld_e28 > 0 && fld_e51 >= fld_e28 )  // 若 fld_e28 > 0 与/或 fld_e51 >= fld_e28
    {
      *((uint8_t *)this + 216) = 1;  // this[216] = 1
      fld_e512 = fld_e28;  // fld_e28=this+112 pHostComp112
    }
    pThis_1A = 1 - (uint64_t)((double)fld_e512 * *((float *)this + 26) * -0.001);
    fld_e272 = *(this + 27);  // this+108〔nAdd108(推断)〕
    if ( fld_e272 != 0 && pThis_1A >= fld_e272 )  // 若 fld_e272 != 0 与/或 pThis_1A >= fld_e272
    {
      *((uint8_t *)this + 216) = 1;  // this[216] = 1
      pThis_1A = fld_e272;  // fld_e272=this+108 nAdd108
    }
    v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 84))(this, pThis_1A);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
  }
  fld_e53 = *(this + 53);  // this+212〔nField212(推断)〕
  v50 = v8;
  fld_e534 = fld_e53;  // fld_e53=this+212 nField212
  if ( fld_e53 < v8 )  // 若 fld_e53 < v8
  {
    fld_e512 = 1000 * fld_e53;  // fld_e53=this+212 nField212
    do  // do-while 循环体起点
    {
      pThis_1A2 = *((float *)this + 26);  // this+104〔nTimerEnd(推断)〕
      pObj = 0;
      fld_e52 = 0;
      if ( pThis_1A2 <= 0.0 )  // pThis_1A2=this+104 nTimerEnd
      {
        if ( *(this + 26) == -1082130432 )  // this+104〔nTimerEnd(推断)〕
          fld_e52 = *(this + 52);  // this+208〔nField208(推断)〕
      }
      else  // 否则分支
      {
        v15 = *this;
        fld_e26 = *(this + 26);  // this+104〔nTimerEnd(推断)〕
        *(float *)&v47 = (float)fld_e512;
        v16 = ((double (/*thiscall*/ *)(uint32_t *, int))*(uint32_t *)(v15 + 80))(this, fld_e26);  // fld_e26=this+104 nTimerEnd
        fld_e52 = *(this + 52) - (uint64_t)(*(float *)&v47 / v16);  // this+208〔nField208(推断)〕
      }
      pThis_59 = *(uint32_t *)((char *)this + 89);  // this+89〔nLifetime〕
      if ( pThis_59 == 0 || pThis_59 > fld_e52 )  // 若 pThis_59 == 0 与/或 pThis_59 > fld_e52
      {
        v18 = sub_445D00(156);  // CRT 一次性池初始化（池 &unk_97B6D4）
        pObj2 = v18;
        LOBYTE(v52) = 1;
        if ( v18 != 0 )  // 若 v18 非 0
          pObj = sub_445B90(v18);  // CNRDParticle 构造
        v19 = *(uint32_t *)pObj;
        fld_e46 = *(this + 46);  // this+184〔bSingleTarget(推断)〕
        LOBYTE(v52) = 0;
        pObj2 = pObj;
        (*(void (/*thiscall*/ **)(int, int))(v19 + 68))(pObj, fld_e46);  // 调虚槽 +68：CNRDPrivateStoreWindow__vmt44 槽（484880 + 5441B0 …
        (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 20))(this, pObj);  // 调虚槽 +20：CNRDPrivateStoreItemBuyConfirmWindow__vmt14 确认…
        if ( *((uint8_t *)this + 156) != 0 )  // this+156〔nAdd156(推断)〕
        {
          pThis_37 = this + 55;
          pThis_372 = this + 55;
          v43 = -220 - (uint32_t)this;
          v47 = 3;
          do  // do-while 循环体起点
          {
            v21 = *pThis_37;
            v22 = *pThis_37 == *(pThis_37 - 54);
            v45 = *(pThis_37 - 54);
            if ( !v22 )
            {
              fld_e532 = fld_e53 - *(this + 53) + 1;  // this+212〔nField212(推断)〕
              fld_e533 = v50 - *(this + 53);  // this+212〔nField212(推断)〕
              v44 = v21;
              v33 = (float)v45;
              v32 = (float)v21;
              v24 = (uint64_t)sub_4049C0(v32, v33, fld_e532, fld_e533);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
              v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
              v26 = v43 + v25;
              pThis_37 = pThis_372;
              *(int *)((char *)pThis_372 + v26) = v24;
              fld_e53 = fld_e534;  // fld_e53=this+212 nField212
            }
            ++pThis_37;
            v22 = v47 == 1;
            pThis_372 = pThis_37;
            --v47;
          }
          while ( !v22 );  // 条件循环
        }
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, fld_e52);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
        if ( v39 != nullptr && ((uint8_t *)Src - v39) >> 2 < (unsigned int)((v41 - (int)v39) >> 2) )  // 若 v39 != nullptr
        {
          v27 = (char *)Src;
          *(uint32_t *)Src = pObj;  // *Src = pObj
          Src = v27 + 4;
        }
        else  // 否则分支
        {
          sub_490950(Src, 1, (int)&pObj2);  // vector<uint32> 区间插入（含容量决策三支）
        }
      }
      v8 = v50;
      fld_e534 = ++fld_e53;  // fld_e53=this+212 nField212
      fld_e512 += 1000;
    }
    while ( fld_e53 < v50 );  // 条件循环
    v5 = v39;
  }
  *(this + 53) = v8;  // this+212〔nField212(推断)〕
  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  *(this + 55) = *(this + 1);  // this+220〔nSnapDst220(推断)〕等 2 字段
  *(this + 56) = fld_e2;  // this+224〔nSnapDst224(推断)〕
  *(this + 57) = fld_e3;  // this+228〔nSnapDst228(推断)〕
  nArg22 = nArg2;
  sub_490B30(v38);  // vector<uint32> 拷贝构造（源 pArg2 为同构 3 字段 vector）
  if ( v5 != nullptr )  // 若 v5 有效（非空）
    j__free(v5);  // 调 j__free（堆释放）
  return nArg22;
}


// ------------------------------------------------------------
// 0x4910A0 sub_4910A0 —— 沿 +212 同步源链上溯，返回链尾对象的累计播放时刻（+32）
//   链尾即无同步源的根动画；帧推进 ·0x493840 用它取时间基准。
//   与 ·0x4910C0（同链取 +169 暂停位）同构，仅取样字段不同。
// ------------------------------------------------------------
int /*fastcall*/ sub_4910A0(int pArg1)  // 实现：沿 +212 同步源链上溯，返回链尾对象的累计播放时刻（+32）
{
  int pArg12; // eax

  do  // do-while 循环体起点
  {
    pArg12 = pArg1;
    pArg1 = *(uint32_t *)(pArg1 + 212);  // pArg1+212〔nField212(推断)〕
  }
  while ( pArg1 != 0 );  // 条件循环
  return *(uint32_t *)(pArg12 + 32);  // pArg12+32〔nHeight(推断)〕
}



// ------------------------------------------------------------
// 0x4910C0 sub_4910C0 —— 沿 +212 同步源链上溯，返回链尾对象的 +169（暂停/冻结位）
//   与 ·0x4910A0 同构；调用方 ·0x4910E0 用它决定是否还刷新时间。
// ------------------------------------------------------------
char /*fastcall*/ sub_4910C0(int pArg1)  // 实现：沿 +212 同步源链上溯，返回链尾对象的 +169（暂停/冻结位）
{
  int pArg12; // eax

  do  // do-while 循环体起点
  {
    pArg12 = pArg1;
    pArg1 = *(uint32_t *)(pArg1 + 212);  // pArg1+212〔nField212(推断)〕
  }
  while ( pArg1 != 0 );  // 条件循环
  return *(uint8_t *)(pArg12 + 169);
}



// ------------------------------------------------------------
// 0x4910E0 sub_4910E0 —— 帧时刻推进（返回 1 表示时刻发生位移）
//   ① +168 置 1（已启动）；② sub_698F90(this,0,0) = clock_set_countdown(clk,0,0) 复位本对象时钟；
//   ③ 基准暂停位：有 +212 同步源沿链问 ·0x4910C0，否则取自身 +169；
//   ④ 时刻 = +28 起点 + clock_now(this)（sub_699000），与 +32 不同才写回并返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4910E0(int this)  // 实现：帧时刻推进（返回 1 表示时刻发生位移）
{
  int fld_D4; // ecx
  char fld_A9; // al
  int fld_1C; // eax

  *(uint8_t *)(this + 168) = 1;  // this+168〔pAppendVec(推断)〕等 2 字段
  sub_698F90(this, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_D4 = *(uint32_t *)(this + 212);  // fld_D4 = 读 this+212
  if ( fld_D4 != 0 )  // 若 fld_D4 非 0
    fld_A9 = sub_4910C0(fld_D4);  // 沿 +212 同步源链上溯，返回链尾对象的 +169（暂停/冻结位）
  else  // 否则分支
    fld_A9 = *(uint8_t *)(this + 169);  // fld_A9 = 读 this+169
  if ( fld_A9 != 0 )  // 若 fld_A9 非 0
    return 0;
  fld_1C = *(uint32_t *)(this + 28) + sub_699000(this);  // 【clock_now(clk)】
  if ( fld_1C == *(uint32_t *)(this + 32) )  // this+32〔nHeight(推断)〕等 2 字段
    return 0;
  *(uint32_t *)(this + 32) = fld_1C;  // this+32〔nHeight(推断)〕等 2 字段
  return 1;  // 返回 1(成功)
}



// ============================================================
// §C 0x491130-0x4919D0  帧渲染/图层属性族（sub_4049C0 插值、图层 +40..+56）
// ============================================================
// ------------------------------------------------------------
// 0x491130 sub_491130 —— ★AABB 包围盒相交测试（6 float 盒：[x,y,z,w,h,d]）
//   任一轴半径 w/h/d 为 0 → 视为无效盒返回 0；三轴分离即不相交返回 0；
//   相交且 pArg3 非空时输出交集盒（min 取大、尺寸 = 双上界的小者 - min 下界）。
//   研究 P29 族：IRDCollisionObject / hiteff_monster 用它对攻击盒与受击盒世界坐标求交。
// ------------------------------------------------------------
char /*cdecl*/ sub_491130(float *pArg1, float *pArg2, float *pArg3)  // 实现：AABB 包围盒相交测试（6 float 盒：）
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
  if ( pArg3 != nullptr )  // 若 pArg3 有效（非空）
  {
    if ( *pArg1 <= (double)*pArg2 )
      v4 = *pArg2;
    else  // 否则分支
      v4 = *pArg1;
    *pArg3 = v4;
    v5 = *pArg1 + pArg1[3];
    v11 = *pArg2 + pArg2[3];
    if ( v5 >= v11 )  // 若 v5 >= v11
      v5 = v11;
    pArg3[3] = v5 - v4;
    if ( pArg1[1] <= (double)pArg2[1] )
      v6 = pArg2[1];  // v6 = 取 pArg2[1]
    else  // 否则分支
      v6 = pArg1[1];  // v6 = 取 pArg1[1]
    pArg3[1] = v6;
    v7 = pArg1[4] + pArg1[1];
    v12 = pArg2[4] + pArg2[1];
    if ( v7 >= v12 )  // 若 v7 >= v12
      v7 = v12;
    pArg3[4] = v7 - v6;
    if ( pArg1[2] <= (double)pArg2[2] )
      v8 = pArg2[2];  // v8 = 取 pArg2[2]
    else  // 否则分支
      v8 = pArg1[2];  // v8 = 取 pArg1[2]
    pArg3[2] = v8;
    v9 = pArg1[2] + pArg1[5];
    v13 = pArg2[2] + pArg2[5];
    if ( v9 >= v13 )  // 若 v9 >= v13
      v9 = v13;
    pArg3[5] = v9 - v8;
  }
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x491300 sub_491300 —— 帧图像绘制
//   帧(a6)：+0 句柄 /+4 路径id /+8 资源id /+12,+16 位置 /+20,+24 缩放 /+28 旋转 /+35 A通道。
//   a10 ms 内 alpha 0→帧+35 淡入（sub_4049C0）；+161 阴影分支；a8 翻转；a9 纵向缩放。
// ------------------------------------------------------------
void /*thiscall*/ sub_491300(uint8_t *this, int nArg2, int nArg3, int nArg4, float fArg5, int pArg6, int nArg7, float fArg8, float fArg9, int nArg10)  // 实现：帧图像绘制
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

  v10 = *(uint32_t *)(pArg6 + 4);  // pArg6+4〔宿主对象〕
  if ( v10 != -1 )
  {
    v31 = *(uint32_t *)(pArg6 + 8);  // pArg6+8〔nSkillRec8(推断)〕
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v10);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    *(uint32_t *)pArg6 = sub_418DD0(v31);  // *pArg6 = 调 sub_418DD0 返回值
  }
  if ( byte_790AD0 != 0 && *(this + 161) != 0 && *(uint32_t *)pArg6 != 0 )  // this+644〔uHitBoxSnap644〕
  {
    v25 = (float)nArg10;
    v12 = (uint64_t)sub_4049C0(0.0, v25, *(uint8_t *)(pArg6 + 35), 255);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    if ( dword_9A012C == 0 )  // 若 dword_9A012C 为 0
    {
      if ( LOBYTE(fArg5) != 0 )
      {
        v32 = *(float *)(pArg6 + 28) - fArg8;  // pArg6+28〔pPanelVec(推断)〕
        v35 = -*(float *)(pArg6 + 20);  // pArg6+20〔nPage(推断)〕
      }
      else  // 否则分支
      {
        v13 = fArg8 + *(float *)(pArg6 + 28);  // pArg6+28〔pPanelVec(推断)〕
        v35 = *(float *)(pArg6 + 20);  // pArg6+20〔nPage(推断)〕
        v32 = v13;
      }
      v14 = *(uint32_t *)(pArg6 + 16);  // pArg6+16〔nChannelTypeSel(推断)〕
      v15 = *(uint32_t *)(pArg6 + 12);  // pArg6+12〔nSkillRec12(推断)〕
      v29 = (float)-v14;
      v27 = (float)-v15;
      v26 = (uint8_t)v12 << 24;
      v23 = v32;
      v16 = v35;
LABEL_21:  // 标签 LABEL_21（跳转合流点）
      *(float *)&v22 = fArg9 * *(float *)(pArg6 + 24);  // pArg6+24〔nPageMax(推断)〕
      sub_424760(  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
        dword_79C0B0,  // 默认字体/绘制资源
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
    if ( dword_9A012C != 1 )  // 若 dword_9A012C != 1
    {
      if ( dword_9A012C != 2 )  // 若 dword_9A012C != 2
        return;
      if ( LOBYTE(fArg5) != 0 )
      {
        v34 = *(float *)(pArg6 + 28) - fArg8;  // pArg6+28〔pPanelVec(推断)〕
        v36 = -*(float *)(pArg6 + 20);  // pArg6+20〔nPage(推断)〕
      }
      else  // 否则分支
      {
        v21 = fArg8 + *(float *)(pArg6 + 28);  // pArg6+28〔pPanelVec(推断)〕
        v36 = *(float *)(pArg6 + 20);  // pArg6+20〔nPage(推断)〕
        v34 = v21;
      }
      v14 = *(uint32_t *)(pArg6 + 16);  // pArg6+16〔nChannelTypeSel(推断)〕
      v15 = *(uint32_t *)(pArg6 + 12);  // pArg6+12〔nSkillRec12(推断)〕
      v29 = (float)-v14;
      v27 = (float)-v15;
      v26 = -16777216;
      v23 = v34;
      v16 = v36;
      goto LABEL_21;
    }
    v17 = *(float *)(pArg6 + 28);  // pArg6+28〔pPanelVec(推断)〕
    v18 = (v12 - 50) & (((int)v12 - 50 < 0) - 1);
    if ( LOBYTE(fArg5) != 0 )
    {
      v19 = v17 - 3.14;
      v33 = *(float *)(pArg6 + 20);  // pArg6+20〔nPage(推断)〕
    }
    else  // 否则分支
    {
      v19 = v17 + 3.14;
      v33 = -*(float *)(pArg6 + 20);  // pArg6+20〔nPage(推断)〕
    }
    v20 = *(uint32_t *)(pArg6 + 12);  // pArg6+12〔nSkillRec12(推断)〕
    v30 = (float)-*(uint32_t *)(pArg6 + 16);  // pArg6+16〔nChannelTypeSel(推断)〕
    v28 = (float)-v20;
    v24 = v19;
    sub_424760(  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      dword_79C0B0,  // 默认字体/绘制资源
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
// 0x491530 sub_491530 —— 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
//   nArg1=1..4 把渲染器槽 19/20 设为固定模式对（19=9&20=5 / 5&2 / 4&6 / 10&1）；
//   nArg1=5 槽 60 写 RGBA 通道重排后的 nArg2（RRGGBB 交换），再用 vt+36 设 3/1 号屏映射。
//   被 CNRDObject 等以 sub_491530(2,0) 形式调用（渲染状态应用），与 ·0x491630 成对。
// ------------------------------------------------------------
int /*cdecl*/ sub_491530(int nArg1, int nArg2)  // 实现：渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
{
  int result; // eax

  result = nArg1 - 1;
  switch ( nArg1 )  // 按 nArg1 分派
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 9);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 5);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      break;  // 跳出循环/分支
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 5);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 2);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      break;  // 跳出循环/分支
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 4);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 6);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 10);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      result = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 1);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      (*(void (/*thiscall*/ **)(int, int, unsigned int))(*(uint32_t *)dword_79C0A4 + 28))(  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
        dword_79C0A4,  // dword_79C0A4（全局渲染器对象）
        60,
        nArg2 & 0xFF00FF00 | ((uint8_t)nArg2 << 16) | BYTE2(nArg2));
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 3);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      result = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 3);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      break;  // 跳出循环/分支
    default:  // 默认分支
      return result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x491630 sub_491630 —— 渲染层状态还原（与 ·0x491530 配对）
//   nArg1=1..4 恢复槽 19=5/20=6；nArg1=5 用 vt+36 把 3/1 号屏映射设为 1/4。
//   CNRDObject 以 sub_491630(2) 成对调用。
// ------------------------------------------------------------
int /*cdecl*/ sub_491630(int nArg1)  // 实现：渲染层状态还原（与 ·0x491530 配对）
{
  int result; // eax

  result = nArg1;
  if ( nArg1 > 0 )  // 若 nArg1 > 0
  {
    if ( nArg1 <= 4 )  // 若 nArg1 <= 4
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 19, 5);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_79C0A4 + 28))(dword_79C0A4, 20, 6);  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
    }
    else if ( nArg1 == 5 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 1);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      return (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 4);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x491690 sub_491690 —— 图层后处理配置（this+176..196 图层参数块写入）
// +176 总开关（0 时整块不落地）；+180 STENCIL 模式 id、+184 标志、+188/+192 参数、
//   +196 一次性标志（渲染后由 ·0x491D00 自清）。
// ------------------------------------------------------------
char /*thiscall*/ sub_491690(int this, char pszArg2, int nArg3, char pszArg4, int nArg5, int nArg6, char pszArg7)  // 实现：图层后处理配置（this+176..196 图层参数块写入）
{
  char result; // al

  result = pszArg2;
  *(uint8_t *)(this + 176) = pszArg2;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
  {
    *(uint32_t *)(this + 180) = nArg3;  // this+180〔nRadius(推断)〕
    *(uint8_t *)(this + 184) = pszArg4;  // this+184〔bSingleTarget(推断)〕
    *(uint32_t *)(this + 188) = nArg5;  // this+188〔nStatusIdx(推断)〕
    *(uint32_t *)(this + 192) = nArg6;  // this+192〔nDlgId(推断)〕
    *(uint8_t *)(this + 196) = pszArg7;
    return pszArg7;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4916E0 sub_4916E0 —— 图层属性下发（帧 +40 特效/+44 参数色 → 渲染态，sub_424760 提交）
// ------------------------------------------------------------
int /*stdcall*/ sub_4916E0(int nArg1, int nArg2, int nArg3, float fArg4, int pArg5)  // 实现：图层属性下发（帧 +40 特效/+44 参数色 → 渲染态，sub_424760 提交）
{
  int result; // eax
  int v6; // ecx
  float v7; // [esp+4h] [ebp-Ch]
  int v8; // [esp+8h] [ebp-8h]
  float v9; // [esp+8h] [ebp-8h]
  float v10; // [esp+24h] [ebp+14h]

  result = *(uint32_t *)(pArg5 + 4);  // pArg5+4〔宿主对象〕
  if ( result != -1 )
  {
    v8 = *(uint32_t *)(pArg5 + 8);  // pArg5+8〔nSkillRec8(推断)〕
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, result);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    result = sub_418DD0(v8);  // result = 调 sub_418DD0 返回值
    *(uint32_t *)pArg5 = result;
  }
  if ( *(uint32_t *)pArg5 != 0 )
  {
    sub_491530(*(uint32_t *)(pArg5 + 40), *(uint32_t *)(pArg5 + 44));  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    if ( LOBYTE(fArg4) != 0 )
      v10 = -*(float *)(pArg5 + 20);  // pArg5+20〔nPage(推断)〕
    else  // 否则分支
      v10 = *(float *)(pArg5 + 20);  // pArg5+20〔nPage(推断)〕
    v6 = *(uint32_t *)(pArg5 + 12);  // pArg5+12〔nSkillRec12(推断)〕
    v9 = (float)-*(uint32_t *)(pArg5 + 16);  // pArg5+16〔nChannelTypeSel(推断)〕
    v7 = (float)-v6;
    sub_424760(  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      dword_79C0B0,  // 默认字体/绘制资源
      nArg2 + v6,
      nArg3 + *(uint32_t *)(pArg5 + 16),
      *(uint32_t *)pArg5,
      v10,
      *(uint32_t *)(pArg5 + 24),
      *(float *)(pArg5 + 28),
      *(uint32_t *)(pArg5 + 32),
      v7,
      v9);
    return sub_491630(*(uint32_t *)(pArg5 + 40));  // 渲染层状态还原（与 ·0x491530 配对）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4917A0 sub_4917A0 —— 图层属性下发·STENCIL 分支（dword_79C0A4 vtable+28/+36；RGBA 重排）
// ------------------------------------------------------------
char /*stdcall*/ sub_4917A0(int nArg1, int nArg2, int nArg3, float fArg4, int pArg5, int nArg6, char pszArg7, int nArg8, int nArg9)  // 实现：图层属性下发·STENCIL 分支（dword_79C0A4 vtable+28/+36；RGBA 重排）
{
  int v9; // eax
  int nArg62; // edi
  int v11; // ecx
  float v13; // [esp+24h] [ebp-10h]
  float v14; // [esp+28h] [ebp-Ch]
  int v15; // [esp+2Ch] [ebp-8h]
  float v16; // [esp+48h] [ebp+14h]

  v9 = *(uint32_t *)(pArg5 + 4);  // pArg5+4〔宿主对象〕
  if ( v9 != -1 )
  {
    v15 = *(uint32_t *)(pArg5 + 8);  // pArg5+8〔nSkillRec8(推断)〕
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v9);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    v9 = sub_418DD0(v15);  // v9 = 调 sub_418DD0 返回值
    *(uint32_t *)pArg5 = v9;  // *pArg5 = v9
  }
  if ( *(uint32_t *)pArg5 != 0 )
  {
    nArg62 = nArg6;
    if ( nArg6 != 0 )  // 若 nArg6 非 0
      sub_491530(nArg6, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    if ( pszArg7 != 0 )  // 若 pszArg7 非 0
    {
      (*(void (/*thiscall*/ **)(int, int, unsigned int))(*(uint32_t *)dword_79C0A4 + 28))(  // 调虚槽 +28：CNFollowMe__vmt1C 生成装配：Character/Mage/Effect/A…
        dword_79C0A4,  // dword_79C0A4（全局渲染器对象）
        60,
        nArg8 & 0xFF00FF00 | ((uint8_t)nArg8 << 16) | BYTE2(nArg8));
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 3);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 3);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      nArg62 = nArg6;
    }
    if ( LOBYTE(fArg4) != 0 )
      v16 = -*(float *)(pArg5 + 20);  // pArg5+20〔nPage(推断)〕
    else  // 否则分支
      v16 = *(float *)(pArg5 + 20);  // pArg5+20〔nPage(推断)〕
    v11 = *(uint32_t *)(pArg5 + 12);  // pArg5+12〔nSkillRec12(推断)〕
    v14 = (float)-*(uint32_t *)(pArg5 + 16);  // pArg5+16〔nChannelTypeSel(推断)〕
    v13 = (float)-v11;
    sub_424760(  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
      dword_79C0B0,  // 默认字体/绘制资源
      nArg2 + v11,
      nArg3 + *(uint32_t *)(pArg5 + 16),
      *(uint32_t *)pArg5,
      v16,
      *(uint32_t *)(pArg5 + 24),
      *(float *)(pArg5 + 28),
      nArg9,
      v13,
      v14);
    if ( nArg62 != 0 )  // 若 nArg62 非 0
      sub_491630(nArg62);  // 渲染层状态还原（与 ·0x491530 配对）
    LOBYTE(v9) = pszArg7;
    if ( pszArg7 != 0 )  // 若 pszArg7 非 0
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 3, 1);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      LOBYTE(v9) = (*(int (/*thiscall*/ **)(int, uint32_t, int, int))(*(uint32_t *)dword_79C0A4 + 36))(dword_79C0A4, 0, 1, 4);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
    }
  }
  return v9;
}



// ------------------------------------------------------------
// 0x4918E0 sub_4918E0 —— 动画盒四边界提取（研究 P29 族）
//   pDwArg1 = 描述块：+0 图像对象、+4 图像id(-1 忽略)、+8 资源id、+12/+16 锚点、
//   +20/+24 比例(float，1065353216=1.0f 时跳过缩放)。nArg2 取边：0=左 -(锚x+图宽)、
//   1=右、2=上 -(锚y+图高)、3=下；返回该边像素坐标（负号即左/上侧）。
//   被 IRDCollisionObject 用于攻击盒/受击盒的屏幕边界换算。
// ------------------------------------------------------------
int /*cdecl*/ sub_4918E0(int *pDwArg1, int nArg2)  // 实现：动画盒四边界提取（研究 P29 族）
{
  int v2; // eax
  uint32_t *v3; // eax
  uint64_t v4; // rax
  unsigned int v6; // [esp-4h] [ebp-8h]

  if ( pDwArg1 != nullptr && *pDwArg1 != 0 )  // 若 pDwArg1 != nullptr
  {
    v2 = pDwArg1[1];  // v2 = 取 pDwArg1[1]
    if ( v2 != -1 )
    {
      v6 = pDwArg1[2];  // v6 = 取 pDwArg1[2]
      v3 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v2);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      *pDwArg1 = sub_418DD0(v3, v6);  // 调 资源句柄 (101)
    }
    LODWORD(v4) = 0;
    switch ( nArg2 )  // 按 nArg2 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        LODWORD(v4) = -(pDwArg1[3] + *(uint32_t *)(*pDwArg1 + 28));
        goto LABEL_7;
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        LODWORD(v4) = pDwArg1[3] + *(uint32_t *)(*pDwArg1 + 20) + *(uint32_t *)(*pDwArg1 + 28);
LABEL_7:  // 标签 LABEL_7（跳转合流点）
        if ( pDwArg1[5] != 1065353216 )  // 常量 1.0f
          return (uint64_t)((double)(int)v4 * *((float *)pDwArg1 + 5));
        return v4;
      case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
        LODWORD(v4) = -(pDwArg1[4] + *(uint32_t *)(*pDwArg1 + 32));
        goto LABEL_12;
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        LODWORD(v4) = pDwArg1[4] + *(uint32_t *)(*pDwArg1 + 24) + *(uint32_t *)(*pDwArg1 + 32);
LABEL_12:  // 标签 LABEL_12（跳转合流点）
        if ( pDwArg1[6] != 1065353216 )  // 常量 1.0f
          v4 = (uint64_t)((double)(int)v4 * *((float *)pDwArg1 + 6));
        break;  // 跳出循环/分支
      default:  // 默认分支
        return v4;
    }
  }
  else  // 否则分支
  {
    LODWORD(v4) = 0;
  }
  return v4;
}



// ------------------------------------------------------------
// 0x4919B0 sub_4919B0 —— 转发 sub_48C4B0（24 字节元素区间深拷贝，6 dword 一组）
//   盒 vector 复制族一环，被 ·0x492E80 缩容分支调用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4919B0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：转发 sub_48C4B0（24 字节元素区间深拷贝，6 dword 一组）
{
  return sub_48C4B0(uArg1, uArg2, uArg3);  // 24 字节元素区间拷贝（6 dword 一组）
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
char /*thiscall*/ sub_4919D0(int this)  // 实现：帧间插值核心（研究§11/§26）
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

  LOBYTE(fld_94) = *(uint8_t *)(this + 96);  // this+96〔nStatusMode(推断)〕等 2 字段
  if ( (uint8_t)fld_94 != 0 )
  {
    fld_2C = *(uint32_t *)(this + 44);  // fld_2C = 读 this+44
    if ( fld_2C != 0 )  // 若 fld_2C 非 0
      fld_30 = (*(uint32_t *)(this + 48) - fld_2C) / 88;  // 帧数 = (帧数组尾+48 - 首+44)/88
    else  // 否则分支
      fld_30 = 0;
    fld_94 = *(uint32_t *)(this + 148);  // 当前帧索引
    if ( fld_94 == fld_30 - 1 )  // fld_94=this+148 第 4 组·+802 增量子倍率
    {
      if ( *(uint8_t *)(this + 160) == 0 )  // 尾帧无[LOOP]则停住
        return fld_94;  // fld_94=this+148 第 4 组·+802 增量子倍率
      fld_2C2 = *(uint32_t *)(this + 44);  // fld_2C2 = 读 this+44
      fld_2C22 = fld_2C2;  // fld_2C2=this+44 剩余时间 ms
    }
    else  // 否则分支
    {
      fld_2C2 = *(uint32_t *)(this + 44);  // fld_2C2 = 读 this+44
      fld_2C22 = fld_2C2 + 88 * (fld_94 + 1);  // 下一帧（步长88）
    }
    v7 = fld_2C2 + 88 * fld_94;  // fld_2C2=this+44 剩余时间 ms
    fld_D4 = *(uint32_t *)(this + 212);  // fld_D4 = 读 this+212
    v36 = v7;
    if ( fld_D4 != 0 )  // 若 fld_D4 非 0
      fld_20 = sub_4910A0(fld_D4);  // 沿 +212 同步源链上溯，返回链尾对象的累计播放时刻（+32）
    else  // 否则分支
      fld_20 = *(uint32_t *)(this + 32);  // fld_20 = 读 this+32
    fld_98 = *(uint32_t *)(this + 152);  // fld_98 = 读 this+152
    fld_9C = *(uint32_t *)(this + 156) - fld_98;  // 本帧跨度 = 帧尾(+156)-帧首(+152)
    v26 = (float)*(int *)(fld_2C22 + 12);
    v12 = (double)*(int *)(v36 + 12);
    v35 = fld_20 - fld_98;  // fld_20=this+32 格子像素尺寸
    v20 = v12;
    sub_4049C0(v20, v26, fld_20 - fld_98, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(uint32_t *)(this + 72) = (uint64_t)v12;  // 渲染态：位置x
    v27 = (float)*(int *)(fld_2C22 + 16);
    v13 = (double)*(int *)(v36 + 16);
    v21 = v13;
    sub_4049C0(v21, v27, v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(uint32_t *)(this + 76) = (uint64_t)v13;  // this+76〔pBtnActionE〕
    sub_4049C0(*(float *)(v36 + 20), *(float *)(fld_2C22 + 20), v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(float *)(this + 80) = v13;  // this+80〔nAuraStage(推断)〕
    sub_4049C0(*(float *)(v36 + 24), *(float *)(fld_2C22 + 24), v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(float *)(this + 84) = v13;  // this+84〔pFxObjA(推断)〕
    sub_4049C0(*(float *)(v36 + 28), *(float *)(fld_2C22 + 28), v35, fld_9C);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
    *(float *)(this + 88) = v13;  // this+88〔pFxObjB(推断)〕等 2 字段
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
    LOBYTE(fld_94) = v32;  // fld_94=this+148 第 4 组·+802 增量子倍率
  }
  return fld_94;  // fld_94=this+148 第 4 组·+802 增量子倍率
}


// ------------------------------------------------------------
// 0x491C10 sub_491C10 —— 遍历帧数组（首+44/尾+48，步长 88）
// ------------------------------------------------------------
int /*thiscall*/ sub_491C10(int this)  // 实现：遍历帧数组（首+44/尾+48，步长 88）
{
  int fld_2C; // eax
  int v2; // ebx
  int *fld_2C2; // esi
  int i; // edi

  fld_2C = *(uint32_t *)(this + 44);  // fld_2C = 读 this+44
  v2 = 0;
  if ( fld_2C != 0 )  // 若 fld_2C 非 0
    fld_2C = (*(uint32_t *)(this + 48) - fld_2C) / 88;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  if ( fld_2C > 0 )  // 若 fld_2C > 0
  {
    fld_2C2 = (int *)(*(uint32_t *)(this + 44) + 48);  // this+44〔nExpireMs(推断)〕等 2 字段
    for ( i = fld_2C; i != 0; --i )  // 循环：i 从 fld_2C 递减到 0
    {
      v2 += (uint64_t)((double)*fld_2C2 * (1.0 / *(float *)(this + 164)) * 100.0);  // this+164〔fAdd164(推断)〕
      fld_2C2 += 22;  // fld_2C2=this+44 nExpireMs
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x491C70 sub_491C70 —— ★帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
// ------------------------------------------------------------
int /*thiscall*/ sub_491C70(int this, int nArg2)  // 实现：帧时刻换算：第 a2 帧累计时刻 = Σ 帧+48(DELAY)×100/速率(+164)（研究§26）
{
  int fld_2C; // eax
  int v4; // ebx
  int v5; // edi
  int fld_2C2; // ecx
  int fld_30; // [esp+Ch] [ebp-8h]
  int fld_2C22; // [esp+10h] [ebp-4h]

  fld_2C = *(uint32_t *)(this + 44);  // fld_2C = 读 this+44
  v4 = 0;
  fld_2C22 = 0;
  if ( fld_2C != 0 )  // 若 fld_2C 非 0
    fld_30 = (*(uint32_t *)(this + 48) - fld_2C) / 88;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  else  // 否则分支
    fld_30 = 0;  // fld_30=this+48 pCmdVecBegin48
  v5 = 0;
  if ( nArg2 <= 0 )  // 若 nArg2 <= 0
    return 0;
  do  // do-while 循环体起点
  {
    if ( v5 >= fld_30 )  // 若 v5 >= fld_30
      break;  // 跳出循环/分支
    fld_2C2 = (uint64_t)((double)*(int *)(*(uint32_t *)(this + 44) + v4 + 48) / *(float *)(this + 164) * 100.0) + fld_2C22;  // Σ 帧+48(DELAY)×100/速率(+164)（研究§26 帧尾公式）
    ++v5;
    v4 += 88;
    fld_2C22 = fld_2C2;
  }
  while ( v5 < nArg2 );  // 条件循环
  return fld_2C22;
}



// ------------------------------------------------------------
// 0x491D00 sub_491D00 —— 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
//   先对子链中索引<0 的项递归，再 sub_4916E0 提交本层（帧 +40 特效/+44 参数色）；
//   +176 开启时续调 sub_4917A0（STENCIL 分支，取 +180/+184/+188/+192），+196 一次性则渲染后自清。
// ------------------------------------------------------------
char /*thiscall*/ sub_491D00(int this, int nArg2, int nArg3, int nArg4, float fArg5)  // 实现：图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
{
  uint32_t *fld_CC; // eax
  uint32_t *v7; // esi
  char result; // al

  fld_CC = *(uint32_t **)(this + 204);  // fld_CC = 读 this+204
  v7 = (uint32_t *)*fld_CC;  // fld_CC=this+204 子动画链指针
  if ( (uint32_t *)*fld_CC != fld_CC )  // fld_CC=this+204 子动画链指针
  {
    do  // do-while 循环体起点
    {
      if ( (int)v7[2] >= 0 )
        break;  // 跳出循环/分支
      sub_491D00(nArg2, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      v7 = (uint32_t *)*v7;
    }
    while ( v7 != *(uint32_t **)(this + 204) );  // 条件循环
  }
  sub_4916E0(nArg2, nArg3, nArg4, fArg5, this + 60);  // 图层属性下发（帧 +40 特效/+44 参数色 → 渲染态，sub_424760 提交）
  result = *(uint8_t *)(this + 176);  // result = 读 this+176
  if ( result != 0 )  // 若结果非 0（成功）
  {
    sub_4917A0(  // 图层属性下发·STENCIL 分支（dword_79C0A4 vtable+28/+36；RGBA 重排）
      nArg2,
      nArg3,
      nArg4,
      fArg5,
      this + 60,  // this+60 fade 值
      *(uint32_t *)(this + 180),  // this+180 半径/计数
      *(uint8_t *)(this + 184),  // this+184 单目标标志
      *(uint32_t *)(this + 188),  // this+188 状态槽索引
      *(uint32_t *)(this + 192));  // this+192〔nDlgId(推断)〕
    result = *(uint8_t *)(this + 196);  // result = 读 this+196
    if ( result != 0 )  // 若结果非 0（成功）
      *(uint8_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  }
  for ( ; v7 != *(uint32_t **)(this + 204); v7 = (uint32_t *)*v7 )  // 遍历循环
    result = sub_491D00(nArg2, nArg3, nArg4, fArg5);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  return result;
}



// ------------------------------------------------------------
// 0x491DE0 sub_491DE0 —— 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
//   与 ·0x491D00 同构（差异：不调 sub_4916E0 普通分支，STENCIL 参数直接取自入参），
//   递归 +204 子链，用于需要整链替换 stencil 的场合。
// ------------------------------------------------------------
char /*thiscall*/ sub_491DE0(uint32_t *this, int nArg2, int nArg3, int nArg4, float fArg5, int nArg6, char pszArg7, int nArg8, int nArg9)  // 实现：图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
{
  uint32_t *fld_e51; // eax
  uint32_t *v11; // esi
  char result; // al

  fld_e51 = (uint32_t *)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  v11 = (uint32_t *)*fld_e51;  // fld_e51=this+204 pSubAnim204
  if ( (uint32_t *)*fld_e51 != fld_e51 )  // fld_e51=this+204 pSubAnim204
  {
    do  // do-while 循环体起点
    {
      if ( (int)v11[2] >= 0 )
        break;  // 跳出循环/分支
      sub_491DE0(nArg2, nArg3, nArg4, fArg5, nArg6, pszArg7, nArg8, nArg9);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
      v11 = (uint32_t *)*v11;
    }
    while ( v11 != (uint32_t *)*(this + 51) );  // 条件循环
  }
  for ( result = sub_4917A0(nArg2, nArg3, nArg4, fArg5, (int)(this + 15), nArg6, pszArg7, nArg8, nArg9);  // 图层属性下发·STENCIL 分支（dword_79C0A4 vtable+28/+36；RGBA 重排）
        v11 != (uint32_t *)*(this + 51);  // this+204〔pSubAnim204(推断)〕
        v11 = (uint32_t *)*v11 )  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
  {
    result = sub_491DE0(nArg2, nArg3, nArg4, fArg5, nArg6, pszArg7, nArg8, nArg9);  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
  }
  return result;
}



// ------------------------------------------------------------
// 0x491EA0 sub_491EA0 —— 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161 阴影位门）
//   先递归子链索引<0 项，再 sub_491300 画本帧（帧块 this+60），后递归余项。
// ------------------------------------------------------------
void /*thiscall*/ sub_491EA0(int this, int nArg2, int nArg3, int nArg4, float fArg5, int nArg6, float fArg7, float fArg8, int nArg9)  // 实现：帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161 阴影位门）
{
  uint32_t *fld_CC; // eax
  uint32_t *v11; // esi

  if ( byte_790AD0 != 0 && *(uint8_t *)(this + 161) != 0 )  // 若 byte_790AD0 != 0
  {
    fld_CC = *(uint32_t **)(this + 204);  // fld_CC = 读 this+204
    v11 = (uint32_t *)*fld_CC;  // fld_CC=this+204 子动画链指针
    if ( (uint32_t *)*fld_CC != fld_CC )  // fld_CC=this+204 子动画链指针
    {
      do  // do-while 循环体起点
      {
        if ( (int)v11[2] >= 0 )
          break;  // 跳出循环/分支
        sub_491EA0(nArg2, nArg3, nArg4, fArg5, nArg6, fArg7, fArg8, nArg9);  // 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161 阴影位门）
        v11 = (uint32_t *)*v11;
      }
      while ( v11 != *(uint32_t **)(this + 204) );  // 条件循环
    }
    sub_491300((uint8_t *)this, nArg2, nArg3, nArg4, fArg5, this + 60, nArg6, fArg7, fArg8, nArg9);  // 帧图像绘制
    for ( ; v11 != *(uint32_t **)(this + 204); v11 = (uint32_t *)*v11 )  // 遍历循环
      sub_491EA0(nArg2, nArg3, nArg4, fArg5, nArg6, fArg7, fArg8, nArg9);  // 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161 阴影位门）
  }
}



// ------------------------------------------------------------
// 0x491F80 sub_491F80 —— RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
// ------------------------------------------------------------
char /*thiscall*/ sub_491F80(int this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
{
  int fld_5C; // ebx
  uint32_t **fld_CC; // eax
  uint16_t v9; // cx
  uint32_t *v10; // esi

  fld_5C = nArg2;
  LOBYTE(fld_CC) = -1;
  if ( nArg2 == -1 )
  {
    if ( nArg3 == -1 && nArg4 == -1 && nArg5 == -1 )  // 若 nArg3 == -1 与/或 nArg4 == -1 与/或 nArg5 == -1
      return (char)fld_CC;
    fld_5C = *(uint8_t *)(this + 92);  // fld_5C = 读 this+92
  }
  if ( nArg3 == -1 )
    nArg3 = *(uint8_t *)(this + 93);  // this+93〔bEnableFlag〕
  if ( nArg4 == -1 )
    nArg4 = *(uint8_t *)(this + 94);  // this+94〔nScaleParam〕
  if ( nArg5 == -1 )
    nArg5 = *(uint8_t *)(this + 95);  // nArg5 = 读 this+95
  HIBYTE(v9) = nArg5;
  LOBYTE(v9) = nArg4;  // nArg4=this+94 nScaleParam
  LOBYTE(fld_CC) = nArg6;
  *(uint32_t *)(this + 92) = (uint8_t)fld_5C | (((uint8_t)nArg3 | (v9 << 8)) << 8);  // this+92〔pFxObjC(推断)〕等 2 字段
  if ( (uint8_t)nArg6 != 0 )
  {
    fld_CC = *(uint32_t ***)(this + 204);  // fld_CC = 读 this+204
    v10 = *fld_CC;  // fld_CC=this+204 子动画链指针
    if ( *fld_CC != fld_CC )  // fld_CC=this+204 子动画链指针
    {
      do  // do-while 循环体起点
      {
        LOBYTE(fld_CC) = sub_491F80(fld_5C, nArg3, nArg4, nArg5, nArg6);  // RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
        v10 = (uint32_t *)*v10;
      }
      while ( v10 != *(uint32_t **)(this + 204) );  // 条件循环
    }
  }
  return (char)fld_CC;  // fld_CC=this+204 子动画链指针
}



// ------------------------------------------------------------
// 0x492030 sub_492030 —— 子对象绘制原点/尺寸下发（+100/+104 转发给 +204 子链）
// a5≠0 时递归广播；与 ·0x492080 的累计时刻偏移配合做子动画相对定位。
// ------------------------------------------------------------
char /*thiscall*/ sub_492030(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：子对象绘制原点/尺寸下发（+100/+104 转发给 +204 子链）
{
  uint32_t **fld_e51; // eax
  uint32_t *v6; // esi

  *(this + 26) = nArg3;  // this+104〔nTimerEnd(推断)〕
  LOBYTE(fld_e51) = nArg4;
  *(this + 25) = nArg2;  // this+100〔bEnchantDone(推断)〕
  if ( (uint8_t)nArg4 != 0 )
  {
    fld_e51 = (uint32_t **)*(this + 51);  // this+204〔pSubAnim204(推断)〕
    v6 = *fld_e51;  // fld_e51=this+204 pSubAnim204
    if ( *fld_e51 != fld_e51 )  // fld_e51=this+204 pSubAnim204
    {
      do  // do-while 循环体起点
      {
        LOBYTE(fld_e51) = sub_492030(nArg2, nArg3, nArg4);  // 子对象绘制原点/尺寸下发（+100/+104 转发给 +204 子链）
        v6 = (uint32_t *)*v6;
      }
      while ( v6 != (uint32_t *)*(this + 51) );  // 条件循环
    }
  }
  return (char)fld_e51;  // fld_e51=this+204 pSubAnim204
}



// ------------------------------------------------------------
// 0x492080 sub_492080 —— 播放速率写入（+172 新速率；差值补偿累计时刻 +88）
// 速率变化时把 (新-旧) 累加进 +88（重算时刻，与 ·0x493B70 同族思路），再递归 +204 子链下发。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_492080(int this, float fArg2)  // 实现：播放速率写入（+172 新速率；差值补偿累计时刻 +88）
{
  double fld_AC; // st7
  uint32_t *result; // eax
  uint32_t *v5; // esi

  if ( *(float *)(this + 172) != fArg2 )  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  {
    fld_AC = fArg2 - *(float *)(this + 172);  // this+172〔pAppendVecEnd(推断)〕等 2 字段
    *(float *)(this + 172) = fArg2;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
    *(float *)(this + 88) = fld_AC + *(float *)(this + 88);  // this+88〔pFxObjB(推断)〕等 2 字段
  }
  result = *(uint32_t **)(this + 204);  // result = 读 this+204
  v5 = (uint32_t *)*result;  // result=this+204 子动画链指针
  if ( (uint32_t *)*result != result )  // result=this+204 子动画链指针
  {
    do  // do-while 循环体起点
    {
      result = (uint32_t *)sub_492080(fArg2);  // 播放速率写入（+172 新速率；差值补偿累计时刻 +88）
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != *(uint32_t **)(this + 204) );  // 条件循环
  }
  return result;  // result=this+204 子动画链指针
}



// ------------------------------------------------------------
// 0x4920E0 sub_4920E0 —— ★批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4920E0(uint32_t *this, float fArg2, float fArg3)  // 实现：批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
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

  fld_e11 = *(this + 11);  // this+44〔nExpireMs(推断)〕
  if ( fld_e11 != 0 )  // 若 fld_e11 非 0
    fld_e12 = (*(this + 12) - fld_e11) / 88;  // this+48〔pCmdVecBegin48(推断)〕
  else  // 否则分支
    fld_e12 = 0;  // fld_e12=this+48 pCmdVecBegin48
  v6 = 0;
  if ( fld_e12 >= 4 )  // 若 fld_e12 >= 4
  {
    v7 = 0;
    v8 = ((unsigned int)(fld_e12 - 4) >> 2) + 1;  // fld_e12=this+48 pCmdVecBegin48
    v6 = 4 * v8;
    do  // do-while 循环体起点
    {
      *(float *)(*(this + 11) + v7 + 20) = fArg2;  // 帧+20 缩放x（sub_4920E0 批量改写，研究§11）
      v7 += 352;
      --v8;
      *(float *)(*(this + 11) + v7 - 328) = fArg3;  // 帧+24 缩放y（展开循环）
      *(float *)(*(this + 11) + v7 - 244) = fArg2;  // this+44〔nExpireMs(推断)〕
      *(float *)(*(this + 11) + v7 - 240) = fArg3;  // this+44〔nExpireMs(推断)〕
      *(float *)(*(this + 11) + v7 - 156) = fArg2;  // this+44〔nExpireMs(推断)〕
      *(float *)(*(this + 11) + v7 - 152) = fArg3;  // this+44〔nExpireMs(推断)〕
      *(float *)(*(this + 11) + v7 - 68) = fArg2;  // this+44〔nExpireMs(推断)〕
      *(float *)(*(this + 11) + v7 - 64) = fArg3;  // this+44〔nExpireMs(推断)〕
    }
    while ( v8 != 0 );  // 条件循环
  }
  if ( v6 < fld_e12 )  // 若 v6 < fld_e12
  {
    v9 = 88 * v6;
    v10 = fld_e12 - v6;  // fld_e12=this+48 pCmdVecBegin48
    do  // do-while 循环体起点
    {
      *(float *)(*(this + 11) + v9 + 20) = fArg2;  // this+44〔nExpireMs(推断)〕
      v9 += 88;
      --v10;
      *(float *)(*(this + 11) + v9 - 64) = fArg3;  // this+44〔nExpireMs(推断)〕
    }
    while ( v10 != 0 );  // 条件循环
  }
  result = (uint32_t *)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  v12 = (uint32_t *)*result;  // result=this+204 pSubAnim204
  if ( (uint32_t *)*result != result )  // result=this+204 pSubAnim204
  {
    do  // do-while 循环体起点
    {
      result = (uint32_t *)sub_4920E0(fArg2, fArg3);  // 批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
      v12 = (uint32_t *)*v12;
    }
    while ( v12 != (uint32_t *)*(this + 51) );  // 条件循环
  }
  return result;  // result=this+204 pSubAnim204
}



// ------------------------------------------------------------
// 0x4921E0 sub_4921E0 —— ★批量改写全帧攻击盒/受击盒坐标（各分量 ×fArg2）
//   帧数组 = +44..+48，步长 88；每帧 +60/+64 攻击盒 vector、+76/+80 受击盒 vector
//   元素 24B=6×float 逐一乘 fArg2；末尾递归 +51 表登记的同步子链。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4921E0(int *this, float fArg2)  // 实现：批量改写全帧攻击盒/受击盒坐标（各分量 ×fArg2）
{
  int fld_e11; // eax
  int fld_e112; // ecx
  int v5; // edx
  int i; // edi
  int v7; // eax
  int j; // eax
  uint32_t *result; // eax
  uint32_t *v10; // edi

  fld_e11 = *(this + 11);  // this+44〔nExpireMs(推断)〕
  if ( fld_e11 != 0 )  // 若 fld_e11 非 0
    fld_e11 = (*(this + 12) - fld_e11) / 88;  // this+48〔pCmdVecBegin48(推断)〕
  if ( fld_e11 > 0 )  // 若 fld_e11 > 0
  {
    fld_e112 = *(this + 11);  // this+44〔nExpireMs(推断)〕
    v5 = 0;
    for ( i = fld_e11; i != 0; --i )  // 循环：i 从 fld_e11 递减到 0
    {
      v7 = *(uint32_t *)(v5 + fld_e112 + 60);  // fld_e112=this+44 nExpireMs
      if ( v7 != *(uint32_t *)(v5 + fld_e112 + 64) )  // fld_e112=this+44 nExpireMs
      {
        do  // do-while 循环体起点
        {
          v7 += 24;
          *(float *)(v7 - 24) = fArg2 * *(float *)(v7 - 24);
          *(float *)(v7 - 20) = fArg2 * *(float *)(v7 - 20);
          *(float *)(v7 - 16) = fArg2 * *(float *)(v7 - 16);
          *(float *)(v7 - 12) = fArg2 * *(float *)(v7 - 12);
          *(float *)(v7 - 8) = fArg2 * *(float *)(v7 - 8);
          *(float *)(v7 - 4) = fArg2 * *(float *)(v7 - 4);
        }
        while ( v7 != *(uint32_t *)(*(this + 11) + v5 + 64) );  // 条件循环
      }
      fld_e112 = *(this + 11);  // this+44〔nExpireMs(推断)〕
      for ( j = *(uint32_t *)(v5 + fld_e112 + 76); j != *(uint32_t *)(v5 + fld_e112 + 80); fld_e112 = *(this + 11) )  // 遍历循环
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
  result = (uint32_t *)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  v10 = (uint32_t *)*result;  // result=this+204 pSubAnim204
  if ( (uint32_t *)*result != result )  // result=this+204 pSubAnim204
  {
    do  // do-while 循环体起点
    {
      result = (uint32_t *)sub_4921E0(fArg2);  // 批量改写全帧攻击盒/受击盒坐标（各分量 ×fArg2）
      v10 = (uint32_t *)*v10;
    }
    while ( v10 != (uint32_t *)*(this + 51) );  // 条件循环
  }
  return result;  // result=this+204 pSubAnim204
}



// ------------------------------------------------------------
// 0x4922F0 sub_4922F0 —— 全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
//   与 ·0x4921E0 同构（差异：不递归子链、不查容量，纯就地乘算）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4922F0(uint32_t *this, float fArg2)  // 实现：全帧缩放与盒缩放统一乘算（帧 +20/+24 与 +60/+76 盒 ×fArg2）
{
  int fld_e11; // edx
  int i; // ecx
  int j; // eax
  int k; // eax

  fld_e11 = *(this + 11);  // this+44〔nExpireMs(推断)〕
  for ( i = *(this + 12); fld_e11 != i; fld_e11 += 88 )  // 遍历循环
  {
    *(float *)(fld_e11 + 20) = fArg2 * *(float *)(fld_e11 + 20);  // fld_e11=this+44 nExpireMs
    *(float *)(fld_e11 + 24) = fArg2 * *(float *)(fld_e11 + 24);  // fld_e11=this+44 nExpireMs
    for ( j = *(uint32_t *)(fld_e11 + 60); j != *(uint32_t *)(fld_e11 + 64); *(float *)(j - 4) = fArg2 * *(float *)(j - 4) )  // 遍历循环
    {
      j += 24;
      *(float *)(j - 24) = fArg2 * *(float *)(j - 24);
      *(float *)(j - 20) = fArg2 * *(float *)(j - 20);
      *(float *)(j - 16) = fArg2 * *(float *)(j - 16);
      *(float *)(j - 12) = fArg2 * *(float *)(j - 12);
      *(float *)(j - 8) = fArg2 * *(float *)(j - 8);
    }
    for ( k = *(uint32_t *)(fld_e11 + 76); k != *(uint32_t *)(fld_e11 + 80); *(float *)(k - 4) = fArg2 * *(float *)(k - 4) )  // 遍历循环
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
int /*thiscall*/ sub_4923C0(uint32_t *this, int nArg2)  // 实现：全帧缩放统一设值（+20/+24）
{
  int result; // eax
  int i; // ecx

  result = *(this + 11);  // this+44〔nExpireMs(推断)〕
  for ( i = *(this + 12); result != i; result += 88 )  // 遍历循环
  {
    *(uint32_t *)(result + 20) = nArg2;  // result=this+44 nExpireMs
    *(uint32_t *)(result + 24) = nArg2;  // result=this+44 nExpireMs
  }
  return result;  // result=this+44 nExpireMs
}



// ------------------------------------------------------------
// 0x4923F0 sub_4923F0 —— 全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
//   帧 +20/+24 与 +60/+76 盒各分量乘 1.0/fArg2，用于把已缩放帧还原到基准尺寸。
// ------------------------------------------------------------
void /*thiscall*/ sub_4923F0(uint32_t *this, float fArg2)  // 实现：全帧按倒数缩放（×1/fArg2，抵消 ·0x4922F0/·0x4921E0 的正向乘算）
{
  int fld_e11; // edx
  int fld_e12; // ecx
  double v4; // st7
  int i; // eax
  int j; // eax

  fld_e11 = *(this + 11);  // this+44〔nExpireMs(推断)〕
  fld_e12 = *(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
  if ( fld_e11 != fld_e12 )  // 若 fld_e11 != fld_e12
  {
    v4 = 1.0 / fArg2;
    do  // do-while 循环体起点
    {
      *(float *)(fld_e11 + 20) = v4 * *(float *)(fld_e11 + 20);  // fld_e11=this+44 nExpireMs
      *(float *)(fld_e11 + 24) = v4 * *(float *)(fld_e11 + 24);  // fld_e11=this+44 nExpireMs
      for ( i = *(uint32_t *)(fld_e11 + 60); i != *(uint32_t *)(fld_e11 + 64); *(float *)(i - 4) = v4 * *(float *)(i - 4) )  // 遍历循环
      {
        i += 24;
        *(float *)(i - 24) = v4 * *(float *)(i - 24);
        *(float *)(i - 20) = v4 * *(float *)(i - 20);
        *(float *)(i - 16) = v4 * *(float *)(i - 16);
        *(float *)(i - 12) = v4 * *(float *)(i - 12);
        *(float *)(i - 8) = v4 * *(float *)(i - 8);
      }
      for ( j = *(uint32_t *)(fld_e11 + 76); j != *(uint32_t *)(fld_e11 + 80); *(float *)(j - 4) = v4 * *(float *)(j - 4) )  // 遍历循环
      {
        j += 24;
        *(float *)(j - 24) = v4 * *(float *)(j - 24);
        *(float *)(j - 20) = v4 * *(float *)(j - 20);
        *(float *)(j - 16) = v4 * *(float *)(j - 16);
        *(float *)(j - 12) = v4 * *(float *)(j - 12);
        *(float *)(j - 8) = v4 * *(float *)(j - 8);
      }
      fld_e11 += 88;  // fld_e11=this+44 nExpireMs
    }
    while ( fld_e11 != fld_e12 );  // 条件循环
  }
}



// ------------------------------------------------------------
// 0x4924C0 sub_4924C0 —— 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
// ------------------------------------------------------------
int /*thiscall*/ sub_4924C0(int *this, int nArg2)  // 实现：按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
{
  int fld_e11; // eax
  int *fld_e112; // ebx
  int v5; // eax
  uint32_t *v6; // eax
  unsigned int v8; // [esp-8h] [ebp-10h]

  fld_e11 = *(this + 11);  // this+44〔nExpireMs(推断)〕
  if ( fld_e11 != 0 )  // 若 fld_e11 非 0
    fld_e11 = (*(this + 12) - fld_e11) / 88;  // this+48〔pCmdVecBegin48(推断)〕
  if ( nArg2 >= fld_e11 )  // 若 nArg2 >= fld_e11
    return 0;
  fld_e112 = (int *)(*(this + 11) + 88 * nArg2);  // this+44〔nExpireMs(推断)〕
  v5 = fld_e112[1];  // v5 = 取 fld_e112[1]
  if ( v5 != -1 )
  {
    v8 = fld_e112[2];  // v8 = 取 fld_e112[2]
    v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v5);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    *fld_e112 = sub_418DD0(v6, v8);  // 调 资源句柄 (101)
  }
  return 88 * nArg2 + *(this + 11);  // 返回 88 * nArg2 + *(this + 11)
}



// ============================================================
// §E 0x492530-0x493400  攻击盒/受击盒容器族（元素 24B = 6×float）
// ============================================================
// ------------------------------------------------------------
// 0x492530 sub_492530 —— 转发 sub_4FF050（24 字节元素区间拷贝，6 dword 一组）
// 盒 vector 复制族一环，被 ·0x492E80 扩容分支调用。
// ------------------------------------------------------------
int /*stdcall*/ sub_492530(int nArg1, int nArg2, int nArg3)  // 实现：转发 sub_4FF050（24 字节元素区间拷贝，6 dword 一组）
{
  return sub_4FF050(nArg1, nArg2, nArg3);  // 返回 调 sub_4FF050 返回值
}



// ------------------------------------------------------------
// 0x492550 sub_492550 —— 按帧号绘制 + 子链广播（+44 帧数组；帧+4 经 sub_418DD0 取句柄）
//   ① 递归 +204 子链索引<0 项；② 帧号越界帧指针=0，否则 ·0x4924C0 取帧并确保图像就绪；
//   ③ sub_4916E0 提交该帧图层属性；④ +176 开启时 sub_4917A0 走 STENCIL（+180..+196），
//   +196 一次性则自清；⑤ 递归子链余项。参数与 ·0x491D00 一致，仅帧来源由索引决定。
// ------------------------------------------------------------
char /*thiscall*/ sub_492550(int this, int nArg2, int nArg3, int nArg4, float fArg5, int nArg6)  // 实现：按帧号绘制 + 子链广播（+44 帧数组；帧+4 经 sub_418DD0 取句柄）
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

  fld_CC = *(uint32_t **)(this + 204);  // fld_CC = 读 this+204
  v9 = (uint32_t *)*fld_CC;  // fld_CC=this+204 子动画链指针
  if ( (uint32_t *)*fld_CC != fld_CC )  // fld_CC=this+204 子动画链指针
  {
    do  // do-while 循环体起点
    {
      if ( (int)v9[2] >= 0 )
        break;  // 跳出循环/分支
      sub_492550(nArg2, nArg3, nArg4, fArg5, nArg6);  // 按帧号绘制 + 子链广播（+44 帧数组；帧+4 经 sub_418DD0 取句柄）
      v9 = (uint32_t *)*v9;
    }
    while ( v9 != *(uint32_t **)(this + 204) );  // 条件循环
  }
  fld_2C = *(uint32_t *)(this + 44);  // fld_2C = 读 this+44
  if ( fld_2C != 0 )  // 若 fld_2C 非 0
    fld_2C = (*(uint32_t *)(this + 48) - fld_2C) / 88;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  if ( nArg6 >= fld_2C )  // 若 nArg6 >= fld_2C
  {
    fld_2C3 = 0;
  }
  else  // 否则分支
  {
    v11 = 88 * nArg6;
    fld_2C2 = 88 * nArg6 + *(uint32_t *)(this + 44);
    v22 = (int *)fld_2C2;
    if ( *(uint32_t *)(fld_2C2 + 4) != -1 )
    {
      v20 = *(uint32_t *)(fld_2C2 + 8);
      v13 = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F84BC + 56))(  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
                        dword_8F84BC,
                        *(uint32_t *)(fld_2C2 + 4));
      *v22 = sub_418DD0(v13, v20);  // 调 资源句柄 (101)
      v11 = 88 * nArg6;
    }
    fld_2C3 = v11 + *(uint32_t *)(this + 44);  // this+44〔nExpireMs(推断)〕等 2 字段
  }
  sub_4916E0(nArg2, nArg3, nArg4, fArg5, fld_2C3);  // 图层属性下发（帧 +40 特效/+44 参数色 → 渲染态，sub_424760 提交）
  result = *(uint8_t *)(this + 176);  // result = 读 this+176
  if ( result != 0 )  // 若结果非 0（成功）
  {
    fld_C0 = *(uint32_t *)(this + 192);  // fld_C0 = 读 this+192
    fld_BC = *(uint32_t *)(this + 188);  // fld_BC = 读 this+188
    fld_B8 = *(uint8_t *)(this + 184);  // fld_B8 = 读 this+184
    fld_B4 = *(uint32_t *)(this + 180);  // fld_B4 = 读 this+180
    v16 = sub_4924C0((int *)this, nArg6);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
    sub_4917A0(nArg2, nArg3, nArg4, fArg5, v16, fld_B4, fld_B8, fld_BC, fld_C0);  // 图层属性下发·STENCIL 分支（dword_79C0A4 vtable+28/+36；RGBA 重排）
    result = *(uint8_t *)(this + 196);  // result = 读 this+196
    if ( result != 0 )  // 若结果非 0（成功）
      *(uint8_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  }
  for ( ; v9 != *(uint32_t **)(this + 204); v9 = (uint32_t *)*v9 )  // 遍历循环
    result = sub_492550(nArg2, nArg3, nArg4, fArg5, nArg6);  // 按帧号绘制 + 子链广播（+44 帧数组；帧+4 经 sub_418DD0 取句柄）
  return result;
}



// ------------------------------------------------------------
// 0x4926A0 sub_4926A0 —— 帧游标复位（+44 帧数组；递归子链 +204）
// ------------------------------------------------------------
int /*thiscall*/ sub_4926A0(int this)  // 实现：帧游标复位（+44 帧数组；递归子链 +204）
{
  int v2; // ebx
  uint32_t *fld_CC; // eax
  uint32_t *v4; // edi
  int i; // edi
  int result; // eax

  v2 = 0;
  *(uint8_t *)(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *(uint8_t *)(this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint8_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint8_t *)(this + 169) = 0;  // this+676〔nResetFlag676(推断)〕
  *(uint8_t *)(this + 170) = 0;  // this+680〔nSnapshot680〕
  sub_430B70(this + 60);  // 88B 帧条目复位
  fld_CC = *(uint32_t **)(this + 204);  // fld_CC = 读 this+204
  *(uint32_t *)(this + 148) = -1;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 0;  // this+156〔nAdd156(推断)〕
  v4 = (uint32_t *)*fld_CC;  // fld_CC=this+204 子动画链指针
  if ( (uint32_t *)*fld_CC != fld_CC )  // fld_CC=this+204 子动画链指针
  {
    do  // do-while 循环体起点
    {
      sub_4926A0(v4[3]);  // 帧游标复位（+44 帧数组；递归子链 +204）
      v4 = (uint32_t *)*v4;
    }
    while ( v4 != *(uint32_t **)(this + 204) );  // 条件循环
  }
  *(uint32_t *)(this + 36) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
  for ( i = 0; ; i += 88 )  // 遍历循环
  {
    result = *(uint32_t *)(this + 44);  // result = 读 this+44
    if ( result != 0 )  // 若结果非 0（成功）
      result = (*(uint32_t *)(this + 48) - result) / 88;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    if ( v2 >= result )  // 若 v2 >= result
      break;  // 跳出循环/分支
    ++v2;
    *(uint32_t *)(this + 36) += *(uint32_t *)(i + *(uint32_t *)(this + 44) + 48);  // this+36〔nStateWord36(推断)〕等 4 字段
  }
  return result;  // result=this+48 pCmdVecBegin48
}



// ------------------------------------------------------------
// 0x492750 sub_492750 —— std::string 就地构造（SSO：+20 len / +24 cap 15 / +4 空字节收尾）
// pArg2 源串，+28 = 源串 +28 槽值（同族结构尾部字段拷贝）。
// 被 ·0x494680 主解析器用于拼资源路径临时串。
// ------------------------------------------------------------
int /*thiscall*/ sub_492750(int this, size_t *pArg2, uint32_t *uArg3)  // 实现：std::string 就地构造（SSO：+20 len / +24 cap 15 / +4 空字节收尾）
{
  *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  sub_4014D0((size_t *)this, pArg2, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  *(uint32_t *)(this + 28) = *uArg3;  // this+28〔pPanelVec(推断)〕等 2 字段
  return this;
}



// ------------------------------------------------------------
// 0x492780 sub_492780 —— std::list 节点计数累加（cached size 位于 +8）
//   溢出上限 0x1FFFFFFF 时构造 list<T> too long 的 std::length_error 抛出。
//   被 ·0x494240 在 sub_52DAA0 分配并插入子链节点后调用（计数 +1）。
// ------------------------------------------------------------
int /*thiscall*/ sub_492780(uint32_t *this, unsigned int uArg2)  // 实现：std::list 节点计数累加（cached size 位于 +8）
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( 0x1FFFFFFF - fld_e2 < uArg2 )  // fld_e2=this+8 nSkillRec8
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x492810 sub_492810 —— vector<uint32> 长度溢出兜底（throw length_error，vector<T> too long）
//   与 ·0x490880 同构（差异：this 仅作抛点标识，不做字段访问）；由 32 字节元素容器扩容分支调用。
// ------------------------------------------------------------
void /*noreturn*/ sub_492810()  // 实现：vector<uint32> 长度溢出兜底（throw length_error，vector<T> too long）
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
  sub_401740(pExceptionObject, &v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x492880 sub_492880 —— 32 字节元素容器区间反向拷贝（后向搬入版）
//   从 [pArg1,pArg2) 尾部逐元素（-8 dword=32B）拷到 pArg3 之前空位：sub_4014D0 拷 std::string
//   主体 + 整拷 +28 槽（该结构 = string + 1 字段）。被 ·0x492DC0 的 assign/erase 分支转发。
// ------------------------------------------------------------
size_t */*cdecl*/ sub_492880(size_t *pArg1, size_t *pArg2, size_t *pArg3)  // 实现：32 字节元素容器区间反向拷贝（后向搬入版）
{
  size_t *pArg22; // esi
  size_t *pArg32; // edi

  pArg22 = pArg2;
  if ( pArg1 == pArg2 )  // 若 pArg1 == pArg2
    return pArg3;
  pArg32 = pArg3;
  do  // do-while 循环体起点
  {
    pArg22 -= 8;
    pArg32 -= 8;
    sub_4014D0(pArg32, pArg22, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    pArg32[7] = pArg22[7];  // pArg32[7] = 取 pArg22[7]
  }
  while ( pArg22 != pArg1 );  // 条件循环
  return pArg32;
}



// ------------------------------------------------------------
// 0x4928C0 sub_4928C0 —— 32 字节元素容器的正向构造循环（assign 版）
//   从 pArg1 起逐元素写到 nArg32（每份 32B：+20/+24/+4 初始化 SSO 头，sub_4014D0 拷串体，
//   +28 = 源 +28 槽）；LOBYTE(v7)=1 为构造期异常展开标记。
// ------------------------------------------------------------
int /*cdecl*/ sub_4928C0(size_t *pArg1, size_t *pArg2, int nArg3)  // 实现：32 字节元素容器的正向构造循环（assign 版）
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != pArg2 )  // 条件循环
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )  // 若 nArg32 非 0
    {
      *(uint32_t *)(nArg32 + 24) = 15;  // nArg32+24〔nPageMax(推断)〕
      *(uint32_t *)(nArg32 + 20) = 0;  // nArg32+20〔nPage(推断)〕
      *(uint8_t *)(nArg32 + 4) = 0;  // nArg32+4〔宿主对象〕
      sub_4014D0((size_t *)nArg32, pArg1, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      *(uint32_t *)(nArg32 + 28) = pArg1[7];  // nArg32+28〔pPanelVec(推断)〕
    }
    nArg32 += 32;
    LOBYTE(v7) = 0;
    pArg1 += 8;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x492980 sub_492980 —— 子链节点按对象指针摘除（组件槽卸载/释放）
//   遍历 +204 链找节点 +12 == pArg2 者；命中后清 pArg2+212（同步源）、sub_42AF90 +
//   sub_657740(obj,228) 释放对象、双向摘链、j__free 节点、链计数 +208 减 1。
// ------------------------------------------------------------
void **/*thiscall*/ sub_492980(void ***this, void *pArg2)  // 实现：子链节点按对象指针摘除（组件槽卸载/释放）
{
  void **fld_e51; // ecx
  void **result; // eax
  uint32_t *v5; // ecx

  fld_e51 = *(this + 51);  // this+204〔pSubAnim204(推断)〕
  result = (void **)*fld_e51;  // fld_e51=this+204 pSubAnim204
  if ( *fld_e51 != fld_e51 )  // fld_e51=this+204 pSubAnim204
  {
    while ( result[3] != pArg2 )  // 条件循环
    {
      result = (void **)*result;
      if ( result == fld_e51 )  // 若 result == fld_e51
        return result;
    }
    v5 = result[3];  // v5 = 取 result[3]
    if ( v5 != nullptr )  // 若 v5 有效（非空）
      v5[53] = 0;
    if ( result != *(this + 51) )  // this+204〔pSubAnim204(推断)〕
    {
      *(uint32_t *)result[1] = *result;
      *((uint32_t *)*result + 1) = result[1];
      j__free(result);  // 调 j__free（堆释放）
      result = (void **)((char *)*(this + 52) - 1);  // this+208〔nField208(推断)〕
      *(this + 52) = result;  // this+208〔nField208(推断)〕
    }
  }
  return result;  // result=this+208 nField208
}



// ------------------------------------------------------------
// 0x4929F0 sub_4929F0 —— 盒 vector 插入（元素 24B = 6×float）
// ------------------------------------------------------------
int /*thiscall*/ sub_4929F0(int *this, int pArg2, unsigned int uArg3, uint32_t *Block)  // 实现：盒 vector 插入（元素 24B = 6×float）
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
  v6 = Block[1];  // v6 = 取 Block[1]
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  v28[0] = *Block;
  v8 = Block[2];  // v8 = 取 Block[2]
  v28[1] = v6;
  v9 = Block[3];  // v9 = 取 Block[3]
  v28[2] = v8;
  v10 = Block[4];  // v10 = 取 Block[4]
  v28[3] = v9;
  v11 = Block[5];  // v11 = 取 Block[5]
  v28[6] = &v27;
  v28[4] = v10;
  v28[5] = v11;
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 24;  // this+12〔nSkillRec12(推断)〕
  }
  else  // 否则分支
  {
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  }
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - fld_e1) / 24;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 178956970 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_430A90(this);  // vector 超长异常（length_error）
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - fld_e1) / 24;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = (void *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      Blockb = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( ((int)fld_e23 - pArg2) / 24 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v30 = (int)fld_e23 - 24 * uArg3;  // fld_e23=this+8 nSkillRec8
        *(this + 2) = sub_4FF050(v30, fld_e23, fld_e23);  // this+8〔nSkillRec8(推断)〕
        sub_504430(pArg2, v30, Blockb);
        return sub_4FEF50(pArg2, pArg2 + 24 * uArg3, v28);  // 返回 调 sub_4FEF50 返回值
      }
      else  // 否则分支
      {
        sub_4FF050(pArg2, fld_e23, pArg2 + 24 * uArg3);  // fld_e23=this+8 nSkillRec8
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 24;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        v29 = 2;
        sub_504620(fld_e25, fld_e24, v28);  // fld_e25=this+8 nSkillRec8
        fld_e26 = 24 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        return sub_4FEF50(pArg2, fld_e26 - 24 * uArg3, v28);  // 返回 调 sub_4FEF50 返回值
      }
    }
    else  // 否则分支
    {
      if ( 178956970 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v16 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else  // 否则分支
        v16 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - fld_e1) / 24;  // this+8〔nSkillRec8(推断)〕
      else  // 否则分支
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v16 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v16 = uArg3 + sub_4FEF30(this);  // 调 pArg2+4〔宿主对象〕
      v18 = 24 * v16;
      Blocka = (char *)operator new(24 * v16);
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      v29 = 0;
      v31 = sub_4FF050(fld_e12, pArg2, Blocka);  // v31 = 调 sub_4FF050 返回值
      sub_5044B0(v31, uArg3, v28);  // 调 后返回 &pArg1[6*uArg2] 尾地址
      sub_4FF050(pArg2, *(this + 2), v31 + 24 * uArg3);  // this+8〔nSkillRec8(推断)〕
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != 0 )  // 若 fld_e13 非 0
        fld_e13 = (*(this + 2) - fld_e13) / 24;  // this+8〔nSkillRec8(推断)〕
      v20 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      *(this + 3) = (int)&Blocka[v18];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&Blocka[24 * v20];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)Blocka;  // this+4〔宿主对象〕
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x492CC0 sub_492CC0 —— 盒 vector（24B 元素）容器构造：按源 size 预分配
//   size=(+8-+4)/24；sub_430BE0 分配成功即 sub_4FF050 深拷贝全部元素。
//   被 ·0x493070 帧拷贝构造用于 +56/+72 两个盒 vector。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_492CC0(uint32_t *this, int pArg2)  // 实现：盒 vector（24B 元素）容器构造：按源 size 预分配
{
  int v2; // eax
  int v5; // [esp-14h] [ebp-34h]
  int v6; // [esp-10h] [ebp-30h]
  int fld_e1; // [esp-Ch] [ebp-2Ch]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v2 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v10 = &v8;
  pThis = this;
  if ( v2 != 0 )  // 若 v2 非 0
    v2 = (*(uint32_t *)(pArg2 + 8) - v2) / 24;  // pArg2+8〔nSkillRec8(推断)〕
  if ( (uint8_t)sub_430BE0(v2) != 0 )  // 盒数组预分配（24B 元素）
  {
    fld_e1 = *(this + 1);  // this+4〔宿主对象〕
    v6 = *(uint32_t *)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v5 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v11 = 0;
    *(this + 2) = sub_4FF050(v5, v6, fld_e1);  // this+8〔nSkillRec8(推断)〕
  }
  return this;
}



// ------------------------------------------------------------
// 0x492D60 sub_492D60 —— 32 字节元素容器正向区间拷贝（逐元素赋值，非构造版）
//   对 [pArg1,pArg2) 每元素调 sub_4014D0 拷 std::string，再整拷 +28 槽。
// ------------------------------------------------------------
size_t /*cdecl*/ sub_492D60(size_t *pArg1, size_t *pArg2, size_t *pArg3)  // 实现：32 字节元素容器正向区间拷贝（逐元素赋值，非构造版）
{
  size_t *i; // esi
  size_t result; // eax

  for ( i = pArg1; i != pArg2; i += 8 )  // 遍历循环
  {
    sub_4014D0(i, pArg3, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    result = pArg3[7];  // result = 取 pArg3[7]
    i[7] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x492DA0 sub_492DA0 —— 转发 ·0x492880（32 字节元素反向拷贝）
// 容器 erase/assign 族占位，无附加逻辑。
// ------------------------------------------------------------
size_t */*cdecl*/ sub_492DA0(size_t *pArg1, size_t *pArg2, size_t *pArg3)  // 实现：转发 ·0x492880（32 字节元素反向拷贝）
{
  return sub_492880(pArg1, pArg2, pArg3);  // 32 字节元素容器区间反向拷贝（后向搬入版）
}



// ------------------------------------------------------------
// 0x492DC0 sub_492DC0 —— 32 字节元素容器填充构造（nArg2 份，源 pArg3）
//   循环 nArg2 次：每份写 +24=15/+20=0/+4=0 的 SSO 头、sub_4014D0 拷串体、+28 取源 +28 槽；
//   返回末位置，被 ·0x493230/·0x493AD0 用于末尾追加。
// ------------------------------------------------------------
size_t /*cdecl*/ sub_492DC0(int nArg1, int nArg2, size_t *pArg3)  // 实现：32 字节元素容器填充构造（nArg2 份，源 pArg3）
{
  int nArg12; // esi
  size_t result; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-24h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  nArg12 = nArg1;
  v5[5] = v5;
  v5[4] = nArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 条件循环
  {
    v5[3] = nArg12;
    LOBYTE(v6) = 1;
    if ( nArg12 != 0 )  // 若 nArg12 非 0
    {
      *(uint32_t *)(nArg12 + 24) = 15;  // nArg12+24〔nPageMax(推断)〕
      *(uint32_t *)(nArg12 + 20) = 0;  // nArg12+20〔nPage(推断)〕
      *(uint8_t *)(nArg12 + 4) = 0;  // nArg12+4〔宿主对象〕
      sub_4014D0((size_t *)nArg12, pArg3, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      result = pArg3[7];  // result = 取 pArg3[7]
      *(uint32_t *)(nArg12 + 28) = result;  // nArg12+28〔pPanelVec(推断)〕
    }
    nArg12 += 32;
    LOBYTE(v6) = 0;
    --nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x492E80 sub_492E80 —— 盒 vector（24B/6float）赋值 operator=（三支）
//   源空 → 释放本侧返回；源更大且容量够 → ·0x4919B0 拷已有段 + sub_4FF050 补尾；
//   容量不够 → 释放后 sub_430BE0 重分配 + ·0x492530 整拷；
//   源更小 → sub_48C4B0 覆盖已用段后收尾（end = begin + 源元素数×24）。
// ------------------------------------------------------------
int /*thiscall*/ sub_492E80(int this, int pArg2)  // 实现：盒 vector（24B/6float）赋值 operator=（三支）
{
  int v4; // eax
  unsigned int v5; // ecx
  uint32_t *fld_4; // edi
  unsigned int fld_8; // eax
  int v9; // eax
  unsigned int fld_C; // eax
  int v11; // eax
  uint32_t *v12; // [esp+10h] [ebp+8h]

  if ( this == pArg2 )  // 若 this == pArg2
    return this;
  v4 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v4 == 0 || (v5 = (*(uint32_t *)(pArg2 + 8) - v4) / 24) == 0 )  // 若 v4 == 0
  {
    if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
    *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
    return this;
  }
  fld_4 = *(uint32_t **)(this + 4);  // fld_4 = 读 this+4
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 24;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v5 > fld_8 )  // 若 v5 > fld_8
  {
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 24;  // this+12〔nSkillRec12(推断)〕等 2 字段
    else  // 否则分支
      fld_C = 0;  // fld_C=this+12 nSkillRec12
    if ( v5 <= fld_C )  // 若 v5 <= fld_C
    {
      v12 = (uint32_t *)(*(uint32_t *)(pArg2 + 4) + 24 * sub_4FEF30(this));  // pArg2+4〔宿主对象〕
      sub_4919B0(*(uint32_t **)(pArg2 + 4), v12, fld_4);  // 转发 sub_48C4B0（24 字节元素区间深拷贝，6 dword 一组）
      *(uint32_t *)(this + 8) = sub_4FF050(v12, *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 8));  // this+8〔nSkillRec8(推断)〕等 2 字段
      return this;
    }
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    v11 = sub_4FEF30(pArg2);  // v11 = 调 sub_4FEF30 返回值
    if ( (uint8_t)sub_430BE0(v11) != 0 )  // 盒数组预分配（24B 元素）
      *(uint32_t *)(this + 8) = sub_492530(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t *)(this + 4));  // 转发 sub_4FF050（24 字节元素区间拷贝，6 dword 一组）
    return this;
  }
  sub_48C4B0(*(uint32_t **)(pArg2 + 4), *(uint32_t **)(pArg2 + 8), fld_4);  // 24 字节元素区间拷贝（6 dword 一组）
  v9 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v9 != 0 )  // 若 v9 非 0
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 24 * ((*(uint32_t *)(pArg2 + 8) - v9) / 24);  // this+8〔nSkillRec8(推断)〕等 4 字段
  else  // 否则分支
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);  // this+8〔nSkillRec8(推断)〕等 4 字段
  return this;
}



// ------------------------------------------------------------
// 0x493000 sub_493000 —— 盒 vector 中间插入（nArg3 位置插 Block，元素 24B）
// 位置换算 (nArg3-+4)/24 得索引经 *uArg2 回传，实际插入委托 ·0x4929F0。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493000(int *this, uint32_t *uArg2, int nArg3, uint32_t *Block)  // 实现：盒 vector 中间插入（nArg3 位置插 Block，元素 24B）
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 24 != 0 )  // 若 fld_e1 != 0
    v6 = (nArg3 - fld_e1) / 24;  // fld_e1=this+4 宿主对象
  else  // 否则分支
    v6 = 0;
  sub_4929F0(this, nArg3, 1u, Block);  // 盒 vector 插入（元素 24B = 6×float）
  *uArg2 = *(this + 1) + 24 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x493070 sub_493070 —— ★88 字节帧拷贝构造（全字段 +0..+87；+56..71 攻击盒/+72..87 受击盒 vector 深拷贝）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493070(uint32_t *this, int pArg2)  // 实现：88 字节帧拷贝构造（全字段 +0..+87；+56..71 攻击盒/+72..87 受击盒 vector 深拷贝）
{
  *this = *(uint32_t *)pArg2;
  *(this + 1) = *(uint32_t *)(pArg2 + 4);  // this+4〔宿主对象〕
  *(this + 2) = *(uint32_t *)(pArg2 + 8);  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = *(uint32_t *)(pArg2 + 12);  // this+12〔nSkillRec12(推断)〕
  *(this + 4) = *(uint32_t *)(pArg2 + 16);  // this+16〔nChannelTypeSel(推断)〕
  *(this + 5) = *(uint32_t *)(pArg2 + 20);  // this+20〔nPage(推断)〕
  *(this + 6) = *(uint32_t *)(pArg2 + 24);  // this+24〔nPageMax(推断)〕
  *(this + 7) = *(uint32_t *)(pArg2 + 28);  // this+28〔pPanelVec(推断)〕
  *(this + 8) = *(uint32_t *)(pArg2 + 32);  // this+32〔nHeight(推断)〕
  *((uint8_t *)this + 36) = *(uint8_t *)(pArg2 + 36);  // this+36〔nStateWord36(推断)〕
  *(this + 10) = *(uint32_t *)(pArg2 + 40);  // this+40〔bStateSub40(推断)〕
  *(this + 11) = *(uint32_t *)(pArg2 + 44);  // this+44〔nExpireMs(推断)〕
  *(this + 12) = *(uint32_t *)(pArg2 + 48);  // +48 DELAY
  *(this + 13) = *(uint32_t *)(pArg2 + 52);  // +52 DAMAGE TYPE
  sub_492CC0(this + 14, pArg2 + 56);  // +56..71 攻击盒vector 深拷贝
  sub_492CC0(this + 18, pArg2 + 72);  // +72..87 受击盒vector 深拷贝
  return this;
}



// ------------------------------------------------------------
// 0x493120 sub_493120 —— ★88 字节帧拷贝·析构变体（+56/+72 盒 vector 先 sub_492E80 析构再覆盖）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493120(uint32_t *this, int pArg2)  // 实现：88 字节帧拷贝·析构变体（+56/+72 盒 vector 先 sub_492E80 析构再覆盖）
{
  *this = *(uint32_t *)pArg2;
  *(this + 1) = *(uint32_t *)(pArg2 + 4);  // this+4〔宿主对象〕
  *(this + 2) = *(uint32_t *)(pArg2 + 8);  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = *(uint32_t *)(pArg2 + 12);  // this+12〔nSkillRec12(推断)〕
  *(this + 4) = *(uint32_t *)(pArg2 + 16);  // this+16〔nChannelTypeSel(推断)〕
  *(this + 5) = *(uint32_t *)(pArg2 + 20);  // this+20〔nPage(推断)〕
  *(this + 6) = *(uint32_t *)(pArg2 + 24);  // this+24〔nPageMax(推断)〕
  *(this + 7) = *(uint32_t *)(pArg2 + 28);  // this+28〔pPanelVec(推断)〕
  *(this + 8) = *(uint32_t *)(pArg2 + 32);  // this+32〔nHeight(推断)〕
  *((uint8_t *)this + 36) = *(uint8_t *)(pArg2 + 36);  // this+36〔nStateWord36(推断)〕
  *(this + 10) = *(uint32_t *)(pArg2 + 40);  // this+40〔bStateSub40(推断)〕
  *(this + 11) = *(uint32_t *)(pArg2 + 44);  // this+44〔nExpireMs(推断)〕
  *(this + 12) = *(uint32_t *)(pArg2 + 48);  // +48 DELAY
  *(this + 13) = *(uint32_t *)(pArg2 + 52);  // +52 DAMAGE TYPE
  sub_492E80(pArg2 + 56);  // +56..71 攻击盒vector 析构
  sub_492E80(pArg2 + 72);  // +72..87 受击盒vector 析构
  return this;
}



// ------------------------------------------------------------
// 0x4931A0 sub_4931A0 —— 盒 vector 追加一组（6 float=24B；容量不足走 sub_493000 扩容）
// ------------------------------------------------------------
int /*thiscall*/ sub_4931A0(int *this, void *Block)  // 实现：盒 vector 追加一组（6 float=24B；容量不足走 sub_493000 扩容）
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  int result; // eax

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
    fld_e2 = (*(this + 2) - fld_e1) / 24;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 24 )  // 若 fld_e1 == 0
    return sub_493000((int)&Block, *(this + 2), Block);  // 盒 vector 中间插入（nArg3 位置插 Block，元素 24B）
  fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = sub_5044B0(fld_e22, 1, Block);  // result = 调 sub_5044B0 返回值
  *(this + 2) = fld_e22 + 24;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x493230 sub_493230 —— 32 字节元素容器批量追加（构造 nArg2 份源 pArg3）
// 转发 ·0x492DC0，返回末尾位置 nArg1+32×nArg2。
// ------------------------------------------------------------
int /*stdcall*/ sub_493230(int nArg1, int nArg2, size_t *pArg3)  // 实现：32 字节元素容器批量追加（构造 nArg2 份源 pArg3）
{
  sub_492DC0(nArg1, nArg2, pArg3);  // 32 字节元素容器填充构造（nArg2 份，源 pArg3）
  return nArg1 + 32 * nArg2;
}



// ------------------------------------------------------------
// 0x493260 sub_493260 —— 32 字节元素数组析构遍历（区间 [pszArg1,pszArg2)，步长 32）
// 逐元素 sub_501490（std::string 析构）。
// ------------------------------------------------------------
void /*stdcall*/ sub_493260(char *pszArg1, char *pszArg2)  // 实现：32 字节元素数组析构遍历（区间 [pszArg1,pszArg2)，步长 32）
{
  char *i; // esi

  for ( i = pszArg1; i != pszArg2; i += 32 )  // 遍历循环
    sub_501490(i);  // 调 对象析构后释放堆块
}



// ------------------------------------------------------------
// 0x493290 sub_493290 —— 帧数组批量拷贝构造（步长 88B/帧，元素 22×uint32）
// 对 [uArg1,uArg2) 每帧调 ·0x493120（帧拷贝·析构变体，盒 vector 覆盖）；
//   被 ·0x493F30 帧数组批量构造调用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493290(uint32_t *uArg1, uint32_t *uArg2, int nArg3)  // 实现：帧数组批量拷贝构造（步长 88B/帧，元素 22×uint32）
{
  uint32_t *i; // esi
  uint32_t *result; // eax

  for ( i = uArg1; i != uArg2; i += 22 )  // 遍历循环
    result = sub_493120(i, nArg3);  // 88 字节帧拷贝·析构变体（+56/+72 盒 vector 先 sub_492E80 析构再覆盖）
  return result;
}



// ------------------------------------------------------------
// 0x4932C0 sub_4932C0 —— 帧数组正向区间拷贝构造（步长 88B，返回目标尾）
// 与 ·0x493290 同构（差异：源/目标各自按 88B 前进并回传尾指针）；盒 vector 走 ·0x493120 覆盖式拷贝。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_4932C0(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：帧数组正向区间拷贝构造（步长 88B，返回目标尾）
{
  int nArg12; // esi
  uint32_t *uArg32; // edi

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )  // 若 nArg1 == nArg2
    return uArg3;
  uArg32 = uArg3;
  do  // do-while 循环体起点
  {
    sub_493120(uArg32, nArg12);  // 88 字节帧拷贝·析构变体（+56/+72 盒 vector 先 sub_492E80 析构再覆盖）
    nArg12 += 88;
    uArg32 += 22;
  }
  while ( nArg12 != nArg2 );  // 条件循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x493300 sub_493300 —— 帧数组反向区间拷贝构造（从尾到头，步长 88B）
// 与 ·0x4932C0 同构（差异：从 nArg2 往前逐帧拷到 uArg3 之前，用于原地右移腾位）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493300(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：帧数组反向区间拷贝构造（从尾到头，步长 88B）
{
  int nArg22; // esi
  uint32_t *uArg32; // edi

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )  // 若 nArg1 == nArg2
    return uArg3;
  uArg32 = uArg3;
  do  // do-while 循环体起点
  {
    nArg22 -= 88;
    uArg32 -= 22;
    sub_493120(uArg32, nArg22);  // 88 字节帧拷贝·析构变体（+56/+72 盒 vector 先 sub_492E80 析构再覆盖）
  }
  while ( nArg22 != nArg1 );  // 条件循环
  return uArg32;
}



// ------------------------------------------------------------
// 0x493340 sub_493340 —— 帧数组批量拷贝构造（全字段版，调 ·0x493070 深拷贝盒 vector）
// 与 ·0x4932C0 同构（差异：用不带析构的 ·0x493070 构造 +56/+72 盒 vector，适合裸内存）。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493340(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：帧数组批量拷贝构造（全字段版，调 ·0x493070 深拷贝盒 vector）
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )  // 条件循环
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )  // 若 uArg32 有效（非空）
      sub_493070(uArg32, nArg1);  // 88 字节帧拷贝构造（全字段 +0..+87；+56..71 攻击盒/+72..87 受击盒 vector 深拷贝）
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
void /*thiscall*/ sub_493400(int this, int nArg2)  // 实现：应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
{
  int fld_2C; // eax
  int fld_9C; // edi

  if ( nArg2 != *(uint32_t *)(this + 148) )  // this+148〔fAdd148(推断)〕
  {
    fld_2C = *(uint32_t *)(this + 44);  // fld_2C = 读 this+44
    *(uint32_t *)(this + 148) = nArg2;  // this+148〔fAdd148(推断)〕
    fld_9C = *(uint32_t *)(this + 156);  // fld_9C = 读 this+156
    *(uint32_t *)(this + 152) = fld_9C;  // this+152〔nAdd152(推断)〕等 2 字段
    *(uint32_t *)(this + 156) = fld_9C  // this+156〔nAdd156(推断)〕
                            - (uint64_t)((double)*(int *)(88 * nArg2 + fld_2C + 48) / *(float *)(this + 164) * -100.0);  // this+164〔fAdd164(推断)〕
    sub_430B70(this + 60);  // 88B 帧条目复位
    sub_493120(88 * nArg2 + *(uint32_t *)(this + 44));  // 88 字节帧拷贝·析构变体（+56/+72 盒 vector 先 sub_492E80 析构再覆盖）
    *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  }
}



// ------------------------------------------------------------
// 0x493480 sub_493480 —— 帧数组 vector<frame88> 模板实现（assign/erase 族）
// ------------------------------------------------------------
void /*thiscall*/ sub_493480(int *this, int pArg2, unsigned int uArg3, int pArg4)  // 实现：帧数组 vector<frame88> 模板实现（assign/erase 族）
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
  dword_796E502 = dword_796E50;  // dword_796E50（栈检 cookie 值）
  v26[3] = this;
  v32 = 15;
  v31 = 0;
  LOBYTE(v30) = 0;
  sub_4014D0((std::_String_base *)v29, pArg4, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  v33 = *(uint32_t *)(pArg4 + 28);  // pArg4+28〔pPanelVec(推断)〕
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  v36 = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
    fld_e3 = (*(this + 3) - fld_e1) >> 5;  // this+12〔nSkillRec12(推断)〕
  else  // 否则分支
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - fld_e1) >> 5;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 0x7FFFFFF - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_492810(this);  // vector<uint32> 长度溢出兜底（throw length_error，vector<T> too long）
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - fld_e1) >> 5;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = (void *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      Block = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( ((int)fld_e23 - pArg2) >> 5 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v19 = (int)fld_e23 - 32 * uArg3;  // fld_e23=this+8 nSkillRec8
        v20 = sub_4928C0(v19, (int)fld_e23, (int)fld_e23);  // 32 字节元素容器的正向构造循环（assign 版）
        Block2 = Block;
        *(this + 2) = v20;  // this+8〔nSkillRec8(推断)〕
        sub_492DA0(pArg2, v19, Block2);  // 转发 ·0x492880（32 字节元素反向拷贝）
        sub_492D60(pArg2, pArg2 + 32 * uArg3, v29);  // 32 字节元素容器正向区间拷贝（逐元素赋值，非构造版）
      }
      else  // 否则分支
      {
        sub_4928C0(pArg2, (int)fld_e23, pArg2 + 32 * uArg3);  // 32 字节元素容器的正向构造循环（assign 版）
        fld_e24 = uArg3 - ((*(this + 2) - pArg2) >> 5);  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        LOBYTE(v36) = 3;
        sub_493230(fld_e25, fld_e24, v29);  // 32 字节元素容器批量追加（构造 nArg2 份源 pArg3）
        fld_e26 = 32 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        v36 = 0;
        sub_492D60(pArg2, fld_e26 - 32 * uArg3, v29);  // 32 字节元素容器正向区间拷贝（逐元素赋值，非构造版）
      }
    }
    else  // 否则分支
    {
      if ( 0x7FFFFFF - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v10 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else  // 否则分支
        v10 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - fld_e1) >> 5;  // this+8〔nSkillRec8(推断)〕
      else  // 否则分支
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
      {
        if ( fld_e1 != 0 )  // 若 fld_e1 非 0
          fld_e28 = (*(this + 2) - fld_e1) >> 5;  // this+8〔nSkillRec8(推断)〕
        else  // 否则分支
          fld_e28 = 0;  // fld_e28=this+8 nSkillRec8
        v10 = uArg3 + fld_e28;
      }
      v37 = 32 * v10;
      pMem = (char *)operator new(32 * v10);
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;
      pMem2 = (char *)sub_4928C0(fld_e12, pArg2, (int)pMem);  // 32 字节元素容器的正向构造循环（assign 版）
      sub_492DC0((int)pMem2, uArg3, (int)v29);  // 32 字节元素容器填充构造（nArg2 份，源 pArg3）
      fld_e29 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
      pMem2 += 32 * uArg3;
      sub_4928C0(pArg2, fld_e29, (int)pMem2);  // 32 字节元素容器的正向构造循环（assign 版）
      fld_e13 = (void *)*(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != nullptr )  // 若 fld_e13 有效（非空）
        fld_e210 = (*(this + 2) - (int)fld_e13) >> 5;  // this+8〔nSkillRec8(推断)〕
      else  // 否则分支
        fld_e210 = 0;  // fld_e210=this+8 nSkillRec8
      v16 = fld_e210 + uArg3;
      if ( fld_e13 != nullptr )  // 若 fld_e13 有效（非空）
      {
        sub_493260(fld_e13, *(this + 2));  // 32 字节元素数组析构遍历（区间 [pszArg1,pszArg2)，步长 32）
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      }
      *(this + 3) = (int)&pMem[v37];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&pMem[32 * v16];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)pMem;  // this+4〔宿主对象〕
    }
  }
  if ( v32 >= 0x10 )  // 若 v32 >= 0x10
    j__free(v30);  // 调 j__free（堆释放）
}


// ------------------------------------------------------------
// 0x493740 sub_493740 —— 转发 ·0x4932C0（帧数组正向拷）
// 帧容器接口族占位，被 ·0x493DB0 帧数组 assign 调用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493740(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：转发 ·0x4932C0（帧数组正向拷）
{
  return sub_4932C0(nArg1, nArg2, uArg3);  // 帧数组正向区间拷贝构造（步长 88B，返回目标尾）
}



// ------------------------------------------------------------
// 0x493760 sub_493760 —— 转发 ·0x493300（帧数组反向拷）
// 帧容器接口族占位，被 ·0x493F30 帧数组批量构造调用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_493760(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：转发 ·0x493300（帧数组反向拷）
{
  return sub_493300(nArg1, nArg2, uArg3);  // 帧数组反向区间拷贝构造（从尾到头，步长 88B）
}



// ------------------------------------------------------------
// 0x493780 sub_493780 —— 帧数组填充构造（nArg2 帧，源 uArg1，步长 88B）
// 逐份调 ·0x493070（全字段拷贝含盒 vector）写 nArg3 起的连续内存；被 ·0x493B40 在尾部批量建帧。
// ------------------------------------------------------------
void /*cdecl*/ sub_493780(uint32_t *uArg1, int nArg2, int nArg3)  // 实现：帧数组填充构造（nArg2 帧，源 uArg1，步长 88B）
{
  uint32_t *uArg12; // esi
  uint32_t v5[5]; // [esp+0h] [ebp-20h] BYREF
  int v6; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v5[4] = v5;
  v5[3] = uArg1;
  v6 = 0;
  while ( nArg2 != 0 )  // 条件循环
  {
    LOBYTE(v6) = 1;
    if ( uArg12 != nullptr )  // 若 uArg12 有效（非空）
      sub_493070(uArg12, nArg3);  // 88 字节帧拷贝构造（全字段 +0..+87；+56..71 攻击盒/+72..87 受击盒 vector 深拷贝）
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
char /*thiscall*/ sub_493840(int this)  // 实现：帧推进（研究§26）
{
  int fld_D4; // ecx
  int fld_20; // ebx
  unsigned int fld_2C2; // eax
  int fld_94; // edi
  int fld_2C; // eax

  fld_D4 = *(uint32_t *)(this + 212);  // fld_D4 = 读 this+212
  if ( fld_D4 != 0 )  // 若 fld_D4 非 0
    fld_20 = sub_4910A0(fld_D4);  // 沿 +212 同步源链上溯，返回链尾对象的累计播放时刻（+32）
  else  // 否则分支
    fld_20 = *(uint32_t *)(this + 32);  // fld_20 = 读 this+32
  LOBYTE(fld_2C2) = *(uint8_t *)(this + 170);  // this+680〔nSnapshot680〕
  fld_94 = *(uint32_t *)(this + 148);  // fld_94 = 读 this+148
  if ( (uint8_t)fld_2C2 == 0 )
  {
    while ( fld_20 >= *(uint32_t *)(this + 156) )  // 累计时刻 ≥ 帧尾(+156) → 切帧
    {
      fld_2C = *(uint32_t *)(this + 44);  // fld_2C = 读 this+44
      if ( fld_2C != 0 )  // 若 fld_2C 非 0
        fld_2C = (*(uint32_t *)(this + 48) - fld_2C) / 88;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
      if ( fld_94 == fld_2C - 1 )  // fld_94=this+148 第 4 组·+802 增量子倍率
      {
        LOBYTE(fld_2C2) = *(uint8_t *)(this + 160);  // this+160〔fAdd160(推断)〕
        if ( (uint8_t)fld_2C2 == 0 )
        {
          *(uint8_t *)(this + 170) = 1;  // 播完标志（无[LOOP]到尾帧）
          return fld_2C2;
        }
        fld_2C2 = *(uint32_t *)(this + 44);  // fld_2C2 = 读 this+44
        if ( fld_2C2 == 0 )  // 若 fld_2C2 为 0
          return fld_2C2;  // fld_2C2=this+44 剩余时间 ms
        fld_2C2 = (int)(*(uint32_t *)(this + 48) - fld_2C2) / 88;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
        if ( fld_2C2 <= 1 )  // 若 fld_2C2 <= 1
          return fld_2C2;  // fld_2C2=this+48 pCmdVecBegin48
        fld_94 = 0;  // fld_94=this+148 第 4 组·+802 增量子倍率
      }
      else  // 否则分支
      {
        ++fld_94;  // fld_94=this+148 第 4 组·+802 增量子倍率
      }
      sub_493400(this, fld_94);  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
      LOBYTE(fld_2C2) = *(uint8_t *)(this + 170);  // this+680〔nSnapshot680〕
      if ( (uint8_t)fld_2C2 != 0 )  // fld_2C2=this+48 pCmdVecBegin48
        return fld_2C2;  // fld_2C2=this+48 pCmdVecBegin48
    }
  }
  return fld_2C2;  // fld_2C2=this+48 pCmdVecBegin48
}



// ------------------------------------------------------------
// 0x4938F0 sub_4938F0 —— ★播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4938F0(int this)  // 实现：播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
{
  int fld_D4; // ecx
  char fld_A9; // al
  uint32_t *result; // eax
  uint32_t *v5; // esi

  fld_D4 = *(uint32_t *)(this + 212);  // fld_D4 = 读 this+212
  if ( fld_D4 != 0 )  // 若 fld_D4 非 0
    fld_A9 = sub_4910C0(fld_D4);  // 沿 +212 同步源链上溯，返回链尾对象的 +169（暂停/冻结位）
  else  // 否则分支
    fld_A9 = *(uint8_t *)(this + 169);  // fld_A9 = 读 this+169
  if ( fld_A9 == 0 && sub_4910E0(this) != 0 || *(uint32_t *)(this + 148) == -1 )  // 帧时刻推进（返回 1 表示时刻发生位移）
  {
    sub_493840(this);  // 帧推进（研究§26）
    sub_4919D0(this);  // 帧间插值核心（研究§11/§26）
  }
  result = *(uint32_t **)(this + 204);  // result = 读 this+204
  v5 = (uint32_t *)*result;  // result=this+204 子动画链指针
  if ( (uint32_t *)*result != result )  // result=this+204 子动画链指针
  {
    do  // do-while 循环体起点
    {
      result = (uint32_t *)sub_4938F0(v5[3]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != *(uint32_t **)(this + 204) );  // 条件循环
  }
  return result;  // result=this+204 子动画链指针
}



// ------------------------------------------------------------
// 0x493960 sub_493960 —— 帧数组前插（在 +8 尾之前腾位并回写尾指针）
// 把 uArg3 起的帧序列右移到 nArg4 之后（sub_4932C0），旧区间用 sub_42AA10 析构回收，
//   更新 +8 尾指针，经 *uArg2 回传目标首址。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_493960(int *this, uint32_t *uArg2, uint32_t *uArg3, int nArg4)  // 实现：帧数组前插（在 +8 尾之前腾位并回写尾指针）
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
    fld_e2 = sub_4932C0(nArg4, *(this + 2), uArg3);  // 帧数组正向区间拷贝构造（步长 88B，返回目标尾）
    fld_e22 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
    fld_e23 = fld_e2;
    for ( i = fld_e2; i != fld_e22; i += 22 )  // 遍历循环
      sub_42AA10(i);  // 双缓冲释清（+60/+76 组）
    uArg32 = uArg3;
    pThis[2] = (int)fld_e23;
  }
  *uArg2 = uArg32;
  return uArg2;
}



// ------------------------------------------------------------
// 0x4939C0 sub_4939C0 —— 转发 ·0x493340（帧数组全字段拷贝构造）
// 帧容器接口族占位。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_4939C0(int nArg1, int nArg2, uint32_t *uArg3)  // 实现：转发 ·0x493340（帧数组全字段拷贝构造）
{
  return sub_493340(nArg1, nArg2, uArg3);  // 帧数组批量拷贝构造（全字段版，调 ·0x493070 深拷贝盒 vector）
}



// ------------------------------------------------------------
// 0x4939E0 sub_4939E0 —— 播放/暂停级联（递归子链 +204）
// ------------------------------------------------------------
char /*thiscall*/ sub_4939E0(int this, char pszArg2)  // 实现：播放/暂停级联（递归子链 +204）
{
  char result; // al
  char fld_A9; // bl
  int fld_20; // edi

  result = pszArg2;
  fld_A9 = *(uint8_t *)(this + 169);  // fld_A9 = 读 this+169
  if ( pszArg2 != fld_A9 )  // 若 pszArg2 != fld_A9
  {
    if ( pszArg2 != 0 )  // 若 pszArg2 非 0
    {
      result = sub_4938F0(this);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      *(uint8_t *)(this + 169) = pszArg2;  // this+676〔nResetFlag676(推断)〕
    }
    else  // 否则分支
    {
      if ( *(uint32_t *)(this + 212) != 0 )  // this+212〔nField212(推断)〕
        fld_20 = sub_4910A0();  // 沿 +212 同步源链上溯，返回链尾对象的累计播放时刻（+32）
      else  // 否则分支
        fld_20 = *(uint32_t *)(this + 32);  // fld_20 = 读 this+32
      sub_4926A0(this);  // 帧游标复位（+44 帧数组；递归子链 +204）
      *(uint32_t *)(this + 28) = fld_20;  // this+28〔pPanelVec(推断)〕等 2 字段
      sub_4910E0(this);  // 帧时刻推进（返回 1 表示时刻发生位移）
      result = sub_4939E0(fld_A9);  // 播放/暂停级联（递归子链 +204）
      *(uint8_t *)(this + 169) = 0;  // this+676〔nResetFlag676(推断)〕
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x493A60 sub_493A60 —— 时间推进包装（累计 +32；+212 同步源优先）
// ------------------------------------------------------------
char /*thiscall*/ sub_493A60(int this, int nArg2)  // 实现：时间推进包装（累计 +32；+212 同步源优先）
{
  int fld_D4; // ecx
  char fld_A92; // al
  int fld_1C; // eax
  char fld_A9; // [esp+4h] [ebp-4h]

  fld_A9 = *(uint8_t *)(this + 169);  // fld_A9 = 读 this+169
  sub_4926A0(this);  // 帧游标复位（+44 帧数组；递归子链 +204）
  *(uint32_t *)(this + 28) = nArg2;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint8_t *)(this + 168) = 1;  // this+168〔pAppendVec(推断)〕等 2 字段
  sub_698F90(this, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_D4 = *(uint32_t *)(this + 212);  // fld_D4 = 读 this+212
  if ( fld_D4 != 0 )  // 若 fld_D4 非 0
    fld_A92 = sub_4910C0(fld_D4);  // 沿 +212 同步源链上溯，返回链尾对象的 +169（暂停/冻结位）
  else  // 否则分支
    fld_A92 = *(uint8_t *)(this + 169);  // fld_A92 = 读 this+169
  if ( fld_A92 == 0 )  // 若 fld_A92 为 0
  {
    fld_1C = *(uint32_t *)(this + 28) + sub_699000(this);  // 【clock_now(clk)】
    if ( fld_1C != *(uint32_t *)(this + 32) )  // this+32〔nHeight(推断)〕等 2 字段
      *(uint32_t *)(this + 32) = fld_1C;  // this+32〔nHeight(推断)〕等 2 字段
  }
  return sub_4939E0(this, fld_A9);  // 播放/暂停级联（递归子链 +204）
}



// ------------------------------------------------------------
// 0x493AD0 sub_493AD0 —— 32 字节元素容器末尾追加（容量够就地写，不够走 ·0x493480 扩容）
// 元素 32B；被 ·0x494680 主解析器用于追加帧别名/资源名条目。
// ------------------------------------------------------------
void /*thiscall*/ sub_493AD0(int this, size_t *pArg2)  // 实现：32 字节元素容器末尾追加（容量够就地写，不够走 ·0x493480 扩容）
{
  int fld_4; // edx
  unsigned int fld_8; // ecx
  int fld_82; // edi

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( fld_4 != 0 && fld_8 < (*(uint32_t *)(this + 12) - fld_4) >> 5 )  // 若 fld_4 != 0
  {
    fld_82 = *(uint32_t *)(this + 8);  // fld_82 = 读 this+8
    sub_492DC0(fld_82, 1, pArg2);  // 32 字节元素容器填充构造（nArg2 份，源 pArg3）
    *(uint32_t *)(this + 8) = fld_82 + 32;  // this+8〔nSkillRec8(推断)〕等 2 字段
  }
  else  // 否则分支
  {
    sub_493480(this, *(size_t **)(this + 8), 1u, pArg2);  // 帧数组 vector<frame88> 模板实现（assign/erase 族）
  }
}



// ------------------------------------------------------------
// 0x493B40 sub_493B40 —— 帧数组尾部批量构造并返回新尾（pArg1+22×nArg2）
// 转发 ·0x493780（全字段拷贝）后回传尾指针，供 ·0x493F30 续写。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_493B40(uint32_t *pArg1, int nArg2, int nArg3)  // 实现：帧数组尾部批量构造并返回新尾（pArg1+22×nArg2）
{
  sub_493780(pArg1, nArg2, nArg3);  // 帧数组填充构造（nArg2 帧，源 uArg1，步长 88B）
  return &pArg1[22 * nArg2];
}



// ------------------------------------------------------------
// 0x493B70 sub_493B70 —— 同步源模式下重算累计时间（sub_493A60 链）
// ------------------------------------------------------------
char /*thiscall*/ sub_493B70(int this)  // 实现：同步源模式下重算累计时间（sub_493A60 链）
{
  int fld_D4; // ecx
  char fld_A9; // al
  int fld_1C; // eax

  *(uint8_t *)(this + 168) = 1;  // this+168〔pAppendVec(推断)〕等 2 字段
  sub_698F90(this, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_D4 = *(uint32_t *)(this + 212);  // fld_D4 = 读 this+212
  if ( fld_D4 != 0 )  // 若 fld_D4 非 0
    fld_A9 = sub_4910C0(fld_D4);  // 沿 +212 同步源链上溯，返回链尾对象的 +169（暂停/冻结位）
  else  // 否则分支
    fld_A9 = *(uint8_t *)(this + 169);  // fld_A9 = 读 this+169
  if ( fld_A9 == 0 )  // 若 fld_A9 为 0
  {
    fld_1C = *(uint32_t *)(this + 28) + sub_699000(this);  // 【clock_now(clk)】
    if ( fld_1C != *(uint32_t *)(this + 32) )  // this+32〔nHeight(推断)〕等 2 字段
      *(uint32_t *)(this + 32) = fld_1C;  // this+32〔nHeight(推断)〕等 2 字段
  }
  return sub_493A60(this, *(uint32_t *)(this + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
}



// ------------------------------------------------------------
// 0x493BD0 sub_493BD0 —— 动画对象复位
//   +148=-1 帧索引、+160=0 [LOOP]、+161=1 [SHADOW] 默认开、
//   +164=1120403456(100.0f) 播放速率默认 100、+200 list 初始化（子动画链）、+212=0。
// ------------------------------------------------------------
int /*thiscall*/ sub_493BD0(int this)  // 实现：动画对象复位
{
  int result; // eax

  sub_699070(1);  // 【clock_bind_domain(clk, newDomainId)】
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = -1;  // this+32〔nHeight(推断)〕等 2 字段
  sub_42AF40(this + 40);  // 88 字节元素数组析构
  sub_430B70(this + 60);  // 88B 帧条目复位
  *(uint32_t *)(this + 148) = -1;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 0;  // this+156〔nAdd156(推断)〕
  *(uint8_t *)(this + 160) = 0;  // [LOOP] 默认关
  *(uint8_t *)(this + 161) = 1;  // [SHADOW] 默认开
  *(uint32_t *)(this + 164) = 1120403456;  // 播放速率=100.0f（0x42C80000）
  *(uint8_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint8_t *)(this + 169) = 0;  // this+676〔nResetFlag676(推断)〕
  *(uint8_t *)(this + 170) = 0;  // this+680〔nSnapshot680〕
  *(uint8_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  *(uint8_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint32_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
  *(uint8_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = -1;  // this+192〔nDlgId(推断)〕
  *(uint8_t *)(this + 196) = 0;
  result = sub_6569D0(this + 200);  // result = 调 sub_6569D0 返回值
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x493C80 sub_493C80 —— 析构（帧数组 +40..55、子链 list +200..211 释放）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_493C80(void ****this)  // 实现：析构（帧数组 +40..55、子链 list +200..211 释放）
{
  void ***fld_e53; // ecx
  void ****fld_e51; // ecx
  void ***v4; // eax
  void ****fld_e512; // ecx
  void ***result; // eax
  bool fld_e513; // zf
  void ***v8; // edi

  sub_42AF40(this + 10);  // 88 字节元素数组析构
  sub_430B70(this + 15);  // 88B 帧条目复位
  fld_e53 = *(this + 53);  // this+212〔nField212(推断)〕
  if ( fld_e53 != nullptr )  // 若 fld_e53 有效（非空）
    sub_492980(fld_e53, this);  // 子链节点按对象指针摘除（组件槽卸载/释放）
  fld_e51 = (void ****)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  v4 = *fld_e51;  // fld_e51=this+204 pSubAnim204
  if ( *fld_e51 != (void ***)fld_e51 )  // fld_e51=this+204 pSubAnim204
  {
    do  // do-while 循环体起点
    {
      v4[3][53] = nullptr;  // v4[3][53] = 空指针
      v4 = (void ***)*v4;
    }
    while ( v4 != *(this + 51) );  // 条件循环
  }
  fld_e512 = (void ****)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  result = *fld_e512;  // fld_e512=this+204 pSubAnim204
  *fld_e512 = (void ***)fld_e512;  // fld_e512=this+204 pSubAnim204
  (*(this + 51))[1] = (void **)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  fld_e513 = result == *(this + 51);  // this+204〔pSubAnim204(推断)〕
  *(this + 52) = nullptr;  // this+208〔nField208(推断)〕
  if ( !fld_e513 )  // fld_e513=this+204 pSubAnim204
  {
    do  // do-while 循环体起点
    {
      v8 = (void ***)*result;
      j__free(result);  // 调 j__free（堆释放）
      result = v8;
    }
    while ( v8 != *(this + 51) );  // 条件循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x493D00 sub_493D00 —— ★变速（研究§26）
//   新速率写 +164；累计时长(+32)按 旧/新 速率比换算（sub_493A60），同步源(+212)模式走
//   sub_493B70；随后递归子链(+204)同速、sub_4938F0 重推帧。速率 0 视为 1。
// ------------------------------------------------------------
void /*thiscall*/ sub_493D00(int this, float fArg2)  // 实现：变速（研究§26）
{
  double fld_A4; // st7
  uint32_t **fld_CC; // eax
  uint32_t *v5; // esi

  if ( fArg2 == 0.0 )
    fArg2 = 1.0;
  if ( fArg2 != *(float *)(this + 164) )  // 速率槽 +164
  {
    fld_A4 = *(float *)(this + 164);  // this+164〔fAdd164(推断)〕
    *(float *)(this + 164) = fArg2;  // this+164〔fAdd164(推断)〕
    if ( *(uint32_t *)(this + 212) != 0 )  // this+212〔nField212(推断)〕
      sub_493B70(this);  // 同步源模式下重算累计时间（sub_493A60 链）
    else  // 否则分支
      sub_493A60(this, (uint64_t)((double)*(int *)(this + 32) / fArg2 * fld_A4));  // 累计时长(+32)按 旧/新 速率比换算，不跳帧
    fld_CC = *(uint32_t ***)(this + 204);  // 子动画链 +204
    v5 = *fld_CC;  // fld_CC=this+204 子动画链指针
    if ( *fld_CC != fld_CC )  // fld_CC=this+204 子动画链指针
    {
      do  // do-while 循环体起点
      {
        sub_493D00(fArg2);  // 变速（研究§26）
        v5 = (uint32_t *)*v5;
      }
      while ( v5 != *(uint32_t **)(this + 204) );  // 条件循环
    }
    sub_4938F0(this);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
  }
}



// ============================================================
// §G 0x493DB0-0x494680  帧数组批量操作 + 加载准备
// ============================================================
// ------------------------------------------------------------
// 0x493DB0 sub_493DB0 —— 帧数组 assign（源 a2 的 +44..+48 区间，元素 88B，含盒 vector 深拷贝）
// ------------------------------------------------------------
int /*thiscall*/ sub_493DB0(int this, int pArg2)  // 实现：帧数组 assign（源 a2 的 +44..+48 区间，元素 88B，含盒 vector 深拷贝）
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

  if ( this == pArg2 )  // 若 this == pArg2
    return this;
  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == 0 || (v4 = (*(uint32_t *)(pArg2 + 8) - v3) / 88) == 0 )  // 若 v3 == 0
  {
    sub_42AF40(this);  // 88 字节元素数组析构
    return this;
  }
  fld_4 = *(uint32_t **)(this + 4);  // fld_4 = 读 this+4
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) / 88;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v4 > fld_8 )  // 若 v4 > fld_8
  {
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
      fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) / 88;  // this+12〔nSkillRec12(推断)〕等 2 字段
    else  // 否则分支
      fld_C = 0;  // fld_C=this+12 nSkillRec12
    if ( v4 <= fld_C )  // 若 v4 <= fld_C
    {
      v11 = *(uint32_t *)(pArg2 + 4) + 88 * sub_42FC70(this);  // 88B 元素计数（+4 组）
      sub_493740(*(uint32_t *)(pArg2 + 4), v11, fld_4);  // 转发 ·0x4932C0（帧数组正向拷）
      *(uint32_t *)(this + 8) = sub_493340(v11, *(uint32_t *)(pArg2 + 8), *(uint32_t **)(this + 8));  // 帧数组批量拷贝构造（全字段版，调 ·0x493070 深拷贝盒 vector）
      return this;
    }
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    {
      sub_42AF10(fld_4, *(uint32_t *)(this + 8));  // 区间析构（步长 88）
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    }
    v12 = sub_42FC70(pArg2);  // 88B 元素计数（+4 组）
    if ( (uint8_t)sub_430C30(v12) != 0 )  // 帧数组预分配（88B 元素）
      *(uint32_t *)(this + 8) = sub_4939C0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), *(uint32_t **)(this + 4));  // 转发 ·0x493340（帧数组全字段拷贝构造）
    return this;
  }
  v8 = sub_4932C0(*(uint32_t *)(pArg2 + 4), *(uint32_t *)(pArg2 + 8), fld_4);  // 帧数组正向区间拷贝构造（步长 88B，返回目标尾）
  sub_42AF10(v8, *(uint32_t *)(this + 8));  // 区间析构（步长 88）
  v9 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v9 != 0 )  // 若 v9 非 0
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4) + 88 * ((*(uint32_t *)(pArg2 + 8) - v9) / 88);  // this+8〔nSkillRec8(推断)〕等 4 字段
  else  // 否则分支
    *(uint32_t *)(this + 8) = *(uint32_t *)(this + 4);  // this+8〔nSkillRec8(推断)〕等 4 字段
  return this;
}



// ------------------------------------------------------------
// 0x493F30 sub_493F30 —— 帧数组批量构造（sub_493070/493120/493340 复制族 + 尾部裁剪）
// ------------------------------------------------------------
void /*thiscall*/ sub_493F30(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 实现：帧数组批量构造（sub_493070/493120/493340 复制族 + 尾部裁剪）
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
  sub_493070(nArg4);  // 88 字节帧拷贝构造（全字段 +0..+87；+56..71 攻击盒/+72..87 受击盒 vector 深拷贝）
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  fld_e3 = 0;
  v31 = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
    fld_e3 = (*(this + 3) - fld_e1) / 88;  // this+12〔nSkillRec12(推断)〕
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - fld_e1) / 88;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 48806446 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_430A90(this);  // vector 超长异常（length_error）
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - fld_e1) / 88;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
      fld_e232 = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( (fld_e23 - pArg2) / 88 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v32 = fld_e23 - 88 * uArg3;  // fld_e23=this+8 nSkillRec8
        *(this + 2) = sub_493340(v32, fld_e23, fld_e23);  // 帧数组批量拷贝构造（全字段版，调 ·0x493070 深拷贝盒 vector）
        sub_493760(pArg2, v32, fld_e232);  // 转发 ·0x493300（帧数组反向拷）
        sub_493290(pArg2, pArg2 + 88 * uArg3, v23);  // 帧数组批量拷贝构造（步长 88B/帧，元素 22×uint32）
      }
      else  // 否则分支
      {
        sub_493340(pArg2, fld_e23, pArg2 + 88 * uArg3);  // 帧数组批量拷贝构造（全字段版，调 ·0x493070 深拷贝盒 vector）
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 88;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        LOBYTE(v31) = 3;
        sub_493B40(fld_e25, fld_e24, v23);  // 帧数组尾部批量构造并返回新尾（pArg1+22×nArg2）
        fld_e26 = 88 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        v31 = 0;
        sub_493290(pArg2, fld_e26 - 88 * uArg3, v23);  // 帧数组批量拷贝构造（步长 88B/帧，元素 22×uint32）
      }
    }
    else  // 否则分支
    {
      if ( 48806446 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v10 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else  // 否则分支
        v10 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - fld_e1) / 88;  // this+8〔nSkillRec8(推断)〕
      else  // 否则分支
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v10 = uArg3 + sub_42FC70(this);  // 88B 元素计数（+4 组）
      v34 = 88 * v10;
      pMem = (char *)operator new(88 * v10);
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      Block = pMem;
      LOBYTE(v31) = 1;
      v33 = sub_493340(fld_e12, pArg2, pMem);  // 帧数组批量拷贝构造（全字段版，调 ·0x493070 深拷贝盒 vector）
      sub_493780(v33, uArg3, v23);  // 帧数组填充构造（nArg2 帧，源 uArg1，步长 88B）
      sub_493340(pArg2, *(this + 2), 88 * uArg3 + v33);  // 帧数组批量拷贝构造（全字段版，调 ·0x493070 深拷贝盒 vector）
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != 0 )  // 若 fld_e13 非 0
        fld_e13 = (*(this + 2) - fld_e13) / 88;  // this+8〔nSkillRec8(推断)〕
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e14 != 0 )  // 若 fld_e14 非 0
      {
        sub_42AF10(fld_e14, *(this + 2));  // 区间析构（步长 88）
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      }
      *(this + 3) = (int)&pMem[v34];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&pMem[88 * v14];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)pMem;  // this+4〔宿主对象〕
    }
  }
  if ( v25 != nullptr )  // 若 v25 有效（非空）
    j__free(v25);  // 调 j__free（堆释放）
  v25 = nullptr;  // v25 = 空指针
  v26 = 0;
  v27 = 0;
  if ( v24 != nullptr )  // 若 v24 有效（非空）
    j__free(v24);  // 调 j__free（堆释放）
}


// ------------------------------------------------------------
// 0x494240 sub_494240 —— 子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
// ------------------------------------------------------------
void /*thiscall*/ sub_494240(int this, int nArg2, int pArg3)  // 实现：子链变换/重建（sub_52DAA0；+212 同步源 → 复位/变速跟随）
{
  uint32_t *fld_CC; // eax
  uint32_t *v5; // esi
  bool v6; // zf
  int v7; // edi
  uint32_t v8[2]; // [esp+4h] [ebp-8h] BYREF

  if ( pArg3 != 0 )  // 若 pArg3 非 0
  {
    v8[1] = pArg3;
    fld_CC = *(uint32_t **)(this + 204);  // fld_CC = 读 this+204
    v5 = (uint32_t *)*fld_CC;  // fld_CC=this+204 子动画链指针
    v6 = *fld_CC == (uint32_t)fld_CC;  // fld_CC=this+204 子动画链指针
    v8[0] = nArg2;
    if ( !v6 )
    {
      do  // do-while 循环体起点
      {
        if ( v5[2] > nArg2 )
          break;  // 跳出循环/分支
        v5 = (uint32_t *)*v5;
      }
      while ( v5 != fld_CC );  // 条件循环
    }
    v7 = sub_52DAA0(v5, v5[1], v8);  // v7 = 调 sub_52DAA0 返回值
    sub_492780(1);  // std::list 节点计数累加（cached size 位于 +8）
    v5[1] = v7;
    **(uint32_t **)(v7 + 4) = v7;
    *(uint32_t *)(pArg3 + 212) = this;  // pArg3+212〔nField212(推断)〕
    sub_4926A0(pArg3);  // 帧游标复位（+44 帧数组；递归子链 +204）
    sub_493D00(pArg3, *(float *)(this + 164));  // 变速（研究§26）
  }
}



// ------------------------------------------------------------
// 0x4942D0 sub_4942D0 —— ★子链整体销毁（+204 链：清同步源、释放对象、回收节点）
//   ① 逐节点：node+12 对象的 +212 同步源清 0，sub_42AF90 + sub_657740(obj,228) 释放对象，
//      node+12 清 0；② +204 链头自环（置空链）、+208 计数归 0；③ j__free 逐个释放节点。
//   被 broadcast_debug 的 sub_42B040（三槽销毁族）三次调用。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4942D0(uint32_t *this)  // 实现：子链整体销毁（+204 链：清同步源、释放对象、回收节点）
{
  uint32_t *fld_e51; // eax
  uint32_t *v3; // esi
  int v4; // ebx
  uint32_t **fld_e512; // ecx
  uint32_t *result; // eax
  bool fld_e513; // zf
  uint32_t *v8; // esi

  fld_e51 = (uint32_t *)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  v3 = (uint32_t *)*fld_e51;  // fld_e51=this+204 pSubAnim204
  if ( (uint32_t *)*fld_e51 != fld_e51 )  // fld_e51=this+204 pSubAnim204
  {
    do  // do-while 循环体起点
    {
      *(uint32_t *)(v3[3] + 212) = 0;
      v4 = v3[3];  // v4 = 取 v3[3]
      if ( v4 != 0 )  // 若 v4 非 0
      {
        sub_42AF90((void **)v3[3]);  // 帧对象析构（帧数组 + 元素数组）
        sub_657740(v4, 228);  // 池化结点弹出（写魔术标记后挂入链头）
      }
      v3[3] = 0;
      v3 = (uint32_t *)*v3;
    }
    while ( v3 != (uint32_t *)*(this + 51) );  // 条件循环
  }
  fld_e512 = (uint32_t **)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  result = *fld_e512;  // fld_e512=this+204 pSubAnim204
  *fld_e512 = fld_e512;  // fld_e512=this+204 pSubAnim204
  *(uint32_t *)(*(this + 51) + 4) = *(this + 51);  // this+204〔pSubAnim204(推断)〕
  fld_e513 = result == (uint32_t *)*(this + 51);  // this+204〔pSubAnim204(推断)〕
  *(this + 52) = 0;  // this+208〔nField208(推断)〕
  if ( !fld_e513 )  // fld_e513=this+204 pSubAnim204
  {
    do  // do-while 循环体起点
    {
      v8 = (uint32_t *)*result;
      j__free(result);  // 调 j__free（堆释放）
      result = v8;
    }
    while ( v8 != (uint32_t *)*(this + 51) );  // 条件循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x494370 sub_494370 —— 装载帧数组副本并重取图像句柄（帧+4 → sub_418DD0 刷新帧+0）
// ------------------------------------------------------------
void /*thiscall*/ sub_494370(int this, int pArg2)  // 实现：装载帧数组副本并重取图像句柄（帧+4 → sub_418DD0 刷新帧+0）
{
  int pThis_28; // edi
  unsigned int v3; // ebx
  int v4; // eax
  int *fld_2C; // esi
  uint32_t *v6; // eax
  unsigned int v7; // [esp-Ch] [ebp-14h]
  int i; // [esp+10h] [ebp+8h]

  if ( pArg2 != 0 )  // 若 pArg2 非 0
  {
    *(uint8_t *)(this + 160) = *(uint8_t *)(pArg2 + 160);  // this+160〔fAdd160(推断)〕
    pThis_28 = this + 40;
    *(uint8_t *)(this + 161) = *(uint8_t *)(pArg2 + 161);  // this+644〔nFrameOverrideTime(推断)〕
    sub_42AF40(this + 40);  // 88 字节元素数组析构
    sub_493DB0(pThis_28, pArg2 + 40);  // 帧数组 assign（源 a2 的 +44..+48 区间，元素 88B，含盒 vector 深拷贝）
    v3 = 0;
    for ( i = 0; ; i += 88 )  // 遍历循环
    {
      v4 = *(uint32_t *)(pThis_28 + 4);  // pThis_28+4〔宿主对象〕
      if ( v4 == 0 || v3 >= (*(uint32_t *)(pThis_28 + 8) - v4) / 88 )  // 若 v4 == 0
        break;  // 跳出循环/分支
      fld_2C = (int *)(*(uint32_t *)(this + 44) + i);  // this+44〔nExpireMs(推断)〕等 2 字段
      if ( fld_2C[1] != -1 )  // fld_2C=this+44 nExpireMs
      {
        v7 = fld_2C[2];  // v7 = 取 fld_2C[2]
        v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, fld_2C[1]);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
        *fld_2C = sub_418DD0(v6, v7);  // 调 资源句柄 (101)
      }
      ++v3;
    }
  }
}



// ------------------------------------------------------------
// 0x494420 sub_494420 —— 帧数组构建（每帧 22×uint32=88B；sub_493960/493F30）
// ------------------------------------------------------------
void /*thiscall*/ sub_494420(  // 帧数组构建（每帧 22×uint32=88B；sub_493960/493F30）
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

  v24 = *(this + 1);  // this+4〔宿主对象〕
  if ( v24 != 0 )  // 若 v24 非 0
    v25 = (*(this + 2) - v24) / 88;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    v25 = 0;  // v25=this+8 nSkillRec8
  if ( v25 >= a2 )  // 若 v25 >= a2
  {
    if ( v24 != 0 && a2 < (*(this + 2) - v24) / 88 )  // 若 v24 != 0
      sub_493960(this, &a2, (uint32_t *)(v24 + 88 * a2), *(this + 2));  // 帧数组前插（在 +8 尾之前腾位并回写尾指针）
  }
  else  // 否则分支
  {
    if ( v24 != 0 )  // 若 v24 非 0
      v26 = (*(this + 2) - v24) / 88;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      v26 = 0;  // v26=this+8 nSkillRec8
    sub_493F30(this, (char *)*(this + 2), a2 - v26, (int)&a3);  // 帧数组批量构造（sub_493070/493120/493340 复制族 + 尾部裁剪）
  }
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 j__free（堆释放）
  if ( a18 != nullptr )  // 若 a18 有效（非空）
    j__free(a18);  // 调 j__free（堆释放）
}



// ------------------------------------------------------------
// 0x494500 sub_494500 —— 子链按序号定向销毁（node+8 == nArg2）
//   遍历 +204 链（node+8 有序，> nArg2 即提前返回）：命中则清对象 +212、sub_42AF90 +
//   sub_657740(obj,228) 释放、摘链、j__free 节点、+208 计数减 1。
//   与 ·0x492980 同构（差异：键为 node+8 序号且带序剪枝）。
// ------------------------------------------------------------
int /*thiscall*/ sub_494500(int *this, int nArg2)  // 实现：子链按序号定向销毁（node+8 == nArg2）
{
  int result; // eax
  uint32_t *v4; // esi
  int v5; // edi
  uint32_t *v6; // edi

  result = *(this + 51);  // this+204〔pSubAnim204(推断)〕
  v4 = *(uint32_t **)result;  // result=this+204 pSubAnim204
  if ( *(uint32_t *)result != result )  // result=this+204 pSubAnim204
  {
    do  // do-while 循环体起点
    {
      result = v4[2];  // result = 取 v4[2]
      if ( result == nArg2 )  // 若 result == nArg2
      {
        result = v4[3];  // result = 取 v4[3]
        *(uint32_t *)(result + 212) = 0;  // result=this+204 pSubAnim204
        v5 = v4[3];  // v5 = 取 v4[3]
        if ( v5 != 0 )  // 若 v5 非 0
        {
          sub_42AF90((void **)v4[3]);  // 帧对象析构（帧数组 + 元素数组）
          result = sub_657740(v5, 228);  // 池化结点弹出（写魔术标记后挂入链头）
        }
        v4[3] = 0;
        v6 = (uint32_t *)*v4;
        if ( v4 != (uint32_t *)*(this + 51) )  // this+204〔pSubAnim204(推断)〕
        {
          *(uint32_t *)v4[1] = v6;
          *(uint32_t *)(*v4 + 4) = v4[1];
          j__free(v4);  // 调 j__free（堆释放）
          result = *(this + 52) - 1;  // this+208〔nField208(推断)〕
          *(this + 52) = result;  // this+208〔nField208(推断)〕
        }
        v4 = v6;
      }
      else  // 否则分支
      {
        if ( result > nArg2 )  // 若 result > nArg2
          return result;  // result=this+208 nField208
        v4 = (uint32_t *)*v4;
      }
    }
    while ( v4 != (uint32_t *)*(this + 51) );  // 条件循环
  }
  return result;  // result=this+208 nField208
}



// ------------------------------------------------------------
// 0x4945A0 sub_4945A0 —— 按帧数 n 初始化帧数组（转发 sub_494420）
// ------------------------------------------------------------
void /*thiscall*/ sub_4945A0(int *this, unsigned int uArg2)  // 实现：按帧数 n 初始化帧数组（转发 sub_494420）
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
  v4 = nullptr;  // v4 = 空指针
  v5 = 0;
  v6 = 0;
  v8 = nullptr;  // v8 = 空指针
  v9 = 0;
  v10 = 0;
  sub_430B70(v3);  // 88B 帧条目复位
  v12 = -1;
  sub_494420(  // 帧数组构建（每帧 22×uint32=88B；sub_493960/493F30）
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
int /*thiscall*/ sub_494610(int *this, unsigned int uArg2)  // 实现：帧数组重置包装（对 +40 偏移的动画子对象）
{
  sub_4945A0(this + 10, uArg2);  // 按帧数 n 初始化帧数组（转发 sub_494420）
  return sub_4926A0((int)this);  // 帧游标复位（+44 帧数组；递归子链 +204）
}



// ------------------------------------------------------------
// 0x494630 sub_494630 —— 单帧占位初始化：帧+0 句柄槽；帧+12/+16 = 尺寸(a2+20/+24)/2 取负 → 居中锚点
// ------------------------------------------------------------
int /*thiscall*/ sub_494630(int this, int pArg2)  // 实现：单帧占位初始化：帧+0 句柄槽；帧+12/+16 = 尺寸(a2+20/+24)/2 取负 → 居中锚点
{
  sub_4945A0((int *)(this + 40), 1u);  // 按帧数 n 初始化帧数组（转发 sub_494420）
  **(uint32_t **)(this + 44) = pArg2;  // this+176〔pAppendVecCap(推断)〕
  *(uint32_t *)(*(uint32_t *)(this + 44) + 12) = *(uint32_t *)(pArg2 + 20) / -2;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(*(uint32_t *)(this + 44) + 16) = *(uint32_t *)(pArg2 + 24) / -2;  // this+44〔nExpireMs(推断)〕等 2 字段
  return sub_4926A0(this);  // 帧游标复位（+44 帧数组；递归子链 +204）
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
char /*thiscall*/ sub_494680(uint8_t *this, char ArgList, int nArg3, char pszArg4, int nArg5, int nArg6, int nArg7)  // 实现：.ani 主解析器（标签清单见文件头）
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

  dword_796E502 = dword_796E50;  // dword_796E50（栈检 cookie 值）
  pThis = this;
  pThis2 = this;
  result = sub_442A10(ArgList, nArg3);  // 脚本载入调度（PVF 或磁盘）
  if ( result == 0 )  // 若 result 为 0
    return result;
  v35 = 15;
  v34 = 0;
  LOBYTE(v33) = 0;
  v37 = 1;
  v31 = 15;
  v30 = 0;
  LOBYTE(Block[0]) = 0;
  if ( (uint8_t)sub_443430(v32) == 0 || sub_40BF00((std::_String_base *)v32, 0, v34, "[LOOP]", 6u) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
  {
    v31 = 15;
    v30 = 0;
    LOBYTE(Block[0]) = 0;
    if ( v35 >= 0x10 )  // 若 v35 >= 0x10
      j__free(v33);  // 调 j__free（堆释放）
    return 0;
  }
  pThis[160] = sub_4423D0(0) != 0;  // [LOOP] → 动画对象+160
  if ( (uint8_t)sub_443430(v32) == 0  // 读 token 到 string + 国家码标记
    || (uint8_t)sub_423340(v32, "[SHADOW]") != 0  // 串首比较判定（不等）
    || (pThis[161] = sub_4423D0(0) != 0, (uint8_t)sub_443430(v32) == 0)  // [SHADOW] → 对象+161
    || (uint8_t)sub_423340(v32, "[FRAME MAX]") != 0  // 串首比较判定（不等）
    || (v9 = sub_4423D0(0), v24 = v9, sub_4945A0(v9), (uint8_t)sub_443430(v32) == 0)  // [FRAME MAX] → 帧数 v24；sub_4945A0 按 88B/帧分配
    || (uint8_t)sub_423340(v32, "[FRAME000]") != 0 )  // 串首比较判定（不等）
  {
LABEL_66:  // 标签 LABEL_66（跳转合流点）
    sub_501490(v28);  // 调 对象析构后释放堆块
    sub_501490(v32);  // 调 对象析构后释放堆块
    return 0;
  }
  v25 = 0;
  if ( v9 > 0 )  // 若 v9 > 0
  {
    ArgLista = 0;
    while ( 1 )  // 条件循环
    {
      v10 = ArgLista + *((uint32_t *)pThis + 11);  // 帧基址 = 对象+44(vector首) + 88×帧序【研究§11】
      sub_430B70(v10);  // 88B 帧条目复位
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[IMAGE]") != 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      sub_443370();  // 脚本 token 取串（第三入口）
      v11 = sub_4423D0(0);  // v11 = 调 sub_4423D0 返回值
      nArg3 = v11;
      if ( (uint8_t)sub_423340(v28, szPassword) != 0 )  // 串首比较判定（不等）
      {
        if ( pszArg4 == 0 )  // 若 pszArg4 为 0
        {
          v15 = sub_4BC700(v28);  // 部件路径 → 资源 id
LABEL_25:  // 标签 LABEL_25（跳转合流点）
          *(uint32_t *)(v10 + 8) = v11;  // 帧+8 资源id
          *(uint32_t *)(v10 + 4) = v15;  // 帧+4 路径资源（sub_4BC700 路径→id）
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84BC + 56))(dword_8F84BC, v15);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
          *(uint32_t *)v10 = sub_418DD0(v11);  // 帧+0 图像句柄
          goto LABEL_26;
        }
        if ( nArg5 == 0 )  // 若 nArg5 为 0
        {
          Block2 = (void **)Block[0];
          if ( v31 < 0x10 )  // 若 v31 < 0x10
            Block2 = Block;
          sprintf(Src, (const char *const)Block2, nArg6, nArg7);  // 拼字符串
          sub_406D60(Src);  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
          v15 = sub_4BC700(v28);  // 部件路径 → 资源 id
          goto LABEL_25;
        }
        *(uint32_t *)v10 = 0;  // *v10 = 0
        v12 = sub_492750(v28, &nArg3);  // std::string 就地构造（SSO：+20 len / +24 cap 15 / +4 空字节收尾）
        LOBYTE(v37) = 2;
        sub_493AD0(v12);  // 32 字节元素容器末尾追加（容量够就地写，不够走 ·0x493480 扩容）
        LOBYTE(v37) = 1;
        sub_501490(v20);  // 调 对象析构后释放堆块
        Block3 = (void **)Block[0];
        if ( v31 < 0x10 )  // 若 v31 < 0x10
          Block3 = Block;
        sprintf(Buffer, (const char *const)Block3, nArg6, nArg7);  // 拼字符串
        sub_406D60(Buffer);  // std::string 从 C 串赋值（strlen 定长后转发 ·sub_4015C0）
        *(uint32_t *)(v10 + 4) = sub_4BC700(v28);  // 帧+4 路径资源
        *(uint32_t *)(v10 + 8) = v11;  // 帧+8 资源id
      }
LABEL_26:  // 标签 LABEL_26（跳转合流点）
      if ( (uint8_t)sub_443430(v32) == 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE POS]") != 0 )  // 串首比较判定（不等）
        goto LABEL_66;
      *(uint32_t *)(v10 + 12) = sub_4423D0(0);  // 帧+12 位置x [IMAGE POS]
      *(uint32_t *)(v10 + 16) = sub_4423D0(0);  // 帧+16 位置y
      if ( (uint8_t)sub_443430(v32) == 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE RATE]") != 0 )  // 串首比较判定（不等）
        goto LABEL_66;
      *(float *)(v10 + 20) = sub_442480(0);  // 帧+20 缩放x [IMAGE RATE]
      *(float *)(v10 + 24) = sub_442480(0);  // 帧+24 缩放y
      if ( (uint8_t)sub_443430(v32) == 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[IMAGE ROTATE]") != 0 )  // 串首比较判定（不等）
        goto LABEL_66;
      *(float *)(v10 + 28) = sub_442480(0);  // 帧+28 旋转 [IMAGE ROTATE]
      if ( (uint8_t)sub_443430(v32) == 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[RGBA]") != 0 )  // 串首比较判定（不等）
        goto LABEL_66;
      v16 = sub_4423D0(0);  // v16 = 调 sub_4423D0 返回值
      nArg3 = sub_4423D0(0);  // nArg3 = 调 sub_4423D0 返回值
      v23 = sub_4423D0(0);  // v23 = 调 sub_4423D0 返回值
      HIBYTE(v17) = sub_4423D0(0);  // 调 循环：k = (void ***)sub_4423D0(&i); i != 0; k = (void ***)sub_4423
      LOBYTE(v17) = v23;
      *(uint32_t *)(v10 + 32) = v16 | (((uint8_t)nArg3 | (v17 << 8)) << 8);  // 帧+32 [RGBA] 打包
      if ( (uint8_t)sub_443430(v32) == 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[INTERPOLATION]") != 0 )  // 串首比较判定（不等）
        goto LABEL_66;
      *(uint8_t *)(v10 + 36) = sub_4423D0(0) != 0;  // 帧+36 [INTERPOLATION] 插值开关
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[GRAPHIC EFFECT]") != 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      sub_443370();  // 脚本 token 取串（第三入口）
      if ( (uint8_t)sub_423300(v28, "NONE") != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 40) = 0;  // 帧+40 特效=NONE
      }
      else if ( (uint8_t)sub_423300(v28, "DODGE") != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 40) = 1;  // 帧+40 特效=DODGE
      }
      else if ( (uint8_t)sub_423300(v28, "LINEARDODGE") != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 40) = 2;  // 帧+40 特效=LINEARDODGE
      }
      else if ( (uint8_t)sub_423300(v28, "DARK") != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 40) = 3;  // 帧+40 特效=DARK
      }
      else if ( (uint8_t)sub_423300(v28, &off_6CAF88) != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 40) = 4;  // 帧+40 特效=4（off_6CAF88 指向的标签，研究§11 之"+4"）
      }
      else if ( (uint8_t)sub_423300(v28, "MONOCHROME") != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 40) = 5;  // 帧+40 特效=MONOCHROME
        v18 = sub_4423D0(0);  // v18 = 调 sub_4423D0 返回值
        nArg3 = sub_4423D0(0);  // nArg3 = 调 sub_4423D0 返回值
        *(uint32_t *)(v10 + 44) = v18 | (((uint8_t)nArg3 | ((sub_4423D0(0) | 0xFFFFFF00) << 8)) << 8);  // 帧+44 MONOCHROME 参数色
      }
      if ( (uint8_t)sub_443430(v32) == 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      if ( (uint8_t)sub_423340(v32, "[DELAY]") != 0 )  // 串首比较判定（不等）
        goto LABEL_66;
      *(uint32_t *)(v10 + 48) = sub_4423D0(0);  // ★帧+48 [DELAY] 本帧驻留ms（研究§11）
      if ( (uint8_t)sub_443430(v32) == 0 || (uint8_t)sub_423340(v32, "[DAMAGE TYPE]") != 0 )  // 读 token 到 string + 国家码标记
        goto LABEL_66;
      sub_443370();  // 脚本 token 取串（第三入口）
      if ( (uint8_t)sub_423300(v28, "NORMAL") != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 52) = 0;  // ★帧+52 [DAMAGE TYPE] 0=NORMAL
      }
      else if ( (uint8_t)sub_423300(v28, "SUPERARMOR") != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 52) = 1;  // ★帧+52 [DAMAGE TYPE] 1=SUPERARMOR 霸体
      }
      else if ( (uint8_t)sub_423300(v28, "UNBREAKABLE") != 0 )  // 串首比较判定（相等）
      {
        *(uint32_t *)(v10 + 52) = 2;  // ★帧+52 [DAMAGE TYPE] 2=UNBREAKABLE 不可打断
      }
      while ( (uint8_t)sub_443430(v32) != 0 )  // 读 token 到 string + 国家码标记
      {
        if ( (uint8_t)sub_423340(v32, "[ATTACK BOX]") != 0  // 串首比较判定（不等）
          && (uint8_t)sub_423340(v32, "[DAMAGE BOX]") != 0 )  // 串首比较判定（不等）
        {
          break;  // 跳出循环/分支
        }
        nArg3 = sub_4423D0(0);  // nArg3 = 调 sub_4423D0 返回值
        v21[0] = (float)nArg3;  // 盒参数 6×float（[ATTACK BOX]/[DAMAGE BOX] 多组循环）
        nArg3 = sub_4423D0(0);  // nArg3 = 调 sub_4423D0 返回值
        v21[1] = (float)nArg3;
        nArg3 = sub_4423D0(0);  // nArg3 = 调 sub_4423D0 返回值
        v21[2] = (float)nArg3;
        nArg3 = sub_4423D0(0);  // nArg3 = 调 sub_4423D0 返回值
        v21[3] = (float)nArg3;
        nArg3 = sub_4423D0(0);  // nArg3 = 调 sub_4423D0 返回值
        v21[4] = (float)nArg3;
        nArg3 = sub_4423D0(0);  // nArg3 = 调 sub_4423D0 返回值
        v21[5] = (float)nArg3;
        sub_423300(v32, "[ATTACK BOX]");  // 串首比较判定（相等）
        sub_4931A0(v21);  // ecx=帧+56 盒vector【推断】追加一组 6float
      }
      v19 = ++v25 < v24;  // 帧序 < [FRAME MAX]
      ArgLista += 88;  // ★下一帧：帧结构步长 88 字节（研究§11）
      if ( !v19 )
        break;  // 跳出循环/分支
      pThis = pThis2;
    }
  }
  sub_501490(v28);  // 调 对象析构后释放堆块
  sub_501490(v32);  // 调 对象析构后释放堆块
  return 1;  // 返回 1(成功)
}


// ============================================================
// §I 0x494E40-0x496540  动画/粒子创建工厂（ANIMATION CREATE FAIL）
// ============================================================
// ------------------------------------------------------------
// 0x494E40 sub_494E40 —— 动画创建入口
//   a4 非空时 strcmp(a2,szPassword) 分流 sub_4F3BA0/sub_4F3D60 建空动画 → sub_494370 →
//   sub_494680 解析 .ani；失败 ANIMATION CREATE FAIL1/2!。
// ------------------------------------------------------------
int /*thiscall*/ sub_494E40(uint8_t *this, const char *pArg2, const char *ArgList, char pszArg4, int nArg5, int nArg6, int nArg7, int nArg8)  // 实现：动画创建入口
{
  int pThis; // esi
  int v9; // eax

  pThis = (int)this;
  if ( (uint8_t)nArg5 != 0 && (nArg7 == -1 || nArg8 == -1) )  // 若 nArg7 == -1 与/或 nArg8 == -1
    LOBYTE(nArg5) = 0;
  if ( pszArg4 != 0 )  // 若 pszArg4 非 0
  {
    if ( strcmp(pArg2, szPassword) == 0 )  // 调 strcmp（串比较）
      v9 = sub_4F3BA0(ArgList, nArg5, nArg7, nArg8);  // v9 = 调 sub_4F3BA0 返回值
    else  // 否则分支
      v9 = sub_4F3D60((char)pArg2, (int)ArgList, nArg5, nArg7, nArg8);  // v9 = 调 sub_4F3D60 返回值
    if ( v9 == 0 )  // 若 v9 为 0
      return off_77F3FC("ANIMATION CREATE FAIL1! FILENAME[%s]", ArgList);  // 返回 调 off_77F3FC
    pThis = (int)this;
    sub_494370(v9);  // 装载帧数组副本并重取图像句柄（帧+4 → sub_418DD0 刷新帧+0）
  }
  else if ( sub_494680(this, (char)pArg2, (int)ArgList, nArg5, nArg6, nArg7, nArg8) == 0 )  // .ani 主解析器（标签清单见文件头）
  {
    return off_77F3FC("ANIMATION CREATE FAIL2! FILENAME[%s]", ArgList);  // 返回 调 off_77F3FC
  }
  return sub_4926A0(pThis);  // 帧游标复位（+44 帧数组；递归子链 +204）
}



// ------------------------------------------------------------
// 0x494F20 sub_494F20 —— 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
// this+0 对象经 vt+308 校验（有效性门），值变化才写并置 +196 失效标志。
//   被动画/技能以 sub_494F20(2, 速率或缩放) 形式批量下发。
// ------------------------------------------------------------
void /*thiscall*/ sub_494F20(float *this, int pArg2, float fArg3)  // 实现：属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
{
  float v4; // ecx

  v4 = *this;
  if ( v4 != 0.0
    && (*(uint8_t (/*thiscall*/ **)(float))(*(uint32_t *)LODWORD(v4) + 308))(COERCE_FLOAT(LODWORD(v4))) != 0  // 调虚槽 +308：是否本地玩家
    && *(this + pArg2 + 4) != fArg3 )  // 属性浮点槽写入（槽号 pArg2，落 this+pArg2+4）
  {
    *(this + pArg2 + 4) = fArg3;
    *((uint8_t *)this + 196) = 1;  // this[196] = 1
  }
}



// ------------------------------------------------------------
// 0x494F60 sub_494F60 —— 属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
// 与 ·0x494F20 同构（差异：槽基址 +40、整型值），同走 vt+308 校验 + +196 失效标志。
// ------------------------------------------------------------
void /*thiscall*/ sub_494F60(uint32_t *this, int pArg2, int nArg3)  // 实现：属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
{
  int pObj; // ecx

  pObj = *this;
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 && *(this + pArg2 + 10) != nArg3 )  // 调虚槽 +308：是否本地玩家
  {
    *(this + pArg2 + 10) = nArg3;
    *((uint8_t *)this + 196) = 1;  // this[196] = 1
  }
}



// ------------------------------------------------------------
// 0x494FA0 sub_494FA0
// ------------------------------------------------------------
int /*thiscall*/ sub_494FA0(int *this, int nArg2, int nArg3)  // 实现：双目标检查（双方均需条件 16 不在 且 vt+308 通过）
{
  int result; // eax
  char v5; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*this + 308))(this);  // 调虚槽 +308：是否本地玩家
  if ( (uint8_t)result != 0 )
  {
    result = *(this + 50);  // this+200〔nMainState(推断)〕
    if ( result == 0 )  // 若 result 为 0
    {
      result = (*(int (/*thiscall*/ **)(int *, int))(*this + 776))(this, 16);  // 调虚槽 +776：异常状态查询
      if ( (uint8_t)result == 0 )  // result=this+200 nMainState
      {
        v5 = 1;
        if ( nArg2 == 4 || nArg3 == 4 )  // 若 nArg2 == 4 与/或 nArg3 == 4
          v5 = 0;
        (*(void (/*thiscall*/ **)(int *, uint32_t, int, char))(*this + 892))(this, 0, nArg2, v5);  // 调虚槽 +892：★ 动画速率缓存写入【会话 3 还原】
        return (*(int (/*thiscall*/ **)(int *, int, int, char))(*this + 892))(this, 1, nArg3, v5);  // 调虚槽 +892：★ 动画速率缓存写入【会话 3 还原】
      }
    }
  }
  return result;  // result=this+200 nMainState
}



// ------------------------------------------------------------
// 0x495010 sub_495010
// ------------------------------------------------------------
void /*userpurge*/ sub_495010(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)  // 实现：★ 装备/武器模式切换状态机(会话 3 还原骨架)
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
    if ( nArg4 != 0 )  // 若 nArg4 非 0
    {
      if ( nArg4 != 1 )  // 若 nArg4 != 1
        return;
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 188))(pArg1);  // 调虚槽 +188：动画对象 z 倾斜转状态码
    }
    else  // 否则分支
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 184))(pArg1);  // 调虚槽 +184：动画对象 z 倾斜转状态码
    }
    v29 = v6;
    if ( v6 != 4 )  // 若 v6 != 4
    {
      v7 = nArg4 != 0
         ? (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 184))(pArg1)  // 调虚槽 +184：动画对象 z 倾斜转状态码
         : (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 188))(pArg1);  // 调虚槽 +188：动画对象 z 倾斜转状态码
      v28 = v7;
      if ( v7 == 4 )  // 若 v7 == 4
      {
        v27 = 0;
        v25 = 4 * (nArg4 != 0) + 13;
        if ( 4 * (nArg4 != 0) != -13 )
        {
          v8 = &v24 - nArg4;
          v26 = 0;
          while ( 1 )  // 条件循环
          {
            v9 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 120))(pArg1, nArg2, nArg3);  // 调虚槽 +120：动画对象
            v10 = *pArg1;
            v23 = v9;
            v24 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 124))(pArg1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69 行…
            if ( v29 == 0 || v29 == 2 )  // 若 v29 == 0 与/或 v29 == 2
            {
              v11 = &v23 + nArg42;
              v12 = *v11 - 1;
            }
            else  // 否则分支
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
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(v13 + 136))(pArg1, v23) != 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
            {
              v28 = 2 * (nArg4 == 0) + 1;
              goto LABEL_23;
            }
            v16 = *pArg1;
            *v8 = v15 - v26 - 2;
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(v16 + 136))(pArg1, v23, v24, 0) != 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
              break;  // 跳出循环/分支
            nArg42 = nArg4;
            v17 = ++v27 < v25;
            v26 += 2;
            if ( !v17 )
              goto LABEL_24;
          }
          v28 = nArg4 != 0 ? 0 : 2;
LABEL_23:  // 标签 LABEL_23（跳转合流点）
          nArg42 = nArg4;
        }
LABEL_24:  // 标签 LABEL_24（跳转合流点）
        v18 = v28;
        v19 = v29;
        pArg1[1674] = 1 - nArg42;
        pArg1[1675] = v18;
        pArg1[1676] = v19;
        if ( nArg42 != 0 )  // 若 nArg42 非 0
          v20 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 124))(pArg1, nArg2, nArg3);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
        else  // 否则分支
          v20 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 120))(pArg1, nArg2, nArg3);  // 调虚槽 +120：动画对象
        pArg1[1677] = v20;
        if ( nArg42 != 0 )  // 若 nArg42 非 0
          (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 896))(pArg1);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
        else  // 否则分支
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 896))(pArg1, v29, v18);  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
      }
    }
  }
}


// ------------------------------------------------------------
// 0x4951F0 sub_4951F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4951F0(int *this)  // 实现：模式有效期校验（依赖值变化则失效）
{
  int result; // eax

  result = *(this + 1674);
  if ( result != -1 )
  {
    result = result != 0
           ? (*(int (/*thiscall*/ **)(int *))(*this + 184))(this)  // 调虚槽 +184：动画对象 z 倾斜转状态码
           : (*(int (/*thiscall*/ **)(int *))(*this + 188))(this);  // 调虚槽 +188：动画对象 z 倾斜转状态码
    if ( *(this + 1676) != result
      || (*(this + 1674) != 0
        ? (result = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this))  // 调虚槽 +120：动画对象
        : (result = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this)),  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
          *(this + 1677) != result) )  // 属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
    {
      *(this + 1674) = -1;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495250 sub_495250
// ------------------------------------------------------------
char /*thiscall*/ sub_495250(uint8_t *this, unsigned int uArg2, int nArg3, int nArg4)  // 实现：双标志门 + 转发 vt+968
{
  char result; // al

  result = *(this + 6634);
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = *(this + 6635);
    if ( result != 0 && *((uint32_t *)this + 1674) == -1 )  // 若 result != 0
    {
      result = uArg2;
      if ( uArg2 <= 1 )  // 若 uArg2 <= 1
        return (*(int (/*thiscall*/ **)(uint8_t *, unsigned int))(*(uint32_t *)this + 968))(this, uArg2);  // 调虚槽 +968：★ 装备/武器模式切换状态机【会话 3 还原骨架】
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495290 sub_495290
// ------------------------------------------------------------
int /*thiscall*/ sub_495290(uint32_t *this, int pArg2, int nArg3, int nArg4, int nArg5, int nArg6, char pszArg7)  // 实现：参数组写入（+6608 族 5 元组 + 转发 vt+892）
{
  *(this + pArg2 + 1652) = nArg3;
  *(this + pArg2 + 1654) = nArg4;
  *((uint8_t *)this + pArg2 + 6634) = nArg5;
  *(this + pArg2 + 1656) = nArg6;
  *((uint8_t *)this + pArg2 + 6632) = pszArg7;
  if ( nArg6 != 0 )  // 若 nArg6 非 0
    *((uint8_t *)this + pArg2 + 6634) = 0;
  LOBYTE(nArg5) = 1;
  if ( *(this + 1659) == 4 || *(this + 1660) == 4 )  // 复合条件判定（与/或）
    LOBYTE(nArg5) = 0;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 892))(this, pArg2, *(this + pArg2 + 1659), nArg5);  // 调虚槽 +892：★ 动画速率缓存写入【会话 3 还原】
}



// ------------------------------------------------------------
// 0x495310 sub_495310
// ------------------------------------------------------------
int /*thiscall*/ sub_495310(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：速率设置链: a2/a3 经 vt+976 换算 → vt+980/vt+984 写入
{
  int nArg42; // ebx
  int nArg52; // edi

  *(this + 1661) = nArg2;  // this+6644〔nSubGate〕
  *(this + 1662) = nArg3;
  if ( nArg2 != 0 )  // 若 nArg2 非 0
    nArg42 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 976))(this, nArg2);  // 调虚槽 +976：★ 速率查询（分四类）【会话 3 还原】
  else  // 否则分支
    nArg42 = nArg4;
  if ( nArg3 != 0 )  // 若 nArg3 非 0
    nArg52 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 976))(this, nArg3);  // 调虚槽 +976：★ 速率查询（分四类）【会话 3 还原】
  else  // 否则分支
    nArg52 = nArg5;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 980))(this, nArg42);  // 调虚槽 +980：速率档位应用: 写 +6652 后按 (6636/6640) 调 vt+896
  return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 984))(this, nArg52);  // 调虚槽 +984：★ 动作速率应用（千分值 ×0.1 → sub_493D00 写动画速率；
}



// ------------------------------------------------------------
// 0x495380 sub_495380
// ------------------------------------------------------------
int /*thiscall*/ sub_495380(int *this, int nArg2)  // 实现：速率档位应用: 写 +6652 后按 (6636/6640) 调 vt+896
{
  int v2; // edx

  v2 = *this;
  *(this + 1663) = nArg2;  // this+6652〔nRateNum〕
  return (*(int (/*stdcall*/ **)(uint32_t, uint32_t))(v2 + 896))(*(this + 1659), *(this + 1660));  // 调虚槽 +896：IRDCharacter__vmt380 默认虚槽桩（11 行 return）
}



// ------------------------------------------------------------
// 0x4953B0 sub_4953B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4953B0(uint32_t *this)  // 实现：★ 每 3 次调用发一次 UDP（%3 周期）(会话 3 新发现)
{
  int result; // eax
  int fld_e1686; // eax  | +0x1A58 → 冻结标志（IRDActiveObject·基类）
  int v4; // et2
  int v5; // edi
  int v6; // eax
  int v7; // edi
  int v8; // eax

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 852))(this);  // 调虚槽 +852：冻结标志 != -1 查询
  if ( (uint8_t)result != 0 )
  {
    fld_e1686 = *(this + 1686) + 1;  // this+6744〔nFrozenFlag〕
    *(this + 1686) = fld_e1686;  // this+6744〔nFrozenFlag〕
    v4 = fld_e1686 % 3;  // fld_e1686=this+6744 nFrozenFlag
    result = fld_e1686 / 3;  // fld_e1686=this+6744 nFrozenFlag
    if ( v4 == 0 )  // 若 v4 为 0
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 33, 2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      v5 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 48))(this);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, v6);  // 会话/UDP 管理器
      v7 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);  // 会话/UDP 管理器
      return (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495430 sub_495430 —— 时间轴坐标换算（毫秒 → 刻度）
// 4000×nArg1 / ((100×nArg2/nArg3-10000)×0.0121+2100)：分母为对 1 万基准的线性校正项；
//   属 UI 时间轴（char_server_info）刻度换算。
// ------------------------------------------------------------
double /*cdecl*/ sub_495430(int nArg1, int nArg2, int nArg3)  // 实现：时间轴坐标换算（毫秒 → 刻度）
{
  return (double)(4000 * nArg1) / ((double)(100 * nArg2 / nArg3 - 10000) * 0.0121 + 2100.0);
}



// ------------------------------------------------------------
// 0x495470 sub_495470 —— 条件写时间槽（+6668 开关为真才写 +6672）
// 被 char_server_info 与 bigfunc_4471E0 调用，用于状态/演出计时槽的条件更新。
// ------------------------------------------------------------
char /*thiscall*/ sub_495470(int this, int nArg2)  // 实现：条件写时间槽（+6668 开关为真才写 +6672）
{
  char result; // al

  result = *(uint8_t *)(this + 6668);  // result = 读 this+6668
  if ( result != 0 )  // 若结果非 0（成功）
  {
    *(uint32_t *)(this + 6672) = nArg2;  // this+6672〔uUI6672〕
    return nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x495490 sub_495490 —— 双使能位门控的槽写入
//   仅当 +6681 与 +6682 两使能字节均非 0 时，才把 nArg2 落到 +6684 并原样返回；
//   任一使能为 0 则不做写入，直接返回该使能字节值（no-op 路径）。
// ------------------------------------------------------------
char /*thiscall*/ sub_495490(int this, int nArg2)  // 实现：双使能位门控的槽写入
{
  char result; // al

  result = *(uint8_t *)(this + 6681);  // result = 读 this+6681
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = *(uint8_t *)(this + 6682);  // this+6682〔bUI6682〕
    if ( result != 0 )  // 若结果非 0（成功）
    {
      *(uint32_t *)(this + 6684) = nArg2;  // this+6684〔uUI6684〕
      return nArg2;
    }
  }
  return result;  // result=this+6682 bUI6682
}



// ------------------------------------------------------------
// 0x4954C0 sub_4954C0 —— 槽对乘积读取（+816/+830）
//   取 +816 槽整数值与 +830 槽浮点值（均经 0x41A5E0 的 clong 槽读取）相乘，以 double 返回。
//   本族共 4 组槽对（每对间隔 14 字节），与 sub_4957F0 尾段的 956×970 乘算同源，服务于尺寸×倍率换算。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_4954C0(void *this)  // 实现：槽对乘积读取（+816/+830）
{
  int pThis_330; // [esp+8h] [ebp-4h]

  pThis_330 = sub_41A5E0((unsigned int)this + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_330 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 830)));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x495500 sub_495500 —— 槽对乘积读取（+844/+858）
//   与 sub_4954C0 同构（差异：槽对为 +844/+858）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495500(void *this)  // 实现：槽对乘积读取（+844/+858）
{
  int pThis_34C; // [esp+8h] [ebp-4h]

  pThis_34C = sub_41A5E0((unsigned int)this + 844);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_34C * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 858)));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x495540 sub_495540 —— 槽对乘积读取（+872/+886）
//   与 sub_4954C0 同构（差异：槽对为 +872/+886）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495540(void *this)  // 实现：槽对乘积读取（+872/+886）
{
  int pThis_368; // [esp+8h] [ebp-4h]

  pThis_368 = sub_41A5E0((unsigned int)this + 872);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_368 * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 886)));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x495580 sub_495580 —— 槽对乘积读取（+956/+970）
//   与 sub_4954C0 同构（差异：槽对为 +956/+970，正是 sub_4957F0 尾段缩放路径所用的两槽）。
// ------------------------------------------------------------
uint64_t /*thiscall*/ sub_495580(void *this)  // 实现：槽对乘积读取（+956/+970）
{
  int pThis_3BC; // [esp+8h] [ebp-4h]

  pThis_3BC = sub_41A5E0((unsigned int)this + 956);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return (uint64_t)((double)pThis_3BC * COERCE_FLOAT(sub_41A5E0((unsigned int)this + 970)));  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x4955C0 sub_4955C0 —— 属性槽条件写入（变化才落 + 触发广播）
//   对象句柄 *this 有效（vt+308）且槽 *(this+pArg2+7) 与新值 nArg3 不同时：写入并置 +196 重算位，
//   再经 ·0x494F60 以槽号 pArg2 广播该属性变更（整型槽族，落 +40+4×槽）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4955C0(int *this, int pArg2, int nArg3)  // 实现：属性槽条件写入（变化才落 + 触发广播）
{
  int pObj; // ecx

  pObj = *this;
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 && *(this + pArg2 + 7) != nArg3 )  // 调虚槽 +308：是否本地玩家
  {
    *(this + pArg2 + 7) = nArg3;
    *((uint8_t *)this + 196) = 1;  // this[196] = 1
    sub_494F60(this, pArg2, -1);  // 属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
  }
}



// ------------------------------------------------------------
// 0x495600 sub_495600
// ------------------------------------------------------------
char /*thiscall*/ sub_495600(uint32_t *this, int pArg2, int nArg3, char pszArg4)  // 实现：★ 动画速率缓存写入(会话 3 还原)
{
  uint8_t *fld_e28; // ebx
  uint32_t *fld_e282; // ebx
  char result; // al
  int v9; // [esp+8h] [ebp-8h]
  int v10; // [esp+18h] [ebp+8h]
  float v11; // [esp+18h] [ebp+8h]
  float fld_e1663; // [esp+20h] [ebp+10h]
  int v13; // [esp+20h] [ebp+10h]

  if ( pszArg4 != 0 )  // 若 pszArg4 非 0
    v10 = *(this + pArg2 + 1654);
  else  // 否则分支
    v10 = *(this + pArg2 + 1652);
  v9 = *(this + pArg2 + 1656);
  fld_e1663 = 0.0;
  if ( nArg3 == 0 || nArg3 == 2 )  // 若 nArg3 == 0 与/或 nArg3 == 2
  {
    fld_e1663 = -1.0;
  }
  else if ( nArg3 == 1 || nArg3 == 3 )
  {
    fld_e1663 = 1.0;
  }
  if ( *(this + 1663) != 1000 )  // this+6652〔nRateNum〕
    fld_e1663 = (double)(int)*(this + 1663) * fld_e1663 * 0.001;  // this+6652〔nRateNum〕
  fld_e28 = (uint8_t *)*(this + 28);  // this+112〔pHostComp112〕
  v11 = (double)v10 * fld_e1663;  // fld_e1663=this+6652 nRateNum
  if ( *(uint32_t *)fld_e28 != 0  // fld_e28=this+112 pHostComp112
    && (*(uint8_t (/*thiscall*/ **)(uint32_t))(**(uint32_t **)fld_e28 + 308))(*(uint32_t *)fld_e28) != 0  // 调虚槽 +308：是否本地玩家
    && *(float *)&fld_e28[4 * pArg2 + 16] != v11 )  // 属性槽条件写入（变化才落 + 触发广播）
  {
    *(float *)&fld_e28[4 * pArg2 + 16] = v11;  // fld_e28=this+112 pHostComp112
    fld_e28[196] = 1;  // fld_e28=this+112 pHostComp112
  }
  fld_e282 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  v13 = (uint64_t)((double)v9 * fld_e1663);  // fld_e1663=this+6652 nRateNum
  if ( *fld_e282 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e282 + 308))(*fld_e282) != 0 && fld_e282[pArg2 + 7] != v13 )  // 复合条件判定（与/或）
  {
    fld_e282[pArg2 + 7] = v13;
    *((uint8_t *)fld_e282 + 196) = 1;  // fld_e282=this+112 pHostComp112
    sub_494F60(fld_e282, pArg2, -1);  // 属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
  }
  result = *((uint8_t *)this + pArg2 + 6632);
  if ( result != 0 )  // 若结果非 0（成功）
  {
    sub_4A0600(pArg2);  // 调 把 this[a2+10] 写为 浮点值×-1000/系数 —— 千分位换算 + 方向翻转
    result = nArg3;
  }
  *(this + pArg2 + 1659) = nArg3;
  return result;
}



// ------------------------------------------------------------
// 0x495740 sub_495740
// ------------------------------------------------------------
int /*thiscall*/ sub_495740(void *this, int nArg2)  // 实现：★ 速率查询（分四类）(会话 3 还原)
{
  int pThis_2A0; // esi
  int v3; // eax
  unsigned int v4; // ecx
  int pThis_2A02; // esi
  int64_t v6; // rax
  void *pThis_2A03; // eax

  switch ( nArg2 )  // 按 nArg2 分派
  {
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      pThis_2A0 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
      v3 = sub_41A5E0(pThis_2A0 + 816);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v4 = pThis_2A0 + 830;
      return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0(v4)));  // crypt4byte 解密校验（·0x41A590 逆运算）
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      pThis_2A02 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
      v3 = sub_41A5E0(pThis_2A02 + 844);  // crypt4byte 解密校验（·0x41A590 逆运算）
      v4 = pThis_2A02 + 858;
      return (uint64_t)((double)v3 * COERCE_FLOAT(sub_41A5E0(v4)));  // crypt4byte 解密校验（·0x41A590 逆运算）
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      LODWORD(v6) = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 900))(this, 3);  // 调虚槽 +900
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      pThis_2A03 = (void *)(*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 672))(this, 3);  // 调虚槽 +672：自身 HP
      LODWORD(v6) = sub_495540(pThis_2A03);  // 槽对乘积读取（+872/+886）
      break;  // 跳出循环/分支
    default:  // 默认分支
      LODWORD(v6) = 1000;
      break;  // 跳出循环/分支
  }
  return v6;
}



// ------------------------------------------------------------
// 0x4957F0 sub_4957F0 —— 方位基数求解（-1500 基准 + 956×970 比例折算）
//   pszArg2 非 0 时基数固定 -1500，叠加 *(this+1669) 与宿主对象 +1324 的偏移后直接返回；
//   pszArg2 为 0 时读 +1666 作基数，宿主无效或基数为 0 则改走缩放路径：基数 × (956×970 乘积)/100。
//   【推断】-1500 为坐标基准偏移，+1669 由 ·sub_495890/·sub_495920 维护。
// ------------------------------------------------------------
int /*thiscall*/ sub_4957F0(int *this, char pszArg2)  // 实现：方位基数求解（-1500 基准 + 956×970 比例折算）
{
  int fld_e1666; // edi
  int fld_e29; // eax
  int v4; // eax
  int v6; // esi
  int v7; // [esp+14h] [ebp+8h]

  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
  {
    fld_e1666 = -1500;
  }
  else  // 否则分支
  {
    fld_e1666 = *(this + 1666);  // this+6664〔uUI6664〕
    if ( fld_e1666 == 0 )  // 若 fld_e1666 为 0
      goto LABEL_9;
  }
  fld_e29 = *(this + 29);  // this+116〔会话上下文〕
  if ( fld_e29 != 0 )  // 若 fld_e29 非 0
  {
    v4 = *(uint32_t *)(fld_e29 + 132);  // fld_e29=this+116 会话上下文
    if ( v4 != 0 )  // 若 v4 非 0
      fld_e1666 += *(this + 1669) + *(uint32_t *)(v4 + 1324);  // fld_e1666=this+6664 uUI6664
  }
  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
    return fld_e1666;  // fld_e1666=this+6664 uUI6664
LABEL_9:  // 标签 LABEL_9（跳转合流点）
  v6 = (*(int (/*thiscall*/ **)(int *, int))(*this + 672))(this, 3);  // 调虚槽 +672：自身 HP
  v7 = sub_41A5E0(v6 + 956);  // crypt4byte 解密校验（·0x41A590 逆运算）
  return (int)(fld_e1666 * (uint64_t)((double)v7 * COERCE_FLOAT(sub_41A5E0(v6 + 970)))) / 100;  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x495890 sub_495890 —— 模式选择式方位设置（1/2/其他 三分支）
//   模式号写 +1665 后求值：1 → 宿主 +1324 加 +1669 偏移再减 1500；2 → ·sub_4957F0(0) 比例折算；其余直接取 nArg3。
//   值变化时写入 *(this+28) 子对象 +36 槽（槽号 2），置 +196 并经 ·0x494F60 广播。
// ------------------------------------------------------------
void /*thiscall*/ sub_495890(int *this, int nArg2, int nArg3)  // 实现：模式选择式方位设置（1/2/其他 三分支）
{
  int fld_e29; // eax
  int fld_e1669; // edi
  int v6; // eax
  uint32_t *fld_e28; // esi

  *(this + 1665) = nArg2;
  if ( nArg2 == 1 )  // 若 nArg2 == 1
  {
    fld_e29 = *(this + 29);  // this+116〔会话上下文〕
    fld_e1669 = -1500;
    if ( fld_e29 != 0 )  // 若 fld_e29 非 0
    {
      v6 = *(uint32_t *)(fld_e29 + 132);  // fld_e29=this+116 会话上下文
      if ( v6 != 0 )  // 若 v6 非 0
        fld_e1669 = *(uint32_t *)(v6 + 1324) + *(this + 1669) - 1500;  // fld_e1669 = 读 this+1669
    }
  }
  else if ( nArg2 == 2 )
  {
    fld_e1669 = sub_4957F0(this, 0);  // 方位基数求解（-1500 基准 + 956×970 比例折算）
  }
  else  // 否则分支
  {
    fld_e1669 = nArg3;
  }
  fld_e28 = (uint32_t *)*(this + 28);  // this+112〔pHostComp112〕
  if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[9] != fld_e1669 )  // 复合条件判定（与/或）
  {
    fld_e28[9] = fld_e1669;  // fld_e28=this+112 pHostComp112
    *((uint8_t *)fld_e28 + 196) = 1;  // fld_e28=this+112 pHostComp112
    sub_494F60(fld_e28, 2, -1);  // 属性整型槽写入（槽号 pArg2，落 this+pArg2+10 即 +40+4×槽）
  }
}



// ------------------------------------------------------------
// 0x495920 sub_495920 —— 状态 4/9 超时偏移重算（+1639 门控 → +1669）
//   门控 +6668 非 0 且状态号 +1639 为 4/9（或子对象计数为 0 且 vt+128>0）时：按 +1668×100÷vt+740 求比例，
//   超 20 的部分按每单位 -300 折算写入 +1669 并置 +6680；状态退出时清 +1668 与 +6680；偏移变化且原模式为 1/2 时经 ·sub_495890 重发方位。
// ------------------------------------------------------------
void /*thiscall*/ sub_495920(uint32_t *this)  // 实现：状态 4/9 超时偏移重算（+1639 门控 → +1669）
{
  int fld_e1639; // eax
  int v3; // edi
  double v4; // st7
  int fld_e1665; // eax
  float fld_e1668; // [esp+4h] [ebp-8h]

  if ( *((uint8_t *)this + 6668) != 0 )
  {
    fld_e1639 = *(this + 1639);  // this+6556〔大状态ID〕
    v3 = 0;
    if ( fld_e1639 == 4 || fld_e1639 == 9 || (int)*(this + 81) <= 0 && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) > 0 )  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
    {
      fld_e1668 = (double)(int)*(this + 1668) * 100.0;  // this+6672〔uUI6672〕
      v4 = fld_e1668 / (double)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 740))(this);  // 调虚槽 +740：属性块 +4 浮点壳（GetHP 族）
      if ( v4 > 20.0 )
        v3 = (uint64_t)((v4 - 20.0) * -300.0);
      *((uint8_t *)this + 6680) = 1;  // this+6680〔bUI6680〕
    }
    else if ( *((uint8_t *)this + 6680) != 0 )  // this+6680〔bUI6680〕
    {
      if ( *((uint8_t *)this + 6668) != 0 )
        *(this + 1668) = 0;  // this+6672〔uUI6672〕
      *((uint8_t *)this + 6680) = 0;  // this+6680〔bUI6680〕
    }
    if ( *(this + 1669) != v3 )
    {
      fld_e1665 = *(this + 1665);
      *(this + 1669) = v3;
      if ( fld_e1665 == 1 || fld_e1665 == 2 )  // 若 fld_e1665 == 1 与/或 fld_e1665 == 2
        sub_495890(this, fld_e1665, 0);  // 模式选择式方位设置（1/2/其他 三分支）
    }
  }
}



// ------------------------------------------------------------
// 0x495A10 sub_495A10
// ------------------------------------------------------------
void /*thiscall*/ sub_495A10(int *this, int nArg2)  // 实现：★ 动作速率应用（千分值 ×0.1 → sub_493D00 写动画速率；
{
  int fld_e30; // ecx  | +0x0078 → 动画对象指针（CNGhoulOilSellerOlrek；va=00499020）
  uint32_t *fld_e32; // eax
  uint32_t *v5; // esi
  float v6; // [esp+0h] [ebp-Ch]
  float fld_e1664; // [esp+0h] [ebp-Ch]

  fld_e30 = *(this + 30);  // this+120〔pAnimObj〕
  *(this + 1664) = nArg2;  // this+6656〔nRateDen〕
  if ( fld_e30 != 0 )  // 若 fld_e30 非 0
  {
    v6 = (double)nArg2 * 0.1;
    sub_493D00(fld_e30, v6);  // 变速（研究§26）
  }
  fld_e32 = (uint32_t *)*(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
  v5 = (uint32_t *)*fld_e32;  // fld_e32=this+128 szStatusKeyBuf
  if ( (uint32_t *)*fld_e32 != fld_e32 )  // fld_e32=this+128 szStatusKeyBuf
  {
    do  // do-while 循环体起点
    {
      fld_e1664 = (double)*(this + 1664) * 0.1;  // this+6656〔nRateDen〕
      sub_493D00(v5[3], fld_e1664);  // 变速（研究§26）
      v5 = (uint32_t *)*v5;
    }
    while ( v5 != (uint32_t *)*(this + 32) );  // 条件循环
  }
}



// ------------------------------------------------------------
// 0x495A70 sub_495A70 —— 场景对象动画挂接（+1004 门控；v5==4 PVP 分流 aPvp_2 / v5==6 aWarroom，否则普通）
// ------------------------------------------------------------
char /*thiscall*/ sub_495A70(uint8_t *this, int nArg2, int ArgList, int nArg4)  // 实现：场景对象动画挂接（+1004 门控；v5==4 PVP 分流 aPvp_2 / v5==6 aWarroom，否则普通）
{
  char result; // al
  int v5; // eax
  int v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // eax

  result = *(this + 1004);  // this+1004 数值槽 D
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v5 = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
    if ( v5 == 4 )  // 若 v5 == 4
    {
      if ( sub_48F5E0(nArg4) == -1 )  // 座位下标按 id 查找
      {
        return off_77F3FC(aPvp_2, ArgList);  // 返回 调 off_77F3FC
      }
      else  // 否则分支
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg4);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg2);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        v6 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        v7 = sub_48F5E0(nArg4);  // 座位下标按 id 查找
        return (*(int (/*thiscall*/ **)(int, int, int))(v6 + 60))(dword_8F8520, 1, v7);  // 会话/UDP 管理器
      }
    }
    else if ( v5 == 6 )
    {
      if ( sub_48FCE0(nArg4) == -1 )  // 座位下标按 id 查找（表 dword_99FF08）
      {
        return off_77F3FC(aWarroom, ArgList);  // 返回 调 off_77F3FC
      }
      else  // 否则分支
      {
        (*(void (/*thiscall*/ **)(int, int, uint32_t))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 0);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg4);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg2);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        v8 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
        v9 = sub_48FCE0(nArg4);  // 座位下标按 id 查找（表 dword_99FF08）
        return (*(int (/*thiscall*/ **)(int, int, int))(v8 + 60))(dword_8F8520, 1, v9);  // 会话/UDP 管理器
      }
    }
    else  // 否则分支
    {
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 35, 2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, nArg4);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, ArgList);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nArg2);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      return (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495C00 sub_495C00 —— 三槽常量覆盖（+864 累加，+990/+892/+920 复位）
//   门控 +1004 非 0 且全局域号 dword_8F7A24+12 不等于 4 时：+864 槽累加 nArg2，
//   并把 +990 写 140.0f（0x430C0000）、+892 与 +920 写 70.0f（0x428C0000）。【推断】为界面尺寸/位置槽复位。
// ------------------------------------------------------------
char /*thiscall*/ sub_495C00(uint8_t *this, int nArg2)  // 实现：三槽常量覆盖（+864 累加，+990/+892/+920 复位）
{
  char result; // al
  int pThis_360; // eax
  int v5; // edx
  int v6; // edx
  int v7; // edx

  result = *(this + 1004);  // this+1004 数值槽 D
  if ( result != 0 )  // 若结果非 0（成功）
  {
    result = dword_8F7A24;  // 登录/选区管理器
    if ( *(uint32_t *)(dword_8F7A24 + 12) != 4 )  // 登录/选区管理器
    {
      pThis_360 = sub_41A5E0((unsigned int)(this + 864));  // crypt4byte 解密校验（·0x41A590 逆运算）
      sub_41A590((unsigned int)(this + 864), v5, nArg2 + pThis_360);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      sub_41A590((unsigned int)(this + 990), 1124859904, 1124859904);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      sub_41A590((unsigned int)(this + 892), v6, 1116471296);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
      return sub_41A590((unsigned int)(this + 920), v7, 1116471296);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x495C80 sub_495C80 —— 百分比分档（105/95/85/70/55/45/40/35）
//   读 +976 处浮点值（前五档经 ·0x41A5E0、后三档经 ·0x43B5A0 取值）按固定阈值降序分档，
//   返回 105/95/85/70/55/45/40/35/0 之一。【推断】该槽为血量百分比，供外观/特效档位切换。
// ------------------------------------------------------------
int /*thiscall*/ sub_495C80(char *this)  // 实现：百分比分档（105/95/85/70/55/45/40/35）
{
  void *pThis_3D0; // esi

  pThis_3D0 = this + 976;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)(this + 976))) >= 105.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return 105;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)pThis_3D0)) >= 95.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return 95;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)pThis_3D0)) >= 85.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return 85;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)pThis_3D0)) >= 70.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return 70;
  if ( COERCE_FLOAT(sub_41A5E0((unsigned int)pThis_3D0)) >= 55.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    return 55;
  if ( sub_43B5A0(pThis_3D0) >= 45.0 )  // 防篡读壳（槽值转 float）
    return 45;
  if ( sub_43B5A0(pThis_3D0) >= 40.0 )  // 防篡读壳（槽值转 float）
    return 40;
  if ( sub_43B5A0(pThis_3D0) < 35.0 )  // 防篡读壳（槽值转 float）
    return 0;
  return 35;
}



// ------------------------------------------------------------
// 0x495DA0 sub_495DA0 —— 96 字节元素双槽清零（+24/+72）
//   以 96 字节步长定位第 nArg2 个元素，把其 +24 与 +72 两槽清零并返回元素地址。
// ------------------------------------------------------------
char */*thiscall*/ sub_495DA0(char *this, int nArg2)  // 实现：96 字节元素双槽清零（+24/+72）
{
  char *result; // eax

  result = this + 96 * nArg2;
  *((uint32_t *)result + 6) = 0;  // result[6] = 0
  *((uint32_t *)result + 18) = 0;  // result[18] = 0
  return result;
}



// ------------------------------------------------------------
// 0x495DC0 sub_495DC0 —— 12×8 矩阵逐列比例累积（clamp 到 flt_790B04）
//   清 +192..+215 两行累计器（0x60 字节）后，按行（步长 24 float，共 8 行）× 列（12 列）逐格累加：
//   增量 = flt_790B04[i] ÷ 计数 × 当前值 × 模式缩放（域号 4/6 用 flt_790B34[i]，否则 flt_790AD4[i]，计数≤10 再乘 1/3）累入 +192 行，原值累入 +204 行；
//   第 6 列走独立路径（累入 +198/+210，缩放用 flt_790B4C/flt_790AEC），域号 3 时结果上限夹到 flt_790B04[i]。
// ------------------------------------------------------------
int /*thiscall*/ sub_495DC0(float *this)  // 实现：12×8 矩阵逐列比例累积（clamp 到 flt_790B04）
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
  memset(this + 192, 0, 0x60u);  // 清零 this+192 起 0x60 字节
  v23 = 12;
  pThis_12 = this + 18;  // this+18〔bDragChild〕
  do  // do-while 循环体起点
  {
    for ( i = 0; i < 12; ++i )  // 循环：i 从 0 递增到 12
    {
      pThis_D8 = sub_41A5E0((unsigned int)(this + 216));  // crypt4byte 解密校验（·0x41A590 逆运算）
      if ( i == 6 )  // 若 i == 6
      {
        if ( pThis_D8 <= 1 )  // 若 pThis_D8 <= 1
        {
          sub_41A630((unsigned int)v21);  // 调 防篡改字段读校验（crypt 逆运算链）
          v26 = 0;
          v21[0] = &clong::`vftable';  // 构造装配 vftable：clong
          sub_41A590((unsigned int)v21, v5, 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          v4 = v21;
          v26 = 1;
          v25 |= 1u;
        }
        else  // 否则分支
        {
          v4 = this + 216;
        }
        v22 = sub_41A5E0((unsigned int)v4);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v6 = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
        if ( v6 == 4 || v6 == 6 )  // 若 v6 == 4 与/或 v6 == 6
        {
          v8 = flt_790B4C;
        }
        else  // 否则分支
        {
          v7 = sub_41A5E0((unsigned int)(this + 216));  // crypt4byte 解密校验（·0x41A590 逆运算）
          v8 = flt_790AEC;
          if ( v7 <= 10 )  // 若 v7 <= 10
            v8 = v8 * 0.33333334;
        }
        v9 = v24;
        v10 = (v25 & 1) == 0;
        v11 = *v24 / (double)v22;
        v26 = -1;
        *(this + 198) = v11 * v8 + *(this + 198);  // this+198 复位组字节 等2字段
        if ( !v10 )
        {
          v25 &= ~1u;
          sub_41A580(v21);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
        }
        *(this + 210) = *(this + 210) + *v9;
      }
      else  // 否则分支
      {
        if ( v3 <= 1 )  // 若 v3 <= 1
        {
          sub_41A630((unsigned int)v20);  // 调 防篡改字段读校验（crypt 逆运算链）
          v26 = 2;
          v20[0] = &clong::`vftable';  // 构造装配 vftable：clong
          sub_41A590((unsigned int)v20, v13, 1);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
          pThis_D84 = v20;
          v26 = 3;
          v25 |= 2u;
        }
        else  // 否则分支
        {
          pThis_D84 = this + 216;
        }
        v22 = sub_41A5E0((unsigned int)pThis_D84);  // crypt4byte 解密校验（·0x41A590 逆运算）
        v14 = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
        if ( v14 == 4 || v14 == 6 )  // 若 v14 == 4 与/或 v14 == 6
          v15 = flt_790B34[i];  // v15 = 取 flt_790B34[i]
        else  // 否则分支
          v15 = flt_790AD4[i];  // v15 = 取 flt_790AD4[i]
        v16 = this + i + v23;
        v17 = flt_790B04[i] / (double)v22;
        v10 = (v25 & 2) == 0;
        v26 = -1;
        *(this + i + 192) = v17 * *v16 * v15 + *(this + i + 192);
        if ( !v10 )
        {
          v25 &= ~2u;
          sub_41A580(v20);  // crypt4byte 析构（vftable 复位 + 实例计数递减）
        }
        *(this + i + 204) = *(this + i + 204) + *v16;
        if ( *(uint32_t *)(dword_8F7A24 + 12) == 3 && *(this + i + 192) > (double)flt_790B04[i] )  // 登录/选区管理器
          *(this + i + 192) = flt_790B04[i];
      }
    }
    result = v23 + 24;
    v19 = v23 + 24 < 204;
    pThis_12 += 24;  // pThis_12=this+18 bDragChild
    v23 += 24;
  }
  while ( v19 );  // 条件循环
  return result;
}


// ------------------------------------------------------------
// 0x496010 sub_496010 —— 帧图像重载工厂（事件号 +48 → sub_495DC0 等）
// ------------------------------------------------------------
int /*thiscall*/ sub_496010(int this, int nArg2, int pArg3, int nArg4)  // 实现：帧图像重载工厂（事件号 +48 → sub_495DC0 等）
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

  v4 = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
  if ( v4 == 4 )  // 若 v4 == 4
  {
    result = dword_99FEC0;
    if ( dword_99FEC0 == 0 )  // 若 dword_99FEC0 为 0
      return result;
    v7 = sub_48F5E0(nArg2);  // 座位下标按 id 查找
  }
  else if ( v4 == 6 )
  {
    result = dword_99FF08;
    if ( dword_99FF08 == 0 )  // 若 dword_99FF08 为 0
      return result;
    v7 = sub_48FCE0(nArg2);  // 座位下标按 id 查找（表 dword_99FF08）
  }
  else  // 否则分支
  {
    result = sub_429830(nArg2);  // 表按键查找（uint16）
    if ( result == 0 )  // 若 result 为 0
      return result;
    result = sub_429830(nArg2);  // 表按键查找（uint16）
    if ( *(uint32_t *)(result + 196) == 0 )
      return result;
    v8 = sub_429830(nArg2);  // 表按键查找（uint16）
    v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(v8 + 196) + 1216))(*(uint32_t *)(v8 + 196));  // 调虚槽 +1216：IRDCharacter__vmt4C0 默认虚槽桩（10 行 return）
  }
  v21 = v7;
  *(float *)(this + 4 * (pArg3 + 24 * v7) + 48) = (double)nArg4 + *(float *)(this + 4 * (pArg3 + 24 * v7) + 48);
  sub_495DC0(this);  // 12×8 矩阵逐列比例累积（clamp 到 flt_790B04）
  fld_308 = *(float *)(this + 776) + *(float *)(this + 772) + *(float *)(this + 768);  // this+772〔uVal772(推断)〕
  sub_41A590(LODWORD(fld_308));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_314 = *(float *)(this + 788) + *(float *)(this + 784) + *(float *)(this + 780);
  sub_41A590(LODWORD(fld_314));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(*(uint32_t *)(this + 792));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  sub_41A590(*(uint32_t *)(this + 840));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( *(uint32_t *)(this + 964) != -956156672 )  // this+964〔nBlobSize〕
    sub_41A590(*(uint32_t *)(this + 964));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( *(uint32_t *)(this + 968) != -956156672 )  // this+968〔pBlobData〕
    sub_41A590(*(uint32_t *)(this + 968));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  fld_3CC = *(uint32_t *)(this + 972);  // fld_3CC = 读 this+972
  if ( fld_3CC != -956156672 )  // fld_3CC=this+972 叉子缩放计数
    sub_41A590(fld_3CC);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  v10 = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
  if ( v10 == 4 || v10 == 6 )  // 若 v10 == 4 与/或 v10 == 6
  {
    pThis_36E = COERCE_FLOAT(sub_41A5E0(this + 878));  // crypt4byte 解密校验（·0x41A590 逆运算）
    pThis_38A = COERCE_FLOAT(sub_41A5E0(this + 906));  // crypt4byte 解密校验（·0x41A590 逆运算）
    fld_32C = *(float *)(this + 812)  // 帧图像重载工厂（事件号 +48 → sub_495DC0 等）
        + *(float *)(this + 808)
        + *(float *)(this + 804)
        + *(float *)(this + 800)
        + *(float *)(this + 796)
        + COERCE_FLOAT(sub_41A5E0(this + 934))  // crypt4byte 解密校验（·0x41A590 逆运算）
        + pThis_38A
        + pThis_36E;
    fld_32C2 = fld_32C;
  }
  else  // 否则分支
  {
    pThis_36E2 = COERCE_FLOAT(sub_41A5E0(this + 878));  // crypt4byte 解密校验（·0x41A590 逆运算）
    pThis_38A2 = COERCE_FLOAT(sub_41A5E0(this + 906));  // crypt4byte 解密校验（·0x41A590 逆运算）
    pThis_3A6 = COERCE_FLOAT(sub_41A5E0(this + 934)) + pThis_38A2 + pThis_36E2;  // crypt4byte 解密校验（·0x41A590 逆运算）
    fld_32C2 = pThis_3A6;
  }
  sub_41A590(LODWORD(fld_32C2));  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  if ( COERCE_FLOAT(sub_41A5E0(this + 976)) < 0.0 )  // crypt4byte 解密校验（·0x41A590 逆运算）
    sub_41A590(0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  result = dword_8F8500;  // 对象链表头
  if ( dword_8F8500 != 0 )  // 对象链表头
  {
    result = sub_456420(dword_8F850C);  // 房间/席位表
    if ( result == v21 && dword_8F8520 != 0 )  // 会话/UDP 管理器
    {
      result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
      if ( result != 0 )  // 若结果非 0（成功）
      {
        result = pArg3;
        switch ( pArg3 )  // 按 pArg3 分派
        {
          case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
          case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
          case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
            pThis_36E3 = (uint64_t)sub_43B5A0(this + 878);  // 防篡读壳（槽值转 float）
            v13 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
            result = sub_426820(v13, 6, pThis_36E3);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
            break;  // 跳出循环/分支
          case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
          case 4:  // case 4 = ENUM_CMDPACKET_EXIT
          case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
            pThis_38A3 = (uint64_t)sub_43B5A0(this + 906);  // 防篡读壳（槽值转 float）
            pThis_38A32 = pThis_38A3;
            v12 = (*(int (/*fastcall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520, HIDWORD(pThis_38A3));  // 调虚槽 +120：动画对象
            result = sub_426820(v12, 7, pThis_38A32);  // 【总入口 case0-7（研究 §12）：0/1/2 横幅模式 · 3 HK_ATTA…】
            break;  // 跳出循环/分支
          default:  // 默认分支
            return result;
        }
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x496320 sub_496320 —— 三元输入探测 → 帧图像重载工厂转发
//   从 dword_8F8520 取 字(word)/子码(byte)/参数(int) 三元组，首字等于 word_77F804 且宿主 +104 非空时，
//   经宿主 vt+1208 通知，最后把三元组转发 ·sub_496010 做帧图像重载（事件号 +48 → 帧结构族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_496320(void *this)  // 实现：三元输入探测 → 帧图像重载工厂转发
{
  int v3; // [esp+4h] [ebp-Ch] BYREF
  uint16_t v4[3]; // [esp+8h] [ebp-8h] BYREF
  uint8_t v5; // [esp+Fh] [ebp-1h] BYREF

  (*(void (/*thiscall*/ **)(int, uint16_t *))(*(uint32_t *)dword_8F8520 + 76))(dword_8F8520, v4);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
  (*(void (/*thiscall*/ **)(int, uint8_t *))(*(uint32_t *)dword_8F8520 + 72))(dword_8F8520, &v5);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
  (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v3);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  if ( v4[0] == (uint16_t)word_77F804  // 本机身份键(ServerId)
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0  // 调虚槽 +120：动画对象
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 104) != 0 )  // 调虚槽 +120：动画对象
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
    if ( (uint8_t)sub_45E680(dword_8F7C04) != 0 )  // 对象表归属判定
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 1208))(dword_8F7C04, v5, v3);  // 调虚槽 +1208
  }
  return sub_496010((int)this, v4[0], v5, v3);  // 帧图像重载工厂（事件号 +48 → sub_495DC0 等）
}



// ------------------------------------------------------------
// 0x4963E0 sub_4963E0 —— 40 字节文案节点初始化（SSO 空串 + 三槽 -1）
//   头三槽写 -1/-1/0，其后 std::string 以容量 15 走 SSO 空串分支（+36=15、+32=0），
//   再经 ·sub_406D00 完成字符串区间赋值。节点 = 12 字节头 + 28 字节 std::string，共 40 字节，与 ·sub_496470 族一致。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4963E0(uint32_t *this)  // 实现：40 字节文案节点初始化（SSO 空串 + 三槽 -1）
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
  *(this + 1) = -1;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  v3 = pThis_3[6];  // v3 = 取 pThis_3[6]
  v7[4] = 0;
  v4 = pThis_3 + 1;
  if ( v3 < 0x10 )  // 若 v3 < 0x10
    v5 = pThis_3 + 1;
  else  // 否则分支
    v5 = (uint32_t *)*v4;
  if ( v3 >= 0x10 )  // 若 v3 >= 0x10
    v4 = (uint32_t *)*v4;
  sub_406D00(pThis_3, v7, (int)v4, (unsigned int)v5 + pThis_3[5]);  // std::string 中段擦除（·sub_401230 erase，pos 与 n 由指针差换算）
  return this;
}



// ------------------------------------------------------------
// 0x496470 sub_496470 —— 40 字节元素区间构造（模板逐份拷贝）
//   从 nArg3 模板元素向 nArg1 起连续 nArg2 份做 40 字节节点构造拷贝（·sub_459690 逐份），返回最后一份结果。
// ------------------------------------------------------------
int /*cdecl*/ sub_496470(int nArg1, int nArg2, int nArg3)  // 实现：40 字节元素区间构造（模板逐份拷贝）
{
  int nArg12; // esi
  int result; // eax
  uint32_t v6[8]; // [esp+0h] [ebp-20h] BYREF

  nArg12 = nArg1;
  v6[4] = v6;
  v6[3] = nArg1;
  v6[7] = 0;
  while ( nArg2 != 0 )  // 条件循环
  {
    result = sub_459690(nArg12, nArg3);  // 单条 40 字节元素拷贝构造
    --nArg2;
    nArg12 += 40;
  }
  return result;
}



// ------------------------------------------------------------
// 0x496510 sub_496510 —— 批量构造 + 返回尾指针
//   调 ·sub_496470 构造 nArg2 份 40 字节元素后，返回末元素之后的位置（nArg1+40×nArg2），便于续写。
// ------------------------------------------------------------
int /*stdcall*/ sub_496510(int nArg1, int nArg2, int nArg3)  // 实现：批量构造 + 返回尾指针
{
  sub_496470(nArg1, nArg2, nArg3);  // 40 字节元素区间构造（模板逐份拷贝）
  return nArg1 + 40 * nArg2;
}



// ============================================================
// §J 0x496540-0x497EA0  异常状态演出表（Common/ActiveStatus/*.ani|ptl）
// ============================================================
// ------------------------------------------------------------
// 0x496540 sub_496540 —— 40 字节元素 vector 区间插入（n 份模板填充）
//   在 +4/+8/+12 三指针描述的 40 字节元素数组上做 insert_n（元素 = 12 字节头 + 28 字节内嵌串，见 ·sub_4963E0）。
//   容量足够时按尾部段长度分流：先经 ·sub_459860 平移尾部，再用 ·sub_496510/·sub_496470 在插入点构造 n 份模板，空隙经 ·sub_570610/·sub_572550 组装；
//   容量不足时按 1.5 倍上限（·sub_5721D0）重分配并搬家前后两段后补插，旧区间经 ·sub_55A010 析构，上限守卫走 ·sub_434730。
// ------------------------------------------------------------
void /*thiscall*/ sub_496540(int *this, char *pszArg2, unsigned int uArg3, int *pDwArg4)  // 实现：40 字节元素 vector 区间插入（n 份模板填充）
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

  dword_796E502 = dword_796E50;  // dword_796E50（栈检 cookie 值）
  v4 = pDwArg4[1];  // v4 = 取 pDwArg4[1]
  v6 = *pDwArg4;
  v35 = &v25;
  v29[0] = v6;
  v29[2] = pDwArg4[2];  // v29[2] = 取 pDwArg4[2]
  pThis = this;
  v29[1] = v4;
  v33 = 15;
  v32 = 0;
  LOBYTE(v31) = 0;
  sub_4014D0((std::_String_base *)v30, pDwArg4 + 3, 0, -1);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  v36 = 0;
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
    fld_e3 = (*(this + 3) - fld_e1) / 40;  // this+12〔nSkillRec12(推断)〕
  else  // 否则分支
    fld_e3 = 0;  // fld_e3=this+12 nSkillRec12
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e2 = (*(this + 2) - fld_e1) / 40;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
    if ( 107374182 - fld_e2 < uArg3 )  // fld_e2=this+8 nSkillRec8
      sub_434730(this);  // vector 超长抛 length_error
    if ( fld_e1 != 0 )  // 若 fld_e1 非 0
      fld_e22 = (*(this + 2) - fld_e1) / 40;  // this+8〔nSkillRec8(推断)〕
    else  // 否则分支
      fld_e22 = 0;  // fld_e22=this+8 nSkillRec8
    if ( fld_e3 >= uArg3 + fld_e22 )  // fld_e3=this+12 nSkillRec12
    {
      fld_e23 = (char *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      fld_e232 = fld_e23;  // fld_e23=this+8 nSkillRec8
      if ( (fld_e23 - pszArg2) / 40 >= uArg3 )  // fld_e23=this+8 nSkillRec8
      {
        v37 = &fld_e23[-40 * uArg3];  // fld_e23=this+8 nSkillRec8
        *(this + 2) = sub_459860(v37, fld_e23, (int)fld_e23);  // 40 字节元素区间拷贝循环
        sub_572550(pszArg2, v37, fld_e232);  // 转发 572400
        sub_570610(pszArg2, &pszArg2[40 * uArg3], v29);  // 文本行组装：4014D0 拼接（数值行）
      }
      else  // 否则分支
      {
        sub_459860(pszArg2, fld_e23, (int)&pszArg2[40 * uArg3]);  // 40 字节元素区间拷贝循环
        fld_e24 = uArg3 - (*(this + 2) - (int)pszArg2) / 40;  // this+8〔nSkillRec8(推断)〕
        fld_e25 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
        LOBYTE(v36) = 3;
        sub_496510(fld_e25, fld_e24, v29);  // 批量构造 + 返回尾指针
        fld_e26 = 40 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;  // this+8〔nSkillRec8(推断)〕
        v36 = 0;
        sub_570610(pszArg2, fld_e26 - 40 * uArg3, v29);  // 文本行组装：4014D0 拼接（数值行）
      }
    }
    else  // 否则分支
    {
      if ( 107374182 - (fld_e3 >> 1) >= fld_e3 )  // fld_e3=this+12 nSkillRec12
        v12 = (fld_e3 >> 1) + fld_e3;  // fld_e3=this+12 nSkillRec12
      else  // 否则分支
        v12 = 0;
      if ( fld_e1 != 0 )  // 若 fld_e1 非 0
        fld_e27 = (*(this + 2) - fld_e1) / 40;  // this+8〔nSkillRec8(推断)〕
      else  // 否则分支
        fld_e27 = 0;  // fld_e27=this+8 nSkillRec8
      if ( v12 < uArg3 + fld_e27 )  // fld_e27=this+8 nSkillRec8
        v12 = uArg3 + sub_5721D0(this);  // 物品信息窗小辅助（15 行）
      v38 = 40 * v12;
      pMem = (char *)operator new(40 * v12);
      fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v36) = 1;
      pMem2 = (char *)sub_459860(fld_e12, pszArg2, (int)pMem);  // 40 字节元素区间拷贝循环
      sub_496470((int)pMem2, uArg3, v29);  // 40 字节元素区间构造（模板逐份拷贝）
      fld_e28 = (uint32_t *)*(this + 2);  // this+8〔nSkillRec8(推断)〕
      pMem2 += 40 * uArg3;
      sub_459860(pszArg2, fld_e28, (int)pMem2);  // 40 字节元素区间拷贝循环
      fld_e13 = *(this + 1);  // this+4〔宿主对象〕
      if ( fld_e13 != 0 )  // 若 fld_e13 非 0
        fld_e13 = (*(this + 2) - fld_e13) / 40;  // this+8〔nSkillRec8(推断)〕
      v17 = fld_e13 + uArg3;
      fld_e14 = (void *)*(this + 1);  // this+4〔宿主对象〕
      if ( fld_e14 != nullptr )  // 若 fld_e14 有效（非空）
      {
        sub_55A010(fld_e14, *(this + 2));  // 信息窗文本（5014C0）
        j__free((void *)*(this + 1));  // this+4〔宿主对象〕
      }
      *(this + 3) = (int)&pMem[v38];  // this+12〔nSkillRec12(推断)〕
      *(this + 2) = (int)&pMem[40 * v17];  // this+8〔nSkillRec8(推断)〕
      *(this + 1) = (int)pMem;  // this+4〔宿主对象〕
    }
  }
  if ( v33 >= 0x10 )  // 若 v33 >= 0x10
    j__free(v31);  // 调 j__free（堆释放）
}


// ------------------------------------------------------------
// 0x496870 sub_496870 —— 单元素插入 + 回填插入位地址
//   先由插入点 nArg3 与首指针算出索引 v6，调 ·sub_496540 插入 1 份模板 uArg4，
//   再回填 *uArg2 = 新首 + 40×v6，即新元素地址（扩容后仍指向插入位）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_496870(int *this, uint32_t *uArg2, int nArg3, uint32_t *uArg4)  // 实现：单元素插入 + 回填插入位地址
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 40 != 0 )  // 若 fld_e1 != 0
    v6 = (nArg3 - fld_e1) / 40;  // fld_e1=this+4 宿主对象
  else  // 否则分支
    v6 = 0;
  sub_496540(this, nArg3, 1u, uArg4);  // 40 字节元素 vector 区间插入（n 份模板填充）
  *uArg2 = *(this + 1) + 40 * v6;  // this+4〔宿主对象〕
  return uArg2;
}



// ------------------------------------------------------------
// 0x4968E0 sub_4968E0 —— 对象三段清零 + 双 40 字节链释放 + 槽默认值
//   先把对象前 0x300 与 +768..+816 清零；按全局域号 dword_8F7A24+12（4/6 与其余）分派两组 0 与 -1.0f 槽默认值（+864..+990 九槽）；
//   释放 +1012 与 +1028 两条 40 字节元素链（逐元素 ·sub_5014C0 析构后 free）并清三指针；
//   最后把 +964/+968/+972 置默认值 -956156672（0xC7023500）。
// ------------------------------------------------------------
int /*fastcall*/ sub_4968E0(int pArg1, int nArg2)  // 实现：对象三段清零 + 双 40 字节链释放 + 槽默认值
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

  memset((void *)pArg1, 0, 0x300u);  // 调 memset（内存按字节填充）
  memset((void *)(pArg1 + 768), 0, 0x60u);  // 调 memset（内存按字节填充）
  v3 = *(uint32_t *)(dword_8F7A24 + 12);  // 登录/选区管理器
  if ( v3 == 4 || v3 == 6 )  // 若 v3 == 4 与/或 v3 == 6
  {
    sub_41A590(pArg1 + 976, nArg2, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 864, v9, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 934, v10, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 906, 0, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 878, v11, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 892, v12, -1082130432);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 920, -1082130432, -1082130432);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 990, v13, -1082130432);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 948, v14, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  else  // 否则分支
  {
    sub_41A590(pArg1 + 990, nArg2, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 920, 0, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 892, v4, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 976, v5, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 864, v6, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 934, 0, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 906, v7, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 878, v8, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
    sub_41A590(pArg1 + 948, 0, 0);  // crypt4byte 加密初始化（随机密钥 + 双校验字）
  }
  v15 = *(char **)(pArg1 + 1012);  // pArg1+1012〔uGrabA1012(推断)〕
  if ( v15 != nullptr )  // 若 v15 有效（非空）
  {
    for ( i = *(char **)(pArg1 + 1016); v15 != i; v15 += 40 )  // 遍历循环
      sub_5014C0(v15);
    j__free(*(void **)(pArg1 + 1012));  // pArg1+1012〔uGrabA1012(推断)〕
  }
  *(uint32_t *)(pArg1 + 1012) = 0;  // pArg1+1012〔uGrabA1012(推断)〕
  *(uint32_t *)(pArg1 + 1016) = 0;  // pArg1+1016〔uGrabB1016(推断)〕
  *(uint32_t *)(pArg1 + 1020) = 0;  // pArg1+1020〔pAnimHandleArr(推断)〕
  v17 = *(char **)(pArg1 + 1028);
  if ( v17 != nullptr )  // 若 v17 有效（非空）
  {
    for ( j = *(char **)(pArg1 + 1032); v17 != j; v17 += 40 )  // 遍历循环
      sub_5014C0(v17);
    j__free(*(void **)(pArg1 + 1028));  // 调 j__free（堆释放）
  }
  *(uint32_t *)(pArg1 + 1028) = 0;
  *(uint32_t *)(pArg1 + 1032) = 0;
  *(uint32_t *)(pArg1 + 1036) = 0;
  *(uint32_t *)(pArg1 + 964) = -956156672;  // pArg1+964〔nBlobSize〕
  *(uint32_t *)(pArg1 + 968) = -956156672;  // pArg1+968〔pBlobData〕
  *(uint32_t *)(pArg1 + 972) = -956156672;  // pArg1+972〔uCfgD972(推断)〕
  return -956156672;
}



// ------------------------------------------------------------
// 0x496B40 sub_496B40 —— 尾部追加（满则走插入扩容路径）
//   若数组首指针为空或尾指针已达容量，则改走 ·sub_496870 的插入路径完成扩容追加；
//   否则在尾位置用 ·sub_496470 就地构造 1 份 uArg2，并把尾指针后移 40 字节。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_496B40(int *this, uint32_t *uArg2)  // 实现：尾部追加（满则走插入扩容路径）
{
  int fld_e1; // edi
  unsigned int fld_e2; // ecx
  int fld_e22; // edi
  uint32_t *result; // eax

  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
    fld_e2 = (*(this + 2) - fld_e1) / 40;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) / 40 )  // 若 fld_e1 == 0
    return sub_496870(this, &uArg2, *(this + 2), uArg2);  // 单元素插入 + 回填插入位地址
  fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = (uint32_t *)sub_496470(fld_e22, 1, (int)uArg2);  // 40 字节元素区间构造（模板逐份拷贝）
  *(this + 2) = fld_e22 + 40;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x496BD0 sub_496BD0 —— 异常演出节点入链（按类型分流 +252/+256）
//   取 pArg2 宿主 id（vt+376）与全局 dword_8F7C04 比对，不一致才组装节点：先 ·sub_4963E0 初始化，
//   再填 id 三槽（vt+1032 结果的 +68、vt+340 结果的首槽与 +4 起字符串）；
//   按 pArg2[1943] 分流：3 → 追加 this+252 链，1/2 → this+256 链（均经 ·sub_496B40），尾段释放临时串。
// ------------------------------------------------------------
void /*thiscall*/ sub_496BD0(int *this, uint32_t *pArg2)  // 实现：异常演出节点入链（按类型分流 +252/+256）
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

  dword_796E502 = dword_796E50;  // dword_796E50（栈检 cookie 值）
  v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg2 + 376))(pArg2);  // 调虚槽 +376：坐标同步包（type 37）
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) != v3 )  // 调虚槽 +376：坐标同步包（type 37）
  {
    sub_4963E0(v11);  // 40 字节文案节点初始化（SSO 空串 + 三槽 -1）
    v4 = *pArg2;
    v15 = 0;
    v5 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 1032))(pArg2);
    v6 = *pArg2;
    v11[2] = *(uint32_t *)(v5 + 68);
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(v6 + 340))(pArg2);  // 调虚槽 +340：三元组基址（+284，vt+340）
    v8 = *pArg2;
    v11[1] = *v7;
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 340))(pArg2);  // 调虚槽 +340：三元组基址（+284，vt+340）
    sub_4014D0(v12, (size_t *)(v9 + 4), 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    v11[0] = pArg2[1943];  // v11[0] = 取 pArg2[1943]
    if ( v11[0] == 3 )
    {
      sub_496B40(this + 252, v11);  // 尾部追加（满则走插入扩容路径）
    }
    else  // 否则分支
    {
      v10 = pArg2[1943];  // v10 = 取 pArg2[1943]
      if ( v10 != 1 && v10 != 2 )  // 若 v10 != 1 与/或 v10 != 2
      {
        if ( v13 < 0x10 )  // 若 v13 < 0x10
          return;
        goto LABEL_10;
      }
      sub_496B40(this + 256, v11);  // 尾部追加（满则走插入扩容路径）
    }
    if ( v13 < 0x10 )  // 若 v13 < 0x10
      return;
LABEL_10:  // 标签 LABEL_10（跳转合流点）
    j__free((void *)v12[1]);  // 调 j__free（堆释放）
  }
}



// ------------------------------------------------------------
// 0x496CE0 sub_496CE0 —— 播放状态对象复位（+104=4、+104..120 连续 5 格 1065353216=1.0f）
// ------------------------------------------------------------
int /*thiscall*/ sub_496CE0(int this)  // 实现：播放状态对象复位（+104=4、+104..120 连续 5 格 1065353216=1.0f）
{
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = 17;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 36) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  sub_699070(1);  // 【clock_bind_domain(clk, newDomainId)】
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint8_t *)(this + 96) = 0;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint8_t *)(this + 97) = 0;  // this+97〔bFlag97〕
  *(uint32_t *)(this + 124) = 0;  // this+124〔pAuraAnim(推断)〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 140) = 0;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 196) = 0;
  *(uint32_t *)(this + 200) = 0;  // this+200〔nMainState(推断)〕
  *(uint8_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 100) = 4;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 104) = 1065353216;  // this+104 = 1.0f
  *(uint32_t *)(this + 108) = 1065353216;  // this+108 = 1.0f
  *(uint32_t *)(this + 112) = 1065353216;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 116) = 1065353216;  // this+116 = 1.0f
  *(uint32_t *)(this + 120) = 1065353216;  // this+120〔pAnimObj〕
  return 1065353216;  // 常量 1.0f
}



// ------------------------------------------------------------
// 0x496DA0 sub_496DA0 —— 倒计时启动（解冻时钟 + 清零标志）
//   先解冻 +60 处时钟（·sub_698FE0）并清 +73/+74 两标志，把 nArg2 写入 +92，
//   最后以（时长 nArg2，起始 0）调 ·sub_698F90 启动倒计时。
// ------------------------------------------------------------
char /*thiscall*/ sub_496DA0(uint32_t *this, int nArg2)  // 实现：倒计时启动（解冻时钟 + 清零标志）
{
  int pThis_F; // esi

  pThis_F = (int)(this + 15);  // this+60〔nFadeValue60(推断)〕
  sub_698FE0((int)(this + 15));  // 【clock_unfreeze(clk)】
  *(uint8_t *)(pThis_F + 13) = 0;  // pThis_F=this+60 nFadeValue60
  *(uint8_t *)(pThis_F + 14) = 0;  // pThis_F=this+60 nFadeValue60
  *(this + 23) = nArg2;  // this+92〔pFxObjC(推断)〕
  return sub_698F90(pThis_F, nArg2, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// ------------------------------------------------------------
// 0x496DD0 sub_496DD0 —— 致盲遮罩绘制（Blind1.img 懒加载 + 50px 网格平铺）
//   首次调用时经资源管理器加载 Common/ActiveStatus/Blind1.img 并取三张子图（·sub_418DD0，存 dword_9A0130[0..2]）；
//   取角色坐标（·sub_4239A0）与插值族值（·sub_4239D0，pszArg1 选 0.0/1.0）换算到 (v6,v5) = (x-245, y-345)，
//   先画中心图（pszArg1==0 用第 0 张否则第 1 张），再以 50 像素步长在 640×480 内平铺第 2 张图，跳过以中心为原点的 500×500 区域。
// ------------------------------------------------------------
void /*cdecl*/ sub_496DD0(char pszArg1)  // 实现：致盲遮罩绘制（Blind1.img 懒加载 + 50px 网格平铺）
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

  dword_8F7C042 = dword_8F7C04;  // 本地玩家对象
  if ( dword_8F7C04 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 80))(dword_8F7C04) != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  {
    if ( dword_9A0130[0] == 0 )
    {
      v2 = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84B8 + 60))(  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
                       dword_8F84B8,
                       "Common/ActiveStatus/Blind1.img");  // 资源 Common/ActiveStatus/Blind1.img
      dword_9A0130[0] = sub_418DD0(v2, 0);  // dword_9A0130[0] = 调 sub_418DD0 返回值
      dword_9A0134 = sub_418DD0(v2, 1u);  // dword_9A0134 = 调 sub_418DD0 返回值
      dword_9A0138 = sub_418DD0(v2, 2u);  // dword_9A0138 = 调 sub_418DD0 返回值
    }
    v3 = sub_4239A0(dword_8F7C042);  // 取值后转坐标与方向合成
    if ( pszArg1 != 0 )  // 若 pszArg1 非 0
      v4 = sub_4239D0(dword_8F7C042, 0.0);  // 取值后转插值族
    else  // 否则分支
      v4 = sub_4239D0(dword_8F7C042, 1.0);  // 取值后转插值族
    v5 = v4 - 345;
    v6 = v3 - 245;
    v15 = v5;
    pObj2 = dword_9A0130[pszArg1 == 0];  // pObj2 = 取 dword_9A0130[pszArg1 == 0]
    if ( pObj2 != 0 )  // 若 pObj2 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, v6, v5, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    v8 = v6;
    v14 = v6;
    v9 = v5;
    if ( v6 > 0 )  // 若 v6 > 0
    {
      v14 = v6 - 50 * ((v6 - 1) / 0x32u + 1);
      v8 = v14;
    }
    if ( v5 > 0 )  // 若 v5 > 0
      v9 = v5 - 50 * ((v5 - 1) / 0x32u + 1);
    v10 = v9;
    if ( v9 < 480 )  // 若 v9 < 480
    {
      pObj = dword_9A0138;
      v13 = v9;
      do  // do-while 循环体起点
      {
        v12 = v8;
        if ( v8 < 640 )  // 若 v8 < 640
        {
          do  // do-while 循环体起点
          {
            if ( (v12 < v6 || v12 >= v6 + 500 || v10 < v15 || v10 >= v15 + 500) && pObj != 0 )  // 若 v12 < v6 与/或 v12 >= v6 与/或 v10 < v15
            {
              (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(dword_9A0138, v12, v10, dword_79C0B0);  // 调虚槽 +152：效果通道 3
              pObj = dword_9A0138;
            }
            v8 += 50;
            v12 = v8;
          }
          while ( v8 < 640 );  // 条件循环
          v8 = v14;
          v9 = v13;
        }
        v9 += 50;
        v13 = v9;
        v10 = v9;
      }
      while ( v9 < 480 );  // 条件循环
    }
  }
}



// ------------------------------------------------------------
// 0x496F80 sub_496F80 —— 状态号映射表（12 直通、15→14、16→15，其余→16）
//   纯查表：0..11 原样返回，15→14、16→15，其余（含 12/13）归 16。【推断】用于把 16 档状态压到 17 档索引。
// ------------------------------------------------------------
int /*cdecl*/ sub_496F80(int nArg1)  // 实现：状态号映射表（12 直通、15→14、16→15，其余→16）
{
  int result; // eax

  switch ( nArg1 )  // 按 nArg1 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = 0;
      break;  // 跳出循环/分支
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = 1;
      break;  // 跳出循环/分支
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      result = 2;
      break;  // 跳出循环/分支
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      result = 3;
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = 4;
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      result = 5;
      break;  // 跳出循环/分支
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      result = 6;
      break;  // 跳出循环/分支
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      result = 7;
      break;  // 跳出循环/分支
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      result = 8;
      break;  // 跳出循环/分支
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      result = 9;
      break;  // 跳出循环/分支
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      result = 10;
      break;  // 跳出循环/分支
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      result = 11;
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = 14;
      break;  // 跳出循环/分支
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      result = 15;
      break;  // 跳出循环/分支
    default:  // 默认分支
      result = 16;
      break;  // 跳出循环/分支
  }
  return result;
}



// ------------------------------------------------------------
// 0x497040 sub_497040 —— 状态号映射表（12 直通、14→15、15→16，其余→17）
//   与 ·sub_496F80 同构（差异：14→15、15→16，缺省归 17；两表互补用于不同档位索引换算）。
// ------------------------------------------------------------
int /*cdecl*/ sub_497040(int nArg1)  // 实现：状态号映射表（12 直通、14→15、15→16，其余→17）
{
  int result; // eax

  switch ( nArg1 )  // 按 nArg1 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = 0;
      break;  // 跳出循环/分支
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      result = 1;
      break;  // 跳出循环/分支
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
      result = 2;
      break;  // 跳出循环/分支
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      result = 3;
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      result = 4;
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      result = 5;
      break;  // 跳出循环/分支
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      result = 6;
      break;  // 跳出循环/分支
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      result = 7;
      break;  // 跳出循环/分支
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      result = 8;
      break;  // 跳出循环/分支
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      result = 9;
      break;  // 跳出循环/分支
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      result = 10;
      break;  // 跳出循环/分支
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      result = 11;
      break;  // 跳出循环/分支
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      result = 15;
      break;  // 跳出循环/分支
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
      result = 16;
      break;  // 跳出循环/分支
    default:  // 默认分支
      result = 17;
      break;  // 跳出循环/分支
  }
  return result;
}



// ------------------------------------------------------------
// 0x497100 ?_Get_future_error_what@std@@YAPBDH@Z_0
// ------------------------------------------------------------
const char */*cdecl*/ std::_Get_future_error_what(int nArg1)  // 状态号映射表（12 直通、14→15、15→16，其余→17）
{
  return (const char *)dword_9A0140[nArg1];
}



// ------------------------------------------------------------
// 0x497110 sub_497110 —— 虚转发 vt+84
//   无参转发本对象虚表 +84 槽，供 ·sub_497190/·sub_497300 族作状态推进入口。
// ------------------------------------------------------------
int /*thiscall*/ sub_497110(void *this)  // 实现：虚转发 vt+84
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 84))(this);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
}



// ------------------------------------------------------------
// 0x497120 sub_497120 —— 状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
//   以 39 为终点对第 pArg1 组起止值做区间线性插值（·sub_4049C0），t 取 nArg2-1。【推断】nArg2 为 1..40 档位。
// ------------------------------------------------------------
int /*cdecl*/ sub_497120(int pArg1, int nArg2)  // 实现：状态时长插值（flt_6CB268 → flt_6CB26C，tEnd=39）
{
  return sub_4049C0(*(&flt_6CB268 + 2 * pArg1), flt_6CB26C[2 * pArg1], nArg2 - 1, 39);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
}



// ------------------------------------------------------------
// 0x497150 sub_497150 —— 第二组状态时长插值（flt_6CB2F0 → flt_6CB2F4）
//   与 ·sub_497120 同构（差异：表基址 flt_6CB2F0/flt_6CB2F4，返回值丢弃）。
// ------------------------------------------------------------
void /*cdecl*/ sub_497150(int pArg1, int nArg2)  // 实现：第二组状态时长插值（flt_6CB2F0 → flt_6CB2F4）
{
  sub_4049C0(*(&flt_6CB2F0 + 2 * pArg1), flt_6CB2F4[2 * pArg1], nArg2 - 1, 39);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
}



// ------------------------------------------------------------
// 0x497190 sub_497190 —— 子链级联播放（+20 链 + 恒真标志）
//   对 *(this+5)（即 +20 处子动画链）执行播放/暂停级联 ·sub_4939E0，
//   第二参数取函数指针非空比较，编译期恒为真。【推断】原意为常量真值。
// ------------------------------------------------------------
char /*thiscall*/ sub_497190(int *this)  // 实现：子链级联播放（+20 链 + 恒真标志）
{
  return sub_4939E0(*(this + 5), sub_497180 != nullptr);  // 播放/暂停级联（递归子链 +204）
}



// ------------------------------------------------------------
// 0x4971B0 sub_4971B0 —— 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
//   按 pArg1 分三族：0/2/4/6/9/11/12/13 直接查 dword_6CB220 乘 1000；1/3/5/7/8/15/16 经 flt_6CB268→flt_6CB26C 插值乘 1000；10/14 归 0（单位毫秒）。
//   若 nArg3 具备 529 号特性（vt+40），按 vt+672(nArg3,3) 子对象与本对象各自帧数×速率（+4 与 +18 槽）之比扣减：时长 ×(子帧数×子速率/2)÷(帧数×速率)；
//   【推断】用于动作时长随攻速/装备缩短，返回值下限夹 0。
// ------------------------------------------------------------
int /*cdecl*/ sub_4971B0(int pArg1, int nArg2, int nArg3)  // 实现：状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
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
  switch ( pArg1 )  // 按 pArg1 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
    case 12:  // case 12 = ENUM_CMDPACKET_RESPONSE_PEER
    case 13:  // case 13 = ENUM_CMDPACKET_SET_PARTY_INFO
      v3 = 1000 * dword_6CB220[pArg1];
      goto LABEL_5;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
    case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
    case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
    case 15:  // case 15 = ENUM_CMDPACKET_WALKOUT_PARTY_MEMBER
    case 16:  // case 16 = ENUM_CMDPACKET_START_GAME
      v3 = (uint64_t)(sub_4049C0(*(&flt_6CB268 + 2 * pArg1), flt_6CB26C[2 * pArg1], nArg2 - 1, 39) * 1000.0);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      goto LABEL_5;
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
    case 14:  // case 14 = ENUM_CMDPACKET_LEAVE_PARTY
      v3 = 0;
LABEL_5:  // 标签 LABEL_5（跳转合流点）
      v10 = v3;
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  if ( nArg3 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 40))(nArg3, 529) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 684))(nArg3);  // 调虚槽 +684：取攻击上下文
    sub_41A5E0(v4);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v5 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 672))(nArg3, 3);  // 调虚槽 +672：自身 HP
    v9 = sub_41A5E0(v5 + 4);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v8 = COERCE_FLOAT(sub_41A5E0(v5 + 18));  // crypt4byte 解密校验（·0x41A590 逆运算）
    v6 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 672))(nArg3, 3);  // 调虚槽 +672：自身 HP
    v11 = sub_41A5E0(v6 + 4);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v3 -= (uint64_t)((double)((int)(uint64_t)((double)v11 * COERCE_FLOAT(sub_41A5E0(v6 + 18)))  // crypt4byte 解密校验（·0x41A590 逆运算）
                                    / 2
                                    / (int)(uint64_t)((double)v9 * v8))  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
                           * (double)v10);
  }
  if ( v3 >= 0 )  // 若 v3 >= 0
    return v3;
  else  // 否则分支
    return 0;
}



// ------------------------------------------------------------
// 0x497300 sub_497300 —— 状态档位设置（1..40 夹取 → 时长下发 + 播放分派）
//   档位 ArgList 存 +12 并夹到 40（越界走 off_77F3FC 断言），nArg3 存 +16；档位 >0 时经 ·sub_4971B0(档位, 档内值, 宿主) 求毫秒时长交 vt+84，
//   再以（旧档==0）作布尔发 vt+60，尾调宿主 vt+676(this+4, 1)；档位为 0 时，若已过倒计时且模式 +8 == 7 则记 +88 = +92，改走 vt+64 停止。
// ------------------------------------------------------------
int /*thiscall*/ sub_497300(int *this, int ArgList, int nArg3)  // 实现：状态档位设置（1..40 夹取 → 时长下发 + 播放分派）
{
  int fld_e3; // ebx
  unsigned int fld_e23; // edi
  int v7; // edi
  int fld_e2; // eax  | +0x0008 → 状态模式号（CNRDActiveStatus；va=004973B0）
  int v9; // ecx

  fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
  *(this + 3) = ArgList;  // this+12〔nSkillRec12(推断)〕
  if ( ArgList > 40 )  // 若 ArgList > 40
  {
    off_77F3FC((char *)&byte_6CB378, ArgList, 40);  // 引擎日志输出函数(printf 风格)
    *(this + 3) = 40;  // this+12〔nSkillRec12(推断)〕
  }
  *(this + 4) = nArg3;  // this+16〔nChannelTypeSel(推断)〕
  if ( ArgList > 0 )  // 若 ArgList > 0
  {
    v7 = *this;
    fld_e2 = sub_4971B0(*(this + 2), *(this + 3), *(this + 1));  // 状态时长求值（1000 倍常量表 / 39 档插值 + 攻速修正）
    (*(void (/*thiscall*/ **)(int *, int))(v7 + 84))(this, fld_e2);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
    LOBYTE(v9) = fld_e3 == 0;  // fld_e3=this+12 nSkillRec12
    (*(void (/*thiscall*/ **)(int *, int))(*this + 60))(this, v9);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 676))(*(this + 1), 1);  // this+4〔宿主对象〕
  }
  else  // 否则分支
  {
    fld_e23 = *(this + 23);  // this+92〔pFxObjC(推断)〕
    if ( fld_e23 > sub_699000((int)(this + 15)) && *(this + 2) == 7 )  // 【clock_now(clk)】
      *(this + 22) = fld_e23;  // this+88〔pFxObjB(推断)〕
    (*(void (/*thiscall*/ **)(int *))(*this + 64))(this);  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
    return (*(int (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1) + 676))(*(this + 1), 1);  // this+4〔宿主对象〕
  }
}



// ------------------------------------------------------------
// 0x4973B0 sub_4973B0 —— 暂停/恢复级联（按模式号分派子动画链）
//   仅在 +96 状态变更时生效：按 pszArg2 冻结（·sub_699030）或解冻（·sub_698FE0）本对象 +60 处时钟，
//   再按模式号 *(this+8) 把播放/暂停经 ·sub_4939E0 广播到 +20..+28 的 1~3 条子动画链（模式 1 三条、3/5 两条、0/6/8/12/15 单条或双条、16 三条，模式 7 走 ·sub_497190，其余不处理）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4973B0(int this, char pszArg2)  // 实现：暂停/恢复级联（按模式号分派子动画链）
{
  int pThis_3C; // ecx
  int *pThis_14; // esi
  int i; // edi
  int *pThis_142; // esi
  int j; // edi
  int *pThis_143; // esi
  int k; // edi

  if ( *(uint8_t *)(this + 96) != pszArg2 )  // this+96〔nStatusMode(推断)〕等 2 字段
  {
    *(uint8_t *)(this + 96) = pszArg2;  // this+96〔nStatusMode(推断)〕等 2 字段
    pThis_3C = this + 60;
    if ( pszArg2 != 0 )  // 若 pszArg2 非 0
      sub_699030(pThis_3C);  // 【clock_freeze(clk)】
    else  // 否则分支
      sub_698FE0(pThis_3C);  // 【clock_unfreeze(clk)】
    switch ( *(uint32_t *)(this + 8) )  // 按 *(uint32_t *)(this + 8) 分派
    {
      case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
        sub_4939E0(*(uint32_t *)(this + 20), 1);  // 播放/暂停级联（递归子链 +204）
        break;  // 跳出循环/分支
      case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
        pThis_14 = (int *)(this + 20);  // this+20〔nPage(推断)〕等 2 字段
        for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
          sub_4939E0(*pThis_14++, pszArg2);  // 播放/暂停级联（递归子链 +204）
        break;  // 跳出循环/分支
      case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        pThis_142 = (int *)(this + 20);  // this+20〔nPage(推断)〕等 2 字段
        for ( j = 2; j != 0; --j )  // 循环：j 从 2 递减到 0
          sub_4939E0(*pThis_142++, pszArg2);  // 播放/暂停级联（递归子链 +204）
        break;  // 跳出循环/分支
      case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        pThis_143 = (int *)(this + 20);  // this+20〔nPage(推断)〕等 2 字段
        for ( k = 2; k != 0; --k )  // 循环：k 从 2 递减到 0
          sub_4939E0(*pThis_143++, pszArg2);  // 播放/暂停级联（递归子链 +204）
        break;  // 跳出循环/分支
      case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      case 0xC:
        sub_4939E0(*(uint32_t *)(this + 20), pszArg2);  // 播放/暂停级联（递归子链 +204）
        break;  // 跳出循环/分支
      case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
        sub_497190(this);  // 子链级联播放（+20 链 + 恒真标志）
        break;  // 跳出循环/分支
      case 0xF:
        sub_4939E0(*(uint32_t *)(this + 20), pszArg2);  // 播放/暂停级联（递归子链 +204）
        sub_4939E0(*(uint32_t *)(this + 24), pszArg2);  // 播放/暂停级联（递归子链 +204）
        break;  // 跳出循环/分支
      case 0x10:
        sub_4939E0(*(uint32_t *)(this + 20), pszArg2);  // 播放/暂停级联（递归子链 +204）
        sub_4939E0(*(uint32_t *)(this + 24), pszArg2);  // 播放/暂停级联（递归子链 +204）
        sub_4939E0(*(uint32_t *)(this + 28), pszArg2);  // 播放/暂停级联（递归子链 +204）
        break;  // 跳出循环/分支
      default:  // 默认分支
        return;
    }
  }
}



// ------------------------------------------------------------
// 0x497500 sub_497500 —— 5 组指针对释放（228 字节对象 + 虚析构）
//   对 +20..+36 与 +40..+56 两组错开 5 槽的指针数组共 5 组：对象槽先交 ·sub_42AF90 处理，再以 ·sub_657740(对象, 228) 释放该 228 字节对象，
//   伴随槽走虚表首槽 (obj, 1) 释放；两数组槽位随后全部清空。
// ------------------------------------------------------------
int /*thiscall*/ sub_497500(char *this)  // 实现：5 组指针对释放（228 字节对象 + 虚析构）
{
  int (/*thiscall*/ ****pThis_28)(uint32_t, int); // esi
  int i; // ebx
  int v3; // edi
  int result; // eax
  int (/*thiscall*/ ***v5)(uint32_t, int); // ecx
  bool v6; // zf

  pThis_28 = (int (/*thiscall*/ ****)(uint32_t, int))(this + 40);  // this+160〔fAdd160(推断)〕
  for ( i = 5; i != 0; --i )  // 循环：i 从 5 递减到 0
  {
    v3 = (int)*(pThis_28 - 5);  // pThis_28=this+160 fAdd160
    if ( v3 != 0 )  // 若 v3 非 0
    {
      sub_42AF90((void **)*(pThis_28 - 5));  // 帧对象析构（帧数组 + 元素数组）
      result = sub_657740(v3, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    v5 = *pThis_28;  // pThis_28=this+160 fAdd160
    v6 = *pThis_28 == nullptr;  // pThis_28=this+160 fAdd160
    *(pThis_28 - 5) = nullptr;  // pThis_28=this+160 fAdd160
    if ( !v6 )
      result = (**v5)(v5, 1);  // 调 v5 的虚函数（vt+0）
    *pThis_28++ = nullptr;  // pThis_28=this+160 fAdd160
  }
  return result;
}



// ------------------------------------------------------------
// 0x497560 sub_497560 —— 石化状态演出装配（StoneCurse.ani + StoneCursing/StoneCurseDestroy.ptl 挂帧 +40/+44）
// ------------------------------------------------------------
float */*thiscall*/ sub_497560(int this)  // 实现：石化状态演出装配（StoneCurse.ani + StoneCursing/StoneCurseDestroy.ptl 挂帧 +40/+4…
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

  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/StoneCurse.ani", 1);  // 动画件构造（资源 id 版）
  else  // 否则分支
    v2 = 0;
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  *(uint32_t *)(this + 20) = v2;  // this+20〔nPage(推断)〕等 2 字段
  result = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 688))(fld_4);  // 调虚槽 +688：附加块基址 this+6160
  if ( *((uint32_t *)result + 3) != 0 )
  {
    result = (float *)(*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));  // 调虚槽 +688：附加块基址 this+6160
    if ( *((uint32_t *)result + 3) != 0 )
    {
      fld_42 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));  // 调虚槽 +688：附加块基址 this+6160
      result = (float *)sub_4924C0(*(int **)(fld_42 + 12), 0);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
      if ( result != nullptr && *(uint32_t *)result != 0 )  // 若 result != nullptr
      {
        *(float *)(this + 116) = (double)*(unsigned int *)(*(uint32_t *)result + 20) * result[5] * 0.016666668;  // this+116〔会话上下文〕
        v6 = (double)*(unsigned int *)(*(uint32_t *)result + 24) * result[6];
        fld_74 = *(float *)(this + 116);  // this+116〔会话上下文〕
        fld_14 = *(uint32_t **)(this + 20);  // fld_14 = 读 this+20
        Block = v6 * 0.016666668;
        *(float *)(this + 120) = Block;  // this+120〔pAnimObj〕
        sub_4920E0(fld_14, fld_74, Block);  // 批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
        pMem = operator new(0x12Cu);  // new(300 字节) 分配对象
        if ( pMem != nullptr )  // 若 pMem 有效（非空）
          v10 = sub_428F30(pMem, (int)"Common/ActiveStatus/Particle/StoneCursing.ptl", 0);  // CNRDObjectParticleCreater 构造
        else  // 否则分支
          v10 = nullptr;  // v10 = 空指针
        *(uint32_t *)(this + 40) = v10;  // this+40〔bStateSub40(推断)〕等 2 字段
        pMem2 = operator new(0x12Cu);  // new(300 字节) 分配对象
        if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
        {
          result = (float *)sub_428F30(pMem2, (int)"Common/ActiveStatus/Particle/StoneCurseDestroy.ptl", 0);  // CNRDObjectParticleCreater 构造
          *(uint32_t *)(this + 44) = result;  // this+44〔nExpireMs(推断)〕等 2 字段
        }
        else  // 否则分支
        {
          *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
          return nullptr;  // 返回 空指针
        }
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4976E0 sub_4976E0 —— 冰冻状态演出装配（Freeze1/2/3.ani 按强度分档）
// ------------------------------------------------------------
float */*thiscall*/ sub_4976E0(int this)  // 实现：冰冻状态演出装配（Freeze1/2/3.ani 按强度分档）
{
  int v2; // eax
  uint32_t **pThis_14; // edi
  int v4; // eax
  int v5; // eax
  int fld_4; // ecx
  float *result; // eax
  int fld_42; // eax
  int v9; // ebx

  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze1.ani", 1);  // 动画件构造（资源 id 版）
  else  // 否则分支
    v2 = 0;
  pThis_14 = (uint32_t **)(this + 20);  // this+80〔nAuraStage(推断)〕
  *(uint32_t *)(this + 20) = v2;  // this+20〔nPage(推断)〕等 2 字段
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v4 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze2.ani", 1);  // 动画件构造（资源 id 版）
  else  // 否则分支
    v4 = 0;
  *(uint32_t *)(this + 24) = v4;  // this+24〔nPageMax(推断)〕等 2 字段
  if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
    v5 = sub_431860((char)"Common/ActiveStatus/Animation/Freeze3.ani", 1);  // 动画件构造（资源 id 版）
  else  // 否则分支
    v5 = 0;
  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  *(uint32_t *)(this + 28) = v5;  // this+28〔pPanelVec(推断)〕等 2 字段
  result = (float *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_4 + 688))(fld_4);  // 调虚槽 +688：附加块基址 this+6160
  if ( *((uint32_t *)result + 3) != 0 )
  {
    fld_42 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4) + 688))(*(uint32_t *)(this + 4));  // 调虚槽 +688：附加块基址 this+6160
    result = (float *)sub_4924C0(*(int **)(fld_42 + 12), 0);  // 按索引取帧并确保图像就绪（帧+4 → 管理器 vtable+56 → sub_418DD0 → 帧+0）
    if ( result != nullptr && *(uint32_t *)result != 0 )  // 若 result != nullptr
    {
      *(float *)(this + 108) = (double)*(unsigned int *)(*(uint32_t *)result + 20) * result[5] * 0.0076923077;  // this+108〔nAdd108(推断)〕
      v9 = 3;
      *(float *)(this + 112) = (double)*(unsigned int *)(*(uint32_t *)result + 24) * result[6] * 0.0071428572;  // this+112〔pHostComp112〕
      do  // do-while 循环体起点
      {
        result = (float *)sub_4920E0(*pThis_14++, *(float *)(this + 108), *(float *)(this + 112));  // 批量改写全帧缩放（帧+20/+24；主循环 4 帧展开=步长 352）；递归子链 +204
        --v9;
      }
      while ( v9 != 0 );  // 条件循环
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x497840 sub_497840 —— ★异常状态→动画/粒子 装配总表
//   Slow→Stun1/2→Curse→Blind1/2→Lightning→Sleep→Burn→Bleeding(+12Age)→Haste→
//   Bless1/2→Confuse(+Glow)→Hold；+244 状态槽；共用 sub_42FCB0/431860 图像创建。
// ------------------------------------------------------------
void /*thiscall*/ sub_497840(int *this, void *Block, int nArg3)  // 实现：异常状态→动画/粒子 装配总表
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

  *(this + 2) = (int)Block;  // this+8〔nSkillRec8(推断)〕
  *(this + 1) = nArg3;  // this+4〔宿主对象〕
  switch ( (unsigned int)Block )  // 按 (unsigned int)Block 分派
  {
    case 0u:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
      if ( sub_42FCB0(228) == 0 )  // CRT 一次性初始化
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Slow.ani", 1);  // 动画件构造（资源 id 版）
      goto LABEL_62;
    case 1u:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      sub_4976E0(this);  // 冰冻状态演出装配（Freeze1/2/3.ani 按强度分档）
      return;
    case 2u:  // case 2 = ENUM_CMDPACKET_LOGIN
      pMem = operator new(0x12Cu);  // new(300 字节) 分配对象
      if ( pMem != nullptr )  // 若 pMem 有效（非空）
        *(this + 10) = (int)sub_428F30(pMem, (int)"Common/ActiveStatus/Particle/PoisonParticle.ptl", *(this + 1));  // CNRDObjectParticleCreater 构造
      else  // 否则分支
        *(this + 10) = 0;  // this+40〔bStateSub40(推断)〕
      return;
    case 3u:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v17 = sub_431860((char)"Common/ActiveStatus/Animation/Stun1.ani", 1);  // 动画件构造（资源 id 版）
      else  // 否则分支
        v17 = 0;
      *(this + 5) = v17;  // this+20〔nPage(推断)〕
      if ( sub_42FCB0(228) == 0 )  // CRT 一次性初始化
        goto LABEL_44;
      *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/Stun2.ani", 1);  // 动画件构造（资源 id 版）
      return;
    case 4u:  // case 4 = ENUM_CMDPACKET_EXIT
      pMem2 = operator new(0x12Cu);  // new(300 字节) 分配对象
      if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
        fld_e1 = sub_428F30(pMem2, (int)"Common/ActiveStatus/Particle/CurseParticle.ptl", *(this + 1));  // CNRDObjectParticleCreater 构造
      else  // 否则分支
        fld_e1 = nullptr;  // fld_e1 = 空指针
      fld_e12 = *(this + 1);  // this+4〔宿主对象〕
      *(this + 10) = (int)fld_e1;  // this+40〔bStateSub40(推断)〕
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e1 + 112))(fld_e1, fld_e12);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      return;
    case 5u:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v21 = sub_431860((char)"Common/ActiveStatus/Animation/Blind1.ani", 1);  // 动画件构造（资源 id 版）
      else  // 否则分支
        v21 = 0;
      *(this + 5) = v21;  // this+20〔nPage(推断)〕
      if ( sub_42FCB0(228) == 0 )  // CRT 一次性初始化
        goto LABEL_44;
      *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/Blind2.ani", 1);  // 动画件构造（资源 id 版）
      return;
    case 6u:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      if ( sub_42FCB0(228) == 0 )  // CRT 一次性初始化
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Lightning.ani", 1);  // 动画件构造（资源 id 版）
      goto LABEL_62;
    case 7u:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
      sub_497560(this);  // 石化状态演出装配（StoneCurse.ani + StoneCursing/StoneCurseDestroy.ptl 挂帧 +40/+44）
      return;
    case 8u:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
      if ( sub_42FCB0(228) == 0 )  // CRT 一次性初始化
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Sleep.ani", 1);  // 动画件构造（资源 id 版）
      goto LABEL_62;
    case 9u:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v5 = sub_431860((char)"Common/ActiveStatus/Animation/ActiveStatus_BurnDamage_Effect.ani", 1);  // 动画件构造（资源 id 版）
      else  // 否则分支
        v5 = 0;
      *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
      goto LABEL_62;
    case 0xBu:
      if ( *(uint32_t *)(dword_8F7A24 + 244) == 1 )  // 登录/选区管理器
      {
        if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        {
          v5 = sub_431860((char)"Common/ActiveStatus/Animation/Bleeding.ani", 1);  // 动画件构造（资源 id 版）
          goto LABEL_62;
        }
      }
      else if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
      {
        v5 = sub_431860((char)"Common/ActiveStatus/Animation/Bleeding12Age.ani", 1);  // 动画件构造（资源 id 版）
        goto LABEL_62;
      }
LABEL_61:  // 标签 LABEL_61（跳转合流点）
      v5 = 0;
LABEL_62:  // 标签 LABEL_62（跳转合流点）
      *(this + 5) = v5;  // this+20〔nPage(推断)〕
      return;
    case 0xCu:
      if ( sub_42FCB0(228) == 0 )  // CRT 一次性初始化
        goto LABEL_61;
      v5 = sub_431860((char)"Common/ActiveStatus/Animation/Haste.ani", 1);  // 动画件构造（资源 id 版）
      goto LABEL_62;
    case 0xDu:
      pMem3 = operator new(0x12Cu);  // new(300 字节) 分配对象
      if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
        fld_e13 = sub_428F30(pMem3, (int)"Common/ActiveStatus/Particle/BlessParticle1.ptl", *(this + 1));  // CNRDObjectParticleCreater 构造
      else  // 否则分支
        fld_e13 = nullptr;  // fld_e13 = 空指针
      fld_e14 = *(this + 1);  // this+4〔宿主对象〕
      *(this + 10) = (int)fld_e13;  // this+40〔bStateSub40(推断)〕
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e13 + 112))(fld_e13, fld_e14);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      pMem4 = operator new(0x12Cu);  // new(300 字节) 分配对象
      if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
        fld_e15 = sub_428F30(pMem4, (int)"Common/ActiveStatus/Particle/BlessParticle2.ptl", *(this + 1));  // CNRDObjectParticleCreater 构造
      else  // 否则分支
        fld_e15 = nullptr;  // fld_e15 = 空指针
      fld_e16 = *(this + 1);  // this+4〔宿主对象〕
      *(this + 11) = (int)fld_e15;  // this+44〔nExpireMs(推断)〕
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*fld_e15 + 112))(fld_e15, fld_e16);  // 调虚槽 +112：CNRDStackable__vmt70 槽位（699000 时钟 + 4B44E0）
      return;
    case 0xFu:
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v4 = sub_431860((char)"Common/ActiveStatus/Animation/Confuse.ani", 1);  // 动画件构造（资源 id 版）
      else  // 否则分支
        v4 = 0;
      *(this + 5) = v4;  // this+20〔nPage(推断)〕
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        *(this + 6) = sub_431860((char)"Common/ActiveStatus/Animation/ConfuseGlow.ani", 1);  // 动画件构造（资源 id 版）
      else  // 否则分支
LABEL_44:  // 标签 LABEL_44（跳转合流点）
        *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
      return;
    case 0x10u:
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v6 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);  // 动画件构造（资源 id 版）
      else  // 否则分支
        v6 = 0;
      *(this + 5) = v6;  // this+20〔nPage(推断)〕
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v7 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);  // 动画件构造（资源 id 版）
      else  // 否则分支
        v7 = 0;
      *(this + 6) = v7;  // this+24〔nPageMax(推断)〕
      if ( sub_42FCB0(228) != 0 )  // CRT 一次性初始化
        v8 = sub_431860((char)"Common/ActiveStatus/Animation/Hold.ani", 1);  // 动画件构造（资源 id 版）
      else  // 否则分支
        v8 = 0;
      fld_e5 = *(this + 5);  // this+20〔nPage(推断)〕
      *(this + 7) = v8;  // this+28〔pPanelVec(推断)〕
      v10 = sub_42FC90(fld_e5);  // 88B 元素计数（+44 组）
      nRand = rand();  // nRand = 调 rand
      sub_493400(*(this + 5), nRand % v10);  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
      fld_e6 = sub_42FC90(*(this + 6));  // 88B 元素计数（+44 组）
      nRand2 = rand();  // nRand2 = 调 rand
      sub_493400(*(this + 6), nRand2 % fld_e6);  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
      fld_e7 = sub_42FC90(*(this + 7));  // 88B 元素计数（+44 组）
      nRand3 = rand();  // nRand3 = 调 rand
      sub_493400(*(this + 7), nRand3 % fld_e7);  // 应用帧索引 a2（帧起点重算 + sub_430B70 复位盒）
      return;
    default:  // 默认分支
      return;
  }
}


// ------------------------------------------------------------
// 0x497E40 sub_497E40 —— 双虚转发 vt+96 与 vt+4
//   先把 nArg4 交 vt+96 槽，再把 (nArg2, nArg3) 转发 vt+4 槽并返回其结果；属 §K 状态应用族的薄壳入口。
// ------------------------------------------------------------
int /*thiscall*/ sub_497E40(void *this, int nArg2, int nArg3, int nArg4)  // 实现：双虚转发 vt+96 与 vt+4
{
  (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 96))(this, nArg4);  // 调虚槽 +96：CNRDPrivateStoreWindow__vmt60 槽（4BE520 + 44E8D…
  return (*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 4))(this, nArg2, nArg3);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
}



// ------------------------------------------------------------
// 0x497E70 sub_497E70 —— uint32 区间逐元素拷贝
//   把 [uArg1, uArg2) 的 uint32 逐个写入 uArg3 起的目标（目标非空才写），返回写完位置；std::copy 展开。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_497E70(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：uint32 区间逐元素拷贝
{
  uint32_t *uArg12; // ecx
  uint32_t *result; // eax

  uArg12 = uArg1;
  for ( result = uArg3; uArg12 != uArg2; ++result )  // 遍历循环
  {
    if ( result != nullptr )  // 若 result 有效（非空）
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
void /*usercall*/ sub_497EA0(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)  // 实现：帧事件回调分发（+48/+52/+40 帧、sub_460230/sub_529A80；调试 off_77F3FC）
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

  pObj3 = pArg1[59];  // pObj3 = 取 pArg1[59]
  if ( pObj3 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)pObj3 + 308))() != 0 && pArg1[61] == 33 )  // 调虚槽 +308：是否本地玩家
  {
    v4 = pArg1[63];  // v4 = 取 pArg1[63]
    if ( v4 != 0 && (v31 = (pArg1[64] - v4) >> 5, v5 = v31, v31 != 0) )  // 若 v4 != 0
    {
      sub_490D70(pArg1, (int)v27);  // 按时间步(1000ms)批量生成对象
      v33 = 0;
      if ( Block != nullptr )  // 若 Block 有效（非空）
        v32 = (v29 - (int)Block) >> 2;
      else  // 否则分支
        v32 = 0;
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 21, 2, nArg2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
      v6 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v7 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[59] + 48))(pArg1[59]);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
      (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, v7);  // 会话/UDP 管理器
      v8 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
      v9 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[59] + 52))(pArg1[59]);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行…
      (*(void (/*thiscall*/ **)(int, int))(v8 + 36))(dword_8F8520, v9);  // 会话/UDP 管理器
      pObj = pArg1[67];  // pObj = 取 pArg1[67]
      if ( pObj != 0 )  // 若 pObj 非 0
        v11 = (*(int (**)(void))(*(uint32_t *)pObj + 48))();  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      else  // 否则分支
        v11 = 0xFFFF;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v11);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      pObj2 = pArg1[67];  // pObj2 = 取 pArg1[67]
      if ( pObj2 != 0 )  // 若 pObj2 非 0
        v13 = (*(int (**)(void))(*(uint32_t *)pObj2 + 52))();  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      else  // 否则分支
        v13 = 0xFFFF;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v13);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, v32);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      v14 = 0;
      if ( v32 > 0 )  // 若 v32 > 0
      {
        while ( 1 )  // 条件循环
        {
          if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 36))(pArg1) + 68) != 0 )  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
          {
            nRand = rand() % v5;  // nRand = 调 rand
          }
          else  // 否则分支
          {
            nRand = v14;
            if ( v14 >= v5 )  // 若 v14 >= v5
              nRand = v5;
          }
          v25 = *(uint16_t *)(pArg1[63] + 32 * nRand + 28);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 0);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
          v16 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
          v17 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 1220))(dword_8F7C04);  // 调虚槽 +1220：IRDCharacter__vmt4C4 默认虚槽桩（10 行 return）
          (*(void (/*thiscall*/ **)(int, int))(v16 + 36))(dword_8F8520, v17);  // 会话/UDP 管理器
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
          v19 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
          v20 = sub_460230(*(uint32_t *)(v18 + 104));  // 图标槽随机 id 分配（线性探测）
          (*(void (/*thiscall*/ **)(int, int))(v19 + 36))(dword_8F8520, v20);  // 会话/UDP 管理器
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 32))(dword_8F8520, 1);  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
          (*(void (/*thiscall*/ **)(uint32_t, void *, int *))(**((uint32_t **)Block + v14) + 16))(  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44ABE…
            *((uint32_t *)Block + v14),
            &unk_9A0188,
            &v30);
          v26 = sub_529A80(v25, v26);  // v26 = 调 sub_529A80 返回值
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
          (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &unk_9A0188, v30);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
          v21 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
          v22 = (*(int (/*thiscall*/ **)(uint32_t))(**((uint32_t **)Block + v14) + 44))(*((uint32_t *)Block + v14));  // 调虚槽 +44：IRDPopupWindow__vmt2C 定位槽（43C330/69C4C0/69C420 +…
          (*(void (/*thiscall*/ **)(int, int))(v21 + 40))(dword_8F8520, v22);  // 会话/UDP 管理器
          (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)dword_8F8520 + 52))(dword_8F8520, 0, 0);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
          v23 = *((void (/*thiscall*/ ****)(uint32_t, int))Block + v14);
          if ( v23 != nullptr )  // 若 v23 有效（非空）
            (**v23)(v23, 1);  // 调 v23 的虚函数（vt+0）
          if ( ++v14 >= v32 )
            break;  // 跳出循环/分支
          v5 = v31;
        }
      }
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      if ( Block != nullptr )  // 若 Block 有效（非空）
        j__free(Block);  // 调 j__free（堆释放）
    }
    else  // 否则分支
    {
      off_77F3FC((char *)&byte_6CB800);  // 引擎日志输出函数(printf 风格)
    }
  }
}


// ------------------------------------------------------------
// 0x498150 sub_498150 —— 32 字节元素区间拷贝（std::string + 尾槽）
//   逐元素（步长 32 字节）用 ·sub_4014D0 深拷贝 std::string 并搬运 +28 尾槽，返回目标区间尾指针。
//   【推断】元素 = 28 字节 std::string + 1 个 4 字节附加值，与 ·sub_4981F0/·sub_498370 同族。
// ------------------------------------------------------------
size_t */*cdecl*/ sub_498150(size_t *pArg1, size_t *pArg2, size_t *pArg3)  // 实现：32 字节元素区间拷贝（std::string + 尾槽）
{
  size_t *pArg12; // esi
  size_t *pArg32; // edi

  pArg12 = pArg1;
  if ( pArg1 == pArg2 )  // 若 pArg1 == pArg2
    return pArg3;
  pArg32 = pArg3;
  do  // do-while 循环体起点
  {
    sub_4014D0(pArg32, pArg12, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
    pArg32[7] = pArg12[7];  // pArg32[7] = 取 pArg12[7]
    pArg12 += 8;
    pArg32 += 8;
  }
  while ( pArg12 != pArg2 );  // 条件循环
  return pArg32;
}



// ------------------------------------------------------------
// 0x498190 sub_498190 —— 对象默认字段装配（+236..+272）
//   把 +236=0、+240=4、+244=2、+264=1、+268=0 五槽置默认，
//   尾随 std::string（+272）经 ·sub_4015C0 赋 szPassword。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_498190(size_t *this)  // 实现：对象默认字段装配（+236..+272）
{
  *(this + 59) = 0;  // this+236〔nSyncArgA〕
  *(this + 60) = 4;  // this+240〔nSyncArgB〕
  *(this + 61) = 2;  // this+244〔fSyncTime〕
  *(this + 66) = 1;  // this+264〔nAnimHandle(推断)〕
  *(this + 67) = 0;  // this+67 周期 ms
  return sub_4015C0(this + 68, szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x4981D0 sub_4981D0 —— 转发 sub_498150
//   一层薄转发到 ·sub_498150（32 字节元素区间拷贝）。
// ------------------------------------------------------------
size_t */*cdecl*/ sub_4981D0(size_t *pArg1, size_t *pArg2, size_t *pArg3)  // 实现：转发 sub_498150
{
  return sub_498150(pArg1, pArg2, pArg3);  // 32 字节元素区间拷贝（std::string + 尾槽）
}



// ------------------------------------------------------------
// 0x4981F0 sub_4981F0 —— 32 字节元素区间构造拷贝（先置空串）
//   对每份源元素先在目标处建空 std::string（+20=0、+24=15 容量），再用 ·sub_4014D0 深拷贝并搬 +28 尾槽，返回目标尾指针；
//   与 ·sub_498150 的覆盖式拷贝互补，同供 ·sub_498370 的 vector 赋值使用。
// ------------------------------------------------------------
int /*cdecl*/ sub_4981F0(size_t *pArg1, size_t *pArg2, int nArg3)  // 实现：32 字节元素区间构造拷贝（先置空串）
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != pArg2 )  // 条件循环
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )  // 若 nArg32 非 0
    {
      *(uint32_t *)(nArg32 + 24) = 15;  // nArg32+24〔nPageMax(推断)〕
      *(uint32_t *)(nArg32 + 20) = 0;  // nArg32+20〔nPage(推断)〕
      *(uint8_t *)(nArg32 + 4) = 0;  // nArg32+4〔宿主对象〕
      sub_4014D0((size_t *)nArg32, pArg1, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
      *(uint32_t *)(nArg32 + 28) = pArg1[7];  // nArg32+28〔pPanelVec(推断)〕
    }
    nArg32 += 32;
    LOBYTE(v7) = 0;
    pArg1 += 8;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x4982B0 sub_4982B0 —— uint32 元素 vector 拷贝赋值（复用首指针）
//   先用 ·sub_42CFD0 校验源元素数，再把 pArg2 的 [begin, end) 经 ·sub_497E70 逐 uint32 拷到 *(this+4) 起，
//   尾指针回写 +8。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4982B0(uint32_t *this, int pArg2)  // 实现：uint32 元素 vector 拷贝赋值（复用首指针）
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

  v3 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  v11 = &v9;
  pThis = this;
  if ( v3 != 0 )  // 若 v3 非 0
    v4 = (*(uint32_t *)(pArg2 + 8) - v3) >> 2;  // pArg2+8〔nSkillRec8(推断)〕
  else  // 否则分支
    v4 = 0;
  if ( (uint8_t)sub_42CFD0(v4) != 0 )  // vector 预留（4B 元素）
  {
    fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    v7 = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
    v6 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    v12 = 0;
    *(this + 2) = sub_497E70(v6, v7, fld_e1);  // uint32 区间逐元素拷贝
  }
  return this;
}



// ------------------------------------------------------------
// 0x498350 sub_498350 —— 转发 sub_4981F0
//   一层薄转发到 ·sub_4981F0（32 字节元素构造拷贝）。
// ------------------------------------------------------------
int /*stdcall*/ sub_498350(size_t *pArg1, size_t *pArg2, int nArg3)  // 实现：转发 sub_4981F0
{
  return sub_4981F0(pArg1, pArg2, nArg3);  // 32 字节元素区间构造拷贝（先置空串）
}



// ------------------------------------------------------------
// 0x498370 sub_498370 —— 32 字节元素 vector 赋值（容量足/不足双路径）
//   自赋值短路；源为空则经 ·sub_428480 清空本对象；源元素数超过现有容量时先以 ·sub_493260 析构旧区间、free 后重分配，再经 ·sub_498350 全量构造拷贝（分配校验 ·sub_4281D0）；
//   否则先用 ·sub_4981D0 覆盖公共段，再用 ·sub_4981F0 在后段构造剩余元素并回写尾指针 +8。
// ------------------------------------------------------------
int /*thiscall*/ sub_498370(int this, int pArg2)  // 实现：32 字节元素 vector 赋值（容量足/不足双路径）
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

  if ( this == pArg2 )  // 若 this == pArg2
    return this;
  v3 = *(size_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(pArg2 + 8) - (int)v3) >> 5) == 0 )  // 若 v3 == nullptr
  {
    sub_428480(this);  // 32B 元素容器清空
    return this;
  }
  fld_4 = *(size_t **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_8 = 0;  // fld_8=this+8 nSkillRec8
  if ( v4 <= fld_8 )  // 若 v4 <= fld_8
  {
    v8 = (char *)sub_498150(v3, *(size_t **)(pArg2 + 8), fld_4);  // 32 字节元素区间拷贝（std::string + 尾槽）
    sub_493260(v8, *(char **)(this + 8));  // 32 字节元素数组析构遍历（区间 [pszArg1,pszArg2)，步长 32）
    v9 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v9 != 0 )  // 若 v9 非 0
      fld_42 = *(uint32_t *)(this + 4) + 32 * ((*(uint32_t *)(pArg2 + 8) - v9) >> 5);  // fld_42 = 读 this+4
    else  // 否则分支
      fld_42 = *(uint32_t *)(this + 4);  // fld_42 = 读 this+4
    *(uint32_t *)(this + 8) = fld_42;  // this+8〔nSkillRec8(推断)〕等 2 字段
    return this;
  }
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) >> 5;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    fld_C = 0;  // fld_C=this+12 nSkillRec12
  if ( v4 > fld_C )  // 若 v4 > fld_C
  {
    if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    {
      sub_493260((char *)fld_4, *(char **)(this + 8));  // 32 字节元素数组析构遍历（区间 [pszArg1,pszArg2)，步长 32）
      j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
    }
    v14 = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( v14 != 0 )  // 若 v14 非 0
      v15 = (*(uint32_t *)(pArg2 + 8) - v14) >> 5;  // pArg2+8〔nSkillRec8(推断)〕
    else  // 否则分支
      v15 = 0;
    if ( (uint8_t)sub_4281D0(v15) != 0 )  // STL 内联 vector 扩容分配（32B 元素）
      *(uint32_t *)(this + 8) = sub_498350(*(size_t **)(pArg2 + 4), *(size_t **)(pArg2 + 8), *(uint32_t *)(this + 4));  // 转发 sub_4981F0
    return this;
  }
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 5;  // this+8〔nSkillRec8(推断)〕等 2 字段
  else  // 否则分支
    fld_82 = 0;  // fld_82=this+8 nSkillRec8
  v13 = (size_t *)(*(uint32_t *)(pArg2 + 4) + 32 * fld_82);  // pArg2+4〔宿主对象〕
  sub_4981D0(*(size_t **)(pArg2 + 4), v13, *(size_t **)(this + 4));  // 转发 sub_498150
  *(uint32_t *)(this + 8) = sub_4981F0(v13, *(size_t **)(pArg2 + 8), *(uint32_t *)(this + 8));  // 32 字节元素区间构造拷贝（先置空串）
  return this;
}



// ------------------------------------------------------------
// 0x4984D0 sub_4984D0 —— 状态对象字段级拷贝（源 +172/+180/+176 + 尾串）
//   先经 ·sub_490340 做基类双层转发拷贝（本对象 vt+24，内嵌 +100 子对象），
//   再把源的 +172 槽、+180 起 32 字节元素链（·sub_498370）与 +176 槽、+196 起字符串（·sub_4014D0）
//   分别拷入本对象 +244、+248、+264、+272。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4984D0(size_t *this, uint32_t *pArg2)  // 实现：状态对象字段级拷贝（源 +172/+180/+176 + 尾串）
{
  sub_490340(this, (int)pArg2);  // 双层转发（本对象 vt+24，内嵌 +100 子对象 vt+32）
  *(this + 61) = pArg2[43];  // this+244〔fSyncTime〕
  sub_498370((int)(this + 62), (int)(pArg2 + 45));  // 32 字节元素 vector 赋值（容量足/不足双路径）
  *(this + 66) = pArg2[44];  // this+264〔nAnimHandle(推断)〕
  return sub_4014D0(this + 68, pArg2 + 49, 0, 0xFFFFFFFF);  // std::string::assign(str, pos, n) 模板实例（含自赋值旋转路径）
}



// ------------------------------------------------------------
// 0x498530 sub_498530 —— 动画对象构造（vftable 装配 + 复位 + 首帧占位）
//   装 off_6C2B88 虚表并清各槽，初始化 +60 处时钟/计数段（·sub_430B70）；
//   把 +200 处子对象经 ·sub_4A2CF0 注册为 +204，再依次 ·sub_493BD0 动画对象复位与 ·sub_494630 单帧占位初始化（帧 +0 句柄槽、+12/+16 位置）。
// ------------------------------------------------------------
char */*thiscall*/ sub_498530(char *this, int nArg2)  // 实现：动画对象构造（vftable 装配 + 复位 + 首帧占位）
{
  uint32_t *pThis_3C; // ecx

  *(this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  *(uint32_t *)this = &off_6C2B88;
  *((uint32_t *)this + 2) = 0;  // this[2] = 0
  *(this + 12) = 1;  // this+48〔pCmdVecBegin48(推断)〕
  *(this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *((uint32_t *)this + 6) = 0;  // this[6] = 0
  *((uint32_t *)this + 5) = 0;  // this[5] = 0
  *((uint32_t *)this + 4) = 0;  // this[4] = 0
  *((uint32_t *)this + 11) = 0;  // this[11] = 0
  *((uint32_t *)this + 12) = 0;  // this[12] = 0
  *((uint32_t *)this + 13) = 0;  // this[13] = 0
  pThis_3C = this + 60;
  pThis_3C[15] = 0;  // pThis_3C=this+60 fade 值
  pThis_3C[16] = 0;  // pThis_3C=this+60 fade 值
  pThis_3C[17] = 0;  // pThis_3C=this+60 fade 值
  pThis_3C[19] = 0;  // pThis_3C=this+60 fade 值
  pThis_3C[20] = 0;  // pThis_3C=this+60 fade 值
  pThis_3C[21] = 0;  // pThis_3C=this+60 fade 值
  sub_430B70(pThis_3C);  // 88B 帧条目复位
  *((uint32_t *)this + 51) = sub_4A2CF0(this + 200);  // this[51] = 调 sub_4A2CF0 返回值
  *((uint32_t *)this + 52) = 0;  // this[52] = 0
  sub_493BD0((int)this);  // 动画对象复位
  sub_494630((int)this, nArg2);  // 单帧占位初始化：帧+0 句柄槽；帧+12/+16 = 尺寸(a2+20/+24)/2 取负 → 居中锚点
  return this;
}



// ------------------------------------------------------------
// 0x4985E0 sub_4985E0 —— 状态加载大函数（+216 同步、+59/+236/+217、sub_490D70 批量生成、sub_498530 单帧、+46 事件）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4985E0(uint32_t *this, uint32_t *uArg2)  // 实现：状态加载大函数（+216 同步、+59/+236/+217、sub_490D70 批量生成、sub_498530 单帧、+46 事件）
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
  v31 = nullptr;  // v31 = 空指针
  v32 = 0;
  v33 = 0;
  pThis_D8 = *((uint8_t *)this + 216);  // this+216〔bField216(推断)〕
  v43 = 0;
  if ( pThis_D8 != 0 )  // 若 pThis_D8 非 0
  {
    uArg22 = uArg2;
    sub_4982B0(uArg2, (int)v30);  // uint32 元素 vector 拷贝赋值（复用首指针）
    return uArg22;
  }
  fld_e59 = *(this + 59);  // this+236〔nSyncArgA〕
  if ( fld_e59 != 0 )  // 若 fld_e59 非 0
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e59 + 236))(fld_e59);  // 调虚槽 +236
    pThis_D9 = *((uint8_t *)this + 217);
    LOBYTE(v40) = v7 == 2;
    if ( (v7 == 2) != pThis_D9 )
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 72))(this, v40);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
  }
  fld_e60 = *(this + 60);  // this+240〔nSyncArgB〕
  if ( fld_e60 != 0 )  // 若 fld_e60 非 0
  {
    if ( fld_e60 == 1 )  // 若 fld_e60 == 1
    {
      *((uint8_t *)this + 88) = 0;  // this[88] = 0
    }
    else  // 否则分支
    {
      fld_e592 = *(this + 59);  // this+236〔nSyncArgA〕
      if ( fld_e592 != 0 )  // 若 fld_e592 非 0
        *((uint8_t *)this + 88) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e592 + 152))(fld_e592) == 0;  // 调虚槽 +152：效果通道 3
    }
  }
  else  // 否则分支
  {
    *((uint8_t *)this + 88) = 1;  // this[88] = 1
  }
  if ( *(this + 59) != 0 && *(this + 61) == 33 )  // this+236〔nSyncArgA〕
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);  // 调虚槽 +120：动画对象
    uArg22 = uArg2;
    sub_4982B0(uArg2, (int)v30);  // uint32 元素 vector 拷贝赋值（复用首指针）
    return uArg22;
  }
  fld_e63 = *(this + 63);  // this+252〔nQuad2〕
  if ( fld_e63 == 0 || (fld_e64 = (*(this + 64) - fld_e63) >> 5, fld_e642 = fld_e64, fld_e64 == 0) )  // this+256〔bQuad3〕
  {
    off_77F3FC(aFail_1);  // 引擎日志输出函数(printf 风格)
    uArg22 = uArg2;
    sub_4982B0(uArg2, (int)v30);  // uint32 元素 vector 拷贝赋值（复用首指针）
    return uArg22;
  }
  sub_490D70(this, (int)v34);  // 按时间步(1000ms)批量生成对象
  LOBYTE(v43) = 1;
  if ( Block != nullptr )  // 若 Block 有效（非空）
    v40 = (v36 - (int)Block) >> 2;
  else  // 否则分支
    v40 = 0;
  v42 = 0;
  if ( v40 > 0 )  // 若 v40 > 0
  {
    while ( 1 )  // 条件循环
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 36))(this) + 68) != 0 )  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
      {
        nRand = (uint32_t *)(*(this + 63) + 32 * (rand() % fld_e642));  // this+252〔nQuad2〕
      }
      else  // 否则分支
      {
        if ( v2 < fld_e642 )  // 若 v2 < fld_e642
          fld_e642 = v2;
        nRand = (uint32_t *)(*(this + 63) + 32 * fld_e642);  // this+252〔nQuad2〕
      }
      if ( *(this + 61) == 2 )  // this+244〔fSyncTime〕
        break;  // 跳出循环/分支
      if ( *(this + 61) != 33 )  // this+244〔fSyncTime〕
        goto LABEL_54;
      pObj2 = (char *)sub_53A220(nRand[7], nullptr);  // 【巨函数（size=17574）→ src/combat/bigfunc_53A220…】
      pObj22 = pObj2;
LABEL_53:  // 标签 LABEL_53（跳转合流点）
      if ( pObj2 != nullptr )  // 若 pObj2 有效（非空）
      {
        fld_e46 = *(this + 46);  // this+184〔bSingleTarget(推断)〕
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 72))(pObj2);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
        (*(void (/*thiscall*/ **)(char *, uint32_t))(*(uint32_t *)pObj2 + 60))(pObj2, *((uint32_t *)Block + v2));  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        sub_4A0B60(fld_e46);  // 调 控制对象换绑
        fld_e67 = *(this + 67);  // this+67 周期 ms
        (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)pObj2 + 60))(pObj2);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        sub_4A06D0(fld_e67);  // 调 绑定目标对象并记录相对偏移
        pObj = *((uint32_t *)Block + v2);
        v24 = *(uint32_t *)pObj2;
        v25 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 16))(pObj);  // 调虚槽 +16：CNRDSkillBuyWindow__vmt10 状态切换槽：对象状态 17→18（44A…
        (*(void (/*thiscall*/ **)(char *, bool))(v24 + 148))(pObj2, *(uint8_t *)(v25 + 84) == 0);  // 调虚槽 +148：CNProvocationDollAura__vmt94 槽（12 行）
        *((uint32_t *)Block + v42) = 0;
        sub_45FC10(&pObj22);  // 单对象插入包装（转 ·sub_45F8A0 后回传槽址）
        v2 = v42;
        goto LABEL_58;
      }
LABEL_54:  // 标签 LABEL_54（跳转合流点）
      Block2 = Block;
      v22 = *((void (/*thiscall*/ ****)(uint32_t, int))Block + v2);
      if ( v22 != nullptr )  // 若 v22 有效（非空）
      {
        (**v22)(v22, 1);  // 调 v22 的虚函数（vt+0）
        Block2 = Block;
      }
      Block2[v2] = 0;
LABEL_58:  // 标签 LABEL_58（跳转合流点）
      v42 = ++v2;
      if ( v2 >= v40 )  // 若 v2 >= v40
        goto LABEL_59;
      fld_e642 = fld_e64;
    }
    if ( nRand[7] == -1 )  // nRand=this+252 nQuad2
    {
      v15 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      pObj22 = v15;
      LOBYTE(v43) = 2;
      if ( v15 != nullptr )  // 若 v15 有效（非空）
      {
        v38 = sub_42FCB0(228);  // CRT 一次性初始化
        LOBYTE(v43) = 3;
        if ( v38 != 0 )  // 若 v38 非 0
        {
          if ( nRand[6] < 0x10u )  // nRand=this+252 nQuad2
            LOBYTE(nRand) = (uint8_t)nRand + 4;  // nRand=this+252 nQuad2
          else  // 否则分支
            nRand = (uint32_t *)nRand[1];  // nRand=this+252 nQuad2
          if ( *(this + 74) < 0x10u )  // this+296〔bInitFlag296(推断)〕
            pThis_14 = (char *)sub_431920((uint8_t)this + 20, (char)nRand, 1);  // 动画件构造（文件名版）
          else  // 否则分支
            pThis_14 = (char *)sub_431920(*(this + 69), (char)nRand, 1);  // 动画件构造（文件名版）
        }
        else  // 否则分支
        {
          pThis_14 = nullptr;  // pThis_14 = 空指针
        }
        LOBYTE(v43) = 2;
        goto LABEL_43;
      }
    }
    else  // 否则分支
    {
      v15 = (char *)sub_44B6C0(284);  // CRT 一次性池初始化 2（池 &unk_98B6F8）
      v38 = (int)v15;
      LOBYTE(v43) = 4;
      if ( v15 != nullptr )  // 若 v15 有效（非空）
      {
        pObj22 = (char *)sub_42FCB0(228);  // CRT 一次性初始化
        LOBYTE(v43) = 5;
        if ( pObj22 != nullptr )  // 若 pObj22 有效（非空）
        {
          if ( nRand[6] < 0x10u )  // nRand=this+252 nQuad2
            v17 = nRand + 1;
          else  // 否则分支
            v17 = (uint32_t *)nRand[1];  // nRand=this+252 nQuad2
          v27 = nRand[7];  // v27 = 取 nRand[7]
          (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v17);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
          v18 = sub_418DD0(v27);  // v18 = 调 sub_418DD0 返回值
          pThis_14 = sub_498530(pObj22, v18);  // 动画对象构造（vftable 装配 + 复位 + 首帧占位）
          LOBYTE(v43) = 4;
        }
        else  // 否则分支
        {
          pThis_14 = nullptr;  // pThis_14 = 空指针
          LOBYTE(v43) = 4;
        }
LABEL_43:  // 标签 LABEL_43（跳转合流点）
        sub_44E0D0(v15, (int)pThis_14, 0);  // CNRDObject 构造（KMessenger 虚表起步，自证 vftable）
        *(uint32_t *)v15 = &CNRDPooledObject::`vftable';  // 构造装配 vftable：CNRDPooledObject
LABEL_52:  // 标签 LABEL_52（跳转合流点）
        pObj2 = v15;
        v19 = *(uint32_t *)v15;
        LOBYTE(v43) = 1;
        pObj22 = v15;
        v20 = (*(int (/*thiscall*/ **)(char *))(v19 + 36))(v15);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/60584…
        v2 = v42;
        *(uint32_t *)(v20 + 8) = *(this + 66);  // this+264〔nAnimHandle(推断)〕
        goto LABEL_53;
      }
    }
    v15 = nullptr;  // v15 = 空指针
    goto LABEL_52;
  }
LABEL_59:  // 标签 LABEL_59（跳转合流点）
  uArg22 = uArg2;
  sub_4982B0(uArg2, (int)v30);  // uint32 元素 vector 拷贝赋值（复用首指针）
  if ( Block != nullptr )  // 若 Block 有效（非空）
    j__free(Block);  // 调 j__free（堆释放）
  Block = nullptr;  // Block = 空指针
  v36 = 0;
  v37 = 0;
  if ( v31 != nullptr )  // 若 v31 有效（非空）
    j__free(v31);  // 调 j__free（堆释放）
  return uArg22;
}


// ------------------------------------------------------------
// 0x4989B0 sub_4989B0 —— 链头注册（全局链 dword_9A02B4）
//   把 this 经 ·sub_407EA0 插入全局链 dword_9A02B4，返回节点结果指针。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4989B0(void *this)  // 实现：链头注册（全局链 dword_9A02B4）
{
  void *pThis; // [esp+0h] [ebp-4h] BYREF

  pThis = this;
  return sub_407EA0(&dword_9A02B4, &pThis);  // 链表按值摘除（遍历哨兵环，节点 +8 == *uArg2 时摘除 free 且计数递减）
}



// ------------------------------------------------------------
// 0x4989D0 sub_4989D0 —— 容器双清 + 缓冲释放
//   连续两次 ·sub_6569D0 做容器清理，再 free *(this+4) 缓冲并置空。
// ------------------------------------------------------------
void /*thiscall*/ sub_4989D0(void **this)  // 实现：容器双清 + 缓冲释放
{
  sub_6569D0(this);  // 调 清 +28
  sub_6569D0(this);  // 调 清 +28
  j__free(*(this + 1));  // this+4〔宿主对象〕
  *(this + 1) = nullptr;  // this+4〔宿主对象〕
}



// ------------------------------------------------------------
// 0x498A00 sub_498A00 —— 容器重置（首指针重建 + 计数清零）
//   用 ·sub_425940 重建首指针写 +4、清 +8 计数，再经 ·sub_6569D0 整体清零；与 ·sub_4989D0 配对构成构造/析构两半。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_498A00(uint32_t *this)  // 实现：容器重置（首指针重建 + 计数清零）
{
  *(this + 1) = sub_425940(this);  // 链表哨兵节点
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  sub_6569D0(this);  // 调 清 +28
  return this;
}



// ------------------------------------------------------------
// 0x498A20 sub_498A20 —— 元素计数增长 + 溢出抛 length_error
//   把 +8 计数累加 uArg2，超过 0x3FFFFFFF 上限时构造 list<T> too long 的 std::length_error 抛出
//   （·sub_4015C0 造串 + ·sub_401740 包装 + _CxxThrowException）。
// ------------------------------------------------------------
int /*thiscall*/ sub_498A20(uint32_t *this, unsigned int uArg2)  // 实现：元素计数增长 + 溢出抛 length_error
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )  // fld_e2=this+8 nSkillRec8
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x498AB0 sub_498AB0 —— 全局链节点追加（自增 id + 双向回接）
//   取 dword_9A02A8 自增序号写 +4，经 ·sub_40C0F0 插到 dword_9A02B8 链头，
//   调 ·sub_498A20 令全局元素计数 +1，最后回填前驱/后继使双向链成环。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_498AB0(uint32_t *this)  // 实现：全局链节点追加（自增 id + 双向回接）
{
  int v1; // edx
  int v2; // esi
  int v3; // edx
  uint32_t *v4; // edi
  uint32_t *result; // eax
  uint32_t *pThis; // [esp+8h] [ebp-4h] BYREF

  v1 = dword_9A02A8++;
  *(this + 1) = v1;  // this+4〔宿主对象〕
  v2 = *(uint32_t *)dword_9A02B8;
  v3 = *(uint32_t *)(*(uint32_t *)dword_9A02B8 + 4);
  pThis = this;
  v4 = sub_40C0F0(v2, v3, &pThis);  // list 结点分配（12B：前驱/后继/数据）
  sub_498A20(&dword_9A02B4, 1u);  // 元素计数增长 + 溢出抛 length_error
  *(uint32_t *)(v2 + 4) = v4;
  result = (uint32_t *)v4[1];
  *result = v4;
  return result;
}



// ------------------------------------------------------------
// 0x498B00 sub_498B00 —— 浮点属性条件写入（置 +124 与 +196）
//   无条件先置 +124 位；对象句柄有效（vt+308）且槽 *(this+pArg2+1)（即 +4+4×pArg2）变化时写入 (double)nArg3 并置 +196 重算位。
//   与 ·sub_4955C0 的整型槽版互补。
// ------------------------------------------------------------
void /*thiscall*/ sub_498B00(float *this, int pArg2, int nArg3)  // 实现：浮点属性条件写入（置 +124 与 +196）
{
  int pObj; // ecx
  double v5; // st7

  pObj = *(uint32_t *)this;
  *((uint8_t *)this + 124) = 1;  // this[124] = 1
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    v5 = (double)nArg3;
    if ( *(this + pArg2 + 1) != v5 )
    {
      *(this + pArg2 + 1) = v5;
      *((uint8_t *)this + 196) = 1;  // this[196] = 1
    }
  }
}



// ------------------------------------------------------------
// 0x498B50 sub_498B50 —— 转发 sub_657740（带尺寸释放）
//   一层薄转发到 ·sub_657740(nArg1, nArg2)。
// ------------------------------------------------------------
int /*cdecl*/ sub_498B50(int nArg1, int nArg2)  // 实现：转发 sub_657740（带尺寸释放）
{
  return sub_657740(nArg1, nArg2);  // 池化结点弹出（写魔术标记后挂入链头）
}



// ------------------------------------------------------------
// 0x498B70 sub_498B70 —— 对象字段快照复位（+200..+276 全量默认值；+280 = timeGetTime() 时间戳）
// ------------------------------------------------------------
DWORD /*thiscall*/ sub_498B70(int this)  // 实现：对象字段快照复位（+200..+276 全量默认值；+280 = timeGetTime() 时间戳）
{
  DWORD result; // eax

  *(uint32_t *)(this + 92) = 1;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint32_t *)(this + 96) = 0;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 116) = 0;  // this+116〔会话上下文〕
  *(uint32_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint8_t *)(this + 156) = 1;  // this+156〔nAdd156(推断)〕
  *(uint8_t *)(this + 157) = 0;
  *(uint32_t *)(this + 160) = -1;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
  *(uint32_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint8_t *)(this + 172) = 1;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  *(uint32_t *)(this + 200) = 0;  // this+200〔nMainState(推断)〕
  *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 208) = 0;  // this+208〔nField208(推断)〕
  *(uint8_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 216) = -1;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 220) = -1;  // this+220〔nSnapDst220(推断)〕
  *(uint32_t *)(this + 224) = -1;  // this+224〔nSnapDst224(推断)〕
  *(uint32_t *)(this + 228) = -1;  // this+228〔nSnapDst228(推断)〕
  *(uint8_t *)(this + 232) = 0;  // this+232〔bSyncFlag〕
  *(uint32_t *)(this + 236) = 0;  // this+236〔nSyncArgA〕
  *(uint32_t *)(this + 240) = 0;  // this+240〔nSyncArgB〕
  *(uint32_t *)(this + 244) = 0;  // this+244〔fSyncTime〕
  *(uint8_t *)(this + 248) = 0;  // this+248〔bQuad1〕
  *(uint32_t *)(this + 252) = 0;  // this+252〔nQuad2〕
  *(uint8_t *)(this + 256) = 1;  // this+256〔bQuad3〕
  *(uint32_t *)(this + 260) = 2;  // this+260〔nQuad4〕
  *(uint32_t *)(this + 268) = 0;
  *(uint32_t *)(this + 272) = 0;
  *(uint8_t *)(this + 276) = 1;  // this+276〔pMapEntry〕
  *(uint8_t *)(this + 277) = 0;  // this+1108〔pAttach1108(推断)〕
  result = timeGetTime();  // result = 调 timeGetTime
  *(uint32_t *)(this + 280) = result;  // this+280〔pMapEntryVecEnd〕
  return result;
}



// ------------------------------------------------------------
// 0x498C40 sub_498C40 —— 五组虚槽批量重置
//   依次 vt+228（全清）、vt+252（4 次，逐槽 -1）、vt+260、vt+272、vt+284（0,0,1,2）重置附属槽，形如一套属性清空序列。
// ------------------------------------------------------------
int /*thiscall*/ sub_498C40(void *this)  // 实现：五组虚槽批量重置
{
  int i; // edi

  (*(void (/*thiscall*/ **)(void *, uint32_t, int, uint32_t))(*(uint32_t *)this + 228))(this, 0, -1, 0);  // 调虚槽 +228：主状态写入(0自由/1硬直/2冻结)
  for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
    (*(void (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 252))(this, i, -1);  // 调虚槽 +252
  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 260))(this, 0, 0, 0);  // 调虚槽 +260
  (*(void (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 272))(this, 0, 0);  // 调虚槽 +272
  return (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 284))(this, 0, 0, 1, 2);  // 调虚槽 +284：四字段批量写（+248..+260）
}



// ------------------------------------------------------------
// 0x498CA0 sub_498CA0 —— 组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）
//   先查 +200/+204/+208：启用且已过结束时刻时经 vt+232 终止；把 vt+120/124/128 取到的三分量回写 +176/+180/+184；
//   满足 vt+40(...,2) 时按 *(*(+28)+104) 与 +157 标志决定是否 vt+84(0)；随后 vt+332 主更新，+164/+168 两子模块经 ·sub_50EB10/·sub_50E9B0 刷新；
//   若 *(*(+28)+196) 置位则 ·sub_49FFC0 播放尾帧处理（+48/+52/+40），末按 vt+40(...,1) 决定是否 vt+564 收尾。
// ------------------------------------------------------------
int /*usercall*/ sub_498CA0@<eax>(float *pArg1@<ecx>, int nArg2@<edi>)  // 实现：组件逐帧驱动（坐标回写 + 尾帧处理 + 子模块更新）
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
    (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 232))(pArg1);  // 调虚槽 +232：CNRDObject__vmtE8
  }
  sub_4A0790(*((uint32_t *)pArg1 + 28));  // 调 条件分支里再读 this+116/this+28 决定二次写轴 —— 这是挂件跟随 + 延迟提交循环
  v7 = (float)(*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  v8 = (float)(*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 124))(pArg1);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v9 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 120))(pArg1);  // 调虚槽 +120：动画对象
  pArg1[45] = v8;
  pArg1[46] = v7;
  pArg1[44] = (float)v9;
  if ( (*(uint8_t (/*thiscall*/ **)(float *, int))(*(uint32_t *)pArg1 + 40))(pArg1, 2) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  {
    pObj = *(uint32_t *)(*((uint32_t *)pArg1 + 28) + 104);
    if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj) == 0 )  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 84))(pArg1, 0);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
    if ( *((uint8_t *)pArg1 + 157) != 0 )
    {
      v4 = *((uint32_t *)pArg1 + 30);
      if ( v4 != 0 && *(uint8_t *)(v4 + 170) != 0 )  // 若 v4 != 0
        (*(void (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)pArg1 + 84))(pArg1, 0);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
    }
  }
  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 332))(pArg1);  // 调虚槽 +332：IRDActiveObject__vmt14C 行走动画（505 行）：G_WALK_FLO…
  if ( *((uint32_t *)pArg1 + 41) != 0 )
    sub_50EB10();  // 气泡计时到期判定
  if ( *((uint32_t *)pArg1 + 42) != 0 )
    sub_50E9B0();  // 表情气泡次层提前销毁（主层 +170 标志触发）
  v5 = *((uint32_t *)pArg1 + 28);
  if ( *(uint8_t *)(v5 + 196) != 0 )
    sub_49FFC0((uint32_t *)v5, nArg2, (int)pArg1, 0, 0);  // 播放尾帧处理（+48/+52/+40 → sub_49FA20 收尾）
  result = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)pArg1 + 40))(pArg1, 1);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
  if ( (uint8_t)result != 0 )
    return (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 564))(pArg1);  // 调虚槽 +564
  return result;
}



// ------------------------------------------------------------
// 0x498DE0 sub_498DE0
// ------------------------------------------------------------
bool /*thiscall*/ sub_498DE0(uint32_t *this, int nArg2)  // 实现：★ 条件位掩码测试（研究第 20 轮直证: 273/529/17/65 均出自此）
{
  return (nArg2 & *(this + 24)) == nArg2;  // this+96〔nStatusMode(推断)〕
}



// ------------------------------------------------------------
// 0x498E00 sub_498E00 —— 坐标三分量设置（+4/+8/+12，带有效性与等值判定）
//   对 *(this+28) 子对象连做三次同构写值：分别把 nArg2/nArg3/nArg4 写入其 +4/+8/+12 浮点槽；
//   每段都先置 +124 位，仅在 vt+308 有效且值变化时落值并置 +196。
// ------------------------------------------------------------
void /*thiscall*/ sub_498E00(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：坐标三分量设置（+4/+8/+12，带有效性与等值判定）
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

  fld_e28 = (int *)*(this + 28);  // this+112〔pHostComp112〕
  pObj3 = *fld_e28;  // fld_e28=this+112 pHostComp112
  v7 = *fld_e28 == 0;  // fld_e28=this+112 pHostComp112
  *((uint8_t *)fld_e28 + 124) = 1;  // fld_e28=this+112 pHostComp112
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 308))(pObj3) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    v8 = (double)nArg2;
    if ( *((float *)fld_e28 + 1) != v8 )  // fld_e28=this+112 pHostComp112
    {
      *((float *)fld_e28 + 1) = v8;  // fld_e28=this+112 pHostComp112
      *((uint8_t *)fld_e28 + 196) = 1;  // fld_e28=this+112 pHostComp112
    }
  }
  fld_e282 = (int *)*(this + 28);  // this+112〔pHostComp112〕
  pObj2 = *fld_e282;  // fld_e282=this+112 pHostComp112
  v7 = *fld_e282 == 0;  // fld_e282=this+112 pHostComp112
  *((uint8_t *)fld_e282 + 124) = 1;  // fld_e282=this+112 pHostComp112
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 308))(pObj2) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    v11 = (double)nArg3;
    if ( *((float *)fld_e282 + 2) != v11 )  // fld_e282=this+112 pHostComp112
    {
      *((float *)fld_e282 + 2) = v11;  // fld_e282=this+112 pHostComp112
      *((uint8_t *)fld_e282 + 196) = 1;  // fld_e282=this+112 pHostComp112
    }
  }
  fld_e283 = (int *)*(this + 28);  // this+112〔pHostComp112〕
  pObj = *fld_e283;  // fld_e283=this+112 pHostComp112
  v7 = *fld_e283 == 0;  // fld_e283=this+112 pHostComp112
  *((uint8_t *)fld_e283 + 124) = 1;  // fld_e283=this+112 pHostComp112
  if ( !v7 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )  // 调虚槽 +308：是否本地玩家
  {
    v14 = (double)nArg4;
    if ( *((float *)fld_e283 + 3) != v14 )  // fld_e283=this+112 pHostComp112
    {
      *((float *)fld_e283 + 3) = v14;  // fld_e283=this+112 pHostComp112
      *((uint8_t *)fld_e283 + 196) = 1;  // fld_e283=this+112 pHostComp112
    }
  }
}



// ------------------------------------------------------------
// 0x498EC0 sub_498EC0 —— 坐标三分量直写（无有效性判定版）
//   与 ·sub_498E00 同构（差异：不做 vt+308 校验与等值跳过，无条件写 +4/+8/+12 并逐段置 +124）。
// ------------------------------------------------------------
int /*thiscall*/ sub_498EC0(uint32_t *this, int nArg2, int nArg3, int nArg4)  // 实现：坐标三分量直写（无有效性判定版）
{
  int fld_e28; // eax
  int result; // eax
  int fld_e282; // ecx

  fld_e28 = *(this + 28);  // this+112〔pHostComp112〕
  *(uint8_t *)(fld_e28 + 124) = 1;  // fld_e28=this+112 pHostComp112
  *(float *)(fld_e28 + 4) = (float)nArg2;  // fld_e28=this+112 pHostComp112
  result = *(this + 28);  // this+112〔pHostComp112〕
  *(uint8_t *)(result + 124) = 1;  // result=this+112 pHostComp112
  *(float *)(result + 8) = (float)nArg3;  // result=this+112 pHostComp112
  fld_e282 = *(this + 28);  // this+112〔pHostComp112〕
  *(uint8_t *)(fld_e282 + 124) = 1;  // fld_e282=this+112 pHostComp112
  *(float *)(fld_e282 + 12) = (float)nArg4;  // fld_e282=this+112 pHostComp112
  return result;  // result=this+112 pHostComp112
}



// ------------------------------------------------------------
// 0x498F00 sub_498F00
// ------------------------------------------------------------
int /*thiscall*/ sub_498F00(int *this, int nArg2)  // 实现：设置条件字节（经动画对象 +52，需通过 vt+308 玩家检查）
{
  int result; // eax
  uint8_t *fld_e28; // esi

  result = *(this + 50);  // this+200〔nMainState(推断)〕
  if ( result == 0 )  // 若 result 为 0
  {
    fld_e28 = (uint8_t *)*(this + 28);  // this+112〔pHostComp112〕
    if ( *(uint32_t *)fld_e28 != 0 )  // fld_e28=this+112 pHostComp112
    {
      result = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)fld_e28 + 308))(*(uint32_t *)fld_e28);  // 调虚槽 +308：是否本地玩家
      if ( (uint8_t)result != 0 )  // result=this+200 nMainState
      {
        result = nArg2;  // result=this+200 nMainState
        if ( (char)fld_e28[52] != nArg2 )  // fld_e28=this+112 pHostComp112
        {
          fld_e28[52] = nArg2;  // fld_e28=this+112 pHostComp112
          fld_e28[196] = 1;  // fld_e28=this+112 pHostComp112
        }
      }
    }
  }
  return result;  // result=this+200 nMainState
}



// ------------------------------------------------------------
// 0x498F40 sub_498F40
// ------------------------------------------------------------
int /*thiscall*/ sub_498F40(uint32_t *this, char pszArg2)  // 实现：同 vmt90 但不检查（直接写）
{
  int result; // eax

  result = *(this + 50);  // this+200〔nMainState(推断)〕
  if ( result == 0 )  // 若 result 为 0
  {
    result = *(this + 28);  // this+112〔pHostComp112〕
    *(uint8_t *)(result + 52) = pszArg2;  // result=this+112 pHostComp112
  }
  return result;  // result=this+112 pHostComp112
}



// ------------------------------------------------------------
// 0x498F70 sub_498F70
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_498F70(void *this)  // 是否本地玩家（研究第 10 轮直证: vt+304 == 0x8F7C04）
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 304))(this) != 0  // 调虚槽 +304：是否本地玩家
      && (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 304))(this) == dword_8F7C04;  // 调虚槽 +304：是否本地玩家
}



// ------------------------------------------------------------
// 0x498FA0 sub_498FA0 —— 时刻槽写入（-1 语义为推进并释放）
//   槽 *(this+pArg2+54)（即 +216+4×pArg2）为空(-1) 时直接落 nArg3；
//   已占用而新值 -1 时，把 *(this+30) 对象经 ·sub_4910E0 推进帧时刻后按累计 +32 同步（·sub_493A60），再置 -1。
// ------------------------------------------------------------
char /*thiscall*/ sub_498FA0(int *this, int pArg2, int nArg3)  // 实现：时刻槽写入（-1 语义为推进并释放）
{
  char result; // al
  int fld_e30; // edi  | +0x0078 → 基类动画对象指针（CNRDObject；va=00499020）

  if ( *(this + pArg2 + 54) == -1 )
  {
    *(this + pArg2 + 54) = nArg3;
  }
  else  // 否则分支
  {
    result = nArg3;
    if ( nArg3 == -1 )
    {
      fld_e30 = *(this + 30);  // this+120〔pAnimObj〕
      if ( fld_e30 != 0 )  // 若 fld_e30 非 0
      {
        sub_4910E0(*(this + 30));  // 帧时刻推进（返回 1 表示时刻发生位移）
        result = sub_493A60(fld_e30, *(uint32_t *)(fld_e30 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
        *(this + pArg2 + 54) = -1;
      }
      else  // 否则分支
      {
        *(this + pArg2 + 54) = -1;
      }
    }
    else  // 否则分支
    {
      *(this + pArg2 + 54) = nArg3;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x499020 sub_499020 —— 开关关闭时的时刻同步（+232 位 + +236/+240 参数）
//   当 +232 位由开转关（旧非 0、新 0）且 +120 对象存在时，对其推进帧时刻（·sub_4910E0）并按累计 +32 同步（·sub_493A60）；
//   随后无条件写 +232/+236/+240 三位；与 ·sub_499080 的浮点参数版同族。
// ------------------------------------------------------------
char /*thiscall*/ sub_499020(int this, char pszArg2, int nArg3, int nArg4)  // 实现：开关关闭时的时刻同步（+232 位 + +236/+240 参数）
{
  char result; // al
  int fld_78; // edi  | +0x0078 → 基类动画对象指针（CNRDObject；va=00499020）

  result = *(uint8_t *)(this + 232);  // this+232〔bSyncFlag〕
  if ( result != 0 && pszArg2 == 0 )  // 若 result != 0 与/或 pszArg2 == 0
  {
    fld_78 = *(uint32_t *)(this + 120);  // this+120〔pAnimObj〕
    if ( fld_78 != 0 )  // 若 fld_78 非 0
    {
      sub_4910E0(*(uint32_t *)(this + 120));  // 帧时刻推进（返回 1 表示时刻发生位移）
      result = sub_493A60(fld_78, *(uint32_t *)(fld_78 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
    }
  }
  *(uint8_t *)(this + 232) = pszArg2;  // this+232〔bSyncFlag〕
  *(uint32_t *)(this + 236) = nArg3;  // this+236〔nSyncArgA〕
  *(uint32_t *)(this + 240) = nArg4;  // this+240〔nSyncArgB〕
  return result;  // result=this+232 bSyncFlag
}



// ------------------------------------------------------------
// 0x499080 sub_499080 —— 浮点参数时刻同步（+244 由非 0 转 0 时推进）
//   参数归一（关闭时 fArg3 归 0）：目标槽 +244 原非 0 且新值为 0 时走 +120 对象的 ·sub_4910E0 + ·sub_493A60 推进，否则直接写 +244。
//   与 ·sub_499020 同族（浮点版）。
// ------------------------------------------------------------
void /*thiscall*/ sub_499080(int this, char pszArg2, float fArg3)  // 实现：浮点参数时刻同步（+244 由非 0 转 0 时推进）
{
  double fArg32; // st7
  int fld_78; // esi  | +0x0078 → 基类动画对象指针（CNRDObject；va=00499020）

  if ( pszArg2 != 0 )  // 若 pszArg2 非 0
  {
    fArg32 = fArg3;
  }
  else  // 否则分支
  {
    fArg32 = 0.0;
    fArg3 = 0.0;
  }
  if ( *(float *)(this + 244) == 0.0 || fArg32 != 0.0 )  // this+244〔fSyncTime〕
  {
    *(float *)(this + 244) = fArg32;  // this+244〔fSyncTime〕
  }
  else  // 否则分支
  {
    fld_78 = *(uint32_t *)(this + 120);  // this+120〔pAnimObj〕
    if ( fld_78 != 0 )  // 若 fld_78 非 0
    {
      sub_4910E0(*(uint32_t *)(this + 120));  // 帧时刻推进（返回 1 表示时刻发生位移）
      sub_493A60(fld_78, *(uint32_t *)(fld_78 + 32));  // 时间推进包装（累计 +32；+212 同步源优先）
      *(float *)(this + 244) = fArg3;  // this+244〔fSyncTime〕
    }
    else  // 否则分支
    {
      *(float *)(this + 244) = fArg32;  // this+244〔fSyncTime〕
    }
  }
}



// ------------------------------------------------------------
// 0x499110 sub_499110
// ------------------------------------------------------------
char /*thiscall*/ sub_499110(uint8_t *this, void *Src, int nArg3, int nArg4, int nArg5)  // 实现：音效标签播放（szPassword 去重 → sub_65FE10 分发到 50 声道）
{
  char result; // al
  int pThis_38; // eax

  result = 0;
  if ( strcmp((const char *)Src, szPassword) != 0 )  // 调 strcmp（串比较）
  {
    result = *(this + 172);  // this+688〔nSnapshot688〕
    if ( result != 0 )  // 若结果非 0（成功）
    {
      pThis_38 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 56))(this);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
      return sub_65FE10(Src, (int)(this + 176), nArg4, nArg5, 0, pThis_38, nArg3);  // 按标签名播声音：命中则立即播或入延迟队列，否则打 Tag Missing
    }
  }
  return result;  // result=this+688 nSnapshot688
}



// ------------------------------------------------------------
// 0x499170 sub_499170
// ------------------------------------------------------------
int /*thiscall*/ sub_499170(void *this, int nArg2)  // 实现：音效 TAG 查询
{
  int pThis_38; // eax

  pThis_38 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
  return sub_65DE30(pThis_38, nArg2);  // 按 (nArg2,nArg3) 键停止 50 个音源槽位中的对应流
}



// ------------------------------------------------------------
// 0x499190 sub_499190 —— 帧索引归零联动（命中则复位并 vt+84(0)）
//   当 *(this+28) 子对象的 +128 槽（【推断】帧索引）恰等于 nArg2 且 nArg2 非 0 时：调 ·sub_4A06D0(0) 复位，
//   再按 vt+40(this,2) 结果决定是否 vt+84(this,0) 结束播放。
// ------------------------------------------------------------
int /*thiscall*/ sub_499190(uint32_t *this, int nArg2)  // 实现：帧索引归零联动（命中则复位并 vt+84(0)）
{
  int result; // eax

  result = nArg2;
  if ( *(uint32_t *)(*(this + 28) + 128) == nArg2 && nArg2 != 0 )  // this+112〔pHostComp112〕
  {
    sub_4A06D0(0);  // 调 绑定目标对象并记录相对偏移
    result = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 2);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    if ( (uint8_t)result != 0 )
      return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 84))(this, 0);  // 调虚槽 +84：CNRDPrivateStoreWindow__vmt54 槽（参数写入 2 变体）
  }
  return result;
}



// ------------------------------------------------------------
// 0x4991D0 sub_4991D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4991D0(uint32_t *this)  // 实现：观察者组件懒创建（0x10 字节）
{
  void *pMem; // eax
  void *pMem2; // esi

  if ( *(this + 42) == 0 )  // this+168〔pAppendVec(推断)〕
  {
    pMem = operator new(0x10u);  // new(16 字节) 分配对象
    pMem2 = pMem;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      sub_50E730(pMem);  // 对象字段清零（三指针 + 两标志）
      sub_50E8D0(this);  // 表情气泡对象构造（EmoBalloonS.ani）
    }
    else  // 否则分支
    {
      pMem2 = nullptr;  // pMem2 = 空指针
    }
    *(this + 42) = pMem2;  // this+168〔pAppendVec(推断)〕
  }
  return *(this + 42);  // 返回成员 this+168
}



// ------------------------------------------------------------
// 0x499240 sub_499240 —— 像素距离（y 差值按 dword_7930D4 折算）
//   求两点欧氏距离；pszArg5 为 0 时把 y 方向差值乘 100/dword_7930D4[0] 做宽高比折算。
//   【推断】dword_7930D4[0] 为纵向像素基准比，与 ·sub_499280 同源。
// ------------------------------------------------------------
uint64_t /*cdecl*/ sub_499240(int nArg1, int nArg2, int pArg3, int nArg4, char pszArg5)  // 实现：像素距离（y 差值按 dword_7930D4 折算）
{
  int v5; // eax

  v5 = nArg2 - nArg4;
  if ( pszArg5 == 0 )  // 若 pszArg5 为 0
    v5 = 100 * v5 / dword_7930D4[0];
  return (uint64_t)sqrt((double)((nArg1 - pArg3) * (nArg1 - pArg3) + v5 * v5));  // 调 sqrt（平方根）
}



// ------------------------------------------------------------
// 0x499280 sub_499280
// ------------------------------------------------------------
double /*thiscall*/ sub_499280(void *this, int nArg2, char pszArg3)  // 实现：★ 与目标朝向角度（atan2 角度制；3D 俯视判定）(新发现(会话 3))
{
  int v4; // ebx
  int pThis_78; // ebx
  int v6; // edi
  int pThis_7C; // edi
  double result; // st7
  int pThis_7C2; // [esp+18h] [ebp+8h]

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 调虚槽 +120：动画对象
  pThis_78 = v4 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);  // 调虚槽 +120：动画对象
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 124))(nArg2);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  pThis_7C = v6 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  pThis_7C2 = pThis_7C;
  if ( pszArg3 == 0 )  // 若 pszArg3 为 0
  {
    pThis_7C = 100 * pThis_7C / dword_7930D4[0];
    pThis_7C2 = pThis_7C;
  }
  if ( pThis_78 != 0 )  // 若 pThis_78 非 0
  {
    result = atan2((double)pThis_7C2 / (double)pThis_78, 1.0) * 57.29577951308232;  // result = 调 atan2
    if ( pThis_78 >= 0 )  // 若 pThis_78 >= 0
    {
      if ( pThis_7C < 0 )  // 若 pThis_7C < 0
        return result + 360.0;
    }
    else  // 否则分支
    {
      return result + 180.0;
    }
  }
  else if ( pThis_7C < 0 )
  {
    return 270.0;  // 返回 270.0
  }
  else  // 否则分支
  {
    return 90.0;  // 返回 90.0
  }
  return result;
}



// ------------------------------------------------------------
// 0x499330 sub_499330
// ------------------------------------------------------------
long double /*thiscall*/ sub_499330(void *this, int nArg2, int nArg3)  // 实现：与目标俯仰角（z 轴）
{
  int v4; // esi
  signed int pThis_78; // esi
  int v6; // ebx
  int pThis_80; // ebx

  v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 120))(nArg2);  // 调虚槽 +120：动画对象
  pThis_78 = abs32(v4 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this));  // 调虚槽 +120：动画对象
  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 128))(nArg2);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  pThis_80 = v6 - (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  if ( pThis_78 != 0 )  // 若 pThis_78 非 0
    return atan2((double)(pThis_80 / pThis_78), 1.0) * 57.29577951308232;  // 返回 调 atan2
  if ( pThis_80 < 0 )  // 若 pThis_80 < 0
    return -90.0;  // 返回 -90.0
  return 90.0;  // 返回 90.0
}



// ------------------------------------------------------------
// 0x4993B0 sub_4993B0
// ------------------------------------------------------------
char /*thiscall*/ sub_4993B0(void *this, int *pDwArg2, int *pDwArg3, int nArg4, int nArg5, int nArg6, char pszArg7, int nArg8)  // 实现：★ 螺旋式寻找空位（同心方环，从 (a4,a5) 起向外扫）
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
  if ( pszArg7 != 0 )  // 若 pszArg7 非 0
  {
    v9 = nArg8 + 2 * nArg6;
    v20 = v9;
    if ( v9 > 0 )  // 若 v9 > 0
    {
      while ( 1 )  // 条件循环
      {
        v10 = v8 % 2 != 0 ? nArg5 - (v8 + 1) / 2 : nArg5 + v8 / 2;
        v11 = 0;
        if ( v9 > 0 )  // 若 v9 > 0
          break;  // 跳出循环/分支
LABEL_13:  // 标签 LABEL_13（跳转合流点）
        v8 += nArg8;
        v19 = v8;
        if ( v8 >= v9 )  // 若 v8 >= v9
          return 0;
      }
      while ( 1 )  // 条件循环
      {
        v12 = v11 % 2 != 0 ? nArg4 - (v11 + 1) / 2 : nArg4 + v11 / 2;
        if ( (*(uint8_t (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v12, v10, 0) != 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
          break;  // 跳出循环/分支
        v11 += nArg8;
        if ( v11 >= v20 )  // 若 v11 >= v20
        {
          v8 = v19;
          v9 = v20;
          goto LABEL_13;
        }
      }
      *pDwArg2 = v12;
      *pDwArg3 = v10;
      return 1;  // 返回 1(成功)
    }
    return 0;
  }
  v14 = nArg8 + 2 * nArg6;
  v21 = v14;
  if ( v14 <= 0 )  // 若 v14 <= 0
    return 0;
  while ( 1 )  // 条件循环
  {
    v15 = v8 % 2 != 0 ? nArg4 - (v8 + 1) / 2 : nArg4 + v8 / 2;
    v16 = 0;
    if ( v14 > 0 )  // 若 v14 > 0
      break;  // 跳出循环/分支
LABEL_27:  // 标签 LABEL_27（跳转合流点）
    v8 += nArg8;
    v19 = v8;
    if ( v8 >= v14 )  // 若 v8 >= v14
      return 0;
  }
  while ( 1 )  // 条件循环
  {
    v17 = v16 % 2 != 0 ? nArg5 - (v16 + 1) / 2 : nArg5 + v16 / 2;
    if ( (*(uint8_t (/*thiscall*/ **)(void *, int, int, uint32_t))(*(uint32_t *)this + 136))(this, v15, v17, 0) != 0 )  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
      break;  // 跳出循环/分支
    v16 += nArg8;
    if ( v16 >= v21 )  // 若 v16 >= v21
    {
      v8 = v19;
      v14 = v21;
      goto LABEL_27;
    }
  }
  *pDwArg2 = v15;
  *pDwArg3 = v17;
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x499560 sub_499560 —— 重试式预约（延迟 30 起每次 +10，最多 nArg6 次）
//   以 vt+140 反复尝试同一组 (nArg2..nArg5) 预约，延迟从 30 起步、每次 +10 递增，最多 nArg6 次，任一次成功返回 1。
//   【推断】用于技能/演出排队的退避重试（末两参固定 1）。
// ------------------------------------------------------------
char /*cdecl*/ sub_499560(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)  // 实现：重试式预约（延迟 30 起每次 +10，最多 nArg6 次）
{
  int v6; // edi
  int v8; // [esp+Ch] [ebp-4h]

  v8 = 0;
  if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int, int, int, int, int))(*(uint32_t *)nArg1 + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
         nArg1,
         nArg2,
         nArg3,
         nArg4,
         nArg5,
         30,
         1,
         1) != 0 )
    return 1;  // 返回 1(成功)
  v6 = 30;
  while ( 1 )  // 条件循环
  {
    v6 += 10;
    if ( ++v8 >= nArg6 )
      break;  // 跳出循环/分支
    if ( (*(uint8_t (/*thiscall*/ **)(int, int, int, int, int, int, int, int))(*(uint32_t *)nArg1 + 140))(  // 调虚槽 +140：CNProvocationDollAura__vmt8C 槽（17 行）
           nArg1,
           nArg2,
           nArg3,
           nArg4,
           nArg5,
           v6,
           1,
           1) != 0 )
      return 1;  // 返回 1(成功)
  }
  return 0;
}



// ------------------------------------------------------------
// 0x4995F0 sub_4995F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4995F0(void *this, uint32_t *uArg2, uint32_t *uArg3, int nArg4, int nArg5)  // 实现：朝目标方向按比例取点: p = this + (target − this) × (1 − a5/距离)
{
  int v6; // ebx
  double pThis_8; // st7
  int result; // eax
  int pThis_7C; // [esp+Ch] [ebp-Ch]
  int v10; // [esp+10h] [ebp-8h]
  int pThis_78; // [esp+14h] [ebp-4h]
  float v12; // [esp+2Ch] [ebp+14h]

  v6 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 120))(nArg4);  // 调虚槽 +120：动画对象
  v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg4 + 124))(nArg4);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  pThis_78 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 120))(this);  // 调虚槽 +120：动画对象
  pThis_7C = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v12 = (float)nArg5;
  pThis_8 = 1.0 - v12 / (double)(*(int (/*thiscall*/ **)(void *, int, int))(*(uint32_t *)this + 8))(this, nArg4, 1);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
  *uArg2 = pThis_78 + (uint64_t)((double)(v6 - pThis_78) * pThis_8);
  result = pThis_7C + (uint64_t)((double)(v10 - pThis_7C) * pThis_8);
  *uArg3 = result;
  return result;
}



// ------------------------------------------------------------
// 0x499690 sub_499690 —— 绘制基元包装（按标志翻转 X 偏移与缩放）
//   依据 a6 低字节决定水平镜像：镜像时 x 取 a2-a4、缩放取 -a8，否则取 a2+a4 与 +a8，
//   统一转 ·sub_424760 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）。
// ------------------------------------------------------------
void /*cdecl*/ sub_499690(  // 绘制基元包装（按标志翻转 X 偏移与缩放）
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
  else  // 否则分支
  {
    v14 = a8;
    v13 = a2 + a4;
  }
  sub_424760(a1, v13, a5 + a3, a7, v14, a9, a10, a11, a12, a13);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
}



// ------------------------------------------------------------
// 0x4996F0 sub_4996F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4996F0(uint32_t *this)  // 实现：动画对象 z 倾斜转状态码
{
  double fld_e28; // st7

  fld_e28 = *(float *)(*(this + 28) + 16);  // this+112〔pHostComp112〕
  if ( fld_e28 > 5.0 )  // fld_e28=this+112 pHostComp112
    return 1;  // 返回 1(成功)
  if ( fld_e28 >= -5.0 )  // fld_e28=this+112 pHostComp112
    return _RTC_NumErrors();  // 返回 调 _RTC_NumErrors
  return 0;
}



// ------------------------------------------------------------
// 0x49971B __RTC_NumErrors —— RTC 错误号计数（恒 4）
//   运行时检查库桩，固定返回 4（RTC 错误分类数），无业务语义。
// ------------------------------------------------------------
int /*cdecl*/ _RTC_NumErrors()  // 实现：RTC 错误号计数（恒 4）
{
  return 4;
}



// ------------------------------------------------------------
// 0x499730 sub_499730 —— 斜率分档（>5→3、区间内→4、<-5→2）
//   读 *(this+28) 子对象 +20 处浮点值分档：大于 5 返回 3，[-5,5] 返回 4，小于 -5 返回 2。
//   【推断】对应当前朝向三态（顺时针/无/逆时针）。
// ------------------------------------------------------------
int /*thiscall*/ sub_499730(uint32_t *this)  // 实现：斜率分档（>5→3、区间内→4、<-5→2）
{
  double fld_e28; // st7
  int result; // eax

  fld_e28 = *(float *)(*(this + 28) + 20);  // this+112〔pHostComp112〕
  if ( fld_e28 > 5.0 )  // fld_e28=this+112 pHostComp112
    return 3;
  result = 2;
  if ( fld_e28 >= -5.0 )  // fld_e28=this+112 pHostComp112
    return 4;
  return result;
}



// ------------------------------------------------------------
// 0x499770 sub_499770 —— 双槽设置（+268/+272）
//   把 nArg2/nArg3 分写 *(this+67)（+268）与 *(this+68)（+272）并返回 nArg2。
// ------------------------------------------------------------
int /*thiscall*/ sub_499770(uint32_t *this, int nArg2, int nArg3)  // 实现：双槽设置（+268/+272）
{
  *(this + 67) = nArg2;  // this+67 周期 ms
  *(this + 68) = nArg3;  // this+68 角色数（begin/end 差 >>2；>=8 …
  return nArg2;
}



// ------------------------------------------------------------
// 0x4997A0 sub_4997A0 —— 对象槽默认装配（+40..+168 全量 + 七字段下发）
//   逐槽置默认：+4..+36 九格清 0、+40/+44/+48 置 -1、+52 与 +101 置 1、+144 装 off_6C2B88 虚表、+156 置 1 等；
//   再经 ·sub_49FC60 把 +44..+57 七字段全量下发，最后按 nArg2 走 ·sub_4A0770 初始化。
// ------------------------------------------------------------
int /*thiscall*/ sub_4997A0(int this, int nArg2)  // 实现：对象槽默认装配（+40..+168 全量 + 七字段下发）
{
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 16) = 0;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 36) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = -1;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = -1;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = -1;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint8_t *)(this + 52) = 1;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 53) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 65) = 0;  // this+260〔nQuad4〕
  *(uint32_t *)(this + 77) = 0;  // this+77〔bGuildFlagB〕
  *(uint32_t *)(this + 89) = -1;  // this+89〔nLifetime〕
  *(uint32_t *)(this + 57) = 0;  // this+228〔nSnapDst228(推断)〕
  *(uint32_t *)(this + 69) = 0;  // this+276〔pMapEntry(推断)〕
  *(uint32_t *)(this + 81) = 0;  // this+324〔nAnchor324(推断)〕
  *(uint32_t *)(this + 93) = -1;  // this+93〔bEnableFlag〕
  *(uint32_t *)(this + 61) = 0;  // this+61〔bReadyFlagA〕
  *(uint32_t *)(this + 73) = 0;  // this+73〔szDigitalName(推断)〕等 2 字段
  *(uint32_t *)(this + 85) = 0;  // this+340〔pSlotTbl340(推断)〕
  *(uint32_t *)(this + 97) = -1;  // this+97〔bFlag97〕
  *(uint8_t *)(this + 101) = 1;  // this+101〔bFired101(推断)〕
  *(uint8_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 144) = &off_6C2B88;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint8_t *)(this + 156) = 1;  // this+156〔nAdd156(推断)〕
  *(uint8_t *)(this + 158) = 0;
  *(uint8_t *)(this + 157) = 0;
  *(uint32_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
  *(uint32_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  sub_49FC60(this);  // 七字段访问器（+44..+57 全量下发）
  sub_4A0770(nArg2);  // 调 (推断)设置宿主/所有者指针并联动 sub_49FD20（动画归属重绑）
  return this;
}



// ------------------------------------------------------------
// 0x499880 sub_499880 —— 析构序（资源释放 + 虚表回落 IObject）
//   先调 ·sub_649170 释放关联资源（RTTI 名 CNDarkDamageFromCurseAura__vmt78），
//   再把 +144 虚表指针回落 nengine::IObject 并清 +148；与 ·sub_4999D0 同族。
// ------------------------------------------------------------
int /*thiscall*/ sub_499880(int this)  // 实现：析构序（资源释放 + 虚表回落 IObject）
{
  int result; // eax

  result = sub_649170();  // 【CNDarkDamageFromCurseAura__vmt78】
  *(uint32_t *)(this + 144) = &nengine::IObject::`vftable';  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint8_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x4998D0 sub_4998D0 —— 单次初始化 + 分配转发（首次注册 atexit 清理）
//   用 dword_9A024C 位 0 作一次性门：首次以 ·sub_657800(nArg1, 256) 建池并 atexit(·sub_6BF9D0) 注册清理，置 dword_9A0268 标记；
//   最后返回 ·sub_6578B0(nArg1) 的分配结果。
// ------------------------------------------------------------
int /*cdecl*/ sub_4998D0(int nArg1)  // 实现：单次初始化 + 分配转发（首次注册 atexit 清理）
{
  if ( dword_9A0268 == 0 )  // 若 dword_9A0268 为 0
  {
    if ( (dword_9A024C & 1) == 0 )  // 若 dword_9A024C 位 1 清零
    {
      dword_9A024C |= 1u;
      sub_657800(nArg1, 256);  // MTUPD 内存池初始化：清 +12..+20 后以 「MemoryPools」 名转 sub_659B80 注册
      atexit(sub_6BF9D0);  // 调 atexit（登记退出回调（表满返回非 0））
    }
    dword_9A0268 = (int)&unk_9A022C;
  }
  return sub_6578B0(nArg1);  // 环形队列取头结点（空则经 sub_657780 挂载）
}



// ------------------------------------------------------------
// 0x499960 sub_499960 —— 子对象构造（off_6C2B88 装配 + 基类初始化）
//   按 off_6C2B88 装虚表并清默认槽（+8=0、+12=0、+16=1），调 ·sub_50EAD0 做基类构造，
//   再以 (Block, nArg3, nArg4) 调 ·sub_50F1C0 完成资源侧初始化。
// ------------------------------------------------------------
int /*thiscall*/ sub_499960(int this, void *Block, int nArg3, int nArg4)  // 实现：子对象构造（off_6C2B88 装配 + 基类初始化）
{
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 4) = &off_6C2B88;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 12) = 0;  // this+12〔nSkillRec12(推断)〕等 2 字段
  *(uint8_t *)(this + 16) = 1;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  *(uint8_t *)(this + 18) = 0;  // this+18〔bDragChild〕
  *(uint8_t *)(this + 17) = 0;  // this+17〔bEnable〕
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 0;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  sub_50EAD0();  // 气泡对象定时/计数状态复位
  sub_50F1C0(Block, nArg3, nArg4);  // 气泡文本宿主绑定（建 96B CNText + 取屏幕边界）
  return this;
}



// ------------------------------------------------------------
// 0x4999D0 sub_4999D0 —— 子对象析构序（基类释放 + 虚表回落）
//   先调 ·sub_50EAF0 做基类释放，再把 +4 虚表回落 nengine::IObject 并清 +8。
// ------------------------------------------------------------
int /*thiscall*/ sub_4999D0(int this)  // 实现：子对象析构序（基类释放 + 虚表回落）
{
  int result; // eax

  result = sub_50EAF0();  // 释放内嵌对象（this+32）并置空
  *(uint32_t *)(this + 4) = &nengine::IObject::`vftable';  // this+4〔宿主对象〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  return result;
}



// ------------------------------------------------------------
// 0x499A20 sub_499A20 —— 对象重建（三时钟复位 + 204 字节子对象装配）
//   先把 +8/+36/+64 三个时钟经 ·sub_698F90 清零；按 204 字节规格经 ·sub_4998D0 分配、·sub_4997A0 装配成子对象挂 +112；
//   随后 vt+92(nArg2) 与 vt+72(1) 初始化，把 +24 置 2、+157 置 pszArg3、+264 清 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_499A20(uint32_t *this, int nArg2, char pszArg3)  // 实现：对象重建（三时钟复位 + 204 字节子对象装配）
{
  int v4; // eax
  int v5; // eax
  int result; // eax

  sub_698F90((int)(this + 2), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  sub_698F90((int)(this + 9), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  sub_698F90((int)(this + 16), 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( sub_4998D0(204) != 0 )  // 单次初始化 + 分配转发（首次注册 atexit 清理）
    v4 = sub_4997A0(this);  // 对象槽默认装配（+40..+168 全量 + 七字段下发）
  else  // 否则分支
    v4 = 0;
  *(this + 28) = v4;  // this+112〔pHostComp112〕
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 92))(this, nArg2);  // 调虚槽 +92：CNRDPrivateStoreWindow_Display__vmt5C 槽（102 行：…
  v5 = *this;
  *(this + 24) = 2;  // this+96〔nStatusMode(推断)〕
  *((uint8_t *)this + 157) = pszArg3;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 72))(this, 1);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520/4…
  *((uint8_t *)this + 264) = 0;  // this[264] = 0
  return result;
}



// ------------------------------------------------------------
// 0x499AD0 sub_499AD0
// ------------------------------------------------------------
int /*thiscall*/ sub_499AD0(void *Block)  // 实现：取观察者容器（懒创建 0x44 字节 sb_499960(this,120)）
{
  void *pMem; // eax
  int v3; // eax

  if ( *((uint32_t *)Block + 41) == 0 )
  {
    pMem = operator new(0x44u);  // new(68 字节) 分配对象
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
      v3 = sub_499960((int)pMem, Block, 120, 0);  // 子对象构造（off_6C2B88 装配 + 基类初始化）
    else  // 否则分支
      v3 = 0;
    *((uint32_t *)Block + 41) = v3;  // Block[41] = v3
  }
  return *((uint32_t *)Block + 41);
}



// ------------------------------------------------------------
// 0x499B40 sub_499B40 —— 默认参数重建（转发 sub_499A20(0,0)）
//   以 (0, 0) 转发 ·sub_499A20，执行默认参数的对象重建。
// ------------------------------------------------------------
int /*thiscall*/ sub_499B40(uint32_t *this)  // 实现：默认参数重建（转发 sub_499A20(0,0)）
{
  return sub_499A20(this, 0, 0);  // 对象重建（三时钟复位 + 204 字节子对象装配）
}



// ------------------------------------------------------------
// 0x499B50 sub_499B50
// ------------------------------------------------------------
char /*thiscall*/ sub_499B50(char *this, char pszArg2)  // 实现：★ 濒死/一击表现（LAST STRIKE；死亡链上游）(新发现(会话 3))
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
  if ( (pszArg2 != 0 || (result = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 308))(this)) != 0) && *(this + 264) != 1 )  // 调虚槽 +308：是否本地玩家
  {
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 23, 2);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    v4 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    pThis_30 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 48))(this);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v4 + 36))(dword_8F8520, pThis_30);  // 会话/UDP 管理器
    v6 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    pThis_34 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v6 + 36))(dword_8F8520, pThis_34);  // 会话/UDP 管理器
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    v8 = *(uint32_t *)this;
    *(this + 264) = 1;  // this+264 动画句柄
    result = (*(int (/*thiscall*/ **)(char *, int))(v8 + 40))(this, 529);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    if ( result != 0 )  // 若结果非 0（成功）
    {
      if ( *((uint32_t *)this + 78) < 0x10u )  // this+78 公会标志字节 C
        pThis_124 = this + 292;
      else  // 否则分支
        pThis_124 = *((char **)this + 73);  // this+73 基类名字缓冲 SSO 首字节
      pThis_342 = (*(int (/*thiscall*/ **)(char *))(*(uint32_t *)this + 52))(this);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
      return off_77F3FC((char *)&byte_6CB870, pThis_124, pThis_342);  // 返回 调 off_77F3FC
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x499C20 sub_499C20 —— 28 字节节点分配（2 入参 + 5 槽拷贝）
//   operator new(0x1C) 后写入两枚入参，再把 pArg3[0..4] 五个槽原样拷入 +8..+24。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_499C20(int nArg1, int nArg2, uint32_t *pArg3)  // 实现：28 字节节点分配（2 入参 + 5 槽拷贝）
{
  uint32_t *result; // eax

  result = operator new(0x1Cu);  // new(28 字节) 分配对象
  if ( result != nullptr )  // 若 result 有效（非空）
  {
    *result = nArg1;
    result[1] = nArg2;
    result[2] = *pArg3;
    result[3] = pArg3[1];  // result[3] = 取 pArg3[1]
    result[4] = pArg3[2];  // result[4] = 取 pArg3[2]
    result[5] = pArg3[3];  // result[5] = 取 pArg3[3]
    result[6] = pArg3[4];  // result[6] = 取 pArg3[4]
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
int /*thiscall*/ sub_499C70(uint8_t *this)  // 实现：每帧表现主循环（子对象循环渲染）
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

  pThis_1E = *((uint32_t *)this + 30);  // this+120〔pAnimObj〕
  if ( pThis_1E != 0 )  // 若 pThis_1E 非 0
  {
    sub_4938F0(pThis_1E);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    pThis_1C = *(uint32_t *)(*((uint32_t *)this + 28) + 104);  // this+112〔pHostComp112〕
    pThis_39 = *((uint32_t *)this + 57);  // this+228〔nSnapDst228(推断)〕
    pThis_392 = pThis_39;  // pThis_39=this+228 nSnapDst228
    if ( pThis_1C != 0 && 100.0 != ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)pThis_1C + 64))(pThis_1C) )  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
    {
      if ( pThis_39 == -1 )  // pThis_39=this+228 nSnapDst228
        pThis_392 = 255;
      pThis_39 = (uint64_t)(((double (/*thiscall*/ *)(uint32_t))*(uint32_t *)(**(uint32_t **)(*((uint32_t *)this + 28) + 104)  // this+112〔pHostComp112〕
                                                                        + 64))(*(uint32_t *)(*((uint32_t *)this + 28) + 104))  // this+112〔pHostComp112〕
                            * (double)pThis_392
                            * 0.0099999998);
    }
    sub_491F80(*((uint32_t *)this + 54), *((uint32_t *)this + 55), *((uint32_t *)this + 56), pThis_39, 1);  // RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
    if ( *(this + 232) != 0 )  // this+232 bSyncFlag
      sub_492030(*((uint32_t *)this + 59), *((uint32_t *)this + 60), 1);  // 子对象绘制原点/尺寸下发（+100/+104 转发给 +204 子链）
    if ( (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 276))(this) != 0 )  // 调虚槽 +276：浮点非零判定（+244）
      sub_492080(*((float *)this + 61));  // 播放速率写入（+172 新速率；差值补偿累计时刻 +88）
  }
  pThis_8 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this) + 8);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this);  // 调虚槽 +120：动画对象
  v6 = sub_45E490(pThis_78, pThis_8);  // 屏幕 y → 演出层坐标（减基线）
  v21 = v6;
  pThis_82 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this) + 8);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 124))(this);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v25 = sub_45E4D0(pThis_7C, pThis_80, pThis_82, 1.0);  // 带比例的回换算（nArg2 - nArg3*f + 120）
  LOBYTE(v26) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 152))(this) != 1;  // 调虚槽 +152：效果通道 3
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, int, int, uint8_t))(*(uint32_t *)this + 324))(  // 调虚槽 +324：CNRDNpc__vmt144 绘制槽（5677B0 标记 + 418DD0/472E30/…
    this,
    0,
    v6,
    v25,
    LOBYTE(v26));
  pThis_20 = *((uint32_t **)this + 32);  // this+32 格子像素尺寸
  v9 = (uint32_t *)*pThis_20;  // pThis_20=this+128 第 2 组·+1208 增量子倍率
  if ( (uint32_t *)*pThis_20 != pThis_20 )  // pThis_20=this+128 第 2 组·+1208 增量子倍率
  {
    do  // do-while 循环体起点
    {
      if ( (int)v9[2] >= 0 )
        break;  // 跳出循环/分支
      if ( *((uint8_t *)v9 + 25) == 0 )
      {
        sub_4938F0(v9[3]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
        if ( LOBYTE(v26) != 0 )
          v11 = v6 - v9[4];
        else  // 否则分支
          v11 = v6 + v9[4];
        LOBYTE(v10) = (*((uint8_t *)v9 + 24) != 0) - 1;
        sub_491D00(dword_79C0B0, v11, v25 + v9[5], COERCE_FLOAT(LODWORD(v26) & v10));  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
      v9 = (uint32_t *)*v9;
    }
    while ( v9 != *((uint32_t **)this + 32) );  // 条件循环
  }
  if ( *((uint32_t *)this + 30) != 0 )  // this+120〔pAnimObj〕
  {
    if ( *(this + 248) != 0 )  // this+992〔uCfgB992(推断)〕
    {
      if ( *(this + 256) != 0 )  // this+1024〔nBurnT1_1024〕
      {
        nRand = rand();  // nRand = 调 rand
        v22 = nRand % 3 - 1;
        if ( nRand % 3 == 1 )
          nRand2 = rand() % 2 != 0 ? 2 : 0;  // nRand2 = 调 rand
        else  // 否则分支
          nRand2 = rand() % 3;  // nRand2 = 调 rand
        sub_491DE0(  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
          dword_79C0B0,  // 默认字体/绘制资源
          v6 + v22 * *((uint32_t *)this + 65),  // this+260〔nQuad4〕
          v25 + (nRand2 - 1) * *((uint32_t *)this + 65),  // this+260〔nQuad4〕
          v26,
          0,
          1,
          *((uint32_t *)this + 63),  // this+252〔nQuad2〕
          -1761607681);
      }
      else  // 否则分支
      {
        v14 = 0;
        v23 = 0;
        do  // do-while 循环体起点
        {
          if ( v14 != 4 )  // 若 v14 != 4
          {
            v6 = v21;
            sub_491DE0(  // 图层属性下发·纯 STENCIL 变体（只走 sub_4917A0）
              dword_79C0B0,  // 默认字体/绘制资源
              v21 + *((uint32_t *)this + 65) * (v14 / 3u - 1),  // this+260〔nQuad4〕
              v25 + *((uint32_t *)this + 65) * (v14 % 3u - 1),  // this+260〔nQuad4〕
              v26,
              0,
              1,
              *((uint32_t *)this + 63),  // this+252〔nQuad2〕
              (*(this + 255) << 24) | 0xFFFFFF);  // this+1020〔pAnimHandleArr(推断)〕
            v14 = v23;
          }
          v23 = ++v14;
        }
        while ( v14 < 9 );  // 条件循环
      }
    }
    sub_491D00(dword_79C0B0, v6 + *((uint32_t *)this + 67), v25 + *((uint32_t *)this + 68), v26);  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
  }
  for ( ; v9 != *((uint32_t **)this + 32); v9 = (uint32_t *)*v9 )  // 遍历循环
  {
    if ( *((uint8_t *)v9 + 25) == 0 )
    {
      sub_4938F0(v9[3]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      if ( LOBYTE(v26) != 0 )
      {
        v15 = v9[4];  // v15 = 取 v9[4]
        v16 = v6 - v15;
      }
      else  // 否则分支
      {
        v16 = v6 + v9[4];
      }
      LOBYTE(v15) = (*((uint8_t *)v9 + 24) != 0) - 1;
      sub_491D00(dword_79C0B0, v16, v25 + v9[5], COERCE_FLOAT(LODWORD(v26) & v15));  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    }
  }
  result = (*(int (/*thiscall*/ **)(uint8_t *, int, int, int, uint8_t))(*(uint32_t *)this + 324))(  // 调虚槽 +324：CNRDNpc__vmt144 绘制槽（5677B0 标记 + 418DD0/472E30/…
             this,
             1,
             v6,
             v25,
             LOBYTE(v26));
  if ( *((uint32_t *)this + 41) != 0 )  // this+164〔fAdd164(推断)〕
    result = sub_50EB40(v6, v25, 255);  // 表情气泡绘制（按行数拼 9-slice：id 63/64/65/66）
  if ( *((uint32_t *)this + 42) != 0 )  // this+168〔pAppendVec(推断)〕
    return sub_50E750(v6, v25);  // 表情气泡双图层播放推进
  return result;
}


// ------------------------------------------------------------
// 0x499FF0 sub_499FF0 —— 主播放驱动·usercall 变体（ecx/ebx 传参；+44 尾帧事件）
// ------------------------------------------------------------
int /*usercall*/ sub_499FF0@<eax>(float *pArg1@<ecx>, float fArg2@<ebx>)  // 实现：主播放驱动·usercall 变体（ecx/ebx 传参；+44 尾帧事件）
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
  if ( v3 != 0 )  // 若 v3 非 0
  {
    sub_4938F0(v3);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    pObj = *(uint32_t *)(*((uint32_t *)pArg1 + 28) + 104);
    v5 = *((uint32_t *)pArg1 + 57);
    v25 = v5;
    if ( pObj != 0 && 100.0 != ((double (/*thiscall*/ *)(int))*(uint32_t *)(*(uint32_t *)pObj + 64))(pObj) )  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/…
    {
      if ( v5 == -1 )
        v25 = 255;
      v5 = (uint64_t)(((double (/*thiscall*/ *)(uint32_t))*(uint32_t *)(**(uint32_t **)(*((uint32_t *)pArg1 + 28) + 104) + 64))(*(uint32_t *)(*((uint32_t *)pArg1 + 28) + 104))  // 调虚槽 +64：CNRDPlayDungeonResultWindow__vmt40 文案槽（459700/40…
                            * (double)v25
                            * 0.0099999998);
    }
    sub_491F80(*((uint32_t *)pArg1 + 30), *((uint32_t *)pArg1 + 54), *((uint32_t *)pArg1 + 55), *((uint32_t *)pArg1 + 56), v5, 1);  // RGBA 设置（打包于 +92；-1=保留原通道；a6≠0 时广播子链 +204）
    if ( (*(uint8_t (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 276))(pArg1) != 0 )  // 调虚槽 +276：浮点非零判定（+244）
      sub_492080(*((uint32_t *)pArg1 + 30), pArg1[61]);  // 播放速率写入（+172 新速率；差值补偿累计时刻 +88）
  }
  v24 = *(uint32_t *)((*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 36))(pArg1) + 8);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  v6 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 120))(pArg1);  // 调虚槽 +120：动画对象
  v27 = sub_45E490(v6, v24);  // 屏幕 y → 演出层坐标（减基线）
  v23 = *(uint32_t *)((*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 36))(pArg1) + 8);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
  v7 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  v8 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)pArg1 + 124))(pArg1, v7);  // 调虚槽 +124：CNAuraChangeStatusMaster__vmt7C 状态变化（5F8000，69…
  v9 = sub_45E4D0(v8, v23, 0, fArg2);  // 带比例的回换算（nArg2 - nArg3*f + 120）
  v26 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 128))(pArg1);  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
  LOBYTE(v28) = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)pArg1 + 152))(pArg1) != 1;  // 调虚槽 +152：效果通道 3
  (*(void (/*thiscall*/ **)(float *, uint32_t, int, int, uint8_t))(*(uint32_t *)pArg1 + 328))(  // 调虚槽 +328：IRDActiveObject__vmt148 2D 精灵绘制：491530/491630 …
    pArg1,
    0,
    v27 + *((uint32_t *)pArg1 + 67),
    v9 + *((uint32_t *)pArg1 + 68),
    LOBYTE(v28));
  v10 = *((uint32_t **)pArg1 + 32);
  v11 = (uint32_t *)*v10;
  if ( (uint32_t *)*v10 != v10 )
  {
    do  // do-while 循环体起点
    {
      if ( (int)v11[2] >= 0 )
        break;  // 跳出循环/分支
      sub_4938F0(v11[3]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
      if ( *((uint8_t *)v11 + 25) != 0 )
      {
        v14 = LOBYTE(v28) != 0 ? v27 - v11[4] : v27 + v11[4];  // v14 = 调 LOBYTE
        LOBYTE(v13) = (*((uint8_t *)v11 + 24) != 0) - 1;
        sub_491D00(v11[3], dword_79C0B0, v14, v9 + v11[5], COERCE_FLOAT(LODWORD(v28) & v13));  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
      }
      else  // 否则分支
      {
        v15 = LOBYTE(v28) != 0 ? v27 - v11[4] : v27 + v11[4];  // v15 = 调 LOBYTE
        LOBYTE(v12) = (*((uint8_t *)v11 + 24) != 0) - 1;
        sub_491EA0(  // 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161 阴影位门）
          v11[3],
          dword_79C0B0,  // 默认字体/绘制资源
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
    while ( v11 != *((uint32_t **)pArg1 + 32) );  // 条件循环
  }
  v16 = *((uint32_t *)pArg1 + 30);
  if ( v16 != 0 )  // 若 v16 非 0
    sub_491EA0(v16, dword_79C0B0, v27, v9, v28, v26, 0.40000001, 0.30000001, 100);  // 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161 阴影位门）
  for ( ; v11 != *((uint32_t **)pArg1 + 32); v11 = (uint32_t *)*v11 )  // 遍历循环
  {
    sub_4938F0(v11[3]);  // 播放驱动总入口：+169 暂停判定 → sub_493840 切帧 → sub_4919D0 插值；递归子链 +204
    if ( *((uint8_t *)v11 + 25) != 0 )
    {
      if ( LOBYTE(v28) != 0 )
        v19 = v27 - v11[4];
      else  // 否则分支
        v19 = v27 + v11[4];
      LOBYTE(v18) = (*((uint8_t *)v11 + 24) != 0) - 1;
      sub_491D00(v11[3], dword_79C0B0, v19, v9 + v11[5], COERCE_FLOAT(LODWORD(v28) & v18));  // 图层属性下发 + 子链广播（本层块 this+60，递归 +204 子动画链）
    }
    else  // 否则分支
    {
      if ( LOBYTE(v28) != 0 )
        v20 = v27 - v11[4];
      else  // 否则分支
        v20 = v27 + v11[4];
      LOBYTE(v17) = (*((uint8_t *)v11 + 24) != 0) - 1;
      sub_491EA0(  // 帧图像绘制入口（递归 +204 子链；byte_790AD0 全局开关 + 自身 +161 阴影位门）
        v11[3],
        dword_79C0B0,  // 默认字体/绘制资源
        v20,
        v9 + v11[5],
        COERCE_FLOAT(LODWORD(v28) & v17),
        v26,
        0.40000001,
        0.30000001,
        100);
    }
  }
  (*(void (/*thiscall*/ **)(float *, int, int, int))(*(uint32_t *)pArg1 + 328))(pArg1, 1, v27, v9);  // 调虚槽 +328：IRDActiveObject__vmt148 2D 精灵绘制：491530/491630 …
  result = dword_8F7A24;  // 登录/选区管理器
  if ( *(uint32_t *)(dword_8F7A24 + 12) == 4 )  // 登录/选区管理器
  {
    result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
    if ( *(uint32_t *)(result + 44) != 0 )
    {
      result = *((uint32_t *)pArg1 + 24);
      if ( result == 273 || result == 529 )  // 若 result == 273 与/或 result == 529
      {
        v22 = *((uint32_t *)pArg1 + 30);
        if ( v22 != 0 )  // 若 v22 非 0
          *(uint8_t *)(v22 + 161) = 1;
      }
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x49A320 sub_49A320 —— 播放状态切换（+50/+51/+52 位组、子链级联、特效槽 +40）
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_49A320(uint32_t *this, int nArg2, uint32_t **uArg3, int nArg4)  // 实现：播放状态切换（+50/+51/+52 位组、子链级联、特效槽 +40）
{
  uint32_t **result; // eax
  int nArg22; // ebx
  int fld_e50; // edi
  int fld_e30; // edi  | +0x0078 → 基类动画对象指针（CNRDObject；va=00499020）
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
  if ( nArg2 != 0 && uArg3 == nullptr )  // 若 nArg2 != 0 与/或 uArg3 == nullptr
    nArg22 = 0;
  fld_e50 = *(this + 50);  // this+200〔nMainState(推断)〕
  fld_e502 = fld_e50;  // fld_e50=this+200 nMainState
  *(this + 50) = nArg22;  // this+200〔nMainState(推断)〕
  if ( nArg22 != 0 )  // 若 nArg22 非 0
  {
    *(this + 51) = uArg3;  // this+204〔pSubAnim204(推断)〕
    result = (uint32_t **)(nArg4 + sub_699000(this + 2));  // 【clock_now(clk)】
    *(this + 52) = result;  // this+208〔nField208(推断)〕
  }
  if ( fld_e50 != nArg22 )  // 若 fld_e50 != nArg22
  {
    if ( fld_e50 < 1 )  // 若 fld_e50 < 1
    {
      if ( nArg22 >= 1 )  // 若 nArg22 >= 1
      {
        fld_e30 = *(this + 30);  // this+120〔pAnimObj〕
        if ( fld_e30 != 0 )  // 若 fld_e30 非 0
        {
          if ( *(uint32_t *)(fld_e30 + 212) != 0 )  // fld_e30=this+120 pAnimObj
            *((uint8_t *)this + 212) = sub_4910C0();  // 沿 +212 同步源链上溯，返回链尾对象的 +169（暂停/冻结位）
          else  // 否则分支
            *((uint8_t *)this + 212) = *(uint8_t *)(fld_e30 + 169);  // this+212〔nField212(推断)〕
          sub_4939E0(1);  // 播放/暂停级联（递归子链 +204）
        }
        else  // 否则分支
        {
          *((uint8_t *)this + 212) = 0;  // this[212] = 0
        }
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        {
          v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 844))(this);  // 调虚槽 +844：内嵌动作子对象 this+6560
        }
        else  // 否则分支
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 65) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
            goto LABEL_20;
          v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);  // 调虚槽 +684：取攻击上下文
        }
        sub_699030(v9);  // 【clock_freeze(clk)】
LABEL_20:  // 标签 LABEL_20（跳转合流点）
        sub_4A0680(1);  // 调 被 CNRDObject_vmtE4（0x49A320）用作子对象全冻的施加点
        sub_699030(this + 9);  // 【clock_freeze(clk)】
        result = (uint32_t **)*(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
        v10 = *result;  // result=this+128 szStatusKeyBuf
        if ( *result != result )  // result=this+128 szStatusKeyBuf
        {
          do  // do-while 循环体起点
          {
            result = (uint32_t **)sub_4939E0(1);  // 播放/暂停级联（递归子链 +204）
            v10 = (uint32_t *)*v10;
          }
          while ( v10 != (uint32_t *)*(this + 32) );  // 条件循环
        }
      }
LABEL_34:  // 标签 LABEL_34（跳转合流点）
      if ( fld_e502 >= 2 )  // 若 fld_e502 >= 2
      {
        if ( nArg22 < 2 )  // 若 nArg22 < 2
        {
          if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
          {
            (*(void (/*thiscall*/ **)(uint32_t *))(*this + 700))(this);  // 调虚槽 +700：读 +6296 槽
            sub_53F720(0);  // 调 批量广播器 vt+84 槽：遍历 +1..+2 vector，vt+80() 活跃者调 vt+84(a2)
            for ( i = 0; i < 17; ++i )  // 循环：i 从 0 递增到 17
            {
              if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, i) != 0 )  // 调虚槽 +776：异常状态查询
              {
                pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 772))(this, i);  // 调虚槽 +772：17 状态槽数组访问（+6228+4*a2）
                (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj2 + 36))(pObj2, 0);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
              }
            }
          }
          return (uint32_t **)sub_698FE0(this + 16);  // 【clock_unfreeze(clk)】
        }
      }
      else if ( nArg22 >= 2 )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*this + 700))(this);  // 调虚槽 +700：读 +6296 槽
          sub_53F720(1);  // 调 批量广播器 vt+84 槽：遍历 +1..+2 vector，vt+80() 活跃者调 vt+84(a2)
          for ( j = 0; j < 17; ++j )  // 循环：j 从 0 递增到 17
          {
            if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, j) != 0 )  // 调虚槽 +776：异常状态查询
            {
              pObj = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 772))(this, j);  // 调虚槽 +772：17 状态槽数组访问（+6228+4*a2）
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 36))(pObj, 1);  // 调虚槽 +36：CNTargetIt__vmt24 目标锁定（102 行：4AED00/47EFD0/605…
            }
          }
        }
        return (uint32_t **)sub_699030(this + 16);  // 【clock_freeze(clk)】
      }
      return result;  // result=this+128 szStatusKeyBuf
    }
    if ( nArg22 >= 1 )  // 若 nArg22 >= 1
      goto LABEL_34;
    if ( *((uint8_t *)this + 212) == 0 && *(this + 30) != 0 )  // 复合条件判定（与/或）
      sub_4939E0(0);  // 播放/暂停级联（递归子链 +204）
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 17) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
    {
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 844))(this);  // 调虚槽 +844：内嵌动作子对象 this+6560
    }
    else  // 否则分支
    {
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*this + 40))(this, 65) == 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
        goto LABEL_32;
      v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 684))(this);  // 调虚槽 +684：取攻击上下文
    }
    sub_698FE0(v11);  // 【clock_unfreeze(clk)】
LABEL_32:  // 标签 LABEL_32（跳转合流点）
    sub_4A0680(0);  // 调 被 CNRDObject_vmtE4（0x49A320）用作子对象全冻的施加点
    sub_698FE0(this + 9);  // 【clock_unfreeze(clk)】
    result = (uint32_t **)*(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
    v12 = *result;  // result=this+128 szStatusKeyBuf
    if ( *result != result )  // result=this+128 szStatusKeyBuf
    {
      do  // do-while 循环体起点
      {
        result = (uint32_t **)sub_4939E0(0);  // 播放/暂停级联（递归子链 +204）
        v12 = (uint32_t *)*v12;
      }
      while ( v12 != (uint32_t *)*(this + 32) );  // 条件循环
    }
    goto LABEL_34;
  }
  return result;  // result=this+128 szStatusKeyBuf
}


// ------------------------------------------------------------
// 0x49A590 sub_49A590
// ------------------------------------------------------------
int /*thiscall*/ sub_49A590(uint32_t *this, int nArg2)  // 实现：★★ 全体时钟换域广播
{
  uint32_t **fld_e32; // eax
  uint32_t *v4; // esi

  *(this + 23) = nArg2;  // this+92〔pFxObjC(推断)〕
  sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  if ( *(this + 30) != 0 )  // this+120〔pAnimObj〕
    sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
  fld_e32 = (uint32_t **)*(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
  v4 = *fld_e32;  // fld_e32=this+128 szStatusKeyBuf
  if ( *fld_e32 != fld_e32 )  // fld_e32=this+128 szStatusKeyBuf
  {
    do  // do-while 循环体起点
    {
      sub_699070(nArg2);  // 【clock_bind_domain(clk, newDomainId)】
      v4 = (uint32_t *)*v4;
    }
    while ( v4 != (uint32_t *)*(this + 32) );  // 条件循环
  }
  return sub_4A0740(nArg2);  // 返回 调 sub_4A0740 返回值
}



// ------------------------------------------------------------
// 0x49A600 sub_49A600
// ------------------------------------------------------------
char /*thiscall*/ sub_49A600(void *this, char pszArg2, int nArg3, int nArg4, int nArg5)  // 实现：★ 玩家脚下光圈渲染钩（101 号资源；150↔255 / 400ms 三角波）
{
  char result; // al
  int pThis_40; // eax
  uint8_t v7; // bl
  int v8; // eax

  result = pszArg2;
  if ( pszArg2 == 0 && ((void *)dword_8F7C08 == this || (void *)dword_8F7C04 == this) )  // 本地玩家对象
  {
    pThis_40 = sub_699000((int)this + 64);  // 【clock_now(clk)】
    v7 = sub_42B420(150, 255, pThis_40, 400);  // 往返插值（三角波）
    sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    v8 = sub_418DD0(101);  // v8 = 调 sub_418DD0 返回值
    sub_424760(dword_79C0B0, nArg3 - 63, nArg4 - 21, v8, 1.0, 1065353216, 0.0, (v7 << 24) | 0xFFFFFF, 0.0, 0.0);  // 【= 图像绘制基元（顶点缓冲 dword_79C0B0 + ARGB）】
    return sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
  }
  return result;
}



// ------------------------------------------------------------
// 0x49A6B0 sub_49A6B0
// ------------------------------------------------------------
void /*thiscall*/ sub_49A6B0(void ***this, void *pArg2)  // 实现：定时器移除（链表摘除 + 释放）
{
  void **fld_e32; // ecx
  void **v4; // eax

  if ( pArg2 != nullptr )  // 若 pArg2 有效（非空）
  {
    fld_e32 = *(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
    v4 = (void **)*fld_e32;  // fld_e32=this+128 szStatusKeyBuf
    if ( *fld_e32 != fld_e32 )  // fld_e32=this+128 szStatusKeyBuf
    {
      while ( v4[3] != pArg2 )  // 条件循环
      {
        v4 = (void **)*v4;
        if ( v4 == fld_e32 )  // 若 v4 == fld_e32
          return;
      }
      if ( v4 != *(this + 32) )  // this+128〔szStatusKeyBuf(推断)〕
      {
        *(uint32_t *)v4[1] = *v4;
        *((uint32_t *)*v4 + 1) = v4[1];
        j__free(v4);  // 调 j__free（堆释放）
        *(this + 33) = (void **)((char *)*(this + 33) - 1);  // this+132〔nAgeTicks〕
      }
    }
  }
}



// ------------------------------------------------------------
// 0x49A720 sub_49A720 —— 元素计数增长 + 溢出抛 length_error（上限 214748364）
//   与 ·sub_498A20 同构（差异：溢出上限为 214748364，异常类型同为 std::length_error）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49A720(uint32_t *this, unsigned int uArg2)  // 实现：元素计数增长 + 溢出抛 length_error（上限 214748364）
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( 214748364 - fld_e2 < uArg2 )  // fld_e2=this+8 nSkillRec8
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x49A7B0 sub_49A7B0
// ------------------------------------------------------------
void /*thiscall*/ sub_49A7B0(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5, char pszArg6, char pszArg7)  // 实现：定时器插入（按触发时刻 a2 有序；触发时调 vt+232 动画复位）
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

  if ( nArg3 != 0 )  // 若 nArg3 非 0
  {
    sub_699070(*(this + 23));  // 【clock_bind_domain(clk, newDomainId)】
    v14[3] = nArg5;
    pszArg72 = pszArg7;
    fld_e32 = (uint32_t **)*(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
    v14[1] = nArg3;
    v9 = *fld_e32;  // fld_e32=this+128 szStatusKeyBuf
    v10 = *fld_e32 == fld_e32;  // fld_e32=this+128 szStatusKeyBuf
    v14[2] = nArg4;
    v14[0] = nArg2;
    pszArg62 = pszArg6;
    if ( !v10 )
    {
      do  // do-while 循环体起点
      {
        if ( v9[2] > nArg2 )
          break;  // 跳出循环/分支
        v9 = (uint32_t *)*v9;
      }
      while ( v9 != fld_e32 );  // 条件循环
    }
    v11 = sub_499C20((int)v9, v9[1], v14);  // 28 字节节点分配（2 入参 + 5 槽拷贝）
    pThis_1F = this + 31;
    v13 = v11;
    sub_49A720(pThis_1F, 1u);  // 元素计数增长 + 溢出抛 length_error（上限 214748364）
    v9[1] = v13;
    *(uint32_t *)v13[1] = v13;
    sub_4926A0(nArg3);  // 帧游标复位（+44 帧数组；递归子链 +204）
  }
}



// ------------------------------------------------------------
// 0x49A850 sub_49A850 —— 主对象析构（204 字节子对象 + 136 链 + 164/168 附属）
//   依次：有临界区时经 vt+56 取句柄做引用释放（·sub_65DF60）；+116 非空走 ·sub_45F1E0；释放 +112 处 204 字节子对象（·sub_499880 + ·sub_657740(...,204)）；
//   把 +144 起指针链逐元素 ·sub_42AF90 + ·sub_657740(...,228) 后 free 并清三指针；
//   最后释放 +164（·sub_4999D0 + free）与 +168（·sub_50E950 + free）两个附属对象。
// ------------------------------------------------------------
void /*thiscall*/ sub_49A850(void *this)  // 实现：主对象析构（204 字节子对象 + 136 链 + 164/168 附属）
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

  if ( lpCriticalSection != nullptr )  // 若 lpCriticalSection 有效（非空）
  {
    pThis_38 = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 56))(this);  // 调虚槽 +56：CNRDCashShopNoDoubleEventConfirmWindow__vmt38 …
    sub_65DF60(pThis_38);  // FSOUND 通道占用清理：以 28 字节步长遍历 10 槽组，比对 nArg2 命中则把 +288 处句柄清零
  }
  if ( *((uint32_t *)this + 29) != 0 )  // this+116〔会话上下文〕
    sub_45F1E0(this);  // 对象注销/退场（递归，含 ELVEN_GATE 检查）
  pThis_1C = *((uint32_t *)this + 28);  // this+112〔pHostComp112〕
  if ( pThis_1C != 0 )  // 若 pThis_1C 非 0
  {
    sub_499880(*((uint32_t *)this + 28));  // 析构序（资源释放 + 虚表回落 IObject）
    sub_657740(pThis_1C, 204);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  pThis_22 = *((void ***)this + 34);  // pThis_22=this+136 演出已播标志
  *((uint32_t *)this + 28) = 0;  // this+112〔pHostComp112〕
  if ( pThis_22 != nullptr )  // 若 pThis_22 有效（非空）
  {
    sub_42AF90(pThis_22);  // 帧对象析构（帧数组 + 元素数组）
    sub_657740(pThis_22, 228);  // 池化结点弹出（写魔术标记后挂入链头）
  }
  *((uint32_t *)this + 34) = 0;  // this[34] = 0
  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    pThis_24 = *((uint32_t *)this + 36);  // this+144〔pFrameList144(推断)〕
    if ( pThis_24 == 0 || i >= (*((uint32_t *)this + 37) - pThis_24) >> 2 )  // 若 pThis_24 == 0
      break;  // 跳出循环/分支
    v7 = 4 * i;
    v8 = *(void ***)(pThis_24 + 4 * i);  // pThis_24=this+144 pFrameList144
    if ( v8 != nullptr )  // 若 v8 有效（非空）
    {
      v11 = v8;
      sub_42AF90(v8);  // 帧对象析构（帧数组 + 元素数组）
      sub_657740(v11, 228);  // 池化结点弹出（写魔术标记后挂入链头）
    }
    *(uint32_t *)(v7 + *((uint32_t *)this + 36)) = 0;  // this+144〔pFrameList144(推断)〕
  }
  if ( *((uint32_t *)this + 36) != 0 )  // this+144〔pFrameList144(推断)〕
    j__free(*((void **)this + 36));  // this+36 物品状态字
  *((uint32_t *)this + 36) = 0;  // this[36] = 0
  *((uint32_t *)this + 37) = 0;  // this[37] = 0
  *((uint32_t *)this + 38) = 0;  // this[38] = 0
  pThis_29 = *((void **)this + 41);  // pThis_29=this+164 第 5 组·+88 增量子倍率
  if ( pThis_29 != nullptr )  // 若 pThis_29 有效（非空）
  {
    sub_4999D0(*((uint32_t *)this + 41));  // 子对象析构序（基类释放 + 虚表回落）
    j__free(pThis_29);  // pThis_29=this+164 第 5 组·+88 增量子倍率
  }
  pThis_2A = *((void **)this + 42);  // pThis_2A=this+168 附属对象向量 begin
  *((uint32_t *)this + 41) = 0;  // this[41] = 0
  if ( pThis_2A != nullptr )  // 若 pThis_2A 有效（非空）
  {
    sub_50E950(pThis_2A);  // 表情气泡双动画件释放
    j__free(pThis_2A);  // pThis_2A=this+168 附属对象向量 begin
  }
  *((uint32_t *)this + 42) = 0;  // this[42] = 0
}



// ------------------------------------------------------------
// 0x49A9A0 sub_49A9A0 —— 四标志清零（内层 +16 与 +8/+73/+74）
//   把 *(*(this+4)+16)、+8、+73、+74 四处标志清零并返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_49A9A0(int this)  // 实现：四标志清零（内层 +16 与 +8/+73/+74）
{
  *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint8_t *)(this + 73) = 0;  // this+73〔szDigitalName(推断)〕等 2 字段
  *(uint8_t *)(this + 74) = 0;  // this+74〔bResetB74(推断)〕等 2 字段
  return 0;
}



// ------------------------------------------------------------
// 0x49A9D0 sub_49A9D0 —— 区间填充（逐 uint32 写同值）
//   把 [uArg1, uArg2) 区间每个 uint32 写成 uArg3 的值，返回尾指针；std::fill 展开。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_49A9D0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *uArg3)  // 实现：区间填充（逐 uint32 写同值）
{
  uint32_t *result; // eax

  for ( result = uArg1; result != uArg2; ++result )  // 循环：result 从 uArg1 递增到 uArg2
    *result = *uArg3;
  return result;
}



// ------------------------------------------------------------
// 0x49A9F0 sub_49A9F0 —— 子项状态批量复位（+12 清零、+16 置 1）
//   把 +28 计数清零后，遍历 +36 起指针链（尾 +40）的每个元素，将其 +12 槽清 0、+16 字节置 1。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49A9F0(uint32_t *this)  // 实现：子项状态批量复位（+12 清零、+16 置 1）
{
  unsigned int i; // edx
  int fld_e9; // esi
  unsigned int result; // eax

  *(this + 7) = 0;  // this+28〔pPanelVec(推断)〕
  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e9 = *(this + 9);  // this+36〔nStateWord36(推断)〕
    if ( fld_e9 == 0 )  // 若 fld_e9 为 0
      break;  // 跳出循环/分支
    result = (*(this + 10) - fld_e9) >> 2;  // this+40〔bStateSub40(推断)〕
    if ( i >= result )  // 若 i >= result
      break;  // 跳出循环/分支
    result = *(uint32_t *)(fld_e9 + 4 * i);  // result=this+40 bStateSub40
    *(uint32_t *)(result + 12) = 0;  // result=this+40 bStateSub40
    *(uint8_t *)(result + 16) = 1;  // result=this+40 bStateSub40
  }
  return result;  // result=this+40 bStateSub40
}



// ------------------------------------------------------------
// 0x49AA30 sub_49AA30 —— 按 int16 键批量置标志（子链匹配 → +16）
//   由 +48 与 +40 两槽算出成员节点地址，遍历其 +36 处的 4 字节元素子链，
//   首字段（int16）等于 nArg2 的元素把 +16 字节置为 pszArg3。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49AA30(uint32_t *this, int nArg2, char pszArg3)  // 实现：按 int16 键批量置标志（子链匹配 → +16）
{
  unsigned int i; // edi
  int fld_e12; // edx
  int v5; // esi
  unsigned int result; // eax

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_e12 = *(this + 12) + 4 * *(this + 10);  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    v5 = *(uint32_t *)(*(uint32_t *)fld_e12 + 36);  // fld_e12=this+48 pCmdVecBegin48
    result = *(uint32_t *)fld_e12 + 32;  // fld_e12=this+48 pCmdVecBegin48
    if ( v5 == 0 )  // 若 v5 为 0
      break;  // 跳出循环/分支
    result = (*(uint32_t *)(*(uint32_t *)fld_e12 + 40) - v5) >> 2;  // fld_e12=this+48 pCmdVecBegin48
    if ( i >= result )  // 若 i >= result
      break;  // 跳出循环/分支
    if ( **(int16_t **)(4 * i + *(uint32_t *)(*(uint32_t *)fld_e12 + 36)) == nArg2 )  // fld_e12=this+48 pCmdVecBegin48
      *(uint8_t *)(*(uint32_t *)(4 * i + *(uint32_t *)(*(uint32_t *)fld_e12 + 36)) + 16) = pszArg3;  // fld_e12=this+48 pCmdVecBegin48
  }
  return result;
}



// ------------------------------------------------------------
// 0x49AA90 sub_49AA90 —— 字符串参数 setter（保存于 +48/+52；未匹配走 off_77F3FC）
// ------------------------------------------------------------
char /*thiscall*/ sub_49AA90(int this, const char *pArg2)  // 实现：字符串参数 setter（保存于 +48/+52；未匹配走 off_77F3FC）
{
  unsigned int i; // edi
  int fld_30; // ecx
  int fld_302; // edx
  int pThis_10; // esi

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_30 = *(uint32_t *)(this + 48);  // fld_30 = 读 this+48
    if ( fld_30 == 0 || i >= (*(uint32_t *)(this + 52) - fld_30) >> 2 )  // 若 fld_30 == 0
      break;  // 跳出循环/分支
    if ( sub_40BF00(*(std::_String_base **)(fld_30 + 4 * i), 0, *(uint32_t *)(*(uint32_t *)(fld_30 + 4 * i) + 20), pArg2, strlen(pArg2)) == 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
    {
      *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 1;  // this+4〔宿主对象〕等 2 字段
      *(uint8_t *)(this + 8) = 1;  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint8_t *)(this + 73) = 0;  // this+73〔szDigitalName(推断)〕等 2 字段
      *(uint8_t *)(this + 74) = 0;  // this+74〔bResetB74(推断)〕等 2 字段
      sub_698F90(this + 60, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      fld_302 = *(uint32_t *)(this + 48);  // fld_302 = 读 this+48
      *(uint32_t *)(this + 40) = i;  // this+40〔bStateSub40(推断)〕等 2 字段
      sub_49A9F0(*(uint32_t **)(fld_302 + 4 * i));  // 子项状态批量复位（+12 清零、+16 置 1）
      return 1;  // 返回 1(成功)
    }
  }
  if ( *(uint32_t *)(this + 36) < 0x10u )  // this+36〔nStateWord36(推断)〕等 2 字段
    pThis_10 = this + 16;
  else  // 否则分支
    pThis_10 = *(uint32_t *)(this + 16);  // pThis_10 = 读 this+16
  off_77F3FC(aErrorS, pThis_10, pArg2);  // 引擎日志输出函数(printf 风格)
  return 0;
}



// ------------------------------------------------------------
// 0x49AB50 sub_49AB50 —— 命令序号推进（clamp 后 vt+12 派发旧/新序号）
//   条目 = (this+48 数组)[this+40]；条目 +28 = 当前命令序号、+36/+40 = 命令节点数组首/尾，
//   序号 +1 并 clamp 到 (尾-首)>>2 后调 vt+12(this, 旧序号, 条目+28 新序号)。
// ------------------------------------------------------------
int /*thiscall*/ sub_49AB50(uint32_t *this)  // 实现：命令序号推进（clamp 后 vt+12 派发旧/新序号）
{
  uint32_t *fld_e12; // edx
  uint32_t *fld_e122; // eax
  int v3; // esi
  int v4; // edi
  unsigned int v5; // edx
  unsigned int v6; // esi

  fld_e12 = *(uint32_t **)(*(this + 12) + 4 * *(this + 10));  // fld_e12 = 读 this+12
  fld_e122 = fld_e12;
  v3 = fld_e12[9];  // v3 = 取 fld_e12[9]
  v4 = fld_e12[7];  // v4 = 取 fld_e12[7]
  if ( v3 != 0 )  // 若 v3 非 0
    v5 = (fld_e12[10] - v3) >> 2;
  else  // 否则分支
    v5 = 0;
  v6 = fld_e122[7] + 1;
  if ( v6 < v5 )  // 若 v6 < v5
    fld_e122[7] = v6;
  return (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 12))(  // 调虚槽 +12：CNRDUpgradeResultWindow__vmtC 播放强化结果：STRENGTHE…
           this,
           v4,
           *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28));  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
}



// ------------------------------------------------------------
// 0x49ABA0 sub_49ABA0 —— 命令驻留计时判定（clock_now - 节点+12 >= 节点+8 则推进）
//   仅当 nArg2 等于条目 +28（当前命令序号）时计时；
//   节点 +12 = 时间戳基准、+8 = 驻留上限【推断】；满期转 ·sub_49AB50 推进。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49ABA0(uint32_t *this, int nArg2)  // 实现：命令驻留计时判定（clock_now - 节点+12 >= 节点+8 则推进）
{
  int fld_e12; // ecx
  int fld_e10; // eax
  int v5; // edx
  unsigned int result; // eax
  int v7; // esi

  fld_e12 = *(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
  fld_e10 = *(this + 10);  // this+40〔bStateSub40(推断)〕
  v5 = *(uint32_t *)(fld_e12 + 4 * fld_e10);  // fld_e12=this+48 pCmdVecBegin48
  result = fld_e12 + 4 * fld_e10;  // fld_e12=this+48 pCmdVecBegin48
  if ( nArg2 == *(uint32_t *)(v5 + 28) )
  {
    v7 = *(uint32_t *)(*(uint32_t *)(v5 + 36) + 4 * nArg2);
    result = sub_699000((int)(this + 15)) - *(uint32_t *)(v7 + 12);  // 【clock_now(clk)】
    if ( result >= *(uint32_t *)(v7 + 8) )
      return sub_49AB50(this);  // 命令序号推进（clamp 后 vt+12 派发旧/新序号）
  }
  return result;
}



// ------------------------------------------------------------
// 0x49ABF0 sub_49ABF0 —— 9 号命令节点·按路径取图落位（资源管理器 vt+60）
//   节点 +20 触发标志为 0 时执行：节点 +32 起 string 为资源路径（容量查 +52），
//   资源管理器 dword_8F84B8 经 vt+60 取图集、节点 +24 为图序号；
//   命中后 vt+152(图, dword_6CB988[+22], dword_6CB990[+22], dword_79C0B0) 落位。
// ------------------------------------------------------------
char /*thiscall*/ sub_49ABF0(uint32_t *this, int nArg2)  // 实现：9 号命令节点·按路径取图落位（资源管理器 vt+60）
{
  int v2; // esi
  int fld_e12; // eax
  int v4; // eax
  uint32_t *v5; // eax

  fld_e12 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * nArg2;  // fld_e12 = 读 this+12
  v2 = *(uint32_t *)fld_e12;
  LOBYTE(fld_e12) = *(uint8_t *)(*(uint32_t *)fld_e12 + 20);
  if ( (uint8_t)fld_e12 == 0 )
  {
    if ( *(uint32_t *)(v2 + 52) < 0x10u )
      v4 = v2 + 32;
    else  // 否则分支
      v4 = *(uint32_t *)(v2 + 32);
    v5 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v4);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    fld_e12 = sub_418DD0(v5, *(uint32_t *)(v2 + 24));  // fld_e12 = 调 sub_418DD0 返回值
    if ( fld_e12 != 0 )  // 若 fld_e12 非 0
      LOBYTE(fld_e12) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e12 + 152))(  // 调虚槽 +152：效果通道 3
                     fld_e12,
                     dword_6CB988[*(int16_t *)(v2 + 22)],
                     dword_6CB990[*(int16_t *)(v2 + 22)],
                     dword_79C0B0);  // 默认字体/绘制资源
  }
  return fld_e12;
}



// ------------------------------------------------------------
// 0x49AC70 sub_49AC70 —— 3..6 号命令节点·横向滑入（sub_4049F0 二次缓动 300ms）
//   节点 +4 类型定起终 x：3 → -宽→0、4 → 0→-宽、5 → 640→640-宽、6 → 640-宽→640，y = 480-图高；
//   图序号取节点 +48（string 路径在 +24）；300ms 二次缓动（sub_4049F0）；
//   节点 +52 == 1 或满 300ms 且仍为当前序号时 ·sub_49AB50 推进。
// ------------------------------------------------------------
int /*thiscall*/ sub_49AC70(uint32_t *this, int nArg2)  // 实现：3..6 号命令节点·横向滑入（sub_4049F0 二次缓动 300ms）
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

  fld_e12 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * nArg2;  // fld_e12 = 读 this+12
  v4 = *(uint32_t *)fld_e12;
  if ( *(uint32_t *)(*(uint32_t *)fld_e12 + 44) < 0x10u )
    v5 = v4 + 24;
  else  // 否则分支
    v5 = *(uint32_t *)(v4 + 24);
  v6 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
  v14 = *(uint32_t *)(sub_418DD0(v6, *(uint32_t *)(v4 + 48)) + 20);  // 调 资源句柄 (101)
  v16 = 0;
  v17 = 0;
  v13 = 480 - *(uint32_t *)(sub_418DD0(v6, *(uint32_t *)(v4 + 48)) + 24);
  pThis_F = sub_699000((int)(this + 15)) - *(uint32_t *)(v4 + 12);  // 【clock_now(clk)】
  switch ( *(uint32_t *)(v4 + 4) )  // 按 *(uint32_t *)(v4 + 4) 分派
  {
    case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
      v16 = -v14;
      v17 = 0;
      break;  // 跳出循环/分支
    case 4:  // case 4 = ENUM_CMDPACKET_EXIT
      v16 = 0;
      v17 = -v14;
      break;  // 跳出循环/分支
    case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
      v16 = 640;
      v17 = 640 - v14;
      break;  // 跳出循环/分支
    case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
      v16 = 640 - v14;
      v17 = 640;
      break;  // 跳出循环/分支
    default:  // 默认分支
      break;  // 跳出循环/分支
  }
  v11 = (float)v17;
  v10 = (float)v16;
  v15 = (uint64_t)sub_4049F0(v10, v11, pThis_F, 300, 1);  // 二次抛物线缓动变体（按 t 在  上的加速差项计算，pszArg5 控制正反方向）
  pObj = sub_418DD0(v6, *(uint32_t *)(v4 + 48));  // pObj = 调 sub_418DD0 返回值
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, v15, v13, dword_79C0B0);  // 调虚槽 +152：效果通道 3
  result = nArg2;
  if ( *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28) == nArg2 && (*(uint8_t *)(v4 + 52) == 1 || pThis_F >= 300) )  // 若 pThis_F >= 300
    return sub_49AB50(this);  // 命令序号推进（clamp 后 vt+12 派发旧/新序号）
  return result;
}



// ------------------------------------------------------------
// 0x49ADF0 sub_49ADF0 —— 7/8 号命令节点·透明度渐变（sub_4049C0 线性 300ms）
//   7 = 0→255 淡入、8 = 255→0 淡出；图序号取节点 +48；
//   Alpha 取插值结果高字节 ((v16<<24)|0xFFFFFF)，vt+128 十参绘制于 (0,397)；
//   节点 +52 == 1 或满 300ms 且为当前序号时推进。
// ------------------------------------------------------------
int /*thiscall*/ sub_49ADF0(uint32_t *this, int nArg2)  // 实现：7/8 号命令节点·透明度渐变（sub_4049C0 线性 300ms）
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

  fld_e12 = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 36) + 4 * nArg2;  // fld_e12 = 读 this+12
  v4 = *(uint32_t *)fld_e12;
  if ( *(uint32_t *)(*(uint32_t *)fld_e12 + 44) < 0x10u )
    v5 = v4 + 24;
  else  // 否则分支
    v5 = *(uint32_t *)(v4 + 24);
  v14 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v5);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
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
  pObj = sub_418DD0(v14, *(uint32_t *)(v4 + 48));  // pObj = 调 sub_418DD0 返回值
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      pObj,
      0,
      397,
      dword_79C0B0,  // 默认字体/绘制资源
      1065353216,
      1065353216,
      0,
      ((uint8_t)v16 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  fld_e10 = *(this + 10);  // this+40〔bStateSub40(推断)〕
  fld_e122 = *(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
  v10 = *(uint32_t *)(fld_e122 + 4 * fld_e10);  // fld_e122=this+48 pCmdVecBegin48
  result = fld_e122 + 4 * fld_e10;  // fld_e122=this+48 pCmdVecBegin48
  if ( *(uint32_t *)(v10 + 28) == nArg2 && (*(uint8_t *)(v4 + 52) == 1 || pThis_F >= 300) )  // 若 pThis_F >= 300
    return sub_49AB50(this);  // 命令序号推进（clamp 后 vt+12 派发旧/新序号）
  return result;
}



// ------------------------------------------------------------
// 0x49AF20 sub_49AF20 —— 9 号节点·两位数拆分绘制（个位/十位各取一图）
//   遍历启用（+16 非 0）且类型 9、int16 参数（+22）为 0 的节点；数值取自 this+88；
//   值 >= 10 时画 个位 (v9%10+2) 与 十位 (v9/10+2) 两张（dword_6CB988 表 +43/+31 列偏移），
//   否则单张 (v9+2)。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49AF20(uint32_t *this)  // 实现：9 号节点·两位数拆分绘制（个位/十位各取一图）
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
  do  // do-while 循环体起点
  {
    pObj4 = pThis[12] + 4 * pThis[10];
    v4 = *(uint32_t *)(*(uint32_t *)pObj4 + 36);
    result = *(uint32_t *)pObj4 + 32;
    if ( v4 == 0 )  // 若 v4 为 0
      break;  // 跳出循环/分支
    result = (*(uint32_t *)(*(uint32_t *)pObj4 + 40) - v4) >> 2;
    if ( v2 >= result )  // 若 v2 >= result
      break;  // 跳出循环/分支
    if ( *(uint8_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)pObj4 + 36)) + 16) != 0
      && *(uint32_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)pObj4 + 36)) + 4) == 9 )  // 9 号节点·两位数拆分绘制（个位/十位各取一图）
    {
      v6 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)pObj4 + 36) + 4 * v2);
      if ( *(uint16_t *)(v6 + 22) == 0 && (int)pThis[22] > -1 )  // 复合条件判定（与/或）
      {
        if ( *(uint32_t *)(v6 + 52) < 0x10u )
          v7 = v6 + 32;
        else  // 否则分支
          v7 = *(uint32_t *)(v6 + 32);
        v8 = (uint32_t *)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F84B8 + 60))(dword_8F84B8, v7);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
        v9 = pThis[22];  // v9 = 取 pThis[22]
        if ( v9 >= 10 )  // 若 v9 >= 10
        {
          pObj2 = sub_418DD0(v8, v9 % 10 + 2);  // pObj2 = 调 sub_418DD0 返回值
          if ( pObj2 != 0 )  // 若 pObj2 非 0
          {
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(  // 调虚槽 +152：效果通道 3
              pObj2,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 43,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);  // 默认字体/绘制资源
            pThis = this;
          }
          pObj = sub_418DD0(v8, pThis[22] / 10 + 2);  // pObj = 调 sub_418DD0 返回值
          if ( pObj != 0 )  // 若 pObj 非 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(  // 调虚槽 +152：效果通道 3
              pObj,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 31,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);  // 默认字体/绘制资源
        }
        else  // 否则分支
        {
          pObj3 = sub_418DD0(v8, v9 + 2);  // pObj3 = 调 sub_418DD0 返回值
          if ( pObj3 != 0 )  // 若 pObj3 非 0
            (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(  // 调虚槽 +152：效果通道 3
              pObj3,
              dword_6CB988[*(int16_t *)(v6 + 22)] + 43,
              dword_6CB990[*(int16_t *)(v6 + 22)],
              dword_79C0B0);  // 默认字体/绘制资源
        }
      }
    }
    result = *(uint32_t *)(*(uint32_t *)(pThis[12] + 4 * pThis[10]) + 28);
    v2 = ++v14;
  }
  while ( v14 <= result );  // 条件循环
  return result;
}



// ------------------------------------------------------------
// 0x49B0C0 sub_49B0C0 —— 说话人条目析构（清内部：命令数组 + 名字 string）
//   +36..+44 指针数组逐项 j__free 并清槽后释放数组本体；
//   名字 string 按 +24 容量判定（>= 0x10 才 free），复位为空串（+20=0 / +24=15 / +4=0）。
// ------------------------------------------------------------
void /*thiscall*/ sub_49B0C0(int this)  // 实现：说话人条目析构（清内部：命令数组 + 名字 string）
{
  unsigned int i; // ebx
  int fld_24; // ecx
  int v4; // edi
  void *v5; // ecx

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_24 = *(uint32_t *)(this + 36);  // fld_24 = 读 this+36
    if ( fld_24 == 0 || i >= (*(uint32_t *)(this + 40) - fld_24) >> 2 )  // 若 fld_24 == 0
      break;  // 跳出循环/分支
    v4 = 4 * i;
    v5 = *(void **)(fld_24 + 4 * i);  // fld_24=this+36 物品状态字
    if ( v5 != nullptr )  // 若 v5 有效（非空）
      j__free(v5);  // 调 j__free（堆释放）
    *(uint32_t *)(v4 + *(uint32_t *)(this + 36)) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
  }
  if ( *(uint32_t *)(this + 36) != 0 )  // this+36〔nStateWord36(推断)〕等 2 字段
    j__free(*(void **)(this + 36));  // 释放 this+36〔nStateWord36(推断)〕堆块
  *(uint32_t *)(this + 36) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 24) >= 0x10u )  // this+24〔nPageMax(推断)〕等 2 字段
    j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
  *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
}



// ------------------------------------------------------------
// 0x49B150 sub_49B150 —— 子控件构造与宿主回指（IControl + MoveWindow(0,0) + 控件+68=this）
//   new(0x68) → sub_426BD0（IControl 构造）；控件 +28/+32 清零、
//   sub_69A5F0(控件, 0, 0)（MoveWindow 归零）、控件 +68 记录宿主 this。
// ------------------------------------------------------------
int /*thiscall*/ sub_49B150(uint32_t *this)  // 实现：子控件构造与宿主回指（IControl + MoveWindow(0,0) + 控件+68=this）
{
  uint8_t *pMem; // eax
  uint8_t *v3; // eax
  int result; // eax

  pMem = operator new(0x68u);  // new(104 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v3 = sub_426BD0(pMem);  // nengine::IControl 构造
  else  // 否则分支
    v3 = nullptr;  // v3 = 空指针
  *(this + 1) = v3;  // this+4〔宿主对象〕
  *((uint32_t *)v3 + 7) = 0;  // v3[7] = 0
  *((uint32_t *)v3 + 8) = 0;  // v3[8] = 0
  sub_69A5F0((uint32_t *)*(this + 1), 0, 0);  // 调 设位、sub_69A840 登记
  result = *(this + 1);  // this+4〔宿主对象〕
  *(uint32_t *)(result + 68) = this;  // result=this+4 宿主对象
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x49B1D0 sub_49B1D0 —— 图层属性四连（sub_49ABA0/49AC70/49ADF0/49ABF0）
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B1D0(uint32_t *this)  // 实现：图层属性四连（sub_49ABA0/49AC70/49ADF0/49ABF0）
{
  unsigned int v2; // edi
  int fld_e12; // ecx
  int v4; // edx
  unsigned int result; // eax

  v2 = 0;
  do  // do-while 循环体起点
  {
    fld_e12 = *(this + 12) + 4 * *(this + 10);  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    v4 = *(uint32_t *)(*(uint32_t *)fld_e12 + 36);  // fld_e12=this+48 pCmdVecBegin48
    result = *(uint32_t *)fld_e12 + 32;  // fld_e12=this+48 pCmdVecBegin48
    if ( v4 == 0 )  // 若 v4 为 0
      break;  // 跳出循环/分支
    result = (*(uint32_t *)(*(uint32_t *)fld_e12 + 40) - v4) >> 2;  // fld_e12=this+48 pCmdVecBegin48
    if ( v2 >= result )  // 若 v2 >= result
      break;  // 跳出循环/分支
    if ( *(uint8_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)fld_e12 + 36)) + 16) != 0 )  // fld_e12=this+48 pCmdVecBegin48
    {
      switch ( *(uint32_t *)(*(uint32_t *)(4 * v2 + *(uint32_t *)(*(uint32_t *)fld_e12 + 36)) + 4) )  // 按 *(uint32_t *)(*(uint32_t *)(4 … 分派
      {
        case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
          sub_49ABA0(this, v2);  // 命令驻留计时判定（clock_now - 节点+12 >= 节点+8 则推进）
          break;  // 跳出循环/分支
        case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
        case 4:  // case 4 = ENUM_CMDPACKET_EXIT
        case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
        case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
          sub_49AC70(this, v2);  // 3..6 号命令节点·横向滑入（sub_4049F0 二次缓动 300ms）
          break;  // 跳出循环/分支
        case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
        case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
          sub_49ADF0(this, v2);  // 7/8 号命令节点·透明度渐变（sub_4049C0 线性 300ms）
          break;  // 跳出循环/分支
        case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
          sub_49ABF0(this, v2);  // 9 号命令节点·按路径取图落位（资源管理器 vt+60）
          break;  // 跳出循环/分支
        default:  // 默认分支
          break;  // 跳出循环/分支
      }
    }
    result = *(uint32_t *)(*(uint32_t *)(*(this + 12) + 4 * *(this + 10)) + 28);  // result = 读 this+12
    ++v2;
  }
  while ( v2 <= result );  // 条件循环
  return result;
}



// ------------------------------------------------------------
// 0x49B290 sub_49B290 —— 命令节点时钟写入与命令分派（0/9 推进、1 清标志、10/11 置标志）
//   节点 = 条目(this+48 数组第 this+40 项) 的 +36 命令数组第 nArg3 项；节点 +12 写 clock_now(this+60)；
//   节点 +4 命令枚举：0/9 → ·sub_49AB50 推进；1 → 清 (this+4 子控件)+16、this+8、this+73/74；
//   10/11 → ·sub_49AA30 以节点 +8 int16 键批量置标志 0/1 后推进。
// ------------------------------------------------------------
char /*thiscall*/ sub_49B290(int this, int nArg2, int nArg3)  // 实现：命令节点时钟写入与命令分派（0/9 推进、1 清标志、10/11 置标志）
{
  int pThis_3C; // ebx
  uint32_t *fld_30; // edi
  int v6; // eax

  pThis_3C = this + 60;
  fld_30 = *(uint32_t **)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 48) + 4 * *(uint32_t *)(this + 40)) + 36) + 4 * nArg3);  // fld_30 = 读 this+48
  fld_30[3] = sub_699000(this + 60);  // 【clock_now(clk)】
  v6 = fld_30[1];  // v6 = 取 fld_30[1]
  switch ( v6 )  // 按 v6 分派
  {
    case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
    case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
      goto LABEL_5;
    case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
      *(uint8_t *)(*(uint32_t *)(this + 4) + 16) = 0;  // this+4〔宿主对象〕等 2 字段
      *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint8_t *)(pThis_3C + 13) = 0;  // pThis_3C=this+60 fade 值
      *(uint8_t *)(pThis_3C + 14) = 0;  // pThis_3C=this+60 fade 值
      LOBYTE(v6) = 0;
      return v6;
    case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
      sub_49AA30((uint32_t *)this, fld_30[2], 0);  // 按 int16 键批量置标志（子链匹配 → +16）
      goto LABEL_5;
    case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
      sub_49AA30((uint32_t *)this, fld_30[2], 1);  // 按 int16 键批量置标志（子链匹配 → +16）
LABEL_5:  // 标签 LABEL_5（跳转合流点）
      LOBYTE(v6) = sub_49AB50((uint32_t *)this);  // 命令序号推进（clamp 后 vt+12 派发旧/新序号）
      break;  // 跳出循环/分支
    default:  // 默认分支
      return v6;
  }
  return v6;
}



// ------------------------------------------------------------
// 0x49B330 sub_49B330 —— 命令分派包装（第 2 槽当前序号 == 9 时 this+88 置 -1）
//   转调 ·sub_49B290；当 this+40 槽号 == 1 且第 2 槽条目 +28 当前序号为 9 时清零 this+88。
// ------------------------------------------------------------
char /*thiscall*/ sub_49B330(uint32_t *this, int nArg2, int nArg3)  // 实现：命令分派包装（第 2 槽当前序号 == 9 时 this+88 置 -1）
{
  char result; // al
  int fld_e12; // eax  | +0x0030 → 命令节点向量 begin（CNRDWarRoomBattleTalkBox；va=0049B570）
  int v6; // edx

  result = sub_49B290((int)this, nArg2, nArg3);  // 命令节点时钟写入与命令分派（0/9 推进、1 清标志、10/11 置标志）
  if ( *(this + 10) == 1 )  // this+40〔bStateSub40(推断)〕
  {
    fld_e12 = *(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
    v6 = *(uint32_t *)(fld_e12 + 4);  // fld_e12=this+48 pCmdVecBegin48
    result = fld_e12 + 4;
    if ( *(uint32_t *)(v6 + 28) == 9 )
      *(this + 22) = -1;  // this+88〔pFxObjB(推断)〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x49B370 sub_49B370 —— 对象析构（子控件 vt+4(1) + 条目数组逐项 ·sub_49B0C0/j__free）
//   先销毁 this+4 处子控件（vt+4(1)）并置 0；
//   再遍历 this+48..+52 条目数组：每项 ·sub_49B0C0 清内部后 j__free，槽位置 0。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B370(uint32_t *this)  // 实现：对象析构（子控件 vt+4(1) + 条目数组逐项 ·sub_49B0C0/j__free）
{
  int (/*thiscall*/ ***fld_e1)(uint32_t, int); // ecx
  unsigned int v3; // ebx
  unsigned int result; // eax
  int fld_e12; // ecx
  int v6; // ecx
  void *Block; // [esp+Ch] [ebp-4h]

  fld_e1 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 1);  // this+4〔宿主对象〕
  v3 = 0;
  if ( fld_e1 != nullptr )  // 若 fld_e1 有效（非空）
    result = (**fld_e1)(fld_e1, 1);  // 调 fld_e1 的虚函数（vt+0）
  *(this + 1) = 0;  // this+4〔宿主对象〕
  while ( 1 )  // 条件循环
  {
    fld_e12 = *(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
    if ( fld_e12 == 0 )  // 若 fld_e12 为 0
      break;  // 跳出循环/分支
    result = (*(this + 13) - fld_e12) >> 2;  // this+52〔bAuraState(推断)〕
    if ( v3 >= result )  // 若 v3 >= result
      break;  // 跳出循环/分支
    v6 = *(uint32_t *)(4 * v3 + fld_e12);  // fld_e12=this+48 pCmdVecBegin48
    if ( v6 != 0 )  // 若 v6 非 0
    {
      Block = (void *)v6;
      sub_49B0C0(v6);  // 说话人条目析构（清内部：命令数组 + 名字 string）
      j__free(Block);  // 调 j__free（堆释放）
    }
    result = 4 * v3 + *(this + 12);
    *(uint32_t *)result = 0;  // *result = 0
    ++v3;
  }
  return result;  // result=this+52 bAuraState
}



// ------------------------------------------------------------
// 0x49B3F0 sub_49B3F0 —— 对象 tick 触发（参数命中 +4 且 +8 标志置位 → 图层四连 + vt+8）
//   参数 == this+4 且 this+8 标志非 0 时，先 ·sub_49B1D0 驱动全部图层属性节点，
//   再走本对象 vt+8（帧/命令后续）。
// ------------------------------------------------------------
char /*thiscall*/ sub_49B3F0(int this, int nArg2)  // 实现：对象 tick 触发（参数命中 +4 且 +8 标志置位 → 图层四连 + vt+8）
{
  char result; // al

  result = nArg2;
  if ( nArg2 == *(uint32_t *)(this + 4) )  // this+4〔宿主对象〕等 2 字段
  {
    result = *(uint8_t *)(this + 8);  // result = 读 this+8
    if ( result != 0 )  // 若结果非 0（成功）
    {
      sub_49B1D0((uint32_t *)this);  // 图层属性四连（sub_49ABA0/49AC70/49ADF0/49ABF0）
      return (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 8))(this);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    }
  }
  return result;  // result=this+8 bTickEnable8
}



// ------------------------------------------------------------
// 0x49B420 sub_49B420 —— [img] 命令节点构造（0x14 字节，路径 string 在 +32）
//   +0 = -1、+4 = 9、+8 = -1、+12 = 0、+16 = 1、+20 = 255、+22 = 0、+24 = 0；
//   +32 起内嵌 string（长度 +48 / 容量 +52，sub_4015C0 置空串）；
//   与 ·sub_49B4A0（0x38 字节命令节点）分路，节点字段与 88 字节帧结构无对应关系。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49B420(uint32_t *this, int nArg2, int nArg3)  // 实现：命令节点构造（0x14 字节，路径 string 在 +32）
{
  char *pThis_7; // ecx

  *(this + 1) = nArg3;  // this+4〔宿主对象〕
  pThis_7 = (char *)(this + 7);  // this+7〔uPathTerm(推断)〕等 2 字段
  *(uint16_t *)this = -1;  // *this = -1
  *(this + 2) = -1;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  *((uint8_t *)this + 16) = 1;  // this[16] = 1
  *((uint32_t *)pThis_7 + 6) = 15;  // pThis_7=this+7 uPathTerm
  *((uint32_t *)pThis_7 + 5) = 0;  // pThis_7[5] = 0
  pThis_7[4] = 0;  // pThis_7=this+7 uPathTerm
  *((uint8_t *)this + 20) = -1;  // this[20] = -1
  *((uint16_t *)this + 11) = 0;  // this[11] = 0
  *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
  sub_4015C0((size_t *)pThis_7, szPassword, 0);  // 【std::string构造赋值】
  return this;
}



// ------------------------------------------------------------
// 0x49B4A0 sub_49B4A0 —— 命令节点构造·0x38 变体（string +24、+48 参数、+52 标志）
//   +0 = -1、+4 = 命令枚举、+8 = -1、+12 = 0、+16 = 1；
//   +24 起内嵌 string（长度 +40 / 容量 +44 初始 15）；
//   +48 与 +52 由调用者填参数与标志（与 88 字节帧 [DELAY]/[DAMAGE TYPE] 同偏移但不同域）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49B4A0(uint32_t *this, int nArg2, int nArg3)  // 实现：命令节点构造·0x38 变体（string +24、+48 参数、+52 标志）
{
  char *pThis_5; // ecx

  pThis_5 = (char *)(this + 5);  // this+20〔nPage(推断)〕
  *(uint16_t *)this = -1;  // *this = -1
  *(this + 1) = nArg3;  // this+4〔宿主对象〕
  *(this + 2) = -1;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  *((uint8_t *)this + 16) = 1;  // this[16] = 1
  *((uint32_t *)pThis_5 + 6) = 15;  // pThis_5=this+20 nPage
  *((uint32_t *)pThis_5 + 5) = 0;  // pThis_5[5] = 0
  pThis_5[4] = 0;  // pThis_5=this+20 nPage
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  *(this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *((uint8_t *)this + 52) = 0;  // this[52] = 0
  return this;
}



// ------------------------------------------------------------
// 0x49B520 sub_49B520 —— 帧字段读组（+40/+48/+52/+56 → 打包返回）
// ------------------------------------------------------------
size_t */*thiscall*/ sub_49B520(int this)  // 实现：帧字段读组（+40/+48/+52/+56 → 打包返回）
{
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = -1;  // this+40〔bStateSub40(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 48) != 0 )  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    j__free(*(void **)(this + 48));  // 释放 this+48〔pCmdVecBegin48(推断)〕堆块
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint8_t *)(this + 73) = 0;  // this+73〔szDigitalName(推断)〕等 2 字段
  *(uint8_t *)(this + 74) = 0;  // this+74〔bResetB74(推断)〕等 2 字段
  return sub_4015C0((size_t *)(this + 12), szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x49B570 sub_49B570 —— 帧字段读组·变体（+48/+52 + 盒 +56 + 特效 +40）
// ------------------------------------------------------------
size_t */*thiscall*/ sub_49B570(int this)  // 实现：帧字段读组·变体（+48/+52 + 盒 +56 + 特效 +40）
{
  unsigned int i; // ebx
  int fld_30; // ecx  | +0x0030 → 命令节点向量 begin（CNRDCharacterTalkBox；va=0049B570）
  int v4; // ecx
  void *Block; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )  // 无限循环：i 从 0 递增
  {
    fld_30 = *(uint32_t *)(this + 48);  // fld_30 = 读 this+48
    if ( fld_30 == 0 || i >= (*(uint32_t *)(this + 52) - fld_30) >> 2 )  // 若 fld_30 == 0
      break;  // 跳出循环/分支
    v4 = *(uint32_t *)(fld_30 + 4 * i);  // fld_30=this+48 pCmdVecBegin48
    if ( v4 != 0 )  // 若 v4 非 0
    {
      Block = (void *)v4;
      sub_49B0C0(v4);  // 说话人条目析构（清内部：命令数组 + 名字 string）
      j__free(Block);  // 调 j__free（堆释放）
    }
    *(uint32_t *)(4 * i + *(uint32_t *)(this + 48)) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  }
  if ( *(uint32_t *)(this + 48) != 0 )  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    j__free(*(void **)(this + 48));  // 释放 this+48〔pCmdVecBegin48(推断)〕堆块
  *(uint32_t *)(this + 48) = 0;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint8_t *)(this + 8) = 0;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = -1;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint8_t *)(this + 73) = 0;  // this+73〔szDigitalName(推断)〕等 2 字段
  *(uint8_t *)(this + 74) = 0;  // this+74〔bResetB74(推断)〕等 2 字段
  return sub_4015C0((size_t *)(this + 12), szPassword, 0);  // 【std::string构造赋值】
}



// ------------------------------------------------------------
// 0x49B610 sub_49B610 —— vector 越界异常抛掷（vector<T> too long / length_error）
//   构造 std::length_error 文案并 _CxxThrowException；
//   被 ·sub_49B680 在 0x3FFFFFFF - 已有容量 < 追加量时调用。
// ------------------------------------------------------------
void /*noreturn*/ sub_49B610()  // 实现：vector 越界异常抛掷（vector<T> too long / length_error）
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
  sub_401740(pExceptionObject, &v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x49B680 sub_49B680 —— 指针数组插入/扩容专用路径（容量足后移，不足 1.5 倍重建）
//   容器 +4 首 / +8 尾 / +12 容量；容量不足时新容量 = 容量 + 容量/2（0x3FFFFFFF 上限），
//   再取 max(需求) 后 operator new 重建；中段用 sub_55E7F0 搬移、sub_49A9D0 填充新格；
//   由 ·sub_49B8E0 在尾插时以 (尾指针, 1, 值) 调用。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B680(int this, uint32_t *Src, unsigned int uArg3, int *pDwArg4)  // 实现：指针数组插入/扩容专用路径（容量足后移，不足 1.5 倍重建）
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

  fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )  // 若 fld_4 非 0
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;  // this+12〔nSkillRec12(推断)〕等 2 字段
  else  // 否则分支
    result = 0;  // result=this+12 nSkillRec12
  if ( uArg3 != 0 )  // 若 uArg3 非 0
  {
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_8 = 0;  // fld_8=this+8 nSkillRec8
    if ( 0x3FFFFFFF - fld_8 < uArg3 )  // fld_8=this+8 nSkillRec8
      sub_49B610(this);  // vector 越界异常抛掷（vector<T> too long / length_error）
    if ( fld_4 != 0 )  // 若 fld_4 非 0
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
    else  // 否则分支
      fld_82 = 0;  // fld_82=this+8 nSkillRec8
    if ( result >= uArg3 + fld_82 )  // result=this+12 nSkillRec12
    {
      fld_83 = *(uint8_t **)(this + 8);  // fld_83 = 读 this+8
      v21 = (fld_83 - (uint8_t *)Src) >> 2;  // fld_83=this+8 物品 id
      v22 = 4 * uArg3;
      v29 = (int)fld_83;  // fld_83=this+8 物品 id
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )  // 若 v21 >= uArg3
      {
        v24 = (int)&fld_83[-v22];  // fld_83=this+8 物品 id
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);  // 商城状态（10 行）
        sub_5DAF70(Src, v24, v29);  // 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
        return (unsigned int)sub_49A9D0(Src, &Srca[(uint32_t)Src], &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
      else  // 否则分支
      {
        sub_55E7F0(Src, (int)fld_83, &Src[v22 / 4u]);  // 商城状态（10 行）
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - (int)Src) >> 2), &pDwArg4);  // 调 填充补足尾段
        fld_84 = &Srca[*(uint32_t *)(this + 8)];  // this+8〔nSkillRec8(推断)〕等 2 字段
        *(uint32_t *)(this + 8) = fld_84;  // this+8〔nSkillRec8(推断)〕等 2 字段
        return (unsigned int)sub_49A9D0(Src, (uint32_t *)(fld_84 - Srca), &pDwArg4);  // 区间填充（逐 uint32 写同值）
      }
    }
    else  // 否则分支
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )  // result=this+12 nSkillRec12
        v10 = (result >> 1) + result;  // result=this+12 nSkillRec12
      else  // 否则分支
        v10 = 0;
      if ( fld_4 != 0 )  // 若 fld_4 非 0
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_85 = 0;  // fld_85=this+8 nSkillRec8
      if ( v10 < uArg3 + fld_85 )  // fld_85=this+8 nSkillRec8
      {
        if ( fld_4 != 0 )  // 若 fld_4 非 0
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
        else  // 否则分支
          fld_86 = 0;  // fld_86=this+8 nSkillRec8
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * (((int)Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);  // this+16〔nChannelTypeSel(推断)〕
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);  // v15 = 调 sub_523700 返回值
      memcpy_0(v15, Src, 4 * ((*(uint32_t *)(this + 8) - (int)Src) >> 2));  // this+8〔nSkillRec8(推断)〕等 2 字段
      fld_43 = *(uint32_t *)(this + 4);  // fld_43 = 读 this+4
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;  // this+8〔nSkillRec8(推断)〕等 2 字段
      else  // 否则分支
        fld_87 = 0;  // fld_87=this+8 nSkillRec8
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )  // 若 fld_43 非 0
        j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
      *(uint32_t *)(this + 12) = &pMem[v28];  // this+12〔nSkillRec12(推断)〕等 2 字段
      *(uint32_t *)(this + 8) = &pMem[4 * v18];  // this+8〔nSkillRec8(推断)〕等 2 字段
      *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
      return (unsigned int)pMem;
    }
  }
  return result;  // result=this+12 nSkillRec12
}



// ============================================================
// §M 0x49B860-0x49BE70  对话脚本解析器 sub_49B930 + COUNT_DOWN
// ============================================================
// ------------------------------------------------------------
// 0x49B860 sub_49B860 —— 说话人条目构造（0x30：名字 string +4/+20/+24 + 命令数组 +36..+44）
//   名字 string 置空串（+20 = 0、+24 = 15、+4 = 0），+28 字段清零；
//   +36..+44 命令节点数组指针复位为 0；随后由 ·sub_49B930 的 [commands] 段填充。
// ------------------------------------------------------------
int /*thiscall*/ sub_49B860(int this)  // 实现：说话人条目构造（0x30：名字 string +4/+20/+24 + 命令数组 +36..+44）
{
  *(uint32_t *)(this + 24) = 15;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  *(uint8_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 36) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  sub_4015C0((size_t *)this, szPassword, 0);  // 【std::string构造赋值】
  *(uint32_t *)(this + 28) = 0;  // this+28〔pPanelVec(推断)〕等 2 字段
  if ( *(uint32_t *)(this + 36) != 0 )  // this+36〔nStateWord36(推断)〕等 2 字段
    j__free(*(void **)(this + 36));  // 释放 this+36〔nStateWord36(推断)〕堆块
  *(uint32_t *)(this + 36) = 0;  // this+36〔nStateWord36(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = 0;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  return this;
}



// ------------------------------------------------------------
// 0x49B8E0 sub_49B8E0 —— 条目数组尾插（容量足直接写尾，满则 ·sub_49B680 扩容）
//   +4 首 / +8 尾 / +12 容量；尾指针写值后 +8 前移；
//   未分配或 size >= 容量时转 ·sub_49B680(尾指针, 1, &值) 走扩容路径。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49B8E0(int **this, int *pDwArg2)  // 实现：条目数组尾插（容量足直接写尾，满则 ·sub_49B680 扩容）
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = (int)*(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != 0 )  // 若 fld_e1 非 0
    fld_e2 = ((int)*(this + 2) - fld_e1) >> 2;  // this+8〔nSkillRec8(推断)〕
  else  // 否则分支
    fld_e2 = 0;  // fld_e2=this+8 nSkillRec8
  if ( fld_e1 == 0 || fld_e2 >= ((int)*(this + 3) - fld_e1) >> 2 )  // 若 fld_e1 == 0
    return sub_49B680((int)this, *(this + 2), 1u, pDwArg2);  // 指针数组插入/扩容专用路径（容量足后移，不足 1.5 倍重建）
  fld_e22 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  *fld_e22 = *pDwArg2;  // fld_e22=this+8 nSkillRec8
  result = (unsigned int)(fld_e22 + 1);  // fld_e22=this+8 nSkillRec8
  *(this + 2) = (int *)result;  // this+8〔nSkillRec8(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x49B930 sub_49B930 —— ★对话脚本解析器
//   [talk name]→说话人条目(0x30B 节点+字符串)；[commands]→命令序列：off_790B94 命令表
//   12 条，0/1→0x14B 节点；2/10/11→0x14B+参数；3..8→0x38B 节点(+48 参数、+52
//   [pass next command] 标志)；9→[img] 图像节点(+20/+22/+24)。
//   注意：节点 +48/+52 是对话命令字段，与 88B 帧结构的 DELAY/DAMAGE TYPE 无关。
// ------------------------------------------------------------
char /*thiscall*/ sub_49B930(uint32_t *this, void *ArgList)  // 实现：对话脚本解析器
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
  dword_796E502 = dword_796E50;  // dword_796E50（栈检 cookie 值）
  if ( (uint8_t)sub_442A10((char)szPassword, (int)ArgList) != 0 )  // 脚本载入调度（PVF 或磁盘）
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 4))(this);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
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
    fld_e13 = nullptr;  // fld_e13 = 空指针
    while ( (uint8_t)sub_443430(v18) != 0 )  // 读 token 到 string + 国家码标记
    {
      sub_442BC0(v18);  // 国家码标签配对校验（bool）
      if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[talk name]", 0xBu) != 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
      {
        if ( sub_40BF00((std::_String_base *)v18, 0, v20, "[commands]", 0xAu) == 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
        {
          HIBYTE(ArgList) = 0;
          for ( i = sub_4423D0((uint8_t *)&ArgList + 3); HIBYTE(ArgList) != 0; i = sub_4423D0((uint8_t *)&ArgList + 3) )  // 遍历循环
          {
            sub_443370();  // 脚本 token 取串（第三入口）
            for ( j = 0; j < 12; ++j )  // 循环：j 从 0 递增到 12
            {
              if ( sub_40BF00((std::_String_base *)v26, 0, v28, off_790B94[j], strlen(off_790B94[j])) == 0 )  // std::string 比较（memcmp + 长度序；越界走 _Xran）
              {
                switch ( j )  // 按 j 分派
                {
                  case 0:  // case 0 = ENUM_CMDPACKET_CHECK_CONNECTION
                  case 1:  // case 1 = ENUM_CMDPACKET_CHECK_CONNECTION
                    pMem = operator new(0x14u);  // new(20 字节) 分配对象
                    if ( pMem != nullptr )  // 若 pMem 有效（非空）
                    {
                      *(uint16_t *)pMem = -1;  // *pMem = -1
                      pMem[1] = j;
                      pMem[2] = -1;
                      pMem[3] = 0;
                      *((uint8_t *)pMem + 16) = 1;  // pMem[16] = 1
                      pMem3 = pMem;
                    }
                    else  // 否则分支
                    {
                      pMem3 = nullptr;  // pMem3 = 空指针
                    }
                    goto LABEL_33;
                  case 2:  // case 2 = ENUM_CMDPACKET_LOGIN
                  case 10:  // case 10 = ENUM_CMDPACKET_RECOVER_STAMINA
                  case 11:  // case 11 = ENUM_CMDPACKET_REQUEST_PEER
                    v11 = sub_4423D0(nullptr);  // v11 = 调 sub_4423D0 返回值
                    pMem2 = operator new(0x14u);  // new(20 字节) 分配对象
                    if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
                    {
                      *(uint16_t *)pMem2 = -1;  // *pMem2 = -1
                      pMem2[1] = j;
                      pMem2[2] = v11;
                      pMem2[3] = 0;
                      *((uint8_t *)pMem2 + 16) = 1;  // pMem2[16] = 1
                      pMem3 = pMem2;
                    }
                    else  // 否则分支
                    {
                      pMem3 = nullptr;  // pMem3 = 空指针
                    }
                    goto LABEL_33;
                  case 3:  // case 3 = ENUM_CMDPACKET_SET_UDP_IP_PORT
                  case 4:  // case 4 = ENUM_CMDPACKET_EXIT
                  case 5:  // case 5 = ENUM_CMDPACKET_SELECT_CHARACTER
                  case 6:  // case 6 = ENUM_CMDPACKET_CREATE_CHARACTER
                  case 7:  // case 7 = ENUM_CMDPACKET_DELETE_CHARACTER
                  case 8:  // case 8 = ENUM_CMDPACKET_RETURN_SELECT_CHARACTER
                    pMem3 = operator new(0x38u);  // new(56 字节) 分配对象
                    LOBYTE(v31) = 4;
                    if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
                      v13 = sub_49B4A0(i, j);  // 命令节点构造·0x38 变体（string +24、+48 参数、+52 标志）
                    else  // 否则分支
                      v13 = 0;
                    LOBYTE(v31) = 2;
                    *(uint32_t *)(v13 + 48) = sub_4423D0(nullptr);  // 调 循环：k = (void ***)sub_4423D0(&i); i != 0; k = (void ***)sub_4423
                    sub_443370();  // 脚本 token 取串（第三入口）
                    sub_443370();  // 脚本 token 取串（第三入口）
                    *(uint8_t *)(v13 + 52) = sub_40BF00((std::_String_base *)v22, 0, v24, "[pass next command]", 0x13u) == 0;  // std::string 比较（memcmp + 长度序；越界走 _Xran）
                    goto LABEL_32;
                  case 9:  // case 9 = ENUM_CMDPACKET_GET_USERINFO
                    pMem3 = operator new(0x38u);  // new(56 字节) 分配对象
                    LOBYTE(v31) = 5;
                    if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
                      v13 = sub_49B420(i, 9);  // 命令节点构造（0x14 字节，路径 string 在 +32）
                    else  // 否则分支
                      v13 = 0;
                    LOBYTE(v31) = 2;
                    sub_443370();  // 脚本 token 取串（第三入口）
                    *(uint8_t *)(v13 + 20) = sub_40BF00((std::_String_base *)v22, 0, v24, "[img]", 5u) != 0;  // std::string 比较（memcmp + 长度序；越界走 _Xran）
                    *(uint16_t *)(v13 + 22) = sub_4423D0(nullptr);  // 调 循环：k = (void ***)sub_4423D0(&i); i != 0; k = (void ***)sub_4423
                    *(uint32_t *)(v13 + 24) = sub_4423D0(nullptr);  // 调 循环：k = (void ***)sub_4423D0(&i); i != 0; k = (void ***)sub_4423
                    sub_443370();  // 脚本 token 取串（第三入口）
LABEL_32:  // 标签 LABEL_32（跳转合流点）
                    pMem3 = (void *)v13;
LABEL_33:  // 标签 LABEL_33（跳转合流点）
                    sub_49B8E0(&pMem3);  // 条目数组尾插（容量足直接写尾，满则 ·sub_49B680 扩容）
                    break;  // 跳出循环/分支
                  default:  // 默认分支
                    continue;  // 进入下一轮循环
                }
              }
            }
          }
        }
      }
      else  // 否则分支
      {
        sub_443370();  // 脚本 token 取串（第三入口）
        pMem4 = operator new(0x30u);  // new(48 字节) 分配对象
        fld_e13 = pMem4;
        LOBYTE(v31) = 3;
        if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
          v6 = (void *)sub_49B860(pMem4);  // 说话人条目构造（0x30：名字 string +4/+20/+24 + 命令数组 +36..+44）
        else  // 否则分支
          v6 = nullptr;  // v6 = 空指针
        p_Src = Src;
        LOBYTE(v31) = 2;
        fld_e13 = v6;
        if ( v29 < 0x10 )  // 若 v29 < 0x10
          p_Src = &Src;
        sub_4015C0(p_Src, strlen((const char *)p_Src));  // 【std::string构造赋值】
        sub_5660C0(&fld_e13);  // 文本辅助转发（565EE0）
        fld_e12 = *(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
        if ( fld_e12 != 0 )  // 若 fld_e12 非 0
          fld_e13 = (void *)(((*(this + 13) - fld_e12) >> 2) - 1);  // this+52〔bAuraState(推断)〕
        else  // 否则分支
          fld_e13 = (void *)-1;  // fld_e13 = 转换(-1)
      }
    }
    if ( v25 >= 0x10 )  // 若 v25 >= 0x10
      j__free(Block);  // 调 j__free（堆释放）
    v25 = 15;
    v24 = 0;
    LOBYTE(Block) = 0;
    if ( v29 >= 0x10 )  // 若 v29 >= 0x10
      j__free(Src);  // 调 j__free（堆释放）
    v28 = 0;
    LOBYTE(Src) = 0;
    v29 = 15;
    if ( v21 >= 0x10 )  // 若 v21 >= 0x10
      j__free(v19);  // 调 j__free（堆释放）
    return 1;  // 返回 1(成功)
  }
  else  // 否则分支
  {
    off_77F3FC(aErrorS_0, v2);  // 引擎日志输出函数(printf 风格)
    return 0;
  }
}


// ------------------------------------------------------------
// 0x49BD60 sub_49BD60 —— COUNT_DOWN 事件复位（+4..+16、+100 模式、+104 上次数 = -1）
//   +100 为事件模式（·sub_49BDB0 置 1/2，·sub_49CE00 依 2 走倒计时数字显示【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49BD60(uint32_t *this)  // 实现：COUNT_DOWN 事件复位（+4..+16、+100 模式、+104 上次数 = -1）
{
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 0;  // this+12〔nSkillRec12(推断)〕
  *(this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  *(this + 25) = 0;  // this+100〔bEnchantDone(推断)〕
  *(this + 26) = -1;  // this+104〔nTimerEnd(推断)〕
  return 0;
}



// ------------------------------------------------------------
// 0x49BD80 sub_49BD80 —— 事件对象子控件析构（+8 / +16 两枚 vt+4(1)）
//   两枚子控件指针非空则 vt+4(1) 析构并置 0（对照 ·sub_49B150 构造的 IControl【推断】）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49BD80(uint32_t *this)  // 实现：事件对象子控件析构（+8 / +16 两枚 vt+4(1)）
{
  int (/*thiscall*/ ***fld_e2)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e4)(uint32_t, int); // ecx

  fld_e2 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( fld_e2 != nullptr )  // 若 fld_e2 有效（非空）
    result = (**fld_e2)(fld_e2, 1);  // 调 fld_e2 的虚函数（vt+0）
  fld_e4 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  if ( fld_e4 != nullptr )  // 若 fld_e4 有效（非空）
    result = (**fld_e4)(fld_e4, 1);  // 调 fld_e4 的虚函数（vt+0）
  *(this + 4) = 0;  // this+16〔nChannelTypeSel(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x49BDB0 sub_49BDB0 —— COUNT_DOWN 设置（+100 模式 + 时钟复位 + 子控件可见切换）
//   时钟基 this+72 经 ·0x698F90 复位、+85/+86 标志清零；
//   模式非 0 → 子控件（this+8 指针）+16 可见 = 1，否则 0；+104 上次数置 -1。
// ------------------------------------------------------------
char /*thiscall*/ sub_49BDB0(uint32_t *this, int nArg2)  // 实现：COUNT_DOWN 设置（+100 模式 + 时钟复位 + 子控件可见切换）
{
  int pThis_12; // ecx
  int fld_e2; // eax

  pThis_12 = (int)(this + 18);  // this+18〔bDragChild〕
  *(this + 25) = nArg2;  // this+100〔bEnchantDone(推断)〕
  *(uint8_t *)(pThis_12 + 13) = 0;  // pThis_12=this+18 bDragChild
  *(uint8_t *)(pThis_12 + 14) = 0;  // pThis_12=this+18 bDragChild
  LOBYTE(fld_e2) = sub_698F90(pThis_12, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( nArg2 != 0 )  // 若 nArg2 非 0
  {
    *(uint8_t *)(*(this + 2) + 16) = 1;  // this+8〔nSkillRec8(推断)〕
  }
  else  // 否则分支
  {
    fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
    *(uint8_t *)(fld_e2 + 16) = 0;  // fld_e2=this+8 nSkillRec8
  }
  *(this + 26) = -1;  // this+104〔nTimerEnd(推断)〕
  return fld_e2;  // fld_e2=this+8 nSkillRec8
}



// ------------------------------------------------------------
// 0x49BE00 sub_49BE00 —— 会话对象数值读取（dword_8F8520 vt+120 → +134 防篡改读）
//   dword_8F8520 经 vt+120 取会话对象，读其 +134（·sub_41A5E0 防篡改数值读取）；
//   供 ·sub_49BEF0/·sub_49CE00 的数字位偏移计算 (v4 - 本值 + 25) 使用【推断：十位/位数偏移】。
// ------------------------------------------------------------
int sub_49BE00()  // 实现：会话对象数值读取（dword_8F8520 vt+120 → +134 防篡改读）
{
  int result; // eax
  int v1; // eax

  result = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
  if ( result != 0 )  // 若结果非 0（成功）
  {
    v1 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
    return sub_41A5E0(v1 + 134);  // crypt4byte 解密校验（·0x41A590 逆运算）
  }
  return result;
}



// ------------------------------------------------------------
// 0x49BE30 sub_49BE30 —— 会话对象槽值读取（+108 → 再 +108；断链返回 -1）
//   dword_8F8520 → vt+120 → +108 → +108；任一为空即 -1；
//   供 ·sub_49BEF0/·sub_49CE00 的显示分支（-1 与非 -1 落位不同）【推断：乱斗房间槽位/名次】。
// ------------------------------------------------------------
int sub_49BE30()  // 实现：会话对象槽值读取（+108 → 再 +108；断链返回 -1）
{
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) != 0  // 调虚槽 +120：动画对象
    && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) != 0 )  // 调虚槽 +120：动画对象
  {
    return *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108)  // 调虚槽 +120：动画对象
                     + 108);
  }
  else  // 否则分支
  {
    return -1;
  }
}



// ============================================================
// §N 0x49BE70-0x49CA80  UI/窗口联动（CLICK_BUTTON2）
// ============================================================
// ------------------------------------------------------------
// 0x49BE70 sub_49BE70 —— 会话数值 >= 槽值判定（+134 对 +108/+108）
//   对象或 +108 链为空、槽值为 -1 时一律 false；
//   否则以 ·sub_41A5E0(+134) >= 槽值 判定【推断：乱斗房间人数凑齐校验】。
// ------------------------------------------------------------
bool sub_49BE70()  // 实现：会话数值 >= 槽值判定（+134 对 +108/+108）
{
  int v0; // esi
  int v2; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) == 0 )  // 调虚槽 +120：动画对象
    return false;
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) == 0 )  // 调虚槽 +120：动画对象
    return false;
  v0 = *(uint32_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) + 108) + 108);  // 调虚槽 +120：动画对象
  if ( v0 == -1 )
    return false;
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520) == 0 )  // 调虚槽 +120：动画对象
    return v0 <= 0;
  v2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520);  // 调虚槽 +120：动画对象
  return sub_41A5E0(v2 + 134) >= v0;  // crypt4byte 解密校验（·0x41A590 逆运算）
}



// ------------------------------------------------------------
// 0x49BEF0 sub_49BEF0 —— COUNT_DOWN 事件（+44 图像、+208 状态、sub_48FD80）
// ------------------------------------------------------------
char /*thiscall*/ sub_49BEF0(int this, int nArg2)  // 实现：COUNT_DOWN 事件（+44 图像、+208 状态、sub_48FD80）
{
  int fld_64; // eax  | +0x0064 → 倒计时状态（0x49BEF0: *(this+100) 1/2 两态分派 blink 与文本）（CNRDCountDown；va=0049BEF0）
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
  if ( nArg2 != *(uint32_t *)(this + 8) )  // this+8〔nSkillRec8(推断)〕等 2 字段
    return fld_64;  // +0x0064 → 倒计时状态（0x49BEF0: *(this+100) 1/2 两态分派 blink 与文本）（CNRDCountDown；va=0049BEF0）
  fld_64 = *(uint32_t *)(this + 100);  // fld_64 = 读 this+100
  if ( fld_64 == 1 || fld_64 == 2 )  // 若 fld_64 == 1 与/或 fld_64 == 2
  {
    fld_64 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));  // 角色/物品栏管理器
    if ( fld_64 != 0 )  // 若 fld_64 非 0
    {
      v4 = sub_49BE30();  // 会话对象槽值读取（+108 → 再 +108；断链返回 -1）
      if ( v4 == -1 )
      {
        fld_C = sub_418DD0(*(uint32_t **)(this + 12), 0);  // fld_C = 调 sub_418DD0 返回值
        if ( fld_C != 0 )  // 若 fld_C 非 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_C + 152))(fld_C, 213, 236, dword_79C0B0);  // 调虚槽 +152：效果通道 3
        if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )  // 【clock_now(clk)】
        {
          fld_C2 = sub_418DD0(*(uint32_t **)(this + 12), 1u);  // fld_C2 = 调 sub_418DD0 返回值
          sub_40FC80((void *)dword_79C0B0, 215, 238, fld_C2);  // 贴图转发（目标对象虚发 +152(this, x, y)）
        }
        v7 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));  // 角色/物品栏管理器
        LOBYTE(fld_64) = sub_69A110(338, 276, v7, -1);  // fld_64=this+100 nCountState
        goto LABEL_24;
      }
      LOBYTE(fld_64) = sub_49BE70();  // 会话数值 >= 槽值判定（+134 对 +108/+108）
      if ( (uint8_t)fld_64 == 0 )  // fld_64=this+100 nCountState
      {
        LOBYTE(fld_64) = *(uint8_t *)(*(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 120))(dword_8F8520)  // 调虚槽 +120：动画对象
                                          + 108)
                              + 464);
        if ( (uint8_t)fld_64 != 0 )
        {
          fld_C3 = sub_418DD0(*(uint32_t **)(this + 12), 0x26u);  // fld_C3 = 调 sub_418DD0 返回值
          sub_40FC80((void *)dword_79C0B0, 209, 206, fld_C3);  // 贴图转发（目标对象虚发 +152(this, x, y)）
          if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )  // 【clock_now(clk)】
          {
            fld_C4 = sub_418DD0(*(uint32_t **)(this + 12), 0x27u);  // fld_C4 = 调 sub_418DD0 返回值
            sub_40FC80((void *)dword_79C0B0, 213, 248, fld_C4);  // 贴图转发（目标对象虚发 +152(this, x, y)）
          }
          v10 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));  // 角色/物品栏管理器
          sub_69A110(338, 267, v10, -1);
          fld_C5 = sub_418DD0(*(uint32_t **)(this + 12), 0x18u);  // fld_C5 = 调 sub_418DD0 返回值
          sub_40FC80((void *)dword_79C0B0, 365 - (*(uint32_t *)(fld_C5 + 20) >> 1), 310 - (*(uint32_t *)(fld_C5 + 24) >> 1), fld_C5);  // 贴图转发（目标对象虚发 +152(this, x, y)）
          v12 = sub_49BE00();  // 会话对象数值读取（dword_8F8520 vt+120 → +134 防篡改读）
          fld_C6 = sub_418DD0(*(uint32_t **)(this + 12), v4 - v12 + 25);  // fld_C6 = 调 sub_418DD0 返回值
          sub_40FC80((void *)dword_79C0B0, 352 - (*(uint32_t *)(fld_C6 + 20) >> 1), 310 - (*(uint32_t *)(fld_C6 + 24) >> 1), fld_C6);  // 贴图转发（目标对象虚发 +152(this, x, y)）
          fld_C7 = sub_418DD0(*(uint32_t **)(this + 12), v4 + 25);  // fld_C7 = 调 sub_418DD0 返回值
          v15 = 310;
        }
        else  // 否则分支
        {
          if ( *(uint32_t *)(dword_8F7A24 + 12) != 6 )  // 登录/选区管理器
            goto LABEL_24;
          fld_C8 = sub_418DD0(*(uint32_t **)(this + 12), 0x28u);  // fld_C8 = 调 sub_418DD0 返回值
          sub_40FC80((void *)dword_79C0B0, 211, 237, fld_C8);  // 贴图转发（目标对象虚发 +152(this, x, y)）
          if ( ((sub_699000(this + 72) / 0x1F4u) & 1) != 0 && sub_699000(this + 72) < 10000 )  // 【clock_now(clk)】
          {
            fld_C9 = sub_418DD0(*(uint32_t **)(this + 12), 0x29u);  // fld_C9 = 调 sub_418DD0 返回值
            sub_40FC80((void *)dword_79C0B0, 213, 239, fld_C9);  // 贴图转发（目标对象虚发 +152(this, x, y)）
          }
          v18 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)dword_8F852C + 3) + 4) + 44))(*(uint32_t *)(*((uint32_t *)dword_8F852C + 3) + 4));  // 角色/物品栏管理器
          sub_69A110(338, 267, v18, -1);
          fld_C10 = sub_418DD0(*(uint32_t **)(this + 12), 0x18u);  // fld_C10 = 调 sub_418DD0 返回值
          sub_40FC80((void *)dword_79C0B0, 363 - (*(uint32_t *)(fld_C10 + 20) >> 1), 311 - (*(uint32_t *)(fld_C10 + 24) >> 1), fld_C10);  // 贴图转发（目标对象虚发 +152(this, x, y)）
          v20 = sub_49BE00();  // 会话对象数值读取（dword_8F8520 vt+120 → +134 防篡改读）
          fld_C11 = sub_418DD0(*(uint32_t **)(this + 12), v4 - v20 + 25);  // fld_C11 = 调 sub_418DD0 返回值
          sub_40FC80((void *)dword_79C0B0, 347 - (*(uint32_t *)(fld_C11 + 20) >> 1), 311 - (*(uint32_t *)(fld_C11 + 24) >> 1), fld_C11);  // 贴图转发（目标对象虚发 +152(this, x, y)）
          fld_C7 = sub_418DD0(*(uint32_t **)(this + 12), v4 + 25);  // fld_C7 = 调 sub_418DD0 返回值
          v15 = 311;
        }
        LOBYTE(fld_64) = sub_40FC80(  // 贴图转发（目标对象虚发 +152(this, x, y)）
                       (void *)dword_79C0B0,  // 默认字体/绘制资源
                       378 - (*(uint32_t *)(fld_C7 + 20) >> 1),
                       v15 - (*(uint32_t *)(fld_C7 + 24) >> 1),
                       fld_C7);
      }
    }
  }
LABEL_24:  // 标签 LABEL_24（跳转合流点）
  if ( *(uint32_t *)(this + 100) == 2 )  // this+100〔bEnchantDone(推断)〕
  {
    if ( (9999 - sub_699000(this + 72)) / 1000 <= 0 )  // 【clock_now(clk)】
      pThis_48 = 0;
    else  // 否则分支
      pThis_48 = (9999 - sub_699000(this + 72)) / 1000;  // 【clock_now(clk)】
    if ( *(uint32_t *)(dword_8F7A24 + 12) == 6 && dword_99FF08 != 0 && sub_48FD80((uint8_t *)dword_99FF08) == 0 )  // 空槽计数（+144..+151 中为 0 的字节数）
    {
      fld_C12 = sub_418DD0(*(uint32_t **)(this + 12), pThis_48 + 2);  // fld_C12 = 调 sub_418DD0 返回值
      sub_40FC80((void *)dword_79C0B0, 271, 105, fld_C12);  // 贴图转发（目标对象虚发 +152(this, x, y)）
      v24 = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 208), 0x4Cu);  // v24 = 调 sub_418DD0 返回值
      LOBYTE(fld_64) = sub_40FC80((void *)dword_79C0B0, 115, 194, v24);  // 贴图转发（目标对象虚发 +152(this, x, y)）
    }
    else  // 否则分支
    {
      v25 = sub_49BE30();  // 会话对象槽值读取（+108 → 再 +108；断链返回 -1）
      fld_C13 = *(uint32_t **)(this + 12);  // fld_C13 = 读 this+12
      v28 = pThis_48 + 2;
      if ( v25 == -1 )
      {
        fld_64 = sub_418DD0(fld_C13, v28);  // fld_64 = 调 sub_418DD0 返回值
        if ( fld_64 != 0 )  // 若 fld_64 非 0
          LOBYTE(fld_64) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_64 + 152))(fld_64, 282, 121, dword_79C0B0);  // 调虚槽 +152：效果通道 3
      }
      else  // 否则分支
      {
        fld_64 = sub_418DD0(fld_C13, v28);  // fld_64 = 调 sub_418DD0 返回值
        if ( fld_64 != 0 )  // 若 fld_64 非 0
          LOBYTE(fld_64) = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_64 + 152))(fld_64, 282, 116, dword_79C0B0);  // 调虚槽 +152：效果通道 3
      }
    }
    if ( *(uint32_t *)(this + 104) != pThis_48 )  // this+104〔nTimerEnd(推断)〕
    {
      LOBYTE(fld_64) = (uint8_t)sub_432EA0("COUNT_DOWN", -1, 0, 0);  // 音效播放包装（非空判定）
      *(uint32_t *)(this + 104) = pThis_48;  // this+104〔nTimerEnd(推断)〕
    }
  }
  return fld_64;  // +0x0064 → 倒计时状态（0x49BEF0: *(this+100) 1/2 两态分派 blink 与文本）（CNRDCountDown；va=0049BEF0）
}


// ------------------------------------------------------------
// 0x49C380 sub_49C380 —— 帧字段组读取（+40/+44/+48/+52/+56）
// ------------------------------------------------------------
int /*thiscall*/ sub_49C380(int this, void *Block)  // 实现：帧字段组读取（+40/+44/+48/+52/+56）
{
  uint8_t *pMem; // eax
  uint8_t *v4; // eax
  int fld_C; // eax
  int result; // eax

  *(uint32_t *)(this + 4) = Block;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 12) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 68);  // this+12〔nSkillRec12(推断)〕等 2 字段
  pMem = operator new(0x68u);  // new(104 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v4 = sub_426BD0(pMem);  // nengine::IControl 构造
  else  // 否则分支
    v4 = nullptr;  // v4 = 空指针
  *(uint32_t *)(this + 8) = v4;  // this+8〔nSkillRec8(推断)〕等 2 字段
  *((uint32_t *)v4 + 17) = this;  // v4[17] = this
  if ( operator new(0x2Cu) != nullptr )  // new(44 字节) 分配对象
    fld_C = sub_423B30(dword_79C0B0, *(uint32_t *)(this + 12), 13, 4);  // CNNumberSet 构造
  else  // 否则分支
    fld_C = 0;
  *(uint32_t *)(this + 16) = fld_C;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  *(uint8_t *)(this + 20) = 0;  // this+20〔nPage(推断)〕等 2 字段
  *(uint8_t *)(this + 21) = 0;  // this+21〔bArmorState〕
  *(uint8_t *)(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  *(uint8_t *)(this + 23) = 0;  // this+92〔pFxObjC(推断)〕
  *(uint32_t *)(this + 32) = 0;  // this+32〔nHeight(推断)〕等 2 字段
  *(uint32_t *)(this + 36) = 6;  // this+36〔nStateWord36(推断)〕等 2 字段
  *(uint32_t *)(this + 40) = 12;  // this+40〔bStateSub40(推断)〕等 2 字段
  *(uint32_t *)(this + 44) = 0;  // this+44〔nExpireMs(推断)〕等 2 字段
  *(uint32_t *)(this + 48) = 1600;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *(uint32_t *)(this + 52) = 0;  // this+52〔bAuraState(推断)〕等 2 字段
  *(uint32_t *)(this + 56) = 0;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  *(uint32_t *)(this + 60) = 0;  // this+60〔nFadeValue60(推断)〕等 2 字段
  *(uint32_t *)(this + 64) = 0;  // this+64〔apServerTabBtn(推断)〕等 2 字段
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 68) = dword_99FCCC;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 24) = -16777216;  // this+24〔nPageMax(推断)〕等 2 字段
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint8_t *)(this + 85) = 0;  // this+340〔pSlotTbl340(推断)〕
  *(uint8_t *)(this + 86) = 0;  // this+344〔nReservedDelay(推断)〕
  sub_698F90(this + 72, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  result = *(uint32_t *)(this + 8);  // result = 读 this+8
  *(uint8_t *)(result + 16) = 0;  // result=this+8 物品 id
  *(uint32_t *)(this + 104) = -1;  // this+104〔nTimerEnd(推断)〕
  return result;  // result=this+8 物品 id
}



// ------------------------------------------------------------
// 0x49C4A0 sub_49C4A0 —— 命令记录推入缓冲（8 项：参 + clock_now + 常量 4）
//   推入顺序：nArg2、clock_now(this+20)、nArg3、4、nArg4..nArg7；
//   ·sub_58B2A0 为 dword 数组 push（容量按 +100 步长扩容）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49C4A0(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6, int nArg7)  // 实现：命令记录推入缓冲（8 项：参 + clock_now + 常量 4）
{
  int pThis_14; // eax

  sub_58B2A0(nArg2);  // dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
  pThis_14 = sub_699000((int)this + 20);  // 【clock_now(clk)】
  sub_58B2A0(pThis_14);  // dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
  sub_58B2A0(nArg3);  // dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
  sub_58B2A0(4);  // dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
  sub_58B2A0(nArg4);  // dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
  sub_58B2A0(nArg5);  // dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
  sub_58B2A0(nArg6);  // dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
  return sub_58B2A0(nArg7);  // dword 动态数组 push（容量按 +100 步长扩容，operator new(4n+400) 迁移）
}



// ------------------------------------------------------------
// 0x49C510 sub_49C510 —— 命令下发入口（五元组写 dword_9A0250 后 ·sub_4AEA30 派发）
//   首次调用注册 atexit 清理（dword_9A0264 位 0 守卫）；
//   参数落 dword_9A0250/9A0254/9A0258/9A025C/9A0260 后调 ·sub_4AEA30（按容器 +4 标签查找分发）；
//   旁证：tau_golem/goblin_fox 转写把 ·0x49C510(10, 自身, 同伴, 目标, 0) 记为协同攻击令。
// ------------------------------------------------------------
int /*cdecl*/ sub_49C510(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：命令下发入口（五元组写 dword_9A0250 后 ·sub_4AEA30 派发）
{
  if ( (dword_9A0264 & 1) == 0 )  // 若 dword_9A0264 位 1 清零
  {
    dword_9A0264 |= 1u;
    dword_9A0250 = 0;
    dword_9A0254 = 0;
    dword_9A0258 = 0;
    dword_9A025C = 0;
    dword_9A0260 = 0;
    atexit(nullsub_4);  // 调 atexit（登记退出回调（表满返回非 0））
  }
  dword_9A0254 = nArg2;
  dword_9A0250 = nArg1;
  dword_9A0260 = nArg5;
  dword_9A0258 = nArg3;
  dword_9A025C = nArg4;
  return sub_4AEA30(&dword_9A0250);  // 返回 调 sub_4AEA30 返回值
}



// ------------------------------------------------------------
// 0x49C5A0 sub_49C5A0 —— 命令缓冲消费（从 dword_9A02C0 顺序取 4 项 → ·sub_49C510）
//   dword_9A02C0 缓冲、dword_9A02D0 读游标；
//   取出 4 项重排为 (第 2, 0, 第 1, 第 3, 第 4) 下发【推断：缓冲由 ·sub_49C4A0 的推入序列填充】。
// ------------------------------------------------------------
int sub_49C5A0()  // 实现：命令缓冲消费（从 dword_9A02C0 顺序取 4 项 → ·sub_49C510）
{
  int v0; // edx
  int v1; // esi
  int v2; // edi
  int v4; // [esp-4h] [ebp-Ch]

  v0 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v1 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v2 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  v4 = *(uint32_t *)(dword_9A02C0 + 4 * dword_9A02D0++);
  return sub_49C510(v1, 0, v0, v2, v4);  // 命令下发入口（五元组写 dword_9A0250 后 ·sub_4AEA30 派发）
}



// ------------------------------------------------------------
// 0x49C5F0 sub_49C5F0 —— 命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
//   转调 ·sub_49C4A0(&dword_9A02C0, ·sub_49C5A0, nArg5, this+4, nArg2, nArg3, nArg4)。
// ------------------------------------------------------------
int /*thiscall*/ sub_49C5F0(int *this, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：命令记录写入包装（回调指针 ·sub_49C5A0 + this+4 关联 id）
{
  return sub_49C4A0(&dword_9A02C0, (int)sub_49C5A0, nArg5, *(this + 1), nArg2, nArg3, nArg4);  // 命令缓冲消费（从 dword_9A02C0 顺序取 4 项 → ·sub_49C510）
}



// ------------------------------------------------------------
// 0x49C620 sub_49C620 —— 命令下发包装（组 id = this+4，值重复两遍）
//   转调 ·sub_49C510(nArg2, this+4, this+4, nArg3, nArg4)。
// ------------------------------------------------------------
int /*thiscall*/ sub_49C620(int *this, int nArg2, int nArg3, int nArg4)  // 实现：命令下发包装（组 id = this+4，值重复两遍）
{
  return sub_49C510(nArg2, *(this + 1), *(this + 1), nArg3, nArg4);  // 命令下发入口（五元组写 dword_9A0250 后 ·sub_4AEA30 派发）
}



// ------------------------------------------------------------
// 0x49C640 sub_49C640 —— deque 越界异常抛掷（deque<T> too long / length_error）
//   与 ·sub_49B610 同构（差异：文案为 deque<T> too long），由 ·sub_49C6B0 超限时调用。
// ------------------------------------------------------------
void /*noreturn*/ sub_49C640()  // 实现：deque 越界异常抛掷（deque<T> too long / length_error）
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
  sub_401740(pExceptionObject, &v1);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x49C6B0 sub_49C6B0 —— deque 块缓冲扩容（≥1.5 倍或 +8 步长重建 + 中段迁移）
//   +4 缓冲、+8 容量、+12 起始偏移；新容量 = 旧 + max(要求, 旧/2 且下限 8)；
//   operator new 后按 4 字节格 memcpy 中段，两侧空档 memset 清零。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_49C6B0(int this, unsigned int uArg2)  // 实现：deque 块缓冲扩容（≥1.5 倍或 +8 步长重建 + 中段迁移）
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
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = 读 this+8
  if ( 0xFFFFFFF - fld_8 < uArg2 )  // fld_8=this+8 物品 id
    sub_49C640(this);  // deque 越界异常抛掷（deque<T> too long / length_error）
  v5 = fld_8 >> 1;  // fld_8=this+8 物品 id
  if ( fld_8 >> 1 < 8 )  // fld_8=this+8 物品 id
    v5 = 8;
  if ( uArg2 < v5 && fld_8 <= 0xFFFFFFF - v5 )  // 若 uArg2 < v5 与/或 fld_8 <= 0xFFFFFFF
  {
    uArg2 = v5;
    uArg22 = v5;
  }
  fld_C = *(uint32_t *)(this + 12) >> 2;  // fld_C = 读 this+12
  v7 = 4 * fld_C;
  pMem = (char *)operator new(4 * (uArg22 + fld_8));  // fld_8=this+8 物品 id
  fld_82 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * fld_C) >> 2);
  fld_4 = (char *)memcpy_0(&pMem[4 * fld_C], (const void *)(4 * fld_C + *(uint32_t *)(this + 4)), fld_82);  // this+4〔宿主对象〕等 2 字段
  fld_42 = *(const void **)(this + 4);  // this+16〔nChannelTypeSel(推断)〕
  v10 = &fld_4[fld_82];  // fld_4=this+4 宿主对象
  if ( fld_C > uArg2 )  // 若 fld_C > uArg2
  {
    memcpy_0(v10, fld_42, 4 * ((int)(4 * uArg2) >> 2));  // fld_42=this+16 nChannelTypeSel
    v14 = 4 * ((int)(v7 - 4 * uArg2) >> 2);
    fld_43 = (char *)memcpy_0(pMem, (const void *)(4 * uArg2 + *(uint32_t *)(this + 4)), v14);  // this+4〔宿主对象〕等 2 字段
    pBuf = uArg2;
    pBuf2 = &fld_43[v14];  // fld_43=this+4 宿主对象
    if ( uArg2 == 0 )  // 若 uArg2 为 0
      goto LABEL_15;
    goto LABEL_14;
  }
  pBuf3 = (char *)memcpy_0(v10, fld_42, 4 * (v7 >> 2)) + 4 * (v7 >> 2);  // fld_42=this+16 nChannelTypeSel
  if ( uArg2 != fld_C )  // 若 uArg2 != fld_C
    memset(pBuf3, 0, 4 * (uArg2 - fld_C));  // 调 memset（内存按字节填充）
  if ( fld_C != 0 )  // 若 fld_C 非 0
  {
    pBuf = fld_C;
    pBuf2 = pMem;
LABEL_14:  // 标签 LABEL_14（跳转合流点）
    memset(pBuf2, 0, 4 * pBuf);  // 调 memset（内存按字节填充）
  }
LABEL_15:  // 标签 LABEL_15（跳转合流点）
  if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
    j__free(*(void **)(this + 4));  // 释放 this+4〔宿主对象〕堆块
  result = uArg2 + *(uint32_t *)(this + 8);  // this+8〔nSkillRec8(推断)〕等 2 字段
  *(uint32_t *)(this + 4) = pMem;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 8) = result;  // this+8〔nSkillRec8(推断)〕等 2 字段
  return result;  // result=this+8 nSkillRec8
}



// ------------------------------------------------------------
// 0x49C800 sub_49C800 —— deque 尾格写入（4 格一块按需 new(0x10)，+16 计数自增）
//   this+4 块指针数组、+8 容量、+12 起始偏移、+16 有效计数；
//   块内槽 = 绝对序号 & 3，块首 (绝对 >> 2) 为空时分配 operator new(0x10)；
//   边界对齐时先 ·sub_49C6B0(1) 扩容。
// ------------------------------------------------------------
int /*thiscall*/ sub_49C800(int this, uint32_t *uArg2)  // 实现：deque 尾格写入（4 格一块按需 new(0x10)，+16 计数自增）
{
  int fld_10; // eax
  unsigned int fld_8; // eax
  unsigned int fld_102; // edi
  unsigned int v6; // ebx
  uint32_t *fld_4; // edi
  int result; // eax

  fld_10 = *(uint32_t *)(this + 16);  // fld_10 = 读 this+16
  if ( (((uint8_t)fld_10 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(fld_10 + 4) >> 2 )  // 复合条件判定（与/或）
    sub_49C6B0(this, 1u);  // deque 块缓冲扩容（≥1.5 倍或 +8 步长重建 + 中段迁移）
  fld_8 = *(uint32_t *)(this + 8);  // fld_8 = 读 this+8
  fld_102 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);  // fld_102 = 读 this+16
  v6 = fld_102 >> 2;
  if ( fld_8 <= fld_102 >> 2 )  // fld_8=this+8 物品 id
    v6 -= fld_8;  // fld_8=this+8 物品 id
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )  // this+4〔宿主对象〕等 2 字段
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);  // new(16 字节) 分配对象
  fld_4 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (fld_102 & 3));  // this+4〔宿主对象〕等 2 字段
  if ( fld_4 != nullptr )  // 若 fld_4 有效（非空）
    *fld_4 = *uArg2;  // fld_4=this+4 宿主对象
  result = *(uint32_t *)(this + 16) + 1;  // result = 读 this+16
  *(uint32_t *)(this + 16) = result;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  return result;
}



// ------------------------------------------------------------
// 0x49C880 sub_49C880 —— 定长对象池取用（尺寸匹配走预填池，否则直 operator new）
//   尺寸 != 池对象尺寸时直接 operator new(Size)【推断：池为定长对象复用】；
//   池空（+20 计数为 0）时先铺 512 个 operator new 进 ·sub_49C800 环形块；
//   取格后 +36 递减、归零时 +28 清零（回收游标复位）。
// ------------------------------------------------------------
void */*thiscall*/ sub_49C880(size_t *this, size_t Size)  // 实现：定长对象池取用（尺寸匹配走预填池，否则直 operator new）
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
  if ( *(this + 5) == 0 )  // this+20〔nPage(推断)〕
  {
    for ( i = 512; i != 0; --i )  // 循环：i 从 512 递减到 0
    {
      Size = (size_t)operator new(*this);
      sub_49C800((int)(this + 1), &Size);  // deque 尾格写入（4 格一块按需 new(0x10)，+16 计数自增）
    }
  }
  pThis_1 = this + 1;
  fld_e4 = *(this + 4) + *(this + 5) - 1;  // this+16〔nChannelTypeSel(推断)〕等 2 字段
  v7 = fld_e4 >> 2;  // fld_e4=this+16 nChannelTypeSel
  pThis_12 = this + 1;
  v9 = fld_e4 - 4 * (fld_e4 >> 2);  // fld_e4=this+16 nChannelTypeSel
  v10 = pThis_12[2];  // v10 = 取 pThis_12[2]
  if ( v10 <= v7 )  // 若 v10 <= v7
    v7 -= v10;
  result = *(void **)(*(uint32_t *)(pThis_12[1] + 4 * v7) + 4 * v9);
  v11 = pThis_1[4];  // v11 = 取 pThis_1[4]
  if ( v11 != 0 )  // 若 v11 非 0
  {
    v12 = v11 - 1;
    pThis_1[4] = v12;
    if ( v12 == 0 )  // 若 v12 为 0
      pThis_1[3] = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49C920 sub_49C920 —— 池对象分配（0x14 字节 5 值）并入队 unk_9A02F0
//   ·sub_49C880(dword_9B930C, 0x14) 取池格，填 (nArg1..nArg5)；
//   再经 ·sub_49C800(&unk_9A02F0) 尾写入队（队列存格指针）。
// ------------------------------------------------------------
int /*cdecl*/ sub_49C920(int nArg1, int nArg2, int nArg3, int nArg4, int nArg5)  // 实现：池对象分配（0x14 字节 5 值）并入队 unk_9A02F0
{
  uint32_t *v5; // ecx
  uint32_t *nArg12; // eax
  uint32_t *nArg122; // [esp+0h] [ebp-4h] BYREF

  nArg122 = v5;
  nArg12 = sub_49C880(&dword_9B930C, 0x14u);  // 定长对象池取用（尺寸匹配走预填池，否则直 operator new）
  if ( nArg12 != nullptr )  // 若 nArg12 有效（非空）
  {
    *nArg12 = nArg1;
    nArg12[1] = nArg2;
    nArg12[2] = nArg3;
    nArg12[3] = nArg4;
    nArg12[4] = nArg5;
  }
  else  // 否则分支
  {
    nArg12 = nullptr;  // nArg12 = 空指针
  }
  nArg122 = nArg12;
  return sub_49C800((int)&unk_9A02F0, &nArg122);  // deque 尾格写入（4 格一块按需 new(0x10)，+16 计数自增）
}



// ------------------------------------------------------------
// 0x49C970 sub_49C970 —— 池分配包装（this+4 复制为第 2/3 参）
//   转调 ·sub_49C920(nArg2, this+4, this+4, nArg3, nArg4)。
// ------------------------------------------------------------
int /*thiscall*/ sub_49C970(int *this, int nArg2, int nArg3, int nArg4)  // 实现：池分配包装（this+4 复制为第 2/3 参）
{
  return sub_49C920(nArg2, *(this + 1), *(this + 1), nArg3, nArg4);  // 池对象分配（0x14 字节 5 值）并入队 unk_9A02F0
}



// ------------------------------------------------------------
// 0x49C990 sub_49C990 —— 事件对象字段清零（+4..+72 与 +232..+260 八槽置 -1）
//   八槽 -1 对应 ·sub_49CA80 的 +58..+65 窗口状态槽（拾取窗口序号后再行填实）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49C990(uint32_t *this)  // 实现：事件对象字段清零（+4..+72 与 +232..+260 八槽置 -1）
{
  uint32_t *pThis_3A; // ecx

  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
  *(this + 9) = 0;  // this+36〔nStateWord36(推断)〕
  *(this + 10) = 0;  // this+40〔bStateSub40(推断)〕
  *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  *(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *(this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *(this + 15) = 0;  // this+60〔nFadeValue60(推断)〕
  *(this + 16) = 0;  // this+64〔apServerTabBtn(推断)〕
  *(this + 17) = 0;  // this+68〔nCharCount(推断)〕
  *(this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  *(this + 7) = 0;  // this+28〔pPanelVec(推断)〕
  *(this + 8) = 0;  // this+32〔nHeight(推断)〕
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
// 0x49C9E0 sub_49C9E0 —— 事件对象子控件批量析构（+24/+36/+40/+44/+52/+56 + 3 连 +60..+68 + +72）
//   逐个 vt+4(1) 销毁后清槽；
//   其中 +60/+64/+68（视图 +15..+17）为连续 3 槽小数组。
// ------------------------------------------------------------
int /*thiscall*/ sub_49C9E0(uint32_t *this)  // 实现：事件对象子控件批量析构（+24/+36/+40/+44/+52/+56 + 3 连 +60..+68 + +72）
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

  fld_e6 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 6);  // this+24〔nPageMax(推断)〕
  if ( fld_e6 != nullptr )  // 若 fld_e6 有效（非空）
    result = (**fld_e6)(fld_e6, 1);  // 调 fld_e6 的虚函数（vt+0）
  fld_e9 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 9);  // this+36〔nStateWord36(推断)〕
  *(this + 6) = 0;  // this+24〔nPageMax(推断)〕
  if ( fld_e9 != nullptr )  // 若 fld_e9 有效（非空）
    result = (**fld_e9)(fld_e9, 1);  // 调 fld_e9 的虚函数（vt+0）
  fld_e10 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 10);  // this+40〔bStateSub40(推断)〕
  *(this + 9) = 0;  // this+36〔nStateWord36(推断)〕
  if ( fld_e10 != nullptr )  // 若 fld_e10 有效（非空）
    result = (**fld_e10)(fld_e10, 1);  // 调 fld_e10 的虚函数（vt+0）
  fld_e11 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 11);  // this+44〔nExpireMs(推断)〕
  *(this + 10) = 0;  // this+40〔bStateSub40(推断)〕
  if ( fld_e11 != nullptr )  // 若 fld_e11 有效（非空）
    result = (**fld_e11)(fld_e11, 1);  // 调 fld_e11 的虚函数（vt+0）
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);  // this+52〔bAuraState(推断)〕
  *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  if ( fld_e13 != nullptr )  // 若 fld_e13 有效（非空）
    result = (**fld_e13)(fld_e13, 1);  // 调 fld_e13 的虚函数（vt+0）
  fld_e14 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 14);  // this+56〔pCmdVecCap56(推断)〕
  *(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  if ( fld_e14 != nullptr )  // 若 fld_e14 有效（非空）
    result = (**fld_e14)(fld_e14, 1);  // 调 fld_e14 的虚函数（vt+0）
  *(this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  pThis_F = this + 15;
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
  {
    if ( *pThis_F != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_F)(*pThis_F, 1);
    *pThis_F++ = 0;
  }
  fld_e18 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 18);  // this+72〔nSnapshot72(推断)〕
  if ( fld_e18 != nullptr )  // 若 fld_e18 有效（非空）
    result = (**fld_e18)(fld_e18, 1);  // 调 fld_e18 的虚函数（vt+0）
  *(this + 18) = 0;  // this+72〔nSnapshot72(推断)〕
  return result;
}



// ============================================================
// §O 0x49CA80-0x49E930  结算演出族（M_RESULT / RESULT_FLASH）
// ============================================================
// ------------------------------------------------------------
// 0x49CA80 sub_49CA80 —— 窗口状态查询（+58/+59 → sub_48FCA0/sub_578E80）
// ------------------------------------------------------------
int /*thiscall*/ sub_49CA80(int *this)  // 实现：窗口状态查询（+58/+59 → sub_48FCA0/sub_578E80）
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
  *(this + 58) = -1;  // this+232〔bSyncFlag〕
  *(this + 59) = -1;  // this+236〔nSyncArgA〕
  *(this + 60) = -1;  // this+240〔nSyncArgB〕
  *(this + 61) = -1;  // this+244〔fSyncTime〕
  *(this + 62) = -1;  // this+248〔bQuad1〕
  *(this + 63) = -1;  // this+252〔nQuad2〕
  *(this + 64) = -1;  // this+256〔bQuad3〕
  *(this + 65) = -1;  // this+260〔nQuad4〕
  v3 = 0;
  v4 = 1;
  v5 = (uint32_t *)(dword_99FF082 + 8);
  v12 = 1;
  pThis_3A = this + 58;
  v11 = v5;
  do  // do-while 循环体起点
  {
    if ( *v5 != 255 )
    {
      if ( v3 == sub_48FCA0() )  // 自身座位下标查找（表 dword_99FF08）
      {
        *pThis_3A = 0;
      }
      else  // 否则分支
      {
        v6 = sub_578E80(v3);  // v6 = 调 sub_578E80 返回值
        if ( v6 != 0 )  // 若 v6 非 0
        {
          pObj = *(uint32_t *)(v6 + 196);
          if ( pObj != 0 )  // 若 pObj 非 0
          {
            v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 376))(pObj);  // 调虚槽 +376：坐标同步包（type 37）
            v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 376))(dword_8F7C04) == v8;  // 调虚槽 +376：坐标同步包（type 37）
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
  while ( v3 < 8 );  // 条件循环
  result = -1;
  if ( *(this + 58) == -1 )  // this+232〔bSyncFlag〕
    *(this + 58) = v4++;  // this+232〔bSyncFlag〕
  if ( *(this + 59) == -1 )  // this+236〔nSyncArgA〕
    *(this + 59) = v4++;  // this+236〔nSyncArgA〕
  if ( *(this + 60) == -1 )  // this+240〔nSyncArgB〕
    *(this + 60) = v4++;  // this+240〔nSyncArgB〕
  if ( *(this + 61) == -1 )  // this+244〔fSyncTime〕
    *(this + 61) = v4++;  // this+244〔fSyncTime〕
  if ( *(this + 62) == -1 )  // this+248〔bQuad1〕
    *(this + 62) = v4++;  // this+248〔bQuad1〕
  if ( *(this + 63) == -1 )  // this+252〔nQuad2〕
    *(this + 63) = v4++;  // this+252〔nQuad2〕
  if ( *(this + 64) == -1 )  // this+256〔bQuad3〕
    *(this + 64) = v4++;  // this+256〔bQuad3〕
  if ( *(this + 65) == -1 )  // this+260〔nQuad4〕
    *(this + 65) = v4;  // this+260〔nQuad4〕
  return result;
}



// ------------------------------------------------------------
// 0x49CBD0 sub_49CBD0 —— CLICK_BUTTON2 事件分发（音效 sub_432EA0、sub_48FCA0/48FC30）
// ------------------------------------------------------------
int /*thiscall*/ sub_49CBD0(int *this)  // 实现：CLICK_BUTTON2 事件分发（音效 sub_432EA0、sub_48FCA0/48FC30）
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

  result = *(this + 6);  // this+24〔nPageMax(推断)〕
  if ( *(uint8_t *)(result + 16) != 0 )  // result=this+24 nPageMax
  {
    result = dword_99FF08;  // result=this+24 nPageMax
    if ( dword_99FF08 != 0 )  // 若 dword_99FF08 非 0
    {
      fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
      v4 = fld_e1[202];  // v4 = 取 fld_e1[202]
      if ( v4 == 0 || (result = (fld_e1[203] - v4) >> 2) == 0 )  // 若 v4 == 0
      {
        fld_e11 = *(this + 11);  // this+44〔nExpireMs(推断)〕
        if ( *(uint8_t *)(fld_e11 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e11 + 12) )  // 复合条件判定（与/或）
        {
          fld_e3 = *(this + 3);  // this+12〔nSkillRec12(推断)〕
          if ( fld_e3 != 0 && (*(this + 4) - fld_e3) >> 2 != 0 )  // 若 fld_e3 != 0
          {
            sub_44E8D0((char *)dword_8F8528, (void *)0x2A, (int)(this + 2), 0);  // 对象池借出（按池号取可用对象）
          }
          else  // 否则分支
          {
            v7 = (uint32_t *)fld_e1[7];  // fld_e1=this+4 宿主对象
            v8 = sub_422E70(448);  // v8 = 调 sub_422E70 返回值
            sub_43BEE0(v7, v8, -6567706, 0, -1);  // 调 播报 + 面板刷新 ──
          }
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 音效播放包装（非空判定）
        }
        fld_e10 = *(this + 10);  // this+40〔bStateSub40(推断)〕
        if ( *(uint8_t *)(fld_e10 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e10 + 12) )  // 复合条件判定（与/或）
        {
          v10 = sub_48FCA0();  // 自身座位下标查找（表 dword_99FF08）
          if ( v10 != -1 )
            sub_48FC30(v10, 255);  // 座位状态上报发包（op 94，表 dword_99FF08）
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 音效播放包装（非空判定）
        }
        fld_e14 = *(this + 14);  // this+56〔pCmdVecCap56(推断)〕
        if ( *(uint8_t *)(fld_e14 + 17) != 0 && dword_79BE34 == *(uint32_t *)(fld_e14 + 12) )  // 复合条件判定（与/或）
        {
          *(uint8_t *)(*(this + 13) + 16) = *(uint8_t *)(*(this + 13) + 16) == 0;  // this+52〔bAuraState(推断)〕
          sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 音效播放包装（非空判定）
        }
        v12 = 0;
        v14[0] = 1;
        v14[1] = 2;
        v14[2] = 0;
        while ( 1 )  // 条件循环
        {
          result = *(this + v14[v12] + 15);  // result=this+24 nPageMax
          if ( *(uint8_t *)(result + 17) != 0 && dword_79BE34 == *(uint32_t *)(result + 12) )  // 复合条件判定（与/或）
            break;  // 跳出循环/分支
          if ( ++v12 >= 3 )
            return result;  // result=this+24 nPageMax
        }
        *(uint8_t *)(*(this + 13) + 16) = 0;  // this+52〔bAuraState(推断)〕
        v13 = sub_48FCA0();  // 自身座位下标查找（表 dword_99FF08）
        if ( v13 != -1 )
          sub_48FC30(v13, v14[v12]);  // 座位状态上报发包（op 94，表 dword_99FF08）
        return (int)sub_432EA0("CLICK_BUTTON2", -1, 0, 0);  // 音效播放包装（非空判定）
      }
    }
  }
  return result;  // result=this+24 nPageMax
}



// ------------------------------------------------------------
// 0x49CD70 sub_49CD70 —— CLICK_BUTTON2 可见切换（+24 主件 + 22×槽号 联动移位）
//   +24 子控件 +16 可见标志变更时才执行；
//   sub_48FCA0 取当前槽号 ×22 → ·sub_69A5F0(MoveWindow) 把 +56/+52 两件移到 (603, v4+150)/(577, v4+164)，
//   并置 +36/+44 子件可见、清 +52/+56。
// ------------------------------------------------------------
int /*thiscall*/ sub_49CD70(uint32_t *this, char pszArg2)  // 实现：CLICK_BUTTON2 可见切换（+24 主件 + 22×槽号 联动移位）
{
  int result; // eax
  int v4; // edi

  result = *(this + 6);  // this+24〔nPageMax(推断)〕
  if ( *(uint8_t *)(result + 16) != pszArg2 )  // result=this+24 nPageMax
  {
    *(uint8_t *)(result + 16) = pszArg2;  // result=this+24 nPageMax
    if ( pszArg2 != 0 )  // 若 pszArg2 非 0
    {
      if ( sub_48FCA0() != -1 )  // 自身座位下标查找（表 dword_99FF08）
      {
        *(uint8_t *)(*(this + 14) + 16) = 1;  // this+56〔pCmdVecCap56(推断)〕
        *(uint8_t *)(*(this + 13) + 16) = 0;  // this+52〔bAuraState(推断)〕
      }
      v4 = 22 * sub_48FCA0();  // 自身座位下标查找（表 dword_99FF08）
      sub_69A5F0((uint32_t *)*(this + 14), 603, v4 + 150);  // 调 设位、sub_69A840 登记
      sub_69A5F0((uint32_t *)*(this + 13), 577, v4 + 164);  // 调 设位、sub_69A840 登记
      *(uint8_t *)(*(this + 13) + 16) = 0;  // this+52〔bAuraState(推断)〕
      *(uint8_t *)(*(this + 14) + 16) = 0;  // this+56〔pCmdVecCap56(推断)〕
      *(uint8_t *)(*(this + 9) + 16) = 1;  // this+36〔nStateWord36(推断)〕
      result = *(this + 11);  // this+44〔nExpireMs(推断)〕
      *(uint8_t *)(result + 16) = 1;  // result=this+44 nExpireMs
    }
  }
  return result;  // result=this+44 nExpireMs
}



// ------------------------------------------------------------
// 0x49CE00 sub_49CE00 —— 倒计时数字绘制（30000 - clock_now 拆 分/秒/毫秒 逐位）
//   v2 = 30000 - clock_now((dword_8F7A24+40)+36)，配 424/111 底图；
//   位图序号 = 43 + 数字（取 dword_99FCC8+20 对象 +208 图容器），分/秒/毫秒(0.1s) 各 1..2 位；
//   前导零位略过（数值 > 0 才画）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49CE00(uint32_t **this)  // 实现：倒计时数字绘制（30000 - clock_now 拆 分/秒/毫秒 逐位）
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
  fld_e8 = sub_418DD0(*(this + 8), 0x35u);  // fld_e8 = 调 sub_418DD0 返回值
  if ( fld_e8 != 0 )  // 若 fld_e8 非 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)fld_e8 + 152))(fld_e8, 424, 111, dword_79C0B0);  // 调虚槽 +152：效果通道 3
  v4 = *(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 208);  // nengine::CNSlider 全局实例
  v13 = v2 % 1000;
  v5 = v2 / 1000 % 60;
  v6 = v2 / 60000;
  if ( v6 > 0 )  // 若 v6 > 0
  {
    if ( v6 > 10 )  // 若 v6 > 10
    {
      pObj5 = sub_418DD0(v4, v6 / 10 + 43);  // pObj5 = 调 sub_418DD0 返回值
      if ( pObj5 != 0 )  // 若 pObj5 非 0
        (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(pObj5, 456, 118, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    }
    pObj4 = sub_418DD0(v4, v6 % 10 + 43);  // pObj4 = 调 sub_418DD0 返回值
    if ( pObj4 != 0 )  // 若 pObj4 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 470, 118, dword_79C0B0);  // 调虚槽 +152：效果通道 3
LABEL_11:  // 标签 LABEL_11（跳转合流点）
    pObj = sub_418DD0(v4, v5 / 10 + 43);  // pObj = 调 sub_418DD0 返回值
    if ( pObj != 0 )  // 若 pObj 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 504, 118, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    goto LABEL_13;
  }
  if ( v5 > 0 )  // 若 v5 > 0
  {
    if ( v5 >= 10 )  // 若 v5 >= 10
      goto LABEL_11;
LABEL_13:  // 标签 LABEL_13（跳转合流点）
    pObj3 = sub_418DD0(v4, v5 % 10 + 43);  // pObj3 = 调 sub_418DD0 返回值
    if ( pObj3 != 0 )  // 若 pObj3 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, 518, 118, dword_79C0B0);  // 调虚槽 +152：效果通道 3
  }
  pObj2 = sub_418DD0(v4, v13 / 100 + 43);  // pObj2 = 调 sub_418DD0 返回值
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 544, 118, dword_79C0B0);  // 调虚槽 +152：效果通道 3
  result = sub_418DD0(v4, v13 / 10 % 10 + 43);  // result = 调 sub_418DD0 返回值
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)result + 152))(result, 558, 118, dword_79C0B0);  // 调虚槽 +152：效果通道 3
  return result;
}



// ------------------------------------------------------------
// 0x49CFF0 sub_49CFF0 —— 窗口对象装配（+52 → sub_69C780/69C7B0；+40..228 字段组初始化）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49CFF0(int this, void *Block)  // 实现：窗口对象装配（+52 → sub_69C780/69C7B0；+40..228 字段组初始化）
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

  *(uint32_t *)(this + 4) = Block;  // this+4〔宿主对象〕等 2 字段
  *(uint32_t *)(this + 28) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 100);  // this+28〔pPanelVec(推断)〕等 2 字段
  *(uint32_t *)(this + 32) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 196);  // this+32〔nHeight(推断)〕等 2 字段
  pMem = operator new(0x6Cu);  // new(108 字节) 分配对象
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    fld_20 = sub_43C250(pMem, *(uint32_t *)(this + 32), 45);  // nengine::CNFrame 构造
  else  // 否则分支
    fld_20 = nullptr;  // fld_20 = 空指针
  *(uint32_t *)(this + 24) = fld_20;  // this+24〔nPageMax(推断)〕等 2 字段
  *((uint32_t *)fld_20 + 17) = this;
  pMem2 = operator new(0x68u);  // new(104 字节) 分配对象
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v6 = sub_426BD0(pMem2);  // nengine::IControl 构造
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  *(uint32_t *)(this + 36) = v6;  // this+36〔nStateWord36(推断)〕等 2 字段
  sub_69A840(v6);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem3 = operator new(0x6Cu);  // new(108 字节) 分配对象
  if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    fld_1C = sub_43C250(pMem3, *(uint32_t *)(this + 28), 75);  // nengine::CNFrame 构造
  else  // 否则分支
    fld_1C = nullptr;  // fld_1C = 空指针
  *(uint32_t *)(this + 52) = fld_1C;  // this+52〔bAuraState(推断)〕等 2 字段
  sub_69A840(fld_1C);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v29 = 2;
  Blocka = (int *)&unk_6CBA30;
  pThis_3C = (uint32_t *)(this + 60);  // this+60〔nFadeValue60(推断)〕等 2 字段
  do  // do-while 循环体起点
  {
    pMem4 = operator new(0x84u);  // new(132 字节) 分配对象
    if ( pMem4 != nullptr )  // 若 pMem4 有效（非空）
    {
      v27 = *Blocka;
      fld_1C2 = *(uint32_t *)(this + 28);  // fld_1C2 = 读 this+28
      v26 = Blocka[2];  // v26 = 取 Blocka[2]
      v25 = Blocka[1];  // v25 = 取 Blocka[1]
      sub_426BD0(pMem4);  // nengine::IControl 构造
      *(uint32_t *)pMem4 = &nengine::CNButton::`vftable';
      sub_69C780(v9);  // 调 初始化 → ·vmt20(nArg2..nArg8
      sub_69C7B0(v24, v27, v25, v26, v27, 0, 0);
      v10 = v9;
    }
    else  // 否则分支
    {
      v10 = nullptr;  // v10 = 空指针
    }
    *v28 = v10;
    sub_69A5F0(v10, 2, v29);  // 调 设位、sub_69A840 登记
    sub_69A840(*v28);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
    v11 = (int)(Blocka + 3) < (int)&unk_6CBA54;
    ++v28;
    Blocka += 3;  // Blocka 前进 3
    v29 += 13;
  }
  while ( v11 );  // 条件循环
  v12 = operator new(0x84u);  // new(132 字节) 分配对象
  v13 = v12;
  if ( v12 != nullptr )  // 若 v12 有效（非空）
  {
    Blockb = *(void **)(this + 28);  // this+112〔pHostComp112〕
    sub_426BD0(v12);  // nengine::IControl 构造
    *v13 = &nengine::CNButton::`vftable';
    sub_69C780(pMem52);  // 调 初始化 → ·vmt20(nArg2..nArg8
    sub_69C7B0(Blockb, 4, 5, 6, 4, 0, 0);  // Blockb=this+112 pHostComp112
  }
  else  // 否则分支
  {
    pMem52 = nullptr;  // pMem52 = 空指针
  }
  *(uint32_t *)(this + 56) = pMem52;  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  sub_69A840(pMem52);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem6 = operator new(0x84u);  // new(132 字节) 分配对象
  pMem62 = pMem6;
  if ( pMem6 != nullptr )  // 若 pMem6 有效（非空）
  {
    Blockc = *(void **)(this + 32);  // this+128〔szStatusKeyBuf(推断)〕
    sub_426BD0(pMem6);  // nengine::IControl 构造
    *pMem62 = &nengine::CNButton::`vftable';
    sub_69C780(v15);  // 调 初始化 → ·vmt20(nArg2..nArg8
    sub_69C7B0(Blockc, 46, 47, 48, 46, 0, 0);  // Blockc=this+128 szStatusKeyBuf
  }
  else  // 否则分支
  {
    v15 = nullptr;  // v15 = 空指针
  }
  *(uint32_t *)(this + 40) = v15;  // this+40〔bStateSub40(推断)〕等 2 字段
  v15[17] = this;
  sub_69A5F0(*(uint32_t **)(this + 40), 86, 388);  // 调 设位、sub_69A840 登记
  sub_69A840(*(uint32_t *)(this + 40));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v16 = operator new(0x84u);  // new(132 字节) 分配对象
  v17 = v16;
  if ( v16 != nullptr )  // 若 v16 有效（非空）
  {
    Blockd = *(void **)(this + 28);  // this+112〔pHostComp112〕
    sub_426BD0(v16);  // nengine::IControl 构造
    *v17 = &nengine::CNButton::`vftable';
    sub_69C780(pMem72);  // 调 初始化 → ·vmt20(nArg2..nArg8
    sub_69C7B0(Blockd, 46, 47, 48, 46, 0, 0);  // Blockd=this+112 pHostComp112
    pMem722 = pMem72;
  }
  else  // 否则分支
  {
    pMem722 = nullptr;  // pMem722 = 空指针
  }
  *(uint32_t *)(this + 44) = pMem722;  // this+44〔nExpireMs(推断)〕等 2 字段
  sub_69A5F0(pMem722, 110, 332);  // 调 设位、sub_69A840 登记
  sub_69A840(*(uint32_t *)(this + 44));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  pMem8 = operator new(0x68u);  // new(104 字节) 分配对象
  if ( pMem8 != nullptr )  // 若 pMem8 有效（非空）
    v20 = sub_426BD0(pMem8);  // nengine::IControl 构造
  else  // 否则分支
    v20 = nullptr;  // v20 = 空指针
  *(uint32_t *)(this + 72) = v20;  // this+72〔nSnapshot72(推断)〕等 2 字段
  *((uint32_t *)v20 + 17) = this;  // v20[17] = this
  sub_69A840(*(uint32_t *)(this + 72));  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  *(uint8_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  *(uint8_t *)(this + 77) = 0;  // this+77〔bGuildFlagB〕
  *(uint8_t *)(this + 78) = 0;  // this+78〔bGuildFlagC〕
  *(uint8_t *)(this + 79) = 0;
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 116) = 0;  // this+116〔会话上下文〕
  *(uint32_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
  *(uint32_t *)(this + 124) = 0;  // this+124〔pAuraAnim(推断)〕
  *(uint32_t *)(this + 92) = 6;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint32_t *)(this + 96) = 12;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint32_t *)(this + 104) = 1600;  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 124) = dword_99FCCC;  // this+124〔pAuraAnim(推断)〕
  *(uint32_t *)(this + 80) = -16777216;  // this+80〔nAuraStage(推断)〕
  *(uint8_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint8_t *)(this + 129) = 0;  // this+516〔bAbilityFlag(推断)〕
  *(uint8_t *)(this + 130) = 0;  // this+520〔nAbilityDur(推断)〕
  *(uint8_t *)(this + 131) = 0;  // this+524〔fAbilityScale(推断)〕
  *(uint32_t *)(this + 140) = 0;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 144) = 6;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 148) = 12;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 152) = 0;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 1600;  // this+156〔nAdd156(推断)〕
  *(uint32_t *)(this + 160) = 0;  // this+160〔fAdd160(推断)〕
  *(uint32_t *)(this + 164) = 0;  // this+164〔fAdd164(推断)〕
  *(uint32_t *)(this + 168) = 0;  // this+168〔pAppendVec(推断)〕等 2 字段
  *(uint32_t *)(this + 172) = 0;  // this+172〔pAppendVecEnd(推断)〕等 2 字段
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint32_t *)(this + 176) = dword_99FCCC;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint32_t *)(this + 156) = 72;  // this+156〔nAdd156(推断)〕
  *(uint32_t *)(this + 140) = 1;  // this+140〔nAdd140(推断)〕
  *(uint8_t *)(this + 180) = 0;  // this+180〔nRadius(推断)〕
  *(uint8_t *)(this + 181) = 0;  // this+724〔fVal724(推断)〕
  *(uint8_t *)(this + 182) = 0;
  *(uint8_t *)(this + 183) = 0;
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint32_t *)(this + 196) = 6;
  *(uint32_t *)(this + 200) = 12;  // this+200〔nMainState(推断)〕
  *(uint32_t *)(this + 204) = 0;  // this+204〔pSubAnim204(推断)〕
  *(uint32_t *)(this + 208) = 1600;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 212) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 216) = 0;  // this+216〔bField216(推断)〕
  *(uint32_t *)(this + 220) = 0;  // this+220〔nSnapDst220(推断)〕
  *(uint32_t *)(this + 224) = 0;  // this+224〔nSnapDst224(推断)〕
  *(uint32_t *)(this + 228) = 0;  // this+228〔nSnapDst228(推断)〕
  fld_18 = *(uint32_t **)(this + 24);  // fld_18 = 读 this+24
  *(uint32_t *)(this + 228) = dword_99FCCC;  // this+228〔nSnapDst228(推断)〕
  *(uint32_t *)(this + 208) = 156;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 192) = 1;  // this+192〔nDlgId(推断)〕
  *(uint8_t *)(this + 182) = 1;
  *(uint32_t *)(this + 184) = -16777216;  // this+184〔bSingleTarget(推断)〕
  result = sub_69A5F0(fld_18, 365, 0);  // result = 调 sub_69A5F0 返回值
  fld_182 = *(uint32_t *)(this + 24);  // fld_182 = 读 this+24
  if ( *(uint8_t *)(fld_182 + 16) != 0 )  // fld_182=this+24 页数上限
    *(uint8_t *)(fld_182 + 16) = 0;  // fld_182=this+24 页数上限
  return result;
}


// ------------------------------------------------------------
// 0x49D4B0 sub_49D4B0 —— 窗口动画驱动（+45 部件、sub_49CE00 图像、sub_578E80）
// ------------------------------------------------------------
void /*userpurge*/ sub_49D4B0(uint32_t *pArg1@<ecx>, uint32_t *uArg2@<esi>, int nArg3)  // 实现：窗口动画驱动（+45 部件、sub_49CE00 图像、sub_578E80）
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
  if ( dword_99FF08 != 0 )  // 若 dword_99FF08 非 0
  {
    v5 = *(uint32_t *)(pArg1[1] + 4);
    if ( nArg3 == pArg1[6] )
    {
      if ( v5 == 0 )  // 若 v5 为 0
      {
        v6 = dword_99FF08 + 4;
        pObj4 = sub_418DD0(41);  // pObj4 = 调 sub_418DD0 返回值
        if ( pObj4 != 0 )  // 若 pObj4 非 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj4 + 152))(pObj4, 383, 57, dword_79C0B0);  // 调虚槽 +152：效果通道 3
        pObj6 = sub_418DD0(54);  // pObj6 = 调 sub_418DD0 返回值
        if ( pObj6 != 0 )  // 若 pObj6 非 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj6 + 152))(pObj6, 387, 83, dword_79C0B0);  // 调虚槽 +152：效果通道 3
        pObj2 = sub_418DD0(35);  // pObj2 = 调 sub_418DD0 返回值
        if ( pObj2 != 0 )  // 若 pObj2 非 0
          (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj2 + 152))(pObj2, 394, 84, dword_79C0B0);  // 调虚槽 +152：效果通道 3
        (*(void (/*thiscall*/ **)(int, uint32_t *))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0, pArg12 + 45);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
        v46 = *(uint32_t *)dword_79C0B0;  // 默认字体/绘制资源
        v10 = sub_48FE30(dword_99FF082);  // 组装显示串（串表名 + 表项串 #编号）
        (*(void (/*cdecl*/ **)(int, int, int, int, int))(v46 + 80))(dword_79C0B0, 424, 27, -1, v10);  // 默认字体/绘制资源
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
        if ( *(uint32_t *)(*(uint32_t *)(dword_8F7A24 + 40) + 32) == 1 )  // 登录/选区管理器
          sub_49CE00(pArg12);  // 倒计时数字绘制（30000 - clock_now 拆 分/秒/毫秒 逐位）
        v47 = *(uint32_t *)(pArg12[6] + 20) + 30;
        v11 = 0;
        v12 = 1048644 - v6;
        v13 = (uint32_t *)(v6 + 4);
        v43 = 0;
        v44 = (int *)(v6 + 4);
        v42 = 1048644 - v6;
        v41 = -4 - v6;
        while ( 1 )  // 条件循环
        {
          v40 = (char *)v13 + v12;
          v14 = dword_790BC8 + dword_790BCC * *(uint32_t *)((char *)pArg12 + (uint32_t)v13 + v12 - 1048416);
          if ( *v13 != 255 )
          {
            v15 = sub_578E80(v11);  // v15 = 调 sub_578E80 返回值
            v16 = v15;
            if ( v15 != 0 )  // 若 v15 非 0
            {
              pObj = sub_42B340(v15);  // 虚拟角色惰性创建（0x294 字节）
              (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t *))(*(uint32_t *)pObj + 384))(  // 调虚槽 +384：槽数组 getter（+348 起，越界返回 0）
                pObj,
                v47,
                v14,
                16,
                16,
                1065353216,
                uArg2);
              v18 = *v44;
              if ( *v44 == 1 || v18 == 2 )  // 若 v18 == 2
              {
                pObj7 = sub_418DD0(v18 + 73);  // pObj7 = 调 sub_418DD0 返回值
                if ( pObj7 != 0 )  // 若 pObj7 非 0
                  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj7 + 152))(pObj7, v47, v14, dword_79C0B0);  // 调虚槽 +152：效果通道 3
              }
              uArg2 = pArg12 + 32;
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 72))(dword_79C0B0);  // 调虚槽 +72：CNRDPrivateStoreWindow_Display__vmt48 槽（4BE520…
              if ( *(uint32_t *)(v16 + 40) < 0x10u )
                v20 = v16 + 20;
              else  // 否则分支
                v20 = *(uint32_t *)(v16 + 20);
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
                dword_79C0B0,  // 默认字体/绘制资源
                v47 + 55,
                v14 + 4,
                -9795152,
                v20);
              if ( *(uint32_t *)(v16 + 40) < 0x10u )
                v21 = v16 + 20;
              else  // 否则分支
                v21 = *(uint32_t *)(v16 + 20);
              v22 = v14 + 3;
              (*(void (/*cdecl*/ **)(int, int, int, int, int))(*(uint32_t *)dword_79C0B0 + 80))(  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
                dword_79C0B0,  // 默认字体/绘制资源
                v47 + 55,
                v14 + 3,
                -16179413,
                v21);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B0 + 76))(dword_79C0B0);  // 调虚槽 +76：CNRDPrivateStoreWindow__vmt4C 槽（542940 + 48502…
              v23 = *v44;
              if ( *v44 == 1 || v23 == 2 )  // 若 v23 == 2
                pObj5 = sub_418DD0(v23 + 99);  // pObj5 = 调 sub_418DD0 返回值
              else  // 否则分支
                pObj5 = sub_418DD0(112);  // pObj5 = 调 sub_418DD0 返回值
              if ( pObj5 != 0 )  // 若 pObj5 非 0
                (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj5 + 152))(  // 调虚槽 +152：效果通道 3
                  pObj5,
                  v47 + 180,
                  v14 + 2,
                  dword_79C0B0);  // 默认字体/绘制资源
              dword_8F85202 = dword_8F8520;  // 会话/UDP 管理器
              if ( *(uint32_t *)((char *)sub_656710() + (uint32_t)v44 + v41) != -1 && *(uint32_t *)&v40[dword_8F85202] != 0 )  // 取全局单例地址（返回 unk_9BD5D0）
              {
                pObj3 = sub_418DD0(44);  // pObj3 = 调 sub_418DD0 返回值
                if ( pObj3 != 0 )  // 若 pObj3 非 0
                  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj3 + 152))(pObj3, v47 + 130, v22, dword_79C0B0);  // 调虚槽 +152：效果通道 3
              }
              pArg12 = pArg1;
            }
          }
          v11 = v43 + 1;
          v13 = v44 + 1;
          v27 = ++v43 < 8;
          ++v44;
          if ( !v27 )
            break;  // 跳出循环/分支
          v12 = v42;
        }
      }
    }
    else  // 否则分支
    {
      v28 = pArg1[10];  // v28 = 取 pArg1[10]
      if ( nArg3 != v28 || v5 != 0 )  // 若 nArg3 != v28 与/或 v5 != 0
      {
        if ( nArg3 == pArg1[18] && v5 == 0 )  // 若 nArg3 == pArg1 与/或 v5 == 0
        {
          if ( (uint8_t)sub_43BCB0(pArg1[11]) != 0 )  // 焦点窗口判定（三选）
          {
            v32 = sub_422E70(449);  // v32 = 调 sub_422E70 返回值
            sub_4649B0(510, 321, -1, -16777216, 2, v32, 0, 0, 1600, 0);  // 带框文本上屏（静态一次性初始化）
          }
          else if ( (uint8_t)sub_43BCB0(pArg12[14]) != 0 )  // 焦点窗口判定（三选）
          {
            v33 = sub_48FD20(dword_99FF082);  // 槽占用查询（跳过 255 取首槽）
            v34 = pArg12[14];  // v34 = 取 pArg12[14]
            v35 = *(uint32_t *)(v34 + 24);
            v36 = *(uint32_t *)(v34 + 20);
            if ( v33 != 0 )  // 若 v33 非 0
              v37 = sub_422E70(452);  // v37 = 调 sub_422E70 返回值
            else  // 否则分支
              v37 = sub_422E70(453);  // v37 = 调 sub_422E70 返回值
            sub_4649B0(v36 - 10, v35, -1, -16777216, 2, v37, 0, 0, 1600, 0);  // 带框文本上屏（静态一次性初始化）
          }
          else if ( (uint8_t)sub_43BCB0(pArg12[17]) != 0 )  // 焦点窗口判定（三选）
          {
            v38 = sub_422E70(455);  // v38 = 调 sub_422E70 返回值
            sub_4649B0(505, 202, -1, -16777216, 2, v38, 0, 0, 1600, 0);  // 带框文本上屏（静态一次性初始化）
          }
        }
      }
      else if ( *(uint8_t *)(v28 + 17) != 0 && dword_79BE3C == *(uint32_t *)(v28 + 12) )  // 动画对象指针(帧同步比对基准 C)
      {
        v29 = *(uint32_t *)(v28 + 24);
        v30 = *(uint32_t *)(v28 + 20);
        v31 = sub_418DD0(87);  // v31 = 调 sub_418DD0 返回值
        sub_40FC80(v30 + 24, v29 - 33, v31);  // 贴图转发（目标对象虚发 +152(this, x, y)）
      }
    }
  }
}


// ------------------------------------------------------------
// 0x49D920 sub_49D920 —— 房间列表刷新（按差值排序建临时链 + 收集进 +8 数组 + 释放节点）
//   this+24 子件 +16 使能时执行：清空 this+8 指针数组，
//   sub_429830(word_77F804) 取本场景对象、sub_41A5E0(+53) 读值、sub_4A2CF0 建临时链；
//   按 abs(值差) 递增插入（sub_52DAA0 建节点 + sub_430C80 收集）后释放全部临时节点。
// ------------------------------------------------------------
void /*thiscall*/ sub_49D920(uint32_t *this)  // 实现：房间列表刷新（按差值排序建临时链 + 收集进 +8 数组 + 释放节点）
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

  if ( *(uint8_t *)(*(this + 6) + 16) != 0 )  // this+24〔nPageMax(推断)〕
  {
    fld_e3 = (void *)*(this + 3);  // this+12〔nSkillRec12(推断)〕
    pThis_2 = this + 2;
    pThis_22 = this + 2;
    if ( fld_e3 != nullptr )  // 若 fld_e3 有效（非空）
      j__free(fld_e3);  // fld_e3=this+12 nSkillRec12
    pThis_2[1] = 0;
    pThis_2[2] = 0;
    pThis_2[3] = 0;
    v30 = sub_429830((uint16_t)word_77F804);  // 表按键查找（uint16）
    v29 = sub_41A5E0(v30 + 53);  // crypt4byte 解密校验（·0x41A590 逆运算）
    v3 = (uint32_t *)sub_4A2CF0(v23);  // v3 = 调 sub_4A2CF0 返回值
    v24 = v3;
    v25 = 0;
    v4 = *(int ***)(dword_8F8500 + 8);  // 对象链表头
    v5 = *v4;
    v6 = (int **)(dword_8F8500 + 8);  // 对象链表头
    v7 = *v4 == (int *)v4;
    v31 = 0;
    v28 = dword_8F8500 + 8;  // 对象链表头
    if ( !v7 )
    {
      do  // do-while 循环体起点
      {
        v8 = v5[4];  // v8 = 取 v5[4]
        if ( *(uint32_t *)(v8 + 68) == 0 && v8 != v30 )  // 若 v8 != v30
        {
          v9 = sub_41A5E0(v8 + 53);  // crypt4byte 解密校验（·0x41A590 逆运算）
          v10 = (uint32_t *)*v24;
          for ( i = abs32(v29 - v9); v10 != v24; v10 = (uint32_t *)*v10 )  // 遍历循环
          {
            if ( v10[2] >= i )
              break;  // 跳出循环/分支
          }
          v26[0] = i;
          v22 = v10[1];  // v22 = 取 v10[1]
          v26[1] = *(uint16_t *)(v5[4] + 4);
          v12 = sub_52DAA0(v10, v22, v26);  // v12 = 调 sub_52DAA0 返回值
          sub_468240(1);  // list 元素数预留（溢出抛错）
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
            for ( j = (int *)v5[1]; *((uint8_t *)j + 21) == 0; j = (int *)j[1] )  // 遍历循环
            {
              if ( v5 != (int *)j[2] )
                break;  // 跳出循环/分支
              v5 = j;
            }
            v5 = j;
          }
          else  // 否则分支
          {
            v5 = (int *)v5[2];
            for ( k = *v13; *((uint8_t *)k + 21) == 0; k = (int *)*k )  // 遍历循环
              v5 = k;
          }
        }
      }
      while ( v5 != *v6 );  // 条件循环
    }
    v16 = (uint32_t *)*v3;
    if ( (uint32_t *)*v3 != v3 )
    {
      do  // do-while 循环体起点
      {
        v17 = pThis_2[1];  // v17 = 取 pThis_2[1]
        if ( v17 != 0 )  // 若 v17 非 0
          v18 = (pThis_2[2] - v17) >> 2;
        else  // 否则分支
          v18 = 0;
        if ( v17 != 0 && v18 < (pThis_2[3] - v17) >> 2 )  // 若 v17 != 0
        {
          v19 = (uint32_t *)pThis_2[2];
          *v19 = v16[3];
          pThis_2[2] = v19 + 1;
        }
        else  // 否则分支
        {
          sub_430C80((void *)pThis_2[2], 1, (int)(v16 + 3));  // uint32 vector 区间插入（同值填充）
        }
        v16 = (uint32_t *)*v16;
      }
      while ( v16 != v24 );  // 条件循环
      v3 = v24;
    }
    v20 = (uint32_t *)*v3;
    v7 = *v3 == (uint32_t)v3;
    *v3 = v3;
    v3[1] = v3;
    if ( !v7 )
    {
      do  // do-while 循环体起点
      {
        v21 = (uint32_t *)*v20;
        j__free(v20);  // 调 j__free（堆释放）
        v3 = v24;
        v20 = v21;
      }
      while ( v21 != v24 );  // 条件循环
    }
    j__free(v3);  // 调 j__free（堆释放）
  }
}


// ------------------------------------------------------------
// 0x49DB10 sub_49DB10 —— 窗口字段清零（+4、+36..+56 子件槽、+116/+120）
//   配套 ·sub_49DB30 回收 +48/+52 与三连槽子件。
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB10(uint32_t *this)  // 实现：窗口字段清零（+4、+36..+56 子件槽、+116/+120）
{
  *(this + 29) = 0;  // this+116〔会话上下文〕
  *(this + 30) = 0;  // this+120〔pAnimObj〕
  *(this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  *(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  *(this + 14) = 0;  // this+56〔pCmdVecCap56(推断)〕
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 9) = 0;  // this+36〔nStateWord36(推断)〕
  *(this + 10) = 0;  // this+40〔bStateSub40(推断)〕
  *(this + 11) = 0;  // this+44〔nExpireMs(推断)〕
  return 0;
}



// ------------------------------------------------------------
// 0x49DB30 sub_49DB30 —— 窗口子件批量析构（+48/+52 + 3 连 +36..+44）
//   逐 vt+4(1) 销毁后清槽（对照 ·sub_49DB10 的字段清零与 ·sub_49DB80 的 +56 图链）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB30(uint32_t *this)  // 实现：窗口子件批量析构（+48/+52 + 3 连 +36..+44）
{
  int (/*thiscall*/ ***fld_e12)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e13)(uint32_t, int); // ecx
  uint32_t *pThis_9; // esi
  int i; // edi

  fld_e12 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
  if ( fld_e12 != nullptr )  // 若 fld_e12 有效（非空）
    result = (**fld_e12)(fld_e12, 1);  // 调 fld_e12 的虚函数（vt+0）
  fld_e13 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 13);  // this+52〔bAuraState(推断)〕
  *(this + 12) = 0;  // this+48〔pCmdVecBegin48(推断)〕
  if ( fld_e13 != nullptr )  // 若 fld_e13 有效（非空）
    result = (**fld_e13)(fld_e13, 1);  // 调 fld_e13 的虚函数（vt+0）
  *(this + 13) = 0;  // this+52〔bAuraState(推断)〕
  pThis_9 = this + 9;
  for ( i = 3; i != 0; --i )  // 循环：i 从 3 递减到 0
  {
    if ( *pThis_9 != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_9)(*pThis_9, 1);
    *pThis_9++ = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49DB80 sub_49DB80 —— 数字底板透明度刷新（+56 图链 0/3 两图 vt+128 十参）
//   Alpha 取参数低字节左移 24（|0xFFFFFF 补白）；
//   第一图 (0,0) 用钳位值（>= 220 → -36 即 220）、第二图 (264,12) 用原值。
// ------------------------------------------------------------
int /*thiscall*/ sub_49DB80(uint32_t **this, int nArg2)  // 实现：数字底板透明度刷新（+56 图链 0/3 两图 vt+128 十参）
{
  uint8_t nArg22; // bl
  int fld_e14; // eax
  int result; // eax

  nArg22 = nArg2;
  if ( nArg2 >= 220 )  // 若 nArg2 >= 220
    nArg22 = -36;
  fld_e14 = sub_418DD0(*(this + 14), 0);  // fld_e14 = 调 sub_418DD0 返回值
  if ( fld_e14 != 0 )  // 若 fld_e14 非 0
    (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, int, int, int, uint32_t, int, int, int))(*(uint32_t *)fld_e14 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      fld_e14,
      0,
      0,
      dword_79C0B0,  // 默认字体/绘制资源
      1065353216,
      1065353216,
      0,
      (nArg22 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  result = sub_418DD0(*(this + 14), 3u);  // result = 调 sub_418DD0 返回值
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
             result,
             264,
             12,
             dword_79C0B0,  // 默认字体/绘制资源
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
int /*thiscall*/ sub_49DC30(uint32_t *this)  // 实现：M_RESULT 事件处理（sub_432EE0/sub_65DC70 → sub_49DCF0）
{
  int64_t pThis_2; // rax
  int v3; // edi
  int pObj; // eax

  pThis_2 = 1717986919LL * (sub_699000((int)(this + 2)) % 640);  // 【clock_now(clk)】
  v3 = (SHIDWORD(pThis_2) >> 5) + (HIDWORD(pThis_2) >> 31);  // 调 SHIDWORD（取 64 位值高 32 位(带符号)）
  if ( v3 < 8 )  // 若 v3 < 8
  {
    sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    pObj = sub_418DD0(v3 + 15);  // pObj = 调 sub_418DD0 返回值
    if ( pObj != 0 )  // 若 pObj 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pObj + 152))(pObj, 43, 328, dword_79C0B0);  // 调虚槽 +152：效果通道 3
    LODWORD(pThis_2) = sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
    if ( v3 == 0 )  // 若 v3 为 0
    {
      LODWORD(pThis_2) = *(this + 37);  // this+148〔fAdd148(推断)〕
      if ( (uint32_t)pThis_2 == 0 )
      {
        *(this + 37) = *(this + 32) + *(this + 33) + *(this + 34) + *(this + 35) + *(this + 36);  // this+148〔fAdd148(推断)〕等 6 字段
        LODWORD(pThis_2) = sub_432EA0("RESULT_FLASH", -1, 0, 0);  // 音效播放包装（非空判定）
      }
    }
  }
  return pThis_2;
}



// ------------------------------------------------------------
// 0x49DCF0 sub_49DCF0 —— 结算段复位与时长装载（+128=5000、+132/136/140=3000/2000/1000、+144=30000）
//   先清 +128..+148 与 +152（Alpha=255）、+73/+74 清零，·sub_432FA0 停止旧段；
//   时钟 this+60 经 ·0x698F90 复位；+124 置 254（刻度基准【推断】）。
// ------------------------------------------------------------
char /*thiscall*/ sub_49DCF0(int this)  // 实现：结算段复位与时长装载（+128=5000、+132/136/140=3000/2000/1000、+144=30000）
{
  uint32_t *pThis_80; // edi
  char result; // al

  pThis_80 = (uint32_t *)(this + 128);  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 140) = 0;  // this+140〔nAdd140(推断)〕
  sub_432FA0();  // srand 播种
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *pThis_80 = 0;  // pThis_80=this+128 szStatusKeyBuf
  pThis_80[1] = 0;  // pThis_80=this+128 szStatusKeyBuf
  pThis_80[2] = 0;  // pThis_80=this+128 szStatusKeyBuf
  pThis_80[3] = 0;  // pThis_80=this+128 szStatusKeyBuf
  *(uint32_t *)(this + 148) = 0;  // this+148〔fAdd148(推断)〕
  *(uint32_t *)(this + 124) = 0;  // this+124〔pAuraAnim(推断)〕
  *(uint32_t *)(this + 152) = 255;  // this+152〔nAdd152(推断)〕等 2 字段
  *(uint8_t *)(this + 73) = 0;  // this+73〔szDigitalName(推断)〕等 2 字段
  *(uint8_t *)(this + 74) = 0;  // this+74〔bResetB74(推断)〕等 2 字段
  result = sub_698F90(this + 60, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *pThis_80 = 5000;  // pThis_80=this+128 szStatusKeyBuf
  *(uint32_t *)(this + 144) = 30000;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 3000;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 136) = 2000;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 140) = 1000;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 124) = 254;  // this+124〔pAuraAnim(推断)〕
  return result;
}



// ------------------------------------------------------------
// 0x49DD80 sub_49DD80 —— 数字底板双图交替落位（13/14 号，按 nArg2 阈值换序）
//   Alpha = this+152 高字节（|0xFFFFFF）；
//   nArg2 >= 80 时先画 14 号 (304,108) 再画 13 号 (315,108)，否则相反（13 → 14），两图同 Alpha。
// ------------------------------------------------------------
int /*thiscall*/ sub_49DD80(int this, int nArg2)  // 实现：数字底板双图交替落位（13/14 号，按 nArg2 阈值换序）
{
  int fld_98; // edi
  uint32_t *fld_38; // ecx
  int v5; // edi
  int pObj; // eax
  int pObj2; // eax
  int fld_982; // edi
  int result; // eax
  unsigned int v10; // [esp-4h] [ebp-Ch]

  fld_98 = *(uint8_t *)(this + 152);  // fld_98 = 读 this+152
  fld_38 = *(uint32_t **)(this + 56);  // fld_38 = 读 this+56
  v5 = (fld_98 << 24) | 0xFFFFFF;  // fld_98=this+152 第 4 组·+886 增量
  if ( nArg2 >= 80 )  // 若 nArg2 >= 80
  {
    pObj2 = sub_418DD0(fld_38, 0xEu);  // pObj2 = 调 sub_418DD0 返回值
    if ( pObj2 != 0 )  // 若 pObj2 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        pObj2,
        304,
        108,
        dword_79C0B0,  // 默认字体/绘制资源
        1065353216,
        1065353216,
        0,
        v5,
        1333788672,
        1333788672);
    v10 = 13;
  }
  else  // 否则分支
  {
    pObj = sub_418DD0(fld_38, 0xDu);  // pObj = 调 sub_418DD0 返回值
    if ( pObj != 0 )  // 若 pObj 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        pObj,
        304,
        108,
        dword_79C0B0,  // 默认字体/绘制资源
        1065353216,
        1065353216,
        0,
        v5,
        1333788672,
        1333788672);
    v10 = 14;
  }
  fld_982 = (*(uint8_t *)(this + 152) << 24) | 0xFFFFFF;  // this+152〔nAdd152(推断)〕等 2 字段
  result = sub_418DD0(*(uint32_t **)(this + 56), v10);  // result = 调 sub_418DD0 返回值
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
             result,
             315,
             108,
             dword_79C0B0,  // 默认字体/绘制资源
             1065353216,
             1065353216,
             0,
             fld_982,  // fld_982=this+152 nAdd152
             1333788672,
             1333788672);
  return result;
}



// ------------------------------------------------------------
// 0x49DE70 sub_49DE70 —— 名次星标绘制（四格 6..9 号 + 5/10 号收尾）
//   每格 46 间距：图 4 (166, 160+46i) 与图 6+i (180, 166+46i)，各以 ·0x491530/·0x491630 变换包裹；
//   收尾 5 号 (113,349) 与 10 号 (180, v2+170)；Alpha 取参数低字节，>= 150 时钳位 -106（即 150）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49DE70(void *this, int nArg2)  // 实现：名次星标绘制（四格 6..9 号 + 5/10 号收尾）
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
  for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
  {
    sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
    nArg22 = nArg2;
    if ( nArg2 >= 150 )  // 若 nArg2 >= 150
      nArg22 = -106;
    pObj = sub_418DD0(4);  // pObj = 调 sub_418DD0 返回值
    if ( pObj != 0 )  // 若 pObj 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        pObj,
        166,
        v2 + 160,
        dword_79C0B0,  // 默认字体/绘制资源
        1065353216,
        1065353216,
        0,
        (nArg22 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
    pObj3 = sub_418DD0(v10[i]);  // pObj3 = 调 sub_418DD0 返回值
    if ( pObj3 != 0 )  // 若 pObj3 非 0
      (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj3 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
        pObj3,
        180,
        v2 + 166,
        dword_79C0B0,  // 默认字体/绘制资源
        1065353216,
        1065353216,
        0,
        ((uint8_t)nArg2 << 24) | 0xFFFFFF,
        1333788672,
        1333788672);
    v2 += 46;
  }
  sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
  nArg23 = nArg2;
  if ( nArg2 >= 150 )  // 若 nArg2 >= 150
    nArg23 = -106;
  pObj2 = sub_418DD0(5);  // pObj2 = 调 sub_418DD0 返回值
  if ( pObj2 != 0 )  // 若 pObj2 非 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      pObj2,
      113,
      349,
      dword_79C0B0,  // 默认字体/绘制资源
      1065353216,
      1065353216,
      0,
      (nArg23 << 24) | 0xFFFFFF,
      1333788672,
      1333788672);
  sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
  result = sub_418DD0(10);  // result = 调 sub_418DD0 返回值
  if ( result != 0 )  // 若结果非 0（成功）
    return (*(int (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)result + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
             result,
             180,
             v2 + 170,
             dword_79C0B0,  // 默认字体/绘制资源
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
int /*thiscall*/ sub_49E050(uint32_t *this, int nArg2)  // 实现：M_RESULT 演出（结算上下文 sub_65DC70、音效 sub_432EA0）
{
  int pThis_2; // ecx
  int result; // eax
  int i; // esi

  pThis_2 = (int)(this + 2);  // this+8〔nSkillRec8(推断)〕
  *(this + 1) = nArg2;  // this+4〔宿主对象〕
  *(uint8_t *)(pThis_2 + 13) = 0;  // pThis_2=this+8 nSkillRec8
  *(uint8_t *)(pThis_2 + 14) = 0;  // pThis_2=this+8 nSkillRec8
  sub_698F90(pThis_2, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( *(this + 1) != 0 )  // this+4〔宿主对象〕
  {
    if ( nArg2 == 1 )  // 若 nArg2 == 1
    {
      *(uint8_t *)(*(this + 12) + 16) = 0;  // this+48〔pCmdVecBegin48(推断)〕
      for ( i = 0; i < 4; ++i )  // 循环：i 从 0 递增到 4
        result = sub_432EE0(i);  // 音效 TAG 查询包装
    }
    else  // 否则分支
    {
      if ( *(uint8_t *)(*(this + 12) + 16) == 0 )  // this+48〔pCmdVecBegin48(推断)〕
      {
        sub_65DC70(lpCriticalSection);  // FSOUND 全停：50 个 48B 通道槽逐个 sub_65D8B0 停止，再摘 +2560 处播放链所有结点
        sub_432EA0("M_RESULT", -1, 0, 0);  // 音效播放包装（非空判定）
      }
      result = *(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
      *(uint8_t *)(result + 16) = 1;  // result=this+48 pCmdVecBegin48
    }
  }
  else  // 否则分支
  {
    sub_49DCF0((int)this);  // 结算段复位与时长装载（+128=5000、+132/136/140=3000/2000/1000、+144=30000）
    result = *(this + 12);  // this+48〔pCmdVecBegin48(推断)〕
    *(uint8_t *)(result + 16) = 0;  // result=this+48 pCmdVecBegin48
  }
  return result;  // result=this+48 pCmdVecBegin48
}



// ------------------------------------------------------------
// 0x49E0E0 sub_49E0E0 —— 结算阶段计时推进（阶段计数归零且满 4000ms → ·sub_49E050(+1)）
//   this+4 阶段计数递减；归零后以 this+8 时钟满 4000ms 为界推进到下一阶段。
// ------------------------------------------------------------
int /*thiscall*/ sub_49E0E0(int *this)  // 实现：结算阶段计时推进（阶段计数归零且满 4000ms → ·sub_49E050(+1)）
{
  int result; // eax

  result = *(this + 1);  // this+4〔宿主对象〕
  if ( result != 0 && --result == 0 )  // 若 result != 0
  {
    result = sub_699000((int)(this + 2));  // 【clock_now(clk)】
    if ( result >= 4000 )  // 若 result >= 4000
      return sub_49E050(this, *(this + 1) + 1);  // M_RESULT 演出（结算上下文 sub_65DC70、音效 sub_432EA0）
  }
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x49E110 sub_49E110 —— 结算数值标签刷新（284/102 与 359/99 两处 + 0xAC 底板）
//   ·sub_69A110 写两处数字（Value 与 nArg3），中间以 0xAC 号图 (339,103) 用 +152 Alpha 重绘。
// ------------------------------------------------------------
int /*thiscall*/ sub_49E110(int *this, int Value, int nArg3)  // 实现：结算数值标签刷新（284/102 与 359/99 两处 + 0xAC 底板）
{
  int pThis_98; // esi
  int pObj; // eax

  sub_69A110(284, 102, Value, *(this + 38));  // this+152〔nAdd152(推断)〕
  pThis_98 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;  // this+152〔nAdd152(推断)〕
  pObj = sub_418DD0(*(uint32_t **)(*(uint32_t *)(dword_99FCC8 + 20) + 64), 0xACu);  // pObj = 调 sub_418DD0 返回值
  if ( pObj != 0 )  // 若 pObj 非 0
    (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
      pObj,
      339,
      103,
      dword_79C0B0,  // 默认字体/绘制资源
      1065353216,
      1065353216,
      0,
      pThis_98,  // pThis_98=this+152 nAdd152
      1333788672,
      1333788672);
  return sub_69A110(359, 99, nArg3, *(this + 38));  // 返回 调 sub_69A110 返回值
}



// ------------------------------------------------------------
// 0x49E1B0 sub_49E1B0 —— 结算名次行逐行绘制（172 行图 + 301 标签，行距 46）
//   行图 172 画于 (279, 164+46i)，标签 ·sub_69A110(301, 161+46i, this+32+4i)；
//   另有收尾分支在 clock_now(this+88) < 100 时以 ·0x491530(5,-1)/·0x491630(5) 变换包裹绘制【推断：末行高亮】。
// ------------------------------------------------------------
int /*thiscall*/ sub_49E1B0(int *this, int nArg2)  // 实现：结算名次行逐行绘制（172 行图 + 301 标签，行距 46）
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
  if ( nArg2 >= 0 )  // 若 nArg2 >= 0
  {
    v4 = 161;
    pThis_20 = this + 32;
    v5 = nArg2 == 0;
    v6 = nArg2 > 0;
    do  // do-while 循环体起点
    {
      if ( v6 )
      {
        pThis_98 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;  // this+152〔nAdd152(推断)〕
        pObj = sub_418DD0(172);  // pObj = 调 sub_418DD0 返回值
        if ( pObj != 0 )  // 若 pObj 非 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
            pObj,
            279,
            v4 + 3,
            dword_79C0B0,  // 默认字体/绘制资源
            1065353216,
            1065353216,
            0,
            pThis_98,  // pThis_98=this+152 nAdd152
            1333788672,
            1333788672);
        sub_69A110(301, v4, *pThis_20, *(this + 38));  // this+152〔nAdd152(推断)〕
      }
      else  // 否则分支
      {
        if ( !v5 || result == 4 )  // 若 result == 4
          goto LABEL_16;
        if ( sub_699000((int)(this + 22)) < 100 )  // 【clock_now(clk)】
          sub_491530(5, -1);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
        pThis_982 = (*((uint8_t *)this + 152) << 24) | 0xFFFFFF;  // this+152〔nAdd152(推断)〕
        pObj2 = sub_418DD0(172);  // pObj2 = 调 sub_418DD0 返回值
        if ( pObj2 != 0 )  // 若 pObj2 非 0
          (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
            pObj2,
            279,
            v4 + 3,
            dword_79C0B0,  // 默认字体/绘制资源
            1065353216,
            1065353216,
            0,
            pThis_982,  // pThis_982=this+152 nAdd152
            1333788672,
            1333788672);
        sub_69A110(301, v4, *pThis_20, *(this + 38));  // this+152〔nAdd152(推断)〕
        if ( sub_699000((int)(this + 22)) < 100 )  // 【clock_now(clk)】
          sub_491630(5);  // 渲染层状态还原（与 ·0x491530 配对）
      }
      result = nArg2;
LABEL_16:  // 标签 LABEL_16（跳转合流点）
      v4 += 46;
      v5 = v11 + 1 == result;
      v6 = ++v11 < result;
      ++pThis_20;  // pThis_20=this+32 格子像素尺寸
    }
    while ( v6 );  // 条件循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x49E340 sub_49E340 —— 结算动画装配（+56 图像、+48/+52 帧字段、M_RESULT 事件）
// ------------------------------------------------------------
char /*thiscall*/ sub_49E340(int this, void *Block, int nArg3)  // 实现：结算动画装配（+56 图像、+48/+52 帧字段、M_RESULT 事件）
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

  *(uint32_t *)(this + 116) = Block;  // this+116〔会话上下文〕
  *(uint32_t *)(this + 120) = nArg3;  // this+120〔pAnimObj〕
  *(uint32_t *)(this + 56) = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 208);  // this+56〔pCmdVecCap56(推断)〕等 2 字段
  pMem = operator new(0x68u);  // new(104 字节) 分配对象
  v5 = 0;
  v21 = 0;
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
    v6 = sub_426BD0(pMem);  // nengine::IControl 构造
  else  // 否则分支
    v6 = nullptr;  // v6 = 空指针
  *(uint32_t *)(this + 48) = v6;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  *((uint32_t *)v6 + 7) = 640;  // v6[7] = 640
  *((uint32_t *)v6 + 8) = 480;  // v6[8] = 480
  *(uint32_t *)(*(uint32_t *)(this + 48) + 68) = this;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  pMem2 = operator new(0x68u);  // new(104 字节) 分配对象
  v21 = 1;
  if ( pMem2 != nullptr )  // 若 pMem2 有效（非空）
    v8 = sub_426BD0(pMem2);  // nengine::IControl 构造
  else  // 否则分支
    v8 = nullptr;  // v8 = 空指针
  *(uint32_t *)(this + 52) = v8;  // this+52〔bAuraState(推断)〕等 2 字段
  *((uint32_t *)v8 + 17) = this;  // v8[17] = this
  fld_34 = *(uint32_t *)(this + 52);  // fld_34 = 读 this+52
  v21 = -1;
  sub_69A840(fld_34);  // 调 五处登记 → +76=-1 且 ·0x42E990(-1) 复位且 +108=0
  v9 = *(uint32_t *)(*(uint32_t *)(dword_99FCC8 + 20) + 64);  // nengine::CNSlider 全局实例
  v18[0] = -5;
  v18[1] = -5;
  v18[2] = -5;
  v19[0] = *(uint32_t *)(this + 56);  // v19[0] = 读 this+56
  v19[2] = v19[0];  // v19[2] = 取 v19[0]
  v20[0] = (void *)22;  // v20[0] = 转换(22)
  v20[1] = (void *)36;  // v20[1] = 转换(36)
  v20[2] = (void *)32;  // v20[2] = 转换(32)
  v17[0] = 0;
  v17[1] = 0;
  v17[2] = 2;
  v19[1] = v9;
  Blocka = (char *)(this + 36);  // this+36〔nStateWord36(推断)〕等 2 字段
  do  // do-while 循环体起点
  {
    pMem3 = operator new(0x2Cu);  // new(44 字节) 分配对象
    pMem32 = pMem3;
    v20[3] = pMem3;
    v21 = 2;
    if ( pMem3 != nullptr )  // 若 pMem3 有效（非空）
    {
      dword_79C0B02 = dword_79C0B0;  // 默认字体/绘制资源
      pMem3[4] = 0;
      LOBYTE(v21) = 3;
      *(uint32_t *)pMem3 = &nengine::CNNumberSet::`vftable';
      sub_699E20(pMem3);  // 调 本体初始化 + sub_699E40(a2..a5)
      sub_699E40(dword_79C0B02, v19[v5], v20[v5], 9);  // 默认字体/绘制资源
    }
    else  // 否则分支
    {
      pMem32 = nullptr;  // pMem32 = 空指针
    }
    v12 = v18[v5];  // v12 = 取 v18[v5]
    *(uint32_t *)Blocka = pMem32;  // Blocka=this+36 nStateWord36
    *((uint32_t *)pMem32 + 10) = v12;
    *(uint32_t *)(*(uint32_t *)Blocka + 36) = v17[v5];  // Blocka=this+36 nStateWord36
    v13 = *(uint32_t *)Blocka;  // Blocka=this+36 nStateWord36
    ++v5;
    v21 = -1;
    *(uint8_t *)(v13 + 24) = 0;
    Blocka += 4;  // Blocka 前进 4
  }
  while ( v5 < 3 );  // 条件循环
  sub_698F90(this + 60, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint32_t *)(this + 4) = 0;  // this+4〔宿主对象〕等 2 字段
  *(uint8_t *)(this + 21) = 0;  // this+21〔bArmorState〕
  *(uint8_t *)(this + 22) = 0;  // this+88〔pFxObjB(推断)〕
  sub_698F90(this + 8, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  if ( *(uint32_t *)(this + 4) != 0 )  // this+4〔宿主对象〕等 2 字段
  {
    LOBYTE(fld_30) = *(uint8_t *)(*(uint32_t *)(this + 48) + 16);  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
    if ( (uint8_t)fld_30 == 0 )
    {
      sub_65DC70(lpCriticalSection);  // FSOUND 全停：50 个 48B 通道槽逐个 sub_65D8B0 停止，再摘 +2560 处播放链所有结点
      LOBYTE(fld_30) = (uint8_t)sub_432EA0("M_RESULT", -1, 0, 0);  // 音效播放包装（非空判定）
    }
    *(uint8_t *)(*(uint32_t *)(this + 48) + 16) = 1;  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  }
  else  // 否则分支
  {
    sub_49DCF0(this);  // 结算段复位与时长装载（+128=5000、+132/136/140=3000/2000/1000、+144=30000）
    fld_30 = *(uint32_t *)(this + 48);  // fld_30 = 读 this+48
    *(uint8_t *)(fld_30 + 16) = 0;  // fld_30=this+48 UDP 上报使能位
  }
  return fld_30;  // fld_30=this+48 UDP 上报使能位
}


// ------------------------------------------------------------
// 0x49E560 sub_49E560 —— RESULT_FLASH 演出驱动（+48 亮度 sub_4049C0 插值 → sub_491530/491630 图层）
// ------------------------------------------------------------
int /*thiscall*/ sub_49E560(int this, int nArg2)  // 实现：RESULT_FLASH 演出驱动（+48 亮度 sub_4049C0 插值 → sub_491530/491630 图层）
{
  uint64_t v2; // rax
  int fld_4; // eax  | +0x0004 → 演出阶段值（CNRDWarRoomResult；va=0049E560）
  int fld_98; // edi  | +0x0098 → 当前亮度值（0x49E560: ==12 段取本槽作亮度；并作 sub_69A110 第四参，与 +148 成对）（CNRDWarRoomResult；va=0049E560）
  int pThis_8; // eax
  uint8_t fld_982; // bl
  int pObj; // eax
  uint8_t fld_983; // bl
  int pObj2; // eax
  int fld_42; // eax  | +0x0004 → 演出阶段值（CNRDWarRoomResult；va=0049E560）
  int fld_43; // eax  | +0x0004 → 演出阶段值（CNRDWarRoomResult；va=0049E560）
  int pThis_82; // eax
  int v14; // ebx
  int pThis_83; // eax
  double v16; // st7
  int fld_44; // eax  | +0x0004 → 演出阶段值（CNRDWarRoomResult；va=0049E560）
  int v18; // edi
  int pThis_85; // eax
  float fld_7C; // [esp+48h] [ebp-1Ch]  | +0x007C → 淡出起始亮度（CNRDWarRoomResult；va=0049E560）
  float fld_90; // [esp+4Ch] [ebp-18h]  | +0x0090 → 淡出目标亮度（CNRDWarRoomResult；va=0049E560）
  int pThis_84; // [esp+54h] [ebp-10h]
  float pThis_3C; // [esp+6Ch] [ebp+8h]

  LODWORD(v2) = nArg2;
  if ( nArg2 == *(uint32_t *)(this + 48) )  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
  {
    fld_4 = *(uint32_t *)(this + 4);  // fld_4 = 读 this+4
    if ( fld_4 >= 2 )  // 若 fld_4 >= 2
    {
      fld_98 = 255;
      if ( fld_4 == 2 )  // 若 fld_4 == 2
      {
        pThis_8 = sub_699000(this + 8);  // 【clock_now(clk)】
        fld_98 = (uint64_t)sub_4049C0(0.0, 255.0, pThis_8, 800);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      }
      else if ( fld_4 == 12 )  // fld_4=this+4 nShowStage
      {
        fld_98 = *(uint32_t *)(this + 152);  // fld_98 = 读 this+152
      }
      sub_49DB80(fld_98);  // 数字底板透明度刷新（+56 图链 0/3 两图 vt+128 十参）
      pThis_3C = (double)sub_699000(this + 60) * 0.000033333334;  // 【clock_now(clk)】
      sub_491530(2, 0);  // 渲染层调色/绘制模式设置（dword_79C0A4 全局渲染器对象）
      fld_982 = fld_98;  // fld_98=this+152 nBrightness
      if ( fld_98 >= 120 )  // 若 fld_98 >= 120
        fld_982 = 120;
      pObj = sub_418DD0(1);  // pObj = 调 sub_418DD0 返回值
      if ( pObj != 0 )  // 若 pObj 非 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, float, int, int, int))(*(uint32_t *)pObj + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
          pObj,
          111,
          31,
          dword_79C0B0,  // 默认字体/绘制资源
          1065353216,
          1065353216,
          COERCE_FLOAT(LODWORD(pThis_3C)),
          (fld_982 << 24) | 0xFFFFFF,
          1129447424,
          1129447424);
      sub_491630(2);  // 渲染层状态还原（与 ·0x491530 配对）
      fld_983 = fld_98;  // fld_98=this+152 nBrightness
      if ( fld_98 >= 220 )  // 若 fld_98 >= 220
        fld_983 = -36;
      pObj2 = sub_418DD0(2);  // pObj2 = 调 sub_418DD0 返回值
      if ( pObj2 != 0 )  // 若 pObj2 非 0
        (*(void (/*thiscall*/ **)(int, int, int, int, int, int, uint32_t, int, int, int))(*(uint32_t *)pObj2 + 128))(  // 调虚槽 +128：CNRDAuraMaster__vmt80 受击槽（42AF90/657740 + 42FC…
          pObj2,
          122,
          71,
          dword_79C0B0,  // 默认字体/绘制资源
          1065353216,
          1065353216,
          0,
          (fld_983 << 24) | 0xFFFFFF,
          1333788672,
          1333788672);
      sub_49DE70((void *)this, fld_98);  // 名次星标绘制（四格 6..9 号 + 5/10 号收尾）
      if ( *(uint32_t *)(this + 4) == 2 && sub_699000(this + 8) >= 800 )  // 【clock_now(clk)】
        goto LABEL_41;
    }
    fld_42 = *(uint32_t *)(this + 4);  // fld_42 = 读 this+4
    if ( fld_42 >= 3 )  // 若 fld_42 >= 3
    {
      if ( fld_42 == 3 )  // 若 fld_42 == 3
      {
        sub_49E110(*(uint32_t *)(this + 124), 0);  // 结算数值标签刷新（284/102 与 359/99 两处 + 0xAC 底板）
        sub_49DD80(0);  // 数字底板双图交替落位（13/14 号，按 nArg2 阈值换序）
      }
      sub_69A110(273, 352, *(uint32_t *)(this + 148), *(uint32_t *)(this + 152));  // this+148〔fAdd148(推断)〕等 3 字段
      if ( *(uint32_t *)(this + 4) == 3 && sub_699000(this + 8) >= 1000 )  // 【clock_now(clk)】
        goto LABEL_41;
    }
    fld_43 = *(uint32_t *)(this + 4);  // fld_43 = 读 this+4
    if ( fld_43 >= 4 )  // 若 fld_43 >= 4
    {
      if ( fld_43 == 4 )  // 若 fld_43 == 4
      {
        pThis_82 = sub_699000(this + 8);  // 【clock_now(clk)】
        fld_7C = (float)*(int *)(this + 124);  // this+124〔pAuraAnim(推断)〕
        v14 = (uint64_t)sub_4049C0(fld_7C, 0.0, pThis_82, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        pThis_83 = sub_699000(this + 8);  // 【clock_now(clk)】
        fld_90 = (float)*(int *)(this + 144);  // this+144〔pFrameList144(推断)〕等 2 字段
        v16 = sub_4049C0(0.0, fld_90, pThis_83, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        sub_49E110(v14, (uint64_t)v16);  // 结算数值标签刷新（284/102 与 359/99 两处 + 0xAC 底板）
        pThis_84 = sub_699000(this + 8) % 160;  // 【clock_now(clk)】
        sub_49DD80(pThis_84);  // 数字底板双图交替落位（13/14 号，按 nArg2 阈值换序）
      }
      else  // 否则分支
      {
        sub_49E110(*(uint32_t *)(this + 124), *(uint32_t *)(this + 144));  // 结算数值标签刷新（284/102 与 359/99 两处 + 0xAC 底板）
        sub_49DD80(0);  // 数字底板双图交替落位（13/14 号，按 nArg2 阈值换序）
      }
      if ( *(uint32_t *)(this + 4) == 4 && (double)sub_699000(this + 8) >= 1100.0 )  // 【clock_now(clk)】
      {
        *(uint32_t *)(this + 124) = 0;  // this+124〔pAuraAnim(推断)〕
        *(uint8_t *)(this + 101) = 0;  // this+101〔bFired101(推断)〕
        *(uint8_t *)(this + 102) = 0;  // this+102〔bFlashClearB〕
        sub_698F90(this + 88, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
LABEL_41:  // 标签 LABEL_41（跳转合流点）
        LODWORD(v2) = sub_49E050(*(uint32_t *)(this + 4) + 1);  // M_RESULT 演出（结算上下文 sub_65DC70、音效 sub_432EA0）
        return v2;
      }
    }
    fld_44 = *(uint32_t *)(this + 4);  // fld_44 = 读 this+4
    if ( fld_44 == 5 || fld_44 == 6 || fld_44 == 7 || fld_44 == 8 )  // 若 fld_44 == 5 与/或 fld_44 == 6 与/或 fld_44 == 7
    {
      v18 = fld_44 - 5;  // fld_44=this+4 nShowStage
      sub_49E1B0((int *)this, fld_44 - 5);  // 结算名次行逐行绘制（172 行图 + 301 标签，行距 46）
      if ( *(uint32_t *)(this + 4) == v18 + 5 && sub_699000(this + 8) >= 1000 )  // 【clock_now(clk)】
      {
        *(uint8_t *)(this + 101) = 0;  // this+101〔bFired101(推断)〕
        *(uint8_t *)(this + 102) = 0;  // this+102〔bFlashClearB〕
        sub_698F90(this + 88, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        goto LABEL_41;
      }
    }
    if ( *(int *)(this + 4) >= 9 )  // this+4〔宿主对象〕等 2 字段
    {
      sub_49E1B0((int *)this, 4);  // 结算名次行逐行绘制（172 行图 + 301 标签，行距 46）
      if ( *(uint32_t *)(this + 4) == 9 && sub_699000(this + 8) >= 1000 )  // 【clock_now(clk)】
        goto LABEL_41;
    }
    if ( *(uint32_t *)(this + 4) == 10 )  // this+4〔宿主对象〕等 2 字段
    {
      sub_49DC30((uint32_t *)this);  // M_RESULT 事件处理（sub_432EE0/sub_65DC70 → sub_49DCF0）
      if ( sub_699000(this + 8) >= 560 )  // 【clock_now(clk)】
        goto LABEL_41;
    }
    if ( *(uint32_t *)(this + 4) == 11 && sub_699000(this + 8) >= 3000 )  // 【clock_now(clk)】
      goto LABEL_41;
    LODWORD(v2) = *(uint32_t *)(this + 4);  // this+4〔宿主对象〕等 2 字段
    if ( (int)v2 >= 12 )
    {
      pThis_85 = sub_699000(this + 8);  // 【clock_now(clk)】
      v2 = (uint64_t)sub_4049C0(255.0, 0.0, pThis_85, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      *(uint32_t *)(this + 152) = v2;  // this+152〔nAdd152(推断)〕等 2 字段
      if ( *(uint32_t *)(this + 4) == 12 )  // this+4〔宿主对象〕等 2 字段
      {
        LODWORD(v2) = sub_699000(this + 8);  // 【clock_now(clk)】
        if ( (int)v2 >= 1000 )
          LODWORD(v2) = sub_49E050(0);  // M_RESULT 演出（结算上下文 sub_65DC70、音效 sub_432EA0）
      }
    }
  }
  return v2;
}


// ============================================================
// §P 0x49E930-0x49FFC0  列表子项管理 + 收尾
// ============================================================
// ------------------------------------------------------------
// 0x49E930 sub_49E930 —— 列表子项字段初始化（+68 清零、+72 = -1、+76..+144 归零、+148 = 0xFF）
//   与 ·sub_49E990（+4..+32 = 255、+36..+64 = 0xFFFF）组合成列表子项完整初值。
// ------------------------------------------------------------
int /*thiscall*/ sub_49E930(int this)  // 实现：列表子项字段初始化（+68 清零、+72 = -1、+76..+144 归零、+148 = 0xFF）
{
  *(uint32_t *)(this + 68) = 0;  // this+68〔nCharCount(推断)〕
  *(uint32_t *)(this + 72) = -1;  // this+72〔nSnapshot72(推断)〕等 2 字段
  *(uint32_t *)(this + 76) = 0;  // this+76〔pBtnActionE〕
  *(uint32_t *)(this + 80) = 0;  // this+80〔nAuraStage(推断)〕
  *(uint32_t *)(this + 84) = 0;  // this+84〔pFxObjA(推断)〕
  *(uint32_t *)(this + 88) = 0;  // this+88〔pFxObjB(推断)〕等 2 字段
  *(uint32_t *)(this + 92) = 0;  // this+92〔pFxObjC(推断)〕等 2 字段
  *(uint32_t *)(this + 96) = 0;  // this+96〔nStatusMode(推断)〕等 2 字段
  *(uint32_t *)(this + 100) = 0;  // this+100〔bEnchantDone(推断)〕
  *(uint32_t *)(this + 104) = 0;  // this+104〔nTimerEnd(推断)〕
  *(uint32_t *)(this + 108) = 0;  // this+108〔nAdd108(推断)〕
  *(uint32_t *)(this + 112) = 0;  // this+112〔pHostComp112〕
  *(uint32_t *)(this + 116) = 0;  // this+116〔会话上下文〕
  *(uint32_t *)(this + 120) = 0;  // this+120〔pAnimObj〕
  *(uint32_t *)(this + 124) = 0;  // this+124〔pAuraAnim(推断)〕
  *(uint32_t *)(this + 128) = 0;  // this+128〔szStatusKeyBuf(推断)〕等 2 字段
  *(uint32_t *)(this + 132) = 0;  // this+132〔nAgeTicks〕
  *(uint32_t *)(this + 136) = 0;  // this+136〔nCtx136(推断)〕等 2 字段
  *(uint32_t *)(this + 140) = 0;  // this+140〔nAdd140(推断)〕
  *(uint32_t *)(this + 144) = 0;  // this+144〔pFrameList144(推断)〕等 2 字段
  *(uint8_t *)(this + 148) = -1;  // this+148〔fAdd148(推断)〕
  return -1;
}



// ------------------------------------------------------------
// 0x49E990 sub_49E990 —— 列表子项初值（+4..+32 = 255、+36..+64 = 0xFFFF）
//   uint32 索引 1..8 置 255（图序号占位）、9..16 置 0xFFFF（空槽标记）；
//   尾调 ·sub_49E930 清时间字段；255 与 0xFFFF 为两种占位符【推断】。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49E990(uint32_t *this)  // 实现：列表子项初值（+4..+32 = 255、+36..+64 = 0xFFFF）
{
  *this = 0;
  *(this + 1) = 255;  // this+4〔宿主对象〕
  *(this + 2) = 255;  // this+8〔nSkillRec8(推断)〕
  *(this + 3) = 255;  // this+12〔nSkillRec12(推断)〕
  *(this + 4) = 255;  // this+16〔nChannelTypeSel(推断)〕
  *(this + 5) = 255;  // this+20〔nPage(推断)〕
  *(this + 6) = 255;  // this+24〔nPageMax(推断)〕
  *(this + 7) = 255;  // this+28〔pPanelVec(推断)〕
  *(this + 8) = 255;  // this+32〔nHeight(推断)〕
  *(this + 9) = 0xFFFF;  // this+36〔nStateWord36(推断)〕
  *(this + 10) = 0xFFFF;  // this+40〔bStateSub40(推断)〕
  *(this + 11) = 0xFFFF;  // this+44〔nExpireMs(推断)〕
  *(this + 12) = 0xFFFF;  // this+48〔pCmdVecBegin48(推断)〕
  *(this + 13) = 0xFFFF;  // this+52〔bAuraState(推断)〕
  *(this + 14) = 0xFFFF;  // this+56〔pCmdVecCap56(推断)〕
  *(this + 15) = 0xFFFF;  // this+60〔nFadeValue60(推断)〕
  *(this + 16) = 0xFFFF;  // this+64〔apServerTabBtn(推断)〕
  sub_49E930((int)this);  // 列表子项字段初始化（+68 清零、+72 = -1、+76..+144 归零、+148 = 0xFF）
  return this;
}



// ------------------------------------------------------------
// 0x49E9E0 sub_49E9E0 —— CNWarRoom 析构（挂 vftable + nullsub 收尾，条件 j__free）
//   挂 CNWarRoom vftable（RTTI 表 VT 006CBA60）、nullsub_3(Block) 收尾；
//   参数位 0（pszArg2 & 1）置位时 j__free（标量删除语义）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49E9E0(uint32_t *Block, char pszArg2)  // 实现：CNWarRoom 析构（挂 vftable + nullsub 收尾，条件 j__free）
{
  *Block = &CNWarRoom::`vftable';  // 构造装配 vftable：CNWarRoom
  nullsub_3(Block);
  if ( (pszArg2 & 1) != 0 )  // 若 pszArg2 位 1 测试
    j__free(Block);  // 调 j__free（堆释放）
  return Block;
}



// ------------------------------------------------------------
// 0x49EA10 sub_49EA10 —— 红黑树槽字段清零（int 视角 +4 / +8）
//   短小复位例程：两字段清零并返回 0（对照 ·sub_49DB10 的字段组清零）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA10(uint32_t *this)  // 实现：红黑树槽字段清零（int 视角 +4 / +8）
{
  *(this + 1) = 0;  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
  return 0;
}



// ------------------------------------------------------------
// 0x49EA20 sub_49EA20 —— 内嵌对象析构代理（this+4 挂 vftable + nullsub_3）
//   与 ·sub_49E9E0 同构（差异：作用于 this+4 的内嵌 CNWarRoom 子对象，无 j__free）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA20(uint32_t *this)  // 实现：内嵌对象析构代理（this+4 挂 vftable + nullsub_3）
{
  uint32_t *pThis_1; // ecx

  pThis_1 = this + 1;
  *pThis_1 = &CNWarRoom::`vftable';  // 构造装配 vftable：CNWarRoom
  return nullsub_3(pThis_1);  // 返回 调 nullsub_3
}



// ------------------------------------------------------------
// 0x49EA30 sub_49EA30 —— 红黑树槽基址计算（*(this+4) + 12 × 序号）
//   槽每项 12 字节（·sub_49F970 按 0xC 步长构造数组；槽 +4 = header 节点、+8 = 计数）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EA30(uint32_t *this, int nArg2)  // 实现：红黑树槽基址计算（*(this+4) + 12 × 序号）
{
  return *(this + 1) + 12 * nArg2;  // this+4〔宿主对象〕
}



// ------------------------------------------------------------
// 0x49EA50 sub_49EA50 —— 红黑树节点下行（沿 +8 链至哨兵，返回最深节点）
//   +173 = 哨兵标记字节（非 0 即空位）；
//   [推断] 对应 _Rb_tree 的 _Maximum 侧（前驱方向），与 ·sub_49EA80 镜像。
// ------------------------------------------------------------
int /*cdecl*/ sub_49EA50(int pArg1)  // 实现：红黑树节点下行（沿 +8 链至哨兵，返回最深节点）
{
  int result; // eax
  int i; // ecx

  result = pArg1;
  for ( i = *(uint32_t *)(pArg1 + 8); *(uint8_t *)(i + 173) == 0; i = *(uint32_t *)(i + 8) )  // 遍历循环
    result = i;
  return result;
}



// ------------------------------------------------------------
// 0x49EA80 sub_49EA80 —— 红黑树节点下行（沿 +0 链至哨兵）
//   [推断] 对应 _Rb_tree 的 _Minimum 侧（后继方向）；
//   被 ·sub_49F3F0 删除重平衡用于修正 header 的 +4 指针。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_49EA80(uint32_t *pArg1)  // 实现：红黑树节点下行（沿 +0 链至哨兵）
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 173) == 0 )
  {
    do  // do-while 循环体起点
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 173) == 0 );  // 条件循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EAB0 sub_49EAB0 —— 红黑树右旋（+0 子提升为新子树根）
//   节点 +0/+4/+8 = 两子 + 父（+172 颜色、+173 哨兵）；
//   为 ·sub_49F150 插入重平衡与 ·sub_49F3F0 删除重平衡的原子步。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EAB0(uint32_t *this, uint32_t *pArg2)  // 实现：红黑树右旋（+0 子提升为新子树根）
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
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( pArg2 == *(uint32_t **)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1=this+4 宿主对象
    *(uint32_t *)(result + 8) = pArg2;
    pArg2[1] = result;
  }
  else  // 否则分支
  {
    v5 = (uint32_t *)pArg2[1];
    if ( pArg2 == (uint32_t *)v5[2] )
      v5[2] = result;
    else  // 否则分支
      *v5 = result;
    *(uint32_t *)(result + 8) = pArg2;
    pArg2[1] = result;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EB20 sub_49EB20 —— 红黑树迭代器自增（++，中序下一节点）
//   _Rb_tree_increment 骨架：右子树最小或沿父链上溯；空位判定 = +173 哨兵标记。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EB20(void *this)  // 实现：红黑树迭代器自增（++，中序下一节点）
{
  uint32_t *v1; // eax
  int result; // eax
  int v3; // edx

  v1 = *(uint32_t **)this;
  if ( *(uint8_t *)(*(uint32_t *)this + 173) != 0 )  // this+692〔nSnapshot692〕
  {
    result = v1[2];  // result = 取 v1[2]
    *(uint32_t *)this = result;
  }
  else  // 否则分支
  {
    v3 = *v1;
    if ( *(uint8_t *)(*v1 + 173) != 0 )
    {
      result = v1[1];  // result = 取 v1[1]
      if ( *(uint8_t *)(result + 173) == 0 )
      {
        do  // do-while 循环体起点
        {
          if ( *(uint32_t *)this != *(uint32_t *)result )
            break;  // 跳出循环/分支
          *(uint32_t *)this = result;
          result = *(uint32_t *)(result + 4);
        }
        while ( *(uint8_t *)(result + 173) == 0 );  // 条件循环
        if ( *(uint8_t *)(result + 173) == 0 )
          *(uint32_t *)this = result;
      }
    }
    else  // 否则分支
    {
      for ( result = *(uint32_t *)(v3 + 8); *(uint8_t *)(result + 173) == 0; result = *(uint32_t *)(result + 8) )  // 遍历循环
        v3 = result;
      *(uint32_t *)this = v3;  // *this = v3
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EBA0 sub_49EBA0 —— 红黑树迭代器自减（--，中序上一节点）
//   _Rb_tree_decrement 骨架：左子树最大或沿父链上溯；
//   被 ·sub_49EE90/·sub_49EEE0/·sub_49EF60 全表遍历与 ·sub_49F750 区间删除使用。
// ------------------------------------------------------------
int */*thiscall*/ sub_49EBA0(int *this)  // 实现：红黑树迭代器自减（--，中序上一节点）
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 173) == 0 )  // this+173 动画辅助标志
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 173) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 173) == 0; result = (int *)result[1] )  // 遍历循环
      {
        if ( *this != result[2] )
          break;  // 跳出循环/分支
        *this = (int)result;
      }
      *this = (int)result;
    }
    else  // 否则分支
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 173) == 0 )
      {
        do  // do-while 循环体起点
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 173) == 0 );  // 条件循环
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EC10 sub_49EC10 —— 红黑树槽计数求和（12 字节槽取 +8 字段）
//   槽数组 this+4、槽数 this+8；每槽按 12 字节跨度累加 +8 字段（[推断] 槽内条目数）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EC10(int *this)  // 实现：红黑树槽计数求和（12 字节槽取 +8 字段）
{
  int fld_e2; // edx
  int result; // eax
  uint32_t *fld_e1; // ecx

  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  result = 0;
  if ( fld_e2 > 0 )  // 若 fld_e2 > 0
  {
    fld_e1 = (uint32_t *)(*(this + 1) + 8);  // this+4〔宿主对象〕
    do  // do-while 循环体起点
    {
      result += *fld_e1;  // fld_e1=this+4 宿主对象
      fld_e1 += 3;  // fld_e1=this+4 宿主对象
      --fld_e2;  // fld_e2=this+8 nSkillRec8
    }
    while ( fld_e2 != 0 );  // 条件循环
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EC30 sub_49EC30 —— 红黑树左旋（+8 子提升为新子树根，与 ·sub_49EAB0 镜像）
//   同族原子步，与 ·sub_49EAB0 互补成双旋。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49EC30(uint32_t *this, int pArg2)  // 实现：红黑树左旋（+8 子提升为新子树根，与 ·sub_49EAB0 镜像）
{
  uint32_t *result; // eax
  int fld_e1; // ecx
  uint32_t *v4; // ecx

  result = *(uint32_t **)(pArg2 + 8);  // pArg2+8〔nSkillRec8(推断)〕
  *(uint32_t *)(pArg2 + 8) = *result;  // pArg2+8〔nSkillRec8(推断)〕
  if ( *(uint8_t *)(*result + 173) == 0 )
    *(uint32_t *)(*result + 4) = pArg2;
  result[1] = *(uint32_t *)(pArg2 + 4);  // pArg2+4〔宿主对象〕
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  if ( pArg2 == *(uint32_t *)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
  {
    *(uint32_t *)(fld_e1 + 4) = result;  // fld_e1=this+4 宿主对象
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4〔宿主对象〕
  }
  else  // 否则分支
  {
    v4 = *(uint32_t **)(pArg2 + 4);  // pArg2+4〔宿主对象〕
    if ( pArg2 == *v4 )
      *v4 = result;
    else  // 否则分支
      v4[2] = result;
    *result = pArg2;
    *(uint32_t *)(pArg2 + 4) = result;  // pArg2+4〔宿主对象〕
  }
  return result;
}



// ------------------------------------------------------------
// 0x49EC90 sub_49EC90 —— 红黑树槽定位（首键 >= 键值的节点，lower_bound）
//   this+4 = header（header+4 = 树根）、节点 +12 = 键；沿子链下降；
//   命中可能为 header（表示超出），由调用者按 nil 判定区分。
// ------------------------------------------------------------
int */*thiscall*/ sub_49EC90(uint32_t *this, uint32_t *uArg2)  // 实现：红黑树槽定位（首键 >= 键值的节点，lower_bound）
{
  int *result; // eax
  int *v3; // ecx

  result = (int *)*(this + 1);  // this+4〔宿主对象〕
  v3 = (int *)result[1];  // result=this+4 宿主对象
  while ( *((uint8_t *)v3 + 173) == 0 )  // 条件循环
  {
    if ( v3[3] >= *uArg2 )
    {
      result = v3;  // result=this+4 宿主对象
      v3 = (int *)*v3;
    }
    else  // 否则分支
    {
      v3 = (int *)v3[2];
    }
  }
  return result;  // result=this+4 宿主对象
}



// ------------------------------------------------------------
// 0x49ECD0 sub_49ECD0 —— 红黑树节点分配（0xB0 字节：指针三件 + 键 + 载荷 0x98 拷贝）
//   +0/+4/+8 = 子/父指针初值（nArg1/nArg2/nArg3）、+12 = 键 (*pArg4)、+16 = CNWarRoom vftable、
//   +20..+171 = pArg4+8 起 0x98 字节 qmemcpy、+172 = 颜色参数、+173 = 0（常规节点标记）。
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_49ECD0(int nArg1, int nArg2, int nArg3, uint32_t *pArg4, char pszArg5)  // 实现：红黑树节点分配（0xB0 字节：指针三件 + 键 + 载荷 0x98 拷贝）
{
  uint32_t *result; // eax

  result = operator new(0xB0u);  // new(176 字节) 分配对象
  if ( result != nullptr )  // 若 result 有效（非空）
  {
    *result = nArg1;
    result[2] = nArg3;
    result[1] = nArg2;
    result[3] = *pArg4;
    result[4] = &CNWarRoom::`vftable';  // 构造装配 vftable：CNWarRoom
    qmemcpy(result + 5, pArg4 + 2, 0x98u);  // 调 qmemcpy（内存块拷贝(内联展开)）
    *((uint8_t *)result + 172) = pszArg5;
    *((uint8_t *)result + 173) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x49ED30 sub_49ED30 —— 红黑树槽 header 分配（0xB0 字节，+172 = 1 黑）
//   指针三件与 +12 键清零；+172 = 1（黑）、+173 = 0（·sub_49F940 再置 1 作哨兵）。
// ------------------------------------------------------------
uint32_t *sub_49ED30()  // 实现：红黑树槽 header 分配（0xB0 字节，+172 = 1 黑）
{
  uint32_t *result; // eax

  result = operator new(0xB0u);  // new(176 字节) 分配对象
  if ( result != nullptr )  // 若 result 有效（非空）
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
// 0x49ED70 sub_49ED70 —— 红黑树槽查找并回填迭代器（越界则取 header）
//   转 ·sub_49EC90；命中为 header 或键小于节点 +12 时回填 header（即 end），否则回填命中节点。
// ------------------------------------------------------------
int **/*thiscall*/ sub_49ED70(int **this, int **pDwArg2, uint32_t *uArg3)  // 实现：红黑树槽查找并回填迭代器（越界则取 header）
{
  int *v5; // eax
  int *fld_e1; // esi
  int *v8; // [esp+18h] [ebp+Ch]

  v5 = sub_49EC90(this, uArg3);  // 红黑树槽定位（首键 >= 键值的节点，lower_bound）
  fld_e1 = *(this + 1);  // this+4〔宿主对象〕
  v8 = v5;
  if ( v5 == fld_e1 || *uArg3 < v5[3] )  // 若 v5 == fld_e1
  {
    *pDwArg2 = fld_e1;  // fld_e1=this+4 宿主对象
    return pDwArg2;
  }
  else  // 否则分支
  {
    *pDwArg2 = v8;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x49EDC0 sub_49EDC0 —— 红黑树多槽查表（槽内 lower_bound，命中返回条目 +16）
//   槽数组 this+4、槽数 this+8；每槽 12 字节（+4 = header，其 +4 = 树根）；
//   pDwArg3 == -1 → 从槽 0 起逐槽查，命中返回节点 +16（条目载荷地址）；
//   否则只查指定槽 (12 × 槽号)；全未命中返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EDC0(int *this, int nArg2, int *pDwArg3)  // 实现：红黑树多槽查表（槽内 lower_bound，命中返回条目 +16）
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
    fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
    v4 = 0;
    if ( fld_e2 <= 0 )  // 若 fld_e2 <= 0
    {
      return 0;
    }
    else  // 否则分支
    {
      fld_e1 = *(this + 1);  // this+4〔宿主对象〕
      nArg22 = nArg2;
      while ( 1 )  // 条件循环
      {
        v7 = *(uint32_t *)(fld_e1 + 4);  // fld_e1=this+4 宿主对象
        v8 = *(int **)(v7 + 4);
        while ( *((uint8_t *)v8 + 173) == 0 )  // 条件循环
        {
          if ( v8[3] >= nArg22 )
          {
            v7 = (int)v8;
            v8 = (int *)*v8;
          }
          else  // 否则分支
          {
            v8 = (int *)v8[2];
          }
        }
        v9 = *(int **)(fld_e1 + 4);  // fld_e1=this+4 宿主对象
        nArg2 = v7;
        if ( (int *)v7 == v9 || nArg22 < *(uint32_t *)(v7 + 12) )  // 复合条件判定（与/或）
        {
          pDwArg3 = v9;
          v10 = (int *)&pDwArg3;
        }
        else  // 否则分支
        {
          v10 = &nArg2;
        }
        v11 = *v10;
        if ( v11 != *(uint32_t *)(fld_e1 + 4) )  // fld_e1=this+4 宿主对象
          break;  // 跳出循环/分支
        ++v4;
        fld_e1 += 12;  // fld_e1=this+4 宿主对象
        if ( v4 >= fld_e2 )  // 若 v4 >= fld_e2
          return 0;
      }
      return v11 + 16;  // 返回 v11 + 16
    }
  }
  else  // 否则分支
  {
    fld_e12 = (uint32_t *)(*(this + 1) + 12 * (uint32_t)pDwArg3);  // this+4〔宿主对象〕
    v14 = sub_49EC90(fld_e12, &nArg2);  // 红黑树槽定位（首键 >= 键值的节点，lower_bound）
    v15 = (int *)fld_e12[1];  // fld_e12=this+4 宿主对象
    pDwArg3 = v14;
    if ( v14 == v15 || nArg2 < v14[3] )  // 若 v14 == v15 与/或 nArg2 < v14
    {
      nArg2 = (int)v15;
      v16 = &nArg2;
    }
    else  // 否则分支
    {
      v16 = (int *)&pDwArg3;
    }
    v17 = *v16;
    if ( v17 == fld_e12[1] )  // fld_e12=this+4 宿主对象
      return 0;
    else  // 否则分支
      return v17 + 16;  // 返回 v17 + 16
  }
}



// ------------------------------------------------------------
// 0x49EE90 sub_49EE90 —— 槽表遍历计数（·sub_48FD50 为真的条目数）
//   每槽从 header 起用 ·sub_49EBA0 迭代全树；条目载荷位于节点 +16；
//   ·sub_48FD50（载荷 +72 != -1）计数【推断：有效/已选条目数】。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EE90(uint32_t *this, uint32_t *uArg2)  // 实现：槽表遍历计数（·sub_48FD50 为真的条目数）
{
  int v3; // esi
  uint32_t *fld_e1; // ecx
  uint32_t *uArg22; // eax
  int v6; // ebx

  v3 = 12 * (uint32_t)uArg2;
  fld_e1 = *(uint32_t **)(12 * (uint32_t)uArg2 + *(this + 1) + 4);  // fld_e1 = 读 this+1
  uArg22 = (uint32_t *)*fld_e1;
  v6 = 0;
  uArg2 = (uint32_t *)*fld_e1;
  if ( uArg2 != fld_e1 )  // 若 uArg2 != fld_e1
  {
    do  // do-while 循环体起点
    {
      if ( sub_48FD50(uArg22 + 4) )  // 状态位查询（+72 不等于 -1）
        ++v6;
      sub_49EBA0((int *)&uArg2);  // 红黑树迭代器自减（--，中序上一节点）
      uArg22 = uArg2;
    }
    while ( uArg2 != *(uint32_t **)(v3 + *(this + 1) + 4) );  // 条件循环
  }
  return v6;
}



// ------------------------------------------------------------
// 0x49EEE0 sub_49EEE0 —— 槽表遍历求和（·sub_48FBB0 累加非 0xFFFF 字段数）
//   与 ·sub_49EE90 同构（差异：每次命中的增量改为 ·sub_48FBB0 的非 0xFFFF 字段计数）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EEE0(uint32_t *this, int nArg2)  // 实现：槽表遍历求和（·sub_48FBB0 累加非 0xFFFF 字段数）
{
  int v3; // esi
  int *fld_e1; // ecx
  int nArg22; // eax
  bool v6; // zf
  uint32_t *v7; // ebx
  int v9; // [esp+8h] [ebp-4h]

  v3 = 12 * nArg2;
  fld_e1 = *(int **)(12 * nArg2 + *(this + 1) + 4);  // this+4〔宿主对象〕
  nArg22 = *fld_e1;  // fld_e1=this+4 宿主对象
  v6 = *fld_e1 == (uint32_t)fld_e1;  // fld_e1=this+4 宿主对象
  v9 = 0;
  nArg2 = *fld_e1;  // fld_e1=this+4 宿主对象
  if ( v6 )
    return 0;
  do  // do-while 循环体起点
  {
    v7 = (uint32_t *)(nArg22 + 16);  // nArg22+16〔nChannelTypeSel(推断)〕
    if ( sub_48FD50((uint32_t *)(nArg22 + 16)) )  // 状态位查询（+72 不等于 -1）
      v9 += sub_48FBB0(v7);  // 槽表计数（+40..+68 中不等于 0xFFFF 的字段数）
    sub_49EBA0(&nArg2);  // 红黑树迭代器自减（--，中序上一节点）
    nArg22 = nArg2;
  }
  while ( nArg2 != *(uint32_t *)(v3 + *(this + 1) + 4) );  // 条件循环
  return v9;
}



// ------------------------------------------------------------
// 0x49EF60 sub_49EF60 —— 槽表遍历求和（·sub_48F4C0 计非 254 字段数）
//   与 ·sub_49EEE0 同构（差异：改用 ·sub_48F4C0，即 +8..+36 字节区不等于 254 的字段数）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49EF60(uint32_t *this, int nArg2)  // 实现：槽表遍历求和（·sub_48F4C0 计非 254 字段数）
{
  int v3; // esi
  int *fld_e1; // ecx
  int nArg22; // eax
  bool v6; // zf
  uint32_t *v7; // ebx
  int v9; // [esp+8h] [ebp-4h]

  v3 = 12 * nArg2;
  fld_e1 = *(int **)(12 * nArg2 + *(this + 1) + 4);  // this+4〔宿主对象〕
  nArg22 = *fld_e1;  // fld_e1=this+4 宿主对象
  v6 = *fld_e1 == (uint32_t)fld_e1;  // fld_e1=this+4 宿主对象
  v9 = 0;
  nArg2 = *fld_e1;  // fld_e1=this+4 宿主对象
  if ( v6 )
    return 0;
  do  // do-while 循环体起点
  {
    v7 = (uint32_t *)(nArg22 + 16);  // nArg22+16〔nChannelTypeSel(推断)〕
    if ( sub_48FD50((uint32_t *)(nArg22 + 16)) )  // 状态位查询（+72 不等于 -1）
      v9 += sub_48F4C0(v7);  // 槽表计数（+8..+36 中不等于 254 的字段数）
    sub_49EBA0(&nArg2);  // 红黑树迭代器自减（--，中序上一节点）
    nArg22 = nArg2;
  }
  while ( nArg2 != *(uint32_t *)(v3 + *(this + 1) + 4) );  // 条件循环
  return v9;
}



// ------------------------------------------------------------
// 0x49EFE0 sub_49EFE0 —— 槽表按键搜索（·sub_48FB60 按 +4 int16 键；回填载荷/键/槽号）
//   每槽从 header 起迭代；·sub_48FB60(载荷 +16, nArg2) 返回 0 则继续遍历；
//   命中后回填 *uArg3 = 节点 +16（载荷）、*uArg4 = 节点 +12（键）、*uArg5 = 槽号；
//   全表未命中返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_49EFE0(int *this, int nArg2, uint32_t *uArg3, uint32_t *uArg4, uint32_t *uArg5)  // 实现：槽表按键搜索（·sub_48FB60 按 +4 int16 键；回填载荷/键/槽号）
{
  int fld_e2; // ecx
  int *fld_e1; // eax
  int v8; // esi
  bool fld_e22; // cc
  int *v11; // [esp+Ch] [ebp-Ch] BYREF
  int v12; // [esp+10h] [ebp-8h]
  int v13; // [esp+14h] [ebp-4h]

  fld_e2 = *(this + 2);  // this+8〔nSkillRec8(推断)〕
  v12 = 0;
  if ( fld_e2 <= 0 )  // 若 fld_e2 <= 0
    return 0;
  v13 = 0;
  while ( 1 )  // 条件循环
  {
    fld_e1 = *(int **)(v13 + *(this + 1) + 4);  // this+4〔宿主对象〕
    v8 = *fld_e1;  // fld_e1=this+4 宿主对象
    v11 = (int *)*fld_e1;  // fld_e1=this+4 宿主对象
    if ( v11 != fld_e1 )  // 若 v11 != fld_e1
      break;  // 跳出循环/分支
LABEL_6:  // 标签 LABEL_6（跳转合流点）
    fld_e22 = ++v12 < *(this + 2);  // this+8〔nSkillRec8(推断)〕
    v13 += 12;
    if ( !fld_e22 )  // fld_e22=this+8 nSkillRec8
      return 0;
  }
  while ( sub_48FB60((uint32_t *)(v8 + 16), nArg2, nullptr) == 0 )  // 槽按键查找（回填槽号）
  {
    sub_49EBA0((int *)&v11);  // 红黑树迭代器自减（--，中序上一节点）
    v8 = (int)v11;
    if ( v11 == *(int **)(v13 + *(this + 1) + 4) )  // this+4〔宿主对象〕
      goto LABEL_6;
  }
  if ( uArg4 != nullptr )  // 若 uArg4 有效（非空）
    *uArg4 = *(uint32_t *)(v8 + 12);
  if ( uArg5 != nullptr )  // 若 uArg5 有效（非空）
    *uArg5 = v12;
  if ( uArg3 != nullptr )  // 若 uArg3 有效（非空）
    *uArg3 = v8 + 16;
  return 1;  // 返回 1(成功)
}



// ------------------------------------------------------------
// 0x49F090 sub_49F090 —— 红黑树整树递归释放（先子树后本体的后序）
//   递归参数为槽 header 的子节点：先递归 +8 子，再沿 +0 链前进逐节点 ·sub_49EC00 收尾 + j__free；
//   +173 哨兵即停；为 ·sub_49F0E0/·sub_49F750 的释放原语。
// ------------------------------------------------------------
char /*stdcall*/ sub_49F090(void **Block)  // 实现：红黑树整树递归释放（先子树后本体的后序）
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 173);
  for ( i = Block; result == 0; Block2 = i )  // 遍历循环
  {
    sub_49F090(i[2]);  // 红黑树整树递归释放（先子树后本体的后序）
    i = (void **)*i;
    sub_49EC00(Block2);  // 调 收尾 + j__free
    j__free(Block2);  // 调 j__free（堆释放）
    result = *((uint8_t *)i + 173);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49F0E0 sub_49F0E0 —— 槽数组树整体清空（逐槽递归释放 + header 自环复位）
//   槽数 this+8、槽数组 this+4；每槽取 +4 处 header 的 +4（树根）走 ·sub_49F090；
//   随后 header 的 +4/+0/+8 自环复位、槽 +8 计数清 0；
//   尾调 ·sub_48FE80(0)（宿主/UDP 联动收尾）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49F0E0(uint32_t *this)  // 实现：槽数组树整体清空（逐槽递归释放 + header 自环复位）
{
  int v2; // ebx
  int fld_e1; // esi
  int v4; // eax
  int v5; // esi
  uint32_t *v6; // eax
  int v8; // [esp+8h] [ebp-4h]

  v2 = 0;
  if ( (int)*(this + 2) > 0 )  // this+8〔nSkillRec8(推断)〕
  {
    v8 = 0;
    do  // do-while 循环体起点
    {
      fld_e1 = *(this + 1);  // this+4〔宿主对象〕
      v4 = *(uint32_t *)(fld_e1 + v8 + 4);  // fld_e1=this+4 宿主对象
      v5 = v8 + fld_e1;
      sub_49F090(*(void ***)(v4 + 4));  // 红黑树整树递归释放（先子树后本体的后序）
      *(uint32_t *)(*(uint32_t *)(v5 + 4) + 4) = *(uint32_t *)(v5 + 4);
      v6 = *(uint32_t **)(v5 + 4);
      *(uint32_t *)(v5 + 8) = 0;
      *v6 = v6;
      *(uint32_t *)(*(uint32_t *)(v5 + 4) + 8) = *(uint32_t *)(v5 + 4);
      ++v2;
      v8 += 12;
    }
    while ( v2 < *(this + 2) );  // 条件循环
  }
  return sub_48FE80(0);  // 宿主/UDP 联动收尾（@@SET HOST、sub_42F160）
}



// ------------------------------------------------------------
// 0x49F150 sub_49F150 —— 红黑树插入 + 重平衡（CLR 修正 + map/set too long 保护）
//   this 为单槽（+4 = header、+8 = 计数），计数 >= 0x1999998 时抛 map/set<T> too long；
//   ·sub_49ECD0 分配节点并按 pszArg3 挂到 pArg4 的左/右，空槽时 header 三指针同指新节点；
//   随后沿父链重着色 + ·sub_49EAB0/·sub_49EC30 旋转修正，尾置根为黑。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_49F150(int *this, uint32_t *uArg2, char pszArg3, uint32_t *pArg4, uint32_t *uArg5)  // 实现：红黑树插入 + 重平衡（CLR 修正 + map/set too long 保护）
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

  if ( (unsigned int)*(this + 2) >= 0x1999998 )  // this+8〔nSkillRec8(推断)〕
  {
    v20 = 15;
    v19 = 0;
    v18 = 0;
    sub_4015C0(&v17, "map/set<T> too long", 0x13u);  // 【std::string构造赋值】
    v21 = 0;
    sub_401740(pExceptionObject, &v17);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  fld_e1 = sub_49ECD0(*(this + 1), (int)pArg4, *(this + 1), uArg5, 0);  // 红黑树节点分配（0xB0 字节：指针三件 + 键 + 载荷 0x98 拷贝）
  fld_e12 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  fld_e15 = fld_e1;
  ++*(this + 2);  // this+8〔nSkillRec8(推断)〕
  if ( pArg4 == fld_e12 )  // 若 pArg4 == fld_e12
  {
    fld_e12[1] = fld_e1;  // fld_e12=this+4 宿主对象
    *(uint32_t *)*(this + 1) = fld_e1;  // this+4〔宿主对象〕
    *(uint32_t *)(*(this + 1) + 8) = fld_e1;  // this+4〔宿主对象〕
  }
  else if ( pszArg3 != 0 )
  {
    *pArg4 = fld_e1;
    fld_e13 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == (uint32_t *)*fld_e13 )  // fld_e13=this+4 宿主对象
      *fld_e13 = fld_e1;  // fld_e13=this+4 宿主对象
  }
  else  // 否则分支
  {
    pArg4[2] = fld_e1;
    fld_e14 = *(this + 1);  // this+4〔宿主对象〕
    if ( pArg4 == *(uint32_t **)(fld_e14 + 8) )  // fld_e14=this+4 宿主对象
      *(uint32_t *)(fld_e14 + 8) = fld_e1;  // fld_e14=this+4 宿主对象
  }
  v10 = fld_e1 + 1;
  v11 = (int)fld_e1;
  if ( *(uint8_t *)(fld_e1[1] + 172) == 0 )
  {
    while ( 1 )  // 条件循环
    {
      v12 = (uint32_t *)*v10;
      v13 = *(int **)(*v10 + 4);
      v14 = *v13;
      if ( *v10 == *v13 )
      {
        v14 = v13[2];  // v14 = 取 v13[2]
        if ( *(uint8_t *)(v14 + 172) != 0 )
        {
          if ( v11 == v12[2] )
          {
            v11 = *v10;
            sub_49EC30(this, *v10);  // 红黑树左旋（+8 子提升为新子树根，与 ·sub_49EAB0 镜像）
          }
          *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) = 1;
          *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 172) = 0;
          sub_49EAB0(this, *(uint32_t **)(*(uint32_t *)(v11 + 4) + 4));  // 红黑树右旋（+0 子提升为新子树根）
          goto LABEL_21;
        }
      }
      else if ( *(uint8_t *)(v14 + 172) != 0 )
      {
        if ( v11 == *v12 )
        {
          v11 = *v10;
          sub_49EAB0(this, (uint32_t *)*v10);  // 红黑树右旋（+0 子提升为新子树根）
        }
        *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) = 1;
        *(uint8_t *)(*(uint32_t *)(*(uint32_t *)(v11 + 4) + 4) + 172) = 0;
        sub_49EC30(this, *(uint32_t *)(*(uint32_t *)(v11 + 4) + 4));  // 红黑树左旋（+8 子提升为新子树根，与 ·sub_49EAB0 镜像）
        goto LABEL_21;
      }
      *(uint8_t *)(*v10 + 172) = 1;
      *(uint8_t *)(v14 + 172) = 1;
      *(uint8_t *)(*(uint32_t *)(*v10 + 4) + 172) = 0;
      v11 = *(uint32_t *)(*v10 + 4);
LABEL_21:  // 标签 LABEL_21（跳转合流点）
      v10 = (int *)(v11 + 4);
      if ( *(uint8_t *)(*(uint32_t *)(v11 + 4) + 172) != 0 )
      {
        fld_e1 = fld_e15;
        break;  // 跳出循环/分支
      }
    }
  }
  *(uint8_t *)(*(uint32_t *)(*(this + 1) + 4) + 172) = 1;  // this+4〔宿主对象〕
  *uArg2 = fld_e1;
  return uArg2;
}



// ------------------------------------------------------------
// 0x49F330 sub_49F330 —— 槽查找或插入（lower_bound 与插入判定）
//   this 为单槽；沿树下降比较节点 +12 键，命中则返回既有节点（*pArg2 = 节点、+4 = 0），
//   未命中改走 ·sub_49F150 插入（+4 = 1 表示新建）。
// ------------------------------------------------------------
int /*thiscall*/ sub_49F330(int *this, int pArg2, uint32_t *uArg3)  // 实现：槽查找或插入（lower_bound 与插入判定）
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
  fld_e1 = (uint32_t *)*(this + 1);  // this+4〔宿主对象〕
  v6 = (int *)fld_e1[1];  // fld_e1=this+4 宿主对象
  v7 = true;
  v13 = 1;
  if ( *((uint8_t *)v6 + 173) == 0 )
  {
    v8 = *uArg3;
    do  // do-while 循环体起点
    {
      v7 = v8 < v6[3];
      fld_e1 = v6;  // fld_e1=this+4 宿主对象
      v13 = v7;
      if ( v8 >= v6[3] )
        v6 = (int *)v6[2];
      else  // 否则分支
        v6 = (int *)*v6;
    }
    while ( *((uint8_t *)v6 + 173) == 0 );  // 条件循环
  }
  fld_e12 = fld_e1;  // fld_e1=this+4 宿主对象
  uArg3 = fld_e1;  // fld_e1=this+4 宿主对象
  if ( v7 )
  {
    if ( fld_e1 == *(uint32_t **)*(this + 1) )  // this+4〔宿主对象〕
    {
      v10 = *sub_49F150(this, &uArg3, 1, fld_e1, uArg32);  // 红黑树插入 + 重平衡（CLR 修正 + map/set too long 保护）
      *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
      *(uint32_t *)pArg2 = v10;  // *pArg2 = v10
      return pArg2;
    }
    sub_49EB20(&uArg3);  // 红黑树迭代器自增（++，中序下一节点）
    fld_e12 = uArg3;
  }
  if ( fld_e12[3] >= *uArg32 )
  {
    *(uint8_t *)(pArg2 + 4) = 0;  // pArg2+4〔宿主对象〕
    *(uint32_t *)pArg2 = fld_e12;
    return pArg2;
  }
  else  // 否则分支
  {
    v12 = *sub_49F150(this, &uArg3, v13, fld_e1, uArg32);  // 红黑树插入 + 重平衡（CLR 修正 + map/set too long 保护）
    *(uint32_t *)pArg2 = v12;  // *pArg2 = v12
    *(uint8_t *)(pArg2 + 4) = 1;  // pArg2+4〔宿主对象〕
    return pArg2;
  }
}



// ------------------------------------------------------------
// 0x49F3F0 sub_49F3F0 —— 红黑树节点删除 + 双黑修正（rebalance_for_erase）
//   先按左/右子与父指针重挂接，再沿父链做删除修正（·sub_49EAB0/·sub_49EC30 旋转）；
//   被删节点本体 CNWarRoom 析构 + j__free，槽计数 -1；
//   pArg3 命中哨兵（+173 非 0）时抛 invalid map/set<T> iterator。
// ------------------------------------------------------------
int */*thiscall*/ sub_49F3F0(uint32_t *this, int *pDwArg2, int pArg3)  // 实现：红黑树节点删除 + 双黑修正（rebalance_for_erase）
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
    sub_401740(pExceptionObject, &v21);  // std::logic_error 构造（·sub_66AF9C 基类 + logic_error::vftable + 存消息串）
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = (int *)a3;
  Block = (void *)a3;
  sub_49EBA0(&a3);  // 红黑树迭代器自减（--，中序上一节点）
  if ( *(uint8_t *)(*v3 + 173) != 0 )
  {
    v4 = v3[2];  // v4 = 取 v3[2]
LABEL_8:  // 标签 LABEL_8（跳转合流点）
    v6 = v3[1];  // v6 = 取 v3[1]
    if ( *(uint8_t *)(v4 + 173) == 0 )
      *(uint32_t *)(v4 + 4) = v6;
    v7 = v27;
    v8 = v27[1];  // v8 = 取 v27[1]
    if ( *(int **)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( *(int **)v6 == v3 )
    {
      *(uint32_t *)v6 = v4;  // *v6 = v4
    }
    else  // 否则分支
    {
      *(uint32_t *)(v6 + 8) = v4;
    }
    if ( *(int **)v7[1] == v3 )
    {
      if ( *(uint8_t *)(v4 + 173) != 0 )
      {
        v9 = (uint32_t *)v6;
      }
      else  // 否则分支
      {
        v9 = sub_49EA80((uint32_t *)v4);  // 红黑树节点下行（沿 +0 链至哨兵）
        v7 = v27;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];  // v10 = 取 v7[1]
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
    v25 = v10;
    if ( v11 )
    {
      if ( *(uint8_t *)(v4 + 173) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else  // 否则分支
        *(uint32_t *)(v25 + 8) = sub_49EA50(v4);  // 红黑树节点下行（沿 +8 链至哨兵，返回最深节点）
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
  else  // 否则分支
  {
    v6 = *(uint32_t *)(v5 + 4);
    if ( *(uint8_t *)(v4 + 173) == 0 )
      *(uint32_t *)(v4 + 4) = v6;
    *(uint32_t *)v6 = v4;  // *v6 = v4
    *(uint32_t *)(v5 + 8) = v3[2];
    *(uint32_t *)(v3[2] + 4) = v5;
  }
  v12 = v27[1];  // v12 = 取 v27[1]
  if ( *(int **)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else  // 否则分支
  {
    v13 = (int *)v3[1];
    if ( (int *)*v13 == v3 )
      *v13 = v5;
    else  // 否则分支
      v13[2] = v5;
  }
  *(uint32_t *)(v5 + 4) = v3[1];
  v14 = *(uint8_t *)(v5 + 172);
  *(uint8_t *)(v5 + 172) = *((uint8_t *)v3 + 172);
  *((uint8_t *)v3 + 172) = v14;  // v3[172] = v14
LABEL_35:  // 标签 LABEL_35（跳转合流点）
  if ( *((uint8_t *)Block + 172) == 1 )
  {
    v15 = v27;
    if ( v4 != *(uint32_t *)(v27[1] + 4) )
    {
      do  // do-while 循环体起点
      {
        if ( *(uint8_t *)(v4 + 172) != 1 )
          break;  // 跳出循环/分支
        v16 = *(uint8_t **)v6;
        if ( v4 == *(uint32_t *)v6 )
        {
          v16 = *(uint8_t **)(v6 + 8);
          if ( v16[172] == 0 )
          {
            v16[172] = 1;
            *(uint8_t *)(v6 + 172) = 0;
            sub_49EC30(v15, v6);  // 红黑树左旋（+8 子提升为新子树根，与 ·sub_49EAB0 镜像）
            v16 = *(uint8_t **)(v6 + 8);
            v15 = v27;
          }
          if ( v16[173] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*(uint32_t *)v16 + 172) != 1 || *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) != 1 )  // 复合条件判定（与/或）
          {
            if ( *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) == 1 )
            {
              *(uint8_t *)(*(uint32_t *)v16 + 172) = 1;
              v16[172] = 0;
              sub_49EAB0(v15, v16);  // 红黑树右旋（+0 子提升为新子树根）
              v16 = *(uint8_t **)(v6 + 8);
              v15 = v27;
            }
            v16[172] = *(uint8_t *)(v6 + 172);
            *(uint8_t *)(v6 + 172) = 1;
            *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) = 1;
            sub_49EC30(v15, v6);  // 红黑树左旋（+8 子提升为新子树根，与 ·sub_49EAB0 镜像）
            break;  // 跳出循环/分支
          }
        }
        else  // 否则分支
        {
          if ( v16[172] == 0 )
          {
            v16[172] = 1;
            *(uint8_t *)(v6 + 172) = 0;
            sub_49EAB0(v15, (uint32_t *)v6);  // 红黑树右旋（+0 子提升为新子树根）
            v16 = *(uint8_t **)v6;
            v15 = v27;
          }
          if ( v16[173] != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) != 1 || *(uint8_t *)(*(uint32_t *)v16 + 172) != 1 )  // 复合条件判定（与/或）
          {
            if ( *(uint8_t *)(*(uint32_t *)v16 + 172) == 1 )
            {
              *(uint8_t *)(*((uint32_t *)v16 + 2) + 172) = 1;
              v16[172] = 0;
              sub_49EC30(v15, (int)v16);  // 红黑树左旋（+8 子提升为新子树根，与 ·sub_49EAB0 镜像）
              v16 = *(uint8_t **)v6;
              v15 = v27;
            }
            v16[172] = *(uint8_t *)(v6 + 172);
            *(uint8_t *)(v6 + 172) = 1;
            *(uint8_t *)(*(uint32_t *)v16 + 172) = 1;
            sub_49EAB0(v15, (uint32_t *)v6);  // 红黑树右旋（+0 子提升为新子树根）
            break;  // 跳出循环/分支
          }
        }
        v16[172] = 0;
LABEL_53:  // 标签 LABEL_53（跳转合流点）
        v4 = v6;
        v11 = v6 == *(uint32_t *)(v15[1] + 4);
        v6 = *(uint32_t *)(v6 + 4);
      }
      while ( !v11 );  // 条件循环
    }
    *(uint8_t *)(v4 + 172) = 1;
  }
  v17 = (char *)Block + 16;
  *((uint32_t *)Block + 4) = &CNWarRoom::`vftable';  // 构造装配 vftable：CNWarRoom
  nullsub_3(v17);
  j__free(Block);  // 调 j__free（堆释放）
  v18 = pThis[2];  // v18 = 取 pThis[2]
  if ( v18 != 0 )  // 若 v18 非 0
    pThis[2] = v18 - 1;
  *pDwArg2 = pArg3;
  return pDwArg2;
}


// ------------------------------------------------------------
// 0x49F750 sub_49F750 —— 红黑树区间删除（first..last 逐节点 ·sub_49F3F0）
//   首末同为一槽 header（整槽区间）时走 ·sub_49F090 整树释放 + header 自环复位；
//   否则逐节点：·sub_49EBA0 前推 + ·sub_49F3F0 删除。
// ------------------------------------------------------------
int */*thiscall*/ sub_49F750(int **this, int *pDwArg2, int nArg3, int nArg4)  // 实现：红黑树区间删除（first..last 逐节点 ·sub_49F3F0）
{
  int nArg42; // ebx
  int fld_e1; // eax
  int nArg32; // ecx
  uint32_t *fld_e12; // eax
  int nArg322; // edi

  nArg42 = nArg4;
  fld_e1 = (int)*(this + 1);  // this+4〔宿主对象〕
  nArg32 = nArg3;
  if ( nArg3 == *(uint32_t *)fld_e1 && nArg4 == fld_e1 )  // 若 nArg4 == fld_e1
  {
    sub_49F090(*(void ***)(fld_e1 + 4));  // 红黑树整树递归释放（先子树后本体的后序）
    (*(this + 1))[1] = (int)*(this + 1);  // this+4〔宿主对象〕
    fld_e12 = *(this + 1);  // this+4〔宿主对象〕
    *(this + 2) = nullptr;  // this+8〔nSkillRec8(推断)〕
    *fld_e12 = fld_e12;  // fld_e12=this+4 宿主对象
    (*(this + 1))[2] = (int)*(this + 1);  // this+4〔宿主对象〕
    *pDwArg2 = **(this + 1);  // this+4〔宿主对象〕
    return pDwArg2;
  }
  else  // 否则分支
  {
    if ( nArg3 != nArg4 )  // 若 nArg3 != nArg4
    {
      do  // do-while 循环体起点
      {
        nArg322 = nArg32;
        sub_49EBA0(&nArg3);  // 红黑树迭代器自减（--，中序上一节点）
        sub_49F3F0(this, &nArg4, nArg322);  // 红黑树节点删除 + 双黑修正（rebalance_for_erase）
        nArg32 = nArg3;
      }
      while ( nArg3 != nArg42 );  // 条件循环
    }
    *pDwArg2 = nArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x49F7D0 sub_49F7D0 —— 槽条目改写或新建插入（未命中则建载荷再插）
//   先用 ·sub_49EDC0 按槽号定位：命中直接返回条目 +16；
//   未命中时 new(0x9C) 载荷（CNWarRoom vftable + ·sub_49E990 初值）后 ·sub_49F330 插入槽，
//   再以 lower_bound 重取并返回条目指针。
// ------------------------------------------------------------
int /*thiscall*/ sub_49F7D0(int *this, int nArg2, int *pDwArg3)  // 实现：槽条目改写或新建插入（未命中则建载荷再插）
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
  result = sub_49EDC0(this, nArg2, pDwArg3);  // 红黑树多槽查表（槽内 lower_bound，命中返回条目 +16）
  if ( result == 0 )  // 若 result 为 0
  {
    pMem = operator new(0x9Cu);  // new(156 字节) 分配对象
    pMem2 = pMem;
    Block = pMem;
    v20 = 0;
    if ( pMem != nullptr )  // 若 pMem 有效（非空）
    {
      *pMem = &CNWarRoom::`vftable';  // 构造装配 vftable：CNWarRoom
      sub_49E990(v5 + 1);  // 列表子项初值（+4..+32 = 255、+36..+64 = 0xFFFF）
      nullsub_3(v6);
      unknown_libname_7(v3);
    }
    else  // 否则分支
    {
      v6 = nullptr;  // v6 = 空指针
    }
    v7 = a3;
    v15 = v3;
    *((uint8_t *)v6 + 152) = (uint8_t)a3;
    v16[0] = &CNWarRoom::`vftable';  // 构造装配 vftable：CNWarRoom
    qmemcpy(&v16[1], pMem2 + 1, 0x98u);  // 调 qmemcpy（内存块拷贝(内联展开)）
    pThis2 = pThis;
    v9 = 12 * (uint32_t)pDwArg32;
    v10 = (int *)(12 * (uint32_t)pDwArg32 + pThis[1]);
    v20 = 1;
    sub_49F330(v10, (int)v17, &nArg222);  // 槽查找或插入（lower_bound 与插入判定）
    v20 = -1;
    v16[0] = &CNWarRoom::`vftable';  // 构造装配 vftable：CNWarRoom
    nullsub_3(v16);
    (*(void (/*thiscall*/ **)(uint32_t *, int))*pMem2)(pMem2, 1);
    v11 = (uint32_t *)(v9 + pThis2[1]);
    v12 = sub_49EC90(v11, &nArg2);  // 红黑树槽定位（首键 >= 键值的节点，lower_bound）
    v13 = (int *)v11[1];
    pDwArg3 = v12;
    if ( v12 == v13 || nArg2 < v12[3] )  // 若 v12 == v13 与/或 nArg2 < v12
    {
      nArg2 = (int)v13;
      v14 = (int **)&nArg2;
    }
    else  // 否则分支
    {
      v14 = &pDwArg3;
    }
    return (int)(*v14 + 4);
  }
  return result;
}



// ------------------------------------------------------------
// 0x49F900 sub_49F900 —— 单槽销毁（全树区间删除 + 释放 header）
//   ·sub_49F750 清空该槽全树后 j__free(header)，this+4/+8 置空。
// ------------------------------------------------------------
void /*thiscall*/ sub_49F900(int **this)  // 实现：单槽销毁（全树区间删除 + 释放 header）
{
  int v2; // [esp+4h] [ebp-4h] BYREF

  sub_49F750(this, &v2, **(this + 1), (int)*(this + 1));  // 红黑树区间删除（first..last 逐节点 ·sub_49F3F0）
  j__free(*(this + 1));  // this+4〔宿主对象〕
  *(this + 1) = nullptr;  // this+4〔宿主对象〕
  *(this + 2) = nullptr;  // this+8〔nSkillRec8(推断)〕
}



// ------------------------------------------------------------
// 0x49F940 sub_49F940 —— 单槽初始化（分配 header 哨兵 + 自环空树）
//   ·sub_49ED30 建 0xB0 哨兵，+173 = 1（哨兵标记）、header 的 +4/+0/+8 三指针自指；
//   槽计数 this+8 = 0。
// ------------------------------------------------------------
void /*thiscall*/ sub_49F940(uint32_t *this)  // 实现：单槽初始化（分配 header 哨兵 + 自环空树）
{
  uint32_t *v2; // eax

  v2 = sub_49ED30();  // 红黑树槽 header 分配（0xB0 字节，+172 = 1 黑）
  *(this + 1) = v2;  // this+4〔宿主对象〕
  *((uint8_t *)v2 + 173) = 1;  // v2[173] = 1
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);  // this+4〔宿主对象〕
  *(uint32_t *)*(this + 1) = *(this + 1);  // this+4〔宿主对象〕
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);  // this+4〔宿主对象〕
  *(this + 2) = 0;  // this+8〔nSkillRec8(推断)〕
}



// ------------------------------------------------------------
// 0x49F970 sub_49F970 —— 槽数组创建（Block 槽 × 12 字节 + 头部计数）
//   operator new(12 × Block + 4)，首 4 字节存槽数；
//   eh vector constructor iterator 逐槽 ·sub_49F940（析构器 ·sub_49F900）；
//   尾调 ·sub_49F0E0 复位全部槽树。
// ------------------------------------------------------------
int /*thiscall*/ sub_49F970(uint32_t *this, int Block)  // 实现：槽数组创建（Block 槽 × 12 字节 + 头部计数）
{
  int *pMem; // eax
  uint32_t *v4; // edi

  *(this + 2) = Block;  // this+8〔nSkillRec8(推断)〕
  pMem = (int *)operator new(12 * Block + 4);
  v4 = nullptr;  // v4 = 空指针
  if ( pMem != nullptr )  // 若 pMem 有效（非空）
  {
    v4 = pMem + 1;
    *pMem = Block;
    `eh vector constructor iterator'(
      pMem + 1,
      0xCu,
      Block,
      (void (/*thiscall*/ *)(void *))sub_49F940,  // 单槽初始化（分配 header 哨兵 + 自环空树）
      (void (/*thiscall*/ *)(void *))sub_49F900);  // 单槽销毁（全树区间删除 + 释放 header）
  }
  *(this + 1) = v4;  // this+4〔宿主对象〕
  return sub_49F0E0(this);  // 槽数组树整体清空（逐槽递归释放 + header 自环复位）
}



// ------------------------------------------------------------
// 0x49F9F0 sub_49F9F0 —— 槽数组析构（eh vector destructor iterator 逐槽 ·sub_49F900）
//   元素尺寸 0xC，槽数取自分配头前 4 字节（基址 - 4）。
// ------------------------------------------------------------
void /*thiscall*/ sub_49F9F0(uint32_t *this)  // 实现：槽数组析构（eh vector destructor iterator 逐槽 ·sub_49F900）
{
  char *fld_e1; // eax
  char *v2; // esi

  fld_e1 = (char *)*(this + 1);  // this+4〔宿主对象〕
  if ( fld_e1 != nullptr )  // 若 fld_e1 有效（非空）
  {
    v2 = fld_e1 - 4;  // fld_e1=this+4 宿主对象
    `eh vector destructor iterator'(fld_e1, 0xCu, *((uint32_t *)fld_e1 - 1), (void (/*thiscall*/ *)(void *))sub_49F900);  // 单槽销毁（全树区间删除 + 释放 header）
    j_j__free(v2);
  }
}



// ------------------------------------------------------------
// 0x49FA20 sub_49FA20 —— 三字段组写（+40/+44/+48）
// ------------------------------------------------------------
int /*thiscall*/ sub_49FA20(int this, uint32_t *pArg2, uint32_t *uArg3, uint32_t *uArg4)  // 实现：三字段组写（+40/+44/+48）
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
  do  // do-while 循环体起点
  {
    v24 = (uint64_t)(*pThis * 10.0);
    if ( v24 != 0 )  // 若 v24 非 0
    {
      if ( (unsigned int)(uint64_t)(*(float *)&v23[(uint32_t)pThis] * 10.0) == v24 )
      {
        v4 |= 2 << v5;
      }
      else  // 否则分支
      {
        *uArg3++ = *(uint32_t *)pThis;
        *uArg4 += 4;
      }
    }
    else  // 否则分支
    {
      v4 |= 1 << v5;
    }
    v5 += 2;
    ++pThis;
  }
  while ( v5 < 6 );  // 条件循环
  v26 = v4 << 26;
  v7 = 0;
  v8 = 0;
  pThis_C = (float *)(this + 12);  // this+12〔nSkillRec12(推断)〕等 2 字段
  do  // do-while 循环体起点
  {
    v25 = (uint64_t)(*pThis_C * 10.0);  // pThis_C=this+12 nSkillRec12
    if ( v25 != 0 )  // 若 v25 非 0
    {
      if ( (unsigned int)(uint64_t)(*(float *)&v23[(uint32_t)pThis_C] * 10.0) == v25 )  // pThis_C=this+12 nSkillRec12
      {
        v7 |= 2 << v8;
      }
      else  // 否则分支
      {
        *uArg3++ = *(uint32_t *)pThis_C;  // pThis_C=this+12 nSkillRec12
        *uArg4 += 4;
      }
    }
    else  // 否则分支
    {
      v7 |= 1 << v8;
    }
    v8 += 2;
    ++pThis_C;  // pThis_C=this+12 nSkillRec12
  }
  while ( v8 < 6 );  // 条件循环
  fld_18 = *(uint32_t *)(this + 24);  // fld_18 = 读 this+24
  v11 = 0;
  v27 = (v7 << 20) | v26;
  if ( fld_18 != 0 )  // 若 fld_18 非 0
  {
    uArg32 = uArg3;
    if ( pArg2[6] == fld_18 )  // fld_18=this+24 页数上限
    {
      uArg42 = uArg4;
      v11 = 2;
    }
    else  // 否则分支
    {
      *uArg3 = fld_18;  // fld_18=this+24 页数上限
      uArg42 = uArg4;
      uArg32 = uArg3 + 1;
      *uArg4 += 4;
    }
  }
  else  // 否则分支
  {
    uArg42 = uArg4;
    uArg32 = uArg3;
    v11 = 1;
  }
  fld_1C = *(uint32_t *)(this + 28);  // fld_1C = 读 this+28
  if ( fld_1C != 0 )  // 若 fld_1C 非 0
  {
    if ( pArg2[7] == fld_1C )  // fld_1C=this+28 逐帧驱动对象
    {
      v11 |= 8u;
    }
    else  // 否则分支
    {
      *uArg32++ = fld_1C;  // fld_1C=this+28 逐帧驱动对象
      *uArg42 += 4;
    }
  }
  else  // 否则分支
  {
    v11 |= 4u;
  }
  fld_20 = *(uint32_t *)(this + 32);  // fld_20 = 读 this+32
  if ( fld_20 != 0 )  // 若 fld_20 非 0
  {
    if ( pArg2[8] == fld_20 )  // fld_20=this+32 格子像素尺寸
    {
      v11 |= 0x20u;
    }
    else  // 否则分支
    {
      *uArg32++ = fld_20;  // fld_20=this+32 格子像素尺寸
      *uArg42 += 4;
    }
  }
  else  // 否则分支
  {
    v11 |= 0x10u;
  }
  v16 = (v11 << 14) | v27;
  fld_24 = *(uint32_t *)(this + 36);  // fld_24 = 读 this+36
  v28 = v16;
  v18 = 0;
  if ( fld_24 != 0 )  // 若 fld_24 非 0
  {
    if ( pArg2[9] == fld_24 )  // fld_24=this+36 物品状态字
    {
      v18 = 2;
    }
    else if ( fld_24 == -1 )  // fld_24=this+36 物品状态字
    {
      v18 = 3;
    }
    else  // 否则分支
    {
      *uArg32++ = fld_24;  // fld_24=this+36 物品状态字
      *uArg42 += 4;
    }
  }
  else  // 否则分支
  {
    v18 = 1;
  }
  fld_28 = *(uint32_t *)(this + 40);  // fld_28 = 读 this+40
  if ( fld_28 != 0 )  // 若 fld_28 非 0
  {
    if ( pArg2[10] == fld_28 )  // fld_28=this+40 物品状态附属标志
    {
      v18 |= 8u;
    }
    else if ( fld_28 == -1 )  // fld_28=this+40 物品状态附属标志
    {
      v18 |= 0xCu;
    }
    else  // 否则分支
    {
      *uArg32++ = fld_28;  // fld_28=this+40 物品状态附属标志
      *uArg42 += 4;
    }
  }
  else  // 否则分支
  {
    v18 |= 4u;
  }
  fld_2C = *(uint32_t *)(this + 44);  // fld_2C = 读 this+44
  if ( fld_2C != 0 )  // 若 fld_2C 非 0
  {
    if ( pArg2[11] == fld_2C )  // fld_2C=this+44 剩余时间 ms
    {
      v18 |= 0x20u;
    }
    else if ( fld_2C == -1 )  // fld_2C=this+44 剩余时间 ms
    {
      v18 |= 0x30u;
    }
    else  // 否则分支
    {
      *uArg32 = fld_2C;  // fld_2C=this+44 剩余时间 ms
      *uArg42 += 4;
    }
  }
  else  // 否则分支
  {
    v18 |= 0x10u;
  }
  return v28 | (32 * ((8 * v18) | *(uint8_t *)(this + 48) & 7));  // this+48〔pCmdVecBegin48(推断)〕等 2 字段
}


// ------------------------------------------------------------
// 0x49FC60 sub_49FC60 —— 七字段访问器（+44..+57 全量下发）
// ------------------------------------------------------------
int /*thiscall*/ sub_49FC60(char *this)  // 实现：七字段访问器（+44..+57 全量下发）
{
  *(uint32_t *)this = 0;  // *this = 0
  *((uint32_t *)this + 26) = 0;  // this[26] = 0
  *(this + 108) = 1;  // this+108 第 1 组·宿主属性 +886 增量
  *((uint32_t *)this + 28) = 0;  // this+112〔pHostComp112〕
  *(this + 116) = 0;  // this+116 观察者 vector 尾针
  *(uint16_t *)(this + 117) = 0;
  *(this + 119) = 0;
  *((uint32_t *)this + 30) = 0;  // this+120〔pAnimObj〕
  *((uint32_t *)this + 32) = 0;  // this[32] = 0
  *((uint32_t *)this + 33) = 0;  // this[33] = 0
  *((uint32_t *)this + 34) = 0;  // this[34] = 0
  *((uint32_t *)this + 35) = 0;  // this[35] = 0
  *(this + 172) = 0;  // this+688〔nSnapshot688〕
  *((uint32_t *)this + 44) = 0;  // this[44] = 0
  *((uint32_t *)this + 45) = 0;  // this[45] = 0
  *((uint32_t *)this + 46) = 0;  // this[46] = 0
  *((uint32_t *)this + 47) = 0;  // this[47] = 0
  *((uint32_t *)this + 48) = 0;  // this[48] = 0
  *(this + 196) = 0;
  *((uint32_t *)this + 50) = 0;  // this[50] = 0
  *(this + 124) = 0;  // this+124 第 2 组·+858/+1292 增量
  *((uint32_t *)this + 1) = 0;  // this[1] = 0
  *((uint32_t *)this + 4) = 0;  // this[4] = 0
  *((uint32_t *)this + 7) = 0;  // this[7] = 0
  *((uint32_t *)this + 2) = 0;  // this[2] = 0
  *((uint32_t *)this + 5) = 0;  // this[5] = 0
  *((uint32_t *)this + 8) = 0;  // this[8] = 0
  *((uint32_t *)this + 3) = 0;  // this[3] = 0
  *((uint32_t *)this + 6) = 0;  // this[6] = 0
  *((uint32_t *)this + 9) = 0;  // this[9] = 0
  *((uint32_t *)this + 10) = -1;  // this[10] = -1
  *((uint32_t *)this + 11) = -1;  // this[11] = -1
  *((uint32_t *)this + 12) = -1;  // this[12] = -1
  *(this + 52) = 1;  // this+208〔nField208(推断)〕
  *(uint32_t *)(this + 53) = 0;  // this+212〔nField212(推断)〕
  *(uint32_t *)(this + 65) = 0;  // this+260〔nQuad4〕
  *(uint32_t *)(this + 77) = 0;  // this+77〔bGuildFlagB〕
  *(uint32_t *)(this + 89) = -1;  // this+89〔nLifetime〕
  *(uint32_t *)(this + 57) = 0;  // this+228〔nSnapDst228(推断)〕
  *(uint32_t *)(this + 69) = 0;  // this+276〔pMapEntry(推断)〕
  *(uint32_t *)(this + 81) = 0;  // this+324〔nAnchor324(推断)〕
  *(uint32_t *)(this + 93) = -1;  // this+93〔bEnableFlag〕
  *(uint32_t *)(this + 61) = 0;  // this+61〔bReadyFlagA〕
  *(uint32_t *)(this + 73) = 0;  // this+73〔szDigitalName(推断)〕等 2 字段
  *(uint32_t *)(this + 85) = 0;  // this+340〔pSlotTbl340(推断)〕
  *(uint32_t *)(this + 97) = -1;  // this+97〔bFlag97〕
  *(this + 101) = 1;  // this+101 已播标志
  return 0;
}



// ------------------------------------------------------------
// 0x49FD20 sub_49FD20 —— +200 状态位（sub_698F90 复位）
// ------------------------------------------------------------
char /*thiscall*/ sub_49FD20(int this)  // 实现：+200 状态位（sub_698F90 复位）
{
  int fld_68; // ecx
  char result; // al
  int fld_C8; // ecx

  fld_68 = *(uint32_t *)(this + 104);  // fld_68 = 读 this+104
  if ( fld_68 != 0 )  // 若 fld_68 非 0
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)fld_68 + 4))(fld_68, 0);  // 调虚槽 +4：CNTargetIt__vmt4 复位/锁定（64F690 + 64A790 + 69900…
  *(uint8_t *)(this + 157) = 0;
  *(uint8_t *)(this + 158) = 0;
  result = sub_698F90(this + 144, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  fld_C8 = *(uint32_t *)(this + 200);  // fld_C8 = 读 this+200
  *(uint32_t *)(this + 176) = 0;  // this+176〔pAppendVecCap(推断)〕等 2 字段
  *(uint32_t *)(this + 180) = -fld_C8;  // this+180〔nRadius(推断)〕
  *(uint32_t *)(this + 184) = 0;  // this+184〔bSingleTarget(推断)〕
  *(uint32_t *)(this + 188) = 0;  // this+188〔nStatusIdx(推断)〕
  *(uint32_t *)(this + 192) = 0;  // this+192〔nDlgId(推断)〕
  *(uint8_t *)(this + 196) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x49FD80 sub_49FD80 —— 渲染参数（+40 → sub_432F40）
// ------------------------------------------------------------
int /*thiscall*/ sub_49FD80(float *this, int pArg2, float *pArg3)  // 实现：渲染参数（+40 → sub_432F40）
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

  if ( *(this + pArg2 + 4) == 0.0 && *((uint32_t *)this + pArg2 + 7) == 0 )  // 复合条件判定（与/或）
    return 0;
  v6 = *((uint32_t *)this + pArg2 + 7);
  v7 = *(this + pArg2 + 4);
  v8 = *((uint32_t *)this + pArg2 + 10);
  v26 = v8;
  if ( v6 != 0 )  // 若 v6 非 0
  {
    pArg32 = pArg3;
    if ( v8 == -1 || v8 >= (int)pArg3 )  // 若 v8 == -1
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
    else  // 否则分支
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
  if ( *((uint32_t *)this + 26) != 0 && *((uint8_t *)this + 108) != 0 )  // 复合条件判定（与/或）
    goto LABEL_25;
  if ( *(uint32_t *)this == 0 )
    goto LABEL_25;
  v23 = 0;
  v24 = 0;
  v25 = 0;
  pArg3 = this + 1;
  do  // do-while 循环体起点
  {
    v13 = sub_432F40(*pArg3);  // 舍入取整（float → int）
    pArg33 = pArg3;
    *(&v23 + v12++) = v13;
    pArg3 = pArg33 + 1;
  }
  while ( v12 < 3 );  // 条件循环
  v22 = v28 + *(this + pArg2 + 1);
  v15 = sub_432F40(v22);  // 舍入取整（float → int）
  if ( *(&v23 + pArg2) == v15 )
  {
LABEL_25:  // 标签 LABEL_25（跳转合流点）
    v21 = v28 + *(this + pArg2 + 1);
    pArg3 = *((float **)this + pArg2 + 7);
    pArg34 = pArg3;
    *(this + pArg2 + 1) = v21;
    if ( pArg34 != nullptr )  // 若 pArg34 有效（非空）
    {
      result = 1;
      if ( (double)(int)pArg3 * *(this + pArg2 + 4) >= 0.0 )
        return 3;
    }
    else if ( *(this + pArg2 + 4) == 0.0 )
    {
      return 0;
    }
    else  // 否则分支
    {
      return 2;
    }
  }
  else  // 否则分支
  {
    while ( 1 )  // 条件循环
    {
      v26 = *(&v23 + pArg2);
      v16 = v26 >= v15 ? v26 - 1 : v26 + 1;
      v17 = *(int **)this;
      *(&v23 + pArg2) = v16;
      pArg3 = nullptr;  // pArg3 = 空指针
      v18 = *v17;
      v19 = pArg2 == 2
          ? (*(int (/*stdcall*/ **)(int))(v18 + 132))(v25)  // 调虚槽 +132：CNAuraChangeStatusMasterSpikeKing__vmt84 受击事件槽（钉…
          : (*(unsigned int (/*stdcall*/ **)(int, int, float **))(v18 + 136))(v23, v24, &pArg3);  // 调虚槽 +136：CNProvocationDollAura__vmt88 槽（10 行）
      if ( v19 == 0 )  // 若 v19 为 0
        break;  // 跳出循环/分支
      if ( *(&v23 + pArg2) == v15 )
        goto LABEL_25;
    }
    *(this + pArg2 + 1) = (float)v26;
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)this + 40))(*(uint32_t *)this, 1) != 0 )  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, float *))(**(uint32_t **)this + 532))(  // 调虚槽 +532：追踪冰浪攻击判定槽（前置参数装载）
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
void /*userpurge*/ sub_49FFC0(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3@<esi>, int nArg4, char pszArg5)  // 实现：播放尾帧处理（+48/+52/+40 → sub_49FA20 收尾）
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
  if ( pObj != 0  // 若 pObj 非 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0  // 调虚槽 +308：是否本地玩家
    && (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 80))(*pArg1) != 0  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    && *(uint32_t *)((*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 80))(*pArg1) + 132) != 0 )  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
  {
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 4, 1, nArg2, nArg3);  // 调虚槽 +8：CNRDItemShopWindow__vmt8 Update（166 行：CLICK_BU…
    v7 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 48))(*pArg1);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4D0…
    (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);  // 会话/UDP 管理器
    v9 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v10 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 52))(*pArg1);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15 行…
    (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);  // 会话/UDP 管理器
    v11 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 48))(dword_8F7C04);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
    (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);  // 会话/UDP 管理器
    v13 = *(uint32_t *)dword_8F8520;  // 会话/UDP 管理器
    v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);  // 调虚槽 +52：CNAuraShield__vmt34 播 AURA_SHIELD_LOOP（第二挂点，15…
    (*(void (/*thiscall*/ **)(int, int))(v13 + 36))(dword_8F8520, v14);  // 会话/UDP 管理器
    v15 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 80))(*pArg1);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
      dword_8F8520,  // 会话/UDP 管理器
      *(uint8_t *)(*(uint32_t *)(v15 + 132) + 112));
    v16 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pArg1 + 80))(*pArg1);  // 调虚槽 +80：CNRDPrivateStoreWindow__vmt50 槽（参数写入 3 转发）
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 32))(  // 调虚槽 +32：CNRDPVPRoomListWindow__vmt20 槽（41C590 + 46ED90…
      dword_8F8520,  // 会话/UDP 管理器
      *(uint8_t *)(*(uint32_t *)(v16 + 132) + 116));
    if ( (uint8_t)nArg4 != 0 )
    {
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, 16);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      v17 = pArg1 + 1;
      (*(void (/*thiscall*/ **)(int, uint32_t *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, pArg1 + 1, 49);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      if ( pszArg5 == 1 )  // 若 pszArg5 == 1
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      else  // 否则分支
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      v18 = (char *)pArg1 + 53;
    }
    else  // 否则分支
    {
      v18 = (char *)pArg1 + 53;
      v17 = pArg1 + 1;
      v19 = sub_49FA20((char *)pArg1 + 53, &unk_9A026C, &nArg4);  // 三字段组写（+40/+44/+48）
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, v19);  // 调虚槽 +40：条件位掩码测试(273受击/529濒死/17有血/65机械)
      (*(void (/*thiscall*/ **)(int, void *, int))(*(uint32_t *)dword_8F8520 + 48))(dword_8F8520, &unk_9A026C, nArg4);  // 调虚槽 +48：CNRDAuraMaster__vmt30 更新槽（64A5A0 + 41C5E0/52E4…
      if ( pszArg5 == 1 )  // 若 pszArg5 == 1
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
      else  // 否则分支
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 0);  // 调虚槽 +60：CNRDPrivateStoreWindow_Display__vmt3C 取消动作槽（79…
    }
    qmemcpy(v18, v17, 0x31u);  // 调 qmemcpy（内存块拷贝(内联展开)）
    pArg1[45] = sub_699000((int)(pArg1 + 36));  // 【clock_now(clk)】
    *((uint8_t *)pArg1 + 196) = 0;
  }
}


