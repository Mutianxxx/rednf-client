// ============================================================
// 【40JP逆向源代码工程】creature/expeller_guard.cpp
// 模块: 怪物AI 0x5D —— 驱逐者八型/四属性守卫/锤王/邪眼/白魔 WZ 主状态机
// 来源: work/dump_monster.txt  区块: 0x5D0000-0x5E0000
// 层级: L2 转写层 + L1 精修（函数体保持 Hex-Rays 忠实输出，仅升级注释与分区）
// 函数数: 251
// ------------------------------------------------------------
// ★ 本文件已按《20_打击感与HitStop系统研究》定案升级注释（研究 20 §x 为引）：
//   · vmt200(=vt+512 字节槽) 命中处理器覆写：本文件【无】—— 0x5D 段全部虚表在 +512 槽
//     继承基类 0x4D71B0（纯 Python 直读 PE 全域扫描证实）；守卫族行为差异 = 数据 + 技能函数
//   · ★ AI 大状态机总定案：0x5DE690（1082L, 本工程最大函数）= 白魔 WZ 大型主状态机 ——
//     switch(this+6556) 大状态 6/10/16/17/18/19/20/21 分派 + this+616 反应态 == -1 空闲门
//     （研究 15 三层状态架构的最完整客户端样本）；0x5D9BF0 亦读 this+612/616
//   · SUPERARMOR 霸体（0x5D47D0, 研究 20 §1.2 vt+720 霸体 setter 的调用侧）；
//     0x5D44D0/0x5D59B0 读 this+568 最后受击时刻
//   · 语音 TAG 组（R_DEFEN_GUARD_*/R_ICE_GUARD/R_HAMMER_KING/R_EXPELLER_*/EVIL_*/WZ_*）经
//     sub_4015C0 写语音槽，vt+212(sub_499110) 播报（研究 28）；sub_431230=vector 打包 setState
//   · 资源标注：sub_431860/431920=.ani 装载 / sub_4BA9E0=.equ 外观 / sub_699000=clock_now /
//     sub_47EF20=数据表读数 / sub_4049C0=帧间插值 / sub_406D60=BGM 曲名槽
//   · 驱逐者八型外观（0x5D7F80-0x5D88C0）：Expeller/AxeExpeller/HeavenExpeller/AxionExpeller/
//     TSMExpeller/LegionExpeller/SandorExpeller + Guard + HammerKing；四属性守卫特效族
//     ksguard_{light,wind,ice,protection,flame}.ani（0x5D6590-0x5D6AF0）
// ============================================================

#include "../../common/arad_types.h"

// ============================================================
// 【分区 1】守卫基础与蓄雷（0x5D0070-0x5D0DB0）
// 证据：this+8601/8603/8669 守卫字段区、BEFORE_THUNDER 蓄雷（0x5D0330 175L, 雷守卫）

// 子类扩展字段复位（this+8601/8603/8669 —— 守卫字段区）
// ------------------------------------------------------------
// 0x5D0070 sub_5D0070 —— 逐帧门控（攻击态收招 + 守卫站立二次判定）
// 姿态查询 vt+840 == 8（攻击态）时经 vt+1332 收招，随后转调 ·sub_5CF180 基类帧处理；
// 守卫激活位 this+8669==1、盾空闲 this+8603==0、站立位 this+8601==1 三条件齐备且
// 姿态回落 0 时，再走 vt+1344 二次判定并以其返回值收尾。【推断】守卫系专属待机收尾
// ------------------------------------------------------------
char /*thiscall*/ sub_5D0070(int this)
{
  int pThis_348; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
  sub_5CF180((uint32_t *)this);
  LOBYTE(pThis_348) = 1;
  if ( *(uint8_t *)(this + 8669) == 1 && *(uint8_t *)(this + 8603) == 0 && *(uint8_t *)(this + 8601) == 1 )
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( pThis_348 == 0 )
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
  }
  return pThis_348;
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5D00D0 sub_5D00D0 —— 守卫状态分派透传（激活门）
// this+8669==1（守卫激活）时把状态事件原样转发 ·sub_4E33D0 状态收尾族；
// 未激活直接返回（result 未赋值，Hex-Rays 忠实输出保留）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D00D0(uint8_t *this, char pszArg2, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  if ( *(this + 8669) == 1 )
    return sub_4E33D0(pszArg2, fArg3, nArg4, nArg5);
  return result;
}



// AI 字段访问（this+8601/8812/8816）
// ------------------------------------------------------------
// 0x5D00F0 sub_5D00F0 —— 守卫相位三槽清零（站立位 + 两计时空槽）
// this+8601 = 0、this+8812 = 0、this+8816 = 0 后返回 0（this+8816 为相位计时器）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D00F0(int this)
{
  *(uint8_t *)(this + 8601) = 0;
  *(uint32_t *)(this + 8816) = 0;
  *(uint32_t *)(this + 8812) = 0;
  return 0;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D0110 sub_5D0110 —— 碰撞对象过滤与目标投递（守卫交互判定）
// 先经 vt+40(obj, 17) 校验对方为玩家型（类型 id 17），再 __RTDynamicCast 将
// IRDCollisionObject 提升为 IRDActiveObject 并调 vt+700 取实体；
// 技能对象 this+2203 就绪（·sub_53F660==1）时清其 +13/+14 字节并挂 20000 单位时钟
// （·sub_698F90），否则走 vt+56 七参投递（this, pObj, this, 1, 0, 0, -1）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D0110(uint32_t *this, int nArg2)
{
  char result; // al
  int pObj; // edi
  int fld_e2203; // eax

  result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17);
  if ( result == 1 )
  {
    pObj = __RTDynamicCast(nArg2, 0, &IRDCollisionObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
    if ( (uint8_t)sub_53F660(*(this + 2203)) == 1 )
    {
      fld_e2203 = *(this + 2203) + 8;
      *(uint8_t *)(fld_e2203 + 13) = 0;
      *(uint8_t *)(fld_e2203 + 14) = 0;
      return sub_698F90(*(this + 2203) + 8, 20000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    else
    {
      return (*(int (/*thiscall*/ **)(uint32_t, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2203) + 56))(
               *(this + 2203),
               pObj,
               this,
               1,
               0,
               0,
               -1);
    }
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D01B0 sub_5D01B0 —— 架招反击挂钩（攻击态 + 段号 2）
// 攻击态（vt+840==8）且攻击段槽 this+7028 经 ·sub_41A5E0 读得段号 2 时，
// 先经 vt+1360 触发守卫专属反击动作，再统一转 ·sub_4DB480 反击/架招触发判定。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D01B0(void *this, int nArg2, int nArg3, int nArg4)
{
  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) == 8 && sub_41A5E0((unsigned int)this + 7028) == 2 )
    (*(void (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1360))(this, nArg2);
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0200 sub_5D0200 —— 双子对象析构释放（this+2203/2204 槽）
// 对 this+2204、this+2203 两个指针槽各自判空后经其虚表首槽（+0）以参数 1 调用
// （·0x5AF1C0 式释放约定），随后两槽置 0 返回最后结果。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0200(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2204)(uint32_t, int); // ecx
  int result; // eax
  int (/*thiscall*/ ***fld_e2203)(uint32_t, int); // ecx

  fld_e2204 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2204);
  if ( fld_e2204 != nullptr )
    result = (**fld_e2204)(fld_e2204, 1);
  fld_e2203 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2203);
  *(this + 2204) = 0;
  if ( fld_e2203 != nullptr )
    result = (**fld_e2203)(fld_e2203, 1);
  *(this + 2203) = 0;
  return result;
}



// 时钟门 AI（sub_699000; this+8600/8812..8837 守卫相位）
// ------------------------------------------------------------
// 0x5D0240 sub_5D0240 —— 相位场复位 + 计时器重挂（30 帧窗口）
// 先清 this+8600/8829/8832/8812 与 this+8824（计数器）、this+8837（标志），
// 再经 ·sub_699000(clock_now, this+36) 取当前时刻写入 this+8816 作起点，
// 并把窗口长度 this+8820 置 30 帧。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0240(int this)
{
  int result; // eax

  *(uint8_t *)(this + 8600) = 0;
  *(uint8_t *)(this + 8829) = 0;
  *(uint32_t *)(this + 8832) = 0;
  *(uint8_t *)(this + 8812) = 0;
  result = sub_699000(this + 36);  // 【clock_now(clk)】
  *(uint32_t *)(this + 8824) = 0;
  *(uint8_t *)(this + 8837) = 0;
  *(uint32_t *)(this + 8816) = result;
  *(uint32_t *)(this + 8820) = 30;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0290 sub_5D0290 —— 三武器槽扫描赋默认值（先转 ·sub_4D4CE0 基类）
// 转调 ·sub_4D4CE0(this, nArg2) 后从 this+1648 起以 uint32_t 步长扫描最多 3 槽，
// 遇值 17（玩家型 id）即停；对命中槽写三字段：+412/+436 槽 = 6、+436/+... = 8、
// +424 槽 = 1097859072（浮点 110.0 的位模式）。【推断】按武器序号索引的默认参数面
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0290(char *this, int nArg2)
{
  int result; // eax
  uint32_t *i; // ecx

  sub_4D4CE0(this, nArg2);
  result = 0;
  for ( i = this + 412; *i != 17; ++i )
  {
    if ( ++result >= 3 )
      return result;
  }
  *((uint32_t *)this + result + 103) = 6;
  *((uint32_t *)this + result + 109) = 8;
  *((uint32_t *)this + result + 106) = 1097859072;
  return result;
}



// AI 字段访问（this+8812/8824）
// ------------------------------------------------------------
// 0x5D02E0 sub_5D02E0 —— 攻击段计数器累加（段号为 1 的帧）
// 以 this+7028 段槽经 ·sub_41A5E0 读段号，把「当前段号 == 1」写入 this+8812，
// 该帧命中段槽时 this+8824 计数器自增 1，最后统一转 ·sub_4DB480 反击判定。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D02E0(int this, int nArg2, int nArg3, int nArg4)
{
  unsigned int pThis_1B74; // edi

  pThis_1B74 = this + 7028;
  *(uint8_t *)(this + 8812) = sub_41A5E0(this + 7028) == 1;
  if ( sub_41A5E0(pThis_1B74) == 1 )
    ++*(uint32_t *)(this + 8824);
  return sub_4DB480(nArg2, nArg3, nArg4);
}



// 蓄雷 AI：BEFORE_THUNDER 播报（175L；雷守卫蓄雷循环 —— 与 0x5A1BF0 基诺尔同族）
// ------------------------------------------------------------
// 0x5D0330 sub_5D0330 —— 蓄雷循环：BEFORE_THUNDER 播报 + 雷柱预判布点（175L）
// 【推断】雷守卫蓄雷相位机：按动画序号 pDwArg1[2208] 查表 v22=0..11 帧序、v20=0/150..1150 偏移、v21=10..120；
// 与 vt+200 帧号 +148 比对且 this+8829==0 时经 vt+212 播报 BEFORE_THUNDER（雷预警语音），
// 再取 vt+120/124（帧宽高）以 0.5 系数算落点 v8/v10，依目标 pDwArg1[1813] 的 vt+124 做上下侧判定 v24；
// 多次 vt+584（位置写入）以 30070 号攻击、段 10、flank（pDwArg1[1908] ? 100 : 130）在落点与 ±v21 偏移布雷柱，
// 收尾 this+8829=1 标记本帧已施放，待帧号推进至 v22[段号]+1 时复位并 ++段号，进入下一格。
// ------------------------------------------------------------
int /*usercall*/ sub_5D0330@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int result; // eax
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // edi
  int pObj; // ecx
  int v10; // ebx
  int v11; // ebx
  int v12; // eax
  bool v13; // zf
  bool v14; // sf
  bool v15; // of
  int v16; // eax
  int v17; // ecx
  int v18; // [esp-38h] [ebp-108h]
  int v19; // [esp+4h] [ebp-CCh]
  uint32_t v20[23]; // [esp+8h] [ebp-C8h]
  uint32_t v21[12]; // [esp+64h] [ebp-6Ch]
  uint32_t v22[12]; // [esp+94h] [ebp-3Ch]
  float v23; // [esp+C4h] [ebp-Ch]
  int v24; // [esp+C8h] [ebp-8h]
  int v25; // [esp+CCh] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1);
  if ( (uint8_t)result != 0 )
  {
    v5 = *pDwArg1;
    v22[10] = 10;
    v21[0] = 10;
    v22[0] = 0;
    v22[1] = 1;
    v22[2] = 2;
    v22[3] = 3;
    v22[4] = 4;
    v22[5] = 5;
    v22[6] = 6;
    v22[7] = 7;
    v22[8] = 8;
    v22[9] = 9;
    v22[11] = 11;
    v19 = 50;
    v20[0] = 0;
    v20[1] = 150;
    v20[2] = 0;
    v20[3] = 250;
    v20[4] = 0;
    v20[5] = 350;
    v20[6] = 0;
    v20[7] = 450;
    v20[8] = 0;
    v20[9] = 550;
    v20[10] = 0;
    v20[11] = 650;
    v20[12] = 0;
    v20[13] = 750;
    v20[14] = 0;
    v20[15] = 850;
    v20[16] = 0;
    v20[17] = 950;
    v20[18] = 0;
    v20[19] = 1050;
    v20[20] = 0;
    v20[21] = 1150;
    v20[22] = 0;
    v21[1] = 20;
    v21[2] = 30;
    v21[3] = 40;
    v21[4] = 50;
    v21[5] = 60;
    v21[6] = 70;
    v21[7] = 80;
    v21[8] = 90;
    v21[9] = 100;
    v21[10] = 110;
    v21[11] = 120;
    v25 = (*(int (/*thiscall*/ **)(int *))(v5 + 152))(pDwArg1) != 1 ? -1 : 1;
    if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1) + 148) == v22[pDwArg1[2208]]
      && *((uint8_t *)pDwArg1 + 8829) == 0 )
    {
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*pDwArg1 + 212))(pDwArg1, "BEFORE_THUNDER", -1, 0, 0);
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*pDwArg1 + 308))(pDwArg1) != 0 && pDwArg1[2208] > 0 )
      {
        v6 = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 120))(pDwArg1, nArg2, nArg3);
        v7 = pDwArg1[2208];
        v24 = v6;
        v8 = (uint64_t)((double)v6 + (double)v20[2 * v7 - 1] * 0.5 * (double)v25);
        v25 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
        pObj = pDwArg1[1813];
        v10 = (uint64_t)((double)v25 + (double)(int)v20[2 * pDwArg1[2208]] * 0.5);
        v25 = v10;
        v24 = 1;
        if ( pObj != 0 )
        {
          v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
          v12 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 124))(pDwArg1);
          v15 = __OFSUB__(v11, v12);
          v13 = v11 == v12;
          v14 = v11 - v12 < 0;
          v10 = v25;
          v24 = 2 * !(v14 ^ v15 | v13) - 1;
        }
        (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int))(*pDwArg1 + 584))(
          pDwArg1,
          v8,
          v10,
          0,
          v8,
          v10,
          30070,
          10,
          0,
          4,
          pDwArg1[1908] != 0 ? 100 : 130,
          1);
        v25 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 740))(pDwArg1);
        v16 = *pDwArg1;
        v23 = (double)v25 * 0.5;
        v25 = (*(int (/*thiscall*/ **)(int *))(v16 + 736))(pDwArg1);
        if ( (double)v25 < v23 )
        {
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*pDwArg1 + 584))(
            pDwArg1,
            v8,
            v24 * v21[pDwArg1[2208]] + v10,
            0,
            v8,
            v24 * v21[pDwArg1[2208]] + v10,
            30070,
            10,
            0,
            4,
            pDwArg1[1908] != 0 ? 100 : 130,
            1,
            0,
            0);
          if ( *((uint8_t *)pDwArg1 + 8836) == 1 )
          {
            v18 = v10 - v24 * v21[pDwArg1[2208]];
            (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*pDwArg1 + 584))(
              pDwArg1,
              v8,
              v18,
              0,
              v8,
              v18,
              30070,
              10,
              0,
              4,
              pDwArg1[1908] != 0 ? 100 : 130,
              1,
              0,
              0);
          }
        }
      }
      *((uint8_t *)pDwArg1 + 8829) = 1;
    }
    result = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
    v17 = pDwArg1[2208];
    if ( *(uint32_t *)(result + 148) == v22[v17] + 1 )
    {
      *((uint8_t *)pDwArg1 + 8829) = 0;
      pDwArg1[2208] = v17 + 1;
    }
  }
  return result;
}


// AI 字段访问（this+8603）
// ------------------------------------------------------------
// 0x5D06E0 sub_5D06E0 —— 架招反击挂钩（架招态 14 + 盾空闲）
// 姿态 14（蓄力架招）且击退/伤害参数 nArg4==0、盾位 this+8603==0 时，
// 先经 vt+1336 触发守卫专属架招反击，再统一转 ·sub_5CEFF0 伤害/事件分发。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D06E0(uint8_t *this, int nArg2, int nArg3, int nArg4)
{
  if ( (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 840))(this) == 14 && (uint8_t)nArg4 == 0 && *(this + 8603) == 0 )
    (*(void (/*thiscall*/ **)(uint8_t *, int, int, uint32_t))(*(uint32_t *)this + 1336))(this, nArg2, nArg3, 0);
  return sub_5CEFF0(this, nArg2, nArg3, nArg4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0730 sub_5D0730 —— 大状态进入副作用（22 号 → 进架招 14）
// 先经 ·sub_4DBA80 执行大状态进入的增益侧副作用；若事件号 nArg2==22，
// 追加经 vt+560 setState 切到状态 14（架招）四参清零调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0730(void *this, int nArg2)
{
  int result; // eax

  result = sub_4DBA80(nArg2);
  if ( nArg2 == 22 )
    return (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, 0, 0, 0);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0760 sub_5D0760 —— 大状态退出副作用（22 号 → 回状态 0）
// ·sub_4DBC20（0x4DBA80 的还原对偶）执行退出副作用后，若事件号 nArg2==22
// 追加 vt+560 setState 回退到状态 0 全零参数调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0760(void *this, int nArg2)
{
  int result; // eax

  result = sub_4DBC20(nArg2);
  if ( nArg2 == 22 )
    return (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D0790 sub_5D0790 —— 单槽析构释放（this+2213）
// 对 this+2213 指针槽判空后经虚表首槽以参数 1 调用（·0x5AF1C0 式释放约定），
// 随后置 0。同 ·sub_5D0200 是同一析构族的单槽变体（此处挂的是 TSM 破碎粒子对象）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0790(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2213)(uint32_t, int); // ecx
  int result; // eax

  fld_e2213 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2213);
  if ( fld_e2213 != nullptr )
    result = (**fld_e2213)(fld_e2213, 1);
  *(this + 2213) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D07B0 sub_5D07B0 —— 单槽析构释放（this+2207）
// 对 this+2207 指针槽判空后经虚表首槽以参数 1 调用（·0x5AF1C0 式释放约定）
// 并置 0；槽位语义与 this+2203/2204（·sub_5D0200）、this+2213（·sub_5D0790）同族。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07B0(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2207)(uint32_t, int); // ecx
  int result; // eax

  fld_e2207 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2207);
  if ( fld_e2207 != nullptr )
    result = (**fld_e2207)(fld_e2207, 1);
  *(this + 2207) = 0;
  return result;
}



// AI 相位字段（this+8600/8812..8820）
// ------------------------------------------------------------
// 0x5D07D0 sub_5D07D0 —— 相位四槽清零（计时起点 + 窗口长 + 站立位）
// this+8812 = 0、this+8816 = 0、this+8820 = 0（窗口长清零）、this+8600 = 0 后返回 0；
// 与 ·sub_5D0240（重挂 30 帧窗口）配对使用。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07D0(int this)
{
  *(uint8_t *)(this + 8812) = 0;
  *(uint32_t *)(this + 8816) = 0;
  *(uint8_t *)(this + 8820) = 0;
  *(uint8_t *)(this + 8600) = 0;
  return 0;
}



// AI 字段访问（this+8722）
// ------------------------------------------------------------
// 0x5D07F0 sub_5D07F0 —— 消亡/解除绑定处理（this+7260 主属 + this+8722 播报位）
// 若 uArg2 即自身主属体 this+7260 且 vt+316 判定有效，先经 vt+312(this, 0) 解绑；
// 再统一转 ·sub_4D9170 消亡通知；若 uArg2 == this（自身消亡）且 this+8722==1
// 则经 vt+216(this, 10) 播报 10 号表现/音效（与 ·sub_5D0950 播报族同槽）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D07F0(uint8_t *this, uint8_t *uArg2)
{
  int result; // eax

  if ( uArg2 == *((uint8_t **)this + 1815) && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 316))(this) != 0 )
    (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 312))(this, 0);
  result = sub_4D9170(uArg2);
  if ( uArg2 == this && *(this + 8722) == 1 )
    return (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 10);
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0850 sub_5D0850 —— CNRDParticleCreater 构造（破碎粒子对象，0xEC 字节）
// 装 CNRDParticleCreater 虚表；·sub_423A20 初始化内嵌 +1 子对象（+4 起）后，
// 清 +104..+152 十三个槽与 +156 字节，+160/+164/+168 三色置 100，+172=1、
// +180=0、+176 = off_6C2B88（默认资源/回调槽）、+184=0、+188=1、+190/+189=0、
// +192/+196/+200=0；再 ·sub_4902C0 动画状态复位（+204..232 清零、+216=1）、
// ·sub_490D40(nArg2, nArg3) 写入资源名与参数【推断】，返回 this。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D0850(uint32_t *this, int nArg2, int nArg3)
{
  *this = &CNRDParticleCreater::`vftable';
  sub_423A20(this + 1);
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *((uint8_t *)this + 156) = 0;
  *(this + 40) = 100;
  *(this + 41) = 100;
  *(this + 42) = 100;
  *((uint8_t *)this + 172) = 1;
  *((uint8_t *)this + 180) = 0;
  *(this + 44) = &off_6C2B88;
  *(this + 46) = 0;
  *((uint8_t *)this + 188) = 1;
  *((uint8_t *)this + 190) = 0;
  *((uint8_t *)this + 189) = 0;
  *(this + 50) = 0;
  *(this + 49) = 0;
  *(this + 48) = 0;
  sub_4902C0(this);
  sub_490D40(nArg2, nArg3);
  return this;
}



// AI 相位字段（this+8669/8722）
// ------------------------------------------------------------
// 0x5D0950 sub_5D0950 —— 行为字相位机 + 语音播报门（this+1787 / this+8722）
// 守卫激活（this+8669==1）下先 ·sub_4E0120 无参处理（参数缺失，Hex-Rays 输出保留）；
// 行为字 this+1787==5 时经 vt+212 播报字符串槽 this+2197（+2202 SSO 门，≥16 取堆指针）
// 的 10 号表现/音效并使 this+8722=1（抑制位，先重置已有 8722==1 状态）；
// 随后按 this+1787 分派：case 0 走 vt+1284；case 4/5 依目标 this+1813 有无
// 经 vt+1104 写行为字 13（无目标接手）或 5（有目标收招）；case 13/14/15 有目标则写 5。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0950(uint32_t *this)
{
  char *pThis_895; // eax
  uint32_t *pThis; // ecx

  if ( *((uint8_t *)this + 8669) == 1 )
  {
    sub_4E0120();
    if ( *(this + 1787) == 5 )
      goto LABEL_6;
    if ( *((uint8_t *)this + 8722) == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 10);
      *((uint8_t *)this + 8722) = 0;
    }
    if ( *(this + 1787) == 5 )
    {
LABEL_6:
      if ( *((uint8_t *)this + 8722) == 0 )
      {
        if ( *(this + 2202) < 0x10u )
          pThis_895 = (char *)(this + 2197);
        else
          pThis_895 = (char *)*(this + 2197);
        (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_895, 10, 0, 0);
        *((uint8_t *)this + 8722) = 1;
      }
    }
    switch ( *(this + 1787) )
    {
      case 0:
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1284))(this);
        break;
      case 4:
        pThis = this;
        if ( *(this + 1813) != 0 )
          goto LABEL_19;
        goto LABEL_14;
      case 5:
        if ( *(this + 1813) == 0 )
LABEL_14:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 13);
        break;
      case 0xD:
      case 0xE:
      case 0xF:
        if ( *(this + 1813) != 0 )
        {
          pThis = this;
LABEL_19:
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(pThis, 5);
        }
        break;
      default:
        return;
    }
  }
}



// 时钟门 AI（sub_699000）
// ------------------------------------------------------------
// 0x5D0A60 sub_5D0A60 —— 冷却门反击概率机（写行为字 22）
// this+2187 为上次触发时刻，this+2181 内嵌 clock 结构（·sub_699000 读、·sub_698F90 挂）。
// 冷却到时且存活、姿态 0（待机）、行为字 this+1787 != 22 时考察目标 this+1813：
// 先 vt+40(target, 17) 确认玩家型，判定目标处于硬直/受击段（vt+840 为 8 或 7，或 vt+40(target, 273) 且 vt+840==12）
// 记为 v9，且自身 vt+152 阵营与目标不同、距离 vt+8(this, target, 0) < 150 且 rand()%100 < this+2179 时写行为字 22。
// 收尾清 clock 结构 +13/+14 并挂 100 单位冷却（this+2179 为触发概率阈值字段）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D0A60(uint32_t *this)
{
  int fld_e2187; // ebx
  int pThis_885; // edi
  int pThis_8853; // eax
  int fld_e1813; // eax
  int fld_e18132; // edi
  int fld_e18133; // ebx
  BOOL v9; // [esp+Ch] [ebp-8h]
  uint32_t *pThis_8852; // [esp+10h] [ebp-4h]

  fld_e2187 = *(this + 2187);
  pThis_885 = (int)(this + 2181);
  pThis_8852 = this + 2181;
  pThis_8853 = sub_699000((int)(this + 2181));  // 【clock_now(clk)】
  if ( pThis_8853 >= fld_e2187 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
      && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 0
      && *(this + 1787) != 22 )
    {
      fld_e1813 = *(this + 1813);
      if ( fld_e1813 != 0 && (*(uint8_t (/*stdcall*/ **)(int))(*(uint32_t *)fld_e1813 + 40))(17) != 0 )
      {
        fld_e18132 = *(this + 1813);
        v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 8
          || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 7
          || (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e18132 + 40))(fld_e18132, 273) != 0
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e18132 + 840))(fld_e18132) == 12;
        fld_e18133 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 152))(*(this + 1813));
        if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != fld_e18133
          && v9
          && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, fld_e18132, 0) < 150
          && rand() % 100 < *(this + 2179) )
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 22);
        }
        pThis_885 = (int)pThis_8852;
      }
    }
    *(uint8_t *)(pThis_885 + 13) = 0;
    *(uint8_t *)(pThis_885 + 14) = 0;
    LOBYTE(pThis_8853) = sub_698F90(pThis_885, 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  return pThis_8853;
}



// 主状态门（this+200/8669）
// ------------------------------------------------------------
// 0x5D0BA0 sub_5D0BA0 —— 守卫相位主门（架招释放概率 10%）
// 守卫激活下：姿态 == 14（架招）且 vt+200 状态块 +170 标志 == 1 时经 vt+560 setState 全零收架招。
// 否则转 ·sub_5D0950 行为字相位机；攻击段槽 this+7148 == 22（架招段）、this+7252（当前目标/技能对象）非空
// 且姿态 == 14 时，以双方 vt+120（帧宽）与 vt+152（阵营）比较判定目标是否在可架招窗口：
// 不在窗口时 rand()%100 < 10 概率经 vt+1104 写行为字 4 并 vt+1340 触发后续，否则写行为字 5（收招）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0BA0(int this)
{
  int fld_1C54; // eax
  int v3; // edi
  int fld_1C542; // edi

  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )
    {
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
    else
    {
      sub_5D0950((uint32_t *)this);
      if ( *(uint32_t *)(this + 7148) == 22 )
      {
        if ( *(uint32_t *)(this + 7252) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )
        {
          fld_1C54 = *(uint32_t *)(this + 7252);
          if ( fld_1C54 != 0 )
          {
            v3 = (*(int (**)(void))(*(uint32_t *)fld_1C54 + 120))();
            if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= v3
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)
              && ((fld_1C542 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252)),
                   (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < fld_1C542)
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )
            {
              if ( rand() % 100 < 10 )
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);
            }
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);
        }
      }
    }
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D0CC0 sub_5D0CC0 —— 多段投射物扇形布点（nArg2 ≤ 5 段）
// 存活门 vt+308 通过且 pArg2 <= 5 时：从场景对象 (*this+116)->+132 链取 +44 子对象，
// 以其 +364/+368 指针差 >> 5 得元素数 v6，算出每段步进 v7 = 224*v6/(pArg2+1)，
// 帧距 v14 = 120*(·sub_424FF0()+3)/2；循环 pArg2 次：经 vt+672(this, 0) 读倍率乘
// this+2233（浮点系数槽）得坐标（HIDWORD 传参），vt+152 建投射物（掩码 0xFFFF），
// vt+376 定位，vit+592（= vt+592 槽）以 50068 号效果登记，v7 每轮自增 v12 实现扇形铺开。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0CC0(float *this, int pArg2)
{
  int result; // eax
  int pThis_1D; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // ebx
  uint64_t fld_e2233; // rax
  float v9; // edi
  int pThis_98; // eax
  int pThis_178; // eax
  int v12; // [esp+4h] [ebp-Ch]
  int fld_e22332; // [esp+8h] [ebp-8h]
  int v14; // [esp+Ch] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result != 0 && pArg2 <= 5 )
  {
    pThis_1D = *(uint32_t *)(*(uint32_t *)(*((uint32_t *)this + 29) + 132) + 44);
    v5 = *(uint32_t *)(pThis_1D + 364);
    if ( v5 != 0 )
      v6 = (*(uint32_t *)(pThis_1D + 368) - v5) >> 5;
    else
      v6 = 0;
    v7 = 224 * v6 / (pArg2 + 1);
    v12 = v7;
    result = 120 * (sub_424FF0() + 3) / 2;
    v14 = result;
    if ( pArg2 > 0 )
    {
      do
      {
        fld_e2233 = (uint64_t)((double)*(int *)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 672))(
                                                  this,
                                                  0)
                              * *(this + 2233));
        v9 = *this;
        fld_e22332 = fld_e2233;
        pThis_98 = (*(int (/*fastcall*/ **)(float *, uint32_t, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 152))(
                this,
                HIDWORD(fld_e2233),
                2,
                0,
                0,
                0xFFFF,
                0,
                0,
                0,
                0);
        pThis_178 = (*(int (/*thiscall*/ **)(float *, int, int, int, uint32_t, int))(*(uint32_t *)this + 376))(
                this,
                fld_e22332,
                v7,
                v14,
                0,
                pThis_98);
        (*(void (/*thiscall*/ **)(float *, int, int))(LODWORD(v9) + 592))(this, 50068, pThis_178);
        v7 += v12;
        result = --pArg2;
      }
      while ( pArg2 != 0 );
    }
  }
  return result;
}



// ============================================================
// 【分区 2】驱逐者碎片与防御守卫（0x5D0DB0-0x5D2470）
// 证据：Particle/{HeavenExpellerBrokenParts,ExpellerBrokenParts,TSMShattered,AxeExpeller-
//       BrokenParts}.ptl 破碎粒子四型、R_DEFEN_GUARD_LAUGH 防御守卫笑声、LIGHT_GUARD_SHINE
//       光守卫闪耀、FIRE_GUARD_LAUGH 火守卫笑声、CONDITION_HASTE/SLOW 状态播报

// AI 字段访问
// ------------------------------------------------------------
// 0x5D0DB0 sub_5D0DB0 —— 守卫相位主门包装 + 姿态回读
// 先转 ·sub_5D0BA0 相位主门，再经 vt+308 存活判定；存活返回时把 vt+840 姿态值
// 作为结果回读（供调用方直接取姿态）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0DB0(void *this)
{
  int result; // eax

  sub_5D0BA0((int)this);
  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
  if ( (uint8_t)result == 1 )
    return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this);
  return result;
}



// 天界驱逐者破碎：引用 Particle/HeavenExpellerBrokenParts.ptl（23L）
// ------------------------------------------------------------
// 0x5D0DE0 sub_5D0DE0 —— 天界驱逐者破碎：装载 HeavenExpellerBrokenParts.ptl
// 三槽 this+8704/8708/8712 置 -1（破碎段序号无效化），vt+1308 先行走清理，
// 再经 vt+1352 装载粒子字符串 Particle/HeavenExpellerBrokenParts.ptl
// （资源名 this+364 起 SSO，≥16 取堆指针）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D0DE0(uint32_t *this)
{
  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  if ( *(this + 96) < 0x10u )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
             this,
             this + 91,
             "Particle/HeavenExpellerBrokenParts.ptl");
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, const char *))(*this + 1352))(
             this,
             *(this + 91),
             "Particle/HeavenExpellerBrokenParts.ptl");
}



// 主状态门（this+200/8669）
// ------------------------------------------------------------
// 0x5D0E40 sub_5D0E40 —— 守卫相位主门（架招释放概率 20% + 收招后置门）
// 与 ·sub_5D0BA0 同构：姿态非 14 时转 ·sub_5D0950，攻击段槽 this+7148==22 且
// this+7252 非空、目标可架招窗口判定通过时 rand()%100 < 20（概率翻倍）写行为字 4
// 并 vt+1340 触发，否则写 5；差异在于收招门（姿态 14 且状态块 +170==1 时
// vt+560 setState 全零）在本函数中位于尾部无条件执行。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0E40(int this)
{
  int fld_1C54; // eax
  int v3; // edi
  int fld_1C542; // edi

  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 14 )
    {
      sub_5D0950((uint32_t *)this);
      if ( *(uint32_t *)(this + 7148) == 22 )
      {
        if ( *(uint32_t *)(this + 7252) != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )
        {
          fld_1C54 = *(uint32_t *)(this + 7252);
          if ( fld_1C54 != 0 )
          {
            v3 = (*(int (**)(void))(*(uint32_t *)fld_1C54 + 120))();
            if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= v3
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)
              && ((fld_1C542 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252)),
                   (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) < fld_1C542)
               || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )
            {
              if ( rand() % 100 < 20 )
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);
              }
            }
            else
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);
            }
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);
        }
      }
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14
      && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
  }
}



// 主状态门（this+200/8669）
// ------------------------------------------------------------
// 0x5D0F80 sub_5D0F80 —— 守卫相位主门（低频架招释放 1%）
// 与 ·sub_5D0E40 同构三件套：姿态非 14 转 ·sub_5D0950、段槽 this+7148==22 且
// 目标窗口判定、写 4 或 5；唯一差异为触发概率 rand()%100 < 1（1%，低频型）
// 与收招门同样置于尾部紧随前述分支。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D0F80(int this)
{
  int fld_1C54; // edi
  int fld_1C542; // edi
  int v4; // [esp+4h] [ebp-4h]

  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 14 )
    {
      sub_5D0950((uint32_t *)this);
      if ( *(uint32_t *)(this + 7148) == 22 )
      {
        if ( *(uint32_t *)(this + 7252) != 0 )
        {
          fld_1C54 = (*(int (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 7252) + 120))(*(uint32_t *)(this + 7252));
          if ( ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) >= fld_1C54
             || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0)
            && ((fld_1C542 = *(uint32_t *)(this + 7252),
                 (v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this)) < (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_1C542 + 120))(fld_1C542))
             || (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 1) )
          {
            if ( rand() % 100 < 1 )
            {
              (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 4);
              (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1340))(this);
            }
          }
          else
          {
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 5);
          }
        }
        else
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1104))(this, 13);
        }
      }
    }
    if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14
      && *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 170) == 1 )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
  }
}



// 破碎粒子：Particle/ExpellerBrokenParts.ptl + Particle/TSMShattered.ptl（TSM 型专用碎屑）
// ------------------------------------------------------------
// 0x5D10A0 sub_5D10A0 —— 驱逐者破碎 + TSM 碎屑双装载（TSM 型专用）
// 三槽 this+8704/8708/8712 置 -1 后经 vt+1352 装载 Particle/ExpellerBrokenParts.ptl；
// 再 operator new(0xEC) 构造 CNRDParticleCreater（·sub_5D0850）挂
// Particle/TSMShattered.ptl，结果写入 this+2213（与 ·sub_5D0790 释放槽对应）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D10A0(int *this)
{
  int *pThis_5B; // eax
  uint32_t *pMem; // eax
  uint32_t *result; // eax

  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  if ( (unsigned int)*(this + 96) < 0x10 )
    pThis_5B = this + 91;
  else
    pThis_5B = (int *)*(this + 91);
  (*(void (/*thiscall*/ **)(int *, int *, const char *))(*this + 1352))(this, pThis_5B, "Particle/ExpellerBrokenParts.ptl");
  pMem = operator new(0xECu);
  if ( pMem != nullptr )
  {
    if ( (unsigned int)*(this + 96) < 0x10 )
      result = sub_5D0850(pMem, (int)(this + 91), (int)"Particle/TSMShattered.ptl");
    else
      result = sub_5D0850(pMem, *(this + 91), (int)"Particle/TSMShattered.ptl");
  }
  else
  {
    result = nullptr;
  }
  *(this + 2213) = (int)result;
  return result;
}



// 斧驱逐者破碎：引用 Particle/AxeExpellerBrokenParts.ptl
// ------------------------------------------------------------
// 0x5D1160 sub_5D1160 —— 斧驱逐者破碎：装载 AxeExpellerBrokenParts.ptl
// 与 ·sub_5D0DE0 同构（三槽置 -1、vt+1308 清理、vt+1352 装载），仅资源名换为
// Particle/AxeExpellerBrokenParts.ptl。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D1160(uint32_t *this)
{
  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  if ( *(this + 96) < 0x10u )
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
             this,
             this + 91,
             "Particle/AxeExpellerBrokenParts.ptl");
  else
    return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, const char *))(*this + 1352))(
             this,
             *(this + 91),
             "Particle/AxeExpellerBrokenParts.ptl");
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5D11C0 sub_5D11C0 —— 帧处理包装（激活门）
// this+8669==1 时转 ·sub_5D0950 行为字相位机，否则空返回（守卫未激活跳过）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D11C0(uint32_t *this)
{
  if ( *((uint8_t *)this + 8669) == 1 )
    sub_5D0950(this);
}



// 防御守卫笑声：R_DEFEN_GUARD_LAUGH 播报（168L；嘲讽循环【推断】）
// ------------------------------------------------------------
// 0x5D11D0 sub_5D11D0 —— 防御守卫嘲讽：R_DEFEN_GUARD_LAUGH + CNChangeHp 伤害包（168L）
// this+2175==-1（相位空闲）且 this+2210 != 2 时，nArg2 经 vt+576 解出受击体 pObj 并须存活（vt+308==1）：
// 取 nArg2 的 vt+348 攻击方档位 v7，以 this+2210 相位与 v7+12 配对从效果号表 {42004,42003,42005,42006,48011} 选 v44；
// 经 vt+628 七参取落点盒（基准 ± rand()%60-30 散布），operator new(0x80) 构造 ·sub_4D6810（CNChangeHp 伤害包 500/1/1），
// vt+56 绑定 (v26, this, this, 0,0,0,-1)、·sub_605840 取体积，再 ·sub_4E4A50 请求效果 v44（pObj 三轴坐标）并 vt+212 播报 R_DEFEN_GUARD_LAUGH；
// 表未命中则退化播报文案槽 this+1692；尾部姿态 14 且 nArg4==0 经 vt+1336 收招，统一转 ·sub_5CEFF0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D11D0(uint32_t *this, int nArg2, float *pArg3, int nArg4)
{
  int nArg22; // ebx
  int pObj; // esi
  int v7; // eax
  int fld_e2210; // ecx
  int v9; // edx
  int v10; // eax
  float v11; // edx
  float v12; // eax
  float v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // ebx
  int nRand; // edx
  int v20; // eax
  int v21; // ebx
  int nRand2; // edx
  int v23; // eax
  int v24; // ebx
  uint8_t *pMem; // eax
  uint8_t *v26; // eax
  int v27; // edx
  int v28; // eax
  uint32_t *pThis_69C; // eax
  int v31; // [esp+10h] [ebp-60h]
  int v32; // [esp+14h] [ebp-5Ch]
  int v33; // [esp+18h] [ebp-58h]
  int v34; // [esp+20h] [ebp-50h]
  int v35; // [esp+24h] [ebp-4Ch]
  float v36; // [esp+34h] [ebp-3Ch] BYREF
  float v37; // [esp+38h] [ebp-38h]
  float v38; // [esp+3Ch] [ebp-34h]
  int v39; // [esp+40h] [ebp-30h]
  int v40; // [esp+44h] [ebp-2Ch]
  int v41; // [esp+48h] [ebp-28h]
  uint8_t v42[4]; // [esp+4Ch] [ebp-24h] BYREF
  void *Block; // [esp+50h] [ebp-20h]
  int v44; // [esp+54h] [ebp-1Ch]
  int v45; // [esp+58h] [ebp-18h]
  int v46; // [esp+5Ch] [ebp-14h] BYREF
  char v47; // [esp+63h] [ebp-Dh] BYREF
  int v48; // [esp+6Ch] [ebp-4h]

  nArg22 = nArg2;
  if ( nArg2 != 0 )
    pObj = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
  else
    pObj = 0;
  if ( *(this + 2175) == -1
    && *(this + 2210) != 2
    && pObj != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 1 )
  {
    v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
    if ( v7 != 0 )
    {
      fld_e2210 = *(this + 2210);
      LODWORD(v37) = 42004;
      LODWORD(v38) = 42003;
      v39 = 42005;
      v40 = 42006;
      v41 = 48011;
      if ( fld_e2210 == 0 && *(uint32_t *)(v7 + 12) == 0 )
      {
        v44 = 48011;
        goto LABEL_15;
      }
      if ( fld_e2210 == 1 && *(uint32_t *)(v7 + 12) == 1 )
      {
        v44 = *((uint32_t *)&v37 + *(uint32_t *)(v7 + 20));
        if ( v44 != 0 )
        {
LABEL_15:
          v9 = *this;
          v46 = 0;
          v10 = (*(int (/*thiscall*/ **)(uint32_t *, char *, uint8_t *, int, int, float *, uint32_t))(v9 + 628))(
                  this,
                  &v47,
                  v42,
                  100,
                  nArg2,
                  pArg3,
                  0);
          v11 = *pArg3;
          v45 = v10;
          v12 = pArg3[1];
          v36 = v11;
          v13 = pArg3[2];
          v37 = v12;
          v14 = *((uint32_t *)pArg3 + 3);
          v38 = v13;
          v15 = *((uint32_t *)pArg3 + 4);
          v39 = v14;
          v16 = *((uint32_t *)pArg3 + 5);
          v40 = v15;
          v17 = *(uint32_t *)pObj;
          v41 = v16;
          v18 = (*(int (/*thiscall*/ **)(int))(v17 + 120))(pObj);
          nRand = rand() % 60;
          v20 = *(uint32_t *)pObj;
          Block = (void *)(v18 + nRand - 30);
          v36 = (float)(int)Block;
          v21 = (*(int (/*thiscall*/ **)(int))(v20 + 124))(pObj);
          nRand2 = rand() % 60;
          v23 = *(uint32_t *)pObj;
          Block = (void *)(v21 + nRand2 - 30);
          v37 = (float)(int)Block;
          v24 = (*(int (/*thiscall*/ **)(int))(v23 + 128))(pObj);
          Block = (void *)(v24 + rand() % 60 - 30);
          v38 = (float)(int)Block;
          pMem = operator new(0x80u);
          Block = pMem;
          v48 = 0;
          if ( pMem != nullptr )
          {
            *(float *)&v33 = (float)v45;
            v26 = sub_4D6810(pMem, v33, 500, 1, 1);
          }
          else
          {
            v26 = nullptr;
          }
          v27 = *(uint32_t *)v26;
          v48 = -1;
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(v27 + 56))(
            v26,
            this,
            this,
            0,
            0,
            0,
            -1);
          v35 = sub_605840(&v46, pObj, &v36, 1);
          v34 = v46;
          v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
          v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
          v28 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
          sub_4E4A50(this, v44, v45, v28, v31, v32, 1, 0, v34, v35);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*this + 212))(
            this,
            "R_DEFEN_GUARD_LAUGH",
            -1,
            0,
            0);
          nArg22 = nArg2;
          goto LABEL_23;
        }
      }
    }
    if ( *(this + 1697) < 0x10u )
      pThis_69C = this + 1692;
    else
      pThis_69C = (uint32_t *)*(this + 1692);
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_69C, -1, 0, 0);
  }
LABEL_23:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 && (uint8_t)nArg4 == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, float *, uint32_t))(*this + 1336))(this, nArg22, pArg3, 0);
  return sub_5CEFF0(nArg22, pArg3, nArg4);
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5D1490 sub_5D1490 —— 五元组记录构造（20 字节堆分配）
// operator new(0x14) 后写 (nArg1, nArg2, pArg3[0..2]) 五个 32 位字段，返回首址；
// 供上层把「攻击方/受击方 + 三轴坐标」快照存入列表。【推断】坐标/帧快照结构
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_5D1490(int nArg1, int nArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax

  result = operator new(0x14u);
  if ( result != nullptr )
  {
    *result = nArg1;
    result[1] = nArg2;
    result[2] = *pArg3;
    result[3] = pArg3[1];
    result[4] = pArg3[2];
  }
  return result;
}



// 时钟门 AI（sub_699000, 101L）
// ------------------------------------------------------------
// 0x5D14D0 sub_5D14D0 —— 变身/变身解除三相位机（this+2175: -1→0→1→2）
// 相位 0：this+8668==1 且 this+2175==0 时经 vt+144 触发形态切换，对 vt+200 子链 ·sub_493400 应用帧 1、·sub_4939E0 播放级联，
// 再 ·sub_4E7F30(200,200,0) 判定非零则清 this+8685/8686 并挂 2000 单位时钟（this+8672）、this+2175=1。
// 相位 1：等 this+2174 时长到点（·sub_699000 读）置 2175=2，子链 ·sub_4926A0 帧游标复位并 ·sub_4939E0(子链, 0) 停播。
// 相位 2：vt+200 状态块 +170==1 时遍历 this+8624 起 8 槽经 vt+784（.equ 挂装）调 vt+4(obj, 1) 收尾，this+8669 置 1（正式激活）、
// this+2175=-1，vt+212 播报字符串槽 this+8760（+8780 SSO 门）；this+7801 非零且 this+8723==1 则 ·sub_4DB130(24, 0) 随机语音。
// ------------------------------------------------------------
char /*usercall*/ sub_5D14D0@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>)
{
  int v3; // eax
  int v4; // eax
  bool v5; // al
  int v6; // eax
  int v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // eax
  uint32_t *v11; // edi
  int i; // ebx
  int pObj; // eax
  int *v14; // eax
  uint32_t *v15; // edi
  int j; // ebx
  float v19; // [esp-4h] [ebp-Ch]

  if ( *((uint8_t *)pDwArg1 + 8668) == 1 && pDwArg1[2175] == 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 144))(pDwArg1);
    v3 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 200))(pDwArg1, 0);
    sub_493400(v3, 1);
    v4 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
    sub_4939E0(v4, 1);
    v5 = sub_4E7F30(pDwArg1, 200, 200, 0) == 0;
    *((uint8_t *)pDwArg1 + 8668) = v5;
    if ( !v5 )
    {
      *((uint8_t *)pDwArg1 + 8685) = 0;
      *((uint8_t *)pDwArg1 + 8686) = 0;
      sub_698F90((int)(pDwArg1 + 2168), 2000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      pDwArg1[2175] = 1;
    }
  }
  v6 = pDwArg1[2175];
  if ( v6 == 1 )
  {
    v7 = pDwArg1[2174];
    v6 = sub_699000((int)(pDwArg1 + 2168));  // 【clock_now(clk)】
    if ( v6 >= v7 )
    {
      v8 = *pDwArg1;
      pDwArg1[2175] = 2;
      v9 = (*(int (/*thiscall*/ **)(int *))(v8 + 200))(pDwArg1);
      sub_4926A0(v9);
      v10 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
      LOBYTE(v6) = sub_4939E0(v10, 0);
    }
  }
  else if ( v6 == 2 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 200))(pDwArg1);
    if ( *(uint8_t *)(v6 + 170) == 1 )
    {
      v11 = pDwArg1 + 2156;
      for ( i = 8; i != 0; --i )
      {
        if ( *v11 != 0 )
        {
          pObj = (*(int (/*thiscall*/ **)(int *, uint32_t))(*pDwArg1 + 784))(pDwArg1, *v11);
          if ( pObj != 0 )
            (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, 1);
        }
        ++v11;
      }
      pDwArg1[1639] = 0;
      *((uint8_t *)pDwArg1 + 8669) = 1;
      pDwArg1[2175] = -1;
      if ( (unsigned int)pDwArg1[2195] < 0x10 )
        v14 = pDwArg1 + 2190;
      else
        v14 = (int *)pDwArg1[2190];
      (*(void (/*thiscall*/ **)(int *, int *, int, uint32_t, uint32_t, int))(*pDwArg1 + 212))(pDwArg1, v14, -1, 0, 0, nArg2);
      if ( *((uint8_t *)pDwArg1 + 7801) != 0 && *((uint8_t *)pDwArg1 + 8723) == 1 )
        sub_4DB130(24, 0);
      if ( pDwArg1[2188] != 1065353216 )
      {
        v19 = *((float *)pDwArg1 + 2188);
        (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 688))(pDwArg1);
        sub_4EB2C0(v19);
        v15 = pDwArg1 + 2156;
        for ( j = 8; j != 0; --j )
        {
          if ( *v15 != 0 )
            sub_4EB6A0(*((float *)pDwArg1 + 2188));
          ++v15;
        }
        pDwArg1[40] = (uint64_t)((double)pDwArg1[40] * *((float *)pDwArg1 + 2188));
      }
      LOBYTE(v6) = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 820))(pDwArg1, 1);
    }
  }
  return v6;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D16D0 sub_5D16D0 —— 挂载点全表遍历销毁（装备/子件批量清理）
// 对 this+6160/6164/6168 三槽与 this+6172 起 2 槽、this+6200..6204、this+6216..6220
// 各区间逐个经 vt+1328(this, 槽值) 注销；再遍历 this+6468 起 18 个条目槽，
// 对每槽调 vt+248 取其容器 [+4, +8) 的元素链，按 31 个 uint32_t 步长逐条
// 展开 3 个主槽 + 2 槽 + [+44,+48)、[+60,+64) 两数组（共 17 值），
// 逐值经 vt+1328 注销（虚表槽与绑定/挂装表清理同族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D16D0(uint32_t *this)
{
  uint32_t *pThis_607; // edi
  int i; // ebx
  uint32_t *j; // edi
  uint32_t *k; // edi
  uint32_t *pThis_651; // ebx
  int v7; // eax
  uint32_t *v8; // edi
  uint32_t *v9; // ebx
  uint32_t *n; // ebx
  uint32_t *ii; // ebx
  bool v12; // zf
  int result; // eax
  int v14; // [esp+Ch] [ebp-10h]
  int v15; // [esp+10h] [ebp-Ch]
  uint32_t *pThis_6512; // [esp+14h] [ebp-8h]
  int m; // [esp+18h] [ebp-4h]

  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1540));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1541));
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *(this + 1542));
  pThis_607 = this + 1543;
  for ( i = 2; i != 0; --i )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *pThis_607++);
  for ( j = (uint32_t *)*(this + 1550); j != (uint32_t *)*(this + 1551); ++j )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *j);
  for ( k = (uint32_t *)*(this + 1554); k != (uint32_t *)*(this + 1555); ++k )
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *k);
  pThis_651 = this + 1617;
  pThis_6512 = this + 1617;
  v15 = 18;
  do
  {
    if ( *pThis_651 != 0 )
    {
      v7 = (*(int (**)(void))(*(uint32_t *)*pThis_651 + 248))();
      v8 = *(uint32_t **)(v7 + 4);
      v14 = v7;
      if ( v8 != *(uint32_t **)(v7 + 8) )
      {
        do
        {
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[1]);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[2]);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, v8[3]);
          v9 = v8 + 4;
          for ( m = 2; m != 0; --m )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *v9++);
          for ( n = (uint32_t *)v8[11]; n != (uint32_t *)v8[12]; ++n )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *n);
          for ( ii = (uint32_t *)v8[15]; ii != (uint32_t *)v8[16]; ++ii )
            (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 1328))(this, *ii);
          v8 += 31;
        }
        while ( v8 != *(uint32_t **)(v14 + 8) );
        pThis_651 = pThis_6512;
      }
    }
    ++pThis_651;
    result = v15 - 1;
    v12 = v15 == 1;
    pThis_6512 = pThis_651;
    --v15;
  }
  while ( !v12 );
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D1880 sub_5D1880 —— 时间轴批量前移 40（帧表烫平）
// pArg1 非空且 != -40 时，从 [+44, +48) 指针区间以 88 字节元素步长遍历，
// 每元素 +16 字段 += 40。【推断】时间轴/时间戳补偿（与 ·sub_5D16D0 同表族）
// ------------------------------------------------------------
int /*stdcall*/ sub_5D1880(int pArg1)
{
  int result; // eax
  int v2; // ecx

  result = pArg1;
  if ( pArg1 != 0 && pArg1 != -40 )
  {
    v2 = *(uint32_t *)(pArg1 + 44);
    if ( v2 != *(uint32_t *)(pArg1 + 48) )
    {
      do
      {
        *(uint32_t *)(v2 + 16) += 40;
        result = *(uint32_t *)(pArg1 + 48);
        v2 += 88;
      }
      while ( v2 != result );
    }
  }
  return result;
}



// 破碎粒子：引用 Particle/ExpellerBrokenParts.ptl（this+8600 相位）
// ------------------------------------------------------------
// 0x5D18E0 sub_5D18E0 —— 破碎初始化（粒子 + 双轴尺寸 + 变速因子）
// this+8600 相位位清零、this+7208 = 150（窗口长）、三破碎槽 -1 后经 vt+1352
// 装载 Particle/ExpellerBrokenParts.ptl（资源名 this+364 SSO 门）；
// operator new(0x84) 经 ·sub_5FE2C0(1120403456) 构造（float 110.0 参数）子对象，
// vt+56 七参绑定 (pObj, this, this, 0,0,0,-1)；本函数另写 this+8752 = 1066192077
// （float 1.1 变速因子）并给 this+8612 二轴尺寸槽写 900/1400。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D18E0(uint8_t *this)
{
  char *pThis_16C; // eax
  int pObj; // eax
  uint32_t *result; // eax

  *(this + 8600) = 0;
  *((uint32_t *)this + 1802) = 150;
  *((uint32_t *)this + 2176) = -1;
  *((uint32_t *)this + 2177) = -1;
  *((uint32_t *)this + 2178) = -1;
  if ( *((uint32_t *)this + 96) < 0x10u )
    pThis_16C = this + 364;
  else
    pThis_16C = *((char **)this + 91);
  (*(void (/*thiscall*/ **)(uint8_t *, char *, const char *))(*(uint32_t *)this + 1352))(
    this,
    pThis_16C,
    "Particle/ExpellerBrokenParts.ptl");
  if ( operator new(0x84u) != nullptr )
    pObj = sub_5FE2C0(1120403456);
  else
    pObj = 0;
  (*(void (/*thiscall*/ **)(int, uint8_t *, uint8_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)pObj + 56))(
    pObj,
    this,
    this,
    0,
    0,
    0,
    -1);
  result = *((uint32_t **)this + 2153);
  *((uint32_t *)this + 2188) = 1066192077;
  *result = 900;
  *(uint32_t *)(*((uint32_t *)this + 2153) + 4) = 1400;
  return result;
}



// AI 相位字段（this+8669）
// ------------------------------------------------------------
// 0x5D19C0 sub_5D19C0 —— 状态事件总透传（架招退出 + 反击效果 30022）
// 门条件：vt+736（某资源/高度值为 0）或姿态 != 14 或 ArgList == 0 时进入。
// 段一：ArgList == 14（架招退出）且 this+8669==1 时，对子链 **this+6216 ·sub_4926A0 帧游标复位、vt+196 应用帧、两次 vt+876（速率双轴）清零再置 1。
// 段二：反应态 this+1639 == 4（受击后置）且 ArgList == 0 时，若 vt+235 == 0 且 vt+77 == 1 且 this+2207 == 1，
// 取 vt+30/31/38 三值经 ·sub_4E4A50 请求 30022 号效果（架招反震表现）。尾：this+8669==1 时统一转 ·sub_4E33D0 状态收尾。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D19C0(int **this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int v7; // eax
  int v8; // [esp-18h] [ebp-20h]
  int v9; // [esp-10h] [ebp-18h]

  result = ((int (/*thiscall*/ *)(int **))(*this)[184])(this);
  if ( result <= 0 || (result = ((int (/*thiscall*/ *)(int **))(*this)[210])(this)) != 14 || ArgList == 0 )
  {
    if ( ArgList == 14 && *((uint8_t *)this + 8669) == 1 )
    {
      sub_4926A0(**(this + 1554));
      ((void (/*thiscall*/ *)(int **, uint32_t))(*this)[49])(this, **(this + 1554));
      ((void (/*thiscall*/ *)(int **, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
        this,
        0,
        0,
        0,
        0,
        0,
        0);
      result = ((int (/*thiscall*/ *)(int **, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this)[219])(
                 this,
                 1,
                 0,
                 0,
                 0,
                 0,
                 0);
    }
    if ( *(this + 1639) == (int *)4 && ArgList == 0 )
    {
      result = ((int (/*thiscall*/ *)(int **))(*this)[235])(this);
      if ( (uint8_t)result == 0 )
      {
        result = ((int (/*thiscall*/ *)(int **))(*this)[77])(this);
        if ( (uint8_t)result == 1 && *(this + 2207) == (int *)1 )
        {
          v9 = ((int (/*thiscall*/ *)(int **))(*this)[38])(this);
          v8 = ((int (/*thiscall*/ *)(int **))(*this)[31])(this);
          v7 = ((int (/*thiscall*/ *)(int **))(*this)[30])(this);
          result = sub_4E4A50(this, 30022, 0, v7, v8, 0, v9, 0, 0, 0);
        }
      }
    }
    if ( *((uint8_t *)this + 8669) == 1 )
      return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  }
  return result;
}



// 光守卫闪耀：LIGHT_GUARD_SHINE 播报（61L）
// ------------------------------------------------------------
// 0x5D1AD0 sub_5D1AD0 —— 光守卫闪耀：LIGHT_GUARD_SHINE + 光刃投射（61L）
// ArgList == 32 专用分支：this+8840 计数 < 3 时 ·sub_4DB130(24, 1) 随机语音，计数 +1 并同步写 this+8844。
// 其余事件先转 ·sub_5D19C0 总透传；若姿态 vt+840 == 8（攻击态）且 vt+908 == 2，经全局 dword_8F7C04 的 vt+212 播报 LIGHT_GUARD_SHINE，
// ·sub_4DB200(24, 2) 文案门、this+8848 清零、·sub_698F90(pArg1+8852, 0) 清计时，再 vt+888(this, 4, 4, 1000, 1000) 设攻击段窗口，
// vt+672(this, 3) 取参后以 this+8916 / ·sub_41A5E0(v8+872) * 1000 算时长写 this+8880，经 v10[48]/v10[51] 把 1 号参数与 this+6216 子槽 +20 以负值写回。
// 条件不满足时清 this+8865/8866、vt+208 写回子槽 +20、清全局 dword_8F8528+2492 槽、vt+820(this, 1)。
// ------------------------------------------------------------
int /*userpurge*/ sub_5D1AD0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int result; // eax
  int v8; // eax
  uint64_t v9; // rax
  int *v10; // ebx
  int v11; // edi
  int v12; // eax

  result = ArgList;
  if ( ArgList == 32 )
  {
    if ( *(int *)(pArg1 + 8840) < 3 )
    {
      sub_4DB130(24, 1);
      result = *(uint32_t *)(pArg1 + 8840) + 1;
      *(uint32_t *)(pArg1 + 8840) = result;
      *(uint32_t *)(pArg1 + 8844) = result;
    }
  }
  else
  {
    sub_5D19C0((int **)pArg1, ArgList, fArg4, nArg5, nArg6);
    if ( (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 840))(pArg1, nArg2) == 8
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 908))(pArg1) == 2 )
    {
      (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
        dword_8F7C04,
        "LIGHT_GUARD_SHINE",
        -1,
        0);
      sub_4DB200(24, 2);
      *(uint8_t *)(pArg1 + 8848) = 0;
      sub_698F90(pArg1 + 8852, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 888))(pArg1, 4, 4, 1000, 1000);
      v8 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 672))(pArg1, 3);
      v9 = (uint64_t)((double)*(int *)(pArg1 + 8916) / (double)sub_41A5E0(v8 + 872) * 1000.0);
      v10 = *(int **)pArg1;
      v11 = *(uint32_t *)(pArg1 + 6216);
      *(uint32_t *)(pArg1 + 8880) = v9;
      v12 = ((int (/*fastcall*/ *)(int, uint32_t, uint32_t, uint32_t))v10[48])(pArg1, HIDWORD(v9), 0, 0);
      ((void (/*thiscall*/ *)(int, int, uint32_t, uint32_t, int))v10[51])(pArg1, 1, *(uint32_t *)(v11 + 20), 0, -v12);
      return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 820))(pArg1, 0);
    }
    else
    {
      *(uint8_t *)(pArg1 + 8865) = 0;
      *(uint8_t *)(pArg1 + 8866) = 0;
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20));
      *((uint32_t *)dword_8F8528 + 623) = 0;
      return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 820))(pArg1, 1);
    }
  }
  return result;
}



// 时钟门 AI（sub_699000; this+200/208）
// ------------------------------------------------------------
// 0x5D1C50 sub_5D1C50 —— 透明度正弦淡出（sin 曲线，250 上限，0.5 秒窗口）
// 先转 ·sub_5CF520 基类帧处理；nArg2（入帧标志）非零时经 this+8852 内嵌 clock（·sub_699000）取时刻，
// 姿态 8（攻击）且 vt+908 == 2 且时刻非零且 vt+200 子链非零时与起点 this+8880 比较：未到点用 250*t/span 线性渐入，
// 已过点则 v10 = t - 起点，>= 0x1F4（500）置 0，否则 250*(1 - sin(v10*0.003141592)) 正弦淡出；
// 非零值时以高 8 位为 alpha 合成 (v9 << 24) | 0xFFFFFF 交 ·sub_491DE0（全局 dword_79C0B0）混合渲染，源子槽取 this+6216 的 +20 经 vt+208 写回。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D1C50(int *this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  uint64_t v6; // rax
  unsigned int pThis_8A5; // edi
  int fld_e2220; // eax
  uint8_t v9; // bl
  unsigned int v10; // edi
  int dword_79C0B02; // [esp-24h] [ebp-30h]

  LODWORD(v6) = sub_5CF520(this, nArg2, nArg3, nArg4, fArg5);
  if ( (uint8_t)nArg2 != 0 )
  {
    pThis_8A5 = sub_699000((int)(this + 2213));  // 【clock_now(clk)】
    LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 840))(this);
    if ( (uint32_t)v6 == 8 )
    {
      LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 908))(this);
      if ( (uint32_t)v6 == 2 && pThis_8A5 != 0 )
      {
        LODWORD(v6) = (*(int (/*thiscall*/ **)(int *))(*this + 200))(this);
        if ( (uint32_t)v6 != 0 )
        {
          fld_e2220 = *(this + 2220);
          if ( pThis_8A5 >= fld_e2220 )
          {
            v10 = pThis_8A5 - fld_e2220;
            if ( v10 >= 0x1F4 )
              v9 = 0;
            else
              v9 = (uint64_t)((1.0 - sin((double)v10 * 0.003141592)) * 250.0);
            LODWORD(v6) = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 20));
          }
          else
          {
            v6 = (uint64_t)((double)pThis_8A5 * 250.0 / (double)fld_e2220);
            v9 = v6;
          }
          if ( v9 != 0 )
          {
            dword_79C0B02 = dword_79C0B0;
            (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);
            LODWORD(v6) = sub_491DE0(dword_79C0B02, nArg3, nArg4, fArg5, 2, 1, -1, (v9 << 24) | 0xFFFFFF);
          }
        }
      }
    }
  }
  return v6;
}



// 守卫相位字段（this+8857/8858/8972/8976/9012）
// ------------------------------------------------------------
// 0x5D1D90 sub_5D1D90 —— 事件 26/27/28 专用 + 总透传
// ArgList == 26 写 this+8972/8976 = 1、== 27 写 = 2 后转 ·sub_5CF880（子类帧处理）；
// ArgList == 28 时 vt+944(this, 1, 100000) 开启长时窗口、清 this+8857/8858，
// 再挂 this+8844 时钟（时长取 this+9012）与清 this+8944 时钟；
// 其余事件转 ·sub_5D19C0 总透传。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D1D90(int this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int v7; // eax

  if ( ArgList == 26 )
  {
    v7 = 1;
    goto LABEL_7;
  }
  if ( ArgList == 27 )
  {
    v7 = 2;
LABEL_7:
    *(uint32_t *)(this + 8972) = v7;
    *(uint32_t *)(this + 8976) = v7;
    return sub_5CF880((int *)this);
  }
  if ( ArgList != 28 )
    return sub_5D19C0((int **)this, ArgList, fArg3, nArg4, nArg5);
  (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 944))(this, 1, 100000);
  *(uint8_t *)(this + 8857) = 0;
  *(uint8_t *)(this + 8858) = 0;
  sub_698F90(this + 8844, *(uint32_t *)(this + 9012), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  return sub_698F90(this + 8944, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// 时钟门 AI（sub_699000; this+200）
// ------------------------------------------------------------
// 0x5D1E30 sub_5D1E30 —— 光效链淡出驱动（子对象 ring 遍历，此帧比率映射）
// 先转 ·sub_5CF520；vt+200 子链非零时读 this+8972 相位值 fld_e2243：
// nArg2==1（入帧）：fld_e2243 != 0 且 vt+940 == 0 时 ·sub_4938F0(this+8980) 播放驱动，以 vt+128（高度槽）叠加 nArg4 后 ·sub_491D00 提交渲染（fArg5 非零偏 +3，否则 -3）。
// 非入帧且 fld_e2243 == 2：缓存 this+9016 起减值，vt+940 != 1 或时刻差（·sub_699000(this+36) 减 this+7108）<= 1000 用 ·sub_423A80(255,0,dt,1000) 得渐隐系数 v17；
// 随后从 this+8908 指向的子表首元素起环形遍历链表，对每元素以 v11[2]/v11[3]/v11[4] 三坐标为参、v11[5] 为高 8 位 alpha 合成 (fld_e225422 << 24) | 0xFFFFFF 交 ·sub_491DE0 混合渲染。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D1E30(int *this, int nArg2, int nArg3, int nArg4, float fArg5)
{
  int fld_e2243; // eax
  int v8; // eax
  int fld_e1777; // eax
  uint32_t *fld_e2227; // eax
  uint32_t *v11; // edi
  uint64_t fld_e22542; // rax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  uint8_t fld_e225422; // [esp+1Bh] [ebp+Bh]
  float v17; // [esp+1Ch] [ebp+Ch]
  int v18; // [esp+20h] [ebp+10h]
  int fld_e2254; // [esp+24h] [ebp+14h]

  sub_5CF520(this, nArg2, nArg3, nArg4, fArg5);
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != 0 )
  {
    fld_e2243 = *(this + 2243);
    if ( (uint8_t)nArg2 == 1 )
    {
      if ( fld_e2243 != 0 && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 )
      {
        sub_4938F0(*(this + 2245));
        v8 = nArg4 + (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        sub_491D00(dword_79C0B0, nArg3 + (LOBYTE(fArg5) != 0 ? 3 : -3), v8, fArg5);
      }
    }
    else if ( fld_e2243 == 2 )
    {
      fld_e2254 = *(this + 2254);
      v17 = 1.0;
      (*(void (/*thiscall*/ **)(int *))(*this + 200))(this);
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) != 1
        || (fld_e1777 = sub_699000((int)(this + 9)) - *(this + 1777)) <= 1000  // 【clock_now(clk)】
        && (v17 = (double)(int)sub_423A80(255, 0, fld_e1777, 1000) * 0.0039215689) != 0.0 )
      {
        fld_e2227 = (uint32_t *)*(this + 2227);
        v11 = (uint32_t *)*fld_e2227;
        if ( (uint32_t *)*fld_e2227 != fld_e2227 )
        {
          do
          {
            fld_e22542 = (uint64_t)((double)fld_e2254 * 150.0 / (double)*(this + 2254) * v17);
            fld_e225422 = fld_e22542;
            --fld_e2254;
            if ( (uint8_t)fld_e22542 == 0 )
              break;
            v13 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);
            v18 = sub_45E490(v11[2], *(uint32_t *)(v13 + 8));
            v14 = (*(int (/*thiscall*/ **)(int *))(*this + 36))(this);
            v15 = sub_45E4D0(v11[3], v11[4], *(uint32_t *)(v14 + 8), 1.0);
            sub_491DE0(dword_79C0B0, v18, v15, fArg5, 0, 0, 0, (fld_e225422 << 24) | 0xFFFFFF);
            v11 = (uint32_t *)*v11;
          }
          while ( v11 != (uint32_t *)*(this + 2227) );
        }
      }
    }
  }
}



// 状态播报：CONDITION_HASTE + CONDITION_SLOW + FIRE_GUARD_LAUGH 火守卫笑声（67L）
// ------------------------------------------------------------
// 0x5D2020 sub_5D2020 —— 状态播报分派（HASTE/SLOW 增速减速 + FIRE_GUARD_LAUGH）
// switch (ArgList)：case 21/23 为增减速计数器维护 —— 21 时 this+8840 计数 +1 限 2、·sub_4DB200(24, 1) 门并播报 CONDITION_HASTE（增速）；
// 23 时计数 -1（下限 0，用 ((v<=1)-1) 掩码实现）并播报 CONDITION_SLOW（减速）；计数实际变化时写回 this+8840 并 ·sub_5CFD80(this, 是否增速) 应用变速。
// case 21/22/23 共同走 LABEL_9：·sub_41A590(this+8841, nArg2, 0) 计时器重挂并把 ·sub_699000(this+36) 时刻写入 this+8868（this+2217 槽）。
// case 31：·sub_4DB130(24, 2) 随机语音 + vt+212 播报 FIRE_GUARD_LAUGH（火守卫笑声）。default：转 ·sub_5D19C0 总透传。
// ------------------------------------------------------------
int /*fastcall*/ sub_5D2020(uint8_t *pArg1, int nArg2, int ArgList, float fArg4, int nArg5, int nArg6)
{
  char v7; // bl
  void *v8; // ecx
  int result; // eax

  switch ( ArgList )
  {
    case 21:
    case 23:
      if ( ArgList == 21 )
      {
        v7 = pArg1[8840] + 1;
        if ( (unsigned int)(uint8_t)pArg1[8840] + 1 >= 2 )
          v7 = 2;
        sub_4DB200(24, 1);
        (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "CONDITION_HASTE",
          -1,
          0,
          0);
      }
      else
      {
        v7 = (pArg1[8840] - 1) & (((uint8_t)pArg1[8840] <= 1u) - 1);
        (*(void (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
          pArg1,
          "CONDITION_SLOW",
          -1,
          0,
          0);
      }
      if ( v7 != pArg1[8840] )
      {
        LOBYTE(v8) = ArgList == 21;
        pArg1[8840] = v7;
        sub_5CFD80(pArg1, v8);
      }
      goto LABEL_9;
    case 22:
LABEL_9:
      sub_41A590((unsigned int)(pArg1 + 8841), nArg2, 0);
      result = sub_699000((int)(pArg1 + 36));  // 【clock_now(clk)】
      *((uint32_t *)pArg1 + 2217) = result;
      break;
    case 31:
      sub_4DB130(24, 2);
      result = (*(int (/*thiscall*/ **)(uint8_t *, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
                 pArg1,
                 "FIRE_GUARD_LAUGH",
                 -1,
                 0,
                 0);
      break;
    default:
      result = sub_5D19C0((int **)pArg1, ArgList, fArg4, nArg5, nArg5);
      break;
  }
  return result;
}



// 守卫相位字段（this+8669/8828/8829/8836）
// ------------------------------------------------------------
// 0x5D2140 sub_5D2140 —— 事件 14 架招退出 + 事件 8 攻击起始随机化
// 门：vt+736 <= 0 或姿态 != 14 或 ArgList == 0 或 ArgList == 9 时进入。
// ArgList == 14 且 this+8669==1：子链 **this+6216 经 ·sub_4926A0 帧游标复位、vt+196 应用帧、两次 vt+876 速率双轴清零再置 1（与 ·sub_5D19C0 段一同构）。
// ArgList == 8：清 this+8828，this+8836 = rand()%100 < 30（30% 副手随机门），再按段槽 this+7028 经 ·sub_41A5E0 读段号：段 1 清 this+8824（计数），段 3 清 this+8829 与 this+8832；
// 段 0（未进入）时 rand()%100 < 10 置 this+8828 = 1。尾：this+8669==1 时统一转 ·sub_4E33D0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2140(void *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax
  int nRand; // eax
  int v8; // et2

  if ( (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this) <= 0
    || (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this) != 14
    || (result = ArgList, ArgList == 0)
    || ArgList == 9 )
  {
    result = ArgList;
    if ( ArgList == 14 )
    {
      if ( *((uint8_t *)this + 8669) != 1 )
        return result;
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
      result = (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
                 this,
                 1,
                 0,
                 0,
                 0,
                 0,
                 0);
    }
    else if ( ArgList == 8 )
    {
      *((uint8_t *)this + 8828) = 0;
      *((uint8_t *)this + 8836) = rand() % 100 < 30;
      if ( sub_41A5E0((unsigned int)this + 7028) != 0 )
      {
        result = sub_41A5E0((unsigned int)this + 7028);
        if ( result == 1 )
        {
          *((uint32_t *)this + 2206) = 0;
        }
        else
        {
          result = sub_41A5E0((unsigned int)this + 7028);
          if ( result == 3 )
          {
            *((uint8_t *)this + 8829) = 0;
            *((uint32_t *)this + 2208) = 0;
          }
        }
      }
      else
      {
        nRand = rand();
        v8 = nRand % 100;
        result = nRand / 100;
        if ( v8 < 10 )
          *((uint8_t *)this + 8828) = 1;
      }
    }
    if ( *((uint8_t *)this + 8669) == 1 )
      return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  }
  return result;
}



// AI 字段访问（this+8669）
// ------------------------------------------------------------
// 0x5D2270 sub_5D2270 —— 与 ·sub_5D2140 同构（差异：无事件 8 分支）
// 门条件同为 vt+736 <= 0 / 姿态 != 14 / ArgList 0 或 9；ArgList == 14 时
// 同走 ·sub_4926A0 帧游标复位 + vt+196 应用帧 + 两次 vt+876 速率双轴处理；
// 尾部统一转 ·sub_4E33D0 状态收尾（去掉攻击段随机化段，无 this+8828/8832 写入）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2270(void *this, int ArgList, float fArg3, int nArg4, int nArg5)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 736))(this);
  if ( result <= 0
    || (result = (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 840))(this)) != 14
    || ArgList == 0
    || ArgList == 9 )
  {
    if ( ArgList == 14 )
    {
      if ( *((uint8_t *)this + 8669) != 1 )
        return result;
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
      result = (*(int (/*thiscall*/ **)(void *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
                 this,
                 1,
                 0,
                 0,
                 0,
                 0,
                 0);
    }
    if ( *((uint8_t *)this + 8669) == 1 )
      return sub_4E33D0(ArgList, fArg3, nArg4, nArg5);
  }
  return result;
}



// 斧驱逐者破碎 2：Particle/AxeExpellerBrokenParts.ptl
// ------------------------------------------------------------
// 0x5D2320 sub_5D2320 —— 斧驱逐者破碎 2：装载 + 应用目标帧
// 三槽 this+8704/8708/8712 置 -1、vt+1308 清理后经 vt+1352 装载
// Particle/AxeExpellerBrokenParts.ptl（资源名 this+364 SSO 门）；
// 与 ·sub_5D1160 差异：末尾不挂资源而走 vt+196(this, *(this+6216)+16)
// 对子链应用目标帧（把破碎动画接到当前帧位置）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2320(uint32_t *this)
{
  uint32_t *pThis_5B; // eax

  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  if ( *(this + 96) < 0x10u )
    pThis_5B = this + 91;
  else
    pThis_5B = (uint32_t *)*(this + 91);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
    this,
    pThis_5B,
    "Particle/AxeExpellerBrokenParts.ptl");
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 16));
}



// 插值 AI（sub_4049C0）
// ------------------------------------------------------------
// 0x5D2380 sub_5D2380 —— 破碎尺寸插值（0..30 帧间 ·sub_4049C0 线性插值）
// 取 vt+1172（插值 t）与 vt+384 双参（无参 + 9 号参数 = 起止），经 ·sub_4049C0
// 插值后 /100 得缩放 v8（0.01 量化）；vt+688 先置 1.0 复位、·sub_4EB4B0(10.0)
// 再置回、·sub_4EB2C0(v8) 提交主速率，最后遍历 this+8624 起 6 个子槽
// （·sub_4EB6E0(1.0) + ·sub_4EB6A0(v8)）逐子对象同步破碎缩放。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2380(uint32_t *this)
{
  int v2; // edi
  int result; // eax
  uint32_t *pThis_86C; // esi
  int i; // ebx
  float v6; // [esp+4h] [ebp-28h]
  float v7; // [esp+8h] [ebp-24h]
  float v8; // [esp+24h] [ebp-8h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1172))(this);
  v7 = (float)(*(int (/*thiscall*/ **)(uint32_t *))(*this + 384))(this);
  v6 = (float)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);
  v8 = (double)(int)(uint64_t)sub_4049C0(v6, v7, v2, 30) * 0.0099999998;  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 688))(this, 1065353216);
  sub_4EB4B0(COERCE_FLOAT(10));
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 688))(this);
  result = sub_4EB2C0(v8);
  pThis_86C = this + 2156;
  for ( i = 6; i != 0; --i )
  {
    if ( *pThis_86C != 0 )
    {
      sub_4EB6E0(1.0);
      result = sub_4EB6A0(v8);
    }
    ++pThis_86C;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D2440 sub_5D2440 —— 相位记录环摘除（this+2226 槽）
// 把 this+4 指向的首节点从双向环解链后 free，并递减 this+8 记录计数，返回剩余计数。
// 调用侧 ·0x5D48D0：22 秒级计时（2289 槽）到点复位记录环。【推断】相位记录出队辅助。
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_5D2440(uint32_t *this)
{
  int fld_e1; // ecx
  uint32_t **result; // eax

  fld_e1 = *(this + 1);
  result = *(uint32_t ***)(fld_e1 + 4);
  if ( result != (uint32_t **)fld_e1 )
  {
    *result[1] = *result;
    (*result)[1] = result[1];
    j__free(result);
    result = (uint32_t **)(*(this + 2) - 1);
    *(this + 2) = result;
  }
  return result;
}



// ============================================================
// 【分区 3】锤王三连与四属性守卫语音（0x5D2470-0x5D3400）
// 证据：HAMMER_KING_01/02/03 三连段、R_ICE_GUARD 冰守卫语音、LEGION_SHOUT 军团呐喊、
//       this+8840/8853..8872 守卫相位字段

// RTTI cast 目标解算（this+8601/8603/8669, 76L）
// ------------------------------------------------------------
// 0x5D2470 sub_5D2470 —— 受击挂件清理 + 守卫帧收尾（本区多个 AI 的公共尾段）
// vt+776 查询类型 2/11 挂件，存在则 vt+772 取件、vt+4 解链；随后遍历 vt+700 挂件表，
// RTTI 定到 CNChangeHp 且 +80 血量 < 0 者交 ·sub_53FE50 结算（命中分发族）。
// 尾段与 ·0x5D0070 同构：攻击态 vt+1332 收招 → ·sub_5CF180 基类帧处理 →
// 8669/8603/8601 三条件齐备且姿态回落 0 时 vt+1344 二次判定收尾。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D2470(int this)
{
  int pThis_304; // eax
  int pThis_3042; // eax
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
  int v14; // eax
  int pThis_348; // eax
  int v17; // [esp-8h] [ebp-Ch]

  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 2) != 0 )
  {
    pThis_304 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 772))(this, 2);
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pThis_304 + 4))(pThis_304, 0, this);
  }
  if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 11) != 0 )
  {
    pThis_3042 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 772))(this, 11);
    (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pThis_3042 + 4))(pThis_3042, 0, this);
  }
  for ( i = 0; ; ++i )
  {
    pThis_2BC = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
    v6 = *(uint32_t *)(pThis_2BC + 4);
    v7 = v6 != 0 ? (*(uint32_t *)(pThis_2BC + 8) - v6) >> 2 : 0;
    if ( (int)i >= v7 )
      break;
    pThis_2BC2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
    v9 = *(uint32_t *)(pThis_2BC2 + 4);
    if ( v9 != 0 && i < (*(uint32_t *)(pThis_2BC2 + 8) - v9) >> 2 )
      v10 = *(uint32_t *)(v9 + 4 * i);
    else
      v10 = 0;
    if ( *(uint32_t *)(v10 + 4) == this )
    {
      pThis_2BC3 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
      v12 = *(uint32_t *)(pThis_2BC3 + 4);
      if ( v12 != 0 && i < (*(uint32_t *)(pThis_2BC3 + 8) - v12) >> 2 )
        v13 = *(uint32_t *)(v12 + 4 * i);
      else
        v13 = 0;
      v14 = __RTDynamicCast(v13, 0, &IRDAppendage `RTTI Type Descriptor', &CNChangeHp `RTTI Type Descriptor', 0);
      if ( v14 != 0 && *(float *)(v14 + 80) < 0.0 )
      {
        v17 = v14;
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 700))(this);
        sub_53FE50(v17);
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
  sub_5CF180((uint32_t *)this);
  LOBYTE(pThis_348) = 1;
  if ( *(uint8_t *)(this + 8669) == 1 && *(uint8_t *)(this + 8603) == 0 && *(uint8_t *)(this + 8601) == 1 )
  {
    pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
    if ( pThis_348 == 0 )
      LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
  }
  return pThis_348;
}



// AI 字段访问（this+8723）
// ------------------------------------------------------------
// 0x5D25D0 sub_5D25D0 —— 自动守卫参数装载（vt+384 出场参数面 0..10 号）
// vt+1308 复位后按索引 0..10 读 vt+384，写入 8968..9008 参数面（8968/8988 两处 ×0.01 缩放）。
// 8612 双元槽写 1000/1600，清 8723 与 +1905 对象 +96 位，8840 时钟按 1000ms 起计时。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D25D0(float *this)
{
  double pThis_180; // st7
  int v3; // eax
  double v4; // st7
  int v5; // eax
  float v6; // edx
  int pThis_1802; // eax
  float v8; // edx
  int pThis_1803; // eax
  float v10; // edx
  int pThis_1804; // eax
  float v12; // edx
  int pThis_1805; // eax
  float v14; // edx
  uint8_t *pThis_771; // eax

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);
  pThis_180 = (double)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v3 = *(uint32_t *)this;
  v4 = pThis_180 * 0.0099999998;
  *(this + 2242) = v4;
  *(this + 2188) = v4;
  v5 = (*(int (/*thiscall*/ **)(float *, int))(v3 + 384))(this, 1);
  v6 = *this;
  *((uint32_t *)this + 2243) = v5;
  *((uint32_t *)this + 2244) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v6) + 384))(this, 2);
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v8 = *this;
  *((uint32_t *)this + 2245) = pThis_1802;
  *((uint32_t *)this + 2246) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v8) + 384))(this, 4);
  pThis_1803 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);
  v10 = *this;
  *(this + 2247) = (double)pThis_1803 * 0.0099999998;
  *((uint32_t *)this + 2248) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v10) + 384))(this, 6);
  pThis_1804 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);
  v12 = *this;
  *((uint32_t *)this + 2249) = pThis_1804;
  *((uint32_t *)this + 2250) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v12) + 384))(this, 8);
  pThis_1805 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 9);
  v14 = *this;
  *((uint32_t *)this + 2251) = pThis_1805;
  *((uint32_t *)this + 2252) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v14) + 384))(this, 10);
  **((uint32_t **)this + 2153) = 1000;
  *(uint32_t *)(*((uint32_t *)this + 2153) + 4) = 1600;
  pThis_771 = (uint8_t *)(*((uint32_t *)this + 1905) + 96);
  *((uint8_t *)this + 8723) = 0;
  *pThis_771 = 0;
  return sub_698F90((int)(this + 2210), 1000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
}



// 锤王三连：HAMMER_KING_02 + HAMMER_KING_03 + HAMMER_KING_01 播报组（77L；
//   三段连击音序 —— 与 0x5D5F10 崩地全演出配套）
// ------------------------------------------------------------
// 0x5D2710 sub_5D2710 —— 锤王三连段播报（HAMMER_KING_01/02/03）
// 透传 ·sub_5D19C0 后，姿态 8 且 vt+908==3 时按 8932 段号选语音 TAG（0/1/其余）经 vt+212 播报、
// ·sub_4DB130(24, 8934) 触发表情，并清 8924/8881/8882、8868 时钟归零、vt+888(4,4,1000,1000)、
// 6216 帧游标复位（·sub_4926A0）、vt+51 写 ·0x5D28D0 排程（8992 与子链 vt+672(3)+872 换算段时长）。
// 段号递增至 3 时归零并清 7620+96/8953/8954、按 9008 重排 8940；否则 vt+820(1) 收尾。
// ------------------------------------------------------------
int /*userpurge*/ sub_5D2710@<eax>(int pArg1@<ecx>, int nArg2@<edi>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  int v7; // eax
  const char *v8; // eax
  bool v9; // zf
  uint32_t *v10; // edi
  int v11; // eax
  int v12; // eax
  uint64_t v13; // rax
  int v14; // ecx
  int v15; // eax
  int *v17; // [esp+18h] [ebp+14h]

  sub_5D19C0((int **)pArg1, ArgList, fArg4, nArg5, nArg6);
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) == 8
    && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 908))(pArg1) == 3 )
  {
    sub_4DB130(24, *(uint32_t *)(pArg1 + 8932) + 2);
    v7 = *(uint32_t *)(pArg1 + 8932);
    if ( v7 != 0 )
    {
      v9 = v7 == 1;
      v8 = "HAMMER_KING_02";
      if ( !v9 )
        v8 = "HAMMER_KING_03";
    }
    else
    {
      v8 = "HAMMER_KING_01";
    }
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 212))(
      dword_8F7C04,
      v8,
      -1,
      0,
      0,
      nArg2);
    *(uint8_t *)(pArg1 + 8924) = 0;
    *(uint8_t *)(pArg1 + 8881) = 0;
    *(uint8_t *)(pArg1 + 8882) = 0;
    sub_698F90(pArg1 + 8868, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    (*(void (/*thiscall*/ **)(int, int, int, int, int))(*(uint32_t *)pArg1 + 888))(pArg1, 4, 4, 1000, 1000);
    sub_4926A0(*(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));
    v10 = (uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4);
    v17 = *(int **)pArg1;
    v11 = (*(int (/*thiscall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 192))(pArg1, 0, 0);
    ((void (/*thiscall*/ *)(int, int, uint32_t, uint32_t, int))v17[51])(pArg1, 1, *v10, 0, -v11);
    v12 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 672))(pArg1, 3);
    v13 = (uint64_t)((double)*(int *)(pArg1 + 8992) / (double)sub_41A5E0(v12 + 872) * 1000.0);
    v14 = *(uint32_t *)(pArg1 + 8932) + 1;
    *(uint32_t *)(pArg1 + 8928) = v13;
    *(uint32_t *)(pArg1 + 8932) = v14;
    if ( v14 == 3 )
    {
      v15 = *(uint32_t *)(pArg1 + 7620);
      *(uint32_t *)(pArg1 + 8932) = 0;
      *(uint8_t *)(v15 + 96) = 0;
      *(uint8_t *)(pArg1 + 8953) = 0;
      *(uint8_t *)(pArg1 + 8954) = 0;
      sub_698F90(pArg1 + 8940, *(uint32_t *)(pArg1 + 9008), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    return (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 820))(pArg1, 0);
  }
  else
  {
    *(uint8_t *)(pArg1 + 8881) = 0;
    *(uint8_t *)(pArg1 + 8882) = 0;
    (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 208))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 4));
    return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 820))(pArg1, 1);
  }
}



// 时钟门 AI（sub_699000, 119L）
// ------------------------------------------------------------
// 0x5D28D0 sub_5D28D0 —— 多段扇形散射门（血量比阈值 + 时钟）
// ·sub_5D2470 尾段后：7801 门为 0 时 8752 速率浮点置 1.0；8700==-1 时按 vt+736/vt+740
// 血量比与 8884+4*8840 阈值表比对（8840==8844、vt+308==1、7801==1、8840<3、姿态≠5）后
// ·sub_5D0CC0 按 8900+4*8840 布点、vt+560(32)+vt+564 起手；姿态 8 且 vt+908==2 时按
// 8920 周期 sin 呼吸写 dword_8F8528+623，8848 门首次触发时补 vt+764 事件与 30311 效果。
// ------------------------------------------------------------
char /*usercall*/ sub_5D28D0@<al>(int pArg1@<ecx>, int nArg2@<edi>)
{
  uint64_t v3; // rax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // eax
  unsigned int v8; // ecx
  unsigned int v9; // eax
  int v10; // edi
  int v11; // edi
  float v12; // edi
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  float v18; // [esp+4h] [ebp-8h]
  float v19; // [esp+8h] [ebp-4h]

  sub_5D2470(pArg1);
  LOBYTE(v3) = *(uint8_t *)(pArg1 + 7801);
  if ( (uint8_t)v3 == 0 )
    *(uint32_t *)(pArg1 + 8752) = 1065353216;
  if ( *(uint32_t *)(pArg1 + 8700) == -1 )
  {
    v18 = (float)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 736))(pArg1);
    v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 740))(pArg1);
    v5 = *(uint32_t *)(pArg1 + 8840);
    v19 = v18 / (double)v4;
    if ( v19 < (double)*(float *)(pArg1 + 4 * v5 + 8884)
      && v5 == *(uint32_t *)(pArg1 + 8844)
      && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 308))(pArg1) == 1
      && *(uint8_t *)(pArg1 + 7801) == 1
      && *(int *)(pArg1 + 8840) < 3
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1) != 5 )
    {
      v6 = *(uint32_t *)(pArg1 + 8840);
      ++*(uint32_t *)(pArg1 + 8844);
      sub_5D0CC0((float *)pArg1, *(uint32_t *)(pArg1 + 4 * v6 + 8900));
      (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)pArg1 + 560))(pArg1, 32, 0, 2, 0);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 564))(pArg1);
    }
    *(uint8_t *)(*(uint32_t *)(pArg1 + 7620) + 64) = (double)*(int *)(pArg1 + 8924) >= v19;
    LODWORD(v3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);
    if ( (uint32_t)v3 == 8 )
    {
      LODWORD(v3) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 908))(pArg1);
      if ( (uint32_t)v3 == 2 )
      {
        if ( sub_699000(pArg1 + 8852) <= *(uint32_t *)(pArg1 + 8880) )  // 【clock_now(clk)】
        {
          LOBYTE(v3) = (uint8_t)dword_8F8528;
          *((uint32_t *)dword_8F8528 + 623) = 0;
        }
        else
        {
          v7 = sub_699000(pArg1 + 8852);  // 【clock_now(clk)】
          v8 = *(uint32_t *)(pArg1 + 8920);
          v9 = v7 - *(uint32_t *)(pArg1 + 8880);
          if ( v9 >= v8 )
            LOBYTE(v3) = 0;
          else
            v3 = (uint64_t)(sin((double)(v8 + v9) * 6.2831841 / (double)(int)(4 * v8)) * 250.0);
          *((uint32_t *)dword_8F8528 + 623) = (uint8_t)v3;
          LOBYTE(v3) = *(uint8_t *)(pArg1 + 8848);
          if ( (uint8_t)v3 == 0 )
          {
            if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 608))(dword_8F7C04, nArg2) == 1 )
            {
              if ( (v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04),
                    (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) >= v10)
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 152))(dword_8F7C04) == 1
                || (v11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04),
                    (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) < v11)
                && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 152))(dword_8F7C04) == 0 )
              {
                (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)dword_8F7C04 + 764))(
                  dword_8F7C04,
                  3,
                  *(uint32_t *)(pArg1 + 8928),
                  pArg1,
                  0);
              }
            }
            (*(void (/*thiscall*/ **)(int, int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 764))(
              dword_8F7C04,
              6,
              *(uint32_t *)(pArg1 + 8928),
              pArg1);
            v12 = *(float *)pArg1;
            v13 = (*(int (/*thiscall*/ **)(int, int, uint32_t, uint32_t, int, int, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04
                                                                                                 + 124))(
                    dword_8F7C04,
                    30311,
                    0,
                    0,
                    4,
                    100,
                    2,
                    0,
                    0);
            v14 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04, v13);
            v15 = (*(int (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)dword_8F7C04 + 124))(dword_8F7C04, 0, v14);
            v16 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 120))(dword_8F7C04, v15);
            (*(void (/*thiscall*/ **)(int, int))(LODWORD(v12) + 584))(pArg1, v16);
            LOBYTE(v3) = sub_424120(*(uint32_t **)(*(uint32_t *)(pArg1 + 116) + 132), 3, *(uint32_t *)(pArg1 + 8920));
            *(uint8_t *)(pArg1 + 8848) = 1;
          }
        }
      }
    }
  }
  return v3;
}


// 冰守卫：R_ICE_GUARD 语音（91L；RTTI cast + this+8853/8854/8868/8872 相位；
//   8212 字段亦现 —— 守卫/邪眼共享字段区）
// ------------------------------------------------------------
// 0x5D2BB0 sub_5D2BB0 —— 冰守卫交互事件响应（R_ICE_GUARD）
// ·sub_4DC630 事件取参返回 15 时：取 8F8520 事件坐标对，·sub_45EBE0 解算对象并 RTTI 到 IRDCharacter，
// 扫描 8F850C 表 16..31 槽逐个匹配 +48/+52 坐标，命中后 8868 门为 0 时经 +8212 文案格式化
// ·sub_4D9F00 写提示、·sub_4D84F0 头顶气泡，并对命中对象 vt+212 播报 R_ICE_GUARD。
// 收尾清 8868/8853/8854，8840 时钟按 8872 duration 重排。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2BB0(int this)
{
  int result; // eax
  int v3; // eax
  int v4; // edi
  uint32_t *v5; // esi
  int pObj; // ecx
  int v7; // eax
  int v8; // eax
  uint32_t *v9; // eax
  const char *fld_2014; // eax
  uint32_t *v11; // [esp-Ch] [ebp-A0h]
  int v12; // [esp+4h] [ebp-90h] BYREF
  int v13; // [esp+8h] [ebp-8Ch]
  int v14; // [esp+Ch] [ebp-88h] BYREF
  char Buffer[128]; // [esp+10h] [ebp-84h] BYREF
  int dword_796E502; // [esp+90h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v13 = -1;
  result = sub_4DC630();
  if ( result != -1 )
  {
    if ( result == 15 )
    {
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v12);
      (*(void (/*thiscall*/ **)(int, int *))(*(uint32_t *)dword_8F8520 + 80))(dword_8F8520, &v14);
      v3 = sub_45EBE0(v12, v14);
      if ( __RTDynamicCast(v3, 0, &CNRDObject `RTTI Type Descriptor', &IRDCharacter `RTTI Type Descriptor', 0) != 0 )
      {
        v4 = 16;
        while ( 1 )
        {
          v5 = *(uint32_t **)(v4 + dword_8F850C);
          if ( v5 != nullptr )
          {
            pObj = v5[49];
            if ( pObj != 0 )
            {
              v7 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 48))(pObj);
              if ( v7 == v12 )
              {
                v8 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)v5[49] + 52))(v5[49]);
                if ( v8 == v14 )
                  break;
              }
            }
          }
          v4 += 4;
          if ( v4 >= 32 )
            goto LABEL_18;
        }
        if ( *(uint8_t *)(this + 8868) == 0 )
        {
          if ( v5[10] < 0x10u )
            v9 = v5 + 5;
          else
            v9 = (uint32_t *)v5[5];
          v11 = v9;
          fld_2014 = (const char *)sub_41ACF0(*(uint32_t *)(this + 8212) + 4);
          sprintf(Buffer, fld_2014, v11);
          sub_4D9F00(Buffer);
        }
        sub_4D84F0(0, 0);
        (*(void (/*thiscall*/ **)(uint32_t, const char *, int, uint32_t, uint32_t))(*(uint32_t *)v5[49] + 212))(
          v5[49],
          "R_ICE_GUARD",
          -1,
          0,
          0);
      }
LABEL_18:
      *(uint8_t *)(this + 8868) = 0;
      *(uint8_t *)(this + 8853) = 0;
      *(uint8_t *)(this + 8854) = 0;
      sub_698F90(this + 8840, *(uint32_t *)(this + 8872), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      return v13;
    }
    else
    {
      v13 = result;
    }
  }
  return result;
}



// RTTI cast 大型 AI（168L；this+8840 相位）
// ------------------------------------------------------------
// 0x5D2D50 sub_5D2D50 —— 暗黑火命中装配（CNFireBomb 挂件 + 42004 效果）
// nArg2 非 0 且 vt+40(obj,17) 判定为玩家时：8840 相位==2 且 vt+308==1 分支经 vt+628 取伤害、
// 按 2231 槽比率放大后 ±30 随机偏移三点，·sub_605840 打包、·sub_4E4A50 发 42004 效果。
// 2175 槽（-1 空闲）时遍历 vt+700 挂件表 RTTI 找 CNFireBomb：·sub_64D310 命中则以
// vt+560(31)+vt+564 触发；未找到则 new 0x1C0 + ·sub_64D6A0 装配暗黑火并 vt+56 挂装。
// 尾段姿态 14 且 nArg4==0 时 vt+1336 反击收手，最后透传 ·sub_5CEFF0。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D2D50(uint32_t *this, int nArg2, int pArg3, int nArg4)
{
  int nArg22; // ebx
  int pObj2; // eax
  int pObj; // esi
  void *v8; // eax
  double fld_e2231; // st7
  double v10; // st7
  float v11; // eax
  float v12; // edx
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // ecx
  int v23; // ecx
  int v24; // eax
  int v25; // ecx
  int v26; // ecx
  void *v27; // eax
  int *fld_e2232; // eax
  int v29; // edx
  int v31; // [esp-1Ch] [ebp-58h]
  int v32; // [esp-18h] [ebp-54h]
  int v33; // [esp-Ch] [ebp-48h]
  int v34; // [esp-8h] [ebp-44h]
  float v35; // [esp+8h] [ebp-34h] BYREF
  float v36; // [esp+Ch] [ebp-30h]
  float v37; // [esp+10h] [ebp-2Ch]
  int v38; // [esp+14h] [ebp-28h]
  int v39; // [esp+18h] [ebp-24h]
  int v40; // [esp+1Ch] [ebp-20h]
  uint8_t v41[4]; // [esp+20h] [ebp-1Ch] BYREF
  void *Block; // [esp+24h] [ebp-18h]
  int v43; // [esp+28h] [ebp-14h] BYREF
  char v44; // [esp+2Fh] [ebp-Dh] BYREF
  int v45; // [esp+38h] [ebp-4h]

  nArg22 = nArg2;
  if ( nArg2 != 0 )
  {
    pObj2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 576))(nArg2);
    pObj = pObj2;
    if ( pObj2 != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 17) != 0 )
    {
      if ( *((uint8_t *)this + 8840) == 2 && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 1 )
      {
        v8 = (void *)(*(int (/*thiscall*/ **)(uint32_t *, char *, uint8_t *, int, int, int, uint32_t))(*this + 628))(
                       this,
                       &v44,
                       v41,
                       100,
                       nArg2,
                       pArg3,
                       0);
        fld_e2231 = (double)(int)*(this + 2231);
        Block = v8;
        v10 = fld_e2231 * 0.0099999998 * (double)(int)v8;
        if ( v10 < 1.0 )
          v10 = 1.0;
        v11 = *(float *)(pArg3 + 4);
        v35 = *(float *)pArg3;
        v12 = *(float *)(pArg3 + 8);
        v36 = v11;
        v13 = *(uint32_t *)(pArg3 + 12);
        v37 = v12;
        v14 = *(uint32_t *)(pArg3 + 16);
        v38 = v13;
        v15 = *(uint32_t *)(pArg3 + 20);
        v43 = 0;
        v39 = v14;
        v40 = v15;
        Block = (void *)(rand() % 60 - 30);
        v35 = (double)(int)Block + v35;
        Block = (void *)(rand() % 60 - 30);
        v36 = (double)(int)Block + v36;
        Block = (void *)(rand() % 60 - 30);
        v37 = (double)(int)Block + v37;
        v34 = sub_605840(&v43, pObj, &v35, 0);
        v33 = v43;
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
        v31 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
        v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        sub_4E4A50((int)this, (int)this, 42004, (uint64_t)v10, v16, v31, v32, 1, 0, v33, v34);
        nArg22 = nArg2;
      }
      if ( *(this + 2175) == -1 )
      {
        v17 = 0;
        Block = nullptr;
        while ( 1 )
        {
          v18 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
          v19 = *(uint32_t *)(v18 + 4);
          v20 = v19 != 0 ? (*(uint32_t *)(v18 + 8) - v19) >> 2 : 0;
          if ( (int)v17 >= v20 )
            break;
          v21 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
          v22 = *(uint32_t *)(v21 + 4);
          if ( v22 != 0 && v17 < (*(uint32_t *)(v21 + 8) - v22) >> 2 )
            v23 = *(uint32_t *)(v22 + 4 * v17);
          else
            v23 = 0;
          if ( *(uint32_t *)(v23 + 4) == pObj )
          {
            v24 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 700))(pObj);
            v25 = *(uint32_t *)(v24 + 4);
            if ( v25 != 0 && v17 < (*(uint32_t *)(v24 + 8) - v25) >> 2 )
              v26 = *(uint32_t *)(v25 + 4 * v17);
            else
              v26 = 0;
            v27 = (void *)__RTDynamicCast(
                            v26,
                            0,
                            &IRDAppendage `RTTI Type Descriptor',
                            &CNFireBomb `RTTI Type Descriptor',
                            0);
            Block = v27;
            if ( v27 != nullptr )
            {
              if ( (uint8_t)sub_64D310(v27) == 1
                && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) == 1 )
              {
                (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t))(*this + 560))(this, 31, 0, 2, 0);
                (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
              }
              break;
            }
          }
          ++v17;
        }
        if ( Block == nullptr )
        {
          Block = operator new(0x1C0u);
          v45 = 0;
          if ( Block != nullptr )
            fld_e2232 = (int *)sub_64D6A0(*(this + 2232), *(this + 2233), *(this + 2234));
          else
            fld_e2232 = nullptr;
          v29 = *fld_e2232;
          v45 = -1;
          (*(void (/*thiscall*/ **)(int *, int, uint32_t *, uint32_t, uint32_t, int, int))(v29 + 56))(
            fld_e2232,
            pObj,
            this,
            0,
            0,
            39,
            -1);
        }
        nArg22 = nArg2;
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 14 && (uint8_t)nArg4 == 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 1336))(this, nArg22, pArg3, 0);
  return sub_5CEFF0(nArg22, pArg3, nArg4);
}


// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3060 sub_5D3060 —— 军团驱逐者号令复位（this+29 子表扫描）
// 遍历 this+29 容器，vt+40(obj,529) 过滤后 RTTI 到 IRDMonster 再定到 CNSoldier，
// 非自身的 CNSoldier 逐个交 ·sub_5CF0F0（军团兄弟单位联动收尾）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3060(int *this)
{
  int result; // eax
  unsigned int i; // esi
  int fld_e29; // ecx
  int v5; // edx
  int v6; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // eax

  result = *(this + 29);
  if ( result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);
      v5 = *(uint32_t *)(fld_e29 + 8);
      result = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;
      if ( (int)i >= result )
        break;
      v6 = *(uint32_t *)(fld_e29 + 8);
      if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
        pObj = *(uint32_t *)(v6 + 4 * i);
      else
        pObj = 0;
      if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
      {
        fld_e292 = *(this + 29);
        v9 = *(uint32_t *)(fld_e292 + 8);
        if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        v11 = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
        if ( v11 != 0 )
        {
          v12 = __RTDynamicCast(v11, 0, &IRDMonster `RTTI Type Descriptor', &CNSoldier `RTTI Type Descriptor', 0);
          if ( v12 != 0 && (int *)v12 != this )
            sub_5CF0F0(v12);
        }
      }
    }
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3130 sub_5D3130 —— 军团编队槽位清空（CNTinSwordManExpeller）
// 遍历 this+29 子表，vt+40(obj,529) 过滤、RTTI 定到 CNTinSwordManExpeller 后写 +8848 门为 0
// （释放该驱逐者的编队占位）。与 ·0x5D31D0 / ·0x5D3FD0 同族编队管理。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3130(uint32_t *this)
{
  unsigned int i; // esi
  int fld_e29; // ecx
  int v4; // edx
  int result; // eax
  int v6; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    result = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)i >= result )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj = *(uint32_t *)(v6 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * i);
      else
        v10 = 0;
      v11 = __RTDynamicCast(
              v10,
              0,
              &CNRDObject `RTTI Type Descriptor',
              &CNTinSwordManExpeller `RTTI Type Descriptor',
              0);
      if ( v11 != 0 )
        *(uint8_t *)(v11 + 8848) = 0;
    }
  }
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D31D0 sub_5D31D0 —— 最近编队驱逐者选取（按 vt+120 坐标取最小）
// 遍历 this+29 子表，RTTI 到 CNTinSwordManExpeller 且 vt+120 值小于当前最小者记录返回；
// 初值 99999 表示无候选时返回 0。·0x5D3FD0 编队搜索的前置取点。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D31D0(uint32_t *this)
{
  unsigned int v1; // edi
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int pObj3; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // eax
  int pObj2; // eax
  int pObj; // esi
  int pObj4; // [esp+Ch] [ebp-8h]
  int v15; // [esp+10h] [ebp-4h]

  v1 = 0;
  v15 = 99999;
  pObj4 = 0;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 8);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v4) >> 2 : 0;
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 8);
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 )
      pObj3 = *(uint32_t *)(v6 + 4 * v1);
    else
      pObj3 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj3 + 40))(pObj3, 529) != 0 )
    {
      fld_e292 = *(this + 29);
      v9 = *(uint32_t *)(fld_e292 + 8);
      if ( v9 != 0 && v1 < (*(uint32_t *)(fld_e292 + 12) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * v1);
      else
        v10 = 0;
      pObj2 = __RTDynamicCast(
              v10,
              0,
              &CNRDObject `RTTI Type Descriptor',
              &CNTinSwordManExpeller `RTTI Type Descriptor',
              0);
      pObj = pObj2;
      if ( pObj2 != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) < v15 )
      {
        v15 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        pObj4 = pObj;
      }
    }
    ++v1;
  }
  return pObj4;
}



// 军团呐喊：LEGION_SHOUT 播报（72L）
// ------------------------------------------------------------
// 0x5D32A0 sub_5D32A0 —— 军团呐喊状态切换（LEGION_SHOUT）
// 姿态与 ArgList 同为 20 时跳过；ArgList==8 且事件包首参为 0 时 vt+212 播报 LEGION_SHOUT。
// ArgList==20：8669 门为 1 时置 8832、6216 帧游标复位（·sub_4926A0）、vt+196 转移、
// vt+344 清场、vt+876 双轴速率清零、写 8812=1/8816=4；再 ·sub_45EBE0 解算目标，
// vt+40 校验玩家后按 vt+120 比较大小改写 8816（朝向），vt+144 提交；
// 最后经 8669 门透传 ·sub_4E33D0 状态收尾。
// ------------------------------------------------------------
uint32_t */*userpurge*/ sub_5D32A0@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  uint32_t *result; // eax
  char v8; // di
  int *v9; // eax
  int pObj; // eax
  int pObj2; // edi
  int v12; // edi

  result = (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 840))(pArg1);
  v8 = ArgList;
  if ( result != (uint32_t *)20 || ArgList != 20 )
  {
    if ( ArgList == 8 )
    {
      result = *(uint32_t **)(LODWORD(fArg4) + 4);
      if ( *result == 0 )
        result = (uint32_t *)(*(int (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(
                             pArg1,
                             "LEGION_SHOUT",
                             -1,
                             0,
                             0);
    }
    else if ( ArgList == 20 )
    {
      if ( *(uint8_t *)(pArg1 + 8669) != 1 )
        return result;
      v9 = (int *)(*(uint32_t *)(pArg1 + 6216) + 20);
      *(uint8_t *)(pArg1 + 8832) = 1;
      sub_4926A0(*v9);
      (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)pArg1 + 196))(pArg1, *(uint32_t *)(*(uint32_t *)(pArg1 + 6216) + 20), nArg2);
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 344))(pArg1, *(uint32_t *)(pArg1 + 556));
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(
        pArg1,
        0,
        0,
        0,
        0,
        0,
        0);
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 876))(
        pArg1,
        1,
        0,
        0,
        0,
        0,
        0);
      *(uint8_t *)(pArg1 + 8812) = 1;
      *(uint32_t *)(pArg1 + 8816) = 4;
      pObj = sub_45EBE0(**(uint32_t **)(LODWORD(fArg4) + 4), *(uint32_t *)(*(uint32_t *)(LODWORD(fArg4) + 4) + 4));
      pObj2 = pObj;
      if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 17) != 0 )
      {
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2);
        *(uint32_t *)(pArg1 + 8816) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 120))(pArg1) < v12;
      }
      result = (uint32_t *)(*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 144))(pArg1, *(uint32_t *)(pArg1 + 8816));
      v8 = 20;
    }
    if ( *(uint8_t *)(pArg1 + 8669) == 1 )
      return (uint32_t *)sub_4E33D0(v8, fArg4, nArg5, nArg6);
  }
  return result;
}



// ============================================================
// 【分区 4】守卫核心 AI 与霸体（0x5D3400-0x5D5C30）
// 证据：AMOR_HIT 阿莫尔命中三连（0x5D4340/0x5D4420/0x5D4480）、SUPERARMOR 霸体播报
//       （0x5D47D0 —— 研究 20 §1.2 vt+720 霸体 setter 的调用侧）、REPAIR_OBJECT

// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3400 sub_5D3400 —— 最近军团驱逐者选取（CNLegionExpeller, 类型 704）
// 遍历 this+29 的 +120/+124 子表，RTTI 到 CNLegionExpeller，排除自身且 vt+340 类型码 == 704，
// 用 vt+8 距离取最小者返回；·0x5D41E0 环绕布点的目标解算。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3400(uint32_t *this)
{
  unsigned int v1; // ebx
  int fld_e29; // ecx
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int pObj; // eax
  int pObj2; // esi
  int pObj22; // [esp+Ch] [ebp-8h]
  int v12; // [esp+10h] [ebp-4h]

  v1 = 0;
  pObj22 = 0;
  v12 = 99999;
  while ( 1 )
  {
    fld_e29 = *(this + 29);
    v4 = *(uint32_t *)(fld_e29 + 120);
    v5 = v4 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v4) >> 2 : 0;
    if ( (int)v1 >= v5 )
      break;
    v6 = *(uint32_t *)(fld_e29 + 120);
    if ( v6 != 0 && v1 < (*(uint32_t *)(fld_e29 + 124) - v6) >> 2 )
      v7 = *(uint32_t *)(v6 + 4 * v1);
    else
      v7 = 0;
    pObj = __RTDynamicCast(v7, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNLegionExpeller `RTTI Type Descriptor', 0);
    pObj2 = pObj;
    if ( (uint32_t *)pObj != this
      && pObj != 0
      && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 704
      && (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0) < v12 )
    {
      v12 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj2, 0);
      pObj22 = pObj2;
    }
    ++v1;
  }
  return pObj22;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D34C0 sub_5D34C0 —— 编队格占用检测（nArg2/nArg3 坐标）
// 遍历 this+29 子表，RTTI 到 CNLegionExpeller 后比对 +8820/+8824 与传入坐标：
// 已有同坐标占用者返回 0（冲突），全表无冲突返回 1（可放置）。·0x5D41E0 放置前校验。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D34C0(uint32_t *this, int nArg2, int nArg3)
{
  unsigned int i; // esi
  int fld_e29; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // edx
  int pObj; // ecx
  int fld_e292; // ecx
  int v11; // edx
  int v12; // eax
  int v13; // eax

  for ( i = 0; ; ++i )
  {
    fld_e29 = *(this + 29);
    v6 = *(uint32_t *)(fld_e29 + 8);
    v7 = v6 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v6) >> 2 : 0;
    if ( (int)i >= v7 )
      break;
    v8 = *(uint32_t *)(fld_e29 + 8);
    if ( v8 != 0 && i < (*(uint32_t *)(fld_e29 + 12) - v8) >> 2 )
      pObj = *(uint32_t *)(v8 + 4 * i);
    else
      pObj = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) != 0 )
    {
      fld_e292 = *(this + 29);
      v11 = *(uint32_t *)(fld_e292 + 8);
      if ( v11 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v11) >> 2 )
        v12 = *(uint32_t *)(v11 + 4 * i);
      else
        v12 = 0;
      v13 = __RTDynamicCast(v12, 0, &CNRDObject `RTTI Type Descriptor', &CNLegionExpeller `RTTI Type Descriptor', 0);
      if ( v13 != 0 && *(uint32_t *)(v13 + 8820) == nArg2 && *(uint32_t *)(v13 + 8824) == nArg3 )
        return 0;
    }
  }
  return 1;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5D3590 sub_5D3590 —— 场上军团驱逐者计数（类型 704）
// 遍历 this+29 子表，vt+40(obj,529) 过滤后 RTTI 到 IRDMonster，统计 vt+340 == 704 者数量；
// ·0x5D42A0 以计数 > 1 作为编队移动门。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3590(uint32_t *this)
{
  int v1; // ebx
  unsigned int i; // esi
  int fld_e29; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v10; // edx
  int v11; // eax
  int pObj; // eax

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
      pObj2 = *(uint32_t *)(v7 + 4 * i);
    else
      pObj2 = 0;
    if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj2 + 40))(pObj2, 529) != 0 )
    {
      fld_e292 = *(this + 29);
      v10 = *(uint32_t *)(fld_e292 + 8);
      if ( v10 != 0 && i < (*(uint32_t *)(fld_e292 + 12) - v10) >> 2 )
        v11 = *(uint32_t *)(v10 + 4 * i);
      else
        v11 = 0;
      pObj = __RTDynamicCast(v11, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
      if ( *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 704 )
        ++v1;
    }
  }
  return v1;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D3640 sub_5D3640 —— 编队档位清位（vt+1172 档位 → 子对象 +32..+160 五槽）
// vt+1172 返回值按 >0/5/10/15/20 分档，逐级清 *(this+1905) 子对象内 +32/+64/+96/+128/+160
// 五个相位位；返回值直接回传。·0x5D5A60 以其 >5 选择 vt+384 参数 0 或 1 作为编队规模档。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3640(int *this)
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
        *(uint8_t *)(*(this + 1905) + 128) = 0;
LABEL_6:
        result = *(this + 1905);
        *(uint8_t *)(result + 160) = 0;
        return result;
      }
    }
    else
    {
      *(uint8_t *)(*(this + 1905) + 32) = 0;
    }
    *(uint8_t *)(*(this + 1905) + 64) = 0;
    *(uint8_t *)(*(this + 1905) + 96) = 0;
    goto LABEL_5;
  }
  return result;
}



// AI 相位字段（this+8602..8604）
// ------------------------------------------------------------
// 0x5D36C0 sub_5D36C0 —— 编队挂件装配（8602/8603/8604 三相门）
// nArg2==1 或 2 时按相位推进：vt+788(16/13) 装配、vt+1324 相位解除，8603/8604 立门；
// 首入时 vt+788(0)+vt+788(1) 双状态、vit 取 this+2166 对象，vt+12 解链后按
// vt+128/vt+124(+65)/vt+120 换算槽位交 vt+40 定位、vt+92 取包，·sub_4600B0(2,...) 派发。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D36C0(uint8_t *this, int nArg2)
{
  char v3; // cl
  char fld_e8603; // al
  char fld_e8602; // al
  int pThis_876; // edi
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  void *pThis_1D; // ecx
  uint8_t v11[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v13; // [esp+1Ch] [ebp-4h]

  v3 = 0;
  if ( nArg2 == 0 )
    goto LABEL_8;
  if ( nArg2 == 1 )
  {
LABEL_6:
    if ( *(this + 8603) != 0 )
      goto LABEL_10;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 16);
    fld_e8602 = *(this + 8602);
    *(this + 8603) = 1;
    v3 = 1;
    if ( fld_e8602 != 0 )
      goto LABEL_11;
LABEL_8:
    if ( *(this + 8602) == 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 788))(this, 0);
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 1);
      *(this + 8602) = 1;
LABEL_11:
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**((uint32_t **)this + 2166) + 12))(*((uint32_t *)this + 2166), 0);
      pThis_876 = **((uint32_t **)this + 2166);
      pThis_80 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 128))(this);
      pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, pThis_80 + 65);
      pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 120))(this, pThis_7C);
      (*(void (/*thiscall*/ **)(uint32_t, int))(pThis_876 + 40))(*((uint32_t *)this + 2166), pThis_78);
      (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**((uint32_t **)this + 2166) + 92))(*((uint32_t *)this + 2166), v11);
      pThis_1D = *((void **)this + 29);
      v13 = 0;
      sub_4600B0(pThis_1D, 2, 0, (int)v11);
      if ( Block != nullptr )
        j__free(Block);
      return;
    }
LABEL_10:
    if ( v3 != 1 )
      return;
    goto LABEL_11;
  }
  if ( nArg2 == 2 && *(this + 8604) == 0 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 788))(this, 13);
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 1324))(this);
    fld_e8603 = *(this + 8603);
    *(this + 8604) = 1;
    v3 = 1;
    if ( fld_e8603 != 0 )
      goto LABEL_11;
    goto LABEL_6;
  }
}



// 主状态门（this+200/8604/8660, 105L）
// ------------------------------------------------------------
// 0x5D3810 sub_5D3810 —— 军团呐喊表现铺设（vt+200 状态对象 +148 == 1 分支）
// vt+200 状态对象 +148 为 1 时：按 7028 帧位（·sub_41A5E0）走 vt+876 双轴速率（0 档用 8612
// 双元值配 -2000/-3000 延时）；8604 门为 0 时补 vt+876(1)、vt+888(2,2,1000,1000)、
// vt+152(4)+vt+896 提交；8660 门时取 8F8270[vt+924(this,2)] 池对象定位（vt+152 判定 ±20 朝向偏移）。
// +148 == 0 时置 8660 门待下一帧。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D3810(uint8_t *this)
{
  int pThis_94; // eax
  int v3; // edi
  int pThis_98; // eax
  uint32_t *pThis_39C; // edi
  int v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // eax
  int pThis_7C; // eax
  int pThis_982; // edi
  uint32_t *pThis_39C22; // edi
  void *pThis_1D; // ecx
  void *Block2; // eax
  int pThis_78; // [esp-Ch] [ebp-34h]
  char v17[4]; // [esp+4h] [ebp-24h] BYREF
  void *Block; // [esp+8h] [ebp-20h]
  uint32_t *pThis_39C2; // [esp+14h] [ebp-14h]
  bool v20; // [esp+1Bh] [ebp-Dh]
  int v21; // [esp+24h] [ebp-4h]

  pThis_94 = *(uint32_t *)((*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 200))(this) + 148);
  if ( pThis_94 != 0 )
  {
    if ( pThis_94 == 1 )
    {
      if ( sub_41A5E0((unsigned int)(this + 7028)) != 0 )
      {
        if ( sub_41A5E0((unsigned int)(this + 7028)) == 1 )
          (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 876))(
            this,
            0,
            *(uint32_t *)(*((uint32_t *)this + 2153) + 4),
            *(uint32_t *)(*((uint32_t *)this + 2153) + 4),
            0,
            -3000,
            1);
      }
      else
      {
        (*(void (/*thiscall*/ **)(uint8_t *, uint32_t, uint32_t, uint32_t, uint32_t, int, int))(*(uint32_t *)this + 876))(
          this,
          0,
          **((uint32_t **)this + 2153),
          **((uint32_t **)this + 2153),
          0,
          -2000,
          1);
      }
      if ( *(this + 8604) == 0 )
      {
        (*(void (/*thiscall*/ **)(uint8_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 876))(
          this,
          1,
          0,
          0,
          0,
          0,
          0);
        (*(void (/*thiscall*/ **)(uint8_t *, int, int, int, int))(*(uint32_t *)this + 888))(this, 2, 2, 1000, 1000);
        v3 = *(uint32_t *)this;
        pThis_98 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 152))(this, 4);
        (*(void (/*thiscall*/ **)(uint8_t *, int))(v3 + 896))(this, pThis_98);
      }
      if ( *(this + 8660) == 1 )
      {
        pThis_39C = (uint32_t *)dword_8F8270[(*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 924))(this, 2)];
        v6 = *(uint32_t *)this;
        pThis_39C2 = pThis_39C;
        v7 = (*(int (/*thiscall*/ **)(uint8_t *))(v6 + 152))(this);
        v8 = *(uint32_t *)this;
        v9 = *pThis_39C;
        v20 = v7 == 0;
        v10 = (*(int (/*thiscall*/ **)(uint8_t *))(v8 + 128))(this);
        pThis_7C = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 124))(this, v10);
        pThis_982 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 152))(this, pThis_7C + 1) != 0 ? -20 : 20;
        pThis_78 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 120))(this) + pThis_982;
        pThis_39C22 = pThis_39C2;
        (*(void (/*thiscall*/ **)(uint32_t *, int))(v9 + 40))(pThis_39C2, pThis_78);
        *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pThis_39C2 + 28))(pThis_39C2) + 84) = v20;
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pThis_39C22 + 12))(pThis_39C22, 0);
        (*(void (/*thiscall*/ **)(uint32_t *, char *))(*pThis_39C22 + 92))(pThis_39C22, v17);
        pThis_1D = *((void **)this + 29);
        v21 = 0;
        sub_4600B0(pThis_1D, 2, 0, (int)v17);
        Block2 = Block;
        *(this + 8660) = 0;
        if ( Block2 != nullptr )
          j__free(Block2);
      }
    }
  }
  else
  {
    *(this + 8660) = 1;
  }
}



// 时钟门 AI（sub_699000; this+8840/8841 相位, 130L）
// ------------------------------------------------------------
// 0x5D39D0 sub_5D39D0 —— 军团驱逐者编队主循环（出生点重定位 + 编队态切换）
// ·sub_5D2470 尾段后：2175 空闲门内，2214 子对象 vt+68 判定下按 2226/2218/2219 参数
// ±随机散布出生坐标，vt+12 归位、vt+92 取包，·sub_4600B0 重定位；2216/2215 速率对偶按
// 0.02 步长收敛并 ·sub_4EB4B0/·sub_4EB2C0/·sub_4EB6E0/·sub_4EB6A0 逐槽下发。
// 2217 时钟到点后按 8841 与 2221 阈值及 8840 相位分 21/22/23 号状态交 vt+560+vt+564。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5D39D0(int *this)
{
  unsigned int result; // eax
  int fld_e2226; // edx
  int fld_e2218; // edi
  int fld_e2219; // ebx
  int nRand; // eax
  int v7; // edx
  int nRand2; // edi
  int v9; // edx
  void *v10; // eax
  double pThis_8A8; // st7
  uint8_t v13; // c0
  uint8_t v14; // c3
  double pThis_8A7; // st7
  float v16; // ebx
  uint32_t *pThis_651; // edi
  int fld_e2217; // edi
  int v19; // ebx
  int v20; // [esp-14h] [ebp-38h]
  int v21; // [esp-10h] [ebp-34h]
  float pThis_8A82; // [esp-Ch] [ebp-30h]
  char v23[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v25; // [esp+Ch] [ebp-18h]
  int v26; // [esp+10h] [ebp-14h]
  int i; // [esp+14h] [ebp-10h]
  int v28; // [esp+20h] [ebp-4h]

  result = sub_5D2470();
  if ( *(this + 2175) != -1 )
    return result;
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2214) + 68))(*(this + 2214)) != 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2214) + 12))(*(this + 2214), 0);
  }
  else if ( (*(int (/*thiscall*/ **)(int *))(*this + 128))(this) == 0 )
  {
    fld_e2226 = *(this + 2226) * *((uint8_t *)this + 8840) / 100 + 1;
    fld_e2218 = fld_e2226 * *(this + 2218);
    fld_e2219 = fld_e2226 * *(this + 2219);
    nRand = rand();
    v7 = *this;
    i = nRand % fld_e2218 - fld_e2218 / 2;
    i += (*(int (/*thiscall*/ **)(int *))(v7 + 120))(this);
    nRand2 = rand() % fld_e2219 - fld_e2219 / 2;
    v21 = (*(int (/*thiscall*/ **)(int *))(*this + 124))(this) + nRand2;
    v20 = i;
    (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2214) + 40))(*(this + 2214));
    (*(void (/*thiscall*/ **)(uint32_t, char *))(*(uint32_t *)*(this + 2214) + 92))(*(this + 2214), v23);
    v9 = *this;
    v28 = 0;
    v10 = (void *)(*(int (/*thiscall*/ **)(int *, int, uint32_t, char *))(v9 + 80))(this, 2, 0, v23);
    sub_4600B0(v10, v20, v21, 0);
    v28 = -1;
    if ( Block != nullptr )
      j__free(Block);
    Block = nullptr;
    v25 = 0;
    v26 = 0;
  }
  if ( *((float *)this + 2216) != *((float *)this + 2215) )
  {
    i = *(this + 2216);
    pThis_8A8 = *((float *)this + 2216);
    if ( (v13 | v14) != 0 )
    {
      pThis_8A7 = pThis_8A8 - 0.02;
      if ( pThis_8A7 >= *((float *)this + 2215) )
        goto LABEL_14;
    }
    else
    {
      pThis_8A7 = pThis_8A8 + 0.02;
      if ( pThis_8A7 <= *((float *)this + 2215) )
        goto LABEL_14;
    }
    pThis_8A7 = *((float *)this + 2215);
LABEL_14:
    v16 = *(float *)&i;
    *((float *)this + 2216) = pThis_8A7;
    (*(void (/*thiscall*/ **)(int *))(*this + 688))(this);
    sub_4EB4B0(v16);
    pThis_8A82 = *((float *)this + 2216);
    (*(void (/*thiscall*/ **)(int *))(*this + 688))(this);
    sub_4EB2C0(pThis_8A82);
    pThis_651 = this + 1617;
    for ( i = 18; i != 0; --i )
    {
      if ( *pThis_651 != 0 )
      {
        sub_4EB6E0(v16);
        sub_4EB6A0(*((float *)this + 2216));
      }
      ++pThis_651;
    }
  }
  fld_e2217 = *(this + 2217);
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( fld_e2217 + *(this + 2220) < result || fld_e2217 == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
    {
      v19 = 22;
      if ( sub_41A5E0((char *)this + 8841) >= *(this + 2221) )
      {
        if ( sub_41A5E0((char *)this + 8841) >= *(this + 2221) && *((uint8_t *)this + 8840) != 0 )
          v19 = 23;
      }
      else if ( *((uint8_t *)this + 8840) != 2 )
      {
        v19 = 21;
      }
      (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, v19, 0, 2, 0);
      result = (*(int (/*thiscall*/ **)(int *))(*this + 564))(this);
      *(this + 2217) = -1;
    }
    else
    {
      result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
      *(this + 2217) = result;
    }
  }
  return result;
}


// 时钟门 AI（this+8601/8603/8669/8812..8837, 73L）
// ------------------------------------------------------------
// 0x5D3CB0 sub_5D3CB0 —— 雷守卫主帧（蓄雷循环 + 编队召唤收尾）
// 姿态 8 时按 7028 帧位：==1 走 vt+1332 收招；0/2/3 时 ·sub_4D9360 帧推进，==3 额外
// ·0x5D0330(1,...) 蓄雷播报（BEFORE_THUNDER）；8812 门 + 7028==1 + 8824<3 +
// 8816+8820 逾时钟（·sub_699000）时 vt+352 追击并刷新 8816。非攻击态 ·sub_4D93D0 帧退。
// 尾段 ·sub_5CF180 + 8669/8603/8601 三条件走 vt+1344；8837 门为 0 时构造 8F8520 事件
// （29/2 + 坐标对 + 14）并 ·0x5D3060 号令复位，置 8837。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D3CB0(int this)
{
  int pThis_348; // eax
  int v3; // edi
  int pThis_30; // eax
  int v5; // edi
  int pThis_34; // eax
  int v7; // edi
  int v8; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
  {
    if ( sub_41A5E0(this + 7028) == 1 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
    }
    else if ( sub_41A5E0(this + 7028) == 0 || sub_41A5E0(this + 7028) == 2 || sub_41A5E0(this + 7028) == 3 )
    {
      if ( sub_41A5E0(this + 7028) == 3 )
        sub_5D0330((int *)this, 1, this + 7028);
      sub_4D9360(this);
    }
  }
  if ( *(uint8_t *)(this + 8812) == 1
    && sub_41A5E0(this + 7028) == 1
    && *(int *)(this + 8824) < 3
    && *(uint32_t *)(this + 8816) + *(uint32_t *)(this + 8820) < (unsigned int)sub_699000(this + 36) )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 352))(this);
    *(uint32_t *)(this + 8816) = sub_699000(this + 36);
  }
  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) != 8 )
    sub_4D93D0(this);
  LOBYTE(pThis_348) = sub_5CF180((uint32_t *)this);
  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8603);
    if ( (uint8_t)pThis_348 == 0 && *(uint8_t *)(this + 8601) == 1 )
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
      if ( pThis_348 == 0 )
        LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
    }
    if ( *(uint8_t *)(this + 8669) == 1 )
    {
      LOBYTE(pThis_348) = *(uint8_t *)(this + 8837);
      if ( (uint8_t)pThis_348 == 0 )
      {
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 8))(dword_8F8520, 29, 2);
        v3 = *(uint32_t *)dword_8F8520;
        pThis_30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 48))(this);
        (*(void (/*thiscall*/ **)(int, int))(v3 + 36))(dword_8F8520, pThis_30);
        v5 = *(uint32_t *)dword_8F8520;
        pThis_34 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 52))(this);
        (*(void (/*thiscall*/ **)(int, int))(v5 + 36))(dword_8F8520, pThis_34);
        v7 = *(uint32_t *)dword_8F8520;
        v8 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
        (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
        (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 14);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        LOBYTE(pThis_348) = sub_5D3060((int *)this);
        *(uint8_t *)(this + 8837) = 1;
      }
    }
  }
  return pThis_348;
}



// AI 字段访问（this+8837）
// ------------------------------------------------------------
// 0x5D3E70 sub_5D3E70 —— 事件门号令复位（8837 一次性门）
// ·sub_4DC630 取事件 == 14 且 8837 门为 0 时，·0x5D3060 号令复位并置 8837；其余事件原样返回。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3E70(int this)
{
  int result; // eax
  int v3; // edi

  result = sub_4DC630();
  v3 = result;
  if ( result != -1 )
  {
    if ( result == 14 && *(uint8_t *)(this + 8837) == 0 )
    {
      sub_5D3060((int *)this);
      *(uint8_t *)(this + 8837) = 1;
    }
    return v3;
  }
  return result;
}



// AI 相位字段（this+8603/8664）
// ------------------------------------------------------------
// 0x5D3EB0 sub_5D3EB0 —— 军团驱逐者播报转发（8664 子对象定位）
// 姿态 14 且 8603 门为 0 时 vt+1336 反击收手；nArg4 非 0 则直接透传 ·sub_5CEFF0。
// 随后 this+8664 对象 vt+12 归位、按 vt+128/vt+124(+65)/vt+120 定位 vt+40、vt+92 取包，
// ·sub_4600B0(2,...) 派发后仍透传 ·sub_5CEFF0 状态收尾。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D3EB0(int this, int nArg2, int nArg3, int nArg4)
{
  int fld_21D8; // edi
  int pThis_80; // eax
  int pThis_7C; // eax
  int pThis_78; // eax
  void *fld_74; // ecx
  uint8_t v11[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v13; // [esp+Ch] [ebp-14h]
  int v14; // [esp+10h] [ebp-10h]
  int v15; // [esp+1Ch] [ebp-4h]

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 14 )
  {
    if ( (uint8_t)nArg4 != 0 )
      return sub_5CEFF0((uint8_t *)this, nArg2, nArg3, nArg4);
    if ( *(uint8_t *)(this + 8603) == 0 )
      (*(void (/*thiscall*/ **)(int, int, int, uint32_t))(*(uint32_t *)this + 1336))(this, nArg2, nArg3, 0);
  }
  else if ( (uint8_t)nArg4 != 0 )
  {
    return sub_5CEFF0((uint8_t *)this, nArg2, nArg3, nArg4);
  }
  (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 8664) + 12))(*(uint32_t *)(this + 8664), 0);
  fld_21D8 = **(uint32_t **)(this + 8664);
  pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
  pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_80 + 65);
  pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C);
  (*(void (/*thiscall*/ **)(uint32_t, int))(fld_21D8 + 40))(*(uint32_t *)(this + 8664), pThis_78);
  (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(**(uint32_t **)(this + 8664) + 92))(*(uint32_t *)(this + 8664), v11);
  fld_74 = *(void **)(this + 116);
  v15 = 0;
  sub_4600B0(fld_74, 2, 0, (int)v11);
  v15 = -1;
  if ( Block != nullptr )
    j__free(Block);
  Block = nullptr;
  v13 = 0;
  v14 = 0;
  return sub_5CEFF0((uint8_t *)this, nArg2, nArg3, nArg4);
}



// 时钟门+RTTI AI（122L）
// ------------------------------------------------------------
// 0x5D3FD0 sub_5D3FD0 —— 编队格位搜索（48x480 网格扫描 + 时间门）
// 2211 时钟未到返回 0；到点后 ·0x5D3130 清位、2218/2219 归零、698F90(10000) 起长时门。
// ·0x5D31D0 取自身时，以 this+29 子链 vt+672(3) 尺寸算网格上界，48 步长双层循环扫
// ·0x5D34C0 空位与 vt+136 地形可用性，命中则写 8812/8816 并 vt+1144 落位；否则 8848 置位。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D3FD0(int *this)
{
  int pThis_89D; // esi
  int fld_e2211; // edi
  int v5; // eax
  int pObj2; // edx
  int fld_e29; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // esi
  unsigned int v12; // edi
  int fld_e292; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // edx
  int pObj; // ecx
  int fld_e293; // ecx
  int v19; // edx
  int v20; // eax
  int v21; // esi
  int v22; // edx
  int v23; // [esp+Ch] [ebp-10h]
  int v24; // [esp+10h] [ebp-Ch]
  int v25; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]

  pThis_89D = (int)(this + 2205);
  fld_e2211 = *(this + 2211);
  if ( sub_699000((int)(this + 2205)) < fld_e2211 )  // 【clock_now(clk)】
    return 0;
  sub_5D3130(this);
  *(uint8_t *)(pThis_89D + 13) = 0;
  *(uint8_t *)(pThis_89D + 14) = 0;
  sub_698F90(pThis_89D, 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  v5 = sub_5D31D0(this);
  pObj2 = v5;
  v24 = v5;
  if ( v5 != 0 && (int *)v5 == this )
  {
    fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
    v8 = *(uint32_t *)(fld_e29 + 364);
    v9 = fld_e29 + 360;
    v10 = v8 != 0 ? (*(uint32_t *)(v9 + 8) - v8) >> 5 : 0;
    v11 = 224 * v10;
    v23 = 224 * v10;
    v25 = 48 * ((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 120))(pObj2) / 48);
    if ( v25 < v11 )
    {
LABEL_9:
      v26 = 0;
      while ( 1 )
      {
        v12 = 0;
        while ( 1 )
        {
          fld_e292 = *(this + 29);
          v14 = *(uint32_t *)(fld_e292 + 8);
          v15 = v14 != 0 ? (*(uint32_t *)(fld_e292 + 12) - v14) >> 2 : 0;
          if ( (int)v12 >= v15 )
            break;
          v16 = *(uint32_t *)(fld_e292 + 8);
          if ( v16 != 0 && v12 < (*(uint32_t *)(fld_e292 + 12) - v16) >> 2 )
            pObj = *(uint32_t *)(v16 + 4 * v12);
          else
            pObj = 0;
          if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 529) == 0 )
            goto LABEL_31;
          fld_e293 = *(this + 29);
          v19 = *(uint32_t *)(fld_e293 + 8);
          if ( v19 != 0 && v12 < (*(uint32_t *)(fld_e293 + 12) - v19) >> 2 )
            v20 = *(uint32_t *)(v19 + 4 * v12);
          else
            v20 = 0;
          v21 = __RTDynamicCast(
                  v20,
                  0,
                  &CNRDObject `RTTI Type Descriptor',
                  &CNTinSwordManExpeller `RTTI Type Descriptor',
                  0);
          if ( v24 == v21 )
          {
            (*(void (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 15);
            ++v12;
          }
          else
          {
            if ( v21 != 0
              && *(uint8_t *)(v21 + 8848) == 0
              && *(uint32_t *)(v21 + 8812) != v25
              && *(uint32_t *)(v21 + 8816) != v26
              && (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(*this + 136))(this, v25, v26, 0) != 0 )
            {
              v22 = *(uint32_t *)v21;
              *(uint32_t *)(v21 + 8816) = v26;
              *(uint32_t *)(v21 + 8812) = v25;
              *(uint8_t *)(v21 + 8848) = 1;
              (*(void (/*thiscall*/ **)(int, int, int))(v22 + 1144))(v21, v25, v26);
              break;
            }
LABEL_31:
            ++v12;
          }
        }
        v26 += 48;
        if ( v26 >= 480 )
        {
          v25 += 48;
          if ( v25 >= v23 )
            return 1;
          goto LABEL_9;
        }
      }
    }
  }
  return 1;
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5D41E0 sub_5D41E0 —— 环绕八点布位（±48 步长）
// ·0x5D3400 取最近军团驱逐者作锚点，按 -48/0/48 组合枚举 8 个环绕格位，逐点叠加锚点
// vt+120/vt+124 作绝对坐标，·0x5D34C0 判空位与 vt+136 判可用，命中即 break 并回传出参。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D41E0(uint32_t *this, int *pDwArg2, int *pDwArg3)
{
  int pObj; // esi
  int i; // ebx
  int v6; // eax
  int v8; // [esp+Ch] [ebp-40h]
  uint32_t v9[15]; // [esp+10h] [ebp-3Ch]

  pObj = sub_5D3400(this);
  v8 = 0;
  v9[0] = -48;
  v9[1] = 0;
  v9[2] = 48;
  v9[3] = 48;
  v9[4] = 0;
  v9[5] = -48;
  v9[6] = 0;
  v9[7] = 48;
  v9[8] = -48;
  v9[9] = -48;
  v9[10] = 48;
  v9[11] = -48;
  v9[12] = -48;
  v9[13] = 48;
  v9[14] = 48;
  for ( i = 0; i < 8; ++i )
  {
    if ( pObj != 0 )
    {
      *pDwArg2 = v9[2 * i - 1] + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
      v6 = v9[2 * i] + (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
      *pDwArg3 = v6;
      if ( sub_5D34C0(this, *pDwArg2, v6) != 0
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*this + 136))(this, *pDwArg2, *pDwArg3, 0) != 0 )
      {
        break;
      }
    }
  }
  return pObj;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D42A0 sub_5D42A0 —— 编队落位判定（count>1 且后仰非 25 号）
// ·0x5D3590 计数 > 1 且 1813 门为 0 时，取自身坐标交 ·0x5D41E0 找格位；命中后以
// vt+8 距离落在 64..100 区间与 1787 行为字 == 25 对照，走 vt+1144 落位或 vt+1104 写 15 号行为字。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D42A0(uint32_t *this)
{
  int result; // eax
  int v3; // eax
  int v4; // edx
  int v5; // [esp+4h] [ebp-8h] BYREF
  int v6; // [esp+8h] [ebp-4h] BYREF

  result = sub_5D3590(this);
  if ( *(this + 1813) == 0 && result > 1 )
  {
    v3 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    v4 = *this;
    v5 = v3;
    v6 = (*(int (/*thiscall*/ **)(uint32_t *))(v4 + 124))(this);
    result = sub_5D41E0(this, &v5, &v6);
    if ( result != 0 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, result, 0);
      if ( result > 100 || result < 64 )
      {
        if ( *(this + 1787) != 25 )
          return (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 1144))(this, v5, v6);
      }
      else if ( *(this + 1787) == 25 )
      {
        return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1104))(this, 15);
      }
    }
  }
  return result;
}



// 阿莫尔命中 1：AMOR_HIT + Particle/ExpellerBrokenParts.ptl（24L；受击掉碎屑）
// ------------------------------------------------------------
// 0x5D4340 sub_5D4340 —— 阿莫尔战损第一段（AMOR_HIT + 爆碎粒子）
// 清 8600 门、·sub_4015C0 写 AMOR_HIT 语音槽（8 字节短串）、2176/2177/2178 三槽置 -1；
// 按 96 槽长短路判定（SSO）取 364 或 +91 字符串，vt+1352 装载
// Particle/ExpellerBrokenParts.ptl（机体爆碎）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4340(uint8_t *this)
{
  *(this + 8600) = 0;
  sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
  *((uint32_t *)this + 2176) = -1;
  *((uint32_t *)this + 2177) = -1;
  *((uint32_t *)this + 2178) = -1;
  if ( *((uint32_t *)this + 96) < 0x10u )
    return (*(int (/*thiscall*/ **)(uint8_t *, uint8_t *, const char *))(*(uint32_t *)this + 1352))(
             this,
             this + 364,
             "Particle/ExpellerBrokenParts.ptl");
  else
    return (*(int (/*thiscall*/ **)(uint8_t *, uint32_t, const char *))(*(uint32_t *)this + 1352))(
             this,
             *((uint32_t *)this + 91),
             "Particle/ExpellerBrokenParts.ptl");
}



// AI 相位字段（this+8601/8603/8669）
// ------------------------------------------------------------
// 0x5D43B0 sub_5D43B0 —— 编队搜索帧（主帧包装）
// 攻击态先 vt+1332 收招；8669 门为 1 时调 ·0x5D3FD0 编队格位搜索，再 ·sub_5CF180 基类帧，
// 尾段 8603/8601 + 姿态 0 走 vt+1344 二次判定（与 ·0x5D0070 同构收尾）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D43B0(int this)
{
  int pThis_348; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
  if ( *(uint8_t *)(this + 8669) == 1 )
    sub_5D3FD0((int *)this);
  LOBYTE(pThis_348) = sub_5CF180((uint32_t *)this);
  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8603);
    if ( (uint8_t)pThis_348 == 0 && *(uint8_t *)(this + 8601) == 1 )
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
      if ( pThis_348 == 0 )
        LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
    }
  }
  return pThis_348;
}



// 阿莫尔命中 2：AMOR_HIT 播报（this+8600/8820/8833/8834/8848 相位）
// ------------------------------------------------------------
// 0x5D4420 sub_5D4420 —— 阿莫尔战损第二段（位置双槽重置）
// 清 8600 门，vt+52 取当前坐标写 2203/2204 双槽，8833/8834 归零，8820 时钟按 10000ms 起计时，
// 清 8848 门与 2213 槽，最后 ·sub_4015C0 写 AMOR_HIT 语音槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4420(uint8_t *this)
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)this;
  *(this + 8600) = 0;
  v3 = (*(int (**)(void))(v2 + 52))();
  *((uint32_t *)this + 2204) = v3;
  *((uint32_t *)this + 2203) = v3;
  *(this + 8833) = 0;
  *(this + 8834) = 0;
  sub_698F90((int)(this + 8820), 10000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(this + 8848) = 0;
  *((uint32_t *)this + 2213) = 0;
  return sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
}



// 阿莫尔命中 3：AMOR_HIT 播报（this+8601/8812/8832 相位）
// ------------------------------------------------------------
// 0x5D4480 sub_5D4480 —— 阿莫尔战损第三段（编队门清位）
// 清 8601/8812/8600 三门，vt+52 取坐标写 2205/2206 双槽、2207 归零，清 8832 门，
// 最后 ·sub_4015C0 写 AMOR_HIT 语音槽。与 ·0x5D4420 同构（差异：清 8601/8812/8832 组）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4480(uint8_t *this)
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)this;
  *(this + 8601) = 0;
  *(this + 8812) = 0;
  *(this + 8600) = 0;
  v3 = (*(int (**)(void))(v2 + 52))();
  *((uint32_t *)this + 2206) = v3;
  *((uint32_t *)this + 2205) = v3;
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 0;
  return sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
}



// 复合门（this+200/568/8669/8812/8832 —— this+568 最后受击时刻, 研究 20 §1.2）
// ------------------------------------------------------------
// 0x5D44D0 sub_5D44D0 —— 阿莫尔主帧（姿态 8/20 分支 + 受击联动）
// 姿态 8 时按 7028 帧位 0/1 走 vt+1332 收招、2 进入 20 号段：+148<=1 且 vt+308 时
// 8812 门联动 vt+896+vt+876（1400/-2000）、8F8270[vt+924(this,2)] 池对象定位并 ·sub_5E5260；
// +148>1 且 vt+308 与 vt+568（最后受击时刻）非 0 时 vt+560(0,0,0,0) 复位。
// 尾段 8669 门走 ·0x5D42A0，8832 门走 ·sub_4D83E0 惊叹气泡并清位，最后 ·sub_5CF180 基类帧。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D44D0(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int pObj; // edi
  bool v5; // bl
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  void *fld_e29; // ecx
  int fld_e2204; // [esp-8h] [ebp-30h]
  void *v13[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v14; // [esp+24h] [ebp-4h]

  v2 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( v2 == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 0 || sub_41A5E0((unsigned int)(this + 1757)) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1332))(this);
    else
      sub_41A5E0((unsigned int)(this + 1757));
  }
  else if ( v2 == 20 )
  {
    if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) <= 1 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*this + 200))(this) + 148) >= 1
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
      {
        if ( *((uint8_t *)this + 8812) == 1 )
        {
          v3 = *this;
          fld_e2204 = *(this + 2204);
          *((uint8_t *)this + 8812) = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, int, int))(v3 + 896))(this, fld_e2204, 4);
          (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, int, int, uint32_t, int, int))(*this + 876))(
            this,
            0,
            1400,
            1400,
            0,
            -2000,
            1);
        }
        pObj = dword_8F8270[(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 924))(this, 2)];
        v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) == 0;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj) + 84) = v5;
        v6 = *(uint32_t *)pObj;
        v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
        v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 124))(this, v7);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 120))(this, v8);
        (*(void (/*thiscall*/ **)(int, int))(v6 + 40))(pObj, v9);
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
        (*(void (/*thiscall*/ **)(int, void **))(*(uint32_t *)pObj + 92))(pObj, v13);
        fld_e29 = (void *)*(this + 29);
        v14 = 0;
        sub_4600B0(fld_e29, 2, 0, (int)v13);
        v14 = -1;
        sub_5E5260(v13);
      }
    }
    else if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 568))(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
    }
  }
  if ( *((uint8_t *)this + 8669) == 1 )
    sub_5D42A0(this);
  if ( *((uint8_t *)this + 8832) != 0 )
  {
    sub_4D83E0(0, 0);
    *((uint8_t *)this + 8832) = 0;
  }
  return sub_5CF180(this);
}



// 语音注册（sub_4015C0; 容器越界串为 STL 断言文本, 非游戏资源）
// ------------------------------------------------------------
// 0x5D46D0 sub_5D46D0 —— STL vector 下标越界抛掷（编译器内联展开的异常路径）
// 构造 std::out_of_range 对象（_TI3_AVout_of_range_std__）并 _CxxThrowException；
// 源码侧即 v[i] 越界检查失败的 noreturn 桩，非业务逻辑。
// ------------------------------------------------------------
void /*noreturn*/ sub_5D46D0()
{
  void **pExceptionObject; // [esp+0h] [ebp-50h] BYREF
  uint8_t v1[20]; // [esp+28h] [ebp-28h] BYREF
  int v2; // [esp+3Ch] [ebp-14h]
  int v3; // [esp+40h] [ebp-10h]
  int v4; // [esp+4Ch] [ebp-4h]

  v3 = 15;
  v2 = 0;
  v1[4] = 0;
  sub_4015C0("invalid vector<T> subscript", 0x1Bu);  // 【std::string构造赋值】
  v4 = 0;
  sub_401740(v1);
  pExceptionObject = &std::out_of_range::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// 语音注册（sub_4015C0）
// ------------------------------------------------------------
// 0x5D4740 sub_5D4740 —— STL list 结点计数累加（超限抛 length_error）
// 以 357913941（0x15555555 上限）校验 this+2 计数，溢出则抛 std::length_error；
// 否则 this+2 += uArg2 并回传新计数。·0x5D48D0 中以 1 递增相位记录环长度。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4740(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  void **pExceptionObject; // [esp+4h] [ebp-50h] BYREF
  uint8_t v5[20]; // [esp+2Ch] [ebp-28h] BYREF
  int v6; // [esp+40h] [ebp-14h]
  int v7; // [esp+44h] [ebp-10h]
  int v8; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 357913941 - fld_e2 < uArg2 )
  {
    v7 = 15;
    v6 = 0;
    v5[4] = 0;
    sub_4015C0("list<T> too long", 0x10u);  // 【std::string构造赋值】
    v8 = 0;
    sub_401740(v5);
    pExceptionObject = &std::length_error::`vftable';
    _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ★ 霸体：SUPERARMOR 播报（32L；sub_699000 时钟门 —— 研究 20 §1.2 vt+720 霸体 setter
//   的怪物侧调用场景, 霸体开启演出）
// ------------------------------------------------------------
// 0x5D47D0 sub_5D47D0 —— 霸体状态事件（SUPERARMOR 播报, 24/25 号）
// ArgList 非 24/25 时透传 ·sub_5D19C0；否则按 vt+736/vt+740 血量比与 8864 系数算出
// 8844 缓冲时间（8852+4*首参 槽），8848 记时钟；8700==-1 时 ·sub_4DB200(24,..) +
// vt+212 播报 SUPERARMOR，8840 相位写 ArgList!=24，尾调 vt+248(992字节槽, 8844)。
// ------------------------------------------------------------
int /*userpurge*/ sub_5D47D0@<eax>(int pArg1@<ecx>, int nArg2@<edi>, int ArgList, float fArg4, int nArg5, int nArg6)
{
  uint64_t v7; // rax
  uint32_t *v8; // edi
  int *v9; // edx
  float v11; // [esp+1Ch] [ebp+14h]

  if ( ArgList < 24 || ArgList > 25 )
    return sub_5D19C0((int **)pArg1, ArgList, fArg4, nArg5, nArg6);
  v11 = (float)(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 736))(pArg1, nArg2);
  v7 = (uint64_t)((1.0 - v11 / (double)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 740))(pArg1))
                        * (double)*(int *)(pArg1 + 8864));
  v8 = *(uint32_t **)(LODWORD(fArg4) + 4);
  if ( v8 == nullptr || (*(uint32_t *)(LODWORD(fArg4) + 8) - (int)v8) >> 2 == 0 )
    sub_454B50();
  *(uint32_t *)(pArg1 + 8844) = *(uint32_t *)(pArg1 + 4 * *v8 + 8852) - v7;
  *(uint32_t *)(pArg1 + 8848) = sub_699000(pArg1 + 36);
  if ( *(uint32_t *)(pArg1 + 8700) == -1 )
  {
    sub_4DB200(24, (ArgList != 24) + 1);
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)pArg1 + 212))(pArg1, "SUPERARMOR", -1, 0, 0);
  }
  v9 = *(int **)pArg1;
  *(uint32_t *)(pArg1 + 8840) = ArgList != 24;
  return ((int (/*thiscall*/ *)(int, uint32_t))v9[248])(pArg1, *(uint32_t *)(pArg1 + 8844));
}



// 大型 AI（183L；sub_699000 + this+8840..8998 守卫相位字段）
// ------------------------------------------------------------
// 0x5D48D0 sub_5D48D0 —— 军团驱逐者计时器总调度（2211..2262 多时钟）
// ·sub_5D2470 尾段后于 2175 空闲门内依次巡检: 2211 时钟（8840 相位与 940 门下 28 号状态）、
// 2243/2244 血量比阈值→26/27 号状态、2236 逾 1000 时 8F8520 事件 + ±随机坐标 vt+136 探测、
// 2235/2229 记录环（·sub_5D2440 摘除 + ·0x5D1490 造记录 + ·0x5D4740 计数）、
// 2246 逾 2252 时 8F8270 池对象定位 + 2261/2262 随机重排。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D48D0(int *this)
{
  int fld_e2217; // ebx
  int fld_e2243; // edi
  int v4; // eax
  int fld_e22432; // eax
  int v6; // edx
  int v7; // edi
  int v8; // eax
  int v9; // edi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int fld_e29; // edi
  int v14; // edi
  int nRand; // ebx
  int nRand2; // edx
  int v17; // eax
  int fld_e2235; // edi
  int v20; // eax
  int v21; // edx
  uint32_t *fld_e2227; // eax
  int v23; // ebx
  int nRand222; // eax
  int fld_e2252; // edi
  int pObj; // edi
  int v27; // eax
  int v28; // ebx
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  void *fld_e292; // ecx
  int nRand3; // eax
  char v35[4]; // [esp+4h] [ebp-38h] BYREF
  void *Block; // [esp+8h] [ebp-34h]
  uint32_t v37[3]; // [esp+14h] [ebp-28h] BYREF
  int nRand22; // [esp+20h] [ebp-1Ch]
  float v39; // [esp+24h] [ebp-18h]
  int v40; // [esp+28h] [ebp-14h]
  bool v41; // [esp+2Fh] [ebp-Dh]
  int v42; // [esp+38h] [ebp-4h]

  sub_5D2470();
  if ( *(this + 2175) == -1 )
  {
    fld_e2217 = *(this + 2217);
    if ( sub_699000((int)(this + 2211)) >= fld_e2217 && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 0 )  // 【clock_now(clk)】
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1
        && *((uint8_t *)this + 8840) == 0
        && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 28, 0, 2, 0);
        (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);
      }
      *((uint8_t *)this + 8840) = 0;
      *((uint8_t *)this + 8857) = 0;
      *((uint8_t *)this + 8858) = 0;
      sub_698F90((int)(this + 2211), *(this + 2253), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    fld_e2243 = *(this + 2243);
    v40 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
    v4 = *this;
    v39 = (float)v40;
    v40 = (*(int (/*thiscall*/ **)(int *))(v4 + 740))(this);
    if ( v39 / (double)v40 < *((float *)this + fld_e2243 + 2256)
      && fld_e2243 == *(this + 2244)
      && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
    {
      fld_e22432 = *(this + 2243);
      if ( fld_e22432 != 2 )
      {
        if ( fld_e22432 != 0 )
        {
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 27, 0, 2, 0);
          *(this + 2244) = 2;
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, int, uint32_t, int, uint32_t))(*this + 560))(this, 26, 0, 2, 0);
          *(this + 2244) = 1;
        }
        (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);
      }
    }
    if ( sub_699000((int)(this + 2236)) > 1000 )  // 【clock_now(clk)】
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 1
        && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
      {
        v6 = *(uint32_t *)dword_8F8520;
        v40 = 100;
        (*(void (/*thiscall*/ **)(int, int, int))(v6 + 8))(dword_8F8520, 29, 2);
        v7 = *(uint32_t *)dword_8F8520;
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 48))(this);
        (*(void (/*thiscall*/ **)(int, int))(v7 + 36))(dword_8F8520, v8);
        v9 = *(uint32_t *)dword_8F8520;
        v10 = (*(int (/*thiscall*/ **)(int *))(*this + 52))(this);
        (*(void (/*thiscall*/ **)(int, int))(v9 + 36))(dword_8F8520, v10);
        v11 = *(uint32_t *)dword_8F8520;
        v12 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F7C04 + 52))(dword_8F7C04);
        (*(void (/*thiscall*/ **)(int, int))(v11 + 36))(dword_8F8520, v12);
        fld_e29 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
        v39 = COERCE_FLOAT(sub_425050(fld_e29));
        v14 = 120 * (sub_424FF0(fld_e29) + 3);
        do
        {
          nRand = rand() % SLODWORD(v39);
          nRand2 = rand() % v14;
          v17 = *this;
          nRand22 = nRand2;
          if ( (*(uint8_t (/*thiscall*/ **)(int *, int, int, uint32_t))(v17 + 136))(this, nRand, nRand2, 0) == 1 )
            break;
        }
        while ( v40-- != 0 );
        if ( v40 != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 36))(dword_8F8520, 17);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nRand);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F8520 + 40))(dword_8F8520, nRand22);
          (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)dword_8F8520 + 60))(dword_8F8520, 1, -1);
        }
      }
      *((uint8_t *)this + 8957) = 0;
      *((uint8_t *)this + 8958) = 0;
    }
    fld_e2235 = *(this + 2235);
    if ( sub_699000((int)(this + 2229)) >= fld_e2235 )  // 【clock_now(clk)】
    {
      if ( *(this + 2228) == *(this + 2254) )
        sub_5D2440(this + 2226);
      v20 = (*(int (/*thiscall*/ **)(int *))(*this + 120))(this);
      v21 = *this;
      v37[0] = v20;
      v37[1] = (*(int (/*thiscall*/ **)(int *))(v21 + 124))(this);
      v37[2] = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
      fld_e2227 = (uint32_t *)*(this + 2227);
      v23 = *fld_e2227;
      nRand22 = sub_5D1490(*fld_e2227, *(uint32_t *)(*fld_e2227 + 4), v37);
      sub_5D4740(1);
      nRand222 = nRand22;
      *(uint32_t *)(v23 + 4) = nRand22;
      **(uint32_t **)(nRand222 + 4) = nRand222;
      *((uint8_t *)this + 8929) = 0;
      *((uint8_t *)this + 8930) = 0;
      sub_698F90((int)(this + 2229), *(this + 2255), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 940))(this) == 1 )
    {
      fld_e2252 = *(this + 2252);
      if ( sub_699000((int)(this + 2246)) >= fld_e2252 )  // 【clock_now(clk)】
      {
        pObj = dword_8F8270[(*(int (/*thiscall*/ **)(int *, int))(*this + 924))(this, 2)];
        v27 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this);
        v28 = *(uint32_t *)pObj;
        v41 = v27 == 0;
        v29 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
        v30 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v29);
        v31 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v30);
        (*(void (/*thiscall*/ **)(int, int))(v28 + 40))(pObj, v31);
        v32 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 28))(pObj);
        *(uint8_t *)(v32 + 84) = v41;
        (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 12))(pObj, 0);
        (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pObj + 92))(pObj, v35);
        fld_e292 = (void *)*(this + 29);
        v42 = 0;
        sub_4600B0(fld_e292, 2, 0, (int)v35);
        *((uint8_t *)this + 8997) = 0;
        *((uint8_t *)this + 8998) = 0;
        nRand3 = rand();
        sub_698F90((int)(this + 2246), *(this + 2261) + nRand3 % *(this + 2262), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
        if ( Block != nullptr )
          j__free(Block);
      }
    }
  }
}


// AI 相位辅助
// ------------------------------------------------------------
// 0x5D4D00 sub_5D4D00 —— 霸体 PO 挂装（vt+1757 帧位 2 分支）
// 姿态 8 且 7028 帧位为 2 时：2204 槽空则 new 0x64 + ·sub_51A7D0 构造霸体 PO 并回写 +64 派生
// 对象 +36 位；到位后 vt+80 判定未挂装则 vt+56 挂装。非该帧位下若 PO 已挂装则 vt+76 摘除；
// 最后 ·sub_5CF180 基类帧。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D4D00(uint32_t *this)
{
  void *pMem; // eax
  int pObj; // eax
  int fld_e2204; // ecx

  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 8 )
  {
    if ( sub_41A5E0((unsigned int)(this + 1757)) == 0 || sub_41A5E0((unsigned int)(this + 1757)) == 1 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1332))(this);
    }
    else if ( sub_41A5E0((unsigned int)(this + 1757)) == 2 )
    {
      if ( *(this + 2204) == 0 )
      {
        pMem = operator new(0x64u);
        if ( pMem != nullptr )
          pObj = sub_51A7D0(pMem);
        else
          pObj = 0;
        *(this + 2204) = pObj;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
      }
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2204) + 80))(*(this + 2204)) == 0 )
        (*(void (/*thiscall*/ **)(uint32_t, uint32_t *, uint32_t *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2204) + 56))(
          *(this + 2204),
          this,
          this,
          0,
          0,
          0,
          -1);
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 8 || sub_41A5E0((unsigned int)(this + 1757)) != 2 )
  {
    fld_e2204 = *(this + 2204);
    if ( fld_e2204 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2204 + 80))(fld_e2204) == 1 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*(this + 2204) + 76))(*(this + 2204), 0);
  }
  return sub_5CF180(this);
}



// 斧驱逐者破碎 3：Particle/AxeExpellerBrokenParts.ptl（32L）
// ------------------------------------------------------------
// 0x5D4E30 sub_5D4E30 —— 斧驱逐者战损（AxeExpellerBrokenParts.ptl）
// 清 2176/2177/2178 三槽、vt+1308 复位；new 0x7C + ·sub_4B3DF0(5,1,-10.0,20000,0) 构造爆碎
// 颗粒对象写 2203 槽并清派生 +36 位；按 96 槽长短路取 364 或 +91 字符串，
// vt+1352 装载 Particle/AxeExpellerBrokenParts.ptl。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D4E30(uint32_t *this)
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  uint32_t *pThis_5B; // eax

  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  pMem = operator new(0x7Cu);
  if ( pMem != nullptr )
    v3 = sub_4B3DF0(pMem, 5, 1, -1035468800, 20000, 0);
  else
    v3 = nullptr;
  *(this + 2203) = v3;
  *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v3 + 64))(v3) + 36) = 0;
  if ( *(this + 96) < 0x10u )
    pThis_5B = this + 91;
  else
    pThis_5B = (uint32_t *)*(this + 91);
  return (*(int (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
           this,
           pThis_5B,
           "Particle/AxeExpellerBrokenParts.ptl");
}



// AI 相位辅助（126L）
// ------------------------------------------------------------
// 0x5D4EF0 sub_5D4EF0 —— 火属性守卫表现分派（7028 帧位 2/3/5 三分支）
// 2090 槽非空 + 8820 门为 0 + 8669 门非 0 时置 8820 并 vt+1360 触发。
// 主状态 1639==8 时按 7028 帧位：0/1 走 vt+1332 收招；2/3/5 在子链 +148>=4、vt+308 与 8812
// 齐备时各取 vt+384 参数（11 / 2+3 / 6+7+8）构造效果 —— 分别 new 0x80+·sub_4D6810(500,1,1)、
// new 0x7C+·sub_4B3DF0(21,1,..)、new 0x1D0+·sub_64B6C0（火焰动画），并 vt+56 挂装。
// 尾段 ·sub_5CF180 + 8669/8603/8601 三条件走 vt+1344 收尾。
// ------------------------------------------------------------
char /*usercall*/ sub_5D4EF0@<al>(uint8_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  int v5; // edi
  int v6; // eax
  uint8_t *pMem; // edi
  int *v8; // eax
  int v9; // edi
  uint32_t *pMem2; // eax
  int v11; // edx
  int v12; // edi
  int v13; // ebx
  int *v14; // eax
  int v15; // edx
  int v16; // eax
  int v18; // [esp+8h] [ebp-38h]
  int v19; // [esp+Ch] [ebp-34h]
  int v21; // [esp+1Ch] [ebp-24h] BYREF
  char v22; // [esp+20h] [ebp-20h]
  float v23; // [esp+24h] [ebp-1Ch]
  void *Block; // [esp+28h] [ebp-18h]
  float v25; // [esp+2Ch] [ebp-14h]
  int v26; // [esp+30h] [ebp-10h]
  int v27; // [esp+3Ch] [ebp-4h]

  if ( *((uint32_t *)pArg1 + 2090) != 0 && pArg1[8820] == 0 && pArg1[8669] != 0 )
  {
    v4 = *(uint32_t *)pArg1;
    pArg1[8820] = 1;
    (*(void (**)(void))(v4 + 1360))();
  }
  v5 = *(uint32_t *)(*((uint32_t *)pArg1 + 30) + 148);
  if ( *((uint32_t *)pArg1 + 1639) == 8 )
  {
    switch ( sub_41A5E0((unsigned int)(pArg1 + 7028)) )
    {
      case 0:
      case 1:
        (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 1332))(pArg1);
        break;
      case 2:
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8812] != 0 )
        {
          v6 = (*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 11, nArg3);
          v26 = v6;
          pArg1[8812] = 0;
          v25 = (double)v6 * 0.0099999998;
          pMem = operator new(0x80u);
          Block = pMem;
          v27 = 0;
          if ( pMem == nullptr )
            goto LABEL_18;
          v26 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 740))(pArg1);
          *(float *)&v18 = (double)v26 * v25;
          v8 = (int *)sub_4D6810(pMem, v18, 500, 1, 1);
          goto LABEL_19;
        }
        break;
      case 3:
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8812] != 0 )
        {
          v25 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 2, nArg3));
          v9 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 3);
          pArg1[8812] = 0;
          pMem2 = operator new(0x7Cu);
          Block = pMem2;
          v27 = 1;
          if ( pMem2 != nullptr )
          {
            *(float *)&v19 = (float)SLODWORD(v25);
            v8 = sub_4B3DF0(pMem2, 21, 1, v19, v9, 0);
          }
          else
          {
LABEL_18:
            v8 = nullptr;
          }
LABEL_19:
          v11 = *v8;
          v27 = -1;
          (*(void (/*thiscall*/ **)(int *, uint8_t *, uint8_t *, uint32_t, uint32_t, uint32_t))(v11 + 56))(v8, pArg1, pArg1, 0, 0, 0);
        }
        break;
      case 5:
        if ( v5 >= 4 && (*(uint8_t (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1) != 0 && pArg1[8812] != 0 )
        {
          v25 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint8_t *, int, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 6, nArg2, nArg3));
          v12 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 7);
          v13 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 384))(pArg1, 8);
          v23 = (float)SLODWORD(v25);
          pArg1[8812] = 0;
          v21 = 5;
          v22 = 1;
          Block = operator new(0x1D0u);
          v27 = 2;
          if ( Block != nullptr )
            v14 = (int *)sub_64B6C0(v12, &v21, 1, v13, 1, 0);
          else
            v14 = nullptr;
          v15 = *v14;
          v27 = -1;
          (*(void (/*thiscall*/ **)(int *, uint8_t *, uint8_t *, uint32_t, uint32_t))(v15 + 56))(v14, pArg1, pArg1, 0, 0);
        }
        break;
      default:
        break;
    }
  }
  LOBYTE(v16) = sub_5CF180(pArg1);
  if ( pArg1[8669] == 1 )
  {
    LOBYTE(v16) = pArg1[8603];
    if ( (uint8_t)v16 == 0 && pArg1[8601] == 1 )
    {
      v16 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 840))(pArg1);
      if ( v16 == 0 )
        LOBYTE(v16) = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 1344))(pArg1);
    }
  }
  return v16;
}


// 守卫字段大复位（this+8600..8738 全区, 88L）
// ------------------------------------------------------------
// 0x5D51D0 sub_5D51D0 —— 守卫字段大复位（8600..8738 全区 + 参数面向量重建）
// 1639 主状态置 19、8668/8669 门与 8600/8601 立位、8604/8602 清零；2156..2163 与 1698..1702
// 两组槽清零/初始化（后者写 0/1/1/2/3）；8612 参数面向量先试原地压入 700 否则 ·sub_430C80 追加，
// 8608 同法写入 1000；8685/8686、2175、8721/8722 清位，vt+820(0) 归位；
// 尾段 8737/8738 清位、8724 时钟按 100ms 起计时、2179 置 3、2188 速率写 1.0、8723 置 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D51D0(char *this)
{
  char *pThis_21A0; // edi
  int pThis_869; // eax
  unsigned int pThis_86A; // edx
  uint32_t *pThis_86A2; // eax
  int v6; // edx
  unsigned int v7; // ecx
  uint32_t *v8; // eax
  int v9; // eax
  char result; // al
  int v11; // [esp+Ch] [ebp-4h] BYREF

  *((uint32_t *)this + 1639) = 19;
  *(this + 8668) = 1;
  *(this + 8669) = 0;
  *(this + 8660) = 0;
  *(this + 8600) = 1;
  *(this + 8601) = 1;
  *((uint16_t *)this + 4301) = 0;
  *(this + 8604) = 0;
  *((uint32_t *)this + 2156) = 0;
  *((uint32_t *)this + 2157) = 0;
  *((uint32_t *)this + 2158) = 0;
  *((uint32_t *)this + 2159) = 0;
  *((uint32_t *)this + 2160) = 0;
  *((uint32_t *)this + 2161) = 0;
  *((uint32_t *)this + 2162) = 0;
  *((uint32_t *)this + 2163) = 0;
  pThis_21A0 = this + 8608;
  *((uint32_t *)this + 1698) = 0;
  *((uint32_t *)this + 1699) = 1;
  *((uint32_t *)this + 1700) = 1;
  *((uint32_t *)this + 1701) = 2;
  *((uint32_t *)this + 1702) = 3;
  pThis_869 = *((uint32_t *)this + 2153);
  v11 = 700;
  if ( pThis_869 != 0 )
    pThis_86A = (*((uint32_t *)this + 2154) - pThis_869) >> 2;
  else
    pThis_86A = 0;
  if ( pThis_869 != 0 && pThis_86A < (*((uint32_t *)this + 2155) - pThis_869) >> 2 )
  {
    pThis_86A2 = *((uint32_t **)this + 2154);
    *pThis_86A2 = 700;
    *((uint32_t *)this + 2154) = pThis_86A2 + 1;
  }
  else
  {
    sub_430C80(*((void **)this + 2154), 1, (int)&v11);
  }
  v6 = *((uint32_t *)pThis_21A0 + 1);
  v11 = 1000;
  if ( v6 != 0 )
    v7 = (*((uint32_t *)pThis_21A0 + 2) - v6) >> 2;
  else
    v7 = 0;
  if ( v6 != 0 && v7 < (*((uint32_t *)pThis_21A0 + 3) - v6) >> 2 )
  {
    v8 = *((uint32_t **)pThis_21A0 + 2);
    *v8 = 1000;
    *((uint32_t *)pThis_21A0 + 2) = v8 + 1;
  }
  else
  {
    sub_430C80(*((void **)pThis_21A0 + 2), 1, (int)&v11);
  }
  *(this + 8685) = 0;
  *(this + 8686) = 0;
  v9 = *(uint32_t *)this;
  *((uint32_t *)this + 2175) = 0;
  *(this + 8721) = 0;
  *(this + 8722) = 0;
  (*(void (/*thiscall*/ **)(char *, uint32_t))(v9 + 820))(this, 0);
  *(this + 8737) = 0;
  *(this + 8738) = 0;
  result = sub_698F90((int)(this + 8724), 100, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *((uint32_t *)this + 2179) = 3;
  *((uint32_t *)this + 2188) = 1065353216;
  *(this + 8723) = 1;
  return result;
}



// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5D5370 sub_5D5370 —— 近身随机起手（50% 门 + 150 距离）
// 50% 随机命中、1813 槽对象 vt+40(17) 为玩家、vt+8 距离 < 150 三条件齐备时，
// ·sub_431230 打包参数 {1} 后 vt+560(8, ...) 转 8 号状态（近身攻击起手）。
// ------------------------------------------------------------
void /*thiscall*/ sub_5D5370(uint32_t *this)
{
  uint8_t v2[4]; // [esp+4h] [ebp-20h] BYREF
  void *Block; // [esp+8h] [ebp-1Ch]
  int v4; // [esp+Ch] [ebp-18h]
  int v5; // [esp+10h] [ebp-14h]
  uint32_t v6[4]; // [esp+14h] [ebp-10h] BYREF

  if ( rand() % 100 < 50
    && (*(uint8_t (/*thiscall*/ **)(uint32_t, int))(*(uint32_t *)*(this + 1813) + 40))(*(this + 1813), 17) != 0
    && (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 8))(this, *(this + 1813), 0) < 150 )
  {
    Block = nullptr;
    v4 = 0;
    v5 = 0;
    v6[3] = 0;
    v6[0] = 1;
    sub_431230((int)v2, v6);
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, uint32_t, uint32_t))(*this + 560))(this, 8, v2, 0, 0);
    if ( Block != nullptr )
      j__free(Block);
  }
}



// 时钟门 AI（sub_699000; this+8853/8854）
// ------------------------------------------------------------
// 0x5D5420 sub_5D5420 —— 冰守卫光环收束（2210 时钟 + 8F850C 对象表 16..31）
// ·sub_5D2470 尾段后 2175 空闲门内，2216 时钟到点且 vt+308 为 1 时扫描 8F850C 表 16..31 槽，
// 对 +196 槽对象 vt+724 == 0 者 ·sub_487F60 收束；随后清 8853/8854，2210 时钟按 2218 重排。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D5420(int *this)
{
  int pThis_8A2; // eax
  int fld_e2216; // edi
  int i; // ebx
  int v5; // edi
  int pObj; // ecx
  int v8; // [esp+4h] [ebp-3Ch]
  int v9; // [esp+8h] [ebp-38h]
  int v10; // [esp+Ch] [ebp-34h]
  int v11; // [esp+10h] [ebp-30h]
  int v12; // [esp+14h] [ebp-2Ch]
  int v13; // [esp+18h] [ebp-28h]
  int v14; // [esp+1Ch] [ebp-24h]
  void *Block; // [esp+24h] [ebp-1Ch]
  int v16; // [esp+28h] [ebp-18h]
  int v17; // [esp+2Ch] [ebp-14h]
  int v18; // [esp+30h] [ebp-10h] BYREF
  int v19; // [esp+3Ch] [ebp-4h]

  LOBYTE(pThis_8A2) = sub_5D2470((int)this);
  if ( *(this + 2175) == -1 )
  {
    fld_e2216 = *(this + 2216);
    pThis_8A2 = sub_699000((int)(this + 2210));  // 【clock_now(clk)】
    if ( pThis_8A2 >= fld_e2216 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
      {
        Block = nullptr;
        v16 = 0;
        v17 = 0;
        v19 = 0;
        v8 = 0;
        v9 = 0;
        v10 = 0;
        v11 = 0;
        v12 = 0;
        v13 = 0;
        v14 = 0;
        for ( i = 16; i < 32; i += 4 )
        {
          v5 = *(uint32_t *)(i + dword_8F850C);
          if ( v5 != 0 )
          {
            pObj = *(uint32_t *)(v5 + 196);
            if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 724))(pObj) == 0 )
            {
              v18 = *(uint32_t *)(v5 + 196);
              sub_487F60(&v18);
            }
          }
        }
        v19 = -1;
      }
      *((uint8_t *)this + 8853) = 0;
      *((uint8_t *)this + 8854) = 0;
      LOBYTE(pThis_8A2) = sub_698F90((int)(this + 2210), *(this + 2218), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
  }
  return pThis_8A2;
}



// 参数打包+时钟门 AI（sub_431230+sub_699000）
// ------------------------------------------------------------
// 0x5D56A0 sub_5D56A0 —— 随机段状态选择（24/25 号, 时钟门）
// ·sub_5D2470 尾段后 2212+2211 时钟逾或未初始化时：vt+308 为 1 则 rand%3 经 ·sub_431230
// 打包，按 2210 槽 1/2 选 24 号状态否则 25 号状态（vt+560+vt+564），
// 再以 2213 刷新间隔重排 2211/2212 双时钟。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5D56A0(uint32_t *this)
{
  int fld_e2212; // edi
  unsigned int result; // eax
  int fld_e2210; // eax
  uint8_t v5[4]; // [esp+Ch] [ebp-20h] BYREF
  void *Block; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-18h]
  int v8; // [esp+18h] [ebp-14h]
  int nRand; // [esp+1Ch] [ebp-10h] BYREF
  int v10; // [esp+28h] [ebp-4h]

  sub_5D2470((int)this);
  fld_e2212 = *(this + 2212);
  result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
  if ( fld_e2212 + *(this + 2211) < result || fld_e2212 == 0 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) == 1 )
    {
      Block = nullptr;
      v7 = 0;
      v8 = 0;
      v10 = 0;
      nRand = rand() % 3;
      sub_431230((int)v5, &nRand);
      fld_e2210 = *(this + 2210);
      if ( fld_e2210 == 2 || fld_e2210 == 1 )
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 24, v5, 2, 0);
      else
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *, int, uint32_t))(*this + 560))(this, 25, v5, 2, 0);
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 564))(this);
      v10 = -1;
      if ( Block != nullptr )
        j__free(Block);
      Block = nullptr;
      v7 = 0;
      v8 = 0;
    }
    *(this + 2211) = *(this + 2213);
    result = sub_699000((int)(this + 9));  // 【clock_now(clk)】
    *(this + 2212) = result;
  }
  return result;
}



// 参数打包+RTTI AI（sub_431230+cast）
// ------------------------------------------------------------
// 0x5D57B0 sub_5D57B0 —— 军团同袍点名（20 号状态 + 坐标双参）
// vt+308 为 1 时遍历 this+29 子表：vt+40(obj,529) 过滤、RTTI 到 IRDMonster 且 vt+340==704、
// vt+568（受击态）!= 20、1813 槽非空者，取 1813 对象 vt+48/vt+52 双坐标经 ·sub_431230 打包，
// 对同袍 vt+560(20, ...) 转移并 ·sub_5E5260 释放包。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D57B0(uint32_t *this)
{
  int result; // eax
  unsigned int i; // ebx
  int fld_e29; // ecx
  int v5; // edx
  int v6; // edx
  int pObj2; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int v10; // eax
  int pObj; // esi
  int fld_e1813; // ecx
  void *pBuf[4]; // [esp+4h] [ebp-20h] BYREF
  int fld_e18132; // [esp+14h] [ebp-10h] BYREF
  int v15; // [esp+20h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    for ( i = 0; ; ++i )
    {
      fld_e29 = *(this + 29);
      v5 = *(uint32_t *)(fld_e29 + 8);
      result = v5 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v5) >> 2 : 0;
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
          v10 = *(uint32_t *)(v9 + 4 * i);
        else
          v10 = 0;
        pObj = __RTDynamicCast(v10, 0, &CNRDObject `RTTI Type Descriptor', &IRDMonster `RTTI Type Descriptor', 0);
        if ( pObj != 0
          && *(uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 340))(pObj) == 704
          && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 568))(pObj) != 20
          && *(this + 1813) != 0 )
        {
          memset(&pBuf[1], 0, 12);
          fld_e1813 = *(this + 1813);
          v15 = 0;
          fld_e18132 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 48))(fld_e1813);
          sub_431230((int)pBuf, &fld_e18132);
          fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 52))(*(this + 1813));
          sub_431230((int)pBuf, &fld_e18132);
          (*(void (/*thiscall*/ **)(int, int, void **, uint32_t, uint32_t))(*(uint32_t *)pObj + 560))(pObj, 20, pBuf, 0, 0);
          v15 = -1;
          sub_5E5260(pBuf);
        }
      }
    }
  }
  return result;
}



// 破碎粒子：引用 Particle/ExpellerBrokenParts.ptl（24L）
// ------------------------------------------------------------
// 0x5D5920 sub_5D5920 —— 破碎颗粒对象构造（ExpellerBrokenParts.ptl）
// new 0x12C 后按 96 槽长短路取 364 或 +91 字符串，·sub_4C3640 构造颗粒对象并以 this 为宿主，
// 结果写 2166 槽（分配失败则 0）。
// ------------------------------------------------------------
int /*thiscall*/ sub_5D5920(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax

  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      result = sub_4C3640(this + 91, "Particle/ExpellerBrokenParts.ptl", this);
    else
      result = sub_4C3640(*(this + 91), "Particle/ExpellerBrokenParts.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(this + 2166) = result;
  return result;
}



// 复合门（this+200/568/8601/8603/8669 —— 最后受击时刻联动）
// ------------------------------------------------------------
// 0x5D59B0 sub_5D59B0 —— 军团同袍联动帧（主帧包装）
// 姿态 8 时按 7028 帧位 0/1 走 vt+1332 收招；==2 且 vt+200 状态 +148>=4、vt+568 != 20 时
// 调 ·0x5D57B0 同袍点名。尾段 ·sub_5CF180 + 8669/8603/8601 三条件走 vt+1344（与 ·0x5D0070 同构）。
// ------------------------------------------------------------
char /*thiscall*/ sub_5D59B0(int this)
{
  int pThis_348; // eax

  if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this) == 8 )
  {
    if ( sub_41A5E0(this + 7028) == 0 || sub_41A5E0(this + 7028) == 1 )
    {
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)this + 1332))(this);
    }
    else if ( sub_41A5E0(this + 7028) == 2
           && *(int *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 200))(this) + 148) >= 4
           && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 568))(this) != 20 )
    {
      sub_5D57B0((uint32_t *)this);
    }
  }
  LOBYTE(pThis_348) = sub_5CF180((uint32_t *)this);
  if ( *(uint8_t *)(this + 8669) == 1 )
  {
    LOBYTE(pThis_348) = *(uint8_t *)(this + 8603);
    if ( (uint8_t)pThis_348 == 0 && *(uint8_t *)(this + 8601) == 1 )
    {
      pThis_348 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 840))(this);
      if ( pThis_348 == 0 )
        LOBYTE(pThis_348) = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 1344))(this);
    }
  }
  return pThis_348;
}



// RTTI cast 大型 AI（100L）
// ------------------------------------------------------------
// 0x5D5A60 sub_5D5A60 —— 军团编队召唤（20 号状态, 挑衅人偶出场）
// 8816 槽为 0 时 ·0x5D3640 清编队档位，vt+1172 写 8816，>5 取 vt+384 参数 1 否则参数 0 写 8716。
// ArgList==8 时按事件首参分派：2/3/5 置 8812 门；==4 遍历 vt+700 挂件表 RTTI 找
// CNProvocationDollAura（·sub_517740 取件）vt+76 摘除，随后取 vt+384 参数 4/5、
// new 0x98 + ·sub_591260 构造挑衅人偶并 vt+56 挂装、vt+64 派生 +40 槽写参数 5。
// 尾段 8669 门透传 ·sub_4E33D0 状态收尾。
// ------------------------------------------------------------
int /*userpurge*/ sub_5D5A60@<eax>(int pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int ArgList, float fArg5, int nArg6, int nArg7)
{
  int result; // eax
  int v9; // eax
  unsigned int i; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // eax
  int pObj; // eax
  int v19; // edi
  int v20; // ebx
  uint32_t *pMem; // eax
  uint32_t *v22; // edi
  int nArg32; // [esp-8h] [ebp-1Ch]
  int nArg22; // [esp-4h] [ebp-18h]

  result = *(uint32_t *)(pArg1 + 8816);
  if ( result == 0 )
  {
    sub_5D3640((int *)pArg1);
    v9 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 1172))(pArg1);
    *(uint32_t *)(pArg1 + 8816) = v9;
    if ( v9 > 5 )
      result = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 1);
    else
      result = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pArg1 + 384))(pArg1, 0);
    *(uint32_t *)(pArg1 + 8716) = result;
  }
  if ( ArgList == 8 )
  {
    result = **(uint32_t **)(LODWORD(fArg5) + 4) - 2;
    switch ( **(uint32_t **)(LODWORD(fArg5) + 4) )
    {
      case 2:
      case 3:
      case 5:
        *(uint8_t *)(pArg1 + 8812) = 1;
        break;
      case 4:
        nArg22 = nArg2;
        nArg32 = nArg3;
        for ( i = 0; ; ++i )
        {
          v11 = (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pArg1 + 700))(pArg1, nArg32, nArg22);
          v12 = *(uint32_t *)(v11 + 4);
          v13 = v12 != 0 ? (*(uint32_t *)(v11 + 8) - v12) >> 2 : 0;
          if ( (int)i >= v13 )
            break;
          v14 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 700))(pArg1);
          v15 = *(uint32_t *)(v14 + 4);
          if ( v15 != 0 && i < (*(uint32_t *)(v14 + 8) - v15) >> 2 )
            v16 = *(uint32_t *)(v15 + 4 * i);
          else
            v16 = 0;
          if ( *(uint32_t *)(v16 + 4) == pArg1 )
          {
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pArg1 + 700))(pArg1);
            v17 = sub_517740(i);
            pObj = __RTDynamicCast(
                    v17,
                    0,
                    &IRDAppendage `RTTI Type Descriptor',
                    &CNProvocationDollAura `RTTI Type Descriptor',
                    0);
            if ( pObj != 0 )
            {
              (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 76))(pObj, 0);
              break;
            }
          }
        }
        v19 = (*(int (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 4, nArg32, nArg22);
        v20 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pArg1 + 384))(pArg1, 5);
        pMem = operator new(0x98u);
        if ( pMem != nullptr )
          v22 = sub_591260(pMem, v19, 0);
        else
          v22 = nullptr;
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t))(*v22 + 56))(v22, pArg1, pArg1, 0, 0);
        result = (*(int (/*thiscall*/ **)(uint32_t *))(*v22 + 64))(v22);
        *(uint32_t *)(result + 40) = v20;
        break;
      default:
        break;
    }
  }
  if ( *(uint8_t *)(pArg1 + 8669) == 1 )
    return sub_4E33D0(ArgList, fArg5, nArg6, nArg7);
  return result;
}



// ============================================================
// 【分区 5】锤王崩地与格挡（0x5D5C30-0x5D6590）
// 证据：GuardSpark/GuardCircle.ani 格挡特效（0x5D5C30）、R_HAMMER_KING 语音 +
//       PassiveObject/Common/Animation/{EarthQuake,EarthQuakeRing}.ani + HAMMER_KING_CRASH
//       （0x5D5F10 304L 锤王大地崩全演出）

// 格挡特效：Character/Swordman/Effect/Animation/{GuardSpark,GuardCircle}.ani（104L；
//   研究 20 §3 vt+644 格挡特效族的守卫侧调用, 普通槽位版本）
// ------------------------------------------------------------
// 0x5D5C30 sub_5D5C30 —— 守卫格挡特效（GuardSpark.ani + GuardCircle.ani 双层）
// 642 门或 vt+200(+148==-1 时 ·sub_4938F0 播放驱动) 的 +112 帧位 > 1 时直接返回；
// vt+348 攻击方档位 +12 非 0 或 vt+180 判定命中时 vt+1104 写 13 号行为字；随后 vt+876 双轴速率
// （300/-3000）、vt+888(0,0,1000,1000)、vt+152(4)+·sub_432E50+vt+896 表现提交。
// 按 pArg4 求中点坐标，·sub_42FCB0(228) 校验后 ·sub_431860 装载 GuardSpark.ani 与 GuardCircle.ani，
// 各 new(284) ·sub_44B6C0 构造 CNRDPooledObject、·sub_44E0D0 装配、·sub_45FE80 入池 + vt+148/vt+112 定位。
// ------------------------------------------------------------
uint8_t /*userpurge*/ sub_5D5C30@<al>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3, float *pArg4, int nArg5)
{
  uint8_t result; // al
  unsigned int v7; // edi
  int v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // eax
  int v14; // ebx
  char *v15; // eax
  int pObj; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // ebx
  char *pObj2; // edi
  int v21; // eax
  int v22; // [esp+Ch] [ebp-10h]
  int v23; // [esp+24h] [ebp+8h]
  int v24; // [esp+24h] [ebp+8h]
  int v25; // [esp+24h] [ebp+8h]
  int v26; // [esp+28h] [ebp+Ch]

  result = *((uint8_t *)pDwArg1 + 642);
  if ( result != 0 )
  {
    v7 = pDwArg1[161];
    goto LABEL_7;
  }
  v8 = pDwArg1[30];
  if ( v8 != 0 )
  {
    if ( *(uint32_t *)(v8 + 148) == -1 )
      result = (uint8_t)sub_4938F0(pDwArg1[30]);
    v7 = *(uint32_t *)(v8 + 112);
LABEL_7:
    if ( v7 > 1 )
      return result;
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg3 + 348))(nArg3, nArg2) + 12) != 0
    || (v9 = *pDwArg1,
        v10 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg3 + 120))(nArg3),
        (*(uint8_t (/*thiscall*/ **)(int *, int))(v9 + 180))(pDwArg1, v10) != 0) )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*pDwArg1 + 1104))(pDwArg1, 13);
  }
  (*(void (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int, int))(*pDwArg1 + 876))(pDwArg1, 0, 300, 300, 0, -3000, 1);
  (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*pDwArg1 + 876))(pDwArg1, 1, 0, 0, 0, 0, 0);
  (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*pDwArg1 + 888))(pDwArg1, 0, 0, 1000, 1000);
  v11 = *pDwArg1;
  v12 = (*(int (/*thiscall*/ **)(int *, int))(*pDwArg1 + 152))(pDwArg1, 4);
  v13 = sub_432E50(v12);
  (*(void (/*thiscall*/ **)(int *, int))(v11 + 896))(pDwArg1, v13);
  v23 = (uint64_t)(pArg4[3] * 0.5 + *pArg4);
  v22 = (*(int (/*fastcall*/ **)(int *, uint32_t))(*pDwArg1 + 124))(pDwArg1, (uint64_t)(pArg4[3] * 0.5 + *pArg4) >> 32);
  v26 = (uint64_t)(pArg4[5] * 0.5 + pArg4[2]);
  if ( sub_42FCB0(228) != 0 )
    v14 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardSpark.ani", 1);
  else
    v14 = 0;
  v15 = (char *)sub_44B6C0(284);
  pObj = (int)v15;
  if ( v15 != nullptr )
  {
    sub_44E0D0(v15, v14, 1);
    *(uint32_t *)pObj = &CNRDPooledObject::`vftable';
  }
  else
  {
    v16 = 0;
  }
  sub_45FE80(a1[29], v16, 2, 0, v16, (int)a1, 0);
  v17 = *(uint32_t *)v16;
  v18 = (*(int (/*thiscall*/ **)(int *))(*a1 + 152))(a1);
  (*(void (/*thiscall*/ **)(int, int))(v17 + 148))(v16, v18);
  v19 = v23;
  (*(void (/*thiscall*/ **)(int, int, int, int))(*(uint32_t *)v16 + 112))(v16, v23, v22, v26);
  if ( sub_42FCB0(228) != 0 )
    v24 = sub_431860((char)"Character/Swordman/Effect/Animation/GuardCircle.ani", 1);
  else
    v24 = 0;
  v20 = (char *)sub_44B6C0(284);
  if ( v20 != nullptr )
  {
    sub_44E0D0(v20, v24, 1);
    *(uint32_t *)v20 = &CNRDPooledObject::`vftable';
  }
  else
  {
    pObj2 = nullptr;
  }
  sub_45FE80(pDwArg1[29], (int)pObj2, 2, 0, (int)pObj2, (int)pDwArg1, 0);
  v25 = *(uint32_t *)pObj2;
  v21 = (*(int (/*thiscall*/ **)(int *))(*pDwArg1 + 152))(pDwArg1);
  (*(void (/*thiscall*/ **)(char *, int))(v25 + 148))(pObj2, v21);
  return (*(int (/*thiscall*/ **)(char *, int, int, int))(*(uint32_t *)pObj2 + 112))(pObj2, v19, v22, v26);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D5ED0 sub_5D5ED0 —— 特效动画槽释放（idx2209）
// 释放特效槽 idx2209（·0x5D6590 处装载 ksguard_light.ani 的落点）：·sub_42AF90 解引用 +
// ·sub_657740(句柄, 228) 按 228 池标签归还资源，随后槽置空。
// 【推断】疑属光守卫或四属性守卫析构路径（与 ·0x5D6860 的 Haste 槽释放同构）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D5ED0(void ***this)
{
  int fld_e2209; // esi
  int result; // eax

  fld_e2209 = (int)*(this + 2209);
  if ( fld_e2209 != 0 )
  {
    sub_42AF90(*(this + 2209));
    result = sub_657740(fld_e2209, 228);
  }
  *(this + 2209) = nullptr;
  return result;
}



// 锤王大地崩（304L）：R_HAMMER_KING 语音 + PassiveObject/Common/Animation/
//   {EarthQuake,EarthQuakeRing}.ani 双段震地 + HAMMER_KING_CRASH 播报
//   （this+200/208 + 8853..8936 相位 —— 与 0x5D2710 三连段配套的全演出）
// ------------------------------------------------------------
// 0x5D5F10 sub_5D5F10 —— 锤王大地崩三相位主处理（R_HAMMER_KING 语音 + 双 PassiveObject 震地）
// 相位 A：血比 this+2247 阈值下时钟到点置 this+1905 子对象 +96 阶段旗标；相位 B：姿态非 5 时按 RTTI
// 统计 CNTinSwordManExpeller 数 < this+2245 则 vt+152/376/592 生成 705 号随从并播 R_HAMMER_KING；
// 相位 C：姿态 ==8 且 vt+908 ==3 时生成 EarthQuake/EarthQuakeRing 双段 + ·sub_4E4A50(30312) 散射 +
// ·sub_424120 范围打击 + HAMMER_KING_CRASH 文案并 setState(8)。
// 【推断】this+2241/2243/2246/2249..2251 = WZ 表冷却/时长/半径档（与 ·0x5D6590 vt+384 读同面）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D5F10(int *this)
{
  int v2; // eax
  int v3; // edx
  int fld_e2241; // edi
  int fld_e2216; // edi
  unsigned int v6; // edi
  int v7; // ebx
  int fld_e29; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int fld_e292; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // eax
  int v17; // ebx
  int v18; // edi
  int v19; // eax
  int fld_e2244; // eax
  int fld_e2230; // ebx
  int v22; // eax
  int *v23; // edi
  int v24; // edx
  int v25; // ebx
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int *v30; // edi
  int v31; // edx
  int v32; // ebx
  int v33; // eax
  int v34; // eax
  int v35; // eax
  unsigned int i; // ebx
  int fld_e293; // ecx
  int v38; // edx
  int v39; // eax
  int v40; // edx
  int v41; // eax
  int pObj2; // eax
  int pObj; // edi
  int v44; // edx
  int v45; // ebx
  int nRand; // edx
  int v47; // eax
  int v48; // eax
  int v49; // edx
  int v50; // eax
  int v51; // [esp-18h] [ebp-64h]
  int v52; // [esp-14h] [ebp-60h]
  BOOL nRand2; // [esp-10h] [ebp-5Ch]
  float v54; // [esp-8h] [ebp-54h]
  int v55; // [esp-4h] [ebp-50h]
  float v56; // [esp+Ch] [ebp-40h] BYREF
  float v57; // [esp+10h] [ebp-3Ch]
  int v58; // [esp+14h] [ebp-38h]
  int v59; // [esp+18h] [ebp-34h]
  int v60; // [esp+1Ch] [ebp-30h]
  int v61; // [esp+20h] [ebp-2Ch]
  void *pBuf[4]; // [esp+24h] [ebp-28h] BYREF
  int v63; // [esp+34h] [ebp-18h] BYREF
  int v64; // [esp+38h] [ebp-14h]
  float v65; // [esp+3Ch] [ebp-10h] BYREF
  int v66; // [esp+48h] [ebp-4h]

  sub_5D2470((int)this);
  v2 = (*(int (/*thiscall*/ **)(int *))(*this + 736))(this);
  v3 = *this;
  v64 = v2;
  v65 = (float)v2;
  v64 = (*(int (/*thiscall*/ **)(int *))(v3 + 740))(this);
  if ( v65 / (double)v64 <= *((float *)this + 2247) )
  {
    fld_e2241 = *(this + 2241);
    if ( sub_699000((int)(this + 2235)) >= fld_e2241 )  // 【clock_now(clk)】
      *(uint8_t *)(*(this + 1905) + 96) = 1;
  }
  fld_e2216 = *(this + 2216);
  if ( sub_699000((int)(this + 2210)) >= fld_e2216 && (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) != 5 )  // 【clock_now(clk)】
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
    {
      v6 = 0;
      v7 = 0;
      while ( 1 )
      {
        fld_e29 = *(this + 29);
        v9 = *(uint32_t *)(fld_e29 + 8);
        v10 = v9 != 0 ? (*(uint32_t *)(fld_e29 + 12) - v9) >> 2 : 0;
        if ( (int)v6 >= v10 )
          break;
        v11 = *(uint32_t *)(fld_e29 + 8);
        if ( v11 != 0 && v6 < (*(uint32_t *)(fld_e29 + 12) - v11) >> 2 )
          v12 = *(uint32_t *)(v11 + 4 * v6);
        else
          v12 = 0;
        if ( __RTDynamicCast(
               v12,
               0,
               &CNRDObject `RTTI Type Descriptor',
               &CNTinSwordManExpeller `RTTI Type Descriptor',
               0) != 0 )
          ++v7;
        ++v6;
      }
      if ( v7 < *(this + 2245) )
      {
        fld_e292 = *(uint32_t *)(*(uint32_t *)(*(this + 29) + 132) + 44);
        v14 = *(uint32_t *)(fld_e292 + 364);
        if ( v14 != 0 )
          v15 = (*(uint32_t *)(fld_e292 + 368) - v14) >> 5;
        else
          v15 = 0;
        v64 = 224 * v15;
        v16 = sub_424FF0(fld_e292);
        v17 = *this;
        v18 = 120 * (v16 + 3);
        v19 = (*(int (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 152))(
                this,
                2,
                0,
                0,
                0xFFFF,
                0,
                0,
                0,
                0);
        fld_e2244 = (*(int (/*thiscall*/ **)(int *, uint32_t, int, int, uint32_t, int))(*this + 376))(
                this,
                *(this + 2244),
                v64 / 2,
                v18 / 2,
                0,
                v19);
        (*(void (/*thiscall*/ **)(int *, int, int))(v17 + 592))(this, 705, fld_e2244);
      }
    }
    if ( *((uint8_t *)this + 8936) == 0 )
    {
      sub_4DB130(24, 0);
      (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "R_HAMMER_KING", -1, 0, 0);
      *((uint8_t *)this + 8936) = 1;
    }
    *((uint8_t *)this + 8853) = 0;
    *((uint8_t *)this + 8854) = 0;
    sub_698F90((int)(this + 2210), *(this + 2243), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  fld_e2230 = *(this + 2230);
  if ( sub_699000((int)(this + 2224)) >= fld_e2230 )  // 【clock_now(clk)】
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 308))(this);
    *((uint8_t *)this + 8909) = 0;
    *((uint8_t *)this + 8910) = 0;
    sub_698F90((int)(this + 2224), *(this + 2246), 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  }
  if ( (*(int (/*thiscall*/ **)(int *))(*this + 840))(this) == 8
    && (*(int (/*thiscall*/ **)(int *))(*this + 908))(this) == 3
    && sub_699000((int)(this + 2217)) > *(this + 2232)  // 【clock_now(clk)】
    && *((uint8_t *)this + 8924) == 0 )
  {
    (*(void (/*thiscall*/ **)(int *, uint32_t, uint32_t, int, int))(*this + 888))(this, 0, 0, 1000, 1000);
    v64 = (*(int (/*thiscall*/ **)(int *))(*this + 152))(this) != 0 ? 1 : -1;
    LODWORD(v65) = (uint64_t)((double)v64 * *((float *)this + 2188) * 125.0);
    v63 = sub_44B6C0(284);
    v66 = 0;
    if ( v63 != 0 )
    {
      v64 = sub_42FCB0(228);
      LOBYTE(v66) = 1;
      if ( v64 != 0 )
        v22 = sub_431860((char)"PassiveObject/Common/Animation/EarthQuake.ani", 1);
      else
        v22 = 0;
      LOBYTE(v66) = 0;
      v23 = (int *)sub_44E1F0(v22, 1);
    }
    else
    {
      v23 = nullptr;
    }
    v24 = *v23;
    v66 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(v24 + 72))(v23, 2);
    sub_45FE80(*(this + 29), (int)v23, 2, 0, (int)v23, (int)this, 0);
    v25 = *v23;
    v26 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v27 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v26);
    v28 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v27 - 1);
    (*(void (/*thiscall*/ **)(int *, int))(v25 + 112))(v23, LODWORD(v65) + v28);
    v63 = sub_44B6C0(284);
    v66 = 2;
    if ( v63 != 0 )
    {
      v64 = sub_42FCB0(228);
      LOBYTE(v66) = 3;
      if ( v64 != 0 )
      {
        v29 = sub_431860((char)"PassiveObject/Common/Animation/EarthQuakeRing.ani", 1);
        LOBYTE(v66) = 2;
        v30 = (int *)sub_44E1F0(v29, 1);
      }
      else
      {
        LOBYTE(v66) = 2;
        v30 = (int *)sub_44E1F0(0, 1);
      }
    }
    else
    {
      v30 = nullptr;
    }
    v31 = *v30;
    v66 = -1;
    (*(void (/*thiscall*/ **)(int *, int))(v31 + 72))(v30, 2);
    sub_45FE80(*(this + 29), (int)v30, 2, 0, (int)v30, (int)this, 0);
    v32 = *v30;
    v33 = (*(int (/*thiscall*/ **)(int *))(*this + 128))(this);
    v34 = (*(int (/*thiscall*/ **)(int *, int))(*this + 124))(this, v33);
    v35 = (*(int (/*thiscall*/ **)(int *, int))(*this + 120))(this, v34 - 2);
    (*(void (/*thiscall*/ **)(int *, int))(v32 + 112))(v30, LODWORD(v65) + v35);
    for ( i = 0; ; ++i )
    {
      fld_e293 = *(this + 29);
      v38 = *(uint32_t *)(fld_e293 + 8);
      v64 = i;
      v39 = v38 != 0 ? (*(uint32_t *)(fld_e293 + 12) - v38) >> 2 : 0;
      if ( (int)i >= v39 )
        break;
      v40 = *(uint32_t *)(fld_e293 + 8);
      if ( v40 != 0 && i < (*(uint32_t *)(fld_e293 + 12) - v40) >> 2 )
        v41 = *(uint32_t *)(v40 + 4 * i);
      else
        v41 = 0;
      pObj2 = __RTDynamicCast(v41, 0, &CNRDObject `RTTI Type Descriptor', &IRDActiveObject `RTTI Type Descriptor', 0);
      pObj = pObj2;
      if ( (int *)pObj2 != this
        && pObj2 != 0
        && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 308))(pObj2) == 1
        && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj) <= *(this + 2251) )
      {
        v44 = *(uint32_t *)pObj;
        v65 = 0.0;
        v56 = 0.0;
        v57 = 0.0;
        v58 = 0;
        v59 = 0;
        v60 = 0;
        v61 = 0;
        v45 = (*(int (/*thiscall*/ **)(int))(v44 + 120))(pObj);
        nRand = rand() % 60;
        v47 = *(uint32_t *)pObj;
        v63 = v45 + nRand - 30;
        v56 = (float)v63;
        v48 = (*(int (/*thiscall*/ **)(int))(v47 + 124))(pObj);
        v49 = *(uint32_t *)pObj;
        v63 = v48;
        v58 = 1092616192;
        v57 = (float)v48;
        v59 = 1106247680;
        v60 = 1106247680;
        v61 = 1084227584;
        (*(void (/*thiscall*/ **)(int))(v49 + 44))(pObj);
        v55 = sub_605840(&v65, pObj, &v56, 1);
        v54 = v65;
        nRand2 = rand() % 2 == 0;
        v52 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 128))(pObj);
        v51 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
        v50 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
        sub_4E4A50(this, 30312, 0, v50, v51, v52, nRand2, 0, LODWORD(v54), v55);
        i = v64;
      }
    }
    sub_424120(*(uint32_t **)(*(this + 29) + 132), *(this + 2249), *(this + 2250));
    (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)dword_8F7C04 + 212))(
      dword_8F7C04,
      "HAMMER_KING_CRASH",
      -1,
      0,
      0);
    (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 4));
    *((uint8_t *)this + 8924) = 1;
  }
  if ( *(this + 2233) != 0
    && (*(int (/*thiscall*/ **)(int *))(*this + 200))(this) != 0
    && *(uint8_t *)((*(int (/*thiscall*/ **)(int *))(*this + 200))(this) + 170) == 1
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) == 1 )
  {
    memset(&pBuf[1], 0, 12);
    v66 = 4;
    v63 = 3;
    sub_431230((int)pBuf, &v63);
    (*(void (/*thiscall*/ **)(int *, int, void **, int, uint32_t))(*this + 560))(this, 8, pBuf, 2, 0);
    (*(void (/*thiscall*/ **)(int *))(*this + 564))(this);
    sub_5E5260(pBuf);
  }
}


// ============================================================
// 【分区 6】四属性守卫特效族（ksguard_*）（0x5D6590-0x5D6CF0）
// 证据：equipment/character/common/title/titleanimation/ksguard_{light,wind,ice,protection,
//       flame}.ani 五系守卫特效 + Common/ActiveStatus/Animation/Haste.ani +
//       Particle/TrackingFire.ptl 追踪火 + R_DEFEN_GUARD_{DIE,DMG,ALIVE,AMB} 语音组

// 光守卫特效：ksguard_light.ani（58L；titleanimation 目录复用 —— 光属性守卫）
// ------------------------------------------------------------
// 0x5D6590 sub_5D6590 —— 光守卫参数装载（ksguard_light.ani + vt+384 十一连读）
// 先调 vt+1308 清相位，this+1905 子对象 +64 旗标清 0；再经 vt+384(0..10) 把 WZ 数值表导入
// this+2221..2223（*0.01 转浮点）与 this+2225..2233 整数档，末装载 ksguard_light.ani 到
// 特效槽 idx2209。四属性守卫装载族之一（wind/ice/prot/flame 同面）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6590(float *this)
{
  double pThis_180; // st7
  int v3; // eax
  int v4; // eax
  float v5; // edx
  double v6; // st7
  float v7; // eax
  int v8; // eax
  float v9; // edx
  int pThis_1802; // eax
  float v11; // edx
  int pThis_1803; // eax
  float v13; // edx
  int pThis_1804; // eax
  float v15; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);
  *(uint8_t *)(*((uint32_t *)this + 1905) + 64) = 0;
  pThis_180 = (double)(*(int (/*thiscall*/ **)(float *, uint32_t))(*(uint32_t *)this + 384))(this, 0);
  v3 = *(uint32_t *)this;
  *(this + 2221) = pThis_180 * 0.0099999998;
  v4 = (*(int (/*thiscall*/ **)(float *, int))(v3 + 384))(this, 1);
  v5 = *this;
  *(this + 2222) = (double)v4 * 0.0099999998;
  v6 = (double)(*(int (/*thiscall*/ **)(float *, int))(LODWORD(v5) + 384))(this, 2);
  v7 = *this;
  *(this + 2223) = v6 * 0.0099999998;
  v8 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v7) + 384))(this, 3);
  v9 = *this;
  *((uint32_t *)this + 2225) = v8;
  *((uint32_t *)this + 2226) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v9) + 384))(this, 4);
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 5);
  v11 = *this;
  *((uint32_t *)this + 2227) = pThis_1802;
  *((uint32_t *)this + 2229) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v11) + 384))(this, 6);
  pThis_1803 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);
  v13 = *this;
  *((uint32_t *)this + 2230) = pThis_1803;
  *((uint32_t *)this + 2231) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v13) + 384))(this, 8);
  pThis_1804 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 9);
  v15 = *this;
  *((uint32_t *)this + 2232) = pThis_1804;
  *(this + 2233) = (double)(*(int (/*thiscall*/ **)(float *, int))(LODWORD(v15) + 384))(this, 10) * 0.0099999998;
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_light.ani", 1);
  else
    result = 0;
  *((uint32_t *)this + 2209) = result;
  return result;
}



// 风守卫特效：Common/ActiveStatus/Animation/Haste.ani + ksguard_wind.ani（加速/风）
// ------------------------------------------------------------
// 0x5D6700 sub_5D6700 —— 风守卫参数装载（Haste.ani + ksguard_wind.ani 双载）
// vt+1308 清相位后先取 228 池的 Common/ActiveStatus/Animation/Haste.ani 存 idx2245（加速表现槽，
// 与 ·0x5D6860 释放对偶），再经 vt+384(0..8) 导入 this+2253..2262 档（idx2256/2257 为 *0.01 浮点），
// 末装载 ksguard_wind.ani 到特效槽 idx2209。风属性守卫——速度/追猎主题
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6700(float *this)
{
  int v2; // eax
  int v3; // edx
  int pThis_180; // eax
  int v5; // edx
  int pThis_1802; // eax
  int v7; // edx
  double v8; // st7
  float v9; // eax
  int v10; // eax
  float v11; // edx
  int pThis_1803; // eax
  float v13; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 1308))(this);
  if ( sub_42FCB0(228) != 0 )
    v2 = sub_431860((char)"Common/ActiveStatus/Animation/Haste.ani", 1);
  else
    v2 = 0;
  v3 = *(uint32_t *)this;
  *((uint32_t *)this + 2245) = v2;
  *((uint32_t *)this + 2253) = (*(int (/*thiscall*/ **)(float *, uint32_t))(v3 + 384))(this, 0);
  pThis_180 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 1);
  v5 = *(uint32_t *)this;
  *((uint32_t *)this + 2254) = pThis_180;
  *((uint32_t *)this + 2255) = (*(int (/*thiscall*/ **)(float *, int))(v5 + 384))(this, 2);
  pThis_1802 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 3);
  v7 = *(uint32_t *)this;
  *(this + 2256) = (double)pThis_1802 * 0.0099999998;
  v8 = (double)(*(int (/*thiscall*/ **)(float *, int))(v7 + 384))(this, 4);
  v9 = *this;
  *(this + 2257) = v8 * 0.0099999998;
  v10 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v9) + 384))(this, 5);
  v11 = *this;
  *((uint32_t *)this + 2259) = v10;
  *((uint32_t *)this + 2260) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v11) + 384))(this, 6);
  pThis_1803 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 384))(this, 7);
  v13 = *this;
  *((uint32_t *)this + 2261) = pThis_1803;
  *((uint32_t *)this + 2262) = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v13) + 384))(this, 8);
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_wind.ani", 1);
  else
    result = 0;
  *((uint32_t *)this + 2209) = result;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D6860 sub_5D6860 —— 加速表现槽释放（idx2245）
// —— 与 ·sub_5D5ED0 同构（差异：释放槽 idx2245 —— ·0x5D6700 装载的 Haste.ani 加速表现，
//    风守卫独有；·sub_42AF90 + ·sub_657740(228) 归还后置空）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6860(void ***this)
{
  int fld_e2245; // esi
  int result; // eax

  fld_e2245 = (int)*(this + 2245);
  if ( fld_e2245 != 0 )
  {
    sub_42AF90(*(this + 2245));
    result = sub_657740(fld_e2245, 228);
  }
  *(this + 2245) = nullptr;
  return result;
}



// 冰守卫特效：ksguard_ice.ani（31L）
// ------------------------------------------------------------
// 0x5D68A0 sub_5D68A0 —— 冰守卫参数装载（ksguard_ice.ani + vt+384 五连读）
// vt+1308 清相位后经 vt+384(0..4) 导入 this+2218..2222 档，末装载 ksguard_ice.ani 到特效槽 idx2209。
// 与 ·0x5D6590 同面（差异：档位仅 5 个、无 *0.01 浮点转写 —— 冰守卫参数面较短）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D68A0(uint32_t *this)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  *(this + 2218) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 384))(this, 0);
  v2 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v3 = *this;
  *(this + 2219) = v2;
  *(this + 2220) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v3 + 384))(this, 2);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v5 = *this;
  *(this + 2221) = v4;
  *(this + 2222) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 4);
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_ice.ani", 1);
  else
    result = 0;
  *(this + 2209) = result;
  return result;
}



// 防御守卫语音组：R_DEFEN_GUARD_DIE/DMG/ALIVE/AMB 四件套 + ksguard_protection.ani（60L）
// ------------------------------------------------------------
// 0x5D6960 sub_5D6960 —— 防御守卫参数装载（ksguard_protection.ani + R_DEFEN_GUARD 语音四件套）
// vt+1308 清相位后经 vt+384 分三段导入：this+2213..2215 三连、this+2216/2225/2226/2179 单点、
// this+2219..2222 步长 3 的 12 连读（末段按字节拼装 pThis_8AB[4] 的按位字段）；随后经 ·sub_4015C0
// 写四语音槽 R_DEFEN_GUARD_DIE/DMG/ALIVE/AMB（守卫死亡/受伤/存活/循环环境音，研究 28 语音 TAG 组），
// this+2208 归零并装载 ksguard_protection.ani。守卫系语音最全的一支
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6960(uint32_t *this)
{
  int v2; // edi
  uint32_t *pThis_8A5; // ebx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // ebx
  uint32_t *pThis_8AB; // edi
  int v10; // eax
  int v11; // ecx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  v2 = 0;
  pThis_8A5 = this + 2213;
  do
    *pThis_8A5++ = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v2++);
  while ( v2 < 3 );
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v5 = *this;
  *(this + 2216) = v4;
  *(this + 2225) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 4);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);
  v7 = *this;
  *(this + 2226) = v6;
  *(this + 2179) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 384))(this, 6);
  v8 = 8;
  pThis_8AB = this + 2219;
  do
  {
    *(pThis_8AB - 2) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8 - 1);
    *pThis_8AB = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8);
    v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, v8 + 1);
    v11 = *((uint8_t *)pThis_8AB - 8);
    pThis_8AB[2] = v10;
    pThis_8AB[4] = v11 | ((*(uint8_t *)pThis_8AB | ((v10 | 0xFFFFFF00) << 8)) << 8);
    v8 += 3;
    ++pThis_8AB;
  }
  while ( v8 < 14 );
  sub_4015C0("R_DEFEN_GUARD_DIE", 0x11u);  // 【std::string构造赋值】
  sub_4015C0("R_DEFEN_GUARD_DMG", 0x11u);  // 【std::string构造赋值】
  sub_4015C0("R_DEFEN_GUARD_ALIVE", 0x13u);  // 【std::string构造赋值】
  sub_4015C0("R_DEFEN_GUARD_AMB", 0x11u);  // 【std::string构造赋值】
  *(this + 2208) = 0;
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_protection.ani", 1);
  else
    result = 0;
  *(this + 2209) = result;
  return result;
}



// 火守卫特效：Particle/TrackingFire.ptl 追踪火 + ksguard_flame.ani（79L）
// ------------------------------------------------------------
// 0x5D6AF0 sub_5D6AF0 —— 火守卫参数装载（Particle/TrackingFire.ptl 追踪火 + ksguard_flame.ani）
// vt+1308 清相位后 new 0x12C 并调 ·sub_4C3640 生成 Particle/TrackingFire.ptl 追踪火粒子存 idx2214
// （this+96 小串优化分支），再经 vt+384(0..15) 十六连读导入 this+2218..2234；随后写 this+2188 = 1.0f
// （缩放因子，·0x5D5F10 按朝向复用此值）与 this+2207 = 0，末装载 ksguard_flame.ani。
// 四属性守卫中参数面最长、唯一带粒子发射器的一支
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6AF0(uint32_t *this)
{
  int pThis_5B; // eax
  int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 1308))(this);
  if ( operator new(0x12Cu) != nullptr )
  {
    if ( *(this + 96) < 0x10u )
      pThis_5B = sub_4C3640(this + 91, "Particle/TrackingFire.ptl", this);
    else
      pThis_5B = sub_4C3640(*(this + 91), "Particle/TrackingFire.ptl", this);
  }
  else
  {
    pThis_5B = 0;
  }
  v3 = *this;
  *(this + 2214) = pThis_5B;
  *(this + 2218) = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t))(v3 + 384))(this, 0);
  v4 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 1);
  v5 = *this;
  *(this + 2219) = v4;
  *(this + 2220) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v5 + 384))(this, 2);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 3);
  v7 = *this;
  *(this + 2221) = v6;
  *(this + 2223) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v7 + 384))(this, 4);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 5);
  v9 = *this;
  *(this + 2224) = v8;
  *(this + 2225) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v9 + 384))(this, 6);
  v10 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 7);
  v11 = *this;
  *(this + 2226) = v10;
  *(this + 2227) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v11 + 384))(this, 8);
  v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 9);
  v13 = *this;
  *(this + 2228) = v12;
  *(this + 2229) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v13 + 384))(this, 10);
  v14 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 11);
  v15 = *this;
  *(this + 2230) = v14;
  *(this + 2231) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v15 + 384))(this, 12);
  v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 13);
  v17 = *this;
  *(this + 2232) = v16;
  *(this + 2233) = (*(int (/*thiscall*/ **)(uint32_t *, int))(v17 + 384))(this, 14);
  *(this + 2234) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 384))(this, 15);
  *(this + 2188) = 1065353216;
  *(this + 2207) = 0;
  if ( sub_42FCB0(228) != 0 )
    result = sub_431860((char)"equipment/character/common/title/titleanimation/ksguard_flame.ani", 1);
  else
    result = 0;
  *(this + 2209) = result;
  return result;
}



// ============================================================
// 【分区 7】驱逐者 AMOR 命中与相位字段区（0x5D6CF0-0x5D7F80）
// 证据：AMOR_HIT + R_EXPELLER_ALIVE/R_EXPELLER_AMB_LOOP 语音、this+8840..9012 扩展字段区
//       （与 0x5CF 分区阿莫尔同构）、AMOR_HIT 复现群

// 驱逐者命中+语音：AMOR_HIT + R_EXPELLER_ALIVE + R_EXPELLER_AMB_LOOP（44L；
//   this+8612..8728 相位字段）
// ------------------------------------------------------------
// 0x5D6CF0 sub_5D6CF0 —— CNSoldier 基类构造 + 守卫字段区清零 + 三语音槽（AMOR_HIT/R_EXPELLER_*）
// ·sub_4A4EA0 走基类构造后写 CNSoldier vftable；this+8612..8748 成对清零并铺 off_6C2B88（内嵌
// 子对象 vftable，两处：this+8672/8724 族）与 this+8760/8788 的 15/0 串槽；再调 ·sub_5D51D0
// 守卫字段大复位（8600..8738 全区）经 vt+196 写 0，末经 ·sub_4015C0 写 AMOR_HIT（受击命中回调 TAG）
// 与 R_EXPELLER_ALIVE/AMB_LOOP（驱逐者存活/环境循环语音）。驱逐者六型共用基构造
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6CF0(int this, char ArgList, int nArg3)
{
  sub_4A4EA0(ArgList, nArg3);
  *(uint32_t *)this = &CNSoldier::`vftable';
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8676) = 0;
  *(uint32_t *)(this + 8672) = &off_6C2B88;
  *(uint32_t *)(this + 8680) = 0;
  *(uint8_t *)(this + 8684) = 1;
  *(uint8_t *)(this + 8686) = 0;
  *(uint8_t *)(this + 8685) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8688) = 0;
  *(uint8_t *)(this + 8728) = 0;
  *(uint32_t *)(this + 8724) = &off_6C2B88;
  *(uint32_t *)(this + 8732) = 0;
  *(uint8_t *)(this + 8736) = 1;
  *(uint8_t *)(this + 8738) = 0;
  *(uint8_t *)(this + 8737) = 0;
  *(uint32_t *)(this + 8748) = 0;
  *(uint32_t *)(this + 8744) = 0;
  *(uint32_t *)(this + 8740) = 0;
  *(uint32_t *)(this + 8780) = 15;
  *(uint32_t *)(this + 8776) = 0;
  *(uint8_t *)(this + 8760) = 0;
  *(uint32_t *)(this + 8808) = 15;
  *(uint32_t *)(this + 8804) = 0;
  *(uint8_t *)(this + 8788) = 0;
  sub_5D51D0((char *)this);
  (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 196))(this, 0);
  sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
  sub_4015C0("R_EXPELLER_ALIVE", 0x10u);  // 【std::string构造赋值】
  sub_4015C0("R_EXPELLER_AMB_LOOP", 0x13u);  // 【std::string构造赋值】
  return this;
}



// 相位字段（this+8676/8728/8760/8788）
// ------------------------------------------------------------
// 0x5D6E40 sub_5D6E40 —— 守卫族基类析构（内嵌子对象 + 双串槽 + 帧表释放）
// 写 CNSoldier vftable 后按内嵌序逆序析构：idx2166 接口指针经虚表 +0 自毁、idx2202/2195 两处
// 容量 >=16 的堆串 j__free 并重置 15/0/旗标 0（this+8788/8760），idx2181/2168 换 IObject vftable
// 并清 this+8728/8676，末释放 idx2153 帧/参数表三元组。收尾走 ·sub_4A50F0 基类析构。
// 守卫族与驱逐者族共用（各型析构后缀本函数）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6E40(void *this)
{
  void (/*thiscall*/ ***pThis_876)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNSoldier::`vftable';
  v2 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 2166);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *((uint32_t *)this + 2166) = 0;
  if ( *((uint32_t *)this + 2202) >= 0x10u )
    j__free(*((void **)this + 2197));
  *((uint32_t *)this + 2202) = 15;
  *((uint32_t *)this + 2201) = 0;
  *((uint8_t *)this + 8788) = 0;
  if ( *((uint32_t *)this + 2195) >= 0x10u )
    j__free(*((void **)this + 2190));
  *((uint32_t *)this + 2195) = 15;
  *((uint32_t *)this + 2194) = 0;
  *((uint8_t *)this + 8760) = 0;
  *((uint32_t *)this + 2181) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8728) = 0;
  *((uint32_t *)this + 2168) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8676) = 0;
  if ( *((uint32_t *)this + 2153) != 0 )
    j__free(*((void **)this + 2153));
  *((uint32_t *)this + 2153) = 0;
  *((uint32_t *)this + 2154) = 0;
  *((uint32_t *)this + 2155) = 0;
  return sub_4A50F0(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D6F50 sub_5D6F50 —— 守卫族标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7000 / ·sub_5D7CE0 / ·sub_5D7D10 / ·sub_5D7D40 / ·sub_5D7D70 同构
//    （差异：仅转调 ·sub_5D6E40 —— this-1 无 vftable 重写的最简变体；pszArg2&1 时 j__free）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D6F50(void *Block, char pszArg2)
{
  sub_5D6E40(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D6F80 sub_5D6F80 —— 守卫王族析构（CNKingGuard vftable + 特效槽释放 + 基析构）
// 写 CNKingGuard vftable 后经 ·sub_42AF90 + ·sub_657740(228) 释放 idx2209 特效槽（ksguard_*.ani
// 落点）并置空，收尾走 ·sub_5D6E40 基析构。守卫王/锤王/四属性守卫/驱逐者各型析构的共同尾段
// ------------------------------------------------------------
int /*thiscall*/ sub_5D6F80(void ***this)
{
  void **fld_e2209; // edi

  *this = &CNKingGuard::`vftable';
  fld_e2209 = *(this + 2209);
  if ( fld_e2209 != nullptr )
  {
    sub_42AF90(fld_e2209);
    sub_657740(fld_e2209, 228);
  }
  *(this + 2209) = nullptr;
  return sub_5D6E40(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7000 sub_5D7000 —— 守卫王族标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D6F50 同构（差异：转调 ·sub_5D6F80 —— 带 CNKingGuard vftable 重写的守卫王族版本）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7000(void ***Block, char pszArg2)
{
  sub_5D6F80(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D7030 sub_5D7030 —— CNKingGuard 二段构造（六处置 1 武装 + 破碎初始化 + 外观装载分支）
// 先转调 ·sub_5D6CF0 基构造再写 CNKingGuard vftable，把 idx2203..2208 六处置 1（守卫六件武装/
// 存活旗标），经 ·sub_5D18E0 破碎初始化（粒子 + 双轴尺寸 + 变速因子）后按 pszArg4 分派：
// ==1 取 this+1554 外层 +16 槽的外观资源，否则经 this+1540 与 ·sub_5CF120 走另一条装载路径。
// 守卫王/锤王/四属性守卫全部经此 —— 分支疑为 军团/野外 两种出场形态【推断】
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D7030(uint32_t *this, char ArgList, int nArg3, char pszArg4)
{
  sub_5D6CF0(ArgList, nArg3);
  *this = &CNKingGuard::`vftable';
  *(this + 2203) = 1;
  *(this + 2204) = 1;
  *(this + 2205) = 1;
  *(this + 2206) = 1;
  *(this + 2207) = 1;
  *(this + 2208) = 1;
  *(this + 2209) = 0;
  sub_5D18E0(this);
  if ( pszArg4 == 1 )
  {
    sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));
  }
  else
  {
    sub_4D50A0(*(this + 1540));
    sub_5CF120(this);
  }
  return this;
}



// 驱逐者相位字段 A（this+8840..8881）
// ------------------------------------------------------------
// 0x5D7100 sub_5D7100 —— CNHammerKing 构造（四组内嵌子对象清零 + 基构造 + 参数装载）
// 转调 ·sub_5D7030 基构造后写 CNHammerKing vftable；this+8840..8964 按 28 字节步长铺五组内嵌
// 结构（每组：off_6C2B88 vftable + 12 字节零 + 1/0/0 三旗标，即五条串/列表槽），this+8840 组
// 即守卫王族相位字段 A 面；末调 ·sub_5CF690 参数复位与 ·sub_5D25D0 自动守卫参数装载——注意此处
// v4 未初始化【原样保留】。锤王（R_HAMMER_KING）专属构造
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7100(int this, char ArgList, int nArg3)
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, nArg3, 0);
  *(uint32_t *)this = &CNHammerKing::`vftable';
  *(uint8_t *)(this + 8844) = 0;
  *(uint32_t *)(this + 8840) = &off_6C2B88;
  *(uint32_t *)(this + 8848) = 0;
  *(uint8_t *)(this + 8852) = 1;
  *(uint8_t *)(this + 8854) = 0;
  *(uint8_t *)(this + 8853) = 0;
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint32_t *)(this + 8856) = 0;
  *(uint8_t *)(this + 8872) = 0;
  *(uint32_t *)(this + 8868) = &off_6C2B88;
  *(uint32_t *)(this + 8876) = 0;
  *(uint8_t *)(this + 8880) = 1;
  *(uint8_t *)(this + 8882) = 0;
  *(uint8_t *)(this + 8881) = 0;
  *(uint32_t *)(this + 8892) = 0;
  *(uint32_t *)(this + 8888) = 0;
  *(uint32_t *)(this + 8884) = 0;
  *(uint8_t *)(this + 8900) = 0;
  *(uint32_t *)(this + 8896) = &off_6C2B88;
  *(uint32_t *)(this + 8904) = 0;
  *(uint8_t *)(this + 8908) = 1;
  *(uint8_t *)(this + 8910) = 0;
  *(uint8_t *)(this + 8909) = 0;
  *(uint32_t *)(this + 8920) = 0;
  *(uint32_t *)(this + 8916) = 0;
  *(uint32_t *)(this + 8912) = 0;
  *(uint8_t *)(this + 8944) = 0;
  *(uint32_t *)(this + 8940) = &off_6C2B88;
  *(uint32_t *)(this + 8948) = 0;
  *(uint8_t *)(this + 8952) = 1;
  *(uint8_t *)(this + 8954) = 0;
  *(uint8_t *)(this + 8953) = 0;
  *(uint32_t *)(this + 8964) = 0;
  *(uint32_t *)(this + 8960) = 0;
  *(uint32_t *)(this + 8956) = 0;
  sub_5CF690(this);
  sub_5D25D0(v4);
  return this;
}



// 驱逐者相位字段 B（this+8844/8872/8900/8944）
// ------------------------------------------------------------
// 0x5D7240 sub_5D7240 —— CNHammerKing 析构（四组相位子对象换 IObject vftable + 旗标清 0）
// 写 CNHammerKing vftable 后按 idx2235/2224/2217/2210 四组（对应 this+8944/8900/8872/8844）
// 换 nengine::IObject vftable 并清各自 +24 字节旗标，收尾 ·sub_5D6F80 守卫王族析构。
// 与 ·0x5D7100 构造的相位字段 A 面严格对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7240(void ***this)
{
  *this = &CNHammerKing::`vftable';
  *(this + 2235) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8944) = 0;
  *(this + 2224) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8900) = 0;
  *(this + 2217) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8872) = 0;
  *(this + 2210) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8844) = 0;
  return sub_5D6F80(this);
}



// 驱逐者相位字段 C（this+8852..8876）
// ------------------------------------------------------------
// 0x5D7290 sub_5D7290 —— CNGuardLight 构造（光守卫）
// 转调 ·sub_5D7030（pszArg4=1 军团形态）后写 CNGuardLight vftable；this+8852..8876 铺一组内嵌
// 结构（off_6C2B88 vftable + 零 + 1/0/0 旗标），末调 ·sub_5CF740 参数复位与 ·0x5D6590 光守卫
// 参数装载（ksguard_light.ani + vt+384 十一连读）。守卫格挡族——光属性
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7290(int this, char ArgList, int nArg3)
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, nArg3, 1);
  *(uint32_t *)this = &CNGuardLight::`vftable';
  *(uint8_t *)(this + 8856) = 0;
  *(uint32_t *)(this + 8852) = &off_6C2B88;
  *(uint32_t *)(this + 8860) = 0;
  *(uint8_t *)(this + 8864) = 1;
  *(uint8_t *)(this + 8866) = 0;
  *(uint8_t *)(this + 8865) = 0;
  *(uint32_t *)(this + 8876) = 0;
  *(uint32_t *)(this + 8872) = 0;
  *(uint32_t *)(this + 8868) = 0;
  sub_5CF740(this);
  sub_5D6590(v4);
  return this;
}



// AI 字段访问（this+8856）
// ------------------------------------------------------------
// 0x5D7330 sub_5D7330 —— CNGuardLight 析构（全局光守卫计数减一 + 特效槽清）
// 写 CNGuardLight vftable 后把全局 dword_8F8528 +623 处计数置 0（【推断】光守卫在场/链数清位），
// idx2213 换 IObject vftable 并清 this+8856 旗标，收尾 ·sub_5D6F80。与 ·0x5D7290 构造对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7330(void ***this)
{
  *this = &CNGuardLight::`vftable';
  *((uint32_t *)dword_8F8528 + 623) = 0;
  *(this + 2213) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8856) = 0;
  return sub_5D6F80(this);
}



// 驱逐者相位字段 D（this+8844..8889）
// ------------------------------------------------------------
// 0x5D7360 sub_5D7360 —— CNGuardWind 构造（风守卫）
// 转调 ·sub_5D7030（pszArg4=1 军团形态）后写 CNGuardWind vftable；this+8844..9008 铺七组内嵌结构
// （含 this+8908 = ·sub_4A2D10(this+8904) 的链式切面），相位数与参数面在守卫族中最宽 —— 疑含
// 多段风刃/场地表现槽；末调 ·sub_5CF7F0 参数复位与 ·0x5D6700 风守卫装载（Haste.ani + ksguard_wind）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7360(int this, char ArgList, int nArg3)
{
  float *v4; // ecx

  sub_5D7030((uint32_t *)this, ArgList, nArg3, 1);
  *(uint32_t *)this = &CNGuardWind::`vftable';
  *(uint8_t *)(this + 8848) = 0;
  *(uint32_t *)(this + 8844) = &off_6C2B88;
  *(uint32_t *)(this + 8852) = 0;
  *(uint8_t *)(this + 8856) = 1;
  *(uint8_t *)(this + 8858) = 0;
  *(uint8_t *)(this + 8857) = 0;
  *(uint32_t *)(this + 8868) = 0;
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint8_t *)(this + 8880) = 0;
  *(uint32_t *)(this + 8876) = &off_6C2B88;
  *(uint32_t *)(this + 8884) = 0;
  *(uint8_t *)(this + 8888) = 1;
  *(uint8_t *)(this + 8890) = 0;
  *(uint8_t *)(this + 8889) = 0;
  *(uint32_t *)(this + 8900) = 0;
  *(uint32_t *)(this + 8896) = 0;
  *(uint32_t *)(this + 8892) = 0;
  *(uint32_t *)(this + 8908) = sub_4A2D10(this + 8904);
  *(uint32_t *)(this + 8912) = 0;
  *(uint8_t *)(this + 8920) = 0;
  *(uint32_t *)(this + 8916) = &off_6C2B88;
  *(uint32_t *)(this + 8924) = 0;
  *(uint8_t *)(this + 8928) = 1;
  *(uint8_t *)(this + 8930) = 0;
  *(uint8_t *)(this + 8929) = 0;
  *(uint32_t *)(this + 8940) = 0;
  *(uint32_t *)(this + 8936) = 0;
  *(uint32_t *)(this + 8932) = 0;
  *(uint8_t *)(this + 8948) = 0;
  *(uint32_t *)(this + 8944) = &off_6C2B88;
  *(uint32_t *)(this + 8952) = 0;
  *(uint8_t *)(this + 8956) = 1;
  *(uint8_t *)(this + 8958) = 0;
  *(uint8_t *)(this + 8957) = 0;
  *(uint32_t *)(this + 8968) = 0;
  *(uint32_t *)(this + 8964) = 0;
  *(uint32_t *)(this + 8960) = 0;
  *(uint8_t *)(this + 8988) = 0;
  *(uint32_t *)(this + 8984) = &off_6C2B88;
  *(uint32_t *)(this + 8992) = 0;
  *(uint8_t *)(this + 8996) = 1;
  *(uint8_t *)(this + 8998) = 0;
  *(uint8_t *)(this + 8997) = 0;
  *(uint32_t *)(this + 9008) = 0;
  *(uint32_t *)(this + 9004) = 0;
  *(uint32_t *)(this + 9000) = 0;
  sub_5CF7F0(this);
  sub_5D6700(v4);
  return this;
}



// 驱逐者相位字段 E（this+8844..8988）
// ------------------------------------------------------------
// 0x5D7500 sub_5D7500 —— CNGuardWind 析构（风守卫，含 list 释放 + 基析构）
// 写 CNGuardWind vftable 后经 ·sub_42AF90 + ·sub_657740(228) 释放 this+8980 特效槽；随后
// this+8984/8944/8916/8876/8844 五组换 IObject vftable 并清旗标，this+8904 槽经 ·sub_6569D0
// 释放其节点后 j__free(this+8908) 并置 0，收尾 ·sub_5D6F80。守卫族析构中清理面最宽的一支
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7500(int this)
{
  void **fld_2314; // edi

  *(uint32_t *)this = &CNGuardWind::`vftable';
  v2 = *(void ***)(this + 8980);
  if ( v2 != nullptr )
  {
    sub_42AF90(v2);
    sub_657740(v2, 228);
  }
  *(uint32_t *)(this + 8980) = 0;
  *(uint32_t *)(this + 8984) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8988) = 0;
  *(uint32_t *)(this + 8944) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8948) = 0;
  *(uint32_t *)(this + 8916) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8920) = 0;
  sub_6569D0(this + 8904);
  j__free(*(void **)(this + 8908));
  *(uint32_t *)(this + 8908) = 0;
  *(uint32_t *)(this + 8876) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8880) = 0;
  *(uint32_t *)(this + 8844) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 8848) = 0;
  return sub_5D6F80((void ***)this);
}



// 驱逐者相位字段 F（this+8840..8884）
// ------------------------------------------------------------
// 0x5D75E0 sub_5D75E0 —— CNGuardIce 构造（冰守卫）
// 转调 ·sub_5D7030（pszArg4=1 军团形态）后写 CNGuardIce vftable；this+8840..8888 铺一组内嵌结构
// （off_6C2B88 vftable + 零 + 1/0/0 旗标），末调 ·0x5D68A0 冰守卫装载（ksguard_ice.ani + vt+384
// 五连读）。守卫格挡族——冰属性
// ------------------------------------------------------------
int /*thiscall*/ sub_5D75E0(int this, char ArgList, int nArg3)
{
  sub_5D7030((uint32_t *)this, ArgList, nArg3, 1);
  *(uint32_t *)this = &CNGuardIce::`vftable';
  *(uint8_t *)(this + 8844) = 0;
  *(uint32_t *)(this + 8840) = &off_6C2B88;
  *(uint32_t *)(this + 8848) = 0;
  *(uint8_t *)(this + 8852) = 1;
  *(uint8_t *)(this + 8854) = 0;
  *(uint8_t *)(this + 8853) = 0;
  *(uint32_t *)(this + 8864) = 0;
  *(uint32_t *)(this + 8860) = 0;
  *(uint32_t *)(this + 8856) = 0;
  *(uint8_t *)(this + 8853) = 0;
  *(uint8_t *)(this + 8854) = 0;
  *(uint8_t *)(this + 8868) = 1;
  *(uint32_t *)(this + 8872) = 0;
  *(uint32_t *)(this + 8876) = 0;
  *(uint32_t *)(this + 8880) = 0;
  *(uint32_t *)(this + 8884) = 0;
  *(uint32_t *)(this + 8888) = 0;
  sub_5D68A0((uint32_t *)this);
  return this;
}



// AI 字段访问（this+8844）
// ------------------------------------------------------------
// 0x5D76B0 sub_5D76B0 —— CNGuardIce 析构
// 写 CNGuardIce vftable 后 idx2210 换 IObject vftable、清 this+8844 旗标，收尾 ·sub_5D6F80。
// 与 ·0x5D75E0 构造对偶（冰守卫清理面最简）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D76B0(void ***this)
{
  *this = &CNGuardIce::`vftable';
  *(this + 2210) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8844) = 0;
  return sub_5D6F80(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D76D0 sub_5D76D0 —— CNGuardBlock 构造（重装/格挡守卫）
// 转调 ·sub_5D7030 基构造后写 CNGuardBlock vftable，经 ·sub_5CFAE0 参数复位与 ·0x5D6960 装载 ——
// 即 R_DEFEN_GUARD_DIE/DMG/ALIVE/AMB 语音四件套 + ksguard_protection.ani 防御守卫特效。
// 【推断】CNGuardBlock = 守卫格挡/盾卫分支，语音组取自防御守卫
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D76D0(uint32_t *this, char ArgList, int nArg3)
{
  uint32_t *v4; // ecx

  sub_5D7030(this, ArgList, nArg3, 1);
  *this = &CNGuardBlock::`vftable';
  sub_5CFAE0(this);
  sub_5D6960(v4);
  return this;
}



// AI 字段访问（this+8841）
// ------------------------------------------------------------
// 0x5D7740 sub_5D7740 —— CNGuardFire 构造（火守卫）
// 转调 ·sub_5D7030 基构造后写 CNGuardFire vftable；this+8841 处经 ·sub_41A630 构造 clong 并从
// 该处写回 clong::vftable（this+8841 未按指针对齐 —— 疑为字节内嵌计数/引用对象【推断】），
// 末经 ·sub_5CFCC0 参数复位与 ·0x5D6AF0 火守卫装载（TrackingFire.ptl + ksguard_flame.ani）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D7740(uint32_t *this, char ArgList, int nArg3)
{
  int v4; // edx

  sub_5D7030(this, ArgList, nArg3, 1);
  *this = &CNGuardFire::`vftable';
  sub_41A630((unsigned int)this + 8841);
  *(uint32_t *)((char *)this + 8841) = &clong::`vftable';
  sub_5CFCC0((int)this, v4);
  sub_5D6AF0(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D77C0 sub_5D77C0 —— CNGuardFire 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D6F50 同构（差异：转调 ·sub_5D77F0 —— 火守卫析构；原样保留的零参调用形式）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D77C0(void *Block, char pszArg2)
{
  sub_5D77F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问（this+8841/8856）
// ------------------------------------------------------------
// 0x5D77F0 sub_5D77F0 —— CNGuardFire 析构（clong 子对象析构 + 基析构）
// 写 CNGuardFire vftable 后 this+8856 接口指针经虚表 +0 自毁并置 0，经 ·sub_41A580 析构 this+8841
// 处 clong 子对象，收尾 ·sub_5D6F80。与 ·0x5D7740 构造对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5D77F0(int this)
{
  void (/*thiscall*/ ***pThis_2298)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNGuardFire::`vftable';
  pThis_2298 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8856);
  if ( pThis_2298 != nullptr )
    (**pThis_2298)(pThis_2298, 1);
  *(uint32_t *)(this + 8856) = 0;
  sub_41A580(this + 8841);
  return sub_5D6F80((void ***)this);
}



// AI 字段访问（this+8601）
// ------------------------------------------------------------
// 0x5D7870 sub_5D7870 —— CNAxeExpeller 构造（斧驱逐者）
// 转调 ·sub_5D6CF0 基构造后写 CNAxeExpeller vftable；清 this+8601 与 idx2203/2204 两槽，
// 经 ·sub_5D4E30 装载 AxeExpellerBroken 破碎外观，末取 this+1554 外层 +16 槽外观资源。
// 斧驱逐者（AxeExpeller）专属构造——破碎件表现族
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7870(uint8_t *this, char ArgList, int nArg3)
{
  sub_5D6CF0(ArgList, nArg3);
  *(uint32_t *)this = &CNAxeExpeller::`vftable';
  *(this + 8601) = 0;
  *((uint32_t *)this + 2204) = 0;
  *((uint32_t *)this + 2203) = 0;
  sub_5D4E30(this);
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  return this;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D78F0 sub_5D78F0 —— CNAxeExpeller 析构（idx2204/2203 双槽逆序释放 + 基析构）
// 写 CNAxeExpeller vftable 后按 idx2204 → idx2203 逆序经虚表 +0 自毁两接口槽并置 0
// （对应 ·0x5D7870 的清零点），收尾 ·sub_5D6E40。与斧驱逐者构造严格对偶
// ------------------------------------------------------------
int /*thiscall*/ sub_5D78F0(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e2204)(uint32_t, int); // ecx
  void (/*thiscall*/ ***fld_e2203)(uint32_t, int); // ecx

  *this = &CNAxeExpeller::`vftable';
  fld_e2204 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2204);
  if ( fld_e2204 != nullptr )
    (**fld_e2204)(fld_e2204, 1);
  fld_e2203 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2203);
  *(this + 2204) = 0;
  if ( fld_e2203 != nullptr )
    (**fld_e2203)(fld_e2203, 1);
  *(this + 2203) = 0;
  return sub_5D6E40(this);
}



// 时钟门 AI（sub_699000; this+8600/8812/8829/8837）
// ------------------------------------------------------------
// 0x5D7970 sub_5D7970 —— CNHeavenExpeller 构造（天界驱逐者）
// 转调 ·sub_5D6CF0 基构造后写 CNHeavenExpeller vftable；清 this+8600/8812/8829/8837 相位字节，
// idx2204 = ·sub_699000(this+36) 取时钟基线、idx2205/2206 = 30/0 冷却初值；经 ·sub_5D0DE0 装载
// HeavenExpellerBroken 破碎外观与 this+1554 外层外观，释放 idx2153 三元组后经 ·sub_430C80
// 向该表按序压入 1000/2000 两项（int 容器 push_back 的内联展开）。天界驱逐者专属构造
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7970(void *this, char ArgList, int nArg3)
{
  int pThis_869; // edx
  unsigned int pThis_86A; // ecx
  uint32_t *pThis_86A2; // eax

  sub_5D6CF0(ArgList, nArg3);
  *(uint32_t *)this = &CNHeavenExpeller::`vftable';
  *((uint8_t *)this + 8600) = 0;
  *((uint8_t *)this + 8829) = 0;
  *((uint32_t *)this + 2208) = 0;
  *((uint8_t *)this + 8812) = 0;
  *((uint32_t *)this + 2204) = sub_699000((int)this + 36);
  *((uint32_t *)this + 2206) = 0;
  *((uint32_t *)this + 2205) = 30;
  *((uint8_t *)this + 8837) = 0;
  sub_5D0DE0(this);
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  if ( *((uint32_t *)this + 2153) != 0 )
    j__free(*((void **)this + 2153));
  *((uint32_t *)this + 2153) = 0;
  *((uint32_t *)this + 2154) = 0;
  *((uint32_t *)this + 2155) = 0;
  nArg3 = 1000;
  sub_430C80(*((void **)this + 2154), 1, (int)&nArg3);
  pThis_869 = *((uint32_t *)this + 2153);
  nArg3 = 2000;
  if ( pThis_869 != 0 )
    pThis_86A = (*((uint32_t *)this + 2154) - pThis_869) >> 2;
  else
    pThis_86A = 0;
  if ( pThis_869 != 0 && pThis_86A < (*((uint32_t *)this + 2155) - pThis_869) >> 2 )
  {
    pThis_86A2 = *((uint32_t **)this + 2154);
    *pThis_86A2 = 2000;
    *((uint32_t *)this + 2154) = pThis_86A2 + 1;
  }
  else
  {
    sub_430C80(*((void **)this + 2154), 1, (int)&nArg3);
  }
  return this;
}



// 阿莫尔命中 4：AMOR_HIT 播报（this+8601/8812/8832 相位）
// ------------------------------------------------------------
// 0x5D7AE0 sub_5D7AE0 —— CNLegionExpeller 构造（军团驱逐者）
// 转调 ·sub_5D6CF0 基构造后写 CNLegionExpeller vftable；清 this+8601/8812/8600 与 idx2207/8832；
// ·sub_42A560 取参数存 idx2205/2206（同值双槽，疑为 帧/时长 或 距离/半径 对偶【推断】）；
// 再经 ·sub_4015C0 写 AMOR_HIT 命中 TAG，末 ·sub_5D1160 装载 AxeExpellerBroken 破碎外观与
// this+1554 外层外观，pszArg4==1 时另走 ·sub_5CF120。军团驱逐者专属（vt+40 类型校验 704 = 本型）
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7AE0(uint8_t *this, char ArgList, int nArg3, char pszArg4)
{
  int v5; // eax

  sub_5D6CF0(ArgList, nArg3);
  *(uint32_t *)this = &CNLegionExpeller::`vftable';
  *(this + 8601) = 0;
  *(this + 8812) = 0;
  *(this + 8600) = 0;
  v5 = sub_42A560(this);
  *((uint32_t *)this + 2206) = v5;
  *((uint32_t *)this + 2205) = v5;
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 0;
  sub_4015C0("AMOR_HIT", 8u);  // 【std::string构造赋值】
  sub_5D1160(this);
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  if ( pszArg4 == 1 )
    sub_5CF120(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7BA0 sub_5D7BA0 —— CNLegionExpeller 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7E00 同构（差异：转调 ·sub_5D7BD0 —— 军团驱逐者析构）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7BA0(void *Block, char pszArg2)
{
  sub_5D7BD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7BD0 sub_5D7BD0 —— CNLegionExpeller 析构（idx2207 槽释放 + 基析构）
// 写 CNLegionExpeller vftable 后 idx2207 接口指针经虚表 +0 自毁并置 0（·0x5D7AE0 置 0 的落点），
// 收尾 ·sub_5D6E40 基析构
// ------------------------------------------------------------
int /*thiscall*/ sub_5D7BD0(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e2207)(uint32_t, int); // ecx

  *this = &CNLegionExpeller::`vftable';
  fld_e2207 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2207);
  if ( fld_e2207 != nullptr )
    (**fld_e2207)(fld_e2207, 1);
  *(this + 2207) = 0;
  return sub_5D6E40(this);
}



// AI 相位字段（this+8600/8812/8820）
// ------------------------------------------------------------
// 0x5D7C40 sub_5D7C40 —— CNSandorExpeller 构造（沙多/桑多驱逐者）
// 转调 ·sub_5D6CF0 基构造后写 CNSandorExpeller vftable；清 this+8812/8820/8600 与 idx2204，
// 经 ·sub_5D2320 装载 AxeExpellerBroken 2 破碎外观并应用目标帧；pszArg4==1 时走 this+1540 与
// ·sub_5CF120 军团分支，末 ·sub_5D3640 编队档位清位（vt+1172 档位 → 子对象 +3x 字段）。
// 沙多驱逐者专属构造
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D7C40(uint8_t *this, char ArgList, int nArg3, char pszArg4)
{
  sub_5D6CF0(ArgList, nArg3);
  *(uint32_t *)this = &CNSandorExpeller::`vftable';
  *(this + 8812) = 0;
  *((uint32_t *)this + 2204) = 0;
  *(this + 8820) = 0;
  *(this + 8600) = 0;
  sub_5D2320(this);
  if ( pszArg4 == 1 )
  {
    sub_4D50A0(*((uint32_t *)this + 1540));
    sub_5CF120(this);
  }
  sub_5D3640(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7CE0 sub_5D7CE0 —— CNHammerKing 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7D10 同构（差异：转调 ·sub_5D7240 —— 锤王析构）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7CE0(void ***Block, char pszArg2)
{
  sub_5D7240(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D10 sub_5D7D10 —— CNGuardLight 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7D70 同构（差异：转调 ·sub_5D7330 —— 光守卫析构）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7D10(void ***Block, char pszArg2)
{
  sub_5D7330(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D40 sub_5D7D40 —— CNGuardWind 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7D70 同构（差异：转调 ·sub_5D7500 —— 风守卫析构）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7D40(void *Block, char pszArg2)
{
  sub_5D7500((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7D70 sub_5D7D70 —— CNGuardIce 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7DD0 同构（差异：转调 ·sub_5D76B0 —— 冰守卫析构）
// ------------------------------------------------------------
void ***/*thiscall*/ sub_5D7D70(void ***Block, char pszArg2)
{
  sub_5D76B0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7DA0 sub_5D7DA0 —— 守卫格挡族标量删除器（析构 + 可选 free）
// 转调 ·sub_5D7730 后按 pszArg2&1 释放。与 ·sub_5D7D70 同构（差异：被调析构为 ·sub_5D7730）。
// 【推断】·sub_5D7730 紧邻 ·0x5D76D0 CNGuardBlock 构造之后，当为该型析构 —— 本条属重装/格挡守卫
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7DA0(void *Block, char pszArg2)
{
  sub_5D7730();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7DD0 sub_5D7DD0 —— CNAxeExpeller 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7E30 同构（差异：转调 ·sub_5D78F0 —— 斧驱逐者析构）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D7DD0(uint32_t *Block, char pszArg2)
{
  sub_5D78F0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7E00 sub_5D7E00 —— 军团驱逐者族标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7BA0 同构（差异：转调 ·sub_5D7AD0 —— 本条为该型析构的近邻定义；
//    【推断】疑为 ·sub_5D7AE0 CNLegionExpeller 析构别名）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7E00(void *Block, char pszArg2)
{
  sub_5D7AD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D7E30 sub_5D7E30 —— CNSandorExpeller 标量删除器（析构 + 可选 free）
// —— 与 ·sub_5D7DD0 同构（差异：转调 ·sub_5D7CD0 —— 本条为沙多驱逐者析构的近邻定义；
//    【推断】疑为 ·sub_5D7C40 CNSandorExpeller 析构别名）
// ------------------------------------------------------------
void */*thiscall*/ sub_5D7E30(void *Block, char pszArg2)
{
  sub_5D7CD0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D7E60 sub_5D7E60 —— CNRDEquipment 构造（.equ 外观对象 —— 驱逐者八型外观装载的公共工厂）
// ·sub_485CC0 基构造后写 CNRDEquipment vftable；this+148 与 this+212 分别经 ·sub_4B3BE0 /
// ·sub_437E70 构造两子结构，this+1160 经 ·sub_4E9A50 初始化；this+1224..1332 铺五组内嵌槽
// （off_6C2B88 + 12 零 + 1/0/0）并对 idx318 经 ·sub_41BFE0(this+1272, szPassword) 做串赋值
// （.equ 加密口令槽【推断】）；末 ·sub_4E9D70(this) + ·sub_4EE580(Block, nArg3, nArg4, nArg5) 完成
// .equ 文件装载。·0x5D7F80/0x5D8040/0x5D8120/0x5D8230/0x5D82C0 全部经此 new 0x544 字节成件
// ------------------------------------------------------------
char */*thiscall*/ sub_5D7E60(char *this, void *Block, int nArg3, int nArg4, int nArg5)
{
  sub_485CC0();
  *(uint32_t *)this = &CNRDEquipment::`vftable';
  sub_4B3BE0(this + 148);
  sub_437E70(this + 212);
  sub_4E9A50(this + 1160);
  *(this + 1224) = 0;
  *((uint32_t *)this + 305) = &off_6C2B88;
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
  sub_4EE580(Block, nArg3, nArg4, nArg5);
  return this;
}



// ============================================================
// 【分区 8】驱逐者八型外观装载（0x5D7F80-0x5D89A0）
// 证据：Monster/Soldier/{HammerKing 七件, Expeller 六件, AxeExpeller 六件, HeavenExpeller 七件,
//       AxionExpeller 七件, TSMExpeller 六件, LegionExpeller 六件, SandorExpeller 六件}.equ +
//       Monster/Soldier/Guard/GuardHandle.equ 双载入 + Particle/ExpellerBrokenParts.ptl

// 锤王装载：Monster/Soldier/HammerKing/{Cloak1,Cloak2,Leg,Head1,Head2,Shield,Weapon}.equ
//   七件（46L）
// ------------------------------------------------------------
// 0x5D7F80 sub_5D7F80 —— 锤王七件外观装载（Monster/Soldier/HammerKing 七件 .equ 查表循环）
// v6[0..6] 为 Cloak1/Cloak2/Leg/Head1/Head2/Shield/Weapon 七条 .equ 路径的字符串表，循环 8 次
// （第 8 项为 0 空转）；每非空项 new 0x544 并 ·sub_4BA9E0(pMem, 路径, 0) 挂装，结果按序写入
// this+2156 起的指针槽（this+8624..+8652）。锤王外观组装入口
// ------------------------------------------------------------
void /*thiscall*/ sub_5D7F80(char **this)
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/HammerKing/Cloak1.equ";
  v6[1] = "Monster/Soldier/HammerKing/Cloak2.equ";
  v6[2] = "Monster/Soldier/HammerKing/Leg.equ";
  v6[3] = "Monster/Soldier/HammerKing/Head1.equ";
  v6[4] = "Monster/Soldier/HammerKing/Head2.equ";
  v6[5] = "Monster/Soldier/HammerKing/Shield.equ";
  v6[6] = "Monster/Soldier/HammerKing/Weapon.equ";
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )
        v5 = sub_4BA9E0(pMem, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *pThis_86C = v5;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( v1 < 8 );
}



// 守卫装载：Monster/Soldier/Guard/GuardHandle.equ（45L；守卫持械）
// ------------------------------------------------------------
// 0x5D8040 sub_5D8040 —— 守卫外观装载（off_795608 路径表 + GuardHandle.equ 单件）
// 遍历全局路径表 off_795608 直至 &CNFireBomb RTTI 边界（表以 RTTI 描述符地址收尾，非空项 new
// ·0x544 字节后经 ·sub_5D7E60(..., 0, 0, 3) 成件，写入 this+2156 起槽），随后单独 new 0x544 装载
// Monster/Soldier/Guard/GuardHandle.equ(..., 0,0,0) 存 this+2162（守卫持械/手柄件）。
// 与 ·0x5D8120 同构（差异：本型仅 1 件 GuardHandle —— 存 this+2162）
// ------------------------------------------------------------
char */*thiscall*/ sub_5D8040(char **this)
{
  void **v1; // esi
  char **pThis_86C; // edi
  char *pMem; // eax
  char *v4; // eax
  char *pMem2; // eax
  char *result; // eax

  v1 = (void **)off_795608;
  pThis_86C = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      if ( pMem != nullptr )
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 3);
      else
        v4 = nullptr;
      *pThis_86C = v4;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
  {
    result = sub_5D7E60(pMem2, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);
    *(this + 2162) = result;
  }
  else
  {
    *(this + 2162) = nullptr;
    return nullptr;
  }
  return result;
}



// 守卫装载 2：Monster/Soldier/Guard/GuardHandle.equ（48L）
// ------------------------------------------------------------
// 0x5D8120 sub_5D8120 —— 守卫外观装载 2（off_795608 路径表 + GuardHandle.equ 双件）
// —— 与 ·sub_5D8040 同构（差异：GuardHandle.equ 装载两次，分别存 this+2162 与 this+2163；
//    off_795608 遍历段沿用 nArg5=4 而非 3 —— 疑为双手持械/双件挂点【推断】）
// ------------------------------------------------------------
char */*thiscall*/ sub_5D8120(char **this)
{
  void **v1; // esi
  char **pThis_86C; // edi
  char *pMem; // eax
  char *v4; // eax
  char *pMem2; // eax
  char *v6; // eax
  char *pMem3; // eax
  char *result; // eax

  v1 = (void **)off_795608;
  pThis_86C = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      if ( pMem != nullptr )
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 4);
      else
        v4 = nullptr;
      *pThis_86C = v4;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
  pMem2 = (char *)operator new(0x544u);
  if ( pMem2 != nullptr )
    v6 = sub_5D7E60(pMem2, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);
  else
    v6 = nullptr;
  *(this + 2162) = v6;
  pMem3 = (char *)operator new(0x544u);
  if ( pMem3 != nullptr )
    result = sub_5D7E60(pMem3, "Monster/Soldier/Guard/GuardHandle.equ", 0, 0, 0);
  else
    result = nullptr;
  *(this + 2163) = result;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8230 sub_5D8230 —— 外观装载表 e1 型（off_795608 路径表 + 变体号 1）
// 与 ·sub_5D8040 同构（差异：off_795608 逐项经 ·sub_5D7E60 变体号 1 成件，无后续单件补装）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8230(char **this)
{
  void **v1; // esi
  char **pThis_86C; // edi
  char *pMem; // eax
  char *v4; // eax

  v1 = (void **)off_795608;
  pThis_86C = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      if ( pMem != nullptr )
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 1);
      else
        v4 = nullptr;
      *pThis_86C = v4;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D82C0 sub_5D82C0 —— 外观装载表 e2 型（off_795608 路径表 + 变体号 2）
// 与 ·sub_5D8230 同构（差异：变体号 2；对应 Expeller 族 ·sub_5D7E60 第 4 实参 = 2）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D82C0(char **this)
{
  void **v1; // esi
  char **pThis_86C; // edi
  char *pMem; // eax
  char *v4; // eax

  v1 = (void **)off_795608;
  pThis_86C = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      if ( pMem != nullptr )
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 2);
      else
        v4 = nullptr;
      *pThis_86C = v4;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8350 sub_5D8350 —— 外观装载表 e0 型（off_795608 路径表 + 变体号 0）
// 与 ·sub_5D8230 同构（差异：变体号回 0；三件套 e0/e1/e2 供 0x5D 段各型构造选用【推断】）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8350(char **this)
{
  void **v1; // esi
  char **pThis_86C; // edi
  char *pMem; // eax
  char *v4; // eax

  v1 = (void **)off_795608;
  pThis_86C = this + 2156;
  do
  {
    if ( *v1 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      if ( pMem != nullptr )
        v4 = sub_5D7E60(pMem, *v1, 0, 0, 0);
      else
        v4 = nullptr;
      *pThis_86C = v4;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( (int)v1 < (int)&CNFireBomb `RTTI Type Descriptor' );
}



// 驱逐者装载：Monster/Soldier/Expeller/{Leg,Head,RightArm,LeftArm,HeadEnd,Glow}.equ 六件
// ------------------------------------------------------------
// 0x5D83E0 sub_5D83E0 —— 驱逐者外观装载：Expeller 六件套（Leg/Head/RArm/LArm/HeadEnd/Glow）
// 固定路径串表循环 new ·0x544 后经 ·sub_4BA9E0 成件，依序写入 this+2156 起的 8 槽
// ------------------------------------------------------------
void /*thiscall*/ sub_5D83E0(char **this)
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/Expeller/ExpellerLeg.equ";
  v6[1] = "Monster/Soldier/Expeller/ExpellerHead.equ";
  v6[2] = "Monster/Soldier/Expeller/ExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/Expeller/ExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/Expeller/ExpellerHeadEnd.equ";
  v6[5] = "Monster/Soldier/Expeller/ExpellerGlow.equ";
  v6[6] = 0;
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )
        v5 = sub_4BA9E0(pMem, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *pThis_86C = v5;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( v1 < 8 );
}



// 斧驱逐者装载：Monster/Soldier/AxeExpeller/ 六件套
// ------------------------------------------------------------
// 0x5D8490 sub_5D8490 —— AxeExpeller 外观装载：Monster/Soldier/AxeExpeller 六件套
// 与 ·sub_5D83E0 同构（差异：仅路径前缀为 AxeExpeller 系列）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8490(char **this)
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/AxeExpeller/AxeExpellerLeg.equ";
  v6[1] = "Monster/Soldier/AxeExpeller/AxeExpellerHead.equ";
  v6[2] = "Monster/Soldier/AxeExpeller/AxeExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/AxeExpeller/AxeExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/AxeExpeller/AxeExpellerHeadEnd.equ";
  v6[5] = "Monster/Soldier/AxeExpeller/AxeExpellerGlow.equ";
  v6[6] = 0;
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )
        v5 = sub_4BA9E0(pMem, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *pThis_86C = v5;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( v1 < 8 );
}



// 天界驱逐者装载：Monster/Soldier/HeavenExpeller/ 七件套（含 LeftArmHandle）
// ------------------------------------------------------------
// 0x5D8540 sub_5D8540 —— HeavenExpeller 外观装载：天界驱逐者七件套（Leg/Head/双边臂/LeftArmHandle/HeadEnd/Glow）
// 与 ·sub_5D83E0 同构（差异：多 1 件 LeftArmHandle 挂件 —— 表项序 4）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8540(char **this)
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeg.equ";
  v6[1] = "Monster/Soldier/HeavenExpeller/HeavenExpellerHead.equ";
  v6[2] = "Monster/Soldier/HeavenExpeller/HeavenExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/HeavenExpeller/HeavenExpellerLeftArmHandle.equ";
  v6[5] = "Monster/Soldier/HeavenExpeller/HeavenExpellerHeadEnd.equ";
  v6[6] = "Monster/Soldier/HeavenExpeller/HeavenExpellerGlow.equ";
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )
        v5 = sub_4BA9E0(pMem, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *pThis_86C = v5;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( v1 < 8 );
}



// 冲击驱逐者装载：Monster/Soldier/AxionExpeller/ 七件套（含 LeftArmHandle）
// ------------------------------------------------------------
// 0x5D8600 sub_5D8600 —— AxionExpeller 外观装载：冲击驱逐者七件套（含 LeftArmHandle 挂件）
// 与 ·sub_5D83E0 同构（差异：路径前缀 AxionExpeller；表项序 4 = LeftArmHandle）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8600(char **this)
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/AxionExpeller/AxionExpellerLeg.equ";
  v6[1] = "Monster/Soldier/AxionExpeller/AxionExpellerHead.equ";
  v6[2] = "Monster/Soldier/AxionExpeller/AxionExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/AxionExpeller/AxionExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/AxionExpeller/AxionExpellerLeftArmHandle.equ";
  v6[5] = "Monster/Soldier/AxionExpeller/AxionExpellerHeadEnd.equ";
  v6[6] = "Monster/Soldier/AxionExpeller/AxionExpellerGlow.equ";
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )
        v5 = sub_4BA9E0(pMem, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *pThis_86C = v5;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( v1 < 8 );
}



// TSM 驱逐者装载：Monster/Soldier/TSMExpeller/ 六件套
// ------------------------------------------------------------
// 0x5D86C0 sub_5D86C0 —— TSMExpeller 外观装载：Monster/Soldier/TSMExpeller 六件套
// 与 ·sub_5D83E0 同构（差异：仅路径前缀为 TSMExpeller 系列）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D86C0(char **this)
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/TSMExpeller/TSMExpellerLeg.equ";
  v6[1] = "Monster/Soldier/TSMExpeller/TSMExpellerHead.equ";
  v6[2] = "Monster/Soldier/TSMExpeller/TSMExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/TSMExpeller/TSMExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/TSMExpeller/TSMExpellerHeadEnd.equ";
  v6[5] = "Monster/Soldier/TSMExpeller/TSMExpellerGlow.equ";
  v6[6] = 0;
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )
        v5 = sub_4BA9E0(pMem, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *pThis_86C = v5;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( v1 < 8 );
}



// 军团驱逐者装载：Monster/Soldier/LegionExpeller/ 六件套
// ------------------------------------------------------------
// 0x5D8770 sub_5D8770 —— LegionExpeller 外观装载：军团驱逐者六件套
// 与 ·sub_5D83E0 同构（差异：仅路径前缀为 LegionExpeller 系列）
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8770(char **this)
{
  int v1; // edi
  char **pThis_86C; // ebx
  void *v3; // esi
  char *pMem; // eax
  char *v5; // eax
  uint32_t v6[9]; // [esp+Ch] [ebp-30h]
  int v7; // [esp+38h] [ebp-4h]

  v1 = 0;
  v6[0] = "Monster/Soldier/LegionExpeller/LegionExpellerLeg.equ";
  v6[1] = "Monster/Soldier/LegionExpeller/LegionExpellerHead.equ";
  v6[2] = "Monster/Soldier/LegionExpeller/LegionExpellerRightArm.equ";
  v6[3] = "Monster/Soldier/LegionExpeller/LegionExpellerLeftArm.equ";
  v6[4] = "Monster/Soldier/LegionExpeller/LegionExpellerHeadEnd.equ";
  v6[5] = "Monster/Soldier/LegionExpeller/LegionExpellerGlow.equ";
  v6[6] = 0;
  v6[7] = 0;
  pThis_86C = this + 2156;
  do
  {
    v3 = (void *)v6[v1];
    if ( v3 != nullptr )
    {
      pMem = (char *)operator new(0x544u);
      v6[8] = pMem;
      v7 = 0;
      if ( pMem != nullptr )
        v5 = sub_4BA9E0(pMem, v3, 0);
      else
        v5 = nullptr;
      v7 = -1;
      *pThis_86C = v5;
    }
    ++v1;
    ++pThis_86C;
  }
  while ( v1 < 8 );
}



// 桑德尔驱逐者装载：Monster/Soldier/SandorExpeller/ 六件套
// ------------------------------------------------------------
// 0x5D8820 sub_5D8820 —— SandorExpeller 外观装载：桑德尔驱逐者六件套（直接表循环 6 项）
// 与 ·sub_5D83E0 同构（差异：循环上下界 6 而非 8，无空串尾项 —— 六件全实）
// ------------------------------------------------------------
char */*thiscall*/ sub_5D8820(char **this)
{
  int v1; // esi
  char **pThis_86C; // edi
  char *pMem; // eax
  char *result; // eax
  uint32_t v5[7]; // [esp+8h] [ebp-28h]
  int v6; // [esp+2Ch] [ebp-4h]

  v5[0] = "Monster/Soldier/SandorExpeller/SandorExpellerLeg.equ";
  v5[1] = "Monster/Soldier/SandorExpeller/SandorExpellerHead.equ";
  v5[2] = "Monster/Soldier/SandorExpeller/SandorExpellerRightArm.equ";
  v5[3] = "Monster/Soldier/SandorExpeller/SandorExpellerLeftArm.equ";
  v5[4] = "Monster/Soldier/SandorExpeller/SandorExpellerHeadEnd.equ";
  v5[5] = "Monster/Soldier/SandorExpeller/SandorExpellerGlow.equ";
  v1 = 0;
  pThis_86C = this + 2156;
  do
  {
    pMem = (char *)operator new(0x544u);
    v5[6] = pMem;
    v6 = 0;
    if ( pMem != nullptr )
      result = sub_4BA9E0(pMem, (void *)v5[v1], 0);
    else
      result = nullptr;
    *pThis_86C = result;
    ++v1;
    ++pThis_86C;
    v6 = -1;
  }
  while ( v1 < 6 );
  return result;
}



// 破碎粒子：引用 Particle/ExpellerBrokenParts.ptl
// ------------------------------------------------------------
// 0x5D88C0 sub_5D88C0 —— CNExpeller 主构造（Expeller 破碎原型）
// 基类 ·sub_5D6CF0 构造后挂 CNExpeller vftable，+2176/2177/2178 相位索引清零(=-1)，
// 经 vftable+1352 装载 Particle/ExpellerBrokenParts.ptl 破碎粒子，再调 ·sub_5D83E0 六件套装载
// 与 ·sub_4D50A0 触发初次刷新；·0x5D89B0/·0x5D8A70 为同族各型变体构造
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D88C0(uint32_t *this, char ArgList, int nArg3)
{
  uint32_t *pThis_5B; // eax

  sub_5D6CF0(ArgList, nArg3);
  *this = &CNExpeller::`vftable';
  *(this + 2176) = -1;
  *(this + 2177) = -1;
  *(this + 2178) = -1;
  if ( *(this + 96) < 0x10u )
    pThis_5B = this + 91;
  else
    pThis_5B = (uint32_t *)*(this + 91);
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t *, const char *))(*this + 1352))(
    this,
    pThis_5B,
    "Particle/ExpellerBrokenParts.ptl");
  sub_5D83E0(this);
  sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8970 sub_5D8970 —— 标量删除器（转调 ·sub_5D89A0 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8970(void *Block, char pszArg2)
{
  sub_5D89A0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ============================================================
// 【分区 9】邪眼 EvilEye（0x5D89A0-0x5DC170）
// 证据：EYE_APPEAR/EYE_SHOT/EYE_WRIGGLE、STONE_LASER_READY/STONE_LASER_FIRE（复用石激光）、
//       BEFORE_THUNDER、EVIL_SHOUT/EVIL_DMG、Monster/Common/Particle/MonsterDieSmoke.ptl +
//       PassiveObject/Monster/EvilEye/Particle/MissileGero{Center,CenterLeft,CenterRight,Left,
//       Right}.ptl 五向泪弹、CHASER_LAUNCH/CHASER_EXPLOSION 追击弹

// AI 字段访问
// ------------------------------------------------------------
// 0x5D89A0 sub_5D89A0 —— CNExpeller 析构（重挂 vftable 后转调 ·sub_5D6E40 守卫族基析构）
// 本函数无字段清理动作 —— 全部释放交由基析构完成（破碎粒子等由基类链处理）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D89A0(void *this)
{
  *(uint32_t *)this = &CNExpeller::`vftable';
  return sub_5D6E40(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D89B0 sub_5D89B0 —— CNAxionExpeller 主构造（冲击驱逐者）
// 基类 ·sub_5D6CF0 后挂 CNAxionExpeller vftable；·sub_5D4340 战损一段（AMOR_HIT + 爆碎粒子）、
// ·sub_5D8600 七件套装载、·sub_4D50A0 刷新，pszArg4==1 时 ·sub_5CF120 补挂默认件【推断】
// 与 ·sub_5D88C0 同族（差异：无破碎粒子 ptl 挂装；装载七件套型）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D89B0(uint32_t *this, char ArgList, int nArg3, char pszArg4)
{
  sub_5D6CF0(ArgList, nArg3);
  *this = &CNAxionExpeller::`vftable';
  sub_5D4340(this);
  sub_5D8600(this);
  sub_4D50A0(*(uint32_t *)(*(this + 1554) + 16));
  if ( pszArg4 == 1 )
    sub_5CF120(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8A30 sub_5D8A30 —— 标量删除器（转调 ·sub_5D8A60 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8A30(void *Block, char pszArg2)
{
  sub_5D8A60();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8A60 sub_5D8A60 —— CNAxionExpeller 析构（重挂 vftable 后转调 ·sub_5D6E40 基析构）
// 本函数无字段清理动作 —— 七件套外观件释放交由基析构链完成
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8A60(void *this)
{
  *(uint32_t *)this = &CNAxionExpeller::`vftable';
  return sub_5D6E40(this);
}



// 相位字段（this+8824/8832/8833/8834）
// ------------------------------------------------------------
// 0x5D8A70 sub_5D8A70 —— CNTinSwordManExpeller 主构造（TSM 驱逐者）
// 基类 ·sub_5D6CF0 后挂 CNTinSwordManExpeller vftable；+8824 相位字节与 +2205/2207/2209..2211
// 计时槽区清零、+8832 置 1（this+2205 挂 ·off_6C2B88 IObject 空 vftable）；·sub_5D4420 战损二段、
// ·sub_5D10A0 驱逐者破碎 + TSM 碎屑双装载、·sub_5D86C0 六件套；pszArg4==1 时 ·sub_5CF120
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_5D8A70(uint8_t *this, char ArgList, int nArg3, char pszArg4)
{
  sub_5D6CF0(ArgList, nArg3);
  *(uint32_t *)this = &CNTinSwordManExpeller::`vftable';
  *(this + 8824) = 0;
  *((uint32_t *)this + 2205) = &off_6C2B88;
  *((uint32_t *)this + 2207) = 0;
  *(this + 8832) = 1;
  *(this + 8834) = 0;
  *(this + 8833) = 0;
  *((uint32_t *)this + 2211) = 0;
  *((uint32_t *)this + 2210) = 0;
  *((uint32_t *)this + 2209) = 0;
  sub_5D4420(this);
  sub_5D10A0(this);
  sub_5D86C0(this);
  sub_4D50A0(*(uint32_t *)(*((uint32_t *)this + 1554) + 16));
  if ( pszArg4 == 1 )
    sub_5CF120(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8B40 sub_5D8B40 —— 标量删除器（转调 ·sub_5D8B70 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
void */*thiscall*/ sub_5D8B40(void *Block, char pszArg2)
{
  sub_5D8B70();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问（this+8824）
// ------------------------------------------------------------
// 0x5D8B70 sub_5D8B70 —— CNTinSwordManExpeller 析构
// 重挂 vftable；this+2213 子对象经其 vftable[0](v, 1) 释放后槽清零，this+2205 回写
// nengine::IObject 空 vftable、+8824 相位字节清零，最后转调 ·sub_5D6E40 基析构
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8B70(uint32_t *this)
{
  void (/*thiscall*/ ***fld_e2213)(uint32_t, int); // ecx

  *this = &CNTinSwordManExpeller::`vftable';
  v2 = (void (/*thiscall*/ ***)(uint32_t, int))*(this + 2213);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *(this + 2213) = 0;
  *(this + 2205) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8824) = 0;
  return sub_5D6E40(this);
}



// AI 字段访问（this+8600/8604）
// ------------------------------------------------------------
// 0x5D8BF0 sub_5D8BF0 —— 相位槽二次清零（this+8600 字节 + this+8604 双字；恒返回 0）
// 与 ·0x5D8DA0 同片清零区 —— 本函数仅覆盖 8600/8604 两槽（窄幅复位变体）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8BF0(int this)
{
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  return 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8C00 sub_5D8C00 —— 架招相位门（·sub_4E7F30(this,300) 非零 → vt+560 setState(14 蓄力架招)）
// 尾调 ·sub_4E1780（激活码轮询），其返回值透传
// ------------------------------------------------------------
char /*thiscall*/ sub_5D8C00(uint32_t *this)
{
  if ( sub_4E7F30(this, 300, 0, 0) != 0 )
    (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 14, 0, 0, 0);
  return sub_4E1780(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8C30 sub_5D8C30 —— 状态 14 联动：帧写入（vt+196 ← *(*(this+1554)+4)）后取 this+28 关联对象
// 归零其 +5 速率槽为 1.0f 并置其 +196 激活位（对象 vt+308 存活判定）【推断】
// ------------------------------------------------------------
void /*thiscall*/ sub_5D8C30(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  uint32_t *fld_e28; // esi

  if ( nArg2 == 14 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*this + 196))(this, *(uint32_t *)(*(this + 1554) + 4));
    fld_e28 = (uint32_t *)*(this + 28);
    if ( *fld_e28 != 0 && (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*fld_e28 + 308))(*fld_e28) != 0 && fld_e28[5] != 1065353216 )
    {
      fld_e28[5] = 1065353216;
      *((uint8_t *)fld_e28 + 196) = 1;
    }
  }
}



// AI 相位字段（this+8600/8624）
// ------------------------------------------------------------
// 0x5D8C80 sub_5D8C80 —— CNBat 主构造（蝙蝠族）
// 基类 ·sub_4A4EA0 后挂 CNBat vftable；+1698..1702 参数字段置 2/2/2/3/4、+8600/+8624 相位字节与
// +2151 槽清零；pszArg4==1 时 +1639 清零、+2151=-1、+8600=1（困难级 + 相位激活【推断】）
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D8C80(uint32_t *this, char ArgList, int nArg3, char pszArg4)
{
  sub_4A4EA0(ArgList, nArg3);
  *(this + 1698) = 2;
  *(this + 1699) = 2;
  *(this + 1700) = 2;
  *this = &CNBat::`vftable';
  *((uint8_t *)this + 8600) = 0;
  *(this + 2151) = 0;
  *(this + 1701) = 3;
  *(this + 1702) = 4;
  *((uint8_t *)this + 8624) = 0;
  if ( pszArg4 == 1 )
  {
    *(this + 1639) = 0;
    *(this + 2151) = -1;
    *((uint8_t *)this + 8600) = 1;
  }
  sub_4D50A0(*(uint32_t *)*(this + 1554));
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D40 sub_5D8D40 —— CNBat 析构（重挂 vftable 后转调 ·sub_4A50F0 基析构）
// 本函数无字段清理动作（蝙蝠族字段由基析构链回收）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8D40(uint32_t *this)
{
  *this = &CNBat::`vftable';
  return sub_4A50F0(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D50 sub_5D8D50 —— 标量删除器（转调 ·sub_5D8D40 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5D8D50(uint32_t *Block, char pszArg2)
{
  sub_5D8D40(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8D80 sub_5D8D80 —— 子对象释放（this+2159 经其 vftable[0](v,1) 析构，槽随后清零）
// 与 ·0x5DA0E0 析构中的同型子对象释放段一致（2159 槽复用形态）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8D80(uint32_t *this)
{
  int (/*thiscall*/ ***fld_e2159)(uint32_t, int); // ecx
  int result; // eax

  fld_e2159 = (int (/*thiscall*/ ***)(uint32_t, int))*(this + 2159);
  if ( fld_e2159 != nullptr )
    result = (**fld_e2159)(fld_e2159, 1);
  *(this + 2159) = 0;
  return result;
}



// AI 相位字段（this+8600/8604/8628）
// ------------------------------------------------------------
// 0x5D8DA0 sub_5D8DA0 —— 邪眼族相位大区清零（+6792..6808 五槽、+8600/+8604、+7144）
// 并把 +8628 置 5（帧索引/相位初值，与 ·0x5DA220 同片字段区呼应）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8DA0(int this)
{
  *(uint32_t *)(this + 6792) = 0;
  *(uint32_t *)(this + 6796) = 0;
  *(uint32_t *)(this + 6800) = 0;
  *(uint32_t *)(this + 6804) = 0;
  *(uint32_t *)(this + 6808) = 0;
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8628) = 5;
  *(uint8_t *)(this + 7144) = 0;
  return 0;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D8DE0 sub_5D8DE0 —— 行为字相位推进（·sub_4E0120 预处理后按 this+1787 行为字分派）
// 0 → vt+1284 相位解除；4/5 → 关联对象 this+1813 非空时 10% 概率经 vt+1104 写入 5/4 进阶；
// 13/14/15 有对象则回写行为字 4；无对象则 vt+1104 写 13（随机进阶档位）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8DE0(int *this)
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
      break;
    case 4:
      if ( *(this + 1813) == 0 )
        goto LABEL_4;
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
        if ( v6 < 10 )
          goto LABEL_11;
      }
      else
      {
LABEL_4:
        result = (*(int (/*thiscall*/ **)(int *, int))(*this + 1104))(this, 13);
      }
      break;
    case 13:
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



// AI 字段访问
// ------------------------------------------------------------
// 0x5D8EC0 sub_5D8EC0 —— 对称随机偏移发生器（对象存活经 vt+308 门；rand%100>=50 取 +rand%n 否则 -rand%n）
// 供 ·0x5D9950 消散抖动用（n=100/50 分别产生三轴散布量）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D8EC0(void *this, int nArg2)
{
  if ( (*(uint8_t (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this) == 0 )
    return 0;
  if ( rand() % 100 >= 50 )
    return rand() % nArg2;
  return -(rand() % nArg2);
}



// 时钟门 AI（sub_699000, 79L）
// ------------------------------------------------------------
// 0x5D8F10 sub_5D8F10 —— 行为字相位机（站姿门 vt+840 + clock_now 超时重掷）
// 行为字 this+1787-4 分派：4 → 80% 闸 + ·sub_4DA6B0 命中包；5/9 → ·sub_4DBDB0 空间栅格重叠检测；
// 13 → 40% 闸 + rand 重掷（命中 nRand==4&&nRand2==4 时超时 300ms，否则 1000ms 写入 this+1818）；
// 关联对象 this+1813 非空双向 vt+124 激活，按 iskill 表 SHIWORD(this+行为字+2092) 概率复位挡位，
// 经 vt+896 写入速率、·sub_5FDFE0 粒子与 vt+1080 收手
// ------------------------------------------------------------
int /*usercall*/ sub_5D8F10@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>)
{
  int result; // eax
  int v4; // eax
  int nRand2; // eax
  int v6; // eax
  int pObj; // ecx
  int v8; // edi
  int nRand; // [esp+4h] [ebp-8h] BYREF
  int nRand22; // [esp+8h] [ebp-4h] BYREF

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    result = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);
    if ( result == 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 184))(pArg1, nArg2);
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 188))(pArg1);
      v4 = pArg1[1787] - 4;
      nRand = 4;
      nRand22 = 4;
      switch ( v4 )
      {
        case 0:
          if ( rand() % 100 >= 80 || (uint8_t)sub_4DA6B0(&nRand) != 0 )
            goto LABEL_7;
          goto LABEL_6;
        case 1:
        case 5:
LABEL_6:
          sub_4DBDB0(&nRand, &nRand22);
          goto LABEL_7;
        case 9:
          if ( rand() % 100 >= 40 )
          {
LABEL_7:
            nRand2 = nRand22;
          }
          else
          {
            if ( (uint8_t)sub_4DA6B0(&nRand) == 0 )
              nRand = rand() % 2;
            nRand2 = rand() % 2 + 2;
            nRand22 = nRand2;
          }
          if ( nRand == 4 && nRand2 == 4 )
            goto LABEL_10;
          v6 = sub_699000((int)(pArg1 + 9)) + 1000;  // 【clock_now(clk)】
          break;
        default:
LABEL_10:
          v6 = sub_699000((int)(pArg1 + 9)) + 300;  // 【clock_now(clk)】
          break;
      }
      pObj = pArg1[1813];
      pArg1[1818] = v6;
      nRand = 4;
      if ( pObj != 0 )
      {
        (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 124))(pObj);
        (*(void (/*thiscall*/ **)(uint32_t *))(*pArg1 + 124))(pArg1);
      }
      v8 = pArg1[1787];
      if ( rand() % 100 < SHIWORD(pArg1[v8 + 2092]) )
        nRand22 = 4;
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 896))(pArg1, nRand);
      sub_5FDFE0(pArg1[1932]);
      return (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1080))(pArg1);
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5D90F0 sub_5D90F0 —— 困难级伤害定位摆动（this+1943==3）
// 非困难级直通 ·sub_4E22E0；困难级经 vt+152 姿态查询取一侧先写入 ±115 偏移执行 ·sub_4E22E0，
// 随后反向写入对称偏移（+115 与 -115 成对，vt+112 位置写入）—— 双向摆动定位【推断】
// ------------------------------------------------------------
int /*userpurge*/ sub_5D90F0@<eax>(uint32_t *pArg1@<ecx>, int nArg2@<edi>, int nArg3, int nArg4, int nArg5, int nArg6, void *Block, int nArg8)
{
  int v9; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // edi
  int v23; // eax
  int v24; // eax
  int v25; // eax

  if ( pArg1[1943] != 3 )
    return sub_4E22E0(nArg3, nArg4, nArg5, nArg6, Block, nArg8);
  v9 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 152))(pArg1, nArg2);
  v10 = *pArg1;
  if ( v9 != 0 )
  {
    v19 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 128))(pArg1);
    v20 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v19);
    v21 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v20);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v10 + 112))(pArg1, v21 + 115);
    sub_4E22E0(nArg3, nArg4, nArg5, nArg6, Block, nArg8);
    v22 = *pArg1;
    v23 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    v24 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v23);
    v25 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v24);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v22 + 112))(pArg1, v25 - 115);
  }
  else
  {
    v11 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 128))(pArg1);
    v12 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v11);
    v13 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v12);
    (*(void (/*thiscall*/ **)(uint32_t *, int))(v10 + 112))(pArg1, v13 - 115);
    sub_4E22E0(nArg3, nArg4, nArg5, nArg6, Block, nArg8);
    v14 = *pArg1;
    v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 128))(pArg1);
    v16 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 124))(pArg1, v15);
    v17 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 120))(pArg1, v16);
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(v14 + 112))(pArg1, v17 + 115);
  }
}



// 邪眼现身：EYE_APPEAR 播报（79L；this+204/208/8685/8686 相位）
// ------------------------------------------------------------
// 0x5D9210 sub_5D9210 —— 邪眼现身相位机（EYE_APPEAR）
// this+2175 相位 0→1：vt+204 帧写入 + 倒计时 5000ms 起、子链 8685/8686 清零、this+2176 计零；
// 相位 1：每 500ms 经 vt+584 发射 30303 弹（伤害 10/4/100）并播报 EYE_APPEAR，clock 达
// this+2174 后切相 2；相位 2：vt+208 帧复位 + vt+560 setState(0) 回待机并置 3
// ------------------------------------------------------------
char /*thiscall*/ sub_5D9210(int *this)
{
  int fld_e2175; // eax
  int fld_e1813; // ecx
  int v4; // edi
  int fld_e18132; // ebx
  int fld_e2174; // edi

  fld_e2175 = *(this + 2175);
  if ( fld_e2175 != 0 )
  {
    if ( fld_e2175 == 1 )
    {
      if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
        && (unsigned int)(sub_699000((int)(this + 2168)) - *(this + 2176)) > 0x1F4 )  // 【clock_now(clk)】
      {
        fld_e1813 = *(this + 1813);
        if ( fld_e1813 != 0 )
        {
          v4 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)fld_e1813 + 120))(fld_e1813);
          fld_e18132 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 124))(*(this + 1813));
          (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 1813) + 128))(*(this + 1813));
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*this + 584))(
            this,
            v4,
            fld_e18132,
            0,
            v4,
            fld_e18132,
            30303,
            10,
            0,
            4,
            100,
            1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "EYE_APPEAR", -1, 0, 0);
        }
        *(this + 2176) = sub_699000((int)(this + 2168));
      }
      fld_e2174 = *(this + 2174);
      fld_e2175 = sub_699000((int)(this + 2168));  // 【clock_now(clk)】
      if ( fld_e2175 >= fld_e2174 )
        *(this + 2175) = 2;
    }
    else if ( fld_e2175 == 2 )
    {
      (*(void (/*thiscall*/ **)(int *, uint32_t))(*this + 208))(this, *(uint32_t *)(*(this + 1554) + 12));
      LOBYTE(fld_e2175) = (*(int (/*thiscall*/ **)(int *, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 0, 0, 0, 0);
      *(this + 2175) = 3;
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*this + 204))(
      this,
      1,
      *(uint32_t *)(*(this + 1554) + 12),
      0,
      0,
      0,
      0);
    *(this + 2175) = 1;
    sub_49C620(3, 1, 5000);
    sub_49C5F0(3, 0, 0, 5000);
    *((uint8_t *)this + 8685) = 0;
    *((uint8_t *)this + 8686) = 0;
    LOBYTE(fld_e2175) = sub_698F90((int)(this + 2168), 5000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    *(this + 2176) = 0;
  }
  return fld_e2175;
}



// 邪眼主技能状态机（295L）：STONE_LASER_READY/EYE_SHOT/EYE_APPEAR/BEFORE_THUNDER/
//   STONE_LASER_FIRE 五段播报（sub_699000 时钟门 —— 石激光/落雷/射击三相【推断】）
// ------------------------------------------------------------
// 0x5D93A0 sub_5D93A0 —— 邪眼主技能状态机（大状态 8/14/17/9 分派）
// 状态 8 按 vt+908 段号：段 1 → vt+580 发射 48029 石激光 + 播报 STONE_LASER_READY；段 2 → 经
// this+2177..2181 五路粒子槽发射 30302 弹（五向泪弹）+ 播报 EYE_SHOT；段 3 → vt+584 发射 30303
// 并播报 EYE_APPEAR + BEFORE_THUNDER；段 0 → 发射 30305；状态 14 → 播报 STONE_LASER_FIRE +
// 发射 30301；状态 17 → 转 ·sub_5D9210 现身相位机；状态 9 → 帧游标复位 + 2000ms 后 setState(5)
// 尾段状态>=14 走 ·sub_4D9360 否则 ·sub_4D93D0，统一 ·sub_4E1780 激活码轮询
// ------------------------------------------------------------
char /*usercall*/ sub_5D93A0@<al>(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int v4; // eax
  int v5; // edx
  uint32_t *v6; // eax
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int64_t v10; // rax
  int v11; // edi
  bool v12; // zf
  int v13; // eax
  int v14; // edx
  int pObj; // ecx
  int v16; // edi
  int v17; // ebx
  int v18; // eax
  int v19; // ebx
  int64_t v20; // rax
  int v21; // edi
  int v22; // edi
  uint32_t *v23; // edi
  int v25; // [esp-2Ch] [ebp-30h]

  v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1);
  v5 = *pArg1;
  if ( v4 == 8 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(v5 + 840))(pArg1) == 17 )
      goto LABEL_6;
    v6 = (uint32_t *)(pArg1[1554] + 12);
  }
  else
  {
    (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v5 + 208))(pArg1, *(uint32_t *)(pArg1[1554] + 4));
    v6 = (uint32_t *)(pArg1[1554] + 20);
  }
  (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 208))(pArg1, *v6);
LABEL_6:
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 8 )
  {
    v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 908))(pArg1);
    v8 = *pArg1;
    if ( v7 == 1 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v8 + 200))(pArg1) + 148) >= 3 && *((uint8_t *)pArg1 + 8600) == 1 )
      {
        v9 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);
        if ( v9 != 0 )
        {
          v11 = sub_425050(*(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44));
          v10 = 1374389535LL * (v11 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));
        }
        else
        {
          v10 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
        }
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t))(*pArg1 + 580))(
          pArg1,
          48029,
          (SHIDWORD(v10) >> 5) + (HIDWORD(v10) >> 31),
          0,
          0,
          85,
          0,
          107,
          v9,
          0);
        *((uint8_t *)pArg1 + 8600) = 0;
        sub_432EA0("STONE_LASER_READY", -1, 0, 0);
      }
      else if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 148) >= 8
             && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 568))(pArg1) != 14 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 14, 0, 0, 0);
      }
    }
    else
    {
      v12 = (*(int (/*thiscall*/ **)(uint32_t *))(v8 + 908))(pArg1) == 2;
      v13 = *pArg1;
      if ( v12 )
      {
        if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v13 + 200))(pArg1) + 148) >= 5 && *((uint8_t *)pArg1 + 8600) == 1 )
        {
          v14 = *pArg1;
          v25 = pArg1[2177];
          *((uint8_t *)pArg1 + 8600) = 0;
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(v14 + 580))(
            pArg1,
            30302,
            0,
            v25,
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
            pArg1,
            30302,
            0,
            pArg1[2178],
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
            pArg1,
            30302,
            0,
            pArg1[2179],
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
            pArg1,
            30302,
            0,
            pArg1[2180],
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
            pArg1,
            30302,
            0,
            pArg1[2181],
            0,
            60,
            0,
            98,
            4,
            0,
            0,
            0);
          (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(pArg1, "EYE_SHOT", -1, 0, 0);
        }
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t *))(v13 + 908))(pArg1) == 3 )
      {
        if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 148) >= 5 && *((uint8_t *)pArg1 + 8600) == 1 )
        {
          pObj = pArg1[1813];
          *((uint8_t *)pArg1 + 8600) = 0;
          if ( pObj != 0 )
          {
            v16 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 120))(pObj);
            v17 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 124))(pArg1[1813]);
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)pArg1[1813] + 128))(pArg1[1813]);
            (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, int, int, int, int, uint32_t, int, int, int, uint32_t, uint32_t))(*pArg1 + 584))(
              pArg1,
              v16,
              v17,
              0,
              v16,
              v17,
              30303,
              10,
              0,
              4,
              100,
              1,
              0,
              0);
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(
              pArg1,
              "EYE_APPEAR",
              -1,
              0,
              0);
            (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pArg1 + 212))(
              pArg1,
              "BEFORE_THUNDER",
              -1,
              0,
              0);
          }
        }
      }
      else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 908))(pArg1) == 0
             && *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 148) >= 5
             && *((uint8_t *)pArg1 + 8600) == 1 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
          pArg1,
          30305,
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
        *((uint8_t *)pArg1 + 8600) = 0;
      }
    }
  }
  else
  {
    v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 14;
    v18 = *pArg1;
    if ( v12 )
    {
      if ( *(int *)((*(int (/*thiscall*/ **)(uint32_t *))(v18 + 200))(pArg1) + 148) >= 0 && *((uint8_t *)pArg1 + 8600) == 1 )
      {
        v19 = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 152))(pArg1, nArg3, nArg2);
        if ( v19 != 0 )
        {
          v21 = sub_425050(*(uint32_t *)(*(uint32_t *)(pArg1[29] + 132) + 44));
          v20 = 1374389535LL * (v21 - (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));
        }
        else
        {
          v20 = 1374389535LL * (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
        }
        v22 = (SHIDWORD(v20) >> 5) + (HIDWORD(v20) >> 31);
        (*(void (/*thiscall*/ **)(uint32_t *, const char *, int))(*pArg1 + 212))(pArg1, "STONE_LASER_FIRE", -1);
        (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, int, uint32_t, int, int, uint32_t, uint32_t, uint32_t))(*pArg1 + 580))(
          pArg1,
          30301,
          v22,
          0,
          0,
          85,
          0,
          107,
          v19,
          0,
          0,
          0);
        *((uint8_t *)pArg1 + 8600) = 0;
      }
      if ( *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) + 170) != 0
        && (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 568))(pArg1) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 0, 0, 0, 0);
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(v18 + 840))(pArg1) == 17 )
    {
      sub_5D9210(pArg1);
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 9 && pArg1[2151] == 1 )
    {
      v23 = (uint32_t *)(pArg1[1554] + 8);
      if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 200))(pArg1) != *v23 )
      {
        sub_4926A0(*(uint32_t *)(pArg1[1554] + 8));
        (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(*pArg1 + 196))(pArg1, *(uint32_t *)(pArg1[1554] + 8));
      }
      if ( (unsigned int)(sub_699000((int)(pArg1 + 9)) - pArg1[2156]) > 0xFA0  // 【clock_now(clk)】
        && (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 308))(pArg1) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t *, uint32_t, uint32_t))(*pArg1 + 560))(pArg1, 5, pArg1 + 2152, 0, 0);
        pArg1[2151] = 2;
      }
    }
  }
  if ( (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) == 8 || (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 840))(pArg1) >= 14 )
  {
    sub_4D9360(pArg1);
    return sub_4E1780(pArg1);
  }
  else
  {
    sub_4D93D0(pArg1);
    return sub_4E1780(pArg1);
  }
}


// 时钟门+插值 AI（sub_699000+sub_4049C0; this+200）
// ------------------------------------------------------------
// 0x5D9950 sub_5D9950 —— 状态 9 消散演出（时钟插值渐隐 + 抖动位移）
// clock_now-this+2156 经 ·sub_4049C0(255..0,1000ms) 换算 alpha 后 ·sub_491690 通道写入（1/5/1）；
// this+2157 计数 >0 时每 300ms 经 ·sub_5D8EC0 三轴抖动 + ·sub_605840 打包 + ·sub_4E4A50 请求
// 42005 效果并递减；计数耗尽后 ·sub_4600B0 双轴写入 + 子链帧游标 ·sub_4924C0 复位（3000ms 槽）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9950(uint32_t *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  unsigned int fld_e2156; // eax
  uint64_t v7; // rax
  int v8; // ebx
  int v9; // eax
  int v10; // edx
  int v11; // ebx
  int v12; // eax
  int v13; // edi
  int v14; // edi
  int v15; // eax
  void *fld_e29; // ecx
  uint32_t *Block2; // edi
  int v19; // [esp-8h] [ebp-50h]
  int v20; // [esp-8h] [ebp-50h]
  int v21; // [esp-4h] [ebp-4Ch]
  float v22; // [esp+Ch] [ebp-3Ch] BYREF
  float v23; // [esp+10h] [ebp-38h]
  float v24; // [esp+14h] [ebp-34h]
  int v25; // [esp+18h] [ebp-30h]
  int v26; // [esp+1Ch] [ebp-2Ch]
  int v27; // [esp+20h] [ebp-28h]
  uint8_t v28[4]; // [esp+24h] [ebp-24h] BYREF
  void *Block; // [esp+28h] [ebp-20h]
  uint32_t *v30; // [esp+2Ch] [ebp-1Ch]
  int v31; // [esp+30h] [ebp-18h]
  int v32; // [esp+34h] [ebp-14h]
  int v33; // [esp+38h] [ebp-10h] BYREF
  int v34; // [esp+44h] [ebp-4h]

  if ( (uint8_t)nArg2 == 0 )
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) == 9 )
    {
      fld_e2156 = sub_699000((int)(this + 9)) - *(this + 2156);  // 【clock_now(clk)】
      if ( fld_e2156 >= 0x3E8 )
        LOBYTE(v7) = 0;
      else
        v7 = (uint64_t)sub_4049C0(255.0, 0.0, fld_e2156, 1000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
      v19 = ((uint8_t)v7 << 24) | 0xFFFFFF;
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
      sub_491690(1, 5, 1, -1, v19, 1);
      if ( (int)*(this + 2157) <= 0 )
      {
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 1 ? -50 : 50;
        v14 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) + v13;
        v15 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + 2159) + 40))(*(this + 2159), v14, v15, 60);
        (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + 2159) + 92))(*(this + 2159), v28);
        fld_e29 = (void *)*(this + 29);
        v34 = 0;
        sub_4600B0(fld_e29, 2, 0, (int)v28);
        Block2 = Block;
        if ( Block != v30 )
        {
          do
          {
            (*(void (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*Block2 + 200))(*Block2);
            *(uint32_t *)(sub_4924C0(0) + 48) = *(this + 2160);
            ++Block2;
          }
          while ( Block2 != v30 );
          Block2 = Block;
        }
        v34 = -1;
        if ( Block2 != nullptr )
          j__free(Block2);
        Block = nullptr;
        v30 = nullptr;
        v31 = 0;
      }
      else if ( (unsigned int)(sub_699000((int)(this + 9)) - *(this + 2158)) > 0x12C )  // 【clock_now(clk)】
      {
        v33 = 0;
        v22 = 0.0;
        v23 = 0.0;
        v24 = 0.0;
        v25 = 0;
        v26 = 0;
        v27 = 0;
        v8 = sub_5D8EC0(this, 100);
        v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
        v10 = *this;
        v32 = v9 + v8;
        v22 = (float)(v9 + v8);
        v32 = (*(int (/*thiscall*/ **)(uint32_t *))(v10 + 124))(this);
        v23 = (float)v32;
        v11 = sub_5D8EC0(this, 50);
        v32 = v11 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this) + 50;
        v24 = (float)v32;
        v21 = sub_605840(&v33, this, &v22, 1);
        v20 = v33;
        v12 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
        sub_4E4A50(this, 42005, 1, 0, 0, 0, v12, 0, v20, v21);
        *(this + 2158) = sub_699000((int)(this + 9));
        --*(this + 2157);
      }
    }
    else if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this) != 9
           && (*(int (/*thiscall*/ **)(uint32_t *))(*this + 736))(this) <= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 200))(this);
      sub_491690(1, 5, 1, -1, -1, 1);
    }
  }
  return sub_4D8F90(nArg2, nArg3, nArg4, nArg5);
}



// 复合门（114L；this+612/616 反应态 + 8600/8657/8658 —— 反应态空闲门样本, 研究 15）
// ------------------------------------------------------------
// 0x5D9BF0 sub_5D9BF0 —— 复合状态门（ArgList 5/8/14/17 分派 + 超时回环）
// 5 → 存活则 this+2151=2；相位 0 时置 1、setState 9 候选、this+2152 槽写入 + 2156/2158 计零；
// 8 → 攻击入场（+8600=1 相位激活，vt+204 帧写入取 1554 双槽择一）；14 → vt+196 帧写 + vt+612(1,1)；
// 17 → 2175/8657/8658 清零 + this+2161 倒计时 30000ms 重挂；状态 0 且 this+2167 到点 → setState(17)
// 循环重挂；状态 14 → vt+612(0,0) 收架；尾调 ·sub_4E33D0 状态收尾
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9BF0(uint32_t *this, int ArgList, int pArg3, int nArg4, int nArg5)
{
  char v5; // di
  int v7; // edx
  int fld_e1554; // eax
  uint32_t *fld_e15542; // eax
  int v10; // edx
  int v11; // eax
  int fld_e2167; // ebx

  v5 = ArgList;
  switch ( ArgList )
  {
    case 5:
      if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
        *(this + 2151) = 2;
      if ( *(this + 2151) == 0 )
      {
        *(this + 2151) = 1;
        LOBYTE(ArgList) = 9;
        sub_4ED3F0((int)(this + 2152), pArg3);
        *(this + 2156) = sub_699000((int)(this + 9));
        v5 = 9;
        *(this + 2158) = sub_699000((int)(this + 9));
      }
      break;
    case 8:
      *((uint8_t *)this + 8600) = 1;
      v7 = *this;
      fld_e1554 = *(this + 1554);
      if ( **(uint32_t **)(pArg3 + 4) != 0 )
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(
          this,
          1,
          *(uint32_t *)(fld_e1554 + 4),
          0,
          0,
          0,
          0);
      else
        (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(v7 + 204))(
          this,
          1,
          *(uint32_t *)(fld_e1554 + 20),
          0,
          0,
          0,
          0);
      break;
    case 14:
      fld_e15542 = (uint32_t *)*(this + 1554);
      v10 = *this;
      *((uint8_t *)this + 8600) = 1;
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t))(v10 + 196))(this, *fld_e15542);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*this + 612))(this, 1, 1);
      break;
    case 17:
      *(this + 2175) = 0;
      *((uint8_t *)this + 8657) = 0;
      *((uint8_t *)this + 8658) = 0;
      sub_698F90((int)(this + 2161), 30000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      break;
    default:
      break;
  }
  v11 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 840))(this);
  if ( v11 != 0 )
  {
    if ( v11 == 14 )
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t))(*this + 612))(this, 0, 0);
  }
  else
  {
    fld_e2167 = *(this + 2167);
    if ( sub_699000((int)(this + 2161)) >= fld_e2167 )  // 【clock_now(clk)】
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t, uint32_t))(*this + 560))(this, 17, 0, 0, 0);
      *(this + 2175) = 0;
      *((uint8_t *)this + 8657) = 0;
      *((uint8_t *)this + 8658) = 0;
      sub_698F90((int)(this + 2161), 30000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
    }
    v5 = ArgList;
  }
  return sub_4E33D0(v5, *(float *)&pArg3, nArg4, nArg5);
}



// 邪眼死亡演出：Monster/Common/Particle/MonsterDieSmoke.ptl + PassiveObject/Monster/
//   EvilEye/Particle/MissileGero{Center,CenterLeft,CenterRight,Left,Right}.ptl 五向泪弹（58L）
// ------------------------------------------------------------
// 0x5D9DA0 sub_5D9DA0 —— 邪眼死亡演出资源预载
// new ·0x12C 经 ·sub_428F30 装载 MonsterDieSmoke.ptl 入 this+2159，其 vt+36 取参数面；
// 经 vt+672(3) 对象 +984/+998 倒计时双字段换算（-30000）/140000 后 ·sub_4049C0 插值出
// 尺寸 20..60 与 50..150（+12/+16/+20 三尺寸槽，中槽双倍）；this+2160=3000 演出时长；
// this+2177..2181 五槽经 dword_8F84E4 资源器 vt+4 装载 MissileGero 五向泪弹粒子
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9DA0(uint32_t *this)
{
  uint32_t *pMem; // eax
  uint32_t *v3; // eax
  int fld_e2159; // edi
  int v5; // ebx
  uint64_t v6; // rax
  int v7; // ebx
  uint64_t v8; // rax
  uint64_t v9; // rax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-14h]
  int v12; // [esp+10h] [ebp-10h]

  pMem = operator new(0x12Cu);
  if ( pMem != nullptr )
    v3 = sub_428F30(pMem, (int)"Monster/Common/Particle/MonsterDieSmoke.ptl", 0);
  else
    v3 = nullptr;
  *(this + 2159) = v3;
  (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 28))(v3);
  fld_e2159 = (*(int (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2159) + 36))(*(this + 2159));
  v5 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  v12 = sub_41A5E0(v5 + 984);
  v6 = (uint64_t)((double)v12 * COERCE_FLOAT(sub_41A5E0(v5 + 998)));
  *(float *)fld_e2159 = sub_4049C0(20.0, 60.0, (int)v6 - 30000, 140000);
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 672))(this, 3);
  Block = (void *)sub_41A5E0(v7 + 984);
  v8 = (uint64_t)((double)(int)Block * COERCE_FLOAT(sub_41A5E0(v7 + 998)));
  v9 = (uint64_t)sub_4049C0(50.0, 150.0, (int)v8 - 30000, 140000);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
  *(uint32_t *)(fld_e2159 + 12) = v9;
  *(uint32_t *)(fld_e2159 + 16) = 2 * v9;
  *(uint32_t *)(fld_e2159 + 20) = v9;
  *(this + 2160) = 3000;
  *(this + 2177) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenter.ptl");
  *(this + 2178) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenterLeft.ptl");
  *(this + 2179) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroCenterRight.ptl");
  *(this + 2180) = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
                     dword_8F84E4,
                     "PassiveObject/Monster/EvilEye/Particle/MissileGeroLeft.ptl");
  result = (*(int (/*thiscall*/ **)(int, const char *))(*(uint32_t *)dword_8F84E4 + 4))(
             dword_8F84E4,
             "PassiveObject/Monster/EvilEye/Particle/MissileGeroRight.ptl");
  *(this + 2181) = result;
  return result;
}



// 邪眼语音：EVIL_SHOUT + EVIL_DMG + EYE_WRIGGLE 蠕动（57L；this+8600..8664 相位）
// ------------------------------------------------------------
// 0x5D9F50 sub_5D9F50 —— CNEvilEye 主构造（邪眼）
// 基类 ·sub_4A4EA0 后挂 CNEvilEye vftable；+8612..8696 两组相位区清零（+8644/+8672 挂 ·off_6C2B88
// IObject 空 vftable；+8656/+8684 置 1）、+6792..6808、+8600/+8604、+8628=5、+7144=0；
// ·sub_5D9DA0 死亡粒子预载；文案注册 ·sub_4015C0 写 EVIL_SHOUT×2(0xA)/EVIL_DMG(8)/EYE_WRIGGLE(0xB)；
// ·sub_4DE5E0 文案条目装载 + 随机倒计时（id 0，15 条，5000..10000ms 随机）
// ------------------------------------------------------------
int /*thiscall*/ sub_5D9F50(int this, char ArgList, int nArg3)
{
  char v5; // [esp-24h] [ebp-3Ch]
  void *v6; // [esp-20h] [ebp-38h]
  int v7; // [esp-1Ch] [ebp-34h]
  int v8; // [esp-18h] [ebp-30h]
  int v9; // [esp-14h] [ebp-2Ch]

  sub_4A4EA0(ArgList, nArg3);
  *(uint32_t *)this = &CNEvilEye::`vftable';
  *(uint32_t *)(this + 8612) = 0;
  *(uint32_t *)(this + 8616) = 0;
  *(uint32_t *)(this + 8620) = 0;
  *(uint8_t *)(this + 8648) = 0;
  *(uint32_t *)(this + 8644) = &off_6C2B88;
  *(uint32_t *)(this + 8652) = 0;
  *(uint8_t *)(this + 8656) = 1;
  *(uint8_t *)(this + 8658) = 0;
  *(uint8_t *)(this + 8657) = 0;
  *(uint32_t *)(this + 8668) = 0;
  *(uint32_t *)(this + 8664) = 0;
  *(uint32_t *)(this + 8660) = 0;
  *(uint8_t *)(this + 8676) = 0;
  *(uint32_t *)(this + 8672) = &off_6C2B88;
  *(uint32_t *)(this + 8680) = 0;
  *(uint8_t *)(this + 8684) = 1;
  *(uint8_t *)(this + 8686) = 0;
  *(uint8_t *)(this + 8685) = 0;
  *(uint32_t *)(this + 8696) = 0;
  *(uint32_t *)(this + 8692) = 0;
  *(uint32_t *)(this + 8688) = 0;
  *(uint32_t *)(this + 6792) = 0;
  *(uint32_t *)(this + 6796) = 0;
  *(uint32_t *)(this + 6800) = 0;
  *(uint32_t *)(this + 6804) = 0;
  *(uint32_t *)(this + 6808) = 0;
  *(uint8_t *)(this + 8600) = 0;
  *(uint32_t *)(this + 8604) = 0;
  *(uint32_t *)(this + 8628) = 5;
  *(uint8_t *)(this + 7144) = 0;
  sub_5D9DA0((uint32_t *)this);
  *(uint8_t *)(this + 8657) = 0;
  *(uint8_t *)(this + 8658) = 0;
  sub_4015C0("EVIL_SHOUT", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("EVIL_SHOUT", 0xAu);  // 【std::string构造赋值】
  sub_4015C0("EVIL_DMG", 8u);  // 【std::string构造赋值】
  LOBYTE(v6) = 0;
  sub_4015C0("EYE_WRIGGLE", 0xBu);  // 【std::string构造赋值】
  sub_4DE5E0(v5, v6, v7, v8, v9, 0, 15, 5000, 10000);
  return this;
}



// AI 字段访问（this+8648/8676）
// ------------------------------------------------------------
// 0x5DA0E0 sub_5DA0E0 —— CNEvilEye 析构
// 重挂 vftable；this+2159 粒子子对象经 vftable[0](v,1) 释放清零；+2168/+2161 回写
// nengine::IObject 空 vftable（+8676/+8648 相位字节清零）；+2153 堆数组 free 后 2153/2154/2155 清零；
// 尾调 ·sub_4A50F0 基析构
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA0E0(void *this)
{
  void (/*thiscall*/ ***pThis_86F)(uint32_t, int); // ecx

  *(uint32_t *)this = &CNEvilEye::`vftable';
  v2 = *((void (/*thiscall*/ ****)(uint32_t, int))this + 2159);
  if ( v2 != nullptr )
    (**v2)(v2, 1);
  *((uint32_t *)this + 2159) = 0;
  *((uint32_t *)this + 2168) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8676) = 0;
  *((uint32_t *)this + 2161) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 8648) = 0;
  if ( *((uint32_t *)this + 2153) != 0 )
    j__free(*((void **)this + 2153));
  *((uint32_t *)this + 2153) = 0;
  *((uint32_t *)this + 2154) = 0;
  *((uint32_t *)this + 2155) = 0;
  return sub_4A50F0(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA190 sub_5DA190 —— 标量删除器（转调 ·sub_5DA0E0 析构，pszArg2&1 时 free）
// 标准 ICD 删除器形态：尾调析构后按掩码最低位判定是否 j__free 释放本块
// ------------------------------------------------------------
void */*thiscall*/ sub_5DA190(void *Block, char pszArg2)
{
  sub_5DA0E0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA1C0 sub_5DA1C0 —— 存活查询（this+2093 对象非空且其 vt+80 判定为真）
// 供 ·0x5DA550/·0x5DA750 族受击/伤害流程的存活门复用
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_5DA1C0(uint32_t *this)
{
  int fld_e2093; // eax

  fld_e2093 = *(this + 2093);
  return fld_e2093 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2093 + 80))() != 0;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA1E0 sub_5DA1E0 —— 索引→组号映射（nArg1>=55 归 4，否则查表 dword_738048；与 ·0x5DACE0 同表）
// 供 4 组帧区（本轮序 4 组上限）取组号，超界统一折叠到组 4
// ------------------------------------------------------------
int /*cdecl*/ sub_5DA1E0(int nArg1)
{
  if ( nArg1 >= 55 )
    return 4;
  else
    return dword_738048[nArg1];
}



// 邪眼相位字段大区（this+8216..8308, 112L —— 邪眼专用 82xx 字段块）
// ------------------------------------------------------------
// 0x5DA220 sub_5DA220 —— 邪眼相位大区复位（this+8216..8628，57 槽批量置初值）
// 默认 -1 的索引槽（8216/8400/8444/8496/8516/8536/8568/8592/8596）、组 5（8244）、
// 组 4（8252/8512/8528）、容量 100（8392）、倍率 1.0f（8388/8488）；
// 4 轮循环清 8260 起 4 个 -1 索引与 8276 起 4×2 计时对；8308..8364 十二槽与其余位清零；
// 8628 归 0（与 ·0x5D8DA0 的置 5 对照 —— 复位态）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA220(int this)
{
  int result; // eax
  uint32_t *pThis_2054; // esi
  uint32_t *pThis_2044; // edx
  int i; // [esp+Ch] [ebp-4h]

  result = 0;
  *(uint32_t *)(this + 8216) = -1;
  *(uint8_t *)(this + 8220) = 0;
  *(uint32_t *)(this + 8224) = 0;
  *(uint8_t *)(this + 8228) = 0;
  *(uint32_t *)(this + 8232) = 0;
  *(uint32_t *)(this + 8236) = 0;
  *(uint32_t *)(this + 8240) = 0;
  *(uint32_t *)(this + 8244) = 5;
  *(uint32_t *)(this + 8248) = 0;
  *(uint32_t *)(this + 8252) = 4;
  *(uint32_t *)(this + 8256) = 0;
  pThis_2054 = (uint32_t *)(this + 8276);
  pThis_2044 = (uint32_t *)(this + 8260);
  for ( i = 4; i != 0; --i )
  {
    *pThis_2044 = -1;
    *pThis_2054 = 0;
    pThis_2054[1] = 0;
    ++pThis_2044;
    pThis_2054 += 2;
  }
  *(uint32_t *)(this + 8308) = 0;
  *(uint32_t *)(this + 8328) = 0;
  *(uint32_t *)(this + 8348) = 0;
  *(uint32_t *)(this + 8312) = 0;
  *(uint32_t *)(this + 8332) = 0;
  *(uint32_t *)(this + 8352) = 0;
  *(uint32_t *)(this + 8316) = 0;
  *(uint32_t *)(this + 8336) = 0;
  *(uint32_t *)(this + 8356) = 0;
  *(uint32_t *)(this + 8320) = 0;
  *(uint32_t *)(this + 8340) = 0;
  *(uint32_t *)(this + 8360) = 0;
  *(uint32_t *)(this + 8324) = 0;
  *(uint32_t *)(this + 8344) = 0;
  *(uint32_t *)(this + 8364) = 0;
  *(uint8_t *)(this + 8368) = 0;
  *(uint32_t *)(this + 8372) = 0;
  *(uint8_t *)(this + 8376) = 0;
  *(uint32_t *)(this + 8380) = 0;
  *(uint32_t *)(this + 8384) = 0;
  *(uint32_t *)(this + 8392) = 100;
  *(uint32_t *)(this + 8396) = 0;
  *(uint8_t *)(this + 8404) = 0;
  *(uint32_t *)(this + 8400) = -1;
  *(uint32_t *)(this + 8388) = 1065353216;
  *(uint32_t *)(this + 8408) = 0;
  *(uint32_t *)(this + 8416) = 0;
  *(uint32_t *)(this + 8424) = 0;
  *(uint32_t *)(this + 8432) = 0;
  *(uint32_t *)(this + 8412) = 0;
  *(uint32_t *)(this + 8420) = 0;
  *(uint32_t *)(this + 8428) = 0;
  *(uint32_t *)(this + 8436) = 0;
  *(uint32_t *)(this + 8440) = 0;
  *(uint32_t *)(this + 8444) = -1;
  *(uint32_t *)(this + 8448) = 0;
  *(uint32_t *)(this + 8452) = 0;
  *(uint32_t *)(this + 8456) = 0;
  *(uint32_t *)(this + 8460) = 0;
  *(uint32_t *)(this + 8464) = 0;
  *(uint32_t *)(this + 8468) = 0;
  *(uint32_t *)(this + 8472) = 0;
  *(uint32_t *)(this + 8476) = 0;
  *(uint32_t *)(this + 8480) = 0;
  *(uint32_t *)(this + 8484) = 0;
  *(uint32_t *)(this + 8488) = 1065353216;
  *(uint32_t *)(this + 8492) = 0;
  *(uint32_t *)(this + 8496) = -1;
  *(uint32_t *)(this + 8500) = 0;
  *(uint8_t *)(this + 8504) = 0;
  *(uint32_t *)(this + 8508) = 0;
  *(uint32_t *)(this + 8512) = 4;
  *(uint32_t *)(this + 8516) = -1;
  *(uint8_t *)(this + 8520) = 0;
  *(uint32_t *)(this + 8524) = 0;
  *(uint32_t *)(this + 8528) = 4;
  *(uint32_t *)(this + 8532) = 0;
  *(uint32_t *)(this + 8536) = -1;
  *(uint32_t *)(this + 8540) = 0;
  *(uint32_t *)(this + 8544) = 0;
  *(uint32_t *)(this + 8548) = 0;
  *(uint32_t *)(this + 8552) = 0;
  *(uint32_t *)(this + 8556) = 0;
  *(uint32_t *)(this + 8560) = 0;
  *(uint32_t *)(this + 8564) = 0;
  *(uint32_t *)(this + 8568) = -1;
  *(uint32_t *)(this + 8572) = 0;
  *(uint32_t *)(this + 8576) = 0;
  *(uint32_t *)(this + 8580) = 0;
  *(uint8_t *)(this + 8584) = 0;
  *(uint8_t *)(this + 8585) = 0;
  *(uint32_t *)(this + 8588) = 0;
  *(uint32_t *)(this + 8592) = -1;
  *(uint32_t *)(this + 8596) = -1;
  *(uint8_t *)(this + 8628) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA490 sub_5DA490 —— avatar 子对象复位（·sub_4B32E0 后 +2148/2149 置 -1，返回 -1）
// 与 ·0x5DADE0（置 dword_79D100 时钟快照）配对使用 —— 复位态用 -1 表示无锚点
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA490(uint32_t *this)
{
  sub_4B32E0();
  *(this + 2148) = -1;
  *(this + 2149) = -1;
  return -1;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA4B0 sub_5DA4B0 —— avatar 集合初始化（·sub_4B1670 后 +2061 槽置 5）
// +2061 与 ·0x5DAC20 的 this+2064 倒计时计数缓存同片字段区【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA4B0(uint32_t *this)
{
  int result; // eax

  result = sub_4B1670();
  *(this + 2061) = 5;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA4D0 sub_5DA4D0 —— 收招复位（this+2056 非零 → 经 vt+672(3)+1026 槽回写差值并由
// ·sub_41A590 写回速率），尾调 ·sub_4D4A20 观察者通知（受击包五号回调）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA4D0(float *this, int nArg2, int nArg3, int nArg4)
{
  unsigned int pThis_2A0; // edi
  int v6; // edx
  float fld_e2056; // [esp+4h] [ebp-8h]
  int v9; // [esp+4h] [ebp-8h]

  if ( *(this + 2056) != 0.0 )
  {
    fld_e2056 = *(this + 2056);
    pThis_2A0 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 672))(this, 3) + 1026;
    *(float *)&v9 = COERCE_FLOAT(sub_41A5E0(pThis_2A0)) - fld_e2056;
    sub_41A590(pThis_2A0, v6, v9);
    *(this + 2056) = 0.0;
  }
  return sub_4D4A20(this, nArg2, nArg3, nArg4);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA550 sub_5DA550 —— 伤害计算覆写（受击方档位 vt+348 + 帧写入 vt+736）
// this+2095 对象存活且 nArg4==0 且 ·sub_4AED20 计数<=1 时：vt+648 伤害类型（100）→ vt+628
// 伤害结算（·sub_432F40 定点转换）→ 与 vt+752 上限比较钳位 → 百分比写入 this+2098；
// 命中则 vt+744 扣血 + this+2095 vt+120 反馈；返回 ·sub_4AFB80（受击流程收尾）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA550(float *this, int nArg2, int nArg3, int nArg4)
{
  int nArg22; // ebx
  int pThis_82F; // ecx
  int v7; // edx
  int v8; // edx
  int pThis_2F0; // edi
  int pThis_8302; // eax
  int v11; // eax
  float pThis_830; // [esp+20h] [ebp-20h]
  float fld_e2097; // [esp+20h] [ebp-20h]
  float fld_e20972; // [esp+20h] [ebp-20h]
  float v16; // [esp+20h] [ebp-20h]
  int v17; // [esp+30h] [ebp-10h] BYREF
  float v18; // [esp+34h] [ebp-Ch]
  int v19; // [esp+38h] [ebp-8h] BYREF
  int pThis_2F02; // [esp+3Ch] [ebp-4h]

  nArg22 = nArg2;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2);
  (*(void (/*thiscall*/ **)(float *))(*(uint32_t *)this + 736))(this);
  pThis_82F = *((uint32_t *)this + 2095);
  if ( pThis_82F != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pThis_82F + 80))(pThis_82F) != 0
    && (uint8_t)nArg4 == 0
    && (unsigned int)sub_4AED20((int)this) <= 1 )
  {
    v7 = *(uint32_t *)this;
    v19 = 100;
    (*(void (/*thiscall*/ **)(float *, int *, int))(v7 + 648))(this, &v19, nArg22);
    v8 = *(uint32_t *)this;
    HIBYTE(nArg2) = 0;
    v17 = 0;
    v18 = (float)(*(int (/*thiscall*/ **)(float *, char *, int *, int, int, int, uint32_t))(v8 + 628))(
                   this,
                   (char *)&nArg2 + 3,
                   &v17,
                   v19,
                   nArg22,
                   nArg3,
                   0);
    pThis_830 = (double)*((int *)this + 2096) * v18 * 0.0099999998;
    pThis_2F02 = sub_432F40(pThis_830);
    fld_e2097 = (double)pThis_2F02 * *(this + 2097);
    pThis_2F0 = sub_432F40(fld_e2097);
    if ( pThis_2F0 > (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 752))(this) )
    {
      pThis_2F0 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 752))(this);
      pThis_2F02 = pThis_2F0;
      fld_e20972 = (double)pThis_2F0 / *(this + 2097);
      pThis_2F02 = sub_432F40(fld_e20972);
      v16 = 100.0 - (double)pThis_2F02 * 100.0 / v18;
      pThis_8302 = sub_432F40(v16);
    }
    else
    {
      pThis_8302 = 100 - *((uint32_t *)this + 2096);
    }
    *((uint32_t *)this + 2098) = pThis_8302;
    if ( pThis_2F0 != 0 )
    {
      v18 = *this;
      v11 = (*(int (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 752))(this, 1);
      (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 744))(this, v11 - pThis_2F0);
      (*(void (/*thiscall*/ **)(uint32_t))(**((uint32_t **)this + 2095) + 120))(*((uint32_t *)this + 2095));
    }
  }
  return sub_4AFB80(nArg22, nArg3, nArg4);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA6D0 sub_5DA6D0 —— 伤害百分比复位（+2098=100）后转调 ·sub_4AFC30 受击流程
// 与 ·0x5DA550 的 +2098 上限写入配对 —— 本函数为其满值复位路径
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA6D0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  *(this + 2098) = 100;
  return sub_4AFC30(nArg2, nArg3, nArg4);
}



// AI 字段访问（this+8584）
// ------------------------------------------------------------
// 0x5DA6F0 sub_5DA6F0 —— 受击联动（·sub_4D54E0 受击包后：+1639==10 主状态镜像 且 +1953==0/+1954==15
// 子相位 且 +8584 标志位时，以 dword_9B9344 弧度常量经 vt+272 触发转向/击退【推断】）
// ------------------------------------------------------------
char /*thiscall*/ sub_5DA6F0(uint32_t *this)
{
  int fld_e1953; // eax
  float v4; // [esp+0h] [ebp-8h]

  LOBYTE(fld_e1953) = sub_4D54E0(this);
  if ( *(this + 1639) == 10 )
  {
    fld_e1953 = *(this + 1953);
    if ( fld_e1953 == 0 && *(this + 1954) == 15 )
    {
      LOBYTE(fld_e1953) = *((uint8_t *)this + 8584);
      if ( (uint8_t)fld_e1953 != 0 )
      {
        v4 = (double)dword_9B9344 * 0.017444445;
        LOBYTE(fld_e1953) = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 272))(this, 1, LODWORD(v4));
      }
    }
  }
  return fld_e1953;
}



// 数据表读数（sub_47EF20, 41L）
// ------------------------------------------------------------
// 0x5DA740 sub_5DA740 —— 伤害数值闸（·sub_4AFBF0 受击过滤；结果!=3 时）
// this+2095 存活 → 伤害钳位到 this+2098 百分比上限；this+2142!=-1 且主状态镜像 +1639 为 0/11 时
// 经 vt+1140 取表 38 参数、vt+1160 恢复、·sub_47EF20 查表加权（+1000 基准）后改写伤害
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA740(int *this, int *pDwArg2, int nArg3)
{
  int result; // eax
  int v5; // ebx
  int fld_e2095; // eax
  int fld_e2098; // eax
  int fld_e1639; // eax
  int v9; // [esp-Ch] [ebp-18h]

  result = sub_4AFBF0(pDwArg2, nArg3);
  v5 = result;
  if ( result != 3 )
  {
    fld_e2095 = *(this + 2095);
    if ( fld_e2095 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2095 + 80))() != 0 )
    {
      fld_e2098 = *pDwArg2;
      if ( *pDwArg2 >= *(this + 2098) )
        fld_e2098 = *(this + 2098);
      *pDwArg2 = fld_e2098;
    }
    if ( *(this + 2142) != -1 )
    {
      fld_e1639 = *(this + 1639);
      if ( fld_e1639 == 0 || fld_e1639 == 11 )
      {
        v9 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 38, -1);
        (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
        *pDwArg2 = (sub_47EF20(38, 1, v9, -1, 11) + 1000) * *pDwArg2 / 1000;
      }
    }
    return v5;
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA7F0 sub_5DA7F0 —— 受击事件链（vt+308 存活门；+7730 标志决定 pszArg3 是否生效）
// ·sub_4AFD50 过滤 → vt+1140 查 32 号表项 >0 判定 → vt+1160 写 11 标志 → ·sub_47E440 事件 11；
// 非零路径 vt+1140 查 33 号表项 + vt+1160 + ·sub_47E440(14)；再按 34 号表项判定写 12 标志 + 事件
// ------------------------------------------------------------
int /*userpurge*/ sub_5DA7F0@<eax>(uint8_t *pArg1@<ecx>, char pszArg2@<bl>, char pszArg3)
{
  int result; // eax
  char pszArg32; // bl
  int v6; // eax
  bool v7; // al
  char v9; // [esp-4h] [ebp-8h]

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 308))(pArg1);
  if ( (uint8_t)result != 0 )
  {
    if ( pArg1[7730] != 0 )
    {
      pszArg32 = pszArg3;
    }
    else
    {
      pszArg32 = 0;
      pszArg3 = 0;
    }
    v6 = sub_4AFD50(pszArg3);
    LOBYTE(v6) = pszArg32 != 0 && (v6 = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 32)) > 0;
    (*(void (/*thiscall*/ **)(uint8_t *, int, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 11, v6);
    sub_47E440(pszArg2);
    if ( pszArg32 != 0 )
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 33);
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)pArg1 + 1160))(pArg1);
    sub_47E440(14);
    v7 = pszArg32 != 0 && (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1140))(pArg1, 34) > 0;
    v9 = v7;
    (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)pArg1 + 1160))(pArg1, 12);
    return sub_47E440(v9);
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA8D0 sub_5DA8D0 —— 存活查询透传（vt+308）
// 供受击包族（·0x5DA7F0/·0x5DA9E0 等）统一走 vftable 存活门，避免直接判对象指针
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA8D0(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 308))(this);
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA8E0 sub_5DA8E0 —— 集合移除回调（·sub_4B0530 后：uArg2==this+2110 槽则清槽；
// uArg2==this 自身移除时经 vt+216 自毁通知 11）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DA8E0(uint32_t *this, uint32_t *uArg2)
{
  int result; // eax

  result = sub_4B0530(uArg2);
  if ( uArg2 == (uint32_t *)*(this + 2110) )
    *(this + 2110) = 0;
  if ( uArg2 == this )
    return (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DA920 sub_5DA920 —— 主状态→组号映射（6/7/8/9 → 0/1/2/3，其余归 4）
// 与 ·0x5DA1E0 的 dword_738048 表映射互为印证（两条索引→组号路径）
// ------------------------------------------------------------
int /*stdcall*/ sub_5DA920(int nArg1)
{
  int result; // eax

  switch ( nArg1 )
  {
    case 6:
      result = 0;
      break;
    case 7:
      result = 1;
      break;
    case 8:
      result = 2;
      break;
    case 9:
      result = 3;
      break;
    default:
      result = 4;
      break;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA980 sub_5DA980 —— 索引→表值查表（在 dword_738020 前 4 项中定位，命中返回 dword_738030 同位项；未命中 -1）
// 与 ·0x5DA9B0（成员布尔查询）共用 dword_738020 区表 —— 一表两用（值映射 + 包含判定）
// ------------------------------------------------------------
int /*cdecl*/ sub_5DA980(int nArg1)
{
  int v1; // eax

  v1 = 0;
  while ( nArg1 != dword_738020[v1] )
  {
    if ( ++v1 >= 4 )
      return -1;
  }
  return dword_738030[v1];
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DA9B0 sub_5DA9B0 —— 表包含查询（nArg1 在 unk_737FFC..dword_738020 区间表内返回 1）
// 与 ·0x5DA980 同表区（737FFC..738020，四项）—— 本函数只判包含不取值
// ------------------------------------------------------------
char /*stdcall*/ sub_5DA9B0(int nArg1)
{
  uint32_t *v1; // eax

  v1 = &unk_737FFC;
  while ( nArg1 != *v1 )
  {
    if ( (int)++v1 >= (int)dword_738020 )
      return 0;
  }
  return 1;
}



// 时钟门+数据表 AI（sub_699000+sub_47EF20, 46L）
// ------------------------------------------------------------
// 0x5DA9E0 sub_5DA9E0 —— 相位组切换（pArg2 目标组；this+2062 对象存活门）
// 组变更且新组!=4 时：vt+1140 查 29 号表项 + vt+1160 恢复 → ·sub_47EF20 表 29 加权时延写
// this+2065+pArg2 到点槽；·sub_4926A0 帧游标复位选帧（2087/2082 组、组 2 时补 2091/2086）；
// this+2063 记组号；this+2*pArg2+2069 起 2 项帧游标复位
// ------------------------------------------------------------
void /*thiscall*/ sub_5DA9E0(int *this, int pArg2)
{
  int fld_e2062; // ecx
  int fld_e2063; // eax
  int v5; // ebx
  int pThis_9; // eax
  int v7; // ecx
  int *pThis_2; // esi
  int i; // edi
  int v10; // [esp-14h] [ebp-18h]

  fld_e2062 = *(this + 2062);
  if ( fld_e2062 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2062 + 80))(fld_e2062) != 0 )
  {
    fld_e2063 = *(this + 2063);
    if ( fld_e2063 != pArg2 )
    {
      if ( fld_e2063 != 4 )
      {
        v10 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 29, -1);
        (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
        v5 = sub_47EF20(29, 1, v10, -1, 11);
        pThis_9 = sub_699000((int)(this + 9));  // 【clock_now(clk)】
        v7 = *(this + pArg2 + 2087);
        *(this + pArg2 + 2065) = v5 + pThis_9;
        sub_4926A0(v7);
        sub_4926A0(*(this + pArg2 + 2082));
        if ( pArg2 == 2 )
        {
          sub_4926A0(*(this + 2091));
          sub_4926A0(*(this + 2086));
        }
      }
      *(this + 2063) = pArg2;
      pThis_2 = this + 2 * pArg2 + 2069;
      for ( i = 2; i != 0; --i )
        sub_4926A0(*pThis_2++);
    }
  }
}



// 时钟门 AI（sub_699000, 79L）
// ------------------------------------------------------------
// 0x5DAAC0 sub_5DAAC0 —— 播放驱动（帧数组批播 + 表偏移定位）
// this+2062 存活门；动作切换（pszArg2 且组!=4）时对当前组 2 项帧数组 ·sub_4938F0 起播 +
// ·sub_491D00 基座定位；行 5 组循环查 byte_737FF4 匹配动作：到点槽 this+2065 未到用 2087 组、
// 到点且帧未播放（+170==0 且帧数<3）经 ·sub_491C70/·sub_493A60 换算起播，等宽/越限分支 2082 组；
// 每组经 ·sub_4938F0(v10) 播放 + ·sub_491D00 按 dword_737FD4/737FE4 表偏移定位坐标
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAAC0(int *this, char pszArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int i; // edi
  int j; // ebx
  int v9; // edi
  int v10; // edi
  int v11; // eax
  int v12; // [esp+4h] [ebp-4h]

  result = *(this + 2062);
  if ( result != 0 )
  {
    result = (*(int (**)(void))(*(uint32_t *)result + 80))();
    if ( (uint8_t)result != 0 )
    {
      if ( pszArg2 != 0 && *(this + 2063) != 4 )
      {
        for ( i = 0; i < 2; ++i )
        {
          sub_4938F0(*(this + 2 * *(this + 2063) + i + 2069));
          sub_491D00(dword_79C0B0, nArg3, nArg4 - *(this + 40), 0.0);
        }
      }
      for ( j = 0; j < 5; ++j )
      {
        if ( j == 4 )
        {
          result = 2;
          v12 = 2;
        }
        else
        {
          v12 = j;
          result = j;
        }
        if ( byte_737FF4[result] != pszArg2 )
          continue;
        v9 = *(this + result + 2065);
        if ( v9 == -1 )
        {
          v10 = *(this + j + 2077);
          if ( *(uint8_t *)(v10 + 170) != 0 )
            goto LABEL_17;
        }
        else
        {
          if ( sub_699000((int)(this + 9)) >= v9 )  // 【clock_now(clk)】
          {
            v10 = *(this + j + 2087);
            if ( *(uint8_t *)(v10 + 170) == 0 )
            {
              if ( *(int *)(v10 + 148) < 3 )
              {
                v11 = sub_491C70(v10, 3);
                sub_493A60(v10, v11);
              }
              goto LABEL_18;
            }
LABEL_17:
            v10 = *(this + j + 2082);
            goto LABEL_18;
          }
          v10 = *(this + j + 2087);
        }
LABEL_18:
        sub_4938F0(v10);
        result = sub_491D00(dword_79C0B0, nArg3 + dword_737FD4[v12], nArg4 + dword_737FE4[v12], 0.0);
      }
    }
  }
  return result;
}



// 时钟门+数据表 AI（sub_699000+sub_47EF20, 45L）
// ------------------------------------------------------------
// 0x5DAC20 sub_5DAC20 —— 倒计时槽计数广播（this+2062 存活门）
// 扫描 this+2065..2068 四个到点槽，统计未到点（clock_now < 槽值）个数 v5；与 this+2064 缓存不同则
// this+2062 vt+124 激活；v5!=0 时经 vt+1140 查 29 号表项、vt+1160 写 29 组(v5+1) 与查表值、
// ·sub_47EF20 时延换算后经 this+2062 vt+120 广播（计数 +1 与浮点值）
// ------------------------------------------------------------
void /*usercall*/ sub_5DAC20(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>)
{
  int pObj; // ecx
  int v5; // ebx
  int *v6; // edi
  int pObj2; // ecx
  int v8; // eax
  int v9; // eax
  int v12; // [esp+14h] [ebp-8h]
  float v13; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  pObj = pDwArg1[2062];
  if ( pObj != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 80))(pObj) != 0 )
  {
    v5 = 0;
    v6 = pDwArg1 + 2065;
    for ( i = 4; i != 0; --i )
    {
      if ( *v6 != -1 && sub_699000((int)(pDwArg1 + 9)) < *v6 )  // 【clock_now(clk)】
        ++v5;
      ++v6;
    }
    if ( v5 != pDwArg1[2064] )
    {
      pObj2 = pDwArg1[2062];
      pDwArg1[2064] = v5;
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 124))(pObj2);
      if ( v5 != 0 )
      {
        v8 = (*(int (/*thiscall*/ **)(int *, int, int))(*pDwArg1 + 1140))(pDwArg1, 29, -1);
        (*(void (/*thiscall*/ **)(int *, int, int, int))(*pDwArg1 + 1160))(pDwArg1, 29, v5 + 1, v8);
        v9 = sub_47EF20(-1, 11, nArg3, nArg2, v12);
        v13 = (float)v9;
        (*(void (/*cdecl*/ **)(int, uint32_t, uint32_t, int))(*(uint32_t *)pDwArg1[2062] + 120))(1, 0, LODWORD(v13), v9);
      }
    }
  }
}



// 数据表+变速换锚 AI（sub_47EF20+sub_493D00, 39L）
// ------------------------------------------------------------
// 0x5DACE0 sub_5DACE0 —— 换锚重定（主状态镜像 +1639 为 0/11 且 this+2142 表参非 -1 时）
// 经 vt+1140 查 38 号表项 + vt+1160 恢复 → ·sub_47EF20 查表；vt+888 速率双轴写入
// （v5*pArg1[1663]/1000 千分制换算）；·0x5DA1E0 同一 dword_738048 组表取组号后
// this+2043 组区 2 项帧对经 ·sub_493D00 速率复位至 100.0（变速撤离锚点）【推断】
// ------------------------------------------------------------
void /*usercall*/ sub_5DACE0(uint32_t *pArg1@<ecx>, int nArg2@<edi>)
{
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int *v8; // esi
  int i; // edi

  if ( pArg1[2142] != -1 )
  {
    v3 = pArg1[1639];
    if ( v3 == 0 || v3 == 11 )
    {
      v4 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 1140))(pArg1);
      (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*pArg1 + 1160))(pArg1, 38, 0, v4);
      v5 = sub_47EF20(38, -1, -1, 11, nArg2);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, int))(*pArg1 + 888))(pArg1, 0, 0, v5 * pArg1[1663] / 1000);
      v6 = pArg1[2142];
      if ( v6 >= 55 )
        v7 = 4;
      else
        v7 = dword_738048[v6];
      v8 = &pArg1[2 * v7 + 2043];
      for ( i = 2; i != 0; --i )
      {
        sub_493D00(*(v8 - 10), 100.0);
        sub_493D00(*v8++, 100.0);
      }
    }
  }
}



// AI 字段访问（this+8628）
// ------------------------------------------------------------
// 0x5DADE0 sub_5DADE0 —— 死亡/移除锚定（vt+216 事件 11 + +8628 帧索引清零 + vt+212 播报 nArg2；
// +2148 时刻槽取 dword_79D100 时钟快照 —— 与 ·0x5DA490 的 -1 复位及后续到点比较配对）【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DADE0(uint8_t *this, int nArg2)
{
  int v3; // edx
  int result; // eax

  (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 216))(this, 11);
  v3 = *(uint32_t *)this;
  *(this + 8628) = 0;
  result = (*(int (/*thiscall*/ **)(uint8_t *, int, int, uint32_t, uint32_t))(v3 + 212))(this, nArg2, 11, 0, 0);
  *((uint32_t *)this + 2148) = dword_79D100[0];
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DAE20 sub_5DAE20 —— 内联尾插（this[0]=容量上限、this[1]=基址、this[2]=游标；越界转·off_77F3FC 断言）
// ·被 0x5E1000 / aura_create / passive_object 直接喂 dword_9B9344 等 AI 相位槽值【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAE20(int *this, int nArg2)
{
  int fld_e2; // esi
  int v3; // ecx
  int result; // eax

  *(uint32_t *)(*(this + 1) + *(this + 2)) = nArg2;
  fld_e2 = *(this + 2) + 4;
  *(this + 2) = fld_e2;
  v3 = *this;
  result = fld_e2;
  if ( fld_e2 > v3 )
    return off_77F3FC(aCriticalError_40, v3);
  return result;
}



// 追击弹发射：CHASER_LAUNCH 播报（14L）
// ------------------------------------------------------------
// 0x5DAE60 sub_5DAE60 —— 追击弹发射相位同步：·sub_4AFDB0 基类发射后，索引 <55 且组号非 4 时·sub_5DA9E0 切相位组
// ·弹种 39 追加 vt+212 播报 CHASER_LAUNCH（dword_738048 为索引→组号表，55 为表长门）
// ------------------------------------------------------------
void /*thiscall*/ sub_5DAE60(int *this, int nArg2, int nArg3)
{
  sub_4AFDB0((uint8_t **)this, nArg2, nArg3);
  if ( nArg2 < 55 && dword_738048[nArg2] != 4 )
    sub_5DA9E0(this, dword_738048[nArg2]);
  if ( nArg2 == 39 )
    (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "CHASER_LAUNCH", -1, 0, 0);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DAEB0 sub_5DAEB0 —— 双驱动择序派发：nArg2 非 0 先·sub_4B1E50 外观渲染主驱动再·sub_5DAAC0 帧数组批播
// ·nArg2 为 0 时反序（先批播后渲染）【推断：两套表现管线的顺序门】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAEB0(int *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  if ( (uint8_t)nArg2 != 0 )
  {
    sub_4B1E50(nArg2, nArg3, nArg4, nArg5);
    return sub_5DAAC0(this, nArg2, nArg3, nArg4, nArg5);
  }
  else
  {
    sub_5DAAC0(this, 0, nArg3, nArg4, nArg5);
    return sub_4B1E50(0, nArg3, nArg4, nArg5);
  }
}



// AI 字段访问（this+8628）
// ------------------------------------------------------------
// 0x5DAF10 sub_5DAF10 —— 延时播报到点触发：this+8596 时刻槽非 -1 且 dword_79D100 时钟已到，先判 this+8628 忙位 vt+216(this,11) 解忙
// ·再以 this+8624<0x10 判 SSO 取 +8604 文案串交 vt+212 播报，末尾时刻槽复位 -1（与·0x5DADE0/·0x5DBBD0 三点配对）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DAF10(int *this)
{
  int result; // eax
  uint32_t *pThis_867; // eax

  result = *(this + 2149);
  if ( result != -1 && dword_79D100[0] >= result )
  {
    if ( *((uint8_t *)this + 8628) != 0 )
      (*(void (/*thiscall*/ **)(int *, int))(*this + 216))(this, 11);
    if ( (unsigned int)*(this + 2156) < 0x10 )
      pThis_867 = this + 2151;
    else
      pThis_867 = (uint32_t *)*(this + 2151);
    result = (*(int (/*thiscall*/ **)(int *, uint32_t *, int, uint32_t, uint32_t))(*this + 212))(this, pThis_867, -1, 0, 0);
    *(this + 2149) = -1;
  }
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DAF70 sub_5DAF70 —— 内联 vector 插入搬移：dst=nArg3-4*元素数、长度由 nArg2-Src 推得，尾段整体后移一格
// ·仅被·0x5DBCD0/·0x5DBEB0 的插入分支调用【推断：MSVC vector 插入内联残留】
// ------------------------------------------------------------
void */*cdecl*/ sub_5DAF70(void *Src, int nArg2, int nArg3)
{
  return memcpy_0((void *)(nArg3 - 4 * ((nArg2 - (int)Src) >> 2)), Src, 4 * ((nArg2 - (int)Src) >> 2));
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DAFA0 sub_5DAFA0 —— CNWhipped 构造（鞭挞效果）：基类·sub_4B1030 → 置 CNWhipped vftable → ·sub_64D880 装资源
// ··sub_64DC00 注入鞭挞参数；被·0x5DE100 以 new(0x70)+弹种 20 实例化
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DAFA0(uint32_t *this, char pszArg2, int nArg3)
{
  sub_4B1030();
  *this = &CNWhipped::`vftable';
  sub_64D880(this);
  sub_64DC00((int)this, pszArg2, nArg3);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB000 sub_5DB000 —— CNWhipped 标量删除器（转调·sub_5DB030 析构，bit0 置位才 j__free）
// ·调用点由 vtable 槽 0 承担；本文件·0x5DAFA0 构造的 0x70 字节块配套释放【推断：vftable 未知】
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB000(void *Block, char pszArg2)
{
  sub_5DB030();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB030 sub_5DB030 —— CNWhipped 析构：先回置 CNWhipped vftable → ·sub_6509F0 释放资源 → 降为 IRDAppendage vftable
// ··sub_5F6640 基类析构，this+8 再置 nengine::IObject vftable、this+12 清零（三态析构链）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB030(uint32_t *this)
{
  int result; // eax

  *this = &CNWhipped::`vftable';
  sub_6509F0();
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB090 sub_5DB090 —— CNFollowMe 构造（召集跟随标）：基类·sub_4B1030 → 置 CNFollowMe vftable → ·sub_64D910 装资源
// ··sub_64D940 注入 nArg2；被·0x5DB260 以 new(0x7C)+vt+1140(this,30) 取参实例化
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DB090(uint32_t *this, int nArg2)
{
  sub_4B1030();
  *this = &CNFollowMe::`vftable';
  sub_64D910(this);
  sub_64D940((int)this, nArg2);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB0F0 sub_5DB0F0 —— CNFollowMe 标量删除器（转调·sub_5DB120 析构，bit0 置位才 j__free）
// ·与·0x5DB000/·0x5DB1D0 三者除析构目标不同外指令序列一致（同构删除器族）
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB0F0(void *Block, char pszArg2)
{
  sub_5DB120();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB120 sub_5DB120 —— CNFollowMe 析构：·sub_64E920 跟随受击收尾 → 回置 IRDAppendage vftable → ·sub_5F6640 基类析构
// ·this+8 置 nengine::IObject vftable、this+12 清零（与·0x5DB030 同构析构链）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB120(uint32_t *this)
{
  int result; // eax

  *this = &CNFollowMe::`vftable';
  sub_64E920();
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB180 sub_5DB180 —— CNAuraShield 构造（光环护盾）：基类·sub_4B1030 → 置 CNAuraShield vftable
// ··sub_6509D0 基类装配 → ·sub_64ED00 装载 AuraShieldStart/Loop/End 三段光环资源
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DB180(uint32_t *this)
{
  sub_4B1030();
  *this = &CNAuraShield::`vftable';
  sub_6509D0(this);
  sub_64ED00(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB1D0 sub_5DB1D0 —— CNAuraShield 标量删除器（转调·sub_5DB200 析构，bit0 置位才 j__free）
// ·与·0x5DB000/·0x5DB0F0 同构（本组三挂件析构统一尾调·sub_5F6640）
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB1D0(void *Block, char pszArg2)
{
  sub_5DB200();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB200 sub_5DB200 —— CNAuraShield 析构：·sub_64EE40 护盾受击收尾 → 回置 IRDAppendage vftable → ·sub_5F6640 基类析构
// ·this+8 置 nengine::IObject vftable、this+12 清零（与·0x5DB030/·0x5DB120 同构，仅末段收尾函数不同）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB200(uint32_t *this)
{
  int result; // eax

  *this = &CNAuraShield::`vftable';
  sub_64EE40();
  *this = &IRDAppendage::`vftable';
  result = sub_5F6640(this);
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB260 sub_5DB260 —— 召集标实例化：new(0x7C) 后取 vt+1140(this,30) 参数交·sub_5DB090 构造 CNFollowMe
// ·再 vt+56(v4, Block, this, 0, 0, 12, -1) 挂装到 Block 上（12 为挂点/类型参数）；仅由·0x5DB2E0 的三重门放行
// ------------------------------------------------------------
void /*thiscall*/ sub_5DB260(void *this, void *Block)
{
  uint32_t *pMem; // edi
  uint32_t *v4; // eax
  int pThis_474; // eax

  if ( Block != nullptr )
  {
    pMem = operator new(0x7Cu);
    v4 = nullptr;
    if ( pMem != nullptr )
    {
      pThis_474 = (*(int (/*thiscall*/ **)(void *, int))(*(uint32_t *)this + 1140))(this, 30);
      v4 = sub_5DB090(pMem, pThis_474);
    }
    (*(void (/*thiscall*/ **)(uint32_t *, void *, void *, uint32_t, uint32_t, int, int))(*v4 + 56))(
      v4,
      Block,
      this,
      0,
      0,
      12,
      -1);
  }
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DB2E0 sub_5DB2E0 —— 召集标挂装门：this+8372 挂件存活（vt+80）且 Block 经 vt+40 类型校验 ==529 且 Block+8352 回指 this
// ·三门齐备才转·0x5DB260（529 为可挂召集标的目标类型码）【推断】
// ------------------------------------------------------------
void /*thiscall*/ sub_5DB2E0(uint32_t *this, void *Block)
{
  int fld_e2093; // eax

  nullsub_1(Block);
  fld_e2093 = *(this + 2093);
  if ( fld_e2093 != 0
    && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2093 + 80))() != 0
    && (*(uint8_t (/*thiscall*/ **)(void *, int))(*(uint32_t *)Block + 40))(Block, 529) != 0
    && *((uint32_t **)Block + 2088) == this )
  {
    sub_5DB260(this, Block);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB330 sub_5DB330 —— 关联容器结点深拷贝（红黑树克隆）：先·sub_5648C0 分配并装配本结点
// ·再以 +21 哨兵色位判分支，递归拷贝 (*pDwArg2) 与 pDwArg2[2] 左右子树；v7[3] 存 this 供回填【推断：vftable 未知的泛型容器】
// ------------------------------------------------------------
void */*thiscall*/ sub_5DB330(void **this, int *pDwArg2, int nArg3)
{
  char v3; // al
  uint32_t *fld_e1; // edi
  int v6; // [esp-8h] [ebp-2Ch]
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  void *Block; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  Block = *(this + 1);
  v3 = *((uint8_t *)pDwArg2 + 21);
  v9 = v7;
  v7[3] = this;
  if ( v3 == 0 )
  {
    fld_e1 = (uint32_t *)sub_5648C0(*(this + 1), nArg3, *(this + 1), pDwArg2 + 3, *((uint8_t *)pDwArg2 + 20));
    if ( *((uint8_t *)Block + 21) != 0 )
      Block = fld_e1;
    v6 = *pDwArg2;
    v10 = 0;
    *fld_e1 = sub_5DB330(v6, fld_e1);
    fld_e1[2] = sub_5DB330(pDwArg2[2], fld_e1);
  }
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB3E0 sub_5DB3E0 —— 全局偏位/相位常量表装载（无 this）：·sub_47E720/·sub_47E9D0 建 5 组表句柄
// ·dword_795850 与 dword_795854(=其*dword_7930D4[0]/100) 为攻方 X/Y 偏位（·0x5DCA10 作插值端点），
// ·dword_9B9338..9B9344 四槽供·0x5DE690/·0x5DE100 的距离与计时门；被 equ_buff 侧调用
// ------------------------------------------------------------
int sub_5DB3E0()
{
  uint32_t *v0; // eax
  uint32_t *v1; // eax
  uint32_t *v2; // eax
  uint32_t *v3; // eax
  uint32_t *v4; // eax
  int result; // eax

  v0 = (uint32_t *)sub_47E720(3, 3);
  dword_795850 = sub_47E9D0(v0, 1u);
  dword_795854 = dword_795850 * dword_7930D4[0] / 100;
  v1 = (uint32_t *)sub_47E720(3, 14);
  dword_9B9338 = sub_47E9D0(v1, 0);
  v2 = (uint32_t *)sub_47E720(3, 14);
  dword_9B933C = sub_47E9D0(v2, 1u);
  v3 = (uint32_t *)sub_47E720(3, 14);
  dword_9B9340 = sub_47E9D0(v3, 2u);
  v4 = (uint32_t *)sub_47E720(3, 42);
  result = sub_47E9D0(v4, 3u);
  dword_9B9344 = result;
  return result;
}



// RTTI cast 目标解算
// ------------------------------------------------------------
// 0x5DB490 sub_5DB490 —— 本体追击弹存在性查询：遍历 this[29] 碰撞对象表 RTTI cast 到 CNChaser
// ·命中条件 vt+688(obj)==2（弹种态）且 vt+684(obj)==this（回指本体）；被·0x5DB810/·0x5DE100/·0x5DE690 作三处前置门
// ------------------------------------------------------------
char /*thiscall*/ sub_5DB490(uint32_t *this)
{
  uint32_t *pThis; // edx
  int fld_e29; // eax
  int v4; // ecx
  int v5; // ebx
  unsigned int v6; // edi
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int pObj2; // eax
  int pObj; // esi

  pThis = this;
  fld_e29 = *(this + 29);
  if ( fld_e29 == 0 )
    return 0;
  v4 = *(uint32_t *)(fld_e29 + 120);
  if ( v4 != 0 )
    v5 = (*(uint32_t *)(fld_e29 + 124) - v4) >> 2;
  else
    v5 = 0;
  v6 = 0;
  if ( v5 <= 0 )
    return 0;
  while ( 1 )
  {
    v7 = pThis[29];
    v8 = *(uint32_t *)(v7 + 120);
    if ( v8 != 0 && v6 < (*(uint32_t *)(v7 + 124) - v8) >> 2 )
      v9 = *(uint32_t *)(v8 + 4 * v6);
    else
      v9 = 0;
    pObj2 = __RTDynamicCast(v9, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNChaser `RTTI Type Descriptor', 0);
    pObj = pObj2;
    if ( pObj2 != 0
      && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 688))(pObj2) == 2
      && (uint32_t *)(*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 684))(pObj) == this )
    {
      break;
    }
    if ( (int)++v6 >= v5 )
      return 0;
    pThis = this;
  }
  return 1;
}



// AI 相位辅助（65L）
// ------------------------------------------------------------
// 0x5DB550 sub_5DB550 —— 双锚位姿同步（v4=0/1 两挂点 this+8416 起步长 4）：vt+120/124/128 取本体坐标
// ·按 vt+152 朝向决定 X 加/减 nArg2，第二锚再补 ±30 错位；逐锚 vt+40(x,y,z) 写位置、vt+28 结点 +84 写朝向布尔、
// vt+92 取包交·sub_4600B0(fld,2,0,pkt) 广播（44/60 为·0x5DE690 case 0xA 传入的界面偏移量）
// ------------------------------------------------------------
void /*thiscall*/ sub_5DB550(uint32_t *this, int nArg2, int nArg3)
{
  int v4; // edi
  int v5; // ebx
  int v6; // eax
  int *v7; // ebx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  void *fld_e29; // ecx
  uint8_t v12[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Block; // [esp+10h] [ebp-24h]
  int v14; // [esp+14h] [ebp-20h]
  int v15; // [esp+18h] [ebp-1Ch]
  int v16; // [esp+1Ch] [ebp-18h]
  int v17; // [esp+20h] [ebp-14h]
  bool v18; // [esp+27h] [ebp-Dh]
  int v19; // [esp+30h] [ebp-4h]

  v4 = 0;
  do
  {
    if ( (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 )
      v5 = nArg2 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this);
    else
      v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 120))(this) - nArg2;
    v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 124))(this);
    v6 = nArg3 + (*(int (/*thiscall*/ **)(uint32_t *))(*this + 128))(this);
    v17 = v6;
    if ( v4 == 1 )
    {
      v5 += (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this) != 0 ? -30 : 30;
      v6 = v17;
    }
    (*(void (/*thiscall*/ **)(uint32_t, int, int, int))(*(uint32_t *)*(this + v4 + 2104) + 40))(
      *(this + v4 + 2104),
      v5,
      v16,
      v6);
    v7 = (int *)*(this + v4 + 2104);
    v8 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 152))(this);
    v9 = *v7;
    v18 = v8 == 0;
    v10 = (*(int (/*thiscall*/ **)(int *))(v9 + 28))(v7);
    *(uint8_t *)(v10 + 84) = v18;
    (*(void (/*thiscall*/ **)(uint32_t, uint8_t *))(*(uint32_t *)*(this + v4 + 2104) + 92))(*(this + v4 + 2104), v12);
    fld_e29 = (void *)*(this + 29);
    v19 = 0;
    sub_4600B0(fld_e29, 2, 0, (int)v12);
    v19 = -1;
    if ( Block != nullptr )
      j__free(Block);
    ++v4;
    Block = nullptr;
    v14 = 0;
    v15 = 0;
  }
  while ( v4 < 2 );
}



// 数据表读数（sub_47EF20, 47L）
// ------------------------------------------------------------
// 0x5DB670 sub_5DB670 —— 攻击段号驱动的伤害系数改写：vt+308 存活 + this+8232 挂件门，vt+1160(this) 取表 vt+348 攻击方档位
// ·sub_41A5E0(14*nArg3 + 档位 - 14) 算槽位；sub_47EF20(2,...) 取千分比后按 (1000-v8)/1000 缩放写 sub_41A590 双字段，
// ·再经·sub_579650 基类虚方法转发；无挂件时退化为 vt+1160(this,nArg2) 后 vt+4 直接转调
// ------------------------------------------------------------
int /*thiscall*/ sub_5DB670(uint32_t *this, int nArg2, int nArg3)
{
  int result; // eax
  int fld_e2058; // eax
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int pObj; // eax
  int v11; // [esp+4h] [ebp-4h]

  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)result != 0 )
  {
    fld_e2058 = *(this + 2058);
    if ( fld_e2058 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2058 + 80))() != 0 )
    {
      v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1160))(this);
      v11 = sub_41A5E0(14 * nArg3 + *(uint32_t *)(v6 + 348) - 14);
      v7 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, int))(*this + 1160))(this, 2, 1, v7);
      v8 = sub_47EF20(2, -1, -1, 11, nArg2);
      sub_41A590(
        14 * nArg3 + *(uint32_t *)(v6 + 348) - 14,
        (int)((uint64_t)(274877907LL * v11 * (1000 - v8)) >> 32) >> 6,
        v11 * (1000 - v8) / 1000);
      sub_579650(nArg2, nArg3);  // 【IRDCharacter__vmt510】
      return sub_41A590(14 * nArg3 + *(uint32_t *)(v6 + 348) - 14, v9, v11);
    }
    else
    {
      result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
      if ( (uint8_t)result != 0 )
      {
        pObj = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, nArg2);
        return (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 4))(pObj, nArg3);
      }
    }
  }
  return result;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DB780 sub_5DB780 —— 关联容器整体重建（红黑树复制）：先·sub_5DB330 克隆源树到 this+4 结点、this+8 复制根
// ·再按 +21 哨兵色位重链最左/最右缓存（空树则自指），供·0x5DC090 初始化与·0x5DC140 赋值复用
// ------------------------------------------------------------
int */*thiscall*/ sub_5DB780(int this, int pArg2)
{
  int fld_4; // edi
  int **fld_42; // edx
  int *result; // eax
  int *v6; // ecx
  int fld_43; // esi
  int **v8; // ecx

  fld_4 = *(uint32_t *)(this + 4);
  *(uint32_t *)(fld_4 + 4) = sub_5DB330((void **)this, *(int **)(*(uint32_t *)(pArg2 + 4) + 4), fld_4);
  *(uint32_t *)(this + 8) = *(uint32_t *)(pArg2 + 8);
  fld_42 = *(int ***)(this + 4);
  result = fld_42[1];
  if ( *((uint8_t *)result + 21) != 0 )
  {
    *fld_42 = (int *)fld_42;
    *(uint32_t *)(*(uint32_t *)(this + 4) + 8) = *(uint32_t *)(this + 4);
  }
  else
  {
    v6 = (int *)*result;
    if ( *(uint8_t *)(*result + 21) == 0 )
    {
      do
      {
        result = v6;
        v6 = (int *)*v6;
      }
      while ( *((uint8_t *)v6 + 21) == 0 );
    }
    *fld_42 = result;
    fld_43 = *(uint32_t *)(this + 4);
    v8 = *(int ***)(fld_43 + 4);
    for ( result = v8[2]; *((uint8_t *)result + 21) == 0; result = (int *)result[2] )
      v8 = (int **)result;
    *(uint32_t *)(fld_43 + 8) = v8;
  }
  return result;
}



// 时钟门 AI（sub_699000, 134L）
// ------------------------------------------------------------
// 0x5DB810 sub_5DB810 —— 三层状态门总调度（vt+308 存活 + this+7730 字节 + switch(this+1639) 主状态镜像2）：
// ·首段 this+8444 时刻与 clock_now(this+36) 比且·sub_5DB490 成立 → vt+1160(this,39) 登记追击态、sub_47E440 刷新；
// ·case 0/11 空白态且 this+8568==-1 时批量 vt+1160(2..18/20/26..31/37/40/41/43/49/50)+unk_737FFC..dword_738020
// ·全表预热（换装/复活后一次性推齐动画段）；case 3/4 由 vt+776(8/16) 判缺段补 3；case 6 待机且 vt+1140(this,42)>0 转 15 施放
// ------------------------------------------------------------
char /*thiscall*/ sub_5DB810(uint32_t *this)
{
  int fld_e1639; // eax
  int *v3; // edi

  LOBYTE(fld_e1639) = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 308))(this);
  if ( (uint8_t)fld_e1639 != 0 )
  {
    sub_4AFEC0(this);
    if ( *(this + 2111) != -1
      && *(this + 2110) != 0
      && sub_699000((int)(this + 9)) < *(this + 2111)  // 【clock_now(clk)】
      && (uint8_t)sub_5DB490(this) != 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 39);
      sub_47E440(1);
    }
    LOBYTE(fld_e1639) = *((uint8_t *)this + 7730);
    if ( (uint8_t)fld_e1639 != 0 )
    {
      fld_e1639 = *(this + 1639);
      switch ( fld_e1639 )
      {
        case 0:
        case 11:
          if ( *(this + 2142) == -1 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 2);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 4);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 5);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 6);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 7);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 9);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 8);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 10);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 11);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 12);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 13);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 14);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 15);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 16);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 17);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 18);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 20);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 26);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 27);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 28);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 29);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 30);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 31);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 37);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 40);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 41);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 43);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 49);
            sub_47E440(1);
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 50);
            sub_47E440(1);
            v3 = (int *)&unk_737FFC;
            do
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, *v3);
              LOBYTE(fld_e1639) = sub_47E440(1);
              ++v3;
            }
            while ( (int)v3 < (int)&dword_738020 );
          }
          else
          {
            byte_9A0358 = 0;
            byte_9A0384 = 0;
            LOBYTE(fld_e1639) = sub_483DF0(0);
          }
          break;
        case 3:
        case 4:
          LOBYTE(fld_e1639) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 8);
          if ( (uint8_t)fld_e1639 == 0 )
          {
            LOBYTE(fld_e1639) = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 776))(this, 16);
            if ( (uint8_t)fld_e1639 == 0 )
            {
              (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 3);
              LOBYTE(fld_e1639) = sub_47E440(1);
            }
          }
          break;
        case 6:
          fld_e1639 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1140))(this, 42);
          if ( fld_e1639 > 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 15);
            LOBYTE(fld_e1639) = sub_47E440(1);
          }
          break;
        default:
          return fld_e1639;
      }
    }
  }
  return fld_e1639;
}


// 语音注册（sub_4015C0; this+8628）
// ------------------------------------------------------------
// 0x5DBBD0 sub_5DBBD0 —— 延时播报登记（this+8592 时刻槽非 -1 时生效）：dword_79D100 时钟未到 nArg3+起点则挂起
// ·this+8596 存到期时刻、sub_4015C0 拷贝 Src 文案、this+8628 置忙位 1；已到则立即 vt+216(this,11)+vt+212 播报；
// ·无论何种分支末尾 this+8592 复位 -1（与·0x5DADE0 清零、·0x5DAF10 到点触发构成三件套）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DBBD0(uint32_t *this, void *Src, int nArg3)
{
  int result; // eax
  int v5; // eax

  result = *(this + 2148);
  if ( result != -1 )
  {
    v5 = nArg3 + result;
    if ( dword_79D100[0] < v5 )
    {
      *(this + 2149) = v5;
      result = sub_4015C0(Src, strlen((const char *)Src));  // 【std::string构造赋值】
      *((uint8_t *)this + 8628) = 1;
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint32_t *, int))(*this + 216))(this, 11);
      result = (*(int (/*thiscall*/ **)(uint32_t *, void *, int, uint32_t, uint32_t))(*this + 212))(this, Src, -1, 0, 0);
    }
    *(this + 2148) = -1;
  }
  return result;
}



// 语音注册（sub_4015C0; STL 断言串为符号文本非资源）
// ------------------------------------------------------------
// 0x5DBC60 sub_5DBC60 —— std::vector 超长断言（noreturn）：构造 length_error 异常对象并 _CxxThrowException
// ·「vector<T> too long」仅 STL 诊断符号文本、非业务资源；由·0x5DBCD0 容量溢出分支转调【推断：MSVC 模板内联外提】
// ------------------------------------------------------------
void /*noreturn*/ sub_5DBC60()
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
  sub_401740(v1);
  pExceptionObject = &std::length_error::`vftable';
  _CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5DBCD0 sub_5DBCD0 —— 指针表 insert_n（三分支自研实现，本工程 vector<T*> 语义）：尾插空间足则
// ··sub_55E7F0 尾段搬移 + ·sub_5DAF70 前段回填 + ·sub_49A9D0 收尾；空隙不足则·sub_523700 就地扩容；
// ·容量不足则 operator new(4*v10) 整块重建后搬移旧块并 j__free；异常路径转·0x5DBC60；被·0x5DC170 逐目标调用
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5DBCD0(int this, int Src, unsigned int uArg3, int *pDwArg4)
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
      sub_5DBC60(this);
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



// AI 相位辅助（112L）
// ------------------------------------------------------------
// 0x5DBEB0 sub_5DBEB0 —— 与·0x5DBCD0 同构（指针表 insert_n 尾部单元素快路径）：唯一差异为容量溢出时转·sub_4DE680
// ·（noreturn 异常抛出）而非本文件内联断言；被·0x5DC730 尾插时择路调用
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5DBEB0(int this, int Src, unsigned int uArg3, int *pDwArg4)
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
      sub_4DE680(this);
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



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC090 sub_5DC090 —— 关联容器初始化（红黑树头结点）：·sub_433AC0 分配哨兵结点头，+21 置 1（黑/哨兵色）
// ·结点 +0/+4/+8 三指针自指成环、this+2 计数清零，末尾·sub_5DB780 灌入 nArg2 源树；被·0x5DC120/·0x5DC780 复用
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DC090(uint32_t *this, int nArg2)
{
  int v3; // eax
  uint32_t v5[8]; // [esp+0h] [ebp-20h] BYREF

  v5[4] = v5;
  v5[3] = this;
  v3 = sub_433AC0(this);
  *(this + 1) = v3;
  *(uint8_t *)(v3 + 21) = 1;
  *(uint32_t *)(*(this + 1) + 4) = *(this + 1);
  *(uint32_t *)*(this + 1) = *(this + 1);
  *(uint32_t *)(*(this + 1) + 8) = *(this + 1);
  *(this + 2) = 0;
  v5[7] = 0;
  sub_5DB780((int)this, nArg2);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DC120 sub_5DC120 —— 与·0x5DC090 同构的转发封装（仅多一层返回 this），供·0x5DC780 目标切换时调用
// ·差异：·0x5DC090 直接构造，本函数经 vt+344 相位切换后被复用以重灌目标树【推断】
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DC120(uint32_t *this, int nArg2)
{
  sub_5DC090(this, nArg2);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DC140 sub_5DC140 —— 关联容器拷贝赋值：this 与 uArg2 不同则·sub_4A3610 释放旧树后·sub_5DB780 依源重建
// ·返回 this 支持链式；被·0x5DC780 在三处状态切换后刷新（this+540 处的相位树）
// ------------------------------------------------------------
uint32_t **/*thiscall*/ sub_5DC140(uint32_t **this, uint32_t **uArg2)
{
  int v2; // edi

  v2 = (int)uArg2;
  if ( this != uArg2 )
  {
    sub_4A3610(&uArg2, **(this + 1), *(this + 1));
    sub_5DB780((int)this, v2);
  }
  return this;
}



// ============================================================
// 【分区 10】追击弹与 AI 群（0x5DC170-0x5DD470）
// 证据：sub_47EF20 数据表读数群、sub_493D00 动画变速换锚、RTTI cast 目标解算群

// RTTI cast 目标解算（89L）
// ------------------------------------------------------------
// 0x5DC170 sub_5DC170 —— 本体所属追击弹收集器（唯一调用者链·0x5DC290/·0x5DC480/·0x5DCE00/·0x5DCF20）：
// ·清空出口参数 pArg2 三字段后遍历 this[29] 碰撞表 RTTI cast CNChaser，命中 vt+688==2 且 vt+684==this 者；
// ·以 obj+1004（序号槽）降序扫描既有结果找插入位，再经·0x5DBCD0(pArg2, 位, 1, &pObj3) 有序插入；返回命中数
// ------------------------------------------------------------
int /*thiscall*/ sub_5DC170(uint32_t *this, int pArg2)
{
  unsigned int v3; // ebx
  uint32_t *pThis; // esi
  int v5; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int pObj; // eax
  uint32_t *v12; // esi
  int v13; // eax
  int pObj2; // eax
  int v15; // esi
  int pObj3; // [esp+Ch] [ebp-Ch] BYREF
  uint32_t *pThis2; // [esp+10h] [ebp-8h]
  int v18; // [esp+14h] [ebp-4h]
  int v19; // [esp+20h] [ebp+8h]

  v3 = 0;
  pThis = this;
  pThis2 = this;
  v18 = 0;
  if ( pArg2 != 0 )
  {
    if ( *(uint32_t *)(pArg2 + 4) != 0 )
      j__free(*(void **)(pArg2 + 4));
    *(uint32_t *)(pArg2 + 4) = 0;
    *(uint32_t *)(pArg2 + 8) = 0;
    *(uint32_t *)(pArg2 + 12) = 0;
  }
  v5 = pThis[29];
  if ( v5 == 0 )
    return 0;
  v7 = *(uint32_t *)(v5 + 120);
  if ( v7 != 0 )
    v19 = (*(uint32_t *)(v5 + 124) - v7) >> 2;
  else
    v19 = 0;
  if ( v19 > 0 )
  {
    while ( 1 )
    {
      v8 = pThis[29];
      v9 = *(uint32_t *)(v8 + 120);
      if ( v9 != 0 && v3 < (*(uint32_t *)(v8 + 124) - v9) >> 2 )
        v10 = *(uint32_t *)(v9 + 4 * v3);
      else
        v10 = 0;
      pObj = __RTDynamicCast(v10, 0, &IRDCollisionObject `RTTI Type Descriptor', &CNChaser `RTTI Type Descriptor', 0);
      v12 = (uint32_t *)pObj;
      pObj3 = pObj;
      if ( pObj != 0 && (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 688))(pObj) == 2 )
      {
        v13 = (*(int (/*thiscall*/ **)(uint32_t *))(*v12 + 684))(v12);
        if ( (uint32_t *)v13 == pThis2 )
        {
          if ( pArg2 != 0 )
          {
            pObj2 = *(uint32_t *)(pArg2 + 4);
            if ( pObj2 != *(uint32_t *)(pArg2 + 8) )
            {
              v15 = v12[251];
              do
              {
                if ( *(uint32_t *)(*(uint32_t *)pObj2 + 1004) >= v15 )
                  break;
                pObj2 += 4;
              }
              while ( pObj2 != *(uint32_t *)(pArg2 + 8) );
            }
            sub_5DBCD0(pArg2, pObj2, 1u, &pObj3);
          }
          ++v18;
        }
      }
      if ( (int)++v3 >= v19 )
        break;
      pThis = pThis2;
    }
  }
  return v18;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC290 sub_5DC290 —— 追击弹序号重排：·sub_5DC170 收集后按数组序回写 obj+1004（序号槽）
// ·obj+960 != 3（非 3 态）者再·sub_617720(obj+984, +988, +992, 序号) 同步三段缓存；被 passive_object 的飘字/挂点链调用
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC290(uint32_t *this)
{
  unsigned int v1; // esi
  int v2; // ebx
  void *Block2; // edi
  int v4; // eax
  bool v5; // zf
  uint8_t v6[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]
  int v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+24h] [ebp-4h]

  v1 = 0;
  Block = nullptr;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  sub_5DC170(this, (int)v6);
  v2 = v8;
  Block2 = Block;
  while ( Block2 != nullptr )
  {
    if ( v1 >= (v2 - (int)Block2) >> 2 )
    {
      j__free(Block2);
      return;
    }
    v4 = *((uint32_t *)Block2 + v1);
    v5 = *(uint32_t *)(v4 + 960) == 3;
    *(uint32_t *)(v4 + 1004) = v1;
    if ( !v5 )
      sub_617720(v4 + 984, v4 + 988, v4 + 992, v1);
    ++v1;
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC330 sub_5DC330 —— 目标筛选与登记（this[29] 碰撞表遍历）：按 vt+40(obj,33) 类型门 + vt+348(obj) 档位 +20 == nArg4 匹配
// ·命中者交 vt+8(this,pObj,0) 求距离，<= nArg3/2 则记入 pObj2 并经·sub_45F8A0 登记；返回 nArg2 原样
// ·被 fighter_skills 的追加打击链调用【推断：nArg4 为攻击方档位、nArg3 为距离上界】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DC330(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  unsigned int v4; // esi
  int fld_e29; // eax
  int v7; // ecx
  int fld_e292; // ecx
  int v9; // edx
  int pObj; // ebx
  uint8_t v12[4]; // [esp+Ch] [ebp-28h] BYREF
  void *Src; // [esp+10h] [ebp-24h]
  int v14; // [esp+14h] [ebp-20h]
  int v15; // [esp+18h] [ebp-1Ch]
  int pObj2; // [esp+1Ch] [ebp-18h] BYREF
  unsigned int v17; // [esp+20h] [ebp-14h]
  int v18; // [esp+24h] [ebp-10h]
  int v19; // [esp+30h] [ebp-4h]

  v4 = 0;
  pObj2 = 0;
  Src = nullptr;
  v14 = 0;
  v15 = 0;
  fld_e29 = *(this + 29);
  v19 = 0;
  if ( fld_e29 != 0 )
  {
    v7 = *(uint32_t *)(fld_e29 + 120);
    v18 = v7 != 0 ? (*(uint32_t *)(fld_e29 + 124) - v7) >> 2 : 0;
    v17 = 0;
    if ( v18 > 0 )
    {
      do
      {
        fld_e292 = *(this + 29);
        v9 = *(uint32_t *)(fld_e292 + 120);
        if ( v9 != 0 && v4 < (*(uint32_t *)(fld_e292 + 124) - v9) >> 2 )
          pObj = *(uint32_t *)(v9 + 4 * v4);
        else
          pObj = 0;
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 40))(pObj, 33) != 0
          && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 348))(pObj) + 20) == nArg4 )
        {
          pObj2 = (*(int (/*thiscall*/ **)(uint32_t *, int, uint32_t))(*this + 8))(this, pObj, 0);
          if ( pObj2 <= nArg3 / 2 )
          {
            pObj2 = pObj;
            sub_45F8A0(Src, 1, (int)&pObj2);
            v4 = v17;
          }
        }
        v17 = ++v4;
      }
      while ( (int)v4 < v18 );
    }
  }
  sub_4982B0(v12);
  return nArg2;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC480 sub_5DC480 —— 追击弹发射（vt+308 存活门）：·sub_5DC170 收集现存弹，数量 < vt+1160(this,5) 表值·sub_47E9D0(vt,1) 才发射
// ·序号取末弹 +1004+1（pszArg3 非 0 再加 10000 偏置），经 vt+580(this, dword_737FB0[nArg2], 序号, ...) 发射调用；
// ·满额则经 dword_8F8528[7] + ·sub_422E70(1205) + ·sub_43BEE0 挂提示；nArg2 为 dword_737FB0 弹种表索引
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC480(uint32_t *this, int nArg2, char pszArg3)
{
  unsigned int v4; // edi
  void *Block2; // esi
  uint32_t *v6; // eax
  uint32_t *v7; // edi
  int v8; // eax
  int v9; // ecx
  uint8_t v10[4]; // [esp+4h] [ebp-1Ch] BYREF
  void *Block; // [esp+8h] [ebp-18h]
  int v12; // [esp+Ch] [ebp-14h]
  int v13; // [esp+10h] [ebp-10h]
  int v14; // [esp+1Ch] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*this + 308))(this) != 0 )
  {
    v4 = 0;
    Block = nullptr;
    v12 = 0;
    v13 = 0;
    v14 = 0;
    sub_5DC170(this, (int)v10);
    Block2 = Block;
    if ( Block != nullptr )
      v4 = (v12 - (int)Block) >> 2;
    v6 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*this + 1160))(this, 5);
    if ( v4 < sub_47E9D0(v6, 1u) )
    {
      v9 = 0;
      if ( Block2 != nullptr && (v12 - (int)Block2) >> 2 != 0 )
        v9 = *(uint32_t *)(*(uint32_t *)(v12 - 4) + 1004) + 1;
      if ( pszArg3 != 0 )
        v9 += 10000;
      (*(void (/*thiscall*/ **)(uint32_t *, int, int, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, uint32_t, uint32_t))(*this + 580))(
        this,
        dword_737FB0[nArg2],
        v9,
        0,
        0,
        0,
        0,
        0,
        1,
        0,
        0,
        0);
    }
    else
    {
      v7 = *((uint32_t **)dword_8F8528 + 7);
      v8 = sub_422E70(1205);
      sub_43BEE0(v7, v8, -6567706, 0, -1);
    }
    if ( Block2 != nullptr )
      j__free(Block2);
  }
}



// 数据表读数（sub_47EF20, 49L）
// ------------------------------------------------------------
// 0x5DC590 sub_5DC590 —— 追击弹发射概率门：vt+1160(this, this+8244) 取上限表、vt+1140 取当前并发数（<=1 归 1）
// ··sub_5DC170 计数 < ·sub_47E9D0(表,1) 时再判 vt+752(this) >= ·sub_47EA80(并发) 且 rand()%1000 < nArg2（千分概率）；
// ·通过则 vt+744 扣减差值、vt+1160(this,40,1,vt+1140) 登记、sub_47EF20(40,...) 取参后·sub_5DC480 发射（nRand 再判一次千分）
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC590(int *this, int nArg2)
{
  uint32_t *fld_e2061; // edi
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // edi
  int v8; // eax
  int v9; // eax
  int v10; // edi
  int fld_e20613; // eax
  uint32_t *v12; // ecx
  char nRand; // [esp-Ch] [ebp-14h]
  int fld_e20612; // [esp+4h] [ebp-4h]

  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    sub_432FA0();
    fld_e2061 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1160))(this, *(this + 2061));
    if ( (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 2061)) <= 1 )
      fld_e20612 = 1;
    else
      fld_e20612 = (*(int (/*thiscall*/ **)(int *, uint32_t))(*this + 1140))(this, *(this + 2061));
    v4 = sub_5DC170(this, 0);
    if ( v4 < sub_47E9D0(fld_e2061, 1u) )
    {
      v5 = sub_47EA80(fld_e20612);
      if ( (*(int (/*thiscall*/ **)(int *))(*this + 752))(this) >= v5 && rand() % 1000 < nArg2 )
      {
        v6 = *this;
        v7 = sub_47EA80(fld_e20612);
        v8 = (*(int (/*thiscall*/ **)(int *))(*this + 752))(this);
        (*(void (/*thiscall*/ **)(int *, int))(v6 + 744))(this, v8 - v7);
        v9 = (*(int (/*thiscall*/ **)(int *))(*this + 1140))(this);
        (*(void (/*thiscall*/ **)(int *, int, int, int))(*this + 1160))(this, 40, 1, v9);
        v10 = sub_47EF20(40, -1, -1, 11, 1);
        nRand = rand() % 1000 < v10;
        fld_e20613 = sub_5DA920(*(this + 2061));
        sub_5DC480(v12, fld_e20613, nRand);
      }
    }
  }
}



// 数据表读数（sub_47EF20, 21L）
// ------------------------------------------------------------
// 0x5DC6D0 sub_5DC6D0 —— 发射概率外部入口：this+8240 挂件存活 + nArg3>0 + nArg2<=5 时
// ·vt+1140(this,40,-1) 取参交 sub_47EF20(40,4,参数,-1,11) 折算后转·sub_5DC590(this, v5) 走概率门
// ------------------------------------------------------------
void /*thiscall*/ sub_5DC6D0(int *this, int nArg2, int nArg3)
{
  int fld_e2060; // eax
  int v5; // eax
  int v6; // [esp-Ch] [ebp-10h]

  fld_e2060 = *(this + 2060);
  if ( fld_e2060 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_e2060 + 80))() != 0 && nArg3 > 0 && nArg2 <= 5 )
  {
    v6 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 40, -1);
    (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
    v5 = sub_47EF20(40, 4, v6, -1, 11);
    sub_5DC590(this, v5);
  }
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DC730 sub_5DC730 —— 指针表尾插快路径封装（this[1] 基址、this[2] 游标、this[3] 容量）：this[1]==0
// ·或游标已达容量时转·sub_5DBEB0 走扩容；否则就地写入 *pDwArg2 并游标 +1；被·0x5DD040 在收集结果后调用
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_5DC730(int *this, int *pDwArg2)
{
  int fld_e1; // esi
  unsigned int fld_e2; // edx
  int *fld_e22; // eax
  unsigned int result; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 2;
  else
    fld_e2 = 0;
  if ( fld_e1 == 0 || fld_e2 >= (*(this + 3) - fld_e1) >> 2 )
    return sub_5DBEB0((int)this, *(this + 2), 1u, pDwArg2);
  fld_e22 = (int *)*(this + 2);
  *fld_e22 = *pDwArg2;
  result = (unsigned int)(fld_e22 + 1);
  *(this + 2) = result;
  return result;
}



// AI 相位辅助（104L）
// ------------------------------------------------------------
// 0x5DC780 sub_5DC780 —— 敌方挂件相位切换（三段）：this+6556==8 攻击态且·sub_41A5E0(this+7028)==0 且 this+8216==-1 时
// ·以·sub_445870(37712398,10000)<100 的万分比触发，this+8224 置 9.0、vt+672(this,3) 与·sub_4AED60(9.0) 起效果；
// ·this+6556==20 军团态且 this+8516==20 时按·sub_4E4630 敌我关系在盟/敌分支置 this+8528 为 6/4/5 并·sub_5DC090/·sub_5DC120 切树，
// ·再 vt+344 定相位、th+139+152*相位 取偏移、sub_47EFD0 与·sub_4A3790 结算并写 this+388/396/397 三字段
// ------------------------------------------------------------
int /*thiscall*/ sub_5DC780(float *this, int nArg2, int nArg3, int nArg4)
{
  int v5; // eax
  int v6; // edx
  char *pThis_488; // edi
  int pThis_474; // ebx
  int pThis_184; // eax
  int pThis_63; // edx
  int v11; // eax
  int v12; // eax
  int pThis_632; // eax
  uint8_t *v14; // ecx
  char v15; // al
  int pThis_854; // ecx
  float v17; // edx
  float v18; // edx
  int pThis_8B; // [esp-8h] [ebp-38h]
  int pThis_8B2; // [esp-8h] [ebp-38h]
  int pThis_8B3; // [esp-8h] [ebp-38h]
  uint8_t v23[12]; // [esp+8h] [ebp-28h] BYREF
  uint8_t v24[12]; // [esp+14h] [ebp-1Ch] BYREF
  int v25; // [esp+20h] [ebp-10h]
  int v26; // [esp+2Ch] [ebp-4h]

  if ( *((uint32_t *)this + 1639) == 8 && sub_41A5E0(this + 1757) == 0 && *((uint32_t *)this + 2054) == -1 )
  {
    v25 = sub_445870(37712398, 10000);
    if ( (double)v25 < 100.0 )
    {
      v5 = *(uint32_t *)this;
      *(this + 2056) = 9.0;
      (*(void (/*thiscall*/ **)(float *, int))(v5 + 672))(this, 3);
      sub_4AED60(9.0);
    }
  }
  if ( *((uint32_t *)this + 1639) == 20 && *((uint32_t *)this + 2129) == 20 )
  {
    if ( (uint8_t)sub_4E4630(nArg2) != 0 )
    {
      if ( *((uint32_t *)this + 2132) != 6 )
      {
        *((uint32_t *)this + 2132) = 6;
        sub_5DC090(this + 135);
        v6 = *(uint32_t *)this;
        pThis_8B = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);
        v26 = 0;
        (*(void (/*thiscall*/ **)(float *, int))(v6 + 344))(this, pThis_8B);
        sub_5DC140(v24);
        pThis_488 = (char *)(*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 1160))(this, 20);
        pThis_474 = (*(int (/*thiscall*/ **)(float *, int))(*(uint32_t *)this + 1140))(this, 20);
        pThis_184 = (*(int (/*thiscall*/ **)(float *))(*(uint32_t *)this + 388))(this);
        pThis_63 = sub_47EFD0(pThis_488, COERCE_FLOAT(8), pThis_474, pThis_184, pThis_184, 11) - 100 + *((uint32_t *)this + 99);
        v11 = *(uint32_t *)this;
        *((uint32_t *)this + 99) = pThis_63;
        v12 = (*(int (/*thiscall*/ **)(float *))(v11 + 388))(this);
        pThis_632 = 100 * sub_47EFD0(pThis_488, COERCE_FLOAT(9), pThis_474, v12, v12, 0) / (*((uint32_t *)this + 99) + 100);
        v14 = v24;
        *(this + 97) = (double)pThis_632 + *(this + 97);
LABEL_16:
        v26 = -1;
        sub_4A3790(v14);
      }
    }
    else
    {
      v15 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529);
      pThis_854 = *((uint32_t *)this + 2132);
      if ( v15 != 0 )
      {
        if ( pThis_854 != 4 )
        {
          *((uint32_t *)this + 2132) = 4;
          sub_5DC120(this + 135);
          v17 = *this;
          pThis_8B2 = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);
          v26 = 1;
          (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v17) + 344))(this, pThis_8B2);
          sub_5DC140(v24);
          v14 = v24;
          goto LABEL_16;
        }
      }
      else if ( pThis_854 != 5 )
      {
        *((uint32_t *)this + 2132) = 5;
        sub_5DC120(this + 135);
        v18 = *this;
        pThis_8B3 = *((uint32_t *)this + 139) + 152 * *((uint32_t *)this + 2132);
        v26 = 2;
        (*(void (/*thiscall*/ **)(float *, int))(LODWORD(v18) + 344))(this, pThis_8B3);
        sub_5DC140(v23);
        v14 = v23;
        goto LABEL_16;
      }
    }
  }
  return 0;
}



// 数据表+插值 AI（sub_47EF20+sub_4049C0, 175L）
// ------------------------------------------------------------
// 0x5DCA10 sub_5DCA10 —— 位移插值推进（this+6556 为 4/3 且 vt+724 静止门）：vt+776(8/16) 判缺段后 vt+1160(this,3, 缺段)
// ·+sub_47E440，再 vt+1312(this,3) 反击门放行；vt+1132(this,0,nArg3,nArg2) 与 (this,1) 取两组方向码（7=4 && 8=4 时经·sub_432E50 归一）；
// ·主体以 dword_795850/795854 偏位补偿起止点后·sub_4049C0 逐格双轴 lerp，每步 vt+136 试探碰撞即中断；
// ·末尾 sub_430C80 六次登记（3/起点/终点/表值/sub_47E9D0/·sub_47EF20 抽参）后 vt+560(this,17,包) 提交相位
// ------------------------------------------------------------
void /*userpurge*/ sub_5DCA10(uint32_t *pArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int nArg4)
{
  int v5; // eax
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // edi
  float v13; // eax
  float v14; // edi
  float v15; // eax
  int v16; // eax
  int v17; // edx
  int v18; // edi
  int v19; // eax
  int v20; // edx
  int v21; // ebx
  int v22; // edi
  uint64_t v23; // rax
  int v24; // ebx
  uint64_t v25; // rax
  int v26; // edi
  bool v27; // cc
  uint32_t *v28; // eax
  int nArg42; // [esp-10h] [ebp-50h]
  char v30; // [esp+0h] [ebp-40h]
  uint8_t v31[4]; // [esp+4h] [ebp-3Ch] BYREF
  void *Block; // [esp+8h] [ebp-38h]
  void *Src; // [esp+Ch] [ebp-34h]
  int v34; // [esp+10h] [ebp-30h]
  int v35; // [esp+14h] [ebp-2Ch] BYREF
  float v36; // [esp+18h] [ebp-28h]
  int v37; // [esp+1Ch] [ebp-24h] BYREF
  int v38; // [esp+20h] [ebp-20h]
  float v39; // [esp+24h] [ebp-1Ch]
  int v40; // [esp+28h] [ebp-18h] BYREF
  float v41; // [esp+2Ch] [ebp-14h]
  float v42; // [esp+30h] [ebp-10h]
  int v43; // [esp+3Ch] [ebp-4h]

  v5 = pArg1[1639];
  if ( v5 != 4 && v5 != 3 || (*(uint8_t (/*thiscall*/ **)(uint32_t *))(*pArg1 + 724))(pArg1) != 0 )
    return;
  v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 776))(pArg1, 8);
  LOBYTE(v6) = (uint8_t)v6 == 0 && (uint8_t)(v6 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 776))(pArg1, 16)) == 0;
  (*(void (/*thiscall*/ **)(uint32_t *, int, int))(*pArg1 + 1160))(pArg1, 3, v6);
  sub_47E440(v30);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1312))(pArg1, 3) == 0 )
    return;
  v7 = (*(int (/*thiscall*/ **)(uint32_t *, uint32_t, int, int))(*pArg1 + 1132))(pArg1, 0, nArg3, nArg2);
  v8 = (*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1132))(pArg1, 1);
  v37 = v8;
  if ( v7 == 4 && v8 == 4 )
  {
    v9 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 152))(pArg1);
    v7 = sub_432E50(v9);
  }
  *(float *)&v10 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1));
  v11 = *pArg1;
  v12 = v10;
  v41 = *(float *)&v10;
  v13 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v11 + 124))(pArg1));
  v42 = v13;
  if ( v7 != 0 )
  {
    if ( v7 != 1 )
      goto LABEL_17;
    LODWORD(v14) = dword_795850 + v12;
  }
  else
  {
    LODWORD(v14) = v12 - dword_795850;
  }
  v41 = v14;
LABEL_17:
  if ( v37 == 2 )
  {
    LODWORD(v15) = LODWORD(v13) - dword_795854;
LABEL_21:
    v42 = v15;
    goto LABEL_22;
  }
  if ( v37 == 3 )
  {
    LODWORD(v15) = dword_795854 + LODWORD(v13);
    goto LABEL_21;
  }
LABEL_22:
  v16 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
  v17 = *pArg1;
  v18 = v16;
  v38 = v16;
  v39 = COERCE_FLOAT((*(int (/*thiscall*/ **)(uint32_t *))(v17 + 124))(pArg1));
  v19 = (*(int (/*thiscall*/ **)(uint32_t *))(*pArg1 + 120))(pArg1);
  v20 = *pArg1;
  v37 = v19;
  v40 = (*(int (/*thiscall*/ **)(uint32_t *))(v20 + 124))(pArg1);
  if ( v7 == 4 )
  {
    v24 = abs32(LODWORD(v39) - LODWORD(v42));
    v38 = 0;
    if ( v24 >= 0 )
    {
      v42 = (float)SLODWORD(v42);
      v39 = (float)SLODWORD(v39);
      do
      {
        v25 = (uint64_t)sub_4049C0(v39, v42, v38, v24);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        v26 = v25;
        if ( (*(uint8_t (/*fastcall*/ **)(uint32_t *, uint32_t, float, uint32_t, uint32_t))(*pArg1 + 136))(
               pArg1,
               HIDWORD(v25),
               COERCE_FLOAT(LODWORD(v41)),
               v25,
               0) == 0 )
          break;
        v27 = v38 + 1 <= v24;
        v40 = v26;
        ++v38;
      }
      while ( v27 );
    }
  }
  else
  {
    v21 = 0;
    v22 = abs32(v18 - LODWORD(v41));
    if ( v22 >= 0 )
    {
      v41 = (float)SLODWORD(v41);
      v36 = (float)v38;
      v42 = (float)SLODWORD(v42);
      v39 = (float)SLODWORD(v39);
      do
      {
        v38 = (uint64_t)sub_4049C0(v36, v41, v21, v22);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        v23 = (uint64_t)sub_4049C0(v39, v42, v21, v22);  // 【插值与通用辅助（lerp 源头 / 字符串安全拷贝 / rdtsc 高精度时钟族）】
        HIDWORD(v23) = *pArg1;
        v35 = v23;
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t *, int, uint32_t, uint32_t))(HIDWORD(v23) + 136))(pArg1, v38, v23, 0) == 0 )
          break;
        ++v21;
        v37 = v38;
        v40 = v35;
      }
      while ( v21 <= v22 );
    }
  }
  Block = nullptr;
  Src = nullptr;
  v34 = 0;
  v43 = 0;
  v35 = 3;
  sub_430C80(nullptr, 1, (int)&v35);
  sub_430C80(nullptr, 1, (int)&v37);
  sub_430C80(nullptr, 1, (int)&v40);
  v28 = (uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1160))(pArg1, 3);
  v35 = sub_47E9D0(v28, 0);
  sub_430C80(nullptr, 1, (int)&v35);
  nArg42 = nArg4;
  (*(void (/*thiscall*/ **)(uint32_t *, int))(*pArg1 + 1160))(pArg1, 3);
  v35 = sub_47EF20(0, nArg42, -1, -1, 11);
  sub_430C80(nullptr, 1, (int)&v35);
  sub_430C80(nullptr, 1, (int)&nArg4);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint8_t *))(*pArg1 + 560))(pArg1, 17, v31);
  if ( Block != nullptr )
    j__free(Block);
}


// 参数打包 AI（sub_431230）
// ------------------------------------------------------------
// 0x5DCE00 sub_5DCE00 —— 追击弹命中播报：nArg2 非 0 时·sub_5DC170 收集现存弹，取首弹 obj+980（弹种索引）查 off_79583C 文案表
// ·交 vt+212 播报，再判该弹 vt+308 存活后以 sub_431230 三次打包（vt+48/vt+52 坐标 + 常量 400）经 vt+560(弹,3,包,0,0) 下发相位
// ------------------------------------------------------------
void /*thiscall*/ sub_5DCE00(uint32_t *this, int nArg2)
{
  int pObj; // edi
  uint32_t *pObj22; // esi
  int v4; // eax
  uint8_t v5[4]; // [esp+8h] [ebp-30h] BYREF
  void *pObj2; // [esp+Ch] [ebp-2Ch]
  int v7; // [esp+10h] [ebp-28h]
  int v8; // [esp+14h] [ebp-24h]
  uint8_t v9[4]; // [esp+18h] [ebp-20h] BYREF
  void *Block; // [esp+1Ch] [ebp-1Ch]
  int v11; // [esp+20h] [ebp-18h]
  int v12; // [esp+24h] [ebp-14h]
  uint32_t *pThis; // [esp+28h] [ebp-10h]
  int v14; // [esp+34h] [ebp-4h]

  pObj = nArg2;
  pThis = this;
  if ( nArg2 != 0 )
  {
    pObj2 = nullptr;
    v7 = 0;
    v8 = 0;
    v14 = 0;
    sub_5DC170(this, (int)v5);
    pObj22 = pObj2;
    if ( pObj2 != nullptr )
    {
      if ( (v7 - (int)pObj2) >> 2 != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *, char *, int, uint32_t, uint32_t))(*pThis + 212))(
          pThis,
          off_79583C[*(uint32_t *)(*(uint32_t *)pObj2 + 980)],
          -1,
          0,
          0);
        if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*pObj22 + 308))(*pObj22) != 0 )
        {
          Block = nullptr;
          v11 = 0;
          v12 = 0;
          v4 = *(uint32_t *)pObj;
          LOBYTE(v14) = 1;
          nArg2 = (*(int (/*thiscall*/ **)(int))(v4 + 48))(pObj);
          sub_431230((int)v9, &nArg2);
          nArg2 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 52))(pObj);
          sub_431230((int)v9, &nArg2);
          nArg2 = 400;
          sub_431230((int)v9, &nArg2);
          (*(void (/*thiscall*/ **)(uint32_t, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)*pObj22 + 560))(*pObj22, 3, v9, 0, 0);
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          v11 = 0;
          v12 = 0;
        }
      }
      j__free(pObj22);
    }
  }
}



// 追击弹爆炸：CHASER_EXPLOSION 播报（81L）
// ------------------------------------------------------------
// 0x5DCF20 sub_5DCF20 —— 追击弹爆炸总清理：·sub_5DC170 收集后逐弹（vt+308 存活者）以 sub_430C80 登记 v4 偏移
// ·（步长 +80）再 vt+560(弹,4,包,0,0) 触发第 4 相位；全部处理完 vt+212 播报 CHASER_EXPLOSION 并统一 j__free 释放收集块
// ------------------------------------------------------------
void /*thiscall*/ sub_5DCF20(uint32_t *this)
{
  uint32_t *Block2; // esi
  unsigned int v2; // eax
  unsigned int v3; // ecx
  int v4; // edi
  int pObj; // esi
  uint8_t v6[4]; // [esp+8h] [ebp-3Ch] BYREF
  void *Block; // [esp+Ch] [ebp-38h]
  int v8; // [esp+10h] [ebp-34h]
  int v9; // [esp+14h] [ebp-30h]
  uint8_t v10[4]; // [esp+18h] [ebp-2Ch] BYREF
  void *v11; // [esp+1Ch] [ebp-28h]
  int v12; // [esp+20h] [ebp-24h]
  int v13; // [esp+24h] [ebp-20h]
  uint32_t *pThis; // [esp+28h] [ebp-1Ch]
  unsigned int v15; // [esp+2Ch] [ebp-18h]
  int v16; // [esp+30h] [ebp-14h] BYREF
  int v17; // [esp+34h] [ebp-10h]
  int v18; // [esp+40h] [ebp-4h]

  pThis = this;
  Block = nullptr;
  v8 = 0;
  v9 = 0;
  v18 = 0;
  sub_5DC170(this, (int)v6);
  Block2 = Block;
  if ( Block != nullptr )
  {
    v2 = (v8 - (int)Block) >> 2;
    v15 = v2;
    if ( v2 != 0 )
    {
      v3 = 0;
      v17 = 0;
      v4 = 0;
      while ( v3 < v2 )
      {
        pObj = Block2[v3];
        if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 308))(pObj) != 0 )
        {
          v11 = nullptr;
          v12 = 0;
          v13 = 0;
          LOBYTE(v18) = 1;
          v16 = v4;
          sub_430C80(nullptr, 1, (int)&v16);
          (*(void (/*thiscall*/ **)(int, int, uint8_t *, uint32_t, uint32_t))(*(uint32_t *)pObj + 560))(pObj, 4, v10, 0, 0);
          LOBYTE(v18) = 0;
          if ( v11 != nullptr )
            j__free(v11);
          v11 = nullptr;
          v12 = 0;
          v13 = 0;
        }
        Block2 = Block;
        v2 = v15;
        v3 = ++v17;
        v4 += 80;
      }
      (*(void (/*thiscall*/ **)(uint32_t *, const char *, int, uint32_t, uint32_t))(*pThis + 212))(
        pThis,
        "CHASER_EXPLOSION",
        -1,
        0,
        0);
      j__free(Block2);
    }
    else
    {
      j__free(Block);
    }
  }
}



// RTTI cast 大型 AI（139L）
// ------------------------------------------------------------
// 0x5DD040 sub_5DD040 —— 召唤物/弹体筛选收集（this[29] 碰撞表）：先按 pArg3 清空出口表，nArg2 命中 dword_738020..738030
// ·召唤种表则 v29=1；逐项先 RTTI cast IRDMonster，回指 this[2088]==this 且 vt+840 非 13/5 者取 vt+340 码；
// ·否则 cast CNSummonMonsterWithEffect，vt+576(obj)==this 时取 obj+973 半字码；码匹配 nArg2（或 0xFFFF 通配）则计数 +1
// ·并经·0x5DC730 登记（仅当 v29 且 pszArg4 时再查表）；返回命中数；被·0x5DD700 以 0xFFFF 调用
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD040(uint32_t *this, int nArg2, int pArg3, char pszArg4)
{
  uint32_t *pThis; // esi
  int fld_e29; // eax
  unsigned int v6; // ebx
  int *v8; // eax
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // eax
  uint32_t *v15; // eax
  uint32_t *v16; // edi
  int v17; // ecx
  int v18; // ecx
  int v19; // edx
  int v20; // eax
  int pObj; // eax
  int pObj2; // esi
  int v23; // eax
  int *v24; // eax
  uint32_t *v25; // [esp+8h] [ebp-14h] BYREF
  int v26; // [esp+Ch] [ebp-10h]
  int v27; // [esp+10h] [ebp-Ch]
  uint32_t *pThis2; // [esp+14h] [ebp-8h]
  char v29; // [esp+1Bh] [ebp-1h]

  pThis = this;
  fld_e29 = *(this + 29);
  v6 = 0;
  pThis2 = this;
  if ( fld_e29 == 0 )
    return 0;
  if ( pArg3 != 0 )
  {
    if ( *(uint32_t *)(pArg3 + 4) != 0 )
      j__free(*(void **)(pArg3 + 4));
    *(uint32_t *)(pArg3 + 4) = 0;
    *(uint32_t *)(pArg3 + 8) = 0;
    *(uint32_t *)(pArg3 + 12) = 0;
  }
  v8 = &dword_738020;
  while ( nArg2 != *v8 )
  {
    if ( (int)++v8 >= (int)&dword_738030 )
    {
      v29 = 0;
      goto LABEL_11;
    }
  }
  v29 = 1;
LABEL_11:
  v9 = pThis[29];
  v10 = *(uint32_t *)(v9 + 120);
  v11 = v9 + 116;
  v26 = 0;
  if ( v10 != 0 )
    v27 = (*(uint32_t *)(v11 + 8) - v10) >> 2;
  else
    v27 = 0;
  if ( v27 > 0 )
  {
    do
    {
      v12 = pThis[29];
      v13 = *(uint32_t *)(v12 + 120);
      if ( v13 != 0 && v6 < (*(uint32_t *)(v12 + 124) - v13) >> 2 )
        v14 = *(uint32_t *)(v13 + 4 * v6);
      else
        v14 = 0;
      v15 = (uint32_t *)__RTDynamicCast(
                        v14,
                        0,
                        &IRDCollisionObject `RTTI Type Descriptor',
                        &IRDMonster `RTTI Type Descriptor',
                        0);
      v16 = v15;
      v25 = v15;
      if ( v15 != nullptr )
      {
        if ( (uint32_t *)v15[2088] != pThis
          || (*(int (/*thiscall*/ **)(uint32_t *))(*v15 + 840))(v15) == 13
          || (*(int (/*thiscall*/ **)(uint32_t *))(*v16 + 840))(v16) == 5 )
        {
          goto LABEL_44;
        }
        v17 = *(uint32_t *)(*(int (/*thiscall*/ **)(uint32_t *))(*v16 + 340))(v16);
      }
      else
      {
        v18 = pThis[29];
        v19 = *(uint32_t *)(v18 + 120);
        if ( v19 != 0 && v6 < (*(uint32_t *)(v18 + 124) - v19) >> 2 )
          v20 = *(uint32_t *)(v19 + 4 * v6);
        else
          v20 = 0;
        pObj = __RTDynamicCast(
                v20,
                0,
                &IRDCollisionObject `RTTI Type Descriptor',
                &CNSummonMonsterWithEffect `RTTI Type Descriptor',
                0);
        pObj2 = pObj;
        if ( pObj == 0 || (uint32_t *)(v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 576))(pObj)) != pThis2 )
        {
          pThis = pThis2;
          goto LABEL_44;
        }
        v17 = *(uint16_t *)(pObj2 + 973);
        pThis = pThis2;
      }
      if ( nArg2 == 0xFFFF || nArg2 == v17 )
        goto LABEL_40;
      if ( v29 != 0 && pszArg4 != 0 )
      {
        v24 = &dword_738020;
        while ( v17 != *v24 )
        {
          if ( (int)++v24 >= (int)&dword_738030 )
            goto LABEL_44;
        }
LABEL_40:
        ++v26;
        if ( pArg3 != 0 && v16 != nullptr )
          sub_5DC730(&v25);
      }
LABEL_44:
      ++v6;
    }
    while ( (int)v6 < v27 );
  }
  return v26;
}


// AI 字段访问
// ------------------------------------------------------------
// 0x5DD210 sub_5DD210 —— CNSummonMonsterAura 构造（召唤怪光环区）：·sub_5910D0 基类 CNRDAuraMaster 构造(0,18,250,1)
// ·置 CNSummonMonsterAura vftable、·sub_64EE80 装配、·sub_64F170 装载 SummonMonsterAuraArea 资源；被·0x5DD810 case 48 实例化
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DD210(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  sub_5910D0(this, 0, 18, 250, 1);
  *this = &CNSummonMonsterAura::`vftable';
  sub_64EE80(this);
  sub_64F170(nArg2, nArg3, nArg4);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD280 sub_5DD280 —— 三字段直写 setter（this+84/+128/+132 依次内存 nArg2/nArg3/nArg4）；本文件内无调用点【推断：vtable 挂接】
// ·与·0x5DD210 同属 CNSummonMonsterAura 族，疑似召唤区参数配置接口【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD280(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  *(this + 21) = nArg2;
  *(this + 32) = nArg3;
  *(this + 33) = nArg4;
  return nArg4;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD2A0 sub_5DD2A0 —— CNSummonMonsterAura 标量删除器（转调·sub_5DD2D0 析构，bit0 置位才 j__free）
// ·与·0x5DD3B0 同构，对应·0x5DD210/·0x5DD320 两构造
// ------------------------------------------------------------
void */*thiscall*/ sub_5DD2A0(void *Block, char pszArg2)
{
  sub_5DD2D0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD2D0 sub_5DD2D0 —— CNSummonMonsterAura 析构：置 CNSummonMonsterAura vftable、·sub_64F1F0 召唤受击收尾
// ·末尾转·sub_591190 CNRDAuraMaster 基类析构（本组析构统一尾调）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD2D0(char *this)
{
  *(uint32_t *)this = &CNSummonMonsterAura::`vftable';
  sub_64F1F0();
  return sub_591190(this);
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DD320 sub_5DD320 —— CNTargetIt 构造（标记球挂件）：·sub_5910D0 基类构造(0,18,250,0) → 置 CNTargetIt vftable
// ··sub_607240/·sub_607280 初始化 this+136 双子对象、this+160/164/168 三指针清零、·sub_64F230 装配、·sub_64FB80 装载 Character/Mage/Effect 资源
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_5DD320(uint32_t *this)
{
  sub_5910D0(this, 0, 18, 250, 0);
  *this = &CNTargetIt::`vftable';
  sub_607240(this + 34);
  sub_607280(this + 34);
  *(this + 40) = 0;
  *(this + 41) = 0;
  *(this + 42) = 0;
  sub_64F230(this);
  sub_64FB80(this);
  return this;
}



// AI 字段访问
// ------------------------------------------------------------
// 0x5DD3B0 sub_5DD3B0 —— CNTargetIt 标量删除器（转调·sub_5DD3E0 析构，bit0 置位才 j__free）
// ·与·0x5DD2A0 同构，对应 new(0xB0) 的 CNTargetIt 块释放【推断】
// ------------------------------------------------------------
void */*thiscall*/ sub_5DD3B0(void *Block, char pszArg2)
{
  sub_5DD3E0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// AI 相位辅助
// ------------------------------------------------------------
// 0x5DD3E0 sub_5DD3E0 —— CNTargetIt 析构：置 CNTargetIt vftable、·sub_64FC00 目标受击收尾
// ·释放 this+160 指针块并三清 +160/164/168，nullsub_3(this+136) 收末，末尾转·sub_591190 CNRDAuraMaster 基类析构
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD3E0(int this)
{
  *(uint32_t *)this = &CNTargetIt::`vftable';
  sub_64FC00();
  if ( *(uint32_t *)(this + 160) != 0 )
    j__free(*(void **)(this + 160));
  *(uint32_t *)(this + 160) = 0;
  *(uint32_t *)(this + 164) = 0;
  *(uint32_t *)(this + 168) = 0;
  nullsub_3(this + 136);
  return sub_591190((char *)this);
}



// ============================================================
// 【分区 11】白魔 WZ（大型主状态机）（0x5DD470-0x5E0000）
// 证据：WZ_JUMP_ATK/WZ_JUMP/WZ_BACKSTEP/WZ_DASH_ATK/WZ_DASH_HIT/WZ_DIE/WZ_NOMANA +
//       R_WZ_DMG/R_WZ_THROW/R_WZ_LESSON_START、Effect/Particle/HandHit{1,2}.ptl、
//       Effect/Animation/WhipToMonsterHit.ani 鞭击、FollowMeCast.ani/PRICK/HEAVEN_HIT、
//       ★ 0x5DE690（1082L 本工程最大函数）= switch(this+6556) 大状态 6/10/16-21 分派

// 白魔技能语音组：WZ_JUMP_ATK/R_WZ_DMG/WZ_DIE/WZ_JUMP/WZ_BACKSTEP/WZ_DASH_ATK/
//   WZ_NOMANA/R_WZ_THROW 八件套 + Effect/Particle/HandHit{1,2}.ptl（93L）
// ------------------------------------------------------------
// 0x5DD470 sub_5DD470 —— CNMage/白魔 WZ 构造后段资源装配（由·0x579E70 接·0x5DA220 之后调用）：
// ·预置动画段号表（+6792/6796/6800=2、6804=3、6808=4、+6864=1、6868=8、6872=14）与攻击参数面
// ·（+7908/7912/7916/7920=100/-300/200/-300、+7844/7848/7852=43/60/1、+7928=3 攻段槽）
// ·八件套语音：WZ_JUMP_ATK/R_WZ_DMG/WZ_DIE/WZ_JUMP/WZ_BACKSTEP/WZ_DASH_ATK/WZ_NOMANA/R_WZ_THROW
// ·（空串作分组分隔）经·sub_4015C0 上推；末以 new(0x12C)+·sub_4C3640 装载 Effect/Particle/HandHit1.ptl 与 HandHit2.ptl 存 +8416/8420
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD470(int this)
{
  int pThis_1ED4; // ecx
  int v3; // eax
  unsigned int v4; // edi
  uint32_t *v5; // eax
  int pThis_16C; // eax
  int result; // eax
  void *Block; // [esp+Ch] [ebp-10h] BYREF
  int v9; // [esp+18h] [ebp-4h]

  pThis_1ED4 = this + 7892;
  *(uint32_t *)(this + 6792) = 2;
  *(uint32_t *)(this + 6796) = 2;
  *(uint32_t *)(this + 6800) = 2;
  *(uint32_t *)(this + 6804) = 3;
  *(uint32_t *)(this + 6808) = 4;
  *(uint32_t *)(this + 6864) = 1;
  *(uint32_t *)(this + 6868) = 8;
  *(uint32_t *)(this + 6872) = 14;
  v3 = *(uint32_t *)(pThis_1ED4 + 4);
  Block = (void *)3;
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(pThis_1ED4 + 8) - v3) >> 2;
  else
    v4 = 0;
  if ( v3 != 0 && v4 < (*(uint32_t *)(pThis_1ED4 + 12) - v3) >> 2 )
  {
    v5 = *(uint32_t **)(pThis_1ED4 + 8);
    *v5 = 3;
    *(uint32_t *)(pThis_1ED4 + 8) = v5 + 1;
  }
  else
  {
    sub_430C80(*(void **)(pThis_1ED4 + 8), 1, (int)&Block);
  }
  *(uint32_t *)(this + 7908) = 100;
  *(uint32_t *)(this + 7912) = -300;
  *(uint32_t *)(this + 7916) = 200;
  *(uint32_t *)(this + 7920) = -300;
  *(uint32_t *)(this + 7844) = 43;
  *(uint32_t *)(this + 7848) = 60;
  *(uint32_t *)(this + 7852) = 1;
  *(uint8_t *)(this + 7924) = 0;
  *(uint32_t *)(this + 7928) = 3;
  sub_4015C0("WZ_JUMP_ATK", 0xBu);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("R_WZ_DMG", 8u);  // 【std::string构造赋值】
  sub_4015C0("WZ_DIE", 6u);  // 【std::string构造赋值】
  sub_4015C0("WZ_JUMP", 7u);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("WZ_BACKSTEP", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("WZ_DASH_ATK", 0xBu);  // 【std::string构造赋值】
  sub_4015C0("WZ_NOMANA", 9u);  // 【std::string构造赋值】
  sub_4015C0((void *)szPassword, 0);  // 【std::string构造赋值】
  sub_4015C0("R_WZ_THROW", 0xAu);  // 【std::string构造赋值】
  Block = operator new(0x12Cu);
  v9 = 0;
  if ( Block != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      pThis_16C = sub_4C3640(this + 364, "Effect/Particle/HandHit1.ptl", this);
    else
      pThis_16C = sub_4C3640(*(uint32_t *)(this + 364), "Effect/Particle/HandHit1.ptl", this);
  }
  else
  {
    pThis_16C = 0;
  }
  v9 = -1;
  *(uint32_t *)(this + 8416) = pThis_16C;
  Block = operator new(0x12Cu);
  v9 = 1;
  if ( Block != nullptr )
  {
    if ( *(uint32_t *)(this + 384) < 0x10u )
      result = sub_4C3640(this + 364, "Effect/Particle/HandHit2.ptl", this);
    else
      result = sub_4C3640(*(uint32_t *)(this + 364), "Effect/Particle/HandHit2.ptl", this);
  }
  else
  {
    result = 0;
  }
  *(uint32_t *)(this + 8420) = result;
  return result;
}



// AI 字段访问（this+8372）
// ------------------------------------------------------------
// 0x5DD700 sub_5DD700 —— 召唤物受击转发：this+8372 挂件存活时·sub_5DD040(this,0xFFFF,...,1) 全量收集召唤物
// ·再逐个 vt+1052(obj, this, nArg2, nArg3, nArg4) 下发受击；随后取 nArg2 攻方档位 vt+348(nArg2)+60 判断本机关卡门，
// ·动画槽（this+120 挂载对象 +148==-1 时·sub_4938F0 帧游标复位、取 +112；this+642 则直取 this+644）就绪时 vt+216(this,11) 解忙
// ------------------------------------------------------------
int /*thiscall*/ sub_5DD700(int this, int nArg2, int nArg3, int nArg4)
{
  int fld_20B4; // eax
  uint32_t *Block2; // esi
  uint32_t *v7; // ebx
  int fld_284; // esi
  int fld_78; // esi
  char v11[4]; // [esp+Ch] [ebp-1Ch] BYREF
  void *Block; // [esp+10h] [ebp-18h]
  uint32_t *v13; // [esp+14h] [ebp-14h]
  int v14; // [esp+18h] [ebp-10h]
  int v15; // [esp+24h] [ebp-4h]

  fld_20B4 = *(uint32_t *)(this + 8372);
  if ( fld_20B4 != 0 && (*(uint8_t (**)(void))(*(uint32_t *)fld_20B4 + 80))() != 0 )
  {
    Block = nullptr;
    v13 = nullptr;
    v14 = 0;
    v15 = 0;
    sub_5DD040((uint32_t *)this, 0xFFFF, (int)v11, 1);
    Block2 = Block;
    v7 = v13;
    if ( Block != v13 )
    {
      do
      {
        (*(void (/*thiscall*/ **)(uint32_t, int, int, int, int))(*(uint32_t *)*Block2 + 1052))(*Block2, this, nArg2, nArg3, nArg4);
        ++Block2;
      }
      while ( Block2 != v7 );
      Block2 = Block;
    }
    v15 = -1;
    if ( Block2 != nullptr )
      j__free(Block2);
  }
  if ( *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 348))(nArg2) + 60) != 0 )
  {
    if ( *(uint8_t *)(this + 642) != 0 )
    {
      fld_284 = *(uint32_t *)(this + 644);
    }
    else
    {
      fld_78 = *(uint32_t *)(this + 120);
      if ( fld_78 == 0 )
      {
LABEL_16:
        if ( (uint8_t)nArg4 == 0 )
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 216))(this, 11);
        return sub_4B9720(nArg2, nArg3, nArg4);
      }
      if ( *(uint32_t *)(fld_78 + 148) == -1 )
        sub_4938F0(*(uint32_t *)(this + 120));
      fld_284 = *(uint32_t *)(fld_78 + 112);
    }
    if ( fld_284 != 0 )
      return sub_4B9720(nArg2, nArg3, nArg4);
    goto LABEL_16;
  }
  return sub_4B9720(nArg2, nArg3, nArg4);
}



// 参数打包+数据表 AI（sub_431230+sub_47EF20, 160L）
// ------------------------------------------------------------
// 0x5DD810 sub_5DD810 —— 挂件槽按相位建销总表（pArg2 为相位/挂点号，Block 为开关量）：
// ·pArg2==1 时 Block<=0 转·sub_505FF0(1,0)；>0 且 this+7892 表不足 2 项则以·sub_431230 写入常量 4；
// ·pArg2==19 建 new(0x7C)+·sub_4B3C90 于 this+8552，vt+64(obj)+36 清标志，·sub_47EF20 抽参后 vt+124/vt+120(9,...)/vt+56 装配，
// ·Block<=0 且存活则·sub_53FE50 回收；pArg2==35/36 建 new(0x88)+·sub_4C2820 于 this+8556/8560 并经·sub_5F9DD0 起效；
// ·pArg2==48 建 new(0x8C)+·0x5DD210 于 this+8564，抽三参 sub_47EF20(2/1/0,...)*0.1 经 vt+148 定标后 vt+56 装配
// ------------------------------------------------------------
void /*thiscall*/ sub_5DD810(int *this, void *pArg2, int Block)
{
  int Block2; // edi
  int fld_e1974; // edx
  void *pMem; // eax
  int pObj; // eax
  int v8; // eax
  int *fld_e2138; // ecx
  int v10; // edx
  int fld_e21382; // ecx
  int fld_e21383; // ecx
  int pObj2; // eax
  int fld_e21412; // ebx
  int v15; // eax
  int fld_e2141; // ecx
  BOOL v17; // edi
  void *pMem2; // eax
  int pObj3; // eax
  int pObj4; // ecx
  float v21; // [esp+4h] [ebp-20h]
  float v22; // [esp+8h] [ebp-1Ch]
  float v23; // [esp+8h] [ebp-1Ch]

  Block2 = Block;
  sub_4B3E70(this, pArg2, Block);
  if ( pArg2 == (void *)1 )
  {
    if ( Block2 <= 0 )
    {
      sub_505FF0(1, 0);
    }
    else
    {
      fld_e1974 = *(this + 1974);
      if ( fld_e1974 == 0 || (unsigned int)((*(this + 1975) - fld_e1974) >> 2) < 2 )
      {
        Block = 4;
        sub_431230((int)(this + 1973), &Block);
      }
    }
    return;
  }
  if ( pArg2 == (void *)19 )
  {
    if ( Block2 > 0 )
    {
      if ( *(this + 2138) == 0 )
      {
        pMem = operator new(0x7Cu);
        Block = (int)pMem;
        if ( pMem != nullptr )
          pObj = sub_4B3C90((int)pMem, 0, 0);
        else
          pObj = 0;
        *(this + 2138) = pObj;
        *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 64))(pObj) + 36) = 0;
      }
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 19);
      v8 = sub_47EF20(0, Block2, -1, -1, 11);
      fld_e2138 = (int *)*(this + 2138);
      v10 = *fld_e2138;
      Block = v8;
      (*(void (/*thiscall*/ **)(int *))(v10 + 124))(fld_e2138);
      v22 = (float)Block;
      (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t))(*(uint32_t *)*(this + 2138) + 120))(9, 0, LODWORD(v22));
      (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2138) + 56))(
        *(this + 2138),
        this,
        this,
        0,
        0,
        0,
        -1);
      return;
    }
    fld_e21382 = *(this + 2138);
    if ( fld_e21382 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e21382 + 80))(fld_e21382) == 0 )
      return;
    fld_e21383 = *(this + 2138);
LABEL_41:
    sub_53FE50(fld_e21383);
    return;
  }
  if ( pArg2 == (void *)35 || pArg2 == (void *)36 )
  {
    v17 = pArg2 == (void *)36;
    if ( Block <= 0 )
    {
      pObj4 = *(this + v17 + 2139);
      if ( pObj4 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj4 + 80))(pObj4) == 0 )
        return;
      fld_e21383 = *(this + v17 + 2139);
      goto LABEL_41;
    }
    if ( *(this + v17 + 2139) == 0 )
    {
      pMem2 = operator new(0x88u);
      if ( pMem2 != nullptr )
        pObj3 = sub_4C2820((int)pMem2, 3, (int)pArg2);
      else
        pObj3 = 0;
      *(this + v17 + 2139) = pObj3;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj3 + 64))(pObj3) + 36) = 0;
    }
    sub_5F9DD0(Block);
    (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + v17 + 2139) + 56))(
      *(this + v17 + 2139),
      this,
      this,
      0,
      0,
      0,
      -1);
  }
  else
  {
    if ( pArg2 != (void *)48 )
      return;
    if ( Block2 <= 0 )
    {
      fld_e2141 = *(this + 2141);
      if ( fld_e2141 == 0 || (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2141 + 80))(fld_e2141) == 0 )
        return;
      fld_e21383 = *(this + 2141);
      goto LABEL_41;
    }
    if ( *(this + 2141) == 0 )
    {
      if ( operator new(0x8Cu) != nullptr )
        pObj2 = sub_5DD210(0, 0, 0);
      else
        pObj2 = 0;
      *(this + 2141) = pObj2;
      *(uint8_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 64))(pObj2) + 36) = 0;
    }
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 48);
    fld_e21412 = *(uint32_t *)*(this + 2141);
    v23 = (double)(int)sub_47EF20(2, Block, -1, -1, 11) * 0.1;
    v21 = (double)(int)sub_47EF20(1, Block, -1, -1, 11) * 0.1;
    v15 = sub_47EF20(0, Block, -1, -1, 11);
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t, uint32_t))(fld_e21412 + 148))(
      *(this + 2141),
      v15 / 2,
      LODWORD(v21),
      LODWORD(v23));
    (*(void (/*thiscall*/ **)(uint32_t, int *, int *, uint32_t, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2141) + 56))(
      *(this + 2141),
      this,
      this,
      0,
      0,
      0,
      -1);
  }
}


// 数据表读数（sub_47EF20, 43L）
// ------------------------------------------------------------
// 0x5DDBA0 sub_5DDBA0 —— 标记球挂件挂装（this+8492 槽）：空则 new(0xB0)+·0x5DD320 建 CNTargetIt、vt+64(obj)+36 清标志
// ·vt+1140(this) 取参交·sub_64F250 写目标数据、vt+1160(this,50,0,参) 登记，sub_47EF20(50,-1,-1,11,50) 抽码；
// ·挂件不存活或 +4 不等于 nArg2 时 vt+56(挂件, nArg2, this, 1, 0, 0, -1) 重新挂装；末尾·sub_64FAC0 走目标锁业务
// ------------------------------------------------------------
int /*thiscall*/ sub_5DDBA0(uint32_t *this, int nArg2)
{
  uint32_t *pMem; // eax
  uint32_t *v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // edi

  if ( *(this + 2123) == 0 )
  {
    pMem = operator new(0xB0u);
    if ( pMem != nullptr )
      v4 = sub_5DD320(pMem);
    else
      v4 = nullptr;
    *(this + 2123) = v4;
    *(uint8_t *)((*(int (/*thiscall*/ **)(uint32_t *))(*v4 + 64))(v4) + 36) = 0;
  }
  v5 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);
  sub_64F250(v5);
  v6 = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 1140))(this);
  (*(void (/*thiscall*/ **)(uint32_t *, int, uint32_t, int))(*this + 1160))(this, 50, 0, v6);
  v7 = sub_47EF20(50, -1, -1, 11, 50);
  if ( (*(uint8_t (/*thiscall*/ **)(uint32_t))(*(uint32_t *)*(this + 2123) + 80))(*(this + 2123)) == 0
    || *(uint32_t *)(*(this + 2123) + 4) != nArg2 )
  {
    (*(void (/*thiscall*/ **)(uint32_t, int, uint32_t *, int, uint32_t, uint32_t, int))(*(uint32_t *)*(this + 2123) + 56))(
      *(this + 2123),
      nArg2,
      this,
      1,
      0,
      0,
      -1);
  }
  return sub_64FAC0(v7);
}



// 白魔相位字段大区（this+8232..8480, 247L —— WZ 专用字段块）
// ------------------------------------------------------------
// 0x5DDCA0 sub_5DDCA0 —— CNMage 白魔字段块总析构（this+8232..8564 全槽清理，由·0x579F10 构造链对偶调用）：
// ·先 vt[0](obj,1) 释放 this+8232/8236/8240/8248 四挂件指针；this+8276 起 4x2 与 this+8328 起 5x3 两组
// ·经·sub_42AF90+·sub_657740(obj,228) 双段回收（228 为对象池/尺寸码）并逐槽清零；
// ·再处理 +8372/8380、+8396 起 2x4 块（含 vt[0] 与·sub_42AF90 混合）、+8448/8452、+8456 起 2、+8464、+8468 起 3、
// ·+8480 起 2、+8492、+8500、+8524、+8544、+8552、+8556 起 2、+8564 各组【推断：+8396..8420 与·0x5DD470 的 HandHit 粒子槽对应】
// ------------------------------------------------------------
int /*thiscall*/ sub_5DDCA0(int this)
{
  void (/*thiscall*/ ***pThis_2028)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_202C)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_2030)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_2038)(uint32_t, int); // ecx
  void ***pThis_2054; // esi
  void **v7; // edi
  void ***pThis_2088; // esi
  int v9; // edi
  void **v10; // edi
  bool v11; // zf
  void **v12; // edi
  void (/*thiscall*/ ***pThis_20B4)(uint32_t, int); // ecx
  void (/*thiscall*/ ***pThis_20BC)(uint32_t, int); // ecx
  int pThis_20E0; // esi
  int v16; // edi
  void (/*thiscall*/ ***v17)(uint32_t, int); // ecx
  void **v18; // edi
  void **v19; // edi
  int fld_2100; // esi
  void **fld_2104; // esi
  void ***pThis_2108; // esi
  void **v23; // edi
  int fld_2110; // esi
  void ***pThis_2114; // esi
  void **v26; // edi
  void ***pThis_2120; // esi
  void **v28; // edi
  int result; // eax
  int (/*thiscall*/ ***pThis_212C)(uint32_t, int); // ecx
  void **fld_2134; // esi
  void **fld_214C; // esi
  void **fld_2160; // esi
  int (/*thiscall*/ ***pThis_2168)(uint32_t, int); // ecx
  uint32_t *pThis_216C; // esi
  int jj; // edi
  int (/*thiscall*/ ***pThis_2174)(uint32_t, int); // ecx
  int i; // [esp+8h] [ebp-8h]
  int k; // [esp+8h] [ebp-8h]
  int m; // [esp+8h] [ebp-8h]
  int n; // [esp+8h] [ebp-8h]
  int ii; // [esp+8h] [ebp-8h]
  int v43; // [esp+8h] [ebp-8h]
  int j; // [esp+Ch] [ebp-4h]

  pThis_2028 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8232);
  if ( pThis_2028 != nullptr )
    (**pThis_2028)(pThis_2028, 1);
  pThis_202C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8236);
  *(uint32_t *)(this + 8232) = 0;
  if ( pThis_202C != nullptr )
    (**pThis_202C)(pThis_202C, 1);
  pThis_2030 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8240);
  *(uint32_t *)(this + 8236) = 0;
  if ( pThis_2030 != nullptr )
    (**pThis_2030)(pThis_2030, 1);
  pThis_2038 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8248);
  *(uint32_t *)(this + 8240) = 0;
  if ( pThis_2038 != nullptr )
    (**pThis_2038)(pThis_2038, 1);
  *(uint32_t *)(this + 8248) = 0;
  pThis_2054 = (void ***)(this + 8276);
  for ( i = 4; i != 0; --i )
  {
    for ( j = 2; j != 0; --j )
    {
      v7 = *pThis_2054;
      if ( *pThis_2054 != nullptr )
      {
        sub_42AF90(*pThis_2054);
        sub_657740(v7, 228);
      }
      *pThis_2054++ = nullptr;
    }
  }
  pThis_2088 = (void ***)(this + 8328);
  for ( k = 5; k != 0; --k )
  {
    v9 = (int)*(pThis_2088 - 5);
    if ( v9 != 0 )
    {
      sub_42AF90(*(pThis_2088 - 5));
      sub_657740(v9, 228);
    }
    v10 = *pThis_2088;
    v11 = *pThis_2088 == nullptr;
    *(pThis_2088 - 5) = nullptr;
    if ( !v11 )
    {
      sub_42AF90(v10);
      sub_657740(v10, 228);
    }
    v12 = pThis_2088[5];
    *pThis_2088 = nullptr;
    if ( v12 != nullptr )
    {
      sub_42AF90(v12);
      sub_657740(v12, 228);
    }
    pThis_2088[5] = nullptr;
    ++pThis_2088;
  }
  pThis_20B4 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8372);
  if ( pThis_20B4 != nullptr )
    (**pThis_20B4)(pThis_20B4, 1);
  pThis_20BC = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 8380);
  *(uint32_t *)(this + 8372) = 0;
  if ( pThis_20BC != nullptr )
    (**pThis_20BC)(pThis_20BC, 1);
  *(uint32_t *)(this + 8380) = 0;
  pThis_20E0 = this + 8416;
  for ( m = 2; m != 0; --m )
  {
    v16 = *(uint32_t *)(pThis_20E0 - 8);
    if ( v16 != 0 )
    {
      sub_42AF90(*(void ***)(pThis_20E0 - 8));
      sub_657740(v16, 228);
    }
    v17 = *(void (/*thiscall*/ ****)(uint32_t, int))pThis_20E0;
    v11 = *(uint32_t *)pThis_20E0 == 0;
    *(uint32_t *)(pThis_20E0 - 8) = 0;
    if ( !v11 )
      (**v17)(v17, 1);
    v18 = *(void ***)(pThis_20E0 + 8);
    *(uint32_t *)pThis_20E0 = 0;
    if ( v18 != nullptr )
    {
      sub_42AF90(v18);
      sub_657740(v18, 228);
    }
    v19 = *(void ***)(pThis_20E0 + 16);
    *(uint32_t *)(pThis_20E0 + 8) = 0;
    if ( v19 != nullptr )
    {
      sub_42AF90(v19);
      sub_657740(v19, 228);
    }
    *(uint32_t *)(pThis_20E0 + 16) = 0;
    pThis_20E0 += 4;
  }
  fld_2100 = *(uint32_t *)(this + 8448);
  if ( fld_2100 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8448));
    sub_657740(fld_2100, 228);
  }
  fld_2104 = *(void ***)(this + 8452);
  *(uint32_t *)(this + 8448) = 0;
  if ( fld_2104 != nullptr )
  {
    sub_42AF90(fld_2104);
    sub_657740(fld_2104, 228);
  }
  *(uint32_t *)(this + 8452) = 0;
  pThis_2108 = (void ***)(this + 8456);
  for ( n = 2; n != 0; --n )
  {
    v23 = *pThis_2108;
    if ( *pThis_2108 != nullptr )
    {
      sub_42AF90(*pThis_2108);
      sub_657740(v23, 228);
    }
    *pThis_2108++ = nullptr;
  }
  fld_2110 = *(uint32_t *)(this + 8464);
  if ( fld_2110 != 0 )
  {
    sub_42AF90(*(void ***)(this + 8464));
    sub_657740(fld_2110, 228);
  }
  *(uint32_t *)(this + 8464) = 0;
  pThis_2114 = (void ***)(this + 8468);
  for ( ii = 3; ii != 0; --ii )
  {
    v26 = *pThis_2114;
    if ( *pThis_2114 != nullptr )
    {
      sub_42AF90(*pThis_2114);
      sub_657740(v26, 228);
    }
    *pThis_2114++ = nullptr;
  }
  pThis_2120 = (void ***)(this + 8480);
  v43 = 2;
  do
  {
    v28 = *pThis_2120;
    if ( *pThis_2120 != nullptr )
    {
      sub_42AF90(*pThis_2120);
      sub_657740(v28, 228);
    }
    *pThis_2120++ = nullptr;
    result = v43 - 1;
    v43 = result;
  }
  while ( result != 0 );
  pThis_212C = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8492);
  if ( pThis_212C != nullptr )
    result = (**pThis_212C)(pThis_212C, 1);
  fld_2134 = *(void ***)(this + 8500);
  *(uint32_t *)(this + 8492) = 0;
  if ( fld_2134 != nullptr )
  {
    sub_42AF90(fld_2134);
    result = sub_657740(fld_2134, 228);
  }
  fld_214C = *(void ***)(this + 8524);
  *(uint32_t *)(this + 8500) = 0;
  if ( fld_214C != nullptr )
  {
    sub_42AF90(fld_214C);
    result = sub_657740(fld_214C, 228);
  }
  fld_2160 = *(void ***)(this + 8544);
  *(uint32_t *)(this + 8524) = 0;
  if ( fld_2160 != nullptr )
  {
    sub_42AF90(fld_2160);
    result = sub_657740(fld_2160, 228);
  }
  pThis_2168 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8552);
  *(uint32_t *)(this + 8544) = 0;
  if ( pThis_2168 != nullptr )
    result = (**pThis_2168)(pThis_2168, 1);
  *(uint32_t *)(this + 8552) = 0;
  pThis_216C = (uint32_t *)(this + 8556);
  for ( jj = 2; jj != 0; --jj )
  {
    if ( *pThis_216C != 0 )
      result = (**(int (/*thiscall*/ ***)(uint32_t, int))*pThis_216C)(*pThis_216C, 1);
    *pThis_216C++ = 0;
  }
  pThis_2174 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 8564);
  if ( pThis_2174 != nullptr )
    result = (**pThis_2174)(pThis_2174, 1);
  *(uint32_t *)(this + 8564) = 0;
  return result;
}


// 冲刺命中（255L）：WZ_DASH_HIT 播报 + Effect/Animation/WhipToMonsterHit.ani 鞭击特效
//   （sub_431920+sub_699000+sub_47EF20+RTTI cast; this+8228 相位）
// ------------------------------------------------------------
// 0x5DE100 sub_5DE100 —— 冲刺命中（白魔 WZ_DASH_HIT）：vt+308 存活 + 攻方 vt+40(,17) 为玩家 + ·sub_4E4630 敌我成立 +
// ··sub_5DB490 追击弹存在 + nArg4==0 时，写 this+8440/8444 记录目标与到期时刻（clock_now(this+36)+·sub_47E9D0 表值）备后续判定；
// ··sub_47EF20(40, 3-条件, ...) 抽参后·sub_5DC590 走发射概率门；再按 this+1639 主状态镜像2 分派：
// ·case 12 首次进入播报 WZ_DASH_HIT（this+8228 置 1）；case 20 军团态且 this+8516==20 时装载 Effect/Animation/WhipToMonsterHit.ani，
// ·经·sub_45FE80 挂到目标并以·sub_5DAFA0 建 CNWhipped 鞭挞结点（273→弹种 0、529→弹种 1）；
// ·case 21 反应态 14 且 this+8532==1 时，对 IRDActiveObject 目标 vt+648 试伤 + sub_47EFD0 抽 5/6/7 参 + ·sub_423A80 插值，
// ·交 vt+56 装配后 vt+580(this,48028,obj) 计算伤害；三支均尾调·sub_4AFB30（受击基类链）
// ------------------------------------------------------------
int /*thiscall*/ sub_5DE100(int *this, int nArg2, float *pArg3, int nArg4)
{
  uint32_t *v5; // edi
  int v6; // eax
  uint32_t *v7; // eax
  int v8; // ebx
  int fld_e2060; // ecx
  int fld_e1639; // eax
  char v11; // bl
  int v12; // eax
  int fld_e16392; // eax
  int v14; // edi
  int fld_e91; // edx
  int *v16; // edi
  int fld_e29; // ecx
  int v18; // ebx
  uint64_t v19; // rax
  int v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // ebx
  int v24; // eax
  int *v25; // eax
  int v26; // edx
  int v27; // ebx
  uint32_t *v28; // eax
  int v29; // eax
  int *v30; // eax
  int v31; // eax
  int pObj2; // eax
  int pObj; // edi
  int v35; // ebx
  int v36; // eax
  int v37; // eax
  char *v38; // edi
  int v39; // ebx
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int fld_e2135; // eax
  int fld_e21352; // edx
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // edi
  int v49; // eax
  int v50; // [esp-Ch] [ebp-74h]
  int v51; // [esp-4h] [ebp-6Ch]
  unsigned int v52; // [esp+0h] [ebp-68h]
  int v53; // [esp+Ch] [ebp-5Ch]
  void *Block; // [esp+10h] [ebp-58h]
  int v55; // [esp+14h] [ebp-54h] BYREF
  int fld_e21353; // [esp+18h] [ebp-50h] BYREF
  int16_t v57; // [esp+1Ch] [ebp-4Ch]
  int16_t v58; // [esp+1Eh] [ebp-4Ah]
  int16_t v59; // [esp+20h] [ebp-48h]
  int v60; // [esp+22h] [ebp-46h]
  int dword_796E502; // [esp+58h] [ebp-10h]
  int v62; // [esp+64h] [ebp-4h]

  dword_796E502 = dword_796E50;
  v5 = (uint32_t *)nArg2;
  if ( (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0
    && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 17) != 0
    && sub_4E4630(this, nArg2)
    && (uint8_t)sub_5DB490(this) != 0
    && (uint8_t)nArg4 == 0 )
  {
    v6 = *this;
    *(this + 2110) = nArg2;
    v7 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int))(v6 + 1160))(this, 39);
    v8 = sub_47E9D0(v7, 0);
    *(this + 2111) = sub_699000((int)(this + 9)) + v8;
  }
  fld_e2060 = *(this + 2060);
  if ( fld_e2060 != 0
    && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_e2060 + 80))(fld_e2060) != 0
    && (uint8_t)nArg4 == 0
    && sub_4E4630(this, nArg2) )
  {
    fld_e1639 = *(this + 1639);
    v11 = 0;
    if ( fld_e1639 == 8 && *(this + 2054) == -1 || fld_e1639 == 12 || fld_e1639 == 7 )
      v11 = 1;
    v50 = (*(int (/*thiscall*/ **)(int *, int, int))(*this + 1140))(this, 40, -1);
    (*(void (/*thiscall*/ **)(int *))(*this + 1160))(this);
    v12 = sub_47EF20(40, 3 - (v11 != 0), v50, -1, 11);
    sub_5DC590(v12);
  }
  fld_e16392 = *(this + 1639);
  switch ( fld_e16392 )
  {
    case 12:
      if ( *((uint8_t *)this + 8228) == 0 )
      {
        (*(void (/*thiscall*/ **)(int *, const char *, int, uint32_t, uint32_t))(*this + 212))(this, "WZ_DASH_HIT", -1, 0, 0);
        *((uint8_t *)this + 8228) = 1;
      }
      return sub_4AFB30(this, v5, (int)pArg3, nArg4);
    case 20:
      if ( *(this + 2129) != 20 || (uint8_t)nArg4 != 0 )
        return sub_4AFB30(this, v5, (int)pArg3, nArg4);
      v14 = 0;
      v62 = 0;
      if ( sub_42FCB0(228) != 0 )
      {
        if ( (unsigned int)*(this + 96) < 0x10 )
          LOBYTE(fld_e91) = (uint8_t)this + 108;
        else
          fld_e91 = *(this + 91);
        v14 = sub_431920(fld_e91, (char)"Effect/Animation/WhipToMonsterHit.ani", 1);
      }
      v62 = 1;
      if ( sub_44B6C0(284) != 0 )
        v16 = (int *)sub_44E1F0(v14, 1);
      else
        v16 = nullptr;
      fld_e29 = *(this + 29);
      v62 = -1;
      sub_45FE80(fld_e29, (int)v16, 2, 0, (int)v16, nArg2, 0);
      v18 = *v16;
      v51 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)nArg2 + 124))(nArg2, (uint64_t)(pArg3[5] * 0.5 + pArg3[2]));
      v19 = (uint64_t)(pArg3[3] * 0.5 + *pArg3);
      (*(void (/*fastcall*/ **)(int *, uint32_t, uint32_t, int))(v18 + 112))(v16, HIDWORD(v19), v19, v51);
      v20 = *v16;
      v21 = (*(int (/*thiscall*/ **)(int *, int))(*this + 660))(this, nArg2);
      v22 = sub_432E50(v21);
      (*(void (/*thiscall*/ **)(int *, int))(v20 + 148))(v16, v22);
      v23 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)nArg2 + 376))(nArg2);
      if ( v23 == (*(int (/*thiscall*/ **)(int *))(*this + 376))(this) )
      {
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 273) != 0 )
        {
          v62 = 2;
          if ( operator new(0x70u) != nullptr )
          {
            v24 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 20);
            v25 = (int *)sub_5DAFA0(0, v24);
          }
          else
          {
            v25 = nullptr;
          }
          v26 = *this;
          v27 = *v25;
          v55 = (int)v25;
          v62 = -1;
          v28 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, int))(v26 + 1160))(this, 20, 1);
LABEL_42:
          sub_47E9D0(v28, v52);
          (*(void (/*thiscall*/ **)(int, int, int *, int, uint32_t, int))(v27 + 56))(v55, nArg2, this, 1, 0, 11);
          goto LABEL_43;
        }
        if ( (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)nArg2 + 40))(nArg2, 529) != 0 )
        {
          v62 = 3;
          if ( operator new(0x70u) != nullptr )
          {
            v29 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 20);
            v30 = (int *)sub_5DAFA0(1, v29);
          }
          else
          {
            v30 = nullptr;
          }
          v27 = *v30;
          v55 = (int)v30;
          v31 = *this;
          v62 = -1;
          v28 = (uint32_t *)(*(int (/*thiscall*/ **)(int *, int, uint32_t))(v31 + 1160))(this, 20, 0);
          goto LABEL_42;
        }
      }
LABEL_43:
      v5 = (uint32_t *)nArg2;
      return sub_4AFB30(this, v5, (int)pArg3, nArg4);
    case 21:
      if ( *(this + 2134) != 14 || (uint8_t)nArg4 != 0 || *(this + 2133) != 1 )
        return sub_4AFB30(this, v5, (int)pArg3, nArg4);
      pObj2 = __RTDynamicCast(
              nArg2,
              0,
              &IRDCollisionObject `RTTI Type Descriptor',
              &IRDActiveObject `RTTI Type Descriptor',
              0);
      pObj = pObj2;
      Block = (void *)pObj2;
      if ( pObj2 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 308))(pObj2) != 0 )
      {
        v35 = sub_4AED20(nArg2);
        v36 = *(uint32_t *)nArg2;
        v55 = 100;
        v37 = (*(int (/*thiscall*/ **)(int, int *, int *))(v36 + 648))(nArg2, &v55, this);
        if ( v35 == 0 && v37 == 0 && *(uint32_t *)((*(int (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 688))(pObj) + 20) != 0 )
        {
          v38 = (char *)(*(int (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);
          v39 = (*(int (/*thiscall*/ **)(int *, int))(*this + 1140))(this, 14);
          v40 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
          v53 = sub_47EFD0(v38, COERCE_FLOAT(6), v39, v40, v40, 0);
          v41 = (*(int (/*thiscall*/ **)(int *))(*this + 388))(this);
          v42 = sub_47EFD0(v38, COERCE_FLOAT(5), v39, v41, v41, 0);
          fld_e2135 = sub_423A80(v42, v53, *(this + 2135), dword_9B9340);
          fld_e21352 = *(this + 2135);
          fld_e21353 = fld_e2135;
          v45 = 4;
          if ( fld_e21352 >= dword_9B9340 )
          {
            v57 = sub_47E9D0(v38, 4u);
            v58 = sub_47E9D0(v38, 3u);
            v46 = *this;
            v59 = 15;
            v47 = (*(int (/*thiscall*/ **)(int *))(v46 + 388))(this);
            v60 = sub_47EFD0(v38, COERCE_FLOAT(7), v39, v47, v47, 0);
            v45 = 14;
          }
          v48 = *this;
          v49 = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, int, uint32_t, int, int *))(*(uint32_t *)Block + 56))(
                  Block,
                  0,
                  0,
                  0,
                  0,
                  0,
                  4,
                  0,
                  v45,
                  &fld_e21353);
          (*(void (/*thiscall*/ **)(int *, int, int))(v48 + 580))(this, 48028, v49);
        }
      }
      (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);
      sub_47DCD0(this, -1);
      goto LABEL_43;
    default:
      break;
  }
  if ( fld_e16392 == 18
    && *(this + 2100) == 4
    && (uint8_t)nArg4 == 0
    && (*(uint8_t (/*thiscall*/ **)(int *))(*this + 308))(this) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 12);
    sub_47E440(1);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 14);
    sub_47E440(1);
    (*(void (/*thiscall*/ **)(int *, int))(*this + 1160))(this, 13);
    sub_47E440(1);
  }
  return sub_4AFB30(this, v5, (int)pArg3, nArg4);
}


// ★★ 白魔 WZ 大型主状态机（1082L, 本工程最大函数）：switch(this+6556) 大状态分派
//   （case 6/10/16/17/18/19/20/21 可见）+ this+616 反应态 == -1 空闲门 + this+612 门；
//   内含 FollowMeCast.ani 召集/PRICK 刺击/HEAVEN_HIT 天击/MAGE_SWING/WZ_SWING 挥击/
//   LESSON_START + R_WZ_LESSON_START 教程语音（sub_431920+sub_431230+sub_699000+sub_47EF20）
//   —— 研究 15 三层状态架构（+200/+616/+6556）的最完整客户端样本
// ------------------------------------------------------------
// 0x5DE690 sub_5DE690 —— 白魔 WZ 每帧主状态机总入口（switch(this+6556) 大状态 0/7/8/10/12/14/18/19/20/21）：
// ·序章·sub_5DAC20 倒计时广播、·0x5DAF10 延时播报、·sub_4B7430 升级演出装配；
// ·this+8568/+8572/+8576/+8580 相位计时段以 clock_now(this+36) 比点（·sub_699000）+ ·sub_431230 打包 + ·sub_5DA1E0 索引→组号映射，
// ·转段时·sub_5E5260 释放包、·sub_4BFC10(this+8116) 作总开关；case 8 攻段号·sub_41A5E0(this+7028) 查 dword_738604 定段；
// ·case 10 由·0x5DB550(44,60) 双锚位姿同步；case 12 反应态 3 分派 vt+560(this,16,...) 相位；case 14 装载 FollowMeCast.ani 召集；
// ·case 18/19/20/21 依次播报 PRICK/WZ_HEAVEN_HIT(HEAVEN_HIT)/MAGE_SWING(WZ_SWING)/LESSON_START+R_WZ_LESSON_START 教程语音
// ------------------------------------------------------------
void /*thiscall*/ sub_5DE690(int this)
{
  double v2; // st7
  int fld_2184; // eax
  int fld_21782; // eax
  int fld_2178; // eax
  int pThis_24; // eax
  int fld_2180; // edi
  int fld_782; // edi
  bool fld_78; // cc
  int v10; // edi
  int pThis_494; // eax
  int fld_16C; // edx
  int v13; // edi
  int *v14; // edi
  int fld_74; // ecx
  int pThis_11; // eax
  int v17; // ebx
  int pThis_80; // eax
  int pThis_7C; // eax
  int v20; // ebx
  int pThis_98; // eax
  int fld_2154; // eax
  int pThis_39C2; // edi
  int pThis_984; // eax
  int pThis_782; // eax
  int v26; // edx
  int v27; // ebx
  int v28; // eax
  int pThis_7C3; // eax
  int v30; // eax
  void *fld_743; // ecx
  int fld_783; // ecx
  bool fld_21842; // cc
  int pThis_19A0; // eax
  int v35; // eax
  int fld_2144; // eax
  int v37; // edi
  int fld_2140; // eax
  int pThis_982; // eax
  int pThis_39C; // edi
  int pThis_983; // eax
  int v42; // edx
  int v43; // ebx
  int v44; // eax
  int pThis_7C2; // eax
  int pThis_78; // eax
  int v47; // eax
  void *fld_742; // ecx
  int *v49; // edi
  int fld_199C; // eax
  int fld_20B4; // ecx
  int fld_199C2; // eax
  bool pThis_308; // al
  int pThis_474; // eax
  int fld_199C3; // eax
  int fld_199C4; // eax
  int v57; // edi
  int pThis_1FB4; // ecx
  int v59; // eax
  int v60; // ebx
  uint32_t *v61; // ebx
  int v62; // eax
  int v63; // ebx
  int pThis_488; // edi
  int pThis_4742; // eax
  int v66; // ebx
  int v67; // eax
  bool fld_199C5; // zf
  int v69; // eax
  char *v70; // edx
  uint32_t *v71; // edx
  int v72; // edi
  uint32_t *fld_217C2; // edx
  uint32_t *v74; // edx
  uint32_t *v75; // edx
  uint32_t *v76; // edx
  uint32_t *v77; // edx
  uint32_t *v78; // edx
  uint32_t *v79; // edx
  uint32_t *fld_199C62; // edx
  bool fld_20FC; // al
  int fld_199C7; // eax
  uint32_t *v83; // ebx
  int pThis_4882; // edi
  int pThis_4743; // ebx
  int v86; // eax
  int v87; // eax
  int v88; // eax
  int *v89; // ecx
  uint32_t *v90; // ecx
  char v91; // al
  uint32_t *v92; // edi
  int v93; // eax
  int v94; // ebx
  uint32_t *v95; // ebx
  char *v96; // edx
  uint32_t *v97; // edx
  int fld_217C3; // eax
  int v99; // eax
  char *v100; // ebx
  int v101; // eax
  char *v102; // ebx
  char *v103; // eax
  int fld_199C8; // eax
  int fld_199C9; // eax
  int fld_199C10; // eax
  int fld_199C11; // eax
  char pThis_3082; // [esp-4h] [ebp-58h]
  char fld_20FC2; // [esp-4h] [ebp-58h]
  char v110[4]; // [esp+Ch] [ebp-48h] BYREF
  void *v111; // [esp+10h] [ebp-44h]
  int v112; // [esp+14h] [ebp-40h]
  int v113; // [esp+18h] [ebp-3Ch]
  char v114[4]; // [esp+1Ch] [ebp-38h] BYREF
  void *Block; // [esp+20h] [ebp-34h]
  void *Src; // [esp+24h] [ebp-30h]
  int v117; // [esp+28h] [ebp-2Ch]
  int fld_215C; // [esp+2Ch] [ebp-28h] BYREF
  int fld_217C; // [esp+30h] [ebp-24h] BYREF
  int v120; // [esp+34h] [ebp-20h]
  int fld_199C6; // [esp+38h] [ebp-1Ch] BYREF
  int v122; // [esp+3Ch] [ebp-18h] BYREF
  int v123; // [esp+40h] [ebp-14h] BYREF
  bool v124; // [esp+47h] [ebp-Dh]
  int v125; // [esp+50h] [ebp-4h]

  sub_5DAC20();
  v2 = sub_5DAF10(this);
  sub_4B7430((int *)this, v2);
  if ( *(uint32_t *)(this + 8568) != -1 )
  {
    if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0
      && sub_699000(this + 36) >= *(uint32_t *)(this + 8572)  // 【clock_now(clk)】
      && (uint8_t)sub_4BFC10(this + 8116) == 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 0;
      fld_217C = 1;
      sub_431230(&fld_217C);
      fld_217C = sub_699000(this + 36) - *(uint32_t *)(this + 8572);  // 【clock_now(clk)】
      sub_431230(&fld_217C);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, v110, 0, 0);
      v125 = -1;
      sub_5E5260(v110);
    }
    fld_2184 = *(uint32_t *)(this + 8580);
    if ( fld_2184 != 0 )
    {
      if ( fld_2184 == 1 )
      {
        if ( sub_699000(this + 36) >= *(uint32_t *)(this + 8572) + *(uint32_t *)(this + 8576)  // 【clock_now(clk)】
          && *(uint32_t *)(this + 616) == -1 )
        {
          fld_2178 = sub_5DA1E0(*(uint32_t *)(this + 8568));
          sub_4BA730(1, fld_2178, 0, -*(uint32_t *)(this + 160));
          *(uint32_t *)(this + 8580) = 2;
        }
      }
      else if ( fld_2184 == 2 && sub_699000(this + 36) >= *(uint32_t *)(this + 8576) + *(uint32_t *)(this + 8572) + 200 )  // 【clock_now(clk)】
      {
        pThis_24 = sub_699000(this + 36);  // 【clock_now(clk)】
        fld_2180 = sub_42B420(255, 220, -200 - *(uint32_t *)(this + 8576) - *(uint32_t *)(this + 8572) + pThis_24, 100);
        (*(void (/*thiscall*/ **)(int, uint32_t, int))(*(uint32_t *)this + 252))(this, 0, fld_2180);
        (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)this + 252))(this, 1, fld_2180);
      }
    }
    else if ( sub_699000(this + 36) >= *(uint32_t *)(this + 8572) && *(uint32_t *)(this + 616) == -1 )  // 【clock_now(clk)】
    {
      fld_21782 = sub_5DA1E0(*(uint32_t *)(this + 8568));
      sub_4BA730(0, fld_21782, 0, -*(uint32_t *)(this + 160));
      *(uint32_t *)(this + 8580) = 1;
    }
  }
  switch ( *(uint32_t *)(this + 6556) )
  {
    case 0:
      if ( *(uint32_t *)(this + 8568) != -1 && *(uint32_t *)(this + 6644) != 0 )
        sub_5DACE0(this);
      break;
    case 7:
      if ( *(uint8_t *)(this + 8220) == 0 )
      {
        fld_78 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148) < 2;
        goto LABEL_32;
      }
      break;
    case 8:
      if ( *(uint8_t *)(this + 8220) == 0 )
      {
        fld_782 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148);
        fld_78 = fld_782 < dword_738604[sub_41A5E0(this + 7028)];
        goto LABEL_32;
      }
      break;
    case 0xA:
      if ( *(uint32_t *)(this + 7812) == 0
        && *(uint32_t *)(this + 7828) == 0
        && *(uint32_t *)(this + 7816) == 11
        && *(uint32_t *)(this + 7808) == 1
        && *(int *)(*(uint32_t *)(this + 8428) + 148) >= 1 )
      {
        sub_5DB550(44, 60);
      }
      break;
    case 0xC:
      if ( *(uint32_t *)(*(uint32_t *)(this + 120) + 148) == 3 )
      {
        if ( *(uint8_t *)(this + 8228) != 0 )
        {
          sub_4AECE0(4);
        }
        else if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
        {
          (*(void (/*thiscall*/ **)(int, int, uint32_t, int, uint32_t))(*(uint32_t *)this + 560))(this, 16, 0, 1, 0);
        }
      }
      if ( *(uint8_t *)(this + 8220) == 0 )
      {
        fld_78 = *(uint32_t *)(*(uint32_t *)(this + 120) + 148) < 2;
LABEL_32:
        if ( !fld_78 )
        {
          v10 = *(uint32_t *)this;
          pThis_494 = (*(int (/*thiscall*/ **)(int, uint32_t, int, uint32_t, uint32_t))(*(uint32_t *)this + 1172))(this, 0, -1, 0, 0);
          (*(void (/*thiscall*/ **)(int, int))(v10 + 212))(this, pThis_494);
          *(uint8_t *)(this + 8220) = 1;
        }
      }
      break;
    case 0xE:
      if ( *(uint32_t *)(this + 7964) == 30
        && *(uint8_t *)(this + 8376) == 0
        && *(int *)(*(uint32_t *)(this + 120) + 148) >= 2 )
      {
        fld_215C = sub_42FCB0(228);
        v125 = 1;
        if ( fld_215C != 0 )
        {
          if ( *(uint32_t *)(this + 384) < 0x10u )
            LOBYTE(fld_16C) = this + 108;
          else
            fld_16C = *(uint32_t *)(this + 364);
          v13 = sub_431920(fld_16C, (char)"Effect/Animation/FollowMeCast.ani", 1);
        }
        else
        {
          v13 = 0;
        }
        v125 = -1;
        fld_215C = sub_44B6C0(284);
        v125 = 2;
        if ( fld_215C != 0 )
          v14 = (int *)sub_44E1F0(v13, 1);
        else
          v14 = nullptr;
        fld_74 = *(uint32_t *)(this + 116);
        v125 = -1;
        sub_45FE80(fld_74, (int)v14, 2, 0, (int)v14, 0, 0);
        if ( (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this) != 0 )
          pThis_11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 17;
        else
          pThis_11 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 17;
        v17 = *v14;
        fld_217C = pThis_11;
        pThis_80 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 128))(this);
        pThis_7C = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, pThis_80 + 81);
        (*(void (/*thiscall*/ **)(int *, int, int))(v17 + 112))(v14, fld_217C, pThis_7C);
        v20 = *v14;
        pThis_98 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
        (*(void (/*thiscall*/ **)(int *, int))(v20 + 148))(v14, pThis_98);
        *(uint8_t *)(this + 8376) = 1;
      }
      break;
    case 0x12:
      if ( *(uint8_t *)(this + 8404) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 4 )
      {
        (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
          this,
          "PRICK",
          -1,
          0,
          0);
        *(uint8_t *)(this + 8404) = 1;
      }
      break;
    case 0x13:
      if ( *(uint8_t *)(this + 8504) == 0 )
      {
        if ( *(int *)(*(uint32_t *)(this + 120) + 148) >= 1 )
        {
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 308))(this) != 0 )
          {
            (*(void (/*thiscall*/ **)(int, uint32_t, int, int, uint32_t, int, int))(*(uint32_t *)this + 876))(
              this,
              0,
              500,
              500,
              0,
              -1500,
              1);
            v37 = *(uint32_t *)this;
            fld_2140 = sub_432E50(*(uint32_t *)(this + 8512));
            pThis_982 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 152))(this, fld_2140);
            (*(void (/*thiscall*/ **)(int, int))(v37 + 896))(this, pThis_982);
          }
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "HEAVEN_HIT",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "WZ_HEAVEN_HIT",
            -1,
            0,
            0);
          *(uint8_t *)(this + 8504) = 1;
        }
        if ( *(uint8_t *)(this + 8504) == 0
          && fabs(*(float *)(*(uint32_t *)(this + 112) + 20)) >= 20.0
          && sub_699000(this + 6560) >= *(uint32_t *)(this + 8508) + 150 )  // 【clock_now(clk)】
        {
          pThis_39C = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 924))(this, 2)];
          pThis_983 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
          v42 = *(uint32_t *)this;
          v43 = *(uint32_t *)pThis_39C;
          v124 = pThis_983 == 0;
          v44 = (*(int (/*thiscall*/ **)(int))(v42 + 128))(this);
          pThis_7C2 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v44);
          pThis_78 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 120))(this, pThis_7C2);
          (*(void (/*thiscall*/ **)(int, int))(v43 + 40))(pThis_39C, pThis_78);
          v47 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_39C + 28))(pThis_39C);
          *(uint8_t *)(v47 + 84) = v124;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pThis_39C + 12))(pThis_39C, 0);
          (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pThis_39C + 92))(pThis_39C, v114);
          fld_742 = *(void **)(this + 116);
          v125 = 4;
          sub_4600B0(fld_742, 2, 0, (int)v114);
          *(uint32_t *)(this + 8508) = sub_699000(this + 6560);
          v125 = -1;
          sub_5E5260(v114);
        }
      }
      break;
    case 0x14:
      if ( *(uint8_t *)(this + 8520) == 0 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 3 )
      {
        fld_2144 = *(uint32_t *)(this + 8516);
        if ( fld_2144 == 13 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "MAGE_SWING",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, void *, int, int))(*(uint32_t *)this + 212))(
            this,
            "WZ_SWING",
            -1,
            0,
            0,
            v111,
            v112,
            v113);
        }
        else if ( fld_2144 == 20 )
        {
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t))(*(uint32_t *)this + 212))(
            this,
            "LESSON_START",
            -1,
            0,
            0);
          (*(void (/*thiscall*/ **)(int, const char *, int, uint32_t, uint32_t, void *, int, int))(*(uint32_t *)this + 212))(
            this,
            "R_WZ_LESSON_START",
            -1,
            0,
            0,
            v111,
            v112,
            v113);
        }
        *(uint8_t *)(this + 8520) = 1;
      }
      break;
    case 0x15:
      fld_2154 = *(uint32_t *)(this + 8532);
      if ( fld_2154 != 0 )
      {
        if ( fld_2154 == 1 && *(int *)(*(uint32_t *)(this + 120) + 148) >= 10 )
          sub_5DB550(57, 63);
      }
      else
      {
        if ( fabs(*(float *)(*(uint32_t *)(this + 112) + 16)) >= 20.0
          && sub_699000(this + 6560) >= *(uint32_t *)(this + 8548) + 200 )  // 【clock_now(clk)】
        {
          pThis_39C2 = dword_8F8270[(*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 924))(this, 2)];
          pThis_984 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 152))(this);
          v124 = pThis_984 == 0;
          if ( pThis_984 != 0 )
            pThis_782 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) - 20;
          else
            pThis_782 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)this + 120))(this) + 20;
          v26 = *(uint32_t *)this;
          v27 = *(uint32_t *)pThis_39C2;
          fld_217C = pThis_782;
          v28 = (*(int (/*thiscall*/ **)(int))(v26 + 128))(this);
          pThis_7C3 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 124))(this, v28);
          (*(void (/*thiscall*/ **)(int, int, int))(v27 + 40))(pThis_39C2, fld_217C, pThis_7C3);
          v30 = (*(int (/*thiscall*/ **)(int))(*(uint32_t *)pThis_39C2 + 28))(pThis_39C2);
          *(uint8_t *)(v30 + 84) = v124;
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pThis_39C2 + 12))(pThis_39C2, 0);
          (*(void (/*thiscall*/ **)(int, char *))(*(uint32_t *)pThis_39C2 + 92))(pThis_39C2, v114);
          fld_743 = *(void **)(this + 116);
          v125 = 3;
          sub_4600B0(fld_743, 2, 0, (int)v114);
          *(uint32_t *)(this + 8548) = sub_699000(this + 6560);
          v125 = -1;
          sub_5E5260(v114);
        }
        fld_783 = *(uint32_t *)(this + 120);
        if ( *(int *)(fld_783 + 148) >= 7 && *(uint32_t *)(this + 8580) == 0 )
        {
          sub_4939E0(fld_783, 1);
          sub_4AECE0(7);
          sub_4939E0(*(uint32_t *)(this + 8544), 1);
          *(uint32_t *)(this + 8540) = sub_699000(this + 6560);
          sub_4BA610(4);
          sub_4BA730(0, 4, 0, -106);
          *(uint32_t *)(this + 8580) = 1;
        }
        fld_21842 = *(uint32_t *)(this + 8580) < 1;
        if ( *(uint32_t *)(this + 8580) == 1 )
        {
          if ( sub_699000(this + 6560) >= dword_9B9340 + *(uint32_t *)(this + 8540) )  // 【clock_now(clk)】
          {
            sub_4BA730(1, 4, 0, -106);
            *(uint32_t *)(this + 8580) = 2;
          }
          fld_21842 = *(uint32_t *)(this + 8580) < 1;
        }
        if ( !fld_21842 )
        {
          pThis_19A0 = sub_699000(this + 6560);  // 【clock_now(clk)】
          v35 = sub_42B420(150, 255, pThis_19A0, 150);
          sub_491F80(-1, -1, -1, v35, 1);
        }
      }
      break;
    default:
      break;
  }
  if ( dword_8F7C04 == this && *(uint32_t *)(this + 200) != 2 )
  {
    if ( *(uint32_t *)(this + 6556) == 10 && *(uint32_t *)(this + 7812) == 0 )
    {
      if ( *(uint32_t *)(this + 7808) == 0
        && (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 38) > 0
        && *(uint32_t *)(this + 7820) == -1
        && sub_699000(this + 36) >= *(uint32_t *)(this + 8572)  // 【clock_now(clk)】
        && ((*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1132))(this, 0) != 4
         || (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1132))(this, 1) != 4) )
      {
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
      }
      if ( *(uint32_t *)(this + 7808) == 1
        && *(uint8_t *)(this + 8584) != 0
        && *(uint32_t *)(*(uint32_t *)(this + 112) + 192) == 4 )
      {
        v111 = nullptr;
        v112 = 0;
        v113 = 0;
        v125 = 5;
        fld_217C = 2;
        sub_431230(&fld_217C);
        fld_217C = 0;
        sub_431230(&fld_217C);
        fld_217C = 0;
        sub_431230(&fld_217C);
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 6, v110, 0, 0);
        v125 = -1;
        sub_5E5260(v110);
      }
    }
    if ( *(uint32_t *)(this + 6556) == 16 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int, int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 1, 0, 0, 0);
    v49 = (int *)&unk_795930;
    do
    {
      fld_199C = *(uint32_t *)(this + 6556);
      if ( (fld_199C == 0 || fld_199C == 11)
        && sub_4842B0(*v49, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, *v49) != 0 )
      {
        Block = nullptr;
        Src = nullptr;
        v117 = 0;
        fld_217C = *v49;
        v125 = 6;
        sub_431230(&fld_217C);
        if ( *v49 == 30 )
        {
          fld_20B4 = *(uint32_t *)(this + 8372);
          if ( fld_20B4 != 0 && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)fld_20B4 + 80))(fld_20B4) != 0 )
          {
            fld_217C = 0;
            sub_431230(&fld_217C);
          }
          else
          {
            fld_217C = 1;
            sub_431230(&fld_217C);
          }
        }
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 14, v114, 0, 0);
        v125 = -1;
        if ( Block != nullptr )
          j__free(Block);
        Block = nullptr;
        Src = nullptr;
        v117 = 0;
      }
      ++v49;
    }
    while ( (int)v49 < (int)&dword_795948 );
    fld_199C2 = *(uint32_t *)(this + 6556);
    if ( (fld_199C2 == 4 || fld_199C2 == 3) && (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)this + 724))(this) == 0 )
    {
      pThis_308 = (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 8) == 0
         && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 776))(this, 16) == 0;
      pThis_3082 = pThis_308;
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 3);
      sub_47E440(pThis_3082);
      if ( sub_4842B0(3, nullptr) != -1
        && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 3) != 0 )
      {
        pThis_474 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, 3);
        sub_5DCA10(pThis_474);
      }
    }
    if ( *(uint32_t *)(this + 6556) == 17 && sub_699000(this + 6560) >= *(uint32_t *)(this + 8396) )  // 【clock_now(clk)】
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    fld_199C3 = *(uint32_t *)(this + 6556);
    if ( (fld_199C3 == 0 || fld_199C3 == 11)
      && sub_4842B0(4, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 4) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 7;
      fld_217C = 4;
      sub_431230(&fld_217C);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 18, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    if ( *(uint32_t *)(this + 6556) == 18 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    fld_199C4 = *(uint32_t *)(this + 6556);
    if ( fld_199C4 == 0 || fld_199C4 == 11 || fld_199C4 == 8 || fld_199C4 == 6 )
    {
      v57 = 0;
      v120 = 0;
      do
      {
        pThis_1FB4 = sub_4842B0(dword_7958E8[v57], (void *)(this + 8116));
        v59 = dword_7958E8[v57];
        fld_217C = pThis_1FB4;
        if ( v59 == 5 || v59 == 6 || v59 == 7 || v59 == 9 || v59 == 8 )
        {
          if ( pThis_1FB4 == -1 )
            goto LABEL_246;
          v60 = sub_5DC170(0);
          (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, dword_7958E8[v57]);
          if ( v60 >= sub_47E9D0(1) )
          {
            v61 = *((uint32_t **)dword_8F8528 + 7);
            v62 = sub_422E70(1205);
            sub_43BEE0(v61, v62, -6567706, 0, -1);
            goto LABEL_246;
          }
          pThis_1FB4 = fld_217C;
        }
        if ( pThis_1FB4 != -1
          && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, dword_7958E8[v57]) != 0 )
        {
          v63 = v120;
          pThis_488 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, dword_7958E8[v120]);
          pThis_4742 = (*(int (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1140))(this, dword_7958E8[v63]);
          v66 = 0;
          v122 = 0;
          v123 = 0;
          fld_199C6 = 0;
          if ( pThis_4742 == -1 )
            pThis_4742 = sub_41A5E0(pThis_488 + 510);
          fld_217C = sub_41A5E0(*(uint32_t *)(pThis_488 + 316) + 14 * (pThis_4742 - 1));
          v67 = dword_7958E8[v120];
          switch ( v67 )
          {
            case 5:
            case 6:
            case 7:
            case 9:
            case 8:
            case 10:
              v69 = sub_47E9D0(0);
LABEL_197:
              v123 = 3;
LABEL_198:
              v66 = v69;
              v122 = v69;
              break;
            case 11:
              v66 = sub_47E9D0(0);
              v122 = v66;
              v123 = 0;
              fld_199C6 = sub_47E9D0(3);
              break;
            case 15:
              v66 = sub_47E9D0(0);
              fld_199C5 = *(uint32_t *)(this + 6556) == 6;
              v122 = v66;
              v123 = 1;
              if ( fld_199C5 || (fld_199C6 = sub_47E9D0(1), *(uint32_t *)(this + 6556) == 6) )
              {
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 42);
                fld_217C = fld_217C * sub_47E9D0(2) / 100;
              }
              break;
            case 16:
              v66 = sub_47E9D0(0);
              v122 = v66;
              v123 = 3;
              fld_199C6 = sub_47E9D0(5);
              break;
            case 17:
              v66 = sub_47E9D0(0);
              v122 = v66;
              v123 = 2;
              fld_199C6 = sub_47E9D0(2);
              break;
            case 18:
              v66 = sub_47E9D0(0);
              v122 = v66;
              v123 = 0;
              fld_199C6 = sub_47E9D0(1);
              break;
            case 26:
            case 27:
              v66 = sub_47E9D0(0);
              v123 = 1;
              v122 = v66;
              fld_199C6 = sub_47E9D0(2);
              break;
            case 28:
              v69 = sub_47E9D0(0);
              v123 = 2;
              goto LABEL_198;
            case 31:
              v66 = 10000;
              v123 = 3;
              v122 = 10000;
              fld_199C6 = sub_47E9D0(0);
              break;
            case 43:
              goto LABEL_195;
            case 49:
              v69 = sub_47E9D0(2);
              goto LABEL_197;
            case 50:
LABEL_195:
              v69 = sub_47E9D0(0);
              v123 = 0;
              goto LABEL_198;
            default:
              break;
          }
          Block = nullptr;
          Src = nullptr;
          v117 = 0;
          v125 = 8;
          fld_215C = 0;
          sub_430C80(nullptr, 1, (int)&fld_215C);
          v70 = (char *)Src;
          fld_215C = 0;
          if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *(uint32_t *)Src = 0;
            v71 = v70 + 4;
            Src = v71;
          }
          else
          {
            sub_430C80(Src, 1, (int)&fld_215C);
            v71 = Src;
          }
          v72 = dword_7958E8[v120];
          fld_215C = v72;
          if ( Block != nullptr && ((char *)v71 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v71 = v72;
            fld_217C2 = v71 + 1;
            Src = fld_217C2;
          }
          else
          {
            sub_430C80(v71, 1, (int)&fld_215C);
            fld_217C2 = Src;
          }
          if ( Block != nullptr && ((char *)fld_217C2 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *fld_217C2 = fld_217C;
            v74 = fld_217C2 + 1;
            Src = v74;
          }
          else
          {
            sub_430C80(fld_217C2, 1, (int)&fld_217C);
            v74 = Src;
          }
          if ( Block != nullptr && ((char *)v74 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v74 = v66;
            v75 = v74 + 1;
            Src = v75;
          }
          else
          {
            sub_430C80(v74, 1, (int)&v122);
            v75 = Src;
          }
          if ( Block != nullptr && ((char *)v75 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v75 = v123;
            v76 = v75 + 1;
            Src = v76;
          }
          else
          {
            sub_430C80(v75, 1, (int)&v123);
            v76 = Src;
          }
          fld_215C = 4;
          if ( Block != nullptr && ((char *)v76 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v76 = 4;
            v77 = v76 + 1;
            Src = v77;
          }
          else
          {
            sub_430C80(v76, 1, (int)&fld_215C);
            v77 = Src;
          }
          fld_215C = 4;
          if ( Block != nullptr && ((char *)v77 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
          {
            *v77 = 4;
            v78 = v77 + 1;
            Src = v78;
          }
          else
          {
            sub_430C80(v77, 1, (int)&fld_215C);
            v78 = Src;
          }
          if ( fld_199C6 > 0 || *(uint32_t *)(this + 6556) == 6 )
          {
            fld_215C = 1000;
            if ( Block != nullptr && ((char *)v78 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
            {
              *v78 = 1000;
              v79 = v78 + 1;
              Src = v79;
            }
            else
            {
              sub_430C80(v78, 1, (int)&fld_215C);
              v79 = Src;
            }
            fld_215C = 1000;
            if ( Block != nullptr && ((char *)v79 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
            {
              *v79 = 1000;
              fld_199C62 = v79 + 1;
              Src = fld_199C62;
            }
            else
            {
              sub_430C80(v79, 1, (int)&fld_215C);
              fld_199C62 = Src;
            }
            if ( Block != nullptr && ((char *)fld_199C62 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
            {
              *fld_199C62 = fld_199C6;
              Src = fld_199C62 + 1;
            }
            else
            {
              sub_430C80(fld_199C62, 1, (int)&fld_199C6);
            }
            if ( *(uint32_t *)(this + 6556) == 6 )
            {
              fld_215C = 1;
              sub_431230(&fld_215C);
            }
          }
          (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, v114, 0, 0);
          v125 = -1;
          if ( Block != nullptr )
            j__free(Block);
          Block = nullptr;
          Src = nullptr;
          v117 = 0;
          v57 = v120;
        }
LABEL_246:
        v120 = ++v57;
      }
      while ( v57 < 18 );
    }
    fld_20FC = *(uint32_t *)(this + 8444) != -1
       && *(uint32_t *)(this + 8440) != 0
       && sub_699000(this + 36) < *(uint32_t *)(this + 8444)  // 【clock_now(clk)】
       && (uint8_t)sub_5DB490(this) != 0;
    fld_20FC2 = fld_20FC;
    (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1160))(this, 39);
    sub_47E440(fld_20FC2);
    if ( sub_4842B0(39, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 39) != 0 )
    {
      sub_5DCE00(*(uint32_t *)(this + 8440));
    }
    fld_199C7 = *(uint32_t *)(this + 6556);
    if ( fld_199C7 == 0 || fld_199C7 == 11 )
    {
      v120 = (int)&unk_737FFC;
      do
      {
        if ( sub_4842B0(*(uint32_t *)v120, nullptr) != -1 )
        {
          v83 = (uint32_t *)v120;
          pThis_4882 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1160))(this, *(uint32_t *)v120);
          pThis_4743 = (*(int (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1140))(this, *v83);
          fld_217C = pThis_4743;
          v86 = sub_47E9D0(2);
          fld_215C = sub_5DD040(v86, 0, 1);
          v87 = sub_47EF20(2, pThis_4743, -1, -1, 11);
          if ( fld_215C < v87 )
          {
            if ( (int)sub_47E9D0(7) <= 0 || (v94 = sub_5DD040(60006, 0, 1)) >= sub_47E9D0(7) )
            {
              v95 = (uint32_t *)v120;
              if ( (*(uint8_t (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)this + 1312))(this, *(uint32_t *)v120) != 0 )
              {
                Block = nullptr;
                Src = nullptr;
                v117 = 0;
                v125 = 9;
                fld_215C = 0;
                sub_430C80(nullptr, 1, (int)&fld_215C);
                v96 = (char *)Src;
                fld_215C = 0;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = 0;
                  v97 = v96 + 4;
                  Src = v97;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&fld_215C);
                  v97 = Src;
                }
                if ( Block != nullptr && ((char *)v97 - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *v97 = *v95;
                  Src = v97 + 1;
                }
                else
                {
                  sub_430C80(v97, 1, (int)v95);
                }
                fld_217C3 = fld_217C;
                if ( fld_217C == -1 )
                  fld_217C3 = sub_41A5E0(pThis_4882 + 510);
                v99 = sub_41A5E0(*(uint32_t *)(pThis_4882 + 316) + 14 * (fld_217C3 - 1));
                v100 = (char *)Src;
                fld_217C = v99;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = fld_217C;
                  Src = v100 + 4;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&fld_217C);
                }
                v101 = sub_47E9D0(4);
                v102 = (char *)Src;
                fld_217C = v101;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = fld_217C;
                  Src = v102 + 4;
                }
                else
                {
                  sub_430C80(Src, 1, (int)&fld_217C);
                }
                fld_217C = sub_47E9D0(3);
                v103 = (char *)Src;
                if ( Block != nullptr && ((uint8_t *)Src - (uint8_t *)Block) >> 2 < (unsigned int)((v117 - (int)Block) >> 2) )
                {
                  *(uint32_t *)Src = fld_217C;
                  Src = v103 + 4;
                }
                else
                {
                  sub_430FB0((int)&fld_215C, Src, (int)&fld_217C);
                }
                fld_215C = 4;
                sub_431230(&fld_215C);
                fld_215C = 4;
                sub_431230(&fld_215C);
                (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 10, v114, 0, 0);
                v125 = -1;
                if ( Block != nullptr )
                  j__free(Block);
                Block = nullptr;
                Src = nullptr;
                v117 = 0;
              }
              goto LABEL_300;
            }
            v92 = *((uint32_t **)dword_8F8528 + 7);
            v93 = sub_422E70(2104);
          }
          else
          {
            v88 = sub_47E9D0(2);
            v89 = &dword_738020;
            while ( v88 != *v89 )
            {
              if ( (int)++v89 >= (int)&dword_738030 )
              {
                v90 = &unk_738040;
                while ( v88 != *v90 )
                {
                  if ( (int)++v90 >= (int)&dword_738044 )
                  {
                    v91 = 0;
                    goto LABEL_268;
                  }
                }
                break;
              }
            }
            v91 = 1;
LABEL_268:
            v92 = *((uint32_t **)dword_8F8528 + 7);
            v93 = sub_422E70(v91 != 0 ? 2103 : 1);
          }
          sub_43BEE0(v92, v93, -6567706, 0, -1);
        }
LABEL_300:
        v120 += 4;
      }
      while ( v120 < (int)&dword_738020 );
    }
    fld_199C8 = *(uint32_t *)(this + 6556);
    if ( (fld_199C8 == 0 || fld_199C8 == 11 || fld_199C8 == 8 || fld_199C8 == 18)
      && sub_4842B0(12, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 12) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 10;
      fld_215C = 12;
      sub_431230(&fld_215C);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 19, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    if ( *(uint32_t *)(this + 6556) == 19 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    fld_199C9 = *(uint32_t *)(this + 6556);
    if ( (fld_199C9 == 0 || fld_199C9 == 11 || fld_199C9 == 18)
      && sub_4842B0(13, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 13) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 11;
      fld_215C = 13;
      sub_431230(&fld_215C);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 20, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    fld_199C10 = *(uint32_t *)(this + 6556);
    if ( (fld_199C10 == 0 || fld_199C10 == 11)
      && sub_4842B0(20, nullptr) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 20) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 12;
      fld_215C = 20;
      sub_431230(&fld_215C);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 20, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    if ( *(uint32_t *)(this + 6556) == 20 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
      (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    fld_199C11 = *(uint32_t *)(this + 6556);
    if ( (fld_199C11 == 0 || fld_199C11 == 11 || fld_199C11 == 8 || fld_199C11 == 18)
      && sub_4842B0(14, (void *)(this + 8116)) != -1
      && (*(uint8_t (/*thiscall*/ **)(int, int))(*(uint32_t *)this + 1312))(this, 14) != 0 )
    {
      v111 = nullptr;
      v112 = 0;
      v113 = 0;
      v125 = 13;
      fld_215C = 0;
      sub_431230(&fld_215C);
      fld_215C = 14;
      sub_431230(&fld_215C);
      (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 21, v110, 0, 0);
      v125 = -1;
      if ( v111 != nullptr )
        j__free(v111);
    }
    if ( *(uint32_t *)(this + 6556) == 21 )
    {
      if ( *(uint32_t *)(this + 8532) == 0
        && *(uint32_t *)(*(uint32_t *)(this + 120) + 148) == 7
        && (uint8_t)sub_4BFC10(this + 8116) == 0 )
      {
        v111 = nullptr;
        v112 = 0;
        v113 = 0;
        v125 = 14;
        fld_215C = 1;
        sub_431230(&fld_215C);
        fld_215C = sub_699000(this + 6560) - *(uint32_t *)(this + 8540);  // 【clock_now(clk)】
        sub_431230(&fld_215C);
        (*(void (/*thiscall*/ **)(int, int, char *, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 21, v110, 0, 0);
        if ( sub_699000(this + 6560) == *(uint32_t *)(this + 8540) )  // 【clock_now(clk)】
          sub_4BA730(2, 4, 0, 0);
        v125 = -1;
        if ( v111 != nullptr )
          j__free(v111);
        v111 = nullptr;
        v112 = 0;
        v113 = 0;
      }
      if ( *(uint32_t *)(this + 8532) == 1 && *(uint8_t *)(*(uint32_t *)(this + 120) + 170) != 0 )
        (*(void (/*thiscall*/ **)(int, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)this + 560))(this, 0, 0, 0, 0);
    }
  }
}

